#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Mean_curvature_flow_skeletonization.h>

#include <fstream>
#include <filesystem>

typedef CGAL::Simple_cartesian<double>                        Kernel;
typedef Kernel::Point_3                                       Point;
typedef CGAL::Surface_mesh<Point>                             Triangle_mesh;

typedef CGAL::Mean_curvature_flow_skeletonization<Triangle_mesh> Skeletonization;
typedef Skeletonization::Skeleton                             Skeleton;

typedef Skeleton::vertex_descriptor                           Skeleton_vertex;

namespace fs = std::filesystem;

// more detailed version of the skeleton extraction
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

	if (ext == std::string(".off"))
	{
		if (!read_off(input, tmesh))
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

	if (!CGAL::is_triangle_mesh(tmesh))
	{
		std::cout << "Input geometry is not triangulated." << std::endl;
		return EXIT_FAILURE;
	}

	Skeleton skeleton;
	Skeletonization mcs(tmesh);

	// 1. Contract the mesh by mean curvature flow.
	mcs.contract_geometry();

	// 2. Collapse short edges and split bad triangles.
	mcs.collapse_edges();
	mcs.split_faces();

	// 3. Fix degenerate vertices.
	mcs.detect_degeneracies();

	// Perform the above three steps in one iteration.
	mcs.contract();

	// Iteratively apply step 1 to 3 until convergence.
	mcs.contract_until_convergence();

	// Convert the contracted mesh into a curve skeleton and
	// get the correspondent surface points
	mcs.convert_to_skeleton(skeleton);

	// Output all the vertices of the skeleton.
	std::ofstream output("skel.obj");
	for (Skeleton_vertex v : CGAL::make_range(vertices(skeleton)))
	{
		output << "v " << skeleton[v].point << "\n";
	}
	output.close();

	return EXIT_SUCCESS;
}
