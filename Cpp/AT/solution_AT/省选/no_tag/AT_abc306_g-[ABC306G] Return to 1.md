# [ABC306G] Return to 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc306/tasks/abc306_g

$ N $ 頂点 $ M $ 辺の有向グラフがあります。 頂点には $ 1 $ から $ N $ までの番号が付けられていて、$ i $ 番目の辺は頂点 $ U_i $ から頂点 $ V_i $ に向かって伸びています。

あなたは今頂点 $ 1 $ にいます。 以下の行動をちょうど $ 10^{10^{100}} $ 回繰り返して頂点 $ 1 $ に戻ってくることが可能かどうか判定してください。

- 今いる頂点から伸びている辺を $ 1 $ つ選び、その辺が伸びている先の頂点に移動する。

$ T $ 個のテストケースが与えられるので、それぞれについて解いてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\leq\ T\ \leq\ 2\times\ 10^5 $
- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ M\ \leq\ 2\times\ 10^5 $
- 全てのテストケースにおける $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 全てのテストケースにおける $ M $ の総和は $ 2\ \times\ 10^5 $ 以下
- $ 1\ \leq\ U_i,\ V_i\ \leq\ N $
- $ U_i\ \neq\ V_i $
- $ i\neq\ j $ ならば $ (U_i,V_i)\ \neq\ (U_j,V_j) $

### Sample Explanation 1

$ 1 $ 番目のテストケースについて、 - 頂点 $ 1\ \rightarrow\ 2\ \rightarrow\ 1\ \rightarrow\ \dots $ という移動を繰り返す以外の選択肢はありません。 このとき、$ 10^{10^{100}} $ 回の移動をした時点で頂点 $ 1 $ にいるので、答えは `Yes` です。 $ 2 $ 番目のテストケースについて、 - 頂点 $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 1\ \rightarrow\ \dots $ という移動を繰り返す以外の選択肢はありません。 このとき、$ 10^{10^{100}} $ 回の移動をした時点で頂点 $ 2 $ にいるので、答えは `No` です。

## 样例 #1

### 输入

```
4
2 2
1 2
2 1
3 3
1 2
2 3
3 1
7 10
1 6
6 3
1 4
5 1
7 1
4 5
2 1
4 7
2 7
4 3
7 11
1 6
6 3
1 4
5 1
7 1
4 5
2 1
4 7
2 7
4 3
3 7```

### 输出

```
Yes
No
No
Yes```

# 题解

## 作者：六楼溜刘 (赞：12)

### 题意
- 给你一张有 $N$ 个结点 $M$ 条边的有向图，问能不能经过恰好 $10^{10^{100}}$ 条边从结点 $1$ 出发回到结点 $1$，可以重复经过同一个点或边。
- $2 \le N \le 2\times 10^5,1 \le M \le 10^5$，无重边（两条相向的有向边不算重边），自环，有 $T$ 组测试数据，$1\le T \le 2\times 10^5$。

### 题解
首先看到 $10^{10^{100}}$ 这个大数就容易想到这道题肯定和数论有关，很容易得出初步思路：**计算出所有由 $1$ 出发能到达 $1$ 的路径长度，用某种方法凑出 $10^{10^{100}}$。**

但这个思路本身有点小问题，比如这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/ok424eg3.png)

容易想到只需要重复走 $1 \to 2 \to 3 \to 2 \to 3 \to 1$ 这条路径即可，由于 $10^{10^{100}}$ 是 $5$ 的倍数所以显然可以，但从 $1$ 出发到达 $1$ 的路径要么就统计不到 $2 \to 3 \to 2$ 这个环（只统计简单路径），要么就会死循环。

关于如何解决这个问题，这个我们放到最后讲。

刚刚提过这个问题和数论有关，不妨把它放到一个代数的情景下，就转化成了这个问题：

> 求证 $a_1x_1+a_2x_2+\dots+a_Kx_K=10^{10^{100}}$ 是否有正整数解。

多元一次不定方程有解性证明让我们联想到什么？裴蜀定理！

---

简单讲一下裴蜀定理：

> 不定方程 $ax+by=c(a,b,c\in \mathbb{Z})$ 有整数解当且仅当 $\gcd(a,b)\mid c$。

这里讲一个我比较喜欢的证明（主要是其他的我看不懂）。

设集合 $A=\{ax+by\;|x,y\in \mathbb{Z}\}$，也就是有整数解时所有 $c$ 可能的取值。

假设集合 $A$ 中的最小正整数为 $s$，易证 $A$ 中所有数都被 $s$ 整除，假如存在 $n \in A$ 且 $s \nmid n$，那么可以令 $n=ps+q(0 <q<s)$，显然 $q$ 可以由 $n$ 和 $s$ 线性变化得到，所以它在集合 $A$ 中，与 $s$ 是最小矛盾。

接下来证明 $s=\gcd(a,b)$，转化为证明 $s\mid \gcd(a,b)$ 且 $\gcd(a,b) \mid s$，

首先，设 $s=ax_0+by_0$，显然 $\gcd(a,b)\mid ax_0$ 且 $\gcd(a,b)\mid by_0$，故 $\gcd(a,b) \mid s$。

然后，当取到 $x=1,y=0$ 时， $ax+by=a$，故 $a\in A$，同理，$b\in A$，又由于 $A$ 中所有数都被 $s$ 整除，所以 $s \mid a,s \mid b$，故 $s \mid \gcd(a,b)$。

综上，$s=\gcd(a,b)$

然后这个证明还可以拓展到多个数（比如 $ax+by+cz=d$），~~我邀请读者把这当做一种练习~~。

拓展到多个数得到的结论就是这道题要用的了，注意到 $10^{10^{100}}$ 所含的质因子仅有 $2$ 和 $5$，由于这个数足够大我们几乎可以把它看做 $2^{\infty}\times5^{\infty}$，所以只要找到多个合法的环（指上文所说 $1 \to \cdots \to 1$ 的和路径上额外的环）使得它们长度的 $\gcd$ 包含的质因子仅有 $2$ 和 $5$（注意 $\gcd=1$ 也是可行的）。容易发现一个数集中所有数的 $\gcd$ 一定是其中部分数 $\gcd$ 的约数，不妨直接求出所有路径长度的 $\gcd$ 来判断是否有解。

---

注意到裴蜀定理只能保证有整数解，我们还需要证明它有正整数解。

首先有个比较经典的结论：
> 对于不定方程 $ax+by=c$（$a,b,c\in \mathbb{Z},\gcd(a,b)=1$），它有正整数解的充分不必要条件是 $c> ab$。

这一部分类似于 [P3951 [NOIP2017 提高组] 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)，我还是简单证明一下。

设不定方程 $ax+by=c(\gcd(a,b)=1)$ 有一组整数特解 $x=x_0,y=y_0$，那么它的通解是什么呢？设另一组解为 $x_1,y_1$，令 $x_1=x_0+\lambda$，故 $ax_0+a\lambda+by_1=c$，则 $ax_0+b(y_1+\frac{a}{b}\lambda)=c$，即 $y_1=y_0-\frac{a}{b}\lambda$，由于 $x_1,y_1$ 是整数，不妨设一整数 $\theta=\frac{1}{b}\lambda$，可得方程通解为：

$$\begin{cases}x&=x_0+b\theta\\y&=y_0-a\theta\end{cases}$$

其中 $\theta$ 为任意整数。

回到原来的证明，设 $c=ab+z(z\in \mathbb{Z},z>0)$，原方程可化为：$ax+by=ab+z$。

假如 $x_0,y_0$ 是上方程的一组特解，易得：

$$\begin{cases}x&=x_0+b\theta\\y&=y_0-a\theta\end{cases}$$

另外我们可以得到 $y$ 关于 $x$ 的函数关系式：$y=\frac{ab+z-ax}{b}$，这关于 $x$ 的增加而线性减小。

由通解的那个式子容易发现我们可以把 $x$ 控制在 $[1,b]$ 这个范围内，那么最坏情况就是 $x=b$，此时 $y=\frac{z}{b}$，由于 $b>0,z>0$ ，所以 $y>0$，结合裴蜀定理可证 $y$ 为正整数。

此处我们用 $a_1,a_2,\dots a_K$ 来表示所有环的长度组成的数列。

首先可以列出方程 $a_1x_1+a_2x_2=y_1$（假如 $\gcd(a_1,a_2)\ne 1$ 我们可以左右同时除以 $\gcd$ 所以不影响，可以认为 $\gcd(a_1,a_2)=1$），为保证有整数解， $y_1>a_1a_2$，此时不妨用 $y_1$ 来替代 $a_1$ 和 $a_2$，原数列变为 $y_1,a_3,a_4\dots a_K$。

接下来同理，得到 $y_2>y_1a_3>a_1a_2a_3$，最终得到 $y_{K-1}>a_1a_2a_3\dots a_K$，也就是说只要原方程等号右侧的数足够大就必定有正整数解。

那么 $10^{10^{100}}$ 算不算一个足够大的数呢？由于最多有 $M$ 条路径（假设存在有自环且全是自环），每条路径长度最大为 $M$（假设只有一条路径），在这种完全不可能的情况下，$y_K=M^M$，那么 $M$ 最大是多少呢？答案是 $2 \times 10^5$，此时 $y_K=2^{2\times 10^5}\times10^{2\times 5\times 10^5}$，远小于 $10^{2\times 10^6}$，更是比 $10^{10^{100}}$ 小，肯定有正整数解。

~~其实也可以感性理解一下，这个数太大了，也就是说只要能凑出某个只含有质因子 $2$ 和 $5$ 的数就能凑出它。~~

---

现在难点都证明完了，我们考虑如何统计所有环的长度。

首先，我们不能直接用 dfs 统计，前面已经说过了。

考虑用 dfs 随便建一棵外向树 $T_1$ 包含尽量多的结点，再随便建一棵内向树 $T_2$ 包含尽量多的结点，那么一个环在这两棵树上应该长啥样呢？下文为方便叙述，设点 $i$ 在 $T_1$ 中与 $1$ 的距离为 $dis_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/we4pe7f6.png)

~~最近 csacademy.com 炸了将就一下。~~

在上图中，黑色和绿色的箭头表示有向边，蓝色是生成的外向树 $T_1$，红色是内向树 $T_2$，涂黑的结点是点 $1$。

我们发现，假设存在一条边 $u \to v$，这条边不在 $T_1$ 中，且 $v$ 在 $T_2$ 中（比如点 $A$ 就不在 $T_2$ 中），点 $u$ 在 $T_1$ 中（比如点 $B$ 就不在 $T_1$ 中），其实上图中四条绿边就是，那么就存在一个长度为 $\lvert dis_u+1-dis_v \rvert$ 的环。

这时候细心的读者就会发现问题了，比如左边那条边算出来就是 $1$，而并不存在一条长度为 $1$ 的环，这不会影响答案吗？其实它和那条长度为 $4$ 的环拼起来就能得到一条新的路径，好巧不巧这条新路径的长度刚好就是 $1+4=5$，而 $\gcd(n,n+k)=\gcd(n,k)$（辗转相除法，自己分类讨论证一下），之前说过我们只要求出**所有路径长度**的 $\gcd$ 再判断其质因子是否只含有 $2$ 和 $5$ 即可，所以这对答案并无影响。

而下面的那条边，它算出来是 $2$，这是一个在某条路径“中间”的小环，之前证过了必然存在正整数解，也就是说它附属的那条路径必然经过至少一次，我们利用这经过的一次把该跑的全跑完即可（感性理解一下），这就解决了开头提出的那个问题。

---

综上，整理一下整个实现过程：

1. 分别建正反两无向图。
1. 在正图上做 dfs 算出每个点和结点 $1$ 在外向树的距离，在反图上做 dfs 判断某个点是否在内向树上。
1. 枚举 $u$，找到所有合法的 $v$，直接统计所有路径长度的 $\gcd$。
1. 判断 $\gcd$ 是否含有 $2$ 和 $5$ 以外的质因子，得到答案。

### code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);++i)
#define fordown(i,s,e) for(int i=(s);i>=(e);--i)
using namespace std;
#define gc getchar()
int read(){//快读
	int x=0,f=1;char c;
	while(!isdigit(c=gc))if(c=='-')f=-1;
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
	return x*f;
}
const int N=2e5+5,inf=0x3f3f3f3f;
int t,n,m;
vector<int> e[N],re[N],nt[N];//正图，反图，不在外向树上的边
int ret[N],dpt[N];//能否回到 1，从 1 到该节点的距离
int vis[N];
void dfs(int x){//建外向树
	vis[x]=1;
	for(auto i:e[x]){
		if(vis[i]){
			nt[x].push_back(i);
			continue;
		}
		dpt[i]=dpt[x]+1;
		dfs(i);
	}
}
void dfs1(int x){//建内向树
	vis[x]=1;
	for(auto i:re[x]){
		if(vis[i]){
			if(i==1) ret[1]=1;//特判结点 1
			continue;
		}
		ret[i]=1;
		dfs1(i);
	}
}
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
signed main(){
	t=read();
	while(t--){
		n=read();m=read();
		forup(i,1,n){//注意清空
			e[i].clear();
			re[i].clear();
			nt[i].clear();
		}
		forup(i,1,m){
			int u=read(),v=read();
			e[u].push_back(v);
			re[v].push_back(u);
		}
		forup(i,1,n){
			ret[i]=vis[i]=0;
			dpt[i]=-1;
		}
		dpt[1]=0;
		dfs(1);
		forup(i,1,n){
			vis[i]=0;
		}
		dfs1(1);
		if(!ret[1]){//如果 ret[1]=0 说明整个图不存在包含结点 1 的环，无解。
			puts("No");
			continue;
		}
		int G=-1;
		forup(i,1,n){
			for(auto v:nt[i]){
				if(!ret[v]||dpt[i]==-1) continue;
				if(G==-1){//直接统计 gcd
					G=abs(dpt[i]+1-dpt[v]);
				}else{
					G=gcd(G,abs(dpt[i]+1-dpt[v]));
				}
			}
			if(G==1) break;//如果等于 1 就不可能再变小了，直接 break
			//其实这里还可以加一些其它剪枝，但是我懒得搞
		}
		while(!(G%2)) G/=2;
		while(!(G%5)) G/=5;//去掉所有质因子 2 和 5，判剩下的
		puts(G==1?"Yes":"No");
	}
}
```


---

## 作者：SoyTony (赞：6)

这也太强了！

容易想到的是用若干环拼出这个 $10^{10^{100}}$，也就是这些环的 $\gcd \mid 10^{10^{100}}$。

之后就不会了。

先正图反图两次 DFS，只留下 $1$ 所在强连通分量里的边，对正图跑 DFS 生成树，定义其深度从 $0$ 开始，然后有一个结论是：对于任何正整数 $a$，图中存在一个包含 $1$ 的且长度不是 $a$ 的倍数的环的充要条件是存在一条图上的边 $(u,v)$ 使 $dep_u+1-dep_v\not\equiv 0\pmod a$。

下面是证明。

必要性考虑证明逆否命题，即若不存在一条图上的边 $(u,v)$ 使 $dep_{u}+1-dep_v\not\equiv 0\pmod a$，则图中包含 $1$ 的环的长度都是 $a$ 的倍数。这是显然的，由于这样的环深度从 $0$ 开始，每次移动都相当于深度在模 $a$ 意义下加 $1$，又回到 $0$，所以环长一定是 $a$ 的倍数。

充分性不知道题解在说什么，但是若存在这样 $dep_u+1-dep_v\not\equiv 0\pmod a$ 的边，就说明 $(u,v)$ 是非树边且 $u$ 和 $v$ 是由两条不同的根链遍历到的，由于 $dep_u+1-dep_v\not\equiv 0\pmod a$，那么 $1\to u$ 的根链长加 $1$ 与 $1\to v$ 的根链长，在模 $a$ 意义下不同余，也就是两条 $1$ 到 $v$ 的路径长不同余。这时候同样是从 $v$ 回到 $1$，两个环长度一定不同余，那么至少有一个不是 $a$ 的倍数。

这样我们对所有环求 $\gcd$ 就可以对所有 $dep_u+1-dep_v$ 求 $\gcd$。


```cpp
int t;
int n,m;
vector<int> E1[maxn],E2[maxn];
bool vis1[maxn],vis2[maxn];
int dep[maxn];
void dfs1(int u,int d){
    vis1[u]=true,dep[u]=d;
    for(int v:E1[u]){
        if(vis1[v]) continue;
        dfs1(v,d+1);
    }
}
void dfs2(int u){
    vis2[u]=true;
    for(int v:E2[u]){
        if(vis2[v]) continue;
        dfs2(v);
    }
}
int main(){
    t=read();
    while(t--){
        n=read(),m=read();
        for(int i=1;i<=n;++i){
            E1[i].clear(),E2[i].clear();
            vis1[i]=false,vis2[i]=false,dep[i]=0;
        }
        for(int i=1;i<=m;++i){
            int u=read(),v=read();
            E1[u].push_back(v);
            E2[v].push_back(u);
        }
        dfs1(1,0);
        dfs2(1);
        int g=0;
        for(int u=1;u<=n;++u){
            if(!vis1[u]||!vis2[u]) continue;
            for(int v:E1[u]){
                if(!vis1[v]||!vis2[v]) continue;
                if(!g) g=abs(dep[u]+1-dep[v]);
                else g=__gcd(g,abs(dep[u]+1-dep[v]));
            }
        }
        if(!g) printf("No\n");
        else{
            while(g%2==0) g/=2;
            while(g%5==0) g/=5;
            if(g==1) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
```

---

## 作者：xrk2006 (赞：6)

# 【题解】[ABC306G] Return to 1

[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/ABC306G.html)

## 题目链接

[ABC306G - Return to 1](https://atcoder.jp/contests/abc306/tasks/abc306_g)

## 题意概述

本题多测，$T$ 组数据。

对于每组数据，给定一个 $n$ 个点 $m$ 条边的有向图，无重边自环。

问从顶点 $1$ 出发，能否恰好走 ${10^{10}}^{100}$ 步回到 $1$。

## 数据范围

- $1≤T,N,M≤2\times 10^5$
- $\sum N \le 2 \times 10^5,\sum M \le 2 \times 10^5$

## 思路分析

首先，可以删掉图中无法从顶点 $1$ 出发到达的点，和无法到达顶点 $1$ 的点，因为无论怎么走都不可能经过这些点。那么删掉后的图是强联通的。

---

设 $L$ 表示图中所有经过 $1$ 的环长集合，$d$ 为 $L$ 中所有数的 $\gcd$。那么若从 $1$ 出发能恰好走 ${10^{10}}^{100}$ 步回到 $1$ 当且仅当：$d$ 是 ${10^{10}}^{100}$ 的约数。

>证明：
>
>由于我们要从开始恰好走 ${{10}^{10}}^{100}$ 步回到 $1$。假设原图中有两个长度为 $a$ 和 $b$ 的环，那么就相当于找两个非负整数 $x$ 和 $y$，使得 $ax+by=c$，其中 $c={{10}^{10}}^{100}$。
>
>那么问题就转化为：对于方程 $ax+by=c$，它有解的充要条件当且仅当 $d|c$，其中 $d=\gcd(a,b)$。
>
>**充分性**：根据**裴蜀定理**可知：存在 $x_0,y_0$ 使得 $ax_0+by_0=d$，又 $d|c$，所以 $c=dk=(ax_0+by_0)k=a(kx_0)+b(ky_0)$，所以方程有整数解 $(kx_0,ky_0)$；
>
>**必要性**：因为 $ax_0+by_0=c$，$d$ 是 $a,b$ 的最大公约数，所以 $d|a,d|b$，所以 $d|(ax_0+by_0)$，即 $d|c$。
>
>更一般地，当原图中环的个数超过两个时，我们可以用归纳法证明出对于 $L$ 里所有元素 $a_1-a_n$，方程 $a_1x_1+a_2x_2+a_3x_3+\cdots+a_nx_n=c$ 有解当且仅当 $\gcd(a_1,a_2,\cdots,a_n)|c$。

那么我们现在就可以有一个清晰的思路：暴力把所有的环长求出来，取它们的 $\gcd$，判断其是否为 ${{10}^{10}}^{100}$ 的约数。

但是当经过 $1$ 的环很多时，这种方法复杂度显然接受不了，所以考虑优化。

---

走到这一步，问题实际上可以转化为：

> 给定若干个经过 $1$ 的环，如何求出这些环长的 $\gcd$？

我们考虑反向思考，首先要弄明白一个问题：对于一个数 $x$，怎么判断它是否是所有经过 $1$ 环长的**公约数**（注意这里不是最大）？

有一个方法是：从 $1$ 开始 dfs 一遍所有点计算出每个点 $i$ 到 $1$ 的距离 $dep_i$，那么要使得如果 $x$ 是所有环长的公约数，则在 $\bmod x$ 意义下，对于图中的每条边 $u\rightarrow v$ 都满足 $dep_u+1=dep_v$。

> 证明：
>
> 首先考虑简单环：
>
> - 如果给定一堆简单环，我们从 $1$ 开始 dfs 给每个点标记一个模 $x$ 意义下的 $dep$，那么每个环一定都是按照一定顺序像 $0,1,2,\cdots ,x-1,0,1,\cdots$ 这样标号的。
> - 假设一个环环长为 $len$，那么从 $1$ 开始 dfs，到第 $len-1$ 个点的过程中，对于非第 $len-1$ 个点，无论如何一定有 $dep_u+1=dep_v$，这是显然的。
> - 对于第 $len-1$ 个点当且仅当它的 $dep$ 不是 $x-1$ 时，这个点的编号加一模 $x$ 不等于 $dep_1=0$，此时 $x$ 一定就不是该环环长的约数，与“$x$ 是所有环长公约数”矛盾。
>
> 然后考虑复杂环：
>
> - 复杂环与简单环的最主要区别就在于简单环一定不会存在公用边，也就是不会多个环经过同一条边的情况，而复杂环可能会出现。
>
> - 假设有两个环，环长均是 $x$ 的约数，从 $1$ 出发经过不同的路径到达一个点 $u$，然后再沿着同一条从 $u$ 到 $1$ 路径回到 $1$。比如下图（两个环分别从 $1$ 出发沿着不同路径到达 $3$ 再沿着相同的路径从 $3$ 回到 $1$）。定义这个 $u$ 为两个环的**交汇点**，$len_1$ 和 $len_2$ 为两个环环长。
>
> - 那么对于两个环非交汇点，同样无论如何一定有 $dep_u+1=dep_v$（与简单环相同）。
> - 对于两个环交汇点 $u$（相当于图中的 $3$），如果存在其中一个环的一条边 $v\rightarrow u$，使得模 $x$ 意义下不满足 $dep_v+1= dep_u$，那么当且仅当这两个环的环长差 $|len_1-len_2|$ 不是 $x$ 的倍数。
> - 由于 $x$ 是 $len_1$ 和 $len_2$ 的公约数，所以 $\gcd(len_1,len_2)|x$。根据**更相减损法**，有 $\gcd(len_1,len_2)=\gcd(len_1,|len_1-len_2|)$，所以 $\gcd(len_1,|len_1-len_2|)|x$，所以 $|len_1-len_2|$ 一定是 $x$ 的倍数。
>
> ![img](https://cdn.luogu.com.cn/upload/image_hosting/fc1ago6z.png)

由于 $x$ 是所有环长的公约数时，在 $\bmod x$ 意义下，对于图中的每条边 $u\rightarrow v$ 都满足 $dep_u+1=dep_v$，即 $dep_u+1-dep_v\equiv 0 \pmod {x}$，所以 $x$ 是所有 $dep_u+1-dep_v$ 的公约数。

同理，要使得 $x$ 是所有环长的 $\gcd$，那么它也应该是所有 $dep_u+1-dep_v$ 的 $\gcd$。

那么我们直接枚举所有边 $u \rightarrow v$ 求出 $dep_u+1-dep_v$ 的 $\gcd$ 即可。

最后一步就是要判断这个 $\gcd$ 是不是 ${{10}^{10}}^{100}$ 的约数。

由于 ${{10}^{10}}^{100}$ 只有 $2$ 和 $5$ 两个质因数，且 ${{10}^{10}}^{100}$ 很大，所以只需要判断 $\gcd$ 是否只有 $2$ 和 $5$ 两个质因子，若是，则答案 `Yes`，反之是 `No`。

---

总体来说，这个题大的方面分为三步：先删掉图中无关的点；再将问题转化为求所有环长的 $\gcd$；最后求这些环长 $\gcd$。

总复杂度 $O(T\max(n,m))$。

注意多测清空。

## 代码实现

```cpp
//G
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define mk make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=2e5+10;
int ok[maxn],dep[maxn];//ok[i] 表示 i 是否为有用点（即能不能到达 1）。

basic_string<int>edge[maxn],edge2[maxn];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void dfs(int x)
{
	ok[x]=1;
	for(int y:edge2[x])
	{
		if(ok[y])continue;
		dfs(y);
	}
}

void dfs2(int x)
{
	for(int y:edge[x])
	{
		if(!ok[y])continue;
		if(dep[y]!=-1)continue;
		dep[y]=dep[x]+1;
		dfs2(y);
	}
}

int gcd(int a,int b){if(b==0)return a;return gcd(b,a%b);}

int main()
{
	int T=read();
	while(T--)
	{
		int n,m;
		n=read();m=read();
		for(int i=1;i<=n;i++)edge[i].clear(),edge2[i].clear(),dep[i]=-1,ok[i]=0;
		for(int i=1;i<=m;i++)
		{
			int u,v;
			u=read();v=read();
			edge[u]+=v;
			edge2[v]+=u;
		}
		dfs(1);
		dep[1]=0;
		dfs2(1);
		int d=0;
		for(int u=1;u<=n;u++)
		{
			if(dep[u]==-1)continue;
			for(int v:edge[u])
			{
				if(dep[v]==-1)continue;
				d=gcd(d,abs(dep[u]+1-dep[v]));
			}
		}
		if(!d){cout<<"No"<<'\n';continue;}//没有经过 1 的环。
		while(d%2==0)d/=2;
		while(d%5==0)d/=5;
		if(d==1)cout<<"Yes"<<'\n';
		else cout<<"No"<<"\n";
	}
	return 0;
}
```



---

## 作者：_•́へ•́╬_ (赞：5)

## 思路

如果没有包含 $1$ 的环，直接 `NO`。

记 $ans$ 为所有包含 $1$ 的环的长度的 $\gcd$。

如果满足 $ans|10^{10^{100}}$，根据裴蜀定理（就是你 exgcd 板子判无解的那个），我们一定有方法安排每个环走多少次，使得恰好 $10^{10^{100}}$ 步后回到 $1$。

显然 $ans\leq n$，所以 $ans|10^{18}\Leftrightarrow ans|10^{10^{100}}$。（之前这里我写了 $10^8$，被指出是错误的，但是 pp 了）

实际上我们不需要找到所有的环长。根据 $\gcd(a,b)=\gcd(a-b,b)$，可以使用以下方法实现：

## code

```cpp
#include<stdio.h>
#include<vector>
#define N 200009
#define abs(x) ((x)>>31?-(x):(x))
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,m,len,dis[N];vector<int>e1[N],e2[N];bool v[N],ans;
struct __readt__{inline __readt__(){read(t);}}_readt___;
inline int gcd(const int&x,const int&y){if(y)return gcd(y,x%y);return x;}
inline void dfs(const int&i)
{
	if(!i)if(dis[i])len=dis[i];
	for(int j=0;j<e2[i].size();++j)if(!v[e2[i][j]])
		v[e2[i][j]]=1,dis[e2[i][j]]=dis[i]+1,dfs(e2[i][j]);
}
inline void dfs2(const int&i,const int&d)
{
	if(!v[i])return;
	if(~dis[i])
	{
		if(!(1000000000000000000ll%gcd(len,abs(d-dis[i]))))ans=1;
		return;
	}
	dis[i]=d;
	for(int j=0;j<e1[i].size()&&!ans;++j)dfs2(e1[i][j],d+1);
}
main()
{
	read(n);read(m);
	for(int i=0;i<n;v[i]=dis[i]=0,e1[i].clear(),e2[i++].clear());
	for(int u,v;m--;)read(u),read(v),--u,--v,
		e1[u].emplace_back(v),e2[v].emplace_back(u);
	dis[0]=0;dfs(0);ans=0;
	if(!v[0]){printf("No\n");goto nxt;}
	if(!(1000000000000000000ll%len)){printf("Yes\n");goto nxt;}
	for(int i=0;i<n;dis[i++]=-1);
	dfs2(0,0);
	printf(ans?"Yes\n":"No\n");
	nxt:if(--t)main();
}
```

---

## 作者：_determination_ (赞：2)

神秘题目。

好的这个 $10^{10^{100}}$ 看着十分诡异，我们要凑出来这个数肯定是在环上来回跑凑出来这个数。

首先我们先只保留 1 所在强联通分量，不然不好搞。  
之后所说的所有图如果没特殊说明就是这样一整个联通分量的图。

那么根据裴蜀定理，只要你图中的环长度 $\gcd$ 出来质因子只包括 2 和 5 就好了。那么我们的问题就是怎样求出所有环的长度的 $\gcd $。

不难想到建立 bfs 生成树，考虑每条边 $(u,v)$ 的影响。

1. 对于生成树上的边，我们不管他。
2. 对于其他边，我们发现我们找到了一个长度为 $dis_v+x$ 和一个长度为 $dis_u+1+x$ 的环。

根据辗转相除的结论，这两个环的 $\gcd$ 一定是 $dis_u+1-dis_v$ 的因数。

那么我们把这些因数 $\gcd$ 起来就是最终的 $\gcd$。

为什么？

首先不会出现两个环的 $\gcd$ 没被考虑导致最后的答案大。因为 $\gcd(\gcd(x,y),\gcd(y,z))| \gcd(x,z)$。

那又要有人问了，主播主播，你处理两个环的关系的时候只处理了两个环的差值，那会不会有问题呢？

不会的，因为返租边这样得到的差值就是环长，横叉边没考虑的是差值与更小的那个环的 $\gcd$，但是这个更小的环的长度已经被我们记下来了。

[Link.](https://atcoder.jp/contests/abc306/submissions/65563425)

---

## 作者：cwfxlh (赞：2)

# [AT_abc306_g](https://www.luogu.com.cn/problem/AT_abc306_g)    

发现我们可以将所有与 $1$ 不在一个强连通分量的点都排除，之后只需要求经过 $1$ 的所有环的 $\gcd$ 是否整除 $100^{100}$ 即可。以 $1$ 为起点建立一棵 dfs 树，则存在环长度不是 $a$ 的倍数的充要条件是存在一条边 $(u,v)$ 满足 $dep_u+1-dep_v\mod  a\neq 0$。必要性是显然的。考虑充分性，给出一条从 $v$ 到 $1$ 的路径长为 $x$，则有两个环：$1-u-v-1$ 和 $1-v-1$，长度分别为 $dep_u+1+x$ 和 $dep_v+x$，二者必有一个不是 $a$ 的倍数。于是对所有边的 $dep_u+1-dep_v$ 取 $\gcd$ 即可。    

代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,ans;
int dfn[500003],low[500003],idx,scc,col[500003],instk[500003],stk[500003],tot,dep[500003];
vector<int>E[500003];
set<int>R[500003];
void tarjan(int now){
	dfn[now]=low[now]=++idx;
	stk[++tot]=now;
	instk[now]=1;
	for(auto i:E[now]){
		if(dfn[i]==0){
			tarjan(i);
			low[now]=min(low[now],low[i]);
		}
		else if(instk[i])low[now]=min(low[now],dfn[i]);
	}
	if(dfn[now]==low[now]){
		scc++;
		while(1){
			k1=stk[tot];
			tot--;
			instk[k1]=0;
			col[k1]=scc;
			if(k1==now)break;
		}
	}
	return;
}
void dfs(int now){
	for(auto i:E[now]){
		if(col[i]!=col[now])continue;
		if(dep[i]==0){
			dep[i]=dep[now]+1;
			dfs(i);
		}
		if(ans==0)ans=abs(dep[now]-dep[i]+1);
		else ans=__gcd(ans,abs(dep[now]-dep[i]+1));
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			E[i].clear();
			R[i].clear();
			E[i].shrink_to_fit();
			dfn[i]=low[i]=instk[i]=col[i]=dep[i]=0;
		}
		idx=scc=tot=0;
		for(int i=1;i<=m;i++){
			cin>>k1>>k2;
			auto p=R[k1].lower_bound(k2);
			if(p==R[k1].end()||(*p)!=k2)E[k1].emplace_back(k2);
			R[k1].insert(k2);
		}
		for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
		ans=0;
		dep[1]=1;
		dfs(1);
		while(ans!=0&&ans%2==0)ans/=2;
		while(ans!=0&&ans%5==0)ans/=5;
		if(ans==1)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```


---

## 作者：rzh01014 (赞：1)

# [abc306_g](https://www.luogu.com.cn/problem/AT_abc306_g)
### 题目描述
有一个有向图，图中有 $N$ 个顶点和 $M$ 条边。每个顶点被标号从  $1$ 到 $N$，第 $i$ 条边从顶点 $U_i$ 指向顶点 $V_i$。    
现在你位于顶点 $1$。请判断是否可以通过以下操作恰好重复 $10^{10^{100}}$ 次并回到原点 $1$。    

- 从当前的顶点选择一条出边，将自己移动到该边指向的顶点。 
### 做法
首先我们需要简化一下图。    
易发现，需要删掉无法从 $1$ 到达的点，还有无法到达 $1$ 的点。无论怎么走，必不会经过这些点。   
在简化完图后，其一定是强连通的。     
可以选出一个包含顶点 $1$ 的环长度集合，令 $d$ 为该集合中数字的最大公约数，题目答案为真当且仅当 $d|10^{10^{100}}$。    

证明:   
假设图中有两个长度为 $a$ 和 $b$ 的环，令 $c=10^{10^{100}}$，则该题目会变为对于方程 $ax+by=c$ 是否有解。     
该方程有解的充要条件为 $\gcd(a,b)|c$。
> 充分性：
> 根据裴蜀定理可知：$ax+by=d$ 有解，$d$ 为 $\gcd(a,b)$。因为 $d|c$，所以方程 $ax+by=c$ 必有解。
> 
>必要性：
>因为 $ax+by=c$，$d=\gcd(a,b)$。又因为 $d|a$，$d|b$，$c=ax+by$，所以必有 $d|c$。

对于一般情况，当图中的环的个数超过两个时，可以用归纳法证明出对于方程 $\sum_{i=1}^{n} a_i\times x_i = c$ 有解的充要条件为 $\gcd(a_1,a_2,a_3,…,a_n)|c$。  
由于 $c$ 足够大，因此只需判断 $\gcd$ 中是否有除了 $2$ 和 $5$ 的因子。   
由于环长集合可能是一个无限集，所以不能直接找到其 $\gcd$。   
考虑任取一个以 $1$ 为根节点的 DFS 生成树 $T$，令 $d_i$ 为点 $i$ 在 $T$ 上的深度。   
性质：对于任意的正整数 $x$ 而言，$L$ 中包含一个不是 $x$ 的倍数的条件为存在一条连着 $u,v$ 的有向边，使得 $|d_u+1-d_v|\neq 0\pmod x$。    
对于可行解 $\gcd$ 中只存在素因子 $p=2,5$，故考虑环长是否为 $p$ 的倍数。    
证明：环的长度为 $p$ 的倍数，那么对于所有的边 $u,v$，有 $d_u+1\equiv d_v \pmod p$，就有 $d_u+1-d_v\equiv \pmod p$。因此对于所有的边 $u,v$ 有 $p|(d_u-d_v+1)$，所以 $p$ 整除所有 $u,v$ 对应的 $d_u-d_v+1$ 的 $\gcd$。    
所以 $T$ 上所有非树边所对的 $|d_u-d_v+1|$ 的最大公约数即要求的所有环长的 $\gcd$。
### code
``` cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,m,T;
int vis1[N],vis2[N];
vector<int>ve1[N],ve2[N];
int gcd(int a,int b){
	if(a>b) swap(a,b);
	return a==0?b:gcd(b%a,a);
}
void dfs1(int u,int st){
	vis1[u]=st;
	for(int v:ve1[u]){
		if(!vis1[v]) dfs1(v,st+1);
	}
}
void dfs(int u){
	vis2[u]=1;
	for(int v:ve2[u]){
		if(!vis2[v]) dfs(v);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) ve1[i].clear(),ve2[i].clear(),vis1[i]=vis2[i]=0;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			ve1[u].emplace_back(v);
			ve2[v].emplace_back(u);
		}
		dfs1(1,0);
		dfs(1);
		int anss=0;
		for(int i=1;i<=n;i++){
			if(!vis1[i]||!vis2[i]) continue;
			for(int v:ve1[i]){
				if(!vis1[v]||!vis2[v]) continue;
				if(!anss) anss=abs(vis1[i]+1-vis1[v]);
				else anss=gcd(anss,abs(vis1[i]+1-vis1[v]));
			}
		}
		if(!anss) cout<<"No\n";
		else{
			while(anss%10==0) anss/=10;
			if(anss%2==0) while(anss%2==0) anss/=2;
			else while(anss%5==0) anss/=5;
			cout<<(anss==1?"Yes":"No")<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：Nelofus (赞：1)

#### 简要题意：
给出一张 $n$ 点 $m$ 边的有向图，你在节点 $1$，问能否走恰好 $10^{10^{100}}$ 步回到 $1$。

$n,m\le 2\times 10^5$
#### 简要题解
显然每一次走都是走一个包含 $1$ 的环，只保留包含 $1$ 的强联通分量中的所有边，设一共有 $k$ 个环，环长分别为 $a_1,a_2,\cdots, a_k$。

问题实际上是问
$$
\sum_{i=1}^{k}a_ix_i=10^{10^{100}}
$$
是否有解，根据裴蜀定理，有解当且仅当
$$
\gcd_{i=1}^{k}a_i|10^{10^{100}}
$$
也就是所有环长的 $\gcd$ 只有 $2$ 和 $5$ 的质因子。

再考虑怎么计算所有环长的 $\gcd$ 的信息，这里有一个结论：

设点 $\operatorname{dep}(u)$ 为 DFS 树上 $u$ 的深度，则存在一个长度不是 $p$ 的倍数的环，当且仅当：
$$
\exists (u,v)\in E, |\operatorname{dep}(u)-\operatorname{dep}(v)+1|\not \equiv 0\pmod p
$$

一个并不严谨的证明如下：

1. $(u,v)$ 是树边

	那么 $\operatorname{dep}(u)-\operatorname{dep}(v)+1=0$，不对答案造成影响。
2. $(u,v)$ 是返祖边
	
	那么 $\operatorname{dep}(u)-\operatorname{dep}(v)+1$ 就是环长。
    
3. $(u,v)$ 是横叉边
	
    这实际上是在说两条到 $v$ 的路径 $1\rightarrow v$（DFS树上的那条） 与 $1\rightarrow u\rightarrow v$（DFS树先到 $u$ 再到 $v$）在 $\bmod p$ 意义下不等长。
    
    那么考虑所有 $v\rightarrow 1$ 的路径，假如它们所有在加上 $\operatorname{dep}(v)$ 后 $\bmod p$ 都是 $0$，那么在加上 $1+\operatorname{dep}(u)$ 后 $\bmod p$ 就不是 $0$，存在一个环长不是 $p$ 的倍数的环，反之亦然。

	所以必定存在一个环长不是 $p$ 的倍数的环。
    
所以，如果对于所有 $(u,v)$ 都有 $|\operatorname{dep}(u)+1-\operatorname{dep}(v)|\equiv 0\pmod p$，说明所有环长都是 $p$ 的倍数。

那么对所有 $|\operatorname{dep}(u)+1-\operatorname{dep}(v)|$ 取 $\gcd$，即为所有环长的 $\gcd$。
```cpp
#include <bits/stdc++.h>
using i64 = long long;

template<typename Ta, typename Tb>
inline void chkmin(Ta &a, const Tb &b) {if (a > b)	a = b;}

constexpr int N = 2e5 + 10;
int n, m;
std::basic_string<int> G[N];
int dfn[N], low[N], dfc;
int stk[N], tt;
bool instk[N];
int belong[N], SCCC;

void dfs(int u) {
	dfn[u] = low[u] = ++dfc;
	instk[u] = true;
	stk[++tt] = u;

	for (const int &v : G[u]) {
		if (!dfn[v]) {
			dfs(v);
			chkmin(low[u], low[v]);
		} else if (instk[v]) {
			chkmin(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		SCCC++;
		while (true) {
			instk[stk[tt]] = false;
			belong[stk[tt]] = SCCC;
			if (stk[tt--] == u)
				break;
		}
	}
}

int dep[N];
bool vis[N];
int g;

void clear() {
	for (int i = 1; i <= n; i++)
		G[i].clear();
	SCCC = 0;
	dfc = 0, tt = 0;
	g = 0;
	memset(dfn + 1, 0, n * sizeof(int));
	memset(low + 1, 0, n * sizeof(int));
	memset(instk + 1, 0, n * sizeof(bool));
	memset(dep + 1, 0, n * sizeof(int));
	memset(vis + 1, 0, n * sizeof(bool));
}

void dfs2(int u) {
	vis[u] = true;
	for (const int &v : G[u]) {
		if (belong[v] != belong[u])
			continue;
		if (!vis[v]) {
			dep[v] = dep[u] + 1;
			dfs2(v);
		}
		g = std::gcd(g, abs(dep[u] - dep[v] + 1));
	}
}

void solve() {
	std::cin >> n >> m;
	clear();
	for (int i = 1; i <= m; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u] += v;
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			dfs(i);
	dfs2(1);
	if (g) {
		while (g % 2 == 0)	g /= 2;
		while (g % 5 == 0)	g /= 5;
	}
	if (g == 1)
		std::cout << "Yes" << '\n';
	else
		std::cout << "No" << '\n';
}

int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：cosf (赞：1)

## [ABC306G](https://www.luogu.com.cn/problem/AT_abc306_g) Return to 1

## 题目分析

注意到 $10^{10^{100}}(\textsf{googolplex})$ 实际上就是一个充分大的数，并且只有质因子 $2$ 和 $5$。所以题目相当于求所有环长的最大公因数是不是只有 $2$ 和 $5$ 这两个质因子。

为什么呢？假设环长为 $a_1, \dots, a_n$，则会存在一组 $x_1, \dots, x_n$，满足

$$
\sum_{i=1}^n a_ix_i = n\operatorname{gcd}_{i=1}^na_i
$$

其中 $n$ 是整数。当 $n \to +\infty$ 时，肯定有一组 $x_n$ 全部大于或等于 $0$。而题目中的 $\textsf{googolplex}$ 已经充分大了，故得证。

但是，环不可能在时限中每个遍历一遍，那么我们可以利用一个式子代替它：

$$
\operatorname{gcd}_{i=1}^M |d_{U_i} + 1 - d_{V_i}|
$$

其中 $d_i$ 表示在图中以 $1$ 为根 $i$ 的 **任意** 顺序深搜深度，$U_i, V_i$ 均在 $1$ 所在强连通分量中。

这个任意是指对于通向 $i$ 的所有边 $u_1 \to i, u_2 \to i, \dots, u_k \to i, \exists j, d_{u_j} + 1 = d_i$。

接下来证明可行性（接下来只考虑在 $1$ 所在强连通分量重的点）。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/vmftd8q1.png)

### 情况 1

对于这种情况（每个环“互不相干”），对于每个 $V_i \not= 1$ 的时候均有 $d_{U_i} + 1 = d_{V_i}$，而对于 $V_i = 1$ 的时候，$d_{U_i} + 1$ 就是环长，$d_1 = 0$，显然成立

![](https://cdn.luogu.com.cn/upload/image_hosting/9bj6nuo8.png)

### 情况 2

对于这种情况，即整个图可以简化为三条路径的情况。我们假设在深搜的时候 $d_2$ 是由路径 $1$ 递推得来的。那么，此时的环 $\operatorname{gcd}=(l_1 + l_3, l_2 + l_3) = (l_1 + l_3, l_2 - l_1)$。（$l_i$ 表示路径 $i$ 长度）

根据深搜递推公式，对于 $d_{U_i} + 1 \not= d_{V_i}$ 的情况也只有 $V_i=1$ 的那条和 $V_i=2$ 且 $U_i$ 在路径 $2$ 上那条，共两条边。那么对于 $V_i=1$ 的那条，$d_{U_i} + 1 = l_1 + l_3$，而对于另外那条，有 $d_{U_i}+1 = l_2, d_2 = l_1, d_{U_i} + 1 - d_{V_i} = l_2 - l_1$，两个求 $\gcd$ 也是 $(l_1 + l_3, l_2 - l_1)$，与求环 $\gcd$ 是一样的。

---

那么，对于一般情况，每个图都可以理解为情况 1 和情况 2 的结合，意思就是说，对于情况 1 中标出的每个 $a_1, a_2, \dots$，都是一个情况 2。

而情况 2 也可以把其中的三条路径任意一条换成一个情况 2，例如说

![](https://cdn.luogu.com.cn/upload/image_hosting/1p3cr630.png)

经过推导能够发现，这还是一样的。

这也就证明了，题目就是要求

$$
\operatorname{gcd}_{i=1}^M |d_{U_i} + 1 - d_{V_i}|
$$

是不是只有质因数 $2$ 和 $5$ 了（注意 $U_i$ 和 $V_i$ 要在 $1$ 所在的强连通分量中！）。

## [参考代码](https://atcoder.jp/contests/abc306/submissions/42934436)

```cpp
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<int> to[200005];
vector<int> from[200005];

int visb[200005];
int visf[200005];
int dis[200005];

void dfs_fore(int c, int d) // 前面提到的深搜，d 为深度
{
    for (int i : to[c])
    {
        if (!visf[i])
        {
            visf[i] = 1;
            dis[i] = d + 1;
            dfs_fore(i, d + 1);
        }
    }
}
void dfs_back(int c) // 把能达到 1 的点找出来
{
    for (int i : from[c])
    {
        if (!visb[i] && visf[i])
        {
            visb[i] = 1;
            dfs_back(i);
        }
    }
}

template <class _Tp>
_Tp _gcd(_Tp __m, _Tp __n)
{
    return __n == 0 ? __m : _gcd<_Tp>(__n, __m % __n);
}

int main()
{
    int t, n = 0, m = 0;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            to[i].clear(); // 清空
            from[i].clear();
            visb[i] = visf[i] = 0;
            dis[i] = 0;
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            to[u].push_back(v);
            from[v].push_back(u);
        }
        visb[1] = visf[1] = 1;
        dfs_fore(1, 0);
        dfs_back(1);
        long long g = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!visb[i] || !visf[i])
            {
                continue;
            }
            for (int t : to[i])
            {
                if (visb[t] && visf[t]) // 如果都在 scc 上
                {
                    g = _gcd(g, (long long)(abs(dis[i] + 1 - dis[t])));
                }
            }
        }
        if (g == 0)
        {
            cout << "No" << endl;
            continue;
        }
        while ((g & 1) == 0)
        {
            g >>= 1;
        }
        while (g % 5 == 0)
        {
            g /= 5;
        }
        if (g == 1)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}

```

---

个人认为本题评绿。



---

## 作者：happybob (赞：0)

题意：

给定一个 $n$ 个点 $m$ 条边的有向图，判断是否存在一条长度恰好为 $10^{10^{100}}$ 的不要求简单的路径，起点和终点都为 $1$ 号点。 

$1 \leq n, m \leq 2 \times 10^5$。

解法：

首先拉出包含点 $1$ 的 SCC，非 SCC 内的点与边不重要。现在图是一个强连通图。

考虑此图的环长为 $c_1,c_2,\cdots,c_k$，由于 $10^{10^{100}}$ 非常大，即要求判断是否存在 $x_1,x_2,\cdots,x_k$ 使得 $\forall 1 \leq i \leq k, x_i \geq 0$ 且 $\sum \limits_{i=1}^k x_ic_i = 10^{10^{100}}$，根据相关数论定理，充要条件为 $\gcd(c_1,c_2,\cdots,c_k) \mid 10^{10^{100}}$。

令 $d = \gcd(c_1,c_2,\cdots,c_k)$，我们需要判定 $d \mid 10^{10^{100}}$ 是否成立。从质因数角度分析这个问题，等价于判定 $d$ 质因数是否只含有 $2$ 与 $5$。所以只要求出 $d$，后面的过程是容易的。

对于强连通图求 $d$ 是经典结论。考虑以任意一个点为根建出 DFS 树，并记 $dep_u$ 表示 $u$ 在 DFS 树上的深度，对于每条边 $u \rightarrow v$，将结果与 $\left|dep_u-dep_v+1\right|$ 取 $\gcd$ 即可。证明考虑分返祖边和横叉边考虑一下即可。

[Submission Link.](https://atcoder.jp/contests/abc306/submissions/60490874)

---

