namespace GMMK.Models;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618

public class ModInfo
{
    public string name { get; set; }
    public string id { get; set; }
    public string? developer { get; set; }
    public string? source { get; set; }
    public string[]? dependencies { get; set; }
    public ResourceLocations? resource_locations { get; set; }
}