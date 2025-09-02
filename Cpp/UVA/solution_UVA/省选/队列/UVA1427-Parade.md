# Parade

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4173

[PDF](https://uva.onlinejudge.org/external/14/p1427.pdf)

# 题解

## 作者：CreeperLordVader (赞：2)

楼下封装了一个队列,我来直接数组模拟一个

花了几个小时,这题真的是刷新了我对单调队列的认识

## 重要的事情说三遍

###  单调队列先插入再转移!

## 单调队列先插入再转移!

# 单调队列先插入再转移!

## 这样在转移时,你才能保证队列里总有合法元素

那么我们来看看这个DP应该怎么做

首先注意到,对于一个点,我们只需要知道它是从哪里走过来的

把向左和向右计入状态吗?不需要

直接枚举以后分类讨论即可,因此可以直接设$d(i,j)$为到达点$(i,j)$的最大值

由于有行走的距离上限k,可以发现决策的可行域单调

由于是最大化答案,我们维护一个递减的单调队列

插入时,如果当前值大于等于队尾,弹出队尾直至当前值小于队尾

~~如果一个选手比你小,还比你强,你就可以退役了~~

要注意的是,单调队列一定要先插入后删除,不然你的队列可能是空的,转移就会出问题

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int tot[110][10010];
int sum[110][10010];
int d[110][10010];
int q[10010];
bool read(int& x)
{
	char c=getchar();
	int f=1;x=0;
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
	return x;
}
inline int func(int i,int j)
{
	return d[i+1][j]-sum[i][j];
}
inline int calc(int i,int j)
{
	return d[i+1][j]+sum[i][j];
}
int main()
{
// 	freopen("fuck.in","r",stdin);
//	freopen("1.out","w",stdout);
	while(read(n))
	{
		read(m);
		read(k);
		int ans=0;
		memset(sum,0,sizeof(sum));
		memset(tot,0,sizeof(tot));
		for(int i=1;i<=n+1;i++)
		{
			for(int j=1;j<=m;j++)
			{
				int x;
				read(x);
				sum[i][j]=sum[i][j-1]+x;
			}
		}
		for(int i=1;i<=n+1;i++)
		{
			tot[i][1]=0;
			for(int j=1;j<=m;j++)
			{
				int x;
				read(x);
				tot[i][j]=tot[i][j-1]+x;
			}
		}
		memset(d,0,sizeof(d));
		for(int i=n+1;i>=1;i--)
		{
			int l=1,r=0;
			for(int j=0;j<=m;j++)
			{//先计算左边的情况 
				while(l<=r&&tot[i][j]-tot[i][q[l]]>k)l++;
				while(l<=r&&func(i,q[r])<=func(i,j))r--;
				q[++r]=j;
				d[i][j]=func(i,q[l])+sum[i][j];
			}
			l=1,r=0;
			for(int j=m;j>=0;j--)
			{
				while(l<=r&&tot[i][q[l]]-tot[i][j]>k)l++;
				while(l<=r&&calc(i,q[r])<=calc(i,j))r--;
				q[++r]=j;
				d[i][j]=max(d[i][j],calc(i,q[l])-sum[i][j]);
			}
		}
		for(int i=0;i<=m;i++)
		{
			ans=max(ans,d[1][i]);
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：_J_C_ (赞：2)

# 单调队列优化DP裸题
首先这道题里往下走和往上走是没有区别的，毕竟路径没有方向。我当然选择往下走……**别逼着自己逆向思考**。。

dp的思路很简单：设dp[i][j]表示从第i行j个点向左右任意延伸能取得的最大值。

则有**dp[i][j] = max { dp[i - 1][j], dp[i - 1][j - 1] + map[i][j], dp[i - 1][j - 2] + map[i][j] + map[i][j - 1], …… }**之类的**一大串转移**。其中map表示的是第i行第j个点左边的边权，且这些边的距离加起来不超过k。

上述方程中只从左侧转移过来，我们在从右侧转移一遍就可以得到答案了。

当然，这样转移对于其中一点的复杂度是O(m),总体就是O(n\*m\*m)，直接升天。

还有就是为什么要把从左侧转移和从右侧转移分出来呢？~~**这是为了下文做铺垫，请赏析一下这样写的好处。**~~

考虑优化。首先当然可以想到把求和改成前缀和之差，求距离改成前缀和的距离之差，虽然**对于上述算法这毫无意义**（扫描的时候顺带加起来就好了）。

然后考虑单调队列优化。我们在队列中存放可能是接下来的最优转移的位置。这种位置暗含了单调性：**如果一个位置在你右边，它的dp值还比你大，我要你干嘛？**

形式化的说，**记距离的前缀和为f**，对于dp[i - 1][j]与dp[i - 1][k]且j<k，如果有dp[i - 1][j] < dp[i - 1][k]，又由于对于任意x > k有f[x] - f[k] > f[x] - f[j]（**距离为正数，前缀和单调**），所以dp[i - 1][j]不可能成为dp[i - 1][x]（x > k）的最优转移，因为**如果能从dp[i - 1][j]处转移，那么从dp[i - 1][k]处转移一定是合法的。**所以dp[i - 1][j]，对后面的x来说，是无效的，可以当作不存在。

以上是单调队列优化的原理。这样的队列中**越先入队的元素越优，越后入队的元素越劣但是因很可能更晚才失效而被保留。**

具体的操作就是当从左侧转移时，先查看que的队首是否合法（**可以形象的理解为队首在左，队尾在右**），即距离的前缀和之差是否超过了k，如果超过了就一直pop直到空了或者是que的队首合法。之后**将队尾值劣与dp[i - 1][j]的元素全部pop掉**，将j塞入队尾（象征着dp[i - 1][j]）。然后给dp[i][j - 1]赋值。

从右侧转移同理，但是要注意取最优值而不是直接赋值。

比较孰优孰劣的时候记得要**加上路径上的权值**。由于后来的权值对队列中所有元素的权值**效果是相同的**（因为队列中的所有元素都在同一侧），所以加上这个权值后队列**仍然单调**。

再注意一下此题奇妙的输入。

更具体而形象的描述，请见下面的代码。

```cpp
#include <cstdio>
#include <cstdlib>

const int maxn(112), maxm(11234);
namespace my
{
	template <class T>
	class deque//双端队列，其实一般而言STL的deque就够用了
	{
	public:
		deque() : beg(0), end(0) {}
		bool empty() const { return beg == end; }
		T front() const { return all[beg]; }
		T back() const { return all[(end - 1 + maxm) % maxm]; }
		void push_back(const T& x) { all[end++] = x; end %= maxm; }
		void push_front(const T& x) { all[beg = (beg - 1 + maxm) % maxm] = x; }
		void pop_front() { ++beg %= maxm; }
		void pop_back() { end = (end - 1 + maxm) % maxm; }
		void clear() { beg = end = 0; }
		int beg, end;
		T all[maxm]; 
	};
}


int n, m, k;
int dp[maxn][maxm];
int map[maxn][maxm], len[maxn][maxm];
int forward[maxn][maxm], forward_len[maxn][maxm];//forward是权值的前缀和，forward_len即长度的前缀和
my::deque<int> que;

inline void getmax(int& a, int b) { if (b > a) a = b; }

int main()
{
	while (~scanf("%d%d%d", &n, &m, &k))
	{
		if (n == 0 && m == 0 && k == 0) return 0;
		++n; 
		for (int i(1); i <= n; ++i)
		{
			for (int j(1); j <= m; ++j)
			{
				scanf("%d", &map[i][j]);
				forward[i][j] = forward[i][j - 1] + map[i][j];
			}
		}
		for (int i(1); i <= n; ++i)
		{
			for (int j(1); j <= m; ++j)
			{
				scanf("%d", &len[i][j]);
				forward_len[i][j] = forward_len[i][j - 1] + len[i][j];
			}
		}
		++m;
		for (int i(1); i <= n; ++i)
		{
			que.clear();
			for (int j(0); j != m; ++j)
			{
				while (!que.empty() && forward_len[i][j] - forward_len[i][que.front()] > k)
					que.pop_front();
				while (!que.empty() && dp[i - 1][que.back()] + forward[i][j] - forward[i][que.back()] < dp[i - 1][j])
					que.pop_back();
				que.push_back(j);
				dp[i][j] = dp[i - 1][que.front()] + forward[i][j] - forward[i][que.front()];
			}
			que.clear();
			que.push_back(m - 1);
			for (int j(m - 2); j >= 0; --j)
			{
				while (!que.empty() && forward_len[i][que.back()] - forward_len[i][j] > k)
					que.pop_back();
				while (!que.empty() && dp[i - 1][que.front()] + forward[i][que.front()] - forward[i][j] < dp[i - 1][j])
					que.pop_front();
				que.push_front(j);
				getmax(dp[i][j], dp[i - 1][que.back()] + forward[i][que.back()] - forward[i][j]);
			}
		}
		int ans(0);
		for (int i(0); i != m; ++i)
		{
			getmax(ans, dp[n][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

