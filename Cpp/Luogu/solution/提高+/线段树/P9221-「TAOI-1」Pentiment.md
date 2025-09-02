# 「TAOI-1」Pentiment

## 题目背景

近日（存疑），一款名为闊靛緥婧愮偣的游戏更新了它的 4.0 版本。在这个版本中某谱面中的大直角蛇给玩家们留下了深刻的印象……

![](https://cdn.luogu.com.cn/upload/image_hosting/qbdvtftu.png)

## 题目描述

我们规定，在 $n$ 行 $m$ 列的网格中，“直角蛇”是这样一条路径：

- 从最下方（第一行）的某个格子的中心开始，在最上方（第 $n$ 行）的某个格子的中心结束。
- 每次可以向上、向右或向左移动一格，每次移动后都到达某个格子的中心（**不能向下移动**）。
- 不能重复经过同一个格子。

特别地，为了给你增加一些考验，我们规定有一些格子是“直角蛇”不能经过的。

请你统计在给定的网格中存在多少种这样的“直角蛇”。答案对 $998244353$ 取模。

## 说明/提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leq 10^6$，$m \leq 2$。
- Subtask 2（10 points）：$q=0$。
- Subtask 3（15 points）：$n,m \leq 10^4$。
- Subtask 4（20 points）：$n \leq 10^4$。
- Subtask 5（20 points）：$m \leq 10^4$。
- Subtask 6（25 points）：无特殊限制。

对于所有测试数据，$2 \leq n \leq 10^9$，$1 \leq m \leq 10^9$，$0 \leq q \leq 10^5$，$1 \leq x_i \leq n$，$1 \leq y_i \leq m$。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/dkyhh41q.png)

如图，样例一中共有八种满足条件的“直角蛇”。

对于样例二，不存在满足条件的“直角蛇”。

---

在寂若死灰中屈服。

在飘忽不定中屈服。

在功亏一篑中屈服。

## 样例 #1

### 输入

```
2 3 2
1 1
2 1```

### 输出

```
8```

## 样例 #2

### 输入

```
4 4 4
1 1
2 2
3 3
4 4```

### 输出

```
0```

## 样例 #3

### 输入

```
6 5 4
1 3
3 1
3 4
5 2```

### 输出

```
2000```

## 样例 #4

### 输入

```
100000000 100000000 0```

### 输出

```
103866487```

# 题解

## 作者：251Sec (赞：5)


下文将第 $i$ 行第 $j$ 列称为 $(i, j)$。

首先发现整条路径只和起点，终点，以及在每一行你选择哪个格子向上走有关。

定义 $f_{i,j}$ 代表到达 $(i, j)$ 的方案数。

若 $(i, j)$ 有一个障碍，$(i, k)$ 有一个障碍，且 $\forall p \in [j+1,k-1]$，$ (i, p)$ 没有障碍，则 $\forall p \in [j+1, k-1], f_{i,p}=\sum\limits_{s=j+1}^{k-1}f_{i-1, s}$。且 $f_{i,j}=f_{i,k}=0$。换句话说，对于这些格子，我们都可以先向上移动一格，然后左右移动到达 $(i,p)$。

注意到 $f$ 的第一维可以压掉，并且转移是区间求和与区间覆盖的形式，所以可以用线段树优化。

但是考虑到 $n, m$ 的数量级，时间和空间都无法承受。注意到 $q$ 很小，必定会出现连续的很多行没有障碍，可以使用快速幂直接转移。空间上的问题可以直接使用动态开点线段树来解决，当然更好的方案是离线下来离散化。

---

## 作者：喵仔牛奶 (赞：4)

# Preface

这是一篇线性复杂度的题解。

在蒟蒻的[博客](https://www.cnblogs.com/Milkcatqwq/p/17580329.html)食用效果（可能）更佳。

# Solution

## 算法一

考虑朴素 DP，设 $f_{i,j}$ 是从第 $1$ 行任意格子出发，走到 $(i,j)$ 的方案数。枚举行 $i$ 进行 DP，令 $x,y$ 分别为 $(i,j)$ 左边和右边的**第一个**障碍，$l=x+1,r=y-1$，则 $\displaystyle f_{i,j}=\sum_{k=l}^{r}f_{i-1,k}$。初值是对于所有 $i\in[1,m]$，$f_{0,i}=1$。

时间复杂度 $\mathcal{O}(nm+q)$，期望得分 $25$。

## 算法二

考虑优化算法一。对于每个 $[l,r]$，$j$ 在这之间的 $f_{i,j}$ 都相等，令这个值为 $k$。考虑珂朵莉树（颜色段均摊），将三元组 $(l,r,k)$ 放入容器进行操作。由于每次遍历上行的所有区间，所以放入 `vector` 即可。每次转移时使用双指针维护区间的和。

时间复杂度 $\mathcal{O}(n+q)$，期望得分 $45$。

## 算法三

考虑 $q=0$ 的部分分。$q=0$ 即每行都是 $l=1,r=m$。观察转移方程可知答案为 $m^{n+1}$。

时间复杂度 $\mathcal{O}(\log n)$，期望得分 $10$。

## 算法四

对有障碍的行跑算法二，没有障碍的行跑算法三即可。算法三有些改动，设当前行（有障碍）为 $i$，上一行有障碍的是 $p$ 且 $p<i-1$，可以将上一行直接处理为 $\displaystyle(1,m,m^{i-p-2}\times\sum_{j=1}^{m}f_{p,j})$。需要特判没有做到第 $n$ 行的情况。

时间复杂度 $\mathcal{O}(q\log n)$，期望得分 $100$。

## 算法五

使用[光速幂](https://loj.ac/p/162)（分块预处理的快速幂），钦定 $B=\sqrt{n}+1$，处理出所有 $0\leq i\leq B$ 的 $m^i$ 与 $m^{iB}$，即可做到 $\mathcal{O}(1)$ 查询 $m$ 的幂。

时间复杂度 $\mathcal{O}(q+\sqrt{n})$，期望得分 $100$。

# Code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, mod = 998244353;
	struct node { LL v, l, r; LL val() { return v * (r - l + 1); } }; // val：求整段区间数的和
	LL n, m, q, qwq, cnt, ans, p1[N], p2[N]; pii a[N];
	vector<node> vec, now;
	LL qpow(LL k) { return p1[k % cnt] * p2[k / cnt] % mod; }
	LL add(LL& x, LL y) { return x = ((x + y) % mod + mod) % mod; }
	int main() {
		cin >> n >> m >> q, cnt = sqrt(n) + 1, p1[0] = p2[0] = 1;
		for (int i = 1; i <= cnt; i ++) p1[i] = p1[i - 1] * m % mod;
    	for (int i = 1; i <= cnt; i ++) p2[i] = p2[i - 1] * p1[cnt] % mod; // 光速幂
		for (int i = 1; i <= q; i ++) cin >> a[i].fi >> a[i].se;
		vec.push_back({1, 1, m}), qwq = 0; // 初值
		for (int i = 1; i <= q; ) {
			if (a[i].fi - qwq > 1) {
				LL sum = 0, k = a[i].fi - qwq;
				for (node v : vec) add(sum, v.val());
				vector<node>().swap(vec), vec.push_back({sum * qpow(k - 2) % mod, 1, m});
			} // 算法三
			qwq = a[i].fi, vector<node>().swap(now);
			LL l = 0, r = 0, pre = 1, sum = vec.front().val();
			while (a[i].fi == qwq) {
				if (pre < a[i].se) now.push_back({0, pre, a[i].se - 1});
				now.push_back({-1, a[i].se, a[i].se}), pre = a[i].se + 1, i ++;
			}
			if (pre <= m) now.push_back({0, pre, m});
			for (node &v : now) {
				if (v.v == -1) { v.v = 0; continue; }
				while (vec[l].r < v.l) add(sum, -vec[l ++].val());
				while (vec[r].r < v.r) add(sum, vec[++ r].val());
				v.v = ((sum - vec[l].v * (v.l - vec[l].l) - vec[r].v * (vec[r].r - v.r)) % mod + mod) % mod;
			} // 算法二
			vec.swap(now);
		}
		if (qwq < n) {
			LL sum = 0, k = n - qwq + 1;
			for (node v : vec) add(sum, v.val());
			vector<node>().swap(vec), vec.push_back({sum * qpow(k - 2) % mod, 1, m});
		} // 特判没有做完
		for (node v : vec) add(ans, v.val());
		cout << ans << '\n';
		return 0;
	}
}
int main() {
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}
```

---

## 作者：2018ljw (赞：2)

不用线段树的其实。

设 $dp_{i,j}$ 表示从位置 $j$ **进入**第 $i$ 行的方案数。

易得转移式 $dp_{i,j}=\sum\limits_{k}dp_{i-1,k}$，满足第 $i-1$ 行，$k$ 走到 $j$ 的区间内没有障碍。特别的，若 $(i-1,j)$ 或 $(i,j)$ 为障碍，则 $dp_{i,j}=0$。

考虑把 $i$ 和 $i-1$ 两行的障碍拍扁到数轴上，那么对于一个非障碍区间的 $dp_{i,[l,r]}$，会发现他们转移是完全一样一段区间和。

假设障碍把第 $i-1$ 行划分成了若干个区间，我们转移 $dp_{i,j}$ 这段区间的时候实际上就是在找 $j$ 在上一段的哪个区间里，然后求区间和。

所以不再具体维护某个位置的 $dp$ 值，我们对于一行，只需要维护若干被障碍分隔的区间左右端点，以及这段区间的和。这样转移一段位置时，只需要找出它对应上一段的哪个区间；转移一段连续区间时，只需要求出一个点值再乘上区间长度。

控制好转移顺序可以保证区间按左端点单调，找区间就可以双指针处理。

然后对于障碍，若一个障碍在第 $i-1$ 行有但第 $i$ 行没有，我们需要额外加入 $[l,l,0]$ 这段区间，便于后续区间合并。

然后转移完一行后，只需要按顺序把左右端点相邻的区间合并即可。

若一行没有障碍，那么上一行每段区间 $[l,r,sum]$ 到这一行会变为 $[l,r,sum\times (r-l+1)]$，可以直接处理出这行的 $[1,m,sum^\prime]$。

若连续若干行没有障碍，不难发现每转移一行 $sum$ 都会乘上 $m$，快速幂即可。

初值 $[1,m,1]$ 表示第 $0$ 行的状态，结束状态引入没有任何障碍的第 $n+1$ 行，答案为第 $n+1$ 行的 $sum$。

复杂度 $O(q\log n)$，瓶颈在快速幂。关注到只需要求 $m^k$，可以用光速幂预处理做到 $O(q+\sqrt n)$。

因为实际评测时快速幂和光速幂耗时差不多，所以放快速幂的版本了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
const int mod=998244353;
using namespace std;
int n,m,q,cnt,nc;
int dx[200001],dy[200001];
int p[500001],w;
long long ksm(long long x,int y){
	long long res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
struct dps{
	int l,r;
	long long res;
}dp[1000001],tmp[1000001];
unordered_map<int,bool>tl;
int main(){
	int i,j,k,ls=0;dp[0].r=-1;
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=q;i++)scanf("%d%d",&dx[i],&dy[i]);
	for(i=1;i<=q;i++)if(i==q||dx[i+1]!=1)break;
	dp[++cnt]={1,m,1};
	for(i=ls+1;i<=q;i++){
		if(i!=q&&dx[i+1]==dx[i])continue;
		if(dx[ls]!=dx[i]-1){
			int dh=dx[i]-dx[ls]-2;
			long long sum=0;
			for(j=1;j<=cnt;j++)sum+=dp[j].res*(dp[j].r-dp[j].l+1)%mod,sum%=mod;
			cnt=1;dp[1]={1,m,sum};
			dp[1].res=dp[1].res*ksm(m,dh)%mod;
		}
		nc=0;w=0;
		if(dx[ls]==dx[i]-1){
			for(j=ls;j;j--){
				if(dx[j]!=dx[ls])break;
				if(dy[j]==-1)continue;
				p[++w]=dy[j];
			}
		}
		tl.clear();
		for(j=ls+1;j<=i;j++)p[++w]=dy[j],tl[dy[j]]=1;
		p[++w]=0;p[++w]=m+1;
		sort(p+1,p+w+1);w=unique(p+1,p+w+1)-p-1;
		int pos=1;
		for(j=1;j<w;j++){
			if(p[j]&&!tl[p[j]])tmp[++nc]={p[j],p[j],0};
			int nx=p[j+1],len=nx-p[j]-1;
			while(pos<=cnt&&dp[pos].r<p[j]+1)pos++;
			if(nx==p[j]+1)continue;
			long long s=0;
			s=dp[pos].res;
			s=s*len%mod;
			tmp[++nc]={p[j]+1,nx-1,s};
		}
		cnt=0;
		for(j=1;j<=nc;j++){
			if(dp[cnt].r==tmp[j].l-1){
				dp[cnt].r=tmp[j].r;
				dp[cnt].res+=tmp[j].res;
				dp[cnt].res%=mod;
			}
			else dp[++cnt]=tmp[j];
		}
		ls=i;
	}
	int rh=n-dx[ls]+1;
	long long sum=0;
	for(i=1;i<=cnt;i++)sum+=dp[i].res*(dp[i].r-dp[i].l+1)%mod,sum%=mod;
	cnt=1;dp[1]={1,m,sum};
	dp[1].res=dp[1].res*ksm(m,rh-1)%mod;
	long long ans=0;
	for(i=1;i<=cnt;i++)ans+=dp[i].res,ans%=mod;
	printf("%lld",ans);
}
```

---

## 作者：Caged_Bird (赞：0)

# P9221 解题报告 

## 解题思路

首先考虑朴素 dp，设 $dp_{i,j}$ 表示走到第 $i$ 行第 $j$ 列的方案数，转移：  
$$dp_{i,j}=\sum dp_{i-1,k}$$
其中 $k$ 表示第 $i$ 行可以走到 $j$ 的列。   
比如如果第 $i$ 行是下面这种情况：  
![qwq](https://cdn.luogu.com.cn/upload/image_hosting/bntn3tqj.png)
当 $j=3$ 时，$2,3,4$ 都可以走到 $j$，所以 $dp_{i,3}=dp_{i-1,2}+dp_{i-1,3}+dp_{i-1,4}$。  
同理，当 $j=2$ 或 $j=4$ 时他们的 $dp$ 值都和 $dp_{i,3}$ 相等。  
容易发现每次转移都是区间求和和区间赋值的形式，并且可以压维，那么可以考虑线段树优化。  

又容易发现 $n\leq 10^9,m\leq 10^9$。  
所以一般的线段树在 $m$ 上空间会炸，在 $n$ 上时间会炸。  
发现 $q$ 很小，意味着有很多行都可能没有障碍。  
考虑没有障碍的两行，转移时等同于全局乘 $m$。  
所以没有障碍的行可以通过快速幂来实现跳跃。  
这样对线段树的调用次数就是 $O(q)$，解决了时间问题。  
使用动态开点线段树解决空间问题。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 100005
using namespace std;
inline void print(int n){if(n<0){putchar('-');print(-n);return;}if(n>9)print(n/10);putchar(n%10+'0');}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch==EOF)return 0;if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();if(ch==EOF)break;}return x*f;}
struct point{
    int x,y;
}a[N];
int p[N];
struct node{
    int s,t,v,p,ls,rs;
}tree[3000000];
int tot,n,m,q,tot1;
unordered_map<int,vector<int> >mp;
int add(int l,int r){
    tree[++tot].s=l;
    tree[tot].t=r;
    tree[tot].v=tree[tot].p=tree[tot].ls=tree[tot].rs=0;
    return tot;
}
void push_down(int now){
    tree[tree[now].ls].v=tree[now].p*(tree[tree[now].ls].t-tree[tree[now].ls].s+1)%mod;
    tree[tree[now].ls].p=tree[now].p;
    tree[tree[now].rs].v=tree[now].p*(tree[tree[now].rs].t-tree[tree[now].rs].s+1)%mod;
    tree[tree[now].rs].p=tree[now].p;
    tree[now].p=0;
}
void modify(int now,int l,int r,int k){
    if(tree[now].s>r||tree[now].t<l)return;
    if(tree[now].s>=l&&tree[now].t<=r){
        tree[now].v=(tree[now].t-tree[now].s+1)*k%mod;
        tree[now].p=k;
        return;
    }
    int mid=(tree[now].s+tree[now].t)>>1;
    if(!tree[now].ls)tree[now].ls=add(tree[now].s,mid);
    if(!tree[now].rs)tree[now].rs=add(mid+1,tree[now].t);
    if(tree[now].p)push_down(now);
    modify(tree[now].ls,l,r,k);
    modify(tree[now].rs,l,r,k);
    tree[now].v=(tree[tree[now].ls].v+tree[tree[now].rs].v)%mod;
}
int query(int now,int l,int r){
    if(tree[now].t<l||tree[now].s>r)return 0;
    if(tree[now].s>=l&&tree[now].t<=r)return tree[now].v;
    int mid=(tree[now].s+tree[now].t)>>1;
    if(!tree[now].ls)tree[now].ls=add(tree[now].s,mid);
    if(!tree[now].rs)tree[now].rs=add(mid+1,tree[now].t);
    if(tree[now].p)push_down(now);
    return (query(tree[now].ls,l,r)+query(tree[now].rs,l,r))%mod;
}
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b/=2;
    }
    return res;
}
signed main(){
    n=read();m=read();q=read();
    for(int i=1;i<=q;i++){
        a[i].x=read();a[i].y=read();
        mp[a[i].x].push_back(a[i].y);
    }
    add(1,m);
    tree[1].v=m;tree[1].p=1;
    for(int i=1;i<=q;i++){
        if(p[tot1]!=a[i].x)p[++tot1]=a[i].x;
    }
    for(int i=1;i<=tot1;i++){
        if(p[i]-p[i-1]>1)modify(1,1,m,query(1,1,m)*qpow(m,p[i]-p[i-1]-2)%mod);
        int j=0;
        for(;j<mp[p[i]].size();j++){
            modify(1,mp[p[i]][j],mp[p[i]][j],0);
            if(j==0)modify(1,1,mp[p[i]][j]-1,query(1,1,mp[p[i]][j]-1));
            else modify(1,mp[p[i]][j-1]+1,mp[p[i]][j]-1,query(1,mp[p[i]][j-1]+1,mp[p[i]][j]-1));
        }
        if(j!=0)modify(1,mp[p[i]][j-1]+1,m,query(1,mp[p[i]][j-1]+1,m));
        else modify(1,1,m,query(1,1,m));
    }
    if(p[tot1]<=n-1)modify(1,1,m,query(1,1,m)*qpow(m,n-p[tot1]-1)%mod);
    cout<<query(1,1,m);
    return 0;
}
```

---

## 作者：Na2PtCl6 (赞：0)

这题感觉和 [Ezzat and Grid](https://codeforces.com/problemset/problem/1557/D) 这个经典题还是有很多相似之处的。比如处理上，把有标记的行拎出来，然后从前往后扫。两个题都是很典型很基础的数据结构优化 DP 题，很值得做。

设 $f(i,j)$ 为从最底行到 $(i,j)$ 的方案数。

首先，如果没有障碍，转移方程是长这样的 $\displaystyle f(i,j)=\sum_{k=1}^n f(i-1,k)$，边界条件为 $f(1,i)=1(1 \leq i \leq n)$。最后一行的 $f(m,i)$ 之和其实就是 $m^{n+1}$

如果有障碍，那么上一个转移方程中的 $k$ 就要被障碍物限制住了，并且对于同一行两个障碍物之间的 $k$，$f(i,k)$ 全都是相等的，这就使得我们可以用数据结构来优化这个问题。

所以，我们就按顺序处理每一行就好了，对于没有障碍物的行就直接快速幂。

---

