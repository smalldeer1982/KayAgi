# [COCI 2021/2022 #2] Hiperkocka

## 题目描述

给定一个 $n$ 维的超正方体。

将该超正方体抽象为一个含 $2^n$ 个结点的图，结点分别用序号 $0,1,\cdots,2^n-1$ 表示。两个结点 $x,y$ 联通，当且仅当 $x \oplus y$ 为 $2$ 的整数幂。

现需将若干棵含有 $n$ 条边的树 $T$ 放置于该超正方体中。结点分别用序号 $0,1,\cdots,n$ 表示。给定每棵树的 $n$ 条边所连接的点的序号，则每一棵树需满足下列条件：

- 每个树上的结点都与超正方体的其中一个结点一一对应
- 每个结点互不相同
- 每一棵树的每一条边所连接的两个结点在超正方体中所对应的两个结点在超正方体中有边相连（即对应的两个结点的异或值为 $2$ 的整数幂）
- 每两棵树的边集在超正方体中所对应的边集不交，即超正方体中的每条边最多包含于一棵树中

请给定一种放置方案，使得放在超正方体中的每一棵树都符合题意。

## 说明/提示

**【样例 3 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/58a0p43i.png)

**【数据规模与约定】**

对于 $100\%$ 的数据，$1 \le n \le 16$，$0 \le x,y \le n$，$x \neq y$。

**【提示与说明】**

如果程序正确地放置了 $k$ 棵树，则每个测试点的得分为 $f(k) \cdot 110$，其中：

$$f(k)=\begin{cases}
\dfrac{0.7k}{2^{n-1}} & (k \lt 2^{n-1}) \cr
1 & (k=2^{n-1}) \cr
\end{cases}$$

若放置方式错误，则该测试点得分为 $0$。可以证明，总存在一种方式可以放置 $2^{n-1}$ 棵树。

因评分方式特殊，本题启用自行编写的 [Special Judge](https://www.luogu.com.cn/discuss/738608)，欢迎大家 hack。

**题目译自 [COCI 2021-2022](https://hsin.hr/coci/) [CONTEST #2](https://hsin.hr/coci/contest2_tasks.pdf) _Task 3 Hiperkocka_。**

**本题在 COCI 原题中满分 $110$，但由于为了计算方便，将满分修改为 $26 \times 5=130$。**

## 样例 #1

### 输入

```
1
0 1```

### 输出

```
1
0 1```

## 样例 #2

### 输入

```
2
0 1
1 2```

### 输出

```
2
0 1 3
0 2 3```

## 样例 #3

### 输入

```
3
0 1
0 2
0 3```

### 输出

```
4
0 1 2 4
3 1 2 7
5 1 4 7
6 2 4 7```

# 题解

## 作者：Tsawke (赞：2)

# COCI2021-2022 Contest1 T3题解

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=COCI-2021-2022-Contest2)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## [原题面链接](https://hsin.hr/coci/contest2_tasks.pdf)

## [Luogu题面](https://www.luogu.com.cn/problem/list?keyword=COCI2021-2022%232&page=1)

## T3 Hiperkocka

### 题意

(这道题定义了一个 n-dimensional hipercube，但是实际上和这东西没什么关系)

存在一个 $ 2^n (n \le 16) $ 个节点的图，其中两个节点 $ x, y $ 连通，当且仅当满足 $ x \oplus y = 2^k \quad k \in \mathbb{N} $。

给定若干棵有 $ n + 1 $ 个节点 $ n $ 条边的树，节点用 $ 0, 1, 2, \cdots, n $ 表示，要求将其放置在图中并对于每棵树都满足如下条件：

* 每棵树上每个节点都与图上节点一一对应。
* 每棵树上的每个节点对应的图上节点互不相同。
* 对于每棵树的边连结的两个节点，对应到图上之后，在图上两个节点仍然是联通的（即对应在图上两个节点的编号按位异或后的值为 $ 2 $ 的整数次幂）。
* 图上的每条边只能对应一个树上的边。

需要你给定一种放置方案，使放置的树尽可能多。

采用 SPJ，可以证明最多能放 $ 2^{n - 1} $ 棵树，故采用如下方式计算得分：

若放置不合法则获得 $ 0 \texttt{pts} $，否则若正确放置了 $ k $ 棵树，得分为 $ f(k) \times 110 \texttt{pts} $，其中：
$$
dp(l, r, k) = \left\{
	\begin{array}{ll}
	1 &\quad k = 2^{n - 1} \\
	\dfrac{0.7k}{2^{n - 1}} &\quad k \lt 2^{n - 1}
	\end{array}
\right.
$$


### Solution

本题的难度基本都在思维和找规律上，代码实现很简单，也并不需要用到任何高级算法和数据结构。

首先我们观察题目里一个很奇怪的条件，$ x \oplus y = 2^k \quad k \in \mathbb{N} $，我们思考对于 $ 2^k $ 的二进制表达，显然有且仅有一个 $ 1 $，而其他位置均为 $ 0 $。我们在考虑运算的性质，异或运算得到 $ 1 $ 的情况则需要两个数这一位置上不同。那么由此我们便不难发现，满足要求的 $ x, y $ 在二进制上必须有且仅有一位不同。

通过这个性质我们可以进行一些大胆猜想：

假设我们只需要放置一棵树，那么可以考虑采用如下方案：

任意选择一个树上的节点作为根，并对应到图上的任意节点，这里我们考虑令树上的 $ 0 $ 节点映射到图上的 $ 0 $ 节点，记作 $ 0 \longrightarrow 0 $。

对于树上剩余的点，我们考虑对其进行 DFS，按照其 DFS 序为其分配映射到图上的节点。

为了保证我们映射的节点不会重复，这里我们按照如下方案选点，对于 DFS 序等于 $ \xi $ 的点，我们考虑使其父节点映射的图上节点对应的第 $ \xi $ 位进行取反，可以通过对该位进行异或 $ 1 $ 来实现。如果令父亲节点映射到图上的节点为 $ \epsilon $ 则可以记作：$ \xi \longrightarrow \epsilon \oplus (1 \times 2^{\xi - 1}) $，或写成在搜索过程中写成 `` dfs(son, cur ^ (1 << (cur++))) ``。

现在我们就需要扩展到更多的树，注意题目有个要求即每条边只能用一次，那么就需要注意扩展的时候不能使用两次相同图上的父子关系（包括父子之间调换），这里我们可以尝试从一些较小的数找规律。

首先考虑若父亲为 $ \epsilon $，其儿子为 $ \xi $，则将父子关系记作 $ \epsilon \rightarrow \xi $。

下面我们先找一种特殊情况，如 $ n = 3 $，树为一条 $ 0 \rightarrow 1 \rightarrow 2 \rightarrow 3 $ 的链时，考虑每一种 $ 0 \longrightarrow i \quad i \in \left[ 0, 2^n - 1 \right] $（注意此时的 $ \longrightarrow $ 为长箭头，指的是树与图之间的映射关系，而非父子关系，后文中也以此表示），会有如下可能性：

Tips：这里我们只考虑枚举以树上根节点为 $ 0 $ 映射到图上的任意节点，而不考虑树上的其他根节点的正确性很显然，对于任意一个节点作为根最终形成的结果应该是不变的，可以感性理解一下。
$$
\begin{aligned}
i = 0: (000)_2 \rightarrow (001)_2 \rightarrow (011)_2 \rightarrow (111)_2 \\
i = 1: (001)_2 \rightarrow (000)_2 \rightarrow (010)_2 \rightarrow (110)_2 \\
i = 2: (010)_2 \rightarrow (011)_2 \rightarrow (001)_2 \rightarrow (101)_2 \\
i = 3: (011)_2 \rightarrow (010)_2 \rightarrow (000)_2 \rightarrow (100)_2 \\
i = 4: (100)_2 \rightarrow (101)_2 \rightarrow (111)_2 \rightarrow (011)_2 \\
i = 5: (101)_2 \rightarrow (100)_2 \rightarrow (110)_2 \rightarrow (010)_2 \\
i = 6: (110)_2 \rightarrow (111)_2 \rightarrow (101)_2 \rightarrow (001)_2 \\
i = 7: (111)_2 \rightarrow (110)_2 \rightarrow (100)_2 \rightarrow (000)_2 
\end{aligned}
$$
然后我们寻找不合法的解，如果我们贪心地优先保留 $ i $ 更小的解，那么下面标注的这些部分显然是重复的不合法的：
$$
\begin{aligned}
i = 0: (000)_2 \rightarrow (001)_2 \rightarrow (011)_2 \rightarrow (111)_2 \\
i = 1: \underline{(001)_2 \rightarrow (000)_2} \rightarrow (010)_2 \rightarrow (110)_2 \\
i = 2: (010)_2 \rightarrow \underline{(011)_2 \rightarrow (001)_2} \rightarrow (101)_2 \\
i = 3: (011)_2 \rightarrow (010)_2 \rightarrow (000)_2 \rightarrow (100)_2 \\
i = 4: (100)_2 \rightarrow (101)_2 \rightarrow \underline{(111)_2 \rightarrow (011)_2} \\
i = 5: (101)_2 \rightarrow (100)_2 \rightarrow (110)_2 \rightarrow (010)_2 \\
i = 6: (110)_2 \rightarrow (111)_2 \rightarrow (101)_2 \rightarrow (001)_2 \\
i = 7: \underline{(111)_2 \rightarrow (110)_2} \rightarrow (100)_2 \rightarrow (000)_2 
\end{aligned}
$$
观察剩余的合法的解：
$$
\begin{aligned}
i = 0: (000)_2 \rightarrow (001)_2 \rightarrow (011)_2 \rightarrow (111)_2 \\
i = 3: (011)_2 \rightarrow (010)_2 \rightarrow (000)_2 \rightarrow (100)_2 \\
i = 5: (101)_2 \rightarrow (100)_2 \rightarrow (110)_2 \rightarrow (010)_2 \\
i = 6: (110)_2 \rightarrow (111)_2 \rightarrow (101)_2 \rightarrow (001)_2 \\
\end{aligned}
$$


不难发现其符合一个规律，即二进制中 $ 1 $ 的数量为偶数个（如果仍未发现可以考虑 $ n = 4 $ 的情况）。

经过验证，显然当树的形态不为一条链的时候该结论仍然成立。

下面我们需要思考如何计算这些扩展出来的节点，显然我们可以每次都进行一次 $ \texttt{DFS} $，时间复杂度大约是 $ O(n2^n) $，显然可以接受，于是这题就切了...不过我们可以考虑接着找规律（虽然并不能优化复杂度）。

观察刚才得到的合法解中的每一列：
$$
\begin{aligned}
i = 0: (000)_2 \rightarrow (001)_2 \rightarrow (011)_2 \rightarrow (111)_2 \\
i = 3: (011)_2 \rightarrow (010)_2 \rightarrow (000)_2 \rightarrow (100)_2 \\
i = 5: (101)_2 \rightarrow (100)_2 \rightarrow (110)_2 \rightarrow (010)_2 \\
i = 6: (110)_2 \rightarrow (111)_2 \rightarrow (101)_2 \rightarrow (001)_2 \\
\end{aligned}
$$
不难发现第一个可能的规律，将 $ i = 0 $ 的情况中每一个数的第 $ k $ 位保留不变并将其他位全部取反，枚举 $ k $ 便可以得到剩余的情况。但是这真的正确吗？我们可以考虑随意构造一个非链状的树，简单验证后就会发现这个规律假掉了（这里就不写验证过程了，很简单）。

于是我们继续尝试构造规律，可以发现若对于每一个符合要求的 $ i (i \neq 0) $ 与 $ i = 0 $ 时的每一个数进行异或运算后，得到的结果便是一组新的解，并且经过验证这个规律在其他树的形态仍然是正确的。

至此我们便可以考虑用 dp 思想，$ O(2^n) $ 预处理出所有合法的 $ i $，然后按照我们的算法进行计算，时间复杂度大概是 $ O(n2^n) $，可以接受。

同时建议对于这种规律题如果有时间，打个对拍验证一下规律的正确性。


### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;

template<typename T = int>
inline T read(void);

vector < int > vert[110000];
int N;
int base[110000];
bool vis[110000];
int cur(0);
void dfs(int p, int mapp){
    base[p] = mapp;
    vis[p] = true;
    for(auto i : vert[p]){
        if(!vis[i]){
            vis[i] = true;
            dfs(i, mapp ^ (1 << (cur++)));
        }
    }
}
int dp[110000];
vector < int > legal;
void Init(int N){
    int lim = 1 << N;
    dp[0] = 0;
    for(int i = 1; i <= lim; ++i){
        dp[i] = dp[i >> 1] + (i & 1);
        if(!(dp[i] & 1))legal.push_back(i);
    }
}
int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        int f = read(), t = read();
        vert[f].push_back(t);
        vert[t].push_back(f);
    }
    dfs(0, 0);
    Init(N);
    printf("%d\n", (int)legal.size() + 1);
    for(int i = 0; i <= N; ++i)printf("%d%c", base[i], i == N ? '\n' : ' ');
    for(auto i : legal)
        for(int j = 0; j <= N; ++j)
            printf("%d%c", base[j] ^ i, j == N ? '\n' : ' ');
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

2022_09_05 完成 T1 - T3 及 T4 一部分

2022_09_06 初稿


---

## 作者：Wait_Add (赞：0)

## 先分析超正方体由什么边组成：
这是一个二维正方体（0123）。  
![](https://cdn.luogu.com.cn/upload/image_hosting/08sukfac.png) 

将正方体上每个点加 $2^2=4$ 便得到了它的复制正方体（4567）。  
再将二维正方体（0123）与二维正方体（4567）对应边连线就得到了三维正方体。  
![](https://cdn.luogu.com.cn/upload/image_hosting/wnookbol.png) 
***
## 做法：
以样例三举例

```
3
0 1
0 2
0 3
```
假设已经用树 $abc$ 装满了二维正方体，现需要在树的 $a$ 点上加一条边 $a\longrightarrow d$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/kk5hn0yg.png) 

复制正方体（0123）得到正方体（4567）**（设为步骤 1）**。  
![](https://cdn.luogu.com.cn/upload/image_hosting/f2yrszw8.png) 

如果此时直接将正方体（0123）与复制正方体（4567）对应点相连，新建的边重合，方案不合法。  
考虑将正方体（4567）相邻的/**异或等于 1** 的两点交换。**（设为步骤 2）**。  
如：4 和 5 交换，6 和 7 交换。  
![](https://cdn.luogu.com.cn/upload/image_hosting/7zrac97j.png) 

再从每棵树的 $a$ 点新建一条边，连向的点为此树的 $d$ 点，**（设为步骤 3）**。  
![](https://cdn.luogu.com.cn/upload/image_hosting/r5ilam2y.png) 

正好覆盖三维正方体上每一条边，方案合法。
***
## 正确性证明：
设性质 $F$：
> $x$ 为高维正方体中某点的编号。  
> 若 $x$ 能与某棵树的 $a$ 点对应，则 $x\operatorname{xor}1$ 不能与任何树的 $a$ 点对应。  
> 反之，则 $x\operatorname{xor}1$ 与某棵树的 $a$ 点对应。

在一维正方体中，显然满足性质 $F$，
考虑每个步骤对性质影响：
 * **（步骤 1）**，将正方体复制为两个正方体，任然满足性质 $F$。
 * **（步骤 2）**，将复制正方体中**异或等于** 1 的点交换，任然满足性质 $F$。
 * **（步骤 3）**，从每棵树的 $a$ 点新建一条边连向 $b$ 点，由于每棵树的 $a$ 满足性质 $F$ ，所以每棵树的 $b$ 也满足性质 $F$。

 所以图始终满足性质 $F$。  
 于是正方体中若 $x$ 能与某棵树的 $a$ 点对应，  
 则 $x\operatorname{xor}1$ 不能与任何树的 $a$ 点对应，  
 则**步骤 3** 中 $x$ 连向的 $y$ 是 $x\operatorname{xor}1$ 的复制，也不能与任何树的 $a$ 点对应。   
 能实现新建的边不重合，方案合法。
 ***
 ## code
 ```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int n,k,bas=1;
//bas为当前正方体的节点个数
vector<int>sid[20];
//树的节点编号从0开始
//正方体的节点编号从0开始
//树的编号从1开始
int sec[N][20];//sec[i][j]表示正方体中的i是第几棵树的j节点
int ans[N][20];//ans[k][j]表示第k棵树的j节点对应正方体的编号

void sol(int x,int y){
	
	for(int i=0;i< bas;i++){
		if(bas==1)	break;
		for(int j=0;j<=n;j++)
			if(sec[i][j])
				sec[bas+(i^1)][j]=sec[i][j]+bas/2;
	}
	
	for(int i=0;i< bas;i++)
		if(sec[i][x])	sec[i+bas][y]=sec[i][x];
		else			sec[i][y]=sec[i+bas][x];
	
	bas*=2;
}

void dfs(int u,int fa){
	for(int v:sid[u])
		if(v!=fa)	sol(u,v),dfs(v,u);
}

int main(){
	cin>>n;
	int x,y;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		sid[x].push_back(y);
		sid[y].push_back(x);
	}
	
	sec[0][0]=1;
	dfs(0,-1);
	
	for(int i=0;i<=n;i++)
		for(int j=0;j<=(1<<n)-1;j++)
			ans[sec[j][i]][i]=j;
	
	int k=(1<<(n-1));
	cout<<k<<'\n';
	for(int i=1;i<=k;i++){
		for(int j=0;j<=n;j++)
			cout<<ans[i][j]<<" ";
		cout<<'\n';
	}
	return 0;
}
 ```

---

## 作者：Fish_Clever (赞：0)

  每个点在每个位置取反都能连上新点，这样是 $\frac{2^k \times k}{2}$，即 $k \times 2^{k-1}$ 条边，最多能有 $2^{k-1}$ 棵树(树的边不重但点肯定要重合一些)。
  
  所以，若能放满，还需要管什么输入的必联边。。。(也就是说，我一开始没有考虑这点，得到了一个结论，接下来会将其修改以适应本题)
  
  把题中所给的 $n=3$ 的那 $3$ 个根拆一下(左边是根，右边是叶)：
  
```
  000 : __* _*_ *__
  011 : __* _*_ *__
  101 : __* _*_ *__
  110 : __* _*_ *__

  其中 * 表示变化, _ 表示不变.
```

  由于任意两根之间至少差了 $2$ 次变化，所以“根—叶”这条边不会重复。

  很好，试试推广到 $n=4$，保证每个新点与之前所有点的差都至少为 $2$：
```
  0000
  0011
  0101
  0110
  1001
  1010
  1100
  1111
```

  发现，后 $4$ 个就是前 $4$ 个的对称+取反，正确性证明：首先前 $4$ 个和后 $4$ 个内部满足差大于等于 $2$ 的性质，因为这是 $n=3$ 的情况；再因为取反，首位肯定不同，仅需保证后面有个不同的就行。

  还没证明完，但别急，再看看 $n=5$ 的情况，若只是单纯的对称+取反就不行了，因为 $01111 \to 10000$，和第一个只有一个位置不同。那还是尝试枚举第一个可行的值，发现：

```
  00000 10001
  00011 10010
  00101 10100
  00110 10111
  01001 11000
  01010 11011
  01100 11101
  01111 11110
```

  这个构造可视为一一对应+把首位和末位取反，首位取反必然导致一个差异了，末位取反可以保证两个数的对应下，恰有两个差异，但和别的呢？

  新构造的第 $1 \sim 4$ 个和原本的 $5 \sim 8$ 比较，肯定满足差异，因为第二高位也不同。

  反证，假设**新构造的**第 $i$ 个和**原本的**第 $j$ 个没有别的差异，也就是说，**原本的**第 $i$ 个和第 $j$ 个只有末位的差异喽，但根据**数学归纳法**，之前已找到满足的一组，这个基石是不会有问题的。所以反证不成立。

  然后我突然发现题目看错了，每棵树哪几条边相连还是限定好的。。。

  没事，改改还能用。举个例子，比如限定了和 $0$ 位置相连的有 $2$ 个，和 $1$ 位置相连的有 $1$ 个。
  那么，先能有：

```
  000 -- 001
      -- 010
  011 -- 010
      -- 001
  101 -- 100
      -- 111
  110 -- 111
      -- 100
```

  以上构造源于原本的答案生成方式。
  
  然后考虑 $1$ 位置的那些要怎么连，显然是唯一的。

```
  000 -- 001 -- 101
      -- 010
  011 -- 010 -- 110
      -- 001
  101 -- 100 -- 000
      -- 111
  110 -- 111 -- 011
      -- 100
```

  诶，将其抽象一下：
```
  ___  ^ __*  ^ *__
       ^ _*_  
```
  发现，原本是让 $(001,010,100)$ 全部异或根，现在只是去异或别的点。

  证明下，仅需考虑链的情况，因为不是链就会这样(见下图)：

![](https://cdn.luogu.com.cn/upload/image_hosting/4j9evnv6.png)

  若 $x=z$，$y=w$，那么异或下就可得到有颜色的这两段相等，但由于每一段是多少为预先设定好的，互不重复，因此这类情况不会出现($x=w$，$y=z$同理)。

  因此若重合，情况必然是在同一个边的两端，而且是 $x=w$，$y=z$ 的情况(毕竟根不相同嘛)(见下图)：

![](https://cdn.luogu.com.cn/upload/image_hosting/ztiwvu2q.png)

  因此有 $\texttt{a xor 某边 = b}$，但 $a$ 和 $b$ 至少差了 $2$ 个位置的 $1$，因此不可能。

  给个例子解释下(见下图)：

![](https://cdn.luogu.com.cn/upload/image_hosting/qwitmztf.png)

  注意，要 dfs 一下，会出现类似 $(0,2)(2,1)$ 这种数据，而不能直接排序。

```
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
#include<map>
#define ls p<<1
#define rs p<<1|1
#define m_p make_pair
#define _for(i,a,b) for(int i=(a);i<(b);i++)
#define _rof(i,a,b) for(int i=(a)-1;i>=(b);i--)
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T1,typename T2>
inline bool cmax(T1& a,T2 b){return a<b?a=b,1:0;}//被更改=true.
template<typename T1,typename T2>
inline bool cmin(T1& a,T2 b){return a>b?a=b,1:0;}//被更改=true.
template<typename T1,typename T2>
inline T1 max(T1 x,T2 y){return x>y? x:y;}//以前面的类型为准.
template<typename T1,typename T2>
inline T1 min(T1 x,T2 y){return x<y? x:y;}//以前面的类型为准.
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
	return s*w;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline void write(int x,char ch){write(x),putchar(ch);}

const int N=16;
int n,a[(1<<N)+10],cnt=1;
int head[N+10],to[N+10<<1],nxt[N+10<<1],tot=0;
inline void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int _xor=1;
int change[N+10];
void dfs(int p,int fa,int cg){//为了得到change数组,表示每个点和root的相对值(自然是相对xor了).
	change[p]=cg;
	for(int i=head[p],y;i;i=nxt[i])
		if((y=to[i])!=fa){
			_xor<<=1;//这东东可不能放dfs的后面.
			dfs(y,p,cg^(_xor>>1));
		}
}
int main(){
	n=read();
	a[1]=0;
	_rep(i,1,n-1){
		int high=(1<<i);
		_rep(j,1,cnt)//生成root们.
			a[cnt+j]=high^a[j]^1;
		cnt<<=1;
	}
//	_rep(i,1,cnt) printf("%d ",a[i]);printf("\n");
	write(1<<n-1,'\n');//2^(n-1)个.

	_rep(i,1,n){
		int x=read(),y=read();
		add(x,y), add(y,x);
	}
	dfs(0,-1,0);
//	_rep(i,0,n) printf("%d ",change[i]);printf("\n");
	
	_rep(i,1,cnt){
		_rep(j,0,n-1)
			write(a[i]^change[j],' ');
		write(a[i]^change[n],'\n');
	}
	return 0;
}
```

---

