# [HNOI/AHOI2018] 转盘

## 题目描述

一次小 G 和小 H 准备去聚餐，但是由于太麻烦了于是题面简化如下：

一个转盘上有摆成一圈的 $n$ 个物品（编号 $1\sim n$），其中的 $i$ 个物品会在 $T_i$ 时刻出现。

在 $0$ 时刻时，小 G 可以任选 $n$ 个物品中的一个，我们将其编号为 $s_0$。并且如果 $i$ 时刻选择了物品 $s_i$，那么 $i+1$ 时刻可以继续选择当前物品或选择下一个物品。当 $s_i$ 为 $n$ 时，下一个物品为物品 $1$，否则为物品 $s_{i}+1$。在每一时刻（包括0时刻），如果小 G 选择的物品已经出现了，那么小 G 将会标记它。小 H 想知道，在物品选择的最优策略下，小 G 什么时候能标记所有物品？

但麻烦的是，物品的出现时间会不时修改。我们将其描述为 $m$ 次修改，每次修改将改变其中一个物品的出现时间。每次修改后，你也需求出当前局面的答案。对于其中部分测试点，小 H 还追加了强制在线的要求。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/17510.png)

## 样例 #1

### 输入

```
5 3 0
1 2 3 4 5
3 5
5 0
1 4```

### 输出

```
5
7
6
7```

# 题解

## 作者：Kelin (赞：31)

## [题意](https://blog.csdn.net/BeNoble_/article/details/80051296)

给你一个$n$元环$,$你可以在$0$时刻从任意一个位置出发$,$每一秒可以选择往后或者留在原地

每个点有个参数$T_i,$当你走到$i$的时间$t\ge T_i$时你就可以把$i$标记

问你把整个环上的点都标记最小需要多长时间$,$带修改$T_i,$强制在线

---

## 题解

考虑转化问题

>假设你$t$时刻在某个点$,$每次可以向前走或者留在原地$,$然后$t$减$1$

>每个点在$T_i$时间消失$,$求一个最小的$t$使得在所有点都消失前访问所有点

可以发现转化之后你**留在原地一定是不优的**$,$也就是说你会**一直往前走**$

考虑破环为链$,$枚举一个起点$i\in[n,2n),$然后往前走到一个点$j$的时间是$t-(i-j)$

对于所有的$j\in(i-n,i]$都要满足

$$t-(i-j)\ge T_j$$

$$\Rightarrow t\ge(T_j-j)+i$$

$$\Rightarrow t_{\min}=\max\{T_j-j\}+i$$

这样我们就可以枚举$i$然后在$O(n\log n)$的时间内求出最优解了

令$a_i=T_i-i,$那么

$$Ans=\min_{n\le i\lt 2n}\{\max_{i-n\lt j\le i}a_j+i\}$$

把$i$替换成$i+(n-1)$

$$\Rightarrow\min_{1\le i\le n}\{\max_{i\le j\le i+n-1}a_j+i\}+n-1$$

考虑到$a_i=T_i-i\gt a_{i+n}=T_i-(i+n),$**减少一下限制**

$$\Rightarrow\min_{1\le i\le n}\{\max_{i\le j\le2n}a_j+i\}+n-1$$

对于一个$i$算出其后缀最大值就可以得到答案$,$但是这样复杂度不会更优

**这时候就要考虑对于一个$j$来说的答案**(令$a_0=\inf$)

>$1.$如果$j$就是后缀最大值$,$那么就是找到一个$j$前面第一个权值大于$a_j$的$a_i,$那么答案就是$a_j+i+1$

>$2.$如果$j$不是后缀最大值$,$那么他的答案和后缀最大值$a_k$的答案一样

第一点提醒到我们可以从后往前对这个序列维护一个单调上升的栈

假设栈里面的留下的元素是$p_0,p_1,\ldots,p_k$

其实$p_0=0,$设$j$满足$p_{j-1}\lt n\le p_j$

$$\Rightarrow Ans=\min_{1\le i\le j}\{a_{p_i}+p_{i-1}+1\}+n-1=\min_{1\le i\le j}\{a_{p_i}+p_{i-1}\}+n$$

可以用线段树来维护一个单调栈(模板题$\to$[楼房重建](https://www.luogu.org/problemnew/show/P4198))

这里讲一下具体实现和细节

其实就是合并两个区间单调栈的细节

>$1.$首先右子树的答案可以直接取

>$2.$然后用右子树的区间最大值在左子树里二分找到第一个比其大的位置然后返回答案

>对于该位置前面的所有答案取个$\min$

记$2$的一次操作是$qry(x)$

因为这样是操作是对于一个长度为$2n$的序列而言的

而最优位置$j$必须满足$p_{j-1}\lt n,$所以还需要记录一下上面$qry$得到的答案

但是我们可以发现对于维护$[1,2n]$的节点

最后的答案就是$(n,2n]$里的最大值在$[1,n]$二分后得到的答案

而$(n,2n]$里的最大值就是$[1,n]$里的**最大值$-n$**

所以就可以只维护区间$[1,n]$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+5,inf=1e9;
typedef int arr[N];
int n,m,q,ans,a[N],tr[N<<2],mx[N<<2];
#define lc p<<1
#define rc p<<1|1
int qry(int p,int L,int R,int x){
    if(L==R)return mx[p]>x?x+L:inf;
    int mid=(L+R)>>1;
    return mx[rc]>x?min(tr[p],qry(rc,mid+1,R,x)):qry(lc,L,mid,x);
}
inline void up(int p,int L,int R){
    mx[p]=max(mx[lc],mx[rc]);
    tr[p]=qry(lc,L,(L+R)>>1,mx[rc]);
}
void build(int p,int L,int R){
    if(L==R)return mx[p]=a[L]-L,void();
    int mid=(L+R)>>1;
    build(lc,L,mid),build(rc,mid+1,R),up(p,L,R);
}
void mdy(int p,int L,int R,int x,int w){
    if(L==R)return mx[p]=w-L,void();
    int mid=(L+R)>>1;
    if(x<=mid)mdy(lc,L,mid,x,w);
    else mdy(rc,mid+1,R,x,w);up(p,L,R);
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n),sd(m),sd(q);
    fp(i,1,n)sd(a[i]);
    build(1,1,n);int x,y;
    we(ans=qry(1,1,n,mx[1]-n)+n);
    while(m--){
        sd(x),sd(y);q?x^=ans,y^=ans:0;
        mdy(1,1,n,x,y),we(ans=qry(1,1,n,mx[1]-n)+n);
    }
return Ot(),0;
}
```

---

## 作者：ztzshiwo001219 (赞：11)

我们首先根据题目推导一些性质,然后依据性质得到做法.

首先记录每一个点最后一次被访问的时间为$a_i$

首先我们一定可以找到一种最优解的方法是从某一个点出发,然后每一次都向右走,走完一圈.因为假如不存在这样的方法,对于一个最优解,一定可以转化为一个合法的走一圈的最优解.

比如原来的最优解为

$a=\{ 1,2,3,6,7 \}$

可以转化为

$a=\{3,4,5,6,7\}$

可知这样转化一定合法.

那么我们可以枚举任何一个点为起点,然后计算出出发点的时间,求最小值就可以得到答案.这样一次运算是$O(n^2)$的


接下来我们分析答案的式子.首先将原数组复制一遍去掉环的影响
$$ans=min_{1\leq i \leq n}(max_{0 \leq j \leq n-1}(t_{i+j}-j)+n-1)$$

$$ans=min_{1\leq i \leq n}(max_{i \leq j \leq i+n-1}(t_{j}-j+i)+n-1)$$

$$ans=min_{1\leq i \leq n}(max_{i \leq j \leq i+n-1}(t_{j}-j)+i+n-1)$$

令$x_i=t_i-i$

$$ans=min_{1\leq i \leq n}(max_{i \leq j \leq i+n-1}x_j+i+n-1)$$

而$x_i=t_i-i,x_{i+n}=t_i-i-n,x_i-n=x_{i+n},x_i>x_{i+n}$
$$ans=min_{1\leq i \leq n}(max_{i \leq j}x_j+i)+n-1$$

如果先考虑$i$再考虑$j$的话只能枚举,最多做到一次运算$O(nlogn)$

如果确定了$j$,只需要满足$i$最小就行了.也就是对于每一个$j$,找到最小$i$的满足$i$位置的后缀最大值为$x_j$,最后答案取min.

我们可以从后往前维护一个$x_i$单调上升的栈.

如果栈内元素的位置为
$$p_1,p_2,p_3\ldots p_{top}$$
那么
$$min(1+x_{p_1},p_1+1+x_{p_2} \ldots p_{top-1}+1+x_{p_{top}})+n-1$$
就是答案,时间复杂度为$O(n)$

单调上升序列实际上可以用线段树维护,比如[楼房重建](https://www.luogu.org/problemnew/show/P4198).

具体思想和细节就不讲了,可以看其他题解或者代码理解.

代码:
```c++
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define	rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
#define lc p<<1
#define rc p<<1|1
#define ls l,mid
#define rs mid+1,r
#define pb push_back
#define pii pair<int,int>
#define ft first
#define sd second
#define SZ(x) (int)x.size()
using namespace std;
typedef long long LL;
const int N=200010;
const int inf=0x3f3f3f3f;
template<typename T>inline bool chkmax(T&A,const T&B){return A<B?A=B,1:0;}
template<typename T>inline bool chkmin(T&A,const T&B){return A>B?A=B,1:0;}
template<typename T>inline void read(T&x)
{
    x=0;int f=0;char ch=getchar();
    while(!isdigit(ch))f|=(ch=='0'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=f?-x:x;
}
inline void file()
{
    freopen("circle.in","r",stdin);
    freopen("circle.out","w",stdout);
}
int n,m,L,a[N];
int t[N<<3],tl[N<<3],Max[N<<3],ans,P;
inline int Query(int l,int r,int p,int x)
{
	if(l==r)return Max[p]<=x?inf:x+l+1;
	int mid=(l+r)>>1;
	if(Max[rc]<=x)return Query(ls,lc,x);
	else return min(tl[p],Query(rs,rc,x));
}
inline void pushup(int p,int l,int r)
{
	int mid=(l+r)>>1;
	Max[p]=max(Max[lc],Max[rc]);
	t[p]=min(tl[p]=Query(ls,lc,Max[rc]),t[rc]);
}
inline void Modify(int l,int r,int p,int x,int y)
{
	if(l==r){Max[p]=y-x;t[p]=inf;return;}
	int mid=(l+r)>>1;
	if(x<=mid)Modify(ls,lc,x,y);
	else Modify(rs,rc,x,y);
	pushup(p,l,r);
}
inline void Build(int l,int r,int p)
{
	if(l==r){Max[p]=a[l]-l;t[p]=inf;return;}
	int mid=(l+r)>>1;
	Build(ls,lc),Build(rs,rc),pushup(p,l,r);
}
int main()
{
    int x,y;
    //file();
    read(n),read(m),read(P);
	L=n<<1;
    For(i,1,n)read(a[i]),a[i+n]=a[i];
	Build(1,L,1);
    printf("%d\n",ans=min(1+Max[1],tl[1])+n-1);
    while(m--)
    {
		read(x),read(y);
		x^=P*ans,y^=P*ans;
		Modify(1,L,1,x,y),Modify(1,L,1,x+n,y);
		printf("%d\n",ans=min(1+Max[1],tl[1])+n-1);
    }
    return 0;
}
```

---

## 作者：litble (赞：8)

[你真的不想戳开看一看吗](https://blog.csdn.net/litble/article/details/80187830)

可以发现，如果我需要在转盘上走两圈，不如在第一个物品上停留一段时间，然后再走一圈。

假设我们固定起点，那么一定是走一圈+多出来的一点点。

会发现那多出来的一点点假设走到x，那么以x+1为起点就可以只走一圈。

所以得到结论：**最优方案一定是在第一个物品上停留一段时间后走一圈**。

拆环，把原数列往后面粘一遍，设$a_i=T_i-i$（即走到这里时可以标记该物品需要预先停留的时间），则答案为：

$$\min_{i=1}^n \{ \max_{j=1}^n \{ a_{i+j-1}+i \} \} +n-1$$

也就是：

$$\min_{i=1}^n \{ \max_{j=1}^n \{ a_{i+j-1}\}+i \} +n-1$$

以下将取$\max_{j=1}^n \{ a_{i+j-1}\}+i$的区间称作**“窗口”**，而左边这个取max的式子称作**“窗口的答案”**，注意窗口的长度不一定是n。

用线段树弄一弄。

假设线段树上一个节点代表的区间是$[s,t]$，那么我们开一个数组$mx$表示这个区间内最大的$a_i$，开一个数组$ans$来维护所有包含了整个右半区间的窗口中$\max_{j=1}^n \{ a_{i+j-1}\}+i$的最小值。

这样维护的窗口可能长度会大于n，但是由于在整个长为2n的序列中，有$a_x=T_x-x , a_{x+n}=T_x-x-n$的缘故，如果这个窗口包含了$a_x$，那么$a_{x+n}$及以后的值并不会对该窗口的答案产生影响，所以可以视作所有的窗口长度都是小于等于n的。而每个窗口的长度一定是大于$\frac{t-s+1}{2}$的，所以线段树的根节点，也就是代表区间为$[1,2n]$的那个节点的窗口长度是大于等于n的，综上，我们可以统计所有长度为n的窗口的答案。

然后就是在线段树操作的时候，如何合并左右子区间的答案的问题了。方法和[这道题](https://www.luogu.org/problemnew/show/P4198)差不多，具体实现看代码。

复杂度$O(nlog^2 n+mlog^2 n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int N=200005;
int n,m,p,lasans;
#define ls (i<<1)
#define rs ((i<<1)|1)
int T[N],a[N],ans[N<<2],mx[N<<2];
//orz:合并左右子区间答案
int orz(int i,int s,int t,int num) {
	if(s==t) return s+max(mx[i],num);
	int mid=(s+t)>>1;
	if(mx[rs]>=num) return min(ans[i],orz(rs,mid+1,t,num));
	//此时窗口的左端点在左半时max受的不是num影响，而是右半影响，所以取一次ans[i]
	else return min(orz(ls,s,mid,num),mid+1+num);
	//否则整个右半作窗口左端点的max都受num影响，左端点越小答案越小。
}
void up(int i,int s,int t) {
	mx[i]=max(mx[ls],mx[rs]);
	ans[i]=orz(ls,s,(s+t)>>1,mx[rs]);//既然考虑的窗口要包含整个右子区间，则一定包含其a[i]最大值
}
void build(int s,int t,int i) {
	if(s==t) {ans[i]=T[s],mx[i]=a[s];return;}
	int mid=(s+t)>>1;
	build(s,mid,ls),build(mid+1,t,rs),up(i,s,t);
}
void chan(int x,int s,int t,int i) {
	if(s==t) {ans[i]=T[s],mx[i]=a[s];return;}
	int mid=(s+t)>>1;
	if(x<=mid) chan(x,s,mid,i<<1);
	else chan(x,mid+1,t,(i<<1)|1);
	up(i,s,t);
}
int main()
{
	int x,y;
	n=read(),m=read(),p=read();
	for(RI i=1;i<=n;++i) {
		T[i]=read(),T[i+n]=T[i];
		a[i]=T[i]-i,a[i+n]=T[i+n]-i-n;
	}
	build(1,n<<1,1);
	lasans=ans[1]+n-1;printf("%d\n",lasans);
	while(m--) {
		x=read(),y=read();
		if(p) x^=lasans,y^=lasans;
		T[x]=T[x+n]=y,a[x]=y-x,a[x+n]=y-x-n;
		chan(x,1,n<<1,1),chan(x+n,1,n<<1,1);
		lasans=ans[1]+n-1;printf("%d\n",lasans);
	}
	return 0;
}
```

最后，鸣谢[这位dalao](https://www.cnblogs.com/Yuzao/p/8877365.html)对本蒟蒻理解本题的帮助。


---

## 作者：wujingfey (赞：7)

# 前言
一道线段树的练习题，虽然是黑但也不算不能做。蒟蒻来水一篇“线段树和递归合并”的题解。这篇题解超详细的，保证你能看懂！

传送门：[P4425](https://www.luogu.com.cn/problem/P4425)
# 题意描述
题面还是不算长，略过了。
# 题解

## 题目分析
首先环是不好解决的，我们用一个 trick 破环为链：将原数组复制一份放在后面得到一个 $2n$ 的数组，记为 $t$，这样在解决问题的时候就可以不用考虑环的问题了。

我们发现一个性质：**任何在一个点等待的时间，我们都可以挪到最前面来等；走走停停拿完所有物品的时间，等价于在开局先等上这一段内最长的等待时间，然后一直向前走完 $n$ 个物品花费的时间**。其实很好感性理解的，下面给出证明：

我们从前往后给数组每个元素标号 $1\to 2 n$，假设在 $S$ 时刻从 $i$ 号元素出发，一刻都不停地往前走，在到达位置 $j$ 号元素时，时刻应该是 $s+(j-i)$。这个是显然的。

然后根据题意嘛，到达 $j$ 的时刻应该要大于 $t_j$ 的，所以可以得到不等式 $s+(j-i)\ge t_j$。简单移一下项，得到：$s\ge (t_j-j)+i$。

为什么给 $t_j-j$ 打括号呢？因为我们发现在一次询问里，每个元素的 $t_j-j$ 都是固定的！

然后扯回来，对于一个起点 $i$ 因为 $s$ 要满足大于所有的 $(t_j-j)+i$，所以 $s$ 最优就等于 $\max_{i\le j\le i+n-1}\{t_j-j\}+i$。也就是开局先等上最长的一段时间，然后一路向前走。证明完毕。

因为 $s$ 是指的起始时间，再加上全部走完的时间 $n-1$ 就是 $s+n-1$，所以题目要求的就是所有 $i\in [1,n]$ 对应的 $s_{min}+(n-1)$，形式化来说就是
$$\min_{1\le i\le n}\{i+\max_{i\le j\le i+n-1}\{t_j-j\}\}+n-1$$

------------------

但推到这里似乎就陷入瓶颈了：这个式子还能怎么变，才能降低复杂度呢？

这里有个非常重要的性质：**把 $\max_{i\le j\le i+n-1}\{t_j-j\}$ 替换成 $\max_{i\le j\le 2n}\{t_j-j\}$ 答案不变！**

为什么呢？请看下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/mw1hndpu.png)
如图所示，我们发现修改之后多出来的那一部分，就是后面圈出来的那一坨红色。比较一下，发现它和前面那一坨红色对应的 $t$ 应该是一样的，但是下标也就是 $j$ 增大了，那么 $t_j-j$ 肯定就减小咯。我们这里求的是 $s_{max}$，所以加上它们并无影响。

加上之后有什么好处呢？加上之后，我们的表达式就变成了：
$$\min_{1\le i\le n}(i+\max_{i\le j\le 2n}(t_j-j))+n-1$$
这样就~~容易~~用线段树和递归合并来维护答案了！

## 实现
我们用线段树维护两个值：$maxx,minn$，$maxx$ 表示这个区间内最大的 $t+j-j$，$minn$ 表示这个区间**左半部分**内最小的 $i+maxx$。为什么是左半部分呢？因为我们的出发点 $i\in [1,n]$，而数组的完整区间是 $[1,2n]$（我们倍长了一次数组）。

建空树和修改的框架就不多赘述了，重点讲一下 push_up。

在讲 push_up 之前推荐去看一下 [P4198](https://www.luogu.com.cn/problem/P4198)，那道题的合并方式和此题类似。~~不过不看也问题不大？~~

```cpp
void push_up(int p){
	tr[p].maxx=max(tr[ls].maxx,tr[rs].maxx);
	tr[p].minn=dfs(ls,tr[rs].maxx);
}
```
首先 $maxx$ 是很好更新的，直接取 $maxx$ 即可。

但 $minn$ 的更新比较繁琐，因为更新的时候 $maxx$ 是会改变的，会对之前的答案产生影响。也就是说，可能之前子树更新到的答案现在是不能用的。所以我们要用 dfs 重新从子树内查找答案。

如图模拟一个合并过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/3pqxn9ye.png)

我们现在要把左侧区间 $P$ 和右侧的 $R$ 合并在一起变成 $Q$，$Q$ 的答案记录左半侧 $P$ 的 $minn$。

dfs 传入两个参数：$p,mrs$。$p$ 表示这个区间在线段树上的编号，$mrs$ 表示右侧区间 $R$ 的 $maxx$。把 $P$ 劈开成 $ls$ 和 $rs$ 两个子区间。考虑三种情况：

1. 搜索到 $P$ 是叶子结点，那么直接根据式子返回 $l+\max\{t_j-j\}$，其中 $\max\{t_j-j\}$ 是 $mrs$ 和它本身的 $maxx$ 中的较大值。
```cpp
if(tr[p].l==tr[p].r){//叶子节点 
	return tr[p].l+max(tr[p].maxx,mrs);//根据式子直接返回值 
}
```
2. 劈开之后，考虑 $rs.maxx$ 和 $mrs$ 谁大。如果 $mrs$ 更大，说明 $P$ 内的原本答案都无效，因为现在加入的 $mrs$ 让 $maxx$ 可能发生改变。这时对于右区间而言，所有 $max\{t_j-j\}$ 都是 $mrs$，所以右侧的 $minn$ 就是 $mid+1+mrs$。而左侧的答案则因为 $mrs$ 也不清楚，直接搜索就好。
```cpp
if(tr[rs].maxx<=mrs){//mid往右的最大值都是mrs 
	int mid=(tr[p].l+tr[p].r)>>1;
	return min(mid+1+mrs,dfs(ls,mrs));//答案可能是mid+1+mrs,也有可能在左区间的左儿子部分 
}
```
3. 否则 $rs.maxx$ 比 $mrs$ 更大。这时候的 $mrs$ 对 $P$ 毫无影响，而在之前自下而上的线段树 push_up 操作中，我们已经处理好了 $p.minn$，表示 $p$ 的左半部分的答案，这是可以直接用的。而 $Q$ 的答案是由 $ls$ 和 $rs$ 组合而成，所以还要搜索 $rs$ 得到答案。
```cpp
else if(tr[rs].maxx>mrs){//最大值在右儿子这一块区间内
	//左半段的min不受mrs影响，所以不用递归
	//tr[p].minn只记录了这个区间的左侧答案，但我们整个区间Q的答案还要看看p的右半侧，所以搜索右儿子 
	return min(tr[p].minn,dfs(rs,mrs));
}
```

然后这道题就完成了。

## AC CODE:
```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=2e5+5;
int n,m,p,lastans;
struct NODE{
	int l,r;
	int maxx,minn;
	//maxx记录区间内的max(tj-j) 
	//minn记录区间内的min(i+max) 
}tr[N<<2];
void build(int p,int l,int r){//建空树 
	tr[p].l=l;
	tr[p].r=r;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
int dfs(int p,int mrs){
	if(tr[p].l==tr[p].r){//叶子节点 
		return tr[p].l+max(tr[p].maxx,mrs);//根据式子直接返回值 
	}
	if(tr[rs].maxx<=mrs){//mid往右的最大值都是mrs 
		int mid=(tr[p].l+tr[p].r)>>1;
		return min(mid+1+mrs,dfs(ls,mrs));//答案可能是mid+1+mrs,也有可能在左区间的左儿子部分 
	}else if(tr[rs].maxx>mrs){//最大值在右儿子这一块区间内
		//左半段的min不受mrs影响，所以不用递归
		//tr[p].minn只记录了这个区间的左侧答案，但我们整个区间Q的答案还要看看p的右半侧，所以搜索右儿子 
		return min(tr[p].minn,dfs(rs,mrs));
	}
}
void push_up(int p){
	tr[p].maxx=max(tr[ls].maxx,tr[rs].maxx);
	tr[p].minn=dfs(ls,tr[rs].maxx);
}
void updata(int p,int x,int k){
	if(tr[p].l==tr[p].r){
		tr[p].maxx=k-x;
		tr[p].minn=k;
		return;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) updata(ls,x,k);
	else updata(rs,x,k);
	push_up(p);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>p;
	build(1,1,2*n);
	for(int i=1;i<=n;i++){
		 int x;
		 cin>>x;
		 updata(1,i,x);
		 updata(1,i+n,x);
	}
	lastans=tr[1].minn+n-1;
	cout<<lastans<<'\n';
	while(m--){
		int x,y;
		cin>>x>>y;
		if(p==1){
			x^=lastans;
			y^=lastans;
		}
		updata(1,x,y);
		updata(1,x+n,y);
		lastans=tr[1].minn+n-1;
		cout<<lastans<<'\n';
	}
	cout<<endl;
	return 0;
}
```

复杂度分析：$m$ 次操作，每次操作线段树的复杂度是 $O(\log_2n)$，每次 push_up 至多修改 $O(n\log_2n)$。复杂度 $O(n\log_2^2n)$。

# 后记
蒟蒻的第一篇黑题题解，求通过！审核大大辛苦了 QwQ。

---

## 作者：花淇淋 (赞：5)

# Solution
 - 如果一种最优解是：在时刻$t$从位置$x$开始，从时刻$t+1$开始共有$t1$个时刻选择当前物品，有$t2$个时刻选择下一个物品，那么这和在时刻$t+t1$从位置$x$开始，从时刻$t+1$开始都不选择当前物品，实际上是等价的
 - 那么只要考虑不停留的情况，问题转化为选择一个最小的开始时间$b_{x}(t≥0)$，使得从位置$x$开始，花$n$个时刻完成标记，答案即$t+n-1$
 - 首先，为了处理环的情况，令$T$数组倍长，即$$T_{i}=T_{i-n}(n+1≤i≤2n)$$
 - 因为要求满足$$t+i-x≥T_{i}(\forall i,x≤i≤x+n-1)$$
 - 所以$bx$即$$max_{i=x}^{x+n-1}T_{i}-i$$
 - 那么令$a_{i}=T_{i}-i$
 - 发现$$T_{i}=T_{i-n}(x+n≤i≤2n)$$
 - 说明$$a_{i}<a_{i-n}(x+n≤i≤2n)$$
 - 那么$b_{x}$可以改写为后缀最大值的形式：$$max_{i=x}^{2n}a_{i}(1≤x≤n)$$
 - 因为$$ans=min(b_{x}+x)$$
 - 所以如果对于$l≤i≤r$满足$b_{i}$全部相同，那么选$l$一定比选$[l+1,r]$中的任何一个要优
 - 将所有这样区间$[l,r]$中的$l$取出，就形成了一个关于$a_{i}$的单调下降子序列
 - 特别地，这个子序列的每一项$d_{i}$都要满足
 $$a_{j}<a_{i}(\forall j,i<j≤2n)$$
 - 其实只要最后一项满足上述条件即可，也就是对**这个单调下降子序列的末项作了限制**
 - 那么为了方便，**从右到左维护一个单调上升子序列**，也就是取出所有的$r$放入$c$数组，所有的$c_{i}+1$就是要选的$l$，对答案的贡献即$$(1).min(a_{c_{i+1}}+c_{i}+1)(1≤i<m)$$
 - 特别地，由于$x$和$c$的取值在$[1,n]$，所以当$c_{m}!=n$时，位置$c_{m}+1$对答案的贡献是$$(2).max_{i=n+1}^{2n}a_{i}$$
 - 即$$max_{i=1}^{n}a_{i}-n$$
 - 因为在此条件下，$c_{m}+1,n,n+1$必处于同一区间$[l,r]$中
 - 当$c_{m}=n$时$(2)$显然成立
 - 于是对$(1),(2),a_{c_{1}}+1$取最小值即可
 - 维护线段树，记$calc(l,r,v,p)$为一个四元组，表示节点$p$（对应区间$[l,r]$），末项$>v$的单调上升子序列（**从右到左**）的信息：
 $$(c_{1},c_{m},a_{c_{1}},min(a_{c_{i+1}}+c_{i}+1)(1≤i<m))$$
 - 记$val[p]$表示节点$p$对应区间的$max(a_{i})$
 - 记$b[p]$表示$calc(l,mid,val[p3],p2)$，$p2,p3$为左右子节点
 - 修改回溯时要更新$val$和$b$
 - 下面讨论如何计算$calc(l,r,v,p)$
 - 若$val[p3]≤v$，那么这个子序列与$p3$无关，递归$p2$即可
 - 否则，$p2$对子序列的贡献依然是$b[p]$
 - 显然回溯时$b[p2]$会比$calc(l,mid,val[p3],p2)$先算
 - 时间复杂度$O(nlog^2n)$

# Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define p2 p << 1
#define p3 p << 1 | 1

template <class t>
inline void read(t & res)
{
	char ch;
	while (ch = getchar(), !isdigit(ch));
	res = ch ^ 48;
	while (ch = getchar(), isdigit(ch))
	res = res * 10 + (ch ^ 48);
}

const int e = 1e5 + 5, inf = 0x3f3f3f3f;
struct node
{
	int c1, cm, a1, res;
}b[e * 4];
int n, m, val[e * 4], a[e], op, ans;

inline node calc(int l, int r, int v, int p)
{
	if (l == r) return val[p] > v ? (node){l, r, val[p], inf} : (node){0, inf, inf, inf};
	int mid = l + r >> 1;
	if (val[p3] <= v) return calc(l, mid, v, p2);
	if (val[p2] <= val[p3]) return calc(mid + 1, r, v, p3);
	node lc = b[p], rc = calc(mid + 1, r, v, p3);
	if (!lc.c1) return rc;
	return (node){lc.c1, rc.cm, lc.a1, min(min(lc.res, rc.res), rc.a1 + lc.cm + 1)};
}

inline void update(int l, int r, int s, int v, int p)
{
	if (l == r)
	{
		val[p] = v;
		return;
	}
	int mid = l + r >> 1;
	if (s <= mid) update(l, mid, s, v, p2);
	else update(mid + 1, r, s, v, p3);
	val[p] = max(val[p2], val[p3]);
	b[p] = calc(l, mid, val[p3], p2);
}

inline void build(int l, int r, int p)
{
	if (l == r)
	{
		val[p] = a[l] - l;
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, p2);
	build(mid + 1, r, p3);
	val[p] = max(val[p2], val[p3]);
	b[p] = calc(l, mid, val[p3], p2);
}

int main()
{
	int i, x, y;
	read(n); read(m); read(op);
	for (i = 1; i <= n; i++) read(a[i]);
	build(1, n, 1);
	node z = calc(1, n, val[1] - n, 1);
	ans = min(z.res, min(z.a1 + 1, val[1] - n + z.cm + 1));
	ans += n - 1;
	printf("%d\n", ans);
	while (m--)
	{
		read(x);
		read(y);
		if (op)
		{
			x ^= ans;
			y ^= ans;
		}
		a[x] = y;
		update(1, n, x, y - x, 1);
		node z = calc(1, n, val[1] - n, 1);
		ans = min(z.res, min(z.a1 + 1, val[1] - n + z.cm + 1));
		ans += n - 1;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：ZHR100102 (赞：4)

一道贪心与线段树递归合并的综合题。

# 贪心

破环成链的 trick 自然不用多说。

首先观察题目，很容易发现一个性质：只走一圈的方案一定最优。这个很容易证，因为再绕一圈回来标记前面的和等前面的标记完之后继续走是等价的，并且再绕一圈甚至可能更劣。

于是，我们只用走一圈，并且在走路的途中走走停停，就可以走出最优解。

但这依然不怎么好求，通过观察发现：我们把所有停下的时间移到前面来，在起点就把要停的时间全部停掉，和走走停停是等价的，并且这样更好求。

接下来我们就来推式子了：

假设当前的时间是 $t$，我们从 $i$ 出发，要走到 $j$ 处，并且 $j$ 处的最早出现时间为 $a_j$，那么可以列出方程：

$$t+(j-i)\ge a_j$$

移项得：

$$t \ge a_j-j+i$$

因此在此时 $t$ 的最小值就是 $\max_{j=i}^{i+n-1}(a_j-j+i)$。

由于每次走路还要计算时间，所以总时间为 $\max_{j=i}^{i+n-1}(a_j-j+i)+n-1$。

因为要最小化，所以答案就是 $\min_{i=1}^{n}(\max_{j=i}^{i+n-1}(a_j-j+i))+n-1$。

# 线段树与递归

根据上面的分析，我们需要维护 $\min_{i=1}^{n}(\max_{j=i}^{i+n-1}(a_j-j+i))+n-1$ 这个式子。

首先 $\max_{j=i}^{i+n-1}(a_j-j+i)$ 是很好维护的，我们可以通过一个线段树来维护。

但是外面的那个 $\min_{i=1}^{n}$ 怎么维护？实际上我们可以通过在线段树上递归来实现。

设 $x$ 表示线段树上某个节点的最小值。因为我们只需要求出起点在 $1$ 到 $n$ 中的最小值（后面一部分是复制两倍后的，所以和前面的重复了，可以不要计算），所以 $x$ 就是**这个节点左半部分的最小值**，而不是整个节点的最小值。但也不是说按整个节点算就不可以了，只是说这样做代码好写、思路好想一些。

接下来考虑如何递归合并信息：

![](https://cdn.luogu.com.cn/upload/image_hosting/xofcupd1.png)

注意：当前我们处在的节点是 $l$。

## 当递归到叶子节点时

由式子可知，直接返回 $i+\max(lson_{max},r_{max})$ 即可。

## 当 $rson_{max}< r_{max}$ 时

$r_{max}$ 依然是最大值，所以要接下来递归 $l$ 的左儿子 $lson$，因为右儿子已经确定贡献了，贡献就是 $\min(dfs(lson,r_{max}),mid+1+r_{max})$。

## 当 $rson_{max}\ge r_{max}$ 时

$rson_{max}$ 把 $r_{max}$ 挤下去了，所以要接下来递归 $l$ 的右儿子 $rson$，以找到右儿子的那个最大值在哪，才能确定贡献，左儿子的贡献就是 $\min(x_l,dfs(rson,r_{max}))$。

注意 $x_l$ 与 $dfs(p,r_{max})$ 函数的定义不同，其一是表示左半部分的最小值，另一个是表示全部区间的最小值。

其余部分就是按照线段树常规的配置来写了。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
const int N=200005;
int n,m,q,a[N],lastans=0;
struct node{
	int l,r;
	int mx,mi;
}tr[4*N];
int dfs(int p,int mxr)
{
	if(tr[p].l==tr[p].r)return (tr[p].l+max(mxr,tr[p].mx));
	int mid=(tr[p].l+tr[p].r)>>1;
	if(tr[rc].mx<mxr)return min(dfs(lc,mxr),mid+1+mxr);
	return min(tr[p].mi,dfs(rc,mxr));
}
void pushup(int p)
{
	tr[p].mx=max(tr[lc].mx,tr[rc].mx);
	tr[p].mi=dfs(lc,tr[rc].mx);
}
void build(int p,int ln,int rn)
{
	tr[p]={ln,rn,a[ln]-ln,ln+a[ln]-ln};
	if(ln==rn)return;
	int mid=(ln+rn)>>1;
	build(lc,ln,mid);
	build(rc,mid+1,rn);
	pushup(p);
}
void update(int p,int x,int v)
{
	if(tr[p].l==x&&tr[p].r==x)
	{
		tr[p].mx=v-x;
		tr[p].mi=x+v-x;
		return;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid)update(lc,x,v);
	else update(rc,x,v);
	pushup(p);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i];
	build(1,1,2*n);
	cout<<tr[1].mi+n-1<<endl;
	lastans=tr[1].mi+n-1;
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		if(q)x^=lastans,y^=lastans;
		update(1,x,y);
		update(1,x+n,y);
		cout<<tr[1].mi+n-1<<endl;
		lastans=tr[1].mi+n-1;
	}
	return 0;
}
```

---

## 作者：lhm_ (赞：4)

发现最优解可以表示为在起点等待一段时间，然后不停顿地走完一圈。因为停顿的原因是当前的物品没有出现，所以可以在起点先等待，然后不停顿地来标记。

对环倍长来将其转化为链，用 $i$ 来枚举起始位置，$j$ 来枚举物品，则答案可表示为：
$$
\min\limits_{i=1}^n\left \{ i+\max\limits_{j=i}^{2n} \left \{t_j-j \right \} \right \} +n-1
$$
这里可以将 $\max$ 的枚举范围扩大，因为扩大的部分不可能成为最大值，所以不影响答案。

考虑用线段树来维护答案，因为倍长后长度为 $2n$，起始位置只可能为 $[1,n]$，所以对于一个区间，只维护左区间的答案即可。线段树上维护当前区间的答案和 $t_i-i$ 的最大值，合并两个区间时，用右区间的最大值 $v$ 在左区间二分即可。

具体地，若 $v$ 比当前区间右区间的最大值大，则说明 $mid$ 往右的最大值是 $v$，右区间就直接返回左端点的答案即可，若 $v$ 更小，就不用再进入左区间，区间返回当前区间的答案即可。

线段树根节点的答案即为所求。维护方法和[楼房重建](https://www.luogu.com.cn/problem/P4198)很像。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 800010
#define ls (cur<<1)
#define rs (cur<<1|1)
#define mid ((l+r)>>1)
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,ans,p,root=1;
int t[maxn],ma[maxn],val[maxn];
int query(int l,int r,int v,int cur)
{
    if(l==r) return l+max(v,ma[cur]);
    if(v>=ma[rs]) return min(mid+1+v,query(l,mid,v,ls));
    return min(val[cur],query(mid+1,r,v,rs));
}
void pushup(int cur,int l,int r)
{
    ma[cur]=max(ma[ls],ma[rs]);
    val[cur]=query(l,mid,ma[rs],ls);
}
void build(int l,int r,int cur)
{
    if(l==r)
    {
        val[cur]=t[l],ma[cur]=t[l]-l;
        return;
    }
    build(l,mid,ls),build(mid+1,r,rs),pushup(cur,l,r);
}
void modify(int l,int r,int pos,int v,int cur)
{
    if(l==r)
    {
        val[cur]=v,ma[cur]=v-l;
        return;
    }
    if(pos<=mid) modify(l,mid,pos,v,ls);
    else modify(mid+1,r,pos,v,rs);
    pushup(cur,l,r);
}
int main()
{
    read(n),read(m),read(p);
    for(int i=1;i<=n;++i) read(t[i]),t[i+n]=t[i];
    build(1,2*n,root),printf("%d\n",ans=val[root]+n-1);
    while(m--)
    {
        int x,y;
        read(x),read(y),x^=ans*p,y^=ans*p;
        modify(1,2*n,x,y,root),modify(1,2*n,x+n,y,root);
        printf("%d\n",ans=val[root]+n-1);
    }
    return 0;
}
```

---

## 作者：Nemlit (赞：4)

~~颂魔眼中的一眼题我大湖南竟无一人$AC$~~

首先我们考虑一个性质：我们肯定存在一种最优解，满足从某个点出发，一直往前走，不停下来。

证明：我们假设存在一种最优解，是在$t_i$的时候到达$a$点，那么我肯定会在$t_i - x(x≥1)$的时间会到达$a - 1$号点

我们假设$x != 1$，即我们会在$a-1$点进行停留，此时那么我们到达$a - 2$号点的时间$<t_i - 2$，到达$a-3$号点的时间$<t_i - 3$

那么如果我有一个点$a - y$是在$t_i - y$时刻出现，那么我们不能取到这个点，必须要重新转一圈

那么如果$x = 1$，且每一次走都没停下来，我们可以保证我们在$x!=1$经过该点后经过该点

所以说如果$x!=1$可以经过的所有点我们肯定在$x==1$的情况下都能经过，而且$x==1$情况下的一些点，$x != 1$不一定能经过，所以我们肯定每一次取$x==1$是一种最优情况

然后我们考虑进一步转化题意：假设我在一个点，从$T_i$时刻出发，满足转一圈刚好标记所有点，那么我们$T_i$以前的时间实际上是没有用的

由于环不好处理，而且转化后我们保证只要走一圈，所以我们可以断环成链

于是我们可以考虑，找到一个最好的起点$i$，找到最好的$T_i$，使得从i点在$T_i$时刻出发答案最优，即我们要求这个式子：$min(T_i+n)$其中满足对于任意的$x$，$T_i≥t_x-x+i$

即我们要求：$min_{i=1}^n(n + max_{x=i+1}^{2*n}(i-x + t_x))=min_{i=1}^n(n+i+max_{x=i+1}^{2*n}(x-t_x))$

所以我们枚举每一个起点，找到最大的$t_x-x$，用线段树维护，单次操作复杂度为$O(NlogN)$，现在问题要考虑怎么修改

令$a_i=t_i-i$，所以原式变成$n+min_{i=1}^n(max_{x=i+1}^{2*n}(a_x)+i)$

不难发现，$max_{x=i+1}^{i+n}(a_x)$是单调不增的。于是，我们维护一个单调栈，对于每一个$max_{x=i+1}^{i+n}(a_x)$连续的一段，找到一个最小的$i$即可，单调栈可以用线段树来维护（[详见我楼房重建的题解](https://www.cnblogs.com/bcoier/p/10293075.html)），把楼房重建的求和改成$max$就行了，于是复杂度就变成了$O(Nlog^2N)$

## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
int read() {
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(int i = s; i <= t; ++ i)
#define ls k * 2
#define rs k * 2 + 1
#define maxn 100005 
int n, m, p, last, a[maxn << 1], ma[maxn << 3], ans[maxn << 3];
int query(int k, int l, int r, int v) {
	if(l == r) return l + max(v, ma[k]);
	int mid = (l + r) >> 1;
	if(ma[rs] >= v) return min(ans[k], query(rs, mid + 1, r, v));
	return min(mid + v + 1, query(ls, l, mid, v));
}
inline void updata(int k, int l, int r, int mid) {
	ma[k] = max(ma[ls], ma[rs]), ans[k] = query(ls, l, mid, ma[rs]);
}
void modify(int k, int l, int r, int ll) {
	if(l == r) return (void)(ans[k] = a[l] + l, ma[k] = a[l]);
	int mid = (l + r) >> 1;
	if(ll <= mid) modify(ls, l, mid, ll);
	else modify(rs, mid + 1, r, ll);
	updata(k, l, r, mid);
}
void build(int k, int l, int r) {
	if(l == r) return (void)(ans[k] = a[l] + l, ma[k] = a[l]);
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r), updata(k, l, r, mid);
}
int main() {
	n = read(), m = read(), p = read();
	rep(i, 1, n) a[i] = read() - i, a[i + n] = a[i] - n;
	build(1, 1, n * 2);
	printf("%d\n", last = ans[1] + n - 1);
	rep(i, 1, m) {
		int x = read() ^ (p * last), y = read() ^ (p * last);
		a[x] = y - x, a[x + n] = y - x - n, modify(1, 1, 2 * n, x), modify(1, 1, 2 * n, x + n);
		printf("%d\n", last = ans[1] + n - 1);
	}
	return 0;
}
```

---

## 作者：lnzwz (赞：3)

### 题意：

给你一个$n$元环，你可以在0时刻从任意一个位置出发，每一秒可以选择往后或者留在原地

每个点有个参数$T_i$，当你走到$i$的时间$t>=T_i$时你就可以把i标记

问你把整个环上的点都标记最小需要多长时间，带修改$T_i$，强制在线

----------------------------------------------------------------------------------------------

好难的题。

首先，有等待操作不太好弄。

可以发现：在总时间一定的情况下，到每个点越晚越好。

所以，可以把所有等待都移到起点处，解不会变差。

由于是环，破环为链处理。

如果在$s$时间在$i (1<=i<=n)$出发，那么到$j (i<=j<i+n)$的时间为$s+(j-i)$。根据要求，得$s+(j-i)>=T_j$，

即$s=max(T_j-j)+i (i<=j<i+n)$。总时间为$max(T_j-j)+i+n-1 (i<=j<i+n)$。

就是要找一个$i (1<=i<=n)$，使得$max(T_j-j)+i+n-1 (i<=j<i+n)$最小。

设$A_j=T_j-j$，则式子变为$max(A_j)+i+n-1 (i<=j<i+n)$。

这样就得出的答案的式子。

发现$max(A_j)+i+n-1 (i<=j<i+n)$
等于$max(max(A_j) (i<=j<=n),max(A_j) (n+1<=j<i+n)+i+n-1$

而由于$A$的后半段是由前半段复制过来并减$n$，

所以$max(A_j) (i+1<=j<=n+n)<max(max(A_j) (i<=j<=n)$。

所以式子可以变为$max(A_j)+i+n-1 (i<=j<=n+n)$（即后缀最值）。

但是有修改，这样还是不好维护答案。增加很好做，区间覆盖即可，但因为有减小的操作，减小后，修改的段会很多，无法处理。

我们发现，在$max(A_j)$一定时，$i$越小越好。

所以维护所有让$max(A_j)$变大的$j$，就是从后往前的单调递增序列。

设这个序列为$W_i$，那么若$i={W_x}+1$，则$max(A_j)=A_{W_{i+1}}$。

这样，式子变为$A_{W_{i+1}}+{W_i}+1+i+n-1$，即$A_{W_{i+1}}+{W_i}+i+n$。
单调递增序列可以用线段树维护，方法如下：

首先，单调递增序列只是用于合并答案，所以保存$W$的第一个和最后一个，还有这段序列的答案就行。

维护每个节点的$max$，单调递增序列，还有整体考虑时左子节点的单调递增序列。

设计一个$getst(l,r,x)$表示求$l$~$r$的元素只考虑>$x$的答案。

若右儿子的最值不大于x，则不用考虑右儿子，只考虑左儿子即可。

否则，左儿子的递增序列一定完全包含在答案中，只考虑右儿子即可。

可以递归实现，复杂度$O(logn)$。

考虑$pushup$操作的实现：只要用左儿子的$getst$加上右儿子即可。

每次$pushup$，时间复杂度为$O(logn)$，总时间复杂度为$O(nlog^2n)$。

代码还不算太难写，主要是推导比较复杂。
```cpp
#include <stdio.h> 
#define max(a, b)(a > b ? a: b)
#define min(a, b)(a < b ? a: b) 
int sz[200010],inf = 999999999;
struct SJd {
	int x,y,mi;
	SJd() {}
	SJd(int a) {
		x = y = a;
		mi = inf;
	}
	SJd(int l, int r, int w) {
		x = y = -1;
		mi = inf;
		for (int i = r; i >= l; i--) {
			if (sz[i] > sz[w]) {
				if (y == -1) x = y = i;
				else x = i;
				mi = min(mi, sz[w] + i);
				w = i;
			}
		}
	}
};
SJd operator + (SJd a, SJd b) {
	if (a.x == -1) return b;
	if (b.x == -1) return a;
	SJd rt;
	rt.x = a.x;
	rt.y = b.y;
	rt.mi = min(a.mi, b.mi);
	rt.mi = min(rt.mi, sz[b.x] + a.y);
	return rt;
}
SJd jd[400010],zz[400010];
int ma[400010],wz[400010];
SJd getst(int i, int l, int r, int w) {
	if (r - l <= 4) return SJd(l, r - 1, w);//小范围暴力，避免细节。
	int m = (l + r) >> 1;
	if (ma[(i << 1) | 1] <= sz[w]) return getst(i << 1, l, m, w);
	else return zz[i] + getst((i << 1) | 1, m, r, w);
}
void pushup(int i, int l, int r) {
	ma[i] = max(ma[i << 1], ma[(i << 1) | 1]);
	if (ma[i] == ma[i << 1]) wz[i] = wz[i << 1];
	else wz[i] = wz[(i << 1) | 1];
	int m = (l + r) >> 1;
	zz[i] = getst(i << 1, l, m, jd[(i << 1) | 1].x);
	jd[i] = zz[i] + jd[(i << 1) | 1];
}
void getddz(int i, int l, int r) {
	ma[i] = sz[l];
	wz[i] = l;
	jd[i] = SJd(l);
}
void jianshu(int i, int l, int r) {
	if (l + 1 == r) {
		getddz(i, l, r);
		return;
	}
	int m = (l + r) >> 1;
	jianshu(i << 1, l, m);
	jianshu((i << 1) | 1, m, r);
	pushup(i, l, r);
}
void xiugai(int i, int l, int r, int j) {
	if (l + 1 == r) {
		getddz(i, l, r);
		return;
	}
	int m = (l + r) >> 1;
	if (j < m) xiugai(i << 1, l, m, j);
	else xiugai((i << 1) | 1, m, r, j);
	pushup(i, l, r);
}
void xiugai(int x, int y, int n) {
	sz[x] = y - x;
	sz[x + n] = y - (x + n);
	xiugai(1, 1, n + 1, x);
}
int getans(int n) {
	SJd rt;
	rt.mi = ma[1];
	rt.x = wz[1] + n;
	rt.y = -1;
	rt = getst(1, 1, n + 1, wz[1] + n) + rt;
	return rt.mi + n;
}
int main() {
	int n,m,p;
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		sz[i] = a - i;
		sz[i + n] = a - (i + n);
	}
	jianshu(1, 1, n + 1);
	int la = getans(n);
	printf("%d\n", la);
	for (int i = 0; i < m; i++) {
		int x,y;
		scanf("%d%d", &x, &y);
		if (p == 1) {
			x ^= la;
			y ^= la;
		}
		xiugai(x, y, n);
		la = getans(n);
		printf("%d\n", la);
	}
	return 0;
}
```

---

## 作者：tyler178 (赞：3)

大概就是要维护这样一个式子，各位大佬都解释的很明白了
$$
\min_{i=1}^{n}\Big\{\max_{j=i}^{2n}T_j-j+i\Big\} + (n-1)
$$
然而接下来的线段树做法太神仙了，如果我们不会这个技巧，还能怎么办？当然是分块大法好。
把序列分成若干块，每一块内部倒着求单调栈，那么总的单调栈就是每个块的单调栈取一个后缀拼起来。需要记录栈内答案的后缀最小值，每次查询时二分出后缀的位置，更新答案。

```cpp
#include <bits/stdc++.h>
#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
#define rg register
using namespace std;
typedef long long LL;
const int MAXN = 100005;
const int MAXB = 350;
const int MAXS = 1000;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &AKNOI) {
	T x = 0, flag = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') flag = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	AKNOI = flag * x;
}

template <typename T> inline void cmin(T &x, T y) {
	if (x > y) x = y;
}

template <typename T> inline void cmax(T &x, T y) {
	if (x < y) x = y;
}

struct Heap {
	priority_queue<int> q, q2;
	inline void push(int x) {
		q.push(x);
	}
	inline void erase(int x) {
		q2.push(x);
	}
	inline int top() {
		while (!q.empty() && !q2.empty() && q.top() == q2.top()) {
			q.pop(); q2.pop();
		}
		return q.top();
	}
} S;

int n, m, op, T[MAXN];
int B, bcnt, bel[MAXN], L[MAXB], R[MAXB], mx[MAXB];
int stk[MAXB][MAXS], top[MAXB], mn[MAXB][MAXS];

void Build(int b) {
	int tp = 0;
	for (int i = R[b]; i >= L[b]; --i) {
		if (!tp || T[i] > T[stk[b][tp]]) {
			stk[b][++tp] = i;
		}
	}
	mx[b] = T[stk[b][top[b] = tp]];
	for (int i = tp; i >= 2; --i) {
		mn[b][i] = stk[b][i] + 1 + T[stk[b][i - 1]];
		if (i < tp) cmin(mn[b][i], mn[b][i + 1]);
	}
}

int Query() {
	int Mx = S.top(), ret = INF;
	for (int b = bcnt; b >= 1; --b) {
		if (mx[b] <= Mx) continue;
		int l = 1, r = top[b] - 1, p = r + 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (T[stk[b][mid]] > Mx) {
				p = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		cmin(ret, stk[b][p] + 1 + Mx);
		if (p < top[b]) cmin(ret, mn[b][p + 1]);
		cmax(Mx, mx[b]);
	}
	return min(ret, 1 + Mx) + n - 1;
}

void init() {
	read(n); read(m); read(op);
	B = sqrt(1.0 * n * log(n)) / 1.6;
	for (int i = 1; i <= n; ++i) {
		read(T[i]);
		T[i] -= i;
		S.push(T[i] - n);
	}
	for (int l = 1, r; l <= n; l += B) {
		r = min(l + B - 1, n);
		L[++bcnt] = l; R[bcnt] = r;
		for (int i = l; i <= r; ++i) {
			bel[i] = bcnt;
		}
		Build(bcnt);
	}
}

void solve() {
	int x, y, ans;
	printf("%d\n", ans = Query());
	while (m--) {
		read(x); read(y);
		if (op) {
			x ^= ans;
			y ^= ans;
		}
		S.erase(T[x] - n);
		T[x] = y - x;
		S.push(T[x] - n);
		Build(bel[x]);
		printf("%d\n", ans = Query());
	}
}

int main() {
	init();
	solve();
	return 0;
}

```


---

## 作者：伊地知虹夏 (赞：2)

非常 edu 的一杯 hot tea。

有一个观察是每个点会被恰好经过 $1$ 次，因为我们只需要保留每个点最后一次经过的位置。

枚举起点 $i$，设 $i-1$ 被访问到的时间为 $T$。则有 $T \ge T_j + n - {\operatorname{dis}(i,j)}$。这个 ${\operatorname{dis}}$ 不是很好处理，考虑断环为链，那么 ${\operatorname{dis}(i,j)} = j - i + 1$。此时 $T = \max\limits_{j \in [i, i+n)}\{T_j  - j\} + i + n - 1$。

那么答案就是 $\min\limits_{1\le i\le n} \{i + \max\limits_{i\le j\le i+n-1} T_j-j\} + n-1$。

注意到 $j \le i + n -1$ 实际上是没有用的，那么就变成了 $\min\limits_{1\le i\le n} \{i + \max\limits_{i\le j} T_j-j\} + n-1$。

涉及到后缀的带修 ds 问题我们一般考虑单侧递归线段树维护。具体地，设计函数 `calc(c, v)` 表示线段树节点 $c$ 右侧 $\max$ 为 $v$ 时的答案。分类讨论右儿子 $\max$ 和 $v$ 的大小关系即可完成单侧递归，实现细节可以看代码。

时间复杂度 $\mathcal O(n\log n)$，非常小清新。

```
#include<bits/stdc++.h>
#define rep(i,l,r) for (int i = l; i <= r; i ++)
#define rrp(i,l,r) for (int i = l; i >= r; i --)
using namespace std;
typedef long long LL;
const int N = 2e5 + 5;

int n, q, ty, a[N], b[N], val[N << 2], mx[N << 2], son[N << 2];

int calc(int c, int l, int r, int v) {
  if (l == r) return max(mx[c], v) + l;
  int mid = l + r >> 1;
  if (mx[c << 1 | 1] >= v) 
    return min(son[c], calc(c << 1 | 1, mid + 1, r, v));
  return min(calc(c << 1, l, mid, v), v + mid + 1);
}

void init (int c, int l, int r) {
  if (l == r) { val[c] = a[l] + l, mx[c] = a[l]; return ; }
  int mid = l + r >> 1;
  init(c << 1, l, mid), init(c << 1 | 1, mid + 1, r);
  mx[c] = max(mx[c << 1], mx[c << 1 | 1]);
  val[c] = son[c] = calc(c << 1, l, mid, mx[c << 1 | 1]);
  if (mid < n) val[c] = min(val[c << 1 | 1], val[c]);
}

void upd (int p, int v, int c, int l, int r) {
  if (l == r) { val[c] += v, mx[c] += v; return ; }
  int mid = l + r >> 1;
  if (p <= mid) upd(p, v, c << 1, l, mid);
  else upd(p, v, c << 1 | 1, mid + 1, r);
  mx[c] = max(mx[c << 1], mx[c << 1 | 1]);
  val[c] = son[c] = calc(c << 1, l, mid, mx[c << 1 | 1]);
  if (mid < n) val[c] = min(val[c << 1 | 1], val[c]);
}

void print(int c, int l, int r) {
  fprintf(stderr, "[%d,%d] = {%d, %d}\n", l, r, val[c], mx[c]);
  if (l == r) return ;
  int mid = l + r >> 1;
  print(c << 1, l, mid), print(c << 1 | 1, mid + 1, r);
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> q >> ty;
  rep (i, 1, n) cin >> a[i], a[i + n] = b[i] = a[i];
  rep (i, 1, 2 * n) a[i] -= i;
  init(1, 1, 2 * n);
  int ans = val[1] + n-1;
  cout << ans << '\n';
  rep (i, 1, q) {
    int x, y; cin >> x >> y;
    x ^= ty * ans, y ^= ty * ans;
    upd(x, y - b[x], 1, 1, 2 * n);
    upd(x + n, y - b[x], 1, 1, 2 * n);
    b[x] = y, cout << (ans = val[1]+n-1) << '\n';
    // print(1, 1, 2 * n);
  }
  cerr << 1. * clock() / CLOCKS_PER_SEC << '\n'; 
  return 0;
}
```

---

## 作者：居然有个高手 (赞：2)

介绍一种比较新颖的维护答案方法。

首先，最优方案肯定可以被表示为在起始位置停留一段时间后连续走一圈。因为如果在中途停止了一段时间，那么显然可以将那段时间放到在起始位置停留，这样子原本的限制也一定能够满足。

然后，我们倒着考虑，固定最终位置 $pos$，往前走连续的一段，则最终答案 $T$ 需要满足以下式子：

$T = \begin{cases} \max \limits_{1\le i \le pos} t_i+pos-i \\ \max \limits_{pos<i \le n} t_i+pos+n-i \end{cases}$  

我们定义 $b_i = \max \limits_{1\le j\le i}t_i-i$，$c_i = \max \limits_{i<j\le n}t_i+n-i$，我们枚举最终位置 $i$，那么答案就可以写成 $T= \min \limits_{1\le i\le n} \max(b_i+i,c_{i+1}+i)$。

观察到随着 $i$ 的增大，$b_i$ 单调不降，$c_i$ 单调不升，所以在 $\max(b_i,c_{i+1})$ 的取值上必然存在一个 $pos$，使得 $\forall i < pos,c_{i+1} > b_i$，$\forall i\ge pos,c_{i+1}\le b_i$，则我们可以将上式分段拆开，改为分别维护 $b_i+i,c_i+i$ 的最小值。

考虑到 $b_i$，$c_i$ 是前缀最大值与后缀最大值的形式，所以这是一个关于前后缀最值的最优取值问题。我们可以将楼房重建的维护方法进行一个变形，将其转换为提前预处理答案。

具体的，我们可以考虑维护 $b_i$ 的前缀最大值（维护 $c_i$ 的后缀最小值是同理），考虑对于一个线段树上的一个节点 $p$ 进行查询，所对应的区间是 $[l,r]$，在此区间之前的最大值为 $mx$，右区间在考虑了左区间的值的情况下，答案最小值为 $ansr$，则这个区间的答案取值分别为：

$ans = \begin{cases} \max(mx,t[p].val)+l & l=r \\ \min(query(ls,mx),t[p].ansr) & mx\le t[ls].maxb \\ \min(query(rs,mx),mx+l) & mx>t[ls].maxb\end{cases}$

可以手画一下线段树结构进行进一步的理解，在此不多赘述。

至此，本题得到解决。时间复杂度 $O(n\log^2 n)$，空间复杂度 $O(n)$。

贴个代码（可能码风比较奇特，大家参考一下就好）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
int n,m,p,a[N],b[N],c[N],ans,mx,res;
struct tree{
	int l,r,maxt1,maxt2,minr,minl;
}t[N<<2];
#define mid (t[p].l+t[p].r>>1)
inline int upl(int p,int x){
	if(t[p].l==t[p].r)return max(x,t[p].maxt1)+t[p].l;
	if(x<=t[p<<1].maxt1)return min(t[p].minr,upl(p<<1,x));
	return min(x+t[p<<1].l,upl(p<<1|1,x));
}
inline int upr(int p,int x){
	if(t[p].l==t[p].r)return max(x,t[p].maxt2)+t[p].l;
	if(x<=t[p<<1|1].maxt2)return min(t[p].minl,upr(p<<1|1,x));
	return min(x+t[p<<1|1].l,upr(p<<1,x));
}
inline void up1(int p){
	t[p].maxt1=max(t[p<<1].maxt1,t[p<<1|1].maxt1);
	t[p].maxt2=max(t[p<<1].maxt2,t[p<<1|1].maxt2);
	t[p].minr=upl(p<<1|1,t[p<<1].maxt1);
	t[p].minl=upr(p<<1,t[p<<1|1].maxt2);
}
inline void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l==r){
		t[p].maxt1=a[l]-l;t[p].maxt2=a[l+1]+n-(l+1);
		return ;
	}
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	up1(p);
}
inline void change1(int p,int pos,int val){
	if(t[p].l==t[p].r){
		t[p].maxt1=val-t[p].l;
		return ;
	}
	if(pos<=mid)change1(p<<1,pos,val);
	else change1(p<<1|1,pos,val);
	up1(p);
}
inline void change2(int p,int pos,int val){
	if(t[p].l==t[p].r){
		t[p].maxt2=val+n-(t[p].l+1);
		return ;
	}
	if(pos<=mid)change2(p<<1,pos,val);
	else change2(p<<1|1,pos,val);
	up1(p);
}
inline void query1(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r){
		res=min(upl(p,mx),res);
		mx=max(mx,t[p].maxt1);
		return ;
	}
	if(l<=mid)query1(p<<1,l,r);
	if(r>mid)query1(p<<1|1,l,r);
}
inline void query2(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r){
		res=min(upr(p,mx),res);
		mx=max(mx,t[p].maxt2);
		return ;
	}
	if(r>mid)query2(p<<1|1,l,r);
	if(l<=mid)query2(p<<1,l,r);
}
inline int ask1(int p,int l,int r){
	if(!l)return 0;
	if(l<=t[p].l&&t[p].r<=r)return t[p].maxt1;
	int ans=0;
	if(l<=mid)ans=max(ans,ask1(p<<1,l,r));
	if(r>mid)ans=max(ans,ask1(p<<1|1,l,r));
	return ans;
}
inline int ask2(int p,int l,int r){
	if(!l)return 0;
	if(l<=t[p].l&&t[p].r<=r)return t[p].maxt2;
	int ans=0;
	if(l<=mid)ans=max(ans,ask2(p<<1,l,r));
	if(r>mid)ans=max(ans,ask2(p<<1|1,l,r));
	return ans;
}
#undef mid
inline void calc(){
	int l = 0,r=n,mid;
	while(l<=r){
		mid=l+r>>1;
		if(ask1(1,1,mid)>ask2(1,mid,n))r=mid-1;
		else l=mid+1;
	}
	int pos = r+1;
	ans=res=1e9;
	if(pos^1){
		if(pos<=n)mx=ask2(1,pos,n);
		else mx=0;
		query2(1,1,pos-1),ans=res;
	}
	mx=0,res=1e9;
	if(pos!=n+1){
		if(pos^1)mx=ask1(1,1,pos-1);
		else mx=0;
		query1(1,pos,n),ans=min(ans,res);
	}
}
int main(){
	n=read(),m=read(),p=read();
	for(int i = 1;i<=n;i++)a[i]=read();
	a[n+1]=-1e9;
	build(1,1,n);
	calc();
	printf("%d\n",ans);
	int x,y;
	while(m--){
		x=read()^(p*ans),y=read()^(p*ans);
		change1(1,x,y);
		if(x^1)change2(1,x-1,y);
		calc();
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Graphcity (赞：2)

做这道题的时候忘记倍长数组这个东西了，乐。

发现正着做不是很好处理，我们倒着考虑，枚举终点 $i$。每次可以原地不动，或者向左移动一位。要求每个点第一次到达的时间 $\ge t_i$。

那我们就发现原地不动显然不优，所以我们会直接走一圈。使用二分就可以做到单次询问 $O(n\log n)$。

考虑优化。我们对 $i$ 左边的部分和 $i$ 右边的部分进行分类讨论：

- 对于左边的部分：如果 $\forall j<i,\ mid-i+j\ge t_j$ 则合法。
- 对于右边的部分：如果 $\forall j>i,\ mid -i -n+j\ge t_j$ 则合法。

两边都合法看起来不是很好处理，所以我们考虑第一个部分比第二个部分严格的条件：

$$
\max_{j<i}t_j-j+i\ge \max_{j>i} t_j-j+i-n
$$

那我们发现 $i$ 都是相同的，可以去掉。左边是前缀最大值，右边是后缀最大值，中间必然有个交点。交点之前只用考虑条件二，交点后面只用考虑条件一。

条件一太棒了，对于 $i$ 递增的时候限制严格递增。所以直接取交点 $x$ 处答案即可。

重点在于条件二。转化一下：

$$
\begin{aligned}
mid-i-n+j &\ge t_j && (i<x,i<j)\\
mid &\ge t_j-j+i+n && (i<x,i<j)\\
mid &\ge t_j-j+i+(n-1) && (i\le x,i\le j)
\end{aligned}
$$

我们先不管后面 $n-1$ 的常数。

设 $i$ 处的答案为 $f_i$，那么就有 $f_i=\max(f_{i+1}-1,t_i)$。

如果手画张图发现这个相当于 $n$ 条直线 $f_k(x)=t_k-k+x$ 在 $x=i$ 处的最高截距。这个东西就是楼房重建的翻版，直接套用兔队线段树即可。

时间复杂度 $O((n+q)\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,inf=1e9;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,TYP,ans,a[Maxn+5],top;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

struct SegTree
{
    int t[Maxn*4+5];
    #define ls(x) (x<<1)
    #define rs(x) (x<<1|1)
    inline void push_up(int p) {t[p]=max(t[ls(p)],t[rs(p)]);}
    inline void Build(int l,int r,int p)
    {
        if(l==r) {t[p]=a[l]-l; return;}
        int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
    }
    inline void Modify(int l,int r,int p,int k)
    {
        if(l==r) {t[p]=a[l]-l; return;}
        int mid=(l+r)>>1;
        if(k<=mid) Modify(l,mid,ls(p),k); else Modify(mid+1,r,rs(p),k);
        push_up(p);
    }
    inline int Count(int nl,int nr,int l,int r,int p)
    {
        if(l>r) return -inf; if(l<=nl && nr<=r) return t[p];
        int mid=(nl+nr)>>1,res=-inf;
        if(l<=mid) res=max(res,Count(nl,mid,l,r,ls(p)));
        if(r>mid) res=max(res,Count(mid+1,nr,l,r,rs(p)));
        return res;
    }
} Tr;

struct Node{int l,r,id,mx,ans,lans;} t[Maxn*4+5],st[Maxn+5];
inline int Count(int l,int r,int p,int k)
{
    if(l==r) return max(t[p].ans,k+l);
    int mid=(l+r)>>1;
    if(k>=t[rs(p)].mx) return min(k+mid+1,Count(l,mid,ls(p),k));
    else return min(t[p].lans,Count(mid+1,r,rs(p),k));
}
inline Node operator+(Node a,Node b)
{
    Node c; c.l=a.l,c.r=b.r,c.mx=max(a.mx,b.mx),c.id=a.id>>1;
    c.lans=Count(a.l,a.r,a.id,b.mx),c.ans=min(c.lans,b.ans); return c;
}
inline void push_up(int p) {t[p]=t[ls(p)]+t[rs(p)];}
inline void Build(int l,int r,int p)
{
    t[p].l=l,t[p].r=r,t[p].id=p;
    if(l==r) {t[p].mx=a[l]-l,t[p].ans=a[l],t[p].lans=inf; return;}
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int l,int r,int p,int k)
{
    if(l==r) {t[p].mx=a[l]-l,t[p].ans=a[l],t[p].lans=inf; return;}
    int mid=(l+r)>>1;
    if(k<=mid) Modify(l,mid,ls(p),k); else Modify(mid+1,r,rs(p),k);
    push_up(p);
}
inline void Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) {st[++top]=t[p]; return;}
    int mid=(nl+nr)>>1;
    if(l<=mid) Count(nl,mid,l,r,ls(p));
    if(r>mid) Count(mid+1,nr,l,r,rs(p));
}
inline int Solve()
{
    int l=0,r=n,ans;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(Tr.Count(1,n,1,mid,1)>=Tr.Count(1,n,mid+1,n,1)+n) r=mid;
        else l=mid+1;
    } ans=Tr.Count(1,n,1,l,1)+l;
    if(l)
    {
        if(l==n) ans=min(ans,t[1].ans+n-1);
        else
        {
            top=0,Count(1,n,l+1,n,1); Node res=st[top];
            Rof(i,top-1,1) res=st[i]+res;
            top=0,Count(1,n,1,l,1);
            Rof(i,top,1) {res=st[i]+res; ans=min(ans,res.lans+n-1);}
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read(),TYP=read();
    For(i,1,n) a[i]=read(); Tr.Build(1,n,1),Build(1,n,1);
    printf("%d\n",ans=Solve());
    while(m--)
    {
        int x=read(),y=read();
        if(TYP) x^=ans,y^=ans;
        a[x]=y,Tr.Modify(1,n,1,x),Modify(1,n,1,x);
        printf("%d\n",ans=Solve());
    }
    return 0;
}
```

---

## 作者：nosta (赞：2)

倍长数组$T$。

若从$x$出发，依次标记完所有物品的代价为$n-1+\max_{i=x}^{x+n-1}\{T_i-(i-x)\}$，如果某个物品$y$被跳过一次才取到，则取到$y$时的增加的代价/固有时间$n$，而减少的代价/等待时间却不会超过$n$，因为$y$在绕一周之后能够被标记到，总不会减少。这也适用于被跳过多次的情况和跳过多个物品的情况，故称从点$x$出发的最优方案是依次标记完所有的物品。

记$P_i=T_i-i$，根据结论本题的最优解为
$$
(n-1)+\min_{i=1}^n\{i+\max_{j=i}^{i+n-1}P_j\}
$$
~~我有一个$O(2nm)$的大胆想法~~ 考虑到$P_i=P_{i+n}+n$，可以变形
$$
(n-1)+\min_{i=1}^n\{i+\max_{j=i}^{2n}P_j\}
$$
线段树（总长$2n$，堆式储存）节点$x$维护$m_x=\max_{i=l_x}^{r_x}P_i$和$v_x=\min_{i=l}^{mid_x}\{i+\max_{j=i}^{r_x}P_j\}$，这样答案是
$$
(n-1)+v_1
$$

于$v_x$的合并，设$Q(y)=\min_{i=l_y}^{r_y}\{i+\max_{j=i}^{r_x}P_i\}$，则 
$$
v_x=\min_{i=l}^{mid_x}\{i+\max_{j=i}^{r_x}P_j\}=Q(ls_x)
$$
很显然的有递归式，边界另外看就好了
$$
Q(y)=\begin{cases}
\min\{v_{y},Q(rs_y)\}&m_{rs_y}\ge \max_{i=r_y+1}^{mid_x}P_i\\
\min\{Q(ls_y),mid_y+1+\max_{i=r_y+1}^{mid_x}P_i \}&m_{rs_y}<\max_{i=r_y+1}^{mid_x}P_i
\end{cases}
$$
这样合并$v_x$是一个$\log$的，线段树是两个$\log$的，完全可行。

~~代码马上补~~

代码补好啦

~~~cpp
#include <bits/stdc++.h>
#define ll long long 
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;

const int N=2e5+10;
const int inf=0x3f3f3f3f;

int n,q,p,ans,P[N];
int mid[N<<2],m[N<<2],v[N<<2];
int dfn[N<<2];

int Q(int x,int w) {
	if(dfn[x]) return dfn[x]+max(m[x],w);
	if(m[rs]>=w) return min(v[x],Q(rs,w));
	return min(Q(ls,max(w,m[rs])),mid[x]+1+w);
}
inline void upd(int x) {
	m[x]=max(m[ls],m[rs]);
	v[x]=Q(ls,m[rs]);
}
void build(int x,int l,int r) {
	if(l==r) {
		m[x]=P[l];
		v[x]=l+P[l];
		dfn[x]=l;
		return;
	}
	mid[x]=(l+r)>>1;
	build(ls,l,mid[x]);
	build(rs,mid[x]+1,r);
	upd(x);
}
void modify(int x,int l,int r,int p) {
	if(l==r) {
		m[x]=P[l];
		v[x]=l+P[l];
		return;
	}
	if(p<=mid[x]) modify(ls,l,mid[x],p);
	else modify(rs,mid[x]+1,r,p);
	upd(x);
}

int main() {
	scanf("%d%d%d",&n,&q,&p);
	for(int i=1; i<=n; ++i) scanf("%d",P+i),P[i+n]=P[i];
	for(int i=1; i<=n*2; ++i) P[i]-=i;
	build(1,1,n*2);
	printf("%d\n",ans=n-1+v[1]);
	for(int x,y; q--; ) {
		scanf("%d%d",&x,&y);
		if(p) x^=ans,y^=ans;
		P[x]=y-x; 
		P[x+n]=y-x-n; 
		modify(1,1,n*2,x);
		modify(1,1,n*2,x+n);
		printf("%d\n",ans=n-1+v[1]);
	}
	return 0;
}
~~~

---

## 作者：Cindy_Li (赞：1)

**key：不会重复经过某个点（只走一圈）。**

因为 $\ge t_i$ 的限制，我们越晚到一个点越好，若重复经过，则前一次经过是没用的。

断环为链，枚举起点 $i$，答案可以写成：

$$\min\limits_{0\le i<n}\{\max\limits_{i\le j<i+n} \{t_j+(i+n-1)-j\}\}$$

记 $a_i=t_i-i$，转写为：

$$\min\limits_{0\le i<n}\{\max\limits_{i\le j<i+n} \{a_j\}+i\}+n-1$$

注意到 $a_{i+n}=a_i-n<a_i$，于是内层 $\max$ 可以写成后缀 $\max$，容易用线段树维护。

外层的 $\min$ 怎么办呢？考虑左右区间的合并，右区间的答案可以直接查，左区间的一段后缀 $\max$ 可能会变成右区间的最大值。在左区间上二分出这个变化的位置，这个位置左边的也是直接查。

注意到我们只需要 $[1,n]$ 的答案，而维护了 $[1,2n]$ ，于是每个节点只需维护左区间的 $\min$ 答案。

```c++
const int N=2e5+5;
const int inf=1e9;
int t[N];
namespace seg{
    int tot;
    int ls[2*N],rs[2*N];
    int mx[2*N],mn[2*N];
    inline int build(int l,int r){
        int x=++tot;mx[x]=-inf,mn[x]=inf;
        if(l==r) return x;
        int mid=(l+r)>>1;
        ls[x]=build(l,mid);
        rs[x]=build(mid+1,r);
        return x;
    }
    inline int qmn(int x,int l,int r,int c){
        if(l==r) return l+max(mx[x],c);
        int mid=(l+r)>>1;
        if(mx[rs[x]]<c) return min(mid+1+c,qmn(ls[x],l,mid,c));
        return min(mn[x],qmn(rs[x],mid+1,r,c));
    }
    inline void pushup(int x,int l,int r){
        mx[x]=max(mx[ls[x]],mx[rs[x]]);
        int mid=(l+r)>>1;
        mn[x]=qmn(ls[x],l,mid,mx[rs[x]]);
    }
    inline void modify(int x,int l,int r,int p,int v){
        if(l==r) return mx[x]=v,mn[x]=v+l,void();
        int mid=(l+r)>>1;
        if(p<=mid) modify(ls[x],l,mid,p,v);
        else modify(rs[x],mid+1,r,p,v);
        return pushup(x,l,r);
    }
}
int n,m,p,lst;
inline int get(int x){return p?x^lst:x;}
int main(){
    read(n),read(m),read(p);
    seg::build(1,2*n);
    rep(i,1,n) read(t[i]),t[i+n]=t[i];
    rep(i,1,2*n) seg::modify(1,1,2*n,i,t[i]-i);
    printf("%d\n",lst=seg::mn[1]+n-1);
    rep(i,1,m){
        int x,y;read(x),read(y);
        x=get(x),y=get(y);
        seg::modify(1,1,2*n,x,y-x);
        seg::modify(1,1,2*n,x+n,y-x-n);
        printf("%d\n",lst=seg::mn[1]+n-1);
    }
    return 0;
}
```

---

## 作者：xcyyyyyy (赞：1)

因为在思考前耳朵里进了几句讲题人的话所以想的时候可能有趋向性吧，不管怎么说单切了。

一个人不会走两圈，因为更优秀的做法是原地等一会然后直接走一圈，那么答案就是：

$$
\min \limits _{1\leq i \leq n}(\max \limits_{0\leq j\leq n-1} (t_{i+j}-j))+n-1
$$

有一种直觉告诉我们时间整体减下标，那么式子就变成了：

$$
\min \limits_{1\leq i \leq n}(\max \limits_{i\leq j \leq i+n-1}(t_j-j)+i)+n-1
$$

注意到内层 $\max $ 的范围没有意义，我们不妨直接变成询问后缀，多出来的一部分一定不会影响最终的 $\max$，同时我们令 $t_i=t_i-i$，式子变成了：

$$
\min \limits_{1\leq i \leq n}(\max\limits_{j\geq i}t_j+i)+n-1
$$

现在询问的东西看起来非常好处理，一个位置的值与后缀 $\max $ 有关系很难不让人想起楼房重建那一题。

但是我写代码的时候还是栽在了楼房重建上，看来我对这个东西还是理解不透彻，这里具体的说一下怎么维护：

三个变量：$mx_u$ 表示区间最大值，$tr_u $ 表示区间的答案，$mg_u$ 表示左区间 [有了右区间] 后的贡献，注意这个贡献是左区间提供的。

在线段树 `pull ` 的时候，很明显 $tr_u=\min(tr_{rs},mg_u)$，我们来看怎么求 $mg_u$，我们记 $x=mx_{rs}$接下来我们递归到左区间来看：

（现在我们已经到了上面所说的左区间)

如果 $mx_{rs} \geq x$，那么对于左区间来说他的贡献就是 $mg_{ls}$，右区间继续递归下去。

如果 $mx_{rs}\lt x$，那么对于左区间来说他的贡献需要递归下去求解，而对于右区间的所有下标来说，后缀最大值都是 $x$。设右区间是 $[m+1,r]$ 那么我们贪心地取最小 $x+m+1$ 即可。

再次总结一下，当我们需要修改 $a_i$，而我们所求的贡献 $b_i$ 与 $\max/\min\limits_{j\leq} a_{j}$ 有关时，一定要想起楼房重建线段树！！！

想清楚了代码 $10$ 分钟写完。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define ls rt<<1
#define rs rt<<1|1
int n,m,tp;
int a[N<<1],lst;
int mg[N<<3],tr[N<<3],mx[N<<3];
int qry(int rt,int l,int r,int x){
    if(l==r)return max(mx[rt],x)+l;
    int m=(l+r)>>1;
    if(mx[rs]>=x)return min(mg[rt],qry(rs,m+1,r,x));
    else return min(qry(ls,l,m,x),m+1+x);
}
inline void pull(int rt,int l,int r,int m){
    mx[rt]=max(mx[ls],mx[rs]);
    tr[rt]=min(tr[rs],mg[rt]=qry(ls,l,m,mx[rs]));
}
void build(int rt,int l,int r){
    if(l==r)return tr[rt]=(mx[rt]=a[l])+l,void();
    int m=(l+r)>>1;
    build(ls,l,m),build(rs,m+1,r);
    pull(rt,l,r,m);
}
void upd(int rt,int l,int r,int x,int y){
    if(l==r)return tr[rt]=(mx[rt]=y)+l,void();
    int m=(l+r)>>1;
    if(m>=x)upd(ls,l,m,x,y);
    else upd(rs,m+1,r,x,y);
    pull(rt,l,r,m);
}
int main(){
    scanf("%d%d%d",&n,&m,&tp);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i];
    for(int i=1;i<=n<<1;i++)a[i]-=i;
    build(1,1,n<<1);
    printf("%d\n",lst=mg[1]+n-1);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(tp)x^=lst,y^=lst;
        upd(1,1,n<<1,x,y-x);
        upd(1,1,n<<1,x+n,y-(x+n));
        printf("%d\n",lst=mg[1]+n-1);
    }
}
```

---

## 作者：不存在之人 (赞：1)

显然有一种最优解是在某个时刻从某个点出发，一步不停的走一圈。 
一波分析： 

![](https://img-blog.csdn.net/20180421100602954?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2ODA4MDMw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

考虑枚举$j$，需要找最小满足条件的$i$。也就是对于每一个$j$,找到最小$i$的满足$i$位置的后缀最大值为$xj$,最后答案取$min$。

于是就需要从后往前维护一个单调上升的栈，用类似楼房重建的方法。 

值得一提的是，对于一段区间的答案，所用的ii一定是要在左半边的，这样就可以合并了。 

code：
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int n,m,op;
int T[200010];
struct trnode{
    int lc,rc,mx,c;
}tr[400010];int tot=0;
inline int read()
{
    int p=0; int f=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9'){p=p*10+ch-'0'; ch=getchar();}
    return p*f;
}
int findans(int x,int l,int r,int c)
{
    if(l==r) return tr[x].c=l+max(tr[x].mx,c);
    int mid=(l+r)/2;
    if(tr[tr[x].rc].mx>=c) return min(tr[x].c,findans(tr[x].rc,mid+1,r,c));
    return min(mid+1+c,findans(tr[x].lc,l,mid,c));
}
void update(int x,int l,int r)
{
    int mid=(l+r)/2;
    tr[x].c=(findans(tr[x].lc,l,mid,tr[tr[x].rc].mx));
    tr[x].mx=max(tr[tr[x].lc].mx,tr[tr[x].rc].mx);
}
void change(int x,int l,int r,int k)
{
    if(l==r) {tr[x].mx=T[l];tr[x].c=T[l]+l;return;}
    int mid=(l+r)/2;
    if(k<=mid) change(tr[x].lc,l,mid,k);
    else change(tr[x].rc,mid+1,r,k);
    update(x,l,r);
}
int bt(int l,int r)
{
    int x=++tot;
    if(l!=r)
    {
        int mid=(l+r)/2;
        tr[x].lc=bt(l,mid);
        tr[x].rc=bt(mid+1,r);
        update(x,l,r);
    }
    else tr[x].mx=T[l],tr[x].c=T[l]+l;
    return x;
}
int main()
{
    scanf("%d %d %d",&n,&m,&op);
    for(int i=1;i<=n;i++) T[i]=T[i+n]=read(),T[i]-=i,T[i+n]-=i+n;
    bt(1,n<<1);int ans=0;
    printf("%d\n",ans=tr[1].c+n-1);
    while(m--)
    {
        int x=read(),c=read();
        if(op) x^=ans,c^=ans;
        T[x]=T[x+n]=c;T[x]-=x;T[x+n]-=x+n;
        change(1,1,n<<1,x);change(1,1,n<<1,x+n);
        printf("%d\n",ans=tr[1].c+n-1);
    }
}
```

---

## 作者：sqrtqwq (赞：0)

[problem](https://www.luogu.com.cn/problem/P4425) & [blog](https://www.cnblogs.com/Carousel/p/18189392)。

我们可以先转换问题。

> 每个点在 $a_i$ 时间消失，求一个最小的 $t$ 使得在所有点都消失前访问所有点

然后我们就可以发先我们发现一直向前走一定不会比等一会在向前走更劣。

先破环成链，枚举每一个 $i \in [n,2 \times n)$。所以走到一个点 $j$ 的时间即为 $t - (i - j)$。

所以对于所有的 $j$ 必须满足 $a_j \le t - (i - j)$。即 $\max (T_j - j) + i = t_{min}$。

所以答案即为 $\min_{n \le i < 2n} max_{i - n < j \le i} \ a_j - j + i$。

于是我们令 $t_i = a_i - i$。并且让 $i$ 向前平移 $n$ 为，得到 $ans = \min_{1 \le i \le n}(i + max_{i \le j \le 2 \times n} \ a_j) + (n - 1)$。

实际上就是维护后缀最大值。相同的，对于每一个 $j$ 我们只需维护这个点作为 $i$ 的最大后缀中最小的 $i$。这个操作我们可以使用单调队列进行维护。

有了修改，我们用一颗线段树来维护单调队列即可。所以复杂度即为 $O((n + m) \log^2 n)$。

[code](https://loj.ac/s/2064675)。

---

## 作者：Cute_Fish (赞：0)

首先环不好处理所以考虑破环为链。

然后就是一个简单贪心：只绕一圈肯定最优。

有 $ans=\min_{1\leq i\leq n}(\max_{i\leq j\leq i+n-1} (T_j-j)+i)+n-1$。

简单放缩有 $ans=\min_{1\leq i\leq n}(\max_{i\leq j\leq 2\times n} (T_j-j)+i)+n-1$。

令 $S_j=T_j-j$

有 $ans=\min_{1\leq i\leq n}(\max_{i\leq j\leq 2\times n} S_j+i)+n-1$。

然后就可以维护后缀最大值有一个 $O(nm)$ 的做法。

但是这样是通不过的。

考虑一个 $j$ 对答案的影响为：

> 1. $j$ 是后缀最大值，在左边找到的第一个满足 $S_k>S_j$ 的 $k$，则 $i\in(k,x]$ 时可以取到 $j$ 那么答案最小就是 $S_j+k+n$。
>
> 2. $j$ 不是后缀最大值，则答案就是后缀最大值的答案。

考虑单调栈元素 $S_{p_1},S_{p_2},...,S_{p_m}$ 都是 $S$ 的后缀最大值。

则有 $ans= \min _{1\leq i\leq m-1} S_{p_i}+p_{i+1}+n-1$。

然后用线段树维护单调栈即可。

时间复杂度 $O(n\log^2n)$。

---

## 作者：under_the_time (赞：0)

## 题意

> 有一个 $n$ 个点的环（顺时针编号为 $1\sim n$），每个点上都有一个物品，第 $i$ 个物品的出现时间为 $T_i$。初始 $0$ 时刻你可以选择任意一个点出发，每个单位时间都可以顺时针方向移动一格或不动。如果你在的点上的物品已经出现，那么你可以拿走它。
>
> 现在有 $m$ 次修改，每次修改某一个 $T_i$ 的值，每一轮都需要求出拿走所有物品的最少时间。强制在线。

## 解法

首先破环成链，令 $T_{i+n}=T_i,i\in[1,n]$。最终的策略一定只需在环上走一圈，遇到物品如果还没有出现就等。如果需要走 $2$ 圈及以上，不如直接在起点等着，等到所有物品都会在到达前出现再出发走一圈。

枚举起点 $i$，那么终点就是 $i+n-1$。对于位置 $j,j\in[i,i+n-1]$，从 $i$ 出发到达它的时间为 $j-i$；想让物品 $j$ 在到达前出现，在 $i$ 上至少需要等待 $T_j-(j-i)$ 的时间。于是在 $i$ 上的等待时间为：
$$
\max^{i+n-1}_{j=i}T_j-j+i
$$
答案即为：
$$
\min^n_{i=1}(\max^{i+n-1}_{j=i}T_j-j+i)+n-1
$$
令 $S_j=T_j-j$，则化简后答案可以表示为
$$
n-1+\min^n_{i=1}\big(i+(\max^{2n}_{j=i}S_j)\big)
$$
注意到对于不同的 $i$，$j$ 之间的大小关系基本一致，所以考虑某一个 $j$ 在什么时候对答案产生贡献。我们找到满足 $S_k>S_j$ 的最右边的 $k$，则 $(k,j]$ 中的 $i$ 都在 $j$ 处取得最大值。$j$ 的贡献即为 $S_j+k+1$。令 $S$ 的后缀最大值集合 $S'=\{p_1,p_2,\cdots,p_k\}$，则答案为
$$
\min^k_{i=1}S_i+p_{i-1}+1
$$
利用类似单调栈的方法在线段树上维护这个部分的答案即可。

## 实现

线段树部分和 [P4198 楼房重建](https://www.luogu.com.cn/problem/P4198) 类似，只不过求和换成了取 $\max$。因为起点只在 $[1,n]$ 中，所以每个区间维护左子区间答案即可。线段树维护一个答案和 $S_j$ 的最大值，合并子区间信息时用右区间的最大值在左区间中二分即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 5;
#define lson l,mid,rt << 1
#define rson mid + 1,r,rt << 1 | 1
int ans[maxn << 2], mx[maxn << 2];
int k, T[maxn];
const int inf = 0x3f3f3f3f;
int query(int l,int r,int rt) {
    if (l == r) 
        return l + max(k,mx[rt]);
    int mid = l + r >> 1;
    if (mx[rt << 1 | 1] >= k) 
        return min(ans[rt],query(rson));
    return min(mid + k + 1,query(lson));
}
void update(int l,int r,int rt) {
    int mid = l + r >> 1;
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    k = mx[rt << 1 | 1];
    ans[rt] = query(lson);
}
int now;
void modify(int l,int r,int rt) {
    if (l == r) { mx[rt] = T[l], ans[rt] = T[l] + l; return ; }
    int mid = l + r >> 1;
    if (now <= mid) modify(lson);
    else modify(rson);
    update(l,r,rt);
}
void build(int l,int r,int rt) {
    if (l == r) return ans[rt] = T[l] + l, mx[rt] = T[l], void(0);
    int mid = l + r >> 1;
    build(lson); build(rson); update(l,r,rt);
}
int n,m,P;
int main() {
    scanf("%d%d%d",&n,&m,&P);
    for (int i = 1;i <= n;i ++)
        scanf("%d",&T[i]), T[i + n] = (T[i] -= i) - n;
    build(1,n << 1,1);
    int lst = ans[1] + n - 1;
    printf("%d\n",lst);
    for (int i = 1,x,y;i <= m;i ++) {
        scanf("%d%d",&x,&y);
        if (P) x ^= lst, y ^= lst;
        T[x + n] = (T[now = x] = y - x) - n;
        modify(1,n << 1,1);
        now = x + n; modify(1,n << 1,1);
        printf("%d\n",lst = ans[1] + n - 1);
    }
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

容易发现最优解里一定存在一种方案，为「一开始停留一段时间，然后一直往下一个取」的形式。通过调整容易证明。

断环成链，直接列出式子：

$$\text{ans}=\min\limits_{n\le i<2n}\max\limits_{i-n< j\le i}a_j-j+i$$

令 $t_i=a_i-i(1\le i\le 2n)$，然后让 $i$ 平移 $n-1$ 位，化简后得：

$$\text{ans}=(n-1)+\min\limits_{1\le i\le n}\left(i+\max\limits_{i\le j\le 2n}a_j\right)$$

相当于对每个 $i$，求出其后缀最大值 $a_j$。反过来，考虑每个 $j$，其作为 $i$ 的后缀最大值**最小的 $i$**。那么要求的就是 $j$ 前面第一个满足 $a_i>a_j$ 的 $i+1$，可以单调栈解决。

现在有了修改，直接线段树维护单调栈（楼房重建线段树）即可。

复杂度 $O((n+m)\log^2 n)$。

```cpp
// Problem: #2495. 「AHOI / HNOI2018」转盘
// Contest: LibreOJ
// URL: https://loj.ac/p/2495
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Med;

const int N = 1e5 + 100;
const int inf = 0x3f3f3f3f;

int n, m, op, a[N << 1];
int mx[N << 3], tr[N << 3];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)

int qry(int l, int r, int c, int x) {
	if (l == r) return mx[x] <= c ? inf : c + l + 1;
	if (mx[rs] < c) return qry(l, mid, c, ls);
	return min(tr[x], qry(mid + 1, r, c, rs));
}

void pup(int l, int r, int x) {
	mx[x] = max(mx[ls], mx[rs]);
	tr[x] = qry(l, mid, mx[rs], ls);
}

void upd(int l, int r, int p, int c, int x) {
	if (l == r) return mx[x] = c, void();
	if (p <= mid) upd(l, mid, p, c, ls);
	else upd(mid + 1, r, p, c, rs);
	pup(l, r, x);
}

void solve() {
	cin >> n >> m >> op;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], a[i + n] = a[i];
	for (int i = 1; i <= (n << 1); i++)
		upd(1, n << 1, i, a[i] - i, 1);
	int lst = 0;
	cout << (lst = min(1 + mx[1], tr[1]) + n - 1) << '\n';
	while (m--) {
		int x, y; cin >> x >> y;
		x ^= op * lst, y ^= op * lst;
		upd(1, n << 1, x, y - x, 1), upd(1, n << 1, x + n, y - n - x, 1);
		cout << (lst = min(1 + mx[1], tr[1]) + n - 1) << '\n';
	}
}

bool Mbe;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Med - &Mbe) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

