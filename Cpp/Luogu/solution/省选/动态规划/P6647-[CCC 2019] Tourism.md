# [CCC 2019] Tourism

## 题目背景

**警告：滥用本题评测将被封号！**


Shuchong 和您正在畅玩洛谷著名景点。  
但是他因为太菜爽约了。   
您只好独自去游览洛谷著名景点。

## 题目描述

您正在游览 $n$ 个景点，编号为 $1$ 到 $n$，并且因为 3k 的强硬要求，您必须按照 $1$ 到 $n$ 的顺序浏览。您一天最多可以游览 $k$ 个景点，因为剩下的时间您要用来爆切黑题，所以您想尽快浏览完这些景点。   
每个景点对您的吸引度不同，第 $i$ 个景点对您的吸引度为 $a_i$，一天游览的这些景点的官方评分就是这天游览的景点的 $a_i$ 的最大值。最后，您需要把每天的官方评分加起来获得最后的评分。   
因为您太着急想爆切黑题了，所以您提前计算好了浏览完所有景点最少需要多少天（假设它为 $t$），您想知道：

- 用 $t$ 天浏览
- 满足每天最多游览 $k$ 个景点
- 能得到的最后的评分最大是多少

## 说明/提示

#### 样例说明

对于样例 $1$：

- 我们很容易就知道至少需要 $2$ 天就可以浏览完所有景点。  
- 但是我们不能一天内浏览完所有景点。（$n>k$）   
- 我们把景点尽量平分，有以下两种情况：
	- 如果第一天浏览 $2$ 个，第二天浏览 $3$ 个，最终的评分为 $5+7=12$。
    - 如果第二天浏览 $3$ 个，第二天浏览 $2$ 个，最终的评分为  $7+4=11$。
- 最后的答案为 $\max(12,11)=12$。

#### 数据规定与说明

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$2k \ge n$。
- Subtask 2（20 pts）：$k \le 100$，$n \le 10^5$。
- Subtask 3（60 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k \le n \le 10^6$，$1 \le a_i \le 10^9$。

#### 说明

**翻译自 [CCC 2019](https://cemc.math.uwaterloo.ca/contests/computing/2019/index.html) Senior T4 [Tourism](https://cemc.math.uwaterloo.ca/contests/computing/2019/stage%201/seniorEF.pdf)。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

## 样例 #1

### 输入

```
5 3
2 5 7 1 4
```

### 输出

```
12```

# 题解

## 作者：chen_qian (赞：23)

以下做法来自大佬[Daniel13265](https://www.luogu.com.cn/user/55251)，复杂度为线性。

考虑暴力的 $\text{dp}$。定义 $f_{i,j}$ 表示前 $i$ 个分成 $j$ 段的答案。方程如下。复杂度 $O(n^2)$

$$f_{i,j}=\max\limits_{l=i-k}^{i-1}(f_{l,j-1}+\max\limits_{r=l+1}^{i}(a_r)) $$

考虑如何优化这个 $\text{dp}$，显然枚举过程已经是最优，只能从状态上简化。可以发现这样一个事实，我们之前枚举的大部分状态对于最终的答案都是没有贡献的。借此，我们发现对于 $i$，只有 $f_{i,\left \lceil \frac{i}{k} \right \rceil }$ 对之后的答案有贡献。证明如下

  - 若 $j<\left \lceil \frac{i}{k} \right \rceil$，那么必定有一段长度大于 $k$。
  
  - 若 $j>\left \lceil \frac{i}{k} \right \rceil$，由上分析可知后面最少也要 $\left \lceil \frac{n-i}{k} \right \rceil$ 段，所以有 $j+\left \lceil \frac{n-i}{k} \right \rceil >\left \lceil \frac{i}{k} \right \rceil + \left \lceil \frac{n-i}{k} \right \rceil \geqslant \left \lceil \frac{n}{k} \right \rceil$ 一定不满足。
 
所以记 $g_i=f_{i,\left \lceil \frac{i}{k} \right \rceil }$。根据如上的方程，能够向 $g_i$ 贡献的只有满足 $i-k\leqslant j \leqslant i-1$ 且 $\left \lceil \frac{i}{k} \right \rceil-1=\left \lceil \frac{j}{k} \right \rceil$ 的 $j$。所以方程为：

$$g_{i}=\max _{j=i-k}^{k \times\left\lfloor\frac{i-1}{k}\right\rfloor}\left(g_{j}+\max _{k=j+1}^{i} a_{k}\right)$$

做到这里，就可以用单调栈+线段树做到 $O(n\log n)$。已经可以解决这个问题，也是大部分题解所用到的。

接下来就是如何优化到线性。

根据上面的 $\text{dp}$ 我们发现，序列实际上是被分割成 $\left \lceil \frac{n}{k} \right \rceil$，每段为 $k$ 长度。每一段只能对下一段贡献答案。那么我们可以通过对于每一段进行预处理，同时修改同一块中的枚举顺序来加速回答问题。如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/tgp5tae2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

 $r$ 为块的分界点我们从块的右端点倒序枚举需要更新的 $i$。显然左端点 $j$ 也在更新。如果我们假设 $s(l,r)$ 是区间 $[l,r]$ 的最大值，对于处于 $[j,r]$ 之间 $k$ 其产生的贡献是 $\max(g_k+s(k+1,r),g_k+s(r,i))$，对于后面的一部分 $s(r,i)$ 只与 $i$ 有关，只需要维护前一个块中的后缀最大值即可，对于前面一部分只与 $k$ 有关，同样可以在移动 $i$ 的过程中维护。做到 $O(1)$ 转移。复杂度为 $O(n)$。
 
 ```cpp
#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
int n,m,a[N];
ll f[N],maxn[N];
int x[N];
int pos[N],L[N],R[N],numb;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	numb=n/m;
	for(int i=1;i<=numb;i++){
		L[i]=R[i-1]+1;
		R[i]=i*m;
	}
	if(R[numb]<=n) numb++,L[numb]=R[numb-1]+1,R[numb]=n;
	for(int i=1;i<=numb;i++){
		for(int j=L[i];j<=R[i];j++){
			if(j==L[i]) x[j]=a[j];
			else x[j]=max(x[j-1],a[j]);
		}	
	}
	for(int i=L[1];i<=R[1];i++) f[i]=x[i];
	for(int i=R[1];i>=L[1];i--) maxn[i]=max(maxn[i+1],f[i]);
	for(int k=2;k<=numb;k++){
		ll mx=0;
		int j=R[k-1],mx2=0;
		while(j>R[k]-m){
			mx=max(mx,f[j]+mx2);
			mx2=max(mx2,a[j]);
			j--;
		}
		for(int i=R[k];i>=L[k];i--){
			mx=max(mx,f[j]+mx2);
			f[i]=max(mx,maxn[j]+x[i]);
			mx2=max(mx2,a[j]);
			maxn[i]=max(maxn[i+1],f[i]);
			j--;
		}
		
	}
	cout<<f[n]<<endl;
	return 0;
}
```


---

## 作者：xuanxuan001 (赞：22)

一年多没写题解了，该写写了（~~其实是写过一次的但没过审~~）

Upd
-
- 2020/7/28 改正了代码上的一个错误和例子答案的错，感谢@Suzt_ilymtics的提醒。我为了增强代码可读性改了一下代码，但是改完后没测，就出问题了，我那时候可能脑抽了。

正文
-

这题 DP。但 $10^6$ 的数据范围显然是要求我们只用一维的空间解决，所以 DP 的方法已经显然了，那就是 $dp_i$ 表示刚好游览前 $i$ 个景点能得到的最大评分。

但这个状态本来应该是受到现在用的天数的影响的，我们应该把这个状态加进去，但是不行，怎么解决呢？

由于题面要求用尽量少的天数来游览 $n$ 个景点，所以说对于任意的 $1 \le i \le n$，游览完前 $i$ 个景点用的天数也应该是尽量少的。

为什么呢，因为如果你前 $i$ 个景点不用最少的天数的话，这就意味着你前 $i$ 天至少还能多去 $k$ 个景点，这就导致你游览完 $n$ 个景点的天数不可能是尽量少的，因为你前 $i$ 个景点用的若干天中可以分担之后一天的工作量，从而少一天时间。

**所以，现在的 DP 就转换为: $dp_i$ 表示用尽量少的天数去游览完正好前 $i$ 个景点能得到的最大评分。**

_上面写了那么多，我也不知道写没写清楚，但是一定要先把上面的看懂啊，上面的毕竟只是个开头。_

由于样例不适合表现我的算法，所以我的图例中用的是下面这组数据：

```
8 3
7 5 4 1 3 2 1 3
```

答案是14。

下面考虑转移方程。如下图，我们把 $n$ 个景点按顺序分成 $\lceil \dfrac{n}{k} \rceil$ 个部分，前面 $\lceil \dfrac{n}{k} \rceil - 1$ 个区间都是 $k$ 个景点。

然后我们把每天游览完后游览的景点标出来（换句话说，就是每天的游览的分割线，但我用左边的那个景点来存储(为什么看完就知道了)）

![](https://cdn.luogu.com.cn/upload/image_hosting/vkcnsh9x.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

这时我们发现每个部分中都有且仅有一个景点被标记。下面是证明（
可以先自己想一下）：

1. 一个区域中不可能没有景点被标记。因为如果这样的话这个区间所在的这一天游览的景点数就超过 $k$ 了。
1. 一个区域中不可能有超过一个景点被标记。因为如果这样天数就不是尽量少的了。

发现了这个命题，我们就会发现，对于一个下标 $i$，能转移给它的点在它往前数 $k$ 个点与它前面的第一个分割线之间，而每个分割线的右边都是编号为 $k$ 的倍数的景点。所以说，DP 方程就是这样的：

$$
dp_i=\max\limits_{j=i-k}^{k \times \lfloor \dfrac{i}{k} \rfloor}(dp_j+\max\limits_{k=j+1}^ia_k)
$$

但是，这个方程的复杂度是 $O(nk)$ 的，显然不行，需要优化。

我们可以把上面的 $j+1$ 到 $i$ 的最大值拆成 $j+1$ 到 $k \times \lfloor \dfrac{i}{k} \rfloor$ 和 $k \times \lfloor \dfrac{i}{k} \rfloor+1$ 到 $i$ 两段。

对于第一段，我们可以记 $lm_j$ 为 $j+1$ 到 $k \times \lfloor \dfrac{i}{k} \rfloor$ 的最大值，因为这部分的右端点是固定的，所以可以 $O(k)$ 预处理出来，然后就可以设一个数组 $num$ 来存放 $dp_j+lm_j$，这就是每个转移给每个要求的 $dp_i$ 的值。
下面是第二段，我们可以用一个循环边处理边把 $dp_i$ 处理好，对于每个 $i$，在过程中动态处理 $num$。下面就是如何维护。

如下图，我们以最后一部分为例，这是处理前的。

![](https://cdn.luogu.com.cn/upload/image_hosting/taga9csr.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

处理第七个景点，它是 1，这需要更新 $num$ 数组，这时会受到影响的就是第六个，即 $lm$ 数组低于 1 的，将它加上 1 与原本的 $lm$ 数组的差，即 1。并且需要记一个变量 $\textit{aff}$ 指向 6。此时的答案是 $num$ 数组的最大值 15。 

![](https://cdn.luogu.com.cn/upload/image_hosting/9v3gsz05.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

下面是第八个景点。这时 $\textit{aff}$ 所指向的景点以及它右边的所有景点都一定会受到它的影响。所以将 $\textit{aff}$ 到分割线的所有 $num$ 都加上这个景点与 $lm_{\textit{aff}}$ 的差，即 2。然后重复处理第七个景点的事，$\textit{aff}$变成 5。这时注意取的不是整个 $num$ 数组的最大值，应该去掉第四个，因为如果取第四个的话这天游览的景点就超过 $k$ 个了。所以答案是 14。

![](https://cdn.luogu.com.cn/upload/image_hosting/idyfhk0n.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

这时，$num$ 数组需要维护的是区间加和区间最大值，这需要用线段树。最后复杂度$O(n \times \log k)$

最后要注意的就是开 long long

代码：

```cpp
#include<cstdio>
#define MAXN 2000002
using namespace std;
int maxn(int a,int b){return a>b?a:b;}
int n,k,a[MAXN],lm[MAXN],aff,tag[MAXN<<1],nowmax,tmp;
long long dp[MAXN],tree[MAXN<<1];
void upd(int id){tree[id]=tree[tree[id<<1]>tree[id<<1|1]?id<<1:id<<1|1];}
void build(int l,int r,int id){//这些线段树部分没什么好说的，就是我的区间下标不是从1开始的，可能不太好懂 
    tag[id]=0;if(l==r){tree[id]=lm[l]+dp[l];return;}
    int mid=(l+r)>>1;build(l,mid,id<<1);
    build(mid+1,r,id<<1|1);upd(id);
}void pushdown(int id){
    int ls=id<<1,rs=id<<1|1;
    tag[ls]+=tag[id];tree[ls]+=tag[id];
    tag[rs]+=tag[id];tree[rs]+=tag[id];
    tag[id]=0;
}void add(int l,int r,int i,int j,int id,int k){
    if(l<=i&&j<=r){tree[id]+=k;tag[id]+=k;return;}
    pushdown(id);int mid=(i+j)>>1;
    if(l<=mid)add(l,r,i,mid,id<<1,k);
    if(r>mid)add(l,r,mid+1,j,id<<1|1,k);
    upd(id);
}long long ask(int l,int r,int i,int j,int id){
    if(l<=i&&j<=r){return tree[id];}
    pushdown(id);int mid=(i+j)>>1;
    long long ans=0,now;
    if(l<=mid){
        now=ask(l,r,i,mid,id<<1);
        if(now>ans)ans=now;
    }if(r>mid){
        now=ask(l,r,mid+1,j,id<<1|1);
        if(now>ans)ans=now;
    }return ans;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",a+i);dp[0]=0;
    for(int i=1;i<=k;i++)dp[i]=maxn(dp[i-1],a[i]);//第一个部分直接解决 
    for(int i=1;i*k<n;i++){//一个个地处理每个景区部分 
        lm[i*k]=0;
        for(int j=i*k-1;j>(i-1)*k;j--)lm[j]=maxn(lm[j+1],a[j+1]);
        build((i-1)*k+1,i*k,1);aff=i*k;nowmax=0;
        for(int j=i*k+1;j<=(i+1)*k;j++){
            if(a[j]>nowmax){//如果这个数前面有更大的就不需要更新了 
                add(aff,i*k,(i-1)*k+1,i*k,1,a[j]-nowmax);
                nowmax=a[j];
                while(aff>(i-1)*k+1&&a[j]>lm[aff-1]){//aff指针 
                    aff--;add(aff,aff,(i-1)*k+1,i*k,1,a[j]-lm[aff]);
                }
            }dp[j]=ask(j-k,i*k,(i-1)*k+1,i*k,1);
        }
    }printf("%lld",dp[n]);
    return 0;
}
```
后记
-
我的代码竟然跑得挺快，才130ms。

---

## 作者：dead_X (赞：9)

## 前言
疑惑，这为啥是紫题？
## 思路
首先记取 $i$ 个的最少次数为 $f(i)$，那么 $i$ 一定会从 $f(j)=f(i)-1$ 的地方转移过来，因此我们可以直接算出转移的区间。

然后一个很自然的想法就是记录一下前 $j$ 个点的最大值和 $(j+1)\sim i$ 号点的最大值。

前者我们 dp 的时候就可以得出，而后者可以使用一个单调栈简单实现。

最后直接用一个线段树维护区间最大值即可。
## 代码
```cpp
// Problem: P6647 [CCC 2019] Tourism
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6647
// Memory Limit: 128 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int tag[4000003],ans[4000003];
void push_down(int x)
{
	tag[x<<1]+=tag[x],tag[(x<<1)+1]+=tag[x];
	ans[x<<1]+=tag[x],ans[(x<<1)+1]+=tag[x];
	tag[x]=0;
	return ;
}
void update(int l,int r,int L,int R,int id,int val)
{
	if(L<=l && r<=R) 
	{
		tag[id]+=val;
		ans[id]+=val;
		return ;
	}
	int mid=(l+r)>>1;
	push_down(id);
	if(L<=mid) update(l,mid,L,R,id<<1,val);
	if(R>=mid+1) update(mid+1,r,L,R,(id<<1)+1,val);
	ans[id]=max(ans[(id<<1)],ans[(id<<1)+1]);
	return ;
}
long long query(int l,int r,int L,int R,int id)
{
	if(L<=l && r<=R) return ans[id];
	int mid=(l+r)>>1;
	push_down(id);
	long long res=0;
	if(L<=mid) res=max(res,query(l,mid,L,R,id<<1));
	if(R>=mid+1) res=max(res,query(mid+1,r,L,R,(id<<1)+1));
	return res;
}
int a[1000003],f[1000003];
int n=read(),k=read();
stack<int> s;
void calc(int x)
{
	update(0,n,x-1,x-1,1,a[x]);
	int lst=x-2,val;
	while(a[s.top()]<a[x]) 
		val=a[s.top()],s.pop(),update(0,n,s.top(),lst,1,a[x]-val),lst=s.top()-1;
	s.push(x);
	return ;
}
signed main()
{
	s.push(0),a[0]=1e15;
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i)
	{
		calc(i);
		int L=max(i-k,0ll),R=(i-1)/k*k;
		// printf("%lld %lld ",L,R);
		assert(L<=R);
		f[i]=query(0,n,L,R,1);
		update(0,n,i,i,1,f[i]);
		// printf("%lld\n",f[i]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：SSerxhs (赞：8)

先不考虑 $t$ 的限制，设 $f_i$ 表示刚看完第 $i$ 个景点的答案，记 $g(l,r)=\max\limits_{l\le i \le r}a_i$，那么 dp 方程显然为 $f_i=\max\limits_{i-m\le j<i}\{f_j+g(j+1,i)\}$。

考虑到有 $t$ 的限制，要求最小化天数，即最小化转移次数，那么把方程改写为 $f_i=\max\limits_{i-m\le j<i}\{f_j+g(j+1,i)\}-\inf$ 就可以了。

接下来处理这个麻烦的 $g(j+1,i)$。先不管 $m$ 的限制，考虑维护一个单调递减栈。

举个例子，对于某 $a$ 序列 $7,4,5,6$，当 $i=3$ 时，单调栈内**序列下标**为 $1,3$。可以注意到，单调栈内的**序列下标**恰好把序列划分成了若干个区间，对于指定区间内的 $j$，$g(j+1,i)$ 的值是相等的。具体地，设单调栈内的**序列下标**序列为 $\{s\}$，那么 $\forall j\in[s_k,s_{k+1}),g(j+1,k)=a_{s_{k+1}}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0bgtvcbu.png)

如上图，三个黑色矩形的长表示对应的下标区间，宽表示对应的 $g$ 值。那么我们可以考虑对每个 $j$ 动态维护 $f_j+g(j+1,i)$，需要维护的操作是加一个新元素。

当单调栈需要弹栈时（如红色矩形进入）时，相当于是把黑色矩形补齐成和红色矩形同宽，即增加了一个绿色矩形，对应 $f_j+g(j+1,i)$ 的区间加，用线段树维护即可。那么我们就实现了动态维护。

接下来再考虑 $m$ 的限制，那么只需要做区间求最大值就可以了。总复杂度 $O(n\log n)$。

```cpp
int main()
{
	read(n,m,a,n);l[1]=0;r[1]=n;build(1);
	for (i=1;i<=n;i++)
	{
		while (tp&&a[st[tp]]<=a[i])
		{
			if (a[st[tp]]==a[i]) {--tp;continue;}
			z=st[tp-1];y=st[tp]-1;dt=a[i]-a[st[tp]];
			mdf(1);--tp;
		}
		st[++tp]=i;
		z=y=i-1;dt=f[i-1]+a[i];mdf(1);
		dt=-9e18;z=max(i-m,0);y=i-1;ask(1);
		f[i]=dt+inf;
	}
	enter(f[n]-(ll)(n-1+m)/m*inf);
}
```

---

## 作者：tommymio (赞：6)

对于这种多个约束条件的题目，一个一个条件来考虑。

- 游览天数 $t$ 最小，每天最多浏览 $k$ 个景点。

  显然贪心的取是最好的，那么天数 $t$ 就是 $\left\lceil\frac{n}{k}\right\rceil$。

- 求最大评分。

  如果只是求每天浏览 $k$ 个景点下的最大评分的话，直接 $\text{DP}$ 就好了。

但是加上了游览天数 $t$ 最小的限制该怎么做呢？

想到如果给每一天加上一个 $-\infty$ 的权值，那么最大值一定在总天数最小的时候取到。计算答案的时候再加上对应个数的 $\infty$ 权值就好了。

设 $f_i$ 为游览 $i$ 个景点的最大评分。
$$
f_i=\max_{i-k\leq j\leq i-1} \{f_j+\max(a_{j+1},\cdots,a_i)\}-\infty
$$

转移是 $O(n)$ 的，当然不能接受。

注意到转移中 $\max(a_{j+1},...,a_i)$ 对于每个 $i$ 其右边界向右平移 $1$ 个长度。将 $\max(a_{j+1},..,a_i)$ 记作 $\mathrm{calc}(j,i)$。对于新增的 $a_{i+1}$，考虑 $\max(\mathrm{calc}(j,i),a_{i+1})$ 的值。

发现一定存在 $L$，对于以 $i$ 为右端点的一段区间 $[L,i]$ 中，$j\in[L,i]$，其 $\max(\mathrm{calc}(j,i),a_{i+1})=a_{i+1}$。

所以用单调栈维护从右到左的一个递增序列就好了。每次取出一段会被 $a_{i+1}$ 更新最大值的区间进行区间修改，转移时查询区间最大值。

时间复杂度为 $O(n\log n)$。

**你的 $\infty$ 需要足够大**。

```cpp
#include<cstdio>
#include<cmath> 
#include<cstring>
typedef long long ll;
const ll inf=1e12;
struct SegmentTree {
	#define ls p<<1
	#define rs p<<1|1
	int n;
	ll sgt[4000010],add[4000010];
	inline ll max(const ll &x,const ll &y) {return x>y? x:y;}
	inline void init(int n) {this->n=n;}
	inline void spread(int p) {
		if(add[p]) {
			add[ls]+=add[p]; add[rs]+=add[p];
			sgt[ls]+=add[p]; sgt[rs]+=add[p];
			add[p]=0;
		}
	}
	inline void API_modify_add(int p,int l,int r,int L,int R,ll d) {
		if(L<=l&&r<=R) {add[p]+=d; sgt[p]+=d; return;}
		int mid=l+r>>1; spread(p);
		if(L<=mid) API_modify_add(ls,l,mid,L,R,d);
		if(R>mid) API_modify_add(rs,mid+1,r,L,R,d);
		sgt[p]=max(sgt[ls],sgt[rs]); 
	}
	inline void API_modify_mono(int p,int l,int r,int x,ll d) {
		if(l==r) {sgt[p]=d; return;}
		int mid=l+r>>1; spread(p);
		if(x<=mid) API_modify_mono(ls,l,mid,x,d);
		else API_modify_mono(rs,mid+1,r,x,d);
		sgt[p]=max(sgt[ls],sgt[rs]);
	}	
	inline ll API_ask(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return sgt[p];
		int mid=l+r>>1; spread(p);
		if(R<=mid) return API_ask(ls,l,mid,L,R);
		if(L>mid) return API_ask(rs,mid+1,r,L,R);
		return max(API_ask(ls,l,mid,L,mid),API_ask(rs,mid+1,r,mid+1,R)); 
	}
	inline void modify_add(int l,int r,ll d) {API_modify_add(1,0,n,l,r,d);}
	inline void modify_mono(int x,ll d) {API_modify_mono(1,0,n,x,d);}
	inline ll ask(int l,int r) {return API_ask(1,0,n,l,r);}
	#undef ls
	#undef rs
}SGT;
int st[1000005],a[1000005];
ll f[1000005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline ll max(const ll &x,const ll &y) {return x>y? x:y;}
int main() {
	int n=read(),K=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	SGT.init(n); int top=0; 
	for(register int i=1;i<=n;++i) {
		while(top&&a[st[top]]<=a[i]) {
			SGT.modify_add(st[top-1],st[top]-1,a[i]-a[st[top]]);
			--top;
		}
		st[++top]=i;
		SGT.modify_mono(i-1,f[i-1]+a[i]);
		f[i]=SGT.ask(max(0,i-K),i-1)-inf;
	}
	printf("%lld\n",f[n]+((n-1)/K+1)*1ll*inf);
	return 0;
}
```

  

  

  

   

  

---

## 作者：尹昱钦 (赞：6)

## 解题思路
**首先 $t$ 可以直接算出来**：$t=\left \lceil \dfrac{n}{k} \right \rceil$

我们从最朴素的 dp 开始想。

**设 $dp(i,j)$ 表示前 $i$ 天，浏览了 $j$ 个景点的最大评分。**

那么转移方程为：

$$dp(i,j)=\max_{x=j-k}^{j-1}(dp(i-1,x)+\max(a_{x+1},a_{x+2},\cdots,a_j))$$

我们发现因为**要保证用最少的天数浏览**，所以可以把原转移方程改为：

$$dp(i,j)=\max_{x=j-k}^{j-1}(dp(i-1,x)+\max(a_{x+1},a_{x+2},\cdots,a_j)-inf)$$

Q：有什么用呢？

A：**第一维可以直接省掉了，$dp(j)$ 的意义变为用最少的天数浏览前 $j$ 个景点的最大评分。**

转移方程变为：

$$dp(i)=\max_{j=i-k}^{i-1}(dp(j)+\max(a_{j+1},a_{j+2},\cdots,a_i)-inf)$$

但是这样还需要枚举 $x$，复杂度仍为 $O(nk)$，需要继续进行优化。因为已经优化完**状态设计**了，所以我们把下一步优化放在**优化转移**上。

令 $maxx(j,i)$ 表示 $a_j$ 到 $a_i$ 的最大值，则在 $i$ 固定的时候，$maxx(j,i)$ 的值是随着 $j$ 的增大而呈区间变小的，这样我们可以用线段树维护区间的最大值，维护的信息为 $dp[j]+maxx(j+1,i)$。

需要进行的操作即为单点更新 $dp[j]$，区间修改，和区间查询最大值 $(i-k)\to (i-1)$。

**线段树**维护一下即可。

总时间复杂度为 $O(nlogn)$。

**注意：**
- update 函数传的参数 $v$ 需要用 long long。
- ceil 函数默认返回值是 double，而 double 没有 long long 范围大，需要先强制转换为 long long 类型，不然会 wa 掉。

~~（调了一晚上交了二十多遍的我瑟瑟发抖）~~
## AC代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=1e6+5;
const long long inf=1e12;
long long dp[maxn],d[maxn*6],lazy[maxn*6],a[maxn],s[maxn],n,k,last;
inline void pushdown(int id){
	if(lazy[id]==0) return;
	lazy[id*2]+=lazy[id];
	lazy[id*2+1]+=lazy[id];
	d[id*2]+=lazy[id];
	d[id*2+1]+=lazy[id];
	lazy[id]=0;
}
inline void pushup(int id){
	d[id]=max(d[id*2],d[id*2+1]);
}
void update(int id,int l,int r,int x,int y,long long v){
	if(x<=l&&r<=y){
		lazy[id]+=v;
		d[id]+=v;
		return;
	}
	int mid=(l+r)/2;
	pushdown(id);
	if(x<=mid) update(id*2,l,mid,x,y,v);
	if(y>mid) update(id*2+1,mid+1,r,x,y,v);
	pushup(id);
}
long long query(int id,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return d[id];
	}
	int mid=(l+r)/2;
	pushdown(id);
	long long res=-9e18;
	if(x<=mid) res=max(res,query(id*2,l,mid,x,y));
	if(y>mid) res=max(res,query(id*2+1,mid+1,r,x,y));
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		while(last&&a[s[last]]<=a[i]){//单调栈更新
			update(1,0,n,s[last-1],s[last]-1,a[i]-a[s[last]]);//因为maxx(j,i)改变了，所以需要在线段树中进行更新
			last--;
		}
		s[++last]=i;
		update(1,0,n,i-1,i-1,dp[i-1]+a[i]);
		dp[i]=query(1,0,n,max((long long)0,i-k),i-1)-inf;//状态转移
	}
	cout<<(long long)(dp[n]+(long long)ceil((double)1.0*n/k)*inf);
    return 0;
}
```

---

## 作者：Light_snow (赞：5)

本文同步自[[CCC​2019] Tourism题解](https://www.cnblogs.com/dixiao/p/15019610.html)。

## [CCC​2019] Tourism题解

我们先考虑一下拿部分分：

### subtask1

考虑因为 $n < 2k$ ，那么我们的划分一定是从中间某个地方裁开，且满足 $k$ 的条件的，我们发现当划分点在 $[n\ mod\ k,k]$ 时满足条件，那么我们只需要维护一个前缀最大值和后缀最大值就好了。

```c++
	for(int i = 1;i <= n;++i)
	pre[i] = std::max(pre[i - 1],a[i]);
	for(int i = n;i >= 1;--i)
	s[i] = std::max(s[i + 1],a[i]);
	ll ans = 0;
	for(int i = n % k ;i <= k;++i)
	ans = std::max(ans,1ll * pre[i] + s[i + 1]);
	td::cout<<ans<<std::endl;
```

### subtask2

我们发现这一档的分的关键是 $k$ 很小，那么我们先轻松就能想到一个朴素的 $dp$ ,我们设 $f_i$ 为以 $i$ 处为结尾的划分的答案最大值。为了满足转移次数最小，我们每次转移都要附上一个较大的代价 $INF$ 。

所以转移方程为 $f_i = \max_{j = \max(0,i - k + 1)}(f_j + p(j + 1,i)) - INF,p(x,y) = \max_{i = x} ^ y a_i$ 。

最后我们发现转移次数我们是可以计算出来的，我们为 $f_n$ 加上 $\lfloor\frac{n}{k}\rfloor + [n \ mod\ k  > 0] * INF$ 就好了。

```c++
	for(int i = 1;i <= n;++i)
	f[i] = -9e18;
	// std::cout<<f[0]<<std::endl;
	for(int i = 1;i <= n;++i){
	ll ma = a[i];
	ll m = std::max((ll)0,i - k + 1);
	f[0] = 0;
	for(int j = i;j >= m;--j){
		ma = std::max(a[j],ma);
		f[i] = std::max(1ll * f[j - 1] + ma - INF,f[i]);
	}
	// std::cout<<f[i] + (i / k + (i % k > 0)) * INF<<std::endl;
	}
	std::cout<<1ll * f[n] + 1ll * (n / k + (n % k > 0)) * INF<<std::endl;
```

### all subtask 

我们考虑 $p(x,y)$ 是一个较难处理的点，我们可以使用单调栈来处理他。

即我们依次向右扩展当前节点，并维护最大值的阶段。

我们需要一个可以处理区间修改，区间查询最大值的数据结构，线段树。

但是要注意一个最大值区间所对应的贡献区间要向左移一位。

```c++
// Problem: P6647 [CCC 2019] Tourism
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6647
// Memory Limit: 128 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 1000005


const ll INF = 1e12;
ll n,k;
int a[N];
ll f[N];

struct seg{int l,r;ll v,tag;}t[N * 6];

ll st[N],tp;

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mid ((l + r) >> 1)

inline void build(int u,int l,int r){
	t[u].l = l;
	t[u].r = r;
	if(l == r)
	return ;
	build(ls(u),l,mid);
	build(rs(u),mid + 1,r);
}

inline void up(int u){
	t[u].v = std::max(t[ls(u)].v,t[rs(u)].v);
}

inline void push_down(int u){
	if(t[u].tag){
		t[ls(u)].tag += t[u].tag;
		t[ls(u)].v += t[u].tag;
		t[rs(u)].tag += t[u].tag;
		t[rs(u)].v += t[u].tag;
		t[u].tag = 0;
	}
}

inline void md(int u,int tl,int tr,ll p){
	// std::cout<<u<<" "<<t[u].l<<" "<<t[u].r<<" "<<tl<<" "<<tr<<" "<<p<<std::endl; 
	ll l = t[u].l,r = t[u].r;
	if(tl <= l && r <= tr){
		t[u].v += p;
		t[u].tag += p;
		return ;
	}
	push_down(u);
	if(tl <= mid)
	md(ls(u),tl,tr,p);
	if(tr > mid)
	md(rs(u),tl,tr,p);
	up(u);
}

inline ll find(int u,int tl,int tr){
	ll ans = -9e18;
	push_down(u);	
	int l = t[u].l,r = t[u].r;
	if(tl <= l && r <= tr)
	return t[u].v;
	if(tl <= mid)
	ans = std::max(find(ls(u),tl,tr),ans);
	if(tr > mid)
	ans = std::max(find(rs(u),tl,tr),ans);
	return ans;
}

int main(){
	scanf("%lld%lld",&n,&k);
	for(int i = 1;i <= n;++i)
	scanf("%lld",&a[i]);
	build(1,0,n);
	for(int i = 1;i <= n;++i){
		while(tp && a[st[tp]] <= a[i]){
		if(a[st[tp]] == a[i]){--tp;continue;}
		md(1,st[tp - 1],st[tp] - 1,a[i] - a[st[tp]]);//[st[tp] + 1,st[tp + 1]]向左移一位
		--tp;			
		}
		st[++tp] = i;
		md(1,i - 1,i - 1,f[i - 1] + a[i]);
		ll ans = find(1,std::max(i - k,(ll)0),i - 1);
		f[i] = ans - 1ll * INF;
	}
	// for(int i = 1;i <= n;++i)
	// std::cout<<f[i] + (i - 1 + k) / k * INF<<std::endl; 
	std::cout<<f[n] + (n - 1 + k) / k * INF;
	
}
```





---

## 作者：Purslane (赞：3)

## Solution

这个操作 , 学到了 !

考虑如何让操作次数最小 . 一个新奇的 trick : 给每次操作付一个手续费 , 高达 $10^{12}$ 或更多 ( 其实越高越保险 , 但是会爆 long long ) . 这样程序就会自动选择更少的操作 . 

然后就是平凡的 dp 了 : $dp_i$ 表示以 $i$ 结尾 , 用的次数最小 , 获得的最大利益 .

$$dp_i=\max^{i-1}_{j=i-k}\{dp_j+\max^{i}_{x=j+1}a_x\}- \infty$$

然后考虑怎么维护 . 我们可以建立线段树 , 表示从这一个数往后分一大段获得的利益 , 查询区间最大值 .

然后怎么搞这个 $\max a_i$ . 然后我们发现 , $a_i$ 的影响力能扩展到前面第一个大于 $i$ 的数 , 那么是不是可以单调栈 . 退栈的时候 , 需要把这连续一段都改成 $a_i$ , 然后插入一段连续的 .

具体细节看代码 .

```cpp
#include<bits/stdc++.h>
#define int long long
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,INF=1e12;
int n,k,a[MAXN],dp[MAXN],mx[MAXN<<2],tag[MAXN<<2];
void push_down(int k,int l,int r) {
	mx[lson]+=tag[k],mx[rson]+=tag[k],tag[lson]+=tag[k],tag[rson]+=tag[k];tag[k]=0;
}
void push_up(int k) {
	mx[k]=max(mx[lson],mx[rson]);
}
void update(int k,int l,int r,int x,int y,int val) {
	if(y<l) return ;
	if(x<=l&&r<=y) return mx[k]+=val,tag[k]+=val,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,val); if(y>mid) update(rson,mid+1,r,x,y,val);
	push_up(k);
	return ;
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx[k];
	push_down(k,l,r);
	if(x>r||l>y) return -0x3f3f3f3f3f3f3f3f;
	return max(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>a[i];
	dp[1]=a[1]-INF;stack<pair<pair<int,int>,int>> st;st.push({{0,0},INF});st.push({{1,1},a[1]});
	int mmx=a[1];
	ffor(i,2,n) {
		int lst=i;
		while(st.top().second<=a[i]) {
			int L=st.top().first.first,R=st.top().first.second,w=st.top().second;
			lst=min(lst,L);st.pop();update(1,1,n,L-1,R-1,a[i]-w);
		}
		mmx=max(mmx,a[i]);
		update(1,1,n,i-1,i-1,dp[i-1]+a[i]);
		int l=i-k,r=i-1;
		dp[i]=query(1,1,n,max(1ll,l),r)-INF;
		if(l<=0) dp[i]=max(dp[i],mmx-INF);
		st.push({{lst,i},a[i]});
	}
	cout<<dp[n]+((n-1)/k+1)*INF;
	return 0;
}
```

迷之 RE : 有没有哪位很懂的人告诉我 , 为什么不开 O2 会 RE ?

---

## 作者：liu_yi (赞：3)

## 前言

这题有点难想，但代码不长。

## 解题思路

考虑暴力 DP。设 $dp_{i,j}$ 表示前 $i$ 个景点分成 $j$ 天游览的最大评分，整体时间复杂度为 $\Theta(n\times k)$。

$$dp_{i,j}=\max\limits_{l=i-k}^{i-1}(dp_{l,j-1}+\max\limits_{x=l+1}^{i}{a_x})$$

此时，我们配合特殊性质可以拿到 $40$ 分，显然不优，需要优化。由于有 $t$ 的限制，我们可以改变一下 DP 的设计。重设 $dp_{i,j}$ 表示前 $i$ 个景点用最短的天数，那么转移方程就得改一下，可以想到给每一天减去一个 $\infty$，这里的 $\infty$ 表示一个极大值，这样最大值一定在最少天数上取到，最后计算答案再加上 $\left\lceil\dfrac{n}{k}\right\rceil\times \infty$ 即可。此时式子是这样的：

$$dp_i=\max\limits_{l=i-k}^{i-1}(dp_l+\max\limits_{x=l+1}^{i}{a_x})-\infty$$

这样只优化了空间，时间复杂度还是 $\Theta(n\times k)$，考虑继续优化。由于是求区间最大值，我们考虑使用线段树来维护，但是 $dp_l+\max\limits_{x=l+1}^{i}{a_x}$ 会变化，所以我们还得再考虑一下加入 $i$ 这个景点有什么影响，若 $j<i$ 并且 $\max\limits_{x=j+1}^{i-1}{a_x}<a_i$，那么就会产生影响，增值为 $a_i-\max\limits_{x=j+1}^{i-1}{a_x}$，如何快速求出这个 $j$ 呢？考虑单调栈，每次取出小于等于 $a_i$ 的栈顶元素，更新并弹出，由于每个景点只会入栈一次出栈一次，时间复杂度是 $\Theta(n)$ 的，没有影响。至此，我们在 $\Theta(n\log n)$ 的时间复杂度下通过了此题。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INF 10000000000000

int n,k,a[1000010],dp[1000010],s[1000010],top;
struct node{
    int sum,tag;
}tree[4000010];
inline void pushup(register int cur){
    tree[cur].sum=max(tree[cur<<1].sum,tree[cur<<1|1].sum);
}
inline void addtag(register int cur,register int val){
    tree[cur].tag+=val;
    tree[cur].sum+=val;
}
inline void pushdown(register int cur){
    if(!tree[cur].tag)return ;
    addtag(cur<<1,tree[cur].tag);
    addtag(cur<<1|1,tree[cur].tag);
    tree[cur].tag=0;
}
inline void update(register int cur,register int l,register int r,register int x,register int y,register int z){
    if(l>y||r<x)return ;
    if(x<=l&&r<=y){
        addtag(cur,z);
        return ;
    }
    register int mid=l+r>>1;
    pushdown(cur);
    update(cur<<1,l,mid,x,y,z),update(cur<<1|1,mid+1,r,x,y,z);
    pushup(cur);
}
inline int query(register int cur,register int l,register int r,register int x,register int y){
    if(l>y||r<x)return LLONG_MIN;
    if(x<=l&&r<=y)return tree[cur].sum;
    register int mid=l+r>>1;
    pushdown(cur);
    return max(query(cur<<1,l,mid,x,y),query(cur<<1|1,mid+1,r,x,y));
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(register int i=1;i<=n;i++)cin>>a[i];
    for(register int i=1;i<=n;i++){
        while(top&&a[s[top]]<a[i]){
            update(1,0,n,s[top-1],s[top]-1,a[i]-a[s[top]]);
            top--;
        }
        while(top&&a[s[top]]==a[i])top--;
        s[++top]=i;
        update(1,0,n,i-1,i-1,dp[i-1]+a[i]);
        dp[i]=query(1,0,n,max(0ll,i-k),i-1)-INF;
    }
    cout<<dp[n]+(int)ceil(n*1.0/k)*INF;
    return 0;
}
```

---

## 作者：Z1qqurat (赞：3)

赛前写一波题解攒攒 rp。真的是神题，膜拜场切之神 zzq！

首先不难设计出一个 dp：$f_{i, j}$ 表示用 $j$ 天游览完前 $i$ 个景点的最大价值，那么转移就很显然了：

$$
f_{i, j} = \max\limits_{i - k \le l \le i - 1} \{ f_{l, j - 1} + \max\limits_{l + 1 \le r \le i} a_r\}
$$

感觉很难优化，不是吗！而且看一手部分分，除了送的 $2k \ge n$ 以外没有给这个 $\mathcal{O} (n ^ 2)$ 做法的部分分！看到 $k \le 100, n \le 10 ^ 5$ 的一档，感觉绝对是 $\mathcal{O} (nk)$。考虑怎么去掉 $t = \left\lceil {\frac{n}{k}}\right\rceil$。手玩发现因为最后要求以最少天数完成所有 $n$ 个景点，所以无论现在是到了前几个景点，都是以尽量少的天数访问完，其他的状态都是无效的。

于是设 $f_i$ 表示以 $t_i = \left\lceil {\frac{i}{k}}\right\rceil$ 天访问完前 $i$ 个景点可以得到的最大价值。怎么转移？难点在于要保证是以 $t_i$ 天访问完。我们考虑枚举 $j$，使第 $t_i$ 天访问了 $j + 1 \sim i$ 个景点。那么这样的 $j$ 只需要满足 $\max(0, i - k) \le j \le i - 1$ 且 $t_j + 1 = t_i$ 即可。于是可以简单 $\mathcal{O}(nk)$。我考场上就是这个神秘做法。

但是你会发现这个非常难优化啊，$t_j + 1 = t_i$ 的限定条件简直没法优化。其实难点就在于要保证最小化天数，剩下的就是一个区间查询的问题。zzq 讲了一个神仙做法：为了最小化天数，我们将转移方程改成 $f_i =  \max\limits_{i - k \le j \le i - 1} \{ f_j + \max\limits_{j + 1 \le l \le i} a_l \} - \infty$，那么肯定会最小化天数了，答案就是 $f_n + t_n \times \infty$。其实这很像二分图最大权匹配里面将原图补成完全二分图的方式有没有！！！

接下来我们设 $g_j$ 在 $i$ 时刻的取值为 $f_j + \max\limits_{j + 1 \le l \le i} a_l$，那么 $f_i = \max\limits_{i - k \le j \le i - 1} g_j - \infty$。考虑从时刻 $i-1$ 推到时刻 $i$ 时 $g$ 的变化量。如果 $g_j < a_i$，那么 $g_j$ 会改变。这相当于让我们找一个值在序列中为最大值的区间范围，这很单调栈。我们维护一个递减的单调栈，现在我们有单调栈中两个点 $u, v$，分别为 $stk_{top - 1}, stk_{top}$，且 $a_u > a_v, a_v \le a_i$。那么对于 $j \in [u, v - 1], g_j$ 要从 $a_v + f_j$ 变成 $a_i + f_j$，相当于 $+ (a_i - a_v)$。于是我们加入 $a_i$ 时，用单调栈求出 $u, v$，将 $[u, v - 1]$ 做一个区间加的修改，然后 $f_i$ 的转移就相当于一个区间查询 $\max$。这个操作用线段树解决。然后这个修改操作均摊下来是 $\mathcal{O} (n)$ 次的，因为每个数只会进入单调栈一次。用一个线段树维护即可。总复杂度 $\mathcal{O} (n \log n)$，好写而且跑得飞快。

每一个踏实且努力的人都值得尊重，感谢 zzq 的讲解。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lc (p << 1)
#define rc (p << 1 | 1)
using namespace std;
const int N = 1e6 + 5;
const ll inf = 1e12;
int n, k, a[N], t, s[N], top;
ll f[N];

int divu(int x, int y) {
    return (x - 1 + y) / y;
}

namespace SegT{
    ll tr[N << 2], tag[N << 2];
    void pushup(int p) {
        tr[p] = max(tr[lc], tr[rc]); return ;
    }
    void addtag(int p, ll v) {
        tag[p] += v, tr[p] += v; return ;
    }
    void pushdown(int p) {
        if(tag[p]) addtag(lc, tag[p]), addtag(rc, tag[p]);
        tag[p] = 0; return ;
    }
    void modify(int p, int l, int r, int x, int y, ll v) {
        if(x <= l && r <= y) return addtag(p, v);
        pushdown(p);
        int mid = l + r >> 1;
        if(x <= mid) modify(lc, l, mid, x, y, v);
        if(y > mid) modify(rc, mid + 1, r, x, y, v);
        pushup(p); return ;
    }
    void modify(int x, int y, ll v) {
        modify(1, 0, n, x, y, v);
    }
    ll query(int p, int l, int r, int x, int y) {
        if(x <= l && r <= y) return tr[p];
        pushdown(p);
        int mid = l + r >> 1;
        if(x > mid) return query(rc, mid + 1, r, x, y);
        if(y <= mid) return query(lc, l, mid, x, y);
        return max(query(rc, mid + 1, r, x, y), query(lc, l, mid, x, y));
    }
    ll query(int x, int y) {
        return query(1, 0, n, x, y);
    }
} using namespace SegT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k; t = divu(n, k);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        while(top && a[i] >= a[s[top]]) {
            if(a[i] == a[s[top]]) { top--; continue;}
            modify(s[top - 1], s[top] - 1, a[i] - a[s[top]]);
            top--;
        }
        s[++top] = i;
        modify(i - 1, i - 1, f[i - 1] + a[i]);
        f[i] = query(max(0, i - k), i - 1) - inf;
    }
    cout << f[n] + 1ll * t * inf << "\n";
    return 0;
}
```

---

## 作者：Sktic (赞：2)

[P6647 [CCC2019] Tourism](https://www.luogu.com.cn/problem/P6647)

这道题我们可以从朴素的 dp 想起，然后逐步优化。



我们设 $dp_{i,j}$ 为在前 $i$ 天逛了 $j$ 个景点的每天最大评分和。



那么显然可以得到：
$$
dp_{i,j}=\max_{t=j-k}^{j-1}\{dp_{i-1,t}+\max(a_{t+1},a_{t+2},\cdots,a_{j})\}
$$
由于题目要求采用最少的天数浏览，而这个比较难用常规 $dp$ 方式处理，于是我们可以考虑对于每一次操作（天数+1），我们让答案都减去一个超级大的数字 $inf$ （其远远大于答案规模，可以看作 $\infty$ ），这样程序为了使答案尽量大，会选择最小的天数（即减去尽量少的 $inf$ ），可以满足题目的要求。于是我们还可以削掉 $dp$ 的第一维，使 $dp_i$ 表示的意义变为**采用最少的天数浏览前 $j$ 个景点的每日最大评分和** 。



可以得到这样的转移方程：
$$
dp_{i}=\max_{t=i-k}^{i-1}\{dp_{t}+\max(a_{t+1},a_{t+2},\cdots,a_{i})-inf\}
$$
于是每次枚举时遍历 $a$ 求最大值，总时间复杂度为 $O(nk)$ 。



这样只能获得 $40$ 分，考虑优化 $dp$ 时求最大值的过程。



我们可以发现对于 $\max(a_{t+1},a_{t+2},\cdots,a_{i})$ 求最大值时，当 $i$ 每增加 $1$ ，其对应的区间也向右移动一位。对于新增加的 $a_{i+1}$ ，考虑 $\max(\max(a_{t+1},\cdots,a_i),a_{i+1})$ 的值。



于是我们可以发现区间中最大的 $a_{i+1}$ 能影响前面一段的 $a$ 序列的最大值直到前面第一个 $\ge a_i$ 的数字出现，考虑单调栈维护。



于是每次对于一段会被最大值更新的区间，进行区间修改最大值，在采用 $dp$ 递推时区间查询，即可做到 $O(n\log n)$ 。



AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn=1e6+10;
const ll INF=1e12;
struct node
{
	int l,r;
	ll mx;
	ll las;
}c[maxn<<2];
void pushdown(int x)
{
	if(c[x].las)
	{
		c[x<<1].las+=c[x].las;
		c[x<<1|1].las+=c[x].las;
		c[x<<1].mx+=c[x].las;
		c[x<<1|1].mx+=c[x].las;
		c[x].las=0;
	}
} 
void build(int x,int l,int r)
{
	c[x].l=l;
	c[x].r=r;
	if(l==r) 
		return;
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void modify(int x,int l,int r,ll k)
{
	if(l<=c[x].l&&r>=c[x].r)
	{
		c[x].las+=k;
		c[x].mx+=k;
		return;
	}
	pushdown(x);
	int mid=c[x].l+c[x].r>>1;
	if(l<=mid)
		modify(x<<1,l,r,k);
	if(r>=mid+1)
		modify(x<<1|1,l,r,k);
	c[x].mx=max(c[x<<1].mx,c[x<<1|1].mx);
	return;
}
ll query(int x,int l,int r)
{
	if(l<=c[x].l&&r>=c[x].r)
		return c[x].mx;
	pushdown(x);
	ll ans=-1e18;
	int mid=c[x].l+c[x].r>>1;
	if(l<=mid)
		ans=max(ans,query(x<<1,l,r));
	if(r>=mid+1)
		ans=max(ans,query(x<<1|1,l,r));
	return ans;
}
ll a[maxn],dp[maxn];
ll st[maxn],tot=0;
int main()
{
	ios::sync_with_stdio(false);
	ll n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		while(tot&&a[st[tot]]<=a[i])
		{
			if(a[i]==a[st[tot]])
			{
				tot--;
				continue;
			}
			modify(1,st[tot-1]+1,st[tot],a[i]-a[st[tot]]);
			tot--;
		}
		st[++tot]=i;
		modify(1,i,i,dp[i-1]+a[i]);
		dp[i]=query(1,(i-k>0ll?i-k:0ll)+1,i)-INF;
	}
	cout<<dp[n]+(ll)((n-1)/k+1)*INF;
	return 0;
}
```



---

## 作者：快斗游鹿 (赞：0)

## 思路

先考虑最简单的 dp。设 $f_{i,j}$ 表示游览到第 $i$ 个景点，用了 $j$ 天的答案，显然有 $f_{i,j}=\displaystyle\max_{p=i-k}^{i-1} (f_{p,j-1}+\displaystyle\max_{q=p+1}^i a_i)$。但这样做时间复杂度是 $O(nk)$ 的，空间复杂度也是 $O(nk)$，过不去。

因为有天数最少的限制，所以我们可以设 $f_i$ 表示游览到第 $i$ 个景点且花费天数最少的答案。这么一来，我们可以省掉一维。转移方程变为 $f_i=\displaystyle\max_{p=i-k}^{i-1} (f_p+\displaystyle\max_{q=p+1}^i a_i-inf)$，其中，$inf$ 是一个极大值。这样可以保证花费天数最少。但这样时间复杂度仍为 $O(nk)$。所以接下来要优化转移过程。

我们发现，上述转移相当于求两次区间最大值。我们可以用线段树维护 $f_i$ 的区间最大值。那么如何修改呢？我们可以使用单调栈，每次找到一段会被当前 $a_i$ 影响的区间，并修改，即把以前的最大值减掉，加上新的最大值。再思考一下，会发现每个 $f_i$ 其实只能由 $[i-k,\lfloor \dfrac{i-1}{k} \rfloor\times k]$ 中转移过来。否则无法满足最小天数。至此，本题就解决了。总时间复杂度 $O(n\log n)$。

## 代码

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+5;
const int inf=1e12;
struct tree{
	int l,r,mx,tag;
}t[N<<2];
int n,k,a[N],dp[N];
stack<int>st;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r); 
}
void change(int p,int l,int r,int w){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].mx+=w;
		t[p].tag+=w;
		return;
	}
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)change(p<<1,l,r,w);
	if(r>mid)change(p<<1|1,l,r,w);
	t[p].mx=max(t[p<<1].mx,t[p<<1|1].mx); 
}
void solve(int x){
	change(1,x-1,x-1,a[x]);
	int lst=x-2;
	while(!st.empty()&&a[st.top()]<a[x]){
		int sss=a[st.top()];st.pop();
		change(1,st.top(),lst,a[x]-sss);
		lst=st.top()-1;
	}
	st.push(x);
}
void spread(int p){
	if(t[p].tag){
		t[p<<1].mx+=t[p].tag;
		t[p<<1|1].mx+=t[p].tag;
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0;
	}
}
int ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r)return t[p].mx;
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	int aaa=-1e18;
	if(l<=mid)aaa=max(aaa,ask(p<<1,l,r));
	if(r>mid)aaa=max(aaa,ask(p<<1|1,l,r));
	return aaa;
}
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,0,n);
	st.push(0);
	a[0]=1e18;
	for(int i=1;i<=n;i++){
		solve(i);
		int lll=i-k,rrr=(i-1)/k*k;if(lll<0)lll=0;
		/*int mx=a[i],w=-1e18; 
		for(int j=i-1;j>=lst;j--){
			w=max(w,dp[j]+mx-inf);
			mx=max(mx,a[j]);
		}
		dp[i]=w;*/
		dp[i]=ask(1,lll,rrr);
		change(1,i,i,dp[i]);
		//cout<<dp[i]<<endl;
	}
	cout<<dp[n];
	return 0;
}

```


---

