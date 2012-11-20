/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Quicksort_(C_Plus_Plus)?action=history&offset=20080623154833

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Quicksort_(C_Plus_Plus)?oldid=13758
*/

#include <algorithm>	// std::swap()
#include <iterator>     // std::iterator_traits<>

#include "log.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {
namespace Algorithm {

template<typename IT, typename CP>
IT Partition(IT begin, IT end, IT pivot, CP cmp)
{
    typename std::iterator_traits<IT>::value_type piv(*pivot);
	std::swap(*pivot, *(end-1));
    IT store = begin;
    for(IT it = begin; it != end-1; ++it) {
        if (cmp(*it, piv)) {
			std::swap(*store, *it);
			++store;
		}
	}
	std::swap(*(end-1), *store);
	return store;
}

template<typename IT>
IT PivotMedian(IT begin, IT end)
{
    IT pivot(begin + (end - begin) / 2);
    if (*begin <= *pivot && *(end-1) <= *begin)
        pivot = begin;
    else if (*(end-1) <= *pivot && *begin <= *(end-1))
        pivot = end-1;

	return pivot;
}

template<typename IT>
struct PivotRandom {
    PivotRandom() {
		srand(time(NULL));
	}
	IT operator()(IT begin, IT end) {
        return begin + (rand() % (end - begin));
	}
};

template<typename IT>
bool CompareGeneric(const typename std::iterator_traits<IT>::value_type &a,
                    const typename std::iterator_traits<IT>::value_type &b)
{
    return a < b;
}

template<typename IT, typename CP, typename PF>
void QuickSort(IT begin, IT end, CP cp, PF pf)
{
	if((end-begin)>1) {
        IT pivot = pf(begin, end);

        pivot = Partition(begin, end, pivot, cp);

        QuickSort(begin, pivot, cp, pf);
        QuickSort(pivot+1, end, cp, pf);
	}
}
template<typename IT, typename CP>
void QuickSort(IT begin, IT end, CP cp)
{
    QuickSort(begin, end, cp, PivotMedian<IT>);
}

template<typename IT>
void QuickSort(IT begin, IT end)
{
    QuickSort(begin, end, CompareGeneric<IT>);
}

template<typename C, typename CP, typename PF>
void QuickSort(C &container, CP cp, PF pf)
{
    QuickSort(container.begin(), container.end(), cp, pf);
}
template<typename C, typename CP>
void QuickSort(C &container, CP cp)
{
    QuickSort(container.begin(), container.end(), cp);
}
template<typename C>
void QuickSort(C &container)
{
    QuickSort(container.begin(), container.end());
}

} // namespace Algorithm
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
