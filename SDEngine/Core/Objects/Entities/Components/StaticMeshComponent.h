#pragma once
#include "Core/Objects/Entities/Component.h"

class StaticMesh;

class StaticMeshComponent : public Component {
public:
	StaticMeshComponent(const TString& Name);
	~StaticMeshComponent();

	virtual void DrawAdvanced(const Camera* RenderCamera, const EDrawType& DrawType) override;

	void SetStaticMesh(StaticMesh* Mesh);
	StaticMesh* GetStaticMesh();

private:
	StaticMesh* Mesh;

};

