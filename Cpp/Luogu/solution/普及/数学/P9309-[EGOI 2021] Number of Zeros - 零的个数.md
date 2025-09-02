# [EGOI 2021] Number of Zeros / 零的个数

## 题目背景

Day 1 Problem A.

题面译自 [EGOI2021 zeros](https://stats.egoi.org/media/task_description/2021_zeros_en.pdf)。

## 题目描述

圣诞老人已经在准备 $2021$ 年圣诞节。他希望买正整数个礼物，使得可以平均分给所有不淘气的孩子。然而，他不知道具体有多少不淘气的孩子，只知道数量一定在 $a$ 和 $b$ 之间。他希望买最少的正整数个礼物，使得可以被任何 $x\in\{a,a+1,\ldots,b\}$ 个孩子平分。

他已经计算出这（可能很大的）礼物数量，但他不确定计算是否正确，希望你可以进行一些基本的正确性检查。你可以告诉他答案的后导零个数吗？

## 说明/提示

**样例 $1$ 解释**

如果可能有 $1$ 至 $6$ 个不淘气的孩子，圣诞老人至少需要 $60$ 个礼物（这是最小的能被 $1,2,3,4,5,6$ 整除的正整数），而 $60$ 有一个后导零。

---

**样例 $2$ 解释**

如果可能有 $10$ 或 $11$ 个不淘气的孩子，圣诞老人会买 $110$ 个礼物。

---

**数据范围**

对于全部数据，$1\le a\le b\le 10^{18}$。

- 子任务一（$6$ 分）：$b\le 16$。
- 子任务二（$7$ 分）：$b\le 40$。
- 子任务三（$9$ 分）：$a=1$，$b\le 200$。
- 子任务四（$12$ 分）：$b-a\le 10^6$。
- 子任务五（$17$ 分）：$a=1$。
- 子任务六（$49$ 分）：无特殊限制。

## 样例 #1

### 输入

```
1 6```

### 输出

```
1```

## 样例 #2

### 输入

```
10 11```

### 输出

```
1```

# 题解

## 作者：Red0rangE (赞：7)

## 题意理解

给出两个正整数 $a$ 和 $b$。
想要让礼物可以被 $x \in \{a,a+1,…,b\}$ 个孩子平分。
求答案的后导零个数。

## 思路阐述

首先想要让礼物可以被 $x \in \{a,a+1,…,b\}$ 个孩子平分即为求这个集的最小公倍数，但是数据范围很大，直接求显然会超时。
题目中要求的是后导零的个数，即答案中有几个 $10$ 作为因子，而 $10$ 又可以分解为 $2\times 5$，所以后导零的个数即为答案中质因子 $2$ 的个数和 $5$ 的个数的最小值。
接下来便是求范围内含因子 $2$ 最多的数有几个 $2$ 因子和含因子 $5$ 最多的数有几个 $5$ 因子。

## 代码呈现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int unsigned long long

int a,b;

int f(int x,int y,int k){//在范围x~y中因子k的最大个数
    int cnt=0;
    while (x!=y){
        x/=k;
        y/=k;//不断除k，增加答案
        cnt++;
    }
    return cnt-1;//注意答案最后要减一
}

signed main(){

    scanf("%lld%lld",&a,&b);
    a--;//a在范围内，下界要低一个
    printf("%lld",min(f(a,b,2),f(a,b,5)));
    return 0;
    
}
```

希望可以帮到各位大佬。

---

## 作者：autumnrain_qhc (赞：6)

这是一个数学题！！！

因为 $2^n \times 5^m \times z$ 的后缀 $0$ 个数为 $\min(n, m)$。

所以仅需求出 $n, m$ 最大值就可以了。

# 上代码
```
#include <bits/stdc++.h>
using namespace std;
long long a, b;
long long check(long long x){
    long long na = a, nb = b;
    int cnt = -1;
    while(na != nb){
        cnt++;
        na /= x, nb /= x;
    }
    return max(cnt, 0);
}
int main(){
    cin >> a >> b;
    a--;
    cout << min(check(2), check(5));
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：5)

真实的答案是 $\operatorname{lcm}(a,a+1,\dots,b)$。因为礼物个数一定是所有可能人数的公倍数。

因为一个正整数 $\times10$ 就等于加一个后导零，所以有多少个后导零就能被 $10$ 的多少次方整除。

$10=2\times5$。所以我们需要考虑到质因数 $2$ 和 $5$。最小公倍数的某个质因数个数是所有数的这个质因数个数的最大值。

因为 $a,b\le10^{18}$，所以经过计算最多只可能有 $59$ 个质因数 $2$ 和 $25$ 个质因数 $5$。这个值域非常小，可以直接枚举质因数个数。假设有 $x$ 个质因数 $2$ 和 $5$，检查 $a$ 到 $b$ 中是否有数被 $2^x$ 和 $5^x$ 整除。如果都有就成立，否则不成立。

```cpp
#include<iostream>
#define int long long
using namespace std;
int a,b;
bool chk(int x)
{
    if(a%x==0||b%x==0)return 1;
    return a/x!=b/x;
}
signed main()
{
    cin>>a>>b;
    int mul2=1,mul5=1;
    for(int i=1;i<=60;i++)
    {
        mul2*=2,mul5*=5;
        if(!chk(mul2)||!chk(mul5))
        {
            cout<<i-1<<endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：翟翟 (赞：3)

阅读题目，可知要求的是 $[a,b]$ 的最小公倍数的后导零的个数，因为 $10=2\times 5$，$2^x\times 5^y\times z$ 后导零个数为 $\min(x,y)$，而它等于 $[a,b]$ 中存在的 $2$ 的最高次幂与 $5$ 的最高次幂的较小值。

我用二分法求区间中存在的 $2$ 的最高次幂与 $5$ 的最高次幂。

## Code
```
#include<iostream>
using namespace std;
typedef long long ll;
ll a,b,p[2][61];
int solve(ll x,ll y,int k,int limit){
	int mid=0,l=1,r=limit;
	for(;l<=r;){
		mid=(l+r)>>1;
		if(y/p[k][mid]>x/p[k][mid])l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
int main(){
	p[0][0]=p[1][0]=1;
	for(int i=1;i<=60;++i)
		p[0][i]=p[0][i-1]<<1;
	for(int i=1;i<=26;++i)
		p[1][i]=p[1][i-1]*5;
	//预处理2和5的次幂
	scanf("%lld%lld",&a,&b);
	printf("%d\n",min(solve(a-1,b,0,60),solve(a-1,b,1,26)));
	return 0;
}
```

时间复杂度 $\mathcal{O}(\log b)$。

---

## 作者：Untitled10032 (赞：3)

## 题意

给定一个区间 $[a, b]$，求 $\rm{lcm} \{a, a + 1, ..., b\}$（十进制下的）后导零个数。

## 思路

如果使用暴力做法，则可以发现只需要统计区间中每个数分解质因数后，$2$ 和 $5$ 的指数大小，求出所有数中 $2$ 的指数的最大值，和 $5$ 的指数的最大值，两个数取最小值即为最后的答案。（这种方法应该可以通过前四个子任务。）

但是注意到 $1 \leq a \leq b \leq 10 ^ {18}$，所以需要优化。

如果一个数可以被 $2^k$ 整除，那么它一定可以表示为 $2^k \times n, n \in \mathbb D$，那么在区间 $[a, b]$ 之中存在一个整数，使得它可以被 $2^k$ 整除的充要条件是 $\exists n \in \mathbb D, s.t. \  n = \frac m {2^k}, m \in [a, b]$，即区间 $[\frac a {2^k}, \frac b {2^k}]$ 之内至少包含一个整数。

易得如果区间中包含整数，那么这些整数中一定有 $\lfloor \frac b {2^k} \rfloor$，因为它是离区间右界最近的一个整数。我们判断这个数是否在区间内即可，即比较 $\lfloor \frac b {2^k} \rfloor$ 和 $\frac a {2^k}$ 的大小，若前者大于等于后者则区间中存在数可以被 $2^k$ 整除，反之则不存在。

我们可以从小到大枚举 $k$，如果有数可以被 $2^k\ (k \in \mathbb {N*})$ 整除，那么它一定可以被 $2^{k - 1}$ 整除。所以枚举到第一个没有可以整除的数的 $k$ 就可以停止，并记录 $k - 1$ 为区间中 $2$ 的最大指数。

对于计算 $5^k$ 的整除情况同理。

时间复杂度为 $O(\log_2 n + \log_5 n)$，符合要求。

## 代码

**注意除法的精度问题，建议使用 `long double` 进行运算。**

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    long long l, r;
    cin >> l >> r;
    int res_2 = 0;
    for (int i = 0; ; i++) {
        const long long t = 1LL << i;
        if (r / t < (long double)l / t) {
            res_2 = i - 1;
            break;
        }
    }
    int res_5 = 0;
    long long t = 1;
    for (int i = 0; ; i++) {
        if (r / t < (long double)l / t) {
            res_5 = i - 1;
            break;
        }
        t *= 5;
    }
    cout << min(res_2, res_5);
    return 0;
}
```


---

## 作者：__zfy__ (赞：1)

这是一道数学题。

### 分析和思路与部分伪代码
因为 $2 \times 5 = 10$，所以一个数的后导 $0$ 的个数就等于分解质因数后，$2$ 和 $5$ 的指数的最小值。

我们可以用一个函数来写 $\text{lcm}(a,a+1,...,b)$，分解质因数后 $2$ 和 $5$ 的指数。

```
ll h(ll x)
{
	ll ta=a-1,tb=b,cnt=-1;
	while(ta!=tb)
	{
		cnt++;           //计数++
		ta/=x,tb/=x;
	}
	return max(cnt,0);
}
```
主函数部分只需要输出 $\min(h(2),h(5))$ 就可以了。

---

## 作者：small_turtle (赞：0)

因为最少满足条件的数为 $a\sim b$ 的最小公倍数。而一些数的最小公倍数的后导零的个数取决于它 $2$ 和 $5$ 的个数，$2^x\times 5^y\times z$ 后导零的个数为 $\min(x,y)$。于是我们只需要分别找出 $2$ 和 $5$ 的最高次幂，求最小值即可。
```cpp
//Time:2023.5.3
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
const ll inf=0x3f3f3f3f;
const double eps=1e-6;
using namespace std;

ll a,b;

ll sol(int x)
{
	ll res=-1,_a=a,_b=b;
	while(_a!=_b)
	{
		++res;
		_a/=x,_b/=x;
	}
	return res;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	scanf("%lld%lld", &a, &b);
  	--a;
	printf("%lld", min(sol(2), sol(5)));
	return 0;
}


```

---

## 作者：Piggy343288 (赞：0)

此题问 $\operatorname{lcm}(a\sim b)$ 的后导 $0$ 个数。  
考虑 $\operatorname{lcm}$ 相当于对唯一分解中的素数的指数取 $\max$，此题等价于：
> 定义 $\operatorname{g}(x,y,z)$ 在 $[a,b]$ 的所有整数中，分解出 $z$ 的最高次幂是多少，那么 $ans=\min(\operatorname{g}(a,b,2),\operatorname{g}(a,b,5))$。  

下面转化为求 $\operatorname{g}$。其实这也显然，我们只需要对 $a,b$ 持续的除以 $z$，直到 $a=b$，这说明 $a,b$ 在 $z$ 的幂的“同一倍数”里。再考虑一下边界问题，我们不难得到下面的代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long get(long long x,long long y,int a){
    int cnt=-1;
    while(x!=y){
        cnt++;
        x/=a,y/=a;
    }
    return cnt;
}
int main() {
    long long a,b;
    cin>>a>>b;
    a--;
    cout<<min(get(a,b,2),get(a,b,5));
}
```
即为本题答案。

---

