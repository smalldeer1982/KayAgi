# 题目信息

# On Sum of Fractions

## 题目描述

我们设：

- $v(n)$是不超过$n$的最大素数；

- $u(n)$是大于$n$的最小素数。

计算![](https://cdn.luogu.org/upload/vjudge_pic/CF396B/35810ad29d9f6c4fb0ebb0082bbbd3e3b2a406a1.png)。

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
1/6
7/30
```

# AI分析结果

### 题目内容
# 分数之和

## 题目描述
我们设：
- \(v(n)\)是不超过\(n\)的最大素数；
- \(u(n)\)是大于\(n\)的最小素数。
计算\(\sum_{i = 2}^{n}\frac{1}{v(i)u(i)}\) 。

## 样例 #1
### 输入
```
2
2
3
```
### 输出
```
1/6
7/30
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过对\(\sum_{i = 2}^{n}\frac{1}{v(i)u(i)}\) 展开并观察规律，利用分数裂项的方法进行化简，最终得到一个简洁的表达式，再通过暴力寻找\(v(n)\)和\(u(n)\)来计算结果。各题解的不同主要体现在对规律的推导过程表述上。难点在于如何通过观察式子找到裂项规律并证明其正确性。

### 所选的题解
- **作者：Moco_jof (赞：3)  星级：4星**
    - **关键亮点**：先引入分数裂项公式，通过具体例子\(n = 9\)详细推导，得出通用公式，思路清晰，代码实现简洁明了。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：通过从\(n\)开始向两边暴力遍历寻找\(v(n)\)和\(u(n)\)，代入推导出的公式计算分子分母，再用`__gcd`求最大公约数进行约分。
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long 
int t,n,v,u,a,b,gcd0;
bool p(int);
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=n;i>=2;i--){ 
			if(p(i)){
				v=i;
				break;
			}
		}
		for(int i=n+1;;i++){ 
			if(p(i)){
				u=i;
				break;
			}
		}
		a=2*n+2+u*v-2*u-2*v,b=2*v*u; 
		gcd0=__gcd(a,b);
		cout<<a/gcd0<<'/'<<b/gcd0<<'\n';
	}
	return 0;
} 
bool p(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			return false;
		}
	}
	return true;
}
```
- **作者：hank0402 (赞：2)  星级：4星**
    - **关键亮点**：以\(n = 11\)为例展开式子，详细分析重复分式并化简，逐步推导出一般形式，对最后一项的处理解释清晰，还给出了粗略证明。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：与上一题解类似，通过暴力遍历确定\(v(n)\)和\(u(n)\)，根据推导出的公式计算分子分母，利用`__gcd`约分输出。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool prime(int n) { 
	if(n == 1) return false;
	for(int i = 2; i * i <= n; ++i) {
		if(n % i == 0) return false;
	}
	return true;
}
int T;
int main() {
	cin >> T;
	while(T --) {
		long long n, v, u; 
		cin >> n;
		u = n + 1;
		v = n;
		while(!prime(v)) u ++; 
		while(!prime(u)) v --; 
		long long fz = v * u - 2 * u  + 2 * n - 2 * v + 2, fm = 2 * u * v; 
		long long g = __gcd(fz, fm);
		fz /= g; fm /= g; 
		cout << fz << '/' << fm << endl;
	} 
	return 0;
}
```
- **作者：luuia (赞：1)  星级：4星**
    - **关键亮点**：先详细介绍裂项相消法和素数相关知识，包括欧拉筛法（虽未在本题使用），对式子的猜想、证明过程完整且详细。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：通过`prime`函数判断素数，暴力寻找\(v(n)\)和\(u(n)\)，按照推导出的公式计算并利用`gcd`函数约分输出。
```cpp
#include <bits/stdc++.h>
using namespace std;

int read()//快读 
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

void write(long long a)//快写 
{
	if(a > 9) write(a / 10);
	putchar(a % 10 + '0');
}

long long gcd(long long x,long long y)//求最小公因数
{
    if(y == 0) return x;
    else
    {
    	return gcd(y,x % y);
	}
}

bool prime(long long x)//判断是否为素数
{
	for(long long i = 2;i * i <= x;i++)
	{
		if(x % i == 0) return 0;	
	}
	return 1;
}

int solve(int n)//解决问题
{
	long long u = n + 1,v = n;
	while(!prime(u))
	{
		u++;
	}
	while(!prime(v))
	{
		v--;
	}
	long long a = (u * v) + (2 * n) - (2 * u) - (2 * v) + 2;
	long long b = 2 * u * v;
	long long d = gcd(a,b);
	a /= d;
	b /= d;
	cout << a << "/" << b << endl;
}

int main() 
{
	int T;
	T = read();
	while(T--)
	{
		int x;
		x = read();
		solve(x);
	}
	return 0;
}
```

### 最优关键思路或技巧
通过列举较小\(n\)值展开式子，观察到分式的重复规律，利用分数裂项公式\(\frac{b - a}{ab} = \frac{1}{a} - \frac{1}{b}\)对式子进行化简，从而避免直接求和的复杂计算。在实现中，利用素数判断的基本方法暴力寻找\(v(n)\)和\(u(n)\)。

### 可拓展之处
同类型题通常围绕数列求和，结合数论知识如素数、合数等概念，通过寻找规律、裂项相消等方法化简式子求解。类似算法套路是对于复杂求和式子，先通过列举小数据找规律，再利用常见的数学方法（如裂项、通项公式等）进行化简。

### 洛谷相似题目推荐
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的同余方程与扩展欧几里得算法，与本题一样涉及数学推导与计算。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过寻找数列规律，结合简单数学运算求解，与本题找规律化简式子思路类似。
- [P1403 [AHOI2005]约数研究](https://www.luogu.com.cn/problem/P1403)：关于数论中约数的研究，通过数学方法优化计算，与本题利用数学知识优化计算过程相似。 

---
处理用时：80.04秒