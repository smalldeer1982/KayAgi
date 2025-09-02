# Nastya and Time Machine

## 题目描述

Denis came to Nastya and discovered that she was not happy to see him... There is only one chance that she can become happy. Denis wants to buy all things that Nastya likes so she will certainly agree to talk to him.

The map of the city where they live has a lot of squares, some of which are connected by roads. There is exactly one way between each pair of squares which does not visit any vertex twice. It turns out that the graph of the city is a tree.

Denis is located at vertex $ 1 $ at the time $ 0 $ . He wants to visit every vertex at least once and get back as soon as possible.

Denis can walk one road in $ 1 $ time. Unfortunately, the city is so large that it will take a very long time to visit all squares. Therefore, Denis took a desperate step. He pulled out his pocket time machine, which he constructed in his basement. With its help, Denis can change the time to any non-negative time, which is less than the current time.

But the time machine has one feature. If the hero finds himself in the same place and at the same time twice, there will be an explosion of universal proportions and Nastya will stay unhappy. Therefore, Denis asks you to find him a route using a time machine that he will get around all squares and will return to the first and at the same time the maximum time in which he visited any square will be minimal.

Formally, Denis's route can be represented as a sequence of pairs: $ \{v_1, t_1\}, \{v_2, t_2\}, \{v_3, t_3\}, \ldots, \{v_k,       t_k\} $ , where $ v_i $ is number of square, and $ t_i $ is time in which the boy is now.

The following conditions must be met:

- The route starts on square $ 1 $ at time $ 0 $ , i.e. $ v_1 = 1, t_1 = 0 $ and ends on the square $ 1 $ , i.e. $ v_k = 1 $ .
- All transitions are divided into two types: 
  1. Being in the square change the time: $ \{ v_i, t_i \} \to \{             v_{i+1}, t_{i+1} \} : v_{i+1} = v_i, 0 \leq t_{i+1} <             t_i $ .
  2. Walk along one of the roads: $ \{ v_i, t_i \} \to \{             v_{i+1}, t_{i+1} \} $ . Herewith, $ v_i $ and $ v_{i+1} $ are connected by road, and $ t_{i+1} = t_i +             1 $
- All pairs $ \{ v_i, t_i \} $ must be different.
- All squares are among $ v_1, v_2, \ldots, v_k $ .

You need to find a route such that the maximum time in any square will be minimal, that is, the route for which $ \max{(t_1, t_2,       \ldots, t_k)} $ will be the minimum possible.

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5```

### 输出

```
13
1 0
2 1
3 2
3 1
2 2
4 3
4 1
5 2
5 1
4 2
2 3
2 0
1 1```

# 题解

## 作者：maruize (赞：6)

### 题意
有一棵 $n$个点的树，你从$ 1 $号点开始遍历，最后回到 $1$ 号 点。通过一条边需要的时间是 $1$，初始时间是$0$。 你有一台时间机器，可以让你在不改变所在位置的情况下穿 越到任意一个**小于**当前时间且大于等于 0 的时间点。（必须是整数） 

由于不能违背宇宙法则，你不能在两次在同一个时间点位于 同一个节点。 你需要设置一个遍历次序，满足所有时间点的最大值最小。

（抄自wqy老师的课件） 

输出：

第一行一个正整数$k$，表示遍历的长度

接下来$k$行，每行两个数，表示遍历到的点的编号和时间。

---
先考虑一些特殊情况：

- (以$1$为端点的)一条链？$T=(n==2?2:3)$
- 菊花图？$T=(n-1)$

可以发现$T$和点的度数好像有关系。

假设有无穷多的时间，在时间$t+1$时进入一棵子树，那么可以在$t$时刻回到子树的根(遍历完子树后在子树根上用一次穿越)。

这样，对于每个点遍历完它的一个孩子需要“用”$1$的时间。显然如果它有父亲那么过来也需要$1$的时间，所以在一个点只需$deg_i$的时间(只要保证进来的时间$<deg_i\color{blue}{[1]}$)。(为什么是$deg_i$而不是孩子的个数因为不可能在$0$时刻到达一个非根节点，需要在这个点进行穿越(自己想想) )

(注:$deg$表示度)

![演示](https://cdn.luogu.com.cn/upload/image_hosting/611m50cp.png)

所以总时间为$\max_{i \in tree}deg_i$

---

考虑如何构造：


(先看我的错误做法)

**1.**

一开始我想成了对于每个点向下走时到了时间$T$就穿越为$0$最后遍历完后穿越到$t$。

有什么问题呢？这样完美的忽略了"只能穿越到任意一个**小于**当前时间的点"。

无法保证子树内最后一次穿越符合上述条件。

然后WA了一大堆。。。

**2.**

那到时间$deg_i$就穿越回$0$？

我又没想起$"\color{blue}{[1]}$  $"$

那怎么办呢？？？

- 大于$deg_i$的话一开始就回到0？——想想不对。
- 可以把时间区间向后移一下:$(\to 3.)$

**3.** 由原来的时间区间$(t+1\to deg_i),(0 \to t)=>(t+1 \to T),(T-deg_i \to t)$。

code:

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200605;
int head[maxn],num_edge;
struct Edge{int next,to;}ed[maxn*2];
void add(int from,int to){
	ed[++num_edge].next=head[from];
	ed[num_edge].to=to;
	head[from]=num_edge;
}
int fa[maxn];

int cnt=0,top=0;
struct{int p,t;}ans[1000605];
inline void print(int point,int tim)
	{ans[++cnt]={point,tim};}
int T;
int deg[maxn];
void dfs1(int now,int tim,int fa=0){
	print(now,tim);
	int t=tim;//"t"为t'及刚才的t+1
	for(int i=head[now];i;i=ed[i].next){
		int to=ed[i].to;
		if(to==fa)continue;
		if(tim==T&&t>deg[now])tim=T-deg[now],print(now,tim);//1
		if(tim==deg[now]&&t<=deg[now])tim=0,print(now,tim);//1
		dfs1(to,++tim,now);
		print(now,tim);
	}
	if(t-1>=0&&tim!=t-1)print(now,t-1);
        //穿越回t'-1
        //只有now==root时不会执行
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)T=max(T,deg[i]);
	dfs1(1,0);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d %d\n",ans[i].p,ans[i].t);
	return 0;
}
```
**4.** $<deg_i$的也可进行时间区间后移可以精简一下"1"处的代码.

参考资料：wqy老师的课件

注：

spj报错信息：

1. wrong answer t[...] is a bad time:你是否穿越到了未来？

2.wrong answer jury found better answer, pans=a > jans=b：你的答案不够优秀。

3.wrong answer all states should be different:不可以在多个同一时间到达同一个点。

---

## 作者：ZigZagKmp (赞：5)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)
## CF1340D
### 题意简述
给你一棵树，通过每条边需要 $1$ 的时间，你可以在一个结点处将时间变为任意一个比当前时间小的非负整数。现在要从 $1$ 号节点从时间 $0$ 出发，经过所有的节点并返回 $1$ 号节点，要求不能两次在同一时间在同一个节点。求一种方案使得每个点的最大时间最小。
### 算法标签
树上问题 dfs 构造
### 算法分析
不难发现答案的下界是度数最大的节点的度数（最优情况下每个节点都要经过 $deg+1$ 次，因此至少要填上 $0,1,\cdots,deg$ 这些数字）

下面我们考虑直接构造出满足下界的答案。

为了方便构造，若进入节点 $x$ 的时间点为 $t_x$ ，则离开节点 $x$ 的时间点必须为 $t_x-1$ (这样返回节点 $x$ 的父节点时间点就为 $t_x$ )。

在遍历节点 $x$ 的所有子节点时可能会有如下两种情况：

1. $t_x+deg_x<maxdeg$ 则过程中不会超过答案，只需遍历结束后将时间回到 $t_x-1$ 即可。
2. $t_x+deg_x\ge maxdeg$ 过程中会有某一个节点的时间点超过答案。因为总共会占用 $deg_x+1$ 个时间点，因此当过程中的标号达到 $maxdeg$ 时只需回到 $maxdeg-deg_x$ 的时间点即可。

注意一些实现上的细节即可，时间复杂度 $O(n)$ 。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,m;
vector<int>G[maxn];
struct oper{
	int id,tm;
}ans[maxm];
int tot;
int du[maxn],md;
void dfs(int x,int pa,int tim){
	int curt=tim;
	ans[++tot]=(oper){x,tim};
	if(curt==md){
		curt-=du[x];
		ans[++tot]=(oper){x,curt};
	}
	for(unsigned i=0;i<G[x].size();++i){
		int y=G[x][i];
		if(y==pa)continue;
		dfs(y,x,++curt);
		ans[++tot]=(oper){x,curt};
		if(curt==md&&i!=G[x].size()-1){
			curt-=du[x];
			ans[++tot]=(oper){x,curt};
		}
	}
	if(x!=1&&curt!=tim-1){
		ans[++tot]=(oper){x,tim-1};
	}
}
signed main(){
	read(n);
	if(n==1){
		puts("1");
		puts("1 0");
		return 0;
	}
	for(int i=1,x,y;i<n;++i){
		read(x);read(y);
		G[x].push_back(y);
		G[y].push_back(x);
		++du[x];++du[y];md=max(md,du[x]);md=max(md,du[y]);
	}
	dfs(1,0,0);
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i){
		printf("%d %d\n",ans[i].id,ans[i].tm);
	}
	return 0;
}

```

---

## 作者：Suiseiseki (赞：4)

~~最大最小，直接二分答案上啊。~~要求出一种方案，这题二分答案不大好做，考虑直接构造。

首先考虑单纯的走（即不考虑修改时间），每个节点很明显经过的次数是它的度数次，并且，如果考虑修改时间，若修改一次时间不算经过该节点一次的话，那么经过该节点的时间肯定是度数次（多了只会给自己加负担）。

那么先考虑确定下答案，~~二分答案多好啊~~（博主这个菜鸡只会二分答案了），首先，很明显最终答案肯定不小于每个点的度数中的最大值，所以答案就是每个点的度数的最大值减一（因为从$0$开始）……吗？样例就推翻了我们的这个结论。

仔细考虑，每个点很明显最小是它的度数减一，但是问题在于如果进入这个点时的时间不为$0$，那么就需要更改一次时间，但是更改时间又会导致当前点时间个数的浪费，所以更改时间自然是越少越好，但因为更改时间不可避免，所以考虑每一个点能否最多只用一次更改时间，这样的话答案就是每个点的度数的最大值。

令$maxdeg=\max_{u} deg_u\text{（} deg_u\text{表示节点}u\text{的度数）}$，那么考虑让每一个点的时间取值为$[maxdeg-deg_u,maxdeg]$，一共有$deg_u+1$中取值，满足我们的要求。

接下来就是考虑怎么构造答案了，因为我们钦定每一个节点的时间取值是在一个范围内，所以到儿子的时间就要连续（将该区间看成一个环），因为只能更改一次时间，这可以在当前时间到达$maxdeg$时更改为$maxdeg-deg_u$，然后这题就做完了（有一些简单的情况就不列了）。

代码可以去我的博客查看：[Codeforces 1340D. Nastya and Time Machine 题解](https://www.cnblogs.com/withhope/p/12790266.html)

---

