# [NOISG 2021 Finals] Pond

## 题目背景

乌龟 Syrup 经常在他家旁边的池塘里游泳。这个池塘是由很久以前的冰川运动形成的，呈狭长直线状，水面平静，适合双向游泳。

## 题目描述

今天，Syrup 像往常一样游泳时，发现了一簇绿点——正在萌发的藻类孢子。经过暴雨冲刷，富含营养的土壤流入池塘，为藻类提供了大量养分，导致它们以惊人的速度生长。如果不加以控制，这些藻类会遮挡阳光，破坏水下生态平衡。

幸运的是，Syrup 有一个简单有效的解决方案——吃掉它们。他已经识别出池塘中 $N$ 个土壤流失点，标号为 $1$ 到 $N$，并记下了它们之间的距离 $D_i$（第 $i$ 点到第 $i+1$ 点之间的距离为 $D_i$）。目前，Syrup 位于第 $K$ 个点，并从这里开始消灭藻类。

池塘中的每个点初始有 $0$ 条藻类，并且每秒会增加 $1$ 条藻类，直到 Syrup 到达该点并吃掉所有藻类。Syrup 需要选择一个方向，沿着池塘游泳，并依次吃掉遇到的所有藻类。为了让藻类不至于变得太难吃，他希望尽可能减少吃下的藻类总数。

你的任务是计算 Syrup 吃下的最少藻类总数。

## 说明/提示

【样例解释】

- 对于样例 $1$，最优路径是按顺序访问点 $3 \to 2 \to 4 \to 5 \to 6 \to 7 \to 1$，总共吃掉 $0 + 2 + 8 + 10 + 12 + 17 + 37 = 86$ 条藻类。
- 对于样例 $2$，最优路径是按顺序访问点 $5 \to 6 \to 4 \to 3 \to 2 \to 1 \to 7 \to 8 \to 9$，总共吃掉 $0 + 1 + 3 + 5 + 8 + 12 + 26 + 32 + 42 = 129$ 条藻类。
- 对于样例 $3$，最优路径是按顺序访问点 $4 \to 3 \to 2 \to 1 \to 5 \to 6$，总共吃掉 $0 + 1 + 2 + 3 + 7 + 8 = 21$ 条藻类。

【数据范围】

- $2 \leq N \leq 3 \times 10^5$
- $1 \leq K \leq N$
- $1 \leq D_i \leq 10^6$

| 子任务编号 | 分值 | 额外限制条件                       |
| :--------: | :--: | :-------------------------------: |
| $1$        | $7$  | $N \leq 100$                     |
| $2$        | $11$ | $N \leq 2000$                    |
| $3$        | $10$ | $1 \leq K \leq \min(N, 20)$      |
| $4$        | $6$  | $D_i = 1$                        |
| $5$        | $12$ | $1 \leq K \leq \min(N, 2000)$ 且 $D_i \geq D_{i+1}$（对所有 $i$ 满足 $i \not\equiv 0 \pmod{100}$） |
| $6$        | $25$ | $1 \leq K \leq \min(N, 2000)$    |
| $7$        | $29$ | 无额外限制                       |

## 样例 #1

### 输入

```
7 3
5 2 4 2 2 5```

### 输出

```
86```

## 样例 #2

### 输入

```
9 5
4 3 2 1 1 3 6 10```

### 输出

```
129```

## 样例 #3

### 输入

```
6 4
1 1 1 1 1```

### 输出

```
21```

# 题解

## 作者：forest114514 (赞：6)

这不是去年正睿某天 T4 吗？后面忘了，反正是道 DP 好题就是了。

首先 $O(k(n-k))$ 的 DP 是容易的，直接关路灯即可，但是优化不了一点。

但是我们关路灯用了费用提前计算的思想，这题也可以呢，只不过我们之前的贡献思想基于每步操作**两侧**路灯的贡献，自然需要二维来知道两边的信息，我们能否只用关系一侧信息？

不妨设每个点下标为 $p$，考虑除了从 $k$ 走向 $i$ 的那段是一定会有的之外其他所有背道而驰的路径都会使得这个水藻产生额外的贡献，如果从左边 $i$ 走到右边 $j$ 此时对 $1\sim i-1$ 的额外的贡献就是 $2(i-1)\times (p_j-p_i)$，为什么有二倍呢？因为你过去了还要回来，这也是额外的代价啊。相反同理。

设 $f_i$ 为当前走到了 $i$ 的最小代价转移有：
$$
\begin{aligned}
	&f_i+2(p_j-p_i)\times(i-1)\to f_j,i\leq K,j\geq K\\
	&f_i+2(p_i-p_j)\times(n-i)\to f_j,i\geq K,j\leq K
\end{aligned}
$$
这个转移有环，但是我们可以从最短路的角度看不难发现可以 dijkstra，每次从最小的开始转移，显然当前考虑完了的区间是 $[l,r]$，每次考虑 $f_{l-1}$ 和 $f_{r+1}$ 哪个更小即可，一开始 $f_{K}=\sum\limits_{i=1}^{n}|p_K-p_i|$，答案就是 $\min(f_1,f_n)$，看哪个先被转移到。

直接转移是 $O(n^2)$ 的，但是这个 DP 显然可以斜率优化，所以可以维护凸包做到 $O(n)$。

---

## 作者：ForgotMe (赞：4)

很有启发意义的一题。

题意等价于数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，现从第 $K$ 个点出发，设 $t_i$ 表示第一次走到 $t_i$ 的时间，要求最小化 $\sum t_i$。

显然有一个 $\mathcal{O}(n^2)$ 的区间 dp，表示设 $dp_{l,r,0/1}$ 现在已经经过了 $[l,r]$ 的点且在左边/右边的最小代价。但是这个 dp 的状态是平方级别的，很难进行优化，基本没有前途。

注意到上面这个 dp 的状态难以优化在于其每次代价的计算与 $l,r$ 都有关，能不能想一个办法把两边的代价分开计算呢。

不如先来观察一个 $t_i$ 的值是由哪些部分组成的。假设 $i<K$，那么如果在不管要求经过其他点的情况下，$t_i=x_K-x_i$，但是在这个途中可能会出一些**意外**。例如从 $K\rightarrow i$ 中在经过 $j(i<j<K)$ 时，突然要转向往右走走到 $K$ 右边的 $P(P>K)$ 然后再回来，那么可以发现 $t_i$ 会因为这个**意外**而多产生 $2(x_P-x_j)$ 的贡献。考虑将上面这个东西形式化的描述，设 $pos_i$ 表示走到 $i$ 时要转向走到 $pos_i$，如果不转向那么 $pos_i=0$。那么可知 $t_i=(x_K-x_i)+2\sum_{j=i+1}^K [pos_j\ne 0](x_{pos_j}-x_j)$。
我们把 $2\sum_{j=i+1}^K [pos_j\ne 0](x_{pos_j}-x_j)$ 这部分称为到达 $i$ 产生的额外贡献。其实这个思路应该叫作费用提前计算？

于是由此可以设计另外一个 dp，设 $f_x(x\le K)$ 表示当前走到 $x$ 所产生的所有的额外贡献之和的最小值，$g_x(x\ge K)$ 表示当前走到 $x$ 所产生的所有的额外贡献之和的最小值。

那么有 dp 转移式：

- $f_i=\min_j\{g_j+2(x_j-x_i)(n-j)\}$。

- $g_i=\min_j\{f_j+2(x_i-x_j)(j-1)\}$。

答案就是 $\min(f_1,g_n)+\sum_{i=1}^n |x_K-x_i|$。

上面这个玩意看上去就非常好优化，不就是一个斜率优化板子！做完了吗？其实还没有。你会发现一个巨大的问题在于这个 dp 居然没有一个确定的转移顺序！！这导致一个暴力 dp 都很难写出来。考虑把转移看成正权无向图上的边。那么这个 dp 相当于在做一个完全无向图上的单源最短路！可是这个边是平方级别的，做 dijkstra 复杂度直接升天了。

考虑 dijkstra 是怎么做的，最开始有一个空集 $S=\mathbb{\emptyset}$，然后拿出来当前不在集合 $S$ 且最短路最短的点 $u$ 进行转移并把点 $u$ 加入 $S$ 集合中。观察本题 dp 转移式，你会发现当 $j$ 固定时 $i$ 越小 $g_j+2(x_j-x_i)(n-j)$ 越大，$i$ 越大 $f_j+2(x_i-x_j)(j-1)$  越大。于是可以得出一个结论是在任意时刻 $S$ 形成了一个区间 $[l,r](l\le K\le r)$。也就是说每次加入集合 $S$ 的点不是 $l-1$ 就是 $r+1$。

于是双指针模拟这个过程，可以写出一个暴力:

```cpp
inline LL query2(int x){
	LL res=INF; 
	for(int i=l;i<=K;i++)res=min(res,f[i]+2ll*(d[x]-d[i])*(i-1));
	return res;
}
inline LL query1(int x){
	LL res=INF; 
	for(int i=K;i<=r;i++)res=min(res,g[i]+2ll*(d[i]-d[x])*(n-i));
	return res;
}
inline void solve(){
	gi(n),gi(K);
	for(int i=2;i<=n;i++){
		gi(d[i]);
		d[i]+=d[i-1];
	}
	if(K==1||K==n){
		LL res=0;
		for(int i=1;i<=n;i++)res+=abs(d[K]-d[i]);
		pi(res);
		return ;
	}
	for(int i=1;i<=n;i++)ans+=abs(d[K]-d[i]);
	for(int i=1;i<=K;i++)f[i]=INF;
	for(int i=K+1;i<=n;i++)g[i]=INF;
	f[K]=0;
	l=K,r=K;
	while(l>1||r<n){
		if(l==1){
			r++; 
			g[r]=query2(r);
		}else if(r==n){
			l--;
			f[l]=query1(l);
		}else{
			LL pl=query1(l-1),pr=query2(r+1);
			if(pl<=pr){
				l--;
				f[l]=pl;
			}else{
				r++;
				g[r]=pr;
			}
		}
	}
	pi(ans+min(f[1],g[n]));
}
```

发现优化是容易的，这是显然的斜率优化，上李超树即可，复杂度 $\mathcal{O}(n\log n)$。能不能线性呢？其实是可以的，注意到加入的点 $x$ 坐标递增，询问的斜率递增，把李超树换成凸包即可，但是感觉不太好写，所以推荐采用李超树。

完整代码：https://www.luogu.com.cn/paste/sx3uz6d8

---

## 作者：Lucyna_Kushinada (赞：2)

# P11303 [NOISG 2021 Finals] Pond

## 题意

有 $n$ 个路灯，路灯 $i$ 与路灯 $i+1$ 距离为 $d_i$，每秒没有被关闭的路灯都会消耗 $1$ 电能。

你初始时在 $m$，每秒可以移动 $1$ 单位距离，在移动过程中关闭所经过的路灯，直到所有路灯被关闭。

最小化消耗的总电能。

$n\le 3\times 10^5$。

## 题解

知识点：动态规划，斜率优化，李超线段树。

启发：

- 贡献提前计算。

- 代价分开计算。

不妨对 $d_i$ 做前缀和，得到 $a_i$，表示 $i$ 的位置，$a_1=0$。

首先有一个不需要怎么动脑子的区间 dp，设 $dp_{l,r,0/1}$ 为关闭了 $l\sim r$ 的路灯，最后停在左/右端点的最小消耗。

初始条件：$dp_{m,m,0}=dp_{m,m,1}=0$。

答案：$\min (dp_{1,n,0},dp_{1,n,1})$。

有如下转移：

$$
\begin{cases}

dp_{l,r,0}=\min(dp_{l+1,r,0}+(a_{l+1}-a_{l})(l+n-r),dp_{l+1,r,1}+(a_{r}-a_{l})(l+n-r))\\

dp_{l,r,1}=\min(dp_{l,r-1,0}+(a_{r}-a_{l})(l+n-r),dp_{l,r-1,1}+(a_{r}-a_{r-1})(l+n-r))

\end{cases}
$$

上面用到了贡献提前计算的思想，因为对于每个路灯，很难刻画他什么时候被关闭，所以使用一种巧妙的方法来变相维护。

以第一个转移第一个式子为例，从 $l+1$ 走到 $l$，耗时 $a_{l+1}-a_l$，这个过程中，$1\sim l$ 与 $r+1\sim n$ 的路灯都在消耗电能，所以加上 $(l+n-r)(a_{l+1}-a_l)$ 的消耗。

时间复杂度 $O(n^2)$。

代码如下，结合 $d_i=1$ 的特判，可以获得 $24$ 分。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 300010
#define int long long

int n,m,a[N],dp[2025][2025][2];

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    bool one=1;

    rep(i,2,n){
        int x;
        cin>>x;
        a[i]=a[i-1]+x;

        one&=(x==1);
    }

    if(one){
        int ans1=0,ans2=0;

        rep(i,1,m){
            ans1+=(a[m]-a[i]);
        }
        rep(i,m+1,n){
            ans1+=(a[m]-a[1])*2+a[i]-a[m];
        }

        rep(i,m,n){
            ans2+=(a[i]-a[m]);
        }
        rep(i,1,m-1){
            ans2+=(a[n]-a[m])*2+a[m]-a[i];
        }

        cout<<min(ans1,ans2);

        return 0;
    }

    rep(i,1,n){
        dp[i][i][0]=dp[i][i][1]=3e18;
    }

    dp[m][m][0]=dp[m][m][1]=0;

    rep(len,2,n){
        rep(l,1,n){
            int r=l+len-1;
            if(r>n){
                break;
            }

            dp[l][r][0]=min({dp[l+1][r][0]+(a[l+1]-a[l])*(l+n-r),dp[l+1][r][1]+(a[r]-a[l])*(l+n-r)});
            dp[l][r][1]=min({dp[l][r-1][0]+(a[r]-a[l])*(l+n-r),dp[l][r-1][1]+(a[r]-a[r-1])*(l+n-r)});
        }
    }

    cout<<min(dp[1][n][0],dp[1][n][1]);

    return 0;
}
```

但是 $n\le 3\times 10^5$，区间 dp 的状态包含两个端点，状态数十分爆炸，能否拆开两个端点，分别考虑？

通过上面的观察，可以发现答案由两部分组成，每个路灯到第 $m$ 个路灯的距离之和加上额外的电能消耗，前者是固定的，所以考虑最小化后者。

先思考最优的移动路径长什么样子，肯定是从 $m$ 出发，走到 $m$ 的一边，再掉头走到 $m$ 的另一边，不会出现类似在 $m$ 的右边，往左走但没走到 $m$，又转头往右走的情况，这种是纯浪费。

可以发现，每一次的掉头走一段距离，都会关闭新的路灯，也都会跨过 $m$。

那就找到了分界点 $m$，接着将两个端点分开，定义 $f_i(i\le m)$ 表示走到 $i$ 位置的最小消耗，$g_i(i\ge m)$ 表示走到 $i$ 位置的最小消耗。

根据上面的推理，$f_i$ 一定是从 $g_i$ 转移过来（跨过 $m$），反之亦然，可以得出以下转移：

$\displaystyle f_i=\min_{j\ge m} g_j+2(a_j-a_i)(n-j)$

$\displaystyle g_i=\min_{j\le m} f_u+2(a_i-a_j)(j-1)$

依旧是运用了贡献提前计算的思想，以第一个式子为例，$f_i$ 从 $g_j$ 转移过来，相当于从 $j$ 走到 $i$，虽然距离为 $a_j-a_i$，但是还是会走回去的（或者从 $g_n$ 转移过来，但是此时没有额外贡献），且一定会再次经过 $j$，此时路程为 $2(a_j-a_i)$，相比于正常走，第 $j+1\sim n$ 个路灯晚到了 $2(a_j-a_i)$，所以提前计算他们的贡献，显然 $1\sim i-1$ 的贡献不用计算。

发现无法确定转移的顺序，此时需要的是一个类 dijkstra 状物式的拓展，设定 $l=r=m$，表示当前 $f_l$ 和 $g_r$，每次 $f_l$ 选择当前最优的 $g_i(i\in[m,r])$ 往左拓展，同样地每次 $g_r$ 选择当前最优的 $f_i(i\in[l,m])$ 往右拓展，当两者都能拓展时，贪心地选择 dp 值最小的拓展，这基于的是 $g_i,f_i$ 都是单调的，根据状态的定义就能轻易证明。

最终可以得到一个 $O(nk)$ 的做法。

再转过头看转移式，发现可以斜率优化，所以直接上李超线段树，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define bg(x) (x).begin()
#define ed(x) (x).end()
#define sz(x) (int)(x).size()

#define N 300010
#define int long long

int n,m,a[N],f[N],g[N];

struct lct{//lichao
    #define mid ((l+r)>>1)

    pr tr[N<<2];

    inline int calc(pr u,int x){
        return u.fi*x+u.se;
    }

    inline void build(int k,int l,int r){
        tr[k]={1e7,1e18};

        if(l==r){
            return;
        }

        build(k*2,l,mid);
        build(k*2+1,mid+1,r);
    }

    inline void ref(int k,int l,int r,pr u){
        if(calc(u,a[mid])<calc(tr[k],a[mid])){
            swap(u,tr[k]);
        }

        if(l==r){
            return;
        }

        if(calc(u,a[l])<calc(tr[k],a[l])){
            ref(k*2,l,mid,u);
        }
        if(calc(u,a[r])<calc(tr[k],a[r])){
            ref(k*2+1,mid+1,r,u);
        }
    }

    inline int ask(int k,int l,int r,int x){
        if(l==r){
            return calc(tr[k],x);
        }

        int ans=calc(tr[k],x);

        if(x<=a[mid]){
            ans=min(ans,ask(k*2,l,mid,x));
        }
        else{
            ans=min(ans,ask(k*2+1,mid+1,r,x));
        }

        return ans;
    }

    #undef mid
}ft,gt;

inline void insf(int i){
    ft.ref(1,1,n,{2*(i-1),-2*(i-1)*a[i]+f[i]});
}

inline void insg(int i){
    gt.ref(1,1,n,{2*(i-n),2*(n-i)*a[i]+g[i]});
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    rep(i,2,n){
        cin>>a[i];
        a[i]+=a[i-1];
    }

    ft.build(1,1,n);
    gt.build(1,1,n);

    int l=m,r=m;

    insf(l);
    insg(r);

    while(l>1||r<n){
        if(l==1){
            r++;

            g[r]=ft.ask(1,1,n,a[r]);
            insg(r);

            continue;
        }
        if(r==n){
            l--;

            f[l]=gt.ask(1,1,n,a[l]);
            insf(l);

            continue;
        }

        int resl=gt.ask(1,1,n,a[l-1]),resr=ft.ask(1,1,n,a[r+1]);

        if(resl<=resr){
            l--;
            f[l]=resl;
            insf(l);
        }
        else{
            r++;
            g[r]=resr;
            insg(r);
        }
    }

    int ans=min(f[1],g[n]);

    rep(i,1,n){
        ans+=abs(a[i]-a[m]);
    }

    cout<<ans<<"\n";

    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P11303)

**题目大意**

> 数轴上给定 $n$ 个点 $x_1\sim x_n$，从 $x_k$ 出发访问所有点，最小化每个点首次被访问时经过的距离总和。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

朴素的状态是 $dp_{l,r,0/1}$ 表示当前经过 $[l,r]$ ，到达 $l/r$ 时的最小总和。

我们需要在状态中分离出 $l,r$，即对每个 $l/r$ 分别计算贡献。

尝试再每个掉头的位置计算贡献，对每个点我们先假设答案是 $|x_i-x_k|$，此时如果我们在到达 $x_l$ 之后先掉头去了 $x_r$ 再回到 $x_{l-1}$，那么就会让 $x_1\sim x_{l-1}$ 的距离增加 $2|x_l-x_r|$。

那么就能设立出如下状态：$f_l,g_r$ 表示掉头在 $x_l/x_r$ 时的最小代价，转移就是 $g_r=\min f_l+2(l-1)|x_r-x_l|,f_l=\min g_r+2(n-r)|x_r-x_l|$。

但是此时我们对 $f,g$ 的转移没有一个明确的顺序，并且我们并不能保证 dp 出来的路径满足 $l$ 递减 $r$ 递增，

分析该转移，首先我们可以用 Dijkstra 维护转移。

其次我们注意到 $g_r\to f_l$ 的代价严格小于 $g_r\to f_{l-1}$ 的代价。

因此我们 Dijkstra 从 $[u,v]=[k,k]$ 开始，每一次增广到的最近点一定是 $x_{u-1}/x_{v-1}$，即任何时候经过的点都是一个区间。

由于我们的代价函数形式较好，不难证明 $f,g$ 的转移具有决策单调性，从而 dp 出的路径一定是合法的。

那么我们对已知的 $f/g$ 维护一个凸壳，转移的时候直接求最小点值，可以用李超树实现。

时间复杂度 $\mathcal O(n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5;
const ll inf=1e18;
struct func {
	ll k,b;
	ll f(ll x) { return k*x+b; }
}	a[MAXN];
struct LCT {
	int tr[MAXN],ls[MAXN],rs[MAXN],tot;
	void ins(int id,ll l,ll r,int &p) {
		if(!p) return tr[p=++tot]=id,void();
		ll mid=(l+r)>>1;
		if(a[tr[p]].f(mid)>a[id].f(mid)) swap(tr[p],id);
		if(l==r) return ;
		if(a[tr[p]].f(l)>a[id].f(l)) ins(id,l,mid,ls[p]);
		if(a[tr[p]].f(r)>a[id].f(r)) ins(id,mid+1,r,rs[p]);
	}
	ll qry(ll x,ll l,ll r,int p) {
		ll s=a[tr[p]].f(x);
		if(!p||l==r) return s;
		ll mid=(l+r)>>1;
		return min(s,x<=mid?qry(x,l,mid,ls[p]):qry(x,mid+1,r,rs[p]));
	}
}	F,G;
int n,m,rf,rg;
ll x[MAXN],f[MAXN],g[MAXN];
signed main() {
	scanf("%d%d",&n,&m),a[0]={0,inf};
	for(int i=2;i<=n;++i) scanf("%lld",&x[i]),x[i]+=x[i-1];
	a[n+1]={-2*(n-m),2*(n-m)*x[m]},F.ins(n+1,0,x[n],rf);
	a[n+2]={2*(m-1),-2*(m-1)*x[m]},G.ins(n+2,0,x[n],rg);
	int l=m,r=m;
	while(1<l||r<n) {
		ll vl=(l==1?inf:F.qry(x[l-1],0,x[n],rf));
		ll vr=(r==n?inf:G.qry(x[r+1],0,x[n],rg));
		if(vl<vr) {
			f[--l]=vl,a[l]={2*(l-1),vl-2*(l-1)*x[l]},G.ins(l,0,x[n],rg);
		} else {
			g[++r]=vr,a[r]={-2*(n-r),vr+2*(n-r)*x[r]},F.ins(r,0,x[n],rf);
		}
	}
	ll ans=min(f[1],g[n]);
	for(int i=1;i<=n;++i) ans+=abs(x[i]-x[m]);
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：伊地知虹夏 (赞：1)

非常 edu 的一道题啊。

## Descirption

数轴上有 $n$ 个点，第 $i$ 个点坐标为 $X_i$，你要从第 $k$ 个点出发到达每个点。记到达 $i$ 号点的时刻为 $t_i$，你需要最小化 $\sum t_i$。

## Analyze

首先有一个朴素的关路灯 dp，即设 $f_{i,j, 0/1}$ 表示访问完区间 $[i,j]$，且最后在左/右端点的最小 $\sum t_i$。

这个 dp 状态是二维的，如果想要优化就先得从状态入手。

考虑最后的行走序列一定形如 $a_1 \to b_1 \to a_2 \to b_2 \to \cdots \to a_p(b_p)$，其中 $a_i \le k, b_i > k$。将代价拆到每个转向点上，当 $a_i \to b_i$，前 $a_i-1$ 个点要额外走 $2(X_{b_i} - X_{a_i})$，$b_i \to a_{i+1}$ 同理。

考虑设状态 $f_i$ 表示走到 $i$ 的最小额外代价，那么有转移：

- $f_i = \min\limits_{j \ge k} f_j + 2(n-j)(X_j-X_i)$，当 $i \le k$。
- $f_i = \min\limits_{j \le k} f_j + 2(j-1)(X_i-X_j)$，当 $i > k$。

但是转移量还是太大了，而且没有明显的拓扑序。实际上我们是要在一个 $n ^ 2$ 边的图上做最短路，这是比较困难的。

但本题的边权有性质，当 $j$ 固定时，$i$ 越小，边权越大。这说明 $f$ 是以 $k$ 为谷的单谷函数。考虑 dijkstra 的过程，其维护了一个集合 $S$，初始为 $\{k\}$，每次找距离 $S$ 中元素最小的点 $P$ 加入集合 $S$ 中。由于 $f$ 单谷，那么有 $S$ 在任意时刻都形如一个区间，维护这个区间 $[l,r]$，每次拓展只要考虑 $l-1,r+1$ 中的较小值即可。

现在转化为了一个动态加点，查询某个点在集合中的截距最小值。由于 $X$ 是单调的，可以直接维护凸包，也可以李超树。时间复杂度 $\mathcal O(n)$ 或 $\mathcal O(n\log n)$。

---

## 作者：yukimianyan (赞：0)

## 题目描述

花花和啾啾是好朋友。花花要给啾啾的花园清除杂草。

啾啾的后花园可以抽象为一个数轴，数轴上有 $n$ 个杂草，从左到右编号为 $1$ 到 $n$。第 $i$ 个杂草距离第 $i+1$ 个杂草 $d_i$，初始花花在第 $k$ 个杂草上。

初始所有杂草高度为 $0$, 每经过 $1$ 秒会增长 $1$。花花每秒能走 $1$ 单位距离，清除杂草不需要时间，清除后不会继续生长。

因为清除下来的杂草太多不方便运输。花花想知道要清除所有杂草，杂草被清除时高度之和最小是多少。

$1\leq k\leq n\leq 3\times 10^5,1\leq d_i\leq 10^6$

## solution

### subtask 5

这个 subtask 的具体限制是 $k\leq 2000,d_i\geq d_{i+1},\forall i\not \equiv 0\pmod {100}$。这是个啥？

考虑区间 dp。$f_{l,r,0/1}$ 表示已经干掉了 $[l,r]$ 的草，当然 $k\in[l,r]$，然后现在在 $l$ 还是 $r$。决策是向哪一边走，可以对费用提前计算，就是我走一秒是对答案加上“所有没死的草的棵树”这么多。也很好写。这就 $O(nk)$ 了。

这个特殊性质很神秘动人。实际上，我们发现，向右走的时候，如果 $i>k,d_i\geq d_{i+1}$ 且我们走到 $i+1$ 了，是不是会有一种继续走到 $i+2$ 的冲动，肯定继续走啊，因为现在折返再回来会更远，感性理解一下。于是我们就断言折返的地方一定满足 $d_i<d_{i+1}$。于是就 $O(nk/100)$ 了。

### 正解

首先定义一个东西，势能 $U$（我觉得不应该叫势能，但是没别的名字）。当我们现在在 $p$ 时，势能 $U$ 就等于 $\sum_iT(i)$，其中 $T(i)$ 是对草定义的：假设当前时间是 $t$，也即高度，如果草在 $t$ 前死亡，那么 $T(i)$ 是他的死亡时间；否则，$T(i)=t+dist(p,i)$。非常奇怪，但是有性质比较诱人：

- 踩死一棵草，势能不变，以后不需要管这棵草的距离以及高度。
- 接近一棵草，势能不变，正负抵消。
- 远离一棵草，势能 $+2$。

- 如果我们走到了 $1$ 或 $n$，那么可以得知 $ans\leq U$。或者更极端一点 $ans=U$，当 $U$ 是记我们所能得到的最小势能时。为了以后方便讨论，我们以 $k$ 为中心断开，$[1,k]$ 翻转变为左部 $[1,n]$，$[k,n]$变为右部 $[1,m]$。这样，如果我们走到了左部终点或右部终点，那么向相反方向走一轮，最终草全死了，势能就是答案。

开始 dp。记 $f_i$ 是左部，表示在左部 $i$ 号点的最小势能；$g_j$ 是右部，表示在右部 $i$ 号点的最小势能。有转移。
$$
f_i=\min_j\{g_j+2(m-j)(s1_i+s2_j)\}
$$

$$
g_j=\min_i\{f_i+2(n-i)(s1_i+s2_j)\}
$$

$s1,s2$ 是两边距离的前缀和。以第一条为例解释，我首先走到右部 $j$ 踩死右部 $[1,j]$ 上的草，得到势能 $g_j$，然后折返经过 $k$ 到达左部 $i$，这个过程中，右部 $[1,j]$ 已经死了；$[j+1,m]$ 被远离，势能一直 $+2$；左部 $[i+1,n]$ 始终被接近，势能不变；$[1,i]$ 被逐步接近之后踩死，势能一直不变。所以整个势能的变化就很优美。

但是这个 dp 方程的转移怎么在互相转移，很丑啊，我们观察到**系数都是**一堆**正数**，而且 $f,g$ 各自**单调**。有方法，考虑像 dijkstra 一样转移，按照大小顺序逐个转移。维护两个指针 $p_1,p_2$ 表示目前 $f[0,p_1)$ 到 $g[0,p_2)$ 都已经**确定**（注意 $f_0=g_0$ 且容易**计算**并**确定**；计算和确定是不同的）。每一次，计算即将产生的 $f[p_1],g[p_2]$，如果 $f[p_1]<g[p_2]$，我们就确定 $f[p_2]$，按照大小顺序转移；否则确定 $g[p_2]$。在计算的时候只用已确定的值转移。

斜率优化。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
struct dot {
  LL x, y;
  dot operator-(dot b) const { return {x - b.x, y - b.y}; }
  friend LL  cross(dot a, dot b) { return a.x * b.y - a.y * b.x; }
};
struct convexHull {
  dot q[300010];
  int L = 1, R = 0;
  void addPoint(LL x, LL y) {
    dot t = {x, y};
    while (L < R && cross(t - q[R], q[R - 1] - q[R]) <= 0) --R;
    q[++R] = t;
  }
  LL query(LL k) {
    while (L < R && cross(q[L + 1] - q[L], {1, k}) >= 0) ++L;
    return q[L].y - k * q[L].x;
  }
};
int n, m, _1, _2;
LL s1[300010], s2[300010], f[300010], g[300010];
convexHull F, G;
LL dp() {
  for (int i = 1; i <= n; i++) s1[i] += s1[i - 1];
  for (int i = 1; i <= m; i++) s2[i] += s2[i - 1];
  for (int i = 1; i <= n; i++) f[0] += s1[i];
  for (int i = 1; i <= m; i++) f[0] += s2[i];
  g[0] = f[0];
  int p1 = 0, p2 = 0;
  F.addPoint(2 * p1, f[p1] + 2 * s1[p1] * (n - p1));
  G.addPoint(2 * p2, g[p2] + 2 * s2[p2] * (m - p2));
  for (int t = 1; t <= n + m; t++) {
    if (p1 < n && (p2 == m || G.query(s1[p1 + 1]) + 2 * s1[p1 + 1] * m <= F.query(s2[p2]) + 2 * s2[p2] * n)) {
      //    f[++p1] = 1e18;
      //    for (int j = 0; j <= p2; j++) f[p1] = min(f[p1], g[j] + (s1[p1] + s2[j]) * 2 * (m - j));
      ++p1;
      f[p1] = G.query(s1[p1]) + 2 * s1[p1] * m;
      F.addPoint(2 * p1, f[p1] + 2 * s1[p1] * (n - p1));
    } else {
      //    g[++p2] = 1e18;
      //    for (int j = 0; j <= p1; j++) g[p2] = min(g[p2], f[j] + (s1[j] + s2[p2]) * 2 * (n - j));
      ++p2;
      g[p2] = F.query(s2[p2]) + 2 * s2[p2] * n;
      G.addPoint(2 * p2, g[p2] + 2 * s2[p2] * (m - p2));
    }
  }
  return min(f[n], g[m]);
}
int main() {
#ifndef LOCAL
freopen("cut.in", "r", stdin);
freopen("cut.out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(false);
#endif  
  cin >> _1 >> _2;
  n = _2 - 1, m = _1 - _2;
  for (int i = 1; i <= n; i++) cin >> s1[i];
  for (int i = 1; i <= m; i++) cin >> s2[i];
  reverse(s1 + 1, s1 + n + 1);
  cout << dp() << endl;
  return 0;
}
```

---

