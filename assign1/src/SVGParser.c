#include "SVGParser.h"

#define PI 3.14159265359

void printer() {
	puts("hello. Printer has been called.");
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
//SVGimage* createSVGimage(char* fileName);

/** Function to create a string representation of an SVG object.
 *@pre SVGimgage exists, is not null, and is valid
 *@post SVGimgage has not been modified in any way, and a string representing the SVG contents has been created
 *@return a string contaning a humanly readable representation of an SVG object
 *@param obj - a pointer to an SVG struct
**/
//char* SVGimageToString(SVGimage* img);

/** Function to delete image content and free all the memory.
 *@pre SVGimgage  exists, is not null, and has not been freed
 *@post SVSVGimgageG  had been freed
 *@return none
 *@param obj - a pointer to an SVG struct
**/
//void deleteSVGimage(SVGimage* img);


// Function that returns a list of all rectangles in the image.  
List* getRects(SVGimage* img) {
	return img->rectangles; // fix this
}

// Function that returns a list of all circles in the image.  
List* getCircles(SVGimage* img) {
	return img->circles; // fix this
}

// Function that returns a list of all groups in the image.  
List* getGroups(SVGimage* img) {
	return img->groups; // fix this
}

// Function that returns a list of all paths in the image.  
List* getPaths(SVGimage* img) {
	linkedPrinter();
	return img->paths; // fix this
}

///////////////WIP WIP ///////////////WIP WIP ///////////////WIP WIP 
// Function that returns the number of all rectangles with the specified area
int numRectsWithArea(SVGimage* img, float area) {
	int matches = 0;
	List* rectangles = img->rectangles; // linked list of rectangles
	
	// initialize the currentNode to the first node
	Node* currentNode = getFromFront(rectangles);
	
	// create a list iterator to traverse the list
	ListIterator iterator = createIterator(rectangles);
	
	while(currentNode != NULL) {
		//
		
	}
	
	return matches;
}

// Function that returns the number of all circles with the specified area
int numCirclesWithArea(SVGimage* img, float area);

// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(SVGimage* img, char* data);

// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(SVGimage* img, int len);

// Sums all the attributes
int numAttr(SVGimage* img) {
	int attributes = 0;
	
	// TODO
	
	return attributes;
}


void deleteAttribute( void* data);
char* attributeToString( void* data);
int compareAttributes(const void *first, const void *second) {
	return 0;
}


void deleteGroup(void* data);
char* groupToString( void* data);
int compareGroups(const void *first, const void *second) {
	return 0;
}


void deleteRectangle(void* data);
char* rectangleToString(void* data);
int compareRectangles(const void *first, const void *second) {
	return 0;
}


void deleteCircle(void* data);
char* circleToString(void* data);
int compareCircles(const void *first, const void *second) {
	return 0;
}


void deletePath(void* data);
char* pathToString(void* data);
int comparePaths(const void *first, const void *second) {
	return 0;
}
