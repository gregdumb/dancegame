#!/bin/ash

echo "Generating PDF file..."

labname=${PWD##*/}

if [ -f $1.doc ]
then labname=$1
fi

if [ -f $labname.doc ]
then
	doctex $labname.doc
	docsml $labname.doc
	pdflatex $labname.tex

	while true; do
		read -p "Open the PDF now? " yn
		case $yn in
			[Yy]* ) gsview $labname.pdf; break;;
			[Nn]* ) exit;;
			* ) exit;;
		esac
	done
else
	echo "ERROR: couold not find .doc files!"
fi