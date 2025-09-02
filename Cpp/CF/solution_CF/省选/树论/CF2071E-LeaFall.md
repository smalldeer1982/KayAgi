# LeaFall

## 题目描述

给定一棵包含 $n$ 个顶点的树 $^{\text{∗}}$。每个顶点 $i$（$1 \le i \le n$）会以 $\frac{p_i}{q_i}$ 的概率掉落。求最终形成的森林 $^{\text{‡}}$ 中不同顶点构成叶子节点 $^{\text{§}}$ 的无序对 $^{\text{†}}$ 数量的期望值，结果对 $998\,244\,353$ 取模。

注意：当顶点 $v$ 掉落时，其自身及所有相连的边将被移除，但相邻顶点的掉落状态不受 $v$ 的影响。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 无序对指不考虑元素顺序的二元组。例如，无序对 $(1, 2)$ 与 $(2, 1)$ 视为相同。

$^{\text{‡}}$ 叶子节点指恰好连接一条边的顶点。

$^{\text{§}}$ 森林是多个不连通树的集合。

## 说明/提示

第一个测试用例中，树仅有一个顶点（非叶子节点），因此答案为 $0$。

第二个测试用例的树结构如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2071E/e210655965d56feaaf229740e97605900e199981.png)  
未掉落的顶点以粗体表示。考虑以下三种情况：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2071E/bce055b5035c73bf3a2b7bdce10fef13e9d765af.png)  
该情况出现概率为 $\left( \frac{1}{2} \right)^3$，唯一满足条件的无序对是 $(2, 3)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2071E/0c808c247da11487994ddc208f626c2d026e7d6b.png)  
该情况出现概率为 $\left( \frac{1}{2} \right)^3$，唯一满足条件的无序对是 $(2, 1)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2071E/d81763e6a6b35fb9616ff49e1a2e49523b004d8a.png)  
该情况出现概率为 $\left( \frac{1}{2} \right)^3$，唯一满足条件的无序对是 $(1, 3)$。

其他情况中不存在满足条件的无序对。因此答案为 $\frac{1 + 1 + 1}{8} = \frac{3}{8}$，模 $998\,244\,353$ 的结果为 $623\,902\,721$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1
1 2
3
1 2
1 2
1 2
1 2
2 3
3
1 3
1 5
1 3
1 2
2 3
1
998244351 998244352
6
10 17
7 13
6 11
2 10
10 19
5 13
4 3
3 6
1 4
3 5
3 2```

### 输出

```
0
623902721
244015287
0
799215919```

## 样例 #2

### 输入

```
1
10
282508078 551568452
894311255 989959022
893400641 913415297
460925436 801908985
94460427 171411253
997964895 998217862
770266391 885105593
591419316 976424827
606447024 863339056
940224886 994244553
9 5
9 6
9 8
8 7
3 6
1 5
7 4
8 10
4 2```

### 输出

```
486341067```

# 题解

## 作者：Twig_K (赞：6)

[cnblogs](https://www.cnblogs.com/wanggk/articles/-/CF2071E)

分类讨论部分参考了现有的一篇题解（~~怎么想不到呢~~），自己推了式子。

一个点成为叶子的充要条件是它自己没有被删除，且它的邻居恰好有一个没有被删除。

对下文变量的一些声明：

- $p_i$ 表示 $i$ 脱落的概率,并令 $q_i=\frac{1-p_i}{p_i}$。
- $a_u$ 表示 $u$ 的所有邻居都脱落的概率，$a_u=\prod p_v$。
- $b_u$ 表示 $u$ 恰有一个邻居未脱落，其他邻居都脱落的概率，$b_u=\sum _v a_u q_v$。
- $d_u$ 表示 $u$ 恰有一个邻居未脱落，其他邻居都脱落，且 $u$ 本身未脱落的概率，$d_u=(1-p_u)b_u$。
- $s_u$ 表示固定根节点时， $u$ 及其直属儿子的 $d$ 值之和，$s_u=d_u + \sum_{v \in son(u)} d_v$。

将点对分类，分别计算贡献：

### 对于 $dis(u,v)=1$：

此时两点互为邻居，枚举树上每一条边，贡献为 $a_u a_v q_u q_v$。这样，第一类贡献就为每条树边的贡献之和。复杂度 $O(n)$。

### 对于 $dis(u,v)=2$：

此时 $u$ 和 $v$ 有一个公共邻居 $z$，枚举 $z$，对每个 $z$ 统计它邻居两两贡献。

下式前半部分对应 $z$ 未脱落的情况，此时 $u,v$ 的其他邻居必须全部脱落，且 $u,v$ 本身不脱落；后半部分对应 $z$ 脱落的情况，$u$ 和 $v$ 都恰好剩下一个未脱落的邻居，且 $u,v$ 本身不脱落。对于某个 $z$ 的贡献：

$$f(z)=(1-p_z)\sum_{u,v} (1-p_u) \frac{a_u}{p_z} \times (1-p_v) \frac{a_v}{p_z}+ p_z\sum_{u,v} (1-p_u)\frac{b_u-a_uq_z}{p_z} (1-p_v) \frac{b_v-a_vq_z}{p_z}$$

这样子复杂度是 $O(deg_z^2)$ 的，但是由于 $2 \times \sum_{i<j} x_ix_j = (\sum x_i)^2-\sum x_i^2$，就可以非常容易地优化为 $O(deg_z)$。我另外开了一个函数算这种形式的式子。

最后把所有 $f(z)$ 累加，就得到了第二类贡献。复杂度 $O(n)$。

### 对于 $dis(u,v)>2$：

计算第三类贡献：

$$ans=\sum_{dis(u,v)>2} d_ud_v$$

这样不太好处理，转化为对每个点求贡献，并转化为总贡献减去不合法（距离太小）的贡献，设 $sum=\sum_{i=1}^{n} d_i$。

$$\begin{equation*}
  \begin{aligned}
    ans&=\frac{1}{2}\sum_{u=1}^n \sum_{dis(u,v)>2} d_u d_v  \\
     &=\frac{1}{2} \sum_{u=1}^n d_u (sum- \sum_{dis(u,v) \leq 2} d_v)
  \end{aligned}
\end{equation*}$$

考虑如何 $O(deg_u)$ 获取里面的和式：

$$\sum_{dis(u,v) \leq 2} b_v=b_{fa_{fa_u}} + s_{fa_u}+\sum_{v\in son(u)} s_v$$

第一项即 $u$ 父亲的父亲，第二项包括 $u$ 的父亲以及 $u$ 的父亲的儿子们（包括 $u$），第三项为 $u$ 的儿子与孙子（即儿子的儿子）。

复杂度 $O(n)$。

上面的式子是写完代码之后重新推的，虽然检查过但是没准还是有错，欢迎在评论区捉虫。

代码见[提交记录](https://codeforces.com/problemset/submission/2071/309747243)，变量名意义和上面式子一致。

---

## 作者：未来姚班zyl (赞：3)

这种题第一步都是不着急，先看一个点什么时候会满足条件。

考虑点 $x$ 什么时候会是个叶子。显然当且仅当 $x$ 被保留，且与 $x$ 相邻的点中恰好保留一个时 $x$ 是个叶子。

然后我们发现，如果一个点对 $(x,y)$ 的距离 $d(x,y)\ge 4$（这里距离指路径上的点数），那么它们成为叶子的事件互相独立，可以直接相乘。

否则，$d(x,y)=2$ 或 $3$，我们分别处理即可。

- $d(x,y)=2$

只需 $x,y$ 均保留，且它们的其他邻居均被删除。

- $d(x,y)=3$

假设它们夹着的点为 $z$，则有两种可能：一种是保留 $z$，$x$ 和 $y$ 的其余邻居均被删除；另一种是删除 $z$，$x$ 和 $y$ 的其余邻居中恰好保留一个。

利用前缀和的思想即可计算点对的贡献，推式子都很容易。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=1e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,h[N],to[N<<1],nxt[N<<1],cnt,ans,p[N],kp[N];
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int G[N],F[N];
inline void Main(){
	n=read();
	repn(i){
		int x=read(),y=read();
		p[i]=mul(x,INV(y)),kp[i]=Red(1,p[i]);
	}
	rep(i,2,n){
		int x=read(),y=read();
		add_(x,y),add_(y,x);
	}
	ans=0;
	repn(x){
		G[x]=0,F[x]=1;
		e(x)add(G[x],mul(kp[y],INV(p[y]))),Mul(F[x],p[y]);
		Mul(G[x],F[x]),Mul(G[x],kp[x]);
	}
	repn(x){
		int S1=0,K1=mul(kp[x],INV(mul(p[x],p[x]))),K2=p[x],S2=0,S3=0;
		e(x){
			if(x<y)add(ans,mul(mul(F[x],INV(p[y])),mul(mul(F[y],INV(p[x])),mul(kp[x],kp[y]))));
			int W1=mul(F[y],kp[y]),W2=mul(Red(G[y],mul(mul(kp[y],F[y]),mul(kp[x],INV(p[x])))),INV(p[x]));
			add(ans,mul(S1,mul(K1,W1))),add(ans,mul(S2,mul(K2,W2)));
			add(S1,W1),add(S2,W2);
			if(x<y)red(ans,mul(G[x],G[y]));
			red(ans,mul(G[y],S3)),add(S3,G[y]);
		}
		
	}
	int S=0;
	repn(x)add(ans,mul(G[x],S)),add(S,G[x]);
	cout <<ans<<"\n";
	repn(i)h[i]=0;cnt=0;
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}

```

---

## 作者：__Potata__ (赞：2)

## [_CF2071E_](https://www.luogu.com.cn/problem/CF2071E) LeaFall

### 前言

> 这篇题解可能写得并不好，但你认真看完后一定能学会这道题。

**_By potata111_**


---


### 题目大意

有一棵 $n$ 个结点的无环连通图（**树**），结点 $i$ 有 $P_i$ 的概率**_掉落_**。  
求最终形成的无环图（**森林**）中相异结点构成叶子节点的**无序对**数量的**_期望值_**。

**_掉落_**：当树上的某一结点**掉落**时，与其所有相连的边将会被抹除。

_**期望值**_：众所周知，
$$
\forall s \in \Bbb{Q},\ \exists\ p,q,\ s = \dfrac{p}{q}.
$$
其中 $p,q$ 互质且唯一。构成叶子节点的**无序对**数量的**概率** $P \in \Bbb{Q}$，故关于 $P = \dfrac{p}{q}$ 的二元组 $(p,q)$ 存在且惟一。

**期望值**便是：使得同余方程 $qx \equiv p \pmod{M}$ 成立且 $x \in [0,M)$ 的解。  
（由题设 $M = 998244353$）


---


### 输入数据
给定 $n$。

接下来 $n$ 行，每行两个整数 $p, q$。表示各个结点的掉落概率：$P(fall_i)=\dfrac{p}{q}$。

随后 $n - 1$ 行，每行两个整数 $u, v$。  
表示在最初的树上，结点 $u$ 与结点 $v$ 间由一条边联通。

### 输出数据

期望值 $x$。


---


   

### 整体思想

观察题意，发现本题实质上是求：各个 $(u,v)$ 构成一对（无序）叶子的概率。

理性思考下，$L$ 若最终成为了叶子节点，则 $L$ 的所有邻居中，**有且仅有 $1$ 个没有掉落**（显然地，$L$ **本身**亦当**未掉落**）。

**分情况**讨论不同距离的 $(u,v)$ 为期望值造成的贡献，最终累加起来。

   

---



### 钦定变量

 _这里标注了代码内的变量名与推演公式过程中变量的对应关系。_

  $dist(i,j)$ 代表 $i,j$ 两点的**_距离_**（即最短路径的长度）。
  
  $neibor_i$ 是 $i$ 的所有**邻居节点**编号构成的集合。
  
  $son_i$ 是 $i$ 的所有**孩子**编号构成的集合。

  $fath_i$ 是 $i$ 的父亲结点编号。
  
  $p_i = $ 结点 $i$ 的**掉落概率**，同时记 $p'_i = \dfrac {1 - p_i}{p_i}.$  
  $p_i$ 由题目给定，$p'_i$ 为定义，直接求值。
  
  $a_i = \ i$ **所有的邻居**（不包括 $i$）**掉落**的概率。
  
  $∵$ 每个结点的掉落均为独立事件，**多独立事件同时发生概率为其积**。
  
  $∴\ a_i = \displaystyle\prod_{j \in \{neibor_i\}} p_j.$
  
  $o_i = \ i$ 的邻居中，**恰有一个未掉落**的概率。
  
  先讨论未掉落邻居是哪个，并将所有情况发生的概率加和。  
  即 $o_i = \displaystyle\sum_{j \in \{neibor_i\}} a_ip'_j.$
  
  $l_i = i$ 成为**叶子结点的概率**。
  
  如上，即 $i$ 恰有一邻居未掉落 $(o_i)$ 且自己未掉落 $(1 - p_i)$ 的概率。
  这两者互为独立事件，故 $l_i = (1 - p_i)o_i.$
  
  $s_i = i$ 与其儿子**有一成为叶子**的概率。
  
  易得 $s_i = l_i + \displaystyle\sum_{j \in \{son_i\}} l_j.$

### 分类讨论

对一组点 $(i,j)$：

  $dist(i,j) = 1$，

  **——** 推论：则 $i,j$ 互为邻居结点，共造成了 $a_ia_jq_iq_j$ 的贡献。
  
  **——** 实现：$i,j$ 必然由一条边联通。故可以**枚举图上的所有边**求这一类贡献。

  $dist(i,j) = 2$，

  **——** 推论：联通 $i,j$ 的唯一最短路径（毕竟树上是没有环的）上必有一个 $i,j$ 的公共邻居 $k$。  
  **注意：我们这里以 $k$ 为出发点，来考虑不同的 $i,j$**。

  进一步考虑 $k$ 的掉落情况：

  $k$ 掉了，则概率应为：
  $$
  S_1 = p_k \sum_{i,j \in \{neibor_k\}} (1 - p_i)(\dfrac {o_i - a_ip'_k}{p_k})(1 - p_j)(\dfrac{o_j - a_jp'_k}{1 - p_k}).
  $$

  其中 $(1 - p_i)(\dfrac {o_i -  a_ip'_k}{p_k})$ 是 $i$ 未掉落且可以成为叶子结点的概率。对 $j$ 亦然。

  $k$ 没掉，则概率应为：
$$
  S_2 = (1-p_k) \sum_{i,j \in \{neibor_k\}}(1 - p_i)(\dfrac {a_i}{p_k})(1 - p_j)(\dfrac {a_j}{p_k}).
$$ 

  其中 $(1-p_i)(\dfrac {a_i}{p_k})$ 是 $i$ 未掉落且可以成为叶子结点的概率。对 $j$ 亦然。

  那么第二类贡献对**单个**的 $k$ 值就为 $S_1 + S_2.$（代码中做了一些算术优化，但思路如此。）

  **——** 实现：**枚举 $i,j$ 的公共邻居 $k$**，依次考虑关于各个 $k$ 的点对 $i,j$ 计算贡献。

  $dist(i,j) > 2$，

  **——** 推论：简单地， $S = \sum_{dist(i,j) > 2} l_il_j$。
  但显然这样是 $O(n^2)$ 的。

  故考虑将关于某个点 $i$ 与任一点 $j$ 构成点对 $(i,j)$ 造成的总贡献 $P$ 减去 $dist(i,j) \leqslant 2$ 的部分 $N$。有 $S = P - N.$

  **--**  **那我问你**，为什么不直接算总贡献呢?  
  **--**  直接算总贡献是 $O(n^2)$ 的且~~非常~~难处理，而这样的分情况讨论可以**大大优化效率**。  
  **--**  ~~彳亍~~。

  回到正题。

   显然贡献为 $\dfrac {\sum_{dist(i,j) > 2}l_il_j} {2}$，除以 $2$ 是为了求**无序**对的期望值。

  $$ \begin{aligned}
     S_i &= \dfrac {\sum_{dist(i,j) > 2}l_il_j} {2} \\
       &= \dfrac{1}{2} \ \ l_i \ (\displaystyle\sum_{i=1}^n {l_i} -  \sum_{\mathclap{dist(i,j) \leqslant 2}} l_j)
  \end{aligned} $$

  **——** 优化：

上式中 $\displaystyle\sum_{i=1}^n {l_i}$ 是一个显然的**常数**，故可以作预处理。  
（记其值为 $sum$），从而**省去**一个 $O(n)$ 的时间系数。

对后半部分，考虑**更优的算术方法**：

  $$
  \sum_{\mathclap{dist(i,j) \leqslant 2}} l_j = (\sum_{j \in son_i} s_j\ ) + \ s_{fath_i} + b_{fath_{fath_i}}.
  $$

  上式从左至右分别表示：

  $i$ 向下放射 $2$ 层（即 $i$ 的儿子与孙子）；

  $i$ 向上放射一层与 $i$ 所在层（即 $i$ 的父亲与兄弟）；

  $i$ 向上放射第二层（即 $i$ 的祖父（爷爷）结点）。

  **——** 推论：随即

  $$
    S_i = \dfrac{1}{2} \ \ l_i(sum   (\sum_{j \in son_i} s_j\ + \ s_{fath_i} + b_{fath_{fath_i}})); \\

  ans =  \sum_{i \in [1,n]} S_i.
  $$
   

---



### 华丽收工

那么本题的答案就为上述三种点对贡献之和。


```cpp
#include<iostream>
#include<vector>
 
#define ll long long
#define potata int(1e5 + 10)
#define mod 998244353
 
using namespace std;
 
// 一个点成为叶子的充要条件是： 它自己没有被删除 且 它的邻居恰有一个没有被删除.
// 叶子的掉落互为独立事件 P(AB) = P(A) * P(B).
 
int n;
vector<int> nxt[potata]; // nxt[i] = 与结点 i 直接连通的结点集合, 即 i 的邻居（其父节点及其孩子）
int fath[potata]; // i 的父节点
 
ll p[potata], q[potata];
ll all[potata], bef[potata];
ll one[potata], Sum[potata];
vector<ll> tmp;
 
ll div(ll x)
{
    ll res = 1;
    x %= mod;
 
    for (ll tmp = mod - 2; tmp != 0; x = x * x % mod, tmp /= 2) // 这里 x * x % mod 我竟在首次写成了 x** (?)
        if (tmp % 2 == 1)
            res = (res * x) % mod;
 
    return res;
} // 求逆元
 
void Input()
{
    cin >> n;
 
    for (int i = 1; i <= n; i++)
    {
        ll u, v; // 为了传参还是要开 ll 
        cin >> u >> v;
        p[i] = u * div(v) % mod;
        q[i] = div(p[i]) * (-(p[i] - mod - 1)) % mod;
    }
 
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        nxt[u].push_back(v);
        nxt[v].push_back(u);
    }
} // 输入
 
void dfs(int u, int father)
{
    fath[u] = father;
    Sum[u] = one[u];
    Sum[father] = (Sum[father] + one[u]) % mod;
 
    int len = nxt[u].size();
    for (int i = 0; i < len; i++)
        if (nxt[u][i] != father)
            dfs(nxt[u][i], u); // 下搜儿子
} // 通过深搜初始化
 
void Inital()
{
    for (int i = 1; i <= n; i++)
    {
        bef[i] = 0;
        all[i] = 1;
 
        int len = nxt[i].size();
        for (int j = 0; j < len; j++)
            all[i] = all[i] * p[nxt[i][j]] % mod;
        for (int j = 0; j < len; j++)
            bef[i] = (bef[i] + (all[i] * q[nxt[i][j]] % mod)) % mod;
 
        one[i] = bef[i] * (mod + 1 - p[i]) % mod;
    }
 
    dfs(1, 0);
} // 初始化
 
ll cal()
{
    ll S1 = 0;
    ll S2 = 0;
 
    int len = tmp.size();
    for (int i = 0; i < len; i++)
        S1 = (S1 + tmp[i]) % mod,
        S2 = (S2 + ((tmp[i] % mod) * (tmp[i] % mod))) % mod;
 
    return ((S1 * S1 % mod - S2 + mod) % mod * ((mod + 1) / 2) % mod);
} // 计算
 
ll solve1()
{
    ll Sum = 0;
 
    for (int i = 1; i <= n; i++)
        for (int j : nxt[i]) // 迭代器真的好用
            if (i < j)
                Sum = (Sum + (all[i] % mod * all[j] % mod * q[i] % mod * q[j] % mod)) % mod;
 
    return Sum;
} // 两点互为邻居（两点距离为 1） 枚举树上所有的边 O(n)
 
ll solve2()
{
    ll Sum = 0;
 
    for (int i = 1; i <= n; i++)
    {
        tmp.clear();
        int len = nxt[i].size();
        for (int j = 0; j < len; j++)
            tmp.push_back(all[nxt[i][j]] * (mod + 1 - p[nxt[i][j]]) % mod * div(p[i]) % mod);
 
        Sum = (Sum + cal() * (mod + 1 - p[i]) % mod) % mod;
 
        tmp.clear();
        len = nxt[i].size();
        for (int j = 0; j < len; j++)
            tmp.push_back(((bef[nxt[i][j]] - all[nxt[i][j]] * q[i] % mod + mod) % mod) * (mod + 1 - p[nxt[i][j]]) % mod);
 
        Sum = (Sum + cal() * div(p[i]) % mod) % mod;
    }
 
    return Sum;
} // 两点有一公共邻居 分别考虑该邻居掉落与否（两点距离为 2）; 这里写完真的感觉大脑焕然一新
 
ll solve3()
{
    ll res = 0;
    ll summ = 0;
 
    for (int i = 1; i <= n; i++)
        summ = (summ + one[i]) % mod;
 
    for (int i = 1; i <= n; i++)
    {
        ll tmp = (Sum[fath[i]] + one[fath[fath[i]]]) % mod;
        // 考虑儿子和孙子
 
        int len = nxt[i].size();
        for (int j = 0; j < len; j++)
            if (nxt[i][j] != fath[i])
                tmp = (tmp + Sum[nxt[i][j]]) % mod;
        // 继续找孙子
 
        res = (res + ((summ - tmp + mod) % mod) * one[i] % mod) % mod;
    }
 
    return (res * ((mod + 1) / 2) % mod);
} // 两点距离大于 2; 推公式更是高手
 
void Answer()
{
    ll ans = ((solve1() % mod) + (solve2() % mod) + (solve3() % mod)) % mod;
    cout /* << "Answer is here: "*/ << ans << '\n';
} // 输出
 
void Clear()
{
    for (int i = 0; i <= n; i++)
        nxt[i].clear(),
        Sum[i] = 0;
} // 清零
 
int main()
{
    int q; // 因为会和概率 q 重名 所以只能设局部变量了
    cin >> q;
 
    while (q--)
        Input(),
        Inital(),
        Answer(),
        Clear();
    // 好看
 
    return 0;
} // 大脑一直在推不完的概率期望数学公式和濒临溢出的代码间反复横跳
```

---

## 作者：tyr_04 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2071E)

调了两天，思维含量不算低，代码细节较多（也有可能是想复杂了）

前注：光看下面这一坨描述可能有点抽象，建议阅读代码助于理解。

### 题意

给定一棵 $n$ 个节点的树，给定每个点删除的概率 $\frac{p_i}{q_i}$（不同点删除概率可能不同，保存该点的概率为 $\frac{q_i - p_i}{q_i}$，$0 < p_i < q_i$），删除 $x$ 意为删除所有与 $x$ 有关的边，不影响其它点，设无序对 $(o1,o2)$，$o1,o2$ 都为叶子节点（叶子节点指只有一条边与其它点相连的点），求判断 $n$ 个点是否删除后，无序对 $(o1,o2)$ 的期望数量（$(o1,o2)$ 和 $(o2,o1)$ 视为相同，对无序对总数的贡献只有 $1$），实在不懂可以看看样例解释。

### 思路

注意到这是伪期望，考虑枚举两个点 $(x,y)$ 计算它们出现的概率（$x \ne y$，$(x,y)$ 对总数贡献为 $1$，最终答案直接加上 $(x,y)$ 出现的概率即可），$x,y$ 能否成为叶子节点只与自己和它们的相邻点的状态有关，计算概率时要对 $x,y$ 的位置进行分类讨论：

1. 如果两点相邻：保留 $x,y$，与 $x,y$ 相连的点全部删除

2. 如果两点间隔一个点：保留 $x,y$ 及中间点；或保留 $x,y$，删除中间点，$x,y$ 分别选其它两个相邻点保留

3. 如果两点间隔两点即以上：保留 $x,y$，$x,y$ 的相邻点分别保留一个，其它相邻点删除

然而暴力枚举 $x,y$ 时间复杂度是 $O(n^2)$ 的（加上判断两点的距离会更大），考虑优化，预处理出 $u_x$ 为保留 $x$ 点且删除所有与 $x$ 相连的点的概率（即 $u_x = \frac{p_x}{q_x} \times \frac{p_{y_1}}{q_{y_1}} \times \frac{p_{y_2}}{q_{y_2}} \ldots$，其中 $y_i$ 表示与 $x$ 相邻的点）；$sum_x$ 为保留 $x$ 和任意一个 $x$ 的相邻点，其它 $x$ 的相邻点删除的概率（枚举与 $x$ 相连的点 $y$，$u_x$ 除以 $y$ 删除的概率再乘 $y$ 保留的概率，也就是乘 $p_x$ 的逆元再乘 $(q_x - p_x)$，依次加入 $sum_x$ 即可），预处理复杂度 $O((n + m)\log V)$，设 $h = \sum_{i = 1}^{n} sum_i$。

对于第一种情况，枚举每条边的左右端点 $x,y$，由于 $u_x$ 钦定删了 $y$，$u_y$ 钦定删了 $x$，所以贡献为 $u_x \times u_y$ 再除以 $x,y$ 被删的概率，此处复杂度为 $O(m \log V)$，可以在处理第二及第三种情况的过程中计算。

接下来枚举 $x$，为统计第三种情况，将 $h$ 减掉 $x$ 相邻点的 $sum$ 和，设减去后值为 $now$，最终答案加 $now \times sum_x$，**注意此时未区分第三与第二种情况，并且多算部分全部有误**（对于中间只间隔一个点的 $(x,y)$，如果 $x,y$ 都选中间点，保留中间点算了两次；如果 $x,y$ 都不选中间点，删除中间点算了两次；如果 $x,y$ 一个选中间点一个不选，中间点状态矛盾），因此要全部减掉。

刚刚我们把 $x$ 看做 $(x,y)$ 中的一点，接下来看做第二种情况中被夹在中间的点。

设 $gs$ 为 $x$ 的相邻点 $y$ 的 $sum_y$ 和（即所有相邻点 $y$ 及 $y$ 的某一个相邻点保留，$y$ 的其它相邻点删除的概率，$gs$ 用于减去第二种情况在第三种情况里多算的错误部分）。$ts$ 为 $x$ 的相邻点 $y$ 的 $u_y$ 除以删掉 $x$ 的概率（即所有 $x$ 的相邻点 $y$ 删掉其它相邻点但不管 $x$ 是否删除的概率，不管 $x$ 是方便后来计算两点保留中间点的情况的概率）。$tp$ 为 $x$ 的相邻点 $y$ 的 $sum_y$ 减去 $y$ 保留 $x$ 的概率（$y$ 保留 $x$ 的概率：$\frac{u_y \times (q_x - p_x)}{p_x}$）**后**除以删除 $x$ 的概率（即所有相邻点 $y$ 不保留 $x$，且 $y$ 剩余的情况不管 $x$ 是否删除的概率，这里不管 $x$ 是方便后来计算两点删除中间点保留其它相邻点的情况的概率）。计算第三种情况的方法与求出 $gs,ts,tp$ 的总复杂度为 $O((n + m) \log V)$。

首先答案要减去每个与 $x$ 的相邻点 $o$ 的 $sum_o \times (gs - sum_o)$ 的值，把所有 $x$ 的相邻点两两组合对答案的多余错误贡献减掉；接着计算 $x$ 的每个相邻点 $o$ 不选择 $x$ 的贡献：$(sum_{o} - \frac{u_{o}}{p_x} \times (q_x - p_x)) \times (tp - (sum_o - \frac{u_o}{p_x} \times (q_x - p_x))) \times (\frac{q_x}{p_x})$（前面部分是 $o$ 只保留任一相邻点的概率减去保留 $x$ 的概率；中间部分是 $tp$ 减掉 $o$ 的贡献，防止出现多算 $(o,o)$；后面部分是钦定 $x$ 不保留。每个部分以最外层括号区分）；最后一种情况是 $x$ 的相邻点 $o$ 选择 $x$ 的情况：$(\frac{u_o}{p_x} \times (q_x - p_x)) \times (ts - \frac{u_o}{p_x} \times q_x)$（前半部分计算 $o$ 点只保留 $x$ 删除其它相邻点的概率；后半部分是 $ts$ 减掉 $o$ 的贡献，也防止出现多算 $(o,o)$。每个部分以最外层括号区分）。减去多余错误的情况和计算第二种情况的贡献的复杂度也为 $O((n + m) \log V)$。

代码里所有的除法都用逆元处理，注意减法里要加上模数防止变为负数，总复杂度 $O((n + m)\log V)$ 其中 $V$ 是值域。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t,n,p[100005],q[100005],sum[100005],u[100005],h,ans;
vector<int> v[100005];
int ksm(int x,int y)
{
	int now=1;
	while(y!=0)
	{
		if(y%2==1)
		{
			now*=x;
			now%=mod;
		}
		x*=x;
		x%=mod;
		y/=2;
	}
	return now;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0;
		h=0;
		for(int i=1;i<=n;i++)
		{
			cin>>p[i]>>q[i];
			sum[i]=0;
			u[i]=0;
			v[i].clear();
		}
		for(int i=1;i<n;i++)
		{
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		for(int x=1;x<=n;x++)
		{
			u[x]=(q[x]-p[x])*ksm(q[x],mod-2)%mod;
			for(int i=0;i<v[x].size();i++)
			{
				int y=v[x][i];
				u[x]=u[x]*p[y]%mod*ksm(q[y],mod-2)%mod;//预处理 u，方法及含义见上文
			}
			sum[x]=0;
			for(int i=0;i<v[x].size();i++)
			{
				int y=v[x][i];
				sum[x]+=u[x]*ksm(p[y],mod-2)%mod*(q[y]-p[y])%mod;
				sum[x]%=mod;//预处理 sum，方法及含义见上文
			}
			h+=sum[x];
			h%=mod;
		}
		for(int x=1;x<=n;x++)
		{
			int now=h,gs=0,ts=0,tp=0;//now,gs,ts,tp 的含义见上文
			now=(now-sum[x]+mod)%mod;
			for(int i=0;i<v[x].size();i++)
			{
				int y=v[x][i];
				now=(now-sum[y]+mod)%mod;
				ans+=u[x]*u[y]%mod*q[x]%mod*ksm(p[x],mod-2)%mod*q[y]%mod*ksm(p[y],mod-2)%mod;//第一种情况
				ans%=mod;
				gs+=sum[y];
				gs%=mod;
				tp=tp+((sum[y]-(u[y]*ksm(p[x],mod-2)%mod*(q[x]-p[x])%mod)+mod)%mod)*ksm(p[x],mod-2)%mod*q[x]%mod;
				tp%=mod;
				ts+=u[y]*ksm(p[x],mod-2)%mod*q[x]%mod;
				ts%=mod;
			}
			ans+=now*sum[x]%mod;//第三种情况，但此时多算了第二种情况，且多算的部分有误（原因见上文）
			ans%=mod;
			for(int i=0;i<v[x].size();i++)
			{
				int y=v[x][i];
				ans=(ans-(sum[y]*((gs-sum[y]+mod)%mod)%mod)+mod)%mod;//减掉多算的第二种情况
				ans+=((sum[y]-(u[y]*ksm(p[x],mod-2)%mod*(q[x]-p[x])%mod)+mod)%mod)*((tp-(((sum[y]-(u[y]*ksm(p[x],mod-2)%mod*(q[x]-p[x])%mod)+mod)%mod)*ksm(p[x],mod-2)%mod*q[x]%mod)+mod)%mod)%mod;//第二种情况中两点都不选 x 的贡献
				ans%=mod;
				ans+=u[y]*ksm(p[x],mod-2)%mod*(q[x]-p[x])%mod*((ts-(u[y]*ksm(p[x],mod-2)%mod*q[x]%mod)+mod)%mod)%mod;//第二种情况中两点都选 x 的贡献
				ans%=mod;
			}
		}
		cout<<ans*ksm(2,mod-2)%mod<<'\n';//(x,y),(y,x) 都算了一遍，故除以二
	}
	return 0;
}
```

---

## 作者：Demoe (赞：1)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF2071E)

### $\text{Description}$

- 给定一棵 $n$ 个节点的树，每个节点有 $\dfrac{p_i}{q_i}$ 的概率坍塌（指切断所有邻边）。
- 求期望的无序叶子节点对数。（其中**叶子节点**指恰有一条邻边的节点）
- 答案对 $998244353$ 取模。
- 多测。

---



### $\text{Solution}$

记 $N(k)$ 为 $k$ 在树上的相邻节点集，$dis(i,j)$ 为树上 $i$ 与 $j$ 路径的边数，简记 $p_i$ 为 $i$ 号节点坍塌的概率。

首先考虑每个节点成为叶子节点的概率，由题可写出 $v_i=(1-p_i)\sum\limits_{j\in N(i)}(1-p_j)\prod\limits_{k\in N(i) \& k\neq j}p_k=(1-p_i)(\prod\limits_{k\in N(i)}p_k)(\sum\limits_{j\in N(i)}\dfrac{1-p_j}{p_j})$。

#### $\text{Warning}$

**期望点对数不可直接由期望点数求出。**

$Node=\sum p_i a_i$

$Pair=\sum p_i \dfrac{a_i^2-a_i}{2}\neq \dfrac{Node^2-Node}{2}$

因此我们只可直接考虑点对。

---

考虑到 $dis(i,j)\ge 3$ 时，两点各自为叶子节点的两事件独立，而 $dis(i,j)=1$ 和 $dis(i,j)=2$ 的情况下，由于存在邻居节点重合事件不独立，需要另外考虑。

因此做出如下分讨：

#### $dis(i,j)\ge 3$

由于独立，贡献为 $v_i\times v_j$。

#### $dis(i,j)=1$

显然 $i$ 和 $j$ 都不能坍塌，则若 $(i,j)$ 要成为叶子点对，其连边则为唯一边，也即 $i$ 和 $j$ 的其余所有邻居节点坍塌。

贡献为 $(1-p_i)(1-p_j)\prod\limits_{k\in N(i)\cup N(j)\& k\neq i,j}p_k$。

#### $dis(i,j)=2$

考虑 $i$ 与 $j$ 路径上的唯一点 $k$。

若 $k$ 不坍塌，则 $(i,j)$ 要成为叶子点对，则除 $k$ 以外的 $i$ 与 $j$ 的邻居节点全部坍塌。

此处贡献为 $(1-p_i)(1-p_j)(1-p_k)\prod\limits_{s\in N(i)\cup N(j)\& s\neq k}p_s$。

若 $k$ 坍塌，则 $(i,j)$ 要成为叶子点对，则各有一个邻居节点未坍塌。

此处贡献为 $p_k(1-p_i)(1-p_j)(\sum\limits_{s\in N(i)\& s\neq k}(1-p_s)\prod\limits_{t\in N(i)\& t\neq k,s}p_t)(\sum\limits_{s\in N(j)\& s\neq k}(1-p_s)\prod\limits_{t\in N(j)\& t\neq k,s}p_t)$。

两者加和即可。

---

考虑如何快速计算贡献。

令 $A_i=\prod\limits_{j\in N(i)}p_j$，$B_i=\sum\limits_{j\in N(i)}\dfrac{1-p_j}{p_j}$。

两者都可以在输入的时候顺带线性处理。

- $dis(i,j)\ge 3$

  $v_i=(1-p_i)A_iB_i$。

  可以先利用前缀和线性计算 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^nv_i\times v_j$，然后再在计算 $dis(i,j)=1$ 和 $dis(i,j)=2$ 的时候将多计算的部分剔除。

- $dis(i,j)=1$

  枚举边即可线性计算 $(1-p_i)(1-p_j)\prod\limits_{k\in N(i)\cup N(j)\& k\neq i,j}p_k=\dfrac{(1-p_i)(1-p_j)}{p_ip_j}A_iA_j$。

- $dis(i,j)=2$

  对每个 $k$，

  分别计算 $(1-p_i)(1-p_j)(1-p_k)\prod\limits_{s\in N(i)\cup N(j)\& s\neq k}p_s$ 和 $p_k(1-p_i)(1-p_j)(\sum\limits_{s\in N(i)\& s\neq k}(1-p_s)\prod\limits_{t\in N(i)\& t\neq k,s}p_t)(\sum\limits_{s\in N(j)\& s\neq k}(1-p_s)\prod\limits_{t\in N(j)\& t\neq k,s}p_t)$，

  可分别简记为 $\dfrac{1-p_k}{p_k^2}(1-p_i)A_i(1-p_j)A_j$ 和 $\dfrac{1}{p_k}(1-p_i)A_i(B_i-\dfrac{1-p_k}{p_k})(1-p_j)A_j(B_j-\dfrac{1-p_k}{p_k})$。

  由于 $i$ 与 $j$ 在贡献中对称，易发现可以类似 $dis(i,j)\ge 3$ 的方式计算前缀和线性得。

---

#### $\text{Time Complexity}$

计算逆元时间复杂度为 $O(\log M)$，每部分遍历都是线性的，因此总时间复杂度为 $O(n\log M)$。

---

#### $\text{Space Complexity}$

记录树以及每个节点的不同权值即可，$O(n)$。

---

### $\text{Code}$

```cpp
const int N=1e5+5,mod=998244353;
int t,n,p[N],v[N],A[N],B[N];
vector<int> e[N];

inline int pw(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=1ll*sum*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return sum;
}

inline int inv(int x){return pw(x,mod-2);}

inline void solve(){
	rd(n);int sum1=0,sum21=0,sum22=0,sum3=0;
	for(re i=1;i<=n;++i){
		int q;rd(p[i]);rd(q);p[i]=1ll*p[i]*inv(q)%mod;
		e[i].clear();A[i]=1;B[i]=0;
	}
	for(re i=1;i<n;++i){
		int u,v;rd(u);rd(v);
		e[u].pb(v);e[v].pb(u);
		A[u]=1ll*A[u]*p[v]%mod;A[v]=1ll*A[v]*p[u]%mod;
		B[u]=(1ll*(1-p[v]+mod)%mod*inv(p[v])%mod+B[u])%mod;B[v]=(1ll*(1-p[u]+mod)%mod*inv(p[u])%mod+B[v])%mod;
	}
	for(re i=1;i<=n;++i) v[i]=1ll*(1-p[i]+mod)%mod*A[i]%mod*B[i]%mod;
	int tmp=0;
	for(re i=1;i<=n;++i) sum3=(sum3+1ll*tmp*v[i]%mod)%mod,tmp=(tmp+v[i])%mod;
	for(re i=1;i<=n;++i)
		for(re j=0;j<e[i].size();++j)
			if(i<e[i][j]){
				sum1=(sum1+1ll*(1-p[i]+mod)%mod*(1-p[e[i][j]]+mod)%mod*inv(p[i])%mod*inv(p[e[i][j]])%mod*A[i]%mod*A[e[i][j]]%mod)%mod;
				sum3=(sum3-1ll*v[i]*v[e[i][j]]%mod+mod)%mod;
			}
	for(re i=1;i<=n;++i){
		int tmp1=0,tmp2=0,tmp3=0,p1=1ll*(1-p[i]+mod)%mod*inv(p[i])%mod*inv(p[i])%mod,p2=inv(p[i]),p3=1ll*(1-p[i]+mod)%mod*inv(p[i])%mod;
		for(re j=0;j<e[i].size();++j){
			sum21=(sum21+1ll*tmp1*(1-p[e[i][j]]+mod)%mod*A[e[i][j]]%mod*p1%mod)%mod;tmp1=(tmp1+1ll*(1-p[e[i][j]]+mod)%mod*A[e[i][j]]%mod)%mod;
			sum22=(sum22+1ll*tmp2*(1-p[e[i][j]]+mod)%mod*A[e[i][j]]%mod*(B[e[i][j]]-p3+mod)%mod*p2%mod)%mod;tmp2=(tmp2+1ll*(1-p[e[i][j]]+mod)%mod*A[e[i][j]]%mod*(B[e[i][j]]-p3+mod)%mod)%mod;
			sum3=(sum3-1ll*tmp3*v[e[i][j]]%mod+mod)%mod;tmp3=(tmp3+v[e[i][j]])%mod;
		}
	}
	wr((sum1+(sum21+(sum22+sum3)%mod)%mod)%mod);puts("");
}

// ---------- sum ---------- //
```

---

