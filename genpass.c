#!/bin/tcc -run
//includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>
//const
#define begin {
#define then {
#define do {
#define elif(expression) }else if (expression)
#define otherwise }else{
#define end; }
#define u8 unsigned long long
#define defsize		8
#define defcount	1
//genpass does a very basic and-based reduction of random generation.
//This means that without adding 4 extra characters, the generation wraps back around to numbers.
//Since I don't have any alphanumeric characters left, I chose to substitute with 4 common symbols
//which are in a row in the ascii chart.
#define dosymbols	1
//{{{ Legal compliance
static const char *gamerword="NIGGER";
//}}}
static const char nl = '\n';
static const char strnd = '\0';
static const char *inwarningstr="GENPASS FAIL:	Requires input of EXACTLY TWO DECIMAL NUMBERS if you don't want the default setting.\n";
static const char *argusagestr="GENPASS USAGE:	genpass (size count)\nIf either size or count is not given, defaults will be used.\nEdit these defaults in the C script at path \"/bin/genpass\"\n";

//code
int printinformat() begin
	//write, not fwrite, so that none of its standard output  gets redirected to a file
	//(Fucking C is so weird).
	write(0,inwarningstr,strlen(inwarningstr));	
	return 0;
end;
int printargusage() begin
	write(0,argusagestr,strlen(argusagestr));
	return 0;
end;
int checkisdec(char *a,u8 len) begin
	//var
	int output=1;
	//code
	for (int i=0;i<len;i++)
		if (a[i]<=0||a[i]>=0x39) output^=output;
	return output;
end;

int main(int argc,char** argv) begin
	//var
	int size;	int count;	char *strs;	u8 ttime;
	//code
	if (argc<2) then
		size	=defsize;
		count	=defcount;
	elif(argc<3) then
		printargusage(); return 1;
	otherwise
		if (	checkisdec(argv[1],strlen(argv[1]))&&
			checkisdec(argv[2],strlen(argv[2]))) then
			size	=atoi(argv[1]);
			count	=atoi(argv[2]); 
		otherwise 
		printinformat(); return 0; 
		end;
	end;
	
	strs=malloc(size*count);
	asm volatile("rdtsc":"=a"(ttime));
	srand(ttime);
	for (int i=0;i<count;i++) begin
		for (int j=0;j<size;j++) begin
			//var
			char rnd;
			//code
			rnd=(char)(rand()& 0x3f);//max of 64
			strs[(i*size)+j]=
					rnd<0x0a?	rnd|0x30:
					rnd<35?	(rnd-9)|0x40:
					rnd<60?	(rnd-34)|0x60://one less to keep the @s away
						#if dosymbols == 1
						(rnd-25)|0x20;//do 4 symbols
						#else
						(rnd-60)|0x30;//do 4 more numbers
						#endif
		end;
	end;
	for (int i=0;i<count;i++) begin
		fwrite(&strs[i*size],1,size,stdout);
		fwrite(&nl,1,1,stdout);
	end;
	return 0;
end;
