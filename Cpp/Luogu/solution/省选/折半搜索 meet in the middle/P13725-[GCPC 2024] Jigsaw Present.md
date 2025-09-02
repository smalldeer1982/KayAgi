# [GCPC 2024] Jigsaw Present

## 题目描述

Julia 正在为 James 准备一份礼物。她会从自己拥有的 $n$ 个拼图中选出一些送给他，其中第 $i$ 个拼图（$1 \leq i \leq n$）包含 $x_i$ 块拼图，并且难度为 $y_i$（如果拼图非常简单，$y_i$ 可以为负数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/okr7isdn.png)

James 已经非常激动，并且想提前知道自己会收到什么。因此，他动用了一些“犯罪天赋”收集到了关于礼物的信息。具体来说，他设法获得了一条加密消息，内容是他将收到的所有拼图的总难度和总块数。

现在他想知道，是否值得花更多时间去解密这条消息。毕竟，这些信息可能不足以唯一确定他的礼物。由于他对计算机一窍不通，James 向你寻求帮助。请你帮他判断是否值得解密这条消息。如果不能唯一确定礼物，你还需要找出两种不同的礼物，它们对应的加密消息是相同的。

## 说明/提示

在第一个样例中，第一份礼物包含拼图 $2$、$4$ 和 $5$。总块数为 $3 + 1 + 1 = 5$，总难度为 $2 + (-3) + 1 = 0$。第二份礼物包含拼图 $1$ 和 $3$。总块数为 $2 + 3 = 5$，总难度为 $(-1) + 1 = 0$。因此，如果 James 只知道总块数和总难度，他无法确定自己的礼物，所以不值得解密消息。

在第二个样例中，无论 Julia 如何准备礼物，只要 James 知道总块数和总难度，他都能确定自己的礼物，所以值得解密消息。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 -1
3 2
3 1
1 -3
1 1```

### 输出

```
no
3 2 4 5
2 1 3```

## 样例 #2

### 输入

```
4
2 -1
3 2
3 1
1 -3```

### 输出

```
yes```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

我们参考 [P12012](https://www.luogu.com.cn/problem/P12012) 中的处理方法，发现值域很小，所以 $x,y$ 之和不会很大，但是 $n$ 足够大的时候不同的集合数是 $O(2^n)$ 量级的，所以 $n$ 大于某个阈值的时候取前若干个数就可以找到符合题意的数。这里我的代码取了阈值 $28$（$26$ 不够）。

然后我们考虑暴力判断每个数是进入第一个集合、第二个集合还是都不进入，这样做是 $O(3^n)$ 的，$n\le 28$ 所以还不够。但是注意到这个暴力是可以合并的，所以考虑折半搜索，先把所有小于等于 $\frac{n}2$，也就是 $14$ 的状态都找出来，然后与后面的进行合并。具体地，维护每个状态下第一个集合的 $x$ 之和减第二个的，$y$ 同理，合并是平凡的。不要使用 map，会多一个 $\log$。总复杂度 $O(3^{\frac n 2})$，可以通过。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[40],y[40],n,vis[40],p3[17],sta,sumx1=0,sumx2=0,sumy1=0,sumy2=0;
unordered_map<int,int> mp1[120010];
void dfs1(int step)
{
	if(step==n/2+1)
	{
		if(!sta) return;
		mp1[sumx1-sumx2+58000][sumy1-sumy2]=sta;
		return;
	}
	dfs1(step+1);
	vis[step]=1;
	sta+=p3[step-1];
	sumx1+=x[step];
	sumy1+=y[step];
	dfs1(step+1);
	vis[step]=2;
	sta+=p3[step-1];
	sumx1-=x[step];sumx2+=x[step];
	sumy1-=y[step];sumy2+=y[step];
	dfs1(step+1);
	vis[step]=0;
	sta-=2*p3[step-1];
	sumx2-=x[step];sumy2-=y[step];
}
void dfs2(int step)
{
	if(step==n+1)
	{
		if(!sta) return;
		if(mp1[-(sumx1-sumx2+58000)+116000][sumy2-sumy1])
		{
			cout<<"no\n";
			int num=mp1[-(sumx1-sumx2+58000)+116000][sumy2-sumy1];
			vector<int> ans1,ans2;
			for(int i=1;i<=n/2;i++)
			{
				if(num/p3[i-1]%3==1) ans1.push_back(i);
				if(num/p3[i-1]%3==2) ans2.push_back(i);
			}
			for(int i=n/2+1;i<=n;i++)
			{
				if(sta/p3[i-1-n/2]%3==1) ans1.push_back(i);
				if(sta/p3[i-1-n/2]%3==2) ans2.push_back(i);
			}
			cout<<ans1.size()<<' ';
			for(auto i:ans1) cout<<i<<' ';
			cout<<'\n';
			cout<<ans2.size()<<' ';
			for(auto i:ans2) cout<<i<<' ';
			exit(0);
		}
		if(sumx1==sumx2&&sumy1==sumy2)
		{
			vector<int> ans1,ans2;
			for(int i=n/2+1;i<=n;i++)
			{
				if(sta/p3[i-1-n/2]%3==1) ans1.push_back(i);
				if(sta/p3[i-1-n/2]%3==2) ans2.push_back(i);
			}
			cout<<ans1.size()<<' ';
			for(auto i:ans1) cout<<i<<' ';
			cout<<'\n';
			cout<<ans2.size()<<' ';
			for(auto i:ans2) cout<<i<<' ';
			exit(0);
		}
		return;
	}
	dfs2(step+1);
	vis[step]=1;
	sta+=p3[step-1-n/2];
	sumx1+=x[step];
	sumy1+=y[step];
	dfs2(step+1);
	vis[step]=2;
	sta+=p3[step-1-n/2];
	sumx1-=x[step];sumx2+=x[step];
	sumy1-=y[step];sumy2+=y[step];
	dfs2(step+1);
	vis[step]=0;
	sta-=2*p3[step-1-n/2];
	sumx2-=x[step];sumy2-=y[step];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	if(n>=28) n=28;
	p3[0]=1;
	for(int i=1;i<=n/2+1;i++) p3[i]=p3[i-1]*3;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	dfs1(1);
	dfs2(n/2+1);
	if(mp1[58000][0])
	{
		int num=mp1[58000][0];
		cout<<"no\n";
		vector<int> ans1,ans2;
		for(int i=1;i<=n/2;i++)
		{
			if(num/p3[i-1]%3==1) ans1.push_back(i);
			else if(num/p3[i-1]%3==2) ans2.push_back(i);
		}
		cout<<ans1.size()<<' ';
		for(auto i:ans1) cout<<i<<' ';
		cout<<'\n';
		cout<<ans2.size()<<' ';
		for(auto i:ans2) cout<<i<<' ';
		cout<<'\n';
		return 0;
	}
	cout<<"yes";
}

---

