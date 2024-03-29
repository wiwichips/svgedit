/******************************************************************************
 ******************************************************************************
 **	Author: 	Will Pringle following Dennis Nikitenko's API 				 **
 ** Student ID:	1056636														 **
 **																			 **
 ** Date: 		January 29 2020												 **
 **																			 **
 ** Citations:	(1)	libXmlExample.c written by Dodji Seketeli				 **
 **					used lines: 31, 33, 34, 45, 46, 48, 49, 50.				 **
 **				(2)	LinkedListAPI.h written by CIS*2750 S18					 **
 **					used lines:322, 326, 328, 329, 334, 337.				 **
 ******************************************************************************
 ******************************************************************************/

#include "SVGParser.h"
#include "helper.h"
#include <math.h>
#include <strings.h>

#define PI 3.14159265359

// functions for a3
char* printHelloWorld(int num) {
	char* string = NULL;
	
	string = calloc(20, sizeof(char));
	strcpy(string, "hello world");
	printf("num = %d\n", num);
	
	return string;
}

char* JSONcreateValidSVG(char* fileName, char* schemaFile) {
	char* JSONstring = NULL;
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	JSONstring = SVGtoJSON(image);
	
	deleteSVGimage(image);
	
	return JSONstring;
}

bool validateSVGfile(char* fileName, char* schemaFile) {
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	bool result = validateSVGimage(image, schemaFile);
	deleteSVGimage(image);
	return result;
}

bool createNewSVGimageAndWriteToFile(char* schemaFile, char* fileName, char* title, char* description) {
	bool result = true;
	
	SVGimage* image = createEmptySVG();
	
	// copy over the description and the title
	strcpy(image->description, description);
	strcpy(image->title, title);
	
	//append a .svg to the end if there isn't one already
	if(strlen(fileName) > 4 && !strcmp(&(fileName[strlen(fileName) - 4]), ".svg")) {
		// printf("fileName > 4 && !strcmp(&(fileName[strlen(fileName) - 4]), \n");
	} else {
		// allocate new memory
		char* temp = calloc(strlen(fileName) + 5, sizeof(char));
		strcpy(temp, fileName);
		strcat(temp, ".svg");
		fileName = temp;
	}
	
	// check if its valid
	result = validateSVGimage(image, schemaFile);
	
	if(result == false) {
		deleteSVGimage(image);
		return false;
	}
	
	result = writeSVGimage(image, fileName);
	
	return result;
}

char* getTitle(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "{}");
	}
	else { // otherwise
		result = calloc(strlen(image->title) + 10, sizeof(char));
		strcpy(result, image->title);
		// result[0] = 'A';
		
	}
	
	deleteSVGimage(image);
	
	return result;
}



char* getDescription(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "{}");
	}
	else { // otherwise
		result = calloc(strlen(image->description) + 10, sizeof(char));
		strcpy(result, image->description);
	}
	
	deleteSVGimage(image);
	
	return result;
}

char* circleToJSONfromValidFile(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "[]");
	}
	else { // otherwise
		result = circListToJSON(getCircles(image));
	}
	
	deleteSVGimage(image);
	
	return result;
}

char* rectToJSONfromValidFile(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "[]");
	}
	else { // otherwise
		result = rectListToJSON(getRects(image));
	}
	
	deleteSVGimage(image);
	
	return result;
}


char* pathToJSONfromValidFile(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "[]");
	}
	else { // otherwise
		result = pathListToJSON(getPaths(image));
	}
	
	deleteSVGimage(image);
	
	return result;
}


char* groupToJSONfromValidFile(char* fileName, char* schemaFile) {
	char* result = NULL;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		result = calloc(4, sizeof(char));
		strcpy(result, "[]");
	}
	else { // otherwise
		result = groupListToJSON(getGroups(image));
	}
	
	deleteSVGimage(image);
	
	return result;
}



bool scaleShapeFromFile(char* fileName, char* schemaFile, float scaleFactor, char* shapeType) {
	bool result = false;
	elementType e;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		return false;
	}
	
	// find the type
	if(!strcasecmp(shapeType, "circle")) {
		e = CIRC;
	} else if (!strcasecmp(shapeType, "rectangle")) {
		e = RECT;
	} else if(!strcasecmp(shapeType, "imageimage")) {
		e = SVG_IMAGE;
		
	} else {
		// incorrect type
		deleteSVGimage(image);
		return false;
	}
	
	// attempt to scale the shape
	result = findShapeToScale(e, scaleFactor, image);
	
	if(result == true) {
		
		result = writeSVGimage(image, fileName);
puts("write svg image");
	}
	
	deleteSVGimage(image);
	
	return result;
}

bool findShapeToScale(elementType e, float scaleFactor, SVGimage* image) {
	if(e == SVG_IMAGE) {
		// scale all shapes TODO
		return false;
	}
	
	
	List* list = NULL;
	ListIterator itr;
	int i = 0;
	
	// get list of either all rectagles or all circles
	if(e == CIRC) {
		list = getCircles(image);
		
	} else if (e == RECT) {
		list = getRects(image);
		
	} else {
		return false;
	}
	
	// set list iterator
	itr = createIterator(list);
	
	// Cycle through data
	if(e == CIRC) {
		for(Circle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			scaleShape(CIRC, data, scaleFactor);
			
			i++;
		
		}
	}
	else{
		for(Rectangle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			scaleShape(RECT, data, scaleFactor);
			
			i++;
		
		}
	}
	
	return true;
}

bool scaleShape(elementType e, void* data, float scaleFactor) {
	
	if(e == CIRC) {
		// ((Circle*) data)->cx *= scaleFactor;
		// ((Circle*) data)->cy *= scaleFactor;
		((Circle*) data)->r *= scaleFactor;
puts("Circle scale");
		
	} else if (e == RECT) {
		// ((Rectangle*) data)->x *= scaleFactor;
		// ((Rectangle*) data)->y *= scaleFactor;
		((Rectangle*) data)->width *= scaleFactor;
		((Rectangle*) data)->height *= scaleFactor;
puts("rect scale");
	}
	
	return true;
}


void* getDataFromIndex(List* list, int index) {
	ListIterator itr;
	int i = 0;
	
	itr = createIterator(list);
	
printf("index = %d\n", index);
	
	for(void* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		if(i == index) {
printf("index %d = i %d\n", index, i);
			return data;
		}
		
		i++;
	}
	
	return NULL;
}

// attrListToJSON(list)

char* returnInformationAboutShape(char* fileName, char* schemaFile, char* shapeType, int number) {
	char* string = calloc(5, sizeof(char));
	strcpy(string, "bad");
	int index = number;
	
	// try to open SVG, return "bad" if doesn't work
	// elementType e;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) { // if image invlaid then return empty array
		string = calloc(5, sizeof(char));
		strcpy(string, "bad");
		return string;
	}
	
	// if its an image type, then just return json list of attributes for image
	if(!strcasecmp(shapeType, "svg") || !strcasecmp(shapeType, "image") || !strcasecmp(shapeType, "img") || !strcasecmp(shapeType, "SVGimage")) {
		
		// temporarily add new attributes 
		insertBack(image->otherAttributes, addAttribute("title", image->title));
		insertBack(image->otherAttributes, addAttribute("description", image->description));
		insertBack(image->otherAttributes, addAttribute("namespace", image->namespace));
		
		string = attrListToJSON(image->otherAttributes);
		deleteSVGimage(image);
		return string;
	}
	
	else if(!strcasecmp(shapeType, "circle") || !strcasecmp(shapeType, "circ")) {
		if(index > getLength(getCircles(image)) || index < 0) {
			// deleteSVGimage(image);
			return string;
		} else {
// puts("Circle* circ = getDataFromIndex(getCircles(image), index);");
			Circle* circ = getDataFromIndex(getCircles(image), index);
			printf("circ = %p\n", circ);
			
			if(circ == NULL) { // if image invlaid then return empty array
				string = calloc(5, sizeof(char));
				strcpy(string, "bad");
				return string;
			}
			
			// temporarily add new attributes 
			insertBack(circ->otherAttributes, addAttribute("cx", floatToString(circ->cx)));
			insertBack(circ->otherAttributes, addAttribute("cy", floatToString(circ->cy)));
			insertBack(circ->otherAttributes, addAttribute("r", floatToString(circ->r)));
			
			string = attrListToJSON(circ->otherAttributes);
		}
	}
	
	else if(!strcasecmp(shapeType, "rectangle") || !strcasecmp(shapeType, "rect")) {
		if(index > getLength(getRects(image)) || index < 0) {
			// deleteSVGimage(image);
			return string;
		} else {
// puts("Rectangle* circ = getDataFromIndex(getCircles(image), index);");
			Rectangle* circ = getDataFromIndex(getRects(image), index);
			printf("rect = %p\n", circ);
			
			if(circ == NULL) { // if image invlaid then return empty array
				string = calloc(5, sizeof(char));
				strcpy(string, "bad");
				return string;
			}
			
			
			// temporarily add new attributes 
			insertBack(circ->otherAttributes, addAttribute("x", floatToString(circ->x)));
			insertBack(circ->otherAttributes, addAttribute("y", floatToString(circ->y)));
			insertBack(circ->otherAttributes, addAttribute("width", floatToString(circ->width)));
			insertBack(circ->otherAttributes, addAttribute("height", floatToString(circ->height)));
			
			// set string to json
			string = attrListToJSON(circ->otherAttributes);
		}
	}
	
	else if(!strcasecmp(shapeType, "path")) {
		if(index > getLength(getRects(image)) || index < 0) {
			// deleteSVGimage(image);
			return string;
		} else {
			Path* circ = getDataFromIndex(getPaths(image), index);
			printf("path = %p\n", circ);
			
			if(circ == NULL) { // if image invlaid then return empty array
				string = calloc(5, sizeof(char));
				strcpy(string, "bad");
				return string;
			}
			
			// temporarily add new attributes 
			insertBack(circ->otherAttributes, addAttribute("d", circ->data));
			
			string = attrListToJSON(circ->otherAttributes);
		}
	}
	
	// else if for gorups
	else if(!strcasecmp(shapeType, "group")) {
		if(index > getLength(getGroups(image)) || index < 0) {
			// deleteSVGimage(image);
			return string;
		} else {
			Group* circ = getDataFromIndex(getGroups(image), index);
			printf("path = %p\n", circ);
			
			if(circ == NULL) { // if image invlaid then return empty array
				string = calloc(5, sizeof(char));
				strcpy(string, "bad");
				return string;
			}
						
			string = attrListToJSON(circ->otherAttributes);
		}
	}
	
	else {
		string = calloc(5, sizeof(char));
		strcpy(string, "bad");
		return string;
	}
	
	
	
	return string;
}

bool updateAttributeFromFile(char* fileName, char* schemaFile, char* shapeType, int number, char* name, char* value) {
	int index = number;
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image == NULL) {
puts("image == null");
		return false;
	}
	
	// if its an image type, then just return json list of attributes for image
	if(!strcasecmp(shapeType, "svg") || !strcasecmp(shapeType, "image") || !strcasecmp(shapeType, "img") || !strcasecmp(shapeType, "SVGimage")) {
puts("svg");
		setAttribute(image, SVG_IMAGE, index, addAttribute(name, value));

	}

	else if(!strcasecmp(shapeType, "circle") || !strcasecmp(shapeType, "circ")) {
puts("circle");
		if(index > getLength(getCircles(image)) || index < 0) {
			// deleteSVGimage(image);
puts("index > getLength(getcircles(image)....)");
			return false;
		} else {

puts("index is permissible, now calling setattributes");
			setAttribute(image, CIRC, index, addAttribute(name, value));

		}
	}
	
	else if(!strcasecmp(shapeType, "rectangle") || !strcasecmp(shapeType, "rect")) {
		if(index > getLength(getRects(image)) || index < 0) {
			// deleteSVGimage(image);
			return false;
		} else {
			setAttribute(image, RECT, index, addAttribute(name, value));
		}
	}
	
	else if(!strcasecmp(shapeType, "path")) {
		if(index > getLength(getRects(image)) || index < 0) {
			// deleteSVGimage(image);
			return false;
		} else {
			setAttribute(image, PATH, index, addAttribute(name, value));
		}
	}
	
	// else if for gorups
	else if(!strcasecmp(shapeType, "group")) {
		if(index > getLength(getGroups(image)) || index < 0) {
			// deleteSVGimage(image);
			return false;
		} else {
			setAttribute(image, GROUP, index, addAttribute(name, value));
		}
	}
	
	// validate it
	if(!validateSVGimage(image, schemaFile)) {
		
		return false;
	}
	
	// write it to file
	bool result = writeSVGimage(image, fileName);
	
	return result;
}



void changeTitleFromFile(char* fileName, char* schemaFile, char* newTitle) {	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image && newTitle && strlen(newTitle) < 256) { // if image is valid change title
		strncpy (image->title, newTitle, 255);
		
		// write it after changing the image title
		writeSVGimage(image, fileName);
	}
	
	deleteSVGimage(image);
	
	return;
}

void changeDescriptionFromFile(char* fileName, char* schemaFile, char* newDescription)
 {	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	if(image && newDescription && strlen(newDescription) < 256) { // if image is valid change title
		strncpy (image->description, newDescription, 255);
		
		// write it after changing the image title
		writeSVGimage(image, fileName);
	}
	
	deleteSVGimage(image);
	
	return;
}

bool addCircleFromFile(char* fileName, char* schemaFile, float cx, float cy, float r, char* units, char* fill) {
	bool result = false;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
	// if image is null return false
	if(!image) {
		return false;
	}
	
	// check if uniuts are greater than 49 chars, in case return false
	if(strlen(units) > 49) {
		return false;
	}
	
	// check if radius is positive
	if(r < 0) {
		return false;
	}
	
	// create a circle struct
	Circle* newCircle = calloc(1, sizeof(Circle));
	
	// populate it
	newCircle->cx = cx;
	newCircle->cy = cy;
	newCircle->r = r;
	strcpy(newCircle->units, units);
	newCircle->otherAttributes = initializeList(&rectangleToString, &deleteAttribute, &comparePaths);
	
	// add fill as an otherAttribute if it is sent
	if(strlen(fill) > 0) {
		insertBack(newCircle->otherAttributes, addAttribute("fill", fill));
	}
	
	// insert the cirlce into the svgImage
	insertBack(image->circles, newCircle);
	
	// check if the image is still valid after adding the circle
	if(validateSVGimage(image, schemaFile)) {
		result = true;
		
		// write it to file if it is valid
		writeSVGimage(image, fileName);
	}
	
	// delete the image
	deleteSVGimage(image);
	
	// return boolean
	return result;
}

bool addRectangleFromFile(char* fileName, char* schemaFile, float x, float y, float width, float height, char* units, char* fill) {
	bool result = false;
	
	// create the svg based off of the filename
	SVGimage* image = createValidSVGimage(fileName, schemaFile);
	
// printf("fileName = %s\n", fileName);
	
	// if image is null return false
	if(!image) {
// puts("!image");
		return false;
	}
	
	// check if uniuts are greater than 49 chars, in case return false
	if(strlen(units) > 49) {
// puts("strlen(units) > 49");
		return false;
	}
	
	// check if radius is positive
	if(width < 0 || height < 0) {
// puts("width < 0 || height < 0");
		return false;
	}
	
	
//debugging
// printf("x = %f\ny = %f\n, height = %f\n units = %s\nfill = %s\n", x, y, height, units, fill);
	
	// create a Rectangle struct
	Rectangle* newRectangle = calloc(1, sizeof(Rectangle));
	
	// populate it
	newRectangle->x = x;
	newRectangle->y = y;
	newRectangle->width = width;
	newRectangle->height = height;
	strcpy(newRectangle->units, units);
	newRectangle->otherAttributes = initializeList(&rectangleToString, &deleteAttribute, &comparePaths);
	
	// add fill as an otherAttribute if it is sent
	if(strlen(fill) > 0) {
		insertBack(newRectangle->otherAttributes, addAttribute("fill", fill));
	}
	
	// insert the cirlce into the svgImage
	insertBack(image->rectangles, newRectangle);
	
	// check if the image is still valid after adding the circle
	if(validateSVGimage(image, schemaFile)) {
		result = true;
		
		// write it to file
		writeSVGimage(image, fileName);
		
	}
	
// puts("\t\tabout to delte");
	
	// delete the image
	deleteSVGimage(image);
	
	// return boolean
	return result;
}





// A2 bonus functions
SVGimage* createEmptySVG() {
	// allocate space for the image
	SVGimage* image = malloc(sizeof(SVGimage));
	
	// copy the namespace for SVGs
	strcpy(image->namespace, "http://www.w3.org/2000/svg");
	
	// set title and description to ""
	strcpy(image->description, "");
	strcpy(image->title, "");
	
	// create empty lists
	image->rectangles = initializeList(&rectangleToString, &deleteRectangle, &comparePaths);
	image->circles = initializeList(&rectangleToString, &deleteCircle, &comparePaths);
	image->paths = initializeList(&rectangleToString, &deletePath, &comparePaths);
	image->groups = initializeList(&groupToString, &deleteGroup, &comparePaths);
	image->otherAttributes = initializeList(&rectangleToString, &deleteAttribute, &comparePaths);
	
	// create a viewbox attribute
	Attribute* vb = calloc(sizeof(Attribute), 1);
	vb->name  = calloc(strlen("viewBox") + 5, sizeof(char));
	strcpy(vb->name, "viewBox");
	vb->value  = calloc(strlen("0 0 1200 600") + 5, sizeof(char));
	strcpy(vb->value, "0 0 1200 600");
	
	insertBack(image->otherAttributes, vb);
	
	// return it
	return image;
}

SVGimage* JSONtoSVG(const char* svgString) {
	char* str = calloc(strlen(svgString) + 2, sizeof(char));
	strcpy(str, svgString);
	
	const char s[4] = "\"";
	char* token;
	
	SVGimage* image = createEmptySVG();

	// generate first token
	token = strtok(str, s);

	for(int i = 0; token != NULL; i++) {
		// printf("%d\t%s\n", i, token );
		if(i == 3) {
			strcpy(image->title, token);
		} else if(i == 7) {
			strcpy(image->description, token);
		}

		token = strtok(NULL, s);
	}
	
	free(str);

	return image;
}

Rectangle* JSONtoRect(const char* svgString) {
	char* str = calloc(strlen(svgString) + 2, sizeof(char));
	strcpy(str, svgString);
	
	const char s[4] = "\":,";
	char* token;
	
	Rectangle* rect = malloc(sizeof(Rectangle));

	// generate first token
	token = strtok(str, s);

	for(int i = 0; token != NULL; i++) {
		printf("%d\t%s\n", i, token );
		
		if(i == 2) { // xval
			rect->x = strtof(token, NULL);
			
		}
		if(i == 4) { // yval
			rect->y = strtof(token, NULL);
			
		}
		if(i == 6) { // wval
			rect->width = strtof(token, NULL);
			
		}
		if(i == 8) { // hval
			rect->height = strtof(token, NULL);
			
		}
		if(i == 10) { // units
			strcpy(rect->units, token);
		}
		
		token = strtok(NULL, s);
	}
	
	free(str);

	return rect;
}

Circle* JSONtoCircle(const char* svgString) {
	return NULL;
}

// A2 new functions
/** Function to create an SVG object based on the contents of an SVG file.
 * This function must validate the XML tree generated by libxml against a SVG schema file
 * before attempting to traverse the tree and create an SVGimage struct
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
       Schema file name is not NULL/empty, and represents a valid schema file
 *@post Either:
        A valid SVGimage has been created and its address was returned
		or 
		An error occurred, or SVG file was invalid, and NULL was returned
 *@return the pinter to the new struct or NULL
 *@param fileName - a string containing the name of the SVG file
**/
SVGimage* createValidSVGimage(char* fileName, char* schemaFile) {
	/// check if fileName or schemaFile are NULL, return NUll if either one is...
	if(!fileName || !schemaFile) {
		return NULL;
	}
	
	// call xmlReadFile
	xmlDoc* doc = xmlReadFile(fileName, NULL, 0);
	
	/// check if doc is NULl, return NULL if it is
	if(!doc) {
		return NULL;
	}
	
	// validate doc
	bool isValid = validateDoc(doc, schemaFile);
//	printf("isValid = %d\n", isValid);
	
	/// check if its valid, return NULL if it is invalid
	if(!isValid) {
		xmlFreeDoc(doc);
		return NULL;
	}
	
	// turn Doc into svgimage
	SVGimage* img = createSVGimageFromDoc(doc);
	
	return img;
}

/** Function to validating an existing a SVGimage object against a SVG schema file
 *@pre 
    SVGimage object exists and is not NULL
    schema file name is not NULL/empty, and represents a valid schema file
 *@post SVGimage has not been modified in any way
 *@return the boolean aud indicating whether the SVGimage is valid
 *@param obj - a pointer to a GPXSVGimagedoc struct
 *@param obj - the name of a schema file
 **/
bool validateSVGimage(SVGimage* image, char* schemaFile) {
	
	if(!image || !schemaFile) {
		return false;
	}

	// check if it follows the header file standards
	if(!validateHeaderConditions(image)) {
//		puts("!validateHeaderConditions(image)");
		return false;
	}

	// convert the SVGimage* to an XMLdoc*
	xmlDoc* doc = SVGimageToDoc(image);
	
	if(!doc) {
//		puts("!doc");
		return false;
	}
	
	// check if its valid
	bool isValid = validateDoc(doc, schemaFile);
	
//printf("isValid = %d\n", isValid);
	// free doc
	xmlFreeDoc(doc);
	
	return isValid;
}

bool validateHeaderConditions(SVGimage* image) {
	ListIterator itr;
	
	// check ifthe lists are NULL
	if(!image->rectangles || !image->circles || !image->paths || !image->groups) {
		return false;
	}
	
	// check if the arrays are NULL
	if(!image->namespace || !image->title || !image->description) {
		return false;
	}
	
	// check if namespace is empty
	if(image->namespace[0] == '\0') {
		return false;
	}
	
	// check if otherAttributes is NULL
	if(!image->otherAttributes) {
		return false;
	}
	
	/// rectangle check
//puts("rectangle check");
	List* rects = getRects(image);
	itr = createIterator(rects);
	for(Rectangle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		// check basic conditions
		if(data->width < 0 || data->height < 0 || !(data->units) /*|| !(data->otherAttributes)*/) {
			freeListDataStructure(rects);
			return false;
		}
		
		if(!validateAttributesAgainstHeaderConditions(data->otherAttributes)) {
			freeListDataStructure(rects);
			return false;
		}
		
	}
	freeListDataStructure(rects); // frees the list
	
	/// circle check
//puts("circle check");
	List* circles = getCircles(image);
	itr = createIterator(circles);
	for(Circle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		// check basic conditions
		if(data->r < 0 || !(data->units) || !(data->otherAttributes)) {
			freeListDataStructure(circles);
			return false;
		}
		
		// check the otherattributes list
		if(!validateAttributesAgainstHeaderConditions(data->otherAttributes)) {
//			freeListDataStructure(circles);
			return false;
		}
	}
	freeListDataStructure(circles);
	
	/// path check
//puts("path check");
	List* paths = getPaths(image);
	itr = createIterator(paths);
	for(Path* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		// check basic conditions
		if(!(data->data) || !(data->otherAttributes)) { // TODO
			freeListDataStructure(paths);
			return false;
		}
		
		// check the otherattributes list
		if(!validateAttributesAgainstHeaderConditions(data->otherAttributes)) {
			freeListDataStructure(paths);
			return false;
		}
	}
	freeList(paths);
	
	/// group check
	List* groups = getGroups(image);
	itr = createIterator(groups);
	for(Group* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		// check basic conditions
		if(!(data->otherAttributes) || !(data->rectangles) || !(data->circles) || !(data->paths) || !(data->groups)) {
			freeListDataStructure(groups);
			return false;
		}
		
		// check the otherattributes list
		if(!validateAttributesAgainstHeaderConditions(data->otherAttributes)) {
			freeListDataStructure(groups);
			return false;
		}
	}
	freeList(groups);

	return true;
}

bool validateAttributesAgainstHeaderConditions(List* attributes) {
	
	// if the attributes list is NULL
	if(!attributes) {
		return false;
	}
	
	ListIterator itr = createIterator(attributes);
	for(Attribute* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		if(!(data->name) || !(data->value)) {
//			printf("data->name = %s and data->value = %s\n", data->name, data->value);
			return false;
		}
	}
	
	return true;
}

bool writeSVGimage(SVGimage* image, char* fileName) {
	// check if either one is NULL
	if(!image || !fileName) {
		return false;
	}
	
	// convert it to a doc
	xmlDoc* doc = NULL;
	doc = SVGimageToDoc(image);
	
	// check if the doc is NULL
	if(!doc) {
//		puts("test");
		return false;
	}
	
	// write the doc to file
	int result = -1;
	result = xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1);
	
	
	xmlFreeDoc(doc);
	xmlCleanupParser();
	
	//
	if(result > 0) {
		return true;
	}
	
	return false;
}

void setAttribute(SVGimage* image, elementType elemType, int elemIndex, Attribute* newAttribute) {
	
	if(!image || !newAttribute) {
		return;
	}
	
	// validate the svgimage against the header conditions, need schemafile
	if(!validateHeaderConditions(image)) {
		return;
	}
	
	if(!(newAttribute->name) || !(newAttribute->value)) {
		return;
	}
	
	List* list = NULL;
	ListIterator itr;
	
	int i = 0;
	
	if(elemType == SVG_IMAGE) {
//		puts("SVG_IMAGE");
		list = image->otherAttributes;
		if(!isDuplicateAttribute(image->otherAttributes, newAttribute)) {
			insertBack(image->otherAttributes, newAttribute);
		}
		
		return;
	}
	
	else if(elemType == CIRC){
//		puts("CIRC");
		
		// list = image->circles;
		list = getCircles(image);

		// check if the index is valid
		if(elemIndex >= getLength(list)) {
			return;
		}
		
		
		// variables for looping
		i = 0;
		
		itr = createIterator(list);
		
		// check for i
		for(Circle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			if(i == elemIndex) {
				
				// check if the new attribute is a mandatory type
				if(!strcmp(newAttribute->name, "r")) {
					data->r = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else if(!strcmp(newAttribute->name, "cx")) {
					data->cx = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else if(!strcmp(newAttribute->name, "cy")) {
					data->cy = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				else {
					if(!isDuplicateAttribute(data->otherAttributes, newAttribute)) {
						insertBack(data->otherAttributes, newAttribute);
					}
				}
			}
			
			i++;
		}
	}

	else if(elemType == RECT){
		// list = image->rectangles;
		list = getRects(image);
		
		// check if the index is valid
		if(elemIndex >= getLength(list)) {
			return;
		}
		
		// variables for looping
		i = 0;
		
		itr = createIterator(list);
		
		// check for i
		for(Rectangle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			if(i == elemIndex) {
				
				// check if the new attribute is a mandatory type
				if(!strcmp(newAttribute->name, "x")) {
					data->x = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else if(!strcmp(newAttribute->name, "y")) {
					data->y = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else if(!strcmp(newAttribute->name, "width")) {
					data->width = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else if(!strcmp(newAttribute->name, "height")) {
					data->height = strtof(newAttribute->value, NULL);
					deleteAttribute(newAttribute);
					return;
				}
				
				else {
					if(!isDuplicateAttribute(data->otherAttributes, newAttribute)) {
						insertBack(data->otherAttributes, newAttribute);
					}
				}
			}
			
			i++;
		}
		
	}
	
	else if(elemType == PATH){
		// list = image->paths;
		list = getPaths(image);
		// check if the index is valid
		if(elemIndex >= getLength(list)) {
			return;
		}
		
		// variables for looping
		i = 0;
		
		
		itr = createIterator(list);
		
		// check for i
		for(Path* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			if(i == elemIndex) {
				
				// check if the new attribute is a mandatory type
				if(!strcmp(newAttribute->name, "d")) {
					strcpy(data->data, newAttribute->value);
					deleteAttribute(newAttribute);
					return;
				}
				
				else {
					if(!isDuplicateAttribute(data->otherAttributes, newAttribute)) {
						insertBack(data->otherAttributes, newAttribute);
					}
				}
			}
			
			i++;
		}
	}
	
	else if(elemType == GROUP){
		// list = image->groups;
		list = getGroups(image);
		// check if the index is valid
		if(elemIndex >= getLength(list)) {
			return;
		}
		
		// variables for looping
		i = 0;
		
		
		itr = createIterator(list);
		
		// check for i
		for(Group* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
			if(i == elemIndex) {
				if(!isDuplicateAttribute(data->otherAttributes, newAttribute)) {
					insertBack(data->otherAttributes, newAttribute);
				}
			}
			
			i++;
		}
	}
	return;
}

void addComponent(SVGimage* image, elementType type, void* newElement) {
	
	if(!image || !newElement) {
		return;
	}
	
	if(type == SVG_IMAGE || type == GROUP) {
		return;
	}
	
	// add to the end of the list
	switch(type) {
		case CIRC:
			insertBack(image->circles, newElement);
			break;
		case RECT:
			insertBack(image->rectangles, newElement);
			break;
		case PATH:
			insertBack(image->paths, newElement);
			break;
		case GROUP:
			insertBack(image->paths, newElement);
			break;
		default:
			break;
	}
	
	return;
}

// returns true if there is another attribute ofthe same name
bool isDuplicateAttribute(List* otherAttributes, Attribute* newAttribute) {
	ListIterator itr = createIterator(otherAttributes);
printf("newAttribute->value = %s\n", newAttribute->value);
	for(Attribute* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// replace
		if(strcmp(data->name, newAttribute->name) == 0) {
			// strcpy(data->value, newAttribute->value);

			// free the old value
			free(data->value);
			
			// allocate space for the new value
			data->value = calloc(strlen(newAttribute->value) + 1, sizeof(char));
			data->value[0] = '\0';
			
			// copy the new value over
			strcpy(data->value, newAttribute->value);
printf("strcpy( %s , %s )\n", data->value, newAttribute->value);
			
			// delete new attribute if its a duplicate
			deleteAttribute(newAttribute);
			return true;
		}
	}
	
	return false;
}

char* attrToJSON(const Attribute *a) {
	int size = 0;
	char* string = NULL;
	
	if(!a) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	if(!(a->name) || !(a->value)) {
		return NULL;
	}
	
	// calculate the size
	size = snprintf(NULL, 0, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);

	// allocte space for the new string
	string = calloc(size + 2, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size + 1, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);
	
	return string;
}

char* circleToJSON(const Circle *c) {
	int size = 0;
	char* string = NULL;
	
	if(!c) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	// calculate the size
	size = snprintf(NULL, 0, 
	"{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", 
	c->cx, c->cy, c->r, getLength(c->otherAttributes), c->units);

	// allocte space for the new string
	string = calloc(size+1, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size + 1, 
	"{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", 
	c->cx, c->cy, c->r, getLength(c->otherAttributes), c->units);
	
	return string;
}

char* rectToJSON(const Rectangle *r) {
	int size = 0;
	char* string = NULL;
	
	if(!r) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	// calculate the size
	size = snprintf(NULL, 0, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}",r->x, r->y, r->width, r->height, getLength(r->otherAttributes), r->units);

	// allocte space for the new string
	string = calloc(size + 2, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size+1, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}",r->x, r->y, r->width, r->height, getLength(r->otherAttributes), r->units);
	
	return string;
}

char* pathToJSON(const Path *p) {
	int size = 0;
	char* string = NULL;
	char* pData = NULL;
	
	if(!p) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	if(!(p->data)) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	// 
	pData = calloc(65, sizeof(char));
	snprintf(pData, 65, "%s", p->data);
	
	// calculate the size
	size = snprintf(NULL, 0, "{\"d\":\"%s\",\"numAttr\":%d}", pData, getLength(p->otherAttributes));

	// allocte space for the new string
	string = calloc(size + 1, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size + 1, "{\"d\":\"%s\",\"numAttr\":%d}", pData, getLength(p->otherAttributes));
	
	// free
	free(pData);
	
	return string;
}

char* groupToJSON(const Group *g) {
	int size = 0;
	int numElements = 0;
	char* string = NULL;
	
	if(!g) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	numElements += getLength(g->rectangles);
	numElements += getLength(g->circles);
	numElements += getLength(g->paths);
	numElements += getLength(g->groups);
	
	// calculate the size
	size = snprintf(NULL, 0, "{\"children\":%d,\"numAttr\":%d}", numElements, getLength(g->otherAttributes));

	// allocte space for the new string
	string = calloc(size + 2, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size+1, "{\"children\":%d,\"numAttr\":%d}", numElements, getLength(g->otherAttributes));
	
	return string;
}

char* attrListToJSON(const List *list) {
	
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	char* itemToJSON = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 3;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(Attribute* attData = nextElement(&itr); attData != NULL; attData = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		itemToJSON = attrToJSON(attData);
		
		// get new size of attData to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJSON);
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJSON);
		
		free(copy);
		free(itemToJSON);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
	return string;
}

char* circListToJSON(const List *list) {
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	char* itemToJSON = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 3;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(Circle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		// get the item to json
		itemToJSON = circleToJSON(data);
		
		// get new size of data to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJSON);
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJSON);
		
		free(copy);
		free(itemToJSON);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
	return string;
}

char* rectListToJSON(const List *list) {
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	char* itemToJSON = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 3;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(Rectangle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		// get the item to json
		itemToJSON = rectToJSON(data);
		
		// get new size of data to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJSON);
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJSON);
		
		free(copy);
		free(itemToJSON);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
	return string;
}

char* pathListToJSON(const List *list) {
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	char* itemToJSON = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 3;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(Path* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		// get the item to json
		itemToJSON = pathToJSON(data);
		
		// get new size of data to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJSON);
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJSON);
		
		free(copy);
		free(itemToJSON);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
	return string;
}

char* groupListToJSON(const List *list) {
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	char* itemToJSON = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 3;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(Group* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		// get the item to json
		itemToJSON = groupToJSON(data);
		
		// get new size of data to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJSON);
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJSON);
		
		free(copy);
		free(itemToJSON);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
//	char* string = listToJson(list, &groupToJSON);
	
	return string;
}

char* SVGtoJSON(const SVGimage* imge) {
	int size = 0;
	char* string = NULL;
	List* rects = getRects((SVGimage*) imge);
	List* circles = getCircles((SVGimage*) imge);
	List* paths = getPaths((SVGimage*) imge);
	List* groups = getGroups((SVGimage*) imge);
	
	if(!imge) {
		string = calloc(4, sizeof(char));
		snprintf(string, 3, "{}");
		
		return string;
	}
	
	// calculate the size
	size = snprintf(NULL, 0, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", 
	getLength(rects), getLength(circles), getLength(paths), getLength(groups));

	// allocte space for the new string
	string = calloc(size + 23, sizeof(char));
	
	// copy the json formatted text to the string
	snprintf(string, size+1, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", 
//	getLength(imge->rectangles), getLength(imge->circles), getLength(imge->paths), getLength(imge->groups));
	getLength(rects), getLength(circles), getLength(paths), getLength(groups));

	// frees
	freeList(rects);
	freeList(circles);
	freeList(paths);
	freeList(groups);
	
	return string;
}

/// Will Pringle's Helper Functions A2

char* listToJson(const List *list, char* itemToJson(const void* e)) {
	if(!list) {
		return NULL;
	}
	
	char* string = NULL;
	char* copy = NULL;
	ListIterator itr = createIterator((List*) list);
	
	int size = 2;
	
	string = malloc(sizeof(char) * size);
	
	string[0] = '[';
	string[1] = '\0';
	
	
	for(void* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		
		// create a new copy 
		copy = calloc(size + 2, sizeof(char));
		strcpy(copy, string);
		
		// get new size of data to json
		size = snprintf(NULL, 0, "%s%s,D", string, itemToJson(data));
		
		// realloc space for this size
		string = realloc(string, sizeof(char) * (size + 1));
		
		// copy old data to string
		snprintf(string, size, "%s%s,D", copy, itemToJson(data));
		
		free(copy);
	}
	
	string[size - 2] = ']';
	string[size - 1] = '\0';
	
	return string;
}

// creating a doc from an svgimage functions
xmlDoc* SVGimageToDoc(SVGimage* image) {
	if(!image) {
		return NULL;
	}
	
	xmlDoc* doc = NULL;
	xmlNode* root_node = NULL; 
	xmlNs* ns = NULL;
	
	// Creates a new document, a node and set it as a root node
	doc = xmlNewDoc(BAD_CAST "1.0"); 
    root_node = xmlNewNode(NULL, BAD_CAST "svg"); // make the svg thing
    xmlDocSetRootElement(doc, root_node);
		
	// set up namespace
	ns = xmlNewNs(root_node, BAD_CAST image->namespace, NULL);
	xmlSetNs(root_node, ns);

	// populate title and description if there is one
	if(image->title[0] != '\0'){
		xmlNewChild(root_node, NULL, BAD_CAST "title", BAD_CAST image->title);
	}
	
	if(image->description[0] != '\0') {
		xmlNewChild(root_node, NULL, BAD_CAST "desc", BAD_CAST image->description);
	}
	
	// add attributes to svg image base node
	addAttributeNodesToTree(root_node, image->otherAttributes);
	
	// add rects, circles, and paths from the node to the root_node
	addAllElementsToDoc(image->rectangles, image->circles, image->paths, root_node);
	
	// add all groups 
	addGroupsToDoc(image->groups, root_node);
	
	return doc;
}

void addGroupToDoc(Group* g, xmlNode* parentNode) {
	// make groupNode a child of parentNode
	xmlNode* groupNode = xmlNewChild(parentNode, NULL, BAD_CAST "g", NULL);
	
	// add misc other attributes to the g
	addAttributeNodesToTree(groupNode, g->otherAttributes);
	
	// add all elements
	addAllElementsToDoc(g->rectangles, g->circles, g->paths, groupNode);
	
	// make recursive call to get groups in groups
	addGroupsToDoc(g->groups, groupNode);
}

void addRectangleToDoc(Rectangle* rect, xmlNode* parentNode) {
	xmlNode* temp = NULL;
	char* floatString = NULL;
	
	// make a rectangle child of the current node
	temp = xmlNewChild(parentNode, NULL, BAD_CAST "rect", NULL);
	
	// add the x value
	floatString = floatToString(rect->x);
	floatString = addUnitsToString(floatString, rect->units);
	xmlNewProp(temp, BAD_CAST "x", BAD_CAST floatString);
	free(floatString);
	
	// add the y value
	floatString = floatToString(rect->y);
	floatString = addUnitsToString(floatString, rect->units);
	xmlNewProp(temp, BAD_CAST "y", BAD_CAST floatString);
	free(floatString);
	
	// add the width value
	floatString = floatToString(rect->width);
	floatString = addUnitsToString(floatString, rect->units);
	xmlNewProp(temp, BAD_CAST "width", BAD_CAST floatString);
	free(floatString);
	
	// add the height
	floatString = floatToString(rect->height);
	floatString = addUnitsToString(floatString, rect->units);
	xmlNewProp(temp, BAD_CAST "height", BAD_CAST floatString); // WHY THE &??????!!!
	free(floatString);
	
	// add other attributes
	addAttributeNodesToTree(temp, rect->otherAttributes);
}

void addCircleToDoc(Circle* circle, xmlNode* parentNode) {
	xmlNode* temp = NULL;
	char* floatString = NULL;
	
	// make a circle child of the current node
	temp = xmlNewChild(parentNode, NULL, BAD_CAST "circle", NULL);
	
	// set the cx
	floatString = floatToString(circle->cx);
	floatString = addUnitsToString(floatString, circle->units);
	xmlNewProp(temp, BAD_CAST "cx", BAD_CAST floatString); // WHY THE &??????!!!
	free(floatString);
	
	// set the cy
	floatString = floatToString(circle->cy);
	floatString = addUnitsToString(floatString, circle->units);
	xmlNewProp(temp, BAD_CAST "cy", BAD_CAST floatString); // WHY THE &??????!!!
	free(floatString);
	
	// set the r
	floatString = floatToString(circle->r);
	floatString = addUnitsToString(floatString, circle->units);
	xmlNewProp(temp, BAD_CAST "r", BAD_CAST floatString); // WHY THE &??????!!!
	free(floatString);
	
	// add other attributes
	addAttributeNodesToTree(temp, circle->otherAttributes);
}

void addPathToDoc(Path* path, xmlNode* parentNode) {
	xmlNode* temp = NULL;
	
	// make a path child of the current node
	temp = xmlNewChild(parentNode, NULL, BAD_CAST "path", NULL);
	xmlNewProp(temp, BAD_CAST "d", BAD_CAST path->data);
	
	// add other attributes
	addAttributeNodesToTree(temp, path->otherAttributes);
}

void addAllElementsToDoc(List* rects, List* circles, List* paths, xmlNode* node) {
	ListIterator itr;
	
	/// rectangles 
	itr = createIterator(rects);
	for(Rectangle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		addRectangleToDoc(data, node);
	}
	
	/// circles 
	itr = createIterator(circles);
	for(Circle* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		addCircleToDoc(data, node);
	}
	
	/// paths
	itr = createIterator(paths);
	for(Path* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		addPathToDoc(data, node);
	}
	
}

void addGroupsToDoc(List* groups, xmlNode* node) {
	ListIterator itr;
	
	/// loop through groups and add them
	itr = createIterator(groups);
	for(Group* data = nextElement(&itr); data != NULL; data = nextElement(&itr)) {
		addGroupToDoc(data, node);
		
		// add all the elements within the group
		
	}
	
}

int addAttributeNodesToTree(xmlNode* node, List* otherAttributes) {
	
	ListIterator itr = createIterator(otherAttributes);
	
	for(Attribute* attData = nextElement(&itr); attData != NULL;) {
		// add the new attribute
		xmlNewProp(node, BAD_CAST attData->name, BAD_CAST attData->value);
		
		// advance the LL to the next attribute
		attData = nextElement(&itr);
	}

	return 0;
}


// validate doc
bool validateDoc(xmlDoc* doc, char* schemaFile) {
	xmlSchemaParserCtxtPtr context = NULL;
	xmlSchemaPtr schema = NULL;
	xmlSchemaValidCtxtPtr validContext = NULL;
	int isValid = 0;
	
	// use the file to get the cotext
	context = xmlSchemaNewParserCtxt((const char*)schemaFile);

	if(!context) {
		xmlSchemaFreeParserCtxt(context);
		xmlCleanupParser();
		return false;
	}

	// create schema using context
	schema = xmlSchemaParse(context);
	
	if(!schema) {
		xmlSchemaFreeParserCtxt(context);
		xmlCleanupParser();
		return false;
	}
	
	// create validcontext using schema
	validContext = xmlSchemaNewValidCtxt(schema);
	
	if(!validContext) {
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(context);
		xmlCleanupParser();
		return false;
	}
	
	// check if it is valid
	isValid = xmlSchemaValidateDoc(validContext, doc);
	

//	printf("isValid = %d\n", !isValid);
	
	// frees
	xmlSchemaFree(schema);
	xmlSchemaFreeParserCtxt(context);
	xmlSchemaFreeValidCtxt(validContext);
	
	// cleanup
	xmlCleanupParser();
	
//	puts("validateDoc");
	return !isValid;
	
}

// create valid SVGimage from Doc
SVGimage* createSVGimageFromDoc(xmlDoc* doc) {
	
	// Get the root element node
    xmlNode* root_element = xmlDocGetRootElement(doc);

	// CREATE SPACE FOR SVGIMAGE
	SVGimage* image = malloc(sizeof(SVGimage));
	
	// tempoarily setting list variables to NULL
	image->rectangles = initializeList(&rectangleToString, &deleteRectangle, &comparePaths);
	image->circles = initializeList(&rectangleToString, &deleteCircle, &comparePaths);
	image->paths = initializeList(&rectangleToString, &deletePath, &comparePaths);
	image->groups = initializeList(&groupToString, &deleteGroup, &comparePaths);
	image->otherAttributes = initializeList(&rectangleToString, &deleteAttribute, &comparePaths);
	
	// add other attributes to the thing
	snprintf(image->namespace, 256, (char*) root_element->ns->href);
	
	// populate attributes
	xmlAttr *attr = NULL;
	bool titleFlag = false;
	bool descFlag = false;
	bool nsFlag = false; // there must be a namespace, so this must be true
	
	// est the title and desc to empty
	strcpy(image->title, "");
	strcpy(image->description, "");
	
	// 
	for (attr = root_element->properties; attr != NULL; attr = attr->next) {
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		// if it is not xmlns
		if(!strcmpu(attr->name, "title")) {
			strcpy(image->title, (char*) attr->children->content);
			titleFlag = true;
//puts("!strcmpu(attr->name, \"title\"");
			
		} else if(!strcmpu(attr->name, "desc")) {
			strcpy(image->description, (char*) attr->children->content);
			descFlag = true;
//puts("!strcmpu(attr->name, \"desc\"");
		} else {
			insertBack(image->otherAttributes, addAttribute(attrName, cont));
			nsFlag = true;
//			printf("this should never be called --> attrName = %s\tcont = %s", attrName, cont);
			
		}
	}

	// check if there is not a desc or title
	if(!titleFlag) {
		strcpy(image->title, "");
//		puts("!titleFlag");
	}
	
	if(!descFlag) {
		strcpy(image->description, "");
//		puts("!descFlag");
	}

	// if there is no ns it is not valid
	if(!nsFlag) {
		deleteSVGimage(image);
		return NULL;
	}
	
	// populating the svgimage
	bog(image, root_element->children);

	// frees
    xmlFreeDoc(doc); // free document
    xmlCleanupParser(); // free global variable 
	
	return image;
}

// misc functions // depricated 
void freeListDataStructure(List* list) {
	
	if(!list) {
		return;
	}
	
	Node* tmp = list->head;
	Node* freeMe = NULL;
	
	while(tmp) {
		freeMe = tmp;
		tmp = tmp->next;
		free(freeMe);
		freeMe = NULL;
	}
	
	free(list);
	return;
}
/*
List* copyList(List* list) {
	List* copiedList;
}
*/

char* floatToString(float num) {
	int floatLength = 0;
	char* floatString = NULL;
	
	floatLength = snprintf(NULL, 0, "%f", num);
	floatString = malloc(sizeof(char) * (floatLength + 1));
	snprintf(floatString, floatLength + 1, "%f", num);
	
	return floatString;
}

char* addUnitsToString(char* string, char units[50]) {
	int stringLength = strlen(string) + strlen(units) + 1;
	
	// realloc for the string length
	string = realloc(string, sizeof(char) * stringLength);
	
	// concatenate the strings
	strcat(string, (const char*) units);	
	
	return string;
}

void dummyDelete(void* data) {
	return;
}



/// Will Pringle's Helper functions A1
List* combineList(List* source, List* destination) {
	
	// iterate through each element in source and add it to destination
	ListIterator itr = createIterator(source);
	
	void* data = nextElement(&itr);
	while (data != NULL)
	{
		
		//destination
		insertBack(destination, data);
		
		// advance to the next data
		data = nextElement(&itr);
	}

	return source;
}

/*
List* getAllRectsFromGroups(Group* g, List* list) {
    
	// add the list of rectangles to the lists
//	combineList(g->groups, list);

    // if there is at least one group in the group list
    if(getLength(g->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(g->groups);
        
        Group* data = nextElement(&itr);
		
		// iterate through each thing 
        while (data != NULL) {
            getAllRectsFromGroups(data, list);
            data = nextElement(&itr);
			insertBack(groups, data);
            
        }
    }
    
    return list;
}*/

void getAllElementsFromGroups(Group* g, List* list, elementType e) {
	// iterate through each group and call goThroughGroup recursively
	ListIterator itr = createIterator(g->groups);
	
	// go through every group in the base level of the SVGimage
	for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
		// add all the elements from the current group
		
		// add differnet element to list depending on what list it is
		switch(e){
			case RECT:
				combineList(tempG->rectangles, list);
				break;
			case CIRC:
				combineList(tempG->circles, list);
				break;
			case PATH:
				combineList(tempG->paths, list);
				break;
			default:
				break;
		}
		
		// then dive into the group and see if there are elements to add from there
		getAllElementsFromGroups(tempG, list, e);
	}
    return;
}

void getAllRectsFromGroups(Group* g, List* list) {
	// iterate through each group and call goThroughGroup recursively
	ListIterator itr = createIterator(g->groups);
	
	// go through every group in the base level of the SVGimage
	for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
		// add all the rectangles from the current rectangle
		combineList(tempG->rectangles, list);
		
		// then dive into the group and see if there are rectangles to add from there
		getAllRectsFromGroups(tempG, list);
	}
    return;
}

List* getAllCirclesFromGroups(Group* g, List* list) {
    
	// add the list of rectangles to the lists

	combineList(g->circles, list);


    // if there is at least one group in the group list
    if(getLength(g->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(g->groups);
        
        Group* data = nextElement(&itr);
		
//		puts("circle called and added");
		
		// iterate through each thing 
        while (data != NULL) {
            getAllCirclesFromGroups(data, list);
            data = nextElement(&itr);
            
        }
    }
    
    return list;
}

List* getAllPathsFromGroups(Group* g, List* list) {
    
	// add the list of rectangles to the lists
	combineList(g->paths, list);

    // if there is at least one group in the group list
    if(getLength(g->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(g->groups);
        
        Group* data = nextElement(&itr);
		
		// iterate through each thing 
        while (data != NULL) {
            getAllPathsFromGroups(data, list);
            data = nextElement(&itr);
            
        }
    }
    
    return list;
}



int attributeListCounter(List* list, int test) {
	
	int num = 0;
	ListIterator itr = createIterator(list);
	
	
	if(test == 1) {
		// rectangle
		Rectangle* data = NULL;
		
		data = nextElement(&itr);
		while (data != NULL)
		{
			// 
			num += getLength(data->otherAttributes);
			

			data = nextElement(&itr);
		}
		
	} else if (test == 2) {
		// circle
		Circle* data = NULL;
		
		data = nextElement(&itr);
		while (data != NULL)
		{
			// 
			num += getLength(data->otherAttributes);

			data = nextElement(&itr);
		}
		
	} else if (test == 3) {
		// path
		Path* data = NULL;
		
//		puts("hello world");
		
		data = nextElement(&itr);
		while (data != NULL)
		{
			// 
			
			num += getLength(data->otherAttributes);

			data = nextElement(&itr);
		}
		
	} else if (test == 4) {
		// group
		Group* data = NULL;
		
		data = nextElement(&itr);
		while (data != NULL)
		{
			// 
			num += getLength(data->otherAttributes);

			data = nextElement(&itr);
		}
		
	} else {
//		puts("something went wrong");
	}

	
	return num;
	
}

int goThroughGroupAndAddAttributes(Group* g) {
	
	// if the group is null, return
	if(!g) {
//puts("null group");
		return -1;
	}
	
	// do stuff
	int attributes = 0;
	
	attributes += attributeListCounter(g->rectangles, 1);
	attributes += attributeListCounter(g->circles, 2);
	attributes += attributeListCounter(g->paths, 3);
	attributes += getLength(g->otherAttributes);
	
	
	// if there is at least one group in the group list
	if(getLength(g->groups)) {
		
		// iterate through each group and call goThroughGroupAndAddAttributes recursively
		ListIterator itr = createIterator(g->groups);
		
		Group* data = nextElement(&itr);
		while (data != NULL)
		{
			// 
			attributes += goThroughGroupAndAddAttributes(data);
			
			data = nextElement(&itr);
			
		}
		
	}
	
	return attributes;
	
}

// will return a list of elements that match a criteria
int findElements(List * list, const void* searchRecord,
int (*compareFunction)(const void* first, const void* second)
){
	int matches = 0;
	
//	List* matchList = initializeList(printFunction, deleteFunction, compareFunction);
	
	if (compareFunction == NULL)
		return -1;

	ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{
		if (compareFunction(data, searchRecord)) {
			matches++;
		}

		data = nextElement(&itr);
	}

	return matches;
}


// 
int getGroupLength(Group* group) {
	
	if(!group) {
		return 0;
	}
	
//	printf("group = %p\n", group);
	
/*	puts("");
	
	printf("group->rectangles = %p\n", group->rectangles);
	printf("group->circles = %p\n", group->circles);
	printf("group->paths = %p\n", group->paths);
	printf("group->groups = %p\n", group->groups);
*/	
	int size = 0;
    size += getLength(group->rectangles);
	size += getLength(group->circles);
	size += getLength(group->paths);
	size += getLength(group->groups);
	
	return size;
}

// first parameter is for the element to compare, second is length
int compareGroupLength(const void* first, const void* second) {
	Group* group = (Group*) first;
	int* len = (int*) second;
	
//	printf("\t\tdata = {%d}\t sRecord = {%d}\n", getGroupLength(group), *len);
	
//	puts("right before getGroupLength(group) == *len");
	if(getGroupLength(group) == *len) {
		return 1;
	}
	
	return 0;
}


// compares an unsigned string to a string, s1 is unsigned, s2 is signed
int strcmpu(const unsigned char* s1, const char* s2) {
	return strcmp((const char*) s1, s2);
}

// returns an integer from a string and sets the second string to string portion
int stringToInt(char* string, char* end) {
	return (int) strtol(string, &end, 10);
}

// 
Attribute* addAttribute(char* attrName, char* cont) {
	Attribute* a;
	
	// alloacte space for the attribute and the strings
	a = malloc(sizeof(Attribute));
	a->name = malloc(sizeof(char) * (strlen(attrName) +1));
	a->value = malloc(sizeof(char) * (strlen(cont) +1));
	
	// copy the information to the strings
	strcpy(a->name, attrName);
	strcpy(a->value, cont);
	return a;
}

List* addToList(List* head, void* data, char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted)) {
	
	// if there are no elements in the linked list, add a starting node
	if (head == NULL) {
		head = initializeList(printFunction, deleteFunction, &comparePaths);
		insertBack(head, data);
		
	} else { // if there is already a node in the linked list, add another one
		insertBack(head, data);
		
	}
	
	return head;
}

// shape paresers
Rectangle* parseRect(xmlNode* cur_node) {
	xmlAttr* attr;
	Rectangle* rect;
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
	char* end;

	// check if x y width and height are given
	bool isX = false, isY = false, isWidth = false, isHeight = false;
	
	// allocate space for a rectanle and create list of other Attributes
	rect = malloc(sizeof(Rectangle));
	rect->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// ensure a null character
	rect->units[0] = '\0';
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next)
	{
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		// check if its valid
		if(!attrName || !(value->content)) {
//			puts("BAD1 - invalid attrName == NULL");
			free(rect);
			return NULL;
		}
		
		
		if(!strcmp(attrName, "x")) {
			x = strtof(cont, &end);
			rect->x = x;
			isX = true;
			
		} else if(!strcmp(attrName, "y")) {
			y = strtof(cont, &end);
			rect->y = y;
			isY = true;
			
		} else if(!strcmp(attrName, "width")) {
			width = strtof(cont, &end);
			rect->width = width;
			isWidth = true;
			
		} else if(!strcmp(attrName, "height")) {
			height = strtof(cont, &end);	
			rect->height = height;
			isHeight = true;
			
		// all othre attributes go here
		} else {
			
			// add the attribute to the list
			insertBack(rect->otherAttributes, addAttribute(attrName, cont));
		}
	}
	
	// if there is no attribute setthem to 0
	if(!isX) {
		rect->x = 0;
	}
	
	if(!isY) {
		rect->y = 0;
	}
	
	if(!isWidth) {
		rect->width = 0;
	}
	
	if(!isHeight) {
		rect->height = 0;
	}
	
	// copy the units from the x to the units in the struct
	if(isX || isY || isWidth || isHeight) {
		strcpy(rect->units, end);
	} else {
		strcpy(rect->units, "");
	}

	return rect;
}

Circle* parseCircle(xmlNode* cur_node) {
	xmlAttr* attr = NULL;
	Circle* circle = NULL;
	float cx = 0;
	float cy = 0;
	float r = 0;
	char* end; // used to get units

	// check if cx cy and r
	bool isCx = false, isCy = false, isR = false;
	
	// allocate space for a rectanle and create list of other Attributes
	circle = malloc(sizeof(Rectangle));
	circle->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// ensure a null character
	circle->units[0] = '\0';
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next)
	{
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		// check if its valid
		if(!attrName || !(value->content)) {
	//		puts("BAD1 - invalid attrName == NULL");
			free(circle);
			return NULL;
		}
		
		if(!strcmp(attrName, "cx")) {
			cx = strtof(cont, &end);
			circle->cx = cx;
			isCx = true;
			
		} else if(!strcmp(attrName, "cy")) {
			cy = strtof(cont, &end);
			circle->cy = cy;
			isCy = true;
			
		} else if(!strcmp(attrName, "r")) {
			r = strtof(cont, &end);
			
			
			// check if r < 0
			if(r < 0) {
//				puts("BAD2 - invalid r < 0");
				
				
				freeList(circle->otherAttributes);
				free(circle);
				return NULL;
			}
			
			isR = true;
			
			circle->r = r;
			
			
		// all othre attributes go here
		} else {
			
			// add the attribute to the list
			insertBack(circle->otherAttributes, addAttribute(attrName, cont));
			
		}
		
	}
	
	//
	if(!isCx) {
		circle->cx = 0;
	}
	if(!isCy) {
		circle->cy = 0;
	}
	if(!isR) {
		circle->r = 0;
	}
	
	if(isCx || isCy || isR) {
		// copy the units from the x to the units in the struct
		strcpy(circle->units, end);
	}
	else {
		strcpy(circle->units, "");
	}

	return circle;
}

Path* parsePath(xmlNode* cur_node) {
	xmlAttr* attr = NULL;
	Path* path = NULL;
	
	// allocate space for a rectanle and create list of other Attributes
	path = malloc(sizeof(Path));
	path->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// allocate space for the path data and set the first index to /0
	path->data = malloc(sizeof(char) * 2);
	path->data[0] = '\0';
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		
		// check if its valid
		if(!attrName || !(value->content)) {
//			puts("BAD1 - invalid attrName == NULL");
			free(path);
			return NULL;
		}
		
		if(!strcmp(attrName, "d")) {
//			printf("content is = {%s}\n}", cont);
			
			// realloc size for the path
			path->data = realloc(path->data, sizeof(char) * (strlen(cont)+1));
			
			// copy the string over
			sprintf(path->data, "%s", cont);
			
		// all othre attributes go here
		} else {
//puts("insert otherAttr FOR PATH");
			// add the attribute to the list
			insertBack(path->otherAttributes, addAttribute(attrName, cont));
//printf("path->otherAttributes = %p", path->otherAttributes);
		}	
	}

	return path;
}

Group* parseGroup(xmlNode* groupNode) {
	Group* g = NULL;
	
	// allocate space for the group
	g = malloc(sizeof(Group));
	
	xmlNode *cur_node = NULL;
	
	g->rectangles = initializeList(&rectangleToString, &deleteRectangle, &comparePaths);
	g->circles = initializeList(&rectangleToString, &deleteCircle, &comparePaths);
	g->paths = initializeList(&rectangleToString, &deletePath, &comparePaths);
	g->groups = initializeList(&groupToString, &deleteGroup, &comparePaths);
	g->otherAttributes = initializeList(&rectangleToString, &deleteAttribute, &comparePaths);
	
	
	// get attributes
	// populate attributes
	if(!(groupNode)) {
		return g;
	}
	
	for (xmlAttr* attr = groupNode->parent->properties; attr != NULL; attr = attr->next)
	{		
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		// check if its valid
		if(!attrName || !(value->content)) {
//			puts("BAD1 - invalid attrName == NULL");
			free(g);
			return NULL;
		}
		
		// if it is not xmlns
		if(strcasecmp(attrName, "xmlns")) {
			insertBack(g->otherAttributes, addAttribute(attrName, cont));
		}
	}
	
	

	// get all the circles, groups, rectangles, etc
	// while the current node isn't null, set it to the next node
    for (cur_node = groupNode; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
			// place in rectangles, circles, paths, groups
			if(!strcmpu(cur_node->name, "rect")) {
				insertBack(g->rectangles, parseRect(cur_node));

			} else if(!strcmpu(cur_node->name, "circle")) {
				insertBack(g->circles, parseCircle(cur_node));
				
			} else if(!strcmpu(cur_node->name, "path")) {
				insertBack(g->paths, parsePath(cur_node));
				
			}
			
			// groups
			else if(!strcmpu(cur_node->name, "g")) {
				
				// if the group is empty don't do anything
				
				if(cur_node->next) {
					
					insertBack(g->groups, parseGroup(cur_node->children));
				} else {
//					puts("suepr suepr syeper");
				}
			}
        }
    }
	
	return g;
	
}

void bog(SVGimage* image, xmlNode *root) {
	
	xmlNode *cur_node = NULL;

	// while the current node isn't null, set it to the next node
    for (cur_node = root; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
			
			// place in title, description
			if(!strcmpu(cur_node->name, "title")) {		
				snprintf(image->title, 256, (char*) cur_node->children->content);
			} else if(!strcmpu(cur_node->name, "desc")) {
//				strcpy(image->description, (char*) cur_node->children->content);
				snprintf(image->description, 256, (char*) cur_node->children->content);
				
			}
			
			// place in rectangles, circles, paths, groups
			/*else*/ if(!strcmpu(cur_node->name, "rect")) {
				insertBack(image->rectangles, parseRect(cur_node));
				
				
			} else if(!strcmpu(cur_node->name, "circle")) {
				insertBack(image->circles, parseCircle(cur_node));
				
			} else if(!strcmpu(cur_node->name, "path")) {
				insertBack(image->paths, parsePath(cur_node));
				
			}
			
			// groups
			else if(!strcmpu(cur_node->name, "g")) {
				insertBack(image->groups, parseGroup(cur_node->children));
				
			}
        }
    }
}


/* Public API - main */

/** Function to create an SVG object based on the contents of an SVG file.
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
 *@post Either:
        A valid SVGimage has been created and its address was returned
		or 
		An error occurred, and NULL was returned
 *@return the pinter to the new struct or NULL
 *@param fileName - a string containing the name of the SVG file
**/
SVGimage* createSVGimage(char* fileName) {
	
	// check for NULL
	if(!(fileName)) {
		return NULL;
	}
	
	xmlDoc *doc = NULL;
	SVGimage *image = NULL;

	// intialize library / check for other issues
    LIBXML_TEST_VERSION

    // parse the file and get the DOM
    doc = xmlReadFile(fileName, NULL, 0);
	
	// if xml had problems
	if(doc == NULL) {
		// cleanup the aprser
		xmlCleanupParser();
		return NULL;
	}
	
	image = createSVGimageFromDoc(doc);
	
	if(!image) {
		return NULL;
	}

	/*
	 * return the svgimage
	 */
	return image;
}

/** Function to create a string representation of an SVG object.
 *@pre SVGimgage exists, is not null, and is valid
 *@post SVGimgage has not been modified in any way, and a string representing the SVG contents has been created
 *@return a string contaning a humanly readable representation of an SVG object
 *@param obj - a pointer to an SVG struct
**/
char* SVGimageToString(SVGimage* img) {
	char* temp = malloc(sizeof(char) * 2);
	temp[0] = 's';
	temp[1] = '\0';
	return temp;
}
/////TODO TODO
/** Function to delete image content and free all the memory.
 *@pre SVGimgage  exists, is not null, and has not been freed
 *@post SVSVGimage  had been freed
 *@return none
 *@param obj - a pointer to an SVG struct
**/
void deleteSVGimage(SVGimage* img) {
	
	// check for NULL
	if(img == NULL) {
		return;
	}
	
	// free all the lists
	freeList(img->rectangles);
	freeList(img->circles);
	freeList(img->paths);
	freeList(img->groups);
	freeList(img->otherAttributes);
	
	// frees the space that held the struct
	free(img);
	
}


// Function that returns a list of all rectangles in the image.  
List* getRects(SVGimage* img) {
	// check for NULL
	if(!(img)) {
		return NULL;
	}
	
	List* list = initializeList(&rectangleToString, &dummyDelete, &comparePaths);
	combineList(img->rectangles, list);
	
	// if there is at least one group in the group list
    if(getLength(img->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(img->groups);
        
        for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
            // 
			combineList(tempG->rectangles, list);
            getAllElementsFromGroups(tempG, list, RECT);
        }
    }
	
	return list; // fix this
}

List* getCircles(SVGimage* img) {
	// check for NULL
	if(!(img)) {
		return NULL;
	}
	
	List* list = initializeList(&circleToString, &dummyDelete, &comparePaths);
	combineList(img->circles, list);
	
	// if there is at least one group in the group list
    if(getLength(img->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(img->groups);
        
        for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
            // 
			combineList(tempG->circles, list);
            getAllElementsFromGroups(tempG, list, CIRC);
        }
    }
	
	return list; // fix this
}

// Function that returns a list of all groups in the image.  
List* getGroups(SVGimage* img) {
	// check for NULL
	if(!(img)) {
		return NULL;
	}
	
	// create an iterator for the base level of the function
	ListIterator itrBaseLevel = createIterator(img->groups);
	
	// create a lits full of ALL the groups in the image (not just abse top level)
	List* groups = initializeList(&groupToString, &dummyDelete, &comparePaths);
	
	// put all the groups in the base level in the groups list
	combineList(img->groups, groups);
	
	// go through every group in the base level of the SVGimage
	for(Group* tempG = nextElement(&itrBaseLevel); tempG; tempG = nextElement(&itrBaseLevel)) {
		// 
		getAllGroupsFromGroups(tempG, groups);
	}
	
	return groups;
}

List* getAllGroupsFromGroups(Group* g, List* groups) {
	// iterate through each group and call goThroughGroup recursively
	ListIterator itr = createIterator(g->groups);
	
	// go through every group in the base level of the SVGimage
	for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
		// 
		getAllGroupsFromGroups(tempG, groups);
		insertBack(groups, tempG);
//		puts("getAllGroupsFromGroups");
	}
    
    return NULL;
}


List* getPaths(SVGimage* img) {
	// check for NULL
	if(!(img)) {
		return NULL;
	}
	
	List* list = initializeList(&pathToString, &dummyDelete, &comparePaths);
	combineList(img->paths, list);
	
	// if there is at least one group in the group list
    if(getLength(img->groups)) {
        
        // iterate through each group and call goThroughGroup recursively
        ListIterator itr = createIterator(img->groups);
        
        for(Group* tempG = nextElement(&itr); tempG; tempG = nextElement(&itr)) {
            // 
			combineList(tempG->paths, list);
            getAllElementsFromGroups(tempG, list, PATH);
        }
    }
	
	return list; // fix this
}

// Function that returns the number of all rectangles with the specified area
int numRectsWithArea(SVGimage* img, float area) {
	// check for NULL
	if(!(img) || area < 0) {
		return 0;
	}
	
	// allocate the base
	Rectangle* base = malloc(sizeof(Rectangle));
	base->width = area;
	base->height = 1;
	
	// get a list of the rectangles
	List* list = getRects(img);
	
	// find the elements and put them in a list
	int matches = findElements(list, base, &compareRectangles);
	
	// free 
	free(base);
	freeListDataStructure(list);
	
	return matches;
}

// Function that returns the number of all circles with the specified area
int numCirclesWithArea(SVGimage* img, float area) {
	// check for NULL
	if(!(img) || area < 0) {
		return 0;
	}
	
	//allocate the base
	Circle* base = malloc(sizeof(Circle));
	
	// set the radius to the radius (since comparing area using radius)
	base->r = sqrt(area / PI);
	
	// get a list of the rectangles
	List* list = getCircles(img);
	
	// find the elements and put them in a list
	int matches = findElements(list, base, &compareCircles);
	
	// free 
	free(base);
	freeListDataStructure(list);
	
	return matches;
}

// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(SVGimage* img, char* data) {
	// check for NULL
	if(!(img)) {
		return 0;
	}
	
	// allocate the base
	Path* base = malloc(sizeof(Path));
	
	// set the string to point to the same data as the data string
	base->data = data;
	
	List* list = getPaths(img);
	
	// find the elements and put them in a list
	int matches = findElements(list, base, &comparePaths);
	
	free(base);
	freeList(list);
	
	return matches;
}

// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(SVGimage* img, int len) {
	int matches = 0;
	// check for NULL
	if(!(img) || len < 0) {
		return 0;
	}
	
	List* list = getGroups(img);
	
//	printf("list->length = %d\n", getLength(list));
	
	matches = findElements(list, &len, &compareGroupLength);
	
	freeListDataStructure(list);
	
	return matches;
}


// Sums all the attributes
int numAttr(SVGimage* img) {
	//check for NULL
	if (!img) {
		return 0;
	}
	
	int attributes = 0;
	
	attributes += attributeListCounter(img->rectangles, 1);
	attributes += attributeListCounter(img->circles, 2);
	attributes += attributeListCounter(img->paths, 3);
	attributes += getLength(img->otherAttributes);
	
	// get the attributes from groups
	ListIterator itr = createIterator(img->groups);
		
	Group* data = nextElement(&itr);
	while (data != NULL)
	{
		// 
		attributes += goThroughGroupAndAddAttributes(data);
		
		data = nextElement(&itr);
		
	}
		
	return attributes;
}


void deleteAttribute( void* data) {
	if(!data) {
		return;
	}
	
	Attribute* a = (Attribute*) data;
	
	// free name and value
	free(a->name);
	free(a->value);
	
	// free the struct itself
	free(a);

	return;
}
char* attributeToString( void* data) {
	if(!data) {
		return NULL;
	}
	
	char* string = calloc(3, sizeof(char));
	string[0] = 'a';
	string[1] = '\0';
	
	
	return string;
}
int compareAttributes(const void *first, const void *second) {
	// check for NULL
	if(!(first&&second)) {
		return 0;
	}
	
	
	return 0;
}


void deleteGroup(void* data) {
	if(!data) {
		return;
	}
	
	Group* g = (Group*) data;
	
	// clear the lists
	freeList(g->rectangles);
	freeList(g->circles);
	freeList(g->paths);
	freeList(g->groups);
	
	// free the other attributes list
	freeList(g->otherAttributes);
	
	free(g);
	
	return;
}
char* groupToString( void* data){
	if(!data) {
		return NULL;
	}
	
//	Group* group = (Group*) data;
	
/*	printf("group length = %d\n", getGroupLength(group));
	printf("\tnum rectans = %d\n", getLength(group->rectangles));
	printf("\tnum circles = %d\n", getLength(group->circles));
	printf("\tnum paths   = %d\n", getLength(group->paths));
	printf("\tnum groups  = %d\n", getLength(group->groups));*/
	
	char* string = malloc(sizeof(char) * 5);
	string[0] = 'G';
	string[1] = '\0';
	
	return string;
}
int compareGroups(const void *first, const void *second) {
	// check for NULL
	if(!(first&&second)) {
		return 0;
	}
	
	// TODO - will break code if used to sort groups hahahaha
	
	
	return 0;
}


void deleteRectangle(void* data) {
	// check for NULL
	if(!data) {
		return;
	}
	
	Rectangle* rect = (Rectangle*) data;
	
	// free miscellaneous attributes  
	freeList(rect->otherAttributes);

	// free the struct itself
	free(rect);
	
	return;
}
char* rectangleToString(void* data) {
	// check for NULL
	if(!data) {
		return NULL;
	}
	
	
	char* string = malloc(sizeof(char) * 5);
	string[0] = 'R';
	string[1] = '\0';
	
	return string;
}
int compareRectangles(const void *first, const void *second) {
	// check for NULL
	if(!(first&&second)) {
		return 0;
	}
	
	
	Rectangle* rect1 = (Rectangle*) first;
	Rectangle* rect2 = (Rectangle*) second;
	
	// calculate the areas
	float area1 = rect1->width * rect1->height;
	float area2 = rect2->width * rect2->height;
	
	// return 1 is the areas are equal
	if(ceil(area1) == ceil(area2)) {
		return 1;
	}
	
	return 0;
}


void deleteCircle(void* data) {
	// check for NULL
	if(!data) {
		return;
	}
	
	Circle* circle = (Circle*) data;
	
	// free miscellaneous attributes  
	freeList(circle->otherAttributes);

	// free the struct itself
	free(circle);
	
	return;
}
char* circleToString(void* data) {
	// check for NULL
	if(!data) {
		return NULL;
	}
	
//	Circle* c = (Circle*) data;
	
/*	printf("~~~ CIRCLE - %p ~~~\n", c);
	printf("\tcx = %lf\n\tcy = %lf\n\tr = %lf\n", c->cx, c->cy, c->r);
	printf("\tunits = %s\n", c->units);*/
	
	char* string = malloc(sizeof(char) * 5);
	string[0] = 'C';
	string[1] = '\0';
	
	return string;
}
int compareCircles(const void *first, const void *second) {
	// check for NULL
	if(!(first&&second)) {
		return 0;
	}
	
	
	Circle* circle1 = (Circle*) first;
	Circle* circle2 = (Circle*) second;
	
	// return 1 is the areas are equal (only need radius to compare area)
	if(ceil(circle1->r * circle1->r * PI ) == ceil(circle2->r * circle2->r * PI)) {
		return 1;
	}
	
	return 0;
}

void deletePath(void* data) {
	// check for NULL
	if(!data) {
		return;
	}
	
	Path* path = (Path*) data;
	
	// free data 
	free(path->data);
	
	// free miscellaneous attributes  
	freeList(path->otherAttributes);

	// free the struct itself
	free(path);
	
	return;
}

char* pathToString(void* data) {
	// check for NULL
	if(!data) {
		return NULL;
	}
	
	char* string = malloc(sizeof(char) * 5);
	string[0] = 'P';
	string[1] = '\0';
	
	return string;
}
int comparePaths(const void *first, const void *second) {
	// check for NULL
	if(!(first&&second)) {
		return 0;
	}
	
	
	Path* path1 = (Path*) first;
	Path* path2 = (Path*) second;
	
	// return string comparison
	return !strcmp(path1->data, path2->data);
}

