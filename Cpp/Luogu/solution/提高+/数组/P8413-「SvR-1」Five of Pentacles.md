# 「SvR-1」Five of Pentacles

## 题目背景

UPD on 2023.2.5 by 出题人： 原题强制在线方式有问题，会使得一些依赖强制在线的方式通过，这并不是正解~~但是不想改了~~。

## 题目描述

**请仔细阅读数据范围和时间限制。**

有一个长度为 $m$ 的数轴，一开始，处于 $1$ 时刻的**开始**，小 Z 处于 $1$ 号点，此时数轴上每个点都有一个障碍。

每个时刻，若小 Z 处于 $i$ 号点，小 Z 可以指定一个 $d \geq 0$，然后移动到 $i + d$ 号点，并且会越过 $[i, i + d]$ 的每一个障碍。

当然，一切都是在变化的，一共会有 $k$ 次变化，第 $i$ 次会发生如下变化：

- $t_i$ 时刻内 $x_i$ 号点上的障碍将会消失。
- **请注意，此变化仅作用于 $t_i$ 时刻**

保证变化是**随时间倒序发生的**，也就是说 $t_i$ **单调不升**。

现在，对于每个 $1\le i\le k$，你都需要输出**在前 $i$ 个变化发生的条件下**、在保证第 $n$ 个时刻结束时小 Z 恰好处于 $m$ 号点的基础上，小 Z 越过的最小障碍数。

## 说明/提示

#### 样例解释

样例解密后：

```plain
2 3 2
2 1
2 2
```

- 第一次变化后：小 Z 第一秒选择 $d = 0$，跨过一个障碍。第二秒选择 $d = 2$，原本跨过了 $3$ 个障碍，但是第 $2$ 秒第一个点没有障碍，所以只跨过了 $2$ 个障碍。一共 $1 + 2 = 3$ 个障碍。
- 第二次变化后：小 Z 第一秒选择 $d = 0$，跨过一个障碍。第二秒只有第三个位置有障碍，选择 $d = 2$，所以只跨过了一个障碍。一共 $1 + 1 = 2$ 个障碍。

#### 数据规模与约定

**本题自动开启捆绑测试和 O2 优化。**

$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c}\hline\hline
\textbf{Subtask} & \bm{n,m,k\le} & \textbf{分值} \\\hline
\textsf{1} & 100 & 15 \\\hline
\textsf{2} & 2\times10^3 & 20 \\\hline
\textsf{3} & 5\times10^4 & 20 \\\hline
\textsf{4} & 10^6 & 20 \\\hline
\textsf{5} & \text{无特殊限制} & 25 \\\hline\hline
\end{array}
$$

对于 $100\%$ 的数据（解密后），$1 \leq n, m, k \leq 2 \times 10^6$，$1 \leq t_i \leq n$，$0 \leq p \leq 15$，$t_i$ **单调不升**，若 $t_i$ 相同，按 $x_i$ **升序**，且 $\forall 1 \leq i < j \leq k$，$(t_i, x_i)$ 和 $(t_j, x_j)$ 不同。

本题提供读入优化方式。

使用 `read(x);` 读入一个任意的整型 `x` 等价于 `scanf("%d", &x);`其中可以将 `%d` 自动识别为对应类型。

```cpp
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
	r=w?-r:r;
}
```


## 样例 #1

### 输入

```
2 3 2
2 0
2 3```

### 输出

```
3
2```

# 题解

## 作者：思考人生中 (赞：6)

UPD @ 2022-10-05 :修改了一些误导性的内容

>赛时的时候在期末复习，就没做。
>
>期末考完来看的时候我的内心 OS 如下：
>
>这不是求个最大不下降子序列就好了吗？这么简单也能评蓝？
>
>然后看到 $n,m,k\le 2\times10^6$ 的时候我凝固了。
>
>~~好毒瘤一题~~

以上是我当时不知道 BIT 常数有多小的时候的**言论，大可以忽略。

当然我这个利用在线格式的奇怪做法还是挺有意思的（？

（最终复杂度是与正解差不多的）

---

### 正文

我们来看一下题目啊([传送门](https://www.luogu.com.cn/problem/P8413))

题目要求最小的越过障碍数，那么我们很容能够想到两点：

+ 如果没有障碍消失，那么最终越过障碍数就是 $n+m-1$。
+ 我们每走过一个消失的障碍，最终越过的障碍数就减少 $1$。

结合这两点我们希望越过尽可能多的消失的障碍。

而越过的障碍，我们用题目中的 $(t_i,x_i)$ 来表示我们在时间 $t_i$ 越过了障碍 $x_i$。

不难发现根据 $d\ge 0$ 有 $\forall t_i<t_j,x_i\le x_j$，于是题目顺利地被转化为求一个最大不下降子序列的。

但是我们就是要走不寻常的路。我们看在线输入的格式。

> 接下来 $k$ 行，其中第 $i$ 行有两个数字 $t_i, p$。其中 $p$ 用于生成 $x_i$，即： $x_i = \min(x_{i - 1} + p \oplus (lastans \bmod 15) + 1, m)$ 其中 $lastans$ 表示上次变化的答案。

> **特别地，第一次变化之前 $lastans = 0$， $x_0 = 0$，且当 $x_{i - 1} = m$ 时，将 $x_{i - 1}$ 视作 $0$（注意这不会真的改变 $x_{i - 1}$ 的值）。**

同时我们有 $p\le 15$, $(lastans \bmod 15) \le15$， 从而 $p \oplus (lastans \bmod 15) + 1 \le 16$。

那么我们会发现我们得到的 $\left\{ x_i\right\}$ 序列是若干个长度不小于 $\dfrac{m}{\max\{p\}}$ 的严格单调增序列拼接而成的，且每一个的结尾都是 $m$。

利用这个“严格单调增”的性质，我们可以用数组 $a[i]$ 来记录以 $i$ 为开头的最大不下降子序列的后缀最大值（因为 $t_i$ 是按照单调减的顺序给出的）从而只需要在处理完其中某一严格单调增序列 $x_i,x_{i+1}\cdots,x_j$ 时再更新每一个 $a[i]$ 的值，在处理该序列过程中只需要依次更新 $a[x_i],a[x_{i+1}]\cdots,a[x_j]$ 的值，因为前面的值改变并不影响后面的值。

记**最大跨过的消失的障碍数**为 $ans$。

按照 $t_i$ 相同为一组来处理。设 $t$ 时的 $x$ 值依次为 $x'_1,x'_2\cdots,x'_{tot}$。

那么我们发现当 $x'_i$ 的变化出现的时候，包含 $x'_i$ 的最大不下降子序列为 $a[x'_i]$ 所代表的最大不下降序列前接上 $x'_1,x'_2\cdots,x'_{i}$ ，用这个去更新 $ans$ 即可。

处理完之后我们再用下面的 DP 柿子**倒序更新** $a[x'_1],a[x'_2]\cdots,a[x'_{tot}]$:

$$a[x'_i]=\max\{a[x'_{i}],a[x'_{i+1}]\}+1$$

然后就做完了。主要的复杂度在更新一整个 $a[i]$ 数组，总复杂度为 $O(m\cdot \frac{m}{\frac{m}{\max\{p\}}})=O(m\cdot \max\{p\})$

注意一下在线格式的细节就好了，怕 TLE 就用上快读。

### 代码

```cpp

#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 2000000
using namespace std;

//快读
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
	r=w?-r:r;
}

int a[MAXN+5],tot,stk[MAXN+5],x[MAXN+5],now;
//stk是t时间下的p序列，x是解密以后的x序列

int main() {
    ios::sync_with_stdio(0);
    int n,m,k,t,ans=0,p,lst=0,lstans=0;
    read(n);read(m);read(k);
    read(t);read(p);
    stk[++tot]=p;
    now=t;
    for (int i=1;i<=k;++i) {
        if (i==k) t=p=0;
        else read(t),read(p);
        if (t==now) {
            stk[++tot]=p;
        } else {
            //依次更新并输出答案
            for (int j=1;j<=tot;++j) {
                lst=min(lst+(stk[j]^(lstans%15))+1,m);
                x[j]=lst;
                ans=max(ans,a[lst]+j);
                cout<<n+m-ans-1<<"\n";
                lstans=n+m-ans-1;
            }
            //更新a数组
            ++a[x[tot]];
            for (int j=tot-1;j>=1;--j) a[x[j]]=max(a[x[j+1]],a[x[j]])+1;
            //在处理完后把下一个p放入stk
            stk[tot=1]=p;
            now=t;
            if (lst==m) {
                for (int j=m-1;j>=1;--j) a[j]=max(a[j+1],a[j]);
                lst=0;
            }
        }
    }
    return 0;
}

```

---

## 作者：do_while_true (赞：3)

官方题解。

# 题目描述

有一个长度为 $m$ 的数轴，一开始，处于 $1$ 时刻的**开始**，小 Z 处于 $1$ 号点，此时数轴上每个点都有一个障碍。

每个时刻，若小 Z 处于 $i$ 号点，小 Z 可以指定一个 $d \geq 0$，然后移动到 $i + d$ 号点，并且会越过 $[i, i + d]$ 的每一个障碍。

当然，一切都是在变化的，一共会有 $k$ 次变化，第 $i$ 次会发生如下变化：

- 在 $t_i$ 时刻初把 $x_i$ 号点上的障碍移走。
- **此变化仅作用于 $t_i$ 时刻。**

保证变化是**随时间倒序发生的**，也就是说 $t_i$ **单调不升**。

现在，对于每个 $1\le i\le k$，你都需要输出**在前 $i$ 个变化发生的条件下**、在保证第 $n$ 个时刻结束时小 Z 恰好处于 $m$ 号点的基础上，小 Z 越过的最小障碍数。

对于 $100\%$ 的数据，$1 \leq n, m, k \leq 4 \times 10^6$，$1 \leq t_i \leq n$，$0 \leq p \leq 15$，$t_i$ **单调不升**，若 $t_i$ 相同，按 $x_i$ **升序**，且 $\forall 1 \leq i < j \leq k$，$(t_i, x_i)$ 和 $(t_j, x_j)$ 不同。**强制在线**。O2，500ms。

# 算法一

若将时间看作一个坐标轴，并且适当旋转一下。那么问题转化为：

在二维平面上，初始每个点上均有一个障碍物，每次拿走一个障碍物。拿走的顺序是先从上到下一行行拿，每一行内从右往左拿。每步可以向右走或者向下走，每次拿走后询问从左上角走到右下角最少经过多少障碍物。

由于按照这个规则走，总经过格子数是一定的，所以可以反过来看成初始为空，每次放一个障碍物，询问最多经过多少障碍物。

那么依照题意模拟，每次放完后 $\mathcal{O}(nm)$ dp 出最多走多少个障碍物。具体地，设 $f_{i,j}$ 为走到 $(i,j)$ 最多经过多少障碍物，$a_{i,j}$ 为 $(i,j)$ 上是否有障碍物，则有 $f_{i,j}=\max\{f_{i-1,j},f_{i,j-1}\}+a_{i,j}$．

时间复杂度为 $\mathcal{O}(knm)$，期望得分 15 分。

# 算法二

不难发现每次放障碍物后，只有当前行的 $f$ 值会发生变化，并且并不需要考虑下面行的 $f$ 值，所以每次放完障碍物只更新当前行的 $f$ 值即可。

时间复杂度 $\mathcal{O}(km)$，期望得分 35 分。

# 算法三

考虑对上述 dp 进行优化。采用常用的套路，用数据结构来维护 $f$，而维护整个二维的 $f$ 似乎把问题复杂化了，于是尝试只维护当前行的 $f$．

在同一行内从后往前放障碍物时，假设在 $(x,y)$ 处放置，那么可能会影响到 $y$ 后面很多个位置的 $f$ 发生改变。不过值得注意的是，由于已经求出上一次放置的答案，那么只需要关心新的可能成为答案的方案，而暂时不需要关系 $f$ 具体的变化。也就是考虑一定经过 $(x,y)$ 的路径最大答案是多少，其值为原先 $(x,y)$ 的 $f$ 值，加上 $(x,y)$ 及其右边有多少个障碍物。用其来更新答案即可。

那么现在要处理的就是新开一行的情况，要把当前行的 $f$ 处理出来再去考虑新的一行。由于从上一行向下走时如果没有遇到障碍物一定不会比遇到障碍物更优，于是单独考虑当前行有障碍物的位置。

假设从左往右依次为 $p_1,p_2,...,p_l$，那么考虑 dp 的过程，容易发现转移方法是每次将 $[p_i+1,p_{i+1}]$ 的 $f$ 与 $f_{p_i}$ 取 $\max$ 后再加 $1$，这个很容易用线段树来实现。

时间复杂度 $\mathcal{O}(k\log m)$．期望得分 84 分。

注意到 $f$ 是单调的，亦可以用树状数组维护。

时间复杂度 $\mathcal{O}(k\log m)$．期望得分 100 分。

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
	r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=4000010;
int n,m,q,lst=0,lstx=0,nowans=0,lastt=0,cnt=0;
int mx[N];
inline int lowbit(int x){return x&(-x);}
int query(int x){int s=0;for(;x;x-=lowbit(x))cmax(s,mx[x]);return s;}
void modify(int x,int v){for(;x<=m;x+=lowbit(x))cmax(mx[x],v);}
signed main(){
	read(n,m,q);
	vpii pos;
	for(int o=1;o<=q;o++){
		int t,p;read(t,p);
		int x=min(lstx+(p^((n+m-1-lst)%15))+1,m);
		if(o==1)x=min(p+1,m);
		lstx=x%m;
		t=n-t+1;x=m-x+1;
		if(t!=lastt){
			int len=pos.size(),lastval=0;reverse(pos.begin(),pos.end());
			for(int i=0;i<len;i++)
				modify(pos[i].fi,lastval=max(lastval,pos[i].se)+1);
			vpii().swap(pos);
			lst=query(m);
		}
		lastt=t;
		int val=query(x);
		pos.pb(mp(x,val));
		cmax(lst,val+(int)pos.size());
		cout << n+m-1-lst << '\n';
	}
    #ifdef do_while_true 
		cerr<<'\n'<<"Time:"<<clock()<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Leasier (赞：2)

~~我的做法似乎太麻烦了。~~
### Subtask $1$
直接暴力 dp 即可。时间复杂度为 $O(knm)$。
### Subtask $2$
前置芝士：[树状数组](https://oi-wiki.org/ds/fenwick/)

考虑将这个 dp 转化为以下模型：从 $(1, 1)$ 走到 $(n, m)$，动态地在某个点上添加障碍，并询问 $(1, 1)$ 走到 $(n, m)$ 所经过的最小障碍数。

注意到任何一种满足条件的走法一开始取到的值均为 $n + m - 1$，每走过一个 $0$ 就会使得值减小 $1$，问题转化为求经过 $0$ 的数量的最大值。

为了方便，我们令 $t_i \leftarrow n - t_i + 1$，$x_i \leftarrow m - x_i + 1$，则 $t_i$ 单调不升，若 $t_i$ 相同，$x_i$ 单调递减。

考虑设 $dp_i$ 表示位于 $(t_i, x_i)$ 时，此处的 $0$ 走过之后最多还能走过多少个 $0$。由于只能向下或者向右，走过一个 $0$ 之后所走过的 $0$ 显然都会在它的左上方，则 $dp_i = \displaystyle\max_{t_j \leq t_i, x_j \leq x_i} dp_j + 1$。

直接用树状数组维护前缀 max 即可。时间复杂度为 $O(k^2 \log m)$。
### Subtask $3$ & $4$
考虑两种情况。

1. $t_i \neq t_{i - 1}$

在前缀 max 的树状数组中更新 $t_j = t_{i - 1}$ 的所有 $j$ 的 $x_j$，**然后**一次前缀 max 查询求出 $dp_i$ 即可。

2. $t_i = t_{i - 1}$

容易发现在还未更新 $dp_{i - 1}$ 前 $dp_i \leq dp_{i - 1}$。

**首先**一次前缀 max 查询求出 $dp_i$，则本次更新可**依次向后传递**，即：$dp_{i - j} \leftarrow \max(dp_{i - j}, dp_i + j)$。

考虑到若存在一个最小的 $j$ 满足 $dp_{i - j} < dp_{i - j + 1}$，则从 $i - j$ 开始，再向前传递便不会更新任何值，于是我们可以找到一个最小的 $j$，使 $dp_j + j = dp_i + i - 1$（注意：**这里的 $dp_j$ 是传递之前的 $dp_j$**），并 $\forall y \in [j, i)$，令 $dp_y \leftarrow dp_y + 1$。这一步可以用二分 + 区间加、单点查询的树状数组维护。

综上，时间复杂度为 $O(k(\log m + \log^2 k))$。
### Subtask $5$
考虑用其他时间复杂度更低的维护方式替换二分。

考虑对于每一个 $i$ 维护一个**极大**可传递区间的左端点 $nxt_i$。即：在满足 $t_i = t_{nxt_i}$ 且 $\forall nxt_i < j \leq i$，$dp_j = dp_{j - 1} + 1$ 的情况下，$nxt_i$ 尽量小。

1. $t_i \neq t_{i - 1}$

显然 $nxt_i = i$。

2. $t_i = t_{i - 1}$

如果 $dp_i = dp_{i - 1}$，将 $[nxt_{i - 1}, i)$ 中每个 dp 值加 $1$，然后让 $nxt_i$ 向左扩展，每次令 $nxt_i = nxt_{nxt_i - 1}$，直到再跳就不符合条件为止；如果 $dp_i + 1 = dp_{i - 1}$，令 $nxt_i = nxt_{i - 1}$；否则，令 $nxt_i = i$。

现在考虑向左扩展的时间复杂度。

当 $dp_{nxt_i - 1} + nxt_i - 1 \neq dp_i - i$，显然不能再扩展；否则，$nxt_{nxt_i - 1}$ 一定已经是**极大**可传递区间的左端点了，所以只需要扩展一次。

综上，时间复杂度为 $O(k(\log m + \log k))$。

代码：
```cpp
#include <stdio.h>

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int lowbit(int x){
	return x & (-x);
}

typedef struct {
	int tree[20000007];
	
	inline int get_max(int x){
		int ans = 0;
		while (x > 0){
			ans = max(ans, tree[x]);
			x -= lowbit(x);
		}
		return ans;
	}
	
	inline void update(int n, int x, int k){
		while (x <= n){
			tree[x] = max(tree[x], k);
			x += lowbit(x);
		}
	}
} RMQ;

typedef struct {
	int tree[20000007];
	
	inline void update(int n, int x, int k){
		while (x <= n){
			tree[x] += k;
			x += lowbit(x);
		}
	}
	
	inline int get_val(int x){
		int ans = 0;
		while (x > 0){
			ans += tree[x];
			x -= lowbit(x);
		}
		return ans;
	}
	
	inline void assign(int n, int x, int k){
		update(n, x, k - get_val(x));
	}
	
	inline void add(int n, int l, int r, int k){
		update(n, l, k);
		update(n, r + 1, -k);
	}
} BIT;

int t[2000007], x_[2000007], nxt[2000007], dp[2000007];
RMQ tree1;
BIT tree2;

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

void write(int n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int n = read(), m = read(), k = read(), x = 0, all = n + m - 1, max_val = 0, last_ans = 0;
	for (register int i = 1, j = -1; i <= k; i++){
		int p;
		t[i] = n - read() + 1;
		p = read();
		x = min((x == m ? 0 : x) + (p ^ (last_ans % 15)) + 1, m);
		x_[i] = m - x + 1;
		if (t[i] != t[j]){
			if (j != -1){
				for (register int y = j; y < i; y++){
					dp[y] = tree2.get_val(y);
					max_val = max(max_val, dp[y]);
					tree1.update(m, x_[y], dp[y]);
				}
			}
			j = nxt[i] = i;
			dp[i] = tree1.get_max(x_[i]) + 1;
			tree2.assign(k, i, dp[i]);
		} else {
			int id = i - 1;
			dp[i] = tree1.get_max(x_[i]) + 1;
			tree2.assign(k, i, dp[i]);
			if (dp[i] == dp[id]){
				nxt[i] = nxt[id];
				tree2.add(k, nxt[id], id, 1);
				if (nxt[id] == j){
					dp[j]++;
				} else {
					int t = nxt[i] - 1;
					if (nxt[i] > j && tree2.get_val(t) + t == dp[i] + i) nxt[i] = nxt[t];
				}
			} else if (dp[i] + 1 == dp[id]){
				nxt[i] = nxt[id];
			} else {
				nxt[i] = i;
			}
		}
		last_ans = all - max(max_val, dp[j]);
		write(last_ans);
		putchar('\n');
	}
	return 0;
}
```

---

