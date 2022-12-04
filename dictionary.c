#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dictionary.h"

DictionaryData* data;

Dictionary dictionary;

DictionaryData parse(char* data){
    char* original = strtok(data, ",");
    char* translation = strtok(NULL, ",");
    translation[strcspn(translation, "\n")] = '\0';

    DictionaryData d = {
        .original = (char*) calloc(sizeof(char), strlen(original)+1),
        .translation = (char*) calloc(sizeof(char) , strlen(translation)+1)
        };

    strcpy(d.original, original);
    strcpy(d.translation, translation);

    return d;
}

void init_dict(char* file){
    FILE* f = fopen(file, "r");
    if(f == NULL){
        printf("Could not load dictionary\n");
        exit(1);
    }
    char* buffer[255];
    int line = 0;
    data = malloc(0);
    while(fgets(buffer, sizeof(buffer), f) != NULL){
        line ++;

        DictionaryData dict_data = parse(buffer);
        
        data = realloc(data, sizeof(DictionaryData)*line);

        data[line-1] = dict_data;
    }
    fclose(f);
    Dictionary dict = {data, line};
    dictionary = dict;
}

void free_dictionary(){
    for(int i = 0; i < dictionary.dictionary_size; i++){
        free(dictionary.dictionary_data[i].original);
        free(dictionary.dictionary_data[i].translation);
    }
    
    free(data);
    data = NULL;
}

bool compare(char* original, char* to){
    char new[strlen(to) + 1];
    strcpy(new, to);
    new[strcspn(new, "\r\n")] = '\0';
    new[strcspn(new, "\n")] = '\0';

    return strcmp(original, new) == 0;
}
char* get_translation(const char* from){
    for(int i = 0; i < dictionary.dictionary_size; i++){
        char* original = dictionary.dictionary_data[i].original;
        if(compare(original, from)){
            return dictionary.dictionary_data[i].translation;
        }
    }
    return "<unknown>";
}

Dictionary get_dictionary(){
    return dictionary;
}