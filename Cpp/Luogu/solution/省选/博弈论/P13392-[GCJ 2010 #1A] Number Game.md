# [GCJ 2010 #1A] Number Game

## 题目描述

Arya 和 Bran 正在玩一个游戏。最初，黑板上写着两个正整数 $A$ 和 $B$。两位玩家轮流行动，Arya 先手。在每一回合，玩家可以将 $A$ 替换为 $A - k \times B$（$k$ 为任意正整数），或者将 $B$ 替换为 $B - k \times A$（$k$ 为任意正整数）。第一个使得其中一个数变为零或负数的人输掉游戏。

例如，如果初始数字为 $(12, 51)$，游戏过程可能如下：

- Arya 将 $51$ 替换为 $51 - 3 \times 12 = 15$，黑板上变为 $(12, 15)$。
- Bran 将 $15$ 替换为 $15 - 1 \times 12 = 3$，黑板上变为 $(12, 3)$。
- Arya 将 $12$ 替换为 $12 - 3 \times 3 = 3$，黑板上变为 $(3, 3)$。
- Bran 将其中一个 $3$ 替换为 $3 - 1 \times 3 = 0$，Bran 输掉游戏。

我们称 $(A, B)$ 为“必胜态”，如果 Arya 无论 Bran 如何应对，都能保证获胜。

给定四个整数 $A_1$、$A_2$、$B_1$、$B_2$，请统计有多少个 $(A, B)$ 是必胜态，且满足 $A_1 \leq A \leq A_2$ 且 $B_1 \leq B \leq B_2$。

## 说明/提示

**数据范围**

- $1 \leqslant T \leqslant 100$。
- $1 \leqslant A_1 \leqslant A_2 \leqslant 1,000,000$。
- $1 \leqslant B_1 \leqslant B_2 \leqslant 1,000,000$。

**小数据（16 分，测试点 1 - 可见）**

- 时间限制：3 秒。
- $A_2 - A_1 \leqslant 30$。
- $B_2 - B_1 \leqslant 30$。

**大数据（25 分，测试点 2 - 隐藏）**

- 时间限制：9 秒。
- $A_2 - A_1 \leqslant 999,999$。
- $B_2 - B_1 \leqslant 999,999$。
- 无其他限制。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5 5 8 8
11 11 2 2
1 6 1 6```

### 输出

```
Case #1: 0
Case #2: 1
Case #3: 20```

# 题解

## 作者：_2eyks (赞：1)

我们先考虑，对于一个固定初始状态 $(a,b)$，如何判断先手是否必胜。这里假设 Alice 是先手，Bob 是后手。不妨设 $a\geq b$。

- 当 $a\geq2b$ 时，Alice 是必胜的。
  - 假设 $(a\bmod b,b)$ 是先手必败的状态，则 Alice 可以一步操作将 $(a,b)$ 转到 $(a\bmod b,b)$，所以 Alice 此时是必胜的。
  - 反之，Alice 可以一次操作得到 $(a\bmod b+b,b)$，那么 Bob 下次操作只能转到 $(a\bmod b,b)$，Alice 仍然必胜。
- 反之，由于策略唯一，可以考虑递归求解。

然而这样的暴力做法复杂度是 $n^3$ 的，不足以通过此题。

通过跑暴力程序打表可以发现，当 $a$ 固定时，对于一个 $b$，其先手胜负性是单调的。换句话说，对于固定的正整数 $a$，存在一个数 $k$，使得对于任意的正整数 $i$，满足当 $i\geq k$ 时，$(a,i)$ 这个状态是 Alice 必胜的；反之则是必败。

考虑如何用上面推出的结论（$a\geq2b$ 时先手必胜）证明这个东西，仍然假设初始状态为 $(a,b)$：

- 当 $a\geq2b$ 即 $\frac{a}{b}\geq2$ 时，Alice 是必胜的。
- 反之，$(a,b)\to(b,a-b)$，并继续递归情况：
  - 当 $b\geq2(a-b)$ 即 $\frac{a}{b}\leq\frac{3}{2}$ 时，Bob 必胜。
  - 反之，$(b,a-b)\to(a-b,2b-a)$ 继续递归：
    - 当 $(a-b)\geq2(2b-a)$ 即 $\frac{a}{b}\geq\frac{5}{3}$ 时，Alice 必胜。
    - 反之，类似地改变状态，继续递归……

容易发现对于每次递归，对应不等式中右侧的分数为相邻两项 fibonacci 数列相除后的结果。而对于 fibonacci 数列，其相邻两项相除后的结果正好是黄金比例数，即 $\frac{1+\sqrt5}{2}$。所以，枚举每个 $a$，判断 $b\geq\frac{1+\sqrt5}{2}$ 的 $b$ 的总数即可。

实际实现的时候需要分别枚举 $a$ 和 $b$ 来处理，因为不保证 $a\geq b$。

```cpp
#define fo(i,l,r) for(int i=l;i<=r;i++)
const double alpha=(1+sqrt(5))/2.0;
void solve(){
    int al,ar,bl,br,rs=0;
    cin>>al>>ar>>bl>>br;
    fo(i,al,ar){
        int x=ceil(i*alpha);
        if (x<=bl) rs+=br-bl+1;
        else if (x<=br) rs+=br-x+1;
    }
    fo(i,bl,br){
        int x=ceil(i*alpha);
        if (x<=al) rs+=ar-al+1;
        else if (x<=ar) rs+=ar-x+1;
    }
    cout<<rs<<'\n';
}
```

---

## 作者：L_zaa_L (赞：0)

神秘的博弈论。

首先我们先考虑一个东西就是每个 $(A,B)$ 什么时候必胜。一个比较显然的假如 $\max(A,B)\ge2\times \min(A,B)$ 那么先手必胜。


证明比较简单，首先假设 $A>B$，那么如果 $(B,A\bmod B)$，是一个先手必败态，那么此时先手就可以将 $A\to A\bmod B$，如果不是，先手将 $A\to A\bmod B+B$，此时后手一定将只能将 $A\bmod B+B\to A\bmod B$，因为如果后手操作 $B$ 一定直接输。 

所以这种情况我们是很好判断的，然后就是 $\max(A,B)< 2\times \min(A,B)$，先默认 $A>B$，然后我们发现 $(A,B)\to(B,A-B)$ 实际上是最优的，其他操作都会使操作者输掉，那么就一直这么操作，直到 $A\ge 2\times B$（$B$ 不可能小于 $0$，而 $B=0$ 时也满足 $A\ge 2\times B$）。

然后就有可以判断先手必胜的代码：

```cpp

bool solve(int a,int b){
	if(a<b) return solve(b,a);
	if(a>=2*b) return 1;
	return 1-solve(b,a-b);
}
```

然后发现我们暴力求所有的先手必胜的情况肯定是会超时的，于是我们考虑只枚举一个数字，然后考虑求出另外一个数的取值范围。

现在有两个数 $(A,B)$：

1. 先手操作 $(A,B)$，然后如果 $(A\ge 2\times B)\Rightarrow (\frac{A}{B}\ge 2)$，那么先手必胜，否则变为 $(B,A-B)$。
2. 后手操作 $(B,A-B)$，然后如果 $B\ge 2\times(A-B)\Rightarrow (\frac{A}{B}\le\frac{3}{2})$，则后手必胜，否则变为 $(A-B,B-(A-B))$。
3. 先手操作 $(A-B,2\times B-A)$，然后如果 $(A-B\ge 2\times (2\times B-A))\Rightarrow (\frac{A}{B}\ge \frac{5}{3})$，那么先手必胜，否则变为 $(2\times B-A,2\times A-3\times B)$。
4. 如果 $\frac{A}{B}\le \frac{8}{5}$ 则后手必胜。
5. 如果 $\frac{A}{B}\ge \frac{13}{8}$ 则先手必胜。
6. $\dots$

一直这么推，我们发现没有判断胜负范围是越来越小的，胜负的两个界限分母分子都是斐波那契，且都是 $\frac{Fib(i+1)}{Fib(i)}$。有一个结论就是，如果 $i$ 足够大，$\frac{Fib(i+1)}{Fib(i)}$ 越趋近 $\frac{1+\sqrt{5}}{2}$。所以如果 $\frac{A}{B}\ge \frac{1+\sqrt{5}}{2}$ 先手必胜，否则后手必胜。

所以你对于每个数，可以得到另一个数的必胜取值范围，随便写一些就过了。

## 核心代码

```cpp

	int T=read();
	For(test,1,T){
		int l=read(),r=read();
		int L=read(),R=read();int ans=0;
		For(b,L,R){
			int p=ceil((1.0+sqrt(5.0))*b/2.0);
			if(p<=r){
				p=max(p,l);
				ans+=(r-p+1);
			}
		}
		For(a,l,r){
			int p=ceil((1.0+sqrt(5.0))*a/2.0);
			if(p<=R){
				p=max(p,L);
				ans+=(R-p+1);
			}
		}
		printf("Case #%lld: %lld\n",test,ans);
	}
```

---

