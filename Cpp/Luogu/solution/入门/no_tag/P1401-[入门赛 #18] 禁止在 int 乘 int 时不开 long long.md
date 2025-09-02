# [入门赛 #18] 禁止在 int 乘 int 时不开 long long

## 题目描述

在比赛中，根据数据范围，分析清楚变量的取值范围，是非常重要的。int 类型变量与 int 类型变量相乘，往往可能超出 int 类型可以表示的取值范围。

现在，给出两个 int 类型变量 $x,y$ 及其取值范围，请问 $x\times y$ 的值是否可能超过 int 类型可以表示的范围？

> 提示：int 类型可以表示的范围为 $[-2147483648, 2147483647]$，即 $[-2^{31},2^{31}-1]$。也就是，int 类型可以表示的最小值为 $-2147483648$，最大值为 $2147483647$。

## 说明/提示

### 数据规模与约定

- 对于 $50\%$ 的测试数据，$0 \le x_l \le x_u < 2^{31}$，$0 \le y_l \le y_u < 2^{31}$。
- 对于 $100\%$ 的测试数据，$-2^{31} \le x_l \le x_u < 2^{31}$，$-2^{31} \le y_l \le y_u < 2^{31}$。

## 样例 #1

### 输入

```
1 5
1 5```

### 输出

```
int```

## 样例 #2

### 输入

```
-2147483647 2147483647
-2147483647 2147483647```

### 输出

```
long long int```

# 题解

## 作者：Oracynx (赞：60)

## P1401 [入门赛 #18] 禁止在 int 乘 int 时不开 long long 题解

### 思路分析

~~题目说的不是我吗？~~

题目要求在 `int` 乘 `int` 溢出时输出 $\texttt{long long int}$，否则输出 $\texttt{int}$，这里有个小技巧，我们可以利用 C++ 的数据自然溢出解题。

首先我们记 `int ix, iy, ia, ib;` 为对应数据在 `int` 类型下的储存，`long long x, y, a, b;` 为在 `long long` 类型下的储存。比较连个相乘的结果即可。

一种常见的错误：

```cpp
#include <cstdio>
int ix, iy;
int ia, ib;
long long x, y;
long long a, b;
int main()
{
    scanf("%lld%lld", &x, &y);
    scanf("%lld%lld", &a, &b);
    ix = x;
    iy = y;
    ia = a;
    ib = b;
    if (x * a != ix * ia || y * b != iy * ib)
    {
        printf("long long int\n");
    }
    else
    {
        printf("int\n");
    }
    return 0;
}
```

显而易见的 Hack 数据：

```plain
-1000000 1
-1 1000000
```

因为我们只相乘了左右端点，但如果其交叉相乘溢出则无法判断。

所以我们需要判断 $4$ 种情况。

### 代码实现

```cpp
#include <cstdio>
int ix, iy;
int ia, ib;
long long x, y;
long long a, b;
int main()
{
    scanf("%lld%lld", &x, &y);
    scanf("%lld%lld", &a, &b);
    ix = x;
    iy = y;
    ia = a;
    ib = b;
    if (x * a != ix * ia || x * b != ix * ib || y * a != iy * ia || y * b != iy * ib)
    {
        printf("long long int\n");
    }
    else
    {
        printf("int\n");
    }
    return 0;
}
```

---

## 作者：cff_0102 (赞：18)

题意简述：已知 $x$ 和 $y$ 的最大值和最小值，求 $x\times y$ 会不会爆 `int`。

要爆 `int`，则要乘积结果绝对值尽可能大，那么 $x,y$ 当然要尽量取最值。

只需判断 $x_1\times y_1,x_1\times y_2,x_2\times y_1,x_2\times y_2$ 这四个数的值在不在 `int` 范围内即可。

```python
def check(x,y):
    return (x*y>=-2147483648 and x*y<=2147483647)

a=input().split()
x1=int(a[0])
x2=int(a[1])
b=input().split()
y1=int(b[0])
y2=int(b[1])

if((not check(x1,y1)) or (not check(x1,y2)) or (not check(x2,y1)) or (not check(x2,y2))):
    print("long long ",end="")
print("int")
```

---

## 作者：Erica_N_Contina (赞：14)

一种很简单无脑的方法。
既然是入门题，那么直接暴力枚举每一种组合。

判断的时候使用取巧的方法：记录 $res=a\times b$，分别用 `int` 和 `long long` 存储 $res$，判断是否相等即可。

```c++
#include <bits/stdc++.h>
#define db double
#define rtn return
using namespace std;

long long a[6],b,c,d,n,m,nn,mm;

signed main() {
	cin>>a[1]>>a[2]>>a[3]>>a[4];
	
	for(int i=1;i<=2;i++){
		for(int j=3;j<=4;j++){
			int res=a[i]*a[j];
			long long res2=a[i]*a[j];
			if(res!=res2){
				cout<<"long long int";
				return 0;
			}
		}
	}

    cout<<"int";

    return 0;
}

```

---

## 作者：guozhe6241 (赞：10)

# 题目传送门

[P1401](https://www.luogu.com.cn/problem/P1401)

# 思路

只需要把每两个数全部判断一遍看看是否越界，然后就可以输出了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
signed main(){
	cin>>a>>b>>c>>d;
	if(a*c<-2147483648||a*c>2147483647||b*d<-2147483648||b*d>2147483647||a*d<-2147483648||a*d>2147483647||b*c<-2147483648||b*c>2147483647){
		cout<<"long long int";
	}else{
		cout<<"int";
	}
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/139257304)

---

## 作者：zhang_Jimmy (赞：7)

一道简单题，但是细节很多。

# 思路

首先，`int` 类型的范围是 $[-2^{31}, 2^{31} - 1]$，`long long` 类型的范围是 $[-2^{64}, 2^{64} - 1]$。可以拿计算器算一下，两个 `int` 类型相乘有可能会爆 `int`，但绝对不会爆 `long long`。

同时，我们还需要注意：

由于本题 $xl,xu,yl,yu$ 有可能为负数，所以要依次把它们的四种极端情况算出来（即 $xl \cdot yl,xl \cdot yu,xu \cdot yl, xu \cdot yu$），然后判断它们的值有没有爆 `int`，注意上下界都要判断，不要想当然。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll xl, xu, yl, yu;

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> xl >> xu >> yl >> yu;
	ll ans1 = xl * yl, ans2 = xl * yu, ans3 = xu * yl, ans4 = xu * yu;
	if(ans1 > INT_MAX || ans1 < INT_MIN || ans2 > INT_MAX || ans2 < INT_MIN
	  ||ans3 > INT_MAX || ans3 < INT_MIN || ans4 > INT_MAX || ans4 < INT_MIN)
		cout << "long long int";
	else
		cout << "int";
	return 0;
}

```


---

## 作者：zimujum (赞：6)

## 思路
题已经给出了整形变量的范围了，正常跟随题意就行。~~但我写了半天发现错了，然后我一看是先输入 $x$ 的最大最小再输入 $y$ 的最大最小。~~

## 代码
```
#include <bits/stdc++.h>
#define itn int
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
ll ima=2147483647;
ll x,y,x2,y2;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> x >> y >> x2 >> y2;//输入。
	if(x*x2>ima||y*y2>ima||x*y2<-ima-1||y*x2<-ima-1) cout << "long long int";
    else cout << "int";//进行判断。
//	fclose(stdin);
//	fclose(stdout);
	AC;
}


```

没了。

---

