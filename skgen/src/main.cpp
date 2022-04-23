#include <iostream>
#include <string>

#include <SimpleCommandLine.h>
#include "MeshViewer.hpp"

int main(int argc, char** argv)
{
    cli::Parser parser(argc, argv);
    
    parser.set_optional<std::string>("p", "path", std::string(), "Path to the requested mesh");
    //parser.set_optional<std::string>("s", "skeleton", std::string(), "Path to mesh's skeleton");
    parser.set_optional<cli::NumericalBase<int,10>>("y", "height", 800, "Height of the window");
    parser.set_optional<cli::NumericalBase<int, 10>>("x", "width", 800, "Width of the window");
    parser.run_and_exit_if_error(); // exit and print on std::cerr
    
    // set program path
    std::error_code ec;
    std::filesystem::path p("/proc/self/exe");
    SkeletonManager::programPath = std::filesystem::read_symlink(p,ec).parent_path();

    std::string mesh = parser.get<std::string>("p");
    //std::string skel = parser.get<std::string>("s");

    auto w = parser.get<cli::NumericalBase<int, 10>>("x");
    auto h = parser.get<cli::NumericalBase<int, 10>>("y");

    MeshViewer viewer("SKgen", w.value, h.value);

    if (!mesh.empty())
    {
        viewer.load_mesh(mesh.c_str());
    }

    freopen("/dev/null", "w", stderr); // disable stderr

    viewer.run();

    return 0;
}
