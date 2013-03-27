/**
 * Objects.cpp
 * Created By: Michael Feist
 */

#include <osg/Geometry>

#include "Objects.h"

const int PLANELENGTH = 10;

osg::Geode *Objects::createPlane() {
	// vertex array
	osg::Vec3Array *vertexArray = new osg::Vec3Array();
	vertexArray->push_back(osg::Vec3(0, PLANELENGTH, 0));
	vertexArray->push_back(osg::Vec3(0, 0, 0));
	vertexArray->push_back(osg::Vec3(PLANELENGTH, 0, 0));
	vertexArray->push_back(osg::Vec3(PLANELENGTH, PLANELENGTH, 0));

	// face array
	// give indices of vertices in counter-clockwise order
	osg::DrawElementsUInt *faceArray = new osg::DrawElementsUInt(
		osg::PrimitiveSet::QUADS, 0
	);
	faceArray->push_back(0);
	faceArray->push_back(1);
	faceArray->push_back(2);
	faceArray->push_back(3);

	// normal array
	// give the normals on the cube's faces
	osg::Vec3Array *normalArray = new osg::Vec3Array();
	normalArray->push_back(osg::Vec3(0, 0, +1));

	// normal index
	// assign each vertex a normal (similar to assigning colors)
	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 24, 4> *normalIndexArray;
	normalIndexArray = new osg::TemplateIndexArray<
		unsigned int, osg::Array::UIntArrayType, 24, 4
	>();
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);

	// texture coordinates
	osg::Vec2Array *texCoords = new osg::Vec2Array();
	texCoords->push_back(osg::Vec2(0.0, 1.0));
	texCoords->push_back(osg::Vec2(0.0, 0.0));
	texCoords->push_back(osg::Vec2(1.0, 0.0));
	texCoords->push_back(osg::Vec2(1.0, 1.0));

	osg::Geometry *geometry = new osg::Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setNormalArray(normalArray);
	geometry->setNormalIndices(normalIndexArray);
	geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	geometry->setTexCoordArray(0, texCoords);
	geometry->addPrimitiveSet(faceArray);

	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(geometry);
	return geode;
}