# 【MX-X7-T6】[LSOT-3] 棋盘

## 题目背景

原题链接：<https://oier.team/problems/X7G>。

现在有一个序列。

这个序列第 $1$ 项为 $0$，第 $2$ 项为 $1$，第 $3$ 项为 $1$，第 $4$ 项为 $3$。

现在 [@lxwtr](https://www.luogu.com.cn/discuss/875194) 问你第 $n$ 项的值为多少。

## 题目描述

Alice 和 Bob 找到了一个棋盘。棋盘可以看成一个数轴，初始时在原点处有 $n$ 个棋子。令 $a_i$ 表示数轴下标为 $i$ 的位置的棋子数量（原点 $i=0$），操作者每次会找到最小的满足 $a_i\ge 2$ 的 $i$，令 $a_i$ 减去 $2$ 并选择令 $a_{i+1}$ 加上 $1$ 或令 $a_{i+2}$ 加上 $1$。由 Alice 先手，二人轮流操作。操作者必须操作，如果无法找到这样的 $i$ 则立即结束游戏。

Alice 希望二人的总操作次数最少，Bob 希望二人的总操作次数最多，二人都是绝对聪明的。二人一共进行了 $T$ 次游戏，你希望知道每次游戏最终二人一共会进行多少次操作。

## 说明/提示

**【样例解释】**

对于第一次游戏，原点棋子数为 $1$，无法进行操作。

对于第二次游戏，可以恰好进行一次操作之后使得 $a_1=1$ 或 $a_2=1$。无论哪一种都无法继续操作。

对于第三次游戏，类似第二次游戏，额外在原点留下了一个棋子。

对于第四次游戏，第一次操作无论 Alice 操作后将棋子放在哪个位置，Bob 都可以放在那个位置，这样 Alice 会再进行一次操作。总共 $3$ 次操作。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（5 分）：$n\le16$。
- 子任务 2（6 分）：$n\le 50$。
- 子任务 3（14 分）：$n\le 200$。
- 子任务 4（20 分）：$n\le 5000$。
- 子任务 5（21 分）：$n\le 10^5$。
- 子任务 6（34 分）：无特殊性质。

对于全部的数据，$1\le T\le 500$，$1\le n\le 10^{18}$。

## 样例 #1

### 输入

```
6
1
2
3
4
100
100000
```

### 输出

```
0
1
1
3
95
99989
```

# 题解

## 作者：良心WA题人 (赞：9)

因为只能操作最左侧的棋子，则抛开无法操作的位置，只会有位置 $i,i+1,i+2$ 有值。

记 $f_{i,j,k,l,0/1}$ 表示位置 $i,a_i=j,a_{i+1}=k,a_{i+2}=l$，当前操作者是 Alice/Bob 时的操作次数。有转移 

$$\left\{\begin{matrix} 
  f_{i,j,k,l,0}=\min(f_{i,j-2,k+1,l,1},f_{i,j-2,k,l+1,1})+1\ (j\ge 2) \\  
  f_{i,j,k,l,0}=f_{i+1,k,l,0,0}\ (j<2)
\end{matrix}\right. $$

最后一维为 $1$ 时同理。

注意到第一维最多只会有 $2\times \log n$ 次就会变成 $0$，所以只需要枚举到 $2\times\log n$ 即可。

然后发现貌似不太好优化了。注意到，当前位置无论如何操作，操作次数都是固定的。可以考虑位置 $i$ 会分别操作多少个到后面的位置。

> Key Lemma: $a_i$ 个棋子除了最后一轮操作以外，无论 $a_{i+1}$ 和 $a_{i+2}$ 一开始放了多少个，每轮一定是 Alice 和 Bob 分别在 $a_{i+1}$ 和 $a_{i+2}$ 各放一个。

此时去掉原 dp 第三维，令最终放置 $a_{i+1}$ 了 $k$ 个，若假设定理成立，令 $t=f_{i+1,a_{i+1}+k,a_{i+2}+\left\lfloor \frac{a_i}{2}\right\rfloor-k,?}$（问号由当前状态的先后手和 $\left\lfloor \frac{a_i}{2}\right\rfloor$ 奇偶性决定）。

考虑反证法，若最后结果 $f_{i+1,a_{i+1}+k,a_{i+2}+\left\lfloor \frac{a_i}{2}\right\rfloor-k,?}\le t$，则最终情况对 Alice 有利，此时假设 $k\ge \left\lfloor \frac{a_i}{2}\right\rfloor-k$（另一种同理）：
- 若 $k-(\left\lfloor \frac{a_i}{2}\right\rfloor-k)\le 2$，此时可以通过除最后一轮外二人轮流在 $a_{i+1}$ 和 $a_{i+2}$ 放置来达到，则有 $f_{i+1,a_{i+1}+k,a_{i+2}+\left\lfloor \frac{a_i}{2}\right\rfloor-k,?}= t$，原命题得证。
- 若 $k-(\left\lfloor \frac{a_i}{2}\right\rfloor-k)> 2$，则 $2\times k>2+\left\lfloor \frac{a_i}{2}\right\rfloor$，$k>1+\left\lfloor \frac{a_i}{4}\right\rfloor$。而一个人在一轮操作中最多进行 $\left\lfloor \frac{a_i}{4}\right\rfloor+1$ 次操作，则在放置 $a_{i+1}$ 的棋子中必然有 Bob 参与，此时可以让 Bob 参与操作的棋子放到 $a_{i+2}$ 使得最终结果不为 $f_{i+1,a_{i+1}+k,a_{i+2}+\left\lfloor \frac{a_i}{2}\right\rfloor-k,?}$，与假设相悖，所以原命题得证。

此时可以得知在最后一轮之前，$a_{i+1}$ 和 $a_{i+2}$ 各增加了 $\left\lfloor\dfrac{\left\lfloor \frac{a_i}{2}\right\rfloor-1}{2}\right\rfloor=tmp$。考虑 $\left\lfloor \frac{a_i}{2}\right\rfloor$ 的奇偶性（下面假设是 Alice 先操作，Bob 操作同理）：
- 奇数：最后一步是先手操作，则先手可以决定最后放在 $a_{i+1}$ 还是 $a_{i+2}$。转移 $f_{i,j,k,0}=\min(f_{i+1,k+tmp+1,tmp,1},f_{i+1,k+tmp,tmp+1,1})$。
- 偶数：最后一步是后手操作，则后手可以选择是让二者相等还是其中一个多 $2$。若后手会选择让其中一个多 $2$，则先手会为了让后手更小于是会选择更小的一个。转移 $f_{i,j,k,0}=\max(f_{i+1,k+tmp+1,tmp+1,0},\min(f_{i+1,k+tmp+2,tmp,0},f_{i+1,k+tmp,tmp+2,0}))$。

注意到，有用的 $j,k$ 两维看上去是很少的！事实上也确实如此。

可以看出在 $j+k$ 相同时，前一个访问后一个位置的 $j-k$ 的值是连续的。则只有 $j-k$ 是最大值和最小值时在下一维才会产生多出来的状态数。每一个位置多出来两个，一共多出来 $\log n$ 级别个，每个会进行 $\log n$ 级别次转移，所以是 $\log^2 n$ 级别的。

而 $j+k$ 的个数最多会有多少呢？类似的，一次只会以原来的基准多或少 $1$，所以也是连续的且只有最大和最小的会扩展出新的，是 $\log n$ 级别的。

总时间复杂度 $O(\log^3 n)$。使用 `map` 是 $O(\log^4 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<tuple<int,int,int,int>,int>f;
int dp(int i,int j,int k,int l)
{
	if(f.count({i,j,k,l}))
		return f[{i,j,k,l}];
	int&d=f[{i,j,k,l}];
	if(!j&&!k)
		return d=0;
	int t=j/2;
	if(t%2)
	{
		if(!l)
			return d=min(dp(i+1,k+t/2,t/2+t%2,1),dp(i+1,k+t/2+t%2,t/2,1))+t;
		return d=max(dp(i+1,k+t/2,t/2+t%2,0),dp(i+1,k+t/2+t%2,t/2,0))+t;
	}
	d=dp(i+1,k+t/2,t/2,l)+t;
	if(t/2)
	{
		if(!l)
			d=max(d,min(dp(i+1,k+t/2-1,t/2+1,0),dp(i+1,k+t/2+1,t/2-1,0))+t);
		else
			d=min(d,max(dp(i+1,k+t/2-1,t/2+1,1),dp(i+1,k+t/2+1,t/2-1,1))+t);
	}
	return d;
}
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		int n;
		scanf("%lld",&n);
		printf("%lld\n",dp(1,n,0,0));
	}
	return 0;
}
```

---

