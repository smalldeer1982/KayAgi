# [WFOI - 02] I wanna reverse to reserve（翻转）

## 题目背景

> 君子不器

“我最擅长解谜了，你说是吧，kid。”

“嗯...”

## 题目描述

kid 走进了一个 $n$ 行 $m$ 列的矩阵，**不**保证矩阵中有 $n$ 个数字 $1$，$n$ 个数字 $2$，$\dots$ , $n$ 个数字 $m$ 但 $n,m$ 均为偶数。

现有两种改变矩阵的方式：

- 选择任意一行，将这一行上的数翻转；
- 选择任意一列，将这一列上的数翻转。

每次操作可以选择任意一种方式。

现在需要通过若干次操作，将矩阵变为：

$$
n\;行\left\{
\begin{array}{l}
1\quad2\quad3\quad\cdots\quad m\\
\\
1\quad2\quad3\quad\cdots\quad m\\

\\
\cdots\\
\\
1\quad2\quad3\quad\cdots\quad m\\
\end{array}
\right.

$$

这样才会出现下一个存档点。

你需要帮 kid 解决这个问题。

你只需要给出答案，剩下的操作就交给 Uvocde 吧！

## 说明/提示

**【数据范围】**

**本题采用 Subtask 捆绑测试**。

- $\texttt{Subtask \#0 (20pts)}$：最多只有 $2$ 个数不在规定位置上；
- $\texttt{Subtask \#1 (20pts)}$：$n=2$；
- $\texttt{Subtask \#2 (20pts)}$：$m=2$；
- $\texttt{Subtask \#3 (40pts)}$：$1\le n\le 100$，$1\le m\le 100$；

全部数据满足 $1\le n\le 100$，$1\le m\le 100$。

## 样例 #1

### 输入

```
2 4
1 2 3 4
4 3 2 1```

### 输出

```
YES
1
0 2```

## 样例 #2

### 输入

```
2 4
1 2 3 4
4 1 3 2```

### 输出

```
NO```

# 题解

## 作者：Cocoly1990 (赞：10)

验题人题解。

引理一：定义 $f_x=n-x+1$.

则无论如何置换，$\left(x,y\right)$ 上的数只能置换到

 $$\left(x,y\right),\left(f_x,y\right),\left(x,f_y\right),\left(f_x,f_y\right)$$
上。

证明：易证。

----
引理二：我们称上述四个位置为一个置换环。

数据有解当且仅当四个位置的值是

$$x,x,f_x,f_x$$

证明：也易证。

---
考虑对于每个环分情况构造。

一个很重要的原则是构造的时候每一行必须翻转偶数次，即不能影响行内其他的值。

----

Case 1：

$$\begin{matrix}

     x & f_x \\

     x & f_x

\end{matrix}$$

已经归位，无需构造。

----
Case 2：对角线换位
$$\begin{matrix}

     f_x & x \\

     x & f_x

\end{matrix}$$

交换第二列。

$$\begin{matrix}

     f_x & f_x \\

     x & x

\end{matrix}$$

交换第一行。

$$\begin{matrix}

     f_x & f_x \\

     x & x

\end{matrix}$$

交换第二列。

$$\begin{matrix}

     f_x & x \\

     x & f_x

\end{matrix}$$

交换第一行。

$$\begin{matrix}

     x & f_x \\

     x & f_x

\end{matrix}$$

done.

---
Case 3：双侧换位

$$\begin{matrix}

     f_x & x \\

     f_x & x

\end{matrix}$$

交换第一行。

$$\begin{matrix}

     x & f_x \\

     f_x & x

\end{matrix}$$

交换第一列。

$$\begin{matrix}

     f_x & f_x \\

     x & x

\end{matrix}$$

交换第二列。

$$\begin{matrix}

     f_x & x \\

     x & f_x

\end{matrix}$$

交换第一行。

$$\begin{matrix}

     x & f_x \\

     x & f_x

\end{matrix}$$

done.

---

## 作者：Icyfires18 (赞：5)

### 题意

对输入矩阵进行行/列翻转操作，使其变换成行值递增且列值相等的矩阵，操作数不超过 $n×m$，输出操作。

### 思路

这篇题解为赛时思路，灵感来源于魔方，并且部分解释与魔方相关。

下文可能看上去很复杂很高级，其实一点即通，毫无思维难度可言。

#### Step 1 性质

不难发现，对于任意一个点 $(x,y)$ ，经过行/列翻转操作之后，只可能处于四个位置，分别见下图；

$$
\begin{bmatrix}
(x,y) & (x,m+1-y) \\
(n+1-x,y) & (n+1-x,m+1-y)
\end{bmatrix}
$$

能看出，单进行行翻转操作，就相当于上述位置左右互换；单进行列翻转操作，就相当于上述位置上下互换。



**现称这四个相对位置为一组变换位，其值在翻转变换中不会改变。**

将题意再翻译一下，可以得出最终需要将矩阵中所有的变换位翻转成同一形式。若用 $0$ 和 $1$ 标注目标变换位的值格式，即为下式。具体地说，**$0$ 代表值 $y0$**，**$1$ 代表值 $y1$**。

$$
\begin{bmatrix}
(x0,y0) & (x0,y1) \\
(x1,y0) & (x1,y1)
\end{bmatrix}=
\begin{bmatrix}
0 & 1 \\
0 & 1
\end{bmatrix},
\begin{pmatrix}
x0+x1=n+1 \\
y0+y1=m+1
\end{pmatrix}
$$

由上文性质和值格式可得，若单组变换位满足其中两值等于 $y0$、两值等于 $y1$，即可通过翻转变换得到目标变换位，否则不可能（直接输出“$NO$”就行了）。而满足条件的变换位又有以下五种形式：

$$
\begin{bmatrix}
0 & 0 \\
1 & 1
\end{bmatrix},
\begin{bmatrix}
1 & 1 \\
0 & 0
\end{bmatrix},
\begin{bmatrix}
0 & 1 \\
1 & 0
\end{bmatrix},
\begin{bmatrix}
1 & 0 \\
0 & 1
\end{bmatrix},
\begin{bmatrix}
1 & 0 \\
1 & 0
\end{bmatrix}
$$

下面我们分类讨论将这五种形式翻转成目标变换位的操作方案。

#### Step 2 方案

对于一组变换位，**定义 $U,D,L,R$ 分别为翻转上行、下行、左列、右列**，翻转完成后值会对调。（有魔方基础的应该能很快很顺的理解）

在考虑单组变换位的翻转方案时，有两点需要注意：

1. **行翻转次数为偶数**，**列翻转次数不限**。因为奇数次行反转会影响同行其它已转好的变换位元素顺序，而已转好的变换位列值相等，翻转没有影响。

2. **翻转次数尽量控制在 $4$ 次及以内**。因为变换位组数为 $\frac 1 4 (n×m)$，而总操作次数最多为 $n×m$，均摊下每组为 $4$ 次。

接下来在满足上述条件的前提下考虑前文五种情况（从左到右分别对应上面的矩阵）：

- 情况一：上行为 $0$，下行为 $1$；
	
    方案：$\texttt{DRDR}$ （无多余翻转）；

- 情况二：上行为 $1$，下行为 $0$；
	
    方案：$\texttt{URUR}$ （无多余翻转）；

- 情况三：正对角为 $0$，斜对角为 $1$；
	
    方案：$\texttt{RDRD}$ （无多余翻转）；

- 情况四：正对角为 $1$，斜对角为 $0$；
	
    方案：$\texttt{RURU}$ （无多余翻转）；

- 情况五：左列为 $1$，右列为 $0$；
	
    方案：$\texttt{ULRU}$ （有多余翻转）；
    
想要真正理解方案妙处的可以手动模拟推演过程（毕竟是结论题）。

至此思路的核心要素已经叙述完毕，然后就是代码实现和细节处理了。

P.S.听说变换完后还可以对操作序列离线处理压一下操作数，或许有所帮助，不过在这里就没必要。

### 代码

[记录](https://www.luogu.com.cn/record/72264508)

1. 枚举变换位可先枚举左上位置点再推导，参考 main 函数里的 for 循环；

2. 处理变换位可先用位运算提取信息存入二进制再判断，参考 deal 函数；

3. 注意 NO 情况的判断有两处，第一处判断值是否符合，第二处判断个数是否满足，见 flag 变量；


```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int N=101;
int n,m,cnt,a[N][N];//基础矩阵
string str[N][N];//操作序列
bool flag;//NO标记
inline void fip(int &rer){//快读
	register char ch;
	for(ch=0;ch<'0'||ch>'9';ch=getchar());
	for(rer=0;ch>='0'&&ch<='9';ch=getchar())
		rer=(rer<<3)+(rer<<1)+(ch^48);
}
void reverse(int col){//列翻转
	register int i,j;
	for(i=1,j=n;i<j;++i,--j)
		swap(a[i][col],a[j][col]);
}
void deal(int x0,int y0,int x1,int y1){//变换位处理
	register int s=0;
	s|=(a[x0][y0]==y0? 0:1),s<<=1;
	s|=(a[x1][y0]==y0? 0:1),s<<=1;
	s|=(a[x0][y1]==y0? 0:1),s<<=1;
	s|=(a[x1][y1]==y0? 0:1);
	if(s==0x3)return;//0011
	else cnt+=4;
	switch(s){
		case 0x5:str[x0][y0]="DRDR";return;//0101
		case 0x6:str[x0][y0]="RDRD";return;//0110
		case 0x9:str[x0][y0]="RURU";return;//1001
		case 0xA:str[x0][y0]="URUR";return;//1010
		case 0xC:reverse(y0),reverse(y1);
				 str[x0][y0]="ULRU";return;//1100
		default:flag=true;return; 
	}
}
void print(int x0,int y0,int x1,int y1){//操作输出
	for(auto i:str[x0][y0]){
		if(i=='U')printf("0 %d\n",x0);
		if(i=='D')printf("0 %d\n",x1);
		if(i=='L')printf("1 %d\n",y0);
		if(i=='R')printf("1 %d\n",y1);
	}
}
int main(){
	register int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	for(j=1;j<=m;++j)
		fip(k),a[i][j]=k,
		flag|=(k!=j&&k!=m+1-j);
	if(flag){puts("NO");return 0;}
	for(i=n>>1;i>=1;--i)
	for(j=m>>1;j>=1;--j)
		deal(i,j,n+1-i,m+1-j);
	if(flag){puts("NO");return 0;}
	printf("YES\n%d\n",cnt);
	for(i=n>>1;i>=1;--i)
	for(j=m>>1;j>=1;--j)
		print(i,j,n+1-i,m+1-j);
	return 0;
}
```

不错的月赛题目:)

---

## 作者：Eafoo (赞：5)

~~不得不说，构造题真恶心~~

~~管理大大说我题解 LATEX 与汉字中间没空格，我仔细看了好几遍都没发现没加空格的 LATEX QAQ 望管理大大对我这个蒟蒻宽容一些，如果这篇博客还有其他问题请管理大大一并写明，毕竟被打回四次我心态是真的快崩了~~

# 1. 翻转操作有什么性质呢？

显然，对于矩阵内的任意一个数，它最多只能翻转到四个位置，这四个位置依次是它的原位置、将它水平翻转后的位置、将它竖直翻转后的位置、将它水平且竖直翻转后的位置。

**于是这篇题解中我们将这一组四个位置称为一个轮换位，显然轮换位中的四个位置互相关于矩阵对称。**

如下表所示，其中同一个颜色的四个位置表示一个轮换位。

| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |
| ----------- | -----------: | -----------: | -----------: |
| $\color{green}1$ | $\color{brown}2$ | $\color{brown}3$ | $\color{green}4$ |
| $\color{green}1$ | $\color{brown}2$ | $\color{brown}3$ | $\color{green}4$ |
| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |

**既然一个数字只能翻转到它处于的轮换位中的四个位置，那么它就不可能通过翻转到达其他的轮换位。同理，一个轮换位中的数字不能通过到达其他轮换位中，那么一个轮换位中的数字无论怎样翻转都还是原来的那四个。**

# 2. 如何判断无解呢？

### 第一种，某个数字出现次数不等于 $n$，则一定无解

这个十分显然，这个数字的出现次数都不对劲，我们又没有办法凭空替换掉其中一个数字，怎么可能复原呢？

### 第二种，某个数字出现在不该出现的列上

我们用题目中给出的样例二举例。

| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |
| ----------- | -----------: | -----------: | -----------: |
| $\color{red}4$ | $\color{brown}1$ | $\color{blue}3$ | $\color{brown}2$ |

其中 第二行第二列 的位置出现了数字 $1$，第二行第四列的位置出现了数字 $2$，根据上面提到的轮换位，那么这个数字 $1$ 不可能转到第一列，数字 $2$ 不可能转到第二列，矩阵就不可能复原，无解。

这一种情况也很好判断，只要在读入时判断一下这一列是否对应合适的数字就可以了，**第 $j$ 列上的数字就只能是 $j$ 或者 $m - j + 1$ (与 $j$ 关于矩阵水平对称)**。可以根据参考代码感性理解：

```cpp
n = read(), m = read(); // read逝快读
for (int i = 1; i <= n; ++i)
{
	for (int j = 1; j <= m; ++j)
	{
		num[i][j] = read();
		if (j != num[i][j] && j != m - num[i][j] + 1)
		{
			printf("NO\n");
			return 0;
		}
	}
}
```

### 第三种，轮换位上的同一种数字出现次数不为二

比如说这样一个矩阵：

| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}1$ |
| ----------- | -----------: | -----------: | -----------: |
| $\color{green}4$ | $\color{brown}2$ | $\color{brown}3$ | $\color{green}4$ |
| $\color{green}1$ | $\color{brown}2$ | $\color{brown}3$ | $\color{green}4$ |
| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |

其中颜色为绿色的轮换位中出现了一次数字 $1$，三次数字 $4$。

颜色为红色的轮换位中出现了三次数字 $1$，一次数字 $4$。

那么无论如何翻转，像这样的轮换位上的数字都无法复原到正常情况（正常情况下一种数字在一个轮换位中的出现次数一定为二，而这种情况下数字在这个轮换位中的出现次数已经不为二了，根据轮换位定义，数字在一个轮换位中的出现次数永远不可能发生改变，所以该情况一定无法复原到正常情况），该情况无解。

# 3. 如何复原矩阵呢？

**我们考虑对每一个轮换位依次进行复原。**

既然是依次复原，那么这一次的复原操作一定要保证对上一次的复原操作没有影响。所以我们按行枚举轮换位，那么为了不破坏这一行其他轮换位的排列顺序，**我们要保证还原一个轮换位的水平翻转的次数为偶数次。**

举个例子：

| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |
| :----------: | :----------: | :----------: | :----------: |
| $\color{red}1$ | $\color{blue}3$ | $\color{blue}2$ | $\color{red}4$  |

假设现在枚举处于第一行、第四行的轮换位，其中第一列、第四列红色的轮换位已经还原好了，我们现在要还原第二列、第三列的轮换位。

此时直接翻转第二行可以直接还原蓝色轮换位，但与此同时，红色的轮换位会被打乱，所以我们不能够这样操作。

为了保证红色轮换位不被打乱，我们要构造一个水平翻转为偶数次的还原方式，~~那么经过我们的大量手模~~，我们找到了一种合适的还原方式：先转第三列，再转第二行，再转第三列，再转第二行，这样可以还原蓝色的轮换位，也可以保证红色的轮换位不被打乱。

那么有人可能会问了：**为什么不用保证竖直翻转的次数也是偶数次呢？**

我们依然来举例子：

| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |
| ----------- | -----------: | -----------: | -----------: |
| $\color{green}4$ | $\color{brown}3$ | $\color{brown}2$ | $\color{green}4$ |
| $\color{green}1$ | $\color{brown}2$ | $\color{brown}3$ | $\color{green}1$ |
| $\color{red}1$ | $\color{blue}2$ | $\color{blue}3$ | $\color{red}4$ |

我们可以发现，在复原第二行、第三行的轮换位时，即使竖直翻转了奇数次，对于已经复原好的第一行、第四行的轮换位也没有影响（因为已经还原好的轮换位上下两部分是对称的）。

那么可能还会有人问：**那我保证竖直翻转次数是偶数会有什么坏处吗？**

这还真的有！当出现这样一种情况的轮换位时：

| $\color{red}2$ | $\color{red}1$ |
| ----------- | -----------: |
| $\color{red}2$ | $\color{red}1$ |

**如果要保证竖直翻转的次数相同，那么就最少要六步操作才能复原这个轮换位，一旦数据中所有的轮换位都是这种情况，由于共有 $\frac{mn}{4}$ 个轮换位，那么复原次数为 $1.5mn$，会因为超步数WA掉**~~（我就是因为这个赛时拿了60）。~~

如果只是保证水平翻转次数相同，那么只需要四步操作就可以复原了。这样我们就可以保证不会超步数啦~

**那么我们就只需要分类讨论轮换位的排列顺序，分别设计一种不超过四步且保证水平翻转次数相同的复原方案即可。**

**这里我们用 $1$ 来对应轮换位中较小的数字，$2$ 来对应较大的数字，下面分别为所有轮换位的排列顺序以及复原方案：**

| $\color{red}1$ | $\color{red}2$ |
| ----------- | -----------: |
| $\color{red}1$ | $\color{red}2$ |

不需操作。

| $\color{red}2$ | $\color{red}2$ |
| ----------- | -----------: |
| $\color{red}1$ | $\color{red}1$ |

转第一行，转第二列，转第一行。

| $\color{red}1$ | $\color{red}1$ |
| ----------- | -----------: |
| $\color{red}2$ | $\color{red}2$ |

转第二行，转第二列，转第二行。

| $\color{red}2$ | $\color{red}1$ |
| ----------- | -----------: |
| $\color{red}2$ | $\color{red}1$ |

转第一行，转第一列，转第二列，转第一行。

| $\color{red}2$ | $\color{red}1$ |
| ----------- | -----------: |
| $\color{red}1$ | $\color{red}2$ |

转第一列，转第一行，转第一列，转第一行。

| $\color{red}1$ | $\color{red}2$ |
| ----------- | -----------: |
| $\color{red}2$ | $\color{red}1$ |

转第二列，转第二行，转第二列，转第二行。

**以上每种情况操作步数不超过四，因为一共有 $\frac{mn}{4}$ 个轮换位，所以总操作步数不超过 $mn$，可以A掉此题。**

那么来到最后一个问题：**怎么枚举轮换位呢？**

```cpp
for (int i1 = 1, i2 = n; i1 < i2; ++i1, --i2)
{
	for (int j1 = 1, j2 = m; j1 < j2; ++j1, --j2)
	{
        // 位于第i1行、第i2行、第j1列、第j2列的一组轮换位
	}
}
```

这样就可以啦~

# 4. 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int read() // 快读
{
	int x = 0;
	char c;
	bool f = 0;
	while (!isdigit(c = getchar()))
	{
		if (c == '-')
		{
			f = 1;
		}
	}
	do
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
	} while (isdigit(c = getchar()));
	if (f)
	{
		return -x;
	}
	return x;
}

const int maxn = 110;

int n, m;
int num[maxn][maxn];

typedef pair<int, int> P;
P opt[maxn * maxn]; // 用来存操作的数组
int cnt;

// 下面两个翻转函数是真的对原数组翻转了一下，其实不用真的翻转，只需记录操作即可

void ReverseHang(int x) // 翻转一行
{
	opt[++cnt] = P(0, x); // 记录操作
	reverse(num[x] + 1, num[x] + m + 1); // 翻转这一行（可有可无）
}

int tmp[maxn];

void ReverseLie(int x)
{
	opt[++cnt] = P(1, x); // 记录操作

	// 翻转这一列（可有可无）
	for (int i = 1; i <= n; ++i)
	{
		tmp[i] = num[i][x];
	}
	for (int j = 1, i = n; j <= n; ++j, --i)
	{
		num[i][x] = tmp[j];
	}
}

void Print() // 输出矩阵（调试用）
{
	printf("now:\n");
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			printf("%d ", num[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

// 对处于第i1行、第i2行、第j1列、第j2列，左上角数为a，右上角为b，左下角为c，右下角为d的轮换位还原
void Work(int i1, int i2, int j1, int j2, int a, int b, int c, int d)
{
	if (a == b && c == d && a > c)
	{
		ReverseHang(i1);
		ReverseLie(j2);
		ReverseHang(i1);
	}
	else if (a == b && c == d && a < c)
	{
		ReverseHang(i2);
		ReverseLie(j2);
		ReverseHang(i2);
	}
	else if (a == c && b == d && a > b)
	{
		ReverseHang(i1);
		ReverseLie(j1);
		ReverseLie(j2);
		ReverseHang(i1);
	}
	else if (a == d && b == c && a > b)
	{
		ReverseLie(j1);
		ReverseHang(i1);
		ReverseLie(j1);
		ReverseHang(i1);
	}
	else if (a == d && b == c && b > a)
	{
		ReverseLie(j2);
		ReverseHang(i2);
		ReverseLie(j2);
		ReverseHang(i2);
	}
}

int tot[maxn];

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			num[i][j] = read();
			++tot[num[i][j]];
			if (j != num[i][j] && j != m - num[i][j] + 1)
			{
				// 无解情况二
				printf("NO\n");
				return 0;
			}
		}
	}
	for (int i = 1; i <= m; ++i)
	{
		if (tot[i] != n)
		{
			// 无解情况一
			printf("NO\n");
			return 0;
		}
	}
	for (int i1 = 1, i2 = n; i1 < i2; ++i1, --i2)
	{
		for (int j1 = 1, j2 = m; j1 < j2; ++j1, --j2)
		{
			// 枚举第i1行、第i2行、第j1列、第j2列的轮换位，记左上角数为a，右上角为b，左下角为c，右下角为d
			int a = num[i1][j1], b = num[i1][j2], c = num[i2][j1], d = num[i2][j2];
			// 笨拙的判无解情况三操作）
			int n1 = a, c1 = 1, c2 = 0;
			if (b == n1) ++c1;
			else ++c2;
			if (c == n1) ++c1;
			else ++c2;
			if (d == n1) ++c1;
			else ++c2;
			if (c1 != 2)
			{
				printf("NO\n");
				return 0;
			}
			// 复原
			Work(i1, i2, j1, j2, a, b, c, d);
		}
	}
	// 输出操作
	printf("YES\n");
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; ++i)
	{
		printf("%d %d\n", opt[i].first, opt[i].second);
	}
}

```


---

## 作者：LJ07 (赞：3)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/P8221)
## 思路简述
+ 容易发现这样一个规律：无论是行翻转还是列翻转，$(x,y)$，$(x,m-x+1)$，$(n-x+1,y)$，$(n-x+1,y-n+1)$ 这四个位置上的值总是固定的 $4$ 个数。
+ 所以可以想到对于每一个这样的 $4$ 个位置进行分类讨论，最好能使得它进行平均最多不多于 $4$ 次操作能够调换成符合题目要求的形态并且不影响其他位置。
+ 而不影响其他位置，暂时简单理解行或列翻转偶数次。
+ 不妨设目标状态为 $\begin{matrix}a\ b\\a\ b \end{matrix}$，而翻转第 $n-x+1$ 行的操作定义为 D, 翻转第 $x$ 行的操作定义为 U, 翻转第 $y$ 列的操作定义为 L, 翻转第 $m-y+1$ 的操作定义为 R。
+ 一共有以下 $6$ 种情况。
1. 当前状态为 $\begin{matrix}a\ b\\a\ b \end{matrix}$， 无需操作
1. 当前状态为 $\begin{matrix}a\ b\\b\ a \end{matrix}$， 操作为 RDRD。
1. 当前状态为 $\begin{matrix}b\ a\\a\ b \end{matrix}$， 操作为 LULU。
1. 当前状态为 $\begin{matrix}a\ a\\b\ b \end{matrix}$， 操作为 DRDR。
1. 当前状态为 $\begin{matrix}b\ a\\b\ a \end{matrix}$， 操作为 DLRDLR。
1. 当前状态为 $\begin{matrix}b\ b\\a\ a \end{matrix}$， 操作为 DLDL。
+ 然而我们发现情况 $5$ 的操作数多达 $6$ 个，容易导致步数过多。
+ 我们又发现，我们对行或列没有影响的要求，事实上是为了保证原先已经达成目标状态的 $4$ 个位置不要因为当前的操作而发生改变。那么可以这么认为，列的翻转不会对它们产生影响。
+ 那么情况 $5$ 的操作就可以变成 DLR，但是同时要模拟列翻转的过程（事实上应该每种情况都可以这样节省步数，不过常数会更大），时间复杂度为 $O(n^3)$，但实际上应该远远达不到。

## 丑陋の代码
[click here](https://www.luogu.com.cn/paste/nvot40sl)

---

## 作者：LKY928261 (赞：3)

## 题目分析

题意大致是：求能使矩阵变成目标矩阵的具体方案，每次操作只能翻转一个行或列，且要求在 $n \times m$ 次操作内完成。

#### 判错

根据观察，我们可以发现：由于每次操作是相对对称的，所以每对称的四个点中，不论怎样操作，这四个数总在对应的四个位置上。

因此，只需依次判断每四个位置对称的数是否符合题意，即可判断矩阵可否通过操作变成目标矩阵。

具体如下：
 
- 当四个数中有既不是 $j$ 也不是 $m-j+1$ 的数出现，直接输出 ``NO`` ；

- 当四个数中 $j$ （或 $m-j+1$）的个数不是2个，直接输出 ``NO`` 。

局部代码：

```cpp
if(
	(a[i][j]!=j&&a[i][j]!=m-j+1)||
	(a[i][m-j+1]!=j&&a[i][m-j+1]!=m-j+1)||
	(a[n-i+1][j]!=j&&a[n-i+1][j]!=m-j+1)||
	(a[n-i+1][m-j+1]!=j&&a[n-i+1][m-j+1]!=m-j+1)||
	//判断数字是否符合要求
	((a[i][j]==j)+(a[i][m-j+1]==j)+(a[n-i+1][j]==j)+(a[n-i+1][m-j+1]==j)!=2)
	//判断个数是否符合要求
)
{cout<<"NO\n";re 0;}
```

#### 求解

方便起见，可以将矩阵中的数字在判错的同时改为布尔值，便于判断状态。

为了维护矩阵，我们每次对行操作，就要再操作一次来抵消对其他位置的影响。至于对列操作，由于目标矩阵上列的对称性，则不用如此麻烦，直接交换即可。

假设改为布尔值后的目标状态为：(令 `1` 代表 $j$，`0` 代表 $m-j+1$)

$$\begin{matrix}
1 & 0 \\ 
1 & 0
\end{matrix}$$

我们暂且以 ``U`` 表示对上方的行操作，``D`` 表示对下方的行操作，``L`` 表示对左方的列操作，``R`` 表示对右方的列操作。

接下来分情况讨论：

- $\begin{matrix}1 & 0 \\ 1 & 0 \end{matrix}$ ：已经恢复至目标状态，不用操作；

- $\begin{matrix}1 & 1 \\ 0 & 0 \end{matrix}$ ：需要 ``D,R,D`` 3次操作还原；

- $\begin{matrix}1 & 0 \\ 0 & 1 \end{matrix}$ ：需要 ``R,D,R,D`` 4次操作还原；

- $\begin{matrix}0 & 1 \\ 1 & 0 \end{matrix}$ ：需要 ``R,U,R,U`` 4次操作还原；

- $\begin{matrix}0 & 0 \\ 1 & 1 \end{matrix}$ ：需要 ``U,R,U`` 3次操作还原；

- $\begin{matrix}0 & 1 \\ 0 & 1 \end{matrix}$ ：需要 ``D,L,R,D`` 4次操作还原。

由于每次操作次数均不超过 $4$，枚举次数不超过 $\frac{nm}{4}$，所以总操作数不会超过 $nm$ 次。

局部代码

```cpp
for(i=1;i<=n/2;i++)for(j=1;j<=m/2;j++){
	k=a[i][j]*1000+a[i][m-j+1]*100+a[n-i+1][j]*10+a[n-i+1][m-j+1];
	//此处的k是为了方便判断
	if(k==1100){b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;for(g=1;g<=n/2;g++)swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
	else if(k==1001){b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;}
	else if(k==110){b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;}
	else if(k==101){b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=j;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;for(g=1;g<=n/2;g++)swap(a[g][j],a[n-g+1][j]),swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
	else if(k==11){b[T]=0;c[T++]=i;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;for(g=1;g<=n/2;g++)swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
}
```

最后，再对奇数进行特殊处理:

```cpp
if(n&1)for(j=1;j<=m;j++)if(a[n/2+1][j]!=j){cout<<"NO\n";re 0;}
if(m&1)for(i=1;i<=n;i++)if(a[i][m/2+1]!=m/2+1){cout<<"NO\n";re 0;}
```

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define re return
using namespace std;
int n,m,k,a[105][105],T,b[10005],c[10005],i,j,g;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)cin>>a[i][j];
	for(i=1;i<=n/2;i++)for(j=1;j<=m/2;j++){
		if(
		(a[i][j]!=j&&a[i][j]!=m-j+1)||
		(a[i][m-j+1]!=j&&a[i][m-j+1]!=m-j+1)||
		(a[n-i+1][j]!=j&&a[n-i+1][j]!=m-j+1)||
		(a[n-i+1][m-j+1]!=j&&a[n-i+1][m-j+1]!=m-j+1)||
		((a[i][j]==j)+(a[i][m-j+1]==j)+(a[n-i+1][j]==j)+(a[n-i+1][m-j+1]==j)!=2)
		){cout<<"NO\n";re 0;}
		a[i][j]=(a[i][j]==j);
		a[i][m-j+1]=(a[i][m-j+1]==j);
		a[n-i+1][j]=(a[n-i+1][j]==j);
		a[n-i+1][m-j+1]=(a[n-i+1][m-j+1]==j);
	}
	if(n&1)for(j=1;j<=m;j++)if(a[n/2+1][j]!=j){cout<<"NO\n";re 0;}
	if(m&1)for(i=1;i<=n;i++)if(a[i][m/2+1]!=m/2+1){cout<<"NO\n";re 0;}
	for(i=1;i<=n/2;i++)for(j=1;j<=m/2;j++){
		k=a[i][j]*1000+a[i][m-j+1]*100+a[n-i+1][j]*10+a[n-i+1][m-j+1];
		if(k==1100){b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;for(g=1;g<=n/2;g++)swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
		else if(k==1001){b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;}
		else if(k==110){b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;}
		else if(k==101){b[T]=0;c[T++]=n-i+1;b[T]=1;c[T++]=j;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=n-i+1;for(g=1;g<=n/2;g++)swap(a[g][j],a[n-g+1][j]),swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
		else if(k==11){b[T]=0;c[T++]=i;b[T]=1;c[T++]=m-j+1;b[T]=0;c[T++]=i;for(g=1;g<=n/2;g++)swap(a[g][m-j+1],a[n-g+1][m-j+1]);}
	}
	cout<<"YES\n"<<T<<"\n";
	for(i=0;i<T;i++)cout<<b[i]<<' '<<c[i]<<"\n";
	//本人从不打return 0;
}
```

---

## 作者：int08 (赞：1)

# 前言
~~非常有趣的~~构造题。

个人觉得和高阶魔方中间块的还原部分非常像，各位可以去逝一逝。

# Solution

## 探讨

定义 $(i,j)$ 为第 $i$ 行第 $j$ 列。

首先我们容易发现一个规律：

1、无论怎么翻转，最多只有 $(i,j),(n+1-i,j),(i,m+1-j),(n+1-i,m+1-j)$ 四个点成为一组，一组之间可能可以互相交换，但是一组的数字不会去到其他组。

那么现在就是很简单了：

我们只需要一组一组的换，如果组内出现了不该出现的数字，即情况非法，就判定不能还原，否则就可以。

但是要注意，**交换本组数字的时候不能打乱已经复原的组**，就像还原魔方一样。然后保证每一组的所有合法情况都能在 $4$ 步内还原就行了。

## 分类讨论

为了方便~~打字~~理解，用

| 1 | 2 |
| :----------: | :----------: |
| 1 | 2 |

表示在一组中还原后的情况。

L 表示将左边的一列翻转，R 表示翻转右列，U 表示将上面的一行翻转，D 表示翻转下行。

总共有 $6$ 种合法情况，解法如下：

1：

| 1 | 1 |
| :----------: | :----------: |
| 2 | 2 |

solution:DRDR

2：

| 1 | 2 |
| :----------: | :----------: |
| 1 | 2 |

~~solution:nothing~~

3：

| 1 | 2 |
| :----------: | :----------: |
| 2 | 1 |

solution:LDLD

4：

| 2 | 1 |
| :----------: | :----------: |
| 1 | 2 |

solution:RURU

5：

| 2 | 2 |
| :----------: | :----------: |
| 1 | 1 |

solution:DLDL

6：

| 2 | 1 |
| :----------: | :----------: |
| 2 | 1 |

solution:DLRD

其中第6种情况比较特殊：这种情况解决之后，两列都翻转过一次，但是只要按照按列优先的方式一组一组解决，翻转不会打乱已经解决的组，没解决的不影响，跟着换就是了。

所以最后肯定能在 $n\times m \div 4\times4=n\times m$ 之内解决啦！

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,z[114][514],i,j,l,r,a,b,ans[2][10086],an; 
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>z[i][j];
	for(j=1;j<=m/2;j++)
	{
		l=0;r=0;
		for(i=1;i<=n/2;i++)
		{
			a=0;b=0;
			if(l) swap(z[i][j],z[n+1-i][j]);
			if(r) swap(z[i][m+1-j],z[n+1-i][m+1-j]);
			if(z[i][j]==j) a++;if(z[i][j]==m+1-j) b++;
			if(z[i][m+1-j]==j) a++;if(z[i][m+1-j]==m+1-j) b++;
			if(z[n+1-i][j]==j) a++;if(z[n+1-i][j]==m+1-j) b++;
			if(z[n+1-i][m+1-j]==j) a++;if(z[n+1-i][m+1-j]==m+1-j) b++;
			if(a!=2||b!=2){
				cout<<"NO";
				return 0;
			}
			if(z[i][j]==j&&z[i][m+1-j]==j)
			{
				ans[0][an+1]=0;ans[1][an+1]=n+1-i;
				ans[0][an+2]=1;ans[1][an+2]=m+1-j;
				ans[0][an+3]=0;ans[1][an+3]=n+1-i;
				ans[0][an+4]=1;ans[1][an+4]=m+1-j;
				an+=4;
			}
			if(z[i][j]==j&&z[n+1-i][m+1-j]==j)
			{
				ans[0][an+1]=1;ans[1][an+1]=m+1-j;
				ans[0][an+2]=0;ans[1][an+2]=n+1-i;
				ans[0][an+3]=1;ans[1][an+3]=m+1-j;
				ans[0][an+4]=0;ans[1][an+4]=n+1-i;
				an+=4;
			}
			if(z[i][m+1-j]==j&&z[n+1-i][j]==j)
			{
				ans[0][an+1]=1;ans[1][an+1]=m+1-j;
				ans[0][an+2]=0;ans[1][an+2]=i;
				ans[0][an+3]=1;ans[1][an+3]=m+1-j;
				ans[0][an+4]=0;ans[1][an+4]=i;
				an+=4;
			}
			if(z[i][m+1-j]==j&&z[n+1-i][m+1-j]==j)
			{
				l=(l+1)%2;r=(r+1)%2;
				ans[0][an+1]=0;ans[1][an+1]=n+1-i;
				ans[0][an+2]=1;ans[1][an+2]=m+1-j;
				ans[0][an+3]=1;ans[1][an+3]=j;
				ans[0][an+4]=0;ans[1][an+4]=n+1-i;
				an+=4;
			}
			if(z[n+1-i][j]==j&&z[n+1-i][m+1-j]==j)
			{
				ans[0][an+1]=0;ans[1][an+1]=i;
				ans[0][an+2]=1;ans[1][an+2]=m+1-j;
				ans[0][an+3]=0;ans[1][an+3]=i;
				ans[0][an+4]=1;ans[1][an+4]=m+1-j;
				an+=4;
			}
		}
	}
	cout<<"YES\n"<<an<<"\n";
	for(i=1;i<=an;i++) cout<<ans[0][i]<<" "<<ans[1][i]<<"\n";
	return 0;
}
```

---

## 作者：do_while_true (赞：1)

如果只有一行并翻转这一行，那么只有关于中心对称的两个位置会发生交换，一列也同理。所以对于这个矩阵来说，无论怎样翻转，都每对称的四个位置上的数发生交换。所以可以先判断每对称的四个位置组成的集合是否与目标状态的集合相同，若不同则无解。

否则给出一个构造方案：

从上到下一行一行考虑每一组四个位置，对于以下六种情况：

```
x y
x y

x y
y x

y x
x y

y x
y x

x x
y y

y y
x x
```

我们都想把它们还原成

```
x y
x y
```

并且不会打乱前面还原过的组。

注意到对于每一组，一行是不对称的，但是列是对称的。所以列反转几次都无所谓，但是行必须反转偶数次。

那么对于六种情况，皆构造出一组方案，满足每一行反转偶数次从而不影响前面的还原即可。

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=110;
int n,m;
int v[N][N];
vpii b;
void swap0(int x){
	b.pb(mp(0,x));
	for(int i=1;i<=m/2;i++)
		swap(v[x][i],v[x][m-i+1]);
}
void swap1(int x){
	b.pb(mp(1,x));
	for(int i=1;i<=n/2;i++)
		swap(v[i][x],v[n-i+1][x]);
}
signed main(){
	read(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(v[i][j]);
	for(int i=1;i<=n/2;i++)
		for(int j=1;j<=m/2;j++){
			int &a=v[i][j],&b=v[i][m-j+1];
			int &c=v[n-i+1][j],&d=v[n-i+1][m-j+1];
			int v1=j,v2=m-j+1;
			if((a==j)+(b==j)+(c==j)+(d==j)!=2){
				puts("NO");
				return 0;
			}
			if((a==m-j+1)+(b==m-j+1)+(c==m-j+1)+(d==m-j+1)!=2){
				puts("NO");
				return 0;
			}
			if(a==v1&&b==v2&&c==v1&&d==v2)continue;
			if(a==v1&&b==v2&&c==v2&&d==v1){
				swap1(j);
				swap0(i);
				swap1(m-j+1);
				swap0(i);
				continue;
			}
			if(a==v2&&b==v1&&c==v1&&d==v2){
				swap1(j);
				swap0(n-i+1);
				swap1(m-j+1);
				swap0(n-i+1);
				continue;
			}
			if(a==v2&&b==v1&&c==v2&&d==v1){
				swap0(n-i+1);
				swap1(m-j+1);
				swap1(j);
				swap0(n-i+1);
				continue;
			}
			if(a==v1&&b==v1&&c==v2&&d==v2){
				swap0(n-i+1);
				swap1(m-j+1);
				swap0(n-i+1);
				continue;
			}
			if(a==v2&&b==v2&&c==v1&&d==v1){
				swap0(i);
				swap1(m-j+1);
				swap0(i);
				continue;
			}
			do{}while(true);
		}
	puts("YES");
	cout << b.size() << '\n';
	for(auto x:b)cout << x.fi << ' ' << x.se << '\n'; 
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Preface

比 I wanna 还难（确信）。

### Analysis

判无解很简单：对称的 $4$ 个点的权值是否可以重排到目标状态。

然后就是构造。

由于目标状态一列中值都相同，我们考虑将对称的 $4$ 个位置归位而每行最后都相当于没被 reverse 过，这样我们可以按靠外列到靠中心列求解。

将这 $4$ 个值取出为 $2\times 2$ 的矩阵，设目标为

$$\begin{bmatrix}x&y\\x&y\end{bmatrix}$$

设 L0 表示 reverse 靠左的这列，H0 表示 reverse 靠上的这行，L1、R1 同理表示 reverse 右列、下行。

公式 ~~魔方乱入~~：

#### 状态 1（对侧）

$$\begin{bmatrix}y&x\\y&x\end{bmatrix}$$

```
H0L0L1H0
```

#### 状态 2（上下）

$$\begin{bmatrix}y&y\\x&x\end{bmatrix}$$

```
H0L1H0
```

$$\begin{bmatrix}x&x\\y&y\end{bmatrix}$$

```
H1L1H1
```

#### 状态 3（斜侧）

$$\begin{bmatrix}y&x\\x&y\end{bmatrix}$$

```
L1H0L1H0
```

$$\begin{bmatrix}x&y\\y&x\end{bmatrix}$$

```
L1H1L1H1
```

分类结束。

由于对称的 $4$ 元组个数 $\le\frac{n\cdot m}4$，所以操作次数 $\le 4\frac{n\cdot m}4=n\times m$

### Code

代码中 $x,y,a,b$：

| 坐标 | y | b |
| -----------: | -----------: | -----------: |
| **x** | sth. | sth. |
| **a** | sth. | sth. |


```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define N 102
#define endl '\n'
int c[N][N],n,m;
bool rev[N];//列是否被翻转 
vector<pair<bool,int> > ans;//答案操作序列 
void modi(bool x,int y){
	if(x) rev[y]^=1;
	ans.pb(mkp(x,y));
}
inline int C(int x,int y){return rev[y]?c[n-x+1][y]:c[x][y];}
int cnt;
inline bool pan(int x,int y,int val){
	if(c[x][y]!=val && c[x][y]!=m-val+1) return false;
	if(c[x][y]==val) cnt++;
	return true;
}
#define a n-x+1//x 对称 
#define b m-y+1//y 对称 
inline void work(string s,int x,int y){
	int len=s.size();
	for(int i=0;i<len;i+=2){
		if(s.substr(i,2)=="L0") modi(1,y);
		if(s.substr(i,2)=="L1") modi(1,b);
		if(s.substr(i,2)=="H0") modi(0,x);
		if(s.substr(i,2)=="H1") modi(0,a);
	}
}
bool check(int x,int y){
	cnt=0;
	if(!pan(x,y,y) || !pan(x,b,y) || !pan(a,y,y) || !pan(a,b,y) || cnt!=2) return false;
	#define val y
	//以下 5 个与题解顺序相同 
	     if(C(x,b)==val && C(a,b)==val) work("H0L0L1H0",x,y);
	else if(C(a,y)==val && C(a,b)==val) work("H0L1H0"  ,x,y);
	else if(C(x,y)==val && C(x,b)==val) work("H1L1H1"  ,x,y);
	else if(C(x,b)==val && C(a,y)==val) work("L1H0L1H0",x,y);
	else if(C(x,y)==val && C(a,b)==val) work("L1H1L1H1",x,y);
	return true;
}
signed main(){IOS;
	cin>>n>>m;
	For(i,1,n) For(j,1,m) cin>>c[i][j];
	For(j,1,(m>>1)) For(i,1,(n>>1)) if(!check(i,j)){cout<<"NO"<<endl;return 0;}
	cout<<"YES"<<endl<<ans.size()<<endl;
	for(auto i:ans) cout<<i.fir<<" "<<i.sec<<endl;
return 0;}
```

---

## 作者：jockbutt (赞：0)

简单思维题。

# Solution

首先不难~~能~~发现，一个数最多只能被换到四个位置，首先判断这四个位置的值是否符合题目要求，判掉无解情况。

然后，我们可以每四个四个换，依次把它们换到正确位置。  
因为最终状态竖着的所有数都是一样的，可以换任意多次数，而横着换只能换偶数次。于是，在手玩几次后，我们就可以推出交换的方式。

因为换的情况巨多，我没有想到很好的循环写法，只有一种一种地特判断。

最后注意，因为最开始的矩阵不是有序的，所以在竖着交换的时候一定要暴力交换一下。

具体细节在代码里面。

# Code 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pause while(1){cout<<"AK";}
int n,m;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int a[110][110],tot;
struct node{
	int x,y;
}p[10010];
//(i,j)  (n-i+1,j)   (i,m-j+1)   (n-i+1,m-j+1)     2j    2(n-j+1)
inline void H(int x)
{
	p[++tot]=(node){0,x};
	for(int i=1;i<=m/2;++i)	swap(a[x][i],a[x][m-i+1]);
}
inline void S(int x)
{
	p[++tot]=(node){1,x};
	for(int i=1;i<=n/2;++i)	swap(a[i][x],a[n-i+1][x]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			a[i][j]=read();
		}
	}
	for(int i=1;i<=n/2;++i)
	{
		for(int j=1,t1,t2;j<=m/2;++j)
		{
			t1=t2=0;
			if(a[i][j]==j)	t1++;
			if(a[i][j]==m-j+1)	t2++;
			if(a[n-i+1][j]==j)	t1++;
			if(a[n-i+1][j]==m-j+1)	t2++;
			if(a[n-i+1][m-j+1]==j)	t1++;
			if(a[n-i+1][m-j+1]==m-j+1)	t2++;
			if(a[i][m-j+1]==j)	t1++;
			if(a[i][m-j+1]==m-j+1)	t2++;
			if(t1!=2||t2!=2)
			{
				printf("NO\n");
				return 0;
			}
			if(a[i][j]==j&&a[n-i+1][j]==j)	continue;
			else	if(a[i][j]==j&&a[n-i+1][m-j+1]==j)	S(m-j+1),H(n-i+1),S(m-j+1),H(n-i+1);
			else	if(a[i][j]==j&&a[i][m-j+1]==j)	H(n-i+1),S(m-j+1),H(n-i+1);
			else	if(a[i][m-j+1]==j&&a[n-i+1][j]==j)	S(m-j+1),H(i),S(m-j+1),H(i);
			else	if(a[i][m-j+1]==j&&a[n-i+1][m-j+1]==j)	H(i),S(j),S(m-j+1),H(i);
			else	if(a[n-i+1][j]==j&&a[n-i+1][m-j+1]==j)	H(i),S(m-j+1),H(i);
		}
	}
	printf("YES\n%lld\n",tot);
	for(int i=1;i<=tot;++i)
	{
		printf("%lld %lld\n",p[i].x,p[i].y);
	}
	// for(int i=1;i<=n;++i)
	// {
	// 	for(int j=1;j<=m;++j)
	// 	{
	// 		printf("%lld ",a[i][j]);
	// 	}
	// 	puts("");
	// }
	return 0;
}
/*
6 6
1 2 3 4 5 6
6 5 4 3 2 1
1 2 3 4 5 6
1 2 3 4 5 6
6 5 3 4 2 1
1 5 3 4 2 6




*/
```


---

