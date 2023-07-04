#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>

#include "includes/methods/encrypt.cpp"
#include "includes/methods/decrypt.cpp"


int main(int argc, char *argv[]) {	
	for (int i = 0; i < argc; ++i) {

		if (std::string(argv[i]) == "-encrypt") {
			std::cout << "Your files are being encrypted!";

			std::string value = std::string(argv[i + 1]);
			encryptDirectory(value);

		}
		else if (std::string(argv[i]) == "-decrypt") {
			std::cout << "Your files are being decrypted!";

			std::string value = std::string(argv[i + 1]);
			decryptDirectory(value);

		}
	}
	return 0;
}


