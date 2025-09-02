# [NOI Online #2 提高组] 子序列问题

## 题目背景

2s 512M

## 题目描述

给定一个长度为 $n$ 的正整数序列 $A_1$, $A_2$, $\cdots$, $A_n$。定义一个函数 $f(l,r)$ 表示：序列中下标在 $[l,r]$ 范围内的子区间中，不同的整数个数。换句话说，$f(l,r)$ 就是集合 $\{A_l,A_{l+1},\cdots,A_r\}$ 的大小，这里的集合是不可重集，即集合中的元素互不相等。

现在，请你求出 $\sum_{l=1}^n\sum_{r=l}^n (f(l,r))^2$。由于答案可能很大，请输出答案对 $10^9 +7$ 取模的结果。

## 说明/提示

对于 $10\%$ 的数据，满足 $1 \leq n \leq 10$；

对于 $30\%$ 的数据，满足 $1 \leq n \leq 100$；

对于 $50\%$ 的数据，满足 $1\leq n \leq 10^3$；

对于 $70\%$ 的数据，满足 $1 \leq n \leq 10^5$；

对于 $100\%$ 的数据，满足 $1\leq n\leq 10^6$，集合中每个数的范围是 $[1,10^9]$。

## 样例 #1

### 输入

```
4
2 1 3 2```

### 输出

```
43```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
6```

# 题解

## 作者：OMG_wc (赞：78)

设 $g(r)=\sum\limits_{l=1}^{r}f(l,r)^2$，那么本题要求的答案为 $\sum\limits_{r=1}^n g(r)$。

思路很简单的，循环枚举 $r$，然后用数据结构在 $O(\log n)$ 的时间内求出 $g(r)$ （当然得利用 $g(r-1)$ 的值），这样总时间复杂度为 $O(n \log n)$。

首先预处理一个`last` 数组：`last[i]` 表示上一个等于 $a_i$ 的位置，不存在就为 $0$。用`map`可能会卡常，建议离散化。

下面考虑 $r\Rightarrow r+1$ 的变化：

此时新增了一个数 $a_{r+1}$ ，在 $l\in[last_{r+1}+1,r+1]$ 的范围内的 $f(l,r+1)=f(l,r)+1$ ，因为这部分原本没有 $a_{r+1}$ 这个数，而其余部分是不变的，对 $g$ 也毫无影响。

那么 $g(r+1)-g(r)=\sum\limits_{l=last_{r+1}+1}^{r+1}f(l,r+1)^2-f(l,r)^2=\sum\limits_{l=last_{r+1}+1}^{r+1}(2f(l,r)+1)=2\sum\limits_{l=last_{r+1}+1}^{r+1}f(l,r)+r+1-last_{r+1}$

那么对于当前固定的 $r$，我们的数据结构需要能查询 $f(l,r)$ 的一段区间和，其中 $l\in[last_{r+1}+1,r+1]$ ，并且让这段区间加 $1$ 。

线段树容易在 $10^6$ 范围内卡常，用两个树状数组就能解决区间求和、区间查询的问题，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 1000005;
LL c1[N], c2[N];
LL sum(int x) {
    LL res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        res += c1[i] * (x + 1) - c2[i];
    }
    return res;
}
void add(int x, int d, int n) {
    for (int i = x; i <= n; i += i & -i) {
        c1[i] += d;
        c2[i] += (LL)d * x;
    }
}
int a[N], b[N], d[N], last[N];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i - 1] = a[i];
    }
    sort(b, b + n);
    int m = unique(b, b + n) - b;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b, b + m, a[i]) - b;
        last[i] = d[a[i]];
        d[a[i]] = i;
    }
    LL ans = 0, now = 0;
    for (int i = 1; i <= n; i++) {
        now += i - last[i] + 2 * (sum(i) - sum(last[i]));
        now %= mod;
        ans += now;
        add(last[i] + 1, 1, n);
        add(i + 1, -1, n);
    }
    printf("%lld\n", ans % mod);
    return 0;
}
```









---

## 作者：BFqwq (赞：49)

第二场 NOIol 的 T2，其实挺套路的，直接考虑 dp。

我们考虑当数列的长度为 $i-1$ 的时候，我们在数列的尾部加上一个数 $a_i$。

然后考虑这个长度为 $i$ 的数列，将它的贡献分为与 $a_i$ 有关和与 $a_i$ 无关。

对于与 $a_i$ 无关的我们显然在前面计算好了，

而与 $a_i$ 有关的区间就是 $[1,i],[2,i]\ldots [i,i]$。

然后我们考虑在计算 $a_{i-1}$ 的时候顺便维护区间 $[1,i-1],[2,i-1]\ldots [i-1,i-1]$ 区间的答案。

假设 $a_i$ 这个**数值**上一次出现的位置为 $lst_{a_i}$（如果未出现过就是 $0$），

那么我们发现，对于 $[lst_{a_i}+1,i-1]\ldots [i-1,i-1]$ 的区间，原本的区间中是没有 $a_i$ 的，故在扩张时它们的答案会加一。

然后对于 $[1,i-1]\ldots [lst_{a_i},i-1]$ 的区间，它们已经包含了 $a_i$，故扩张时答案不变。

然后对于 $[i,i]$ 这一区间，元素个数显然是 $1$。

于是我们就想到用一种支持区间加和区间平方和的数据结构来维护贡献数组。

每次修改时，就是将 $lst_{a_i}+1$ 到 $i$ 位置的数加一，

然后当前序列与 $a_i$ 有关的贡献之和就是全局的平方和。

至于如何维护平方和，这又是一个套路。

直接对公式平方和展开，得到

$$\sum_{i=l}^r (t_i+v)^2=\sum_{i=l}^r t_i^2+\sum_{i=l}^r 2\times t_i\times v+\sum_{i=l}^r v^2$$

所以我们只需要维护平方和以及和。

于是就很自然的想到了线段树维护。

（不过这个题的数据范围比较大，所以不保证线段树不被卡常，不过至少我的程序洛谷能 AC）

（当然这题也有其他的维护方法，比如树状数组等，可以减小常数）

```cpp
#include <bits/stdc++.h>
//#define int long long 
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200],str[200];int tt;
inline void print(register long long x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int p=1e9+7;
const int maxn=1e6+5;
struct seg{
	int tag,sum2,sum;
}t[maxn<<2];
inline void pushdown(register int o,register int l,register int r){
	if(!t[o].tag||l==r) return;
	int mid=l+r>>1;
	t[o<<1].sum2+=(2ll*t[o].tag*t[o<<1].sum%p+1ll*t[o].tag*t[o].tag%p*(mid-l+1)%p)%p;
	if(t[o<<1].sum2>p) t[o<<1].sum2-=p;
	t[o<<1|1].sum2+=(2ll*t[o].tag*t[o<<1|1].sum%p+1ll*t[o].tag*t[o].tag%p*(r-mid)%p)%p;
	if(t[o<<1|1].sum2>p) t[o<<1|1].sum2-=p;
	t[o<<1].sum+=1ll*t[o].tag*(mid-l+1)%p;
	if(t[o<<1].sum>p) t[o<<1].sum-=p;
	t[o<<1|1].sum+=1ll*t[o].tag*(r-mid)%p;
	if(t[o<<1|1].sum>p) t[o<<1|1].sum-=p;
	t[o<<1].tag+=t[o].tag;
	t[o<<1|1].tag+=t[o].tag;
	t[o].tag=0;
}
inline void change(register int o,register int l,register int r,register int ql,register int qr,register int v){
	if(ql<=l&&r<=qr){
		t[o].sum2+=(2ll*t[o].sum*v%p+1ll*v*v*(r-l+1)%p)%p;
		if(t[o].sum2>p) t[o].sum2-=p;
		t[o].sum+=1ll*v*(r-l+1)%p;
		if(t[o].sum>p) t[o].sum-=p;
		t[o].tag+=v;
		if(t[o].tag>p) t[o].tag-=p;
		return ; 
	}
	pushdown(o,l,r);
	int mid=l+r>>1;
	if(ql<=mid) change(o<<1,l,mid,ql,qr,v);
	if(mid<qr) change(o<<1|1,mid+1,r,ql,qr,v);
	t[o].sum=(t[o<<1].sum+t[o<<1|1].sum)%p;
	t[o].sum2=(t[o<<1].sum2+t[o<<1|1].sum2)%p;
	return;
}
int a[maxn],ans,n,lsh[maxn],len,lst[maxn];
signed main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++){
		lsh[i]=a[i]=read();
	}
	sort(lsh+1,lsh+n+1);
	len=unique(lsh+1,lsh+n+1)-lsh-1;
	for(register int i=1;i<=n;i++){
		a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
		change(1,1,n,lst[a[i]]+1,i,1);
		ans+=t[1].sum2;
		if(ans>p) ans-=p; 
		lst[a[i]]=i;
	}
	print((ans%p+p)%p);
	return 0;
}
```

---

## 作者：codecode (赞：25)

考场上最后一分钟写完了正解，结果提交的一瞬间刚好结束。。。

这里就来分享一下考场上的思路吧。

------------

**题解：**

首先，对于区间去重后的元素个数，有一种套路化的递推方法：

- 设 $\operatorname{pre}(i)$ 表示 $a_i$ 上一次出现的位置

- 则 $f(l,i)=\begin{cases}1\quad\quad\quad\quad\quad\quad\;\;\; l=i\\f(l,i-1)\quad\quad\quad l\leq\operatorname{pre}(i)\\f(l,i-1)+1\quad \text{else}\end{cases}$

如何求出 $\operatorname{pre}$ 数组？可以利用桶排序的技巧，离散化后递推

~~由于不好解释，直接放代码了~~

```
for(int i=1;i<=n;i++)
	cin>>a[i],b[i]=a[i];
sort(b+1,b+n+1);
cnt=unique(b+1,b+n+1)-b-1;
for(int i=1;i<=n;i++){
	int pos=lower_bound(b+1,b+cnt+1,a[i])-b;
	a[i]=pos;
} //以上为离散化
for(int i=1;i<=n;i++){
	if(pree[a[i]])pre[i]=pree[a[i]]; //pree 数组指向 a[i] 上次出现的位置
	pree[a[i]]=i;
}
```

然后这道题 $f$ 平方了。设 $g=f^2$，带到上面的递推式中，可得

$$g(l,i)=\begin{cases}1\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\;\;\;\; l=i\\g(l,i-1)\quad\quad\quad\quad\quad\quad\quad\quad\;\; l\leq\operatorname{pre}(i)\\g(l,i-1)+2f(l,i-1)+1\quad \text{else}\end{cases}$$

我们需要求 

$$T(i)=\sum_{j=1}^{i}g(j,i)$$

函数的前缀和，这部分可以直接扫描 $i$ 累加，问题变成了如何快速地从 $T(i-1)$ 递推到 $T(i)$。

直接把 $g$ 带入递推式，可得

$$\begin{aligned}T(i)&=\sum_{j=1}^{\operatorname{pre}(i)}g(j,i-1)+\sum_{j=\operatorname{pre}(i)+1}^{i-1}\left(g(j,i-1)+2f(j,i-1)+1\right)+1\\&=\sum_{j=1}^{i-1}g(j,i-1)+2(S_{i-1}(i-1)-S_{i-1}(\operatorname{pre}(i)))+\left(i-1-(\operatorname{pre}(i)+1)+1\right)+1\\&=T(i-1)+2(S_{i-1}(i-1)-S_{i-1}(\operatorname{pre}(i)))+i-\operatorname{pre}(i)\end{aligned}$$

其中 $S_i(j)=f(1,i)+f(2,i)+\cdots+f(j,i)$。

计算 $T(i)$ 的瓶颈成为了计算 $S_i(j)$。

当 $i\leftarrow i+1$ 时，由 $S$ 的定义及 $f$ 的递推式可知，这等价于在数列 $S$ 的一部分加上了一个等差数列。

具体地说，$i\leftarrow i+1$ 时对于 $S$ 需要执行以下一系列操作

1. 给 $S_i(\operatorname{pre}(i)+1)$ 加上 $1$，给 $S_i(\operatorname{pre}(i)+2)$ 加上 $2$，……，给 $S_i(i-1)$ 加上 $i-\operatorname{pre}(i)-1$；

2. 给 $S_i(i)$ 赋值 $S_i(i-1)+1$。


------------

所以，我们需要写一个数据结构，支持

- 区间加等差数列

- 单点修改

- 前缀和查询

显然树状数组，线段树都可以做到。这里我写的树状数组，常数较小。

树状数组在处理区间加等差数列时，只能对原数列差分，将区间加等差数列变为区间加。

树状数组处理区间加，常规方法是对原数列**再差分一次**。

也就是说，我们需要用树状数组维护

- 区间加

- 前缀和查询

这是可以做到的~~当时线段树1我就这么做的~~：

> 设待处理数列为 $A$，其差分数列为 $B_i=A_i-A_{i-1}$。
>
> 则 
>
> $$\sum_{i=1}^{n}A_i=(n+1)\sum_{i=1}^{n}B_i-\sum_{i=1}^{n}iB_i$$
>
> 维护数列 $B$ 和数列 $iB$ 的前缀和即可。

也就是说，我们可以在 $\Theta(\log n)$ 的时间复杂度内将 $S_i$ 递推到 $S_{i+1}$，即将 $T_i$ 递推到 $T_{i+1}$。

所以总时间复杂度 $\Theta(n\log n)$。

但是常数较大，需注意优化。


------------

这道题难度还是比较大的（可能是我太弱了），个人意见：难度评级 蓝~紫

---

## 作者：tzc_wk (赞：24)

> 题意：有一个长度为 $n$ 的序列 $a$，定义 $f(l,r)$ 为 $a$ 序列中 $[l,r]$ 区间不同数的个数。求：

> $$\sum\limits_{l=1}^n \sum\limits_{r=l}^n f(l,r)^2 \bmod (10^9+7)$$

> $1 \leq n \leq 10^6$

插句题外话，一定要注意 $\texttt{freopen}$，我因为这个 bao0 了 /wn

首先值域是 $10^9$ 就暗示着需要离散化。

我们枚举左端点 $l$，考虑当左端点为 $l$ 的区间对答案的贡献，把这些贡献全部加在一起就是最终的答案。

题目就简化为求 $\sum\limits_{i=l}^n f(l,i)^2$

对于 $[l,n]$ 中出现过的**数** $x$，我们找出它在 $[l,n]$ 中出现**最靠左的位置** $pos_x$。我们记 $t_i$ 为 $f(l,i)$ 的值。**倒着循环** $l$，考虑左端点从 $l+1$ 变为 $l$ 的影响，假设原来的 $pos_{a_l}$ 为 $l'$，那么会发生以下两件事：

1. $pos_{a_l}$ 会变为 $l$
2. $t_l,t_{l+1},\dots,t_{l'-1}$ 的值将全部加 $1$。因为 $a_l$ 这个数在 $[l+1,l],[l+1,l+1],\dots,[l+1,l'-1]$ 中没有出现过，而在 $[l,l],[l,l+1],\dots,[l,l'-1]$ 出现过了。

那么现在就变成了下面的问题：

- 区间加某个数
- 求区间中所有数平方的和

这个可以用线段树来实现。考虑区间加上某个数 $k$，那么平方和变为：

$$(a_l+k)^2+(a_{l+1}+k)^2+\dots+(a_r+k)^2$$

$$=a_l^2+2ka_l+k^2+a_{l+1}^2+2ka_{l+1}+k^2+\dots+a_r^2+2ka_r+k^2$$

$$=(a_l^2+a_{l+1}^2+\dots+a_r^2)+2k(a_l+a_{l+1}+\dots+a_r)+(r-l+1) \times k^2$$

维护区间平方和和区间和就可以做到 $\mathcal O(1)$ 更新了。

代码（常数有点大，开了 O2）：

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
const int MOD=1e9+7;
int n,a[1000005],key[1000005],hs[1000005],cnt=0;
struct node{
	int l,r;
	int sum,sqr;
	int lz;
} s[1000005<<2];
inline void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;
	if(l==r)	return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
inline void pushup(int k){
	s[k].sqr=s[k<<1].sqr+s[k<<1|1].sqr;
	if(s[k].sqr>MOD)	s[k].sqr-=MOD;
	s[k].sum=s[k<<1].sum+s[k<<1|1].sum;
	if(s[k].sum>MOD)	s[k].sum-=MOD;
}
inline void pushdown(int k){
	if(!s[k].lz)	return;
	s[k<<1].sqr=(s[k<<1].sqr+2*s[k].lz*s[k<<1].sum+(s[k<<1].r-s[k<<1].l+1)*s[k].lz*s[k].lz)%MOD;
	s[k<<1].sum=(s[k<<1].sum+(s[k<<1].r-s[k<<1].l+1)*s[k].lz)%MOD;
	s[k<<1].lz+=s[k].lz;
	s[k<<1|1].sqr=(s[k<<1|1].sqr+2*s[k].lz*s[k<<1|1].sum+(s[k<<1|1].r-s[k<<1|1].l+1)*s[k].lz*s[k].lz)%MOD;
	s[k<<1|1].sum=(s[k<<1|1].sum+(s[k<<1|1].r-s[k<<1|1].l+1)*s[k].lz)%MOD;
	s[k<<1|1].lz+=s[k].lz;
	s[k].lz=0;
}
inline void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].sqr=(s[k].sqr+2*x*s[k].sum+(s[k].r-s[k].l+1)*x*x)%MOD;
		s[k].sum=(s[k].sum+(s[k].r-s[k].l+1)*x)%MOD;
		s[k].lz+=x;
		return;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid)		modify(k<<1,l,r,x);
	else if(l>mid)	modify(k<<1|1,l,r,x);
	else			modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
inline int query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r){
		return s[k].sqr;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid)		return query(k<<1,l,r);
	else if(l>mid)	return query(k<<1|1,l,r);
	else			return (query(k<<1,l,mid)+query(k<<1|1,mid+1,r))%MOD;
}
int lst[1000005];
signed main(){
	n=read();
	fz(i,1,n)	a[i]=read();
	fz(i,1,n)	key[i]=a[i];
	sort(key+1,key+n+1);
	fz(i,1,n)	if(key[i]!=key[i-1])	hs[++cnt]=key[i];
	fz(i,1,n)	a[i]=lower_bound(hs+1,hs+cnt+1,a[i])-hs;
	fz(i,1,cnt)	lst[i]=n+1;
	build(1,1,n);
	int ans=0;
	fd(i,n,1){
		modify(1,i,lst[a[i]]-1,1);
		ans=(ans+query(1,i,n))%MOD;
//		cout<<query(1,i,n)<<endl;
		lst[a[i]]=i;
	}
	cout<<ans<<endl;
	return 0;
}
/*
6
1 2 1 3 2 1
111
*/
```

---

## 作者：白木偶君 (赞：24)

### update 5.9 ，更新一下题解，请管理大大友善通过

**--------以下为正文--------**

## 我觉得大佬们的题解都比较复杂
## 因为线段树/树状数组里存的都是很复杂的东西
## 我就比较直接，线段树里存的就是 $f(l,r)$

**因为真的不需要那些很复杂的拆分求单点贡献**

****

### 1. $O(n)$ 倒序枚举 $l$ （顺序枚举 $r$ 也行，看个人习惯）

### 2. 维护一个 $last[i]$ 表示i这个颜色上一次出现的位置。
>**若这个颜色前面没有出现，那么我让 $last[i]$ 默认为 $n+1$**

### 3. 线段树第$r$个位置存的是以当前枚举的 $l$ 终点为 $r$  的$f(l,r)$。
>**我们要求的是$\sum_{l=1}^n\sum_{r=l}^n f(l,r)^2$**

>**这里我们先求$\sum_{l=1}^n\sum_{r=l}^n f(l,r)$**

>**那么很显然对于每一个不同的 $l$ 求 $query(1,1,n)$**

>**线段树优化的就是后面那个 $\sum_{r=l}^n$的过程**

>**枚举到一个$l$时,则线段树里存的是$\sum f(l,r)$**

>**最终要求答案的是 $\sum f(l,r)^2$**

>**这个其实就在下一步就能解决**


### 4.每当要枚举下一个 $l$ 之前，就把当前的 $l$ 的贡献加上
>令$ans[l]$是$\sum_{r=l}^nf(l,r)^2$

>怎么样从$\sum_{r=l}^nf(l,r)$求$ans[l]$呢？

>>**来一波学过初中数学就能看懂的东西**

>>**$\because(x+1)^2=x^2+2x+1$**

>>**$\therefore(x+1)^2-x^2=2x+1$**

>>**更新后-更新前=$2x+1$**

>>**那么当线段树里的$x$要更新$+1$时**

>>**实际上要求的答案增加了 $2\sum{x+1}$**

>>**也就是增加了$2\sum{x}+2len$ ($len$ 是区间长度), 在代码中体现为**

>**$ans[l]=ans[l+1]+2*query(1,1,last[a[l]]-1)+last[a[l]]-l$**

>>其实$query(1,1,last[a[l]-1])$ 就是  $\sum{x}$

>>$last[a[l]]-l$ 就是 $2len$

>**最后 $update(1,l,last[a[l]]-1)$**

>**因为$a[l]$这个颜色对答案的影响最多只能到$last[a[l]]-1$**

>**后面的区间已经有了这个颜色，就不会重复增加**

### 5.每个 $l$ 的答案加起来就是总答案

>#### $ans[l]=\sum_{r=l}^n f[l][r]$ (线段树$O(logn)$)
>#### $ANS=\sum_{l=1}^n ans[l]$ (枚举$l$ $O(n)$)

**说到这，我们发现**

**其实没有必要开数组ans,只要一边求一边统计就好啦**

**我的代码里$op$就是那个$ans[l]$**


****


复杂度$O(nlogn)$

最后注意一下要开long long

运算要取膜

还有细节问题看代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
#define int long long
const int N=1e6+5,mod=1e9+7;
inline int read(){
    int x=0; char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48); ch=getchar();}
    return x;
}
int n,a[N],b[N];
#define ls p<<1
#define rs p<<1|1
#define mid ((l(p)+r(p))>>1)
struct Seg{
	int l,r,sum,add;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define sum(x) tree[x].sum
	#define add(x) tree[x].add
	#define len(x) (r(x)-l(x)+1)
}tree[N<<2];
void build(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r)return;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
inline void pushdown(int p){
	sum(ls)+=add(p)*len(ls);
	sum(rs)+=add(p)*len(rs);
	add(ls)+=add(p);
	add(rs)+=add(p);
	add(p)=0;
}
void update(int p,int l,int r,int d){
	if(l<=l(p)&&r(p)<=r){
		sum(p)+=len(p)*d;
		add(p)+=d;
		return;
	}
	if(add(p))pushdown(p);
	if(l<=mid)update(ls,l,r,d);
	if(r>mid)update(rs,l,r,d);
	sum(p)=sum(ls)+sum(rs);
}
int query(int p,int l,int r){
	if(l<=l(p)&&r(p)<=r)return sum(p);
	if(add(p))pushdown(p);
	int ans=0;
	if(l<=mid)ans+=query(ls,l,r);
	if(r>mid)ans+=query(rs,l,r);
	return ans;	
}
int last[N];
signed main(){
	
	//freopen("sequence.in","r",stdin);
	//freopen("sequence.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+1+n);
	int len=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+len,a[i])-b,last[i]=n+1;
	build(1,1,n);
	ll op=0,ans=0;
	for(int l=n;l>=1;l--){
		op=(op+2*query(1,1,last[a[l]]-1)+(last[a[l]]-l))%mod;
		update(1,l,last[a[l]]-1,1);
		last[a[l]]=l;
		ans=(ans+op)%mod;
	}
	cout<<ans<<endl;
}
```

---

## 作者：皎月半洒花 (赞：17)

我来说一个很不正常的解法…不正常在他特别麻烦…特别难调…

我的做法是先算出全部区间的贡献：

$$\sum_{i=1}^n\sum_{j=i}^n(j-i)^2=\sum_{i=1}^n(1^2+2^2+3^2+\cdots +(n-i)^2)$$

也就是

$$\sum_{i=1}^n\frac{(n-i)(n-i+1)(2\times (n-i)+1)}{6}$$

然后考虑减掉那些不合法的。具体的，预处理出每个位置左边最近的那个相同颜色的下标 $pre_x$ 。那么 $x$ 和 $pre_x$ 会对左端点在 $1\sim pre_x$ ，右端点在 $x+1\sim n$ 的区间产生贡献。贡献怎么算呢？

考虑假设一个区间长为 $L$ 。那么第一组 $(pre_x,x)$ 出现时，会有

$$L^2\to (L-1)^2=L^2-2L+1=L^2-(2L-1)$$

第二组出现时：

$$(L-1)^2\to (L-2)^2=(L-1)^2-2(L-1)+1=(L-1)^2-(2L-3)$$

以此类推，当一个区间存在 $t$ 个重复颜色时（即假设某种颜色的数量为 $c$，那么这种颜色的「重复颜色数」为 $c-1$），他需要减去 $(2\cdot t\cdot L-t^2)$ 的贡献。

考虑拆成两半做：

1、$2\cdot t\cdot L$

需要枚举每个位置 $i$ ，设 $j=pre_i$ 。记 $p=\max\{(n-i+1),i\},q=\min\{i,(n-i+1)\}$ 。即 $p$ 是左右两边较长的那个区间，$q$ 是较短的那个。同时记当前区间长度为 $d$，即 $d=i-pre_i$ 。以下默认省略前面的系数 $2$ 。

那么需要再分三类讨论会被产生贡献的区间长度 $L$ ，以下在计算 $L$ 时，用 $d+\Delta$ 来代替：

> （1）$d+1\leq L\leq q+d$ 
>
> 对于每个这样的 $L$ ，会存在 $L-d$ 个区间产生合法贡献，所以这部分贡献就是

$$\sum_{L=d+1}^{q+d}L\cdot i=\sum_{i=1}^{q}(d+i)\cdot i$$

> 可以通过预处理 $\sum i$ ，$\sum i^2$ 快速计算。
>
> （2） $q+d+1\leq L\leq p+d$ 
>
> 对于每个这样的 $L$ ，由于不能全部取到，所以至多会有 $q$ 个。所以这部分贡献是：

$$\sum_{L=q+d+1}^{p+d}L\cdot q=\sum_{i=q+1}^{p}(d+i)\cdot q$$

> 这部分比较好算。
>
> （3） $p+d+1\leq L\leq n$
>
> 对于每个这样的 $L$ ，发现最多只能取到 $n-L+1$ 次。所以这部分贡献是

$$\sum_{L=p+d+1}^{n}L\cdot (n-L+1)=\sum_{i=p+1}^{n-d}(n-d-i+1)\cdot (d+i)$$

> 这一部分同样可以通过预处理来快速计算。

综上，这一部分的复杂度是排序外线性。

2、$-t^2$ 

设 $i$ 右边第一个和 $i$ 同颜色的元素为 $r_i$ 。

也就是现在把问题转化成了「{区间内重复出现的数字个数 $-1$ 的平方和」。考虑扫描线。一开始将所有的数都加进线段树。从左开始，每次都删掉一个最左边的元素 $i$。如果这个元素的颜色依旧出现在后面的序列中，那么可以知道对于所有右端点 $\geq r_i$ 的区间，都会少掉一个 $(i, r_i)$ 组成的 `pair`，也就是会少掉一个重复颜色的元素。所以就是后缀减 $-1$ and 询问后缀的平方和，线段树维护即可。

这一部分复杂度 $O(n\log n)$ 。   

如何卡常：

1、不要用 `map` .

2、(mayaohua 在 uoj 群里的高论)发现中间，一段区间内部的平方的和本质上是不会爆 `long long` 的，所以可以减少取模次数。

Upd: 发现代码里最难懂的部分没有注明 `add(),dec(),addn(),decn()` 都是什么…我的锅。


```cpp
template <typename T>
il void add(T &x, T y, ll mod = P){
    x += y ; x = x >= mod ? x - mod : x ;
}
template <typename T>
il void dec(T &x, T y, ll mod = P){
    x -= y ; x = x < 0 ? x + mod : x ;
}
template <typename T>
il T addn(T x, T y, ll mod = P){
    x += y ; return (x = x > mod ? x - mod : x) ;
}
template <typename T>
il T decn(T x, T y, ll mod = P){
    x -= y ; return (x = x < 0 ? x + mod : x) ;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
int val[N] ;

ll s[N * 3] ;
ll t[N * 3] ;
ll tg[N * 3] ;

void build(int rt, int l, int r){
    if (l == r){
        s[rt] = val[l]  ;
        t[rt] = s[rt] * s[rt] ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    build(ls, l, mid) ;
    build(rs, mid + 1, r) ;
	s[rt] = s[ls] + s[rs] ;
	t[rt] = t[ls] + t[rs] ;
}
void _down(int rt, int l, int r){
    if (tg[rt]){
        ll p = tg[rt] * tg[rt] % P ;
        ll pr = r - ((l + r) >> 1) ;
        ll pl = ((l + r) >> 1) - l + 1 ;
        tg[ls] += tg[rt], tg[rs] += tg[rt] ;
        dec(t[ls], decn(2ll * s[ls] * tg[rt] % P, p * pl)) ;
        dec(t[rs], decn(2ll * s[rs] * tg[rt] % P, p * pr)) ;
        dec(s[ls], tg[rt] * pl % P) ; dec(s[rs], tg[rt] * pr % P) ; tg[rt] = 0 ;
    }
}
void update(int rt, int l, int r, int ul, int ur){
    if (ul <= l && r <= ur){
        dec(t[rt], decn(2ll * s[rt] % P, 1ll * (r - l + 1))) ;
        dec(s[rt], 1ll * (r - l + 1)) ; tg[rt] += 1 ; return ;
    }
    int mid = (l + r) >> 1 ; _down(rt, l, r) ;
    if (ul <= mid) update(ls, l, mid, ul, ur) ;
    if (ur > mid) update(rs, mid + 1, r, ul, ur) ;
    s[rt] = s[ls] + s[rs] ; t[rt] = t[ls] + t[rs] ;
}
ll query(int rt, int l, int r, int ul, int ur){
    if (ul <= l && r <= ur) return t[rt] ;
    int mid = (l + r) >> 1 ; ll res = 0 ; _down(rt, l, r) ;
    if (ul <= mid) res += query(ls, l, mid, ul, ur) ;
    if (ur > mid) res += query(rs, mid + 1, r, ul, ur) ;
    return res ;
}
int n ;
ll ans ;
ll res ;
ll sum1[N] ;
ll sum2[N] ;
int pos[N] ;
int nxt[N] ;
int buc[N] ;
int tmp[N] ;
int base[N] ;
ll fuck[M][M] ;

const ll Inv6 = 166666668ll ;

int main(){
    cin >> n ; int len ;
	for (int i = 1 ; i <= n ; ++ i)
		base[i] = tmp[i] = qr() ;
	sort(tmp + 1, tmp + n + 1) ;
	len = unique(tmp + 1, tmp + n + 1) - tmp - 1 ;
    for (int i = 1 ; i <= n ; ++ i)
        base[i] = lb(tmp + 1, tmp + len + 1, base[i]) - tmp ;
	for (int i = 1 ; i <= n ; ++ i){
        if (buc[base[i]]) pos[i] = buc[base[i]] ; buc[base[i]] = i ;
    }
    for (ll i = 1 ; i <= n ; ++ i)
        sum1[i] = addn(sum1[i - 1], i) ;
    for (ll i = 1 ; i <= n ; ++ i)
		sum2[i] = addn(sum2[i - 1], i * i)  ;
    for (ll i = 0 ; i <= n ; ++ i)
        add(ans, (i + 1) * i * (2ll * i + 1ll) % P) ;
    ans = ans * Inv6 % P ;
    ll q, maxx, minx, m, p, len1, len2, d ;
    for (int i = 1 ; i <= n ; ++ i){
        if (!pos[i])
			continue ;
		q = n - i + 1 ;
        maxx = q, minx = pos[i] ;
        p = i - pos[i], m = n - p ;
        d = decn(sum1[m], sum1[maxx]) ;
        if (minx > maxx) swap(minx, maxx) ;
        len2 = m - maxx, len1 = maxx - minx ;
      	//part1
        add(res, sum2[minx]) ;
        add(res, sum1[minx] * p) ;
      	//part2
        add(res, p * minx * len1) ;
        add(res, minx * decn(sum1[maxx], sum1[minx], P) % P) ;
        //part3
        dec(res, 2ll * p * d % P) ;
        dec(res, p * p * len2 % P) ;
		add(res, 1ll * (n + 1) * d % P) ;
		dec(res, decn(sum2[m], sum2[maxx])) ;
        add(res, 1ll * (n + 1) * p * len2 % P) ;
        dec(ans, 2ll * res % P) ; res = 0 ;
	}
    if (n <= 1000){
        for (int i = 1 ; i <= n ; ++ i){
           	fill(buc, buc + n + 1, 0) ;
            for (int j = i ; j <= n ; ++ j){
                buc[base[j]] ++ ;
                fuck[i][j] = fuck[i][j - 1] + (buc[base[j]] > 1) ;
                add(ans, fuck[i][j] * fuck[i][j]) ;
            }
        }
        cout << ans << '\n' ; return 0 ;
    }
    fill(buc, buc + n + 1, 0) ;
    for (int i = n ; i >= 1 ; -- i)
        nxt[i] = buc[base[i]] ? buc[base[i]] : n + 1, buc[base[i]] = i ;
    fill(buc, buc + n + 1, 0) ;
    for (int i = 1 ; i <= n ; ++ i)
        buc[base[i]] ++, val[i] = val[i - 1] + (buc[base[i]] > 1) ;
    build (1, 1, n) ;
    for (int i = 1 ; i < n ; ++ i){
        add(ans, query(1, 1, n, i, n) % P) ;
        if (nxt[i] <= n) update(1, 1, n, nxt[i], n) ;
    }
    cout << ans << '\n' ; return 0 ;
}

```

---

## 作者：WYXkk (赞：7)

毒瘤题，我本地随机数据 2.5s，洛谷上跑得挺快，能卡时限过。

------

看到 $\sum\limits_{l=1}^n\sum\limits_{r=l}^n$，我们可以想到枚举 $r$，同时维护一些信息并从上一次的信息转移过来。

记 $a_i=f(i,r)$。

若记 $pre_i$ 为 $A_i$ 在 $A$ 中上一次出现的位置，第一次出现则记为 $0$，则我们发现，每次转移的时候，就是把 $a_{pre_r+1},\cdots,a_r$ 都加上 $1$。

然后众所周知线段树可以区间加区间平方和，于是我们只要想办法求出 $pre$ 数组即可。

我们可以建一堆 pair $s_i=(A_i,i)$，然后按先 $A_i$ 后 $i$ 排序。

此时 $A_i$ 相同的都归到了一起，且是按下标递增排列的。

于是若 $s_{i,1}=s_{i-1,1}$ 则 $pre_{s_{i,2}}=s_{i-1,2}$，否则 $pre_{s_{i,2}}=0$。

然后这题就搞完了。

由于线段树常数大，出题人可能会把它卡掉（

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=1000005;
int a[N],pre[N];
pair<int,int> s[N];
const ll p=1000000007;
ll sum[N*4],tag[N*4],sum2[N*4];
il void f(int k,int l,int r,ll v){tag[k]+=v;sum2[k]=(sum2[k]+sum[k]*v*2+(r-l+1)*v*v)%p;sum[k]=(sum[k]+(r-l+1)*v)%p;}
il void pd(int k,int l,int r){int mid=(l+r)>>1;f(k<<1,l,mid,tag[k]);f(k<<1|1,mid+1,r,tag[k]);tag[k]=0;}
il void pu(int k){sum[k]=(sum[k<<1]+sum[k<<1|1])%p;sum2[k]=(sum2[k<<1]+sum2[k<<1|1])%p;}
void change(int k,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return f(k,l,r,1);
	pd(k,l,r);int mid=(l+r)>>1;
	if(mid>=L) change(k<<1,l,mid,L,R);
	if(mid< R) change(k<<1|1,mid+1,r,L,R);
	return pu(k);
}
int main()
{
	//openf(sequence);
	int n=rd();
	F(i,1,n) rd(a[i]);
	F(i,1,n) s[i]=make_pair(a[i],i);
	sort(s+1,s+n+1);
	F(i,1,n) pre[s[i].second]=(s[i-1].first==s[i].first)?s[i-1].second:0;
	ll ans=0;
	F(i,1,n) {change(1,1,n,pre[i]+1,i);ans=(ans+sum2[1])%p;}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：ethan_zhou (赞：5)

本文latex在博客中没挂，请在博客页面查看[点这里](https://ethanblog.blog.luogu.org/p6477)


注：本题解看似很长~~其实是非常详细~~，实则思路简单粗暴，容易理解
## 暴力优化
最暴力的做法即为枚举每一对 $l$，$r$，并分别计算其 $f(l,r)$ 的值。但这样不知道会慢到哪里去了，所以我们考虑只滚动 $l$ 的值，并每次计算 $G(l)=\sum_{r=l}^{n} f^2(l,r)$ 的值。

## 转移
考虑 $G(l)$ 如何从 $G(l-1)$ 转移过来，由 $G$ 的定义：

$$
\begin{aligned}
G(l-1)&=&f^2(l-1,l-1)+&f^2(l-1,l)&&+\cdots +f^2(l-1,n)\cr
 G(l)&=&&f^2(l,l)&&+\cdots +f^2(l,n)
 \end{aligned}
 $$

不难发现，$G(l)$ 与 $G(l-1)$ 的唯一区别在于 $G(l)$ 中的每个 $f(l,i)$ 的值都少考虑了 $A_{l-1}$，即：
$$
\begin{aligned}
f(l-1,l-1)&\rightarrow0\cr
f(l-1,l)&\rightarrow f(l,l)\cr
f(l-1,l+1)&\rightarrow f(l,l+1)\cr
f(l-1,l+2)&\rightarrow f(l,l+2)\cr
&\vdots
\end{aligned}
$$
（$f(l-1,l-1)$ 彻底没了）。

所以为了计算 $A_{l-1}$ 对哪些 $f$ 有影响，我们可以先预处理出一个数组 $suf[i]$，表示 $A_x=A_i$ 且 $x>i$ 时，$x$ 的最小值（如果找不到这样的数，则 $suf[i]=n+1$）。

在从 $G(l-1)$ 转移到 $G(l)$ 的过程中，$A_{l-1}$ 的消失只对 $f(l-1,l-1\sim suf[l-1]-1)$ 有影响（会-1）,因为 $f(l-1,suf[l-1]\sim n)$ 中，都有超过两个与 $A_{l-1}$ 相等的元素，所以即使 $A_{l-1}$ 消失了，这些区间内数字的种类数也不会变。

即：
$$
f(l,r)=\left\{
\begin{aligned}
&f(l-1,r)+1&&(r\in[l-1,suf[l-1]-1])\cr
&f(l-1,r)&&(r\in[suf[l-1],n])
\end{aligned}
\right.
$$

这样，我们就可以通过线段树维护 $f(l-1,i)$，在 $\log(n)$ 的时间内，将每一个 $f(l-1,i)$ 转移成 $f(l,i)$（区间修改）。

但是这题答案要求的是 $f(l,i)$ 的平方和，怎么办？

## 由前缀和维护平方和


对于 $f(l-1,r)$ ,如果 $f(l,r)=f(l-1,r)-1$ 
那么
$$
\begin{aligned}
f^2(l,r)&=(f(l-1,r)-1)^2\cr
&=f^2(l-1,r)-(2f(l-1,r)-1)
\end{aligned}

$$
又因为
$$
\begin{aligned}
G(l-1)-G(l)=(f^2(l-1,l-1)&-0)+\cr
(f^2(l-1,l)&-f^2(l,l))+\cr
(f^2(l-1,l+1)&-f^2(l,l+1))+\cr
&\vdots\cr
(f^2(l-1,n)&-f^2(l,n))
\end{aligned}
$$

又因为刚才推出 $r\in[suf[l-1],n]$ 时，$f(l-1,r)$ 与 $f(l,r)$ 相同，所以式子中许多项被消掉了（式子中的 $n$ 变成了 $suf[l-1]$）
$$
\begin{aligned}
G(l-1)-G(l)=(f^2(l-1,l-1)&-0)+\cr
(f^2(l-1,l)&-f^2(l,l))+\cr
(f^2(l-1,l+1)&-f^2(l,l+1))+\cr
&\vdots\cr
(f^2(l-1,{\color{red}suf[l-1]-1})&-f^2(l,{\color{red}suf[l-1]-1}))
\end{aligned}
$$

又由于第二部分的结论（$r\in[l-1,suf[l-1]-1]$ 时，$f(l-1,r)=f(l,r)+1$）和这部分开头的结论，式子可以再次化简：
$$
\begin{aligned}
G(l)-G(l-1)&=&-(2f(l-1,l-1)&-1)\cr
&&-(2f(l-1,l)&-1)\cr
&&-(2f(l-1,l+1)&-1)\cr
&&&\vdots\cr
&&-(2f(l-1,suf[l-1]-1)&-1)\cr
&=&-2\times\sum_{r=l-1}^n f(l-1,r)+((suf[l-1])&-(l-1)+1)
\end{aligned}
$$

这个值可以直接用刚才维护 $f$ 的线段树来算出。

## 最终做法

**伪代码：**
```plain
计算出f(1,1)~f(1,n)的值，建线段树
tot=G(1)
ans=0
for l in [1,n]:
	ans+=tot;
	tot+=G(l+1)-G(l) (通过线段树计算)
	将 f(l,l)~f(l,suf[l]-1) 减1
```
**最终代码：（除去线段树极其简短）**
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const long long P=1000000007;
const long long MXN=1e6+5;
long long n;
long long arr[MXN],pool[MXN];
long long suf[MXN],nxt[MXN],diff[MXN];
long long tot=0,ans=0;

//线段树
struct stree{
	long long t[MXN<<2],tag[MXN<<2];
	inline long long ls(long long p){return p<<1;}
	inline long long rs(long long p){return (p<<1)|1;}
	inline void push_up(long long p){t[p]=t[ls(p)]+t[rs(p)];}
	inline void add_tag(long long p,long long l,long long r,long long k){
		tag[p]+=k;
		t[p]+=k*(r-l+1);
	}
	inline void push_down(long long p,long long l,long long r){
		if(!tag[p])return;
		long long mid=(l+r)>>1;
		add_tag(ls(p),l,mid,tag[p]);
		add_tag(rs(p),mid+1,r,tag[p]);
		tag[p]=0;
	}
	void build(long long p,long long l,long long r){
		tag[p]=0;
		if(l==r){
			t[p]=diff[l];
			return;
		}
		long long mid=(l+r)>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
		push_up(p);
	}
	void mo(long long p,long long l,long long r,long long al,long long ar,long long k){
		//区间是否合法
		if(al>ar)return;
		if(al<=l && r<=ar){
			add_tag(p,l,r,k);
			return;
		}
		long long mid=(l+r)>>1;
		push_down(p,l,r);
		if(al<=mid)mo(ls(p),l,mid,al,ar,k);
		if(ar>mid)mo(rs(p),mid+1,r,al,ar,k);
		push_up(p);
	}
	long long query(long long p,long long l,long long r,long long al,long long ar){
		//区间是否合法
		if(al>ar)return 0;
		if(al<=l && r<=ar)return t[p];
		long long mid=(l+r)>>1;
		push_down(p,l,r);
		long long res=0;
		if(al<=mid)res+=query(ls(p),l,mid,al,ar);
		if(ar>mid)res+=query(rs(p),mid+1,r,al,ar);
		return res;
	}
	
}tree;
void init(){
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		scanf("%lld",arr+i);
		pool[i]=arr[i];
		nxt[i]=n+1;
	}
	//离散化
	sort(pool+1,pool+1+n);
	long long cnt=unique(pool+1,pool+1+n)-pool-1;
	for(long long i=1;i<=n;i++)
		arr[i]=lower_bound(pool+1,pool+1+cnt,arr[i])-pool;
	//计算suf[i]
	for(long long i=n;i>=1;i--){
		suf[i]=nxt[arr[i]];
		nxt[arr[i]]=i;
	}
	//计算f(1,1)~f(1,n)
	memset(pool,0,sizeof(pool));
	for(long long i=1;i<=n;i++){
		diff[i]=diff[i-1];
		diff[i]+=((pool[arr[i]]++)==0);
		tot+=diff[i]*diff[i];
		tot%=P;
	}
	//建树
	tree.build(1,1,n);
}
void solve(){
	for(long long i=1;i<=n;i++){
		ans+=tot;
		ans%=P;
		tot-=(tree.query(1,1,n,i,suf[i]-1)*2)-(suf[i]-i);
		tot%=P;
		tree.mo(1,1,n,i+1,suf[i]-1,-1);
	}
}
int main(){
	/*freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);*/
	init();
	solve();
	ans%=P;
	if(ans<0)ans+=P;
	printf("%lld",ans);
	
	return 0;
}
```
## 易错点
1. 随时%p，如果不开 long long 小心越界
2. 计算 $suf[i]$ 的时候如果用类似桶排序的方法要离散化
3. 线段树中查询和修改操作要判断查询的区间是否合法，如果否，要直接退出（本题解中，为了写得更加方便，$suf[i]$ 的定义比较特别（如果找不到这样的数，则 $suf[i]=n+1$），所以如果不特判可能会re）
4. 线段树数组大小


---

## 作者：YoOXiii (赞：4)

考虑依次计算第i个数作为子序列右端点产生的贡献。

记 $num(i,j)$ 表示 $i-j$ 这段区间内互不相同的数个数。

记 $f_i$ 表示以 $i$ 结尾的子序列的贡献和。

用 $loc[a[r]]$ 表示数字 $a[r]$ 上一次出现的位置，则对于 $loc[x]$ 之前的位置 $l$ ，$num(l,r)=num(l,r-1)$ ；对于 $loc[a[r]]$ 之后的位置 $l$ ，$num(l,r)=num(l,r-1)+1$ 。由于涉及区间修改，考虑用线段树或者树状数组维护 $num$ 的值。

考虑用 $f_{r-1}$ 转移出 $f_r$，则有
$f_r - f_{r-1} = Σnum(l,r)^2-Σnum(l,r-1)^2$。其中 $l$ 从 $loc[x]+1$ 到 $r$。

由于 $num(l,r)=num(l,r-1)+1$ ，整理得 $f_r - f_{r-1} = Σnum(l,r) + ∑num(l,r-1)$。通过线段树区间查询即可。时间复杂度 $O(nlogn)$。

```cpp
#include <cstdio>
#include <map>

using namespace std;

#define int long long int

map<int,int> loc;

inline int read() {
	int x=0,f=1;
	char cr=getchar();
	while (cr>'9' || cr<'0') {
		if (cr=='-') f=-1;
		cr=getchar();
	}
	while (cr>='0' && cr<='9') {
		x=(x<<3)+(x<<1)+cr-'0';
		cr=getchar();
	}
	return x*f;
}

const int maxn=1000500;
const int mod=1e9+7;

int tr[maxn<<2],tag[maxn<<2],a[maxn];

inline void add(int now,int l,int r,int w) {
	tr[now]+=(r-l+1)*w;
	tag[now]+=w;
}

inline void pushdown(int now,int l,int r) {
	if (!tag[now]) return;
	int mid=l+r>>1;
	add(now<<1,l,mid,tag[now]);
	add(now<<1|1,mid+1,r,tag[now]);
	tag[now]=0;
}

inline void modify(int now,int l,int r,int x,int y,int w) {
	if (x<=l && r<=y) return add(now,l,r,w);
	pushdown(now,l,r);
	int mid=l+r>>1;
	if (x<=mid) modify(now<<1,l,mid,x,y,w);
	if (mid+1<=y) modify(now<<1|1,mid+1,r,x,y,w);
	tr[now]=tr[now<<1]+tr[now<<1|1];
}

inline int query(int now,int l,int r,int x,int y) {
	if (x<=l && r<=y) return tr[now];
	pushdown(now,l,r);
	int mid=l+r>>1,ans=0;
	if (x<=mid) ans+=query(now<<1,l,mid,x,y);
	if (mid+1<=y) ans+=query(now<<1|1,mid+1,r,x,y);
	return ans;
}

signed main() {
	int n=read();
	for (int i=1;i<=n;i++) a[i]=read(),loc[a[i]]=0;
	int ans=0,lst=0;
	for (int i=1;i<=n;i++) {
		int ls=loc[a[i]];
		lst+=2*query(1,1,n,ls+1,i)+i-ls,lst%=mod;
		modify(1,1,n,ls+1,i,1);
		loc[a[i]]=i;
		ans+=lst,ans%=mod;
	}
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：lory1608 (赞：4)

首先这道题花了我半个小时写，但是我$T1$想错了，不知道有多少分。

来看看$NOI$ $online2$ $T2$,这题如果是询问区间的集合大小，就可以用主席树或树状数组维护。

用$pre_i$表示前一个$a_i$出现的位置，用主席树在$pre_i+1 \to i$区间加一即可，复杂度$\Theta(n\log n)$。

回到这题，首先可以暴力$\Theta(n^2)$,常数很小，可以跑过前$50\%$的数据。

那么这道题$1 \times 10^6$的数据，肯定至少要一个$log$的数据结构。

那么可以将数据离散化后，向上面那样维护$pre_i$。

那么对于$i$结尾的区间，考虑$i$有贡献的部分为$pre_i+1\to i$。

那么只用对这一段区间加一即可，树状数组或线段树维护。

对于上述结构，只用维护平方和即可。

不就是线段树维护平方和的板子了吗。

维护$sum_i$为区间和，$ans_i$维护答案。

那么上传答案就是$ans_u=ans_{ls_u}+ans_{rs_u}$,$sum_u=sum_{ls_u}+sum_{rs_u}$。

对于区间加，用标记来表示。

对于下方标记就是一个平方和展开$(a+b)^2=a^2+2\times a \times b+b^2$。

设$mid$为中点,
具体维护$ans$加了$tag_u$: 
$ans_{ls}=ans_{ls}+2 \times tag_u \times sum_{ls}+(mid-l+1) \times tag_u^2$。
$ans_{rs}=ans_{rs}+2 \times tag_u \times sum_{rs}+(r-mid) \times tag_u^2$。
$sum_{ls}=sum_{ls}+(mid-l+1) \times tag_u$。
$sum_{rs}=sum_{ls}+(r-mid) \times tag_u$。

根据平方和展开，要先更新$ans$,再更新$sum$。

总复杂度为$\Theta(n\log n)$。

但是线段树常数有点大，所以要加快读。

注意到以$i$结尾的答案不超过$n^3$即$10^{18}$,故可以用$long long$存，而代替取模的大常数。

具体实现看代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=1e6+5,mod=1e9+7;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return f?x:-x;
}
struct segmentree
{
	#define ls u<<1
	#define rs u<<1|1
	long long sum[maxn<<2],tag[maxn<<2],ans[maxn<<2];
	inline void pushup(int u)
	{
		sum[u]=sum[ls]+sum[rs];
		ans[u]=ans[ls]+ans[rs];
	}
	inline void pushdown(int u,int l,int r)
	{
		if(tag[u])
		{
			int mid=(l+r)>>1;
			ans[ls]=ans[ls]+sum[ls]*2*tag[u]+(mid-l+1)*tag[u]*tag[u];
			sum[ls]=sum[ls]+(mid-l+1)*tag[u];
			ans[rs]=ans[rs]+sum[rs]*2*tag[u]+(r-mid)*tag[u]*tag[u];
			sum[rs]=sum[rs]+(r-mid)*tag[u];
			tag[ls]=tag[ls]+tag[u];
			tag[rs]=tag[rs]+tag[u];
			tag[u]=0;
		}
	}
	inline void update(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)
		{
			tag[u]++;
			ans[u]=ans[u]+sum[u]*2+(r-l+1);
			sum[u]+=(r-l+1);
			return ;
		}
		else
		{
			pushdown(u,l,r);
			int mid=(l+r)>>1;
			if(x<=mid)update(ls,l,mid,x,y);
			if(y>mid) update(rs,mid+1,r,x,y);
			pushup(u);
		}
	}
	inline long long query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)return ans[u];
		else
		{
			pushdown(u,l,r);
			int mid=(l+r)>>1;
			long long val=0;
			if(x<=mid)val=val+query(ls,l,mid,x,y);
			if(y>mid)val=val+query(rs,mid+1,r,x,y);
			return val;
		}
	}
}tree;
int pre[maxn],a[maxn],n,b[maxn],temp[maxn];
long long sum;
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	n=getint();
	for(int i=1;i<=n;++i)
	{
		a[i]=getint();
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int pos=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i)
	{
		a[i]=lower_bound(b+1,b+pos+1,a[i])-b-1;
		pre[i]=temp[a[i]];
		temp[a[i]]=i;
	}
	for(int i=1;i<=n;++i)
	{
		tree.update(1,1,n,pre[i]+1,i);
		sum+=tree.query(1,1,n,1,i)%mod;
		sum%=mod;
	}
	printf("%lld\n",sum);
	return 0;
}
```


---

## 作者：CaCl2 (赞：3)

这题在考场上线段树pushdown l写成r，直接挂成5分。 ~~论对拍的重要性~~ 

这里给出一种不用维护平方和的线段树做法。

首先看到 $\left[1,10^9\right]$的数据范围需要离散化。

然后考虑对每个$i(1\le i \le n)$求出$ 
\sum\limits_{l=1}^if(l,i)^2$，然后相加即为答案。

我们用$lst_i$表示$a_i$上次出现的位置（如果之前没出现过则为$0$），用$ans_i$表示$ 
\sum\limits_{l=1}^if(l,i)^2$。

所以我们只要在$O(\log(n))$的时间内实现$ans$的转移即可。

当$l \le lst_i$时，$a_i$ 不会对$f(l,i)$产生贡献，所以 $f(l,i) = f(l,i-1)$。

当$lst_i < l < i$时，$a_i$会对$f(l,i)$产生$1$的贡献，所以$f(l,i) = f(l,i-1)+1$，$f(l,i)^2-f(l,i-1)^2 = 2f(l,i-1)+1$。

当$l=i$时，$f(l,i) = 1$。

所以可以得到$ans_i = ans_{i-1} + \sum\limits_{l=lst_i}^{i-1}\left(f(l,i)^2- f(l,i-1)^2\right) + 1= ans_{i-1} + \sum\limits_{l=lst_i}^{i-1}\left(f(l,i-1) *2+1\right) + 1 $。

求$\sum\limits_{l=lst_i}^{i-1}\left(f(l,i-1) *2+1\right)$ 用线段树维护序列和即可，并不需要维护平方和。

最后的答案为$\sum\limits_{i = 1}^n ans_i $。

代码不卡常不加O2在洛谷也能AC，不加O2 9.29s，加O2 5.38s。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e6 + 7;
int n;
int a[N],b[N];
int ans[N];
int totans = 0;
int cnt = 0;
int lst[N];
void discrete(){
    sort(b+1,b+n+1);
    cnt = unique(b+1,b+n+1) - (b+1);
    for(int i = 1;i<=n;i++){
        a[i] = lower_bound(b+1,b+cnt+1,a[i]) - b;
    }
}
struct Node{
    int lazy,c,l,r;
}tr[N*4] = {0};
void bt(int nw,int l,int r){
    tr[nw].l = l;
    tr[nw].r = r;
	if(l==r) return;
    int mid = (l+r)/2;
    bt(nw*2,l,mid);
    bt(nw*2+1,mid+1,r);
}
void upd(int nw){
    if(tr[nw].lazy){
        tr[nw*2].lazy += tr[nw].lazy;
        tr[nw*2+1].lazy += tr[nw].lazy;
        tr[nw*2].c =  (1ll * tr[nw*2].c + 1ll * tr[nw].lazy * (tr[nw*2].r - tr[nw*2].l + 1)) % mod;
        tr[nw*2+1].c = (1ll * tr[nw*2+1].c + 1ll * tr[nw].lazy * (tr[nw*2+1].r - tr[nw*2+1].l + 1)) % mod;
        tr[nw].lazy = 0;
    }
}
void chg(int nw,int l,int r,int k){
	if(l>r) return;
    if((l == tr[nw].l)&&(r == tr[nw].r)){
        tr[nw].c = (tr[nw].c + (r-l+1) * k)%mod;
        tr[nw].lazy += k;
        return;
    }
    upd(nw);
    int mid = (tr[nw].r + tr[nw].l)/2;
    if(r<=mid) chg(nw*2,l,r,k);
    else if(l>mid) chg(nw*2+1,l,r,k);
    else chg(nw*2,l,mid,k),chg(nw*2+1,mid+1,r,k);
    tr[nw].c = (tr[nw*2].c + tr[nw*2+1].c) % mod; 
}
int qry(int nw,int l,int r){
    if(l>r) return 0;
    if((l == tr[nw].l)&&(r == tr[nw].r)){
        return tr[nw].c;
    }
    upd(nw);
    int mid = (tr[nw].r + tr[nw].l)/2;
    if(r<=mid) return qry(nw*2,l,r);
    else if(l>mid) return qry(nw*2+1,l,r);
    else return (qry(nw*2,l,mid)+qry(nw*2+1,mid+1,r)) % mod;
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i] = a[i];
    }
    discrete();
    bt(1,1,n);
    for(int i = 1;i<=n;i++){
        ans[i] = ans[i-1];
        ans[i] += (qry(1,lst[a[i]]+1,i) * 2 + (i-lst[a[i]])) % mod;
        chg(1,lst[a[i]]+1,i,1);
        ans[i] %= mod;
        lst[a[i]] = i;
        totans = (totans + ans[i]) % mod;
    }
    printf("%d",totans);
    return 0;
}
```

---

## 作者：AThousandSuns (赞：3)

我来聊聊我是怎么做这题的。

这题做法其实并不难想（毕竟子区间互不重复的数这种题都这样）：

从左到右枚举右端点 $r$。然后线段树维护每个左端点的 $f(i,r)$ 和 $f(i,r)^2$ 的值。

当 $r$ 往右推一格时，$lst_{a_r}+1$ 到 $r$ 的 $f(i,r)$ 都会加一。$lst_{a_r}$ 表示 $a_r$ 这个数上一次出现的位置，如果没有就看成 $0$。

问题变成了区间加和全局平方和。

---
我刚写完代码，本地测了一下，要 6s。

然后我发现线段树中不取模也不会爆 long long，于是把取模换掉了，跑到了 5s。

然后我发现用 map 来维护 $lst$ 太慢了，换成了离散化，这个优化特别给力，到了 3.7s。

我看到离散化就用了 1.1s，就把离散化换成了基数排序，然后也没有二分，勉强卡进 3s。

此时读入+离散化只用了 0.3s，而线段树部分看着就没救。就弃疗了。

一出来发现大家本地都能随便进 2s，当时心态就崩了……

出了数据，一交，怎么 1.1s 就过了？（没有 O2）

然后同学们反而被卡了几个点（然而也是贴着时限被卡，换成 CCF 的机子应该都能过）

---
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=1048576,mod=1000000007;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
struct item{
	int x,id;
}it[maxn],it2[maxn];
int n,a[maxn],b[maxn],bl,ans,add[maxn*2],lst[maxn],cnt[32768],tot;
ll s1[maxn*2],s2[maxn*2];
inline void pushup(int o){
	s1[o]=s1[o<<1]+s1[o<<1|1];
	s2[o]=s2[o<<1]+s2[o<<1|1];
}
inline void setadd(int o,int l,int r,int v){
	add[o]+=v;
	s2[o]+=2*s1[o]*v+1ll*(r-l+1)*v*v;
	s1[o]+=1ll*(r-l+1)*v;
}
inline void pushdown(int o,int l,int r){
	if(add[o]){
		int mid=(l+r)>>1;
		setadd(lson,add[o]);
		setadd(rson,add[o]);
		add[o]=0;
	}
}
void update(int o,int l,int r,int ql,int qr,int v){
	if(l>=ql && r<=qr) return setadd(o,l,r,v);
	pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(mid>=ql) update(lson,ql,qr,v);
	if(mid<qr) update(rson,ql,qr,v);
	pushup(o);
}
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();
	FOR(i,1,n) a[i]=read(),it[i]=(item){a[i],i};
	FOR(i,1,n) cnt[it[i].x&32767]++;
	FOR(i,1,32767) cnt[i]+=cnt[i-1];
	ROF(i,n,1) it2[cnt[it[i].x&32767]--]=it[i];
	FOR(i,1,n) it[i]=it2[i];
	MEM(cnt,0);
	FOR(i,1,n) cnt[it[i].x>>15]++;
	FOR(i,1,32767) cnt[i]+=cnt[i-1];
	ROF(i,n,1) it2[cnt[it[i].x>>15]--]=it[i];
	FOR(i,1,n) a[it2[i].id]=it2[i].x==it2[i-1].x?tot:++tot;
	FOR(i,1,n){
		update(1,1,n,lst[a[i]]+1,i,1);
		lst[a[i]]=i;
		ans=(ans+s2[1])%mod;
	}
	printf("%d\n",ans);
}
```

---

## 作者：syksykCCC (赞：3)

挺有意思的题目。

比如一个数 $a_i$，它对哪些 $f()$ 是有贡献的呢？

比如一个集合 $S$，里面包含了两个 $x$，那么我们可以钦定第一个 $x$ 对 $f(S)$ 造成了 $1$ 的贡献，第二个 $x$ 没有贡献。

所以，当 $l\in[last_{a_i} + 1, i], r \in[i, n]$ 时，$a_i$ 被包含进了区间内，且 **一定是第一个这种数**，所以它会对这些 $f(l, r)$ 都造成了 $1$ 的贡献。

那么这时候我们就可以开一个平面了，横轴表示 $l$，纵轴表示 $r$，每次把横坐标在 $[last_{a_i} + 1, i]$，纵坐标在 $[i, n]$ 的这个矩形的每个元素的权值 $+1$，最后的答案就是每个元素的值的平方和。

难道是二维线段树/树套树？空间显然是不够的。

这时候难道要用[扫描线](https://www.luogu.com.cn/problem/P5490)了吗？当然不是，太麻烦了。

我们沿用扫描线的思想，观察一下这些矩形有什么特点。

我们发现，第 $i$ 个矩形的纵坐标下端点是 $i$，上端点是 $n$，那么我们如果使用水平扫描线的话，所有的 $-1$ 标记都是在平面的顶端，所以，我们可以忽视所有的 $-1$ 标记。

于是，题目就变成了，$i$ 次，每次先把 $[last_{a_i}+1, i]$ 的位置的权值 $+1$，然后查询全局平方和，发现这个用一维线段树是很好维护的。

具体实现细节的话，读入进来的 $a_i$ 首先要离散化，然后按照上面的进行就行了，至于线段树怎么维护区间加，全局平方和，可以考虑维护区间和 $sum$ 和区间平方和 $sum_2$，比如现在要把 $[L,R]$ 这一段都 $+v$，其实就是：

* $sum_2 \gets sum_2 + v^2 \times (R-L+1)+ 2v \times sum$（注意这个 $sum$ 是老的）；
* $sum \gets sum + v \times (R-L+1)$。

这时因为比如对于一个数字 $n$，由 $n^2 \to (n+v)^2$ 其实就是 $n^2 \to n^2 + v^2 + 2nv$，也就是加上了 $v^2 + 2nv$。

代码就很好写了，注意卡常。

---

## 作者：FC_Viiiiictor_K (赞：2)

一道画风正常的扫描线题。

首先对于这种考虑所有区间的问题，不难想到可以枚举右端点，然后用一个较低的时间复杂度一次性得出所有左端点下的贡献；

我们用一个扫描线从1扫到n，每扫过一个数，就加上这个数对左侧所有能做贡献的区间的贡献，不难发现这个数**能且只能做贡献到上次相同数字出现的位置，因为再往左就一定不对不同数字的出现次数产生影响了**；

所以我们开一个维护区间平方和的区间修改、区间查询的线段树，和一个记录一个数上次出现位置的map，每扫过一个数就按上述方法向左侧能做贡献的区间+1，并把目前的全体区间和加到ans上即可。

区间修改平方和的式子稍微推一下就可以得出来了。

完整代码：（此代码惨遭卡常，需要吸氧过）

```cpp
#define INL inline
#define REG register
#define M ((l+r)>>1)
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
INL int read(){
    REG int sum=0,sign=1;
    REG char tmp=getchar();
    while(tmp<'0'||tmp>'9'){
        if(tmp=='-'){
            sign=-1;
        }
        tmp=getchar();
    }
    while(tmp>='0'&&tmp<='9'){
        sum=(sum<<1)+(sum<<3)+(tmp-'0');
        tmp=getchar();
    }
    return sum*sign;
}//快读
const int maxn=1145140;
const ll mod=1e9+7;
int n,lst[maxn];
map<int,int> laspos;//记录上次位置
ll tre[maxn<<2],sqrs[maxn<<2],wait[maxn<<2];
INL void upload(REG int pos){
    tre[pos]=(tre[pos<<1]+tre[pos<<1|1])%mod;
    sqrs[pos]=(sqrs[pos<<1]+sqrs[pos<<1|1])%mod;
}
INL void download(REG int l,REG int r,REG int pos){
    if(wait[pos]){
        wait[pos<<1] = (wait[pos<<1] + wait[pos])%mod;
        wait[pos<<1|1]=(wait[pos<<1|1]+wait[pos])%mod;
        sqrs[pos<<1] = (sqrs[pos<<1] + tre[pos<<1] * wait[pos]%mod*2+wait[pos]*wait[pos]%mod*(M-l+1))%mod;
        sqrs[pos<<1|1]=(sqrs[pos<<1|1]+tre[pos<<1|1]*wait[pos]%mod*2+wait[pos]*wait[pos]%mod*(r-M))%mod;
        tre[pos<<1] = (tre[pos<<1] + (wait[pos]*(M-l+1)))%mod;
        tre[pos<<1|1]=(tre[pos<<1|1]+(wait[pos]*(r-M)))%mod;
        wait[pos]=0;
    }//下传懒标记
}
void update(int al,int ar,int d,int l,int r,int pos){
    if(al<=l&&ar>=r){
        wait[pos]=wait[pos]+d;
        sqrs[pos]=(sqrs[pos]+tre[pos]*d*2+d*d*(r-l+1))%mod;//区间修改平方和
        tre[pos]=(tre[pos]+d*(r-l+1))%mod;
        return;
    }
    download(l,r,pos);
    if(al<=M){
        update(al,ar,d,l,M,pos<<1);
    }
    if(ar>M){
        update(al,ar,d,M+1,r,pos<<1|1);
    }
    upload(pos);
}
ll query(int al,int ar,int l,int r,int pos){
    if(al<=l&&ar>=r){
        return sqrs[pos];
    }
    download(l,r,pos);
    REG ll ans=0;
    if(al<=M){
        ans+=query(al,ar,l,M,pos<<1);
    }
    if(ar>M){
        ans+=query(al,ar,M+1,r,pos<<1|1);
    }
    return ans%mod;
}
int main(){
    n=read();
    for(REG int i=1;i<=n;i++){
        lst[i]=read();
    }
    REG ll ans=0;
    for(REG int i=1;i<=n;i++){
        update(laspos[lst[i]]+1,i,1,1,n,1);//扫过数的做贡献区间
        laspos[lst[i]]=i;//修改上次出现的位置
        ans=(ans+query(1,n,1,n,1))%mod;//统计答案
    }
    cout<<ans;
    return 0;
}
```

~~考场上忘记把线段树数组开大4倍，凉了30pts~~

---

## 作者：Alear (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/P6477)

## 题面

给定一个有颜色的序列，求所有子区间的颜色数的平方和。

$n \leqslant 10^6, col \leqslant 10^9$

## 题解

~~扫描线和递推太强我不会怎么办~~

这里提供一个不一样的思路。

考虑枚举右端点$r$，每次$logn$内求出以当前点为右端点的答案。

每种颜色仅保留在最后一次出现的位置，这样问题就转化成了求序列的所有后缀和的平方和。

如果没有带上平方，考虑每个数的贡献，可以通过维护一个$i * x_i$的树状数组求得答案，记为$sum$。

记$s_i$表示$f(i,n)$，$tot$表示颜色总数，$x_i$表示颜色序列上第$i$位的值。注意这里的颜色序列指的是转化后的序列，值为1表示这个位置上的颜色最后一次出现，0表示后面出现了相同的颜色。

考虑下面这个式子：
$$ \sum s_i * (tot - s_i) $$
它等于：
$$ \sum\limits_{i=1}^n\sum\limits_{j=i}^n x_i\cdot x_j \cdot (j-i) $$
可以想象一条链，把$i$到$j$的路径上每一条边都加上$x_i \cdot x_j$的值，后者是按点对计算，前者按每条边的贡献计算，显然相等。

OK，目标有了，考虑如何维护。记上式为$w$，分别维护两个形如$x_i , i\cdot x_i$树状数组，分别记为$c1$，$c2$。

需要支持两种操作，将中间的某个1改为0，将末尾的0改为1.记修改的位置为$p$。

对于第一种操作,考虑该点的贡献，左边的减少量为$\sum\limits_{x_i==1}(p-i)=c1_p \cdot p - c2_p$，右边同理。

对于第二种操作，也和第一种同理。~~完全一致~~

从左往右扫一遍，将当前位置改为1，如果当前颜色之前出现过，将上一个位置改为0。

当前后缀新增的答案为$sum \cdot tot - w$

完结撒花，总复杂度$O(nlogn)$。

### 思路来源：
[小清新数据结构题](https://www.luogu.com.cn/problem/P3676)，以上构思基本参考该题的做法，你可以前往题解区，或者看我的[这篇博客](https://www.luogu.com.cn/blog/whenindark/p3676-xiao-qing-xin-shuo-ju-jie-gou-ti-dian-fen-shu-post)。

$ Talk \  is \ cheap ,show\ you\ the\ code. $  
考场代码，变量名基本和题解内命名保持一致。
```cpp
#include<bits/stdc++.h>
#define next nxt
#define int long long
using namespace std;
typedef long long ll;
int read(){
	int c=0,nx,sign=1;
	while(!isdigit(nx = getchar()))
		if(nx=='-')
			sign=-1;
	while(isdigit(nx))
		c=c*10+nx-'0',nx=getchar();
	return sign*c;
}
const int N = 1e6 + 20, mod = 1e9 + 7;
inline void ad(int &a, int x){
	if((a += x) >= mod)
		a %= mod;
	else if(a < 0){
		a %= mod;
		a += mod;
	}
}
int n;
int c1[N], c2[N];
void add(int p,int x,int c[]=c1){
	for(;p<=n;p+=p&-p)
		c[p] += x;
}
int query(int p,int c[]=c1){
	int ans = 0;
	for(;p;p=p&(p-1))
		ans += c[p];
	return ans;
}
int a[N], col[N], vis[N];
int tot;
int ans;
int b[N];
bool cmp(int x,int y){
	return a[x] < a[y];
}
signed main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int now = 0;
	n = read();
	for(int i=1;i<=n;i++)
		a[i] = read();
	for(int i=1;i<=n;i++)
		b[i] = i;
	sort(b + 1, b + n + 1, cmp);
	for(int i=1;i<=n;i++){
		int u = b[i];
		if(a[u] == a[b[i - 1]])
			col[u] = now;
		else
			col[u] = ++now;
	}
	int w = 0;
	for(int i=1;i<=n;i++){
		int c = col[i];
		if(vis[c]){
			int p = vis[c];
			add(p, -p);
			add(p, -1, c2);
			tot--;
			int dis = (query(i, c2) - 2 * query(p, c2)) * p + 2 * query(p) - query(i);
			ad(w, dis);
		}
		vis[c] = i, tot++;
		
		int dis = query(i, c2) * i - query(i);
		ad(w, dis);
		add(i, i);
		add(i, 1, c2);
		ad(ans, query(i) * tot - w);
	}
	printf("%lld", ans);
}
```

---

## 作者：hekaiyu (赞：0)

如果公式出锅[**请在博客页面查看**](https://www.luogu.com.cn/blog/hekaiyu/noi-online-2-ti-gao-zu-zi-xu-lie-wen-ti)

# [P6477 [NOI Online #2 提高组]子序列问题](https://www.luogu.com.cn/problem/P6477)

求所有子集的大小平方和；

# 分析

首先help一下和我一样RE的选手，注意要离散化啊。（100->0警告，顺便吐槽写出正解却服务器奔溃，虽然没离散化交了也没差多少）

既然说到离散化，那就从这里开始讲起吧！

使用排序然后重新编号（挺容易但是很重要）

```
int cmp(ss a,ss b){
	return a.a<b.a;
}
for(inti=1;i<=n;i++)
    scanf("%d",&st[i].a),st[i].lie=i;
sort(st+1,st+1+n,cmp);int head=1;
for(int i=1;i<=n;i++){
	if(st[i].a!=st[i-1].a)head++;
	a[st[i].lie]=head;
}
```
接下来就是关键了；

我们依次枚举 $i$。计入从 $i-1$ 开始往前 $j$ 个数字的所有子集的长度 $l_1,l_2,\cdots,l_{i-1}$。

对于第 $i$ 个数字 $a_i$ 考虑其对那些子集可以增加长度，显然是不包含 $a_i$数字的子集。由于长度连续且从 $i$ 开始。所有我们可以记入下 $i-1$ 之前$a_i$ 最后出现的位置 $lie[a_i]$ 

观察枚举到 $i$ 的答案 $ans[i]$ ：（如下式子）

$(0+1)^2+(l_{i-1}+1)^2+(l_{i-2}+1)^2+\cdots+(l_{lie[a_i]+1}+1)^2+(l_{lie[a_i]})^2+\cdots+(l_1)^2$

和并展开：

$(0^2+l_1^2+l_2^2+\cdots+l_{i-1}^2)+2(l_{i-1}+l_{i-2}+\cdots+l_{lie[a[i]]
+1})+i-lie[a[i]]$ 

发现没有！最前那部分就是 $ans[i-1]$ 。

中间部分是长度和。

结尾只要计入下 $lie[a_i]$ 就可以了。

那么如何求长度和呢？

每次我们修改 $i-1$ 到 $lie[a_i]+1$ ，查询位置相同。
区间修改，区间查询只有加法，这不就是线段树模板一吗？[不会可以简单了解一下blog](https://www.luogu.com.cn/blog/hekaiyu/post-shuo-ju-jie-gou-xian-duan-shu#)
这里就不解释了。

贴出60行的代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int mod=1e9+7;
long long lie[maxn],num[maxn],ans[maxn];int n;long long _ans;
long long a[maxn*4],addv[maxn*4],sumv[maxn*4];
void add(int o,int l,int r,int p,int q){//线段树区间加
	int mid=(l+r)/2;
	if(p<=l&&q>=r){
		addv[o]=(long long)addv[o]+1;
	}
	else{
		if(p<=mid)add(o*2,l,mid,p,q);
		if(q>mid)add(o*2+1,mid+1,r,p,q);
    }
    sumv[o]=0;
	if(r>l){
		sumv[o]=sumv[o*2]+sumv[o*2+1];
	}
	sumv[o]+=(long long)addv[o]*(r-l+1);
}
long long summ=0;
void query(int o,int l,int r,int p,int q,long long addd){//线段树查询，不会去看blog
	if(p<=l&&q>=r){
		summ +=(long long)sumv[o]+addd*(r-l+1); 
	}
	else {
		long long mid=(r+l)/2;
		if(p<=mid) query(o*2,l,mid,p,q,addd+addv[o]);
		if(q>mid) query(o*2+1,mid+1,r,p,q,addd+addv[o]);
	}
}
struct ss{
	int a,lie;
}st[maxn];
int cmp(ss a,ss b){
	return a.a<b.a;
}
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&st[i].a),st[i].lie=i;
	sort(st+1,st+1+n,cmp);int head=1;
	for(int i=1;i<=n;i++){//离散化
		if(st[i].a!=st[i-1].a)head++;
		a[st[i].lie]=head;//a[i]离散化后结果数组
	}
    for(int i=1;i<=n;i++){
    	summ=0;
    	query(1,1,n,lie[a[i]]+1,i,0);//查询总长度
        ans[i]=(long long)((long long)ans[i-1]+(long long)i-lie[a[i]]+(long long)summ*2)%mod;//化简后的答案，之前爆负数了多转几次long long
        add(1,1,n,lie[a[i]]+1,i);//区间修改长度
        _ans=(long long)((long long)_ans+ans[i])%mod;//将所有答案进行相加
        lie[a[i]]=i;更新位置
	}
	printf("%lld",_ans);
	return 0;
} 
```
结束了撒花！！！！


---

