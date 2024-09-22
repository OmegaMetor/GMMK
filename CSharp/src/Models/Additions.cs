namespace GMMK.Models;
using System.Text.Json;
#nullable enable
#pragma warning disable CS8618

public class Additions
{
    public Room[]? rooms { get; set; }
    public Script[]? scripts { get; set; }
    public Object[]? objects { get; set; }
}