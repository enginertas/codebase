#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void* malloc(size_t size);
void free(void* p);

int ARGC;
char** ARGV;
unsigned Cluster_Size = 0, bytes_per_sector=0 , sectors_per_cluster=0, start_sector = 0, Int_Fragmentation = 0, cctc=0;

void printAttr(int hex2)
{
	if(hex2 & 1)
		printf("R");
	else
		printf("-");
	if(hex2 & 2)
		printf("H");
	else
		printf("-");
	if(hex2 & 4)
		printf("S");
	else
		printf("-");
	if(hex2 & 16)
		printf("D");
	else
		printf("-");	
	if(hex2 & 32)
		printf("A");
	else
		printf("-");

	printf(" ");
}

int totalSize(int fd, int offset)
{
	int i, total_size=0, hex2, hex3;
	char buffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(i=0; i<Cluster_Size; i++)
	{
		lseek(fd, offset + i*32, SEEK_SET);
		read(fd, buffer, 8);

		lseek(fd, 3, SEEK_CUR);
		hex2 = 0;
		read(fd, &hex2, 1);
		if(strcmp(buffer, ".       ") && strcmp (buffer, "..      ") && hex2!=0x80)
		{
			lseek(fd, 14, SEEK_CUR);
			hex2 = 0;
			read(fd, &hex2, 2);
			if(hex2)
			{
				hex3=0;
				read(fd, &hex3, 4);
				if(hex3)
				{
					total_size += hex3;
					Int_Fragmentation += cctc - hex3 % cctc;
				}
				else
					total_size += totalSize(fd, (start_sector + (hex2-2)*sectors_per_cluster)*bytes_per_sector);
			}
		}			
	}
	return total_size;
}

void printBootSector(char* image)
{
	unsigned hex=0, fd;
	char buffer[12];
	fd = open(image, O_RDONLY);

	lseek(fd, 0x0b ,SEEK_SET);
	read(fd, &hex ,2);
	printf("bytes per sector: %d\n", hex);
	hex=0;
	read(fd, &hex, 1);
	printf("sectors per cluster: %d\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("number of reserved sectors: %d\n", hex);
	hex=0;
	read(fd, &hex, 1);
	printf("number of fat copies: %d\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("maximum root directory entries: %d\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("total sectors: %d\n", hex);
	hex=0;
	read(fd, &hex, 1);
	printf("media descriptor type: %hx\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("sectors per fat: %d\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("sectors per track: %d\n", hex);
	hex=0;
	read(fd, &hex, 2);
	printf("number of heads: %d\n", hex);
	hex=0;
	read(fd, &hex, 4);
	printf("number of hidden sectors: %d\n", hex);
	hex=0;
	read(fd, &hex, 4);
	printf("number of sectors: %d\n", hex);
	hex=0;	
	lseek(fd, 0x1fe ,SEEK_SET);
	read(fd, &hex ,2);
	printf("signature: %hx\n", hex);
	hex=0;
	lseek(fd, 0x02b ,SEEK_SET);
	read(fd, buffer ,11);
	buffer[11]='\0';
	printf("volume label: <%s>\n", buffer);
	
	close(fd);
}

void printDiskUsage(char* image)
{	
	unsigned hex1=0, hex2=0, fd, total_clusters ,reserved=0;
	unsigned max_root_directory=0, total_fat_sectors=0;
	unsigned free_clusters=0, total_size=0, hex3=0;
	fd = open(image, O_RDONLY);

	lseek(fd, 0x0e ,SEEK_SET);	/******** get reserved sector number *********/
	read(fd, &reserved, 2);
	start_sector += reserved;

	read(fd, &hex1, 1);		/******** hex1 <- no_of_copies_of_fat ********/
	lseek(fd, 5, SEEK_CUR);
	read(fd, &hex2, 2);		/******** hex2 <- sectors_per_fat ************/
	total_fat_sectors = hex1*hex2;	
	start_sector += total_fat_sectors;	

	lseek(fd, 0x11, SEEK_SET);	
	read(fd, &max_root_directory, 2);
	lseek(fd, 0x0b , SEEK_SET);
	read(fd, &bytes_per_sector, 2);
	start_sector += max_root_directory * 32 / bytes_per_sector;

	lseek(fd, 0x0d ,SEEK_SET);
	read(fd, &sectors_per_cluster, 1);
	hex1 = hex2 = 0;
	lseek(fd, 0x13, SEEK_SET);
	read(fd, &hex1, 2);	

	total_clusters = (hex1 - start_sector) / sectors_per_cluster;
	printf("total clusters: %d\n", total_clusters);

	lseek(fd, reserved * bytes_per_sector, SEEK_SET);	/*****go to FAT tables *****/
	for(hex2=0; hex2<total_clusters; hex2++)
	{
		hex1 = 0;
		read(fd ,&hex1, 2);
		if(!hex1)
			free_clusters++;
	}
	printf("used clusters: %d\n", total_clusters - free_clusters);

	cctc = bytes_per_sector * sectors_per_cluster;
	Cluster_Size = cctc/ 32;
	for(hex1=1; hex1<max_root_directory; hex1++)
	{
		lseek(fd, (reserved + total_fat_sectors)*bytes_per_sector + hex1*32 + 0x0b, SEEK_SET);
		hex2 = 0;
		read(fd, &hex2, 1);
		if(hex2!=0x80)
		{	
			lseek(fd, 14, SEEK_CUR);
			hex2 = 0;
			read(fd, &hex2, 2);
			if(hex2)
			{
				hex3=0;
				read(fd, &hex3, 4);
				if(hex3)
				{
					total_size += hex3;
					Int_Fragmentation += cctc - hex3 % cctc;
				}				
				else
					total_size += totalSize(fd, (start_sector + (hex2-2)*sectors_per_cluster)*bytes_per_sector);

			}
		}
	}
	printf("total size of files: %d\n", total_size);



	printf("internal fragmentation: %d\n", Int_Fragmentation);

	close(fd);
}

int listEntries(char* image, int argv_offset)
{
	unsigned hex1=0, hex2=0, fd,reserved=0,test_case=0;
	unsigned max_root_directory=0, total_fat_sectors=0, offset = 0;
	char buffer[9]={0,0,0,0,0,0,0,0,0}, *p;

	fd = open(image, O_RDONLY);

	lseek(fd, 0x0e ,SEEK_SET);	/******** get reserved sector number *********/
	read(fd, &reserved, 2);
	start_sector += reserved;

	read(fd, &hex1, 1);		/******** hex1 <- no_of_copies_of_fat ********/
	lseek(fd, 5, SEEK_CUR);
	read(fd, &hex2, 2);		/******** hex2 <- sectors_per_fat ************/
	total_fat_sectors = hex1*hex2;	
	start_sector += total_fat_sectors;	

	lseek(fd, 0x11, SEEK_SET);	
	read(fd, &max_root_directory, 2);
	lseek(fd, 0x0b , SEEK_SET);
	read(fd, &bytes_per_sector, 2);
	start_sector += max_root_directory * 32 / bytes_per_sector;

	lseek(fd, 0x0d ,SEEK_SET);
	read(fd, &sectors_per_cluster, 1);
	hex1 = hex2 = 0;

	Cluster_Size = bytes_per_sector * sectors_per_cluster / 32;
	offset = (reserved + total_fat_sectors)*bytes_per_sector;
	if(ARGC==4)
	{
		for(hex1=0; hex1<max_root_directory; hex1++)
		{
			lseek(fd, offset + hex1*32, SEEK_SET);
			read(fd, buffer, 8);
			
			lseek(fd, 3, SEEK_CUR);
			hex2 = 0;
			read(fd, &hex2, 1);			
			if(hex2!=0x80 && strcmp(buffer,"") && buffer[0]!=' ')
			{
				printAttr(hex2);
				for(p = buffer; *p && *p!=' ' ;p++)
					printf("%c", *p);

				lseek(fd, -4, SEEK_CUR);
				read(fd, buffer, 3);
				buffer[3]=0;
				
				if(!(hex2 & 16) && strcmp(buffer,"") && buffer[0]!=' ')
				{
					printf(".");
					for(p = buffer; *p && *p!=' ' ;p++)
						printf("%c", *p);					
				}	
				printf("\n");	
			}			
		}
		return 0;
	}
	
	for(;argv_offset < ARGC; argv_offset++)
	{
		lseek(fd, offset + 0x1a, SEEK_SET);
		hex1=0;
		read(fd, &hex1, 2);

		if(hex1)
		{
			test_case = Cluster_Size;
			hex1 = 0;
		}
		else
		{
			test_case = max_root_directory;
			hex1 = 1;
		}
		for(; hex1<test_case; hex1++)
		{
			lseek(fd, offset + hex1*32, SEEK_SET);
			read(fd, buffer, 8);

			for(p=buffer; *p!='\0' && *p!=' '; p++);
			*p='\0';

			if(!strcmp(buffer, ARGV[argv_offset]))
			{
				/*lseek(fd, -4, SEEK_CUR);
				read(fd, buffer, 3);
				for(p=buffer; *p!='\0' && *p!=' '; p++);
				*p=0;*/
				hex2=0;
				lseek(fd, 3 ,SEEK_CUR);
				read(fd, &hex2, 2);
				
				if(hex2 & 16/*strcmp(buffer,"") && buffer[0]!=' '*/) /*******directory test******/
				{
					lseek(fd, offset + hex1*32 + 0x1a, SEEK_SET);
					hex2=0;
					read(fd, &hex2, 2);
					
					if(hex2)
						offset = (start_sector + (hex2-2)*sectors_per_cluster)*bytes_per_sector;
					else
						offset = (reserved + total_fat_sectors)*bytes_per_sector;
					
					break;
				}
			}
		}
	}

	lseek(fd, offset + 0x1a, SEEK_SET);
	hex1=0;
	read(fd, &hex1, 2);

	if(hex1)
		test_case = Cluster_Size;
	else
		test_case = max_root_directory;
	
	for(hex1=0; hex1<test_case; hex1++)
	{
		lseek(fd, offset + hex1*32, SEEK_SET);
		read(fd, buffer, 8);
		
		lseek(fd, 3, SEEK_CUR);
		hex2 = 0;
		read(fd, &hex2, 1);			
		if(hex2!=0x80 && strcmp(buffer,"") && buffer[0]!=' ')
		{
			printAttr(hex2);
			for(p = buffer; *p && *p!=' ' ;p++)
				printf("%c", *p);

			lseek(fd, -4, SEEK_CUR);
			read(fd, buffer, 3);
			buffer[3]=0;
			
			if(!(hex2 & 16) && strcmp(buffer,"") && buffer[0]!=' ')
			{
				printf(".");
				for(p = buffer; *p && *p!=' ' ;p++)
					printf("%c", *p);					
			}	
			printf("\n");	
		}			
	}
	return 0;
}
int fileContents(char* image, int argv_offset)
{
	unsigned hex1=0, hex2=0, fd,reserved=0,total_size=0 ,test_case=0,i=0;
	unsigned max_root_directory=0, total_fat_sectors=0, offset = 0;
	char buffer[9]={0,0,0,0,0,0,0,0,0}, *p, file_name[13] = {0}, ext[4]={0,0,0,0};

	fd = open(image, O_RDONLY);

	lseek(fd, 0x0e ,SEEK_SET);	/******** get reserved sector number *********/
	read(fd, &reserved, 2);
	start_sector += reserved;

	read(fd, &hex1, 1);		/******** hex1 <- no_of_copies_of_fat ********/
	lseek(fd, 5, SEEK_CUR);
	read(fd, &hex2, 2);		/******** hex2 <- sectors_per_fat ************/
	total_fat_sectors = hex1*hex2;	
	start_sector += total_fat_sectors;	

	lseek(fd, 0x11, SEEK_SET);	
	read(fd, &max_root_directory, 2);
	lseek(fd, 0x0b , SEEK_SET);
	read(fd, &bytes_per_sector, 2);
	start_sector += max_root_directory * 32 / bytes_per_sector;

	lseek(fd, 0x0d ,SEEK_SET);
	read(fd, &sectors_per_cluster, 1);
	hex1 = hex2 = 0;

	Cluster_Size = bytes_per_sector * sectors_per_cluster / 32;
	offset = (reserved + total_fat_sectors)*bytes_per_sector;

	ARGC--;
	for(;argv_offset < ARGC; argv_offset++)
	{
		lseek(fd, offset + 0x1a, SEEK_SET);
		hex1=0;
		read(fd, &hex1, 2);

		if(hex1)
		{
			test_case = Cluster_Size;
			hex1 = 0;
		}
		else
		{
			test_case = max_root_directory;
			hex1 = 1;
		}
		for(; hex1<test_case; hex1++)
		{
			lseek(fd, offset + hex1*32, SEEK_SET);
			read(fd, buffer, 8);

			for(p=buffer; *p && *p!=' '; p++);
			*p=0;

			if(!strcmp(buffer, ARGV[argv_offset]))
			{
				/*lseek(fd, -4, SEEK_CUR);
				read(fd, buffer, 3);
				for(p=buffer; *p && *p!=' '; p++);
				*p=0;*/

				hex2=0;
				lseek(fd, 3 ,SEEK_CUR);
				read(fd, &hex2, 2);

				if(hex2 & 16/*strcmp(buffer,"") && buffer[0]!=' '*/)
				{
					lseek(fd, offset + hex1*32 + 0x1a, SEEK_SET);
					hex2=0;
					read(fd, &hex2, 2);
					
					if(hex2)
						offset = (start_sector + (hex2-2)*sectors_per_cluster)*bytes_per_sector;
					else
						offset = (reserved + total_fat_sectors)*bytes_per_sector;
					break;
				}
			}
		}
	}

	lseek(fd, offset + 0x1a, SEEK_SET);
	hex1=0;
	read(fd, &hex1, 2);

	if(hex1)
	{
		test_case = Cluster_Size;
		hex1 = 0;
	}
	else
	{
		test_case = max_root_directory;
		hex1 = 1;
	}
	
	for(; hex1<test_case; hex1++)
	{
		lseek(fd, offset + hex1*32, SEEK_SET);
		read(fd, buffer, 8);
		read(fd, ext, 3);

		for(p=buffer; *p && *p!=' ' ;p++);
		*p = 0;

		for(p=ext; *p && *p!=' ' ;p++);
		*p = 0;

		strcpy(file_name, buffer);
		if(*ext!=' ' && *ext)
		{	
			strcat(file_name,".");
			strcat(file_name,ext);
		}
		read(fd, &hex2 ,2);
		if(hex2!=0x80 && !strcmp(file_name, ARGV[argv_offset]))
		{
			hex2=0;
			lseek(fd, offset + hex1*32 + 0x1a, SEEK_SET);
			read(fd, &hex2, 2);
			offset = (start_sector + (hex2-2)*sectors_per_cluster)*bytes_per_sector;
			
			read(fd, &total_size, 4);			
			break;
		}			
	}

	lseek(fd, offset, SEEK_SET);
	for(i=0; i<total_size; i++)
	{
		hex2=0;
		read(fd, &hex2, 1);
		printf("%c",hex2);
	}
	return 0;
}

int main(int argc, char** argv)
{
	char* image_file;

	image_file = (char*)malloc((strlen(argv[1])+1)*sizeof(char));
	strcpy(image_file, argv[1]);

	if(!strcmp(argv[2], "--printbootsector"))
		printBootSector(image_file);
	else if(!strcmp(argv[2], "--printdiskusage"))
		printDiskUsage(image_file);
	else if(argc>3)
	{
		ARGC = argc;
		ARGV = argv;	

		if(!strcmp(argv[2], "--listdirectoryentries"))
			listEntries(image_file, 4);
		else if(!strcmp(argv[2], "--printfilecontents"))
			fileContents(image_file, 4);
	}
	free(image_file);
	return 0;
}
