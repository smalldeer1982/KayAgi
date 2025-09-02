# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5 1
5 8
```

### 输出

```
9
```

# 题解

## 作者：YuRuiH_ (赞：7)

二分答案，用差分数列O(n)判断是否可行。

二分答案，设当前答案为x，也就是碉值最低的话的碉值最大值为x。

从头到尾观察花，若a[i]<x，则对a[i]开头的w盆花怒浇(x-a[i])天，让其碉值达到x。让所有的a[i]都>=x。若怒浇的天数和小于等于m，则可行。

而这个怒浇操作可以用差分队列实现

因为差分数列b[i]=a[i]-a[i-1]，则当前点的值为now，下一个点的值就为now+b[i+1]。差分数列的L到R全加D操作：    b[L]+=x; b[R+1]-=x;（注意这题R可能会怒超边界，记得特殊处理一下或者数组开大点）

首先我们能够得到全部花的最矮高度即答案的下界，给这个花浇m天即是答案的上界

然后二分枚举答案，检验合法性。

 

怎样检验合法性

 类似于：

我们用个数组来记录need[i]表示 i点须要浇的次数（从i点開始的区间）

我们再用一个变量has来维护 i点已经被浇了的次数（由i点之前的在浇花范围内的点浇过的次数和）

动态地维护这两个值就可以

假设不够浇的。need[i]前缀和已经大于m天。则return false;

不然 return true;

```
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
const int NN=111111;
int n,m,w;
int need[NN];
int f[NN];
bool can(int s){
	int a=0;int b=m;
	for(int i=1;i<=n;i++){
		if(i>=w)
			a-=need[i-w];
		need[i]=max((int)0,s-a-f[i]);
		a+=need[i];
		b-=need[i];
		if(b<0)
			return false;
	}
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("G:/in.txt","r",stdin);
	//freopen("G:/myout.txt","w",stdout);
#endif
	cin>>n>>m>>w;
	int minn=(1<<30);
	for(int i=1;i<=n;i++){
		cin>>f[i];
		minn=min(f[i],minn);
	}
	int maxn=minn+m;
	int mid=(minn+maxn)/2+1;
	while(minn<maxn){
		if(can(mid)){
			minn=mid;
		}else{
			maxn=mid-1;
		}
		mid=(minn+maxn)/2+1;
	}
	cout<<minn<<endl;
}
```


---

## 作者：TernaryTree (赞：6)

给出一种不需要二分的 $\Theta(m\log n)$ 解法。

将序列看作一个木桶的板子高度。我们想要让这个桶装尽可能多的水，就要把最短的板尽可能变高。~~这个理论大家想必都从家长或者老师那里多多少少听过~~

于是我们考虑每次操作找到当前序列最小值中最左边的那个，将其作为一次操作的左端点。若对应的右端点超出范围就让右端点顶齐最右侧。这个可以线段树维护一下。

由于最小值与严格次小值的差大于等于每次操作加上的 $1$，所以我们感性理解一下这个贪心的正确性：

- 如果我们当前加的区间里没有最小值那么这次操作没有意义。因为最小值是不变的。

- 我们要在最少次操作内消除最小值。

但是到这里还有一个疑问在于如果有多个区间都包含了同样个数的最小值，那么其会不会影响后面的操作的结果。答案是不会。

假设有这样一个数据：

```
5 2 4
2 1 1 1 114514
```

观众老爷如果用自己人类的思维想都会觉得先加 $[1,4]$ 是最好的。但是其实加 $[2,5]$ 效果是一样的。为什么呢？

因为最小值每次加一，其它数可以作为陪衬，最终的结果只与最小值有关。这里需要一点感性理解吧！过于严谨的证明这里没有展开~~其实是我不会~~。

这样我们使用线段树维护最左的最小值下标就能做到 $m\log n$ 了。

代码在这里：[Link](https://www.luogu.com.cn/discuss/597223)。

---

## 作者：Karry5307 (赞：6)

### 题意

给定一个长度为 $n$ 的序列 $a$，有 $m$ 次操作，每次可以将 $a$ 中的连续 $w$ 个元素增加 $1$，最大化最终序列的最小值。

$\texttt{Data Range:}1\leq w\leq n\leq 10^5,1\leq m\leq 10^5$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13584410.html)

~~咋一到数据结构题就缩卵呢，于是就理所当然的被神 $\texttt{x\color{red}gzc}$ 教育了 >_<~~

[![db9tRU.jpg](https://s1.ax1x.com/2020/08/30/db9tRU.jpg)](https://imgchr.com/i/db9tRU)

看到这种最小值最大这东西考虑二分答案，于是只需要对于二分出的答案 $x$ 判定 $m$ 次操作之后最小值是否不小于 $x$。

考虑贪心搞。如果 $a$ 中存在一个值小于 $x$ 我们就把他加到大于等于 $x$ 即可，但是为了不浪费操作次数，我们可以直接加到 $x$。这里我的实现是以这个数为左端点来考虑。

但是有一些位置不可能成为长度为 $w$ 的区间的左端点。这个时候考虑完前面所有的操作之后直接把 $[n-w+1,n]$ 这个区间加上剩下的操作次数即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51; 
ll n,m,w,l,r,mid,res;
ll x[MAXN],diff[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll check(ll mid)
{
	ll c=0,cur=m,p;
	for(register int i=1;i<=n;i++)
	{
		diff[i]=x[i]-x[i-1];
	}
	for(register int i=1;i<=n-w+1;i++)
	{
		c+=diff[i];
		if(cur>0&&c<mid)
		{
			p=min(cur,mid-c),diff[i]+=p,diff[i+w]-=p,cur-=p,c+=p;
		}
	}
	diff[n-w+1]+=cur,diff[n+1]-=cur,c=0;
	for(register int i=1;i<=n;i++)
	{
		c+=diff[i];
		if(c<mid)
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	n=read(),m=read(),w=read(),l=0x3f3f3f3f,r=0x3f3f3f3f;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),l=min(l,x[i]);
	}
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		check(mid)?l=mid+1,res=mid:r=mid-1;
	}
	printf("%d\n",res);
}
```

---

## 作者：Sol1 (赞：6)

首先这题怎么着也不能是入门吧。。。

## 翻译

Little Beaver的信息学教师要过生日了，他种了$n$朵花想当作礼物，但是一段时间后他发现花不长了，他认为送特别小的花是不好的行为，就想了一种方案：

每一天，他会对于一个区间$(i, i+w-1)$进行一种特殊的浇水，让该区间内所有花的高度都增加1。

现在，距离生日还有$m$天，他想让花的最小高度最大。

### 输入格式

第一行有三个数，分别为$n$,$m$,$w$;

第二行有$n$个数，为每一朵花的初始高度

### 输出格式

一个数，表示最大的最小高度

### 说明

$1<=n,m,w<=10^{5},a[i]<=10^{9}$

## 思路

1.我们很容易想到模拟，但是复杂度为$O(N^{2})$，对于$10^{5}$是过不了的，于是将目标转向$O(NlogN)$。

2.由log很容易想到二分，然而开始写了，却发现判断可行处依然要$O(N^{2})$复杂度，如何写出$O(N)$判断呢？

## 答案：差分数组。

用差分数组求出$a[i]$,只需要求出$c[1]+c[2]+c[3]+...+c[i]$即可。用一个cur变量记录目前和，可以$O(1)$遍历数组。

区间$(L,R)$加x时，只需要$c[L]+x,c[R+1]-x$即可，$O(1)$完成更改！重大突破！

于是，$O(N)$判断实现了，看代码吧。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
long long N, M, W;
//h为高度，dis为差分
long long h[100010], dis[100010];
//判断
bool check(long long H)//H为目标最小高度
{
	long long cur = 0, dsum = 0;
	for (int i = 1;i <= N;i++)
	{
		cur += dis[i];//遍历
		if (cur < H)//需要浇水
		{
			dsum += H - cur;//增加天数
            //更改
			dis[i] += H - cur;
            //注意越界问题
			if(i + W <= N) dis[i + W] -= H - cur;
			cur += H - cur;//dis加了，cur当然也要加了
		}
		//for (int i = 1;i <= N;i++) printf("%d ",dis[i]);
		//printf("\n");
	}
	return dsum <= M;
}
int main()
{
	scanf("%lld%lld%lld", &N, &M, &W);
	long long l = 111111111, r = -1;
	for (int i = 1;i <= N;i++)
	{
		scanf("%lld", &h[i]);
        //开差分数组
		dis[i] = h[i] - h[i - 1];
        //l要保证合法，取最小
		l = min(h[i], l);
        //r要保证不合法，取最大，下面再加（天数+1）
		r = max(h[i], r);
	}
	//for (int i = 1;i <= N;i++) printf("%d ",dis[i]);
	//printf("\n");
	r += M + 1;
    //二分
	while (l < r - 1)
	{
		long long m = (l + r) / 2;
		if (check(m)) l = m;//合法
		else r = m;//不合法
		//cout<<l<<" "<<r<<" "<<m<<endl;
        //重新计算差分数组（check已经将其更改）
		for (int i = 1;i <= N;i++)
			dis[i] = h[i] - h[i - 1];
	}
	printf("%lld", l);//输出合法值
	return 0;
}
```

---

## 作者：IntrepidStrayer (赞：2)

题目要求最小值最大，那么不难想到二分。最小值越大，显然操作次数也越多。数列中小于当前二分到的最小值的数都应该进行操作。至于如何判定当前方案是否可行，这里给出两种方法。

## 方法一：二分+树状数组/线段树

在从左往右操作的过程中，如果来到了 $a_i$，就要使 $[1,i-1]$ 内的数全部合法（大于或等于最小值）。这样一来，对于每个不合法的 $a_i$，我们只需考虑对 $a_i$ 及 $a_i$ 右边的数进行操作。当前操作的区间就应为 $[i,i+w-1]$，操作次数为 $mid-a_i$（$mid$ 是当前二分到的最小值）。

那么只要区间加，单点查询，用树状数组或线段树即可。时间复杂度 $\operatorname{O}(n\log m\log n)$。

## 方法二：二分+前缀和

还是二分，还是用前面提到的操作策略。原来我们计算 $a_i$ 对其他数的影响，不妨换一个角度，对于每个 $a_i$，考虑其他数对它的影响。

令 $b_i$ 表示 $[i,i+w-1]$ 的区间操作了多少次。能够对 $a_i$ 产生影响的操作区间是 $[i-w+1,i],[i-w+2,i+1]\dots[i-1,i+w-2]$（$[i,i+w-1]$ 是当前求的区间，不算在内）。那么 $a_i$ 就变成了 $a_i+\sum\limits_{k=i-w+1}^{i-1}b_k$，若现在的 $a_i$ 仍不合法，$b_i$ 应为 $mid-a_i$。计算区间和，并且只在末尾插入一个数，这个可以用前缀和处理。

时间复杂度 $\operatorname{O}(n\log m)$。

## 注意

1. 防止数组越界，当下标可能为负数的时候与 $0$ 取 $\max$，可能超过 $n$ 的时候与 $n$ 取 $\min$。

2. 经过 $m$ 次操作，数列中最小值一定不超过 $\min\{a_i\}+m$。所以二分边界为 $\min\{a_i\}$ 和 $\min\{a_i\}+m$。

## 参考代码

### 方法一

```cpp
inline void add(int i, int x) {
	for(; i <= n; i += i & -i) bit[i] += x;
}

inline int query(int i) {
	int res = 0;
	for(; i; i -= i & -i) res += bit[i];
	return res;
}

bool check(int k) {
	int x, res = 0;
	memset(bit, 0, sizeof(bit));
	rep(i, 1, n) add(i, a[i] - a[i - 1]);
	rep(i, 1, n) {
		x = query(i);
		if(x >= k) continue;
		res += k - x;
		if(res > m) return false;
		add(i, k - x);
		add(min(i + w, n + 1), x - k);
	}
	return true;
}

signed main() {
	int l = 1e9, r = 0, mid, ans = 0;
	n = read(); m = read(); w = read();
	rep(i, 1, n) {
		a[i] = read();
		l = min(l, a[i]);
	}
	r = l + m;
	while(l <= r) {
		mid = l + r >> 1;
		if(check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
```
### 方法二

```cpp
bool check(int k) {
	int x, res = 0;
	memset(bit, 0, sizeof(bit));
	rep(i, 1, n) {
		x = a[i] + bit[i - 1] - bit[max(i - w, 0)];
		bit[i] = bit[i - 1];
		if(x >= k) continue;
		bit[i] += k - x;
		if(bit[i] > m) return false;
	}
	return true;
}
//main 略
```

---

## 作者：封禁用户 (赞：2)

搞毛线啊

表示我代码又臭又长复杂度还劣，但是是另一种方法，就发下吧

线段树，查询单点信息，区间修改每次建树

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
int n, m, w, a[100005], sum[100005];
struct SegmentTree
{
	int l, r, mi, lazy;
}Tree[100005 << 3];
inline void pushup(int x)
{
	Tree[x].mi = min(Tree[x << 1].mi, Tree[x << 1 | 1].mi);
	return;
}
inline void pushdown(int x)
{
	int oo = Tree[x].lazy;
	Tree[x << 1].lazy += oo;
	Tree[x << 1].mi += oo;
	Tree[x << 1 | 1].lazy += oo;
	Tree[x << 1 | 1].mi += oo;
	Tree[x].lazy = 0;
	return;
}
inline void build(int l, int r, int x)
{
	Tree[x].l = l;
	Tree[x].r = r;
	Tree[x].lazy = 0;
	if (l == r)
	{
		Tree[x].mi = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, x << 1);
	build(mid + 1, r, x << 1 | 1);
	pushup(x);
	return;
}
inline int query(int pos, int x)
{
	if (Tree[x].l == Tree[x].r)
	return Tree[x].mi;
	if (Tree[x].lazy != 0)
	pushdown(x);
	int mid = (Tree[x].l + Tree[x].r) >> 1;
	if (pos <= mid)
	return query(pos, x << 1);
	else
	return query(pos, x << 1 | 1);
}
inline void updata(int l, int r, int x, int val)
{
	if (l <= Tree[x].l && Tree[x].r <= r)
	{
		Tree[x].lazy += val;
		Tree[x].mi += val;
		return;
	}
	if (Tree[x].lazy != 0) pushdown(x);
	if (Tree[x].l > r || Tree[x].r < l) return;
	int mid = (Tree[x].l + Tree[x].r) >> 1;
	if (l <= mid) updata(l, r, x << 1, val);
	if (mid <= r) updata(l, r, x << 1 | 1, val);
	pushup(x);
}
inline bool judge(int mid)
{
	int mm = m;
	for(int i = 1; i <= n; i++)
	{
		int pp = query(i, 1);
		if (pp < mid)
		{
			int oo = mid - pp;
			mm -= oo;
			if (mm < 0) 
			return false;
			else
			updata(i, min(i + w - 1, n), 1, oo);
		}
	}
	return true;
}
signed main()
{
	while(~ scanf("%lld%lld%lld", &n, &m, &w))
	{
		for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
		int l = 1, r = 1e15;
		while(l <= r)
		{
			build(1, n, 1);
			int mid = (l + r) >> 1;
			if (judge(mid))
			l = mid + 1;
			else
			r = mid - 1;
		}
		printf("%lld\n", r);
	}
}
```

---

## 作者：When (赞：1)

#### 算法

二分答案+线段树

#### 思路

显然，这题正着不太好推，那么就考虑二分答案，有一个很大的问题，我们需要在$O(n\log n)$或者$O(n)$的时间内判断我们二分答案的可行性。首先肯定想到贪心，但是你会发现每一个元素需要加的值不一样，加了值以后影响的范围也不一样，并不好维护。

因为涉及到区间修改，考虑使用线段树。我们维护每一位置已经加了多少。

首先明确什么情况下是必须操作一次的（当前值小于二分所得的最小值的前提下）：

+ 当前节点已经加的值小于需要加的值

而对于每一次操作，我们可以用线段树方便地进行区间加。至于每一个点已经加的值，单点查询就可以了。

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 1e5 + 10;
int n,m,w,a[maxn];

struct Seg_Tree{
    #define lc(x) x << 1
    #define rc(x) x << 1 | 1
    int c[maxn << 2],tag[maxn << 2];
    
    void clear(){
        memset(c,0,sizeof(c));
        memset(tag,0,sizeof(tag));
    }
    
    void f(int l, int r, int p, int x){
        c[p] += (r - l + 1) * x;
        tag[p] += x;
    }
    
    void downdate(int l, int r, int p){
        if(tag[p]){
            int mid = (l + r) >> 1;
            f(l, mid, lc(p), tag[p]);
            f(mid + 1, r, rc(p), tag[p]);
            tag[p] = 0;
        }
    }
    
    void add(int L, int R, int l, int r, int p, int x){
        if(L <= l && R >= r){
            f(l, r, p, x);
            return;
        }
        downdate(l, r, p);
        int mid = (l + r) >> 1;
        if(mid >= L) add(L, R, l, mid, lc(p), x);
        if(mid < R) add(L, R, mid + 1, r, rc(p), x);
        c[p] = c[lc(p)] + c[rc(p)];
    }
    
    int query(int l, int r, int p, int pos){
        if(l == r) return c[p];
        downdate(l, r, p);
        int mid = (l + r) >> 1;
        if(mid >= pos) return query(l, mid, lc(p), pos);
        else return query(mid + 1, r, rc(p), pos);
    }
}tree;

inline int check(int mid){
    int cnt = 0, flag = 1; tree.clear();  //记得清空
    for(int i = 1; i <= n; ++ i){
        if(a[i] < mid){
            int val = tree.query(1, n, 1, i);
            if(val < mid - a[i]){
                cnt += mid - a[i] - val;
                tree.add(i, i + w - 1, 1, n, 1, mid - a[i] - val);
            } 
        } 
        if(cnt > m){flag = 0; break;}
    }
    if(cnt > m || !flag) return 0;
    else return 1;
}

int main(){
    int h = 0x3f3f3f3f, l = 0x3f3f3f3f, mid; //这里h不能设成1e9+10，因为答案可能会大于它
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; ++ i){
        scanf("%d", a + i);
        l = min(l, a[i]);
    }
    
    while(h >= l){
        mid = (h + l) >> 1;
        if(!check(mid)) h = mid - 1;
        else l = mid + 1;
    } printf("%d\n", l - 1);
    return 0;
}
```



---

## 作者：Harmony (赞：1)

首先通过题目对于答案“最小值最大”我们可以想到使用二分答案来查找最终的结果。

然后就是每次的check函数。我们需要把所有的元素都加到我们二分的ans.而通过贪心我们发现，我们可以从最左端开始，依次向右边找到小于答案的数，然后以他们为左端点扫(后面w个元素加1)，直到它变成0。我们再记录加的次数，让它小于m则此答案是可行。

以上过程可以简化到以下做法：
	
    cnt = 0;
	for i = 1 to n
    {
    	if a[i] < ans
        {
        	a[i, i + w - 1] += ans - a[i];
            cnt += ans - a[i];
            if cnt > m
            	break;
        }
	}

而这里我们需要一个数据结构来维护区间加减和单点查询。树状数组即可。

code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#define NO 100005
#define INF 0x3f3f3f3f
typedef long long ll;
//by Oliver
using namespace std;
ll read()
{
    char ch = ' ', last;
    ll ans = 0;
    while(ch < '0' || ch > '9')
        last = ch, ch = getchar();
    while(ch >= '0' && ch <= '9')
        ans *= 10, ans += ch - '0', ch = getchar();
    if(last == '-')
        return -ans;
    return ans;
}
//head

ll n, m, w, a[NO], d[NO], k;
//variable

ll lowbit(ll x)
{
    return x & -x;
}
void add(ll pos, ll val)
{
    for(int i = pos; i <= n; i += lowbit(i))
        d[i] += val;
}
ll ask(ll pos)
{
    ll ans = 0;
    for(ll i = pos; i; i -= lowbit(i))
        ans += d[i];
    return ans;
}
void init()
{
    n = read(), m = read(), w = read();
    for(ll i = 1; i <= n; i++)
        a[i] = read();
}
bool check(ll ans)
{
    memset(d, 0, sizeof(d));
    ll last = 0;
    for(ll i = 1; i <= n; i++)
        add(i, a[i] - ans - last), last = a[i] - ans;
    ll cnt = 0;
    for(ll i = 1; i <= n; i++)
    {
        ll askn = ask(i);
        if(askn < 0)
        {
            cnt += -askn;
            if(cnt > m)
                return false;
            add(i, -askn), add(i + w, askn);
        }
    }
    return true;
}
//functinos

int main()
{
    init();  
    ll l = 1, r = 1000200000;//注意这里。答案可能到m + amax = 1e9 + 1e5, 以防万一我们开到1e9 + 2e5.
    while(l <= r)
    {
        ll mid = (l + r) / 2;
        if(check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout<<l - 1<<endl;
    return 0;
}
//main
```

---

## 作者：Suzt_ilymtics (赞：0)

# 二分答案 + 差分

题目让我们最大化最小值，虽然有着线段树的标签，但不难想到可以用二分答案来做

## 单调性证明

每个元素，操作一次元素值加一，操作的越多，值越高

所以元素值随操作次数的增加而增加

不难看出是单调递增

## 如何二分

考虑给定一个最低限度值$mid$

即尝试让每个元素都达到最低限度值$mid$，看看需要操作的次数是否小于给定的次数$m$

如果小于给定次数$m$，则二分提高最低限度值$mid$

否则，二分降低最低限度值$mid$

## 二分范围

（其实直接0 ~ 1e10也没啥大问题）

（1e10要记得开long long）

考虑最优情况，找到一个最小元素$a_i$，把所有的操作都给它，它巧好还是最小值，那么答案就是$a_i + m$

考虑最差情况，就是序列中的最小值$a_i$

## 差分优化

因为同时操作的是一个序列，所以暴力加值太慢了，容易T掉

因此可以用差分来维护这个序列

注意每次二分后都要将这个序列重新赋值，因为上一次二分时已经将它的值改变了

### 双手奉上AC代码

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#define INF 1000010000
using namespace std;
const int MAXN = 1e5+5;
long long n, m, w, ans, minn = INF;
long long a[MAXN], b[MAXN], cnt[MAXN];
bool vis[MAXN];
long long tree[MAXN << 1];

int lowbit(int x){return x & (-x); }

void add(int x, int k){
	for(int i = x; i <= n; i += lowbit(i))
		tree[i] += k; 
}

int getsum(int x){
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)) ans+=tree[i];
}

bool check(int mid){
	for(int i = 1; i <= n; ++i) tree[i] = b[i];
	long long day = 0, sum = 0;
	for(int i = 1; i <= n; ++i){
		sum += tree[i];
		if(sum < mid){
			day += mid - sum;
			tree[i] += (mid - sum);
			tree[i + w] += (sum - mid);
			//add(i, (mid - sum));
			//add(i + w + 1, (sum - mid));
			sum = mid;
		}
	}
	if(day <= m) return true;
	else		 return false;
}

void ef(int l, int r){
	long long mid;
	mid = ((l + r) /2);
	//------
	//cnt[mid]++;
	//cout<<l<<" "<<mid<<" "<<r<<endl;
	//if(cnt[mid] >= 10) return ;
	//-------
	if(l > r) return ;
	if(check(mid))	{//l = 9, r = 10, mid = 9, check(9) = true
		ans = mid;
		ef(mid + 1, r);	
	}
	else{
		ef(l, mid - 1);	
	} 	
}

int main()
{
	scanf("%d%d%d", &n ,&m, &w);
	for(int i = 1; i <= n; ++i)	{
		scanf("%d", &a[i]),	b[i] = a[i] - a[i-1];
		minn = min(minn, a[i]);
	}
	
	ef(minn - 1, minn + m + 1);
	
	printf("%d", ans);
	
	return 0;	
}
```


---

## 作者：STPGUY (赞：0)

# [Present](https://www.luogu.com.cn/problem/CF460C)

## 题目大意:

先给你一串序列,你至多有$\text{m}$次操作使得一段长度为$w$的区间加一

问这串序列的最小值最大可以是多少?

## 分析:
最小值最大或者最大值最小,我们的第一反应可能都是二分答案
> 简单证明一下:
> > 如果最小值最大为$x$,那么只要我们少做一次操作,那么$x-1$也是可行的

> > 这满足二分答案的性质,所以呢二分答案没有问题的

那么关于$check$函数的话,如果当前我们枚举到的数他小于这个我们$\text{check}$的值,那么我们就给这一段区间加上这个差值(如果可以加,否则返回零)

那么时间复杂度大概就是$O(\log10^9*n)$,可以接受的

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll maxn = 1e5 + 10;
const ll mod = 1e9 + 7;

inline ll __read()
{
    ll x(0), t(1);
    char o (getchar());
    while (o < '0' || o > '9') {
        if (o == '-') t = -1;
        o = getchar();
    }
    for (; o >= '0' && o <= '9'; o = getchar()) x = (x << 1) + (x << 3) + (o ^ 48);
    return x * t;
}

ll n, m, w, a[maxn];
ll CF[maxn], temp[maxn];
ll l(0x7fffffff), r, ans;

inline bool Check(ll x) 
{
    memcpy(temp + 1, CF + 1, sizeof(ll) * n);
    ll now(0), rest(m);
    for (ll i = 1; i <= n; ++i) {
        now += temp[i];
        if (now >= x) continue;
        if (now + rest < x) return 0;
        ll get = x - now;
        rest -= get;
        now += get;
        if (i + w <= n) temp[i + w] -= get;
    }
    return 1;
}

signed main()
{
    n = __read(), m = __read(), w = __read();
    for (ll i = 1; i <= n; ++i)  {
        a[i] = __read();
        CF[i] = a[i] - a[i - 1];
        l = min(l, a[i]), r = max(r, a[i]);
    }
    r += m;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (Check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf ("%lld\n", ans);
    system("pause");
}
```

---

## 作者：斗神_君莫笑 (赞：0)

最小最大，直接条件性反射上二分  
本题坑不多，注意二分的边界问题和线段树每次清0  
```cpp
#include<bits/stdc++.h>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
long long a[100010];
struct Node{
	int l,r;long long lazy,sum;
}T[400010];
inline void pushup(int p){
	T[p].sum=min(T[lc].sum,T[rc].sum);
}
void build(int p,int l,int r){
	T[p].l=l,T[p].r=r;
	if(l==r){
		T[p].sum=a[l];return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(p);
}
inline void pushnow(int p,int v){
	T[p].sum+=v;T[p].lazy+=v;
}
void pushdown(int p){
	if(T[p].lazy){
		pushnow(lc,T[p].lazy);
		pushnow(rc,T[p].lazy);
		T[p].lazy=0;
	}
}
void update(int p,int ql,int qr,long long v){
	if(ql<=T[p].l&&T[p].r<=qr){
		pushnow(p,v);return;
	}
	pushdown(p);
	int mid=(T[p].l+T[p].r)>>1;
	if(ql<=mid)update(lc,ql,qr,v);
	if(qr>mid)update(rc,ql,qr,v);
	pushup(p);
}
long long query(int p,int ql,int qr){
	if(ql<=T[p].l&&T[p].r<=qr)
		return T[p].sum;
	pushdown(p);
	int mid=(T[p].l+T[p].r)>>1;
	long long ans=0;
	if(ql<=mid)ans+=query(lc,ql,qr);
	if(qr>mid)ans+=query(rc,ql,qr);
	return ans;
}
int n,m,w;
int check(int mid){
	//cout<<mid<<endl;
	memset(T,0,sizeof(T));
	build(1,1,n);
	int rest=m;
	for(int i=1;i<=n;++i){
		int now=query(1,i,i);
		if(now<mid)
			update(1,i,min(i+w-1,n),mid-now),rest-=(mid-now);
		if(rest<0)return 0;
		//cout<<rest<<" ";
	}
	//cout<<endl;
	//if(rest<0)return 0;
	return 1;
}
int main(){
	//freopen("std.in","r",stdin);
	//freopen("my.out","w",stdout);
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	build(1,1,n);
	int l=T[1].sum,r=T[1].sum+m,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)==1)ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
```


---

