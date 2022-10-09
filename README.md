# CompGrafica_Projeto1
## Verificador de Triângulo

Para esse primeiro projeto par ao disciplina de Computação Gráfica, foi feito um verificador de triângulos utilizando interface gráfica.
Esse verificador possui duas aplicações:

1ª Através de inputações do usuário (deslizando os sliders) é informado se os tamanhos dos lados inseridos formam ou não um triângulo.

2ª Através de inputações do usuário (deslizando os sliders) é informado se os ângulos inseridos formam ou triângulo, se sim, qual tipo de triângulo e qual o valor do 3°.

## Implementação

### main.cpp

Praticamente, esse arquivo não houve alterações ao main.cpp do firstapp. Somente houve mudança no nome da página, presente na linha 10:

~~~C++
window.setWindowSettings({.title = "É Triângulo"});
~~~

### window.hpp

Esse arquivo não houve alterações, foi utilizado o mesmo window.hpp do firstapp.

### window.cpp

Este arquivo possui os comandos para a implementação do programa. Abaixo será explicado as suas particularidades.

##### onPaintUI

~~~C++
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
  ~~~

Vamos ver com mais atenção cada parte do código:

~~~C++
abcg::OpenGLWindow::onPaintUI();
~~~
Acima temos a função membro onPaintUI da classe base, que mostra o medidor de FPS e o botão para alternar entre o modo janela e tela cheia

~~~C++
// Presente na linha 19 do arquivo window.cpp
ImGui::Begin("Verificador de Triângulos: Lados e Ângulos");

// Presente na linha 78 do arquivo window.cpp
ImGui::End();
~~
Iniciamos uma janela para conter todos os widgets que criarmos. Tudo que estiver entre o Begin e o End, estará dentro da janela.

