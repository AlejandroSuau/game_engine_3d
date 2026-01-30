#include "scene/components/MeshComponent.hpp"

#include "render/Material.hpp"
#include "render/Mesh.hpp"
#include "render/RenderQueue.hpp"
#include "scene/GameObject.hpp"
#include "Engine.hpp"

namespace eng
{

MeshComponent::MeshComponent(
    const std::shared_ptr<Material>& material,
    const std::shared_ptr<Mesh>& mesh) 
    : m_material(material), m_mesh(mesh) {}

void MeshComponent::Update(float deltaTime) {
    if (!m_material || !m_mesh) {
        return;
    }

    RenderCommand command;
    command.material = m_material.get();
    command.mesh = m_mesh.get();
    command.modelMatrix = GetOwner()->GetWorldTransform();

    auto& renderQueue = Engine::GetInstance().GetRenderQueue();
    renderQueue.Submit(command);    
}

void MeshComponent::SetMaterial(const std::shared_ptr<Material>& material) {
    m_material = material;
}

void MeshComponent::SetMesh(const std::shared_ptr<Mesh>& mesh) {
    m_mesh = mesh;
}

}