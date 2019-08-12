#include "Box.h"

Box::Box() :mLengthX(10), mLengthY(10), mLengthZ(10) {
	this->BuildBox();
}

Box::Box(const float iLenX, const float  iLenY, const float  iLenZ):mLengthX(iLenX),mLengthY(iLenY),mLengthZ(iLenZ) {

	this->BuildBox();
}
Box::~Box(){}

void Box::BuildBox() {
	float pXPoint = (this->mLengthX) / 2.f;
	float pYPoint = (this->mLengthY) / 2.f;
	float pZPoint = (this->mLengthZ) / 2.f;

	FVector p0 = FVector(pXPoint, pYPoint, -pZPoint);
	FVector p1 = FVector(pXPoint, -pYPoint, -pZPoint);
	FVector p2 = FVector(pXPoint, -pYPoint, pZPoint);
	FVector p3 = FVector(pXPoint, pYPoint, pZPoint);
	FVector p4 = FVector(-pXPoint, pYPoint, -pZPoint);
	FVector p5 = FVector(-pXPoint, -pYPoint, -pZPoint);
	FVector p6 = FVector(-pXPoint, -pYPoint, pZPoint);
	FVector p7 = FVector(-pXPoint, pYPoint, pZPoint);

	FVector pNormalFrontFace(1, 0, 0);
	FVector pNormalBackFace(-1, 0, 0);
	FVector pNormalLeftFace(0, -1, 0);
	FVector pNormalRightFace(0, 1, 0);
	FVector pNormalUpperFace(0, 0, 1);
	FVector pNormalBottomFace(0, 0, -1);

	int32_t pVectorOffset = 0;
	//Front Face
	this->BuildFace(p3, p0, p2, p1, pNormalFrontFace, pVectorOffset);

	//Back
	this->BuildFace(p6, p5, p7, p4, pNormalBackFace, pVectorOffset);

	//Left
	this->BuildFace(p2, p1, p6, p5, pNormalLeftFace, pVectorOffset);

	//Right
	this->BuildFace(p7, p4, p3, p0, pNormalRightFace, pVectorOffset);

	//Top
	this->BuildFace(p2, p6, p3, p7, pNormalUpperFace, pVectorOffset);
	this->mTopFaceVertices = { p2,p6,p3,p7 };

	//bottom
	this->BuildFace(p5, p1, p4, p0, pNormalBottomFace, pVectorOffset);
}
void Box::BuildFace(const FVector& iTopLeft, const FVector& iBottomLeft, const FVector& iTopRight, const FVector& iBottomRight, const FVector& iNormal, int32_t& iVertexOffset) {


	int32 pIndex1 = iVertexOffset++;
	int32 pIndex2 = iVertexOffset++;
	int32 pIndex3 = iVertexOffset++;
	int32 pIndex4 = iVertexOffset++;

	this->mVerices.Add(iBottomLeft);
	this->mVerices.Add(iBottomRight);
	this->mVerices.Add(iTopRight);
	this->mVerices.Add(iTopLeft);

	this->mTriangles.Add(pIndex1);
	this->mTriangles.Add(pIndex2);
	this->mTriangles.Add(pIndex3);
	this->mTriangles.Add(pIndex1);
	this->mTriangles.Add(pIndex3);
	this->mTriangles.Add(pIndex4);

	this->mNormals.Add(iNormal);
	this->mNormals.Add(iNormal);
	this->mNormals.Add(iNormal);
	this->mNormals.Add(iNormal);

}