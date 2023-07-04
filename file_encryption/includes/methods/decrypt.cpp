void decryptFile(std::string filePath) {
	std::fstream file, tempFile;
	std::string tempFilePath = "text.txt";

	file.open(filePath, std::ios::in);
	tempFile.open(tempFilePath, std::ios::out);

	char byte;
	while (file >> std::noskipws >> byte) {
		byte -= 1;
		tempFile << byte;
	}

	file.close();
	tempFile.close();

	// Now write the contents of tempFile to file

	file.open(filePath, std::ios::out);
	tempFile.open(tempFilePath, std::ios::in);

	while (tempFile >> std::noskipws >> byte) {
		file << byte;
	}

	file.close();
	tempFile.close();

	remove(tempFilePath.c_str());
}

void decryptDirectory(std::string directoryPath) {
	DIR* directory;
	struct dirent* entry;
	struct stat status;
	std::string path;

	if ((directory = opendir(directoryPath.c_str())) != NULL) {
		while ((entry = readdir(directory)) != NULL) {
			// strcmp (string compare) returns 0 if strings aren't equal
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				path = directoryPath + "\\" + entry->d_name;
				// stat gets file information and is storing it in status variable
				stat(path.c_str(), &status);
				if (S_ISDIR(status.st_mode)) {
					decryptDirectory(path);
				}
				else {
					decryptFile(path);
				}
			}
		}
	}
}