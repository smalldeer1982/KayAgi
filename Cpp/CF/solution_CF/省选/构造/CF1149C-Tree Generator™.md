# Tree Generator™

## 题目描述

Owl Pacino 一直对树结构情有独钟——尤其是无权有根树。他喜欢为每棵树求直径——即树中任意简单路径的最大长度。

Owl Pacino 的猫头鹰朋友们决定送给他一台 Tree Generator™——这是一台能够根据描述生成有根树的强大机器。一棵 $n$ 个结点的有根树可以用长度为 $2(n-1)$ 的括号序列来描述，具体方式如下：找到一条从根结点出发并最终回到根结点的路径，要求每条边恰好经过两次——一次向下走，一次向上走。沿着这条路径，每当沿着一条边向下时，记下一个左括号“(”；每当沿着一条边向上时，记下一个右括号“)” 。

下图展示了样例有根树及其描述：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149C/a9818ec6abf351ce6c6a0eaa115c2729c37577f5.png)

Owl 写下了一棵 $n$ 个结点的有根树的描述。之后，他又写了 $q$ 次新的描述。每次写新描述时，他会从上一次写下的描述中选出两个不同的位置，交换这两个括号，并将结果写下来。他始终确保每次写下的字符串都能描述一棵有根树。

每次写下描述后，Pacino 都用 Tree Generator™ 生成对应的树。请你求出每次生成的树的直径。

## 说明/提示

下图展示了第一个样例测试中每次生成的树及其描述：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149C/285660de836d4f0c8cc3430ffe028ede0245c7ef.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 5
(((())))
4 5
3 4
5 6
3 6
2 5
```

### 输出

```
4
3
3
2
4
4
```

## 样例 #2

### 输入

```
6 4
(((())()))
6 7
5 4
6 4
7 4
```

### 输出

```
4
4
4
5
3
```

# 题解

## 作者：KaisuoShutong (赞：46)

码长文不易，点个赞吧。QwQ  
UPD：修复部分错误

## 题目概述

中文翻译很清楚了。不过有一点是没有讲清楚的：关于如何使用树构建括号序列。

Dfs，每经过一条边，往下走就加入“(”，往上走就加入“)”。

## 题目分析

~~™好评~~

首先我们来证明一个引理。

> **引理1.1 若从序列中任取一段连续子序列，从中去掉所有匹配括号后，剩下的括号组成的路径一定为一条链，链长为剩下的子序列长。**

以下是一个例子。  
对于括号序列（（）（（））），其构成的树如下：  
其中，若我们取：后六个括号（中文括号没法标红好烦啊）  
其对应的即为从节点3到节点1的链。  
我们可以发现，2-4-5-4-2的链在括号序列上因为匹配而被消掉了。  
因此，括号匹配即表示这条链下去过，但又上来了，因此对答案没有贡献。  
这是一个似曾相识的思想，可是我记不起是什么了\笑  

这样，第二个引理就出现了。

> **引理1.2 树上直径长度即为任意区间去掉匹配括号后的长度的最大值。**

考虑直径的构成情况。它只会有两种。

![](https://cdn.luogu.com.cn/upload/image_hosting/lahn3jex.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/x9xzliy2.png)

图有点龊，将就看吧。

第二种没有问题，但是第一种。注意到它也是可以被括号序列表示出来的。比如（）（（）（））选第5、6个括号。其实这点在刚刚的例子中已经体现出来了。

这时候我们给出第三个引理。

若我们给”(”赋值 +1，给”)”赋值 -1，则：

> **引理1.3 最长去匹配区间 = 最大的（将区间分成两段）后面的权值和 - 前面的权值和**

这是为什么呢？我想你可能会有以下疑问：

Q：如果我把一个括号在分配时分成两半了怎么办啊？  
A：依赖于负数权值，不会有任何影响。因为此时的值为 -1-(+1)=-2，对比之前的 -1+1=0，你只会选择之前的办法，根本不会考虑这种毫无用处的办法。

Q：对于）（）（））这种序列岂不是无法划分？  
A：可以的，只需要全部划分到前半部分即可。

Q：（略加思考后）那你证明一下吧。  
A：因为匹配的括号在灵魂拷问三连第一问中已经证明了是无用的（即贡献为0），所以整个序列可以被简化为以下三种：

1> ……（（（（（（……  
2> ……））））））……  
3> ……）））（（（……  

对于第一种和第二种我们只需将中间位置移到左边和右边即可。而对于第三种，放到中间，所以后减前的好处就体现出来了——两边相减恰为答案。

那么，思考：如何维护相邻区间差最大值呢？

用线段树（废话）。

不妨设这个最长去匹配区间为Δ。

我们选择维护九个变量：区间和，左/右连续选值最大/小值，从左/右连续选值Δ最大值，选择整个区间Δ最大值，无限制连续选值Δ最大值（最终答案）。

接下来考虑如何向上更新。

区间和：直接加。  
左/右连续选值最大值，无限制连续选值最大值：Can you answer these queries III  
从左/右连续选值Δ最大值：以左为例，先给转移式：

$$lv[k]=max(max(lv[k<<1],lv[k<<1|1]-s[k<<1]),mv[k<<1]+lmx[k<<1|1])$$

这个真的画个图看一下就明白了。用到的思想就是，枚举中间点分别在左区间和右区间的情况，取max。

选择整个区间Δ最大值：同上一个的思想：

$$mv[k]=max(mv[k<<1]+s[k<<1|1],mv[k<<1|1]-s[k<<1])$$

无限制连续选值Δ最大值：同上一个的思想：

$$mm[k]=max(max(max(mm[k<<1],mm[k<<1|1]),lv[k<<1|1]-rmn[k<<1]),rv[k<<1]+lmx[k<<1|1])$$

这题就做完了。掐头去尾后40行都没有。

```cpp
void Pushup(int k)
{
	s[k]=s[k<<1]+s[k<<1|1];
	lmx[k]=max(lmx[k<<1],s[k<<1]+lmx[k<<1|1]);
	rmx[k]=max(rmx[k<<1|1],s[k<<1|1]+rmx[k<<1]);
	lmn[k]=min(lmn[k<<1],s[k<<1]+lmn[k<<1|1]);
	rmn[k]=min(rmn[k<<1|1],s[k<<1|1]+rmn[k<<1]);
	lv[k]=max(max(lv[k<<1],lv[k<<1|1]-s[k<<1]),mv[k<<1]+lmx[k<<1|1]);
	rv[k]=max(max(rv[k<<1|1],s[k<<1|1]+rv[k<<1]),mv[k<<1|1]-rmn[k<<1]);
	mv[k]=max(mv[k<<1]+s[k<<1|1],mv[k<<1|1]-s[k<<1]);
	mm[k]=max(max(max(mm[k<<1],mm[k<<1|1]),lv[k<<1|1]-rmn[k<<1]),rv[k<<1]+lmx[k<<1|1]);
}
char S[maxn];
void Build(int k,int l,int r)
{
	if(l==r) return s[k]=(S[l]=='('?1:-1),lmx[k]=rmx[k]=max(s[k],0),lmn[k]=rmn[k]=min(s[k],0),lv[k]=rv[k]=mv[k]=mm[k]=1,void(0);
	int mid=l+r>>1;
	Build(k<<1,l,mid),Build(k<<1|1,mid+1,r);
	Pushup(k);
}
void Update(int k,int l,int r,int p,char d)
{
	if(l==r) return s[k]=(d=='('?1:-1),lmx[k]=rmx[k]=max(s[k],0),lmn[k]=rmn[k]=min(s[k],0),lv[k]=rv[k]=mv[k]=mm[k]=1,void(0);
	int mid=l+r>>1;
	if(p>mid) Update(k<<1|1,mid+1,r,p,d);
	else Update(k<<1,l,mid,p,d);
	Pushup(k);
}
char SWAP(char&x,char&y) {char z=y;y=x,x=z;}
signed main()
{
	int x,y;
	n=read()-1<<1,m=read(),rein(S+1);
	Build(1,1,n),printf("%d\n",mm[1]);
	while(m--) x=read(),y=read(),S[x]^S[y]?(SWAP(S[x],S[y]),Update(1,1,n,x,S[x]),Update(1,1,n,y,S[y])):void(0),printf("%d\n",mm[1]);
	return 0;
}
```


---

## 作者：tzc_wk (赞：20)

UPD on 2021.3.24：修了一个 typo

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/1149/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1149C)

首先考虑这个所谓的“括号树”与直径的本质是什么。考虑括号树上两点 $x,y$，我们不妨用一个“DFS”的过程来理解，在 DFS 过程中假设我们在第 $l$ 个字符后访问 $x$，显然接下来会访问 $x$ 的子树并回到 $x$，也就是说对应的括号序列是一个合法括号序列，也就是说它的**左右括号相抵消了**，紧接着我们会向上回溯到 $\text{LCA}(x,y)$，对于在回溯的过程中访问的点 $z$，我们可能还会访问它的其它子树，不过由于最终回到了 $z$，所经过的括号串一定是一个合法括号序列，最终不能相抵消的部分一定是 $dep_x-dep_{\text{LCA}(x,y)}$ 个右括号，换句话说，从 $x$ 到 $\text{LCA}(x,y)$，其经过的路径进行左右括号抵消后一定是**若干个右括号**拼起来的字符串。同理，从 $\text{LCA}(x,y)\to y$ 一定是**若干个左括号**拼起来的字符串，也就是说 $x,y$ 之间的路径长度就是 $[l,r]$ 进行左括号相抵消后剩余部分的长度，我们记该值为 $f(l,r)$。而显然 $\forall 1\leq l\leq r\leq 2(n-1)$，区间 $[l,r]$ 都对应一对 $(x,y)$。故答案即为 $\max\limits_{1\leq l\leq r\leq 2(n-1)}f(l,r)$。

~~然后我就在那儿一直想怎样直接维护 $f(l,r)$，心态爆炸……似乎 ycx 也卡在了这个地方？~~

根据 $f(l,r)$ 的定义不难发现这玩意儿直接维护是不太容易的，因为合并两个区间时还需考虑左右括号相消的问题。如果我们能够将其变成类似于求和、取 $\max$ 的东西是不是就比较好维护了呢？

我们假设 $[l,r]$ 消完之后剩余 $x$ 个右括号，$y$ 个左括号。考虑套路地将 `(` 看作 $1$，`)` 看作 $-1$。对 $[l,r]$ 进行一遍前缀和得到数组 $s_i$（或者说 $s_i$ 表示区间 $[l,i]$ 中左括号个数 $-$ 右括号个数），那么显然 $\min_{i=l}^rs_i=-x$。

看到这个 $\min$ 能想到什么呢？

考虑设 $s_k=-x$，我们不妨将区间 $[l,r]$ 从 $k$ 处劈开，劈成两个子区间 $[l,k],[k+1,r]$，显然 $[l,k]$ 中左右相消后一定是 $x$ 个右括号，$[k+1,r]$ 中左右相消后一定是 $y$ 个左括号。如果我们记 $sum(l,r)$ 为 $[l,r]$ 中所有数字和。那么有 $sum(l,k)=-x,sum(k+1,r)=y$，故 $sum(k+1,r)-sum(l,k)=x+y$。而对于某个 $k'\in[l,r),k'\neq k$，由 $\min_{i=l}^rs_i=-x$ 知 $s_k\le s'_k$ 知 $sum(k+1,r)-sum(l,k')=sum(l,r)-2sum(l,k)=sum(l,r)-2s_{k'}\le sum(l,r)-2s_k=x+y$，故 $f(l,r)=x+y=\max\limits_{k=l}^{r-1}\{sum(k+1,r)-sum(l,k)\}$

于是最终答案即为 $\max\limits_{1\leq l\leq r\leq 2(n-1)}\max\limits_{k=l}^{r-1}\{sum(k+1,r)-sum(l,k)\}$，也就是第一篇题解中所说的“选择相邻两段并做差的最大值”。

这个就可以用线段树维护了，每个节点 $[l,r]$ 维护以下八个值：

- $sum$ 表示 $sum(l,r)$
- $lmx$ 表示 $\max sum(l,k)$
- $rmx$ 表示 $\max sum(k,r)$
- $lmn$ 表示 $\min sum(l,k)$
- $rmn$ 表示 $\min sum(k,r)$
- $mx1$ 表示 $\max sum(x,y)-sum(l,x),l\leq x\le y\le r$
- $mx2$ 表示 $\max sum(y,x)-sum(x,y),l\leq x\leq y\le r$
- $mx$ 表示 $\max sum(y,z)-sum(x,y),l\leq x\leq y\leq z\leq r$

以上八个标记都可 $\mathcal O(1)$ `pushup`，具体见代码。

至于修改……这个就相当容易了罢，直接单点修改即可。

时间复杂度线对。

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
const int MAXN=2e5;
int n,qu;char str[MAXN+5];
struct node{int l,r,sum,lmx,rmx,lmn,rmn,mx1,mx2,mx;} s[MAXN*4+5];
void pushup(int k){
	s[k].sum=s[k<<1].sum+s[k<<1|1].sum;
	s[k].lmx=max(s[k<<1].lmx,s[k<<1].sum+s[k<<1|1].lmx);
	s[k].lmn=min(s[k<<1].lmn,s[k<<1].sum+s[k<<1|1].lmn);
	s[k].rmx=max(s[k<<1|1].rmx,s[k<<1|1].sum+s[k<<1].rmx);
	s[k].rmn=min(s[k<<1|1].rmn,s[k<<1|1].sum+s[k<<1].rmn);
	s[k].mx1=max(s[k<<1].mx1,max(-s[k<<1].sum+s[k<<1|1].mx1,s[k<<1|1].lmx+s[k<<1].rmx*2-s[k<<1].sum));
	s[k].mx2=max(s[k<<1|1].mx2,max(s[k<<1|1].sum+s[k<<1].mx2,-s[k<<1].rmn+s[k<<1|1].sum-2*s[k<<1|1].lmn));
	s[k].mx=max(max(s[k<<1].mx,s[k<<1|1].mx),max(s[k<<1].mx2+s[k<<1|1].lmx,-s[k<<1].rmn+s[k<<1|1].mx1));
}
void build(int k=1,int l=1,int r=n){
	s[k].l=l;s[k].r=r;
	if(l==r){
		if(str[l]=='(') s[k].sum=1,s[k].lmx=1,s[k].rmx=1,s[k].lmn=0,s[k].rmn=0;
		else s[k].sum=-1,s[k].lmx=0,s[k].rmx=0,s[k].lmn=-1,s[k].rmn=-1;
		s[k].mx1=1;s[k].mx2=1;s[k].mx=1;return;
	} int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
void modify(int k,int p,int v){
	if(s[k].l==s[k].r){
		s[k].lmx=s[k].rmx=max(v,0);
		s[k].lmn=s[k].rmn=min(v,0);
		s[k].sum=v;
		s[k].mx1=1;s[k].mx2=1;s[k].mx=1;return;
	} int mid=s[k].l+s[k].r>>1;
	if(p<=mid) modify(k<<1,p,v);
	else modify(k<<1|1,p,v);
	pushup(k);
}
int main(){
	scanf("%d%d%s",&n,&qu,str+1);n=(n-1)<<1;
	build(1,1,n);printf("%d\n",s[1].mx);
	while(qu--){
		int x,y;scanf("%d%d",&x,&y);
		if(str[x]!=str[y]){
			swap(str[x],str[y]);
			modify(1,x,(str[x]=='(')?1:-1);
			modify(1,y,(str[y]=='(')?1:-1);
		} printf("%d\n",s[1].mx);
	}
	return 0;
}
```



---

## 作者：霖ux (赞：14)

一个个人认为比较自然的做法
### 题目描述
给一个树的括号序 每次操作对换两个括号 求出每次操作后树的直径长度  
$m,n\le 10^5$

### 题解
题目要求维护一个括号序所对应的树的直径，我们应该先考虑如何把这两个东西联系在一起。

众所周知，设 $\text{dep}_i$ 表示表示深度，则树上一条以 $a,b$ 为端点路径的长度是 $\text{dep}_a+\text{dep}_b-2\times \text{dep}_{\text{lca}(a,b)}$   ,而  $\text{dep}_{\text{lca}(a,b)}$ 在括号序上正好就是 $\min_{i=a}^b \text{dep}_i$  ,于是直径就是最大的 $\text{dep}_a+\text{dep}_b-2\times \min_{i=a}^b \text{dep}_i$  。

我们可以把括号序上的左括号看作进入一个节点，右括号代表退回到这个节点的父亲节点，于是我们把左括号设成 $1$ ,右括号设成 $-1$ ,这样每个位置的前缀和就是这个位置的深度。

因为题目保证每次操作后都是一颗树，所以我们考虑直接用线段树维护这个前缀和。操作就是把原序列的 $1$ 换成 $-1$ ，$-1$ 换成 $1$ ，体现在前缀和上就是后缀 $\pm2$ 。

为了维护答案，对于每个节点，我们需要维护五个值：  
$\text{mx}\triangleq \max_{i=l}^r \text{dep}_i$  即区间最大值    
$\text{mn}\triangleq \min_{i=1}^r \text{dep}_i$  即区间最小值   
$\text{lmx}\triangleq \max_{i=l}^r\{\text{dep}_i-2\times \min_{j=l}^i \text{dep}_j\}$  即最大的  $\text{dep}_b-2\times \min_{i=a}^b \text{dep}_i$    
$\text{rmx}\triangleq \max_{i=l}^r\{\text{dep}_i-2\times \min_{j=i}^r \text{dep}_j\}$  即最大的  $\text{dep}_a-2\times \min_{i=a}^b \text{dep}_i$    
$\text{ans}$  这个区间的答案  
考虑 $\text{lca}(a,b)$ 分别在左右两区间的情况  
1. $\text{lca}(a,b)$ 在左区间: $\text{ans}=\text{rmx}_l+\text{mx}_r$  
2. $\text{lca}(a,b)$ 在右区间: $\text{ans}=\text{mx}_l+\text{lmx}_r$

我们对这两个情况取 $\max$ 即可，因为不合法的情况显然是不优的。

对于区间操作，打标记即可，值得注意的是 $\text{lmx},\text{rmx}$ 在区间 $\pm x$ 后反而会 $\mp x$ ,而 $\text{ans}$ 则不会有变化。

复杂度自然是 $\mathcal{O}(m\log n)$

上代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
	return x;
}
const int maxn=1e6+10;
int a[maxn],sum[maxn],n,m;
namespace SGT{const int maxsiz=4*maxn;
	int lmx[maxsiz],rmx[maxsiz],mx[maxsiz],mn[maxsiz],ans[maxsiz],tag[maxsiz];
	inline int lt(int x){return x<<1;}
	inline int rt(int x){return (x<<1)|1;}
	void down(int x,int v)//修改一个节点
	{tag[x]+=v,mx[x]+=v,mn[x]+=v,lmx[x]-=v,rmx[x]-=v;}
	void pushup(int x){
		lmx[x]=max(mx[rt(x)]-2*mn[lt(x)],max(lmx[lt(x)],lmx[rt(x)]));
		rmx[x]=max(mx[lt(x)]-2*mn[rt(x)],max(rmx[lt(x)],rmx[rt(x)]));
		mx[x]=max(mx[lt(x)],mx[rt(x)]),mn[x]=min(mn[lt(x)],mn[rt(x)]);
		ans[x]=max(max(ans[lt(x)],ans[rt(x)]),max(mx[lt(x)]+lmx[rt(x)],rmx[lt(x)]+mx[rt(x)]));
	}
	void pushdown(int x)
	{if(tag[x]){down(lt(x),tag[x]);down(rt(x),tag[x]);tag[x]=0;}}
	void upd(int x,int l,int r,int k,int d){
		if(l==r){down(x,d);return;}
		int mid=(l+r)>>1;pushdown(x);
		if(k<=mid){upd(lt(x),l,mid,k,d);down(rt(x),d);}
		else upd(rt(x),mid+1,r,k,d);
		pushup(x);
	}
	void build(int x,int l,int r){
		if(l!=r){
			int mid=(l+r)>>1;
			build(lt(x),l,mid);
			build(rt(x),mid+1,r);
			pushup(x);
		}else mx[x]=mn[x]=sum[l],lmx[x]=rmx[x]=-sum[l],ans[x]=0;
	}
}
inline int getc(){
	char c=getchar();
	while(c!='('&&c!=')')c=getchar();
	return c=='('?1:-1;
}
signed main(){
	n=2*read()-1,m=read();
    for(int i=2;i<=n;i++)a[i]=getc();a[1]=1;\\手动补上根节点
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	SGT::build(1,1,n);printf("%d\n",SGT::ans[1]);
	for(int i=1;i<=m;i++){
		int x=read()+1,y=read()+1;\\因为前面多了一个点
		if(a[x]==1)SGT::upd(1,1,n,x,-2),a[x]=-1;
		else SGT::upd(1,1,n,x,2),a[x]=1;
		if(a[y]==1)SGT::upd(1,1,n,y,-2),a[y]=-1;
		else SGT::upd(1,1,n,y,2),a[y]=1;
		printf("%d\n",SGT::ans[1]);
	}return 0;
}
```


 


---

## 作者：GIFBMP (赞：11)

前言：写一发题解纪念这道让我想了两天的题目。

#### 正题

首先我们把原串中的左括号看作 $1$，右括号看作 $-1$，然后对于这个序列做前缀和，记作 $h$。画出 $h_i$ 关于 $i$ 的图像，我们可以发现，对于下图（其中红色的线代表 $h$ 的图像），所有黄色的线以上的每一座“山峰”就代表了一棵子树。

![](https://cdn.luogu.com.cn/upload/image_hosting/k3qizusa.png)

那么紧接着我们考虑，答案应该如何计算。首先我们考虑树上的的两点距离公式：$dis_{x,y}=dep_x+dep_y-2\times dep_{lca}$。我们把这个公式转化到 $h$ 的图像上，可以发现 $\forall x\le y$，有：

$$dis_{x,y}=h_x+h_y-2\times\min_{i=x}^y h_i$$

那么答案即为 $\max_{x\le y}dis_{x,y}$。

我们发现这个东西不是很好维护，但是我们考虑到一个性质，那就是如果在 $[x,y]$ 中有一个整数 $k$，且 $h_k$ 不等于 $\min_{i=x}^y h_i$，那么答案只会更劣。因此我们就可以把这层 $\min$ 的限制去掉，接下来问题就变简单了。

那么答案就可以转化为：

$$\max_{x\le y\le z}h_x+h_z-2\times h_y$$

看到这个东西，我们考虑用线段树维护。具体地，分别维护区间最大值（记作 $mx$），区间最小值（记作 $mn$），区间 $\max_{l\le x\le y\le r}h_x-2\times h_y$（记作 $pl$），区间 $\max_{l\le x\le y\le r}h_y-2\times h_x$（记作 $pr$），以及区间 $\max_{l\le x\le y\le z\le r}h_x+h_z-2\times h_y$（记作 $ans$）。

记 $o$ 为线段树的当前节点，$lc$，$rc$ 为 $o$ 的左右儿子，具体转移如下：

$$mx_o=\max{(mx_{lc},mx_{rc})}$$

$$mn_o=\min{(mn_{lc},mn_{rc})}$$

$$pl_o=\max{(pl_{lc},pl_{rc},mx_{lc}-2\times mn_{rc})}$$

$$pr_o=\max{(pr_{lc},pr_{rc},mx_{rc}-2\times mn_{lc})}$$

$$ans_o=\max{(ans_{lc},ans_{rc},mx_{lc}+pr_{rc},pl_{lc}+mx_{rc})}$$

紧接着我们考虑交换操作，对于每一对交换的 $(x,y)$ 不妨令 $x\le y$，如果 $x>y$ 则交换。再来看上面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/k3qizusa.png)

我们发现如果 $x$ 位置是左括号而 $y$ 位置是右括号，那么就相当于把 $[x,y-1]$ 中的所有 $h_i$ 减 $2$（见绿色部分）；如果 $x$ 位置是右括号而 $y$ 位置是左括号，那么就相当于把 $[x,y-1]$ 中的所有 $h_i$ 加 $2$（见蓝色部分）。于是我们只需要多一个区间加操作即可。

时间复杂度：$\Theta(n\log n)$。

Code:

```cpp
#include <cstdio>
#include <algorithm>
using namespace std ;
const int MAXN = 2e5 + 10 ;
int n , q , a[MAXN] , lz[MAXN << 2] ;
char ch[MAXN] ;
#define lc (o << 1)
#define rc (o << 1 | 1)
#define mid ((l + r) >> 1)
struct sgt {
	int mx , mn , pl , pr , ans ;
	sgt (int mx = 0 , int mn = 0 , int pl = 0 , int pr = 0 , int ans = 0) : mx(mx) , mn(mn) , pl(pl) , pr(pr) , ans(ans) {}
	sgt operator + (sgt x) const {
		sgt ret ;
		ret.mx = max (mx , x.mx) , ret.mn = min (mn , x.mn) ;
		ret.pl = max (max (pl , x.pl) , mx - 2 * x.mn) ;
		ret.pr = max (max (pr , x.pr) , x.mx - 2 * mn) ;
		ret.ans = max (max (ans , x.ans) , max (pl + x.mx , mx + x.pr)) ;
		return ret ;
	}
} t[MAXN << 2] ;
void build (int o , int l , int r) {
	if (l == r) {t[o] = sgt (a[l] , a[l] , -a[l] , -a[l] , 0) ; return ;}
	build (lc , l , mid) , build (rc , mid + 1 , r) , t[o] = t[lc] + t[rc] ;
}
void pushdown (int o) {
	if (!o || !lz[o]) return ;
	t[lc].mx += lz[o] , t[lc].mn += lz[o] , t[lc].pl -= lz[o] , t[lc].pr -= lz[o] , lz[lc] += lz[o] ;
	t[rc].mx += lz[o] , t[rc].mn += lz[o] , t[rc].pl -= lz[o] , t[rc].pr -= lz[o] , lz[rc] += lz[o] ;
	lz[o] = 0 ;
}
void upd (int o , int l , int r , int x , int y , int k) {
	if (x <= l && r <= y) {
		t[o].mx += k , t[o].mn += k , t[o].pl -= k , t[o].pr -= k , lz[o] += k ;
		return ;
	}
	pushdown (o) ;
	if (x <= mid) upd (lc , l , mid , x , y , k) ;
	if (mid < y) upd (rc , mid + 1 , r , x , y , k) ;
	t[o] = t[lc] + t[rc] ;
//	printf ("%d:[%d %d]\n" , o , l , r) ;
//	printf ("mx-%d,mn-%d,pl-%d,pr-%d,ans-%d\n" , t[o].mx , t[o].mn , t[o].pl , t[o].pr , t[o].ans) ;
}
int main () {
	scanf ("%d%d" , &n , &q) , scanf ("%s" , ch + 1) ; n = 2 * n - 2 ;
	for (int i = 1 ; i <= n ; i++) a[i] = (a[i - 1] + (ch[i] == '(' ? 1 : -1)) ;
	build (1 , 1 , n) ;
	printf ("%d\n" , max (t[1].ans , t[1].mx)) ;
	while (q--) {
		int x , y ; scanf ("%d%d" , &x , &y) ;
		if (x > y) swap (x , y) ;
		if (ch[x] == '(' && ch[y] == ')') upd (1 , 1 , n , x , y - 1 , -2) ;
		else if (ch[x] == ')' && ch[y] == '(') upd (1 , 1 , n , x , y - 1 , 2) ;
		swap (ch[x] , ch[y]) , printf ("%d\n" , max (t[1].ans , t[1].mx)) ;
		//puts (ch + 1) ;
	}
	return 0 ;
}
```

---

## 作者：yuzhechuan (赞：11)

很有意思的一道线段树小清新题

---

### 题解：

首先是一个前置知识（这里就难住了我QAQ）：括号序列的任意区间去掉匹配的括号对后都可以表示为一条树链，链长为剩余的括号序列的长度（其实自己口胡一下还是能明白的（大雾））

于是问题就变成了让你选出一个连续括号序列，使得非匹配括号的数量最多

然后就是经典套路了，将左括号看做1，右括号看做-1，问题变为找到相邻的两段，使后一段的数字和减前一段的数字和最大，这个差就是答案，特殊的，我们用$\Delta$表示这个差

问题终于转化完啦，下面就是考虑如何用线段树维护最大的$\Delta$了

区间最大$\Delta$不容易维护，所以我们可以维护区间前后缀的最大$\Delta$

pushup思路类似线段树维护区间最大子序列，我们还需要维护区间和，区间前后缀最大最小来辅助pushup

具体实现上可以看下代码

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=2e5+5;
int n,m;
char s[N];
int sum[N<<2],lma[N<<2],lmi[N<<2],rma[N<<2],rmi[N<<2],ld[N<<2],rd[N<<2],mad[N<<2],tr[N<<2];
//sum区间和，lma前缀大，lmi前缀小，rma后缀大，rmi后缀小，ld前缀右减左，rd后缀右减左，mad区间右减左，tr区间答案 

int max(int x,int y){
	return x>y?x:y;
}

int min(int x,int y){
	return x<y?x:y;
}

void pushup(int x){
	sum[x]=sum[x<<1]+sum[x<<1|1]; //直接加
	lma[x]=max(lma[x<<1],sum[x<<1]+lma[x<<1|1]); //经典分两类取最值
	rma[x]=max(rma[x<<1|1],sum[x<<1|1]+rma[x<<1]);
	lmi[x]=min(lmi[x<<1],sum[x<<1]+lmi[x<<1|1]);
	rmi[x]=min(rmi[x<<1|1],sum[x<<1|1]+rmi[x<<1]);
	ld[x]=max(ld[x<<1],max(ld[x<<1|1]-sum[x<<1],mad[x<<1]+lma[x<<1|1])); //类似上面的最大最小子段和
	rd[x]=max(rd[x<<1|1],max(sum[x<<1|1]+rd[x<<1],mad[x<<1|1]-rmi[x<<1]));
	mad[x]=max(mad[x<<1]+sum[x<<1|1],mad[x<<1|1]-sum[x<<1]);
	tr[x]=max(max(tr[x<<1],tr[x<<1|1]),max(ld[x<<1|1]-rmi[x<<1],rd[x<<1]+lma[x<<1|1])); //该区间答案的答案有四种情况，同样取个max
}

void build(int x,int l,int r){
	if(l==r){
		int v=s[l]=='('?1:-1;
		sum[x]=v; //赋初值
		lma[x]=rma[x]=max(v,0);
		lmi[x]=rmi[x]=min(v,0);
		ld[x]=rd[x]=mad[x]=tr[x]=1; //初始肯定是一个多余的括号
		return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}

void up(int x,int l,int r,int p,int v){
	if(l==r){
		sum[x]=v;
		lma[x]=rma[x]=max(v,0);
		lmi[x]=rmi[x]=min(v,0);
		ld[x]=rd[x]=mad[x]=tr[x]=1;
		return ;
	}
	int mid=l+r>>1;
	if(p<=mid) up(x<<1,l,mid,p,v);
	else up(x<<1|1,mid+1,r,p,v);
	pushup(x);
}

signed main(){
	read(n);read(m);scanf("%s",s+1);
	n=n-1<<1; //括号序列的长度
	build(1,1,n);
	write(tr[1]);puts("");
	while(m--){
		int x,y;
		read(x);read(y);
		if(s[x]!=s[y]){ //小优化，相同就不用做了（但其实期望1/2的操作都能被跳过）
			swap(s[x],s[y]);
			up(1,1,n,x,s[x]=='('?1:-1); //单点修改
			up(1,1,n,y,s[y]=='('?1:-1);
		}
		write(tr[1]);puts("");
	}
}
```

---

## 作者：command_block (赞：8)

**题意** : 给出一棵以括号序列描述的树。

资瓷交换两个括号(不一定相邻,保证仍为一棵树),求直径。

$n,q\leq 10^5$ ,时限$\texttt{2s}$。

------------

同学 : 欸这个括号序列挺有趣的,你学不学啊。

我 : 这个题搞个欧拉序也行吧,再不济直接动态链分治。改天再学吧 (咕

直到我遇见了这题……题目中直接蕴含该知识点。

括号序可以视作有进有出的`dfs`序,有如下结论:

- 选取 $u,v$ 之间的括号,全部**匹配**对消完毕之后,剩余形如 `))))(((`。

  剩余括号个数即为 $dis(u,v)$ ,可以给括号加权。
  
证明 : 考虑到达 $a$ 点时 $b$ 的两个括号可能的状态。

- ① 均填完
 
  $b$ 不是 $a$ 的祖先或子孙。
  
- ② 均未填

  $b$ 不是 $a$ 的祖先。

- ③ 只填写了左边

  $b$ 是 $a$ 的祖先。
 
$u,v$ 之间,能够匹配的括号们,对于 $u$ 是情况②,对于 $v$ 是情况①,均不在路径上。

对于余下的右括号,对于 $u$ 是情况③,对于 $v$ 是情况 ①,对应 “既是 $u$ 的祖先,又不是 $v$ 的祖先”的路径,即为蓝色部分。

对于余下的左括号,对于 $u$ 是情况②,对于 $v$ 是情况 ③,对应 “既是 $v$ 的祖先,又不是 $u$ 的祖先”的路径,即为红色部分。

红蓝两种颜色恰好拼成 $u,v$ 两点间的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/gsj3e2t0.png?x-oss-process=image/resize,m_lfit,h_300)

那么,我们只需要维护任意区间内未匹配括号的最大数量即可。

给 $"("$ 赋权 $+1$ , 给 $")"$ 赋权 $-1$ 。

一段括号序列对消完毕之后,假设分界线前面的和为 $s1$ (负数),分界线后面的和为 $s2$ ,则剩余括号个数为 $s2-s1$。

若我们选择的不是实际的分界线,答案一定更劣(依赖于权值非负),所以不必特殊考虑。

现在就是要维护 : 相邻的两段区间和的差的最大值。资瓷单点修改。

使用线段树维护。

每个区间要记录区间和 $s$ ,最小后缀 $r0$ ,最大后缀 $r1$ ,最小前缀 $l0$ ,最大前缀 $l1$,

左侧完整(贡献为负),经过分界线,右侧贴右端点的最大值 $rm$。

右侧完整,经过分界线,左侧(贡献为负)贴左端点的最大值 $lm$。

左右侧均贴端点的最大值 $lrm$。

区间内部的答案 $m$。

> 觉得费脑子可以直接`DDP`,然后化简矩阵,不过估计也挺麻烦。

转移具体细节请见代码。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define MaxN 200500
using namespace std;
struct Node
{int s,r0,l1,rm,lm,lrm,m;}
a[MaxN<<2];
inline void up(int u)
{
  int l=u<<1,r=u<<1|1;
  a[u].s=a[l].s+a[r].s;
  a[u].l1=max(a[l].l1,a[l].s+a[r].l1);
  a[u].r0=min(a[l].r0+a[r].s,a[r].r0);
  a[u].lm=max(a[l].lm,max(a[l].lrm+a[r].l1,a[r].lm-a[l].s));
  a[u].rm=max(a[r].rm,max(a[r].lrm-a[l].r0,a[l].rm+a[r].s));
  a[u].lrm=max(a[l].lrm+a[r].s,a[r].lrm-a[l].s);
  a[u].m=max(max(a[l].m,a[r].m),max(a[l].rm+a[r].l1,a[r].lm-a[l].r0));
}
char str[MaxN];
int n,m;
void build(int l=1,int r=n,int u=1)
{
  if (l==r){
    int x=(str[l]=='(' ? 1 : -1);
    a[u].l1=max(x,0);a[u].r0=min(a[u].s=x,0);
    a[u].rm=a[u].lm=a[u].lrm=a[u].m=(x<0 ? -x : x);
    return ;
  }int mid=(l+r)>>1;
  build(l,mid,u<<1);
  build(mid+1,r,u<<1|1);
  up(u);
}
int to;
void chg(int l=1,int r=n,int u=1)
{
  if (l==r){
    int x=(str[l]=='(' ? 1 : -1);
    a[u].l1=max(x,0);a[u].r0=min(a[u].s=x,0);
    a[u].rm=a[u].lm=a[u].lrm=a[u].m=(x<0 ? -x : x);
    return ;
  }int mid=(l+r)>>1;
  if (to<=mid)chg(l,mid,u<<1);
  else chg(mid+1,r,u<<1|1);
  up(u);
}
int main()
{
  scanf("%d%d%s",&n,&m,str+1);
  n=n*2-2;
  build();printf("%d\n",a[1].m);
  for (int i=1,x,y;i<=m;i++){
    scanf("%d%d",&x,&y);
    swap(str[x],str[y]);
    to=x;chg();
    to=y;chg();
    printf("%d\n",a[1].m);
  }return 0;
}
```






---

## 作者：Mihari (赞：6)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1149C)

# 题解

首先搞明白建树的方式：遇到左括号往下走，遇到右括号往回走.现在我们要求这个构造出来的树的直径.

由于每一次都会互换两个括号的位置，所以显然树的形态是不固定的，进而如果我们每次将树构造出来跑树 $\tt DP$ 显然不可取，这样复杂度为 $\mathcal O(qn)$，对于 $n\le 100000$ 以及 $n,q$ 同阶来说直接 $\tt TLE$.

那么我们要想一种能将快速求直径的方法，并且在树形态发生改变之后亦可以快速维护，那么此时需要对这道题的性质进行挖掘.

我们考虑，在用括号表达这个树之后，两点之间的距离是什么：

由于一个左括号往下，一个右括号往上，不难发现，对于这个括号序列的两点，他们**所表示的点的距离**为：

> 将形如 $\tt ()$ 的可匹配括号去掉之后，剩下的括号的数量.

**对于区间进行操作以及修改，不难想到用线段树维护答案.**

同时，树的直径，即可表示为

> 任取括号序列的一段区间，在去掉可匹配括号之后，剩下来的括号的最长长度.

并且，显然有将一个序列的可匹配括号删去之后，剩下的只可能长得像 $\tt )))))(($，可以不存在左括号或者右括号.

我们考虑合并答案，假设这个区间的左子区间有右括号 $a$ 个，左括号 $b$ 个，右子区间有右括号 $c$ 个，左括号 $b$ 个，那么这个区间从中间合并的答案就是 

$$
a+|b-c|+d
$$
这个绝对值很烦，我们考虑将其去掉，那么，原式变成了
$$
\max\{a+b-c+d,a-b+c+d\}
$$
我们考虑上式需要维护的东西：

1. $a+b$，即一个区间在去掉可匹配括号之后的后缀右括号加上后缀左括号的最大值；
2. $a-b$，即一个区间在去掉可匹配括号之后的后缀右括号减去后缀左括号的最大值；
3. $d-c$，即一个区间在去掉可匹配括号之后的前缀左括号减去前缀右括号的最大值；
4. $c+d$，即一个区间在去掉可匹配括号之后的前缀左括号加上前缀右括号的最大值；

我们分别记这四个值为 $x,y,z,k$.

现在考虑我们怎么维护这四个值，我们拿 $x$ 举例子（其他都差不多了）：

对于区间 $i$，记其左右儿子分别为 $ls,rs$，如果这个最优点划分在右边，那么直接就可以使用 $rs$ 的 $x$ 对答案进行取最优，但是，如果最优点划分在左边，即说明右边已经全部入选，那么我们需要将右边匹配完之后剩下的左括号、右括号分别记作 $l,r$，那么，我们现在所知的就是，右边已经形如 $\tt )))(($ 的结构，我们要在左边的哪里选择划分才能达到让 $x$ 最大，考虑在左边选择的划分点以后有 $a$ 的右括号，$b$ 个左括号，那么 $x$ 就可以表示为
$$
x=a+|b-r|+l
$$
用同样的方法去掉绝对值，有
$$
x=\max\{a+b-r+l,a-b+r+l\}
$$
同时，我们有 $x_{ls}=a+b,y_{ls}=a-b$，由于我们是上传，那么 $ls$ 以及 $rs$ 的信息都是已知的，那么全部整合在一起，就有
$$
x_i=\max\{x_{rs},\;x_{ls}-r_{rs}+l{rs},\;y_{ls}+l_{rs}+r_{rs}\}
$$
由维护过程可知，我们还得再多维护俩值：一个区间的 $l,r$，即将这个区间全部进行匹配之后，剩下的左括号、右括号个数，这个很好进行维护.

对于 $y,z,k$ 的维护同理.

最终复杂度为 $\mathcal O(n\log n+q\log n)$.

# 代码

```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
using namespace std;
namespace Elaina{
    # define rep(i,l,r) for(int i=l, i##_end_ = r; i <= i##_end_; ++ i)
    # define fep(i,l,r) for(int i=l, i##_end_ = r; i >= i##_end_; -- i)
    # define fi first
    # define se second
    # define Endl putchar('\n')
    # define writc(x, c) fwrit(x), putchar(c)
    // # define int long long
    typedef long long ll;
    typedef pair<int, int> pii;
    typedef unsigned long long ull;
    typedef unsigned int uint;
    template<class T>inline T Max(const T x, const T y){return x < y ? y : x;}
    template<class T>inline T Min(const T x, const T y){return x < y ? x : y;}
    template<class T>inline T fab(const T x){return x < 0 ? -x : x;}
    template<class T>inline void getMax(T& x, const T y){x = Max(x, y);}
    template<class T>inline void getMin(T& x, const T y){x = Min(x, y);}
    template<class T>T gcd(const T x, const T y){return y ? gcd(y, x % y) : x;}
    template<class T>inline T readin(T x){
        x=0; int f = 0; char c;
        while((c = getchar()) < '0' || '9' < c) if(c == '-') f = 1;
        for(x = (c ^ 48); '0' <= (c = getchar()) && c <= '9'; x = (x << 1) + (x << 3) + (c ^ 48));
        return f ? -x : x;
    }
    template<class T>void fwrit(const T x){
        if(x < 0)return putchar('-'), fwrit(-x);
        if(x > 9)fwrit(x / 10); putchar(x % 10 ^ 48);
    }
}
using namespace Elaina;

const int maxn = 1e6;

char s[maxn + 5];

int n, q;

struct node{
    // 下面维护的都是最大值
    /** @brief 后缀右括号加上后缀左括号*/
    int x;
    /** @brief 后缀右括号减去后缀左括号*/
    int y;
    /** @brief 前缀左括号减去前缀右括号*/
    int z;
    /** @brief 前缀左括号加上前缀右括号*/
    int k;
    /** @brief 合并整个区间之后, 剩下的左括号*/
    int l;
    /** @brief 合并整个区间之后, 剩下的右括号*/
    int r;
    /** @brief 区间答案*/
    int ans;
}tre[maxn * 4 + 5];
# define ls (i << 1)
# define rs (i << 1 | 1)
# define mid ((l + r) >> 1)
# define _lq ls, l, mid
# define _rq rs, mid + 1, r
inline void pushup(const int i){
    if(tre[ls].l > tre[rs].r){
        tre[i].l = tre[ls].l - tre[rs].r + tre[rs].l;
        tre[i].r = tre[ls].r;
    } else {
        tre[i].l = tre[rs].l;
        tre[i].r = tre[rs].r - tre[ls].l + tre[ls].r;
    }
    tre[i].x = Max(tre[rs].x, Max(tre[ls].x + tre[rs].l - tre[rs].r, tre[ls].y + tre[rs].r + tre[rs].l));
    tre[i].y = Max(tre[rs].y, tre[ls].y + tre[rs].r - tre[rs].l);
    tre[i].z = Max(tre[ls].z, tre[ls].l - tre[ls].r + tre[rs].z);
    tre[i].k = Max(tre[ls].k, Max(tre[ls].l + tre[ls].r + tre[rs].z, tre[ls].r - tre[ls].l + tre[rs].k));
    tre[i].ans = Max(Max(tre[ls].x + tre[rs].z, tre[ls].y + tre[rs].k), Max(tre[ls].ans, tre[rs].ans));
}
/** @param x 如果是 -1 就是右括号, 如果是 1 就是左括号*/
inline void modify(const int p, const int x, const int i = 1, const int l = 1, const int r = n){
    if(l == r){
        tre[i].x = tre[i].k = 1;
        tre[i].y = Max(-x, 0);
        tre[i].z = Max(x, 0);
        tre[i].l = (x == 1), tre[i].r = (x == -1);
        tre[i].ans = 1;
        return;
    }
    if(p <= mid) modify(p, x, _lq);
    else modify(p, x, _rq);
    pushup(i);
}
void build(const int i = 1, const int l = 1, const int r = n){
    if(l == r){
        int x = (s[l] == '(') ? 1 : -1;
        tre[i].x = tre[i].k = 1;
        tre[i].y = Max(-x, 0);
        tre[i].z = Max(x, 0);
        tre[i].l = (x == 1), tre[i].r = (x == -1);
        tre[i].ans = 1;
        return;
    }
    build(_lq), build(_rq);
    pushup(i);
}

void print(const int i = 1,const int l = 1, const int r = n){
    if(l != r) print(_lq), print(_rq);
    printf("node %d :> l == %d, r == %d\n", i, l, r);
    printf("x == %d, y == %d, z == %d, k == %d, ans == %d\n", tre[i].x, tre[i].y, tre[i].z, tre[i].k, tre[i].ans);
    printf("l == %d, r == %d\n", tre[i].l, tre[i].r);
    puts("-----------------------------------------");
    
}

inline void init(){
    n = readin(1), q = readin(1);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    build();
    // print();
}

signed main(){
    init();
    printf("%d\n", tre[1].ans);
    int x, y;
    while(q --){
        x = readin(1), y = readin(1);
        modify(x, s[y] == '(' ? 1 : -1);
        modify(y, s[x] == '(' ? 1 : -1);
        swap(s[x], s[y]);
        printf("%d\n", tre[1].ans);
        // print();
    }
    return 0;
}
```



---

## 作者：Arghariza (赞：5)

[$\color{plum}\mathtt{600AC}$](https://www.luogu.com.cn/problem/CF1149C) 题解。

首先显然序列上两个点 $u,v$ 的距离就是将这个括号序列匹配的括号删除掉，剩下的括号个数。

所以答案即求出最大的区间使得里面**不匹配的括号最多**。

单点修改，考虑用线段树维护，如何合并两个区间。

合并两个区间时，假设左区间右括号数为 $a$ ，左括号数为 $b$ ，右区间右括号数为 $c$ ，左括号数为 $d$ 。合并时对答案的贡献为 $a\ +\mid b-c\mid +\ d$ ，加上绝对值还要维护正负性，直接换成 $\max\{a+b-c+d,a-b+c+d\}$  。

由于答案求的是 $\max$ 值，我们考虑把这玩意分开来求。由上式得出我们对于每一个树上的点只需维护其**后缀左括号+后缀右括号、后缀左括号-后缀右括号、前缀右括号+前缀左括号、前缀右括号-前缀左括号**的值即可。

如何维护就要看代码细节了，括号加加减减不容易说明（好吧其实是懒）![](https://啧.tk/doge)

代码出奇地简洁，不超 $\mathtt {100}$ 行。

$\mathtt{3.3s}$ ，~~算是人傻常数大吧~~：

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 1e6 + 100;
int n, m;
char ch[maxn];

#define max2 max
#define max3(x, y, z) max2(x, max2(y, z))
#define max4(x, y, z, w) max2(max2(x, y), max2(z, w))
int get(char x) { return x == '(' ? 1 : -1; }
struct segtree {
    #define ls(x) x << 1
    #define rs(x) x << 1 | 1
    int a[maxn << 2], b[maxn << 2], c[maxn << 2], d[maxn << 2], l[maxn << 2], r[maxn << 2], t[maxn << 2];
    void pushup(int x) {
        if (l[ls(x)] <= r[rs(x)]) {
            l[x] = l[rs(x)];
            r[x] = r[rs(x)] - l[ls(x)] + r[ls(x)];
        } else {
            l[x] = l[ls(x)] - r[rs(x)] + l[rs(x)];
            r[x] = r[ls(x)];
        }
        a[x] = max3(a[rs(x)], a[ls(x)] + l[rs(x)] - r[rs(x)], b[ls(x)] + r[rs(x)] + l[rs(x)]);
        b[x] = max2(b[rs(x)], b[ls(x)] + r[rs(x)] - l[rs(x)]);
        c[x] = max2(c[ls(x)], l[ls(x)] - r[ls(x)] + c[rs(x)]);
        d[x] = max3(d[ls(x)], l[ls(x)] + r[ls(x)] + c[rs(x)], r[ls(x)] - l[ls(x)] + d[rs(x)]);
        t[x] = max4(a[ls(x)] + c[rs(x)], b[ls(x)] + d[rs(x)], t[ls(x)], t[rs(x)]);
    }
    void build(int ls, int rs, int x) {
        if (ls == rs) {
            int chk = get(ch[ls]);
            a[x] = d[x] = 1;
            b[x] = max2(-chk, 0);
            c[x] = max2(chk, 0);
            l[x] = (chk == 1);
            r[x] = (chk == -1);
            t[x] = 1;
            return;
        }
        int mid = (ls + rs) >> 1;
        build(ls, mid, ls(x));
        build(mid + 1, rs, rs(x));
        pushup(x);
    }
    void update(int ls, int rs, int pos, int chk, int x) {
        if (ls == rs) {
            a[x] = d[x] = 1;
            b[x] = max2(-chk, 0);
            c[x] = max2(chk, 0);
            l[x] = (chk == 1);
            r[x] = (chk == -1);
            t[x] = 1;
            return;
        }
        int mid = (ls + rs) >> 1;
        if (pos <= mid) update(ls, mid, pos, chk, ls(x));
        else update(mid + 1, rs, pos, chk, rs(x));
        pushup(x);
    }
} st;

int main() {
    n = read();
    m = read();
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    st.build(1, n, 1);
    write(st.t[1]);
    puts("");
    for (int i = 1, x, y; i <= m; i++) {
        x = read();
        y = read();
        st.update(1, n, x, get(ch[y]), 1);
        st.update(1, n, y, get(ch[x]), 1);
        swap(ch[x], ch[y]);
        write(st.t[1]);
        puts("");
    }
    return 0;
}
```

---

## 作者：UperFicial (赞：3)

> [**CF1149C Tree Generator™**](https://www.luogu.com.cn/problem/CF1149C)

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16755771.html)。

牛逼题 & ZROI Day3 数据结构选讲。

来一波详细的题解。

当时和 $\texttt{ys}$，$\texttt{hy}$ 还有[小猴子](https://www.luogu.com.cn/user/331947)讨论了半天，一直认为是最大子段和很激动直接就在群里说了，结果被喷了，然后一波周折群友觉得这是十分正确的，然后一波周折又被喷了（

考虑把 `(` 看成深度 $+1$，`)` 看成深度 $-1$，那么就可以把括号序列看成一个 $+1$ 和 $-1$ 的序列。

考虑一条路径的长度如何算，对于一段 $u\to \operatorname{lca}(u,v)\to v$ 的路径，在括号序列上肯定会被表示成形如 `)...)(...(` 的一段，路径长度为 `(` 括号数量 $+$ `)` 括号数量。

但是，如果路径上还会有一个子树，比如形如 `)..()..)(..(`，`()` 是需要忽略不计的。

由此我们得到结论：**括号序列上任何一个子区间，去掉所有匹配的括号后，得到的括号序列一定是树上一条链**。如果用权值表示法来表示，你会发现其实匹配的括号根本不用管，因为一个 $(+1)$ 和一个 $(-1)$ 都消掉了，如果我们称 `)(` 为分界点，`(` 右边的部分为右区间，`)` 左边的部分为左区间，那么这条路径的长度为，右区间的权值和 $+$ 左区间权值和的**相反数**，因为左区间的 `)` 我们表示成了 $-1$，现在需要算成 $1$ 的长度。

对此，我们又得到一个结论：**对于所有子区间，找到一个分界点，右区间权值和 $-$ 左区间权值和的最大值，为这个子区间的路径长度最大值。**

那么显然，树的直径是对于**所有子区间**，找到一个分界点后的权值最大值。

交换字符可以看成 $\Theta(1)$ 的修改，那么很自然地想到用线段树来维护这个东西，且类似于最大子段和。

维护区间答案 $\text{ans}$，后缀最大值 $\text{sm}$，后缀最小值 $\text{sn}$，前缀最大值 $\text{pm}$，前缀最小值 $\text{pn}$。

但这样是不足以转移的，比如左区间是 `)))` 右区间是 `))(`，你完全可以一起拼一块儿。

所以我们还要维护一下，紧靠左端点的答案最大值 $\text{lm}$，紧靠右端点答案最大值 $\text{rm}$，紧靠左右端点的答案最大值 $\text{lrm}$，以及区间和 $\text{sum}$。

考虑 $\texttt{pushup}$ 的过程，设 $u$ 的左右儿子分别为 $u_0$ 和 $u_1$。

- 首先很显然的 $\text{ans}_u\leftarrow \max(\text{ans}_{u_0},\text{ans}_{u_1})$。

- 还可以是左区间已经是包含右端点的完整答案了，右区间在拼上一个 `(..(` 的最长前缀，$\text{ans}_u\leftarrow \text{rm}_{u_0}+\text{pm}_{u_1}$。

- 当然完整答案在右区间的情况也同理，$\text{ans}_u\leftarrow \text{lm}_{u_1}-\text{sn}_{u_0}$。

前缀最小值 / 最大值都可以通过区间和来转移，考虑 $\text{lm}$ 的转移，首先可以直接继承 $\text{lm}_{u_0}$，还让左区间紧靠左右端点的答案再拼上右端点的 `(..(`，即 $\text{lrm}_{u_0}+\text{pm}_{u_1}$，还可以是右区间选择一个紧靠左端点的答案段 `)..)(..(`，然后左区间全部选择，只不过这里需要注意取反，$\text{lm}_{u_1}-\text{sum}_{u_0}$。$\text{rm}$ 是同理的。

$\text{sum}$ 直接将左右区间的 $\text{sum}$ 加起来就行了。

最后还剩一个 $\text{lrm}$，这个很简单，只需要一个区间选择 $\text{lrm}$ 另一个区间选择 $\text{sum}$，同样注意变号的问题：$\text{lrm}_u\leftarrow\max(\text{lrm}_{u_0}+\text{sum}_{u_1},\text{lrm}_{u_1}-\text{sum}_{u_0})$。

这样就都处理完毕啦。

[**code**](https://codeforces.com/contest/1149/submission/174713590)。

---

## 作者：SunsetSamsara (赞：2)

## 题意

一棵树有 $n$ 个，给你括号序列，输出它的直径。

接下来有 $m$ 次询问，每次询问表示交换两个括号，输出交换两个括号后的直径（保证每次操作后都为一棵树）

$3 \le n \le 100\,000,1 \le q \le 100$

## 分析

这题有一个很重要的结论：

> 任意一个括号序列的子串都表达一条链，这条链的长度就是括号序列消去匹配括号后的剩余括号个数。

证明：

> 取一段括号序列，则里面的匹配括号一定表达若干棵完整的子树（就是往上/往下走时跳过的子树）。而剩余的括号，就是没有完整的子树的结点的左/右括号。因为剩余的括号中没有匹配的括号，所以没有任何一个没有完整子树的结点占有 $2$ 个括号。这样的话就可以知道，剩余括号个数就是没有完整子树的结点个数了。而没有完整子树的结点个数就是链的长度，所以这个结论成立。

那么，直径就显然为所有子串中消去匹配的括号后未匹配的括号个数最大值。


这时，将 `(` 赋值为 $1$，`)` 赋值为 $-1$，就会有：

所有子串中消去匹配的括号后未匹配的括号个数最大值就是将区间分成两段后后半部分的权值和减去前半部分权值和的最大值。

至于原因，是因为后半部分减去前半部分可以用权值消去匹配的括号（尝试统计一下相消的括号就会发现能够消去的括号对答案没有任何影响）。

这时候就可以用线段树维护这些杂七杂八的信息了。我们要在线段树节点上维护一些值：区间和，前缀连续最大值和最小值，后缀连续最大值和最小值（到这里都和维护最大子段和类似）。还要维护前缀、后缀连续选的后半部分减前半部分最大值，才能维护整个区间的后半部分减前半部分最大值。

看上去很多，但是其实整个实现不长，和最大子段和有可比性。

## 代码

```cpp
static const int BUFSIZE = 1 << 23;
static const int prec = 10;
extern "C++" {
#define reg register
template<class Tp>inline const Tp&min(reg const Tp &x,reg const Tp&y){return x<y?x:y;}
template<class Tp>inline const Tp&max(reg const Tp &x,reg const Tp&y){return x<y?y:x;}
typedef long long lld;const int inf=0x3f3f3f3f;const lld inflld=0x3f3f3f3f3f3f3f3fll;
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
using std::pair,std::make_pair,std::swap,std::sort,std::next_permutation,std::prev_permutation;
using std::string,std::vector,std::map,std::set,std::queue,std::enable_if,std::is_integral,std::is_same;
using std::is_floating_point,std::is_pointer,std::is_lvalue_reference,std::remove_reference, std::is_const;
char iBuf[BUFSIZE],oBuf[BUFSIZE],*iEnd,*iP,*oEnd,*oP;
#ifdef ONLINE_JUDGE
#define getchar() (iP==iEnd?iEnd=(iP=iBuf)+fread(iBuf,1,sizeof(iBuf),stdin),(iP==iEnd?EOF:*iP++):*iP++)
#define putchar(ch) (oP==oEnd?fwrite(oBuf,1,BUFSIZE,stdout),*(oP++)=ch:*(oP++)=ch)
#endif
inline lld qpow(lld x,lld y,lld p){reg lld t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}
template<class Tp>inline void read(char&x){for(;isspace(x=getchar()););}
inline void read(char*x){
	reg int t=1;for(;isspace(*x=getchar()););
	for(;!isspace(x[t ++]=getchar()););x[t]=0;
}
template<class Tp>typename enable_if<is_integral<Tp>::value^is_same<Tp,char>::value,void>::type
inline read(Tp&x){
	x=0;reg char ch,f=1;for(;!isdigit(ch=getchar());)f=ch=='-'?-1:f;x=ch&15;
	for(;isdigit(ch=getchar());)x=(x<<3)+(x<<1)+(ch&15);x*=f;
}
template<class Tp,class=typename enable_if<is_floating_point<Tp>::value&&!is_integral<Tp>::value,void>::type>
inline void read(Tp&x){
	reg char f=1,ch;x=0;reg Tp val=0.1;for(;!isdigit(ch=getchar());)f=ch=='-'?-1:f;
	for(x=ch&15;isdigit(ch=getchar());)x=x*10+(ch&15);
	if(ch=='.')for(;isdigit(ch=getchar());val/=10)x+=(ch&15)*val;x*=f;
}
template <typename T>
using is_pointer_or_ref=std::integral_constant<bool,is_pointer<T>::value||
(is_lvalue_reference<T>::value&&!is_const<typename remove_reference<T>::type>::value)>;
template<typename...Conds>struct and_:std::true_type{};template<typename Cond,typename... Conds>
struct and_<Cond,Conds...>:std::conditional<Cond::value,and_<Conds...>,std::false_type>::type{};
template <typename...Ts>using are_pointer_or_ref=and_<is_pointer_or_ref<Ts>...>;inline void scan(){}
template<typename Tp,typename...Tps,typename enable_if<are_pointer_or_ref<Tps...>::value>::type* =nullptr>
inline void scan(reg Tp&x,reg Tps&&...t){read(x);scan(t...);}
template<typename Tp,typename...Tps,typename enable_if<are_pointer_or_ref<Tps...>::value>::type* =nullptr>
inline void scan(reg Tp*x,reg Tps&&...t){read(x);scan(t...);}

inline void write(const char&x){putchar(x);}
inline void write(const char*x){for(int t=0;x[t];++t)putchar(x[t]);}
template<class Tp>typename enable_if<is_integral<Tp>::value^is_same<Tp,char>::value,void>::type
inline write(const Tp&x){
	if(!x){putchar('0');return;}static char buf[256];reg int cnt=0;reg Tp cpy=x;
	if(x<0)putchar('-'),cpy=-x;for(;cpy;cpy/=10)buf[cnt++]=(cpy%10)+48;for(--cnt;~cnt;--cnt)putchar(buf[cnt]);
}
template<class Tp,class=typename enable_if<is_floating_point<Tp>::value&&!is_integral<Tp>::value,void>::type>
inline void write(const Tp&pr) {
	reg Tp cpy=pr,res=0.5;for(int i=1;i<=prec;++i)res/=10;cpy+=res,write((__int128)cpy);putchar('.');
	cpy-=(__int128)cpy;for(int i=1;i<=prec;++i)cpy=(cpy-(int)cpy)*10,putchar((int)cpy+'0');
}
inline void print(){}
template<typename Tp,typename...Tps>
inline void print(reg const Tp&x,reg Tps&&...t){write(x);print(t...);}
template<typename Tp,typename...Tps>
inline void print(reg const Tp*x,reg Tps&&...t){write(x);print(t...);}
struct tmp_s{tmp_s(){iP=iEnd=iBuf,oP=oBuf,oEnd=oBuf+BUFSIZE;}~tmp_s(){fwrite(oBuf,1,oP-oBuf,stdout);}}tmp_v;
}
const int N = 200010;
char s[N];
struct node {
	int sum;
	int prex, prem;
	int sucx, sucm;
	int pred, sucd;
	int d, ans;
} tr[N << 2];
const node L = (node){1, 1, 0, 1, 0, 1, 1, 1, 1};
const node R = (node){-1, 0, -1, 0, -1, 1, 1, 1, 1};
char str[N];
node operator + (const node &x, const node &y) {
	node z;
	z.prex = max(x.prex, x.sum + y.prex);
	z.sucx = max(y.sucx, x.sucx + y.sum);
	z.prem = min(x.prem, x.sum + y.prem);
	z.sucm = min(y.sucm, x.sucm + y.sum);
	z.d = max(y.d - x.sum, x.d + y.sum);
	z.pred = max(x.pred, max(y.pred - x.sum, x.d + y.prex));
	z.sucd = max(y.sucd, max(y.sum + x.sucd, y.d - x.sucm));
	z.sum = x.sum + y.sum;
	z.ans = max(max(x.ans, y.ans), max(y.pred - x.sucm, x.sucd + y.prex));
	return z;
}
void build(int k, int l, int r) {
	if (l == r) {
		if (str[l] == '(') tr[k] = L;
		else tr[k] = R;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tr[k] = tr[k << 1] + tr[k << 1 | 1];
}
void modify(int k, int l, int r, int pos) {
	if (l == r) {
		if (str[l] == '(') tr[k] = L;
		else tr[k] = R;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) modify(k << 1, l, mid, pos);
	else modify(k << 1 | 1, mid + 1, r, pos);
	tr[k] = tr[k << 1] + tr[k << 1 | 1];
}
int n, m;
int main() {
	scan(n, m, str + 1);
	n = 2 * n - 2;
	build(1, 1, n);
	print(tr[1].ans, '\n');
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		scan(a, b);
		swap(str[a], str[b]);
		modify(1, 1, n, a);
		modify(1, 1, n, b);
		print(tr[1].ans, '\n');
	}
}
```

---

## 作者：xfrvq (赞：2)

[$\tt Link$](/problem/CF1149C)。

树在变化且变化没有规律，我们不好维护树，考虑从括号序入手。

首先讨论一条链在括号序上是怎样的。

+ $\color{red})\cdots)\color{green}(\cdots($
+ $\color{red}(\cdots(\color{green}(\cdots($
+ $\color{red})\cdots)\color{green})\cdots)$

红色和绿色是一段连续的左括号或右括号（路径部分），但是还有一些括号穿插其中，它们互相匹配但是不会在这条链上。

如果带上其它的部分是不好讨论的，我们希望用合理的方法规避掉那些部分。

考虑把左括号和右括号的权值记为 $1,-1$，然后这时 $1\cdots n$ 的直径长度就是 **找到 $p\in[1,n]$，最大的 $\Sigma(p,n]-\Sigma[1,p]$**，其中 $\Sigma$ 为一个区间的权值和。

这样似乎考虑有时把一对括号拆开？并不，拆开一对括号会让答案减小 $2$，所以为了答案的 $\max$ 一定不会拆开括号。

单点修改，全局查询这玩意（但是这玩意并不好搞），考虑上线段树。

这个有点类似最大子段和。线段树维护这些东西：

1. 区间和（辅助转移）
1. 从左或右开始的最大连续和
1. 从左或右开始的最大的差
1. 整个区间的最大的差
1. 区间内（不受限制）的最大的差

转移看代码。主要思想就是看选择的 $p$ 是在这个点的左子树还是右子树。

<https://codeforces.com/contest/1149/submission/166449731>

---

## 作者：天梦 (赞：2)

这个题卡了我较长时间。

因为需要支持区间修改，无法用离线算法维护，所以我们考虑用线段树在线维护。

用线段树维护的难点在于合并信息。

首先我们这样用括号序列构造这棵树：遇到左括号往儿子走，右括号往父亲走，所以，树的直径在线段树上就是这样的：


$$
\texttt{))))))((((((((}
$$
我们考虑一个区间中的最大直径，首先与左右两边最大区间求最值，这个不用说，我们考虑如何合并两段。

我们设参与合并的左区间的左括号数量为 $a$，右括号数量为 $b$，参与合并的右区间的左括号数量为 $c$ 右括号数量为 $d$，那么我们有答案为：
$$
b+|a-d|+c
$$
之所以是这个答案，是因为左边右边组成的区间同样也是形如上面的括号序列，这是因为任意一个区间，把能消除的都消除，就会变成上面那个式子。

我们把绝对值拆开：
$$
\max(b+a-d+c,b-a+d+c)
$$
不难发现如果我们单独维护 $a,b,c,d$ 是比较难维护的，所以我们考虑维护 $a+b,b-a,c-d,d+c$。

怎么维护？我们先考虑这些值的意义，不难发现这些意义分别是：

+ $a+b$ 后缀左括号加右括号最大值。
+ $b-a$ 后缀右括号减左括号最大值。
+ $c-d$ 前缀左括号减右括号最大值。
+ $d+c$ 前缀左括号加右括号最大值。

注意，上面的所有意义都是在合并了一些之后，形如 $\texttt{)))))((((((}$​​ 的左右括号最值。

我们考虑如何维护上面的值，以维护第一个举例，设其为 $x$。

首先我们考虑这个后缀的开始位置。如果开始位置在右区间，显然值应该是右区间的 $x$。

如果开始位置在左区间，首先，这个一定包含了右区间，设右区间全部合并左括号数量为 $l$​ ，右括号数量为 $r$​，左区间部分的左括号为 $a$​，右括号为 $b$​，那么答案为 $b+|a-r|+l$​，我们再次分类讨论：
$$
\max(b+a-r+l,b-a+r-l)
$$
 不难发现最大化的 $a+b,b-a$ 是我们要维护的值。而 $l,r$ 也好维护。

所以我们就可以用线段树做了，代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 300010
#define M 700010
using namespace std;

const int INF=0x3f3f3f3f;
const int MAXN=1e7+10;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,a[N];

struct node{
    ll val;
    int lazy,maxx,minn,len;
    bool op;
    node(){op=0;}
};

bool NotPrime[MAXN];
int prime[M],tail,Phi[MAXN];

inline void GetPhi(){
    NotPrime[1]=1;Phi[1]=1;
    for(int i=2;i<=1e7;i++){
        if(!NotPrime[i]){prime[++tail]=i;Phi[i]=i-1;}
        for(int j=1;j<=tail&&i*prime[j]<=1e7;j++){
            int k=i*prime[j];
            NotPrime[k]=1;
            if(i%prime[j]==0){
                Phi[k]=Phi[i]*prime[j];
                break;
            }
            else Phi[k]=Phi[i]*Phi[prime[j]];
        }
    }
    // for(int i=1;i<=10;i++) printf("i:%d Phi:%d\n",i,Phi[i]);
}

struct DS{
    node p[N<<2];
    inline void Pushup(int k){
        p[k].val=p[k*2].val+p[k*2+1].val;
        p[k].len=p[k*2].len+p[k*2+1].len;
        p[k].maxx=max(p[k*2].maxx,p[k*2+1].maxx);
        p[k].minn=min(p[k*2].minn,p[k*2+1].minn);
    }
    inline void ClearNode(int k){
        p[k].val=p[k].lazy=p[k].minn=p[k].maxx=p[k].op=p[k].len=0;
    }
    inline void Build(int k,int l,int r){
        if(l==r){
            p[k].val=a[l];p[k].minn=p[k].maxx=a[l];p[k].len=1;
            return;
        }
        ClearNode(k);
        int mid=(l+r)>>1;
        Build(k*2,l,mid);Build(k*2+1,mid+1,r);
        Pushup(k);
    }
    inline void A(int k,ll x){
        p[k].val=x*(ll)p[k].len;p[k].lazy=x;p[k].maxx=p[k].minn=x;
        p[k].op=1;
    }
    inline void Pushdown(int k){
        A(k*2,p[k].lazy);A(k*2+1,p[k].lazy);
        p[k].lazy=0;p[k].op=0;
    }
    inline void ChangeInt(int k,int l,int r,int z,int y,int x){
        if(l==z&&r==y){
            A(k,x);return;
        }
        if(p[k].op) Pushdown(k);
        int mid=(l+r)>>1;
        if(y<=mid) ChangeInt(k*2,l,mid,z,y,x);
        else if(z>mid) ChangeInt(k*2+1,mid+1,r,z,y,x);
        else ChangeInt(k*2,l,mid,z,mid,x),ChangeInt(k*2+1,mid+1,r,mid+1,y,x);
        Pushup(k);
    }
    inline void ChangePhi(int k,int l,int r,int z,int y){
        if(p[k].maxx==p[k].minn&&l==z&&r==y){
            int phi=Phi[p[k].minn];
            A(k,phi);return;
        }
        if(p[k].op) Pushdown(k);
        int mid=(l+r)>>1;
        if(y<=mid) ChangePhi(k*2,l,mid,z,y);
        else if(z>mid) ChangePhi(k*2+1,mid+1,r,z,y);
        else ChangePhi(k*2,l,mid,z,mid),ChangePhi(k*2+1,mid+1,r,mid+1,y);
        Pushup(k);
    }
    inline ll AskSum(int k,int l,int r,int z,int y){
        if(l==z&&r==y) return p[k].val;
        if(p[k].op) Pushdown(k);
        int mid=(l+r)>>1;
        if(y<=mid) return AskSum(k*2,l,mid,z,y);
        else if(z>mid) return AskSum(k*2+1,mid+1,r,z,y);
        else return AskSum(k*2,l,mid,z,mid)+AskSum(k*2+1,mid+1,r,mid+1,y);
    }
};
DS ds;

int t;

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    GetPhi();
    while(t--){
        read(n);read(m);
        for(int i=1;i<=n;i++) read(a[i]);
        ds.Build(1,1,n);
        for(int i=1;i<=m;i++){
            int op,l,r;
            read(op);read(l);read(r);
            if(op==1){
                ds.ChangePhi(1,1,n,l,r);
            }
            else if(op==2){
                int x;read(x);
                ds.ChangeInt(1,1,n,l,r,x);
            }
            else{
                ll ans=ds.AskSum(1,1,n,l,r);
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
```

---

## 作者：xcyle (赞：2)

显然直径的两端是叶子，括号序列上的叶子是$()$

经过观察，不难得出计算两个叶子间路径的方法。


$((($**()**$)))($**()**$)$ 对于那两个加粗的括号来说，它们在对应树上的距离就是二者之间的这些左右括号的数量

那么对于一般的情况呢？显然我们只需要找到一个合适的位置，计算它左右两边的不匹配括号数量之和即可

具体来说：设需要计算距离的两个节点分别在 $l,r$，那个合适的位置在 $k$ ，则 $d = sum_l + sum_r - 2 \times sum_k$，这里 $sum$ 代表左括号为1，右括号为-1的前缀和

这样一来，显然这个合适的位置 $k$ 一定使得 $sum_k=\min\limits_{l < i < r}sum_i$

问题转化为：给定一个序列，每次区间修改，并求出：

$\min\limits_{l < k < r}sum_l + sum_r - 2 \times sum_k$

用线段树维护即可

```cpp
#include <iostream>
#include <cstdio>
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define maxn 200005
#define N 800005
using namespace std;
const int INF = 0x3f3f3f3f;
int n, q, a[maxn], sum[maxn], p1, p2;
char s[maxn];
int t[N][5], tag[N]; 
void pushdown(int x)
{
	tag[lc(x)] += tag[x];
	t[lc(x)][0] += tag[x];
	t[lc(x)][1] += tag[x];
	t[lc(x)][2] -= tag[x];
	t[lc(x)][3] -= tag[x];
	tag[rc(x)] += tag[x];
	t[rc(x)][0] += tag[x];
	t[rc(x)][1] += tag[x];
	t[rc(x)][2] -= tag[x];
	t[rc(x)][3] -= tag[x];
	tag[x] = 0;
}
void pushup(int x)
{
	t[x][0] = max(t[lc(x)][0], t[rc(x)][0]);
	t[x][1] = min(t[lc(x)][1], t[rc(x)][1]);
	t[x][2] = max(max(t[lc(x)][2], t[rc(x)][2]), t[lc(x)][0] - 2 * t[rc(x)][1]);
	t[x][3] = max(max(t[lc(x)][3], t[rc(x)][3]), t[rc(x)][0] - 2 * t[lc(x)][1]);
	t[x][4] = max(max(t[lc(x)][4], t[rc(x)][4]), max(t[lc(x)][0] + t[rc(x)][3], t[lc(x)][2] + t[rc(x)][0]));
}
void build(int x, int l, int r)
{
	if(l == r)
	{
		t[x][0] = t[x][1] = sum[l];
		t[x][2] = t[x][3] = t[x][4] = -INF;
		return;
	}
	int mid = (l + r) >> 1;
	build(lc(x), l, mid);
	build(rc(x), mid + 1, r);
	pushup(x);
}
void add(int x, int l, int r, int a, int b, int data)
{
	if(a <= l && r <= b)
	{
		tag[x] += data;
		t[x][0] += data;
		t[x][1] += data;
		t[x][2] -= data;
		t[x][3] -= data;
		return;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(a <= mid) add(lc(x), l, mid, a, b, data);
	if(b > mid) add(rc(x), mid + 1, r, a, b, data);
	pushup(x);
}
int main()
{
	scanf("%d%d%s", &n, &q, s + 1);
	n = 2 * (n - 1);
	for (int i = 1; i <= n; i++) 
	{
		a[i] = (s[i] == '(' ? 0 : 1); 
		sum[i] = sum[i - 1] - a[i] * 2 + 1;
	}
	build(1, 1, n);
	printf("%d\n", max(t[1][0], t[1][4]));
	for (int i = 1; i <= q; i++)
	{
		scanf("%d%d", &p1, &p2);
		if(p1 > p2) swap(p1, p2);
		if(a[p1] != a[p2]) add(1, 1, n, p1, p2 - 1, a[p1] * 4 - 2);
		swap(a[p1], a[p2]);
		printf("%d\n", max(t[1][0], t[1][4]));
	}
	return 0;
}
```

---

## 作者：λᴉʍ (赞：2)

有一个合法的括号序列，每次交换两个括号（保证还是合法）求这个括号序列对应的树的直径

Orz zsy碾标算

直径相当于选一段，匹配完括号以后剩下最多的括号数

然后（因为zsy太强了）等于这一段分成两段后面的权值和-前面的权值和最大值，其中左括号权值为1，右括号为-1，证明显然

所以在线段树上维护一堆东西。。。就行了

要维护的：最大/最小前/后缀和，最大前/后缀的$d$值，序列整体$d$值，权值和，答案

一段的$d$值就是将这一段分成两段后-前权值最大值

https://www.cnblogs.com/xzz_233/p/10798276.html

---

## 作者：orz_z (赞：1)

### CF1149C Tree Generator™

不能暴力建树，考虑从括号序入手。

联想树上莫队的点括号序列，一段区间去掉匹配括号剩下的括号对应的点即为路径上的点，有特殊情况。

则这里边括号序列，发现特殊情况都给你省掉了，那么一条路径对应一个区间去掉匹配括号。

那么有，**树上直径长度为任意区间去掉匹配括号后的长度的最大值。**

考虑如何代数去除匹配括号，树上莫队是判奇偶，这里可以设左端点为 $1$，右端点为 $-1$。

问题变为找到相邻的两段，使后一段的数字和减前一段的数字和的差最大，这个差就是答案。 

因为后一段的数字和，对应一条向下的链，前一段的数字和对应一条向上的链，减去是因为向上的链的非匹配括号数计算是反过来的，即 $1、-1$ 交换。

区间最大差，考虑维护区间前后缀最大差以及整个区间的最大差。

需要维护区间前后缀最大最小子段和辅助计算。

一棵线段树即可，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int o = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		o = o * 10 + c - '0', c = getchar();
	return o * f;
}

inline void write(int o)
{
	if(o < 0)
	{
		putchar('-');
		o = -o;
	}
	if(o > 9)
		write(o / 10);
	putchar(o % 10 + '0');
}

const int _ = 2e5 + 10;

int n, q;

int tr[_ << 2], su[_ << 2], lm[_ << 2], rm[_ << 2], ln[_ << 2], rn[_ << 2], ld[_ << 2], rd[_ << 2], zd[_ << 2];

// m 大 n 小 d 右减左

char s[_];

void pushup(int o)
{
	su[o] = su[o << 1] + su[o << 1 | 1];
	lm[o] = max(lm[o << 1], su[o << 1] + lm[o << 1 | 1]);
	rm[o] = max(rm[o << 1 | 1], su[o << 1 | 1] + rm[o << 1]);
	ln[o] = min(ln[o << 1], su[o << 1] + ln[o << 1 | 1]);
	rn[o] = min(rn[o << 1 | 1], su[o << 1 | 1] + rn[o << 1]);
	
	ld[o] = max(ld[o << 1], max(ld[o << 1 | 1] - su[o << 1], zd[o << 1] + lm[o << 1 | 1]));
	rd[o] = max(rd[o << 1 | 1], max(su[o << 1 | 1] + rd[o << 1], zd[o << 1 | 1] - rn[o << 1]));
	
	zd[o] = max(zd[o << 1] + su[o << 1 | 1], zd[o << 1 | 1] - su[o << 1]);
	tr[o] = max(max(ld[o << 1 | 1] - rn[o << 1], rd[o << 1] + lm[o << 1 | 1]), max(tr[o << 1], tr[o << 1 | 1]));
}

void build(int o, int l, int r)
{
	if(l == r)
	{
		int v = s[l] == '(' ? 1 : -1;
		su[o] = v;
		lm[o] = rm[o] = max(v, 0);
		ln[o] = rn[o] = min(v, 0);
		ld[o] = rd[o] = zd[o] = tr[o] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

void upd(int o, int l, int r, int p, int v)
{
	if(l == r)
	{
		su[o] = v;
		lm[o] = rm[o] = max(v, 0);
		ln[o] = rn[o] = min(v, 0);
		ld[o] = rd[o] = zd[o] = tr[o] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) upd(o << 1, l, mid, p, v);
	else upd(o << 1 | 1, mid + 1, r, p, v);
	pushup(o);
}

signed main()
{
	n = read(), q = read();
	scanf("%s", s + 1);
	n = (n - 1) << 1;
	build(1, 1, n);
	write(tr[1]), he;
	int a, b;
	while(q--)
	{
		a = read(), b = read();
		if(s[a] != s[b])
		{
			swap(s[a], s[b]);
			upd(1, 1, n, a, s[a] == '(' ? 1 : -1);
			upd(1, 1, n, b, s[b] == '(' ? 1 : -1);
		}
		write(tr[1]), he;
	}
	return 0;
}
```



---

## 作者：Albert_van (赞：0)

首先把边上的括号序转换成不完整的点上括号序：把每条边上的括号下放到它所指向的儿子处，题设序列就变成了“从根节点开始遍历整棵树，除根结点外，每开始访问和结束访问某个结点的子树时分别将一个 `(` 和一个 `)` 添加至序列末尾”所最终形成的括号序。借鉴树上莫队的方式方法可知这个括号序的子串们 去掉匹配括号后的长度（以下简称“去匹长”）可以**满射**到树上任意一条路径的长度，且它们相等（实际上是子串去掉匹配括号后可以直接满射到路径上，感性理解）：

$$\forall u\in[1,n]\land v\in[1,n]\land u\le v,\exists i\in[1,2n-2]\land j\in [1,2n-2]\land i\le j,f((i,j))=(u,v)$$

其中 $f$ 是一种奇怪的映射，具体可以访问[这篇blog](https://www.cnblogs.com/vanspace/p/Mos-algo-Naive.html)中的【树上莫队】篇内容。

于是树的直径变成了【子串们去匹长的最大值】。这东西很难看，考虑具象化，赋予每个 `(` $1$ 的权值以及每个 `)` $-1$ 的权值，一个串的去匹长转化为把这个串分成两段（均可以为空）后 后面一段的权值和减去前面一段的权值和 的最大值：

$$\operatorname{lenextractmatch}(t)=\max_{i=0}^{|t|} \left(\sum_{j=i+1}^{|t|} val(t_j)\right)-\left(\sum_{j=1}^i val(t_j)\right)$$

这个仍然可以感性理解，分出来的后面那段要放尽量多的 `(` 也就是权值尽量大，前面那段要放尽量多的 `)` 也就是权值尽量小，加减的过程中匹配的 `(` 和 `)` 会被自动消掉。

外面再套上一层 $\max$，求出一个串 $S$ 的任意一个子串 $t$ 去匹长的最大值：

$$\operatorname{maxsubstrlenextractmatch}(S)=\max_{t\in substr(S)} \max_{i=0}^{|t|} \left(\sum_{j=i+1}^{|t|} val(t_j)\right)-\left(\sum_{j=1}^i val(t_j)\right)$$

$$=\max_{i=0}^{|S|} \left(\sum_{j=i+1}^{|S|} val(S_j)\right)-\left(\sum_{j=1}^i val(S_j)\right)$$

做到这一步题目中 `swap` 已经没有任何性质了，线段树维护然后模拟之即可。

重头戏来了。每个结点需要维护 $7$ 个值（设其维护的区间为 $[l,r]$）：

- `ans`，该结点答案，即 $[l,r]$ 这个子串的所有子串们去匹长的最大值；
- `whans`，用上 $[l,r]$ 这个子串的所有位置组成串的去匹长，也就是 $[l,r]$ 这个子串的去匹长；
- `lans`，包含 $l$ 这个位置的 $[l,r]$ 的子串的去匹长的最大值，即前缀最大去匹长；
- `rans`，包含 $r$ 这个位置的 $[l,r]$ 的子串的去匹长的最大值，即后缀最大去匹长；
- `sum`，$[l,r]$ 的权值和；
- `lmx`，$[l,r]$ 中包含 $l$ 这个位置的 $[l,r]$ 的子串的权值和最大值，即前缀最大权值和；
- `rmx`，$[l,r]$ 中包含 $r$ 这个位置的 $[l,r]$ 的子串的权值和最大值，即后缀最大权值和。

剩下的就是如何 `pushup` 了，十分的简单，简单到笔者在赛时AC本题的 dalao 的帮助下调了6h：

```cpp
void updata(int x){
    ans(x)=max(max(ans(ls(x)),ans(rs(x))),
               max(lans(rs(x))-min(rmn(ls(x)),0),rans(ls(x))+max(lmx(rs(x)),0)));
    whans(x)=max(whans(ls(x))+sum(rs(x)),whans(rs(x))-sum(ls(x)));
    lans(x)=max(lans(ls(x)),max(whans(ls(x))+max(lmx(rs(x)),0),lans(rs(x))-sum(ls(x))));
    rans(x)=max(rans(rs(x)),max(whans(rs(x))-min(rmn(ls(x)),0),rans(ls(x))+sum(rs(x))));
    sum(x)=sum(ls(x))+sum(rs(x));
    lmx(x)=max(lmx(ls(x)),sum(ls(x))+lmx(rs(x)));
    rmn(x)=min(rmn(rs(x)),sum(rs(x))+rmn(ls(x)));
}
```

---

