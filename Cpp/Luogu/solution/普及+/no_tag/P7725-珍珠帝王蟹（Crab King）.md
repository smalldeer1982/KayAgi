# 珍珠帝王蟹（Crab King）

## 题目背景

在一次航程中，你偶然发现了被一片礁石环绕的帝王蟹，被月岛能量侵蚀的它又与月光有着怎样的联系呢？似乎只有击败它才能见分晓。


## 题目描述

帝王蟹可以通过镶嵌宝石触发战斗，不同的宝石效果不同，但奇特的是，镶嵌宝石的顺序有时也会影响它的强度。

帝王蟹有一个初始为 $0$ 的强度值，每个宝石有属性 $op$ 和 $v$，表示：

- 若 $op$ 为 `+`，则镶嵌后帝王蟹的强度值将会加上 $v$；

- 若 $op$ 为 `*`，则镶嵌后帝王蟹的强度值将会乘上 $v$。

由于宝石的效果十分奇异，所以 $v$ 可能是负数。

作为一个有挑战精神的冒险者，你希望采取某种镶嵌方式，将**每个宝石**都镶嵌**恰好一遍**，且使得帝王蟹的强度值最大。

你只需要输出最大的强度值对 $998244353$ 取模的结果，注意这是一个 $[0, 998244353)$ 中的数。

也就是说，如果答案为 `ans`，按照 C++ 语法，你需要输出 `(ans % P + P) % P`，其中 `P = 998244353`。


## 说明/提示

**【样例 1 解释】**

按照输入顺序以 $1, 2, 3$ 标记每个宝石，所有可能的镶嵌顺序如下：

$1\to 2\to 3$：$x = ((0 + {\color{red}{-3}}) + {\color{red}{4}}) \times {\color{red}{-4}} = -4$；

$1\to 3\to 2$：$x = ((0 + {\color{red}{-3}}) \times {\color{red}{-4}}) + {\color{red}{4}} = 16$；

$2\to 1\to 3$：$x = ((0 + {\color{red}{4}}) + {\color{red}{-3}}) \times {\color{red}{-4}} = -4$；

$2\to 3\to 1$：$x = ((0 + {\color{red}{4}}) \times {\color{red}{-4}}) + {\color{red}{-3}} = -19$；

$3\to 1\to 2$：$x = ((0 \times {\color{red}{-4}}) + {\color{red}{-3}}) + {\color{red}{4}} = 1$；

$3\to 2\to 1$：$x = ((0 \times {\color{red}{-4}}) + {\color{red}{4}}) + {\color{red}{-3}} = 1$。

因此，强度值的最大值为 $16$，对 $998244353$ 取模后为 $16$。

---

**【样例 2 解释】**

按照输入顺序以 $1, 2, 3$ 标记每个宝石，所有可能的镶嵌顺序如下：

$1\to 2\to 3$：$x = ((0 + {\color{red}{-3}}) + {\color{red}{-4}}) \times {\color{red}{4}} = -28$；

$1\to 3\to 2$：$x = ((0 + {\color{red}{-3}}) \times {\color{red}{4}}) + {\color{red}{-4}} = -16$；

$2\to 1\to 3$：$x = ((0 + {\color{red}{-4}}) + {\color{red}{-3}}) \times {\color{red}{4}} = -28$；

$2\to 3\to 1$：$x = ((0 + {\color{red}{-4}}) \times {\color{red}{4}}) + {\color{red}{-3}} = -19$；

$3\to 1\to 2$：$x = ((0 \times {\color{red}{4}}) + {\color{red}{-3}}) + {\color{red}{-4}} = -7$；

$3\to 2\to 1$：$x = ((0 \times {\color{red}{4}}) + {\color{red}{-4}}) + {\color{red}{-3}} = -7$。

因此，强度值的最大值为 $-7$，对 $998244353$ 取模后为 $998244346$。

---

**【数据范围】**

**本题采用捆绑测试。**

对于全部测试数据：$1 \le n \le {10}^5$，$2 \le |v| \le {10}^6$。

- Subtask 1（26 points）：$n \le 9$，$|v| \le 5$。
- Subtask 2（22 points）：$v > 0$。
- Subtask 3（12 points）：保证当 $op$ 为 `*` 时 $v > 0$。
- Subtask 4（15 points）：保证当 $op$ 为 `+` 时 $v > 0$。
- Subtask 5（25 points）：无特殊限制。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/rwzuwu9z.png)

## 样例 #1

### 输入

```
3
+ -3
+ 4
* -4
```

### 输出

```
16
```

## 样例 #2

### 输入

```
3
+ -3
+ -4
* 4
```

### 输出

```
998244346
```

# 题解

## 作者：_lfxxx_ (赞：22)

**题目传送门：[P7725 珍珠帝王蟹（Crab King）](https://www.luogu.com.cn/problem/P7725)**

UPD：

2021-07-21：稍微修改了下代码并增加了一下关于代码的内容。

2021-08-04：再次稍微修改题解。

2021-08-25：又一次稍微修改题解。
## 前记：
月赛时被这题恶心到了，~~果然还是太蒟了~~于是在月赛后好好研究了这题，就有了这篇题解。
## 题意：
初始贡献为 $0$ ，给你 $n$ 个字符 $op$ 和整数 $v$（$v$ 可以为**负数**），（每次给定 $1$ 组 $op$ 和 $v$）并且你要**进行 $n$ 次操作**。

每次操作你需要选**一组 $op$ 和 $v$，并且每组都要选 $1$ 次**。

- 若该 $op$ 为 `+` ，则贡献加 $v$ ；

- 若该 $op$ 为 `*` ，则贡献乘 $v$ 。

请安排选的顺序使贡献**最大**，输出贡献对 $998244353$ 取模的值。
## 思路：
不难看出该题是贪心，但贪心策略一眼看不出来，于是按 Subtask 来思考。
### Subtask 1：
$n\le9$，爆搜即可。
### Subtask 2：
$v>0$。

不难想到先加上所有数再乘上所有数。（证明略）~~这么明显应该不用证吧~~
### Subtask 3：
保证当 $op$ 为 `*` 时 $v>0$。

由于乘法只有正数，所以如果负数被乘了，贡献会大大减少，所以只让正数乘，然后加上负数。
### Subtask 4：
保证当 $op$ 为 `+` 时 $v>0$。

这时如果**乘法的负数有偶数个，那跟 Subtask 2 没有区别**（负负得正）。

如果**乘法的负数有奇数个呢？**，我们可以舍弃**绝对值最小**的负数（即**最大**的负数），接下来又跟 Subtask 2 没有区别。
### Subtask 5：
经过前面的思考，我们看出：**乘法可以带来的贡献的绝对值比不乘要多。**（$|v|\ge2$）此时我们再思考最终的贪心策略。

优先考虑乘法。
#### 如果乘法的负数有偶数个。
1. 无乘法负数

同 Subtask 3。

2. 有乘法负数
尽可能让多的数乘，怎么将**正数和负数都能乘上去**且都是**正贡献**呢？

**负负得正！**
可以找一个**最大的负数乘上加法的正数和**，然后再**加上加法的负数和**，最后**乘上所有乘法**。（这段话可能难理解，可以结合[讨论区的那个 Hack ](https://www.luogu.com.cn/discuss/show/328252)理解）
#### 如果乘法的负数有奇数个。
跟上面差不多，找一个**最大的负数乘上加法的负数和**，再**加上加法的正数和**，最后**将剩下的乘法乘上**。
## 代码：
~~好像有点长~~

关于我代码中的 [`vector<int>v4;`](https://blog.csdn.net/sss_0916/article/details/90380644) 。
```cpp
#include<iostream>
#include<vector>
#define ll long long
using namespace std;
const int mod=998244353;
ll s1,s2,s3=1,s4=1;
int max4=0;
vector<int>v4;
//s1表示加法的正数，s2表示减法的正数，s3表示乘法的正数，s4表示乘法的负数。v4是记录s4的数的，因为要记录最大值。
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);//cin，cout加速
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		char op;
		int v;
		cin>>op>>v;
		if(op=='+')
			if(v>0)
				s1=(s1+v)%mod;
			else
				s2=(s2+v)%mod;
		else
			if(v>0)
				s3=s3*v%mod;
			else
				v4.push_back(v);
	}
	if(!v4.empty()){
		for(int i=1;i<v4.size();i++)
			if(v4[i]>v4[max4])
				max4=i;
		for(int i=0;i<v4.size();i++)
			if(i!=max4)
				s4=s4*v4[i]%mod;
		max4=v4[max4];
	}//找最大值
	else
		max4=1;
	if(!(v4.size()&1))
		if(v4.empty())
			cout<<(s1*s3%mod+s2+mod)%mod<<endl;
		else
			cout<<(s1*max4%mod+s2)%mod*s3%mod*s4%mod<<endl;
	else
		cout<<(s2*max4%mod+s1)*s4%mod*s3%mod<<endl;
	return 0;
}
```
## 后记：
感谢[这个讨论中的 Hack ](https://www.luogu.com.cn/discuss/show/328252)给了我思路。

如有书写错误，请在下方评论。

---

## 作者：Blueqwq (赞：5)

## P7725 珍珠帝王蟹 (Crab King) 题解

[题目传送门](https://www.luogu.com.cn/problem/P7725)

注：以下所有名为 “减法” 的，实际上为加负数的操作。

### 简要题意：

给定 $n$ 个形如 $+v$ 或 $\times v$ 的操作以及初始数 $0$ (其中 $v$ 可能是负数)，问怎样安排操作顺序能使最后的结果最大，输出其对 $998244353$ 取模的结果。

数据范围：$n\leq 10^5,2\leq \left|v\right|\leq 10^6$ 

### Subtask 1

$O(n!)$ 枚举操作顺序，暴力判断最大值即可，注意到最大值不会超过 $5^9=1953125$，所以不必考虑溢出。

### Subtask 2

对于 $v>0$ 的情况，假设我们已经得到了一个中间值 $w$，考虑两个操作 $+m$ 和 $\times n$，怎样安排顺序才能最大化结果？

先加再乘：$(w+m)n=wn+mn$ 

先乘再加：$wn+m$ 

显然先加、再乘是优于先乘、再加的。

所以总体的操作顺序就是**先加、再乘正数**。

### Subtask 3

对于所有乘法操作保证 $v>0$，即在 Subtask 2 的基础上多出了减法操作。

那么如何让减法对最后的结果影响最小？

首先，乘法要放在加法之后，才能保证其结果更优。

其次，减法不能在乘法或加法之前，不然会让乘法增大减法对答案的影响。

所以**先加、再乘正数、最后减**是最优方案。

### Subtask 4

对于所有加法操作保证 $v>0$，即在 Subtask 2 的基础上多出了乘负数的操作。

~~不会真有人还不知道负负得正吧。~~

如果乘负数的操作有偶数个，就和 Subtask 2 类似，只需要**先加、再乘负数和正数**即可。

那如果乘负数的操作有奇数个呢？

样例 $1$ 的说明提示我们，可以在第一次操作前，把 $0$ 乘上一个负数，这样就相当于让这个操作 **“凭空消失”** ，剩下的就和上面一致了。

### Subtask 5

其实和上面的分析类似，我们需要考虑的就是如何让减法和乘负数对结果的影响最小 (或者说是对结果的贡献最大) 。

但是乘负数的操作数的奇偶性也会对顺序有影响。

所以按乘负数的操作数的奇偶进行分类。

- 乘负数的操作数是奇数。

不妨设有 $2k+1$ 个操作。

对于减法操作来说，只需要让它们之和乘奇数个负数就能变成正数。

最优解是先减、再乘负数、再加、最后乘正数？显然还有更优的做法。

对于乘 $2k$ 个较小的负数而言，他们是可以当作乘 $2k$ 个较大的正数，而剩下的一个最大的负数就已经可以把减出来的负数变为正数了。

所以最优解应该是**先减、再乘最大的负数、再加、最后乘剩下的负数和正数**。

- 乘负数的操作数是偶数。

实话实说，比赛时这种情况卡了我很久。

一开始想的是跟奇数类似，再加上 Subtask 4 中先乘最大的负数的操作，也就是：

先乘最大的负数、再减、再乘第二大的负数、再加、再乘剩下的负数和正数。

但是提交之后发现这并不是正解。

思考一下：为什么我们在上一种情况中要把负数变成正数后再计算？

1. $2k$ 个乘负数的操作能乘出一个正数，但是我们有 $2k+1$ 个。
2. 而且这多出来的一个操作刚好能让减出来的负数变成正数。

那我们现在有 $2k$ 个操作，是不是也可以让他多出来一个呢？

相信大家看到这里都能基本理解我的意思了，这里的操作与上一种情况基本相反。

既然我们想要剩下 $2k-1$ 个乘负数的操作，我们就要让之前的所有操作得到的结果变成一个最小的负数。

所以最优解实际上是**先加、再乘最大的负数、再减 (这里得到了最小的负数) 、最后乘剩下的负数和正数**。

然而现在就对了吗？

对于 Subtask 3 (没有乘负数操作) 的情况，它的操作数确实是偶数，但我们得不到想要的最小负数，所以实际上这个做法只适用于操作数 $\geq 2$ 的情况，对于操作数 $=0$ 的情况，只需要特判并采用 Subtask 3 的做法即可。



---

## 作者：CBBoos0422 (赞：5)

## 涮法：贪心
#### 题面传送门：[P7725 珍珠帝王蟹（Crab King）](https://www.luogu.com.cn/problem/P7725)


------------

这道题的细节还挺多的，对于我这样的蒟蒻只能想到用贪心来解决。
### 题意：
一开始初始值为 0 ，经过一堆运算后求**最大**值对于 998244353 取模的值。

- 若 op 为 $+$  ，则镶嵌后帝王蟹的强度值将会加上  v ；

- 若  op  为 $\times$ ，则镶嵌后帝王蟹的强度值将会乘上  v 。


------------
### 思路：
1.当第一眼看到题目的时候，不能想出适合所有情况的贪心思路，好在  

 Subtask 提供了可行的思路。

我们设给定数据中正加数之和为 $Suma$ , 负加数之和为 $Sumb$ ,正乘数之积为 $Mula$ ,负乘数之积为 $Mulb$ ，最大负乘数为 $Maxmul$ 。 

#### **由此我们可以分为以下几类：**

#### 1.对于 $op=\times$ ， $v>0$ 时：

此时，最优方案显然为 

$Ans=Suma \times Mula-Sumb$ （不需要证明，显而易见）


#### 2.对于 $op = \times$ 时， $v<0$ 的个数为偶数时：

会有很多人**想当然地认为**最优解为 $Suma \times Mula \times Mulb-Sumb$  

但是其实负加数的贡献是可以统计到**负乘数**中去的。

其中负数的和应该加到**最大负乘数**（绝对值最小）中去。

由此可得方案为 

$Ans=[(Suma \times Maxmul) + Sumb ]\times Mula \times (Mulb/Maxmul)$

#### 3.对于 $op=\times$ 时， $v<0$ 的个数为奇数时：

**1 ) . 对于 $op=\times$ ， $v>0$** ：

此时明显应该忽略掉**最大负乘数**

$Ans=(Mulb/Maxmul)\times(Mula+Suma)$ 

**2 ) . 对于 $op=+$ ， $v$ 无限制** ：

这种情况应该是比较普遍的，这是 $Sumb$ 可以说就是一个负乘数。

所以这种情况等同于是第 2 种情况：

$Ans=[(Sumb \times Maxmul)+Suma] \times Mula \times (Mulb/Maxmu l)$

------------
### 提示 
1. 在 2 与 3.2 这两种情况中，需要注意 Suma 与 Sumb 的位置；

2. 在运算的时候要边做边模，不然会爆长整型；

3. 有错误请 Hack 我。


------------

最后附上~~高清无码有点长有点啰嗦~~的代码：

```cpp
#include <bits/stdc++.h>
#define P 998244353
#define N 100005
#define int long long 
using namespace std;
int a[N],b[N];
int pd1,pd2,num1,num2,sum,sum1,Max=-P;
int t1,t2,t3;
int n,x,ans;
char c;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>c; 
		scanf("%lld",&x);
		if(c=='+') a[++num1]=x;
		else b[++num2]=x;
		if(c=='+'&&x<0) pd1=1;
		if(c=='*'&&x<0) pd2=1;
	}
	if(pd2==0) 
	{
		for(int i=1;i<=num1;i++) if(a[i]>0) ans+=a[i],ans%=P;
		for(int i=1;i<=num2;i++) ans*=b[i],ans%=P;
		for(int i=1;i<=num1;i++) if(a[i]<0) ans+=a[i],ans%=P;
		printf("%lld\n",(ans%P+P)%P);
		return 0;
	}
	for(int i=1;i<=num2;i++) if(b[i]<0) t1++;
	for(int i=1;i<=num1;i++) if(a[i]<0) t2++;
	if(t1%2==0)
	{
		for(int i=1;i<=num1;i++) 
		{
			if(a[i]<0) sum+=a[i],sum%=P;
			if(a[i]>0) sum1+=a[i],sum1%=P;
		}
		for(int i=1;i<=num2;i++) if(b[i]<0) if(b[i]>Max) Max=b[i],t3=i;
		ans=sum+(Max*sum1)%P;
		for(int i=1;i<=num2;i++) if(i!=t3) ans*=b[i],ans%=P;
		printf("%lld",(ans%P+P)%P);
	}
	else
	{
		if(pd1==0) 
		{
			for(int i=1;i<=num2;i++) if(b[i]<0) if(b[i]>Max) Max=b[i],t3=i;
			for(int i=1;i<=num1;i++) ans+=a[i],ans%=P;
			for(int i=1;i<=num2;i++) if(i!=t3) ans*=b[i],ans%=P;
			printf("%lld",(ans%P+P)%P);
		}
		else
		{
			for(int i=1;i<=num1;i++) 
			{
				if(a[i]<0) sum+=a[i],sum%=P;
				if(a[i]>0) sum1+=a[i],sum1%=P;
			}
			for(int i=1;i<=num2;i++) if(b[i]<0) if(b[i]>Max) Max=b[i],t3=i;
			ans=((Max*sum)%P+sum1)%P;
			for(int i=1;i<=num2;i++) if(i!=t3) ans*=b[i],ans%=P;
			printf("%lld",(ans%P+P)%P);
		}
	}
	return 0;
}
```







---

## 作者：Argon_Cube (赞：3)

* **【题目链接】**

[Link:P7725](https://www.luogu.com.cn/problem/P7725)

* **【解题思路】**

本题正解：贪心、分类讨论。

不得不说，这个贪心是真的妙啊。

我们的贪心策略是：争取让每一个元素都可以对答案做最大的正贡献。

那么，如何做呢？

首先，我们要把加正数、乘正数、加负数、乘负数的操作分开来。

然后，我们需要对乘以负数的操作数分类讨论。

* 如果没有乘以负数的操作，那么加负数无论如何都会对结果有负贡献。显然我们要先把加正数的操作用完，然后再把所有的乘法操作用完，最后使用加负数的操作。

* 否则，

	* 如果乘以负数的操作是奇数个，那么我们可以把全部加负数的操作先用上，再选取乘负数操作中操作数绝对值最小的那个使用，接着把加正数全用上，最后把乘法操作全部用完。
    
   * 如果乘以负数的操作是偶数个，那么我们可以把全部加正数的操作先用上，再选取乘负数操作中操作数绝对值最小的那个使用，接着把加负数全用上，最后把乘法操作全部用完。
   
* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

array<int,100000> plus_pst,mult_pst,plus_neg,mult_neg;
const int modu=998244353;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int idx_plus_pst=0,idx_mult_pst=0,idx_plus_neg=0,idx_mult_neg=0,cnt,tmp;
	char optype;
	cin>>cnt;
	for(int i=0;i<cnt;i++)//操作分类
	{
		cin>>optype>>tmp;
		if(optype=='+')
			if(tmp>0)
				plus_pst[idx_plus_pst++]=tmp;
			else
				plus_neg[idx_plus_neg++]=tmp;
		else
			if(tmp>0)
				mult_pst[idx_mult_pst++]=tmp;
			else
				mult_neg[idx_mult_neg++]=tmp;
	}
	long long ans=0;
	if(idx_mult_neg==0)//没有乘以负数的操作
	{
		for(int i=0;i<idx_plus_pst;i++)
			ans=(ans+plus_pst[i])%modu;
		for(int i=0;i<idx_mult_pst;i++)
			ans=ans*mult_pst[i]%modu;
		for(int i=0;i<idx_plus_neg;i++)
			ans=(ans+plus_neg[i]+modu)%modu;
	}
	else
		if(idx_mult_neg%2)//乘以负数的操作是奇数个
		{
			for(int i=0;i<idx_plus_neg;i++)
				ans=(ans+plus_neg[i]+modu)%modu;
			auto min_pos=max_element(mult_neg.begin(),mult_neg.begin()+idx_mult_neg);
			ans=(ans*(*min_pos)%modu+modu)%modu;
			for(int i=0;i<idx_plus_pst;i++)
				ans=(ans+plus_pst[i])%modu;
			for(int i=0;i<idx_mult_pst;i++)
				ans=ans*mult_pst[i]%modu;
			int max_pos=min_pos-mult_neg.begin();
			for(int i=0;i<idx_mult_neg;i++)
				if(i!=max_pos)
					ans=ans*mult_neg[i]%modu;
		}
		else//如果乘以负数的操作是偶数个
		{
			for(int i=0;i<idx_plus_pst;i++)
				ans=(ans+plus_pst[i]+modu)%modu;
			auto min_pos=max_element(mult_neg.begin(),mult_neg.begin()+idx_mult_neg);
			ans=(ans*(*min_pos)%modu+modu)%modu;
			for(int i=0;i<idx_plus_neg;i++)
				ans=(ans+plus_neg[i]+modu)%modu;
			for(int i=0;i<idx_mult_pst;i++)
				ans=ans*mult_pst[i]%modu;
			int max_pos=min_pos-mult_neg.begin();
			for(int i=0;i<idx_mult_neg;i++)
				if(i!=max_pos)
					ans=ans*mult_neg[i]%modu;
			ans=(ans+modu)%modu;
	    }
	cout<<ans;
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：2)

#### Description

> 初始 $A=0$，给定 $n$ 个操作，每次操作可以加或乘上一个数 $v$，求安排操作顺序得到的 $A$ 的最大值为多少。

#### Solution

这题好神啊，解这道题下来感觉十分通畅。单独看问题没什么思路，可以逐个 Subtask 考虑。

**Subtask 2**：$v>0$。

贪心安排操作，先加后乘，因为乘法得到的贡献更大。

**Subtask 3**：对于乘法操作 $v>0$。

将 $v>0$ 的加法操作执行，然后执行乘法操作，最后执行 $v<0$ 的加法操作，使得加负数的损耗最小。

**Subtask 4**：对于加法操作 $v>0$。

考虑如何处理 $v<0$ 的乘法操作。

因为负负得正，我们可以对负数个数进行分类讨论：

- 偶数个负数，那么执行完所有乘法操作与执行 $|v|$ 的乘法操作无区别，转化为 Subtask 2；
- 奇数个负数，为了保证最后得到的答案是正的，可以选出负数乘法操作中的一个 $v'$ 使得 $|v'|$ 最小，最后乘起来对答案的贡献率也最小，也就是先消耗掉这个数，其他的转化成偶数个负数的情况即可。

**正解**

与 Subtask 4 类似，我们仍然是对乘法操作中负数个数进行分类讨论（正解 part 参考 @[lfxxx](https://www.luogu.com.cn/user/478461) 的题解）：

- 没有负数：转化成 Subtask 3；
- 偶数个负数：与 Subtask 4 不同，因为加法有负数操作，考虑先执行所有的 $v>0$ 的加法操作，然后执行 $|v|$ 最小且 $v<0$ 的一个乘法操作，然后执行所有 $v<0$ 的加法操作，然后执行其他所有乘法操作；
- 奇数个负数：与偶数个负数的情况同理，先执行所有 $v<0$ 的加法操作，然后执行 $|v|$ 最小且 $v<0$ 的一个乘法操作，然后执行所有 $v>0$ 的加法操作，然后执行其他所有乘法操作。

#### Code

```cpp
#include <bits/stdc++.h>
#define Mod 998244353
#define int long long

using namespace std;

int n;
int plusz[100015];
int timesz[100015];
int plusm[100015];
int timesm[100015];
int cntpz, cnttz;
int cntpm, cnttm;
int ans;

signed main () {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		char opt;
		int v;
		cin >> opt >> v;
		if (opt == '+') {
			if (v > 0) plusz[++cntpz] = v;
			if (v < 0) plusm[++cntpm] = v;
		}
		if (opt == '*') {
			if (v > 0) timesz[++cnttz] = v;
			if (v < 0) timesm[++cnttm] = v;
		}
	}
	sort(timesm + 1, timesm + cnttm + 1);
	if (cnttm == 0) {
		for (int i = 1; i <= cntpz; i++) ans += plusz[i], ans %= Mod;
		for (int i = 1; i <= cnttz; i++) ans *= timesz[i], ans %= Mod;
		for (int i = 1; i <= cntpm; i++) ans += plusm[i], ans = (ans % Mod + Mod) % Mod;
	} else if (cnttm % 2ll == 0ll) {
		for (int i = 1; i <= cntpz; i++) ans += plusz[i], ans %= Mod;
		ans *= timesm[cnttm];
		ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i <= cntpm; i++) ans += plusm[i], ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i < cnttm; i++) ans *= timesm[i], ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i <= cnttz; i++) ans *= timesz[i], ans = (ans % Mod + Mod) % Mod;
	} else {
		for (int i = 1; i <= cntpm; i++) ans += plusm[i], ans = (ans % Mod + Mod) % Mod;
		ans *= timesm[cnttm];
		ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i <= cntpz; i++) ans += plusz[i], ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i < cnttm; i++) ans *= timesm[i], ans = (ans % Mod + Mod) % Mod;
		for (int i = 1; i <= cnttz; i++) ans *= timesz[i], ans = (ans % Mod + Mod) % Mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：luqyou (赞：0)

# 前言

$ 167ms $，自认为比较慢。~~毕竟最优解是22ms~~

本来一看**样例说明**，觉得这就是一道大法师题，太简单了吧。于是开始爆搜吃了**4个Subtask的TLE**......

后来仔细想了想，贪心可以做啊。

再加上我的神犇同学 lfxxx 都用这么~~麻烦~~难以理解的方法做的，为什么不支持一下贪心呢？

# 还是先理一下题意

给定 $ n $ 个 $ op $ ，具有符号 $ × $ 或者符号 $ + $ , 且权值为 $ v $, 还可能出现负权。

初始战斗值为 $ 0 $,挑选一种操作顺序使得最终战斗值最大。

总数据范围如下：

$ 1≤n≤10^5 $

$ 2≤|v|≤10^6 $

# 分析思路

大概思路可以明确就是贪心。

容易发现比较特殊且棘手的操作的就是乘上负数和加上负数，还要分支判断。

首先，我们要明确以下几点：

1. 如果没用乘上负数的操作，那么加上负数的操作我们肯定希望影响越小越好，个人认为这个情况比较简单，只要先加上所有正数然后乘上所有正数然后减去所有负数即可。

1. 如果有乘上负数的操作，就必须要讨论奇偶个负权，因为我们一定希望结果是正数。

1. 如果乘负数的个数是奇数个，那么要让最后的数是正数，只需要先把所有负数加上，然后用绝对值最小的负数去乘上当前数。这样当前数就成为了非负数，且有偶数个乘负数操作，接下来贪心即可，把所有正数加上，然后乘上剩下的数。

1. 最后一种情况，如果乘负数的个数是偶数个，那么应该让所有正数先加上，然后把它乘上负数，然后用绝对值最小的负数去乘上当前数，这样当前数成为了负数，这么做是为了同时最大化加减数贡献的战斗值，这时再加上所有的负数，最后再乘上剩下的数即可。

这样下来这一题就被KO啦，可以上代码了。

# code

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;


ll rd(){
	ll x;
	scanf("%lld",&x);
	return x;
}

const int MOD = 998244353;

int mul(int a,int b){
	int res = (ll)a * b % MOD;
	if(res < 0) res += MOD;
	return res;
}

void add(int &a,int b){
	a += b;
	if(a >= MOD) a -= MOD;
}

void sub(int &a,int b){
	a -= b;
	if(a < 0) a += MOD;
}

char op[5];

int main(){
	int n = rd();
	vector<int> v1,v2,v3,v4; //+:+,-   *:+,-
   	for(int i = 0;i < n;i++){
		scanf("%s",op);
		int val = rd();
		if(op[0] == '+') {
			if(val > 0) v1.push_back(val);
			else v2.push_back(-val);	
		}
		else {
			if(val > 0) v3.push_back(val);
			else v4.push_back(val);
		}
	}	
	int ans = 0;
	sort(v1.begin(),v1.end());
	sort(v2.begin(),v2.end());
	sort(v3.begin(),v3.end());
	sort(v4.begin(),v4.end());
	if(v4.empty()) {
		for(auto it:v1){
			add(ans,it);
		}
		for(auto it:v3){
			ans = mul(ans,it);
		}
		for(auto it:v2){
			sub(ans,it);			
		}
	}
	else {
		if(v4.size() & 1) {
			for(auto it:v2){
				sub(ans,it);
			}
			ans = mul(ans,v4.back());
			v4.pop_back();
			for(auto it:v1){
				add(ans,it);
			}
			for(auto it:v3){
				ans = mul(ans,it);
			}
			for(auto it:v4){
				ans = mul(ans,it);
			}
		}
		else {
			for(auto it:v1){
				add(ans,it);
			}
			ans = mul(ans,v4.back());
			v4.pop_back();
			for(auto it:v2){
				sub(ans,it);：
			}
			for(auto it:v3){
				ans = mul(ans,it);
			}
			for(auto it:v4){
				ans = mul(ans,it);
			}
		}
	}
	cout << ans;		
}
```

灵感来源于：

洛谷 lfxxx

博客园 MQFLLY


---

## 作者：WuhenGSL (赞：0)

## 分析:

为了让最后的结果最大，我们需要把负数的影响消除或者把负数变为正数。

如果我们当前的值是负数，此时再乘上一个负数，就能把结果“扭亏为盈”。

关键在于什么时候进行“扭亏为盈”，才能让最终的收益最大化。

我们也不难发现，我们一定需要先进行一些加减操作，然后再乘。这样让乘数尽量大，才能让乘法的收益较大。

## 分类讨论：

- 当负乘数的个数为奇数
    
    1. 先加负数
    
    2. 乘一个绝对值最小的负数（用最小的代价扭亏为盈）
    
    3. 加正数
    
    4. 乘剩下的数（此时负数为偶数个，乘完必为正）
    
- 当负乘数的个数为偶数个且不为零

	 1. 先加正数
      
     2. 乘一个绝对值最小的负数
      
     3. 加负数
      
     4. 乘剩下的数
      
由于负乘数为偶数个，最后一定能乘出正数，所以先让加数变为负数，这样加减不会相消，最后再乘成正数
      
- 负乘数的个数为零
	
    1. 加正数
    
    2. 乘正数
    
    3. 加负数
    
  
### 注意

此题需要边取模边乘，不然会爆 long long

### 代码实现


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 200010
#define inf 1<<30
#define int long long
using namespace std;
const int MOD = 998244353;
int n,add,mut,addcnt,mutcnt,maddcnt,mmutcnt;
int madd,mmut[N],minadd=-inf,minmut=-inf,M=1;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		char c;int a;cin>>c;
		cin>>a;
		if(c=='+'&&a<0)madd+=a;
		if(c=='*'&&a<0)++mmutcnt,minmut=max(minmut,a),M=(M%MOD*a%MOD)%MOD;
		if(c=='+'&&a>0)add+=a;
		if(c=='*'&&a>0)++mutcnt,M=(M%MOD*a%MOD)%MOD;
	}
	int ans=0;
	if(M>0&&mmutcnt)
	{
		ans+=add;
		ans*=minmut;
		ans+=madd;
		ans=(ans%MOD*M%MOD)%MOD;
		ans/=minmut;
	}
	if(M>0&&!mmutcnt)
	{
		ans+=add;
		ans=(ans%MOD*M%MOD)%MOD;
		ans+=madd;
	}
	if(M<0)
	{
		ans+=madd;
		ans*=minmut;
		ans+=add;
		ans=(ans%MOD*M%MOD)%MOD;
		ans/=minmut;
	}
	printf("%lld",(ans%MOD+MOD)%MOD);
	return 0;
}

```
    
    
    

---

## 作者：张晟轩 (赞：0)

## 题目分析:
很显然是贪心，但比较复杂，一个一个Subtask分析。
### 预处理:
先分别统计 $op$ 为 $+,* $ 时 $v>0$ 和 $v<0$ 的情况。  
用 $p1$ 表示 $op$ 为 $+,v>0$ 时 $v$ 之和，   
$p2$ 表示 $op$ 为 $+,v<0$ 时 $v$ 之和(没有绝对值)，   
$t1$ 表示 $op$ 为 $* ,v>0$ 时 $v$ 之积，   
$t2$ 表示 $op$ 为 $* ,v<0$ 时 $v$ 之积(同样没有绝对值)，  
$maxm$ 表示 $op$ 为 $* ,v<0$ 时 $v$ 的最大值(注意 $v$ 是负数)。  
处理代码
```cpp
for(int i=1;i<=n;++i){
    scanf("%s%lld",op,&x);
    if(op[0]=='+'){
        if(x>0) p1=(p1+x)%MOD;
        else p2=(p2+x)%MOD;
    }
    if(op[0]=='*'){
        if(x>0) t1=t1*x%MOD;
        else if(x<0) {
            if(maxm<x) maxm=x,t2=t2%MOD*x;
            else t2=t2/maxm*x%MOD*maxm;
            //注意这里不能直接写t2=t2*x%MOD,否则后面t2/maxm会出错
        }
    }
}

```
### Subtask 1:
$n\leq 9$, 暴力DFS就行了。  

### Subtask 2:
$v>0$, 显然只需输出 $p1\cdot t2$。  
代码：
```cpp
if(p2==0&&t2==1){
    printf("%lld\n",p1*t1%MOD);
    return 0;
}

```
### Subtask 3:
保证当 $op$ 为 * 时 $v>0$,即 $t2=1$。  
此时 $p1\cdot t1$ 最大，而 $p2$ 不乘任何书最大，所以答案为 $p1\cdot t1+p2$。  
代码：
```cpp
if(t2==1){
    printf("%lld\n",((p1*t1%MOD+p2)%MOD+MOD)%MOD);
    return 0;
}
```
### Subtask 4:
保证当 $op$ 为 $+$ 时 $v>0$,即 $p2=0$。  
注意 $t2$ 可能为负，要分类讨论。  
若 $t2>0$ ,答案就是 $p1\cdot t1\cdot t2$,  
若 $t2<0$ ,要让最大（即绝对值最小）的负数乘 $0$，答案就是 $p1\cdot t1\cdot\frac{t2}{maxm}$。   
代码：
```cpp
if(p2==0&&t2>0){
    printf("%lld\n",p1*t1%MOD*t2%MOD);
    return 0;
}
if(p2==0&&t2<0){
    printf("%lld\n",t2/maxm*p1%MOD*t1%MOD);
    return 0;
}

```
### Subtask 5:
$t2$ 不一定等于1，所以继续分类讨论。  
若 $t2>0$, 对于 $t1$, $t1\cdot p1\cdot p2$ 最大，而对于 $t2$, $t2\cdot p1\cdot \frac{p2}{maxm}$最大（为正数），此时式子为  $((0+t1)\cdot maxm+t2)\cdot p1\cdot \frac{p2}{maxm}$。    
若 $t2<0$, 对于 $t1$, $t1\cdot p1\cdot \frac{p2}{maxm}$最大，而对于 $t2$, $t2\cdot p1\cdot p2$最大，此时式子为 $((0+t2)\cdot maxm+t1)\cdot p1\cdot \frac{p2}{maxm}$。  
代码：
```cpp
ll ans=0;
if(t2>0){
	ans=p1*t1%MOD*t2%MOD+p2*t2/maxm%MOD*t1%MOD;
}
else if(t2<0){
	ans=p1*t1%MOD*t2/maxm%MOD+p2*t2%MOD*t1%MOD;
}
printf("%lld\n",(ans%MOD+MOD)%MOD);
```

## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x,p1,p2,t1=1,t2=1,maxm=-2e9;
const ll MOD=998244353;
char op[5];
int main(){
    scanf("%d",&n);
    //预处理
    for(int i=1;i<=n;++i){
        scanf("%s",op);
        scanf("%lld",&x);
        if(op[0]=='+'){
            if(x>0) p1+=x,p1%=MOD;
            else p2+=x,p2%=MOD;
        }
        if(op[0]=='*'){
            if(x>0) t1=t1*x%MOD;
            else if(x<0) {
                if(maxm<x){
                    maxm=x;
                    t2%=MOD;
                    t2=t2*x;
                }
                else t2=t2/maxm%MOD*x%MOD*maxm;
            }
        }
    }
    //subtask2
    if(p2==0&&t2==1){
        printf("%lld\n",p1*t1%MOD);
        return 0;
    }
    //subtask3
    if(t2==1){
        printf("%lld\n",((p1*t1%MOD+p2)%MOD+MOD)%MOD);
        return 0;
    }
    //subtask4
    if(p2==0&&t2>0){
        printf("%lld\n",p1*t1%MOD*t2%MOD);
        return 0;
    }
    if(p2==0&&t2<0){
        printf("%lld\n",t2/maxm*p1%MOD*t1%MOD);
        return 0;
    }
    //subtask5 and 1
    ll ans;
    if(t2>0) ans=p1*t1%MOD*t2%MOD+p2*t2/maxm%MOD*t1%MOD;
    else if(t2<0) ans=p1*t1%MOD*t2/maxm%MOD+p2*t2%MOD*t1%MOD;
    printf("%lld\n",(ans%MOD+MOD)%MOD);
    return 0;
}
```



---

