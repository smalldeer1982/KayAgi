# 3 Steps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c

りんごさんは $ N $ 頂点 の連結な無向グラフを持っています。 このグラフにはすでに $ M $ 本の辺があり、$ i $ 本目の辺は頂点 $ A_i $ と頂点 $ B_i $ を繋いでいます。

りんごさんは以下の操作を行うことで、辺を追加しようと思っています。

- 操作：頂点 $ u $ から辺をちょうど $ 3 $ 本辿ることによって頂点 $ v $ に辿り着けるような $ u,v\ (u\ \neq\ v) $ をとり、頂点 $ u $ と頂点 $ v $ の間に辺を追加する。ただし、すでに頂点 $ u $ と頂点 $ v $ の間に辺が存在する場合は辺を追加することはできない。

りんごさんが追加できる辺の本数の最大値を求めて下さい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- 多重辺や自己ループは存在しない
- 与えられるグラフは連結である

### Sample Explanation 1

下の図のように辺を追加していくと $ 4 $ 本の辺を追加することができ、これ以上辺を追加することはできません。 !\[\](https://img.atcoder.jp/code-festival-2017-qualb/6e99dccc06ac8b14d9ca2e297524bc0c.png)

### Sample Explanation 2

例えば、以下のような順番で辺を追加することによって $ 5 $ 本の辺を追加することができます。 - 頂点 $ 5 $ と頂点 $ 3 $ の間に辺を追加する。 - 頂点 $ 5 $ と頂点 $ 2 $ の間に辺を追加する。 - 頂点 $ 4 $ と頂点 $ 1 $ の間に辺を追加する。 - 頂点 $ 4 $ と頂点 $ 2 $ の間に辺を追加する。 - 頂点 $ 4 $ と頂点 $ 3 $ の間に辺を追加する。

## 样例 #1

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 6```

### 输出

```
4```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 1
5 4
5 1```

### 输出

```
5```

# 题解

## 作者：Sunqi666 (赞：5)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,to[200001],next[200001],tot,col[100001],head[100001],sum[3],cnt;
long long ans;
bool vis[100001],flag;
void add(int u,int v){to[++tot]=v,next[tot]=head[u],head[u]=tot;}
void dfs(int x,int color){
	++cnt;
	col[x]=color;
	sum[color]++;
	vis[x]=true;
	for(int i=head[x];i;i=next[i]){
		if(!vis[to[i]])dfs(to[i],3-color);
		else if(col[x]==col[to[i]])flag=true;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		dfs(i,1);
		if(!flag)ans+=1LL*sum[1]*sum[2];
		else ans+=1LL*cnt*(cnt-1)/2;
		sum[1]=sum[2]=flag=cnt=0;
	}
	printf("%lld\n",ans-m);
	return 0;
}
```
首先有一个坑，那就是，这题输出的是**能添加的边数**，而不是最后得到的图的边数

这是一道结论题。

首先，如果一个图中有奇环，那么这个图就不是二分图，反之就是二分图。

~~我们口糊一下。。~~ 对于一个奇环，在经过数次操作后总能变成一个完全图（手玩一下就知道），接着我们就能知道，只要一个图里面有奇环，那么这个图就可以变成一个完全图。此时边数即为 $C_n^2 -m$。

第二种情况就是这个图里面没有奇环。此时这个时候这个图就是一个二分图。那么此时显然我们可以把两个点集之间的点相互连边。这时我们就可以对图上的点进行染色，设A色有$x$个点，B色有$y$个点，显然答案为 $xy-m$

另外，~~不开long long见祖宗~~，一定记得开long long哦！

---

## 作者：newblash (赞：4)

[题目](https://www.luogu.org/problem/AT3574)
==

---

这题其实可以用二分图的思想解决。

我们把样例的图（$\downarrow$）拿过来研究一下，把每个点$01$染色一遍，然后我们就会发现……傻破来！题目原来就是叫我们把所有被染成$0$的点和所有被染成$1$的点连起来，然后问连完有多少条新增的边。于是我们就可以跑一遍$dfs$，边跑边记录染成$0$的点的数量（$cnt1$）和染成$1$的点的数量（$cnt2$），然后再乘起来，减去$m$就是我们要的答案了。

![](https://cdn.luogu.com.cn/upload/image_hosting/o1w33sgc.png)

但是有一个问题，就是图里面出现奇环的时候（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/8wwqbxpv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其实我们只要按题目要求连一遍之后就会发现……（为什么图这么小）

![](https://cdn.luogu.com.cn/upload/image_hosting/t8hcpy8y.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

傻破来！原先的奇环竟然变成了一个完全图！而且环外面的点可以连上环里面的所有点！再多画几个点（作者太懒了）之后我们就发现……(O_o)??整张图都变成了完全图！这时候，答案就是$\frac{n\times(n-1)}{2}-m$。

至于偶环，我们可以把它看成一条长链来处理（反正你要求的只是连完之后的总边数而已）。

---

重要的事情说三遍：$\mathfrak{LONG\ LONG!}\mathcal{LONG\ LONG!!}\mathbb{LONG\ LONG!!!}$
--

code:

```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define ll long long
using namespace std;

int head[maxn],cnt,vis[maxn];ll cnt1,cnt2,n,m;

struct edge{
	int to,nxt;
}e[maxn<<1];

void add(int u,int v){
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}

void dfs(int u,int fa,int col){
	if(!vis[u]) vis[u]=col;
	else {
		if(vis[u]!=col){
			printf("%lld",(n-1)*n/2-m);
			exit(0);
		}
		return ;
	}
	col?cnt1++:cnt2++;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,col^1);
	}
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0,1);
	printf("%lld",cnt1*cnt2-m);
}
```

---

## 作者：myee (赞：2)

### 前言

热知识：尝试给某场比赛出签到题时胡出了一模一样的 idea，然后查了一下发现撞原了！

说实话感觉这题不难啊。

### 思路

观察到每个连通块互不干扰，我们现在考虑各个连通块。

如果这个连通块是一个二分图，那么其会变成一个完全二分图：因为给定的操作相当于 $(a,b),(a,b'),(a',b)\Rightarrow(a',b')$，于是可以归纳出只要有路径的二分图不同侧点就会连边。

如果不是二分图，那么我们先通过 dfs 进行黑白染色，我们得到一个连通的生成二分子图，以及若干条同色点之间的连边。根据已有的结论，那个生成二分子图最终会变成一张完全二分图。然后若有同色边 $(a,a')$，那么我们就有 $(a,a'),(a',b),(a'',b)\Rightarrow(a,a'')$ 以及 $(a,a'),(a,b),(a',b')\Rightarrow(b,b')$。于是只要连通块不是二分图，最终就会变成完全图。

于是只用 dfs 搜索一遍各个连通块，判断是否是二分图就做完了。

---

