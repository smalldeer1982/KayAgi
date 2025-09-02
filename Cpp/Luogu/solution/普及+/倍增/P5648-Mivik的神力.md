# Mivik的神力

## 题目背景

$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$发怒了，机房的$\textcolor{grey}{\text{deco}}$瑟瑟发抖

## 题目描述

$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$要写一篇文章，在写文章时，他有$n$个备选的单词，第$i$个单词有一个长度$a_i$，$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$可以选择从第$i$个单词开始写作，一共写$k$秒，第$j$秒会写上第$i+j-1(j\in[1,k])$个单词，并且他在写作时每秒都会获得愉悦值，第$j$秒的愉悦值为$max_{l=i}^{i+j-1} a_l$，现在，请你帮他算出，他每一次写作获得的愉悦值之和

**一句话题意：给出一个序列和多组询问 $(l,q)$ ，求**

$$
\sum_{i=l}^{l+q-1} \max_{l\le j\le i}a_j
$$

**数据要求强制在线**

## 说明/提示

**样例解释**

第一个询问 $1,1$，解密后得到 $l=2,q=1$ ，则按题意可得所求即为区间 $[2,2]$ 的最大值，为 $2$

第一个询问 $1,2$ ，解密后得到 $l=1,q=2$ ，则所求即为区间 $[1,1]$ 和区间 $[1,2]$ 的最大值之和，为 $3$

-----

对于$20\%$的数据，$n \leq 1000$，$t \leq 1000$

对于$100\%$的数据，$n\leq 500000$，$t\leq 500000$，$1 \leq a_i\leq 10^9(i\in [1,n])$

## 样例 #1

### 输入

```
3 2
1 2 3
1 1
1 2```

### 输出

```
2
3```

# 题解

## 作者：Mivik (赞：39)

**我并没有神力ww**

- 20 pts.

直接暴力。

时间复杂度 $O(m\cdot n^2)$

- 90 pts.

读入时用单调栈记录每一个点后面第一个比他大的数的位置（记为 $fa_i$ ），询问时跳跃统计

时间复杂度 $O(n+(m\cdot n\sim m\cdot n^2))$

~~出题人：是我少出了单调递增的数据点卡你们~~

- 90 pts. $PLUS$

观察到这个序列是不变的，因此我们预先倍增处理一个点往后“跳跃” $2^k$ 次能跳跃到哪里和“跳跃”的贡献

时间复杂度 $O(n+m\cdot\log n)$

- 100 pts.

我们来观察一个区间。我们从这个区间的左端点开始“跳跃”统计，我们将在哪一个点结束呢？

没错。我们将会在这个区间最左侧最大值的位置结束。我们可以用一个ST表来维护区间最大值的**位置**

然后我们来观察我们这个“跳跃”的路径，由于每一个点有且只有一个“跳跃”的目标，因此不能看出这是一个树形结构

综上所述，我们现在知道了树上的起始点和结束点，那么这个题就被转化为树上求两点之间距离的板子题了

又由于本题的特殊情况，我们的结束点必定是起始点的祖先，因此我们仅仅需要一个 $dis$ 数组来存储每一个点到根节点（ 根节点是 $n+1$，因为原序列最大值默认的 $fa$ 是 $n+1$ ）的距离即可

**举个例子**

我们现在有一个序列 $1,1,4,5,1,4$ ，那么我们可以得到它对应的 $fa$ 数组为 $3,3,4,7,6,7$

我们把每一个点的 $fa$ 作为它在树上的父亲，就可以得到下面的树

![树](https://s2.ax1x.com/2019/11/10/MKTJat.png)

这是假如我们想要查询 $[1,5]$ 这个区间的答案，我们可以首先查询到 $[1,5]$ 这个区间的最大值是在第4位，因此答案最终就是要从1号点跳到4号点路上所有的权值，再加上4号点到5号点额外的贡献

时间复杂度 $O(n\cdot\log n+m)$

[代码](https://www.luogu.org/paste/trfv5br4)

---

## 作者：Froggy (赞：27)

### 卡常神仙题!

本萌新不会线性做法,只会带log的

首先,可以发现,对于同一个询问 $\max\limits_{l \le j \le i}{a_{j}}$是单调非递减的,这个值改变的条件是下一个数比当前答案大

所以先预处理一下每个数之后第一个大于它的位置,计为$next_{i}$

那么每个询问的答案就是:$\sum {a_{i} \times (next_{i}-i)}$ 暴力往后跳即可,这样你就可以拿到$90pts$的好成绩!!~~(数据水)~~

如果$a$是单调递增的,那就会被卡到飞起 $O(nt)$

暴力跳步星,那就一次性跳多次!

想到了什么?(⊙ˍ⊙)？

## 倍增!!

记录跳$2^{j}$后的位置和这一段的答案,如果跳出去了就计为跳到$n+2$

$f_{i,j}$表示从$i$跳 $2^{j}$ 次后的答案(最大值之和), $nxt_{i,j}$表示从$i$跳$2^j$后的位置

状态转移:

$nxt[i][j]=nxt[nxt_{i,j-1}][j-1]$

$f[i][j]=f[i][j-1]+f[nxt_{i,j-1}][j-1]$

初始化:

```cpp
for(int i=1;i<=n;i++){
	while(top&&a[st[top]]<a[i]){//用栈找每一个位置第一个大于它的位置
		nxt[st[top]][0]=i;
		--top;
	}
	st[++top]=i;
}
while(top)nxt[st[top--]][0]=n+2;//细节,别忘了把栈清空
nxt[n+1][0]=nxt[n+2][0]=n+2;
for(register int i=1;i<=n;++i){//初始化
	f[i][0]=1LL*a[i]*(nxt[i][0]-i);
}
for(register int j=1;j<=MX;++j){//倍增
	for(register int i=1;i<=n+2;++i){//先要把每个位置都设成n+2
		nxt[i][j]=n+2;
	}
	for(register int i=1;i+(1<<j)-1<=n;++i){
		nxt[i][j]=nxt[nxt[i][j-1]][j-1];
		f[i][j]=f[i][j-1]+f[nxt[i][j-1]][j-1];
	}
}
```

最后统计答案,从大到小枚举$j$,能跳就跳,把答案加一块即可

所有代码:

注:本人不太会卡常,提交个20次才能AC ~~(出题人卡时间,过于毒瘤)~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize(3)
#define N 500050
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
ll f[N][22],a[N];
int n,Q,nxt[N][22];
ll ans;
int st[N],top;
int buf[111],p; 
inline void Output(ll x){
	p=0;
	while(x)buf[++p]=x%10,x/=10;
	while(p)putchar(buf[p--]+'0');
	putchar('\n');
}
int main(){
	n=read(),Q=read();
	int MX=log2(n)+1;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i]){
			nxt[st[top]][0]=i;
			--top;
		}
		st[++top]=i;
	}
	while(top)nxt[st[top--]][0]=n+2;
	nxt[n+1][0]=nxt[n+2][0]=n+2;
	for(register int i=1;i<=n;++i){
		f[i][0]=1LL*a[i]*(nxt[i][0]-i);
	}
	for(register int j=1;j<=MX;++j){
		for(register int i=1;i<=n+2;++i){
			nxt[i][j]=n+2;
		}
		for(register int i=1;i+(1<<j)-1<=n;++i){
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			f[i][j]=f[i][j-1]+f[nxt[i][j-1]][j-1];
		}
	}
	while(Q--){
		int u=read(),v=read();
		int l=1+(u^ans)%n,r=(v^(ans+1))%(n-l+1)+l;
		int pos=l;
		ans=0;
		for(register int i=MX;i>=0;--i){
			if(nxt[pos][i]-1>r)continue;
			ans+=f[pos][i];
			pos=nxt[pos][i];
		}
		ans+=a[pos]*(r-pos+1);
		Output(ans);
	}
	return 0;
}
/*
10 10
3 1 4 4 2 1 6 3 2 9
1 2
2 3
1 4
2 5
3 6
4 7
2 10
3 4
1 4
5 8
*/
```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!

---

## 作者：decoqwq (赞：18)

题意，给定$n$个数，$a_1..a_n$，每次给出$l,r$，令$f(l,r)$为$[l,r]$中最大值，求$\sum\limits_{i=l}^r f(l,i)$

令$suf[i]$表示第一个大于$a[i]$的位置，若不存在则为$n+1$

然后每次查询时，我们考虑每个点最为最大值的贡献，先找到当前区间中第一个$suf[i]$大于$r$的点，则区间$[i,r]$的最大值为$a[i]$，后面的和可以直接算出，用线段树求出这个点，复杂度$O(log n)$

然后前面的点，我们从第一个点开始算答案，每算完一个点$i$就跳到$suf[i]$，依次计算，但如果序列单调递增，这样的复杂度就是$O(n)$的，需要优化

考虑到每个点的后继是唯一的，我们可以把它看作一棵树的形态，用树上前缀和，预处理复杂度$O(n)$，单次查询复杂度$O(1)$

总时间复杂度$O(qlogn)$

然后找最大值那个地方可以用$01rmq$，就可以线性复杂度

反正是一道屑题

---

## 作者：VegChicken (赞：12)

### 题意
给你一个序列，多组询问：给定 $(l,r)$ 求 $\sum\limits_{l\le i\le r}\max\limits_{l\le j\le i}a_j$ 。强制在线。

### 离线做法
首先，我们发现强制在线这个要求很难受，考虑离线怎么做~~离线是不是加边加边加边然后并查集查询~~。我们这么想，题目要求的式子是一个求和套求最大值，我们考虑把询问按照左端点排序。什么东西擅长维护区间和？我们首先考虑线段树。所以一个离线做法呼之欲出：我们拿一个线段树倒着扫序列，线段树上的每一个位置存的是从指定点到每一个点的区间最大值，预处理出每一个点左右第一个比他大的位置，移动线段树时直接区间覆盖即可。求和就可以直接上线段树了。

### 在线做法
看完离线做法，我们考虑将他“魔改”成在线做法。考虑这么做：我们预处理指定每一个阶段的线段树，然后直接区间查询，**等等，这不是主席树吗?**

考虑建出主席树，然后就可以直接回答询问了。反过头来看我们的离线做法，我们发现他们之间的修改是区间覆盖，这可以主席树吗？答案是**可以！**

#### 魔改的主席树
首先，主席树的本质就是线段树，它的操作也基本和线段树相同，所以我们发现我们唯一要考虑的是区间懒标记的建立与下放。

因为主席树的空间问题，所以我们暴力下放懒标记会空间爆炸，我们想到另一种科技——标记永久化。具体来说，就是每次碰到懒标记不去下放，就把他放在原位不动，把子树递归完后再根据懒标记改变答案。

考虑对主席树的节点打上永久化的覆盖标记，每次查询时碰到懒标记直接返回它乘以区间长度。我们可以先这么写一下，然后发现全部错了。。。为什么呢？考虑我们的建树：

![ ](https://cdn.luogu.com.cn/upload/image_hosting/mid8jbeq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

假设我们的红点上有一个永久化的懒标记，现在在对绿点建树，“很自然地”继承了黄点去算和，但是懒标记在红点上，黄点上的区间和是错误的，这就导致了绿点区间和的错误。换句话来说，我们的问题出在建树上。

我们来换一种做法。在建树的过程中“顺便”记录一下原来树上走过的第一个永久化标记，在看见黄点时给他“打上”即可。可是这样还是错误的，为什么呢？考虑下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/5y3ebcmg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们在绿点的基础上给蓝点建树，把绿点上的永久化标记推到了黄点上，但是黄点不仅属于绿点和蓝点，还属于红点！所以我们同时改了其他不应该改的线段树的值。

我们貌似陷入了困境，但是考虑后缀自动机的建立方法——当一个新点出现矛盾时，我们不妨考虑把它复制了：

![](https://cdn.luogu.com.cn/upload/image_hosting/3ub9tgg1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这里我们把黄点复制到橙点，然后给他打上懒标记，和蓝点接起来。这样的话，我们就可以区间修改主席树，并且不会改变其他点的值！而且空间复杂度显然也是 $n\log n$ 级别的。

### 总结
所以来看一遍完整解法：用单调栈预处理每一个点左右两边第一个比他大的位置，然后建立主席树，对于询问，我们直接在对应版本的主席树上查区间和即可。
 
 **注意：因为主席树的空间复杂度多一个 $\log$ ,所以我们需要精细实现空间。**
 
 附上代码：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define inf (1ll<<60)
//不用解释的快读快写
#define gc() getchar()
#define pc(a) putchar(a)
inline long long read()
{
	long long x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0') 
	{
		if(c=='-') f=-f;
		c=gc();
	}
	while(c>='0'&&c<='9') x=x*10+c-'0',c=gc();
	return x*f;
}
int buffer[25];
inline void write(long long x)
{
	if(!x)
	{
		pc('0');
		return;
	}
	if(x<0) pc('-'),x=-x;
	int top=0;
	while(x) buffer[++top]=x%10,x/=10;
	while(top) pc(buffer[top]+'0'),top--;
	return;
}
#define ma 500005
long long s[ma<<5];
int ls[ma<<5],rs[ma<<5];
long long tag[ma<<5];
int root[ma],tot;
//我们的魔改主席树
inline void New(int &i){i=++tot;}
void push(int pre,int &i,int l,int r,int L,int R,long long v,int tg)//区间修改的基础上建树
{//tg是记录的懒标记
	New(i);
	if(!tg) tg=tag[pre];
	if(L<=l&&r<=R)
	{
		s[i]=1ll*v*(r-l+1);
		tag[i]=v;//打上永久化的懒标记
		return;
	}
	int mid=(l+r)>>1;
	if(L<=mid&&mid+1<=R)
	{
		push(ls[pre],ls[i],l,mid,L,R,v,tg);
		push(rs[pre],rs[i],mid+1,r,L,R,v,tg);
		s[i]=s[ls[i]]+s[rs[i]];//分别递归左右子树
	} 
	else if(L<=mid)
	{
		push(ls[pre],ls[i],l,mid,L,R,v,tg);
		rs[i]=rs[pre];
		if(tg)
		{
			New(rs[i]);//新建一个复制打上懒标记
			ls[rs[i]]=ls[rs[pre]];
			rs[rs[i]]=rs[rs[pre]];
			tag[rs[i]]=tg;
			s[rs[i]]=1ll*tg*(r-mid);
		}
		s[i]=s[ls[i]]+s[rs[i]];
	}
	else//同上
	{
		push(rs[pre],rs[i],mid+1,r,L,R,v,tg);
		ls[i]=ls[pre];
		if(tg)
		{
			New(ls[i]);
			ls[ls[i]]=ls[ls[pre]];
			rs[ls[i]]=rs[ls[pre]];
			tag[ls[i]]=tg;
			s[ls[i]]=1ll*tg*(mid-l+1);
		}
		s[i]=s[rs[i]]+s[ls[i]];
	} 
	return;
}
long long sum(int i,int l,int r,int L,int R)//区间求和
{
	if(L<l) L=l;
	if(R>r) R=r;
	if(!i) return 0;
	if(tag[i]) return 1ll*tag[i]*(R-L+1);//碰上懒标记直接算答案
	if(L==l&&r==R) return s[i];
	int mid=(l+r)>>1;
	long long ans=0;
	if(L<=mid) ans+=sum(ls[i],l,mid,L,R);
	if(mid+1<=R) ans+=sum(rs[i],mid+1,r,L,R);
	return ans;
}
int L[ma],R[ma];//每个点左右两边第一个比他大的位置
int st[ma];//单调栈
int a[ma];
signed main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int tp=0;//单调栈的预处理
	for(int i=1;i<=n;i++)
	{
		while(tp&&a[st[tp]]<=a[i]) R[st[tp--]]=i-1;
		st[++tp]=i;
	}
	while(tp) R[st[tp--]]=n;
	for(int i=n;i;i--)
	{
		while(tp&&a[st[tp]]<=a[i]) L[st[tp--]]=i+1;
		st[++tp]=i;
	}
	while(tp) L[st[tp--]]=1;
	for(int i=n;i;i--)
		push(root[i+1],root[i],1,n,L[i],R[i],a[i],0);//主席树的建立
	long long la=0;
	while(m--)
	{
		long long l=(read()^la)%n+1,r=(read()^(la+1))%(n-l+1)+1+l-1;//对于每一个询问直接查询
		write(la=sum(root[l],1,n,l,r)),pc('\n');
	}
	return 0;//完结撒花！
}

```
最后无耻求赞。。。



---

## 作者：Fish_Clever (赞：5)

### 线段树的思路。

概括：普通线段树的框架 + 普通线段树的查询。

思考的过程：先假设我们已经处理好了一颗线段树，然后看看要如何求得答案，而在求答案的过程中根据需要来维护线段树中的信息。

首先，对于询问的区间而言，它肯定能在线段树中被分成至多 $\log n$ 块，比如给定序列 $[ 1 , 3 , 2 , 4 ]$，要询问（位置） $2\sim4$ 的答案，就可以分为 $2\sim2$ 和 $3\sim4$ 这两个节点。

然而，与其它题目不同的是：这道题的“相邻”节点之间有关系——比如例子中需要将区间 $3\sim4$ 中的小于 $3$ 的数替换成 $3$，再得到和。如果没有这个限制，就是一般的区间求和了。

看似到了无解的地步，但请回忆一下，线段树的本质是什么？~~一颗由线段所构成的树~~！点不只是点，而表示一段信息，那么在本题中，我们想要它维护什么样的信息呢？肯定就是题目所要求的，一条单调不降的折线。

所以，线段树的 `query` 操作，就是将许多条折线合并为一条，并求出最终这条折线的值。

因此，我们考虑其中的一次合并，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jps8azho.png)

可以发现，左边的折线保持不变，即它对于答案还是照样加。

而对于右边的折线，哦豁，左半部分变平了,它所有小于（等于）左边折线最大值（记为 `lmax`）的部分，都变成了 `lmax`，这是因为它们与左边最大值取了个 `max` 这能否给我们新的启发？

你看这个图，对于左边的折线而言，计算答案时（就是合并时）它所需要的仅为 `sum` 和 `lmax`，这不就成了区间赋值，取 `max` 的一道题目了吗：只要在某个区间（右儿子区间）中找到小于某个数（左儿子）的第一个位置，再计算一下新贡献不就好了。

上述操作可以分两步完成，当然也可以合并完成，详见代码。
（当然了，在 `build` 时也是这样的操作）

时间复杂度的分析：就是将原来 `push_up` $O(1)$ 的时复变成了 $O(\log n)$，`query` 的 $O(\log n)$ 也多了只 $\log$，因为最坏的情况是查到叶子结点，比如这种数据：$[9,10,8,11,7,12,6,13,5,14,...]$。

所以最坏时间复杂度为 $O((n+m) \log n\log n )$。

```cpp
注：为了卡常（其实并不需要）就写了 cri 和 ri ，如果看着不习惯可以 Ctrl+F 改回 int 。
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define ls p<<1
#define rs p<<1|1
typedef long long ll;
#define ri register int
#define rll register ll
#define cri const ri
#define crll const rll
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MID(x,y) ((x)>(y)?(y):(x))
using namespace std;
inline ll read(){
	rll s=0,w=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
	return s*w;
}
inline void write(rll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=5e5+1;
int n,q;
struct SegmentTree{
	ll num;int da,tou;
	//对于每个区间,要维护不受干扰时的和,以及区间的两个最值.
	//那么显然维护的每段区间的形状都是一条"单调不降"的折线.
	//故最小值即为开头,而并非区间的最小值.
	#define sum(x) t[x].num
	#define da(x) t[x].da
	#define xiao(x) t[x].tou
}t[N<<2];
//什么时候才要改?显然,当某个区间中的最小值小于它,才会改这个区间.
int query_num;//要都改成max(原数,query_num),返回和.
ll query_sum(cri p,cri l,cri r){
	if(da(p)<=query_num) return (ll)query_num*(r-l+1);//全改.
	if(xiao(p)>=query_num) return sum(p);//不改.
//	if(l==r)//不用了(前面肯定已经排除了).
	ri mid=l+r>>1;
	if(query_num<=da(ls))//特别注意:不能直接用sum(rs).
		//想想为什么?提示:[2 4 3 5]这一段的sum(p,ls,rs).
		return query_sum(ls,l,mid)+(sum(p)-sum(ls))/*sum(rs)*/;//此时表示rson都不改.
	else
		return (ll)query_num*(mid-l+1)+query_sum(rs,mid+1,r);//此时表示lson都要改.
	//等号挂哪都一样.
}
inline void push_up(cri p,cri mid,cri r){//注意,传了mid和r(其实和传lr差不多).
	da(p)=MAX(da(ls),da(rs));
	xiao(p)=xiao(ls);//维护最值.
	query_num=da(ls);
	sum(p)=sum(ls)+query_sum(rs,mid+1,r);//维护不受干扰时的和.
	//即更新右边那条折线的<da(ls)的部分(将其改为da(ls)).
	//当然不会真的更新.
}
void build(cri p,cri l,cri r){
	if(l==r) return (void)(sum(p)=da(p)=xiao(p)=read());
	ri mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	push_up(p,mid,r);
//	printf("[%d~%d],sum=%lld da=%d xiao=%d\n",l,r,sum(p),da(p),xiao(p));
}
int q_l,q_r;
ll query(cri p,cri l,cri r){
	if(q_l<=l && r<=q_r){//注意.
		rll tt=query_sum(p,l,r);
		query_num=MAX(query_num,da(p));
//		printf("Q:(%d~%d),sum=%lld\n",l,r,tt);
		return tt;
	}
	ri mid=l+r>>1;rll sum_=0;
	if(q_l<=mid) sum_=query(ls,l,mid);
	if(mid< q_r) sum_+=query(rs,mid+1,r);
	return sum_;
}

int main(){
//	freopen("in.txt","r",stdin);
	n=read(),q=read();
	build(1,1,n);
	rll lastans=0;
	for(ri i=1;i<=q;i++){
		q_l=1+(read()^lastans)%n,q_r=(read()^(lastans+1))%(n-q_l+1)+q_l;
//		printf("q_l=%d q_r=%d\n",q_l,q_r);
		query_num=0,lastans=query(1,1,n);
		write(lastans),putchar('\n');
	}
	return 0;
}
```


---

## 作者：Mazen (赞：2)

## 倍增思路

#### 预处理

先用单调栈处理出每个数后面第一个大于它的数，记为 $nxt[i][0]$，然后倍增处理出 $nxt[i][1\sim20]$，其中 $nxt[i][k]$ 表示第$i$个数后面第 $2^k$ 个大于它的数的位置，同时维护 $sum[i][0\sim20]$，表示区间 $[i,nxt[i][k])$ 的答案。对于 $sum[i][0]$，因为 $[i,nxt[i][0])$ 中所有的数均小于等于 $a[i]$，所以 $sum[i][0]=(nxt[i][0]-i)\times a[i]$。

```cpp
void init()
{
    for(int i=1;i<=n+3;i++)
        for(int j=0;j<=20;j++)
            nxt[i][j]=n+2;
    for(int i=1;i<=n;i++)//单调栈
    {
        while(top&&a[sta[top]]<a[i])
            nxt[sta[top]][0]=i,top--;
        sta[++top]=i;
    }
    for(int i=1;i<=n;i++)
        sum[i][0]=(nxt[i][0]-i)*a[i];
    for(int i=1;i<=20;i++)//倍增
    {
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            nxt[j][i]=nxt[nxt[j][i-1]][i-1];
            sum[j][i]=sum[j][i-1]+sum[nxt[j][i-1]][i-1];
        }
    }
}
```

#### 查询答案

对于区间 $[l,r]$，我们贪心的从 $nxt[l][20]$ 开始尝试，若 $nxt[l][20]-1\le r$，则答案即可加上 $sum[l][20]$，并且令 $l=nxt[l][20]$，随后再依次尝试 $19,18,... ,0$，即可使 $l$ 跳到 $[l,r]$ 中最大值的位置,最终让答案加上 $a[l]\times (r-l+1)$ 即可。

```cpp
int query(int l,int r)
{
    int ans=0;
    for(int i=20;i>=0;i--)//从大到小贪心地尝试每一个i
    {i
        if(nxt[l][i]-1<=r)
        {
            ans+=sum[l][i];
            l=nxt[l][i];
        }
    }
    ans+=a[l]*(r-l+1);//处理区间最大值位置后面的数对答案的贡献
    return ans;
}
```

#### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+15;
int n,t,l,q,las,sum[N][21],a[N],nxt[N][21],sta[N],top;
void init()
{
    for(int i=1;i<=n+3;i++)
        for(int j=0;j<=20;j++)
            nxt[i][j]=n+2;
    for(int i=1;i<=n;i++)
    {
        while(top&&a[sta[top]]<a[i])
            nxt[sta[top]][0]=i,top--;
        sta[++top]=i;
    }
    for(int i=1;i<=n;i++)
        sum[i][0]=(nxt[i][0]-i)*a[i];
    for(int i=1;i<=20;i++)
    {
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            nxt[j][i]=nxt[nxt[j][i-1]][i-1];
            sum[j][i]=sum[j][i-1]+sum[nxt[j][i-1]][i-1];
        }
    }
}
int query(int l,int r)
{
    int ans=0;
    for(int i=20;i>=0;i--)
    {
        if(nxt[l][i]-1<=r)
        {
            ans+=sum[l][i];
            l=nxt[l][i];
        }
    }
    ans+=a[l]*(r-l+1);
    return ans;
}
signed main()
{
     ios::sync_with_stdio(0);
     cin.tie(0),cout.tie(0);
     cin>>n>>t;
     for(int i=1;i<=n;i++)
         cin>>a[i];
     init();
     int u,v;
    while(t--)
     {
         cin>>u>>v;
         l=1+(u^las)%n;
         q=1+(v^(las+1))%(n-l+1);
        las=query(l,l+q-1);
         cout<<las<<"\n";
    }
    return 0;
}
```

本题解借鉴了楼上几篇题解的思路，如有不足还请多多包涵。

---

## 作者：Belia (赞：1)

### 题意：

给定一个长度为 $n$ 的序列 $a$，有 $t$ 次查询。每次查询给定起始位置 $l$ 和长度 $q$，要求计算：

$$\sum_{i=l}^{l+q-1} \max_{j=l}^{i} a_j$$

即从 $l$ 开始到 $i$ 的最大值之和。查询强制在线：参数 $u,v$ 需解密：

- $l=1+(u \oplus lastans)%n$

- $q=1+(v \oplus (lastans+1))%(n-l+1)$

其中 $lastans$ 为上次查询的答案（初始为 $0$）。

### 思路：

我们利用**单调栈**做预处理——从右向左扫描序列，用单调栈维护每个元素右侧第一个更大元素的位置 $nxt_i$，若右侧没有更大元素，则 $nxt_i=n+1$。

接着我们使用**倍增数组**，其中：

- $to_{i,0}$：从 $i$ 开始下一跳位置（$nxt_i$）。

- $val_{i,0}$：从 $i$ 到 $nxt_i-1$ 的贡献值（$a_i \times (nxt_i-i)$）。

时间复杂度为 $\mathcal{O}((n+t) \log n)$，可轻松通过此题。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long//#define ll long long你值得拥有
using namespace std;
const int maxn=5e5+10,low=20;
ll n,t,u,v,a[maxn],nxt[maxn],to[maxn][low+1],val[maxn][low+1],ans;
stack <ll> st;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//cincout加速代码
	cin>>n>>t;
    for(ll i=1;i<=n;i++)
    cin>>a[i];
    for(ll i=n;i;i--)// 单调栈求nxt[i]（右侧第一个更大位置）
	{
        while(!st.empty()&&a[i]>=a[st.top()])
		st.pop();
        nxt[i]=st.empty()?n+1:st.top();
        st.push(i);
    }
    for(ll i=1;i<=n;i++)// 初始化倍增数组
    to[i][0]=nxt[i],val[i][0]=1ll*a[i]*(nxt[i]-i);
    for(ll j=1;j<=low;j++)// 构建倍增表
    for(ll i=1,p;i<=n;i++)
    p=to[i][j-1],to[i][j]=p>n?n+1:to[p][j-1],val[i][j]=val[i][j-1]+(p>n?0:val[p][j-1]);
    while(t--)
	{
		cin>>u>>v;
        ll l=1+(u^ans)%n,q=1+(v^(ans+1))%(n-l+1),r=l+q-1,res=0,x=l;
        for(ll j=low;j>=0;j--)// 倍增跳转累加贡献
        if(to[x][j]<=r)
        res+=val[x][j],x=to[x][j];
        res+=1ll*a[x]*(r-x+1),ans=res;// 剩余区间贡献 & 更新 lastans
        cout<<res<<endl;
    }
    return 0;
}
```
$\mathcal{Just}$ $\mathcal{so}$ $\mathcal{so}!$

---

