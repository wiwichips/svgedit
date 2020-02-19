#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

#define sch "testFilesA2/svg.xsd"

int testingNumber = 0;
int debug = 0;

int dain(int argc, char **argv);
void test1(SVGimage* gork);
void putsError(char* string);

int main(int argc, char **argv) {
	putsError("createValidSvgImage from quad01_A2.svg");
	SVGimage* img1 = createValidSVGimage("quad01_A2.svg", "testFilesA2/svg.xsd");
	
	putsError("validateSVGimage on img1 created from img1 -> ");
	validateSVGimage(img1, "quad01_A2.svg");
	
	putsError("SVGimageToDoc from img1 ->  ");
	xmlDoc* doc = SVGimageToDoc(img1);

	putsError("validateDoc on doc from img1");
	printf("validateDoc = %d\n", validateDoc(doc, "testFilesA2/svg.xsd"));
	
	putsError("xmlFreeDoc on doc from img1");
	xmlFreeDoc(doc);

	putsError("deleteSVGimage on img1");
	deleteSVGimage(img1);


	xmlCleanupParser();
	puts("");
    return 0;
}

void putsError(char* string) {
	printf("\033[0;3%dm", 4);
	printf("\n\n%d:\t%s", testingNumber, string);
	printf("\033[0m");
	
	testingNumber++;
	return;
}

void test1(SVGimage* gork) {
	
	freeListDataStructure(getRects(gork));
	freeListDataStructure(getCircles(gork));
//	freeListDataStructure(getGroups(gork));
	freeListDataStructure(getPaths(gork));
	
	printf("numRectsWithArea = %d\n", numRectsWithArea(gork, 1));
	printf("numCirclesWithArea = %d\n", numCirclesWithArea(gork, 1));
	printf("numPathsWithdata = %d\n", numPathsWithdata(gork, "test"));
//	printf("numGroupsWithLen = %d\n", numGroupsWithLen(gork, 1));
	
	printf("numAttr = %d\n", numAttr(gork));
	
	return;
}

int dain(int argc, char **argv) {
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
    char buff[256];
    int i, j;

    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory. 
     */
    xmlCreateIntSubset(doc, BAD_CAST "root", NULL, BAD_CAST "tree2.dtd");

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
    xmlNewChild(root_node, NULL, BAD_CAST "node1", BAD_CAST "content of node 1");
    /* 
     * The same as above, but the new child node doesn't have a content 
     */
    xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);

    /* 
     * xmlNewProp() creates attributes, which is "attached" to an node.
     * It returns xmlAttrPtr, which isn't used here.
     */
    node =
        xmlNewChild(root_node, NULL, BAD_CAST "node3",
                    BAD_CAST "this node has attributes");
    xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");
    xmlNewProp(node, BAD_CAST "foo", BAD_CAST "bar");

    /*
     * Here goes another way to create nodes. xmlNewNode() and xmlNewText
     * creates a node and a text node separately. They are "attached"
     * by xmlAddChild() 
     */
    node = xmlNewNode(NULL, BAD_CAST "node4");
    node1 = xmlNewText(BAD_CAST
                   "other way to create content (which is also a node)");
    xmlAddChild(node, node1);
    xmlAddChild(root_node, node);

    /* 
     * A simple loop that "automates" nodes creation 
     */
    for (i = 5; i < 7; i++) {
        sprintf(buff, "node%d", i);
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);
        for (j = 1; j < 4; j++) {
            sprintf(buff, "node%d%d", i, j);
            node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
            xmlNewProp(node1, BAD_CAST "odd", BAD_CAST((j % 2) ? "no" : "yes"));
        }
    }

    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}


