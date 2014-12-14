
/* ObjectImporter.h

  This comes from an assmebly of tutorials found on www.gametutorials.com
  The union of the fiesl and minor enhancements and funcitonalities were added by
  Anthoyn Aquilio.


*/


#ifndef _OBJECTIMPORTER_H
#define _OBJECTIMPORTER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <GL/gl.h>										// Header File For The OpenGL32 Library
#include <GL/glut.h>										// Header File For The GLu32 Library

#include "BMPLoader.h"

using namespace std;


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

// This file includes all of the model structures that are needed to load
// in a .3DS file.  If you intend to do animation you will need to add on
// to this.  These structures only support the information that is needed
// to load the objects in the scene and their associative materials.

#define MAX_TEXTURES 100								// The maximum amount of textures to load

// This is our 3D point class.  This will be used to store the vertices of our model.
class CVector3 
{
public:
	float x, y, z;
};

// This is our 2D point class.  This will be used to store the UV coordinates.
class CVector2 
{
public:
	float x, y;
};

// This is our face structure.  This is is used for indexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	int coordIndex[3];			// indicies for the tex coords to texture this face
};

// This holds the information for a material.  It may be a texture map of a color.
// Some of these are not used, but I left them because you will want to eventually
// read in the UV tile ratio and the UV tile offset for some models.
struct tMaterialInfo
{
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	unsigned char  color[3];				// The color of the object (R, G, B)
	int   texureId;				// the texture ID
	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)
} ;

// This holds all the information for our model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject 
{
	int  numOfVerts;			// The number of verts in the model
	int  numOfFaces;			// The number of faces in the model
	int  numTexVertex;			// The number of texture coordinates
	int  materialID;			// The texture ID to use, which is the index into our texture array
	bool bHasTexture;			// This is TRUE if there is a texture map for this object
	char strName[255];			// The name of the object
	CVector3  *pVerts;			// The object's vertices
	CVector3  *pNormals;		// The object's normals
	CVector2  *pTexVerts;		// The texture's UV coordinates
	tFace *pFaces;				// The faces information of the object
};

// This holds our model information.  This should also turn into a robust class.
// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
struct t3DModel 
{
	int numOfObjects;					// The number of objects in the model
	int numOfMaterials;					// The number of materials for the model
	vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	vector<t3DObject> pObject;			// The object list for our model
};


// This creates a texture and stores it in the texture array with it's ID.
void CreateTexture(unsigned int textureArray[], char * strFileName, int textureID);

// This creates a texture from a *.bmp and stores it in the texture array with it's ID.
void CreateBMPTexture(unsigned int textureArray[], char * strFileName, int textureID);

/////////////////////////////////////////////////////////////////////////////////
//***********************************************************************//
//																		 //
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 //
//                                                                       //
//		$Author:		DigiBen		digiben@gametutorials.com			 //
//																		 //
//		$Program:		3DS Loading										 //
//																		 //
//		$Description:	Functions to load a .3ds file format		 //
//																		 //
//		$Date:			10/6/01											 //
//																		 //
//***********************************************************************//
#include "3ds.h"					// Include the 3DS header file.

int   g_ViewMode	  = GL_TRIANGLES;					// We want the default drawing mode to be normal

////////////////////////////////////////////////////////////////////////////////
//  String function implemetations by A Aquilio
////////////////////////////////////////////////////////////////////////////////
/*Purpose: 
	The string functions used in the Object3DS class for searching for a 
	substring within a string. 
	
	  For example: Given a filename texture.bmp, look for the substring
	   .bmp.  This can the  be used to determine fiel types based on the 
	   extension assigned to the filename. This is simply used as a utility
	   of function for parsing the filename to determine fiel type.
*/

//Note: A String is regarded as an array of characters with the end 
//of the string delimted by the null character

bool HasSubstring(char* string, char* substring);
void CopyString(char* original, char* copy);
int GetStringLength(char* string);
void StringToLower(char* string);
void StringToUpper(char* string);
/* This takes in two strings and checks to see if one is contained 
	as a substriong within the other upper vs. lower case is ignored 
	and the parameter strings are unchanged.
*/
bool HasSubstring(char* string, char* substring) {

	int length = GetStringLength(string);
	int index = 0;
	int subindex = 0;
	bool token = false;

	char* strtmp = new char[length + 1];
	char* subtmp = new char[length + 1];

	CopyString(string, strtmp);
	CopyString(substring, subtmp);

	StringToLower(strtmp);
	StringToLower(subtmp);

	while(strtmp[index] != '\0' && token == false)
	{
	//	cout << strtmp[index] << " vs " << subtmp[subindex] << endl;
		if(subtmp[subindex + 1] == '\0') {
			token = true;
		}
		else {
			if(strtmp[index] == subtmp[subindex]) {
				subindex++;
			}
			index++;
		}
	}
	
	return token;
}

/* This takes in a string and converts all alphabetical characters 
	to lower case.
*/
void StringToLower(char* string) {

	int length = GetStringLength(string);

	for(int i = 0; i < length; i++) {
		if(string[i] >= 65 && string[i] <=90 )
		{
			string[i] = string[i] + 32;
		}
	}
}

/* This takes in a string and converts all alphabetical characters 
	to upper case.
*/
void StringToUpper(char* string) {

	int length = GetStringLength(string);

	for(int i = 0; i < length; i++) {
		if(string[i] >= 97 && string[i] <=122 )
		{
			string[i] = string[i] - 32;
		}
	}
}

/* This takes in a string and counts its length based on the number 
	of characters preceeding the termination signifier.
	(i.e. the null character).
*/
int GetStringLength(char* string) {
	int length = 0;

	while(string[length] != '\0') {
		length++;
	}

	return length;

}

/* This takes in two pre allocated arrays/string storage space 
	and copies the ocntents of the original string into the copy 
	string space.

	PLEASE NOTE: It is required that the memory allocation take 
	place prior to calling this function.
*/
void CopyString(char* original, char* copy) {

	int length;
	length = GetStringLength(original);

	for(int i = 0; i <= length; i++) {
		copy[i] = original[i];
	}

	return;
}
///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This creates a texture in OpenGL that we can texture map
/////
///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
void CreateTexture(unsigned int textureArray[], char * strFileName, int textureID)
{

	if(HasSubstring(strFileName, ".bmp")) 
	{ 
		CreateBMPTexture(textureArray, strFileName, textureID); 
	}

	return;
}

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


////////////////////////////////////////////////////////////////////////////////////////
void CreateBMPTexture(unsigned int textureArray[], char * strFileName, int textureID)
{

	FILE *pFile = NULL;									// The File Handle we will use to read the bitmap

	BMPClass pBitmap;

	if(!strFileName)									// Return from the function if no file name was passed in
		return;

	pFile = fopen(strFileName,"r");						// Check To See If The File Exists

	if(pFile)											// If we have a valid file pointer we found the file
	{
		string myStr(strFileName);
		BMPLoad(myStr,pBitmap);
		//pBitmap = auxDIBImageLoad(strFileName);			// Load the bitmap and store the data
	}
	else												// If we can't find the file, quit!
	{													// Prompt the error message
		printf("Couldn't find a texture! - Error!\n");
		//MessageBox(NULL, "Couldn't find a texture!", "Error!", MB_OK);
		exit(0);
	}

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// This sets the alignment requirements for the start of each pixel row in memory.
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap.width, pBitmap.height, GL_RGB, GL_UNSIGNED_BYTE, pBitmap.bytes);
	//glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);

	// Lastly, we need to tell OpenGL the quality of our texture map.  GL_LINEAR is the smoothest.
	// GL_NEAREST is faster than GL_LINEAR, but looks blochy and pixelated.  Good for slower computers though.
	// Read more about the MIN and MAG filters at the bottom of main.cpp
		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

/*
	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture

	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
		{
			free(pBitmap->data);						// Free the texture data, we don't need it anymore
		}

		free(pBitmap);									// Free the bitmap structure
	}
*/
}


/////////////////////////////////////////////////////////////////////////////////
//
// * NOTES * 
// 
// I would like to thank wosit.org and Terry Caton (tcaton@umr.edu) for his help on this.
//
// Let me know if this helps you out!
// 
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
// © 2001 GameTutorials

#endif 
