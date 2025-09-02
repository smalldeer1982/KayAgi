# RGB Walking

## 题目描述

[Red and Blue and Green - fn and Silentroom](https://www.youtube.com/watch?v=UeN7U474cxE)

给定一个包含 $n$ 个顶点和 $m$ 条双向边的连通图，每条边的权重不超过 $x$。第 $i$ 条边连接顶点 $u_i$ 和 $v_i$，权重为 $w_i$，颜色为 $c_i$（$1 \leq i \leq m$，$1 \leq u_i, v_i \leq n$）。颜色 $c_i$ 为红色（red）、绿色（green）或蓝色（blue）。保证图中至少存在一条每种颜色的边。

对于一条允许重复顶点和边的路径，设 $s_r$、$s_g$、$s_b$ 分别表示路径中经过的红色、绿色和蓝色边的权重之和。若某条边被多次遍历，每次遍历均会被单独计数。

请找到从顶点 $1$ 到顶点 $n$ 的所有可能路径中，$\max(s_r, s_g, s_b) - \min(s_r, s_g, s_b)$ 的最小值。


## 说明/提示

第一个测试用例中，最优路径为 $1 \to 2 \to 3 \to 4$。使用的边依次为：
- $1 \to 2$（红色，权重 $2$）
- $2 \to 3$（绿色，权重 $3$）
- $3 \to 4$（蓝色，权重 $2$）

此时 $s_r = 2$，$s_g = 3$，$s_b = 2$，因此答案为 $1$。

第二个测试用例中，一条最优路径为 $1 \to 1 \to 2 \to 1 \to 2 \to 3 \to 4$。使用的边依次为：
- $1 \to 1$（红色，权重 $1$）
- $1 \to 2$（红色，权重 $1$）
- $2 \to 1$（红色，权重 $1$）
- $1 \to 2$（红色，权重 $1$）
- $2 \to 3$（绿色，权重 $4$）
- $3 \to 4$（蓝色，权重 $4$）

此时 $s_r = s_g = s_b = 4$，因此答案为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 3 3
1 2 2 r
2 3 3 g
3 4 2 b
4 5 4
1 2 1 r
1 1 1 r
2 1 1 r
2 3 4 g
3 4 4 b
4 6 4
1 2 2 r
1 2 2 r
2 3 3 b
1 3 4 r
1 4 1 g
3 4 4 g```

### 输出

```
1
0
0```

# 题解

## 作者：BPG_ning (赞：2)

可真是一道美题，但是题解区现存的两篇题解都讲的过于粗糙，笔者在学习时遇到了很多困难，故作题解记之。

先随便走一条回路，使得每条边都经过。对于一种颜色，令所有此颜色边的边权 gcd 为 $M_c$，可以认为这条回路上的权值和是 $2M_c$ 的倍数。

证明：设边 $i$ 经过次数为 $x_i$，那么权值和 $=\sum x_i w_i$，又因为 $2|x_i$，所以这个不定方程的每一项 gcd 为 $2M_c$，根据裴蜀定理 $y=\sum x_iw_i$ 有整数解当且仅当 $2M_c|y$。对于 $x_i\geq 0$ 的限制，我们可以走足够多条边使得三种颜色权值和相等，就能保证每条边走的次数足够多，即 $x_i\geq 0$。

考虑完一条“准备工作”的回路，接下来考虑 $1\to n$ 的一条路径，根据前面的推导发现你只关心边权和 $\mod {2M_c}$ 的结果，也就是说对于一条路径，答案即为 $a_i \equiv r_i \pmod{2M_i} ,\min(\max(a)-\min(a))$。进一步发现，$r_i$ 等于 $0$ 或 $M_i$，所以状态数是 $2^3$ 的，接下来只考虑已知 $r_i$ 求答案。

枚举一个 $a_i=k\times 2M_i+r_i$，找到每个颜色 $a_i$ 的前驱后继在 $2^2$ 统计答案即可，发现 $a_i$ 存在周期 $\operatorname{lcm}(M)$，所以枚举 $k$ 的复杂度为 $\frac{\operatorname{lcm}(M)}{\max(M)}$。容易发现直接做无法通过。

接下来是关键的一步，令 $p$ 是 $M_i$ 中一个质因子且对全局 $\operatorname{lcm}$ 有贡献，我们 $M_i\gets \frac{M_i}{p}$，答案不变！

证明：答案显然不会变劣，考虑证明答案不会变优，假设我们已经 $M'_i\gets \frac{M_i}{p}$，得到一组答案，由于 $M'$ 的周期 $\operatorname{lcm}(M')\times p = \operatorname{lcm}(M)$，所以我们一定可以调整到 $M$ 的周期上！

除去这些质因子之后，结果会形如：$M_0=gab,M_1=gbc,M_2=gac$，由于 $M_0,M_1,M_2\leq V$，所以 $\min(a,b,c)\leq \sqrt{V}$，此时做上述暴力，时间复杂度即为 $\frac{gabc}{\max(gab,gbc,gac)}=\min(a,b,c)\leq \sqrt{V}$，我们便通过了此题！

---

## 作者：operator_ (赞：2)

# CF2077G RGB Walking

[题目传送门](https://www.luogu.com.cn/problem/CF2077G)

这题作为一道 G，可能不算太难，但还是挺 educational 的。以下记 $s_x$ 为颜色 $x$ 的边权和，$g_x$ 为颜色 $x$ 的边权 $\gcd$。

我们不妨来考虑，假设只有一条唯一的路径，我们怎么做。容易发现，我们只要在一条边上多走一个来回，就可以让对应颜色的边权和加上 $2w$，这个形式让我们想到裴蜀定理，于是我们希望最终能达到让 $s_x$ 加上 $2g_x$ 的效果。事实上这是可以做到的，对于想加的边我们直接加就好了，而如果让所有边都先走上 $2\dfrac{\operatorname{lcm}(s_r,s_g,s_b)}{s_c}$（$c$ 是边的颜色）次，那么所有 $s$ 相对不变，我们只需要让想减的边少走一个来回就做到了减的效果。于是我们可以认为 $s_x$ 是在模 $2g_x$ 意义下的，那么对于更一般的情况，显然 $g_x$ 越小我们可以调整的范围就越大，所以我们先把所有边都走上一个来回一定不劣，此时 $s_x$ 只有 $0$ 和 $g_x$ 两种取值，求最终是否可以取到某种取值可以用 bfs 来处理，复杂度 $O(n+m)$。

现在本题就被割裂开了，还剩一个数论问题：给定 $3$ 个颜色的可取值的通项 $s'_x=lim_x+2k\times mod_x$，如何求最小极差。我最开始的想法是直接枚举最小与最大，再枚举答案，用 exCRT 合并后判断另一个颜色是否有可能在其中，没有实现过，因为在翻代码的时候发现了更优秀的做法：我们先减小 $mod_x$ 的范围，以 $mod_r$ 为例，我们一定可以把它变成 $mod'_r=\gcd(mod_r,\operatorname{lcm}(mod_g,mod_b))$，原理与上文所述类似。然后我们求出此时所有 $mod_x$ 的 $\operatorname{lcm}$，找到最大的 $mod_x$，暴力枚举 $s'_x$ 并求出其他的 $s'$ 来更新答案，显然此时其他 $s'$ 一定在枚举的值附近。

关于复杂度，我们来分析一下：对于单组询问，不妨设 $mod_r=gabx,mod_g=gacy,mod_b=gbcz$，其中 $x,y,z$ 两两互质，那么我们缩减后的 $mod'_r=gab,mod_g'=gac,mod'_b=gbc$，求出来的 $\operatorname{lcm}$ 是 $gabc$，然后枚举量是 $\dfrac{\operatorname{lcm}}{\max mod_x}$，也就是 $\min(a,b,c)$，而我们知道这是 $O(\sqrt V)$ 级别的，所以复杂度很对。

代码：

```cpp
//Date: 2025-03-12 19:31:51
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define P emplace_back
#define CLEAR(a,v) memset(a,(v),sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
//char buf[1<<20],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
bool MBE;
namespace SOLVER {
int n,m,x,mp[305],g[3],s[3],f[200005][9],mod[3],sum[3];vector<tuple<int,int,int>> G[200005];queue<pair<int,int>> q;
inline int gcd(int x,int y) {return !y?x:gcd(y,x%y);}inline int lcm(int x,int y) {return x*y/gcd(x,y);}
void MAIN() {
    n=rd(),m=rd(),x=rd();int ans=1e18;
    rep(i,0,n+1) G[i].clear(),CLEAR(f[i],0);g[0]=g[1]=g[2]=s[0]=s[1]=s[2]=0;
    rep(i,1,m) {
        int u=rd(),v=rd(),w=rd(),c=mp[getchar()];
        G[u].P(v,w,c),G[v].P(u,w,c),g[c]=gcd(g[c],w),s[c]+=w;
    }
    q.emplace(1,0);f[1][0]=1;
    while(q.size()) {
        auto [u,S]=q.front();q.pop();
        for(auto [v,w,c]:G[u]) {
            int T=S^((w%(2*g[c])/g[c])<<c);
            if(!f[v][T]) q.emplace(v,T),f[v][T]=1;
        }
    }
    rep(S,0,7) if(f[n][S]) {
        mod[0]=2*gcd(g[0],lcm(g[1],g[2])),sum[0]=(S>>0&1)*g[0]%mod[0];
        mod[1]=2*gcd(g[1],lcm(g[0],g[2])),sum[1]=(S>>1&1)*g[1]%mod[1];
        mod[2]=2*gcd(g[2],lcm(g[0],g[1])),sum[2]=(S>>2&1)*g[2]%mod[2];
        if(mod[1]<mod[2]) swap(mod[1],mod[2]),swap(sum[1],sum[2]);
        if(mod[0]<mod[1]) swap(mod[0],mod[1]),swap(sum[0],sum[1]);
        assert(lcm(mod[0],lcm(mod[1],mod[2]))/mod[0]<=pow(2*m,0.5)+5);
        for(int L=lcm(mod[0],lcm(mod[1],mod[2])),x=L+sum[0];x<L*2;x+=mod[0]) {
            rep(i,-2,2) rep(j,-2,2) {
                int y=(x/mod[1]+i)*mod[1]+sum[1],z=(x/mod[2]+j)*mod[2]+sum[2];
                ans=min(ans,max({x,y,z})-min({x,y,z}));
            }
        }
    }
    cout<<ans<<endl;
}
}
bool MED;
signed main() {
    //freopen(".in","r",stdin);freopen(".out","w",stdout);
    SOLVER::mp['r']=0,SOLVER::mp['g']=1,SOLVER::mp['b']=2;
    for(int tt=rd();tt;tt--) SOLVER::MAIN();
    cerr<<(&MBE-&MED)/1024<<" KB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

假设第 $i$ 条边被经过 $t_i$ 次。那么你发现我们可以通过到 $x$ 点的时候通过走到 $y$ 再走回 $x$ 这种操作使得 $t(x,y)$ 自增 $2$。

所以我们只关心 $t_i$ 的奇偶性。 不妨设每个 $t_i$ 都充分大。根据裴蜀定理，对于颜色 $c$，我们容易通过调整 $t$ 让颜色 $c$ 的权值和增加 $2\gcd_{c(e)=c}w(e)$。

所以对一个边 $e$，我们只关注其边权对 $2\gcd_{c(f)=c(e)}w(f)=M_c$ 取模的结果。由于 $M_c|2w(e)$ 所以 $w(e)\equiv 0\text{ or }\frac M2\pmod M$。

我们先关心走一条路径从 $1\to n$ 再考虑增加 $M_0,M_1,M_2$ 相关的东西。我们现在想要计算的是，我们能不能走到 $n$ 且对颜色 $i$ 的权值和对 $M_i$ 取模的结果恰为 $0 \text{ or }\frac{M_i}2$。我们对 $8$ 种情况都来处理。

相当于每条边有个 $\leq 7$ 的权值。然后要走一条路径，问能不能让所有经过边的权值异或为某个 $[0,7]$ 的数。这是经典问题，dfs 树找环然后线性基即可。

然后我们把问题转换成了三个变量 $x_0,x_1,x_2$ 满足 $x_i\equiv r_i\pmod {M_i}$（$r_i\in\{0,\frac{M_i}{2}\}$）。求 $\min(\max(x)-\min(x))$。

首先显然有 $O(n^2)$ 的做法。每次找最小的 $x_i$ 增加 $M_i$，然后更新答案。

考虑优化上面这个做法。不难发现 $M_i$ 当中其实很多因子是没用的。更具体地，$M_0\leftarrow \operatorname{lcm}(\gcd(M_0,M_1),\gcd(M_0,M_2))$ 结果不变。

我们把三个数按照上面地变换规则来，那么就会形如：$M_0=pab,M_1=pbc,M_2=pca$。由于 $\max(M)\leq x$。所以 $a,b,c$ 当中有至少两个小于 $\sqrt x$。

我们按照上面地暴力做 $x\sqrt x$ 就能保证正确性了。

---

