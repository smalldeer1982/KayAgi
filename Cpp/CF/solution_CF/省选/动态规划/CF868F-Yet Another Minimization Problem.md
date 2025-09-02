# Yet Another Minimization Problem

## 题目描述

给定一个序列 $a$，要把它分成 $k$ 个子段。每个子段的费用是其中相同元素的对数。求所有子段的费用之和的最小值。

## 说明/提示

$2 \leq n \leq 10^5$，$2 \leq k \leq \min(n,20)$，$1 \leq a_i \leq n$ 。

## 样例 #1

### 输入

```
7 3
1 1 3 3 3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 2
1 2 1 2 1 2 1 2 1 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
13 3
1 2 2 2 1 2 1 1 1 2 2 1 1
```

### 输出

```
9
```

# 题解

## 作者：vectorwyx (赞：110)

最暴力的做法是令 $dp_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的最小费用，转移方程为 $dp_{i,j}=\min_{k=1\sim i} (dp_{k-1,j-1}+calc(k,i))$，其中 $calc(k,i)$ 表示  $a[k,i]$ 这段区间的费用。

而这个 dp 在 $j$ 不变，$i$ 向右移时显然具有决策单调性。因为如果 $i$ 往右移了一位（$i=i+1$），有 $calc(k,i+1)=calc(k,i)+\sum_{w=k}^{i}[a_{w}=a_{i+1}]$ ，也就是说 $a[k,i]$ 这段区间有多少个数和 $a_{i+1}$ 相等，$calc(k,i+1)$ 相比于 $calc(k,i)$ 就会增加多少。所以 $k$ 越靠左 $calc(k,i+1)$ 的增量就越大，如果说在 $i$ 右移一位之前决策点 $u$ 的值 $dp_{u,j-1}+calc(u,i)$就大于等于决策点 $v$ 的值 $dp_{v,j-1}+calc(v,i)(u<v)$，那在 $i$ 右移之后，两者的前一项不变，而 $calc(u,i+1)$ 的增量一定大于等于 $calc(v,i+1)$ 的增量，所以决策点 $u$ 的值仍然会大于等于决策点 $v$ 的值。综上，当 $i$ 右移时，最优决策点只可能右移不可能左移。

接着考虑利用决策单调性来减少枚举量。借鉴一下分治的思路，把 dp 的第二维放到外层，也就是先枚举段数 $k$。如果我们知道了 $[1,n]$ 这段区间的中点 $M$ 的 dp 值以及它的最优决策点 $p$，那 $[1,M]$ 这段区间的每个点的所有可能的最优决策点组成的区间（以下简称“最优决策区间”）就会缩小为 $[1,p]$，同理，$[M+1,n]$ 这段区间的最优决策区间就缩小为 $[p+1,n]$。这样递归地分治下去，最多会递归 $\log n$层。

同时，如果我们能 $O(1)$ 地计算某段区间的费用 $calc(l,r)$，那每层的复杂度就是这一层的每次递归的最优决策区间之和，也就是 $O(n)$。但问题来了，如何 $O(1)$ 地计算 $calc$ 呢？我们借鉴一下莫队的手法，做一个类莫队暴力。即：我们记录上一次计算的区间的左右端点、对应的桶、对应的 $calc$ 值，然后对于目前要计算的区间，不断地挪动上一次的区间并更新记录的信息。但这样做的复杂度如何保证呢？首先，从区间 $[L,R]$ 的最后一次计算递归到 $[L,mid]$  的第一次计算最多会挪动 $O(R-L)$ 次。其次，同一层递归之间的区间挪动最多为 $O(n)$ 次（因为右端点和左端点都只会向右走）。这样均摊下来单次计算就是 $O(1)$ 的，故总时间复杂度为 $O(knlogn)$，轻松通过本题。

代码如下（点个赞再走吧QAQ，谢谢您！）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

const int N=2e5+5;
int a[N],cnt[N]={1},n,dep,l,r;
ll dp[N][25],sum;

inline ll calc(int aim_L,int aim_R){
	while(l>aim_L) sum+=cnt[a[--l]]++;
	while(r<aim_R) sum+=cnt[a[++r]]++;
	while(l<aim_L) sum-=--cnt[a[l++]];
	while(r>aim_R) sum-=--cnt[a[r--]]; 
	return sum;
}

void divi(int L,int R,int mnL,int mnR){//求区间[L,R]的dp值 且最优决策点在区间[mnL,mnR]内
	int mid=(L+R)>>1,pos,TL=max(1,mnL),TR=min(mid,mnR); 
	//printf("div(%d,%d,%d,%d) dep=%d,[TL,TR]=[%d,%d]\n",L,R,mnL,mnR,dep,TL,TR);
	ll mn=1e15;
	fo(i,TL,TR){
		//printf("F[%d,%d]=%lld\n",i,mid,calc(i,mid));
		ll val=dp[i-1][dep-1]+calc(i,mid);
		if(val<mn) mn=val,pos=i;
	}
	dp[mid][dep]=mn;
	//fo(i,TL,mid) cnt[a[i]]--;
	//printf("dp[%d][%d]=%lld,pos=%d\n",mid,dep,dp[mid][dep],pos);
	if(L==R) return;
	divi(L,mid,mnL,pos);
	divi(mid+1,R,pos,mnR);
}

int main(){
	int k;
	cin>>n>>k;
	fo(i,1,n) dp[i][0]=1e15;
	dp[0][0]=0;
	fo(i,1,n) a[i]=read();
	while(dep<=k){
		++dep;
		divi(1,n,1,n);
	}
	cout<<dp[n][k];
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：zhongyuwei (赞：44)

我们设$dp_{i,j}$表示将序列的前$i$个数划分成$j$段所需要的最小费用，设$w_{l,r}$表示将$l$到$r$划分成一段所需要的花费。那么显然有转移方程：$dp_{i,j} =min(dp_{x,j-1}+w_{x+1,i}) \text{ for }0\le x < i $。

而这个$dp$转移是具有决策单调性的。也就是说，$\forall i_1 < i_2$，假设它们分别是从$x_1,x_2$转移过来的，那么一定有$x_1\le x_2$。怎么证明呢？假设$x_1>x_2$， 那么由于$x_1,x_2$分别为$i_1,i_2$的决策点，一定有：$dp_{x_1,j-1}+ w_{x_1+1,i_1}\le dp_{x_2,j-1} + w_{x_2+1,i_1}$，$dp_{x_2,j-1} +w_{x_2+1,i_2} \le dp_{x_1,j-1} +w_{x_1+1,i_2}$。

如果$dp_{x_1,j-1}+ w_{x_1+1,i_1} = dp_{x_2,j-1} + w_{x_2+1,i_1}$且$dp_{x_2,j-1} +w_{x_2+1,i_2} = dp_{x_1,j-1} +w_{x_1+1,i_2}$，那么我们可以直接交换$x_1,x_2$两个决策点，决策单调性是成立的。

否则，这两个式子里面至少有一个取了小于符号。不妨假设是这样的：$dp_{x_1,j-1}+ w_{x_1+1,i_1}\le dp_{x_2,j-1} + w_{x_2+1,i_1}$，$dp_{x_2,j-1} +w_{x_2+1,i_2} < dp_{x_1,j-1} +w_{x_1+1,i_2}$。

移项可以得到：$w_{x_1+1,i_1}-w_{x_2+1,i_1}\le dp_{x_2,j-1} - dp_{x_1,j-1}$，$w_{x_1+1,i_2} - w_{x_2+1,i_2} > dp_{x_2,j-1} - dp_{x_1,j-1}$。

也就是$w_{x_1+1,i_1} -w_{x_2+1,i_1} < w_{x_1+1,i_2} - w_{x_2+1,i_2}$，即$w_{x_2+1,i_1}-w_{x_1+1,i_1} >  w_{x_2+1,i_2} - w_{x_1+1,i_2}$。这个式子是显然错误的，因为在区间的增加一个元素，它对答案的贡献是与这个区间内与它值相同的元素的数量相关的。固定右端点，左端点从$x_1$挪到$x_2$时答案的增量，右端点更靠右的一定更大。决策单调性得证。

接下来，我们可以利用决策单调性，将每一次转移的枚举量尽量减少。如果最先计算整个序列中间的那个点的转移，那么计算左右两半边的枚举量都可以减半。这样分治下去，每一层计算的复杂度是与整个序列的长度线性相关的。尽管对于$mid$，决策点不一定在靠近中间的地方，将“可能做决策的区间”划分给左右儿子时不一定是均匀的，但是，每一层的总复杂度，是与这一层所有区间的“可能做决策区间的长度”的和线性相关，这个和一定是与序列长度线性相关的。所以这里分治的复杂度是$n\log n$的。
``` cpp
//这里l,r表示要计算[l,r]的dp值，[lb,rb]是决策点可能存在的区间
void solve(int lb,int rb,int l,int r)
{
	if(lb>rb||l>r) return; int mid=l+r>>1;
	int d=0; ll res=1e18;
	for(int i=lb;i<=rb;++i)
	{
		ll tmp=cal(i+1,mid);
		if(res>dp[cur-1][i]+tmp) res=dp[cur-1][i]+tmp,d=i;
	}
	dp[cur][mid]=res;
	solve(lb,d,l,mid-1),solve(d,rb,mid+1,r);
}
```

还有一个问题需要解决：如何计算$w_{l,r}$。答案出奇地暴力：直接用类似与莫队的那种方法，暴力挪左右端点的指针！像这样：
``` cpp
int buc[N],L,R,a[N];
ll ans;
void update(int c,int d){ans+=d*buc[c]*(ll)(buc[c]-1)/2;}
ll cal(int l,int r)
{
	while(L<l) update(a[L],-1),buc[a[L]]--,update(a[L],1),L++;
	while(L>l) L--,update(a[L],-1),buc[a[L]]++,update(a[L],1);
	while(R<r) R++,update(a[R],-1),buc[a[R]]++,update(a[R],1);
	while(R>r) update(a[R],-1),buc[a[R]]--,update(a[R],1),R--;
	return ans;
}
```

实际上，左右端点的总移动距离是$O(n\log n)$的。这个结论的证明可以考虑一种放缩，我们考虑让左右端点先从父亲区间它所在的位置移到左儿子区间它所在的位置，分治完左儿子之后再移回父亲区间它所在的位置，然后再移到分治右儿子的时候它所在的位置。那么显然对于每一层，指针的移动次数是$O(n)$的，所以总复杂度是$O(n\log n)$的。

至此，这道题就在$O(kn\log n)$的时间解决了。

完整代码：
``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void read(T &x)
{
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int N=1e5+10;
int buc[N],L,R,a[N];
ll ans;
void update(int c,int d){ans+=d*buc[c]*(ll)(buc[c]-1)/2;}
ll cal(int l,int r)
{
	while(L<l) update(a[L],-1),buc[a[L]]--,update(a[L],1),L++;
	while(L>l) L--,update(a[L],-1),buc[a[L]]++,update(a[L],1);
	while(R<r) R++,update(a[R],-1),buc[a[R]]++,update(a[R],1);
	while(R>r) update(a[R],-1),buc[a[R]]--,update(a[R],1),R--;
	return ans;
}
ll dp[22][N]; int cur;
void solve(int lb,int rb,int l,int r)
{
	if(lb>rb||l>r) return; int mid=l+r>>1;
	int d=0; ll res=1e18;
	for(int i=lb;i<=rb;++i)
	{
		ll tmp=cal(i+1,mid);
		if(res>dp[cur-1][i]+tmp) res=dp[cur-1][i]+tmp,d=i;
	}
	dp[cur][mid]=res;
	solve(lb,d,l,mid-1),solve(d,rb,mid+1,r);
}
int main()
{
	memset(dp,0x3f,sizeof(dp)); dp[0][0]=0;
	int n,m; read(n),read(m);
	for(int i=1;i<=n;++i) read(a[i]); buc[a[1]]++,L=R=1;
	for(cur=1;cur<=m;++cur) solve(0,n-1,1,n);
	printf("%lld",dp[m][n]);
	return 0;
}
```

---

## 作者：FlashHu (赞：24)

貌似做所有的DP题都要先搞出暴力式子，再往正解上靠。。。

设$f_{i,j}$为前$i$个数分$j$段的最小花费，$w_{l,r}$为$[l,r]$全在一段的费用。

$$f_{i,j}=\min\limits_{k=1}^{i}\{f_{k,j-1}+w_{k,i}\}$$

显然$j$这一维可以滚掉，于是变成$g_i=\min\limits_{k=1}^{i}\{f_k+w_{k,i}\}$做$m$遍（题目中的$k$）

这又是一个决策单调性优化的式子。还是决策二分栈吗？要不得了，因为就算知道$i,k$也没法直接算$f_k+w_{k,i}$。

再次推广[蒟蒻的DP优化总结](https://www.cnblogs.com/flashhu/p/9480669.html)

分治。总结里的概述蒟蒻也懒得再㧟一遍了。。。就说说这题的实现细节吧。

---

$L^AT_EX$画图？（雾

求解区间：$|\gets$预处理$\to|$ $l\frac{\qquad\qquad\qquad\qquad\downarrow^{mid}\qquad\qquad\qquad\qquad}{}r$

决策区间：$L\frac{\qquad\qquad\qquad\qquad\qquad\downarrow^{k}\qquad\qquad\qquad\qquad}{}R$

---

设当前的求解区间为$[l,r]$，最优决策区间$[L,R]$。对于当前分治的中点$mid$，我们需要在$[L,\min(R,mid)]$中暴力找到最优决策$k$。注意到从$w_{l,r}$到$w_{l,r+1}$或者从$w_{l,r}$到$w_{l+1,r}$都是可以做到$O(1)$的，只要开一个桶记录当前区间每个颜色出现次数就可以啦。把指针$i$从$L$移到$\min(R,mid)$并不断的算$f_i+w_{i,mid}$，最终可以找到$k$。

注意一点，当进入求解区间时，我们的应该要确保$[L,l-1]$的信息的存在，这样才能保证分治的复杂度。

于是我们考虑进子问题之前如何先处理出子问题的答案。先看左边的子问题（$[l,mid-1],[L,k]$）显然和当前问题的$[L,l-1]$是一样的。注意到我们在求$k$的时候对$w$和桶都做了修改，那么我们直接还原回来就可以进左子问题了。

而右子问题呢？（$[mid+1,r],[k,R]$）它要预处理的是$[k,mid]$，而当前的是$[L,l-1]$。所以我们先把右端点指针从$l-1$移到$mid$，桶和$w$都加上去，再把左端点从$L$移到$k-1$，桶和$w$都减掉，接着进去就好了。回溯的时候还是要还原到$[L,l-1]$，因为上一层要接着用。

注意答案是long long级别的。

代码经过了精心排版（尤其是分治那一块）
```cpp
#include<cstdio>
#include<cstring>
#define RG register
#define R RG int
#define G c=getchar()
typedef long long LL;
const int N=1e5+9;
int a[N],c[N];
LL ff[N],gg[N],*f=ff,*g=gg;
inline int in(){
	RG char G;
	while(c<'-')G;
	R x=c&15;G;
	while(c>'-')x=x*10+(c&15),G;
	return x;
}
void solve(R l,R r,R kl,R kr,RG LL w){//kl,kr就是决策区间
	if(l>r)return;//边界
	R m=(l+r)>>1,k=0,p=m<kr?m:kr,i;
	for(i= l;i<=m;++i)w+=c[a[i]]++;//求k
	for(i=kl;i<=p;++i)w-=--c[a[i]],g[m]>f[i]+w?g[m]=f[i]+w,k=i:0;
	for(i=kl;i<=p;++i)w+=c[a[i]]++;//还原
	for(i= l;i<=m;++i)w-=--c[a[i]];
	solve(l,m-1,kl,k,w);
	for(i= l;i<=m;++i)w+=c[a[i]]++;//调整
	for(i=kl;i< k;++i)w-=--c[a[i]];
	solve(m+1,r,k,kr,w);
	for(i=kl;i< k;++i)++c[a[i]];//再次还原
	for(i= l;i<=m;++i)--c[a[i]];
}
int main(){
	R n=in(),k=in();
	RG LL*tmp;
	for(R i=1;i<=n;++i)//第一次直接算
		f[i]=f[i-1]+c[a[i]=in()]++;
	memset(c,0,(n+1)<<2);
	while(--k){
		memset(g,1,(n+1)<<3);
		solve(1,n,1,n,0);
		tmp=f;f=g;g=tmp;
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：CG__HeavenHealer (赞：13)


刚刚学完DP的各种玄学优化，所以过来~~赶紧水一发题解~~巩固一下知识。

### 题意

有一个长度为 $n$ 的序列，要求将其分成 $k$ 个子段，每个子段的花费是子段内相同元素的对数，求最小花费。

### 解法

首先想到暴力的DP，设 $f[i][j]$ 表示长度为 $i$ 的序列分成 $j$ 个子段后的最小花费，显然有： $f[i][j]=\min \{f[k][j-1] + val(k+1,i)\},k\in[1,i]$ ，$val$ 表示的是这一段的花费。

如果直接用上面的转移方程计算，复杂度是 $\Theta (n^2k)$ 。~~妥妥的TLE~~

所以我们要考虑优化。

可以看出，随着 $i$ 的增加，如果 $j$ 不变，显然 $f[i][j]$ 单调不降。所以， $f[i][j]$ 在向右转移时具有决策单调性。

可以简单口胡一下：如果后面的子段对答案有贡献，答案应该增加；否则，由于答案取的是前一段的最小值并且要加上一个 $val$ ，所以不会导致答案比以前更小，即使 $val = 0$ ，答案也是不降的。

由此，我们可以祭出这篇题解的主角：**分治决策优化DP**。

由于答案单调，所以我们可以二分，设现在等待转移的区间为 $[l,r]$ ，可以转移过来的决策所在区间为 $[ql,qr]$ ，那么对于每一次查找，我们可以定义一个 $mid$ 为 $l,r$ 的中点，然后递归求解。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/sp3t3q9b.png)

分治优化DP模板——代码片段（摘自OI-WIKI）

```cpp
void DP(int l, int r, int k_l, int k_r) {
  int mid = (l + r) / 2, k = k_l;
  // 求状态f[mid]的最优决策点
  for (int i = k_l; i <= min(k_r, mid - 1); ++i)
    if (w(i, mid) < w(k, mid)) k = i;
  f[mid] = w(k, mid);
  // 根据决策单调性得出左右两部分的决策区间，递归处理
  if (l < mid) DP(l, mid - 1, k_l, k);
  if (r > mid) DP(mid + 1, r, k, k_r);
}
```

对于本题，我们可以用同样的思路，设 $qmid$ 为最优决策所在的位置，最开始置为 $ql$ ，然后遍历 $ql$ 到 $qr$ ，遇到答案可以更新的时候就更新答案和 $qmid$ ，之后递归求解。

```cpp
inline void solve(int l, int r, int ql, int qr, int tot) { 
    //l, r, ql, qr 如上所述，tot 代表当前的子段数。
    if (l > r) return;
    int mid = (l + r) >> 1, qmid = ql;
    for (ri i = ql; i <= min(qr, mid); i++) {
        int las = f[i - 1][(tot - 1) & 1] + val(i, mid); //计算此时决策区间对应的决策
        bool updated = (las < f[mid][tot & 1]); // 是否可以更新
        if (updated) f[mid][tot & 1] = las, qmid = i; // 更新答案和决策位置
    }
    solve(l, mid - 1, ql, qmid, tot);
    solve(mid + 1, r, qmid, qr, tot); // 递归求解
}
```

降低了DP的复杂度后，考虑怎样维护每个子段的花费。对于类似的计数问题，可以用~~暴力~~**莫队**求解。

不了解莫队的看这里——[莫队 - CG__HeavenHealer 的博客 - 洛谷博客 (luogu.com.cn)](https://www.luogu.com.cn/blog/375030/mu-dui)~~（自己推销自己）~~

莫队维护贡献数代码片段：

```cpp
namespace mocap {
int L = 1, R, ans, cnt[N], a[N];
inline void add(int x) { ans += cnt[x], cnt[x]++; }
inline void del(int x) { cnt[x]--, ans -= cnt[x]; }
inline int val(int l, int r) {
    while (L > l) add(a[--L]);
    while (L < l) del(a[L++]);
    while (R > r) del(a[R--]);
    while (R < r) add(a[++R]);
    return ans;
}
}  // namespace mocap
```

有了这些，就可以求解本题了。

对了，还有一个小优化——第二维可以用滚动数组优化。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 1e5 + 10, K = 25;
inline int read() {
    ri x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f * x;
}
int f[N][2];
namespace mocap {
int L = 1, R, ans, cnt[N], a[N];
inline void add(int x) { ans += cnt[x], cnt[x]++; }
inline void del(int x) { cnt[x]--, ans -= cnt[x]; }
inline int val(int l, int r) {
    while (L > l) add(a[--L]);
    while (L < l) del(a[L++]);
    while (R > r) del(a[R--]);
    while (R < r) add(a[++R]);
    return ans;
}
}  // namespace mocap
using namespace mocap;
inline void solve(int l, int r, int ql, int qr, int tot) {
    if (l > r) return;
    int mid = (l + r) >> 1, qmid = ql;
    for (ri i = ql; i <= min(qr, mid); i++) {
        int las = f[i - 1][(tot - 1) & 1] + val(i, mid);
        bool updated = (las < f[mid][tot & 1]);
        if (updated) f[mid][tot & 1] = las, qmid = i;
    }
    solve(l, mid - 1, ql, qmid, tot);
    solve(mid + 1, r, qmid, qr, tot);
}
signed main() {
    int n = read(), k = read();
    for (ri i = 1; i <= n; i++) a[i] = read();
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (ri i = 1; i <= k; i++) solve(1, n, 1, n, i & 1);
    printf("%lld\n", f[n][k & 1]);
    return 0;
}
/*
7 3
1 1 3 3 3 2 1

10 2
1 2 1 2 1 2 1 2 1 2

13 3
1 2 2 2 1 2 1 1 1 2 2 1 1
*/
```



---

## 作者：lahlah (赞：6)

[CF868F Yet Another Minimization Problem](https://www.luogu.org/problem/CF868F)
###  题目大意比较清楚，这里就不扯了
最朴素的做法是直接 $O(n^2k) \ \ \ DP$

发现会T上天

然后就有了决策单调性优化

意思就是设$dp[i][j]$  表示前$i$个数，分成$j$段的最小值是多少

然后如果$dp[i][j]$ 是由 $dp[k][j-1]$转移过来的，那么$dp[i-1][j]$ 一定是从$dp[l][j-1]$转移过来的$(l<=k)$

具体证明要推推式子,这里就省略了

然后怎么做呢?

直接维护肯定是比较麻烦的（涉及到每个数出现的个数)

可以考虑先把dp数组分成k层

然后发现每次都是从上一层的转移过来的

然后再设

$calc(l, r, ll, rr)$表示$dp[l.....r][k]$的$dp$值是由$dp[ll.......rr][k-1]$转移过来的

然后就发现这个东西是可以二分（分治）的

令$mid = (l + r) / 2$

然后找到$dp[mid][k]$的最优决策点$p$

然后再分治处理$calc(l, mid - 1, ll, p)$ 和 $calc(mid + 1, r, p, rr)$

然后就行了

关于费用的计算就直接像莫队一样移动一下L，R就行了（反正一共只会移动 $nlogn$次）

代码可能好懂一些

代码中的dp数组的两维是反的

code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int L = 1, R, f[23][N], a[N], cnt[N], n, m, ans, cur;
void get(int l, int r){//动态算一下贡献
	while(L < l) cnt[a[L]] --, ans -= cnt[a[L]], L ++;
	while(R > r) cnt[a[R]] --, ans -= cnt[a[R]], R --;
	while(L > l) L --, ans += cnt[a[L]], cnt[a[L]] ++;
	while(R < r) R ++, ans += cnt[a[R]], cnt[a[R]] ++;
}
void calc(int l, int r, int ll, int rr){//如上面说的
	if(l > r) return;
	int p = 0, mid = (l + r) >> 1;
	for(int i = ll; i <= min(rr, mid - 1); i ++){//找dp[cur][mid]的最优决策点
		get(i + 1, mid);
		if(f[cur - 1][i] + ans < f[cur][mid]) 
			f[cur][mid] = f[cur - 1][i] + ans, p = i;
	}
	calc(l, mid - 1, ll, p);//分治处理
	calc(mid + 1, r, p, rr);
}
signed main(){
	memset(f, 0x3f, sizeof f);
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i ++) get(1, i), f[1][i] = ans;//初始化
	for(int i = 2; i <= m; i ++) cur = i, calc(1, n, 0, n - 1);//一层层计算
	printf("%lld", f[m][n]);//输出
	return 0;
}
```

[打个广告](https://blog.csdn.net/qq_38944163/article/details/100607136)

---

## 作者：摸鱼酱 (赞：4)

[CF868F Yet Another Minimization Problem](http://codeforces.com/problemset/problem/868/F)

给定序列 $a_{1\cdots n}$，将其划分为 $k$ 个子段，一个子段 $[l,r]$ 的代价 $c(l,r)$ 为 $l\leq i<j\leq r,a_i=a_j$ 的 $(i,j)$ 的数量，最小化所有子段的代价和。

$2\leq n\leq 10^5$，$2\leq k\leq 20$，$1\leq a_i\leq n$。

考虑题意为转移 $f_i=\min_{i'<i}\{f_{i'}+c(i'+1,i)\}$ 做 $k$ 次，即 $f_{i,j}$ 为前 $i$ 个恰好分成 $j$ 段的答案压掉了 $j$ 一维。

因为复杂度不太能做，我们挖掘一下性质考虑优化，若 $i_1<i_2$，它们的转移点为 $i'_1,i'_2$，则有 $i'_1\leq i'_2$，即满足决策单调性，证明如下：

假设存在 $i_1<i_2,i'_1>i'_2$，则由于 $i'_1,i'_2$ 是决策点，有 $f_{i'_1}+c(i'_1+1,i_1)\leq f_{i'_2}+c(i'_2+1,i_1)$ 以及 $f_{i'_2}+c(i'_2+1,i_2)\leq f_{i'_1}+c(i'_1+1,i_2)$。我们将其相加再抵消掉两边的 $f$，为了简洁省略掉 $c$，得到 $(i'_1,i_1)+(i'_2+1,i_2)\leq (i'_2+1,i_1)+(i'_1+1,i_2)$，看着有点抽象，不妨画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2g236k1g.png)

下面的图示的点分别表示上面四个端点中间的三段，边表示计算连接的两个点之间的贡献，不难发现 $1$ 是大于等于 $2$ 而不是小于等于，因为其边集包含了 $2$ 的边集，故决策单调性成立。

于是进行一个分治 $\operatorname{solve}(l,r,ql,qr)$ 表示 $[l,r]$ 的决策点在 $[ql,qr]$ 中，计算出 $mid=\lfloor\frac{l+r}2\rfloor$ 位置的决策点 $qmid$ 后递归 $\operatorname{solve}(l,mid-1,ql,qmid),\operatorname{solve}(mid+1,r,qmid,qr)$，问题来到了如何计算 $qmid$。普通的题目在这里是暴力枚举 $[ql,qr]$ 找到决策点，但这题由于要计算 $c$，所以考虑用类似莫队的思想来完成这个过程，维护全局指针 $[L,R]$ 表示当前得到了 $c(L,R)$，每次要计算时暴力挪动端点，考虑这样移动端点的次数，从父节点的 $[ql,qr]$ 到 $[ql,qmid]$ 的移动或逆向进行至多是 $O(qr-ql)$ 的，每个区间的 $qr-ql$ 求和的级别是 $O(n\log n)$ 的，因为无论怎么切割，一层的总数是 $O(n)$，共 $O(\log n)$ 层分治；在每个分治区间中的挪动也至多是 $O(qr-ql)$ 的，故端点移动次数为 $O(n\log n)$，单次移动复杂度是 $O(1)$，于是在这里使用莫队的思想复杂度是正确的。

因为要做 $k$ 次，总复杂度 $O(kn\log n)$，[一份参考代码实现](https://www.luogu.com.cn/paste/9ft5s7ko)。

---

## 作者：huayucaiji (赞：3)

## 解法

这个题首先考虑最基础的 DP。

显然，我们可以令 $f_{i,j}$ 表示，考虑区间 $[1,i]$，分成 $j$ 段的最小费用。那么我们最后求得就是 $f_{n,k}$。

转移也显然：

$$f_{i,j}=\min\limits_{t=1}^i f_{t-1,j-1}+w_{t,i}$$

其中 $w_{t,i}$ 表示 $[t,i]$ 区间内的费用。

这个 DP 显然 $O(k\cdot n^2)$，要炸。由于 $k$ 很小，我们考虑优化到 $O(k\cdot n\log n)$。CF的少爷机肯定跑的了。

我们考虑用整体二分优化。

首先理解一点，我们令 $g_{i,j}$ 为 $f_{i,j}$ 的决策点，即，使得 $f_{i,j}$ 最小的那个 $t$。我们可以理性理解一下，$j$ 不变，随着 $i$ 增大，$g_{i,j}$ 一定单调不严格递增。想要证明的话可以用四边形不等式。~~这个读者自证不难。~~

其实我自己证过，是对的。

那我们考虑固定 $j$，计算区间 $[l,r]$ 内的 $f_{i,j}$ 的值。我们现在暴力求解 $f_{mid,j}$。为了表达方便，记 $p=g_{mid,j}$。由于我们上面提到的那个性质，$\forall t\in [l,mid-1]$ 的决策点一定在 $[l,p]$ 中，右半边同理。

这样，我们不停递归即可。我们可以发现，最多递归 $\log n$ 层，每层复杂度是 $O(n)$，再算上枚举 $j$ 的时间，总复杂度为 $O(k\cdot n\log n)$。

至于怎么计算 $w_{i,j}$，可以类比莫队。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10,INF=1e14; 

int n,m,nl,nr,tot;
int f[MAXN][22],a[MAXN],sum[MAXN];

int calc(int x) {
	return x*(x-1)/2;
}
void get(int l,int r) {
    //类比莫队
	while(nl<l) {
		tot-=calc(sum[a[nl]]);
		sum[a[nl]]--;
		tot+=calc(sum[a[nl]]);
		nl++;
	}
	while(nl>l) {
		nl--; 
		tot-=calc(sum[a[nl]]);
		sum[a[nl]]++;
		tot+=calc(sum[a[nl]]);
	}
	while(nr<r) {
		nr++; 
		tot-=calc(sum[a[nr]]);
		sum[a[nr]]++;
		tot+=calc(sum[a[nr]]);
	}
	while(nr>r)  {
		tot-=calc(sum[a[nr]]);
		sum[a[nr]]--;
		tot+=calc(sum[a[nr]]);
		nr--;
	}
}

void divide(int l,int r,int lp,int rp,int j) {
    //[lp,rp]为决策点的可能区间范围。
	if(r<l) {
		return ;
	}
	int mark=0;
	int mid=(l+r)>>1;
	int rrpp=min(rp,mid-1);
	f[mid][j]=INF;
	
	for(int p=lp;p<=rrpp;p++) {
		get(p+1,mid);
		//f[mid][j]=min(f[mid][j],f[p][j-1]+tot);
		if(f[mid][j]>f[p][j-1]+tot) {
			f[mid][j]=f[p][j-1]+tot;
			mark=p;
		}
	}
	divide(l,mid-1,lp,mark,j);
	divide(mid+1,r,mark,rp,j);
}

signed main() {
	cin>>n>>m;
	nl=1;
	for(int i=1;i<=n;i++) {
		a[i]=read();
	}
	for(int i=1;i<=n;i++) {
		get(1,i);
		f[i][1]=tot;
        //j=1特别计算
	}
	for(int i=2;i<=m;i++) {
		divide(1,n,1,n,i);
	}
	
	cout<<f[n][m]<<endl;
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：3)

洛谷的 RemoteJudge 炸了？

~~前阵子好像问过 wxw 类似的题。~~

朴素的做法是设 $f_{i,j}$ 表示分好了前 $i$ 个子段，第 $i$ 个子段以位置 $j$ 结尾的最优方案。

那么有 $f_{i,j}\leftarrow f_{i-1,k}+cost_{k+1,j}$。复杂度 $O(n^2k)$。

考虑优化。这个 $cost_{k+1,j}$ 很烦所以看看它有啥性质。我们考虑从左往右枚举 $j$，并考虑 $j$ 右移的过程中 $cost_{k+1,j}$ 的增量。容易发现这个增量是不增的。通俗来讲就是对于 $k<l$，$cost_{k+1,j}$ 增加的量一定不比 $cost_{l+1,j}$ 增加得少。那么就会发现每个位置的决策点是单调的。

对于决策单调性的问题，我们可以用分治的方式去解决。

感觉有点像整体二分，我们假设当前在 $solve(l,r,ql,qr)$ 表示 $f_{i,[l,r]}$ 的决策点在区间 $[ql,qr]$。

我们取中点 $mid=\frac{l+r}{2}$，枚举 $[ql,qr]$ 的每个决策点，暴力地算出 $mid$ 的最终决策点在 $qmid$。然后递归到 $solve(l,mid-1,ql,qmid)$ 和 $solve(mid+1,r,qmid,qr)$。

这样分治会有 $\log n$ 层，每次分治的时候决策点区间会分成两个相交 1 个位置的区间。所以这部分复杂度是 $O(n\log n)$。

瓶颈在于查询 $cost_{l,r}$。事实上我们可以类似莫队一样暴力地维护两个端点，然后暴力地去移动。

考虑这个做法的复杂度。我们发现从 $solve(l,r,ql,qr)$ 递归到 $solve(l,mid-1,ql,qmid)$ 的时候，两个端点刚好是 $mid$ 和 $qmid$。那么意味着每一层暴力移动的次数实际上是 $qr-ql$ 级别的。所以整体的移动次数依然是 $O(n\log n)$。

外面跑 $k$ 次，复杂度为 $O(nk\log n)$。

https://codeforces.com/contest/868/submission/192508661

---

## 作者：miaokehao (赞：3)

这明显是一道决策单调性dp

什么是决策单调性dp：这是一种dp对于i<j，假设i由fi转来，j由fj转来，则有fi<fj。这个性质我们可以用来进行分治，具体看我常数巨大的代码
```
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(4)
#pragma GCC optimize("Ofast,no-stack-protector")
#define res register ll
#define ll long long
#define N 100005
#define K 25
#define inf 0x3f3f3f3f
using namespace std;
ll n,k,f[K][N],l=1,r,num[N],sum,a[N];
bool used[N];
inline ll read()
{
  ll X=0,w=0;
  char ch=0;
  while(!isdigit(ch))
  {
    w|=ch=='-';
    ch=getchar();
  }
  while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
  return w?-X:X;
}
inline void rev(res x){
	if(used[x]^=1) sum+=num[a[x]]++;
	else sum-=--num[a[x]];
}
inline void solve(res L,res R){
	while(l>L) rev(--l);
	while(l<L) rev(l++);
	while(r<R) rev(++r);
	while(r>R) rev(r--);
}
inline void div(res now,res L,res R,res ql,res qr){
	if(L>R) return;
	res mid=L+R>>1,ans=ql;
	for(res i=min(mid,qr);i>=ql;i--){
		solve(i,mid);
		if(f[now][mid]>f[now-1][i-1]+sum) ans=i,f[now][mid]=f[now-1][i-1]+sum; 
	}
	div(now,L,mid-1,ql,ans);
	div(now,mid+1,R,ans,qr);
}
int main(){
	n=read(),k=read();
	for(res i=1;i<=n;i++)
	  a[i]=read();
	memset(f,inf,sizeof(f));
	f[0][0]=0;
	for(res i=1;i<=k;i++)
	  div(i,1,n,1,n);
	printf("%lld\n",f[k][n]);
	return 0;
}
```

---

## 作者：pokefunc (赞：1)

# CF868F Yet Another Minimization Problem

## Description

给定 $n,k$ 和长度为 $n$ 的数列 $a$，要求把 $a$ 划分成 $k$ 个无交集的非空连续子串，使得总代价最小。

子串 $a_l,a_{l+1},\dots,a_r$ 的代价定义为 $\sum_{l \le i < j \le r}[a_i=a_j]$。

$n \le 10^5,k \le \min(20,n)$

## Sol

决策单调性优化 DP。

首先不难想出暴力 DP 方程：定义 $f(i,k)$ 为前 $i$ 个元素划分成 $k$ 段的最小费用，则转移为
$$
f(i,k)=\min_{j<i}\{f(j,k-1)+w(j+1,i)\}
$$
边界 $f(i,1)=w(1,i)$。$w$ 是代价函数。

显然滚掉第二维，然后证明 $w$ 满足四边形不等式：
$$
w(i,j)+w(i+1,j+1)-w(i,j+1)-w(i+1,j) \\
=w(i,j)-w(i,j+1)+w(i+1,j+1)-w(i+1,j)\\
=-\sum_{p=i}^j[a_p=a_{j+1}]+\sum_{p = i+1}^{j}[a_p=a_{j+1}]\\
=-[a_i=a_{j+1}] \le 0
$$
于是 $f$ 具有决策单调性，可以套分治做。

但是还有一个问题：$w$ 函数并不方便 $O(1)$ 计算。

一种可行的思路考虑到每一层计算是右界固定为 $\mathrm{mid}$，使用类似莫队的方法，维护当前区间的答案暴力移动左右指针转移答案，这样的好处是每一层的指针移动量是与区间长度相同同阶，不影响时间复杂度。

时间复杂度 $O(kn\log n)$，不需要刻意卡常但是注意细节防止时间退化。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const int M=1e5+5;
template<typename Tp=int>inline Tp read(){Tp x(0);int op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
ll f[M][21],nw;
int cnt[M],a[M];
int n,m,cl=1,cr;
ll w(int l,int r){//计算代价
    while(cl>l)cl--,nw+=cnt[a[cl]]++;
    while(cr<r)cr++,nw+=cnt[a[cr]]++;
    while(cl<l)nw-=--cnt[a[cl]],cl++;
    while(cr>r)nw-=--cnt[a[cr]],cr--;
    return nw;
}
void dp(int l,int r,int kl,int kr,int p){//分治优化
    if(l>r)return;
    int mid=(l+r)>>1,k=kl;
    ll minn=f[k][p-1]+w(k+1,mid);
    for(int i=kl;i<=std::min(mid-1,kr);++i)if(minn>f[i][p-1]+w(i+1,mid))k=i,minn=f[i][p-1]+w(i+1,mid);
    f[mid][p]=minn;//注意：这里不能用w(k+1,mid)，否则指针复原无法优化时间
    dp(l,mid-1,kl,k,p);dp(mid+1,r,k,kr,p);
}
signed main(){
    n=read();m=read();cr=n;
    for(int i=1;i<=n;++i)a[i]=read();
    memset(f,0x3f3f,sizeof(f));
    for(int i=1;i<=n;++i)f[i][1]=(nw+=cnt[a[i]]++);
    for(int i=2;i<=m;++i)dp(1,n,1,n,i);
    printf("%lld\n",f[n][m]);
    return 0;
}
```

---

## 作者：lmgoat (赞：1)

设 $f[i][j]$ 表示前 $j$ 个数分成 $i$ 段的最小费用。有转移： $f[i][j]=\min_{0\le k<j}\{f[i-1][k]+w(k+1,j)\}$。

可以证明 $f[i][j]$ 有决策单调性。证明如下：

设 $i<j$，$t[i][j][k]$ 表示 $[j,k]$ 区间内等于 $i$ 的 $a$ 的个数。

$w(i+1,j)+w(i,j+1)=2w(i,j)-t[a[i]][i+1][j]+t[a[j+1]][i][j]$

$w(i,j)+w(i+1,j+1)=2w(i,j)-t[a[i]][i+1][j]+t[a[j+1]][i+1][j]$

$\because t[a[j+1]][i][j]\ge t[a[j+1]][i+1][j]$

$\therefore w(i+1,j)+w(i,j+1)\ge w(i,j)+w(i+1,j+1)$

$\therefore w(b,c)+w(a,d)\ge w(a,b)+w(c,d)\,(a<b<c<d)$

即 $w(i,j)$ 满足四边形不等式

所以 $f[i][j]$ 有决策单调性。

证毕。

现在问题就在于计算 $w(i,j)$。发现如果单独对于一个 $w(i,j)$ 计算不太好优化，但是如果已知 $w(i,j)$，要扩展到 $w(i+1,j)$ 或者 $w(i-1,j)$ 或者 $w(i,j+1)$ 或者 $w(i,j-1)$ 只需要维护桶就可以 $O(1)$ 实现。

所以可以用类似于莫队的方法，维护全局指针 $lc,rc$ 每次要计算一个区间 $[l,r]$ 就把指针一步一步移过去，在移的过程中维护 $w(lc,rc)$ 与桶 $t$ 数组。每次加入第 $i$ 个数对答案的贡献就是 $t[a[i]]$，删除第 $i$ 个数答案就减少 $t[a[i]]-1$。加入或删除后再更新 $t[a[i]]$ 的值即可。

所以现在需要使用一种算法，使得 $lc,rc$ 的移动次数在可以接受的复杂度内。因为有决策单调性，所以考虑分治。分治的参数 $(l,r,L,R,k)$ 表示当前在 $[l,r]$ 区间，$mid=\lfloor\frac{l+r}{2}\rfloor$，已经可以确定最优决策点在 $[L,R]$ 这个区间内，这轮 DP 是分的第 $k$ 段。每次在 $[L,R]$ 这个区间中暴力枚举，求出 $f[k][mid]$，与其最优决策点 $p$。然后递归到 $(l,mid-1,L,p)$ 和 $(mid+1,r,p,R)$。

因为分治中 $mid$ 的最优决策点 $p$ 在递归的每一层单调不降，而且每次往下递归时 $lc$ 往回走的部分在每一层的和也是 $O(n)$，所以 $lc$ 的移动次数是 $O(n\log n)$ 的。

而 $rc$ 在每个分治的区间内都是 $mid$，同样在递归的每一层中单调不降。每次往下递归时 $rc$ 往回走的部分在每一层的和也是 $O(n)$ 的，所以 $rc$ 的移动次数也是 $O(n\log n)$ 的。

所以每次从 $[1,n]$ 开始分治的时间复杂度是 $O(n\log n)$。因为要做 $k$ 次，所以总时间复杂度是 $O(kn\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x(0),f(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=100005,K=25,inf=LONG_LONG_MAX;
int a[N],f[K][N],t[N],lc=1,rc,res;
void add(int x) {res+=t[a[x]]++;}
void del(int x) {res-=--t[a[x]];}
int calc(int l,int r) {
	while(lc>l) add(--lc);
	while(rc<r) add(++rc);
	while(lc<l) del(lc++);
	while(rc>r) del(rc--);
	return res;
}
void solve(int l,int r,int L,int R,int k) {
	if(l>r) return;
	int mi=inf,mid=(l+r)>>1,tmp=L;
	for(int i=min(mid-1,R);i>=L;--i)
		if(f[k-1][i]+calc(i+1,mid)<mi) mi=f[k-1][i]+calc(i+1,mid),tmp=i;
	f[k][mid]=mi;
	solve(l,mid-1,L,tmp,k);
	solve(mid+1,r,tmp,R,k);
}
int n,k;
signed main() {
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	solve(1,n,0,0,1);
	for(int i=2;i<=k;++i) solve(1,n,0,n-1,i);
	cout<<f[k][n];
	return 0;
}
```

---

## 作者：hegm (赞：1)

### [CF868F Yet Another Minimization Problem](https://www.luogu.com.cn/problem/CF868F)

很容易想出暴力 dp 式子：

$dp_{i,j}$ 表示前 $i$ 个元素，分 $j$ 个块的最小花费。

转移：

$dp_{i,j}=\min\limits_{j\le x< i}(dp_{x,j-1}+cost(x+1,i)$。

复杂度 $O(n^2)$。

考虑如何优化，发现是线性 dp 于是考虑决策单调性以及斜率优化。

决策单调性：

我们假设 $i_1<i_2$ 需要证明 $x_1\le x_2$。

我们知道 $dp_{i_1,j}=dp_{x_1,j-1}+cost(x_1+1,i)$。
不妨使用反证法假设 $x_1>x_2$。

1. 因为 $x_1$ 为 $i_1$ 的决策点，我们就能知道 $dp_{x_1,j-1}+cost(x_1+1,i_1)\le dp_{x_2,j-1}+cost(x_2+1,i_1)$，如果不能保证这个性质，那么 $i_1$ 的决策点就会被 $x_2$ 替换掉。

2. 同理，因为 $x_2$ 为 $i_2$ 决策点，我们知道 $dp_{x_2,j-1}+cost(x_2+1,i_2)\le dp_{x_1,j-1}+cost(x_1+1,i_2)$。

我们将两式移项可得

1. $cost(x_1+1,i_1)-cost(x_2+1,i_1)\le dp_{x_2,j-1}-dp_{x_1,j-1}$

2. $cost(x_1+1,i_2)-cost(x_2+1,i_2)\ge dp_{x_2,j-1}-dp_{x_1,j-1}$

我们将两项连接起来并且去掉 $dp_{x_2,j-1}-dp_{x_1,j-1}$。

$cost(x_1+1,i_1)-cost(x_2+1,i_1)\le cost(x_1+1,i_2)-cost(x_2+1,i_2)$

当取 `=` 的时候， $x_1,x_2$ 效果相同。我们不做考虑。

$cost(x_1+1,i_1)-cost(x_2+1,i_1)< cost(x_1+1,i_2)-cost(x_2+1,i_2)$

这样不方便看，因为 $cost(x_1+1,i_1)<cost(x_2+1,i-1)$ 所以式子会是个负数，我们同时乘以 $-1$。

$cost(x_2+1,i_1)-cost(x_1+1,i_1)> cost(x_2+1,i_2)-cost(x_1+1,i_2)$

对于这个式子，对于同侧我们可以看做 $\vartriangle cost(x_2\to x_1,i)$。

那么我们思考 $i$ 的值对这个式子的影响：

当左端点从 $x_2$ 扫到 $x_1$ 时。如果左端点越靠左，能和 $x_2\sim x_1$ 中匹配的数越多，因此 $\vartriangle$ 也就越大。

因此当 $x_2<x_1$ 时，上述式子不成立。
所以 $x_1\ge x_2$。

接下来考虑如何快速求得 $cost$，我们发现，预处理出 $cost$ 和现场求出复杂度都很爆炸，我们考虑一个问题：

给你一个序列，多次询问 $l\sim r$ 范围内有多少对相同的数，很容易就能想到莫队，所以我们既可以借助独特的转移方式：分治来加快 $cost$ 的求解。

具体内容看代码

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1000006
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,a[N],num,dp[N][31],L,R,tot;
int vis[N];
void add(int x)
{
	x=a[x];
	tot+=vis[x];
	vis[x]++;
}
void del(int x)
{
	x=a[x];
	vis[x]--;
	tot-=vis[x];
}
int calc(int l,int r)
{
	while(L>l)add(--L);
	while(R<r)add(++R);
	while(L<l)del(L++);
	while(R>r)del(R--);
	return tot;
}
void solve(int pl,int pr,int l,int r)
{
	if(pl>pr||l>r)return ;
	int mid=(l+r)>>1,ans=100000000000000000,d=0;
	for(int i=pl,res,con=min(mid,pr);i<=con;i++)
	{
		res=calc(i+1,mid);
		if(ans>dp[i][num-1]+res)ans=dp[i][num-1]+res,d=i;
	}
	dp[mid][num]=ans;
	solve(pl,d,l,mid-1);solve(d,pr,mid+1,r);
}
signed main()
{
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	{
		num=i;
		L=R=1;tot=0;
		memset(vis,0,sizeof(vis));
		vis[a[1]]=1;
		solve(0,n-1,1,n);
	}
	cout<<dp[n][m]<<"\n";
	return 0;
}
```

记得开 `long long`。

---

## 作者：NaN_HQJ2007_NaN (赞：0)

[Yet Another Minimization Problem](https://www.luogu.com.cn/problem/CF868F)

神仙题。

第一眼看上去就是 DP。

定义 $f_{i,j}$ 表示当前点 $i$，分 $j$ 段的最小费用。

$f_{i,j}= \min(f_{i,j},f_{k,j-1}+val_{k+1,i})$

然后发现复杂度 $O(n^2k)$，直接 T 飞，需要优化。

我们发现 $j$ 那一维可以滚掉，也就是只考虑第一维，然后做 $j$ 次就行了，下面称 $f_{i,j}$ 为 $f_i$。

对于 $val_{i,j}$，我们发现当 $j$ 固定时，$i$ 越小，值越大 (废话。

接下来最关键的一步就是证明转移的最优决策点是单调不降的。

我们考虑反证法。

定义 $u$ 为当前点 $i$ 的最优决策点，$v$ 为 $i+1$ 的最优决策点。

那么 $f_u+\operatorname{val}(u+1,i) \le f_v+\operatorname{val}(v+1,i)$

若 $v < u$，则对于 $i+1$ 应当满足：$f_v+\operatorname{val}(v+1,i+1) \le f_u+\operatorname{val}(u+1,i+1)$

即：$f_v+\operatorname{val}(v+1,i)+ \Delta v \le f_u+\operatorname{val}(u+1,i)+ \Delta u$

根据之前发现的单调性，显然可以得出 $\Delta v \ge \Delta u$，即 $\Delta v-\Delta u \ge 0$。

所以移项可得 $f_u+\operatorname{val}(u+1,i) \ge f_v+\operatorname{val}(v+1,i)+(\Delta v-\Delta u)$，与前者矛盾，证毕。

接下来就可以用分治来优化了。

定义 $\operatorname{cal}(l,r,L,R)$ 为当前处理的区间 $[l,r]$ 和可能的最优决策点所在区间 $[L,R]$。

对于一个这样的函数，我们可以暴力找到 $mid=\left\lfloor l+r \right\rfloor$ 的最优决策点 p, 然后递归下去。

那么问题来了，怎么快速求出 $\operatorname{val}(l,r)$ 呢？直接莫队就行了！

复杂度 $O(kn \log n)$ 。

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5, inf = LLONG_MAX >> 1;
ll n, k, a[N], cnt[N], lm = 1, rm = 0, ans = 0, f[N], g[N];
void add(ll w) {
	ans += cnt[a[w]];
	++cnt[a[w]];
}
void del(ll w) {
	--cnt[a[w]];
	ans -= cnt[a[w]];
}
ll val(ll l, ll r) {
	while (lm > l) add(--lm);
	while (lm < l) del(lm++);
	while (rm > r) del(rm--);
	while (rm < r) add(++rm);
	return ans;
}
void dfs(ll l, ll r, ll L, ll R) {
	if (l > r) return;
	ll mid = (l + r) >> 1, mid2 = L, minn = inf;
	for (ll i = L; i <= min(R, mid); ++i) {
		if (f[i - 1] + val(i, mid) < minn) {
			minn = f[i - 1] + val(i, mid);
			mid2 = i;
		}
	}
	g[mid] = minn;
	dfs(l, mid - 1, L, mid2); dfs(mid + 1, r, mid2, R);
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (ll i = 1; i <= n; ++i) cin >> a[i], f[i] = inf;
	for (ll i = 1; i <= k; ++i) {
		dfs(1, n, 1, n);
		for (ll j = 1; j <= n; ++j) f[j] = g[j], g[j] = inf;
	}
	cout << f[n] << endl;
	return 0;
}
```


---

## 作者：lfxxx (赞：0)

写出如下的转移方程：

$f_{i,j} = \min(f_{k,j-1} + w(k+1,i))$。

$w(l,r)$ 表示区间 $[l,r]$ 产生的贡献，显然满足区间包含单调性和四边形不等式所以考虑原转移方程满足决策单调性，分治优化转移即可，同时我们用两个类似莫队的指针移动快速求解 $w(l,r)$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int inf = 1e18+7;
using namespace std;
const int maxn = 1e5+114;
int dp[maxn],f[maxn];//dp[i]=dp[j]+(j+1,i)
int cnt[maxn];
int a[maxn];
int w;
int n,k;
void add(int x){
	w+=cnt[x];
	cnt[x]++;
}
void del(int x){
	cnt[x]--;
	w-=cnt[x];
}
int lt,rt; 
void solve(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	while(rt>mid) del(a[rt]),rt--;
	while(rt<mid) rt++,add(a[rt]);
	int mi=inf,p=L;
	for(int i=L;i<=min(R,mid);i++){
		while(lt<i) del(a[lt]),lt++;
		while(lt>i) lt--,add(a[lt]);
		if(dp[i-1]+w<=mi){
			mi=w+dp[i-1];
			p=i;
		}
	}
	f[mid]=mi;
	solve(l,mid-1,L,p);
	solve(mid+1,r,p,R);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[0]=0;
	for(int i=1;i<=n;i++) f[i]=inf;
	for(int i=1;i<=k;i++){
		for(int i=1;i<=n;i++) dp[i]=f[i],f[i]=0;
		memset(cnt,0,sizeof(cnt));
		w=0;
		lt=1,rt=0;
		solve(1,n,1,n);
	}
	cout<<f[n];
}
```


---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF868F-Solution.html)
#### 题意

一个长度为 $n$ 的序列，要分为 $m$ 段，每段代价为段内相同数的对数，求总代价的最小值。

#### 分析

设 $cal(i,j)$ 表示段 $[i,j]$ 内的相同的数的对数，$dp_i$ 表示当前最后一段以 $i$ 为末端的最小总代价，则有转移方程：
$$
dp_i=\min\limits_{j=1}^{i-1}\{dp_j+cal(i,j)\}
$$
,需要优化。观察代价函数 $cal$，如图，

![](https://cdn.luogu.com.cn/upload/image_hosting/1t4ggje5.png)

可以发现上面蓝线左侧的黑色部分变到下面红色部分，即从包含变为相交，其代价减小的是上面蓝线右侧的黑色部分对左侧的贡献，增加的是下面蓝线右侧的黑色部分对左侧的贡献，容易发现增加的贡献小于减少的贡献。由于求的是最小值，因此发现代价函数满足包含劣于相交，即满足四边形不等式，因此 dp 满足决策单调性。

发现转移只需从上一层转移，因此可以使用分治优化，而代价函数可以用类似莫队的方法快速从相邻的转移，所以就做完了。

#### 核心代码

```cpp
int n,m,a[MAXN],L=1,R,res,f[MAXN],dp[MAXN],mp[MAXN];
inline void add(int x){res+=!mp[x]++;}
inline void del(int x){res-=!--mp[x];}
int cal(int l,int r){
    while(l>L) del(a[L++]);
    while(r<R) del(a[R--]);
    while(l<L) add(a[--L]);
    while(r>R) add(a[++R]);return res;
}
void solve(int l,int r,int pl,int pr){
    if(l>r) return;
    int p=0,mid=(l+r)>>1;dp[mid]=0;
    for(int i=pl;i<=qmin(pr,mid-1);i++)
        if(dp[mid]<f[i]+cal(i+1,mid)) dp[mid]=f[i]+cal(i+1,mid),p=i;
    solve(l,mid-1,pl,p);solve(mid+1,r,p,pr);
}
signed main(){
    qread(n,m);int i,j;for(i=1;i<=n;i++) qread(a[i]);mp[0]=1;
    for(i=1;i<=n;i++) dp[i]=f[i]=cal(1,i);m--;
    while(m--){
        solve(1,n,0,n-1);
        for(i=1;i<=n;i++) f[i]=dp[i];
    }printf("%lld\n",dp[n]);
    return 0;
}
```
[record](https://codeforc.es/problemset/submission/868/172034293)


---

