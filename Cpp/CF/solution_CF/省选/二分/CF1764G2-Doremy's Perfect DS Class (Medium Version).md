# Doremy's Perfect DS Class (Medium Version)

## 题目描述

The only difference between this problem and the other two versions is the maximum number of queries. In this version, you are allowed to ask at most $ \mathbf{25} $ queries. You can make hacks only if all versions of the problem are solved.

This is an interactive problem.

"Everybody! Doremy's Perfect Data Structure Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's Data Structure class, Doremy is teaching everyone a powerful data structure — Doremy tree! Now she gives you a quiz to prove that you are paying attention in class.

Given an array $ a $ of length $ m $ , Doremy tree supports the query $ Q(l,r,k) $ , where $ 1 \leq l \leq r \leq m $ and $ 1 \leq k \leq m $ , which returns the number of distinct integers in the array $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ .

Doremy has a secret permutation $ p $ of integers from $ 1 $ to $ n $ . You can make queries, in one query, you give $ 3 $ integers $ l,r,k $ ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ ) and receive the value of $ Q(l,r,k) $ for the array $ p $ . Can you find the index $ y $ ( $ 1 \leq y \leq n $ ) such that $ p_y=1 $ in at most $ \mathbf{25} $ queries?

Note that the permutation $ p $ is fixed before any queries are made.

## 说明/提示

The permutation in the example is $ [3,5,2,1,4] $ .

The input and output for example illustrate possible interaction on that test (empty lines are inserted only for clarity).

In this interaction process:

- For the first query, $ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $ , so the answer is $ 2 $ .
- For the second query, $ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $ , so the answer is still $ 2 $ .
- For the third query, $ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $ , so the answer is $ 1 $ .
- For the fourth query, $ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $ , so the answer is $ 3 $ .

The correct answer is got after $ 4 $ queries, so this process will be judged correct.

## 样例 #1

### 输入

```
5

2

2

1

3```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4```

# 题解

## 作者：Dream_poetry (赞：1)

### 思路：
首先令 $k = 2$，然后如果 $n$ 是奇数，显然此时只有 $1$ 自己一个人一组。

显而易见的，我们可以对于每个位置 $i$，查询 $[1, i − 1]$ 和 $[1, i]$ 的答案，如果答案一样，那这个位置肯定不是 $1$。

如果不一样，我们再查一下 $[i, n]$ 和 $[i + 1, n]$。由于 $1$ 不会和左右任意一个人配对，不难发现如果这两种情况都不一样，那这里一定是 $1$，这样我们就做到了 $2n − 2$ 次查询。

#### 进行优化。

如果我们查询一个区间 $[l, r]$，那么得到的答案自然是 $len-$ 配对数字都在区间内的对数，因此我们自然也能得到这个区间的未配对数。

这个时候发现，对于第 $i$ 个位置，如果我们查询 $[1, i]$ 和 $[i + 1, n]$，由于这两个区间内没配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中，未配对数多的那个一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

太棒了，所以然后呢？


#### 再考虑 $n$ 是偶数的情况。

这个时候 $1$ 和 $n$ 都没人配对，我们需要找到 $n$ 并将它去掉。

注意到 $k$ 可以取别的数，我们如果只是让 $k = 2$ 未免有些弱，而且看上去也区分不了 $1$ 和 $n$，而不难发现，令 $k = n$ 就可以找到 $n$ 在哪里，于是可以先找 $n$ 再找 $1$，需要 $40$ 步。

显然无法接受。

#### 再优化。

令 $k = 2$，查询 $[1, i]$ 和 $[i + 1, n]$，发现此时会有两种情况: 

1. 左右两边未配对数量相差 $2$，这个时候 $1$ 和 $n$ 一定都在较大的那边，直接递归处理。

2. 左右两边未配对数量相等，这个时候一定 $1$ 在一边，$n$ 在另一边，可以通过查询 $k = n$ 判断哪边是 n。

所以只需要 $21$ 次，足以通过此题了。

假如还要通过 G3，我们就需要解决一点问题，但这里毕竟只是 G2，所以具体过程就不赘述了。

不过还是给出可以通过 G3 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
int n;

int l,r;
int ans;
int flag;

inline int ask(int l,int r,int k){
	printf("? %lld %lld %lld\n",l,r,k),
	fflush(stdout);
	int x;
	cin>>x;
	return x;
}
int g[500005];
int f[500005];

int query(int l,int r){
	return (ask(l,r,2)<<1)-(r-l+1);
}

signed main(){
	cin>>n;
	l=1;
	r=n-1;
	ans=n;
	flag=-1;
	if (n%2) g[1]=f[n]=1;
	else g[1]=f[n]=2;
	
	while (l<=r){
		int mid=(l+r)>>1;
		if (l==r){
			if (flag==-1 && (!(n%2))){
				if (mid==1){
					if (ask(mid+1,n,n)!=1){
						ans=l;
					}			
				}
				else{
					if (ask(1,mid,n)==1){
						ans=l;
					}
				}
				break;
			}
			else if (g[l]-g[l+2]){
				if (query(1,l)>f[l-1]){
					ans=l;
				}
			}
			else{
				if (query(l+1,n)<g[l+2]){
					ans=l;
				}
			}
			break;
		}	
		f[mid]=query(1,mid);
		g[mid+1]=query(mid+1,n);
		int val=f[mid]-g[mid+1];
		if (val>0){
			ans=mid;
			r=mid-1;
		}
		else if (val<0){
			l=mid+1;
		}
		else{
			if (flag==-1){
				if (mid==1) flag=(ask(mid+1,n,n)==1);
				else flag=ask(1,mid,n)-1;
			}
			if (flag){
				l=mid+1;
			}
			else{
				ans=mid;
				r=mid-1;
			}
		}
	}
	printf("! %lld",ans);
	return 0;
}
```

---

## 作者：FLAMEs_ (赞：1)

做了半天的交互题，感觉做完之后整个人升华了。

前言：这类题目似乎需要很好的“和出题人对上脑电波”，不然什么也想不到。而且，遇到这类向下取整相关的题目时，应当考虑 $k = 2$ 或者 $k = n$ 的情况，从这种特殊情况为突破口去思考题目。

以下用 $Q(l,r,k)$ 表示向交互库发起一组形如 ```? l r k``` 的询问。

[戳我看 G1 题解](https://www.luogu.com.cn/blog/gggggggghost/CF1764G1)

## G2 做法

**请保证你会了 G1 的做法。**

本题的次数限制为 $25$ 次，我认为是最诈骗的一点。

考虑优化过程。我们发现 $Q(l,r,2)$ 这样的询问不太好优化。但是，$n$ 和 $1$ 所在的位置是不变的。

这时，我们发现，当二分到 $Q(1,mid,2)=Q(mid+1,n,2)$ 的情况时，我们不知道 $1$ 和 $n$ 分别在哪一侧。我们用一组询问问出 $n$ 与 $1$ 的相对位置之后，便不必再问。

简略证明：考虑二分的过程一定是缩短区间的过程，以前所二分过并且被丢弃的区间必定不会再被经过。所以，$1$ 和 $n$ 的相对位置一定不会变。

然后，用 $2\log n=20$ 次便可以得出答案。总次数为 $21$ 次，可以通过 G2。

为什么这么诈骗。$25$ 次的限制我想了好久也没想到可以限制的更紧。/fn

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, L, R, Ans, Npos;
int Ask(int L, int R, int p) {
	cout << "? " << L << " " << R << " " << p << endl;
	int x; cin >> x; return x;
}
int main() {
	cin >> n;
	if(n & 1) {
		L = 1, R = n;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(mid == n) {
				Ans = n;
				break;
			}
			int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid;
			int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid);
			if(Lval < Rval) L = mid + 1;
			else R = mid - 1, Ans = mid;
		}
		cout << "! " << Ans;
		return 0;
	}
	L = 1, R = n;
	int flag = -1;
	while(L <= R) {
		int mid = (L + R) >> 1;
		if(mid == n) {
			Ans = n;
			break;
		}
		int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid;
		int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid);
		if(Lval == Rval + 2) R = mid - 1, Ans = mid;
		else if(Lval + 2 == Rval) L = mid + 1;
		else {
			if(flag == -1) {
				if(Ans == 2) {
					int Nval = Ask(2, 3, n);
					if(Nval == 2) Ans = 1;
					else Ans = 2;
					break;
				} 
				int Nval = Ask(1, mid, n);
				if(Nval == 2) flag = 0;
				else flag = 1;
			}
			if(flag == 0) L = mid + 1;
			else R = mid - 1, Ans = mid;
		}
	}
	cout << "! " << Ans;
	return 0;
}
```

[戳我看 G3 题解](https://www.luogu.com.cn/blog/gggggggghost/CF1764G3)

---

## 作者：james1BadCreeper (赞：1)

询问能告诉我们什么？好奇怪啊，不知道。尝试从给定的 $k$ 值开始分析。$k=1$ 没什么意义，然后尝试从特殊的，比如 $k=2,n$ 开始分析。$k=n$ 比较好说，只有 $n$ 可以被记入答案，可以根据此找出 $n$ 的位置。$k=2$ 则可以将数分为两组，在 $n$ 为奇数时只有 $1$ 是单独一组，$n$ 为偶数时只有 $1,n$ 是单独一组。

从别的地方再想一想，都要求 $\log$ 级别的询问，不难想到二分。设 `solve(l, r)` 代表答案在 $[l,r]$ 的位置中，我们需要确定 $1$ 在 $[l,mid]$ 还是 $[mid+1,r]$ 里。咦，感觉不太对，不是严格的子问题！但是我们只需要寻找答案在哪里，因此只需要分别答案在 $[1,mid]$ 还是 $[mid+1,n]$ 就好了。

选择从 $k=2$ 入手，$x,y$ 分为一组仅当它们除以二下取整后的值相等。我们可以求出两个区间中在自己区间内没有匹配的数的数量，然后这个数量大的，答案就在哪里（因为剩下的每有一个都是成对的）。

$n$ 是偶数怎么办呢？我们只需要找到 $n$ 就行，不难发现 $k=n$ 可以很好的完成这个任务。当两个区间的值相等时，说明 $1,n$ 各占一个，我们令 $k=n$，询问其中一个，看 $n$ 是否在其中。找到 $n$ 的位置之后发现之后的递归不会受到影响（如果 $p_n> mid$，我们会递归到 $[l,mid]$，必定有 $p_n>mid'$）。

这样我们将询问次数控制在了 $2\log n+1$，可以通过 G2。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, flag; 
int query(int l, int r, int k) {
	if (l > r) return 0; 
	if (l == r) return 1; 
	if (l == 1 && r == n) return n / k + 1; 
	cout << "? " << l << " " << r << " " << k << endl; 
	int ans; cin >> ans; return ans; 
}

int solve(int l, int r) {
	if (l == r) return l; 
	int mid = l + r >> 1; 
	int L = 2 * (query(1, mid, 2)) - mid; 
	int R = 2 * (query(mid + 1, n, 2)) - (n - mid); 
	if (n % 2 == 0) {
		if (!flag) {
			if (L == R) {
				bool con = 0; 
				if (mid == 1 && query(mid + 1, n, n) == 1) con = 1; 
				if (mid > 1 && query(1, mid, n) == 2) con = 1; 
				if (con) flag = 1, --L; 
				else flag = -1, --R; 
			}
		} else {
			if (flag == 1) --L; 
			else --R; 
		}
	}
	return L > R ? solve(l, mid) : solve(mid + 1, r); 
}

int main(void) {
	ios::sync_with_stdio(0); 
	cin >> n; int ans = solve(1, n); 
	cout << "! " << ans << endl; 
	return 0; 
}
```

---

## 作者：honglan0301 (赞：1)

如果还不会做 G1 题，可以先去看 [CF1764G1 题解](https://www.luogu.com.cn/blog/529697/solution-cf1764g1) qwq。

## 题目分析
通过 G1 题，我们不难发现需要优化 $n$ 为偶数时的做法。之前的做法里，我们每次碰到两段未配对数相等时就要进行一次 $k=n$ 的询问，而这些询问是没什么必要的。  

注意到在二分的过程中，只要进行了一次 $k=n$ 的询问，之后 $1$ 和 $n$ 的相对位置就已经固定下来了（不可能发生左右的颠倒），于是可以在第一次询问 $n$ 后就记录下它们的位置关系，这个优化可以使询问次数降低到 $2\times \log(1024)+1=21$ 次，可以通过本题。  

## 代码
```cpp
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#include <stdlib.h>
using namespace std;
int n,flag;
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int ask(int l,int r,int k)
{
	printf("? %d %d %d\n",l,r,k);
	fflush(stdout);
	return read();
}
void putans(int x)
{
	printf("! %d\n",x);
	fflush(stdout);
}
bool check1(int x)
{
	int a=ask(1,x,2);
	int b=0;
	if(x+1<=n)
	{
		b=ask(x+1,n,2);
	}
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	return 0;
}
void solve1()//n为奇数
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check1(mid))
		{
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
bool check2(int x)
{
	int a=ask(1,x,2);
	int b=ask(x+1,n,2);
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	else if(c<d)
	{
		return 0;
	}
	else
	{
		if(!flag)//flag表示n在1的左侧/右侧，当这个关系确定之后就不用再问了
		{
			int e=0;
			if(x>1)//放在出现ask(1,1,n)的无效情况 
			{
				e=ask(1,x,n);
			}
			else
			{
				e=3-ask(x+1,n,n);
			}
			if(e==2)
			{
				flag=1;
				return 0;
			}
			else
			{
				flag=2;
				return 1;
			}
		}
		else if(flag==1)
		{
			return 0;
		}
		else if(flag==2)
		{
			return 1;
		}
	}
}
void solve2()//n为偶数
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check2(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
int main()
{
	n=read();
	if(n%2==1)
	{
		solve1();
	}
	else
	{
		solve2();
	}
}
```

---

## 作者：OoXiao_QioO (赞：0)

在下文，我们令“两个数配对”表示这两个数相等。不直接用“两个数相等”是因为可能有歧义，需要读者自己注意。

不难发现这个下取整对于 $n$ 的奇偶性有影响，所以我们要分类讨论。

* 若 $n$ 是奇数

第一反应是令 $k=2$。此时只有 $1$ 自己是一组，其他连续两个数都是同一个值。

那么我们可以对于每个位置 $i$，查询 $[1,i-1]$ 和 $[1,i]$ 的答案。如果这两个区间答案一样，那么这个位置肯定不是 $1$；如果不一样，再查询 $[i,n]$ 和 $[i+1,n]$。因为 $1$ 不会和左右任意一个数配对，因此若这两种情况都不一样，那么这个位置肯定就是 $1$，此时询问次数就是 $2n-2$ 次。

考虑优化，若查询一个区间 $[l,r]$，那么答案数就是 $len-x$，其中 $x$ 是配对数字都在区间内的对数。所以我们也能得出这个区间的未配对数。

更进一步地，发现对于位置 $i$，如果查询 $[1,i]$ 和 $[i+1,n]$，由于这两个区间内未配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中未配对数多的那个区间一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

* 若 $n$ 是偶数

此时 $1$ 和 $n$ 都没有点可以配对，那么我们需要找到 $n$ 并把他消除掉，那么找 $1$ 就变得简单了。

注意到 $k$ 可以取除了 $2$ 的数，通过手玩样例发现，令 $k=n$ 可以找到 $n$ 在那里，那么可以先找到 $n$ 再找 $1$，此时需要 $40$ 步。也就是找两次 $20$ 步。

可是若 $k$ 一直取 $n$，优化的前景不大，那么继续考虑 $k$ 的取值。

继续优化，还是令 $k=2$，查询 $[1,i]$ 和 $[i+1,n]$，我们发现此时有两种情况：

1. 左右两边未配对的数量相差 $2$，这时候 $1$ 和 $n$ 一定都在较大的那边，直接递归求解即可。

2. 左右两边未配对数量相等，此时肯定 $1$ 和 $n$ 各在一边，再查询一次 $k=n$，就知道了 $n$ 再哪里。

至于为什么有这两种情况请读着自己思考。



---



奇偶两种情况结合一下即可。

---

## 作者：M1saka16I72 (赞：0)

# [CF1764G2 Doremy's Perfect DS Class (Medium Version)](http://codeforces.com/problemset/problem/1764/G2) 题解

## 前言
[更可爱的阅读体验](https://misaka16172.github.io/solution-CF1764G2)

## 思路

前置芝士：CF1764G1 的解法。

考虑在 G1 的基础上进行一个小小的优化。

G1 的最大询问次数是 $3\log n$，其瓶颈在于当 $n$ 为偶数时，我们需要预先额外花费 $\log n$ 的时间去找到 $n$ 的位置，从而消除后续询问里 $n$ 的影响，因为这时 $n$ 与 $1$ 一样都具有除以 $2$ 向下取整的结果唯一的性质。

而 G2 把最大询问次数限制到了 $25$ 次，所以我们需要找一种更高效的辨别 $n$ 和 $1$ 的方式来代替预先询问。

当我们对 $[1,k]$ 和 $[k+1,n]$ 两个区间进行询问时，除了 $1$ 和 $n$ 之外，两个区间里无法配对数字的数量一定是相等的，那我们可以分类讨论 $1$ 和 $n$ 的位置：
 - 当 $1$ 和 $n$ 在同一个区间里时，这个区间里未配对的数字个数会比另一边大 $2$，于是继续处理这个区间就好。
 - 当 $1$ 和 $n$ 分居在两个区间里时，两个区间里未配对的数字个数相等，我们只需要对其中一个区间进行一次 $?\ l\ r\ n$ 的询问，如果得到的结果是 $2$ 那就证明 $1$ 不在这个区间里，反之则证明 $1$ 在另一个区间里，于是我们就可以记录下 $n$ 所在区间，继续对有 $1$ 的区间进行询问。

进行这个优化之后，我们就可以把询问次数降低到 $2\log n+1$，其中这 $1$ 次询问就是用来帮助我们辨别 $n$ 的询问，可以通过此题。

代码：[link](https://codeforces.com/contest/1764/submission/248429804)。

---

## 作者：樱雪喵 (赞：0)

## G1

考虑 $1$ 和其他的数有什么不同点。我们令询问的 $k=2$，那么只有 $1$ 的值是 $0$，其余都不是。这看起来并没有什么用，因为我们只能知道不同的数的个数。

但是真的没有用吗？可以发现，若 $k=2$，则所有数下取整后是两两配对的，$\lfloor\frac{2}{2}\rfloor=\lfloor\frac{3}{2}\rfloor,\lfloor\frac{4}{2}\rfloor=\lfloor\frac{5}{2}\rfloor,\dots$。当 $n$ 为奇数时，只有 $1$ 是单出来的；$n$ 为偶数时，$1$ 和 $n$ 两个数都是单出来的。

先考虑奇数的情况怎么做。

对于一个区间 $[l,r]$，若 $\text{query}(l,r,2)=x$，可以得到 $[l,r]$ 中有 $2x-(r-l+1)$ 个数字没有被配对。所以假设我们找了一个分界点 $mid$，并求出 $[1,mid]$ 中有 $L$ 个没配对，$[mid+1,n]$ 中有 $R$ 个没配对。那么如果同一组的数分到了一边一个，它们可以互相消掉，只有 $1$ 是无论如何都无法被配对的。

这就是说，若 $L<R$，$1$ 就在 $[mid+1,n]$ 中；否则 $1$ 在 $[1,mid]$ 中。那么我们可以二分这个 $mid$ 的位置，求出答案，询问次数 $2\log n\le 20$。

再考虑 $n$ 是偶数的情况。

现在，我们同样询问得到了 $L$ 和 $R$ 的值。分类讨论 $1$ 和 $n$ 的位置情况：

- 如果都在左侧，应该是 $L=R+2$；
- 如果都在右侧，应该是 $R=L+2$；
- 如果一左一右，$L=R$。

发现在一左一右的情况下，我们没法判断哪一边是 $1$。

但仔细思考一下，发现 $n$ 的位置是好找的：令 $k=n$，这样只有 $n$ 的答案是 $1$，其他都是 $0$。因此可以在一开始先二分找出 $n$ 的位置，就能知道 $L=R$ 时 $1$ 在哪边了。

找 $n$ 的位置只需要询问一边，所以总询问次数是 $3\log n\le 30$。

## G2

发现找 $1$ 的位置的过程是不好优化的，现在的询问次数瓶颈在找 $n$ 的位置。

实际上，我们只关心 $n$ 在 $mid$ 的哪一侧，而不关心它的具体位置。可以这样优化：

- 当第一次出现 $L=R$ 的情况时，我们通过一次 $\text{query}(1,mid,n)$ 判断 $n$ 在 $mid$ 的哪一侧。
- 当再次出现这个情况时，发现有一条性质：如果之前判断过 $n$ 在 $mid$ 的右侧，我们的二分区间只会往左不会往右，也就是说以后 $n$ 永远在 $mid$ 的右侧，反之同理。

因此，在第一次判断时记录 $n$ 在 $mid$ 的哪一侧，以后不需要再次判断。总询问次数为 $2\log n+1\le 21$。

```cpp
const int N=2005;
int n,L[N],R[N];
il int ask(int l,int r,int k)
{
    cout<<"? "<<l<<" "<<r<<" "<<k<<endl;
    int x=read();
    if(k==2) {if(l==1) L[r]=2*x-(r-l+1); if(r==n) R[l]=2*x-(r-l+1);}
    return x;
}
bool flag,pos;
int main()
{
    n=read();
    int l=1,r=n;
    while(l<r)
    {
        int mid=(l+r)>>1;
        ask(1,mid,2),ask(mid+1,n,2);
        if(L[mid]>R[mid+1]) r=mid;
        else if(L[mid]<R[mid+1]) l=mid+1;
        else 
        {
            if(!flag) 
            {
                if(mid>1) pos=(ask(1,mid,n)>1);
                else pos=(ask(mid+1,n,n)==1);
                flag=1;
            }
            if(pos) l=mid+1; else r=mid;
        }
    }
    cout<<"! "<<l<<endl;
    return 0;
}
```

---

## 作者：Iam1789 (赞：0)

一文三投，赢！

完整文章：[Link](https://www.luogu.com.cn/blog/Iam1789/solution-cf1764g)
## 正文
先考虑 $n$ 为奇数，考虑 $k=2$ 时，按 $\lfloor \frac{a}{k} \rfloor$ 的值将 $1$ 到 $n$ 分组，则有大漂亮性质：$1$ 所在的组大小为 $1$，其它组大小皆为 $2$。

考虑判断 $1$ 的位置 $y$ 是否 $\leq \text{mid}$。对于所有大小为 $2$ 的组，设其两个元素的位置全 $\leq \text{mid}$ 的有 $x$ 对，全 $> \text{mid}$ 的有 $y$ 对，剩下的有 $z$ 对。询问 $(1,\text{mid},2)$ 和 $(\text{mid}+1,r,2)$，设结果分别为 $b,c$，有如下方程组：

$$ \begin{cases}  x+y+z=\lfloor\frac{n}{2} \rfloor+1\ \\x+z=b \\ y+z=c\end{cases}$$

方程组足以解出 $x,y,z$。

$a_1,\cdots,a_{\text{mid}}$ 中有 $2x+z$ 个不为 $1$ 的元素，如果 $2x+z=\text{mid}$，则 $1$ 的位置 $>\text{mid}$，否则 $\leq \text{mid}$。

考虑二分 $\text{mid}$，最劣询问次数为 $2\lceil\log n\rceil$。

接着考虑 $n$ 为偶数。与 $n$ 为奇数不同的是，除了 $1$ 之外，$n$ 所在的组大小为 $1$。因此在判断的时候，可能同时出现 $2x+z\neq \text{mid}$ 和 $2y+z \neq n-\text{mid}$ 的情况。此时 $1$ 与 $n$ 分别在 $\text{mid}$ 的两边。如何判断哪边是 $n$ 呢？如果 $\text{mid} >1$，我们询问 $(1,\text{mid},n)$，否则询问 $(\text{mid}+1,n,n)$。如果结果为 $2$，则说明 $n$ 在对应区域，将其排除。最劣情况下询问次数为 $3\lceil\log n\rceil$，当 $n=1024$ 时为 $30$ 次，可以通过第一个子任务。

考虑第一次遇到上述情况后，我们便知道了 $1$ 相对于 $n$ 是在左边还是在右边，记录下来，后面无需再问，最劣询问次数降低为 $2\lceil\log n \rceil +1$，当 $n=1024$ 时为 $21$ 次，可以通过第二个子任务，但是第三个子任务恰好被卡了 $1$ 次/oh

---

## 作者：OtoriEmu (赞：0)

因为自己思考的时候没有独立做出 G3，所以只写 G2 的题解。

事实上这场 E 浪费太多时间去考虑 corner case 了，能早点看到这题就可以上分了。

---

简单观察范围，G1 的范围是 $3\log n$ 次，G2 的范围是 $2\log n+1$ 次询问。

为什么非要我们找 $1$ 不可呢？事实上向下取整是一个很好的提示。一个直观的想法是每次查询，$k=2$。这个想法的来源在哪儿呢？首先 $k=1$ 的查询显然是浪费，同时发现 $k \geq 2$ 的时候 $\lfloor \frac{1}{k} \rfloor = 0$。如果 $\lfloor \frac{c}{k} \rfloor = 0$ 的 $c$ 可以唯一确定就很不错了，此时 $k=2$（不考虑采取 $k$ 更大的分治结构是因为如果为 $\lfloor \frac{c}{k} \rfloor = 0$ 太多，区分他们的成本太大，并且我们仍然需要 $k$ 更小的询问）。

此时可以按 $\lfloor \frac{c}{2} \rfloor$ 分类。容易发现一类的大小要么是 $2$ 要么是 $1$，并且类与类的区别只有大小的区别，我们只需要找到大小为 $1$ 的那类的位置。这里有一个对 G1 来说无关紧要的问题是，大小为 $1$ 的可能有两类（$0$ 和 $\frac{n}{2}$，此时 $n$ 为偶数）。对于 G1 来说可以先令 $k=n$，通过二分找到 $n$ 的位置并排除。

对于 G1 还剩下 $2 \log n$ 次询问。这是显然的一个二分的结构，每层二分查询两次。假设我们确定 $1$ 在区间 $[l,r]$ 内，对于中点 $p$，将序列分成大小为 $p$ 和 $n-p$ 的两段。在去除 $n$ 之后查询左右两边还没有配对的数的数量（当然这并不是查询的实际意义，当然算是比较简单的，令 $c$ 的值为 `query(l,r,2)` 的结果，则没配对的数的数量为 $2c-r+l-1$）。因为 $1$ 必然无法配对，所以没有配对的数更多的一半存在 $1$。这部分的查询次数为 $2 \log n$。

此时发现，一开始的二分的查询非常费次数。实际上在二分中，我们仍然可以优先向没配对的一半走。然后在某一层发现两边没配对的数量一样多，此时有一半存在 $1$，有一半存在 $n$。只需要令 $k=n$ 查询某一边是否存在 $n$ 就好，此后就可以顺带把 $n$ 删除。这样就可以把 $\log n$ 次询问缩减到 $1$ 次。

[提交记录](https://codeforces.com/problemset/submission/1764/183025730)。

---

