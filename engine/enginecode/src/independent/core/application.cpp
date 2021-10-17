/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>

#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/indexBuffer.h"
#include "rendering/subTexture.h"
#include "rendering/shaders.h"
#include "rendering/Render2D.h"
#include "rendering/Render3D.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		//Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		// Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem.reset(new GLFWSystem);
#endif
		m_windowSystem->start();

		// Start timer (not a system)
		m_timer.reset(new ChronoTimer);
		m_timer->start();

		WindowProperties props("My Game Engine", 1024, 800);

		m_window.reset(Window::Create(props));

		//window setters
		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMovedCallback(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));

		//keyboard setters
		m_window->getEventHandler().setOnKeyPressedCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleasedCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));

		//mouse setters
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonPressedCallback(std::bind(&Application::onButtonPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonReleasedCallback(std::bind(&Application::onButtonReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseScrolledCallback(std::bind(&Application::onScroll, this, std::placeholders::_1));

		//input poller
		InputPoller::setNativeWindow(m_window->getNativeWindow());

		m_timer->reset();
	}

	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		m_running = false;
		return e.handled();
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		//Log::info("Window Resize event: ({0}, {1})", size.x, size.y);
		return e.handled();
	}

	bool Application::onWindowMoved(WindowMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Window moved event: ({0}, {1})", pos.x, pos.y);
		return e.handled();
	}

	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		//Log::info("Window gained focus");
		return e.handled();
	}

	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		//Log::info("Lost focus");
		return e.handled();
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		//Log::info("Key pressed event: key: {0}, repeat{1}", e.getKeyCode(), e.getRepeatCount());
		//if (e.getKeyCode() == NG_KEY_SPACE) Log::error("SPACEBAR");
		return e.handled();
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Key released event: key: {0}", e.getKeyCode());
		//if (e.getKeyCode() == NG_KEY_W) Log::error("W key released");
		return e.handled();
	}

	bool Application::onMouseMoved(MouseMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Mouse moved event: Button: {0}, {1}", pos.x, pos.y);
		return e.handled();
	}

	bool Application::onButtonPressed(MousePressedButtonEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse pressed event: Button: {0}", e.getButtonPressed());
		return e.handled();
	}

	bool Application::onButtonReleased(MouseReleasedButtonEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse released event: Button: {0}", e.getButtonPressed());
		return e.handled();
	}

	bool Application::onScroll(MouseScrolledEvent& e)
	{
		e.handle(true);
		//auto& scroll = e.get
		//Log::info("Mouse scrolled: {0}", e.ge);
		return e.handled();
	}

	Application::~Application()
	{
		// Stop systems

		// Stop logger
		m_logSystem->stop();
		// Stop windows system
		m_windowSystem->stop();

	}


	void Application::run()
	{

#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  (0.0f), (0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  (0.f),  (0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  (0.33f),(0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  (0.33f),(0.f),

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  (0.33f),(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  (0.66f),(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  (0.66f),(0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  (0.33), (0.f),

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  (1.f),  (0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  (0.66f),(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  (0.66f),(0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  (1.0f), (0.5f),

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  (0.f),  (0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  (0.f),  (1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  (0.33f),(1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  (0.3f), (0.5f),

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  (0.66f),(0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  (0.33f),(0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  (0.33f),(1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  (0.66f),(1.0f),
				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  (1.0f), (1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  (1.0f), (0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  (0.66f),(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  (0.66f),(1.0f)
		};																	

		float pyramidVertices[8 * 16] = {
			//	 <------ Pos ------>  <--- normal --->		<-- UV -->
				-0.5f, -0.5f, -0.5f,  0.0f, -1.f, 0.f,		0.f, 0.f,	//square Magneta
				 0.5f, -0.5f, -0.5f,  0.0f, -1.f, 0.f,		0.f, 0.5f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.f, 0.f,		0.33f, 0.5f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.f, 0.f,		0.33f, 0.0f,

				-0.5f, -0.5f, -0.5f, -0.8944f, 0.4472f, 0.f,	0.33f, 1.f,	//triangle Green
				-0.5f, -0.5f,  0.5f, -0.8944f, 0.4472f, 0.f,	0.66f, 1.f,
				 0.0f,  0.5f,  0.0f, -0.8944f, 0.4472f, 0.f,	(0.33 + 0.66) * 0.5f, 0.5f,

				-0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,	0.f, 0.f,	//triangle Red
				 0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, 0.8944f,	0.f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8944f, 0.4472f, 0.f,	0.f, 0.f,	//triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8944f, 0.4472f, 0.f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.8944f, 0.4472f, 0.f,	0.f, 0.f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.4472f, -0.8944f,	0.f, 0.f,	//triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.4472f, -0.8944f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, -0.8944f,	0.f, 0.f,
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		
		//cubes
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(VertexArray::create());

		BufferLayout cubeBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));


		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		//pyramid
		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());

		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), cubeBL));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);

#pragma endregion

#pragma region SHADERS

		std::shared_ptr<Shader> TPShader;
		TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 

#pragma region TEXTURES

		std::shared_ptr<Texture> letterTexture;
		letterTexture.reset(Texture::create("assets/textures/letterCube.png"));
		std::shared_ptr<Texture> numberTexture;
		numberTexture.reset(Texture::create("assets/textures/numberCube.png"));

		unsigned char whitePx[4] = { 255,255,255,255 };
		std::shared_ptr<Texture> plainWhiteTexture;
		plainWhiteTexture.reset(Texture::create2(1, 1, 4, whitePx));

		//SubTexture letterCube(letterTexture, { 0.f,0.f }, { 1.0f, 0.5f });
		//SubTexture numberCube(letterTexture, { 0.f,0.5f }, { 1.0f, 1.0f });

#pragma endregion

#pragma region MATERIALS

		std::shared_ptr<Material> pyramidMat;
		std::shared_ptr<Material> letterCubeMat;
		std::shared_ptr<Material> numberCubeMat;

		pyramidMat.reset(new Material(TPShader, { 0.4f, 0.7f, 0.3f, 1.f }));
		letterCubeMat.reset(new Material(TPShader, letterTexture));
		numberCubeMat.reset(new Material(TPShader, numberTexture));
	
#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glm::mat4 view2D = glm::mat4(1.f);
		glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f);

		SceneWideUniforms swu3D;

		glm::vec3 lightData[3] = { {1.f, 1.f, 1.f},{ 1.f, 4.f, 6.f},{ 0.f, 0.f, 0.f	} };

		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view)));
		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection)));
		swu3D["u_lightColour"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[0])));
		swu3D["u_lightPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[1])));
		swu3D["u_viewPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[2])));


		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view2D)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));

		float timestep = 0.f;


		Quad quads[6] =
		{
			Quad::createCentreHalfExtrents({ 400.f, 200.f }, { 100.f, 50.f }),
			Quad::createCentreHalfExtrents({ 800.f, 600.f }, { 50.f,100.f }),
			Quad::createCentreHalfExtrents({ 500.f, 650.f }, { 75.f,75.f }),
			Quad::createCentreHalfExtrents({ 100.f, 200.f }, { 50.f,50.f }),
			Quad::createCentreHalfExtrents({ 500.f, 100.f }, { 50.f,25.f }),
			Quad::createCentreHalfExtrents({ 300.f, 50.f }, { 75.f,15.f })
		};

		glClearColor(0.25f, 0.7f, 0.1f, 1.0f);

		Render2D::init();
		Render3D::init();

		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			//Spin cubes
			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			glEnable(GL_DEPTH_TEST);

			// Do frame stuff
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Render3D::begin(swu3D);
			Render3D::submit(pyramidVAO, pyramidMat, models[0]);
			Render3D::submit(cubeVAO, letterCubeMat, models[1]);
			Render3D::submit(cubeVAO, numberCubeMat, models[2]);
			Render3D::end();

			//for (auto& model : models) { model = glm::rotate(model, timestep * 0.5f, { 0, 1, 0 }); }

			glDisable(GL_DEPTH_TEST);

			Render2D::begin(swu2D);
			Render2D::submit(quads[0], { 0.f,0.f, 1.f,1.f });
			Render2D::submit(quads[1], { letterTexture });
			Render2D::submit(quads[2], { 0.f,1.f,1.f,1.f }, numberTexture);
			Render2D::submit(quads[3], { 1.f,1.f,0.f,1.f }, numberTexture, 45.f, true);
			Render2D::submit(quads[3], { 0.f,1.f,1.f,1.f }, numberTexture, glm::radians(-45.f));
			Render2D::submit(quads[4], { 1.f,1.f,0.f,1.f }, 45.f, true);
			Render2D::submit(quads[5], { 0.f,1.f,1.f,1.f }, letterTexture, 90.f, true);
			Render2D::end();

			m_window->onUpdate(timestep);
		}

	}

}