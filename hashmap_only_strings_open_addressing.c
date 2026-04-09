#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct KeyValuePair {
    char key[100];
    char value[100];
    struct KeyValuePair *next;
};

int capacity = 100;
struct KeyValuePair bucket[100] = {0}; 


int hash(char string[]) {
    int hash = 5381;
    for( int i = 0 ; i < strlen(string); i++) {
        hash = hash * 33 + string[i];
    }
    return hash % capacity;
}

int check_capacity() {

    int filled = 0;

    for (int i = 0 ; i < sizeof(bucket) / sizeof(bucket[0]); i++ ) {

        if (bucket[i].key[0] != '\0') {
            filled++;
        }

    }

    printf("filled: %d \n", filled);

    return filled;

}

void insert(char key[], char value[]) {
    printf("key=%s value=%s\n", key, value);

    int index = hash(key);

    if (bucket[index].key[0] == '\0') {
        printf("%s \n", "nothing");

        // Copy strings safely
        strncpy(bucket[index].key, key, 99);
        bucket[index].key[99] = '\0';  // ensure null terminator
        
        strncpy(bucket[index].value, value, 99);
        bucket[index].value[99] = '\0';  // ensure null terminator
        
        bucket[index].next = NULL;
    } else {
        printf("%s \n", "something");

        struct KeyValuePair *curr = &bucket[index]; 

        while (curr -> next != NULL) {
            curr = curr -> next;
        }

        struct KeyValuePair *newNode = malloc(sizeof(struct KeyValuePair)); 

        // Copy strings safely
        strncpy(newNode -> key, key, 99);
        newNode -> key[99] = '\0';  // ensure null terminator
        
        strncpy(newNode -> value, value, 99);
        newNode -> value[99] = '\0';  // ensure null terminator
        
        newNode -> next = NULL;

        curr -> next = newNode;
    }

}

void get(char key[]) {

    int index = hash(key);

    if (bucket[index].key[0] == '\0') {
        printf("%s \n", "nothing found");
    } else {
        struct KeyValuePair *curr = &bucket[index];

        while (curr != NULL) {
            if (strcmp(curr -> key, key) == 0) {
                printf("%s \n", curr -> value);
                return;
            }

            curr = curr -> next;
        }
    }

    
}

int delete(char key[]) {

    int index = hash(key);

    if (bucket[index].key[0] == '\0') {
        printf("%s \n", "key no found");
        return -1;
    } else {
        struct KeyValuePair *curr = &bucket[index];
        struct KeyValuePair *prev = curr;

        int counter = 0;

        while (curr != NULL) {
            if (strcmp(curr -> key, key) == 0) {
                printf("%s \n", "found key");

                if (counter == 0) {

                    if (curr -> next != NULL) {
                        bucket[index] = *(curr -> next);
                    } else {
                        // Copy strings safely
                        strncpy(bucket[index].key, "", 99);
                        bucket[index].key[99] = '\0';  // ensure null terminator
                        
                        strncpy(bucket[index].value, "", 99);
                        bucket[index].value[99] = '\0';  // ensure null terminator
                        
                        bucket[index].next = NULL ;
                    }
                    free(curr)
                } else {
                    prev -> next = curr -> next;
                    free(curr) 
                }
                return 1;
            }

            prev = curr;
            curr = curr -> next;
            counter++;

        }
    }

    return -1;

}


int main() {

    insert("215", "Bikraman Karmakar");
    get("215");
    check_capacity();

    delete("215");
    check_capacity();

    return 0;
}



