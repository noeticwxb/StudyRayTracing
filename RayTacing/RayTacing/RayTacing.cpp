// RayTacing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sphere.h"
#include "Triangle.h"
#include <vector>
#include "Image.h"
#include <fstream>
#include "Texture2D.h"

#include <windows.h>   // Standard Header For MSWindows Applications
#include <glut.h>

// The Following Directive Fixes The Problem With Extra Console Window
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Global Variables
bool g_fullscreen;     // Fullscreen Mode ON/OFF (When g_gamemode Is OFF)
const unsigned int CanvasSize = 500;

class Scene
{
public:
	Scene()
	{
		//Shape* s1 = NEW_PTR(Sphere)(Vector3(250, 250, -1000), 150, rgb(0.2f, 0.2f, 0.8f));
		Shape* s1 = NEW_PTR(Sphere)(Vector3(250, 250, -1000), 150, rgb(0.0f, 0.0f, 1.0f));
		mShapes.push_back(s1);

		Shape* s2 = NEW_PTR(Triangle)(
			Vector3(300.0f, 600.0f, -990),
			Vector3(0.0f, 100.0f, -990),
			Vector3(450.0f, 20.0f, -990),
			rgb(0.8f, 0.2f, 0.2f));

		//Shape* s2 = NEW_PTR(Triangle)(
		//	Vector3(250.0f, 250.0f, -1000),
		//	Vector3(250.0f, 100.0f, -1000),
		//	Vector3(500.0f, 0.0f, -1000),
		//	rgb(0.8f, 0.2f, 0.2f));

		mShapes.push_back(s2);

		mImage = NEW_PTR(Image)(CanvasSize, CanvasSize);

		mTexture = NEW_PTR(Texture2D)(CanvasSize, CanvasSize);
	}

	void Render()
	{
		HitTest();

		HitRecord rec;
		bool is_a_hit;
		float tmax;
		Vector3 dir(0, 0, -1);	// direction of viewing rays
		rgb backGround(0.2f, 0.2f, 0.2f);

		for (int i = 0; i < mImage->Width(); i++)
		{
			for (int j = 0; j < mImage->Height(); j++)
			{
				tmax = 100000.0f;
				is_a_hit = false;
				Ray r(Vector3((float)i, (float)j, 0.0f), dir);

				// loop over list of shapes
				for (size_t k = 0; k < mShapes.size(); ++k)
				{
					if (mShapes[k]->hit(r, 0.000001f, tmax, 0, rec))
					{
						tmax = rec.t;
						is_a_hit = true;
					}
				}

				if (is_a_hit)
				{
					mImage->set(i, j, rec.color);
				}
				else
				{
					mImage->set(i, j, backGround);
				}
			}
		}


		mTexture->Update(mImage);
		//CreateImage(img);

		std::ofstream file("d:\\ray_image.ppm", std::ios::binary);
		mImage->writePPM(file);

	}

	void HitTest()
	{
		HitRecord rec;
		int i = 250;
		int j = 250;
		float tmax = 100000;
		Vector3 dir(0, 0, -1);	// direction of viewing rays

		Ray r(Vector3((float)i, (float)j, 0.0f), dir);

		// loop over list of shapes
		for (size_t k = 0; k < mShapes.size(); ++k)
		{
			if (mShapes[k]->hit(r, 0.000001f, tmax, 0, rec))
			{
				//tmax = rec.t;
				//is_a_hit = true;
				std::cout << r.pointAtParameter(rec.t) << std::endl;
			}
		}
	}

	Texture2D* GetTexture2D(){ return mTexture; }

private:
	std::vector<Shape*> mShapes;
	Image* mImage;
	Texture2D* mTexture = NULL;
};


Scene* g_Scene = NULL;


// Our GL Specific Initializations
bool init(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return true;
}


// Our Rendering Is Done Here
void render(void)
{
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);				// Black Background

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	if (g_Scene == NULL)
	{
		g_Scene = NEW_PTR(Scene)();
	}

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint texObj = g_Scene->GetTexture2D()->GetGLObject();
	glBindTexture(GL_TEXTURE_2D, texObj);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);glVertex3f(0, 0, 0);
		glTexCoord2f(0, 1);glVertex3f(1, 0, 0);
		glTexCoord2f(1, 1);glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(0, 1, 0);
	glEnd();


	// Swap The Buffers To Become Our Rendering Visible
	glutSwapBuffers();
}

// Our Reshaping Handler (Required Even In Fullscreen-Only Modes)
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
	// Calculate The Aspect Ratio And Set The Clipping Volume
	//if (h == 0) h = 1;
	//gluPerspective(80, (float)w / (float)h, 1.0, 5000.0);
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
	glLoadIdentity();                // Reset The Modelview Matrix
}

// Our Keyboard Handler (Normal Keys)
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:        // When Escape Is Pressed...
		exit(0);    // Exit The Program
		break;     // Ready For Next Case
	case 114: // r
	case 82: // R
		if (g_Scene!=NULL)
		{
			g_Scene->Render();
		}
		glutPostRedisplay();
		break;
	default:        // Now Wrap It Up
		break;
	}
}

// Our Keyboard Handler For Special Keys (Like Arrow Keys And Function Keys)
void special_keys(int a_keys, int x, int y)
{
	switch (a_keys) {
	case GLUT_KEY_F1:
		// We Can Switch Between Windowed Mode And Fullscreen Mode Only
			g_fullscreen = !g_fullscreen;       // Toggle g_fullscreen Flag
			if (g_fullscreen) glutFullScreen(); // We Went In Fullscreen Mode
			else glutReshapeWindow(500, 500);   // We Went In Windowed Mode
		break;

	default:
		break;
	}
}


int main(int argc, char* argv[])
{

                             // Ask For Fullscreen Mode
	glutInit(&argc, argv);                           // GLUT Initializtion
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);     // Display Mode (Rgb And Double Buffered)

	glutInitWindowSize(500, 500);                // Window Size If We Start In Windowed Mode
	glutCreateWindow("NeHe's OpenGL Framework"); // Window Title 

	init();                                          // Our Initialization
	glutDisplayFunc(render);                         // Register The Display Function
	glutReshapeFunc(reshape);                        // Register The Reshape Handler
	glutKeyboardFunc(keyboard);                      // Register The Keyboard Handler
	glutSpecialFunc(special_keys);                   // Register Special Keys Handler
	glutMainLoop();                                  // Go To GLUT Main Loop

	SAFE_DELETE_ARRAY(g_Scene);
	return 0;
}



