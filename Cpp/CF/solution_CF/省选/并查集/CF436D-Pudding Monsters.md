# Pudding Monsters

## 题目描述

Have you ever played Pudding Monsters? In this task, a simplified one-dimensional model of this game is used.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF436D/cac747e35122b81f9dbf605774cf18b365c5306d.png)Imagine an infinite checkered stripe, the cells of which are numbered sequentially with integers. Some cells of the strip have monsters, other cells of the strip are empty. All monsters are made of pudding, so if there are two monsters in the neighboring cells, they stick to each other (literally). Similarly, if several monsters are on consecutive cells, they all stick together in one block of monsters. We will call the stuck together monsters a block of monsters. A detached monster, not stuck to anyone else, is also considered a block.

In one move, the player can take any block of monsters and with a movement of his hand throw it to the left or to the right. The selected monsters will slide on until they hit some other monster (or a block of monsters).

For example, if a strip has three monsters in cells $ 1 $ , $ 4 $ and $ 5 $ , then there are only four possible moves: to send a monster in cell $ 1 $ to minus infinity, send the block of monsters in cells $ 4 $ and $ 5 $ to plus infinity, throw monster $ 1 $ to the right (it will stop in cell $ 3 $ ), throw a block of monsters in cells $ 4 $ and $ 5 $ to the left (they will stop in cells $ 2 $ and $ 3 $ ).

Some cells on the strip are marked with stars. These are the special cells. The goal of the game is to make the largest possible number of special cells have monsters on them.

You are given the numbers of the special cells on a strip as well as the initial position of all monsters. What is the maximum number of special cells that will contain monsters in the optimal game?

## 样例 #1

### 输入

```
3 2
1 3 5
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2
1 3 4 6
2 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 2
1 8 4 5
7 2
```

### 输出

```
1
```

# 题解

## 作者：RedreamMer (赞：4)

  怎么都写的 $\mathcal O(nm)$？

  这题有很多优美的结论。

  首先，因为最后一定是拼接成若干个区间，对于每个区间，假设初始由 $m$ 个块拼接而成，那么一定移动了 $m - 1$ 步，因此必然有一个块没移动，因此每个区间可以看成以一个块为基点，两侧（或一侧）的块不断移向这个基点。

  其次，考虑最优方案长什么样，对于一个区间 $[l, r]$，令基点为 $x$，那么可以断言，$(a_{x - 1}, a_x]$ 必然有至少一个目标点，不然的话，没必要把 $[l, x)$ 移过来，同理，$[a_x, a_{x + 1})$ 必然有至少一个目标点。

  有了这个结论就好做了，为了方便，将每个区间拆成 $[l, x]$ 和 $[x, r]$ 两部分，对于前者，枚举这个区间中所包含的目标点区间，因为固定了右基点，所以左侧可以贪心选最少的点，因此可以将目标点区间对应到原序列上点的区间。

  然后有了 $m ^ 2$ 个贡献区间，问题就变成选一些不相交的区间，做一个线性 DP 就行了，注意端点上的细节。

  时间复杂度 $\mathcal O(n \log n + m ^ 2)$。

---

## 作者：ax_by_c (赞：0)

首先排序，并求出初始时所有的布丁块 $[l_i,r_i]$ 和长度的前缀和 $sum_i$。

考虑 DP，设 $f_i$ 表示前面的若干块移到 $i$ 前面后 $1$ 到 $i$ 覆盖特殊位置最大个数，$f'_i$ 表示 $i$ 和前面的若干块移到前面后 $1$ 到 $i$ 覆盖特殊位置最大个数。

为了接近可能的复杂度 $O(nm)$，我们在转移时枚举这一段覆盖的最远的特殊位置，并用双指针求出最少需要移动的块数，但这样是 $O(n^2)$ 的。

注意到 $r_i-sum_i$ 是单调不减的，所以同一个特殊位置的双指针可以放到一起做，时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+5;
const int M=2005;
int n,m,a[N],b[M],kk,f[N],ff[N],sum[N],lp[M],rp[M];
pii as[N];
void slv(){
	scanf("%d %d",&n,&m);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,1,m)scanf("%d",&b[i]);
	sort(a+1,a+1+n),sort(b+1,b+1+m);
	rep(i,1,n){
		if(!kk||as[kk].second+1!=a[i])as[++kk]={a[i],a[i]};
		else as[kk].second++;
	}
	n=kk;
	rep(i,1,n)sum[i]=sum[i-1]+as[i].second-as[i].first+1;
	rep(i,1,m)lp[i]=rp[i]=-1;
	int pos=0;
	rep(i,1,n){
		f[i]=max(f[i],ff[i-1]);
		while(pos<m&&b[pos+1]<=as[i].second)pos++;
		per(j,pos,1){
			if(lp[j]==-1)lp[j]=i;
			while(lp[j]>1&&sum[lp[j]-1]>b[j]-as[i].second+sum[i]-1)lp[j]--;
			while(lp[j]<i&&sum[lp[j]]<=b[j]-as[i].second+sum[i]-1)lp[j]++;
			if(1<=lp[j]&&lp[j]<=i&&sum[lp[j]-1]<=b[j]-as[i].second+sum[i]-1)f[i]=max(f[i],ff[lp[j]-1]+(pos-j+1));
		}
		ff[i]=max(ff[i],f[i]);
		rep(j,pos+1,m){
			if(rp[j]==-1)rp[j]=i+1;
			while(rp[j]<n&&sum[rp[j]]<b[j]-as[i].second+sum[i])rp[j]++;
			while(rp[j]>i+1&&sum[rp[j]-1]>=b[j]-as[i].second+sum[i])rp[j]--;
			if(i+1<=rp[j]&&rp[j]<=n&&sum[rp[j]]>=b[j]-as[i].second+sum[i])ff[rp[j]]=max(ff[rp[j]],f[i]+(j-pos));
		}
	}
	printf("%d\n",ff[n]);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

相信 $O(nm)$ 肯定能过。

设 $dp_i$ 表示用了前 $i$ 块布丁，且每块布丁都不再移动的最大覆盖数。

每次覆盖，必定是固定一块布丁，左边的一串和右边的一串向他靠拢。那么直接得到了 $O(n^2)$ 的暴力做法：

- 固定一块布丁；
- 计算他左边的布丁能产生的最大贡献；
- 更新右边布丁的答案。

注意到一共只有 $m$ 个关键点，所以本质不同的左边一串、右边一串只有 $O(m)$ 个。因此每一轮的枚举量都是 $O(m)$ 的，总复杂度为 $O(nm)$。

实现因人而异，你可能需要记录第 $i$ 块布丁的位置，和 $p$ 处布丁的排名。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,dp[MAXN],p[MAXN],id[MAXN],cov[MAXN],pre[MAXN],l[MAXN],r[MAXN],rev[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>p[i];
	ffor(i,1,m) cin>>cov[i];
	sort(p+1,p+n+1),sort(cov+1,cov+m+1);
	id[1]=1;
	ffor(i,1,n) rev[p[i]]=i;
	ffor(i,2,n) id[i]=id[i-1]+(p[i]!=p[i-1]+1);
	ffor(i,1,n) {
		if(!l[id[i]]) l[id[i]]=p[i];
		r[id[i]]=p[i];
	}
	ffor(i,1,id[n]) {
		int L=lower_bound(cov+1,cov+m+1,l[i])-cov-1,R=upper_bound(cov+1,cov+m+1,r[i])-cov;
		ffor(j,0,L) {
			int need=max(l[i]-cov[j+1],0);
			if(need<=rev[l[i]]-1) dp[i]=max(dp[i],dp[id[rev[l[i]]-need]-1]+R-L-1+L-j);
		}
		ffor(j,R-1,m) {
			int need=max(cov[j]-r[i],0);
			if(need<=n-rev[r[i]]) pre[id[rev[r[i]]+need]]=max(pre[id[rev[r[i]]+need]],dp[i]+j-R+1);	
		}
		dp[i]=max({dp[i],dp[i-1],pre[i]});
	}
	cout<<dp[id[n]];
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/436/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF436D)

u1s1 这题数据范围有点迷惑啊……乍一看 $\mathcal O(nm)$ 过不去，还以为是正解是 $\mathcal O(n+m^2)$ 呢。

考虑 $dp$，设 $f_i$ 表示用前 $i$ 个布丁，并且第 $i$ 个布丁要么不动，要么向左移动能够覆盖的最多特殊格子数，再设 $g_i$ 表示前 $i$ 个布丁，并且第 $i$ 个布丁的位置不发生变化所能覆盖的最多特殊格子数。

想好了 $dp$ 状态，转移就水到渠成了：

- 对于 $f_i$，要么第 $i$ 个布丁不动，即 $g_i\rightarrow f_i$，要么第 $i$ 个布丁向左移动，那么我们就枚举上一个不动的布丁 $j$，$g_j+sum(a_j+1,a_j+i-j)\rightarrow f_i$，其中 $sum(l,r)$ 表示 $[l,r]$ 中特殊格子的个数。
- 对于 $g_i$，枚举上一个不动或向左移动的布丁 $j$，那么显然布丁 $j+1,j+2,\dots,i-1$ 都会向右移动直到靠到 $i$ 上，即 $f_j+sum(a_i-i+j+1,a_i)\rightarrow g_i$。

当然也可以改写成以下形式：

- $f_j+sum(a_i-i+j+1,a_i)\rightarrow g_i$
- $g_i+sum(a_i+1,a_i+j)\rightarrow f_{i+j}$
- $g_i\rightarrow f_i$

这样暴力 $dp$ 是平方的，显然会炸，不过注意到特殊格子数量很少，考虑以此为突破口优化 $dp$ 转移。比方说拿转移方程 $f_j+sum(a_i-i+j+1,a_i)\rightarrow g_i$ 举例，注意到 $f_i\leq f_{i+1}$，而如果 $a_i-i+j+1$ 不是特殊格子，那么显然 $sum(a_i-i+j+1,a_i)=sum(a_i-i+j+2,a_i)$，故 $f_j+sum(a_i-i+j+1,a_i)=f_j+sum(a_i-i+j+2,a_i)\le f_{j+1}+sum(a_i-i+j+2,a_i)$，也就是说我们必定会从 $a_i-i+j+1$ 为特殊格子的 $j$ 转移来，故考虑转而枚举特殊格子，这样转移的复杂度就可降到 $\mathcal O(m)$ 了。

最后，上述转移方程忽略的“连续的布丁会粘在一起”这个条件，其实这也异常容易解决，考虑求出 $L_i$ 表示布丁 $i$ 所在的布丁块的左端点，$R_i$ 表示布丁 $i$ 所在的布丁块的右端点——这显然可以线性求出。然后直接从对应转移位置的左右端点转移而来即可。可能讲得不是特别清楚，具体见代码罢。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int MAXM=2e3;
const int MAXPOS=2e5;
int n,m,a[MAXN+5],b[MAXM+5],sum[MAXPOS+5];
int l[MAXN+5],r[MAXN+5],f[MAXN+5],g[MAXN+5];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);sort(a+1,a+n+1);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]),sum[b[i]]++;sort(b+1,b+m+1);
	for(int i=1;i<=MAXPOS;i++) sum[i]+=sum[i-1];
	a[0]=-MAXPOS;a[n+1]=MAXPOS+MAXPOS;
	for(int i=1;i<=n;i++) l[i]=(a[i-1]+1==a[i])?l[i-1]:i;
	for(int i=n;i;i--) r[i]=(a[i+1]-1==a[i])?r[i+1]:i;
	for(int i=1;i<=n;i++){
		f[i]=max(f[i],f[i-1]+sum[a[i]]-sum[a[i]-1]);
		g[i]=max(g[i],f[i-1]+sum[a[i]]-sum[a[i]-1]);
		for(int j=1;j<=m&&b[j]<a[i];j++) if(a[i]-b[j]<i){
			chkmax(g[i],f[l[i-a[i]+b[j]]-1]+sum[a[i]]-sum[b[j]-1]);
		}
		chkmax(f[i],g[i]);
		for(int j=m;j&&b[j]>=a[i];j--) if(b[j]-a[i]<=n-i){
			chkmax(f[r[i+b[j]-a[i]]],g[i]+sum[b[j]]-sum[a[i]]);
		}
	} printf("%d\n",f[n]);
	return 0;
}
```



---

