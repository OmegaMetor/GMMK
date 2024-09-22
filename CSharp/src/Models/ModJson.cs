namespace GMMK.Models;

using System;
using System.IO;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618


public class ModJson
{
    public static ModJson? loadFromJson(String path){
        ModJson? loadedModJson = JsonSerializer.Deserialize<ModJson>("");
        return loadedModJson;
    }

    public ModInfo modinfo { get; set; }
    public Additions? additions { get; set; }
    public Mixin[]? mixins { get; set; }
}