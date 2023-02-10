#pragma once

#include <typeindex>
#include <unordered_map>
#include <any>

#include "./components/texture.h"

namespace kat {

    using Resource     = std::any;
    using ResourceType = const char *;
    using ResourceName = std::string; 
    using ResourceMap  = std::unordered_map<ResourceName, Resource>;
    using ResourceMapRegistry = std::unordered_map<ResourceType, ResourceMap>;

    // Please consider using copyable resources only.
    // Theses resources are not thread safe and should be used only in the main thread.
    // If you need to use them in other threads, please consider using a mutex.
    // When you are using copyable resources, make sure that the resource is not destroyed before the copy is used.
    // It is generally a good idea to use shared resources.
    // For example, the Texture class of the engine has a single pointer to a sf::Texture.
    // This pointer is handeled like a shared pointer.
    // This means that the texture is not destroyed until the last copy of the texture is destroyed.
    // This is a good idea because the texture is used in multiple places.
    class ResourceManager {
    private:
        /**
         * @brief The registry of all resources.
         */
        ResourceMapRegistry m_registry;

    public:
        /**
         * @brief Default constructor, it will setup every trivial resource.
         */
        ResourceManager() {
            const auto typid = typeid(Texture).name();
            m_registry[typid] = ResourceMap();
            m_registry[typid].emplace("default", std::any(Texture()));
        }

        /**
         * @brief Destructor.
         */
        ~ResourceManager() = default;

        /**
         * @brief Add a resource to the registry.
         * @param name The name of the resource.
         * @param resource The resource to add.
         */
        template<typename T>
        void addResource(const ResourceName& name, const T& resource) {
            const auto typid = typeid(T).name();
            if (m_registry.find(typid) == m_registry.end())
                m_registry[typid] = ResourceMap();
            m_registry[typid].emplace(name, std::any(resource));
        }

        /**
         * @brief Add a resource to the registry.
         * @param name The name of the resource.
         * @param resource The resource to add.
         */
        template<typename T>
        void addResource(const ResourceName& name, T&& resource) {
            const auto typid = typeid(T).name();
            if (m_registry.find(typid) == m_registry.end())
                m_registry[typid] = ResourceMap();
            m_registry[typid].emplace(name, std::any(std::move(resource)));
        }

        /**
         * @brief Get a resource from the registry.
         * @param name The name of the resource.
         * @return The resource.
         */
        template<typename T>
        T &getResource(const ResourceName& name) {
            const auto typid = typeid(T).name();
            const auto type = m_registry.find(typid);
            if (type == m_registry.end())
                throw std::runtime_error("Resource type not found.");
            const auto resource = type->second.find(name);
            if (resource == type->second.end())
                throw std::runtime_error("Resource not found.");
            return std::any_cast<T&>(resource->second);
        }

        /**
         * @brief Get a resource from the registry.
         * @param name The name of the resource.
         * @return The resource.
         */
        template<typename T>
        const T &getResource(const ResourceName& name) const {
            const auto typid = typeid(T).name();
            const auto type = m_registry.find(typid);
            if (type == m_registry.end())
                throw std::runtime_error("Resource type not found.");
            const auto resource = type->second.find(name);
            if (resource == type->second.end())
                throw std::runtime_error("Resource not found.");
            return std::any_cast<const T&>(resource->second);
        }

        /**
         * @brief Clear the registry.
         */
        void clear() {
            m_registry.clear();
        }
    };
}