#pragma once
#define BUFFER_SIZE 66000

typedef struct st_Node Node;
struct st_Node {
	Node* link[2];
	size_t freq;
	unsigned char sym;
};

typedef struct Data {
	FILE* file;
	unsigned char buffer[BUFFER_SIZE];
	size_t pos;
	size_t size;
	unsigned int bitpos;
} Data;

int encode(Data* in);
int decode(Data* in);




