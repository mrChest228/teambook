// GNU_pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// oset
template <class T> using oset = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>; // less_equal <T> for omultiset

//st.key_by_order(i);
//st.order_of_key(x);

template <class T>
omultiset <T>::iterator find(const omultiset <T> &st, int x) {
    int num = st.order_of_key(x);
    if (num == st.size())
        return st.end();
    auto it = st.find_by_order(num);
    return (*it == x ? it : st.end());
}

// Hash Maps
unordered_map <int, string> mp;
gp_hash_table <int, string> mp; //Примерно 3x быстрее unordered_map, использует 1.5x памяти, нет mp.count(), но есть mp.find() != mp.end()

template <class T> using priQue = priority_queue <T, vector <T>, greater <T>>;
