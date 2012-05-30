all: thesis

thesis:
	pdflatex thesis.tex
	bibtex thesis
	pdflatex thesis.tex
	bibtex thesis
	pdflatex thesis.tex

clean:
	rm -rf *.aux *.dvi *.log *.toc *.bbl *.blg *.ps *.pdf *.lof *.lot *.out *.brf
