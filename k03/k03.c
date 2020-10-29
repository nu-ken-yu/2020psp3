#include <stdio.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    int start = 0;
    int pos = 0;
    int len = 0;

    while(key[len] != '\0'){
        len++;
    }
    
    while(text[start + len - 1] != '\0'){
        while(text[start + pos] == key[pos]){
            pos++;
            if(pos == len){
                return &text[start];
            }
        }
        pos = 0;
        start++;
    }

    return NULL;
    //  ここを実装する

}

char* BMSearch(char text[], char key[])
{
    int table[ALPHABET_LEN];
    int start, pre_start;
    int dis = 0;
    int i = 0;
    int text_len = 0;
    int key_len = 0;

    while(text[text_len] != '\0'){
        text_len++;
    }

    while(key[key_len] != '\0'){
        key_len++;
    }
    start = key_len - 1;

    while(i < ALPHABET_LEN){
        table[i] = key_len;
        i++;
    }
    i = 0;
    while(key[i] != '\0'){
        table[(int)key[i]] = key_len - i - 1;
        i++;
    }

    while(start < text_len){
        while(text[start - dis] == key[key_len - dis - 1]){
            dis++;
            if(dis == key_len){
                return &text[start - (dis - 1)];
            }
        }
        pre_start = start;
        start = start - dis + table[(int)text[start - dis]];
        if(start <= pre_start){
            start = pre_start + 1;
        }
        dis = 0;
    }

    return NULL;
    //  ここを実装する

}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}