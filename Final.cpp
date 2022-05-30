/*---------------------------------------------------------*/
/* ----------------  Proyecto Laboratorio de Computación gráfica -----------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- Alumnos: Tenorio Ruiz Brayan Fernando y Martínez Pérez Dylan    ---------------*/
/*------------- No. Cuenta: 316205728 y 313152238  ---------------*/
#include <Windows.h>
#include <glad/glad.h>
#include <glfw3.h>	//main
//#include <AL/al.h>
//#include <Al/alc.h>
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
//#include <GL/glut.h>

//Propiedades de congfig general version conjunto de herramientas v142 y version de SDK
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
//#include <audio_file.h>
//#include <audio_format.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>




//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 70.0f, 2000.0f));
float MovementSpeed = 1200.0f; //VELOCIDAD DE LA CAMARA
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting

glm::vec3 lightPosition2(1020.0f, 4.0f, -750.0f);
glm::vec3 lightPosition3(-50.0f, 4.0f, -1300.0f);
glm::vec3 lightPosition4(-1000.0f, 4.0f, -100.0f);

glm::vec3 lightSpotlight1(0.0f, 4.0f, 400.0f);
glm::vec3 lightSpotlight2(0.0f, 4.0f, 400.0f);

glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;

float
B = 0,

animAlas = 0.0f,
alasPtero = 0.0f,

movPtero1_x = -100.0f,
movPtero1_z = 0.0f,
orientaPtero1 = 0.0f,

movPtero2_x = 0.0f,
movPtero2_z = 100.0f,
orientaPtero2 = 0.0f,

movPtero3_x = 100.0f,
movPtero3_z = 0.0f,
orientaPtero3 = 0.0f,

movPtero4_x = 0.0f,
movPtero4_z = -100.0f,
orientaPtero4 = 0.0f,

movGEsfera_x = -65.0f,
movGEsfera_z = 700.0f,
orientaGEsfera = 180.0f,
GEsferaStop = 0.0f,

movDrone1_x = 1000.0f,
movDrone1_z = -400.0f,
orientaDrone1 = 0.0f,

movDrone2_x = -700.0f,
movDrone2_z = 250.0f,
orientaDrone2 = 180.0f,

movHuevoX = 0.0f,
movHuevoY =0.0f,

animaTREX = 0.0f ;


bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false,
recorrido6 = false,
animacion2 = false,

animaHuevo = true,
animaHuevo1 = true,
animaHuevo2 = false,

animaPtero = true,

Ptero1Reco1 = true,
Ptero1Reco2 = false,
Ptero1Reco3 = false,
Ptero1Reco4 = false,
Ptero1Reco5 = false,
Ptero1Reco6 = false,

Ptero2Reco1 = false,
Ptero2Reco2 = true,
Ptero2Reco3 = false,
Ptero2Reco4 = false,
Ptero2Reco5 = false,
Ptero2Reco6 = false,

Ptero3Reco1 = false,
Ptero3Reco2 = false,
Ptero3Reco3 = true,
Ptero3Reco4 = false,
Ptero3Reco5 = false,
Ptero3Reco6 = false,

Ptero4Reco1 = false,
Ptero4Reco2 = false,
Ptero4Reco3 = false,
Ptero4Reco4 = true,
Ptero4Reco5 = false,
Ptero4Reco6 = false,

animaGEsfera = true,

GEsferaReco1 = true,
GEsferaReco2 = false,
GEsferaReco3 = false,
GEsferaReco4 = false,
GEsferaReco5 = false,
GEsferaReco6 = false,
GEsferaReco7 = false,
GEsferaReco8 = false,

animaDrone = true,

Drone2Reco1 = true,
Drone2Reco2 = false,
Drone2Reco3 = false,
Drone2Reco4 = false,
Drone2Reco5 = false,
Drone2Reco6 = false,
Drone2Reco7 = false,
Drone2Reco8 = false,

Drone1Reco1 = false,
Drone1Reco2 = false,
Drone1Reco3 = false,
Drone1Reco4 = false,
Drone1Reco5 = true,
Drone1Reco6 = false,
Drone1Reco7 = false,
Drone1Reco8 = false,

EdnaCam = false;

float	miVariable = 0.0f,
noche = 0.0f,
contNoche = 0.0f,
sol = 0.05f,
cY = 0,
cX = 0,
cZ = 0,
cY2 = 0,
cX2 = 0,
cZ2 = 0,
luzX = 0,
luzY = 0,
luzZ = 0,
vigilanciaX = 0.0f,
vigilanciaY = 0,
vigilanciaZ = 0.0f;

float rotTRex_y = 0.0f,
	  rotTRex_x = 0.0f;

float	movEdnaModa_X = -700.0f,
		movEdnaModa_Z = 650.0f;

float scale = 10.0f;

/*
ALuint buffers[1];
ALuint sources[2];

void loadAudio() {

	ALenum alError;
	ALCenum alcError;

	ALCdevice* openALDevice = alcOpenDevice(NULL);
	if (!openALDevice) return;

	ALCcontext* openALContext;
	openALContext = alcCreateContext(openALDevice, NULL);
	alcMakeContextCurrent(openALContext);
	alcError = alcGetError(openALDevice);
	if (alcError != ALC_NO_ERROR) {
		std::cerr << ("alContext :", alcError) << std::endl;
		return;
	}

	alGenBuffers(1, buffers);

	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alGenBuffers :", alError) << std::endl;
		return;
	}

	AudioFile JP_Theme;
	char* JP_Theme_buffer = JP_Theme.load("resources/audio/JurassicPark_Theme.wav");
	ALenum JP_Theme_format = get_audio_format(JP_Theme.channels, JP_Theme.bitsPerSample);
	alBufferData(buffers[0], JP_Theme_format, JP_Theme_buffer, JP_Theme.size, JP_Theme.sampleRate);

	AudioFile Rugido_Rex;
	char* Rugido_Rex_buffer = Rugido_Rex.load("resources/audio/Rugido_Rex.wav");
	ALenum Rugido_Rex_format = get_audio_format(Rugido_Rex.channels, Rugido_Rex.bitsPerSample);
	alBufferData(buffers[0], Rugido_Rex_format, Rugido_Rex_buffer, Rugido_Rex.size, Rugido_Rex.sampleRate);

	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alDistanceModel :", alError) << std::endl;
		return;
	}

	alGenSources(2, sources);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alGenSources :", alError) << std::endl;
		return;
	}

	// Audio Tematico
	alSourcef(sources[0], AL_PITCH, 1);
	alSourcef(sources[0], AL_GAIN, 5.0f);
	alSource3f(sources[0], AL_POSITION, camera.Position.x, camera.Position.y, camera.Position.z);
	alSource3f(sources[0], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}

	// Audio T-Rex
	alSourcef(sources[1], AL_PITCH, 1);
	alSourcef(sources[1], AL_GAIN, 4.5f);
	alSource3f(sources[1], AL_POSITION, -50.0f, 5.0f, -1100.0f);
	alSourcef(sources[1], AL_REFERENCE_DISTANCE, 200.0f * scale);
	alSourcef(sources[1], AL_ROLLOFF_FACTOR, 70.0f);
	alSource3f(sources[1], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_BUFFER, buffers[0]);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}

	alListener3f(AL_POSITION, camera.Position.x, camera.Position.y, camera.Position.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerf(AL_GAIN, 0.99f);

}
*/
void animate(void) //Ciclo de animado
{
	//Animacion Drones
	if (animaDrone) {

		if (Drone1Reco1) {
			movDrone1_x = -700.0f;
			movDrone1_z -= 3.0f;
			orientaDrone1 = 180.0f;
			lightSpotlight1.x = -700.0f;
			lightSpotlight1.z -= 3.0f;
			if (movDrone1_z <= -400.0f) {
				Drone1Reco1 = false;
				Drone1Reco2 = true;
			}
		}
		if (Drone1Reco2) {
			movDrone1_x += (1.5f * 2.0f);
			movDrone1_z -= (1.0f * 2.0f);
			orientaDrone1 = 124.0f;
			lightSpotlight1.x += (1.5f * 2.0f);
			lightSpotlight1.z -= (1.0f * 2.0f);
			if (movDrone1_z <= -600.0f) {
				Drone1Reco2 = false;
				Drone1Reco3 = true;
			}
		}
		if (Drone1Reco3) {
			movDrone1_x += 3.0f;
			movDrone1_z = -600.0f;
			orientaDrone1 = 90.0f;
			lightSpotlight1.x += 3.0f;
			lightSpotlight1.z = -600.0f;
			if (movDrone1_x >= 600.0f) {
				Drone1Reco3 = false;
				Drone1Reco4 = true;
			}
		}
		if (Drone1Reco4) {
			movDrone1_x += (2.0f * 2.0f);
			movDrone1_z += (1.0f * 2.0f);
			orientaDrone1 = 45.0f;
			lightSpotlight1.x += (2.0f * 2.0f);
			lightSpotlight1.z += (1.0f * 2.0f);
			if (movDrone1_x >= 1000.0f) {
				Drone1Reco4 = false;
				Drone1Reco5 = true;
			}
		}
		if (Drone1Reco5) {
			movDrone1_x = 1000.0f;
			movDrone1_z += 3.0f;
			orientaDrone1 = 0.0f;
			lightSpotlight1.x = 1000.0f;
			lightSpotlight1.z += 3.0f;
			if (movDrone1_z >= 250.0f) {
				Drone1Reco5 = false;
				Drone1Reco6 = true;
			}
		}
		if (Drone1Reco6) {
			movDrone1_x -= (1.14f * 2.0f);
			movDrone1_z += (1.0f * 2.0f);
			orientaDrone1 = 312.0f;
			lightSpotlight1.x -= (1.14f * 2.0f);
			lightSpotlight1.z += (1.0f * 2.0f);
			if (movDrone2_x <= 600.0f) {
				Drone1Reco6 = false;
				Drone1Reco7 = true;
			}
		}
		if (Drone1Reco7) {
			movDrone1_x -= 3.0f;
			movDrone1_z = 600.0f;
			orientaDrone1 = -90.0f;
			lightSpotlight1.x -= 3.0f;
			lightSpotlight1.z = 600.0f;
			if (movDrone1_x <= -400.0f) {
				Drone1Reco7 = false;
				Drone1Reco8 = true;
			}
		}
		if (Drone1Reco8) {
			movDrone1_x -= (0.85f * 2.0f);
			movDrone1_z -= (1.0f * 2.0f);
			orientaDrone1 = 220.0f;
			lightSpotlight1.x -= (0.85f * 2.0f);
			lightSpotlight1.z -= (1.0f * 2.0f);
			if (movDrone1_x <= -700.0f) {
				Drone1Reco8 = false;
				Drone1Reco1 = true;
			}
		}

	// Drone 2

		if (Drone2Reco1) {
			movDrone2_x = -700.0f;
			movDrone2_z -= 3.0f;
			orientaDrone2 = 180.0f;
			lightSpotlight2.x = -700.0f;
			lightSpotlight2.z -= 3.0f;
			if (movDrone2_z <= -400.0f) {
				Drone2Reco1 = false;
				Drone2Reco2 = true;
			}
		}
		if (Drone2Reco2) {
			movDrone2_x += (1.5f * 2.0f);
			movDrone2_z -= (1.0f * 2.0f);
			orientaDrone2 = 124.0f;
			lightSpotlight2.x += (1.5f * 2.0f);
			lightSpotlight2.z -= (1.0f * 2.0f);
			if (movDrone2_z <= -600.0f) {
				Drone2Reco2 = false;
				Drone2Reco3 = true;
			}
		}
		if (Drone2Reco3) {
			movDrone2_x += 3.0f;
			movDrone2_z = -600.0f;
			orientaDrone2 = 90.0f;
			lightSpotlight2.x += 3.0f;
			lightSpotlight2.z = -600.0f;
			if (movDrone2_x >= 600.0f) {
				Drone2Reco3 = false;
				Drone2Reco4 = true;
			}
		}
		if (Drone2Reco4) {
			movDrone2_x += (2.0f * 2.0f);
			movDrone2_z += (1.0f * 2.0f);
			orientaDrone2 = 45.0f;
			lightSpotlight2.x += (2.0f * 2.0f);
			lightSpotlight2.z += (1.0f * 2.0f);
			if (movDrone2_x >= 1000.0f) {
				Drone2Reco4 = false;
				Drone2Reco5 = true;
			}
		}
		if (Drone2Reco5) {
			movDrone2_x = 1000.0f;
			movDrone2_z += 3.0f;
			orientaDrone2 = 0.0f;
			lightSpotlight2.x = 1000.0f;
			lightSpotlight2.z += 3.0f;
			if (movDrone2_z >= 250.0f) {
				Drone2Reco5 = false;
				Drone2Reco6 = true;
			}
		}
		if (Drone2Reco6) {
			movDrone2_x -= (1.14f * 2.0f);
			movDrone2_z += (1.0f * 2.0f);
			orientaDrone2 = 312.0f;
			lightSpotlight2.x -= (1.14f * 2.0f);
			lightSpotlight2.z += (1.0f * 2.0f);
			if (movDrone2_x <= 600.0f) {
				Drone2Reco6 = false;
				Drone2Reco7 = true;
			}
		}
		if (Drone2Reco7) {
			movDrone2_x -= 3.0f;
			movDrone2_z = 600.0f;
			orientaDrone2 = -90.0f;
			lightSpotlight2.x -= 3.0f;
			lightSpotlight2.z = 600.0f;
			if (movDrone2_x <= -400.0f) {
				Drone2Reco7 = false;
				Drone2Reco8 = true;
			}
		}
		if (Drone2Reco8) {
			movDrone2_x -= (0.85f * 2.0f);
			movDrone2_z -= (1.0f * 2.0f);
			orientaDrone2 = 220.0f;
			lightSpotlight2.x -= (0.85f * 2.0f);
			lightSpotlight2.z -= (1.0f * 2.0f);
			if (movDrone2_x <= -700.0f) {
				Drone2Reco8 = false;
				Drone2Reco1 = true;
			}
		}
	}

	//Animacion T-REX
	if (animaTREX == 0) {
		rotTRex_y += 0.05;
		rotTRex_x += 0.04;
		if (rotTRex_y >= 8.0f) {
			animaTREX = 1;
		}
	}
	else {
		rotTRex_y -= 0.05;
		rotTRex_x -= 0.04;
		if (rotTRex_y <= -8.0f) {
			animaTREX = 0;
		}
	}


	//ANIMACION DIA_NOCHE Y LUZ
	if (noche == 0.0f)
	{
		if (sol >= 0.8f)
		{
			sol = 0.8f;
			contNoche = 0.0f;
			noche = 1.0f;
			cX = 1;
			cY = rand() % 2;
			cZ = rand() % 2;

			cX2 = rand() % 2;
			cY2 = 0.1;
			cZ2 = rand() % 2;

		}
		else {

			luzX = 0;
			luzY = 0;
			luzZ = 0;

			vigilanciaX = 0,
			vigilanciaY = 0,
			vigilanciaZ = 0;

			sol += 0.002f;
		}
	}
	else
	{
		if (sol <= 0.2f) {
			sol = 0.2f;
			if (contNoche <= 1.0f) {

				contNoche += 0.001f;

				vigilanciaX = cX;
				vigilanciaY = cY;
				vigilanciaZ = cZ;

				luzX = 0;
				luzY = 1;
				luzZ = 0;
			}
			else {
				contNoche = 0.0f;
				noche = 0.0f;
			}
		}
		else {
			sol -= 0.001f;
		}
	}


	//ANIMA-PTERODACTILO
	if (animaPtero) {

		//AnimacionAlasPtero
		if (animAlas == 0) {
			alasPtero += 1.0f;
			if (alasPtero >= 25) {
				animAlas = 1;
			}
		}
		else {
			alasPtero -= 1.0f;
			if (alasPtero <= -25) {
				animAlas = 0;
			}
		}
			//PTERODACTILO 1
			if (Ptero1Reco1) {
				movPtero1_x += (0.25f * 1.3f);
				movPtero1_z += (1.0f * 1.3f);
				orientaPtero1 = 14.03f;
				if (movPtero1_z >= 100.0f) {
					Ptero1Reco1 = false;
					Ptero1Reco2 = true;
				}
			}

			if (Ptero1Reco2) {
				movPtero1_x += 1.0f;
				movPtero1_z = 100.0f;
				orientaPtero1 = 90.0f;
				if (movPtero1_x >= 75.0f) {
					Ptero1Reco2 = false;
					Ptero1Reco3 = true;
				}
			}

			if (Ptero1Reco3) {
				movPtero1_x += (0.25f * 1.3f);
				movPtero1_z -= (1.0f * 1.3f);
				orientaPtero1 = 165.97f;
				if (movPtero1_z <= 0.0f) {
					Ptero1Reco3 = false;
					Ptero1Reco4 = true;
				}
			}

			if (Ptero1Reco4) {
				movPtero1_x -= (0.25f * 1.3f);
				movPtero1_z -= (1.0f * 1.3f);
				orientaPtero1 = 194.03f;
				if (movPtero1_x <= 75.0f) {
					Ptero1Reco4 = false;
					Ptero1Reco5 = true;
				}
			}

			if (Ptero1Reco5) {
				movPtero1_x -= 1.0f;
				movPtero1_z = -100.0f;
				orientaPtero1 = 270.0f;
				if (movPtero1_x <= -75.0f) {
					Ptero1Reco5 = false;
					Ptero1Reco6 = true;
				}
			}

			if (Ptero1Reco6) {
				movPtero1_x -= (0.25f * 1.3f);
				movPtero1_z += (1.0f * 1.3f);
				orientaPtero1 = 345.97f;
				if (movPtero1_x <= -100.0f) {
					Ptero1Reco6 = false;
					Ptero1Reco1 = true;
				}
			}
			//---------------------------------------------------------
					//PTERODACTILO 2
			if (Ptero2Reco1) {
				movPtero2_x += (0.25f * 1.3f);
				movPtero2_z += (1.0f * 1.3f);
				orientaPtero2 = 14.03f;
				if (movPtero2_z >= 100.0f) {
					Ptero2Reco1 = false;
					Ptero2Reco2 = true;
				}
			}

			if (Ptero2Reco2) {
				movPtero2_x += 1.0f;
				movPtero2_z = 100.0f;
				orientaPtero2 = 90.0f;
				if (movPtero2_x >= 75.0f) {
					Ptero2Reco2 = false;
					Ptero2Reco3 = true;
				}
			}

			if (Ptero2Reco3) {
				movPtero2_x += (0.25f * 1.3f);
				movPtero2_z -= (1.0f * 1.3f);
				orientaPtero2 = 165.97f;
				if (movPtero2_z <= 0.0f) {
					Ptero2Reco3 = false;
					Ptero2Reco4 = true;
				}
			}

			if (Ptero2Reco4) {
				movPtero2_x -= (0.25f * 1.3f);
				movPtero2_z -= (1.0f * 1.3f);
				orientaPtero2 = 194.03f;
				if (movPtero2_x <= 75.0f) {
					Ptero2Reco4 = false;
					Ptero2Reco5 = true;
				}
			}

			if (Ptero2Reco5) {
				movPtero2_x -= 1.0f;
				movPtero2_z = -100.0f;
				orientaPtero2 = 270.0f;
				if (movPtero2_x <= -75.0f) {
					Ptero2Reco5 = false;
					Ptero2Reco6 = true;
				}
			}

			if (Ptero2Reco6) {
				movPtero2_x -= (0.25f * 1.3f);
				movPtero2_z += (1.0f * 1.3f);
				orientaPtero2 = 345.97f;
				if (movPtero2_x <= -100.0f) {
					Ptero2Reco6 = false;
					Ptero2Reco1 = true;
				}
			}

			//---------------------------------------------------------
				//PTERODACTILO 3

			if (Ptero3Reco1) {
				movPtero3_x += (0.25f * 1.3f);
				movPtero3_z += (1.0f * 1.3f);
				orientaPtero3 = 14.03f;
				if (movPtero3_z >= 100.0f) {
					Ptero3Reco1 = false;
					Ptero3Reco2 = true;
				}
			}

			if (Ptero3Reco2) {
				movPtero3_x += 1.0f;
				movPtero3_z = 100.0f;
				orientaPtero3 = 90.0f;
				if (movPtero3_x >= 75.0f) {
					Ptero3Reco2 = false;
					Ptero3Reco3 = true;
				}
			}

			if (Ptero3Reco3) {
				movPtero3_x += (0.25f * 1.3f);
				movPtero3_z -= (1.0f * 1.3f);
				orientaPtero3 = 165.97f;
				if (movPtero3_z <= 0.0f) {
					Ptero3Reco3 = false;
					Ptero3Reco4 = true;
				}
			}

			if (Ptero3Reco4) {
				movPtero3_x -= (0.25f * 1.3f);
				movPtero3_z -= (1.0f * 1.3f);
				orientaPtero3 = 194.03f;
				if (movPtero3_x <= 75.0f) {
					Ptero3Reco4 = false;
					Ptero3Reco5 = true;
				}
			}

			if (Ptero3Reco5) {
				movPtero3_x -= 1.0f;
				movPtero3_z = -100.0f;
				orientaPtero3 = 270.0f;
				if (movPtero3_x <= -75.0f) {
					Ptero3Reco5 = false;
					Ptero3Reco6 = true;
				}
			}

			if (Ptero3Reco6) {
				movPtero3_x -= (0.25f * 1.3f);
				movPtero3_z += (1.0f * 1.3f);
				orientaPtero3 = 345.97f;
				if (movPtero3_x <= -100.0f) {
					Ptero3Reco6 = false;
					Ptero3Reco1 = true;
				}
			}

			//---------------------------------------------------------
				//PTERODACTILO 4

			if (Ptero4Reco1) {
				movPtero4_x += (0.25f * 1.3f);
				movPtero4_z += (1.0f * 1.3f);
				orientaPtero4 = 14.03f;
				if (movPtero4_z >= 100.0f) {
					Ptero4Reco1 = false;
					Ptero4Reco2 = true;
				}
			}

			if (Ptero4Reco2) {
				movPtero4_x += 1.0f;
				movPtero4_z = 100.0f;
				orientaPtero4 = 90.0f;
				if (movPtero4_x >= 75.0f) {
					Ptero4Reco2 = false;
					Ptero4Reco3 = true;
				}
			}

			if (Ptero4Reco3) {
				movPtero4_x += (0.25f * 1.3f);
				movPtero4_z -= (1.0f * 1.3f);
				orientaPtero4 = 165.97f;
				if (movPtero4_z <= 0.0f) {
					Ptero4Reco3 = false;
					Ptero4Reco4 = true;
				}
			}

			if (Ptero4Reco4) {
				movPtero4_x -= (0.25f * 1.3f);
				movPtero4_z -= (1.0f * 1.3f);
				orientaPtero4 = 194.03f;
				if (movPtero4_x <= 75.0f) {
					Ptero4Reco4 = false;
					Ptero4Reco5 = true;
				}
			}

			if (Ptero4Reco5) {
				movPtero4_x -= 1.0f;
				movPtero4_z = -100.0f;
				orientaPtero4 = 270.0f;
				if (movPtero4_x <= -75.0f) {
					Ptero4Reco5 = false;
					Ptero4Reco6 = true;
				}
			}

			if (Ptero4Reco6) {
				movPtero4_x -= (0.25f * 1.3f);
				movPtero4_z += (1.0f * 1.3f);
				orientaPtero4 = 345.97f;
				if (movPtero4_x <= -100.0f) {
					Ptero4Reco6 = false;
					Ptero4Reco1 = true;
				}
			}
		}

		//ANIMACION HUEVO

		if (animaHuevo) {
			B = 1;
			if (B >= 0.5) {
				movHuevoX += 0.5;
			}
		}

		//Animacion girosfera
		if (animaGEsfera) {

			if (GEsferaReco1) {
				movGEsfera_x = -55.0f;
				movGEsfera_z -= 3.0f;
				orientaGEsfera = 180.0f;
				if (movGEsfera_z <= -350.0f) {

					movGEsfera_x = -55.0f;
					movGEsfera_z = -350.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco1 = false;
						GEsferaReco2 = true;
					}
				}
			}

			if (GEsferaReco2) {
				movGEsfera_x += (0.78f * 2.0f);
				movGEsfera_z -= (1.0f * 2.0f);
				orientaGEsfera = 180.0f;
				if (movGEsfera_x >= 180.0f) {

					movGEsfera_x = 180.0f;
					movGEsfera_z = -650.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco2 = false;
						GEsferaReco3 = true;
					}

				}
			}

			if (GEsferaReco3) {
				movGEsfera_x = 180.0f;
				movGEsfera_z -= 3;
				orientaGEsfera = 180.0f;
				if (movGEsfera_z <= -800.0f) {

					movGEsfera_x = 180.0f;
					movGEsfera_z = -800.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco3 = false;
						GEsferaReco4 = true;
					}
				}
			}

			if (GEsferaReco4) {
				movGEsfera_x -= (0.76f * 2.0f);
				movGEsfera_z -= (1.0f * 2.0f);
				orientaGEsfera = 180.0f;
				if (movGEsfera_x <= -50.0f) {

					movGEsfera_x = -50.0f;
					movGEsfera_z = -1100.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco4 = false;
						GEsferaReco5 = true;
					}
				}
			}

			if (GEsferaReco5) {
				movGEsfera_x -= (1.075f * 2.0f);
				movGEsfera_z += (1.0f * 2.0f);
				orientaGEsfera = 180.0f;
				if (movGEsfera_z >= -900.0f) {

					movGEsfera_x = -270.0f;
					movGEsfera_z = -900.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco5 = false;
						GEsferaReco6 = true;
					}
				}
			}

			if (GEsferaReco6) {
				movGEsfera_x = -270.0f;
				movGEsfera_z += 3;
				orientaGEsfera = 180.0f;
				if (movGEsfera_z >= -750.0f) {

					movGEsfera_x = -270.0f;
					movGEsfera_z = -750.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco6 = false;
						GEsferaReco7 = true;
					}
				}
			}

			if (GEsferaReco7) {
				movGEsfera_x = -270.0f;
				movGEsfera_z += 3;
				orientaGEsfera = 180.0f;
				if (movGEsfera_z >= -650.0f) {

					movGEsfera_x = -270.0f;
					movGEsfera_z = -650.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco7 = false;
						GEsferaReco8 = true;
					}
				}
			}

			if (GEsferaReco8) {
				movGEsfera_x += (0.71f * 2.0f);
				movGEsfera_z += (1.0f * 2.0f);;
				orientaGEsfera = 180.0f;
				if (movGEsfera_z >= -350.0f) {

					movGEsfera_x = -55.0f;
					movGEsfera_z = -350.0f;
					GEsferaStop += 0.07f;

					if (GEsferaStop >= 2.0f) {
						GEsferaStop = 0.0f;
						GEsferaReco8 = false;
						GEsferaReco2 = true;
					}
				}
			}
		}
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Parque_Jurasico", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

//	loadAudio();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right03.jpg",
		"resources/skybox/left03.jpg",
		"resources/skybox/top03.jpg",
		"resources/skybox/bottom03.jpg",
		"resources/skybox/front03.jpg",
		"resources/skybox/back03.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	//Casa de brujas
	
	Model helecho("resources/objects/helecho/hel.obj");
	Model fPlant("resources/objects/frgplant/frgp.obj");

	Model cabezarex("resources/objects/cabeza/cabezatrex2.obj");
	Model REX_ojoIzq("resources/objects/cabeza/ojoIzq.obj");
	Model REX_ojoDer("resources/objects/cabeza/ojoDer.obj");
	Model REX_lengua("resources/objects/cabeza/Lengua.obj");

	Model escultrex("resources/objects/esc/escult.obj");
	Model huevo1("resources/objects/huevo1/egg.obj");
	Model huevo2("resources/objects/huevo2/egg2.obj");
	Model huevo3("resources/objects/huevo3/egg3.obj");
	Model banc("resources/objects/banca/objBench.obj");
	Model man("resources/objects/manrex/mandibula.obj");
	Model piso("resources/objects/piso2/piso.obj");
	Model camino("resources/objects/camino/rwk.obj");
	Model puerta("resources/objects/puerta/puerta1.obj");
	Model restroom("resources/objects/restroom/rest.obj");

	Model riel1("resources/objects/riel1/r1.obj");
	Model riel2("resources/objects/riel2/r2.obj");
	Model plataforma("resources/objects/plataform/plat.obj");
	Model mesas("resources/objects/table/pictable.obj");
	Model restaurant("resources/objects/restaurant/Coffee_Shop.obj");
	Model tienda("resources/objects/store/str.obj");
	Model tubo("resources/objects/tubo/tb.obj");
	Model cria1("resources/objects/criadero1/cr1.obj");
	Model cria2("resources/objects/criadero2/cr2.obj");
	Model laboratorio("resources/objects/lab/lab1.obj");
	Model invernadero("resources/objects/greenhouse/gh1.obj");
	Model plant1("resources/objects/plant1/pl1.obj");
	Model plant2("resources/objects/plants2/pl2.obj");
	Model plant3("resources/objects/plants3/pl3.obj");


	Model Dron("resources/objects/Drone/Drone3.obj");
	
	Model Cupula("resources/objects/Cupula/Cupula4.obj");

	Model EdnaCabeza("resources/objects/Edna_Moda/CabezaEdna.obj");
	Model EdnaCuerpo("resources/objects/Edna_Moda/CuerpoEdna.obj");
	Model EdnaBrazIzq("resources/objects/Edna_Moda/BrazoIzq.obj");
	Model EdnaBrazDer("resources/objects/Edna_Moda/BrazoDer.obj");
	Model EdnaPierIzq("resources/objects/Edna_Moda/PiernaIzq.obj");
	Model EdnaPierDer("resources/objects/Edna_Moda/PiernaDer.obj");


	Model Ptero("resources/objects/Dino2/CuerpoPtero.obj");
	Model AlaIzq("resources/objects/Dino2/AlaIzq.obj");
	Model AlaDer("resources/objects/Dino2/AlaDer.obj");

	Model Dino3("resources/objects/Dino3/Dino3.obj");



	Model GiroEsfera("resources/objects/GiroEsfera/GiroEsfera.obj");
	//FIN MODELOS B

	//MODEL MIXAMO 
	ModelAnim persona1("resources/objects/persona1/Talking.dae");
	persona1.initShaders(animShader.ID); //añadir el objeto al shader de animacion

	ModelAnim persona2("resources/objects/person2/Talking.dae");
	persona2.initShaders(animShader.ID); //añadir el objeto al shader de animacion



	/*ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	ninja.initShaders(animShader.ID);*/

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//	alSourcePlay(sources[0]);
//	alSourcePlay(sources[1]);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(sol, sol, sol));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightSpotlight1);
		staticShader.setVec3("pointLight[0].direction", lightSpotlight1);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(vigilanciaX, vigilanciaY, vigilanciaZ));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(vigilanciaX, vigilanciaY, vigilanciaZ));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.0000008f);
		staticShader.setFloat("pointLight[0].linear", 0.0000009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00032f);
		staticShader.setFloat("pointLight[0].cutOff", glm::cos(glm::radians(15.0f)));

		staticShader.setVec3("pointLight[1].position", lightSpotlight2);
		staticShader.setVec3("pointLight[1].direction", lightSpotlight2);
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(vigilanciaX, vigilanciaY, vigilanciaZ));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(vigilanciaX, vigilanciaY, vigilanciaZ));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 0.0000008f);
		staticShader.setFloat("pointLight[1].linear", 0.0000009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.00032f);
		staticShader.setFloat("pointLight[1].cutOff", glm::cos(glm::radians(15.0f)));

		staticShader.setVec3("pointLight[2].position", lightPosition2);//
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 0.008f);
		staticShader.setFloat("pointLight[2].linear", 0.009f);
		staticShader.setFloat("pointLight[2].quadratic", 0.0000022f);

		staticShader.setVec3("pointLight[3].position", lightPosition3);//
		staticShader.setVec3("pointLight[3].ambient", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[3].diffuse", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[3].constant", 0.008f);
		staticShader.setFloat("pointLight[3].linear", 0.009f);
		staticShader.setFloat("pointLight[3].quadratic", 0.0000022f);

		staticShader.setVec3("pointLight[4].position", lightPosition4);//
		staticShader.setVec3("pointLight[4].ambient", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[4].diffuse", glm::vec3(luzX, luzY, luzZ));
		staticShader.setVec3("pointLight[4].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[4].constant", 0.008f);
		staticShader.setFloat("pointLight[4].linear", 0.009f);
		staticShader.setFloat("pointLight[4].quadratic", 0.0000022f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);

		//Persona1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(800.0f, 35.0f, 800.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		persona1.Draw(animShader);

		//Persona2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(820.0f, 35.0f, 850.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		persona2.Draw(animShader);


		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1150.0f, 0.0f, -790.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		helecho.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1180.0f, 0.0f, -800.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1300.0f, 0.0f, -300.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1300.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 0.0f, -1000.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -1000.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1080.0f, 0.0f, -500.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1100.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);


		//DRON 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movDrone1_x, 500.0f, movDrone1_z));
		model = glm::rotate(model, glm::radians(orientaDrone1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		Dron.Draw(staticShader);

		//DRON 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movDrone2_x, 500.0f, movDrone2_z));
		model = glm::rotate(model, glm::radians(orientaDrone2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		Dron.Draw(staticShader);

		//Cabeza REX
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, -1200.0f));
		model = glm::rotate(model, glm::radians(rotTRex_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cabezarex.Draw(staticShader);
		 
		// ojo izq
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -20.0f, -1200.0f));
		model = glm::rotate(model, glm::radians(rotTRex_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		REX_ojoIzq.Draw(staticShader);

		// ojo der
		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -20.0f, -1200.0f));
		model = glm::rotate(model, glm::radians(rotTRex_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		REX_ojoDer.Draw(staticShader);
		
		// lengua
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, -1200.0f));
		model = glm::rotate(model, glm::radians(rotTRex_y), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(-rotTRex_x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		REX_lengua.Draw(staticShader);
//---------------------
// 
		//Escultura
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, -150.0f, 200.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		escultrex.Draw(staticShader);

		//tubo
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1180.0f, 0.0f, -890.0f));
		model = glm::scale(model, glm::vec3(0.150f));
		staticShader.setMat4("model", model);
		tubo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1220.0f, 0.0f, -890.0f));
		model = glm::scale(model, glm::vec3(0.150f));
		staticShader.setMat4("model", model);
		tubo.Draw(staticShader);

		//huevo1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1150.0f, 10.0f, -790.0f));
		tmp = model = glm::rotate(model, glm::radians(movHuevoX), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

		//huevo2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1070.0f, 25.0f, -850.0f));
		model = glm::scale(model, glm::vec3(28.0f));
		staticShader.setMat4("model", model);
		huevo2.Draw(staticShader);

		//huevo3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1090.0f, 30.0f, -890.0f));
		model = glm::scale(model, glm::vec3(35.0f));
		staticShader.setMat4("model", model);
		huevo3.Draw(staticShader);

		//huevo4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1020.0f, 25.0f, -750.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

		//huevo5
		model = glm::translate(glm::mat4(1.0f), glm::vec3(900.0f, 25.0f, -750.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

		//huevo6
		model = glm::translate(glm::mat4(1.0f), glm::vec3(840.0f, 35.0f, -890.0f));
		model = glm::scale(model, glm::vec3(45.0f));
		staticShader.setMat4("model", model);
		huevo3.Draw(staticShader);

		//huevo7
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1000.0f, 35.0f, -700.0f));
		model = glm::scale(model, glm::vec3(60.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

		//plantas

		model = glm::translate(glm::mat4(1.0f), glm::vec3(960.0f, -40.0f, -500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		staticShader.setMat4("model", model);
		plant2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, -40.0f, -930.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		staticShader.setMat4("model", model);
		plant3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(920.0f, -80.0f, -935.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f));
		staticShader.setMat4("model", model);
		plant3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(850.0f, 0.0f, -1005.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		helecho.Draw(staticShader);


		//banca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(600.0f, 35.0f, 800.0f));
		model = glm::rotate(model, glm::radians(-225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);


		//Camino
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, -300.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		camino.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		camino.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		camino.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, 150.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		camino.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		camino.Draw(staticShader);


		//rieles
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 800.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 700.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 900.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1000.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1100.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 600.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel comida
		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel tienda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel criadero
		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, -400.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel lab
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, -450.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel invernadero
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-550.0f, 0.0f, -120.0f));
		model = glm::rotate(model, glm::radians(-270.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);

		//riel rex
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -650.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		riel1.Draw(staticShader);


		//puerta
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1600.0f));
		model = glm::scale(model, glm::vec3(0.93f));
		staticShader.setMat4("model", model);
		puerta.Draw(staticShader);

		//baño
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 35.0f, 820.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		restroom.Draw(staticShader);

		//plataforma
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 0.0f, 900.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		plataforma.Draw(staticShader);

		//Restaurante
		model = glm::translate(glm::mat4(1.0f), glm::vec3(900.0f, 35.0f, 1050.0f));
		model = glm::rotate(model, glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		restaurant.Draw(staticShader);

		//Mesas
		model = glm::translate(glm::mat4(1.0f), glm::vec3(870.0f, 35.0f, 620.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f));
		staticShader.setMat4("model", model);
		mesas.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(870.0f, 35.0f, 780.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f));
		staticShader.setMat4("model", model);
		mesas.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(700.0f, 35.0f, 700.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f));
		staticShader.setMat4("model", model);
		mesas.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1050.0f, 35.0f, 700.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f));
		staticShader.setMat4("model", model);
		mesas.Draw(staticShader);

		//tienda

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-900.0f, 0.0f, 700.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.3f));
		staticShader.setMat4("model", model);
		tienda.Draw(staticShader);

		//criadero
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1150.0f, 0.0f, -880.0f));
		model = glm::scale(model, glm::vec3(25.0f));
		staticShader.setMat4("model", model);
		cria1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(990.0f, 0.0f, -1050.0f));
		model = glm::scale(model, glm::vec3(25.0f));
		staticShader.setMat4("model", model);
		cria2.Draw(staticShader);

		//laboratorio

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-800.0f, 0.0f, -900.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.3f));
		staticShader.setMat4("model", model);
		laboratorio.Draw(staticShader);


		//invernadero
	
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1000.0f, -100.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		plant1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1000.0f, -100.0f, -200.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		plant1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-980.0f, -60.0f, 200.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		staticShader.setMat4("model", model);
		plant2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-860.0f, -60.0f, -200.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		staticShader.setMat4("model", model);
		plant2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, -40.0f, -30.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
		staticShader.setMat4("model", model);
		plant3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, -40.0f, 35.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f));
		staticShader.setMat4("model", model);
		plant3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1150.0f, 0.0f, -205.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		helecho.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1150.0f, 0.0f, 205.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		helecho.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(movGEsfera_x, 12.0f, movGEsfera_z));
		tmp = model = glm::rotate(model, glm::radians(orientaGEsfera), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f));
		staticShader.setMat4("model", model);
		GiroEsfera.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(400.0f));
		staticShader.setMat4("model", model);
		Cupula.Draw(staticShader);

	//PTERO 1

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero1_x, 300.0f, movPtero1_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		Ptero.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero1_x, 300.0f, movPtero1_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero1), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(-alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaIzq.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero1_x, 300.0f, movPtero1_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero1), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaDer.Draw(staticShader);

	//PTERO 2

		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero2_x, 300.0f, movPtero2_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		Ptero.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero2_x, 300.0f, movPtero2_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero2), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(-alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaIzq.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero2_x, 300.0f, movPtero2_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero2), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaDer.Draw(staticShader);

	//PTERO 3

		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero3_x, 300.0f, movPtero3_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero3), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1));
		staticShader.setMat4("model", model);
		Ptero.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero3_x, 300.0f, movPtero3_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero3), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(-alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaIzq.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero3_x, 300.0f, movPtero3_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero3), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaDer.Draw(staticShader);

	//PTERO 4

		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero4_x, 300.0f, movPtero4_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero4), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1));
		staticShader.setMat4("model", model);
		Ptero.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero4_x, 300.0f, movPtero4_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero4), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(-alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaIzq.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero4_x, 300.0f, movPtero4_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero4), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(alasPtero), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		AlaDer.Draw(staticShader);

		//-------------------------------------------------------------------
 
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, 2.0f, 170.0f));
		tmp = model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0));
		staticShader.setMat4("model", model);
		Dino3.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, 2.0f, -100.0f));
		tmp = model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0));
		staticShader.setMat4("model", model);
		Dino3.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, 2.0f, -350.0f));
		tmp = model = glm::rotate(model, glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0));
		staticShader.setMat4("model", model);
		Dino3.Draw(staticShader);

		//EdnaModa

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaCuerpo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaCabeza.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaBrazIzq.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaBrazDer.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaPierIzq.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movEdnaModa_X, 4.0f, movEdnaModa_Z));
		tmp = model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		EdnaPierDer.Draw(staticShader);

		//FIN MODELOS B


		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		/* AUDIO */

	//	alListener3f(AL_POSITION, camera.Position.x, camera.Position.y, camera.Position.z);

		// Audio Tematico
	//	alSource3f(sources[0], AL_POSITION, camera.Position.x, camera.Position.y, camera.Position.z);


		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();

/*	alDeleteSources(2, sources);
	alDeleteBuffers(2, buffers);
	ALCcontext* context = alcGetCurrentContext();
	ALCdevice* device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
*/

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
		if (EdnaCam) {
			movEdnaModa_Z -= 21.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);	
		if (EdnaCam) {
			movEdnaModa_Z += 21.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
		if (EdnaCam) {
			movEdnaModa_X -= 21.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
		if (EdnaCam) {
			movEdnaModa_X += 21.0f;
		}
	}

	//Edna Moda
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		EdnaCam = false;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		EdnaCam = true;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		movEdnaModa_Z -= 10.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		movEdnaModa_Z += 10.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		movEdnaModa_X -= 10.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		movEdnaModa_X += 10.0f;
	}


	/*To Configure Model
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;
	*/
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}