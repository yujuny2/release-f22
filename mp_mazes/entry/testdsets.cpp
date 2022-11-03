/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    // DisjointSets s;

    // s.addelements(50);
    // s.setunion(2, 3);
    // s.setunion(3, 5);
    // s.setunion(5, 7);
    // s.setunion(7, 2);
    // s.setunion(4, 6);

    // cout << s.find(7) << endl;
    // cout << s.find(5) << endl;
    // cout << s.find(6) << endl;

    // s.addelements(1);

    // cout << s.find(50) << endl;

    // s.setunion(50, 3);

    // cout << s.find(50) << endl;

    // cout << "===========addelements1============" << endl;
    // DisjointSets disjSets;
	// disjSets.addelements(5);
    // cout << disjSets.find(3) << endl;
    // cout << endl;

    // cout << "===========addelements2============" << endl;
    // DisjointSets disjSets2;
	// disjSets2.addelements(5);
    // cout << disjSets2.find(0) << endl;
	// disjSets2.addelements(5);
    // cout << disjSets2.find(9) << endl;
    // cout << endl;

    // cout << "===========testFindandSetUnion1============" << endl;
    // DisjointSets disjSets;
	// disjSets.addelements(4);
	// disjSets.setunion(1, 2);
    // cout << disjSets.find(1) << "=" << disjSets.find(2) <<endl;
    // cout << endl;

    // cout << "===========testFindandSetUnion2============" << endl;
    // DisjointSets disjSets;
	// disjSets.addelements(10);

	// disjSets.setunion(4, 8);
	// disjSets.setunion(1, 3);
	// disjSets.setunion(1, 5);
	// disjSets.setunion(8, 3);
	// disjSets.setunion(6, 7);
	// disjSets.setunion(2, 8);
	// disjSets.setunion(7, 1);

	// int root = disjSets.find(1);
	// for (int i = 2; i <= 8; i++)
	// 	cout << root << "==" << disjSets.find(i) << endl;
	// cout << disjSets.find(0) << "!=" << disjSets.find(9) << endl;
    // cout << endl;

    // cout << "===========testFindandSetUnion3============" << endl;
    // DisjointSets disjSets;
	// disjSets.addelements(8);

	// disjSets.setunion(1, 2);
	// disjSets.setunion(1, 3);
	// disjSets.setunion(4, 5);
	// disjSets.setunion(4, 6);
	// disjSets.setunion(3, 6);

	// cout << disjSets.find(4) << "==" << disjSets.find(1) << endl;
	// cout << disjSets.find(0) << "!=" << disjSets.find(4) << endl;

    // cout << "===========size1============" << endl;
    // DisjointSets disjSets;
	// disjSets.addelements(4);
	// cout << 1 << "==" << disjSets.size(2) << endl;

    cout << "===========size2============" << endl;
    DisjointSets disjSets;
	disjSets.addelements(8);

	disjSets.setunion(1, 7);
	disjSets.setunion(2, 6);
	disjSets.setunion(3, 5);
	disjSets.setunion(2, 3);
	cout << 4 << "==" << disjSets.size(3) << endl;
	disjSets.setunion(1, 3);
	cout << 6 << "==" << disjSets.size(6) << endl;

    cout << "Disjoint Sets test complete" << endl;

    return 0;
}
