#ifndef KEY_H
#define KEY_H

#include <stdlib.h>
#include <stdio.h>

#include "alphabet.h"
#include "ciphers.h"

typedef struct Key {
	union {
		void *buf;
		Alphabet *a;
	};
	size_t n;
} Key;

typedef struct KeyInterface {
	int (*initKey)(Key *key, char *argv);
	int (*serializeKey)(Key *key, FILE *f);
	int (*copyKey)(Key *key, Key *other);
	void (*freeKey)(Key *key);
} KeyInterface;

void freeKey(Key *key);
int serializeKeyAlphabet(Key *key, FILE *f);
int copyKey(Key *key, Key *other);
int equalKey(Key *key, Key *other);

int caesar_initKey(Key *key, char *argv);
int caesar_initFirstKey(Key *key);
int caesar_nextKey(Key *key);
int vigenere_initKey(Key *key, char *argv);
int vigenere_initFirstKey(Key *key);
int vigenere_nextKey(Key *key);

static const KeyInterface keyInterfaces[] = {
	[CipherCaesar] = {
		&caesar_initKey,
		&serializeKeyAlphabet,
		&copyKey,
		&freeKey,
	},
	[CipherVigenere] = {
		&vigenere_initKey,
		&serializeKeyAlphabet,
		&copyKey,
		&freeKey,
	},
};

#endif
