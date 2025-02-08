#pragma once

#include<memory>
#include<cstdint>
#include<cassert>

namespace flappy
{
  template<typename T, typename Deleter = std::default_delete<T>>
  using uptr = std::unique_ptr<T, Deleter>;
}