# [ICPC 2018 WF] Wireless is the New Fiber

## 题目描述

一种新型的无限带宽无线通信刚刚通过测试，并被证明可以替代现有的基于光纤的通信网络，后者正努力跟上流量增长的步伐。你被委托决定新通信网络的布局。当前的通信网络由一组节点（用于路由消息）和光纤链路组成，每条链路连接两个不同的节点。对于每对节点，至少存在一条（但可能更多，为了带宽目的）光纤路径。

新的通信网络将不再使用光纤。相反，它将使用无线链路，每条链路连接两个节点。这些链路具有无限带宽，但成本昂贵，因此决定尽可能少地建设这些链路以提供连通性；对于每对节点，应该只有一条路径通过无线链路连接。此外，你发现每个节点的设计都考虑了特定数量的连接。如果每个节点的连接数与今天不同，则需要重新组织，这将非常昂贵。

你的任务是设计新的网络，使其在每对节点之间恰好有一条路径，同时最小化与原始网络连接数不同的节点数量。图 K.1 显示了原始网络和样例输入 1 的解决方案。

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15699/1.png)

图 K.1：样例输入 1 的示意图。

## 说明/提示

时间限制：2 秒，内存限制：1024 MB。

SPJ 提供者：@[shenyouran](/user/137367)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 11
0 1
0 2
0 5
0 6
1 3
2 4
1 2
1 2
1 5
2 6
5 6
```

### 输出

```
3
7 6
0 1
0 2
0 5
0 6
3 6
4 6
```

## 样例 #2

### 输入

```
4 3
0 1
2 1
2 3
```

### 输出

```
0
4 3
2 1
1 3
0 2
```

# 题解

## 作者：feecle6418 (赞：4)

~~标题倒装句好评~~

首先把所有点的度数减一，那么给定度数序列，能构造出合法的树，当且仅当 $\sum d_i=n-2$。下面的构造证明了这一点。

- 方法：把所有点按度数从小到大排序，对每个点 $x$，找到其后面第一个度数非零（注意度数已经减一）的点 $y$，连接 $(x,y)$，把 $y$ 的度数减一。

那么原问题就转化为：

- 给定一些度数，请你选出最多的度数，满足和不超过 $n-2$。（因为如果还没达到 $n-2$ 可以再用剩下的一个点补齐）

排序后从小到大选即可。注意输出格式比较毒瘤。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d[10005],pl[10005];
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,d[x]++,d[y]++;
	for(int i=0;i<n;i++)pl[i]=i,d[i]--;
	sort(pl,pl+n,[](int x,int y){return d[x]<d[y];});
	int s=0,ans=0;
	for(int i=0;i<n;i++){
		if(s+d[pl[i]]>n-2)break;
		s+=d[pl[i]],ans++;
	}
	cout<<n-ans<<'\n'<<n<<' '<<n-1<<'\n';
	for(int i=ans;i<n;i++){
		if(s==n-2)d[pl[i]]=0;
		else d[pl[i]]=1,s++;
	}
	sort(pl,pl+n,[](int x,int y){return d[x]<d[y];});
	for(int i=0,j=0;i+2<n;i++){
		while(!d[pl[j]])j++;
		d[pl[j]]--,cout<<pl[i]<<' '<<pl[j]<<'\n';
	}
	cout<<pl[n-2]<<' '<<pl[n-1]<<'\n';
}
```

---

## 作者：ycy1124 (赞：3)

### 题意
题意翻译很清楚，这里解释一下输出格式。

输出第一行一个 $w$ 表示需要改变度数的点的最少的个数。

第二行两个数 $n,m$ 表示树有 $n$ 个点 $m$ 条边。

接下来 $m$ 行每行两个整数 $u,v$ 表示树上的边。
### 思路
此题分为两个步骤，先求出你最终树的方案的每个点的度数并使改变度数的点最少，然后构造出一个树的方案。

考虑步骤一，当我们建出一棵树时，树上所有点的度数和等于 $2\times n-2$。由于每个点的度数至少为 $1$，所以我们默认每个点的度数减一，并且总度数为 $n-2$。此时我们就要选出最多的点使它们的度数之和小于 $n-2$，剩余的度数可以分配给后面的点。于是我们先将所有的点按从小到大排序，然后选择一些最小的点不改变它的度数，剩余的点全部度数改为 $1$ 然后将剩余度数分配给一个点。

考虑步骤二，卡了很久后发帖求助才会。首先我们对于现在这些点，它里面是有很多度数为 $1$ 的点，他们都是叶子节点。我们优先考虑这些节点，我们可以先将这些点按度数从小到大排个序，然后每次找到一个度数最小且不为 $1$ 的点，将所有度数为 $1$ 的点连在这个点上面直到这个点的度数等于 $1$，以此类推我们就可以得到一种方案。

证明：由于所有点中是不会有度数超过 $n-1$ 的点的，所以一定是可以构造出一种合法的方案的。根据上面的方法，并不会出现重边与环，也不会分成两个图，所以构造出来的方案一定是对的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d[10005],ans;
struct Node{
    int d,id;
}a[10005];
set<int>s;
inline bool cmp(Node x1,Node x2){
    return x1.d<x2.d;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].d++;
        a[v].d++;
    }
    for(int i=1;i<=n;i++){
        a[i].id=i;
    }
    sort(a,a+n,cmp);
    int sum=n-2;
    for(int i=0;i<n;i++){
        if(sum>=a[i].d-1){
            ++ans;
            sum-=(a[i].d-1);
        }
        else{
            a[i].d=1;
            if(sum!=0){
                a[i].d+=sum;
                sum=0;
            }
        }
    }
    sort(a,a+n,cmp);
    cout<<n-ans<<'\n'<<n<<' '<<n-1<<'\n';
    int tmp=0;
    while(a[tmp].d<=1&&tmp<n-1){
        ++tmp;
    }
    for(int i=0;i<n;i++){
        if(a[i].d==0){
            continue;
        }
        cout<<a[i].id<<' '<<a[tmp].id<<'\n';
        a[i].d--;
        a[tmp].d--;
        if(a[tmp].d<=1&&tmp<n-1){
            ++tmp;
        }
    }
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/198023918)。

---

## 作者：OtoriEmu (赞：1)

Source: P6951。

首先想到用度数最小的点，因为这样限制会更少一些，留下来的空的点可以多干一点其他的事情。

这样先按度数排序，然后就可以二分答案构造。

先特判掉本来就是树的情况。我们尝试构造一个合法的解，具体方法是确定每个点的父亲以及一个根。下面将度数相同的点称为实点，否则称为虚点。

不妨将度数最大的实点设为根，下面尽量用实点去填儿子，按度数从大到小的顺序填。有一些点会度数不够，需要用虚点补充，如果够了就好了（注意到如果有一些度数为二的点没有父亲，也是不行的，因为我们接下来的父亲只能选择虚点，但是只能链接一个）。

分析上面的构造方法，我们发现我们的过程是让每个点度数强制减了 $1$（确定父亲），然后如果能构造就成功。实际上点集 $S$ 能构造成功的条件等价于 $\sum_{u \in S} d_u \leq 2n-2$，可以分析上面的构造方法得到证明。

注意有一些度数为 $1$ 的点如果没有父亲，要接到虚点上去。

下面给出关键代码，[完整代码](https://www.luogu.com.cn/paste/5rdpqf2z)可以点这里。

```cpp
int n,m;
struct node{
	int deg,id;
	inline bool operator < (node ano) const {return deg<ano.deg;}
}p[10005];
int seq[10005];
int edu[100005],edv[100005];
typedef pair<int,int> P;
#define mp make_pair
int fa[10005];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)	p[i].id=i;
	for(int i=1;i<=m;++i)
	{
		int u=read()+1,v=read()+1;
		++p[u].deg,++p[v].deg;
		edu[i]=u,edv[i]=v;
	}
	sort(p+1,p+1+n);
	int sum=0,c=n;
	for(int i=1;i<=n;++i)
	{
		if(sum+p[i].deg-1>n-2)
		{
			c=i-1;
			break;
		}
		sum+=p[i].deg-1;
	}
	write(n-c),puts("");
	write(n),putchar(' '),write(n-1),puts("");
	vector<int> R;
	for(int i=c+1;i<=n;++i)	R.push_back(i);
	if(c==n)
	{
		for(int i=1;i<=m;++i)	write(edu[i]-1),putchar(' '),write(edv[i]-1),puts("");
		return 0;
	}
	int u=c;
	vector<P> left;
	int bot=c-1;
	for(int i=c;i;--i)
	{
		int d=p[i].deg-1;
		for(int j=bot;j>=max(bot-d+1,1);--j)	fa[j]=i;
		int s=min(d,bot);
		if(s^d)	left.push_back(mp(i,d-s));
		bot=max(bot-d+1,1)-1;
		bot=min(bot,i-1);
	}
	while(!left.empty())
	{
		P st=left.back();
		left.pop_back();
		int x=st.first,d=st.second;
		while(d)
		{
			--d;
			int y=R.back();
			R.pop_back();
			fa[y]=x;
		}
	}
	int v=*R.begin();
	fa[u]=v;
	R.erase(R.begin());
	while(!R.empty())	fa[R.back()]=v,R.pop_back();
	for(int i=1;i<=c;++i)	if(!fa[i])	fa[i]=v;
	for(int i=1;i<=n;++i)
	{
		if(i^v)
		{
			int tu=i,tv=fa[i];
			tu=p[tu].id-1,tv=p[tv].id-1;
			write(tu),putchar(' '),write(tv),puts("");
		}
	}
	return 0;
}
```

---

