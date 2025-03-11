#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10;

// Struktur untuk Chaining
typedef struct Node {
    char key[50];
    struct Node* next;
} Node;

int mid_square_hash(const char* key) {
    int hash = 0;
    while (*key) {
        hash += (*key) * (*key);
        key++;
    }
    return (hash / 10) % SIZE;
}

int division_hash(const char* key) {
    int hash = 0;
    while (*key) {
        hash += *key;
        key++;
    }
    return hash % SIZE;
}

int folding_hash(const char* key) {
    int hash = 0;
    while (*key) {
        hash += (*key) % 100;
        key++;
    }
    return hash % SIZE;
}

int digit_extraction_hash(const char* key) {
    int hash = 0;
    int length = strlen(key);
    if (length >= 2) {
        hash = (key[0] - '0') * 10 + (key[length - 1] - '0');
    } else {
        hash = key[0] - '0';
    }
    return hash % SIZE;
}

int rotation_hash(const char* key) {
    int hash = 0;
    while (*key) {
        hash = (hash << 1) ^ *key;
        key++;
    }
    return abs(hash) % SIZE;
}

void linear_probing(char table[][50], const char* key, int (*hash_function)(const char*)) {
    int index = hash_function(key);
    while (strlen(table[index]) != 0) {
        index = (index + 1) % SIZE;
    }
    strcpy(table[index], key);
}

void rehashing(char table[][50], const char* key, int (*hash_function)(const char*)) {
    int index = hash_function(key);
    int step = 7 - (index % 7);
    while (strlen(table[index]) != 0) {
        index = (index + step) % SIZE;
    }
    strcpy(table[index], key);
}

void chaining(Node* table[], const char* key, int (*hash_function)(const char*)) {
    int index = hash_function(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;
    
    if (table[index] == NULL) {
        table[index] = newNode;
    } else {
        Node* temp = table[index];
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void print_table(Node* chain_table[], char table[][50], int collision_choice) {
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        if (collision_choice == 3) { // Chaining
            Node* temp = chain_table[i];
            while (temp) {
                printf("%s -> ", temp->key);
                temp = temp->next;
            }
        } else { // Linear Probing atau Rehashing
            if (strlen(table[i]) != 0) {
                printf("%s", table[i]);
            } else {
                printf("Kosong");
            }
        }
        printf(" NULL\n");
    }
}

int main() {
    Node* chain_table[SIZE] = {NULL};
    char table[SIZE][50] = {""};
    
    int (*hash_functions[])(const char*) = {mid_square_hash, division_hash, folding_hash, digit_extraction_hash, rotation_hash};
    void (*collision_methods[])(char[][50], const char*, int (*)(const char*)) = {linear_probing, rehashing};
    
    printf("Pilih Hash Function:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    printf("Enter your Choice : ");
    int hash_choice;
    scanf("%d", &hash_choice);
    getchar();
    
    if (hash_choice < 1 || hash_choice > 5) {
        printf("Pilihan tidak valid!\n");
        return 1;
    }
    
    printf("Pilih Collision Handling:\n");
    printf("1. Linear Probing\n2. Rehashing\n3. Chaining\n");
    int collision_choice;
    scanf("%d", &collision_choice);
    getchar();
    
    if (collision_choice < 1 || collision_choice > 3) {
        printf("Pilihan tidak valid!\n");
        return 1;
    }
    
    int (*hash_function)(const char*) = hash_functions[hash_choice - 1];
    
    while (1) {
        char key[50];
        printf("Masukkan kata (ketik 'exit' untuk keluar): ");
        fgets(key, 50, stdin);
        key[strcspn(key, "\n")] = 0;
        
        if (strcmp(key, "exit") == 0) {
            break;
        }
        
        if (collision_choice == 3) {
            chaining(chain_table, key, hash_function);
        } else {
            collision_methods[collision_choice - 1](table, key, hash_function);
        }
    }
    
    print_table(chain_table, table, collision_choice);
    
    return 0;
}
