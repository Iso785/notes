#include <stdio.h>

int get_int_len(int value){
    int len = 0;
    do{
        len++;
        value /= 10;
    }while(value > 0);
    return len;
}

int get_string_len(char* string){
    int len = 0;
    for(len = 0;string[len];len++); // аналагично с while(string[len]) len++;
    return len;
}

//Generic только для того что бы можно было вызивать 2 функции по 1 имени, он необязателен!
#define get_len(x) _Generic((x), \
    int: get_int_len, \
    char*: get_string_len, \
    const char*: get_string_len, \
    char[sizeof(x)]: get_string_len \
)(x)

void func(char* string,int value,char* new_str,int SIZE){
    int value_len = get_len(value);

    while (*string){
        *new_str = *string;
        new_str++;
        string++;
    }

    for (int i = value_len - 1; i >= 0; i--) {
        new_str[i] = (char)((value % 10) + '0'); // Обязательно добавляем '0'
        value /= 10;
    }
}

int main(){
    char string[] = "random_string_text";
    int value = 1488;
    /* scanf ("%d", &value); 
        можно добавить если хотим вводить число с клавиатуры
    */
    int SIZE = get_len(value) + get_len(string);
    char new_string[SIZE + 1];

    func(string,value,new_string,SIZE);

    printf("%s", new_string);
}