/**
	PGMFS (Program Memory FileSystem)

	Library for handling files stored in the program space as they were in a filesystem.

	@author noti (https://github.com/notisrac)
	@version 1.1 03/01/16

	https://github.com/notisrac/PGMFS
*/

#include "Arduino.h"
#include "PGMFS.h"

PGMFS::PGMFS(unsigned char maxSize)
{
	// init the file list array with the new size
	fileList = new PGMFile[maxSize]();
	fileListMaxSize = maxSize;
	fileListFillSize = 0;
}

PGMFS::~PGMFS()
{
	// just in case, destroy the mem alloced stuff
	delete[] fileList;
}

int PGMFS::addFile(const char * fileName, unsigned int size, PGM_P location)
{
	return addFile(fileName, size, location, FileType::UNKNOWN, false);
}

int PGMFS::addFile(const char * fileName, unsigned int size, PGM_P location, FileType fileType)
{
	return addFile(fileName, size, location, fileType, false);
}

int PGMFS::addFile(const char * fileName, unsigned int size, PGM_P location, FileType fileType, bool compressed)
{
    if(fileListFillSize < fileListMaxSize) // cannot add more files than the size of the array
    {
		// create a new file object and add it to the list
        PGMFile newFile;
        newFile.fileName = fileName;
        newFile.size = size;
        newFile.type = fileType;
        newFile.location = location;
        newFile.compressed = compressed;
        fileList[fileListFillSize] = newFile;
        fileListFillSize++;
        return fileListFillSize - 1;
    }
    else
    {
        return -1;
    }
}

PGMFile * PGMFS::findFile(const char * fileName)
{
    for(unsigned char i = 0; i < fileListFillSize; i++)
    {
        if (0 == strcmp(fileName, fileList[i].fileName))
        {
            return &fileList[i];
        }
    }
    return 0;
}

PGMFile * PGMFS::findFile(unsigned char fileId)
{
    if(fileId >= fileListMaxSize)
    {
        return 0;
    }
    return &fileList[fileId];
}

unsigned int PGMFS::copyFile(char * fileName, byte * dest, unsigned int startPos, unsigned int chunkSize)
{
    PGMFile * sourceFile = findFile(fileName);
    return copyFile(sourceFile, dest, startPos, chunkSize);
}

unsigned int PGMFS::copyFile(unsigned char fileId, byte * dest, unsigned int startPos, unsigned int chunkSize)
{
    PGMFile * sourceFile = findFile(fileId);
    return copyFile(sourceFile, dest, startPos, chunkSize);
}

unsigned int PGMFS::copyFile(PGMFile * sourceFile, byte * dest, unsigned int startPos, unsigned int chunkSize)
{
    if(0 != sourceFile)
    {
        if((startPos + chunkSize) >= sourceFile->size)
        {
            chunkSize = sourceFile->size - startPos;
        }
        //Serial.print((unsigned int)&sourceFile->location + startPos, HEX); // debug
        // copy from the progmem to the sram
        memcpy_P(dest, (sourceFile->location) + startPos, chunkSize);

        return chunkSize;
    }

    return 0;
}
