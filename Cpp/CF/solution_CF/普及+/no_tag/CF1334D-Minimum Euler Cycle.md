# Minimum Euler Cycle

## 题目描述

You are given a complete directed graph $ K_n $ with $ n $ vertices: each pair of vertices $ u \neq v $ in $ K_n $ have both directed edges $ (u, v) $ and $ (v, u) $ ; there are no self-loops.

You should find such a cycle in $ K_n $ that visits every directed edge exactly once (allowing for revisiting vertices).

We can write such cycle as a list of $ n(n - 1) + 1 $ vertices $ v_1, v_2, v_3, \dots, v_{n(n - 1) - 1}, v_{n(n - 1)}, v_{n(n - 1) + 1} = v_1 $ — a visiting order, where each $ (v_i, v_{i + 1}) $ occurs exactly once.

Find the lexicographically smallest such cycle. It's not hard to prove that the cycle always exists.

Since the answer can be too large print its $ [l, r] $ segment, in other words, $ v_l, v_{l + 1}, \dots, v_r $ .

## 说明/提示

In the second test case, the lexicographically minimum cycle looks like: $ 1, 2, 1, 3, 2, 3, 1 $ .

In the third test case, it's quite obvious that the cycle should start and end in vertex $ 1 $ .

## 样例 #1

### 输入

```
3
2 1 3
3 3 6
99995 9998900031 9998900031```

### 输出

```
1 2 1 
1 3 2 3 
1```

# 题解

## 作者：Mcggvc (赞：9)

题意：给你一个n个结点的完全图，找出最小字典序的欧拉回路遍历的结点，输出其中一段。

就是先从小的结点开始，向尽量小的结点走，多枚举一下就可以找出规律。

![](https://cdn.luogu.com.cn/upload/image_hosting/4iewm97j.png)

两个两个看，以1开头的有n - 1个，以二开头的有n - 2个，以此类推。
这样就可以快速算出 l 所在位置开头的结点，然后枚举输出。

考场代码，贼丑

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lld;
int main() {
//	freopen("data.in", "r", stdin);
	int T; scanf("%d", &T);
	while(T--) {
		lld n, l, r; scanf("%lld%lld%lld", &n, &l, &r);
		lld p = 1;
		for(p = 1; p <= n - 1; p++) {
			if(p * (n * 2 - p - 1ll) > l) break;
		}
		p -= 2;
		lld st = (p * ((n * 2) - p - 1));
		p = p + 1; 
		for(lld i = p; i < n; i++) {
			for(lld j = i + 1; j <= n; j++) {
				st++;
				if(st >= l && st <= r) printf("%lld ", i);
				st++;
				if(st >= l && st <= r) printf("%lld ", j);
				if(st > r) break;
			}
		}
		if(st < r) printf("1");
		printf("\n");
	}
	return 0;
}

```

---

## 作者：_lyx111 (赞：3)

# CF1334D Minimum Euler Cycle

[link](https://codeforces.com/problemset/problem/1334/D)

## 题意

$T$ 组询问，每次询问给定一张有 $n$ 个结点的完全图（ 图中任意两点之间都有且仅有一条连线 ），求其字典序最小的欧拉序 $E_1,E_2,\dots E_{n\times(n-1)+1}$ 中的一段 $E_l,E_{\ l+1},\dots,E_r$

数据范围：$1\le T\le 100,2\le n\le 10^5,1\le l\le r\le n\times (n-1)+1,r-l+1\le 10^5$

## 分析

题目中要求的是 “ 字典序最小的欧拉序中的一段 ” ，很显然地想到所求的欧拉序应该长这样：

$$1,2,1,3,\dots,1,n,2,3,2,4,\dots,2,n,3,4\dots,(n-1),n,1$$

这样看大概能看出一点规律，我们把它分开：

$$1,2,1,3,\dots 1,n$$

$$2,3,2,4,\dots,2,n$$

$$3,4,\dots,3,n$$

$$\dots$$

$$(n-1),n$$

$$1$$

这样就能发现规律了：

第 $i$ 行（ $1\le i\le n-1$ ）共有 $2\times (n-i)$ 个点，可将其分为 $n-i$ 组，分别为 $(i,i+1),(i,i+2),\dots,(i,n)$，前 $i$ 行一共有 $\sum_{j=1}^i 2\times (n-j)=i\times(2n-i-1)$ 个点。

那么通过这些信息我们很容易就可以知道 $l$ 所在的行数 $id$，从当前行开始枚举直到欧拉序上 $l$ 到 $r$ 的所有点都已被输出或已经枚举完第 $n-1$ 行，那么就可以正确地输出答案了

时间复杂度：$O(\max(n,r-l+1))$

## 一些细节

1. $l,r$ 需要使用 long long 来存储

2. 要特殊处理 $r=n\times (n-1)+1$ 的情况

其余的细节可以看代码里的注释

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
int n; //点数 
long long l,r; //求的是欧拉序中 l~r 的一段 
int main()
{
	int T; scanf("%d",&T); //读入数据组数 
	while(T--)
	{
		scanf("%d%lld%lld",&n,&l,&r);
		long long id=1; //计算 l 所处的行 
		for(id=1;id<=n-1;id++)
			if(id*(2ll*n-id-1)>=l) //前 id 行的点数 >=l （一定要取等） 
				break;
		long long cnt=(id-1)*(2ll*n-(id-1)-1); //计算第 id 行之前共有多少个数 
		for(int i=id;i<=n-1;i++) //从当前行一直向后枚举 
			if(cnt>r) break; //欧拉序上 l 到 r 的所有点都已被输出 
			else
				for(int j=i+1;j<=n;j++) //一组一组枚举 
				{
					cnt++;
					if(cnt>r) break; //欧拉序上 l 到 r 的所有点都已被输出 
					if(cnt>=l&&cnt<=r) //是欧拉序上 l 到 r 上的点 
						printf("%d ",i); //就输出 
					cnt++;
					if(cnt>r) break;
					if(cnt>=l&&cnt<=r)
						printf("%d ",j);
				}
		if(r==1ll*n*(n-1)+1) printf("1"); //特判 r=n(n-1)+1 的情况，要用 1ll 
		printf("\n");
	}
	return 0;
}
~~~

[AC记录](https://codeforces.com/problemset/submission/1334/174743551)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正

---

## 作者：Scrolling_Ball (赞：2)

题意非常的简洁明了，这里我就不赘述了。

因为要求的是完全图的 **字典序最小** 的欧拉回路，所以就每次尽量往小的节点走。

这里讨论一下 $n$ 为 $5$ 的情况。

[![pCi8lIe.png](https://s1.ax1x.com/2023/06/06/pCi8lIe.png)](https://imgse.com/i/pCi8lIe)

~~是一个很好看的五角星。~~

正在我想怎么走的时候，我的建边顺序给了我启发：

[![pCi8sRs.png](https://s1.ax1x.com/2023/06/06/pCi8sRs.png)](https://imgse.com/i/pCi8sRs)

那字典序最小不就是这么走的吗？

```cpp
//暴力代码
for(int i = 1; i <= n; i ++ )
	for(int j = i + 1; j <= n; j ++ )
    		printf("%d %d\n", i, j);
```

然后很显然我们不能先暴力把图打出来，再把 $l\sim r$ 那一段取出来。

于是我们就要找规律，把上面那些边按出发点分个组。

```
1 2 1 3 1 4 1 5
2 3 2 4 2 5
3 4 3 5
4 5
```

我们容易发现对于每个数 $i$，它所占领的那个组里面有 $2\times (n-i)$ 个数（因为它只能往后面走）。

然后呢奇数位上就是出发点，偶数位上是从 $i+1$ 递增到 $n$。

接着就可以用暴力寻找 $l\sim r$ 的那一段啦（其实不用暴力，~~只是我懒得~~）。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t, n, l, r;
int main()
{
	scanf("%lld", &t);
	while(t -- )
	{
		scanf("%lld%lld%lld", &n, &l, &r);
		ll fi = 0, se = 0;
		for(ll i = n - 1; i >= 1; i -- )//枚举的不是出发点，而是每组个数。
		{
			fi = se + 1;
			se += i * 2;
//			cout << fi << " " << se << endl;
			if(se >= l)
			{
				for(ll j = max(l, fi); j <= min(se, r); j ++ )
					if(j & 1)printf("%lld ", n - i);//如果是奇数位，那就是所在的组的出发点。
					else printf("%lld ", (j + 1 - fi) / 2 + n - i);
			}
			if(se >= r)break;
		}
		if(r == (n - 1) * n + 1)printf("1 ");//这里要特判最后一个点，毕竟是回路，还是要回去的。
		puts("");
	}
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：2)

考虑规律 , 通过简单的贪心或者打表可以得到  

$n : 1\space 2\space 1\space 3\space 1\space 4\space ...\space 1\space n\space 2\space 3\space 2\space 4\space ...\space 2\space n\space 3\space 4\space 3\space 5\space ...\space 3\space n\space ...\space ...\space n-1\space n\space 1$  

关键在于如何确定 $[l, r]$ 内的序列 , 换言之 , 给定下标 $i$ , 求出在序列中对应的值。  

撇开最后一个 $1$ 不谈。

考虑奇数位 , 有 $n-1$ 个 $1$  , $n-2$ 个 $2$ , $...$  , $1$ 个 $n-1$ 。  

考虑偶数位 , 有 $ 2\space 3\space 4\space 5\space ...\space n\space 3\space 4\space 5\space ...\space n\space 4\space 5\space ...\space n\space ...\space ...\space n-1\space n$ 注意到每一组的长度也为 $n-1\space n-2\space ...\space 1$ 。  

因此预处理数列 $n-1\space n-2\space ...\space 1$ 的前缀和 , 用原下标在奇数/偶数数列中对应的下标在该数列中二分查找即可定位。  
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define rz resize

using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, maxn = 123456;
const ll linf = 0x3f3f3f3f3f3f3f3f;

ll a[maxn], b[maxn];

ll tobound(ll l, ll r, ll key) {
	while(l < r) {
		int mid = (l + r) >> 1;
		if(a[mid] >= key) r = mid;
		else l = mid + 1;	
	}
	return l;
}

ll gen(ll n, ll idx) {
	if(idx == n*(n-1) + 1) return 1;
	if(idx % 2 == 1) {
		idx = idx / 2 + 1;
		return tobound(1, n - 1, idx);
	} else {
		idx /= 2;
		int blk = tobound(0, n - 1, idx);
		idx -= a[blk-1];
		return n - (a[blk] - a[blk-1]) + idx;
	}
}
int main() {
	int tests;
	cin>>tests;
	while(tests--) {
		ll n, l, r;
		cin >> n >> l >> r;
		rep(i,1,n) a[i] = n - i, a[i] += a[i-1];
		for(ll i = l; i <= r; ++i) {
			cout << gen(n, i) << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

手推几个情况，发现答案是这样的（比如 $n=4$）

$1,2,1,3,1,4,2,3,2,4,3,4,1$

是由一系列连续的二元组组成的，最后末尾跟个 $1$。

我们可以算出 $l$ 这个位置当前处在哪个二元组里，往后推 $r-l+1$ 步即可。

自认为代码写的挺简单，可以看看注释。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,l,r;
inline void work(re int x,re int y,re int z,re int len){//在(x,y)这个二元组中，当前位置是 z，还要走 len 步。
	if(len==0)return;
	if(x==n){printf("1 ");return;}
	printf("%lld ",z);
	if(z==x){work(x,y,y,len-1);return;}
	if(z==y){
		if(y!=n)work(x,y+1,x,len-1);
		else work(x+1,x+2,x+1,len-1);
	}
}
signed main(){
	t=read();
	while(t--){
		n=read();l=read()-1;r=read()-1;re int sum=0,ans=0,tot;
		for(re int i=n;i;--i){
			if(i!=1)
			sum+=2*i-2;
			else sum+=1;
			if(sum>l){
			//	printf("%lld %lld\n",i,sum);
			if(i!=1)
				sum-=2*i-2;else ++sum;
				ans=n-i+1;
				break;
			}
		}tot=ans+1;//这里是找二元组中第一个的位置
		for(re int i=2;i<=l-sum;i+=2)++tot;//这是第二个
		if((l-sum)&1){work(ans,tot,tot,r-l+1);}
		else work(ans,tot,ans,r-l+1);putchar('\n');
	}
}
```


---

## 作者：AutumnKite (赞：2)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

看到完全图，欧拉回路，以及字典序最小，一个很自然的想法是从 $1$ 开始，每次走能走的最小的那个点。

模拟发现，这样走一定能恰好走出一条欧拉回路，顶点序列如下：
$$1,2,1,3,\cdots,1,n,2,3,2,4,\cdots,2,n,3,4,\cdots,n,n-1,n,1$$

我们可以将这个序列分成若干组，可以更直观的看出规律：
$$
\begin{aligned}
& 1,2,1,3,\cdots,1,n \\
& 2,3,2,4,\cdots,2,n \\
& 3,4,3,5,\cdots,3,n \\
& \vdots \\
& n-2,n-1,n-2,n \\
& n-1,n \\
& 1
\end{aligned}
$$

于是我们求出 $l,r$ 在第几组中的第几个，直接模拟即可。

注意需要特判最后的 $1$。

### 代码

```cpp
const int N = 100005;

int n;
long long l, r;

std::pair<int, int> get(long long l) {
	int p = 1;
	while (p < n && l > 2 * (n - p)) {
		l -= 2 * (n - p);
		++p;
	}
	return {p, l};
}

void solve() {
	read(n), read(l), read(r);
	bool flag = 0;
	if (r == 1ll * n * (n - 1) + 1) {
		if (l == r) {
			print(1);
			return;
		}
		flag = 1, --r;
	}
	std::pair<int, int> L = get(l), R = get(r);
	for (int k = L.first; k <= R.first; ++k) {
		int lb = k == L.first ? L.second : 1;
		int rb = k == R.first ? R.second : 2 * (n - k);
		for (int i = lb; i <= rb; ++i) {
			if (i & 1) {
				print(k, ' ');
			} else {
				print(k + i / 2, ' ');
			}
		}
	}
	if (flag) {
		print(1);
	} else {
		putchar('\n');
	}
}
```

---

## 作者：dead_X (赞：1)

## 题意简述
求一个一个有 $n$ 个点的完全图(即 $\forall i\neq j,1\leq i,j\leq n$ 间都有连边)的最短字典序遍历中第 $l$ 到 $r$ 个点。
## 思路简述
首先我们打表出 $n$ 比较小的时候的遍历。

$$n=2:1\to2 \to 1$$
$$n=3:1\to2\to1\to3\to2\to3\to1$$
$$n=4:1\to2\to1\to3\to 1\to4\to2\to3\to2\to4\to3\to4\to1$$

发现了什么?

$n=k:$

$\to1\to2\to1\to3\to1\to\cdots\to1\to k$

$\to2\to3\to2\to4\to\cdots\to2\to k$

$\to\cdots\to\cdots$

$\to k-1\to k$

$\to1$

$Proof:$

几乎显然。每一步都是在能保证能走成回路的目标点间选择编号最小的点。

那么打出代码就是显然的了，先算好第 $l$ 步的结果，然后依次向后递推即可。
## 代码实现
```
#include<bits/stdc++.h>
#define ll long long
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
long long n;
void nxt(int&x,int&y){if(y!=n) ++y;else {++x;y=x+1;}if(x==n) x=1;}
void cnt(ll m,int&x,int&y)
{
	if(m>n*(n-1)/2) {x=1;y=1;return;}
	ll a=0,b=0;
	while(a<m) {a+=n-1-b;++b;}
	a-=n-b;
	x=b;y=m-a+b;
}
signed main()
{
	int T=read();
	while(T--)
	{
		n=readll();
		long long l=read(),r=read(),x,y;
		cnt((l+1)/2,x,y);
		for(int t=l; t<=r; t++) if(t%2) printf("%lld ",x);else printf("%lld ",y),nxt(x,y);
		puts("");
	}
	return 0;
}
 
```

---

## 作者：kimi0705 (赞：0)

### 前言
本人比较弱，懒得推式子，所以使用无脑二分。

### 题解：CF1334D Minimum Euler Cycle
关键词：找规律。

首先多枚举一下就可以找出规律。因为字典序最小，肯定要用能到达的最小点。

$$ n:\\1~2~1~3 \cdots1~n\\2~3~2~4\cdots2~n\\3~4~3~5\cdots3~n\\\cdots~\cdots\\n−1~n\\1$$。

所以开始无脑二分。对应每一个位置查询一次，用 $O(\log N)$ 的时间。

对于每一次查询，先求出其所在的行，再判断奇偶性。

```cpp
// 1213141516 23242526 343536 4546 56 1
// 2(n-1)     2(n-2)   2(n-3) 2(n-4) 2(n-5) 1
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, l, r;
int calc (int n, int d) { return (n - 1 + n - d) * d; } // calc (6, 3) = 8 * 3
int check (int n, int x, int d) {
    if (calc(n, d - 1) >= x) return 1;
    if (calc(n, d) < x) return -1;
    return 0;
}
void query (int x) {
    if (x == n * (n - 1) + 1) return cout << "1", void();
    int l = 1, r = n - 1, d;
    while (l <= r) {
        int mid = (l + r) >> 1, c = check (n, x, mid);
        if (c == 0) {
            d = mid;
            break;
        } else if (c == 1) r = mid - 1;
        else l = mid + 1;
    }
    x -= calc(n, d - 1);
    if (x & 1) return cout << d << ' ', void();
    return cout << x / 2 + d << ' ', void();
}
signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> l >> r;
        for (int i = l; i <= r; i++) query(i);
        cout << '\n';
    }
}
```

---

