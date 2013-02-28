ARQ_TCC=Artigo_TG.tex

all: compilar_tg

compilar_tg:
	pdflatex -synctex=1 -interaction=nonstopmode $(ARQ_TCC)
	bibtex Artigo_TG
	pdflatex -synctex=1 -interaction=nonstopmode $(ARQ_TCC)

clean:
	@find . -iname "*.log" -exec rm {} \;
	@find . -iname "*.aux" -exec rm {} \;
	@find . -iname "*.dvi" -exec rm {} \;
	@find . -iname "*.lof" -exec rm {} \;
	@find . -iname "*.bit" -exec rm {} \;
	@find . -iname "*.idx" -exec rm {} \;
	@find . -iname "*.glo" -exec rm {} \;
	@find . -iname "*.bbl" -exec rm {} \;
	@find . -iname "*.ilg" -exec rm {} \;
	@find . -iname "*.toc" -exec rm {} \;
	@find . -iname "*.ind" -exec rm {} \;
	@find . -iname "*.out" -exec rm {} \;
	@find . -iname "*.synctex.gz" -exec rm {} \;
	@find . -iname "*.blg" -exec rm {} \;
	@find . -iname "*.thm" -exec rm {} \;
	@find . -iname "*.pre" -exec rm {} \;
	echo -e "Tudo limpo!"
