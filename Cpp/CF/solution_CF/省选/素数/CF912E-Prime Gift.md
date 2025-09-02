# Prime Gift

## 题目描述

Opposite to Grisha's nice behavior, Oleg, though he has an entire year at his disposal, didn't manage to learn how to solve number theory problems in the past year. That's why instead of Ded Moroz he was visited by his teammate Andrew, who solemnly presented him with a set of $ n $ distinct prime numbers alongside with a simple task: Oleg is to find the $ k $ -th smallest integer, such that all its prime divisors are in this set.

## 说明/提示

The list of numbers with all prime divisors inside $ {2,3,5} $ begins as follows:

 $ (1,2,3,4,5,6,8,...) $

The seventh number in this list ( $ 1 $ -indexed) is eight.

## 样例 #1

### 输入

```
3
2 3 5
7
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5
3 7 11 13 31
17
```

### 输出

```
93
```

# 题解

## 作者：Fido_Puppy (赞：14)

这道题的核心就是一个叫做 meet-in-the-middle 的算法。

meet-in-the-middle，就是中途相遇法，其实就是一种搜索的方法。

比如说对于这道题给你 16 个素数，

你可以先搜 8 个素数，把所有乘积存在一个数组 $A$ 中。

接着再搜另外 8 个素数，把所有乘积存在另一个数组 $B$ 中。

最后，再利用二分答案的思想，

将 $A$ 数组与 $B$ 数组中的统计结果结合出来得到答案。

模拟赛出题时发现了这道题，刚好是运用了二分答案的。

二分答案的思想与上半年的绍兴市复赛的 T3 很像（那次 Licykoc dalao 去了 APIO）。

meet-in-the-middle 这个算法也在以前的模拟赛中做过。

加上 CF 2400 的难度，有做我的模拟赛 T4 的风范。

搜索的部分应该不用我讲了。

主要时搜完之后的二分部分。

二分答案搜所有 $A$ 数组中的数字和 $B$ 数组中的数字的乘积中第 $k$ 小的那一个数。

先把二分的板子放在这儿：

```cpp
long long l=0,r=1e18;
while (l<r) {
	long long mid=(l+r)>>1;
	if (check(mid)>=k) r=mid; // check(mid) 表示小于等于 mid 的乘积有几个
	else l=mid+1;
}
```

接着让我们关注一下 check 函数。

我们可以用 two-pointers 的方法。

首先将 $A$ 数组，$B$ 数组排序并去重。

首先 $i$ 指针来枚举 $A$ 数组：

```cpp
for(int i=1;i<=lenA;i++)
```

里面可以再套一个指针 $j$，来枚举 $B$ 数组。

因为 $A$ 数组是从小到大排的，乘积相等（可以看作都是 $mid$），所以 $j$ 指针肯定是递减的。

可能还是不太懂，看看代码就懂了。

```cpp
inline long long check(long long mid) {
	long long ans=0; int j=lenB;
	for(int i=1;i<=lenA;i++) {
		while (j>0&&B[j]>mid/A[i]) j--; // j 表示一个数为 A[i] 时，另一个数 B[j] 最大时（满足 B[j]*A[i]<=mid）的下标
		ans+=1ll*j;
	}
	return ans; // ans 表示小于等于 mid 的乘积有几个
}
```

于是这道题就解决了。

~~其实放在 CSP-J 模拟赛中也不会被群殴。~~

## Talk is cheap, show your code!

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define REP(a,b,c) for(int a=b;a<=c;a++)
int n,a[110],k;
LL A[5000010],B[5000010];
int lenA=0,lenB=0;
inline void dfs1(int x,LL s) {
	A[++lenA]=s;
	if (x>n) return ;
	for(LL i=1;;i*=a[x]) {
		if (1e18/i<s) break;
		dfs1(x+2,s*i);
	}
}
inline void dfs2(int x,LL s) {
	B[++lenB]=s;
	if (x>n) return ;
	for(LL i=1;;i*=a[x]) {
		if (1e18/i<s) break;
		dfs2(x+2,s*i);
	}
}
inline LL check(LL mid) {
	LL ans=0; int j=lenB;
	REP(i,1,lenA) {
		while (j>0&&B[j]>mid/A[i]) j--;
		ans+=1ll*j;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; REP(i,1,n) cin>>a[i]; cin>>k;
	sort(a+1,a+n+1);
	dfs1(1,1); dfs2(2,1);
	LL l=0,r=1e18;
	sort(A+1,A+lenA+1);
	sort(B+1,B+lenB+1);
	lenA=unique(A+1,A+lenA+1)-A-1;
	lenB=unique(B+1,B+lenB+1)-B-1;
	while (l<r) {
		LL mid=(l+r)>>1;
		if (check(mid)>=k) r=mid;
		else l=mid+1;
	}
	cout<<r<<endl;
	return 0;
}
```
完结撒花! の_^

---

## 作者：eternal风度 (赞：9)

# 搜索+二分答案

同步发表于：[博客食用：CF912E Prime Gift题解(搜索+二分答案)](https://www.cnblogs.com/cjoierljl/p/9812791.html)

照例：[eternal风度的博客。。。](https://www.cnblogs.com/cjoierljl/)$\leftarrow$欢迎来踩

## 先翻译一下题意
给你$n$个质数，让你求这$n$个质数能乘起来组成的第$K$大数（$n\le 16,K$好大八大）

## 思路
### 搜索部分
看到这个数据范围，很容易想到搜索对吧

但是又不能盲目地搜索，考虑$meet-in-the-middle$

搜出前$8$个和后$8$个能拼出的所有状态

很显然随便算一下是存的下来的（不确定数组开多大就开个$vector$）

### 二分部分

我们发现还是无法很快找到第$K$大的答案对吧

这种时候就应该想到二分答案$+check$来解决，那么我们对答案二分

问题就转化成了给你一个数和两个数列，让你找出它在这两个数列中每个数列任选两个乘起来的数中排名为多少

这个就不是很难了，那两个指针扫一遍就完事了。。。

如果不知道怎么扫的话可以考虑看一看代码（~~如果你看得懂的话~~）
## Code（日常没注释）
```
#include<bits/stdc++.h>
#define il inline
#define rg register
#define ldb double
#define lst long long
#define rgt register int
#define N 20
#define pb push_back
using namespace std;
const lst Inf=1e18;
il int read()
{
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch))s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}

lst n,K;
vector<lst> v[3];
lst p[N],Sz[3];

void Dfs(int rt,int now,lst ss)
{
	if(now>n){v[rt].pb(ss),++Sz[rt];return;}
	for(lst w=1;;w*=p[now])
	{
	    Dfs(rt,now+2,ss*w);
	    if((1e18)/p[now]<w*ss)return;
	    //用除法是因为怕爆long long
	}
}

int main()
{
	n=read(),v[1].pb(0),v[2].pb(0);
	for(rgt i=1;i<=n;++i)p[i]=read();
	sort(&p[1],&p[n+1]),Dfs(1,1,1),Dfs(2,2,1);
	sort(&v[1][1],&v[1][Sz[1]+1]);
	sort(&v[2][1],&v[2][Sz[2]+1]);
	lst le=1,ri=1e18,mid,tot,Ans;K=read();
	while(le<=ri)
	{
		mid=(le+ri)>>1,tot=0;
		for(rgt i=1,j=Sz[2];i<=Sz[1]&&j>=1;++i,tot+=j)
			while(j&&mid/v[1][i]<v[2][j])--j;//用除法是因为怕爆long long
		if(tot<K)le=mid+1;
		else Ans=mid,ri=mid-1;
	}return printf("%lld\n",Ans),0;
}
```

---

## 作者：MoonCake2011 (赞：8)

与 [CF525E](https://www.luogu.com.cn/problem/CF525E) 一样，采用双向搜索。

题意看起来很复杂，其实也就那么点事。

给你 $n$ 个质数，求这 $n$ 个质数随便选几个数的积的 $k$ 大值（每个数可以选择多次）。

额，感觉有点像完全背包呢？但是值域与 $k$ 都很大，直接否定了。

照样的，搜索出前半部分与后半部分，对其答案进行合并。

合并怎么合并呢？

我们可以将前一半答案存进 $e$ 数组，后一半答案存入 $g$ 数组，并对其排序，去重。


我们尝试二分答案来找出第 $k$ 小的数。

设左端点为 $l$，右端点为 $r$，中间点为 $mid$。

我们用这个二分模板来做此题。
```cpp
while(l<=r){
	mid=l+r>>1;
	if(p(mid))
		ans=mid,l=mid+1;
	else
		r=mid-1;
}
cout<<ans;
```
于是，我们成功 AC。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[30],k;
int e[5000010],g[5000010];
int tot,cnt;
void dfs1(int x,int u){
	if(x>n){
		e[++tot]=u;
		return;
	}
	for(int i=1; ;i*=a[x]){
		if(1e18/i<u) break;
		dfs1(x+2,u*i);
	}
}
void dfs2(int x,int u){
	if(x>n){
		g[++cnt]=u;
		return;
	}
	for(int i=1; ;i*=a[x]){
		if(1e18/i<u) break;
		dfs2(x+2,u*i);
	}
}
bool check(int x){
	int ans=0;
	for(int i=1,j=cnt;i<=tot;i++){
		while(j>0 && g[j]>x/e[i]) j--;
		ans+=j;
	}
	return ans<k;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>k;
	sort(a+1,a+n+1);
	dfs1(1,1);
	dfs2(2,1);
	sort(e+1,e+tot+1);
	sort(g+1,g+cnt+1);
	tot=unique(e+1,e+tot+1)-e-1;
	cnt=unique(g+1,g+cnt+1)-g-1;
	int l=0,r=1e18,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1,ans=mid;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：憨豆Beng (赞：7)

题意  
给定一个素数集合，求第k小的数，满足这个数的所有质因子集合为给定的集合的子集。

保证答案不超过$10^{18}$

考虑二分答案。

根据折半的思想，首先我们把这个集合的数分成两组。

然后分别生成这两组质数所能表示出的正整数的集合。

然后把这个集合sort一下，我们得到了两个有序的数列。

在计算小于等于某个数$x$的符合题目条件的数的时候，我们枚举第一个集合中的数，

用双指针定位和当前枚举到的数乘积恰好小于等于$x$的位置。

然后累加。

这里有一个细节，我们要保证两个正整数的集合的大小要尽可能接近。

所以分组方式要稍微讲究一下，

我这里先对整个数列sort，再根据位置的奇偶性把整个数列分成两组。

这道题的极限数据的集合应该是前$16$小的质数……
```
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b)	for (int i(a); i <= (b); ++i)
#define dec(i, a, b)	for (int i(a); i >= (b); --i)
typedef long long LL;
const int N = 63;
int n;
int cnt;
LL a[N], c[N], k, l, r;
vector <LL> s[2];
void dfs(int i, int x, LL now){
    s[i].push_back(now);
    rep(j, x, cnt) if (1e18 / c[j] >= now) dfs(i, j, now * c[j]);
}
LL solve(LL x){
    int j = 0;
    LL ret = 0;
    dec(i, s[0].size() - 1, 0){
        while (j < s[1].size() && s[1][j] <= x / s[0][i]) ++j;
        ret += j;
    }
    return ret;
}
int main()
{
    scanf("%d", &n);
    rep(i, 1, n) scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    scanf("%lld", &k);
    cnt = 0;
    rep(i, 1, n) if (i & 1) c[++cnt] = a[i];
    dfs(0, 1, 1);
    cnt = 0;
    rep(i, 1, n) if (!(i & 1)) c[++cnt] = a[i];
    dfs(1, 1, 1);
    sort(s[0].begin(), s[0].end());
    sort(s[1].begin(), s[1].end());
    l = 1, r = 1e18;
    while (l + 1 < r){
        LL mid = (l + r) / 2;
        if (solve(mid) >= k) r = mid;
        else l = mid + 1;
    }
    if (solve(l) >= k) printf("%lld\n", l); 
    else printf("%lld\n", r);
    return 0;
}```

---

## 作者：mlvx (赞：3)

明显的折半搜索题。

记录前后两段的答案很简单：

```cpp
void dfs1(int x,int ret=1){
    b1[++c1]=ret;
    if(x>n)return;
    for(int i=1;;i*=a[x]){
        if((double)inf/i<ret)break;
        dfs1(x+2,ret*i);
    }
}void dfs2(int x,int ret=1){
    b2[++c2]=ret;
    if(x>n)return;
    for(int i=1;;i*=a[x]){
        if((double)inf/i<ret)break;
        dfs2(x+2,ret*i);
    }
}
```

注意不能直接用 $i\times ret$ 和 $10^{18}$ 比较，前者会炸 `long long`（貌似 `__int128` 也会炸），可以使用不等式的性质第二条，两边同除以 $i$，再进行比较。

---

但是如何将这两者的答案进行处理，得到最终答案呢？

首先排序并去重。

然后可以二分答案，内部再套一个双指针即可，计算出的值即为有几对乘积是大于 $mid$ 的。

```cpp
bool check(int x,int ret=1){
    for(int l=1,r=c2;l<=c1;l++){
        while(r&&(__int128)b1[l]*b2[r]>x)r--;//左移右指针
        ret+=r;//记录答案
    }return ret>k;
}
```

---

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;
int n,k,c1,c2,l,r,mid,a[20],b1[10000000],b2[10000000];
void dfs1(int x,int ret=1){
    b1[++c1]=ret;
    if(x>n)return;
    for(int i=1;;i*=a[x]){
        if((double)inf/i<ret)break;
        dfs1(x+2,ret*i);
    }
}void dfs2(int x,int ret=1){
    b2[++c2]=ret;
    if(x>n)return;
    for(int i=1;;i*=a[x]){
        if((double)inf/i<ret)break;
        dfs2(x+2,ret*i);
    }
}bool check(int x,int ret=1){
    for(int l=1,r=c2;l<=c1;l++){
        while(r&&(__int128)b1[l]*b2[r]>x)r--;
        ret+=r;
    }return ret>k;
}signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1),cin>>k,dfs1(1),dfs2(2),sort(b1+1,b1+c1+1),sort(b2+1,b2+c2+1),c1=unique(b1+1,b1+c1+1)-b1-1,c2=unique(b2+1,b2+c2+1)-b2-1;
    for(l=0,r=inf+1;l<r;mid=(l+r)>>1,check(mid)?r=mid:l=mid+1);
    return cout<<r,0;
}
```

---

## 作者：2huk (赞：2)

meet-in-the-middle。

考虑将 $n$ 个质数分成前 $\lfloor n/2\rfloor$ 个和后 $n-\lfloor n/2\rfloor$ 个。也就是说这两组的大小都 $\le 8$。分别暴力（dfs）枚举一组内的数能得到的数（即，哪些数的质因子只包括前 $\lfloor n/2\rfloor$ 个质数）。

可以发现这样得到的两个数组的大小很小。验证发现当一组是 $2,3,5,7,11,13,17,19$ 时这个数组的长度最大，为 $7039193$。当然实际上远小于这个数，但无所谓。

于是变成了，给定了两个数组 $a,b$，求 $a_i \times b_j$ 的第 $k$ 大。这是经典问题。二分答案并双指针扫描两个数组即可。

然后我为了卡一点时间把输入的数组 `random_shuffle` 了一下。

---

## 作者：紊莫 (赞：2)

前言：貌似这题的坑我全踩了，好像还发现了一点更快的方法，于是写下这篇题解。

## Part 1 思路  

注意到 $n$ 的取值很小，这启示我们可以用搜索，但是显然不能使用朴素的爆搜，哪怕给出了 $10^{18}$ 这个上限，数据规模仍是不可估量的，比较可取的做法是使用折半搜索这一搜索策略。  

坑点一：[@charleshe 在讨论区提到的](https://www.luogu.com.cn/discuss/564514)  

比如你前面八个数字是 $2,3,5,7,11,13,17,19$，而后面的数字比较大，显然前面的可能比后面多得多。这会导致合并答案的效率极低。我们希望的是两组数据能尽可能平均，容易想到一大一小错位即可。  

假设我们已经有了两组素数分别组合而成的所有可能的数字，记为 $A$ 和 $B$。  
首先要对两者排序，去重。  

然后合并的方法，~~为了慢一点~~，我们以二分查找配合双指针判定为例。  
因为 $A$ 和 $B$ 都是单调递增的，我们枚举 $A$ 的元素，此时能和其搭配的 $B$ 中的元素一定是越来越少的。  

没听懂？看代码！  

```cpp
int check(int mid){
	int rt=0,r=b.size()-1;
	F(i,0,a.size()-1){
		while(r>=0&&mid<a[i]*b[r]) r--;
		rt+=r+1;
		if(r<0) return rt;
	}
	return rt;
}
```

再次假设我们已经完成了这部分代码，但是输出的时候却发现答案错了很多。  

坑点二：爆 ``long long``。  

你会说：$10^{18}$ 怎么会爆 ``long long`` 呢？  

实际上，在利用这一上界时，一旦超过上界，几乎一定是超出 ``long long`` 范围的。  

怎么办？这一点很多人用了除法或者浮点数的方式，然而，这一做法并不是很快。我们不妨使用 ``__int128`` ，改用乘法会带来很大的优化，事实证明，这一做法可以到最优解第三名。这也是我感触较深的一点。  

至此，该题基本得到解决。  

## Part 2 代码  

我在代码里使用的是 ``vector``。这一点题解区也没有提及的，导致之前错了也没有能参考的，这篇题解勉强算是补充了。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
#define int __int128
#define F(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0)x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
const int N=100005,M=(N<<1),MX=1e18;
int n,k,p[N];
vector<int> a,b;
void dfs1(int s,int mul=1){
	b.push_back(mul);
	if(s>n) return;
	for(int i=1;;i*=p[s]){
		if(MX<mul*i) {break;}
		dfs1(s+2,mul*i);
	}
}
void dfs2(int s,int mul=1){
	a.push_back(mul);
	if(s>n) return;
	for(int i=1;;i*=p[s]){
		if(MX<mul*i) break;
		dfs2(s+2,mul*i);
	}
}
int check(int mid){
	int rt=0,r=b.size()-1;
	F(i,0,a.size()-1){
		while(r>=0&&mid<a[i]*b[r]) r--;
		rt+=r+1;
		if(r<0) return rt;
	}
	return rt;
}
signed main(){
	n=read();
	F(i,1,n) p[i]=read();
	k=read();
	dfs1(1);dfs2(2);
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	int l=0,r=MX,ans=-1;
	while (l<=r) {
		__int128 mid=(l+r)>>1;
		if (check(mid)>=k) r=mid-1,ans=mid;
		else l=mid+1;
	}
	write(ans);
    return 0;
}

```


---

## 作者：PPL_ (赞：2)

# 前言

这道题用到了新的奇技淫巧——折半搜索，所以特地写一写题解加深印象

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF912E)

[CF](http://codeforces.com/problemset/problem/912/E)

# 讲解

首先我们通过暴力打表，使用最小的但最多的质数组成$[1,10^{18}]$中的数，发现约有7e9个数，所以如果暴力枚举，一定会TLE

这个时候当然要考虑二分答案，然后问题就来到了如何check上

**折半搜索**！

具体的，我们将至多16个数分为尽量平均的两组

对于两组，我们都跑出所有的在$[1,10^{18}]$中的数

枚举第一个组中所有的数，我们就可以用二分在另一个组中求出答案，最后与外层二分的答案进行比较就行了

具体可以看看代码实现

# 代码
```cpp
//12252024832524
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 16;
const int MAXSIZ = 5000005;
int n;
int a[MAXN],b[MAXN],lena,lenb;
LL A[MAXSIZ],B[MAXSIZ],aa,bb,k;

LL Read()
{
	LL x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(LL x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(LL x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
	if(c >= 0) putchar(c);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

void dfs1(int x,int MAX,LL val)
{
    if(val != 1) A[++aa] = val;
    for(int i = x;i <= MAX;++ i)
        if(1.0 * val * a[i] <= 1e18)
            dfs1(i,MAX,val*a[i]);
}
void dfs2(int x,int MAX,LL val)
{
    if(val != 1) B[++bb] = val;
    for(int i = x;i <= MAX;++ i)
        if(1.0 * val * b[i] <= 1e18)
            dfs2(i,MAX,val*b[i]);
}
bool check(LL x)
{
    LL ret = 0;
    ret += upper_bound(A+1,A+aa+1,x) - A - 1;
    for(int i = 1;i <= aa;++ i)//内层二分统计个数
    {
        LL dz = upper_bound(B+1,B+bb+1,x/A[i]) - B - 1;
        if(!dz) break;
        ret += dz;
    }
    return ret >= k;//比较
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    n = Read();
    for(int i = 1;i <= n;++ i)//分组
        if(i & 1) a[++lena] = Read();
        else b[++lenb] = Read();
    k = Read();
    dfs1(1,lena,1); dfs2(1,lenb,1);//分组跑
    A[++aa] = 1;//注意有1，看样例解释！
    sort(A+1,A+aa+1);
    sort(B+1,B+bb+1);//二分的前提当然是要排序
    LL l = 0,r = 1e18,ans = 1e18;
    while(l <= r)//外层二分枚举答案
    {
        LL mid = (l+r) >> 1;
        if(check(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    Put(ans);
	return 0;
}

```

---

## 作者：RockyYue (赞：1)

朴素的想法是直接枚举每个质数在对应的指数，乘出所有可能的数，再排序出第 $k$ 大。

然最大时 $n=16$，这个方法的时间和空间都难以接受。$16$ 这样的大小很特别，当 $n=8$ 时是可以做的（暴力得出，前 $8$ 个质数组成的 $10^{18}$ 以内的数在 $7\times 10^6$ 的范围）。看到这样的条件不妨尝试 Meet in the middle。

首先 dfs 处理前一半质数和后一半质数可以乘出的所有数，设这两个集合分别为 $S1,S2$（因为质数所以不会乘出重复元素）。

接下来我们考虑如何合并 $S1$ 和 $S2$ 得出全局第 $k$ 大。如果直接求第 $k$ 大，这个过程中不可以忽略掉集合中任意的数，复杂度较高。这里就涉及到此题中另一个 Trick：当我们看到要求第 $k$ 大时，可以二分这个具体的值，再看比其严格小的数的个数与 $k-1$ 的大小关系。

然后问题便转化为了如何计算可以组合出的严格小于 $m$ 的数的个数，这里的组合指 $S1$ 中任一个数与 $S2$ 中任一个数相乘。那么就可以想到先将 $S2$ 升序排列，再枚举 $x\in S1$，二分得出使得 $xy<m$ 且 $y\in S2$ 的 $y$ 的个数，对于所有 $x$ 求和即可，单次 check 复杂度 $O(|S1|\log |S2|)$。

可否省去复杂度中的 $\log$？我们可以将 $S1$ 一样升序排列，那么 $y$ 的个数便随 $x$ 上升单调不升，可以动态维护最后一个 $y$ 的位置，可以把 $\log$ 均摊掉，单次复杂度 $O(\max \{|S1|,|S2|\})$。

综上，总复杂度 $O(\log T\cdot \max\{S1,S2\})$，其中 $T$ 为答案值域大小，本题中为 $10^{18}$。

我保险起见是开了 __int128 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int __int128
inline int read() {
	int f = 0, w = 1; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') w = -w, c = getchar();
	while (isdigit(c)) f = f * 10 + c - '0', c = getchar();
	return f * w;
}
inline void write(int x, char c = '\0') {
	if (x < 0) putchar('-'), x = -x;
	if (x >= 10) write(x / 10);
	putchar(x % 10 + '0');
	if (c != '\0') putchar(c);
}
const int N = 17;
int qpow(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res *= x;
		x *= x, y >>= 1;
	}
	return res;
}
int p[N];
vector<int> v1, v2;
int n, a[N];
void dfs1(int k, int prod) {
	if (k == n / 2 + 1) return void(v1.push_back(prod));
	dfs1(k + 1, prod);
	for (int i = 1; ; ++i) {
		prod *= p[k];
		if (prod > 1e18) break;
		dfs1(k + 1, prod);
	}
}
void dfs2(int k, int prod) {
	if (k == n + 1) return void(v2.push_back(prod));
	dfs2(k + 1, prod);
	for (int i = 1; ; ++i) {
		prod *= p[k];
		if (prod > 1e18) break;
		dfs2(k + 1, prod);
	}
}
int qry(int m) {	// 可以得出的<m的数的个数
	int sum = 0, i = v1.size() - 1;
	for (int x : v2) {
		if (x > m) break;
		while (i >= 0 && v1[i] * x >= m) --i;	//
		sum += i + 1;
	}
	return sum;
}
signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) p[i] = read();
	int k = read();
	if (n == 1) { write(qpow(p[1], k - 1)); return 0; }
	sort(p + 1, p + n + 1);
	dfs1(1, 1), dfs2(n / 2 + 1, 1);
	sort(v1.begin(), v1.end()), sort(v2.begin(), v2.end());
	int l = 1, r = 1e18, res = 0;	// res: 使得可以得出<res的数为k-1的最大的数 
	while (l <= r) {
		int mid = (l + r) >> 1, cnt = qry(mid);
		if (cnt < k) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	write(res, '\n');
	return 0;
}

```

---

## 作者：_shine_ (赞：1)

显然使用折半搜索。

折半搜索，与二分不同，它的原理是把整个分成两半，分开之后再进行二分答案判断（如果 $a$ 数组中有 $n$ 个数，怎把其分成两个长度为 $\frac{n}{2}$ 的数组 $b$ 和 $c$，分开进行处理再二分答案即可）。

**注意：这里必须要隔着隔着分组，而不是直接分成两半，这样效率会极低。**

#### 搜索
分开进行搜索，可以枚举出每个的次方与别的相乘，这样可以方便之后二分判断
```cpp
void dfs1(int x,int y) {
	e[++cnt1]=y;
	if(x>n){
		return ;
	}
	for(int i=1;;i*=a[x]) {
		if(y>1e18/i)break;
		dfs1(x+2,i*y);
	}
}
void dfs2(int x,int y) {
	g[++cnt2]=y;
	if(x>n){
		return ;
	}
	for(int i=1;;i*=a[x]) {
		if(y>1e18/i)break;
		dfs2(x+2,i*y);
	}
}
```
#### check 函数
如何搞定二分内的 check？

不放枚妨两个中的一个数组，并选择另一个与其配对，每次统计一下即可。
```cpp
int check(int x) {
	int num=0;
	int j=cnt2,l=cnt1;
	for(int i=1;i<=l;++i){
		while(j>0&&g[j]>x/e[i])j--;
		num+=j;
	}
//	cout<<num<<endl;
	return num;
}
```
#### 二分
是一个模板，直接贴代码。
```cpp
	int ans=0;
	int l=0,r=inf;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)>=k){
			r=mid-1,ans=mid;
		}else{
			l=mid+1;
		}
	}
```
#### 坑点
- 整个题目中的乘请全部换成除，否则 $10^{18}\times 10^{18}$ 使用 ```long long``` 会爆空间。
- 需要一个隔一个这样的分组，否则两边长度超级不相等的数组会严重影响时间。

[ac records](https://www.luogu.com.cn/record/126451278)

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
我们观察到答案不超过 $10^{18}$，所以我们可以直接用搜索去暴力。但是直接暴力会超时，这时就涉及到折半搜索了。

先将原序列分为两半，每一半分别搜索计算可能的答案，将其存入数组并去重。再观察题目要求求第 $k$ 小的正整数，满足二分的单调性，所以考虑二分。

每次二分时，用双指针在之前搜索出的两个数组中，寻找第一个数组与第二个数组的乘积比 $mid$ 大的数的个数，计算答案，与 $k$ 比较，即可求出答案。
### 代码如下：
```cpp
#include<bits/stdc++.h> 
#define ll long long
#define N 3000005
#define M 45
using namespace std;
ll n,k,a[M],b[M],s[N],cnt=0,ans=0,s1[N],cnt1=0,l=0,r=1e18;
ll MAX=1e18;
void dfs(int x,bool flag,ll sum){
	if(flag==0)s[++cnt]=sum;//暴力枚举可能的答案 
	else s1[++cnt1]=sum;
	if(x>n){
		return ;
	}
	for (ll i=1;;i*=a[x]){
		if(MAX/i<sum) break;
		dfs(x+2,flag,sum*i);
	}
}
bool check(ll mid){
	ll l=1,r=cnt1,sum=0;
	while(l<=cnt){
		while(s1[r]>mid/s[l] and r>=1) r--;//双指针 计算贡献 
		sum+=r;
		l++;
	}
	return sum>=k;
}
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	cin>>k; 
	dfs(1,0,1);
	dfs(2,1,1);
	sort(s+1,s+cnt+1);//排序+去重
	sort(s1+1,s1+cnt1+1);
	cnt=unique(s+1,s+cnt+1)-s-1; 
	cnt1=unique(s1+1,s1+cnt1+1)-s1-1; 
	while(l<r){
		ll mid=l+r>>1;
		if(check(mid)){
			r=mid;
		}
		else l=mid+1;
	}
	cout<<r;
   return 0;
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF912E)

核心思想：**折半查找**！

**先将此序列拆成两半**，分别跑出由这些质数所组成的小于 $1×10^8$ 的数。再考虑**二分答案**，每次判断小于 $mid$ 的数字个数是否小于等于 $k$ 即可。判断的时候可以先枚举前半段所得的答案，再二分找后半段答案有几个可与它拼接。

优化：若所分成的两半质数序列很不均匀，则时间复杂度就会大大增加。所以我们可以~~随机排序~~在排完序后将奇数项成一个序列，偶数项成一个序列。

---

## 作者：DDF_ (赞：0)

## 题解

这道题好像不可做，但由于它的数据范围小的可怜，那应该可以先试试打个暴力骗点分？

好的，所以打第一个暴力，对每一个素数，直接暴力枚举它的所有乘积的方案，在乘到 $1 \times 10^{18}$ 直接退出，这个暴力时间复杂度高得离谱，但能骗一点就骗一点吧。

然后我们有了：

```cpp
inline void dfs(int x,long long s) {
	if(x>n) {f[++cnt]=s;return;}
	for(long long nxt=1;;nxt*=1ll*p[x]) {
		if(s>lim/nxt) return;
		dfs(x+1,s*nxt);
	}
}
```

然后对它排序去重一下，取出 $f_{k}$ 即为答案。

然后，就这样了吗？正解在哪里呢？

这就要涉及到新算法了。

折半搜索（meet in the middle），也称双向搜索，可以直接将暴力时间复杂度的指数减半。

引入了这个算法，就可以把上文的暴力代码拆开了，通过折半搜索，可以得到拆开分别搜索的两个数组 $f1$ 和 $f2$。

接下来就要合并求答案了。

此时问题转化为，有两个排序去重好的数组 $f1$ 和 $f2$，我们要求其以乘法合并后第 $k$ 小。

这是一个二分，[P10417](https://www.luogu.com.cn/problem/P10417) 是一个很好的例子。

二分最终答案，判断函数便是求给出值在合并数组后的排名，由于两个数组都是有序的，考虑对 $f1$ 的每个元素，求 $f2$ 的最后一个下标 $x$，使其对应的元素小于等于 $\lfloor \frac{s}{f1_{i}} \rfloor$（小于等于是因为除法精度带有下取整），这个显然是可以二分的，最后将 $x$ 加起来即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int N=3e6+2;
const ll lim=1e18;
int n,p[18];
ll f1[N],f2[N];
ll cnt1,cnt2;
ll k;
inline void dfs1(int x,ll s) {
	if(x>n) {f1[++cnt1]=s;return;}
	for(ll nxt=1;;nxt*=1ll*p[x]) {
		if(s>lim/nxt) return;
		dfs1(x+2,s*nxt);
	}
}
inline void dfs2(int x,ll s) {
	if(x>n) {f2[++cnt2]=s;return;}
	for(ll nxt=1;;nxt*=1ll*p[x]) {
		if(s>lim/nxt) return;
		dfs2(x+2,s*nxt);
	}
}
inline bool check(ll s) {
	ll rnk=0,lst=cnt2,x;
	for(ll i=1;i<=cnt1;i++) {
		x=upper_bound(f2,f2+1+lst,s/f1[i])-f2-1;
		lst=x,rnk+=x;
	}
	return rnk>=k;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	scanf("%llu",&k);
	dfs1(1,1);
	dfs2(2,1);
	sort(f1+1,f1+1+cnt1),sort(f2+1,f2+1+cnt2);
	cnt1=unique(f1+1,f1+1+cnt1)-f1-1,cnt2=unique(f2+1,f2+1+cnt2)-f2-1;
	ll l=1,r=1e18;
	while(l<r) {
		ll mid=(l+r)/2ll;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%llu",l);
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：给定大小为 $n$ 的质数集合 $P$ 以及正整数 $k$，求第 $k$ 小的正整数，使得其质因数集合包含于 $P$。

范围：$n \leq 16$，$2 \leq p_i \leq 100$。保证答案不超过 $10^{18}$。

解法：

考虑折半搜索，注意到最坏情况下 $n=16$，且 $P$ 只包含前 $16$ 个质数。此时两次折半的可能答案大小都不大。然后问题转化成给定两个序列 $a,b$，求 $a_i \times b_j$ 的第 $k$ 小，二分之后双指针扫一下即可。

[Submission Link](https://codeforces.com/problemset/submission/912/256616281)。

---

## 作者：COsm0s (赞：0)

Meet in Middle。

由于最大只有 $16$ 个素数，我们可以将其分成 $8$ 个一组，将第一组所有乘积结果记录下来，记为集合 $A$。

对于第二组同样记录，记为集合 $B$。

将 $A,B$ 分别排序后，我们可以发现此时对于 $A$ 与 $B$ 的组合，具有单调性。

二分和双指针即可。

因为 $A$ 是从小到大排的，乘积相等，所以 $B$ 的 $j$ 指针肯定是递减的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 20;
int a[N], n, k;
vector<int> A, B;
void dfs1(int depth, int S) {
	A.emplace_back(S);
	if (depth > n) return ;
	for (int i = 1; ; i *= a[depth]) {
		if (1e18 / i < S) break;
		dfs1(depth + 2, S * i);
	}
}
void dfs2(int depth, int S) {
	B.emplace_back(S);
	if (depth > n) return ;
	for (int i = 1; ; i *= a[depth]) {
		if (1e18 / i < S) break;
		dfs2(depth + 2, S * i);
	}
}
bool check(int x) {
	
	int ans = 0;
	for(int i = 0, j = B.size() - 1; i < A.size(); i ++) {
		while(j >= 0 && B[j] > x / A[i]) -- j;
		ans += j + 1;
	}
	return ans < k;
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	cin >> k, sort(a + 1, a + n + 1);
	dfs1(1, 1), dfs2(2, 1);
	sort(A.begin(), A.end()), sort(B.begin(), B.end());
	A.erase(unique(A.begin(), A.end()), A.end());
	B.erase(unique(B.begin(), B.end()), B.end());
//	for(int i : A) cout << i << ' ';
//	cout << '\n';
//	for(int i : B) cout << i << ' ';
	int l = 0, r = 1e18, ans = 0;
	while(l <= r) {
		int mid = l + r >> 1;
//		cout << l << ' ' << r << '\n';
		if(check(mid)) l = mid + 1;
		else r = mid - 1, ans = mid;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：zbzbzzb (赞：0)

折半搜索即可。

找前后两端的代码还是挺简单的，注意不能用 dfs 循环中的 $sum$ 直接乘 $i$，连 `__int128` 也会炸。

难点在怎么求出答案。

用二分搜出两个存乘积的数组中的数的乘积中第 $k$ 小的那个数。

二分之前肯定要排序+去重。

然后就可以写出一个大致模板：

```
while(l<r){
		long long mid=(l+r)/2;
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}printf("%lld",r);
```

需要思考的是 check 怎么写。

我们可以用双指针，第一个指针来枚举 $a$ 数组，然后再开一个指针，然后根据乘积小于 $mid$ 的条件来搜。

可以看看代码了：

```
#include<bits/stdc++.h>
using namespace std;
long long n,k,na,nb,a[110],l,r=1e18+1,ca[10000010],cb[10000010];
void dfs(long long i,long long sum){
	ca[++na]=sum;
	if(i>n){
		return;
	}for(long long j=1;;j*=a[i]){
		if(1e18/j<sum){//不能直接乘
			break;
		}dfs(i+2,sum*j);
	}
}void dfs1(long long i,long long sum){
	cb[++nb]=sum;
	if(i>n){
		return;
	}for(long long j=1;;j*=a[i]){
		if(1e18/j<sum){
			break;
		}dfs1(i+2,sum*j);
	}
}bool check(long long x){
	long long j=nb,sum=1;
	for(int i=1;i<=na;i++){
		while(j>=1&&(__int128)ca[i]*cb[j]>x){//j肯定是递减的，因为ca是从小到大的
			j--;
		}sum+=j;
	}return sum>k;
}int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
	}scanf("%lld",&k);
	sort(a+1,a+n+1);
	dfs(1,1);
	dfs1(2,1);
	sort(ca+1,ca+na+1);
	sort(cb+1,cb+nb+1);
	na=unique(ca+1,ca+na+1)-ca-1,nb=unique(cb+1,cb+nb+1)-cb-1;
	while(l<r){
		long long mid=(l+r)/2;
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}printf("%lld",r);//输出第k小
    return 0;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路

首先我们把握到一个关键点——在一个足够大，大到无法完全处理出来的集合中寻找第 $k$ 小。

遇到这种题目，我们要思考第 $k$ 小的意义。本题中也就是有 $k-1$ 个数严格小于它，因此我们只要二分答案并计算出有多少个数小于它来判断答案是否可行。

要想 dfs 算出整个集合不可能，我们可以使用一个被称作 `Meet in the Middle` 的技巧，也称`折半搜索`。其核心在于**分别搜索前后两部分，并用一些技巧将两部分合并起来**。对于本题，我们可以把 $n$ 个素数分成两部分，每一部分分别算出只用这些质数能构成的数，这复杂度是可以接受的。

分别算出两个部分，记作 $a$ 和 $b$。假设我们现在要看有多少个数 $<x$，就是统计满足 $a_i \times b_j < x$ 的 $(i,j)$ 个数。由于所有数字都是正数，所以 $a_i$ 增大时 $b_j$ 不会变大，于是想到我们可以通过双指针来优化统计过程。

有一个优化是小质数容易产生更多的数，因此我们应让质数大小均匀分布，而不是小的全放前面，我使用排序后间隔取数实现这一点。

**注意**：判断时使用除法或 `__int128`。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long V=1e18;
int n,ed,k;
int p[20];
long long a[10000000],b[10000000];
int p1,p2;
void dfs(int now,long long tot){
	if(now>n){
		a[++p1]=tot;
		return;
	}
	if((__int128)V>=(__int128)tot*p[now]) dfs(now,tot*p[now]);
	dfs(now+2,tot);
}
void dfs2(int now,long long tot){
	if(now>n){
		b[++p2]=tot;
		return;
	}
	if((__int128)V>=(__int128)tot*p[now]) dfs2(now,tot*p[now]);
	dfs2(now+2,tot);
}
long long L,R,MID;
bool check(long long x){
	int res=0;
	for(int l=1,r=p2;l<=p1;++l){
		while(r&&(__int128)a[l]*b[r]>=x) --r;
		res+=r;
	}
	return res<k;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",p+i);
	sort(p+1,p+n+1);
	scanf("%d",&k);
	dfs(1,1);
	dfs2(2,1);
	sort(a+1,a+p1+1);
	sort(b+1,b+p2+1);
	L=1,R=1e18;
	while(L<=R){
		MID=(L+R)>>1;
		if(check(MID)) L=MID+1;
		else R=MID-1;
	}
	printf("%lld",R);
}
```

---

