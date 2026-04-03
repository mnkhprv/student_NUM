from itertools import combinations, permutations
import math
import random

try:
    import networkx as nx
except ImportError:
    nx = None

try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None

mgl_map = {
    'nodes': ['Ulaanbaatar', 'Erdenet', 'Darkhan', 'Choibalsan', 'Mörön', 'Khovd', 'Ölgii', 'Bayankhongor', 'Dalanzadgad', 'Altai'],
    'edges': [
        ('Ulaanbaatar', 'Erdenet', {'weight': 231}),
        ('Ulaanbaatar', 'Darkhan', {'weight': 142}),
        ('Ulaanbaatar', 'Choibalsan', {'weight': 198}),
        ('Ulaanbaatar', 'Mörön', {'weight': 96}),
        ('Ulaanbaatar', 'Khovd', {'weight': 199}),
        ('Ulaanbaatar', 'Ölgii', {'weight': 218}),
        ('Ulaanbaatar', 'Bayankhongor', {'weight': 210}),
        ('Ulaanbaatar', 'Dalanzadgad', {'weight': 140}),
        ('Ulaanbaatar', 'Altai', {'weight': 297}),
        ('Erdenet', 'Darkhan', {'weight': 290}),
        ('Erdenet', 'Choibalsan', {'weight': 185}),
        ('Erdenet', 'Mörön', {'weight': 253}),
        ('Erdenet', 'Khovd', {'weight': 262}),
        ('Erdenet', 'Ölgii', {'weight': 242}),
        ('Erdenet', 'Bayankhongor', {'weight': 264}),
        ('Erdenet', 'Dalanzadgad', {'weight': 246}),
        ('Erdenet', 'Altai', {'weight': 186}),
        ('Darkhan', 'Choibalsan', {'weight': 151}),
        ('Darkhan', 'Mörön', {'weight': 93}),
        ('Darkhan', 'Khovd', {'weight': 85}),
        ('Darkhan', 'Ölgii', {'weight': 229}),
        ('Darkhan', 'Bayankhongor', {'weight': 157}),
        ('Darkhan', 'Dalanzadgad', {'weight': 221}),
        ('Darkhan', 'Altai', {'weight': 152}),
        ('Choibalsan', 'Mörön', {'weight': 56}),
        ('Choibalsan', 'Khovd', {'weight': 137}),
        ('Choibalsan', 'Ölgii', {'weight': 99}),
        ('Choibalsan', 'Bayankhongor', {'weight': 130}),
        ('Choibalsan', 'Dalanzadgad', {'weight': 126}),
        ('Choibalsan', 'Altai', {'weight': 55}),
        ('Mörön', 'Khovd', {'weight': 111}),
        ('Mörön', 'Ölgii', {'weight': 299}),
        ('Mörön', 'Bayankhongor', {'weight': 290}),
        ('Mörön', 'Dalanzadgad', {'weight': 260}),
        ('Mörön', 'Altai', {'weight': 231}),
        ('Khovd', 'Ölgii', {'weight': 150}),
        ('Khovd', 'Bayankhongor', {'weight': 115}),
        ('Khovd', 'Dalanzadgad', {'weight': 296}),
        ('Khovd', 'Altai', {'weight': 130}),
        ('Ölgii', 'Bayankhongor', {'weight': 232}),
        ('Ölgii', 'Dalanzadgad', {'weight': 299}),
        ('Ölgii', 'Altai', {'weight': 229}),
        ('Bayankhongor', 'Dalanzadgad', {'weight': 195}),
        ('Bayankhongor', 'Altai', {'weight': 262}),
        ('Dalanzadgad', 'Altai', {'weight': 263})
    ]
}


START_CITY = "Ulaanbaatar"

# Rough west-to-east / north-to-south placement for easier plotting.
CITY_POSITIONS = {
    "Ulaanbaatar": (0.0, 0.0),
    "Erdenet": (-1.3, 1.0),
    "Darkhan": (-0.5, 1.8),
    "Choibalsan": (3.5, 1.0),
    "Mörön": (-2.2, 3.2),
    "Khovd": (-4.6, 0.8),
    "Ölgii": (-6.0, 1.8),
    "Bayankhongor": (-1.8, -1.8),
    "Dalanzadgad": (1.5, -2.4),
    "Altai": (-3.8, -1.4),
}


def build_distance_map(graph):
    distance_map = {city: {} for city in graph["nodes"]}
    for city_a, city_b, meta in graph["edges"]:
        weight = meta["weight"]
        distance_map[city_a][city_b] = weight
        distance_map[city_b][city_a] = weight
    return distance_map


DISTANCE_MAP = build_distance_map(mgl_map)


def route_distance(route, distance_map=DISTANCE_MAP):
    total = 0
    for current_city, next_city in zip(route, route[1:]):
        total += distance_map[current_city][next_city]
    total += distance_map[route[-1]][route[0]]
    return total


def random_route(nodes, start_city=START_CITY, rng=None):
    rng = rng or random
    middle_cities = [city for city in nodes if city != start_city]
    rng.shuffle(middle_cities)
    return [start_city] + middle_cities


def swap_neighbor(route, rng=None):
    rng = rng or random
    neighbor = route[:]
    i, j = sorted(rng.sample(range(1, len(route)), 2))
    neighbor[i], neighbor[j] = neighbor[j], neighbor[i]
    return neighbor


def hill_climbing(graph, start_city=START_CITY, restarts=100, seed=42):
    rng = random.Random(seed)
    best_route = None
    best_distance = math.inf
    steps_taken = 0

    for _ in range(restarts):
        current_route = random_route(graph["nodes"], start_city, rng)
        current_distance = route_distance(current_route)

        improved = True
        while improved:
            improved = False
            best_neighbor = current_route
            best_neighbor_distance = current_distance

            for i, j in combinations(range(1, len(current_route)), 2):
                candidate = current_route[:]
                candidate[i], candidate[j] = candidate[j], candidate[i]
                candidate_distance = route_distance(candidate)
                steps_taken += 1

                if candidate_distance < best_neighbor_distance:
                    best_neighbor = candidate
                    best_neighbor_distance = candidate_distance
                    improved = True

            current_route = best_neighbor
            current_distance = best_neighbor_distance

        if current_distance < best_distance:
            best_route = current_route
            best_distance = current_distance

    return {
        "route": best_route,
        "distance": best_distance,
        "steps": steps_taken,
        "restarts": restarts,
    }


def simulated_annealing(
    graph,
    start_city=START_CITY,
    seed=7,
    initial_temperature=1000.0,
    cooling_rate=0.995,
    min_temperature=1e-3,
    iterations_per_temp=150,
):
    rng = random.Random(seed)
    current_route = random_route(graph["nodes"], start_city, rng)
    current_distance = route_distance(current_route)
    best_route = current_route[:]
    best_distance = current_distance

    temperature = initial_temperature
    steps_taken = 0

    while temperature > min_temperature:
        for _ in range(iterations_per_temp):
            candidate = swap_neighbor(current_route, rng)
            candidate_distance = route_distance(candidate)
            delta = candidate_distance - current_distance
            steps_taken += 1

            if delta < 0 or rng.random() < math.exp(-delta / temperature):
                current_route = candidate
                current_distance = candidate_distance

                if current_distance < best_distance:
                    best_route = current_route[:]
                    best_distance = current_distance

        temperature *= cooling_rate

    return {
        "route": best_route,
        "distance": best_distance,
        "steps": steps_taken,
        "initial_temperature": initial_temperature,
        "cooling_rate": cooling_rate,
    }


def brute_force_tsp(graph, start_city=START_CITY):
    other_cities = [city for city in graph["nodes"] if city != start_city]
    best_route = None
    best_distance = math.inf

    for candidate_order in permutations(other_cities):
        route = [start_city] + list(candidate_order)
        total_distance = route_distance(route)

        if total_distance < best_distance:
            best_route = route
            best_distance = total_distance

    return {"route": best_route, "distance": best_distance}


def format_cycle(route):
    return " -> ".join(route + [route[0]])


def print_result(title, result):
    print(title)
    print(f"  Route    : {format_cycle(result['route'])}")
    print(f"  Distance : {result['distance']} km")
    if "steps" in result:
        print(f"  Steps    : {result['steps']}")
    if "restarts" in result:
        print(f"  Restarts : {result['restarts']}")
    print()


def build_nx_graph(graph):
    graph_nx = nx.Graph()
    for city_a, city_b, meta in graph["edges"]:
        graph_nx.add_edge(city_a, city_b, weight=meta["weight"])
    return graph_nx


def get_route_edges(route):
    cycle = route + [route[0]]
    return list(zip(cycle[:-1], cycle[1:]))


def draw_route_order(ax, route):
    label_positions = {}
    for order, city in enumerate(route, start=1):
        x, y = CITY_POSITIONS[city]
        label_positions[city] = (x, y - 0.33)

    nx.draw_networkx_labels(
        ROUTE_GRAPH,
        label_positions,
        labels={city: str(order) for order, city in enumerate(route, start=1)},
        font_size=8,
        font_weight="bold",
        font_color="#111827",
        ax=ax,
    )


def visualize_result(ax, graph_nx, result, title, color):
    route_nodes = result["route"]
    route_edges = get_route_edges(route_nodes)
    base_nodes = [city for city in graph_nx.nodes if city != START_CITY]

    nx.draw_networkx_edges(graph_nx, CITY_POSITIONS, edge_color="lightgray", width=1.5, ax=ax)
    nx.draw_networkx_nodes(
        graph_nx,
        CITY_POSITIONS,
        nodelist=base_nodes,
        node_color="#93c5fd",
        node_size=1100,
        edgecolors="white",
        linewidths=1.5,
        ax=ax,
    )
    nx.draw_networkx_nodes(
        graph_nx,
        CITY_POSITIONS,
        nodelist=[START_CITY],
        node_color="#f59e0b",
        node_size=1300,
        edgecolors="white",
        linewidths=1.8,
        ax=ax,
    )
    nx.draw_networkx_edges(
        graph_nx,
        CITY_POSITIONS,
        edgelist=route_edges,
        edge_color=color,
        width=4,
        ax=ax,
    )
    nx.draw_networkx_nodes(
        graph_nx,
        CITY_POSITIONS,
        nodelist=route_nodes,
        node_color="#86efac",
        node_size=1200,
        edgecolors=color,
        linewidths=2,
        ax=ax,
    )
    nx.draw_networkx_labels(graph_nx, CITY_POSITIONS, font_size=9, font_weight="bold", ax=ax)
    nx.draw_networkx_edge_labels(
        graph_nx,
        CITY_POSITIONS,
        edge_labels=nx.get_edge_attributes(graph_nx, "weight"),
        font_size=8,
        ax=ax,
    )
    draw_route_order(ax, route_nodes)
    ax.set_title(f"{title}\nPath: {format_cycle(route_nodes)}\nCost = {result['distance']} km", fontsize=12)
    ax.axis("off")


def route_order_summary(route):
    return " | ".join(f"{index}.{city}" for index, city in enumerate(route, start=1))


def show_route_plot(title, result, color="#dc2626"):
    if plt is None or nx is None:
        print("Visualization skipped: install matplotlib and networkx.")
        return

    fig, ax = plt.subplots(figsize=(12, 8))
    visualize_result(ax, ROUTE_GRAPH, result, title, color)
    fig.text(
        0.5,
        0.03,
        route_order_summary(result["route"]),
        ha="center",
        va="bottom",
        fontsize=8,
        wrap=True,
    )
    fig.tight_layout(rect=(0, 0.06, 1, 1))


def show_comparison_plot(hill_result, annealing_result, optimal_result):
    if plt is None or nx is None:
        print("Visualization skipped: install matplotlib and networkx.")
        return

    fig, axes = plt.subplots(1, 3, figsize=(18, 6))
    plots = [
        ("Hill-Climbing", hill_result, "#dc2626"),
        ("Simulated Annealing", annealing_result, "#059669"),
        ("Optimal", optimal_result, "#7c3aed"),
    ]

    for ax, (title, result, color) in zip(axes, plots):
        visualize_result(ax, ROUTE_GRAPH, result, title, color)

    fig.tight_layout()
    fig.suptitle("TSP Route Comparison", fontsize=14)
    fig.tight_layout()


def compare_algorithms():
    hill_result = hill_climbing(mgl_map, restarts=100, seed=42)
    annealing_result = simulated_annealing(
        mgl_map,
        seed=7,
        initial_temperature=1000.0,
        cooling_rate=0.995,
        min_temperature=1e-3,
        iterations_per_temp=150,
    )
    optimal_result = brute_force_tsp(mgl_map)

    print("TSP on Mongolia city graph")
    print(f"Start city: {START_CITY}")
    print()

    print_result("1. Hill-Climbing", hill_result)
    print_result("2. Simulated Annealing", annealing_result)
    print_result("3. Optimal solution (Brute Force benchmark)", optimal_result)

    print("Comparison")
    print(
        f"  Hill-Climbing gap from optimum     : "
        f"{hill_result['distance'] - optimal_result['distance']} km"
    )
    print(
        f"  Simulated Annealing gap from optimum: "
        f"{annealing_result['distance'] - optimal_result['distance']} km"
    )

    if hill_result["distance"] < annealing_result["distance"]:
        better = "Hill-Climbing"
    elif annealing_result["distance"] < hill_result["distance"]:
        better = "Simulated Annealing"
    else:
        better = "Both algorithms produced the same distance"

    print(f"  Better heuristic result            : {better}")

    if plt is not None and nx is not None:
        show_route_plot("Hill-Climbing Route", hill_result)
        show_route_plot(
            "Simulated Annealing Route",
            annealing_result,
            color="#059669",
        )
        show_route_plot(
            "Optimal Route",
            optimal_result,
            color="#7c3aed",
        )
        show_comparison_plot(hill_result, annealing_result, optimal_result)
        plt.show()
    else:
        print()
        print("Visualization")
        print("  Install matplotlib and networkx to display Romania-style graph popups.")


ROUTE_GRAPH = build_nx_graph(mgl_map) if nx is not None else None


if __name__ == "__main__":
    compare_algorithms()
