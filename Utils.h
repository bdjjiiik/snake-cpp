#pragma once

#include "Utils.h"

template <typename Derived>
class Singleton {
 public:
  static Derived& GetInstance()
  {
    static Derived instance;
    return instance;
  }

  Singleton() = default;
  ~Singleton() = default;

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  Singleton(Singleton&&) noexcept = delete;
  Singleton& operator=(Singleton&&) noexcept = delete;
};