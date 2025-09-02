# Alice's Adventures in the Rabbit Hole

## 题目描述

爱丽丝在兔子洞的底部！兔子洞可以建模为一棵树 $^{\text{∗}}$  ，在顶点 $1$ 有一个出口，而爱丽丝从某个顶点 $v$ 开始。她想要逃出这个洞，但不幸的是，红心女王下令处决她。

每分钟都会抛一次公平的硬币。如果硬币正面朝上，爱丽丝可以移动到她当前位置的一个相邻顶点，否则，红心女王可以将爱丽丝拉到女王选择的一个相邻顶点。如果爱丽丝最终出现在树的任何非根叶子 $^{\text{†}}$ 上，爱丽丝就输了。

假设他们都以最佳方式移动，计算爱丽丝从每个起始顶点 $1\le v\le n$ 成功逃脱的概率。由于这些概率可能非常小，因此输出它们对 $998\,244\,353$ 的取模。

形式上，设 $M = 998\,244\,353$ 。可以证明，确切的答案可以表示为一个不可约分的分数 $\frac{p}{q}$ ，其中 $p$ 和 $q$ 是整数且 $q \not \equiv 0 \pmod{M}$。输出等于 $p \cdot q^{-1} \bmod M$ 的整数。换句话说，输出这样一个整数 $x$，使得 $0 \le x < M$ 和 $x \cdot q \equiv p \pmod{M}$ 

---
$^{\text{∗}}$
 一棵树是一个连通的简单图，具有 $n$ 个顶点和 $n-1$ 条边。

$^{\text{†}} $
 一个叶子是一个仅与一条边相连的顶点。

## 说明/提示

对于第一个测试用例：

1.根据定义，爱丽丝从根节点（顶点 $1$）逃脱的概率为 $1$。\
2.爱丽丝从顶点 $4$ 和 $5$ 立即输掉，因为它们是叶子。\
3.从另外两个顶点，爱丽丝以概率 $\frac 12$ 逃脱，因为女王会将她拉到叶子。

## 样例 #1

### 输入

```
2
5
1 2
1 3
2 4
3 5
9
1 2
2 3
4 5
5 6
7 8
8 9
2 4
5 7```

### 输出

```
1 499122177 499122177 0 0 
1 499122177 0 332748118 166374059 0 443664157 720954255 0```

# 题解

## 作者：spdarkle (赞：8)

首先，贪心地，Alice 只能够向上走，而皇后必然会让其更加靠近叶子，因此会往子树内最近的叶子走。

所以我们可以得到 $f_u=\frac{1}{2}(f_v+f_{fa})$，其中 $v$ 是 $u$ 子树内最近的叶子的方向。

考虑怎么解这个方程，由于是树形结构，而 $f_1=1,f_{leave}=0$，因此我们可以考虑待定系数。

设 $f_u=k_uf_{fa}+b_u$，则带入原式，有：

$$f_{u}=k_uf_{fa}+b_u=\frac{1}{2}(f_{fa}+k_vf_u+b_v)$$

稍加整理，我们得到：
$$
k_u=\frac{1}{2-k_v},b_u=\frac{b_v}{2-k_v}
$$
而叶子节点显然有 $k_{leave}=b_{leave}=0$。

那么幸运地是，我们发现 $b_u$ 恒为零，因此我们可以通过深搜求出 $k,b$，再通过一次深搜求算出答案。

[submission](https://codeforces.com/contest/2028/submission/291016316)

---

## 作者：729hao (赞：6)

[**luogu 传送门**](https://www.luogu.com.cn/problem/CF2028E) [**codeforces 传送门**](https://codeforces.com/problemset/problem/2028/E)


---

## 思路
首先分析双方会如何决策。

显然，爱丽丝一定会往根的方向走。

那么，既然女王不想让爱丽丝到根节点，她就不会让爱丽丝往上走。她又想让爱丽丝尽快走到叶子节点，所以她一定会往子树内深度最小的叶子节点。

于是先对整棵树短链剖分一下。令 $s_i$ 表示点 $i$ 的短儿子（短链剖分上的儿子）。

那么爱丽丝从点 $i$ 逃离的概率 $p_i=\frac{1}{2}p_{fa_i}+\frac{1}{2}p_{s_i}$。

接下来考虑如何计算 $p_i$。

假设我们现在考虑如下图的一条链（top 为链顶，leaf 为链的叶子）：

![](https://cdn.luogu.com.cn/upload/image_hosting/97n40pow.png)

显然，$p_{leaf}=0$。

那么 $p_2=\frac{1}{2}p_3+\frac{1}{2}p_{leaf}=\frac{1}{2}p_3$。

同理，$p_3=\frac{1}{2}p_4+\frac{1}{2}p_2=\frac{1}{2}p_4+\frac{1}{2}\times\frac{1}{2}p_3=\frac{1}{2}p_4+\frac{1}{4}p_3$。

整理一下得 $p_3=\frac{2}{3}p_4$。

以此类推得 $p_4=\frac{3}{4}p_5$。

观察发现，如果 $i$ 到链叶子节点的距离为 $d$，则 $p_i=\frac{d}{d+1}p_{fa_i}$。

证明不难，这里就不写了。可以发现这个结论对于链顶仍然适用。

显然，根节点的答案为 $1$，于是整棵树的答案都可以求出来了。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	const int N=2e5;
	const LL Mod=998244353;
	int T,n;
	vector<int>v[N+5];
	int fa[N+5],mind[N+5],ss[N+5];
	LL inv[N+5],p[N+5];
	LL fastpow(LL a,int x){
		LL rtn=1ll;
		while(x){
			if(x&1)rtn=rtn*a%Mod;
			a=a*a%Mod;
			x>>=1;
		}
		return rtn;
	}
	void dfs(int rt,int prt){
		fa[rt]=prt;
		for(auto u:v[rt]){
			if(u==prt)continue;
			dfs(u,rt);
			if(ss[rt]==0||mind[ss[rt]]>mind[u])ss[rt]=u;
		}
		mind[rt]=mind[ss[rt]]+1;
	}
	void DP(int rt,int prt){
		if(rt==1) p[rt]=1;
		else if(v[rt].size()==1) p[rt]=0;
		else p[rt]=p[prt]*(mind[rt]-1)%Mod*inv[mind[rt]]%Mod;
		for(auto u:v[rt]){
			if(u==prt)continue;
			DP(u,rt);
		}
	}
	void Init(){
		for(int i=1;i<=n;i++){
			v[i].clear();
			fa[i]=ss[i]=mind[i]=0;
			p[i]=0;
		}
	}
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
		cin>>T;
		for(int i=1;i<=N;i++){
			inv[i]=fastpow(i,Mod-2);
		}
		int x,y;
		while(T--){
			Init();
			cin>>n;
			for(int i=1;i<n;i++){
				cin>>x>>y;
				v[x].push_back(y);
				v[y].push_back(x);
			}
			dfs(1,0);
			DP(1,0);
			for(int i=1;i<=n;i++){
				cout<<p[i]<<" ";
			}
			cout<<"\n";
		}
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

## 作者：mango2011 (赞：6)

## 废话

喜提这题正式选手的首杀。

## 分析

比较综合的一道题目。首先观察这个题目，发现如果说我们能够求出每个点 $u$ 可以到父亲节点的概率 $f_u$，就可以通过一遍普通的树形 dp 求出答案，因此考虑怎么求 $f_u$。

分析一下双方的策略：

+ 爱丽丝肯定是往父亲走。
+ 皇后肯定是把爱丽丝往子树内深度最小的叶子赶（如果有多个，任取）。

爱丽丝的策略显然，皇后的策略就是非常朴素的贪心（因为对她来说只关注子树内与爱丽丝最近的叶子，与具体位置无关）。

于是我们可以一遍 dfs 预处理出 $nxt_u$ 表示如果爱丽丝在节点 $u$，那么皇后会把它拽到哪里。

这样我们就可以快速计算 $f_u$ 了：

设 $x=f_{nxt_u}$，枚举 $u$ 被“拽下去又回来的次数”，得到下面的式子：

$$f_u=\displaystyle\sum_{i=0}^{+\infin}(\frac{1}{2})^{i+1}x^i$$

整理得到：

$$f_u=\frac{1}{2}\displaystyle\sum_{i=0}^{+\infin}(\frac{x}{2})^i$$

简单换元，令 $y=\frac{x}{2}$（显然 $<1$），于是：

$$f_u=\frac{1}{2}\displaystyle\sum_{i=0}^{+\infin}y^i=\frac{1}{2}\times \frac{1}{1-y}$$

因此我们可以快速处理出 $f_u$ 了，最后简述一下怎么求答案 $g_u$：

+ $g_1=1$。
+ $g_u=g_{fa_u}\times f_u$（$u\not=1$）。

综上，我们就做完了这个题目，时间复杂度 $O(n\log M)$（$\log M$ 为求逆元，但是如果您比较空，也可以 $O(1)$ 逆元消灭 $\log$）。

[提交记录](https://codeforces.com/contest/2028/submission/290902424)

---

## 作者：Hoks (赞：4)

## 前言
一眼题，为什么写了 $50+$ min。

太唐了。

短链剖分也是挺牛的。
## 思路分析
首先我们设 $f_i$ 表示在点 $i$ 开始 Alice 获胜的概率。

那么我们可以得到一个式子：
$$f_u=\frac{f_{ff}+\min{f_v}}{2}$$

其中 $ff$ 是 $u$ 的父亲，而 $v$ 是 $u$ 的儿子。

然后特殊的我们有 $f_1=1$ 且对于叶子 $u$，$f_u=0$。

这个式子里有一个 $\min$，感觉很抽象，考虑找性质给他消掉。

我们从皇后的角度考虑，就会发现，皇后肯定是想要让 Alice 走到最近的一个叶子去。

因为 Alice 的决策肯定是向上走，所以 Alice 走了一步后**肯定会离当前子树的所有叶子都远一步**。

**也就是 Alice 的决策是不会影响皇后的决策的。**

那么皇后的决策就非常简单了，对于点 $u$，找到他子树里最近的叶子 $x$，然后顺着 $u\rightarrow x$ 这条路径上走。

这里还有一个问题，皇后为什么不可能向上走。

这点其实是显然的，你向上走就相当于在给 Alice 送步数，所以肯定是向下走的。

现在我们就可以处理出来对于每个点 $u$ 的**最坏儿子**，然后考虑来做。

**其实这个最近的叶子这样搞就是短链剖分了。**

我们观察到数被短链剖分**完全剖分**为了叶子个数条链，考虑对每条链来做。

对于一条链，假设链顶为 $u$，其父亲是 $f$，其最坏儿子为 $v$，$v$ 的最坏儿子为 $k$。

我们来推下式子可以得到：
$$f_u=\frac{1}{2} f_f+\frac{1}{2} f_v$$
$$f_v=\frac{1}{2} f_u+\frac{1}{2} f_k$$
把下面的 $f_u$ 用上面那个式子代入。
$$f_v=\frac{1}{4} f_f+\frac{1}{4} f_v+\frac{1}{2} f_k$$
移项然后系数化为一得到：
$$f_v=\frac{1}{3} f_f+\frac{2}{3} f_k$$
这里规律其实已经出来了，也就是对于这条链里深度为 $d$ 的点 $u$，若其儿子为 $v$，链顶父亲的概率为 $p$，则有：
$$f_u=\frac{1}{d+1} p+\frac{d}{d+1} f_v$$
这个式子的左右两半部分显然是可以割裂了算的，所以我们考虑做一个像树剖第二遍 dfs 一样的遍历（因为这题就是短链剖分嘛）。

那么从上而下走的时候优先走**短儿子**（类似的定义的到），然后把式子的前半部分算上，走到底了之后再在回溯回去的时候把后半部分的贡献算上就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define calc(x) ((x)*((x)+1)>>1)
#define int long long
using namespace std;
const int N=1e6+10,V=1e6,M=27,INF=1e18,mod=998244353;
int n,inv=499122177,f[N],dep[N],g[N],t[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u,int ff)
{
    dep[u]=dep[ff]+1;g[u]=INF;
    for(auto v:e[u]) if(v!=ff) dfs(v,u),g[u]=min(g[u],g[v]);
    for(auto v:e[u]) if(v!=ff&&g[u]==g[v]) t[u]=v;
    if(g[u]==INF) g[u]=dep[u];
}
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline void dfs1(int u,int ff,int w,int d)
{
    if(e[u].size()==1&&u!=1) return f[u]=0,void();
    f[u]=w*ksm(d,mod-2,mod)%mod;dfs1(t[u],u,w,d+1);
    f[u]=(f[u]+f[t[u]]*(mod+1-ksm(d,mod-2,mod)%mod))%mod;
    for(auto v:e[u]) if(v!=ff&&v!=t[u]) dfs1(v,u,f[u],2);
}
inline void solve()
{
    n=read();for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
    dfs(1,0);f[1]=1;dfs1(1,0,1,1);for(int i=1;i<=n;i++) print(f[i]),put(' '),e[i].clear();put('\n');
}
signed main()
{
    int T=1;
    T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：封禁用户 (赞：3)

记这棵树是一个以 $1$ 号点为根的有根树。这题首先需要得到的一个性质是：Alice 每次操作必须要往父亲方向走，Queen 每次操作一定要把 Alice 往远离父亲的方向拖。

为什么呢？首先，在一个非根节点，Alice 如果想活必须会经过自己父亲。如果自己获得了操作机会却往下走，还得再回来、往上走，依旧会经过父亲。于是，一个简单的结论出来了：

> Alice 的存活概率必然不高于在父亲节点的存活概率。

其次，Queen 知道了这个结论。由于 Queen 想要处决 Alice，那么轮到她操作的时候，不可能把 Alice 往父亲拖，因为这样只会增加 Alice 的存活概率。

这样，一个最基本的想法便出现了：

记 $f_i$ 为当前 Alice 在 $i$ 号点的生存概率，那么：

- 如果 $i=1$，则 $f_i=1$。

- 否则，如果 $i$ 是叶子，则 $f_i=0$。

- 再否则，设 $fa_{i}$ 为 $i$ 的父亲，$S_{i}$ 为 $i$ 的儿子构成的集合，则 $f_{i}=\frac{1}{2}f_{fa_{i}}+\frac{1}{2}\min\limits_{s\in S_{i}}f_{s}$——其中两个 $\frac{1}{2}$ 后面的式子分别表示 Alice 和 Queen 决策后 Alice 的胜率。

于是我们遇到了一个致命的问题：这个 $\min$ 拆不了了。

正在我们百思不得其解的时候，我们重温了前面的结论的一句话：

> Alice 每次操作必须要往父亲方向走。

我们又得到了灵感：如果 Alice 初始在 $i$ 号点，她要存活，首先要爬到 $fa_{i}$。如果没有爬到，那她就在 $i$ 号点的子树里面被处决了。爬到 $fa_{i}$ 后，状态就变成“Alice 在 $fa_{i}$ 号点”了。

我们设 $g_{i}$ 为 Alice 从 $i$ 号点出发，能够爬到 $fa_{i}$ 的概率。

- $i=1$ 下 $g_{i}$ 没有定义，我们也不用管它。

- 如果 $i$ 是叶子，则 $g_{i}=0$，因为 Alice 已经被处决了。

- 否则，如果当前是 Queen 的回合，那么 Queen 肯定会把 Alice 往 $g$ 最小的儿子拖。Alice 当前有 $\frac{1}{2}$ 的概率轮到她的回合，爬到父亲。除此之外，有 $\frac{1}{2}\min\limits_{s\in S_{i}}g_{s}$ 被 Queen 拖走，但是重新回到了 $i$，剩下的概率就是被拖走处决。自行用等比数列求和推推，发现 $g_{i}=\frac{\frac{1}{2}}{1-\frac{1}{2}\min\limits_{s\in S_{i}}g_{s}}=\frac{1}{2-\min\limits_{s\in S_{i}}g_{s}}$。

我们发现，现在可以使用一遍深搜求出每一个 $g$ 值，再使用一遍深搜求出答案。本着“期望分步走，一步一期望”的思想，$i$ 号点的胜率就是到根节点路上（不含根，含 $i$）的节点的所有 $g$ 值之积。

但真的有这么简单吗？

我们回去看了一眼输出精度——这不对啊，这题是模 $998244353$ 输出，那么怎么对一些分数求 $\min$？

万幸的是，我们及时观察到，任何一个 $g$ 值都可以表示成 $1-\frac{1}{X+1}$，其中 $X$ 是自然数。我们设 $h_i$ 满足 $g_{i}=1-\frac{1}{h_{i}+1}$，那么：

- 如果 $i$ 是叶子，则 $h_{i}=0$。

- 否则，$g_{i}=\frac{1}{2-\min\limits_{s\in S_{i}}g_{s}}=\frac{1}{2-\min\limits_{s\in S_{i}}(1-\frac{1}{h_{s}+1})}=\frac{1}{1+\max\limits_{s\in S_{i}}\frac{1}{h_{s}+1}}=\frac{1}{1+\frac{1}{1+\min\limits_{s\in S_{i}}h_{s}}}=1-\frac{1}{1+\min\limits_{s\in S_{i}}h_{s}}$，故 $h_{i}=1+\min\limits_{s\in S_{i}}h_s$。

于是，我们就打破了比较分数的障碍，在最初线性预处理逆元即可。时间复杂度 $O(\sum n)$，结束。

这题不看题解、从头想一遍确实挺有难度的，但看题解就失去那味了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T,n,ni[200005],dp[200005],ans[200005];
vector<int>mp[200005];
const int modp=998244353;

void dfs(int now,int fa){
	bool satis=0;
	for(auto nxt:mp[now]){
		if(nxt==fa)continue;
		satis=1;dfs(nxt,now);dp[now]=min(dp[now],dp[nxt]+1);
	}
	if(!satis)dp[now]=0;
}

void dfsEX(int now,int fa){
	for(auto nxt:mp[now]){
		if(nxt==fa)continue;
		ans[nxt]=ans[now]*dp[nxt]%modp*ni[dp[nxt]+1]%modp;
		dfsEX(nxt,now);
	}
}

signed main(){
	cin>>T;ni[1]=1;
	for(int i=2;i<=200004;i++)ni[i]=(modp-modp/i)*ni[modp%i]%modp;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			dp[i]=i==1?0:n+1;mp[i].clear();
		}
		for(int i=1;i<n;i++){
			int xx,yy;cin>>xx>>yy;
			mp[xx].push_back(yy);
			mp[yy].push_back(xx);
		}
		dfs(1,1);ans[1]=1;dfsEX(1,1);
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：DGME (赞：3)

对于官方题解做一点补充，对于一条长度为 $n + 1$ 的链而言，假设从左到右节点编号为 $1,\cdots,n + 1$ ，此时记 $dp_u$ 为从 $u$ 开始，能够获胜的概率，显然我们有：

$$
dp_u = \frac{1}{2}(dp_{u - 1} + dp_{u + 1})
$$

这可以导出，$dp$ 数组是一个等差数列，因此配合 $dp_1 = 1, dp_{n+1} = 0$ ，容易得到：

$$
dp_u = \frac{n + 1 - u}{n}
$$

换言之，如果仅仅考虑 $fa = u - 1$ 与 $u$ 的关系，我们得到：

$$
dp_u = dp_{fa} \times \frac{x}{x + 1}\quad x = n + 1 - u 
$$

这里 $x$ 为 $u$ 到其子树中最近的叶子的距离，按照这个思路来思考，我们也很自然地得到了从链推广到树的递推式。

[submission](https://codeforces.com/contest/2028/submission/291911519)

---

## 作者：revolutionary_oier (赞：1)

# CF2028E Alice's Adventures in the Rabbit Hole
## 关于结论的疑惑
这道题首先 Alice 应该向上跳是最优的这是比较显然的，但是很多题解说女皇让 Alice 向它子树内叶子结点离她最近的方向跳是最优的，对此我十分不理解为什么女皇不可以让 Alice 向上跳？很多题解都没有给这个的证明（莫非真理过于显然？），就连官解都没有解释。

## 关于结论的证明
我有一个非常粗略的证明。

对于一条链很显然 Alice 胜率是随着高度的降低而递增的。现在考虑其中在这条链的某一个节点处接入另一条链，假设交点是 $u$，$u$ 短链的儿子为 $v_1$ 长链的儿子为 $v_2$，如果，在 $v_2$ 处考虑向上跳，则用的是短链的贡献，但因为短链单独转移是有单调性的，所以往上跳 Alice 胜率增高（当然也因为 $2$ 人操作概率相等），违反了女皇的目的。所以女皇让 Alice 往子树内跳更优。
## 思路
接下来就非常的树形 dp 了。
- 状态定义： 定义 $f_u$ 表示为从 $u$ 出发 Alice 的胜利的概率，钦定 $fa_u$ 为 $u$ 的父亲节点编号，钦定 $pos_u$ 表示以 $u$ 为根子树，$u$ 向子树内叶子结点最浅的方向移动一步所到达 $u$ 儿子的节点编号。
- 状态初始化：$f_{root}=1,f_{leaf}=0$。
- 状态转移方程：$f_u=\frac{1}{2}(f_{pos_u}+f_{fa_u})$。

注意到这个转移方程非常的恶心——成环了，按照正常操作给他进行展开。

钦定 $v_1=pos_u,v2=pos_{v_1}$。
$$\begin{cases} f_u=\frac{1}{2}(f_{v_1}+f_{fa_u})& (1)\\ f_{v_1}=\frac{1}{2}(f_{v_2}+f_{u})&(2)\end{cases}$$

假设 $f_{fa_u}$ 已经被计算出来。

将 $(1)$ 代入 $(2)$，便可以得到一个 $v_1$ 只取决于 $v_2$ 的转移方程，只需要将这些系数记下来转移即可，树形 dp 加个记忆化便可以得到 DAG 的转移，时间复杂度: $O(n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int maxn=2e5+10;
const int mod=998244353;
int t,n,cnt,inv2;
int head[maxn],f[maxn],fat[maxn],dep[maxn],son[maxn],op[maxn];
bool is[maxn];
struct node{
    int v,nxt;
}e[maxn<<1];
struct vertex{
    int x,y,z;
}a[maxn];
inline int quick_pow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret*=x,ret%=mod;
        y>>=1;
        x*=x;
        x%=mod;
    }
    return ret;
}
inline void add(int u,int v){
    e[++cnt].v=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
inline void ipt(){
    cnt=0;
    dep[0]=mod;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)head[i]=0,f[i]=0,is[i]=false,son[i]=0,op[i]=0,dep[i]=0;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        add(u,v);
        add(v,u);
    }
}
inline void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    fat[u]=fa;
    bool flag=false;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa)continue;
        flag=true;
        dfs(v,u);
        if(dep[son[v]]<dep[son[u]]){
            son[u]=son[v];
            op[u]=v;
        }
    }
    if(!flag)son[u]=u;
}
inline void dp_init(){
    f[1]=1;
    is[1]=true;
    for(int i=2;i<=n;i++){
        if(son[i]==i)is[i]=true;
    }
}
inline void dp(int u,int fa){
    if(is[u])return ;
    a[op[u]].x=1;
    a[op[u]].y=(a[u].y*inv2)%mod;
    a[op[u]].z=inv2;
    a[op[u]].x=(1-(a[u].z*inv2)%mod+mod)%mod;
    int inv=quick_pow(a[op[u]].x,mod-2);
    a[op[u]].y=(a[op[u]].y*inv)%mod;
    a[op[u]].z=(a[op[u]].z*inv)%mod;
    a[op[u]].x=1;
    dp(op[u],u);
    f[u]=(a[u].y+(a[u].z*f[op[u]]))%mod;
    is[u]=true;
}
inline void dfs2(int u,int fa){
    if(!is[u]){
        a[u].x=1,a[u].y=(f[fa]*inv2)%mod,a[u].z=inv2;
        dp(u,fa);
    }
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa)continue;
        dfs2(v,u);
    }
}
inline void opt(){
    for(int i=1;i<=n;i++)printf("%lld ",f[i]);
    printf("\n");
}
signed main(){
    inv2=quick_pow(2,mod-2);
    // printf("inv2= %lld\n",inv2);
    scanf("%lld",&t);
    while(t--){
        ipt();
        dfs(1,1);
        // for(int i=1;i<=n;i++)printf("%lld ",op[i]);
        // printf("\n");
        dp_init();
        dfs2(1,1);
        opt();
    }
    return 0;
}
```

---

## 作者：ny_jerry2 (赞：1)

挺有意思的一道题。

设 $d(u)$ 表示在 $u$ 的儿子当中最靠近叶节点的儿子。显然这个东西可以直接搜索出来。

以下设 $v = d(u)$ 。

设 $f_u$ 表示 Alice 从 $u$ 爬到根的概率。  
分两种情况：

- 这次由她走。因为她想跑掉，所以她会选择更靠近根节点的点走，那她肯定是选父节点，则概率为 $f_{fa}$。
- 这次由女王走。因为女王想杀死她，所以肯定会将她拉到一个最靠近叶节点的位置，同时只能移动一步，所以这个点一定是 $v$，则概率为 $f_v$。

所以可以得出：
$$f_u = \frac{1}{2} (f_v + f_{fa})$$

乘以 $\frac{1}{2}$ 是因为两种情况要平摊 $1$ 的概率。

显然，这个东西有后效性无法转移，所以要让它变一下形式。

![推式子](https://cdn.luogu.com.cn/upload/image_hosting/gaiw4hma.png?x-oss-process=image/resize,m_lfit,h_4000,w_5000)

由此引发猜想：$f_u$ 可以表示成 $k_uf_{fa}$ 的形式，那我们尝试解一下。

有：
$$f_u = \frac{1}{2} (f_v+f_{fa})$$
$$2f_u = f_v+f_{fa}$$
$$2f_u = k_vf_u+f_{fa}$$
$$(2-k_v)f_u=f_{fa}$$
$$f_u = \frac{1}{2 - k_v}f_{fa}$$

$\therefore$ $k_u = \frac{1}{2 - k_v}$。

所以我们就只需要将 $k_u$ 递归求出，再递归求出 $f_u$ 就好了。

关于取模的话，用逆元求出就好了。

## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n;
const int N=5e5+10,mod=998244353;
int h[N],e[N],ne[N],idx,g[N],dep[N];
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
long long f[N],k[N];
int la;
void init(){
	for(int i=1;i<=la;i++){
		h[i]=-1,f[i]=k[i]=g[i]=dep[i]=0;
	}
	idx=0;
}
long long pow(long long a,int b){
	long long res=1;
	while(b){
		if(b&1){
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
long long ny(long long a,long long b){
	return a*pow(b,mod-2)%mod;
}
void dfs1(int u,int fa){
	dep[u]=2e9;
	int cnt=0;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa){
			continue;
		}
		cnt++;
		dfs1(j,u);
		dep[u]=min(dep[u],dep[j]+1);
		if(dep[j]+1==dep[u]){
			g[u]=j;
		}
	}
	if(!cnt){
		dep[u]=0;
	}
}
void dfs2(int u,int fa){
	int cnt=0;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa){
			continue;
		}
		cnt++;
		dfs2(j,u);
	}
	if(cnt){
		int v=g[u];
		k[u]=ny(1ll,(2-k[v]+mod)%mod);
	}
}
void dfs3(int u,int fa){
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa){
			continue;
		}
		f[j]=k[j]*f[u]%mod;
		dfs3(j,u);
	}
}
int main(){
	int t;
	cin>>t;
	la=N-1;
	while(t--){
		init();
		scanf("%d",&n);
		for(int i=1;i<n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			add(a,b),add(b,a);
		}
		dfs1(1,-1);
		dfs2(1,-1);
		f[1]=1ll;
		dfs3(1,-1);
		for(int i=1;i<=n;i++){
			printf("%lld ",f[i]);
		}
		printf("\n");
		la=n;
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

短链剖分/se/se

场上被 B 硬控了，快 1h 的时候还是高贵的一题选手，但是最后 $20$ 秒切这题翻盘啦！[CodeForces Hot News](https://codeforces.com/bestRatingChanges/15703826) 今天发现忘记补题解了，于是来补一篇。

首先考虑对于每一个结点 $i$ 对答案的贡献：

+ 若 $i$ 是根节点则 Alice 已经获胜。
+ 若 $i$ 是叶子结点则女王已经获胜。
+ 否则，有 $\frac{1}{2}$ 的概率 Alice 会往父亲结点移动，有 $\frac{1}{2}$ 的概率女王会让 Alice 向某一个儿子结点移动。

那么设 $f_i$ 表示若 Alice 在 $i$ 点时获胜的概率。那么令 $j$ 表示 $i$ 的儿子，$F_i$ 表示 $i$ 的父亲结点，且 $i$ 同时不是根和叶子结点，则有：

$$
f_i=\frac{f_{F_i}+\min f_j}{2}
$$

然后高兴的发现这个转移带环。~~于是弃掉。~~

考虑换一个思路。先考虑一些特殊情况。如一条 $1\sim n$ 的树，有且仅有 $i$ 到 $i+1$ 存在树边。此时显然 Alice 只会往父亲方向走，女王只会让 Alice 往儿子方向走。现在假设 Alice 位于点 $x$，则只需计算 Alice 获胜的概率。~~显然我不会算~~，所以大眼观察样例得到答案为 $\frac{n-i}{n-1}$。

但是给定的是一棵树，于是考虑把树剖成若干条链。考虑女王为了让 Alice 被拖到叶子结点所需的路程尽量的大，肯定会往距离当前结点最近且不需要往父亲结点的叶子结点移动。于是考虑维护 $g_i$ 表示 $i$ 子树内距离 $i$ 结点最近的叶子结点，即若 Alice 当前在 $i$ 那么女王每一次都会使 Alice 向 $g_i$ 靠近一步。因此考虑类似于长链剖分（这里貌似是短剖？）的思路将树剖分为若干条链，每一次直接在链上转移式子。于是考虑让 Alice 跳短链，每一次计算 Alice 跳过短链顶端的概率和在短链顶端的父亲结点时，可以跳到根节点的概率，将她们相乘就是答案。每一次递归处理短链即可求出答案。

但是问题是树的短链并不像重链和长链一样，有着优美的性质例如从树上任意一个点往上跳到根节点，只会跳 $\log n$ 条不同的重链或 $\sqrt n$ 条不同的长链，要跳短链的次数是 $O(n)$ 级别的（虽然肯定不满）。于是考虑回归一开始的 dp 思想，设 $f_i$ 表示若当前 Alice 在 $i$ 结点能够跳到根节点的概率，显然有 $f_1=1$，$f_k=0$（$k$ 是树的叶子结点）。对于每一个结点 $i$，令其所在短链的顶端的结点为 $\text{top}_i$，则只需要对树做一遍记忆化搜索从 $F_{\text{top}_i}$ 结点为 $f_i$ 结点计算贡献，即可做到 $O(n\log n)$ 计算答案（需要计算逆元）。

能不能不用记忆化搜索？显然从树根开始 dfs 搜索每一个叶子结点更新答案即可。

可不可以做到 $O(n)$？线性处理 $1\sim n$ 的逆元即可。（但是我没写）

代码。因为最后 $15$ min 才开这个题，最后不到 $7$ min 才开始写，所以写的十分混乱。

```cpp
vector<int> z[N];
int f[N], down[N], deg[N], n, xia[N], sh[N], top[N], dep[N];
void dfs(int u, int fa) {
    if (deg[u] == 1 && u != 1) {
        down[u] = 0;
    } else {
        down[u] = 1e18;
        for (auto &v : z[u]) {
            if (v != fa) {
                dfs(v, u);
                down[u] = min(down[u], down[v] + 1);
                if (down[v] + 1 == down[u]) {
                    xia[u] = v;
                }
            }
        }
    }
}
void dfs2(int u, int fa, int up = 1) {
    top[u] = up;
    dep[u] = dep[fa] + 1;
    for (auto &v : z[u]) {
        if (v != fa) {
            if (v == xia[u]) {
                f[v] = f[u] + 1;
                dfs2(v, u, up);
            } else {
                f[v] = 1;
                dfs2(v, u, u);
            }
        }
    }
}
// f[i]: i 往上路径长度
// down[i]: i 往下路径长度
void dfs3(int u, int fa) {
    sh[u] = sh[top[u]] * ksm(f[u] + down[u], mod - 2, mod) % mod * down[u] % mod;
    if (u != 1 && deg[u] == 1) {
        sh[u] = 0;
        return;
    }
    for (auto &v : z[u]) {
        if (v != fa) {
            dfs3(v, u);
        }
    }
}
void run() {
    int T = read();
    while (T--) {
        n = read();
        for (int i = 1; i <= n; ++i) {
            z[i].clear();
            deg[i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int x = read(), y = read();
            z[x].eb(y), z[y].eb(x);
            ++deg[x], ++deg[y];
        }
        dfs(1, 0);
        dfs2(1, 0);
        sh[1] = 1;
        dfs3(1, 0);
        for (int i = 1; i <= n; ++i) {
            cout << sh[i] << ' ';
        }
        cout << '\n';
    }
}
```

---

