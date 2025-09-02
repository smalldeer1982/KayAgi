# The Very Beautiful Blanket

## 题目描述

Kirill wants to weave the very beautiful blanket consisting of $ n \times m $ of the same size square patches of some colors. He matched some non-negative integer to each color. Thus, in our problem, the blanket can be considered a $ B $ matrix of size $ n \times m $ consisting of non-negative integers.

Kirill considers that the blanket is very beautiful, if for each submatrix $ A $ of size $ 4 \times 4 $ of the matrix $ B $ is true:

- $ A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}, $
- $ A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}, $

where $ \oplus $ means [bitwise exclusive OR](https://en.wikipedia.org/wiki/Exclusive_or)

Kirill asks you to help her weave a very beautiful blanket, and as colorful as possible!

He gives you two integers $ n $ and $ m $ .

Your task is to generate a matrix $ B $ of size $ n \times m $ , which corresponds to a very beautiful blanket and in which the number of different numbers maximized.

## 说明/提示

In the first test case, there is only 4 submatrix of size $ 4 \times 4 $ . Consider a submatrix whose upper-left corner coincides with the upper-left corner of the matrix $ B $ :

 $  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

 $ 9740 \oplus 1549 \oplus 1550 \oplus 1551 $ $ = $ $ 10256 \oplus 2065 \oplus 2066 \oplus 2067 $ $ = $ $ 8192 $ ;

 $ 10252 \oplus 2061 \oplus 2062 \oplus 2063 $ $ = $ $ 9744 \oplus 1553 \oplus 1554 \oplus 1555 $ $ = $ $ 8192 $ .

So, chosen submatrix fits the condition. Similarly, you can make sure that the other three submatrices also fit the condition.

## 样例 #1

### 输入

```
4
5 5
4 4
4 6
6 6```

### 输出

```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131```

# 题解

## 作者：六楼溜刘 (赞：20)

## 题意
你需要构造一个 $n \times m$ 的正整数矩阵，使得任意 $4 \times 4$ 大小的子矩阵中，左上角四个点的异或和和右下角四个相等，右上角四个和左下角四个相等。
```
a b c d
e f g h
i j k l 
m n o p
```
即在上图中，$a \oplus b \oplus e \oplus f = k \oplus l \oplus o \oplus p$ 且 $c \oplus d \oplus g \oplus h = i \oplus j \oplus m \oplus n$。

此外，你要使矩阵中不同的数字尽可能多，先输出不同数字的数量，再输出这个矩阵。

## 题解
构造题，我不晓得咋个讲，先说答案。

> 对于数字总量，直接输出 $n \times m$。

> 对于矩阵的第 $i$ 行第 $j$ 列，输出 $(i \times 2^9) \oplus j$。

## code
```cpp
#include<cstdio>
int t,n,m;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		printf("%d\n",n*m);
		for(int i=1;i<=n;i++,puts(""))
			for(int j=1;j<=m;j++)
				printf("%d ",(i<<9)^(j));
	}
}
//其实我写这个题解就是为了炫耀我这个巨短的代码的
```
## 正确性证明

- 为什么满足“异或和相等”的条件？

假设有以下一个子矩阵。
```
a b
c d
```
令 $a$ 在第 $i$ 行 $j$ 列，则：

$$a = (i \times 2^9) \oplus j$$
$$b = (i \times 2^9) \oplus (j + 1)$$
$$c = ((i + 1) \times 2^9) \oplus j$$
$$d = ((i + 1) \times 2^9) \oplus (j + 1)$$

故 

$a \oplus b \oplus c \oplus d$

$ = ((i \times 2^9) \oplus (i \times 2^9)) \oplus (((i + 1) \times 2^9) \oplus ((i + 1) \times 2^9)) \oplus (j \oplus j) \oplus ((j + 1) \oplus (j + 1))$

$= 0 \oplus 0 \oplus 0 \oplus 0$

$= 0$

显然所有 $2 \times 2$ 的子矩阵异或和都为 $0$，满足条件。

- 为什么满足互不相等？

其实这反过来问就是为什么 $i$ 要乘以 $2^9$。

由于 $m,n \leq 200$，故 $2^9=512 \ge m$。

那么将 $i$ 乘上这个数，不仅不会使局部二进制位变化，还使其不会影响 $j$ 管辖的后 $8$ 位，不会出现 $i,j$ 两部分互相影响导致数字重复的情况，此时异或等价于加法。

所以其实不一定要乘 $2^9$，也不一定要 $i$ 来乘，只要保证不爆 `long long`，也不影响另一部分、等价于加法就行了。

---

## 作者：olegekei (赞：12)

## 思路
题目要求每个 $4 \times 4$ 大小的子矩阵都要满足：

- 左上角四个元素异或和等于右下角四个元素异或和
- 右上角四个元素异或和等于左下角四个元素异或和

那么我们不妨从 $2 \times 2$ 大小的矩阵开始构造。

因为异或和相等，所以可以先考虑直接让异或和等于 $0$，那么容易构造出一个矩阵为：

$$\begin{Bmatrix}0 & 1 \\2 & 3\end{Bmatrix}$$

那么相应的，$4 \times 4$ 大小的矩阵也容易构造出：

$$\begin{Bmatrix}
0 & 1 & 4 & 5\\
2 & 3 & 6 & 7\\
8 & 9 &12 &13\\
10&11 &14 &15\\
\end{Bmatrix}$$

但是很明显如果 $n \times m$ 略大一点这个子矩阵就会挂掉，我们需要修改这个子矩阵让他具有更广泛的适用性：

$$\begin{Bmatrix}
 0 & 1 & 4 & 5\\
 2 & 3 & 6 & 7\\
512&513&516&517\\
514&515&518&519\\
\end{Bmatrix}$$

因为 $n,m \le 200$，每两行最多出现 $400$ 个数字，所以将构造方案中将每两行之后的下一个 $base$ 设置为 $512$，可以保证矩阵内的数字不重复。

接下来考虑更大一点的矩阵如何构造。

我们先考虑 $4 \times 5$ 大小的矩阵。因为只有两个 $4 \times 4$ 大小的矩阵，且我们已经构造出了其中一个，现在只需要考虑如何构造出另一个矩阵即可，取出前面矩阵的部分元素：

$$\begin{Bmatrix}
 1 & 4 & 5 &x_1\\
 3 & 6 & 7 &x_2\\
513&516&517&x_3\\
515&518&519&x_4\\
\end{Bmatrix}$$

取出左上角和左下角四个元素，发现 $1 \oplus 4 \oplus 3 \oplus 6 = 513 \oplus 516 \oplus 515 \oplus 518 = 0$，刚好异或和为 $0$，现在我们只需要让 $x_1 \oplus x_2 = 5 \oplus 7,x_3 \oplus x_4 = 517 \oplus 519$ 即可。

我们又发现，$5 \oplus 7 = 517 \oplus 519 =2$，那么我们就可以从 $7$ 和 $519$ 开始向后枚举 $a,b$ 使 $a \oplus b =2$，发现枚举出了 $(8,10)$ 和 $(520,522)$，放到之前的矩阵中：

$$\begin{Bmatrix}
 0 & 1 & 4 & 5 & 8\\
 2 & 3 & 6 & 7 &10\\
512&513&516&517&520\\
514&515&518&519&522\\
\end{Bmatrix}$$

发现 $4 \times m$ 的矩阵呼之欲出了：

$$\begin{Bmatrix}
 0 & 1 & 4 & 5 & 8 & 9 &11+1&11+2&\cdots\\
 2 & 3 & 6 & 7 &10 &11 &11+3&11+4&\cdots\\
512&513&516&517&520&521&522+1&522+2&\cdots\\
514&515&518&519&522&522&522+3&522+4&\cdots\\
\end{Bmatrix}$$

简单手玩一下发现矩阵合法，那么接下来需要考虑 $n>4$ 时的矩阵如何构造。仍然保持当前规律不变，设 $n=6,m=4$，尝试按照当前规律构造：

$$\begin{Bmatrix}
 0 & 1 & 4 & 5\\
 2 & 3 & 6 & 7\\
512&513&516&517\\
514&515&518&519\\
1024&1025&1028&1029\\
1026&1027&1030&1031\\
\end{Bmatrix}$$

简单手玩，发现矩阵仍然合法，设置 $n>6,m>6$，再次检查，仍合法，最终得到构造方案：

$$\begin{Bmatrix}
 A_{1,1} & A_{1,2} & A_{1,2}+3 & A_{1,2}+4 & A_{1,2}+7&\cdots\\
 A_{2,1} & A_{2,2} & A_{2,2}+3 & A_{2,2}+4 & A_{2,2}+7&\cdots\\
A_{1,1}+512&A_{1,2}+512&\cdots&\cdots&\cdots&\cdots\\
A_{2,1}+512&A_{2,2}+512&\cdots&\cdots&\cdots&\cdots\\
A_{1,1}+1024&A_{2,2}+1024&\cdots&\cdots&\cdots&\cdots\\
\cdots&\cdots&\cdots&\cdots&\cdots&\cdots\\
\end{Bmatrix}$$

## 代码
代码实现上可能略有不同，但构造出的矩阵是相同的。
```cpp
#include<iostream>
using namespace std;
int main(){
int t;
cin>>t;
while(t--){
	int n,m;
	cin>>n>>m;
	cout<<n*m<<'\n';
	int i=0;
	long long bas=0;
	while(i<n){
		i++;
		for(int j=0,cnt=0;j<m;j++){
			cout<<bas+j+cnt<<' ';
			if(j&1)cnt+=2;
		}
		cout<<'\n';
		if(i&1)bas+=2;
		else bas+=510;
	}
}
return 0;
}
```

---

## 作者：hgckythgcfhk (赞：4)

考虑把这个题加强一下，其实加强后反而好做。

构造一个矩阵，使得该矩阵的所有 $2\times 2$ 的子矩阵异或和都为 $0$。

不难证明，这个限制强于原题，是原题的必要不充分条件，考虑弱化，我们先强行规定数据范围可以到 $n=2$，考虑 $n=2$ 的情况。

一个显然的结论，相邻两个自然数的异或值为 $1$。

证明：

设 $a$ 为任意的非负偶数，所以 $a\operatorname{and} 1=0$，则有 $a+1=a\operatorname{xor} 1$。

对于任意的正奇数 $b$，则有非负偶数 $a=b-1$ 成立，证毕。

这个结论告诉我们 $a\operatorname{xor}(a+1)\operatorname{xor}(a+1)\operatorname{xor}(a+2)=0$。

所以，我们可以输出一行连续的奇数和一行连续的偶数。

考虑更多行的情况，我们可以把前两行复制一下，然后把每连续的两行或上一个 lowbit 很大的数，这个数要求每两行的相同而两行与两行之间的不同，这样最终这个大数不会有贡献，可以自己手搓一下试试。

这样一定可以使得每个数互不相同。

为防止因为火车头被打回，同时防止删除宏定义导致程序无法运行，我这里直接放 CF 上的[提交记录](https://codeforces.com/contest/1801/submission/255475028)。

---

## 作者：expecto__patronum (赞：4)

## 分析：
想了半个小时也没想出怎么构造，然后突然想到可以大力随机化。

显然可以所有格子都填不同的数字，我们只需要让所有 $2⋅2$ 的格子异或和都相等即可。

我们可以直接随机一个值作为所有 $2⋅2$ 的格子异或和，然后随机出第一行和第一列的值，然后用递推的方式计算出剩下位置的值，如果填的所有数字都不同我们就输出，否则继续以上过程。不难发现因为数字的范围足够大，很容易随机到一组解。

## Code:
```
#include<bits/stdc++.h>
using namespace std;
using LL = long long;

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    mt19937_64 rnd(random_device{}());
    uniform_int_distribution<LL> dist(0, LLONG_MAX);

    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        vector<vector<LL> > a(n, vector<LL>(m));
        while(1){
            for(int i = 0; i < n; i++) a[i][0] = dist(rnd);
            for(int i = 0; i < m; i++) a[0][i] = dist(rnd);
            set<LL> s;
            LL target = dist(rnd);
            for(int i = 1; i < n; i++){
                for(int j = 1; j < m; j++){
                    a[i][j] = target ^ a[i - 1][j - 1] ^ a[i][j - 1] ^ a[i - 1][j];
                }
            }
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    s.insert(a[i][j]);
                }
            }
            if (s.size() == n * m){
                cout << n * m << '\n';
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < m; j++){
                        cout << a[i][j] << " \n"[j == m - 1];
                    }
                }
                break;
            }
        }
    }

}
```


---

## 作者：LJY_ljy (赞：3)

## 0.说点题外话

1. 2023 年 3 月份发现了这道题，当时由于 2022 年 NOIP 后退役全力学 MO 然后在省选前打算做一做这道题，但是反反复复想了几次，没做出来。

2. 2023 年秋季润去了某个大专读高四，2024 年 3 月回去参加学考的时候在考场上没事干，想了想这道题，然后就开窍了。

**得出结论：题目想多了会脑癖，要放置（doge）**

------------

## 1.构造思路：

AC 完之后，翻了一下题解区，发现自己的思路和大家的都不相同，并且 [@olegekei](https://www.luogu.com.cn/user/593613) 还提到：（以下这段节选自这位大佬的题解）

“因为异或和相等，所以可以先考虑直接让异或和等于$\ 0$，那么容易构造出一个矩阵为$\  \begin{pmatrix} 0 & 1\\ 2 & 3 \end{pmatrix}$

那么相应的$\ 4 \times 4\ $大小的矩阵也容易构造出：$\begin{pmatrix} 0 & 1 & 4 & 5\\2 & 3 & 6 & 7\\8 & 9 & 12 & 13\\10 & 11 & 14 & 15 \end{pmatrix}$

但是很明显如果$\ n \times m\ $略大一点这个子矩阵就会挂掉。”

**但其实，只要我们改变这个$\ 4 \times 4\ $矩阵的构造，我们就可以拓展到所有$\ n \times m\ $的矩阵。**

首先，我们直接考虑所有$\ 2 \times 2\ $的子矩阵的四个元素异或和为$\ 0$，并且我们按二进制位考虑。

由于当且仅当四个数中有$\ 2\ $个$\ 0\ $或$\ 4\ $个$\  0\ $时这一位的异或和为$\ 0$，我们希望所有$\ 2 \times 2\ $的子矩阵中，每一二进制位，都有$\ 2 \ $个$\ 0 \ $和$\ 2 \ $个$\ 1$。

我的构造是这样的：$\begin{pmatrix} 0 & 1 & 2 & 3\\4 & 5 & 6 & 7\\8 & 9 & 10 & 11\\12 & 13 & 14 & 15 \end{pmatrix}$

展开成二进制形式：$A = \begin {pmatrix} 00|00 & 00|01 & 00|10 & 00|11\\01|00 & 01|01 & 01|10 & 01|11\\10|00 & 10|01 & 10|10 & 10|11\\11|00 & 11|01 & 11|10 & 11|11 \end{pmatrix}$ 

不难验证假设成立。

然后我们再放大成：$\begin {pmatrix} 00|00|A & 00|01|A & 00|10|A & 00|11|A\\01|00|A & 01|01|A & 01|10|A & 01|11|A\\10|00|A & 10|01|A & 10|10|A & 10|11|A\\11|00|A & 11|01|A & 11|10|A & 11|11|A \end{pmatrix}$，每一个元素是$\ 4 \times 4 \ $的子矩阵，依旧可以发现结论成立。

由于$\ n,m \le 200$，故我们可以构造出一个$\ 256 \times 256\ $的矩阵，然后输出左上角的$\ n \times m\ $的子矩阵即可。


------------

## 2.实现

现在这道题的重难点转换为构造$\ 1 \ $中的$\ 256 \times 256\ $的矩阵了。我们可以考虑分治构造。

将大矩阵划分成$\ 16 \ $个$\ 64 \times 64\ $的子矩阵。
从$\ step = 64\ $开始，先确定好$\ 16\ $个$\ step  \times\ step\ $的子矩阵的左上角的点，然后对每个子矩阵进行类似的操作（这里$\ step\ $要变为原来的$\ \displaystyle \frac{1}{4}$），直到$\ step\ $变为$\ 0\ $为止。



------------

## 3.代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 310;

int a[MAXN][MAXN];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}


void dfs(int i, int j, int step) {
    if (step == 0) return;
    for (int u = 0; u <= 3; u++) {
        for (int v = 0; v <= 3; v++) {
            a[i + u * step][j + v * step] = a[i][j] + step * step * (u * 4 + v);
            dfs(i + u * step, j + v * step, step / 4);
        }
    }
}

int main() {
    dfs(1, 1, 64);
    int u = read();
    while (u--) {
        int n = read(), m = read();
        printf("%d\n", n * m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
    return 0;
}   
```

---

## 作者：I_am_Tangser (赞：0)

## 题目大意

要求你构造一个 $n \times m$ 的矩阵，使得每个 $4\times 4$ 的矩阵左上角 $2 \times 2$ 内的 $4$ 个数和右下角 $2 \times 2$ 内的 $4$ 个数的异或和等于左下角 $2 \times 2$ 内的 $4$ 个数和右上角 $2 \times 2$ 内的 $4$ 个数的异或和并让矩阵内的数的种类尽可能的多。

## 题目思路

首先考虑相等，我们考虑让所有的数都以 $i \times a +j \times b$ 的方式得出，因为这样可以更好的满足两个条件。

那么该怎么定 $a$ 和 $b$ 的值呢？

因为异或是在二进制下按位计算的，所以我们考虑将 $b$ 定为 $1$，然后将 $a$ 定得比最大的 $j$ 还大，发现最小的满足要求的数是 $256$。这样就可以很好地避免 $i$ 和 $j$ 的二进制位相交导致异或值不相等的情况，还可以拉大 $i$ 和 $j$ 对实际值的贡献的差距，使得不同的数最多，最终发现，数最多的情况的数量就是 $n \times m$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		cout<<n*m<<"\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<((i*256)^j)<<" ";
			cout<<"\n";
		}
	}
	return 0;
}
```

---

