# Heidi and Library (medium)

## 题目描述

Whereas humans nowadays read fewer and fewer books on paper, book readership among marmots has surged. Heidi has expanded the library and is now serving longer request sequences.

## 样例 #1

### 输入

```
4 100
1 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 1
1 2 2 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 2
1 2 3 1
```

### 输出

```
3
```

# 题解

## 作者：DPair (赞：7)

## 【题记】
写了一个小时左右，换了几种算法才调出来，手真的生了。。。

## 【注意】
这道题有一个坑点（~~其实是我自己脑残掉进去的，根本不坑~~），如果有掉进去的可以看看：

如果库存满了，哪怕你书马上买马上借出去，也是不行的，必须扔一本书才能买新的。

比如库存$1~2~3$，有人来借$4$，哪怕他借完之后再也没有人要$4$这本书了（就是说$4$废了），你也得忍痛割爱先扔一本库存的才能把$4$借出去。
## 【思路】
这道题有三个版本，最弱的数据范围才$80$（~~居然也是蓝题~~），最难的标算似乎是网络流费用流，我比较弱，所以这里还是讲一讲这个数据范围的解法。

题意很明了，你最多存$k$本书，超出的要扔掉，没有的要买进，于是想到要尽可能少买书，即尽可能让已有的书发挥最大作用。

于是想到了贪心。

再看数据范围，似乎是$O(nlogn)$级别的，于是又想到了堆（优先队列）。

然后就做完了。

## 【算法】
首先我们先考虑一个贪心策略， 方向肯定是从库存书效益的最大化下手，于是，当我们发现一本需要库存的新书时，应该先扔的一定是效益最小的。

那么效益怎么计算呢？也就是说，扔了哪一本书后面买书就可以少买一些呢？

**答案就是，先扔掉库存书中，下一次用最晚的书。**

这个维护好维护，用一个堆就行，下面主要还是证明一下为什么这个贪心策略是对的。

## 【证明】
这个最好还是意会。

首先，假设有两本书，一本先用到，称为$A$，另一本后用到，称为$B$。

那么，在下一次用$B$之前，$A$一定被用到过。

也就是说，如果你先扔了$A$，那么在用$B$之前一定会用到不止一次$A$，即可能买不止一次，最后用$B$时还是$A~B$都在库里（只是时间可能不同）。

但是，如果先扔了$A$，在用$B$之前至少用一次$A$，可能买的次数**多于一次**，但先扔$B$，在下一次用$B$之前对于$A~B$来说一定只用买一次书。

由此，对于$A~B$，先扔$B$一定优于$A$。

证毕。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int k, n;
int ans, tot, succ[400010];
bool b[400010];
pair <int, int> a[400010];
struct BOOK{
	int num, nxt;
	BOOK (int tmp1, int tmp2) : num(tmp1), nxt(tmp2) {}
	bool operator < (const BOOK &b) const
	{
		return nxt < b.nxt;
	}
	bool operator > (const BOOK &b) const
	{
		return nxt > b.nxt;
	}
	
};
priority_queue <BOOK> q;

int main()
{
	scanf("%d%d", &n, &k);
	for (register int i = 1;i <= n;i ++)
	{
		scanf("%d", &a[i].first);
	}
	for (register int i = n;i >= 1;i --)
	{
		if(!succ[a[i].first]) a[i].second = 0x3f3f3f3f;//如果这本书再也不会被用到了，可以考虑将下一次用到的位置设为无限大，因为它被扔掉显然最优。
		else a[i].second = succ[a[i].first];
		succ[a[i].first] = i;
	}
	for (register int i = 1;i <= n;i ++)
	{
		if(!b[a[i].first])
		{
			ans ++;
			tot ++;
			if(tot > k)
			{
				tot --;
				BOOK tp = q.top();
				q.pop();
				b[a[tp.num].first] = false;
			}
			b[a[i].first] = true;
		}
		q.push(BOOK(i, a[i].second));
	}
	printf("%d\n", ans);
}
```

---

## 作者：_edge_ (赞：2)

这里讲的是 $O(n \log n)$ 的做法，可以双倍经验。

~~据说有什么神仙网络流可以做，wtcl 想不明白。~~

考虑朴素的贪心，我们能装满则装满，不能装满就扔。

怎么扔？肯定是扔下一次用到时间比较远的书。

不严格证明一下，假如我们扔了一个，那么到了那个时刻还得再扔一个买回来，而如果我们扔了比较近的，那么近的那个时刻还得再买一个再扔一个，一种理想的情况是尽量让扔的操作少发生。

当然你也可以认为时间比较远的是不够优秀的。

知道了这个，我们用暴力去维护可以过掉 CF802A。

考虑用什么数据结构去维护，需要支持的操作是把时间远的弹掉，然后加入元素，很简单的是用堆来维护，但是我比较菜，不会处理堆内修改，即遇到一个在堆内的元素需要把它的权值修改一下。

类似的，修改权值这个操作可以交给 set 来完成。

记录元素权值和元素，然后遇到了就把他删掉，扔进去一个最新的。

因此时间复杂度是 $O(n \log n)$，同时常数稍大。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#define pb push_back
using namespace std;
const int INF=4e5+5;
int n,m,a[INF],vis[INF],L[INF];
vector <int> v[INF];
struct _node_queue {
	int dis_v,pos;
	bool operator < (const _node_queue &x) const {
		return x.dis_v<dis_v;
	}
};
multiset <_node_queue> q;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) 
		cin>>a[i],v[a[i]].pb(i);
	int ans=0;
	for (int i=1;i<=n;i++) {
		if (vis[a[i]]) {
			int x=a[i],y=L[a[i]];
			q.erase(q.find((_node_queue){y,x}));
			int it=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
			if (it<v[a[i]].size()) it=v[a[i]][it];
			else it=1e9;
			L[a[i]]=it;
			q.insert((_node_queue){it,a[i]});
			continue;
		}
		ans++;
		if (q.size()<m) {
			int it=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
			if (it<v[a[i]].size()) it=v[a[i]][it];
			else it=1e9;
			L[a[i]]=it;
			q.insert((_node_queue){it,a[i]});vis[a[i]]=1;
		}
		else {
			_node_queue xx=*q.begin();q.erase(q.find(*q.begin()));
			vis[xx.pos]=0;
//			cout<<xx.pos<<" weaijr\n";
			int it=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
			if (it<v[a[i]].size()) it=v[a[i]][it];
			else it=1e9;
			L[a[i]]=it;
			q.insert((_node_queue){it,a[i]});vis[a[i]]=1;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：fish_love_cat (赞：1)

简单贪心，然后忘记修改维护的信息调了一个小时 /qd

---

我们容易发现当架子满了的时候要扔书时，扔下一次使用最晚的书是不劣的。

为什么呢？

如果我们扔的不是这本最晚用到的书，那么在下一次用到它之前，我们除了现在买一次书外，扔掉的另一本下一次还得再买。这样算下来就多买了一次甚至更多，是不优的。

那么我们就应该扔最晚用的书。

考虑倒序统计下一次使用，然后利用优先队列处理。

注意如果当前需要的书已经在架上，需要更新优先队列中该书下一次的值（不然挂在第 $9$ 个点）。我们可以多加一本书覆盖原书来实现。

---

[代码](https://www.luogu.com.cn/paste/67z0e4eb)。

---

福利：

[六](https://www.luogu.com.cn/problem/P3419)[倍](https://www.luogu.com.cn/problem/P2088)[经](https://www.luogu.com.cn/problem/SP688)[验](https://www.luogu.com.cn/problem/CF802B)，[好](https://www.luogu.com.cn/problem/P4404)[耶](https://www.luogu.com.cn/problem/CF802A)！

甚至双倍[题](https://www.luogu.com.cn/article/tgf82p31)[解](https://www.luogu.com.cn/article/hga39xyp)！

---

## 作者：_Warfarin_ (赞：1)

## 题目
[仙人指路](https://www.luogu.com.cn/problem/CF802B)

### 大意
一个背包，体积为 $k$，现在有 $n$ 件物品，$m$ 次查询。每次查询时，若被查寻物不在背包内，则将被查寻物加入背包，如若背包已满则和背包内任一物品替换，对于每次操作，代价为 $1$。求出最小代价。

### 思路
当需要交换物品时，将背包内距下次使用的距离最远的物品进行交换。时间复杂度为  $\operatorname{O}(n\log{n})$。

#### 细节处理
 - 使用优先队列进行背包内存储。
 - 使用 `pair` 作为优先队列元素，优先队列默认按第一项排序。
 - 链式结构构建紧急度大小。
 
### 证明
显然，拿走距下次使用物品最远的为最优解，不然就要再次操作。

### AC 代码

```
#include <bits/stdc++.h>

#define ll long long
#define io cin.tie(0),ios::sync_with_stdio(false)
#define ri register int

using namespace std;
typedef pair<int, int> qwq ;
const int N = 414514 ;
long long a[N], _next[N], last[N];
bool vis[N];
priority_queue<qwq> q;
int main()
{
	io;
	int n, m;
	cin >> n >> m;
	ll ans = 0, tmp = 0;
	for (ri i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (ri i = 1; i <= n; i++)
	{
		_next[last[a[i]]] = i;
		last[a[i]] = i;
		_next[i] = 1e9;
	}
	for (ri i = 1; i <= n; i++)
	{
		while (!q.empty() && !vis[q.top().second])
			q.pop();
		if (!vis[a[i]])
		{
			ans++;
			vis[a[i]] = 1;
			if (!q.empty() && tmp >= m)
			{
				vis[q.top().second] = 0;
				q.pop();
			}
			if (tmp < m)
			{
				tmp++;
			}
		}
		q.push({_next[i], a[i]});
	}
	cout << ans << endl;
	return 0;
}
```

---

