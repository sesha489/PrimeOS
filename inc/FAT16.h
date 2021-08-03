#ifndef FAT16_H_
#define FAT16_H_

#include"SDC.h"

#ifdef __cplusplus
 extern "C" {
#endif

uint8_t ReadData[512];
uint16_t SectorCounter;
uint32_t addressPointer, partitionEntry;
uint32_t FAT1Entry, FAT2Entry;
uint32_t RootDirEntry, DataEntry;

struct{
	uint16_t BytesPerSector;
	uint8_t SectorsPerCluster;
	uint16_t NoOfReservedSectors;
	uint8_t NoOfFATcopies;
	uint16_t MaxRootEntries;
	uint16_t SectorsPerFAT;
	char VolumeName[12];
	char FATSystem[9];
}mBR;

struct{
	char fileName[9];
	char fileExtn[4];
	uint8_t fileAttrib;
	uint16_t StartingCluster;
	uint16_t EndingCluster;
}fileInfo;

void DisplayCache(void);
void FAT16_INIT(void);

#ifdef __cplusplus
}
#endif

#endif /* FAT16_H_ */
