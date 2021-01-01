#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    char name[19];  //  市の名前、UTF-8対応
    float members;  //  世帯人員
    int total;      //  食料合計
    int grain;      //  穀類
    int seafood;    //  魚介類
    int meat;       //  肉類
    int milk;       //  乳卵類
    int vegetable;  //  野菜類
    int fruit;      //  果物
    int seasoning;  //  調味料
    int snack;      //  菓子類
    int cocking;    //  調理料理
    int drink;      //  飲料
    int liquor;     //  酒類
    int eatout;     //  外食
} City;

#define DEBUG
#define MAX_CITY    47

void BuildHeap(City arrayCity[], int size);
void PartialHeap(City arrayCity[], int size, int lastNode);

void PrintCity(City city)
{
    printf("%d, %s, %.2f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", 
        city.id, city.name, city.members, city.total, 
        city.grain, city.seafood, city.meat, city.milk, city.vegetable, city.fruit,
        city.seasoning, city.snack, city.cocking, city.drink, city.liquor, city.eatout);
}

void PrintArray(City city[], int size)
{
    int i;

    for (i=0; i<size; i++) {
        PrintCity(city[i]);
    }
}

int LoadData(City arrayCity[])
{
    char buf[256];
    FILE* fp;

    fp = fopen("consumption.csv","r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        return -1;
    }

    int cn = 0; // 市の数
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%[^,],%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
            &(arrayCity[cn].id), arrayCity[cn].name, &(arrayCity[cn].members), &(arrayCity[cn].total), 
            &(arrayCity[cn].grain),  &(arrayCity[cn].seafood),  &(arrayCity[cn].meat), &(arrayCity[cn].milk), 
            &(arrayCity[cn].vegetable),  &(arrayCity[cn].fruit),  &(arrayCity[cn].seasoning),  &(arrayCity[cn].snack),
            &(arrayCity[cn].cocking),  &(arrayCity[cn].drink),  &(arrayCity[cn].liquor),  &(arrayCity[cn].eatout));
#ifdef DEBUG
        PrintCity(arrayCity[cn]);
#endif
        cn++;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        return -1;
    }

    return cn;
}


void BubbleSort(City arrayCity[], int size)
{
    int i;
    City tbl;
    int cnt = 1;

    while(cnt != 0){
        cnt = 0;
        for(i = 0; i + 1 < size; i++){
            if(arrayCity[i].total >= arrayCity[i + 1].total){
                tbl = arrayCity[i];
                arrayCity[i] = arrayCity[i + 1];
                arrayCity[i + 1] = tbl;
                cnt++;
           }
        }
    }
    //  ここを実装する

}


void QuickSort(City arrayCity[], int left, int right)
{
    int i = left;
    int j = right;
    int index_i = left;
    int index_j = right;
    int pivot = arrayCity[left].seafood;
    City table;

    if(left == right){
        return;
    }
    else{
        while(i <= j){
            if(pivot < arrayCity[i].seafood){
                index_i = i;
                while(i <= j){
                    if(pivot > arrayCity[j].seafood){
                        index_j = j;
                        table = arrayCity[index_j];
                        arrayCity[index_j] = arrayCity[index_i];
                        arrayCity[index_i] = table;
                        break;
                    }
                    j--;
                }
            }
            i++;
        }

        if(index_i == left){
            table = arrayCity[left];
            arrayCity[left] = arrayCity[right];
            arrayCity[right] = table;
            QuickSort(arrayCity, left, right - 1);
            QuickSort(arrayCity, right, right);
        }
        else if(index_i == left + 1 && index_j == right){
            QuickSort(arrayCity, left, left);
            QuickSort(arrayCity, left + 1, right);
        }
        else{
            index_j = j;
            table = arrayCity[left];
            arrayCity[left] = arrayCity[index_j];
            arrayCity[index_j] = table;
            QuickSort(arrayCity, left, index_j - 1);
            QuickSort(arrayCity, index_j + 1, right);
        }
    }
    //  ここを実装する
}



void HeapSort(City arrayCity[], int size)
{
    int vertual_size = size;
    City tbl;

    BuildHeap(arrayCity, size);

    while (vertual_size > 1)
    {
        tbl = arrayCity[0];
        arrayCity[0] = arrayCity[vertual_size - 1];
        arrayCity[vertual_size - 1] = tbl;
        vertual_size--;
        BuildHeap(arrayCity, vertual_size);
    }
}

void BuildHeap(City arrayCity[], int size)
{
    int check_Node;
    int change_Node;
    int change_flag = 0;
    City tbl;

    check_Node = size / 2 - 1;

    while (check_Node >= 0)
    {
        if (2 * check_Node + 2 >= size)
        {
            if (arrayCity[check_Node].meat > arrayCity[2 * check_Node + 1].meat)
            {
                change_flag = 0;
            }
            else
            {
                tbl = arrayCity[2 * check_Node + 1];
                arrayCity[2 * check_Node + 1] = arrayCity[check_Node];
                arrayCity[check_Node] = tbl;
                change_Node = 2 * check_Node + 1;
                change_flag = 1;
            }
        }
        else
        {
            if (arrayCity[check_Node].meat > arrayCity[2 * check_Node + 1].meat && arrayCity[check_Node].meat > arrayCity[2 * check_Node + 2].meat)
            {
                change_flag = 0;
            }
            else if (arrayCity[2 * check_Node + 1].meat > arrayCity[2 * check_Node + 2].meat)
            {
                tbl = arrayCity[2 * check_Node + 1];
                arrayCity[2 * check_Node + 1] = arrayCity[check_Node];
                arrayCity[check_Node] = tbl;
                change_Node = 2 * check_Node + 1;
                change_flag = 1;
            }
            else
            {
                tbl = arrayCity[2 * check_Node + 2];
                arrayCity[2 * check_Node + 2] = arrayCity[check_Node];
                arrayCity[check_Node] = tbl;
                change_Node = 2 * change_Node + 2;
                change_flag = 1;
            }
        }

        if (change_Node <= size / 2 - 1 && change_flag == 1)
        {
            PartialHeap(arrayCity, size, change_Node);
        }
        check_Node--;
    }
}

void PartialHeap(City arrayCity[], int size, int lastNode)
{
    City tbl;
    if (2 * lastNode + 2 < size)
    {
        if ((arrayCity[lastNode].meat > arrayCity[2 * lastNode + 1].meat && arrayCity[lastNode].meat > arrayCity[2 * lastNode + 2].meat) || (lastNode > size / 2 - 1))
        {
            return;
        }
        else
        {
            if (arrayCity[2 * lastNode + 1].meat > arrayCity[2 * lastNode + 2].meat)
            {
                tbl = arrayCity[lastNode];
                arrayCity[lastNode] = arrayCity[2 * lastNode + 1];
                arrayCity[2 * lastNode + 1] = tbl;
                PartialHeap(arrayCity, size, 2 * lastNode + 1);
            }
            else
            {
                tbl = arrayCity[lastNode];
                arrayCity[lastNode] = arrayCity[2 * lastNode + 2];
                arrayCity[2 * lastNode + 2] = tbl;
                PartialHeap(arrayCity, size, 2 * lastNode + 2);
            }
        }
    }
    else
    {
        if (arrayCity[lastNode].meat > arrayCity[2 * lastNode + 1].meat || lastNode > size / 2 - 1)
        {
            return;
        }
        else
        {
            tbl = arrayCity[lastNode];
            arrayCity[lastNode] = arrayCity[2 * lastNode + 1];
            arrayCity[2 * lastNode + 1] = tbl;
            PartialHeap(arrayCity, size, 2 * lastNode + 1);
        }
    }
}


void MergeSort(City arrayCity[], int left, int right)
{
    int mid = left + (right - left) / 2;
    int i;
    int left_i = 0;
    int right_i = 0;

    if(left == right){
        return;
    }
    else{

        MergeSort(arrayCity, left, mid);
        MergeSort(arrayCity, mid + 1, right);

        City left_buff[mid - left + 1];
        City right_buff[right - mid];

        for(i = 0; i <= mid - left; i++){
            left_buff[i] = arrayCity[left + i];
        }
        for(i = 0; i <= right - mid - 1; i++){
            right_buff[i] = arrayCity[mid + 1 + i];
        }
        i = left;

        while(i <= right){
            if(left_i <= mid - left && right_i <= right - mid - 1){
                if(left_buff[left_i].liquor < right_buff[right_i].liquor){
                    arrayCity[i] = left_buff[left_i];
                    left_i++;
                    i++;
                }
                else{
                    arrayCity[i] = right_buff[right_i];
                    right_i++;
                    i++;
                }
            }
            else{
                if(left_i > mid - left){
                    arrayCity[i] = right_buff[right_i];
                    right_i++;
                    i++;
                }
                else if(right_i > right - mid - 1){
                    arrayCity[i] = left_buff[left_i];
                    left_i++;
                    i++;
                }
            }
        }
    }
    
    //  チャレンジ問題2
    //  ここを実装する

}

int main(void)
{
 
    //  事前準備。データの読み込み、配列の作成
    City* arrayCity;
    int cn;
    
    arrayCity = (City*)malloc(sizeof(City) * MAX_CITY);
    cn = LoadData(arrayCity);
    if (cn == -1) {
        exit(EXIT_FAILURE);
    }

    //  食料品合計で並び替え
    printf("===== Sorted by total =====\n");
    BubbleSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);

    //  魚介類で並び替え   
    printf("===== Sorted by seafood =====\n");
    QuickSort(arrayCity, 0, MAX_CITY - 1);
    PrintArray(arrayCity, MAX_CITY);
   
    printf("===== Sorted by liquor =====\n");
    MergeSort(arrayCity, 0, MAX_CITY - 1);
    PrintArray(arrayCity, MAX_CITY);
    
    printf("===== Sorted by meat =====\n");
    HeapSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);
    //  後処理
    free(arrayCity);

    return 0;
}