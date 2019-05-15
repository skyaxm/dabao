/*
	a.c
	功能：利用libxml2解析xml文件
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#define manifest

int GetCurFilePath(char *lpOut)		// get full path of the executable file
{
	char chPath[BUFSIZ] = {0};
	int nRetVal = readlink("/proc/self/exe", chPath, sizeof(chPath)); // get full path of the current-executable file
	if(nRetVal < 0)
	{
		strcpy(lpOut, ".");
		return -1;
	}
	else
	{
		strcpy(lpOut, chPath);
		return 0;
	}
}

int GetCurDir(char *lpOut)									// get directory-path of current executable-file
{
	char	chPath[BUFSIZ] = { 0 };
	if( GetCurFilePath(chPath) < 0 )
		return - 1;
	dirname(chPath);										// dirname will change value of "chPath"(contain result)
	strcpy(lpOut, chPath);									// copy result to out-param

	return 0;
}

xmlDocPtr getdoc(char *docname)							// 根据文件名得到文档指针
{
	xmlDocPtr doc;
	doc = xmlParseFile(docname);
	if(doc == NULL)
	{
		fprintf(stderr, "getdoc() : Document not parsed successfully.\n");
		return NULL;
	}
	return doc;
}

// 在文档doc中解析xpath表达式，返回结果集指针
xmlXPathObjectPtr getnodeset(xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(doc);
	if(context == NULL)
	{
		printf("Error in xmlXPathNewContent\n");
		return NULL;
	}
	result = xmlXPathEvalExpression(xpath, context);		// 在context中解析表达式xpath
	xmlXPathFreeContext(context);							// 释放context
	if(result == NULL)
	{
		printf("Error in xmlXPathEvalExpression\n");
		return NULL;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))			// 解析表达式的结果集为空
	{
		xmlXPathFreeObject(result);
		printf("No result\n");
		return NULL;
	}
	return result;
}

// 解析xmlPath路径的结点
void testReadXmlDoc(char *filepath, char *xmlPath)
{
	xmlDocPtr doc = getdoc(filepath);
	if(NULL == doc)
		return ;

	xmlChar *xpath = (xmlChar*) xmlPath;
	xmlXPathObjectPtr result = getnodeset(doc, xpath);			// 获取结果集
	if(result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval;
		xmlChar *name, *value;
		printf("nodeset number : %d\n", nodeset->nodeNr);		// 打印结果集中结点个数
		int i;
        for(i = 0; i < nodeset->nodeNr; i++)
		{
			xmlNodePtr cur = nodeset->nodeTab[i];				// products
			printf("cur->name = %s\n", cur->name);
			cur = cur->xmlChildrenNode;
			while(cur)
			{
//				if(xmlStrcmp(cur->name, (const xmlChar*) "text"))		// cur->name不为"text"
//				{
					printf("cur->name = %s\t", cur->name);
#ifdef manifest
					name = xmlGetProp(cur, (const xmlChar*) "fileName");	// 获取属性值
					value = xmlGetProp(cur, (const xmlChar*) "fileVersion");
                    printf("fileName = %s, fileVersion = %s\n", name, value);
#else
                    name=xmlGetProp(cur, (const xmlChar*)"name");
                    value=xmlGetProp(cur, (const xmlChar*)"value");
                    printf("name = %s, value = %s\n", name, value);
#endif
					xmlFree(name);
					xmlFree(value);
//				}
				cur = cur->next;
			}
			printf("\n");
		}
		xmlXPathFreeObject(result);
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

int main(void)
{
#if 0
	char curDir[100] = {0};
	char docname[100] = {0};
	GetCurDir(curDir);
	strcpy(docname, curDir);
	printf("docname:%s\n",docname);
#ifdef manifest
//	strcat(docname, "/manifest-FHK.xml");
	testReadXmlDoc("/home/shikuiyang/projects/test/manifest-FHK.xml", "/manifest/builds/build");
//	testReadXmlDoc("/home/shikuiyang/projects/test/manifest-FHK.xml", "/manifest/products/product");

#else
    strcat(docname, "/dprod.xml");
	testReadXmlDoc(docname, "/allproducts/products");
#endif
	return EXIT_SUCCESS;
#endif
	xmlChar *docname = "/media/BOOT/slot1/manifest-FHK.xml";
	xmlChar *xpath = "/manifest/builds/build";
    xmlChar *xpath1 = "/manifest/products"
	xmlDocPtr doc = xmlParseFile(docname);
	if (doc==NULL)
	{
		printf("\n can't get the xmlDocPtr, file may not exist\n");
		return -1;
	}
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
	if (context == NULL) {
		printf("\n create the context failed \n");
		return -1;
	}

    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
    xmlXPathObjectPtr result1 = xmlXPathEvalExpression(xpath1, context);
    xmlXPathFreeContext(context);
	if(result == NULL || result1 == NULL)
	{
		printf("Error in xmlXPathEvalExpression\n");
		return -1;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
		printf("No result\n");
		return -1;
	}
	if(result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval;
        xmlChar *id, *bldName, *bldVersion;
		xmlChar *name, *version, *path, *integrity;
		printf("nodeset number: %d\n", nodeset->nodeNr);
		int i;
        for(i = 0; i < nodeset->nodeNr; i++)
		{
			xmlNodePtr cur = nodeset->nodeTab[i]; //builds/build
			printf("cur->name = %s\n", cur->name);
            id = xmlGetProp(cur, (const xmlChar*)"id");
            bldName = xmlGetProp(cur, (const xmlChar*)"bldName");
            bldVersion = xmlGetProp(cur, (const xmlChar*)"bldVersion");
            printf("id = %s, bldName = %s, bldVersion = %s\n", id, bldName, bldVersion);
			cur = cur->xmlChildrenNode; //turn to the /builds/build/file
			while(cur)
			{
				if(xmlStrcmp(cur->name, (const xmlChar*) "text"))
				{
					printf("cur->name = %s\t", cur->name);
					name = xmlGetProp(cur, (const xmlChar*) "fileName");
					version = xmlGetProp(cur, (const xmlChar*) "fileVersion");
					path = xmlGetProp(cur, (const xmlChar*) "path");
               		printf("fileName = %s, fileVersion = %s, path = %s\n", name, version, path);
					xmlFree(name);
					xmlFree(version);
					xmlFree(path);
				}
				cur = cur->next;
			}
			printf("\n");
		}
		xmlXPathFreeObject(result);
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();

	return EXIT_SUCCESS;
}

