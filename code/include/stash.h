#ifndef STASH_H
#define STASH_H

void Stash_Init(void);
void Stash_InitOnce(void);

int Stash_SendData(void *source, int transferQwords, int reserveQwords, char *comment);

int Stash_Upload(void *source, unsigned int slot, int offset, int qwords);

int Stash_GetSize(unsigned int slot);

int Stash_Copy(void *destination, unsigned int slot, int offset, int qwords, int mode);

#endif
