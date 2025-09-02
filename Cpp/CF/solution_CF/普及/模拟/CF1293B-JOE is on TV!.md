# JOE is on TV!

## 题目描述

[3R2 - Standby for Action](https://www.youtube.com/watch?v=P2ZVC9aoiKo)



Our dear Cafe's owner, JOE Miller, will soon take part in a new game TV-show "1 vs. $ n $ "!

The game goes in rounds, where in each round the host asks JOE and his opponents a common question. All participants failing to answer are eliminated. The show ends when only JOE remains (we assume that JOE never answers a question wrong!).

For each question JOE answers, if there are $ s $ ( $ s > 0 $ ) opponents remaining and $ t $ ( $ 0 \le t \le s $ ) of them make a mistake on it, JOE receives $ \displaystyle\frac{t}{s} $ dollars, and consequently there will be $ s - t $ opponents left for the next question.

JOE wonders what is the maximum possible reward he can receive in the best possible scenario. Yet he has little time before show starts, so can you help him answering it instead?

## 说明/提示

In the second example, the best scenario would be: one contestant fails at the first question, the other fails at the next one. The total reward will be $ \displaystyle \frac{1}{2} + \frac{1}{1} = 1.5 $ dollars.

## 样例 #1

### 输入

```
1```

### 输出

```
1.000000000000```

## 样例 #2

### 输入

```
2```

### 输出

```
1.500000000000```

# 题解

## 作者：Meatherm (赞：4)

$n \leq 2$ 的情况似乎看不出什么有用的结论。

当 $n=3$ 的时候，我们可以选择 $\frac 13+\frac12+\frac 11$，也可以选择 $\frac 23 + \frac 11$，还可以选择 $\frac 3 3$。

当 $n=4$ 的时候，我们可以选择 $\frac 14+\frac 13+\frac 12+\frac 11$，很显然找不到比这个更优的。

所以经过打表找规律，我们得到了一个结论：答案就是 $\sum_{i=1}^{n} \frac 1 i$。

```cpp
# include <bits/stdc++.h>
# define rr register
 
int n;
double ans;
 
int main(void){
	std::cin>>n;
	for(rr int i=1;i<=n;++i){
		ans+=(1.00/(double)(i));
	}	
	printf("%.7lf",ans);
	return 0;
}
```

似乎有人会问我的代码连样例都过不去。没事的，Codeforces 有 Special Judge，输出 7 位小数也没问题。

---

## 作者：寒鸽儿 (赞：2)

大胆猜想,不用证明  
结合样例猜测  
每次淘汰一个人比较合理  
不放心可以打个表验证一下  
```cpp
#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int n;
	double ans = 0;
	cin >> n;
	for(int i = 1; i <= n; ++i) ans += (double)1 / i;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：gyh20 (赞：1)

前面两篇题解都没有证明，我来补一点证明吧。

当剩下$i$个人时，无论选走多少个人，每一个人的贡献都为$1/i$，可如果将这个人留到下一轮，他的贡献至少为$1/i-1$，$1/i-1>1/i$，所以每轮只选一个人是最优的。答案即为$1/1+1/2+1/3......1/n$。

这道题比第一题简单多了(第一题我还错了一遍)

代码:
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define re register
using namespace std;
int t,n,a,b,c;
double ans;
signed main(){
scanf("%d",&n);
for(re int i=1;i<=n;++i)ans+=(double)1/i;
printf("%.10lf",ans);
	}
```


---

## 作者：icefake (赞：1)

这道题，除了看不懂(嘤语)以外，其他的都很容易理解，所以嘤语dalao们都可以秒杀这道题了。

下面我们直接开始这道题最难的一步！！！

## 翻译 <----max difficult

> JOE是一个人，他上电视了~~好像大概似乎差不多是这么说的吧~~，参加一个类似于以一敌百的节目~~China诗词大会~~，假设他很强，这世界上就没有他不会的题，所以他可以答对所有的题。
> 这个节目有 $n$ ( $s > 0s>0$ ) 个人(不包括JOE)参加，有若干个回合，每回合开始场上还剩 $s$ 人，有 $t$ ( $0≤t≤s$ ) 个人答错淘汰，则这个回合JOE获得的收益为 $\displaystyle\frac{t}{s}$ ，求JOE所有回合总收益的最大值。

 好吧，翻译得有点长~~废话~~
 
 结束了最难的环节，就到了miaoT的时候了。。。逃)
 
 (归位。。。
 
 ## 推算ing
 首先我们很容易想到最大值 $W = \displaystyle\frac{1}{1} + \displaystyle\frac{1}{2} + …… + \displaystyle\frac{1}{n - 1} + \displaystyle\frac{1}{n}$
 没错——我想到就提交了，但才想起写tijie要证明。。。
 
 ## 证明：
 假设第 $i$ 回合所淘汰的人 $s_i > 1$ 
 
 那么必定可以从 $s_i$ 中分出一个 1 到下一回合
 
 则造成的收益就由 $\displaystyle\frac{s}{t}$
 
 变成了 $\displaystyle\frac{s - 1}{t} + \displaystyle\frac{1}{t - 1}$
 
 相减就可以很容易地比较出大小了~~显然~~
 
 证毕。 <----膜仿某位数学dalao的证明题结尾
 
 终于可以贴蒟蒻的代码了。。。
 
 ## 代码
 
```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
int n;
double ans;
 
template <typename T>
inline T
read()
{
  T sum = 0, fl = 1;
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') fl = -1;
  for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
  return sum * fl;
}//快读。。。
 
signed main()
{
	n = read<int>();
	while(n --) {
		ans += (double)1 / (n + 1);
	}
	printf("%.5f", ans);
	return 0^0;
}

```

---

## 作者：FZzzz (赞：1)

~~一道挺好的高中学考难度证明题。~~

------------
可以秒出一个性质：每次搞掉一个人是最优的。

~~因为调和级数发散。~~

下面用归纳法证明：

首先显然 $n=1$ 时命题成立。

假设 $n\le k-1$ 时命题成立，当 $n=k$ 时：

若有 $t$ 人回答错误，则这一轮可以获得 $\frac{t}{k}$ 元，在这一轮之后，根据归纳法，最优是 $\sum\limits_{i=1}^{k-t}\frac{1}{i}$ 元，共 $\frac{t}{k}+\sum\limits_{i=1}^{k-t}\frac{1}{i}$。

当 $t+1$ 人回答错误时，共可以获得 $\frac{t+1}{k}+\sum\limits_{i=1}^{k-t-1}$ 元。

然后上两式作差，得到 $\frac{t}{k}-\frac{t+1}{k}+\frac{1}{k-t}=\frac{t}{k(k-t)}$。

而 $1\le t<k$，故该式为正。

这就说明淘汰 $t$ 人优于 $t+1$ 人，故 $t=1$ 时最优。

根据归纳法，命题得证。

---

## 作者：ix35 (赞：0)

## CF 1293 B：JOE is on TV

题意非常简洁，不难想到两种思路：

**算法一：动态规划**

~~我一开始就这么想的。~~

设 $dp(i)$ 表示 $n=i$ 时的答案，枚举最后一次干掉 $j$ 人，则 $dp(j)+\dfrac{j}{i}\to dp(i)$，所以：

$$dp(i)=\max\limits_{j\in [1,i-1]}(dp(j)+\dfrac{j}{i})$$

但是这个东西也不太方便优化（实际上优化可以是决策单调性，~~即推结论~~）

**算法二：结论**

考虑赋予题目要求的值一个意义：给第 $i$ 个人一个权值 $\dfrac{1}{x_i}$，其中 $x_i$ 是第 $i$ 个人被干掉之前场上有多少人，那么答案其实就是：

$$\sum\limits_{i=1}^n \dfrac{1}{x_i}$$

不妨设 $x_1\leq x_2\leq \cdots\leq x_n$，那么应该有：

$$x_i\ge i$$

因为 $i$ 在场时显然 $1,2,\cdots,i$ 都在场。

所以要让上面的答案取最大值，$x_i$ 应该越小越好，恰好所有的 $x_i\ge i$ 可同时取等号，所以最值的情形就是 $x_i=i$，即：

$$ans=\sum\limits_{i=1}^n\dfrac{1}{i}$$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {ans+=(double)1.0/(double)i;}
	printf("%lf\n",ans);
	return 0;
}
```


---

## 作者：Mr_Wu (赞：0)

### 题意

玩游戏，当前剩 $s$ 个人，若淘汰掉 $t(0\le t\le s)$ 个人，对答案贡献 $\frac{t}{s}$

现在一开始有 $n$ 个人玩游戏，求答案的最大值

### 题解

把 $\frac{t}{s}$ 拆成 $t$ 个 $\frac{1}{s}$ 相加，观察答案的构成，发现答案是 $\sum\limits_{i=1}^n \frac{1}{a_i}$ 的形式，其中 $a_i=a_{i-1}$ 或 $a_i=n-i+1$。

如 $n=3$，每次砍一个人是 $\frac{1}{3}+\frac{1}{2}+\frac{1}{1}$，先砍两个人是 $\frac{2}{3}+\frac{1}{1}=\frac{1}{3}+\frac{1}{3}+\frac{1}{1}$。

很明显每次只砍一个人最优啦。。

### 代码

Language: GNU C11

```cpp
n,i;double s;main(){scanf("%d",&n);for(i=1;i<=n;++i)s+=1.0/i;return printf("%.6lf\n",s),0;}
```

---

