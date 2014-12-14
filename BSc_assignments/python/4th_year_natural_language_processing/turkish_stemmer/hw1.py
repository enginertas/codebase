#! /usr/bin/python
# -*- coding: utf-8 -*

import nltk
class stemmer(nltk.stem.api.StemmerI):
	"""Engin Ertas : 1560176, 
		'Turkish Verbal Stemmer'"""
	states=[]
	paths =[]
	start_state =[0,1,2,3,4,5,6,7,8,9,10,12,13,14,11]
	final_state =[3,4,5,6,7,9,11,14,15,16]
	def __init__(self):
		#########  Defining the NFS states ###########
		self.states.append(['yım','yim','yüm','yum','um','im','üm','ım'])			# (y)Um -> 0
		self.states[0].extend(['sun', 'sün', 'sin', 'sın', 'sunuz', 'sünüz', 'siniz', 'sınız'])	# sUn(Uz) -> 0
		self.states.append(['yız', 'yiz', 'yuz', 'yüz', 'uz', 'iz', 'üz', 'ız'])		# (y)Uz -> 1
		self.states.extend([['lar','ler'], ['muş', 'müş', 'miş', 'mış']])			# lAr -> 2, # mUs -> 3
		self.states.append(['iyor', 'ıyor', 'uyor', 'üyor', 'yor'])				#(U)yor -> 4 
		self.states.append(['yecek', 'yacak', 'ecek', 'acak', 'eceğ', 'yeceğ', 'acağ', 'yacağ'])#(y)AcAk , mAlI(y) ->5
		self.states[-1].extend(['malı', 'meli', 'malıy', 'meliy'])
		self.states.extend([['ir', 'ır', 'ür', 'ur', 'r'],['ar', 'er']])			# (U)r -> 6, # Ar ->7
		self.states.append(['m', 'n', 'k', 'nız', 'niz', 'nuz', 'nüz'])				# these -> 8
		self.states.append(['dı','di','dü','du','tı','ti','tü','tu','dıy','diy','düy','duy','tıy','tiy','tüy', 'tuy'])			
		self.states.extend([['lım', 'lim'],['ya', 'ye', 'e', 'a','yey','yay', 'ey','ay']])	# DU -> 9, lIm ->10, # (y)A -> 11	
		self.states.append(['yunuz','yünüz','yınız','yiniz','yun','yün','yin','yın']) 		# order ->12
		self.states[-1].extend(['sinler','sınlar','sunlar','sünler','sin','sın','suz', 'süz'])
		self.states.append(['m','zsin','zsın','z','yiz','yız','zsiniz','zsınız','zlar','zler'])	# negative ->13
		self.states.append(['ma','me', 'yama', 'yeme', 'ama', 'eme'])				# mA, (y)AmA ->14
		self.states.append(['mu','mü','mi','mı','yamı','yemi', 'amı', 'emi'])			# mU, (y)AmI ->15
		self.states.append(['yabil', 'yebil','abil', 'ebil'])					# (y)Abil ->16

		#########  Defining the NFS transitions #########
		self.paths.extend([[3,4,5,6,7,11],[3,4,5,6,7],[3,4,5,6,7,9,11],[2,3,4,5,6,7,14,16],[15,16]]) # 0-4
		self.paths.extend([[14,16],[16],[],[9], [2,3,4,5,6,7,9,11,13,14,16],[11],[14,16],[14,16]]) # 5-12  #6-9
		self.paths.extend([[14],[],[],[14]])							# 13-16
				
	def stem(self, word):
		start_list=[]
		end_list=[]
		for state in self.start_state:			##first, define starting possibilities
			for suffix in self.states[state]:
				if word.endswith(suffix):
					start_list.append((word[:-len(suffix)],state, len(unicode(suffix, "utf8")))) #
		
		if(start_list==[]):				##if no extra substrings is found, return word itself
			return word	
		
		end_list.append(word)				## in case of not stemming, put word itself to list

		for (w, st, l) in start_list:			##for each tuple, call sub_stem #
			end_list.append(self.sub_stem(w, st, l)) 				#

		x=100						##default length which is impossible in Turkish
		r_word = 'aa'		
		for w in end_list:				##find the minimum length word
			if w !=-1 and len(unicode(w, "utf8"))<x:
				r_word = w
				x = len(unicode(w, "utf8"))

		return r_word

	def if_ends(self, wrd):
		consonant = ['b','c','ç','d','f','g','ğ','h','j','k','l','m','n','p','r','s','ş','t','v','y','z']
		vowel = ['a', 'e', 'ı', 'i', 'o', 'ö', 'u', 'ü']
		for cons in consonant:
			for vo in vowel:
				if wrd.endswith(vo+cons):
					return True
		return False

	def sub_stem(self, wrd, state, length): #
		transitions=[]
		sub_list=[]		
		for i in self.paths[state]:
			for suffix in self.states[i]:		##first define transitions
				if wrd.endswith(suffix):
					transitions.append((wrd[:-len(suffix)],i,len(unicode(suffix, "utf8")))) #					
							
		if(transitions==[]):				##if no extra substrings is found
			if state in self.final_state:		##return word itself if it is final state
				if state==7:
					if self.if_ends(wrd):	##to handle exceptions in like "sallardı -> sall"
						return wrd					
					else:
						return -1
				elif state==14 or state==15:
					if self.if_ends(wrd):		###
						return wrd
					elif length==2:
						return wrd
					else:
						return -1
				else:
					return wrd			
			else:
				return -1			##return an error state

		for (w, st, l) in transitions:			#call sub stemmer function for transition #
			sub_list.append(self.sub_stem(w,st,l)) 						#
	
		x=100						##default length which is impossible in Turkish
		r_word = 'aa'
		for w in sub_list:				##find the minimum length word
			if w !=-1 and len(unicode(w, "utf8"))<x:	
				r_word = w
				x=len(unicode(w, "utf8"))

		if x==100:					##if eligible short word exists, return it
			return -1
		else:
			return r_word

			
