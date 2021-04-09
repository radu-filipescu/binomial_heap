#include <bits/stdc++.h>

using namespace std;

ifstream fin( "heap.in" );
ofstream fout( "heap.out" );

const int INF = 2000000001;

struct nod {
    nod *p, *child, *sibling;
    int val, grad;
};

int top( list<nod*> &h ) {
    int minn = INF;

    for( list<nod*>::iterator it = h.begin(); it != h.end(); it++ )
        minn = min( minn, (*it) -> val );

    return minn;
}

void adjust2( list<nod*> & h ) {
    list<nod*> _ans;

    for( list<nod*>::iterator it = h.begin(); it != h.end(); it++ ) {
        list<nod*>::iterator it2 = it;
        list<nod*>::iterator it3 = it;
        it2++;
        it3++;
        it3++;

        if( it2 != h.end() && (*it) -> grad == (*it2) -> grad  && ( it3 == h.end() || (*it2) -> grad != (*it3) -> grad ) ) {
            if( (*it) -> val <= (*it2) -> val ) {
              (*it2) -> p = (*it);
              (*it2) -> sibling = (*it) -> child;
              (*it)  -> child = (*it2);
              (*it)  -> grad++;

              _ans.push_back( (*it) );
              it++;
            }
            else {
              (*it) -> p = (*it2);
              (*it) -> sibling = (*it2) -> child;
              (*it2)  -> child = (*it);
              (*it2)  -> grad++;

              _ans.push_back( (*it2) );
            }
        }
        else
            _ans.push_back( (*it) );
    }

    h = _ans;
}

void adjust( list<nod*> & h ) {
    list<nod*> _ans;

    for( list<nod*>::iterator it = h.begin(); it != h.end(); it++ ) {
        list<nod*>::iterator it2 = it;
        list<nod*>::iterator it3 = it;
        it2++;
        it3++;
        it3++;

        if( it2 != h.end() && (*it) -> grad == (*it2) -> grad  && ( it3 == h.end() || (*it2) -> grad != (*it3) -> grad ) ) {
            if( (*it) -> val <= (*it2) -> val ) {
              (*it2) -> p = (*it);
              (*it2) -> sibling = (*it) -> child;
              (*it)  -> child = (*it2);
              (*it)  -> grad++;

              if( it3 == h.end() || (*it3)->grad != (*it)->grad ) {
                _ans.push_back( (*it) );
                it++;
              }
              else (*it2) = (*it);
            }
            else {
              (*it) -> p = (*it2);
              (*it) -> sibling = (*it2) -> child;
              (*it2)  -> child = (*it);
              (*it2)  -> grad++;

              //if( it3 == h.end() || (*it3)->grad != (*it2)->grad )
              //  _ans.push_back( (*it2) );
            }
        }
        else
            _ans.push_back( (*it) );
    }

    h = _ans;
}

list<nod*> merge_heaps( list<nod*> &h1, list<nod*> &h2 ) {
    list<nod*> _ans;

    list<nod*>::iterator it1 = h1.begin(), it2 = h2.begin();

    while( it1 != h1.end() && it2 != h2.end() ) {
        if( (*it1) -> grad < (*it2) -> grad ) {
            _ans.push_back( *it1 );
            it1++;
        }
        else {
            _ans.push_back( *it2 );
            it2++;
        }
    }

    while( it1 != h1.end() ) {
        _ans.push_back( *it1 );
        it1++;
    }

    while( it2 != h2.end() ) {
        _ans.push_back( *it2 );
        it2++;
    }

    adjust( _ans );

    return _ans;
}

void push( list<nod*>& h, int val ) {
    nod *tmp = new nod;

    tmp -> child = tmp -> p = tmp -> sibling = NULL;
    tmp -> grad = 0;
    tmp -> val = val;

    h.push_front( tmp );
    adjust( h );
}

void pop( list<nod*>& h ) {
    int minn = INF;
    nod *p = NULL;
    list<nod*>::iterator it_p;

    for( list<nod*>::iterator it = h.begin(); it != h.end(); it++ )
        if( (*it)->val < minn ) {
            minn = (*it)->val;
            p = (*it);
            it_p = it;
        }

    list<nod*> sons_of_deleted;

    /// sons of deleted root, in reverse order ( because of their degree )
    for( nod *it = (*p).child; it != NULL; it = it -> sibling )
        sons_of_deleted.push_front( it );

    /// remove the minimum root from the heap
    h.erase( it_p );

    /*fout << "****\n";
    for( list<nod*>::iterator it = sons_of_deleted.begin(); it != sons_of_deleted.end(); it++ )
        fout << (*it)->val << ' ';
    fout << "\n*****\n";*/

    /// merge the current heap with the heap made of the sons of deleted root
    list<nod*> tmp = merge_heaps( h, sons_of_deleted );
    h = tmp;

    /// prevent memory leaks
    delete p;
}

list<nod*> H;

int main()
{
    int N, op, x;

    fin >> N;

    for( int i = 1; i <= N; ++i ) {
        fin >> op;
        if( op == 1 ) {
            fin >> x;
            push( H, -x );
        }
        else {
            fout << -top( H ) << '\n';
            pop( H );
        }
    }

    /*nod *mzg = new nod;

    mzg -> child = mzg -> p = mzg -> sibling = NULL;
    mzg -> grad = 0;
    mzg -> val = 15;

    H.push_front( mzg );
    adjust2( H );

    fout << '\n' << H.size() << '\n';
    for( list<nod*>::iterator it = H.begin(); it != H.end(); it++ )
        fout << (*it) -> val << ' ';
    fout << '\n';
    for( list<nod*>::iterator it = H.begin(); it != H.end(); it++ )
        fout << (*it) -> grad << ' ';
        */


    return 0;
}
