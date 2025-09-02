# [JOI Open 2023] 古代机器 2 / Ancient Machine 2

## 题目背景

**译自 [JOI Open 2023](https://contests.ioi-jp.org/open-2023/index.html) T1 「[古代の機械 2](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/ancient2/2023-open-ancient2-statement.pdf) / [Ancient Machine 2](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/ancient2/2023-open-ancient2-statement-en.pdf)」**

**这是一道交互题。**

**在提交本题前请务必仔细阅读以下内容。**

本题只支持 C++ 语言提交（建议使用 C++14，请不要使用 C++14 (GCC9)）。

由于洛谷特殊的交互机制，在提交本题时，请去掉代码中的 ```#include "ancient2.h"``` 语句，并将添加以下语句粘贴到代码最开头：

```cpp
int Query(int m, std::vector<int> a, std::vector<int> b);
```

## 题目描述

Bitaro 和 Bibako 是挖掘和调查 JOI 王国废墟的考古学家。在废墟中，Bitaro 发现了一块古老的石板，Bibako 发现了一台古老的机器。

从研究结果中，Bitaro 发现石板上写有一个长为 $N$ 的字符串 $S$。字符串中每个字符要么是 `0`，要么是 `1`。然而，他还不知道字符串 $S$ 中的每个字符是什么。

另一方面，从研究结果中，Bibako 弄清了如何使用机器。为了使用它，我们需要将石板放在机器上，输入一个整数 $m$ 和两个整数序列 $a,b$，然后做一次查询。这里整数 $m$ 和整数序列 $a,b$ 需满足如下条件：

- 整数 $m$ 在 $1$ 和 $1\ 002$ 之间（包括两端）。
- 序列 $a$ 和 $b$ 的长度均为 $m$。
- 序列 $a,b$ 中的元素都是 $0$ 和 $m-1$ 之间的整数（包括两端）。

如果我们把石板放在机器上，输入一个整数 $m$ 和两个整数序列 $a,b$，然后做一次查询，机器会按如下方式操作并显示一个整数。

1. 机器对其**内存区域**置 $0$。

2. 机器进行如下的 $N$ 次操作。第 $i+1$ 次（$0\le i\le N-1$）操作按如下方式进行。

   令 $x$ 表示机器内存区域中当前的整数。机器读取字符 $S_i$。这里，$S_i$ 是字符串 $S$ 中的第 $i$ 个字符（下标从 $0$ 开始）。

   - 如果 $S_i$ 是 `0`，机器会将内存区域置为 $a_x$。其中 $a_x$ 是序列 $a$ 中第 $x$ 个元素（下标从 $0$ 开始）。
   - 如果 $S_i$ 是 `1`，机器会将内存区域置为 $b_x$。其中 $b_x$ 是序列 $b$ 中第 $x$ 个元素（下标从 $0$ 开始）。

3. 这个机器将展示内存区域中最终置为的整数。

使用这个机器，Bitaro 想要确定石板上写的字符串。然而，因为这个机器十分脆弱，查询的次数不能超过 $1\ 000$。此外，输入机器的整数 $m$ 的最大值需要越小越好。

使用这个机器，写一个程序确定石板上写的字符串。

**【实现细节】**

你需要在程序一开始使用预处理指令 `#include` 引入库 `ancient2.h`。它应当实现如下函数。

- `std::string Solve(int N)`

  这个函数在每组测试数据中仅被调用一次。这个函数需要返回和石板上所写的字符串 $S$ 相同的字符串。

  - 参数 `N` 表示石板上写的字符串 $S$ 的长度 $N$。
  - 这个函数需要返回一个长度为 $N$ 的字符串。如果字符串长度不为 $N$，你的程序会被判为 **Wrong Answer [1]**。
  - 返回值中每个字符要么是 `0`，要么是 `1`。如果该条件不满足，你的程序会被判为 **Wrong Answer [2]**。
  - 返回值应当与石板上写的字符串 $S$ 相同。如果该条件不满足，你的程序会被判为 **Wrong Answer [3]**。

  你的程序可以调用如下函数。

  - `int Query(int m, std::vector<int> a, std::vector<int> b)`

    使用这个函数，你的程序可以做一次查询。

    - 参数 `m` 是输入机器的整数 $m$。
    - 参数 `a`，`b` 是输入机器的两个整数序列 $a,b$。
    - 返回值是当我们把石板放在机器上，并输入上述整数和序列，做一次查询是机器最后显示的整数。
    - 参数 `m` 应当在 $1$ 和 $1\ 002$ 之间（包括两端）。如果该条件不满足，你的程序会被判为 **Wrong Answer [4]**。
    - 序列 `a` 和 `b` 的长度均应等于 $m$。如果该条件不满足，你的程序会被判为 **Wrong Answer [5]**。
    - 序列 `a` 和 `b` 中元素均应在 $0$ 和 $m-1$ 之间（包括两端）。如果该条件不满足，你的程序会被判为 **Wrong Answer [6]**。
    - 函数 `Query` 的调用次数不能超过 $1\ 000$ 次。如果超过 $1\ 000$ 次，你的程序会被判为 **Wrong Answer [7]**。
    
**【注意事项】**

- 你的程序可以实现其它函数供内部使用，或者使用全局变量。
- 你的程序禁止使用标准输入输出。你的程序禁止通过任何方式与其他文件通信。然而，你的程序可以将调试信息输出到标准错误输出。

**【编译和测试运行】**

你可以在「文件」中的「附加文件」下载样例 grader 来测试你的程序。「附加文件」中也包含一份你的程序的样例源程序。

样例交互器是文件 `grader.cpp`。为了测试你的程序，你需要将 `grader.cpp`，`ancient2.cpp` 和 `ancient2.h` 三个文件放在同一文件夹下，并且执行如下命令编译你的程序。你也可以运行 `compile.sh` 来编译你的程序。

```shell
g++ -std=gnu++17 -O2 -o grader grader.cpp ancient2.cpp
```

当编译成功时，会生成一个可执行文件 `grader`。

请注意，实际的交互器和样例不同。样例交互器会作为单进程运行，即它会从标准输入中读取输入数据，并输出结果到标准输出。

## 说明/提示

**【样例解释】**

样例函数调用如下。

| 对 `Solve` 的调用 |   返回值   |           对 `Query` 的调用            |    返回值     |
| :---------------: | :--------: | :------------------------------------: | :-----------: |
|    `Solve(3)`     |            |                              |               |
|                   |   | `Query(4, [3, 3, 2, 2], [2, 2, 1, 0])` |      `3`      |
|          |            |       `Query(2, [0, 1], [1, 0])`       |      `0`      |
|                   |   |          `Query(1, [0], [0])`          | `0`  |
|          |            |    `Query(3, [1, 1, 1], [1, 1, 1])`    |      `1`      |
|                   |  `"110"`   |                                        |   |

假设写在石板上的字符串 $S$ 是 `110`。如果我们把石板放在机器上，输入 $(m,a,b)=(4,[3,3,2,2],[2,2,1,0])$ 并做一次查询，机器将按如下方式操作。

1. 机器将内存区域置为 $0$。
2. 对于第一次操作，因为 $S_0$ 是 `1`，机器会将内存区域置为 $b_0$，即 $2$。
3. 对于第二次操作，因为 $S_1$ 是 `1`，机器会将内存区域置为 $b_2$，即 $1$。
4. 对于第三次操作，因为 $S_2$ 是 `0`，机器会将内存区域置为 $a_1$，即 $3$。
5. 因为最终内存区域被置为的整数是 $3$，所以机器显示 $3$。

注意这组样例输入不满足限制 $N=1\ 000$。在文件中，`sample-02.txt` 满足这个限制。

**【数据范围】**

对于全部数据，满足：

- $N=1\ 000$
- $S$ 是一个长为 $N$ 的字符串
- $S$ 中的每个字符要么是 `0`，要么是 `1`

对于每组数据，实际的交互器 **不是**适应性的。这意味着交互器在开始时答案就已经确定了。

如果你的程序在任意一组数据上被判为任意一种答案错误，在本题你将获得 $0$ 分。

如果你的程序在所有数据上都被判为正确，你的分数由 $M$ 确定，其中 $M$ 是所有数据的 `Query` 函数中参数 `m` 的最大值。然而，如果你的程序没有调用 `Query` 函数并且被判为正确，你的分数由 $M=0$ 确定。

- 如果 $103\le M\le 1\ 002$，你的得分为 $10+\lfloor \frac{(1002-M)^2}{9000}\rfloor$
- 如果 $0\le M\le 102$，你将获得 $100$ 分。

这里 $\lfloor x\rfloor$ 表示不超过 $x$ 的最大整数。

## 样例 #1

### 输入

```
3
110```

### 输出

```
Accepted: 4```

# 题解

## 作者：EXODUS (赞：6)

# Part 1：前言
大概是这三年以来做过的最好的题？

# Part 2：正文

下文中令 $n=N,s=S$。

首先我们考虑一个限制为 $M=1002$ 的做法，对于一个长度为 $n$ 的字符串，我们考虑设计一个算法去按位定位每一位的答案。假设当前我们要确定第 $i$ 位的值，那么考虑构造一种序列，使得前 $i-1$ 位不会影响答案且最后答案只与第 $i$ 位的值有关。也就是说，在到达 $i$ 后，答案始终固定。而对于一个位置 $i$，简单构造可知若 $i=a_i=b_i$，则到达此位置后的结果不影响答案。因此不难想到构造序列 $a=[1,2,\cdots,i-1,i,i,i+1],b=[1,2,\cdots,i-1,i+1,i,i+1]$。期望得分 $10$ 分。

现在我们进军 $M=502$。考虑上面的做法实质上能够让我们在 $M=L+3$ 的长度限制之内确定一段前缀的答案，那么我们现在自然想到能不能也在 $O(L)$ 的限制内确定一段后缀，那么我们知道所有 $j\in[i+1,n]$ 后缀的 $s_j$ 的值，要推出来 $s_i$ 的值，这相当于判定一段后缀是否和某个给定串 $t$ 相等。具体而言，我们试图构造两个数列，若当前机器中的字符为 $i$，则意味着当前的后 $i$ 位和 $t$ 的前 $i$ 位相同，这个可以暴力构造，但对于不同的字符串有不同的形式，故具体实现和构造方式可以参考代码。

这个做法似乎没啥前途，我们不妨跳出这个来想一想。题目的要求实际上是要我们求 $n$ 个 $0/1$ 变量的值，而求未知变量的值我们能够想到的一个做法是构造若干线性无关的方程。而我们还知道存在一组合法解使得 $x_i\in\{0,1\}$，因此我们可以考虑模 $2$ 意义下的方程组。考虑每次询问出下标 $i$ 满足 $i\equiv q\pmod p$ 且 $s_i=1$ 的 $i$ 的个数模 $2$ 后的值。通过手玩发现可以构造两个长度为 $p$ 的环，能改变所在的环的位置只有在环上的第 $q$ 个位置且此时走到的 $s_i$ 为 $1$，实际的构造可以参考代码。

打表发现通过这个方法获得 $1000$ 个独立方程组的 $p$ 的最小值是 $57$，故此时有 $M=114$，求出方程组后高斯消元或其它做法即可。

其实到了这一步以后正解自然的已经出来了。结合前两种做法我们可以把序列长度缩短到 $799$，也就是说我们此时只需要求出 $799$ 个独立的方程组，此时 $p$ 的最小值为 $51$，恰好顶着上界。

于是做完了。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e3+7,M=1e2+2,L=1e2+7;
typedef long long ll;
typedef vector<int> vi;
typedef bitset<N> bit;

int n,m;
vi a,b;
string str;

int Query(int m, std::vector<int> a, std::vector<int> b);

struct Basis{
	vector<pair<int,bit>>S;
	bool ins(bit cur){
		for(auto &[ft,bt]:S)if(cur.test(ft))cur^=bt;
		if(cur.any())return S.eb(cur._Find_first(),cur),1;
		else return 0;
	}
	int size(){
		return S.size();
	}
};

vector<tuple<int,int,bit>>buc[L],qmd;
vector<pair<int,bit>>qft,qbk;

vector<bit>mar;

string Solve(int _n){
	n=_n;
	auto getmd=[&](){
		bit sit;
		rep(x,1,M>>1)rep(r,0,x-1){
			rep(i,0,n-1)sit.set(i,i%x==r);
			buc[2*x].eb(x,r,sit);
		}
	};
	auto getft=[&](){
		bit sit;
		rep(i,0,M-3){
			rep(j,0,n-1)sit.set(j,j==i);
			buc[i+3].eb(-1,i,sit);
		}
	};
	auto getbk=[&](){
		bit sit;
		rep(i,0,M-2){
			rep(j,0,n-1)sit.set(j,j==(n-1-i));
			buc[i+2].eb(-2,i,sit);
		}
	};
	auto merge=[&](){
		Basis tmp;
		rep(i,1,M)for(auto &[x,r,s]:buc[i]){
			if(tmp.size()==n)break;
			if(tmp.ins(s)){
				// Debug("%d %d ",x,r);
				// for(int j=0;j<n;j++)Debug("%d",s.test(j));
				// Debug("\n");
				if(x==-1)qft.eb(r,s);
				else if(x==-2)qbk.eb(r,s);
				else qmd.eb(x,r,s);
			}
		}
	};
	getft(),getmd(),getbk(),merge();
	
	
	auto qryft=[&](){
		auto loop=[&](int i){a[i]=i,b[i]=i;};
		for(auto &[p,s]:qft){
			m=p+3;
			a.resize(m),b.resize(m);
			rep(j,0,p-1)a[j]=b[j]=j+1;
			a[p]=p+1,b[p]=p+2;loop(p+1),loop(p+2);
			auto cur=s;cur.set(n,Query(m,a,b)==p+2);
			mar.eb(cur);
		}
	};
	auto qrybk=[&](){
		vi res;
		for(auto &[p,s]:qbk){
			res.insert(res.begin(),0);
			m=p+2;a.resize(m),b.resize(m);
			auto get=[&](int v,int _p,int i){
				auto cur=vi(res.begin(),res.begin()+i);
				cur.push_back(v);
				per(j,min(_p+1,i+1),1)
					if(vi(cur.end()-j,cur.end())==vi(res.begin(),res.begin()+j))
						return j;
				return 0;
			};
			rep(i,0,p+1)a[i]=get(0,p,i),b[i]=get(1,p,i);
			auto cur=s;cur.set(n,(res[0]=(Query(m,a,b)!=p+1)));
			mar.eb(cur);
		}
	};
	auto qrymd=[&](){
		for(auto &[x,r,s]:qmd){
			m=2*x;a.resize(m),b.resize(m);
			rep(j,0,x-1)a[j]=b[j]=(j+1)%x,a[j+x]=b[j+x]=(j+1)%x+x;
			swap(b[r],b[r+x]);
			auto cur=s;cur.set(n,Query(m,a,b)>=x);
			mar.eb(cur);
		}
	};
	auto solve=[&](){
		rep(i,0,n-1){
			int k=-1;
			rep(j,i,n-1)if(mar[j].test(i)){k=j;break;}
			// Debug("%d\n",k);
			swap(mar[i],mar[k]);
			rep(j,0,n-1)if(j!=i&&mar[j].test(i))mar[j]^=mar[i];
		}
		str.resize(n);
		rep(i,0,n-1)str[i]=mar[i].test(n)+'0';
		// Debug("%s\n",str.c_str());
	};
	
	
	qryft(),qrymd(),qrybk();solve();
	// for(auto bt:mar){for(int j=0;j<n;j++)Debug("%d",bt.test(j));Debug(" %d\n",bt.test(n));}
	
	return str;
}
```
# Part 4：后文
引用一下 vfk 大爷的话。

>一道好题不应该是两道题拼在一起，一道好题会有自己的idea —— 而它应该不加过多包装地突出这个idea。
>
>一道好题应该新颖。真正的好题，应该是能让人脑洞出新的好题的好题。
>
>一道好题应该具有它的选拔性质，具有足够的区分度。应该至少4档部分分，让新手可以拿到分，让高手能够展示自己的实力。

这道题最让人拍案叫绝的是自然是转为求解线性方程组的一步，而以长度相关的代价询问后缀又给了这道题恰到好处的区分度。就这两点而言，无论是从比赛还是练习的角度，这道题也许都称得上是一道好题。


---

## 作者：suzhikz (赞：3)

目前为止做过的最困难的题目，听了讲评后才懂。

题目意思就是你可以构建一个边为 0 或者 1 的自动机，然后告诉你再图上游走完的结果。

然后你就可以一次枚举一个点 $i$，让 $i$ 之前的点的两条边都指向下一个点，然后 $i$ 的两条边分别指向 1001 和 1002，然后 1001 和 1002 就连自环。这样就可以通过返回的点来判断 $i$ 是 0 还是 1。

然后考虑优化下暴力。考虑从后往前求。

比如求最后一位，我们可以 1 的 0 这条边指向自己，下一个指向 2，2 的 0 的边指向 1,1 的边指向自己。这样返回的如果是 1 则代表最后一个是 0，否则是 1。

然后倒数第二位我们可以假设他是 1，然后对后面两个构建下AC自动机，如果返回的值是匹配成功，那么我们就猜测对了，反之我们就猜测错了。

然后我们能过写出前后两百个的值了。

然后我们考虑构建长度为 $a$ 的环，然后枚举下位置 $b$，这样我们可以找到是否有一个位置 $ka+b$ 是 1，但是这玩意还是性质太弱了，考虑构建两个长度为 $a$ 的环，枚举 $b$ ，若环上的位置 $b$ 是 1，就跳到对面那个环，这样我们就知道位置 $ka+b$ 为 1 的个数的奇偶性了。但是直接枚举会有重合的串，用线性基判下，而本质不同的方程组大约有八百多个，用高斯消元即可解出中间的八百个值。

---

## 作者：Lynkcat (赞：2)

vp 的时候只会 98 分。

尝试把每个位置上的数字线性组合得到 $1000$ 个模 $2$ 意义下的线性无关的方程组然后高斯消元求解。

发现我们可以用 $2x$ 的长度来构造两个长度为 $x$ 的环，每次走到 $i\bmod x=y$ 的 $i$ 如果是 $1$ 就跳到对面那个环最后判断在哪个环就可以知道 $i\bmod x=y$ 位置上的数字的异或和。每次暴力枚举 $x,y$ 先判是否线性无关再查询。可以在最长 $114$ 的长度做到 $97$ 分。配合上对前 $100$ 个暴力查询可以得到 $98$ 分。

当 $x\leq 51$ 的时候方程组有 $806$ 个。意味着我们还要再确定 $200$ 个位置才行。而前面我们已经暴力出了 $100$ 个位置，从前面再求 $100$ 个位置好像不太行。转而去求后 $100$ 个位置的值，发现是可行的，我们只要最后从后往前一个个确定，每次就判断用给定的两个序列构建想要匹配的串的 kmp 自动机，判断一下是不是这个后缀完全匹配上了即可。这样就能获得 $100$ 分。

```c++
#include<bits/stdc++.h>
#include "ancient2.h"
// #include "grader.cpp"
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) (int)((x).size())
//#define int ll
//#define N
using namespace std;
namespace 
{
    bitset<1005>f[1005],tmp;
    int n;
    int st[1005],kmp[1005];
    int tot;
    int len;
}
bool insbl(bitset<1005>now)
{
    for (int i=0;i<n;i++)
        if (now[i])
        {
            if (!f[i][i]) return 1;
            now^=f[i];
        }
    return 0;
}
void ins(bitset<1005>now)
{
    for (int i=0;i<n;i++)
        if (now[i])
        {
            if (!f[i][i]){
                f[i]=now;
                return;
            }
            now^=f[i];
        }
}
void qry(int x,int y)
{
    for (int i=0;i<=n;i++) tmp[i]=0;
    for (int i=0;i<n;i++)
        if (i%x==y) tmp[i]=1;
    if (!insbl(tmp)) return;
    ++tot;
    if (tot>1000) return;
    int m=x*2;
    vector<int>a(m,0),b(m,0);
    for (int i=0;i<x;i++)
        a[i]=(i+1)%x;
    for (int i=x;i<x+x;i++)
        a[i]=x+(i+1)%x;
    for (int i=0;i<x;i++)
        b[i]=(i+1)%x;
    for (int i=x;i<x+x;i++)
        b[i]=x+(i+1)%x;
    b[y]=x+(y+1)%x;
    b[x+y]=(y+1)%x;
    int o=Query(m,a,b);
    for (int i=0;i<=n;i++) tmp[i]=0;
    for (int i=0;i<n;i++)
        if (i%x==y) tmp[i]=1;
    if (o<x) tmp[n]=0;
    else tmp[n]=1;
    ins(tmp);
}
std::string Solve(int N)
{
    n=N;tot=0;
    for (int i=0;i<100&&i<n;i++)
    {
        int m=i+3;
        vector<int>a(m,0),b(m,0);
        for (int j=0;j<m;j++)
            a[j]=b[j]=(j+1)%m;
        a[m-1]=m-1,b[m-1]=m-1;
        a[m-2]=m-2,b[m-2]=m-2;
        b[i]=i+2,a[i]=i+1;
        int o=Query(m,a,b);
        if (o==m-2)
        {
            f[i][i]=1;
            f[i][n]=0;
        } else f[i][i]=1,f[i][n]=1;
        tot++;
    }
    for (int i=n-1;i>=n-100&&i>=100;i--)
    {
        f[i][i]=1;
        f[i][n]=0;
        len=0;
        for (int j=i;j<n;j++)
            st[++len]=f[j][n];
        st[len+1]=-1;
        vector<int>a(len+1,0),b(len+1,0);
        if (st[1]==1) b[0]=1;
        else a[0]=1;
        for (int j=1,k=0;j<=len;j++)
        {
            while (k&&st[k+1]!=st[j]) k=kmp[k];
            if (j!=1&&st[k+1]==st[j]) k++;
            kmp[j]=k;
            if (st[j+1]==0) a[j]=j+1;
            else a[j]=a[kmp[j]];
            if (st[j+1]==1) b[j]=j+1;
            else b[j]=b[kmp[j]];
        }
        int o=Query(len+1,a,b);
        if (o!=len) f[i][n]=1;
        tot++;
    }
    for (int i=2;i<=51;i++)
    {
        for (int j=0;j<i;j++)
        {
            qry(i,j);
        }
    }
    for (int i=n-1;i>=0;i--)
        for (int j=0;j<i;j++)
            if (f[j][i]) f[j]^=f[i];
    string ans="";
    for (int i=0;i<n;i++)
        ans+=char('0'+f[i][n]);
    return ans;
}
```

---

