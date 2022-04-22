#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/extract_mean_curvature_flow_skeleton.h>

#include <fstream>


typedef CGAL::Simple_cartesian<double>                        Kernel;
typedef Kernel::Point_3                                       Point;
typedef CGAL::Surface_mesh<Point>                             Triangle_mesh;

typedef boost::graph_traits<Triangle_mesh>::vertex_descriptor    vertex_descriptor;

typedef CGAL::Mean_curvature_flow_skeletonization<Triangle_mesh> Skeletonization;
typedef Skeletonization::Skeleton                             Skeleton;

typedef Skeleton::vertex_descriptor                           Skeleton_vertex;

// This example extracts a medially centered skeleton from a given mesh.
int main(int argc, char* argv[])
{
  if (argc <= 1)
  {
    std::cout << "Arg missing" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream input(argv[1]);
  Triangle_mesh tmesh;
  
  if(!CGAL::read_off(input, tmesh))
  {
    std::cout << "Input error." << std::endl;
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
  for(Skeleton_vertex v : CGAL::make_range(vertices(skeleton)))
  {
    output << "v " << skeleton[v].point << "\n";
  }
  output.close();
  
  return EXIT_SUCCESS;
}

