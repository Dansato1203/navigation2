// Copyright (c) 2023, Samsung Research America
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NAV2_ROUTE__ROUTE_PLANNER_HPP_
#define NAV2_ROUTE__ROUTE_PLANNER_HPP_

#include <string>
#include <limits>
#include <memory>
#include <vector>
#include <mutex>
#include <algorithm>

#include "nav2_route/types.hpp"
#include "nav2_route/utils.hpp"
#include "nav2_route/edge_scorer.hpp"
#include "nav2_core/route_exceptions.hpp"

namespace nav2_route
{
/**
 * @class nav2_route::RoutePlanner
 * @brief An optimal planner to compute a route from a start to a goal in an arbitrary graph
 */
class RoutePlanner
{
public:
  /**
   * @brief A constructor for nav2_route::RoutePlanner
   */
  RoutePlanner() = default;

  /**
   * @brief A destructor for nav2_route::RoutePlanner
   */
  ~RoutePlanner() = default;

  /**
   * @brief Configure the route planner, get parameters
   * @param node Node object to get parametersfrom
   */
  void configure(nav2_util::LifecycleNode::SharedPtr node);

  /**
   * @brief Find the route from start to goal on the graph
   * @param graph Graph to search
   * @param start Start index in the graph of the start node
   * @param goal Goal index in the graph of the goal node
   * @return Route object containing the navigation graph route
   */
  Route findRoute(Graph & graph, unsigned int start, unsigned int goal);

protected:
  /**
   * @brief Reset the search state of the graph nodes
   * @param graph Graph to reset
   */
  inline void resetSearchStates(Graph & graph);

  /**
   * @brief Dikstra's algorithm search on the graph
   * @param graph Graph to search
   * @param start Start Node pointer
   * @param goal Goal node pointer
   */
  void findShortestGraphTraversal(Graph & graph, const NodePtr start, const NodePtr goal);

  /**
   * @brief Gets the traversal cost for an edge using edge scorers
   * @param edge Edge pointer to find traveral cost for
   * @param travel cost
   * @return if this edge is valid for search
   */
  inline bool getTraversalCost(const EdgePtr edge, float & score);

  /**
   * @brief Gets the next node in the priority queue for search
   * @return Next node pointer in queue with cost
   */
  inline NodeElement getNextNode();

  /**
   * @brief Adds a node to the priority queue for search
   * @param cost Priority level
   * @param node Node pointer to insert
   */
  inline void addNode(const float cost, const NodePtr node);

  /**
   * @brief Gets the edges from a given node
   * @param node Node pointer to check
   * @return A vector of edges that the node contains
   */
  inline EdgeVector & getEdges(const NodePtr node);

  /**
   * @brief Clears the priority queue
   */
  inline void clearQueue();

  /**
   * @brief Checks if a given node is the goal node
   * @param node Node to check
   * @return bool If this node is the goal
   */
  inline bool isGoal(const NodePtr node);

  int max_iterations_{0};
  unsigned int goal_id_{0};
  NodeQueue queue_;
  std::unique_ptr<EdgeScorer> edge_scorer_;
};

}  // namespace nav2_route

#endif  // NAV2_ROUTE__ROUTE_PLANNER_HPP_