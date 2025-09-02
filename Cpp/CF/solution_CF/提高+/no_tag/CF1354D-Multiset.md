# Multiset

## 题目描述

Note that the memory limit is unusual.

You are given a multiset consisting of $ n $ integers. You have to process queries of two types:

- add integer $ k $ into the multiset;
- find the $ k $ -th order statistics in the multiset and remove it.

 $ k $ -th order statistics in the multiset is the $ k $ -th element in the sorted list of all elements of the multiset. For example, if the multiset contains elements $ 1 $ , $ 4 $ , $ 2 $ , $ 1 $ , $ 4 $ , $ 5 $ , $ 7 $ , and $ k = 3 $ , then you have to find the $ 3 $ -rd element in $ [1, 1, 2, 4, 4, 5,       7] $ , which is $ 2 $ . If you try to delete an element which occurs multiple times in the multiset, only one occurence is removed.

After processing all queries, print any number belonging to the multiset, or say that it is empty.

## 说明/提示

In the first example, all elements of the multiset are deleted.

In the second example, the elements $ 5 $ , $ 1 $ , $ 4 $ , $ 2 $ are deleted (they are listed in chronological order of their removal).

In the third example, $ 6 $ is not the only answer.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
-1 -1 -1 -1 -1```

### 输出

```
0```

## 样例 #2

### 输入

```
5 4
1 2 3 4 5
-5 -1 -3 -1```

### 输出

```
3```

## 样例 #3

### 输入

```
6 2
1 1 1 2 3 4
5 6```

### 输出

```
6```

# 题解

## 作者：Lskkkno1 (赞：11)

- [CF1354D Multiset](https://www.luogu.com.cn/problem/CF1354D)

### 题目描述

要你维护一个可重集，每次操作插入一个数 $k$， 或者删除第 $k$ 大元素。

询问最后是否还有元素，如果有则任意输出一个元素。

### 正解

虽然这题直接上线段树就可以过这题，但是其实还有时空更加优秀的做法。

二分答案 $x$，判断是否最后剩下一个小于等于 $x$ 的元素。

把元素看成两类数，一类小于等于 $x$，另一类大于 $x$。

这样只需要记录两个桶 $l_{siz}$ 和 $r_{siz}$ 就可以 $O(1)$ 进行插入或者删除操作了。

时间复杂度 $O(n \log V)$，空间复杂度 $O(n)$。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, q;
int a[N], b[N];

inline int read() {
    int x = 0; bool neg = false; char ch = getchar();
    while(!isdigit(ch)) (ch == '-') && (neg = true), ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return neg ? -x : x;
}

bool check(int x) {
    int lsiz = 0, rsiz = 0;
    for(int i = 1; i <= n; ++i)
        if(a[i] <= x) {
            ++lsiz;
        } else {
            ++rsiz;
        }
    for(int i = 1; i <= q; ++i) {
        if(b[i] < 0) {
            if(-b[i] <= lsiz) --lsiz;
            else --rsiz;
        } else {
            if(b[i] <= x) ++lsiz;
            else ++rsiz;
        }
    }
    return lsiz > 0;
}


int main() {
    n = read(), q = read();
    int rem = n;
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    for(int i = 1; i <= q; ++i) {
        b[i] = read();
        if(b[i] < 0) --rem;
        else ++rem; 
    }

    if(rem <= 0) {
        puts("0");
        return 0;
    }

    int l = 1, r = n, mid, mp = n;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(check(mid)) {
            if(mp > mid) mp = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    printf("%d\n", mp);
    return 0;
}
```

---

## 作者：andyli (赞：10)

### 解法一

时间复杂度 $\mathcal O(n\log^2n)$

注意到 $1\leq a_i\leq n$ ，因此开一个值域树状数组存值出现次数，修改时直接修改 $\mathcal O(\log n)$ ，查询时二分排名为 $-x$ 的数字，再进行修改，$\mathcal O(\log^2 n)$。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
constexpr int maxn = 1000005;

int C[maxn], n;
void modify(int p, int v) {
    while (p <= n) {
        C[p] += v;
        p += lowbit(p);
    }
}
int query(int p) {
    int ans = 0;
    while (p) {
        ans += C[p];
        p -= lowbit(p);
    }
    return ans;
}
int main() {
    int q;
    io.read(n, q);
    for (int i = 1; i <= n; i++)
        modify(io.read<int>(), 1);
    while (q--) {
        int x;
        io.read(x);
        if (x >= 1)
            modify(x, 1);
        else {
            x = ~x + 1;
            int l = 1, r = n;
            while (l < r) {
                int m = (l + r) >> 1;
                if (query(m) < x)
                    l = m + 1;
                else
                    r = m;
            }
            modify(l, -1);
        }
    }
    for (int i = 1; i <= n; i++)
        if (query(i))
            return writeln(i), 0;
    writeln(0);
    return 0;
}
```

### 解法二

时间复杂度 $\mathcal O(n\log n)$  

同上，注意到 $1\leq a_i\leq n$ ，因此开一个值域线段树，$\mathcal O(\log n)$ 查询 $k$ 小值，修改。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int sum[2097152];
void modify(int o, int l, int r, int p, int v) {
    sum[o] += v;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (p <= m)
        modify(lc, l, m, p, v);
    else
        modify(rc, m + 1, r, p, v);
}
int query(int o, int l, int r, int k) {
    if (l == r)
        return l;
    int m = (l + r) >> 1;
    if (k <= sum[lc])
        return query(lc, l, m, k);
    return query(rc, m + 1, r, k - sum[lc]);
}
int dfs(int o, int l, int r) {
    if (l == r)
        return l;
    int m = (l + r) >> 1;
    if (sum[lc])
        return dfs(lc, l, m);
    return dfs(rc, m + 1, r);
}
int main() {
    int n, q;
    io.read(n, q);
    for (int i = 1; i <= n; i++)
        modify(1, 1, n, io.read<int>(), 1);
    while (q--) {
        int x;
        io.read(x);
        if (x >= 1)
            modify(1, 1, n, x, 1);
        else
            modify(1, 1, n, query(1, 1, n, ~x + 1), -1);
    }
    writeln(!sum[1] ? 0 : dfs(1, 1, n));
    return 0;
}
```

## 解法三

时间复杂度 $\mathcal O(n\log n)$  

注意到我们只需要找到一个属于可重集的数字。考虑二分可重集中最小的数字。$f(x)$ 表示小于等于 $x$ 的元素数量，当 $f(mid) > 0$ 时，可行区间缩小为左半段 ，否则缩小为右半段。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
constexpr int maxn = 1000005;

int A[maxn], B[maxn], n, q;
int count(int x) {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += A[i] <= x;
    for (int i = 1; i <= q; i++)
        cnt += (B[i] > 0 && B[i] <= x), cnt -= (B[i] < 0 && (~B[i] + 1) <= cnt);
    return cnt;
}
int main() {
    io.read(n, q);
    for (int i = 1; i <= n; i++)
        io.read(A[i]);
    for (int i = 1; i <= q; i++)
        io.read(B[i]);
    if (!count(n))
        return writeln("0"), 0;
    int l = 1, r = n;
    while (l < r) {
        int m = (l + r) >> 1;
        if (count(m) > 0)
            r = m;
        else
            l = m + 1;
    }
    writeln(l);
    return 0;
}
```

---

## 作者：Werner_Yin (赞：3)

考试拿到题，一看，~~这不是权值线段树吗？~~

### 思路

使用线段树每个节点维护该区间内元素出现次数。

根据题目，对于加入、删除元素，我们可以单点修改（$+1$、$-1$），对于输出，我们可 ~~随便~~ 遍历找一个出现次数为 $1$ 的元素即可。

### 代码
具体解释见注释
```cpp
#include<bits/stdc++.h>
#define re read()
using namespace std;
const int MAXN=1e6+10;
int n,q,A[MAXN];
struct SEGTREE{
	int sum;//sum 最大为10^6 无需long long(我第一次手残开了，然后爆了空间）
}tr[MAXN<<2];
int read(){//快读
	#define gt getchar()
	#define isdi(a) (a>='0'&&a<='9')
	int x=0,sgn=1;char ch=gt;
	for(;!isdi(ch);ch=gt)if(ch=='-')sgn=-1;
	for(;isdi(ch);ch=gt)x=(x<<1)+(x<<3)+(ch^48);
	return x*sgn;
}
void build(int k,int l,int r){ //建树
	if(l==r){
		tr[k].sum=A[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	tr[k].sum=tr[k<<1].sum+tr[k<<1|1].sum;
	return;
}
void add(int k,int l,int r,int num){//加入元素
	if(l==r){
		if(l==num)tr[k].sum++;
		return;
	}
	int mid=(l+r)>>1;
	if(num>mid)add(k<<1|1,mid+1,r,num);
	else add(k<<1,l,mid,num);
	tr[k].sum++;
	return;
}
void del(int k,int l,int r,int num){
//删除该区间内第num大的元素
	if(l==r){
		if(tr[k].sum)tr[k].sum--;
		return;
	}
	if(num>tr[k].sum)return;
	int mid=(l+r)>>1;
	if(num>tr[k<<1].sum)del(k<<1|1,mid+1,r,num-tr[k<<1].sum);
//如果num大于左子树元素出现的总次数，则去右子树删第（num-左子树元素出现总次数）大的数
	else if(num<=tr[k<<1].sum)del(k<<1,l,mid,num);
//否则去左子树删除第num大的数
	else return;
	tr[k].sum--;
//该区间内的次数减一
	return;
}
int find(int k,int l,int r){//递归查找
	if(l==r){
		if(tr[k].sum)return l;
		return 0;
	}
	int mid=(l+r)>>1;
	if(tr[k<<1].sum)return find(k<<1,l,mid);
	else return find(k<<1|1,mid+1,r);
	return 0;
//根据题目，随便找一个就行了，找不到就输出0
}
int main (){
	n=re;q=re;
	for(int i=1;i<=n;i++){
		int temp=re;
		A[temp]++;
	}
	build(1,1,n);
	for(int i=1;i<=q;i++){
		int k=re;
		if(k<0)del(1,1,n,-k);
		else add(1,1,n,k);
	}
	printf("%d",find(1,1,n));
	return 0;
}
```


---

## 作者：Eason2009 (赞：2)

线段树上二分简单题。

------------
思路：看到值域，单点加，区间 rank，我们就可以使用权值线段树（也叫值域线段树）进行求解。

对于初始的建树和单点加，都是非常简单的。

难点就在于区间 rank。

这里我放上区间 rank 有注释的代码，让大家理解。

```cpp
//大致思想就是在线段树上二分
int query(int now,int l,int r,int k)
{
	if(l==r) return l;//二分已到达边界，直接输出
	int mid=l+r>>1;
	if(k<=sum[now*2]) return query(now*2,l,mid,k);//sum[now*2]代表l-mid这个区间内有多少个数，如果区间内的数比k多，递归查询左子树
	else return query(now*2+1,mid+1,r,k-sum[now*2]);//若l-mid区间内的数比k少，将k减去区间内的数的数量（也就是sum[now*2]），再递归查询右子树
}
```
那么现在这个题只剩下了最后一个操作：输出。

同样我们可以使用递归求解：
```cpp
int qry(int now,int l,int r)
{
	if(l==r&&sum[now])//已经到了叶子节点，说明这个数一定存在，直接输出
	{
		return l;
	}
	int mid=l+r>>1;
	if(sum[now*2]) return qry(now*2,l,mid);//若左子树内存在数，递归左子树
	else if(sum[now*2+1]) return qry(now*2+1,mid+1,r);//若右子树内存在数，递归右子树
	else return 0;//左右子树都为空，说明数列已经被删空，输出0（这里翻译的题面是有点问题的，没有提到这一点）
}
```
由于题目中只需要输出任意一个数，这个输出方式也是正确的！

接下来放完整代码（线段树常数大，所以加了快读快写）：
```cpp
#include<bits/stdc++.h>
#define maxn 4000005
using namespace std;
int n,q,a[1000005],sum[maxn],ans;
inline int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return ans*f;
}
inline void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void pushup(int now)
{
	sum[now]=sum[now*2]+sum[now*2+1];
	return;
}
int query(int now,int l,int r,int k)
{
	if(l==r) return l;
	int mid=l+r>>1;
	if(k<=sum[now*2]) return query(now*2,l,mid,k);
	else return query(now*2+1,mid+1,r,k-sum[now*2]);
}
void modify(int now,int l,int r,int x,int k)
{
	if(l==r)
	{
		sum[now]+=k;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) modify(now*2,l,mid,x,k);
	else modify(now*2+1,mid+1,r,x,k);
	pushup(now);
	return;
}
int qry(int now,int l,int r)
{
	if(l==r&&sum[now])
	{
		return l;
	}
	int mid=l+r>>1;
	if(sum[now*2]) return qry(now*2,l,mid);
	else if(sum[now*2+1]) return qry(now*2+1,mid+1,r);
	else return 0;
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		modify(1,1,n,a[i],1);
	}
	while(q--)
	{
		int k;
		k=read();
		if(k<0)
		{
			k=-k;
			if(sum[1]<k) continue;
			int del=query(1,1,n,k);
			modify(1,1,n,del,-1);
		}
		else modify(1,1,n,k,1);
	}
	cout<<qry(1,1,n);
	return 0;
}
```
最后，祝大家学习愉快![](//图.tk/3)

---

## 作者：囧仙 (赞：2)

## 题目大意

有一串$n$个正整数的数列$\{A_i\}$，它们的值域为$[1,n]$。现在有$q$个操作，共有两类：

- $1.$删除排名为$k$的数字。若没有，则忽略这次操作。

- $2.$加入数字$k$，满足$k\in[1,n]$。

$n,q\le 1\times 10^6$。空间限制：$\rm 28MB$。

最后输出任意一个数列中存在的数字即可。

## 题解

$10^6$个$\rm int$占用的内存是$\rm 4MB$，因此我们只需要用空间复杂度常数较小的结构就可以轻松地过去了……

由于值域在$[1,n]$内，考虑值域树状数组维护一个桶。

### 操作$2$
加入一个数字$k$，显然直接在桶的下标$k$处加一就可以了。


### 操作$1$

查询$k$大，可以用值域树状数组来写。我们可以用值域树状数组查询到大小在$[1,x]$中所有数字出现过的次数之和。显然，这个值单调不减。用树状数组查询$k$大，有一个好处，就是$C_{p+2^q}$的值，就是$[p,p+2^q]$的值。具体证明可以参照树状数组的定义。于是，我们从大到小枚举$q$，然后判断是否要让当前的$p$加上$2^q$即可。

### 关于空间限制

这题有$\rm 28MB$的限制。虽然他卡不动树状数组，但是这里还是提供一个简单的卡空间的办法。由于桶中每个数字不超过$2^{21}$，因此我们可以将一个$\rm unsigned\_long\_long$类型的数据存储三个元素。这样，可以节省$\frac{1}{3}$的空间。

具体而言，我们开一个存放数据的内存数组$M$。当查询下标$x$时，我们根据$\left\lfloor\frac{x}{3}\right\rfloor$定位出$x$存放在了$M$的哪一位；再根据$x$除以$3$的余数，得出在这一位的哪一段；再使用位运算取出这一段即可。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =1e6+3;
typedef unsigned long long u64;
typedef unsigned int u32;
u64 M[MAXN/3];
u32 get(int idx){
    int p=idx/3;
    switch(idx%3){
        case 0: return (M[p]&0b111111111111111111111000000000000000000000000000000000000000000)>>42;
        case 1: return (M[p]&0b000000000000000000000111111111111111111111000000000000000000000)>>21;
        default: return M[p]&0b000000000000000000000000000000000000000000111111111111111111111;
    }
}
void add(int idx,int w){
    int p=idx/3;
    if(w>0) switch(idx%3){
        case 0: M[p]+=(LL)w<<42; break;
        case 1: M[p]+=(LL)w<<21; break;
        case 2: M[p]+=(LL)w;     break;
    } else{
        w=-w;
        switch(idx%3){
            case 0: M[p]-=(LL)w<<42; break;
            case 1: M[p]-=(LL)w<<21; break;
            case 2: M[p]-=(LL)w;     break;
        }
    }
}
#define C(x) (x&-x)
int n,q,tot;
void inc(int idx){
    while(idx<=n) add(idx,1),idx+=C(idx);
}
void dec(int idx){
    while(idx<=n) add(idx,-1),idx+=C(idx);
}
int  kth(int x){
    int p=0,k=1<<21; for(;k;k>>=1){
        if((p|k)<=n&&get(p|k)<x)  x-=get(p|k),p|=k;
    }
    return p+1;
}
int main(){
    n=qread(),q=qread(),tot=n;
    up(1,n,i) inc(qread());
    up(1,q,i){
        int w=qread(); if(w<0){
            if(-w>tot) continue; else dec(kth(-w)),--tot; 
        }else inc(w),++tot;
    }
    if(tot==0) puts("0"),exit(0);
    printf("%d\n",kth(1));
    return 0;
}
```


---

## 作者：happybob (赞：1)

考虑求排名怎么做。

一种空间比较优秀的做法就是树状数组加二分找排名，即值域树状数组上二分。

然后删除即在树状数组上将数的值 $-1$ 即可。

复杂度应该是 $O(n \log n + q \log^2 n)$。常数有点大，加了快读卡一卡就过去了。

```cpp
#pragma GCC optimize("-Ofast,inline,fast-math")
#pragma GCC target("avx,sse,sse2,sse3,sse4")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1e6 + 5;

inline int read()
{
	char ch(getchar());
	int x = 0, o = 1;
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-') o = -o, ch = getchar();
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * o;
}

int n, a[N], q, k;

class Bit
{
public:
	int tr[N];
	void update(int u, int x)
	{
		while (u <= n)
		{
			tr[u] += x;
			u += u & -u;
		}
	}
	int query(int u)
	{
		int res = 0;
		while (u)
		{
			res += tr[u];
			u -= u & -u;
		}
		return res;
	}
}tr;

int main()
{
	n = read(), q = read();
	for (int i = 1; i <= n; ++i)
	{
		a[i] = read();
		tr.update(a[i], 1);
	}
	while (q--)
	{
		k = read();
		if (k < 0)
		{
			int l = 1, r = n, res = 0;
			while (l <= r)
			{
				int mid = l + r >> 1;

				if (tr.query(mid) >= -k)
				{
					r = mid - 1;
					res = mid;
				}
				else
				{
					l = mid + 1;
				}
			}
			if (res)
			{
				tr.update(res, -1);
			}
		}
		else
		{
			tr.update(k, 1);
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (tr.query(i) - tr.query(i - 1))
		{
			printf("%d\n", i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
```


---

## 作者：FiraCode (赞：0)

## 题解思路：
这个题有两个操作，先看第二个，就是加数操作。

那么我们就建一棵值域树状数组，然后就直接在 $x$ 的位置加一就可以了。

那么删除的话就可以二分，就是二分第一个满足值 $\le mid$ 的个数是否 $= \left | x \right |$ 就可以了。

这个的时间复杂度是 $O(n \log^2 n)$ 的时间复杂度，需要卡卡常数才可以过。
## AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int &read(int &r){//快读
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
int n, q;
template<class T>//线段树模板
struct BIT {
	int c[N];
	void modify(int x, int d) {
		if (x <= 0) return;
		for (; x <= n; x += (x & -x))
			c[x] += d;
	}
	T query(int x) {
		T res = 0;
		for (; x; x -= (x & -x))
			res += c[x];
		return res;
	}
};
BIT<int> c;
int main() {
	read(n), read(q);
	for (int i = 1; i <= n; ++i) {
		int a = read(a);
		c.modify(a, 1);//读入这个序列
	}
	for (int i = 1; i <= q; ++i) {
		int x = read(x);
		if (x > 0) c.modify(x, 1);//把这个x位置+1
		else {
			x = -x;//把x变成|x|
			x = (x < 0 ? -x : x);
			int l = 1, r = n, res = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (c.query(mid) >= x) {//若当前的值<=mid的数的个数是>=x，那么就可以更新答案了。
					res = mid;
					r = mid - 1;
				}else l = mid + 1;
			}
			c.modify(res, -1);//把这个减去
		}
	}
	int l = 1, r = n, res = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (c.query(mid) >= 1) {//就是求最小的那一个。
			res = mid;
			r = mid - 1;
		}else l = mid + 1;
	}
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：锡印鱼 (赞：0)

楼上神犇用的都是 ~~我听都没听过的东西~~。作为一个蒟蒻，只会用最简单的分块做。

时间复杂度插入$ O(1) $，删除$ O(\sqrt n) $，~~跑得飞快~~ 勉强能过qwq。

不了解分块的童鞋可以先移步至 [分块大法](https://www.luogu.com.cn/blog/Start-Dash/P3374)，当然这题并不需要那么多操作，只需了解基本概念即可。

题目数据$ a_i $最大到$1e6$,所以我们可以~~十分愉快地~~把$ 1e6 $分成$ 1000 $块，每块管$ 1000 $个数字。

记$ num_i $为数字$ i $出现的次数，$ fa_i $为第$ i $块中数字的个数，容易看出数字$ i $属于第$ \frac{i-1}{1000} $块，所以在插入时只需$ num_i $++，$ fa_\frac{i-1}{1000} $++即可；在删除时，分块的优势就体现出来了，一次可以判断一段，也就是$ 1000 $个数字。

详见代码

```cpp

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

int n, q;

int num[maxn], fa[1005];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> n >> q;
    int mx = 0; //记录出现的最大值，便于最后循环结束的判断，也可以不用。
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        num[x]++;             //桶中有的数+1
        fa[(x - 1) / 1000]++; //属于的块里有的数+1
        mx = max(mx, x);
    }
    while (q--) {
        int k;
        cin >> k;

        if (k > 0) {
            //插入操作 同读入
            num[k]++;
            fa[(k - 1) / 1000]++;
            mx = max(mx, k);
        }
        else {
            //删除操作
            k = -k; //别忘了k是负数

            //找第k个数属于第几块
            int index = 0;
            while (k > fa[index]) {
                k -= fa[index++];
            }

            // 此时已找到第k个数属于第index块，只需遍历这一块即可
            for (int i = index * 1000 + 1; i < index * 1000 + 1 + 1000; i++) {

                //找第k个数是多少
                if (k > num[i]) {
                    k -= num[i];
                }
                else {
                    //找到了第k个数
                    num[i]--; //桶-1
                    fa[(i - 1) / 1000]--; //属于的块里有的数-1
                    break;
                }
            }
        }
    }
    //找到数字就输出，没找到输出0。
    for (int i = 1; i <= mx; i++) {
        if (num[i]) {
            cout << i;
            return 0;
        }
    }
    cout << 0;
    return 0;
}

```




---

## 作者：XenonKnight (赞：0)

> ```Codeforces 1354D```

> 题意：维护一个可重集，支持：
> - 加入一个值为 $x$ 的元素。
> - 删除第 $x$ 大的元素。有多个就只删除一个

> 求最终集合中任意一个数

> $1 \leq n \leq 10^6$

考场上权值线段树码量略大，影响罚时？没事儿，树状数组+二分帮你解决问题。

开一棵权值树状数组（雾），第 $i$ 位表示值为 $i$ 的数的个数。

删除第 $k$ 个数就直接二分找出第 $k$ 个数。

加入数就在对应位置上 $+1$

最后扫一遍如果个数不为 $0$ 就直接输出就可以了。

时间复杂度两个 $\log$，众所周知，由于 CF 评测机速度之快与数据之弱，只跑了 $561ms$。

```cpp
/*
Contest: Educational Codeforces Round 87
Problem: 1354D
Author: tzc_wk
Time: 2020.5.17
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
int n=read(),m=read();
struct BIT{
	int bit[1000005];
	inline void add(int x,int y){
		for(int i=x;i<=n;i+=(i&(-i)))	bit[i]+=y;
	}
	inline int query(int x){
		int sum=0;
		for(int i=x;i;i-=(i&(-i)))	sum+=bit[i];
		return sum;
	}
} t;
signed main(){
	fz(i,1,n){
		int x=read();
		t.add(x,1);
	}
	fz(i,1,m){
		int x=read();
		if(x>0){
			t.add(x,1);
		}
		else{
			x=-x;
			int l=1,r=n,k=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(t.query(mid)>=x)	k=mid,r=mid-1;
				else				l=mid+1;
			}
//			cout<<k<<endl;
			t.add(k,-1);
		}
	}
	fz(i,1,n){
		if(t.query(i)-t.query(i-1)){
			cout<<i<<endl;
			return 0;
		}
	}
	puts("0");
	return 0;
}
```

---

