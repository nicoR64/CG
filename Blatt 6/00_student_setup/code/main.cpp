#include "scene/Camera.h"
#include "scene/Lights/AmbientLight.h"
#include "scene/Lights/PointLight.h"
#include "scene/Scene.h"
#include "scene/Objects/Container.h"
#include "scene/Objects/Cube.h"
#include "scene/Objects/Triangle.h"
#include "scene/Objects/Sphere.h"
#include "Rasterizer.h"

#include "image/ImageViewer.h"

#include <iostream>
#include <memory>
#include <vector>

cg::Scene createTriangle()
{
    cg::Scene scene("Triangle");

    // Create test scene with a single triangle
    scene.addObject(std::make_shared<cg::TestTriangle>());
    scene.addLight(std::make_shared<cg::AmbientLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f));

    return scene;
}

cg::Scene createCube()
{
    cg::Scene scene("Cube");

    // Create cube
    auto cube = std::make_shared<cg::Cube>();
    cube->Translate(cg::vec3(0.0f, -1.0f, 5.0f));
    cube->Rotate(0.0f, 45.0f, 0.0f);
    scene.addObject(cube);

    // Create point light
    auto pointLight = std::make_shared<cg::PointLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
    pointLight->Translate(cg::vec3(-2.0f, 1.0f, 0.0f));
    scene.addLight(pointLight);

    // Create ambient light
    auto ambient = std::make_shared<cg::AmbientLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
    scene.addLight(ambient);

    return scene;
}

cg::Scene createSphere()
{
    cg::Scene scene("Sphere");

    // Create sphere
    auto sphere = std::make_shared<cg::Sphere>(1.0f);
    sphere->Translate(cg::vec3(0.0f, 0.0f, 5.0f));
    sphere->Rotate(30.0f, 20.0f, 10.0f);
    scene.addObject(sphere);

    // Create point light
    auto pointLight = std::make_shared<cg::PointLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
    pointLight->Translate(cg::vec3(-2.0f, 1.0f, 0.0f));
    scene.addLight(pointLight);

    // Create ambient light
    auto ambient = std::make_shared<cg::AmbientLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
    scene.addLight(ambient);

    return scene;
}

cg::Scene createComplexScene()
{
    cg::Scene scene("Complex Scene");

    // Create object from two spheres and a cube
    auto cube = std::make_shared<cg::Cube>(0.5f, cg::Color(1.0f, 1.0f, 1.0f, 1.0f));

    auto sphere1 = std::make_shared<cg::Sphere>(0.25f, 10, 20, cg::Color(1.0f, 1.0f, 0.0f, 1.0f));
    sphere1->Translate(cg::vec3(-0.5f, 0.0f, 0.0f));

    auto sphere2 = std::make_shared<cg::Sphere>(0.25f, 25, 50, cg::Color(0.0f, 1.0f, 1.0f, 1.0f));
    sphere2->Translate(cg::vec3(0.5f, 0.0f, 0.0f));

    // Create object container
    auto object1 = std::make_shared<cg::Container>();
    object1->addObject(cube);
    object1->addObject(sphere1);
    object1->addObject(sphere2);

    object1->Translate(cg::vec3(0.0f, 0.0f, 2.5f));

    scene.addObject(object1);

    // Create copies and transform them
    auto object2 = std::make_shared<cg::Container>(*object1.get());
    object2->Translate(cg::vec3(-2.0f, 0.0f, 1.0f));
    object2->Rotate(0.0f, 90.0f, 0.0f);

    auto object3 = std::make_shared<cg::Container>(*object1.get());
    object3->Translate(cg::vec3(2.5f, 0.5f, 1.0f));
    object3->Rotate(0.0f, 45.0f, 45.0f);

    scene.addObject(object2);
    scene.addObject(object3);

    // Create point light
    auto pointLight1 = std::make_shared<cg::PointLight>(cg::Color(0.28f, 1.0f, 1.0f, 1.0f), 7.0f);
    pointLight1->Translate(cg::vec3(-2.0f, 1.0f, 0.0f));
    scene.addLight(pointLight1);

    // Create point light
    auto pointLight2 = std::make_shared<cg::PointLight>(cg::Color(0.7f, 0.0f, 0.0f, 1.0f), 7.0f);
    pointLight2->Translate(cg::vec3(2.0f, -1.0f, 0.0f));
    scene.addLight(pointLight2);

    // Create ambient light
    auto ambient = std::make_shared<cg::AmbientLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
    scene.addLight(ambient);

    return scene;
}

cg::Scene createOwnScene()
{
    cg::Scene scene("Own Scene");

    ///////
    // TODO
    // Create your own scene.
    // This task is optional, but the best scenes will be presented in the tutorial.
    
    // Zentrale "Sonne" (Gelb, selbstleuchtend simuliert durch helle Farbe)
    auto sun = std::make_shared<cg::Sphere>(0.8f, 30, 30, cg::Color(1.0f, 0.8f, 0.0f, 1.0f));
    scene.addObject(sun);

    // "Erde" (Blau)
    auto earth = std::make_shared<cg::Sphere>(0.4f, 20, 20, cg::Color(0.0f, 0.0f, 1.0f, 1.0f));
    earth->Translate(cg::vec3(2.0f, 0.0f, 0.0f)); 
    scene.addObject(earth);

    // "Mond" (Grau), relativ zur Erde
    auto moon = std::make_shared<cg::Sphere>(0.15f, 10, 10, cg::Color(0.7f, 0.7f, 0.7f, 1.0f));
    moon->Translate(cg::vec3(2.6f, 0.0f, 0.0f)); // Ein Stück weiter als die Erde
    scene.addObject(moon);

    // Ein Würfel als "Raumstation"
    auto station = std::make_shared<cg::Cube>(0.2f, cg::Color(0.8f, 0.1f, 0.1f, 1.0f));
    station->Translate(cg::vec3(-1.5f, 1.0f, 0.5f));
    station->Rotate(45.0f, 45.0f, 0.0f);
    scene.addObject(station);

    // Lichtquelle in der Sonne (Point Light)
    auto sunLight = std::make_shared<cg::PointLight>(cg::Color(1.0f, 0.95f, 0.8f, 1.0f), 15.0f);
    sunLight->Translate(cg::vec3(0.0f, 0.0f, 0.0f)); // Position in der Sonne
    scene.addLight(sunLight);

    // Schwaches Ambient Light für den Weltraum
    auto ambient = std::make_shared<cg::AmbientLight>(cg::Color(1.0f, 1.0f, 1.0f, 1.0f), 0.1f);
    scene.addLight(ambient);

    return scene;
}

int main(const int argc, const char** argv)
{
    std::cout << "Uni Stuttgart - CG Exercise" << std::endl;

    // Create different scenes
    std::vector<cg::Scene> scenes;
    scenes.push_back(createTriangle());
    scenes.push_back(createCube());
    scenes.push_back(createSphere());
    scenes.push_back(createComplexScene());
    scenes.push_back(createOwnScene());

    // Create rasterizer for creating the images
    cg::Rasterizer rasterizer(cg::defaultCamera(), scenes, cg::Rasterizer::FILLED, 1600, 900);

    // Start image viewer for output rendering
    cg::ImageViewer image_viewer(rasterizer);
    image_viewer.run();

    return 0;
}