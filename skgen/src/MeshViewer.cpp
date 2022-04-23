#include <MeshViewer.hpp>

MeshViewer::MeshViewer(const std::string& title, int width, int height, bool showgui)
: pmp::MeshViewer(title.c_str(), width, height, showgui)
{
    pmp::BoundingBox bb = mesh_.bounds();
    set_scene((pmp::vec3)bb.center(), 0.5f * bb.size());

    _drawSkeleton = false;
    _breakThreshold = (BREAK_THRESHOLD_MIN + BREAK_THRESHOLD_MAX) / 2;
    _metricMode = Metrics::MEAN;

    set_draw_mode("Hidden Line");
    update_mesh();

    mesh_.set_crease_angle(0);
    mesh_.set_specular(0);
    mesh_.set_ambient(0);
    mesh_.set_shininess(0);
    _skeleton.set_crease_angle(0);

    _fbMesh.SetTitle("Choose mesh file");
    _fbMesh.SetTypeFilters({ ".off" });
}

void MeshViewer::process_imgui()
{
    // pmp::MeshViewer::process_imgui();

    if(ImGui::Button("Load mesh"))
        _fbMesh.Open();

    _fbMesh.Display();

    if(_fbMesh.HasSelected())
    {
        mesh_.read(_fbMesh.GetSelected().string());
        load_skeleton(_fbMesh.GetSelected().string());

        pmp::BoundingBox bb = mesh_.bounds();
        set_scene((pmp::vec3)bb.center(), 0.5f * bb.size());

        _fbMesh.ClearSelected();
    }

    ImGui::Checkbox("Draw skeleton", &_drawSkeleton);

    if (ImGui::Button("Use median distance"))
    {
        _metricMode = Metrics::MEDIAN;
        SkeletonManager::evaluate_skeleton(mesh_, _metricMode, (BREAK_THRESHOLD_MAX - _breakThreshold) + BREAK_THRESHOLD_MIN);
    }

    if (ImGui::Button("Use mean distance"))
    {
        _metricMode = Metrics::MEAN;
        SkeletonManager::evaluate_skeleton(mesh_, _metricMode, (BREAK_THRESHOLD_MAX - _breakThreshold) + BREAK_THRESHOLD_MIN);
    }

    if (ImGui::SliderFloat("Break threshold", &_breakThreshold, BREAK_THRESHOLD_MIN, BREAK_THRESHOLD_MAX))
    {
        SkeletonManager::evaluate_skeleton(mesh_, _metricMode, (BREAK_THRESHOLD_MAX - _breakThreshold) + BREAK_THRESHOLD_MIN);
    }

    update_mesh();
}

void MeshViewer::load_skeleton(const std::string &path)
{
    _skeleton = SkeletonManager::compute_skeleton(path.c_str());
    SkeletonManager::dist_mesh_skeleton(mesh_, _skeleton);
    SkeletonManager::evaluate_skeleton(mesh_, _metricMode, (BREAK_THRESHOLD_MAX - _breakThreshold) + BREAK_THRESHOLD_MIN);
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
