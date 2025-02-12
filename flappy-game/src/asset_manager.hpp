#pragma once
#include "core.hpp"

#include <unordered_map>

namespace flappy
{
  template<typename Key, typename Type>
  class asset_manager
  {
  public:
    using key_type      = Key;
    using mapped_type   = Type;
    using registry_type = std::unordered_map<key_type, mapped_type>;
  
  public:
    template<typename...Args>
    static mapped_type& load(const key_type& key, Args&&... args)
    {
      if(auto it = find(key); it != m_registry.end())
      {
        return it->second;
      }

      return m_registry.emplace(std::make_pair( key, std::forward<Args>(args)...)).first->second;
    }

    static auto find(const key_type& key)
    {
      return m_registry.find(key);
    }

    static mapped_type& get(const key_type& key)
    {
      if (auto it = find(key); it != m_registry.end())
      {
        return it->second;
      }
      return nullptr;
    }

  private:
    static inline registry_type m_registry;
  };
}