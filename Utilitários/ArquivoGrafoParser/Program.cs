using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            if (!File.Exists(args[0]) || string.IsNullOrWhiteSpace(args[0]))
                Console.WriteLine("Arquivo \"{0}\" não existe em diretório informado", args[0]);
            else
                WriteNewFile(Parser(args[0]), args[0]);
        }

        private static void WriteNewFile(List<FileLine> _list, string _filepath)
        {
            var filename = Path.GetFileNameWithoutExtension(_filepath);
            var filepath = Path.GetDirectoryName(_filepath);
            var fullfilename = Path.Combine(filepath, string.Format("{0}Parsed.txt", filename));
            var builder = new StringBuilder();
            var numVertices = _list.Select(s => s.vertice)
                .Distinct()
                .Count()
                .ToString();

            builder.AppendLine(numVertices);
            _list.ForEach(f => builder.AppendLine(string.Format("{0} {1} {2}", f.vertice, f.vizinho, f.pesoArestae)));

            if (File.Exists(fullfilename))
                File.Delete(fullfilename);

            using (var file = File.OpenWrite(fullfilename))
                file.Write(Encoding.GetEncoding(1252).GetBytes(builder.ToString()), 0, Encoding.GetEncoding(1252).GetByteCount(builder.ToString()));
        }

        private static List<FileLine> Parser(string _inputFilename)
        {
            var fileLines = File.ReadLines(_inputFilename).ToList();
            var lines = new List<FileLine>();
            var header = fileLines.ElementAt(0)
                .Split(' ')
                .Where(w => !string.IsNullOrWhiteSpace(w))
                .Select(s => s)
                .ToList();

            foreach (var fileline in fileLines.Skip(1))
            {
                var row = fileline
                    .Split(' ')
                    .Where(w => !string.IsNullOrWhiteSpace(w))
                    .Select(s => s)
                    .ToList();

                for (int i = 1; i < header.Count; i++)
                {
                    lines.Add(
                        new FileLine()
                        {
                            vertice = row.ElementAt(0),
                            vizinho = header.ElementAt(i), 
                            pesoArestae = row.ElementAt(i)
                        }    
                    );
                }
            }

            return lines.Where(w => w.vertice != w.vizinho).ToList();
        }
    }
    
    class FileLine
    {
        public string vertice { get; set; }
        public string vizinho { get; set; }
        public string pesoArestae { get; set; }
    }
}
