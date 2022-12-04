typedef struct {
    char* original;
    char* translation;
} DictionaryData;

typedef struct {
    DictionaryData* dictionary_data;
    int dictionary_size;
} Dictionary;

void init_dict(char* file_name);

char* get_translation(const char* from);

void free_dictionary();

Dictionary get_dictionary();

