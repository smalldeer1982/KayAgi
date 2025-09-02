# Searching for Graph

## 题目描述

Let's call an undirected graph of $ n $ vertices  $ p $ -interesting, if the following conditions fulfill:

- the graph contains exactly $ 2n+p $ edges;
- the graph doesn't contain self-loops and multiple edges;
- for any integer $ k $ ( $ 1<=k<=n $ ), any subgraph consisting of $ k $ vertices contains at most $ 2k+p $ edges.

A subgraph of a graph is some set of the graph vertices and some set of the graph edges. At that, the set of edges must meet the condition: both ends of each edge from the set must belong to the chosen set of vertices.

Your task is to find a  $ p $ -interesting graph consisting of $ n $ vertices.

## 样例 #1

### 输入

```
1
6 0
```

### 输出

```
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
```

# 题解

## 作者：流绪 (赞：1)

构造！

这题...我看傻了...

三个条件，第一个告诉我们总边数，第二个告诉我们图的一些性质，第三个告诉我们某几个点最多几条边，但是没啥用，几个点的边的数量还能大于全部边的数量？

所以我们直接从小枚举点，然后让它和它后面的点全连起来，然后输出 2*n+p 次不就好了？？？看一看数据范围,边总量小于 n(n-1)/2，是公差为 1 的等差数列和，刚好符合上面所说的构造方法。不会这么简单吧...再一看样例，好像还真是这样，然后就过了...一脸懵逼。

下面是 AC 代码,细节注释代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n,p;
		cin >> n >> p;
		int x=1,y=2;//设有一条从1到2的边
		for(int i=1;i<=2*n+p;i++)
		{
			cout << x << " " << y << endl;
			y++;
			if(y == n+1)
				x++,y=x+1;//没有重边,所以让y>x恒成立
		}
	}
	return 0;
} 
```


---

## 作者：CH30S (赞：0)

~~水题解了~~

思路和@一个pupil 差不多，稍微拓展一下。



------------

**题意**

给定两个数 $n$ , $p$ 要求构造一个无向图，并满足以下条件


1 . 该图正好有 $n*2 + p$ 个边


2 . 图中不包含自环和重边

3 . 图中任选 $k$ 个点构成的子图边的数量小于等于 $ n*2 + p$



构造如上的图即可。




------------



**思路**

构造。




$t$ 次循环并枚举再输出 $i$ 和 $j$ ，当输出了 $ 2 \times n+p $ 组为止。

~~就是这么简单。~~

~~个人认为不必建树。~~

~~代码就不展示了吧，很简单的，~~ 实在不会见其他题解吧。



------------


**最后推荐。**

题外话，这有个构造题目合集的神仙博客。


[构造题目合集（转载）](https://blog.csdn.net/Irving0323/article/details/118198891)

done（求通过）

---

## 作者：oimaster (赞：0)

题意乱七八糟![ruo](https://cdn.luogu.com.cn/upload/pic/62238.png)

**简单**题面：

- 构造一个连通图
- 一共有 $n$ 个点，$2n+p$ 条边
- 两个点之间最多有一条边，不能有自己连接到自己的边

一道非常水的构造题。首先，为了保证图联通，我们可以建一棵树。$1$ 是根，其他的所有点都与 $1$ 相连。

接下来，我们已经连接了 $n-1$ 条边了，剩下的边我们只需要把没有连接起来的两个点连接就可以了。题目保证一定可以。

为了有顺序，不遗漏，我们可以使用邻接表和 `for` 循环按照顺序枚举，解决一切。当连完边就立刻停下来，等待下一组数据。

```cpp
#include<iostream>
using namespace std;
void solve(){
	int n,p;
	cin>>n>>p;
	int edge=n*2+p;
	int a[n+1][n+1];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			a[i][j]=0;
	for(int i=2;i<=n;++i){
		a[1][i]=a[i][1]=1;
		cout<<1<<' '<<i<<endl;
		--edge;
	}
	for(int i=2;i<=n;++i)
		for(int j=1;j<=n;++j){
			if(j==i)
				continue;
			if(a[i][j]==0){
				a[i][j]=a[j][i]=1;
				--edge;
				cout<<i<<' '<<j<<endl;
				if(edge==0)
					return;
			}
		}
}
int main(){
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

---

