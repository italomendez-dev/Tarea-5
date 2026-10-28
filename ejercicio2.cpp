#include <iostream>
#include <memory>
#include <string>

class Window {
public:
    virtual ~Window() = default;
    virtual void draw() const = 0;
};

class Button {
public:
    virtual ~Button() = default;
    virtual void draw() const = 0;
};

class Shader {
public:
    virtual ~Shader() = default;
    virtual void compile() const = 0;
};

class OpenGLWindow : public Window {
public:
    void draw() const override {
        std::cout << "Dibujando ventana con OpenGL\n";
    }
};

class OpenGLButton : public Button {
public:
    void draw() const override {
        std::cout << "Dibujando boton con estilo OpenGL\n";
    }
};

class OpenGLShader : public Shader {
public:
    void compile() const override {
        std::cout << "Compilando shader GLSL para OpenGL\n";
    }
};

class VulkanWindow : public Window {
public:
    void draw() const override {
        std::cout << "Dibujando ventana con Vulkan\n";
    }
};

class VulkanButton : public Button {
public:
    void draw() const override {
        std::cout << "Dibujando boton con estilo Vulkan\n";
    }
};

class VulkanShader : public Shader { public: void compile() const override { std::cout << "Compilando shader SPIR-V para Vulkan\n"; } };

class RenderFactory {
public:
    virtual ~RenderFactory() = default;
    virtual std::unique_ptr<Window> createWindow() const = 0;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Shader> createShader() const = 0;
};
class OpenGLFactory : public RenderFactory {
public:
    std::unique_ptr<Window> createWindow() const override {
        return std::make_unique<OpenGLWindow>();
    }
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<OpenGLButton>();
    }
    std::unique_ptr<Shader> createShader() const override {
        return std::make_unique<OpenGLShader>();
    }
};
class VulkanFactory : public RenderFactory {
public:
    std::unique_ptr<Window> createWindow() const override {
        return std::make_unique<VulkanWindow>();
    }
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<VulkanButton>();
    }
    std::unique_ptr<Shader> createShader() const override {
        return std::make_unique<VulkanShader>();
    }
};

int main() {
    std::unique_ptr<RenderFactory> factory =
            std::make_unique<OpenGLFactory>();

    auto window = factory->createWindow();
    auto button = factory->createButton();

    window->draw();
    button->draw();

    factory = std::make_unique<VulkanFactory>();

    auto newWindow = factory->createWindow();
    auto newButton = factory->createButton();
    auto shader = factory->createShader();

    newWindow->draw();
    newButton->draw();
    shader->compile();
}
