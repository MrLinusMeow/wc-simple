#include <stdio.h>
#include <ctype.h>

unsigned long bcount = 0;
unsigned long total_bcount = 0;
unsigned long wcount = 0;
unsigned long total_wcount = 0;
unsigned long lcount = 0;
unsigned long total_lcount = 0;

void counter (char *file){
	FILE *fp = fopen (file, "r");
	if(!fp)
		perror("fopen(): ");
	bcount = wcount = lcount = 0;
	unsigned char c = getc(fp);
	while(!feof(fp)){
		if(isalpha(c)){
			wcount++;
			while(isalpha(c)){
				++bcount;
				c = getc(fp);
			}
		}
		++bcount;
		if(c == '\n')
			++lcount;
		c = getc(fp);
	}
	fclose(fp);

	printf ("%6lu %6lu %6lu %s\n", lcount, wcount, bcount, (char*)file);
	total_bcount += bcount;
	total_wcount += wcount;
	total_lcount += lcount;
}

int main(int argc, char **argv){
	if(argc < 2)
		fprintf(stderr,"usage: wc FILE [FILE...]");
	for(int i = 1; i < argc; ++i)
		counter(argv[i]);
	if(argc > 2)
		printf ("%6lu %6lu %6lu %s\n", lcount, wcount, bcount, "total");
	return 0;
}
