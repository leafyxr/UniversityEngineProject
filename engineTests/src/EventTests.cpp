#include "EventTests.h"

TEST(Events, ResizeConstructor) {
	int gotWidth = re.getWidth();
	int gotHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(gotWidth, width);
	EXPECT_EQ(gotHeight, height);
}

TEST(Events, DispatchTrue) {
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchFalse) {
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleTrue) {
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleFalse) {
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeFalse, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_FALSE(result);
}

TEST(Events, CloseConstructor) {
	Engine::EventType type = ce.getEventType();
}

TEST(Events, DispatchCloseTrue) {
	Engine::EventDispatcher dispatcher(ce);
	dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(onClose, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_FALSE(result);
}

TEST(Events, FocusConstructor) {
	int GetxPos = fe.getXPos();
	int GetyPos = fe.getYPos();
	Engine::EventType type = fe.getEventType();

	EXPECT_EQ(GetxPos, xPos);
	EXPECT_EQ(GetyPos, yPos);
}

TEST(Events, DispatchFocusTrue)
{
	Engine::EventDispatcher dispatcher(fe);
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onFocusTrue, std::placeholders::_1));
	bool result = fe.handled();
	EXPECT_TRUE(result);
}
TEST(Events, DispatchFocusFalse)
{
	Engine::EventDispatcher dispatcher(fe);
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onFocusFalse, std::placeholders::_1));
	bool result = fe.handled();
	EXPECT_FALSE(result);
}