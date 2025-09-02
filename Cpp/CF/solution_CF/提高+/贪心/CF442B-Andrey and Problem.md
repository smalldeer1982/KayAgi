# Andrey and Problem

## 题目描述

Andrey needs one more problem to conduct a programming contest. He has $ n $ friends who are always willing to help. He can ask some of them to come up with a contest problem. Andrey knows one value for each of his fiends — the probability that this friend will come up with a problem if Andrey asks him.

Help Andrey choose people to ask. As he needs only one problem, Andrey is going to be really upset if no one comes up with a problem or if he gets more than one problem from his friends. You need to choose such a set of people that maximizes the chances of Andrey not getting upset.

## 说明/提示

In the first sample the best strategy for Andrey is to ask only one of his friends, the most reliable one.

In the second sample the best strategy for Andrey is to ask all of his friends to come up with a problem. Then the probability that he will get exactly one problem is $ 0.1·0.8+0.9·0.2=0.26 $ .

## 样例 #1

### 输入

```
4
0.1 0.2 0.3 0.8
```

### 输出

```
0.800000000000
```

## 样例 #2

### 输入

```
2
0.1 0.2
```

### 输出

```
0.260000000000
```

# 题解

## 作者：da32s1da (赞：7)

我们设现在答案是$x$，之前加入的人答对概率为$\ p_1\cdots p_k\ $,现在要加入的人答对概率为$y$。考虑答案变成多少

$$x(1-y)+y\prod_{i=1}^k(1-p_i)$$

- 回答错误，则前面回答正确，是$\ x(1-y)$
- 回答正确，则前面全回答错误，是$y\prod_{i=1}^k(1-p_i)$

化简一下式子

$\text{原式}=x+y\times (\ \prod_{i=1}^k(1-p_i)-x\ )$

前面选的人固定，则$\ x\ $和$\ \prod_{i=1}^k(1-p_i)-x\ $都是定值，那么就要令$\ y\ $最大。

于是把$\ y\ $排序，从大到小扫一遍即可。
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=105;
typedef double D;
const D eps=1e-15;
D a[N],Ans,x=1.0;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--){
		if(x-Ans>-eps)Ans+=(x-Ans)*a[i];
		else break;
		x*=(1-a[i]);
	}
	printf("%.12f\n",Ans);
}
```

---

## 作者：DennyQi (赞：3)

> 有$n$个人，第$i$个人有$a_i$的概率同意，$1-a_i$的概率不同意。问怎么选择一些人，使得只有一人同意的概率最大。

假设我们已经选择了一个集合$S$，则概率为$\sum\limits_{i \in S}[\dfrac{a_i}{1-a_i}\prod\limits_{j \in S}(1-a_j)]$。令$B=\prod\limits_{i \in S}(1-a_i)$，$S=\sum\limits_{i \in S}\dfrac{a_i}{1-a_i}$。则概率为$SB$。

现在考虑加入一个$a_k$，那么考虑答案的变化量$\Delta=(S+\dfrac{a_k}{1-a_k}) \cdot B \cdot (1-a_k)-SB=B(1-S)a_k$。因此只要满足$S<1$，那么选择$a_k$答案就会变大。

那么接下来考虑怎么选择。如果我们贪心地来考虑，那么显然选择最大的$a_k$会最优，这样我们对$a_k$排序从大到小选择直到$S \geq 1$为止，复杂度$O(n \log n)$。

为什么可以贪心，可以用反证法证明。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
const int N = 110;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n;
double a[N],B,S,ans;
int main(){
	// freopen("file.in","r",stdin);
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		scanf("%lf",a+i);
	}
	std::sort(a+1,a+n+1);
	B = 1.000 - a[n];
	S = a[n] / (1 - a[n]);
	ans = a[n];
	for(int i = n-1; i >= 1; --i){
		if(1 - S > 1e-10){
			ans += B * a[i] * (1-S);
			B *= 1 - a[i];
			S += a[i] / (1 - a[i]);
		}
	}
	printf("%.12f\n",ans);
	return 0;
}
```

---

## 作者：山田リョウ (赞：2)

假设现在选了 $m$ 个朋友，分别是 $a_1,a_2,a_3,...,a_m$，令 $res=\sum\limits_{i=1}^n\prod\limits_{j\ne i}p_{a_j}$，$pro=\prod\limits_{i=1}^np_{a_j}$。

如果此时再加入第 $k$ 个朋友，那么现在的概率应该变成了 $(1-p_k)res+p_k\cdot pro=res+p_k(res-pro)$，所以如果 $res-pro>0$ 就应该选择加，而且应该让 $p_k$ 尽可能大，不然就不加。

所以考虑按照 $p$ 从大到小排序，不断的加入，加到 $res>pro$ 为止。

时间复杂度 $O(n\log n)$。

code:
```cpp
// Problem: CF442B Andrey and Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF442B
// Memory Limit: 250 MB
// Time Limit: 2000 ms

#include<stdio.h>
#include<algorithm>
#include<functional>
double p[101];int n;
const double eps=1e-9;
int main(){
	double res=0,pro=1;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf",p+i);
	std::sort(p+1,p+n+1,std::greater<double>());
	for(int i=1;i<=n;++i){
		if((pro-res)<eps)break;
		res+=(pro-res)*p[i],pro*=(1-p[i]);
	}
	printf("%.9lf",res);
	return 0;
}
```

---

## 作者：王熙文 (赞：1)

# CF442B 题解

## 思路

首先特判一下如果某个 $p_i=1$ 则直接输出 $1$ 即可（防止下面除数为 $0$）。

结论：**答案为将 $p$ 从大到小排序后的所有前缀的概率最大值。**

证明：

假设选了 $k$ 个朋友，做出题的概率为 $p_1,p_2,\cdots,p_k$，那么做出恰好一道题的概率为：

$$\sum_{i=1}^k p_i\prod_{j \not= i}(1-p_j)=\prod_{j=1}^k (1-p_j)\sum_{i=1}^k \dfrac{p_i}{1-p_i}$$

设 $P=\prod\limits_{j=1}^k (1-p_j),S=\sum\limits_{i=1}^k \dfrac{p_i}{1-p_i}$，则概率为 $PS$。

首先，让我们看一下加入一个概率为 $p_k$ 的人后，概率会有什么变化。

$$\Delta = P\cdot (1-p_k) \cdot (S+\dfrac{p_k}{1-p_k})-PS$$

$$=P \cdot (1-p_k) \cdot \dfrac{S-Sp_k + p_k}{1-p_k}-PS=PS+Pp_k(1-S)-PS=Pp_k(1-S)$$

因为 $P,p_k \ge 0$，所以当 $S<1$ 时，$\Delta > 0$，即更优。

这样我们可以发现一个性质：**随着加入的人越来越多，概率先增后减。因此当概率变小的时候，我们就不用考虑剩下的了。**

则现在只需要考虑所有 $S-\dfrac{\min_p}{1-\min_p}<1$ 的方案（为什么是 $\min_p$ 呢？因为一个好的方案一定任意顺序都满足 $\Delta > 0$，而 $\dfrac{\min_p}{1-\min_p}$ 是所有 $p$ 中的最小值，所以满足了这个不等式，则任意顺序都满足 $\Delta > 0$）。

接下来使用调整法（？）证明。**考虑证明对于任意排序后不是前缀，且 $S-\dfrac{\min_p}{1-\min_p}<1$ 的方案，将最小值换成一个比它大的值 $x$（因为不是前缀所以一定存在），概率一定更大。**如果证明了这个，则调整到最后选择的一定是排序后的一个前缀。

将 $\min_p$ 换成 $x$ 的概率是：

$$\dfrac{P(1-x)}{1-\min_p} \cdot (S-\dfrac{\min_p}{1-\min_p}+\dfrac{x}{1-x})$$

$$=\dfrac{P(1-x)}{1-\min_p} \cdot \dfrac{S(1-\min_p)(1-x)-\min_p(1-x) + (1-\min_p)x}{(1-\min_p)(1-x)}$$

$$=\dfrac{P(1-x)}{1-\min_p} \cdot \dfrac{S(1-\min_p)(1-x) + x - \min_p}{(1-\min_p)(1-x)}$$

$$=\dfrac{P(S(1-\min_p)(1-x)+x-\min_p)}{(1-\min_p)^2}$$

现在考虑 $S(1-\min_p)(1-x)+x-\min_p$ 与 $S(1-\min_p)^2$ 的大小关系。作差：

$$\Delta = S(1-\text{min}_p)(1-x)+x-\text{min}_p - S(1-\text{min}_p)^2$$

$$=S(1-\text{min}_p)(1-x-1+\text{min}_p) + x - \text{min}_p$$

$$=S(1-\text{min}_p)(\text{min}_p-x)-(\text{min}_p-x)$$

$$=(S(1-\text{min}_p)-1)(\text{min}_p-x)$$

现在回顾当前方案的性质：$S-\dfrac{\min_p}{1-\min_p}<1$，转化一下变成：$S(1-\min_p) < 1$。

这样原式左边 $S(1-\min_p)-1 < 0$，又因为 $\min_p -x < 0$，所以 $\Delta > 0$，因此 $S(1-\min_p)(1-x)+x-\min_p > S(1-\min_p)^2$。

这样原式 $> \dfrac{PS(1-\min_p)^2}{(1-\min_p)^2}=PS$

这样我们就证明了调整后概率更大。也证明了最初的结论：答案为将 $p$ 从大到小排序后的所有前缀的概率最大值。根据这个结论，排序后直接算即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; double p[110];
int main()
{
	cin>>n;
	for(int i=1; i<=n; ++i)
	{
		cin>>p[i];
		if(p[i]==1) return printf("%.10f",1.0),0;
	}
	sort(p+1,p+n+1,greater<double>());
	double P=1,S=0;
	for(int i=1; i<=n; ++i)
	{
		P*=1-p[i],S+=p[i]/(1-p[i]);
		if(S>=1) return printf("%.10f",P*S),0;
	}
	printf("%.10f",P*S);
	return 0;
}
```



---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF442B)

首先直观上来看肯定应该先选最大的。

考虑前面选的 $k$ 个数答案为 $x$，前面选的 $k$ 个数概率分别为 $p_1,p_2,…,p_k$，当前选的这个数概率为 $y$。

那么答案就会变成 $x(1-y)+y\prod\limits_{i=1}^k(1-p_i)$，即 $x+y(\prod\limits_{i=1}^k(1-p_i)-x)$。

那么这个答案比 $x$ 大当且仅当 $\prod\limits_{i=1}^k(1-p_i)>x$。

然后每次选的 $y$ 越大，答案加得越多，$\prod\limits_{i=1}^k(1-p_i)$ 变得越小。所以显然应该把 $y$ 从大到小排序然后依次加。

---

## 作者：_edge_ (赞：0)

假设我们选择了的是 $p_1,p_2,p_3, \dots,p_n$，那么计算其贡献即为 $\sum \limits _{i=1}^n p_i \times \dfrac{\prod \limits _{j=1}^{n} (1-p_j)}{1-p_i}$。

然后会发现这东西整理一下变成了 $\prod \limits _{j=1}^{n} (1-p_j) \times (\sum \limits _{i=1}^n \dfrac{p_i}{1-p_i})$，观察一下会发现前者下降的更快一些，于是我们有一种新的乱搞做法，先随机一个排列再从前往后搞。

然后会发现，这东西，错误的概率非常非常高。

这咋办，难不成就直接放弃这题？不！我们用人类的智慧搞，随机既然不够优秀我们就用排序的方式来代替一部分随机方式。

猜猜的话前者应该缩小的更快一些，同时观察样例可以大致明白，对于 $p_i$ 比较大的就可以放前面，然后会发现，这东西挺对的 (确信。

好像没有严谨的证明，但是如果遇到这种题的话建议两种从小到大从大到小都试试，反正这范围才 $100$，过不去也没啥损失。

[代码](https://codeforces.com/contest/442/submission/176413708)



---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF442B) & [原题链接](http://codeforces.com/problemset/problem/442/B)

概率论 & 递推 & 排序。

感谢[Engulf](https://www.luogu.com.cn/user/482728)提出错误，CF 评测未有这个问题，已改正。

---

**题意**

现有 $n$ 道题，给出答对的概率。你可从中选题，使得恰好答对一题的概率最大。

---

**解题**

设第 $i$ 道题及前面的题恰好答对 $1$ 题的概率是 $f_i$，第 $i$ 道题的概率是 $p_i$。

$f_i$ 分两种情况讨论：
1. 前面有 $1$ 题答对，则概率为 $f_{i-1}\times (1-p_i)$。
2. 前面全答错，则概率为 $p_i\prod_{o=1}^{i-1}(1-p_o)$

则有：
$$f_i=f_{i-1}\times (1-p_i)+p_i\prod_{o=1}^{i-1}(1-p_o)$$
把第一种情况拆括号，得：
$$f_i=f_{i-1}-f_{i-1}\times p_i+p_i\prod_{o=1}^{i-1}(1-p_o)$$
逆运用乘法分配律，得：
$$f_i=f_{i-1}+p_i(\prod_{o=1}^{i-1}(1-p_o)-f_{i-1})$$
容易看出， $f_{i-1}$、$p_i$、$f_{i-1}$ 都为定值。（**注意这里 $p_i$ 为定值，因为无论如何交换顺序都还是要乘上 $p_i$**）

但是，我们还可以通过修改 $p_i$ 的顺序来使得 $\prod_{o=1}^{i-1}(1-p_o)$ 最大，则下一步的 $f_{i-1}$ 最小（**注意目光要长远些**）。换句话说，就是让 $p_i$ 尽量大，所以从大到小即可。

同时要注意 $1-p_o$ 要是正数，否则 $\prod_{o=1}^{i-1}(1-p_o)$ 是负数就很小了。

---

**代码**

这里的保留小数没有用方便的 `C` 语言写法，用了 `C++` 写法。（支持 `C++` ！！！）

```cpp
#include<bits/stdc++.h>
using namespace std;
double n,p[101],ans,cuo=1;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	sort(p+1,p+int(n)+1);
	for(int i=n;i>=1;cuo*=(1-p[i]),i--)
		ans+=(cuo-ans)*p[i];
	cout<<setprecision(12)<<fixed<<ans<<endl;
	return 0;
}
```

---

