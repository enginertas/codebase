
/*

  Class: Object3DS
  Assembled & Commented by: Anthony Aquilio
  Date: July 30th, 2002

  Please Note most coding is assembled from: http://www.gametutorials.com


  Prelude: The purpose of this Class is to provide a wrapper to the 
  tutorial found on www.gamedtutorials.com on a 3DS File Loader. I 
  have taken it upon myself to provide a class using code developed by

// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com

  I have added funcitonality not contained within the tutorial he has 
  supplied. Read further to find out if this class offers what you need. 
  And if not I ask you to continue on with my work and devlop this further.

  TODO: I will do my best in time to remove O.S. dependent code.

*/

#ifndef OBJECT3DS_H
#define OBJECT3DS_H


#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <string.h>


#include "ObjectImporter.h"
#include "3ds.h"

/* Class Object3DS is the name for all types that will use the 
	functionality within this class. In other owrds, when you 
	use this type, you will be creating an instance of the Object3DS type.

	EXAMPLE: Object3DS TheObject();
	*/
class Object3DS {

	//public functions are allowed to be used by you on otehr classes
public: 

	/* Object3DS(): Constructor for an instance of the class.  This will 
		initialize all default values to any attributes contained within 
		the class.
	*/
	Object3DS();

	/* Initialize(): Initializes an Object3DS instance to parse the 
		information contained within a *.3DS file.

       ***** The Tricky Part *****

		Some 3DS files require use texture mapping from files. Currently, 
			there is only support in this class for 3DS files that use 
			certain	image file types.  Those supported are

			1. Bitmap files
			2. NO Texture Map Image Files

			All other image file formats are currently unsupported, 
			( i.e. you cannot use object that use GIF, TIFF, PNG, etc.).

		Also, when it comes time to figure out what texture files are 
		what format, I use an archaic method.  The extension is the 
		identifying factor (hence the inclusion of a simple string
		function class). Thus...

			1. Bitmaps are specified by a *.bmp
	
		All other file tpyes are ignored and attempting to use 
			objects that require them will most likely cause the 
			applicaiton to crash when you attempt to use the 
			Initialization() function.
	*/
	void Initialize(char* filename);


	/* Render(): If an object is initialized, this will render the object 
		into the coordinate space at the positon specified by the user, 
		and the object will be rotated (IN PLACE) according to the rotation 
		angles specified by the user by calling the private local rendering 
		function aftermaking adjustments for coordinate transformations.
	*/
	void Render();

	/* SetPosition(): Sets the stored object's position within the 3D 
		coordinate space. NOTE: The relative position is dependent on the
		current scalar value and rotation angles. This is to say 
		that if you have alterd either/both of these then attempt 
		to place the object at (0.0f, 0.0f, 0.0f), it may or may NOT 
		!!!APPEAR!!! to be at the relative cooridnate.
	*/
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	/* Rotate(): Rotates the currently stored object around in the x, y 
		and z directions. The real trick here is I have added code so 
		that you can move the object to some position and them rotate it.
		The continue drawing as if the object had been in that 
		rotation originally. All subsequent calls to this will regard 
		the last Rotatation angles specified as the current rotation.  
		So you must rest the rotation angles.

		Also: The angle of Rotation does not stack!!!  Rotatation angles are 
		relative to the original orientaiton of the object within the
		3DS file.  So, if you want to animate a=n object rotating, you 
		would have increment the rotation angle manually and pass that 
		"ever-changing" value to this funciton.
	*/
	void Rotate(GLfloat x_direction, GLfloat y_direction, GLfloat z_direction);

	/*ResetRotation(): Resets the Rotation angles.  This would be the 
		same as making the call TheObject.Rotate(0.0f, 0.0f, 0.0f);
		*/
	void ResetRotation();

	/*SetScalar(): Sets the scalar multiple of the obejct to 
		increase/reduce its size. 
		
		  To shrink the object pass in values:	0.0f < Scalar < 1.0f
		  To keep the object the original size let:	Scalar = 1.0f
		  To enlarge the object pass in values:	1.0f < Scalar

		Note: Negative values result on the default value being 
			used (i.e. scalar = 1.0f)
		*/
	void SetScalar(GLfloat Scalar);

	/*SetMonochromeColor(): This assigns an RGB value to the instance. 
		When drawing an object you have the option to use the colros specified
		in the 3DS file, or you can give one Monochrome value to apply to the 
		object that you specify with this function.
		
		 Default: red = green = blue = 1.0f, color is white
		*/
	void SetMonochromeColor(GLfloat red, GLfloat green, GLfloat blue);

	/*UseMonochrome(): The flag tells whether to use the monochrome 
		color currently set to the instance.
		
		  if flag=true: The monochrome color will be applied.
		  if flag=false: Use the 3DS color specification.
		*/
	void UseMonochrome(bool flag);

	
private:

	/* Model_Load: An instance of the CLOad3DS object developed by Digiben.
		Theinstance is used to parse the 3DS file and retireve useful and 
		necessary contents
	*/
	CLoad3DS Model_Load;

	/*Model_Info: An instance of the t3DModel developed by Digiben. 
		The instance here holds the 3D model info loaded from the 3DS file.
		*/
	t3DModel Model_Info;// This holds the 3D Model info that we load in

	GLfloat scalar;

	/* xPosition: Stores the current x-position of the object.*/
	GLfloat xPosition;

	/* yPosition: Stores the current y-position of the object.*/
	GLfloat yPosition;

	/* zPosition: Stores the current z-position of the object.*/
	GLfloat zPosition;

	/* xRotation: Stores the current angle of rotation around the x-axis.*/
	GLfloat xRotation;

	/* yRotation: Stores the current angle of rotation around the z-axis.*/
	GLfloat yRotation;

	/* zRotation: Stores the current angle of rotation around the y-axis.*/
	GLfloat zRotation;

	/* strX: Stores the original x-position, regardless of manipulations.*/
//	GLfloat strX;

	/* strY: Stores the original y-position, regardless of manipulations.*/
//	GLfloat strY;

	/* strZ: Stores the original z-position, regardless of manipulations.*/
//	GLfloat strZ;

	/* Textures: An array for holding the texture info, and is referenced by an ID.
	*/
	unsigned int *Textures;

	/* R: Stores the Red component for use with an object that is designated
		to use a monochromatic color specified by the user. 
		Default value is 1.0f.
	*/
	GLfloat R;

	/* G: Stores the Green component for use with an object that is designated
		to use a monochromatic color specified by the user. 
		Default value is 1.0f.
	*/
	GLfloat G;

	/* B: Stores the Blue component for use with an object that is designated
		to use a monochromatic color specified by the user. 
		Default value is 1.0f.
	*/
	GLfloat B;
	bool userDefinedRGB;

	/* LocalRender: This function actually does the rendering in the 
		translated & Rotated cooridinate space.
	 */
	void LocalRender();
};

//////////////////////////////////////////////////////////////////////////////////


// This code was mostly taken from http://www.gametutorials.com
// necessary modifications, compilation and assembly was done by 
// Anthony Aquilio.
//Date: July 30, 2002

//see the header file for comments and user descriptions


Object3DS::Object3DS() {

	Textures = new unsigned int[MAX_TEXTURES];

	this->SetScalar(1.0f);
	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->ResetRotation();

	userDefinedRGB = false;
	this->SetMonochromeColor(1.0f, 1.0f, 1.0f);

	Model_Info.numOfObjects = 0;
    Model_Info.numOfMaterials = 0; 

}

void Object3DS::Initialize(char* filename){
// Objects in the study
	// First we need to actually load the .3DS file.  We just pass in an address to
	// our t3DModel structure and the file name string we want to load ("face.3ds").
	
	Model_Load.Import3DS(&Model_Info, filename); // Load our .3DS file into our model structure

	// Depending on how many textures we found, load each one (Assuming .bmp, .jpg, .jpeg, .tga)
	// If you want to load other files than those, you will need to adjust CreateTexture().

	// Below, we go through all of the materials and check if they have a texture map to load.
	// Otherwise, the material just holds the color information and we don't need to load a texture.

	// Go through all the materials

	for(int i = 0; i < Model_Info.numOfMaterials; i++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(Model_Info.pMaterials[i].strFile) > 0)
		{
//********************************************************************************
//Use this cout statement to find out if a texture file is needed by an 3DS object
//for proper rednering

//	cout <<" *****\n" <<
//		Model_Info.pMaterials[i].strFile 
//			<< " loading for use with for " << filename << endl;
//********************************************************************************	
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
			CreateTexture(Textures, Model_Info.pMaterials[i].strFile, i);
		}

		// Set the texture ID for this material
		Model_Info.pMaterials[i].texureId = i;
	}
}

void Object3DS::Render(){

	glPushMatrix();

	glTranslatef(xPosition, yPosition, zPosition);
	//turn the coordinate space to rotate the object
			glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
			glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
			glRotatef(zRotation, 0.0f, 0.0f, 1.0f);

	this->LocalRender();

		//turn the coordinate space back to the orignal orientation
			glRotatef((360.0f - xRotation), 1.0f, 0.0f, 0.0f);
			glRotatef((360.0f - yRotation), 0.0f, 1.0f, 0.0f);
			glRotatef((360.0f - zRotation), 0.0f, 0.0f, 1.0f);

		//Move the drawing context back to the starting position
		glTranslatef(-1.0f * xPosition, -1.0f * yPosition, -1.0f * zPosition);
	glPopMatrix();
}

void Object3DS::LocalRender(){
//int tic = 0;
	// Since we know how many objects our model has, go through each of them.
	for(int i = 0; i < Model_Info.numOfObjects; i++)
	{
		// Make sure we have valid objects just in case. (size() is in the vector class)
		if(Model_Info.pObject.size() <= 0) break;

		// Get the current object that we are displaying
		t3DObject *pObject = &Model_Info.pObject[i];
			
		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) {

			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to white
			glColor3f(1.0f, 1.0f, 1.0f);

			// Bind the texture map to the object by it's materialID
			glBindTexture(GL_TEXTURE_2D, Textures[pObject->materialID]);
		} else {

			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to white
			glColor3f(1.0f, 1.0f, 1.0f);
		}

		glBegin(GL_TRIANGLES);					// Begin drawing with our selected mode (triangles or lines)
			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				glPushMatrix();

				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the index for each point of the face
					int index = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) {

						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) {
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} else {

						// Make sure there is a valid material/color assigned to this object.
						// You should always at least assign a material color to an object, 
						// but just in case we want to check the size of the material list.
						// if the size is at least one, and the material ID != -1,
						// then we have a valid material.
						if(Model_Info.pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							BYTE *pColor = Model_Info.pMaterials[pObject->materialID].color;

							// Assign the current color to this model
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					if(userDefinedRGB) { glColor3f(R, G, B); }
					
					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(
						pObject->pVerts[ index ].x * scalar,// + xPosition, 
						pObject->pVerts[ index ].y * scalar, // + yPosition, 
						pObject->pVerts[ index ].z * scalar);// + zPosition);
				}
				glPopMatrix();
			}
		glEnd();

	}// End the drawing

}

void Object3DS::SetPosition(GLfloat x, GLfloat y, GLfloat z) {

	xPosition = x;
	yPosition = y;
	zPosition = z;

}

void Object3DS::Rotate(GLfloat x, GLfloat y, GLfloat z) {

	this->ResetRotation();

	xRotation = x + xRotation;
	yRotation = y + yRotation;
	zRotation = z + zRotation; 

}

void Object3DS::ResetRotation() {

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;

}

void Object3DS::SetScalar(GLfloat Scalar) 
{
	if(Scalar < 0.0f) {scalar = 1.0f; }
	else { scalar = Scalar;}
}

void Object3DS::SetMonochromeColor(GLfloat red, GLfloat green, GLfloat blue) {

	R = red;
	G = green;
	B = blue;
}

void Object3DS::UseMonochrome(bool flag) { userDefinedRGB = flag; }

#endif
