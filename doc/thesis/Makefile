DOC = thesis

all: build

build:
	pdflatex $(DOC).tex
	bibtex $(DOC)
	pdflatex $(DOC).tex
	bibtex $(DOC)
	pdflatex $(DOC).tex

clean:
	rm -rf $(DOC).aux
	rm -rf $(DOC).dvi
	rm -rf $(DOC).log
	rm -rf $(DOC).toc
	rm -rf $(DOC).bbl
	rm -rf $(DOC).blg
	rm -rf $(DOC).ps
	rm -rf $(DOC).pdf
	rm -rf $(DOC).lof
	rm -rf $(DOC).lot
