#ifndef HELPER_H
#define HELPER_H

// image populator (recursive)
void bog(SVGimage* image, xmlNode *root);

// unsigned string comparison
int strcmpu(const unsigned char* s1, const char* s2);

// Adds data to a linked list, if the linked list is null, creates one. returns
List* addToList(List* head, void* data, char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted));

/*
 * These functions will malloc space for a shape and populate it with information.
 */

Rectangle* parseRect(xmlNode* cur_node);
Circle* parseCircle(xmlNode* cur_node);
Path* parsePath(xmlNode* cur_node);

// specific for group
Group* parseGroup(xmlNode* groupNode);

// add attribute
Attribute* addAttribute(char* attrName, char* cont);


/*
 * Functions used to convert strings to inetgers and floats.
 */
int stringToInt(char* string, char* end);

/*
 * Additional delete group function to avoid recursive scnerio when deleting
 * a group from within a group
 */
void deleteGroupFromGroup(void* data);// not implemented


/*
 * Functions for returning copied lists of specified data;
 */

// returns a list of elements that follow the compare function
int findElements(List * list, const void* searchRecord,
int (*compareFunction)(const void* first,const void* second)
);

// return the length of a group
int getGroupLength(Group* group);


//
int returnNumAttributes(Group* g, int is


//
int groupAttributeHunter(Group* g) {
	int numAttributes = 0;
	ListIterator itr = createIterator(list);
	
	// add the other attributes from the group
	numAttributes += getLength(g->otherAttributes);
	
	for(getLength(g->groups)) {
		//
		numAttributes += groupAttributeHunter(g
	}
	
	return numAttributes;
}

// 
int attributeHunter(int* numAttributes, xmlNode* root) {
	
	
	// add the other attributes
	*numAttributes += getLength(
	
	
}

#endif