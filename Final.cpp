/*---------------------------------------------------------*/
/* ----------------  Práctica    10   -----------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- Alumno: Martínez Pérez Dylan    ---------------*/
/*------------- No. Cuenta 313152238   ---------------*/
#include <Windows.h>
#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

//Propiedades de congfig general version conjunto de herramientas v142 y version de SDK
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
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
Camera camera(glm::vec3(0.0f, 10.0f, 90.0f));
float MovementSpeed = 1500.0f; //VELOCIDAD DE LA CAMARA
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
//VARIABLES BRYAN
float

movPtero1_x = 0.0f,
movPtero1_z = 0.0f,
orientaPtero1 = 0.0f,

movPtero2_x = 0.0f,
movPtero2_z = 0.0f,
orientaPtero2 = 0.0f,

movPtero3_x = 0.0f,
movPtero3_z = 0.0f,
orientaPtero3 = 0.0f,

movPtero4_x = 0.0f,
movPtero4_z = 0.0f,
orientaPtero4 = 0.0f;

bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false,
recorrido6 = false,
animacion2 = false,

animaPtero = true,

Ptero1Reco1 = true,
Ptero1Reco2 = false,
Ptero1Reco3 = false,
Ptero1Reco4 = false,

Ptero2Reco1 = false,
Ptero2Reco2 = true,
Ptero2Reco3 = false,
Ptero2Reco4 = false,

Ptero3Reco1 = false,
Ptero3Reco2 = false,
Ptero3Reco3 = true,
Ptero3Reco4 = false,

Ptero4Reco1 = false,
Ptero4Reco2 = false,
Ptero4Reco3 = false,
Ptero4Reco4 = true;


bool avanza = false;
float giroLlantas = 0.0f; //VARIABLE DE GIRO DE LLANTAS 
int reset = 0.0f;

//Keyframes (Manipulación y dibujo) PRACTICA 10000000000000000000000000000000000000000000
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		posmanY =0.0f,
		rotRodIzq = 0.0f,
		rotRodDer = 0.0f,
		giroMonito = 0.0f,
		movBrazoIzq=0.0f,
		movBrazoDer = 0.0f,
		movCabeza = 0.0f;

float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotInc = 0.0f,
		rotDerInc = 0.0f,
		giroMonitoInc = 0.0f,
		movBrazoIzqInc = 0.0f,
		movBrazoDerInc = 0.0f,
		movCabezaInc = 0.0f;


#define MAX_FRAMES 29 
int i_max_steps = 60; //cantidad de cuadros intermedios a calcular
int i_curr_steps = 0; 
typedef struct _frame //encargada de guardar la informacion 
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float rotRodDer;
	float giroMonito;
	float movBrazoIzq;
	float movBrazoDer;
	float movCabeza;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX; 
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq; //almcenado de la informacion de su posicion con L
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].giroMonito = giroMonito; //orientacion

	KeyFrame[FrameIndex].movBrazoIzq = movBrazoIzq;

	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	KeyFrame[FrameIndex].movCabeza = movCabeza;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;

	rotRodDer = KeyFrame[0].rotRodDer;

	giroMonito = KeyFrame[0].giroMonito;

	movBrazoIzq = KeyFrame[0].movBrazoIzq;
	movBrazoDer = KeyFrame[0].movBrazoDer;

	movCabeza = KeyFrame[0].movCabeza;
}

void interpolation(void) //
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;

	rotDerInc = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	movBrazoIzqInc = (KeyFrame[playIndex + 1].movBrazoIzq - KeyFrame[playIndex].movBrazoIzq) / i_max_steps; //caluclo del incremento dcon la variable diferente 
	movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;
	movCabezaInc = (KeyFrame[playIndex + 1].movCabeza - KeyFrame[playIndex].movCabeza) / i_max_steps;
}

void animate(void) //Ciclo de animado
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			rotRodDer += rotDerInc;
			giroMonito += giroMonitoInc;
			movBrazoIzq += movBrazoIzqInc; //asignar los valores a el mov del brazo
			movBrazoDer += movBrazoDerInc;
			movCabeza += movCabezaInc;


			i_curr_steps++;
		}
	}

	//ANIMACIONES BRAYAN
	//ANIMA-PTERODACTILO
	if (animaPtero) {

		//PTERODACTILO 1
		if (Ptero1Reco1) {
			movPtero1_x = -75.0f;
			movPtero1_z += 1.0f;
			orientaPtero1 = 0.0f;
			if (movPtero1_z >= 75.0f) {
				Ptero1Reco1 = false;
				Ptero1Reco2 = true;
			}
		}

		if (Ptero1Reco2) {
			movPtero1_x += 1.0f;
			movPtero1_z = 75.0f;
			orientaPtero1 = 90.0f;
			if (movPtero1_x >= 75.0f) {
				Ptero1Reco2 = false;
				Ptero1Reco3 = true;
			}
		}

		if (Ptero1Reco3) {
			movPtero1_x = 75.0f;
			movPtero1_z -= 1.0f;
			orientaPtero1 = 180.0f;
			if (movPtero1_z <= -75.0f) {
				Ptero1Reco3 = false;
				Ptero1Reco4 = true;
			}
		}

		if (Ptero1Reco4) {
			movPtero1_x -= 1.0f;
			movPtero1_z = -75.0f;
			orientaPtero1 = 270.0f;
			if (movPtero1_x <= -75.0f) {
				Ptero1Reco4 = false;
				Ptero1Reco1 = true;
			}
		}
		//---------------------------------------------------------
				//PTERODACTILO 2
		if (Ptero2Reco1) {
			movPtero2_x = -75.0f;
			movPtero2_z += 1.0f;
			orientaPtero2 = 0.0f;
			if (movPtero2_z >= 75.0f) {
				Ptero2Reco1 = false;
				Ptero2Reco2 = true;
			}
		}

		if (Ptero2Reco2) {
			movPtero2_x += 1.0f;
			movPtero2_z = 75.0f;
			orientaPtero2 = 90.0f;
			if (movPtero2_x >= 75.0f) {
				Ptero2Reco2 = false;
				Ptero2Reco3 = true;
			}
		}

		if (Ptero2Reco3) {
			movPtero2_x = 75.0f;
			movPtero2_z -= 1.0f;
			orientaPtero2 = 180.0f;
			if (movPtero2_z <= -75.0f) {
				Ptero2Reco3 = false;
				Ptero2Reco4 = true;
			}
		}

		if (Ptero2Reco4) {
			movPtero2_x -= 1.0f;
			movPtero2_z = -75.0f;
			orientaPtero2 = 270.0f;
			if (movPtero2_x <= -75.0f) {
				Ptero2Reco4 = false;
				Ptero2Reco1 = true;
			}
		}

		//---------------------------------------------------------
			//PTERODACTILO 3

		if (Ptero3Reco1) {
			movPtero3_x = -75.0f;
			movPtero3_z += 1.0f;
			orientaPtero3 = 0.0f;
			if (movPtero3_z >= 75.0f) {
				Ptero3Reco1 = false;
				Ptero3Reco2 = true;
			}
		}

		if (Ptero3Reco2) {
			movPtero3_x += 1.0f;
			movPtero3_z = 75.0f;
			orientaPtero3 = 90.0f;
			if (movPtero3_x >= 75.0f) {
				Ptero3Reco2 = false;
				Ptero3Reco3 = true;
			}
		}

		if (Ptero3Reco3) {
			movPtero3_x = 75.0f;
			movPtero3_z -= 1.0f;
			orientaPtero3 = 180.0f;
			if (movPtero3_z <= -75.0f) {
				Ptero3Reco3 = false;
				Ptero3Reco4 = true;
			}
		}

		if (Ptero3Reco4) {
			movPtero3_x -= 1.0f;
			movPtero3_z = -75.0f;
			orientaPtero3 = 270.0f;
			if (movPtero3_x <= -75.0f) {
				Ptero3Reco4 = false;
				Ptero3Reco1 = true;
			}
		}

		//---------------------------------------------------------
			//PTERODACTILO 4

		if (Ptero4Reco1) {
			movPtero4_x = -75.0f;
			movPtero4_z += 1.0f;
			orientaPtero4 = 0.0f;
			if (movPtero4_z >= 75.0f) {
				Ptero4Reco1 = false;
				Ptero4Reco2 = true;
			}
		}

		if (Ptero4Reco2) {
			movPtero4_x += 1.0f;
			movPtero4_z = 75.0f;
			orientaPtero4 = 90.0f;
			if (movPtero4_x >= 75.0f) {
				Ptero4Reco2 = false;
				Ptero4Reco3 = true;
			}
		}

		if (Ptero4Reco3) {
			movPtero4_x = 75.0f;
			movPtero4_z -= 1.0f;
			orientaPtero4 = 180.0f;
			if (movPtero4_z <= -75.0f) {
				Ptero4Reco3 = false;
				Ptero4Reco4 = true;
			}
		}

		if (Ptero4Reco4) {
			movPtero4_x -= 1.0f;
			movPtero4_z = -75.0f;
			orientaPtero4 = 270.0f;
			if (movPtero4_x <= -75.0f) {
				Ptero4Reco4 = false;
				Ptero4Reco1 = true;
			}
		}
	}

	/*Vehículo VELOCIDAD DE MOVIMIENTO DEL COCHE
	if (animacion)
	{
		if (avanza) {
		
			movAuto_z += 2.3f;
			giroLlantas += 3.0f;
			if (movAuto_z >= 200.0f)
				avanza = false;
		
		}
		else {
		
			movAuto_z -= 2.3f;
			giroLlantas -= 3.0f;
			if (movAuto_z <= 0.0f)
				avanza = true;



		}


		








		/*if (movAuto_z < 200.0f){
		movAuto_z += 2.3f;
		giroLlantas += 3.0f;
		}
		//Movimiento estandar
		     
	}*/
	
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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
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
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
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
	Model tRex("resources/objects/trex/rex.obj");
	Model cabezarex("resources/objects/cabeza/cabezatrex.obj");
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
	
	//MODELOS B
	Model Cupula("resources/objects/Cupula/Cupula4.obj");

	Model Dino2("resources/objects/Dino2/ptero.obj");
	Model Dino2_2("resources/objects/Dino2/ptero.obj");
	Model Dino2_3("resources/objects/Dino2/ptero.obj");
	Model Dino2_4("resources/objects/Dino2/ptero.obj");

	Model GiroEsfera("resources/objects/GiroEsfera/GiroEsfera.obj");
	//FIN MODELOS B





	//MODEL MIXAMO PARASIT
	ModelAnim parasit("resources/objects/Mutant/Drunk Walk.dae");
	parasit.initShaders(animShader.ID); //añadir el objeto al shader de animacion




	/*ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	ninja.initShaders(animShader.ID);*/

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].movCabeza = 0;
	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

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



		/*PARASIT
		model = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, -20.0f));
		animShader.setMat4("model", model);
		parasit.Draw(animShader);
		*/


		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		//ninja.Draw(animShader);
		*/


		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, -10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaDoll.Draw(staticShader);
		*/
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		casaVieja.Draw(staticShader);
		*/
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1150.0f, 0.0f, -790.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		helecho.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1180.0f, 0.0f, -800.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		fPlant.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -900.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		tRex.Draw(staticShader);
		//Cabeza REX

		model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		cabezarex.Draw(staticShader);


		//Escultura
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, -150.0f, 100.0f));
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
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

		//huevo2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1070.0f, 5.0f, -850.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		huevo2.Draw(staticShader);

		//huevo3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1090.0f, 10.0f, -890.0f));
		model = glm::scale(model, glm::vec3(15.0f));
		staticShader.setMat4("model", model);
		huevo3.Draw(staticShader);

		//huevo4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1020.0f, 5.0f, -750.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(9.0f));
		staticShader.setMat4("model", model);
		huevo1.Draw(staticShader);

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
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -750.0f));
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

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1100.0f, 0.0f, 900.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
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

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1100.0f, 0.0f, -900.0f));
		model = glm::rotate(model, glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		laboratorio.Draw(staticShader);


		//invernadero

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1000.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f));
		staticShader.setMat4("model", model);
		invernadero.Draw(staticShader);





		//MODELOS BRAYAN
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		GiroEsfera.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(400.0f));
		staticShader.setMat4("model", model);
		Cupula.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero1_x, 300.0f, movPtero1_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f*0.05));
		staticShader.setMat4("model", model);
		Dino2.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero2_x, 300.0f, movPtero2_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f * 0.05));
		staticShader.setMat4("model", model);
		Dino2_2.Draw(staticShader);


		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero3_x, 300.0f, movPtero3_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero3), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f * 0.05));
		staticShader.setMat4("model", model);
		Dino2_3.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPtero4_x, 300.0f, movPtero4_z));
		tmp = model = glm::rotate(model, glm::radians(orientaPtero4), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f * 0.05));
		staticShader.setMat4("model", model);
		Dino2_4.Draw(staticShader);





		//FIN MODELOS BRAYAN

		/*CASA DE BRUJAS
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 0.0f, 30.0f)); //Creando la casa de brujas
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		casaBrujas.Draw(staticShader);*/

	


		/*CasatTec
		model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 0.0f, 200.0f));
		staticShader.setMat4("model", model);
		casaTec.Draw(staticShader); */
		// -------------------------------------------------------------------------------------------------------------------------
		/* Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(15.0f + movAuto_x, -1.0f, movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, 12.9f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, 12.9f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq trase

	




	*/



		// -------------------------------------------------------------------------------------------------------------------------
		/* Personaje                         A PARTIR DE AQUI EMPIEZA LA PRACTICA 100000000000000000000000000000000000000000
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); //ELEMENTO DE MAYOR JERARQUIA
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //POSICION DE MOVIMIENTO DEL PERSONAJE
		tmp = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaDer.Draw(staticShader);

		//Pie Der
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		botaDer.Draw(staticShader);

		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotRodDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaIzq.Draw(staticShader);

		//Pie Iz
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		botaDer.Draw(staticShader);	//Izq trase

		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(movBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(movBrazoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoIzq.Draw(staticShader);

		//Cabeza
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(movCabeza), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
		staticShader.setMat4("model", model);
		cabeza.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cubo.Draw(staticShader);
		glEnable(GL_BLEND);*/
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

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
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) //movCabeza
		movCabeza += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		movCabeza -= 2.0f;

	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) //movCabeza
		posY += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		posY -= 2.0f;


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		posmanY += 3.0;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movBrazoDer -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movBrazoIzq += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movBrazoIzq -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) //pierna derecha
		rotRodDer--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodDer++;



	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//Car animation ANIMACION DE AUTOMOVIL
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		//if (movAuto_z < 200.0f) {
			animacion ^= true;
		//}else
		//movAuto_z = 0.0f; if else comntado para detenerse al llegar al valor

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
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