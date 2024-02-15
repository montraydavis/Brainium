using Microsoft.CodeAnalysis.CSharp.Syntax;
using Codelyzer.Analysis.Model;

namespace Codelyzer.Analysis.CSharp.Handlers
{
    /// <summary>
    /// Handles the processing of class declarations.
    /// </summary>
    public class ClassDeclarationHandler : UstNodeHandler
    {
        private ClassDeclaration ClassDeclaration => (ClassDeclaration)UstNode;

        public ClassDeclarationHandler(CodeContext context, ClassDeclarationSyntax syntaxNode)
            : base(context, syntaxNode, new ClassDeclaration())
        {
            // Get the class symbol from the semantic model
            var classSymbol = SemanticHelper.GetDeclaredSymbol(syntaxNode, SemanticModel, OriginalSemanticModel);

            // Set basic class declaration properties
            ClassDeclaration.Identifier = syntaxNode.Identifier.ToString();
            ClassDeclaration.Modifiers = syntaxNode.Modifiers.ToString();

            if (classSymbol != null)
            {
                // Set full identifier and reference information
                ClassDeclaration.FullIdentifier = classSymbol.OriginalDefinition.ToString();
                ClassDeclaration.Reference.Namespace = GetNamespace(classSymbol);
                ClassDeclaration.Reference.Assembly = GetAssembly(classSymbol);
                ClassDeclaration.Reference.Version = GetAssemblyVersion(classSymbol);
                ClassDeclaration.Reference.AssemblySymbol = classSymbol.ContainingAssembly;

                // Process base types and interfaces
                ClassDeclaration.BaseList = new System.Collections.Generic.List<string>();
                if (classSymbol.BaseType != null)
                {
                    var baseTypeSymbol = classSymbol.BaseType;
                    ClassDeclaration.BaseType = baseTypeSymbol.ToString();
                    ClassDeclaration.BaseTypeOriginalDefinition = GetBaseTypOriginalDefinition(classSymbol);
                    do
                    {
                        ClassDeclaration.BaseList.Add(baseTypeSymbol.ToString());
                    } while ((baseTypeSymbol = baseTypeSymbol.BaseType) != null);
                }

                // Add implemented interfaces to the base list
                if (classSymbol.AllInterfaces != null)
                {
                    ClassDeclaration.BaseList.AddRange(classSymbol.AllInterfaces.Select(x => x.ToString())?.ToList());
                }
            }
        }
    }
}
