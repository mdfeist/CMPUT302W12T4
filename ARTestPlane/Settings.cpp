#include "Settings.h"
#include "pugixml.hpp"

#include <stdio.h>

int Settings::open() {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("Properties.xml");
	
	if (result.status) {
		printf("Load Settings Result: %s\n", result.description());
	} else {
		printf("Settings File Found\n");

		// Get Settings
		pugi::xml_node settings = doc.child("Settings");

		if (settings) {
			
		} else {
			printf("No Settings Attribute\n");
		}
	}

	return 0;
};