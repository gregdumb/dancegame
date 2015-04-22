#!/bin/ash

echo "Preparing to compile code..."

	g++ main.cpp dance.cxx -o dance `fltk-config --cxxflags --ldflags`

	while true; do
		read -p "Execute the program now? " yn
		case $yn in
			[Yy]* ) ./dance; break;;
			[Nn]* ) exit;;
			* ) exit;;
		esac
	done