# [CCC 2023 S3] Palindromic Poster

## 题目描述

Ryo 和 Kita 正在为 Kessoku Band 设计一张新海报。经过一番激烈的头脑风暴，他们得出结论，海报应该以一个 $2\text{-D}$ 的小写英文字母网格（即 `a` 到 `z`）的形式出现，具有 $N$ 行和 $M$ 列。

此外，已知 Ryo 和 Kita 都对回文有独特的品味。Ryo 只有在海报的行中恰好有 $R$ 行是回文时才会满意，而 Kita 只有在海报的列中恰好有 $C$ 列是回文时才会满意。你能设计出一张同时满足 Ryo 和 Kita 的海报，或者确定这是不可能的吗？

**注意**：如果一个字符串正反读都是一样的，则认为它是回文。例如，`kayak` 和 `bb` 是回文，而 `guitar` 和 `live` 不是。

## 说明/提示

对于样例输入 $1$ 的输出解释：

在给定的设计中，只有第二行（即 `radar`）和第二、第三列（即 `naan` 和 `iddi`）是回文。由于恰好有 $R = 1$ 行和 $C = 2$ 列是回文，这是一种可接受的设计。

对于样例输入 $2$ 的输出解释：

在这种情况下，可以证明不可能同时满足 Ryo 和 Kita。

**本题采用捆绑测试**：

- 子任务 1（2 分）：数据保证 $2 \leq N \leq 2000$，$2\leq M\leq 2000$，$R = 1$，$C = 1$。

- 子任务 2（2 分）：数据保证 $N = 2$，$M = 2$，$0\leq R\leq N$，$0\leq C\leq M$。

- 子任务 3（4 分）：数据保证 $N = 2$，$2\leq M \leq2000$，$0\leq R\leq N$，$0\leq C\leq M$。

- 子任务 4（7 分）：数据保证 $2\leq N\leq 2000$，$2\leq M \leq2000$，$0\leq R\leq N$，$0\leq C\leq M$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 5 1 2```

### 输出

```
union
radar
badge
anime```

## 样例 #2

### 输入

```
2 2 2 1```

### 输出

```
IMPOSSIBLE```

# 题解

## 作者：RAY091016 (赞：2)

（upd on 2025.1.20，修改了部分特殊点的做法。）

## 1. 题目解释

求一个有 $r$ 行回文字符串和 $c$ 列回文字符串的 $n\times m$ 字符矩阵。

## 2. 思路

（一道规律题让我调吐了）

考虑对 $r$，$c$ 分类讨论。

### Part 1

当 $r=0,c=0$ 时。

只需有 $a_{i,j}$ 等于第 $(i+j-1)\bmod26$ 个字母即可，证明比较显然。

举例：$n=3,m=4,r=0,c=0$。

```
abcd
bcde
cdef
```

### Part 2

当 $r=0,c=m$ 时。

只需有 $a_{i,j}$ 等于第 $i$ 个字母即可，证明也不难。

举例：$n=3,m=4,r=0,c=4$。

```
abcd
abcd
abcd
```

### Part 3

当 $r=0,0<c<m$ 时。

不难想到将 Part $1$ 的前 $c$ 列填充同一字母，其余与 Part $1$ 相同。

举例：$n=3,m=4,r=0,c=2$。

```
abcd
abde
abef
```

### Part 4

当 $r=n,c=0$ 时。

与 Part $2$ 原理相同，只是 $n$ 和 $m$ 互换，$r$ 和 $c$ 互换。

举例：$n=3,m=4,r=3,c=0$。

```
aaaa
bbbb
cccc
```

### Part 5

当 $r=n,c=m$ 时。

只需填充同一种字符即可。

举例：$n=3,r=4,r=3,c=4$。

```
aaaa
aaaa
aaaa
```

### Part 6

当 $r=n,0<c<m$ 时。

首先考虑不不合法的情况。

先给结论：当 $2\mid m,2\nmid c$ 时不合法，原因待会再说。

给出其余情况的构造方式：

当 $2\mid m,2\mid c$ 时，将 $1$ 至 $\dfrac{c}{2}$ 列与 $m-\dfrac{c}{2}+1$ 至 $m$ 列的字符全部赋为 `a`，将 $2$ 至 $n$ 行的字符全部赋为 `a`，其余赋为 `b`。

举例：$n=3,m=4,r=3,c=2$。

````
abba
aaaa
aaaa
````

当 $2\nmid m,2\mid c$ 时同理（只是 $\dfrac{c}{2}$ 变为 $\dfrac{c-1}{2}$）。

举例：$n=3,m=3,r=3,c=2$。

```
aba
aaa
aaa
```

当 $2\nmid m,2\nmid c$ 时只需将最中间一列赋为 `a` 也就一样了。

举例：$n=3,m=3,r=3,c=1$。

```
bab
aaa
aaa
```

最后解释不合法构造的原因：由于 $2\mid m,2\nmid c$，故而我们需要将 $c$ 列赋为 `a`，而一行的字符数量为偶数，假如它是回文的，那么 `a` 的数量也应该是偶数个，又 $2\nmid c$，因而不合法。

### Part 7

当 $0<r<n,c=0$ 时。

与 Part $3$ 原理相同。

### Part 8

当 $0<r<n,c=m$ 时。

与 Part $6$ 原理相同。

### Part 9

当 $0<r<n,0<c<m$ 时。

只需将前 $r$ 行和前 $c$ 列的字符全部赋为 `a`，其余赋为 `b` 即可。

举例：$n=3,m=4,r=1,c=2$。

```
aaaa
aabb
aabb
```

### Part 10

对于 $n$ 或 $m$ 等于 $2$ 时的一个特殊情况补充。

另外感谢 @tyr_04 帮忙指出。

当 $n=2,c=0,r\ge26$ 时，使用上面的方法会出现如下情况：

```
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
bcedfghijklmnopqrstuvwxyzabcde
```

注意到第 $26$ 列有两个 `a`。

于是我们将下方修改为第 $(i-1)\bmod25+2$ 个字母即可。 

代码不放了，其实不难写。

---

## 作者：Larry76 (赞：2)

## 前言

更好的阅读体验：[隙间传送](https://www.cnblogs.com/larry76/p/17601548.html)

### 数学符号约定

$n$：任意正整数。

$\#$：从未出现过的小写字母。

$\Sigma$：字符集，这里指小写字母集合。

$S$：最终答案的字符矩阵。

其余符号同题目翻译中所写。

如非特殊说明，将会按照上述约定书写符号。

## 题目大意

构造一个 $N\times M$ 的小写字母矩阵，使得其中有 $R$ 行 $C$ 列是回文串，如果无解，输出 `IMPOSSIBLE`。

## 题目分析

首先，让我们仔细阅读一下题目，然后可以得到一个比较显然的性质，就是在 $R\lt N$ 和 $C \lt M$ 的时候我们行回文串与列回文串的位置是**不重要**的，也就是位置无关，可以放到任意位置。证明比较显然，考虑我们如果想要满足任意列数 $C\;(C\lt N)$ 的话至多会使得一行无法形成回文串，但是此时目标要求 $R \lt N$ 即 $R_{\max} = N-1$，所以能够达到题目要求。

所以，我们现在考虑一下 $R\lt N$ 且 $C \lt M$ 的情况下怎么填。考虑让我们的回文串填的暴力一点，即全都填一个字符，这个时候我们预期达到的效果如图所示：

![pPPKnVx.png](https://s1.ax1x.com/2023/08/02/pPPKnVx.png)

其中，蓝色部分全填的字符 $\#$，橙色部分所填字符比较复杂，它的填写规则是这样的：

> 对于第 $i$ 行第 $j$ 列（这里的 $i,\,j$ 是相对于橙色矩形的第 $i$ 行第 $j$ 列）填写字符 $(i+j) \bmod (|\Sigma| - 1)$。

可以证明，根据上述填写方法，能够保证第 $R+1 \sim N$ 行和第 $C+1\sim M$ 列不会出现回文串，理由如下：

> 考虑回文串的定义，如果我们想让第 $i$ 行字符串为回文串，则需要满足下面条件：
>
> $$ \forall j \in [1,M]\qquad S_{i,j} = S_{i,M-j+1} $$
>
> 现在我们 $S_{i,j}$ 位置上的字符进行分类讨论：
>
> 1. 如果 $S_{i,j} = \#$，则显然当前字符串不为回文串，理由如下：
>
>    如果 $S_{i,j} = \#$ 且 $S_{i,j} = S_{i,M-j+1}$，由于橙色部分不可能出现 $\#$，则说明 $C = M$，不符合前置条件 $C\lt M$，故不成立。
>
> 2. 如果 $S_{i,j} \not= \#$，则说明 $C=0$，那么证明 $S_{i,j} = S_{i,M-j+1}$，就等价于证明：
>    $$ \forall j\in [1,M]\qquad i+j \equiv i+M-j+1 \pmod{|\Sigma| -1} $$
>    移项，可以得到：
>
>    $$\forall j\in [1,M]\qquad 2j \equiv M+1 \pmod{|\Sigma|-1} $$
>
>    考虑将同余式转化为线性不定方程：
>
>    $$ 2j + (|\Sigma| - 1)y = M+1 $$
>
>    根据裴蜀定理，若我们想要方程组有解，则需要满足 $\gcd(2,|\Sigma| - 1) \mid (M+1)$，由于 $\gcd(2,|\Sigma| - 1) = \gcd(2,25) = 1$，所以原线性不定方程有解。
>
>    那么此时，我们假设最小的解 $j_0 \in [1,M]$，根据裴蜀定理可知，上述不定方程关于 $j$ 的解集 $J = \{j_t|j_t = j_0 + (|\Sigma| - 1)t,\, t\in [0,+\infty)\}$，那么我们现在证明的命题就变为：
>
>    $$ [1,M]\subset J $$
>
>    若该命题成立，则显然需要 $|\Sigma| - 1 = 1$ 即 $|\Sigma| = 2$，这与我们的条件 $|\Sigma| = 26$ 不符，故命题不成立。
>
> 最后，根据当前的构造方案可以看出，证明列不出现回文串只需要证明行不出现即可，因为我们在第 $i$ 行第 $j$ 列所填字符为 $(i+j) \bmod (|\Sigma|-1)$，顺时针或逆时针旋转 $90^{\circ}$ 本质上就是 $i$ 与 $j$ 发生交换，因为加法满足交换律，所以我们从行得到的结论可以用于列上。

接下来，我们就需要处理 $R = N$ 或 $C = M$ 的情况了：

先考虑 $R = N$ 的情况，因为 $C = M$ 的情况就是沿顺时针或逆时针旋转 $90^{\circ}$ 而已。

如果我们想在不破坏某一行为回文串的情况下达成 $C$ 列为回文串的目标，则显然列与列的位置一定是对称的，换句话说，倘若第 $c$ 列为回文串，则必然 $M - c + 1$ 这一列也为回文串。

那么不难得出结论，当 $M$ 为奇数的时候，可以构造出任意的 $C$，当 $M$ 为偶数的时候，可以构造出偶数的 $C$，构造方案考虑最后一行中，让对称的 $c$ 的位置填 $\#$，其余位置填字符 $x\,(x \not = \#)$，即构成如下情况：
$$
\begin{aligned}
&\text{奇数且 } C \text{ 为奇数：}\\
& \#\,\cdots \, x\,\cdots\, x\,\#\,x\cdots \# \cdots \#\\
&\text{其余情况：}\\
& \#\,\cdots \, x\,\cdots\, x\,\cdots \,\# \,\cdots \,\#\\
\end{aligned}
$$
综上，我们做完了本题

## 代码实现

这里给出了关键部分的代码实现，其余部分还恳请读者自己完成：

```cpp
const char sharp = 'z';
char ansmap[MAX_SIZE][MAX_SIZE];

void main(){
	int N = read();
	int M = read();
	int R = read();
	int C = read();
	if(R == N && C == M){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=M;j++){
				printf("%c",sharp);
			}
			printf("\n");
		}
	} else if(R == N || C == M) {
		int flag = 0;
		if(C == M){
			swap(N,M);
			swap(R,C);
			flag = 1;
		}
		if(!(M & 1) && (C & 1)){
			printf("IMPOSSIBLE");
			return ;
		}
		for(int i=1;i<N;i++){
			for(int j=1;j<=M;j++){
				ansmap[i][j] = sharp;
			}
		}
		char x = 'y';
		int i = 1;
		while(C > 1){
			ansmap[N][i] = sharp;
			ansmap[N][M-i+1] = sharp;
			i++;
			C -= 2;
		}
		if(C){
			ansmap[N][(M >> 1) + 1] = sharp;
		}
		for(i=1;i<=M;i++){
			if(ansmap[N][i] != sharp){
				ansmap[N][i] = x;
			}
		}
		if(flag)
			swap(N,M);
		printmat(N,M,flag);
	} else {
		for(int i=1;i<=R;i++){
			for(int j=1;j<=M;j++){
				ansmap[i][j] = sharp;
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=C;j++){
				ansmap[i][j] = sharp;
			}
		}
		for(int i=R+1;i<=N;i++){
			for(int j=C+1;j<=M;j++){
				ansmap[i][j] = ((i+j)%25) + 'a';
			}
		}
		printmat(N,M);
	}
}
```


---

## 作者：wang1h (赞：0)

## [P9326 \[CCC 2023 S3\] Palindromic Poster](https://www.luogu.com.cn/problem/P9326)

## 题意简述

构造一个 $n \times m$ 的字符数组，且恰有 $r$ 行 $c$ 列回文串。无解输出 `IMPOSSIBLE`。

## 题目分析

看到样例的第一直觉：

```
aaaaa
aabbb
aabbb
aabbb
```

看起来，有解时在数组前 $r$ 行和前 $c$ 列填 $\texttt{a}$，其余填 $\texttt{b}$ 就行了吧？

但容易想到反例：$n=3,m=6,r=0,c=3$、$n=2,m=5,r=2,c=3$。

思路被 hack 了，一时想不到正解，尝试**分类讨论**，把大问题分解为若干简单的小问题。

#### 1. 当 $n=1$

此时每一列都是回文（即无论怎么构造，一定恰有 $m$ 列回文），所以**当 $n=1$ 且 $c \ne m$ 时，无解**。

#### 2. 当 $r=0$

思路被 hack 是因为后 $(m-c)$ 列均为 $\texttt{b}$（这样构造出的数组中，列的回文串数不是 $c$，而是 $m$，其在 $c \ne m$ 时不符题意）。

只要后 $(m-c)$ 列随机填就好了（如果运气极差，小概率 WA ，解决方法看代码）。

例：$n=3,m=6,r=0,c=3$

```
aaaqiu
aaaguo
aaathx
```

反例 $1$ 解决。

#### 3. 当 $r=n$

只是保持 $r$ 行回文是容易的（数组全为 $\texttt{a}$），考虑如何在此前提下满足恰有 $c$ 列回文串。

一个较为简单的方法：**把任意一行中间 $(m-c)$ 个 $\texttt{a}$ 改成 $\texttt{b}$**（有 $c$ 列回文串，就有 $(m-c)$ 列非回文串），破坏列的回文的同时保持行的回文，使得“恰有 $c$ 列回文串”。

例一：$n=2,m=5,r=2,c=3$

```
aaaaa
ababa
```

例二：$n=2,m=5,r=2,c=2$

```
aaaaa
abbba
```

例三：$n=2,m=4,r=2,c=2$

```
aaaa
abba
```

但**当 $m$ 为偶数，$c$ 为奇数时**，可以证明无论如何构造，都不能在保持 $r$ 行回文串的前提下，在最后一行中构造出回文串，此时**无解**。

不太严谨的证明：

> 若 $m$ 为偶数，每在一行中把一个 $\texttt{a}$ 改成 $\texttt{b}$，在对称的另一半中势必也要改一个以保持回文，于是每次要改偶数个 $\texttt{a}$，于是改动总次数是偶数，与 $c$ 为奇数**矛盾**。故无解。
>
> 若 $m$ 为奇数，可以在串的正中间改动，既保持回文，又改变“改动总次数” 的奇偶性，所以 **当 $n=r$ 且 $m$ 为奇数时一定有解**。

反例 $2$ 解决。

#### 4. 当 $0<r<n$

此时才是上述思路的适用范围，模拟即可。

#### 5. 其他

注意到 ~~注意力惊人~~ 构造方法是对称的，其他情况**同理**（$n,m$ 互换，$r,c$ 互换）。

## 关键代码

tip：抄袭刷 AC，棕名两行泪 QAQ

```cpp
//P9326 [CCC 2023 S3] Palindromic Poster
const int N=2005;
char a[N][N];
int n,m,r,c;
void fil(int st1,int ed1,int st2,int ed2,int v){for(int i=st1;i<=ed1;i++)for(int j=st2;j<=ed2;j++)a[i][j]=v;}
void no(){printf("IMP0SSIBLE");exit(0);}
int main(){
	scanf("%d%d%d%d",&n,&m,&r,&c);
	fil(1,n,1,m,'a');
	if(n==1&&m!=c)no();
	else if(m==1&&n!=r)no();
	else if(n==r){
		if(m&1){
			int mid=m/2+1,l=(m-c)/2;
			//mid是第1行中间的数的下标，l*2是只含'b'字符的串的总长度
			//如果感到难以理解，尝试代几组数据
			fil(1,1,mid-l,mid+l,'b');
			if(c&1)a[1][mid]='a';
		}else{
			if(c&1)no();
			int mid=m/2,l=(m-c)/2-1;
			fil(1,1,mid-l,mid+l+1,'b');
		}
	}else if(m==c){
		if(n&1){
			int mid=n/2+1,l=(n-r)/2;
			fil(mid-l,mid+l,1,1,'b');
			if(r&1)a[mid][1]='a';
		}else{
			if(r&1)no();
			int mid=n/2,l=(n-r)/2-1;
			fil(mid-l,mid+l+1,1,1,'b');
		}
	}else for(int i=r+1;i<=n;i++)for(int j=c+1;j<=m;j++)
       a[i][j]='b'+(i+j)%25;//这里可以理解为“以(i+j)为种子，产生'b'至'z'的随机数”,避免用随机数导致的极小概率WA
	for(int i=1;i<=n;i++)printf("%s\n",a[i]+1);
	return 0;
}
```

---

