# Block Sequence

## 题目描述

Given a sequence of integers $ a $ of length $ n $ .

A sequence is called beautiful if it has the form of a series of blocks, each starting with its length, i.e., first comes the length of the block, and then its elements. For example, the sequences \[ $ \color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] and \[ $ \color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] are beautiful (different blocks are colored differently), while \[ $ 1 $ \], \[ $ 1,\ 4,\ 3 $ \], \[ $ 3,\ 2,\ 1 $ \] are not.

In one operation, you can remove any element from the sequence. What is the minimum number of operations required to make the given sequence beautiful?

## 说明/提示

In the first test case of the example, the given sequence is already beautiful, as shown in the statement.

In the second test case of the example, the sequence can only be made beautiful by removing all elements from it.

In the fifth test case of the example, the sequence can be made beautiful by removing the first and last elements. Then the sequence will become \[ $ 2,\ 3,\ 4 $ \].

## 样例 #1

### 输入

```
7
7
3 3 4 5 2 6 1
4
5 6 3 2
6
3 4 1 6 7 7
3
1 4 3
5
1 2 3 4 5
5
1 2 3 1 2
5
4 5 5 1 5```

### 输出

```
0
4
1
1
2
1
0```

# 题解

## 作者：midsummer_zyl (赞：9)

这道题就是简单 $dp$ 嘛。

通过~~观察~~归纳可知，$dp[i]$ 的值只能从 $dp[i + 1] + 1$ 与 $dp[i + a[i] + 1]$ 两者间取较小值，于是，当 ``a[i] + i <= n`` 时就采用这种方法，否则 ``dp[i] = dp[i + 1] + 1``。

好滴，这道题就处理完了，输出 $dp[1]$ 即可。

**AC** 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N], dp[N];
int main() {
	int T; cin >> T;
	while(T--) {
		int n; cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		dp[n + 1] = 0;
		if(a[n] == 0) dp[n] = 0;
		else dp[n] = 1;
		for (int i = n - 1; i >= 1; i--) {
        		//倒序
			if(a[i] + i <= n)
				dp[i] = min(dp[i + 1] + 1, dp[i + a[i] + 1]);
			else dp[i] = dp[i + 1] + 1;
         		//dp
		}
		cout << dp[1] << endl;
	}
	return 0;
}
```

---

## 作者：BrotherCall (赞：7)

## 先考虑暴力 dp

用 $f_i$ 表示前 $i$ 个数字都成功分块需要删的最少数量。

容易得到转移方程：

```cpp
for(int i = 1;i <= n;i ++) {
	for(int j = 0;j < i;j ++) {
		if(a[j + 1] + j + 1 <= i)
			f[i] = min(f[i] , f[j] + (i - (a[j + 1] + j + 1))); 
```

最后的答案就是 $f_n$

时间复杂度 $O(n^2)$

## 如何优化？

### 初步思路：

由于每一层 $i$ 转移时 $i$ 都是个定值，所以 $f_i$ 的值就是由最小的 $f_j - a_{j + 1} - j - 1$ 决定，所以考虑拿一个优先队列处理这个。

所以一开始的想法为搞一个小根堆，每一个 $i$ 转移完之后就放元素，第一维放 $f_i - a_{i + 1} - i - 1$ ，第二维放 $i$ 。

每次把不符合 $a_{j + 1} + j + 1 \leqslant i$ 的扔了，找到第一维最小的符合条件的 $j$ 更新答案。

这时候我们就发现问题了，有可能被我们扔掉的位置后面对答案有贡献，那这个做法就是错的了。

### 解决方法：

所以我的做法是再整一个小根堆，第一维是 $a_{j + 1} + j + 1$，起到一个临时回收站的作用，做法是把不符合 $a_{j + 1} + j + 1 \leqslant i$ 的扔到临时回收站里，每次 $i$ 变大之后判断回收站里的 $j$ 符不符合条件，符合条件就再扔回去。

由于 $i$ 是单调递增的，所以临时回收站中的元素每一个最多被扔回去一次，而扔回去的元素不会再被扔回来了。

所以总复杂度为 $O(n\log n)$

两个堆的具体实现：

```cpp
while(a[now + 1] + now + 1 > i && pq.size()) {
	ano.push(make_pair(a[now + 1] + now + 1 , now));
	pq.pop();
	now = pq.top().second;
}
while(ano.size() && ano.top().first <= i) {
	int h = ano.top().second;
	pq.push(make_pair(f[h] - a[h + 1] - h - 1 , h));
	ano.pop();
}
```

[Code](https://codeforces.com/contest/1881/submission/227907871)

---

## 作者：CQ_Bob (赞：5)

## 分析

一眼 DP。

定义状态函数 $\mathit{f}_{i,j}$ 表示后 $i$ 位中，删掉或不删掉第 $i$ 个数时，使后 $i$ 个数满足条件的最小步数。

如果删掉第 $i$ 个数，有转移方程：$\mathit{f}_{i,1}=\min(\mathit{f}_{i+1,1},\mathit{f}_{i+1,0})+1$。

如果不删掉第 $i$ 个数，则第 $i$ 个数将会是某个块的第 $1$个数，下一个块的第一个数将会至少是 $i+a_i+1$。但是，我们可以在 $[i,i+a_i]$ 中删掉一些别的数，使答案更优。所以有转移方程：$\mathit{f}_{i,0}=\min(\mathit{f}_{i+a_i+1,0},\mathit{f}_{i+a_i+1,1})$。这个的前提是 $i+a_i \le n$。

对于答案，枚举每个终点。对于终点 $i$，由于 $i$ 之前有 $i-1$ 个数，所以以 $i$ 为终点时，答案是 $\mathit{f}_{i,0}+(i-1)$。状态函数初始时 $\mathit{f}_{n+1,0}=0$。

注：有可能全部删完才能使序列满足条件，所以对于答案还要与 $n$ 取最小。

## 代码

```c
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

int n;
const int N=1e6+10,inf=1e10;
int a[N],f[N][2];

il void read(){
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>a[i];
	return ;
}
il void solve(){
	for(re int i=1;i<=n;++i) f[i][0]=f[i][1]=inf; f[n+1][0]=0;
	for(re int i=n;i>=1;--i){
		f[i][1]=min(f[i+1][1],f[i+1][0])+1;
		if(i+a[i]<=n) f[i][0]=min(f[i+a[i]+1][1],f[i+a[i]+1][0]);
	}
	int minn=n;
	for(re int i=1;i<=n;++i) minn=min(minn,f[i][0]+(i-1));
	cout<<minn<<"\n";
	return ;
}

signed main(){
	int t;cin>>t;
	while(t--) read(),solve();
	return 0;
}
```


---

## 作者：NanNanzi_QvQ (赞：5)

非常简洁的 DP，令 $f_i$ 表示把第 $i$ 个到第 $n$ 个数字变为美丽的所需要删掉的数字的最少数量，则可以考虑是否保留第 $i$ 个数字，如果保留，则结果为 $f_{i+a[i]+1}$，如果删除，则结果为 $f_{i+1}+1$，初始化 $f_n=1, f_{n+1}=0$。

状态转移方程为：$f_i=\min(f_{i+1}+1,f_{i+a[i]+1})$

初始化 $f_{n+1}=0$ 是因为，如果第 $i$ 个数字到第 $n$ 个数字刚好构成一个块，则 $f_i=0$，故根据状态转移方程，直接使得 $f_{n+1}=0$ 即可。

AC代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200010], dp[200010];
int main()
{
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		dp[n + 1] = 0; dp[n] = 1;
		for (int i = n - 1; i >= 1; i--) {
			if (i + a[i] > n) dp[i] = dp[i + 1] + 1;
			else dp[i] = min(dp[i + 1] + 1, dp[i + a[i] + 1]);
		}
		cout << dp[1] << endl;
	}
	return 0;
}
```


---

## 作者：AlicX (赞：4)

## Solution 


因为此题想不了贪心，所以考虑 `dp`。定义 $f_i$ 表示前 $i$ 个字符变成美丽串的最小花费。则有一下两种情况：

1. 删去这个数，则有 $f_i=f_{i-1}+1$。

2. 以这个数作为区间长度，则有 $f_{i+a_i}=f_{i-1}$。

分类讨论一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=2e5+10,INF=1e9+7; 
int n; 
int a[N],f[N];  
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f; 
} 
il void work(){ //int ans=INF; 
	n=read(); int ans=INF; 
	for(int i=1;i<=n;i++) a[i]=read(),f[i]=INF; f[0]=0;  
	for(int i=1;i<=n;i++){ 
		f[i]=min(f[i],f[i-1]+1); 
		if(i+a[i]<=n) f[i+a[i]]=min(f[i+a[i]],f[i-1]); 
	} for(int i=1;i<=n;i++) ans=min(ans,f[i]+n-i); printf("%lld\n",ans); 
} 
signed main(){ 
	int T=read(); 
	while(T--) work(); 
	return 0;
} /* */ 
```


---

## 作者：shinzanmono (赞：2)

我们可以发现对于每一个 $i$，都存在一个形如 $[i,i+a_i](i+a_i\leq n)$ 的区间。

所以我们简化问题，给出不超过 $n$ 个区间，请选出一些区间使他们两两不交，并且覆盖的总长度最大。

考虑 dp，设 $f_i$ 表示在 $[1,i]$ 内能被覆盖的总长度。

转移很简单：

设 $S_i$ 表示右端点为 $r$ 的区间的左端点集

$$
f_i=\max(f_{i-1},\max_{l\in S_i}f_{l-1}+r-l+1)
$$

最后的答案为 $n-f_n$。

时间复杂度 $O(\sum n)$，可以通过此题。

---

## 作者：banned_gutongxing (赞：1)

## 思路

一眼 DP。
设计状态：$dp_i$ 表示从 $i$ 开始最少需要修改几次才能成为合法序列。

+ 若本身合法，那么 $dp_{i}=dp_{i+a_i+1}$。
+ 若不能，那么 $dp_{i}=dp_{i+1}+1$，把 $a_i$ 设为 0。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+10;
const int INF = 0x3f3f3f3f;
int dp[MAXN],a[MAXN],n,t;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i = 1;i<=n;i++){
			scanf("%d",a+i);
		}
		for(int i = 1;i<=n;i++) dp[i] = INF;dp[n+1] = 0;
		for(int i = n;i>=1;i--){
			dp[i] = dp[i+1]+1;
			if(i+a[i]+1<=n+1) dp[i] = min(dp[i+a[i]+1],dp[i]);
		}
		printf("%d\n",dp[1]);
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

- 给出一个长度为 $n$ 的整数序列 $a$。定义一个合法序列，当且仅当该序列由一系列块组成（每个块由两部分构成，首先第一个数字是块中元素的数量，紧接着是这些元素）。在一次操作中，你可以删除序列中任意一个元素。问你至少需要多少次操作使这个序列变为一个合法序列。
- $n \le 2 \times 10^5$，$a_i \le 10^6$。

最原始的 DP，设 $f_i$ 表示序列 $a_1 , a_2, \dots, a_i$ 的答案。

枚举最后一段的起点位置 $j(j < i)$。因为只能删除不能添加，所以这一段的长度 $i - j$ 必须不小于 $a_j$。接下来显然我们需要在最后一段上删除 $i - j - a_j$ 个元素。所以转移式：
$$
f_i = \min_{1 \le j < i 且 i - j \ge a_j}\{f_{j - 1} + i - j - a_j\}
$$
稍微变形得：
$$
f_i = \min_{1 \le j < i且\color{red}a_j + j \le i}\{f_{j - 1} - j - a_j\} \color{red} + i
$$
这个式子用树状数组维护即可。

[record](https://codeforces.com/contest/1881/submission/258694751).

---

## 作者：_Maverick_ (赞：0)

## 思路
设 $dp_i$ 为当 $i$ 到 $n$ 为完美的最少删除次数。

从后至前对于 $dp_i$ 更新，若直接删除当前点，则为 $dp_{i+1}+1$。

若不删除则为 $dp_{i+a_i+1}$ 和 $dp_i$ 最小值。

$i+a_i+1$ 为 $a_i$ 不能覆盖的位置。
## ACcode

```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
 
using namespace std;
 
int t;
 
int dp[200010];
int a[200010];
 
void op()
{
	int n;
	cin >> n;
 
	memset(dp, 0x3f, sizeof dp);
 
	for (int i = 1; i <= n; i++)cin >> a[i];
 
	dp[n] = 1;
	dp[n + 1] = 0;
 
	for (int i = n-1; i >=1; i--)
	{
		dp[i] = min(dp[i + 1] + 1, dp[i]);
 
		if (a[i] + i + 1 <= n+1)
		{
			dp[i] = min(dp[i + a[i] + 1], dp[i]);
		}
	}
	
	cout << dp[1] << endl;
}
 
signed main()
{
	cin >> t;
	while (t--)
	{
		op();
	}
 
	return 0;
}
```

---

## 作者：Jason_Harry_Song (赞：0)

# 题解：CF1881E Block Sequence

考察算法：动态规划（dp）。

定义状态 $f_i$ 表示将区间 $[i,n]$ 处理好的最小操作次数。

对于初始状态，我们处理一个空区间，即 $[n+1,n]$ 的操作次数自然是 $0$，因此 $f_{n+1}=0$。

接下来是 dp 的灵魂所在——转移方程。对于 $i$，我们可以选择删除 $a_i$，就是从 $f_{i+1}+1$ 转移；也可以选择不删除 $a_i$，那么从 $i+1$ 开始就会形成一个长度为 $a_i$ 的块，即 $[i+1,i+a_i+1]$，如果 $i+a_i+1\leq n+1$ 就可以从 $f_{i+a_i+1}$ 转移（与 $f_{i+1}$ 取最小值）。

最终答案自然就是 $f_1$。

代码实现：
```cpp
#include <bits/stdc++.h>
#define N 200000
using namespace std;
int t, n, a[N + 1];
int f[N + 2];
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		f[n + 1] = 0;
		for (int i = n; i >= 1; i--) {
			f[i] = f[i + 1] + 1;
			if (i + a[i] + 1 <= n + 1) {
				f[i] = min(f[i], f[i + a[i] + 1]);
			}
		}
		printf("%d\n", f[1]);
	}
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

先说吐槽：这道题，做的时候半个小时就把代码打出来了，结果为什么花了一个小时十分钟，是应为每一次躲测清空的时候，没有加那个一。

再说幸运：我这个代码本来是会运行错误的，但由于我看错了数据范围，把 $2\times10^5$ 看成了 $2\times10^6$，逃过一劫。
# 题目大意
有一个长度为 $n$ 的数组 $a$，问你至少要删除几个元素，才能使一些几个块拼接起来是这个数组。
# 题目思路
~~不要问我怎么想到动态规划的，因为老师考我们的比赛名叫做听说你会 DP。~~

先分析一下时间复杂度，
>$1\leq t \leq 10^4$
>
>$1\leq n \leq 2 \cdot10^5$

很明显，只有 $O(n\times t)$ 才行。

于是我们就可以猜出用来动态规划的 $dp$ 数组是一维。每一次用 $dp_i$ 表示当前是第 $i$ 个，最多能剩下多少个。

然后手搓动转方程：
$$dp_{i+a_i+1}=\max(dp_{i+a_i+1},dp_i+a_i+1)$$
但是每一次还有可能把这一次传到下一次，于是又有：
$$dp_{i+1}=\max(dp_i,dp_{i+1})$$
# AC Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Os")
//#pragma GCC optimize("Ofast")

using namespace std;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1 ++)
char *p1, *p2, buf[(1 << 20) + 5];

inline int read() {
	int x = 0, f = 1;
	char c = gc();
	
	while (!isdigit(c)) {
		if (c == '-') {
			f = -1;
		}
		
		c = gc();
	}
	
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	
	return x * f;
}

void write(int k) {
	if (k < 0) {
		putchar('-');
		k = -k;
	}
	
	if (k > 9) {
		write(k / 10);
	}
	
	putchar(k % 10 + 48);
}

const int N = 2e6;

void init();

int T, n, a[N + 5], dp[N + 5];

signed main() {
	init();
	cin >> T;	
	
	while (T --) {
		cin >> n;
		
		for (int i = 1; i <= n + 1; ++ i) {
			dp[i] = 0;
		}
		
		for (int i = 1; i <= n; ++ i) {
			cin >> a[i];
		}
		
		for (int i = 1; i <= n; ++ i) {
			dp[i + a[i] + 1] = max(dp[i] + a[i] + 1, dp[i + a[i] + 1]);
			dp[i + 1] = max(dp[i], dp[i + 1]);
		}
		
		cout << n - dp[n + 1] << endl;
	}
	
	return 0;
}

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
}
```

---

## 作者：qiuzijin2026 (赞：0)

# CF1881E Block Sequence

#### [题面](https://www.luogu.com.cn/problem/CF1881E)

## 思路

考虑 dp。

设 $f_{i}$ 表示 $i$ 到 $n$ 中最多有多少数是在块内的。

易得：

$$
f_{i}=\max(f_{i+a_{i}+1}+a_{i}+1,\max_{j=i+1}^{n} f_{j})
$$

可以发现 $\max_{j=i+1}^{n} f_{j}$ 可以用一个变量存，于是时间复杂度为 $O(n)$。

最后输出 $n - f_{1}$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[200005];
int f[200005];
int maxx;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            if(i+a[i]+1<=n+1) f[i]=f[i+a[i]+1]+a[i]+1;
            f[i]=max(f[i],maxx);
            maxx=max(f[i],maxx);
        }
        printf("%d\n",n-f[1]);
        for(int i=1;i<=n+1;i++) f[i]=0; 
        maxx=0;
    }
    return 0;
}
```

---

## 作者：_zqh_ (赞：0)

# Solution

考虑 Dp；

$f_i$ 表示遍历到 $i$ 一共需要移除的多少个数。

第 $i$ 个数有可能是一个序列的开头，或者不是；

当 $i$ 为一个序列的开头时，可以跳过这个序列的剩下的数，直接转移到下一个序列的开头；

$$
f_{i+a_i+1}=\min\{f_{i+a_i+1},f_i\}
$$

当然也可以考虑删掉这个数；

$$
f_{i+1}=\min\{f_{i+1},f_i+1\}
$$

**请注意**，最后输出 $f_{n+1}$。

可以写出代码：

[code](https://codeforces.com/contest/1881/submission/261762092).

---

## 作者：_Only_this (赞：0)

### CF1881E Block Sequence 题解

------------

一道很显然的 dp。

------------

状态也很好想，$dp_i$ 表示后 $i$ 个数要删多少个数。

这里我觉得倒着设状态更好转移，因为一个块的第一个数表示块的大小。

然后就是平平无奇的转移了。

考虑两种情况，一种是不要 $a_i$ 了，一种是以 $a_i$ 为一个块的大小。

贴个代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int T,n;
int a[maxn],dp[maxn];
inline void Solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		dp[i]=n-i+1;
	}
	dp[n]=1;
	for(int i=1;i<=n;i++){
		if(i==n-a[i]){
			dp[i]=0;
		}
	}
	for(int i=n-1;i>=1;i--){
		if(i+a[i]+1<=n){
			dp[i]=min(dp[i],dp[i+a[i]+1]);
		}
		dp[i]=min(dp[i],dp[i+1]+1);
	}
	printf("%d\n",dp[1]);
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		Solve();
	}
	return 0;
}
```

完结散花。

---

## 作者：_fairytale_ (赞：0)

## 前言

赛时卡 B 上了，没开 ll 调了一年，拿到这道题的时候还剩 $25min$。

强大的 [@崔化博](https://www.luogu.com.cn/user/304524) 先开的这题，十行切了。

所以给大家介绍一下我的难绷做法，$25min$ 没调出来。

## Solution

首先可以想到一个很简单的 DP。

设 $f[i]$ 为把以 $i$ 结尾的前缀变成完美序列的最小代价。

转移方程：

$$
f[i]=\min_{0\leq j<i,j+a[j]\leq i}f[j-1]+i-(j+a[j])
$$

意思就是，我们枚举 $i$ 前面的一个 $j$ 作为转移点，然后把 $j-i$ 这一部分变成完美序列。因为 $j+a[j]$ 这部分已经是完美序列了，所以只需要把不是的部分删掉，即加上 $i-(j+a[j])$ 的代价。

```cpp
for(re int i=1; i<=n; ++i)cin>>arr[i];
for(re int i=1; i<=n; ++i)f[i]=inf;
f[0]=0;
for(re int i=1; i<=n; ++i)
	for(re int j=0; j<i; ++j)
		if(j+arr[j]<=i)f[i]=min(f[i],f[j-1]+i-j-arr[j]);
cout<<f[n]<<'\n';
```

显然这个 DP 是 $\mathcal O(n^2)$ 的，肯定不行，所以考虑优化。

然后就是最难绷的部分。

假设我们当前求出了 $f[j]$，那么我们考虑它对后面转移的贡献。

把转移方程变成：
$$
\begin{aligned}
f[i]&=i+f[j-1]-(j+a[j])\\
y=f[i],k=1,&i=x,b=f[j-1]-(j+a[j])\\
y&=kx+b
\end{aligned}
$$

所以可以把 $f[j]$ 对后面的贡献看成一条定义域为 $[j+a[j],n]$，斜率为 $1$，截距为 $f[j-1]-(j+a[j])$ 的直线，直接扔进李超树里即可。

注意 $f[0]=0$，那么它对后面的贡献是一条形如 $f[i]=i$ 的直线，意义是你可以把 $i$ 前面的（包括 $i$）全删掉，变成一个完美序列嘛。

时间复杂度 $\mathcal O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define re register
#define inf 0x3f3f3f3f
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
#define mid ((l+r)>>1)
#define maxn 2010000
using namespace std;
int T;
int n,m;
int arr[maxn];
int f[maxn];
int cnt;
struct segment{
	int k,b;
}s[maxn];
inline void addline(int k,int b){
	s[++cnt]=(segment){k,b};
}
inline int calc(int id,int x){
	return s[id].k*x+s[id].b;
}
int now[maxn<<2];
void modify(int p,int l,int r,int f){
	int &g=now[p];
	if(calc(f,mid)<calc(g,mid))swap(f,g);
	int fl=calc(f,l),fr=calc(f,r),gl=calc(g,l),gr=calc(g,r);
	if(fl<gl)modify(ls,l,mid,f);
	if(fr<gr)modify(rs,mid+1,r,f);
}
void insert(int p,int l,int r,int L,int R,int f){
    if(L<=l&&r<=R){
    	if(!now[p])now[p]=f;
    	else modify(p,l,r,f);
    	return ;
	}
	if(mid>=L)insert(ls,l,mid,L,R,f);
	if(mid<R)insert(rs,mid+1,r,L,R,f);
}
int query(int p,int l,int r,int pos){
	int res=calc(now[p],pos);
	if(l==r)return res;
	if(mid>=pos)res=min(res,query(ls,l,mid,pos));
	else res=min(res,query(rs,mid+1,r,pos));
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>T;
    addline(1,0);
	while(T--){
    	cin>>n;
    	cnt=1;
    	for(re int i=1;i<=n*4;++i)now[i]=1;
    	for(re int i=1;i<=n;++i)f[i]=inf;
		for(re int i=1;i<=n;++i){
    		cin>>arr[i];
		}
		for(re int i=1;i<=n;++i){
            f[i]=query(1,1,n,i);
			addline(1,f[i-1]-i-arr[i]);
			insert(1,1,n,i+arr[i],n,cnt);
		}
        cout<<f[n]<<'\n'; 
	}
	return 0;
}
```
我也不知道为什么 div3 的 E 会想到李超树和斜率优化，大概是数据结构学魔怔了。


---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 题意简述
有 $T$ 组数据，在每一组数据中，你需要输入 $n$ 个数表示一个序列 $ \{a_i\}$，对于一个合法数列，我们定义会将这个数列分为若干块，每一块的第一个数字表示块中的元素数量，后面是这个元素。对于每组数据，你需要输出将这个序列变为合法序列的最小花费。
## 开始解题！
那么遇到这一种题，我们很容易就想到通过 `dp` 来维护这一个最小花费。  
令 $dp_i$ 表示把前 $i$ 个数字变为合法序列所需删除数字的最小数量。那么当我们要删掉 $a_i$ 时，$dp_i = dp_{i - 1} + 1$，那么当我们把 $a_i$ 作为块的长度时，有 $dp_{i + a_i} = dp_{i - 1}$。  
然后是边界问题，当我们把 $a_i$ 作为块的长度时，需要保证 $i + a_i \le n$，最后统计答案时，对于每个 $dp_i$，我们就假设要删去后面所有的数字，那么有：$ans = \min\{ans, dp_i + n - i\}$。  
最后分类讨论即可。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[200005], dp[200005]; 
void clear(int a[], int len) {
    for(int i = 1; i <= len; i++) a[i] = 0;
}
int work() {
    int ans = INT_MAX;
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] = min(dp[i - 1] + 1, dp[i]);
        if(i + a[i] <= n) dp[i + a[i]] = min(dp[i + a[i]], dp[i - 1]);
    }
    for(int i = 1; i <= n; i++) {
        ans = min(ans, dp[i] + n - i);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--) {
        memset(a, 0, sizeof(a));
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for(int i = 1; i <= n; i++) {
            dp[i] = INT_MAX;
        }
        cout << work() << endl;
    }
}
```
[AC 记录](https://www.luogu.com.cn/record/157395493)

---

## 作者：yhylivedream (赞：0)

## 题目描述
给出一个长度为 $n$ 的整数序列 $a$。定义一个合法序列，当且仅当该序列由一系列块组成(每个块由两部分构成，首先第一个数字是块中元素的数量，紧接着是这些元素)。在一次操作中，你可以删除序列中任意一个元素。问你至少需要多少次操作使这个序列变为一个合法序列？

## 分析

考虑 `dp`，因为一个数如果作为一个块的第一个只能影响后面的，不能影响前面的，满足 `dp` 的无后效性。

设 $dp_i$ 为将前 $i$ 个数变成合法序列的最少操作次数。
那么状态转移方程就是：

- 将第 $i$ 个数删除： $dp_i = dp_{i - 1} + 1$。
- 将第 $i$ 个数作为一个新的块的第一个（从 $i$ 到 $i+a_i$ 都是一个块，不用删除）：$dp_{i + a_i} = dp_{i - 1}$。

答案就是 $dp_n$，注意要把 `dp` 数组设为极大值，$dp_0$ 设为 $0$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2 * 1e5 + 5;
int T, n, a[N], dp[N];

int main(){
	for(cin >> T; T; T --){
		memset(dp, 0x3f, sizeof dp);
		cin >> n;
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
		}
		dp[0] = 0;
		for(int i = 1; i <= n; i ++){
			dp[i] = min(dp[i], dp[i - 1] + 1);
			if(i + a[i] <= n){
				dp[i + a[i]] = min(dp[i + a[i]], dp[i - 1]);
			}
		}
		cout << dp[n] << "\n";
	}
	return 0;
}


```


---

## 作者：1234567890sjx (赞：0)

那肯定是 dp。

设 $f_i$ 表示 $i\sim n$ 需要改动多少个位置才能满足答案。

首先若 $a_n=0$ 则 $f_n=0$，否则 $f_n=1$。

然后对 $n-1\sim 1$ 的每一个整数做一次转移。

如果删掉 $a_i$，那么答案显然为 $f_{i+1}+1$，否则就是把 $i\sim i+a_i$ 划成一段，答案为 $f_{i+a_i+1}$。取 $\min$ 即可。

单组时间复杂度 $O(n)$。

这边界情况真恶心。/fn

```cpp

int fun(int lim, int x) {
	return (x <= lim) ? f[x] : (int)1e18;
}

void slv(int tc = 0) {
	if (tc) {
		cerr << "Test Case " << tc << '\n';
	}
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	f[n + 1] = 0;
	f[n] = (int)(a[n] != 0);
	for (int i = n - 1; i; i--) {
		f[i] = min(f[i + 1] + 1, fun(n + 1, i + a[i] + 1));
	}
	cout << f[1] << '\n';
}
```


---

## 作者：linxuanrui (赞：0)

### 思路

设 $dp_i$ 为序列第 $i\sim n$ 个至少要改动多少个。

显然 $dp_n=\begin{cases}0&a_n=1\\1&\text{otherwise}\end{cases}$。

考虑状态转移方程。显然，一个位置有改和不改两种状态，分情况讨论：

1. 改：可以把 $a_i$ 改成任意的数，由于 $dp$ 显然单调不增，所以就是 $dp_{i+1}$。

2. 不改：可以将 $a_i\sim a_{i+a_i}$ 划分成一段。显然 $i+a_i$ 得小于或等于 $n$，可以由 $dp_{i+a_i+1}$ 转移。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
int T,n,a[200005],dp[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 1;i <= n;i++)cin >> a[i];
		dp[n] = (a[n] != 0);
		dp[n + 1] = 0;
		for(int i = n - 1;i >= 1;i--){
			dp[i] = dp[i + 1] + 1;
			if(i + a[i] <= n)dp[i] = min(dp[i],dp[i + a[i] + 1]);
		}
		cout << dp[1] << endl;
	}
}
```

---

