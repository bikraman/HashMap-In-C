#include <stdio.h>
#include <string.h>

struct KeyValuePair {
    char key[100];
    char value[100];
    struct KeyValuePair *next;
};

int capacity = 100;
struct KeyValuePair bucket[100]; 




int hash(char string[]) {
    int hash = 5381;
    for( int i = 0 ; i < strlen(string); i++) {
        hash = hash * 33 + string[i];
    }
    return hash % capacity;
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


    }

    printf("%s", bucket[2].key);


}

void get(char key[]) {

    int index = hash(key);

    if (bucket[index].key[0] == '\0') {
        printf("%s \n", "nothing found");
    } else {
        printf("%s \n", bucket[index].value);
    }
}


int main() {
    insert("215", "Bikraman Karmakar");
    get("215");
    return 0;
}



