#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <imgui.h>
#include <imfilebrowser.h>

#include "SkeletonManager.hpp"

/**
 * @brief This class overrides 'pmp::MeshViever'
 */
class MeshViewer : public pmp::MeshViewer
{
    private:
        inline static const float BREAK_THRESHOLD_MIN = 0.6f;
        inline static const float BREAK_THRESHOLD_MAX = 1.4f;

        // file browser linked to the mesh
        ImGui::FileBrowser _fbMesh;

        // skeleton mesh
        pmp::SurfaceMeshGL _skeleton;

        // whether the skeleton is drawn
        bool _drawSkeleton;

        // break threshold
        float _breakThreshold;

        // the metric used to compute distance
        Metrics _metricMode;

    public:
        MeshViewer() = delete;
        MeshViewer(const std::string& title, int width, int height, bool showgui = true);

        /**
         * @brief MeshViewer overrided loop.
         */
        void process_imgui();

        /**
         * @brief Loads a mesh and compute its skeleton.
         */
        void load_mesh(const std::string &path);

        /**
         * @brief Loads a skeleton mesh.
         */
        void load_skeleton(const std::string &path);

        /**
         * @brief Updates the mesh according to the user inputs.
         */
        void update_mesh() override;

        /**
         * @brief Draws the mesh according to the current drawing method.
         */
        void draw(const std::string &draw_mode) override;
};
