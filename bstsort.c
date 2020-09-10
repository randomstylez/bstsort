#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Author: Joseph Pietroluongo
// PID: 5901749
// I affirm that I wrote this program myself without any help
// from any other people or sources from the internet
// Summary: This program is designed in C language, It is a binary search tree that 
// sorts the lines of an input file and prints the sorted lines to an output file
// which takes the following command line arguments:
// % [-c] [-o output_file_name] [input_file_name] */
// Formatting: Standard formating, opening curly brace on the right end of the line above with the block begins.

// creates Node struct, used to construct nodes, named Node
typedef struct Node{
		char* string;
		int count;
		struct Node *left;
		struct Node *right;
	}Node;

// adds nodes to the tree sorted correctly
void addNodes(Node *rt,Node *node,int cFlag){

	if(rt -> string == NULL){

		rt -> string = node -> string;
		rt -> count++;

	} 

	else if(stringCompare(rt -> string, node -> string, cFlag) == 0){

		rt -> count++;

	} 

	else if(stringCompare(rt -> string, node -> string, cFlag) < 0){

		if(rt -> right == NULL){

			rt -> right = node;
		} 

		else{

			addNodes(rt -> right, node, cFlag);
		}
	}

	else if(stringCompare(rt->string,node->string,cFlag) > 0){

		if(rt -> left == NULL){

			rt -> left = node;

		} 

		else{

			addNodes(rt -> left, node, cFlag);
		}
	}
}

// deletes nodes from the tree
void deleteNodes(struct Node *rt){	

	if(rt -> left != NULL){

		deleteNodes(rt -> left);
	}

	if(rt -> right != NULL){

		deleteNodes(rt -> right);
	}

	if(rt -> left == NULL && rt -> right == NULL){

		free(rt -> string);
		free(rt);
	}
}

// sets pointer to compare strings
int stringCompare(char *str1, char *str2, int cFlag){
    
    //sets string length to pointerlength +1
	int length1 = strlen(str1) + 1;
	int length2 = strlen(str2) + 1;
    char string1[length1];
    char string2[length2];
    strcpy(string1, str1); 
    strcpy(string2, str2); 

        //checks flag
		if(cFlag == 0) {	
			
			//sets all characters to lower case in string1
			// i outside loop to run ocelot correctly
			int i = 0;
			while(i < length1){

				string1[i] = tolower(str1[i]);
				i++;
			}

			// sets all characters to lower case in string 2
			// j outside loop to run ocelot correctly
			int j = 0;
			while(j < length2){

				string2[j] = tolower(str2[j]);	
				j++;
			}	
        }
	
	// i outside loop to run ocelot correctly
	int i = 0;
	for(;i < length1 && i < length2; i++) {

		if(string1[i] < string2[i]){
			return -1;
		} 
		
		else if (string1[i] > string2[i]){	  
		 	return  1;
		}
	}

    //checks length of strings
	if(length1 < length2){
		return -1;
	}

	else if(length1 == length2){
		return 0;
	}

	else{
		return 1;
	}
}

void printNodes(struct Node *rt,FILE *fpoutfile){

	if(rt -> left != NULL){	
		printNodes(rt -> left, fpoutfile);
	}

	// i outside loop to run ocelot correctly
	int i = 0;
	for(;i < rt -> count; i++){	
		fprintf(fpoutfile, rt -> string);
	}
		
	if(rt -> right != NULL){
		printNodes(rt -> right, fpoutfile);
	}	
}

//main method for output
int main(int argc, char **argv){

	// named according to assignment and rubric specifications
	extern char *optarg;
	extern int optind;
	int opt = 0;
	int cFlag = 0; 
	int oFlag = 0; 
	char *inputFile; 
	char *outputFile;
	FILE *fpinfile; 
	char* pdynstring; 
 	Node nodes[500];
	
	// usage copied from assignment specifications 
	static char usage[] = "Usage: bstsort [-c] [-o output_file_name] [input_file_name]\n";

	// Creates cases to be used in commandline using getopt
	while ((opt = getopt(argc, argv, "co:")) != -1){

		switch(opt){

			case 'c':
				cFlag = 1;
				break;
				// break statement allowed in switch function according to assignment specifications 

			case 'o':
				oFlag = 1;
				outputFile = optarg;
				break;

			case '?':
				fprintf(stderr, usage, argv[0]);
				exit(1);

			default:
				fprintf(stderr, usage, argv[0]);
				exit(1);
		}
	}
	
	// sets input file specifications using opt function
	inputFile = argv[optind];		
		
        struct Node root; 
        struct Node* dynNode; 
        char buffer[200];
        int nodeCount = 0;

	// catches no input file
    if(inputFile != NULL){
		
		if(!(fpinfile = fopen(inputFile,"r"))){

			printf("An error has occured: Could not open file: %s\n",inputFile);
			exit(101);
		}
	} 

	// error statements
	else{
		fpinfile = stdin;
		printf("Enter the lines, then enter EOF (Ctrl + D) to finish.\n");				
	}
			
			while( fgets(buffer, 200, fpinfile) != NULL){
				
				if(!(pdynstring = (char *)malloc(strlen(buffer)))){
					printf("An error has occured: No memory is available.\n");
					exit(100);
				}
				
				memcpy(pdynstring, buffer, strlen(buffer));

				if(!(dynNode = (struct Node *)malloc(sizeof(Node)))){
					printf("An error has occured: No memory is available.\n");
				}
				
				dynNode -> string = pdynstring;
				dynNode -> count = 1;
				
				addNodes(&root, dynNode, cFlag);
				nodeCount++;
			}
	
	// output file specifications
	FILE* fpoutfile;
	
	if(oFlag == 1) {

		fpoutfile = fopen(outputFile,"w");
	}

	else{	
		
		fpoutfile = stdout;
	}
		
	printNodes(&root,fpoutfile);
	printf("\n");	

	if(root.left != NULL)
	deleteNodes(root.left);
	if(root.right != NULL)
	deleteNodes(root.right);

	return 0;
}