# 回転寿司

## 题目描述

给出一个有 $N$ 个点的环，环上各点有一个初始权值 $a_i$。

给出 $Q$ 个询问，每次询问给出一个区间 $[S_i,T_i]$ 和一个值 $A_i$，对于 $A_i$ 的变动定义如下（$S_i$ 可能会小于 $T_i$ 因为是**环形**）：
```cpp
for (int i=Si;i!=Ti%n+1;i=i%n+1) if(a[i]>Ai) swap(a[i],Ai);
```
对于每个询问，回答遍历完区间 $[S_i,T_i]$ 后 $A_i$ 的最终值。

注：我们按逆时针方向在环上编号，并规定 $[S_i,T_i]$ 为从位置编号为 $S_i$ 的点逆时针遍历至位置编号为 $T_i$ 的点所经过点的集合。

## 说明/提示

对于全部的数据，$1\leq N\leq 4\times 10^5$，$1\leq Q\leq 25000$，$1\leq a_i\leq 10^9$，$1\leq S_i,T_i\leq N$，$1\leq A_i\leq 10^9$。

子任务 1（5 分）：$N\leq 2000$，$Q\leq 2000$。

子任务 2（15 分）：$S_i=1$，$T_i=N$（$1\leq i\leq N$）。

子任务 3（80 分）：无额外限制。

# 题解

## 作者：louhao088 (赞：16)

一道分块好题。良心分块，不卡常，9 秒时限，好评。


------------


首先，我们考虑一下这个问题的弱化版，也是 JOI 的部分分，每次询问 $l=1,r=n$​​ 时该怎么做。很容易想到，由于每次都是从头到尾，如果其他值被替换了，最大值肯定也会被替换，如果最大值都不会换那么其他值肯定更不会换了。

于是我们可以拿优先队列来维护这个过程，每次最大值更给定值比较，若比他大，就输出最大值，否则就输出原值。时间复杂度 $O(n \log n)$ 。


------------


那么这就给我们一个启示，我们对整体修改时其实并不用知道每个人具体是多少，只需知道最大值是什么，考虑分块，我们对每个块维护一个优先队列，每次区间查找就相当于一个块一个块进行修改，每次弹出的值就是下一次的修改值。


------------


那么我们此时又发现了一个问题，就是当我们暴力修改零散块的时候，我们不知道每个值具体是什么。也就是说我们需要在较短时间内得出一个块中所有的值。根据题意我们能发现，每个数 $a_i$​ 与每次修改的操作较小 $x_i$​​ 交换，与每次修改操作 $x_i$​ 与较大的 $a_i$ 操作其实是等价的。我们完全可以利用刚才的方法进行修改。​

具体的，我们用小根堆维护每个块询问 $x_i$​​​ 。修改零散块时，我们暴力更新，把原来的值与堆顶比较，每次的较小值即为此元素的值，得到后更新块，再把它塞入优先队列。


------------

复杂度分析

当我们取块长为 $\sqrt n $ 时最优，时间复杂度 $O(n \sqrt n \log n)$ ，因为时限 9s，完全能过。


------------
短而又易懂的代码


```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
const int maxn=4e5+5,B=655;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
int n,m,t,id[maxn],L[B],R[B],a[maxn],l,r,x; 
priority_queue<int>q[B];
priority_queue<int,vector<int>,greater<int> >q2[B];
int rebuild(int g,int l,int r,int x)
{
	for(int i=L[g];i<=R[g];i++)
		q2[g].push(a[i]),a[i]=q2[g].top(),q2[g].pop();
	for(int i=l;i<=r;i++) if(a[i]>x) swap(x,a[i]);
	while(!q2[g].empty()) q2[g].pop();
	while(!q[g].empty()) q[g].pop();
	for(int i=L[g];i<=R[g];i++) q[g].push(a[i]); 
	return x;
}
int getans(int l,int r,int x)
{
	if(id[l]==id[r]) return rebuild(id[l],l,r,x);
	else
	{
		x=rebuild(id[l],l,R[id[l]],x);
		for(int i=id[l]+1;i<=id[r]-1;i++)
			q[i].push(x),q2[i].push(x),x=q[i].top(),q[i].pop();
		return rebuild(id[r],L[id[r]],r,x);
	}
		
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();t=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read(),id[i]=(i-1)/t+1;
	for(int i=1;i<=id[n];i++)
	{
		L[i]=R[i-1]+1,R[i]=min(n,i*t);
		for(int j=L[i];j<=R[i];j++) q[i].push(a[j]);
	}
	for(int i=1;i<=m;i++)
	{
		l=read(),r=read();x=read();
		if(l>r) printf("%d\n",getans(1,r,getans(l,n,x)));
		else printf("%d\n",getans(l,r,x));
	}
 	return 0;
}
```


---

## 作者：shenxinge (赞：10)

## 崩溃历程：

看到时间限制将近 $10s$ ，我的心情快乐的。

**~~(这不是 $ O(n* \sqrt{n} * log(n)) $ 都能够草过去~~**

看到这神奇的区间操作，我的心情是疑惑的。

想到每次只要找出最大的然后大根堆维护一下的时候，我的心情是生草的。

打完代码然后尝试调的时候被大数据卡到 $20s$ 没有跑出来的时候我的心情是绝望的。

~~最后偷偷开 $O(2)$ 过这道题目的时候我的内心是平静的。~~

## 解法介绍：

这道题目很明显的是他的操作是将从 $s_i$ 到 $t_i$ 的小值一个又一个地传递过去，直到最后一个大值使得后边的所有顾客都无法替换。

由此可以看出，最后弹出的永远都是**这一区间的最大值**。

**这时候我们尝试构造数据。**

如果我们有一种特殊数据使得 $s_i$ 永远为 $1$ , $t_i$ 永远为 $n$ 的数据，那么我们会很自然地想到用**堆**去动态维护这个序列的最大值。

由这组特性，我们可以想到优雅地暴力：**分块**。

我们可以考虑 **分块+堆** 来优雅地解决问题。。。

考虑块与块之间的处理，也就是**整块**的时候。

显然，整块的时候影响块内元素的只有插入的值和被弹出的最大值，而被弹出的最大值继承到下一个块内，以此类推，就可以完成块的处理与合并。

但块内暴力该如何处理呢？**（散块该如何处理）**

考虑如何重构，我们可以考虑到任何一盘寿司能够插进，与它插进的顺序没有任何的关系。也就是说： **插入值的顺序与最后的值没有任何关系。**

所以我们考虑暴力重构时，我们只要考虑插入的值就可以了。

显然的是，**当前位置的更新肯定是当前位置最小的。**

于是就自然得想到了**小根堆**动态维护暴力重构，从小到大维护原始序列（原始块），再压入大根堆中。

因为一位顾客的寿司可能会影响到后面顾客的寿司，所以我们可以把顾客的寿司看做转过来的寿司，也把他放到小根堆中。

**由于注意到题目拥有良好的对称性，我们既可以理解为寿司依次经过顾客，我们也可以理解为顾客经过了寿司。**

**~~（所以你可以近似的认为顾客把顾客吃了~~**

## 时间复杂度分析

我们对于整块操作，额外记下了插入的值，记录下来的寿司当做顾客，顾客当做寿司来执行操作，并用小根堆维护。每一操作的时间复杂度为 $O(L * logm)$ 。

我们取块长 $L=\sqrt{n}$ ,总的时间复杂度就是 $O(m\sqrt{n}(logn + logm ) $。

## 代码部分
```cpp
#include<bits/stdc++.h>
#define Debug if(false)
#define rnt register int
using namespace std;
const int maxn=400010,maxb=670;
inline int read()
{
	int x=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-f;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
int n,m,bs,mb,block[maxn],a[maxn];
inline int get(int x){return x+1>mb?1:x+1;} //循环 
struct Block
{
	int l,r;
	priority_queue<int,vector<int>,less<int> > que;
	priority_queue<int,vector<int>,greater<int> > tag; //只需要记录值
	inline int modify(int x) //块修改,从左往右扫这个块并把最大值弹出,人称暴力修改 
	{
		if(x>=que.top()) return x; //无法过去了
		int res=que.top();que.pop();
		que.push(x),tag.push(x);
		return res; //把最大的pop出去 
	}
	inline void rebuild() //重构，按最小取 
	{
		if(!tag.size()) return;
		for(rnt i=l;i<=r;i++) 
			if(tag.top()<a[i])
			{
				int tis=a[i];
				a[i]=tag.top(),tag.pop();
				tag.push(tis);
			}
	}
	inline void clear()
	{
		while(!tag.empty()) tag.pop();
		while(!que.empty()) que.pop();
	}
	inline int query(int x,int L,int R) //暴力重置 
	{
		rebuild(),clear();
		for(rnt i=L;i<=R;i++) if(a[i]>x) swap(a[i],x);
		for(rnt i=l;i<=r;i++) que.push(a[i]); 
		return x;
	}
}b[maxb];
inline void init_block() //基本操作 
{
	n=read(),m=read();
	bs=sqrt(n),mb=((n-1)/bs)+1;
	for(rnt i=1;i<=n;i++)
	{
		a[i]=read();
		block[i]=(i-1)/bs+1;
		b[block[i]].que.push(a[i]);
	}
	for(rnt i=1;i<=mb;i++) 
		b[i].l=bs*(i-1)+1,b[i].r=bs*i;
	b[mb].r=n;
}
signed main()
{
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	init_block();
	while(m--)
	{
		int s=read(),t=read(),p=read();
		Debug printf("block[%d]: %d block[%d]: %d\n",s,block[s],t,block[t]);
		if(block[s]==block[t]&&s<=t) //同一块中可以直接查询 
			printf("%d\n",b[block[s]].query(p,s,t));
		else //跳块，基本操作。 
		{
			p=b[block[s]].query(p,s,b[block[s]].r);
			int cur=get(block[s]);
			while(cur!=block[t]) 
				p=b[cur].modify(p),cur=get(cur);
			Debug cout << cur << endl;
			printf("%d\n",b[block[t]].query(p,b[block[t]].l,t));
		}
	}
	return 0;
}
```


---

## 作者：harryzhr (赞：7)

# [「JOISC 2016 Day 3」回转寿司](https://www.luogu.com.cn/problem/AT1832)

题意已经很简洁了，就不简化了（注意询问之间肯定是互相有影响的）。

首先 $5\ pts$ 的暴力是很好写的，直接按题意模拟即可。

区间操作肯定想到用数据结构维护，但是想一想线段树好像不太行，在加上这道题超级大时限。

那么我们需要优雅的暴力：**分块**

以 $\sqrt n$ 为大小分块，接下来考虑以下几个问题（分块算法的常见问题）：

1. 整块处理；
2. 整块之间合并；
3. 块内暴力。

## 整块处理

我们要完成 $modify1(A)$ ：将 $A$ 从左往右扫这个块，最后出去的时候得到的 $A'$。

理解一下题意（或者手模几组数据），发现就是找到一个第一个元素大于$A$的单调递增序列，第一个数替换为 $A$ ，剩下的数依次向右平移，最大的数被扔掉，赋值给 $A'$ （如果说的不是很清楚可以参考一下下面的图）。

那如果我们只考虑块内的数有哪些，不考虑相对位置的话，就变成把$A$丢进来，把最大的数扔掉并返回这个最大的数。

维护一个 $val$ 的大根堆即可。

## 整块之间合并

依次进行 $modify1(A)$ ，不断更新 $A$ 即可

## 块内暴力

这是这道题最大的难点，我们需要对整个块暴力重构，询问的边角部分再暴力模拟。

- 性质：插入的数的顺序对序列的值不影响。

也就是，若 $x>y$ ，先插入 $x$ 再插入 $y$ 和先插入 $y$ 再插入 $x$ 得到的序列是一样的。

结合下面的图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/beyvqltk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/i9a95i6l.png)

所以我们不需要管插入的顺序，只需要管插入的数就好了。

显然当前位置能选最小的肯定选最小的更新，用一个小根堆（ $tag$ ）维护即可。

更新过后因为自己会变成 $A'$ ，可能会更新到后面的数，要把自己加进小根堆。

总结一下：整块处理用大根堆维护，并记下来插入的数（打标记），块内暴力重构时把标记从小到大插入即可。

时间复杂度 $O(n\sqrt n\log n)$ 。


```cpp
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;
inline int read(){//快读
	int s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
	return s*f;
}
const int N=4e5+10,M=1005;
int a[N];
struct Block{
	int l,r;
	priority_queue<int> val;//大根堆维护数值
	priority_queue<int,vector<int>,greater<int> > tag;//小根堆维护要插入的标记
	inline int modify1(int x){
		if(x>=val.top())return x;//无法更新，跳过
		int ret=val.top();
		val.pop();tag.push(x);val.push(x);//更新最大值并打标记
		return ret;
	}
	inline void rebuild(){
		if(!tag.size())return;
		for(int i=l;i<=r;++i)
			if(tag.top()<a[i]){
				int t=a[i];
				a[i]=tag.top();//依次插入标记
				tag.pop();tag.push(t);
			}
	}
	inline int modify2(int x,int L,int R){
		rebuild();
		while(tag.size())tag.pop();
		while(val.size())val.pop();//清空
		for(int i=L;i<=R;++i)if(a[i]>x)swap(a[i],x);
		for(int i=l;i<=r;++i)val.push(a[i]);//暴力重构
		return x;
	}
}blk[M];
int n,q,pos[N],sz,tot;
inline int nxt(int x){return (x+1>tot)?1:x+1;}
int main(){ 
	n=read();q=read();
	sz=sqrt(n);tot=(n-1)/sz+1;//块的大小及块的个数
	for(int i=1;i<=n;++i)pos[i]=(i-1)/sz+1;
	for(int i=1;i<=tot;++i)blk[i].l=(i-1)*sz+1,blk[i].r=min(i*sz,n);
	for(int i=1;i<=n;++i){
		a[i]=read();
		blk[pos[i]].val.push(a[i]);
	}
	for(int i=1,l,r,A;i<=q;++i){
		l=read();r=read();A=read();
		if(pos[l]==pos[r]&&l<=r){
			printf("%d\n",blk[pos[l]].modify2(A,l,r));
			continue;
		}
		A=blk[pos[l]].modify2(A,l,blk[pos[l]].r);//边角暴力
		int cur=nxt(pos[l]);
		while(cur!=pos[r]){
			A=blk[cur].modify1(A);//整块
			cur=nxt(cur);
		}
		printf("%d\n",blk[pos[r]].modify2(A,blk[pos[r]].l,r));
	}
	return 0;
}
```

---

## 作者：Astatinear (赞：4)

又是一道满级性质题，第一次在分块里面打堆这种东西。

感觉做了一堆 $\texttt{Ynoi}$ 之后，还是啥也不会。

首先这种神奇题目，还有这个神级时限，没有很好的办法处理的时候，我们考虑对序列分块，设块长为 $B$。

环不用去管，纯粹就是懒得好好造数据，直接破开就可以了。

需要明确的一点是，如果一个数经过了一整块之后，那么这个数就会变成这个块的最大值。（前提是他变了。）

所以对于一个数在整块上的处理是比较简单的，维护一个大根堆，随时跟进这个块上有哪些数就行。然后操作的时候替换就可以了。

但是散块呢？

首先修改散块是非常简单的，就是暴力修。但是我们现在要思考的是如何去查询散块，因为你并没有在修改整块的时候跟进每个数的值。

我们仔细思考可以发现（？？？），对于两个数 $x,y$，你对一段序列进行操作时，无论你是先加 $x$，还是先加 $y$，他的结果是一样的，也就是说，最终结果与你加入数字的先后没有关系。

那这个问题就会方便很多，我们可以对于每个块维护一个小根堆，表示整个块当前加入了哪些数。可以发现，我们为了得到一个散块的具体值，在暴力重构的时候，如果我们按照小根堆的顺序进行加入时，我们就可以直接从左到右枚举块上的所有数，如果这个数大于小根堆的根，那就把这个根删掉，然后将这个数加入小根堆后，替换为这个根（正确性由替换条件 $a_i >x$ 和小根堆每次取出的根的单调性可得），就可以完美在 $B\times \log m$ 次操作下实现重构，从而做到查询散块。（当然重构结束之后，也理应更改大根堆的值，并清空这个小根堆）

总时间复杂度，整块由于存在替换，为 $\mathcal{O}(m\ \dfrac{n}{B}  \log B)$，散块暴力修改，为 $\mathcal{O}(mB)$，暴力重构复杂度为 $\mathcal{O}(mB\log m)$。


时限够大，$B=\sqrt{n}$ 绰绰有余。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 400005
int n, q, a[maxn];
int l[maxn], r[maxn], belong[maxn];
priority_queue<int> p1[705];
priority_queue<int, vector<int>, greater<int> > p2[705];
void init()
{
	int len = sqrt(n);
	for (int i = 1; i <= len; ++i)
	{
		l[i] = (i - 1) * len + 1, r[i] = i * len;
		for (int j = l[i]; j <= r[i]; ++j) belong[j] = i; 
	}
	if(len * len < n)
	{
		l[len + 1] = len * len + 1, r[len + 1] = n;
		++len;
		for (int j = l[len]; j <= n; ++j) belong[j] = len;
	}
	for (int i = 1; i <= len; ++i)
	{
		for (int j = l[i]; j <= r[i]; ++j)
		p1[i].push(a[j]);
	}
}
void rebuild(int p)
{
	if(p2[p].empty()) return;
	for (int i = l[p]; i <= r[p]; ++i)
	{
		if(a[i] > p2[p].top())
		{
			int x = p2[p].top(); p2[p].pop();
			p2[p].push(a[i]), a[i] = x;
		}
	}
	while(!p2[p].empty()) p2[p].pop();
}
int bruce(int p, int l, int r, int x)
{
	while(!p1[p].empty()) p1[p].pop();
	for (int i = l; i <= r; ++i) if(a[i] > x) swap(a[i], x);
	for (int i = ::l[p]; i <= ::r[p]; ++i) p1[p].push(a[i]);
	return x;
}
int query(int l, int r, int x)
{
	int p = belong[l], q = belong[r];
	rebuild(p), rebuild(q);
	if(p == q) return bruce(p, l, r, x);
	else
	{
		x = bruce(p, l, ::r[p], x);
		for (int i = p + 1; i < q; ++i)
		{
			int y = p1[i].top();
			if(y <= x) continue;
			p1[i].pop(), p1[i].push(x), p2[i].push(x);
			x = y;
		}
		return x = bruce(q, ::l[q], r, x);
	}
}
int main()
{
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	init();
	while(q--)
	{
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		int ans;
		if(l <= r) ans = query(l, r, x);
		else ans = query(l, n, x), ans = query(1, r, ans);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：ATZdhjeb (赞：4)

分块好题，细节不是很多，也不卡常，但是思路比较难想。

---

- ### 大致思路

这道题乍一看可能非常奇怪。首先它给了非常奇怪的 $9s$ 时限，然后它又给了一个更为奇怪的操作。观察这个操作，我们发现它似乎不满足 **下标上** 的交换律，即先操作 $l$ 到 $r_0$，再操作 $r_0 + 1$ 到 $r_1$ 和先操作 $r_0 + 1$ 到 $r_1$，再操作 $l$ 到 $r_0$ 的结果是不同的，因为它在前面下标的操作结果会影响到后面的。这样一来，我们很难用线段树之类 $\text{polylog}$ 级别的数据结构来维护它，因为这样很难满足它必须按顺序操作的性质。

但是，暴力模拟显然很好写，并且可以很方便地满足按顺序操作的性质，再联系到本题 $9s$ 的超大时限，于是我们不难想到用优雅的暴力——分块——来维护这种操作。

#### 1. 整块操作

既然要分块，就先思考怎样快速得出以及合并块内的答案。观察操作，我们发现它还有第二个性质，即每次操作遍历一整块后，$A$ 都会变成 $\max(A,\max\{a_i\})$，其中 $a_i$ 为块内每个数的权值。

> 证明：

> 若 $A \ge \max\{a_i\}$，那么 $A$ 显然不会变，得数仍是 $A$。

> 若 $ A < \max\{a_i\}$，那么 $A$ 在遍历到 $a_i$ 中第一个最大值之前，值都不会大于 $\max\{a_i\}$。于是它会在 $a_i$ 中第一个最大值处变为 $\max\{a_i\}$，此后没有一个 $a_i$ 满足 $a_i > A$，于是 $A$ 的最终值就是 $\max\{a_i\}$。

所以我们只需要对于每一个块维护出它的最大值，然后询问时按顺序扫过整块，对于每个块都令 $A \gets \max(A,\max\{a_i\})$ 即可。

#### 2. 散块操作

然后思考怎样处理散块中的询问。显然如果我们知道散块中每个数的值，那 我们就可以暴力模拟题意得出答案。但是注意到我们之前对整块操作时只关注了操作对 $A$ 的影响，而没有关注操作对每一个 $a_i$ 的影响，此时我们就难以知道每一个 $a_i$ 的值。

真的吗？

本题的操作还有一个性质，它 **虽然不对下标具有交换律，但是对操作的 $A$ 值有**。即对于同一个区间 $[l,r]$，先用值 $A_1$ 去修改一遍，再用值 $A_2$ 修改一遍，和先用 $A_2$ 修改，再用 $A_1$ 修改的结果是一样的。

> 证明：

> ~~自己画图，感性理解。~~

> 考虑我们现在用 $k$ 个 $A$ 值 $A_1,A_2,...,A_k$ 去更新同一段区间 $[l,r]$。对于一个 $l \le x \le r$，如果 $a_x \le \min_{j=1}^{k}\{A_j\}$，那么显然 $a_x$ 不会被修改。我们找到第一个会被修改的 $a_x$，那么无论它被以怎样的顺序修改，在它被最小的 $A$ 值修改之前，它的值恒大于 $\min\{A_j\}$。于是它在被最小的 $A$ 修改之后，它就会成为 $\min\{A_j\}$。然后从此以后没有一个 $A_j$ 满足 $A_j > a_x$，于是 $a_x$ 的最终值就是 $\min\{A_j\}$。

> 同理，我们类推至每一个 $a_x$，它最终的值都与被修改的顺序无关。

由上面的推导，我们可以考虑利用类似线段树懒标记的思想，对于每一块记录所有 **整体修改** 了它的 $A$ 值。当我们需要对这一块做散块询问时，我们直接暴力重构这一块。具体地，我们每次取出当前块最小的一个标记（即 $\min\{A_j\}$），用它来与第一个大于它的 $a_x$ 交换，直到换无可换为止。然后，我们就可以在散块中暴力模拟当前询问了。

至此，我们成功理出了分块解决本题的大致思路。

---

- ### 具体实现

#### 1. 整块操作的实现

我们对每一个块维护一个大根堆 $pq$，用来动态维护 $a_i$ 的最大值。同时维护一个小根堆 $tag$，用来记录对该块进行过整块操作的所有 $A$ 值。每次整块操作时取出 $pq$ 的堆顶元素与 $A$ 进行比较，如果 $pq$ 的堆顶大于 $A$，那么说明 $A$ 会对当前块进行修改，于是将 $A$ 丢进 $tag$ 里，然后交换 $A$ 和 $pq$ 堆顶的值。

#### 2. 块的重构的实现

我们从左到右扫描块内每一个 $a_x$，如果 $tag$ 的堆顶小于当前 $a_x$，那么将 $tag$ 堆顶与 $a_x$ 的值进行交换。最后清空 $tag$ 和 $pq$。

#### 3. 散块操作的实现

首先，我们重构当前散块。然后按题意模拟操作，得到本次操作后当前块每一个元素的值，然后重新把它们丢进 $pq$ 里。与此同时，我们也可以得到操作后 $A$ 的值。

当块长取 $\sqrt n$ 时，总时间复杂度最优秀，为 $O(n\sqrt n\log n)$，完全可以通过本题。

- ### 代码展示

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int input() {
	int x = 0,f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

int n,q,blo,nblo,x[400010];

struct Block {
	int l,r,a[700];
	priority_queue< int > val;
	priority_queue< int,vector<int>,greater<int> > tag;
	
	Block() {
		l = r = 0;
		memset(a,0,sizeof(a));
		val = priority_queue< int >();
		tag = priority_queue< int,vector<int>,greater<int> >();
	}
	
	void create(const int& L,const int& R) {
		l = L;
		r = R;
		for (int i = l; i <= r; ++i) val.push(a[i - l + 1] = x[i]);
	}
	
	void rebuild() {
		if (!tag.empty()) {
			for (int i = l; i <= r; ++i) if (a[i - l + 1] > tag.top()) {
				int temp = tag.top();
				tag.pop();
				swap(temp,a[i - l + 1]);
				tag.push(temp);
			}
			tag = priority_queue< int,vector<int>,greater<int> >();
		}
	}
	
	void query(int& A) {
		if (A < val.top()) {
			int temp = val.top();
			val.pop();
			swap(temp,A);
			val.push(temp);
			tag.push(temp);
		}
	}
}b[700];

void solve(const int& l,const int& r,int& A) {
	int lid = (l + blo - 1) / blo,rid = (r + blo - 1) / blo;
	if (lid == rid) {
		b[lid].rebuild();
		b[lid].val = priority_queue< int >();
		for (int i = l; i <= r; ++i) if (b[lid].a[i - b[lid].l + 1] > A) swap(A,b[lid].a[i - b[lid].l + 1]);
		for (int i = b[lid].l; i <= b[rid].r; ++i) b[lid].val.push(b[lid].a[i - b[lid].l + 1]);
	} else {
		b[lid].rebuild();
		b[lid].val = priority_queue< int >();
		for (int i = l; i <= b[lid].r; ++i) if (b[lid].a[i - b[lid].l + 1] > A) swap(A,b[lid].a[i - b[lid].l + 1]);
		for (int i = b[lid].l; i <= b[lid].r; ++i) b[lid].val.push(b[lid].a[i - b[lid].l + 1]);
		for (int i = lid + 1; i < rid; ++i) b[i].query(A);
		b[rid].rebuild();
		b[rid].val = priority_queue< int >();
		for (int i = b[rid].l; i <= r; ++i) if (b[rid].a[i - b[rid].l + 1] > A) swap(A,b[rid].a[i - b[rid].l + 1]);
		for (int i = b[rid].l; i <= b[rid].r; ++i) b[rid].val.push(b[rid].a[i - b[rid].l + 1]);
	}
}

int main() {
	n = input();
	q = input();
	for (int i = 1; i <= n; ++i) x[i] = input();
	blo = sqrt(n);
	nblo = (n + blo - 1) / blo;
	for (int i = 1; i <= nblo; ++i) b[i].create((i - 1) * blo + 1,min(n,i * blo));
	for (int i = 1; i <= q; ++i) {
		int l = input(),r = input(),A = input();
		if (l <= r) {
			solve(l,r,A);
			printf("%d\n",A);
		} else {
			solve(l,n,A);
			solve(1,r,A);
			printf("%d\n",A);
		}
	}
	return 0;
}
```

---

## 作者：MinimumSpanningTree (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_joisc2016_h)

由于这题是修改与查询操作，所以可以考虑用分块维护。

这题的序列虽然是一个环，但是我们无须理会，可以当成普通序列来做，只需要在 $l>r$ 的时候拆成两部分来跑就行。

对于每次分块操作，分为左右两端的散块和中间的整块，下面讲解两种情况分别如何处理。

### 整块处理

因为 $A_i$ 一遇到比它大的数就和它交换，所以 $A_i$ 经过交换后的数一定是原来 $A_i$ 的值与整块中的数的最大值。但是因为有多个查询，之前的 $A_i$ 来这个块跑过，这个块的最大值就可能变了，所以可以使用单调队列，每个块维护一个大根堆。$A_i$ 要和当前这个块做交换操作时把 $A_i$ 丢进去再取堆顶就可以了。

### 散块处理（本题难点）

上面的整块处理仅仅维护了块内数的堆，所以通过堆，经过修改的块内数只能知道有什么数，无法知道到底是什么顺序，这样的话就影响到散块了。有没有什么办法能复原散块的顺序呢？

块内的数在正常情况下是不会被改变的，如果被改变了，那一定是前面整块时的 $A_i$ 导致的。前面这么多次修改，怎么知道最终被换成了哪个数呢？可以想到，只要每次遇到比自己小的 $A_i$，就要和它交换。所以如果被修改过的话，最终一定被修改成了最小的那个数。这个地方的处理方式挺巧妙的，方法是优先队列每个块维护一个小根堆，存储这个块所有曾经整块处理时的 $A_i$，它们遍历交换时都有可能修改块内的数，所以我们整块处理的时候就可以先把 $A_i$ 入队了。散块处理的时候，遍历块内所有数，我们不知道当前这个数会不会被修改，所以就直接把数丢进小根堆里，再取最小的出来就是修改后的数。不会被修改的话，说明没有小于它的 $A_i$，取出来的自然还是原来的数。如果会被修改，取出来的是最小的 $A_i$ 也就是最终被修改成的数，同时该数原来的值也被留在了队列内，就完美地完成了该数与修改它的 $A_i$ 的交换操作。

实现的细节可以看看代码和注释。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
const int N=4e5+100,M=1100;
int n,q,block,nk,st[M],ed[M],p[N],a[N],l,r,num;
priority_queue<int> q1[M];//大根堆，维护整块最大值
priority_queue<int,vector<int>,greater<int> > q2[M];//小根堆，维护会影响散块的x 
void build()//预处理 
{
	block=sqrt(n);
	nk=n/block;
	if(n%block!=0) nk++;
	for(int i=1;i<=nk;i++) st[i]=(i-1)*block+1,ed[i]=st[i]+block-1;
	ed[nk]=n;
	for(int i=1;i<=n;i++) 
	{
		p[i]=(i-1)/block+1;
		q1[p[i]].push(a[i]);
	}
}
int update(int k,int ql,int qr,int x)//处理散块（排好顺序+交换更新x值） 
{
	for(int i=st[k];i<=ed[k];i++)//排好这个块的顺序（复原这个块）
	{
		//将原来的数丢进去，如果遇到了更小的数说明a[i]与前面的x交换了
		q2[k].push(a[i]); 
		a[i]=q2[k].top(),q2[k].pop();
	}
	for(int i=ql;i<=qr;i++)//由于是散块，直接遍历交换更新x的值 
	{
		if(a[i]>x) swap(x,a[i]);
	}
	while(!q2[k].empty()) q2[k].pop();//已将块k更新成最新状态，没有x可以影响它了，清空 
	//由于受到x交换的影响，接下来要更新存储块k的堆
	while(!q1[k].empty()) q1[k].pop(); 
	for(int i=st[k];i<=ed[k];i++) q1[k].push(a[i]);
	return x; 
}
int query(int ql,int qr,int x)//分块处理查询
{
	if(p[ql]==p[qr]) return update(p[ql],ql,qr,x);//处于同一块，直接处理
	x=update(p[ql],ql,ed[p[ql]],x);//处理左边散块
	for(int i=p[ql]+1;i<=p[qr]-1;i++)//处理中间整块 
	{
		q1[i].push(x);
		q2[i].push(x);//此整块处理会影响后面i块处理散块时的顺序，存进小根堆 
		x=q1[i].top(),q1[i].pop();//更新x的值 
	}
	return update(p[qr],st[p[qr]],qr,x);//处理右边散块 
} 
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build();
	while(q--)
	{
		scanf("%d%d%d",&l,&r,&num);
		if(l<=r) printf("%d\n",query(l,r,num));
		else printf("%d\n",query(1,r,query(l,n,num)));//是一个环，所以在n~1之间连和的情况时，可直接拆成两半做 
	}
	return 0;
} 
```

---

## 作者：harmis_yz (赞：2)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

## 分析
注意到不正常的时限。考虑分块做法。

对于一个区间 $[l,r]$ 与当前的 $x$。$x$ 遍历完这个区间之后一定会成为 $\max(\max\limits_{i=l}^{r}a_i,x)$。看出这个不难。那么，我们对于每个块动态维护其最大值，就能得到 $x$ 最终的值了。

现在考虑修改。记 $j$ 为区间 $[l_i,r_i]$ 中第一个比 $x$ 大的位置。那么 $[j,r_i]$ 一定程不降的形式，因为一但有一个 $a_k >a_{k+1}$，我们都会通过 $x$ 将其排好。那么对于 $[l_r,j)$ 中的值，能够保证 $\forall k\in[l_i,j),a_k<a_j$。因为 $a_k\le x\land a_j >x$。于是就好做了，我们能够通过维护前缀最小值得到 $a_i$ 的值。形式化地，对于每次将最大值与 $x$ 比较时，先将 $x$ 加入队列。对于每个 $i$，将 $a_i$ 加入队列。然后每次 $a_i$ 的实际值为当前最小的值。

证明简单。如果 $x$ 存在 $x<a_j$ 的情况，那么 $Max$ 将会被顶出来。如果不存在，那么 $x$ 将会成为最后一个（这里的最后一个不一定是队列的最后一个，因为可能存在多个这样的 $x$）。

动态维护最大和最小值，使用优先队列即可。时间复杂度 $O(q\sqrt{n}\log n)$。$9$ 秒足够了。

## 代码

```cpp
il void rebuild(int k){
	for(re int i=L(k);i<=R(k);++i){
		q[k].push(a[i]);
		a[i]=q[k].top();
		q[k].pop();
	}
	while(!q[k].empty()) q[k].pop();
	while(!qu[k].empty()) qu[k].pop();
	return ;
}
il int query(int l,int r,int x){
	int bl=id(l),br=id(r);
	if(bl==br){
		rebuild(bl);
		for(re int i=l;i<=r;++i)
			if(a[i]>x) swap(x,a[i]);
		for(re int i=L(bl);i<=R(bl);++i) qu[bl].push(a[i]);
		return x;
	}
	rebuild(bl);
	for(re int i=l;i<=R(bl);++i)
		if(a[i]>x) swap(x,a[i]);
	for(re int i=L(bl);i<=R(bl);++i) qu[bl].push(a[i]);
	for(re int i=bl+1;i<br;++i){
		qu[i].push(x),q[i].push(x);
		x=qu[i].top();
		qu[i].pop();
	}
	rebuild(br);
	for(re int i=L(br);i<=r;++i)
		if(a[i]>x) swap(x,a[i]);
	for(re int i=L(br);i<=R(br);++i) qu[br].push(a[i]);
	return x;
}

il void solve(){
	n=rd,m=rd,len=sqrt(n);
	for(re int i=1;i<=n;++i){
		a[i]=rd;
		qu[id(i)].push(a[i]);
	}
	while(m--){
		int l=rd,r=rd,x=rd;
		if(l<=r) printf("%lld\n",query(l,r,x));
		else printf("%lld\n",query(1,r,query(l,n,x)));
	}
    return ;
}
```

---

## 作者：LiangE (赞：2)

# 题解：AT_joisc2016_h 回転寿司
（这是我的第一篇题解，如有瑕疵还请多多包涵，欢迎在评论区或私信中指出【玫瑰】【玫瑰】【玫瑰】）

---

## 题目大意：
给定一个含有 $N$ 个点的环（点有点权），$Q$ 次事件（修改+询问）。求每次询问的结果。


---
  

## 思路：

  首先考虑，如果只用最暴力的算法该怎么做？  
  
  很明显，直接从每次询问的 $l$ 枚举到 $r$，过程中修改序列，最后输出答案 $x$。明显地，我们的时间会爆掉。  
  
  考虑进一步的优化。  
  
  实际上，我们可以将环视为一个序列进行分块。同时，给每个块都配备一个大根堆。这样操作，当询问区间包含到某个整的块时，就可以直接找到这个整块的答案。
  
  紧接着，并不是所有的询问都恰好包含几个块。并且，对于这些“零散”的块，我们无法直接使用优先队列求得答案。那就退而求其次——直接一个一个枚举。
  
  以这样的思路，再加上一些细节——恭喜你，又 AC 一道黑题。

---

### 有关下文部分代码的解释：
- **为什么会有两个优先队列？**

  当我们直接通过大根堆获取某个整块的答案时，无法确定当前块里的信息，当这个整块（的一部分）以散块的形式出现时，就会出现错误。（毕竟处理散块需要明确的信息） 

  那么，在我们维护每个块的队列时，如何**优雅的**确保其数据的正确性？  

  对于每一个被询问到的整块，使用另一个堆，来存储这次的 $x$。当这个整块（的一部分）以散块的形式出现时，以堆中储存的信息对序列进行这次询问的预处理。这样就可以不受影响地处理每一次询问了。  
  
值得注意的是，该堆里的 $x$ 是“上一次用剩下的”，也就是说，$x$ 已经“名义上”参与过比较大小值的过程，也就是说，当前的块里的数据（不妨理解为最大值）是尽可能小的。如果使用一个小根堆来维护这些数据，那么对于询问预处理的实现就会方便很多。


---



### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
const int M=635; 
int maxn;
int n,q;
int a[N];
int id[N];
int L[M],R[M];
priority_queue<int,vector<int>,less<int> >q1[M];
priority_queue<int,vector<int>,greater<int> >q2[M];

int solve_part(int z,int l,int r,int x){
	//询问预处理 
	for(int i=L[z];i<=R[z];i++){
		q2[z].push(a[i]);
		a[i]=q2[z].top();
		q2[z].pop();
	}
	//直接暴力枚举 
	for(int i=l;i<=r;i++) if(a[i]>x) swap(a[i],x);
	//重装队列 
	while(!q1[z].empty()) q1[z].pop();
	while(!q2[z].empty()) q2[z].pop();
	for(int i=L[z];i<=R[z];i++) q1[z].push(a[i]);
	return x;
}
int solve_whole(int l,int r,int x){
	if(id[l]!=id[r]){
		//最前 [ l , R[id[l]] ] 的散块 
		x=solve_part(id[l],l,R[id[l]],x);
		//中间 [ id[l]+1 , id[r]-1 ] 的整块（如有   
		for(int i=id[l]+1;i<=id[r]-1;i++){
			q1[i].push(x);
			q2[i].push(x);
			x=q1[i].top();
			q1[i].pop();
		}
		//最后 [ L[id[r]] , r ] 的散块 
		x=solve_part(id[r],L[id[r]],r,x);
	}
	else x=solve_part(id[l],l,r,x);
	return x;
}
int main(){
	scanf("%d%d",&n,&q);
	maxn=sqrt(n);
	for(int i=1;i<=n;i++) id[i]=(i-1)/maxn+1;
	for(int i=1;i<=id[n];i++){
		L[i]=R[i-1]+1;
		R[i]=min(L[i]+maxn-1,n);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		q1[id[i]].push(a[i]);
	}
	for(int i=1;i<=q;i++){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		if(l<=r) x=solve_whole(l,r,x);
		else{
			x=solve_whole(l,n,x);
			x=solve_whole(1,r,x);
		}
		printf("%d\n",x);
	}
	return 0;
} 
```

---

## 作者：_Yonder_ (赞：1)

看到这么大的时间范围，首先考虑分块。

每次的查询中，散块绝对是最好处理的，那么整块怎么弄标记呢？我们得先证明查询的顺序对最后的 $a$ 序列是否有影响。

令两次查询区间相同的的 $A_i$ 分别为 $x,y$。

当 $x<y$ 时，我们先执行 $y$ 查询，然后执行 $x$ 查询。我们可以发现 $x$ 查询修改过的 $a_i$ 都是 $y$ 查询修改过的，就相当于依次加入了 $x,y$ 后，将修改过的 $a_i$ 全部后移两次再删掉后面两个 $a_i$。这是与先执行 $x$ 查询后的 $a$ 序列相同的。

当 $x>y$ 时证明同上。

所以查询的顺序对最后的 $a$ 序列没有影响。

那么我们就可以考虑用堆维护标记了。对于整块查询，用小顶堆维护标记(你问我为什么用小顶堆？看上面证明的过程)，用大顶堆维护块内最大值，这题就弄完啦。

时间复杂度 $O(n \sqrt n\log n)$。
# Code
```
#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
static char buf[4500000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,4500000,stdin),p1==p2)?EOF:*p1++
#endif
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=x*10+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
#define ll long long
using namespace std;
const int N=4e5+5,M=635;
int n,q,a[N],l,r,x,Sqrt,len,L[N],R[N],id[N];
priority_queue<int,vector<int>,greater<int>> t[M];
priority_queue<int> b[M];
inline void Build(){
	Sqrt=sqrt(n),len=n/Sqrt;
	for(register int i=1;i<=len;i++) L[i]=R[i-1]+1,R[i]=i*Sqrt;
	if(R[len]^n) len++,L[len]=R[len-1]+1,R[len]=n;
	for(register int i=1,ID=1;i<=n;i++) b[id[i]=ID].push(a[i]),ID+=i==R[ID];
}inline int reset(int x,int l,int r,int c){
    if(l==L[x]&&r==R[x]){b[x].push(c),t[x].push(c),c=b[x].top(),b[x].pop();return c;}//这句if判断将常数严格控制在了3。
	for(register int i=L[x];i<=R[x];i++) t[x].push(a[i]),a[i]=t[x].top(),t[x].pop();
	for(register int i=l;i<=r;i++) if(a[i]>c) swap(a[i],c);
	while(t[x].size()) t[x].pop();while(b[x].size()) b[x].pop();
	for(register int i=L[x];i<=R[x];i++) b[x].push(a[i]);
	return c;
}inline int Query(int l,int r,int x){
	if(id[l]==id[r]) return reset(id[l],l,r,x);x=reset(id[l],l,R[id[l]],x);
	for(register int i=id[l]+1;i<id[r];i++) b[i].push(x),t[i].push(x),x=b[i].top(),b[i].pop();
	return reset(id[r],L[id[r]],r,x);
}
int main(){
	read(n),read(q);
	for(register int i=1;i<=n;i++) read(a[i]);Build();
	while(q--){
		read(l),read(r),read(x);
		if(l<=r) write(Query(l,r,x));
		else write(Query(1,r,Query(l,n,x)));
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：1)

题意大概是这样，「每次操作选出区间中的一个 LIS（strictly），满足其开端是极靠近左端点且大于 $A$ 的位置，答案即这个 LIS 的末尾，做一个轮换后弹出序列末端」。

首先做几个观察。

> **Observation 1**：每次被弹出的都是区间最大值。

证明：显然，你考虑有一个最大的值在钦定的 LIS 的前或后，都会被先行选择 / 扩展进来。

> **Observation 2**（key observation）：如果对一个区间插入若干个值，插入顺序不影响最终序列的长相。

证明：每次插入进去的值不可能成为序列的最大值，所以弹出的数固定。并且插入进的数是根据严格偏序关系插进去的，所以顺序不影响长相。

仅凭以上两个观察，此题的奇怪操作怎么看也不像是个 ${\rm polylog}$，选择对序列做 Sqrt Decomposition，接下来我们探讨整块间的处理方式和散块的做法，因为操作的特殊性我们并不需要做 8 种情况的伞兵讨论。

- 整块间：你考虑每个整块上维护一个大根堆，然后整块的后继继承该整块的最大值，该整块去除其最大值即可；
- 散块：把所有需要插入的元素存一个懒标在右边散块放出来，因为 Observation 2，我们贪心优先把值较小的懒标放出去即可。

```cpp
#include <bits/stdc++.h>
template <class T> inline void chmax(T& a, const T b) { a = a > b ? a : b; }
template <class T> inline void chmin(T& a, const T b) { a = a < b ? a : b; }
inline long long rd() {
  long long x = 0; bool f = 0; char ch = getchar();
  while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
  while (ch >= '0' && ch <= '9') x = x * 10 + (ch & 15), ch = getchar();
  return f ? -x : x;
}
/** @brief
 * 选出一个 LIS，满足开始是极靠近 l 的大于 A 的位置，答案即序列的末端，然后用 A 替换序列开头，做一个轮换，弹出序列末端
 * Observation 1：每次被弹出的都是区间最大值
 * Trick：序列分块
 * Section 1：整块
   * 整块上维护一个堆，整块间下一块继承上一块的最大值
 * Section 2：散块
   * 维护一个小根堆，每次散块暴力重构
 * key observation：插入顺序不影响序列的长相
*/
constexpr int BS = 650;
int n, m, a[400100], pos[400100];
int L[660], R[660];
std::priority_queue<int> max[660];
std::priority_queue<int, std::vector<int>, std::greater<int>> tag[660];
void push(int i, int x) { max[i].emplace(x); }
void setBound(int i) { L[i] = (i - 1) * BS + 1, R[i] = i * BS; }
int Qry(int i, int l, int r, int x) {
  if (tag[i].size()) {
    for (int j = L[i]; j <= R[i]; ++j)
      if (int t = a[j]; tag[i].top() < t)
        a[j] = tag[i].top(), tag[i].pop(), tag[i].emplace(t);
  }
  while (max[i].size()) max[i].pop();
  while (tag[i].size()) tag[i].pop();
  for (int j = l; j <= r; ++j)
    if (a[j] > x) std::swap(a[j], x);
  for (int f = L[i]; f <= R[i]; ++f) push(pos[L[i]], a[f]);
  return x;
}
int Mdf(int i, int x) {
  if (x >= max[i].top()) return x;
  int res = max[i].top(); max[i].pop();
  max[i].emplace(x), tag[i].emplace(x);
  return res;
}
signed main() {
  n = rd(), m = rd();
  for (int i = 1; i <= n; ++i)
    push(pos[i] = (i - 1) / BS + 1, a[i] = rd());
  for (int i = 1; i <= pos[n]; ++i) setBound(i);
  R[pos[n]] = n;
  for (int l, r, a; m--;) {
    l = rd(), r = rd(), a = rd();
    if (pos[l] == pos[r] && l <= r) printf("%d\n", Qry(pos[l], l, r, a));
    else {
      a = Qry(pos[l], l, R[pos[l]], a);
      for (int u = pos[l] + 1 > pos[n] ? 1 : pos[l] + 1; u != pos[r]; u = u + 1 > pos[n] ? 1 : u + 1)
        a = Mdf(u, a);
      printf("%d\n", Qry(pos[r], L[pos[r]], r, a));
    }
  }
  return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

神题。。。

首先，我们发现一次询问最后的答案肯定为 $[l,r]$ 的**最大值**。

那么我们就考虑分块，我们可以为每个块都维护一个大根堆，遇到一个块时，就将当前 $A$ 加入当前块的堆，然后将 $A$ 设为堆内最大值并弹出它。

然后我们就发现这样的操作是维护不了所有数的顺序的，因此只适用于整块。

那么散块呢？

我们发现，在 $A$ 的视角下：我们可以视为 $A_j$ 与较小的 $a_i$ 交换，那么我们就可以同时为每个块再维护一个小根堆代表块内询问的数，每次直接暴力重构堆即可。

我们注意到这样单次操作复杂度是 $O(\frac{n}{B}\log n+B\log n)$，取 $B$ 为 $\sqrt{n}$ 时平衡，总时间复杂度为 $O(n\log n+q\sqrt{n}\log n)$，看似跑不过，实测时间 $9$ 秒可以跑过。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=4e5+5,B=666;
int n,m,block,belong[N],L[B],R[B],a[N];
priority_queue<int,vector<int>,less<int>> qp[B];
priority_queue<int,vector<int>,greater<int>> qp2[B];

int bl(int A,int l,int r,int x){
	for(int i=L[A];i<=R[A];i++){
		qp2[A].push(a[i]);
		a[i]=qp2[A].top();
		qp2[A].pop();
	}
	for(int i=l;i<=r;i++) if(a[i]>x) swap(a[i],x);
	while(!qp[A].empty()) qp[A].pop();
	while(!qp2[A].empty()) qp2[A].pop();
	for(int i=L[A];i<=R[A];i++) qp[A].push(a[i]); 
	return x;
}

int query(int l,int r,int x){
	if(belong[l]==belong[r]) return bl(belong[l],l,r,x);
	else{
		x=bl(belong[l],l,R[belong[l]],x);
		for(int i=belong[l]+1;i<=belong[r]-1;i++) qp[i].push(x),qp2[i].push(x),x=qp[i].top(),qp[i].pop();
		return bl(belong[r],L[belong[r]],r,x);
	}
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;block=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		belong[i]=ceil(1.0*i/block);
	}
	for(int i=1;i<=belong[n];i++){
		L[i]=R[i-1]+1,R[i]=i*block;
		for(int j=L[i];j<=R[i];j++) qp[i].push(a[j]);
	}
	R[belong[n]]=n;
	while(m--){
		int l,r,x;
		cin>>l>>r>>x;
		if(l>r) cout<<query(1,r,query(l,n,x))<<endl;
		else cout<<query(l,r,x)<<endl;
	}
	return 0;
}
```

---

## 作者：Basori_Tiara (赞：0)

好多题都叫这个名字啊。

考虑这个环除了恶心你一点用也没有，我们把他变成序列，看怎么解决序列。

然后你惊喜地发现询问次数居然只有 $25000$，大胆猜测是分块然后内部用数据结构来维护。

这个东西有一个显而易见的结论那就是如果这个块可能被替换那么最后一定是最大值被换出去。

而考虑我们以一个 $A=0$ 扫一遍整个块会得到这样一个东西：

![](https://pic.imgdb.cn/item/654cc37dc458853aef7b7ba3.jpg)

容易发现无论 $A$ 的值是什么都没有办法触及那些红色的权值，只能换蓝色的权值。

我们考虑把一个块当作一个集合，集合的值是确定的——因为我们知道要把最大值拿出来再把现在手上的 $A$ 丢进去就可以了，用一个堆就能维护，但是区间操作也意味着我们需要复原散块，只知道集合是不太行的，我们考虑怎么把集合拿来复原散块。

我们考虑一个点会被拿走当且仅当什么？当且仅当他被一个更小的东西干掉了，所以我们先把集合内的点从小到大排序一下，考虑如果一个点他是从上次重构开始就在块里面的，就从那个位置开始找到第一个还没放过的位置放下，否则就从块的开头开始找到第一个还没放过的位置放下。


这个为什么是对的，因为如果一个点的位置已经被占领了，那么就说明在他前面有一个点插入进来然后换了一大摞最后来到这里停下，在实际操作中就是这个点通过若干次操作把当前这个点给换出来了，那我们就要作为一个换点的人找到下一个能换出我的位置，也就是下一个空位，因为空位的原本的权值一定是能被我们换出来的，而新插入的点是从起点开始遍历整个块的，所以他的所谓的原本位置就是块的起点。

这样我们就能够重构一个块，我们现在既能维护整块集合内的取值，又能重构维护散块内的取值，我们也就可以做出这整个题了，时间复杂度是 $Q\sqrt n \log\sqrt n$ 的，实测三秒就能跑完。

模拟赛的时候脑子一热没写堆写的 WBLT。。

下面这一版是堆版本。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[400005];
int father[400005];
int find(int x){
   if(father[x]==x)return x;
   return father[x]=find(father[x]);
}
class SqrtSolve{
   public:
   int id[400005];
   int len[400005];
   int st[400005];
   int ed[400005];
   int belone[400005];
   int block;
   struct node{
      int val;
      int Whe;
      bool friend operator < (const node &a,const node &b){
         return a.val<b.val;
      }
   };
   priority_queue<node> P[400005];
   void Makea(int i){
      for(int j=st[i];j<=ed[i]+1;j++){
         father[j]=j;
      }
      stack<node> stk;
      while(!P[i].empty()){
         node tmp=P[i].top();
         P[i].pop();
         stk.push(tmp);
      }
      while(!stk.empty()){
         node tmp=stk.top();
         stk.pop();
         if(tmp.Whe==0){
            a[find(st[i])]=tmp.val;
            father[find(st[i])]=find(st[i])+1;
         }
         else{
            a[find(tmp.Whe)]=tmp.val;
            father[find(tmp.Whe)]=find(tmp.Whe)+1;
         }
      }
      return;
   }
   void MakeWBLT(int i){
      for(int j=st[i];j<=ed[i];j++){
         P[i].push(node{a[j],j});
      }
      return;
   }
   void build(){
      block=sqrt(n);
      for(int i=1;i<=block;i++){
         st[i]=(i-1)*block+1;
         ed[i]=i*block;
      }
      if(block*block<n){
         st[block+1]=block*block+1;
         ed[block+1]=n;
         block++;
      }
      for(int i=1;i<=block;i++){
         for(int j=st[i];j<=ed[i];j++){
            belone[j]=i;
         }
      }
      for(int i=1;i<=block;i++)MakeWBLT(i);
      return;
   }
   int solve(int lt,int rt,int A){
      if(lt>rt)return A;
      for(int i=lt;i<=rt;i++){
         int tmp=P[i].top().val;
         if(tmp<=A)continue;
         P[i].pop();
         P[i].push(node{A,0});
         A=tmp;
      }
      return A;
   }
}Q;
int main(){
   scanf("%d%d",&n,&q);
   for(int i=1;i<=n;i++){
      scanf("%d",&a[i]);
   }
   Q.build();
   while(q--){
      int lt,rt,A;
      scanf("%d%d%d",&lt,&rt,&A);
      int st=Q.belone[lt],ed=Q.belone[rt];
      if(lt<=rt){
         if(st==ed){
            Q.Makea(st);
            for(int i=lt;i<=rt;i++){
               if(A<a[i])swap(a[i],A);
            }
            Q.MakeWBLT(st);
            printf("%d\n",A);
         }
         else {
            Q.Makea(st);
            for(int i=lt;i<=Q.ed[st];i++){
               if(A<a[i])swap(a[i],A);
            }
            A=Q.solve(st+1,ed-1,A);
            Q.Makea(ed);
            for(int i=Q.st[ed];i<=rt;i++){
               if(A<a[i])swap(a[i],A);
            }
            Q.MakeWBLT(st);
            Q.MakeWBLT(ed);
            printf("%d\n",A);
         }
      }
      else{
         Q.Makea(st);
         for(int i=lt;i<=Q.ed[st];i++){
            if(a[i]>A)swap(A,a[i]);
         }
         int tmp=Q.solve(st+1,Q.block,A);
         A=Q.solve(1,ed-1,tmp);
         if(st^ed)Q.Makea(ed);
         for(int i=Q.st[ed];i<=rt;i++){
            if(a[i]>A)swap(A,a[i]);
            // printf("%d %d\n",i,a[i]);
         }
         printf("%d\n",A);
         Q.MakeWBLT(st);
         if(st^ed)Q.MakeWBLT(ed);
      }
   }
   return 0;
}
```

---

## 作者：xfrvq (赞：0)

以下集合指可重集。设集合 $S$，一次操作 $x$ 会让 $x$ 替换掉 $S\cap\{x\}$ 中最大值。如果有多次操作，设 $O=\{x\}$，$S'$ 即为 $O\cup S$ 的前 $|S|$ 小值。

考虑分块，先解决操作覆盖整块的情况：设每个块集合 $S_i$，依次遍历每个块，用 $x$ 替换原 $S_i$ 最大值，大根堆维护 $S_i$。

考虑散块情况，需要解决：还原块的每个位置。仅凭 $S_i$ 无法做到，设 $O_i$ 为：对块 $i$ 做了整块操作的 $x$ 构成集合。还原时依次枚举块中位置，用 $a_j$ 替换 $O_i\cap\{a_j\}$ 中最小值。用小根堆维护 $O_i$。散块修改按题意模拟就行。

复杂度 $O(n\log n+q\sqrt n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5,SQ = 650;

int n,q,a[N],B,C,bl[N],st[SQ],ed[SQ];
priority_queue<int> Q[SQ];
priority_queue<int,vector<int>,greater<int>> O[SQ];

void sol(int l,int r,int &x){
	int i = bl[l];
	for(int j = st[i];j <= ed[i];++j) O[i].push(a[j]),a[j] = O[i].top(),O[i].pop();
	for(;O[i].size();O[i].pop());
	for(int j = l;j <= r;++j) if(a[j] > x) swap(x,a[j]);
	for(;Q[i].size();Q[i].pop());
	for(int j = st[i];j <= ed[i];++j) Q[i].push(a[j]);
}

int main(){
	scanf("%d%d",&n,&q),B = sqrt(n),C = (n - 1) / B + 1;
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	for(int i = 1;i <= C;++i){
		st[i] = ed[i - 1] + 1,ed[i] = i == C ? n : st[i] + B - 1;
		for(int j = st[i];j <= ed[i];++j) bl[j] = i,Q[i].push(a[j]);
	}
	for(int l,r,x;q--;){
		scanf("%d%d%d",&l,&r,&x);
		if(bl[l] == bl[r] && l <= r) sol(l,r,x);
		else {
			sol(l,ed[bl[l]],x);
			for(int j = bl[l] % C + 1;j != bl[r];j = j % C + 1)
				O[j].push(x),Q[j].push(x),x = Q[j].top(),Q[j].pop();
			sol(st[bl[r]],r,x);
		}
		printf("%d\n",x);
	}
	return 0;
}
```

---

