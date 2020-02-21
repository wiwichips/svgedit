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
int bain();
int gain();
int tesingGroups();






int main(int argc, char **argv) {
	putsError("createSVGimage");
	int result = 0;
	
//	SVGimage* img1 = createValidSVGimage("Wink_Brutal_Test_2.svg", "testFilesA2/svg.xsd");
	SVGimage* img1 = createSVGimage("quad01_A2.svg");
	
	if(!img1) {
		puts("\timg1 is NULL");
	}
	
	

	putsError("getGroups length");
	List* g = getGroups(img1);
	result = getLength(g);
	printf("\tthe number of groups is: %d\t\tshold be 3\n", result);
	freeList(g);
	
	putsError("getRects length");
	List* r = getRects(img1);
	printf("\tthe number of rectangles is: %d\t\tshould be 1\n", getLength(r));
	freeList(r);
	
	putsError("getCircles length");
	List* c = getCircles(img1);
	printf("\tthe number of circles is: %d\t\tshould be 5\n", getLength(c));
	freeList(c);
	
	putsError("getPaths length");
	List* p = getPaths(img1);
	printf("\tthe number of paths is: %d\t\tshould be 2\n", getLength(p));
	freeList(p);
	
	putsError("SVGtoJSON string");
	char* svgtojason = SVGtoJSON(img1);
	printf("\t%s\n", svgtojason);
	free(svgtojason);


	putsError("writeSVGimage");
	printf("\twrite svg = %d\n", writeSVGimage(img1, "willTest.svg"));


/*	
	putsError("validateSVGimage");
	printf("validateSVGimage = %d\n", validateSVGimage(img1, "testFilesA2/svg.xsd"));
*/	
	putsError("frees");
	deleteSVGimage(img1);
	xmlCleanupParser();
	
    return 0;
}

int gain() {
	putsError("createValidSvgImage from svg");
	SVGimage* img1 = createSVGimage("testFilesA2/Emoji_grinning.svg");
//	SVGimage* img1 = createValidSVGimage("quad01.svg", "testFilesA2/svg.xsd");
	printf("img1 = %p\n", img1);
	
	if(!img1) {
		return 0;
	}

	putsError("validateSVGimage on img1 created from img1 -> ");
	printf("validateSVGimage = %d\n", validateSVGimage(img1, "testFilesA2/svg.xsd"));
	
	putsError("write the svg to file");
	printf("write svg = %d\n", writeSVGimage(img1, "will.svg"));


	putsError("try to open the svg file I wrote");
	SVGimage* img2 = createValidSVGimage("will.svg", "testFilesA2/svg.xsd");
	printf("img2 = %p\n", img2);

	putsError("deleteSVGimage on img1 and img2");
	deleteSVGimage(img1);
	deleteSVGimage(img2);


	xmlCleanupParser();
	puts("");

//	bain();
	return 0;
}

void putsError(char* string) {
	printf("\033[0;3%dm", testingNumber%7 + 1);
	printf("\n\n%d:%s\n", testingNumber, string);
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


int bain() {
	
	puts("\n\ncreate svgimage");
//	SVGimage* gork = createValidSVGimage("quad02.svg", "testFilesA2/svg.xsd");
	SVGimage* gork = createSVGimage("Emoji_poo_A2.svg");

	xmlDoc* doc = SVGimageToDoc(gork);
	
	printf("is it valid tho? : %d\n", validateDoc(doc, "testFilesA2/svg.xsd"));

	xmlSaveFormatFileEnc(0 > 1 ? NULL : "-", doc, "UTF-8", 1); 
	
	// clean up
	xmlFreeDoc(doc);
	deleteSVGimage(gork);
	xmlCleanupParser();
	
    return 0;
}
