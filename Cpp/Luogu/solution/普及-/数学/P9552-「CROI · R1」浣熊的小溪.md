# 「CROI · R1」浣熊的小溪

## 题目背景

> “从太阳里奔来，又迎着阳光走去；张开熊爪，与风相拥，离别之际，却低首自吟。”\
那梦枫畔嬉戏的成长，那阳光下不羁的信仰，历久弥坚，在无数浣熊的心畔回响。 \
> 可叹，灵溪上畔，一人意志，大小工事，割裂了纯真的年华，刀刻了落寞的隔阂。\
那明澈的小溪，那快乐的往日，还会，在感怀中驻足吗……

## 题目描述

浣熊岭的森林可以看作一张 $n \times m$ 的网格图。工厂排放的废水污染了纵贯森林的梦枫溪（一条直线），导致所经区域对浣熊是有害的。小浣熊 CleverRaccoon 为了研究废水对浣熊的危害，要寻求你的帮助。

设 $f(n,m)$ 表示一条直线最多能穿过 $n\times m$ 的网格图的格子数。

小浣熊有两种问题想要问你：

1.  给定 $n,m$，求 $f(n,m)$；
2.  给定 $n,m,Q$，你需要找到 $n'\ge n,m'\ge m$，满足 $f(n',m')\ge Q$，且 $n'\times m'$ 尽可能小。求 $n'm'-nm$ 的最小值**对 $998244353$ 取模**的结果。数据保证 $f(n,m)<Q$。

## 说明/提示

#### 样例解释 #1

对于第一次询问：

下图所示的情况是一种最佳构造方案，梦枫溪穿过 $2 \times 3$ 的网格森林时，最多穿过 $4$ 个小网格（黄色部分为穿过的网格，灰色部分为未穿过的网格）。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dknua6w.png?x-oss-process=image/resize,m_lfit,h_360)

下示方案不是一种最佳方案，梦枫溪是从两个绿色网格中间的一个顶点上穿过的，所以两个绿色区域都没有被穿过。因此梦枫溪只穿过了 $3$ 个小网格。

![](https://cdn.luogu.com.cn/upload/image_hosting/cgjzaf2i.png?x-oss-process=image/resize,m_lfit,h_360)

对于第二次询问：

如下图所示，当 $n'=2$, $m'=9$ 时，才能使梦枫溪穿过 $10$ 个网格的情况下，在原基础添加的 $n'm'-nm$ 个网格是最少的（红色虚线左边是原来的森林，右边是添加的部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/phkx3o46.png)

#### 数据范围

**本题采用 Subtask 捆绑测试。**

| Subtask | $n$ | $m$ | $Q$ | 特殊性质 | Score |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $0$ | $\le10^{18}$ | $=1$ | $\le2 \times 10^{18}$  | $op=1$ | $5$ |
| $1$ | $\le10^{18}$ | $=1$ | $\le2 \times 10^{18}$  | $op=2$ | $5$ |
| $2$ | $\le10^{18}$ | $\le10^{18}$ | $\le2 \times 10^{18}$ | $op=1$ | $25$ |
| $3$ | $\le10^{18}$ | $\le10^{18}$ |$\le2 \times 10^{18}$ | $op=2$ | $25$ |
| $4$ | $\le10^9$ | $\le10^9$ | $\le2 \times 10^9$ | 无特殊性质 | $30$ |
| $5$ | $\le10^{18}$ | $\le10^{18}$ | $\le2 \times 10^{18}$ | 无特殊性质 | $10$ |

对于 $100\%$ 的数据，保证 $1 \le T \le 10$，$op \in \{1,2\}$，$1 \le n,m \le 10^{18}$，$2 \le n+m \le Q \le 2 \times 10^{18}$。

## 样例 #1

### 输入

```
2
1
2 3
2
2 3 10```

### 输出

```
4
12```

# 题解

## 作者：CultReborn (赞：15)

[原题链接](https://www.luogu.com.cn/problem/P9552)

比赛时有事，晚进早退，就打卡了一下 T1，估计起码有橙（怎么可能是红）。。。

这是一篇有详细过程的成长类题解。

# 题意（还原向）

设 $f(n,m)$ 表示一条直线最多能穿过 $n\times m$ 的网格图的格子数。

1.  给定 $n,m$，求 $f(n,m)$；
2.  给定 $n,m,Q$，找到 $n'\ge n,m'\ge m$，满足 $f(n',m')\ge Q$，且 $n'\times m'$ 尽可能小。求 $n'm'-nm$ 的最小值**对 $998244353$ 取模**的结果。数据保证 $f(n,m)<Q$。

题目说得很清楚。

# 思路（逐步向）

## 问题一：

对于问题一，我们可以先寻找规律，通过在草稿纸上我们画图得到这样的结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/s76ujnws.png)

|  m\n  |  1   |  2   |  3   |  4   |  5   |  6   |
| :---: | :--: | :--: | :--: | :--: | :--: | :--: |
| **1** |  1   |  2   |  3   |  4   |  5   |  6   |
| **2** |  2   |  3   |  4   |  5   |  6   |  7   |
| **3** |  3   |  4   |  5   |  6   |  7   |  8   |
| **4** |  4   |  5   |  6   |  7   |  8   |  9   |
| **5** |  5   |  6   |  7   |  8   |  9   |  10  |
| **6** |  6   |  7   |  8   |  9   |  10  |  11  |

猜测 $f(n,m)=n+m-1$。

证明：

考虑数学归纳法：

1. $m=1$ 时，直线只能穿过一行或一列的格子，总数为 $n+m-1$，$n=1$ 同理。
2. 假设：对于任意的 $n×m$ 的网格图，一条直线最多能穿过 $n+m-1$ 个格子。试证明对于 $(n+1)\times m$ 和 $n\times(m+1)$ 的网格图也成立。
3. 对于 $(n+1)\times m$ 的网格图，假设直线从左上角顶点到右下角顶点，穿过了 $n\times m$ 的网格图的 $n+m-1$ 个格子，然后再穿过额外的一行格子，总数为 $n+m-1+1$。
4.  又因为 $n$ 和 $m$ 互换后不影响最后的答案，所以 $n×(m+1)$ 的网格图同理。
5. 综上所述，可以证明一条直线最多能穿过 $n×m$ 的网格图的格子数是 $n+m-1$。

命题得证。

于是问题一优雅地解决了。

## 问题二：

至于问题二，需要我们使用一些数学知识。

1. 令 $n>m$，结果不变；
2. 此时易知 $Q\geq n\geq m$；
3. 由问题一的结论我们知道 $Q=f(n',m')=n'\times m'-1$；
4. 要求 $n'm'-nm$ 的最小值，又由于 $n$ 和 $m$ 为定值，所以只要求 $n'\times m'$ 的最小值；
5. 根据均值不等式，当 $n'=m'$ 时，$n'\times m'$ 最大；当 $n'$ 和 $m'$ 之间相差越大时，$n'\times m'$ 最小。
6. 由于我们已经规定 $Q\geq n\geq m$ 了，让 $n'$ 和 $m'$ 之间相差最大的做法，就是让 $m'=m$ 不变，增加 $n'$ 的值；
7. 又 $Q=n'\times m'-1$，所以 $n'=Q+1-m'$，$m'=m$。最终的答案即为 $(Q-m'+1)\times m-n\times m$。
8. **注意取模。**

推理结束，接下来是代码时间……

# 代码（丑陋向）

### [30pts](https://www.luogu.com.cn/record/121413603) Code：

(点击上方超链接可查看评测记录)

事实证明第二问的代码没有那么好写，下面是一篇不良代码，我们看一下哪里出了问题。

```cpp
1    else {
2	  cin >> Q;
3	  n %= mo; m %= mo; Q %= mo; 
4	  if(n < m) swap(n,m);	  
5	  n2 = (Q - m + 1) % mo;
6	  cout << (n2 * m - n * m) % mo << "\n";
7	}
```
1. 第三行和第四行的顺序颠倒了——我们不能先取余再交换，因为取余后会改变大小关系。
2. 因为取余后会改变大小关系，所以第五行和第六行会出现负数，这是不允许的，所以需要在括号内加上模数，来规避错误的负数。
3. 另外，第六行的括号内需要减去一个二次的多项式 $n\times m$，必须要加上 $998244353\times998244353$ 才能合法计算，于是我们不得不使用乘法分配律，把答案 $(Q-m'+1)\times m-n\times m$ 换成 $[(Q-m'+1)-n]\times m$ ，这样只用在括号内加一次模数就好了。

### [AC](https://www.luogu.com.cn/record/121404246) Code:

(点击上方超链接可查看评测记录)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mo = 998244353;
long long T,n,m,op,Q,n2,m2;
int main(){
  cin >> T; 
  while(T--){
  	cin >> op >> n >> m;
  	if(op == 1)
  	  cout << (n + m - 1) << "\n";
	else {
	  cin >> Q; Q %= mo;
	  if(n < m) swap(n,m);	  
	  n %= mo;  m %= mo;
	  n2 = (Q - m + 1 + mo) % mo; 
	  cout << ((n2 - n + mo) * m % mo) % mo << "\n";
	}
  }
  return 0;
}
```

[![Page Views Count](https://badges.toozhao.com/badges/01H819GEGPN901FAEBTMQEMMY2/blue.svg)](https://badges.toozhao.com/stats/01H819GEGPN901FAEBTMQEMMY2 "Get your own page views count badge on badges.toozhao.com")


创建博客：[2023.08.17 16:25]

完成题解：[2023.08.17 18:58]

上传题解：[2023.08.17 19:28]

修改题解：[2023.08.17 23:00]

简化题解：[2023.08.18 18:55]

---

## 作者：HasNoName (赞：9)

# [「CROI · R1」浣熊的小溪 ](https://www.luogu.com.cn/problem/P9552)

### 问题 1

因为长方形内画一条线最多可以穿过 $n+m-1$ 个格子，所以 $op=1$ 的情况就可以直接输出 $n+m-1$ 。

### 问题 2

我们知道 $a+b$ 的和相等 $a-b$ 的绝对值最小 $a \times b$ 的积最大，所以 $a-b$ 的绝对值最大时 $a \times b$ 的积最小。

$ n'm' $ 就等于 $ ( Q + 1 - min(n,m) ) \times min(n,m) \bmod 998244353 $

设 $ N $ 为 $998244353$ ，写出来就是 $ ( Q + 1 - min(n,m)) \times min(n,m) \bmod N $
 
 但这是会爆的，应为 $ n \times m $ 最大可达到 $ 10^{36} $ ，所以可以改为 

$$ (((Q + 1 - min(n,m) ) \bmod N ) \times ( min(n,m)\bmod N) - ( n \bmod N ) \times ( m \bmod N ) ) \bmod N $$


但膜了之后再减就不等于减了之后再膜了，可以改为

```cpp
if(n>m)
{
	long long t=n;
	n=m;
	m=t;
}
m_=(Q+1-n); // m_=m'
cout<<((m_-m)%N)*(n%N)%N<<endl;
```

### AC 代码。

```cpp
#include<iostream>
#define ll long long // 用 ll 代替 long long
using namespace std;
const ll N=998244353;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    // 让输入输出变快
	ll op,T,n,m,q,m_;
	cin>>T;
	while(T--)
	{
		cin>>op;
		if(op==1)
		{
			cin>>n>>m;
			cout<<n+m-1<<endl;
		}
		else
		{
			cin>>n>>m>>q;
			if(n>m)
			{
				ll t=n;
				n=m;
				m=t;
			}
			m_=(q+1-n);
			//cout<<(((m_%N)*(n_%N))%N-((n%N)*(m%N))%N)%N<<endl;  // 可以推出下面公式
			cout<<((m_-m)%N)*(n%N)%N<<endl;
		}
	}
	return 0;
}
```

---

## 作者：zeb6666 (赞：6)

### _**思路**_  

------------

当 $op=1$ 时，要使其经过格子最多，必须使其为台阶型，直接输出公式即可，而无论为何台阶，其公式总为：
$$n+m-1$$

![证明过程](https://cdn.luogu.com.cn/upload/image_hosting/pc0iyni7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当 $op=2$ 时，由 $1$ 得 $n'+m' \ge Q+1$。

已知两数之和，要使两数之积尽可能小，则两数之差要尽可能大（和定差小积大）。因为 $n' \ge n$ , $m' \ge m$，所以较小数为 $\min(n,m)$，则另一数最小为 $Q+1-\min(n,m)$。

接下来是取模，发现数据很大，所以需要边算边模。但有一个问题：由于 $n'\times m' \bmod 998244353$ 可能小于 $n\times m \bmod 998244353$，所以就可以如下操作：
$$(a \bmod N-b \bmod N+N) \bmod N$$

### _**代码**_ 
 
------------

```cpp
#include<bits/stdc++.h>
#define int long long //十年OI一场空，不开long long见祖宗。
using namespace std;
const int N=998244353;
signed main(){
	int t,op,n,m,q,n1,m1,ans;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>op;
		if(op==1){
			cin>>n>>m;
			cout<<n+m-1<<endl;
		}
		else{
			cin>>n>>m>>q;
			q++;
			n1=min(n,m);
			m1=q-n1;
			n%=N,m%=N;
			n1%=N,m1%=N;
			n1=(n1*m1)%N;
			n=(n*m)%N;
			ans=(n1-n+N)%N;
			cout<<ans<<endl;
		}
	}
	return 0；
}
```
注意：第一问不需要取模。

---

## 作者：金刚xkb (赞：5)

## 询问一： $op=1$ 

观察易得，一条直线穿过一个 $n\times m$ 的网格图时，穿过的小网格的数量最大值为 $n+m-1$，即 $f(n,m)=n+m-1$。

**注意：** 这里的答案不需要取模！！！

### 解释：

对于任意一种直线穿过网格图的情况，我们可以将其抽象为在一个 $n\times m$ 的网格图从穿入点到穿出点的路径，该路径由若干个被直线穿过的小网格组成。

由于对于任意确定的~~直线~~射线，它的方向是固定的。所以每条合法的路径只允许从起点开始，**向着**终点行走，例如样例图中可认为是向右和向上行走。

并且，这条路径上的每一个小网格之间必须要有相邻的边，才能保证取到最大值。

![](https://cdn.luogu.com.cn/upload/image_hosting/phkx3o46.png)

注意到，在一个 $n\times m$ 的网格图中，从一个顶点到与其不相邻的顶点的合法路径长度一定为 $n+m-1$，所以只需要令直线经过对角上的两个小正方形即可取得最大值 $n+m-1$。

## 询问二： $op=2$ 

$op=2$ 的情况需要在 $op=1$ 的情况得出的结论的基础上进行推导。

由于 $nm$ 是定值，所以要求 $n'm'$ 的最小值。又因为 $f$ 与 $Q$ 正相关，所以题意相当于将 $n$ 增加到 $n'$，将 $m$ 增加到 $m'$，使 $f(n',m')=Q$，求 $n'm'$。

因为 $f(n,m)=n+m-1$，所以增加等量的 $n$ 或 $m$，**对 $f$ 的增加量相同**。$n$ 每增加 $1$，$f$ 会增加 $m$；$m$ 每增加 $1$，$f$ 会增加 $n$。

由于我们希望增加量**最少**，所以要增加 $n$ 和 $m$ 中较大的那一个。因此，$n$ 和 $m$ 中较大的一个要增加 $Q$ 和 $f(n,m)$ 之差。故答案为：

$$\min(n,m)\times\left[Q-(n+m-1)\right]$$

最后，千万不要忘了取模。

## 本题的完整代码如下：

```cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 998244353
ll n, m, Q;
int T, op;
int main() {
	cin >> T;
	while(T--) {
		cin >> op;
		if(op == 1) { 
			cin >> n >> m;
			cout << n + m - 1 << endl;
		} else {
			cin >> n >> m >> Q;
			cout << ((min(n, m) % MOD) * ((Q - n - m + 1ll) % MOD)) % MOD << endl;
		}
	}
	return 0;
}
```

**注意要开 `long long`。**

完结撒花！

---

## 作者：One_JuRuo (赞：1)

本题看似很难，实际上只需要找找规律就好。

先从样例入手。

样例给的例子是只有两行的特殊情况，我们可以先从这个特殊情况入手。

![](https://cdn.luogu.com.cn/upload/image_hosting/yp7l238m.png)

我们发现，当一条线向下穿过的时候，设与中间的线交点为 P。那么如果 P 不在格点上时，下一行就会从这列开始，如果 P 在格点上，那么就会从下一列开始。显然，前一种会比后一种多一个格子，所以只有前种策略最优。

再把问题的范围扩大到一般情况，有了上面的结论，我们可以发现，如果总格子是 $n\times m$。那么最优解一定是 $n+m-1$，证明如下。

首先这条线可以水平切，那么就是 $n$ 个格子，然后我们再固定一端，把另一端向下移动。当这条线穿过了两行时，如果与中间的线的交点不在格点上，那么就会多出一个格子。再继续向下移动，直到穿过了 $m$ 行，这时一共交了 $m-1$ 条水平线，最多多产生 $m-1$ 个格子被穿过。

综上所述，当总格子是 $n\times m$ 时，最多可穿过 $n+m-1$ 个格子。

于是，第一个问题就很容易地解决了。

再看看第二个问题，如果想要穿过的格子数大于等于 $Q$，也就代表 $n'+m'-1$ 最小也要等于 $Q$。也就是说我们知道了 $n'+m'$ 想要求满足 $n'\leq n,m'\leq m$ 的情况下，使得 $n'\times m'$ 最小。

小学数学老师告诉我们，矩形周长一定时，长宽差距越小，面积越大。所以，$n'$ 或者 $m'$ 某一个尽可能的小就可以让 $n'\times m'$ 尽可能的大。显然，如果 $n>m$ ，就让 $m'=m,n'=Q+1-m$，反之同理。

因为无论是 $n'=n$ 还是 $m'=m$，对应的 $m'-m$ 和 $n'-n$ 的值都是 $Q+1-n-m$。所以第二问的答案就是 $\min(n,m)\times(Q+1-n-m)$。

## AC 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const unsigned long long mod=998244353;//因为数据比较大，所以我直接开的unsigned long long
unsigned long long n,m,k,d;
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%llu%llu%llu",&k,&n,&m);
		if(k==1) printf("%llu\n",n+m-1);
		else scanf("%llu",&d),d=d+1-n-m,d%=mod,printf("%llu\n",min(n,m)%mod*d%mod);
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：1)

# P9552 「CROI · R1」浣熊的小溪 题解

[题目传送门](https://www.luogu.com.cn/problem/P9552)

### 思路

对于第一问：

我们观察给出的样例图片可以发现，最优情况下有一列可以穿过 $2$ 块，剩下的每一列都只能穿过 $1$ 块。

表格归纳和公式点[这里](https://www.luogu.com.cn/paste/izp0yew7)。

通过这个表格，我们发现了 $2$ 点：

+ $m$ 和 $n$ 谁大谁小对结果没有影响。

+ 用**数学归纳法**证明出了推断的公式成立。

对于第二问：

之前学过一个口诀叫做和一定差大积小。所以我们显然应该尽可能增大 $m$ 和 $n$ 中更大的那一个，直到满足题意。

而且我们可以证明当穿过的块数正好等于 $q$ 时，差最小，且和是一定的，所以可以套用口诀，为什么恰好是 $q$ 呢？因为当和固定你找出了最小的乘积，这时要增加一个数，积肯定会更大。

对于差小积大，我们可以这样证明：

设和为 $6$。

有：

$1 \times 5 = 5$

$2 \times 4 = 8$

$3 \times 3 = 9$

显然结论是成立的，当然也可以用代数方法去证明，这里不再给出。

代数方法即设出和与一个未知数，列方程求解。

因为证明过程有些繁琐，所以大家如果想看证明可以点[这里](https://zhuanlan.zhihu.com/p/410312001)。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
unsigned long long n,m,q,t,op,tmp,cha,minn=0;
int main(){
	cin>>t;
	while(t--){
		cin>>op;
		if(op==1){//判断
			cin>>n>>m;
			cout<<n+m-1<<'\n';//推导的公式
		}else{
			cin>>n>>m>>q;
			tmp=n+m-1;
			cha=q-tmp;//差是还需要增加多少
        //我们假定m更大
        //即(m+cha)*n-m*n
        //所以等于cha*n
			minn=min(m,n);
			cout<<((cha%mod)*(minn%mod))%mod<<'\n';//运用了一下乘法分配律
        //乘的时候就要取余
		}
	}
	return 0; 
} 
```

---

## 作者：hjqhs (赞：1)

对于第一问，自己手算：  
![](https://cdn.luogu.com.cn/upload/image_hosting/1zklr4mu.png)  
可得 $f(n,m)=n + m - 1$。  
然后我们需要证明这个结论，考虑使用数学归纳法。  
当 $n=1$ 或者 $m=1$ 时，结论显然成立，因为一条直线可以将所有方格覆盖到。  
假设 $n=n_1,m=m_1$ 时结论成立，需要证明 $n=n_1+1$ 或 $m=m_1+1$ 时成立，即证 $f(n+1,m)=n+m$。  
观察上图可以发现，当 $m=m_1+1$ 时，答案会 `+1`，这个 $1$ 正是新加入一列最上面的格子。同理可证当 $n=n_1+1$ 时结论亦成立，那么 $f(n,m)=n+m-1$ 这个结论也成立。   
对于第二问，需寻找两个数 $n',m'$ 使得 $n' + m' = Q + 1 $ 且 $n' \times m'$ 最小。    
一组显然的解是 $n' = 1,m' = Q$。但这组解不一定满足题目的条件，我们需要 $n' \ge n$ 且 $m' \ge m$。所以需要调整。  
为了 $n' \times m'$ 尽可能的小，$n'$ 需要尽可能小。所以让 $n' = \min(n,m),m'=Q+1-\min(n,m)$ 即可。  
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int MOD=998244353;
int t;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		int op;
		cin>>op;
		if(op==1){
			int n,m;
			cin>>n>>m;
			cout<<n+m-1<<'\n';
		}else if(op==2){
			int n,m,q;
			cin>>n>>m>>q;
			q+=1;
			if(n>=m){
				int n1=q-m;
				cout<<((n1-n)%MOD*(m%MOD))%MOD<<'\n';
			}else{
				int m1=q-n;
				cout<<((m1-m)%MOD*(n%MOD))%MOD<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9552)

------------

**题意简述**：

设 $f(n,m)$ 为一条直线最多能够穿过一个 $n\times m$ 的网格图内的方格的个数。


需要进行 $2$ 种操作：

$1.$ 对于第一种询问，输入 $n,m$，求 $f(n,m)$。

$2.$ 输入 $Q,n,m$，请求出 $f(x,y)\ge Q$ 且 $x\ge n,y\ge m$，并且 $x\times y$ 的值最小，输出 $x\times y-n\times m$ 的**最小值**对 $998244353$ **取模**的值。 

**解决第一种询问**：


首先，我们要解决 $f(n,m)$ 的值，我们画几个图，找一下规律。

当 $n=2,m=2$ 时，$f(n,m)=3$。

当 $n=2,m=3$ 时，$f(n,m)=4$。

当 $n=3,m=2$ 时，$f(n,m)=4$。

当 $n=2,m=4$ 时，$f(n,m)=4$。

如图即为一种 $f(2,4)$ 时的画法：

![](https://cdn.luogu.com.cn/upload/image_hosting/m9g2fnyv.png?x-oss-process=image/resize,m_lfit,h_570,w_725)

猜测：$f(n,m)=n+m+1$。

**证明**：

当 $m=1$ 时，直线最多穿过第一行的 $n$ 个格子，假设成立。

而当 $m$ 增加 $1$ 时，直线除了之前的 $n$ 个格子，还可以穿过新增加的一行的一个格子。依此类推。所以我们的猜测得证。

**解决第二种询问**：

$f(n,m)$ 的值已经求出来了，为了使 $x\times y$ 尽可能小且符合条件，我们就得让 $x$ 尽可能小，也就是等于 $n$ 和 $m$ 中的最小值。而另一个数就是 $n,m,(Q-x+1)$ 中的最大值，然后按照要求输出即可。

**代码部分**：



------------


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	int q;
	cin>>q;
	while(q--){
	   int tot,n,m;
	   cin>>tot;
	   if(tot==1){
	        cin>>m>>n;
		cout<<n+m-1<<endl;
	   } 
	   else{
		int q;
		cin>>m>>n>>q;
		if(n>m) swap(n,m); 
		int n1=n,m1=q-n+1;
	        int ans=((n1%998244353)*(m1%998244353)；
                ans-=(n%998244353)*(m%998244353))%998244353;
                //记得取余。
		if(ans<0) ans+=998244353; //判断负数。
		cout<<ans<<endl;
		}
	}
	return 0;
}
```


------------


---

## 作者：CleverRaccoon (赞：0)

## [「CROI R1-T1」浣熊的小溪](https://www.luogu.com.cn/problem/P9552) 题解

请注意这篇题解**不是官方题解**，是出题人在赛后写的一篇个人认为较为通俗易通一些的题解，官方题解链接[在此](https://www.luogu.com.cn/blog/373648/sol-river)。

注意：下文提到的“区域”指的是网格图的格子。

### 题意

- $op=1$：一条直线最多能穿过 $n\times m$ 的区域数。

- $op=2$：求要使一条直线最多能穿过 $n\times m$ 的区域，最少在原来的基础上增加多少个格子。

### 部分分解法

我会观察！

### 解法一： $op=1$

观察数据范围，发现有 5pts 是 $m=1$ 的特殊数据。如下图所示，因为长方形森林是 $n\times1$ 大小的，所以所有的区域都能被穿过，一共有 $n$ 个区域，故直接输出 $n$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/l9ryny2u.png)

代码如下：

```cpp
cin >> n >> m;
cout << n << endl;
```

### 解法二： $op=2$

因为 $m=1$，所以所有的区域都能被穿过，一共能穿过 $n$ 个区域。如下图所示，为了穿过 $Q$ 个区域，我们要增加 $Q-n$ 个区域。故只要输出 $Q-n$ 对 $998244353$ 取模的结果即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/5l9ox2w8.png)

代码如下：

```cpp
cin >> n >> m >> Q;
cout << (Q - n) % 998244353ll << endl;
```

## 正解

我会推式子！

### $op = 1$ 的情况

#### 思路

对于 $op=1$ 的情况，可以自己举几个例子画一下，应该不难发现规律，梦枫溪（即一条直线）穿过长方形森林时，穿过的正方形区域的数量就是 $n+m-1$ 个。

那么这个一般式是怎么推导出来的呢？

我们先考虑以下简单的情况：一条直线穿越仅由一个正方形区域组成的长方形森林的情况（正方形是特殊的长方形）。如下图所示，当一条直线穿过仅由一个正方形区域组成的长方形森林时，这条直线最多与小方格上、下、左、右四条边中的两个边相交，所以当一条直线穿过一个区域时，这条直线会**与其中某两条边产生两个交点**，并且以两个交点为顶点的线段会**全部落在小方格内**。

![](https://cdn.luogu.com.cn/upload/image_hosting/wsom7ode.png)

这就启发我们：为了求出一条直线最多穿过多少个正方形区域，我们可以转而去考虑当一条直线穿过由小区域拼成的长方形森林时**最多会产生多少个交点**，然后由交点数去**确定有多少根小线段**，进而通过线段的根数**确定会穿过的区域的个数**。

再让我们来考虑一个 $3 \times 3$ 的长方形森林的情况。我们不妨假设这条直线是从右上方至左下方穿过一个 $3 \times 3$ 的长方形，我们从两个方向来分析这条直线穿过这个长方形的情况：

1. 从上下来看，这条直线由下至上最多可穿过上下平行的 $2$ 条线段。

2. 从左右来看，这条直线最多可穿过左右平行的 $4$ 条线段。

故这条直线最多可穿过长方形森林中的 $2+4=6$ 条线段，从而这条直线上会产生 $6$ 个交点，这 $6$ 个交点之间的 $5$ 条线段每条会落在一个不同的正方形区域内，因此这条直线最多能经过 $5$ 个区域（如下图所示，涂黄色的正方形区域是会被直线穿过的区域）。

![](https://cdn.luogu.com.cn/upload/image_hosting/v1yk5t8f.png)

多举几个例子可以发现，对于一个 $n \times m$ 的长方形森林，一条直线总是能恰好地穿过 $n+m$ 条线段，那么这条直线上会产生 $n+m$ 个交点，这 $n+m$ 个交点之间的 $n+m-1$ 条线段每条会落在一个不同的正方形区域内，因此梦枫溪（一条直线）最多能经过 $n+m-1$ 个正方形区域。

#### 代码

$op=1$ 时的代码：

```cpp
cin >> n >> m;
cout << n + m - 1ll << endl;
```

### $op=2$ 的情况

$op=2$ 的情况需要在 $op=1$ 的情况得出的结论的基础上进行推导。

因为梦枫溪会穿过 $n+m-1$ 个区域，所以只要增加 $n$ 和 $m$ 即可。$n$ 增加 $1$，那么就要多出 $m$ 个区域；$m$ 增加 $1$，那么就要多出 $n$ 个区域。我们要得出**最少**添加多少个区域，所以当然要增加 $n$ 和 $m$ 中的最大值，使多出的区域数更少一些。因此，$n$ 和 $m$ 中大的一个要增加 $Q$ 和 $n+m-1$ 之差。故要使梦枫溪穿过 $Q$ 个区域，最少增加的区域个数为 $\min(n,m)\times[Q-(\max(n,m)+\min(n,m)-1)]=\min(n,m)\times(q-n-m+1)$ 个。同时，千万不要忘了取模这件事，因为数字很大，可能会爆 `long long`，所以要借助取模的性质 $a\times b\mod P=(a\mod P)\times(b\mod P)\mod P$，设 $K=998244353$，将公式改为：$\{[\min(n,m)\mod K]\times[(q-n-m+1)\mod K]\}\mod K$。可以将下图代入计算一下，$\{[\min(2,3)\mod K]\times[(10-2-3+1)\mod K]\}\mod K=12$，与样例中的答案一致。

![](https://cdn.luogu.com.cn/upload/image_hosting/phkx3o46.png)

#### 代码

$op = 2$ 时的代码：

```cpp
cin >> n >> m >> Q;
cout << ((min(n, m) % MOD) * ((Q - n - m + 1ll) % MOD)) % MOD << endl;
```

## 代码

本题的完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353ll;
ll n, m, Q;
int T, op;
int main() {
	cin >> T;
	while(T--) {
		cin >> op;
		if(op == 1) { 
			cin >> n >> m;
			cout << n + m - 1ll << endl;
		} else {
			cin >> n >> m >> Q;
        cout << ((min(n, m) % MOD) * ((Q - n - m + 1ll) % MOD)) % MOD << endl;
		}
	}
	return 0;
}
```

**注意要开 `long long`。**

完结撒花！

---

## 作者：I_am_kunzi (赞：0)

# P9552 题解

### 题目描述

记 $ f(n , m) = \text{一条直线穿过 } n \times m \text{ 的矩形能经过最多的方格}$，现在给你两种操作：

1. $ op = 1 $ 时，表示给你 $ n , m$，求出 $ f(n , m)$；

1. $ op = 2 $ 时，表示给你 $ n , m , q$，请找到 $ n' \ge n , m' \ge m$，使 $ f(n' ,  m') = q$，求出 $ n' \times m' - n \times m $ 的最小值。

对于每种操作，输出结果并以换行隔开。

### 题目思路

$ op = 1 $ 时，观察样例发现答案最大只能为 $ n + m - 1$，再大就像样例解释中只能经过顶点而不能穿过方块。

$ op = 2 $ 时，因为要求的 $ n' , m' $ 都要大于等于 $ n , m$，而通过上面的公式得出每当 $ n $ 或 $ m $ 扩大 $ 1 $ 时，答案都会增加 1，而当 $ n , m $ 都扩大 $ 1 $ 时，答案会增加 $ 2$，但是此时面积增大了 $ n + m + 1 $，相对来说花费的面积更多，答案一定不优，所以只考虑 $ n $ 或 $ m $ 扩大 $ 1$。我们让其中的最小值当宽，这样可以保证每次扩大时花费尽可能小。我们设 $ n , m $ 中较小一个为 $ n$，则根据题意得到 $ q = n' + m' - 1$，前文说过最小值当宽，所以变化的是长，而做宽的 $ n $ 长度一定不变，则公式变为 $ q = n + m' - 1$。此时可以求出 $ m' = q + 1 - n$。则最终答案为 $ n \times m' - n \times m$，即 $ n \times (m' - m)$。

### 题目代码

```cpp
#include<iostream>
using namespace std;
__int128 llfr() // 为方便读入和计算直接使用快读快输模板修改得到
{
	__int128 x = 0;
	bool sign = 0;
	char ch = getchar();
	while(!(ch >= 48 && ch <= 57) && ch != EOF)
	{
		if(ch == '-')
		{
			sign = 1;
		}
		ch = getchar();
	}
	while(ch >= 48 && ch <= 57)
	{
		x = (x << 1) + (x << 3) + (ch - 48);
		ch = getchar();
	}
	if(sign == 1)
	{
		return -x;
	}
	else
	{
		return x;
	}
}
void llfp(__int128 x)
{
	char st[105];
	int top = 0;
	if(x < 0)
	{
		putchar('-');
	}
	do
	{
		top++;
		if(x >= 0)
		{
			st[top] = (x % 10 + 48);
		}
		else
		{
			st[top] = (-(x % 10) + 48);
		}
		x /= 10;
	}
	while(x != 0);
	while(top != 0)
	{
		putchar(st[top]);
		top--;
	}
}
#define llfr llfr() // 宏定义使得不必写 ()，方便代码书写
#define int __int128 // 同上
signed main()
{
	int t = llfr;
	while(t--)
	{
		int opt = llfr;
		if(opt == 1)
		{
			int n = llfr , m = llfr;
			llfp(n + m - 1); // 计算公式
			cout << endl;
		}
		else
		{
			int n = llfr , m = llfr , q = llfr;
			if(n >= m) // 保证 n 为最短边，使后续结果正确
			{
				swap(n , m);
			}
			int mm = q + 1 - n; // mm 即为求出的 m'
			llfp((n * (mm - m)) % 998244353); // 记得最后 % 998244353
			cout << endl;
		}
	}
    return 0;
}
```

###### 后记：比赛时因为细节处理多交了十几遍，在此提醒大家做题注意细节处理！

---

## 作者：Genius_Star (赞：0)

### 题意：

设 $f(n,m)$ 表示一条直线最多能穿过 $n\times m$ 的网格图的格子数。

有两种询问方式：

1. 给定 $n,m$，求 $f(n,m)$；

2.  给定 $n,m,Q$，你需要找到 $n'\ge n,m'\ge m$，满足 $f(n',m')\ge Q$，且 $n'\times m'$ 尽可能小。求 $n'm'-nm$ 的最小值**对 $998244353$ 取模**的结果。数据保证 $f(n,m)<Q$。

### 思路：

我们先想一想怎么求 $f(n,m)$，找一下，规律画一图，发现最优的穿线方案肯定是从从左下角穿到右上角的直线就是经过最多的方格数，因为是从左下角穿到右上角，所以我们肯定会穿过 $m$ 列，然后发现每行对于上一行都有一个交叉的地方，则会有 $n-1$ 个交叉的地方，那么可以得到：
$$f(x)=n+m-1$$

现在考虑第二个问题，我们要找到一个 $n',m'$，使得 $f(n',m') = Q$，如果大于 $Q$ 的话，$n'$ 和 $m'$ 也会对应增大，乘积也会增大，所以考虑等于 $Q$ 的情况。

根据这个定理：就是当两个数的和固定时，它们越接近，积就越大。


因为我们要求积的最小值，所以我们要尽量让 $n',m'$ 隔得越开，而且要满足 $n'\ge n,m'\ge m$，我们考虑到，如果 $n'=n$ 的话，那么 $m'=Q-n+1$，我们注意到 $Q-n+1$ 中的 $n$ 越小，差距就越大，所以可以考虑令 $n'=\min(n,m),m=Q-\min(n,m)+1$，这样可以使得两者相差最大。

然后计算答案即可，直接乘好像要爆 long long，还是建议龟速乘。

时间复杂度：$O(T \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,op,n,m,k,t1,t2;
ll f(ll n,ll m){
   return (n+m-1ll);
}
ll X(ll x,ll y,ll p){
	ll sum=0;
	while(y){
		if(y&1ll)
		  sum=(sum+x)%p;
		x=(x<<1ll)%p;
		y>>=1ll;
	}
	return sum;
}
int main(){
	T=read();
	while(T--){
		op=read(),n=read(),m=read();
		if(op==1){
			write(f(n,m));
			putchar('\n');
		}
		else{
			k=read();
			k=(k-min(n,m)+1);
			write((X(min(n,m),k,mod)-X(n,m,mod)+mod)%mod);
			putchar('\n');
		}
	}
	return 0;
}
```


---

