#include<stdio.h>
#include<stdint.h>
#include<endian.h>
#include<string.h>

int main(int argc, char** argv)
{
	FILE *fp;
	fp = fopen(argv[1],"r");
	uint8_t buff[2048];
	fread(buff,8,sizeof(uint8_t),fp);
	buff[8] = 0;
	for(int i=0;i<8;i++)
		printf("%d ",(uint8_t)buff[i]);
	printf("\n");

	int count = 0;
	while(!feof(fp))
	{
		int32_t len;
		fread(&len,1,sizeof(int32_t), fp);
		len = be32toh(len);
		uint8_t type[5];
		fread(type,4,sizeof(uint8_t), fp);
		type[4] = 0;
		printf("Chunk %d, length %d, type %s\n",count, len,type);
		fseek(fp,len+4,SEEK_CUR);
		if(strcmp((char*)type,"IEND") == 0)
			break;
	}
	return 0;

}
