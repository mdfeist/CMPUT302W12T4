#include "HUD.h"

#include "Util.h"

osg::Vec4 textColor(1.0f,1.0f,0.0f,1.0f);

unsigned int titleCharacterSize = 92;
unsigned int layoutCharacterSize = 20;

HUD::HUD(void)
{
	// Get screen resolution
	Util::getDesktopResolution(this->width, this->height);
	this->init();
}

HUD::HUD(int w, int h) : width(w), height(h)
{
	this->init();
}


HUD::~HUD(void)
{
}

void HUD::init()
{
	this->camera = this->createOrthoCamera(this->width, this->height);
	this->geode = new osg::Geode(); 
	this->font = osgText::readFontFile("fonts/segoeui.ttf");
	camera->addChild(geode);
}

osg::Camera* HUD::getCamera()
{
	return this->camera;
}

void HUD::createTitle(const std::string& l)
{
	this->geode->addDrawable(createLabel(l, font, osg::Vec2(120, height - titleCharacterSize - 20), titleCharacterSize));
}

void HUD::createPlane(osg::Vec4 dim, osg::Vec4 color)
{
	osg::Box *box = new osg::Box(osg::Vec3(dim.x() + dim.z()/2, height - (dim.y() + dim.w()/2), -0.1), dim.z(), dim.w(), 0);
	osg::ShapeDrawable *shape = new osg::ShapeDrawable(box);

	shape->setColor(color);

	this->geode->addDrawable(shape);
}

osg::Camera* HUD::createOrthoCamera(double width, double height)
{
    osg::Camera* camera = new osg::Camera();

    camera->getOrCreateStateSet()->setMode(
        GL_LIGHTING,
        osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF
    );

    osg::Matrix m = osg::Matrix::ortho2D(0.0f, width, 0.0f, height);

    camera->setProjectionMatrix(m);
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);

    return camera;
}

osgText::Text* HUD::createLabel(const std::string& l, osgText::Font* font, osg::Vec2 position, unsigned int size)
{
    static osg::Vec3 pos(position.x(), position.y(), 0.0f);

    osgText::Text* label = new osgText::Text();

    label->setFont(font);
    label->setCharacterSize(size);
    label->setFontResolution(size, size);
    label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    label->setPosition(pos);
    label->setAlignment(osgText::Text::LEFT_BOTTOM);

    // It seems to be important we do this last to get best results?
    label->setText(l);

    return label;
}