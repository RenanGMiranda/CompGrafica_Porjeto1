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
    ImGui::Begin("Verificador de Triângulos: Lados e Ângulos");

    // 3 Sliders ao lado
    static std::array lados{0.0f, 0.0f, 0.0f};
    ImGui::SliderFloat3("Insira os lados", lados.data(), 0.0, 100.0);
  
    // Verioficação da existência de triângulos a partir dos lados inseridos dos sliders
    if ((lados[0] < lados[1] + lados[2]) && 
        (lados[1] < lados[0] + lados[2]) && 
        (lados[2] < lados[0] + lados[1])){
      ImGui::Text("Os lados inputados formam um triângulo\n");
    }
    else{
      ImGui::Text("Infelizmente, os lados inputados NÃO formam um triângulo\n");
    }

    //Criação de 2 Sliders, um abaixo do outro 
    static float angulo1{};
    ImGui::SliderFloat("Angulo1", &angulo1, 0.0f, 180.0f);

    static float angulo2{};
    ImGui::SliderFloat("Angulo2", &angulo2, 0.0f, (180.0 - angulo1));

    // A partir dos valores dos Sliders, são calculados e verificados os ângulos do triângulo, mostrando sua existencia, seu tipo e o valor do 3º ângulo
    if ((angulo1 == 0.0) || (angulo2 == 0.0) || (angulo1 + angulo2 >= 180.0)){
      ImGui::Text("Infelizmente, Não existe um triângulo com esses ângulos inputados, a soma dos dois ângulos inputados é >= a 180\n");
    }

    else{
      if ((angulo1 == angulo2) && (angulo1 != 60.0)){
      ImGui::Text("O seu triângulo é Isósceles, com os ângulos 1 e 2 iguais, e o ângulo 3 igual a %f\n", (180 - angulo1 - angulo2));
      }

      else if ((angulo1 == (180.0 - angulo2)/2) && (angulo1 != 60.0)){
        ImGui::Text("O seu triângulo é Isósceles, com os ângulos 1 e 3 iguais, e o ângulo 3 igual a %f\n", (180 - angulo1 - angulo2));
      }

      else if ((angulo2 == (180.0 - angulo1)/2) && (angulo2 != 60.0)){
        ImGui::Text("O seu triângulo é Isósceles, com os ângulos 2 e 3 iguais, e o ângulo 3 igual a %f\n", (180 - angulo1 - angulo2));
      }

      else if (angulo1 == 60.0 && angulo2 == 60.0){
        ImGui::Text("O seu triângulo é Equilátero, com todos os ângulos iguais a 60°\n");
      }

      else{
        ImGui::Text("O seu triângulo é Iscaleno, com todos os ângulos diferentes, e o angulo 3 igual a %f\n", (180 - angulo1 - angulo2));
      }

    }



    // Window end
    ImGui::End();
  }

}