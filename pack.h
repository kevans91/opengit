#ifndef PACK_H
#define PACK_H

#include <stdint.h>

/*
Header source Documentation/technical/multi-pack-index.txt
*/

/*
    GNU git has at least 2 things called "index" in Git.
    These are for files located in .git/objects/pack/[*].idx
*/

// From Documentation/technical/pack-format.txt
#define OBJ_COMMIT		1
#define OBJ_TREE		2
#define OBJ_BLOB		3
#define OBJ_TAG		4
#define OBJ_OFS_DELTA	6
#define OBJ_REF_DELTA	7

// idx file headers
struct offset {
	unsigned int addr;
};

struct checksum {
	unsigned int val;
};

struct entry {
	unsigned char sha[20];
};

struct fan {
	int count[256];
};

// pack file headers
struct objectinfohdr {
	uint8_t	size:4;
	uint8_t	type:3;
	uint8_t	more:1;
	uint8_t	unused[56];
} __packed;

struct objectinfo {
	int offset; // The object header from the file's start

	unsigned long size; // Size of the object content
	unsigned long used; // Bytes the header consumes
};

// Shared by both idx and pack files
struct packhdr {
	uint8_t		sig[4];
};

int pack_find_sha_offset(unsigned char *sha, unsigned char *idxmap);
void pack_uncompress_object(int packfd);
int pack_get_packfile_offset(char *sha_str, char *filename);
void pack_parse_header(int packfd);
void pack_object_header(int packfd, int offset, struct objectinfo *objectinfo);

#endif
