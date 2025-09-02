# 最大数 max(x,y,z)

## 题目描述

已知：

$m=\dfrac{\max(a,b,c)}{\max(a+b,b,c) \times \max(a,b,b+c)}$

输入三个整数 $a$，$b$，$c$，求 $m$。

把求三个数的最大数 $\max(x,y,z)$ 分别定义成函数和过程来做。

## 说明/提示

### 数据规模与约定

对于全部的测试点，保证 $|a|,|b|,|c| \leq 50$。换句话说，$a,b,c$ 都在 $-50$ 到 $50$ 之间。

测试数据保证，分式的分母不为 $0$。

## 样例 #1

### 输入

```
1 2 3```

### 输出

```
0.200```

# 题解

## 作者：happybob (赞：30)

众所周知，在 `algorithm` 库中有一个 `max` 函数，但你不知道的是 `ISO c++11` 中 `max` 可以接受多个参数，前提是要用中括号括起来，如：

```cpp
int a = max({9, 9, 12, 97301, 937});
```

还有，`printf` 支持输出保留小数点位数的数，但是很多人不知道 `cout` 也可以，但是需要包含头文件 `iomanip`，代码：

```cpp
cout << fixed << setprecision(位数) << 值;
```

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    cout << fixed << setprecision(3) << max({a, b, c}) / (max({a + b, b, c}) * max({a, b, b + c})) << endl;
    return 0;
}
```


---

## 作者：newbie666 (赞：12)

## 前置知识：$\max$ 函数应用

这道题是一道函数入门题，我们可以自定义一个函数：求三个数的最大值，可以使用 $\texttt{C++}$ 的 $\max$ 函数，变为 $\max(a, b, c) = \max(a, \max(b, c))$，然后根据题意具体计算即可。

解析都在代码里了，不懂详见代码。
## $\texttt{Code}:$
```cpp
#include<bits/stdc++.h>
using namespace std;
double MAX(double a,double b,double c){ //所有值都要是double，因为题目说要保留3位小数。 
	return max(a,max(b,c)); //核心代码，三数求最大值。 
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	double a,b,c; cin>>a>>b>>c; 
	double m=MAX(a,b,c)/MAX(a+b,b,c)/MAX(a,b,b+c); //按照题意计算答案。 
	printf("%.3lf",m); //保留三位小数。 
	return 0;
}
```


---

## 作者：StayAlone (赞：8)

[B2129](https://www.luogu.com.cn/problem/B2129)  
### 题意
给定 $a,b,c$，求 $m = \dfrac{max(a, b, c)}{max(a+b,b,c) \times max(a,b,b+c)}$。

### 思路

C++ 中自带的函数 `max(a, b)` 将返回 $a$ 与 $b$ 之间的较大值。

想要求到三个数的最大值，可以使用 `max(a, max(b, c))`。

接下来按照题目的式子计算即可。 

$\dfrac{a}{b\times c} = a / b / c$。

[AC code记录 1](https://www.luogu.com.cn/record/52355849)
```cpp
#include <bits/stdc++.h>
using namespace std;
double a, b, c;

int main()
{
    scanf("%lf%lf%lf", &a, &b, &c);
    return printf("%.3lf", max(a, max(b, c)) / max(a + b, max(b, c)) / max(a, max(b, b + c))), 0;
}
```

但是很明显的看到，这样的代码较为臃肿。所以，我们可以自己定义一个 `max1` 函数，`max1(a, b, c)` 将返回三个数中的最大值。  

```cpp
double max1(double a, double b, double c)
{
    return max(a, max(b, c));
}
```  

[AC code记录 2](https://www.luogu.com.cn/record/52355699)
```cpp
#include <bits/stdc++.h>
using namespace std;
double a, b, c;
double max1(double a, double b, double c)
{
    return max(a, max(b, c));
}

int main()
{
    scanf("%lf%lf%lf", &a, &b, &c);
    return printf("%.3lf", max1(a, b, c) / max1(a + b, b, c) / max1(a, b, b + c)), 0;
}
```

代码显得简洁易懂许多。  

`printf("%.xlf")`   
其中$x$ 为非负整数，将会保留 $x$ 为小数。

---

## 作者：int127 (赞：5)

`max()` 是 C++ 中求解最大值的函数。

使用方法:

以比较三个数 $a,b,c$ 为例子。

① `_MAX=max({a,b,c});//花括号括起来`（这一种要用 C++11）

② `_MAX=max(a,max(b,c));//max 嵌套`

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int INP_A, INP_B, INP_C;
int MAX_Q1, MAX_Q2, MAX_Q3;
double ANS_B2129;
signed main(){
	cin>>INP_A>>INP_B>>INP_C;
   	//采取第2种方法求MAX
	MAX_Q1=max(INP_A,max(INP_B,INP_C));
	MAX_Q2=max(INP_A+INP_B,max(INP_B,INP_C));
	MAX_Q3=max(INP_A,max(INP_B,INP_B+INP_C));
	ANS_B2129=1.0*MAX_Q1/(MAX_Q2*MAX_Q3);
	printf("%.3lf",ANS_B2129);
	return 0;
}
```

码风有点乱，请见谅！

---

## 作者：__Cartesian__Tree__ (赞：4)

主要是编写三个数最大值的函数。

在编写函数时，我们可以用到 STL 中的 $\max$ 函数，也就是：

$\operatorname{maxx}(a, b, c)=\max(\max(a, b), c)$

```cpp
int maxx(int a, int b, int c){
    return max(max(a, b), c);
}
```

如果你通过了这道题，那么 [B2049](https://www.luogu.com.cn/problem/B2049) 也应该轻松通过。

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, c;
double m;
int maxx(int a, int b, int c){//求三个数的最大值
    return max(max(a, b), c);
}
int main(){
    scanf("%d%d%d", &a, &b, &c);
    m = maxx(a, b, c) * 1.0 / (maxx(a + b, b, c) * maxx(a, b, b + c));
    //要乘 1.0，否则会自动取整
    printf("%.3lf", m);//注意保留三位小数
    return 0;
}
```


---

