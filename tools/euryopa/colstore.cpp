#include "euryopa.h"

#include <cstring>

static ColDef collist[NUMCOLS];
static int numCols;

static int
FindColSlot(const char *name)
{
	int i;
	for(i = 0; i < numCols; i++){
		if(rw::strncmp_ci(collist[i].name, name, MODELNAMELEN) == 0)
			return i;
	}
	return -1;
}

ColDef*
GetColDef(int i)
{
	if(i < 0 || i >= numCols){
//		log("warning: invalid col slot %d\n", i);
		return nil;
	}
	return &collist[i];
}

int
AddColSlot(const char *name)
{
	int i;
	i = FindColSlot(name);
	if(i >= 0)
		return i;
	i = numCols++;
	strncpy(collist[i].name, name, MODELNAMELEN);
	collist[i].imageIndex = -1;
	return i;
}


void
LoadAllCollisions(void)
{
	ColDef *col;
	int i;
	for(i = 0; i < numCols; i++){
		col = GetColDef(i);
		if(col->imageIndex >= 0)
			LoadCol(i);
	}
}

void
LoadCol(int slot)
{
	uint8 *buffer;
	int size;
	int offset;
	ColFileHeader *header;
	int version;
	ObjectDef *obj;
	ColDef *col = GetColDef(slot);

	if(col->imageIndex < 0){
		log("warning: no streaming info for col %s\n", col->name);
		return;
	}

	buffer = ReadFileFromImage(col->imageIndex, &size);
	offset = 0;
	while(offset < size){
		header = (ColFileHeader*)(buffer+offset);
		version = 0;
		switch(header->fourcc){
		case 0x4C4C4F43:	// COLL
			version = 1;
			break;
		case 0x324C4F43:	// COL2
			version = 2;
			break;
		case 0x334C4F43:	// COL3
			version = 3;
			break;
		default:
			return;
		}
		offset += sizeof(ColFileHeader);

		obj = GetObjectDef(header->name, nil);
		if(obj){
//if(strstr(header->name, "seabed"))
//	printf("loading COL %s\n", header->name);
			CColModel *col = new CColModel;
			obj->m_colModel = col;
			switch(version){
			case 1: ReadColModel(col, buffer+offset, header->modelsize-24); break;
			case 2: ReadColModelVer2(col, buffer+offset, header->modelsize-24); break;
			case 3: ReadColModelVer3(col, buffer+offset, header->modelsize-24); break;
			default:
				printf("unknown COL version %d\n", version);
				obj->m_colModel = nil;
			}
		}else
			printf("Couldn't find object %s for collision\n", header->name);
		offset += header->modelsize-24;
	}
}
