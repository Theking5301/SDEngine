#include <iostream>
#include <GLEW/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Texture2D.h"
#include "StaticMesh.h"
#include "Transform.h"
#include "Light.h"
#include <random>
#include "Grid.h"
#include "Engine.h"
#include "RenderingEngine.h"
#include "EyeActor.h"

#undef main
using namespace glm;

/*
Physics
Collision
AI/Pathfinding
Resource Management
Content Creation

How to implement? (IMO)
What are concerns you have about it?


*/
Engine* S_Engine;
int main(int argc, char* argv[]) {
	S_Engine = Engine::GetInstance();
	if (!S_Engine->Init()) {		
		return 0;
	}
	init_logger("SD_EngineLog.txt");
	PrintToLog("Engine Launched!");

	//Texture2D torusAlbedo("res/T_TorusBaseColor.tga");
	//Texture2D torusRoughness("res/T_TorusRMAO.tga");
	//Texture2D torusNormal("res/T_TorusNormal.tga");

	//Transform torusTransform;
	//torusTransform.SetUniformScale(5.0f);
	//StaticMesh torus(torusTransform, "./res/Torus.fbx");
	//torus.RegisterTexture(&torusAlbedo);
	//torus.RegisterTexture(&torusRoughness);
	//torus.RegisterTexture(&torusNormal);
	//S_Engine->GetWorld()->RegisterEntity(&torus);

	Transform skySphereTransform;
	skySphereTransform.SetUniformScale(100.0f);
	Texture2D* skySphereTexture = new Texture2D("res/ForestEnvironment.jpg");

	Material* skyMaterial = new Material("./Res/Shaders/SkySphereShader");
	skyMaterial->SetTextureParameter("Albedo", skySphereTexture);
	skyMaterial->SetShaderModel(EShaderModel::UNLIT);
	StaticMesh* sky = new StaticMesh(skySphereTransform, skyMaterial, "./res/SkySphere.fbx");
	S_Engine->GetWorld()->RegisterEntity(sky);


	Transform innerEyetransform;
	innerEyetransform.SetUniformScale(3.0f);
	innerEyetransform.SetRotation(-60, 0, 0);
	innerEyetransform.GetPosition().y = 10;

	Texture2D* albedo = new Texture2D("res/Eye/T_EyeBaseColor.tga");
	Texture2D* roughness = new Texture2D("res/Eye/T_EyeRMAO.tga");
	Texture2D* normal= new Texture2D("res/Eye/T_EyeNormal.tga");

	Material* newMaterial = new Material("./Res/Shaders/TestEyeShader");
	newMaterial->SetTextureParameter("Albedo", albedo);
	newMaterial->SetTextureParameter("RMAO", roughness);
	newMaterial->SetTextureParameter("Normal", normal);
	StaticMesh* eye = new StaticMesh(innerEyetransform, newMaterial, "./res/Eye/Eye.fbx");
	S_Engine->GetWorld()->RegisterEntity(eye);


	Transform outerEyeTransform;
	outerEyeTransform.SetUniformScale(3.0f);
	outerEyeTransform.SetRotation(-60, 0, 0);
	outerEyeTransform.GetPosition().y = 10;

	Texture2D* outerRoughness = new Texture2D("res/Eye/T_EyeClearRoughness.tga");
	Texture2D* outerNormal = new Texture2D("res/Eye/T_EyeClearNormal.tga");

	Material* outerEyeMaterial = new Material("./Res/Shaders/TranslucentShader");
	outerEyeMaterial->SetShaderModel(EShaderModel::TRANSLUCENT);
	outerEyeMaterial->SetVec3Parameter("Albedo", vec3(1.0, 1.0, 1.0));
	outerEyeMaterial->SetScalarParameter("Opacity", 0.2f);
	StaticMesh* outerEye = new StaticMesh(outerEyeTransform, outerEyeMaterial, "./res/Eye/EyeClear.fbx");
	S_Engine->GetWorld()->RegisterEntity(outerEye);

	//EyeActor* tempEye = new EyeActor(innerEyetransform);
	//S_Engine->GetWorld()->RegisterEntity(tempEye);

	Grid grid(40, 2);
	S_Engine->GetWorld()->RegisterEntity(&grid);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				float r = (float)(rand()) / (float)(RAND_MAX);
				float g = (float)(rand()) / (float)(RAND_MAX);
				float b = (float)(rand()) / (float)(RAND_MAX);
				Transform tempTransform;
				tempTransform.GetPosition().x = (float)j * 10 - 25.0f;
				tempTransform.GetPosition().y = (float)k * 10;
				tempTransform.GetPosition().z = (float)i * 10 - 25.0f;
				vec3 tempColor = vec3(r, g, b);
				float atten = ((float)(rand()) / (float)(RAND_MAX)) * 50;
				Light* tempLight = new Light(tempTransform, 20, tempColor, atten);
				//tempLight->ToggleDebug(true);
				S_Engine->GetWorld()->RegisterLight(tempLight);
			}
		}
	}
	Transform fillLightTransform;
	fillLightTransform.GetPosition().y = 50;
	Light* fillLight = new Light(fillLightTransform, 800, vec3(0.75, 0.9, 0.8), 150);
	fillLight->ToggleDebug(true);
	S_Engine->GetWorld()->RegisterLight(fillLight);

	fillLightTransform.GetPosition().y = -20;
	Light* bounceLight = new Light(fillLightTransform, 500, vec3(0.75, 0.9, 0.8), 150);
	bounceLight->ToggleDebug(true);
	S_Engine->GetWorld()->RegisterLight(bounceLight);

	S_Engine->StartEngine();
	return 0;
}