# Hexagons!

## 题目描述

After a probationary period in the game development company of IT City Petya was included in a group of the programmers that develops a new turn-based strategy game resembling the well known "Heroes of Might & Magic". A part of the game is turn-based fights of big squadrons of enemies on infinite fields where every cell is in form of a hexagon.

Some of magic effects are able to affect several field cells at once, cells that are situated not farther than $ n $ cells away from the cell in which the effect was applied. The distance between cells is the minimum number of cell border crosses on a path from one cell to another.

It is easy to see that the number of cells affected by a magic effect grows rapidly when $ n $ increases, so it can adversely affect the game performance. That's why Petya decided to write a program that can, given $ n $ , determine the number of cells that should be repainted after effect application, so that game designers can balance scale of the effects and the game performance. Help him to do it. Find the number of hexagons situated not farther than $ n $ cells away from a given cell.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
19```

# 题解

## 作者：超级玛丽王子 (赞：6)

[在窝的博客食用更佳](https://www.luogu.com.cn/blog/LXLDuliu-IAKIOI/solution-cf630d)

本题可以在 $O(1)$ 的常数时间内解决。

首先观察题图：

![图片貌似挂了……](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

可以发现，距离为 $0$ 的六边形有 $1$ 个，距离为 $1$ 的六边形有 $6$ 个，距离为 $2$ 的六边形有 $12$ 个…… 易得距离为 $n\ \ (n\ne0)$ 的六边形有 $6n$ 个。

其实这一点很容易理解。由相同距离的小六边形组成的大六边形，每条边上不重不漏地数有 $n$ 个小六边形。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0wrhau84.png)

~~图有点粗制滥造 凑活看吧~~

因此我们就得出，距离中心六边形距离不超过 $n$ 的六边形为第 $n$ 个大六边形及以内的六边形。根据等差数列的通项公式，我们有
$$ans=\dfrac{(6+6n)\times n}{2}+1$$
注意最后要加1，因为还有中心点；化简得到
$$ans=3n^2+3n+1$$

代公式计算即可。

~~看完 Aw顿顿 巨佬的题解才知道百度百科上有这个结论~~

## 求赞：看我写的这么认真，不点个赞再走嘛？

---

## 作者：szkzyc (赞：1)

这道题是让你求下图图形的六边形个数，再给定你向外扩展的边数
n
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

这题一上手就会有一圈一圈的相加的念头，所以我们可以来找找规律：

| 第n圈 | 1 |2  | 3 | 4... |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 第n圈六边形个数 | 6 | 12 | 18 | 24... |

很容易发现，第n行便会有$6n$个六边形


所以很容易可以得出以下代码：

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define reg register
using namespace std;
ull ans = 1; //注意中心也有一个六边形 
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
    	ans += i * 6; //第i圈就会有6i个正六边形 
	}
	cout << ans << endl;
	return 0;
}

```

但这样纯暴力肯定是会超时的

所以我们开始研究此题$O(1)$的算法

由于每一圈之间相差的数都是固定的6，所以我们可以将它归为一个等差数列求和的问题

这个数列的数分别为：$6,12,18,24,30,36...$

于是，我们很快可以推出

# $ans = \sum_{a=1}^{n}6a$
##### ps:答案还要加一哦

在利用等差数列求和公式可以得出

# $ans = 3n(n+1)+1$

最后，AC代码就诞生了！

```cpp
#include <bit/stdc++.h>`
#defne ull unsigned long long
#defne ll long long
#defne reg register
using namespace std；`
`
int mian(){
   ull n； //注意答案可能很大哦
	cin >> n；
	cout << 3 * n * (n + 1) + 1；
	return 0；
}
//加了亿点点防抄袭，后果自负哦
```


---

## 作者：Aw顿顿 (赞：1)

[博客有更多题解和资料，欢迎前来提出意见](https://www.luogu.com.cn/blog/AlanWalkerWilson/)

这道题我们需要证明，而且过程尽可能详细，便于理解。

我们将要讨论两种方法：

## Solution 1

首先，我们看到题目给出了一张图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

我们会发现，枚举可以找到规律：

$$\operatorname{No.0}:1$$

$$\operatorname{No.1}:6$$

$$\operatorname{No.2}:12$$

$$\cdots$$

这时候我们会发现一个奇妙的现象：

除了第 $0$ 层以外，第 $n$ 层的个数似乎是 $6n$。

于是我们多算几项，都符合这个猜想。

为了验证这个猜想是正确的，你可以到 `oeis.org` 网站上查询，其编号为 `A008458`，链接为 [Search](http://oeis.org/search?q=1%2C6%2C12%2C18&sort=&language=english&go=Search)。


此时我们可以推出，距离不超过 $n$ ，就是前 $n$ 层的总和。

那么，前 $n$ 层我们可以利用等差数列的性质：

$$\dfrac{\text{首项+末项}\times\text{项数}}{2}$$


带入到当中就是：

$$\dfrac{(6+6n)n}{2}+1$$

前 $n$ 层的和要加上 $1$，也就是第 $0$ 层

接着我们化简为：

$$\dfrac{6n(n+1)}{2}+1$$

化简就是：

$$3n(n+1)+1$$

如果你习惯将括号展开，它还可以表示为：


$$3n^2+3n+1$$

带入代码为：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
int main(){
    cin>>x;
    cout<<3*x*(x+1)+1<<endl;
    return 0;
}
```

接下来，我们要讲一个新的方法：六边形数

## Solution 2

其实跟上一种方法异曲同工

给出的图片

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

看着蜂巢一样，就是六边形数了，我们可以去查一下百度。

然后我们找到了[百度百科 - 中心六边形数](https://baike.baidu.com/item/%E4%B8%AD%E5%BF%83%E5%85%AD%E8%BE%B9%E5%BD%A2%E6%95%B0/9459496)。

这时候一定要注意，百度百科有两个六边形数，有一个和我们的题目无关，而打开正确的链接，我们可以找到一个对我们解题有用的东西：

第 $n$ 个中心六边形数为 $1 + 3n(n- 1)$ 。

这个和我们之前证明的内容是几乎一样的。


那么我们就可以根据这个式子列出代码，计算即可。

谢谢大家认真阅读，希望对你们学习能够有帮助。

---

## 作者：Vader10 (赞：1)

好像没有PYTHON3题解，我发一个。
公式有人讲过了，我就不讲了。
上两行代码：
```python
n=int(input())
print(3*n**2+3*n+1)
```
注意：“**”是乘方的意思。

---

## 作者：PC_DOS (赞：1)

通过观察题目所给的图像并进行推演，可以发现当距离iDist大于等于1时，每一个特定距离上的砖块构成一个6为首项，6为公差的等差数列{A(iDist)}，将距离等于0处的单个砖块算入，结合等差数列求和公式Sn=(A1+An)*n/2，可以推出该数列的求和公式:

```
S(iDist) = (iDist+1)*(6*iDist)/2+1;
//简化
S(iDist) = (iDist+1)*(3*iDist)+1;
```

故得到代码:

```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long iDist; //距离，由于不使用中间变量，将其定义为long long (通常为int64)
	cin >> iDist; //输入距离
	cout << (iDist + 1)*(3 * iDist) + 1; //直接输出答案
	return 0; //结束
}
```

---

## 作者：agicy (赞：1)

# 题意

在六边形网格当中,求离中间六边形距离不超过$n$的六边形的个数。

翻译来自@Fuko_Ibuki 。

## 题面源代码

```
在六边形网格当中,求离中间六边形距离不超过$n$的六边形的个数。
```

# 思路

首先，我们先手动计算几组样例数据。

```
n=1
ans=7

n=2
ans=19

n=3
ans=37

n=4
ans=61

n=5
ans=91
```

观察以上数据，我们提出猜想：

$ans=3n^2+3n+1$

下面我们采用**数学归纳法**证明。

根据经验可得：

$ans=1+6×\sum_{i=1}^{n}i$

1. 当$n=1$时，$3n^2+3n+1=1+6×\sum_{i=1}^{n}i$；

2. 假设当$n=k$时结论成立，试证明当$n=k+1$时结论成立。

$ans_{k+1}$

$=1+6×\sum_{i=1}^{k+1}i$

$=1+6×\frac{(k+1)(k+2)}{2}$

$=1+3(k+1)(k+2)$

$=3k^2+9k+7$

$=3(k+1)^2+3(k+1)+1$

所以猜想正确。

# 代码

代码如下。

```cpp
#include<stdio.h>

long long n;

int main(void){
	scanf("%lld",&n);
	printf("%lld\n",3*n*n+3*n+1);
	return 0;
}
```

## [我的评测记录](https://www.luogu.org/recordnew/show/9697956)

---

## 作者：YosemiteHe (赞：0)

题目给了这样一幅图片：

![JXT AK IOI](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

一个蜂窝状的图形，第 $n$ 层（六边形中的数字为层数）的六边形有 $6 \times n$ 个，第 $0$ 层只有 $1$ 个。

所以等差数列求和就行了。

所以公式是：

$$(6 + 6 \times n)\times n ÷ 2+ 1$$

最后那个 $1$ 是第 $0$ 层的。

注意数据范围，要开 `long long`。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
int main(void) {
    cin >> n;
    cout << (6 + 6 * n) * n / 2 + 1 << endl;
    return 0;
}
```

Tks.

---

## 作者：RioBlu (赞：0)

我有不同的思路：
___
我发现距离为1的有6个

我发现距离为2的有12个

我发现距离为3的有18个

那不是很简单，等差数列求和，只不过最后加上个1（距离为0）罢了
```
#include<bits/stdc++.h>
using namespace std;
long long a;
int main()
{
	cin>>a;
	cout<<(6+6*a)*a/2+1<<endl;//等差数列求和公式，首项（6）+末项（6*a）的和乘上项数a除二即可
}
```

---

## 作者：米奇奇米 (赞：0)

```cpp
我们可以发现
当距离为1时，有7个点
距离为2时，样例中说有19个点
当距离为3时，数一数有37个点
当吧相邻两个距离相减时，易得差值为6的倍数，分别为
6,12,18,24...
以此类推，可得递推式f[i]=f[i-1]+6*i;
具体实现看代码

#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll f[50000005],n;//数组一定一定要开
int main()
{
	cin>>n;
	f[1]=7;
	f[2]=19;
	f[3]=37;
	for(int i=4;i<=n;i++)
	f[i]=f[i-1]+6*i;
	cout<<f[n];
	return 0;
}
	 

```

---

## 作者：feecle6418 (赞：0)

可以看出这是一种叫做“中心六边形数”的东西。

$a_i=a_{i-1}+6 \times i,a_1=7$

可以推一推，也可以找规律。最后得出$a_n=3n^2+3n+1$。套公式就好了，注意long long。
```
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long n;
    cin>>n;
    cout<<1+3*n*(n+1);
}
```

---

## 作者：GusyNight (赞：0)

**这是本蒟蒻的第5篇题解~~~**

首先读题目
```
在下图六边形网格当中,求离中间六边形距离不超过n的六边形的个数
```
经过检验（手算）
```
#1
in 1
out 7

#2
in 3
out 37

#3
in 5
out 91

#4
in 385
out 445831
```

**就得到公式**
```cpp
ans=3*n*n+3*n+1;
```
**所以代码就是：**
```cpp
#include<bits/stdc++.h>
#define TP int
#define Max 100009
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n=read();
int main(){
	cout<<3*n*n+3*n+1;
	return 0;
}
```

---

