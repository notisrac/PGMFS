/**
	PGMFile

	This structure holds a single file with all of its attributes

	@author noti (https://github.com/notisrac)
	@version 1.1 03/01/16

	https://github.com/notisrac/PGMFS
*/
typedef struct PGMFile {
	const char * fileName;
	unsigned int size;
	PGM_P location;
	FileType type;
	bool compressed;
} PGMFile;
