# Permutation Partitions

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ and an integer $ k $ , such that $ 1 \leq k \leq n $ . A permutation means that every number from $ 1 $ to $ n $ is contained in $ p $ exactly once.

Let's consider all partitions of this permutation into $ k $ disjoint segments. Formally, a partition is a set of segments $ \{[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]\} $ , such that:

- $ 1 \leq l_i \leq r_i \leq n $ for all $ 1 \leq i \leq k $ ;
- For all $ 1 \leq j \leq n $ there exists exactly one segment $ [l_i, r_i] $ , such that $ l_i \leq j \leq r_i $ .

Two partitions are different if there exists a segment that lies in one partition but not the other.

Let's calculate the partition value, defined as $ \sum\limits_{i=1}^{k} {\max\limits_{l_i \leq j \leq r_i} {p_j}} $ , for all possible partitions of the permutation into $ k $ disjoint segments. Find the maximum possible partition value over all such partitions, and the number of partitions with this value. As the second value can be very large, you should find its remainder when divided by $ 998\,244\,353 $ .

## 说明/提示

In the first test, for $ k = 2 $ , there exists only two valid partitions: $ \{[1, 1], [2, 3]\} $ and $ \{[1, 2], [3, 3]\} $ . For each partition, the partition value is equal to $ 2 + 3 = 5 $ . So, the maximum possible value is $ 5 $ and the number of partitions is $ 2 $ .

In the third test, for $ k = 3 $ , the partitions with the maximum possible partition value are $ \{[1, 2], [3, 5], [6, 7]\} $ , $ \{[1, 3], [4, 5], [6, 7]\} $ , $ \{[1, 4], [5, 5], [6, 7]\} $ , $ \{[1, 2], [3, 6], [7, 7]\} $ , $ \{[1, 3], [4, 6], [7, 7]\} $ , $ \{[1, 4], [5, 6], [7, 7]\} $ . For all of them, the partition value is equal to $ 7 + 5 + 6 = 18 $ .

The partition $ \{[1, 2], [3, 4], [5, 7]\} $ , however, has the partition value $ 7 + 3 + 6 = 16 $ . This is not the maximum possible value, so we don't count it.

## 样例 #1

### 输入

```
3 2
2 1 3```

### 输出

```
5 2```

## 样例 #2

### 输入

```
5 5
2 1 5 3 4```

### 输出

```
15 1```

## 样例 #3

### 输入

```
7 3
2 7 3 1 5 4 6```

### 输出

```
18 6```

# 题解

## 作者：do_while_true (赞：2)

## 题目分析

考虑第一问，划分 $k$ 个区间，最大化 这 $k$ 个区间的最大值的和。显然我们这 $k$ 个区间的最大值只有为序列中前 $k$ 大的数才能最大化，所以第一问所求答案就是序列前 $k$ 大的数。

考虑第二问，首先这前 $k$ 个数一定不能在同一区间内，则我们要把它们划分到不同的区间里，我们可以把这前 $k$ 个数叫做这些区间的**核心**。

考虑类似插板的方法，插板分区间，则两个区间之间的板可以取的位置就是两个核心之间的空档的数量。再根据乘法原理乘起来即可，注意要边乘边模。

## 做法分析

大概浏览了一下其他题解，我的实现方法是不一样的。

首先记录下原序列中数的值 $dis$ 以及它的位置 $pos$，根据 $dis$ 从大到小排序，记录下前 $k$ 个数的和，就是第一问的答案。

再把这前 $k$ 个数根据 $pos$ 排序，答案就为 $\prod\limits_{i=2}^kpos_i-pos_{i-1}$ 

## Code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long T,n,k,a[200001],c[200001],ans1,ans2=1;
struct node{
	long long dis,pos;
}b[200001];
bool cmp(node x,node y)
{
	return x.dis>y.dis;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i].dis=a[i];
		b[i].pos=i;
	}
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=k;i++){
		ans1+=b[i].dis;
		c[i]=b[i].pos;
	}
	sort(c+1,c+k+1);
	for(int i=2;i<=k;i++)
		ans2=ans2*(c[i]-c[i-1])%998244353;
	printf("%lld %lld",ans1,ans2);
	return 0;
}
```

这里给出我比赛时的[评测记录](https://codeforces.ml/contest/1326/submission/73688285)

---

## 作者：xht (赞：2)

最大值肯定可以选择 $n,n-1,\cdots,n-k+1$ 这 $k$ 个数相加。

求方案数时，相邻两个区间的间隔一定在两个选择的数中间，因此将位置之差相乘即可。

时间复杂度 $\mathcal O(n)$。

```cpp
const int N = 2e5 + 7;
int n, k;
ll a[N], ans;
modint Ans = 1;

int main() {
	rd(n), rd(k), rda(a, n);
	for (int i = 1; i <= k; i++) ans += n + 1 - i;
	print(ans, ' ');
	vi p;
	for (int i = 1; i <= n; i++)
		if (a[i] > n - k) p.pb(i);
	for (ui i = 1; i < p.size(); i++)
		Ans *= p[i] - p[i-1];
	print(Ans);
	return 0;
}
```

---

## 作者：AutumnKite (赞：1)

考场上我看到本题一脸懵逼，我发现我好像不会第一问...

冷静一下，发现显然答案的上界是取最大的 $k$ 个数，即 $(n-k+1)+(n-k+2)+\cdots+n=\frac{(2n-k+1)k}{2}$。

我们可以在原排列中标记出这最大的 $k$ 个数，记从左往右第 $i$ 个被标记的位置为 $x_i$。

我们要把原排列划分成 $k$ 段意味着我们要找到 $k-1$ 个分界点，并且我们现在要求两个分界点之间恰好包含一个被标记的数。

那么显然第 $i$ 个分界点应该选在 $x_i$ 到 $x_{i+1}$ 之间。

每个分界点的选择是独立的（即不会影响其他分界点的选择），所以根据乘法原理，把每个分界点的方案数相乘即可。

时间复杂度 $O(n)$。

```cpp
const int N = 200005, P = 998244353;
int n, k, a[N];
void solve(){
	read(n), read(k);
	long long sum = 0;
	int lst = 0, ans = 1;
	for (register int i = 1; i <= n; ++i){
		read(a[i]);
		if (a[i] > n - k){
			sum += a[i];
			if (lst) ans = 1ll * ans * (i - lst) % P;
			lst = i;
		}
	}
	print(sum, ' '), print(ans);
}
```

---

## 作者：andyli (赞：1)

题意：  
你有一个长度为 $n$ 的排列 $p_1, p_2, ..., p_n$ 和一个正整数 $k$，你需要将其划分为 $k$ 段， $\{[l_1, r_1], [l_2, r_2], ..., [l_k, r_k]\}$，满足：  
- $\forall 1\leq i\leq k, 1\leq l_i\leq r_i\leq n$
- $\forall 1\leq j\leq n$ 存在恰好一个段 $[l_i, r_i]$ ，满足 $l_i\leq j\leq r_i$。  

如果存在在第一种划分方案中的一个段，但另一个划分方案中没有这一段，则两种划分方案不同。
定义一种划分方案的“划分值”为 $\sum\limits_{i=1}^{k} {\max\limits_{l_i \leq j \leq r_i} {p_j}}$，对于所有合法的划分方案求出最大的划分值 与 使得划分值最大的划分方案数。  
你只需求出使得划分值最大的划分方案数对 $998244353$ 取模后的结果即可。  
$1\leq k\leq n\leq 2\times 10^5, 1\leq p_i\leq n$。  

分析：  

最大的划分值一定是最大的 $k$ 个数的和，即$\sum\limits_{i=n-k+1}^{n} i = \dfrac{(n-k+1+n)\times k}{2}$，其余数都可与距它最近的（两个）$\geq n-k+1$ 的数合并。找出最大的 $k$ 个数得位置，不妨设为 $pos_i (1\leq i\leq k)$。  
例如，$1\leq i<pos_1$ 的数 $p_i$ 与 $p_{pos_1}$ 合并组成第一段，$pos_1<i<pos_2$ 的数 $p_i$ 与 $p_{pos_1}$ 或 $p_{pos_2}$ 合并，...，$pos_k < i \leq n$ 的数 $p_i$ 与 $p_{pos_k}$ 合并组成最后一段。对于 $pos_i < j < pos_{i+1}$ 的 $pos_{i+1}-pos_i-1$ 个数，令 $m=pos_{i+1}-pos_i-1$ 有 $m+1$ 种合并方案（即 前 $0$ 个数与左边合并，前 $1$ 个数与左边合并，...，前 $m$ 个数 （所有数）与左边合并），由乘法原理得总划分方案数为 $\prod\limits_{i=2}^{k} {pos_i-pos_{i-1}}$ 。  
时间复杂度 $\mathcal O(n)$ 。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <vector>
const int MOD = 998244353;

int main()
{
    int n, k;
    io.read(n, k);
    io.write(1LL * k * (2 * n - k + 1) / 2, " ");
    std::vector<int> pos;
    for (int i = 1; i <= n; i++) {
        int p;
        io.read(p);
        if (p >= n - k + 1)
            pos.push_back(i);
    }
    int ans = 1;
    for (size_t i = 1; i < pos.size(); i++)
        ans = 1LL * ans * (pos[i] - pos[i - 1]) % MOD;
    writeln(ans);
    return 0;
}
```

---

## 作者：YNH_QAQ (赞：0)

## 题意
长度为 $n$ 的全部排列 $p$，要求将这个序列化为 $k$ 个区间中前 $k$ 大的数的和，求出和的最大值和划分方案数量。

## 分析
- 第一问：贪心，取出区间 $[n-k+1,n]$ 作为最大值。

- 第二问：利用乘法原理将位置之差相乘即为答案（两个区间的间隔的位置，一定在两个选择的数中间）。

---

## 作者：liuli688 (赞：0)

### 思路：
第一问比较简单，显然是数组中最大的 $k$ 个数。由于 $a$ 是 $n$ 的排列，可以 $O(n)$ 暴扫。

对于第二问，显然数组中最大的 $k$ 个数相邻的两个数中间要有分隔。设相邻的两个数第 $i$ 对数下标较小的下标为 $p_i$，较大的下标为 $q_i$，则有 $q_i - p_i$ 种方法。所以，运用乘法原理，答案就是它们乘起来，即 $(q_1 - p_1) \times (q_2 - p_2) \times \dots \times (q_{k-1} - p_{k-1})$。时间复杂度 $O(n)$。
### 代码：
```cpp
#define MAIN int main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
#define DB double
#define LL long long
#define ULL unsigned long long
#define LD long double
#define STR string
#define EL '\n'
#define BK break
#define CTN continue
#define INF INT_MAX
#define UINF INT_MIN
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#define FL(i,a,b) for(i = a;i <= b;i++)
#define FG(i,a,b) for(i = a;i >= b;i--)
//以上为缺省源 
#include <bits/stdc++.h>
USING;
int n,k,p[200000],lp = -1,tp = 0,i;
LL sum1 = 0,sum2 = 1;//一定要开 long long，否则第 5 个点会 WA 
const int MOD = 998244353;
MAIN
{
    SPEEDUP;
    IN(n >> k);
    FP(i,0,n)
    	IN(p[i]);
    FP(i,0,n)
    {
    	if(p[i] > n - k)//如果是数组中最大的 k 个数 
    	{
			if(lp + 1)//如果前面已经有过数组中最大的 k 个数了 
    			sum2 *= i - lp;//乘法原理乘一下 
    		sum2 %= MOD;//随时取模好习惯 
    		sum1 += p[i];//同时处理第一问 
			lp = i;//记录下标 
			tp++;//记录个数 
    	}
    	if(tp == k)//如果后面没有数组中最大的 k 个数了，跳出 
    		BK;
    }
    OUT(sum1 << ' ' << sum2);
    END;
}
```

---

## 作者：xuhanxi_dada117 (赞：0)

[题目大意&题目传送门](https://www.luogu.com.cn/problem/CF1326C)

# 解法

第一眼看到这个题时：区间分段，二分吗？

仔细看了一下发现第一个答案就是区间中前 $k$ 大的数的和。

那么第一问就秒了。

第二问求方案数，考虑乘法原理：

设前 $k$ 大值的位置从小到大为 $l_1,l_2,...,l_k$：

第一个区间：$[l_1,l_2)$ 中选择终点（只能包含 $l_1$）。

第二个区间：$[l_2,l_3)$ 中选择终点（只能包含 $l_2$）。

$\cdots $

所以答案为：

$$\Pi_{i=1}^{k-1}(l_{i+1}-l_i)$$

直接计算即可。

## 注意！ 第一个答案不要取模！

# 代码

```cpp
#include<bits/stdc++.h>
#define N 200010
#define mod 998244353
#define int long long
using namespace std;
int n,k,b[N];
struct node{
	int num,id;
}a[N];
bool cmp1(node a,node b){
	if(a.num!=b.num) return a.num>b.num;
	return a.id<b.id;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i].num;
		a[i].id=i;
	}sort(a+1,a+n+1,cmp1);
	int sum=0,typ=1;
	for(int i=1;i<=k;++i){
		sum+=a[i].num;
		b[i]=a[i].id;
	}sort(b+1,b+k+1);
	for(int i=2;i<=k;++i)
		typ=typ*(b[i]-b[i-1])%mod;
	cout<<sum<<" "<<typ;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/125023787)

---

## 作者：wmxwmx (赞：0)

[题目传送门](https://codeforces.com/contest/1326/problem/C)

还是安利一下[我的博客](http://leachim.wang/Codeforces/Global-Round-7/CF1326/)，里面有比赛记录以及其他题题解。
### Problem Restatement

给你一个长度为$n$的全排列$p_1,p_2,…,p_n$，让你严格分割成$k$个非空区间。使得划分的$k$个区间中，（每个区间的最大值）之和最大。输出这个**求和的最大值**和**有多少种这样的划分**。后者对$998244353$取模。

$(1≤k\leq n\leq 2*10^5)$

### Solution

既然全排列分割成$k$份，很明显如果要让每个区间最大值之和最大，就是让每个区间的最大值最大就好。也就是让这$k$个区间，每个区间独占一个$n$个数之中最大的$k$个数。

所以第一步肯定是找出来$n$个数中最大的$k$个数的位置。

然后考虑分割成$k$个非空区间，其实相当于在$n-1$个空隙中切$k-1$刀。而我们锁定了$k$个最大数的位置之后，其实相当于锁定了每一刀切的范围。

举个例子：$n=10,k=4,a=\{8,3,4,9,5,1,7,10,2,6\}$

标记最大数:$\{\textbf 8,3,4,\textbf 9,5,1,\textbf7,\textbf{10},2,6\}$

发现切的位置就是$8-9,9-7,7-10$这三处地方，分别有$3,3,1$种切法。

利用乘法原理可以算出来最多有多少种这样的划分，即$3\times 3\times 1=9$种。

### Code

具体实现用了一下C++ STL里面的map，写的还算是挺好看的吧。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 200005
#define MOD 998244353

int n,k,a[MAXN];

void solve(){
	map<int,int> mp;
	scanf("%d %d", &n, &k);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i]);
		mp[a[i]]=i;
		if(mp.size()>k) mp.erase(mp.begin());
	}
	vector<int> v;
	LL sum=0;
	for(auto p:mp){
		v.push_back(p.second);
		sum+=p.first;
	}
	sort(v.begin(),v.end());
	int ans=1;
	for(int i=1;i<k;i++){
		ans=(1LL*ans*(v[i]-v[i-1]))%MOD;
	}
	printf("%lld %d\n",sum,ans);
}


int main(){
	int T=1;
	// scanf("%d", &T);
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

第一问比较简单，我们只需贪心取 $n-k+1,\ldots ,n$ 作为每一段的最大值即可。

问题主要在第二问。

设第 $i$ 段最大值的位置在 $p_i$ 处。则第一段的右端点可以在 $p_1, p_1+1, \ldots, p_2-1$ 处取得，共有 $p_2-p_1$ 个位置；同理第二段右端点有 $p_3-p_2$ 个位置，以此类推。

根据乘法原理，总方案数为：

$$
\prod_{i=1}^{n-1} p_{i+1}-p_i
$$

```cpp
// Problem : C. Permutation Partitions
// Contest : Codeforces Global Round 7
// URL : https://codeforces.com/contest/1326/problem/C
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#define MOD 998244353
using namespace std;
int a[200005];
int main()
{
 int n,k;
 long long ans=1,res=0;
 cin>>n>>k;
 int lp=0;
 for(int i=1;i<=n;i++)
 {
  cin>>a[i];
  if(a[i]>=n-k+1)
  {
   if(!lp)lp=i;
   else
   {
    ans=ans*(i-lp)%MOD;
    lp=i;
   }
   res+=a[i];
  }
 }
 cout<<res<<' '<<ans<<endl;
 return 0;
}
```

---

