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

    fb.SetTitle("Choose mesh file");
    fb.SetTypeFilters({ ".obj" });

}

void MeshViewer::process_imgui()
{
    // pmp::MeshViewer::process_imgui();

    if(ImGui::Button("open file dialog"))
        fb.Open();

    fb.Display();

    if(fb.HasSelected())
    {
        std::cout << "Selected filename" << fb.GetSelected().string() << std::endl;
        mesh_.read(fb.GetSelected().string());
        pmp::BoundingBox bb = mesh_.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5 * bb.size());
        fb.ClearSelected();
    }
    update_mesh();
    // TODO ...
}
