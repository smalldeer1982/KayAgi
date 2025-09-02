# Alice's Adventures in Addition

## 题目描述

**注意不寻常的空间限制。**

柴郡猫给爱丽丝出了一个题：给定 $n$ 个整数 $a_1,a_2,\dots,a_n$ 和一个整数 $m$，能否在以下等式的 $\circ $ 中放入 $+$ 和 $\times$ 使得等式成立：

$$
a_1 \circ a_2 \circ \cdots \circ a_n = m
$$

我们遵循通常的运算顺序：$\times$ 在 $+$ 之前进行。

虽然爱丽丝的象棋下得很好，但她的数学却不好。请帮帮她，让她找到离开仙境的方法！

## 说明/提示

$1\le t\le 10^4$，$1\le n\le \sum n\le 2\times 10^5$，$1\le m\le 10^4$，$0\le a_i\le 10^4$。

## 样例 #1

### 输入

```
6
5 4
2 1 1 1 2
5 5
2 1 1 1 2
5 6
2 1 1 1 2
5 7
2 1 1 1 2
5 8
2 1 1 1 2
5 6
2 0 2 2 3```

### 输出

```
YES
YES
YES
YES
NO
YES```

# 题解

## 作者：ForgotMe (赞：4)

没抢到一血。10 min 就过了的老哥手速太快了。

比较套路的一道题。

简单转化一下题意就是把序列分成若干段，每段的权值为包含的数的乘积，问是否有一种分法使得权值和为 $m$。

有一个显然的 $\mathcal{O}(nm^2)$ 的 dp，直接设 $dp_{i,j}$ 表示分到了 $i$ 权值和是否能为 $j$。

注意到转移是枚举上一个分的位置 $x$，然后计算 $[x+1,i]$ 的乘积，进行背包的转移。一个关键的点是 $[x+1,i]$ 的乘积只有 $\log_2 m$ 种，那么只需要先把每一种乘积对应的所有背包先做一个或，再进行转移就行，这个过程可以使用 bitset 优化，复杂度 $\mathcal{O}(\frac{nm\log m}{w})$。

这个限制空间纯纯搞笑，显然不需要把 $n$ 个背包都存下来，只需要存 $\log_2 m$ 种乘积对应的背包即可，所以只需要开 $\log_2 m$ 个 bitset，32 MiB 完全够用。

给个代码：https://www.luogu.com.cn/paste/ypc8qs2x

---

## 作者：masonpop (赞：3)

自认为实现的比较优美。

首先思路应该是比较平凡的，我们设 $f_{i,j}$ 表示前 $i$ 个数算出 $j$ 是否可行。首先 DP 值是 boolean 的，且转移形式比较简单，可以 bitset 优化。然后就是注意到，当 $[j,i]$ 的乘积不超过 $m$ 时，一共只有 $O(\log)$ 种不同的取值，表现为先是一段 $0$，然后再从左往右递减。因此我们用一个 bitset 维护值相同的一段的 $f$ 的并即可。

着重讲讲实现。这里我额外用了一个 bitset 维护是 $0$ 的那一段，其余的段直接把值和 bitset 捆绑在一起丢进一个 deque 里面。当 $a_i=0$ 时就是清空队列然后并到是 $0$ 的那一段里（即代码中的 `zero`）。每次弹出队首值过大的段即可。需要注意的是这些段不能直接丢掉，因为之后遇到 $0$ 时有可能作为是 $0$ 的那一段重新投入使用，于是再使用一个临时 bitset 维护即可，对应代码中的 `Rub`。

这样写应该能少很多细节，也不用担心空间问题。[提交记录](https://codeforces.com/contest/2028/submission/299134455)。

---

## 作者：Albert_van (赞：1)

[题](https://www.luogu.com.cn/problem/CF2028F) [题](https://codeforces.com/problemset/problem/2028/F)。因为没有括号，所以这题就是要把序列分成若干段，问每段乘积之和是否可以 $=m$。

先考虑 $a$ 中只有 $\ge 2$ 的数怎么做。$\Theta(n^2m)$ 做法是令 $f(i,j)=1/0$ 表示 $a_1,\cdots,a_i$ 在添上符号后是否可以表示出 $j$，转移枚举 $k$ 将 $[k+1,i]$ 分为一段，即 $f(i,j)\gets f(k,j-\prod_{l=k+1}^i a_l)$，空间 $\Theta(nm)$。首先 $f$ 是 $0/1$ 数组且转移形如整体位移取或和，使用 bitset 可以把时间复杂度除掉 $w$。进一步，$\prod_{l=k+1}^i a_l$ 在 $k<i-\log_2 m$ 时 $>m$，因为整个过程从前往后枚举 $i$，所以对每个 $i$ 只需要考虑最近的 $\mathcal O(\log m)$ 个 $k$，拿个队列只记录这些 $k$ 的 $f(k,*)$ 即可，时空复杂度上均把一个 $n$ 换成了 $\log m$。

现在要处理 $a_i=1/0$ 的 corner case。考虑 $a_i=1$ 的极长段，令其长度 $s$，拿它和左侧最后一个 $\ge 2$ 的值 $a_L$ 拼起来，会发现对于 $a_1,\cdots,a_L$ 能表示的所有数 $j$，$j+p(p\in[0,s])$ 在拼上这个极长段后都能被表示（构造就是先把每个 $1$ 左侧都填上 $+$，然后任选 $s-p$ 个 $+$ 换成 $\times$）。于是无需新开 bitset，直接更新 $f(L,*)$ 即可，这一极长段不会影响区间 $\prod a_l$，后续 $k<L$ 的部分照常转移。$a_i=0$，就是给 $u>i$ 加上了一种转移 $f(u,j)\gets f(k,j)(k<i)$，开辅助 bitset 记录当前可以被直接复制的 $f(k,*)$ 即可。

时间 $\mathcal O\left(\frac{nm\log m}w\right)$，空间 $\mathcal O(m\log m)$。有人在 Editorial 下面骂这题无意义卡空间，宣称把范围改成 $n,m\le 5000$ 并开大空限可以在不改变此题核心 ideas&takeaways 的前提下大幅降低选手实现难度。这题不带 bitset 优化的话估计连 *2000 都没有了，但是在原数据范围下，可能确实倾向于这个空限是出题人一拍脑袋决定的，毕竟空间 $\Theta(nm)$ 的算法只需要 $256\text{MB}$ 不到。

```cpp
#include <cstdio>
#include <bitset>

std::bitset<10086> f[15],F,G;

int memo[15],tp,a[15],q[231231],h,t;

int main()
{
	int T;scanf("%d",&T);while(T--){
		for(tp=1;tp<15;++tp) memo[tp]=tp;
		--tp;f[q[h=t=0]=memo[tp--]].reset();
		F.reset();G.reset();F[0]=f[q[h]][0]=1;
		int n,m;scanf("%d%d",&n,&m);
		while(n--){int x;scanf("%d",&x);switch(x){
			case 0:G=f[q[t]]=F;break;
			case 1:F|=(f[q[t]]|=f[q[t]]<<1);break;
			default:{
				int c=memo[tp--],s=x,i=t;a[c]=x;f[c]=G;
				while(i>=h&&s<=m) f[c]|=f[q[i]]<<s,s*=a[q[i--]];
				F|=f[c];q[++t]=c;while(h<=i) memo[++tp]=q[h++];
			}
		}}
		puts(f[q[t]][m]?"Yes":"No");
	}
}
```

---

## 作者：cqj857699 (赞：0)

本文一些话引用了 ForgotMe 巨佬的话，侵删。

## 解题思路


### 状态设计

其实这道题的状态我们是可以轻松设出的。

我们定义 $f_{i,j}$ 为做到第 $i$ 个数，算出的数能否为 $j$。

### 状态转移

可以枚举上一个分的位置 $k$，计算 $[k+1,i]$ 的乘积，转移式可以轻松推出。

但这样做时间复杂度是 $O(n^2m)$ 的，不能通过本题。

考虑优化。

注意到 $[k+1,i]$ 的乘积只有 $\log_2 m$ 种，所以只需要先把每一种可能乘积对应的所有状态先做一个或，再进行转移就可以了。

但这样做时间复杂度为 $O(nm \log m)$ 还是通不过。

可以发现我们其实可以用 bitset 优化，这样做的时间复杂度为 $O(\frac{nm \log m}{w})$，可以跑过。

### 关于空限

这个空限是诈骗，因为只需开 $\log m$ 个 bitset，31.25 MiB 完全够用。

---

