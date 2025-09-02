# [ARC151C] 01 Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc151/tasks/arc151_c

マス $ 1 $ 、マス $ 2 $ 、$ \ldots $ 、マス $ N $ の $ N $ 個のマスがあり、 $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ についてマス $ i $ とマス $ i+1 $ は隣り合っています。

はじめ、$ M $ 個のマスには $ 0 $ または $ 1 $ が書かれています。 具体的には、$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、マス $ X_i $ に $ Y_i $ が書かれています。 また、その他の $ N-M $ 個のマスには何も書かれていません。

高橋君と青木君が $ 2 $ 人で対戦ゲームをします。 高橋君の先手で、$ 2 $ 人は交互に下記の行動を行います。

- まだ何も書かれていないマスを $ 1 $ つ選び、そのマスに $ 0 $ または $ 1 $ を書きこむ。 ただしその結果、ある $ 2 $ つの隣り合うマスに同じ数字が書かれた状態になってはならない。

先に行動することができなくなったプレイヤーの負けとなり、負けなかったプレイヤーの勝ちとなります。

両者がそれぞれ自身が勝つために最適な戦略をとる場合に、どちらが勝つかを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 0\ \leq\ M\ \leq\ \min\lbrace\ N,\ 2\ \times\ 10^5\ \rbrace $
- $ 1\ \leq\ X_1\ \lt\ X_2\ \lt\ \cdots\ \lt\ X_M\ \leq\ N $
- $ Y_i\ \in\ \lbrace\ 0,\ 1\rbrace $
- $ X_i\ +\ 1\ =\ X_{i+1}\ \implies\ Y_i\ \neq\ Y_{i+1} $
- 入力はすべて整数

### Sample Explanation 1

ゲームの進行の一例を示します。 1. 高橋君がマス $ 6 $ に $ 0 $ を書きこむ。 2. 青木君がマス $ 1 $ に $ 1 $ を書きこむ。 3. 高橋君がマス $ 7 $ に $ 1 $ を書きこむ。 その後、青木君はどのマスにも $ 0 $ または $ 1 $ を書きこむことが出来ないため、高橋君の勝ちとなります。

### Sample Explanation 2

ゲーム開始時点ですでにすべてのマスに $ 0 $ または $ 1 $ が書きこまれているため、先手の高橋君は行動できず青木君の勝ちとなります。

## 样例 #1

### 输入

```
7 2
2 0
4 1```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
3 3
1 1
2 0
3 1```

### 输出

```
Aoki```

## 样例 #3

### 输入

```
1000000000000000000 0```

### 输出

```
Aoki```

# 题解

## 作者：Leasier (赞：7)

显然可以把原问题分成若干没填的连续段来考虑，最后把它们的 SG 函数 xor 起来即可。

现在我们来讨论每一段的情况（长为 $len$），下文中设 $SG_{1/2/3/4}(len)$ 为长度为 $len$ 时，下列四种情况分别的 SG 函数。

- 没有左右边界：$SG_1(len) = len \bmod 2$。

- 只有一个边界：$SG_2(len) = len$。

- 两个边界处固定的数相同：$SG_3(len) = 1$。

- 两个边界处固定的数相不同：$SG_4(len) = 0$。

证明：首先我们有：

- $SG_1(0) = SG_2(0) = SG_4(0) = 0$，$SG_3(0) = 1$。

- $\forall len \geq 1, SG_1(len) = \operatorname{mex}_{i = 1}^{len} (SG_2(i - 1) \operatorname{xor} SG_2(len - i))$。

- $\forall len \geq 1, SG_2(len) = \operatorname{mex}_{i = 1}^{len} \operatorname{mex}(SG_2(i - 1) \operatorname{xor} SG_3(len - i), SG_2(i - 1) \operatorname{xor} SG_4(len - i))$。

- $\forall len \geq 1, SG_3(len) = \operatorname{mex}_{i = 1}^{len} \operatorname{mex}(SG_3(i - 1) \operatorname{xor} SG_3(len - i), SG_4(i - 1) \operatorname{xor} SG_4(len - i))$。

- $\forall len \geq 1, SG_4(len) = \operatorname{mex}_{i = 1}^{len} \operatorname{mex}(SG_3(i - 1) \operatorname{xor} SG_4(len - i), SG_4(i - 1) \operatorname{xor} SG_3(len - i))$。

随后不难归纳证明。

直接求出整体的 SG 函数并判断即可。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int y[200007];
ll x[200007];

int main(){
	int m;
	ll n, sg = 0;
	scanf("%lld %d", &n, &m);
	x[0] = 0;
	x[m + 1] = n + 1;
	for (int i = 1; i <= m; i++){
		scanf("%lld %d", &x[i], &y[i]);
	}
	for (int i = 0; i <= m; i++){
		ll len = x[i + 1] - x[i] - 1;
		if (i == 0 && i == m){
			sg ^= len % 2;
		} else if (i == 0 || i == m){
			sg ^= len;
		} else if (y[i] == y[i + 1]){
			sg ^= 1;
		}
	}
	if (sg != 0){
		printf("Takahashi");
	} else {
		printf("Aoki");
	}
	return 0;
}
```

---

## 作者：qzhwlzy (赞：2)

## 题目大意

有 $n$ 个格子，第 $i$ 与 $i+1$ 相邻。初始 $m$ 个格子里有 `0` 或 `1`，Takahashi 和 Aoki 轮流在没数字的格子里填 `0` 或 `1`，要保证相邻格子的数字不同，求谁赢。

## 思路

发现整个游戏被若干已存在的棋子分割成为若干个子游戏，考虑分别计算子游戏的 SG 值并计算异或和。

一个子游戏有且仅有四种情况。分别设 $f_1(n),f_2(n),f_3(n),f_4(n)$ 表示长度为 $n$ 的两端都没有、只有一端有、两端相同和两端不同的子游戏，则（注意 $f_3(0)$ 无意义，$\oplus$ 表示异或运算）：

$$
\begin{cases}
f_1(n) = \operatorname{mex}_{i=1}^n(f_2(i-1)\oplus f_2(n-i))\\
f_2(n) = \operatorname{mex}_{i=1}^n(f_2(i-1)\oplus f_3(n-i),f_2(i-1)\oplus f_4(n-i))\\
f_3(n) = \operatorname{mex}_{i=1}^n(f_3(i-1)\oplus f_3(n-i),f_4(i-1)\oplus f_4(n-i))\\
f_4(n) = \operatorname{mex}_{i=1}^n(f_3(i-1)\oplus f_4(n-i),f_4(i-1)\oplus f_3(n-i))\\
\end{cases}
$$

打表：

![](https://cdn.luogu.com.cn/upload/image_hosting/anzm61sl.png)

得到：$\begin{cases}f_1(n) = n\bmod 2\\f_2(n) = n\\f_3(n) = 1\\f_4(n) = 0\end{cases}$。考虑用归纳法证明：显然 $n = 0,1$ 时成立。假如 $0\sim n-1$ 时均成立，那么：

- 对于 $f_1(n) = \operatorname{mex}_{i=1}^n((i-1)\oplus(n-i))$：
在 $n$ 为奇数时，存在 $i = \dfrac{n+1}{2}$ 使得 $(i-1)\oplus(n-i) = \dfrac{n-1}{2}\oplus\dfrac{n-1}{2} = 0$，且不存在 $i$ 使得 $(i-1)\oplus(n-i) = 1$（假设存在，有 $\begin{cases}(i-1) + (n-i) = n-1\\(i-1)\oplus(n-i) = 1\end{cases}$，得到 $n-1$ 为奇数，矛盾），故此时 $f_1(n) = 1$；
在 $n$ 为偶数时，同理不存在 $i$ 使得$(i-1)\oplus(n-i) = 0$（假设存在，有 $\begin{cases}(i-1) + (n-i) = n-1\\(i-1)\oplus(n-i) = 0\end{cases}$，得到 $n-1$ 为偶数，矛盾），故此时 $f_1(n) = 0$。
- 对于 $f_2(n) = \operatorname{mex}_{i=1}^n((i-1)\oplus 1,(i-1)\oplus 0)$：
后者刚好取遍 $0\sim n-1$，又因为前者不可能等于 $n$（只有 $n$ 为奇数且 $i=n$ 时会等于，但是此时 $f_3(n-i)$ 无意义），所以 $f_2(n) = n$。
- 对于 $f_3(n) = \operatorname{mex}_{i=1}^n(1\oplus 1,0\oplus 0) = 1$；
- 对于 $f_4(n) = \operatorname{mex}_{i=1}^n(1\oplus 0,0\oplus 1) = 0$。

得证。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m,pos,col,lascol,sgs;
int main(){
    scanf("%lld%lld",&n,&m);
    if(m==0){if(n&1) printf("Takahashi"); else printf("Aoki"); return 0;} // 特判 m=0 的情况 
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&pos,&col);
        if(i==1) sgs=pos-1; else sgs^=(col==lascol);
        if(i==m) sgs^=n-pos; lascol=col; // 首尾两段的 SG 为长度，中间的为两端点是否相同 
    } if(sgs==0) printf("Aoki"); else printf("Takahashi");
    return 0;
}
```

---

## 作者：binbin_200811 (赞：0)

# ARC151C 01 Game

题目链接：[ARC151C 01 Game](https://www.luogu.com.cn/problem/AT_arc151_c)

$SG$ 函数好题。

#### 思路

考虑把原问题分成多个区间的不同问题，求 $SG$ 在异或起来。

设：
1.$SG_1(len)$ 长度为 $len$，边界没有数字。

2.$SG_2(len)$ 长度为 $len$，只有一个边界有数字。

3.$SG_3(len)$ 长度为 $len$，两个边界都有相同数字。

4.$SG_4(len)$ 长度为 $len$，两个边界都有不同数字。

初始有 $SG_1(0)=SG_2(0)=SG_4(0)=0,SG_3(0)=1$。

因为 $SG_3(0)$ 不存在，所以看做先手胜。

考虑枚举选择的点 $i$，有：

$$
SG_1(len)=\operatorname{mex}_{i=1}^{len}(SG_2(i-1) \oplus SG_2(len-i))
$$

$$
SG_2(len)=\operatorname{mex}_{i=1}^{len}\operatorname{mex}(SG_2(i-1) \oplus SG_3(len-i),SG_2(i-1) \oplus SG_4(len-i))
$$

$$
SG_3(len)=\operatorname{mex}_{i=1}^{len}\operatorname{mex}(SG_3(i-1)\oplus SG_3(len-i),SG_4(i-1) \oplus SG_4(len-i))
$$

$$
SG_4(len)=\operatorname{mex}_{i=1}^{len}\operatorname{mex}(SG_3(i-1)\oplus SG_4(len-i),SG_4(i-1) \oplus SG_3(len-i))
$$

然后我们通过打表发现：
$$
SG_1(len)=len\mod 2
$$

$$
SG_2(len)=len
$$

$$
SG_3(len)=1
$$

$$
SG_4(len)=0
$$

这个可以也可以通过上述方程归纳证明。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxn=2e5+5;

ll n;
ll x[maxn];

int m;
int y[maxn];

int main()
{
    scanf("%lld%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%lld%d",&x[i],&y[i]);
    x[0]=0,x[m+1]=n+1;
    ll sg=0;
    for(int i=0;i<=m;i++)
    {
        ll len=x[i+1]-x[i]-1;
        if(i==0&&i==m) sg^=(len&1);
        else if(i==0||i==m) sg^=len;
        else if(y[i]==y[i+1]) sg^=1;
    }
    if(sg) printf("Takahashi");
    else printf("Aoki");
}
```



---

