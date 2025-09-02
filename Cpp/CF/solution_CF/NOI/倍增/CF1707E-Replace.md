# Replace

## 题目描述

给定一个长为 $n$ 的序列 $a_1,\ldots,a_n$，其中对于任意的 $i$ 满足 $1 \leq a_i \leq n$。

定义一个二元组函数如下：
$$f((l,r))=(\min\{a_l,\ldots,a_r\},\max\{a_l,\ldots,a_r\})(l \leq r)$$

你需要回答 $q$ 次询问，每次给定 $(l_i,r_i)$，问其最少经过多少次 $f$ 的调用（即 $(l,r) \rightarrow f((l,r))$）使得 $(l_i,r_i)$ 变成 $(1,n)$，若无解请输出 `-1`。

## 样例 #1

### 输入

```
5 6
2 5 4 1 3
4 4
1 5
1 4
3 5
4 5
2 3```

### 输出

```
-1
0
1
2
3
4```

## 样例 #2

### 输入

```
6 3
2 3 4 6 1 2
5 6
2 5
2 3```

### 输出

```
5
1
3```

## 样例 #3

### 输入

```
5 3
3 2 2 4 1
2 5
1 3
1 5```

### 输出

```
-1
-1
0```

# 题解

## 作者：feecle6418 (赞：26)

注意到 $f(l,r)=\cup_{i=l}^{r-1} f(i,i+1)$。

这个观察本身就很有启发意义，因为相当于告诉我们对于这种看上去没啥性质的函数应该观察其结构，找到一些结构上的性质，使得我们能用某种结构去维护它。

考虑把上面的结论推广，我们断言 $f^k(l,r)=\cup_{i=l}^{r-1} f^k(i,i+1)$。

证明：

- 先证明引理：若 $[l,r],[L,R]$ 有交，则 $f(l,r),f(L,R)$ 有交（这显然）。进一步有 $f^k(l,r),f^k(L,R)$ 有交。
- 接着证明若 $[l,r],[L,R]$ 有交，则 $f(l,r)\cup f(L,R)=f(\min(l,L),\max(r,R))$，这也是显然的。因此证毕。

有了上面的结论后，问题变得很简单：倍增预处理 $f^{2^k}(i,i+1)$（每次倍增都需要 rmq），查询时也倍增即可。复杂度 $O(n\log^2 n+q\log n)$（当然可以优化到 $O(n\log n+q\log n)$）。


---

## 作者：Kubic (赞：17)

一道智慧的题，想了 1h 没有思路后突然就会了。

首先这类题一个很自然的思路就是预处理倍增数组。但是这题状态数量为 $O(n^2)$，不容易直接计算。

然后我就花了 1h 尝试各种奇怪数据结构，最终也没有什么结果。

此时我突然发现了关键结论：设 $f^k([l,r])$ 为 $[l,r]$ 操作 $k$ 次后的结果。如果 $[l_1,r_1]\cup[l_2,r_2]=[l,r],[l_1,r_1]\cap[l_2,r_2]\ne\varnothing$，那么 $f^k([l,r])=f^k([l_1,r_1])\cup f^k([l_2,r_2])$。

证明很简单，采用归纳法，相当于需要证明：如果 $[l_1,r_1]\cup[l_2,r_2]=[l,r],[l_1,r_1]\cap[l_2,r_2]\ne\varnothing$ 那么 $f([l_1,r_1])\cup f([l_2,r_2])=f([l,r]),f([l_1,r_1])\cap f([l_2,r_2])\ne\varnothing$。根据两个区间相交能得到它们的值域相交，因此这个结论显然成立。

然后就非常简单了，我们相当于设定若干关键区间，使得每一个区间都能被较少的相交的关键区间的并表示出来。ST 表，分治，线段树都可以胜任。

最后只需要在上面的数据结构外面套上一层倍增，即计算 $z_{i,j}$ 表示从数据结构中的第 $j$ 个关键区间开始操作 $2^i$ 步会到达的区间。询问时只需要倍增，并在数据结构上进行区间询问，即可。

如果用 ST 表或者分治，那么时间复杂度 $O(n\log^2n+q\log n)$，空间复杂度 $O(n\log^2 n)$。

如果用线段树，那么时间复杂度 $O((n+q)\log^2 n)$，空间复杂度 $O(n\log n)$。

当然如果要卡空间，也可以把询问离线下来，能砍掉空间里的一个 $\log$。不过这题完全没有必要，直接写就可以过了。

回顾整道题，其实做法非常简洁，没有任何复杂的地方，代码也很好写。但是似乎真的不太容易想得到啊（

参考代码（ST 表，在线）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define clz __builtin_clz
int n,m,a[N],zL[18][18][N],zR[18][18][N];
int qryL(int x,int l,int r)
{
	int t=31-clz(r-l+1);
	return min(zL[x][t][l],zL[x][t][r-(1<<t)+1]);
}
int qryR(int x,int l,int r)
{
	int t=31-clz(r-l+1);
	return max(zR[x][t][l],zR[x][t][r-(1<<t)+1]);
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),zL[0][0][i]=zR[0][0][i]=x;
	for(int i=1;i<=17;++i) for(int j=1;j+(1<<i)-1<=n;++j)
	{
		zL[0][i][j]=min(zL[0][i-1][j],zL[0][i-1][j+(1<<i-1)]);
		zR[0][i][j]=max(zR[0][i-1][j],zR[0][i-1][j+(1<<i-1)]);
	}
	for(int i=1;i<=17;++i) for(int j=0;j<=17;++j)
		for(int k=1;k+(1<<j)-1<=n;++k)
		{
			zL[i][j][k]=qryL(i-1,zL[i-1][j][k],zR[i-1][j][k]);
			zR[i][j][k]=qryR(i-1,zL[i-1][j][k],zR[i-1][j][k]);
		}
	for(int i=1,l,r,l1,r1,res;i<=m;++i)
	{
		scanf("%d %d",&l,&r);res=1;
		if(l==1 && r==n) {printf("0\n");continue;}
		for(int j=17;j>=0;--j)
		{
			l1=qryL(j,l,r);r1=qryR(j,l,r);
			if(l1>1 || r1<n) l=l1,r=r1,res+=1<<j;
		}l1=qryL(0,l,r);r1=qryR(0,l,r);
		if(l1>1 || r1<n) res=-1;printf("%d\n",res);
	}return 0;
}
```

---

## 作者：qinyubo (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF1707E)



题意描述：给定长度为 $n$ 的序列 $a$（$1\le a_i\le n$）。

定义 $\min(S)=\min\limits_{i\in S}a_i$。

定义 $\max(S)=\max\limits_{i\in S}a_i$。

定义 $[l,r]=\{x\in\mathbb{N}|l\le x\le r\}$。

定义

$f^0([l,r])=[l,r]$

$f^1([l,r])=[\min([l,r]),\max([l,r])]$

$f^k([l,r])=f^1(f^{k-1}([l,r]))\ \ \ \ (k>1)$

$q$ 次询问，每次给出 $l,r$，求最小的 $k$ 使得 $f^k([l,r])=[1,n]$。若无解，请输出 $-1$。

神仙思维题。考察的算法不难，但考的是灵活应用 ~~（和极强的找性质能力~~。



首先，静态区间求最值，$\text{ST}$ 表即可解决。

然后，如果你像 $\text{Alice}$ 和 $\text{Bob}$ 一样聪明，你就可以看出如果两个区间 $[l_1,r_1]\cap[l_2,r_2]\neq\varnothing$，那么 $f([l_1,r_1])\cap f([l_2,r_2])\neq\varnothing$，且 $f([l_1,r_1])\cup f([l_2,r_2])=f([l_1,r_1]\cup[l_2,r_2])$。

证明如下：

如果两个区间 $[l_1,r_1]\cap[l_2,r_2]\neq\varnothing$，

那么 $\max([l_1,r_1])\ge\max([l_1,r_1]\cap[l_2,r_2])\ge\min([l_1,r_1]\cap[l_2,r_2])\ge\min([l_2,r_2])$

$\max([l_2,r_2])\ge\max([l_2,r_2]\cap[l_1,r_1])\ge\min([l_2,r_2]\cap[l_1,r_1])\ge\min([l_1,r_1])$

即 $f([l_1,r_1])\cap f([l_2,r_2])\neq\varnothing$。

而

$\max([l_1,r_1]\cup[l_2,r_2])=\max(\max([l_1,r_1]),\max([l_2,r_2]))$

$\min([l_1,r_1]\cup[l_2,r_2])=\min(\min([l_1,r_1]),\min([l_2,r_2]))$

即 $f([l_1,r_1])\cup f([l_2,r_2])=f([l_1,r_1]\cup[l_2,r_2])$。

所以如果 $[l_1,r_1]\cap[l_2,r_2]\neq\varnothing$，那么 $f^k([l_1,r_1])\cap f^k([l_2,r_2])\neq\varnothing$，且 $f^k([l_1,r_1])\cup f^k([l_2,r_2])=f^k([l_1,r_1]\cup[l_2,r_2])$。

发现它像区间最值一样可以合并。于是设 $g_{i,j,k}$ 为 $f^{2^j}([i,i+2^k-1])$，然后可以倍增转移。时间 $O(n\log^2n)$。

还有最后一件事，答案的上界是 $2n$，如果拓展了超过 $2n$ 次就无解。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace QYB {
    int n, q, a[100005], log2[100005], minn[18][100005], maxn[18][100005];
    pair<int, int> g[18][18][100005];
    pair<int, int> extend(pair<int, int> s, int k) {
        // 利用 g 数组将 s 拓展 2 ^ k 次
        int l = s.first, r = s.second, t = log2[r - l + 1];
        pair<int, int> s1 = g[k][t][l], s2 = g[k][t][r - (1 << t) + 1];
        return make_pair(min(s1.first, s2.first), max(s1.second, s2.second));
    } int main() {
        scanf("%d%d", &n, &q); log2[0] = -1;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i); log2[i] = log2[i / 2] + 1;
            minn[0][i] = maxn[0][i] = a[i];
        } for (int i = 1; i <= 17; i++) {
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                maxn[i][j] = max(maxn[i - 1][j], maxn[i - 1][j + (1 << i - 1)]);
                minn[i][j] = min(minn[i - 1][j], minn[i - 1][j + (1 << i - 1)]);
            }
        } for (int i = 1; i <= 17; i++) {
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                g[0][i][j] = make_pair(minn[i][j], maxn[i][j]);
            }
        } for (int i = 1; i <= 17; i++) {
            for (int j = 1; j <= 17; j++) {
                for (int k = 1; k + (1 << j) - 1 <= n; k++) {
                    // 由于这个时候 g[i - 1][][] 已经计算完毕了，所以这时调用 extend 是可以的
                    g[i][j][k] = extend(extend(make_pair(k, k + (1 << j) - 1), i - 1), i - 1);
                }
            }
        } while (q--) {
            int l, r, ans = 0; scanf("%d%d", &l, &r);
            if (l == 1 && r == n) { printf("0\n"); continue; }
            // 特判一手，因为下面至少会拓展 1 次
            for (int i = 17; i >= 0; i--) {
                auto tmp = extend(make_pair(l, r), i);
                if (tmp != make_pair(1, n)) {
                    ans |= 1 << i; l = tmp.first; r = tmp.second;
                }
            } if (ans == (1 << 18) - 1) printf("-1\n");
            else printf("%d\n", ans + 1);
        } return 0;
    }
} int main() {
    return QYB::main();
}
```

---

## 作者：liyixin0514 (赞：3)

# [Replace](https://www.luogu.com.cn/problem/CF1707E)

## 题意

给你一个长度为 $n$ 的序列 $A$，有 $q$ 次询问，每次询问对于一个区间 $[l,r]$ 需要操作多少次才能变成区间 $[1,n]$，无解输出 $-1$。其中一次操作指原区间变成 $[l'=\min_{i=l}^r\{a_i\},r'=\max_{i=l}^r\{a_i\}]$。

## solution

看了[feecle大佬的题解](https://www.luogu.com.cn/article/w843rqy5)后对其中的结论有也许是另一种理解方式。

首先题目的操作与取 $\min,\max$ 有关，因此通过丰富的经验和敏锐的观察力~~显然我没有~~可以发现：

$$f(l,r)=\cup_{i=l}^{r-1} f(i,i+1)$$

证明（或者应该叫理解方式）：对于每个 $i$，设 $a_x=\min(a_i,a_{i+1}),a_y=\max(a_i,a_{i+1})$，$f(i,i+1)$ 对应区间 $[a_x,a_y]$，其中相邻的 $i$ 对应区间至少有一个端点重合。因此所有的 $f(i,i+1)$ 并成连续的一段区间，其中最左的一个端点和最右的一个端点就是 $f(l,r)$ 的两端。可见等式是成立的。

蒟蒻的我不能直接观察出推论，但是也许可以这么想：我们考虑对所有 $f(i,i+1)$ 再进行一次操作，看看会发生什么。$f(i,i+1)$ 是若干段首尾相接的区间。每个区间会变成区间最小值和最大值为端点的新区间。由于区间是首尾相接的，因此新区间要么首尾相接要么相交得更多，而所有新区间的最左端点和最右端点一定等于所有区间的最小值和最大值，因此对这些 $f(i,i+1)$ 再进行一次操作，得到的区间 $=f^2(l,r)$。

以此类推，可以得到 $f^k(l,r)=\cup_{i=l}^{r-1} f^k(i,i+1)$。

所以我们不需要求所有的 $f(l,r)$，只需要求所有的 $f^k(i,i+1)$。然后是 RMQ 问题求区间最小值和最大值，ST 表即可。

因为 $f(1,n)=[1,n]$，所以显然操作 $k$ 次能否得到区间 $[1,n]$ 的 $k$ 满足单调性，$k$ 越大越容易得到指定区间。

因此考虑倍增。先求所有 $f^{2^0}(i,i+1)$，然后求所有 $f^{2^1}(i,i+1)$，以此类推，每一层都要做一次 RMQ。时间和空间都是 $O(n \log^2 n)$。

对每个询问，倍增，每次计算 RMQ 判断是否可以得到区间 $[1,n]$ 即可。时间复杂度 $O(q \log n)$。

总时间复杂度是 $O(n \log^2 n+q \log n)$。

据说猫树可以单 $\log$？感觉不会啊，会的大佬欢迎分享。

## code

如果你对 ST 表比较熟练，代码不算难写。

```cpp
#include<bits/stdc++.h>
// #define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
constexpr int N=1e5+7;
#define isdigit(x) (x>='0'&&x<='9')
template <typename T>
void read(T &x) {
	x=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) ;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}
template <typename T>
void write(T x,char ch) {
	static int st[20];
	int top=0;
	do {
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top) putchar(st[--top]+'0');
	putchar(ch);
}
int n,q;
int a[N];
int l,r;
typedef pair<int,int> pii;
#define fi first
#define se second
pii st[50][25][N];
pii cal(pii a,pii b) { return {min(a.fi,b.fi),max(a.se,b.se)}; }
pii _cal(int p,pii x) {
	if(x.fi==x.se) return x;
	int lg=__lg(x.se-x.fi);
	return cal(st[p][lg][x.fi],st[p][lg][x.se-(1<<lg)]);
}
#define mp make_pair
int main() {
	read(n),read(q);
	rep(i,1,n) read(a[i]);
	rep(i,1,n-1) st[0][0][i]={min(a[i],a[i+1]),max(a[i],a[i+1])};
	int lg=__lg(n);
	rep(k,1,lg) for(int i=1;i+(1<<k)-1<=n-1;i++) st[0][k][i]=cal(st[0][k-1][i],st[0][k-1][i+(1<<(k-1))]);
	rep(p,1,lg<<1) {
		rep(i,1,n-1) st[p][0][i]=_cal(p-1,st[p-1][0][i]);
		rep(k,1,lg) for(int i=1;i+(1<<k)-1<=n-1;i++) st[p][k][i]=cal(st[p][k-1][i],st[p][k-1][i+(1<<(k-1))]);
	}
	rep(i,1,q) {
		read(l),read(r);
		if(l==1&&r==n) {
			puts("0");
			continue;
		}
		if(l==r) {
			puts("-1");
			continue;
		}
		pii y={l,r};
		int cnt=0;
		per(p,lg<<1,0) {
			pii x=_cal(p,y);
			if(x!=mp(1,n)) y=x,cnt+=(1<<p);
		}
		if(y!=mp(1,n)) y=_cal(0,y),cnt++;
		if(y==mp(1,n)) write(cnt,'\n');
		else puts("-1");
	}
}
```

---

## 作者：Rainbow_qwq (赞：3)

[link](https://www.luogu.com.cn/problem/CF1707E)

首先区间最多跳 不同区间个数 次，不然就是跳不到，这是显然的。

考虑倍增跳这个区间，这样最多跳 log 次。但每层如果要存储 $n^2$ 个区间的答案肯定不行。

这个跳区间信息很能合并的样子，于是考虑拿 ST 表拼接区间的那种方式来搞。

因为跳的方式是 $[l,r]\to [\min_{i\in[L,R]}a_i,\max_{i\in[L,R]}a_i]$，于是如果两个区间有交的话就可以信息合并。（指如果区间 $A,B$ 有交则 $f(A\bigcup B)=f(A)\bigcup f(B)$，于是可以合并。）

可以考虑改一改 ST 表，制作出 $[1,2],[2,3]..$ 的区间，并且不断倍增求出 $[x,x+2^k]$ 的区间信息，方式是 $[x,x+2^{k-1}]\bigcup\ [x+2^{k-1},x+2^k] = [x,x+2^k]$，这样每次合并都是值域有交的，就是正确的。

$f(t,k,x)$ 表示跳 $2^t$ 步，$[x,x+2^k]$ 跳到哪里，根据上面的做法都推出来就可以了。

这样空间复杂度有 $4 n\log^2 n$ 个 int，但这题开了 1G 空间，应该卡的过（

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for( int i=(a);i<=(b);++i)
#define Rep(i,a,b) for( int i=(a);i>=(b);--i)
//#define int long long
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	if(f)x=-x;return x;
}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 100005
#define inf 0x3f3f3f3f
#define ll long long

int n,m,a[maxn];

struct node{
	int l,r;
	node(int L=0,int R=0){l=L,r=R;}
	node operator +(node b){return node(min(l,b.l),max(r,b.r));}
	bool ok(){return l==1&&r==n;}
};
node f[35][17][maxn];
int lg[maxn];
node ask(int k,int l,int r){
	if(l>=r)return node(n,1);
	--r; int t=lg[r-l+1]; return f[k][t][l]+f[k][t][r-(1<<t)+1];
}

ll query(int l,int r){
	if(l==1&&r==n)return 0;
	if(!ask(34,l,r).ok())return -1;
	ll res=0;
	Rep(i,33,0){
		node t=ask(i,l,r);
		if(!t.ok()) l=t.l,r=t.r,res|=(1ll<<i);
	}
	return res+1;
}

signed main()
{
	n=read(),m=read();
	For(i,1,n)a[i]=read();
	For(i,2,n)lg[i]=lg[i>>1]+1;
	For(k,0,34){
		if(!k){
			For(i,1,n-1)
				f[k][0][i]=node(min(a[i],a[i+1]),max(a[i],a[i+1]));
		}else{
			For(i,1,n-1)
				f[k][0][i]=ask(k-1,f[k-1][0][i].l,f[k-1][0][i].r);
		}
		For(j,1,16)
			For(i,1,n-(1<<j))
				f[k][j][i]=f[k][j-1][i]+f[k][j-1][i+(1<<(j-1))];
	}
	For(_,1,m){
		int l=read(),r=read();
		printf("%lld\n",query(l,r));
	}
	return 0;
}
```

---

## 作者：EXODUS (赞：2)

# Part 1：前言
CF 神仙题 Orz。

下文中，我们称**调用 $k$ 次题面中所述的 $f$ 函数后所得的区间为 $f^k(l,r)$**，下文中所述的对二元组 $(l_1,r_1),(l_2,r_2)$ 进行的加法操作后得到的结果为 $(\min(l_1,l_2),\max(r_1,r_2))$，二元组中的两个元素分别为 $l,r$，$p(l)$ 表示 $p$ 这个二元组中的元素 $l$。
# Part 2：正文

首先看到这种一眼不可做的题先猜性质 qwq。

注意到每次操作区间带有可拆分的性质。即

$$f^k(l,r)=f^k(l,l+1)+f^k(l+1,l+2)+\ ...\ +f^k(r-1,r)$$

如何证明？~~显然的~~ 考虑归纳证明。

首先 $k=0$ 时显然成立。

当 $k=1$ 时，我们设最小值$mn$ 出现在位置 $x$，最大值 $mx$ 出现在位置 $y$，则 $f(x-1,x)(l)=f(x,x+1)(l)=mn$，$f(y-1,y)(r)=f(y,y+1)(r)=mx$。显然每两个二元组中一定有一个存在于右式中，故左右答案相等。

同理可推广到高次情况。

现在咋做呢？

我们设 $g^k(x)$ 表示 $f^k(x,x+1)$，那么答案一定是找到最小的 $k$ 使得 $g^k(x)=(1,n)$，而 $f^k(1,n)=(1,n)$（如果此时 $a$ 中存在 $1$ 和 $n$，否则除非询问二元组是 $(1,n)$，经过任意次变换都不可能是 $(1,n)$），所以可以倍增做，预处理出所有 $k=2^i$ 时 $g^k(x)$ 的值，询问时转化为对于是否二元组 $(l,r)$ 调用 $2^k$ 次使得二元组不是 $(1,n)$，即 $g^{2^k}(l)+g^{2^k}(l+1)+\ ...\ +g^{2^k}(r-1)\neq (1,n)$，答案即为次数加 $1$。而上边的加法操作是可以 st 表维护的。

问题转化为如何快速求 $g$，$g^{2^k}(x)=g^{2^{(k-1)}}(g^{2^{(k-1)}}(x))$，而 $g^{2^{(k-1)}}(x)$ 是已知的，令其为 $(l,r)$，问题又变为询问 $g^{2^k}(x)=g^{2^{(k-1)}}((l,r))$，仿照上文的询问 st 表维护即可。

时间复杂度 $O(n\log^2n)$

# Part 3：代码
```cpp
#define rep(i,l,r) for(int i(l);i<=r;++i)
#define np pair<int,int>
#define mp make_pair
#define mn first
#define mx second

const int N=1e5+7;

int n;

np f[22][N][22];
int lg[N];

np query(int l,int r,int id){
	if(l>=r)return mp(n+1,0);
	return mp(min(f[id][l][lg[r-l]].mn,f[id][r-(1<<lg[r-l])][lg[r-l]].mn)
			 ,max(f[id][l][lg[r-l]].mx,f[id][r-(1<<lg[r-l])][lg[r-l]].mx));
}
int Q;

int ask(int l,int r){
	if(l==1&&r==n)return 0;
	np ans=query(l,r,20);int res=0;
	if(ans.mn!=1||ans.mx!=n)return -1;
	for(int i=19;i>=0;i--){
		ans=query(l,r,i);
		if(ans.mn!=1||ans.mx!=n)l=ans.mn,r=ans.mx,res+=1<<i;
	}
	return res+1;
}

int a[N];

int main(){
	n=read();Q=read();
	rep(i,1,n)a[i]=read();
	rep(i,2,n)lg[i]=lg[i>>1]+1;
	rep(j,1,n-1)f[0][j][0]=mp(min(a[j],a[j+1]),max(a[j],a[j+1]));
	rep(k,1,20)
		for(int j=1;j+(1<<k)<=n;j++)
			f[0][j][k].mx=max(f[0][j][k-1].mx,f[0][j+(1<<k-1)][k-1].mx),
			f[0][j][k].mn=min(f[0][j][k-1].mn,f[0][j+(1<<k-1)][k-1].mn);
	rep(i,1,20){//f^2^i
		rep(j,1,n-1){//f^2^i[j,j+1]
			f[i][j][0]=query(f[i-1][j][0].mn,f[i-1][j][0].mx,i-1);
		}
		rep(k,1,20)
			for(int j=1;j+(1<<k)<=n;j++)
				f[i][j][k].mx=max(f[i][j][k-1].mx,f[i][j+(1<<k-1)][k-1].mx),
				f[i][j][k].mn=min(f[i][j][k-1].mn,f[i][j+(1<<k-1)][k-1].mn);
	}
	while(Q--){
		int l=read(),r=read();
		printf("%d\n",ask(l,r));
	}
	return 0;
}
```

---

## 作者：orz_z (赞：1)

### CF1707E Replace

3500。

注意到 $f(l,r)= \bigcup_{i=l}^{r-1}f(i,i+1)$，即可合并。

还有，若 $[l1,r1]$ 和 $[l2,r2]$ 有交，则 $f(l1,r1)$ 和 $f(l2,r2)$ 可合并也有交。

考虑用某种数据结构维护从某个区间跳若干次到的区间，由于可并，可以倍增跳。

可是倍增还需维护双向跳，一向是区间，一向是次数，上述只证一级可并，还需证明 $k$ 级可并，即 $f^k(l,r)= \bigcup_{i=l}^{r-1}f^k(i,i+1)$。

证明：

上面证明了若 $[l1,r1],[l2,r2]$ 有交，则 $f(l1,r1),f(l2,r2)$ 有交，进一步有 $f^k(l1,r1),f^k(l2,r2)$ 有交可合并。

现合并无法快速求出。

显然，若 $[l1,r1],[l2,r2]$ 有交，则 $f(l1,r1) \cup f(l2,r2)=f(\min(l1,l2),\max(r1,r2))$。

证明完了，倍增预处理 $f^{2^k}(l,r)$ 即可。

时间复杂度 $\mathcal O(n\log^2 n+m\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

inline void write(ll x) {
	if (x < 0)
		x = -x, putchar('-');
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 1e5 + 10;

int n, m, a[_], lg[_];

struct Node {
	int l, r;
	Node operator + (Node b) {
		return {min(l, b.l), max(r, b.r)};
	}
	bool ok() {
		return l == 1 && r == n;
	}
} f[35][17][_];

Node mge(int k, int l, int r) {
	if (l >= r) return {n, 1};
	int t = lg[r - l];
	return f[k][t][l] + f[k][t][r - (1 << t)];
}

ll qry(int l, int r) {
	if (l == 1 && r == n) return 0;
	if (!mge(34, l, r).ok()) return -1;
	ll res = 0;
	for (int i = 33; i >= 0; --i) {
		Node tmp = mge(i, l, r);
		if (!tmp.ok()) l = tmp.l, r = tmp.r, res |= (1ll << i);
	}
	return res + 1;
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
	for (int k = 0; k <= 34; ++k) {
		if (!k)
			for (int i = 1; i < n; ++i)
				f[k][0][i] = {min(a[i], a[i + 1]), max(a[i], a[i + 1])};
		else
			for (int i = 1; i < n; ++i)
				f[k][0][i] = mge(k - 1, f[k - 1][0][i].l, f[k - 1][0][i].r);
		for (int j = 1; j <= 16; ++j)
			for (int i = 1; i + (1 << j) <= n; ++i)
				f[k][j][i] = f[k][j - 1][i] + f[k][j - 1][i + (1 << (j - 1))];
	}
	int l, r;
	while (m--) {
		l = read(), r = read();
		write(qry(l, r)), he;
	}
	return 0;
}
```



---

## 作者：CmsMartin (赞：1)

[「更好的阅读体验」](http://www.cmsblog.top/archives/cf1707ereplae)

## 题目描述

[题目传送门](https://codeforces.com/problemset/problem/1707/E)

## 思路

3500*。

乍一看没有什么很好的思路。观察一下 $f$ 的性质，将其换一个方式来表示，可以发现：$f((l,r))  = \cup_{i=l}^{r - 1}f((i, i + 1))$。这是显然的，这个集合是比他小的交起来得到。

然后，其实这相当于有结合律，很容易去拿各种奇怪高级数据结构去想办法维护。但是发现行不通。

考虑再看看有什么性质。我们要求的等价于最小的 $k$ 使得 $f^k((l,r))=(1,n)$。这样引发我们对 $f^k$ 进行探索。

再刚刚性质的启发下，我们手玩几组不难发现 $f^k((l,r))  = \cup_{i=l}^{r - 1}f^k((i, i + 1))$。

证明非常容易。假设 $(l,r) \cup (L,R) \neq \emptyset$，那么 $f((l,r)) \cup f((L,R)) \neq \emptyset$。依次归纳上去即可。

$k$ 可能很大，可以考虑想办法给他挂到 $\log$ 里。在指数上的话可以考虑倍增。

然后类似于 st 表一样维护 $f^{2^k}(x, x + 2 ^ t - 1)$ 的答案就可以了。

时间复杂度：假设 $q = \Theta(n)$， 粗略实现 $\mathcal{O}(n \log^2 n)$，精细实现可以做到 $\mathcal{O}(n \log n)$ 

## 代码

写的很丑啊。1500ms 的题目跑了 1496ms,喜提最劣解。

[$\mathcal{Link}$](https://codeforces.com/contest/1707/submission/213728707)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1707E)

**题目大意**

> 给定 $a_1\sim a_n$，定义 $[l,r]$ 进行一次迭代为 $[l,r]\gets f(l,r)=[\min a_{l\sim r},\max a_{l\sim r}]$，$q$ 次询问 $[l,r]\to [1,n]$ 最少迭代几次。
>
> 数据范围：$n,q\le 10^5$。

**思路分析**

首先肯定要用倍增维护 $f^{2^k}(l,r)$，问题是初始的 $(l,r)$ 太多，难以维护，我们需要减少维护的 $[l,r]$ 对数。

可以发现如果两个区间 $[l_1,r_1],[l_2,r_2]$ 有交 $i$，那么 $f(l_1,r_1),f(l_2,r_2)$ 有交 $a_i$。

因此对于两个有交区间 $X,Y$，$f(X\cup Y)=f(X)\cup f(Y)$。

那么维护 $f(l,r)=f(l,l+1)\cup f(l+1,l+2)\cup\cdots\cup f(r-1,r)$。

因此我们维护所有 $f^{2^k}(i,i+1)$ 即可，转移时设 $[l,r]=f^{2^{k-1}}(i,i+1)$，求 $\bigcup_{j=l}^{r-1} f^{2^{k-1}}(j,j+1)$，查询也是类似的。

对每层开 ST 表维护即可。

时间复杂度 $\mathcal O(n\log^2n+q\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef array<int,2> seg;
const int MAXN=1e5+5;
seg f[18][18][MAXN];
inline seg operator +(const seg &x,const seg &y) { return {min(x[0],y[0]),max(x[1],y[1])}; }
int bit(int x) { return 1<<x; }
seg qry(int k,int l,int r) {
	int t=__lg(r-l+1);
	return f[k][t][l]+f[k][t][r-bit(t)+1];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,q; cin>>n>>q;
	for(int i=1,x;i<=n;++i) cin>>x,f[0][0][i]={x,x};
	for(int j=1;j<18;++j) for(int i=1;i+bit(j)-1<=n;++i) {
		f[0][j][i]=f[0][j-1][i]+f[0][j-1][i+bit(j-1)];
	}
	for(int k=1;k<18;++k) for(int j=0;j<18;++j) for(int i=1;i+bit(j)-1<=n;++i) {
		f[k][j][i]=qry(k-1,f[k-1][j][i][0],f[k-1][j][i][1]);
	}
	for(int l,r,s;q--;) {
		cin>>l>>r,s=0;
		if(l==1&&r==n) { cout<<"0\n"; continue; }
		for(int k=17;~k;--k) {
			auto i=qry(k,l,r);
			if(1<i[0]||i[1]<n) l=i[0],r=i[1],s+=1<<k;
		}
		auto i=qry(0,l,r);
		if(1<i[0]||i[1]<n) cout<<"-1\n";
		else cout<<s+1<<"\n";
	}
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：0)

錦瑟無端五十絃，一絃一柱思華年。

2023 年北京集训好题分享讲了这题。

## 题意

给定一个长为 $n$ 的序列 $a_n, \forall i \in [1, n], 1 \le a_i \le n$。

定义 $f(l,r)=(\min_{i=l}^{r}{a_i}, \max_{i=l}^{r} {a_i})$。

$q$ 次询问，每次给定 $l,r$，询问最小的 $k$ 使得 $f^k (l, r) = (1, n)$，无解输出 $-1$。

## 题解

首先两个十分显然的性质：

- 如果某次操作把区间变成了 $(1, n)$，那么无论再操作多少次这个区间都是 $(1, n)$；
- 状态数是 $O(n^2)$ 的。

这引导我们想到，如果能求得 $f^k(l, r)$ 在 $k \ge n^2$ 时的结果，就能判定是否有解，同时也可以利用二分之类的方法求得答案。

Key Observation 1: $f(l, r) = \bigcup_{i=l}^{r-1}{f(i, i+1)}$。
  
证明：考虑归纳，则只需证明：$[l_1, r_1] \cup [l_2, r_2] = [l, r], [l_1, r_1] \cap [l_2, r_2] \ne \varnothing$，则 $f(l, r) = f(l_1, r_1) \cup f(l_2, r_2)$。而这是显然的。

Key Observation 2: $f^k(l, r) = \bigcup_{i=l}^{r-1}{f^k(i, i+1)}$。

证明：考虑上一页中结论，每次增加 $k$ 相邻两个区间仍然总是有交。

$$
\begin{aligned}
&f^k(l,r) \\
=& f^k([l_1, r_1] \cup [l_2, r_2]) \\
=& f(f^{k - 1}(l_1, r_1) \cup f^{k - 1}(l_2, r_2)) \\
=& f(f^{k - 1}(l_1, r_1)) \cup f(f^{k - 1}(l_2, r_2)) \\
=& f^{k}(l_1, r_1) \cup f^{k}(l_2, r_2) \\
\end{aligned}
$$

然后我们发现到最后相邻两项区间还是有交，因此我们最终区间到左、右端点就是这些区间左、右节点的极值。这允许我们通过维护 $[i, i+1]$ 的信息，并利用 st 表求得任意区间的结果。

我们令 $F/G_{k, j, i}$ 为 $f^k(j, j+2^i - 1)$ 的左、右端点。那么对于 $i$ 这维的转移，我们有：

$$
\begin{aligned}
F_{k,j,i} &= \min(F_{k,j,i - 1}, F_{k,j + 2^{i-1}, i - 1}) \\
G_{k,j,i} &= \max(G_{k,j,i - 1}, G_{k,j + 2^{i-1}, i - 1})
\end{aligned}
$$

对于 $k$ 这一维，我们有：

$$
\begin{aligned}
&f^k(l,r) = f(f^{k - 1}(l_1, r_1) \cup f^{k - 1}(l_2, r_2)) \\
\end{aligned}
$$

那么我们知道 $f^k(l, r)$ 的左右端点分别是：

$$
\begin{aligned}
&\min(F_{k, l, lg}, F_{k,r - 2^{lg} + 1,lg}) \\
&\max(G_{k, l, lg}, G_{k,r - 2^{lg} + 1,lg})
\end{aligned}
$$

至此，预处理后我们能够在 $O(1)$ 时间内求解 $f^k(l, r)$。二分或倍增即可求得答案。

## 代码

代码实现把 $F$ 和 $G$ 放在了同一个数组里来卡常。

```cpp
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

const int MAX = 1e5 + 5;
const int LG = 35;
const int MAXX = 37;

int n, q, l, r;
int a[MAX], lg2[MAX], f[MAXX][MAX][20][3];

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
void init(int k)
{
	for (int i = 1; (1 << i) < n; ++i)
	{
		for (int j = 1; j + (1 << i) <= n; ++j)
		{
			f[k][j][i][0] = min(f[k][j][i - 1][0], f[k][j + (1 << (i - 1))][i - 1][0]);
			f[k][j][i][1] = max(f[k][j][i - 1][1], f[k][j + (1 << (i - 1))][i - 1][1]);
		}
	}
}

int getl(int l, int r, int k)
{
	int lg = lg2[r - l + 1];
	return min(f[k][l][lg][0], f[k][r - (1 << lg) + 1][lg][0]);
}

int getr(int l, int r, int k)
{
	int lg = lg2[r - l + 1];
	return max(f[k][l][lg][1], f[k][r - (1 << lg) + 1][lg][1]);
}

void solve()
{
	l = read(); r = read(); long long res = 0;
	if (l == 1 and r == n) { printf("0\n"); return ; }
	else if (l == r) { printf("-1\n"); return ; }
	int _l = getl(l, r - 1, LG), _r = getr(l, r - 1, LG);
	if (_l != 1 or _r != n) { printf("-1\n"); return ; }
	for (int i = LG - 1; i >= 0; --i)
	{
		_l = getl(l, r - 1, i), _r = getr(l, r - 1, i);
		if (_l != 1 or _r != n) { res += (1ll << i); l = _l; r = _r; }
	}
	_l = getl(l, r - 1, 0), _r = getr(l, r - 1, 0);
	if (_l == 1 and _r == n) { printf("%lld\n", res + 1); } else { printf("-1\n"); }
}

int main()
{
	n = read(); q = read();
	for (int i = 1; i <= n; ++i) { a[i] = read(); }
	for (int i = 2; i <= n; ++i) { lg2[i] = lg2[i >> 1] + 1; }
	for (int i = 1; i <  n; ++i) { f[0][i][0][0] = min(a[i], a[i + 1]); f[0][i][0][1] = max(a[i], a[i + 1]); }
	init(0);
	for (int i = 1; i <= LG; ++i)
	{
		for (int j = 1; j <  n; ++j)
		{
			f[i][j][0][0] = getl(f[i - 1][j][0][0], f[i - 1][j][0][1] - 1, i - 1);
			f[i][j][0][1] = getr(f[i - 1][j][0][0], f[i - 1][j][0][1] - 1, i - 1);
		}
		init(i);
	}
	while (q--) { solve(); }
	return 0;
}
```

---

## 作者：Sunny郭 (赞：0)

注意到 $f(l,r)=\bigcup\limits_{i=l}^{r-1}f(l,l+1)$

当 $[l,r],[L,R]$ 有交时 $f(l,r)$ 和 $f(L,R)$ 也有交，并且可以合并
（合并指 $l=min(f(l,r)(l),f(L,R)(l))$，$r$ 同理），那么可以归纳地证明操作 $k$ 次的 $f$ 后也能合并，即 $f^k(l,r)=\bigcup\limits_{i=l}^{r-1}f^k(l,l+1)$

那我们维护一个倍增的 $f^k(l,r)$，区间并用 $st$表维护即可，可以注意到一个答案的上界时 $n^2$ 即状态数，但其他题解说是 $2n$，不太懂。

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define l first
#define r second
#define mp make_pair
using namespace std;
using ll = long long;
const int N = 1e5 + 7, T = 18;

int i, j, k, n, m, q, a[N];
pi f[T][T][N];//寻址？？ 

pi operator + (const pi& x, const pi& y) {return mp(min(x.l, y.l), max(x.r, y.r));}

pi ask(int l, int r, int t) {
	if(l > r) return mp(a[l], a[l]);
	int k = __lg(r - l + 1);
	return f[t][k][l] + f[t][k][r - (1 << k) + 1];
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(i = 1; i <= n; i++) cin >> a[i];
	for(i = 1; i < n; i++) f[0][0][i] = mp(min(a[i], a[i + 1]), max(a[i], a[i + 1]));
	for(j = 1; j < T; j++) for(i = 1; i + (1 << j) - 1 < n; i++) f[0][j][i] = f[0][j - 1][i] + f[0][j - 1][i + (1 << j - 1)];
	for(k = 1; k < T; k++) {
		for(i = 1; i < n; i++) {
			pi u = f[k - 1][0][i];
			f[k][0][i] = ask(u.l, u.r - 1, k - 1);
		}
		for(j = 1; j < T; j++) for(i = 1; i + (1 << j) - 1 < n; i++) f[k][j][i] = f[k][j - 1][i] + f[k][j - 1][i + (1 << j - 1)];
	}
	while(q--) {
		int L, R; cin >> L >> R; 
		if(L == 1 && R == n) {cout << "0\n"; continue;}
		int s = 0; pi u = mp(L, R);
		for(i = T - 1; ~i; i--) {
			pi v = ask(u.l, u.r - 1, i);
			if(v.l != 1 || v.r != n) s += 1 << i, u = v;
		}
		pi v = ask(u.l, u.r - 1, 0);
		cout << (v.l == 1 && v.r == n ? s + 1 : -1) << "\n";
	}
	return 0;
}
```

---

## 作者：VoidX (赞：0)

首先答案上界是 $2n$，大概是先转一圈然后再依次扩展。

我们可以维护一个 $f^{2^k}(l,r)$ 来用于在询问的时候快速回答，但是 $(l,r)$ 的数量是爆炸的 $O(n^2)$。现在的问题是如何减少 $f(l,r)$ 需要的数量。

所以要找性质。我们有在 $[l_1,r_1]$ 和 $[l_2,r_2]$ 有交时，令 $[l,r] = [l_1,r_1]\cup [l_2,r_2]$，那么 $f^k ([l,r])=f^k ([l_1,r_1]) \cup f^k ([l_2,r_2])$。

因为它们的值域相交，所以 $f (l_1,r_1) \cap f (l_2,r_2)\ne \varnothing$，而在它们有交集的前提下，有 $f (l_1,r_1) \cup f (l_2,r_2)=f(\min\{l_1,l_2\},\max\{r_1,r_2\})$，对这个东西进行数学归纳，所以上面的那个是对的。

也就是说我们使用 ST 表维护每个 $f^{2^k}$ 的值即可，内部的数量级从 $O(n^2)$ 降低到了 $O(n\log n)$，总时间复杂度 $O((n+q)\log ^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5; 

int n, q; 
int a[N], mn[18][17][N], mx[18][17][N]; 

inline int askmn(int x, int l, int r) {
    int k = __lg(r - l + 1); 
    return min(mn[x][k][l], mn[x][k][r - (1 << k) + 1]); 
}
inline int askmx(int x, int l, int r) {
    int k = __lg(r - l + 1); 
    return max(mx[x][k][l], mx[x][k][r - (1 << k) + 1]); 
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n >> q; 
    for (int i = 1; i <= n; ++i) cin >> a[i], mn[0][0][i] = mx[0][0][i] = a[i]; 
    for (int i = 1; i <= 16; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            mn[0][i][j] = min(mn[0][i - 1][j], mn[0][i - 1][j + (1 << i - 1)]), 
            mx[0][i][j] = max(mx[0][i - 1][j], mx[0][i - 1][j + (1 << i - 1)]); 
    for (int k = 1; k <= 17; ++k) 
        for (int i = 0; i <= 16; ++i) for (int j = 1; j + (i ? (1 << i - 1) : 0) <= n; ++j)
            mn[k][i][j] = askmn(k - 1, mn[k - 1][i][j], mx[k - 1][i][j]), 
            mx[k][i][j] = askmx(k - 1, mn[k - 1][i][j], mx[k - 1][i][j]); 
    while (q--) {
        int l, r, ans = 0; cin >> l >> r; 
        if (l == 1 && r == n) { cout << "0\n"; continue; }
        for (int j = 17; j >= 0; --j) {
            int nl = askmn(j, l, r), nr = askmx(j, l, r); 
            if (nl > 1 || nr < n) ans += 1 << j, l = nl, r = nr; 
        }
        int nl = askmn(0, l, r), nr = askmx(0, l, r); 
        l = nl, r = nr; 
        if (l > 1 || r < n) cout << "-1\n"; 
        else cout << ans + 1 << "\n"; 
    }
    return 0;
}
```

---

## 作者：tribool4_in (赞：0)

找性质题。

首先对于这种问题可以想到倍增，但显然不能直接对于 $O(n^2)$ 对 $(l,r)$ 处理，于是考虑如何只维护 $O(n)$ 个信息来实现，于是大胆考虑对于每个 $i$ 只对 $[i,i+1]$ 倍增，维护出它映射 $2^k$ 次后的区间。

于是可以猜想有 $\displaystyle f^k((l,r))=\bigcup_{i=l}^{r-1}f^k((i,i+1))$（其中 $f^k$ 表示 $f$ 复合自身 $k$ 次），于是对 $2^k$ 每轮倍增时维护一遍 ST 表即可 $O(1)$ 求出一段区间并。

考虑如何证明，容易发现如果 $[l_1,r_1]\cap [l_2,r_2] \neq \varnothing$，则有 $f([l_1,r_1]\cup [l_2,r_2])=f([l_1,r_1])\cup f([l_2,r_2])$。于是归纳证明若对于 $f^k$ 满足，则有：

$$
\begin{aligned}
  & f^{k+1}([l_1,r_1]\cup[l_2,r_2]) \\
  & =f(f^{k}([l_1,r_1]\cup[l_2,r_2])) \\
  & =f(f^{k}([l_1,r_1])\cup f^{k}([l_2,r_2])) \\
  & =f(f^{k}([l_1,r_1]))\cup f(f^{k}([l_2,r_2])) \\
  & =f^{k+1}([l_1,r_1])\cup f^{k+1}([l_2,r_2]) \\
\end{aligned}
$$

于是做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, K = 19;
int n, q, a[N], lg2[N];
int fmn[K][N][K], fmx[K][N][K];
int getmin(int k, int l, int r) {
    int b = lg2[r - l + 1];
    return min(fmn[k][l][b], fmn[k][r - (1 << b) + 1][b]);
}
int getmax(int k, int l, int r) {
    int b = lg2[r - l + 1];
    return max(fmx[k][l][b], fmx[k][r - (1 << b) + 1][b]);
}
int calc(int l, int r) {
    if (l == 1 && r == n) return 0;
    if (l == r) return -1;
    int ans = INT_MAX, tmp = 0;
    for (int k = K - 1; k >= 0; k--)  {
        int nxl = getmin(k, l, r - 1), nxr = getmax(k, l, r - 1);
        if (nxl == 1 && nxr == n) ans = min(ans, tmp + (1 << k));
        else tmp += (1 << k), l = nxl, r = nxr;
    }
    return ans == INT_MAX ? -1 : ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i < n; i++) fmn[0][i][0] = min(a[i], a[i + 1]), fmx[0][i][0] = max(a[i], a[i + 1]);
    for (int j = 1; j < K; j++) {
        for (int i = 1; i + (1 << j) - 1 < n; i++) {
            fmn[0][i][j] = min(fmn[0][i][j - 1], fmn[0][i + (1 << j - 1)][j - 1]);
            fmx[0][i][j] = max(fmx[0][i][j - 1], fmx[0][i + (1 << j - 1)][j - 1]);
        }
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i < n; i++) fmn[k][i][0] = getmin(k - 1, fmn[k - 1][i][0], fmx[k - 1][i][0] - 1), fmx[k][i][0] = getmax(k - 1, fmn[k - 1][i][0], fmx[k - 1][i][0] - 1);
        for (int j = 1; j < K; j++) {
            for (int i = 1; i + (1 << j) - 1 < n; i++) {
                fmn[k][i][j] = min(fmn[k][i][j - 1], fmn[k][i + (1 << j - 1)][j - 1]);
                fmx[k][i][j] = max(fmx[k][i][j - 1], fmx[k][i + (1 << j - 1)][j - 1]);
            }
        }
    }
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        cout << calc(l, r) << '\n';
    }
    return 0;
}
```

---

## 作者：Leasier (赞：0)

因为 $f([1, n]) = [1, n]$，我们可以考虑倍增。现在我们需要对于某个 $2^i$，询问 $f^{2^i}([l, r])$，其中 $f^k([l, r])$ 表示把 $f$ 作用在 $[l, r]$ 上 $k$ 遍。

倍增时 $f^{2^i}([l, r]) = f^{2^{i - 1}}(f^{2^{i - 1}}([l, r]))$，则我们需要考虑怎样利用相对有限的信息快速求值（大概只能有 $O(n)$ 或 $O(n \log n)$ 的样子）。

注意到以下性质：

- $f([l, r]) = \cup_{i = l}^{r - 1} f([i, i + 1])$。

证明可以考虑逐项添加。

进而我们可以归纳得出：$f^k([l, r]) = \cup_{i = l}^{r - 1} f^k([i, i + 1])$。

于是对某个 $2^i$ 而言，有用的信息只有 $O(n)$ 个。又因为 $\cup$ 可重复贡献，整一个 ST 表状物维护即可。

时间复杂度为 $O(n \log^2 n + q \log n)$。

可能需要注意以下细节：

- 在倍增和回答询问时特判 $l = r$ 的情况。
- 如果被卡常了，可以考虑调换一下数组各维间的顺序。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

typedef struct Segment_tag {
	int l;
	int r;
	Segment_tag(){}
	Segment_tag(int l_, int r_){
		l = l_;
		r = r_;
	}
} Segment;

int _log2[100007], a[100007];
Segment g[37][100007], h[37][100007][17];

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

Segment operator +(const Segment a, const Segment b){
	return Segment(min(a.l, b.l), max(a.r, b.r));
}

Segment operator +=(Segment &a, const Segment b){
	return a = a + b;
}

bool operator !=(const Segment a, const Segment b){
	return a.l != b.l || a.r != b.r;
}

inline Segment query(int l, int r, int k){
	if (l == r) return Segment(a[l], a[l]);
	int t = _log2[r - l];
	return h[k][l][t] + h[k][r - (1 << t)][t];
}

inline void init(int n){
	int m = log2((ll)n * n), k;
	for (register int i = 2; i < n; i++){
		_log2[i] = _log2[i / 2] + 1;
	}
	k = _log2[n - 1];
	for (register int i = 1; i < n; i++){
		g[0][i] = h[0][i][0] = Segment(min(a[i], a[i + 1]), max(a[i], a[i + 1]));
	}
	for (register int i = 0; i <= m; i++){
		int id = i - 1;
		if (i > 0){
			for (register int j = 1; j < n; j++){
				g[i][j] = query(g[id][j].l, g[id][j].r, id);
			}
		}
		for (register int j = 1; j < n; j++){
			h[i][j][0] = g[i][j];
		}
		for (register int j = 1; j <= k; j++){
			int jd = j - 1, t1 = n - (1 << j), t2 = 1 << jd;
			for (register int x = 1; x <= t1; x++){
				h[i][x][j] = h[i][x][jd] + h[i][x + t2][jd];
			}
		}
	}
}

int main(){
	int n, q, m;
	bool flag1 = false, flagn = false;
	Segment full;
	scanf("%d %d", &n, &q);
	m = log2((ll)n * n);
	full = Segment(1, n);
	for (register int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		flag1 |= a[i] == 1;
		flagn |= a[i] == n;
	}
	init(n);
	for (register int i = 1; i <= q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		if (l == 1 && r == n){
			printf("0\n");
			continue;
		}
		ll ans = 0;
		Segment seg(l, r);
		for (register int j = m; j >= 0; j--){
			Segment cur = query(seg.l, seg.r, j);
			if (cur != full){
				seg = cur;
				ans += 1ll << j;
			}
		}
		if (query(seg.l, seg.r, 0) != full){
			printf("-1\n");
		} else {
			printf("%lld\n", ans + 1);
		}
	}
	return 0;
}
```

---

## 作者：liaiyang (赞：0)

很水的一道 CF3500\* 黑。

我们首先证明有 $f^k([l,r])=\bigcup_{i=l}^{r-1}f^k([l,l+1])$。

首先显然我们有一个引理：如果 $[l,r]\cap [l^\prime,r^\prime]\not=\varnothing$，那么 $f^k([l,r]\cup[l^\prime,r^\prime])=f^k([l,r])\cup f^k([l^\prime,r^\prime])$。

证明就是使用数学归纳法，首先显然 $k=1$ 时 $f([l,r]\cup[l^\prime,r^\prime])=f([l,r])\cup f([l^\prime,r^\prime])$ 成立，假如当 $k=n-1$ 时成立，那么
$$
\begin{aligned}
f^n\color{Red}(\color{Black}[l,r]\cup[l^\prime,r^\prime]\color{Red})\color{Black}&=f\color{Red}(\color{Black}f^{n-1}\color{Blue}(\color{Black}[l,r]\cup[l^\prime,r^\prime]\color{Blue})\color{Black}\color{Red})\color{Black}\\
&=f\color{Red}(\color{Black}f^{n-1}\color{Blue}(\color{Black}[l,r]\color{Blue})\color{Black}\cup f^{n-1}\color{Blue}(\color{Black}[l^\prime,r^\prime]\color{Blue})\color{Red})\\
&=f\color{Red}(\color{Black}f^{n-1}\color{Blue}(\color{Black}[l,r]\color{Blue})\color{Black}\color{Red})\color{Black}\cup f\color{Red}(\color{Black}f^{n-1}\color{Blue}(\color{Black}[l^\prime,r^\prime]\color{Blue})\color{Black}\color{Red})\color{Black}\\
&=f^n\color{Red}(\color{Black}[l,r]\color{Red})\color{Black}\cup f^n\color{Red}(\color{Black}[l^\prime,r^\prime]\color{Red})\color{Black}\\
&&\square
\end{aligned}
$$

其次，我们总有 $[l,l+1]\cap [l+1,l+2]\not=\varnothing$。

所以命题成立。

然后就是一道简单的题了。

我们维护每一个 $f^{2^k}([i,i+1])$，然后对于每一个 $f^{2^k}$ 维护一个 ST 表，查询时倍增即可。

时间复杂度 $O(n\log^2n+q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second 
#define rd read()
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
inline int read(int u=0, char c=getchar(), bool f=false){
	for (;!isdigit(c);c=getchar()) f|=c=='-';
	for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
	return f?-u:u;
}
inline void wt(int x){
  	if(x<0) x=-x,putchar('-');
  	if(x>9) wt(x/10);
  	putchar(x%10+48);
}
inline void wt(int x,char c){wt(x),putchar(c);}
// const int inf=~0U>>1,linf=~0ULL>>1; 
const int N=1e5+10,logN=20;
int n,q,a[N],mx[logN][N][logN],mn[logN][N][logN],log2_[N];
int query_max(int x,int l,int r){
	if(l>=r) return 1;
	r--;
	int k=log2_[r-l+1];
	return max(mx[x][l][k],mx[x][r-(1<<k)+1][k]);
}
int query_min(int x,int l,int r){
	if(l>=r) return n;
	r--;
	int k=log2_[r-l+1];
	return min(mn[x][l][k],mn[x][r-(1<<k)+1][k]);
}
main(){
	n=rd,q=rd;
	for(int i=1;i<=n;i++) a[i]=rd;
	for(int i=1;i<n;i++){
		mn[0][i][0]=min(a[i],a[i+1]);
		mx[0][i][0]=max(a[i],a[i+1]);
	}mn[0][n][0]=mx[0][n][0]=a[n];
	for(int i=2;i<=n;i++) log2_[i]=log2_[i>>1]+1;
	for(int j=1;j<=18;j++)
		for(int i=1;i+(1<<j)<=n;i++)
			mx[0][i][j]=max(mx[0][i][j-1],mx[0][i+(1<<j-1)][j-1]),
			mn[0][i][j]=min(mn[0][i][j-1],mn[0][i+(1<<j-1)][j-1]);
	for(int x=1;x<=18;x++){
		for(int i=1;i<=n;i++)
			mx[x][i][0]=query_max(x-1,mn[x-1][i][0],mx[x-1][i][0]),
			mn[x][i][0]=query_min(x-1,mn[x-1][i][0],mx[x-1][i][0]);
		for(int j=1;j<=18;j++)
			for(int i=1;i+(1<<j)<=n;i++)
				mx[x][i][j]=max(mx[x][i][j-1],mx[x][i+(1<<j-1)][j-1]),
				mn[x][i][j]=min(mn[x][i][j-1],mn[x][i+(1<<j-1)][j-1]);
	}
	while(q--){
		int l=rd,r=rd;
		long long ans=0;
		if(l==1&&r==n){wt(0,'\n');continue;}
		if(query_min(18,l,r)!=1||query_max(18,l,r)!=n){wt(-1,'\n');continue;}
		for(int i=17;i>=0;i--){
			int l_=query_min(i,l,r),r_=query_max(i,l,r);
			if(l_!=1||r_!=n) l=l_,r=r_,ans+=(1ll<<i);
		}
		wt(ans+1,'\n');
	}
    return 0;
}
```

---

## 作者：赵悦岑 (赞：0)

## 题意

给定一个长度为 $n$ 的序列 $a$，定义一个二元函数 $f$：

$$f((l,r))=(\min\limits_{i=l}^r a_i,\max\limits_{i=l}^r a_i)(l \leq r)$$

有 $q$ 次询问，每次询问二元组 $(l,r)$ 至少经过多少次 $f$ 操作后变为 $(1,n)$。

## 分析

首先把 $l=1,r=n$ 和 $\forall i \in [1,n],a_i \ne 1$，$\forall i \in [1,n],a_i \ne n$ 的情况特判掉。

观察数据范围是 $10^5$，大概率是 $n\log n$ 算法，由于这是询问最少需要多少次操作，而 $f((1,n))=(1,n)$（在特判之后），考虑倍增。

但是我们发现一个问题，二元组 $(l,r)$ 的总数是 $n^2$ 级别的，所以我们不可能将所有区间都倍增预处理出来，我们就要想如何把 $n^2$ 级别的区间数转化为 $n$ 或者 $n\log n$ 的区间数。

我们可能容易想到这么多区间操作几次后数量会大大减少，但是反例也很显然：$5,1,2,3,4,7,8,9,10,6$，形如这样的情况中不管跳多少次，个数仍然是 $n^2$ 级别的。因此此路不通

但是可以想到类似的 ST 表，它的区间数也是 $n^2$，但是每个区间 $(l,r)$ 都可以由另外两个区间 $(l,i),(j,r)(l \leq i,j \leq r,i \geq j-1)$ 合并得出，所以只需要预处理 $n\log n$ 级别的区间数即可。所以我们也可以大胆做出这样的猜想。

令

$$f^k((l,r))=\begin{cases}
 f(f^{k-1}(l,r)) & (k>0)\\(l,r) & (k=0)
\end{cases}$$

显然，如果 $(l_1,r_1)$ 与 $(l_2,r_2)$ 有交集，那么 $f((l_1,r_1))\bigcup f((l_2,r_2)) = f((l_1,r_1)\bigcup (l_2,r_2))$，因为如果两个区间有交集，那么他们就含有相同的数字，这个数字同时存在于两个区间的值域中，又值域连续，所以两个区间的值域有交。

同理，我们也可以证得对于任意 $k$ 都满足上式。所以我们就可以像 ST 表一样表示出区间 $(l,l+2^k-1)$ 跳 $2^t$ 步后的结果，但是这里必须满足两个区间有交，而 ST 表是两个区间覆盖原区间即可，我们只需要令 $b_i = \max(a_i,a_{i+1})$，对 $b$ 做 ST 表即可，最小值同理。

## code
```
#include<bits/stdc++.h>
using namespace std;
const int N=100001,M=18;//
int n,m,q,a[N],pw[N],lg[N],b1[N][M+1][M+1],b2[N][M+1][M+1];
int sum1(int x,int y,int k)
{
    if(x>=y) return n+1;
    --y;
    return min(b1[x][lg[y-x]][k],b1[y-pw[lg[y-x]]+1][lg[y-x]][k]);
}
int sum2(int x,int y,int k)
{
    if(x>=y) return 0;
    --y;
    return max(b2[x][lg[y-x]][k],b2[y-pw[lg[y-x]]+1][lg[y-x]][k]);
}
void init()
{
    for(int i=1;i<=n-1;++i)
    {
        b1[i][0][0]=min(a[i],a[i+1]);
        b2[i][0][0]=max(a[i],a[i+1]);
        lg[i]=log2(i);
    }
    q=log2(n-1);
    pw[0]=1;
    for(int i=1;i<=q;++i) pw[i]=pw[i-1]*2;
    for(int r=0;r<=M;++r)
    {
        if(r!=0)
        {
            for(int i=1;i<=n-1;++i)
            {
                b1[i][0][r]=sum1(b1[i][0][r-1],b2[i][0][r-1],r-1);
                b2[i][0][r]=sum2(b1[i][0][r-1],b2[i][0][r-1],r-1);
            }
        }
        for(int i=1;i<=q;++i)
        {
            for(int j=1;j<=n-pw[i];++j)
            {
                b1[j][i][r]=min(b1[j][i-1][r],b1[j+pw[i-1]][i-1][r]);
                b2[j][i][r]=max(b2[j][i-1][r],b2[j+pw[i-1]][i-1][r]);
            }
        }
    }
}
int check(int x,int y)
{
    if(x==1&&y==n) return 0;
    if(sum1(x,y,M)!=1||sum2(x,y,M)!=n) return -1;
    int s=0;
    for(int i=M;i>=0;--i)
    {
        if(sum1(x,y,i)!=1||sum2(x,y,i)!=n)
        {
            s+=(1<<i);
            int x0=sum1(x,y,i),y0=sum2(x,y,i);
            x=x0,y=y0;
        }
    }
    return s+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    init();
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int z=check(x,y);
        if(z==-1) printf("-1\n");
        else printf("%d\n",z);
    }
    return 0;
}
```

---

