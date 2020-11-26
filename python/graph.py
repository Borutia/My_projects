
def dfs(graph, vertex, visited):
    visited[vertex] = True
    for _ in graph[vertex]:
        if not visited[_]:
            return dfs(graph, _, visited)


def main():
    graph = {
        'A': ['B'],
        'B': ['A', 'D', 'C'],
        'C': ['B', 'G'],
        'D': ['B'],
        'G': ['C']
    }

    #print(len(graph))

    # for _ in graph:
    #     print(graph[_])

    visited = {_: False for _ in graph}

    print(visited)
    vertex = 'A'
    dfs(graph, vertex, visited)
   # print(visited.key.count(True))


if __name__ == '__main__':
    #main()
    test = [5,4,3,5,6,3,4]
