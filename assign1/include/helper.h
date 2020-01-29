#ifndef HELPER_H
#define HELPER_H

// puts two lists of the same type into one longer list
List* combineList(List* source, List* destination);


/*
 *	
 */
// rect
List* getAllRectsFromGroups(Group* g, List* list);
List* getAllCirclesFromGroups(Group* g, List* list);
List* getAllGroupsFromGroups(Group* g, List* list);
List* getAllPathsFromGroups(Group* g, List* list);


// 
void* goThroughGroup(Group* g);

// return all the attributes collected in groups
int goThroughGroupAndAddAttributes(Group* g);

// returns the number of otherAttributes in a given list
// 1 = rectangles, 2 = circles, 3 = paths, 4 = groups, 0 = cancel
int attributeListCounter(List* list, int test);


// image populator BOG -- (build out groups)
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
int returnNumAttributes(void* node, int isGroup);


//
int groupAttributeHunter(Group* g);
// 
int attributeHunter(xmlNode* root);

#endif