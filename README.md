# PGMFS - Program Memory FileSystem for Arduino

PGMFS is a lightweight [Arduino](https://www.arduino.cc/) library for handling files stored in the flash (program) memory (PROGMEM) just like they were in a regular filesystem.
(More information on PROGMEM can be found on the [Arduino reference page](https://www.arduino.cc/en/Reference/PROGMEM))
Since the PROGMEM cannot be altered at runtime, this library only implements a few features:
* Storing (=handling) files
* Finding files based on it's name or Id
* Copying file portions into arrays


### Notes
1. I'm using it for an Arduino based web server for easily looking up, and serving the requested files. You can see this on the features it implements :)
2. It uses the **new** keyword to create the file list array when you instantiate the lib, so the Arduino ide's memory consumption calculation will be off! (I know this is not the best solution, but I'm yet to a find a better one.)
3. Rigth now it does not support directories. However this might be worked around by naming the files, like they were in directories: fs.addFile("dir1/file1.txt", ...); 

## Usage

### File descriptor structure
This structure represents a single file, along with its attributes.
```c
typedef struct PGMFile {
	const char * fileName; // textual representation of the file name
	unsigned int size;     // file size in bytes - size of the array
	PGM_P location;        // PROGMEM location of the file
	FileType type;         // type of the file. this is either an int, or you can use the FileType enum too
	bool compressed;       // indicates whether the file is compressed or not 
} PGMFile;
```
*Shameless plug:* You can compress files (on your pc) and uncompress them on the Arduino device with my [LZe (LZ embedded) compressor/decompressor](https://github.com/notisrac/LZe)


### File types
Enum with the file types. But you can use any integer number instead.
```c
typedef enum FileType { HTML, XML, CSS, PNG, GIF, XSL, ICO, JS, JSON, UNKNOWN, ERROR, TXT } FileType;
```


### Adding a file to the code, that will be stored in PROGMEM
```c
// test file (one paragraph of lorem ipsum) Created with http://notisrac.github.io/FileToCArray/
extern const char fileTest[] PROGMEM; // <- note the PROGMEM variable modifier
const char fileTest[] = {
	0x4c, 0x6f, 0x72, 0x65, 0x6d, 0x20, 0x69, 0x70, 0x73, 0x75, 0x6d, 0x20, 0x64, 0x6f, 0x6c, 0x6f,
	0x72, 0x20, 0x73, 0x69, 0x74, 0x20, 0x61, 0x6d, 0x65, 0x74, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73,
	// reduced for clarity
	0x74, 0x75, 0x72, 0x70, 0x69, 0x73, 0x2e
};
```
*Shameless plug:* You can convert files into arrays with my [File To C Array Converter](http://notisrac.github.io/FileToCArray/)


### Instantiating the library
Upon instantiating the PGMFS, you need to define the max number of files, that will be stored in the FS.
```c
// number of files to store in the fs
#define FileListSize 3
// init the fs
PGMFS PROGMEMFileSystem(FileListSize);
```


### Adding files
You add files with the addFile method. Required parameters are the filename, the size, and the location.
* **fileName** Textual representation of the name of the file
* **size** Size of the file in bytes (size of the array)
* **location** Location of the array in the program memory
* **fileType** Represents the type of the file. Can be any integer, but you can choose one from the FileType enum
* **compressed** Indicates whether the file is compressed, or not.
* **Returns** The id of the file, or -1 if an error occured
```c
// add files to the fs (filename, size, location, [type], [isCompressed])
PROGMEMFileSystem.addFile("testFile1.txt", 727, fileTest1, FileType::TXT);
PROGMEMFileSystem.addFile("testFile2.gif", 456, fileTest2, FileType::GIF, false);
int testFile3Id = PROGMEMFileSystem.addFile("testFile3.foo", 364, fileTest3);
```


### Searching for files
You can search for files in the filesystem based on their name or Id. This method returns a pointer to the PGMFile object in the file list array. (Or a 0 if anything went wrong) 
```c
// look for the file by name "testFile2.gif"
PGMFile * requestedFile = PROGMEMFileSystem.findFile("testFile2.gif");
PGMFile * testFile3 = PROGMEMFileSystem.findFile(testFile3Id);
```


### Copying files
The copyFile method will copy a part of the file into the specified array, starting from the specified position.
* **sourceFile** Source file, file Id or file name
* **dest** Pointer to the destination array
* **startPos** Start copying the file from this byte
* **chunkSize** Copy this many bytes from the file
* **Returns** The number of bytes copied
```c
// copy buffer size
#define TargetBufferSize 100
// copy buffer
byte targetBuffer[TargetBufferSize];
// where to start the copying from
unsigned int startPos = 10;
// copy
unsigned int bytesCopied = PROGMEMFileSystem.copyFile(requestedFile, targetBuffer, startPos, TargetBufferSize);
```


### Example
*See the PGMFSExample.pde file in the examples folder!*
