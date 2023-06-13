#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

// This function will encry[t the file
void encryptFile(std::string filePath) {
	// 'file' is the file that will be encrypted
	// 'tempFile' is a tempory file which will save encrypted data of file
	std::fstream file, tempFile;
	std::string tempFilePath = "temp.txt";

	// Open file streams;
	// Open file to read, temp file to write
	file.open(filePath, std::ios::in);
	tempFile.open(tempFilePath, std::ios::out);

	// Read byte by byte through file
	char byte;
	while (file >> std::noskipws >> byte) {
		// Encrypt byte by adding 1 to it
		byte += 1;
		// Save this byte to temp file
		tempFile << byte;
	}

	// Close file streams
	file.close();
	tempFile.close();

	// Open file streams
	// This time open file to write and temp file to read
	file.open(filePath, std::ios::out);
	tempFile.open(tempFilePath, std::ios::in);

	// Read through temp file byte by byte
	while (tempFile >> std::noskipws >> byte) {
		// Save this byte into file
		file << byte;
	}

	// Close file streams
	file.close();
	tempFile.close();

	// Delete temp file
	remove(tempFilePath.c_str());

}

// This function will read through all directories and files in a directory
// If it find a file, it will encrypt that file
// If it finds a directory, it will read through that directory
void encryptDirectory(std::string directoryPath) {
	DIR* directory;
	struct dirent* entry;
	struct stat status;
	std::string path;

	// Open the directory
	if ((directory = opendir(directoryPath.c_str())) != NULL) {
		// Open directory successfully
		// Read through directory
		while ((entry = readdir(directory)) != NULL) {
			// Check if ths entry (file or directory) is current directory (".") or parent directory ("..")
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				// Get full entry path
				path = directoryPath + "\\" + entry->d_name;
				// Check if this entry is a directory or file
				stat(path.c_str(), &status);
				if (S_ISDIR(status.st_mode)) {
					// This is a directory
					// We will read through it
					encryptDirectory(path);
				}
				else {
					// This is a file
					// We will encrypt it
					encryptFile(path);
				}
			}
		}
	}
}

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

int main() {
	// Encrypt directory
	// decryptDirectory("E:\\C++\\file_encryption\\TEST_FOLDER");

	// TO DO specify flag to run function and directory path

	return 0;
}


