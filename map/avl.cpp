#include "avl.hpp"

namespace ft
{
	void showTrunks(std::ostream& ostr, Trunk *p)
	{
		if (p == nullptr) {
			return;
		}

		showTrunks(ostr, p->prev);
		ostr << p->str;
	}
}