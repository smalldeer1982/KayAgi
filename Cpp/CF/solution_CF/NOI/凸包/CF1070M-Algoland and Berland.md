# Algoland and Berland

## 题目描述

很久以前，Algoland和Berland是一个国家，但那个时代早已过去。现在它们是两个国家，但他们的城市散布在一个共同的领土上。

所有城市都表示为一个平面直角坐标系的一个点。Algoland由 $a$ 个城市组成，编号从 $1$ 到 $a$。Algoland第 $i$ 个城市的坐标为 $(xa_i,ya_i)$ 。同样的，Berland由 $b$ 个城市组成，编号从 $1$ 到 $b$。Berland第 $j$ 个城市的坐标是 $(xb_j,yb_j)$ 。保证两个国家的 $a+b$ 个城市里没有三个城市在一条直线上。

作为联合两国的第一步，Berland决定修建几条双向的高速公路。每条高速公路将是一条线段，从Berland的一个城市开始，到Algoland的一个城市结束。除了高速公路的起点或终点，高速公路不能在任何一点上相互交叉。此外，高速公路必须连接所有 $a+b$ 个城市。这意味着人们可以通过高速公路从任何一个城市到达任何其他的城市。请注意，所有的高速公路都是双向的，这意味着人们可以在每条高速公路上双向行驶。

每一个Berland城市的市长都分配了一个预算来建造从这个城市出发的高速公路。因此，你会得到数 $r_1,r_2,\dots,r_b$ ，其中 $r_j$ 是要从第 $j$ 个Berland城市开始的高速公路的数量。市长们分配的预算是非常紧张的，只有建设所有高速公路必要的代价。也就是 $r_1+r_2+\dots+r_b=a+b-1$ 。

请你帮助Berland建设高速公路，有以下几个要求：

- 每条高速公路都是一条连接Berland城市和Algoland城市的线段。
- 没有任何两条高速公路有交点，除了交点是两条公路的起点或终点。
- 高速公路必须连接所有 $a+b$ 个城市。
- 有 $r_j$ 条高速公路从第 $j$ 个Berland城市开始。

## 样例 #1

### 输入

```
2
2 3
1 1 2
0 0
1 1
1 2
3 2
4 0
1 1
1
0 0
0 1
```

### 输出

```
YES
2 2
1 2
3 2
3 1
YES
1 1
```

# 题解

## 作者：良心WA题人 (赞：0)

如果能够将平面上的点分用一条直线分成两部分，使得两个部分之间只与一个在直线上的点连边，那么这个平面在这两个部分之间不会产生交点。故可以想到分治。

注意到存在边界情况是所有 B 国家的点都只能连出去一条边，此时一定只会存在一个 A 国家的点，那么将这个点连接所有 B 国家的点在这部分中不会产生交点。

但是如果尝试将树以一个点分开，则会分成很多个部分。不过在平面直角坐标系上并不方便分成很多个部分，故考虑将一个点拆成两个点，对分出来的两部分一部分连第一个点，一部分连第二个点。那么就需要考虑将这个点的度数分成两部分。令 $w=|V|-|E|$，其中 $V$ 表示点集，$E$ 表示边集，则我们希望 $w=1$，令 $A$ 国家的点的 $r$ 为 $0$，则有 $w=|V|-\sum_{i\in V} r_i$。因为初始保证了 $w=1$，则我们去掉要分开的点 $u$ 后，剩余的两部分的 $w$ 加起来一定为 $r_u$。那么，只要满足 $1\le w\le r_u$，这一部分就能够与 $u$ 连边。不过我们需要保证另一部分也与 $u$ 有连边，所以不能取到 $r_u$。

现在过 $u$ 做旋转扫描线，对于每一个直线计算 $w$，当 $w$ 满足在这个区间内就可以分治了。但是，不一定能够找到这样的直线使得 $w$ 在区间内。我们改写一下 $w$，写成 $\sum_{i\in V}1-r_i$，发现每次给集合内加入或删除一个点的权值为 $1-r_i$。而我们的区间大小为 $r_u-1$。可以发现，这两个是等价的，则当两侧的 $w$ 均不在区间内的时候，一个在区间左侧，一个在区间右侧。当一侧逐渐变到另一侧的时候，每次的步长最多跨越 $1-r_i$，我们希望这之中存在一个位置落在区间内，只需要取 $r_u$ 最大的一个 $u$ 来分割即可。

注意到时间复杂度实际上是有点紧的，可能会被卡常。`atan2` 的常数比较大，可以提前预处理出来再极角排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1);
struct node
{
	int x,y,id,r;
	double val;
	bool operator<(const node&it)const
	{
		return val<it.val;
	}
};
int n,m;
void solve(vector<node>a)
{
	int cnt=0,p;
	for(int i=0;i<a.size();i++)
		if(a[i].id<=n)
			cnt++,p=a[i].id;
	if(cnt==1)
	{
		for(int i=0;i<a.size();i++)
			if(a[i].id>n)
				printf("%d %d\n",a[i].id-n,p);
		return;
	}
	for(int i=1;i<a.size();i++)
		if(a[i].id>n&&a[i].r>a[0].r)
			swap(a[i],a[0]);
	for(int i=1;i<a.size();i++)
		a[i].val=atan2(a[i].y-a[0].y,a[i].x-a[0].x);
	sort(a.begin()+1,a.end());
	int w=0;
	cnt=0,p=1;
	while(cnt<a.size()-1&&a[p].val+PI<=a.back().val)
	{
		w+=1-a[p].r;
		cnt++,p++;
		if(p==a.size())
			p=1;
	}
	for(int i=1;i<a.size();i++)
	{
		while(1)
		{
			if(w>=1&&w<a[0].r)
			{
				vector<node>b;
				int u=i;
				do
				{
					b.push_back(a[u]);
					u++;
					if(u==a.size())
						u=1;
				}while(u!=p);
				node t=a[0];
				t.r=w;
				b.push_back(t);
				solve(b);
				b.clear();
				u=p;
				while(u!=i)
				{
					b.push_back(a[u]);
					u++;
					if(u==a.size())
						u=1;
				}
				t=a[0];
				t.r=a[0].r-w;
				b.push_back(t);
				solve(b);
				return;
			}
			if(!(cnt<a.size()-1&&(p>=i&&a[p].val<=a[i].val+PI||a[p].val+PI<=a[i].val)))
				break;
			w+=1-a[p].r;
			cnt++,p++;
			if(p==a.size())
				p=1;
		}
		w-=1-a[i].r;
		cnt--;
	}
}
void solve()
{
	scanf("%d%d",&n,&m);
	vector<node>a;
	a.resize(n+m);
	for(int i=0;i<m;i++)
		scanf("%d",&a[i+n].r);
	for(int i=0;i<n+m;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i+1;
		if(i<n)
			a[i].r=0;
	}
	puts("YES");
	solve(a);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
```

---

