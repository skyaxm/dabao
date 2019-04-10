#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct URI
{
    char scheme[16];
    char username[32];
    char host[32];
	char port[16];
    char dir[256];
	char filename[64];
};


static int
	parse_uri(char* uristr, struct URI *uri)
{
	//uristr: sftp://username@host:port:dir
	char *start = uristr;    
//	status_t res = NO_ERR;
	while (!isalpha(*start))
		start++;
	char *symbol = start;

	symbol = strchr(start, ':');
    if (symbol == NULL)
        return -1;
    strncpy(uri->scheme, start, symbol-start);
	uri->scheme[symbol-start] = '\0';
	
    start = symbol+3;
    symbol = strchr(start, '@');
    strncpy(uri->username, start, symbol-start);
	uri->username[symbol-start] = '\0';
		
    start = symbol+1;
    symbol = strchr(start,':');
    strncpy(uri->host, start, symbol-start);
	uri->host[symbol-start] = '\0';
	
    start = symbol+1;
    symbol = strchr(start, ':');
	if (symbol != NULL)
	{
		strncpy(uri->port, start, symbol-start);
		uri->port[symbol-start] = '\0';
		start = symbol+1;
	}
    symbol = strchr(start, '\0');
    strncpy(uri->dir, start, symbol-start);
	uri->dir[symbol-start] = '\0';
	
	start = symbol;
	while (*start != '/')
		start--;
	start=start+1;
	strncpy(uri->filename, start, symbol-start);
	uri->filename[symbol-start] = '\0';
	
    return 0;
}


int main()
{
	char sftp_cmd[4092];
    char *str="sftp://shikuiyang@10.180.8.21:/home/shikuiyang/helloworld.c";
    struct URI *uri=malloc(sizeof(struct URI));
    int ret = parse_uri(str, uri);
    printf("ret:%d\n",ret);
/*    printf("scheme:%s username:%s host:%s port:%s dir:%s\n", uri->scheme,
            uri->username,
            uri->host,
            uri->port,
            uri->dir); */
	printf("uri->scheme = %s\nuri->username = %s\nuri->host = %s\nuri->port = %s\nuri->dir = %s\nuri->filename = %s\n",
								  uri->scheme, uri->username, uri->host, uri->port, uri->dir, uri->filename);

	sprintf(sftp_cmd, "./home/shikuiyang/projects/shell/sftp_download.sh %s %s %s", uri->username,
														    uri->host,														   														       
														    uri->dir);
	printf("%s\n", sftp_cmd);
	return 0;
}
