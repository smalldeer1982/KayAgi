# Magic Breeding

## 题目描述

Nikita and Sasha play a computer game where you have to breed some magical creatures. Initially, they have $ k $ creatures numbered from $ 1 $ to $ k $ . Creatures have $ n $ different characteristics.

Sasha has a spell that allows to create a new creature from two given creatures. Each of its characteristics will be equal to the maximum of the corresponding characteristics of used creatures. Nikita has a similar spell, but in his spell, each characteristic of the new creature is equal to the minimum of the corresponding characteristics of used creatures. A new creature gets the smallest unused number.

They use their spells and are interested in some characteristics of their new creatures. Help them find out these characteristics.

## 说明/提示

In the first sample, Sasha makes a creature with number $ 3 $ and characteristics $ (2,2) $ . Nikita makes a creature with number $ 4 $ and characteristics $ (1,1) $ . After that they find out the first characteristic for the creature $ 3 $ and the second characteristic for the creature $ 4 $ .

## 样例 #1

### 输入

```
2 2 4
1 2
2 1
1 1 2
2 1 2
3 3 1
3 4 2
```

### 输出

```
2
1
```

## 样例 #2

### 输入

```
5 3 8
1 2 3 4 5
5 1 2 3 4
4 5 1 2 3
1 1 2
1 2 3
2 4 5
3 6 1
3 6 2
3 6 3
3 6 4
3 6 5
```

### 输出

```
5
2
2
3
4
```

# 题解

## 作者：critnos (赞：16)

写题解标记一下好题，顺便给个人类比较容易看懂的题解。。

不妨考虑数 $\{0,1\}$ 的时候怎么做。对于初始的序列，每一列都有 $k$ 个 $\{0,1\}$ 中的数。

那么这 $n$ 列中实际上只有 $2^k$ 个本质不同的列。只需要用 bitset 维护这些列即可。

那么如何把一般的问题转为 $\{0,1\}$ 的问题？对每一列分别离散化，使得值域在 $[1,k]$。然后将这一列中的每个数 $x$ 都拆成 $k$ 个 $\{0,1\}$ 的数，$[1,x]$ 为 $1$，$[x+1,k]$ 为 $0$。

这样取 $\max$ 相当于按位或，取 $\min$ 相当于按位与。

比如

```
1
4
9
```

离散化为

```
1
2
3
```

得到的序列是

```
100
110
111
```

代码虽然短，但是实现有困难。[CF 评测记录](https://codeforces.com/contest/878/submission/173880885)。

---

## 作者：wurzang (赞：8)

这题其实并不算很难理解，看不懂题解都写的是啥，所以就来写篇题解。

考虑值全为 0/1 的时候怎么做，显然对于 $n$ 个不同的位，$k$ 个数字最多有 $\min \{n,2^k\}$ 种不同的取值。

比如输入为
```
001
110
101
```
的时候，有 `011`，`010`，`101` 三个位上的不同取值。

于是我们就只需要知道不同取值时的答案，同一取值的位本质上是一样的，因此我们就不需要考虑位。

$f_{i,S}$ 表示 $k$ 个数字的取值为 $S$ 时，第 $i$ 个生物的答案。

$\max / \min$ 操作就可以直接看成二进制的 或/与 。

值域扩展成 $10^9$ 时可以直接枚举答案 ans，把 $<$ ans 的数字看成是 $0$，$\ge $ ans 的数字看成是 $1$，然后根据 $f_{i}$ 来判断答案是否 $\ge$ ans。

以上过程可以用 `bitset` 来加速，时间复杂度 $\mathcal{O}(\frac{q2^k}{\omega})$

代码很多其他题解都写了，我只是来解释一番。

---

## 作者：AzusaCat (赞：7)

给定 $k$ 个长为 $n$ 的数组，有 $q$ 次操作，分别是新建一个数组，每一个元素为某两个已有数组的 $\max/\min$，或者查询某个数组上某个数是多少。$k\leqslant 12$，$n,q\leqslant 10^5$。

本题最有意思也是最难理解的是如何压缩状态量。首先显然每一个位置上的数是独立的，但是我们又不能直接独立考虑：因为这样你至少需要做 $n$ 次，我们承受不了这个复杂度。我们发现由于一开始只有 $k$ 个数组，那么最后的答案一定在这 $k$ 个数组的元素中间，我们考虑定义一个和这 $k$ 个数具体是什么无关的状态，这样就能起到压缩信息的作用。

我们把视角放到某一位上，这样每一次都生成的是一个元素 $a_i$，定义 $f(i,s)$ 表示对于元素 $i$，**无论 $a_1\sim a_k$ 的值是多少**，是否一定满足 $a_i\geqslant \min_{j\in s}(a_j)$。那么对于 $i\in [1,k]$，显然 $f(i,s)=1$ 当且仅当 $i\in s$。

接下来我们考虑 $\min/\max$ 操作，由于 $\max(a_x,a_y)\geqslant \min_{j\in s}(a_j)$ 等价于 $a_x\geqslant \min_{j\in s}(a_j)\lor a_y\geqslant \min_{j\in s}(a_j)$ ，所以如果是 $\max$ 操作，有 $f(i,s)=f(x,s)\lor f(y,s)$。类似地我们也可以把取 $\min$ 操作和 `and` 操作建立联系。

现在我们考虑询问，我们先给出流程，然后再证明它的正确性：我们把 $a_1\sim a_k$ 从大到小排序，每一次向 $s$ 中加入对应的下标 $i$，如果 $f(x,s)=1$，就输出 $a_i$。

下面来证明这样为什么是对的：

- 首先如果 $f(x,s)=1$ 即无论 $a$ 怎么取都成立，那么对于 $a$ 给定的特殊情况也一定成立，也就是 $ans\geqslant a_i$。
- 如果 $ans>a_i$，也就是说对于我们加入过程的某个前缀 $a_{b_k}\rightarrow a_{b_t}$，假设该前缀对应的集合是 $s'$，则 $f(x,s')=0$，但是在这组 $a$ 的情况下有 $a_x\geqslant \min_{j\in s'}(a_j)=a_t$。  
  我们注意到如果存在一组 $a'$ 使得 $a'_x< \min_{j\in s'}(a'_j)$，那展开 $a'_x$ 的生成过程，一定有一步 $\min$ 操作使得两个元素一个属于 $s'$，另一个不属于 $s'$，之后的操作都只在 $s'$ 的补集中进行，而在当前的 $a$ 下，$s'$ 中的 $a$ 是整个序列最大的一部分，所以这个 $\min$ 操作也会使得 $a_x$ 对应的下标变为 $s'$ 补集中的元素，与条件不符。  
  感性理解就是由于我们是从大到小枚举的，那么这个限制已经是所有限制中最紧的那个，如果最紧的限制满足，则其它的也一定满足。

所以这样一定有 $ans=a_i$。至于实现，我们发现取 $\max/\min$ 可以使用 `bitset` 加速，所以总复杂度 $O\left((k+\dfrac{n}{w})2^k\right)$ （$n,q$ 同阶）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<4096>f[100020];
int a[13][100005],b[100005][13],now;
bool cmp(int x,int y){return a[x][now]==a[y][now]?x>y:a[x][now]>a[y][now];}
int main()
{
    int n,q,k,cnt,op,x,y;
    scanf("%d%d%d",&n,&k,&q);cnt=k;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]),b[j][i]=i;
    for(int i=1;i<=n;i++)now=i,sort(b[i]+1,b[i]+k+1,cmp);
    for(int i=1;i<=k;i++)
        for(int j=0;j<(1<<k);j++)
            if(j&(1<<(i-1)))f[i][j]=1;
    while(q--)
    {
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)cnt++,f[cnt]=f[x]|f[y];
        else if(op==2)cnt++,f[cnt]=f[x]&f[y];
        else
            for(int i=1,t=0;i<=k;i++)
            {
                t|=(1<<(b[y][i]-1));
                if(f[x][t]){printf("%d\n",a[b[y][i]][y]);break;}
            }
    }
    return 0;
}
```



---

## 作者：fsy_juruo (赞：7)

### 简要题意

* 一开始有 $k$ 种生物，每种生物有 $n$ 个属性 $a_{k,1}, a_{k,2}, \cdots, a_{k,n}$。现有以下 $3$ 种操作：
* (1). 给定两个正整数 $x$，$y$。创建一个新生物，此生物的第 $i$ 项属性为 $\max(a_{x,i}, a_{y,i})$。
* (2). 给定两个正整数 $x$，$y$。创建一个新生物，此生物的第 $i$ 项属性为 $\min(a_{x,i}, a_{y,i})$。
* (3). 给定两个正整数 $x$，$y$。输出第 $x$ 个生物的第 $y$ 项属性。
* 新生物的编号即为最小的未使用数字。
* 操作数 $q \leq 10^5$，属性数 $n \leq 10^5$，$k \leq 12$。

### 题解

注意到 $k$ 很小，而且最终的答案只会在这 $k$ 个生物里面，考虑把 $k$ 作为切入点。

令 $f_{i,mask}$ 为 如果选择的生物的二进制压缩为 $mask$，则此新生物中，是否一定会存在一个属性大于等于 $i$ 号生物的对应属性？

**初始化：** 枚举 $mask$，注意到如果 $i$ 号生物被选，则 $f_{i, mask}$ 一定为 $1$，否则不确定，为 $0$。

**操作 1（取 $\max$）：** 注意到三个数 $a, b, c$，当且仅当 $c > a$ 且 $c > b$ 才有 $c > \max(a,b)$，故把 $x$，$y$ 的 $f$ 数组看成一个二进制数，则新生物 $\overline{f_{new,1} \cdots f_{new,n}}$ 对应的二进制数即为 $\overline{f_{x,1} \cdots f_{x,n}} \; \text{and} \; \overline{f_{y,1} \cdots f_{y,n}}$ 

操作 2 推导同理，此处不再赘述。

**操作 3（求答案）：** 先按照那一位原来的从小到大排序，之后考虑每次加进去一个数看看是否一定大于等于这个位置的值（即 $f_{...,...}=1$）。第一个合法的数即为答案。

可以使用 ``std::bitset`` 优化上述过程。注意到不同的 $mask$ 只有 $2^k$ 个，故总时间复杂度为 $\mathcal{O}(\frac{q2^k}{w})$，可以通过本题。

### 代码

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}

const int maxN = 4e5 + 20;
int n, k, q, c[12][maxN], f[12], tot, x, y, z;
std::bitset<4096> F[maxN];

int main() {
	read(n, k, q); tot = k;
    _rep(i, 0, k - 1) {
        _rep(j, 1, n) read(c[i][j]);
    }
    _rep(i, 0, k - 1) {
        _rep(mask, 0, (1 << k) - 1) if(mask & (1 << i)) F[i + 1][mask] = 1;
    }
    while(q--) {
        read(x, y, z); 
        if(x == 1) F[++tot] = F[y] & F[z];
        else if(x == 2) F[++tot] = F[y] | F[z];
        else {
            _rep(i, 0, k - 1) f[i] = i;
            std::sort(f, f + k, [](int i, int j) {
                return c[i][z] < c[j][z];
            });
            int mask = 0;
            _rep(i, 0, k - 1) {
                mask |= (1 << f[i]);
                if(F[y][mask]) {
                    writesp(c[f[i]][z], '\n');
                    break;
                }
            }
        }
    }
	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

[CF878D Magic Breeding](https://www.luogu.com.cn/problem/CF878D)

每个生物都可以写成 $k$ 个初始生物的 $\min / \max$ 表达式，但表达式长度级别为 $\mathcal{O}(q)$，无法接受。

考虑对表达式的形态做出一些规定。我们知道 $\min$ 和 $\max$ 互相有分配律，所以我们总可以将表达式写成 **若干个 $\max$ 表达式的 $\min$**，类似由若干简单合取式构成的析取范式。

我们设集合 $S$ 表示 $\max\limits_{j\in S} a_j$，这样我们可以用若干集合 $S$ 形成的集合 $T = \{S_1, S_2, \cdots,  S_k\}$ 描述一个表达式，即一个生物，其含义为 $\min\limits_{S_i\in T}\left(\max\limits_{j\in S_i} a_j\right)$。

合并 $T_i$ 和 $T_j$ 得到 $T_k$ 时，若外层为 $\min$，则 $T_k = T_i\cup T_j$，若外层为 $\max$，则 $T_k = \{X\cup Y | X\in T_i, Y\in T_j\}$。用 $f_{i, S}$ 表示 $[S\in T_i]$，则取 $\max$ 相当于或卷积，然后将值非零的位置设为 $1$。这样，我们有一个 $q2 ^ kk$ 的做法，但不够快。

注意到若 $X\in T_i$，则将所有 $X$ 的超集加入不影响答案。因此，不妨设初始 $f_{i, S} = [i\in S]$，此时满足对于任意 $S$，若 $f_{i, S} = 1$ 则 $f_{i, S'} = 1$，其中 $S\subseteq S$。我们发现 $f_i$ 和 $f_j$ 本身已经是点值表示，所以它们的点值积（对应位置 AND）即为它们做或卷积后的结果，且同样满足点值表示。

用 `bitset` 维护长为 $2 ^ k$ 的 $01$ 序列的按位与和按位或。将询问离线到每个位置上，最后对每个位置 $p$ 进行 $2 ^ k$ 状压 DP 得到 $f_S = \max\limits_{i \in S} a_{i, p}$，则询问 $(x, p)$ 的答案为 $\min\limits_{S\in T_x} f_S$。时间复杂度 $\mathcal{O}((n + q)2 ^ k)$。[代码](https://codeforces.com/contest/878/submission/180033919)。

利用性质，对于每次询问 $(x, y)$，我们可以按 $a_{i, y}$ 从小到大的顺序枚举 $i$，若已经被枚举过的 $i$ 形成的集合 $S$ 对应的 $f_{x, S}$ 第一次为 $1$，则 $a_{i, y}$ 即为所求。时间复杂度 $\mathcal{O}\left(k 2 ^ k + \dfrac {q2 ^ k} w + kq + nk\log k\right)$。[代码](https://codeforces.com/contest/878/submission/180154810)。

---

## 作者：ZigZagKmp (赞：5)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14396638.html)

~~听说 WC2021 的 T2 和这题解法类似，于是就来做一发。~~

## 题意简述
初始有 $k$ 个生物，编号分别为 $1,2,\ldots,k$ ，每个生物有 $n$ 个属性，第 $i$ 个生物的第 $j$ 个属性为 $a_{i,j}$ 。

现在有 $q$ 次操作，形式如下：

- `1 x y` 表示将第 $x$ 号生物的 $n$ 个属性与第 $y$ 号生物的 $n$ 个属性分别取 $\max$ ，作为一个新生物的 $n$ 个属性
- `2 x y` 表示将第 $x$ 号生物的 $n$ 个属性与第 $y$ 号生物的 $n$ 个属性分别取 $\min$ ，作为一个新生物的 $n$ 个属性
- `3 x y` 表示询问第 $x$ 号生物的第 $y$ 个属性值是多少

新生物的编号依次顺延，即第 $t$ 个 `1/2` 操作得到的新生物编号为 $t+k$ 。

你需要对每一个 3 操作回答询问。

$1\le n,q\le 10^5,1\le k\le 12,1\le a_{i,j}\le 10^9$ 。

## 算法分析

如果直接暴力做复杂度是 $\mathcal O(nq)$ 的，无法接受。

本题 $k$ 很小，是本题的突破点。不难发现对于每一种属性，我们最后的答案一定来自于初始的 $k$ 个生物的该属性的值，因此考虑**枚举答案**。 $\min,\max$ **本身代表一种偏序关系**，与其具体值无关，所有可能的情况共有 $2^k$ 个。这说明 $n$ 种属性中最多有 $2^k$ 个**本质不同的属性**，考虑维护这 $2^k$ 种状态。

我们定义一个状态 $S$ 如下：若 $S$ 的第 $i$ 位为 $1$ ，表示当前状态下 $a_i\ge\ \text{对应的答案}$，否则 $a_i<\ \text{对应的答案}$，此时当前节点的真实答案是否 $\ge$ 当前状态对应的答案。

那么我们不难发现 $1,2$ 操作分别对应取 $\mathrm{or}$ 和取 $\mathrm{and}$ 。初始条件对于生物 $i$ ，$f_i(S)=1\ \text{当且仅当}\ S_i=1$ 。

对于一个查询，我们从大到小枚举所有的可能答案，不难求出这个答案对应的状态 $S$ 。根据上述定义，当我们枚举到第一个状态对应值为 $1$ 的答案时，此时答案即为真实答案。

发现可以用 `bitset` 优化，最终时间复杂度为 $\mathcal O\left(\frac{q2^k+qk^2}{\omega}\right)$ 。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m,mm,q;
int a[13][maxn];
bitset<4100>f[maxn];
int tmp[20],ttt;
void solve(int x,int y){
	ttt=0;
	for(int i=1;i<=m;++i)tmp[++ttt]=a[i][y];
	sort(tmp+1,tmp+ttt+1);
	ttt=unique(tmp+1,tmp+ttt+1)-tmp-1;// 这里做了离散化，在最优化问题中（即本题）不一定有必要
	int S;                            // 但在计数问题中（WC2021T2）必须离散化
	for(int i=ttt;i;--i){
		int xx=tmp[i];S=0;// 枚举答案xx，求出对应状态S
		for(int j=1;j<=m;++j){
			if(a[j][y]>=xx)S|=(1<<(j-1));
		}
		if(f[x][S]){//第一个值为1的状态对应答案即为真实答案
			printf("%d\n",xx);
			break;
		}
	}
}
signed main(){
	read(n);read(m);read(q);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			read(a[i][j]);
		}
		for(int S=0;S<(1<<m);++S){//初始状态求解
			if((S>>(i-1))&1)f[i][S]=1;
			else f[i][S]=0;
		}
	}
	mm=m;
	for(int i=1,op,x,y;i<=q;++i){
		read(op);read(x);read(y);
		if(op==1){//操作1对应 or
			++mm;
			f[mm]=(f[x]|f[y]);
		}
		if(op==2){//操作2对应 and
			++mm;
			f[mm]=(f[x]&f[y]);
		}
		if(op==3){
			solve(x,y);
		}
	}
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：5)

这题真神仙啊……虽然代码特别的短，但是思路非常难以理解……

首先我们注意到最终答案只能是这12个初始生物里的某一个，那么我们不妨从**来源**入手，然后我们对每个生物设$f[i][S]$为$S$的一个子集是否能够至少作为i的所有属性的全部来源（可能直接解释其意义比较难理解……可以先看下面的……）。

先说一下如何统计答案，我们从大到小考虑这个属性初始的k个来源，如果存在一个i使得前i大的来源构成的集合的超集开始在$f[i]$中存在，那么i就是答案了，所以比实际属性小的我们并不用去考虑，只需要去掉比他大的非法集合就行了。

我们考虑如何处理$min$和$max$的情况，我们现在有$a$和$b$，想取min生一个$c$，考虑第$i$个属性，我们假设在这个属性上$a>b$，那么也就是说$a$的一些来源的集合不能成为$c$的，所以我们如果想让$S$成为$c$的来源集合，那么必须当且仅当$f[a][S]=1$且$f[b][S]=1$，那么这个正好是个按位与。或者说，这是个集合的交，因为我们的$S$实际上是超集，我们取的是$a$和$b$内都有的部分。

同理$max$按位或就行了，因为这一定能包含住更大的来源，比这个小的来源不用考虑。

（如果你对此仍然一脸懵逼的话，建议手玩几个例子的$f[i][S]$然后你就会感性理解它是对的……）

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll unsigned long long
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int sz;
	typedef struct _bitset {
	    ll data[70];
	    _bitset() { memset(data, 0, sizeof(data)); }
	    friend _bitset operator|(const _bitset &a, const _bitset &b) {
	        _bitset c;
	        for (register int i = 0; i <= sz; i++) c.data[i] = a.data[i] | b.data[i];
	        return (c);
	    }
	    friend _bitset operator&(const _bitset &a, const _bitset &b) {
	        _bitset c;
	        for (register int i = 0; i <= sz; i++) c.data[i] = a.data[i] & b.data[i];
	        return (c);
	    }
	    inline int get(int b) { return ((data[b / 64] & (1ull << (b & 63))) != 0); }
	    inline void set(int b) { data[b / 64] |= (1ull << (b & 63)); }
	} bitset;
	typedef struct _n {
	    int id;
	    int val;
	    friend bool operator<(const _n &a, const _n &b) { return (a.val > b.val); }
	} node;
	vector<node> vec[200001];
	bitset b[110001];
	void ywymain() {
	    int n = get(), k = get(), q = get();
	    sz = (1 << k) / 64 + 1;
	    for (register int i = 0; i < k; i++) {
	        for (register int j = 1; j <= n; j++) {
	            node cjr;
	            cjr.id = i;
	            cjr.val = get();
	            vec[j].push_back(cjr);
	        }
	        for (register int j = 0; j < (1 << k); j++) {
	            if (j & (1 << i))
	                b[i + 1].set(j);
	        }
	    }
	    for (register int i = 1; i <= n; i++) sort(vec[i].begin(), vec[i].end());
	    int gn = k + 1;
	    while (q) {
	        q--;
	        int op = get();
	        if (op == 1) {
	            int x = get(), y = get();
	            b[gn] = b[x] | b[y];
	            gn++;
	        }
	        if (op == 2) {
	            int x = get(), y = get();
	            b[gn] = b[x] & b[y];
	            gn++;
	        }
	        if (op == 3) {
	            int x = get(), y = get();
	            int s = 0;
	            for (register int i = 0; i < vec[y].size(); i++) {
	                s |= (1 << vec[y][i].id);
	                if (b[x].get(s)) {
	                    printf("%d\n", vec[y][i].val);
	                    break;
	                }
	            }
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：tommymio (赞：3)

### 题意

有 $m$ 个长度为 $n$ 的初始数组 $A_1,A_2...A_m$，和$Q$ 个操作，每个操作为以下 $3$ 个操作中的 $1$ 个：
- $\text{1 x y}$：新建一个数组 $A_p$，令 $A_{p,i}=\max(A_{x,i},A_{y,i})$。
- $\text{2 x y}$：新建一个数组 $A_p$，令 $A_{p,i}=\min(A_{x,i},A_{y,i})$。
- $\text{3 x y}$：查询数组 $A_x$ 的第 $y$ 个元素。

$\texttt{Data Range}:n,Q\leq 10^5,m\leq12$

### 题解

考虑维护那些多次操作后，可能成为数组 $x$ 第 $y$ 个元素来源的数组，这一部分显然可以状态压缩。设 $f_{x,mask}$ 为是否存在 $mask$ 的一个子集 $S$，令 $S$ 能够成为数组 $A_x$ 每个元素的全部来源。

则操作 $1$ 只会扩大来源，形式化的说就是对于两个可行集合取并。操作 $2$ 只会缩小来源，形式化的说就是对于两个可行集合取交。这部分使用 $\text{bitset}$ 维护一下，时间复杂度是 $O(\frac{2^mQ}{\omega})$。

值得注意的是定义中 $mask$ 是个超集，操作 $3$ 中求解时将每个初始数组第 $y$ 个元素从大到小排序依次取，第一次能够取到的就是所求了。

总时间复杂度 $O(2^m(n+\frac{Q}{\omega})+Qm\log n)$。

**Show the Code**

```cpp
#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
std::bitset<1<<12> f[100005];   
int a[15][100005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
int main() {
    int n=read(),m=read(),Q=read(),num=m-1;
    for(register int i=0;i<m;++i) {
        for(register int j=1;j<=n;++j) {
            a[i][j]=read();
        }
    }
    for(register int mask=1;mask<(1<<m);++mask) {
        for(register int i=0;i<m;++i) {
            if(mask>>i&1) f[i].set(mask);
        }
    }
    while(Q--) {
        int op=read(),x=read()-1,y=read();
        if(op==1) f[++num]=f[x]|f[y-1];
        else if(op==2) f[++num]=f[x]&f[y-1];
        else {
            std::vector<std::pair<int,int> > t;
            for(register int i=0;i<m;++i) t.push_back(std::make_pair(-a[i][y],i));
            std::sort(t.begin(),t.end());//from large to small
            int mask=0;
            for(register int i=0;i<m;++i) {
                mask|=1<<t[i].second;
                if(f[x][mask]) {printf("%d\n",-t[i].first);break;} 
            }
        }
    }
    return 0;
}
```
 

---

## 作者：Z_301 (赞：2)

## [CF878D Magic Breeding](https://codeforces.com/contest/878/problem/D)

有 $k$ 个长度为 $n$ 的序列，第 $i$ 个编号为 $i$。编号为 $i$ 的序列的第 $j$ 个元素记为 $a_{i,j}$。

现在有 $q$ 个操作，如下：

1.  `1 x y` ：记现有最大编号为 $m$，新建一个序列，编号为 $m+1$，其中第 $j$ 个元素为 $\min\{a_{x,j},a_{y,j}\}$ $(1\le j\le n)$。

2.  `2 x y` ：记现有最大编号为 $m$，新建一个序列，编号为 $m+1$，其中第 $j$ 个元素为 $\max\{a_{x,j},a_{y,j}\}$ $(1\le j\le n)$。

3.  `3 x y` ：查询第 $x$ 个序列的第 $y$ 个元素的值。

$1\le k \le 12$，$1\le n,q\le 10^5$。

## 题解

假设所有 $a_{i,j}\in\{0,1\}$，怎么做？ 

一个显然的想法是使用 bitset，因为此时两个数的 $\min$ 等于 $\operatorname{and}$，$\max$ 同理。复杂度为 $O(\frac{nq}{w})$。这里 $n,q$ 都只有是 $10^5$，应该能跑，但不重要。

更加一般的，假设我们有一个表格，第 $i$ 行第 $j$ 列为 $a_{i,j}$，就是把数组的内容按顺序写下来。刚才我们是对每一行分开做的，现在考虑分析列之间有什么性质。不难发现本质不同的列最多只有 $2^k$ 种，这是因为如果有两列现在相同，那以后肯定也相同。换句话说，对于固定的一列，初始的 $k$ 行确定了，那后面可以直接推算，确定了。

自然的，考虑维护这样一个数组：$f_{i,S}$ 表示，某一列初始的 $k$ 个元素状态为 $S$，第 $i$ 行的值为 $f_{i,S}$。修改是平凡的，直接取 $\operatorname{and}$ 和 $\operatorname{or}$ 即可。现在考虑查询，发现查询就是把对应列的初始情况拿出来，然后直接查表即可。使用 bitset 维护，复杂度 $O(nk+\frac{q2^k}{\omega})$，随便跑。

好了，现在 $a_{i,j}\in \Z$。考虑把它转化为 $a_{i,j}\in\{0,1\}$。

还是对于每一列考虑。记答案为 $A$，假设我们有一个 $x$，然后令 $a'_{i,j}=[a_{i,j}\ge x]$，对 $a'$ 做上面的事情，不难发现，算出来的就是 $[A\ge x]$，也就是说我们现在能 check 任意 $x$ 和答案的大小关系。到这里一个显然的想法是二分答案。一个更简单的做法是， 第 $j$ 列初始 $a$ 值构成的可重集记为 $S$，然后对所有 $x$ 满足 $x\in S$，求出 $[A\ge x]$，不难发现 $A=\max\limits_{x\in S,A\ge x}x$，因为有 $A\in S$ 所以这是显然的。

考虑维护，因为在 $a_{i,j}\in\{0,1\}$ 的时候，我们已经对于所有初始状态维护出每一行的值，所以查询的时候直接算出对应初始状态（这里可以直接 $O(k^2)$ 暴力，也可以 $O(k\log k)$ 排序，都是随便过），然后查表即可。复杂度 $O(\min\{n,q\}k^2+\frac{q2^k}{w})$ 或者 $O(\min\{n,q\}k\log k+\frac{q2^k}{w})$。由于这里有 $k=12$，所以 $k^2=144$，$\frac{2^k}{w}=64$，不好说那个大，就都写了（）。

[一种可能的的代码实现](https://codeforces.com/contest/878/submission/242172697)。

---

## 作者：hegm (赞：1)

### [Magic Breeding](https://www.luogu.com.cn/problem/CF878D)

考虑如何“魔法变化”。

暂不考虑复杂度，考虑 $10^9$ 值域不好处理，假如值域为 $0/1$，那么我们可以用 $\text{bitset}$ 爆草。

每次暴力合并两个节点，复杂度是 $\frac{nq}{w}$，但是这么做很劣，考虑本质不同的位。

我们将 $k$ 个生物（行）的 $n$ 个（列）特征值排成 $k\times n$ 的矩阵。

我们每次本质是将两行进行 $\&$ 或者 $|$。

那么对于初始长得完全一样的列，他们在操作之后也一定完全一样，因此本质上只有 $2^k$ 种不同的列。

因此我们仅需要考虑 $2^k$ 种列操作，每次查询的时候查询列对应的 $2^k$ 种的实际值即可，复杂度为 $\frac{q2^k}{w}$。

现在考虑如何处理值域为非 $0/1$，那么我们将其转化为 $0/1$ 即可。

考虑将同一列的数离散化，然后拆成 $k$ 列，对于排名为 $i$ 的数，其变为 $[1,i]$ 个 $1$ 组成，剩余位置为 $0$。

虽然列数变化了，但是实际上还是仅有 $2^k$ 个本质不同列，因此复杂度不变。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define make make_pair
#define pii pair<int,int>
#define N 100505
#define M 13
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,k,q,a[M][N],id[N*M],p[M][N];
bitset<5000> s[N];
pii d[N][M];
signed main()
{
	n=read();k=read();q=read();
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		a[i][j]=read();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)d[i][j]={a[j][i],j};
		sort(d[i]+1,d[i]+1+k);
		for(int j=1;j<=k;j++)p[d[i][j].se][i]=j;
		for(int j=1;j<=k;j++)
		{
			for(int l=1;l<=k;l++)
			{
				id[(i-1)*k+j]*=2;
				id[(i-1)*k+j]+=(p[l][i]>=j);
			}
		}
	}
	int lim=(1<<k);
	for(int i=1;i<=k;i++)
	{
		for(int j=0;j<lim;j++)
		s[i][j]=((j>>(k-i))&1);
	}
	int e=0;
	while(q--)
	{
		int t=read(),x=read(),y=read();
		if(t==3)
		{
			int c=0;
			for(int i=(y-1)*k+1;i<=y*k;i++)c+=s[x][id[i]];
			cout<<d[y][c].fi<<"\n";
		}
		else
		{
			++e;
			if(t==1)s[k+e]=s[x]|s[y];
			if(t==2)s[k+e]=s[x]&s[y];
		}
	}
	return 0;
}

```

---

## 作者：SnowTrace (赞：1)

记录一个思维过程相对连贯的题解。

首先我们看到本题有取 $\operatorname{min}$，取 $\operatorname{max}$ 操作，我们不难想到可以枚举答案，$\leq x$ 的值都设为 $0$，$> x$ 的值都设为 $1$ 进行求解。

我们考虑转化成 01 序列后应该怎么做。由于 $k$ 比较小，那么实际上此时会有一部分特征（就是 $a$ 数组上的一个列）是本质相同的。本质不同的列只有 $2^k$ 种。（这里本质相同的意思其实就是转化成 01 序列两个列上所有相同位置数的值都一样，这时候这两列算出来答案肯定是一样的）

我们不妨对每一种初始的列状态都去模拟一遍合并的过程。复杂度 $O(q2^kk)$，无法通过。

注意到你的所有操作都是位运算，实际上可以把状态压进 bitset 进行整体转移，时间复杂度 $O(\dfrac{q2^k k}{\omega})$，大概可以过。

更进一步，这种整体转移实际上算出了所有列状态的答案，所以可以提前把所有的结果预处理出来，然后再枚举答案，这样就是 $O(\dfrac{q2^k}{ \omega}+qk^2)$ 的了。


```cpp
/*
去逃避。 
*/

#include<bits/stdc++.h>
using namespace std;
#define double long double
#define lowbit(x) (x&(-x))
bitset<4100>s[100025];
int a[15][100005];
int n,k,q; int nw = 0;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k >> q;
	for(int i = 1;i<=k;i++){
		for(int j = 1;j<=n;j++)cin >> a[i][j];
	}
	for(int i = 1;i<=k;i++){
		for(int j =0;j<(1<<k);j++){
			if(j>>(i-1)&1)s[i][j] = 1;
			else s[i][j] = 0;
		}
	}
	nw = k;
	while(q--){
		int t;cin >> t;
		if(t == 1){
			int x,y;cin >> x >> y;
			s[++nw] = s[x]|s[y];
		}else if(t == 2){
			int x,y;cin >> x >> y;
			s[++nw] = s[x]&s[y];
		}else{
			int x,y;cin >> x >> y;
			vector<int>p;
			for(int i = 1;i<=k;i++)p.push_back(a[i][y]);
			sort(p.begin(),p.end());
			for(int i = k-1;i>=0;i--){
				int S =0;
				for(int j = 1;j<=k;j++){
					if(a[j][y]>=p[i]){
						S|=1<<j-1;
					}
				}
				if(s[x][S]){
					cout << p[i] << endl;break;
				}
			}
		}
	}
	return 0;
}

```

---

## 作者：LinkyChristian (赞：1)

喵喵题。

首先注意到 $k$ 很小，是个很适合状态压缩的范围。

很显然列与列之间是独立的，因此对每一列 $k$ 个数分开考虑。

因为我们要状压，显然需要状态是一个 $k$ 位的二进制数。考虑 $a_{i,j}$ 为二进制数的情况。发现此时本质不同的列很少，只有 $2^k$ 种。因此将列的状态记到 dp 状态中，设 $f_{i,S}$ 表示列的初始状态为 $S$ 时，第 $i$ 行的这一列的值。 

考虑转移。不好处理的 $min$ 和 $max$ 在二进制状况下变成了 $\wedge$ 和 $\vee$ 操作，因此我们使用 bitset 优化 dp。

考虑如何将普通情况转化为二进制情况。我们发现我们只关心数之间的大小关系，不关心其具体的值。因此可以考虑一种转换方式使其只记住该数在列中的排名，并且也能将 $min$ 和 $max$ 操作转换为 $\wedge$ 和 $\vee$ 操作。

设一个数在此列中的排名为 $p$ ，我们将其转换为 $p$ 个 $1$ 后面跟着 $k-p$ 个 $0$ 。很显然，我们只要数 $1$ 的个数就能知道该数在列中的排名。我们将一行中的每个数都转换为这样的一个 $k$ 位二进制数。我们将一个 $k\times n$  的正整数矩阵转换为了一个 $k\times kn$ 的 $01$ 矩阵。在转换后的矩阵中依旧可以将每一列分开来考虑，因此按之前的做法做即可，复杂度为 $O(q\frac{2^k}{w})$。

---

## 作者：老莽莽穿一切 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16309694.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF878D)

[**CF link**](https://codeforces.com/problemset/problem/878/D)

又是一道 `bitset` 科技题，但是思维难度也还是很高的。

考虑先弱化一下题目，如果特征只有 $0/1$ 该怎么做，考虑对于 $0/1$ 来说，$\min/\max$ 可以看成 $\operatorname{bitand}/\operatorname{bitor}$ 操作，那么我们考虑如果将所有生物的一种特征单独做会怎么样，现在的问题就变成了给定一个数组，每次新生成一个元素表示为之前选取两个值的 $\operatorname{bitand}/\operatorname{bitor}$，现在的情况是因为有 $10^5$ 种特征，每一位单独做时间复杂度无法接受，但是发现因为初始数组只有 $12$ 个生物，所以如果特征只有 $0/1$ 的话最多只有 $2^{12}=4096$ 种情况，时间复杂度并不是不能接受，而且可以用 `bitset` 的 `&` 和 `|` 操作加速，性质非常优秀。

考虑如何将 $10^9$ 的值域转化成 $0/1$，这可以说是一个经典套路，首先我们发现因为初始只有 $12$ 个值，而 $\min/\max$ 操作不会产生新的值，所以值最多只有 $12$ 种，对于将大值域转化成 $0/1$ 一个经典的手段在二分时经常用到，就是设一个阈值 $\text{limit}$，如果一个值比 $\text{limit}$ 小就是 $0$，否则就是 $1$，这里我们也可以照用，我们一共有 $12$ 种阈值，难道每个都维护一遍吗？实际上不用这么麻烦。考虑前面我们发现一共就 $4096$ 种情况，我们可以直接设任意一个值为 $0/1$ 的情况，全部记录下来，即设 $f_{i,sta}$ 表示 $sta$ 对应的所有位置的值都为 $1$ 的情况下第 $i$ 个值是什么，然后发现因为 $\min/\max$ 操作对应 $\operatorname{bitand}/\operatorname{bitor}$，且在生成 $i$ 时转移每个 $sta$ 操作的方法是一样的，所以可以用 `bitset` 优化，然后查询操作直接从大到小枚举阈值更新 $sta$ 直到答案为 $f_{i,sta}=1$，初始化就是 $f_{i,sta}=[i\subseteq sta]$。

[代码](https://codeforces.com/contest/878/submission/158359406)并没有想象中那么难。

---

## 作者：_tourist_ (赞：0)

每一列中只有$12$种取值，把其排序以后将最终答案拆贡献。

定义$val[i]$为排好序以后的差分数组，那么一列的答案可以表示为：

$$ans=\sum^{i} [ans>=a[i]]*val[i]$$

用一个$dp[mask]=[0,1]$表示当满足对于所有$i \in mask$,$j \notin mask$，有$a[i]>a[j]$时，$dp$值为$1$则表示$ans \in mask$，反之则$ans \notin mask$，那么$ans$和这个$12$个元素的关系只有$4096$种。

所以我们可以每一行维护一个长度为$4096$的$01$串，如果是取$max$则是取或，取$min$则是取交。

因为每个元素只有$0,1$，所以可以$bitset$优化。

初始第$i$行的$dp[mask]=1$当且仅当$i \in mask$

最后统计答案的时候，对该列元素从小到大枚举，依次把$mask$的每一位从$1$改到$0$，如果$mask$为$1$，则$ans \in mask$，代表$ans>=a[i]$，其中$i$是$\in mask$所有元素中的最小值，那么$ans$加上之前所说的差分数组即可。

复杂度$O(\frac{4096q}{\omega})$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110020;
typedef pair<int,int> pii;
#define mk make_pair
struct QU{
    int opt,x,y;
}Q[N];
int n,k,q;
bitset<4096> bit[N];
int a[13][N]; pii b[13];
 
int main()
{
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
    for(int i=1;i<=k;i++){
        for(int j=0;j<(1<<k);j++)
            bit[i][j]=((j>>(i-1))&1);
    }
    int tot=k;
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&Q[i].opt,&Q[i].x,&Q[i].y);
        if(Q[i].opt==1) bit[++tot]=bit[Q[i].x]|bit[Q[i].y];
        else if(Q[i].opt==2) bit[++tot]=bit[Q[i].x]&bit[Q[i].y];
        else{
            for(int j=1;j<=k;j++) b[j]=mk(a[j][Q[i].y],j);
            sort(b+1,b+k+1);
            for(int j=k;j>=0;j--) b[j].first-=b[j-1].first;
            int mask=(1<<k)-1,ans=0;
            for(int j=1;j<=k;j++){
                if(bit[Q[i].x][mask]) ans+=b[j].first;
                mask^=(1<<(b[j].second-1)); 
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

CF 评分有毒吧，暴力题上 *2900。

先口胡一下，代码等会再写。

首先考虑 $a_{x,y}\in \{0,1\}$，那 $n$ 个属性对应的人的状态只有 $2^k$ 个，可以把状态相同的属性都合并成一个属性。

取 $\max$ 和 $\min$ 操作就变成了两个人与/或起来。我们可以对每个属性都单独考虑。令 $f_{i,S}$ 表示前 $k$ 个人该属性状态为 $S$，第 $i$ 个人该属性的值。用 `bitset` 可以 $O(\frac{2^kq}{w})$ 预处理。

然后考虑 $a_{x,y}\in \mathbb{N^*}$，对于一个询问，离散化后 $O(k)$ 枚举答案 $x$ ，$<x$ 的权值改为 $0$，$\ge x$ 的权值改为 $1$。因为这样的话取 $0$ 与 $0$ 取 $\max$ 还是 $0$，代表小于 $x$ 的数和另一个小于 $x$ 的数取最大还是小于 $x$，另外三种情况同理。而权值改变后的答案已经预处理出来了，所以每次询问 $O(k^2)$。

复杂度 $O(q(\frac{2^k}{w}+k^2))$。

---

upd : 补上了[评测记录](https://codeforces.com/contest/878/submission/188676454)。

其实不用并查集合并相同属性，因为你对 $2^k$ 种情况都预处理了，直接求出对应情况的答案即可。

---

## 作者：tzc_wk (赞：0)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/878/problem/D)

提供一个和其它题解不太一样的理解方式，可能会稍微好理解一些，虽然代码和其它题解大同小异。

很容易发现一件事情，那就是数组的每一位都是独立的，但由于这题数组长度 $n$ 很大，我们不能每次修改都枚举每一位更新其对答案的贡献，这样复杂度必炸无疑。但是这题有个显然的突破口，那就是 $k$ 的取值范围很小，最高只有 $12$，也就是说每一位的取值最多只有 $12$ 种可能，我们考虑以此为突破口，设计一个与这 $k$ 个数的具体取值无关的状态。

首先我们知道每一位是独立的，故我们可以把每一位拆开来考虑，于是问题由二维变成一维：给定 $k$ 个数 $a_1,a_2,\dots,a_k$，$q$ 次操作，每次操作给定两个数 $i,j$，有两种类型，要么新建一个数 $a_n=\max(a_i,a_j)$，要么新建一个数 $a_n=\min(a_i,a_j)$。

我们先来看一个弱化版本，那就是 $\forall a_i\in [0,1]$，我们设计一个状态 $f_{i,S}$，$f_{i,S}=1$ 表示 $\forall j\in S,a_j=1\Rightarrow a_i=1$，也就是说如果 $S$ 中的元素都为 $1$ 那么 $a_i$ 就一定为 $1$，否则不能确定 $a_i$ 究竟是 $1$ 还是 $0$，显然最初对于 $i\in[1,k]$，满足 $i\in S$ 的 $f_{i,S}$ 都为 $1$，其余的 $f_{i,S}$ 都为 $0$。

我们考虑新建一个 $a_n=\max(a_i,a_j)$ 会造成什么样的影响，对于集合 $S$，如果 $f_{i,S}=1\lor f_{j,S}=1$，那么 $a_i,a_j$ 中一定至少有一个为 $1$，故 $a_n=\max(a_i,a_j)$ 一定为 $1$，故 $f_{n,S}=1$。反之，$f_{i,S}=f_{j,S}=0$，我们就不能确定 $a_i,a_j$ 的值，也就是说最坏情况下会出现 $a_i=a_j=0$ 的情况，此时 $a_n=0$，故 $f_{n,S}=0$。故我们有 $f_n=f_i\lor f_j$。同理我们也可将取 $\min$ 的情况与 $\land$ 联系在一起。至于查询……比方说我们要查询第 $x$ 个数组第 $y$ 列的数，我们记 $T=\{i|a_{i,y}=1,i\in [1,k]\}$，如果 $f_{x,T}=1$，根据 $f$ 数组的定义可知 $a_{x,y}=1$，反之，根据 $f$ 数组的定义知在剩下数乱填的情况下，有可能出现 $a_x=0$ 的情况，而显然在“$T$ 之外的数乱填”的情况下，让 $a_x$ 值最小的填法是其它数全填 $0$，而我们有 $\forall i\notin T,a_{i,y}=0$，故 $a_x=0$。也就是说我们只需输出 $f_{x,T}$ 即可，复杂度 $q2^k+2^k$，使用 `bitset` 即可优化到 $\dfrac{q2^k}{w}+k2^k$

现在我们考虑将更一般的情况规约到特殊情况，由于每一位是独立的，我们还是将目光聚焦到某一特定的列（假设为第 $i$ 列）上，对于初始 $k$ 个数组第 $i$ 列上的数我们将其从大到小排个序，设排好序的数组为 $x_{1},x_2,\dots,x_k$，我们对于每个 $a_{t,i}$（包括新建的数组）新建 $k$ 个 0/1 变量 $b_{t,1,i},b_{t,2,i},\dots,b_{t,k,i}$，其中 $b_{t,j,i}$ 为 $1$ 表示 $a_{t,i}\ge x_j$，反之 $a_{t,i}<x_j$，查询就从 $1$ 枚举到 $k$ 直到遇到第一个 $b_{x,i,y}=1$ 并输出 $x_i$ 即可。显然这个小小的修改只不过是将数组长度由 $n$ 变成了 $nk$，在弱化版本中我们 $f$ 数组的定义即求解方法照样使用，复杂度 $\dfrac{q2^k}{w}+k^22^k$，有点脑子就可以优化到 $q2^k+k2^k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXK=12;
const int MAXS=1<<MAXK;
const int MAXN=1e5;
int n,k,qu,cnt,a[MAXK+3][MAXN+5];
bitset<MAXS+4> f[MAXN+MAXK+3];
pii ord[MAXN+5][MAXK+3];
bool cmp(pii x,pii y){return a[x.fi][x.se]>a[y.fi][y.se];}
int main(){
	scanf("%d%d%d",&n,&k,&qu);cnt=k;
	for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	for(int j=1;j<=n;j++) for(int i=1;i<=k;i++) ord[j][i]=mp(i,j);
	for(int j=1;j<=n;j++) sort(ord[j]+1,ord[j]+k+1,cmp);
	for(int i=1;i<=k;i++) for(int j=0;j<(1<<k);j++) if(j>>i-1&1) f[i][j]=1;
	while(qu--){
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) f[++cnt]=f[x]|f[y];
		else if(opt==2) f[++cnt]=f[x]&f[y];
		else{
			int msk=0;
			for(int i=1;i<=k;i++){
				msk|=1<<ord[y][i].fi-1;
				if(f[x][msk]){
					printf("%d\n",a[ord[y][i].fi][y]);
					break;
				}
			}
		}
	}
	return 0;
}
```



---

