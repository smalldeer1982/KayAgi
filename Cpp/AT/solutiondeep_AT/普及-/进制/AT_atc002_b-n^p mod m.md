# 题目信息

# n^p mod m

## 题目描述

求 $n^p$ $mod$ $m$ 的值

## 说明/提示

对于100%的数据 $1≤n,m≤10^9$ $1≤p≤10^{14}$

翻译提供者：Ryan_wxn_

## 样例 #1

### 输入

```
12 15 7```

### 输出

```
3```

## 样例 #2

### 输入

```
123456789 234567894 6574837563712```

### 输出

```
120678297```

# AI分析结果

### 题目内容重写
# n^p mod m

## 题目描述

求 $n^p$ $mod$ $m$ 的值

## 说明/提示

对于100%的数据 $1≤n,m≤10^9$ $1≤p≤10^{14}$

翻译提供者：Ryan_wxn_

## 样例 #1

### 输入

```
12 15 7```

### 输出

```
3```

## 样例 #2

### 输入

```
123456789 234567894 6574837563712```

### 输出

```
120678297```

### 题解综合分析与结论

本题的核心是计算大指数模幂运算，即 $n^p \mod m$。由于 $p$ 的范围非常大（$1 \leq p \leq 10^{14}$），直接计算 $n^p$ 会导致溢出和超时。因此，必须使用快速幂算法来高效地计算模幂。

快速幂算法的核心思想是通过将指数 $p$ 分解为二进制形式，利用幂的乘法性质逐步计算结果。具体来说，每次将指数右移一位，同时将底数平方，并根据当前最低位是否为1来决定是否将结果乘上当前的底数。这种方法将时间复杂度从 $O(p)$ 降低到 $O(\log p)$，非常适合处理大指数的情况。

### 所选高星题解

#### 题解1：ShineEternal (5星)
**关键亮点**：
- 详细解释了快速幂的原理，并通过具体例子展示了如何将指数分解为二进制形式。
- 代码简洁明了，直接实现了快速幂算法。

**核心代码**：
```cpp
#include<cstdio>
using namespace std;
long long m,n,p;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	int ans=1;
	for(;p;p>>=1,n=n*n%m)
	{
		if(p&1)
			ans=ans*n%m;
	} 
	printf("%d\n",ans);
	return 0;
}
```

#### 题解2：weak_ddb (4星)
**关键亮点**：
- 提供了快速幂的推导过程，解释了如何通过二进制分解来优化计算。
- 代码清晰，注释详细，适合初学者理解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,p,m;
int main()
{
    cin>>n>>m>>p;
    ll ans=1;
    while(p>0)
	{
        if(p&1)ans=ans*n%m;
        p=p/2;
        n=n*n%m;
    }
    cout<<ans;
    return 0;
}
```

#### 题解3：ueettttuj (4星)
**关键亮点**：
- 引入了欧拉定理，通过欧拉函数将指数缩小到更容易计算的范围。
- 适用于指数非常大的情况，进一步优化了计算效率。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,p,phi,mod;
long long poww(long long x,long long y){ 
	long long anss=1,res=x;
	while(y){
		if(y%2) anss=anss*res%mod;
		res=res*res%mod;
		y>>=1;
	}
	return anss;
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&p);
	mod=m;
	phi=m;
	for(long long i=2;i*i<=m;i++){
		if(m%i==0){
			phi=phi/i*(i-1);
			while(m%i==0) m/=i;   
		}
	} 
	if(m>1) phi=phi/m*(m-1);
	if(p>=phi) printf("%lld\n",poww(n,p%phi+phi));  
	else printf("%lld\n",poww(n,p));
	return 0;
}
```

### 最优关键思路与技巧
1. **快速幂算法**：通过将指数分解为二进制形式，逐步计算结果，时间复杂度为 $O(\log p)$。
2. **欧拉定理**：当指数非常大时，可以通过欧拉函数将指数缩小到更容易计算的范围，进一步优化计算效率。

### 可拓展之处
- **矩阵快速幂**：快速幂算法可以推广到矩阵运算，用于解决递推关系等问题。
- **大数模幂运算**：在处理大数模幂运算时，快速幂算法是必不可少的工具。

### 推荐题目
1. [P1226 【模板】快速幂||取余运算](https://www.luogu.org/problem/P1226)
2. [P5091 【模板】扩展欧拉定理](https://www.luogu.org/problem/P5091)
3. [P1962 斐波那契数列](https://www.luogu.org/problem/P1962)

### 个人心得总结
- **调试经历**：在处理大指数时，直接计算会导致溢出和超时，必须使用快速幂算法。
- **踩坑教训**：在实现快速幂时，注意每次循环都要对底数进行平方并取模，以避免溢出。
- **顿悟感想**：通过将指数分解为二进制形式，可以显著提高计算效率，这是解决大指数模幂问题的关键。

---
处理用时：43.06秒