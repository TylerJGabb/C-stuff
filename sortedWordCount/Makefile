all: wordCount2

wordCount2: wordCount2.o
	gcc wordCount2.o -o wordCount2

wordCount2.o: wordCount2.c
	gcc -c wordCount2.c

.PHONY:
clean:
	rm *.o*

.PHONY:
mobyDickTop10: wordCount2
	wordCount2 mobyDick.txt aaaaaaaaaa
 