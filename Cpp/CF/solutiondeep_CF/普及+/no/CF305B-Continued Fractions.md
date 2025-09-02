# 题目信息

# Continued Fractions

## 题目描述

A continued fraction of height $ n $ is a fraction of form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/19ade84928d3d628a6e212b03adbbf8bc0856736.png). You are given two rational numbers, one is represented as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png) and the other one is represented as a finite fraction of height $ n $ . Check if they are equal.

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a7429bd0927ab226e00de904e1ba240c58b09318.png).

In the second sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a01a984749367ddde5131c663127bc347e31f0a2.png).

In the third sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/4db9464841d1b99996f6c98f75df85058aee123f.png).

## 样例 #1

### 输入

```
9 4
2
2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
9 4
3
2 3 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
9 4
3
1 2 4
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 连分数

## 题目描述
高度为 $n$ 的连分数是形如![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/19ade84928d3d628a6e212b03adbbf8bc0856736.png) 的分数。给定两个有理数，一个表示为![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png)，另一个表示为高度为 $n$ 的有限分数。检查它们是否相等。

## 说明/提示
在第一个样例中，![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a7429bd0927ab226e00de904e1ba240c58b09318.png)。

在第二个样例中，![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a01a984749367ddde5131c663127bc347e31f0a2.png)。

在第三个样例中，![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/4db9464841d1b99996f6c98f75df85058aee123f.png)。

## 样例 #1
### 输入
```
9 4
2
2 4
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
9 4
3
2 3 1
```
### 输出
```
YES
```

## 样例 #3
### 输入
```
9 4
3
1 2 4
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕如何避免直接暴力计算连分数带来的精度问题展开。多数题解采用对连分数计算过程中的分子分母不断约分，最后与给定分数 $\frac{p}{q}$ 比较分子分母是否相等的方法。部分题解通过将连分数的每一项逐步移到等式左边进行处理，还有题解利用模运算和哈希的思想来解决问题。

### 所选的题解
- **作者：XXh0919 (5星)**
    - **关键亮点**：思路清晰简洁，直接在计算连分数过程中每次通过 `__gcd` 函数对分子分母约分，最后与给定分数比较。代码简洁明了，易于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long//记得开 long long
using namespace std;
const int N=3e5+15;

int n,q,p;
int a[N];

signed main(){
	scanf("%lld %lld %lld",&p,&q,&n);
	int t=__gcd(p,q);
	p/=t,q/=t;//约分 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	int zi=a[n],mu=1;
	for(int i=n-1;i>=1;i--){
		int t=__gcd(zi,mu);
		zi/=t,mu/=t;//约分 
		swap(zi,mu); 
		zi=mu*a[i]+zi;//化成带分数 
	}
	if(p==zi&&q==mu) puts("YES");
	else puts("NO");
	return 0;
} 
```
    - **核心实现思想**：先对给定分数 $\frac{p}{q}$ 约分，然后从连分数最后一项开始，每次对当前分子分母约分，交换后与前一项计算得到新的分子，最后比较结果与给定分数是否相等。
- **作者：ztxtjz (4星)**
    - **关键亮点**：思路与 XXh0919 类似，同样是通过记录分子分母并不断约分来求解，代码实现较为清晰，且自定义了 `gcd` 函数。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,fz,fm=1,p,q,a[100],ans;  //fz是分子，fm是分母
ll gcd(ll a,ll b){return a==0?b:gcd(b%a,a);}  //最大公约数
int main()
{
	cin>>p>>q>>n;
	ll t=gcd(p,q);  //p、q约分
	p/=t,q/=t;
	for(int i=1;i<=n;i++) cin>>a[i];
	fz=a[n];  //分子初始化
	for(int i=n-1;i;i--)
	{
		ll t=gcd(fz,fm);  //最大公约数
		fz/=t,fm/=t;  //分子、分母约分
		swap(fz,fm);  //分数取倒数
		fz=a[i]*fm+fz;  //通分
	}
	if(p==fz&&q==fm) printf("YES");
	else printf("NO");
	return 0;
}
```
    - **核心实现思想**：自定义 `gcd` 函数用于约分，先对给定分数约分，然后从连分数后往前计算，每次约分、交换分子分母并计算新分子，最后比较结果。
- **作者：EasonLiang (4星)**
    - **关键亮点**：采用独特的哈希思想，选定大质数，将分数转换为模意义下的整数，通过双哈希减小冲突概率，思路新颖。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 9e1 + 20;
const ll mod[2] = {ll (1e9 + 7), ll (1e7 - 9)}; // 双哈希，注意要用大质数
int n;
ll p, q, a[maxn], val[2][2]; // val[0] 数组存 p/q 的值，val[1] 数组存连分数的值

ll inv (ll x, ll mod) { // 在 log 时间内求出逆元
    return x ^ 1? (mod - mod / x) * inv (mod % x, mod) % mod : 1;
}

int main () {
    scanf ("%lld%lld%d", &p, &q, &n);

    for (int i = 1; i <= n; ++i) scanf ("%lld", &a[i]);

    val[0][0] = (p % mod[0]) * inv (q % mod[0], mod[0]) % mod[0];
    val[0][1] = (p % mod[1]) * inv (q % mod[1], mod[1]) % mod[1];
    val[1][0] = a[n] % mod[0]; val[1][1] = a[n] % mod[1];
    
    for (int i = n - 1; i >= 1; --i) // 模拟题意计算连分数的值
        val[1][0] = (inv (val[1][0], mod[0]) + a[i]) % mod[0],
        val[1][1] = (inv (val[1][1], mod[1]) + a[i]) % mod[1];

    return!printf ((val[0][0] ^ val[1][0] || val[0][1] ^ val[1][1])? "NO" : "YES"); // 判断哈希值是否相等并输出结果
}
```
    - **核心实现思想**：利用 `inv` 函数求逆元，将给定分数和连分数分别转换为模两个大质数下的整数，通过比较这两个哈希值判断是否相等。

### 最优关键思路或技巧
在处理高精度分数计算时，通过对分子分母不断约分来避免高精度运算，这是一种简单有效的方法。同时，利用模运算和哈希思想来解决相等判断问题，为这类问题提供了新的思路。

### 可拓展之处
同类型题可考虑涉及分数运算、连分数相关的题目，类似算法套路可用于处理高精度有理数的比较、运算等问题。

### 推荐题目
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)：涉及字符与数字的对应关系，可类比本题中分数与连分数的对应判断。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：通过模拟和数学计算解决问题，与本题通过计算判断结果类似。
- [P1304 哥德巴赫猜想](https://www.luogu.com.cn/problem/P1304)：运用数学知识解决数论相关问题，与本题运用数学方法处理分数问题思路相符。

### 个人心得摘录与总结
部分作者提到直接暴力计算会因精度问题不可行，强调了约分的重要性，如不先对给定分数 $\frac{p}{q}$ 约分可能导致错误结果，这提醒在处理分数相关问题时要时刻关注精度和化简。 

---
处理用时：105.03秒