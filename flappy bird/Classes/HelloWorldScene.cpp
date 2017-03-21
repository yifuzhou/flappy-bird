#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	world = new b2World(b2Vec2(0, -10));

	world->SetContactListener(this);

	addBird();
	addGround();
	scheduleUpdate();
	//每隔一秒添加进来一个Bar
	schedule(schedule_selector(HelloWorld::addBar), 1);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	
	Director::getInstance()->getEventDispatcher()->

		addEventListenerWithSceneGraphPriority(listener, this);
	
    
    return true;
}

void HelloWorld::BeginContact(b2Contact* contact)
{
	if (contact->GetFixtureA()->GetBody() == birdBody || contact->GetFixtureB()->GetBody() == birdBody)
		MessageBox("game over", "game over");
}

void HelloWorld::update(float dt)
{
	world->Step(dt, 8, 3);
	Sprite *s;

	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData())
		{
			s = (Sprite*)b->GetUserData();
			s->setPosition(b->GetPosition().x*RATIO, b->GetPosition().y*RATIO);
		}
	}
}

void HelloWorld::addBird()
{
	
	auto bird = Sprite::create("bird_blue_0.png");
	Size size = bird->getContentSize();
	b2BodyDef def;
	def.position = b2Vec2(3, 5);
	def.type = b2_dynamicBody;
	birdBody = world->CreateBody(&def);

	
	bird->setPosition(Point(def.position.x*RATIO, def.position.y*RATIO));
	birdBody->SetUserData(bird);
	addChild(bird);
	

	b2PolygonShape shape;
	shape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	birdBody->CreateFixture(&fixtureDef);
}

void HelloWorld::addGround()
{
	/*auto g = Sprite::create("ground.PNG");
Size size = g->getContentSize();

	b2BodyDef def;
	def.type = b2_staticBody;
	def.position = b2Vec2(size.width/2/RATIO, size.height/2/RATIO);
	b2Body* body = world->CreateBody(&def);
	
	b2PolygonShape groundShape;
	groundShape.SetAsBox(size.width / 2 / RATIO, size.height / 2 / RATIO);
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	body->CreateFixture(&groundFixtureDef);
	addChild(g);*/

	b2BodyDef def;
	def.position = b2Vec2(400 / RATIO, 0);
	def.type = b2_staticBody;

	groundBody = world->CreateBody(&def);

	b2PolygonShape groundshape;
	groundshape.SetAsBox(400 / RATIO, 0.5);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundshape;
	groundBody->CreateFixture(&fixtureDef);

}

void HelloWorld::addBar(float dt)
{
	float offset = -rand() % 5;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//创建down bar
	auto down_bar = Sprite::create("bound_down.png");
	Size size = down_bar->getContentSize();
	b2BodyDef down_bar_body_def;
	down_bar_body_def.type = b2_kinematicBody;
	down_bar_body_def.position = b2Vec2(visibleSize.width / RATIO + 2, size.height / 2 / RATIO+offset);
	down_bar_body_def.linearVelocity = b2Vec2( - 5, 0);
	b2Body *down_bar_body = world->CreateBody(&down_bar_body_def);

	b2PolygonShape down_bar_shape;
	down_bar_shape.SetAsBox(size.width / 2 / RATIO, size.height / 2 / RATIO);
	b2FixtureDef down_bar_fixture_def;
	down_bar_fixture_def.shape = &down_bar_shape;
	down_bar_body->CreateFixture(&down_bar_fixture_def);

	down_bar_body->SetUserData(down_bar);
	addChild(down_bar);

	//创建up bar
	auto up_bar = Sprite::create("bound_up.png");
	Size up_bar_size = up_bar->getContentSize();
	b2BodyDef up_bar_body_def;
	up_bar_body_def.type = b2_kinematicBody;
	up_bar_body_def.position = b2Vec2(visibleSize.width / RATIO + 2, size.height / RATIO + offset+ 2 +up_bar_size.height/2/RATIO);
	up_bar_body_def.linearVelocity = b2Vec2(-5, 0);
	b2Body *up_bar_body = world->CreateBody(&up_bar_body_def);

	b2PolygonShape up_bar_shape;
	up_bar_shape.SetAsBox(up_bar_size.width / 2 / RATIO, up_bar_size.height / 2 / RATIO);
	b2FixtureDef up_bar_fixture_def;
	up_bar_fixture_def.shape = &up_bar_shape;
	up_bar_body->CreateFixture(&up_bar_fixture_def);

	up_bar_body->SetUserData(up_bar);
	addChild(up_bar);

}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	birdBody->SetLinearVelocity(b2Vec2(0, 5));
	return true;
}

