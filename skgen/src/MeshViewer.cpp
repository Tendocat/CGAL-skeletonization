#include <MeshViewer.hpp>

MeshViewer::MeshViewer(const std::string& title, int width, int height, bool showgui)
: pmp::MeshViewer(title.c_str(), width, height, showgui)
{
    pmp::BoundingBox bb = mesh_.bounds();
    set_scene((pmp::vec3)bb.center(), 0.5f * bb.size());

    _drawSkeleton = false;
    _breakThreshold = 1.0f;

    set_draw_mode("Hidden Line");
    update_mesh();

    mesh_.set_crease_angle(crease_angle_);
    _skeleton.set_crease_angle(crease_angle_);

    _fbMesh.SetTitle("Choose mesh file");
    _fbMesh.SetTypeFilters({ ".obj", ".stl", ".ply", ".off" });

    _fbSkel.SetTitle("Choose mesh file");
    _fbSkel.SetTypeFilters({ ".obj", ".stl", ".ply", ".off" });
}

void MeshViewer::process_imgui()
{
    // pmp::MeshViewer::process_imgui();

    if(ImGui::Button("Load mesh"))
        _fbMesh.Open();

    if (ImGui::Button("Load skeleton"))
        _fbSkel.Open();

    _fbMesh.Display();
    _fbSkel.Display();

    if(_fbMesh.HasSelected())
    {
        mesh_.read(_fbMesh.GetSelected().string());

        //_skeleton = Skeleton::compute_skeleton(_fbMesh.GetSelected().string());

        pmp::BoundingBox bb = mesh_.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5f * bb.size());

        _fbMesh.ClearSelected();
    }

    if (_fbSkel.HasSelected())  // MOCK : until 'Skeleton::compute_skeleton()' is completed ...
    {
        _skeleton.read(_fbSkel.GetSelected().string());

        pmp::BoundingBox bb = _skeleton.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5f * bb.size());

        _fbSkel.ClearSelected();
    }

    ImGui::Checkbox("Draw skeleton", &_drawSkeleton);

    if (ImGui::Button("Evaluate skeleton"))
    {
        SkeletonManager::dist_mesh_skeleton(mesh_, _skeleton);
        SkeletonManager::evaluate_skeleton(mesh_, Metrics::MEAN, _breakThreshold);
    }

    if (ImGui::SliderFloat("Break ratio", &_breakThreshold, 0.6f, 1.4f))
    {
        SkeletonManager::evaluate_skeleton(mesh_, Metrics::MEAN, _breakThreshold);
    }

    update_mesh();
}

void MeshViewer::draw(const std::string &draw_mode)
{
    if (_drawSkeleton)
    {
        _skeleton.draw(projection_matrix_, modelview_matrix_, draw_mode);
    }
    else
    {
        pmp::MeshViewer::draw(draw_mode);
    }
}

void MeshViewer::update_mesh()
{
    if (_drawSkeleton)
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
