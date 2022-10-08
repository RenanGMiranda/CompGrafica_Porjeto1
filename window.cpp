#include "window.hpp"

void Window::onCreate() {
  auto const &windowSettings{getWindowSettings()};
  fmt::print("Initial window size: {}x{}\n", windowSettings.width,
             windowSettings.height);
}

void Window::onPaint() {
  // Set the clear color
  abcg::glClearColor(m_clearColor.at(0), m_clearColor.at(1), m_clearColor.at(2),
                     m_clearColor.at(3));
  // Clear the color buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onPaintUI() {
  // Parent class will show fullscreen button and FPS meter
  abcg::OpenGLWindow::onPaintUI();

  // Our own ImGui widgets go below
  {
    // Window begin
    ImGui::Begin("Verificador de Triângulos");

    static std::array lados{0.0f, 0.0f, 0.0f};
    ImGui::SliderFloat3("Insira os lados", lados.data(), 0.0, 100.0);

    if ((lados[0] < lados[1] + lados[2]) && 
        (lados[1] < lados[0] + lados[2]) && 
        (lados[2] < lados[0] + lados[1])){
      ImGui::Text("\nOs lados inputados formam um triângulo");
    }
    else{
      ImGui::Text("\nInfelizmente, os lados inputados NÃO formam um triângulo");
    }

    // Window end
    ImGui::End();
  }
}