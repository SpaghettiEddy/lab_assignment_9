#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType *next;
};

// Fill out this structure
struct HashType {
    struct RecordType* table;
};

// Compute the hash function
int hash(int x, int tableSize) {
    return x % tableSize;
}

// parses input file to an integer array
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
        // Implement parse data block
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

// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize) {
    // call the hash function to get the index
    int hashIndex = hash(record->id, tableSize);
    // if the RecordType at that index is NULL
    if (hashTable[hashIndex].table == NULL) {
        hashTable->table = record;
        printf("\n%c\n", record->name);

    } else {
        struct RecordType *temp = hashTable[hashIndex].table;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = record;
        printf("\n%c\n", record->name);

    }
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz) {

    printf("Hash Records:\n");
    
    printf("\t%c\n", pHashArray->table->name);
    
    
    for (int i = 0; i < hashSz; ++i) {
        printf("\tIndex %d -> ", i);
        struct RecordType *temp = pHashArray[i].table;
        while(temp != NULL){
            printf("%d, %c, %d ->", pHashArray[i].table->id, pHashArray[i].table->name, pHashArray[i].table->order);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation
    
    int HashTableSize = 11;
    
    struct HashType *pHashArray = calloc(HashTableSize, sizeof(struct HashType));
    
    for (int i = 0; i < recordSz; i++) {
        insertRecord(pHashArray, &pRecords[i], HashTableSize);
    }
    displayRecordsInHash(pHashArray, HashTableSize);
    
    
    free(pRecords);
    
}
