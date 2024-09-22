using System.Collections.Generic;
using System.Linq;
using GMMK.Models;
namespace GMMK;

static class DependencySorter
{
    public static List<ModJson> OrderByDependencies(this IEnumerable<ModJson> items)
    {
        var visited = new HashSet<ModJson>();
        var ordered = new List<ModJson>();

        void Dfs(ModJson item)
        {
            if (visited.Contains(item))
            {
                return;
            }

            visited.Add(item);
            foreach (var dependency in item.modinfo.dependencies)
            {
                Dfs(items.First(x => x.modinfo.name.Equals(dependency)));
            }

            ordered.Add(item);
        }

        foreach (var item in items)
        {
            Dfs(item);
        }

        return ordered;
    }
}