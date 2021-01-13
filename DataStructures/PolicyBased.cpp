#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/tree_policy.hpp>      // Including tree_order_statistics_node_update

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

ordered_set X;
X.insert(1);
X.find_by_order(0);  //pointer 0-indexed element
X.order_of_key(-5);  //number of items strictly smaller than
end(X), begin(X);
