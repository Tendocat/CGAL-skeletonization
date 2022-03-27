#include <Viewer.h>

Viewer::Viewer(const std::string& title, int width, int height, bool show_imgui = true)
{
    // Update scene center and bounds
    pmp::BoundingBox bb = mesh_.bounds();
    set_scene((pmp::vec3)bb.center(), 0.5 * bb.size());

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

    mesh_.set_crease_angle(crease_angle_);
}

void Viewer::process_imgui()
{
    pmp::MeshViewer::process_imgui();

    /* ! STUDENTS TODO ! */
    // Add a combobox and select the mesh to display
}
