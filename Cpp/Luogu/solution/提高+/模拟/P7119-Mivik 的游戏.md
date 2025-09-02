# Mivik 的游戏

## 题目背景

Mivik 和 W!ʌ!k 在玩游戏！

## 题目描述

Mivik 首先把 $n$ 枚硬币摆成一排，其中有一些正面朝上，其余的都是反面朝上。W!ʌ!k 打算不断执行以下操作直到这 $n$ 枚硬币中没有硬币反面朝上：

- 如果现在这 $n$ 枚硬币中有 $k$ 枚硬币反面朝上，那么翻转从左到右第 $k$ 枚硬币。具体地，如果从左到右第 $k$ 枚硬币正面朝上，则将其变为反面朝上；如果从左到右第 $k$ 枚硬币反面朝上，则将其变为正面朝上。

在 W!ʌ!k 开始玩游戏之前，Mivik 想考考 W!ʌ!k。Mivik 想让 W!ʌ!k 算出他总共会进行多少次这样的操作，或者是 W!ʌ!k 永远无法停止执行操作。

W!ʌ!k 很快解决了这个问题，但是心理比 yky 还变态的 Mivik 显然不会放过他。Mivik 进行了很多次操作，每次他翻转了一个区间的硬币，他要求 W!ʌ!k 算出他总共会进行多少次这样的操作，或者是 W!ʌ!k 永远无法停止执行操作。

**请注意，W!ʌ!k 只是需要计算总共会进行多少次操作，而不会真正进行操作。**

## 说明/提示

### 样例解释 #1
初始时两枚硬币都是反面朝上，因此如果 W!ʌ!k 从此刻开始执行操作， W!ʌ!k 会将编号为 $2$ 的硬币翻转过来。操作后只有一枚硬币反面朝上，因此第 $2$ 次操作会将编号为 $1$ 的硬币翻转过来。在第 $2$ 次操作后没有硬币反面朝上，因此 W!ʌ!k 不会再执行操作，总共会执行 $2$ 次操作。

### 样例解释 #2
这 $8$ 次操作分别翻转了第 $2,1,2,3,4,3,2,1$ 枚硬币。

### 测试点约束
**本题采用捆绑测试。**

对于全部数据，有 $1\le n,m\le10^6$，$s_i\in\left\{\texttt H,\texttt T\right\}$，$1\le l_i\le r_i\le n$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | 特殊限制 |
|:-:|:-:|:-:|
| 1 | 10 | $n\le3$ |
| 2 | 20 | $n,m\le100$ |
| 3 | 30 | $m\le10$ |
| 4 | 20 | $l_i=r_i$ |
| 5 | 20 | 无 |

**本题读入输出量较大，请使用较快的读入输出方式。**

## 样例 #1

### 输入

```
2 2
TT
2 2
1 2
```

### 输出

```
2
1
3
```

## 样例 #2

### 输入

```
5 0
HTHTH
```

### 输出

```
8
```

## 样例 #3

### 输入

```
10 10
HTHHTHTHHH
9 9
5 5
10 10
7 7
6 6
9 9
4 4
9 9
7 7
2 2
```

### 输出

```
19
30
27
40
33
38
27
28
37
40
47
```

# 题解

## 作者：Noby_Glds (赞：10)

这是我**第一个**不看任何题解过的蓝题。

我想把自己曲折的思考过程分享给大家。

一起深度剖析这道题。
## 思路
一看标签：模拟，线段树。朴实无华。

看了一下题目，很明显是让我们先找一个**通解**。

### 它是如何消除一个反面朝上的硬币的？

凡事先从简单做起，考虑只有**一个**硬币反面朝上。
```latex
HHHTH
```
很显然，想让那个反面朝上的硬币反过来，就得存在 $4$ 个反面朝上的硬币。

所以第一步，是把前面 $3$ 个硬币一起反过来，需要 $3$ 步。
```latex
TTTTH
```
接下来就可以把所有反面朝上的硬币全翻回来了，共需 $4$ 步。
```latex
HHHHH 完成
```
如果我们令 $p$ 为这个反面朝上的硬币的位置，答案就为：
$$ans=p*2-1$$

如果有**两个甚至更多**的硬币反面朝上呢？

```latex
HHHHTT
```
在这里，$k$ 的值一开始不是 $1$，而是 $2$。

所以我们会把位置为 $2$，$3$，$4$ 的硬币翻过来，位置为 $1$ 的硬币没有动。
```latex
HTTTTT
```
接着，$k$ 退回 $2$，并把所经过的位置上的硬币翻面。
```latex
HHHHHT
```
然后就只有一个硬币反面朝上了。

我们在分析过程中可以发现，若 $k$ 为反面朝上的硬币的数量，则在翻硬币时，$k$ 会不断增加，直到位置 $k$ 上的硬币为反面，然后 $k$ 会不断减少，直到退回 $k$ 原来的值。

简的来说，就是 $k$ 不断往右移，碰到一个反面朝上的硬币则折回，向左移回到原来的位置，这个反面朝上的硬币就消除了。

这样不断地消去，直到没有反面朝上的硬币。

### 无解的情况怎么判断？
无解的情况只有一种，就是 $k$ 不断向右移，却一直没碰到反面朝上的硬币。

也就是说，在位置 $k$ 的左边有 $k$ 个硬币反面朝上。

可左边一共就 $k-1$ 个位置！

所以令我们惊异的是，无解的情况不存在！

~~坏坏的出题人。~~
### 答案公式？
我们模拟一下这个场景。

此时一共有 $m$ 个硬币反面朝上，$k$ 的值目前为 $m$。

$k$ 往右移，碰到一个反面朝上的硬币，再折回来。

若这个硬币的位置为 $w_1$，则这个操作所用步数为：$w_1*2-1-2*(m-1)=w_1*2-m*2+1$

然后 $m$ 值减 $1$，但我们不让它减，让它在接下来的操作中体现,此时 $k$ 的初始值更新为 $m-1$。

接着又碰到一个反面朝上的硬币，若这个硬币的位置为 $w_2$，则这个操作所用步数为：$w_2*2-1-2*(m-2)=w_2*2-(m-1)*2+1$

以此类推。

把所有的操作的步数推出来后，相加得：
$$2*(w_1+w_2+...+w_{m-1}+w_m)-2(m+(m-1)+...+2+1)+m*1$$

$$2*\sum\limits_{i=1}^mw_i-2(m+1)*m/2+m$$

$$2*\sum\limits_{i=1}^mw_i-(m+1)*m+m$$

$$2*\sum\limits_{i=1}^mw_i-m^2$$

所以，我们做到了……

等等，怎么维护 $2*\sum_{i=1}^mw_i$ 和 $m^2$？

看到这种**区间异或**的题目，我们会想到[P3870 [TJOI2009] 开关](https://www.luogu.com.cn/problem/P3870)这道题。

先切了这道题，拿着 AC 的线段树代码，公式一套，就完成啦！

## 代码

```cpp
#include<bits/stdc++.h>
#define N 1000010
#define int long long//不开 long long 见祖宗
using namespace std;
struct hhh{
	int l,r,cnt,sum,lz;
}dl[N*4];
int n,m,l,r;
int a[N];
char p;
void pushup(int bh){
	dl[bh].cnt=dl[bh*2].cnt+dl[bh*2+1].cnt;
	dl[bh].sum=dl[bh*2].sum+dl[bh*2+1].sum;
}
void pushdown(int bh){
	if(!dl[bh].lz) return;
	dl[bh*2].lz^=1;
	dl[bh*2].cnt=dl[bh*2].r-dl[bh*2].l+1-dl[bh*2].cnt;
	dl[bh*2].sum=(dl[bh*2].r+dl[bh*2].l)*(dl[bh*2].r-dl[bh*2].l+1)/2-dl[bh*2].sum;
	dl[bh*2+1].lz^=1;
	dl[bh*2+1].cnt=dl[bh*2+1].r-dl[bh*2+1].l+1-dl[bh*2+1].cnt;
	dl[bh*2+1].sum=(dl[bh*2+1].r+dl[bh*2+1].l)*(dl[bh*2+1].r-dl[bh*2+1].l+1)/2-dl[bh*2+1].sum;
	dl[bh].lz=0;
}
void build(int bh,int l,int r){
	dl[bh].l=l,dl[bh].r=r;
	if(l==r){
		if(a[l]) dl[bh].cnt=1,dl[bh].sum=l;
		return;
	}
	int mid=(l+r)>>1;
	build(bh*2,l,mid),build(bh*2+1,mid+1,r);
	pushup(bh);
}
void update(int bh,int L,int R){
	int l=dl[bh].l,r=dl[bh].r;
	if(l>=L&&r<=R){
		dl[bh].lz^=1;
		dl[bh].cnt=r-l+1-dl[bh].cnt;
		dl[bh].sum=(r+l)*(r-l+1)/2-dl[bh].sum;
		return;
	}
	pushdown(bh);
	int mid=(l+r)>>1;
	if(L<=mid) update(bh*2,L,R);
	if(R>mid) update(bh*2+1,L,R);
	pushup(bh);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>p;
		if(p=='T') a[i]=1;
	}
	build(1,1,n);
	cout<<2*dl[1].sum-dl[1].cnt*dl[1].cnt<<endl;
	while(m--){
		cin>>l>>r;
		update(1,l,r);
		cout<<2*dl[1].sum-dl[1].cnt*dl[1].cnt<<endl;
	}
	return 0;
}//由于我用的是cin和cout，这道题卡常又卡得紧，所以要开O2
```
## 后记

这篇题解注重于寻找通解的过程，而不是线段树怎么打。

如果有茬，欢迎向我私信。

QAQ。

---

## 作者：Daniel13265 (赞：6)

设当前反面朝上硬币数为 $k$ ，将所有反面的位置 $p_1,p_2,\dots,p_k$ 从小到大排序。

显然有 $k\le p_k$，所以一定存在一个 $i$ 使得 $p_{i-1}<k,p_i\ge k$。那么一开始翻硬币的过程一定是 $k,k+1\dots,p_i-1,p_i,p_i-1,\dots,k$。容易发现这样操作之后 $p_i$ 上的硬币变成了正面而其他硬币不变，问题就变为了 $k$ 减小 $1$ 后的情况。所以答案不可能是 $\texttt{never}$ 并且每个位置对答案的贡献形如 $2p_i-2j+1$。这可以拆成三部分分别计算求和，即
$$
2\sum_{i=1}^{k}p_i-2\sum_{i=1}^ki+k=2\sum_{i=1}^{k}p_i-k^2.
$$

用线段树维护 $p_i$ 之和以及 $k$ 即可。时间复杂度 $O\left(n+m\log n\right)$，空间复杂度 $O\left(n\right)$。

---

## 作者：封禁用户 (赞：5)

### 思路
令反面朝上的硬币数为 $t$，且 $t$ 个反面朝上的硬币的位置升序排序后为 $p_1,p_2,p_3,\dots,p_{t}$。   
始终存在一个值 $i$ 使 $p_{i-1} \le t \le p_{i}$。所以，思考可得，此时开始的 $2p_i-2t+1$ 次操作与将位置为 $p_t$ 上的硬币翻转等价。此时 $t=t-1$。     
综上，答案为：  
$$
\begin{aligned}
{}&2\sum_{i=1}^{t}p_i-2\sum_{i=1}^{t}i+t&\\
=&2\sum_{i=1}^{t}p_i-2 \left( \frac{t \times \left( t+1\right)}{2}\right)+t&\\
=&2\sum_{i=1}^{t}p_i-{t \times \left( t+1\right)}+t&\\
=&2\sum_{i=1}^{t}p_i-\left({t^2+t}\right)+t&\\
=&2\sum_{i=1}^{t}p_i-t^2-t+t&\\
=&2\sum_{i=1}^{t}p_i-t^2
\end{aligned}
$$
线段树维护即可。

  
### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int n,m;
string s;

struct tree{
	int l,r,tag=0;
	long long tot,p;
}tr[N*4];

void pushup(int x){
	tr[x].p=tr[x*2].p+tr[x*2+1].p;
	tr[x].tot=tr[x*2].tot+tr[x*2+1].tot;
}

void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(l==r){
		if(s[l]=='T')
			tr[x].p=l,tr[x].tot=1;
		else tr[x].p=0,tr[x].tot=0; 
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid),build(x*2+1,mid+1,r);
	pushup(x);
}

void pushdown(int x){
	if(tr[x].tag!=0){
		tr[x*2].tag^=1,tr[x*2+1].tag^=1;
		tr[x*2].tot=1ll*(tr[x*2].r-tr[x*2].l+1)-1ll*tr[x*2].tot;
		tr[x*2+1].tot=1ll*(tr[x*2+1].r-tr[x*2+1].l+1)-1ll*tr[x*2+1].tot;
		tr[x*2].p=1ll*(tr[x*2].r+tr[x*2].l)*(tr[x*2].r-tr[x*2].l+1)/2-1ll*tr[x*2].p;
		tr[x*2+1].p=1ll*(tr[x*2+1].r+tr[x*2+1].l)*(tr[x*2+1].r-tr[x*2+1].l+1)/2-1ll*tr[x*2+1].p;
		tr[x].tag=0;
	}
}

void update(int x,int l,int r){
	if(tr[x].l>=l&&tr[x].r<=r){
		tr[x].tot=1ll*(tr[x].r-tr[x].l+1)-1ll*tr[x].tot;
		tr[x].p=1ll*(tr[x].r+tr[x].l)*(tr[x].r-tr[x].l+1)/2-1ll*tr[x].p;
		tr[x].tag^=1;
		return;
	}
	pushdown(x);
	int mid=(tr[x].l+tr[x].r)/2;
	if(l<=mid)
		update(x*2,l,r);
	if(r>mid)
		update(x*2+1,l,r);
	pushup(x);
}

int main(){
	scanf("%d%d",&n,&m);
	cin>>s;
	s='7'+s;
	build(1,1,n);
	printf("%lld\n",2*tr[1].p-tr[1].tot*tr[1].tot);
	for(int i=1;i<=m;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		update(1,l,r);
		printf("%lld\n",2*tr[1].p-tr[1].tot*tr[1].tot);
	}
} 
``````

---

## 作者：一架飞机 (赞：5)

先考虑模拟操作。可以发现，每次操作之后，k 只 +1 或 -1，所以所操作的位置只向右或向左移一格。所以操作可以变成这样（1 是反面，0 是正面）：
- 当操作 1 时，此硬币从 1 变为 0，并向左一位。
- 当操作 0 时，此硬币从 0 变为 1，并向右一位。

如果把这些操作连续起来，就会变成这样：从某一位开始，向左或向右一直运动。若向左运动，则直到碰到第一个 0 后改变方向。向右同理。来回运动并“同化”所有经过的硬币。最后从最左边的 1 到最右边。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/sawchkgh.png)

设 $a_i$ 为从开始向左数第i个0，$b_i$ 为从开始向右数第 i 个 1。当开始是 0 时:
$$ans=(b_1-x)+(b_1-a_1)+(b_2-a_1)+\cdots+(b_n-0)=2*\sum b_i-2*\sum a_i+x$$
当开始是 1 时同理可得：
$$ans=2*\sum b_i-2*\sum a_i-x$$

所以只要用线段树维护：区间 1 或 0 的下标和，区间 1 的个数（找 x 用）。记得开 long long。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T&x){
	x=0;char ch=getchar();bool f=0;
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	x=f?-x:x;
}
typedef long long ll;
const int M=1e6+5;
char str[M];int a[M],n;
struct node{int l,r,la,c1;ll v0,v1;}tr[M*4];
void pushup(int p){
	tr[p].v0=tr[p*2].v0+tr[p*2+1].v0;
	tr[p].v1=tr[p*2].v1+tr[p*2+1].v1;
	tr[p].c1=tr[p*2].c1+tr[p*2+1].c1;
}
void pd(int p){
	tr[p].la^=1;
	swap(tr[p].v0,tr[p].v1);
	tr[p].c1=tr[p].r-tr[p].l+1-tr[p].c1;
}
void pushdown(int p){
	if(tr[p].la){pd(p*2);pd(p*2+1);tr[p].la=0;}
}
void build(int p,int l,int r){
    tr[p].l=l;tr[p].r=r;
    if(l==r){
		if(a[l])tr[p].v1=l,tr[p].c1=1;
		else tr[p].v0=l;
		return;
	}
    int mid=(l+r)>>1;
    build(p*2,l,mid);build(p*2+1,mid+1,r);
	pushup(p);
}
void change(int p,int l,int r){
    if(l>tr[p].r||r<tr[p].l)return;
    if(l<=tr[p].l&&tr[p].r<=r){pd(p);return;}
    pushdown(p);
    change(p*2,l,r);change(p*2+1,l,r);
	pushup(p);
}
ll tv0,tv1;int tc1;
void ask(int p,int l,int r){
    if(l>tr[p].r||r<tr[p].l)return;
    if(l<=tr[p].l&&tr[p].r<=r){tv0+=tr[p].v0;tv1+=tr[p].v1;tc1+=tr[p].c1;return;}
    pushdown(p);
    ask(p*2,l,r);ask(p*2+1,l,r);
	pushup(p);
}
void getans(){
	int x,col;ll s1,s2;
	tv0=tv1=tc1=0;ask(1,1,n);
	x=tc1;
	tv0=tv1=tc1=0;ask(1,x,x);
	col=tc1;
	tv0=tv1=tc1=0;ask(1,1,x);
	s1=tv0;
	tv0=tv1=tc1=0;ask(1,x,n);
	s2=tv1;
	if(!col)printf("%lld\n",2*s2-2*s1+x);
	else printf("%lld\n",2*s2-2*s1-x);
}
int main(){
//	freopen("n.txt","r",stdin);
	int m,l,r;read(n),read(m);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)a[i]=str[i]=='H'?0:1;
	build(1,1,n);
	getans();
	while(m--){
		read(l),read(r);
		change(1,l,r);
		getans();
	}
	return 0;
}
```



---

