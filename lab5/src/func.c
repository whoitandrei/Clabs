#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#define BUFFER_SIZE 66000

void free_tree(Node* root) {
	if (root->link[0] != NULL) {
		free_tree(root->link[0]);
		free_tree(root->link[1]);
	}

	free(root);

}

void free_codetable(unsigned char** code_table) {
	for (int i = 0; i < 256; ++i) {
		if (code_table[i] != NULL)
			free(code_table[i]);
	}

}


static void freq_count(Data* in, size_t* freq) {
	do {
		for (size_t i = in->pos; i < in->size; i++) {
			freq[in->buffer[i]]++;
		}
		in->pos = 0;

	} while ((in->size = fread(in->buffer, 1, BUFFER_SIZE, in->file)) > 0);
	
}


static int cmp(const void* arg1, const void* arg2) {
	return (int)(*(Node**)arg2)->freq - (int)(*(Node**)arg1)->freq;
}

static Node* mk_tree(size_t* freq, Node** slice) {
	slice[0] = NULL;
	size_t n = 0;
	for (int i = 0; i < 256; ++i) {
		if (freq[i] > 0) {
			Node* node = (Node*)malloc(sizeof(Node));
			node->link[0] = NULL;
			node->link[1] = NULL;
			node->freq = freq[i];
			node->sym = (unsigned char)i;
			slice[n++] = node;
		}
	}


	while (n > 1) {
		qsort(slice, n, sizeof(Node*), cmp);

		Node* node = (Node*)malloc(sizeof(Node));
		if (!node) {
			free(node);
			return NULL;
		}
		node->link[0] = slice[n - 2];
		node->link[1] = slice[n - 1];
		node->freq = slice[n - 2]->freq + slice[n - 1]->freq;
		node->sym = 0;
		slice[n - 2] = node;

		n--;
	}

	return slice[0];
}


static void fill_table(unsigned char** code_table, Node* root, unsigned char* path, size_t depth) {
	if (root->link[0] != NULL) {
		path[depth] = '0';
		fill_table(code_table, root->link[0], path, depth + 1);
		path[depth] = '1';
		fill_table(code_table, root->link[1], path, depth + 1);
	}
	else {
		path[depth] = '\0';
		code_table[root->sym] = (unsigned char*)memcpy(malloc(depth + 1), path, depth + 1);
		if (!code_table[root->sym]) {
			free(code_table[root->sym]);
			return;
		}
	}
}



void writesym(Data* out, unsigned char sym) {

	if (out->bitpos == 0) {
		(out->buffer[out->pos]) = sym;
		(out->pos)++;
		if (out->pos >= BUFFER_SIZE) {
			fwrite(out->buffer, 1, out->pos, out->file);
			memset(out->buffer, 0, BUFFER_SIZE);
			out->pos = 0;
		}
	}
	else {
		(out->buffer[out->pos]) |= sym >> (out->bitpos);
		(out->pos)++;
		if (out->pos >= BUFFER_SIZE) {
			fwrite(out->buffer, 1, out->pos, out->file);
			memset(out->buffer, 0, BUFFER_SIZE);
			out->pos = 0;
		}
		(out->buffer[out->pos]) |= sym << (8 - (out->bitpos));
	}
}


void write_tree(Node* root, Data* out) {
	if (root->link[0] != NULL) {

		(out->buffer[out->pos]) |= 128 >> out->bitpos;
		(out->bitpos)++;
		if (out->bitpos >= 8) {
			out->bitpos = 0;
			(out->pos)++;
			if (out->pos >= BUFFER_SIZE) {
				fwrite(out->buffer, 1, out->pos, out->file);
				memset(out->buffer, 0, BUFFER_SIZE);
				out->pos = 0;
			}
		}
		write_tree(root->link[0], out);
		write_tree(root->link[1], out);
	}
	else {
		++(out->bitpos);


		if (out->bitpos >= 8) {
			out->bitpos = 0;
			(out->pos)++;
			if (out->pos >= BUFFER_SIZE) {
				fwrite(out->buffer, 1, out->pos, out->file);
				memset(out->buffer, 0, BUFFER_SIZE);
				out->pos = 0;
			}
		}


		writesym(out, root->sym);
	}
}

static inline int is_not_zero(int a) { 
	return a != 0; 
}

void encode_huffman(Data* in, Data* out, unsigned char** code_table) {
	unsigned int bitpos = out->bitpos;

	do {
		for (size_t i = in->pos; i < in->size; i++) {
			int k = 0;
			int bit;
			while ((bit = code_table[in->buffer[i]][k]) != 0)
			{

				if (bitpos > 7) {
					bitpos = 0;
					++out->pos;
					if (out->pos >= BUFFER_SIZE) {
						fwrite(out->buffer, 1, out->pos, out->file);
						memset(out->buffer, 0, BUFFER_SIZE);
						out->pos = 0;
					}
					out->buffer[out->pos] = 0;
				}

				if ('1' == bit)
					out->buffer[out->pos] |= 128u >> bitpos;
				bitpos++;
				++k;
			}
		}
		in->pos = 0;
	} while ((in->size = fread(in->buffer, 1, BUFFER_SIZE, in->file)) > 0);

	fwrite(out->buffer, sizeof(unsigned char), out->pos + is_not_zero(bitpos), out->file);
}



int encode(Data* in) {

	Data out = {
		.file = fopen("out.txt", "wb"),
		.bitpos = 0,
		.pos = 4,
		.buffer = {0},
	};

	if (out.file == NULL) {
		printf("[file error]");
		return 0;
	}

	size_t freq[256] = { 0 };
	size_t skip = in->pos;
	
	freq_count(in, freq); 
	in->pos = skip;

	Node* slice[256] = { NULL };
	Node* tree = mk_tree(freq, slice);

	if (tree == NULL) {
		fclose(out.file);
		return 0;
	}

	unsigned char* code_table[256] = { 0 };
	unsigned char path[256] = { 0 };
	fill_table(code_table, tree, path, 0);

	skip = in->pos;
	size_t input_size = (size_t)ftell(in->file) - skip;
	fseek(in->file, (long)skip, SEEK_SET);

	out.buffer[0] = (unsigned char)(input_size >> 24);
	out.buffer[1] = (unsigned char)(input_size >> 16);
	out.buffer[2] = (unsigned char)(input_size >> 8);
	out.buffer[3] = (unsigned char)(input_size);


	write_tree(tree, &out);
	encode_huffman(in, &out, code_table);

	fclose(out.file);
	free_codetable(code_table);
	free_tree(tree);

	return 0;
}


//DECODING

int getbit(Data* in) {
	char byte = in->buffer[in->pos];
	char bit = ((byte << in->bitpos) & 128) >> 7;
	(in->bitpos)++;

	if ((in->bitpos) >= 8) {
		in->bitpos = 0;
		(in->pos)++;
		if (in->pos >= in->size)
		{
			in->size = fread(in->buffer, 1, BUFFER_SIZE - 1, in->file);
			in->pos = 0;
		}
	}
	return bit;
}


unsigned char getbyte(Data* in)
{
	unsigned char sym = 0;
	unsigned char byte = in->buffer[in->pos];
	sym = byte << in->bitpos;

	(in->pos)++;
	if (in->pos >= in->size)
	{
		in->size = fread(in->buffer, 1, BUFFER_SIZE - 1, in->file);
		in->pos = 0;
	}

	byte = in->buffer[in->pos];
	sym |= byte >> (8 - in->bitpos);

	return sym;

}

Node* restore_tree(Data* in) {
	Node* nd = malloc(sizeof(Node));
	int bit = getbit(in);
	if (!bit) {
		nd->link[0] = nd->link[1] = NULL;
		nd->sym = getbyte(in);
	}
	else {
		nd->link[0] = restore_tree(in);
		nd->link[1] = restore_tree(in);
	}

	return nd;
}


void decode_huffman(Data* in, Data* out, Node* tree, size_t out_count) {

	size_t i = 0;
	while (i < out_count) {
		Node* cur = tree;
		while (cur->link[0] != NULL) {
			cur = cur->link[getbit(in)];
		}

		out->buffer[out->pos++] = cur->sym;
		if (out->pos >= BUFFER_SIZE) {
			fwrite(out->buffer, 1, out->pos, out->file);
			out->pos = 0;
		}
		i++;
	}

	fwrite(out->buffer, sizeof(char), out->pos, out->file);
}



int decode(Data* in) {

	Data out = {
		.bitpos = 0,
		.pos = 0,
		.file = fopen("out.txt", "wb"),
	};

	if (out.file == NULL) {
		fclose(out.file);
		printf("out.txt open file error");
		return 0;
	}


	size_t size = 0;
	unsigned char var = 0;
	for (int i = 0; i < 4; i++) {
		size <<= 8;
		if (!(fread(&var, 1, 1, in->file))) {
			fclose(out.file);
			return 0;
		}
		size += var;
	}

	if ((in->size = fread(in->buffer, 1, BUFFER_SIZE - 1, in->file)) == 0) {
		fclose(out.file);
		return 0;

	}

	Node* tree = restore_tree(in);
	decode_huffman(in, &out, tree, size);
	free_tree(tree);

	fclose(out.file);
	return 0;
}




