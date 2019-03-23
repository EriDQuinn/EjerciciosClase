
/*---------------------------------------------------------*/
/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*-------------- Alumno: ERIKA DIAZ ACOSTA                    ---------------*/
/*-----------------Version de Visual 2017-------------------
----------------------Grupo 4------------------------------
--------------Instrucciones:--------------------------------------------------------------
---Mover con el raton y usar la rueda de scroll para acercar y alejar, ----------
------teclas extra:--------------------------------------------------------------------
 ---------------W: Acercar	-----------------------------------------------------------
 ---------------S: Alejar -----------------------------------------------------------
 ---------------A: Izquierda-----------------------------------------------------------
 ---------------D: Derecha -----------------------------------------------------------

*/
#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f;

float	sol = 0.0f,
year = 0.0f,
day = 0.0f,
moon = 0.0f,
mars_year = 0.0f,
jupiter_year = 0.0f,
luna = 0.0f,
mercurio = 0.0f,
venus = 0.0f,
tierra = 0.0f,
marte = 0.0f,
jupiter = 0.0f,
saturno = 0.0f,
urano = 0.0f,
neptuno = 0.0f,
anillo = 0.0f,
luna1 = 0.0f,
luna2 = 0.0f,
luna3 = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{
	GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.5f,
		mercurio += 0.9f,
		venus += 0.70,
		tierra += .55f,
		marte += .45f,
		jupiter += .4f,
		saturno += .35f,
		urano += .3f,
		neptuno += .25f,
		luna += 0.2f,
		luna1 += 0.1f,
		luna2 += 0.15f,
		luna3 += 0.05f,
		anillo += 1.0f

		;
}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos);
	//temporal
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar código aquí

	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 0.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 1.0f, 1.0f, 0.0f);
	my_sphere.render();	//Sphere SOL

	//lampShader.setMat4("model", model);
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light
	/*
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	//model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(1.0f));
	lampShader.setMat4("model", model);
	*/
	//MERCURIO
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3, 0, 0));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .30f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.690, 0.552, 0.450);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.850f, 0.90f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

	my_sphere.render();
	model = glm::mat4(1.0f);

	//venus
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(5, 0, 0));
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 0.1f, 0.0f));
	model = glm::scale(model, glm::vec3(0.60f, 0.60f, .60f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.690, 0.450, 0.533);
	projectionShader.setVec3("diffuseColor", 0.490, 0.450, 0.6533);
	projectionShader.setVec3("specularColor", 0.709, 0.368, 0.556);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//tierra
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(6, 0, 0));
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.650f, 0.650f, .650f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.188, 0.607, 0.750);
	projectionShader.setVec3("diffuseColor", 0.288, 0.807, 0.850);
	projectionShader.setVec3("specularColor", 0.0f, 0.60f, 0.890f);

	model = temp01;

	//luna
	model = glm::rotate(model, glm::radians(luna), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.20f, 0.20f, .20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.664, 0.494, 0.727);
	projectionShader.setVec3("diffuseColor", 0.564, 0.694, 0.627);
	projectionShader.setVec3("specularColor", 1.0f, 0.120f, 0.7780f);
	my_sphere.render();
	model = glm::mat4(1.0f);


	//marte
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(8, 0, 0));
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.450f, 0.450f, .450f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.525, 0.137, 0.203);
	projectionShader.setVec3("diffuseColor", 0.525, 0.337, 0.503);
	projectionShader.setVec3("specularColor", 0.20f, 0.670f, 0.90f);
	my_sphere.render();
	model = temp01;

	//luna2
	model = glm::rotate(model, glm::radians(luna2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1.2, 0, 0));
	model = glm::scale(model, glm::vec3(0.20f, 0.20f, .20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.274, 0.168, 0.184);
	projectionShader.setVec3("diffuseColor", 0.674, 0.468, 0.184);
	projectionShader.setVec3("specularColor", 1.0f, .20f, 0.50f);
	my_sphere.render();
	model = temp01;
	//luna3
	model = glm::rotate(model, glm::radians(luna3), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1, 1, .2));
	model = glm::scale(model, glm::vec3(0.150f, 0.150f, .150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor",0.223, 0.250, 0.168);
	projectionShader.setVec3("diffuseColor", 0.223, 0.250, 0.168);
	projectionShader.setVec3("specularColor", 1.0f, 1.0f, 0.0f);
	my_sphere.render();

	model = glm::mat4(1.0f);

	//jupiter--------
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10, 0, 0));
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.90f, 0.90f, .90f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.682, 0.492, 0.517);
	projectionShader.setVec3("diffuseColor", 0.682, 0.592, 0.517);
	projectionShader.setVec3("specularColor", 1.0f, 1.0f, 0.0f);
	my_sphere.render();
	model = temp01;

	//luna4
	model = glm::rotate(model, glm::radians(luna2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1.2, 0, 0));
	model = glm::scale(model, glm::vec3(0.20f, 0.20f, .20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.603, 0.682, 0.517);
	projectionShader.setVec3("diffuseColor", 0.603, 0.682, 0.617);
	projectionShader.setVec3("specularColor", 1.0f, .20f, 0.0f);
	my_sphere.render();
	model = temp01;

	//luna5
	model = glm::rotate(model, glm::radians(luna3), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1.5, 1, .2));
	model = glm::scale(model, glm::vec3(0.150f, 0.150f, .150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.517, 0.682, 0.647);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.850f, 0.50f);
	projectionShader.setVec3("specularColor", 1.0f, 1.0f, 0.0f);
	my_sphere.render();
	model = temp01;
	//luna6
	model = glm::rotate(model, glm::radians(luna2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-1.3, 1, 0));
	model = glm::scale(model, glm::vec3(0.20f, 0.20f, .20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.580, 0.431, 0.768);
	projectionShader.setVec3("diffuseColor", 0.423, 0.890, 0.917);
	projectionShader.setVec3("specularColor", 1.0f, 1.0f, 0.0f);
	my_sphere.render();
	model = temp01;
	//luna7
	model = glm::rotate(model, glm::radians(luna), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1.7, 1, 0));
	model = glm::scale(model, glm::vec3(0.150f, 0.150f, .150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.705, 0.431, 0.768);
	projectionShader.setVec3("diffuseColor", 0.423, 0.454, 0.917);
	projectionShader.setVec3("specularColor", 0.423, 0.898, 0.917);
	my_sphere.render();
	model = glm::mat4(1.0f);

	//saturno
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13, 0, 0));
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.550f, 0.550f, .550f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.823, 0.580, 0.513);
	projectionShader.setVec3("diffuseColor", 0.619, 0.270, 0.180);
	projectionShader.setVec3("specularColor", 0.364, 0.286, 0.235);
	my_sphere.render();
	model = temp01;

	//anillo
	model = glm::translate(model, glm::vec3(0, 0.055, 0));
	model = glm::scale(model, glm::vec3(0.80f, 0.1f, 0.80f));
	model = glm::rotate(model, glm::radians(anillo), glm::vec3(0.0f, 0.9f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.050, 0.788, 0.870);
	projectionShader.setVec3("diffuseColor", 0.690, 0.960, 0.988);
	projectionShader.setVec3("specularColor", 0.796, 0.890, 0.901);
	my_sphere.render();
	model = temp01;
	model = glm::translate(model, glm::vec3(0, -.055, 0));
	model = glm::rotate(model, glm::radians(anillo), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(.920f, 0.1f, .90f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.694, 0.603, 0.898);
	projectionShader.setVec3("diffuseColor", 0.486, 0.403, 0.678);
	projectionShader.setVec3("specularColor", 0.709, 0.650, 0.850);
	my_sphere.render();
	model = glm::mat4(1.0f);


	//urano
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(16, 0, 0));
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.40f, 0.40f, .40f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.839, 0.886, 0.7923);
	projectionShader.setVec3("diffuseColor", 0.309, 0.345, 0.274);
	projectionShader.setVec3("specularColor", 0.498, 0.580, 0.537);
	my_sphere.render();
	model = temp01;
	//luna8
	model = glm::rotate(model, glm::radians(luna1), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1.2, 0, 0));
	model = glm::scale(model, glm::vec3(0.130f, 0.130f, .130f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.886, 0.792, 0.850);
	projectionShader.setVec3("diffuseColor", 0.549, 0.372, 0.478);
	projectionShader.setVec3("specularColor", 0.364, 0.286, 0.235);
	my_sphere.render();
	model = temp01;
	//luna9
	model = glm::rotate(model, glm::radians(luna), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1, 1, .2));
	model = glm::rotate(model, glm::radians(luna), glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::scale(model, glm::vec3(0.1150f, 0.1150f, .1150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.203, 0.090, 0.309);
	projectionShader.setVec3("diffuseColor", 0.325, 0.141, 0.498);
	projectionShader.setVec3("specularColor", 0.462, 0.372, 0.549);
	my_sphere.render();

	model = glm::mat4(1.0f);
	//neptuno
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(19, 0, 0));
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.1f, 0.1f, 0.1f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, .3f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.533, 0.670, 0.866);
	projectionShader.setVec3("diffuseColor", 0.450, 0.843, 0.866);
	projectionShader.setVec3("specularColor", 0.321, 0.572, 0.980);
	my_sphere.render();
	model = temp01;// = glm::mat4(1.0f);

	//luna9
	model = glm::rotate(model, glm::radians(luna), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(1, 0, 0));
	//model = glm::rotate(model, glm::radians(luna), glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::scale(model, glm::vec3(0.20f, 0.20f, .20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.533, 0.670, 0.866);
	projectionShader.setVec3("diffuseColor", 0.658, 0.368, 0.709);
	projectionShader.setVec3("specularColor", 0.541, 0.439, 0.239);
	my_sphere.render();


	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
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


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
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

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

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