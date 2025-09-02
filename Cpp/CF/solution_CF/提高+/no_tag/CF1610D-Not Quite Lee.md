# Not Quite Lee

## 题目描述

Lee couldn't sleep lately, because he had nightmares. In one of his nightmares (which was about an unbalanced global round), he decided to fight back and propose a problem below (which you should solve) to balance the round, hopefully setting him free from the nightmares.

A non-empty array $ b_1, b_2, \ldots, b_m $ is called good, if there exist $ m $ integer sequences which satisfy the following properties:

- The $ i $ -th sequence consists of $ b_i $ consecutive integers (for example if $ b_i = 3 $ then the $ i $ -th sequence can be $ (-1, 0, 1) $ or $ (-5, -4, -3) $ but not $ (0, -1, 1) $ or $ (1, 2, 3, 4) $ ).
- Assuming the sum of integers in the $ i $ -th sequence is $ sum_i $ , we want $ sum_1 + sum_2 + \ldots + sum_m $ to be equal to $ 0 $ .

You are given an array $ a_1, a_2, \ldots, a_n $ . It has $ 2^n - 1 $ nonempty subsequences. Find how many of them are good.

As this number can be very large, output it modulo $ 10^9 + 7 $ .

An array $ c $ is a subsequence of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

For the first test, two examples of good subsequences are $ [2, 7] $ and $ [2, 2, 4, 7] $ :

For $ b = [2, 7] $ we can use $ (-3, -4) $ as the first sequence and $ (-2, -1, \ldots, 4) $ as the second. Note that subsequence $ [2, 7] $ appears twice in $ [2, 2, 4, 7] $ , so we have to count it twice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1610D/313cb49db5d73c64ca073767762c5a97154eca20.png)Green circles denote $ (-3, -4) $ and orange squares denote $ (-2, -1, \ldots, 4) $ .For $ b = [2, 2, 4, 7] $ the following sequences would satisfy the properties: $ (-1, 0) $ , $ (-3, -2) $ , $ (0, 1, 2, 3) $ and $ (-3, -2, \ldots, 3) $

## 样例 #1

### 输入

```
4
2 2 4 7```

### 输出

```
10```

## 样例 #2

### 输入

```
10
12391240 103904 1000000000 4142834 12039 142035823 1032840 49932183 230194823 984293123```

### 输出

```
996```

# 题解

## 作者：Otomachi_Una_ (赞：7)

一道比较简单的数学题。

## 解题思路
拿到这种问题，我们要思考「好的」数列的本质。

我们假设「好的」构造数列的第 $i$ 个开头是 $x_i$，后面依序是 $x+1,x+2\dots x+b_i-1$。则 $s_i=\dfrac{b_i\times(2x_i+b_i-1)}{2}$。

现在要 $\sum s=0$，即 $\sum b_i\times(2x+b_i-1)=0$，展开就是 $\dfrac{\sum b_i\times(b_i-1)}{2}=-\sum b_ix_i$。

显然等式左边是个常数，由裴蜀定理，可以知道：


$$\gcd b_i|\dfrac{\sum b_i\times(b_i-1)}{2}$$


显然，我们有

$$\gcd b_i|b_i|b_i\times(b_i-1)$$

所以

$$\gcd b_i|\sum b_i\times(b_i-1)$$

所以，我们需要

$$2|\dfrac{\sum b_i\times(b_i-1)}{\gcd b_i}$$

假设 $\gcd b_i=2^t\times (2k+1)$，那么让 $c_i=\dfrac{b_i}{2^t}$，于是会有：

$$2|\dfrac{\sum 2^tc_i\times (2^tc_i-1)}{2^t}$$

$$\therefore 2|\sum c_i\times (2^tc_i-1)······(1)$$

### 情况一、$t=0$

那么 $(1)$ 是显然成立的。

### 情况二、$t\not =0$

那么 $2\not |\ 2^t-1$，$\therefore 2|\sum c_i$。

这也就是「好的」数列的本质。然后就变成了一个极为简单的问题

## 数学知识

在 $n$ 个元素中选取偶数个元素一共 $2^{n-1}$ 中方案。

这是因为假设有一个元素 $A$，选择 $A$ 要在剩下的 $n-1$ 个当中选奇数个，不选择 $A$ 要在剩下的 $n-1$ 个中选择偶数个。结合起来也就是在 $n-1$ 个当中随便选。

## 参考代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define ll long long
const int MR=40;
const int MOD=1e9+7;
int n,a;
int t[MR];
int s=0;
ll ans=0;
int w(int p){
	int cnt=0;
	while(p%2==0){
		cnt++;
		p=p>>1;
	}
	return cnt;
}
ll ksm(ll x,int y){
	ll res=1;
	while(y){
		if(y&1) res=res*x%MOD;
		x=x*x%MOD;
		y=y>>1;
	}
	return res;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		t[w(a)]++;
	}
	for(int i=MR-1;i>=1;i--){
		if(t[i]>=2) ans=(ans+(ksm(2,t[i]-1)-1)*ksm(2,s))%MOD;
		s+=t[i];
	}
	ans=(ans+(ksm(2,t[0])+MOD-1)*ksm(2,s))%MOD;//s^t[0]-1 maybe less then 0
	cout<<ans;
	return 0;
}
```
时间复杂度：$\mathcal{O}(n\log a)$。


## 修正

2022.2.3 修正了口胡的字母错误

---

## 作者：XL4453 (赞：4)

### $\text{Difficulty : 2000}$
---
### 解题思路：

数学题，场上只推出来一半。

对于任意的一个 $a_i$，能表示出来的数都形如：$\dfrac{a_i(2k+a_i-1)}{2}$，也就是 $\dfrac{a_i(a_i-1)}{2}+a_ik$。

题目要求的是所有的这样的值加起来为 $0$，也就是 $\sum_{i=1}^n [\dfrac{a_i(a_i-1)}{2}+a_ik_i]=\sum_{i=1}^n\dfrac{a_i(a_i-1)}{2}+\sum_{i=1}^na_ik_i=0$。

也就是 $\sum_{i=1}^na_ik_i=-\sum_{i=1}^n\dfrac{a_i(a_i-1)}{2}$，其中等式右边是一个常数。

这是一个多元一次不定解方程，根据贝祖定理，有解的条件是 $\gcd(a_i)|\sum_{i=1}^n\dfrac{a_i(a_i-1)}{2}$，负号可以直接去掉。

即：$2|\dfrac{a_i(a_i-1)}{\gcd(a_i)}$。

不妨设 $\gcd(a_i)=2^t(2k-1)$，则每一个数 $a_i$ 都能表示为 $a_i=b_i2^t$。

代入得到：$2|\dfrac{\sum_{i=1}^nb_i2^t(b_i2^t-1)}{2^k(2k-1)}$，提取 $2^t$ 并与分母约分得到：$2|\dfrac{\sum_{i=1}^nb_i(b_i2^t-1)}{2k-1}$。

右边的这个式子还是不好处理，但是可以知道这个式子是由 $\dfrac{a_i(a_i-1)}{\gcd(a_i)}$ 恒等变形而来，而后者显然是一个整数，则 $\dfrac{\sum_{i=1}^nb_i(b_i2^t-1)}{2k-1}$ 同样是一个整数。

左边的 $2$ 提示我们这个式子其实只需要关心右者的奇偶性，而分母 $2k-1$ 是奇数，对奇偶性不产生影响，为了分析方便可以直接去掉。

$\sum_{i=1}^n b_i(b_i2^t-1)$ 依然不好处理，但此时变化的东西就只有 $t$ 了，不妨分情况讨论。

当 $t=0$ 的时候，显然任意的 $b_i(b_i-1)$ 都是偶数，一定成立。

否则，$2\nmid b_i2^t-1$ 一定不产生贡献，也可去掉。

那么就剩下了 $\sum_{i=1}^nb_i$，只需要判断这个的奇偶性就可以了。

---

$t=0$ 的情况发生，且仅发生在选择的数中出现了奇数的时候，放到一起比较麻烦，不妨先把这些奇数排除在外。

然后留下的偶数中，先预处理出一个数中所含有的 $2$，然后枚举 $t$，利用基本的组合数就行了。

设当前被 $2^t$ 除完之后为奇数的数有 $a$ 个，还有多余的 $2$ 的数有 $b$，则方案数为 $2^b\times \sum_{i=2}^nC(a,i)[2|i]$，而 $C(a,i)=C(a-1,i)+C(a-1,i-1)$，带入回去就是 $2^b\times \sum_{i=1}^{n-1}C(a-1,i)=2^b\times (2^{a-1}-1)$。

然后考虑一下奇数，发现其实只要存在奇数就一定都可以，则不妨设奇数的个数为 $a$，偶数有 $b$ 个，答案为 $(2^{a-1}-1)\times2^b$。

---
记得开 $\text{long long}$，并使用快速幂取模。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MOD=1e9+7;
int n,a[200005],t[100],ans,tot;
int calc(int num){
	int cnt=0;
	while(num%2==0){
		num/=2;
		cnt++;
	}
	return cnt;
}
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&a[i]);
		t[calc(a[i])]++;
	}
	for(int i=1;i<=30;i++)tot+=t[i];
	ans=(pow(2,n-tot)-1+MOD)%MOD*pow(2,tot)%MOD;
//	ans=((1<<(n-tot))-1)%MOD*(1<<tot)%MOD;
	for(int i=1;i<=30;i++){
		tot-=t[i];
		if(t[i]<=1)continue;
		ans=(ans+pow(2,tot)%MOD*(pow(2,t[i]-1)-1+MOD)%MOD)%MOD;
//		ans=(ans+(1<<tot)%MOD*((1<<(t[i]-1))-1)%MOD)%MOD;
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：Terraria (赞：3)

谨以此题解纪念我 $3$ 天的努力（

## $\text{Introduction}$

给定一个长度为 $n$ 的数组 $b$，求 $b$ 有多少个子序列，能够以子序列的**每一项**构造出**公差为 $1$ 的等差数列的长度**，使得这些等差数列每个数的和的总和等于 $0$。

## $\text{Solution}$

首先感谢 [Imitators](https://www.luogu.com.cn/user/184069) 大佬的耐心讲解！

假设我们选出了 $m$ 个 $b_i$，构造了 $m$ 个数列 $d_{i,j}$。

我们的目标是：

$$\sum_{i=1}^{m} \bigg (\sum_{j=1}^{b_i} d_{i,j} \bigg)=0$$

根据我们熟知的等差数列求和公式，以上的式子相当于

$$\sum_{i=1}^{m}\dfrac{[d_{i,1}+(d_{i,1}+b_i-1)]\times b_i}{2}=0$$

$$\sum_{i=1}^{m} \dfrac{2d_{i,1}b_i+b_i^2-b_i}{2}=0$$

$$\sum_{i=1}^{m}d_{i,1}b_i+\sum_{i=1}^m\dfrac{b_i(b_i-1)}{2}=0$$

$$\sum_{i=1}^mb_id_{i,1}=-\sum_{i=1}^m\dfrac{b_i(b_i-1)}{2}$$

相当于我们要解一个关于 $b_i,d_{i,1}$ 的方程是否有解。

记 $\gcd(b_1,b_2,\cdots,b_m)=2^tk,2 \nmid k$。

方便起见，记 $r=-\sum\limits_{i=1}^m\dfrac{b_i(b_i-1)}{2}$。

根据裴蜀定理，这个方程若是有解则一定满足 $2^tk \mid r$。

然后再分析，得到

- $k \mid r$ 比较显然，因为右式的 $r$ 只会失去 $2$ 的因子。

- $2^{t-1} \mid r$ 也显然，因为右式的 $b_i$ 只会除以 $2$。

那么现在考虑这样一个 $2^t \parallel b_i$，这样子 $2^{t-1} \parallel\dfrac{b_i(b_i-1)}{2}$。

- 注：$\parallel$ 表示恰好整除，即 $2^t\mid b_i$ 但是 $2^{t+1} \nmid b_i$。

所以，如果想要合法，则一定要求选出来满足 $2^t \parallel b_i$ 的 $b_i$ 的个数为偶数个，否则右式 $2^{t-1} \parallel r$。

---

现在考虑统计答案，记满足 $2^t \parallel b_i$ 的 $i$ 的个数为 $c_i$。

接下来我们枚举 $t$，这个是你钦定下来 $l=\gcd(b_i)$ 的因子的 $2$ 的最高次幂，即 $2^t \parallel l$。

不妨假设满足 $2^t \mid b_i$ 的个数为 $s$，所以 $s=\sum_{i=t}c_i$。

此时对答案产生的贡献为：

$$2^{s-c_i} \sum_{i=1,2 \mid i}\tbinom{c_t}{i}$$

注意到 $\sum\limits_{i=1,2 \mid i}\tbinom{c_t}{i}=2^{c_i}-1$，因为取不到 $\tbinom{c_t}{0}$。

所以总的答案贡献就是 $2^s-1$。

然后枚举的每一个 $t$，将答案累加即可。

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,ans;
int c[35];//考虑到1e9的二进制下不超过32位，故开了35的数组
int a[200009];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b%2) res=res*a%mod;
		b/=2;
		a=a*a%mod;
	}
	return res;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[__builtin_ctz(a[i])]++;
		//__builtin_ctz(a[i])可以求a[i]的二进制下后缀0的个数，即可以求出满足 2^t || a[i] 的t值
	}
	int s=0;
	for(int i=1;i<=30;i++) s+=c[i];
	ans=(qpow(2,c[0])-1)*qpow(2,s)%mod;
	//这一行代码已经处理了c[0]情况
	for(int i=1;i<=30;i++){
		s=0;
		for(int j=i+1;j<=30;j++) s+=c[j];
		int res=0;
		if(c[i]>=2) res=qpow(2,c[i]-1)-1;
		//若c[i]为0，上面已经处理过了，故略过
		//若c[i]为1，由于是奇数故直接忽略
		//所以只需要处理c[i]>=2
		ans+=res*qpow(2,s);
		ans%=mod;
		//按照上面的公式直接推
	}
	cout<<ans;
}
```


---

## 作者：eastcloud (赞：1)

跟学弟 duel 时随到的，想了一个小时才会，这题真只有 2000 吗？

一个显然的想法是找连续段里面的数之间的匹配，然后观察推得性质，但是这不很方便，于是我们考虑转化题意，将其变成一个更好分析的形式。

由于每个数列都是公差为 1 的等差数列，我们不妨直接把 $sum_i$ 写出来，设首项为 $S$，化简可得 $sum=\frac{n^2-n}{2}+nS$，因此子序列合法的条件即为 $\sum_i \frac{a_i^2-a_i}{2}+nS_i=0$。

不难发现我们可以抛弃 $S$，把条件变成 $\gcd(a_1,\cdots,a_m)|\sum_{i=1}^m \frac{a_i^2-a_i}{2}$，首先，当只选奇数时肯定合法。从原题的角度来看每个奇数长度都可以只产生 0 的贡献，奇数偶数都选不难从上面的柿子得出也肯定合法，因此我们只用考虑只选偶数的情况。

接下来怎么办？dp 吗？状态太多了，考虑进一步优化。

接下来貌似只能从上面那个整除的柿子入手了，考虑把条件转化成 $\sum_{i=1}^m \gcd(a_1,\cdots,a_m) \equiv 0 \pmod {\frac{a_i^2-a_i}{2}}$，并尝试分析左边每一个 $\frac{a_i^2-a_i}{2}$ 的贡献。

一个观察是对于所有 $a_i$ 都有 $\frac{a_i^2-a_i}{2}  \equiv \frac{a_i}{2} \pmod{n}$，因此如果 $\gcd$ 2 的幂次比 $a_i$ 少，那贡献为 0，否则贡献为 $\frac{gcd}{2}$。

之后的计算是简单的，先补集转化，考虑求出所有不合法的方案，每次钦定一个 2 的幂次为当前所有 $a_i$ 的最低幂次，大于的随便选，等于的必须选奇数个，组合数算一算即可。


```cpp
int main(){
    int n=read();init();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    int res=qp(2,n)-1;

    for(int i=1;i<=n;i++){
        int tmp=0;
        while(a[i]%2==0)tmp++,a[i]/=2;
        if(tmp)c[tmp]++;
    }
    int sum=0;
    for(int i=30;i>=1;i--){
        int coef=0;
        for(int j=1;j<=c[i];j+=2)Add(coef,C(c[i],j));
        Dec(res,mul(coef,qp(2,sum)));
        sum+=c[i];
    }
    write(res);
    return 0;
}
```

---

## 作者：sgl654321 (赞：1)

很不错的一道题，考验数学功底和观察能力。

## 题目大意
长度为 $m$ 的序列 $b$ 称之为好的，应满足：可以相应构造出 $m$ 个序列 $c_i$，$c_i$ 长度 $l=b_i$ 的等差数列，公差 $d = 1$，首项 $ x_0$ 为任意整数。同时，这 $m$ 个等差数列的和为 $0$。

问长度为 $n$ 的序列 $a$ 中，有多少子序列是好的。

## 解题思路

### 转化“好序列”的判定
首先，将每个等差数列求和 $S_i = {x_0}_ i b_i+\dfrac{b_i(b_i-1)}{2}$。因为这 $m$ 个等差数列的和为 $0$，容易得到：$\sum S_i = \sum {x_0}_ ib_i+\sum\dfrac{b_i(b_i-1)}{2} = 0$。移项就有：

$\sum\dfrac{b_i(b_i-1)}{2}=\sum b_i \times (-{x_0}_ i)$

${x_0}_ i$ 为任意整数，我们可以把他看成一个 $m$ 元的不定方程。不定方程有整数解，则考虑裴蜀定理。容易发现，一个序列 $b$ 是好的的充要条件为：

$$\gcd_{i=1}^m b_i \mid \sum_{i=1}^m\dfrac{b_i(b_i-1)}{2} $$

到这里完成了第一步转化。

### 只要有奇数就一定是好序列

继续观察，通过样例我们发现，一个序列，只要有奇数，就一定是个好序列。为什么是这样呢？

- 引理：若 $x\mid a,y\mid b$，则 $\gcd(x,y)\mid (a+b)$

这个很好理解，因为 $a,b$ 肯定都是 $\gcd(x,y)$ 的倍数，那么他们加起来肯定也还是。

回到正题，如果 $b_i$ 是一个奇数，那么 $\dfrac{b_i-1}{2}\times b_i$ 一定是 $b_i$ 的倍数。因为左边那个分式是一个整数。根据引理，如果序列全是奇数肯定是好的。

那么如果 $b_i$ 是偶数呢？我们设 $b_i=2^q\times k$，其中 $k$ 为奇数。就是把它所有 $2$ 质因子都提出来了。

那么 $\dfrac{b_i(b_i-1)}{2}=2^{q-1}\times k(b_i-1)$，由此可见，除了 $2$ 这个因子少了一个，其他因子都没有少。

如果 $b$ 序列中存在至少一个奇数，那么左边的 $\gcd_{i=1}^m b_i $ 肯定是一个奇数了，$2$ 因子的缺失不会造成影响。因此，序列有奇有偶，也一定是好的。

### 全是偶数也可能是好序列
接下来我们考虑全是偶数的情况。我们只需要考虑 $2$ 因子是否缺失就行了。设这些偶数 $b_i$ 分别为 $2^{q_i}\times k_i$。

那么 $\gcd_{i=1}^m b_i=2^{\min{q_i}}\times \gcd_{i=1}^m k_i$。

$\sum_{i=1}^m \dfrac{b_i(b_i-1)}{2}=\sum_{i=1}^m2^{q_i-1}\times r_i$，其中 $r_i=k_i\times (b_i-1)$，是个奇数。

我们只需要考虑 $2^{\min q_i}$ 是不是 $\sum_{i=1}^m2^{q_i-1}\times r_i$ 的因数就行了。

右边的求和式，我们可以提出一个最小的 $\min(q_i)-1$，对于所有比他大的 $q_i-1$，提出 $2^{min(q_i)-1}$，再乘上 $r_i$，就变成了个偶数。

容易发现，当 $\min(q_i)$ 有奇数个的时候，最终 $2$ 只能到达 $2^{min(q_i)-1}$ 这么多次方，不能是 $2^{\min q_i}$ 的倍数。

当它有偶数个的时候就可以。因为提取之后，括号中又凑齐了一个偶数，就到达了 $2^{\min q_i}$ 这么多次方了。


综合一下，有两种情况可以成为好序列：

- 只要有奇数就是好序列
- 对于全偶数情况，$2$ 指数最小的数有偶数个，也是好序列。

### 通过计数统计答案

设其中有 $o$ 个奇数，$e$ 个偶数。$o+e=n$。

对于有奇数的情况，共有 $2^n-2^e$ 种。正难则反容易得到。

然后全偶数的情况，我们对所有偶数，拿出它的 $2$ 指数幂，然后从小到大排序。

把每一个不同的 $2$ 指数幂作为 $2$ 指数幂最小值。然后在从中取出偶数个。比它大的 $2$ 指数幂都可以任意取。这个用组合数容易实现。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll n, a[maxn], num, b[maxn], c[maxn], tmp, save, fac[maxn], iv[maxn];
ll ans;
ll qpow(ll x, ll y){
	ll ret = 1;
	while(y){
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
ll C(ll x, ll y){
	return fac[x] * iv[y] % mod * iv[x - y] % mod;
}
int main(){
	
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) if(a[i] % 2 == 0) num++, b[num] = a[i];
	
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod; 
	iv[n] = qpow(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; i--) iv[i] = iv[i + 1] * (i + 1) % mod;
	
	
	ans = qpow(2, n) - qpow(2, num);
	ans = (ans % mod + mod) % mod;
	
	for(int i = 1; i <= num; i++){
		c[i] = 1;
		while(1){
			if(b[i] % 2 == 1) break;
			b[i] /= 2; c[i] *= 2;
		}
	}
	sort(c + 1, c + 1 + num);

//	cout << ans << endl;
//	for(int i = 1; i <= num; i++) cout << c[i] << ' ';
//	cout << endl;
	
	for(int i = 1; i <= num + 1; i++)
		if(c[i] != c[i - 1] && i != 1){
			save = 0;
			for(int j = 2; j <= tmp; j += 2)
				save += C(tmp, j), save %= mod;
		//	cout << tmp << endl;
			save = save * qpow(2, num - i + 1) % mod; 
			ans += save; ans %= mod;
			tmp = 1;
		}else tmp++;
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1610d-not-quite-lee-de-ti-jie/)

假设长度为 $a_i$ 的连续的序列的第一项为 $x_i$，那么因为易得 $s_i=\cfrac{a_i\cdot[x_i+(x_i+a_i-1)]}{2}$ 。

因为题目要求 $\sum_{i=1}^{m} s_i=0$，所以可以得到 $\sum_{i=1}^{m} \cfrac{a_i\cdot[x_i+(x_i+a_i-1)]}{2}=0$。

即 $\sum_{i=1}^{m} \cfrac{a_i\cdot[2\cdot x_i+a_i-1]}{2}=0$。

也就是 $(\sum_{i=1}^{m} \cfrac{a_i\cdot(a_i-1)}{2})+(\sum_{i=1}^{m} a_i\cdot x_i)=0$。

通过移项可以得到 $\sum_{i=1}^{m} \cfrac{a_i\cdot(a_i-1)}{2}=-\sum_{i=1}^{m} a_i\cdot x_i$，所以左边就是一个常数。

根据贝祖定理，当且仅当 $\gcd(a_1,a_2,\cdots,a_{m})\mid \sum_{i=1}^m \cfrac{a_i\cdot(a_i-1)}{2}$ 时有解，通过移项可以得到 $2\mid \sum_{i=1}^m \cfrac{a_i\cdot(a_i-1)}{\gcd(a_1,a_2,\cdots,a_{m})}$。

假设 $\gcd(a_1,a_2,\cdots,a_{m})=2^t\cdot (2k+1)$ 其中 $t$ 尽可能大且 $k$ 为整数，那么设 $c_i=\cfrac{a_i}{2^t}$。

将上式代入，得到 $2\mid \sum_{i=1}^m \cfrac{2^t\cdot c_i\cdot(2^t\cdot c_i-1)}{2^t\cdot(2k+1)}$，由于这个式子是由 $\sum_{i=1}^m \cfrac{a_i\cdot(a_i-1)}{\gcd(a_1,a_2,\cdots,a_{m})}$  变形来的，所以一定是一个整数。

因为一个偶数除以一个奇数并不影响奇偶性，所以 $2k+1$ 直接不看，即得到 $2\mid \sum_{i=1}^m c_i\cdot(2^t\cdot c_i-1)$。

当 $t=0$ 时，等式恒成立，否则需满足 $2\mid \sum_{i=1}^m c_i$。

因为 $t=0$ 只会发生在选择的 $m$ 个数中出现奇数，所以将奇数的情况单独讨论。

假设奇数有 $a$ 个，偶数有 $b$ 个，那么因为只要有奇数就可以，所以方案数为 $(2^a-1)\cdot 2^b$。

对于 $t\ne 0$ 的情况，假设有 $a$ 个 $a_i$ 没有多余的 $2$，$b$ 个有多余的 $2$，那么贡献为 $2^b\cdot \sum_{i=0}^{\lfloor a/2\rfloor }C^{2i}_{a}$。

因为 $C^i_a=C^i_{a-1}+C_{a-1}^{i-1}$，所以贡献为 $2^b\cdot\sum_{i=1}^{a-1}C^i_{a-1}$，也就是 $a$ 个元素的非空子集数量 $2^b\cdot (2^{a-1}-1)$。

```c++
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+5,mod=1e9+7;
int n,s[N],sum,ans;
int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a%mod;
        }
        b>>=1;
        a=a*a%mod;
    }
    return ans;
}
int f(int x){
    int ans=0;
    while(!(x&1)){
        ans++;
        x>>=1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        s[f(x)]++;
    }
    for(int i=1;i<=30;i++){
        sum+=s[i];
    }
    ans=(ksm(2,n-sum)-1+mod)%mod*ksm(2,sum)%mod;
    for(int i=1;i<=30;i++){
        sum-=s[i];
        if(s[i]<2){
            continue;
        }
        ans=(ans+ksm(2,sum)%mod*(ksm(2,s[i]-1)-1+mod)%mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：541forever (赞：0)

感觉题目难度不止绿题。

首先，我们需要找出具体什么样的 $b$ 才是合法的。可以发现，$sum_i$ 一定可以被拆成 ${b_i(b_i-1)\over 2}+k_ib_i(k_i \in \mathbb{Z})$ 的形式，又因为 $\sum sum_i=0$,因此 
$$\sum{b_i(b_i-1)\over 2}+k_ib_i(k_i \in \mathbb{Z})=0$$
若 $b$ 已知，则 $\sum{b_i(b_i-1)\over 2}$ 为常数，所以 $\sum k_ib_i=-\sum{b_i(b_i-1)\over 2}$，根据裴蜀定理
$$\gcd(b_1,b_2,...,b_n) \mid \sum{b_i(b_i-1)\over 2}$$
所以 
$$2\mid\sum {b_i(b_i-1)\over \gcd(b1,b2,...,b_n)}$$
那么若 $b_i$ 存在奇数，则 $gcd(b1,b2,...,b_n)$ 为奇数，因此 ${b_i(b_i-1)\over \gcd(b1,b2,...,b_n)}$ 一定为偶数，原式一定成立，否则我们就一定需要偶数个 $b_i \over \gcd(b_1,b_2,...,b_n)$ 为奇数的值。设 $\gcd(b_1,b_2,...,b_n)=2^t\times (2k+1)(t\in \mathbb{N},k\in \mathbb{Z})$，那么我们需要 $b_i \mid 2^t$ 且 $b_i \nmid 2^{t+1}$ 的数的数量为偶数个。计算时枚举 $t$ 钦定选了几个满足 $b_i \mid 2^t$ 且 $b_i \nmid 2^{t+1}$ 的数的个数，简单组合数计算即可。

[Code](https://codeforces.com/contest/1610/submission/211609302)

---

## 作者：DaiRuiChen007 (赞：0)

# CF1610D - Not Quite Lee 题解

## 题目大意

给定一个长度为 $n$ 的序列 $a$，求出 $a$ 的所有子序列中有多少个是“好的”子序列。

定义一个序列 $b_1\sim b_m$ 是“好的”当且仅当能够构造出 $m$ 个公差为 $1$ 的等差数列，其中的第 $i$ 个等差数列的长度为 $b_i$，且这 $m$ 个等差数列的总和为 $0$。

数据范围保证：$n\le2\times 10^5,a_i\le10^9$。

## 思路分析

令 $w=\max_{i=1}^m a_i\le10^9$ 表示值域。

首先，思考如何判断一个数列 $b_1\sim b_m $ 是否是“好的”。

我们用 $s_i$ 表示第 $i$ 个等差数列的首项。

那么第 $i$ 个等差数列的和是 $\dfrac{b_i\times(2\times s_i+b_i-1)}{2}$。

那么如果存在某个序列 $s$ 是“好的”，那么应该满足：
$$\sum_{i=1}^m\left[\dfrac{b_i\times(2\times s_i+b_i-1)}{2}\right]=0$$
$$\sum_{i=1}^{m}(s_i\times b_i)+\sum_{i=1}^m\left[\dfrac{b_i\times(b_i-1)}{2}\right]=0$$
$$\sum_{i=1}^{m}(s_i\times b_i)=-\sum_{i=1}^m\left[\dfrac{b_i\times(b_i-1)}{2}\right]$$
由于等式是定值，所以根据裴蜀定理，这个方程有解的充分必要条件是 $\gcd_{i=1}^m b_i\mid\sum_{i=1}^m\left[\dfrac{b_i\times(b_i-1)}{2}\right]$

令 $g=\gcd_{i=1}^mb_i$，对这个等式进行研究：
$$
g\mid\sum_{i=1}^m\left[\dfrac{b_i\times(b_i-1)}{2}\right]\Leftrightarrow
2\mid\sum_{i=1}^m\left[\dfrac{b_i}{g}\times(b_i-1)\right]
$$
那么这个时候对 $g$ 的次幂进行分析。

令 $g=2^t\times k$ 且 $2\nmid k$。

1. $t=0$ 时：

​		此时，若 $2\mid b_i$ ，则 $2\mid\dfrac{b_i}{g}$，$2\mid\dfrac{b_i}{g}\times(b_i-1)$。

​		若 $2\nmid b_i$，则 $2\mid b_i-1$，$2\mid\dfrac{b_i}{g}\times(b_i-1)$。

​		$\therefore 2\mid\sum_{i=1}^m\left[\dfrac{b_i}{g}\times(b_i-1)\right]$。

​		所以此时 $b$ 一定是“好的”。

2. $t>0$ 时：

​		此时 $\forall b\in[1,m],2\mid b_i$。

​		$\therefore 2\nmid b_i-1$。

​		若 $2\mid \dfrac{b_i}{g}$，则 $\dfrac{b_i}{g}\times(b_i-1)$ 为偶数，否则 $\dfrac{b_i}{g}\times(b_i-1)$ 为奇数。

​		若 $\sum_{i=1}^m\left[\dfrac{b_i}{g}\times(b_i-1)\right]$ 是偶数，则一定有偶数个 $b_i$ 满足 $2\nmid\dfrac{b_i}{g}$。

所以剩下的问题就是一个简单的计数问题，对于每个 $t$ 值分别考虑，记 $l_i$ 满足 $b_i=2^{l_i}\times u,2\nmid u$ 的整数，$cnt_v$ 表示满足 $l_i=v$ 的数的个数。

对于每一个 $t$ 值对答案的贡献。

如果 $t\not=0$，贡献为 $($ 选择偶数个 $l_i=t$ 的方案数 $-1)$ $\times$ $($ 选择任意多个 $l_i>t$ 的方案数 $)$。


如果 $t=0$，贡献为 $($ 选择任意个 $l_i=t$ 的方案数 $-1)$  $\times$ $($ 选择任意多个 $l_i>t$ 的方案数 $)$。

（这里 $-1$ 是为了保证选择的 $l_i=t$ 个数 $\not=0$） 

对于统计选择任意的 $l_i=x$ 的方案数应该就是 $2^{cnt_x}$。

对于统计偶数个任意的 $l_i=x$ 的方案数，可以先让 $cnt_x-1$ 个随便选，然后最后一个选或者不选来调整整个选的个数的奇偶性，所以贡献应该就是 $2^{cnt_x-1}$。

计算 $l_i$ 的时候可以使用 C++ 自带的库函数 `__builtin_ffs(int x)` 函数，这个函数接受一个 $32$ 位整形变量 $x$，返回 $x$ 的二进制形式里右边第一个出现 $1$ 的位置，时间复杂度是 $\Theta(1)$。

所以 `l[i]=__builtin_ffs(a[i])-1` 这样就可以成功地将时间复杂度优化掉了一个 $\log$。

总的时间复杂度是 $\Theta(n+\log w\log\log w)$ 可以通过本题。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,LOG=35,MOD=1e9+7;
//LOG表示log2(w)的值 
int a[MAXN],cnt[LOG],sum[LOG];
//sum[i]表示cnt[i]~cnt[LOG]之间的和 
inline int ksm(int x,int y,int m) {
	//快速幂 
	int ans=1;
	while(y) {
		if(y&1) ans=ans*x%m;
		x=x*x%m;
		y=y>>1;
	}
	return ans;
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(register int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		++cnt[__builtin_ffs(a[i])-1]; //装桶 
	}
	for(register int i=32;i>=0;--i) sum[i]=sum[i+1]+cnt[i];
	int ans=((ksm(2,cnt[0],MOD)-1)*ksm(2,sum[1],MOD)%MOD+MOD)%MOD; //特殊处理0
	for(register int i=1;i<=32;++i) {
		if(cnt[i]<2) continue; //不够凑出偶数个就不统计答案 
		ans=(ans+(ksm(2,cnt[i]-1,MOD)-1)*ksm(2,sum[i+1],MOD)%MOD+MOD)%MOD;
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：Imitators (赞：0)

首先考虑如何判断一个长度为 $n$ 的数列 $b$ 是否合法。

设 $d_i$ 表示第 $i$ 个公差是 1的等差数列开始的位置。

那么可以列出方程 
$$
\begin{aligned}
\sum_{i=1}^n \frac{(d_i+d_i+b_i-1)b_i}{2}=0\\
\sum d_ib_i=-\sum \frac{(b_i-1)b_i}{2}
\end{aligned}
$$
那么根据裴蜀定理，要是有解应满足 $\gcd(b_i)\mid \text{rhs}$。

设 $\gcd(b_i)=2^tk,2\nmid k$。

$k\mid\text{rhs}$ 这个原因比较显然，因为 $\text{rhs}$ 只会有 $2$ 的因子缺失。

$2^{t-1}\mid\text{rhs}$ 这个也是因为 $b_i$ 最多只会除 $2$。

那么考虑存在这样一个 $2^t \mid\mid b_i$ （恰好整除），那么 $2^{t-1}\mid\mid\frac{b_i(b_i-1)}2$。

所以如果想合法，必须有偶数个恰好整除的。

---

这样问题就剩下计数了，接下来的 $b$ 是题意中的 $b$。

设满足 $2^t\mid\mid b_i$ 的 $i$ 有 $\text{num}_i$ 个。

那么我们首先枚举 $t$ 这个是你钦定下来的子序列的 $\gcd$ 最高次2因子，换句话说就是满足 $2^t\mid\mid \gcd$。

设能被 $2^t$ 整除的 $b_i$ 有 $s$ 个,$s=\sum_{i=t}\text{num}_i$。

此时产生对答案的贡献就是：

$$2^{s-\text{num}_t}\sum_{i=1,2\mid i}\binom{\text{num}_t}{i}$$

后面那个很经典就是 $2^{\text{num}_t}-1$ 注意你取不到 $\binom{\text{num}_t}{0}$

暴力做即可，复杂度 $\mathcal{O(n)/O(n\log n)}$ 主要看实现方法。

[参考代码？](https://codeforces.com/contest/1610/submission/137746324)


---

