#ifndef SPACECOLONIZATION_HPP
#define SPACECOLONIZATION_HPP

#include <vector>
#include <unordered_map>
#include <functional>

#include <cstdio>

#include <boost/geometry.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/index/detail/exception.hpp>
#include <boost/geometry/index/parameters.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/functional/hash.hpp>

// Steps:
// - Determine closest tree-node to attraction point
// -- only influence if distance is less than *radius of influence* di
// - Attraction points that affect a tree-node v = S(V)
// -- If S(V) !empty then add a tree node v' and attach by segment (v,v')
// -- v' postioned at D from v, in direction defined as the average 
//      of the normalized vectors toward all sources
// - Check if attraction points should be removed
// -- use a threshold kill distance dk

// Using r-tree to estimate attraction points closest to tree-nodes to decrease search time
// Add <attraction_point, closest_branch> to hash map to avoid branches using the same attraction point [ SIZE_OVERHEAD = sizeof(float) * num_points * 6 ]

// If too slow, multithread (producer/consumer)
// If still too slow, OpenCL / Cuda

// Note that much of this code was made in order to explore C++11 features and boost and doesn't necessarily represent the author's coding style

using boost::geometry::index::rtree;

class SpaceColonization {
  public:
    typedef boost::geometry::model::point<float, 3, boost::geometry::cs::cartesian> point_type;
    typedef boost::geometry::model::multi_point<point_type> point_type_container;

  private:
    point_type_container attraction_points;
    point_type_container seed_points;
    point_type_container branch_points;
    rtree<point_type, boost::geometry::index::linear<100000> > rt;

    double kill_distance;
    double influence_distance;
    double segment_size;

    void buildRTree();
    void findPointsInRadius(const point_type& branch_point, double radius);
    std::vector<point_type> estimatePointsInRadius(const point_type& branch_point, const double radius);

    struct hashfunc {
        std::size_t operator()(point_type const& foo) const {
            using boost::hash_value;
            using boost::hash_combine;

            std::size_t seed = 0;
            hash_combine(seed, hash_value(foo.get<0>()));
            hash_combine(seed, hash_value(foo.get<1>()));
            hash_combine(seed, hash_value(foo.get<2>()));

            return seed;
        };
    };

    struct comparefunc {
        bool operator()(point_type const& foo, point_type const& bar) const {
            if( foo.get<0>() == bar.get<0>() &&
                foo.get<1>() == bar.get<1>() &&
                foo.get<2>() == bar.get<2>() ) {
                return true;
            }
            else return false;
        };
    };

    std::unordered_map<point_type, point_type, hashfunc, comparefunc> point_table;
    std::unordered_map<point_type, point_type, hashfunc, comparefunc> unit_vectors;


    double distance(const point_type& p1, const point_type& p2);
    auto calculateUnitVector(const point_type& branch_point, const point_type& influence_point, const point_type& curr_vector) -> point_type;
    void calculateUnitVectors();
};

#endif //SPACECOLONIZATION_HPP
