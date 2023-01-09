#!/usr/bin/env python3

import sys

def main():

	all_lines = []
	ex_words = []
	line_words = []
	nice_words = []

	for line in sys.stdin:
		all_lines.append(line.strip())
	#obtain ex words in a list
	ex_words = all_lines[2:all_lines.index("\"\"\"\"")]
	ex_words = list(dict.fromkeys(ex_words))
	line_words = all_lines[all_lines.index("\"\"\"\"")+1:]
	#version control
	if(all_lines[0] == "1\n"):
		print("Input is verion 1, concord2.py expected version 2")
		exit()
	#organized list of words
	for line in line_words:
		words = []
		words = line.split()
		for word in words:
			nice_words.append(word)
	nice_words2 = []
	#lowercase all words for continuity
	for word in nice_words:
		nice_words2.append(word.lower())
	nice_words = nice_words2
	#remove duplicates
	nice_words = list(dict.fromkeys(nice_words))
	#remove ex words from list of words
	removewords(ex_words, nice_words)
	#sort the words
	nice_words.sort()
	#print all the lines
	printlines(nice_words, line_words)
	
def removewords(ex_words, nice_words):
	for ex_word in ex_words:
		for nice_word in nice_words:
			if (ex_word == nice_word):
				nice_words.remove(ex_word)
			elif (ex_word.lower() == nice_word):
				nice_words.remove(ex_word.lower())

def printlines(nice_words, line_words):
	for word in nice_words:
		for line in line_words:
			index = 0
			final = line.split()
			test = []
			check = 0
			sp_word = ""
			for i in final:
				
				if(word == i.lower()):
					sp_word = i.upper()
					test.append(i.upper())
					check = 1
				else:
					test.append(i)
			if(check == 1):
				index = test.index(sp_word)
				before_word = test[0:index]
				after_word = test[index+1:]
				after_word_string = ' '.join(after_word)
				while(len(after_word_string + ' ' + sp_word) > 31):
					after_word = after_word[0:len(after_word)-1]
					after_word_string = ' '.join(after_word)
				after_word_string = ' ' + after_word_string
				before_word_string = ' '.join(before_word)
				while(len(before_word_string + ' ') > 20):
					before_word = before_word[1:]
					before_word_string = ' '.join(before_word)
				count = 0
				for char in before_word_string:
					count = count + 1
				while(count < 28):
					before_word_string = ' ' + before_word_string
					count = count + 1
				if(len(after_word) == 0):
					print(before_word_string + ' ' + sp_word)
				else:
					print(before_word_string + ' '+ sp_word + after_word_string)

if __name__ == "__main__":
	main()
