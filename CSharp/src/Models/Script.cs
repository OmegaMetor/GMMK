namespace GMMK.Models;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618

public class Script
{
    public string name { get; set; }
    public string code { get; set; }
    public bool? overwrite { get; set; }
    public CustomProperty[]? custom { get; set; }
}