namespace GMMK.Models;
using System.Text.Json.Nodes;
#nullable enable
#pragma warning disable CS8618

public class CustomProperty
{
    public string name { get; set; }
    public bool required { get; set; } // Would be optional, but I don't know what the default should be :3
    public JsonNode options { get; set; }
}