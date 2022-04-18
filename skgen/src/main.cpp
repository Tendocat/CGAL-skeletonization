#include <iostream>

#include <MeshViewer.hpp>
#include <SimpleCommandLine.h>
#include <string>

int main(int argc, char** argv)
{
    cli::Parser parser(argc, argv);

    parser.set_optional<std::string>("p", "path", std::string(), "Path to the requested mesh");
    parser.set_optional<std::string>("s", "skeleton", std::string(), "Path to mesh's skeleton");
    parser.set_optional<cli::NumericalBase<int,10>>("y", "height", 800, "Height of the window");
    parser.set_optional<cli::NumericalBase<int, 10>>("x", "width", 800, "Width of the window");
    parser.run_and_exit_if_error(); // Exit and print on std::cerr


    std::string mesh = parser.get<std::string>("p");
    std::string skel = parser.get<std::string>("s");

    auto w = parser.get<cli::NumericalBase<int, 10>>("x");
    auto h = parser.get<cli::NumericalBase<int, 10>>("y");

    MeshViewer viewer("SKgen", w.value, h.value);
    if (!mesh.empty())
        viewer.load_mesh(mesh.c_str());
    if (!skel.empty())
        viewer.load_skeleton(skel.c_str());
    viewer.run();

    return 0;
}
