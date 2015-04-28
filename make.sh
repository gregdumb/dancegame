#!/bin/ash

echo "Preparing to compile code..."

	g++ main.cpp dance.cxx -o dance.out `fltk-config --cxxflags --ldflags --use-images`

	while true; do
		read -p "Execute the program now? " yn
		case $yn in
			[Yy]* ) ./dance.out; break;;
			[Nn]* ) exit;;
			* ) exit;;
		esac
	done
