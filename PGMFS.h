/**
	PGMFS (Program Memory FileSystem)

	Library for handling files stored in the program space as they were in a filesystem.

	@author noti (https://github.com/notisrac)
	@version 1.1 03/01/16

	https://github.com/notisrac/PGMFS
*/


#ifndef PGMFS_H
#define PGMFS_H

#include "Arduino.h"
#include "FileType.h"
#include "PGMFile.h"

/**
	This class handles a bunch of files stored in the program memory as they were in a filesystem.
	Or at least it pretends to :)
*/
class PGMFS
{
public:
	/**
		The list of files in the filesystem
	*/
	PGMFile *fileList;
	/**
		Initializes a new instance of the file system with the size specified in the param

		@param maxSize The max number of items the file list can store
	*/
	PGMFS(unsigned char maxSize);
	~PGMFS();
	/**
		Adds a file to the file system

		@param fileName Textual representation of the name of the file
		@param size Size of the file in bytes (size of the array)
		@param location Location of the array in the program memory
		@param fileType Represents the type of the file. Can be any integer, but you can choose one from the {@link #FileType FileType} enum
		@param compressed Indicates whether the file is compressed, or not.
		@returns The id of the file, or -1 if an error occured
	*/
	int addFile(const char * fileName, unsigned int size, PGM_P location, FileType fileType, bool compressed);
	/**
		Adds a file to the file system, with compressed set to false

		@param fileName Textual representation of the name of the file
		@param size Size of the file in bytes (size of the array)
		@param location Location of the array in the program memory
		@param fileType Represents the type of the file. Can be any integer, but you can choose one from the {@link #FileType FileType} enum
		@returns The id of the file, or -1 if an error occured
	*/
	int addFile(const char * fileName, unsigned int size, PGM_P location, FileType fileType);
	/**
		Adds a file to the file system, with compressed set to false, and fileType set to UNKNOWN

		@param fileName Textual representation of the name of the file
		@param size Size of the file in bytes (size of the array)
		@param location Location of the array in the program memory
		@returns The id of the file, or -1 if an error occured
	*/
	int addFile(const char * fileName, unsigned int size, PGM_P location);
	/**
	  Finds a file in the file system by its name

	  @param fileName Name of the file
	  @returns The {@link #PGMFile PGMFile} type object representing the file
	*/
	PGMFile * findFile(const char * fileName);
	/**
	  Finds a file in the file system by its id
	  (The Id is returned by the addFile method.)

	  @param fileId Id of the file
	  @returns The {@link #PGMFile PGMFile} type object representing the file
	*/
	PGMFile * findFile(unsigned char fileId);
	/**
		Finds a file in the file system by its name, and copies (a part of) it into the destination array.

		@param fileName Name of the file
		@param dest Pointer to the destination array
		@param startPos Start copying the file from this byte
		@param chunkSize Copy this many bytes from the file
		@returns The number of bytes copied
	*/
	unsigned int copyFile(char * fileName, byte * dest, unsigned int startPos, unsigned int chunkSize);
	/**
		Copies a (part of the) file into the destination array.

		@param sourceFile Source file Id
		@param dest Pointer to the destination array
		@param startPos Start copying the file from this byte
		@param chunkSize Copy this many bytes from the file
		@returns The number of bytes copied
	*/
	unsigned int copyFile(unsigned char fileId, byte * dest, unsigned int startPos, unsigned int chunkSize);
	/**
		Copies a (part of the) file into the destination array.

		@param sourceFile Source file
		@param dest Pointer to the destination array
		@param startPos Start copying the file from this byte
		@param chunkSize Copy this many bytes from the file
		@returns The number of bytes copied
	*/
	unsigned int copyFile(PGMFile * sourceFile, byte * dest, unsigned int startPos, unsigned int chunkSize);
private:
	/**
		Max number of files
	*/
	unsigned char fileListMaxSize;
	/**
		Actual number of files
	*/
	unsigned char fileListFillSize; // number of items in the array
};

//extern PGMFS PROGMEMFileSystem;

#endif