# Walk on Matrix

## 题目描述

Bob is playing a game named "Walk on Matrix".

In this game, player is given an $ n \times m $ matrix $ A=(a_{i,j}) $ , i.e. the element in the $ i $ -th row in the $ j $ -th column is $ a_{i,j} $ . Initially, player is located at position $ (1,1) $ with score $ a_{1,1} $ .

To reach the goal, position $ (n,m) $ , player can move right or down, i.e. move from $ (x,y) $ to $ (x,y+1) $ or $ (x+1,y) $ , as long as player is still on the matrix.

However, each move changes player's score to the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the current score and the value at the position he moves to.

Bob can't wait to find out the maximum score he can get using the tool he recently learnt — dynamic programming. Here is his algorithm for this problem.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)However, he suddenly realize that the algorithm above fails to output the maximum score for some matrix $ A $ . Thus, for any given non-negative integer $ k $ , he wants to find out an $ n \times m $ matrix $ A=(a_{i,j}) $ such that

- $ 1 \le n,m \le 500 $ (as Bob hates large matrix);
- $ 0 \le a_{i,j} \le 3 \cdot 10^5 $ for all $ 1 \le i\le n,1 \le j\le m $ (as Bob hates large numbers);
- the difference between the maximum score he can get and the output of his algorithm is exactly $ k $ .

It can be shown that for any given integer $ k $ such that $ 0 \le k \le 10^5 $ , there exists a matrix satisfying the above constraints.

Please help him with it!

## 说明/提示

In the first example, the maximum score Bob can achieve is $ 300000 $ , while the output of his algorithm is $ 300000 $ .

In the second example, the maximum score Bob can achieve is $ 7\&3\&3\&3\&7\&3=3 $ , while the output of his algorithm is $ 2 $ .

## 样例 #1

### 输入

```
0```

### 输出

```
1 1
300000```

## 样例 #2

### 输入

```
1```

### 输出

```
3 4
7 3 3 1
4 8 3 6
7 7 7 3```

# 题解

## 作者：CXY07 (赞：11)

# ~~官方教你 Hack 系列~~

## 题目链接：[CF1332D 【Walk on Matrix】](https://www.luogu.com.cn/problem/CF1332D)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/20/)**

题意：

对于题目：
> “给定一个 $n \times m$ 的矩阵，一开始你在 $(1,1)$，手上的数值为 $a_{i,j}$，现在你可以往下或者往右，一直走到 $(n,m)$ 。你每走到一个新的点 $(x,y)$，手上的数就会变成：手上的数 $AND$ $a_{x,y}$，需要你最大化走到 $(n,m)$ 时手上的数字。”

现在 $\texttt{Bob}$ 写了一个 $\texttt{dp}$ 来解决这个问题：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)

照着以上的规则写成代码是这样的：

```cpp
//Code By Bob
#include<bits/stdc++.h>
using namespace std;

//#define int long long

const int MAXN = 510;
const int INF = 2e9;
const int mod = 1e9 + 7;

int n,m;
int a[MAXN][MAXN],dp[MAXN][MAXN];

signed main () {
	scanf("%d%d",&n,&m);
	for(register int i = 1;i <= n; ++i)
		for(register int j = 1;j <= m; ++j)
			scanf("%d",&a[i][j]);
	memset(dp,0x3f,sizeof dp);
	dp[0][1] = a[1][1];
	for(register int i = 1;i <= n; ++i)
		for(register int j = 1;j <= m; ++j)
			dp[i][j] = max((dp[i - 1][j] & a[i][j]),(dp[i][j - 1] & a[i][j]));
	printf("%d\n",dp[n][m]);
	return 0;
}
```

但是这个算法是假的，所以现在要你来 $\texttt{Hack}$ 他。

具体地，题目给定你一个 $k$ ，要求你输出一个 $n \times m$ 的矩阵 $(1 \le n,m \le 500,\forall \ 0 \le a_{i,j} \le 10^5)$

并且以上的 $\texttt{dp}$ 的答案与实际的最大值之差恰好为 $k$

------------


~~题意终于讲完了~~

首先考虑一下以上的 $\texttt{dp}$ 错在哪里

我们发现对于 $\texttt{AND}$，也就是 **按位与** 操作，不见得一个最大的数字与上某个特定的数字就是最大的，例如：

```100000 & 1 = 0 , 1 & 1 = 1```

为什么呢？因为不见得大的数字就会和这个特定数字有更多的同为 $1$ 的二进制位

这个应该很显然

那么我们考虑根据这个东西来 $\texttt{Hack}$ 他

我们考虑 “骗” 这个 $\texttt{dp}$，让他选择一个看似更大的答案，最后把这个答案给卡掉，就可以让 $\texttt{dp}$ 的答案为 $0$，最后让这个方案的真正答案为 $k$，差值就是 $k$ 了。

我们发现 $k_{max} < 2^{17} < 10^5$，那么也就是说，如果我们令一个值为 $2^{17}+k$，那么 $2^{17}$ 和 $k$ 的二进制位是不会相互影响的，也就是不发生进位的，或者说 $k\  \&\ 2^{17} = 0$。

这很好，因为这样就让题目变得非常简单了，我们可以构造以下这个矩阵：

$$n=2,m=3$$

$$\begin{bmatrix} 2^{17}+k & 2^{17} & 0\\ k & 2^{17}+k & k \end{bmatrix}$$

就可以完美解决这个问题了

为什么？

我们可以一步一步看这个矩阵，首先显然的，我们不会走到 $(1,3)$，因此我们迫使$(1,1)\rightarrow (n,m)$ 的走法只有两种：走 $(1,2)$ 或者 $(2,1)$

我们发现 $dp[1][2]=2^{17},dp[2][1] = k$

那为什么 $(2,2)$ 这个位置放的又是 $2^{17}+k$ ？

因为这样能够保证 $dp[2][2]$ 从 $dp[1][2]$ 取值，这样就进入了我们的圈套

最后 $(2,3)$ 再放一个 $k$，此时的 $dp[2][2]=2^{17}$，$dp[2][3]$ 又只能从 $dp[2][2]$ 取值，所以我们就成功让 $\texttt{dp}$ 输出了 $0$

这时我们发现 $\texttt{dp}$ 选择的是走 $(1,2)$ 那一边，并且不难发现如果走 $(2,1)$，答案就恰好为 $k$ 了

因此 $\texttt{dp}$ 答案与正确答案的差值正好就是 $k$ 了

注意：本菜鸡一开始写得是 $2^{18}+k$，但是当 $k$ 取最大值 $10^5$ 时，$2^{18}+10^5$ 是超过了 $a_{i,j}$ 的限制 $3 \times 10^5$ 的，注意一下即可

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define int long long

int k;

signed main () {
	scanf("%d",&k);
	printf("%d %d\n",2,3);
	printf("%d %d %d\n",(1 << 17) + k,(1 << 17),0);
	printf("%d %d %d\n",k,(1 << 17) + k,k);
	return 0;//End.
}
```

代码很简单，不过这题我吹爆 ~~真的好玩~~

初三的 $\texttt{OIer}$，请多关照

---

## 作者：寒冰大大 (赞：3)

这个贪心会从第二个开始贪，我们首先得满足有两行

然后在考虑列数，如果只有两列的话意味着贪心没用（我们相当于直接比较所有答案），所以得来三列

于是设出这个矩阵

$\begin{matrix}a&b&c\\d&e&f\end{matrix} $

然后模拟一下

$\begin{matrix}a& a\&b &c\\a\&d&e&f\end{matrix} $

模拟两下

$\begin{matrix}a& a\&b &a\&b\&c\\a\&d&max((a\&b\&e),(a\&d\&e))&f\end{matrix} $



此时可以看见f有三种取值（妈耶）

但是我们完全可以令$c=0$,此时$f$这个位置只有两种取值$(f=max(a\&b\&e\&f,a\&d\&e\&f))$，我们就来构造一组让贪心小$k$的数据

怎么构造呢？

我们看这两数据只有$b,d$有区别，我们就让$a=e=b~or~d$

这时候还要怎么办呢，注意到题目要求$k\leq10^5$

诶，也就是说这东西小于$2^{17}=131072$

题目要求小于$3*10^{5}$

那就是说还剩了一个二进制位

那就好办了，这样恰好可以让贪心贪这个大的（一个为k，一个为$2^{17}=131072>k$）

我们直接令$f=k$，那么这时候这两东西$\&$下来为$0$，而答案为$k$，刚好满足差为$k$


于是这东西就变得非常浅显易懂：

```cpp
#include<touwenjian.h>

using namespace std;

int k; 

int main()
{
	ios::sync_with_stdio(false);
	cin>>k; 
	cout<<2<<" "<<3<<endl;
	cout<<(1<<17)+k<<" "<<(1<<17)<<" "<<0<<endl;
	cout<<k<<" "<<(1<<17)+k<<" "<<k;
	return 0;
}

```



---

## 作者：dead_X (赞：2)

## 题意简述
求 $n\times m$ 矩阵中所有从左上到右下的最短路径经过的数的与运算结果的最大值。

有一个解决如上问题的错误 $dp$ 需要你来精确hack。

给出一种数据使得这个程序的解和正确答案正好相差 $n$。
## 思路简述
如果我现在是 $(1000000)_2$，虽然我更大，但是一旦这一位没了，我就真没了。

如果我现在是 $(111111)_2$，虽然我更小，但是我还有很多位数。

所以我们考虑让一个正解为 $(111111)_2$ 的解被误判成 $(1000000)_2$。

于是构造就不难了。

构造一个 $2\times 3$ 的矩阵。

$(111\cdots1)_2,(011\cdots1)_2$

$(100\cdots0)_2,(111\cdots1)_2$

$\quad\quad 0\quad\quad~,\quad\quad n$

注意这个 $(100\cdots0)_2$ 中$1$的位置要比 $n$ 的最高位高，确保错误的程序输出$0$。

显然程序输出$0$，实际答案为 $n$。
## 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main()
{
	int m=read(),n=m;
	while(n!=(n&(-n))) n+=n&(-n);
	if(n==0)
	{
		return 0&printf("1 1\n1");
	}
	if(n==1) 
	{
		return 0&printf("3 4\n7 3 3 1\n4 8 3 6\n7 7 7 3");
	}
	if(n<100000) n*=2;
	printf("3 3\n%d %d 0\n%d %d %d\n0 0 %d",2*n-1,n-1,n,2*n-1,m,m);
	return 0;
}
 
```

---

## 作者：George1123 (赞：2)

# 题解-Walk on Matrix

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#D)

> [Walk on Matrix](https://codeforces.com/contest/1332/problem/D)

> 给定一个 $k$，要求构造一个随意大小为 $n\times m$ 的矩阵 $a_{i,j}$ 使得用
> ![](https://img2020.cnblogs.com/blog/1938334/202004/1938334-20200401160503539-1761187453.png)
> 得到的答案与从 $(1,1)$ 到 $(n,m)$ 的最小按位与路径答案相差 $k$。

> 数据范围：$1\le n,m\le 500$，$0\le a_{i,j}\le 3\cdot 10^5$，$0\le k\le 10^5$。

很巧妙的一题，从数据范围以及样例中可以猜测到这题有通解。

首先这个答案 $S$ 肯定是比真实答案 $Ans$ 大的，所以 $S-Ans=k$。

通过研究第二个样例，可以发现，鲍勃的代码会盲目找最大的，不会考虑如 $7\&3>8\&3$ 的情况。

所以可以找一个 $t=2^c>k$，构造如下 $3\times 4$ 矩阵：

$$
\begin{bmatrix}
t|k&k&k&0\\
t&0&k&0\\
t&t&t|k&k\\
\end{bmatrix}
$$

所以鲍勃的代码 $dp_{3,3}=t,dp_{3,4}=0$。

而真正的最小按位与路径为 $(t|k)\&k\&k\&k\&(t|k)\&k$，答案为 $k$。

正好相差 $k$。

**代码：**

```cpp
//Data

//Main
int main(){
	re int k,t=1;
	scanf("%d",&k);
	while(t<=k) t<<=1;
	printf("3 4\n");
	printf("%d %d %d %d\n",t|k,k,k,0);
	printf("%d %d %d %d\n",t,0,k,0);
	printf("%d %d %d %d\n",t,t,t|k,k);
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：gyh20 (赞：1)

构造题，发现原算法的问题就是有一些选择看起来更优，但无法保留到最后。

可以直接让答案为 $k$ ，但原算法只能得到 $0$。

发现 $2^{17}$ 刚好大于 $k$ ，所以 $2^{17}$ 肯定会被选中，所以只用构造如下矩阵：

$2\space 3$

$2^{18}-1,k,0$

$2^{17},2^{18}-1,2^{18}-1$

[广告](https://www.luogu.com.cn/blog/gyh20/post-di-cfat-ti-xie-ji-lie)

---

## 作者：pyqpyq (赞：1)

第一次打 CF A 掉 D，写篇题解纪念一下~~

看完[题目](https://www.luogu.com.cn/problem/CF1332D)有一种[熟悉的感觉（](https://www.luogu.com.cn/problem/P3640)

好吧进入正题。

首先，给出 $ 3 \times 2 $ 的矩阵的话，Bob 一定是对的，因为只在终点取最大值。

那么考虑下面这个 $ 3 \times 2 $ 的矩阵：

$$\begin{gathered}\begin{matrix}a&b\\c&d\\e&f\end{matrix}\quad\end{gathered}$$

首先规划一下，路径分两条， $ a \rightarrow c \rightarrow d \rightarrow f$ 和 $ a \rightarrow b \rightarrow d \rightarrow f$。

设第一条为正确路径，第二条为错误路径即要被误导的路径。（反过来也行）

为了答案不受 $ a \rightarrow c \rightarrow e \rightarrow f$ 干扰，我们把 e 处填为 0，这样整条路径都答案为 0。（因为这条路上的格子的答案都是不受其他格子影响的，是条废路。）

再考虑这个算法为甚错了。

很明显它每次都贪心地选择了目前的最大值，而另一个值可能在未来的某处发挥更大的作用。~~（dp 沦为贪心）~~

那么设 c 就是这个数值小但是作用大的数，b 是那个数值更大但是没甚用的数。

很明显这里格子有限。如果 c 在 d 处乃至之前就发挥作用了，那么错误算法就不会选第一条而是第二条了。所以这里“未来的某处”指 f 处。

为了使问题简化，将 a 处与 d 处的二进制位全设为 1，这样就不会影响答案。

但题目限制不能超过 $ 3 \times 10 ^ 5$，所以我们要尽量把设为 1 的位数减小但是不能影响答案，设这个值为 s，它的值之后再求。

最后总结一下，要求的答案要满足下面的关系：

1. $ e = 0 $

2. $ a = s $

3. $ d = s $

4. $ c\ and\ f - b\ and\ f = k $

5. $ c < b $

为了简便，直接设 $ b\ and\ f = 0 $。

由条件 4 有 $ c\ and\ f = k $，为了简便直接让 $ c = f = k $。

所以又有 $ b \& k = 0 $ 还是直接让 b 变为 k 的反码。（**注意是相对于 s 来说的。**~~s 忘了是什么的自己翻上去看。~~）

举个例子，当 $ s = ( 1111 ) _ 2 $，$ k = ( 0101 ) _ 2 $ 时，$ b = ( 1010 ) _ 2 $，即在  s 范围内的二进制码全部反过来。即 $ s\ xor\ k = b$

条件 4 满足了，条件 5 呢？

注意到可以给出的值的范围比 k 的范围多了整整三倍，这意味着除了 k 所占的二进制位外，还有一位可以给我们用。

那么让 c 在 s 范围内的最高位为 0，b 在 s 的范围内最高位为 1 就行了。

怎么实现呢？直接让 s 多给一位即可，xor 的时候那一位二进制位是不会动的。

最后一个问题：求 s。

计算得 $ 100000 = ( 11000011010100000 ) _ 2 $，共 17 位。~~我不会告诉你我是用计算机程序员模式求的。~~

那么 s 是不是赋 $ ( \underbrace{11\dots1} _ {total 17} ) _ 2$ 即可？

~~既然我这么问了显然~~不是，别忘了上面还要留一位，所以真正的 s 为 $ ( \underbrace{11\dots1} _ {total 18} ) _ 2$。

十进制表示是 262143，没有超出范围。

最后的矩阵就是：

$$\begin{gathered}\begin{matrix}s&s\ xor\ k\\k&s\\0&k\end{matrix}\quad\end{gathered}$$

代码不给了，没意义。

~~最后弱弱地问一句正确的算法是什么。~~

---

## 作者：一扶苏一 (赞：1)

### Description

有这么一个问题：

> 有一个 $n \times m$ 的矩阵 $a_{n, m}$，矩阵的每个位置都有一个数，要求寻找一个每次只能向右或向下走的从 $(1, 1)$ 至 $(n, m)$ 的路径，最大化路径上的数的按位与之和。
>
> $1 \leq n, m \leq 500$，$0 \leq a_{i, j} \leq 3 \times 10^5$。

现在给出解决该问题的一个**错误** dp 算法（见题面图片），请构造一组数据，hack 掉这个算法，使得正确答案比错误的输出**恰好**大 $k$。

$0 \leq k \leq 10^5$。

### Solution

首先考虑这个 dp 为什么是错的，这是因为在 dp 的过程中没有保证**最优子结构**的成立，换句话说，在某个状态的最大值转移到下一个状态以后不一定是最大值。以下面的矩阵为例（方便起见，元素写成二进制形式）

```plain
11 01
10 11
00 01
```

注意到 $f_{2, 2}$ 按照给出的算法计算的话，应该从 $f_{2, 1}$ 转移，其值为 $10$，但是与 $01$ 按位与之后的值为 $0$，相反如果从 $(1, 2)$ 转移，则走到 $(2, 2)$ 的值为 $01$，与 $01$ 按位与后的值为 $01$，比上述结果优。

因此我们只需要在最高位上进行“诱导”，就可以让 dp 走入歧途。

考虑构造这个矩阵，不妨让 dp 输出 $0$，而正解输出 $k$。

可以让矩阵右下角的值为 $k$，然后将左下角格子设成 $0$，表示只能从上方转移下来。然后只需要在上方格子构造两条路径，一条是按位与的值为 $2^{\lfloor\log_2^k\rfloor + 1}$ 的路径，表示为二进制就是 $1000\dots$，其中 $1$ 的位数比 $k$ 的二进制最高位还要多 $1$；另一条是按位与的值恰好为 $k$ 的路径。 构造这个矩阵只需要四个格子：左上角全 1，右上角为 $k$，左下角为 $2^{\lfloor\log_2^k\rfloor + 1}$，右下角全 $1$。

拼上最下面的两行，共有三行两列。

考虑矩阵中的最大值是左上角的全 $1$ 位置，这个位置至少要是 $2^{\lfloor\log_2^k\rfloor + 2} - 1$。当 $k = 10^5$ 时，这个值是 $262143$，满足要求。

### Code

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>

int main() {
  int k;
  std::cin >> k;
  int t = log2(k);
  puts("3 2");
  printf("%d %d\n", (1 << (t + 2)) - 1, k);
  printf("%d %d\n", 1 << (t + 1), (1 << (t + 2)) - 1);
  printf("0 %d\n", k);
  return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
首先让我们看一看他的代码错在了哪里。

不难看出，他的代码中取最大值的操作是错误的。

例如 $10000 \And 1111 = 0$ 但 $1 \And 1=1$ 更大，所以我们构造一个类似这样样例欺骗他的代码。

我们设计一个三行两列的矩阵：
$$
\begin{Bmatrix}
\dots & \dots\\
\dots & \dots \\
0  & \dots
\end{Bmatrix}
$$

这里的 $0$ 使正确路径与错误路径不经过这个点。

这里我们需要使差值为 $k$ 所以我们希望让错误代码到终点时候答案为 $0$ 而正确的答案为 $k$。

所以我们得到了：

$$
\begin{Bmatrix}
\dots & \dots\\
\dots & \dots \\
0  & k
\end{Bmatrix}
$$

因为最终我们希望正确答案为 $k$ 所以我们使正确路径到前一步时等于 $k$ 此时我们又得到：

$$
\begin{Bmatrix}
x & y\\
k & x \\
0  & k
\end{Bmatrix}
$$


到了这一步时，我们先写出正确路径 $x \And k \And x \And k=k$ 简化一下得出 $x \And k=k$ 所以 $x=111\dots 1$ 或者是 $x=k$。

错误路径就是 $x \And y \And x \And k=0$ 简化一下得出 $x \And k \And y=0$ 因为 $x \And k \ne 0$ 所以 $y=100\dots0$ 或者是 $y=0$。

又因需要欺骗最大值，所以 $y=100\dots0$ 此时 $y$ 的二进制大于 $k$ 的二进制位数。推出 $y=2^{17}$，所以推出：

$$
\begin{Bmatrix}
x & 2^{17}\\
k & x \\
0  & k
\end{Bmatrix}
$$

接着推 $x$，上面推出了$x=111\dots1$ 或者是 $k$。

为了保证错误答案尽可能大，所以 $x \And 2_{17}$ 中 $x$ 如果是 $k$ 可能出现 $x \And 2_{17}=0$ 的情况，所以 $x=2^{18}-1$

所以答案就是：
$$
\begin{Bmatrix}
2^{18}-1  & 2^{17}\\
k & 2^{18}-1 \\
0 &k
\end{Bmatrix}
$$


### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int k;
	cin>>k;
	cout<<"3 2"<<endl;
	cout<<(1<<18)-1<<" "<<(1<<17)<<endl;
	cout<<k<<" "<<(1<<18)-1<<endl;
	cout<<0<<" "<<k<<endl;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

教练貌似在某节课讲过本题应该如何改正 bob 的做法？/kx

首先先盯真一下 bob 为什么错，显然按位与并不是一种无后效性的运算。例如，如果 bob 走出的路在到终点前的结果是 $2$，正解到终点前结果是 $1$，而终点上是 $1$，那 bob 就比正确答案少了 $1$。由此不难想到终点上的数是 $k$，且为了避免 bob 从另一个方向进入终点，需要封锁终点的一个入口，我选了上面的。

那么如何诱导 bob 进入错误路线？bob 在终点前的结果需要比 $k$ 大且按位与 $k$ 等于 $0$，可以想到这个数就是 $2^{(\log_2k+1)}$，那么为了方便可以把这个值取得很大，也就是 $2^{17}$（虽然理论上到 $2^{18}$ 也可以，但是由于后面需要一个 $2^{18}+k$ 溢出了所以只能到 $2^{17}$）。那么正确答案到终点前应该就是 $k$。那在这之前呢？为了避免两条路受其他数干扰，可以把矩形变成如下的样子：

$$
\begin{bmatrix}
   x & k & 0 \\
   2^{17} & x & k
\end{bmatrix}
$$

其中 $x$ 是一个未知量，且需要保证 $x\And2^{17}\And x=2^{17}$，$x\And k\And x=k$，不难想到由于 $k<2^{17}$，则 $x$ 最小（避免超过限制）是 $k+2^{17}$，写完！

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int k;
	cin>>k;
	cout<<"2 3"<<endl;
	cout<<(1<<17)+k<<' '<<k<<" 0"<<endl;
	cout<<(1<<17)<<' '<<(1<<17)+k<<' '<<k<<endl;
}
```

---

## 作者：F_Mu (赞：0)

**题意**

$Bob$想解决一个问题：一个$n*m$的矩阵，从$(1,1)$出发，只能走右和下，问从$(1,1)$到$(n,m)$的最大$\&$和

他的算法如下($C++$)

```cpp
    memset(dp, 0, sizeof(dp));
    dp[0][1] = a[1][1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max(dp[i - 1][j] & a[i][j], dp[i][j - 1] & a[i][j]);
        }
    }
    cout << dp[n][m];
```



已知他的算法并不能得到最大的$\&$和

给定一个$k$，请构造出一个$n*m$的矩阵，使得最大$\&$和比他的代码得出的答案大$k$

$1\leq n,m\leq 500$

$0\leq a_{i,j}\leq 3*10^5$

$0\leq k\leq 10^5$

**分析**

既然要针对$Bob$的算法进行构造，那么肯定要知道他的算法错在哪里（知己知彼，百战百胜）

我们将第二个样例的矩阵作为输入，得到$Bob$的答案 ，发现是$2$，在答案路径中，$(3,4)$前的节点是$(3,3)$

我们输出$dp[3][3]$发现是$4$，但是在答案路径中，走到$(3,3)$时是$3$，大概清楚了$\&$和并不能进行贪心

且可以模仿样例在答案路径中放入一个另一个更大的$\&$值

我们考虑能否直接构造矩阵使得答案是$k$，使得$Bob$的代码得到$0$

首先考虑二维矩阵，发现$(2,2)$是的确是挑最大的$\&$和，无法构造

我们看到第二个样例是$3*4$的矩阵，我们考虑能否构造出一个$2*3$的矩阵

考虑设计两个路径

+ $(1,1)->(1,2)->(2,2)->(2,3)$
+ $(1,1)->(2,1)->(2,2)->(2,3)$

通过样例得到灵感，第二条路径得到的$(2,2)$中的答案比第一条路径中大，但是不满足条件

那么思考如果$\&$要大，不妨在$k$的二进制前面加上一个$'1'$，如果第二条路径要大，可以在$k$取反后前面在加一个$'1'$

我们直接设计$a[2][3]=k$，我们看数据范围看到$a[i][j]$的最大值可以为$3*k$，考虑如下构造：

将$k$变为$2$进制，设字符串为$s$，将其各位取反得到字符串$s1$

构造$2*3$矩阵：

$('1'+s)$ $(s)$ $(0)$

$('1'+s1)$ $('1'+s)$ $(s)$

然后将其转换为十进制即可

路径一我们可以直接忽略$s$前面的$1$直接得到答案$k$

路径二我们发现走到$(2,2)$时，答案是$s$前面的$1$，那么这个和$(2,3)$的值$\&$一定是$0$

取反也可以用^，但写代码时没考虑那么多

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int k;
int a[30];

signed main() {
    start;
    cout << 2 << ' ' << 3 << '\n';
    cin >> k;
    int maxx = 0;
    for (int i = 0; i < 30; ++i) {
        if (k & (1 << i))
            a[i] = 1, maxx = i;
        else
            a[i] = 0;
    }
    cout << k + (1 << (maxx + 1)) << ' ' << k << ' ' << 0 << '\n';
    int ans = (1 << (maxx + 1));
    for (int i = maxx; i >= 0; --i) {
        if (!a[i])
            ans += (1 << i);
    }
    cout << ans << ' ' << k + (1 << (maxx + 1));
    cout << ' ';
    cout << k;
    return 0;
}
```

废话好多，构造还是思路重要，所以大部分篇幅都用来讲思路

---

## 作者：AutumnKite (赞：0)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

[题目传送门](https://codeforces.com/contest/1332/problem/D)

### 题意

有一个问题：

> 给定一个 $n\times m$ 的矩阵 $\{a_{i,j}\}$，求一条从 $(1,1)$ 到 $(n,m)$ 的路径，使得路径上所有数按位与（$\operatorname{and}$）的结果最大。

有一个错误的 DP 做法（加载比较慢请直接看原题）。

请你构造一个满足 $1\le n,m\le 500,0\le a_{i,j}\le 3\times 10^5$ 的矩阵，使得最优答案与这个错误 DP 得到的答案恰好差 $k$。

$0\le k\le 10^5$。

### 题解

我们可以把 $a_{i,j}=0$ 的位置视为不能经过的点，那么我们只需要构造一个点 $(x,y)$ 使得：

- 所有 $(1,1)$ 到 $(n,m)$ 的路径必须经过 $(x,y)$。
- $(x,y)$ 到 $(n,m)$ 的路径唯一（为了方便构造）。
- 记 $P_1$ 为从 $(1,1)$ 到 $(n,m)$ 的最优路径，$P_2$ 为从 $(1,1)$ 到 $(x,y)$ 的最优路径加上 $(x,y)$ 到 $(n,m)$ 的唯一路径，需要满足 $w(P_1)-w(P_2)=k$。
- 记 $P_1$ 为从 $(1,1)$ 到 $(n,m)$ 的最优路径上 $(1,1)$ 到 $(x,y)$ 的路径，$P_2$ 为从 $(1,1)$ 到 $(x,y)$ 的最优路径，需要满足 $w(P_1) < w(P_2)$。

其中 $w(P)$ 表示路径 $P$ 上所有数的 $\operatorname{and}$ 和。

那么构造就非常简单了，我们只要构造矩阵
$$\begin{bmatrix} 2^{18}-1 & 2^{17} \\ k & 2^{18}-1 \\ 0 & k\end{bmatrix}$$

即可满足条件。

### 代码

```cpp
int k;
void solve(){
	read(k);
	print(3, ' '), print(2);
	print((1 << 18) - 1, ' '), print(1 << 17);
	print(k, ' '), print((1 << 18) - 1);
	print(0, ' '), print(k);
}
```

---

