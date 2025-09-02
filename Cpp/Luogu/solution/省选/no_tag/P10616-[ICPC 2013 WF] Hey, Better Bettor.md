# [ICPC 2013 WF] Hey, Better Bettor

## 题目描述

> “在赌场里，首要规则是让他们继续玩，让他们不断回来。他们玩得越久，输得越多，最终，我们会赢得一切。”  
> （摘自 1995 年电影《赌场》）

最近的经济衰退对包括赌博业在内的娱乐场所并不友好。赌场之间竞争激烈，以吸引有钱的玩家，一些赌场开始提供特别优厚的优惠。其中一个赌场提供以下优惠：你可以在赌场里随意赌博。当你结束时，如果你比开始时输了任何金额，赌场将退还你损失的 $x\%$。显然，如果你赢钱了，你可以保留所有的奖金。此优惠没有时间限制或金额限制，但你只能兑现一次。

为了简化，假设所有赌注的成本为 $1$ 美元，并支付 $2$ 美元。现在假设 $x$ 是 $20$。如果你在退出前总共下注 $10$ 次，只有 $3$ 次获胜，你的总损失是 $3.2$ 美元。如果 $6$ 次获胜，你就赚了 $2$ 美元。

给定 $x$ 和赢得任何单个赌注的概率百分比 $p$，编写一个程序来确定你在这个赌场下注所能获得的最大期望利润，使用任何赌博策略。

输入由一个单一的测试用例组成。测试用例包含退款百分比 $x (0 \leq x < 100)$，随后是赢得概率百分比 $p (0 \leq p < 50)$。$x$ 和 $p$ 的小数点后最多有两位数字。

显示最大期望利润，绝对误差不超过 $10^{-3}$。

## 样例 #1

### 输入

```
0 49.9```

### 输出

```
0.0```

## 样例 #2

### 输入

```
50 49.85```

### 输出

```
7.10178453```

# 题解

## 作者：donghanwen1225 (赞：1)

高考结束了，来复健 OI。

------------

首先考虑赌博的策略。容易发现我们的策略就是当我们赚到 or 亏到一定钱数时，选择继续拼还是及时止损。

因此，设及时收手的边界为 $r$、及时止损的边界为 $-l$，以 $P$ 表示最后走到 $r$ 的概率，那么所求的期望就等于 $Pr-(1-x)(1-P)l$。

我们需要分析 $P$ 和 $l,r$ 之间的关系。不妨把下标都加上 $l$，记 $p_i\;(0\leq i\leq l+r)$ 表示当前正位于 $i$，最终走到 $l+r$ 的概率，那么有 $p_0=0,p_{l+r}=1$，所求的 $P=p_l$。

接下来建立递推关系。若当前位于位置 $k$，则有 $p$ 的概率走到 $k+1$、有 $1-p$ 的概率走到 $k-1$。于是可以写出 $p_k=pp_{k+1}+(1-p)p_{k-1}$。

对以上这个方程组，我们发现在边界上有 $p_{1}=pp_2$，如果反复将其代入后续的式子，可以消成一个单纯的比例关系式。这意味着我们可以用数学方法求出其通解。具体的，若已求出 $p_k=f(k)p_{k+1}$，就可以代入 $p_{k+1}=pp_{k+2}+(1-p)p_k$ 而解出 $p_{k+1}=\dfrac{p}{1-(1-p)f(k)}p_{k+2}$。

于是有 $f(k+1)=\dfrac{p}{1-(1-p)f(k)}$，且 $f(1)=p$。利用高中数学知识，可以解出 $f(n)=\dfrac{p((1-p)^n-p^n)}{(1-p)^{n+1}-p^{n+1}}$，从而 $p_l=f(l)f(l+1)\cdots f(l+r-1)p_{l+r}=\dfrac{(1-p)^l-p^l}{(1-p)^{l+r}-p^{l+r}}p^r$。

记 $u=\dfrac{p}{1-p}$，有上面的 $P=p_l=\dfrac{u^r-u^{l+r}}{1-u^{l+r}}$。从而最终的期望 $Pr-(1-x)(1-P)l=\dfrac{u^r-u^{l+r}}{1-u^{l+r}}r-(1-x)\dfrac{1-u^r}{1-u^{l+r}}l$。

现在，我们的目标就是通过调整 $l,r$ 确定上式的最大值。我们可以感性理解：如果 $l$ 过小，那么不够大胆，收益不大；如果 $l$ 过大，那么止损不及时，收益也不大：也就是说这个函数应当关于 $l$ 是单峰的。同理也应当关于 $r$ 单峰。那么就可以通过三分逐步找到所求的最大期望。

一些可能的细节：

1. $l,r$ 与准确值偏移太大时，求出的期望过小，可能由于浮点数误差而导致出错。为了方便，我们可以枚举 $r$、三分 $l$，来规避误差的影响。

2. 由于题中的 $x,p$ 均最多有小数点后 $2$ 位，最极限的情况就是 $99.99\;49.99$。据此，可以预先找到 $l,r$ 的上界。实测 $2.5\times10^4$ 即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
double x,p,u,pw[50005];
double v(int l,int r)
{
	double n1=pw[r],n2=pw[l+r];
	return (n1-n2)/(1-n2)*r-(1-x)*(1-n1)/(1-n2)*l;
}
double cal(int rr)
{
	double ans=0;int l=1,r=25000;
	while(r-l>=4)
	{
		int m1=l+(r-l)/3,m2=r-(r-l)/3;
		double r1=v(m1,rr),r2=v(m2,rr);
		if(r1>r2) r=m2;
		else l=m1;
	}
	for(int i=l;i<=r;i++) ans=max(ans,v(i,rr));
	return ans;
}
int main()
{
	scanf("%lf%lf",&x,&p);
	x/=100;p/=100;u=p/(1-p);
	pw[0]=1;for(int i=1;i<=50000;i++) pw[i]=pw[i-1]*u;
	double ans=0;
	for(int i=1;i<=25000;i++) ans=max(ans,cal(i));
	printf("%.12lf\n",ans);
	return 0;
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10616)
## 思路
先令 $x\gets x\%,p\gets p\%$。

考虑设置初始时可使用 $l$ 美元以及赚得 $r$ 美元时收手来最大化最终期望（只要还有钱就继续）。设赚到 $r$ 元的概率为 $P$，期望即为 $Pr-(1-x)(1-P)l$。

设有 $k$ 美元时赚到 $r$ 美元的概率为 $t_k$，那么 $P=t_l$。由于赢的概率为 $p$，因此 $t_i=pt_{i+1}+(1-p)t_{i-1}$。那么对于 $t_0$（下界）则有 $t_0=pt_1$，将其代入 $t_1=pt_2+(1-p)t_0$ 可得 $t_1=pt_2+(1-p)pt_0$，也就是 $t_2=\dfrac{1-(1-p)p}{p}t_1$，这样一直代入下去容易得到 $t_{i+1}=\dfrac{(1-p)^{i+1}-p^{i+1}}{p((1-p)^i-p^i)}t_i$。由此可以进一步推得 $P=t_l=\dfrac{p^r((1-p)^l-p^l)}{(1-p)^{l+r}-p^{l+r}}$。

记 $k=\dfrac{p}{1-p}$，则 $P=\dfrac{k^r-k^{l+r}}{1-k^{l+r}}$。那么 $ans=Pr-(1-x)(1-P)l=\dfrac{k^r-k^{l+r}}{1-k^{l+r}}r-(1-x)(1-\dfrac{k^r-k^{l+r}}{1-k^{l+r}})l$，猜测 $ans$ 对于 $l,r$ 单峰，那么可以枚举 $r$ 并三分 $l$ 找到峰值。

可以开 `long double` 以提升精度。并且由于 $x,p$ 均有上界，所以可以先提前算出 $l,r$ 的上界以提升二分速度，上界大概是 $2.5\times 10^4$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2.5e4+5;
long double p,x,k,ans;
long double mi[2*N];
long double js(int a,int b) {
	return (mi[b]-mi[a+b])/(1.0-mi[a+b])*b*1.0-(1.0-x)*(1.0-mi[b])/(1.0-mi[a+b])*a*1.0;
}
long double sol(int r) {
	long double res=0;
	int lft=1,rgt=N-1;
	while(lft<=rgt-3) {//三分
		int mid1=(lft*2+rgt)/3,mid2=(lft+rgt*2)/3;
		long double res1=js(mid1,r),res2=js(mid2,r);
		if(res1<=res2) lft=mid1,res=res2;
		else rgt=mid2,res=res1;
	}
	return res;
}
int main() {
	cin>>x>>p;
	x/=100.0,p/=100.0;
	k=p*1.0/(1-p);
	mi[0]=1;
	for(int i=1;i<2*N;i++) mi[i]=mi[i-1]*k*1.0;
	for(int i=1;i<=N;i++) ans=max(ans,sol(i));
	printf("%.8Lf",ans);
}
```

---

