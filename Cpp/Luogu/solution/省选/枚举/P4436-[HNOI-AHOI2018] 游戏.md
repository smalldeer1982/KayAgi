# [HNOI/AHOI2018] 游戏

## 题目描述

一次小G和小H在玩寻宝游戏，有 $n$ 个房间排成一列，编号为 $1,2,\cdots,n$ ，相邻的房间之间都有一道门。其中一部分门上锁（因此需要有对应的钥匙才能开门），其余的门都能直接打开。现在小G告诉了小H每把锁的钥匙在哪个房间里（**每把锁有且只有一把钥匙与之对应**），并作出 $p$ 次指示：第 $i$ 次让小H从第 $S_i$ 个房间出发到 $T_i$ 个房间里。但是小G有时会故意在指令中放入死路，而小H也不想浪费多余的体力去尝试，于是想事先调查清楚每次的指令是否会存在一条通路。

你是否能为小H作出解答呢？

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/17503.png)

$1\le n,p\le 10^6$ ， $0\le m <n$ ， $1\le x,y,S_i,T_i<n$ 保证 $x$ 不重复

## 样例 #1

### 输入

```
5 4 5 
1 3
2 2 
3 1
4 4
2 5
3 5
4 5 
2 1
3 1```

### 输出

```
YES
NO
YES
YES
NO```

## 样例 #2

### 输入

```
7 5 4
2 2
3 3 
4 2 
5 3 
6 6
2 1
3 4
3 7
4 5```

### 输出

```
YES
YES
NO
NO```

# 题解

## 作者：Dreamunk (赞：24)

这题复杂度其实很靠谱的啊，不知道为什么这么多题解说是乱搞。

[题目](https://www.luogu.com.cn/problem/P4436)

显然只要求出从每个房间出发能到达的区间。

首先把中间没有锁的房间合并成一个。

考虑一个锁，如果它的钥匙在它左边，那么就不可能从右边打开这个锁；反之亦然。

为了方便，记钥匙在左边的锁为 `>`，钥匙在右边的锁为 `<`，房间为 `.`，那么这一列房间可以长成这种形状：
```
.<.<.<.>.>.<.
```
- 对于形如 `>.<` 的房间，它是永远出不去的，因此答案已经算出来了。

- 对于形如 `>.>` 的房间，它不能往左边走，考虑一直往右边扩张，扩张的方式是

	1. 答案区间 $[L,R]$ 初始为它本身
   2. 判断房间 $R$ 到房间 $R+1$ 的锁能不能开
   3. 如果开不了，扩张过程结束
   4. 如果开得了，$[L,R]$ 并上从 $R+1$ 出发的答案区间，然后返回第 2 步
  
  容易发现，这样的过程可以保证一个锁只会被判断一次。

- 对于形如 `<.<` 的房间，同上。

- 对于形如 `<.>` 的房间，甚至暴力往两边扩张都是对的，因为它再怎么扩张也只能扩张到形如 `>.<.<.<.<.<.>.>.>.>.>.<` 的这段房间的一部分，而对于每一个这样的段只会有一个这样的房间做了这个暴力，因此这部分还是线性。

但是实现起来就不用显式地分类讨论，因为四种情况其实都是扩张，写成一个记忆化搜索的样子。

你们的记忆化搜索当然也是长这个样子，所以复杂度也是 $O(n)$。

拓扑排序的做法也是等价的（毕竟拓扑排序后 DP 的题目基本上都可以记忆化搜索）。
```cpp
#include<bits/stdc++.h>
namespace io{
const int D=1<<21;
char buf[D],*s,*t;
inline char get(){return s==t&&(t=(s=buf)+fread(buf,1,D,stdin),s==t)?-1:*s++;}
inline int read(){
	int a=0;char c=get();
	for(;c< '0'||c> '9';c=get());
	for(;c>='0'&&c<='9';a=a*10+c-'0',c=get());
	return a;
}
}//namespace io
using io::read;
const int N=1e6+3;
int n,m,q,f[N],p[N],l[N],r[N],s[N],t[N];
void Dp(int x){
	if(s[x]&&t[x])return;
	bool fl;
	s[x]=l[x],t[x]=r[x];
	for(;;){
		fl=0;
		if(t[x]<n&&f[t[x]  ]>=s[x]&&f[t[x]  ]<=t[x]){
			Dp(p[t[x]+1]);
			t[x]=t[p[t[x]+1]];
			fl=1;
		}
		if(s[x]>1&&f[s[x]-1]>=s[x]&&f[s[x]-1]<=t[x]){
			Dp(p[s[x]-1]);
			s[x]=s[p[s[x]-1]];
			fl=1;
		}
		if(!fl)break;
	}
}
int main(){
	int x,y;
	n=read(),m=read(),q=read();
	for(int j=1;j<=m;j++)x=read(),y=read(),f[x]=y;
	for(int i=1;i<=n;i++)
		if(i==1||f[i-1])p[i]=l[i]=r[i]=i;
		else p[i]=p[i-1],r[p[i]]=i;
	for(int i=1;i<=n;i++)if(f[i])f[i]=p[f[i]];
	for(int i=1;i<=n;i++)if(p[i]==i)Dp(i);
	for(;q--;)x=read(),y=read(),puts(s[p[x]]<=y&&t[p[x]]>=y?"YES":"NO");
	return 0;
}
```

---

## 作者：ztzshiwo001219 (赞：23)

考场上写的程序,虚的不行,因为以为是$O(nlog^2n)$的,心想这能过?

~~然后就A了,因为其实是O(nlogn)的~~

这道题的做法和思路挺多的,我只讲讲我的...看到这个题发现每个点能够到达的点一定是一个区间$\left[ l_i,r_i \right]$,那么我们如果每一个点能够到达的区间找出来,询问就随便做了.

首先考虑$y \leq x$的数据,除了没有门的情况,一个点向左能够到达的点很容易算(因为知道碰到一个门就一定过不去,因为钥匙在门左边),这样向右能够到达的点就很好用单调栈实现了.

因为如果我们能够到达i号点,那么也就一定能到达$l_i,r_i$,我们拿一个单调栈记录右端点,每次如果能够到达更远就把当前点删掉(因为不可能再用到了),复杂度$O(n)$

部分代码:
```cpp
inline void init()
{
    key[n]=-1;
    For(i,1,n)l[i]=i;
    For(i,2,n)if(!key[i-1])l[i]=l[i-1];
    rFor(i,n,1)
    {
		st[++top]=i;
		while(top&&(key[st[top]]>=l[i]||!key[st[top]]))
			top--;
		r[i]=st[top];
    }
}

```

接下来考虑没有限制怎么做.同理,一个方向可以用单调栈维护,这个方向最多只需要拓展$O(n)$次,但是我们需要快速知道目前能够到达的点为$\left[l_i,r_i\right]$时,最多能向左边延展多远.根据前面的一个小结论,如果向左碰到一个钥匙在门左边的位置一定过不去,向右碰到一个钥匙在门右边的位置也一定过不去.可以方便$O(n)$算出左边和右边的限制$\left[L_i,R_i\right]$.

然后我们可以发现:对于左边的门(在左边的限制右边),只有当门的钥匙在$r_i$右边的时候才不能通过,右边同理(对于右边的门(在右边的限制左边),只有当门的钥匙在$l_i$左边的时候才不能通过).

我们要求目前能够到达的点为$\left[l_i,r_i\right]$时,最多能向左边延展多远,其实就是$\left[L_i,l_i-1\right]$内$key(x) >r_i$的第一个位置,就相当于求一段区间内最先遇到的第一个大于某个数的数的位置.这个东西我是用线段树做的:首先确定$O(logn)$个区间,对于每一个区间记录最大值后可以判断左右区间内有没有解,然后向其中一个方向走,这样就是$O(nlog^2n)$的,然而你只要对于那$O(logn)$个区间也判断一下,那么就只会有一个区间往下走,时间复杂度就是$O(nlogn)$的了...

$O(nlogn)$的代码:
```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define SZ(x) (int)x.size()
#define ft first
#define sd second
#define pb push_back
#define ls l,mid
#define rs mid+1,r
#define lc p<<1
#define rc p<<1|1
using namespace std;
typedef long long LL;
const int N=1000010;
const int inf=0x3f3f3f3f;
template<typename T>inline bool chkmax(T&A,const T&B){return A<B?A=B,1:0;}
template<typename T>inline bool chkmin(T&A,const T&B){return A>B?A=B,1:0;}
template<typename T>inline void read(T&x)
{
    x=0;int f=0;char ch=getchar();
    while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=f?-x:x;
}
inline void file()
{
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
}
int n,m,Q;
int key[N],p[N];
int l[N],r[N],st[N],top;
int lS[N],rS[N];
int t[N<<3];
inline void Build(int l,int r,int p)
{
    if(l==r){t[p]=key[l];return;}
    int mid=(l+r)>>1;
    Build(ls,lc),Build(rs,rc);
    t[p]=max(t[lc],t[rc]);
}
inline int Get(int l,int r,int p,int x)
{
    if(t[p]<=x)return 0;
    if(l==r)return l;
    int mid=(l+r)>>1;
    return t[rc]>x?Get(rs,rc,x):Get(ls,lc,x);
}
inline int Query(int l,int r,int p,int x,int y,int z)
{
    if(x<=l&&r<=y)return Get(l,r,p,z);
    int mid=(l+r)>>1,pos=0;
    if(y>mid)pos=Query(rs,rc,x,y,z);
    if(pos)return pos;
    if(x<=mid)pos=Query(ls,lc,x,y,z);
    return pos;
}
inline int find_pos(int l,int r,int x)
//the last pos_i in [l,r] that key[i]>r;
{
    if(l>r)return l;
    int pos=Query(1,n,1,l,r,x);
    return pos?pos+1:l;
}
inline void init()
{
    Build(1,n,1);
    key[n]=n+1;
    key[0]=-1;
    For(i,1,n)lS[i]=key[i-1]&&key[i-1]<=i-1?i:lS[i-1];
    rFor(i,n,1)rS[i]=key[i]&&key[i]>i?i:rS[i+1];
    rFor(i,n,1)
    {
		l[i]=r[i]=i;
		l[i]=find_pos(lS[i],l[i]-1,r[i]);
		st[++top]=i;
		while(top&&((l[i]<=key[st[top]]&&key[st[top]]<=r[i])||!key[st[top]]))
		{
			r[i]=st[--top];
			l[i]=find_pos(lS[i],l[i]-1,r[i]);
		}
    }
}
int main()
{
    int x,y;
    file();
    read(n),read(m),read(Q);
    For(i,1,m)read(x),read(y),key[x]=y;
    init();
    while(Q--)
    {
		read(x),read(y);
		printf("%s\n",l[x]<=y&&y<=r[x]?"YES":"NO");
    }
    return 0;
}

```

---

## 作者：DegChuZm (赞：15)

### sol
钥匙在门后面肯定是开不了门的。

一段联通的区间肯定可以缩成一个点，随手缩一个。

这里有一个比较优秀的性质：如果 $x$ 可以到 $y$ 这个点，那么 $x$ 一定可以用 $y$ 的答案。

你暴力去做的话肯定是对于每个点去看看能不能开这个门来暴力扩展，这时候就会有很多门是被重复更新的。

用上面那个性质，我们肯定希望更新一个新的区间时能用到以前区间的答案。

这个形式有点像拓扑。

考虑按照每个带锁的门来建边，如果 $x$ 门的钥匙在 $x$ 左边，则连接一条 $x+1 \to x$ 的边。

因为这个时候 $x+1$ 肯定到不了 $x$，我们若先更新 $x+1$，那么在更新 $x$ 的时候就可以使用 $x+1$ 的答案，而更新 $x$ 再更新 $x+1$ 就无法共用答案了。

然后跑拓扑，对于当前入度为 $0$ 的点直接暴力更新就可以了。

这是 $O(n)$ 的，你会发现每个带锁的门最多只会被开一次。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,qx,qy,cnt,tot,ptt,head[1000001],du[1000001],bl[1000001],x[1000001],y[1000001],L[1000001],R[1000001],lc[1000001];
int lf[1000001],rf[1000001];
struct dcz{
	int nex,to;
}a[2000001];
void add(int x,int y){
	a[++cnt].nex=head[x];
	a[cnt].to=y;
	head[x]=cnt;
}
void solve(int x){
	L[x]=lf[x],R[x]=rf[x];
	while(1){
		bool f=0;ptt++;
		assert(ptt<2e8); 
		if(R[x]<n&&lc[R[x]]<=R[x]&&lc[R[x]]>=L[x]){
			f=1;
			R[x]=R[bl[R[x]+1]];
		}
		if(L[x]>1&&lc[L[x]-1]<=R[x]&&lc[L[x]-1]>=L[x]){
			f=1;
			L[x]=L[bl[L[x]-1]];
		}
		if(!f) return;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		lc[x[i]]=y[i];
	}
	++tot;lf[tot]=1;
	for(int i=1;i<=n;i++){
		bl[i]=tot;
		if(lc[i]&&i!=n){
			rf[tot]=i;
			tot++;
			lf[tot]=i+1;
			if(lc[i]<=i) add(tot,tot-1),du[tot-1]++;
			else add(tot-1,tot),du[tot]++; 
		}
	}
	rf[tot]=n;queue<int> qq;
	for(int i=1;i<=tot;i++){
		if(!du[i]) qq.push(i);
	}
	while(qq.size()){
		int u=qq.front();qq.pop();
		solve(u);
		for(int i=head[u];i;i=a[i].nex){
			int v=a[i].to;
			if(!(--du[v])) qq.push(v);
		}
	}
	for(int i=1;i<=q;i++){
		cin>>qx>>qy;
		if(L[bl[qx]]<=qy&&R[bl[qx]]>=qy) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
/*
钥匙在门后面肯定开不了门。
先随手缩个点。 
这里有一个比较优秀的性质：
x 如果能到 l 这个点的话，那么 l 的答案肯定能到 x 上。
我们若想要这个比线性的话，肯定要从小到大更新区间，因为可以吃到之前更新的。 
考虑按照每个带锁的门来建边，若 x 门的钥匙在左边，则连一条 x+1->x，反之亦然。
对于每个入度为 0 的点我直接暴力更新，再搭上前面那个性质，这下显然每个空只会更新一次。 

这题是真的牛逼。 
*/
```

---

## 作者：w36557658 (赞：11)

本题解同步发布于：https://www.cnblogs.com/luyouqi233/p/9127342.html 觉得写的不错的话欢迎访问~

____________________________________

看洛谷题解里面清一色的暴力，连唯一正解也是用了奇技淫巧才过（当然本题解参考了那个题解）。

于是简单说一下“正解”（如有错误请指出orz）。

先从暴力开始，对于每个点我们暴力找到其能够到达的最大的区间$[l,r]$。

一个优化：我们在加入新的点进入这个区间的时候，可以把该点的答案区间合并进区间内。

接下来是正解，首先是对于每个门$i$，如果钥匙在其左边则$add(i+1,i)$，否则$add(i,i+1)$，其中边的含义是从入点无法到达出点。

于是对这个图拓扑排序后可发现，点$u$的答案区间一定不包含比其排名大的点，则在暴力优化的帮助下，我们可以证明出需要我们暴力更新的次数只有$O(n)$次。

但是为什么按照那篇题解所说，“初始化序列倒着加会快”呢？

我把数据下载下来才发现一个坑。

**对于不在拓扑图上的点，其更新后的答案区间可能会覆盖与它同级甚至比它排名小的点的答案区间，这样暴力优化就无用武之地，复杂度退化。**

所以我们**必须缩点，才能保证算法的复杂度**。

也就是说，实际上是因为数据构造问题，才使得“初始化序列倒着加会快”，是可以被卡掉的。

~~（话句话讲就是出题人都如此煞费苦心卡掉了复杂度不对的正解却让暴力AC了）~~

---

## 作者：老K (赞：8)

来一发暴力。

一个很显然的暴力是把连续无门房间变成一个，然后计算每个点能到达的左右边界。

就是两个指针l,r，记录当前的边界，然后每次左一步，右一步。直到走不动。

然后加个优化：l边界移动的时候，计算移动到位置能到达的左右端点，显然右端点到不了l，然后l直接变成那个左端点就行了。

快的飞起。

```C++
/*
Author: CNYALI_LK
LANG: C++
PROG: game.cpp
Mail: cnyalilk@vip.qq.com
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
typedef long long ll;
typedef pair<int,int> pii;
template<class T>int chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>int chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
#define min mmin
#define max mmax
#define abs aabs
int read(){
	int s=0,base=1;
	char c;
	while(!isdigit(c=getchar()))if(c=='-')base=-base;
	while(isdigit(c)){s=s*10+(c^48);c=getchar();}
	return s*base;
}
char WriteIntBuffer[1024];
template<class T>void write(T a,char end){
	int cnt=0,fu=1;
	if(a<0){putchar('-');fu=-1;}
	do{WriteIntBuffer[++cnt]=fu*(a%10)+'0';a/=10;}while(a);
	while(cnt){putchar(WriteIntBuffer[cnt]);--cnt;}
	putchar(end);
}
int is[1024242],a[1024242];
int l[1024224],r[1024224],vis[1024242];
void dfs(int x){
	if(vis[x])return;
	int _l=x,_r=x,ok;
	do{
		ok=0;
		if(_l<=a[_l-1]&&a[_l-1]<=_r){
			ok=1;
			dfs(_l-1);
			_l=l[_l-1];
		}

		if(_l<=a[_r]&&a[_r]<=_r){
			ok=1;
			dfs(_r+1);
			_r=r[_r+1];
		}
	}while(ok);
	l[x]=_l;
	r[x]=_r;
	vis[x]=1;
}
int main(){
#ifdef cnyali_lk
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int n,m,p,x,y;
	n=read();m=read();p=read();
	for(int i=1;i<=m;++i){
		x=read();y=read();
		a[x]=y;
	}
	is[1]=1;
	for(int i=1;i<=n;++i){
		is[i+1]=is[i];
		if(a[i]){
			++is[i+1];
		}
	}
	++m;
	for(int i=1;i<=n;++i)if(a[i]){
		a[is[i]]=is[a[i]];
	}
	for(int i=1;i<=m;++i)dfs(i);
	while(p){
		--p;
		x=is[read()];y=is[read()];
		if(l[x]<=y&&y<=r[x])printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}


```

---

## 作者：myyes (赞：5)

摘自我的博客文章：[钥匙题专项训练](https://www.luogu.com.cn/blog/666666new/keys-tm)。


题目描述：

一个链上的钥匙-锁模型。一个数轴上一些边可能有锁，给出这些锁对应的钥匙的位置。有 $q$ 个师傅要在迷宫上开车，给一个起点的位置 $s$，给一个北京的位置 $t$，现在师傅要开车去北京，每次可以随便往哪个方向走，每遇到一串钥匙就可以撇到皮带上面，可以通过一个边当且仅当师傅现在的皮带上拥有其对应的钥匙。给每个师傅求出他能不能走得到北京？

思路：

我们考虑进行一个板凳的坐。这个题本质上就是一个记忆化搜索哈，搜索就是坐板凳。我们考虑先把连续一段没有锁的板凳给锁到一起，然后从每个点开始搜索。注意到每个点能到的点是一个区间，我们每次搜索就考虑当前区间能不能向左向右扩展，看一下我们现在的区间是否包含扩展出去的锁的钥匙，写一个记忆化搜索来坐板凳就可以了得咩。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p,pos[1000010],zuo[1000010],you[1000010],wei[1000010],xia[1000010];
void dfs(int x)
 {
  if(zuo[x]&&you[x])return;
  zuo[x]=x,you[x]=xia[x];
   while (1){
  bool kue=0;
    if(zuo[x]> 1&&wei[pos[zuo[x]-1]]>=zuo[x]&&wei[pos[zuo[x]-1]]<=you[x])
      {
    kue=1;
    dfs(wei[zuo[x]-1]);
    zuo[x]=zuo[wei[zuo[x]- 1]];
  }
  if(you[x]<n&&wei[pos[you[x]]]>=zuo[x]&&wei[pos[you[x]]]<=you[x])
   {
    kue=1;
    dfs(wei[you[x] + 1]);
    you[x]=you[wei[you[x] +1]];
  } if (!kue) break;}}
int main()
 {
   scanf("%d%d%d",& n, &m ,&p );
  while(m--){int x,y;
 scanf("%d%d",&x,&y);pos[x]=y;
}
  for(int i=1;i<=n;++i)
 if(i==1||pos[i-1])
  wei[i]=xia[i]=i;
    else
   xia[wei[i]=wei[i -1]]= i;
   for(int i=1;i<=n;++i)
  if(wei[i]==i)
    dfs(i);
    while(p--){
   int S,T;
  scanf("%d%d",&S,&T);
    S=wei[S];
    if (T>=zuo[S]&&T<=you[S])
   printf("YES\n");
     else   printf("NO\n");
   }
return 0;
 }
```

---

## 作者：1kri (赞：5)

$AwA$ $OvO$ $QwQ$

---

一篇复杂度正确的题解

显然每个点可以到达的点一定是连续的区间，那么我们可以对于每组询问，求出 $S$ 能到达的区间 $[L,R]$ ，然后判断 $T$ 在不在此区间内。

---

我们可以先把没有锁的门缩成连通块，一下简称`块` 。

我们发现一共有三种`块`：

1. 只能向左边拓展的块
2. 只能向右边拓展的块
3. 两边都能拓展的块

---

前两种块本质相同，我们以第一种为例：

首先容易发现只有 $x \leq y$ 的钥匙才有意义。

那么我们可以对于每个块，枚举这个块内的所有钥匙。

我们用并查集维护每个块所在的`可以相互到达的块`的集合，并记录下可以到达的最左边的块。每次`开门`操作，就相当于把两个集合合并。

这一部分的时间复杂度是 $O((n+m)\cdot\alpha(n))$ 。

---

对于第三种块：

我们可以直接暴力 $O(n+m)$ 拓展每个第三种块。拓展的过程很简单，这里不再赘述。

我们来证明一下时间复杂度的正确：

对于两个相邻的块 $a$ 和 $b$ ，若 $a$ 可到达 $b$ ，则 $b$ 不可到达 $a$ 。   


这个结论我们可以这样证明：假设 $b$ 在 $a$ 右边。由题意知，$a$ 到 $b$ 的钥匙一定在 $a$ 或 $a$ 的左边。所以从 $b$ 就不可能拿到这把钥匙，因此不可能到 $a$ 。

由这个结论易得知：任何两个第三种块的交不大于 $1$ 。

因此，每个块最多被拓展两次，拓展所有第三种块总的复杂度为 $O(n+m)$ 。

---

所以，算法的总复杂度为 $O((n+m)\cdot\alpha(n))$ 。

代码可以私信找 @A_C_L 要，这里就不放了。


---

## 作者：teafrogsf (赞：5)

~~跑的也太慢了吧......被暴力吊起来打~~  
这题目的思路其实很简单：首先$\Theta(n)$处理出每个点一开始能到达的点，然后对于每个门，如果当前门的钥匙在左边那么就$\rm add(i+1,i)$，否则$\rm add(i,i+1)$，这样的意思是从$i+1$到不了$i$，反之亦然。  
然后我们按照拓扑序进行遍历，每次暴力左右跳求当前点能得到的答案。我们可以发现，每次暴力跳的左右边界一定不会超过拓扑序列中还没有的位置能给予的贡献，所以总跳跃次数（或许）为$\Theta(n)$，于是这（或许）可以被证明是$\Theta(n)$的。  
~~函数名比较闲着没事干请不要在意~~  
**另外，有一个小优化：其实我们可以在一开始缩点，之后对于每个缩后的点执行这个过程就可以了。**这样应该会更快一些，然而因为我过了这道题就不想打了。有兴趣的各位可以尝试一下。  
~~此外初始化拓扑的队列时倒着加会快不少~~
```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstdlib>
#define neko 1000010
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
#define rf(i,a,b) for(register int i=(a);i>=(b);i=~(-(i)))
#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].next,v=e[i].v)
int n,m,q,t;
typedef int arr[neko];
arr key,L,R,dgr,head;
struct node
{
    int v,next;
}e[neko];
void add(int x,int y)
{
    e[++t].v=y;
    e[t].next=head[x];
    head[x]=t,++dgr[y];
}
namespace solve
{
    using namespace std;
    void contraction()
    {
        int now=1;
        f(i,1,n){L[i]=now;if(key[i])now=i+1;}now=n;
        rf(i,n,1){R[i]=now;if(key[i-1])now=i-1;}
    }
    bool check(int pos,int now)
    {
        if(!key[pos])return 1;
        if(key[pos]>=L[now]&&key[pos]<=R[now])return 1;
        return 0;
    }
    void monotonestack()
    {
        bool flag;int x;
        queue<int>q;rf(i,n,1)if(!dgr[i])q.push(i);
        while(!q.empty())
        {
            x=q.front(),q.pop();
            flag=1;
            while(flag)
            {
                flag=0;
                while(L[x]>1&&check(L[x]-1,x))L[x]=L[L[x]-1],flag=1;
                while(R[x]<n&&check(R[x],x))R[x]=R[R[x]+1],flag=1;
            }travel(i,x,v)if(!(--dgr[v]))q.push(v);
        }
    }
}
char getc()
{
    static char buf[1048576],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1048576,stdin),p1==p2)?EOF:*p1++;
}
void read(int &x)
{
    char c=getc();x=0;
    while(!isdigit(c))c=getc();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^'0'),c=getc();
}
int main()
{
    int x,y;
    read(n),read(m),read(q);
    f(i,1,m){read(x),read(y),key[x]=y;if(y<=x)add(i+1,i);else add(i,i+1);}
    solve::contraction(),solve::monotonestack();	
    f(i,1,q)	
    {
        read(x),read(y);
        if(x>y&&L[x]<=y)putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
        else if(x<=y&&R[x]>=y)putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
        else putchar('N'),putchar('O'),putchar('\n');
    }
}
```

---

## 作者：ww3113306 (赞：4)

原来n^2暴力真能过啊。。。。

先暴力拓展（左右反复扫），预处理出所有房间作为起点可以到达的最右和最左房间，

然后加个小剪枝，如果遇到了之前处理过的点，就可以直接跳到那个点可以到的端点

然后倒着求（据说是为了防止正着被卡。。。）

早知道考场上就乱搞一下暴力了，，，，

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 1100000
int n,m,p;
int s[AC],l[AC],r[AC];

inline int read()
{
    int x=0;char c=getchar();bool z=false;
    while(c > '9' || c< '0') 
    {
        if(c == '-') z=true;
        c=getchar();
    }
    while(c >= '0' && c <= '9') x=x*10+c-'0',c=getchar();
    if(!z) return x;
    else return -x;
}

void pre()
{
    R a,b;
    n=read(),m=read(),p=read();
    for(R i=1;i<=m;i++) 
    {
        a=read(),b=read();
        s[a]=b;//a~a+1的锁在房间b
    //	have[b]=a;//房间b有a~a+1的锁
    }
}

inline void upmin(int &a,int b)
{
	if(b < a) a=b;
}

void get()
{
    int ll,rr;
    for(R i=n;i>=1;i--)
    {
        ll=rr=i;
        while(1)
        {
        	while(ll > 1 && (!s[ll-1] || (ll <= s[ll-1] && rr >= s[ll-1])))//如果钥匙所在区间已经被访问过了就可以走，这样就还不用开bool了
			{
				--ll;
				//这里就不判断了，因为是倒着乱搞，所以肯定不符合
        	}
        	while(rr < n && (!s[rr] || (ll <= s[rr] && rr >= s[rr])))//因为s[rr]代表的门是rr ---> rr+1,所以是判断rr，而不是rr+1
			{
				++rr;
				if(l[rr]) upmin(ll,l[rr]),rr=r[rr];
			}
			if(ll == 1 || (s[ll-1] && (ll > s[ll-1] || rr < s[ll-1]))) break;
		}
        l[i]=ll,r[i]=rr;
    }	
}

void work()
{
    R a,b;
    for(R i=1;i<=p;i++)
    {
        a=read(),b=read();
        if(a == b || (b < a && l[a] <= b) || (a < b && r[a] >= b)) printf("YES\n");
        else printf("NO\n");
    }
}

int main()
{
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
    pre();
	get();
    work();	
	fclose(stdin);
//	fclose(stdout);
    return 0;
}
```

---

## 作者：Great_Influence (赞：4)

来波非正解题解。。。

出题人在知乎上表示，本来是0.5s无O2的，然而被组委会放开了。。。

开始说题解。考虑暴力维护每个点能够向左向右延伸的最远位置。基本的思想是向左在向右无限反复拓展，利用神秘方法维护（貌似是单调栈），可以做到$O(n$拐弯次数$)$，最优情况$O(n)$,最劣情况 $O(n^2)$（然而数据太水没卡）

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
using namespace std;
template<typename T>inline void read(T&x)
{
	T f=1;static char c;x=0;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
inline void file()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
}

const int MAXN=1e6+7;

static int n,m,q,lock[MAXN],l[MAXN],r[MAXN];

inline void init()
{
	read(n);read(m);read(q);
	static int x;
	Rep(i,1,m)read(x),read(lock[x]);
	Rep(i,1,n)l[i]=r[i]=i;
	static bool flag=true;
	Rep(i,2,n)if(!lock[i-1])l[i]=l[i-1];
	Repe(i,n-1,1)if(!lock[i])r[i]=r[i+1];
	
	while(flag)
	{
		flag=false;
		Rep(i,2,n)while(*(l+i)>1&&
			*(lock+*(l+i)-1)>=*(l+i)
			&&*(lock+*(l+i)-1)<=*(r+i))
			*(l+i)=*(l+*(l+i)-1),flag=true;
		Repe(i,n-1,1)while(*(r+i)<n&&
			*(lock+*(r+i))<=*(r+i)&&*(lock+*(r+i))>=*(l+i))
			*(r+i)=*(r+*(r+i)+1),flag=true;
	}
}

inline void solve()
{
	static int s,t;
	Rep(i,1,q)
	{
		read(s);read(t);
		printf("%s\n",l[s]<=t&&r[s]>=t?"YES":"NO");
	}
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
}

int main()
{
	file();
	init();
	solve();
	return 0;
}

```


顺便%一下自己YY的题撞到原题的出题人。(话说浙江省选赛前培训还选讲了这道题)

---

## 作者：ywy_c_asm (赞：2)

额……为啥题解里写的都是$O(\text{玄学})$暴力啊……

这里来一个比较无脑的常数极大的甚至开了2棵线段树的$O(nlogn)$做法~~线段树大法好~~

显然我们得对于每个点求处他最多能扩展到哪的区间对吧，~~所以那个询问其实是假的……~~ 然后我们手玩发现无法继续扩展的只有以下4种情况：

## A：

![](https://cdn.luogu.com.cn/upload/pic/52720.png)

（其中i点为出发点，左右黑色竖线是门，红色箭头指向要是所在的位置）

这个图中i左右两侧的门的钥匙都在i的异侧，

## B：

![](https://cdn.luogu.com.cn/upload/pic/52721.png)

这个图中i左侧和右侧的门的钥匙都在右侧门的右侧，显然无法打开。

## C：

![](https://cdn.luogu.com.cn/upload/pic/52722.png)

和B同理这个都在左侧。

## D：

![](https://cdn.luogu.com.cn/upload/pic/52723.png)

i两侧的门的钥匙都在对方的外侧。

然后我们要做的就是对每个i点都求出这四种情况中的最小的能够包住他的区间，如果你对这个感到疑惑，请自行在纸上画几个例子手玩一下。

对于A很显然就找i左边最近的钥匙在自己左侧的（记为$pre_i$）和i右边最近的钥匙在自己右侧的（记为$nxt_i$）就行了，对于B，我们希望找出B之前的钥匙在$nxt_i$之后的最右的门，这个就可以开个线段树维护一下$max\{pos_i\}$就可以在线段树上的区间里$O(logn)$二分了，C同理在线段树上维护个$min$，对于D这个情况比较棘手因为着两个门的影响是相互的，在i点好像就确定不了了。所以我们不妨枚举左边的门$l$，然后我们找到在他右边离他最近的一个门$r$使得$pos_r<l$，这个也可以线段树上二分。但是如果有多个这样的r呢？好像不一定非得是离l最近的吧……哦其实你会发现如果出现这种情况的话就是这图：

![](https://cdn.luogu.com.cn/upload/pic/52724.png)

然后i实际上被一个C情况的更小的区间包着，这一定是能被算上的，所以对D情况我们找一个以l为左端点的最小的区间就好了，然后在另一棵线段树上进行区间覆盖就行了。

哦还有注意必须把边界也当做开不开的门！

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 123456789
#define ls(_o) (_o<<1)
#define rs(_o) ((_o<<1)|1)
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	int n;
	typedef struct _qj{
		int l;int r;
		_qj(){l=r=0;}
		_qj(int i,int j){l=i;r=j;}
		friend bool operator <(const _qj &a,const _qj &b){
			return(a.r-a.l<b.r-b.l);
		}
	}qj;
	qj data[4000001];
	int maxn[4000001],minn[4000001],dst[1000001];
	void build(int l,int r,int tree){
		data[tree]=_qj(1,n);
		if(l==r){
			if(!dst[l])maxn[tree]=-inf,minn[tree]=inf;
			else maxn[tree]=minn[tree]=dst[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls(tree));
		build(mid+1,r,rs(tree));
		maxn[tree]=max(maxn[ls(tree)],maxn[rs(tree)]);
		minn[tree]=min(minn[ls(tree)],minn[rs(tree)]);
	}
	void setqj(int rl,int rr,int l,int r,int tree,qj me){
		if(rl==l&&rr==r){
			data[tree]=min(data[tree],me);
			return;
		}
		int mid=(l+r)>>1;
		if(rl>mid)setqj(rl,rr,mid+1,r,rs(tree),me);
		else{
			if(rr<=mid)setqj(rl,rr,l,mid,ls(tree),me);
			else{
				setqj(rl,mid,l,mid,ls(tree),me);
				setqj(mid+1,rr,mid+1,r,rs(tree),me);
			}
		}
	}
	int dfs1(int rl,int rr,int l,int r,int tree,int num){
		if(rl>rr||maxn[tree]<num)return(0);
		if(l==r)return(l);
		int mid=(l+r)>>1;
		if(rl==l&&rr==r){
			if(maxn[rs(tree)]>=num)return(dfs1(mid+1,r,mid+1,r,rs(tree),num));
			return(dfs1(l,mid,l,mid,ls(tree),num));
		}
		if(rl>mid)return(dfs1(rl,rr,mid+1,r,rs(tree),num));
		if(rr<=mid)return(dfs1(rl,rr,l,mid,ls(tree),num));
		int cjr=dfs1(mid+1,rr,mid+1,r,rs(tree),num);
		if(cjr)return(cjr);
		return(dfs1(rl,mid,l,mid,ls(tree),num));
	}
	int dfs2(int rl,int rr,int l,int r,int tree,int num){
		if(rl>rr||minn[tree]>num)return(0);
		if(l==r)return(l);
		int mid=(l+r)>>1;
		if(rl==l&&rr==r){
			if(minn[ls(tree)]<=num)return(dfs2(l,mid,l,mid,ls(tree),num));
			return(dfs2(mid+1,r,mid+1,r,rs(tree),num));
		}
		if(rl>mid)return(dfs2(rl,rr,mid+1,r,rs(tree),num));
		if(rr<=mid)return(dfs2(rl,rr,l,mid,ls(tree),num));
		int cjr=dfs2(rl,mid,l,mid,ls(tree),num);
		if(cjr)return(cjr);
		return(dfs2(mid+1,rr,mid+1,r,rs(tree),num));
	}
	qj ans[1000001];
	void tui(int l,int r,int tree){
		if(l==r){
			ans[l]=data[tree];
			return;
		}
		int mid=(l+r)>>1;
		data[ls(tree)]=min(data[ls(tree)],data[tree]);
		data[rs(tree)]=min(data[rs(tree)],data[tree]);
		tui(l,mid,ls(tree));
		tui(mid+1,r,rs(tree));
	}
	int pre[1000001],nxt[1000011];
	void ywymain(){
		n=get();int m=get(),q=get();
		for(register int i=1;i<=m;i++){
			int x=get();
			dst[x]=get();
		}build(1,n,1);
		for(register int i=1;i<=n;i++){
			pre[i]=pre[i-1];
			if(dst[i-1]&&dst[i-1]<i)pre[i]=i-1;
			if(dst[i]>i){
				int r=dfs2(i+1,dst[i]-1,1,n,1,i);
				if(r)setqj(i+1,r,1,n,1,_qj(i+1,r));
			}
		}
		dst[n]=n+1;
		for(register int i=n;i>=1;i--){
			nxt[i]=nxt[i+1];
			if(dst[i]>i)nxt[i]=i;
		}
		tui(1,n,1);
		for(register int i=1;i<=n;i++){
			ans[i]=min(ans[i],_qj(pre[i]+1,nxt[i]));
			if(pre[i]){
				int r=dfs2(i,n,1,n,1,pre[i]);
				if(r)ans[i]=min(ans[i],_qj(pre[i]+1,r));
			}
			if(nxt[i]){
				int l=dfs1(1,i-1,1,n,1,nxt[i]+1);
				if(l)ans[i]=min(ans[i],_qj(l+1,nxt[i]));
			}
		}
		while(q){
			q--;
			int s=get(),t=get();
			if(t<=ans[s].r&&t>=ans[s].l)printf("YES\n");
			else printf("NO\n");
		}
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：ecnerwaIa (赞：2)

**暴力出奇迹！**（当然要那种比较玄学的才行啦）

[题目](https://www.luogu.org/problemnew/show/P4436)

首先也是求出$i$可以到达的区间$[L_i,R_i]$,但是如果直接暴力求会$TLE$的，这个时候**剪枝可就厉害了！**成功将最慢的点优化成了300ms（还是评测高峰期）。

先考虑从$i$一直往左可以走到的左端点$ls[i]$,一直往右走可以到的右端点$rs[i]$,只要把这个处理出来其实此题就可以过了的...然后对于每一个$i$节点，之前一次$L[i]$,$R[i]$是扩展一个，现在可以一次跳一段，直到跳不了。（不明白的接着看下面）

扫$ls[i]$从$1$到$n$，先一步一步考虑，如果$key[i-1]==i(key[x]=y:x$到$x+1$需要的钥匙是$y$),那么$ls[i]=ls[i-1]$，这个应该是很好理解的吧

但是仅仅这一个优化，只能36到72分（开$O2$ 72分）

接着我发现$i-1$是没有$i$钥匙的，但是我如果从$i$扩展到了$ls[i-1]$其实是有$i$这个钥匙的对吧？那就是说之前没有$i$可以扩展到$ls[i-1]$，现在有了$i$可能可以继续往左边扩展（这里只考虑$ls,rs$同理）。

但是单纯就这样写是不足以过的，那么是否可以按照这种思想得到更好的优化呢？答案显然是有的（否则我就不会写这篇题解了）

假设当前从$i$已经扩展到$pos$节点了，那么有$[pos,i]$的钥匙,考虑是否可以扩展$pos-1$，即判断$key[pos-1]>=pos\&\&key[pos-1]<=i$，如果不能扩展就结束，$ls[i]=pos$，如果能急需扩展$pos=ls[pos-1]$，直到$pos=1$或者不能扩展

**注：** 因为$ls$代表的是一直向左可以到的最远点，是与右边的点没有任何关系的，所以右边的点扩展到点$pos-1$时直接跳$ls[pos-1]$是可以的

而且因为这个其实有点像路径压缩了...所以实际这个找$ls,rs$的复杂度并不高

相信写过暴力都会写如下的代码吧
```cpp
for(int i=1;i<=n;++i){
    L[i]=i;R[i]=i;
    while(1){
        if(L[i]>1)if(!key[L[i]-1]||(L[i]<=key[L[i]-1]&&key[L[i]-1]<=R[i])){L[i]--;continue;}
        if(R[i]<n)if(!key[R[i]]||(L[i]<=key[R[i]]&&key[R[i]]<=R[i])){R[i]++;continue;}
        break;
    }
}
```

那么有了$ls,rs$就可以不用每次都是只$+1,-1$了！代码如下

```cpp
    for(int i=1;i<=n;++i){
        L[i]=ls[i];R[i]=rs[i];
        while(1){f=1;
            if(L[i]>1)if(!key[L[i]-1]||(L[i]<=key[L[i]-1]&&key[L[i]-1]<=R[i])){L[i]=ls[L[i]-1];f=0;}
            if(R[i]<n)if(!key[R[i]]||(L[i]<=key[R[i]]&&key[R[i]]<=R[i])){R[i]=rs[R[i]+1];f=0;}
            if(f)break;
        }
    }
```

**注意事项：**

1. 求$ls,rs$时每次跳一段区间就要更新一下$ls/rs$，因为不更新钥匙就只有$i$，就达不到这个优化的效果

2. 上面的$f$就是一个小优化，其实就是少了点continue的次数

下面上完整代码（码风觉得有点那个，就格式化一下吧），39行，这个暴力是真的好打呢！

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=1e6+10;
int n,m,p,L[N],R[N],key[N];
int ls[N],rs[N];
inline int max_(int a,int b){return a>b?a:b;}
inline int min_(int a,int b){return a<b?a:b;}
int main(){
    scanf("%d%d%d",&n,&m,&p);int x,y;
    for(int i=1;i<=m;++i){scanf("%d%d",&x,&y);key[x]=y;}
    int pos;
    for(int i=1;i<=n;++i){
        ls[i]=i;
        pos=i;
        while(pos>1&&(!key[pos-1]||(ls[i]<=key[pos-1]&&key[pos-1]<=i))){ls[i]=ls[pos-1];pos=ls[pos-1];}
    }for(int i=n;i>=1;--i){
        rs[i]=i;
        pos=i;
        while(pos<n&&(!key[pos]||(i<=key[pos]&&key[pos]<=rs[i]))){rs[i]=rs[pos+1];pos=rs[pos+1];}
    }bool f=1;
    for(int i=1;i<=n;++i){
        L[i]=ls[i];R[i]=rs[i];
        while(1){f=1;
            if(L[i]>1)if(!key[L[i]-1]||(L[i]<=key[L[i]-1]&&key[L[i]-1]<=R[i])){L[i]=ls[L[i]-1];f=0;}
            if(R[i]<n)if(!key[R[i]]||(L[i]<=key[R[i]]&&key[R[i]]<=R[i])){R[i]=rs[R[i]+1];f=0;}
            if(f)break;
        }
    }
    for(int i=1;i<=p;++i){
        scanf("%d%d",&x,&y);
        if(L[x]<=y&&R[x]>=y)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```


---

## 作者：小小小朋友 (赞：1)

## 题意

给出一个链，中间有的路径是带锁的，给出钥匙在某些节点上。多次询问某两点之间路径是否存在。

## 做法

注意到对于每个节点能到达的位置都是一段连续区间。

我们思考对每个位置求出能到达的最左端和最右端。

这里可以用分治处理，但我们注意到一种更为简单的处理方法：暴力。就左一步右一步走到头。

这个地方思考一下走的顺序的问题，发现左一步右一步是正确的，因为每次走一步都会两边进行判断。

考虑怎么优化。首先是缩点，这很好理解。第二，我们扩展的时候将之前计算过的合并一下。第三，我们随机计算顺序。

按顺序做很好卡，譬如说一组第一个点钥匙开第二个点的门，第二个点钥匙开第三个点的门……这样按顺序做就是平方复杂度了。

可能也可以用类似分块的思想做，一开始每隔 $\sqrt n$ 个点计算一个节点，后面再计算别的。

当然这题我们直接随机就能过了，并且我觉得很难卡。

有问题可以私信。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[1000005];
int n,m,p,blo[1000005],loc[1000005],lx[1000005],ly[1000005],maxb,l[1000005],r[1000005];
int s,t;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//快读
	cin>>n>>m>>p;
	int nb=1;
	for(int i=1;i<=m;i++) cin>>lx[i]>>ly[i],loc[lx[i]]=1;
	for(int i=1;i<=n;i++){//缩一下
		blo[i]=nb;
		if(loc[i]) nb++;
	}maxb=nb;
	for(int i=1;i<=m;i++) ly[blo[lx[i]]]=blo[ly[i]];
	for(int i=maxb;i>=1;i--){
		int tl=i,tr=i;//记录左，右边界
		while(1){
			bool flag=0;
			if(tl!=1&&tr>=ly[tl-1]&&tl<=ly[tl-1]) flag=1,tl--;//只要判断其钥匙在不在已经可达区间内
			if(l[tl]!=0) tl=l[tl];//直接合并
			if(tr!=maxb&&tr>=ly[tr]&&tl<=ly[tr]) flag=1,tr++;
			if(r[tr]!=0) tr=r[tr];//直接合并
			if(!flag) {l[i]=tl,r[i]=tr;break;}//不能扩展
		}
	}
	for(int i=0;i<p;i++){
		int s,t;cin>>s>>t;
		// cout<<blo[t]<<' '<<blo[s]<<endl;
		if(blo[t]<=r[blo[s]]&&blo[t]>=l[blo[s]]) cout<<"YES\n";//在区间内就可达
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

首先将没有限制的边缩点，判掉 $s=t$ 的情况。

接着考虑一条边 $(x,x+1)$，限制为 $y$，给这条边定向：若 $y\leq x$，则这条边为 $x\to x+1$，否则为 $x+1\to x$。

那么显然的一组询问 $s,t$ 可行的必要条件为边 $(s,s+1),...,(t-1,t)$ 均为同向且方向均为 $s\to t$ 的方向。

那么就可以把所有点 $s$ 作为起点的情况分为三类：

- 第一类，两边的边方向都指向自己，显然对于任何询问都是 `NO`。
- 第二类，只有右边的边方向指向自己，这时候 $s$ 作为起点时答案为 `YES` 的点一定都在 $s$ 右侧，那么直接用 ST 表维护 $(s,s+1),...,(t-1,t)$ 这些边是否都为向右且限制是否都在 $[s,t)$ 之间。只有左边的边方向指向自己同理。
- 第三类，两边的边方向都不指向自己，这时候 $s$ 作为起点有可能到很多点，发现不好处理，怎么办？其实可以直接暴力向两边扩展。因为第三类点和第一类点肯定是交替出现的，所以这种点能到达的点只会在它两侧的两个第一类点之内的区间，然后就发现了任何两个第三类点所能到达的边的集合都不交（所能到达的点的集合交集也只会有第一类点），所以暴力的复杂度是线性的。


```cpp
//P4436 
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, m, p, x[N], y[N], t[N], id[N];
int fx[N], mx[20][N], mn[20][N];
int bs[N], ct[N], cl[N], cr[N];

int qmn(int l, int r){
	int k = 31 ^ __builtin_clz(r-l+1);
	return min(mn[k][l], mn[k][r-(1<<k)+1]);
}
int qmx(int l, int r){
	int k = 31 ^ __builtin_clz(r-l+1);
	return max(mx[k][l], mx[k][r-(1<<k)+1]);
}

int main(){
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 1; i <= m; ++ i){
		scanf("%d%d", &x[i], &y[i]);
		t[x[i]] = 1;
	}
	int nw = 1;
	for(int i = 1; i <= n; ++ i){
		id[i] = nw;
		if(t[i]){
			++ nw;
		}
	}
	n = nw;
	for(int i = 1; i <= m; ++ i){
		x[i] = id[x[i]];
		y[i] = id[y[i]];
		if(y[i] > x[i]){
			mx[0][i] = y[i];
			mn[0][i] = -1;
		} else {
			fx[x[i]] = 1;
			mn[0][i] = y[i];
			mx[0][i] = n + 2;
		}
	}
	fx[0] = 1;
	for(int i = 1; i < 20; ++ i){
		for(int j = 1; j + (1 << i) - 1 <= n; ++ j){
			mx[i][j] = max(mx[i-1][j], mx[i-1][j+(1<<i-1)]);
			mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<i-1)]);
		}
	}
	for(int i = 1; i <= n; ++ i){
		if((fx[i] && !fx[i-1]) || (i == 1 && fx[1] == 1) || (i == n && fx[n-1] == 0)){
			int r = i;
			while(fx[r]){
				bs[r] = i;
				++ r;
			}
			bs[r] = i;
			int l = i;
			while(!fx[l-1]){
				bs[l] = i;
				-- l;
			}
			bs[l] = i;
			
			ct[i] = 1;
			int nl = i, nr = i;
			while(true){
				bool flg = 1;
				while(nl > 1 && y[nl-1] >= nl && y[nl-1] <= nr){
					-- nl;
					flg = 0;
				}
				while(nr < n && y[nr] <= nr && y[nr] >= nl){
					++ nr;
					flg = 0;
				}
				if(flg){
					break;
				}
			}
			cl[i] = nl;
			cr[i] = nr;
		}
	}
	while(p--){
		int a, b;
		scanf("%d%d", &a, &b);
		a = id[a];
		b = id[b];
		if(a == b){
			puts("YES");
		} else if(ct[a] && cl[a] <= b && b <= cr[a]){
			puts("YES");
		} else if(b > a && qmn(a, b-1) >= a){
			puts("YES");
		} else if(b < a && qmx(b, a-1) <= a){
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：是个妹子啦 (赞：0)

~~本题怎么能没有最乱搞的做法呢~~

正常思路：枚举每个点$u$，从这个点往两边跳，如果下个点没锁门，或者钥匙在当前可走的范围内，继续跳。

拓展到每个点$v$，可以$v$的$[L,R]$更新$u$的，所以我们就可以随机枚举$u$的位置，多跑几回就好了

当然需要一个~~恶臭的种子~~

```cpp
int n,m,Q,L[N],R[N],a[N],key[N];
void solve(int x){
	L[x] = x,R[x] = x; int &l = L[x],&r = R[x];
	while(1){
		bool flag = 0;
		if(l > 1 && (!key[l-1] || l <= key[l-1] && key[l-1] <= r))
			flag = 1,--l,r = max(r,R[l]),l = min(l,L[l]);
		if(r < n && (!key[r] || l <= key[r] && key[r] <= r))
			flag = 1,++r,l = min(l,L[r]),r = max(r,R[r]);
		if(!flag) break;
	}
}
int main(){
	srand(11451419); n = read(); m = read(); Q = read();
	while(m--) key[read()] = read();
	for(int i = 1;i <= n;++i) a[i] = i,L[i] = n+1,R[i] = 0;
	random_shuffle(a + 1,a + n + 1);
	for(int i = 1;i <= n;++i) solve(a[i]); int u,v;
	while(Q--){
		u = read(); v = read();
		puts(L[u] <= v && v <= R[u] ? "YES" : "NO");
	}
}
```

~~就rank1~~了



---

