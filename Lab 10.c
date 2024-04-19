#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    struct TrieNode *children[26]; // Assuming English alphabet
    int isEndOfWord; // Flag to mark end of word
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Create a new Trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->isEndOfWord = 0;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Initialize Trie
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createNode();
    }
    return trie;
}

// Inserts a word into the Trie
void insert(struct Trie *trie, char *word) {
    struct TrieNode *crawl = trie->root;
    int index;
    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = createNode();
        }
        crawl = crawl->children[index];
    }
    crawl->isEndOfWord = 1; // Mark the end of the word
}

// Searches for a word in the Trie and returns the number of occurrences
int search(struct Trie *trie, char *word) {
    struct TrieNode *crawl = trie->root;
    int index;
    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (!crawl->children[index]) {
            return 0; // Word not found
        }
        crawl = crawl->children[index];
    }
    return crawl->isEndOfWord; // Returns 1 if it's the end of a word, 0 otherwise
}

// Deallocates memory used by Trie
void deallocateTrie(struct Trie *trie) {
    free(trie); // Frees the Trie structure
}

// Reads words from a file into an array and returns the number of words read
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File not found or unable to open.\n");
        exit(1);
    }
    int count = 0;
    char word[100]; // Assuming maximum word length is 100
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word); // Duplicate the word and store it
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    // Test cases
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], search(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);
    return 0;
}
//Ezekiel Echenique Lab 10
