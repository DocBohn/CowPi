TARGETS = mk1c mk1d mk3a

mk1c: *.tex
	pdflatex -jobname=cowpi-mk1c-datasheet "\def\cowpiversion{mk1c}\def\softwareversion{0.4}\input{datasheet}"
	bibtex cowpi-mk1c-datasheet
	pdflatex -jobname=cowpi-mk1c-datasheet "\def\cowpiversion{mk1c}\def\softwareversion{0.4}\input{datasheet}"
	pdflatex -jobname=cowpi-mk1c-datasheet "\def\cowpiversion{mk1c}\def\softwareversion{0.4}\input{datasheet}"

mk1d: *.tex
	pdflatex -jobname=cowpi-mk1d-datasheet "\def\cowpiversion{mk1d}\def\softwareversion{0.4}\input{datasheet}"
	bibtex cowpi-mk1d-datasheet
	pdflatex -jobname=cowpi-mk1d-datasheet "\def\cowpiversion{mk1d}\def\softwareversion{0.4}\input{datasheet}"
	pdflatex -jobname=cowpi-mk1d-datasheet "\def\cowpiversion{mk1d}\def\softwareversion{0.4}\input{datasheet}"

mk3a: *.tex
	pdflatex -jobname=cowpi-mk3a-datasheet "\def\cowpiversion{mk3a}\def\softwareversion{0.4}\input{datasheet}"
	bibtex cowpi-mk3a-datasheet
	pdflatex -jobname=cowpi-mk3a-datasheet "\def\cowpiversion{mk3a}\def\softwareversion{0.4}\input{datasheet}"
	pdflatex -jobname=cowpi-mk3a-datasheet "\def\cowpiversion{mk3a}\def\softwareversion{0.4}\input{datasheet}"

all: $(TARGETS)

clean:
	rm *.aux *.log *.out *.synctex.gz
