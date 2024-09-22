namespace GMMK.Models;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618

public class InjectionPoint
{
    public string script { get; set; }
    public InjectionLocation at { get; set; }
    public InjectionRelativity? when { get; set; }
    public int? index { get; set; }
    public string? function { get; set; }
    public string? variable { get; set; }
}