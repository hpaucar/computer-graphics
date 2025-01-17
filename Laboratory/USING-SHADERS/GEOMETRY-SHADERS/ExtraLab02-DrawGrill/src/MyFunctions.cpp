/*
 * MyFunctions.cpp
 *
 *  Created on: 2 abr. 2020
 *      Author: Usuario
 */

#include "MyFunctions.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/string_cast.hpp"


MyFunctions::MyFunctions() {
	// TODO Auto-generated constructor stub

}

MyFunctions::~MyFunctions() {
	// TODO Auto-generated destructor stub
}

std::vector<glm::vec3> MyFunctions::getRectanglePoints(glm::vec3 point0, float width, float height, const char *plane){
	std::vector<glm::vec3> fourPoints = {point0, point0, point0, point0};
	std::vector<glm::vec3> triangles;


	if(!strcmp(plane, "xy")){
		fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
		fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y - height, point0.z);
		fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
	}else if(!strcmp(plane, "xz")){
		fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
		fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y, point0.z + height);
		fourPoints[3] = glm::vec3(point0.x, point0.y, fourPoints[2].z);
	}else if(!strcmp(plane, "yz")){
		fourPoints[1] = glm::vec3(point0.x, point0.y, point0.z + width);
		fourPoints[2] = glm::vec3(point0.x, point0.y - height, fourPoints[1].z);
		fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
	}


	triangles.push_back(fourPoints[0]);
	triangles.push_back(fourPoints[1]);
	triangles.push_back(fourPoints[3]);

	triangles.push_back(fourPoints[2]);
	triangles.push_back(fourPoints[1]);
	triangles.push_back(fourPoints[3]);

	return triangles;
}

// Function draw rectangle from one point using Width, Height, Plane and color
std::vector<Point> MyFunctions::getRectanglePointsColor(glm::vec3 point0, float width, float height, const char *plane, glm::vec3 color){
	std::vector<Point> triangles;
	std::vector<glm::vec3> fourPoints = {point0, point0, point0, point0};

		if(!strcmp(plane, "xy")){
			fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
			fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y - height, point0.z);
			fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
		}else if(!strcmp(plane, "xz")){
			fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
			fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y, point0.z + height);
			fourPoints[3] = glm::vec3(point0.x, point0.y, fourPoints[2].z);
		}else if(!strcmp(plane, "yz")){
			fourPoints[1] = glm::vec3(point0.x, point0.y, point0.z + width);
			fourPoints[2] = glm::vec3(point0.x, point0.y - height, fourPoints[1].z);
			fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
		}

		Point temp;
		temp.coord = fourPoints[0];
		temp.color = color;
		triangles.push_back(temp);
		temp.coord = fourPoints[1];
		triangles.push_back(temp);
		temp.coord = fourPoints[3];
		triangles.push_back(temp);
		temp.coord = fourPoints[2];
		triangles.push_back(temp);
		temp.coord = fourPoints[1];
		triangles.push_back(temp);
		temp.coord = fourPoints[3];
		triangles.push_back(temp);

		return triangles;
}

std::vector<glm::vec3> MyFunctions::getRectangle4Points(glm::vec3 point0, float width, float height, const char *plane){
	std::vector<glm::vec3> fourPoints = {point0, point0, point0, point0};

	if(!strcmp(plane, "xy")){
		fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
		fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y - height, point0.z);
		fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
	}else if(!strcmp(plane, "xz")){
		fourPoints[1] = glm::vec3(point0.x + width, point0.y, point0.z);
		fourPoints[2] = glm::vec3(fourPoints[1].x, point0.y, point0.z + height);
		fourPoints[3] = glm::vec3(point0.x, point0.y, fourPoints[2].z);
	}else if(!strcmp(plane, "yz")){
		fourPoints[1] = glm::vec3(point0.x, point0.y, point0.z + width);
		fourPoints[2] = glm::vec3(point0.x, point0.y - height, fourPoints[1].z);
		fourPoints[3] = glm::vec3(point0.x, fourPoints[2].y, point0.z);
	}

	return fourPoints;
}

std::vector<glm::vec3> MyFunctions::getGrillPoints(glm::vec3 p0, float radio, int length, const char *plane){
	std::vector<glm::vec3> grillPoints;

	glm::vec3 abc;
	std::vector<glm::vec3> temp;
	if(!strcmp(plane, "xz")){
		for (int j = length; j >= -length; j--) {
			for (int i = length; i >= -length; i--){
				//M[i][j] = (p0.x - radio*i, p0.y, p0.z - radio*i)
				grillPoints.push_back(glm::vec3(p0.x - radio*i, p0.y, p0.z - radio*j));
			}
		}
	}

	return grillPoints;
}

std::vector<glm::vec3> MyFunctions::getGrillQuadPoints(glm::vec3 p0, float radio, int length, const char *plane){
	std::vector<glm::vec3> grillPoints;
	glm::vec3 temp;
	int sz = 2*length;
	int c = 0;
	if(!strcmp(plane, "xz")){
		glm::vec3 topLeft(p0.x - 0.5 * radio * (2 * length - 1), p0.y, p0.z - 0.5 * radio * (2 * length - 1));
		temp = topLeft;

		for (int i = 0; i < sz; i++) {
			c++;//grillPoints.push_back(temp);
			for ( int j = 1; j < sz; j++){
				temp.x = temp.x + radio;
				//grillPoints.push_back(temp);

				printf("::::>%d (%d, %d) \n",c++, (int)temp.x, (int)temp.z);
			}
			temp.x = topLeft.x;
			temp.z = temp.z + radio;
		}
	}

	printf("::::> %d :::>c: %d",grillPoints.size(), c);

	return grillPoints;
}

