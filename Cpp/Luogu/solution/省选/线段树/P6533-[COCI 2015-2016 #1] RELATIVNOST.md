# [COCI 2015/2016 #1] RELATIVNOST

## 题目描述

您是一位计数大师，有一天您的朋友 Luka 出了一道问题来刁难您。

Luka 是一位勤劳的画家，他的画很好，所以会有 $n$ 个人来买他的画。

画分两种，黑白画与彩色画。

Luka 十分勤劳，所以他有无穷多的画。

Luka 讨厌出售黑白画，所以他希望至少有 $c$ 个人会买走一张彩色画。

第 $i$ 个人会至多购买 $a_i$ 张彩色画，$b_i$ 张黑白画，且它们会至少购买一幅画。

但是，客户们只能单独购买彩色画或黑白画。

客户们会不断改变 $a_i$ 与 $b_i$，这种改变会持续 $q$ 次。

客户以 $1\sim n$ 编号。

您需要求出在每次改变之后，Luka 会有几种方案满足所有需求。

为了防止输出太大，Luka 只需要您告诉他方案数 $\bmod\ 10^4+7$ 的值。

## 说明/提示

#### 样例 1 说明
第一次改变后，我们只有唯一的一种方案，就是向两位用户都出售一张彩色画。

#### 数据范围及限制
- 对于 $30\%$ 的数据，保证 $n,q\le 10^3$。
- 对于 $100\%$ 的数据，保证 $1\le n,q\le 10^5$，$1\le c\le 20$，$1\le a_i,b_i,a_{p_i},b_{p_i}\le 10^9$，$1\le p_i\le n$。

#### 说明
**本题满分 $140$ 分。**

本题译自 [Croatian Open Competition in Informatics 2015/2016](https://hsin.hr/coci/archive/2015_2016) [Contest #1](https://hsin.hr/coci/archive/2015_2016/contest1_tasks.pdf) T5 RELATIVNOST。

## 样例 #1

### 输入

```
2 2
1 1
1 1
1
1 1 1 
```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2
1 2
2 3
2
1 2 2
2 2 2```

### 输出

```
4
4```

## 样例 #3

### 输入

```
4 2
1 2 3 4
1 2 3 4
1
4 1 1
```

### 输出

```
66```

# 题解

## 作者：if_OF (赞：31)

# P6533 RELATIVNOST 题解

## 题目

[洛谷 P6533 RELATIVNOST](https://www.luogu.com.cn/problem/P6533)

## 分析

题目中要求至少有 $c$ 人买走至少一张彩色画，那暴力的思路就是选取 $i  (c\leq i\leq n)$ 到 $n$ 个人，这 $i$ 个人满足题意的购买方案数就是他们的 $a$ 乘上剩下的人的 $b$。

我们注意到 $c$ 的数据范围小于 $20$，于是就可以考虑使用动态规划解决问题。

又因为对于每组数据有 $q$ 组改变，普通的动态规划会T掉，所以我们使用线段树进行优化。

## 思路

对于线段树上的每一个节点 $tree[i]$，我们设 $tree[i].dp[j]$ 表示 $tree[i].l$ 到 $tree[i].r$ 个人（即该节点覆盖的区间）中有 $j$ 个人购买了至少一幅彩色画的方案数，根据乘法原理，每个节点购买至少 $i+j$ 张彩色画方案数就等于该节点的左子树对应的人数购买至少 $i$ 幅彩色画的方案数乘以该节点的所有右子树对应的人数购买至少 $j$ 幅彩色画的方案数，于是我们就可以推出转移方程：
$$
tree[id].dp[i+j]=\sum_{i=0}^{c}{\sum_{j=0}^{c}{tree[id\cdot 2].dp[i]\cdot tree[id\cdot 2+1].dp[j]}}
$$
这一部分可能有点绕，如果不清楚的话建议~~感性理解~~结合代码看一看（在 `update` 函数里面）。

对于有 $c$ 个人以上的人购买了彩色画的情况，我们都将其存到 $dp[c]$ 里面，所以代码中上面式子里面的 $i+j$ 应该换成 $\min(i+j,c)$。

而对于线段树的每个叶子节点，即单独一个人，他购买了彩色画的方案数就是他最多会买的彩色画的数量（即 $a[i]$），他购买了黑白画的方案数就是他最多会购买的黑白画的数量（即 $b[i]$），于是我们就可以得到以下的式子：
$$
tree[i].dp[0]=b[i],tree[i].dp[1]=a[i]
$$
对于每一个人 $a_i$ 和 $b_i$ 的改变，我们就将线段树更新一下就好了，最后总共的情况数就是线段树根节点的 $dp[c]$ 的值（代表所有顾客中至少有 $c$ 人购买彩色画的方案数）。

更详细的实现步骤详见代码注释。

## 代码

```cpp
#pragma gcc optimize(2)//不开O2会T最后一个点
#include<iostream>
using namespace std;
const int MAXN=100005,MOD=10007;
int a[MAXN],b[MAXN],c,n;//对应题目中的a,b,c,n
struct Node
{
	int l,r,dp[21];
}tree[MAXN*4];//因为这道题的空间限制只有32MB，有些OJ可能过不了，但是洛谷上这么写还是过了
inline void update(int id)//更新一个节点的dp数组
{
	for(register int i=0;i<=c;i++)
	{
		tree[id].dp[i]=0;//每次更新一个节点时先将其清零
	}
	for(register int i=0;i<=c;i++)
	{
		for(register int j=0;j<=c;j++)
		{
			tree[id].dp[min(i+j,c)]=((tree[id*2].dp[i]*tree[id*2+1].dp[j])%MOD+tree[id].dp[min(i+j,c)])%MOD;
            //这行代码比较长，其实去掉取模就是tree[id].dp[min(i+j,c)]+=tree[id*2].dp[i]*tree[id*2+1].dp[j];
            //为啥要用+=？举个例子，左子树两个右子树两个人买彩色画跟左子树一个右子树三个人买彩色画
            //都会计算在有四个人购买彩色画的方案数内。
		}
	}
}
void build(int l,int r,int id)//建树操作
{
	tree[id].l=l,tree[id].r=r;
	if(l==r)//如果是叶子结点
	{
		tree[id].dp[0]=b[l],tree[id].dp[1]=a[l];//那么按照上文所说的修改它的dp[0]和dp[1]
		return;
	}
	build(l,(l+r)/2,id*2);
	build((l+r)/2+1,r,id*2+1);
	update(id);//当该节点的左儿子和右儿子建立完成之后更新该节点的dp值
}
void change(int id,int A,int B,int fxid)//单点修改操作
{//id是当前节点的下标，fxid是要修改的节点的下标
	if(tree[id].l==tree[id].r)
	{
		tree[id].dp[0]=B,tree[id].dp[1]=A;
		return;
	}
	if(fxid<=((tree[id].r+tree[id].l)/2))
		change(id*2,A,B,fxid);
	if(fxid> ((tree[id].r+tree[id].l)/2))
		change(id*2+1,A,B,fxid);
	update(id);//跟上面建树操作一个道理，左右儿子修改完之后更新
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>c;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]%=MOD;//读入之后先取模
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		b[i]%=MOD;
	}
	build(1,n,1);//建树
	int q,A,B,changeid;
	cin>>q;
	while(q--)
	{
		cin>>changeid>>A>>B;
		A%=MOD,B%=MOD;
		change(1,A,B,changeid);
		cout<<tree[1].dp[c]<<endl;
        //tree[1].dp[c]就是所有人至少买了c张及以上的彩色画的方案数
	}
}
```

## 更新

- `2023/12/21` 感谢 [@linyuhuai](https://www.luogu.com.cn/user/505244) 的提醒，修正了一个错误。


---

## 作者：JK_LOVER (赞：9)

## 分析
我们可以发现， $C$ 只与选的人的个数有关，因为 $(1\le a_i,b_i\le 10^9)$ ，所以方案数目是由 $a_i,b_i$ 大小决定的 。如果考虑 $dp$，我们发现对于修改操作我们很难处理 $O(nq)$ ，考虑用线段树优化。则转移方程为：
$$
dp[u][i+j] = dp[lson_u][i] \times dp[rson_u][j]
$$
对于叶子节点有：
$$
dp[u][1] = a[u],dp[u][0] = b[u]
$$
这样我们就可以在 $O(c^2\log n)$ 的复杂度内完成单次操作 。
## 注意
这道题对于空间的要求简直丧心病狂 $32MB$ ，对于线段树就只能采用动态开点了，而且不能开 $long long$ 所以在相乘的时候一定要转类型。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
const int N = 100020;
const int mod = 10007;
int n,c,A[N],B[N],size = 0,rt;
struct T{int dp[21],l,r;}t[N<<1];
void update(int u)
{
	for(int i = 0;i <= c;i++) t[u].dp[i] = 0;
	for(int i = 0;i <= c;i++)
	for(int j = 0;j <= c;j++)
	{
		t[u].dp[min(i+j,c)] += (1LL*t[t[u].l].dp[i]*t[t[u].r].dp[j])%mod;
		t[u].dp[min(i+j,c)] %= mod;
	}
}

int build(int u,int l,int r)
{
	if(!u) u=++size;
	if(l == r)
	{
		t[u].dp[1] = A[l];
		t[u].dp[0] = B[l];
		return u;
	}
	int mid = l+r>>1;
	t[u].l = build(t[u].l,l,mid);
	t[u].r = build(t[u].r,mid+1,r);
	update(u);
	return u;
}
void change(int u,int l,int r,int key,int a,int b)
{
	if(l==r)
	{
		t[u].dp[1] = a;
		t[u].dp[0] = b;
		return;
	}
	int mid = l+r>>1;
	if(key<=mid) change(t[u].l,l,mid,key,a,b);
	else change(t[u].r,mid+1,r,key,a,b);
	update(u);
}
signed main()
{
	n = read();c = read();
	for(int i = 1;i <= n;i++) A[i] = read();
	for(int i = 1;i <= n;i++) B[i] = read();
	rt = build(rt,1,n);
	int q = read();
	while(q--)
	{
		int p = read(),a = read(),b = read();
		change(rt,1,n,p,a,b);
		printf("%d\n",t[1].dp[c]); 
	}
}
```
[博客地址](https://www.luogu.com.cn/blog/xzc/solution-p6533)

---

## 作者：FDsama (赞：8)

# [P6533 RELATIVNOST 题解](https://www.luogu.com.cn/problem/P6533)  
### 前情提要
本人在最近的模拟赛中遇到了一道这道题的加强版。  
然而题解区都是时间复杂度 $\mathcal O(nc^2+qc^2\log n)$ 的线段树上泛化物品合并的解法，无法通过加强版。  
这里提供两种更好的时空复杂度的解法。  
注意：第二种解法因为模数原因不能通过本题，但是有 $\mathcal O((n+q)c+q\log \text{Mod})$ 的理论最优复杂度。

### 题目简述
>给定 $n$ 个物品，若选择这个物品有 $a_i$ 种方案，不选择这个物品有 $b_i$ 种方案。  
>给你 $q$ 次修改，每次修改形如 $(i,a,b)$，指把 $a_i$ 改为 $a$，$b_i$ 改为 $b$。  
>对于每次修改结束后，统计至少选 $c$ 个物品的方案数（对 $\text{Mod}$ 取模）。   
>注意：修改之间**不是独立**的。  
>    
>原题数据范围：$1\le n,q \le 10^5，1\le c \le 20，1 \le a_i,b_i\le 10^9，\text{Mod}=10^4+7$。  
>本题加强版数据范围：$1\le n,q \le 10^6，1\le c \le 50，1 \le a_i,b_i\le 10^8，\text{Mod}=10^9+7$。

### 推导
首先来做一下两个方法共同的推导：  
先考虑无修改的**静态问题**：  
发现可以用一种类似于**背包**的 DP 解决。  
这里设 $dp_{i,j}$ 表示考虑到前 $i$ 个物品，选择了 $j$ 个物品的方案数。  
转移式显然为：$dp_{i,j}=dp_{i-1,j-1}\times a_i+dp_{i-1,j}\times b_i$。  
特别地，有：$dp_{i,0}=dp_{i-1,0}\times b_i$。  
初始值为：$dp_{0,0}=1$。

考虑怎样优化时间和空间。  
首先可以用滚动数组压掉一维。  
由于 $c$ 是固定的，考虑**正难则反**，用总方案数减去不合法方案数。  
显然，总方案数为 $\prod (a_i+b_i)$。    
那么答案就是：$\prod (a_i+b_i)-\sum\limits_{j=0}^{c-1}f_j$。  
注意：这里我们记 $f_j=dp_{n,j}$，发现只需要计算并保留 $0$ 到 $c-1$ 位即可。  
那么这里我们就能做到 $\mathcal O(nc)$ 地解决静态问题。

这里我们可以注意到：  
**合并物品的顺序并不会影响到最终的答案**。  
于是我们就能想到动态问题的做法。  

### 法一：线段树分治
（这里默认大家已经会线段树分治，不再赘述，不了解地可自行搜索）。 

修改可以离线，能解决静态问题，合并顺序不影响结果，于是我们考虑线段树分治。  
我们离线出每个物品 $(a,b)$ 的存在时间范围，在线段树上分为至多 $\mathcal O(\log q)$ 个区间，把这个物品插入这些区间。  
顺序遍历线段树，把这个物品合并到当前答案中即可。  
由于每个物品至多被合并 $\mathcal O(\log q)$ 次，而单次合并的复杂是 $\mathcal O(c)$ 的。  
且我们每次只保存遍历的链上的答案（实现的时候写了一个结构体），答案所占用的空间是 $\mathcal O(c\log q)$ 的。  
所以总的时间复杂度为 $\mathcal O((n+q)c\log q)$，空间复杂度为 $\mathcal O((n+q+c)\log q)$。

代码轻松跑到了 rk1：
```c++
#include <bits/stdc++.h>
using namespace std;

class FD {
private:
    inline static int Read() {
        int r = 0, f = 0, c = getchar();
        while((c < '0' || c > '9') && ~c) f |= c == '-', c = getchar();
        while(c >= '0' && c <= '9') r = (r << 1) + (r << 3) + (c ^ 48), c = getchar();
        return f ? -r : r;
    }

    typedef long long ll;
    static constexpr int AwA = 1e5 + 10;
    static constexpr int QwQ = 21;
    static constexpr int Mod = 1e4 + 7;

    struct Ans {
        ll tot;
        ll f[QwQ];
        Ans(int m) {
            tot = 1;
            memset(f, 0, sizeof(ll) * m);
            f[0] = 1;
        }
        inline void Update(pair<int, int> k, int m) {
            vector<ll> tmp(m);
            for(int i = m - 1; i; i--) tmp[i] = (f[i] * k.second + f[i - 1] * k.first) % Mod;
            tmp[0] = f[0] * k.second % Mod;
            for(int i = 0; i < m; i++) f[i] = tmp[i];
            tot = tot * (k.first + k.second) % Mod;
        }
    };

    int n, m, Q;
    pair<int, int> p[AwA << 1];
    vector<int> sgtr[AwA << 2];
    int lst[AwA], cur[AwA];
    ll ans[AwA];

    void Cover(int u, int l, int r, int lx, int rx, int v) {
        if(lx <= l && r <= rx) return sgtr[u].push_back(v);
        int mid = (l + r) >> 1;
        if(lx <= mid) Cover(u << 1, l, mid, lx, rx, v);
        if(mid < rx) Cover(u << 1 | 1, mid + 1, r, lx, rx, v);
    }

    void Dfs(int u, int l, int r, Ans st) {
        for(auto k : sgtr[u]) st.Update(p[k], m);
        if(l == r) {
            ans[l] = st.tot;
            for(int i = 0; i < m; i++) ans[l] -= st.f[i];
            ans[l] = (ans[l] % Mod + Mod) % Mod;
            return;
        }
        int mid = (l + r) >> 1;
        Dfs(u << 1, l, mid, st);
        Dfs(u << 1 | 1, mid + 1, r, st);
    }
public:
    inline void Main() {
        n = Read(), m = Read();
        for(int i = 1; i <= n; i++) p[i].first = Read();
        for(int i = 1; i <= n; i++) p[i].second = Read();
        for(int i = 1; i <= n; i++) lst[i] = 1, cur[i] = i;
        Q = Read();
        for(int i = 1, x, a, b; i <= Q; i++) {
            x = Read(), a = Read(), b = Read();
            p[i + n] = { a, b };
            if(lst[x] < i) Cover(1, 1, Q, lst[x], i - 1, cur[x]);
            lst[x] = i, cur[x] = i + n;
        }
        for(int i = 1; i <= n; i++) Cover(1, 1, Q, lst[i], Q, cur[i]);

        Dfs(1, 1, Q, Ans(m));
        for(int i = 1; i <= Q; i++) printf("%lld\n", ans[i]);
    }
} Fd;

int main() {
    Fd.Main();
    return 0;
}
```

### 法二：可逆背包
修改一个物品可看作先删除这个物品，再插入一个新的物品。  
由于物品合并顺序不影响结果，我们可以考虑可逆背包。

所谓的可逆背包，就是想办法使当前答案状态变为删去物品的答案状态。  
由于物品合并顺序不影响结果，我们可以把当前要删除的物品当作最后一个物品，那么我们考虑一个物品的贡献。

这里设当前答案数组为 $f_j$，删去该物品后答案数组为 $g_j$ ，则有：  
$f_j=g_{j-1}\times a+g_j\times b,f_0=g_0\times b$。  
则：  
$g_j=(f_j-g_{j-1}\times a)\times b^{-1},g_0=f_0 \times b^{-1}$。  
令总方案数为 $tot$，则有删去物品后总方案数为 $tot\times (a+b)^{-1}$。

那么只要能够求出逆元，我们就可以在 $\mathcal O(c)$ 的时间内删除该物品的贡献，然后再在同样的时间复杂度内插入新的物品。  
总时间复杂度为 $\mathcal O((n+q)c)$，空间复杂度为 $\mathcal O(n+c)$。

但是由于模数较小，不能计算逆元，所以无法通过本题。  
通过加强版的代码：
```c++
#include <bits/stdc++.h>
using namespace std;

class FD {
private:
    inline static int Read() {
        int r = 0, f = 0, c = getchar();
        while((c < '0' || c > '9') && ~c) f |= c == '-', c = getchar();
        while(c >= '0' && c <= '9') r = (r << 1) + (r << 3) + (c ^ 48), c = getchar();
        return f ? -r : r;
    }

    typedef long long ll;
    static constexpr int AwA = 1e6 + 10;
    static constexpr int QwQ = 51;
    static constexpr int Mod = 1e9 + 7;

    inline static ll Pow(ll a, ll b) {
        ll res = 1;
        while(b) {
            if(b & 1) res = res * a % Mod;
            a = a * a % Mod;
            b >>= 1;
        }
        return res;
    }

    int n, m, Q;
    int a[AwA], b[AwA];
    ll f[QwQ], g[QwQ], tot = 1;
public:
    inline void Main() {
        n = Read(), m = Read();
        for(int i = 1; i <= n; i++) a[i] = Read();
        for(int i = 1; i <= n; i++) b[i] = Read();

        f[0] = 1;
        for(int i = 1, j; i <= n; i++) {
            tot = (tot * (a[i] + b[i])) % Mod;
            memcpy(g, f, sizeof(ll) * m);
            f[0] = g[0] * b[i] % Mod;
            for(j = 1; j < m; j++) f[j] = (g[j - 1] * a[i] + g[j] * b[i]) % Mod;
        }

        Q = Read();
        for(int i = 1, x, j; i <= Q; i++) {
            x = Read();
            ll ib = Pow(b[x], Mod - 2);
            tot = tot * Pow(a[x] + b[x], Mod - 2) % Mod;
            g[0] = f[0] * ib % Mod;
            for(j = 1; j < m; j++) g[j] = (((f[j] - g[j - 1] * a[x]) % Mod + Mod) * ib) % Mod;

            a[x] = Read() % Mod, b[x] = Read() % Mod;
            tot = tot * (a[x] + b[x]) % Mod;
            f[0] = g[0] * b[x] % Mod;
            for(j = 1; j < m; j++) f[j] = (g[j - 1] * a[x] + g[j] * b[x]) % Mod;

            ll ans = tot;
            for(int j = 0; j < m; j++) ans = (ans - f[j] + Mod) % Mod;
            printf("%lld\n", ans);
        }
    }
} Fd;

int main() {
    Fd.Main();
    return 0;
}
```

---

## 作者：XuYueming (赞：5)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P6533)。

这道题有很多做法，但是模拟赛寄了，故记之。

**Update on 2024.7.23**

修复了一处时间复杂度的笔误。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18315964)。

## 题意简述

给你两个长为 $n$ 的序列 $A$ 和 $B$，和一个常数 $c \leq 20$，有 $q$ 次修改。每次修改后求：

$$
\large \sum _ {S \subseteq \lbrace i \rbrace _ {i = 1} ^ {n} \land |S| \geq c} \prod _ {x \in S} A_x \prod _ {x \not \in S} B_x
$$

当然，对 $10^4 + 7$ 取模。

## 题目分析

### 法 $1$：线段树

先来考虑部分分。很明显的 DP，记 $f[i][j]$ 表示在前 $i$ 个中，选出了 $j$ 个的乘积。转移很朴素，答案就是 $\sum \limits _ {i = c} ^ {n} f[n][i]$。发现对于本题，$j \geq c$ 的状态意义相同，都表示满足了要求。所以不妨将状态压缩一下。可以得到如下转移方程：

$$
f[i][j] = 
\begin{cases}
f[i - 1][j] \times B_i & \text{ if } j = 0  \\
f[i - 1][j] \times B_i + f[i - 1][j - 1] \times A_i & \text{ if } 0 < j < c\\
f[i - 1][j] \times (A_i + B_i) + f[i - 1][j - 1] \times A_i  & \text{ if } j = c
\end{cases}
$$

可以得到 $30 \%$ 的部分分。考虑优化。这一看就矩阵啊，于是用上线段树优化矩乘，对于一个 $i$，它的转移如下：

$$
\begin{bmatrix}
f_0 & f_1 & \cdots & f_{c - 1} & f_c
\end{bmatrix}

\begin{bmatrix}
B_i    & A_i    & 0      & \cdots & 0   & 0         \\
0      & B_i    & A_i    & \cdots & 0   & 0         \\
0      & 0      & B_i    & \cdots & 0   & 0         \\
\vdots & \vdots & \vdots & \ddots & A_i & 0         \\
0      & 0      & 0      & 0      & B_i & A_i       \\
0      & 0      & 0      & 0      & 0   & A_i + B_i
\end{bmatrix}
$$

可是，$\Theta(c ^ 3)$ 的复杂度怎么都接受不了啊，所以考虑换一个方向思考。

我们发现，对于一个位置的 $(A_i, B_i)$，它是什么时候加到状态里的不会影响最终结果。换句话说，我们 DP 的顺序没有要求。而且发现两个状态合并也很容易。比如合并 $a$ 和 $b$ 到 $f$ 中，分别用 $i$ 和 $j$ 枚举 $a$ 和 $b$ 的状态，表示一个里面选出了 $i$ 个位置，另一个里面选出了 $j$ 个位置，对 $f$ 的贡献可以表示为 $f[\min \lbrace c, i + j \rbrace] \gets f[\min \lbrace c, i + j \rbrace] + a_i \times b_j$。

发现，合并两个区间，就是线段树的工作。用个线段树维护，单点修改，查询根节点的 $f[c]$。~~果然，学矩阵学傻了。~~

时间复杂度：$\Theta(c^2 (n + q \log n))$。

### 法 $2$：线段树分治

结合法 $1$ 的物品添加顺序不会影响最终结果，并且问题可离线，每个物品出现的时间在时间轴上是连续的一段区间，添加物品很容易，想到线段树分治。没什么好说的了……剩下的就是板子了。

由于每次添加单个物品是 $\Theta(c)$ 的，时间复杂度：$\Theta((n + q) c \log q)$。

### 法 $3$：撤销背包

既然物品添加的顺序无关，如果我们想要修改某一个物品，那么把它看做是最后一个添加到状态里的，然后撤销，并增加修改后的物品。至于如何撤销，我们记添加 $(a, b)$ 物品前 DP 状态是 $g$，添加后是 $f$，根据我们上文提到的转移方程：

$$
f[j] = 
\begin{cases}
g[j] \times b & \text{ if } j = 0  \\
g[j] \times b + g[j - 1] \times a & \text{ if } 0 < j < c\\
g[j] \times (a + b) + g[j - 1] \times a  & \text{ if } j = c
\end{cases}
$$

移项移一下，得：

$$
g[j] = 
\begin{cases}
f[j] \times b ^ {-1} & \text{ if } j = 0  \\
(f[j] - g[j - 1] \times a) \times b ^ {-1} & \text{ if } 0 < j < c  \\
(f[j] - g[j - 1] \times a) \times (a + b) ^ {-1} & \text{ if } j = c
\end{cases}
$$

然而，如果 $b$ 或 $a + b$ 没有逆元，即 $b \bmod 10^4 + 7 = 0$ 或 $(a + b) \bmod 10^4 + 7 = 0$ 时，我们无法撤销。怎么办呢？

首先，讨论两个东西太恶心了，考虑转化一下，之保留一个可能不存在逆元的数。

发现，$b$ 是逃不掉的，而 $a + b$ 是由于我们规定了大于等于 $c$ 的看做相同。那这时候，为什么不能重新规定，只用计算恰好 $< c$ 的状态，再用总方案数 $\prod A_i + B_i$ 减去 $\sum \limits _ {i < c} f[i]$ 呢？转移方程变为了：

$$
f[j] = 
\begin{cases}
g[j] \times b & \text{ if } j = 0  \\
g[j] \times b + g[j - 1] \times a & \text{ if } 0 < j < c\\
\end{cases}
$$

即，少了最后一个 $j = c$ 的转移。同理，移项移一下，得：

$$
g[j] = 
\begin{cases}
f[j] \times b ^ {-1} & \text{ if } j = 0  \\
(f[j] - g[j - 1] \times a) \times b ^ {-1} & \text{ if } 0 < j < c  \\
\end{cases}
$$

现在，我们只要考虑 $b \bmod 10^4 + 7 = 0$ 的情况。发现如果有很多 $b$ 都在模意义下为 $0$，转移后的状态会全是 $0$，此时，在继续转移下去不会变化。具体地，这个临界值是 $c$，即如果有超过 $c$ 个物品的 $b$ 在模意义下为 $0$，我们计算的 $\sum \limits _ {i < c} f[i] = 0$。而 $c$ 又很小，我们完全可以在查询前暴力添加到状态中。所以，我们可以尝试用 `multiset<>` 来记录所有 $b \bmod 10^4 + 7 = 0$ 的物品。

至于 $\prod A_i + B_i$ 的撤销会涉及到 $A_i + B_i$ 没有逆元，这时候，可以用一个 `cnt` 记录有多少满足的，以及用 `tot` 记录除了这些的乘积。这样删除的时候，只需要 $cnt \gets cnt - 1$，而查询的时候，如果存在一个 $(A_i + B_i) \bmod 10^4 + 7 = 0$，我们让总方案数设为 $0$，反之设为 $tot$ 即可。

时间复杂度：$\Theta(nc\log n + qc^2\log n)$。实际上界很松。

## 代码

[法 $1$：线段树](https://www.luogu.com.cn/paste/zu45busa)。

[法 $2$：线段树分治](https://www.luogu.com.cn/paste/unxc4vcs)。

### 法 $3$：撤销背包

优化了取模，[超过了](https://www.luogu.com.cn/record/167758778)原来的 rank1。

```cpp
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <cstring>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;

namespace ModInt {
	using mint = short;
	using sint = int;
	
	constexpr const mint mod = 1e4 + 7;

	constexpr inline mint add(const mint a, const mint b) {
		return a + b >= mod ? a + b - mod : a + b;
	}

	constexpr inline mint sub(const mint a, const mint b) {
		return a - b < 0 ? a - b + mod : a - b;
	}

	constexpr inline mint mul(const mint a, const mint b) {
		return (sint(a)) * (sint(b)) % mod;
	}

	constexpr inline mint add(const mint a) { return a; }
	constexpr inline mint mul(const mint a) { return a; }

	template <typename... Types>
	constexpr inline mint add(const mint a, const Types... b) {
		return add(a, add(b...));
	}

	template <typename... Types>
	constexpr inline mint mul(const mint a, const Types... b) {
		return mul(a, mul(b...));
	}
	
	template <typename... Types>
	inline mint& toadd(mint &a, Types... b) {
		return a = add(a, b...);
	}
	
	template <typename... Types>
	inline mint& tomul(mint &a, Types... b) {
		return a = mul(a, b...);
	}
	
	inline mint& tosub(mint &a, const mint b) {
		return a = sub(a, b);
	}

	constexpr inline mint pow(const mint a, const mint p) {
		mint res = 1, base = a, b = p;
		while (b){
			if (b & 1) tomul(res, base);
			tomul(base, base), b >>= 1;
		}
		return res;
	}

	constexpr inline mint inv(const mint a) {
		return pow(a, mod - 2);
	}
}

using namespace ModInt;

namespace Fast{
	// fread(buf, 1, MAX, stdin)
	// fwrite(obuf, 1, o - obuf, stdout)
	
	constexpr const int MAX = 1 << 24, yzh_i_love_you = 1314520736;
	
	char buf[MAX], *p = buf, obuf[MAX], *o = obuf;
	
	#ifdef XuYueming
	# define fread(buf, size, n, file)
	#else
	# define getchar() (*p++)
	#endif
	#define putchar(c) (*o++ = c)
	
	constexpr inline bool isdigit(const char c) {	return c >= '0' && c <= '9'; }
	
	inline void read(int &x){
		x = 0; char c = 0;
		for (;!isdigit(c); c = getchar());
		for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	}
	
	inline void write(int x){
		static short Stack[50], top = 0;
		do Stack[++top] = x % 10, x /= 10; while (x);
		while (top) *o++ = Stack[top--] | 48;
	}
}

using namespace Fast;

int n, m, k;
mint A[100010], B[100010];
multiset<mint> st;
int zero;
mint tot = 1;

mint f[22];

inline void modify(int p, mint a, mint b) {
	if (!B[p]) st.erase(st.find(A[p]));
	else {
		mint q = inv(B[p]);
		f[0] = mul(f[0], q);
		for (int i = 1; i <= k - 1; ++i)
			f[i] = mul(q, sub(f[i], mul(f[i - 1], A[p])));
	}
	if (add(A[p], B[p])) tomul(tot, inv(add(A[p], B[p])));
	else --zero;
	
	if (!b) st.insert(a);
	else {
		for (int i = k - 1; i; --i)
			f[i] = add(mul(f[i], b), mul(f[i - 1], a));
		f[0] = mul(f[0], b);
	}
	if (add(a, b)) tomul(tot, add(a, b));
	else ++zero;
	A[p] = a, B[p] = b;
}

inline mint query() {
	mint res = zero ? 0 : tot;
	if (st.empty()) {
		for (int i = 0; i <= k - 1; ++i)
			tosub(res, f[i]);
	} else if ((int)st.size() <= k) {
		static mint g[22];
		memcpy(g, f, sizeof (mint) * k);
		for (const auto& a: st) {
			for (int i = k - 1; i; --i)
				g[i] = mul(g[i - 1], a);
			g[0] = 0;
		}
		for (int i = 0; i <= k - 1; ++i)
			tosub(res, g[i]);
	}
	return res;
}

signed main() {
	fread(buf, 1, MAX, stdin);
	read(n), read(k);
	for (int i = 1, a; i <= n; ++i)
		read(a), A[i] = a % mod;
	for (int i = 1, b; i <= n; ++i)
		read(b), B[i] = b % mod;
	read(m), f[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (!B[i]) st.insert(A[i]);
		else {
			for (int j = k - 1; j; --j)
				f[j] = add(mul(f[j], B[i]), mul(f[j - 1], A[i]));
			f[0] = mul(f[0], B[i]);
		}
		if (add(A[i], B[i])) tomul(tot, add(A[i], B[i]));
		else ++zero;
	}
	for (int i = 1, p, a, b; i <= m; ++i) {
		read(p), read(a), read(b);
		modify(p, a % mod, b % mod), write(query()), putchar('\n');
	}
	fwrite(obuf, 1, o - obuf, stdout);
	return 0;
}
```

---

## 作者：SilverLi (赞：5)

[RELATIVNOST の 传送门](https://www.luogu.com.cn/problem/P6533)

线段树优化 dp 已经有很多题解讲的很好了。

dp 状态是一样的，但是一般的线段树优化 dp 空间要开 $4n$，而且只利用到线段树的一点点功能（单点修改），所以可以先优化空间，从 $4n$ 优化到 $2n$。

如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/kposmyal.png)

如果用线段树优化 dp 的方法会导致树不止 $\log n+1$ 层，所以可以**从下往上建树**来保证最多 $\log n+1$ 层。

就直接将叶子节点赋值，其余 $\log n$ 层的答案就同线段树的 dp 一样更新。

然后每次询问都直接从要修改的点 $p$ 所对应的叶子节点依次向上更新。

点 $p$ 对应的叶子节点就是 $p+n-1$，向上就直接当前的节点 $now$ 改为 $\frac{now}{2}$ 即可。

~~C 风格的代码。~~

```cpp
#include <stdio.h>
int p,A,B,n,c,Q,a[400005],b[400005],t[400005][21];
int minn(int a,int b) {return a>b?b:a;}
signed main() {
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;++i)   scanf("%d",a+i),a[i]%=10007;
	for(int i=1;i<=n;++i)   scanf("%d",b+i),a[i]%=10007;
	for(int i=1;i<=n;++i)   t[n+i-1][0]=b[i],t[n+i-1][1]=a[i];
	for(int p=n-1;p;--p)
		for(int i=0;i<=c;++i)
			for(int j=0;j<=c;++j)
				t[p][minn(i+j,c)]+=1ll*t[p<<1][i]*t[p<<1|1][j]%10007,
				t[p][minn(i+j,c)]%=10007;
	scanf("%d",&Q);
	while(Q--) {
		scanf("%d%d%d",&p,&A,&B);
		A%=10007,B%=10007;
		p+=n-1;
		t[p][0]=B,t[p][1]=A;
		for(p>>=1;p;p>>=1) {
			for(int i=0;i<=c;++i)   t[p][i]=0;
			for(int i=0;i<=c;++i)
				for(int j=0;j<=c;++j)
					t[p][minn(i+j,c)]+=1ll*t[p<<1][i]*t[p<<1|1][j]%10007,
					t[p][minn(i+j,c)]%=10007;
		}
		printf("%d\n",t[1][c]);
	}
	return 0;
}
```

---

## 作者：Feyn (赞：5)

[link](https://www.luogu.com.cn/problem/P6533) & [博客园食用](https://www.cnblogs.com/dai-se-can-tian/p/16491255.html)

建议管理大大评紫，理由：巧妙的线段树优化动态规划。

首先考虑补集转化。所有顾客不受限制的购买方案显然是 $\prod\limits_ia_i+b_i$ ，即每个顾客买黑白画和彩色画的方案相乘。要求买彩色画的人数不少于某个值的方案，就可以转化成用总方案减去买彩色画的人数不足某个值的方案，于是大大地降低了数据范围。

对于 $30\%$ 的数据可以直接动态规划。假如用 $f_i$ 来代表了前 $j-1$ 名顾客中有 $i$ 名买了彩色画的方案数，用 $a_j、b_j$ 来代表当前这个顾客最多的彩色画和黑白画的个数，有显而易见的转移方程是 $f_i=f_i\times b_j+f_{i-1}\times a_j$ ，当然要注意判断边界和倒序枚举。

然后考场上的我就想出了一个傻逼的做法（这段内容不是正解），上面那个式子具有极强的矩阵乘法的特征，每个顾客的选择可以看成是如下的矩阵：

$$\begin{bmatrix}b_i&0&\dots&0\\a_i&b_i&\dots&0\\0&a_i&\dots&0\\\dots&\dots&\dots&\dots\\0&0&\dots&a_i\end{bmatrix}$$

于是就可以考虑建立一个线段树，每个叶子节点代表一个顾客的转移矩阵。这样一来就可以做到单点修改整体查询了。花了半个多小时打出来发现不论是时间还是空间都承受不住，然后然后这道题就只得了暴力分。果然我太弱了。

正解也用到了线段树，但并没有使用矩阵乘法。它考虑的是这个问题各部分互不干扰，符合分治的条件，也就是说对于要在区间 $[l,r]$ 中选择 $x$ 个彩画顾客的方案会等于 $ans(l,r,x)=\sum\limits_{i=0}^xans(l,mid,i)\times ans(mid+1,r,x-i)$ ，于是就可以直接上线段树了。由于这道题卡空间卡得比较死所以要用动态开点来建立线段树。

还有就是对于总方案数每次修改不需要重复计算，因为修改了乘积式中的一项就相当于是除以原来的值再乘上后来的值，用逆元即可。

代码：

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=100010;
const int mod=10007;
using namespace std;
inline void read(int &wh){
	wh=0;int f=1;char w=getchar();
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w>='0'&&w<='9'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,n,num,a[N],b[N];

#define lc (t[wh].left)
#define rc (t[wh].right)
#define mid (l+r>>1)
struct node{
	int left,right,data[20];
}t[N<<1];
inline void pushup(int wh){
	for(int i=0;i<n;i++){
		t[wh].data[i]=0;
		for(int j=0;j<=i;j++){
			t[wh].data[i]+=t[lc].data[j]*t[rc].data[i-j]%mod;
			t[wh].data[i]%=mod;
		}
	}
}
int cnt=1;
inline int build(int wh,int l,int r){
	if(!wh)wh=++cnt;
	if(l==r){
		t[wh].data[0]=b[l];
		t[wh].data[1]=a[l];
		return wh;
	}
	lc=build(lc,l,mid);
	rc=build(rc,mid+1,r);
	pushup(wh);return wh;
}
inline void change(int wh,int l,int r,int pl){
	if(l==r){
		t[wh].data[0]=b[l];
		t[wh].data[1]=a[l];
		return;
	}
	if(pl<=mid)change(lc,l,mid,pl);
	else change(rc,mid+1,r,pl);
	pushup(wh);return;
}
#undef lc
#undef rc
#undef mid

inline int qpow(int s1,int s2){
	if(s2==1)return s1;
	int an=qpow(s1,s2>>1);
	if(s2&1)return an*an%mod*s1%mod;
	else return an*an%mod;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);
	for(int i=1;i<=m;i++)read(a[i]),a[i]%=mod;
	for(int i=1;i<=m;i++)read(b[i]),b[i]%=mod;
	build(1,1,m);int sum=1;
	for(int i=1;i<=m;i++)sum=sum*(a[i]+b[i])%mod;
	read(num);int s1,s2,s3;
	while(num--){
		read(s1);read(s2);read(s3);s2%=mod;s3%=mod;
		sum=sum*qpow(a[s1]+b[s1],mod-2)%mod;
		sum=sum*(s2+s3)%mod;
		a[s1]=s2;b[s1]=s3;
		change(1,1,m,s1);
		int ans=sum;
		for(int i=0;i<n;i++)ans-=t[1].data[i];
		printf("%d\n",(ans%mod+mod)%mod);
	}
	
	return 0;
}
```

---

## 作者：Mu_leaf (赞：3)

## 分析：
由于前面的大佬们都讲清楚了线段树维护 dp 数组这里便不再赘述了，本文只是在大佬的题解上进行进一步的深入。

这里主要是提供一种新的思路，~~解决像本文作者这样就不会动态开点空间又爆炸了的问题。~~

我们要将原本 $4$ 倍的空间缩小至 $2$ 倍，关于为什么线段树要开到 $4$ 倍空间请移步他人博客，这里不赘述。

首先先明确一个定义 $\mathit{tr}_{i,j}$ 表示在第 $i$ 个节点时，有 $j$ 个人选择买彩色画的方案数，此时的转移方程可表示为
$$\mathit{tr}_{id,i+j}=\mathit{tr}_{id\times2,i} \times \mathit{tr}_{id\times2+1,j}$$
分析转移方程可得如果要求得当前节点的方案数与自己的父亲无关，只会与已经求得答案的左右儿子有关。再进一步展开可以发现**在线段树分治时对答案不会产生影响。而是在合并答案时当前节点才会改变答案**。

有了这个结论，那么线段树的经典递归便可以舍去，改为先为最底层节点赋值，在进行循环合并答案。

需要注意的是，我们怎么找到当前节点的父亲呢？这里用一下小学数学知识，既然我们用 $x \times 2$ 表示左儿子 $x \times 2 + 1$ 表示右儿子，那么对于 $x$ 号节点的父亲就是 $\lfloor\frac{x}{2}\rfloor$。

## 需要注意的是：
根据满二叉树的性质，节点数共有 $2n-1$ 个而叶子节点数一定有 $n$ 个，所有非叶子节点只有 $n-1$ 个。

此时单次修改的时间复杂度为 $O(c^2\log n)$。

空间复杂度 $O(2\times n \times c)$。全部在可接受范围内，那么我们的目的便达到了。

我们便完成了一个~~不是线段树的变态线段树~~。



# Code：
```cpp
#include <bits/stdc++.h>
#define ls x*2
#define rs x*2+1
#define minc min(i+j,c)
using namespace std;
const int N=1e5+5,mod=1e4+7;
int n,c,Q,ind,A,B;
int a[N],b[N];
int tr[N*2][21];
void push_up(int x){
	for(int i=0;i<=c;i++) tr[x][i]=0;
	for(int i=0;i<=c;i++){
		for(int j=0;j<=c;j++){
			tr[x][minc]=((1ll*tr[ls][i]*tr[rs][j])%mod+tr[x][minc])%mod;//状态转移
		}
	}
}
void change(int id,int A,int B){
	tr[id][0]=B,tr[id][1]=A;//为叶子节点重新赋值
	for(id/=2;id>0;id/=2)push_up(id);//找到它的父亲进行答案统计
}
int main(){
	cin >> n >> c;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=n;i++) cin >> b[i];
	for(int i=1;i<=n;i++){tr[n+i-1][0]=b[i],tr[n+i-1][1]=a[i];}//为所有叶子节点赋初值
	for(int i=n-1;i>=1;i--) push_up(i);//跑一遍dp做预处理 。
//	build(1,1,n);这里不需要再建树了。
	cin >> Q;
	for(int i=1,x,aa,bb;i<=Q;i++){
		cin >> x >> aa >> bb;
		aa%=mod,bb%=mod;
		change(x+n-1,aa,bb);
     		//因为单个节点的编号已经变成了 x+n-1。
		cout << tr[1][c] << "\n";
	}
	return 0;
}
```


---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/P6533)。

为啥都是线段树。。。来一发最劣 $O(nc+qc^2)$，实际远远跑不到的做法。

首先考虑补集转化，用总方案数减去 $\le c$ 个人买彩色画的方案数。

显然总方案数 $tot=\prod_{i=1}^na_i+b_i$，后者容易想到用背包求出：设 $f_{i,j}$ 表示只考虑前 $i$ 个人，有 $j$ 个人买了彩色画的方案数，显然有：（为方便表述，不妨认为 $j<0$ 时 $f$ 为 $0$）
$$
f_{i,j}=b_if_{i-1,j}+a_if_{i-1,j-1}
$$
修改时直接退背包即可，不会退背包的看 [这题](https://www.luogu.com.cn/problem/P4141)。

于是我们写出了如下 $O((n+q)c)$ 的代码，喜提 56pts：

```cpp
constexpr int N = 1e5 + 5, C = 25, mod = 1e4 + 7;

ll pw(ll a, ll b = mod - 2, ll res = 1) {
    for(; b; b >>= 1, a = a * a % mod)
        if(b & 1) res = res * a % mod;
    return res;
}

int n, c, a[N], b[N];
ll f[C];

void mian() {
    read(n, c);
    rep(i, 1, n) read(a[i]);
    rep(i, 1, n) read(b[i]);
    f[0] = 1;
    rep(i, 1, n) per(j, c - 1, 0) {
        (f[j] *= b[i]) %= mod;
        if(c) (f[j] += f[j - 1] * a[i]) %= mod;
    }
    ll tot = 1;
    rep(i, 1, n) (tot *= a[i] + b[i]) %= mod;
    int q; read(q);
    while(q--) {
        int p, x, y;
        read(p, x, y);
        int inv = pw(b[p]);
        rep(j, 0, c - 1) {
            if(c) (f[j] -= f[j - 1] * a[p]) %= mod;
            (f[j] += mod) %= mod;
            (f[j] *= inv) %= mod;
        }
        (tot *= pw(a[p] + b[p])) %= mod;
        per(j, c - 1, 0) {
            (f[j] *= y) %= mod;
            if(c) (f[j] += f[j - 1] * x) %= mod;
        }
        (tot *= x + y) %= mod;
        a[p] = x, b[p] = y;
        int res = tot;
        rep(j, 0, c - 1) res = (res - f[j] + mod) % mod;
        cout << res << endl;
    }
}
```

WA 的原因是我们退背包和重新计算 $tot$ 时需要用除法，而本题模数过小导致可能除数为 $0$。

考虑在 DP 时跳过 $b=0$ 的情况，把 $b=0$ 的所有位置放在一个 `set` 里，询问时再计算。

这样每次询问的代价是 $c\times$ `set` 大小 的。但是我们发现，当进行了 $c$ 次 $b=0$ 的转移后，$f$ 的所有位置就都是 $0$ 了，因此把这部分判掉，单次询问最劣就是 $O(c^2)$ 的了。

$tot$ 的计算更加简单，只需要记录现在有几个 $(a_i+b_i)\bmod P=0$ 的位置即可。

是目前的最优解：

```cpp
constexpr int N = 1e5 + 5, C = 25, mod = 1e4 + 7;

ll pw(ll a, ll b = mod - 2, ll res = 1) {
    for(; b; b >>= 1, a = a * a % mod)
        if(b & 1) res = res * a % mod;
    return res;
}

int n, c, a[N], b[N];
ll f[C], g[C];

void mian() {
    read(n, c);
    rep(i, 1, n) read(a[i]);
    rep(i, 1, n) read(b[i]);
    f[0] = 1;
    int ab0 = 0;
    multiset<int> st;
    rep(i, 1, n) {
        a[i] %= mod, b[i] %= mod;
        if(b[i] == 0) st.emplace(a[i]);
        else {
            per(j, c - 1, 0) {
                (f[j] *= b[i]) %= mod;
                if(j) (f[j] += f[j - 1] * a[i]) %= mod;
            }
        }
    }
    ll tot = 1;
    rep(i, 1, n) {
        if((a[i] + b[i]) % mod == 0) ++ab0;
        else (tot *= a[i] + b[i]) %= mod;
    }
    int q; read(q);
    while(q--) {
        int p, x, y;
        read(p, x, y);
        x %= mod, y %= mod;
        if(b[p] == 0) st.erase(st.find(a[p]));
        else {
            int inv = pw(b[p]);
            rep(j, 0, c - 1) {
                if(j) (f[j] -= f[j - 1] * a[p]) %= mod;
                (f[j] += mod) %= mod;
                (f[j] *= inv) %= mod;
            }
        }
        if((a[p] + b[p]) % mod == 0) --ab0;
        else (tot *= pw(a[p] + b[p])) %= mod;
        if(y == 0) st.emplace(x);
        else {
            per(j, c - 1, 0) {
                (f[j] *= y) %= mod;
                if(j) (f[j] += f[j - 1] * x) %= mod;
            }
        }
        if((x + y) % mod == 0) ++ab0;
        else (tot *= x + y) %= mod;
        a[p] = x, b[p] = y;
        int res = ab0 ? 0 : tot;
        if(!st.empty()) {
            if(st.size() > c) memset(g, 0, sizeof g);
            else {
                memcpy(g, f, sizeof f);
                for(auto a : st) {
                    per(j, c - 1, 0) {
                        g[j] = 0;
                        if(j) g[j] = g[j - 1] * a % mod;
                    }
                }
            }
            rep(j, 0, c - 1) res = (res - g[j] + mod) % mod;
        }
        else {
            rep(j, 0, c - 1) res = (res - f[j] + mod) % mod;
        }
        cout << res << endl;
    }
}
```

---

## 作者：Rainsleep (赞：0)

[cnblog](https://www.cnblogs.com/Rainsheep/p/18475810)

考虑当 $q = 0$ 时怎么做。

注意到性质 $c \le 20$，因此不妨正难则反，将**至少有 $c$ 个人购买彩色画**的方案数转化为总方案数减去**不足 $c$ 人购买彩色画的方案数**。

这个是一个类似凑数的 dp，不妨考虑背包。我们有 $f_{i, j}$ 表示前 $i$ 人中**恰好** $j$ 人购买彩色画的方案数。

对于当前人，可以选择买或者不买彩色画，所以有转移

$$f_{i, j} = f_{i - 1, j - 1} \times a_i + f_{i - 1, j} \times b_i$$

>注意到 $f_i$ 只跟 $f_{i - 1}$ 这一维有关，可以进行滚动。

总答案数，根据乘法原理和加法原理有 $tot = \displaystyle\prod_{i = 1}^n (a_i + b_i)$。

当 $q \ne 0$ 时，我们需要支持修改。但别忘了上面 dp 的本质还是背包，而背包是支持合并的，于是我们可以把背包放到线段树上，对于每个节点维护一个背包，在 pushup 时进行合并。

复杂度 $O(nc^2 + c^2q \log n)$。

代码：

```cpp
// ubsan: undefined
// accoders
// 如果命运对你缄默, 那就活给他看。
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream> 
using namespace std;
typedef long long LL; 
// #define int LL
const int p = 1e4 + 7;
void read(int &var) {
    var = 0;
    int f = 1;
    char c;
    do { c = getchar();
        if (c == '-') f = -1;
    } while (c < 48 || c > 57);
    while (c >= 48 && c <= 57) var = var * 10 + (c - '0'), c = getchar();
    var *= f;
};
void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int maxc = 21;
const int maxn = 1e5 + 10;
struct Node {
    int f[maxc];
    int tot;
    int ls, rs;
} t[maxn << 2];
int n, c;
int a[maxn], b[maxn];
int tot;
int root;
int q;
inline void pu(int u) {
    Node& rt = t[u];
    Node ls = t[t[u].ls], rs = t[t[u].rs];
    for(int i = 0; i < c; ++ i) rt.f[i] = 0;
    for(int i = 0; i < c; ++ i)
        for(int j = 0; j + i < c; ++ j) rt.f[i + j] = ((LL)rt.f[i + j] + 1LL * ls.f[i] * rs.f[j] % p) % p;
    rt.tot = 1LL * ls.tot * rs.tot % p;
}
inline void build(int& u, int l, int r) {
    if(!u) u = ++ tot;
    if(l == r) {
        t[u].f[1] = a[r];
        t[u].f[0] = b[r];
        t[u].tot = a[r] + b[r];
        return ;
    }
    int mid = l + r >> 1;
    build(t[u].ls, l, mid);
    build(t[u].rs, mid + 1, r), pu(u);
}
inline void upd(int u, int l, int r, int p) {
    if(l == r) {
        t[u].f[1] = a[r];
        t[u].f[0] = b[r];
        t[u].tot = a[r] + b[r];
        return ;
    }
    int mid = l + r >> 1;
    if(p <= mid) upd(t[u].ls, l, mid, p);
    else upd(t[u].rs, mid + 1, r, p);
    pu(u);
}
signed main() {
    // freopen("balloon.in", "r", stdin);
    // freopen("balloon.out", "w", stdout);
    read(n), read(c);
    for(int i = 1; i <= n; ++ i) read(a[i]);
    for(int i = 1; i <= n; ++ i) read(b[i]);
    build(root, 1, n);
    read(q);
    for(int p, x, y; q --; ) {
        read(p), read(x), read(y);
        a[p] = x, b[p] = y;
        upd(root, 1, n, p);
        int ans = t[1].tot;
        for(int i = 0; i < c; ++ i) {
            ans = ((ans - t[1].f[i]) % :: p + :: p) % :: p;
        }
        ans = (ans + :: p) % :: p;
        write(ans); putchar('\n');
    }
    return 0;
}
```

## Ex $n, q \le 10^6$

背包除了支持合并，还支持撤销。

我们注意到一次修改操作，实质上可以转化为撤销一次和插入一次物品，于是 $O(qc)$ 的做法呼之欲出，我们对于每次操作进行撤销 + 插入的组合，实时维护当前的答案。

具体来说，回顾我们的转移
$$f_{i, j} = f_{i - 1, j - 1} \times a_i + f_{i - 1, j} \times b_i$$

进一步的滚动掉 $i$ 这维

$$f_{j} = f_{j - 1} \times a_i + f_{j} \times b_i$$

注意这时转移是倒序，那撤销时正序答案才正确，所以有

```cpp
f[0] = 1LL * f[0] * invb % mod;
for (int i = 1; i < c; ++i) f[i] = (f[i] - f[i - 1] * a[p] % mod + mod) * invb % mod;
```

插入时与初始 dp 相同。

代码：
```cpp
// ubsan: undefined
// accoders
// 如果命运对你缄默, 那就活给他看。
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream> 
using namespace std;
typedef long long LL; 
#define int LL
const int mod = 1e9 + 7;
void read(int &var) {
    var = 0;
    int f = 1;
    char c;
    do { c = getchar();
        if (c == '-') f = -1;
    } while (c < 48 || c > 57);
    while (c >= 48 && c <= 57) var = var * 10 + (c - '0'), c = getchar();
    var *= f;
};
void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
inline int fpow(int a, int b) {
    int ans = 1;
    for(; b; b >>= 1, a = a * a % mod)
        if(b & 1) ans = ans * a % mod;
    return ans;
}
inline int inv(int x) { return fpow(x, mod - 2); }
const int maxc = 21;
const int maxn = 1e6 + 10;
int f[maxn], n, c, q;
int a[maxn], b[maxn], ans = 1;
signed main() {
    freopen("balloon.in", "r", stdin);
    freopen("balloon.out", "w", stdout);
    read(n), read(c); f[0] = 1;
    for(int i = 1; i <= n; ++ i) read(a[i]);
    for(int i = 1; i <= n; ++ i) {
        read(b[i]);
        ans = ans * (a[i] + b[i]) % mod;
    }
    for(int i = 1; i <= n; ++ i) {
        for(int j = c - 1; j > 0; -- j) f[j] = (f[j - 1] * a[i] % mod + f[j] * b[i] % mod) % mod;
        f[0] = (f[0] * b[i]) % mod;
    }
    read(q);
    for(int p, x, y; q --; ) {
        read(p), read(x), read(y);
        int inva = inv(a[p]), invb = inv(b[p]); // 1 / a_p, 1 / b_p
        ans = 1LL * ans * inv(a[p] + b[p]) % mod;
        ans = 1LL * ans * (x + y) % mod;
        f[0] = 1LL * f[0] * invb % mod;
        for(int i = 1; i < c; ++ i) f[i] = (f[i] - f[i - 1] * a[p] % mod + mod) * invb % mod;
        for(int i = c - 1; i > 0; -- i) f[i] = ((f[i - 1] * x % mod + f[i] * y % mod) + mod) % mod;
        f[0] = 1LL * f[0] * y % mod;
        a[p] = x, b[p] = y;
        int res = ans;
        for(int i = 0; i < c; ++ i) res = (res - f[i]) % mod;
        res = (res + mod) % mod;
        cout << res << '\n';
    }
    return 0;
}
```

---

## 作者：LLLLLL7381 (赞：0)

## 说在前面
笔者学校最近有一次模拟赛考到了这个题目，因为做法不够优被降智到 $80$ 分。在本校模拟赛中数据范围最大是 $10^6$，本题解给出的做法针对加强数据设计。
## 常规做法
$30$ 分的暴力就不解释了。直接说正解。                
首先从暴力可以想到用 dp 解决问题，但是注意到原题中存在修改，而且 $c$ 数据范围特别小，因此可以考虑使用线段树维护。在这里为了能过加强版的数据，可以考虑正难则反。说白了就是总的方案数减去不满 $c$ 个人购买一个彩色画的方案，为什么要这样做后文解释。

对于线段树中的每一个节点，定义 $l,r,dp_c$，$dp_j$ 表示从 $l$ 到 $r$ 个人有 $j$ 个人购买了彩色画的方案数目。下面的 $ls$ 与 $rs$ 很显然为左儿子和右儿子。

这样一来，根据乘法原理，可以得出转移方程：
$$tr[x].dp[i+j]=tr[x].dp[i+j]+(tr[tr[x].ls].dp[i] \times tr[tr[x].rs].dp[j])$$

对于单个叶子结点。很显然：
$$tr[x].dp[0] = b[x],tr[x].dp[1]=a[x]$$

为了正难则反的算法，需要对于每个结点维护一个变量 $tot$，表示当前结点在不考虑限制的情况下的总方案数目。对于 $tot$ 的状态转移，可以使用乘法原理转移，式子如下：
$$tr[x].tot=tr[tr[x].ls].tot \times tr[tr[x].rs].tot$$
这样一来，每一层的循环次数可以直接减少 $(c+1)^2-c^2 = 2c+1$ 次，卡卡常可以过全部测试点。（你谷肯定能过，校内 OJ 因为某些原因不能给出）时间复杂度 $O(nc^2+qc^2\log n)$，没啥问题。
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9')
   {
       if(ch=='-')
           f=-1;
       ch=getchar();
   }
   while(ch>='0' && ch<='9')
       x=x*10+ch-'0',ch=getchar();
   return x*f;
}
inline void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
const int maxn = 1e6+5;
const int maxc = 21;
const int mod = 1e9+7;
int cnt=1,n,q,c,a[maxn],b[maxn];
struct node
{
    int ls,rs,l,r;
    int dp[maxc];
    int tot;
}tr[maxn<<2];

class seg_tree
{
    public:
    inline void pushup(int x)
    {
        memset(tr[x].dp,0,sizeof(tr[x].dp));
        for(int i=0;i<c;i++)
        {
            for(int j=0;i+j<c;j++)
            {
                tr[x].dp[i+j]=(1ll*tr[x].dp[i+j]+(1ll*tr[tr[x].ls].dp[i]*tr[tr[x].rs].dp[j]))%mod;
            }
        }
        tr[x].tot=(1ll*tr[tr[x].ls].tot*tr[tr[x].rs].tot)%mod;
    }    
    inline void build(int x,int l,int r)
    {
        tr[x].l=l;
        tr[x].r=r;
        if(l==r)
        {
            tr[x].dp[0]=b[l]%mod;
            tr[x].dp[1]=a[l]%mod;
            tr[x].tot=(a[l]+b[l])%mod;
            return;
        }
        tr[x].ls=++cnt;
        tr[x].rs=++cnt;
        int mid = (l+r)>>1;
        build(tr[x].ls,l,mid);
        build(tr[x].rs,mid+1,r);
        pushup(x);
    }
    inline void update(int x,int pos,int xx,int y)
    {
        if(tr[x].l==tr[x].r and tr[x].l==pos)
        {
            tr[x].dp[0]=y;
            tr[x].dp[1]=xx;
            tr[x].tot=(xx+y)%mod;
            return ;
        }
        int mid = (tr[x].l+tr[x].r)>>1;
        if(pos<=mid)
        {
            update(tr[x].ls,pos,xx,y);
        }
        if(pos>mid)
        {
            update(tr[x].rs,pos,xx,y);
        }
        pushup(x);
    }
}seg;
signed main()
{
    //freopen("balloon.in","r",stdin);
    //freopen("balloon.out","w",stdout);
    n=read(),c=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
    }
    for(int i=1;i<=n;i++)
    {
        b[i]=read();
    }
    seg.build(1,1,n);
    int q=read();
    while(q--)
    {
        int p=read(),x=read(),y=read();
        seg.update(1,p,x,y);
        int ans=tr[1].tot;
        for(int i=0;i<c;i++)
        {
            ans=(ans-tr[1].dp[i]+mod)%mod;
        }
        write(ans);
        putchar(10);
    }
    return 0;
}
```
提到正难则反，就不得不说另一个解法了。这个做法同时可以卡过加强数据。
## 好像不是那么常规的做法
洛谷上有一道题目叫做[消失之物](https://www.luogu.com.cn/problem/P4141)，类似于这道题的方式，我们可以撤销一个人因为改变购买方案而对答案的贡献。
令 $tot$ 为总方案数，$x$ 和 $y$ 分别为修改后第 $i$ 个人的 $a[i]$ 和 $b[i]$。显而易见，可以得到：
$$tot=\prod{a_i+b_i}$$
$$tot'={\frac{tot}{a_i+b_i}}\times (x+y)$$
$$tot'=inv(a_i+b_i) \times (x+y) \times tot$$
其中 $inv(x)$ 是 $x$ 的乘法逆元。令 $f$ 为此人之前的 dp 状态，$g$ 为之后的，这样初始化 $g_0=yf_0$，$g_i=xf_{i-1}+yf_i$。令 $g$ 为之后的状态，很显然，那么 $f_0=inv(y)g_0$，$f_i=inv(y)(g_i-xf_{i-1})$，保证 $i$ 为正整数。
代码就不放了，但是注意，由于本题目模数较小，可能会出现除以零的情况，对于这些元素需要单独捡出来维护。

下课！

---

## 作者：封禁用户 (赞：0)

### 解题思路
正难则反，考虑背包计算购买彩色画人数不超过 $c$ 时的方案数，且（由于其组合意义）可以将任意一个人当作最后一个人处理，因此考虑退背包处理修改

令 $f$ 为考虑当前人前的 dp 数组，$g$ 为考虑当前人后的 dp 数组，$a$ 和 $b$ 为当前人的两个参数，则可以注意到做背包时有：
$$
g_i= \begin{cases}
f_i \times b & i=0\\
f_i \times b +f_{i-1} \times a & \textup{\textmd otherwise}
\end{cases}
$$
注意到可以逆推，即有：
$$
f_i= \begin{cases}
g_i \times b^{-1} & i=0\\
(g_i-f_{i-1} \times a) \times b^{-1} & \textup{\textmd otherwise}
\end{cases}
$$
其中 $b^{-1}$ 为 $b$ 的逆元

注意到计算 $f_i$ 时只使用了 $f_{i-1}$ 的值，所以可以递推地根据 $g$ 计算 $f$。

修改时根据 $g$ 逆推 $f$ 再顺推 $g'$ 即可。

---

## 作者：Jerrywang09 (赞：0)

比较简单的线段树优化 DP。本文中用 $m$ 表示原题中的 $c$。

看到熟悉的“单点修改”，想到线段树。线段树中的每个结点存储 $f$，$f(i)$ 其中 $i<m$ 表示区间内恰好 $i$ 人购买彩色画的方案数，$f(m)$ 表示区间内 $\ge m$ 人购买彩色画的方案数。也就是说，最终要求的答案就是 `t[1].f[m]`（C++ 代码），即根节点（区间 $1\sim n$）$\ge m$ 人购买彩色画的方案数。

剩下的也就是一个 `pushup` 了。先清空 $f$ 数组。枚举左右区间各有 $i,j$ 人购买彩色画，依据乘法原理，有：

$$
t[p].f[i+j]+=t[lc].f[i]\times t[rc].f[j]
$$

由于特殊的状态 $f(m)$，$\ge m$ 的方案都存 $f(m)$ 里，因此要取 $\min(i+j,m)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=100010, M=21, mod=10007;
using namespace std;

int n, m, a[N], b[N];
struct node
{
    int l, r, f[M];
} t[N<<2];
#define lc p<<1
#define rc p<<1|1
void up(int p)
{
    rep(i, 0, m) t[p].f[i]=0;
    rep(i, 0, m) rep(j, 0, m)
    {
        int k=min(i+j, m);
        t[p].f[k]=(t[p].f[k]+t[lc].f[i]*t[rc].f[j]%mod)%mod;
    }
}
void build(int p, int l, int r)
{
    t[p]={l, r};
    if(l==r)
    {
        t[p].f[0]=b[l]%mod, t[p].f[1]=a[l]%mod;
        return;
    }
    int m=l+r>>1;
    build(lc, l, m), build(rc, m+1, r);
    up(p);
}
void modify(int p, int i)
{
    if(t[p].l==t[p].r)
    {
        t[p].f[0]=b[i]%mod, t[p].f[1]=a[i]%mod;
        return;
    }
    int m=t[p].l+t[p].r>>1;
    if(i<=m) modify(lc, i); else modify(rc, i);
    up(p);
}

int main()
{
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%d", a+i);
    rep(i, 1, n) scanf("%d", b+i);
    build(1, 1, n);
    int Q; scanf("%d", &Q);
    while(Q--)
    {
        int i; scanf("%d", &i);
        scanf("%d%d", a+i, b+i);
        modify(1, i);
        printf("%d\n", t[1].f[m]);
    }

    return 0;
}
```

---

## 作者：PTqwq (赞：0)

转送门：https://www.luogu.com.cn/problem/P6533

一个暴力的做法是，每次修改之后 DP，设 $f_i$ 为当前有 $i$ 个人买了彩色画，$i > c$ 的方案也累加在 $f_c$ 上，这样答案就是 $f_c$ 了。转移就是一个很简单的背包了。~~或者也可以理解成多项式乘法~~

做题的时候有想到线段树维护矩阵，然后矩阵加速，但是复杂度寄了。

我们考虑用线段树维护 $f$ 数组，合并 $f$ 和 $g$ 两个数组的方程就是：

$$h_{\min(i + j,c)} \leftarrow f_{i}g_j (0 \leq i, j \leq c)$$

如果 $i + j > c$ 还可以利用后缀和加速一下，先把代码放出来：

```cpp
info operator + (info l, info r) {
  info mid;
  for (int i = 0;i <= c; ++ i) mid.f[i] = 0;
  suf[c + 1] = 0;
  for (int i = c;i >= 0; -- i) suf[i] = (suf[i + 1] + r.f[i]) % mod;
  for (int i = 0;i <= c; ++ i) {
    for (int j = 0;i + j <= c; ++ j) {
      int kd = ((int) (l.f[i])) * ((int) (r.f[j])) % mod;
      mid.f[i + j] = (mid.f[i + j] + kd) % mod;
    }
    int L = c - i + 1;
    int tmp = suf[L];
    tmp = tmp * ((int) (l.f[i])) % mod;
    if (L <= c) mid.f[c] = (mid.f[c] + tmp) % mod;
  }
  return mid;
}
```

然后就是线段树单点修改，查询的时候可以直接查询 `val[1]`，可以省点时间。

写完交上去 MLE 了，怎么会是呢。

我们注意到模数只有 $10^4 + 7$，而 `short` 可以存下，我们考虑存 dp 数组的时候用 `short`，中间转移的时候用 `int` 暂时存储。

然后就可以轻松过掉了。/cf

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read () {
  int x = 0, f = 0;
  char c = getchar ();
  for ( ; c < '0' || c > '9' ; c = getchar ()) f |= (c == '-');
  for ( ; c >= '0' && c <= '9' ; c = getchar ()) x = (x << 1) + (x << 3) + (c & 15);
  return f == 0 ? x : -x;
}
inline ll readll () {
  ll x = 0, f = 0;
  char c = getchar ();
  for ( ; c < '0' || c > '9' ; c = getchar ()) f |= (c == '-');
  for ( ; c >= '0' && c <= '9' ; c = getchar ()) x = (x << 1) + (x << 3) + (c & 15);
  return f == 0 ? x : -x;
}
inline ll pow_mod (ll a, ll b, ll p) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    b >>= 1, a = a * a % p;
  }
  return res;
}
const int N = 1e5 + 5;
const int mod = 1e4 + 7;
int n, c, q;
int a[N], b[N];
short suf[23];
namespace my_solution {
  struct info {
    short f[23];
  };
  info operator + (info l, info r) {
    info mid;
    for (int i = 0;i <= c; ++ i) mid.f[i] = 0;
    suf[c + 1] = 0;
    for (int i = c;i >= 0; -- i) suf[i] = (suf[i + 1] + r.f[i]) % mod;
    for (int i = 0;i <= c; ++ i) {
      for (int j = 0;i + j <= c; ++ j) {
        int kd = ((int) (l.f[i])) * ((int) (r.f[j])) % mod;
        mid.f[i + j] = (mid.f[i + j] + kd) % mod;
      }
      int L = c - i + 1;
      int tmp = suf[L];
      tmp = tmp * ((int) (l.f[i])) % mod;
      if (L <= c) mid.f[c] = (mid.f[c] + tmp) % mod;
    }
    return mid;
  }
  info val[N << 2];
  inline void push_up (int u) {val[u] = (val[u << 1] + val[u << 1 | 1]);}
  inline void update (int u, int l, int r, int id, int va, int vb) {
    if (l == r) {
      for (int i = 2;i <= c; ++ i) val[u].f[i] = 0;
      val[u].f[0] = vb, val[u].f[1] = va;
      return ;
    }
    int mid = l + r >> 1;
    if (id <= mid) update (u << 1, l, mid, id, va, vb);
    else update (u << 1 | 1, mid + 1, r, id, va, vb);
    push_up (u);
  }
  inline void solve () {
    for (int i = 1;i <= n; ++ i) a[i] %= mod, b[i] %= mod;
    for (int i = 1;i <= n; ++ i) update (1, 1, n, i, a[i], b[i]);
    while (q --) {
      int u = read ();
      a[u] = read (), b[u] = read ();
      a[u] %= mod, b[u] %= mod;
      update (1, 1, n, u, a[u], b[u]);
      int zzz = val[1].f[c];
      printf ("%d\n", zzz);
    }
  }
}
signed main () {
  n = read (), c = read ();
  for (int i = 1;i <= n; ++ i) a[i] = read ();
  for (int i = 1;i <= n; ++ i) b[i] = read ();
  q = read ();
  my_solution :: solve ();
  return 0;
}
```

---

## 作者：watcher_YBH (赞：0)

# 思路：
版权属于我教练。

这道题我们可以用 dp 加线段树做。

 dp 的思路十分清晰：所有顾客的 $a_i$ 可以凑齐多少中达不到 $c$ 的情况数，再乘上所有顾客的 $b_i$ 可以凑齐多少中达不到 $c$ 的情况数，就是最终的方案数。
 
利用线段树的优化也很简单：每一个节点代表每一个区间的的总方案数。但是线段数有一个很致命的问题，**四倍的空间太大了**。于是我们可优化线段树的空间（动态开点也可以）：

我们先来了解一下线段树为什么要开四倍空间，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hzf96bon.png)

传统的线段树的左右儿子分别为 $k \times 2$ 和 $k \times 2 + 1$，这就会使一些节点浪费。在图中，用线段树存储六个点时的数组下标已经到了 $13$，但是数组下标为 $10,11$ 的节点却并没有任何数值。所以，线段树在最坏的情况下要开四倍空间。

线段树浪费空间是因为线段树是从上往下依次扩建的，我们想要优化空间就必须换一个方向：**从下往上依次合并到根节点**。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w1qpvpk7.png)

这样，数组的空间就可以优化到二倍（左右儿子还是 $k \times 2$ 与 $k \times 2 + 1$）。建树我们可以先建立最后一层，数组下标为 $n \sim 2n-1$，然后再更新下标为 $1 \sim n-1$ 的节点。 

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)//卡常小技巧
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
const int mod = 1e4+7;
int n,c,q,ans,a[MAX],b[MAX];
int tree[MAX*2][25];//我们是从下往上建的树，所以只用开二倍的空间
void gengxin(int k){//更新
	for(int i = 0; i<=c; i++)tree[k][i] = 0;//先将数组的这一项清零
	for(int i = 0; i<=c; i++)//用a[i]凑出的张数
		for(int j = 0; j<=c; j++)//用b[i]凑出的张数
			tree[k][min(i+j,c)]=((tree[k*2][i]*tree[k*2+1][j])%mod+tree[k][min(i+j,c)])%mod;
}
void change_pin(int a_,int b_,int y){//更改
	tree[y][0] = b_; tree[y][1] = a_;//直接改
	y/= 2;//更新包含它的节点
	while(y) gengxin(y),y/=2;
}
int main(){
	scanf("%d%d",&n,&c);
	for(int i = 1; i<=n; i++)scanf("%d",a+i),a[i]%=mod;
	for(int i = 1; i<=n; i++)scanf("%d",b+i),b[i]%=mod;
	for(int i = n; i<=n*2-1; i++) tree[i][0] = b[i-n+1],tree[i][1] = a[i-n+1];
	//建立最后一层
	//0张彩色画，每人就有b[i]种情况；1张彩色画就有a[i]种情况
	for(int i = n-1; i>=1; i--) gengxin(i);//更新上面的父节点
	cin>>q;
	for(int i = 1; i<=q; i++){
		int p,a_,b_;
		scanf("%d%d%d",&p,&a_,&b_);
		a_ %= mod;  b_ %= mod;
		change_pin(a_,b_,p+n-1);//这里一定要加n-1，因为树中的最后一层为n~2n-1
		printf("%d\n",tree[1][c]);
	}
	return 0;
}

```
记得开 O2。

---

