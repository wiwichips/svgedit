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
int oldmain(int argc, char **argv);
void hen_and_chicksToFile();
void david();
void chris();

int main() {
	
//	oldmain(2, NULL);
//david();

	chris();
	
	return 0;
}

void david() {
	SVGimage* image = NULL;

    char *SVGname = "Wink_Brutal_Test_21.svg";
    char *XSDname = "testFilesA2/svg.xsd";


    image = createValidSVGimage(SVGname, XSDname);

    // image = createSVGimage(SVGname); // Create

    Attribute* attribute = malloc(sizeof(Attribute));
    attribute->name = malloc((strlen("d") + 1) * sizeof(char));
    attribute->value = malloc((strlen("plzwork.....") + 1) * sizeof(char));

    strcpy(attribute->name, "d");
    strcpy(attribute->value, "plzwork.....");

    setAttribute(image, PATH, 1, attribute);
    writeSVGimage(image, "test.svg");
    xmlCleanupParser();
	deleteSVGimage(image);
    return;
}

void chris() {
	
	SVGimage* image = createValidSVGimage("Wink_Brutal_Test_21.svg", "testFilesA2/svg.xsd");
	
	if (true) {
        Attribute* atr = malloc(sizeof(Attribute));
        char* name = calloc(50, sizeof(char));
        char* value = calloc(50, sizeof(char));
        strcpy(name, "fill");
        strcpy(value, "asdfasdfasdfawqeasdf");
        atr->name = name;
        atr->value = value;
        setAttribute(image, RECT, 0, atr);
    }
    if (true) {
        printf("isvalid: %d\n", validateSVGimage(image, "testFilesA2/svg.xsd"));

        if (validateSVGimage(image, "testFilesA2/svg.xsd") == 1) {
            writeSVGimage(image, "output.svg");
        }
        
        
    }
	
	deleteSVGimage(image);
	xmlCleanupParser();
}

int oldmain(int argc, char **argv) {
	putsError("createSVGimage");
	int result = 0;
	SVGimage* img2 = NULL;
	
//	SVGimage* img1 = createValidSVGimage("Wink_Brutal_Test_2.svg", "testFilesA2/svg.xsd");
	SVGimage* img1 = createSVGimage("hen_and_chicks.svg");
	
	if(!img1) {
		puts("\timg1 is NULL");
	}
	
	if(img1) {
		putsError("numAttr for the image");
		printf("\tnumAttr(img) = %d\n", numAttr(img1));
	}
	
		putsError("getGroups length");
		List* g = getGroups(img1);
	if(img1) {
		result = getLength(g);
		printf("\tthe number of groups is: %d\n", result);
		freeList(g);
	}
	
	putsError("getRects length");
	List* r = getRects(img1);
	if(img1) {
		printf("\tthe number of rectangles is: %d\n", getLength(r));
		freeList(r);
	}
	
	putsError("getCircles length");
	List* c = getCircles(img1);
	if(img1) {
		printf("\tthe number of circles is: %d\n", getLength(c));
		freeList(c);
	}
	
	putsError("getPaths length");
	List* p = getPaths(img1);
	if(img1) {
		printf("\tthe number of paths is: %d\n", getLength(p));
		freeList(p);
	}
	
	putsError("circListToJSON string");
	char* circtojason = circListToJSON(img1->circles);
	printf("\tcircleToJSON : %s\n", circtojason);
	free(circtojason);
	
	putsError("pathToJSON string");
	char* pathListToJaSON = pathListToJSON(img1->paths);
	printf("\tpathToJSON : %s\n", pathListToJaSON);
	free(pathListToJaSON);
	
	putsError("SVGtoJSON string");
	char* svgtojason = SVGtoJSON(img1);
	printf("\tSVGtoJSON : %s\n", svgtojason);
	free(svgtojason);

	putsError("validateSVGimage");
	if(validateSVGimage(img1, "testFilesA2/svg.xsd")) {
		printf("validateSVGimage = true (:");
	} else {
		printf("validateSVGimage = false ):");
	}
	
	if(img1) {
		putsError("writeSVGimage (writes the svg you opened to file)");
		printf("\twrite svg = %d\n", writeSVGimage(img1, "willTest.svg"));

		putsError("opens the svg you wrote to file");
		img2 = createSVGimage("willTest.svg");
		
		putsError("validates the svg you wrote to file");
		if(validateSVGimage(img2, "testFilesA2/svg.xsd")) {
			printf("validateSVGimage = true (:");
		} else {
			printf("validateSVGimage = false ):");
		}
	}
	
	putsError("frees");
	deleteSVGimage(img1);
	deleteSVGimage(img2);
	xmlCleanupParser();
	
    return 0;
}

void hen_and_chicksToFile() {
	SVGimage* img1 = createSVGimage("hen_and_chicks.svg");
	
	List* l = getPaths(img1);
	char* pathListToJaSON = pathListToJSON(l);
	printf("%s", pathListToJaSON);
	free(pathListToJaSON);
	freeList(l);
/*
	putsError("SVGtoJSON string");
	char* svgtojason = SVGtoJSON(img1);
	printf("\tSVGtoJSON : %s\n", svgtojason);
	free(svgtojason);
*/
	deleteSVGimage(img1);
	xmlCleanupParser();
	
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
	printf("\033[0;3%dm", testingNumber%6 + 1);
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
