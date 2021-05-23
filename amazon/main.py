from bs4 import BeautifulSoup
import requests

def get_header():
	return {
		'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
		'accept-encoding': 'gzip, deflate, br',
		'accept-language': 'en-US,en;q=0.9,tr;q=0.8',
		'cache-control': 'max-age=0',
		'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
	}

def parse_html(url):
	response = requests.get(url, headers=get_header())
	return BeautifulSoup(response.text, 'html.parser')

def parse_html_multi_pages(url, page_count):
	'''
	This function parses all Amazon HTMLs until the end page (calculated by page_count)

	url: string -> Base product search url with pagination.
		Example: 'https://www.amazon.co.uk/s?i=aps&k=mr16 12v 35w&ref=nb_sb_noss'
	page_count: int -> The page count in the paginated URL.

	Returns list[BeautifulSoup()] -> A list of parsed HTMLs
	'''
	return [parse_html(url + '&page={}'.format(page_i)) for page_i in range(page_count)]

def parse_price_span(price):
	if price is None:
		return None

	return float(price.text.strip().split('£')[1].strip())

def parse_base_price_span(base_price):
	if base_price is None or '/kg' not in base_price:
		return -1

	return float(base_price.text.strip().split('£')[1].split('/')[0])

def crawl_results_html(https_prefix, parsed_html):
	result_list = []
	for f in parsed_html.findChildren('div', {'class':'s-result-item'}):
		if not f.has_attr('data-index'):
			continue

		h2 = f.findChild('h2')
		if not h2:
			continue

		link = h2.findChild('a')
		if not link:
			continue

		span = link.findChild('span')
		if not span:
			continue

		price = parse_price_span(
				f.findChild('span', {'class': 'a-price', 'data-a-color': 'base'}))
		if not price:
			continue

		base_price = parse_base_price_span(f.findChild('span', {'class': 'a-size-base'}))
		result_list.append((price, base_price, span.text, https_prefix + link['href']))

	return result_list

def crawl_results_html_array(https_prefix, parsed_html_array):
	'''
	This function returns a product array (with links and prices) by extracting the info in the
	parsed HTMLs

	https_prefix: string -> The prefix to add into head of all service URLs.
		Example: 'https://amazon.co.uk'
	parsed_html_array: list[BeautifulSoup()] -> A list of parsed HTMLs

	Returns list[price, base_price, text, link]
	'''
	result_list = []
	for parsed_html in parsed_html_array:
		result_list.extend(crawl_results_html(https_prefix, parsed_html))
	return result_list
