# Let's Play Osu!

## 题目描述

你在玩一个叫做 Osu 的游戏（某音游）！我们来简化一下游戏规则。一局游戏中需要点击 $n$ 次。每一次点击有两种结果：正确或失误。我们定义正确为符号 `O`，失误为 `X`，那么整局游戏可以被写成一个长度为 $n$ 的由字符 `X` 或 `O` 组成的字符串。

用这个字符串你可以用以下的方法计算游戏的得分：对于一个极大的连续的 `O` 连击，将连击的次数的平方加入到总得分中（即连续的 `O` 的个数的平方）。举例说明，如果你的游戏序列为 `OOXOOOXXOO`，那么极大连续的 `O` 连击共有三个：`OO`，`OOO`，`OO`，所以你的总得分为 $2^2 + 3^2 + 2^2= 17$ 。如果整局游戏里没有一次成功的点击那么总得分就为 $0$。

你现在知道了第 $i$ 次 ($1\leq i\leq n$)点击成功的概率为 $p_i$，换句话说，字符串中第 $i$ 个字符有 $p_i$ 的概率成为 `O`，有 $1-p_i$ 的概率成为 `X`，你的任务是算出你游戏总得分的期望值。

## 说明/提示

$3$ 位字符串一共有 $8$ 种不同的情况。每一种出现的概率为 $0.125$ 所以期望得分是 $\dfrac{(9+4+2+1+4+1+1)}{8}=2.75$。

感谢@[凄魉](/user/45876) 提供的翻译。

## 样例 #1

### 输入

```
3
0.5 0.5 0.5
```

### 输出

```
2.750000000000000
```

## 样例 #2

### 输入

```
4
0.7 0.2 0.1 0.9
```

### 输出

```
2.489200000000000
```

## 样例 #3

### 输入

```
5
1 1 1 1 1
```

### 输出

```
25.000000000000000
```

# 题解

## 作者：nekko (赞：19)

如果你做过[bzoj 4318](https://www.lydsy.com/JudgeOnline/problem.php?id=4318)，你会发现这道题是弱化版……

设$q_i$表示从$i$往左连续的$O$的期望

根据期望的线性性，可得$q_i=p_i(q_{i-1} + 1)$

那么位置$i$会对答案产生多少的贡献呢？

$E((x+1)^2)-E(x^2)=E(x^2+1+2x)-E(x^2)=E(2x+1)$

于是$ans=\sum_{i=1}^{n}p_i (2q_{i-1}+1)$

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
double p1[N], p2[N], f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		double p; scanf("%lf", &p);
		p1[i] = p * (p1[i - 1] + 1);
		f[i] = f[i - 1] + p * (1 + 2 * p1[i - 1]);
	}
	printf("%.10lf\n", f[n]);
}
```

---

## 作者：AzusaCat (赞：17)

#### CF235B Let's Play Osu!

[题目链接](https://www.luogu.com.cn/problem/CF235B)

感觉这里的题解有些把平方的期望和答案搞混了，我们来从期望的定义来推一下式子。

设 $ans_i$ 表示以 $i$ 结尾的**答案**，$f_i$ 表示以 $i$ 结尾的连续成功**连击数**的期望，$g_i$ 表示以 $i$ 结尾的连续成功**连击数的平方**的期望（这个东西并不需要用，列在这里只是为了说明和 $ans_i$ 的区别）。

对于任何一种状态，我们可以把它分成若干块极大的'X'和'O'，那么我们设每一块的成功连击数为 $r_k$ （当这一块是'X'时，我们认为 $r_k=0$）。举个例子，某一个状态为"OOXXOOOXOX"，那么这个状态被分为了六块，分别为 $2,0,3,0,1,0$ 。设某个状态被分为的块数为 $ t $ ，那么由之前的定义，我们有

$$
\begin{aligned}
&ans_i=\sum\limits_{k\in S}p_k({r_{k_1}^2+r_{k_2}^2+\dots +r_{k_{t}}}^2)\\
&f_i=\sum\limits_{k\in S}p_kr_{k_{t}}\\
&g_i=\sum\limits_{k\in S}p_kr_{k_{t}^2}
\end{aligned}
$$

这里为了方便，把所有的项数都用 $t$ 表示，但实际上对每个 $k$ ， $t$ 是不同的。

那么我们考虑转移，先考虑 $f_n$ 向 $f_{n+1}$ 的转移，为了区别每种状态的概率，我们记 $a_n$ 为第 $n$ 块成功为'O'的概率。那么有

$$
\begin{aligned}
f_{n+1}&=\sum\limits_{k\in S}a_{n+1}p_k(r_{k_t}+1)+\sum\limits_{k\in S}(1-a_{n+1})p_k\times 0\\
&=a_{n+1}(\sum\limits_{k\in S}p_kr_{k_t}+\sum\limits_{k\in S}p_k)\\
&=a_{n+1}(f_n+1)
\end{aligned}
$$

意义为这一次转移有 $a_{n+1}$ 的概率为'O'，这样会使之前所有状态的 $r_t$ 加上1或者新建一个为1的 $r_t $ ，从数值上和把之前的 $0$ 变成 $1$ 没有区别，还有 $(1-a_{n+1})$ 的概率为'X'，这样新的状态要不会新建一个为0的 $r_t$ ，要不然就是之前的状态结尾也是'X'，$r_t$ 也是0，所以新的 $r_t$ 一定为0，那么总贡献都为0，所以后面那个求和号是0。然后我们把前边的求和号内的内容拆开，显然 $\sum\limits_{k\in S}p_k$ 等于1，所以我们就得到了 $f$  的转移。

接下来考虑 $ans$ 的转移，我们有

$$
\begin{aligned}
ans_{n+1}&=a_{n+1}\sum\limits_{k\in S}p_k(r_{k_1}^2+r_{k_2}^2+\dots +(r_{k_t}+1)^2)+(1-a_{n+1})\sum\limits_{k\in S}p_k(r_{k_1}^2+r_{k_2}^2+\dots +r_{k_t}^2)\\
&=\sum\limits_{k\in S}p_k(r_{k_1}^2+r_{k_2}^2+\dots +r_{k_t}^2)+a_{n+1}(\sum\limits_{k\in S}p_k(2r_{k_t}+1))\\
&=ans_n+a_{n+1}(2\sum\limits_{k\in S}p_kr_{k_t}+\sum\limits_{k\in S}p_k)\\
&=ans_n+a_{n+1}(2f_n+1)
\end{aligned}
$$

BZOJ里还有一道得分为3次方的题，就需要计算 $g$ 了，这里就不再写了。



---

## 作者：_Rainlzy (赞：11)

### [**前置芝士**](https://oi-wiki.org/dp/probability/)

这道题其实是很好的一道期望 $dp$ 题（~~其实我是奔着  OSU 来的~~），至于什么是 `期望dp` ,上面有/cy。

设 $f_i$ 为点到 $i$ 位置时的期望分数，再设 $k_i$ 为点到 $i$ 位置时的期望长度，然后将 $k_i$ 状态转移就是

$$k_i=(k_{i-1}+1) \times p_i$$

（$p_i$ 为第 $i$ 次点击成功的概率）

那么我们就将点到 $i$ 位置时的期望分数（也就是 $f_i$）进行状态转移。

于是就会出现如下的两种情况：

1. $i$ 位置上的字母为 $X$：期望分数应该为~~上一个~~$f_{i-1}$。
2. $i$ 位置上的字母为 $O$：由于不能直接求解，所以我们需要设 $cnt$ 为连续的字母个数，解得 $(x+1)^2$，利用完全平方公式可得 $x^2+2x+1$，所以最终解得期望分数应该为 $(f_{i-1}+2 \times k_{i-1}+1) \times p_i$。

所以把以上几种情况集中到一起便是：

$$f_i=f_{i-1} \times (1-p_i)+(f_{i-1}+2 \times k_{i-1}+1) \times p_i$$

最终把这个状态转移方程代入代码里就可得到最终的答案。

```
#include <bits/stdc++.h>
using namespace std;
int n;
double p[100005],f[100005],k[100005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
		cin>>p[i];
    for(int i=1;i<=n;i++){
		k[i]=(k[i-1]+1)*p[i];
		f[i]=((f[i-1]+2*k[i-1]+1)*p[i])+(f[i-1]*(1-p[i]));
	}
	printf("%.15lf\n", f[n]);
    return 0;
}
```

---

## 作者：Mr_Skirt (赞：10)

# 题意
有$n$个操作，每个操作有$p_i$几率成功，连续$k$次成功会给总分贡献$k^2$，求最后总分的期望。

# 解题思路
前置：
- 期望的线性性质：$E[aX+b] = aE[X]+b$。
- 区别：$E[X^2]$和$E[X]^2$


先考虑线性情况，即每$i$个连击贡献$i$分值的这种情况。
设$X_i$为经过$i$个操作的**总分**，那么$E[X_i]$经过$i$个操作的**期望总分**，对于第$i$个操作而言，如果成功了，那么总贡献就是上一次的期望总分+1，如果失败了那么总分就不变。求$E[X_i]$可以写成
$$
\begin{aligned}
E[X_i] &= p_iE[X_{i-1}+1] + (1-p_i)E[X_{i-1}] \\
E[X_i] &= p_iE[X_{i-1}] + p_i + E[X_{i-1}] - p_iE[X_{i-1}] \\
E[X_i] &= E[X_{i-1}]+p_i
\end{aligned}
$$

但是如果每个$i$连击贡献$i^2$个，那么此时对于期望总分的贡献就不能只是+1了。
假设经过$i-1$号操作后的连击数为$Y_{i-1}$，那么$i$号操作成功它会对**总分**的贡献是$(Y_{i-1}+1)^2-Y_{i-1}^2 = 2Y_{i-1} + 1$。则对于**期望总分**的贡献是$E[2Y_{i-1} + 1]$。
根据期望的线性性质，我们需要求的就是$2E[Y_{i-1}] + 1$。
$E[Y_i]$翻译成人话就是**经过$i$号操作后的连击数的期望**，这个东西很好求。从$i-1$开始推，如果$i$成功，那么期望连击数就是$E[Y_i]+1$，如果失败直接变成0。于是有：
$$
E[Y_i] = p_i(E[Y_{i - 1}] + 1)
$$
于是我们可以事先求出$E[Y_i]$，然后应用到平方贡献里。设$Z_i$为经过$i$个操作以后的**总分**（此时使用的是连击数的平方)，那么所求就是$E[Z_i]$，即经过$i$个操作以后的**期望总分**
$$
\begin{aligned}
E[Z_i] &= p_i(E[Z_{i-1}+2Y_i+1]) + (1-p_i)E[Z_{i-1}]\\
E[Z_i] &= E[Z_{i-1}] + p_i(2E[Y_i] + 1)
\end{aligned}
$$
那么$E[Z_n]$就是答案了。

注意$X,Y,Z$是三个不同的随机变量

# 拓展
假设每段长度为$i$的连击贡献$f(i)$的分数，那么设（我也不知道该用什么字母）$A_i$为为经过$i$个操作以后的**总分**，所求是$E[A_i]$
$$
E[A_i] = p_iE[A_{i-1} + f(Y_{i-1}+1)-f(Y_{i-1})] + (1-p_i)E[A_{i-1}]
$$
那么假设$f(i) =i^3$，展开后可得
$$
\begin{aligned}
E[A_i] &= p_iE[A_{i-1} + (Y_{i-1}+1)^3 - Y_{i-1}^3] + (1-p_i)E[A_{i-1}] \\
E[A_i] &= p_i(E[A_{i-1}] + E[(Y_{i-1}+1)^3 - Y_{i-1}^3]) + (1-p_i)E[A_{i-1}] \\
E[A_i] &= E[A_{i-1}] + p_iE[Y_{i-1}^3+3Y_{i-1}^2+3Y_{i-1}+1-Y_{i-1}^3]\\
E[A_i] &= E[A_{i-1}] + p_iE[3Y_{i-1}^2+3Y_{i-1}+1]\\
E[A_i] &= E[A_{i-1}] + p_i(3E[Y_{i-1}^2]+3E[Y_{i-1}] + 1)
\end{aligned}
$$
$E[Y_{i-1}]$我们之前求过，那么问题就在于怎么求$E[Y_{i-1}^2]$。
$$
\begin{aligned}
E[Y_i^2] &= p_i(E[(Y_{i-1}+1)^2])\\\\
E[Y_i^2] &= p_i(E[Y_{i-1}^2+2Y_{i-1}+1])\\\\
E[Y_i^2] &= p_i(E[Y_{i-1}^2]+2[Y_{i-1}]+1])
\end{aligned}
$$
到这里，我们就应该会求$E[Y_i^2]$了吧。
搞清楚到底是总分还是总分的期望应该就是这道题最关键的一点了。

# 时间复杂度
$O(n)$
# 参考代码
```cpp
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
        EY[i] = (EY[i - 1] + 1) * p[i];
    }
    for (int i = 1; i <= n; i++) {
        EZ[i] = EZ[i - 1] + (2 * EY[i - 1] + 1) * p[i];
    }
    printf("%lf", EZ[n]);
    return 0;
}
```

---

## 作者：D12241R (赞：7)

连续$x$个$won$就有$x\times x$分

考虑增加1个$O$：

$(x+1)^2$=$x^2+2x^1+1$

与原来相比增加了：

$2x^1+1$

题目变成维护这个增加值的期望,所以我们处理$x^1$:

$x1[i]$表示$x^1$的期望;

$x2[i]$表示答案的期望;

$x1[i]=(x1[i-1]+1)*p[i];$

$x2[i]=(x2[i-1]+2*x1[i]+1)*p[i]+x2[i-1]*(1-p[i])$

所以，我们简化一下$x2$:

$x2[i]=x2[i-1]+(2*x1[i-1]+1)*p[i]$

答案是$x2[n]$。

此题还可以用滚动数组优化空间，~~但这题不用优化也能过~~。

```
#include<stdio.h>
#define R register
#define maxn 100001
int n;
double a,x1[maxn],x2[maxn];
int main(void)
{
	scanf("%d",&n);
	for(R int i=1; i<=n; i++)
	{
		scanf("%Lf",&a);
		x1[i]=(x1[i-1]+1)*a;
		x2[i]=x2[i-1]+(x1[i-1]*2+1)*a;
	}
	printf("%.15Lf",x2[n]);
	return 0;
}
```

---

## 作者：轻舟XY (赞：6)

[CF235B Let's Play Osu!](https://www.luogu.com.cn/problem/CF235B)

这道概率 $DP$ 比较套路，其实楼上各位 $dalao$ 已经讲的很详细了。这里主要给没有学过期望的同学解释一下期望的线性性质。

**前置知识：**

期望的线性性质：所有可能的值的加权和，权重为对应值发生的概率。

由此我们可以得到：

$$E(aX+bY)=E(aX)+E(bY)$$

$$E(aX)+E(bY)=aE(X)+bE(Y)$$

在本题中，加入答案的是连续的 $O$ 的个数的平方，那我们可不可以直接加入期望的平方呢？

在一般情况下，两个随机变量的积的期望值不等于这两个随机变量的期望值的积，所以 $E(a)^2 \not={E(a^2)}$ （可以类比 $(a+b)^2 \not ={a^2+b^2}$ ）。

所以答案是不行。

那应该怎样做呢？

**下面是正解：**

设 $l_1(i)$ 表示截止到  $i$ 的长度的期望。

设当前位置为 $i+1$ ，它对答案的贡献为截止到 $i+1$ 的期望减去截止到上一个位置（即 $i$ 的期望）：

$$E((i+1)^2)-E(i^2)=E(i^2+2i+1)-E(i^2)$$

根据期望的线性性质：

$$E(i^2+2i+1)-E(i^2)=E(i^2)+E(2i)+E(1)-E(i^2)=E(2i+1)$$

又由期望的线性性质可得：

$$l_1(i)= (l_1(i-1)+1)\times x(i)$$

$$ans=\sum_{i=1}^{n}(2l_1(i-1)+1) \times x(i)$$

$ans$ 即为所求。

$code$

```cpp
#include<iostream>
#include<iomanip>
#define maxn 100010
using namespace std;

int n;
double x,l1[maxn],ans[maxn];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		l1[i]=(l1[i-1]+1)*x;
		ans[i]=ans[i-1]+(2*l1[i-1]+1)*x;
	}
	cout<<fixed<<setprecision(15)<<ans[n]<<endl;
	return 0;
}
```

三倍经验：

[P1654 OSU!](https://www.luogu.com.cn/problem/P1654)

[P1365 WJMZBMR打osu! / Easy](https://www.luogu.com.cn/problem/P1365)

---

## 作者：幽界の冥神 (赞：5)

众所周知 ： $(x + 1) ^2 = x ^ 2+2 * x + 1$

因此 : $(x + 1) ^2$ $-$ $x ^ 2$ $=$ $2 * x + 1$

我们设$f_1$表示线性期望，$f_2$表示$Ans$

则有$f_1[i] = (f_1[i - 1] + 1) * p_i$ 

由上述可知$f_2[i] = f_2[i - 1] + (2 *f_1[i - 1] +1) * p_i$

道理大家都懂，我讲的也不是太好，这里讲一种空间优化

$O(n)$ $→$ $O(1)$
 
观察上述式子， 可以发现$f[i]$只与$f[i - 1]$有瓜，而$p_i$也只有暂时的用处

由此，将二式颠倒位置即可无数组实现，具体见代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define D double
#define N 100005

using namespace std;

int n;
D a, f1, f2;

int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf ("%lf", &a);
		f2 = f2 + (f1 * 2 + 1) * a;//空间优化
		f1 = (f1 + 1) * a;
	}
	printf ("%.15lf", f2);//一个好的OIER是会数数字位数的
	return 0;
}
```
最后，如果你不会期望，推荐[这个人的博客](https://45475.blog.luogu.org/mathematical-expectation)，讲得很清楚

AND安利一波[我的博客](https://33006.blog.luogu.org/)

---

## 作者：蒟蒻CGZ (赞：4)

## [CF235B Let's Play Osu!](https://www.luogu.com.cn/problem/CF235B)

我们观察到 ${(x+1)}^2 - x^2 = 2 x + 1$ ，那么根据期望的线性性质，我们可以单独算每一个字符的贡献。设 $l(i)$ 为以 $i$ 为结尾的极大连续 **o** 的期望长度，$s_i$ 为第 $i$ 个字符，那么有 $2$ 种情况：

- $s_i = o$ ，对答案的贡献为 $l(i-1) \times 2 + 1$ ，长度计算方式为 $l(i) = l(i-1) + 1$
- $s_i = x$ ，对答案的贡献为 $0$，长度计算方式为 $l(i) = 0$

以上两种情况概率分别为 $p_i$，$(1-p_i)$。

而第二种情况对于答案没有贡献，所以可以在代码中省略。

## 核心代码
```cpp
double a;
for (int i = 1; i <= n; ++ i) {
	cin >> a; 
	ans += (len * 2.0 + 1.0) * a;
	len = (len + 1.0) * a;
}
```


---

## 作者：thecold (赞：4)

[CF235B Let's Play Osu!](https://www.luogu.com.cn/problem/CF235B)

这个题就是一道概率DP，我们考虑第i位的贡献是多少就可以了

我们设x为前i - 1位的序列长度

首先（x + 1）的平方与x的平方的差值就是第i位的贡献 ， 为2 * x + 1，我们可以看到第i位的贡献与前面的线段长度有关,所以我们理所当然的需要记录前i - 1位的期望长度，

### 即 len[i] = (len[i - 1] + 1) * p[i]

那么当前第i位的贡献就是2 * len[i - 1] + 1,最终答案将其累加起来即可（毕竟算的是每位的贡献）


## 注意是15位小数
接下来是愉快的代码时间

```
#include<cstdio>
#include<cctype>
#include<cmath>
using namespace std;
inline int read()
{
	int res = 0;
	char c;
	bool flag = true;
	c = getchar();
	while(!isdigit(c))
	{
		if(c == '-')	flag = false;
		c = getchar();
	}
	while(isdigit(c))
	{
		res = res * 10 + (c ^ 48);
		c = getchar();
	}
	return flag ? res : -res;
}
const int Max_n = 1e5 + 5;
int n;
double len[Max_n] , p[Max_n] , ans;
int main()
{
	n = read();
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%lf" , p + i);
	for(int i = 1 ; i <= n ; ++ i)
	{
		len[i] = (len[i - 1] + 1) * p[i];
		ans +=  (2 * len[i - 1] + 1) * p[i];
	}
	printf("%.15lf" , ans);
	return 0;
}
```


---

## 作者：psoet (赞：3)

不会概率期望的线性性质怎么办？想不出题解中的神奇dp怎么办？

**就用普通的概率dp做法即可，无脑推式子。**

我们令$d(i)$表示前i个的期望分值。d(0)=0,规定d(-1)=0。（方便起见）显然有：

$$d(i)=\sum_{j=0}^i [d(j-1)+(i-j)^2](1-p_j)\prod_{k=j+1}^ip_k$$

虽然长得恶心，但不难理解。j就是来枚举“失败”的位置（可以是0），所以要乘上 $(1-p_j)$。j之后的必定都成功，所以有了乘积式$\prod_{k=j+1}^ip_k$。

之后怎么办？那个完全平方让人难以下手。**所以把它拆了，同时将i项提到前面去。**
$$d(i)= \sum_{j=0}^i[d(j-1)+j^2](1-p_j)\prod_{k=j+1}^ip_k-2i\sum_{j=0}^ij(1-p_j)\prod_{k=j+1}^ip_k+i^2\sum_{j=0}^i(1-p_j)\prod_{k=j+1}^ip_k$$

虽然还是恶心，但我们令：

$$\begin{aligned}
A_i=\sum_{j=0}^i[d(j-1)+j^2](1-p_j)\prod_{k=j+1}^ip_k\\
B_i=\sum_{j=0}^ij(1-p_j)\prod_{k=j+1}^ip_k\\
C_i=\sum_{j=0}^i(1-p_j)\prod_{k=j+1}^ip_k
\end{aligned}$$

（此时有$d(i)=A_i-2iB_i+i^2C_i$）

可以发现，ABC都可以递推出来。

$$\begin{aligned}
A_i=p_iA_{i-1}+[d(i-1)+i^2](1-p_i)\\
B_i=p_iB_{i-1}+i(1-p_i)\\
C_i=p_iC_{i-1}+1-p_i
\end{aligned}$$

边际条件？可以看出$A_0=B_0=0,C_0=1$。（能够证明C恒为1）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define F(i,a,b) for(int i=a;i<=b;++i)
const int maxn=1e5+5;
int n;
double p[maxn],d[maxn];
int main()
{
	scanf("%d",&n);
	F(i,1,n) scanf("%lf",&p[i]);
	double a=0,b=0;
	F(i,1,n)
	{
		a=p[i]*a+(d[i-1]+(double)i*i)*(1-p[i]);
		b=p[i]*b+i*(1-p[i]);
		d[i]=a-2*b*i+(double)i*i;
	}
	printf("%.9lf",d[n]);
	return 0;
}
```

（思维难度并不高）

---

## 作者：红尘仙 (赞：1)

我们先考虑一下什么是期望：~~(我是看到 OSU 来才来做的)~~，期望我们用计算式表达一下就是 $g\times val$ 就是概率 $\times$ 数值。按照我的浅显的理解，就是类似于一个加权平均数。

### 来到本文
我们发现要求平方的期望，我们一开始是很难做的。但是我们对于贡献是 $x$ ，而不是 $x^2$ 的时候，我们是很容易做出来的。我们假设 $g_i$ 表示以 $i$ 结尾的 $O$ 的个数的期望值，那么我们就有

$g_i = (g_{i-1} + 1 )\times p_i + 0 \times (1-p_i) $ 
分别代表 可以成功 ， 不可以成功 的期望值。加起来就好了。 

我们是要维护一下 $x^2$ 的贡献，那么我们考虑一下我们怎么转化一下能够得到呢？我们假设我们现在维护 $x^2$ 的期望值的为 $f$
他代表的就是以 $i$ 结尾的期望值。

然后我们在小学就有一个式子 $(x+1)^2 = x^2 + 2x + 1$ ，那么我们对于 $x^2$ 也就有了维护，我们就能得到 $f_{i+1} = f_{i}+2g_i + 1$ 这个是什么？是成功的时候，那么不成功的时候呢？
那就还是 $f_{i}$ 

>我们这里取得是答案，而不是像上面的 $g_i$ 一样记录的末尾有多少个 $O$ 的期望值。

所以 $f_{i + 1} = (f_{i}+2g_i+1) \times p_i + f_{i}\times(1-p_i) = f_{i} + (2g_i + 1) * p_i$

### 题外
如果是贡献是 $x^3$ 的时候怎么办？
+ 我们还是一样的直接将 $x^2$ 设为结尾有 $O$ 的个数的期望值
+ 对于 $x^3$ 次方一样的。

我们递推式就是这样： 我们用 $g,f,p$ 表示 $x,x^2,x^3$ 的期望值

$g_i = (g_{i-1} + 1)\times p_i$

$f_{i} = (f_{i-1} + 2g_{i-1}+1)\times p_i$

$p_i = p_{i-1} + (3f_{i-1} + 3g_{i-1} + 1)$


Code:
```
/*
By : Zmonarch
知识点：
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <vector>
#define inf 2147483647
#define int long long
#define qwq register
#define inl inline
const int kmaxn = 1e6 + 10 ;
const int kmod = 998244353 ;
inline int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
int n ; 
double f[kmaxn] , g[kmaxn] , p[kmaxn] ; 
signed main() {
	n = read() ;
	for(qwq int i = 1 ; i <= n ; i++) std::cin >>p[i] ; 
	for(qwq int i = 1 ; i <= n ; i++) 
	{
		g[i] = (g[i - 1] + 1.0) * p[i] ; 
		f[i] = f[i - 1] + ( 2.0 * g[i - 1] + 1.0) * p[i] ; 
	}
	printf("%.15lf" , f[n]) ;  
	return 0 ;
}

```

---

## 作者：whiteqwq (赞：1)

[CF235B Let's Play Osu!](https://www.luogu.com.cn/problem/CF235B)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1716014)

## 题意
题意：给定一个序列，每一个位置$i$为$1$的几率为$p_i$，长度为$k$的极长$1$序列的贡献为$k^2$，求期望贡献。
数据范围：$1\leqslant n\leqslant 10^5$

## 分析
很容易发现这是一道概率dp。

我们考虑以$i$为结尾的极长$1$序列长度为$len_i$，则可以分两种情况讨论$len$的转移：

1. $i$位置为$1$，几率为$p_i$，期望长度为$len_{i-1}+1$；
2. $i$位置为$0$，几率为$1-p_i$，期望长度为$0$。

故$len_i=(len_{i-1}+1)\times p_i+0\times(1-p_i)$

我们求得了位置$i$的期望长度为$len_i$后，可以考虑转移答案$ans$：

首先，在这个极长$1$序列之前的期望贡献显然不需要考虑，我们只需要考虑以$i$结尾的极长$1$序列：
1. 若当前位置为$1$，概率为$p_i$，则在$i-1$位置时，期望长度为$len_{i-1}$，则期望贡献为$len_{i-1}^2$；在$i$位置时，期望长度为$len_{i-1}+1$，则期望贡献为$(len_{i-1}+1)^2=len_{i-1}^2+2len_{i-1}+1$。这两个式子相减则为答案：$len_{i-1}^2+2len_{i-1}+1-len_{i-1}^2=2len_{i-1}+1$；
2. 若当前位置为$0$，概率为$1-p_i$，则无以$i$结尾的极长$1$序列，无贡献。

故$ans_i=ans_{i-1}+(2*len_{i-1}+1)\times p_i+0\times(1-p_i)$

## 代码
记得保留$15$位小数。
```
#include<stdio.h>
const int maxn=100005;
int i,j,k,m,n;
double len[maxn],ans[maxn];
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		double p;
		scanf("%lf",&p);
		len[i]=(len[i-1]+1.0)*p+0.0*(1-p);
		ans[i]=ans[i-1]+(2.0*len[i-1]+1.0)*p+0.0*(1-p);
	}
	printf("%.15lf",ans[n]);
	return 0;
}
```
## 后话
本题弱化版：[P1365 WJMZBMR打osu! / Easy](https://www.luogu.com.cn/problem/P1365)
本题扩展版：[P1654 OSU!](https://www.luogu.com.cn/problem/P1654)

---

## 作者：PrefixAMS (赞：1)

## 思路：通过二项式定理求出高次期望

显然，对于一次期望我们有$x_{i}=(x_{i-1}+1)*P_{i}$。

然后进行二次推导。

$(x_{i}+1)^{2}= x_{i}^2+2x+1$

发现我们 $x_{i}^2$ 可以通过$x_{i}$得到，从而计算出每个点为成功时的期望。

```cpp 
for(int i = 1 ; i <= n ; i ++) { //a为x b为x^2
	a[i] = (a[i - 1] + 1) * p[i];
	b[i] = (b[i - 1] + 2 * a[i - 1] + 1) * p[i];
}
```

这个代码看起来很对 ~~(反正我一开始觉得很对)~~ 。

但是他却忽略了一点。

### 我们是在求$ 1\to n$的总期望，只求一个点必然会错。

思考一下，我们的 $1\to n$  其实是通过第$n$个点成功或者不成功两种情况得来的。

所以我们只需要将不成功时的贡献加上即可。

```cpp
b[i] = (b[i - 1] + 2 * a[i - 1] + 1) * p[i] + b[i - 1] * (1 - p[i]);
```

化简得。

```cpp
b[i] = b[i - 1] + (2 * a[i - 1] + 1) * p[i];
```

### 思考：如果我们要求$3$次以上的期望呢？

我们可以通过二项式定理一次一次的向上推。

例如这样（$3$次）：

```cpp 
for(int i = 1 ; i <= n ; i ++) {
	a[i] = (a[i - 1] + 1) * p[i];
	b[i] = (b[i - 1] + 2 * a[i - 1] + 1) * p[i];
	c[i] = c[i - 1] + (b[i - 1] * 3 + a[i - 1] * 3 + 1) * p[i];
}
```

这样问题就被我们完美解决啦！

---

## 作者：Prean (赞：0)

简单期望/fad

题意明确，不说了。

对于高次期望，一个套路的方法是维护低次期望（？）

考虑 dp，设 dp1[i] 为前 i 次点击中 **所有连续的 O 的长度之和**，dp2[i] 为前 i 次点击中 **所有连续的 O 的长度的平方和**。

很明显有：$ dp1[i]=(dp1[i-1]+1]) \times p[i] $

然后能发现，dp2 其实就是 $ \sum E(len^2) $

而：$ E((len+1)^2) = E(len^2 + 2 \times len +1) = E(len^2) + 2 \times E(len) + 1 $

但是由于有 p 的概率，再加上这只是 **这一段的长度的平方** 的期望，所以剩下 1-p 的概率，长度为 dp2[i-1]

综合起来：
$$ dp1[i]=p[i] \times (dp1[i-1]+1) $$
$$ dp2[i]=dp2[i] + p[i] \times (2 \times dp2[i-1] +1) $$
然后可以滚动“数组”，使得空间为常数。

code:
```cpp
#include<cstdio>
const int M=1e5+5;
double p,dp1,dp2;
int n;
signed main(){
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;++i){
        scanf("%lf",&p);
        dp2+=(2*dp1+1)*p;
        dp1=(dp1+1)*p;
    }
    printf("%.15lf",dp2);
}
```

---

## 作者：Star_Cried (赞：0)

# 期望长度

## 定义

这里期望长度表示一段序列连续长度的期望。具体来说，对于一段序列，每个点都有一个概率**连续**和**断开**。求所有连续序列和的期望。

当然，对于以上期望长度的定义，我们只需要求出每个点存在的期望的和即可。但是题目永远不会这么简单。

### Osu!

>  Osu!是一个音乐游戏，玩家需要对音符在恰当时候进行敲击来通关。一次到位的敲击为o，不到位的为x。一段连续到位的敲击，即combo次数为这段序列的长度。

~~我们接下来讨论的三个题都和这个游戏有关。~~

**********

* **level1**

一段Osu!序列为一串字符，包括'o','x','?'。其中'o','x'的定义如上，'?'表示此位置有**一半**的几率为'o'。游戏得分为所有combo次数**平方**的和。求得分的期望。

也就是我们要求所有序列长度平方的期望和。

#### 期望

期望具有线性性，但不具有积性。这意味着我们无法对求得的期望长度直接平方来得到答案。

并且请注意一点，若一个值的期望为0，并不意味着它的平方的期望为0。这可以帮助我们理解期望的线性性。

期望的平方在大多数情况下并没有什么实际意义。

但是，期望具有线性性。

考虑我们的答案，实际上就是长度平方的期望。考虑往后的转移。（设$f1$表示当前期望长度，$f2$表示**答案**，即长度平方期望的和）

根据公式$(len+1)^2=len^2+2*len+1$若后一位$i$为'o',则后一位$i$的期望值分别为

$f1_i=f1_{i-1}+1$

$f2_i=f2_{i-1}+2*f1_{i-1}+1$

即此位$f2$的值其实是可以从前一位线性转移来的。所谓线性，就是其幂为1。

同样，考虑第$i$位为'x'的情况，$f1=0$,$f2$直接继承前面的答案。

然后我们就可以得到'?'的情况：上述两种情况和除以2.

$f1_i=\frac{f1_{i-1}+1}2$

$f2_i=\frac{2*f2_{i-1}+2*f1_{i-1}+1}{2}$

于是我们就能完成[P1365](https://www.luogu.com.cn/problem/P1365)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	int n;
	double f,len,p;
	inline void work(){
		n=read();
		char c=getchar();
		while(c!='o' and c!='?' and c!='x')c=getchar(); 
		while(n--){
			if(c=='o')f=(f+2*len+1),len=len+1;
            else if(c=='?')f=(2*(f+len)+1)/2,len=(len+1)/2;
            else len=0;
		}
		printf("%.4lf",f);
	}
}
signed main(){
	star::work();
	return 0;
}
```

******

* **level2**

我们发现，其实对于概率任意的情况也可以推出来。上题三种字符其实就是对应概率为1,0.5,0的三种情况。

设$p$为该点为'o'的概率，则有:

$f2_i=f2_{i-1}+p*(2*f1_{i-1}+1)$

$f1_i=p*(f1_{i-1}+1)$

所以上题的代码的核心部分等同于：

```cpp
	while(n--){
		p=c=='o'?1.0:c=='?'?0.5:0.0;
		f=f+p*(2*len+1);
		len=p*(len+1);
		c=getchar();
	}
```

于是我们可以完成[CF235B](https://www.luogu.com.cn/problem/CF235B)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	int n;
	double f,len,p;
	inline void work(){
		n=read();
		while(n--){
			scanf("%lf",&p);
			f=(f-len*len+(len+1)*(len+1))*p+f*(1-p);
			len=p*(len+1);
		}
		printf("%.8lf",f);
	}
}
signed main(){
	star::work();
	return 0;
}
```

******

* **level3**

我们已经完成了对于长度平方的期望和的问题。那么我们就可以解决新的问题：对于答案为所有combo长度**立方**的和的期望我们怎么求解呢？

根据期望的线性性，我们再维护一个平方的期望即可。

根据公式$(len+1)^3=len^3+3len^2+3len+1$，我们可以得到以下转移：
$$
f3_i=f3_{i-1}+p*(3*(f2_{i-1}+f1_{i-1})+1)\\
			f2_i=p*(f2_{i-1}+2*f1_{i-1}+1)\\
			f1_i=p*(f1_{i-1}+1);
$$

## 注意！

我承认我的变量名的定义有亿点点毒瘤，因为读者可以清楚地发现在上一题中$f2$的转移为$f2_i=f2_{i-1}+p*(2*f1_{i-1}+1)$而非当前转移。实际上在定义$f2$时我的定义为**答案**而非二次项的期望，根据期望的线性性，答案是可以继承上一次的答案进行转移的，也就是对于'x'的情况继承$f2$而非$0$的原因。

在此level中我对$f2$重新定义为长度二次幂的期望。希望不要因为我的毒瘤误导大家。

相同的，我对$f3$的定义为**答案**，因此需要继承之前的答案。



于是我们就完成了[P1654](https://www.luogu.com.cn/problem/P1654)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	int n;
	double f1,f2,f3;
	inline void work(){
		n=read();
		double p;
		while(n--){
			scanf("%lf",&p);
			f3=f3+p*(3*(f2+f1)+1);
			f2=p*(f2+2*f1+1);
			f1=p*(f1+1);
		}
		printf("%.1lf",f3);
	}
}
signed main(){
	star::work();
	return 0;
}
```

### 总结

期望好神奇。

---

## 作者：FjswYuzu (赞：0)

前置芝士：数学期望，dp。

因为 $(x+1)^2=x^2+2x+1$，而 $E(x+y)=E(x)+E(y)$，我们设 $osu$ 为线性期望（类似于一次），$dp$ 表示答案。很容易得到：

$$osu_i=(osu_{i-1}+1) \times p_i$$

$$dp_i=dp_{i-1}+p_i \times (2 \times osu_{i-1} +1)$$

综上，答案为 $dp_n$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
double osu[100005],dp[100005];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		double cure;
		scanf("%lf",&cure);
		osu[i]=cure*(osu[i-1]+1);
		dp[i]=dp[i-1]+cure*(2*osu[i-1]+1);
	}
	printf("%.10f",dp[n]);
	return 0;
}
```

---

## 作者：Rossie65536 (赞：0)

# 题目大意
求出总得分的期望值。

## 思路
还没有学习数学期望的小朋友赶紧去学一下数学期望，这里只提供公式：

$E\left ( x \right )=\sum_{k=1}^{\infty }x_{k}p_{k}$

其中$x_{k}$表示对应的值，$p_{k}$表示对应的概率。

从题意中很容易看出只有$O$才会对答案做出贡献，设之前连续$O$的长度为$x$，则每次多出一个$O$造成的贡献就是$\left ( x+1 \right )^{2}-x^{2}=2*x+1$，因此我们可以用两个数组，一个是$l_{i}$，表示线性期望，另一个是$ans_{i}$，表示到i的期望得分，很容易得到

$l_{i}=\left(l_{i-1}+1\right)*p$

$ans_{i}=ans_{i-1}+\left(2*l_{i-1}+1 \right )*p$

这里显然可以空间优化，这里不多说明。

# AC代码
```cpp
#include <cstdio>

#define RI register int

using namespace std;

template <class T>
inline void read(T &x) {
    T f = 1; x = 0; char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-')
            f = -f;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}

int n;
double l, ans, p;

int main() {
    read(n);
    for(RI i = 1; i <= n; i++) {
        scanf("%lf", &p);
        ans += (l * 2 + 1) * p;
        l = (l + 1) * p;
    }
    printf("%lf\n", ans);
    return 0;
}

```


---

