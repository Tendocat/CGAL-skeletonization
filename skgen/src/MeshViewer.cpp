#include <MeshViewer.hpp>

MeshViewer::MeshViewer(const std::string& title, int width, int height, bool showgui) : 
    pmp::MeshViewer(title.c_str(),
                    width, 
                    height,
                    showgui)
{

    // Update scene center and bounds
    pmp::BoundingBox bb = mesh_.bounds();
    set_scene((pmp::vec3)bb.center(), 0.5 * bb.size());

    _isDrawingSkeleton = false;

    // Set draw mode
    if (mesh_.n_faces() == 0)
        set_draw_mode("Points");
    else
        set_draw_mode("Hidden Line");

    update_mesh();
    set_draw_mode("Hidden Line");

    mesh_.set_crease_angle(crease_angle_);
    _skeleton.set_crease_angle(crease_angle_);

    _fbMesh.SetTitle("Choose mesh file");
    _fbMesh.SetTypeFilters({ ".obj", ".stl", ".ply" });

    _fbSkel.SetTitle("Choose mesh file");
    _fbSkel.SetTypeFilters({ ".obj", ".stl", ".ply" });
}

void MeshViewer::process_imgui()
{
    // pmp::MeshViewer::process_imgui();
    if(ImGui::Button("Load mesh ..."))
        _fbMesh.Open();

    if (ImGui::Button("Load skeleton ..."))
        _fbSkel.Open();

    _fbMesh.Display();
    _fbSkel.Display();

    if(_fbMesh.HasSelected())
    {
        mesh_.read(_fbMesh.GetSelected().string());
        pmp::BoundingBox bb = mesh_.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5 * bb.size());
        _fbMesh.ClearSelected();
    }

    if (_fbSkel.HasSelected())
    {
        _skeleton.read(_fbSkel.GetSelected().string());
        pmp::BoundingBox bb = _skeleton.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5 * bb.size());
        _fbSkel.ClearSelected();
    }

    ImGui::Checkbox("Draw skeleton", &_isDrawingSkeleton);

    if (ImGui::Button("Evaluate skeleton"))
    {
        evaluate_skeleton();
    }

    update_mesh();
    // TODO ...
}

void MeshViewer::draw(const std::string& draw_mode)
{
    if (_isDrawingSkeleton)
        _skeleton.draw(projection_matrix_, modelview_matrix_, draw_mode);
    else
        pmp::MeshViewer::draw(draw_mode);
}

void MeshViewer::update_mesh()
{
    if (_isDrawingSkeleton)
    {
        _skeleton.set_crease_angle(crease_angle_);
        _skeleton.update_opengl_buffers();
    }
    else
    {
        pmp::MeshViewer::update_mesh();
    }
}

void MeshViewer::load_skeleton(const char* path)
{
    _skeleton.read(path);
}

/* algo de colorimétrie-évaluation du squelette : à déplacer dans une classe appropriée */

float MeshViewer::dist(const pmp::Point &p1, const pmp::Point &p2)
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}

float MeshViewer::dist_to_skeleton(const pmp::Point &p1)
{
    float curr_dist, min_dist = std::numeric_limits<float>::max();

    for (auto const &v : _skeleton.vertices())
    {
        if ((curr_dist = dist(p1, _skeleton.position(v))) < min_dist)
            min_dist = curr_dist;
        
        // amélioration : vérifier que le distance mesurée est bien interne au maillage et ne passe pas par l'extérieur (le cas est très rare, mais peut sûrement arriver)
    }
    return min_dist;
}

void MeshViewer::evaluate_skeleton()
{
    if (mesh_.n_vertices() == 0 || _skeleton.n_vertices() == 0)
    {
        std::cout << "Please load mesh and skeleton" << std::endl;
        return;
    }

    float sum = 0;
    float cpt = 0;

    auto vdist = mesh_.vertex_property<float>("d:dist");

    for (auto const &v : mesh_.vertices())
    {
        vdist[v] = dist_to_skeleton(mesh_.position(v));
        sum += vdist[v];
        cpt++;
    }

    float mean = sum / cpt; // la moyenne est une mesure statistique comme une autre, on pourrait utiliser la médiane et même encore d'autres métriques
    float ratio = 0;

    auto vcolor = mesh_.vertex_property<pmp::Color>("v:color");

    for (auto const &v : mesh_.vertices())
    {
        ratio = std::min(vdist[v] / mean, 1.0f);
        vcolor[v] = (1 - ratio) * pmp::Color(1, 0, 0) + ratio * pmp::Color(1, 1, 1);
    }

    update_mesh();
}
