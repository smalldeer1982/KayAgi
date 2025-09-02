# Milena and Admirer

## 题目描述

Milena has received an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ from a secret admirer. She thinks that making it non-decreasing should help her identify the secret admirer.

She can use the following operation to make this array non-decreasing:

- Select an element $ a_i $ of array $ a $ and an integer $ x $ such that $ 1 \le x < a_i $ . Then, replace $ a_i $ by two elements $ x $ and $ a_i - x $ in array $ a $ . New elements ( $ x $ and $ a_i - x $ ) are placed in the array $ a $ in this order instead of $ a_i $ .More formally, let $ a_1, a_2, \ldots, a_i, \ldots, a_k $ be an array $ a $ before the operation. After the operation, it becomes equal to $ a_1, a_2, \ldots, a_{i-1}, x, a_i - x, a_{i+1}, \ldots, a_k $ . Note that the length of $ a $ increases by $ 1 $ on each operation.

Milena can perform this operation multiple times (possibly zero). She wants you to determine the minimum number of times she should perform this operation to make array $ a $ non-decreasing.

An array $ x_1, x_2, \ldots, x_k $ of length $ k $ is called non-decreasing if $ x_i \le x_{i+1} $ for all $ 1 \le i < k $ .

## 说明/提示

In the first test case, Milena can replace the second element of array $ a $ by integers $ 1 $ and $ 2 $ , so the array would become $ [\, 1, \, \underline{1}, \, \underline{2}, \, 2 \,] $ . Only $ 1 $ operation is required.

In the second test case, the array $ a $ is already non-decreasing, so the answer is $ 0 $ .

In the third test case, Milena can make array $ a $ non-decreasing in $ 3 $ operations as follows.

- Select $ i=1 $ and $ x=2 $ and replace $ a_1 $ by $ 2 $ and $ 1 $ . The array $ a $ becomes equal to $ [\, \underline{2}, \, \underline{1}, \, 2, \, 1 \, ] $ .
- Select $ i=3 $ and $ x=1 $ and replace $ a_3 $ by $ 1 $ and $ 1 $ . The array $ a $ becomes equal to $ [\, 2, \, 1, \, \underline{1}, \, \underline{1}, \, 1 \,] $ .
- Select $ i=1 $ and $ x=1 $ and replace $ a_1 $ by $ 2 $ and $ 1 $ . The array $ a $ becomes equal to $ [\, \underline{1}, \, \underline{1}, \, 1, \, 1, \, 1, \, 1 \,] $ .

It can be shown that it is impossible to make it non-decreasing in $ 2 $ or less operations, so the answer is $ 3 $ .

## 样例 #1

### 输入

```
4
3
1 3 2
4
1 2 3 4
3
3 2 1
7
1 4 4 3 5 7 6```

### 输出

```
1
0
3
9```

# 题解

## 作者：xinruian (赞：8)

### **题意**

给你一个数组 $a$，每次操作你可以把数组中任意一个元素 $a[i]$ 分解为正整数 $x$ 和 $y$（要求 $x+y=a[i]$），求把数组 $a$ 变为非递减数组的最小操作数。

### **思路**

首先我们要明确：把一个数 $num$ 分成 $k$ 个数时，需要对 $num$ 进行 $k-1$ 步操作。下面来分析一下这道题。

这是一道贪心题。我们倒着遍历这个数组，如果当前遍历到的数 $a[i]$ 比他后面的数 $b$ 要大，为了让操作数最小，那么该数一定要拆分成 $\lceil \frac{a[i]}{b} \rceil$ 份(记为 $x$），拆分出的数字的最小值为 $\lfloor \frac{a[i]}{x} \rfloor$ 。

下面来解释一下，比如数组 $[7,3]$，那么把 $7$ 分成 $2$ 个数是不够的，要把其分为 $3$ 个数，我们平均的分解这个数可以使得分解的数中最小的数尽可能的大，所以分解为 $[2,2,3]$，最小的数是 $2$，即 $\lfloor \frac{7}{3} \rfloor$。

### **代码**

```cpp
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;
int a[N];

void solve() {
	int n;
	cin >> n;
	long long ans = 0;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	int b = a[n];
	for (int i = n - 1; i; i --) 
		if (a[i] > b) 
		{
			int k = (a[i] - 1) / b;
			ans += k;
			b = a[i] / (k + 1);
		}
		else
			b = a[i];
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while (t --)
		solve();
	return 0;
}
```



---

## 作者：sjr3065335594 (赞：3)

## 题面翻译

$t$ 次询问，对于每次询问：给定一个长度为 $n$ 的序列 $a_1, a_2, \ldots, a_n$，每次操作你可以选定一个 $a_i$，并且自选一个整数 $x$ 满足 $1\le x<a_i$，将 $a_i$ 删除然后把 $x$ 和 $a_i-x$ 依次插入在原本 $a_i$ 的位置，求出最少多少次操作能使序列 $a$ 单调不减。

## 思路

考虑将整个过程倒着做，由于要使序列单调不降，也不存在能使一个数变大的情况，所以最后一个数肯定是不会变的。

我们倒着遍历一遍序列并记录一个 $now$ 表示对于当前这个数，将它分成的几个数中的最大值可以是多少。接下来问题就转化成了如何将一个数分成几部分使得其中最大的不超过 $now$，最小的数最大且份数最少，显然的策略就是尽量平均分，那么每个数对答案的贡献就是 $\dfrac{a_i}{now}-1$，注意上取整。然后每次按照平均分的规则更新 $now$ 即可，时间复杂度 $\Theta\left(\sum n\right)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
//#define int long long
//#define int __int128
using namespace std;
const int N=2e5+5;
const int M=1e6+5;
const int INF=2e9+5;
int t,n,a[N];
void solve() {
	ll ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int now=a[n];
	for(int i=n-1;i>=1;i--) {
		if(a[i]<=now) {
			now=a[i];
		}
		else if(a[i]%now==0) {
			ans+=a[i]/now-1;
		} else {
			int cnt=a[i]/now+1;
			ans+=cnt-1;
			now=a[i]/cnt;
		}
	}
	printf("%lld\n",ans);
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}

```


---

## 作者：_HCl_ (赞：3)

挺有意思的一道结论题。

# CF1898B 题解

**题意简述**

规定一次操作可以将数列中的一个数拆分成两个正整数，询问经过几次操作可以使整个序列单调不减。

**思路引导**

首先，很容易想到，我们可以倒着遍历数组，将每一个数都拆分成比它后面的数要小的数。

请注意，$a_i$ 后面的数不是 $a_{i+1}$，而是 $a_{i+1}$ 拆分后最小的数。

不难注意到，我们将一个数拆成 $k$ 份，只需要进行 $k-1$ 次操作。

结合一下，不难想到，想要操作次数最小，即让每个数分成的份数最小，那么就要让**分成的数尽量接近**。

形式化的，$k$ 为满足 $\lceil\dfrac{a_i}{k}\rceil\leq nxt$ 的最小值。

根据数论知识，$\lceil\dfrac{a_i}{k}\rceil\leq nxt\Leftrightarrow k\geq\lceil\dfrac{a_i}{nxt}\rceil$。即每个 $k$ 取 $\lceil\dfrac{a_i}{nxt}\rceil$ 即可。

而 $nxt$ 则表示下一个数拆分后的最小值，$a_i$ 拆分后的最小值为 $\lfloor\dfrac{a_i}{k}\rfloor$。

而 $\sum (k-1)$ 即所求结果。

**实现**

对于每一组数据，进行以下操作：

1. 读入数列，初始化（注意将 $nxt$ 赋为 $a_n$）。
1. 从 $n-1$ 到 $1$ 倒序遍历。
1. 输出。

对于每一轮循环

1. 计算 $k$。
1. 将答案统计进 $ans$。
1. 计算新的 $nxt$。

请注意数据范围较大，应当使用 `long long`。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
void solve() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)scanf("%d",a+i);
	long long ans=0;
	int nxt=a[n];
	for(int i=n-1; i>=1; --i) {
		long long k=ceil(1.0*a[i]/nxt);
		ans+=k-1;
		nxt=a[i]/k;
	}
	cout<<ans<<"\n";
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
}
```


---

## 作者：UncleSam_Died (赞：2)

### 题目大意
已知有一个长度为 $n$ 的正整数序列 $a$，现在你可以做若干次以下操作，使得 $a$ 单调不下降：
- 选择一个 $1\le i\le n$；
- 选择一个整数数 $1\le x<a_i$；
- 将 $a_i$ 分成两个正整数 $x$ 和 $a_i-x$ 并重新插入序列中，插入规则如下：
	- 设操作前的序列为 $a_1,a_2,a_3,\dots,a_i,\dots,a_k$，操作后的序列为 $a_1,a_2,a_3,\dots,x,a_i-x,\dots,a_k$。

### 解题思路
我们很容易发现，对于所有的 $a_i$，操作后有 $x<a_i,a_i-x<a_i$，也就是说，所有的 $a_i$ 只能通过操作使得值变小，而不可能增加。那么，我们从后往前更新值。读者自证不难，如果 $\exists a_i>a_{i+1}$，那么把 $a_i$ 均分为若干部分使得每部分的值小于 $a_{i+1}$ 且最大是最优决策。

由上可得，我们的操作如下：
- 若 $a_i\le a_{i+1}$，不做任何操作；
- 若 $a_i>a_{i+1}$，那么我们把 $a_i$ 均分为 $\displaystyle cnt=\left \lceil \frac{a_i}{a_{i+1}} \right\rceil$，个部分，答案 $ans=ans+cnt-1$，但是这个时候不需要更新 $a_i$ 的值，也不需要插入值。接下来，我们把 $a_i$ 更新为 $\displaystyle \left\lfloor \frac{a_i}{cnt} \right \rfloor$。

### 注意事项
考虑到 $a_i\le 10^9$，那么 $ans$ 需要开 long long。

### AC 代码
码风较丑，不喜勿喷。
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 200005
int n,a[N];
inline void work(){
	scanf("%d",&n);ll ans=0;
	for(register int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(register int i=n-1;i>=1;--i){
		if(a[i]>a[i+1]){
			int cheu=ceil((a[i]*1.0)/(a[i+1]*1.0));
			int res=a[i]%cheu;ans+=(ll)cheu-1;
			a[i]=a[i]/cheu;
		}else continue;
	}printf("%lld\n",ans);
}signed main(){
	srand(114514);
	srand(rand());
	srand(time(0));
	int T;scanf("%d",&T);
	while(T--) work();
	return 0;
}
```


---

## 作者：Nuclear_Fish_cyq (赞：1)

## 题意简述

有一个序列 $a$，每次操作把 $a$ 中的一个数分成两个，求让 $a$ 不降的最小操作次数。

## 做法

$a_i\leq10^9$，直接暴力模拟每一个操作是不行的，于是考虑贪心。由于拆数是一个让数变小的操作，所以我们倒着遍历数组。

我们考虑一个数 $x$ 和它后面的数 $y$，我们需要拆分这个数，使拆分后的这个 $x$ 的每一部分都不大于 $y$。通过计算，我们可以知道需要拆分成 $\lceil\frac{x}{y}\rceil$ 份。由于还需要进行接下来的遍历，我们还要求出拆分出的最小数，即 $\lfloor\dfrac{x}{\lceil\frac{x}{y}\rceil}\rfloor$。需要注意的是实际上操作的是 $\lceil\frac{x}{y}\rceil-1$ 次，不然结果会多。

上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
ll n, t, a[200000], ans, now;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		ans = 0;
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> a[i];
		}
		now = a[n - 1];
		for(int i = n - 2; i >= 0; i--){//倒序遍历 
			ans += (a[i] - 1) / now;
			now = a[i] / ((a[i] - 1) / now + 1);
		}
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：czh___ (赞：0)

题目大意：

有一个长为 $n$ 的数组，每次操作可以将任意 $a_i$ 分成两个数 $b$，$c$ 满足 $b+c=a_i$，然后用这两个数放回原 $a_i$ 的位置，问最少多少次操作能使 $a$ 变成非递减数组。

思路：

因为要让数组变成非递减的，所以对于某个 $a_i$，如果其大于 $a_{i+1}$，那么就要对其进行操作，无论最后进行几次操作，都应该满足，分出来的这些数是非递减的，最左边的数要大于等于再左边的一个数，最右边的数要小于等于再右边的一个数。那么如果我们这样从 $n$ 到 $1$ 遍历的话，当前数的分割策略，就只会影响到左边的数，如果我们令当前数分出来的最左边的数尽可能的大，那么再左边一个数是有可能不用分割的，那么要让分出来的最左边的数最大，就要其他数最小，又要满足非递减，所以应该将这些数平分。我们从 $n-1$ 遍历到 $1$，如果当前 $a_i>a_{i+1}$，那么这个数就应该分割 $cnt=\frac {a_i}{a_{i+1}}$ 次，平分出来的数就是 $\frac{a_i}{cnt+1}$，特殊的是如果能 $a_i$ 能整除 $a_{i+1}$，那么整除次数要减一。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int n,a[N],t=1;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int cnt=0;
		for(int i=n-1;i>=1;i--){
			if(a[i]>a[i+1]){
				int k;
				if(a[i]%2==0) 
					k=a[i]/2;
				else 
					k=a[i]/2+1;
				if(k<=a[i+1]){
					if(a[i]%2==0) 
						a[i]=k;
					else 
						a[i]=k-1;
					cnt++;
				}
				else{
					if(a[i]%a[i+1]==0){
						cnt+=a[i]/a[i+1]-1;
						a[i]=a[i+1];
					}
					else{
						cnt+=a[i]/a[i+1];
						a[i]/=(a[i]/a[i+1]+1);
					}
				}
			}
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```


[改编于](https://blog.csdn.net/ashbringer233/article/details/134965331?ops_request_misc=%257B%2522request%255Fid%2522%253A%25222af4ffae63fb5e252a0fab207fcadb60%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=2af4ffae63fb5e252a0fab207fcadb60&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-4-134965331-null-null.142^v100^pc_search_result_base8&utm_term=Milena%20and%20Admirer&spm=1018.2226.3001.4187)
（代码自己写的）

---

## 作者：Melo_DDD (赞：0)

# 题目大意
给定一个序列，每次可以把一个数劈成两个，这两个数的和是原来那个数，问最少需要多少次操作能使这个序列单调不降。
多组数据。
# 题目实现
倒着想，首先最后一个数肯定不分解，依次向前考虑当前数该怎么分。显然我们为了前面更加宽松，一定要使分裂出来最小的数最大，所以我们可以想到尽量将原数平均分，直到不大于它后面的数。
## 代码：
```
#include <bits/stdc++.h>
#define int long long
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch  == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 2e5 + 7 ;
int n ,c[N] ,dp[N] ;
inline int ceiL (int x ,int y) {
	return x % y ? x / y + 1 : x / y ;
}
inline void get () {
	dp[n] = 0 ;
	for (int i = n - 1 ;i ;i --) {
		if (c[i] > c[i + 1]) {
			dp[i] = dp[i + 1] + ceiL (c[i] ,c[i + 1]) - 1 ;
			c[i] = c[i] / (ceiL (c[i] ,c[i + 1])) ;
		}
		else dp[i] = dp[i + 1] ;
	} 
}
int t ;
signed main () {
	//freopen ("divide.in" ,"r" ,stdin) ;
	//freopen ("divide.out" ,"w" ,stdout) ;
	read (t) ;
	do {
	    memset (dp ,0 ,sizeof dp) ;
    	read (n) ;
    	f (i ,1 ,n ,1) {
    		read (c[i]) ;
    	}
    	get () ;
    	cout << dp[1] << '\n' ;
	} while (t -- != 1) ;
	//fclose (stdin) ;
	//fclose (stdout) ;
	return 0 ;
}
```

---

## 作者：_qingshu_ (赞：0)

一道比较不错的结论题。

# 题意：

给定一个长度为 $n$ 的数列 $a$。我们可以进行若干次操作，每一次操作可以把 $a_i$ 拆分成 $a_i-x$ 与 $x$ （其中 $x$ 为任意小于 $a_i$ 的整数），询问至少经过多少次操作之后可以做到将整个数列变为一个单调不降序列。

# 思路：

本题思路并不复杂，首先考虑遍历顺序，因为要求单调不降序列所以对于每一个 $a_i$ 的值的限制在于 $a_{i+1}$ 而 $a_i$ 的改变对于 $a_{i+1}$ 无影响，所以我们倒序遍历。

考虑每一个数字应该分几次？我们知道任意一个 $a_{i}$ 最后分出来的数一定不会大于 $a_{i+1}$，那我们不妨使每一次选择的 $x$ 都为 $a_{i}-a_{i+1}$ 这样子我们一共可以分出 $\frac{(a_{i}+a_{i+1}-1)}{a_{i+1}}$ 个数字，这个式子是向上取整的（式子写法本身具有向上取整的作用）。因为我们答案询问的是分割次数，所以要再 $-1$。

```
ans+=(a[i]+a[i+1]-1)/a[i+1]-1
```

那么其中所有分割方案中最小值最大的一种是什么呢？易得均分是使其最大的方案，而最小值就是总数除以段数也就是 $a_i\div(\frac{a_i+a_{i+1}-1}{a_{i+1}})$。

```
a[i]=a[i]/((a[i]+a[i+1]-1)/a[i+1])
```

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[200010];
long long ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		ans=0;
		for(int i=n-1;i>=1;i--){
			if(a[i]>a[i+1]){
				ans+=(a[i]+a[i+1]-1)/a[i+1]-1;
				a[i]=a[i]/((a[i]+a[i+1]-1)/a[i+1]);
			}
		}
		cout<<ans<<endl;
	}
}
```

update：

23.12.19：修改了数字没有使用 $\LaTeX$ 公式，中文全角标点，说明向上取整的是式子本身而非运用数学运算符。

---

