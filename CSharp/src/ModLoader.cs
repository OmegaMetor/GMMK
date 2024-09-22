using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using GMMK.Models;

namespace GMMK
{
    public class ModLoader
    {
        public static byte[] loadMods()
        {

            string GameFolder = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

            IEnumerable<ModJson> ModJsons = Directory.GetDirectories(Path.Combine(GameFolder, "GMMK")).ToList()
                .Select((String modFolder) =>
                {
                    return ModJson.loadFromJson(Path.Combine(modFolder, "mod.json"));
                }
            ).OrderByDependencies();



            // Here until this is finished <3
            Console.WriteLine("funny");
            byte[] arr = { 0, 1, 2, 3, 4, 5 };
            return arr;
        }
    }
}