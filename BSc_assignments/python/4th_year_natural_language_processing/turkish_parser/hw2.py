#! /usr/bin/python
# -*- coding: utf-8 -*

import nltk
from nltk import parse
class TurkishParser(nltk.parse.api.ParserI):
	"""Engin Ertas : 1560176, 
		'Turkish Parser'"""
	list = []
	def __init__(self):
		return	

	def nbest_parse(self, xx):
		parser = parse.load_parser('file:hw2.fcfg', trace =2)
		wordlist = xx.split()
		tree = parser.nbest_parse(wordlist)
		for a in tree : print a
