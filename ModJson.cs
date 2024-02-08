// See https://aka.ms/new-console-template for more information
using ExtensionBase;
using System.Text.Json;
using System.Text.Json.Nodes;


namespace ModJson;
/* Example Usage:
var i = File.ReadAllText("file.json");
var json = JsonSerializer.Deserialize<modData>(i);
Console.WriteLine(json.modinfo.name);
*/
class modData
{
    public required ModInfo modinfo { get; set; }
    public Additions? additions { get; set; }
    public Mixin[]? mixins { get; set; }
}
public class ModInfo
{
    public required string name { get; set; }
    public required string id { get; set; }
    public string? developer { get; set; }
    public string? source { get; set; }
    public ResourceLocations? resource_locations { get; set; }
}
public class ResourceLocations
{
    public string? code { get; set; }
    public string? textures { get; set; }
    public string? sounds { get; set; }
    public string? rooms { get; set; }
}


public class Additions
{
    public Room[]? rooms { get; set; }
    public Script[]? scripts { get; set; }
    public Object[]? objects { get; set; }
}

public class Room
{
    // TODO: Figure out room format and implement

}

public class Script
{
    public required string name { get; set; }
    public required string code { get; set; }
    public bool? overwrite { get; set; }
    public CustomProperty[]? custom { get; set; }
}
public class Object { }

public class CustomProperty
{
    public required string name { get; set; }
    public required bool required { get; set; } // Would be optional, but I don't know what the default should be :3
    public required JsonNode options { get; set; }
}

class Mixin
{
    public required InjectionPoint inject { get; set; }
    public required string code { get; set; }
}

public class InjectionPoint
{
    public required string script { get; set; }
    public required InjectionLocation at { get; set; }
    public InjectionRelativity? when { get; set; }
    public int? index { get; set; }
    public string? function { get; set; }
    public string? variable { get; set; }
}

[System.Text.Json.Serialization.JsonConverter(typeof(System.Text.Json.Serialization.JsonStringEnumConverter<InjectionRelativity>))]
public enum InjectionRelativity
{
    before,
    after
}

[System.Text.Json.Serialization.JsonConverter(typeof(System.Text.Json.Serialization.JsonStringEnumConverter<InjectionLocation>))]
public enum InjectionLocation
{
    start,
    @return,
    variable,
    call_function
}