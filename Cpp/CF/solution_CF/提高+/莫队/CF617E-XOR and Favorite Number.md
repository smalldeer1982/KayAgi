# XOR and Favorite Number

## 题目描述

Bob has a favorite number $ k $ and $ a_{i} $ of length $ n $ . Now he asks you to answer $ m $ queries. Each query is given by a pair $ l_{i} $ and $ r_{i} $ and asks you to count the number of pairs of integers $ i $ and $ j $ , such that $ l<=i<=j<=r $ and the xor of the numbers $ a_{i},a_{i+1},...,a_{j} $ is equal to $ k $ .

## 说明/提示

In the first sample the suitable pairs of $ i $ and $ j $ for the first query are: ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 3 $ ), ( $ 3 $ , $ 6 $ ), ( $ 5 $ , $ 6 $ ), ( $ 6 $ , $ 6 $ ). Not a single of these pairs is suitable for the second query.

In the second sample xor equals $ 1 $ for all subarrays of an odd length.

## 样例 #1

### 输入

```
6 2 3
1 2 1 1 0 3
1 6
3 5
```

### 输出

```
7
0
```

## 样例 #2

### 输入

```
5 3 1
1 1 1 1 1
1 5
2 4
1 3
```

### 输出

```
9
4
4
```

# 题解

## 作者：stoorz (赞：25)

[$\color{blue}\texttt{链接：蒟蒻的Blog}$](https://blog.csdn.net/SSL_ZYC/article/details/90311426)

好题。

如何求出任意一段的区间异或值是个问题。

如果我们要求$a_i\ xor\ a_{i+1}\ xor...xor\ a_j$，那么显然是可以表示为$(a_1\ xor\ a_2\ xor...xor\ a_{i-1})xor(a_1\ xor\ a_2\ xor...xor\ a_j)$。

所以如果用前缀异或数组的话这道题就变成了“求$[l,r]$中有多少个数对$(i,j)$满足$a_i\ cor\ a_j=k$”。

考虑用莫队离线计算。

由于$x\ xor\ y=z$的话就有$x\ xor\ z=y$，所以每次加入一个数字$x$后，和$x$异或后等于$k$的数字都可以算入答案。也就是说，我们只要知道区间内有多少个数字$x\ xor\ k$，就可以知道答案要加上几。删除时同理。

用$cnt[i]$表示数字$i$在区间内出现的次数。然后就是裸的莫队了。


```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=100010,M=1200010;
int n,m,k,l,r,T,cnt[M],a[N],pos[N];
ll ans;

struct Ask
{
	int l,r,id;
	ll ans;
}ask[N];

ll write(ll x)
{
	if (x>9) write(x/10);
	putchar(x%10+48);
} 

bool cmp1(Ask x,Ask y)  //按照块来排序
{
	if (pos[x.l]<pos[y.l]) return 1;
	if (pos[x.l]>pos[y.l]) return 0;
	return x.r<y.r;
}

bool cmp2(Ask x,Ask y)
{
	return x.id<y.id;
}

void add(int x)
{
	ans+=(ll)cnt[a[x]^k];  //加上数字a[x]^k的个数。
	cnt[a[x]]++;
}

void del(int x)
{
	cnt[a[x]]--;
	ans-=(ll)cnt[a[x]^k];
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	T=(int)sqrt(n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]^=a[i-1];
		pos[i]=(i-1)/T+1;
	} 
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].l--;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp1);
	cnt[0]=1;
	for (int i=1;i<=m;i++)
	{
		for (;l<ask[i].l;l++) del(l);
		for (;l>ask[i].l;l--) add(l-1);
		for (;r<ask[i].r;r++) add(r+1);
		for (;r>ask[i].r;r--) del(r);
		ask[i].ans=ans;  //直接记录答案
	}
	sort(ask+1,ask+1+m,cmp2);
	for (int i=1;i<=m;i++)
		write(ask[i].ans),putchar(10);
	return 0;
}
```


---

## 作者：quest_2 (赞：20)

推一手蒟蒻 [$\color{limegreen}{\texttt {博客}}$](https://www.luogu.com.cn/blog/quest233/#) ～

------------

抓住CF爆炸的间隙乘机AC的水题。（滑稽

做这道题只需要知道两个点：

 **异或前缀性** 和 **普通莫队算法** 。

 不妨分开讲。
 
 -------------------

$\large\color{salmon}{\texttt {异或前缀性：}}$

前缀和可以 $O(1)$ 求解区间和。

前缀积可以 $O(1)$ 求解区间积。

那前缀异或能否 $O(1)$ 求解区间异或呢？

答案是可以的。

$\color{violet}{\texttt {尝试证明：}}$

我们设 $num$ 为一段序列， $xornum_{\small\ l,r}$ 表示这段序列里第 $l$ 到第 $r$ 个元素异或的结果。

手模可知，异或操作满足 **结合律** 。

$$a\;\oplus\; b\;\oplus\; c=a\;\oplus\; (b\;\oplus\; c)$$

把 $xornum_{\small\ 1,l}$ 看成 $a$ ， $xornum_{\small\ l,r}$ 看成 $b$ 和 $c$ 异或的结果，那我们也就有了：

$$xornum_{\small\ 1,r}=xornum_{\small\ 1,l}\;\oplus\; xornum_{\small\ l,r}$$

我们又知道异或有以下两个性质：

$$a\;\oplus\;0=a$$

$$a\;\oplus\;a=0$$

那么我们可以经历一番移位得出：

$$xornum_{\small\ l,r}\;\oplus\; xornum_{\small\ 1,l}=xornum_{\small\ 1,r}$$

佐佑同时异或上一个 $xornum_{\small\ 1,l}$ ，再套用一个结合律得：

$$xornum_{\small\ l,r}\;\oplus\;(xornum_{\small\ 1,l}\;\oplus\;xornum_{\small\ 1,l})=xornum_{\small\ 1,r}\;\oplus\;xornum_{\small\ 1,l}$$

用上面两个性质一通转换：

$$xornum_{\small\ l,r}\;\oplus\;0=xornum_{\small\ 1,r}\;\oplus\;xornum_{\small\ 1,l}$$

$$xornum_{\small\ l,r}=xornum_{\small\ 1,r}\;\oplus\;xornum_{\small\ 1,l}$$

这样，我们就可以 **预处理** 异或前缀，来 $O(1)$ 求出区间异或的结果～

------------
$\large\color{salmon}{\texttt {普通莫队算法：}}$

定一道莫队题需要看三眼。

- 第一眼，奇怪的区间查询。

- 第二眼，可以离线。

- 第三眼，$N\sqrt{N}$ 能过。

完全符合条件，那就先把莫队的板子敲好。

（这里默认读者一定是会打莫队的QwQ。）

思维难度在 $ins/add$ 和 $del$ 两个函数上。（即 **区间扩张/收缩** 时的 **添/删元素** ）

$\color{violet}{\texttt {如何定制这两个函数？}}$

这里要查的是异或值 $=k$ 的元素对数。

两个数 $a,b$ 做异或，知道其中的一个数 $a$ ，知道异或的结果 $c$ ，则运算的另一个数也是 **确定的** ，即 $a\oplus b=c\Leftrightarrow b=a\oplus c$ 。（这也可以用于理解异或的前缀性）

我们增添一个元素 $p$ 进入区间时，它带有一个异或前缀 $xornum_{\small\ 1,p}$ ，查一下区间里 **和 $xornum_{\small\ 1,p}$ 异或结果** 为 $k$ 的异或前缀的出现次数。

也就是说，我们需要开一个  $cnt$ 数组，维护每个 **异或前缀值** 当前出现的次数。

参考之前得到的式子，可以推出和 $xornum_{\small\ 1,p}$ 异或得 $k$ 的数，即为 $xornum_{\small\ 1,p}\oplus k$ 。

那么添加一个元素 $p$ 时就应在答案上加上 $cnt[xornum_{\small\ 1,p}\oplus k]$ 。

同理，删除一个元素 $p$ 就应减去 $cnt[xornum_{\small\ 1,p}\oplus k]$ 。

$\color{violet}{\texttt {为什么能保证不重不漏？}}$

因为 $a\oplus b$ 等于 $b\oplus a$ ，可以保证区间中任取两个数，他们之间只计算了一次。

$\large\color{salmon}{\texttt {实现注意：}}$

- $cnt$ 数组的大小应为 **异或前缀的值域** 大小，而非序列中元素个数，这里应为 $2\times 10^6$ 。

- 正如我们做闭区间和时的 $sum[r]-sum[l-1]$ 一样，这里的闭区间异或也应为 $xornum[r]\oplus xornum[l-1]$ ，一种省力的方法是在输入的时候就把 **所有的 $l$ 都减去 $1$** 。

$\large\color{salmon}{\texttt {Code:}}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 7;
#define int long long
int cnt[MAX << 1], num[MAX]; //注意cnt应开2e6
int block[MAX];
int N, M, K;
int sum;
struct query
{
	int L, R;
	int id;
} q[MAX];
bool cmp(query a, query b)
{
	if (block[a.L] != block[b.L])
	{
		return a.L < b.L;
	}
	return (block[a.L] & 2 ? a.R < b.R : a.R > b.R);
}
int xornum[MAX << 1], ans[MAX << 1];
void ins(int p)
{
	sum += cnt[xornum[p] ^ K]; //查对应的异或值
	cnt[xornum[p]]++;		  ///更新出现次数
}
void del(int p) //同上
{
	cnt[xornum[p]]--;
	sum -= cnt[xornum[p] ^ K];
}
signed main()
{
	cin >> N >> M >> K;
	int lenb = sqrt(N);
	for (int i = 1; i <= N; i++)
	{
		cin >> num[i];
		block[i] = (i - 1) / lenb + 1;
		xornum[i] = xornum[i - 1] ^ num[i]; //预处理异或前缀
	}
	for (int i = 1; i <= M; i++)
	{
		cin >> q[i].L >> q[i].R;
		q[i].L--; //像做前缀和一样-1
		q[i].id = i;
	}
	sort(q + 1, q + 1 + M, cmp);
	int L = 1, R = 0;
	for (int i = 1; i <= M; i++) //普通莫队
	{
		while (q[i].L < L)
		{
			L--;
			ins(L);
		}
		while (q[i].R > R)
		{
			R++;
			ins(R);
		}
		while (q[i].L > L)
		{
			del(L);
			L++;
		}
		while (q[i].R < R)
		{
			del(R);
			R--;
		}
		ans[q[i].id] = sum;
	}
	for (int i = 1; i <= M; i++)
	{
		cout << ans[i] << endl;
	}
}
```


---

## 作者：George1123 (赞：5)


去蒟蒻改过地址的博客园看看![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)$\to$ [$\it George1123$](https://www.cnblogs.com/George1123/p/13456989.html)

---
## 题面

> [CF617E XOR and Favorite Number](https://www.luogu.com.cn/problem/CF617E)

> 给定 $n,m,k$ 和 $n$ 个数的序列 $a_i$，$m$ 次求区间 $[l,r]$ 中异或值为 $k$ 的子序列个数。

> 数据范围：$1\le n,m\le 10^5$，$0\le k,a_i\le 10^6$。

---
## 蒟蒻语

这题的莫队做法太一眼，谁都会是吧（

那么蒟蒻就来写一个过不了这题（会 MLE、TLE）但是可以在线且很有趣的做法：分块。

说不定谁去开大限制卡个离线蒟蒻解就成正解了![/qq](https://cdn.luogu.com.cn/upload/pic/62224.png)。

---
## 蒟蒻解

设 $f(l,r)$ 表示区间 $[l,r]$ 的异或值为 $k$ 的子区间数。

设 $cross(l,r)$ 表示区间左端点在 $[1,l]$ 右端点在 $[r,n]$ 的异或值为 $k$ 的区间数。

先容斥一下（$cross(l-1,r+1)$ 为了抵消掉 $f(1,n)$ 中多余的部分）：

$$ans=f(l,r)=f(1,r)+f(l,n)-f(1,n)+cross(l-1,r+1)$$

这东西前 $3$ 项可以时空 $\Theta(n)$ 求出，只是最后一项太恶心了，蒟蒻的方法是分块时空 $\Theta(n\sqrt{n})$（巨佬如果有更优做法一定要指教蒟蒻）。

设有 $b_n$ 个块，每个块为 $[l_i,r_i]$。

先预处理 $i<j:cro_{i,j}=cross(r_i,l_j)$，做法同莫队，前缀和加 unordered_map。

再记 $lc_{i,c}$ 表示 $[1,r_i]$ 中前缀和为 $c$ 的个数，$rc_{i,c}$ 表示 $[l_i,n]$ 中前缀和为 $c$ 的个数。

求 $cross(l,r)$ 时，设 $lb=\max_{i=1}^{b_n} r_i\le l$，$rb=\min_{i=1}^{b_n} l_i\ge r$。

结果就是 $cro_{lb,rb}$ 再加上

左端点在 $[r_{lb}+1,l]$ 右端点在 $[l_{rb},n]$ 的答案（用 $rc$ 数组求）

和左端点在 $[1,r_{lb}]$ 右端点在 $[r,l_{rb}-1]$ 的答案（用 $lc$ 数组求）

和左端点在 $[r_{lb}+1,l]$ 右端点在 $[r,l_{rb}-1]$ 的答案（用前缀和加 unordered_map）。

然后这题就做完了，别忘了这个做法过不了。

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5;
int n,m,k,sm[N+2];
int a[N+1]; ll la[N+2],ra[N+2];
unordered_map<int,int> cnt;

//Block
const int B=320;
int sz,b[N+1];
ll cro[B+2][B+2];
unordered_map<int,int> lc[B+2],rc[B+2];
void build(){
    sz=sqrt(n);
    for(int i=1;i<=n;i++) b[i]=(i-1)/sz+1;
    for(int i=1;i<=b[n];i++)
        for(int j=1;j<=min(sz*i,n);j++) lc[i][sm[j-1]]++;
    for(int i=1;i<=b[n];i++)
        for(int j=n;j>=sz*(i-1)+1;j--) rc[i][sm[j]]++;
    for(int i=1;i<=b[n];i++){
        for(int t=b[n];t>i;t--){
            for(int j=sz*(t-1)+1;j<=min(sz*t,n);j++)
                cro[i][t]+=lc[i][sm[j]^k];
            cro[i][t]+=cro[i][t+1];
        }
    }
}
ll cross(int l,int r){
    if(l<0||r>n) return 0;
    int lb=b[l+1]-1,rb=b[r-1]+1;
    ll res=cro[lb][rb];
    cnt.clear();
    for(int i=lb*sz+1;i<=l;i++) cnt[sm[i-1]]++;
    for(int i=r;i<=min((rb-1)*sz,n);i++) res+=cnt[sm[i]^k];
    for(int i=lb*sz+1;i<=l;i++) res+=rc[rb][sm[i-1]^k];
    for(int i=r;i<=min((rb-1)*sz,n);i++) res+=lc[lb][sm[i]^k];
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) sm[i]=sm[i-1]^a[i];
    cnt.clear(),cnt[sm[0]]++;
    for(int i=1;i<=n;i++) la[i]=la[i-1]+cnt[sm[i]^k],cnt[sm[i]]++;
    cnt.clear(),cnt[sm[n]]++;
    for(int i=n;i>=1;i--) ra[i]=ra[i+1]+cnt[sm[i-1]^k],cnt[sm[i-1]]++;
    assert(la[n]==ra[1]);
    // for(int i=1;i<=n;i++) cout<<la[i]<<' ';cout<<'\n';
    // for(int i=1;i<=n;i++) cout<<ra[i]<<' ';cout<<'\n';
    build();
    for(int i=0;i<m;i++){
        int l,r; cin>>l>>r;
        cout<<ra[l]+la[r]-la[n]+cross(l-1,r+1)<<'\n';
    }
    return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Little_Jian (赞：5)

　　把题目中给的 a 数组的前缀XOR存在 p 数组中。
　　那么 a[i] XOR a[i+1] XOR ... XOR a[j-1] XOR aj 就等于 p[i-1] XOR p[j]
　　所以题目就变成了求 l-1 到 r 中有多少对 b XOR c 等于 k 。
　　因为当求出 ans[i][j] 时就可以在 O(1) 时间内求出 ans[i-1][j] , ans[i+1][j] , ans[i][j-1] , ans[i][j+1] 。所以就可以用莫队来维护。。。。
　　ps：计数时 0 的初值要设成 1。
``` cpp
#include <bits/stdc++.h>
#define MAXN (1<<20)
#define mset(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long LL;
struct Ques{
    int l,r,no;
};
LL a[MAXN],bsize,out[MAXN],ans,cnt[MAXN],k;
Ques q[MAXN];
bool cmp(Ques a,Ques b){
    if(a.l/bsize==b.l/bsize)
        return a.r<b.r;
    return a.l<b.l;
}
void add(int w){
    ans+=cnt[a[w]^k];
    cnt[a[w]]++;
}
void del(int w){
    cnt[a[w]]--;
    ans-=cnt[a[w]^k];
}
int main(){
    int n,m;
    ios::sync_with_stdio(false);
    while(cin>>n>>m>>k){
        bsize=sqrt(n);
        mset(cnt,0);
        for(int i=1;i<=n;i++){
            cin>>a[i];
            a[i]^=a[i-1];
        }
        for(int i=1;i<=m;i++){
            cin>>q[i].l>>q[i].r;
            q[i].no=i;
        } 
        sort(q+1,q+1+m,cmp);
        int l=1,r=0;
        cnt[0]=1;
        for(int i=1;i<=m;i++){
            while(l<q[i].l){
                del(l-1);
                l++;
            }
            while(l>q[i].l){
                l--;
                add(l-1);
            }
            while(r<q[i].r){
                r++;
                add(r);
            }
            while(r>q[i].r){
                del(r);
                r--;
            }
            out[q[i].no]=ans;
        }
        for(int i=1;i<=m;i++)
            cout<<out[i]<<endl;
    }
    return 0;
}
```
日常宣传[博客](http://www.chenhowe.me/?p=169)

---

## 作者：nbnhzbw (赞：3)

**这题非常适合刚学莫队的人做**

题目中说是一段区间里的区间异或刚好为k



那么，我们考虑弄一个异或的前缀数列，并且由于异或的可逆性，就把问题转换成询问的区间里有多少对数异或为k

（注：因为a[i]=a[i-1]^a[i]，所以实际是求[l-1,r]这个区间满足的数量，所以，在读入的时候，就干脆把l减1）
   
  ** 剩下的直接莫队即可**
    
 
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define Maxn 600001
#define int long long
using namespace std;
struct node{
	int l,r,id;
}q[Maxn];
int n,m,k,a[Maxn],block,b[Maxn],l,O[Maxn<<1],ans[Maxn],num,r;//O记录每个数字出现次数
bool cmp(node A,node B){//奇偶性排序
	return b[A.l]^b[B.l]?b[A.l]<b[B.l]:b[A.l]&1?A.r<B.r:A.r>B.r;
}
main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;block=sqrt(n);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		b[i]=(i-1)/block+1;
		a[i]^=a[i-1];//前缀异或数列
	}
	for(int i=1;i<=m;++i){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;q[i].l--;
	}
	sort(q+1,q+m+1,cmp);l=1;
	for(int i=1;i<=m;++i){//莫队模板
		while(l>q[i].l) num+=O[a[--l]^k],++O[a[l]];
		while(l<q[i].l) --O[a[l]],num-=O[k^a[l++]];
		while(r<q[i].r) num+=O[a[++r]^k],++O[a[r]];
		while(r>q[i].r) --O[a[r]],num-=O[k^a[r--]];
		ans[q[i].id]=num;
	}
	for(int i=1;i<=m;++i){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：2)

莫队题，但是可以分块。

下文中假设值域为 $W=10^6$，块长为 $B$，符号 $\oplus$ 表示按位异或运算。

## 思路

首先我们要求出前缀异或数组 $s$，并且先把序列分成若干块。

然后定义两个数组：

1. $g_{i,j}$ 表示前 $i$ 个块有多少个位置 $p$ 使得 $s_p=j$。

2. $f_{i,j}$ 表示第 $i$ 个块到第 $j$ 个块之间有多少个异或值为 $k$ 的子区间。

求解 $g_{i,j}$ 很简单，可以枚举 $i$ 然后每次在 $g_{i-1,j}$ 的基础上添加。复杂度 $O\left(\dfrac{nW}{B}\right)$。

求解 $f_{i,j}$，可以枚举 $i$ 和 $j$，然后每次对于 $f_{i,j}$ 我们可以从 $f_{i,j-1}$ 转移过来，并且开一个桶 $mp$ 记录一下出现过的值的数量，每次对于 $s_p$ 的贡献就是 $mp_{s_p \oplus k}$。复杂度 $O\left(\dfrac{nB^2}{B}\right)=O(nB)$。

然后考虑每次怎么计算答案。假设一次询问 $l,r$，$l$ 所在的块右端点为 $rig_l$，$r$ 所在的块左端点为 $lef_r$。如果我们用 $(i,j)$ 表示一个满足条件的子序列 $a_i,a_{i+1},\dots,a_j$，那么答案分成三部分：

1. $i,j \in [rig_l+1,lef_r-1]$：这些直接用 $f$ 数组预处理即可。$O(1)$。

2. $i,j$ 中只有一个在 $[rig_l+1,lef_r-1]$ 中：这些可以枚举那个不在这个范围内的，算它对另一个的贡献。$O(B)$。

3. $i,j$ 都不在其中：如果都在 $rig_l$ 左边或者都在 $lef_r$ 右边，直接暴力；否则在算左边对右边的贡献时加上中间一段即可，中间一段可以用预处理好的 $g$ 数组。$O(B)$。

因此我们的时间复杂度是 $O\left(\dfrac{nW}{B}+nB+qB\right)$，空间是 $O\left(\dfrac{nW}{B}\right)$。这个时候你可以去把[异或序列](https://www.luogu.com.cn/problem/P4462)这题写了。

不过这道题显然这个复杂度时间空间都无法接受。

### 一些小优化

因此我们考虑对值域离散化。因为有用的异或值实际只有 $s_i$ 和 $s_i\oplus k$ 所以有效的 $W$ 只有 $2n=2 \times 10^5$ 个。

所以加一个离散化之后复杂度可以降到 $O\left(\dfrac{n^2}{B}+nB+qB\right)$。显然这个时候 $B=\sqrt{n}$ 最优，复杂度 $O(n\sqrt{n}+q\sqrt{n})$。

另外，记得开 `long long`。不过这个 `long long` 很难调，容易发现只有 $f$ 数组需要 `long long`，切忌直接无脑改，否则你会因为空间不够调大块长，然后你会发现调大之后直接 TLE 了。

于是你得到了一个 3.96s 极限 AC 分块代码。

## 代码

卡常内容很多，极其恶心只能说。

~~不保证每次能过，因为我这个是压着时限过的~~（

```cpp
#include <bits/stdc++.h>

// 缺省源↓

#define _cst const
#define _IfD long long
#define _siz 20
char buf[1<<_siz],buffer[1<<_siz],*p1=buf,*p2=buf,chhhhh=' ';
int op1=-1; _cst int op2=(1<<_siz)-1;
inline char gc(){return (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<_siz,stdin)),p1==p2?EOF:*p1++);}
inline void flush(){fwrite(buffer,1,op1+1,stdout),op1=-1;}
inline void pc(_cst char &x){if(op1==op2)flush();buffer[++op1]=x;}
template<typename T>void read(T &w){
	w=0;bool f=1;char ch=gc();
	for(;ch<=32;ch=gc()); if(ch=='-')f=0;
	for(;'0'<=ch && ch<='9';ch=gc()) w=(w<<1)+(w<<3)+(ch^48);
	w=f?w:-w;
}template<typename T,typename ...Arg>void read(T &w,Arg &...arg){
	read(w); read(arg...);
}template<typename T>void wrt(T x){
  	if(x<0) pc('-'),x=-x;
	if(x>9) wrt(x/10);
	pc(x%10|48);
}template<typename T>void write(T x){
	wrt(x); pc(chhhhh);
}template<typename T,typename ...Arg>void write(T x,Arg ...arg){
	write(x); write(arg...);
}inline _IfD pow_10(_IfD x){
    _IfD base=10,ans=1;
    while(x) ans*=((x&1)?base:1),base*=base,x>>=1;
    return ans;
}template<typename T>void readd(T &w){
    w=0; _IfD x=0,cnt=0; bool f=1; char ch=gc();
    for(;ch<=32;ch=gc()); if(ch=='-')f=0;
    for(;'0'<=ch && ch<='9';ch=gc()) x=(x<<1)+(x<<3)+(ch^48);
    w=(T)(f?x:-x);
    if(ch!='.') return; x=0,ch=gc();
    for(;'0'<=ch && ch<='9';ch=gc(),++cnt) x=(x<<1)+(x<<3)+(ch^48);
    T tmp=(T)(x/(T)pow_10(cnt));
    w=w+(T)(f?tmp:-tmp);
}template<typename T,typename ...Arg>void readd(T &w,Arg &...arg){
	readd(w); readd(arg...);
	readd(w); readd(arg...);
}
template<typename T>inline T qmax(_cst T &a,_cst T &b){return a>b?a:b;}
template<typename T,typename ...Arg>inline T qmax(_cst T &a,_cst T &b,_cst Arg &...arg){return qmax(a,qmax(b,arg...));}
template<typename T>inline T qmin(_cst T &a,_cst T &b){return a<b?a:b;}
template<typename T,typename ...Arg>inline T qmin(_cst T &a,_cst T &b,_cst Arg &...arg){return qmin(a,qmin(b,arg...));}
template<typename T>inline void qswap(T &a,T &b){a+=b,b=a-b,a-=b;}

// 缺省源↑

using namespace std;

const int MAXN=100005;

int n,q,k,len,tot;
int a[MAXN],s[MAXN];

int c[MAXN<<1],fk,lsh[1048580];

int bel[MAXN],g[305][MAXN<<1];
long long f[305][305],mp[MAXN<<1];

inline long long get(int L,int R,int x){
	if(L>R) return 0;
	return g[R][x]-g[L-1][x];
}

long long solve(int l,int r){
	if(bel[l]==bel[r]){
		int ans=0; vector<int> vec;
		++mp[lsh[s[l-1]]]; vec.push_back(lsh[s[l-1]]);
		for(register int i=l;i<=r;++i){
			ans+=mp[lsh[s[i]^k]],++mp[lsh[s[i]]];
			vec.push_back(lsh[s[i]]);
		}
		for(register int u:vec) mp[u]=0;
		return ans;
	}
	
	long long tmp; 
	
	long long ans=0; vector<int> vec; tmp=ans;
	++mp[lsh[s[l-1]]]; vec.push_back(lsh[s[l-1]]);
	ans+=get(bel[l]+1,bel[r]-1,lsh[s[l-1]^k]);
	for(register int i=l;i<=bel[l]*len;++i){
		ans+=mp[lsh[s[i]^k]];
		if(i!=bel[l]*len) ans+=get(bel[l]+1,bel[r]-1,lsh[s[i]^k]);
		++mp[lsh[s[i]]],vec.push_back(lsh[s[i]]);
	}
	for(register int u:vec) mp[u]=0; vec.clear();
	
	++mp[lsh[s[bel[l]*len]]],vec.push_back(lsh[s[bel[l]*len]]);
	for(register int i=(bel[r]-1)*len+1;i<=r;++i){
		ans+=mp[lsh[s[i]^k]]+get(bel[l]+1,bel[r]-1,lsh[s[i]^k]);
		++mp[lsh[s[i]]],vec.push_back(lsh[s[i]]);
	}
	
	
	for(register int u:vec) mp[u]=0; vec.clear();
	
	++mp[lsh[s[l-1]]]; vec.push_back(lsh[s[l-1]]);
	for(register int i=l;i<bel[l]*len;++i){
		++mp[lsh[s[i]]];
		vec.push_back(lsh[s[i]]);
	}
	for(register int i=(bel[r]-1)*len+1;i<=r;++i) ans+=mp[lsh[s[i]^k]];
	
	
	for(register int u:vec) mp[u]=0; vec.clear();
	
	return ans+f[bel[l]+1][bel[r]-1];
}

signed main(){
//	freopen("tst.in","r",stdin);
//	freopen("my.out","w",stdout);
	read(n,q,k);
	for(register int i=1;i<=n;++i) read(a[i]),s[i]=s[i-1]^a[i];
	
	for(register int i=1;i<=n;++i) c[++fk]=s[i],c[++fk]=s[i]^k;
	sort(c+1,c+1+fk); int M=unique(c+1,c+1+fk)-c-1;
	for(register int i=1;i<=M;++i) lsh[c[i]]=i;
	
	len=340;
	
	for(register int i=1;i<=n;++i){
		if(i%len==1) ++tot;
		bel[i]=tot;
	}
	
	g[0][0]=1;
	for(register int i=1;i<=tot;++i){
		memset(mp,0,sizeof(mp));
		for(register int j=1;j<=200000;++j) g[i][j]=g[i-1][j];
		for(register int j=(i-1)*len+1;j<=qmin(n,i*len);++j) g[i][lsh[s[j]]]++;
		mp[lsh[s[(i-1)*len]]]++;
		for(register int j=i;j<=tot;++j){
			f[i][j]=f[i][j-1];
			for(register int p=(j-1)*len+1;p<=qmin(n,j*len);p++) f[i][j]+=mp[lsh[s[p]^k]],mp[lsh[s[p]]]++;
		}
	}
	
//	cout<<f[2][2]<<'\n';
	
	memset(mp,0,sizeof(mp));
	
	int Q=0;
	while(q--){
		int l,r; read(l,r);
		wrt(solve(l,r)),pc(10);
	}
	
	return flush(),0;
}
```

---

## 作者：MILLOPE (赞：2)

## 题目
>[题目传送门](https://www.luogu.org/problemnew/show/CF617E)
>题意：给你一个大小为n的序列，然后给你一个数字k，再给出m组询问，询问给出一个区间，问这个区间里面有多少个区间的异或结果为k

## 题解
~~这是道sb题劝大家不要写~~
- 设$a[i]$为$1$~$i$区间的异或前缀和，那么区间$[L,R]$的异或和为$a[L-1] \ xor \ a[R]$（异或的自反性）
- 如果$a \ xor \ b = c$，那么$a \ xor \ c = b$
- 知道了上面那个性质之后我们发现如果我们知道$a \  xor \  k$等于哪些数，我们就可以知道$a \ xor$哪些数等于$k$
- 设$f[i]$表示数字$i$出现的次数
- 最后莫队离线维护一下即可

## code
```cpp
#include <bits/stdc++.h> 
using namespace std; 
typedef long long LL; 
const int maxm = (1 << 20); 

template <typename T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

LL n, m, k, ans; 
LL a[maxm], f[maxm], res[maxm], belong[maxm]; 
struct query { int l, r, id; } q[maxm]; 

inline bool cmp(query A, query B) {
	return belong[A.l] == belong[B.l] ? A.r < B.r : A.l < B.l; 
}

inline void add(int x) {
	ans += f[ a[x] ^ k]; 
	f[ a[x] ]++; 
}

inline void del(int x) {
	f[ a[x] ]--; 
	ans -= f[ a[x] ^ k ]; 
}

int main() {
	read(n); read(m); read(k); 
	int blo = n / sqrt(m); 
	for (int i = 1; i <= n; ++i) {
		read(a[i]); 
		a[i] ^= a[i - 1]; 
		belong[i] = (i - 1) / blo + 1; 
	}
	for (int i = 1; i <= m; ++i) {
		read(q[i].l), read(q[i].r); 
		q[i].id = i; 
	}
	sort(q + 1, q + m + 1, cmp); 
	
	f[0] = 1; 
	int l = 1, r = 0; 
	for (int i = 1; i <= m; ++i) {
		int ql = q[i].l, qr = q[i].r; 
		while (l < ql) { del(l - 1); ++l; }
		while (l > ql) { l--, add(l - 1); } 
		while (r < qr) add(++r); 
		while (r > qr) del(r--); 
		res[ q[i].id ] = ans; 
	}
	
	for (int i = 1; i <= m; ++i) 
		printf("%lld\n", res[i]); 
	return 0; 
}
```

---

## 作者：moosssi (赞：1)

这是一道莫队基础题，打好模板后主要考虑如何计算区间内有好多个子区间的异或和等于$k$

求区间$a_{i}\sim a_{j}$的异或和可以先处理出前缀和数组$sum$，那么可转化为$sum_{i-1}$^$sum_{j}$,然后用一个数组记录当前区间有多少异或和满足条件，左右指针移动时可直接修改即可（具体见代码）

注意：数组大小要开双倍以为$a$^$b$最大为$2*a$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+5;
ll ans[N],cnt[N],dt[N],a[N];
ll n,m,k,len,res,l,r;
struct nod{
	ll id,l,r;
}q[N];
bool cmp(nod x,nod y){
	int i=dt[x.l],j=dt[y.l];
	if(i!=j)return i<j;
	if(dt[x.l]%2==1)return x.r<y.r;
	return x.r>y.r;
}
void add(int x){
	res+=cnt[(x^k)];//cnt[]相当于桶标记 
	cnt[x]++;
}
void del(int x){	
	cnt[x]--;
	res-=cnt[(x^k)];
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	len=sqrt(n);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]^=a[i-1];//预处理前缀和 
		dt[i]=(i-1)/len+1;
	}
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld",&q[i].l,&q[i].r);
		q[i].l--;//因为使用前缀和，左端点要减一 
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	l=1,r=0;
	for(ll i=1;i<=m;i++){//模板 
		while(l>q[i].l)add(a[--l]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(r<q[i].r)add(a[++r]);
		ans[q[i].id]=res;//记录答案 
	}
	for(ll i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：RedreamMer (赞：1)

[$\Large\texttt{CF617E}$](https://www.luogu.com.cn/problem/CF617E)

[$\small\texttt{In my Blog}$](https://www.cnblogs.com/RedreamMer/p/13533755.html)

这道题其实和[P4462](https://www.luogu.com.cn/problem/P4462)几乎一样，但是我却多调了30min，细节很多。~~洛谷数据太水了QwQ~~

$\large\texttt{Meaning}$

给定 $n,m,k$ ，共 $m$ 个询问，每次询问一个区间，问区间内有多少个子区间的异或和等于 $k$。

$\large\texttt{Solution}$

题目中说是区间,则可以转化为前缀和的形式。

令 $S_i=a_1~\texttt{xor}~a_2~\texttt{xor}~...~\texttt{xor}~a_i$

则 $a_l~\texttt{xor}~a_{l+1}~\texttt{xor}~a_{l+2}~...~\texttt{xor}~a_r=S_r~\texttt{xor}~S_{l-1}$

然后每次询问就可转化为在 $[l-1,r]$ 之间有多少个 $S_i$ 和 $S_j$ $(i\le j)$ 使得 $S_i~\texttt{xor}~S_j=k$

发现这个可以用莫队离线下来做，因为 $S_i~\texttt{xor}~S_j=k$ 即 $S_i~\texttt{xor}~k=S_j$ ， $S_i$ **数量**改变，答案也就相应改变了。

几个要注意的地方，坑点：

1. 题目中没保证 $k$ 不为 $0$ ， 即统计贡献的时候要明确，先改贡献，还是先改个数

2. 数组的上界定为 $2e6$ 不是 $1e6$， 我也不知道为啥。

然后处理好细节后，就能过了。

$\large\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e6; //细节2
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a, b, c, s[N + 10], bel[N + 10], p[N + 10], ans, Ans[N + 10];
struct node
{
    int l, r, id;
    bool operator<(const node &t) const
    {
        return (bel[l] ^ bel[t.l]) ? bel[l] < bel[t.l] : (bel[l] & 1 ? r < t.r : r > t.r);
    }
} ask[N + 10];

inline void add(int n)
{
    ans += p[(n ^ c)]; //细节1
    p[n]++;
}

inline void del(int n)
{
    p[n]--; //细节1
    ans -= p[(n ^ c)];
}

signed main()
{
    a = read();
    b = read();
    c = read();
    int k = (int)(sqrt(a));
    for (int i = 1; i <= a; i++)
        bel[i] = (i - 1) / k + 1;
    for (int i = 1; i <= a; i++)
        s[i] = (read() ^ s[i - 1]);
    for (int i = 1; i <= b; i++)
    {
        ask[i].l = read() - 1;
        ask[i].r = read();
        ask[i].id = i;
    }
    sort(ask + 1, ask + b + 1);
    // p[0]= 1;
    int l = 1, r = 0; //其实这里左端点必须设为1，如果设为0，则要先将0这个位置计数1.
    for (int i = 1; i <= b; i++)
    {
        while (l < ask[i].l)
            del(s[l++]);
        while (l > ask[i].l)
            add(s[--l]);
        while (r < ask[i].r)
            add(s[++r]);
        while (r > ask[i].r)
            del(s[r--]);
        Ans[ask[i].id] = ans;
    }
    for (int i = 1; i <= b; i++)
        printf("%lld\n", Ans[i]);
    return 0;
}
```

---

## 作者：zrzring (赞：0)

[更好的阅读体验](http://zrzring.cn/index.php/archives/572)

同洛谷P4462 [CQOI2018]异或序列 - [题目链接](https://www.luogu.com.cn/problem/P4462)

定义异或运算的符号为$\oplus$，考虑对原序列求一个前缀异或，然后询问变成了有多少点对满足$a_x \oplus a_y = k$，其中$x\in [l - 1, r - 1], y\in [l, r]$

如果$a_x \oplus a_y = k$，那么$a_x = a_y \oplus k$，于是另外开一个数组$b$存$a_y \oplus k$的值，问题变成多次询问一段区间内有多少对$(x, y)$使得$a_x = b_y, x \leq y$

莫队即可，复杂度$O(n^{3 / 2})$

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 2e6 + 10, inf = 0x3f3f3f3f;

const long long Linf = 0x3f3f3f3f3f3f3f3f;

inline int read() {
	bool sym = 0; int res = 0; char ch = getchar();
	while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return sym ? -res : res;
}

struct QRY{int l, r, id;}qry[N];

int n, m, l[N], r[N], Q, a[N], b[N], bel[N], cnta[N], cntb[N];

long long ans[N];

void init() {
	int S = sqrt(n);
	for (int i = 1; i <= n; i += S) {
		l[++Q] = i; r[Q] = i + S - 1;
	}
	for (int i = 1; i <= Q; i++) {
		for (int j = l[i]; j <= r[i]; j++) bel[j] = i;
	}
}

bool cmp(QRY a, QRY b) {return bel[a.l] == bel[b.l] ? a.r < b.r : a.l < b.l;}

int main() {
	n = read(); m = read(); init(); int t = read();
	for (int i = 1; i <= n; i++) a[i] = read() ^ a[i - 1];
	for (int i = 1; i <= n; i++) b[i] = a[i - 1] ^ t;
	for (int i = 1; i <= m; i++) qry[i] = (QRY){read(), read(), i};
	sort(qry + 1, qry + m + 1, cmp);
	int l = 1, r = 0; long long res = 0;
	for (int i = 1; i <= m; i++) {
		while (l < qry[i].l) res -= cnta[b[l]], cnta[a[l]]--, cntb[b[l]]--, l++;
		while (l > qry[i].l) l--, cnta[a[l]]++, cntb[b[l]]++, res += cnta[b[l]];
		while (r < qry[i].r) r++, cnta[a[r]]++, cntb[b[r]]++, res += cntb[a[r]];
		while (r > qry[i].r) res -= cntb[a[r]], cnta[a[r]]--, cntb[b[r]]--, r--;
		ans[qry[i].id] = res;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：ricky0916 (赞：0)

弱化版：[P4462](https://www.luogu.com.cn/problem/P4462)

## CF617E 【XOR and Favorite Number】

题面：求区间$ [l,r] $间有多少$ x,y $满足$ a_x ⨁a_{x+1}⨁......⨁a_y=k $

首先，既然有区间就会想到处理前缀。

令$ sum[i]=a_1⨁a_2⨁......⨁a_i $

此时令

$ s(l,r)=a_l ⨁a_{l+1}⨁......⨁a_r=sum[l-1]⨁sum[r] $

接下来怎么做呢

我们可以发现，若$ s(l,r)=k $，则$ sum[r]⨁k=sum[l-1] $

所以考虑使用莫~~膜~~队，增加时统计$ sum[x]=sum[new]⨁k $的个数（$ l<=x<=r $），再将$ now $加上这个数，删除时同理

注意：$ 1. $左端点一定要$ -1 $，$ 2. $数组要开够

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100010],cnt[10000010],belong[100010],k;
struct Cmd{
    int l,r,id;
}cmd[100010];
long long L=1,R=0,now=0,ans[100010];
bool cmp(Cmd x,Cmd y){
    if(belong[x.l]!=belong[y.l]) return belong[x.l]<belong[y.l];
    return x.r<y.r;
}
void add(int p){
    now+=cnt[a[p]^k];
	cnt[a[p]]++;
}
void remove(int p){
    cnt[a[p]]--;
    now-=cnt[k^a[p]];
}
int main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        a[i]=a[i-1]^a[i];
    }
    int s=sqrt(n);
    for(int i=1;i<=n;i++) belong[i]=(i-1)/s+1;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&cmd[i].l,&cmd[i].r);
        cmd[i].id=i;
        cmd[i].l--;
    }
    sort(cmd+1,cmd+m+1,cmp);
    for(int i=1;i<=m;i++){
        while(L<cmd[i].l) remove(L++);
        while(R>cmd[i].r) remove(R--);
        while(L>cmd[i].l) add(--L);
        while(R<cmd[i].r) add(++R);
        ans[cmd[i].id]=now;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
```


---

## 作者：xixiup (赞：0)

## 思路分享

对于一个不强制在线的多个区间询问的问题，我们可以考虑莫队。

我们这时候就可以求出一个异或前缀和 $s_i=\bigoplus\limits_{j=1}^i a_j$，然后我们就可以求出对于一个区间 $\left[ L,R \right]$，对与第 $i$ 个数我们可以考虑，若 $i$ 为子区间 $\left[ l,r \right]$ 的 $r$，考虑 $i$ 能对答案作出多少贡献。

考虑若 $j\in\left[ L-1,R \right]$，若 $s_i \oplus s_j=k$，那么这个区间 $\left[ \min(i,j),\max(i,j) \right]$ 就可以对答案作出 $1$ 的贡献。

然后将式子变形得到，$i$ 对答案做出的贡献就是所有 $j \in \left[ L-1,R\right]$ 且 $s_i \oplus k = s_j$ 的 $j$ 的个数。

然后我们就可以使用莫队维护这个东西了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100100,maxk=2001000;
int n,m,k,S,a[maxn],s[maxn],cnt[maxk];
long long sum,ans[maxn];
struct node{
	int l,r,num;
	bool operator <(node u){
		return l/S==u.l/S?r<u.r:l<u.l;
	}
}qu[maxn];
void add(int x){//增加
	sum+=cnt[k^s[x]];
	cnt[s[x]]++;
}
void del(int x){//减少
	cnt[s[x]]--;
	sum-=cnt[k^s[x]];
}
int main(){
	cin>>n>>m>>k;
	S=sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		s[i]=s[i-1]^a[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&qu[i].l,&qu[i].r);
		qu[i].l--;
		qu[i].num=i;
	}
	sort(qu+1,qu+1+m);//询问排序
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		int tl=qu[i].l,tr=qu[i].r;
		while(l<tl){//莫队基本操作
			del(l);
			l++;
		}
		while(l>tl){
			l--;
			add(l);
		}
		while(r>tr){
			del(r);
			r--;
		}
		while(r<tr){
			r++;
			add(r);
		}
		ans[qu[i].num]=sum;
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}


```


---

## 作者：年华天地 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P4462)

首先，做这道题必须要对异或有所了解,如果a$\bigotimes$b=c,那么c$\bigotimes$b=a,其次，异或也满足前缀和，具体证明就是把异或的运算法则代入算就好了（相同为0，不同为1）。

当我们了解异或的运算法则后这道题就变得好做了，因为我们是求有多少个子区间的异或值为k，所以我们可以在进行摩队的时候吧所有子区间的值用一个桶存起来，每次新便利到一个值，就看k$\bigotimes$这个值为多少，在去桶里求这个值有多少个，贡献给答案就好了。

具体细节看代码吧（注意区间左端点要-1）

```
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=3e6+100;
ll n,m,k,pos,tong[maxn],block[maxn];
ll a[maxn],l,r,sum,ans[maxn];
struct node{
	 ll l,r,id;
}s[maxn];
ll read()
{
	ll x=0,f=1;
	char c;
	c=getchar();
	while (c<'0'||c>'9')
	{
		if (c=='-')f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
bool cmp(node a,node b)
{
	if (block[a.l]!=block[b.l])return a.l<b.l;
	return a.r<b.r;
}
int main()
{
	n=read();
	m=read();
	k=read();
	pos=(int)sqrt(n);
	pos=pos>1?pos:1;
	for (int i=1;i<=n;i++)block[i]=(i-1)/pos+1;
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		a[i]^=a[i-1];
	}
	for (int i=1;i<=m;i++)
	{
		s[i].l=read();
		s[i].l--;
		s[i].r=read();
		s[i].id=i;
	}
	sort(s+1,s+m+1,cmp);
	l=1;
	for (int i=1;i<=m;i++)
	{
		while (l<s[i].l)
		{
			tong[a[l]]--;
			sum-=tong[k^a[l]];
			l++;
		}
		while (l>s[i].l)
		{
			l--;
			sum+=tong[k^a[l]];
			tong[a[l]]++;
		}
		while (r<s[i].r)
		{
			r++;
			sum+=tong[k^a[r]];
			tong[a[r]]++;
		}
		while (r>s[i].r)
		{
			tong[a[r]]--;
			sum-=tong[k^a[r]];	
			r--;
		}
		ans[s[i].id]=sum;
	}
	for (int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：Azazеl (赞：0)

$\ \ \ \ $ 先做了 [P4462 [CQOI2018]异或序列](https://www.luogu.com.cn/problem/P4462)再做的这道题，没想到还被卡了两次。~~（由此可见CQOI数据多水）~~  

---

#### 题意  

>$\ \ \ \ $ 给出一个数列以及 $k$ ，每次询问区间 $[l,r]$ 内有多少个子区间的异或和为 $k$.  

---

#### 题解  

$~~~~$ 看到想到单纯询问，直接上莫队。  

$~~~~$ 异或有一个简单的性质,若：$a\ \operatorname{xor} b=c$ ，则 $a=c\ \operatorname{xor} b$ 。直接讨论各位上 $4$ 种情况可以证明。  

$~~~~$ 则记 $d_i$ 表示 $[1,i]$ 的异或前缀和， $[l,r]$ 的异或和可以表示为 $d_r \operatorname{xor} d_{l-1}$ ，题目就转化为：对于每个询问 $[l-1,r]$ ，有多少区间内的数对 $<i,j>$ 满足 $d_j \operatorname{xor} d_i=k$ 。这个时候直接用莫队维护，开个桶记录数字出现情况即可。注意加减时更新桶和答案的先后顺序，有可能 $k=0$ 且 $a_i=0$ 可以hack掉 。  

$~~~~$ 需要注意的是：  

$~~~~$ 1.不开 `long long` 见祖宗。  

$~~~~$ 2.由于 $a \operatorname{xor} b \leq a+b$ ，因此桶要开 $2$ 倍大小。  

---

#### 代码

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll n,m,k;
ll tmp,bs,cnt[2000005],pos[1000005],q[1000005],arr[1000005],sum[2000005];
struct node{
	ll l,r,id;
}ask[1000005];
inline bool cmp(node x,node y)
{
	if(pos[x.l]^pos[y.l]) return x.l<y.l;
	else
	{
		if(pos[x.l]&1) return x.r<y.r;
		else return x.r>y.r;
	}
}
void del(ll x)
{
	cnt[sum[x]]--;
	tmp-=cnt[k^sum[x]];
}
void add(ll x)
{
	tmp+=cnt[k^sum[x]];
	cnt[sum[x]]++;
}
int main() {
	scanf("%lld %lld %lld",&n,&m,&k);
	bs=n/sqrt(m*2/3);
	if(bs<=10) bs=sqrt(n);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&arr[i]);
		sum[i]=sum[i-1]^arr[i];
		pos[i]=(i-1)/bs+1;
	}
	for(ll i=1;i<=m;i++)
	{
		scanf("%lld %lld",&ask[i].l,&ask[i].r);
		ask[i].l--;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp);
	ll l=1,r=0;
	for(ll i=1;i<=m;i++)
	{
		ll ql=ask[i].l,qr=ask[i].r;
		while(l<ql) del(l++);
		while(l>ql) add(--l);
		while(r<qr) add(++r);
		while(r>qr) del(r--);
		q[ask[i].id]=tmp;
	}
	for(ll i=1;i<=m;i++) printf("%lld\n",q[i]);
	return 0;
}
```



---

## 作者：GoPoux4 (赞：0)

~~双倍经验~~ [P4462 [CQOI2018]异或序列](https://www.luogu.com.cn/problem/P4462)

但是那道题数据太水，放过了很多错误的方法，所以这道题应该算是加强版？

---

### 题解

将原数列做个异或前缀和，则这道题变为了：

求区间 $[l-1,r]$ 内，满足 $sum_i \oplus sum_j =k$ 的点对 $(i,j)(l-1\leq i< j \leq r)$ 的个数。

将上面的式子变一下形： $sum_i=k \oplus sum_j$ 。

用一个数组记录区间内每个值出现的次数，用莫队离线即可。

---

### 注意

由于做了前缀和，所以点对 $(i,j)$ 必须满足 $i<j$ 。

那么插入一个数 $i$ 时要先 `Ans+=cnt[k^i]`，再 `++cnt[i]`；同理，删除一个数时先 `--cnt[i]`，再 `Ans-=cnt[k^i]`。

---

Code：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define maxn 100005
#define BN 400
using namespace std;
typedef long long lxl;

inline lxl read()
{
	lxl x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}

int n,m,k,sum[maxn];
lxl cnt[1<<20],Ans,ans[maxn];

inline int pos(int x) {return (x-1)/BN+1;}

struct ques
{
	int l,r,id;
	bool operator <(const ques &x)const
	{
		if(pos(l)!=pos(x.l)) return pos(l)<pos(x.l);
		return r>x.r;
	}
}querys[maxn];

inline void Add(int i)
{
	Ans+=cnt[k^i];
	++cnt[i];
}

inline void Del(int i)
{
	--cnt[i];
	Ans-=cnt[k^i];
}

int main()
{
	//freopen("P4462.in","r",stdin);
	n=read()+1,m=read(),k=read();
	for(int i=2;i<=n;++i)
		sum[i]=sum[i-1]^read();
	for(int i=1;i<=m;++i)
		querys[i].l=read(),querys[i].r=read()+1,querys[i].id=i;
	sort(querys+1,querys+m+1);
	for(int i=1,l=1,r=0;i<=m;++i)
	{
		ques &q=querys[i];
		while(l<q.l) Del(sum[l++]);
		while(l>q.l) Add(sum[--l]);
		while(r<q.r)
			Add(sum[++r]);
		while(r>q.r) Del(sum[r--]);
		ans[q.id]=Ans;
	}
	for(int i=1;i<=m;++i)
		printf("%lld\n",ans[i]);
	return 0;
}

```


---

## 作者：VTloBong (赞：0)

# 前置算法
[莫队算法](https://www.luogu.com.cn/problem/P1494)
# 思路
异或运算有一个很好的性质，那就是异或运算的逆运算为他自己，所以可以维护一个前缀异或序列，表示 1 到 i 的异或和，问题就变成了：区间$[l-1,r]$中，有多少对数异或为k。   
再将问题转化一下,  
若 $a_i\operatorname{xor}a_j=k$,则$a_i\operatorname{xor}k=a_j$,于是问题就变成了：记 $cnt_i$ 为区间$[l-1,r]$中数字 i 出现次数（即$cnt_i=\Sigma^r_{j=l-1}[a_j=i]$），求 $\Sigma^r_{j=l-1}cnt_{a_i\operatorname{xor}k}$ 。     
开个数组记录 $cnt_i$ ,用莫队算法处理询问即可。
# 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long//十年OI一场空，不开long long见祖宗
const int maxn=1000005;
struct query{
	int l,r,id;
}q[maxn];
int a[maxn],cnt[maxn<<1],ans,ls=1,rs,size,f[maxn],n,m,x;
bool cmp(query x,query y){
    return (x.l-1)/size==(y.l-1)/size?(((x.l-1)/size)&1?x.r<y.r:x.r>y.r ):(x.l-1)/size<(y.l-1)/size; 
}
inline void add(int k){
	ans+=cnt[a[k]^x],cnt[a[k]]++;//注意顺序
}
inline void del(int k){
	cnt[a[k]]--,ans-=cnt[a[k]^x];//注意顺序
}
main(){
	scanf("%lld%lld%lld",&n,&m,&x);
	for(register int i=1;i<=n;++i)scanf("%lld",a+i),a[i]^=a[i-1];
	for(size=1;size*size<n;size++);
	for(register int i=1;i<=m;++i)
		q[i].id=i,scanf("%lld%lld",&q[i].l,&q[i].r),q[i].l--;
	sort(q+1,q+m+1,cmp);
	for(register int i=1;i<=m;++i){
		int nl=q[i].l ,nr=q[i].r ;
		while(rs<nr)rs++,add(rs);
		while(ls>nl)ls--,add(ls);
		while(ls<nl)ls++,del(ls-1);
		while(rs>nr)rs--,del(rs+1);
		f[q[i].id]=ans;
	}for(register int i=1;i<=m;++i)printf("%lld\n",f[i]);
	return 0;
}



---

