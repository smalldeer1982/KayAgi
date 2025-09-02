# Astrophysicists

## 题目描述

In many, many years, far, far away, there will be a launch of the first flight to Mars. To celebrate the success, $ n $ astrophysicists working on the project will be given bonuses of a total value of $ k $ gold coins.

You have to distribute the money among the astrophysicists, and to make it easier, you have to assign bonuses in silver coins. Each gold coin is worth $ g $ silver coins, so you have to distribute all $ k \cdot g $ silver coins among $ n $ people.

Unfortunately, the company has some financial troubles right now. Therefore, instead of paying the number of silver coins written on the bonus, they decided to round this amount to the nearest integer number of gold coins.

The rounding procedure is as follows. If an astrophysicist has bonus equal to $ x $ silver coins, and we denote $ r = x \bmod g $ , then:

- If $ r \geq \lceil \frac{g}{2} \rceil $ , the astrophysicist receives $ x + (g - r) $ silver coins;
- Otherwise, an astrophysicists receives $ x - r $ silver coins.

 Note that due to rounding, the total sum of actually paid money is not, in general, equal to $ k \cdot g $ silver coins. The operation $ a \bmod b $ denotes the remainder of the division of $ a $ by $ b $ . Sum of values before rounding has to be equal to $ k \cdot g $ silver coins, but some workers can be assigned $ 0 $ silver coins.You aim to distribute the bonuses so that the company saves as many silver coins due to rounding as possible. Please note that there is always a distribution in which the company spends no more than $ k \cdot g $ silver coins.

## 说明/提示

In the first test case, one of the optimal assignments could be the following:

- First person: $ x = 30 $ silver coins: company pays $ 0 $ , saves $ 30 $ silver coins,
- Second person: $ x = 140 $ silver coins: company pays $ 100 $ , saves $ 40 $ silver coins,
- Third person: $ x = 130 $ silver coins: company pays $ 100 $ , saves $ 30 $ silver coins.

In the second test case, we could have the following assignment:

- First person: $ x = 8 $ silver coins: company pays $ 14 $ , spends extra $ 6 $ silver coins,
- Second person: $ x = 6 $ silver coins: company pays $ 0 $ , saves $ 6 $ silver coins.

If the bonuses are assigned to $ 7 $ silver coins for both astrophysicists, then the company would have to pay an additional gold coin to cover the bonuses.

## 样例 #1

### 输入

```
5
3 3 100
2 1 14
91 2 13
36 16 6
73 8 22```

### 输出

```
100
0
26
72
176```

# 题解

## 作者：qwq___qaq (赞：3)

首先容易想到一个人最多向下舍入的是 $\lceil\dfrac{g}{2}\rceil-1$，那么我们考虑先让前面的人舍得最多，然后来弥补最后一个人。

那么我们就得到了这样一个序列：$\lceil\dfrac{g}{2}\rceil-1,\cdots,\lceil\dfrac{g}{2}\rceil-1,\max\{0,kg-(n-1)(\lceil\dfrac{g}{2}\rceil)\}$。

那么接下来我们考虑证明这个贪心策略：

- 若 $a_n$ 向下舍入，那么答案显然最优，因为舍入的已经达到了最多。

- 若 $a_n$ 向上进位，那么如果我们为了让 $a_n$ 不做出贡献，即让他舍入，此时 $a_n$ 减小，那么前面一定会存在一个元素 $a_k$ 增大，此时 $a_k$ 就会进位，并且 $a_n$ 最多也只能舍入 $\lceil\dfrac{g}{2}\rceil-1$ 个元素，那么此时调整 $a_n$ 显然不优。

时间复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,g;
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
	while(T--){
		cin>>n>>k>>g;
		int t=max(0ll,k*g-(n-1)*((g-1)/2));
		if(t%g>=(g+1)/2)
			cout<<(k-(t+g-1)/g)*g<<endl;
		else
			cout<<(k-t/g)*g<<endl;
	}
	return 0;
}
```

---

## 作者：Jeefy (赞：2)

# B.Astrophysicists

> 辛辛苦苦写了这么久的文章就没了？？？？烦死了。

> 自己做 Virtual Contest 的时候这道题打表打了半天（~~20min~~）才搞定……

## 题目大意

有 $n$ 个人，$k$ 个金币，每个金币价值 $g$ 个银币。

良心公司要把这 $k$ 个金币作为工资分给这 $n$ 个人，~~但是没有办法平均分配~~，良心老板想出了分配规则：

- 由你设定每个人分配的银币数 $x_i$。
  
- 你需要保证 $\sum_{i = 1}^n x_i = k \times g$。
  
- 老板会把银币数转化为金币发放，所以想出了以下规则：
  
  - 令 $r = x \bmod g$，如果 $r \ge \lceil \frac g2 \rceil$，那么公司会额外花费 $g - r$ 个银币以凑出完整的金币（此时花费了 $x + g - r$ 个银币）。
    
  - 反之，会吞掉这 $r$ 个银币以凑出完整的金币（此时花费了 $x - r$ 个银币）。
    

假定最终公司的花费为 $p$ 个银币。你需要最小化 $p$，并输出 $k \times g - p$。

## 解题思路

如果开始没有思路，那么打表是一个很好的方法。

首先我们可以很轻易的得到一个 $O(nkg)$ 的 DP 算法。

设 $f_{x, i}$ 表示处理到第 $x$ 个人，一共分配了 $i$ 个银币公司省下的最多银币。

有转移方程：

$$
f_{x, i} = \max_{0 \le j \le i} f_{x - 1, i - j} + w(j)
$$

其中：

$$
r = j \bmod g
$$

$$
w(j) = \begin{cases}
r - g &, r \ge \lceil \frac g2 \rceil \\
r &, r \lt \lceil \frac g2 \rceil
\end{cases}
$$

运行后输出 DP 数组，结合 $m = \lceil \frac g2 \rceil - 1$可以很轻易的发现规律：

最终的数组分为两个部分：

- 第一个部分为 $[0, nm]$，下标与数值一一对应。
  
- 第二部分为 $[-\lfloor \frac g2 \rfloor - m - nm, nm]$ 不断循环。
  

---

现在我们来严谨证明一下。

理想状态下，我们自然是给每一个人分发 $m = \lceil \frac g2 \rceil - 1$ 个银币，这样就可以吞掉 $nm$ 个银币。

但是可能存在一下两种情况：

- 其实根本没有 $nm$ 个银币，所以全部都分配到 $\le m$ 个。所以全部可以吞掉。对应上文中第一部分。
  
- 还剩下了 $r = k \times g - nm$ 个银币。由于我们可以按照一个金币为单位再分配，所以我们只需要关注 $r \mod g$ 的值。
  
  显然，如果把这些银币分给不同的人是不优的，因为破坏了老板吞掉更多人 $m$ 个银币的美梦。
  
  所以这些银币应该全部分配给一个人，对于答案做出贡献 $w(m + k \times g- nm) - m$。
  
  （~~化简一下~~）对应上文中第二部分。
  

提交记录：<https://codeforces.com/contest/1836/submission/211134556>

---

## 作者：_Only_this (赞：1)

### CF1836B Astrophysicists 题解

------------

此题一开始觉得比较麻烦，但写起来其实还可以，就是个贪心。

先将所有金币换成银币，容易想到，最理想的情况无非就是给所有人的银币数量 $\bmod g$ 刚好等于 $\lceil \frac{g}{2} \rceil -1$。

当然，这样想可能不会将所有的银币全发完，因此，考虑将剩下的银币全发给一个人，使得损失尽可能小。

另外，可能最理想的情况为公司省的银币数 $>$ 银币总数，那么答案就是银币总数了，因为经过特定的四舍五入后工人们将连一个银币都拿不到（黑心的四舍五入，大家快谴责这个公司）。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n,k,g;
inline ll Solve(){
	ll mx=(g+1>>1)-1,res=0;
	if(k*g<=mx*n){
		return k*g;
	}
	ll d=k*g-mx*n;
	d%=g;
	if(!d){
		res+=mx*n;
	}
	else{
		if(mx+d<g){
			res-=g-mx-d;
		}
		else{
			res+=(mx+d)%g;
		}
		res+=mx*(n-1);
	}
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&k,&g);
		printf("%lld\n",Solve());
	}
	return 0;
}
```


---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1836B Astrophysicists

[题目传送门](/problem/CF1836B)

## 思路

数学题。

最优方案一定是对于任意一个 $i$，$x_i$ 赋值为 $\lfloor g \div 2 \rfloor$。

但这会产生两种情况：

1. 银币没有发完。

2. 公司省下来的银币总数大于银币总数。

第一种比较好解决，全发给第一个人。第二种也一样，~~化身奸商~~，一个银币也不发。

## 代码

详见[提交记录](https://mirror.codeforces.com/problemset/submission/1836/278459944)。

---

## 作者：liyp (赞：0)

很简单的数学题。

可以很容易地推出来，最优方案肯定是对于**任意一个** $i$ 所对应的 $x_i$，刚好就等于 $ \lceil \frac g2 \rceil - 1$。但是这会产生以下两种特殊情况：

1. 当我们按照最优方案处理时，银币**没有全部发完**；
   
2. 当我们按照最优方案处理时，公司省下来的银币总数大于银币总数。

第一种问题其实很好解决，直接把多余的银币**全部发给一个人即可**。第二种问题则需要进行分析，解决方法也较容易想到，就是直接让工人们一个银币都不拿。

本题代码好写，但较长，这里就不放了。

---

## 作者：Norsuman371 (赞：0)

# 思路

## 第一种情况
假设每个人分的钱都为 $h$ 则最理想的情况为 $h \times n \geq k \times g$ 且 $h < g \div 2$，即 $h = g \div 2 - 1$。

如果符合此条件可以直接输出总数 $k \times g$。

## 第二种情况
如每个人分的钱均小于 $g \div 2$ 但是总数加起来不够，分析可得每个人分的钱 

$$h_i = a_i \times g + r_i$$

$$h_1 + h_2 ... + h_n = k \times g$$

$$(a_1 + a_2 + ... + a_n) \times g + r_1 + r_2 ... + r_n = k \times g$$

$$\sum r_i = (k - \sum a_i) \times g$$

由此可以看出个余数之和一定为 $g$ 的倍数，第一种情况下 $a_i$ 全为 $0$ 即都是小于 $g \div 2$ 的数。

所以为了节省更多的钱尽量向第一种情况靠近即求得不大于 $(g \div 2 - 1) \times n$ 的 $g$ 的最大倍数,使得 $\sum r$ 最大，$\sum a$ 最小。

---

## 作者：Natori (赞：0)

>[CF1836B Astrophysicists](https://www.luogu.com.cn/problem/CF1836B)

先将所有金币换算成银币。我们尽量让所有人的工资都是 $\left\lceil\dfrac{g}{2}\right\rceil-1\pmod g$，此时只需要考虑最后一个人拿多少。

这种方法可能不会将所有的银币全发完，但是可以将剩下的银币全发给一个人，使得损失尽可能小。因为前面的人都取到了不补银币的上限，所以最后一个人取 $k\times g-(n-1)\times \left\lceil\dfrac{g}{2}\right\rceil$ 一定是最优的。

我们把 $\left\lceil\dfrac{g}{2}\right\rceil-1$ 设为 $x$，注意如果 $n\times x\ge k\times g$，说明所有的员工被发到的工资 $\le x$，这样就不用再发银币补差值了，所以此时答案为 $k\times g$。

至此可以 $\mathcal{O}(1)$ 回答每次询问。

---

