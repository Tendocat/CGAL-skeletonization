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


// This example extracts a medially centered skeleton from a given mesh.
int main(int argc, char* argv[])
{
  std::ifstream input((argc>1)?argv[1]:"data/elephant.off");
  Triangle_mesh tmesh;
  input >> tmesh;
  if (!CGAL::is_triangle_mesh(tmesh))
  {
    std::cout << "Input geometry is not triangulated." << std::endl;
    return EXIT_FAILURE;
  }

  Skeleton skeleton;

  CGAL::extract_mean_curvature_flow_skeleton(tmesh, skeleton);

  // Output all the vertices of the skeleton.
  std::ofstream output("skel.obj");
  for(auto v : skeleton.m_vertices)
  {
    const Point& s = v.m_property.point;
    output << "v " << s << "\n";
  }
  output.close();

  return EXIT_SUCCESS;
}

