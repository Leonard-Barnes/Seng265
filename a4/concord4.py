import sys
import re

class concord:

    def __init__(self, input=None, output=None):
        self.input = input
        self.output = output
        if(output != None and input != None):
            self.full_concordance()

    def full_concordance(self):
        file_text = []
        ex_words = []
        line_words = []
        nice_words = []
        final_lines = []

        file_text = self.__get_lines(self.input)
        ex_words = self.__create_exwords(file_text)
        line_words = self.__create_lines(file_text)
        nice_words = self.__create_word_list(line_words)
        nice_words = self.__remove_exwords(nice_words, ex_words)
        nice_words.sort()

        final_lines = self.__format_lines(nice_words, line_words)

        self.__print_to_output(self.output, final_lines)
    
        return final_lines

    def __print_to_output(self, output, final_lines):
        if(output == None):
            return
        else:
            g = open(output, "w")
            for line in final_lines:
                g.write(line)
                g.write('\n')
            g.close()
            return
                
#gets input from file or stdin
    def __get_lines(self, input):
        all_lines = []
        if(input == None):
            for line in sys.stdin:
                all_lines.append(line.strip())
        else:
            f = open(input, "r")
            lines = f.readlines()
            f.close()
            for line in lines:
                all_lines.append(line.strip())
        return all_lines

#creates a list of exclusion words
    def __create_exwords(self, lines):
        ex_words = []
        ex_words = lines[2:lines.index("\"\"\"\"")]
        ex_words = list(dict.fromkeys(ex_words))
        return ex_words
 
#creates a list of every line in the input
    def __create_lines(self, lines):
        line_words = []
        line_words = lines[lines.index("\"\"\"\"")+1:]
        return line_words

#creates a list over every word in the file
    def __create_word_list(self, lines):
        nice_words = []
        for line in lines:
            words = []
            words = line.split()
            for word in words:
                nice_words.append(word.lower())
        nice_words = list(dict.fromkeys(nice_words))
        return nice_words

#removes exclusion words from the list of words to search for        
    def __remove_exwords(self, words, ex_words):
        for ex_word in ex_words:
                for word in words:
                        if (ex_word == word):
                                words.remove(ex_word)
                        elif (ex_word.lower() == word):
                                words.remove(ex_word.lower())
        return words

#checks line for the desired word then adds the line to the final list
    def __format_lines(self, words, lines):
        final_lines = []
        for word in words:
            upper = word.upper()
            for line in lines:
                matchobj = re.search(r"\b" + re.escape(word) + r"\b" , line, re.IGNORECASE)
                if(matchobj):
                    line = re.sub(r"\b" + re.escape(word) + r"\b", upper, line, flags=re.I)
                    final_lines.append(self.__shift_lines(line,upper))
        return final_lines

#shifts the line over the desired amount of spaces
    def __shift_lines(self, line, word):
        line = line.split()
        index = line.index(word)
        before_word = line[0:index]
        after_word = line[index+1:]
        after_word_string = ' '.join(after_word)
        while(len(after_word_string + ' ' + word) > 31):
            after_word = after_word[0:len(after_word)-1]
            after_word_string = ' '.join(after_word)
        after_word_string = after_word_string
        before_word_string = ' '.join(before_word)
        while(len(before_word_string + ' ') > 20):
            before_word = before_word[1:]
            before_word_string = ' '.join(before_word)
        count = len(before_word_string)
        while(count < 28):
            before_word_string = ' ' + before_word_string
            count = count + 1
        word = word.strip()
        if after_word_string:
            after_word_string = ' ' + after_word_string
        if before_word_string:
            before_word_string = before_word_string + ' '
        return_string = before_word_string + word + after_word_string
        return return_string





















