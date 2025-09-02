# パスカルの三角形

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-final/tasks/code_festival_final_d

高橋君は、パスカルの三角形が大好きです。

パスカルの三角形とは、一つ上の数字の、右上の数と左上の数を足した数を書き連ねていくことにより、表現することが出来る三角形です。

パスカルの三角形の$ y $ 段目は $ y $ 個の数で構成されており、 $ y $ 段目 $ x $ 番目の数を $ f(y,x) $ とすると、

- $ x\ =\ 1 $、または $ x\ =\ y $ の時、$ f(y,x)\ =\ 1 $
- それ以外の時、$ f(y,x)\ =\ f(y-1,x)\ +\ f(y-1,x-1) $

と定義されます。

高橋君は、ある整数 $ A $ が、パスカルの三角形に含まれるかどうかを調べたいと思いました。

もし、パスカルの三角形に $ A $ が現れるのであれば、その段数、及び何番目かを出力し、出現しないのであれば、`-1 -1`と出力しなさい。

## 说明/提示

### Sample Explanation 1

$ 6 $ 段目、 $ 3 $ 番目の数字は $ 10 $ です。他に $ 6 $ 段目 $ 4 $ 番目なども条件を満たしますが、どの出力をしても問題ありません。

### Sample Explanation 2

ある程度大きな数字が入力されることもあります。

## 样例 #1

### 输入

```
10```

### 输出

```
6 3```

## 样例 #2

### 输入

```
3921225```

### 输出

```
101 5```

# 题解

## 作者：RioBlu (赞：5)

发现规律其实挺难的：
___
最开始，我想了一下暴力一下就能AC
```
#include<bits/stdc++.h>
using namespace std;
long long jc(int n,int m)
//组合数学：第n行的m个数可表示为 C(n-1，m-1)，即为从n-1个不同元素中取m-1个元素的组合数。
{
    long long ans=1,a=min(n-m,m),b=max(n-m,m);
    for(int s=b+1;s<=n;s++)ans*=s;
    for(int s=2;s<=a;s++)ans/=s;
    return ans;
}
long long a;
int main()
{
    cin>>a;
    for(int s=0;s<2000000000;s++)//因为答案不能超过2*10^9
    {
        for(int v=0;v<=s;v++)
        {
            if(jc(s,v)==a)
            {
                cout<<s+1<<" "<<v+1<<endl;
                return 0;
            }
        }
    }
}
```
## ~~TLE预定~~
我想了一想：杨辉三角有一个规律**（第n+1行，第2个必定是：n）**

1

1 **1**

1 **2** 1

1 **3** 3 1

1 **4** 6 4 1

1 **5** 10 10 5 1

1 **6** 15 20 15 6 1

1 **7** 21 35 35 21 7 1

看看加粗的数，没有任何问题！**（第n+1行，第2个必定是：n）**

看看要输入的数：小于$10^9$ 输出：小于$2*10^9$ 可以过！ 
```
#include<bits/stdc++.h>
using namespace std;
long long a;
int main()
{
    cin>>a;
    cout<<a+1<<" "<<2<<endl;//按上面的结论输出
    return 0;
}
```

---

## 作者：死神审判 (赞：2)

### 介绍：
帕斯卡三角形也称杨辉三角，是二项式系数在三角形中的一种几何排列，中国南宋数学家杨辉1261年所著的《详解九章算法》一书中出现。在欧洲，帕斯卡在1654年发现这一规律，所以这个表又叫做帕斯卡三角形。帕斯卡的发现比杨辉要迟393年，比贾宪迟600年。
![](https://cdn.luogu.com.cn/upload/image_hosting/uev8atud.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


------------
### 思路&解析：
我们先来观察一下这张图，发现每一个数都是由Ta正上方的两个数相加而构成的，我们要在帕斯卡三角形中找一个数，应该用怎样的方法呢，请看下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/j9x1resw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

比方说我们要找的数是 $x$ ，在 第$x+1$行的第$2$个数就是$x$，所以输出$x+1$和$2$j就可以了。
### 代码（维护一下```Python```党）：
```python
x=int(input())
print(x+1,2)
```


---

## 作者：一只书虫仔 (赞：1)

看完题面琢磨了一下，帕斯卡三角形，看不懂，然后往下看帕斯卡三角形的定义，每一个数都等于它上方的数字加上左上方的数字加右上方的数字，这不就是**杨辉三角**吗？比如说下面这张杨辉三角

![](https://cdn.luogu.com.cn/upload/image_hosting/8djoat71.png)

我们发现第一斜列全部是数字 $1$ ，第二斜列是全体非零自然数集 $\mathbb{N}^*$，到这里我们就发现无论是什么自然数都可以在这里找到。不看上面图片左边的行的计算方法，我们发现，数字 $2$ 在第三行，数字 $3$ 在第四行，数字 $n$ 就在第 $n+1$ 行，所以输出 $n+1,2$ 就可以 

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	long long n;
	scanf("%d", &n);
	printf("%d %d", n + 1, 2);
	return 0;
}

```

### 拓展

第三斜列是等差数列，第四斜列是二阶等差数列，以此类推，第 $n$ 斜列 $(n\geqslant3)$ 是 $n-2$ 阶等差数列。杨辉三角形的秘密还有很多，因此会被经常用到数学/信息领域，一定要好好了解哦~

求赞 \qwq

---

## 作者：sh7adow_ (赞：1)

帕斯卡三角形，就用``Pascal``解决!

让我们来看图：

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

你发现规律了吗？

第$n+1$行，第$2$个必定是：$n$。

我们以这张图来讲：

![](https://img-blog.csdn.net/20171130143100892?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveWluZ211bGl1Y2h1YW4=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

你再慢慢钻研吧！

## 继续，回归正题！

定义一个数 $n$ :
```pascal
var n:longint;
```
开始程序！
```pascal
begin
```
输入：
```pascal
readln(n);
```
根据分析，输入一个数，得到以下式子：

 $\qquad \qquad \qquad \qquad \qquad \qquad $  **输出:**  $n+1 \qquad 2$ 
```pascal
write(n+1,' ',2);
end.//真的完美的结束程序了！
```

## 以下是完整代码：
```pascal
var n:longint;
begin
	readln(n);
	write(n+1,' ',2);
end.
```

好了， $\color{red}\colorbox{Yellow}{求过和赞}$ 

---

## 作者：monstersqwq (赞：0)

前置芝士：[帕斯卡三角形](https://baike.sogou.com/v313456.htm?fromTitle=%E5%B8%95%E6%96%AF%E5%8D%A1%E4%B8%89%E8%A7%92%E5%BD%A2)。

首先我们考虑用暴力做，但是无论是按照规则递推（数组不够）或是使用组合数的方法搞都没法解决，于是我们考虑其他的方法。

观察一下帕斯卡三角形（杨辉三角）：

$$1$$

$$1\qquad1$$

$$1\qquad2\qquad1$$

$$1\qquad3\qquad3\qquad1$$

$$1\qquad4\qquad6\qquad4\qquad1$$

$$1\qquad5\qquad10\qquad10\qquad5\qquad1$$

$$1\qquad6\qquad15\qquad20\qquad15\qquad6\qquad1$$

相信大家都看出来了，帕斯卡三角形的第二左斜行和第二右斜行都是一个公差为1的等差数列，从第二行开始。

所以，对于每一个 $A$，第 $A+1$ 行的第二个和倒数第二个（即第 $2,A$ 个）一定是 $A$，直接输出它们之中任意一个即可。

tips：AT题中不换行，听取WA声一片。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main()
{
	int n;
	cin>>n;
	cout<<n+1<<" "<<n<<endl;
    return 0;
}
```


---

