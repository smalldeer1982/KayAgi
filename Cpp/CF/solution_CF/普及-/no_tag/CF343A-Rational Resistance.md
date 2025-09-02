# Rational Resistance

## 题目描述

Mad scientist Mike is building a time machine in his spare time. To finish the work, he needs a resistor with a certain resistance value.

However, all Mike has is lots of identical resistors with unit resistance $ R_{0}=1 $ . Elements with other resistance can be constructed from these resistors. In this problem, we will consider the following as elements:

1. one resistor;
2. an element and one resistor plugged in sequence;
3. an element and one resistor plugged in parallel.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/f117fcf32ddafc80e319e28fce885c21483edc5b.png)With the consecutive connection the resistance of the new element equals $ R=R_{e}+R_{0} $ . With the parallel connection the resistance of the new element equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/a708eb8090c66cbbd34afced0c36506bcb612681.png). In this case $ R_{e} $ equals the resistance of the element being connected.

Mike needs to assemble an element with a resistance equal to the fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/eecd60ed91fbeebe74e2406ea1a11d26df905945.png). Determine the smallest possible number of resistors he needs to make such an element.

## 说明/提示

In the first sample, one resistor is enough.

In the second sample one can connect the resistors in parallel, take the resulting element and connect it to a third resistor consecutively. Then, we get an element with resistance ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/234023ef6c61445a95e9903d46cd7846f3823141.png). We cannot make this element using two resistors.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
199 200
```

### 输出

```
200
```

# 题解

## 作者：Alex_Wei (赞：14)

一道很好的锻炼思维的题目，很有意思

### 题目翻译

一个电阻器 $R_0$ 的电阻是 $1$（即 $R_0=\frac{1}{1}$）

一个电阻元件（电阻为 $R_e$ ，可以是电阻器）和另外一个电阻器 （电阻为 $R_0$）

可以有如下的两种合成方式，合成一个电阻元件

- 排成一行，组合后的电阻为 $R=R_0+R_e$

- 排成一列，组合后的电阻为 $R=\large\frac{1}{\frac{1}{R_0}+\frac{1}{R_e}}$



例如，两个电阻器 用第一种方式合成，电阻为 $R=R_0+R_0=1+1=2$

再用**合成后的电阻元件**与**另一个电阻器** 用第二种方式合成，电阻为

$$R=\frac{1}{\frac{1}{R_0}+\frac{1}{R_e}}=\frac{1}{\frac{1}{1}+\frac{1}{2}}=\frac{1}{\frac{3}{2}}=\frac{2}{3}$$

给出 $a,b(1≤a,b≤10^{18})$，求**最少**用多少个**电阻器**能合成一个电阻为$\large\frac{a}{b}$ 的电阻元件

### 思路

乍一看，是不是很难？我们继续分析

设当前的电阻 $R$ 等于 $\large\frac{c}{d}$

用第一种方式合成的结果：

$$\frac{c}{d}+1=\frac{c+d}{d}$$

用第二种方式合成的结果

$$\frac{1}{\frac{1}{1}+\frac{1}{\frac{c}{d}}}=\frac{1}{\frac{1}{1}+\frac{d}{c}}=\frac{1}{\frac{c+d}{c}}=\frac{c}{c+d}$$

~~是不是很神奇？~~

这样一来，我们就可以用给出的 $a,b$

如果 $a$ 大，就变成 $a-b$，如果 $b$ 大，就变成 $b-a$

**不断用大的数减去小的数，直到有一个数为 $0$**（每减一次需要的电阻器个数都要 $+1$）

等等，这个算法是不是有点眼熟？好像在哪里见过？

这不就是**欧几里得的辗转相减法**嘛！只是最后停止的条件不同

对了，这道题目的数据范围很大，记得开 $long\ long$

还要把“相减”，变成“相除”，暴力相减一定会 $TLE$！

### 代码

```cpp
#include<bits/stdc++.h>
long long a,b,c,ans; 
int main()
{
	std::cin>>a>>b;
	while(b!=0)ans+=a/b,c=a%b,a=b,b=c;
	std::cout<<ans;
}
```

$CF$ 的 $A$ 题能难到哪去呢？

码字不易，您不点个赞再走嘛 qwq

如果发现题解有错误请私信我，我会及时改正！

---

## 作者：封禁用户 (赞：4)

题目传送>>[CF343A](https://www.luogu.com.cn/problem/CF343A)  
### 题意简述：  
- 许多 $1Ω$ 的电阻欲通过串联、并联使得总阻值为 $\frac{a}{b}Ω$，求最少需要的数量。  
- $1\le a,b\le 10^{18}$。    

### 题目分析:  
假设目前已得到阻值为 $\frac{c}{d}Ω$，  
1. 再串联一个 $1Ω$ 的电阻，即 $1+\frac{c}{d}=\frac{c+d}{d}Ω$；  
2. 再并联一个 $1Ω$ 的电阻，即 $\frac{1}{\frac{1}{1}+\frac{1}{\frac{c}{d}}}=\frac{c}{c+d}Ω$；  
  
观察发现结果很相似，反推:  
目前阻值为 $\frac{a}{b}Ω$，如果 $a>b$，则 $\frac{a}{b}=1+\frac{a-b}{b}$（串联），如果 $b>a$，则 $\frac{a}{b}= \frac{1}{\frac{1}{1}+\frac{1}{\frac{a}{b-a}}}$（并联）。不断重复，最终会得到 $\frac{1}{1}Ω$，再重复一次便为 $0Ω$。  
即反过来，从 $0Ω$ 开始我们可通过串联、并联得到 $\frac{a}{b}Ω$，所需电阻个数就为相同方式减的次数。  
#### 注意：$1\le a,b\le 10^{18}$，数据较大，需要使用 long long，辗转相减会超时，我们可以转用辗转相除。  
### Code:  
```cpp
#include <iostream>
using namespace std;
typedef long long ll; //类型定义long long为ll，避免频繁使用long long时费手
int main()
{
	ios::sync_with_stdio(0); //关同步流加速cin输入和cout输出
	ll a, b, ans = 0;		 //定义a，b，总数
	cin >> a >> b;
	while (b != 0) //	辗转相除
	{
		ans += a / b;
		int t = a % b;
		a = b;
		b = t;
	}
	cout << ans;
	return 0; //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/cyaogauu.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF343A)

## 思路

两个电阻器有两种合成方式。

排成一行：$R=R_0+R_e$

排成一列：$\frac{1}{\frac{1}{R_0}+\frac{1}{R_e}}$。

我们手上有一个 $\frac{a}{b}$ 的电阻。

排成一行：$\frac{a}{b}+1=\frac{a+b}{b}$。

排成一列：$\frac{1}{\frac{a}{b}+1}=\frac{a}{a+b}$。

反推可知：

如果 $a$ 大，就变成 $a - b$，如果 $b$ 大，就变成 
$b - a$。

一直下去，结果为 $\frac{1}{1}$,再减一次就是 $0$ 了。

这其实就是辗转相减法，只是条件略有不同。

但是看题目中的数据范围，用辗转相减法一定超时，这个问题也好解决，只需要把辗转相减法换成辗转相除法。

再补一句：本题要开 ``long long``。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main()
{
	cin>>a>>b;
	long long sum=0; 
	while(b!=0)
	{
		sum+=a/b;
		c=a%b;
		a=b;
		b=c;
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：baoziwu2 (赞：0)

~~非常好题目，爱来自瓷器。~~

做这道题前要先充分确保读懂题意。
一个合法的串联操作和并联操作必须串/并联一个单位电阻。

也就是说先串两个大于一的电阻，在并到一起是的操作是不合法的。

那么构造方案就比较符合直觉了：

考虑我们手上现在有一个 $\frac{a}{b}$ 的电阻，我们有两个操作：

1. 串联一个单位电阻，电阻变成 $\frac{a}{b} + 1 = \frac{a + b}{b}$。
2. 并联一个单位电阻，电阻变成 $\frac{1}{\frac{a}{b} + 1} = \frac{a}{a + b}$。

所以只要逆推即可。

根据 [Calkin–Wilf_tree](https://en.wikipedia.org/wiki/Calkin%E2%80%93Wilf_tree) 的性质，我们可以通过这种方式表示出任意有理数。

但直接用更向减损术铁定会超时，考虑使用辗转相除法优化成 $O(\log n)$。

```Python
def ansGet(a, b):
    if(b == 0): return 0
    return a // b + ansGet(b, a % b)

a, b = map(int, input().split())
res = ansGet(a, b)
print(res)
```



---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF343A)

## 题意简述

许多 $1Ω$ 的电阻欲通过串联，并联使得总阻值为 $\frac{a}{b}$，求最少需要的数量。$1\le a,b\le 10^{18}$。

## 分析

两个电阻器可以做两种合成方式：
- 串联一个单位电阻，$R=R_0+R_e$

- 并联一个单位电阻，电阻变成 $R=\frac{1}{\frac{1}{R_e}+\frac{1}{R_0}}$。

考虑我们手上现在有一个 $\frac{a}{b}$ 的电阻，我们有两个操作：

- 串联一个单位电阻，电阻变成 $\frac{a}{b} + 1 = \frac{a + b}{b}$。

- 并联一个单位电阻，电阻变成 $\frac{1}{\frac{a}{b} + 1} = \frac{a}{a + b}$。

然后反推可以得到：

如果 $a$ 大，就变成 $a-b$，如果 $b$ 大，就变成 $b-a$。

一直下去，最后会得到电阻为 $\frac{1}{1}$ 然后再一次就得到 $0$ 了。

所需电阻器的数量就为减的次数。但是，这样一直减会超时所以这里要用辗转相除。

注意：这里要用 ``` long long```!

## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long c,d,x,sum=0; 
	cin>>c>>d;
	while(d!=0)
	{
		sum+=c/d;
		x=c%d;
		c=d;
		d=x;
	}
	cout<<sum;
	return 0;
}
```


---

