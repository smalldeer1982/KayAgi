# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 样例 #1

### 输入

```
3
1
3
13```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000```

# 题解

## 作者：CSPJ10pts (赞：1)

~~蓝书真香。~~

## 题意

给出一个整数 $N$，每次可以在不超过 $N$ 的素数中随机选择一个 $P$，如果 $P$ 是 $N$ 的约数，则把 $N$ 变成 $N \div P$，否则 $N$ 不变。问平均多少次随机选择才能把 $N$ 变成 $1$？

## 分析

我们设 $f(x)$ 为通过随机选择把 $x$ 变成 $1$ 的平均次数，$g(x)$ 为 $x$ 的素因子的个数，$p(x)$ 为小于 $x$ 的素数个数，$cnt_{i,j}$ 为 $i$ 的第 $j$ 个素因子。根据全期望公式，$f(x)$ 由自己 $1$ 次随机 $+$  随机后得到的数不是 $x$ 的素因子的情况 $+$ 随机后得到的数是 $x$ 的素因子的情况。转换成数学语言就是： $f(x)=1+f(x) \times [1-\frac{g(x)}{p(x)}] + \sum_{i=1}^{g(x)}{f(\frac{x}{cnt_{x,i}})\frac{1}{p(x)}}$，经过移项整理后得到 $f(x)=\frac{\sum_{i=1}^{g(x)}{f(\frac{x}{cnt_{x,i}})} + p(x)}{g(x)}$。边界为 $f(1) = 0$。由于 $cnt_{x,i} < x$，所以可以用记忆化搜索。

## 代码

和蓝书差不多。

```
#include <iostream>
using namespace std;
#define N 1000001
int prime[600001], cnt, n, t, num;
double f[N];
bool a[N];
double dp(int x) {
	if (x == 1) return 0.0; // 边界
	if (f[x]) return f[x]; // 如果 f(x) 已经调查过了，直接返回
	int g = 0, p = 0; // 我们的 g(x)，p(x)
	for (int i = 1; i <= cnt && prime[i] <= x; i++, p++) if (!(x % prime[i])) g++, f[x] += dp(x / prime[i]);
	return f[x] = (f[x] + p) / g; // 计算 f(x)
}
int main() {
	for (int i = 2; i <= N; i++) if (!a[i]) {prime[++cnt] = i; for (int j = 2 * i; j <= N; j += i) a[j] = 1;} // 预处理一个素数表
	scanf("%d", &t);
	while (++num <= t) {
		scanf("%d", &n);
		printf("Case %d: %.6lf\n", num, dp(n));
	}
    return 0;
}
```

[通过记录~](https://www.luogu.com.cn/record/106249454)

---

## 作者：Captain_Paul (赞：1)

题意：给定一个数n，每次可以将它除以一个小于它的质数，也可以不动，问变成1的期望步数

期望dp，可以用记忆化搜索实现

和一般的期望题目类似，定义$f[i]$表示从$i$到$1$的期望步数

用$num$表示小于$i$的质数的个数，$tot$表示小于$i$且能整除$i$的质数的个数

转移方程可表示为:$f[i]=f[i]*(num-tot)/num+f[i/j]/num+1$

其中$j$是枚举出的小于$i$且能整除$i$的质数

化简后记忆化搜索即可

注意多组询问不需要清空数组，因为每一个数的答案是固定的

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+5;
int prime[N/10],cnt;
double f[N];
bool prim[N];
inline void Get_Prime()
{
	for (int i=2;i<=N-5;i++)
	{
		if (!prim[i]) prime[++cnt]=i;
		for (int j=1;j<=cnt&&i*prime[j]<=N-5;j++)
		{
			prim[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}
double dfs(int x)
{
	if (x==1) return 0;
	if (f[x]) return f[x];
	int num=0,tot=0;
	for (int i=1;i<=cnt&&prime[i]<=x;i++)
	{
		++num;
		if (x%prime[i]==0) ++tot,f[x]+=dfs(x/prime[i]);
	}
	return f[x]=(f[x]+num)/tot;
}
int main()
{
	int T; scanf("%d",&T); Get_Prime();
	for (int t=1;t<=T;t++)
	{
		int x; scanf("%d",&x);
		printf("Case %d: %.10lf\n",t,dfs(x));
	}
	return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：0)

# UVA11762 Race To 1

### 题意

给你一个整数 $num$，等概率地选取任意一个不超过 $num$ 的素数 $p$。如果 $p$ 是 $num$ 的质因子，就将 $num$ 除以 $p$，否则 $num$ 不变。求得到 $1$ 的期望步数。

$num \le 10^6$，多测，$T \le 1000$。

### 思路

我们约定 $p$ 代表一个质数，$fact_i$ 表示 $i$ 的质因子个数，$cnt_i$ 表示小于等于 $i$ 的质数个数。设 $i$ 的期望步数为 $f_i$，那么显然有 $f_1 = 0$。

根据题意，我们来分析一下 $f_i$ 是由哪几部分组成的。  
首先是 $i$ 的质因子，选到一个质因子的概率是 $\frac{1}{cnt_i}$，那么这一部分的总和就是 $\sum_{p | i}{\frac{f_{i/p}}{cnt_i}}$。  
然后是剩余的质数，选到这部分的概率是 $1 - \frac{fact_i}{cnt_i}$，而这一部分是转移到 $i$ 本身，于是这部分的和是 $(1 - \frac{fact_i}{cnt_i})f_i$。  
还有什么呢？不要忘了这次转移本身的 $1$ 次。

根据全期望公式，我们把上边的部分全部加起来，就是要求的 $f_i$：

$$
f_i = 1 + (1 - \frac{fact_i}{cnt_i})f_i + \sum_{p | i}{\frac{f_{i/p}}{cnt_i}}
$$

化简一下得到：

$$
f_i = \frac{\sum_{p | i}f_{i / p} - cnt_i}{fact_i}
$$

于是我们先筛一遍质数，然后做一下记搜就好了。

### 代码

```cpp
/**
 * @file    UVA11762 Race to 1.cpp
 * @author  ForgotDream
 * @brief   记忆化搜索
 * @date    2023-02-20
 */
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;
using i64 = long long;

static const int N = 1e6 + 50;
int T;
int primeCnt, prime[N];
bool isNotPrime[N], vis[N];
double f[N];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++primeCnt] = i;
		for (int j = 1; j <= primeCnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

double solve(int num) {
	if (num == 1) return 0;
	if (vis[num]) return f[num];
	vis[num] = true;
	int fact = 0, cnt = 0;
	for (int i = 1; i <= primeCnt && prime[i] <= num; i++) {
		cnt++;
		if (!(num % prime[i])) {
			fact++;
			f[num] += solve(num / prime[i]);
		}
	}
	return f[num] = (f[num] + cnt) / fact;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	getPrime(1e6);

	cin >> T;
	for (int t = 1; t <= T; t++) {
		int num;
		cin >> num;
		cout << "Case " << t << ": " << fixed << setprecision(10) << solve(num) << '\n';
	}

	return 0;
}
```



---

## 作者：斗神_君莫笑 (赞：0)

又是一道蓝书的题  
观察公式![](https://cdn.luogu.com.cn/upload/pic/73555.png)    
用感性的语言描述就是1+转移失败的状态+所有可行的转移状态   
状态转移失败会产生自环，这对答案没有影响  
移项，我们就求出了f(x)如何转移  
显然可以通过递推从前往后刷表，但是也可以记忆化搜索解决  
实现上面大致等同蓝书   
```cpp
#include<bits/stdc++.h>
using namespace std;
int is_prime[1000010],prime[1000010],num,vis[1000010];
double f[1000010];
double dfs(int x){
	if(x==1)return 0;
	if(vis[x])return f[x];
	vis[x]=1;
	int all=0,can=0;
	for(int i=1;i<=num&&prime[i]<=x;++i){
		++all;
		if(x%prime[i]==0){
			++can;
			f[x]+=dfs(x/prime[i]);
		}
	}
	f[x]+=all;f[x]/=can;
	return f[x];
}
int main(){
	is_prime[0]=is_prime[1]=1;
	prime[++num]=2;
	for(int i=4;i<=1000000;i+=2)is_prime[i]=1;
	for(int i=3;i<=1000000;i+=2)
		if(!is_prime[i]){
			prime[++num]=i;
			for(int j=2*i;j<=1000000;j+=i)is_prime[j]=1;
		}
	int t;
	scanf("%d",&t);
	for(int cas=1;cas<=t;++cas){
		int n;
		scanf("%d",&n);
		printf("Case %d: %.10f\n",cas,dfs(n));
	}
	return 0;
}
```



---

