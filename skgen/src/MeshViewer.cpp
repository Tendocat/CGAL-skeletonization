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
    {
        set_draw_mode("Points");
    }
    else
    {
        set_draw_mode("Hidden Line");
    }

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
    {
        _fbSkel.Open();
    }

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

    ImGui::Checkbox("Draw skeleton ?", &_isDrawingSkeleton);
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

