#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

int demo()
{
  //? GLM tests
  glm::vec3 v1(1.0f, 2.0f, 3.0f);
  glm::vec3 v2(4.0f, 5.0f, 6.0f);

  std::cout << v1.x << std::endl;
  std::cout << glm::dot(v1, v2) << std::endl;
}