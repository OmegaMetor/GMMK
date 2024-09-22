namespace GMMK.Models;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618

public class Mixin
{
    public InjectionPoint inject { get; set; }
    public string code { get; set; }
}