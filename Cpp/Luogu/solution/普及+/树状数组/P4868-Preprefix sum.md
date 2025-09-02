# Preprefix sum

## 题目描述

前缀和（prefix sum）$S_i=\sum_{k=1}^i a_k$。

前前缀和（preprefix sum）则把 $S_i$ 作为原序列再进行前缀和。记再次求得前缀和第 $i$ 个是 $SS_i$。

给一个长度 $n$ 的序列 $a_1, a_2, \cdots, a_n$，有两种操作：

1. `Modify i x`：把 $a_i$ 改成 $x$。
2. `Query i`：查询 $SS_i$。


## 说明/提示

$1\le N,M\le 10^5$，且在任意时刻 $0\le A_i\le 10^5$。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
Query 5
Modify 3 2
Query 5```

### 输出

```
35
32```

# 题解

## 作者：Leianha (赞：38)

## 树状数组
我们需要求的是$\sum_{i=1}^{k}S_i$ ,即$\sum_{i=1}^{k}\sum_{j=1}^{i}a_i$.

暴力求解肯定是不行的，化简式子是OIer的优良传统，所以我们可以考虑化简一下式子。

我们可以考虑一下每一个元素对前前缀合的贡献，第$i$个数被$i$~$k$之间的每一个$S_j$都计算了一遍，所以它的贡献就是$(k-i+1)\times a_i$,我们需要求的就是$\sum_{i=1}^{k}(k-i+1)\times a_i$。

我们回到单个元素，根据乘法分配率，我们就得到$(k-i+1)\times a_i=(k+1)\times a_i-i\times a_i$,

所以$\sum_{i=1}^{k}(k-i+1)\times a_i=\sum_{i=1}^{k}(k+1)\times a_i-\sum_{i=1}^{k}i\times a_i$，

再将$(k+1)$提出来之后就得到式子$(k+1)\sum_{i=1}^{k} a_i-\sum_{i=1}^{k}i\times a_i$

对于$\sum_{i=1}^{k} a_i$和$\sum_{i=1}^{k}i\times a_i$我们都能够用树状数组来维护，这样我们就能快速的求出答案啦^_^。

再考虑修改，只用这样写
```cpp
add1(x,y-a[x]);add2(x,(y-a[x])*x);
```
就可以啦~，还是比较简单的。

最后献上我~~丑陋~~的代码
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,m,x,y;
const int N=100010;
int ans,len;
int a[N],tr1[N<<1],tr2[N<<1];
char s[101];
int read()
{
	char ch;int x=0,f=1;
	while(!isdigit(ch=getchar()))
	{(ch=='-')&&(f=-f);}
	while(isdigit(ch))
	{x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
int lowbit(int x){return x&(-x);}
void add1(int pos,int x)
{
	for(int i=pos;i<=(N<<1);i+=lowbit(i))tr1[i]+=x;
}
void add2(int pos,int x)
{
	for(int i=pos;i<=(N<<1);i+=lowbit(i))tr2[i]+=x;
}
int ask1(int pos)
{
	int lin=0;
	for(int i=pos;i;i-=lowbit(i))lin+=tr1[i];
	return lin;
}
int ask2(int pos)
{
	int lin=0;
	for(int i=pos;i;i-=lowbit(i))lin+=tr2[i];
	return lin;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		add1(i,a[i]);add2(i,a[i]*i);
	}
	while(m--)
	{
		scanf("%s",s+1);
		if(s[1]=='Q')
		{
			x=read();
			ans=((x+1)*ask1(x)-ask2(x));
			printf("%lld\n",ans);
		}
		else
		{
			x=read();y=read();
			add1(x,y-a[x]);add2(x,(y-a[x])*x);
			a[x]=y;
		}
	}
	return 0;
}
```


---

## 作者：Hexarhy (赞：9)

### Preface

不难的数据结构题，冷静分析很容易想。或许可以评黄？

适合新手巩固。

### Solution

众所周知，前缀和是这样计算的：

$$S_i=\sum^i_{j=1}a_j$$

前前缀和就是这样的：

$$T_i=\sum^i_{j=1}S_j=\sum^i_{j=1}\sum^j_{k=1}a_k$$

把 $\sum$ 展开来观察，得到

- $T_1=S_1=a_1$
- $T_2=S_1+S_2=a_1+(a_1+a_2)=2a_1+a_2$
- $T_3=S_1+S_2+S_3=a_1+(a_1+a_2)+(a_1+a_2+a_3)=3a_1+2a_2+a_3$

以此类推，得到：

$$T_i=\sum^i_{j=1} (i-j+1)a_j$$

接下来就考虑怎么维护 $T$。

乘法分配律展开，得到：

$$T_i=\sum^i_{j=1}(i+1)\times a_j-\sum^i_{j-1}j\times a_j=(i+1)\sum^i_{j=1}a_j-\sum^i_{j=1}j\times a_j$$

于是，我们可以用两个树状数组维护 $\sum^i_{j=1}a_j$ 和 $\sum^i_{j=1}j\times a_j$。

接下来考虑怎么建树和单点修改 $a_i=x$。

前者是传统的树状数组，建树 `modify(i,a[i])`，单点修改只需 `modify(i,x-a[i])`。

后者多乘了一个 $j$，那么建树和单点修改也就多乘一个 $j$，也就是 `modify(i,a[i]*i)` 和 `modify(i,(x-a[i])*i)`。

### Another one

还有一个比较直接的做法。

直接维护前缀和，询问前前缀和直接区间加。单点修改的时候，也直接区间修改前缀和。

因此用线段树直接做就行，思维难度和代码难度都很低。这里就不贴代码了。

### Notice

1. 计算一下极端数据，不难发现需要 `long long`。

1. 修改的时候别忘了修改原数组`a[]`。

1. 两个树状数组可以不写`add1(),add2()`这样，用一个结构体`struct`或者类`class`可以大大简化代码。

### Code

按照刚才的思路写就行了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
ll n,m;
ll a[MAXN];
class BIT//模板
{
private:
	ll tree[MAXN];
	ll lowbit(const ll x){return x&(-x);}
public:
	void modify(ll pos,const ll x)
	{
		for(;pos<=n;pos+=lowbit(pos))
		 tree[pos]+=x;
	}
	ll query(ll pos)
	{
		ll res=0;
		for(;pos;pos-=lowbit(pos))
		 res+=tree[pos];
		return res; 
	}
}t1,t2;//简化代码

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
     cin>>a[i];
    for(ll i=1;i<=n;i++)
	{
		t1.modify(i,a[i]);
		t2.modify(i,a[i]*i);
	} 
	while(m--)
	{
		string s;cin>>s;
		if(s=="Modify")
		{
			ll pos,x;cin>>pos>>x;
			t1.modify(pos,x-a[pos]);
			t2.modify(pos,(x-a[pos])*pos);
			a[pos]=x;//别忘了
		}
		if(s=="Query")
		{
			ll pos;cin>>pos;
			cout<<((pos+1)*t1.query(pos)-t2.query(pos))<<endl;//根据推的式子算
		}
	}
	return 0;
}
```

---

## 作者：SuperJvRuo (赞：8)

来一篇树状数组的题解。

简化题意：

1. 单点对$a_i$进行修改

2. 求$SS_i=\sum^i_{j=1}\sum^j_{k=1}a_k$

分析：

展开$SS_i$，发现$SS_i=\sum^i_{j=1}(i-j+1)\times a_j$

可以维护两个树状数组，一个维护$a_i$，另一个维护$b_i=(n-i+1)\times a_i$。这样，我们要查询的$SS_i$即为$\sum^i_{j=1}[(n-j+1)-(n-i)]\times a_j=\sum^i_{j=1}b_j-(n-i)\times\sum^i_{j=1}a_j$

这里面的两个$\sum$都可以用树状数组$O(\log n)$求出。难度评级：普及+/提高

```
#include<cstdio>
#include<cctype>
#define LL long long

int Read()
{
    int x=0;char c=getchar();
    while(!isdigit(c))
    {
        c=getchar();
    }
    while(isdigit(c))
    {
        x=x*10+(c^48);
        c=getchar();
    }
    return x;
}

LL arr[100005];//存ai
LL BIT[2][100005];
//BIT[0]为ai的BIT，BIT[1]为bi=(n-i+1)ai的BIT
int n,m;

int lowbit(int x)
{
    return x&-x;
}

void Add(LL val,int pos,int idx)
{
    for(int i=pos;i<=n;i+=lowbit(i))
        BIT[idx][i]+=val;
}

void Modify(LL val,int pos)
{//对两个BIT分别操作
    Add(-arr[pos],pos,0);
    Add(-arr[pos]*(n-pos+1),pos,1);
    arr[pos]=val;
    Add(arr[pos],pos,0);
    Add(arr[pos]*(n-pos+1),pos,1);
}

LL Query(int pos)
{
    LL ans=0;//sigma(bi)
    for(int i=pos;i;i-=lowbit(i))
    {
        ans+=BIT[1][i];
    }
    LL red=0;//sigma(ai)
    for(int i=pos;i;i-=lowbit(i))
    {
        red+=BIT[0][i];
    }
    return ans-red*(n-pos);
}

int main()
{
    n=Read(),m=Read();
    for(int i=1;i<=n;++i)
    {
        Add(arr[i]=Read(),i,0);
        Add(((LL)n-i+1)*arr[i],i,1);
    }
    char opt[10];
    int pos;
    while(m--)
    {
        scanf("%s",opt);
        if(opt[0]=='M')
        {
            pos=Read();
            Modify(Read(),pos);
        }
        else
        {
            printf("%lld\n",Query(Read()));
        }
    }
    return 0;
}
```

---

## 作者：xieyi0408 (赞：6)

看到大家都用线段树或者树状数组，我就写一个分块的题解吧(保证思路简单，代码量少）

题目要求 ${∑_{i=1}^{x}S_{i}}$ ,于是我们将前缀和( ${S_i}$ ) 预处理出来，分块 。

设 $S_i$ 表示前 $i$ 个数的和,        $block[x]$ 表示x所在的块的编号， $Sum[x]$ 表示第 $i$ 个块的所有前缀和的和 , $L[x]$ 和 $R[x]$ 分别表示第 $x$ 块的左右端点

对于修改操作：

设 $k$ **$=a_i$ 修改后的值 $-a_i$ 修改前的值** 

容易发现单点修改 $a_i$ 只会让 $S_i$ 到 $S_n$ 的值增加 $k$  ,于是我们分两段来处理

对于 $x$ 所在的块，直接将每个 $S$ 值修改，并将该块的 $Sum$ 值增加 $(R[block[x]]-x+1)*k$

对于 $x$ 后面的块，直接将每个块的 $Sum$ 值增加 $(R[block[x]]-L[block[x]]+1)*k$ , 并将该块的 $add$ 值增加 $k$ ,表示该块的 $S$ 值整体加 $k$

对于查询操作：

对于 $x$ 所在的块的前面的块，答案直接加上该块的 $Sum$ 值

对于 $x$ 所在的块，答案加上从 $L[block[x]$ 到 $x$ 的 $S$ 值与该块 $add$ 值的和，即：

 ${∑_{i=L[block[x]}^{x}S_{i}+add[block[x]]}$
 
 代码如下：
 
 ```cpp
 #include<bits/stdc++.h>
#define int long long//要开long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=101010,Sqn=1010;
int xx,Sum[Sqn],block[N],n,m,a[N],add[Sqn],L[Sqn],R[Sqn],cnt,x,y,S[N];
string s;
void init(int n){
	xx=sqrt(n);
	for(int i=1;i<=n;i++){
		block[i]=(i-1)/xx+1;
	}
	cnt=block[n];
	for(int i=1;i<=cnt;i++){
		L[i]=xx*(i-1)+1,R[i]=xx*i;
	}
	R[cnt]=min(R[cnt],n);
}//分块的预处理
main(){
	n=read(),m=read();
	init(n);
	for(int i=1;i<=n;i++)a[i]=read(),S[i]=S[i-1]+a[i],Sum[block[i]]+=S[i];//前缀和以及每块的和的预处理
	while(m--){
		cin>>s;
		if(s[0]=='M'){
			x=read(),y=read();
			int k=y-a[x];a[x]=y;
			for(int i=block[x]+1;i<=cnt;i++)Sum[i]+=k*(R[i]-L[i]+1),add[i]+=k;//对于x所在块的后面的块的处理
			for(int i=x;i<=R[block[x]];i++)S[i]+=k;//对于x所在块的处理
			Sum[block[x]]+=(R[block[x]]-x+1)*k;
		}
		if(s[0]=='Q'){
			x=read();
			int ans=0;
			for(int i=1;i<block[x];i++)ans+=Sum[i];//x所在块的前面的块的处理
			for(int i=L[block[x]];i<=x;i++)ans+=S[i]+add[block[x]];//x所在块的处理
			printf("%lld\n",ans);
		}
	}
}
 ```

---

## 作者：Warriors_Cat (赞：5)

### $Solution:$

线段树来一发！

我们把线段树用来维护区间前缀和，那么修改某个值就直接后缀区间加就行，而询问就询问这个前缀和的前缀和。

简单来说，对于修改 $a_i = x$：

先算出 $y = query(1, i) + query(1, i + 2) - query(1, i + 1) \times 2$，这就是 $a_i$（大家可以想想为什么），然后进行修改 $change(i, n, x - y)$。

对于询问 $SS_i$：

直接求出 $query(1, i)$ 即可。

下面放代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
const int N = 100010;
int n, m, d[N << 2], f[N << 2], x, y, a[N];
char s[20];
inline void pushup(int p){d[p] = d[p << 1] + d[p << 1 | 1];}//上传 
inline void pushdown(int p, int l, int r){
	if(f[p]){
		int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
		d[ls] += f[p] * (mid - l + 1);
		d[rs] += f[p] * (r - mid);
		f[ls] += f[p]; f[rs] += f[p]; f[p] = 0;
	}
}//下放懒标记 
inline void build(int p, int l, int r){
	if(l == r){d[p] = a[l]; return;}
	int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
	build(ls, l, mid); build(rs, mid + 1, r);
	pushup(p);
}//建树 
inline void change(int p, int l, int r, int x, int y, int z){
	if(x <= l && r <= y){
		d[p] += (r - l + 1) * z;
		f[p] += z;
		return;
	}
	pushdown(p, l, r);
	int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
	if(x <= mid) change(ls, l, mid, x, y, z);
	if(y > mid) change(rs, mid + 1, r, x, y, z);
	pushup(p); 
}//修改 
inline int query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return d[p];
	pushdown(p, l, r);
	int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1, ans = 0;
	if(x <= mid) ans += query(ls, l, mid, x, y);
	if(y > mid) ans += query(rs, mid + 1, r, x, y);
	return ans;
}//询问
//以上均为模板 
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%lld", a + i), a[i] += a[i - 1];//先求出前缀和 
	build(1, 1, n);
	for(int i = 1; i <= m; ++i){
		scanf("%s", s + 1);
		if(s[1] == 'M'){
			scanf("%lld%lld", &x, &y);
			int X;
			if(x == 1) X = query(1, 1, n, 1, 1);//特判1 
			else if(x == 2) X = query(1, 1, n, 1, 2) - (query(1, 1, n, 1, 1) << 1);//特判2 
			else X = query(1, 1, n, 1, x) + query(1, 1, n, 1, x - 2) - (query(1,1 , n, 1, x - 1) << 1);//否则直接求 
			change(1, 1, n, x, n, y - X);
		}
		else{
			scanf("%lld", &x);
			printf("%lld\n", query(1, 1, n, 1, x));
		}
	}
	return 0;
}
```


---

## 作者：Ccliang (赞：3)

原本可以不看题解一遍AC，结果没开$long$ $long$见祖宗。

~~很气~~

这道题目很明显是差分，让我们看看为什么是差分：

对于一个数列 $a_1,a_2,a_3$，

它的前缀和即$a_1,a_1+a_2,a_1+a_2+a_3$，

前前缀和即$a_1,2a_1+a_2,3a_1+2a_2+a_3$，

如果我们将 $a_2$ 加 $x$，

前缀和就变成了：$a_1,a_1+a_2+x,a_1+a_2+a_3+x$，

前前缀和就变成了:$a_1,2a_1+a_2+x,3a_1+2a_2+a_3+2x$，

我们可以发现如果我们在第 $i$ 项加上 $x$，前缀和的第 $i$ 项之后每一项都会加 $x$，前前缀和第 $i$ 项每一项之后会加$kx$，$k$为常数，会向后依次递增。

~~看着就像个差分~~

这道题目要求单点查询，我们就可以维护初始的前前缀和，和一个线段树。

修改第 $i$ 项为 $x$ 时在线段树区间$[i,n]$整体加$x-a_i$，$a_i$为初始序列，然后再把$a_i$改为$x$。

询问第 $i$ 项的答案就是线段树区间$[1,i]$的区间和加上初始前前缀和的第 $i$ 项。

具体实现细节可以看我的代码 ~~(线段树常数巨大)~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

const int N = 100000 + 10;

inline int read()
{
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
	return res;
}

int a[N];

ll sum[N],t[N<<2],lazy[N<<2];
#define lson pos<<1
#define rson pos<<1|1
#define mid ((l+r)>>1)
void pushdown(int pos,int l,int r)
{
	lazy[lson]+=lazy[pos],lazy[rson]+=lazy[pos];
	t[lson]+=1ll*(mid-l+1)*lazy[pos],t[rson]+=1ll*(r-mid)*lazy[pos];
	lazy[pos]=0;
}

void change(int pos,int l,int r,int L,int R,int k)
{
	if(l>=L&&r<=R)
	{
		lazy[pos]+=k;
		t[pos]+=1ll*k*(r-l+1);
		return ;
	}
	if(lazy[pos])
		pushdown(pos,l,r);
	if(L<=mid)
		change(lson,l,mid,L,R,k);
	if(R>mid)
		change(rson,mid+1,r,L,R,k);
	t[pos]=t[lson]+t[rson];
}

ll query(int pos,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)
		return t[pos];
	pushdown(pos,l,r);
	if(R<=mid)
		return query(lson,l,mid,L,R);
	else if(L>mid)
		return query(rson,mid+1,r,L,R);
	return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
}

string opt;

int main()
{
	int n=read(),m=read(),x,y;
	for(int i=1;i<=n;i++)
		a[i]=read(),sum[i]=a[i]+sum[i-1];
	for(int i=2;i<=n;i++)
		sum[i]+=sum[i-1];
	while(m--)
	{
		cin>>opt;
		if(opt=="Query")
		{
			x=read();
			printf("%lld\n",1ll*sum[x]+query(1,1,n,1,x));
		}
		if(opt=="Modify")
		{
			x=read(),y=read();
			change(1,1,n,x,n,y-a[x]);
			a[x]=y;
		}
	}
	return 0;
}
```
在推荐一个差分的好题，~~感觉比这个要难，但为什么难度的标签低一些~~：[无聊的序列](https://www.luogu.com.cn/problem/P1438)

---

## 作者：Poetic_Rain (赞：3)

啊，看到这道题，可以自己手推一下这个前前缀和到底等于多少，其实很好推，而且长得很像另外一个式子

$s_x = \sum\limits_{i=1}^xa_i$

$ss_x = \sum\limits_{i=1}^x s_i= \sum\limits_{i=1}^x \sum\limits_{j=1}^i  a_j $

好了，最基本的式子就这么推出来了，但是发现这是个$O(n^2)$的玩意（口胡的时间复杂度），那么如何让它更快呢，我们可以继续化简

$\sum\limits_{i=1}^x \sum\limits_{j=1}^i  a_j $

在我们手动模拟时，我们可以发现$a_1$用了$x$次，$a_2$用了$x-1$次，$a_3$用了$x-2$次，然后可以推得

$a_i$用了$x-i+1$次

那么我们可以继续化简这个式子，把第二层的循环给他删掉

$\sum\limits_{i=1}^x  a_i*(x-i+1) $

$\sum\limits_{i=1}^x  a_i*(x+1)- \sum\limits_{i=1}^x  a_i*i$

$(x+1)*\sum\limits_{i=1}^x  a_i- \sum\limits_{i=1}^x  a_i*i$

那么整个式子就推到这里了，对于$x+1$这个常数，我们可以暂时不管，那么对于这个式子，我们可以得出一个信息

即用两个树状数组，一个维护$a_i$，一个维护$i*a_i$

那么整个程序就可以打出来了，注意开long long，不然只有40分

```
#include<bits/stdc++.h>
using namespace std;
const long long N=500051;
long long lowbit(long long x){
	return x&-x;
}
long long n,m;
long long a[N];
long long c1[N];
long long c2[N];
void update(long long x,long long k){
	long long i=x;
	for(;i<=N;i+=lowbit(i)){
		c1[i]+=k;
		c2[i]+=x*k;
	}
}
void add(long long l,long long r,long long k){
	update(l,k);
	update(r+1,-k);
}
long long res=0;
long long ask(long long x){
    res=0;
    long long i=x;
    for(;i;i-=lowbit(i)){
   	    res+=(x+1)*c1[i]-c2[i];
	}
    return res;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(register long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		add(i,N,a[i]);
	}
	for(register long long i=1;i<=m;i++){
		string op;
		long long x,y;
		cin>>op;
		scanf("%lld",&x);
		if(op[0]=='Q') printf("%lld\n",ask(x));
		else{
			scanf("%lld",&y);
			add(x,N,y-a[x]);
			a[x]=y;
		}
	}
	return 0;
}
```

但是我还是想讲一下其他的东西，如果对树状数组的入门的萌新来说，区间修改+区间查询的操作应该比较少见，我是想通过这篇题解讲解一下

假如是修改$[x,y]$区间，那么老样子，我们可以用差分的思想搞一下，即

```
void add(int l,int r,int k){
	update(l,k);
	update(r+1,-k);
}
```

这里我不会直接给出来update，因为和平时写的有变化，之后会讲

那么区间修改暂时先说到这里，如何去搞区间查询呢？

肯定第一次都会想着直接$ask(r)-ask(l-1)$，但是是错的

原理是这样的没错，但是中间有一些细节需要处理

我们用$b[]$表示增量数组，例如$a[1]=1$，我让它加上一个$k$，那么$b[1]=k$

继续推式子，由于刚刚的$ask(r),ask(l-1)$的运算法则应该是一样的，所以我们只以$ask(r)$为例子

$ask(r) = \sum\limits_{i=1}^xa_i$

$ask(r) = \sum\limits_{i=1}^x a_i= \sum\limits_{i=1}^x \sum\limits_{j=1}^i  b_j $

聪明的你此时一定会发现，跟这道题上面的式子简直那是一模一样，没错，包括后面的推理过程也是完全相同的，所以我就不继续写了，我就贴一下程序好了

```
void update(int x,int k){
	int i=x;
	for(;i<=n;i+=lowbit(i)){
		tree1[i]+=k;
		tree2[i]+=x*k;
	}
}
void add(int l,int r,int k){
	update(l,k);
	update(r+1,-k);
}
int res=0;
int ask(int x){
    res=0;
    int i=x;
    for(;i;i-=lowbit(i)){
   	    res+=(x+1)*tree1[i]-tree2[i];
	}
    return res;
}
int query(int l,int r){
	return ask(r)-ask(l-1);
} 
//区间改和区间查询
```

希望对大家有帮助

---

## 作者：DYan_Hyaena (赞：2)

### 题目大意

题目链接$\rightarrow$[PORTAL](https://www.luogu.com.cn/problem/P4868)

维护一个序列  $\{a_i\}, \ |\{a_i\}|\in(1,1e5),\forall a_i\in(1,1e5)$ ， 使满足以下操作：

1. 单点修改 $a_i$
2. 给定 $i$ 求 $\sum^i_{k=1}\sum^i_{j=1}a_j$

### 所需芝士：前缀和与差分，线段树

考虑到所查询的结果是 $a_i$ 二阶前缀和，看样子比较恼人，但是我们可以 ~~学习中国古代圣贤的中庸之道~~ 将 **前缀和的前缀和** 看作是 **前缀和** 的 **前缀和**，再把原来的序列看作是 **前缀和** 的 **差分序列** 。

利用这个性质，我们就可以把这个问题加以简化了（不知道为什么的赶快回去重新复习吧）

所以我们先存储 题中所给序列 $\{a_i\}$ 与 这个序列的前缀和 $\{b_i\}$ ，这样的话题目中 $\{a_i\}$ 的单点修改就变成了 $\{b_i\}$ 差分序列 的单点修改

比如说我们有一个题中序列：
$$\{a_i\}=\{1,1,4,5,1,4\}$$

这样的话我们就会得到这个序列的前缀和序列
$$\{b_i\}=\{1,2,6,11,12,16\}$$

现在我们把 $a_3$ 加上 $30$， $a_3=4+30=34$

原序列变为$\{a_i\}=\{1,1,34,5,1,4\}$

这时候，$\{b_i\}=\{1,2,36,41,42,46\}$，我的天，$b_3,\ b_4,\cdots$ 一直到 $b_6$ 全都加了个 $30$！


所以 $a_i$ 的单点修改转换过来其实就是 $\{b_i\}$ 的**区间修改**，而且修改的范围是 从 $i$ 到 $n$ 。

诶等等等等！区间修改+前缀和查询？好家伙，这是~~把我喂给露米娅我都要说~~可以用**线段树**来做了。

我们利用线段树维护一阶前缀和数列 $\{b_i\}$ ，然后维护它的区间和，查询的时候就可以查询出二阶前缀和了。

考虑到原来序列 $\{a_i\}$ 中第 $i$ 个数是 $a_i$ ，我们把它改成了 $x$ 的话，相当于是 
$$x=a_i+(x-a_i)$$

所以我们在为线段树做区间加法的时候就加上 $x-a_i$ 就行了。加完后注意要把 $a_i$ 改为设好的新 $x$ 值

最后说一句，不开 `long long` 见祖宗。

AC代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define ine inline
#define int long long
using namespace std;
ine int lowbit(int x){return x&(~x+1);}
ine int rd(){
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){ans=(ans<<3)+(ans<<1)+ch-48;ch=getchar();}
	return ans*f;}
const int maxn=1e5+5;
int n=rd(),m=rd();
int num1[maxn]; //这里是题中所给的原数列
int num2[maxn]; //这里是我们的一阶前缀和数列
//二阶前缀和利用线段树求
class SegmentTree{
	public:
		int node[maxn<<2];
		int L[maxn<<2],R[maxn<<2];
		int lazy[maxn<<2];
		void build(int p,int l,int r){
			L[p]=l,R[p]=r;
			if(l==r){node[p]=num2[l];return;}
            //注意这里用的是一阶前缀和来维护
			rg int mid=(l+r)>>1;
			build(p<<1,l,mid);build(p<<1|1,mid+1,r);
			node[p]=node[p<<1]+node[p<<1|1];
		}
        ine int rge(int p){return R[p]-L[p]+1;}
		ine void down(int p){
			lazy[p<<1]+=lazy[p],lazy[p<<1|1]+=lazy[p];
			node[p<<1]+=lazy[p]*(R[p<<1]-L[p<<1]+1);
			node[p<<1|1]+=lazy[p]*(R[p<<1|1]-L[p<<1|1]+1);
			lazy[p]=0;
		}
		void change(int p,int l,int r,int va){
			if(l<=L[p] && r>=R[p]){
				node[p]+=1ll*va*(R[p]-L[p]+1);
				lazy[p]+=va;
				return;}
			down(p);
			rg int mid=(L[p]+R[p])>>1;
			if(l<=mid)change(p<<1,l,r,va);
			if(r>mid)change(p<<1|1,l,r,va);
			node[p]=node[p<<1]+node[p<<1|1];
		}
		int query(int p,int l,int r){
			if(l<=L[p] && r>=R[p])
				return node[p];
			down(p);
			int ans=0;
			rg int mid=(L[p]+R[p])>>1;
			if(l<=mid)ans+=query(p<<1,l,r);
			if(r>mid)ans+=query(p<<1|1,l,r);
			return ans;
		}
};
//以上是线段树的板子
SegmentTree A;
signed main(){
	for(int i=1;i<=n;i++){
		num1[i]=rd();
		num2[i]=num2[i-1]+num1[i];
	}
	A.build(1,1,n);
	string op;
	int a,b;
	while(m--){
		cin>>op;a=rd();
		if(op[0]=='Q'){
			cout<<A.query(1,1,a)<<endl;
		}
		else{
			b=rd();
			int delta=b-num1[a];
            //这一句要注意，我们要在原来数组里
            //加上 原数与新数的差 才可以达到改为新数的目的
			A.change(1,a,n,delta);
            num1[a]=b;//dont forget
		}
	}
	return 0;
}
```

---

## 作者：feicheng (赞：1)

一道非常好的线段树题目

~~十年OI一场空，不开`long long `见祖宗~~

------------
回到正题
## 题目简述
给定数列 $a$,
定义 $S_p = \sum_{i=1}^pa_i,SS_p = \sum_{i=1}^pS_i$

有如下两种操作：

求 $SS_i$

修改 $a_i$
## 思路讲解
前缀和的前缀和很显然是不好维护的，但是我们可以观察前前缀和的性质：
$$SS_p = \sum_{i=1}^pS_i$$
实质上就是一个区间加啊。

我们再看单点修改会对前缀和造成什么影响：
假设把 $a_i$ 修改成 $a_i+k$，则 
$$\Delta S_p = k\quad(p\ge i  )$$

这实际上就是一个区间修改啊。

所以我们可以用线段树来维护前缀和

注意在单点修改的时候应当直接修改原数组。
## 代码实现
```cpp
/*If you are full of hope,you will be invincible*/
#include <bits/stdc++.h>
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr));
constexpr int inf(0x3f3f3f3f),N(1e5 + 10);
int n,m;
#define int ll 
ll a[N],s[N];
struct Seg{
	#define mid ((t[x].l+t[x].r) >> 1)
	struct node{int l,r;ll sum,laz;}t[N<<2];
	inline void pushup(int x){t[x].sum = t[x<<1].sum + t[x<<1|1].sum;}
	inline void pushdown(int x){
		if(!t[x].laz) return;
		t[x<<1].laz += t[x].laz,t[x<<1|1].laz += t[x].laz,
		t[x<<1].sum += (t[x<<1].r - t[x<<1].l + 1) * t[x].laz,
		t[x<<1|1].sum += (t[x<<1|1].r-t[x<<1|1].l + 1) * t[x].laz,
		t[x].laz = 0;
	}
	void build(int x,int l,int r) {
		if((t[x].l = l) == (t[x].r = r)) return t[x].sum = s[l],void();
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
		pushup(x);
 	}
 	void modify(int x,int l,int r,ll k) {
 		if(t[x].l >= l && t[x].r <= r) return t[x].laz += k,t[x].sum += (t[x].r - t[x].l + 1) * k,void();
 		pushdown(x);
 		if(l <= mid) modify(x<<1,l,r,k);
 		if(mid < r) modify(x<<1|1,l,r,k);
 		pushup(x);
	}
	ll query(int x,int l,int r) {
		if(t[x].l >= l && t[x].r <= r) return t[x].sum;
		pushdown(x);
		ll res = 0;
		if(l <= mid) res += query(x<<1,l,r);
		if(mid < r) res += query(x<<1|1,l,r);
		return res; 
	}
}Seg;
signed main(int argc,const char *argv[]){
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	for(ri i = 1;i <= n;++i) std::cin >> a[i],s[i] = s[i-1] + a[i];
	Seg.build(1,1,n);
	for(ri i = 1;i <= m;++i) {
		int x,y;
		std::string s;
		std::cin >> s;
		if(s == "Query") std::cin >> x,std::cout << Seg.query(1,1,x) << '\n';//修改前缀和 
		else {
			std::cin >> x >> y;
			Seg.modify(1,x,n,y-a[x]);//题目要求修改，我们转化成加上差值 
			a[x] = y;//给a数组赋值 
		} 		
	}
	return 0;
}


```


---

## 作者：Durancer (赞：1)

#### 前言

被差分撮过来的，做了一遍发现只有树状数组=_=

#### 思路

既然看见式子了肯定要推式子

$$SS_i=\sum_{j=1}^{i}\sum_{k=1}^{j}a_k$$

$$SS_i=\sum_{j=1}^{i}(i-j+1)\times a_j$$

$$SS_i=\sum_{j=1}^{i}(i+1)\times a_j-\sum_{j=1}^{i}j\times a_j$$

$$SS_i=(i+1)\times \sum_{j=1}^{i} a_j-\sum_{j=1}^{i}j\times a_j$$

推到最下面可以发现，我们只需要维护两个值

$ \sum_{j=1}^{i} a_j\text{以及}\sum_{j=1}^{i}j\times a_j$即可

可以考虑用两个树状数组来维护就行了

也就是维护 $a_j$ 的前缀和以及 $j\text{个}a_j$ 的前缀和就好了，其他的就是正常更新树状数组

唯一注意的一个坑点就是，更新完别忘了在更新一下 $a_j$ 数组在更新位置的那个值...

#### 代码

```

#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long 
using namespace std;
const int N=1e5+9;
int a[N];
int one[N],two[N];
int sum[N];
int poi[N];//差分数组
int n,m,cnt;
int query[N];
int read()
{
    int f=1,x=0;
    char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
    return x*f;
}
int lowbit(int x)
{
    return x&(-x);
}
void add1(int x,int k)
{
    while(x<=n)
    {
        one[x]+=k;
        x+=lowbit(x);
    }
}
void add2(int x,int k)
{
    while(x<=n)
    {
        two[x]+=k;
        x+=lowbit(x);
    }
}
int query1(int x)
{
    int ret=0;
    while(x)
    {
        ret+=one[x];
        x-=lowbit(x);
    }
    return ret;
}
int query2(int x)
{
    int ret=0;
    while(x)
    {
        ret+=two[x];
        x-=lowbit(x);
    }
    return ret;
}
signed main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<=n;i++)
    {
        add1(i,a[i]);
        add2(i,a[i]*i); 
    } 
    while(m--)
    {
        string s;
        cin>>s;
        if(s=="Query")
        {
            int l=read();
            int a=(l+1)*query1(l);
            int b=query2(l);
            printf("%lld\n",a-b); 
        }
        else if(s=="Modify")
        {
            int l=read();//所在的位置 
            int num=read();//加的值
            add1(l,(num-a[l]));
            add2(l,(num-a[l])*l); 
            a[l]=num;
        }
    }
    return 0;
} 
```


---

## 作者：AubRain (赞：1)

这里是线段树的做法，个人认为更清晰易懂。

用线段树维护序列的前缀和即可，即叶子节点是原序列的前缀和。

然后修改一个点的值，会影响到后面所有的前缀和，于是后缀区间加即可。

然后询问的话，就是前缀和的前缀和，区间求和即可。

**代码：**

```cpp
#pragma GCC target("avx,sse2,sse3,sse4,popcnt")
#pragma GCC optimize("O2,Ofast,inline,unroll-all-loops,-ffast-math")
#include<bits/stdc++.h>
#define N 100005
#define r1 (p<<1)
#define r2 (p<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

inline void rd(int &X){
    X=0;int w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    X=w?-X:X;
}
int n,m;
char pd[9];
int a[N],s[N];
int sum[N<<2],add[N<<2];

void build(int p,int l,int r){
    if(l==r) return sum[p]=s[l],void();
    build(r1,l,mid);build(r2,mid+1,r);
    sum[p]=sum[r1]+sum[r2];
}
void push(int p,int l,int r){
    if(!add[p]) return;
    int x=add[p];add[p]=0;
    add[r1]+=x;add[r2]+=x;
    sum[r1]+=(mid-l+1)*x;sum[r2]+=(r-mid)*x;
}
void change(int p,int L,int R,int d,int l=1,int r=n){
    if(L<=l and r<=R) return sum[p]+=d*(r-l+1),add[p]+=d,void();push(p,l,r);
    if(L<=mid) change(r1,L,R,d,l,mid);
    if(R >mid) change(r2,L,R,d,mid+1,r);sum[p]=sum[r1]+sum[r2];
}
int ask(int p,int L,int R,int l=1,int r=n){
    if(L<=l and r<=R) return sum[p];push(p,l,r);int v=0;
    if(L<=mid) v+=ask(r1,L,R,l,mid);
    if(R >mid) v+=ask(r2,L,R,mid+1,r); return v;
}
signed main()
{
    rd(n);rd(m);
    for(int i=1;i<=n;i++)
        rd(a[i]),s[i]=s[i-1]+a[i];
    build(1,1,n);
    while(m--){
        scanf("%s",pd);int x,y;
        if(pd[0]=='Q') rd(x),printf("%lld\n",ask(1,1,x));
        else rd(x),rd(y),change(1,x,n,y-a[x]),a[x]=y;
    }
}

```

---

## 作者：顾z (赞：1)


# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

显然,这是**差分+树状数组**

题目中给定的$a_i$就是我们的差分数组。

不会差分的小伙汁,来[这里](https://rpdreamer.blog.luogu.org/ci-fen-and-shu-shang-ci-fen)

安利很好的写树状数组的[博客](https://www.cnblogs.com/RabbitHu/p/BIT.html).

然后推一下式子.

如果我们修改差分数组$a_i$,显然,$S_i$会变化.

$S_i=S_{i-1}+a_i$

现在变成了

$S_i=S_{i-1}+x$

那么差值就变成了$x-a_i$

那么,我们就$add(i,x-a[i])$,不要忘了最后将$a_i$变为$x$

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#define int long long
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,m,last,t1[1000008],t2[1000008],a[1000008];
#define lowbit(x) x&-x
inline void add(int pos,int x)
{
	for(R int i=pos;i<=n;i+=lowbit(i))
		t1[i]+=x,t2[i]+=pos*x;
}
inline int query(int pos)
{
	R int res=0;
	for(R int i=pos;i;i-=lowbit(i))
		res+=t1[i]*(pos+1)-t2[i];
	return res;
}
char opt[8];
signed main()
{
	in(n),in(m);
	for(R int i=1,x;i<=n;i++)
	{
		in(a[i]);
		add(i,a[i]);
	}
	for(R int i=1,x,y;i<=m;i++)
	{
		scanf("%s",opt+1);
		if(opt[1]=='Q')
		{
			in(x);
			printf("%lld\n",query(x));
		}
		else
		{
			in(x),in(y);
			add(x,y-a[x]);
			a[x]=y;
		}
	}
}
```

v

---

## 作者：Zxsoul (赞：0)

# 来一发线段树

作者：zxsoul

## 思路


前缀和非常熟悉，开个 $sum$ 存就好了，但是前缀和的前缀和呢？细一些的讲就是得到标号为 $i$ 到开头的所有前缀和 $sum$ 的和，那么显然我们维护前缀和，区间查询就好啦

单点修改也挺好操作的

**注/** 我用的是结构体线段树，他的好处在于处理多项操作时只需要更改一个函数

## Code

```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

#define root 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int B = 1e6+10;
const int mod = 1e9 + 7;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int n,k,a[B],s[B];

struct node
{
    int l,r,sum,col;
    node() {sum=0,col=0,l=r=0;}
    
    void init(int l_,int r_)
    {
        l=l_,r=r_;
        sum=s[l];
        col=0;
    }
} z[B<<2];

node operator +(const node &l, const node &r)
{
    node p;
    p.col=0,p.l=l.l,p.r=r.r;
    p.sum=l.sum+r.sum;
    return p;
}

void color(int rt,int v)
{
    z[rt].col+=v;
    z[rt].sum+=(z[rt].r-z[rt].l+1)*v;
}

void push(int rt)
{
    if (z[rt].col!=0)
    {
        color(rt<<1,z[rt].col);
        color(rt<<1|1,z[rt].col);
        z[rt].col=0;
    }
}

void update(int rt) {z[rt]=z[rt<<1]+z[rt<<1|1];}

void build(int l,int r,int rt)
{
    if (l==r)
    {
        z[rt].init(l,r);
        return;
    }
     
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    update(rt); 
} 

void modify(int l,int r,int rt,int nowl,int nowr,int v)
{
    if (nowl<=l && r<=nowr)
    {
        color(rt,v);
        return;
    }
    
    push(rt);
    int m=(l+r)>>1;
    if (nowl<=m) modify(lson,nowl,nowr,v);
    if (nowr>m) modify(rson,nowl,nowr,v);
    update(rt);
}

node query(int l,int r,int rt,int nowl,int nowr)
{
    if (nowl<=l && r<=nowr) return z[rt];
    
    push(rt);
    
    int m=(l+r)>>1;
    if (nowl<=m)
    {
        if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
        else return query(lson,nowl,nowr);
    }
    else return query(rson,nowl,nowr);
}



main()
{
    int x,y;
    n=read(),k=read();
    for (int i=1;i<=n;i++)
    {
        a[i]=read();
        s[i]=s[i-1]+a[i];
    }
    
    build(root);
    
    for (int i=1;i<=k;i++)
    {
        char b[6];
        cin>>b;
        if (b[0]=='Q')
        {
            x=read();
            printf("%lld\n",query(root,1,x).sum);
        }
        else
        {
            x=read(),y=read();
            modify(root,x,n,y-a[x]);
            a[x]=y;
        }
    }
}

```


---

## 作者：Na2PtCl6 (赞：0)

我来提供一个不一样的线段树做法。
## 题目大意
有一个序列 $A$ ，维护它的前缀和序列的前缀和，动态修改和查询。

- 修改 ：把 $A$ 的第 $i$ 个数改为 $x$

- 查询 ：求 $A$ 的前缀和序列的前缀和的第 $x$ 个数

## 分析题目
对于修改操作，我们把 $A$ 的第 $i$ 个元素赋值为 $x$ ，把前缀和的第 $i$ ~ $n$ 个数加上本次修改前的 $x-A_i$ ；

对于查询，输出前缀和数组的前 $x$ 个数的和。

我们可以用一个树状数组维护 $A$ 序列，用一棵线段树维护 $A$ 序列的前缀和。

## 代码实现
我比较懒，就用线段树写了本该是树状数组的结构。

也就 90 多行吧，比写树状数组的同学们长多了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100004;
char op[24];
int n,m,a,ind,x;

struct seg_tree{
	private:
	LL tree[maxn<<2],tag[maxn<<2];
	
	inline void push_down(int l,int r,int node){
		int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
		LL t=tag[node];
		if(t){
			tag[lnode]+=t,tag[rnode]+=t;
			tree[lnode]+=(mid-l+1)*t;
			tree[rnode]+=(r-mid)*t;
			tag[node]=0;
		}
	}

	void assign(int l,int r,int node,int p,LL v){
		if(l==r){
			tree[node]=v;
			return ;
		}
		int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
		if(p<=mid)
			assign(l,mid,lnode,p,v);
		else
			assign(mid+1,r,rnode,p,v);
		tree[node]=tree[lnode]+tree[rnode];
	}
	
	void add(int l,int r,int node,int start,int end,LL v){
		if(start<=l&&r<=end){
			tag[node]+=v;
			tree[node]+=(r-l+1)*v;
			return ;
		}
		int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
		push_down(l,r,node);
		if(start<=mid)
			add(l,mid,lnode,start,end,v);
		if(end>mid)
			add(mid+1,r,rnode,start,end,v);
		tree[node]=tree[lnode]+tree[rnode];
	} 
	
	LL sum(int l,int r,int node,int start,int end){
		if(start<=l&&r<=end)
			return tree[node];
		int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
		push_down(l,r,node);
		LL ret=0;
		if(start<=mid)
			ret+=sum(l,mid,lnode,start,end);
		if(end>mid)
			ret+=sum(mid+1,r,rnode,start,end);
		return ret;
	}
	
	public:
	inline void assign(int p,LL v){ assign(1,n,1,p,v);}	
		
	inline void add(int start,int end,LL v){ add(1,n,1,start,end,v);}
	
	inline LL sum(int start,int end){ return sum(1,n,1,start,end);}
}s,ss;

signed main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		s.assign(i,a);
		ss.assign(i,s.sum(1,i));
	}
	while(m--){
		scanf("%s",op);
		if(op[0]=='M'){
			scanf("%d %d",&ind,&x);
			int dis=x-s.sum(ind,ind);
			s.assign(ind,x);
			ss.add(ind,n,dis);
		}
		else{
			scanf("%d",&ind);
			printf("%lld\n",ss.sum(1,ind));
		}
	}
	return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：0)

大佬推得公式跟本看不懂啊。我们就用个简单粗暴，无任何思维难度的线段树吧。

我们直接用线段树维护前缀和数组。

加入我们的数列是这样的：

| $A_i$ | 1 | 3 | 5 | 10 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $S_i$ | 1 | 4 | 9 | 19 |

修改操作，假设我们现在要 Modify 2 6 。

那么则会变成：

| $A_i$ | 1 | 6 | 5 | 10 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $S_i$ | 1 | 7 | 12 | 22 |

不难发现，$2 \cdots n$ 的 $S_i$ 加了一个 $6 - A_2$。所以一个单点修改被我们乱搞成了区间修改，区间查询就按照定义查询即可。

线段树还是用指针比较爽，你刚开始可能觉得比较恶心，但你会越用越舒服，尤其是对于我这种强烈讨厌方括号的人。

还有一条建议，多写封装，显著降低代码错误率。

**一定开longlong**

正常版本。
```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e6 + 100;
typedef long long ll;
struct Segment{//线段树
    struct node{
        node *lson , *rson;
        ll val , tag;
    }dizhi[N * 2 + 10] , *root = &dizhi[0];
    ll sum[N] , cnt = 0;
    void inii(int *a , int n) {//降低代码耦合性，传参数
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + a[i];
    }
    void pushup(node *rt) {
        rt->val = rt->lson->val + rt->rson->val;
    }
    void pushdown(node *rt , int l , int r) {
        if(rt->tag == 0)return ;
        int mid = (l + r)>>1;
        rt->lson->tag += rt->tag;
        rt->rson->tag += rt->tag;
        rt->lson->val += rt->tag * (mid - l + 1);
        rt->rson->val += rt->tag * (r - mid);
        rt->tag = 0;
    }
    void build(node *rt , int l , int r) {
        if(l == r) {
            rt->val = sum[l];
            rt->tag = 0;
            return ;
        }
        int mid = (l + r)>>1;
        rt->lson = &dizhi[++cnt];rt->rson = &dizhi[++cnt];
        build(rt->lson , l , mid);
        build(rt->rson , mid + 1 , r);
        pushup(rt);
    }
    void update(node *rt ,int L , int R, int l , int r , ll v) {
        if(L <= l && r <= R) {
            rt->val += (r - l + 1) * v; 
            rt->tag += v;
            return ;
        }
        int mid = (l + r)>>1;
        pushdown(rt , l , r);
        if(L <= mid)update(rt->lson , L , R , l , mid , v);
        if(mid + 1 < R)update(rt->rson , L , R , mid +  1 , r , v);
        pushup(rt);
    }
    ll  query(node *rt , int L , int R , int l , int r) {
 //       cout << l << " " << r << endl;
        if(L <= l && r <= R)return rt->val;
        int mid = (l + r)>>1;
        pushdown(rt , l , r);
        ll ans = 0;
        if(L <= mid)ans += query(rt->lson , L , R , l , mid);
        if(mid + 1 <= R)ans += query(rt->rson , L , R , mid + 1 , r);
        return ans;
    }
}kkk;
int data[N];
int main() {
    int n , m;scanf("%d%d" , &n , &m);
    for(int i = 1; i <= n; i++)
        scanf("%d" , &data[i]);
    kkk.inii(data , n);
    kkk.build(kkk.root , 1 , n);
    string op;int x ;ll y;
    while(m--) {
   //     cout << "eee";
        cin >> op;
        if(op == "Query") {
            scanf("%d" , &x);
            printf("%lld\n" , kkk.query(kkk.root , 1 , x , 1 , n));
        }else {
            scanf("%d%lld" , &x , &y);
            kkk.update(kkk.root , x , n , 1 , n , y - data[x]);//根据刚才说的
            data[x] = y;
        }
    }
}
```

[轻微压行版本](https://www.luogu.com.cn/paste/fwth07vl)

---

## 作者：那一条变阻器 (赞：0)

### 线段树题解qwq

------------

这道题其实把式子一推就行了。因为要求前缀和的前缀和，那为什么我们不维护前缀和，然后求前缀和呢？对于维护前缀和，我们只需要两种操作：区间修改，区间查询。

区间查询是查询前缀和的前缀和嘛，这个是区间操作没问题，但为什么是区间修改？题目不是单点修改吗？我们先推一下式子：

原数列：

$x_1,x_2,x_3,x_4,x_5$

前缀和：


$x_1,x_1+x_2,x_1+x_2+x_3,x_1+x_2+x_3+x_4,x_1+x_2+x_3+x_4+x_5$

可以发现，我们如果修改了$x_1$，对于后面的每一个数都变化了，继续推，发现每一个$x$的变化都会影响到后面的每一个数，所以当修改$x_i$时，我们要修改的范围其实是$i-n$，那么线段树模板就来了。

诶等等，他是修改，而不是加减，这里坑就来了，我们要先拿一个数组存储一下每一次修改后的序列，这样对于下一次修改的时候，我们就可以直接比较一下修改数和原数，这样就可以把修改数转化为加减了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls 2 * p
#define rs 2 * p + 1
long long n , m , last;	//太懒了直接全部long long 
long long sum[4000010] , tag[4000010] , a[1000010];
void pushdown(long long l , long long r , long long p){	//下传标记 
	if(l == r || tag[p] == 0) return;
	long long mid = (l + r) / 2;
	sum[ls] += (mid - l + 1) * tag[p];
	sum[rs] += (r - mid) * tag[p];
	tag[ls] += tag[p];
	tag[rs] += tag[p];
	tag[p] = 0;
}
void add(long long l , long long r , long long s , long long t , long long k , long long p){	//区间加 
	if(l >= s && r <= t){
		sum[p] += (r - l + 1) * k;
		tag[p] += k;
		return;
	}
	pushdown(l , r , p);
	long long mid = (l + r) / 2;
	if(mid >= s) add(l , mid , s , t , k , ls);
	if(mid < t) add(mid + 1 , r , s , t , k , rs);
	sum[p] = sum[ls] + sum[rs];
}
long long query(long long l , long long r , long long s , long long t , long long p){	//区间求和 
	if(l >= s && r <= t) return sum[p];
	pushdown(l , r , p);
	long long mid = (l + r) / 2 , ans = 0;
	if(mid >= s) ans += query(l , mid , s , t , ls);
	if(mid < t) ans += query(mid + 1 , r , s , t , rs);
	return ans;
}
int main(){
	cin >> n >> m;
	for(long long i = 1; i <= n; i++){
		cin >> a[i];
		add(1 , n , i , i , a[i] + last , 1);	//维护前缀和 
		last += a[i];
	} 
	while(m--){
		string st;
		long long x , k;
		cin >> st;
		if(st[0] == 'Q'){
			cin >> x;
			cout << query(1 , n , 1 , x , 1) << endl;
		}else{
			cin >> x >> k;
			add(1 , n , x , n , k - a[x] , 1);	//转化为区间加减 
			a[x] = k;	//存一下修改后序列 
		}
	}
    return 0;
}
```


---

## 作者：rediserver (赞：0)

# P4868 Preprefix sum
[原题地址](https://www.luogu.org/problem/P4868)  
[Github](https://github.com/jerrykcode/luogu)



## 思路

对于原数组a的前缀和s以及s的前缀和ss，  
由于ss[i] = s[1] + s[2] + ... + s[i]  
而更新a[i]则s[i]，s[i + 1]，...，s[n]都要更新。 
那么问题就转化为对`前缀和s的区间修改/求和操作。`  
区间修改/求和用树状数组做，就要求差分，而s的差分其实就是:  
s[i] - s[i - 1]  
= (s[i - 1] + a[i]) - s[i - 1]  
= a[i]  
到这里就太开心了，  
要记录的差分就是a数组本身 
用树状数组记录a，以及另一个数组b，b[i] = a[i]\*i  
对Modify i x操作，直接更新a和b的树状数组即可。  
而 
ss[i]  
= s[1] + s[2] + ... + s[i]  
= a[1] + a[1] + a[2] + ... + a[1] + a[2] + ... + a[i]  
= i \* a[1] + (i - 1) \* a[2] + ... + 1 \* a[i]  
= (i + 1) \* a[1] - 1 \* a[1] + (i + 1) \* a[2] - 2 \* a[2] + ... + (i + 1) \* a[i] - i \* a[i]  
= (i + 1) \* (a[1] + a[2] + ... + a[i]) - (1 \* a[1] + 2 \* a[2] + ... + i \* a[i])  
= (i + 1) \* (a[1] + a[2] + ... + a[i]) - (b[1] + b[2] + ... + b[i])  
那么查询ss[i]只需对a和b进行区间求和，  
通过a和b的树状数组也可以轻松实现。  

## Code

```cc
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <string>
using namespace std;

typedef long long LL;

int lowbit(int x) {
	return x & -x;
}

int n;

void update(LL * bit, int idx, LL k) {
	for (; idx <= n; idx += lowbit(idx)) {
		bit[idx] += k;
	}
}

LL sum(LL * bit, int idx) {
	LL result = 0;
	for (; idx > 0; idx -= lowbit(idx)) {
		result += bit[idx];
	}
	return result;
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	LL * bit_a = (LL *)malloc((n + 1) * sizeof(LL));
	LL * bit_b = (LL *)malloc((n + 1) * sizeof(LL));
	for (int i = 1; i < n + 1; i++) {
		bit_a[i] = bit_b[i] = 0;
	}
	LL *a = (LL *)malloc((n + 1) * sizeof(LL));
	for (int i = 1; i < n + 1; i++) {
		scanf("%lld", a + i);
		update(bit_a, i, a[i]);
		update(bit_b, i, a[i]*i);
	}
	//char cmd[6];
	string cmd;
	int idx;
	LL x;
	for (int i = 0; i < m; i++) {
		//scanf("%s", cmd);
		cin >> cmd;
		if (cmd[0] == 'M') {
			scanf("%d %lld", &idx, &x);
			update(bit_a, idx, x - a[idx]);
			update(bit_b, idx, (x - a[idx]) * idx);
			a[idx] = x;		
		}
		else {
			scanf("%d", &idx);			
			printf("%lld\n", sum(bit_a, idx) * (idx + 1) - sum(bit_b, idx));
		}		
	}
	free(bit_a);
	free(bit_b);
	free(a);
	return 0;
}
```

---

## 作者：Patrickpwq (赞：0)

显然是不能直接开两个树状数组维护 前缀和，前缀和的前缀和。因为一旦对a[i]进行修改，将会影响许多位前缀和的前缀和

我们考虑对式子变一下形

	Qi
    
 	=S1+S2+S3+...+Si

 	=a1+a1+a2+a1+a2+a3+...+ai
    
     =a1*i+a2*(i-1)+a3*(i-2)+...+ai*
    
     =(a1+a2+a3+...+ai)*i - (a2+a3^2+a4^3+...+ai^(i-1))

因此还是开两个树状数组 一个维护前半部分 一个维护后半部分

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
typedef long long ll;
struct BIT
{
	ll tree[N];
	int n;
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	inline void update(int x,ll del)
	{
		for(int i=x;i<=n;i+=lowbit(i))	tree[i]+=del;
	}
	inline ll query(int x)
	{
		ll ans=0;
		for(int i=x;i;i-=lowbit(i))	ans+=tree[i];
		return ans;
	}
}tree1,tree2;
template<class T>
inline void read(T &x)
{
	x=0;
	static char ch=getchar();
	while(ch<'0'||ch>'9')	ch=getchar();
	while(ch>='0'&&ch<='9')	x=x*10+ch-'0',ch=getchar();
}
int n,m;
ll a[N];
int main()
{
	read(n); read(m);
	tree1.n=n;	tree2.n=n;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		tree1.update(i,a[i]);
		tree2.update(i,a[i]*(i-1));
	}
	char s[10];
	for(int i=1;i<=m;i++)
	{
		scanf("%s",&s);
		ll x,y;
		if(s[0]=='Q')
		{
			read(x);
			cout<<ll(tree1.query(x)*x)-tree2.query(x)<<'\n';
		}
		else
		{
			read(x);	read(y);
			tree1.update(x,y-a[x]);	tree2.update(x,(y-a[x])*(x-1));
			a[x]=y;
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

为什么没人发题解呢qwq 假的蓝题欢迎各种乱搞啊

sol：对于开始所有的前缀和建一棵线段树 然后每次对于修改的那个点到n的区间减去差值，查询只要求1~x的和就可以了qwq

码风有点不好将就着看看吧

```cpp
#include <cstdio>
using namespace std;
#define int long long
#define N 100005
int n,m,a[N],b[N];
struct SegmentTree{int l,r,lazy,sum;inline int len(){return r-l+1;}}Tree[N<<2];
inline void up(int x){Tree[x].sum=Tree[x<<1].sum+Tree[x<<1|1].sum;}
inline void ADD(int x,int y){Tree[x].lazy+=y; Tree[x].sum+=Tree[x].len()*y;}
inline void down(int x){int l=Tree[x].lazy;ADD(x<<1,l);ADD(x<<1|1,l);Tree[x].lazy=0;}
inline void build(int l,int r,int x)
{
	Tree[x].l=l; Tree[x].r=r; Tree[x].lazy=0;
	if(l==r) { Tree[x].sum=b[l]; return;}
	int mid=(l+r)>>1; build(l,mid,x<<1); build(mid+1,r,x<<1|1); up(x);
}
inline void ins(int l,int r,int x,int v)
{
	if(Tree[x].l==l&&Tree[x].r==r){Tree[x].lazy+=v;Tree[x].sum+=Tree[x].len()*v;return;}
	if(Tree[x].lazy!=0) down(x);
	int mid=(Tree[x].l+Tree[x].r)>>1;
	if(r<=mid) ins(l,r,x<<1,v); else if(l>mid) ins(l,r,x<<1|1,v);
	else ins(l,mid,x<<1,v),ins(mid+1,r,x<<1|1,v); up(x);
}
inline int que(int l,int r,int x)
{
	if(Tree[x].l==l&&Tree[x].r==r)return Tree[x].sum;
	if(Tree[x].lazy!=0) down(x);
	int mid=(Tree[x].l+Tree[x].r)>>1;
	if(r<=mid) return que(l,r,x<<1); else if(l>mid) return que(l,r,x<<1|1);
	else return que(l,mid,x<<1)+que(mid+1,r,x<<1|1);
}
signed main()
{
	int i,x,y; char s[10];
	scanf("%lld%lld",&n,&m); for(i=1;i<=n;i++)scanf("%lld",&a[i]), b[i]=b[i-1]+a[i];
	build(1,n,1);
	for(i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='Q') {scanf("%lld",&x);printf("%lld\n",que(1,x,1));}
		else {scanf("%lld%lld",&x,&y);if(a[x]!=y) {ins(x,n,1,y-a[x]); a[x]=y;} }
	}
}
```

求管理大大给过啊

---

## 作者：Arghariza (赞：0)

$n,m≤10^5$ ，分块很慌，考虑线段树。

因为整个题目始终在前缀和数组上操作，所以这棵树直接维护 $a$ 的前缀和数组 $s_i$ 。

- 查询：$ss_i=\sum\limits_{k=1}^{i}s_k$ ，线段树标准操作。（树状数组也可以支持）

- 修改：如果把 $a_i=z$ 改成 $x$ ，相当于相加 $x-z$ ，前缀和数组应该将所有 $s_k(k\in[i, n])$ 变为 $s_k + x - z$ ，等同于线段树区间修改。

实际上还要特判 $i=1$ 的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
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

const int maxn = 1e5 + 100;
struct segment_tree {// 线段树
    int tree[4 * maxn], lazy[4 * maxn];
    void pushup(int x) {
        tree[x] = tree[x << 1] + tree[(x << 1) | 1];
    }
    void pushdown(int l, int r, int x) {
        int mid = (l + r) >> 1;
        tree[x << 1] += lazy[x] * (mid - l + 1);
        tree[(x << 1) | 1] += lazy[x] * (r - mid);
        lazy[x << 1] += lazy[x];
        lazy[(x << 1) | 1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int l, int r, int x, int s[]) {
        if (l == r) {
            tree[x] = s[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, x << 1, s);
        build(mid + 1, r, (x << 1) | 1, s);
        pushup(x);
    }
    void update(int l, int r, int s, int t, int c, int x) {
        if (l <= s && t <= r) {
            tree[x] += (t - s + 1) * c;
            lazy[x] += c;
            return;
        }
        int mid = (s + t) >> 1;
        if (lazy[x]) pushdown(s, t, x);
        if (l <= mid) update(l, r, s, mid, c, x << 1);
        if (r > mid) update(l, r, mid + 1, t, c, (x << 1) | 1);
        pushup(x);
    }
    int query(int l, int r, int s, int t, int x) {
        if (l <= s && t <= r) return tree[x];
        int mid = (s + t) >> 1, res = 0;
        if (lazy[x]) pushdown(s, t, x);
        if (l <= mid) res += query(l, r, s, mid, x << 1);
        if (r > mid) res += query(l, r, mid + 1, t, (x << 1) | 1);
        return res;
    }
} st;

int n, m, s[maxn];
char q[maxn];

signed main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; i++) s[i] = read() + s[i - 1];// 计算前缀和
    st.build(1, n, 1, s);// 建树
    for (int i = 1; i <= m; i++) {
        scanf("%s", q);
        if (q[0] == 'Q') {
            int x = read();
            write(st.query(1, x, 1, n, 1));// 查询 1 到 x 的前缀何数组的和
            puts("");
        } else {
            int x = read();
            int y = read();
            int s = y - st.query(x, x, 1, n, 1) + (x == 1 ? 0 : st.query(x - 1, x - 1, 1, n, 1));// 获取 a_i 应该加上的数
            st.update(x, n, 1, n, s, 1);// 区间修改
        }
    }
    return 0;
}
```

---

