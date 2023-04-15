#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType *next;
};

struct HashType {
    struct RecordType* table;
};

int hash(int x, int tableSize) {
    return x % tableSize;
}

int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz) {
    
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize) {
        
    int hashIndex = hash(record->id, tableSize);
    
    if (hashTable[hashIndex].table == NULL){
        hashTable[hashIndex].table = record;
    }
    else {
        struct RecordType *temp = hashTable[hashIndex].table;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = record;
    }
}

void displayRecordsInHash(struct HashType *hashTable, int hashSz) {

    printf("Hash Records:\n");
    
    for (int i = 0; i < hashSz; ++i) {
        printf("\tIndex %d -> ", i);
        struct RecordType *temp = hashTable[i].table;
        while(temp != NULL){
            printf("%d, %c, %d -> ", temp->id, temp->name, temp->order);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    int recordSz = 0;
    int HashTableSize = 11;
    
    struct RecordType *pRecords;
    struct HashType *pHashArray = calloc(HashTableSize, sizeof(struct HashType));

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    
    for (int i = 0; i < recordSz; i++)
        insertRecord(pHashArray, &pRecords[i], HashTableSize);
    displayRecordsInHash(pHashArray, HashTableSize);
    
    free(pRecords);
    free(pHashArray);
}
