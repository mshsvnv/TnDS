#ifndef __DEFS_H__
#define __DEFS_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define SUCCESS 0
#define CHOICE_ERR 1
#define ARGUMENTS_ERR 2
#define WRONG_FILE_ERR 3
#define EMPTY_FILE_ERR 4
#define STRUCTS_AMOUNT_ERR 5
#define EMPTY_TABLE_ERR 6
#define INPUT_ERR 7
#define EMPTY_LIST_ERR 8
#define COUNT_STRUCT_ERR 9
#define NO_DEL_ERR 10

#define MAX_INT 5
#define MAX_DOUBLE 8
#define MAX_STREET 20
#define MAX_STRUCTS 1500
#define TEST_10 10
#define TEST_100 100
#define TEST_500 500
#define TEST_1000 1000
#define TEST_1500 1500

typedef struct
{
    char trim; // наличие отделки
} primary_t;

typedef struct
{
    int year_constr;            // год постройки
    int count_former_owners;    // кол-во бывших владельцев
    int count_last_roomers;     // кол-во последних жильцов
    char pets;                  // были ли животные
} secondary_t;

typedef enum
{
    primary = 1,       // первичное жилье
    secondary = 2      // вторичное жилье
} housing_kind_t;

typedef union  // тип жилья
{
    primary_t primary;
    secondary_t secondary;
} housing_t;

typedef struct 
{
    char street[MAX_STREET];  // имя улицы
    int house;                // номер дома
    int floor;                // номер этажа
    int flat;                 // номер квартиры
} adress_t;

typedef struct
{
    adress_t adress;       // адрес
    double whole_squares;  // кол-во квадратных метров
    int count_rooms;       // кол-во комнат
    double cost_square_m;  // стоимость квадратного метра
    housing_kind_t kind;   // тип жилья
    housing_t housing;
} flat_t;

typedef struct
{
    int index;        // индекс в основной таблице
    int count_rooms;  // кол-во комнат
} keys_t;

#endif //__DEFS_H__