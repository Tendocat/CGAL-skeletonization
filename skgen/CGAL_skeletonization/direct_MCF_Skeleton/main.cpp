#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/extract_mean_curvature_flow_skeleton.h>
#include <CGAL/IO/io.h>

#include <fstream>
#include <filesystem>

typedef CGAL::Simple_cartesian<double>                        Kernel;
typedef Kernel::Point_3                                       Point;
typedef CGAL::Surface_mesh<Point>                             Triangle_mesh;

typedef boost::graph_traits<Triangle_mesh>::vertex_descriptor    vertex_descriptor;

typedef CGAL::Mean_curvature_flow_skeletonization<Triangle_mesh> Skeletonization;
typedef Skeletonization::Skeleton                             Skeleton;

typedef Skeleton::vertex_descriptor                           Skeleton_vertex;

namespace fs = std::filesystem;

// This example extracts a medially centered skeleton from a given mesh.
int main(int argc, char* argv[])
{
	Triangle_mesh tmesh;

	if (argc <= 1)
	{
		std::cerr << "Arg missing" << std::endl;
		return EXIT_FAILURE;
	}

	fs::path p = fs::path(argv[1]);

	if (not fs::exists(p))
	{
		std::cerr << "Input error." << std::endl;
		return EXIT_FAILURE;
	}

	std::string ext = p.extension().string();

	std::ifstream input(argv[1]);

	if (ext == std::string("off"))
	{
		if (!read_OFF(input, tmesh))
		{
			std::cerr << "Input error." << std::endl;
			return EXIT_FAILURE;
		}
	}
	else if (ext == std::string("obj"))
	{
		if (!read_OBJ(input, tmesh))
		{
			std::cerr << "Input error." << std::endl;
			return EXIT_FAILURE;
		}
	}
	else if (ext == std::string("stl"))
	{
		if (!read_STL(input, tmesh))
		{
			std::cerr << "Input error." << std::endl;
			return EXIT_FAILURE;
		}
	}
	else
	{
		std::cerr << "Unsupported file format." << std::endl;
		return EXIT_FAILURE;
	}



	if (tmesh.number_of_vertices() == 0)
	{
		std::cout << "No Input geometry." << std::endl;
		return EXIT_FAILURE;
	}

	if (!CGAL::is_triangle_mesh(tmesh))
	{
		std::cout << "Input geometry is not triangulated." << std::endl;
		return EXIT_FAILURE;
	}

	Skeleton skeleton;

	CGAL::extract_mean_curvature_flow_skeleton(tmesh, skeleton);

	// Output all the vertices of the skeleton.
	std::ofstream output("skel.obj");
	for (Skeleton_vertex v : CGAL::make_range(vertices(skeleton)))
	{
		output << "v " << skeleton[v].point << "\n";
	}
	output.close();

	return EXIT_SUCCESS;
}

