from collections import deque
import heapq
import networkx as nx
import matplotlib.pyplot as plt


romania_map = {
    "Arad": {"Zerind": 75, "Sibiu": 140, "Timisoara": 118},
    "Bucharest": {"Urziceni": 85, "Pitesti": 101, "Giurgiu": 90, "Fagaras": 211},
    "Craiova": {"Drobeta": 120, "Rimnicu": 146, "Pitesti": 138},
    "Drobeta": {"Mehadia": 75},
    "Eforie": {"Hirsova": 86},
    "Fagaras": {"Sibiu": 99},
    "Hirsova": {"Urziceni": 98},
    "Iasi": {"Vaslui": 92, "Neamt": 87},
    "Lugoj": {"Timisoara": 111, "Mehadia": 70},
    "Oradea": {"Zerind": 71, "Sibiu": 151},
    "Pitesti": {"Rimnicu": 97},
    "Rimnicu": {"Sibiu": 80},
    "Urziceni": {"Vaslui": 142}
}

heuristic = {
    "Arad": 366,
    "Bucharest": 0,
    "Craiova": 160,
    "Drobeta": 242,
    "Eforie": 161,
    "Fagaras": 176,
    "Giurgiu": 77,
    "Hirsova": 151,
    "Iasi": 226,
    "Lugoj": 244,
    "Mehadia": 241,
    "Neamt": 234,
    "Oradea": 380,
    "Pitesti": 100,
    "Rimnicu": 193,
    "Sibiu": 253,
    "Timisoara": 329,
    "Urziceni": 80,
    "Vaslui": 199,
    "Zerind": 374
}


def undirect_graph(parametr):
    graph = {}
    for city, neighbors in parametr.items():
        graph.setdefault(city, {})
        for neighbor, cost in neighbors.items():
            graph.setdefault(city, {})[neighbor] = cost
            graph.setdefault(neighbor, {})[city] = cost
    return graph


graph = undirect_graph(romania_map)


def greedy(graph, src, goal, h):
    pq = [(h[src], src, [src], 0)]
    visited = set()
    expanded = []
    total_expanded_cost = 0

    while pq:
        h_cost, node, path, g_cost = heapq.heappop(pq)

        if node in visited:
            continue

        visited.add(node)
        expanded.append((node, g_cost, h[node]))
        total_expanded_cost += g_cost

        if node == goal:
            return {
                "algorithm": "Greedy",
                "path": path,
                "path_cost": g_cost,
                "expanded": expanded,
                "expanded_cost_sum": total_expanded_cost
            }

        for neighbor, weight in graph[node].items():
            if neighbor not in visited:
                heapq.heappush(pq, (h[neighbor], neighbor, path + [neighbor], g_cost + weight))


def astar(graph, src, goal, h):
    pq = [(h[src], 0, src, [src])]
    best_g = {}
    expanded = []
    total_expanded_cost = 0

    while pq:
        f, g, node, path = heapq.heappop(pq)

        if node in best_g and best_g[node] <= g:
            continue

        best_g[node] = g
        expanded.append((node, g, h[node], f))
        total_expanded_cost += g

        if node == goal:
            return {
                "algorithm": "A*",
                "path": path,
                "path_cost": g,
                "expanded": expanded,
                "expanded_cost_sum": total_expanded_cost
            }

        for neighbor, weight in graph[node].items():
            new_g = g + weight
            new_f = new_g + h[neighbor]
            heapq.heappush(pq, (new_f, new_g, neighbor, path + [neighbor]))


def dfs(graph, src, goal):
    stack = [(src, [src], 0)]
    visited = set()
    expanded = []
    total_expanded_cost = 0

    while stack:
        node, path, cost = stack.pop()

        if node in visited:
            continue

        visited.add(node)
        expanded.append((node, cost))
        total_expanded_cost += cost

        if node == goal:
            return {
                "algorithm": "DFS",
                "path": path,
                "path_cost": cost,
                "expanded": expanded,
                "expanded_cost_sum": total_expanded_cost
            }

        neighbors = list(graph[node].items())
        for neighbor, weight in reversed(neighbors):
            if neighbor not in visited:
                stack.append((neighbor, path + [neighbor], cost + weight))


def bfs(graph, src, goal):
    queue = deque([(src, [src], 0)])
    visited = {src}
    expanded = []
    total_expanded_cost = 0

    while queue:
        node, path, cost = queue.popleft()
        expanded.append((node, cost))
        total_expanded_cost += cost

        if node == goal:
            return {
                "algorithm": "BFS",
                "path": path,
                "path_cost": cost,
                "expanded": expanded,
                "expanded_cost_sum": total_expanded_cost
            }

        for neighbor, weight in graph[node].items():
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [neighbor], cost + weight))


def ucs(graph, src, goal):
    pq = [(0, src, [src])]
    visited = {}
    expanded = []
    total_expanded_cost = 0

    while pq:
        cost, node, path = heapq.heappop(pq)

        if node in visited and visited[node] <= cost:
            continue

        visited[node] = cost
        expanded.append((node, cost))
        total_expanded_cost += cost

        if node == goal:
            return {
                "algorithm": "UCS",
                "path": path,
                "path_cost": cost,
                "expanded": expanded,
                "expanded_cost_sum": total_expanded_cost
            }

        for neighbor, weight in graph[node].items():
            new_cost = cost + weight
            heapq.heappush(pq, (new_cost, neighbor, path + [neighbor]))


# ---------- Visualization helpers ----------

def build_nx_graph(graph):
    G = nx.Graph()
    for city, neighbors in graph.items():
        for neighbor, weight in neighbors.items():
            G.add_edge(city, neighbor, weight=weight)
    return G


# Romania map-д ойролцоо харагдуулах гараар өгсөн байрлал
pos = {
    "Arad": (1, 5),
    "Zerind": (2, 6),
    "Oradea": (3, 6.5),
    "Sibiu": (4.5, 5),
    "Timisoara": (1.5, 3.8),
    "Lugoj": (2.8, 3.0),
    "Mehadia": (3.2, 2.2),
    "Drobeta": (3.0, 1.2),
    "Craiova": (4.8, 1.0),
    "Rimnicu": (5.2, 3.8),
    "Fagaras": (6.5, 5.0),
    "Pitesti": (6.3, 2.8),
    "Bucharest": (8.0, 2.2),
    "Giurgiu": (7.8, 1.0),
    "Urziceni": (9.2, 3.0),
    "Hirsova": (10.5, 3.2),
    "Eforie": (10.8, 1.8),
    "Vaslui": (10.0, 4.8),
    "Iasi": (9.5, 6.0),
    "Neamt": (8.5, 6.5),
}

G = build_nx_graph(graph)


def get_path_edges(path):
    return list(zip(path[:-1], path[1:]))


def visualize_result(G, pos, result):
    plt.figure(figsize=(12, 8))

    expanded_nodes = [item[0] for item in result["expanded"]]
    path_nodes = result["path"]
    path_edges = get_path_edges(path_nodes)

    # all edges
    nx.draw_networkx_edges(G, pos, edge_color="lightgray", width=1.5)

    # expanded nodes
    nx.draw_networkx_nodes(
        G, pos,
        nodelist=expanded_nodes,
        node_color="orange",
        node_size=900,
        alpha=0.8
    )

    # final path edges
    nx.draw_networkx_edges(
        G, pos,
        edgelist=path_edges,
        edge_color="red",
        width=4
    )

    # final path nodes
    nx.draw_networkx_nodes(
        G, pos,
        nodelist=path_nodes,
        node_color="limegreen",
        node_size=1100
    )

    # all labels
    nx.draw_networkx_labels(G, pos, font_size=10, font_weight="bold")

    # edge weights
    edge_labels = nx.get_edge_attributes(G, "weight")
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=8)

    plt.title(
        f'{result["algorithm"]}\n'
        f'Path: {" -> ".join(result["path"])} | Cost = {result["path_cost"]}',
        fontsize=14
    )
    plt.axis("off")
    plt.tight_layout()
    plt.show()


start = "Arad"
goal = "Bucharest"

results = [
    dfs(graph, start, goal),
    bfs(graph, start, goal),
    ucs(graph, start, goal),
    greedy(graph, start, goal, heuristic),
    astar(graph, start, goal, heuristic)
]

for r in results:
    print("\nAlgorithm:", r["algorithm"])
    print("Path:", " -> ".join(r["path"]))
    print("Path Cost:", r["path_cost"])
    print("Expanded cities:", [item[0] for item in r["expanded"]])
    print("Expanded cost sum:", r["expanded_cost_sum"])

# algorithm бүрийг тус тусад нь зурна
for r in results:
    visualize_result(G, pos, r)
