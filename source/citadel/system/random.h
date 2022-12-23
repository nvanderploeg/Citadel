//
//  random.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-23.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
//  TODO: this whole Random thing should probably be revisited at some point.
//
#pragma once

#include <random>
#include <chrono>

namespace citadel
{

    class Random
    {
    protected:
        std::mt19937 m_RandomGenerator;

    protected:
        Random()
            : m_RandomGenerator(std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count()))
        { /* empty */ }
        Random(double seed)
            : m_RandomGenerator(std::mt19937(seed))
        { /* empty */ }

    public:
        virtual ~Random() = default;
    };

    class RandomInt : public Random
    {
    private:
        std::uniform_int_distribution<> dist;

    public:
        RandomInt(int lower_bound, int upper_bound)
            : dist(lower_bound, upper_bound)
        { /* empty */ }
        RandomInt(int lower_bound, int upper_bound, double seed)
            : Random(seed)
            , dist(lower_bound, upper_bound)
        { /* empty */ }

        int operator ()() { return dist(m_RandomGenerator); }
    };

    template <class T>
    class RandomReal : public Random
    {
    private:
        std::uniform_real_distribution<> dist;

    public:
        RandomReal(T lower_bound, T upper_bound)
            : dist(lower_bound, upper_bound)
        { /* empty */ }
        RandomReal(T lower_bound, T upper_bound, double seed)
            : Random(seed)
            , dist(lower_bound, upper_bound)
        { /* empty */ }

        T operator ()() { return static_cast<T>(dist(m_RandomGenerator)); }
    };

} // namespace citadel