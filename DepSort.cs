using Codelyzer.Analysis.Model;
using System;
using System.Collections.Generic;
using System.Linq;

public class DependencySorter
{
    private class Graph
    {
        public Dictionary<string, List<string>> AdjacencyList = new();

        public void AddVertex(string vertex)
        {
            if (!AdjacencyList.ContainsKey(vertex))
            {
                AdjacencyList[vertex] = new List<string>();
            }
        }

        public void AddEdge(string from, string to)
        {
            if (AdjacencyList.ContainsKey(from) && !AdjacencyList[from].Contains(to))
            {
                AdjacencyList[from].Add(to);
            }
        }
    }

    public List<ClassDeclaration> SortByDependency(List<ClassDeclaration> classes, List<UsingDirective> usings)
    {
        var graph = new Graph();
        var classByName = classes.ToDictionary(c => c.Identifier.Text, c => c);
        var classNames = classByName.Keys.ToHashSet();
        var usingNames = usings.Select(u => u.Identifier.Text).ToHashSet();

        foreach (var cls in classes)
        {
            var className = cls.Identifier.Text;
            graph.AddVertex(className);

            AddEdgesForBaseTypes(cls, classNames, graph);
            AddEdgesForUsings(cls, usingNames, classNames, graph);
            // AddEdgesForMethodBodies can be implemented similarly, analyzing references within method bodies
        }

        var sortedClassNames = TopologicalSort(graph);
        return sortedClassNames.Select(name => classByName[name]).ToList();
    }

    private void AddEdgesForBaseTypes(ClassDeclaration cls, HashSet<string> classNames, Graph graph)
    {
        var className = cls.Identifier.Text;
        if (cls.BaseList != null)
        {
            foreach (var baseType in cls.BaseList.BaseTypes)
            {
                var baseTypeName = baseType.Identifier.Text;
                if (classNames.Contains(baseTypeName))
                {
                    graph.AddEdge(className, baseTypeName);
                }
            }
        }
    }

    private void AddEdgesForUsings(ClassDeclaration cls, HashSet<string> usingNames, HashSet<string> classNames, Graph graph)
    {
        var className = cls.Identifier.Text;
        foreach (var usingName in usingNames)
        {
            if (classNames.Contains(usingName) && usingName != className)
            {
                graph.AddEdge(className, usingName);
            }
        }
    }

    private List<string> TopologicalSort(Graph graph)
    {
        var visited = new HashSet<string>();
        var stack = new Stack<string>();

        foreach (var vertex in graph.AdjacencyList.Keys)
        {
            TopologicalSortUtil(vertex, visited, stack, graph);
        }

        return stack.ToList();
    }

    private void TopologicalSortUtil(string vertex, HashSet<string> visited, Stack<string> stack, Graph graph)
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
