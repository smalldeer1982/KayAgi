# The Great Equalizer

## 题目描述

Tema bought an old device with a small screen and a worn-out inscription "The Great Equalizer" on the side.

The seller said that the device needs to be given an array $ a $ of integers as input, after which "The Great Equalizer" will work as follows:

1. Sort the current array in non-decreasing order and remove duplicate elements leaving only one occurrence of each element.
2. If the current length of the array is equal to $ 1 $ , the device stops working and outputs the single number in the array — output value of the device.
3. Add an arithmetic progression { $ n,\ n - 1,\ n - 2,\ \ldots,\ 1 $ } to the current array, where $ n $ is the length of the current array. In other words, $ n - i $ is added to the $ i $ -th element of the array, when indexed from zero.
4. Go to the first step.

To test the operation of the device, Tema came up with a certain array of integers $ a $ , and then wanted to perform $ q $ operations on the array $ a $ of the following type:

1. Assign the value $ x $ ( $ 1 \le x \le 10^9 $ ) to the element $ a_i $ ( $ 1 \le i \le n $ ).
2. Give the array $ a $ as input to the device and find out the result of the device's operation, while the array $ a $ remains unchanged during the operation of the device.

Help Tema find out the output values of the device after each operation.

## 说明/提示

Let's consider the first example of the input.

Initially, the array of numbers given as input to the device will be $ [6, 4, 8] $ . It will change as follows: $ $$$[6, 4, 8] \rightarrow [4, 6, 8] \rightarrow [7, 8, 9] \rightarrow [10, 10, 10] \rightarrow [10] $ $ </p><p>Then, the array of numbers given as input to the device will be  $ \[6, 10, 8\] $ . It will change as follows:  $ $ [6, 10, 8] \rightarrow [6, 8, 10] \rightarrow [9, 10, 11] \rightarrow [12, 12, 12] \rightarrow [12] $ $ </p><p>The last array of numbers given as input to the device will be  $ \[6, 10, 1\] $ . It will change as follows:  $ $ [6, 10, 1] \rightarrow [1, 6, 10] \rightarrow [4, 8, 11] \rightarrow [7, 10, 12] \rightarrow [10, 12, 13] \rightarrow [13, 14, 14] \rightarrow [13, 14] \rightarrow [15, 15] \rightarrow [15] $ $$$

## 样例 #1

### 输入

```
4
3
2 4 8
3
1 6
2 10
3 1
5
1 2 2 2 2
1
5 3
2
5 6
7
1 2
1 7
1 7
2 5
1 2
2 7
2 2
5
2 5 1 10 6
10
1 7
4 8
2 5
1 4
2 8
3 4
1 9
3 7
3 4
3 1```

### 输出

```
10 12 15 
4 
10 8 8 9 8 12 2 
14 12 12 11 11 10 11 10 11 14```

# 题解

## 作者：Purslane (赞：9)

# Solution

送分。

你应该注意到进行一次操作之后最大数还是最大数，最小数还是最小数，只不过有些重复的数会被删掉。而最大数每次只加一，因此我们只需要知道进行多少次操作即可。

而操作一次会使所有相邻两个数（从小到大排序后）的差值减一，最后这个差值会减到 $0$。因此操作次数就是差值的最大值。

用两个 multiset 维护即可。

这边提供维护 multiset 的代码：

```cpp
void add(int u) {
	auto it=st.lower_bound(u);
	if(it!=st.end()) {
		del.insert(*it-u);
	}
	if(it!=st.begin()) {
		auto It=it;
		--It;
		del.insert(u-*It);
	}
	if(it!=st.end()&&it!=st.begin()) {
		auto It=it; --It;
		del.erase(del.find(*it-*It));
	}
	st.insert(u);
	return ;
}
void delt(int u) {
	auto it=st.find(u);
	if(it!=st.begin()) {
		auto It=it;
		--It;
		del.erase(del.find(u-*It));
	}
	if(it!=(--st.end())) {
		auto It=it;
		++It;
		del.erase(del.find(*It-u));
	}
	if(it!=st.begin()&&it!=(--st.end())) {
		auto it1=it,it2=it;
		--it1,++it2;
		del.insert(*it2-*it1);
	}
	st.erase(it);
	return ;
}
```

---

## 作者：Imken (赞：6)

[CF Link](https://codeforces.com/contest/1862/problem/G) | [Luogu Link](https://www.luogu.com.cn/problem/CF1862G)

[Blog](https://blog.imken.moe/archives/532) 可能观感更佳。

昨天比赛写的一道非常有意思的题，完赛前 $5$ 分钟想出的解法（然后没写出来）。

主要讲的是找规律，然后没有很严谨的数学证明。

## 题意

定义一个对序列的操作为：

1. 升序排序 + 去重
2. 如果只剩一个元素就返回这个元素
3. 将所有元素 $a_i$（下标从 $0$ 开始）加上 $n - i$，并回到步骤 $1$。

有 $q$ 次询问，每次询问修改原序列上下标为 $i$ 的一个数，在每次修改后求出这个新序列的操作值。

## 解法

找规律。如果数感好并且想象力比较丰富的话，可以大概看出来一些规律。

原序列的顺序对操作结果没有影响，所以这里把样例升序排序。就拿题目给定的样例解释看：

```yaml
[4, 6, 8] -> 10
[6, 8, 10] -> 12
[1, 6, 10] -> 15
```

排序之后，应该不难看出序列到结果的一个规律：

结果 $=$ 原序列最大值 $+$ 排序后某连续两个数的差值

比方说，拿 $[1, 6, 10] \to 15$ 举例：$ 15 = 10 + (6 - 1) $

到底是哪两个数的差值可以写一个暴力来进一步找规律。

```cpp
void bruteforce()
{
	int n = 3;
	vector<int> arr(n);
	for (auto &x : arr) cin >> x;
	while (arr.size()) {
		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());
		if (arr.size() == 1) {
			cout << arr[0] << endl;
			return;
		}
		for (int i = 0; i < arr.size(); i++) {
			arr[i] += n - i;
		}
	}
}
```

手构几组数据，应该不难看出，这个差值是*最大的连续两个数的差值*。

这个时候解法就出来了。可以用一个 multiset 维护序列内的数值（可以通过寻找前驱/后继来动态更新排序后相邻元素的差值），再用另一个 multiset 维护排序后相邻元素的差值。

修改时具体操作捋一下，就几个：

1. 从维护数值的 multiset 里寻找到旧的 $x$ 的前驱和后继；
2. 从维护差值的 multiset 里删除旧的 $x$ 和它的前驱/后继的差值，插入其前驱与后继的差；
3. 删除旧的 $x$，插入新的 $x$；
4. 在维护差值的 multiset 里插入新的 $x$ 与它前驱/后继的差值，删除前驱后继的差。

画个图就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/473mpn0h.png)

最后再注意一下边界条件就可以做出来了。

Code:

```cpp
// mt 存值，sp 存差值
multiset<int> mt, sp;

inline void solve()
{
	mt.clear(); sp.clear();
	i64 n;
	cin >> n;
	// 特判，否则会 RE
	if (n == 1) sp.insert(0);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		mt.insert(s[i]);
	}
	auto it = mt.begin();
	int last = *(it++);
	while (it != mt.end()) {
		sp.insert(*it - last);
		last = *(it++);
	}
	cin >> q;
	while (q--) {
		cin >> x >> v;
		// find s[x] and unbind
		auto it = mt.find(s[x]);
		int beg = -1, end = -1;
		// has pre
		if (it != mt.begin()) {
			auto rit = it--;
			beg = *it;
			sp.erase(sp.find(*rit - *it));
			it++;
		}
		// has nxt
		auto lit = it++;
		if (it != mt.end()) {
			sp.erase(sp.find(*it - *lit));
			end = *it;
		}
		mt.erase(lit);
		// has pre and nxt
		if (beg != -1 && end != -1) {
			sp.insert(end - beg);
		}
		// insert v and bind
		beg = -1; end = -1;
		s[x] = v;
		it = mt.insert(s[x]);
		// has pre
		if (it != mt.begin()) {
			auto rit = it--;
			beg = *it;
			sp.insert(*rit - *it);
			it++;
		}
		// has nxt
		lit = it++;
		if (it != mt.end()) {
			sp.insert(*it - *lit);
			end = *it;
		}
		// has pre and nxt
		if (beg != -1 && end != -1) {
			sp.erase(sp.find(end - beg));
		}
		cout << *sp.rbegin() + *mt.rbegin() << ' ';
	}
	cout << '\n';
}
```


---

## 作者：One_JuRuo (赞：2)

## 思路

对于一个数组，每次操作会缩短排序后的数组的相邻两个数的差距，所以总共会执行 $k$ 次操作，其中，$k$ 为排序后的数组的相邻两个数的最大差距。

因为每次操作都会对最大数加 $1$，所以答案就是 $\text{数组中的最大数} + \text{排序后的数组的相邻两个数的最大差距}$。

因为修改操作修改的位置是按照原数组的位置而定的，所以如果每次修改操作都排序一遍的话，还需要在修改前再排一遍排回去，所以时间复杂度很高，必定会 TLE。

## TLE code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long v,id;}a[200005];
inline bool cmp(node a,node b){return a.v<b.v;}
inline bool cmp1(node a,node b){return a.id<b.id;}
long long T,n,q,x,b;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;++i) scanf("%lld",&a[i].v),a[i].id=i;
		scanf("%lld",&q);
		while(q--)
		{
			sort(a+1,a+n+1,cmp1);
			scanf("%lld%lld",&x,&b),a[x].v=b;
			sort(a+1,a+n+1,cmp);long long maxn=0;
			for(long long i=1;i<n;++i) maxn=max(maxn,a[i+1].v-a[i].v);
			printf("%lld ",a[n].v+maxn);
		}
		puts("");
	}
}
```

我们假设修改的位置是 $p$，排序后这个位置的前一个位置是 $pr$，后一个位置是 $ne$。

那么，相邻两数的差就最多更改两个地方，比如：原本的 $a[p]-a[pr]$ 与 $a[ne]-a[p]$ 会合并为 $a[ne]-a[pr]$，同样会更改的地方还有改后的位置前后。

所以，我们可以考虑维护两个 $\operatorname{multiset}$ 即可以出现重复元素的集合。

一个集合用于储存 $a$ 数组，一个集合用于储存排序后相邻元素的差值。

然后用迭代器快速修改和查询，注意特殊情况的判断。

**注：如果真的不是没有更好的方法，慎用迭代器。**

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],q,p,v;
multiset<int>s,c;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		if(n==1)//特判特殊情况
		{
			scanf("%d",&q);
			while(q--) scanf("%d%d",&p,&v),printf("%d ",v);
			puts("");
		}
		else
		{
			s.clear(),c.clear();//记得清空
			for(int i=1;i<=n;++i) s.insert(a[i]);
			for(auto i=++s.begin();i!=s.end();++i)
			{
				auto pr=i;
				--pr;
				c.insert(*i-*pr);
			}
			scanf("%d",&q);
			while(q--)
			{
				scanf("%d%d",&p,&v);
				auto i=s.find(a[p]),ne=i,pr=i;++ne,--pr;//找到对应位置以及位置前后
				if(i==s.begin()) c.erase(c.find(*ne-*i));//如果在最前面，只用删除位置后一段的差值
				else if(i==--s.end()) c.erase(c.find(*i-*pr));//如果在最后面，只用删除位置前一段的差值
				else c.erase(c.find(*ne-*i)),c.erase(c.find(*i-*pr)),c.insert(*ne-*pr);//否则，合并位置前后的差值
				s.erase(i),s.insert(v),i=s.find(v),ne=i,pr=i;++ne,--pr;//修改集合s，顺便找到对应位置及位置前后
				if(i==s.begin()) c.insert(*ne-*i);//如果在最前面，只用添加位置后的差值
				else if(i==--s.end()) c.insert(*i-*pr);//如果在最后面，只用添加位置前的差值
				else c.insert(*ne-*i),c.insert(*i-*pr),c.erase(c.find(*ne-*pr));//否则，拆开位置前后的差值
				a[p]=v;//记得修改原数组
				printf("%d ",*--s.end()+*--c.end());//数组最大值+差值最大值
			}
			puts("");
		}
	}
	return 0;
}
//使用迭代器会变得不幸！调了快一天了，最后还是和官方题解找不同调好的。
```

---

## 作者：happybob (赞：1)

很简单的结论。

发现有一步十分重要，就是去重。我们考虑对于有序的无重序列中两个数 $a_i$ 和 $a_j$，假设 $i<j$，$a_i$ 加上的是 $n-i$，$a_j$ 加上的是 $n-j$。因为 $a_j-a_i \geq j - i$，所以 $a_i + n - i \leq a_j + n - j$。所以无论怎么加，最终那个数都是从最大的数得到的。

一次操作，相邻两个数差减 $1$。所以答案等于最大数 $+$ 排序后相邻两个数差最大值。

容易用 `multiset` 维护。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int t, n, q;

int a[N];
map<int, int> cnt;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--)
    {
        set<int> s1;
        multiset<int> s2;
        cnt.clear();
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], s1.insert(a[i]), cnt[a[i]]++;
        for (auto it = ++s1.begin(); it != s1.end(); ++it)
        {
            auto g = it;
            --g;
            s2.insert(*it - *g);
        }
        cin >> q;
        while (q--)
        {
            int i, x;
            cin >> i >> x;
            auto it = s1.lower_bound(a[i]);
            if (cnt[a[i]] == 1 and it != --s1.end())
            {
                auto g = it;
                ++g;
                s2.erase(s2.find(*g - *it));
            }
            if (cnt[a[i]] == 1 and it != s1.begin())
            {
                auto g = it;
                --g;
                s2.erase(s2.find(*it - *g));
            }
            if (cnt[a[i]] == 1 and it != --s1.end() and it != s1.begin())
            {
                auto g1 = it, g2 = it;
                g1--, g2++;
                s2.insert(*g2 - *g1);
            }
            cnt[a[i]]--;
            cnt[x]++;
            if (cnt[a[i]] == 0) s1.erase(it);
            a[i] = x;
            s1.insert(x);
            it = s1.lower_bound(x);
            if (cnt[x] == 1 and it != --s1.end())
            {
                auto g = it;
                ++g;
                s2.insert(*g - *it);
            }
            if (cnt[a[i]] == 1 and it != s1.begin())
            {
                auto g = it;
                --g;
                s2.insert(*it - *g);
            }
            if (cnt[a[i]] == 1 and it != --s1.end() and it != s1.begin())
            {
                auto g1 = it, g2 = it;
                g1--, g2++;
                s2.erase(s2.find(*g2 - *g1));
            }
            if (n == 1) cout << x << " ";
            else if (s1.size() == 1) cout << *s1.begin() << " ";
            else cout << *s1.rbegin() + *s2.rbegin() << " ";
        }
        cout << "\n";
    }
    return 0;   
}
```


---

## 作者：TernaryTree (赞：1)

简单题啊。

首先差分数列每次操作全 $-1$。也就是说操作次数是 $k=\max d_i$，其中 $d$ 表示排序后的 $a$ 的差分数组。

注意到 $a$ 中最大数每次 $+1$，而最大数在 $k$ 次以内都在同一个位置，进行 $k$ 次后这个数是 $k+\max a_i$。

也就是说答案是 $\max a_i+\max d_i$。

维护两个 multiset，一个维护 $a$，一个维护 $d$ 即可。

注意 $n=1$ 以及插入删除在开头结尾的情况。

[Code with 火车头 + FIO 快读 8.40 KB](https://www.luogu.com.cn/paste/64czcaim)

---

## 作者：lfxxx (赞：1)

首先这个查询操作很迷，考虑先化简查询操作。

不难发现由于每次是加上一个逆的等差序列，因此一次操作完每个数与它的前驱之差一定会减少，因此加上等差序列的次数就等于全局每个数与它的前驱之差最大值。

又因为会排序去重，所以最后剩下来的数一定是最开始的数一路加过来的，至此我们发现答案就是全局每个数与它的前驱之差最大值加上全局最大值。

考虑怎么维护这个东西，显然可以使用 FHQ treap 维护这件事，我们需要维护子树最大差，最小值，最大值就可以合并信息，在点修时先把原来的数删掉，在插入新的数。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int n,q;
int a[maxn];
struct Node{
	int val,ls,rs,w,mx,mi,ans;
}treap[maxn];
stack<int> brush;
int tot;
int rt;
int clone(int w){
	int New;
    if(brush.size()>0) New=brush.top(),brush.pop();
    else New=++tot;
	treap[New].val=rand();
	treap[New].ls=0;
	treap[New].rs=0;
	treap[New].w=w;
	treap[New].mi=treap[New].mx=w;
	treap[New].ans=0;
	return New;
}
inline void pushup(int cur){
	treap[cur].ans=0;
	treap[cur].ans=max(treap[treap[cur].ls].ans,treap[treap[cur].rs].ans);
	if(treap[cur].ls!=0) treap[cur].ans=max(treap[cur].w-treap[treap[cur].ls].mx,treap[cur].ans);
	if(treap[cur].rs!=0) treap[cur].ans=max(treap[treap[cur].rs].mi-treap[cur].w,treap[cur].ans);
	treap[cur].mx=treap[cur].mi=treap[cur].w;
	if(treap[cur].rs!=0) treap[cur].mx=treap[treap[cur].rs].mx;
	if(treap[cur].ls!=0) treap[cur].mi=treap[treap[cur].ls].mi;
}
inline int merge(int x,int y){
    if(!x||!y) return x+y;
    if(treap[x].val<treap[y].val){
        treap[x].rs=merge(treap[x].rs,y);
        pushup(x);
        return x;
    }
    else{
        treap[y].ls=merge(x,treap[y].ls);
        pushup(y);
        return y;
    }
}
inline void split(int cur,int x,int &l,int &r) {
	if(cur==0){
		l=r=0;
		return ;
	}
	if(treap[cur].w>x){
		r=cur;
		split(treap[cur].ls,x,l,treap[cur].ls);
	}
	else{
		l=cur;
		split(treap[cur].rs,x,treap[cur].rs,r);
	}
	pushup(cur);
}
void dfs(int u){
	if(u==0) return ;
	dfs(treap[u].ls);
	cout<<treap[u].w<<' '<<treap[u].mx<<' '<<treap[u].mi<<'\n';
	dfs(treap[u].rs);
}
void insert(int w){
	int x=0,y=0,z=0;
	split(rt,w,x,z);
	y=clone(w);
	rt=merge(x,merge(y,z));
}
void erase(int w){
	int x=0,y=0,z=0;
	split(rt,w-1,x,y);
	split(y,w,y,z);
    brush.push(y);
	y=merge(treap[y].ls,treap[y].rs);
	rt=merge(x,merge(y,z));
}
void work(){
	rt=tot=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		insert(a[i]); 
	}
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		erase(a[x]);
		a[x]=y;
		insert(a[x]);
		cout<<treap[rt].mx+treap[rt].ans<<' ';
	}
	cout<<'\n';
}
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)work();
}
```


---

## 作者：Leonid (赞：1)

注意到升序排序后每次加等差数列的操作就是相邻元素的差值减 $1$，而我们在每次加法之后都需要去重，也就是数组始终是升序的，所以操作次数就是 $\max\limits_{i=1}^{n-1} {a_{i+1}-a_i}$。

注意到最大值永远只会加 $1$，那么题目要求的答案就是 $a_n+\max\limits_{i=1}^{n-1} {a_{i+1}-a_i}$。

对于 $a$ 数组题目要求单点修改，我们可以用两个 `multiset` 维护答案，一个用于维护最大值，另一个用于维护差值，最后输出两个 `multiset` 末尾的值之和即可。

注意判一下 $n=1$ 的情况。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define db double
#define ld long double

#define M 2000005
#define N 550
#define mod 998244353
#define inf 1e9
#define linf 1e18+7
#define eps 1e-15
#define delta 0.996

int T;
int n;
int a[M];
int q;

multiset<int> s,t;
multiset<int> :: iterator it;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		s.clear(); t.clear();
		for(int i=1;i<=n;++i) scanf("%d",&a[i]),s.insert(a[i]);
		for(auto i=s.begin();i!=prev(s.end());++i) t.insert(*next(i)-*i);
		scanf("%d",&q);
		while(q--){
			int u,x;
			scanf("%d %d",&u,&x);
			int pre=-1,nxt=-1;
			it=s.find(a[u]);
			if(it!=s.begin()){
				pre=*prev(it);
				t.erase(t.find(*it-pre));
			}
			if(it!=prev(s.end())){
				nxt=*next(it);
				t.erase(t.find(nxt-*it));
			}
			if(~pre&&~nxt){
				t.insert(nxt-pre);
			}
			s.erase(it);
			s.insert(x);
			it=s.find(x);
			pre=-1,nxt=-1;
			if(it!=s.begin()){
				pre=*prev(it);
				t.insert(*it-pre);
			}
			if(it!=prev(s.end())){
				nxt=*next(it);
				t.insert(nxt-*it);
			}
			if(~pre&&~nxt){
				t.erase(t.find(nxt-pre));
			}
			a[u]=x;
			printf("%d ",*prev(s.end())+(t.empty()?0:*prev(t.end())));
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

首先对样例的序列排序后找一下规律：

${4,6,8}\rightarrow{7,8,9}\rightarrow{10}$

${6,8,10}\rightarrow{9,10,11}\rightarrow{12}$

${1,6,10}\rightarrow{4,8,11}\rightarrow{7,10,12}\rightarrow{10,12,13}\rightarrow{13,14}\rightarrow{15}$

我们发现，每一次操作，**序列的最大值都只会增加 1**

那么也就是要求，经过多少次操作后序列会只剩一个数。

容易发现，每一次操作后相邻两个数的差都会减少 1，那么最终的操作次数就是这个序列排序后两两之间差的最大值。

那开两个 multiset，维护原数组和原数组两两间的差就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200005],q,ii,xx;
multiset<int> st;
multiset<int> ch;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		st.clear(),ch.clear();
		for(int i=1;i<=n;i++)cin>>a[i],st.insert(a[i]);
		if(n==1){
			cin>>q;
			while(q--){
				cin>>ii>>xx;
				cout<<xx<<" ";
			}
			cout<<"\n";
			continue;
		}
		cin>>q;
		for(auto it=st.begin();it!=st.end();it++){
			if(it==st.begin())continue;
			auto itt=it;itt--;
			ch.insert((*it)-(*itt));
		}
		for(int i=1;i<=q;i++){
			cin>>ii>>xx;
			auto it=st.find(a[ii]),itt=it;
			itt++;
			int qian=INT_MAX,hou=INT_MAX;
			if(it!=st.begin()&&itt!=st.end()){
				it--;
				qian=*it,hou=*itt;
				auto itch1=ch.find(a[ii]-qian);
				ch.erase(itch1);
				auto itch2=ch.find(hou-a[ii]);
				ch.erase(itch2);
				ch.insert(hou-qian);
			}
			else{
				if(it==st.begin()){
					hou=*itt;
					auto itch=ch.find(hou-a[ii]);
					ch.erase(itch);
				}
				if(itt==st.end()){
					it--;
					qian=*it;
					auto itch=ch.find(a[ii]-qian);
					ch.erase(itch);
				}
			}	
			st.erase(st.find(a[ii]));
			st.insert(xx);
			it=st.find(xx),itt=it;
			itt++;
			qian=hou=INT_MAX;
			if(it!=st.begin()&&itt!=st.end()){
				it--;
				qian=*it,hou=*itt;
				auto itch1=ch.find(hou-qian);
				ch.erase(itch1);
				ch.insert(xx-qian),ch.insert(hou-xx);
			}
			else{
				if(it==st.begin()){
					hou=*itt;
					ch.insert(hou-xx);
				}
				if(itt==st.end()){
					it--;
					qian=*it;
					ch.insert(xx-qian);
				}
			}
			auto tti1=st.end(),tti2=ch.end();
			tti1--,tti2--;
			cout<<(*tti1)+(*tti2)<<" ";
			a[ii]=xx;
		}
		cout<<"\n";
	}
	return 0;
}
```

---

