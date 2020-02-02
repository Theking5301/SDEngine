#include "StaticMeshComponent.h"
#include "Core/DataStructures/DataStructures.h"
#include "Entities/StaticMesh.h"
#include "Entities/Actor.h"
#include "Engine/EngineStatics.h"

StaticMeshComponent::StaticMeshComponent(const TString& Name) : Component(Name) {
	Mesh = nullptr;
}
StaticMeshComponent::~StaticMeshComponent() {

}
void StaticMeshComponent::DrawAdvanced(Camera* RenderCamera, EDrawType DrawType) {
	if (!Mesh) {
		return;
	}

	for (FSubMesh* subMesh : Mesh->GetSubMeshes()) {
		if (DrawType == SCENE_RENDER) {
			if (!subMesh->SubMeshMaterial) {
				EngineStatics::GetDefaultMaterial()->BindMaterial(GetWorldTransform(), GetLastFrameWorldTransform(), RenderCamera);
			} else {
				subMesh->SubMeshMaterial->BindMaterial(GetWorldTransform(), GetLastFrameWorldTransform(), RenderCamera);
			}
		}

		glBindVertexArray(subMesh->VertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh->VertexArrayBuffers[INDEX_VB]);
		glDrawElements(GL_TRIANGLES, subMesh->Indices.Count(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
void StaticMeshComponent::SetStaticMesh(StaticMesh* Mesh) {
	this->Mesh = Mesh;
	if (!Mesh->SentToGPU()) {
		Mesh->GenerateGPUBuffers();
	}
}
StaticMesh* StaticMeshComponent::GetStaticMesh() {
	return Mesh;
}