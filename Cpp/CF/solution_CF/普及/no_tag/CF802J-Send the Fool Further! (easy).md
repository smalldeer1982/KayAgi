# Send the Fool Further! (easy)

## 题目描述

Heidi's friend Jenny is asking Heidi to deliver an important letter to one of their common friends. Since Jenny is Irish, Heidi thinks that this might be a prank. More precisely, she suspects that the message she is asked to deliver states: "Send the fool further!", and upon reading it the recipient will ask Heidi to deliver the same message to yet another friend (that the recipient has in common with Heidi), and so on.

Heidi believes that her friends want to avoid awkward situations, so she will not be made to visit the same person (including Jenny) twice. She also knows how much it costs to travel between any two of her friends who know each other. She wants to know: what is the maximal amount of money she will waste on travel if it really is a prank?

Heidi's $ n $ friends are labeled $ 0 $ through $ n-1 $ , and their network of connections forms a tree. In other words, every two of her friends $ a $ , $ b $ know each other, possibly indirectly (there is a sequence of friends starting from $ a $ and ending on $ b $ and such that each two consecutive friends in the sequence know each other directly), and there are exactly $ n-1 $ pairs of friends who know each other directly.

Jenny is given the number $ 0 $ .

## 说明/提示

In the second example, the worst-case scenario goes like this: Jenny sends Heidi to the friend labeled by number $ 2 $ (incurring a cost of $ 100 $ ), then friend $ 2 $ sends her to friend $ 1 $ (costing Heidi $ 3 $ ), and finally friend $ 1 $ relays her to friend $ 4 $ (incurring an additional cost of $ 2 $ ).

## 样例 #1

### 输入

```
4
0 1 4
0 2 2
2 3 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6
1 2 3
0 2 100
1 4 2
0 3 7
3 5 10
```

### 输出

```
105
```

## 样例 #3

### 输入

```
11
1 0 1664
2 0 881
3 2 4670
4 2 1555
5 1 1870
6 2 1265
7 2 288
8 7 2266
9 2 1536
10 6 3378
```

### 输出

```
5551
```

# 题解

## 作者：Velix (赞：2)

没人写题解吗……明明很简单啊……

[题目链接](https://www.luogu.com.cn/problem/CF802J)

---

### 题意

- 给你一棵有 $n$ 个节点并以节点 $0$ 为根的树，每条边有一个权值，权值为正整数。

- 让你从根开始找一条路径，路径的边的权值之和最大。

---

这题就是简单的搜索。

从树根开始 $DFS$ 。

对于每个节点，遍历所有的儿子，求出每个儿子到叶子节点最长的路径。

并取其中与边权之和最大的儿子对该节点进行更新。

注意设置 $vis$ 数组防止多次访问。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct qq{
	int to,dis,next;
}a[2000];
int n,tot,head[1001],vis[1001];
void add(int x,int y,int z){a[++tot].to=y;a[tot].next=head[x];a[tot].dis=z;head[x]=tot;}
//邻接表基本操作 
int dfs(int x)
{
	int ans=0;
	vis[x]=1;
	for(int i=head[x];i;i=a[i].next)
		if(!vis[a[i].to])ans=max(ans,a[i].dis+dfs(a[i].to));
	return ans;
}
int main()
{
	int u,v,w;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	cout<<dfs(0);
}
```


---

## 作者：流绪 (赞：1)

dfs！

给一棵有根带权树，从根出发，找一条权值，它的权值和最大。

n 最大 100，那么我们直接搜索遍历所有路径即可。

给一棵树，那么我们用链式前向星存图，然后 dfs 遍历这个图。因为只是求最大权值和，那么我们直接走到某个点就更新 ans 的值。同时注意不要走回去了就行啦。

下面是 AC 代码，细节注释代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
struct node
{
	int v,nex,c;
}p[maxn];
int ans=0,cnt=0,head[maxn];
void add(int u,int v,int c)
{
	p[++cnt].v=v;
	p[cnt].c=c;
	p[cnt].nex = head[u];
	head[u]=cnt;
}//链式前向星
void dfs(int x,int v,int sum)
{//x是当前位置,v是前一个位置,sum是权值和
	ans = max(ans,sum);//更新答案
	for(int i=head[x];i;i=p[i].nex)
		if(p[i].v != v)//不能走回去
			dfs(p[i].v,x,sum+p[i].c);
}
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	for(int i=1;i<n;i++)
	{
		int u,v,c;
		cin >> u >> v >> c;
		add(u,v,c);
		add(v,u,c);
	}
	dfs(0,-1,0);
	cout << ans;
	return 0;
} 
```


---

