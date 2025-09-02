# Large Array and Segments

## 题目描述

给定一个由 $n$ 个正整数组成的数组 $a$，以及一个正整数 $k$。根据以下规则从数组 $a$ 创建数组 $b$：

- 数组 $b$ 包含 $n \cdot k$ 个元素；
- 数组 $b$ 的前 $n$ 个元素与数组 $a$ 相同，即对于 $i \le n$，有 $b_{i} = a_{i}$；
- 对于任意 $i > n$，有 $b_{i} = b_{i - n}$。

例如，若 $a = [2, 3, 1, 4]$ 且 $k = 3$，则 $b = [2, 3, 1, 4, 2, 3, 1, 4, 2, 3, 1, 4]$。

给定一个数 $x$，要求统计满足以下条件的位置 $l$（$1 \le l \le n \cdot k$）的数量：存在位置 $r \ge l$，使得数组 $b$ 在区间 $[l, r]$ 上的元素之和不小于 $x$（即 $b_{l} + b_{l+1} + \dots + b_{r} \ge x$）。

## 说明/提示

在第一个测试用例中，数组 $b$ 如下所示：

$$[3, 4, 2, 1, 5, 3, 4, 2, 1, 5, 3, 4, 2, 1, 5]$$

共有 $12$ 个位置 $l$ 满足存在对应的位置 $r$。以下是其中部分（非全部）示例：
- $l = 1$，存在 $r = 6$，区间 $[1, 6]$ 的和为 $18$；
- $l = 2$，存在 $r = 5$，区间 $[2, 5]$ 的和为 $12$；
- $l = 6$，存在 $r = 9$，区间 $[6, 9]$ 的和为 $10$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
5 3 10
3 4 2 1 5
15 97623 1300111
105 95 108 111 118 101 95 118 97 108 111 114 97 110 116
1 100000 1234567891011
1
1 1 1
1
1 1 1
2
2 1 2
1 1
2 1 5
2 1```

### 输出

```
12
1452188
0
1
1
1
0```

# 题解

## 作者：potata111 (赞：2)

## [_CF2086B_](https://www.luogu.com.cn/problem/CF2086B) Large Array and Segments 

### 题意

给你一个由 $n$ 个**正整数**组成的数组 $A$ 以及一个正整数 $k$。

则我们可以**构造**出一个数组 $B$，它满足：

- $B$ 由 $nk$ 个数字组成；
- 数组 $B$ 的前 $n$ 个数字与 $A$ 相同，也即 $\forall\ i \in [1,\ n],\ B_i = A_i$；
- 对 $B$ 中的其他数。形式化地，$\forall\ i \in (n,\ nk],\ B_i = B_{i - n}$。

人话：$B$ 是由 $k$ 个 $A$ 直接**拼起来**的。

举个例子：$A = [2, 3, 1, 4];\ k = 3 \Rightarrow B = [{\color{red}2, 3, 1, 4}, {\color{blue}2, 3, 1, 4}, {\color{green} 2, 3, 1, 4}]$。

接下来给定一个正整数 $x$，你需要**统计有多少**个 $l \in [1, nk]$ 满足：
$$
  ∃\ r \in [l, nk],\ \displaystyle\sum_{i=l}^r B_i \ge x.
$$


---

### 输入

首行一个 $t\ (1 \leq t \leq 10^4)$ —— 表示测试样例数量。

每个测试样例由两行组成：

第一行有三个数 $n,\ k,\ x\ (1 \leq n,k \leq 10^5; 1 \leq x \leq 10^{18})$；

第二行有 $n$ 个正整数，表示 $A\ (A_i \leq 10^8)$。

特殊地，**所有样例**的 $n$ 之和与 $k$ 之和均不超过 $2 \times 10^5$。



### 输出

满足条件的 $l$ 的数量。

---

### 解析

贪心地，对任意的区间左端点 $l$，右端点 $r$ 取 $r = nk$ 时 $\displaystyle\sum_{i=l}^{r} B_i$ 最大。


---

**证明**：若 $r \neq nk$，则 $r \in [l,\ nk)$。记：
$$S_1 = \displaystyle\sum_{i=l}^{r} B_i;\ S_2 = \displaystyle\sum_{i=l}^{nk} B_i.$$

则 $S_2 - S_1 = \displaystyle\sum_{i = r + 1}^{nk} B_i$，记其为 $S_3$。

$∵r \in [l,\ nk).$   
$∴ r + 1 \leq nk.$

$∵ \forall\ i \in [1,\ nk],\ A_i \in \bold{Z^{+}}.$  
$∴ S_3 > 0.$  
$∴ S_1 < S_2.$ 

**得证**：$\forall\ r \neq nk,\ \displaystyle\sum_{i=l}^{r} B_i < \displaystyle\sum_{i=l}^{nk} B_i$。也即 $r = nk$ 时 $\displaystyle\sum_{i=l}^{r}$ **最大**。

~~这不是一个“**显然**”就能略过的吗......~~

---

我们记 $P_x = \displaystyle\sum_{i = x}^{nk} B_i$（$P$ 是 $B$ 的后缀和）

**显而易见**，$P$ 是**单调递增**的。

故对于一个 $s \in [1,\ nk]$，若 $P_s < x$ 而 $P_{s + 1} \ge x$。

则 $\forall\ y \in [1, s],\ P_y < x;\ \forall\ z \in (s, nk],\ P_z \ge x$。

那么**当且仅当** $l \in (s, nk]$ 时，$l$ 符合条件。

则 $l$ 就有 $nk - s$ 种**取值**。

但显然，如果把长 $nk (1 \leq nk \leq 10^{10})$ 的 $B$ 构造出来，你一定会因看到 TLE 而高兴坏了的。

故我们把 $B$ 均分为 $k$ 个**_部分_**，每个**部分**都是一个 $A$。  
先用 $O(k)$ 的时间找到 $s$ 在第几**部分**。  
再 $O(n)$ 遍历这个**部分**，我们就可以找到 $s$ 的具体位置了。

时间复杂度为 $O(n + k)$。

---

### Tips

我们细致讲一下如何 $O(1)$ **获取** $P_x$。

显然，把 $P$ 构造出来是不现实的。

但因为 $B$ 本身由多个 $A$ 组成，非常**重复**。  
我们可以考虑先计算**大段的 **$A$，再**细致**计算一个 $A$ **里面**的值。  
（这种计算方法与**查找** $s$ 的方法有异曲同工之**妙**……）

我们先 $O(n)$ 求出 $A$ 数组的总和， 记作 $S$。

$x$ 的后面共有 $\lfloor\dfrac{nk - x}{n} \rfloor$ 个完整的 $A$。

接下来遍历区间 $[x,\ \lceil \dfrac{x}{n} \rceil \times n]$，对不完整的一部分 $A$ 求和即可。

确切地，$P_x = \lfloor\dfrac{nk - x}{n} \rfloor \times S + \displaystyle\sum_{i = x}^{\lceil \frac{x}{n} \rceil \times n} A_{i \bmod n}$。  
这个算式将会在下面的代码中作更细致的处理！


---

### 代码

**注释详尽，码风清奇**。

```cpp
#include<iostream>

#define ll long long
using namespace std;

const int N = 2e5 + 5;

int q;
int n, m;
ll tar;
ll arr[N];
int ans;
ll tot;

void solve()
{
	cin >> n >> m >> tar;

	for (int i = 1; i <= n + 5; i++)
		arr[i] = 0; 

	ll sum = 0;
	for (int i = 1; i <= n; i++)
		cin >> arr[i],
		sum += arr[i];
  // 完整的作一个后缀和也可以 但是没必要

	if (sum * m < tar)
		return cout << 0 << '\n', void();
    // 这表明 s 不存在

	ll div = tar / sum;
	ll mod = tar % sum;
	if (mod == 0)
		div--,
		mod = sum;
	// 计算完整的 A 的个数

	ans = tot = 0;
	for (int i = n; i >= 1; i--)
	{
		tot += arr[i];

		if (tot >= mod) 
			{ ans = i; break; }
	} // 对零散的部分求和

	cout << n * (m - (div + 1)) + ans << '\n';
}

int main()
{
	cin >> q;

	while (q--)
		solve();

	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[CF2086B Large Array and Segments](https://www.luogu.com.cn/problem/CF2086B)

### 题目大意

给你整数 $n,k,x$ 和一个正整数组 $a_1 \sim a_n$，数组 $b$ 是数组 $a$ 循环拼接 $k$ 次得到的，求有多少个 $l$ 满足有 $r \geqslant l$ 使得 $b_l + b_{l+1} + \dots + b_r \geqslant x$。

### 题目分析

由于 $a$ 数组的每一项都大于 $0$，因而对于每个 $l$，使得 $\sum\limits_{i=l}^{r} b_i$ 最大的 $r$ 都是最后一项 $nk$。

于是我们考虑看每一个 $l$ 的后缀和二分答案。

### 做题过程

当 $b$ 数组的所有项之和都小于 $x$ 时，答案显然为 $0$。

建立数组 $a$ 的后缀和数组 $sum_i=a_i+a_{i+1}+\dots +a_n$，则 $b_l + b_{l+1} + \dots + b_{nk}$ 可以先求出有多少个整块的 $a_1 \sim a_n$，再加上零散的 $a$ 数组后缀和。

此处二分答案的 $l$ 称为 $mid$。设 $d$ 为从 $mid+1$ 到 $nk$ 的长度，则 $d=nk-mid$；设 $s$ 为从 $b_{mid}$ 加到 $b_{nk}$ 的总和，则这些整块的部分可以先让 $s$ 加上 $sum_1 \cdot \lfloor \frac{d}{n} \rfloor$。还剩下 $b_{mid}$ 到最近的一个 $b_{nx}$ 的总和（$x$ 为整数），此处等同于 $a_{mid \bmod n} \sim a_n$，等于 $sum_{mid \bmod n}$。

我就是这么写的，然后发现自己漏了一个细节：当 $mid \bmod n =0$ 时，应采用 $sum_n$ 而不是 $sum_0$。

由此可以二分得到结果。

### 代码实现

```cpp
#include<iostream>
using namespace std;
const int N=100005;
long long n,k,x,a[N],s,sum[N],ans;
void solve(){
    cin>>n>>k>>x;
    for(int i=1;i<=n;i++)cin>>a[i];
    sum[n]=a[n];
    for(int i=n-1;i>0;i--)sum[i]=sum[i+1]+a[i];
    if(sum[1]*k<x){
    	cout<<0<<'\n';
    	return;
	}
    for(long long l=1,r=n*k,mid;l<=r;){
        mid=l+r>>1;
        long long d=n*k-mid;
        s=sum[1]*(d/n)+sum[mid%n?mid%n:n];
        if(s>=x)ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<'\n';
    ans=0;
    return;
}
int main(){
    int t;
	cin>>t;
    while(t--)solve();
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2086/submission/314464408)。

---

## 作者：ZAYNAab (赞：0)

## 题意概括

给你一个长 $n$ 的自然数数组 $A$。

将该数组复制 $k$ 次，存入数组 $B$。

求在数组 $B$ 中，有多少个数的前缀和大于 $x$。

## 解题分析

求出在数组 $B$ 中当前位置满足条件，而下一个位置无法满足的即可输出该位置。

可以用 **模拟** 的思路去做。

可以发现不能用直接模拟，时间复杂度 $O(nk)$ 会爆。

考虑到 $B$ 是由 $A$ 复制 $k$ 次而来的，所以 $B$ 中 $k$ 个数一分，每一段和相同。

所以就看这个位置在哪一段，然后在这一段中扫一遍即可。

时间复杂度 $O(n)$。

记得一定开 long long，为保险起见我开了 int128。
```cpp
#include<bits/stdc++.h>
#define lll __int128
#define ll long long
using namespace std;
lll s;
ll a[100005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		s=0;
		ll n,k,x,ans=0;
		cin>>n>>k>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
		}
		lll p=s*k;
		if(p<x){
			cout<<0<<"\n";
			continue;
		}
		while(p-s>=x){
			p-=s;
			ans+=n;
		}
		for(int i=1;i<=n;i++){
			if(p>=x)ans++;
			else break;
			p-=a[i];
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

注意到若某个位置合法，那么它左边的都合法。

官解写的二分，但是没什么必要，枚举即可。

具体地，枚举到在第几次重复，然后再枚举是第几个就行了。

复杂度：$O(n+k)$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,cc),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,k,x,a[100005];
void slv(){
    read3(n,k,x);
    int sum1=0,sum2=0,ans=0;
    for(int i=1;i<=n;i++)read(a[i]),sum1+=a[i];
    for(int i=1;i<=k;i++){
        if(sum2+sum1>=x)break;
        sum2+=sum1;
        ans+=n;
    }
    for(int i=n;i>=1;i--){
        if(sum2+a[i]>=x)break;
        sum2+=a[i];
        ans++;
    }
    cout<<max(n*k-ans,0ll)<<endl;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{58}$ 篇题解。

# $\mathbf{0x01}$ 承

将一个数组 $a$ 复制 $k$ 次形成数组 $b$，求出满足$l$ 及其之后所有数的和大于等于 $x$ 的 $l$ 的数量。

# $\mathbf{0x02}$ 转

很显然，如果从后往前依次遍历 $b$ 中的所有数并累加在 $\text{sum}$ 中，如果在一个位置 $sum\geq x$ 则在它之前的所有位置都满足条件。

记 $a$ 数组中所有元素之和为 $s$，则在 $b$ 数组中，有 $\left\lfloor \frac{x}{s} \right\rfloor\times n$ 个数是一定不满足条件的（如果 $x$ 是 $s$ 的倍数则变为 $(\left\lfloor \frac{x}{s} \right\rfloor-1)\times n$）。然后单独处理一个数组中的数（这里其实是分块的思想，只不过没有起到优化的作用），记其中满足条件的有 $c$ 个，那么答案就是 $(k-p-1)\times n+c$。

个人认为代码中的边界情况还是很不好处理的。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,k,x;
int main(){
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>k>>x;
		vector<ll>a(n+1),g(n+1);
		ll sum=0,c=0;
		for(ll i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		if(sum*k<x){
			cout<<0<<endl;
			continue;
		}
		ll p=x/sum,q=x%sum,l=0;
		if(q==0)p--,q=sum;
		for(ll i=n;i>=1;i--){
			l+=a[i];
			if(l>=q){
				c=i;
				break;
			}
		}
		cout<<n*k-p*n+c-n<<endl;
	}
}

```

---

