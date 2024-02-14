using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using System.Collections.Generic;
using System.Linq;

public static class ClassDependencySorter
{
    /// <summary>
    /// Sorts class declarations by their dependency order.
    /// </summary>
    /// <param name="classes">The list of class declarations to sort.</param>
    /// <param name="model">The semantic model for resolving type information.</param>
    /// <returns>A sorted list of class declarations.</returns>
    public static List<ClassDeclarationSyntax> SortByDependencyOrder(List<ClassDeclarationSyntax> classes, SemanticModel model)
    {
        var graph = new Dictionary<string, List<string>>();
        var classNames = new HashSet<string>();

        // Build the graph
        foreach (var cls in classes)
        {
            var className = cls.Identifier.Text;
            classNames.Add(className);
            var dependencies = GetDependencies(cls, model);

            if (!graph.ContainsKey(className))
            {
                graph[className] = new List<string>();
            }

            foreach (var dependency in dependencies)
            {
                if (classNames.Contains(dependency) && dependency != className)
                {
                    graph[className].Add(dependency);
                }
            }
        }

        var sortedClasses = TopologicalSort(graph).Select(name => classes.First(c => c.Identifier.Text == name)).ToList();
        return sortedClasses;
    }

    /// <summary>
    /// Performs a topological sort on the dependency graph.
    /// </summary>
    /// <param name="graph">The dependency graph.</param>
    /// <returns>A list of class names sorted by dependency order.</returns>
    private static List<string> TopologicalSort(Dictionary<string, List<string>> graph)
    {
        var visited = new HashSet<string>();
        var result = new List<string>();

        foreach (var item in graph.Keys)
        {
            TopologicalSortUtil(item, visited, result, graph);
        }

        result.Reverse();
        return result;
    }

    private static void TopologicalSortUtil(string v, HashSet<string> visited, List<string> result, Dictionary<string, List<string>> graph)
    {
        if (!visited.Contains(v))
        {
            visited.Add(v);
            foreach (var dep in graph[v])
            {
                TopologicalSortUtil(dep, visited, result, graph);
            }
            result.Add(v);
        }
    }

    /// <summary>
    /// Gets the dependencies of a class declaration.
    /// </summary>
    /// <param name="cls">The class declaration.</param>
    /// <param name="model">The semantic model for resolving type information.</param>
    /// <returns>A list of dependency names.</returns>
    private static List<string> GetDependencies(ClassDeclarationSyntax cls, SemanticModel model)
    {
        var dependencies = new List<string>();

        // Add base types
        var baseTypes = cls.BaseList?.Types.Select(bt => model.GetTypeInfo(bt.Type).Type?.Name).Where(n => n != null);
        if (baseTypes != null)
        {
            dependencies.AddRange(baseTypes);
        }

        // Add types from method bodies, properties, etc.
        // This part can be expanded based on specific needs, such as analyzing method bodies or property types.
        // For simplicity, this example does not dive deep into method body analysis.

        return dependencies.Distinct().ToList();
    }
}
