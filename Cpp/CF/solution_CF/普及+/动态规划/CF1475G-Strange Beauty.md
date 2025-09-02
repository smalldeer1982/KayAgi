# Strange Beauty

## 题目描述

Polycarp found on the street an array $ a $ of $ n $ elements.

Polycarp invented his criterion for the beauty of an array. He calls an array $ a $ beautiful if at least one of the following conditions must be met for each different pair of indices $ i \ne j $ :

- $ a_i $ is divisible by $ a_j $ ;
- or $ a_j $ is divisible by $ a_i $ .

For example, if:

- $ n=5 $ and $ a=[7, 9, 3, 14, 63] $ , then the $ a $ array is not beautiful (for $ i=4 $ and $ j=2 $ , none of the conditions above is met);
- $ n=3 $ and $ a=[2, 14, 42] $ , then the $ a $ array is beautiful;
- $ n=4 $ and $ a=[45, 9, 3, 18] $ , then the $ a $ array is not beautiful (for $ i=1 $ and $ j=4 $ none of the conditions above is met);

Ugly arrays upset Polycarp, so he wants to remove some elements from the array $ a $ so that it becomes beautiful. Help Polycarp determine the smallest number of elements to remove to make the array $ a $ beautiful.

## 说明/提示

In the first test case, removing $ 7 $ and $ 14 $ will make array $ a $ beautiful.

In the second test case, the array $ a $ is already beautiful.

In the third test case, removing one of the elements $ 45 $ or $ 18 $ will make the array $ a $ beautiful.

In the fourth test case, the array $ a $ is beautiful.

## 样例 #1

### 输入

```
4
5
7 9 3 14 63
3
2 14 42
4
45 9 3 18
3
2 2 8```

### 输出

```
2
0
1
0```

# 题解

## 作者：Cutest_Junior (赞：13)

## 题解 CF1475G 【Strange Beauty】

### 题意

+ 有 $n$ 个数 $a$；
+ 选取子集，要求子集内任意两个数 $a_i,a_j$ 都有 $a_i|a_j$ 或 $a_j|a_i$；
+ 求最大子集的大小；
+ $n,a\le2\times10^5$。

### 做法

最容易想到的做法是先把所有数排序，设 $dp_i$ 表示以第 $i$ 个数为最大数的最大集合大小，$O(N^2)$dp，显然超时。

然后 Virtual participation 时候我只想到上面的做法，果然我还是太菜了。

接下来想想怎么优化。

因为每个数的状态只可能由它的因数转移过来，而枚举因数的复杂度是 $O(\sqrt{N})$ 的，所以可以设 $dp_i$ 为以 $i$ 为最大数（注意和上一个做法的区别）的最大集合的大小，总复杂度 $O(N\sqrt{N})$，可过本题。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int arr[N];
int dp[N];

void run() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	sort(arr + 1, arr + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j * j <= arr[i]; ++j) {
			if (arr[i] % j == 0) {
				dp[arr[i]] = max(dp[arr[i]], max(dp[j], dp[arr[i] / j]));
			}
		}
		++dp[arr[i]];
		ans = max(ans, dp[arr[i]]);
	}
	printf("%d\n", n - ans);
	memset(dp, 0, sizeof dp);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

### 再优化

然后发现时间 3462ms，跑得飞慢（~~当然也不排除我人傻常数大~~）。

可以想到每个数的倍数均摊 $O(\log N)$，而因数却是 $O(\sqrt{N})$ 级别的，所以我们可以对每个数往后转移，可以减少很多不必要的计算。

期望复杂度 $O(N\log N)$。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int arr[N];

int dp[N];

void run() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	sort(arr + 1, arr + n + 1);
	memset(dp, 0, sizeof dp);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		++dp[arr[i]];
		ans = max(ans, dp[arr[i]]);
		for (int j = arr[i] + arr[i]; j < N; j += arr[i]) {
			dp[j] = max(dp[j], dp[arr[i]]);
		}
	}
	printf("%d\n", n - ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

Time limit exceeded on test 7

？？？

### 再再优化

复杂度不是更优了吗？怎么会 TLE？？？

我们看到之前的一句话：

> **期望**复杂度 $O(N\log N)$。

只有当数据随机时才是 $O(N\log N)$。

那什么时候不能过呢？

考虑如果有 $n$ 个 $2$，那复杂度是——

$$\Huge{O(N^2)}$$

把你人都整傻掉。

那这样要怎么优化呢？

我们发现其实是有了很多重复的计算，那可不可以把所有数丢进一个桶，设 $dp_i$ 表示以第 $i$ 个数为最大数的最大集合大小（然后发现优化着优化着又优化回去了）。

复杂度 $O(N\log N)$，421ms，跑得飞快。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int arr[N];

int dp[N];

void run() {
	int n;
	scanf("%d", &n);
	memset(arr, 0, sizeof arr);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		++arr[x];
	}
	memset(dp, 0, sizeof dp);
	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		dp[i] += arr[i];
		ans = max(ans, dp[i]);
		for (int j = i + i; j < N; j += i) {
			dp[j] = max(dp[j], dp[i]);
		}
	}
	printf("%d\n", n - ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：pengyule (赞：2)

- 【算法】数论，DP
- 【题解】注意观察的同学会发现，$a_i$ 的范围是 $\le 2\cdot10^5$，这是我们的一个突破口。首先我们来看一看，一个 beautiful 的序列有什么性质。显然，将此序列由小至大排序后，$a_i$ 应该是 $a_1,a_2,\cdots,a_{n-1}$ 的倍数。那么题意就被简化为：要想最终的序列排序后满足每个数是它前面所有的数的倍数最少删掉多少数。我们暂且考虑最后的序列最多能有多少数，这是等价的。设置状态：令 $f_{a_i}$ 表示以 $a_i$ 为最终序列的最大数时，最终的序列最多有多少个数。我们可以枚举 $a_i$ 的所有因数（记为 $b_{1\sim m}$），取 $\max_{j=1}^{m} f_{b_j}$，这就是最终序列中除了 $a_i$ 外的数的数量，则 $f_{a_i}=\max_{j=1}^{m} f_{b_j}+1$。这样做是可行的，因为一个数除它本身的所有因数一定是小于它的，即 $f_{b_{1\sim m}}$ 是已经求好的。同时我们也发现应该按 $a_i$ 从小到大的顺序来求 $f_{a_i}$。
- 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005],f[200005];
int main()
{
    ios::sync_with_stdio(false); //题目有点卡常
    int T,n;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        memset(f,0,sizeof(f)); //注意清零
        sort(a+1,a+n+1);
        int ans=1;
        for(int i=1;i<=n;i++){
            if(f[a[i]]) f[a[i]]++; 
            else {
            	//注意这里不能先f[a[i]=1，后面再f[a[i]]+=Mx
                //因为j=1时后面的f[a[i]/j]会用到f[a[i]]，导致重复
                int Mx=0;
                for(int j=1;j<=(int)(sqrt(a[i]));j++)
                    if(a[i]%j==0)
                        Mx=max(Mx,max(f[j],f[a[i]/j]));
                f[a[i]]=Mx+1;
            }
            ans=max(ans,f[a[i]]);
        }   
        cout<<n-ans<<endl;
    }
    return 0;
}
```

---

## 作者：zjjws (赞：2)

其实做法本身并不难想，但是好像很多人因为实现方法导致常数极大，就想安利一波自己的写法。

目前为止还是最优解。

很显然的 DP，因为值域很小就可以直接用桶计数，然后转移。

DP 的写法有两种：

- 正序，用当前去更新自己的倍数。

- 倒序，去自己的因数里找到最大值。

在这里，显然是正序要更好一些，考虑一下我们实际在做什么事情：将一个数质因数拆分，正序就是选择一个质因子将其次数加 $1$，然后把值传递过去，而倒序是选择一个质因子将其次数 $-1$，然后把值拿过来。

那么很显然，正序能避免一些无用计算。

同时，枚举所有的 **质因子** 就可以不遗漏状态，而不需要将所有倍数枚举过去。

枚举倍数就是 $\operatorname O(n\log n)$ 的，质因数的话虽然差不多是同阶的，但是也能快不少。

---

我一开始想的是建图，然后发现如果枚举倍数的话，会有大量无用的边，于是就想到了只连 **质因数次数减 $1$** 的边。最后写代码的时候也并没有真的建图，因为没有必要。

---


```cpp
const int N=2e5+3;

bool pri[N];
int prime[N];
int cutt;
inline void init()
{
    for(int i=2;i<N;i++)
    {
        if(!pri[i])prime[++cutt]=i;
        for(int j=1;j<=cutt;j++)
        {
            int now=i*prime[j];
            if(now>=N)break;
            pri[now]=true;
            if(i%prime[j]==0)break;
        }
    }
    return;
}

int a[N];
int b[N];
int f[N];
inline void work()
{
    int n=rin();
    memset(b,0,sizeof(b));
    memset(f,0,sizeof(f));
    int maxs=0;
    int ans=0;
    for(int i=1,x;i<=n;i++)b[(x=rin())]++,maxs=max(maxs,x);
    for(int i=1;i<=maxs;i++)
    {
        f[i]+=b[i];
        ans=max(ans,f[i]);
        if(f[i])
        {
            for(int j=1;j<=cutt;j++)
            {
                int now=i*prime[j];
                if(now>maxs)break;
                f[now]=max(f[now],f[i]);
            }
        }
    }
    printf("%d\n",n-ans);
    return;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 题意

注意：别误解了，$x|y$ 表示 $x$ 整除 $y$（我以为是按位或，看来学傻了）

## 思路

首先我不会做，于是就~~点开了题解~~看了CF标签。哦，dp啊……

我一开始粗暴的想，$dp[i]$ 表示以 $a[i]$ 为最小数的满足条件的集合。然后得到了转移方程，时间复杂度 $O(n^2)$。一看数据范围，崩溃了（

然后我想优化，想了半天发现可以改变思路，$dp[i]$ 表示以 $a[i]$ 为**最大数**的满足条件的集合。因为对于任意的 $x,y$ 有 $x|y$ 或 $y|x$，所以我们枚举 $j$ 使得 $j|a[i]$，这样的话 $dp[i]$ 就可以由 $dp[j]$ 转移而来。又因为 $dp[j]$ 这个集合已经满足条件，所以它加上 $i$ 这个元素一定满足条件。

枚举因数只需要枚举到 $\sqrt{n}$ 所以总复杂度为 $O(n \sqrt{n})$。 （不需要判断是否在集合中，因为我初始化的时候不在集合里的赋成 0 ，在集合里的赋成 1 了）

那么这道题就被切掉了。一节课就这么过去了（

## 状态转移方程

$dp[i] = dp[j] + 1 (j|a[i])$

$dp[j]+1$ 表示以 $j$ 为最大数的满足条件的集合最大长度加上 $i$ 这一个元素后的的长度。

## 代码

您的代码已到货，如有问题请联系我退换（

```cpp
#include <bits/stdc++.h>
#define rint register int
using namespace std;
template<typename Typ>Typ qmax(Typ a,Typ b){return a>b?a:b;}
int read() //快读，可以换成 cin
{
	char ch=getchar(); int w=0,f=1;
	for(;!isdigit(ch);ch=getchar())if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar())w=(w<<1)+(w<<3)+(ch^48);
	return w*f;
}
int a[200005],dp[200005];
int main()
{
	int T=read();
	while(T--)
	{
		memset(dp,0,sizeof(dp)); //记得初始化
		int n=read(),maxn=-1;
		for(rint i=1;i<=n;i++)
		{
			a[i]=read();
			dp[a[i]]=1; //在集合里的元素赋成1（自己想想就会懂的）
		}
		sort(a+1,a+1+n); //排序，从小到大 dp
		for(rint i=1;i<=n;i++)
			for(rint j=1;j*j<=a[i];j++) //枚举因数
				if(a[i]%j==0)
       					dp[a[i]]=max(max(dp[j]+1,dp[a[i]/j]+1),dp[a[i]]); //每次处理一对因数
		for(rint i=1;i<=n;i++)
			maxn=max(maxn,dp[a[i]]); //求最大值
		printf("%d\n",n-maxn+1); //因为是要被移走的所以用 n 减一下即可。
	}
	return 0;
}
```

$$\large{\texttt{---------------------------THE END---------------------------}}$$

感谢您的观看！

---

## 作者：do_while_true (赞：1)

# [G](https://codeforces.com/contest/1475/problem/G)

### $\mathcal{Translate}$

给定一个长度为 $n$ 的序列 $a$，询问它至少要删除几个数使得它成为一个好的序列。

定义一个好的序列：这个序列中的任意两个数是整除或被整除关系。

### $\mathcal{Solution}$

首先排下序，不影响答案。考虑到一个成为一个好的序列的充分必要条件是这个序列的相邻两个满足 $a_i | a_{i+1}$，正确性显然。

设 $f_i$ 代表考虑前 $i$ 个并且选 $i$，要成为一个好的序列最少删多少数。

有 $f_i = \min \{f_{pos_j} + i - pos_j - 1\}$，其中 其中 $j$ 是 $i$ 的约数, $pos_j$ 代表 $j$ 最后出现的位置。

直接 $dp$ 即可，时间复杂度 $\mathcal{O}(n\sqrt{a})$

### [$\mathcal{Code}$](https://codeforces.com/contest/1475/submission/105840354)


---

## 作者：I_am_Accepted (赞：1)

这肯定是思路最简短的题解。

### 题意简述

求一个数集的最大子集使得子集中两两呈倍数关系。

### 题目分析

先对原序列 $\{a\}$ 排序。

容易发现：

子集满足子集中两两呈倍数关系 $\iff$ 子集中数里值的大小相邻的两数呈倍数关系

比较绕，举个栗子：

![](https://i.loli.net/2021/10/02/Xw7JnCdc1v4xtGM.png)

#### Proof_start

**充分性：**

因为任意两数呈倍数关系，所以值的大小相邻的两数呈倍数关系。

**必要性：**

设子集里的数分别为：

$$b_1\leqslant b_2\leqslant b_3\leqslant \dots \leqslant b_k$$

因为值的大小相邻的两数呈倍数关系，所以：

$$b_i \ | \ b_{i+1} \quad (1\leqslant i\leqslant k-1)$$

由于**整除的传递性**，对于任意的 $1\leqslant i<j\leqslant k$，均有：

$$b_i \ | \ b_{i+1} \ | \ b_{i+2} \ | \ b_{i+3} \ | \ \dots  \ | \ b_j$$

即 $b_i \ | \ b_j$，原命题得证。

#### Proof_end

所以将 $\{a\}$ 顺序遍历，记录下每一种值 $x$ 出现的最后位置 $pos_x$（若没出现记为 $0$）同时更新 $ans_i$ 表示以 $a_i$ 为最大值的满足题意子集的最大大小。

$ans$ 的更新：

$$ans_i=\max(ans_{pos_j}+1) \quad (j \ | \ i)$$

最后输出 $\max(ans_i) \quad (1\leqslant i\leqslant n)$ 即可。

### Talk is cheap,show me the code.

[Codeforces Status](http://codeforces.com/contest/1475/submission/130529487)

```cpp
int n;
int a[N];
int pos[N];
int ans[N];
int out;
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	sort(a+1,a+1+n);
	For(i,0,N-1) pos[i]=0;
	For(i,1,n){
		ans[i]=0;
		for(int x=1,y;x*x<=a[i];x++){
			if(a[i]%x) continue;
			y=a[i]/x;
			ckmx(ans[i],ans[pos[x]]+1);
			ckmx(ans[i],ans[pos[y]]+1);
		}
		pos[a[i]]=i;
	}
	out=0;
	For(i,1,n) ckmx(out,ans[i]);
	cout<<n-out<<endl;
}
```

---

## 作者：lin_rany (赞：0)

## CF1475G Strange Beauty
题目链接:[CF1475G Strange Beauty](https://www.luogu.com.cn/problem/CF1475G)

题目大意:给定一个数组，求最少删去多少个数，使得剩下的所有元素互相整除。

数据范围:$1\le t\le 10,1\le n\le2*10^5,1\le a[i]\le 2*10^5$

题解:采取$dp$方法，$dp[i]$表示以$i$为最小元素的情况下，能最大包含多少元素。转移就是$dp[i]=(\mathop{max}\limits_{i|j} dp[j])+num[i]$

时间复杂度:$O(nlogn)$

AC代码:
```cpp
#include<bits/stdc++.h>

#define ld long double
#define ll long long
using namespace std;
template<class T>
void read(T& x)
{
	T res = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')f = -1; c = getchar();
	}
	while (isdigit(c)) {
		res = (res << 3) + (res << 1) + c - '0'; c = getchar();
	}
	x = res * f;
}
const ll N = 200000 + 10;
const int mod = 1e9 + 7;
int t, a[N],n,num[N],dp[N];
int mx = 200000;

int main()
{
	//ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif // ONLINE_JUDGE
	read(t);
	while (t--)
	{
		for (int i = 1; i <= mx; i++)num[i] = 0,dp[i]=0;
		read(n); 
		for (int i = 1; i <= n; i++)
		{
			read(a[i]); num[a[i]]++;
		}
		int ans = 0;
		for (int i = mx; i >=1; i--)
		{
			if (num[i] == 0)continue;
			dp[i] = num[i];
			for (int j = 2; j * i <= mx; j++)
			{
				dp[i] = max(dp[i], dp[i * j] + num[i]);
			}
			ans = max(ans, dp[i]);
		}
		printf("%d\n", n - ans);
		
	}

	return 0;
}

```

---

## 作者：ZSH_ZSH (赞：0)

[博客园食用效果更佳](https://www.cnblogs.com/ZHANG-SHENG-HAO/p/14332359.html)

题目大意：有 $n$ 个数，从中挑选一个子集，使得集合中任意两个不同的数 $x,y$ ， 有 $x|y$ 或 $y|x$

我们发现，集合中必然存在一个数 $x$ ，使得集合中其他数都是 $x$ 的因数

所以我们只需统计每个数的因数在原数组里的出现次数即可

这里 $a_i \leq 2*10^5 $，可以预处理出每个数的因数

代码：

```
#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline ll read()
{
	ll sum=0,f=0;char c=getchar();
	while (!isdigit(c)) f|=(c=='-'),c=getchar();
	while (isdigit(c)) sum=(sum<<1)+(sum<<3)+(c^48),c=getchar();
	return f?-sum:sum;
}

const int N=200010;
int n,a[N],f[N],cnt[N];
vector<int>fac[N];

inline void init(int size)
{
	rep(i,1,size)
	{
		int x=i<<1;
		while (x<=size) fac[x].push_back(i),x+=i;
	}
}

inline void solve()
{
	memset(cnt,0,sizeof(cnt)),memset(f,0,sizeof(f));
	int mx=0;
	n=read();rep(i,1,n) a[i]=read(),cnt[a[i]]++,mx=max(mx,a[i]);
	int ans=n;
	rep(i,1,mx) if (cnt[i])
	{
		f[i]=cnt[i];
		rep(j,0,(int)fac[i].size()-1)
		{
			if (cnt[fac[i][j]]) f[i]=max(f[i],f[fac[i][j]]+cnt[i]);
		}
		ans=min(ans,n-f[i]);
	}
	cout<<ans<<endl;
}

int main()
{
	init(N-10);
	drep(T,read(),1) solve();
}
```


---

