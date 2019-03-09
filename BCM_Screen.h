
#include <iostream>

#include <GLES/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <SDL/SDL.h>
 #include  "bcm_host.h"


#define _RPI_ 1

using namespace std;

#define LOG(LOGERROR) cout



namespace BCM_Screen
{

	void exitfunc()
{
  SDL_Quit();
  bcm_host_deinit();
}

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;

#ifdef _RPI_
	static EGL_DISPMANX_WINDOW_T nativewindow;
#endif

	unsigned int display_width = 1366;
	unsigned int display_height = 768;

	unsigned int getScreenWidth() { return display_width; }
	unsigned int getScreenHeight() { return display_height; }



	bool createSurface() //unsigned int display_width, unsigned int display_height)
	{
                bcm_host_init();
                atexit(exitfunc);

		LOG(LogInfo) << "Starting SDL...";








		LOG(LogInfo) << "Creating surface...";



#ifdef _RPI_
		DISPMANX_ELEMENT_HANDLE_T dispman_element;
		DISPMANX_DISPLAY_HANDLE_T dispman_display;
		DISPMANX_UPDATE_HANDLE_T dispman_update;
		VC_RECT_T dst_rect;
		VC_RECT_T src_rect;
#endif



		display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if(display == EGL_NO_DISPLAY)
		{
			LOG(LogError) << "Error getting display!";
			return false;
		}

		bool result = eglInitialize(display, NULL, NULL);
		if(result == EGL_FALSE)
		{
			LOG(LogError) << "Error initializing display!";
			return false;
		}

		result = eglBindAPI(EGL_OPENGL_ES_API);
		if(result == EGL_FALSE)
		{
			LOG(LogError) << "Error binding API!";
			return false;
		}


		static const EGLint config_attributes[] =
		{
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_NONE
		};

		GLint numConfigs;
		result = eglChooseConfig(display, config_attributes, &config, 1, &numConfigs);

		if(result == EGL_FALSE)
		{
			LOG(LogError) << "Error choosing config!";
			return false;
		}


		context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
		if(context == EGL_NO_CONTEXT)
		{
			LOG(LogError) << "Error getting context!\n	" << eglGetError();
			return false;
		}

#ifdef _RPI_
        //get hardware info for screen/desktop from BCM interface
		if(!display_width || !display_height)
		{
			bool success = graphics_get_display_size(0, &display_width, &display_height); //0 = LCD

			if(success < 0)
			{
				LOG(LogError) << "Error getting display size!";

				return false;
			}
		}
#else

#endif

		LOG(LogInfo) << "Resolution: " << display_width << "x" << display_height << "...";

#ifdef _RPI_
		dst_rect.x = 0; dst_rect.y = 0;
		dst_rect.width = display_width; dst_rect.height = display_height;

		src_rect.x = 0; src_rect.y = 0;
		src_rect.width = display_width << 16; src_rect.height = display_height << 16;

		dispman_display = vc_dispmanx_display_open(0); //0 = LCD
		dispman_update = vc_dispmanx_update_start(0);

		dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0 /*layer*/, &dst_rect, 0 /*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0 /*clamp*/, DISPMANX_NO_ROTATE /*transform*/);

		nativewindow.element = dispman_element;
        nativewindow.width = display_width; nativewindow.height = display_height;
        vc_dispmanx_update_submit_sync(dispman_update);
#endif

		surface = eglCreateWindowSurface(display, config, &nativewindow, NULL);
		if(surface == EGL_NO_SURFACE)
		{
			LOG(LogError) << "Error creating window surface!";
			return false;
		}

		result = eglMakeCurrent(display, surface, surface, context);
		if(result == EGL_FALSE)
		{
			LOG(LogError) << "Error with eglMakeCurrent!";
			return false;
		}


		LOG(LogInfo) << "Created surface successfully!";


		return true;
	}



	 void SwapBuffers()
	{
	//glClearColor(1,0,0,1);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 eglSwapBuffers(display, surface);
	}




};
