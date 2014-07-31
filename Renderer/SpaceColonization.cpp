#include "SpaceColonization.hpp"

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <type_traits>

void SpaceColonization::buildRTree() {
    rt.insert(attraction_points);
};

std::vector<SpaceColonization::point_type> SpaceColonization::estimatePointsInRadius(const point_type& branch_point, const double radius) {
    // Estimate points within radius
    point_type min_corner;
    min_corner.set<0>(branch_point.get<0>() - radius);
    min_corner.set<1>(branch_point.get<1>() - radius);
    min_corner.set<2>(branch_point.get<2>() - radius);

    point_type max_corner;
    max_corner.set<0>(branch_point.get<0>() + radius);
    max_corner.set<1>(branch_point.get<1>() + radius);
    max_corner.set<2>(branch_point.get<2>() + radius);

    boost::geometry::model::box<point_type> search_area(min_corner, max_corner);

    std::vector<point_type> points; 
    rt.query(boost::geometry::index::intersects(search_area), std::back_inserter(points));

    return points;
};

double SpaceColonization::distance(const point_type& p1, const point_type& p2) {
    return sqrt(pow(p1.get<0>() * p2.get<0>(), 2.0) + pow(p1.get<1>() * p2.get<1>(), 2.0) + pow(p1.get<2>() * p2.get<2>(), 2.0));
};

// Estimate points close to branch using r-tree
// If it's actually within the radius, attempt to add to a hash table
// On conflicts, compare distance and use closer branch
void SpaceColonization::findPointsInRadius(const point_type& branch_point, const double radius) {
    std::vector<point_type> estimated_points = estimatePointsInRadius(branch_point, radius);
    for(auto elem : estimated_points) {
        if(double dist = (distance(elem, branch_point)) < influence_distance) {
            auto check_success = point_table.emplace(elem, branch_point);
            if(!check_success.second) {
                if(dist < distance(elem, check_success.first->second)) {
                    point_table.erase(check_success.first);
                    point_table.emplace(elem, branch_point);
                }
            }
        }
    }
};

auto SpaceColonization::calculateUnitVector(const point_type& branch_point, const point_type& influence_point, const point_type& curr_vector) -> point_type
{
    point_type unit_vector;
    unit_vector.set<0>(curr_vector.get<0>() + influence_point.get<0>() - branch_point.get<0>());
    unit_vector.set<1>(curr_vector.get<1>() + influence_point.get<1>() - branch_point.get<1>());
    unit_vector.set<2>(curr_vector.get<2>() + influence_point.get<2>() - branch_point.get<2>());

    double magnitude = sqrt(pow(unit_vector.get<0>(), 2) + pow(unit_vector.get<1>(), 2) + pow(unit_vector.get<2>(), 2));

    unit_vector.set<0>(unit_vector.get<0>() / magnitude);
    unit_vector.set<1>(unit_vector.get<1>() / magnitude);
    unit_vector.set<2>(unit_vector.get<2>() / magnitude);
    return unit_vector;
};

void SpaceColonization::calculateUnitVectors() {
    for(auto it = point_table.begin(); it != point_table.end(); ++it) {
        point_type empty(0, 0, 0);
        auto check_success = unit_vectors.emplace(it->second, calculateUnitVector(it->second, it->first, empty));
        if(!check_success.second) {
            point_type unit_vector = calculateUnitVector(it->second, it->first, check_success.first->first);
            unit_vectors.erase(check_success.first);
            unit_vectors.emplace(it->second, unit_vector);
        }
    }
};
