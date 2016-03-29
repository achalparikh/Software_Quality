JAVAC=javac
sources = $(wildcard *.java)
classes = $(sources:.java=.class)

all: 
	javac -d ./ ../../Code/BackEnd/*.java
	javac *.java

run:
	java TestRunner

clean :
	rm -f *.class

%.class : %.java
	$(JAVAC) $<