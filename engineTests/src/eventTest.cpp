#include "eventTests.h"

TEST(Events, ResizeConstructor) {
	Engine::WindowResizeEvent e(800, 600);

	int32_t width1 = e.getWidth();
	int32_t height1 = e.getHeight();

	auto size = e.getSize();

	int32_t width2 = size.x;
	int32_t height2 = size.y;

	int32_t category = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(width2, 800);
	EXPECT_EQ(height1, 600);
	EXPECT_EQ(height2, 600);
	EXPECT_EQ(category, 1);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
}