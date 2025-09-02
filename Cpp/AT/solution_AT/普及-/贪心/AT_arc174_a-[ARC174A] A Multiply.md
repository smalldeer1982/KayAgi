# [ARC174A] A Multiply

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc174/tasks/arc174_a

長さ $ N $ の整数列 $ A=(A_1,A_2,\dots,A_N) $ と整数 $ C $ が与えられます。  
 以下の操作を **高々 $ 1 $ 度** 行って達成できる $ A $ の全要素の総和の最大値を求めてください。

- $ 1\ \le\ l\ \le\ r\ \le\ N $ を満たす整数 $ l,r $ を指定し、 $ A_l,A_{l+1},\dots,A_r $ の全ての要素を $ C $ 倍する。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ -10^6\ \le\ C\ \le\ 10^6 $
- $ -10^6\ \le\ A_i\ \le\ 10^6 $
 
### Sample Explanation 1

この入力では、 $ A=(-10,10,20,30,-20),\ C=2 $ です。 $ l=2,r=4 $ と指定して操作を $ 1 $ 度行うことで、操作後の $ A $ を $ (-10,20,40,60,-20) $ とすることができます。 このとき $ A $ の全要素の総和は $ 90 $ となり、これが達成可能な最大値です。

### Sample Explanation 2

この入力では、 $ A=(-1,-2,-3,-4,-5),\ C=1000000 $ です。 操作を一度も行わないとき $ A $ の全要素の総和は $ -15 $ となり、これが達成可能な最大値です。

## 样例 #1

### 输入

```
5 2
-10 10 20 30 -20```

### 输出

```
90```

## 样例 #2

### 输入

```
5 1000000
-1 -2 -3 -4 -5```

### 输出

```
-15```

## 样例 #3

### 输入

```
9 -1
-9 9 -8 2 -4 4 -3 5 -3```

### 输出

```
13```

# 题解

## 作者：___Furina___ (赞：6)

分别考虑 $c$ 的正负性：

- 当 $c$ 为正数，我们肯定是想把最大子段和乘上 $c$，可以让总和最大。

证明：

设最大子段和为 $maxn$，数组总和为 $sum$，目前答案为 $ sum-maxn+maxn\times c=sum+maxn\times(c-1)$。

假设再加入一个数 $p$ 更优，则答案为 $sum-maxn-p+(maxn+p)\times c=sum+(maxn+p)\times (c-1)$。

因为我们假设加入 $p$ 更优，所以 

$sum+maxn\times(c-1)<sum+(maxn+p)\times (c-1)$ 

化简后，得 $maxn<maxn+p$，但是 $maxn$ 是最大子段和，与结论相悖。

所以把最大子段和乘上 $c$ 最优。

- 当 $c$ 为负数，我们肯定是想把最小子段和乘上 $c$，可以让总和最大，证明方法如上。

至此，我们可以开始编码代码了，求解最大 $/$ 最小字段和类比[最大字段和](https://www.luogu.com.cn/problem/P1115)，但是还要注意两个细节：
1. 可能不进行操作更优；
1. 记得开 $long long$。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define N 300010
int maxn=-1e16,ans,suma,sumb,minn=1e16,c,sum;
signed main(){
	int n;
	cin>>n>>c;
	for(int i=1,x;i<=n;i++){
		cin>>x,suma=max(suma+x,x),sumb=min(sumb+x,x),sum+=x;
		maxn=max(maxn,suma),minn=min(minn,sumb);
	}
	cout<<max(sum,max(maxn*c+sum-maxn,minn*c+sum-minn));
	return 0;
}
```
完结撒花（作者的第一篇题解）。

---

## 作者：qw1234321 (赞：3)

前置知识：最大子段和。

~~什么？你不会？出门左转 [P1115](https://www.luogu.com.cn/problem/P1115)。~~

首先有个很显然的性质，当 $c$ 是正数时，选取最大子段和乘在上面即可，反之，选取**最小子段和**乘在上面即可，这样做一定会使结果最大化。

当然和 P1115 不一样的点是选出来的子段可以为空。

所以若 $c \gt 0$，但最大子段和小于 $0$，选空段。

同理若 $c \lt 0$，但最小子段和大于 $0$，选空段。

分类讨论 $c$ 的大小即可。

[code](https://atcoder.jp/contests/arc174/submissions/51392019)

说句闲话：十年 OI 一场空，不开 long long 见祖宗。

---

## 作者：zzhbpyy (赞：2)

### [原题传送门](https://www.luogu.com.cn/problem/AT_arc174_a)

## 思路

我们直接对 $C$ 的正负性进行讨论：

- $C>0$，只需找出序列中区间和最大且大于零的子区间，因为只有让最大正区间翻倍才能让答案最优。

- $C\leq0$，只需找出序列中区间和最小且小于零的子区间，因为只有让最小负区间变成正的才能答案最优。

对于区间和最值问题，只需要简单线性 dp 即可。转移方程为：$dp_{i}=\max(dp_{i-1},0)+a_{i}$ 或 $dp_{i}=\min(dp_{i-1},0)+a_{i}$。

注意特判最大或最小区间和的正负性，不能让答案更优就不改变。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ch,c,a[300005],dp[300005],ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>a[i];
        ch+=a[i];
	}
    if(c>0){
		for(int i=1;i<=n;i++){
			dp[i]=max(dp[i-1],0LL)+a[i];
			ans=max(ans,dp[i]);
		}
	}
	else{
		for(int i=1;i<=n;i++){
			dp[i]=min(dp[i-1],0LL)+a[i];
			ans=min(ans,dp[i]);
		}
	}
	cout<<ch+(c-1)*ans;
	return 0;
}
```

---

## 作者：zfx_VeXl6 (赞：1)

容易发现对区间 $[l,r]$ 进行修改后，序列的总和从 $A_1+A_2+\dots+A_{n-1}+A_n$ 变成了 $A_1+A_2+\dots+A_{l-1}+C\times\sum\limits_{i=l}^rA_i+A_{r+1}+\dots+A_{n-1}+A_n$，总和增加了 $(C-1)\times\sum\limits_{i=l}^rA_i$。

因此，当 $C>0$ 时，需要最大化 $\sum\limits_{i=l}^rA_i$，反之，需要最小化 $\sum\limits_{i=l}^rA_i$。于是就可以转化为最大（小）子段和。

注意特判当 $(C-1)\times\sum\limits_{i=l}^rA_i<0$ 时不能进行操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const int N=3e5+5;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
int n;
LL a[N],f[2][N],s[2],c,sum,k; //s[0] 是最大子段和，s[1] 是最小子段和
int main() {
    cin>>n>>c;
    s[0]=-INF;
    s[1]=INF;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        sum+=a[i];
        f[0][i]=max(a[i],f[0][i-1]+a[i]);
        f[1][i]=min(a[i],f[1][i-1]+a[i]);
        s[0]=max(s[0],f[0][i]);
        s[1]=min(s[1],f[1][i]);
    }
    if(c>0)
        k=(c-1)*s[0];
    else
        k=(c-1)*s[1];
    if(k<0)
        cout<<sum;
    else
        cout<<sum+k;
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

不妨设选定操作的区间为 $[l, r]$，这一段的和为 $s$。

如果 $c > 0$，则相对于原来的数组来说，操作后的和增加了 $(c - 1) \times s$。我们期望选择最大的 $s$ 来获得最大的增量。很显然我们需要求最大子段和。

如果 $c < 0$，则相对于原来的数组来说，操作后的和减少了 $(|c| + 1) \times s$。我们希望是 $s$ 为负数并且最小，这样就能获得最大的增量。

综上，我们需要根据 $c$ 的正负，求最大 / 最小子段和。求最大 / 最小子段和可以 dp。复杂度显然线性。[submission](https://atcoder.jp/contests/arc174/submissions/51386213)。

---

## 作者：x1489631649 (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc174_a)
# 输入
1. 两个数 $n$ 和 $k$。
1. 一串数 $a_1 \sim a_n(-10^6 \le a_i \le 10^6)$。 
# 输出
这串数字在一次操作后的最大值。
# 题意
选取一段连续的区间，乘 $k$ 使得这串数字在操作后最大。
# 分析
- 当 $0 > k$ 时，选择最大子段和，因为乘积在 $k$ 一定是尽可能选大的能让和增加，如果最大字段和也小于零时，那么不乘 $k$ ， 此时结果最大。
- 当 $k \le 0$ 时，选择最小子段和，同上，负负得正，所以加起来和会变大。


 **建议参考[P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)**。
 # $Code$
 ```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+50;
long long c,a[N],s,f[N];
int main()
{
	int n,c;
	cin>>n>>c;
	for(int i=1;i<=n;i++)
		cin>>a[i],s+=a[i];
	if(c>0)
	{
		long long ans=-1e9;
		for(int i=1;i<=n;i++)
		{
			f[i]=max(f[i-1]+a[i],a[i]);
			ans=max(ans,f[i]);
		}
		cout<<max(s+ans*(c-1),s);
	}
	else {
		long long ans=1e9;
		for(int i=1;i<=n;i++)
		{
			f[i]=min(f[i-1]+a[i],a[i]);
			ans=min(ans,f[i]);
		}	
		cout<<max(s+ans*(c-1),s);
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：1)

~~看了前面大佬的题解本人觉得讲的不太清晰，于是就发了一篇史上最清晰的题解~~ ^_^

拿到一道题先看数据范围

$ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $ 

只有两种时间复杂度

- $\operatorname{O}(n\operatorname{log}n)$
- $\operatorname{O}(n)$

二分的题一般都是最大值最小，最小值最大，并且要满足单调性，但这道题明显不存在单调性，所以第一种时间复杂度排除。

接下来就到了最重要的部分，正解！！

根据题目可以发现有如下公式：

$A_l \times (c-1)+A_{l+1} \times (c-1)+A_{l+2} \times (c-1)......+A_r \times (c-1)+sum$ 就是选了这个区间后整个数组的值（$sum$ 表示原数组的总和）。

用分配律倒着求，就变成了：

$$
(A_l+A_{l+1}+A_{l+2}......+A_r) \times (c-1)+sum
$$

由于 $c$ 和 $sum$ 是固定的，所以我们只需要使 $(A_l+A_{l+1}+A_{l+2}......+A_r)$ 的最大值就能使答案最大。参考[P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)。

这里简单讲一下[P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)的思路：

那道题可以用动态规划的方法求出答案，$f_i$ 表示以 $i$ 为结尾的最大子段和。对于每一个 $f_i$，它都有两种选择，

- 接着上一个，$f_i = f_{i-1}+a_i$
- 自己自立门户，从自己开始，$f_i = a_i$

那状态转移就是 $f_i = \max(f_{i-1}+a_i,a_i)$。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main()
{
    int a[200005];
    int f[200005];
    int ans = INT_MIN;//这里求最大值千万不能设置为0，因为f数组可能全是负数
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        f[i] = max(f[i-1]+a[i],a[i]);
        ans = max(ans,f[i]);
    }
    printf("%d",ans);
    return 0;
}
```

**注意：如果 $c \le 0$ 就要求 $(A_l+A_{l+1}+A_{l+2}......+A_r)$ 最小值，因为再大的正整数乘负数也会变得超小，顺带一提，题目的第二个样例是不操作最大的，所以，在输出的时候操作的结果要和不操作的结果取最大值，最后，一定要开long long。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 3e5+5;
int a[N];
int f[N];//最大子段和数组
int dp[N];//最小子段和数组
signed main()
{
    int ans = INT_MIN;//最大子段和的变量
    int num = INT_MAX;//最小子段和的变量
    int sum = 0;//原始数组的和
    int n,c;
    scanf("%lld %lld",&n,&c);
    for(int i = 1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        f[i] = max(f[i-1]+a[i],a[i]);//可以接上，可以从头
        ans = max(ans,f[i]);//记录最大值
        dp[i] = min(dp[i-1]+a[i],a[i]);//可以接上，可以从头
        num = min(num,dp[i]);//记录最小值
        sum+=a[i];//加上
    }
    if(c>0)//c>0就最大子段和
    {
    	printf("%lld",max(sum+ans*(c-1),sum));//sum+ans*(c-1)就是思路上的改变公式，sum就是不修改的结果
	}
	else//否则最小子段和
	{
		printf("%lld",max(sum+num*(c-1),sum));//sum+num*(c-1)也是思路上的改变公式，但求的是最小子段和，所以变成了num，sum就是不修改的结果
	}
    return 0;
}
```

---

## 作者：Magus (赞：0)

Water.

前置芝士：[最大子段和](https://www.luogu.com.cn/problem/P1115)。

注意，$C$ 有可能为负，还可能为 $0$。

那我们分类讨论。

$C \times  \begin{cases}最大子段和 &\text{if } C \geq 1 \\最小子段和 &\text{if } C \leq 0&\end{cases}$

Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e7+10;
const int mod=80112002;
int n,m,cnt,ans=-100000000,ans2=100000000,arr[maxn],dp[maxn],f[maxn];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>arr[i];
	}
	for(int i=1;i<=n;i++)
	{
		dp[i]=max(dp[i-1]+arr[i],arr[i]);
		ans=max(ans,dp[i]);
		f[i]=min(f[i-1]+arr[i],arr[i]);
		ans2=min(ans2,f[i]);
		cnt+=arr[i];
	}
	if(m>=1)cout<<max(cnt+ans*(m-1),cnt);
	else cout<<max(cnt+ans2*(m-1),cnt);
	return 0;
  IAKIOI
}

```

---

## 作者：YXD123456789 (赞：0)

赛时过的

先求一次 $ Sum $。

当 $ C > 0 $ 时，找最大子段和，记作 $ K $ ， $ Ans = max(Sum , Sum - K + K \times C) $。

当 $ C \leq 0 $ 时，找最小子段和，操作与上面相同。

输出 $ Ans $ 即可。

[code](https://atcoder.jp/contests/arc174/submissions/51387825)

---

## 作者：Dtw_ (赞：0)

# A - A Multiply
[atcoder](https://atcoder.jp/contests/arc174/tasks/arc174_a)

## 题目大意
给定长为 $N$ 的序列 $A = (A_1,A_2,…,A_N)$ 和一个整数 $C$，任选一个区间 $[l,r]$ 使这个区间所有的数乘上 $C$，最大化这个序列的和。

## 思路
比较暴力的思路：

（在此我只说 $C$ 是正数的情况，如果 $C$ 是负数那么把取最大改成取最小即可）我们希望把正数乘，负数不乘，那么现在的问题就在于如何求最大的正数区间。但仔细一想一个区间内他的区间和为正也可以，那么我们如何去求区间和最大值呢？

暴力是很好想的，$N^2$ 枚举 $l,r$ 然后算一下答案最后取最大，但是显然不可过，所以考虑优化

首先对于 $A$ 做一个前缀和 $S$，随后对于 $S$ 做前缀最小值 $mins$（是个变量名）这样我们存储了当前 $[1,i]$ 的区间值，然后又存储了 $[1,i]$ 的最小值，我们知道当前的减掉最小的一定是比其余情况优的，然后遍历一遍把对于每个点的答案取最大值，而这是 $O(N)$ 的所以可以通过。当然这是对于 $C>0$ 的情况，相反，$C<0$ 的话把上述最大值改为最小值，最小值改为最大值即可。

## 实现
至于实现的话，赛时写的比较抽象，现在优化了一下。
## Code
[赛时，比较简单易懂](https://atcoder.jp/contests/arc174/submissions/51390664)

[赛后，推荐看这个](https://atcoder.jp/contests/arc174/submissions/51441179)

---

## 作者：Suare_Pi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc174_a)


### 题目大意
有一个长度为 $N$ 的数列 $ A=(A_1,A_2,\dots,A_N) $ 和一个整数 $C$。

选择两个整数 $l,r$，且 $ 1\ \le\ l\ \le\ r\ \le\ N $，

将 $A_i$ 到 $A_j$ 每一项同时乘以 $C$。

求修改后数列 $A$ 所有项相加的和的最大值。

### 思路
求所有项相加，考虑使用前缀和。

观察样例可知，$C$ 有三种可能：

1. $C<1$，显然要选子段和最小的一个序列，因为负负得正；
2. $C=1$，显然不用选，因为一个数乘 $1$ 肯定不变；
3. $C>1$，显然要选子段和最大的一个序列；

具体内容在代码注释里。

求出最大区间和或最小区间和（使用 $t$ 表示）后，最大值即为 $t\times(C-1)+sum_n$。

可以想想为什么是 $C-1$。



### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
long long t,n,c,a[N],sum[N],minn,maxx;
int main()
{
	cin >> n >> c;
	for(int i=1;i<=n;i++)//输入+前缀和 
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}

	if(c==1)//特判 
	{
		cout<<sum[n]<<endl;
		return 0;
	}

	if(c>1)
	{
		for(int i=1;i<=n;i++)
		{
			minn=min(minn,sum[i]);
			t=max(t,sum[i]-minn);//最大区间和 
		}
		cout<<t*(c-1)+sum[n]<<endl;
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			maxx=max(maxx,sum[i]);
			t=min(t,sum[i]-maxx);//最小区间和  
		}
		cout<<t*(c-1)+sum[n]<<endl;
	}
	return 0;
}
```

---

## 作者：zhu_wen (赞：0)

# Multiply
## 题意
本题就是让你找到一个区间，使他乘上 $c$，让序列最大。
## 解法
根据题意我们可以想到，本题为分类讨论：

- 当 $x \le 0$ 时。

我们求出最小子序列，让他乘上 $c$ 能够使序列最大。
- 当 $x >  0$ 时。

我们求出最小子序列，让他乘上 $c$ 能够使序列最大。

但要注意，还有可能，没有操作的情况，就是当 $x \le 0$ 时，最小值大于 $0$ 或者当 $x >  0$ 时，最大值小于 $0$，这样的话我们就不需要操作，因此我们可以再求最大或最小子序列时通过 $0$ 来控制一下。

`ans = min(min(ans, b[i]), 0ll); ans = max(0ll, max(ans, b[i]));`

这就是做特判的地方。

最后将序列和减去字段和，加上字段和乘上 $c$ 就是本题的答案。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define lowbit(x) x & -x
#define fup(x, l, r) for (int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (int x = (r), eNd = (l); x >= eNd; -- x )
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct fastread {
	template <typename T>
	fastread& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	fastread& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct fastwrite {
	template <typename T>
	fastwrite& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	fastwrite& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	fastwrite& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

int n, c;
int a[N], b[N];
int ans; 
 
main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fin >> n >> c;
	fup(i, 1, n)	fin >> a[i], ans += a[i];
	if(c <= 0)
	{
		fup(i, 1, n)
		{
			if(i == 1)	b[i] = a[i];
			b[i] = min(b[i - 1] + a[i], a[i]);
			ans = min(min(ans, b[i]), 0ll);
		}
	}
	else
	{
		fup(i, 1, n)
		{
			if(i == 1)	b[i] = a[i];
			b[i] = max(b[i - 1] + a[i], a[i]);
			ans = max(0ll, max(ans, b[i]));
		}
	}
	int sum = 0;
	fup(i, 1, n)
	{
		sum += a[i];
	}
	sum -= ans;
	sum += ans * c;
	fout << sum << '\n';
	return 0;
}
```

代码可能有些抽象，请谅解。

---

## 作者：Jerry_heng (赞：0)

（一）

注意到，$c$ 可能 $<1$。

主要考虑操作后的变化量。

- 当 $c=1$ 时，不会改变序列。

- 当 $c>1$ 时，和最大即为增加最多。那么求出最大子段和，再乘上 $c-1$ 即为变化量。

- 当 $c<1$ 时，将序列每个数取反即可。

（二）

我因为不会最大字段和挂了 3 发。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,c,a[300010],sum;
signed main(){
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),sum+=a[i];
	if(c==1){
		printf("%lld\n",sum);
		return 0;
	}
	if(c<=1)for(int i=1;i<=n;i++)a[i]*=-1;
	int mx=a[1],s=a[1];
	for(int i=2;i<=n;i++){
		if(s<0)s=0;
		s+=a[i];
		mx=max(mx,s);
	}
	mx=max(mx,s);
	if(c>0)printf("%lld\n",max(sum,sum+(c-1)*mx));
	else printf("%lld\n",max(sum,sum+(1-c)*mx));
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

签个到。

# 正文

解法就是让最大段的体现价值，最小的段改过自新。具体来说（$c \in \mathbb{Z}$）：

1. $c > 0$

求出最大子段和，然后乘上 $c$，再加上原来非最大子段和的部分即为答案。

2. $c \leq 0$

求出最小子段和，然后乘上 $c$，再加上原来非最小子段和的部分即为答案。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, C, allsum;
ll A[300005];

signed main()
{
	cin >> N >> C;
	for(ll i = 1; i <= N; ++ i)
		cin >> A[i], allsum += A[i];
		
	if(C > 0)
	{
		ll maxsum = 0, sum = 0;
		for(ll i = 1; i <= N; ++ i)
		{
			sum += A[i];
			maxsum = max(maxsum, sum);
			if(sum < 0)
				sum = 0;
		}
		
		cout << allsum + maxsum * (C - 1) << endl;
	}
	else
	{
		ll minsum = 0, sum = 0;
		for(ll i = 1; i <= N; ++ i)
		{
			sum += A[i];
			minsum = min(minsum, sum);
			if(sum > 0)
				sum = 0;
		}
		
		cout << allsum - minsum + minsum * C << endl;
	}
	return 0;
}
```

---

## 作者：wosile (赞：0)

一次操作会使总和增加 $(C-1)\sum\limits_{i=l}^rA_i$，负负得正，所以如果 $C-1>0$，就找 $A$ 的最大子段和，否则就找最小子段和就行。最后的答案就是原来的总和加上 $(C-1)$ 乘上最大/最小子段和。注意本题需要 `long long`。

最大子段和见 [P1115](https://www.luogu.com.cn/problem/P1115)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[300005],c;
typedef long long ll;
ll pre[300005];
int main(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(c>1){
		ll now=0,ans=0,sum=0;
		for(int i=1;i<=n;i++){
			now=max(now,0LL)+a[i];
			ans=max(ans,now);
			sum+=a[i]; 
		}
		printf("%lld",sum+ans*(c-1));
	}
	else{
		ll now=0,ans=0,sum=0;
		for(int i=1;i<=n;i++){
			now=min(now,0LL)+a[i];
			ans=min(ans,now);
			sum+=a[i]; 
		}
		printf("%lld",sum+ans*(c-1));
	}
	//quod erat demonstrandum
}
```

---

