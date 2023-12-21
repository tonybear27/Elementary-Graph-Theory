from collections import defaultdict

def bipartite(n, edges):
    graph = defaultdict(list)

    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)

    color = [-1] * (n + 1) 
    queue = []

    for i in range(1, n + 1):
        if color[i] == -1:
            color[i] = 0
            queue.append(i)

            while queue:
                u = queue.pop(0)

                for v in graph[u]:
                    if color[v] == -1:
                        color[v] = 1 - color[u]
                        queue.append(v)
                    elif color[v] == color[u]:
                        return "No"

    return "Yes"

n, m = map(int, input().split())
edges = [list(map(int, input().split())) for _ in range(m)]

result = bipartite(n, edges)
print(result)
