#include "render/RenderQueue.hpp"

#include "render/Mesh.hpp"
#include "render/Material.hpp"
#include "graphics/GraphicsAPI.hpp"
#include "graphics/ShaderProgram.hpp"

namespace eng
{

void RenderQueue::Submit(const RenderCommand& command)
{
    m_commands.push_back(command);
}

void RenderQueue::Draw(
    GraphicsAPI& graphicsAPI,
    const CameraData& cameraData,
    const std::vector<LightData>& lights) {
    for (const auto& command : m_commands) {
        graphicsAPI.BindMaterial(command.material);
        auto* shaderProgram = command.material->GetShaderProgram();
        shaderProgram->SetUniform("uModel", command.modelMatrix);
        shaderProgram->SetUniform("uView", cameraData.viewMatrix);
        shaderProgram->SetUniform("uProjection", cameraData.projectionMatrix);
        shaderProgram->SetUniform("uCameraPos", cameraData.position);
        if (!lights.empty()) {
            auto& light = lights[0];
            shaderProgram->SetUniform("uLight.color", light.color);
            shaderProgram->SetUniform("uLight.direction", glm::normalize(-light.position));
        }

        graphicsAPI.BindMesh(command.mesh);
        graphicsAPI.DrawMesh(command.mesh);
        graphicsAPI.UnbindMesh(command.mesh);
    }

    m_commands.clear();
}

}