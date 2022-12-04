#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "dictionary.h"

void save_translation(char* translation, FILE* file){
    //
    if(strlen(translation) > 1){
        char* translated = get_translation(translation);
        printf("Writing... %s \n", translated);
        char* blank = " ";
        fputs(translated, file);
        fputs(blank, file);
        if(strchr(translation, '\n')){
            fputs("\n", file);
        }
    }
}

int main(int argc, char **argv){
    char* dict_path;
    char* input_path;
    char* output_path;

    if(argc < 4){
        printf("Wrong parameters\n");
    //    return 1
        dict_path = "dictionary-en-cs.csv";
        input_path = "input.txt";
        output_path = "output.txt";
    }else{
        dict_path = argv[1];
        input_path = argv[2];
        output_path = argv[3];
    }

    init_dict(dict_path);

    Dictionary dictionary = get_dictionary();

    for(int i = 0; i < dictionary.dictionary_size; i++){
        printf("D: %s \n", dictionary.dictionary_data[i].original);
    }
    
    FILE* file = fopen(input_path, "rb");
    char* buffer[255];

    FILE* output = fopen(output_path, "wb");
    assert(output != NULL);
   
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        char* word = strtok(buffer, " ");
        save_translation(word, output);
        while(word != NULL){
            word = strtok(NULL, " ");
            if(word == 0x0)
                continue;
            save_translation(word, output);
        }
    }
    fclose(output);
    fclose(file);

    free_dictionary();
    return 0;
}