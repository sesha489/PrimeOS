#include"FAT16.h"

void DisplayCache(void){
	uint16_t row;
	uint16_t col;
	row = col = 0;
	char a[3];

	for(uint16_t inc=0; inc<512; inc++){
		if(inc%22==0){
			col = 0;
			if(inc!=0)
				row++;
		}
		sprintf(a, "%02X", ReadData[inc]);
		WriteText5x8(((col*14)+5), (row*10), a, Black);
		col++;
	}
}

void FAT16_INIT(void){
	char a[9];

	addressPointer = partitionEntry = 0;
	SectorCounter = 0;
	FAT1Entry = FAT2Entry = 0;
	RootDirEntry = DataEntry = 0;

	Paint_Colour(White);
	WriteText5x8(10, 10, "SD Card initialized", Black);
	Read_SDC(ReadData, 0, 512);
	_msDelay(3000);
	Paint_Colour(White);
	DisplayCache();

	addressPointer += (0x000000FF & ReadData[454]);
	addressPointer += ((0x000000FF & ReadData[455])<<8);
	addressPointer += (((0x000000FF & ReadData[456])<<8)<<8);
	addressPointer += ((((0x000000FF & ReadData[457])<<8)<<8)<<8);
	addressPointer = addressPointer * 512;
	partitionEntry = addressPointer;

	_msDelay(3000);
	Paint_Colour(White);
	Read_SDC(ReadData, partitionEntry, 512);
	Paint_Colour(White);
	DisplayCache();

	mBR.BytesPerSector += (0x000000FF & ReadData[11]);
	mBR.BytesPerSector += ((0x000000FF & ReadData[12])<<8);
	mBR.SectorsPerCluster += (0x000000FF & ReadData[13]);
	mBR.NoOfReservedSectors += (0x000000FF & ReadData[14]);
	mBR.NoOfReservedSectors += ((0x000000FF & ReadData[15])<<8);
	mBR.NoOfFATcopies += (0x000000FF & ReadData[16]);
	mBR.MaxRootEntries += (0x000000FF & ReadData[17]);
	mBR.MaxRootEntries += ((0x000000FF & ReadData[18])<<8);
	mBR.SectorsPerFAT += (0x000000FF & ReadData[22]);
	mBR.SectorsPerFAT += ((0x000000FF & ReadData[23])<<8);
	for(int i=0; i<11; i++)
		mBR.VolumeName[i] = ReadData[(43+i)];
	for(int i=0; i<8; i++)
		mBR.FATSystem[i] = ReadData[(54+i)];
	FAT1Entry = partitionEntry + ((uint32_t)mBR.NoOfReservedSectors * (uint32_t)mBR.BytesPerSector);
	FAT2Entry = FAT1Entry + ((uint32_t)mBR.SectorsPerFAT * (uint32_t)mBR.BytesPerSector);
	RootDirEntry = FAT2Entry + ((uint32_t)mBR.SectorsPerFAT * (uint32_t)mBR.BytesPerSector);
	DataEntry = RootDirEntry + ((uint32_t)mBR.MaxRootEntries * 32);

	_msDelay(3000);
	Paint_Colour(White);
	WriteText5x8(5, 10, "File system info", Black);
	WriteText5x8(5, 25, "FAT16 file system found and initiated", Black);
	sprintf(a, "%lu", addressPointer);
	WriteText5x8(5, 35, "Address Pointer        :", Black);
	WriteText5x8(150,35, a, Black);
	addressPointer = RootDirEntry;

	sprintf(a, "%lu", partitionEntry);
	WriteText5x8(5, 45, "Partition Entry        :", Black);
	WriteText5x8(150,45, a, Black);

	sprintf(a, "%lu", FAT1Entry);
	WriteText5x8(5, 55, "FAT1 Entry             :", Black);
	WriteText5x8(150,55, a, Black);

	sprintf(a, "%lu", FAT2Entry);
	WriteText5x8(5, 65, "FAT2 Entry             :", Black);
	WriteText5x8(150,65, a, Black);

	sprintf(a, "%lu", RootDirEntry);
	WriteText5x8(5, 75, "Root Directory Entry   :", Black);
	WriteText5x8(150,75, a, Black);

	sprintf(a, "%lu", DataEntry);
	WriteText5x8(5, 85, "Data Entry             :", Black);
	WriteText5x8(150,85, a, Black);

	sprintf(a, "%lu", addressPointer);
	WriteText5x8(5, 95, "Address Pointer        :", Black);
	WriteText5x8(150,95, a, Black);

	sprintf(a, "%08X", mBR.BytesPerSector);
	WriteText5x8(5,115, "Bytes Per Sector       :", Black);
	WriteText5x8(150,115, a, Black);

	sprintf(a, "%08X", mBR.SectorsPerCluster);
	WriteText5x8(5,125, "Sectors Per Cluster    :", Black);
	WriteText5x8(150,125, a, Black);

	sprintf(a, "%08X", mBR.NoOfReservedSectors);
	WriteText5x8(5,135, "No.of Reserved Sectors :", Black);
	WriteText5x8(150,135, a, Black);

	sprintf(a, "%08X", mBR.NoOfFATcopies);
	WriteText5x8(5,145, "No.of FAT copies       :", Black);
	WriteText5x8(150,145, a, Black);

	sprintf(a, "%08X", mBR.MaxRootEntries);
	WriteText5x8(5,155, "Maximum Root Entries   :", Black);
	WriteText5x8(150,155, a, Black);

	sprintf(a, "%08X", mBR.SectorsPerFAT);
	WriteText5x8(5,165, "Sectors Per FAT        :", Black);
	WriteText5x8(150,165, a, Black);

	//for(int i=0;i<11;i++)
	WriteText5x8(5,175, mBR.VolumeName, Black);

	//for(int i=0;i<8;i++)
	WriteText5x8(5,185, mBR.FATSystem, Black);
}
