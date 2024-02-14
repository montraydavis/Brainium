using Codelyzer.Analysis.Model;
using System.Collections.Generic;
using System.Linq;

public class DependencySorter
{
    private class Graph<T>
    {
        public Dictionary<T, List<T>> AdjacencyList = new();

        public void AddVertex(T vertex)
        {
            AdjacencyList[vertex] = new List<T>();
        }

        public void AddEdge(T from, T to)
        {
            if (AdjacencyList.ContainsKey(from))
            {
                AdjacencyList[from].Add(to);
            }
        }
    }

    public List<ClassDeclaration> SortByDependency(List<ClassDeclaration> classes, List<UsingDirective> usings)
    {
        var graph = new Graph<ClassDeclaration>();
        var classByName = classes.ToDictionary(c => c.Identifier.Text, c => c);
        var usingNames = usings.Select(u => u.Identifier.Text).ToHashSet();

        foreach (var cls in classes)
        {
            graph.AddVertex(cls);

            AddEdgesForBaseTypes(cls, classByName, graph);
            AddEdgesForUsings(cls, usingNames, classByName, graph);
            AddEdgesForMethodBodies(cls, classByName, graph);
        }

        return TopologicalSort(graph).ToList();
    }

    private void AddEdgesForBaseTypes(ClassDeclaration cls, Dictionary<string, ClassDeclaration> classByName, Graph<ClassDeclaration> graph)
    {
        if (cls.BaseList != null)
        {
            foreach (var baseType in cls.BaseList.BaseTypes)
            {
                if (classByName.TryGetValue(baseType.Identifier.Text, out var baseClass))
                {
                    graph.AddEdge(cls, baseClass);
                }
            }
        }
    }

    private void AddEdgesForUsings(ClassDeclaration cls, HashSet<string> usingNames, Dictionary<string, ClassDeclaration> classByName, Graph<ClassDeclaration> graph)
    {
        // Assuming direct class name matches for simplicity; may need namespace handling
        foreach (var usingName in usingNames)
        {
            if (classByName.TryGetValue(usingName, out var usedClass))
            {
                graph.AddEdge(cls, usedClass);
            }
        }
    }

    private void AddEdgesForMethodBodies(ClassDeclaration cls, Dictionary<string, ClassDeclaration> classByName, Graph<ClassDeclaration> graph)
    {
        // This is a simplified approach; actual implementation should parse method bodies
        // to find class references. This requires a detailed analysis of the syntax tree.
    }

    private IEnumerable<ClassDeclaration> TopologicalSort(Graph<ClassDeclaration> graph)
    {
        var visited = new HashSet<ClassDeclaration>();
        var result = new Stack<ClassDeclaration>();

        foreach (var vertex in graph.AdjacencyList.Keys)
        {
            TopologicalSortUtil(vertex, visited, result, graph);
        }

        return result;
    }

    private void TopologicalSortUtil(ClassDeclaration vertex, HashSet<ClassDeclaration> visited, Stack<ClassDeclaration> stack, Graph<ClassDeclaration> graph)
    {
        if (!visited.Contains(vertex))
        {
            visited.Add(vertex);
            foreach (var neighbor in graph.AdjacencyList[vertex])
            {
                TopologicalSortUtil(neighbor, visited, stack, graph);
            }
            stack.Push(vertex);
        }
    }
}
