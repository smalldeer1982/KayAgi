# Heavy Intervals

## 题目描述

[Shiki - Pure Ruby](https://soundcloud.com/shiki-8/pure-rubyversoundcloud)

⠀



You have $ n $ intervals $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ , such that $ l_i < r_i $ for each $ i $ , and all the endpoints of the intervals are distinct.

The $ i $ -th interval has weight $ c_i $ per unit length. Therefore, the weight of the $ i $ -th interval is $ c_i \cdot (r_i - l_i) $ .

You don't like large weights, so you want to make the sum of weights of the intervals as small as possible. It turns out you can perform all the following three operations:

- rearrange the elements in the array $ l $ in any order;
- rearrange the elements in the array $ r $ in any order;
- rearrange the elements in the array $ c $ in any order.

However, after performing all of the operations, the intervals must still be valid (i.e., for each $ i $ , $ l_i < r_i $ must hold).

What's the minimum possible sum of weights of the intervals after performing the operations?

## 说明/提示

In the first test case, you can make

- $ l = [8, 3] $ ;
- $ r = [23, 12] $ ;
- $ c = [100, 100] $ .

In that case, there are two intervals:

- interval $ [8, 23] $ with weight $ 100 $ per unit length, and $ 100 \cdot (23-8) = 1500 $ in total;
- interval $ [3, 12] $ with weight $ 100 $ per unit length, and $ 100 \cdot (12-3) = 900 $ in total.

The sum of the weights is $ 2400 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 2400 $ .

In the second test case, you can make

- $ l = [1, 2, 5, 20] $ ;
- $ r = [3, 4, 10, 30] $ ;
- $ c = [3, 3, 2, 2] $ .

In that case, there are four intervals:

- interval $ [1, 3] $ with weight $ 3 $ per unit length, and $ 3 \cdot (3-1) = 6 $ in total;
- interval $ [2, 4] $ with weight $ 3 $ per unit length, and $ 3 \cdot (4-2) = 6 $ in total;
- interval $ [5, 10] $ with weight $ 2 $ per unit length, and $ 2 \cdot (10-5) = 10 $ in total;
- interval $ [20, 30] $ with weight $ 2 $ per unit length, and $ 2 \cdot (30-20) = 20 $ in total.

The sum of the weights is $ 42 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 42 $ .

## 样例 #1

### 输入

```
2
2
8 3
12 23
100 100
4
20 1 2 5
30 4 3 10
2 3 2 3```

### 输出

```
2400
42```

# 题解

## 作者：Sikiru (赞：5)

记 $ diff = r - l $，容易想到要让尽量小的 $ diff $ 匹配尽量大的 $ c $。

$ diff $ 的总和是一定的，故可以从小到大枚举 $ r $，匹配当前最大的比它小的 $ l $。

这个过程可以用栈来实现。

```cpp
sort(l, l + n);
sort(r, r + n);

int p = 0;
stack<int> s;
for (int i = 0; i < n; ++i) {
    while (l[p] < r[i] && p < n) {
        s.push(l[p]);
        ++p;
    }
    diff[i] = r[i] - s.top();
    s.pop();
}
```

最后按照 $ diff $ 从小到大，$ c $ 从大到小进行匹配，求解答案。


```cpp
ll ans = 0;
sort(c, c + n);
sort(diff, diff + n); // need to sort
for (int i = 0; i < n; ++i) {
    ans += (ll)diff[i] * c[n - i - 1];
}
cout << ans << endl;
```

---

## 作者：Withershine (赞：2)

一种似乎更~~快~~抽象的解法？

# 正文
看这道题，给定序列 $l,r,c$，要求重构 $l,r,c$ 使得 $\sum_{i=1}^n(r_i-l_i) \times c_i$ 最小。

首先可以想到的就是尽量让小的 $r_i-l_i$ 乘上大的 $c_i$。这样子看来 $c_i$ 几乎不需要更多的处理，仅需从小到大（或从大到小）排个序。

来看如何求出优秀的 $r_i-l_i$。

对于每一个 $r_i-l_i$，要使它们的差最小，最好的方法自然是使这两个数尽可能地相近并且 $l_i<r_i$ 仍成立。因为题目中保证了初始序列的 $l$ 与 $r$ 满足 $l_i<r_i$。所以不存在构造不出满足目标的 $l,r$ 序列。

假设已经找出了 $n$ 个最优的 $r_i-l_i$，分别是 $rl_1,rl_2 \sim rl_n$。将它们展开后再合并会发现，无论 $rl_i$ 的具体值是什么，始终会满足:

$$\sum _{i=1}^n rl_i=\sum_{j=1}^n r_j - \sum _{k=1}^n l_k$$

说明在保证 $rl$ 的选择最优的情况下，不管怎么排列并不会影响最终结果。这应该是显而易见的。

贪心的考虑一下，对于每个 $r_i$，找到比它小的最大的 $l_j$ 匹配，得到的 $rl$ 即是最小。若有多个 $r$ 匹配同一个 $l$。则让最小的 $r$ 匹配（能小则小）。

~~下面内容过于抽象所以请移步其它题解~~。

由于最近再练平衡树，练得脑子有点抽，诶？$l_i,r_i$ 互不相同。比 $r_i$ 小的最大值？于是自然而然地用到了三棵平衡树，来维护上面的 $r,l$ 以及 $rl$。并且自己又非常懒惰，所以使用了 [pb_ds](https://zhuanlan.zhihu.com/p/648274705)。

头文件：
```cpp
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>//平衡树
using namespace __gnu_pbds;
```

定义：
```cpp
tree<ll , null_type , std::less<ll> , rb_tree_tag , tree_order_statistics_node_update> L , R;
tree<pair<ll , ll> , null_type , std::less<pair<ll , ll>> , rb_tree_tag , tree_order_statistics_node_update> RL;

```

在代码中用了如下操作：

1. `insert` 插入一个数。代码内使用 `L.insert(l)`。

2. `erase` 擦除一个数或迭代器。代码内使用 `L.erase(nl)`。

3. `lower_bound` 返回指向首个不小于给定键的元素的迭代器。代码内使用 `ll nl = *(--L.lower_bound(nr));`（注：自减操作是为了找到比 $nr$ 小的最大值）。

4. `order_of_key(x)` 返回 $x$ 以比较的排名。代码内使用 `ll order = RL.order_of_key({rl , 0});`。

5. `find_by_order(x)` 返回的排名 $x$ 所对应元素的迭代器。代码内使用 `ll rl = RL.find_by_order(0) -> first;`。

当然，功能多多，码量远小于手写平衡树~~只是比赛时没什么用~~。

最后代码复杂度 $O(Tn \log n)$，勉强能看。

PS：魔怔人平衡树学傻了。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>//平衡树
using namespace __gnu_pbds;
using namespace std;
tree<ll , null_type , std::less<ll> , rb_tree_tag , tree_order_statistics_node_update> L , R;
tree<pair<ll , ll> , null_type , std::less<pair<ll , ll>> , rb_tree_tag , tree_order_statistics_node_update> RL;
ll T , n , l , r , c[200005];
inline bool cmp(ll x , ll y)
{
    return x > y;
}
ll sum;
signed main()
{
    // freopen("in.in" , "r" , stdin);
    // freopen("out.out" , "w" , stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--)
    {
        ll idx = 0;
        cin >> n;
        fr(i , 1 , n)
        {
            cin >> l;
            L.insert(l);
        }
        fr(i , 1 , n)
        {
            cin >> r;
            R.insert(r);
        }
        fr(i , 1 , n)
        {
            cin >> c[i];
        }
        fr(i , 1 , n)
        {
            ll nr = *(R.find_by_order(0));
            ll nl = *(--L.lower_bound(nr));
            RL.insert({nr - nl , ++idx});
            L.erase(nl);
            R.erase(nr);
        }
        sort(c + 1 , c + n + 1 , cmp);
        sum = 0;
        fr(i , 1 , n)
        {
            ll rl = RL.find_by_order(0) -> first;
            sum += rl * c[i];
            ll order = RL.order_of_key({rl , 0});
            RL.erase(RL.find_by_order(order));
        }
        cout << sum << '\n';  
    }
    return 0;
}
```


---

## 作者：zcxnb (赞：1)

~~小清新贪心题。~~

显然我们是要求出来一个降序序列 $r_i-l_i$ 使得其每一位乘上升序排序的 $c_i$ 得出来的结果最小。

考虑如何构造出对应的 $l_i$ 和 $r_i$ 呢？

我们先将 $l,r$ 序列排好序，然后考虑以下两种组合情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/kcsloi0l.png)

所以我们只需要让在 $l_i<r_i$ 这个限制范围内使得 $l_i$ 尽量接近 $r_i$，我们可以用栈来解决这个问题。

以下是AC代码。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,cnt,t;
int l[N],r[N],c[N],s[N],ans[N];
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		cnt=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&l[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&r[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&c[i]);
		}
		sort(c+1,c+1+n);
		sort(l+1,l+1+n);
		sort(r+1,r+1+n);
		for(int i=1,j=1;i<=n;i++){
			while(l[j]<r[i]&&j<=n){
				s[++cnt]=l[j];
				j++;
			}
			// printf("%lld %lld\n",r[i],s[cnt]);
			ans[i]=r[i]-s[cnt--];
		}
		sort(ans+1,ans+1+n,cmp);
		int tot=0;
		for(int i=1;i<=n;i++){
			tot+=ans[i]*c[i];
		}
		printf("%lld\n",tot);
	}
}
```

---

## 作者：1234567890sjx (赞：1)

显然为了让答案最小，可以让 $r_i-l_i$ 的最小来匹配 $c_i$ 的最大值。

因此将 $l_i$ 和 $r_i$ 从小到大排序，对于每一个 $l_i$ 找到严格大于 $l_i$ 的最小的 $r_i$，可以用栈来模拟。

全部匹配完之后按照新的每一组的 $r_i-l_i$ 从小到大排序，将 $c$ 从大到小排序，按照顺序直接匹配即可。

时间复杂度 $O(n\log n)$。代码实现的不太好。[代码](https://www.luogu.com.cn/paste/ah1ngsts)

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1909C)

vector 真是害人不浅。

首先判断当 $l$ 跟 $r$ 配对完之后与 $c$ 的配对。

我们使用数组 $v_i$ 记录 $r_i-l_i$。小学奥数告诉我们，当两个数之间差值越大那么两数乘积越小，所以我们肯定在 $v$ 中找最小的数与 $c$ 中最大的数配对，然后把这两个数去掉，接着继续进行此操作，可证一定使答案最小。

接下来是 $l$ 与 $r$ 的配对。不难发现，我们要答案小就要尽可能让 $v$ 当中越小的数越多，越小的数越小，才能更好地分担 $c$ 中大的数。那么就把 $l$ 跟 $r$ 排序，接着枚举 $r_i$，找 $l$ 中与它差值最小且小于它的数，和它配对，然后再 $l$ 中删除这个数。

这个 $l$ 可用链表实现，但我不会，用了 vector，然后本来过了的，结果好像后来被 hack 了。

于是放了个并查集来维护一个点离它最近的比它小的可使用的下标。很简单的做法。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
long long l[100010],r[100010],c[100010];
long long v[100010],ans=0;
int fa[100010];
inline int find(int k)
{
	if(k==fa[k]) return k;
	return fa[k]=find(fa[k]);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin>>n;
		for(register int i=1;i<=n;i++) cin>>l[i],fa[i]=i;
		for(register int i=1;i<=n;i++) cin>>r[i];
		for(register int i=1;i<=n;i++) cin>>c[i];
		sort(l+1,l+n+1),sort(r+1,r+n+1),sort(c+1,c+n+1);
		for(register int i=1;i<=n;i++)
		{
			int k=lower_bound(l+1,l+n+1,r[i])-l;
			k--;
			k=find(k);
			v[i]=r[i]-l[k];
			fa[k]=k-1;
		}
		sort(v+1,v+n+1);
		for(register int i=1;i<=n;i++) ans+=v[i]*c[n-i+1];
		printf("%lld\n",ans),ans=0;
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

## 思路：

这道题因为 $r-l$ 的总值是不变的，所以最小值就是用最小的 $r-l$ 乘最大的 $c$，以此类推。然后我们用栈将所有的 $r-l$ 求出来再进行排序然后将 $l-r$ 与 $c$ 相乘再输出最终的值就完成了。 

## 代码：


```cpp
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
const int N=1e5+5;
long long t,n;
long long l[N],r[N],c[N];
long long d[N];
long long ii=1,ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>l[i];
		for(int i=1;i<=n;i++) cin>>r[i];
		for(int i=1;i<=n;i++) cin>>c[i];
		sort(l+1,l+n+1);
		sort(r+1,r+n+1);
		stack<int> s;
		ii=1,ans=0;
		for(int i=1;i<=n;i++) {
		    while(l[ii]<r[i]&&ii<=n){
		        s.push(l[ii]);
		        ii++;
		    }
		    d[i]=r[i]-s.top();
		    s.pop();
		}
		sort(c+1,c+n+1);
		sort(d+1,d+n+1);
		for(int i=1;i<=n;i++) ans+=d[i]*c[n-i+1];
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：fls233666 (赞：0)

观察式子 $\sum^{n}_{i=1}(r_i-l_i) \times c_i$ ，为了让结果尽可能小，考虑尽可能让小的 $c_i$ 匹配大的 $r_i-l_i$。

同时我们要尽可能减小 $r_i-l_i$ 的值，考虑在满足 $l<r$ 的前提下，让每个 $r$ 去匹配尽可能大的 $l$。这时候需要用数据结构来维护 $l$，让我们能够尽可能快地去找到未匹配的，最大并且满足条件的 $l$。这里可以使用栈，也可以使用堆。

对于每一对匹配完成的区间 $[l,r]$，计算 $r-l$，并把这个值排序，然后跟 $c$ 匹配并统计答案。这里笔者使用了堆排序来实现。

下面放上代码：[栈匹配+堆排序](https://www.luogu.com.cn/paste/concgt9d)，[堆匹配+堆排序](https://www.luogu.com.cn/paste/ucmkbtz7)。

---

