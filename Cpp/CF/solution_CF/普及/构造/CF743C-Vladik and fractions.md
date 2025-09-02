# Vladik and fractions

## 题目描述

Vladik and Chloe decided to determine who of them is better at math. Vladik claimed that for any positive integer $ n $ he can represent fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/98fe6e67c0215dd9544c203cfb728334ac03fc69.png) as a sum of three distinct positive fractions in form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/140afc1972028e64ad54d4357592e925861bdf13.png).

Help Vladik with that, i.e for a given $ n $ find three distinct positive integers $ x $ , $ y $ and $ z $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/388f8aea1d0cb4eefcbda4cfdf528ffa9edb155f.png). Because Chloe can't check Vladik's answer if the numbers are large, he asks you to print numbers not exceeding $ 10^{9} $ .

If there is no such answer, print -1.

## 说明/提示

对于$100$%的数据满足$n \leq 10^4$  
要求答案中$x,y,z \leq 2* 10^{9}$

## 样例 #1

### 输入

```
3
```

### 输出

```
2 7 42
```

## 样例 #2

### 输入

```
7
```

### 输出

```
7 8 56
```

# 题解

## 作者：封禁用户 (赞：39)

**恶意评分好严重啊（小学数学题，怎么变蓝题了？）**



------------


进入正题

**题目意思：** 给出$n$，问当$x$、$y$、$z$为几时（$x$、$y$、$z$互不相等）， $\frac{1}{x}+\frac{1}{y}+\frac{1}{z}=\frac{2}{n}$ 。

这样一看，你就会奇怪：$\frac{2}{n}$的分子为什么是$2$？再仔细想想，明显就是让我们把$\frac{2}{n}$，拆成两个$n$分之一啊！这题就变得简单多了。

一开始

$$\frac{1}{x}+\frac{1}{y}+\frac{1}{z}=\frac{2}{n}$$

按照上面的思路，则

$$\frac{1}{x}+\frac{1}{y}+\frac{1}{n}=\frac{2}{n}$$

两边分别减去$\frac{1}{n}$，变成

$$\frac{1}{x}+\frac{1}{y}=\frac{1}{n}$$

我们再想，$\frac{1}{n}$不就等于$\frac{1}{n+1}+\frac{1}{n\times(n+1)}$吗？

经过刚刚一想，就变成了

$$\frac{1}{n+1}+\frac{1}{n\times(n+1)}=\frac{1}{n}$$

所以得出

$$x=n+1,y=n\times(n+1),z=n$$

但看到题解区这么多dalao是从小到大的，那我们也排排序吧

$$x=n,y=n+1,z=n\times(n+1)$$

**关于无解的情况**

只要仔细想就可以知道，$n \le 1$时才会无解。

求过qwq

---

## 作者：jins3599 (赞：6)

一道蛮有趣的构造题。

### 题目大意

给定一个数$n$，求满足以下条件的$x,y,z$，若无解输出`-1`。

$$\frac{2}{n}=\frac{1}{x}+\frac{1}{y}+\frac{1}{z}$$

### 思路

首先可以想到的是
$$\frac{2}{n}=\frac{1}{n}+\frac{1}{n}$$

于是可以设 $x=n$，那么题设转化为了求：

$$\frac{1}{n}=\frac{1}{y}+\frac{1}{z}$$

重点在于求$y,z$。

作为一个文化课选手，看到$\frac{1}{n}$我就想到了下面的柿子：

$$\frac{1}{n(n+1)}=\frac{1}{n}-\frac{1}{n+1}$$

转化一下我们的柿子？

$$\to \frac{1}{n}-\frac{1}{z}=\frac{1}{y}$$

令$y=n(n+1),z=n+1$即可。

自此，我们得到了答案：$n,n+1,n(n+1)$


什么时候无解？注意到当$n=1$时，$n(n+1)=n+1$，别的情况下三者均不同，于是当$n=1$的时候输出$-1$即可。

$Code:$
```cpp
//CF743C
#include <bits/stdc++.h>

using namespace std;

int n;

int main () {
	scanf("%d" , &n);
	if(n == 1) {puts("-1"); return 0;}
	printf("%d %d %d" , n , n + 1 , n * (n + 1));
	return 0;
}
```

---

## 作者：DarthVictor (赞：5)

# 题目
[原题链接](https://www.luogu.com.cn/problem/CF743C)
# 解说
找来一些思维题练手，碰上了这一道，个人觉得挺有意思，写博客以记之。

首先有$x,y,z$三个变量对于我们来说是非常不利的，因为很难进一步确定变量之间的关系。那么我们就要想办法先干掉一个变量。既然$x,y,z$都没有什么特殊要求，我们不妨构造出最简单的情况：

不妨令 

$$ z=n $$

则有

$$ \frac{1}{x}+\frac{1}{y}=\frac{1}{n}$$

我们的式子里只有两个变量了，很容易进一步确定它们之间的关系：

$$y=\frac{n \cdot x}{x-n}$$

再一次，既然$x,y,z$没什么特殊要求，不妨令$x=n+1$使我们的工作更加简单。将$x=n+1$代入上式便可以得到:

$$y=n^2+n$$

至此，我们就已经确定了这个方程的一组特解：

$$
\begin{cases}
x=n+1 \\
y=n^2+n\\
z=n
\end{cases}$$

提交之后欢迎直接开门红！

我们来思考一下哪里出问题了……题目中无解的情况似乎没有用到。那么在什么时候$x,y,z$会无解呢？这时我们又注意到题目中的一个条件$x \neq y \neq z$。简单地解个方程就会发现$n=1$时$n+1=n^2+n$，我们的特解不符合要求，因此我们猜测$n=1$时原方程无解。但是我们应当进行严谨的证明。

证明：因为$x,y,z \in N^{+}$且$\frac{1}{x}+\frac{1}{y}+\frac{1}{z}=2$，所以$x,y,z$中必然有且只有一者为$1$(可以假设若$x,y,z$均不为$1$，则$\frac{1}{x}+\frac{1}{y}+\frac{1}{z}$最大只能为$\frac{3}{2}$；若$x,y,z$中有不止一个为$1$，则$\frac{1}{x}+\frac{1}{y}+\frac{1}{z}$肯定大于$2$)。

所以不妨令$z=1$，则
$$\frac{1}{x}+\frac{1}{y}=1$$
即
$$\frac{1}{y}=\frac{x-1}{x}$$
因为右边的分子必须可以约分为$1$，所以$gcd(x-1,x)=x-1$，但$\forall x \in N^{+},gcd(x-1,x)=1$，所以$x$只能为$2$，但将$x=2$代入$x$与$y$的关系式可得$y=2$，不符合$x \neq y$，所以$n=1$时原方程无解。
$$Q.E.D.$$
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	if(n==1) printf("-1\n");
	else printf("%d %d %d\n",n,n+1,n*n+n);
	return 0;
}
```

---

## 作者：彭程远 (赞：5)

- #### 题意

题目的要求就是输入 n，求满足 $\frac{1}{x}$+$\frac{1}{y}$+$\frac{1}{z}$=$\frac{2}{n}$ 并且 x≠y≠z 成立的 x，y，z 的值。若无解，输出 -1。

- #### 分析

仔细一想，这不就是小学奥数中的裂项吗？？？

先将 $\frac{2}{n}$ 分为 $\frac{1}{n}$+$\frac{1}{n}$，

再根据裂项公式 $\frac{1}{n}$-$\frac{1}{n+1}$=$\frac{1}{n(n-1)}$ 导出 $\frac{1}{n}$=$\frac{1}{n+1}$+$\frac{1}{n(n-1)}$。

所以 $\frac{2}{n}$=$\frac{1}{n}$+$\frac{1}{n+1}$+$\frac{1}{n(n-1)}$。

然后 $\frac{1}{x}$+$\frac{1}{y}$+$\frac{1}{z}$=$\frac{1}{n}$+$\frac{1}{n+1}$+$\frac{1}{n(n-1)}$。

于是 x=n，y=n+1，z=n(n-1)。

但当 n=1 时，y=z，无解，输出 -1。

- #### 代码

#### c++

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n==1)  //如果n==1，无解，输出-1
        cout<<-1<<endl;
    else  //反之，输出x，y，z
        cout<<n<<' '<<n+1<<' '<<n*(n+1);
    return 0;
}
```

#### python

```python
n=int(input(""))
if n==1:  #如果n==1，无解，输出-1
    print(-1)
else:  #反之，输出x，y，z
    print(n," ",n+1," ",n*(n+1))
```


---

## 作者：Rulu (赞：2)

题意
------------
给一个数 $n$ ，求下面式子的解 $x,y,z$ ( $x,y,z$ 互不相同)，若无解，输出 $-1$ 

$\dfrac{1}{x}+ \dfrac{1}{y} + \dfrac {1}{z} = \dfrac {2}{n}$

分析
------------

原式结果 $\frac{2}{n}$  可拆成

$\dfrac{2}{n}=\dfrac{1}{n}+\dfrac{1}{n} $ 

根据裂项公式

$\dfrac{1}{n}-\dfrac{1}{n+1}=\dfrac{1}{n(n+1)}$ 

可以推导出

$\dfrac{1}{n}=\dfrac{1}{n+1}+\dfrac{1}{n(n+1)}$

原式变为

$\dfrac{1}{x}+ \dfrac{1}{y} + \dfrac {1}{z} = \dfrac {1}{n}+\dfrac{1}{n+1}+\dfrac{1}{n(n+1)}$

那么

 $x,y,z$ 分别为 $n,n+1,n(n+1)$ 

如果 $n=1$ ,那么 $y=z$ ，无解，输出 $-1$ 即可

代码
------------
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;//一个整数n 
	cin>>n;
	if(n==1)//n=1,无解
	{
		cout<<-1;//输出-1 
	}
	else//n!=1,合法的解
	{
		cout<<n<<" "<<n+1<<" "<<n*(n+1)<<endl;//输出x,y,z 
	}
	return 0; 
}

```




---

## 作者：jijidawang (赞：2)

- [博客体验](https://www.luogu.com.cn/blog/writeSTL/solution-cf743c)

## 题面简述

> 给定 $n$，求一组合法且互不相同的 $x,y,z$ 使得 $\dfrac{1}{x}+\dfrac{1}{y}+\dfrac{1}{z}=\dfrac{2}{n}$。

## 算法分析

因为 $\dfrac{2}{n}=\dfrac{1}{n}+\dfrac{1}{n}$，考虑将 $\dfrac{1}{x},\dfrac{1}{y},\dfrac{1}{z}$ 中一个变成 $\dfrac{1}{n}$，比如用 $\dfrac{1}{x}$。

然后原式变成：

$$\dfrac{1}{n}+\dfrac{1}{y}+\dfrac{1}{z}=\dfrac{2}{n}$$

消掉一个 $\dfrac{1}{n}$，原式变成：

$$\dfrac{1}{y}+\dfrac{1}{z}=\dfrac{1}{n}$$

对于任意自然数 $k$：

$$\dfrac{1}{k}-\dfrac{1}{k+1}=\dfrac{k+1}{k^2+k}-\dfrac{k}{k^2+k}=\dfrac{1}{k^2+k}$$

移项：

$$\dfrac{1}{k}=\dfrac{1}{k+1}+\dfrac{1}{k^2+k}=\dfrac{1}{k+1}+\dfrac{1}{k(k+1)}$$

于是考虑将 $\dfrac{1}{n}$ 分解为 $\dfrac{1}{n+1}+\dfrac{1}{n(n+1)}$，将其赋为 $\dfrac{1}{y},\dfrac{1}{z}$ 即可。

得出：

$\begin{cases}x=n\\y=n+1\\z=n(n+1)\end{cases}$

判断无解：

- 因为 $x\neq y\neq z$，所以 $x,y,z$ 最小为 $1,2,3$，此时 $\dfrac{1}{x}+\dfrac{1}{y}+\dfrac{1}{z}=2$，所以 $\dfrac{2}{n}\ge 2$，$n\ge 1$。

代码如下：

```cpp
#include<cstdio>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    if (n>=1) printf("%d %d %d\n",n,n+1,n*(n+1));     
    else puts("-1");  //判断无解
    return 0;
}
```

---

## 作者：OItby (赞：2)

看到$\frac {2}{n}$很容易猜想$x$，$y$或者$z$中有一个等于$n$，那么我们先设$x=n$，则有$\frac{1}{y} + \frac {1}{z} = \frac {1}{n}$，由样例二我们猜想，$y=n+1$，$z=n\times(n+1)$，正好有公式$\frac{1}{n+1} + \frac {1}{n\times(n+1)} = \frac {1}{n}$，所以我们可以得出一组可行解$x=n$，$y=n+1$，$z=n\times(n+1)$

很显然，这题有多种解，将我们的解代入样例$1$，可以发现这是可行的

但是当$n=1$时，无解

下面给出两种证法

1. 当$n=1$时，$n+1=2$，$n\times(n+1)=2$，与题目中的$x≠y$ , $x≠z$ , $y≠z$矛盾

2. 因为$x≠y$ , $x≠z$ , $y≠z$，且$x,y,z$都是整数，所以$x,y,z$的最小值分别为$1,2,3$，此时$\frac {1}{x} + \frac{1}{y} + \frac {1}{z} = 1 = \frac {2}{2}$，很显然$n≥2$时才有解

$My~Code$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	if(n==1) puts("-1");
	else printf("%d %d %d\n",n,n+1,n*n+n);
	return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：1)

还记得小学数学中的 $\frac{1}{n}-\frac{1}{n+1}=\frac{1}{n \times (n+1)}$ 吗？没错，可以转换一下，变成 $\frac{1}{n}=\frac{1}{n+1}+\frac{1}{n \times (n+1)}$，这样，我们发现可以构造出 $n,n+1,n \times (n+1)$ 三个答案。

可是，很明显，如果 $n=1$，那么必须 $x=1$ 且 $\frac{1}{y}+\frac{1}{z}=1$，显然不成立，所以输出 $-1$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n!=1)cout<<n<<" "<<n+1<<" "<<n*(n+1);
	else cout<<-1;
	return 0;
}
```

---

## 作者：j_GF_y (赞：1)

### 题目：

[Vladik and fractions](https://www.luogu.com.cn/problem/CF743C)

### ~~运用小奥思维即可~~

------------

### 题目大意：
知自然数n，求满足下列条件且互不相等的x,y,z,若无解则输出-1.

$\dfrac{1}{x}$ $+$ $\dfrac{1}{y}$ $+$ $\dfrac{1}{z}$ $=$ $\dfrac{2}{n}$

------------
### 思路：

显然可以将 

$\dfrac{2}{n}$ 拆成$\dfrac{1}{n}$ $+$ $\dfrac{1}{n}$ ,

我们不妨设x=n,那么原式变为

$\dfrac{1}{n}$ $+$ $\dfrac{1}{y}$ $+$ $\dfrac{1}{z}$ $=$ $\dfrac{2}{n}$

即

$\dfrac{1}{y}$ $+$ $\dfrac{1}{z}$ $=$ $\dfrac{1}{n}$

所以转化为了求y,z的问题。

小奥中有一个最基本的裂项式子：

$\dfrac{1}{n(n+1)}$ $=$ $\dfrac{1}{n}$ $-$ $\dfrac{1}{n+1}$

转换原式,可得

$\dfrac{1}{y}$ $=$ $\dfrac{1}{n}$ $-$ $\dfrac{1}{z}$ 

代入上式,令y=n(n+1),z=n+1即可。

即x=n,y=n(n+1),z=n+1。

当n=1时,y=z,不满足题目要求，此时输出-1即可。



------------

### code:

    #include <bits/stdc++.h>
    
    using namespace std;
    
    int n;

    int main ()
    {
        cin>>n;
        if(n==1){
            cout<<"-1";
            return 0;
        }
        cout<<n<<" "<<n+1<<" "<<n*(n+1);
    }
    
    

------------

求过鸭~

---

## 作者：HPXXZYY (赞：0)

因为题目要凑出来的数是 $\dfrac{2}{n}$，所以我们很自然会想到一个贪心：让其中一个分数是 $\dfrac{1}{n}$，这样我们只需再用两个分子为 $1$ 的分数凑出 $\dfrac{1}{n}$ 即可。

我们知道有这么个式子：

$$\dfrac{1}{n+1}+\dfrac{1}{n \times (n+1)}=\dfrac{n}{n \times (n+1)}+\dfrac{1}{n \times (n+1)}=\dfrac{n+1}{n \times (n+1)}=\dfrac{1}{n}$$

所以，我们只需让三个分数分别为 $\dfrac{1}{n},\dfrac{1}{n+1},\dfrac{1}{n \times (n+1)}$ 即可。

什么时候无解？当且仅当 $n=1$ 时会无解。

因为 $n \leq 1 \times 10^4$，所以有解时 $n \times (n+1)$ 是 $1 \times 10^8$ 级别的，构造出的解符合题意。

> 如果你觉得本题解的思路来得太突兀，认真观摩一下样例 $2$ 吧，你会从中获得灵感的！

```cpp
int main(){
	int n;scanf("%d",&n);
	if (n==1) printf("-1");
	else printf("%d %d %d",n,n+1,n*(n+1));
	return 0;
}

除去头文件后，这道题的代码就是这么的短，重点在思维啊！
```

---

## 作者：Instudy (赞：0)

评价：小奥题，裂项好题，难度感觉评高了。

显然：

$ \frac{2}{n}= \frac{1}{n}+\frac{1}{n}$，不妨设 $ x=n $

则 $ \frac{1}{y}+\frac{1}{z}=\frac{1}{n}$，我们关注到一个很好的性质（裂项）： $ \frac{1}{n}-\frac{1}{n+1} =\frac{1}{n(n+1)} $

于是我们进行移项：$ \frac{1}{n}=\frac{1}{n+1} +\frac{1}{n(n+1)} $，仍然是非常显然。

于是我们构造出了$ \frac{1}{x}+\frac{1}{y}+\frac{1}{z}=\frac{2}{n}$的一个解。

注意到题目的一个要求：$ x,y,z $互不相等，那我们列出三个方程：

 ① 若 $ x=y $，则 $ n=n+1 $ 矛盾，舍

 ②  若$ x=z $ 则 $ n=n(n+1) $，解得 $n=0$ 或$1 $ 

又∵  $ 1<=n<=10^4 $，故 $ n=1 $ 时无解

 ③ 若$ y=z $,则 $ n+1=n(n+1) $ 解得 $n=0$ 或$-1 $ ，又∵  $ 1<=n<=10^4 $，故矛盾，舍

综上：~~看程序~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
   scanf("%d",&n);
   if(n==1)
   {
    printf("-1");
    return 0;
   }
   printf("%d %d %d",n,n+1,(n+1)*n);
   return 0;
}
```


---

## 作者：nju_zdd (赞：0)

## 显然，这是一道数学题
 因为等号右边是$\frac{2}{n}$,所以我们自然而然地想到等号左边分母会有n，我们不妨令x=n.

 移项之后，我们可以看到：**$\frac{1}{y}$+$\frac{1}{z}$=$\frac{1}{n}$**.
 
------------

### 重点来了！！！
 大家小学都学过分数的$\color{red}\text{“裂项”}$吧.
 
 譬如说：$\frac{1}{6}$=$\frac{1}{2×3}$=$\frac{1}{2}$-$\frac{1}{3}$，稍加变化即为$\frac{1}{3}$+$\frac{1}{6}$=$\frac{1}{2}$. 

------------
 
### 各位想到了什么？
$y\to 3\ ,z\to 6\ ,n\to 2$

即$y\to 3=(n+1)\ ,z\to 6=n\times(n+1)\ ,n\to 2$

那么我们可以立即得出答案：

$\frac{1}{n}+\frac{1}{n+1}+\frac{1}{n\times(n+1)}=\frac{2}{n}$

**还要加一个特判（$n\le 1$）,此时无解，输出$-1$**。

------------


$\color{red}\text{附AC代码：}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if (n>1)
	cout<<n<<" "<<n+1<<" "<<n*(n+1);
	else
	cout<<-1; 
	return 0;
}
```


---

## 作者：汪鸣谦 (赞：0)

此题很水

纯数学题

我们不妨将2/n拆开，变成1/n+1/n，这样就构造出了一个符合题目要求的数：n

再把1/n拆成1/a+1/b的形式，如下

1/n=n+1/n*(n+1)=n/n*(n+1)+1/n*(n+1)=1/n+1+1/n*(n+1)

至此得到x=n,y=n+1,z=n*(n+1),输出这三个数即可

最后注意对n=0和n=1的情况特判

AC代码：

```
#include<iostream>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n!=0&&n!=1)
	cout<<n<<" "<<n+1<<" "<<n*(n+1);
	else
	cout<<"-1";
	return 0;
}
```



---

