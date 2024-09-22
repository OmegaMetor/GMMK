namespace GMMK.Models;
using System.Text.Json.Serialization;
#nullable enable
#pragma warning disable CS8618

[JsonConverter(typeof(JsonStringEnumConverter))]
public enum InjectionRelativity
{
    before,
    after
}