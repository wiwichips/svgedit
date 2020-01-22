#include "SVGParser.h"
#include "helper.h"

#define PI 3.14159265359

// Will Pringle's Helper functions

void printer() {
	puts("hello. Printer has been called.");
}

// misc helper functions

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

	
	// allocate space for a rectanle and create list of other Attributes
	rect = malloc(sizeof(Rectangle));
	rect->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next)
	{
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		
		if(!strcmp(attrName, "x")) {
			x = strtof(cont, NULL);
			rect->x = x;
			
		} else if(!strcmp(attrName, "y")) {
			y = strtof(cont, NULL);
			rect->y = y;
			
		} else if(!strcmp(attrName, "width")) {
			width = strtof(cont, &end);
			rect->width = width;
			
		} else if(!strcmp(attrName, "height")) {
			height = strtof(cont, NULL);	
			rect->height = height;
			
		// all othre attributes go here
		} else {
			
			// add the attribute to the list
			insertBack(rect->otherAttributes, addAttribute(attrName, cont));
			
		}
		
	}
	
	// copy the units from the x to the units in the struct
	strcpy(rect->units, end);

	return rect;
}

Circle* parseCircle(xmlNode* cur_node) {
	xmlAttr* attr;
	Circle* circle;
	float cx = 0;
	float cy = 0;
	float r = 0;
	char* end; // used to get units

	
	// allocate space for a rectanle and create list of other Attributes
	circle = malloc(sizeof(Rectangle));
	circle->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next)
	{
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		
		if(!strcmp(attrName, "cx")) {
			cx = strtof(cont, NULL);
			circle->cx = cx;
			
		} else if(!strcmp(attrName, "cy")) {
			cy = strtof(cont, NULL);
			circle->cy = cy;
			
		} else if(!strcmp(attrName, "r")) {
			r = strtof(cont, &end);
			circle->r = r;
			
			
		// all othre attributes go here
		} else {
			
			// add the attribute to the list
			insertBack(circle->otherAttributes, addAttribute(attrName, cont));
			
		}
		
	}
	
	// copy the units from the x to the units in the struct
	strcpy(circle->units, end);

	return circle;
}

Path* parsePath(xmlNode* cur_node) {
	xmlAttr* attr;
	Path* path;
	char* data;

	// allocate space for a rectanle and create list of other Attributes
	path = malloc(sizeof(Rectangle));
	path->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &comparePaths);
	
	// go through each attribute
	for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
		xmlNode *value = attr->children;
		char *attrName = (char *)attr->name;
		char *cont = (char *)(value->content);
		
		if(!strcmp(attrName, "d")) {
			data = malloc(sizeof(char) * strlen(cont));
			strcpy(data, cont);
			puts("hello world");
			
		// all othre attributes go here
		} else {
			
			// add the attribute to the list
			insertBack(path->otherAttributes, addAttribute(attrName, cont));
			
		}	
	}

	return path;
}

void bog(SVGimage* image, xmlNode *root) {
	
	xmlNode *cur_node = NULL;

	// while the current node isn't null, set it to the next node
    for (cur_node = root; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("######type/element/name#######: %s\n", cur_node->name);
			
			// copy namespace to svgimage
			if(!strcmpu(cur_node->name, "svg")) {
				strcpy(image->title, (char*) cur_node->ns->href);
				printf("(PF) %s\t(hr) %s\n", cur_node->ns->prefix, cur_node->ns->href);
				
			}
			
			// place in title, description
			else if(!strcmpu(cur_node->name, "title")) {
				strcpy(image->title, (char*) cur_node->name);
				printf("{%s}", (char*) cur_node->children->content);
				
			} else if(!strcmpu(cur_node->name, "desc")) {
				strcpy(image->description, (char*) cur_node->name);
				
			}
			
			// place in rectangles, circles, paths, groups
			else if(!strcmpu(cur_node->name, "rect")) {
				strcpy(image->title, (char*) cur_node->name);
				puts("rectangle ");
				deleteRectangle(parseRect(cur_node)); // purposes
				
				
			} else if(!strcmpu(cur_node->name, "circle")) {
				strcpy(image->description, (char*) cur_node->name);
				
				deleteCircle(parseCircle(cur_node));
				
			} else if(!strcmpu(cur_node->name, "path")) {
				strcpy(image->title, (char*) cur_node->name);
				deletePath(parsePath(cur_node));
				
			}
			
			// groups
			else if(!strcmpu(cur_node->name, "g")) {
				strcpy(image->description, (char*) cur_node->name);
				puts("group\n");
				
			}
			
        }

		// this will check successive groups
		bog(image, cur_node->children);

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
	
	xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
	
	SVGimage *image = NULL;

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    // parse the file and get the DOM
    doc = xmlReadFile(fileName, NULL, 0);
	
	// if xml had problems
	if(doc == NULL) {
		puts("LIB XML cannot open the file.");
		return NULL;
	}
	
	// Get the root element node
    root_element = xmlDocGetRootElement(doc);
	
	/*
	 * Create and allocate the stuf for the 
	 * SVGImage
	 *
	 * if nothing is found, give it a null string.
	 */
	// CREATE SPACE FOR SVGIMAGE
	image = malloc(sizeof(SVGimage));
	
	// tempoarily setting list variables to NULL
	image->rectangles = initializeList(&rectangleToString, &deleteRectangle, &comparePaths);
	image->circles = initializeList(&rectangleToString, &deleteCircle, &comparePaths);
	image->paths = initializeList(&rectangleToString, &deletePath, &comparePaths);
	image->groups = initializeList(&rectangleToString, &deleteGroup, &comparePaths);
	
	// populating the svgimage
	bog(image, root_element);
	
	// frees
    xmlFreeDoc(doc); // free document
    xmlCleanupParser(); // free global variable 
	
// testing free
freeList(image->rectangles);
freeList(image->circles);
freeList(image->paths);
freeList(image->groups);
	
	
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

/*
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
*/
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


void deleteAttribute( void* data) {
	Attribute* a = (Attribute*) data;
	
	// free name and value
	free(a->name);
	free(a->value);
	
	// free the struct itself
	free(a);

	return;
}
char* attributeToString( void* data) {
	return "attributeToString";
}
int compareAttributes(const void *first, const void *second) {
	return 0;
}


void deleteGroup(void* data) {
	
	
	return;
}
char* groupToString( void* data){
	return "groupToString";
}
int compareGroups(const void *first, const void *second) {
	return 0;
}


void deleteRectangle(void* data) {
	Rectangle* rect = (Rectangle*) data;
	
	// free miscellaneous attributes  
	freeList(rect->otherAttributes);

	// free the struct itself
	free(rect);
	
	return;
}
char* rectangleToString(void* data) {
	return "rect to string";
}
int compareRectangles(const void *first, const void *second) {
	return 0;
}


void deleteCircle(void* data) {
	Circle* circle = (Circle*) data;
	
	// free miscellaneous attributes  
	freeList(circle->otherAttributes);

	// free the struct itself
	free(circle);
	
	return;
}
char* circleToString(void* data) {
	return "circle to string";
}
int compareCircles(const void *first, const void *second) {
	return 0;
}


void deletePath(void* data) {
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
	return "pathToString";
}
int comparePaths(const void *first, const void *second) {
	return 0;
}
