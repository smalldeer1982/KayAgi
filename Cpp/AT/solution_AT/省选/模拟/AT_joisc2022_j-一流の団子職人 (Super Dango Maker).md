# 一流の団子職人 (Super Dango Maker)

## 题目描述

# [JOISC2022] 一流团子师傅

## 题目背景

JOISC2022 D4T1

**特别提醒，由于洛谷交互机制的特殊性，你不能在程序中引用 `dango3.h`，而需要把 `dango3.h` 中的内容加入文件的开头。即，在程序中 `void Solve(int N, int M)` 的前面加入以下几行语句：**

```cpp
#include <vector>

void Solve(int N, int M);

int Query(const std::vector<int> &x);
void Answer(const std::vector<int> &a);
```


JOI 君是一位专业的团子师傅。在 JOI 君的店里，团子的颜色很有讲究。一共有 $N$ 种颜色，编号为 $1,2,\dots,N$。

**一流团子串**是 JOI 君的店里的招牌食品。制作一个一流团子串，需要将 $N$ 个**颜色不同**的团子串在一根竹签上。

对于每一种颜色，JOI 君都制作了 $M$ 个这种颜色的团子。因此，JOI 君总共有了 $NM$ 个团子。这些团子被编号为 $1,2,\dots,NM$。使用这些团子和 $M$ 根竹签，JOI 君希望串出 $M$ 个一流团子串。

为了避免在颜色上犯错误，JOI 君将会启用他的团子检测器。如果 JOI 君输入一些团子的编号，团子检测器会返回使用这些团子能制作的一流团子串的个数的最大值。当然，前提是充分使用竹签。

JOI 君希望能通过使用若干次团子检测器将 $NM$ 个团子分为 $M$ 组。其中，每一组包含 $N$ 个团子，且每种颜色的团子恰有一个。

JOI 君想在使用不超过 $50\,000$ 次团子检测器的前提下完成这件事。

请写一个程序，对于给定的团子的信息，实现 JOI 君使用不超过 $50\,000$ 次团子检测器来完成任务的策略。

---

**【实现细节】**

你的程序需要实现以下函数。

  - `void Solve(int N, int M)`。  
    对于每组测试数据，该函数会被调用恰好一次。
      - 参数 $\texttt N$ 是团子的颜色数 $N$。
      - 参数 $\texttt M$ 是 JOI 君想制作的一流团子串的个数 $M$。

你的程序可以调用以下函数。

  - `int Query(const std::vector<int> &x)`。  
    你的程序可以通过调用这个函数来使用团子检测器。
      - 参数 `x` 是输入给团子检测器的团子的编号列表。
      - 该函数返回使用 `x` 中的团子能制作的一流团子串的最大值。
      - `x` 中的每个元素都应当是 $[1,NM]$ 中的整数。否则你的程序会被判定为 **Wrong Answer [1]**。
      - `x` 中的元素应当互不相同。否则你的程序会被判定为 **Wrong Answer [2]**。
      - 你的程序不得调用该函数超过 $50\,000$ 次。否则你的程序会被判定为 **Wrong Answer [3]**。

  - `void Answer(const std::vector<int> &a)`。  
    你的程序可以通过调用这个程序来报告分组方案。
      - 参数 `a` 是你分出的一组团子的编号列表。
      - `a` 的长度应当为 $N$。否则你的程序会被判定为 **Wrong Answer [4]**。
      - `a` 中的每个元素都应当是 $[1,NM]$ 中的整数。否则你的程序会被判定为 **Wrong Answer [5]**。
      - 在整个过程中，同一个团子不能出现在参数中多于一次。否则你的程序会被判定为 **Wrong Answer [6]**。
      - 如果用 `a` 中的团子并不能制作一个一流团子串，你的程序会被判定为 **Wrong Answer [7]**。
      - 该函数应当被调用恰好 $M$ 次。否则你的程序会被判定为 **Wrong Answer [8]**。

## 说明/提示

- 你的程序可以实现其他函数以供内部使用，或者使用全局变量。
  - 你的程序不得使用标准输入输出流，也不得以任何方式访问任何文件。然而，你可以输出调试信息到标准错误流。
  
**【编译与测试运行】**
  
你可以从「附加文件」中下载样例评分器来测试你的程序。「附加文件」中也提供了你应当提交的程序的一个样例。

样例评分器即 `grader.cpp`。为了测试你的程序，请将 `grader.cpp,dango3.cpp` 放置在同一个目录下，并执行如下命令来编译你的程序。

`g++ -std=gnu++17 -O2 -o grader grader.cpp dango3.cpp`

若编译成功，将会生成一个可执行文件 `grader`。

请注意，实际使用的评分器与下发的样例评分器不同。样例评分器仅会有单个进程，从标准输入中读取输入数据并将结果输出到标准输出。
  

**【样例交互】**

这里是样例评分器的一组样例输入和对应的交互过程。

```plain
3 2
3 3 1 2 1 2
```

|调用|调用|返回值|
|:-|:-|:-|
|$\texttt{Solve(3, 2)}$|||
||$\texttt{Query([])}$|$\texttt 0$|
||$\texttt{Query([4, 2, 1, 3])}$|$\texttt 1$|
||$\texttt{Query([3, 4, 5])}$|$\texttt 0$|
||$\texttt{Query([2, 6, 5])}$|$\texttt 1$|
||$\texttt{Query([6, 5, 4, 3, 2, 1])}$|$\texttt 2$|
||$\texttt{Answer([1, 6, 5])}$||
||$\texttt{Answer([2, 3, 4])}$||

注意，这组样例**不满足任意子任务的限制**。

从「附加文件」中可以下载到 $\texttt{sample-02.txt}$，其满足子任务 $1$ 的限制。


对于所有测试数据，满足：

- $1 \le C_i \le N$ $(1 \le i \le NM)$。
- 对于每个 $j$ $(1 \le j \le N)$，恰有 $M$ 个 $i$ $(1 \le i \le NM)$ 满足 $C_i = j$。  
- $N,M$ 是正整数。
- $C_i$ $(1 \le i \le NM)$ 是一个 $[1,N]$ 内的整数。

详细子任务附加限制及分值如下表所示：

|子任务编号|附加限制|分值|
|:-:|:-:|:-:|
|$1$|$N=M=4$|$2$|
|$2$|$N=100$，$M=10$|$5$|
|$3$|$N=200$，$M=25$|$15$|
|$4$|$N=400$，$M=25$|$78$|

# 题解

## 作者：Augen_stern (赞：0)

## Part 1: 分析求解

中文题面可以看 [UOJ](https://uoj.ac/problem/731)，这里就不过多赘述。

我们可以先考虑一种暴力：

每次从左往右扫描整个团子集合，插入进询问集合，直到询问出此时你的询问集合中包含了一串团子（即每种颜色都至少有一个）；

接着，再对这个询问集合，尝试删掉每一个团子，看能否包含一串完整的团子，若删掉后无影响，则直接删了，否则，它就是在这个集合中那一串团子中，是必要的，可以作为待会儿输出的元素。

然后重复操作，就把整个团子集合给拆开了。

可惜这个暴力效率较低，考虑优化：

我们可以二分出包含一串团子的集合的左端点和右端点，然后再进行上述操作。但这样会被特殊数据卡，所以直接 ```random_shuffle``` 一下就可以了，因为考虑所有颜色随机分布在数轴上，包含所有颜色的期望长度就是颜色种数，所以这样在随机数据下很快，而在数据中询问次数差不多就 $40000$ 出头而已。

## Part 2: CODE

```cpp
//#pragma GCC optimize(3)
#include<iostream>
#include<climits>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<vector>
#include "dango3.h"
//#include<random>
//#include<chrono>
//#define int long long
//#define double long double
using namespace std;
const long long INF=LLONG_MAX/2ll;
const long long mod=998244353;
//const long long mod=1000000007;
const double Pai=acos(-1);
const double eps=1e-8;
vector<int> v,ex;
int n,m,cnt=0;
int vst[1000005],be[1000005],vis[1000005],b[1000005];
int mp[405][30];
bool check(int l,int r) {
	for(int i=l;i<=r;i++) v.push_back(b[i]);
	int res=Query(v);v.clear();
	return res>=1;
}
bool del(int x,int l,int r) {
	for(int i=l;i<=r;i++) if(i!=x&&!vst[i]) v.push_back(b[i]);
	int res=Query(v);v.clear();
	return res>=1;
}
void solve() {
	b[0]=0;
	for(int i=1;i<=n*m;i++) {
		if(!vis[be[i]]) b[++b[0]]=be[i];
	}
	int l=1,r=b[0],L=0,R=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(1,mid)) r=mid-1,R=mid;
		else l=mid+1;
	}
	l=1,r=R,L=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid,R)) l=mid+1,L=mid;
		else r=mid-1;
	}
	for(int i=L;i<=R;i++) if(del(i,L,R)) vst[i]=1;
	for(int i=L;i<=R;i++) if(!vst[i]) ex.push_back(b[i]),vis[b[i]]=1;
	for(int i=1;i<=b[0];i++) vst[i]=0;
	Answer(ex);ex.clear();
	random_shuffle(be+1,be+n*m+1);
}
void Solve(int nn,int mm) {
	n=nn,m=mm;
	for(int i=1;i<=n*m;i++) be[i]=i;
	random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);
	random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);
	for(int i=1;i<m;i++) solve();
	for(int i=1;i<=n*m;i++) if(!vis[be[i]]) ex.push_back(be[i]);
	Answer(ex);ex.clear();
}
```


---

## 作者：ningago (赞：0)

## 「JOISC 2022 Day4」一流の団子職人

题意简述：

交互题。

团子的颜色有 $n$ 种，每种颜色恰好 $m$ 个团子。

称一些团子可以串成一串，当且仅当个数为 $n$，且颜色互不相同。

已知交互库有符合要求的 $n\cdot m$ 个团子，但你不知道团子的颜色。

可以进行的操作：给交互库传入一个编号集合，交互库会告诉你用集合内的团子最多可以串几串。

请回答给交互库 $m$ 个长度为 $n$ 的编号集合，满足每个集合内的团子可以串成一串。

$n\leq 400,m\leq 25$，最多询问次数为 $5\times 10^4$ 次。

---

首先将回答的集合编号为 $1\sim m$。

划分策略为：将 $1\sim n\cdot m$ 号团子依次插入集合，从后往前寻找第一个没有这种颜色的集合并将其插入进去。

问题变成多次询问，寻找编号最大的没有 $a_i$ 颜色的集合并插入。

对于一个询问，设答案集合编号为 $t_0$，当前枚举的集合为 $t$。

考虑对所有未确定的团子（除去 $i$）与已确定的所属集合编号 $\leq t$ 的团子，构成的集合进行询问。

若 $t<t_0$，则答案不会被 $a_i$ 颜色所影响，且有可能多出来未确定的团子串成一串，故询问的答案 $\geq t$。

若 $t\geq t_0$，答案会被 $a_i$ 所影响，使得有一串只有 $n-1$ 种颜色。且不会多出团子。故询问的答案为 $t-1$。

---

对 $t$ 进行二分答案即可。

询问复杂度 $n\times m\times \log m$。

（什么，交互题还需要考虑时间复杂度？）

---

