#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Box2D/Box2D.h"
#define RATIO 80.0f 

class HelloWorld : public cocos2d::Layer,public b2ContactListener
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

	void addBird();
	void addGround();
	virtual void update(float dt);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void BeginContact(b2Contact* contact);

private:
	b2World *world;
	b2Body *birdBody;
	b2Body *groundBody;
	void addBar(float dt);

};

#endif // __HELLOWORLD_SCENE_H__
