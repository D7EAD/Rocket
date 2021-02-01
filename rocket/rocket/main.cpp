#include "libupload.h"
#include <string>

std::string help = R"(
                              
------------------------------------------
OPTIONS:              [Rocket::menu::help]
  APIs:
    API_ANONFILE  : 1
    API_BAYFILES  : 2
    API_FILE_IO   : 3

Execution format:
  (./)rocket(.exe) [OPTION] [path-to-file]
  Examples:
    (./)rocket(.exe) -h(elp)
      : show help
    (./)rocket(.exe) 1 path-to-file
      : upload file to API:1 (ANONFILE)
------------------------------------------

)";

int main(int argc, const char* argv[]) {
	// begin param parsing - std::string has operator==() and operator!=() defined for comparison, so, gonna be lazy.
	try {
		if ((std::string)argv[1] == "-h" || (std::string)argv[1] == "-help") {
			std::cout << help;
			exit(0);
		}
		else if (argc < 3) {
			std::cout << "Too few arguments! Check if you supplied an API or file path!" << std::endl;
			exit(1);
		}
		else if (argc > 3) {
			std::cout << "Too many arguments!" << std::endl;
			exit(2);
		}
		else if (std::stoi(argv[1]) > 3 || std::stoi(argv[1]) < 1) {
			std::cout << "Invalid API selected!" << std::endl;
			exit(3);
		}
	} catch (std::invalid_argument &e) { // catches if API(argv[1]) is non-numerical
		std::cout << "Invalid API value entered!" << std::endl;
		exit(5);
	}

	try {
		libupload lib(argv[2]);
		libupload::response res = lib.sendFile((api_identifiers)((unsigned short)std::stoi(argv[1])));
		if (res.status) {
			std::cout << "Upload successful: " << res.URL << std::endl;
		}
		else {
			std::cout << "Upload failed!\n" << res.full_response << std::endl;
		}
	} catch (luException &e) {
		std::cout << e.what() << std::endl;
		exit(4);
	}
}