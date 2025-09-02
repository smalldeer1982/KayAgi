# [ICPC 2022 Xi'an R] Contests

## 题目描述

$n$ 个选手参加了 $m$ 场比赛。给出每场比赛的排行榜。第 $k$ 场比赛的排行榜是一个 $n$ 阶排列 $a_k$，表示选手 $a_{k, i}$ 的排名为 $i$。

SolarPea 和 PolarSea 也是选手。SolarPea 想要证明他比 PolarSea 更强。

定义选手 $x$「$l$ - 强于」选手 $y$，当且仅当存在长度为 $l + 1$ 的序列，满足 $b_1 = x$，$b_{l + 1} = y$，且对于所有 $1\leq i\leq l$，均有 $b_i$ 在至少一场比赛中排名小于 $b_{i + 1}$。

给出 $q$ 组询问。在第 $i$ 组询问中，SolarPea 是选手 $x$，PolarSea 是选手 $y$。求出最小的正整数 $l$，使得 $x$「$l$ - 强于」$y$。

$2\leq n\leq 10 ^ 5$，$1\leq q\leq 10 ^ 5$，$1\leq m\leq 5$，$1\leq x, y\leq n$，$x\neq y$。

## 样例 #1

### 输入

```
6 2
1 3 2 5 4 6
2 1 4 3 6 5
4
1 4
5 3
6 1
5 2
```

### 输出

```
1
2
5
3
```

# 题解

## 作者：under_the_time (赞：11)

## 题意

> 大致题意见题目描述，这里主要解释一下选手 $x$ 「$l$-强于」 选手 $y$：
>
> 以样例为例，对于第一个询问：`1 4`。在第一场比赛中选手 $1$ 的排名已经比选手 $4$ 的排名靠前，所以 $l_{\min} = 1$。
>
> 对于第二个询问：`5 3`。虽然在第一场比赛中选手 $5$ 比选手 $3$ 差，但是比选手 $4$ 好；而第二场比赛中选手 $4$ 又比选手 $3$ 好，所以 $l_{\min}=2$。
>
> 对于第三个询问：`6 1`。我们用 $x \to y$ 表示选手 $x$ 比选手 $y$ 在某一场比赛中排名更靠前，则有：$6\to5\to4\to3\to2\to1$，所以 $l_{\min}=5$。
>
> 对于第四个询问：`5 2`。那么有 $5\to 4\to 3\to 2$，所以 $l_{\min}=3$。

## 思路

暴力的做法是从小到大枚举步数，并维护不超过 $k$ 步能到达的所有选手。注意到我们永远可以通过“$m$ 场比赛的前缀并”来描述下一步能到的所有选手，于是模拟过程中我们可以只维护 $m$ 个选手编号。

考虑使用倍增加速，预处理每个跳 $2^0,2^1,2^2,\dots$ 步能到的 $m$ 维最值即可，复杂度 $O((n+q)m^2\log n)$。

具体地，我们记 $f_{i,j,k}$ 表示 $i$ 跳 $2^j$ 步，能到的第 $k$ 场比赛考的最好的排名：

- $j=0$ 暴力预处理；
- $j>0$ 我们枚举中转点使用的比赛 $c$，然后先跳 $f_{i,j-1,c}$，$f_{j,j,k}\leftarrow f_{c,j-1,k}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 10, maxk = 25;
int n,m,T,ans,a[maxm][maxn],b[maxm][maxn];
struct hyf { int c[maxm]; } f[maxk][maxn],g[maxm][maxn]; // 倍增数组
// 两个纯用于压行的函数，展开来写也彳亍
hyf Min(const hyf &x,const hyf &y) {
    hyf res;
    for (int i = 0;i < m;i ++) res.c[i] = min(x.c[i],y.c[i]);
    return res;
}
bool operator >(const hyf &x,const hyf &y) {
    for (int i = 0;i < m;i ++)
        if (x.c[i] <= y.c[i]) return false;
    return true;
}
hyf input(const int &x) {
    hyf res;
    for (int i = 0;i < m;i ++) res.c[i] = b[i][x];
    return res;
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0;i < m;i ++)
        for (int j = 1;j <= n;j ++){
            scanf("%d",&a[i][j]);
            b[i][a[i][j]] = j; // 第i场比赛中选手a[i][j]的名次为j
        }
    // 预处理倍增数组
    // 处理 j = 0
    for (int i = 0;i < m;i ++)
        for (int j = n,x;j >= 1;j --) {
            x = a[i][j], g[i][j] = input(a[i][j]);
            if (j < n) g[i][j] = Min(g[i][j],g[i][j + 1]);
        }
    for (int i = 1;i <= n;i ++) {
        f[0][i] = g[0][b[0][i]];
        for (int j = 1;j < m;j ++)
            f[0][i] = Min(f[0][i], g[j][b[j][i]]);
    }
    // 处理 j > 0
    for (int b = 1;b <= 19;b ++)
        for (int i = 1;i <= n;i ++) {
            f[b][i] = f[b - 1][i];
            for (int j = 0,k;j < m;j ++) 
                k = a[j][f[b - 1][i].c[j]],
                f[b][i] = Min(f[b][i],f[b - 1][k]);
        }
    scanf("%d",&T);
    for (int t = 1,x,y;t <= T;t ++) {
        scanf("%d%d",&x,&y);
        hyf st = input(x), en = input(y);
        // 开始倍增跳
        if (st > en) { // 需要跳几场比赛，也就是一开始st没有en厉害
            int res = 0;
            for (int i = 19;i >= 0;i --) {
                hyf nxt = st;
                for (int j = 0,k;j < m;j ++) 
                    k = a[j][st.c[j]],
                    nxt = Min(nxt,f[i][k]);
                if (nxt > en) res += 1 << i, st = nxt;
            }
            if (res > n) printf("-1\n");
            else printf("%d\n",res + 2); // 记得加上开头 & 结尾
        } else printf("1\n");
    }
    return 0;
}
```

- 评测记录：[R127071409 记录详情](https://www.luogu.com.cn/record/127071409)

---

## 作者：Jerrycyx (赞：9)

## 引言

思路上，其它题解已经讲得很清楚了，就是预处理再倍增。但是具体的转移方程和代码实现迄今为止却没有一篇题解讲清楚，~~导致本蒟蒻狂调一整天~~。

这里我参考 @[under_the_time](https://www.luogu.com.cn/user/680855) 的[题解](https://www.luogu.com.cn/article/y8u620q0)里的处理方式，讲一讲相关状态的定义和转移、预处理和倍增的具体过程是怎样的。

## 前置

### 名词解释

先解释一下将要用到的名词：
+ 元素/点：均指某个人；
+ 位置：某一个排行榜内的一个排名；
+ 组：一个排行榜；
+ 排名高/低：在排行榜内的位置靠前/后。
+ 跳/走 $x$ 步：将题目看成“每次可以跳一步，$x$ 可以跳到 $y$ 当且仅当存在一个序列使得 $y$ 出现在 $x$ 后面，问最少跳几步。”（[来源](https://www.luogu.com.cn/article/cu5dsrog)）

### 结构体

首先，定义一个结构体类型 `Rank`，内含一个大小为 $m$ 的数组，存储的是一个点在各个组内的排名信息、一个点在各个组的可达最高排名/**可达范围（每组内都是一段后缀）的起点**。

```cpp
struct Rank{
	int c[M];
};
```

我们要让它支持两种操作：比较和合并。

先说合并。在预处理过程中，我们会得到某个点通过某种**单一路径**可以得到不同的最高排名信息。而这些信息需要合并成一个完整的排名信息，即这个点通过**所有路径**所能到达每组的最高排名。

合并的代码也很简单，直接取各个方式的最高排名即可，本文中重载为加号 `+`：

```cpp
Rank operator + (const Rank &x,const Rank &y)
{
	Rank res;
	for(int i=1;i<=m;i++)
		res.c[i]=min(x.c[i],y.c[i]);
	return res;
}
void operator += (Rank &x,const Rank &y){x=x+y;}
```

（其实这里重载的加号更像是一个 $\min$ 操作？）

再说比较。在倍增过程中，我们要判断某个点 $x$ 是否已经可以一步到达另一个点 $y$。这种情况发生当且仅当 $x$ 所能到达的最高排名中**存在**一个位于 $y$ 的前面。

```cpp
bool operator < (const Rank &x,const Rank &y) //x能够一步走到y当且仅当x<y 
{
	for(int i=1;i<=m;i++)
		if(x.c[i]<y.c[i]) return true;
	return false;
}
```

以上单次操作时间复杂度均为 $O(m)$。

### 状态表示

然后是倍增的状态表示（姑且先这么叫）。

+ $p(i)$ 表示 $i$ 在每一组的原始排名（代码中为 `pos`）；
+ $f(i,j)$ 表示 $i$ **在每一组中的后缀**跳 $2^j$ 步后能抵达每一组的最高排名；
+ $g(i,j)$ 表示第 $i$ 组内处于 $[j,n]$ **位置**上的**所有人**在每一组的最高排名（即后缀和）。

以上三个状态都是 `Rank` 类型。

（迄今为止所有题解都没有提到需要用 $g$ 来辅助计算 $f$，导致本蒟蒻迷惑了很久。）

解释：
+ $f$ 表示每组后缀是因为，除了第一步是只能从单点走成后缀以外，其它所有步都是 $m$ 段**后缀上的所有点尝试向外跳**，状态这样设置更好转移。
+ $f(i,0)$ 不好直接计算，所以此处 $g$ 的目的便是辅助初始化 $f(i,0)$，具体过程在后面。

### 特别注意

本题千万不要把不同组内**同一个数**的来回切换看做一步！

（这个错误想法导致我挂了很多次，甚至写这篇题解时也差点又这么想。）

## 预处理

### $g$ 数组

对于倍增的预处理，首先需要计算 $g$，前面已经提到它是一个后缀和，所以直接这样计算就行，时间复杂度 $O(m^2 n)$。

$$g(i,j) = \sum_{k=j}^{n} p(a_{i,j}) = p(a_{i,j}) + g(i,j+1)$$

（求和符号 $\sum$ 所用为上文重载过的加号，下同。）

```cpp
for(int i=1;i<=m;i++)
	for(int j=n;j>=1;j--)
	{
		if(j==n) g[i][j]=pos[a[i][j]];
		else g[i][j]=pos[a[i][j]]+g[i][j+1];
	}
```

### $f(i,0)$ 初始化

有了 $g$ 以后就可以据此来初始化 $f(i,0)$ 了，时间复杂度 $O(m^2 n)$。

$$f(i,0) = \sum_{j=1}^{m} g(j,p(i)_j)$$

这里面的 $j$ 用来枚举 $i$ 所属的组。对于某一个 $j$，$p(i)_j$ 表示 $i$ 在第 $j$ 组中所处的位置。根据定义，$f(i,0)$ 表示每一组内 $i$ 的后缀跳 $1$ 步的最高排名。若当前在第 $j$ 组，那么这一段后缀就是 $[p(i)_j,n]$，$g(j,p(i)_j)$ 就表示了这段后缀在所有组上可达的最大排名（走的这 $1$ 步就是将这些最大排名扩展为后缀）。将所有组内的 $m$ 段后缀合并起来得到 $f(i,0)$， 所表示即为 $m$ 段后缀在全局的可达最大排名。

```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(j==1) f[i][0]=g[1][pos[i].c[1]];
		else f[i][0]+=g[j][pos[i].c[j]];
	}
```

### 剩下的 $f$

最后就可以求出所有 $f$ 值了，时间复杂度 $O(m^2 n \log n)$。

$$f(i,k) = \sum_{j=1}^{m} f(a_{j,f(i,k-1)_j},k-1)$$

该方程中 $j$ 的作用为枚举中转点，我们只需要记录排名最高的那个中转点就行了。

> 解释一下为什么**只用记录最高排名**就行了。因为这里方程所转移的**只是将这个最高排名点作为中转点**，从而**便于走到该组内其它点**的（以最高点走向组内其它点一定最优）。
>
> 反之，**若某条路径无需以它作为中转点就可直达，那么这条路径的贡献应该在枚举这个中转点之前就已经计算完毕**。如果加上中转点，多出来了一段长度，比已有的路径更劣，也不会更新和影响现有答案。

$f(i,k-1)_j$ 表示 $i$ 对应后缀走 $2^{k-1}$ 步，在第 $j$ 组的最高排名/可达后缀；$a_{j,f(i,k-1)_j}$ 即为这个最高排名所对应的数，令它为 $x$。最后 $f(x,k-1)$ 也就是从点 $x$ 出发，再走 $2^{k-1}$ 步（刚才所得已经是可达后缀了，所以这里无需再走一步来将单点扩展为后缀），一共就是 $2^{k-1}+2^{k-1}=2^k$ 步，即 $f(i,k)$。

```cpp
for(int k=1;k<=logN;k++) //确定其余 f
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(j==1) f[i][k]=f[a[j][f[i][k-1].c[j]]][k-1];
			else f[i][k]+=f[a[j][f[i][k-1].c[j]]][k-1];
		}
```

## 倍增

### 求解

前面的过程将整个路径分成三部分：
+ 第一步，将 $x$ 可达范围从 $m$ 个单点扩展为 $m$ 段后缀；
+ 中间若干步，不断扩展使得 $X$ 的表示的后缀中**刚好**任意一段都**不**包含 $Y$，这也是倍增过程所求的；
+ 最后一步，因为 $X$ 刚好不能达到 $Y$，所以走这最后一步就可以直接抵达 $y$ 了。

读入 $x$、$y$ 后，我们首先需要获取它们的原始排名，设为 $X$ 和 $Y$，第一步以后它们就将成为多段后缀段。

倒序枚举 $k$ 的同时，**模拟** $X$ 走 $2^k$ 步后的结果 $nxt$，如果 $nxt<Y$（之前已经重载了 `<` 符号，表示能够直接抵达）不成立，则把这一步实实在在走出去，令 $X \gets nxt$，并把步数加上 $2^k$。

最后的步数应该加上前后省略的那两步，时间复杂度 $O(m^2 q \log n)$。

### 无解

对于每一个有效步，至少能多覆盖一个点，否则未来永远无法覆盖更多点了。

因此，一个全部由有效步构成的路径至多有 $n$ 步。超出 $n$ 步代表有效路径无法覆盖 $y$，因此可判无解。

> 或者你也可以将题目看做图论最短路，$x$ 到 $y$ 至多 $n$ 个点。

### 特判

注意特判 $x$ 能够一步到达 $y$ 的情况，此时第一步和最后一步是同一步，而中间的步骤根本不存在（因为 $x \neq y$，所以答案至少是 $1$）。

倍增部分代码：

```cpp
int px,py; scanf("%d%d",&px,&py);
Rank x=pos[px],y=pos[py];
if(x<y) printf("1\n"); //特判一步即达 
else
{
	int ans=0;
	for(int i=logN;i>=0;i--)
	{
		Rank nxt=x;
		for(int j=1;j<=m;j++)
			nxt+=f[a[j][x.c[j]]][i];
		if(!(nxt<y)) ans+=1<<i,x=nxt; //nxt不能抵达y 
	}
	if(ans>n) printf("-1\n"); //无解 
	else printf("%d\n",ans+2);
}
```

## 代码

总时间复杂度 $O(m^2 (n+q) \log n)$

提交记录：[R203561810](https://www.luogu.com.cn/record/203561810)。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=1e5+5,M=10,logN=17;
int n,m,q,a[M][N];

struct Rank{
	int c[M];
}pos[N],f[N][logN+5],g[M][N];
/*
 * pos[i]：i在每组内的排名/一步后的可达后缀 
 * f[i][j]：i跳2^j步后在每一组的最高排名/可达后缀 
 * g[i][j]：第i组内j~n位置上的所有人在每一组的最高排名/可达后缀 
 */
bool operator < (const Rank &x,const Rank &y) //x能够走到y当且仅当x<y 
{
	for(int i=1;i<=m;i++)
		if(x.c[i]<y.c[i]) return true;
	return false;
}
Rank operator + (const Rank &x,const Rank &y) //合并两个排名信息 
{
	Rank res;
	for(int i=1;i<=m;i++)
		res.c[i]=min(x.c[i],y.c[i]);
	return res;
}
void operator += (Rank &x,const Rank &y){x=x+y;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			pos[a[i][j]].c[i]=j;
		}
	for(int i=1;i<=m;i++)
		for(int j=n;j>=1;j--) //确定 g 
		{
			if(j==n) g[i][j]=pos[a[i][j]];
			else g[i][j]=pos[a[i][j]]+g[i][j+1];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) //确定 f[i][0] 
		{
			if(j==1) f[i][0]=g[1][pos[i].c[1]];
			else f[i][0]+=g[j][pos[i].c[j]];
		}
	for(int k=1;k<=logN;k++) //确定其余 f
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(j==1) f[i][k]=f[a[j][f[i][k-1].c[j]]][k-1];
				else f[i][k]+=f[a[j][f[i][k-1].c[j]]][k-1];
			}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int px,py; scanf("%d%d",&px,&py);
		Rank x=pos[px],y=pos[py];
		if(x<y) printf("1\n"); //特判一步即达 
		else
		{
			int ans=0;
			for(int i=logN;i>=0;i--)
			{
				Rank nxt=x;
				for(int j=1;j<=m;j++)
					nxt+=f[a[j][x.c[j]]][i];
				if(!(nxt<y)) ans+=1<<i,x=nxt; //nxt不能抵达y 
			}
			if(ans>n) printf("-1\n"); //无解 
			else printf("%d\n",ans+2);
		}
	}
	return 0;
}
```

## 后记

本人蒟蒻，即使知道了倍增思路以后也难以打出代码，最后因为被 $O(m^2(n+q) \log n)$ 的时空复杂度卡得 MLE+TLE 而选择放弃原有的处理方式而学习题解中的处理方式。花费 $30$ min 终于（自认为）读懂。于是打算补充大佬们不屑于讲解和证明的部分，写成此篇题解造福后人。

但是，在写题解的过程中，我发现我的理解依然有诸多缺漏，状态的定义和转移仍有许多不完整甚至错误之处，所以这篇题解也经过多次修正，直到整个逻辑自洽，这整个过程也让我受益匪浅。

因为多次修改，本题解难免会有一些前后语言表述不通顺的情况，还请多多包涵、提出意见，谢谢！

---

## 作者：dead_X (赞：9)

怎么都想得到倍增。

这个题他一定会做。

考虑每次我们的操作都是为了下一次跳做准备，即跳到下一场比赛排名最前面的人。

那么直接倍增就做完了，设 $f_{x,a,b}$ 为从 $x$ 开始跳 $2^a$ 次能跳到在第 $b$ 场比赛排名最前面的人，倍增求出最少需要跳多少次才能让 $f_{x,a,b}$ 在第 $z$ 场比赛的排名不低于 $y$ 即可。

时间复杂度 $O(nm^2\log n+qm^2\log n)$。

---

## 作者：dAniel_lele (赞：5)

考虑倍增，设计 $f_{i,j,l,k}$ 表示从 $i$ 比赛中排名第 $k$ 的开始，吊打序列长度为 $2^l$，最多吊打到 $j$ 比赛中的第几名。

转移：$f_{i,p,k,l}=\min(f_{j,p,k-1,f_{i,j,k-1,l}})$。

查询的时候判一下 $1$，否则正常倍增判断即可。（$ans$ 至多为 $n$）

总复杂度 $O(nm^3\log n+qm^2\log n)$。

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
int a[6][100005],b[100005][6];
int f[6][6][21][100005];
signed main(){
	memset(f,1,sizeof(f));
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin>>a[i][j],b[a[i][j]][i]=j;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			int minv=n+1;
			for(int k=n;k>=1;k--){
				int rpos=a[i][k];
				minv=min(minv,b[rpos][j]);
				f[i][j][0][k]=minv;
			}
		}
	}
	for(int k=1;k<=20;k++){
		for(int l=1;l<=n;l++){
			for(int i=1;i<=m;i++){
				for(int j=1;j<=m;j++){
					for(int p=1;p<=m;p++){
						f[i][p][k][l]=min(f[i][p][k][l],f[j][p][k-1][f[i][j][k-1][l]]);
					}
				}
			}
		}
	}
	int q; cin>>q;
	while(q--){
		int x,y; cin>>x>>y;
		int ok=0;
		int p[m+1]; for(int i=1;i<=m;i++) p[i]=b[x][i],ok|=(b[x][i]<=b[y][i]);
		if(ok){
			cout<<1<<"\n";
			continue;
		}
		int num=0;
		for(int j=20;j>=0;j--){
			int np[m+1]; for(int i=1;i<=m;i++) np[i]=1e9;
			for(int i=1;i<=m;i++){
				for(int k=1;k<=m;k++){
					np[k]=min(np[k],f[i][k][j][p[i]]);
				}
			}
			int ok=0;
			for(int i=1;i<=m;i++) ok|=(np[i]<=b[y][i]);
			if(!ok){
				num+=(1<<j);
				for(int i=1;i<=m;i++) p[i]=np[i];
			}
		}
		if(num>1e6) cout<<-1<<"\n";
		else cout<<num+2<<"\n";
	}
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17921522.html)

[P9361 [ICPC2022 Xi'an R] Contests](https://www.luogu.com.cn/problem/P9361)

首先观察一下性质，每个 $l$ 在每场比赛里一定是对应着某个前缀。

发现题目要求的是最小的满足要求的 $l$，最暴力的大概是维护五个指针，每次答案 $+1$，然后尝试跳一步，什么时候某个前缀包含了 $x$ 当前的计数器就是答案。

考虑如何优化。这个东西显然满足单调性，首先想到的是二分答案或者整体二分之类的，但是发现不好 $\operatorname{chk}$。考虑倍增，维护每个人 $i$ 跳 $2^j$ 步在第 $k$ 场比赛的前缀 $f_{i,j,k}$。合并的式子：

$$
\begin{aligned}
f_{i,j,k}=\max_{x=1}^m\max_{y=1}^{f_{i,j-1,x}}f_{a_{x,j},i-1,k}
\end{aligned}
$$

发现 $y$ 的循环可以用前缀 $\max$ 优化掉。对于询问，从大到小枚举 $2^i$，尝试跳这些步，如果符合了条件就不跳，否则跳并且答案累加 $2^i$。最后 $ans+1$ 就是答案。

注意读入格式和判询问一开始就满足的情况。

```cpp
	int n,m,q,ans,flag,c[6],b[6],a[6][100010],f[100010][17][6],g[17][6][100010][6];
	inline void mian()
	{
		read(n,m);int x,y;
		for(int i=1;i<=m;++i)for(int j=1;j<=n;++j)read(a[i][j]),f[a[i][j]][0][i]=j;
		for(int from=1;from<=m;++from)
		{
			for(int to=1;to<=m;++to)
			{
				for(int k=1;k<=n;++k)
				g[0][from][k][to]=max(g[0][from][k-1][to],f[a[from][k]][0][to]);
			}
		}
		for(int i=1;i<=16;++i)
		{
			for(int j=1;j<=n;++j)
			{
				for(int to=1;to<=m;++to)
				{
					for(int from=1;from<=m;++from)
					Mmax(f[j][i][to],g[i-1][from][f[j][i-1][from]][to]);
				}
			}
			for(int from=1;from<=m;++from)
			{
				for(int to=1;to<=m;++to)
				{
					for(int k=1;k<=n;++k)
					g[i][from][k][to]=max(g[i][from][k-1][to],f[a[from][k]][i][to]);
				}
			}
		}
//		for(int i=0;i<=2;++i,puts(""))for(int k=1;k<=m;++k,puts(""))for(int j=1;j<=n;++j)write(f[j][i][k]);
		read(q);
		while(q--)
		{
			read(y,x),ans=1;
			for(int i=1;i<=m;++i)b[i]=f[x][0][i];
			for(int i=16;i>=0;--i)
			{
				memset(c,0,sizeof(c)),flag=1;
				for(int j=1;j<=m;++j)for(int to=1;to<=m;++to)Mmax(c[to],g[i][j][b[j]][to]);
				for(int j=1;j<=m;++j)if(c[j]>f[y][0][j])flag=0;
				if(flag)ans+=(1<<i),memcpy(b,c,sizeof(b));
			}
			flag=0;
			for(int j=1;j<=m;++j)for(int to=1;to<=m;++to)Mmax(c[to],g[0][j][b[j]][to]);
			for(int j=1;j<=m;++j)if(c[j]>f[y][0][j])flag=1;
			if(!flag){puts("-1");continue;}
			for(int j=1;j<=m;++j)if(b[j]>f[y][0][j])flag=0;
			write(ans+flag,'\n');
		}
	}
```

---

## 作者：Purslane (赞：2)

# Solution

首先，如果所有问题中 $x$ 都相同的话，那么这是一眼的后缀优化建图 + $01$ 最短路问题 ~~（回头给小朋友组模拟赛就这么干）~~。

但是一般非负边权图多源最短路在我能力范围内没有低于 $O(n^2 \log n)$ 的做法，显然无法通过本题。

考虑这题具有的特殊性质。一个点能转移到的，必定是某场比赛中被他 defeated 的人。我们下一步就是再从这个被 defeated 的人，转移到下一个又在某场比赛中被这个人打败的人。

如果我们知道了后面的这场比赛确切是那一场，那么就有一个很显然的贪心策略：我们在第一步找人的时候，要想办法是这个人在下一场比赛中排名尽可能考前。所以每一步事实上只有 $O(m)$ 个后继状态。

考虑使用倍增，求出每个点在 $2^k$ 步之后能使他在第 $j$ 场比赛中获得的最高排名是多少，依次合并转移即可。

复杂度 $O((n+q)m^2 \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q,m,nxt[MAXN][20][6],p[MAXN][6],rev[MAXN][6];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) ffor(j,1,n) cin>>p[j][i],rev[p[j][i]][i]=j;
	ffor(op,1,m) {
		ffor(i,1,n) nxt[i][0][op]=n+1;
		ffor(psl,1,m) {int lst=n+1;roff(i,n,1) lst=min(lst,rev[p[i][psl]][op]),nxt[p[i][psl]][0][op]=min(nxt[p[i][psl]][0][op],lst);}
	}
	ffor(len,1,19) {
		ffor(i,1,n) {
			ffor(op,1,m) nxt[i][len][op]=n+1;
			ffor(op,1,m) ffor(tmp,1,m) nxt[i][len][op]=min(nxt[i][len][op],nxt[p[nxt[i][len-1][tmp]][tmp]][len-1][op]);		
		}
	}
	cin>>q;
	ffor(i,1,q) {
		int x,y; cin>>x>>y; int flg=0;
		ffor(j,1,m) flg|=(rev[x][j]<rev[y][j]);
		if(flg) {cout<<1<<'\n';continue ;}
		int f[6],g[6],ans=0;
		ffor(j,1,m) f[j]=rev[x][j];
		roff(st,19,0) {
			int flg=0;
			ffor(j,1,m) g[j]=n+1;
			ffor(j,1,m) ffor(op,1,m) g[j]=min(g[j],nxt[p[f[op]][op]][st][j]);
			ffor(j,1,m) flg|=(g[j]<=rev[y][j]);
			if(!flg) {ans+=(1<<st);ffor(j,1,m) f[j]=g[j];}
		}
		if(ans==(1<<20)-1) cout<<-1<<'\n';
		else cout<<ans+2<<'\n';
	}
	return 0;
}
```

---

## 作者：jinhaoxian (赞：2)

显然可以转化为最短路模型。

为了方便处理，可以交换每组询问的 $(x,y)$，则 $u$ 向 $v$ 有连边当且仅当 $u$ 存在某一维大于 $v$ 的对应维度，即 $v$ 在 $a_i$ 的某个前缀。

直接用bfs/dfs最短路显然不可做，观察发现，除最后一步外，其余每一步必定走向能走到的**某一维度**最大的结点，否则显然不优。因此考虑倍增求出从每个结点出发，$2^k$ 步能走到的每一维度最大的结点，按 $k$ 从小到大可以在 $O(nm^2\log{n})$ 的复杂度预处理（具体而言，考虑第 $2^{k-1}$ 步的中转点，根据前述结论，中转点只有 $m$ 个不同选项。因此倍增求每一项仅需枚举 $m$ 步）。

每次询问特判 $x$ 向 $y$ 有连边（此时答案为 $1$），其余情况可以同样倍增完成。定义**好点**为向 $y$ 有连边的点，每次只需要按类似预处理的方法合并，并检验当前走完 $2^k$ 步后的 $m$ 个可能达到的终点是否包含好点，若不包含则从原状态向后推 $2^k$ 步，最终一定停在好点的前一位，于是加 $2$ 即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[105000][5],b[105000][5],maxt[105000][5][5],c[105000][17][5];
int f[5],g[5],ans,q,x,y;
bool chk(int x,int y) {
    for (int i=0;i<m;i++) if (b[x][i]>b[y][i]) return true;
    return false;
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++) {
        for (int j=1;j<=n;j++) {
            scanf("%d",&a[j][i]);
            b[a[j][i]][i]=j;
        }
    }
    for (int j=0;j<m;j++) {
        for (int i=1;i<=n;i++) {
            for (int k=0;k<m;k++) {
                maxt[i][j][k]=max(maxt[i-1][j][k],b[a[i][j]][k]);
            }
        }
    }
    for (int i=1;i<=n;i++) {
        for (int k=0;k<m;k++) {
            for (int t=0;t<m;t++) c[i][0][k]=max(c[i][0][k],maxt[b[i][t]-1][t][k]);
        }
    }
    for (int j=1;j<17;j++) {
        for (int i=1;i<=n;i++) {
            for (int k=0;k<m;k++) {
                c[i][j][k]=c[i][j-1][k];
                for (int t=0;t<m;t++) {
                    c[i][j][k]=max(c[i][j][k],c[a[c[i][j-1][t]][t]][j-1][k]);
                }
            }
        }
    }
    scanf("%d",&q);
    for (int T=0;T<q;T++) {
        scanf("%d%d",&x,&y);
        swap(x,y);
        if (chk(x,y)) {
            printf("1\n");
            continue;
        }
        int ans=0;
        for (int t=0;t<m;t++) f[t]=b[x][t];
        for (int j=16;j>=0;j--) {
            for (int t=0;t<m;t++) g[t]=0;
            for (int k=0;k<m;k++) {
                for (int t=0;t<m;t++) {
                    g[k]=max(g[k],c[a[f[t]][t]][j][k]);
                }
            }
            bool flg=0;
            for (int k=0;k<m;k++) {
                if (chk(a[g[k]][k],y)) {
                    flg=1;
                }
            }
            if (!flg) {
                ans+=(1<<j);
                for (int k=0;k<m;k++) f[k]=g[k];
            }
        }
        if (ans>n) printf("-1\n");
        else printf("%d\n",ans+2);
    }
    return 0;
}

```


---

## 作者：jun头吉吉 (赞：2)

## 题意

给你 $n,m$，有 $m$ 个长度为 $n$ 的排列 $a_1,\dots,a_m$，有 $q$ 组询问，每次给出 $x,y$，要求找到最小的 $l$ 使得存在一个长为 $l+1$ 的序列 $b_1,\dots,b_{l+1}$ 满足：

- $b_1=x,b_{l+1}=y$
- $\forall 1\le i\le l,\exists 1\le j\le m$ 使得 $b_i$ 在 $a_j$ 比 $b_{i+1}$ 先出现。

或者输出 $-1$ 表示不存在。

$n,q\le 10^5,m\le 5$。

## 题解

看成每次可以跳一步，$x$ 可以跳到 $y$ 当且仅当存在一个序列使得 $y$ 出现在 $x$ 后面，问最少跳几步。

然后我们发现每一次如果不能直接跳到终点，那么可以跳的选择只有 $m$ 种，因为我们每一步肯定是跳到某个序列中最前的能跳到的点。

然后我们就可以倍增了，预处理出从每个点出发，跳 $2^i$ 步在序列 $a_j$ 中最前的点，然后每次询问倍增就能得到答案了。

时间复杂度 $\mathcal O((n+q)m^2\log n)$。

## 代码
```cpp
struct vi{int arr[5];int&operator[](int x){return arr[x];}vi(){memset(arr,0x3f,sizeof arr);}};
const int N=1e5+10,M=5,K=17,inf=0x3f3f3f3f;
int n,m,q,a[M][N],b[M][N];vi f[K][N];
bool ok(vi now,int y){
	for(int i=0;i<m;i++)if(now[i]<=b[i][y])return 1;
	return 0;
}
vi trans(vi now,int p){
	vi res;
	for(int i=0;i<m;i++)for(int j=0;j<m;j++)
		chkmn(res[j],f[p][a[i][now[i]]][j]);
	return res;
}
signed main(){
	read(n,m);
	for(int i=0;i<m;i++)for(int j=1;j<=n;j++)read(a[i][j]),b[i][a[i][j]]=j;
	for(int i=0;i<m;i++)for(int j=0;j<m;j++)
		for(int mn=0x3f3f3f3f,k=n;k;k--)chkmn(mn,b[i][a[j][k]]),chkmn(f[0][a[j][k]][i],mn);
	for(int i=1;i<K;i++)for(int j=1;j<=n;j++)f[i][j]=trans(f[i-1][j],i-1);
	read(q);while(q--){
		int x,y;read(x,y);
		int cnt=0;vi now;for(int i=0;i<m;i++)now[i]=b[i][x];
		for(int i=K-1;~i;i--)if(!ok(trans(now,i),y))
			cnt+=1<<i,now=trans(now,i);
		if(!ok(trans(now,0),y))writeln(-1);
		else{
			if(!ok(now,y))cnt++,now=trans(now,0);
			int t=1;
			for(int i=0;i<m;i++)if(now[i]==b[i][y])t=0;
			writeln(cnt+t);
		}
	}
}
```

---

## 作者：lzdll (赞：1)

梦熊模拟赛考到了这道题，让我用 dijkstra 和针对随机数据的玄学判断骗到了 $50$ 分，然后老师讲完后发现这题并不难。这篇题解就算是在@[daniEl_lElE](https://www.luogu.com.cn/user/116664) 的[这篇题解](https://www.luogu.com.cn/article/4fjrunfw)的基础上进行补充。

## 做法

首先肯定不能直接建图了，我们看看题目有没有别的性质。我们可以看这张图片。

![](https://cdn.luogu.com.cn/upload/image_hosting/jlf26u95.png)

假设现在你要从 $x$ 走到 $y$，然后假设你现在要从第二行跳到第一行，那么你肯定要尽量往前跳，因为前面的点的下一步决策能够完全包含后面的点的下一步决策。也就是说我们只会从 $x$ 跳到 $m$ 场比赛中能到的最靠前的点。

## 倍增优化
但是一个一个跳非常慢，所以我们考虑倍增优化，使用 $f[i][j][l][k]$ 表示从第 $i$ 场比赛的第 $k$ 个人走 $2^l$ 步能走到的第 $j$ 场比赛最靠前的点是第几个。

我们只需要先把 $f[i][j][0][k]$ 全部求出来，然后再求出所有的 $f[i][j][0][l]$。对于每一组询问，我们直接看每一位需不需要即可。

这样说可能比较抽象。我们结合代码具体来看。首先，我们要求出 $f[i][j][0][k]$。


## 倍增预处理
这一部分比较简单，直接枚举 $i$ 和 $j$，跳一步就是 $k$ 后面所有点在其他 $j$ 中的最小位置，所以 $k$ 从后往前枚举，这样前面的 $k$ 就能包含后面的 $k$ 的所有决策了。

解释一下变量名，$a[k][i]$ 表示第 $k$ 场比赛的第 $i$ 个是谁，$b[k][ai]$ 表示第 $k$ 场中的 $ai$ 这个人是第几名。
```cpp
for(int k=1; k<=m; ++k) {
	for(int i=1; i<=n; ++i) {
		R(a[k][i]);
		b[k][a[k][i]]=i;
	}
}
memset(f,0x3f,sizeof f);
for(int i=1; i<=m; ++i) {
	for(int j=1; j<=m; ++j) {
		int nw=0x3f3f3f3f;
		for(int k=n; k>=1; --k) {
			nw=min(nw,b[j][a[i][k]]);
			f[i][j][0][k]=nw;
		}
	}
}
```

预处理完 $f[i][j][0][k]$，我们就可以算 $f[i][j][l][k]$ 了。

## 倍增

如果我们要算 $f[i][j][l][k]$，也就是从第 $i$ 场的第 $k$ 个人跳 $2^l$ 步能到达的第 $j$ 场的最靠前的位置。我们需要先通过 $2^{l-1}$ 步从 $i$ 跳到一个别的地方，然后在通过 $2^{l-1}$ 步从这个地方跳到 $j$。

```cpp
for(int l=1; l<=len; ++l) {
	for(int i=1; i<=m; ++i) {
		for(int p=1; p<=m; ++p) {
			for(int j=1; j<=m; ++j) {
				for(int k=1; k<=n; ++k) {
					f[i][j][l][k]=min(f[i][j][l][k],f[p][j][l-1][f[i][p][l-1][k]]);
				}
			}
		}
	}
}
```
## 处理询问

首先我们要判一步就能到的情况，只要 $x$ 在某一场的排名在 $y$ 之前就能一步跳到。
```cpp
while(q--) {
	int R(x),R(y);
	int flag=0,ans=0;
	for(int i=1; i<=m; ++i) {
		if(b[i][x]<b[i][y]) {
			flag=1;
			break;
		}
	}
	if(flag) {
		cout<<"1\n";
		continue;
	}
}
```

但是一步可能跳不到，这时我们要最小化步数。我们二进制枚举 $l$，然后判断跳 $2^l$ 能不能直接到，如果到不了就说明答案的二进制中从右往左第 $l+1$ 位一定为 $1$，答案加上 $2^l$。如果到不了我们就不管，所以最后一定还差一步跳到 $y$。我们最后再把 $ans$ 加上 $x$ 和将要跳到 $y$ 的那个点，答案就是 $ans+2$。

具体是怎么跳的呢，我们设 $p[i]$ 表示第 $i$ 场比赛之前能跳到的最前的，$np[i]$ 表示第 $i$ 场比赛能跳到的最前的。初始化 $p[i]=b[i][x]$，每一次使用 $f[i][j][l][p[i]]$ 更新 $np[j]$，表示从第 $i$ 场再跳 $2^l$ 次跳到第 $j$ 场最靠前的名次。最后如果需要这 $2^l$ 步，我们再使用 $np[i]$ 更新 $p[i]$ 即可。

```cpp
R(q);
while(q--) {
	int R(x),R(y);
	int flag=0,ans=0;
	for(int i=1; i<=m; ++i) {
		if(b[i][x]<b[i][y]) {
			flag=1;
			break;
		}
	}
	if(flag) {
		cout<<"1\n";
		continue;
	}
	for(int i=1; i<=m; ++i) {
		p[i]=b[i][x];
	}
	for(int l=len; l>=0; --l) {
		flag=0;
		for(int i=1;i<=m;++i){
			np[i]=0x3f3f3f3f;
		}
		for(int i=1; i<=m; ++i) {
			for(int j=1; j<=m; ++j) {
				np[j]=min(np[j],f[i][j][l][p[i]]);
			}
		}
		for(int i=1; i<=m; ++i) {
			if(np[i]<=b[i][y]) {
				flag=1;
			}
		}
		if(!flag) {
			ans+=(1<<l);
			for(int i=1; i<=m; ++i) {
				p[i]=np[i];
			}
		}
	}
		
	if(ans>n){
		cout<<"-1\n";
	}else{
		cout<<ans+2<<"\n";
	}
}
```

## 需要注意的地方

由于内存的连续性，我们把最大的放在最后一维可以减小常数，如果你把$f[i][j][l][k]$ 中 $k$ 这一维放在 $l$ 的位置，就会被卡常。

## 完整代码


完整代码太长了，我就放在[这里](https://www.luogu.me/paste/0kjpevks#)了。

---

## 作者：_Weslie_ (赞：1)

MX 盖世计划青岛 C 班 Day 8 T3 原题。

MX 也是相当无敌。四个题黄蓝紫黑。除了 T1 其他全部在洛谷上有原。

我不反对出原题。这个题也相当不错。

## Solution P9361

### 一次转移状态：贪心

赛时想了个拆点然后跑最短路的做法。显然对于这个题，是过不去的。这个题是全源最短路，最快也只能达到 $\operatorname{O}(n^2\log n)$。我们需要寻找更优的解法。

$m$ 很小。

假如说，我们现在在第 $i$ 场比赛的 $x$，想要到达第 $j$ 场比赛的 $y$。那么我们该如何选择呢？

假如我们要从下面第 $2$ 场比赛的 $7$ 到第 $1$ 场比赛的一个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/qbwuedhj.png)

如果目的地是 $\{4,8,3,5\}$ 中一个，那么答案就是 $1$。

否则，就要考虑中转。

如果我们在比赛 $2$ 中选择 $4$ 作为中转点，可到达 $1$ 的集合有 $\{1,5,7,6,8\}$；选择 $8$ 则是哪也去不了；选择 $3$ 是所有的都能去；选择 $5$ 是可以去 $\{7,6,8\}$。

设 $S_i$ 为在这一场比赛中选择 $i$ 作为中转节点的下一场比赛的可选点集合。

那么可以发现 $S_8\subseteq S_5\subseteq S_4\subseteq S_3$。

那么我们为什么要选择 $4$ 甚至 $8$ 这些可选状态少的点，而放弃 $3$ 这个可选状态多的点呢？选择 $3$ 一定不劣于选择其他状态。

至此，我们得出了一个贪心：先枚举当前比赛 $i$ 和中转比赛 $j$，那么从后往前枚举，记录后缀新比赛中最靠前的排名位置，然后记录下来。

### 多次转移：倍增

显然 $q$ 次询问，每次询问暴力是 $\operatorname{O}(nq)$ 的，我们接受不了。

考虑倍增。

设 $nxt_{i,j,k}$ 表示从 $i$ 位置出发，经过 $j$ 步，到达的人在第 $k$ 次比赛中的最小排名。

那么转移非常简单：设这次比赛为 $j$，经过 $len$ 步。上一次比赛为 $k$。

那么 $nxt_{i,len,j}=\min(nxt_{i,len-1,k},nxt_{i,len,j})$。

对于询问，我们从点 $u$ 开始，记录 $lst$ 状态和 $now$ 新状态。每一次，我们先计算更新之后的状态 $now$。如果更新之后仍然无法满足条件，那么就把 $lst$ 更新为 $now$。

如果你发现答案到了最大值仍然无法满足条件，输出 $-1$ 即可。

否则，输出 $ans+2$，因为我们还需要计算开头和结尾。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,q,m;
int nxt[N][20][6],a[N][6],pl[N][6];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[j][i]);
			pl[a[j][i]][i]=j;
		} 
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			nxt[j][0][i]=n+1;
		}
		for(int j=1;j<=m;j++){
			int lst=n+1;
			for(int k=n;k>=1;k--){
				lst=min(lst,pl[a[k][j]][i]);
				nxt[a[k][j]][0][i]=min(nxt[a[k][j]][0][i],lst);
			}
		}
	} 
	for(int len=1;len<=19;len++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				nxt[i][len][j]=n+1;
			}
			for(int j=1;j<=m;j++){
				for(int k=1;k<=m;k++){
					nxt[i][len][j]=min(nxt[i][len][j],nxt[a[nxt[i][len-1][k]][k]][len-1][j]);
				}
			}
		}
	}
	scanf("%d",&q);
	for(int u,v;q;q--){
		scanf("%d%d",&u,&v);
		int fl=0;
		for(int j=1;j<=m;j++){
			if(pl[u][j]<pl[v][j]){
				fl=1;
				break;
			}
		}
		if(fl){
			printf("1\n");
			continue;
		}
		int lst[6],now[6],ans=0;
		for(int j=1;j<=m;j++){
			lst[j]=pl[u][j];
		}
		for(int st=19;st>=0;st--){
			fl=0;
			for(int j=1;j<=m;j++){
				now[j]=n+1;
			}
			for(int j=1;j<=m;j++){
				for(int k=1;k<=m;k++){
					now[j]=min(now[j],nxt[a[lst[k]][k]][st][j]);
				}
			}
			for(int j=1;j<=m;j++){
				if(now[j]<=pl[v][j]){
					fl=1;
					break;
				}
			}
			if(!fl){
				ans=ans+(1<<st);
				for(int j=1;j<=m;j++)lst[j]=now[j];
			}
		}
		if(ans==1048575)printf("-1\n");
		else printf("%d\n",ans+2);
	}
}
```

---

## 作者：RizzzzziR (赞：0)

tag: 倍增，按位处理

## 题目

$n$ 个选手进行了 $m$ 场比赛，现有每场比赛的排名

若某选手在 **任意一场** 比赛中名次高于另一位选手，则称该选手强于另一位选手（

若找到一条选手序列，以 $x$ 开头，$y$ 结尾，长为 $L+1$，每个选手都比**相邻的下一个选手**强，则称 $x$“L-强于”$y$

给出 $q$ 个询问 $x,y$，求最小的 $L$ 使 $x$ “$L$-强于” $y$。如果做不到，输出 $-1$

$2\le n\le 10^5,1\le m\le 5,q\le 10^5,x\ne y$

## 题解

$m$ 非常非常小，肯定是这题的核心

把从一个点出发的“强于”关系类比成染色  
考虑一个点的“强于”路径，先染各比赛中低名次的点。然后通过这个低位点在其他比赛中的更高名次（若有的话），染掉一开始未染的点。然后再找新染的点的高位，再染色……发现倍增可以快速解决这个问题（注：rk1 是高名次，rkn 是低名次）

设计一个状态 `f[p][t][i]` 表示从 $i$ 开始，经过 $2^p$ 次染色，在比赛 $t$ 中的**染色范围**，记录其名次最高的选手编号。

求答案时从高位向低位枚举每一位，尝试经过 $2^b$ 次染色后能染到哪。类似求 LCA，能染到算染过头，染不到就转移 $sum=sum+2^b$，最后返回 $sum+1$。  

答案范围 $[1,n-1]$，理由是答案更大时$Len=ans+1>n$，有重复点中间可以删去

预处理状态数 $O(nm\log n)$，转移复杂度可做到 $O(m)$；求解二分复杂度 $O(\log n)$，单次查询复杂度 $O(m^2)$。总复杂度 $O(nm^2\log n+qm^2\log n)$

![](https://cdn.luogu.com.cn/upload/image_hosting/1zw2ulxw.png)  
附图例：`f[2][t][x]=w`及其转移：`f[1][tt][x]=y`&`suc[t][tt][y]=f[1][t][z]=w`
### 实现细节

1. 转移方程 `f[p][t][i]=with min rk_{forall mid}: f[p-1][t][from f[p-1][mid][i] to contest[mid].end ]`  
2. 后缀预处理出一个 `suc[t][s][i]` 表示比赛 $s$ 从选手 $i$ 开始的所有选手经过上一轮染色（$2^{p-1}$ 次）后在比赛 $t$ 中能覆盖范围的最大名次。  
3. 实现时分清“选手编号”和“比赛名次”，按道理怎么存都行，个人为了便于思考全程用的选手编号  
4. 按位求答案时，第一次转移用`f`，因为固定由 $x$ 开始。之后转移用 `suc`，因为已经覆盖了，从谁开始都行。也有可能是我实现不好所以要区分  
5. 数组存储时允许选手重复选即 $x\rarr x\rarr x\rarr \dots$，这么做是为了单调性：$ans$ 次可覆盖，$ans+k$ 次也可覆盖。但一定会求出正确的 $ans$，因为是按最小 $ans$ 累积的 $sum$，按位处理时实质上是在做类似 `for(b) if(sum+2^b<ans) sum+=2^b;return sum+1；`的操作  

另：看提交记录时空占用都比较劣，应该还有优化空间  

### code
码风抽象
```cpp
/*  哎呀，能输出已经很厉害啦*/
#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstring>
#define Rep(i,a,b) for(int i=(a);i<=(b);++i)

using namespace std;
inline int mn(int a,int b){return a<b?a:b;}
const int mN=100005,mM=6,mLG=17;
int n,m;
int list[mM][mN],rk[mM][mN];
int f[mLG][mM][mN];//f[mLG][mM][mM][mN];
int suc[mM][mM][mN];
int fff[mLG][mM][mM][mN];
int lgt[mN];

void buildf(){
   //build lgt[]
   lgt[0]=-1;
   Rep(i,1,n) lgt[i]=lgt[i>>1]+1;
    //build f[0][][]
    Rep(t,1,m)Rep(i,1,n)
    	f[0][t][i]=i;

    //build f[p][][]
#define fp f[p]
#define fq f[p-1]
	for(int p=1,pw=2;pw<=n;++p,pw<<=1){
		Rep(t,1,m){
			Rep(s,1,m){
                int *Suc=suc[t][s],*List=list[s],*Rk=rk[t];
				for(int k=n;k;--k)
					if(k==n||Rk[ fq[t][List[k]] ]<Rk[ Suc[List[k+1]] ])
						Suc[List[k]]=fq[t][List[k]];
					else
						Suc[List[k]]=Suc[List[k+1]];
            }
		}
        memcpy(fff[p-1],suc,sizeof(suc));
		Rep(t,1,m){
			Rep(i,1,n){
				int &F=fp[t][i],*Rk=rk[t];
				F=fq[t][i];
				Rep(s,1,m){
					if(Rk[ suc[t][s][fq[s][i]] ]<Rk[F])
						F=suc[t][s][fq[s][i]];
				}
			}
		}
	}
    int p=lgt[n],pw=1<<p;
	Rep(t,1,m){
		Rep(s,1,m){
			int *Suc=suc[t][s],*List=list[s],*Rk=rk[t];
			for(int k=n;k;--k)
				if(k==n||Rk[ fp[t][List[k]] ]<Rk[ Suc[List[k+1]] ])
					Suc[List[k]]=fp[t][List[k]];
				else
					Suc[List[k]]=Suc[List[k+1]];
        }
	}
    memcpy(fff[p],suc,sizeof(suc));
#undef fp
#undef fq

}
int BS(int x,int y){
	
    int sum=0;//ans=1~n-1(len=2~n)
    int dt,maxbit=lgt[n];
    int g[2][mM];
    Rep(i,1,m) g[0][i]=x;
    while(~maxbit){
        dt=1<<maxbit;

        int *g0=g[0],*g1=g[1],gnew;
        Rep(i,1,m) g1[i]=g0[i];
        if(sum==0){
            Rep(j,1,m){
                g1[j]=f[maxbit][j][x];
            }
        }else
            Rep(j,1,m){
                int *Rk=rk[j];
                Rep(i,1,m){
    				if(Rk[ gnew=fff[maxbit][j][i][g0[i]] ]<Rk[g1[j]])
                    	g1[j]=gnew;
                }
            }
        bool chk=0;
        Rep(i,1,m)
            chk|=(rk[i][g1[i]]<rk[i][y]);
        
        if(!chk){
        	sum|=dt;
            memcpy(g0,g1,sizeof(int)*(m+1));//not sizeof(g1),g1 is a pointer
		}
        if(sum>=n-1) return -1;//!(sum+1<n)
        maxbit--;
    }
    return sum+1<n?sum+1:-1;
}

int main()
{
    scanf("%d%d",&n,&m);
    Rep(i,1,m){
        int *Ls=list[i],*Rk=rk[i];
        Rep(j,1,n){
            scanf("%d",&Ls[j]);
            Rk[Ls[j]]=j;
        }
    }
    buildf();
    int q,x,y;
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&x,&y);
        assert(x!=y);
        printf("%d\n",BS(x,y));
    }
    return 0;
}
```

#### 碎碎念
初见是一周前和队友见面随了几道区域赛的题，当场理解错题意口嗨了一个 not even wrong 的或最短路。过了几天重看重做，一开始是要感叹一道比赛题目做的比比赛时长还要久的，然后发现又假又改又假又改……主要就是上面“实现细节”部分的东西，到处都在假~~程序设计能力惊人~~，断断续续改了一周多

~~这下不用考虑比赛时长了~~

---

