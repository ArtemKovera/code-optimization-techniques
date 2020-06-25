/*

    This program demonstrates data alignment for computer systems with x86-64 architecture
    and Linux 64-bit OS

*/
#include<stdio.h>
#include<stdlib.h>



struct Int
{
    int i1;
} i;

struct Long
{
    long i1;
} l;

struct Char
{
    char c1;
} c;

struct CharChar
{
    char c1; char c2;
} cc;

struct IntInt
{
    int i1; int i2;
} ii;

struct LongLong
{
    long l1; long l2;
} ll;

struct CharInt
{
    char c1; int i1;
} ci;

struct CharLong
{
    char c1; long l1;
} cl;

struct IntChar
{
    int i1; char c1;
} ic;

struct IntLong
{
    int i1; long l1;
} il;

struct LongChar
{
    long l1; char c1;
} lc;

struct LongInt
{
    long l1; int i1;
} li;

struct CharIntLong
{
    char c1; int i1; long l1;
} cil;

struct IntCharLong
{
    int i1; char c1; long l1;
} icl;

struct IntLongChar
{
    int i1; long l1; char c1;
} ilc;

struct LongIntChar
{
    long l1; int i1; char c1;
} lic;

struct LongCharInt
{
    long l1; char c1; int i1;
} lci;

struct CharLongInt
{
    char c1; long l1; int i1;
} cli;

struct CharCharIntIntLongLong
{
    char c1; char c2; int i1; int i2; long l1; long l2;
} cciill;

struct CharLongIntCharLongInt
{
    char c1; long l1; int i1; char c2; long l2; int i2;
} clicli;

struct LongCharIntLongCharInt
{
    long l1; char c1; int i1; long l2; char c2; int i2;
} lcilci;

struct LongLongIntIntCharChar
{
    long l1; long l2; int i1; int i2; char c1; char c2;
} lliicc;

struct LongLongCharCharIntInt
{
    long l1; long l2; char c1; char c2; int i1; int i2;
} llccii;

int main()
{
    printf("the actual size of a struct with {char} (1) is %ld\n", sizeof(c));  //1
    printf("the actual size of a struct with {int} (4) is %ld\n", sizeof(i));   //4
    printf("the actual size of a struct with {long} (8) is %ld\n\n", sizeof(l));  //8  

    printf("the actual size of a struct with {char, char} (1, 1) is %ld\n", sizeof(cc));  //2   
    printf("the actual size of a struct with {int, int} (4, 4) is %ld\n", sizeof(ii));    //8
    printf("the actual size of a struct with {long, long} (8, 8) is %ld\n\n", sizeof(ll));  //16  

    printf("the actual size of a struct with {char, int} (1, 4) is %ld\n", sizeof(ci));   //8    
    printf("the actual size of a struct with {char, long} (1, 8) is %ld\n", sizeof(cl));  //16      
    printf("the actual size of a struct with {int, char} (4, 1) is %ld\n", sizeof(ic));   //8    
    printf("the actual size of a struct with {int, long} (4, 8) is %ld\n", sizeof(il));   //16    
    printf("the actual size of a struct with {long, char} (8, 1) is %ld\n", sizeof(lc));  //16    
    printf("the actual size of a struct with {long, int} (8, 4) is %ld\n\n", sizeof(li)); //16    

    printf("the actual size of a struct with {char, int, long} (1, 4, 8) is %ld\n", sizeof(cil));  //16
    printf("the actual size of a struct with {char, long, int} (1, 8, 4) is %ld\n", sizeof(cli));  //24
    printf("the actual size of a struct with {int, char, long} (4, 1, 8) is %ld\n", sizeof(icl));  //16
    printf("the actual size of a struct with {int, long, char} (4, 8, 1) is %ld\n", sizeof(ilc));  //24
    printf("the actual size of a struct with {long, char, int} (8, 1, 4) is %ld\n", sizeof(lci));  //16
    printf("the actual size of a struct with {long, int, char} (8, 4, 1) is %ld\n\n", sizeof(lic));  //16

    printf("the actual size of a struct with {char, char, int, int, long, long} (1, 1, 4, 4, 8, 8) is %ld\n", sizeof(cciill));  //32
    printf("the actual size of a struct with {long, char, int, long, char, int} (8, 1, 4, 8, 1, 4) is %ld\n", sizeof(lcilci));  //32
    printf("the actual size of a struct with {long, long, int, int, char, char} (8, 8, 4, 4, 1, 1) is %ld\n", sizeof(lliicc));  //32
    printf("the actual size of a struct with {long, long, char, char, int, int} (8, 8, 1, 1, 4, 4) is %ld\n", sizeof(llccii));  //32
    printf("the actual size of a struct with {char, long, int, char, long, int} (1, 8, 4, 1, 8, 4) is %ld\n\n", sizeof(clicli));  //40  

    return 0;
}