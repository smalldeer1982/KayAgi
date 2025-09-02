# [ABC126C] Dice and Coin

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc126/tasks/abc126_c

すぬけ君は $ 1 $ 〜 $ N $ の整数が等確率で出る $ N $ 面サイコロと表と裏が等確率で出るコインを持っています。すぬけ君は、このサイコロとコインを使って今から次のようなゲームをします。

1. まず、サイコロを $ 1 $ 回振り、出た目を現在の得点とする。
2. 得点が $ 1 $ 以上 $ K-1 $ 以下である限り、すぬけ君はコインを振り続ける。表が出たら得点は $ 2 $ 倍になり、裏が出たら得点は $ 0 $ になる。
3. 得点が $ 0 $ になった、もしくは $ K $ 以上になった時点でゲームが終了する。このとき、得点が $ K $ 以上である場合すぬけ君の勝ち、 $ 0 $ である場合すぬけ君の負けである。

$ N $ と $ K $ が与えられるので、このゲームですぬけ君が勝つ確率を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ 1\ <\ =\ K\ <\ =\ 10^5 $
- 入力はすべて整数

### Sample Explanation 1

\- サイコロの出た目が $ 1 $ のとき、得点が $ 10 $ 以上になるためには、 $ 4 $ 回コインを振って $ 4 $ 連続で表が出る必要があります。この確率は、 $ \frac{1}{3}\ \times\ (\frac{1}{2})^4\ =\ \frac{1}{48} $ です。 - サイコロの出た目が $ 2 $ のとき、得点が $ 10 $ 以上になるためには、 $ 3 $ 回コインを振って $ 3 $ 連続で表が出る必要があります。この確率は、 $ \frac{1}{3}\ \times\ (\frac{1}{2})^3\ =\ \frac{1}{24} $ です。 - サイコロの出た目が $ 3 $ のとき、得点が $ 10 $ 以上になるためには、 $ 2 $ 回コインを振って $ 2 $ 連続で表が出る必要があります。この確率は、 $ \frac{1}{3}\ \times\ (\frac{1}{2})^2\ =\ \frac{1}{12} $ です。 よって、すぬけ君が勝つ確率は、 $ \frac{1}{48}\ +\ \frac{1}{24}\ +\ \frac{1}{12}\ =\ \frac{7}{48}\ \simeq\ 0.1458333333 $ です。

## 样例 #1

### 输入

```
3 10```

### 输出

```
0.145833333333```

## 样例 #2

### 输入

```
100000 5```

### 输出

```
0.999973749998```

# 题解

## 作者：阿丑 (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT4740)

---

题目大意：

* 你会以相同的几率得到一个在 $1$ 到 $n$ 之间的正整数。

* 当这个数在 $[1, k-1]$ 时，它有 $\dfrac 1 2$ 的几率翻倍；有 $\dfrac 1 2$ 的几率归零；对得到的新数重复这一步骤。

* 若最后这个数大于等于 $k$ 则获胜。求获胜的概率。

* $n$、$k \le 10^5$。

注意到本题范围：$n \le 10^5$，这对于数学题来说是比较小的，可以考虑暴力求解。

思路：

1. 对每一个 $1$ 到 $n$ 之间的数分别求概率。

2. 通过模拟来求得每个数最后大于等于 $k$ 的概率。

---

#### 模拟部分：

~~如果这部分看不懂，直接看代码就好了。~~

设 $x$ 最终大于等于 $k$ 的几率为 $P(x)$。

设当前数为 $j$，那么这个数有 $\dfrac 1 2$ 的几率增加至 $2j$，有 $\dfrac 1 2$ 的几率变成 $0$。即 $P(j)=\dfrac 1 2P(2j)+\dfrac 1 2P(0)$。

而若得到 $0$，则直接失败，即 $P(0)=0$。

故 $P(j)=\dfrac 1 2P(2j)$。

以此类推，$P(2j)=\dfrac 1 2P(4j)$，$P(4j)=\dfrac 1 2P(8j)$ $\text{……}$如图。

![图](https://z3.ax1x.com/2021/05/13/gDAeXV.png)

即 $P(j)=\dfrac 1 {2^m} P(2^mj)$，直到 $2^mj \ge k$，此时有 $P(2^mj)=1$。

代码：

```cpp
double p=1;
while(j<k) {
	j*=2;	//j 变为 2j
	p/=2;	//乘上 1/2
}
ans+=p/n;	//由于只有 1/n 的几率得到 j，所以要除以 n
```

复杂度证明：

由于开始时得到的 $j \ge 1$，而 $j\ge k$ 时 `while` 就会终止，每次将翻倍，故 `while` 最多执行 $\log k$ 次，时间复杂度 $\Theta(n\log k)$。

---

主体部分已经有了，完整代码就不给出了（

---

## 作者：xgwpp6710 (赞：2)

这题思路很好想，就是一个个枚举色子的初始值获胜的概率，最后将所有概率相加。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
double n,k,p;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int i0=i;
		if(i>=k) p+=1/n;//直接获胜，注意每个初始值的概率都是1/n
		else
		{
			double p0=1/n;
			while(i0<k)
			{
				i0*=2;
				p0/=2;//既然赢得方法只能靠不停翻倍，那么我们就看一共需要翻几次倍才能赢，每需要翻一次概率减半
			}
			p+=p0;
		}
	}
	printf("%.12lf",p);
	return 0;
}
```

---

## 作者：LJKX (赞：0)

## 思路 
直接枚举 $1\sim n$ 每个数获胜的总概率，最后相加即可。

这个骰子是 $n$ 面的，所以投到每个面的几率是 $\frac1n$，如果这个面的点数 $≥n$，这个面的概率 $P$ 就是 $\frac1n$， 反之这个点数不断 $\times2$，$P$ 也一直 $\times \frac1 2$ 直到这个点数 $≥n$。

~~虽然写的很烂，但是~~看了代码应该更好理解了吧。
## Code
```cpp
#include<cstdio>
int n,k,m;
double ans;//总概率
int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {//枚举每一个数
        double sum=1.0/n;//sum记录当前i的获胜概率，初始为(1/n)
        m=i;
        while(m<k) m*=2,sum/=2.0;//如果m<k,m就有(1/2)的几率翻倍，同时sum也将除以2
        ans+=sum;
    }
    printf("%.12lf\n",ans);
    return 0;
}
```


---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4740)

首先要**注意这个骰子是 $n$ 面的**，不要想错了。所以每一个面都有 $\dfrac{1}{n}$ 的概率选到，用 `for` 枚举。

因为每一次只能投到正面，反面就输了。所以每一次概率都 $\times \dfrac{1}{2}$ 即可。

时间复杂度 $O(n\log k)$

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
int n,k;
double ans;
int main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        double cnt=1.0/n;
        int h=i;
        while(h<k){
            h*=2;
            cnt*=0.5;
        }
        ans+=cnt;
    }
    printf("%.12lf",ans);
    return 0;
}
```


---

## 作者：Ciaxin_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT4740)
### 题目
扔**色子和金币**，色子会有 $n$ 个面，而金币会有 $k$ 的价值。

扔**色子**时，分数为色子的大小。当色子的大小在 $\left[1,k-1\right]$ 时扔金币，否则不扔。扔**金币**时，金币朝上，分数翻倍；否则，分数变零。当分数大于等于 $k$ 或 等于 $0$ 时，结束。

##### 总之，就是求分数大于等于 $k$ 时的概率 $P$。

- 色子扔出时的每个面概率 $P$ 相同也就是 $\frac{1}{n}$ 。
- 金币扔出时的概率 $P$ 为 $\frac{1}{2}$ 。（不用过多解释）

那这不就好办了吗！！！


```cpp
#include<bits/stdc++.h>
using namespace std;

double ans,P(int);
int n,k;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		ans+=P(i);
	}
	printf("%.12lf",ans);
	return 0;
}
double P(int x)
{
	double cnt=1.0/n;
	if(x>=k) return cnt;
	while(x<k)
	{
		x*=2;
		cnt/=2;
	}
	return cnt;
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4740)

小学生又双叒叕来写题解啦！

这是一个关于概率的**模拟**问题。

游戏分两步，我们先看第一步。

投色子，显然，投中一个 $[1, n]$ 的数，概率是 $\dfrac{1}{n}$ 没错吧。

那么，我们重点思考第二步。

想获胜的唯一办法是：**一直抛到正面**，直到分数大于等于 $k$ 了。

这就好办了，循环枚举分数什么时候达到目标，每次**分数翻倍，概率减半**。

最后累加一下所有初始值对应的概率即可。



------------


最后一个问题，就是输出。

题目里没有翻译输出格式，然而这很重要。

输出格式告诉我们：当误差不超过十的负九次方时，输出被认为是正确的。

因此，我们保留十位小数就够了。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, k;
double Play(int score)  //参数是初始分数，计算的是赢的概率。 
{
	double ans = 1.0 / n;  //存储概率。
	//总概率应该是投色子的概率。
	while (true)
	{
		if (score >= k) break;
		score *= 2;
		ans /= 2;
	}
	return ans;
}
int main()
{
	double sum = 0;
	scanf("%d%d", &n, &k);
	//接下来要枚举初始分数。 
	for (int sc = 1; sc <= n; sc++) sum += Play(sc);
	printf("%.10lf\n", sum);  //勿忘祖传换行。
	//注意精度。 
	return 0;
}
```


---

