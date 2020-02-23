#include "Light.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include "Core/Engine/EngineStatics.h"
#include "Core/Engine/Engine.h"
#include "Core/Rendering/DefferedCompositor.h"
#include "Core/Assets/AssetManager.h"
#include "Core/Objects/CoreTypes/Texture2D.h"


Light::Light(TString Name, const Transform IntialTransform, ELightType Type, float Intensity, vec3 Color, float Attenuation, bool CastShadows) : Actor(Name) {
	SetObjectType("Light");
	SetTransform(IntialTransform);
	S_LightInfo.Type = Type;
	S_LightInfo.Intensity = Intensity;
	S_LightInfo.Color = Color;
	S_LightInfo.Attenuation = Attenuation;
	S_DebugMaterial = new Material(EngineStatics::GetLightDebugShader());
	S_DebugMaterial->SetShaderModel(EShaderModel::UNLIT);
	S_DebugMaterial->SetVec3Parameter("Color", Color);

	bCastShadows = CastShadows;

	RegisterComponent(new BillboardComponent("PointLightSprite", Engine::Get()->GetAssetManager()->FindAsset<Texture2D>("./Res/Assets/Editor/Textures/PointLightSprite.sasset"), Color));

	//S_AABB = new AxisAlignedBoundingBox(vec3(0.0f, -1.0f, -1.0f), vec3(0.0f, 1.0f, 1.0f));

	if (S_LightInfo.Type == DIRECTIONAL) {
		S_ShadowOrthoMatrix = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 40.0f);

		S_ShadowBuffer = new RenderTarget(vec2(2048, 2048));
		S_ShadowBuffer->AddTextureIndex(new FRenderTargetTextureEntry("shadowDepth", GL_RG32F, GL_LINEAR, GL_CLAMP_TO_BORDER, GL_RGBA, GL_FLOAT));
		S_ShadowBuffer->AddDepthStencilBuffer();
		S_ShadowBuffer->FinalizeRenderTarget();

		S_ShadowBufferTemp = new RenderTarget(vec2(2048, 2048));
		S_ShadowBufferTemp->AddTextureIndex(new FRenderTargetTextureEntry("shadowDepth", GL_RG32F, GL_LINEAR, GL_CLAMP_TO_BORDER, GL_RGBA, GL_FLOAT));
		S_ShadowBuffer->AddDepthStencilBuffer();
		S_ShadowBufferTemp->FinalizeRenderTarget();
	}
}
Light::~Light() {}


void Light::SendShaderInformation(Shader* shader, int index) {
	shader->SetShaderInteger("lights[" + std::to_string(index) + "].Type", GetLightInfo().Type);
	shader->SetShaderFloat("lights[" + std::to_string(index) + "].Intensity", GetLightInfo().Intensity);
	shader->SetShaderFloat("lights[" + std::to_string(index) + "].Attenuation", GetLightInfo().Attenuation);
	shader->SetShaderVector3("lights[" + std::to_string(index) + "].Color", GetLightInfo().Color);
	shader->SetShaderVector3("lights[" + std::to_string(index) + "].Position", GetTransform().GetLocation());
	shader->SetShaderVector3("lights[" + std::to_string(index) + "].Direction", GetTransform().GetForwardVector());
	shader->SetShaderInteger("lights[" + std::to_string(index) + "].CastsShadow", CastsShadows());
	shader->SetShaderMatrix4("lights[" + std::to_string(index) + "].VPMatrix", GetLightOrthogonalMatrix()*GetLightViewMatrix());
	
	if (S_LightInfo.Type == DIRECTIONAL && CastsShadows()) {
		glActiveTexture(GL_TEXTURE0 + 9);
		glBindTexture(GL_TEXTURE_2D, S_ShadowBuffer->GetTexture(0));
		glUniform1i(glGetUniformLocation(shader->GetProgram(), S_ShadowBuffer->GetTextureName(0).c_str()), 9);
	}
}
mat4 Light::GetLightViewMatrix() {
	return lookAt(vec3(0,0,0), CurrentTransform.GetForwardVector(), vec3(0, 0, 1));
}
mat4 Light::GetLightOrthogonalMatrix() {
	return S_ShadowOrthoMatrix;
}

void Light::GenerateShadowTexture(DefferedCompositor* Compositor) {
	if (!bCastShadows) {
		return;
	}
	S_ShadowBuffer->BindForWriting();
	glClear(GL_DEPTH_BUFFER_BIT);

	SArray<Actor*> entityList = GetWorld()->GetWorldActors();
	for (Actor* actor : GetWorld()->GetWorldActors()) {
		if (actor->ShouldBeDrawn(SHADOW_MAP_RENDER)) {
			EngineStatics::GetShadowShader()->Bind();
			mat4 mvp;
			mvp = GetLightOrthogonalMatrix() * GetLightViewMatrix();
			mvp = mvp * actor->GetTransform().GetModelMatrix();
			EngineStatics::GetShadowShader()->SetShaderMatrix4("MVP", mvp);
			actor->DrawAdvanced(nullptr, SHADOW_MAP_RENDER);
		}
	}

	S_ShadowBufferTemp->BindForWriting();

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, S_ShadowBuffer->GetTexture(0));
	glUniform1i(glGetUniformLocation(EngineStatics::GetGausBlur7x1Shader()->GetProgram(), S_ShadowBuffer->GetTextureName(0).c_str()), 0);

	Compositor->DrawScreenQuad();

	S_ShadowBuffer->BindForWriting();


	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, S_ShadowBufferTemp->GetTexture(0));
	glUniform1i(glGetUniformLocation(EngineStatics::GetGausBlur7x1Shader()->GetProgram(), S_ShadowBufferTemp->GetTextureName(0).c_str()), 0);

	Compositor->DrawScreenQuad();
}
void Light::BlurTexture(RenderTarget* ReadBuffer, RenderTarget* WriteBuffer) {
	
}
//bool Light::TraceAgainstRay(vec3 Origin, vec3 Direction, vec3& HitPoint, float& Distance, ECollisionChannel Channel) {
//	if (Channel == EDITOR) {
//		if (!Engine::GetInstance()->IsInGameMode()) {
//			if (S_LightInfo.Type == DIRECTIONAL) {
//				return S_Probe->TraceAgainstRay(Origin, Direction, HitPoint, Distance);
//			} else {
//				return Sprite->TraceAgainstRay(Origin, Direction, HitPoint, Distance);
//			}	
//		}
//	}
//	return false;
//}
