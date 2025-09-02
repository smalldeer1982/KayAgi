# Build Permutation

## 题目描述

A  $ \mathbf{0} $ -indexed array $ a $ of size $ n $ is called good if for all valid indices $ i $ ( $ 0 \le i \le n-1 $ ), $ a_i + i $ is a perfect square $ ^\dagger $ .

Given an integer $ n $ . Find a permutation $ ^\ddagger $ $ p $ of $ [0,1,2,\ldots,n-1] $ that is good or determine that no such permutation exists.

 $ ^\dagger $ An integer $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x = y^2 $ .

 $ ^\ddagger $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 说明/提示

In the first test case, we have $ n=3 $ . The array $ p = [1, 0, 2] $ is good since $ 1 + 0 = 1^2 $ , $ 0 + 1 = 1^2 $ , and $ 2 + 2 = 2^2 $

In the second test case, we have $ n=4 $ . The array $ p = [0, 3, 2, 1] $ is good since $ 0 + 0 = 0^2 $ , $ 3 + 1 = 2^2 $ , $ 2+2 = 2^2 $ , and $ 1+3 = 2^2 $ .

## 样例 #1

### 输入

```
3
3
4
7```

### 输出

```
1 0 2 
0 3 2 1 
1 0 2 6 5 4 3```

# 题解

## 作者：lizhous (赞：9)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1713C)

[CF传送门](https://codeforces.com/contest/1713/problem/C)

# CF1713C 题解
**一篇不用递归的题解！**
### 分析
题目中一个明显的突破口是“任意一个元素加上**其下标**”。下标是固定的，完全平方数也是固定的，我们可以把他们画成如下图（以样例第三测为例）。

![](https://cdn.luogu.com.cn/upload/image_hosting/bb0d9vve.png)

我们可以看见下标是等差数列，而我们也要用等差数列与它凑至一个完全平方数。一种贪心构造的方法是对于每个完全平方数，我们尽可能多的摆放数。正序枚举平方数会很难控制放置上界（可以大到任意平方数），所以我们考虑倒序。每次的上界是上次最后摆放的数的下一个数，下界就是当前完全平方数减去最大的下标。如果下界小于 $0$ 就无解。代码实现可以使用两个指针,具体见代码。
### 代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
#define int long long
int t, n, nt, a[1000001], r, l, w, ps[1001];
signed main() {
	for (int i = 1; i <= 1000; i++) {
		ps[i] = i * i; //提前打表出完全平方数
	}
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld", &n);
		nt = n - 1; //下标最大和数值最大到n-1
		nt *= 2; //理论最大结果，即最大两个数结合
		w = upper_bound(ps + 1, ps + 1000 + 1, nt) - ps; //因为之后有比较，所以用upper_bound找上一个完全平方数
		l = n; //左端点
		while (l > 0) { //循环左端点大于0
			r = l - 1; //右端点到上一左端点前
			while (l > r) { //让左端点到右端点前
				w--; //找下一个完全平方数
				l = ps[w] - r; //更新l
			}
			if (l < 0) { //如果小于0
				cout << -1; //输出无解
				return 0;
			}
			for (int i = r; i >= l; i--) { //倒序
				a[i] = (r - i) + l; //下标倒过来
			}
		}
		for (int i = 0; i < n; i++) {
			printf("%lld ", a[i]); //输出
		}
		cout << endl;
	}
}
```
~~好像不会无解~~
### END

---

## 作者：Jasper08 (赞：6)

这一道题一开始看起来有点令人无从下手，不妨先手算，从小的 $n$ 出发找规律。

| $n$ | $a_0$ | $a_1$ | $a_2$ | $a_3$ | $a_4$ | $a_5$ | $a_6$ | $a_7$ | $a_8$ | $a_9$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $0$ |  |  |  |  |  |  |  |  |
| $2$ | $1$ | $0$ |  |  |  |  |  |  |  |
| $3$ | $1$ | $0$ | $2$ |  |  |  |  |  |  |
| $4$ | $0$ | $3$ | $2$ | $1$ |  |  |  |  |  |
| $5$ | $4$ | $3$ | $2$ | $1$ | $0$|  |  |  |  |
| $6$ | $0$ | $3$ | $2$ | $1$ | $5$ | $4$ |  |  |  |
| $7$ | $1$ | $0$ | $2$ | $6$ | $5$ | $4$ | $3$ |  |  |
| $8$ | $1$ | $0$ | $7$ | $6$ | $5$ | $4$ | $3$ | $2$ |  |
| $9$ | $0$ | $8$ | $7$ | $6$ | $5$ | $4$ | $3$ | $2$ | $1$ |
| $10$| $9$ | $8$ | $7$ | $6$ | $5$ | $4$ | $3$ | $2$ | $1$ | $0$ |

发现什么了吗？

最显然地，若 $n$ 为完全平方数 $+1$，那么 $a$ 为一个降序序列，从 $n-1$ 一直到 $0$。

再观察一下，可以发现当 $n=6$ 时前 $4$ 项和 $n=4$ 的情况一样，接下来为从 $5$ 开始的降序序列； $n=7$ 时前 $3$ 项和 $n=3$ 的情况一样，接下来为从 $6$ 开始的降序序列，以此类推……直到 $n=9$ 时前 $1$ 项和 $n=1$ 时相同。

那么我们就可以用递归的方法来解决这道题了。对于 $n$，首先找到其降序序列的起始点应该为 $\left \lceil \sqrt{n} \right \rceil^2-n+1$；对于前面的部分递归处理即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5+10;

int ans[N];

void solve(int n) {
	if (n == 1) {ans[0] = 0; return ;}
	if (n == (int)sqrt(n)*(int)sqrt(n)) {ans[0] = 0; for (int i = 1; i < n; ++i) ans[i] = n-i; return ;}
	if (n == (int)sqrt(n)*(int)sqrt(n)+1) {for (int i = 0; i < n; ++i) ans[i] = n-i-1; return ;}
	 
	int begin = ((int)sqrt(n)+1)*((int)sqrt(n)+1) - n + 1;
	for (int i = begin; i < n; ++i) ans[i] = n-1-(i-begin);
	solve(begin);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t -- ) {
		int n;
		scanf("%d", &n);
		solve(n);
		for (int i = 0; i < n; ++i) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}

```

---

## 作者：szhqwq (赞：5)

## 分析

我们从 $n - 1$ 开始考虑递归处理此题，设当前的数为 $x$，找到比它大的完全平方数中最小的那个 $k$，那么 $k = \left \lceil \sqrt{n}  \right \rceil ^2$，$a_x$ 到 $a_{x-k}$ 则可以依次填入 $k - x,...,x$，再继续递归处理 $k - x - 1$ 即没填完的部分。

AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n;

inline void init(int x) {
	if (x < 0) return ;
	int k = ceil(sqrt(x)); k = k * k;
	init(k - x - 1);
	for (int i = x; i >= k - x; i -- ) cout << i << " ";
}

signed main() {
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	int t;
	cin >> t;
	while (t -- ) {
		cin >> n;
		init(n - 1);
		cout << endl;
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：5)

## 题意
构造一个长度为 $0$ 的序列。序列中 $n$ 个数为 $0$ 到 $n-1$。并使得 $a_j+j$ 是完全平方数。

## 思路
考虑递归处理问题。

先从最后一个数开始，找到一个刚比它大的完全平方数，不妨设当前最后一个数为 $x$，则设这个完全平方数为 ${\lceil \sqrt{n}\rceil}^2=k$，则在此处放上 $k-x$ 即可。那么同样的，在 $a_{k-x}$ 的地方需要放上 $x$。

那么对于从 $i=k-x$ 到 $i=x$ 的地方，我们依次放上 $x,x-1,\dots,k-x$ 即可保证这个区间内所有数的 $a_i+i=k$。然后递归处理 $k-x-1$ 即可。

一开始 $x=n-1$。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t,n,m,k;
void solve(int now){
  if(now<0)return;
  int m=ceil(sqrt(now));
  m=m*m;
  solve(m-now-1);
  nrep(i,now,m-now){
    cout<<i<<" ";
  }
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    solve(n-1);
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：Toothless03 (赞：4)

~~水一篇题解~~

先来证明一点小东西：在 $n,n+1,n+2\cdots 2n$ 中一定有一个完全平方数 $k$ 。

> 假设 $k={\lceil \sqrt{n} \rceil}^2$ 则 $k\ge n$ 。

> 根据上取整的定义可知 ${\lceil \sqrt{n} \rceil} \le \sqrt{n} + 1$ 

> 平方可得 $k = {\lceil \sqrt{n} \rceil}^2 \le n + 2\sqrt{n} + 1$ 

> 因为 $k \le 2n$ 所以 $n \ge 2\sqrt{n} + 1$ 

> 解的 $\sqrt{n} \ge \dfrac{1}{2} + \dfrac{\sqrt{3}}{2} \approx 1.37$ 成立，此时 $n \ge 1.87$ 

> 代入 $n=1$ ，发现也成立，既命题成立，证毕。

可以将上面的命题转化为 $0 \le k-n \le n$ 其中 $k$ 为完全平方数，只需找到 $k$ 便可以将 $[k-n,n]$ 匹配好，然后只需递归求解即可。

贴上核心代码：

```cpp
inline void trav(int n) {
	if (n <= 0)
		return;
	int k = sqr(ceil(sqrt((double)n - 1)));
	int l = k - n + 1, r = n;
	for (int i = l; i < r; i++)
		arr[i] = k - i;
	trav(l);
}
```

---

## 作者：Jeremiahy (赞：2)

## 分析

首先思考最简单的情况：$n$ 为完全平方数。这时候只需要 $0$ 不变，把 $0$ 以后的序列倒过来就形成一种互补的情况，从而全部达到完全平方数。

进一步，我们发现，对于一段连续的序列（值也连续），如果首项加末项为完全平方数，那么把整个序列倒过来后，对应下标与原序列相加得到的序列全部是完全平方数（而且还是固定的一个）。证明很简单，设序列为 $a_1,a_2,\dots,a_n$， $a_1+a_n$ 为完全平方数， $a_2+a_{n-1}=a_1+1+a_n-1=a_1+a_n$ 也为完全平方数，其他同理。

这道题的思路也是构造出这种互补情况：从 $n-1$ 开始，设 $n-1+k$ 为完全平方数，那么只需要往前找，一直找到 $k$，把后面这部分倒过来即可。然后继续从 $k-1$ 处按照上述方法寻找，采用递归实现。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
bool sq[10000005];
inline void solve(int x) {
    if (x != -1)//边界
    	for (register int i = x; ; i++)
        	if (sq[i]) {
          	  	solve(i - x - 1);
          	  	for (register int j = x; j >= i - x; j--)//倒过来
          	      	cout << j << " ";
         	   	break;
        	}		
}
signed main() {
    cin >> t;
    for (register int i = 0; i * i < 10000005; i++)//预处理平方数
    	sq[i * i] = 1;
    while (t--) {
        cin >> n;
        solve(n - 1);
        puts("");
    }
    return 0;
}
```


---

## 作者：linxinyu330 (赞：1)

### 思路

当 $a_i+i$ 等于一个完全平方数 $k$ 时，$a_i=k-i$ ，可以发现，当 $i'=i-1$ 时，$a_i'=a_i+1$。因此，我们可以找到离当前要填的区间 $[0,x]$ 的末尾下标 $i_x$ 最近且大于等于它的完全平方数，从后往前填，直到要填的数超出范围，再按照相同的方法处理剩下的数。

### 代码

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const int N=1e5+5;
int a[N];
vector<int>b;//存完全平方数

//初始化完全平方表
void init()
{
	int u=sqrt(N)+1;
	for(int i=1;i<=u;i++)b.push_back(i*i);
}

void solve()
{
	int n;
	cin>>n;
	memset(a,0,sizeof(int)*(n+1));//初始化答案数组
	
	int x=n-1;//要填入数组的数为[0,n-1]，即此处的[0,x]
	while(x>0)
	{
		int snum=*lower_bound(b.begin(),b.end(),x);//找到 >=x 的最近完全平方数
		int s=0;//记录填了多少个数
		for(int i=x;i>=0;i--)//由后往前填
		{
			if(snum-i<=x)//填入的数上限为x，若超过则break
			{
				a[i]=snum-i;
				s++;
			}
			else break;
		}
		x=x-s;//还要填x-s个数
	}
	
	for(int i=0;i<n;i++)cout<<a[i]<<" \n"[i==n-1];
}

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	init();
	while(t--)solve();
	return 0;
}
```

---

## 作者：Ender_hz (赞：1)

# 题意

给定一个正整数 $n(n\le10^5)$，问能否构造长度为 $n$，**下标从 $0$ 开始**的数组 $p$，满足：

+ $[0,n-1]$ 中的每个数恰好出现一次
+ $p_i+i$是完全平方数

若能，输出数组 $p$，反之输出 $-1$。

# 分析

以样例给出的 $n=7$ 时的一种数组 $p=[1,0,2,6,5,4,3]$ 为例，分析如何构造 $p$ 数组：

+ 令 $p_6+6$ 为完全平方数，则 $p_6$ 有最小值 $\left\lceil\sqrt{6}\right\rceil^2-6=3$，此时 $p_6+6=\left\lceil\sqrt{6}\right\rceil^2=9$，符合要求；
+ 由于数组 $p$ 中一定会出现 $6$，而我们在上一步已经判断出 $3+6=9$ 是完全平方数，所以我们可以令 $p_3=6$，此时 $p_3+3=9$，符合要求；
+ 此时我们令 $p_{3..6}$ 为首项 $p_3=6$，末项 $p_6=3$，公差为 $-1$ 的等差数列，可得 $\forall i\in[3,6], p_i+i$ 是完全平方数，且 $p_i\in[3,6]$，符合要求；
+ 现在数组 $p$ 中还未确定的元素为 $p_0,p_1,p_2$，未使用过的值为 $0,1,2$，则该问题转化为了求 $n=3$ 时的数组 $p$；
+ 在求出 $n=3$ 时的数组 $p$ 后，再接上 $[6,5,4,3]$ 即为 $n=7$ 时的答案。

要让上述思路成立，必须满足 $\left\lceil\sqrt x\right\rceil^2-x\le x\Rightarrow\left\lceil\sqrt x\right\rceil\le\sqrt2\cdot\sqrt x$，可证对于任意非负整数左式均成立，故没有无解的情况。

# 代码

```cpp
#include<iostream>
#include<cmath>
#define dfor(i, t, h) for(int i = (t); i >= (h); --i)
#define il inline
using namespace std;
int T = 1, N;
il void solve(int x) {
    if(x < 0)
        return;
    int m = int(ceil(sqrt(x)));
    m *= m;
    solve(m - x - 1);
    dfor(i, x, m - x)
        cout << i << " ";
}
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        solve(N - 1);
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
看到这题，不难想到是数论。推不出来怎么办？列表找规律！
```cpp
n\a a[0] a[1] a[2] a[3] a[4] a[5] a[6] a[7] a[8] a[9]
1   0
2   1    0
3   1    0    2
4   0    3    2    1
5   4    3    2    1    0
6   0    3    2    1    5    4
7   1    0    2    6    5    4    3
8   1    0    7    6    5    4    3    2
9   0    8    7    6    5    4    3    2    1
10  9    6    7    6    5    4    3    2    1    0

模拟赛时打的表，有点难看勿喷
```
看完这个表我们来推一下:

当 $n$ 取 $1,2,5,10$ 时，$a$ 数组直接倒序。那显然，倒序的是完全平方数加 $1$。（$1=0^2+1,2=1^2+1,5=2^2+1,10=3^2+1$）。

在多看几个，你会发现好像有些重复的地方，我们展开一下：

例如 $n=6$：

把答案分成两部分 $\mathbf{x}=\{0,3,2,1\}$ 和 $\mathbf{y}=\{5,4\}$。显然 $\mathbf{x}$ 与 $n=4$ 时的
$a$ 数组相同，$\mathbf{y}$ 是从 $5$ 开始降序。

剩下的一些不举例了，大家可以试试 $n=7$ 等情况。



最后就能知道，降序排列起点是 $\lceil\sqrt{n}\rceil+1$。因为看表会发现，有重复关系的如下：

$1$：降序。

$2$：降序。

$3$：与 $2$ 重复。

$4$：与 $1$ 重复。

$5$：降序。

$6$：与 $4$ 重复。

$7$：与 $3$ 重复。

$8$：与 $2$ 重复。

$9$：与 $1$ 重复。

$10$：降序。

规律显然，就不再赘述。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int t,n,a[N];
void solve(int n) 
{
	if(n==1)//特判
	{
		a[0]=0; 
		return;
	}
	if(n==(int)sqrt(n)*(int)sqrt(n))//完全平方数
	{
		a[0]=0;
		rep1(i,1,n-1) a[i]=n-i; 
		return;
	}
	if(n==(int)sqrt(n)*(int)sqrt(n)+1)//sqrt返回的是浮点数，强转整型后会向下取整，判断是否是完全平方数+1
	{
		rep1(i,0,n-1) a[i]=n-i-1;//倒序
		return;//走人
	}
	int x=((int)sqrt(n)+1)*((int)sqrt(n)+1)-n+1;
	rep1(i,x,n-1) a[i]=n-1-(i-x);
	solve(x);//递归
}
void getans()
{
	cin>>n;
	solve(n);//递归处理前面的相同部分
	rep1(i,0,n-1) cout<<a[i]<<' ';//输出
	putchar('\n');//换行要记住
	return;
}
signed main() 
{
	cin>>t;
	while (t--) getans();//循环要答案
	return 0;//收场
}
```

---

## 作者：As_Snow (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1713C)

[可能更好的食用体验](https://www.cnblogs.com/As-Snow/p/16900565.html)
### 思路
看起来或许无从下手，所以我们从小的 $n$ 开始枚举找规律。
$$
\begin{aligned}
&n=1:\quad 0\\
&n=2:\quad 1\,0\\
&n=3:\quad 1\,0\,2\\
&n=4:\quad 0\,3\,2\,1\\
&n=5:\quad 4\,3\,2\,1\,0\\
&n=6:\quad 0\,3\,2\,1\,5\,4\\
&n=7:\quad 1\,0\,2\,6\,5\,4\,3\\
&n=8:\quad 1\,0\,7\,6\,5\,4\,3\,2\\
&n=9:\quad 0\,8\,7\,6\,5\,4\,3\,2\,1\\
\end{aligned}
$$
我们设 $\text{sub}(i)+i$ 是一个完全平方数。
不难想到，一个 $0$ 至 $n$ 的一个优秀排列中，从 $\text{sub}(n)$ 位开始，是一个以 $n$ 位首项的降序序列。因为如果 $n + \text{sub}(n)$ 位完全平方数，那么 $(n-1)+(\text{sub}(n)+1)$ 也为相同的完全平方数，以此类推。

那 $\text{sub}(n)$ 前面的怎么解决呢？因为第 $\text{sub}(n)$ 位前面的一定是一个 $0$ 至 $\text{sub}(n)-1$ 的一个优秀排列，我们只需要去递归解决这个子问题就可以了。

### Code
```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+15;
int T;
int n;
int a[N];
int sub(int a){
	int i;
	for(i=0;i*i<a;i++);
	return i*i-a;
}
void dfs(int n){
	if(n==0)return (void)(a[0]=0);
	int t=sub(n);
	dfs(t-1);
	for(int i=t,j=n;i<=n;i++,j--)a[i]=j;
}
void solve(){
	cin>>n;
	dfs(--n);
	for(int i=0;i<=n;i++)cout<<a[i]<<' ';
	puts("");
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：wlmqlzm (赞：0)

## CF1713C Build Permutation
#### 题意简述：
给定 $n$ ，用 $[0,n-1]$ 这 $n$ 个数构造一个长度为 $n$ 的数组 $a$ ，下标从 $0$ 到 $n-1$ ，满足 $a_i+i\ (0\le i\le n-1)$ 是完全平方数，即 $a_i+i=k^2$ ( $k$ 为非负整数）。  
容易发现， $a_0$ 可以放任意小于 $n$ 的完全平方数， $a_1$ 可以放任意小于 $n+1$ 的完全平方数 $-1$ ，但是这样推很麻烦。  
***
我们不妨从 $a_{n-1}$ 开始推。为了方便，记第一个大于等于 $n-1$ 的完全平方数为 $k^2$ 。因为 $n-1\ge 0$ ，所以 $a_{n-1}+n-1$ 只能往 $k^2$ 凑，所以**只有一种**方法。  
因此 $a_{n-1}=k^2-(n-1)$ ，而 $a_{n-2}=k^2-(n-2)$ ，以此类推，直至 $k^2-(n-i)=n-1$ 。那么，我们就可以递归求解。  
事实上，并不存在无法构造输出 $-1$ 的情况，具体证明过程请参考[官方题解](https://codeforces.com/blog/entry/105419)
### code:
~~~cpp
void dfs(int n)
{
	int i,tmp;
	if(n==-1) return;
	tmp=n;
	while(judge(tmp)==0) tmp++;//找第一个大于等于n的完全平方数
	for(i=n;tmp-i<=n&&i>=0;i--)
		a[i]=tmp-i;
	dfs(i);//递归
}
~~~

---

## 作者：Error_Eric (赞：0)

#### 题意

我们认为一个序列 $a$ 是优秀的，当且仅当其任意一个元素加上其下标是完全平方数。

形式化地， $\forall i\in[0,n), \sqrt{a_i+i}\in\mathbb{R}$ 。

给定 $n$，求 $0$ 至 $n-1$ 的一个优秀排列，或者判断不存在这样的排列。

值得注意的是，本题中特殊规定下标从 $0$ 开始，到 $n-1$ 结束。

#### 解法

首先有一个结论是对于任意 $b\geq 0$ 总是满足 $\exists x \in \mathbb{R}\ b\le x^2\le 2b$ 。

证明方法也很简单。

首先 $b<10$ 的时候枚举成立。

剩余情况不妨令 $x$ 非负，则上式等价于 $(x+\sqrt{b})(x-\sqrt b)\geq0$ 且 $(x+\sqrt{2b})(x-\sqrt{2b})\leq0$ 

则上式等价于求一个在 $[\sqrt b,\sqrt 2\times\sqrt b]$ 中的整数。

$(\sqrt2-1)\sqrt b>2$ 数轴上连续的比 $2$ 长的区间必然覆盖至少一个整数。


------

从后往前构造 $a_n$ 。

令 $a_n=\lfloor \sqrt{2n}\rfloor^2-n$ 。

 $a_{a_n}=n$。
 
 然后 $a_{n-1}=a_n+1$， $a_{a_n+1}=n-1$

如此可以构造完 $a_{\lfloor \sqrt{2n}\rfloor^2-n}...a_n$。

再在剩余的里面重复构造即可。

#### Code

没啥好解释的。

[Link](https://codeforces.ml/contest/1713/submission/167580670)


---

