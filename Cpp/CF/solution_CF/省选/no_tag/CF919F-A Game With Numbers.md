# A Game With Numbers

## 题目描述

Imagine that Alice is playing a card game with her friend Bob. They both have exactly $ 8 $ cards and there is an integer on each card, ranging from $ 0 $ to $ 4 $ . In each round, Alice or Bob in turns choose two cards from different players, let them be $ a $ and $ b $ , where $ a $ is the number on the player's card, and $ b $ is the number on the opponent's card. It is necessary that $ a·b≠0 $ . Then they calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919F/9c88cb7ed8bc9c1a29df5a95052841fd640dfb78.png) and replace the number $ a $ with $ c $ . The player who ends up with numbers on all $ 8 $ cards being $ 0 $ , wins.

Now Alice wants to know who wins in some situations. She will give you her cards' numbers, Bob's cards' numbers and the person playing the first round. Your task is to determine who wins if both of them choose the best operation in their rounds.

## 说明/提示

In the first situation, Alice has all her numbers $ 0 $ . So she wins immediately.

In the second situation, Bob picks the numbers $ 4 $ and $ 1 $ . Because we have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919F/a0f56d4347b8b4f2f6d1a078cdc9165a9cd187d1.png), Bob wins after this operation.

In the third situation, Alice picks the numbers $ 1 $ and $ 4 $ . She wins after this operation.

In the fourth situation, we can prove that it falls into a loop.

## 样例 #1

### 输入

```
4
1
0 0 0 0 0 0 0 0
1 2 3 4 1 2 3 4
1
0 0 0 1 0 0 0 0
0 0 0 0 4 0 0 0
0
1 0 0 0 0 0 0 0
0 0 0 4 0 0 2 0
1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
```

### 输出

```
Alice
Bob
Alice
Deal
```

# 题解

## 作者：老莽莽穿一切 (赞：6)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16278538.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF919F)

[**CF link**](https://codeforces.com/problemset/problem/919/F)

这里带来一个跑得很快而且写起来也相对简单的做法。

首先考虑这种题一看就是博弈论，主要就是一个性质——能走到必败态的都是必胜态，**只**能走到必胜态的才是必败态。

那么就很显然了，从终止状态反向推，先看看状态数，一个人的手牌只有八张五种，所以最多只有 $495$ 种状态，那么两个人的手牌加起来也不过只有约 $2.5\times10^5$ 种状态。

考虑先将这些状态编上号，建立双射，方便之后的转移，然后考虑做转移，设 $f_{i,j}$ 表示先手的状态编号为 $i$，后手状态编号为 $j$ 的态势。

考虑怎么转移，首先初始状态，假设手牌全是 $0$ 的状态编号为 $0$，则 $f_{0,i}=1$，$f_{i,0}=0$，且 $f_{i,0}$ 可以作为状态转移别人，而 $f_{0,i}$ 不行，因为我们是反向转移，所以当前的先手如果已经赢了的话，上一步后手就根本无法操作。

现在考虑如何转移，一个点肯定是倒推上一个状态，所以肯定是**当前**后手的一个数减去当前先手的一个**非零**数得到上个状态的原数，如果该状态是必败态，则转移的就是必胜态，如果该状态是必胜态，则转移到必败态，但是不是一定转移，而是只有确定这个点**正向**能转移到的点都是必胜态，这个点才是必败态。

一个点能转移多少点呢？考虑手里任意一**种**非零牌跟对手的每**种**非零牌都可以匹配进行操作，所以就可以快速得到转移种类，注意这里一模一样的牌就算有多张，匹配转移也只能算一种。

最后查询就直接调用查询就好了，[代码](https://codeforces.com/contest/919/submission/157388194)比较简单。

---

## 作者：NaVi_Awson (赞：5)

博客也有详解，欢迎来踩： [菜鸡NaVi_Awson的博客](http://www.cnblogs.com/NaVi-Awson/p/8405966.html)

## Description

[题库链接](http://codeforces.com/problemset/problem/919/F)

两个人 Van♂ 游戏，每人手上各有 $8$ 张牌，牌上数字均为 $[0,4]$ 之间的数。每个人在自己的回合选自己手牌中数字不为 $0$ 的一张与对方手牌中不为 $0$ 的一张。数字相加对 $5$ 取模，赋给自己当前选中的这张牌。 $T$ 组询问，给出先手，问谁能胜。

$1\leq T\leq 100000$

## Solution

首先注意到卡牌顺序是没有影响的，我们可以按数字大小排序。这时由可重复的组合得每个人可能的方案只有 $\binom{8+5-1}{8}=495$ 种。所以两个人不同的状态共 $495^2=245025$ 种。

我们可以将每个状态抽象成节点，节点存下两个状态，改轮的操作者的状态和对方的状态。用有向边链接操作前的和操作后的情况。我们可以用 $O\left(8^2\cdot\binom{8+5-1}{8}^2\right)$ 来枚举所有状态建边。对于每个节点我们考虑其连向的所有节点：

1. 若存在一个连向的节点的状态能够保证当前的后手必败，那么改轮的操作者必胜；
2. 若其连向的所有节点都是必胜，该节点必败；
3. 其余的情况，则是平局。

我们可以通过反向建边 $topsort$ 来实现。 $O(1)$ 回答询问。

## Code

```cpp
//It is made by Awson on 2018.2.2
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N = 400000;
void read(int &x) {
	char ch; bool flag = 0;
	for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
	for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
	x *= 1-2*flag;
}
void print(int x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(int x) {if (x < 0) putchar('-'); print(Abs(x)); }

int S[N+5], C[N+5], cnt;
struct hs {
	int a[8];
	hs() {memset(a, 0, sizeof(a)); }
	hs(int x) {for (int i = 7; i >= 0; i--) a[i] = x%5, x /= 5; }
	hs(int *_a) {for (int i = 0; i < 8; i++) a[i] = _a[i]; }
	void rd() {for (int i = 0; i < 8; i++) read(a[i]); }
	void st() {sort(a, a+8); }
	int hash() {
		int ans = 0;
		for (int i = 0; i < 8; i++) ans = ans*5+a[i];
		return ans;
	}
};
struct tt {int to, next; }edge[(N<<6)+5];
int path[N+5], top, in[N+5], ans[N+5];

void add(int u, int v) {++in[v]; edge[++top].to = v, edge[top].next = path[u]; path[u] = top; }
int no(int a, int b) {return (a-1)*cnt+b-1; }
void dfs(int cen, int last, int h) {
	if (cen == 8) {S[++cnt] = h, C[h] = cnt; return; }
	for (int i = last; i < 5; i++) dfs(cen+1, i, h*5+i);
}
void prework() {
	dfs(0, 0, 0);
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= cnt; j++) {
			hs a(S[i]), b(S[j]);
			for (int p = 0; p < 8; p++) if (a.a[p])
				for (int q = 0; q < 8; q++) if (b.a[q]) {
					hs c(a.a);
					c.a[p] = (a.a[p]+b.a[q])%5;
					c.st(); int tmp = C[c.hash()];
					add(no(j, tmp), no(i, j));
				}
		}
	queue<int>Q; while (!Q.empty()) Q.pop();
	for (int i = 2; i <= cnt; i++) ans[no(i, 1)] = 1, Q.push(no(i, 1));
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (int i = path[u]; i; i = edge[i].next) if (!ans[edge[i].to]) {
			if (ans[u] == 1) {ans[edge[i].to] = -1; Q.push(edge[i].to); }
			else if (--in[edge[i].to] == 0) {
				Q.push(edge[i].to); ans[edge[i].to] = 1;
			}
		}
	}
}
void work() {
	prework();
	int t, f; hs a, b; read(t);
	while (t--) {
		read(f); a.rd(), b.rd(); a.st(); b.st();
		if (f) swap(a, b);
		int as = ans[no(C[a.hash()], C[b.hash()])];
		if (as == 0) puts("Deal");
		else if (as == -1 && f || as == 1 && !f) puts("Bob");
		else puts("Alice");
	}
}
int main() {
	work();
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：3)

> **能转移到必败态的状态就是必胜态，只能转移到必胜态的状态就是必败态。**

首先我们可以把状态压缩，发现状态最多只有 495 种。

然后如果一方是全 0 ，那么这个状态对应的答案就可以很容易得出

然后反着思考，从上面说的这些已知状态逆向搜索

DFS(m1,m2,k) 表示 A 是 m1 状态，B 是 m2 状态，k=0/1 表示当前是 A/B 操作的回合

每一个 m1,m2,k 只需要被搜索一次，所以可以用一个 vis 数组记忆一下有没有搜过

注意，我们是从结果推到初始状态，所以这里的转移也是倒过来转移

如果当前状态是必败态，那么转移到下一个状态（其实是上一个）就一定是必胜态，因为 **能转移到必败态的状态就是必胜态**

如果当前状态是必胜态，那么就把能转移到的状态的计数器自增，如果某个状态的计数器到达了能转移到他的状态的个数，那么那个状态就成为了必败态，因为 **只能转移到必胜态的状态就是必败态**

如果当前状态不是必胜也不是必败，那就别转移给其他状态，因为不确定

到最后还是不确定的起始状态那就是 `Deal`

然后把所有状态都预处理好，查询直接输出即可

至于记搜的复杂度... $\mathcal O(\text{能过})$

$\texttt{Code}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define mem(x,y) memset(x,y,sizeof x)
#define ln puts("")
using namespace std;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int idx[9][9][9][9],idxcnt;
int rev[500][5];
bool win[500][500][2],vis[500][500][2];
int cnt[500][500][2],Sum[500];
inline void dfs(int m[2],int k)
{
	for(int i=0;i<=4;++i)
		for(int j=1;j<=4;++j)
			if(rev[m[k^1]][i]&&rev[m[k]][j])
			{
				reg int c=(i-j+5)%5;
				if(!c)
					continue;
				reg int t[5];memcpy(t,rev[m[k^1]],sizeof t);
				--t[i],++t[c];
				reg int nxtm[2];nxtm[0]=m[0],nxtm[1]=m[1];
				nxtm[k^1]=idx[t[0]][t[1]][t[2]][t[3]];
				if(vis[nxtm[0]][nxtm[1]][k^1])
					continue;
				if(!win[m[0]][m[1]][k])
					win[nxtm[0]][nxtm[1]][k^1]=vis[nxtm[0]][nxtm[1]][k^1]=true,
					dfs(nxtm,k^1);
				else
				{
					if(++cnt[nxtm[0]][nxtm[1]][k^1]==Sum[nxtm[0]]*Sum[nxtm[1]])
						vis[nxtm[0]][nxtm[1]][k^1]=true,dfs(nxtm,k^1);
				}
			}
	return;
}
inline void work()
{
	reg int m[2],k,x;
	read(k);
	int t[5];mem(t,0);
	for(int i=1;i<=8;++i)
		read(x),++t[x];
	m[0]=idx[t[0]][t[1]][t[2]][t[3]];
	mem(t,0);
	for(int i=1;i<=8;++i)
		read(x),++t[x];
	m[1]=idx[t[0]][t[1]][t[2]][t[3]];
	puts(vis[m[0]][m[1]][k]?((win[m[0]][m[1]][k]^k)?"Alice":"Bob"):"Deal");
	return;
}
signed main(void)
{
	for(int i=0;i<=8;++i)
		for(int j=0;i+j<=8;++j)
			for(int k=0;i+j+k<=8;++k)
				for(int l=0;i+j+k+l<=8;++l)
					idx[i][j][k][l]=++idxcnt,
					rev[idxcnt][0]=i,rev[idxcnt][1]=j,rev[idxcnt][2]=k,
					rev[idxcnt][3]=l,rev[idxcnt][4]=8-i-j-k-l,
					Sum[idxcnt]=(!!j)+(!!k)+(!!l)+(!!rev[idxcnt][4]);
	for(int i=1;i<idxcnt;++i)
	{
		vis[idxcnt][i][0]=vis[i][idxcnt][0]=
		vis[idxcnt][i][1]=vis[i][idxcnt][1]=true;
		win[idxcnt][i][0]=win[i][idxcnt][1]=true;
		int m[2];
		m[0]=idxcnt,m[1]=i,dfs(m,0),dfs(m,1);
		m[0]=i,m[1]=idxcnt,dfs(m,0),dfs(m,1);
	}
	int t;read(t);
	while(t--)
		work();
	return 0;
}
```


---

## 作者：aaaaaaaawsl (赞：2)

本文较于其他题解会重点讲述关于状态的定义，状态的后继状态个数和搜索时的转移。

------------

### 前置

关于博弈论的入门可以看我的[学习笔记](https://www.luogu.com.cn/blog/aaaaaaaawsl/bo-yi-lun-xue-xi-bi-ji)。这边仅给出必要的定义：

把操作看成状态的转移，由题目的描述得，**目前**必败态即为不能转移到其他状态的状态。

如果一个状态他能转移到的状态集里有必败态（他可以主观决定他操作完后对手的状态），那么为了最优，他一定会选择转移到必败态，那么当前状态即为必胜态。

继续考虑必败态，加上转移这个操作，除了不能转移到其他状态，如果他能转移到的状态集里都是必胜态，那么他无论怎么走会使对手到达必胜态，那么他本身是必败态。

一个更严谨的定义：

1.无法进行任何移动的局面（也就是 $terminal$ $position$）是 $P-position$；

2.可以移动到 $P-position$ 的局面是 $N-position$；

3.所有移动都导致 $N-position$ 的局面是 $P-position$。

为了之后的明确的转移，下面的胜负是先手操作的人的胜负，对于两个人的状态，**初始时**设胜态为**先手**人的卡全为 $0$ 的状态，对应的，输态就是后手人的卡全为 $0$ 的状态。

之所以说是初始时的胜负态，因为后续搜索中还需要更新其他点的状态。

------

### 状态方面的分析

1.状态的定义和个数。

两个人的手牌一共有 $8$ 张，每张 $5$ 种数字，考虑到手牌的顺序对博弈是没有影响的，于是单论一人，所有不同的状态数应该是八个小球分配五个颜色，可以不分配的方案数。考虑隔板法，即为 $4$ 个板分隔 $8$ 个球，每两个板之间代表一个颜色。于是便变成了 $12$ 个位置选 $4$ 个放板，其他的放球。方案数为 ${8 + 4 \choose 4} = 495$。

程序中，设 $mp_{i,j,k,w}$ 为一个状态的映射，``mp[c1][c2][c3][c4] = idc`` 表示一个状态有 ``c1`` 个 $1$，``c2`` 个 $2$，``c3`` 个 $3$，``c4``个 $4$，此状态的映射值为 ``idc``。

2.如何枚举这些状态。

枚举手牌中含有的 $1,2,3,4$，的个数。用一个结构体建立双射。

3.状态的后继状态有哪些?

考虑两个状态 $c1,c2,c3,c4$，$C1,C2,C3,C4$，由于数字是由 $0$ 到 $4$，在 $\bmod 5$ 下，$1$ 到 $4$ 的某一个数，加上 $1$ 到 $4$ 的任意一个数的值都不一样，所以后继状态数为 $x \times y$，$x,y$ 为两个状态有几个不同的非零的数。

4.如何搜索更新其他状态。

对于当前的两个状态，因为我们可以得出最后的胜态和负态，所以采取倒推。

上一句的先手选择了对方的牌，变成了现在的后手，所以我们枚举选了现在先手的哪张牌，枚举变成了后手的哪张牌，就可以计算出之前后手的牌。

如果当前是输态，那就更新所有后继状态为胜态，如果当前是胜态，就给所有后继状态的计数数组加一，如果某个状态的计数数组的值等于他的后继状态数，那么说明他的所有后继状态都是胜态，他是输态，继续转移即可。

记得带着两个状态一起判断，因为某个局面涉及两个状态。

-------

### 代码

~~卡卡常拿了个最优解~~

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

struct node{
	int c[5];
}pm[500];

int idc, T, f;
int mp[9][9][9][9];
int cnt[500][500];
int st[500][500];
int C[5][5];
int U[500];

namespace FastIO{
	char buf[1 << 9], buf2[1 << 18], a[18], *p1 = buf, *p2 = buf;
	void read(){}
	inline int getc(){
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 9, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	template <typename T>
	inline void read(T &x){
		x = 0;
		char ch = getc();
		while(!isdigit(ch)){
			if(ch == '-') f = 1;
			ch = getc();
		}
		while(isdigit(ch)){
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getc();
		}
	}
}
#define read FastIO::read

int uu;
void init(){
	for(register int c1 = 0; c1 <= 8; ++ c1){
		for(register int c2 = 0; c2 + c1 <= 8; ++ c2){
			for(register int c3 = 0; c3 + c1 + c2 <= 8; ++ c3){
				for(register int c4 = 0; c4 + c3 + c1 + c2 <= 8; ++ c4){
					if(c1 + c2 + c3 + c4 == 0) continue;
					mp[c1][c2][c3][c4] = ++ idc;
					pm[idc].c[0] = 8 - c1 - c2 - c3 - c4;
					pm[idc].c[1] = c1; pm[idc].c[2] = c2; pm[idc].c[3] = c3; pm[idc].c[4] = c4;
					U[idc] = (c1 > 0) + (c2 > 0) + (c3 > 0) + (c4 > 0);
				}
			}
		}
	}
	pm[0].c[0] = 8;
	for(register int i = 0; i <= 4; ++ i)
		for(register int j = 0; j <= 4; ++ j)
			C[(i + j) % 5][i] = j;
	memset(st, -1, sizeof st);
}


//当前是0，往下转移一，dfs
//当前是1，判断下一个状态是否可能是0，如果是就附上，往下转移。
//当前是平，不进入dfs。

inline int chang(int c1, int c2, int st2){
	node a = pm[st2];
	register int c3 = C[c2][c1];
	a.c[c2] --; a.c[c3] ++;
	return mp[a.c[1]][a.c[2]][a.c[3]][a.c[4]];
}

//inline int Cnt(int st1, int st2){
//	return (((pm[st1].c[1] > 0) + (pm[st1].c[2] > 0) + (pm[st1].c[3] > 0) + (pm[st1].c[4] > 0)) * ((pm[st2].c[1] > 0) + (pm[st2].c[2] > 0) + (pm[st2].c[3] > 0) + (pm[st2].c[4] > 0)));
//}

int u, ok = 0;
void dfs(int st1, int st2){
	u ++; 
	for(register int c1 = 1; c1 <= 4; ++ c1){
		if(!pm[st1].c[c1]) continue; // 先手人的牌堆
		for(int c2 = 0; c2 <= 4; ++ c2){ // 后手人在上一环节计算的c
			if(!pm[st2].c[c2]) continue;
			register int k = (c1 - c2 + 5) % 5;
			if (!k) continue;
			register int st3 = chang(c1, c2, st2);// 后手人上一轮的状态。
			if(st[st1][st2] == 0){
				if(st[st3][st1] == -1){
					st[st3][st1] = 1;
					dfs(st3, st1);
				}
			}
			if(st[st1][st2] == 1){
				cnt[st3][st1] ++;
				if(cnt[st3][st1] == (U[st3] * U[st1])){
					if(st[st3][st1] == -1){
						st[st3][st1] = 0;
						dfs(st3, st1);
					}
				}
			}
		}
	}
}

int main(){
	init();
	for(register int i = 1; i <= idc; ++ i){
		st[i][0] = 0; st[0][i] = 1;
		dfs(i, 0);
	}
	read(T);
	while(T --){
		read(f);
		register int st1, st2, c[5] = {0, 0, 0, 0, 0}, a;
		for(register int i = 1; i <= 8; ++ i) read(a), c[a] ++;
		st1 = mp[c[1]][c[2]][c[3]][c[4]];
		c[0] = 0;c[1] = 0;c[2] = 0;c[3] = 0;c[4] = 0;
		for(register int i = 1; i <= 8; ++ i) read(a), c[a] ++;
		st2 = mp[c[1]][c[2]][c[3]][c[4]];
		register int flg = (f ? st[st2][st1] : st[st1][st2]);
		if(flg == -1) puts("Deal");
		else if(f ^ flg) puts("Alice");
		else puts("Bob");
	}
	return 0;
}
```


---

