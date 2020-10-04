#!/usr/bin/env python3

from bs4 import BeautifulSoup
import os
import requests
import sys

def get_header():
	return {
			'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
			'accept-encoding': 'gzip, deflate, br',
			'accept-language': 'en-US,en;q=0.9,tr;q=0.8',
			'cache-control': 'max-age=0',
			#'upgrade-insecure-requests': '1',
			'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
	}


def add_entry_to_list(page_i, li_entry, entry_list, is_response):
	if is_response:
		raw_entry = li_entry.findChild('div', {'class':'content'})
		if raw_entry is None:
			return
	else:
		raw_entry = li_entry

	entry_list.append((
			page_i,
			li_entry['data-id'],
			li_entry['data-author'],
			raw_entry.text.strip().lower()
			))

def get_entries_in_page(url_prefix, page_count):
	url_prefix = url_prefix + '?p='

	entry_list = []

	for page_i in range(1, page_count + 1):
		url = url_prefix + str(page_i)

		response = requests.get(url, headers=get_header())
		parsed_html = BeautifulSoup(response.text, 'html.parser')
		entry_item_list = parsed_html.find('ul', {'id':'entry-item-list'})
		assert entry_item_list is not None

		for li_entry in entry_item_list.findChildren('li'):
			add_entry_to_list(page_i, li_entry, entry_list, False)

			# Try to fetch responses if it has.
			for response_li_entry in li_entry.findChildren('li'):
				add_entry_to_list(page_i, response_li_entry, entry_list, True)

	return entry_list


def start_search_loop(entry_list):
	while True:
		keyword = input('Enter a keyword to search: ').strip().lower()
		print('Keyword is', keyword)

		if keyword:
			for page_i, entry_id, author, entry_text in entry_list:
				if keyword == author or keyword in entry_text:
					print ('Page: %d, Entry Id: %s, Author: %s, Entry: \n %s'
							% (page_i, entry_id, author, entry_text))

if __name__ == '__main__':
	if len(sys.argv) < 3:
		print ('Usage: ./eksireader <url_prefix> <page_count>')
		os._exit(1)

	url_prefix = sys.argv[1]
	page_count = int(sys.argv[2])

	print('Wait a moment! Loading entries')
	entry_list = get_entries_in_page(url_prefix, page_count)
	print('Loading is completed. You can search now')
	start_search_loop(entry_list)
