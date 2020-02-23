#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

#define SCH "testFilesA2/svg.xsd"

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
void mainTestThing(char* fileName1, char* fileName2);
int minDriver();


SVGimage* SVGtest(char* fileName) {

    SVGimage* testImg;
    testImg = createSVGimage(fileName);
    return testImg;
}

SVGimage* SVGtestA2 (char* fileName, char* schemaName) {
    SVGimage* testImg;
    testImg = createValidSVGimage(fileName, schemaName);
    
    return testImg;
}

void JSONTest() {

    char* testString = (char*)malloc(sizeof(char)*41);
    char* testString2 = (char*)malloc(sizeof(char)*41);
    char* testString3 = (char*)malloc(sizeof(char)*33);
    SVGimage* test;
    Rectangle* rect;
    Circle* circ;

    strcpy (testString, "{\"title\":\"titleVal\",\"descr\":\"descrVal\"}");
    strcpy (testString2, "{\"x\":1,\"y\":2,\"w\":19,\"h\":15,\"units\",\"cm\"}");
    strcpy (testString3, "{\"cx\":3,\"cy\":3,\"r\":3,\"units\":\"\"}");

    test = JSONtoSVG(testString);
    rect = JSONtoRect(testString2);
    circ = JSONtoCircle(testString3);
    printf ("%s\n", SVGimageToString(test));
    printf ("%s\n", rectangleToString(rect));
    printf ("%s\n", circleToString(circ));
    free(testString);
    free(testString2);
    free(testString3);
    deleteCircle(circ);
    deleteRectangle(rect);
    deleteSVGimage(test);
}

void groupTest(SVGimage* givenImg) {
    char* tmpString;
    List* tmpList;

    printf ("----------Group Test----------\n");
    tmpString = groupToJSON(getFromBack(givenImg->groups));
    printf ("%s\n", tmpString);
    free(tmpString);

    tmpString = SVGtoJSON(givenImg);
    printf ("%s\n", tmpString);
    free(tmpString);

    tmpString = attrListToJSON(givenImg->otherAttributes);
    printf ("%s\n", tmpString);
    free(tmpString);

    tmpList = getCircles(givenImg);
    tmpString = circListToJSON(tmpList);
    printf ("%s\n", tmpString);
    freeList(tmpList);
    free(tmpString);

    tmpList = getRects(givenImg);
    tmpString = rectListToJSON(tmpList);
    printf ("%s\n", tmpString);
    freeList(tmpList);
    free(tmpString);

    tmpList = getPaths(givenImg);
    tmpString = pathListToJSON(tmpList);
    printf ("%s\n", tmpString);
    freeList(tmpList);
    free(tmpString);

    tmpList = getGroups(givenImg);
    tmpString = groupListToJSON(tmpList);
    printf ("%s\n", tmpString);
    freeList(tmpList);
    free(tmpString);

}

void attributeTest () {

    printf ("----------Attribute Test----------\n");
    Attribute* tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
    Attribute* tmpAttribute2 = (Attribute*)malloc(sizeof(Attribute));
    tmpAttribute->name = (char*)malloc(sizeof(char)*strlen("Min") + 1);
    tmpAttribute->value = (char*)malloc(sizeof(char)*strlen("20") + 1);
    tmpAttribute2->name = (char*)malloc(sizeof(char)*strlen("Dame") + 1);
    tmpAttribute2->value = (char*)malloc(sizeof(char)*strlen("19") + 1);
    strcpy(tmpAttribute->name, "Min");
    strcpy(tmpAttribute->value, "20");
    strcpy(tmpAttribute2->name, "Dame");
    strcpy(tmpAttribute2->value, "19");

    char* testString;
    char* testString2;
    int compLen;

    testString = attributeToString (tmpAttribute);
    printf ("%s\n", testString);
    testString2 = attributeToString (tmpAttribute2);
    printf ("%s\n", testString2);
    compLen = compareAttributes(tmpAttribute, tmpAttribute2);
    printf ("%d\n", compLen);

    free(testString);
    free(testString2);

    testString = attrToJSON(tmpAttribute);
    printf ("%s\n", testString);
    free(testString);

    testString = attrToJSON(tmpAttribute2);
    printf ("%s\n", testString);
    free(testString);

    deleteAttribute(tmpAttribute);
    deleteAttribute(tmpAttribute2);
}

void rectTest() {
    
    printf ("----------Rectangle Test----------");
    Rectangle* testRect = (Rectangle*)malloc(sizeof(Rectangle));
    Rectangle* testRect2 = (Rectangle*)malloc(sizeof(Rectangle));
    char tmpStr[100];
	int memLen;

    testRect->x = 5;
    testRect->y = 5;
    testRect->width = 10;
    testRect->height = 10;
    strcpy(testRect->units, "testRect");

    testRect2->x = 3;
    testRect2->y = 3;
    testRect2->width = 9;
    testRect2->height = 9;
    strcpy(testRect2->units, "testRect2");

    List* attriList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    List* attriList2 = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    Attribute* tmpAttribute;

    for (int i = 0; i < 4; i++){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList, (void*)tmpAttribute);
	}
    for (int i = 3; i >= 0; i--){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList2, (void*)tmpAttribute);
	}

    testRect->otherAttributes = attriList;
    testRect2->otherAttributes = attriList2;

    char* testString = rectangleToString(testRect);
    char* testString2 = rectangleToString(testRect2);
    int compLen;

    printf ("\n%s", testString);
    printf ("\n%s\n", testString2);
    compLen = compareRectangles(testRect, testRect2);
    printf ("Compare value: %d\n", compLen);

    free(testString);
    free(testString2);

    testString = rectToJSON(testRect);
    printf ("%s\n", testString);
    free(testString);
    
    testString = rectToJSON(testRect2);
    printf ("%s\n", testString);
    free(testString);

    deleteRectangle(testRect);
    deleteRectangle(testRect2);
}

void circTest() {
    
    printf ("----------Circle Test----------");
    Circle* testCirc = (Circle*)malloc(sizeof(Circle));
    Circle* testCirc2 = (Circle*)malloc(sizeof(Circle));
    char tmpStr[100];
	int memLen;

    testCirc->cx = 5;
    testCirc->cy = 5;
    testCirc->r = 10;
    strcpy(testCirc->units, "testCirc");

    testCirc2->cx = 3;
    testCirc2->cy = 3;
    testCirc2->r = 9;
    strcpy(testCirc2->units, "testCirc2");

    List* attriList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    List* attriList2 = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    Attribute* tmpAttribute;

    for (int i = 0; i < 4; i++){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList, (void*)tmpAttribute);
	}
    for (int i = 3; i >= 0; i--){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList2, (void*)tmpAttribute);
	}

    testCirc->otherAttributes = attriList;
    testCirc2->otherAttributes = attriList2;

    char* testString = circleToString(testCirc);
    char* testString2 = circleToString(testCirc2);
    int compLen;

    printf ("\n%s", testString);
    printf ("\n%s\n", testString2);
    compLen = compareCircles(testCirc, testCirc2);
    printf ("Compare value: %d\n", compLen);

    free(testString);
    free(testString2);

    testString = circleToJSON(testCirc);
    printf ("%s\n", testString);
    free(testString);

    testString = circleToJSON(testCirc2);
    printf ("%s\n", testString);
    free(testString);

    deleteCircle(testCirc);
    deleteCircle(testCirc2);
}

void pathTest() {

    printf ("----------Path Test----------");
    Path* testPath = (Path*)malloc(sizeof(Path));
    Path* testPath2 = (Path*)malloc(sizeof(Path));
    char tmpStr[100];
	int memLen;

    testPath->data = (char*)malloc(sizeof(char)*strlen("Pathdata") + 1);
    testPath2->data = (char*)malloc(sizeof(char)*strlen("Pathdata2") + 1);
    strcpy(testPath->data, "Pathdata");
    strcpy(testPath2->data, "Pathdata2");

    List* attriList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    List* attriList2 = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    Attribute* tmpAttribute;

    for (int i = 0; i < 4; i++){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList, (void*)tmpAttribute);
	}
    for (int i = 3; i >= 0; i--){

        tmpAttribute = (Attribute*)malloc(sizeof(Attribute));
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->name, tmpStr);
		
		sprintf(tmpStr, "Value%d", i);
		memLen = strlen(tmpStr)+2;
		tmpAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpAttribute->value, tmpStr);
	
		insertBack(attriList2, (void*)tmpAttribute);
	}

    testPath->otherAttributes = attriList;
    testPath2->otherAttributes = attriList2;

    char* testString = pathToString(testPath);
    char* testString2 = pathToString(testPath2);
    int compLen;

    printf ("\n%s", testString);
    printf ("\n%s\n", testString2);
    compLen = comparePaths(testPath, testPath2);
    printf ("Compare value: %d\n", compLen);

    free(testString);
    testString = pathToJSON(testPath);
    printf ("%s\n", testString);

    free(testString);
    testString = pathToJSON(testPath2);
    printf ("%s\n", testString);

    free(testString);
    free(testString2);

    deletePath(testPath);
    deletePath(testPath2);
}

/**
 * Simple main for testing of library
 */
int main() {
/*
	char* filename = "quad01.svg";

    SVGimage* testImg = createSVGimage(filename);
	
	// create an attribute
	Attribute* newA = malloc(sizeof(Attribute));
	newA->name = calloc(64, sizeof(char));
	newA->value = calloc(64, sizeof(char));
	strcpy(newA->name, "cx");
	strcpy(newA->value, "200");

	Attribute* newA1 = malloc(sizeof(Attribute));
	newA1->name = calloc(64, sizeof(char));
	newA1->value = calloc(64, sizeof(char));
	strcpy(newA1->name, "dog");
	strcpy(newA1->value, "200");
	
	// attempt setting the attribute (replace)
	setAttribute(testImg, CIRC, 0, newA);
	
	// attempt setting an attribute as NULL
	setAttribute(testImg, CIRC, 0, NULL);
	setAttribute(testImg, SVG_IMAGE, 0, NULL);
	setAttribute(testImg, PATH, 0, NULL);
	
	// attempt setting the attribute (replace)
	setAttribute(testImg, CIRC, 0, newA1);
	
	//
	
	
    // delete svg image 
	deleteSVGimage(testImg);
*/


	mainTestThing("quad01.svg", SCH);

    return 0;
}

int minDriver() {

    SVGimage* test = SVGtestA2("quad01.svg", "testFilesA2/svg.xsd");
	
	
    mainTestThing("quad01_A2.svg", "testFilesA2/svg.xsd");


    attributeTest();
    rectTest();
    pathTest();
    circTest();
    if (test == NULL) {
        printf ("object null\n");
    }
    groupTest(test);

    //JSONTest();

    deleteSVGimage(test);


    return 0;
}


void mainTestThing(char* fileName1, char* fileName2) {

    SVGimage* testImg;
    char* testString;
    char* testString2;
    char* testString3;
    char* testString4;
    char* testString5;
    List* rects;
    List* circs;
    List* paths;
    List* groups;
    int numAttributes;
    int numRects;
    int memLen;
    Attribute* newAttribute;
    Attribute* newAttribute2;
    Attribute* newAttribute3;
    Attribute* newAttribute4;
    Attribute* newAttribute5;
    Attribute* fakeAttribute = NULL;
    Rectangle* newRect;
    Circle* newCircle;
    Path* newPath;
    Group* newGroup = NULL;
    char tmpStr[100];

    //Function
    //attributeTest();
    //rectTest();
    //circTest();
    //pathTest();
    //groupTest();
    printf ("----------Main Test----------\n");

    testImg = SVGtestA2(fileName1, fileName2);
    if (testImg != NULL) {
        testString = SVGimageToString(testImg);
        printf ("%s\n", testString);
        printf ("--------------------------\n");
        rects = getRects(testImg);
        circs = getCircles(testImg);
        paths = getPaths(testImg);
        groups = getGroups(testImg);
        numAttributes = numAttr(testImg);
        printf ("==============================\n");
        printf ("%d attributes\n", numAttributes);
        printf ("%d groups\n", getLength(groups));
        printf ("%d circs\n", getLength(circs));
        printf ("%d rects\n", getLength(rects));
        printf ("%d paths\n", getLength(paths));
        free(testString);
        freeList(rects);
        freeList(circs);
        freeList(paths);
        freeList(groups);

        newAttribute = (Attribute*)calloc(1, sizeof(Attribute));
        newAttribute2 = (Attribute*)calloc(1, sizeof(Attribute));
        newAttribute3 = (Attribute*)calloc(1, sizeof(Attribute));
        newAttribute4 = (Attribute*)calloc(1, sizeof(Attribute));
        newAttribute5 = (Attribute*)calloc(1, sizeof(Attribute));

        newRect = (Rectangle*)calloc(1, sizeof(Rectangle));
        newCircle = (Circle*)calloc(1, sizeof(Circle));
        newPath = (Path*)calloc(1, sizeof(Path));/////////////////////////////

        strcpy(tmpStr, "width");
		memLen = strlen(tmpStr)+2;
		newAttribute->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute->name, tmpStr);

		strcpy(tmpStr, "90000");
		memLen = strlen(tmpStr)+2;
		newAttribute->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute->value, tmpStr);

        testString = attrToJSON(newAttribute);
        printf ("%s\n", testString);
        free(testString);

        strcpy(tmpStr, "r");
		memLen = strlen(tmpStr)+2;
		newAttribute2->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute2->name, tmpStr);

		strcpy(tmpStr, "60");
		memLen = strlen(tmpStr)+2;
		newAttribute2->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute2->value, tmpStr);

        testString = attrToJSON(newAttribute2);
        printf ("%s\n", testString);
        free(testString);

        strcpy(tmpStr, "data");
		memLen = strlen(tmpStr)+2;
		newAttribute3->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute3->name, tmpStr);
		
		strcpy(tmpStr, "100 4378 32190231");
		memLen = strlen(tmpStr)+2;
		newAttribute3->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute3->value, tmpStr);

        strcpy(tmpStr, "fill");
		memLen = strlen(tmpStr)+2;
		newAttribute4->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute4->name, tmpStr);
		
		strcpy(tmpStr, "all");
		memLen = strlen(tmpStr)+2;
		newAttribute4->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute4->value, tmpStr);

        strcpy(tmpStr, "title");
		memLen = strlen(tmpStr)+2;
		newAttribute5->name = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute5->name, tmpStr);
		
		strcpy(tmpStr, "10px");
		memLen = strlen(tmpStr)+2;
		newAttribute5->value = (char*)malloc(sizeof(char)*memLen);
		strcpy(newAttribute5->value, tmpStr);

        newRect->x = 30;
        newRect->y = 30;
        newRect->width = 100;
        newRect->height = 100;
        newRect->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

        newCircle->cx = 30;
        newCircle->cy = 30;
        newCircle->r = 30;
        newCircle->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

        newPath->data = (char*)malloc(sizeof(char)*17 + 1);
        strcpy(newPath->data, "30 30 30 30 30 30");
        newPath->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

        setAttribute(testImg, RECT, 0, fakeAttribute);
        setAttribute(testImg, RECT, 0, newAttribute);
        setAttribute(testImg, CIRC, 0, newAttribute2);
        setAttribute(testImg, PATH, 0, newAttribute3);
        setAttribute(testImg, GROUP, 0, newAttribute4);
        setAttribute(testImg, SVG_IMAGE, 0, newAttribute5);

        addComponent(testImg, GROUP, newGroup);
        addComponent(testImg, RECT, newRect);
        addComponent(testImg, CIRC, newCircle);
        addComponent(testImg, PATH, newPath);

/*
        if (writeSVGimage(testImg, "test") == false) {
            printf ("failed write\n");
        }
        if (validateSVGimage(testImg, fileName2) == false){
            printf ("validation failed\n");
        } else {
            printf ("validation success\n");
        }
*/

        deleteSVGimage(testImg);
    }

	return;
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
	
	SVGimage* image = createValidSVGimage("takethat", "testFilesA2/svg.xsd");
	

	Attribute* atr = malloc(sizeof(Attribute));
	char* name = malloc(50);
	char* value = malloc(50);
	strncpy(name, "asdf", 40);
	strncpy(value, "asdfasdfasdfawqeasdf", 40);
	atr->name = name;
	atr->value = value;
	setAttribute(image, RECT, 0, atr);

	printf("isvalid: %d\n", validateSVGimage(image, "testFilesA2/svg.xsd"));

	if (validateSVGimage(image, "testFilesA2/svg.xsd") == 1) {
		writeSVGimage(image, "output.svg");
	}
	
	
	if(image == NULL) {
		deleteAttribute(atr);
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


