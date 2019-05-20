#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <dirent.h>  
#include <sys/stat.h>  
#include <unistd.h>  
#include <sys/types.h> 

void listDir(char *path)  
{
	DIR *dir ;  
    struct dirent *ent  ;  
    int i=0  ;  
    char sub_path[512];  
  
    dir=opendir(path);  
    memset(sub_path, 0, sizeof(sub_path));  
    
    while ((ent=readdir(dir))!=NULL) {  
        if (ent->d_type == DT_DIR) {  
            if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)  
               continue;    
            sprintf(sub_path, "%s/%s", path,ent->d_name);  
            printf("path:%s\n",sub_path);  
            listDir(sub_path);  
  
        } else {
			printf("%s\n", ent->d_name);
		}
   }  
}  
  
int main(int argc,char *argv[])  
{  
        listDir(argv[1]);  
        return 0;  
}

