# Square Difference

## 题目描述

Alice has a lovely piece of cloth. It has the shape of a square with a side of length $ a $ centimeters. Bob also wants such piece of cloth. He would prefer a square with a side of length $ b $ centimeters (where $ b < a $ ). Alice wanted to make Bob happy, so she cut the needed square out of the corner of her piece and gave it to Bob. Now she is left with an ugly L shaped cloth (see pictures below).

Alice would like to know whether the area of her cloth expressed in square centimeters is [prime.](https://en.wikipedia.org/wiki/Prime_number) Could you help her to determine it?

## 说明/提示

The figure below depicts the first test case. The blue part corresponds to the piece which belongs to Bob, and the red part is the piece that Alice keeps for herself. The area of the red part is $ 6^2 - 5^2 = 36 - 25 = 11 $ , which is prime, so the answer is "YES".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/26aa17f955334a29eef8994b7c5af8ed29b66689.png)In the second case, the area is $ 16^2 - 13^2 = 87 $ , which is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/bb700dc40c3e1b73968059e8f9c3fba6a4d8a953.png)In the third case, the area of the remaining piece is $ 61690850361^2 - 24777622630^2 = 3191830435068605713421 $ . This number is not prime because $ 3191830435068605713421 = 36913227731 \cdot 86468472991  $ .

In the last case, the area is $ 34^2 - 33^2 = 67 $ .

## 样例 #1

### 输入

```
4
6 5
16 13
61690850361 24777622630
34 33
```

### 输出

```
YES
NO
NO
YES
```

# 题解

## 作者：一扶苏一 (赞：6)

## Description

给你一个长度为 $a$ 的正方形，在其中裁掉一个长度为 $b$ 的正方形，问剩余面积是否是质数。多组数据

## Input

第一行是数据组数 $t$

下面 $t$ 行，每行两个整数 $a~,b$，代表 $a$ 和 $b$

## Output

对于每组数据，如果是质数输出一行 YES，否则输出 NO

## Hint

$0~\leq~t~\leq~5$

$0~\leq~b~<~a~\leq~10^{11}$

## Solution

考虑一个矩形，被裁掉以后面积 $S~=~a^2~-~b^2$

根据完全平方公式

$$S~=~(a~+~b)~\times~(a~-~b)$$

因为 $a~+~b~>~1$，根据素数的定义，当且仅当 $a~-~b~=~1$ 并且 $a~+~b$ 是一个质数时 $S$ 才是一个质数

于是 $O(\sqrt{a})$ 判断质数即可。总复杂度 $O(t\sqrt{a})$

## Code

（话说你谷什么时候资瓷py的高亮啊qwq）

```python
import math

t = int(input())

def IsPrime(x):
	k = int(math.sqrt(x) + 1)
	for i in range(2, k):
		if ((x % i) == 0):
			return 0
	return 1

for T in range(t):
	a, b = map(int, input().split())
	if ((a - b) != 1):
		print("NO")
	else:
		if (IsPrime(a + b)):
			print("YES")
		else:
			print("NO")

```



---

## 作者：_Harrisonwhl_ (赞：3)

### 本人的第三篇题解
题目大意：有多组数据，每组数据有 $a$,$b$ 两数，问 $a^2-b^2$ 是不是质数。

这道题如果单纯的去算然后判断质数，会爆 long long,需要写一堆高精度，再来个高精度判断质数，极难实现。

于是我们可以换一种方法，用平方差公式:$a^2-b^2=(a+b)\cdot(a-b)$ 将其转换为两数相乘的形式。

然后继续想，质数的定义是因数只有$1$和它本身，所以两数 $a-b$ 和 $a+b$ 必须是$1$和它本身，如果是由其他数乘起来的话，那么结果必定有其他因数。

所以我们只需判断每组数据 $a$ 和 $b$ 是否满足 $a+b$ 是质数且 $a-b$ 是$1$即可。

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool isPr(long long x)//记得开long long啊！
{
    if (x < 2) return 0;
    for (int i = 2;i <= sqrt(x);i++)
        if (x % i == 0) return 0;
    return 1;
}
int t;
long long a,b;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> a >> b;
        if (isPr(a + b) && a - b == 1) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：JoseTony (赞：1)

这道题评分有极大的水分。其实就是一道大水题。

题意已经给得很清楚了，但是如果直接判断的话 $10^{11}\times10^{11}$ 明显会爆`long long`的精度。而我们又不想写高精度，所以需要推一推性质。

本题所求的剩余面积正好是 $a^2-b^2$，这是我们需要用到平方差公式，这个式子正好是 $(a+b)(a-b)$。而题目要求这个数必须是质数，也就是说除去 $1$ 和这个数本身外没有其它因数。因此 $a+b$ 就应该是它本身，一个质数，$a-b$ 则应该是 $1$。那么我们就在循环里进行判断即可。本题数据范围为 $10^{11}$，不要忘记开`long long`。
# 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
ll t,a,b;//开long long
inline int is_prime(ll x){
    if(x<2) return 0;
    for(ll i=2;i*i<=x;++i){
        if(x%i==0) return 0;
    }//质数判断，只需到sqrt(x)即可
    return 1;
}
int main(){
    cin >> t;
    while(t--){
        cin >> a >> b;
        if(is_prime(a+b)&&a-b==1) puts("YES");//判断是否为质数
        else puts("NO");
    }
    return 0;
}
```


---

## 作者：tribool4_in (赞：1)

首先分析题目发现，此题就是给你两个整数 $a$，$b$ 判断 $a^2-b^2$ 是否为质数。看到这个公式，显然可以想到平方差公式：$(a+b)(a-b)=a^2-b^2$，至于证明，只需把 $(a+b)(a-b)$ 乘开即可。

又因为 $a > b > 0$，所以易知 $a+b > a-b \ge 1$。而 $(a+b)(a-b)$ 为质数，当且仅当 $a+b$ 为质数且 $a-b=1$，因为质数的因数只有两个，即 1 和它本身。因此只需判断 是否 $a+b$ 为质数且 $a-b=1$ 即可。

注意开 long long！

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, t;
bool check(int x) {
	if (x <= 2) return 1;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) return 0;
	return 1;
}
signed main() {
	cin >> t;
	while (t--) {
		cin >> a >> b;
		if ((a - b == 1) && check(a + b)) puts("YES");
		else puts("NO");
	}
	return 0;
}

```


---

## 作者：MilkyCoffee (赞：0)

挽回我自信心的好题。

由平方差公式可得，需要判断 $(a-b)(a+b)$ 是否为质数

两个数相乘是否为质数，也就是说二者必须有一个为 $1$ ，另一个可以是 $1$ 也可以是质数。

而由题意可得，$a+b > 1$ ，所以需要满足 $a-b$ 是 $1$ ，$a+b$ 是质数。

---

## 作者：Terraria (赞：0)

## 题目大意

有 $T$ 组数据，每组数据给出 $a,b$，求 $a^2-b^2$ 是否为质数。

## 解法

由于数据范围 $1 \leq b<a \leq  10^{11}$，如果直接求平方会炸掉，因此考虑如何不让它炸掉。

根据恒等式：$a^2-b^2=(a+b)(a-b)$，我们可以知道，如果 $a+b$ 是质数且 $a-b$ 不是质数，则可以确定 $a^2-b^2$ 为质数。

## 证明

1. $(a+b)$ 为质数且 $(a-b)$ 不为 $1$ 时，便可以质因数分解为 $(a+b) \times (a-b)$，非质数。

2. $(a+b)$ 非质数时，设它有一个质因子 $k$，则 $a^2-b^2=k \times [\dfrac{a+b}{k} \times (a-b)]$，也是非质数。

由此得证。

## 注意事项

记得开 $\text{long long}$！

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
bool isprime(int k){
	if(k==1) return false;
	if(k==2) return false;
	for(int i=2;i<=sqrt(k);i++){
		if(k%i==0) return false;
	}
	return true;
}
signed main(){
	cin>>t;
	while(t--){
		int a,b;
		cin>>a>>b;
		if(a-b==1&&isprime(a+b)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$
给出$a,b$，求$a^2-b^2$是否为质数。
# $\text{Answer}$
前置知识：[平方差公式](https://baike.baidu.com/item/%E5%B9%B3%E6%96%B9%E5%B7%AE%E5%85%AC%E5%BC%8F/1947969?fromtitle=%E5%B9%B3%E6%96%B9%E5%B7%AE&fromid=9875496&fr=aladdin)。

首先要知道平方差公式：$a^2-b^2=(a+b)(a-b)$

证明：$(a+b)(a-b)=a(a-b)+b(a-b)=a^2-ab+ab-b^2=a^2-b^2$

若$x$为质数，则$x=1\cdot x$。

$\because a+b>a-b$

$\therefore a-b=1,a+b=x$

于是只用判断$a-b$是否为$1$，$a+b$是否为质数即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b;
inline long long read()
{
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline bool check(long long n)
{
    if(n<2) return false;
    for(register long long i=2;i*i<=n;++i) if(n%i==0) return false;
    return true;
}
int main()
{
    t=read();
    while(t--)
    {
        a=read();b=read();
        if(a-b==1&&check(a+b)) cout<<"YES\n";
            else cout<<"NO\n";
    }
    return 0;
}
```


---

## 作者：江户川·乱步 (赞：0)

## 题目大意

   求$ a^2-b^2$是否位质数，共$ T $组数据。 

## 题目分析
   
   根据平方差公式，可得$ a^2-b^2=(a+b)(a-b) $
   
   因为$ a>b>0$,容易推出$ a+b>a-b≥1$
   
   由于质数只有1和它本身这两个因数，所以$a-b$一定为1
   
   所以这道题只需要判断$a+b$是否为质数且$a-b$是否等于1
   
## Code

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll t,a,b;
bool check(ll x) {
	if (x<=2)
	    return 1;
	for (ll i = 2;i*i<=x;i++)
		if (x%i==0)
		    return 0;
	return 1;
}
signed main() {
	cin>>t;
	while(t--){
		cin>>a>>b;
		if (a-b==1&&check(a+b))
		    puts("YES");
		else puts("NO");
	}
	return 0;
}
```
## PS：要开long long！！！

---

