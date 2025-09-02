# LCM Sum (easy version)

## 题目描述

给你两个正整数 $l$ 和 $r$。

计算不同的整数三元组 $(i,j,k)$ 的数量，使得 $l\leq i<j<k\leq r$ 且 $\operatorname{lcm}(i,j,k)\ge i+j+k$。

$\operatorname{lcm}(i,j,k)$ 表示整数 $i,j,k$ 的最小公倍数 $(LCM)$ 。

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868```

### 输出

```
3
1
78975
969
109229059713337```

# 题解

## 作者：youyou2007 (赞：5)

## Description

给定 $l$、$r$，求 $l$ 到 $r$ 之间有多少三元组 $(i,j,k)$，满足 $\operatorname{lcm}(i,j,k) \ge i+j+k$ 且 $i \lt j\lt k$。

共有 $T (1 \le T \le 5)$ 组询问， $ 1 \le l \le r \le 2 \times 10^5 $。

## Solution

观察样例，发现合法的状态太多，不好统计，但**正难则反** ，我们考虑统计不合法的三元组，再用总数减去不合法的个数即可。

问题转化为统计  $\operatorname{lcm}(i,j,k) \lt i+j+k$ 的三元组个数。

由于 $i \lt j\lt k$，所以 $i + j + k \le 3k$ ，从而得出 $\operatorname{lcm}(i,j,k) \lt 3 \times k$。

又根据最小公倍数的性质，$k$ 必然是 $lcm(i,j,k)$ 的约数 ，那么只有两种可能：$\operatorname{lcm}(i,j,k) = k$ 或 $\operatorname{lcm}(i,j,k) = 2 \times k$ 。

先看 $\operatorname{lcm}(i,j,k) = 2 \times k$  的情况，对小数据打表发现，只有 $(3,4,6)$ 与 $(6,10,15)$ 和它们的**整数倍**的情况能够满足。

再看另一种情况，  $i$、$j$、$k$ 的最小公倍数为 $k$，说明 $i$ 和 $j$ 都是 $k$ 的约数，这是一个较强的性质。

在 **easy version** 下，发现 $T$ 很小，几乎可以忽略成常数对待，而区间值域也不大，可以从 $l+2$ 到 $r$ 枚举 $k$，对于每个 $k$ 计算不合法三元组个数：

+ 对于  $\operatorname{lcm}(i,j,k) = k$  的贡献，枚举 $k$ 在 $[l,r]$ 中有多少个**不为自己本身**的约数，设区间内有 $fac$ 个约数，则贡献为 $C(fac, 2)$ 种。

+ 对于 $\operatorname{lcm}(i,j,k) = 2 \times k$  的贡献，我们直接求是不是上述两种的整数倍即可。

整个区间所有三元组的总数为 $C(r-l+1,3)$ 个，最后答案即为 $C(r-l+1,3) - $  所有不合法方案总数。

记得开 **long long**，以及注计算组合数时不要一下全乘起来，保证不炸 long long。

## Code
```cpp
// by youyou2007 in 2022.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#define REP(i, x, y) for(int i = x; i < y; i++)
#define rep(i, x, y) for(int i = x; i <= y; i++)
#define PER(i, x, y) for(int i = x; i > y; i--)
#define per(i, x, y) for(int i = x; i >= y; i--)
using namespace std;
int T;
long long l, r;
long long ans, fac, cnt;
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		ans = 0, cnt = 0;
		scanf("%lld%lld", &l, &r);
		for(int k = l + 2; k <= r; k++)//因为题中要求 i < j < k，所以必须从 l + 2 枚举
		{
			fac = 0;
			for(int i = 1; i * i <= k; i++)
			{
				if(k % i == 0)
				{
                    if(i >= l)
                    {
					    fac++;
                    }   
                    if(k / i != k && i * i != k && (k / i) >= l)//注意自己本身不能被统计进去
					{
						fac++;
					}
				}
			}
			cnt += fac * (fac - 1) / 2;
			if(k % 6 == 0 && k / 2 >= l)//判断是否是 (3,4,6) 的整数倍
			{
				cnt++;
			}
			if(k % 15 == 0 && (k * 2) / 5 >= l) //判断是否是 (6,10,15) 的整数倍
			{
				cnt++;
			}
		}
		ans = (r - l + 1) * (r - l) / 2 * (r - l - 1) / 3 - cnt;
		printf("%lld\n", ans);
	}
	
	return 0;
}
```


---

## 作者：_yjh (赞：4)

一道平凡的数论题。

首先设 
$$\operatorname{lcm}=a_ii=a_jj=a_kk,(a_i,a_j,a_k=1)$$
则有 
$$a_ii \geq i+j+k,a_jj \geq i+j+k,a_kk \geq i+j+k$$
分别乘
$$a_ja_k,a_ia_k,a_ia_j$$
再相加，得
$$a_ia_ja_k \geq a_ia_j+a_ia_k+a_ja_k$$
同除 $a_ia_ja_k$，有
$$\frac{1}{a_i}+\frac{1}{a_j}+\frac{1}{a_k} \leq 1$$

正难则反，可以用总方案数减去 $\frac{1}{a_i}+\frac{1}{a_j}+\frac{1}{a_k} > 1$ 方案数

试根，当 $\min(a_i,a_j,a_k)=1$ 时，成立，这部分枚举因数， $O(n\sqrt{n})$ 暴力算即可。

还有两根 $2,3,4$，$2,3,5$，可以直接枚举 $\operatorname{lcm}$，暴力判是否合法。

总时间复杂度 $O(n\sqrt{n})$。

~~太菜了，场上没调出来。![youl](https://cdn.luogu.com.cn/upload/pic/69020.png)~~

谢谢管理员的辛苦审核。

---

## 作者：Symbolize (赞：2)

# 思路
正着不好求，但我们可以用总的数量减去 $i + j + k > lcm(i,j,k)$ 的数量。

因为 $i < j < k$，所以 $lcm(i,j,k) < 3 \times k$。又因为 $k$ 为 $lcm(i,j,k)$ 的倍数，所以只有两种情况：

1. $lcm(i,j,k) = 2 \times k$
2. $lcm(i,j,k = k$

对于第一种情况，打表找规律，我们会发现只有三元组 $(i,j,k)$ 是 $(3,4,6)$ 或 $(6,10,15)$ 时才满足条件。

对于第二种情况，因为 $1 \le t \le 5$。所以直接从 $l+2$ 循环到 $r$。在中途，枚举的 $i$ 在找它的因数，只要在 $l$ 到 $r$ 的区间内，我们就可以让一个变量 $cnt$ 加一。那么这种情况的总贡献就是 $C_{2}^{cnt}$。

$l,r$ 区间内三元组总数就是 $C_{3}^{r-l}$。

答案就是用 $C_{3}^{r-l}$ 减去前面两种情况的符合数量。

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
const int N=2e5+10;
using namespace std;
int t,l,r,ans;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
void getans()
{
	l=read();
	r=read();
	rep1(i,l+2,r)//枚举 
	{
		int cnt=0;
		rep1(j,1,sqrt(i))//记得素筛 
		{
			if(i%j==0)//枚举因数 
			{
				if(j>=l) ++cnt;
				if(j!=1&&j*j!=i&&i/j>=l) ++cnt;//不算自己 
			}
		}
		ans+=(cnt-1)*cnt>>1;//情况二贡献 
		//情况一贡献 
		if(i%6==0&&(i>>1)>=l) ++ans;//(3,4,6)的倍数 
		if(i%15==0&&(i<<1)/5>=l) ++ans;//(6,10,15)的倍数 
	}
	ans=(r-l+1)*(r-l)*(r-l-1)/6-ans;//减去全部的
	cout<<ans<<endl;
	ans=0;//清空 
	return;
}
signed main()
{
	t=read();
	while(t--) getans();//循环要答案 
	return 0;//收场 
}

```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2300}$
---
### 解题思路：

正难则反，考虑将问题转化为用所有的方案减去 $\text{lcm}(i,j,k)<i+j+k$ 的数量，由于 $i,j<k$，可知 $\text{lcm(i,j,k)}<3\times k$。

而且 $\text{lcm(i,j,k)}$ 是 $k$ 的整数倍，也就是 $\text{lcm}(i,j,k)=2\times k$ 或者 $\text{lcm}(i,j,k)=k$。

前者有一个结论，即 $\text{lcm}(i,j,k)=2\times k$ 时，三元组为 $(3,4,6)$ 或者 $(6,10,15)$ 的倍数，证明后面说。

所以直接枚举一下这个的整数倍，然后筛一下真因数个数就直接算完了。

---
关键是没几篇题解说的那个结论的证明，大概给出两种证明方法，比较好的一种是 $\text{bunH2O}$ 神仙提供的。

---
### 证法一：

设 $i=2^ap_1$，$j=2^bp_2$，$k=2^cp_3$。

要求满足 $\max(a,b)=c+1$，$p_1,p_2|p_3$，$i+j>k$，$\min(a,b,c)=0$，$\gcd(p_1,p_2,p_3)=1$。

根据 $c$ 的大小分为三种情况。

情况一：$c=0$。

可知 $max(a,b)=1$。

此时取 $a=b=1$，$p_3=3\times5$，$p_1=3$，$p_2=5$，此时满足所有条件。

令 $a,b$ 其中一个为 $0$，立即发现不满足条件 $i+j>k$，不成立。

若将 $p_2$ 或者 $p_1$ 中的一个改大，不妨让 $p_2>5$，$p_1$ 为 $3$ 或者 $5$。

取最小的 $p_3=p_1\times p_2$，此时 $2p_1<(p_1-2)\times p_2$，说明情况不成立。

若两者都变化，且都不取 $3$ 和 $5$，还是取 $p_3=p_1\times p_2$，有 $2p_1+2p_2<4\max(p_1,p_2)<p_1\times p_2$，不成立。

若在此基础上变化 $a,b$ 同样是不可能成立的。

情况二：$c=1$

此时要求 $max(a,b)=2$。

取 $a=0,p_1=3,b=2,p_2=1,p_3=3$。

首先此时 $a,b$ 中只能一个是 $0$ 一个是 $2$，否则分别不满足 $\min(a,b,c)=0$ 和 $max(a,b)=c+1$。

若交换 $a,b$，不符合 $k>j,i$。

然后考虑更改 $p_1$ 和 $p_2$ 的取值。

若更改 $p_2$ 的取值为 $p$，由于 $p=3$ 不成立，不妨让 $p> 3$，则 $p_3$ 此时最小为 $3p$，此时 $3+4p<6p$ 不满足条件。

如果更改 $p_1$ 为 $p$，则 $p_3$ 最小为 $p$，要求 $p+4>2p$，即 $p<4$ 只能取 $3$。

两者都更改，则 $p_1,p_2>3$，则 $p$ 最小为 $p_1\times p_2$，此时 $p_1+4p_2<5\max(p_1,p_2)<6\max(p_1,p_2)<2p_1\times p_2$。

---
情况三：$c>1$

此时要求 $max(a,b)=c+1$。

$a$ 取 $0$，$b$ 取 $c+1$，$p_1=3$，$p_2=1$。

此时 $p_3$ 最小为 $3$，容易发现这种取值不满足条件。

和第二种情况类似地，$a,b$ 取值只能调换，调换同也同样明显不满足条件。

更改 $p_1$ 或者 $p_2$ 也是和上面的两种情况类似地放缩一下就证完了，结果就是不成立。

（写不动了其实，反正就是大分讨）。

---
### 证明二

考虑将 $i$ 和 $j$ 表示为 $k$ 的一个分数形式。

由于 $i<j$ 且 $i+j>k$，则 $j>\dfrac{k}{2}$。

若将 $j$ 表示为 $\dfrac{n}{m}$，由于 $j$ 分解质因数之后的非 $2$ 的指数不能超过 $k$，$2$ 的指数最多也只能大一。所以 $n$ 的取值只有 $1$ 和 $2$ 两种。由于 $j<k$，而取不和 $n$ 互质的数并没有意义，所以 $m$ 最小取 $3$。

由此的出 $j$ 最大为 $\dfrac{2}{3}k$，可以发现，满足条件 $j>\dfrac{k}{2}$ 的取值只有 $\dfrac{2}{3}k$ 一种。

再讨论 $i$，由于 $j$ 只能取 $\dfrac{2k}{3}$，所以 $\dfrac{2k}{3}>i>\dfrac{k}{3}$。

同样地，将 $i$ 表示为 $\dfrac{n}{m}$ 的形式，$n$ 的取值依然是 $1$ 或者 $2$，$m$ 的取值在满足上述条件的情况可以有多种。具体地，可以取 $\dfrac{2k}{5}$ 或者 $\dfrac{k}{2}$。

综合一下两者，就证明了最简的两种是 $(3,4,6)$ 和 $(6,10,15)$，其余的都是一些倍数。

---
### 代码：

```
#include<cstdio>
using namespace std;
#define int long long
const int MAXN=200005;
int l,r,T,f[MAXN],ans,cnt;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&l,&r);
		ans=0;
		for(int i=l+2;i<=r;i++){
			cnt=0;
			for(int j=1;j*j<=i;j++)
			if(i%j==0){
				if(j>=l)cnt++;
				if(j!=1&&j*j!=i&&(i/j)>=l)cnt++;
			}
			ans+=(cnt-1)*cnt/2;
		}
		for(int i=1;i<=r;i++){
			if(3*i>=l&&6*i<=r)ans++;
			if(6*i>=l&&15*i<=r)ans++;
		}
		ans=(r-l+1)*(r-l)/2*(r-l-1)/3-ans;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：1)

## 题意
有 $t$ 组数据（$t \le 5$）。

给你正整数 $l,r$（$1\le l<r\le 200000$），寻找有多少个三元组 $i,j,k$ 满足：

- $l\le i <j <k \le r$
- $\operatorname{lcm}(i,j,k)\ge (i+j+k)$

保证 $l+2\le r$。

## 思路
把问题转化为计算 $\operatorname{lcm}(i,j,k)< i+j+k$ 的个数。由于 $\operatorname{lcm}(i,j,k)< i+j+k<3\times k$。故 $\operatorname{lcm}(i,j,k)=k$ 或 $2\times k$。

因此，$i,j$ 一定为 $2\times k$ 的因子。此时，

$$\operatorname{lcm}(i,j,k)=k< i+j+k$$

显然成立，那么，对于

$$\operatorname{lcm}(i,j,k)=2\times k< i+j+k$$

又如何呢？此时，我们需要 $i+j>k$ 才能实现。那么，有没有这样的 $i,j$，使得

- $i|2\times k,j|2\times k$
- $i<j<k<i+j$

成立呢？

答案是有的，但只有两组。分别是：

1. $i:j:k=3:4:6$
1. $i:j:k=6:10:15$

~~我也不知道为什么只有这两组。~~

可以设想，当 $k$ 变的更大时，乘法的增长速度要远大于加法，故更不可能出现满足条件的 $(i,j,k)$。因此应当只有这两组。

因此我们预处理 $l$ 到 $r$ 之间每个 $k$ 的因数。

设其有 $cnt$ 个因数，则我们只需在 $cnt$ 个因数中选两个作为 $(i,j)$ 即可。方案数为 $\dfrac{cnt\times(cnt-1)}{2}$。注意上面提到的特判。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
#define int long long
using namespace std;
int t=1,l,r,ans,cnt;
vector<int> y[400005];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(i,1,2e5){
    for(int j=i;j<=4e5;j+=i){
      y[j].push_back(i);
    }
  }
  rep(kk,1,t){
    cin>>l>>r;
    ans=(r-l+1)*(r-l)*(r-l-1)/6;
    rep(k,l,r){
      cnt=0;
      for(int v:y[k]){
        if(l<=v && v<k)cnt++;
      }
      ans-=cnt*(cnt-1)/2;
      if(k%6==0 && k/2>=l)ans--;
      if(k%15==0 && k*2/5>=l)ans--;
    }
    cout<<ans<<endl;
  }
  
  return 0;
}
```

---

## 作者：ioker (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1712E1)

## 题目描述:

$T$ 组数据

给你两个正整数 $l$ 和 $r$。

计算不同的整数三元组 $(i,j,k)$ 的数量，使得 $l\le i<j<k \le r$ 且 $\text{lcm}(i,j,k)\ge i+j+k$。

$\text{lcm}(i,j,k)$ 表示整数 $i,j,k$ 的最小公倍数。

## 解法：

反向思考，考虑 $\text{lcm}(i,j,k)<i+j+k$ 的数量。

$$\because l\le i<j<k \le r$$

$$\therefore \text{lcm}(i,j,k)<3\times k$$

又 

$$\because k\mid \text{lcm}(i,j,k)$$

$$\therefore \text{lcm}(i,j,k)=k$$

或

$$\text{lcm}(i,j,k)=2\times k$$

当 $\text{lcm}(i,j,k)=k$ 时，易得 $i\mid k,j\mid k$，对答案的贡献为

$$sum=\frac{x\times (x-1)}{2}$$

其中 $x=\sum\limits_{i=l}^{r}{[i\mid k]}$

当 $\text{lcm}(i,j,k)=2\times k$ 时，可以通过枚举发现

如果 $3\mid i$ 并且 $4\mid j$ 并且 $6\mid k$ 

那么，计数器 $sum$ 加 1。

如果 $6\mid i$ 并且 $10\mid j$ 并且 $15\mid k$

那么，计数器 $sum$ 也加 1。

$\frac{(r-l+1)\times (r-l)\times (r-l-1)}{6}-sum$ 即为所求

----
既然 $T\le 5,1\le l \le r\le 2×10^5$

考虑枚举 $k$，分类讨论，统计答案。

枚举 $k$ 需要 $\Theta(r-l+1)$，枚举约数需要 $\Theta(\sqrt{k})$

设 $n=r-l+1$

时间复杂度为 $\Theta(Tn\sqrt{n})$

参考代码:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int n = 0, m = 0;
    char c = getchar();

    while (!isdigit(c))
        m |= c == '-', c = getchar();

    while (isdigit(c))
        n = (n << 1) + (n << 3) + c - '0', c = getchar();

    return m ? -n : n;
}
template <class T> inline void write(int n, int c) {
    int tot = 0, a[101];

    if (n < 0)
        n = -n, putchar('-');

    while (n)
        a[++tot] = n % 10, n /= 10;

    if (!tot)
        putchar('0');

    while (tot)
        putchar(a[tot--] + '0');

    if (c)
        putchar(c);
}
#define read read()
#define N 1000001
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
signed main() {
    int t = read;

    while (t--) {
        int l = read, r = read, ans = 0;

        for (int i = l; i <= r; i++) {
            int k = i, s = 0;

            if (l == 1)
                s++;

            for (int j = 2; j * j <= k; j++) {
                if (k % j == 0) {
                    if (j >= l)
                        s++;

                    if (j != k / j && k / j >= l)
                        s++;
                }
            }

            ans += 1ll * (s) * (s - 1) / 2;

            if (k % 15 == 0) {
                int x = k / 15;

                if (x * 6 >= l)
                    ans++;
            }

            if (k % 6 == 0) {
                int x = k / 6;

                if (x * 3 >= l)
                    ans++;
            }
        }

        write<int>(1ll * (r - l) * (r - l - 1) * (r - l + 1) / 6 - ans, 10);
    }

    return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

本题解按照困难难度撰写。

满足条件的三元组个数有点不好求，那么我们就求不满足条件的三元组。

题目告诉我们，$i<j<k$。那么如果 $\operatorname{lcm}(i,j,k)<i+j+k$，必须满足两个条件之一：

$i\mid k\operatorname{and}j\mid k$

$i\mid k\times2\operatorname{and}j\mid k\times2\operatorname{and}i+j>k$

可以发现，若 $i\mid k$，那么必定有 $i\mid k\times2$。$j$ 同理。

我们可以**依次**枚举 $k$，然后列出所有的 $k\times2$ 的因数。在此基础上枚举 $i$ 和 $j$。

我们可以一边枚举一边记录答案。

将所有的询问按照 $r$ 升序排序。然后，每当我们完成上述枚举（但是还没有开始枚举下一个 $k$ 的时候），我们要解决所有的满足 $r=k$ 的问题。

因为此时，所有的被枚举出来的三元组的所有数字都不会大于 $k$。此时解决问题才正确。

例如，当枚举到 $k=4$ 时，只有 $(1,2,4)$ 一个三元组满足 $\operatorname{lcm}(i,j,k)=4<i+j+k=7$，那么我们就可以解决诸如 $[1,4]$ 之类的问题。

我们可以发现，每当找到一个三元组，我们就要记录有多少个三元组满足左端点是 $i$。我们可以用线段树储存。

解决问题的时候直接找有多少个三元组左端点在  $l$ 和 $k$ 之间即可。反正此时被找到的三元组右端点也都不会超过 $k$。

我们可以发现，总的三元组个数是 $(r-l+1)\times(r-l)\times(r-l-1)\div6$。用总数减去不符题意的数即为符合题意的数。

输出答案即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define max_n 200000
int p[202];
int pi;
struct V{
	int x,cnt;
	long long sum;
};
int q;
struct Q{
	int id,l,r;
	long long ans;
}a[max_n+2];
struct TR{
	int l,r;
	long long sum;
}tr[max_n<<2];
bool cmpr(Q a,Q b){
	return a.r<b.r;
}
bool check(int i,int j,int k){
	return (!(k%i)&&!(k%j))||i+j>k;
}
void pu(int o){
	tr[o].sum=tr[o<<1].sum+tr[o<<1|1].sum;
}
void build(int o,int l,int r){
	tr[o]=(TR){l,r,0};
	if(l>=r)return;
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
void upd(int o,int x,int w){
	int l=tr[o].l,r=tr[o].r;
	if(l>=r){
		tr[o].sum+=w;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)upd(o<<1,x,w);
	else upd(o<<1|1,x,w);
	pu(o);
}
long long query(int o,int ql,int qr){
	int l=tr[o].l,r=tr[o].r;
	if(ql<=l&&r<=qr)return tr[o].sum;
	int mid=(l+r)>>1;
	long long res=0;
	if(ql<=mid)res+=query(o<<1,ql,qr);
	if(qr>mid)res+=query(o<<1|1,ql,qr);
	return res;
}
bool cmpid(Q a,Q b){
	return a.id<b.id;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712E2_1.in","r",stdin);
	freopen("CF1712E2_1.out","w",stdout);
	#endif
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		a[i].id=i;
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	sort(a+1,a+q+1,cmpr);
	build(1,1,max_n);
	for(int k=1,ai=1;k<=max_n;++k){
		pi=0;
		for(int i=1,len=sqrt(k<<1);i<=len;++i){
			if((k<<1)%i==0){
				p[++pi]=i;
				p[++pi]=(k<<1)/i;
			}
		}
		sort(p+1,p+pi+1);
		pi=unique(p+1,p+pi+1)-p-1;
		for(int i=1,cnt;i<=pi&&p[i]<k;++i){
			cnt=0;
			for(int j=i+1;j<=pi&&p[j]<k;++j){
				if(check(p[i],p[j],k))++cnt;
			}
			if(!cnt)continue;
			upd(1,p[i],cnt);
		}
		while(a[ai].r==k){
			long long len=(a[ai].r-a[ai].l+1);
			a[ai].ans=len*(len-1)*(len-2)/6-query(1,a[ai].l,k);
			++ai;
		}
	}
	sort(a+1,a+q+1,cmpid);
	for(int i=1;i<=q;++i)printf("%lld\n",a[i].ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727189)

By **dengziyue**

---

## 作者：Priestess_SLG (赞：0)

简单容斥题。考虑到 $\text{lcm}(i,j,k)\ge i+j+k$ 不好做，于是可以求 $\text{lcm}(i,j,k)<i+j+k$ 的不同方案数。因为 $i<j<k$ 所以枚举 $k$，必有 $i+j+k<k+k+k=3k$。也就是说有且仅有下面的两种合法情况：

+ $\text{lcm}(i,j,k)=k$
+ $\text{lcm}(i,j,k)=2k$

考虑分别计算其对答案的贡献。先考虑第一类情况：显然可以枚举 $k$，然后询问有多少组 $(i,j)$ 满足 $l\le i<j<k$ 且 $i\mid k,j\mid k$。因为 $k$ 的因数个数很少，所以直接暴力算出因数个数 $c$，那么不同的合法 $(i,j)$ 组数就是 $\binom{c}{2}$。

~~让我们来偷一张图：~~

![](https://cdn.luogu.com.cn/upload/image_hosting/kjxzlo2c.png)

然后考虑第二类情况。这个看起来很困难，但是容易猜到合法的 $(i,j,k)$ 组数很少。于是写一个 $O(n^3)$ 暴力可以发现当且仅当 $i:j:k=3:4:6$ 或 $i:j:k=6:10:15$ 时合法。所以直接写一个二分即可通过该问题。

upd：我糖了，我忘记了世界上有个东西叫做除法.jpg

```cpp
int b3(int x) {
    return x * (x-1) * (x-2) / 6;
}
int b2(int x) {
    return x * (x-1) / 2;
}
void run() {
    int T = read();
    while (T--) {
        int l = read(), r = read();
        int len = r - l + 1;
        int all = b3(len);
        int c1 = 0, c2 = 0;
        // 3:4:6
        int L = 1, R = r, best = -1;
        while (L <= R) {
            int mid = L + R >> 1;
            if (3 * mid >= l && 4 * mid >= l && 6 * mid >= l)
                best = mid, R = mid - 1;
            else
                L = mid + 1;
        }
        if (best != -1) {
            int tl = best;
            L = 1, R = r, best = -1;
            while (L <= R) {
                int mid = L + R >> 1;
                if (3 * mid <= r && 4 * mid <= r && 6 * mid <= r)
                    best = mid, L = mid + 1;
                else
                    R = mid - 1;
            }
            if (best != -1) {
                int tr = best;
                c1 += max(0ll, tr - tl + 1);
            }
        }
        // 6:10:15
        L = 1, R = r, best = -1;
        while (L <= R) {
            int mid = L + R >> 1;
            if (6 * mid >= l && 10 * mid >= l && 15 * mid >= l)
                best = mid, R = mid - 1;
            else
                L = mid + 1;
        }
        if (best != -1) {
            int tl = best;
            L = 1, R = r, best = -1;
            while (L <= R) {
                int mid = L + R >> 1;
                if (6 * mid <= r && 10 * mid <= r && 15 * mid <= r)
                    best = mid, L = mid + 1;
                else
                    R = mid - 1;
            }
            if (best != -1) {
                int tr = best;
                c1 += max(0ll, tr - tl + 1);
            }
        }
        for (int i = l + 2; i <= r; ++i) {
            int divs = 0;
            for (int j = 1; j * j <= i; ++j)
                if (i % j == 0) {
                    if (j >= l && j < i) ++divs;
                    if (j * j != i && i / j != i && i / j >= l && i / j < i) ++divs;
                }
            c2 += b2(divs);
        }
        cout << all - c1 - c2 << '\n';
    }
} 
```

---

## 作者：Argon_Cube (赞：0)

非常牛的一题，我们先假设 $l=1$。

考虑两个数的情况，即 $i<j,\operatorname{lcm}(i,j)\geq i+j$。我们考虑算不合法的方案数，即 $\operatorname{lcm}(i,j)<i+j$，可以发现若 $\operatorname{lcm}(i,j)\geq 2j$ 时一定合法，那么自然算 $\operatorname{lcm}(i,j)=i+j\iff i\mid j$。此时若加上 $l$ 的限制可以二维数点做到 $\mathrm O(q+n\log n)$。

推广到三个数，同样考虑容斥，当 $\operatorname{lcm}(i,j,k)\geq 3k$ 时显然合法。那么分两类讨论：$\operatorname{lcm}(i,j,k)=k$、$\operatorname{lcm}(i,j,k)=2k$ 且 $k< i+j$。第一种情况显然就是 $\binom{d(k)-1}{2}$。

对于第二种情况可以发现当 $i<j<k,\operatorname{lcm}(i,j,k)=k$ 时必定 $i,j\leq \frac k2$ 从而 $i+j\leq k$，于是若 $i+j>k$ 则必定有 $\operatorname{lcm}(i,j,k)=2k$，这样我们就不需要考虑 $i,j$ 里面一定要多一个 $2$ 的限制。那么我们发现 $0.5k<j<k$ 并且 $j\mid 2k$，发现存在合法的 $j$ 当且仅当 $3\mid k$，此时 $j=\frac23k$。

现在 $j,k$ 都确定了，自然 $i$ 也很好确定：$i\mid 2k$ 且 $i<j$。注意到此时 $2k$ 的前 $3$ 大因子分别为 $2k,k,\frac23k=j$，也就是说 $i$ 可以取除了这三个因子外的所有 $2k$ 的因子；但是 $i+j>k$ 因此 $i>\frac k3$。也就是说，$i$ 只有最多 $2$ 种取值：$\frac 12k,\frac 25k$。因此，对于一个 $k$ 最多有两对符合 $\operatorname{lcm}(i,j,k)\leq 2k$ 且 $k<i+j$，即 $(\frac12k,\frac23k,k)$ 与 $(\frac 25k,\frac 23k,k)$。

综上，对于一个 $k$ 若 $l=1$ 时它的答案为 $\binom{k-1}{2}-\binom{d(k)-1}{2}-[6\mid k]-[15\mid k]$。

然而事实是，我们不得不面对 $l$ 的限制。显然我们并不想做一个三维的容斥（而且似乎并不可做），那么我们考虑直接硬上。对于一个 $k$，总方案数变为 $\binom{k-l}2$。对于第二种不合法情况显然可以简单变成 $-[6\mid k][k\geq 2l]-[15\mid k][2k\geq5l]$。而第一种不合法情况就很麻烦，我们需要计算 $k$ 大于等于 $l$ 的因子个数（我们记为 $d_{\geq l}(k)$）。

这样答案就是

$$\begin{aligned}
&\sum_{k=l}^r\left(\binom{k-l}{2}-\binom{d_{\geq l}(k)-1}{2}-[6\mid k][k\geq 2l]-[15\mid k][2k\geq5l]\right)\\
=&\binom{r-l+1}{3}-\sum_{k=\color{red}0}^r\binom{d_{\geq l}(k)-1}{2}-\max\left(0,\left\lfloor\frac{r}{6}\right\rfloor-\left\lfloor\frac{2l-1}{6}\right\rfloor\right)-\max\left(0,\left\lfloor\frac{r}{15}\right\rfloor-\left\lfloor\frac{5l-2}{30}\right\rfloor\right)
\end{aligned}$$

预处理出每个数的所有因子即可做到 $\mathrm O(v\log v+Tv\log d(v))=\mathrm O(v(\log v+T\log\log v))$ 的时间复杂度与 $\mathrm O(v\log v)$ 的空间复杂度并通过 Easy Version。第二项加上二维数点优化第二项的求和即可达到 $\mathrm O(v\log^2v+T\log v)$ 的时间复杂度与线性空间并通过 Hard Version，并且我们并不需要将一个询问拆成四个，因为询问等价于做一次原点为 $(0,v)$ 的二维前缀和。

---

## 作者：WaterSun (赞：0)

# 思路

这是一道极好的思维题，主要考察了：组合数学和正难则反的方法。

这题可以发现如果用直接法将十分的繁琐，于是乎，我们可以用正难则反的方法，即：总的减去不满足的。

这道题总的很好求，为：$C_{r - l + 1}^{3}$。

不满足的情况，我们就可以将题目转化为：$\operatorname{lcm}(i,j,k) < i + j +  k$ 的个数。

因为 $l \leq i < j < k \leq r$，所以 $\operatorname{lcm}{(i,j,k)} < 3k$。

又因为 $k$ 必定是 $\operatorname{lcm}{(i,j,k)}$ 的因数，所以，我们的情况就可以分为二种。

1. $\operatorname{lcm}{(i,j,k)} = k$。

2. $\operatorname{lcm}{(i,j,k)} = 2k$。

第一种情况时，我们可以枚举 $k$ 在区间 $[l,r]$ 中不为本身的约数的个数，我们令这个数为：$cnt$。那么它的贡献就为：$C_{cnt}^2$。

第二种情况时，只有为 $(3,4,6)$ 和 $(6,10,15)$ 的整数倍时，才会有成立。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

int T,l,r,ans;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	T = read();
	while (T--){
		ans = 0;
		l = read();
		r = read();
		for (re int k = l + 2;k <= r;k++){//因为 i < j < k，所以 k 要从 l + 2 开始枚举 
			int cnt = 0;
			for (re int i = 1;i * i <= k;i++){//只用枚举到 sqrt(k)，因为对于 k 的约数，最大只会到 sqrt(k)。为了避免浮点数丢失精度，要用乘法 
				if (!(k % i)){
					if (i >= l) cnt++;
					if (i != 1 && i * i != k && (k / i) >= l) cnt++;//注意不要把自己算进去了 
				}
			}
			cnt = cnt * (cnt - 1) >> 1;
			ans += cnt;
		}
		for (re int i = 1;i <= r;i++){
			if (l <= 3 * i && 6 * i <= r) ans++;//判断是否在区间当中 
			if (l <= 6 * i && 15 * i <= r) ans++;
		}
		ans = (r - l + 1) * (r - l) / 2 * (r - l - 1) / 3 - ans;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

