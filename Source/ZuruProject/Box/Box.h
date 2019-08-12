#pragma once
#include "CoreMinimal.h"

class Box {

public:
	Box();
	Box(const float iLenX, const float iLenY, const float iLenZ);
	virtual ~Box();

	virtual void BuildFace(const FVector& iTopLeft, const FVector& iBottomLeft, const FVector& iTopRight, const FVector& iBottomRight, const FVector& iNormal, int32_t& iVertexOffset);

public:
	float mLengthX;
	float mLengthY;
	float mLengthZ;

	TArray<int32> mTriangles;
	TArray<FVector> mVerices;
	TArray<FVector> mNormals;

	TArray<FVector> mTopFaceVertices;
private:
	void BuildBox();
};
