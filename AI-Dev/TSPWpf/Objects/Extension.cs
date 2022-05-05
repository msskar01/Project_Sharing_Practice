using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSPWpf.Objects
{
    public static class Extension
    {
        public static IEnumerable<T> MoveSection<T>(this IEnumerable<T> @this, int insertionPoint, int startIndex, int endIndex)
        {
            var counter = 0;
            var numElements = endIndex - startIndex;
            var range = Enumerable.Range(startIndex, numElements);
            foreach (var i in @this)
            {
                if (counter == insertionPoint)
                {
                    foreach (var j in @this.Skip(startIndex).Take(numElements))
                    {
                        yield return j;
                    }
                }
                if (!range.Contains(counter))
                {
                    yield return i;
                }
                counter++;
            }
            //The insertion point might have been after the entire list:
            if (counter++ == insertionPoint)
            {
                foreach (var j in @this.Skip(startIndex).Take(numElements))
                {
                    yield return j;
                }
            }
        }
    }
}
