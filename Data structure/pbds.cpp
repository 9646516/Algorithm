#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;
/*
定义一颗红黑树
int 关键字类型
null_type无映射(低版本g++为null_mapped_type)
less<int>从小到大排序
rb_tree_tag 红黑树（splay_tree_tag）
tree_order_statistics_node_update结点更新
插入t.insert();
删除t.erase();
Rank:t.order_of_key();
第K值:t.find_by_order();
前驱:t.lower_bound();
后继t.upper_bound();
a.join(b)b并入a 前提是两棵树的key的取值范围不相交
a.split(v,b)key小于等于v的元素属于a，其余的属于b
T.lower_bound(x)   >=x的min的迭代器
T.upper_bound((x)  >x的min的迭代器
T.find_by_order(k) 有k个数比它小的数
*/

#include<ext/pb_ds/priority_queue.hpp>
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int> >,pairing_heap_tag> heap;
/*
binary_heap_tag
binomial_heap_tag
rc_binomial_heap_tag
pairing _heap_tag
thin_heap_tag
*/ 
/*
priority_queue()默认构造函数
priority_queue(const priority_queue &other) 用另一个优先队列来构造
size()用法同std
empty()用法同std
push(const_reference r_val)注意push返回point_iterator
top()没区别…
pop()没什么好说的
point_iterator对应某元素的迭代器
erase(point_iterator it)删除对应点
modify(point_iterator it,const_reference r_new_val)修改对应点的值(这是优化dijkstra神方法,均摊复杂度O(1))
clear()基本没什么用,还不如重新定义一个…
join(priority_queue &other)神方法*2,白送可并堆啊,还是O(1)的,注意合并后other会被清空
split(Pred prd,priority_queue &other)拆分,但好像没什么用
其他迭代器同std
*/
