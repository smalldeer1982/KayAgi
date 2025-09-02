# [BalticOI 2013] Vim

## 题目描述

给定一个长度为 $N$ 的字符串 $S$，Victor 的目标是将其中的 `e` 全部删除，而不删除其他字符。最开始光标在第一个字符处。

Victor 使用 `Vim` 来解决这个问题。

然而，Victor 并不熟悉 `Vim`，他只知道这里面的三个指令：
- `x`：删除光标处的字符，光标位置不变，不可以在最后的字符处使用这个命令。
- `h`：将光标向左移动一格，如果光标位于第一个位置，则光标不动。
- `f`：其后接一个字符 $c$，其将会将光标移至其右边的第一个字符 $c$，$c\not =$ `e`。

请计算将其中的 `e` 全部删除，而不删除其他字符的最小**按键**数。

## 说明/提示

#### 样例解释
`fdhxhhxffhxfahxhhhxhhhxfdhxfghxfahhx` 为最优解。
#### 数据范围及限制
- 对于 $50$ 分的数据，保证 $N\le 500$。
- 对于另外 $10$ 分的数据，保证 $N\le 5\times 10^3$。
- 对于 $100\%$ 的数据，保证 $1\le N\le 7\times 10^4$，$S_i\in\{$ `a` $\sim$ `j` $\}$，$S_1,S_N\not=$ `e`。

**译者提醒：实在是搞不懂怎样设置了，所以按洛谷默认的来。**
#### 说明
本题译自 [Baltic Olympiad in Informatics 2013](https://boi.cses.fi/tasks.php) [Day 2](https://boi.cses.fi/files/boi2013_day2.pdf) T3 Vim。

## 样例 #1

### 输入

```
35
chefeddiefedjeffeachbigagedegghehad```

### 输出

```
36
```

# 题解

## 作者：SDNetFriend (赞：17)

### 转化

首先可以看出，那些 `e` 的位置对答案的贡献是固定的。当我们走到一段连续的 `e` 的前方，便可以后退一次删一次，如此反复，每个 `e` 的贡献就固定是 $2$，那么计算了这个之后把 `e` 从原序列剔除，并且我们把每一个左边有 `e` 的位置都标记为关键点，因为这些点必须经过才能删除 `e`。

于是问题变为了：可以花费 $1$ 的代价向左走一步，可以花费 $2$ 的代价跳到右边下一个任意字符，且序列中有若干关键点必须经过，求最小代价。

### 简化

~~根据官方题解或者感性理解或者经过严谨证明~~，可以得知最终的路线一定是向右跳若干步，然后向左走一段，然后继续向右跳。并且任何两段向左走的区间都不可能有交，否则一定不优。于是就像很多题解所写的那样，路径一定长成这样：（从博客园 [cjoier_Itst ](https://home.cnblogs.com/u/Itst/) 大佬处借了个图）

![](https://www.cnblogs.com/images/cnblogs_com/Itst/1393185/o_%e5%9b%be%e8%a1%a81.png)

这就变成了一个“序列上的复杂路径”，考虑用线头 DP 解决。

### 动态规划

我们给路径切片，第 $i$ 片表示从 $i$ 到 $i+1$ 的路径片。然后观察这个图，发现只有两种路径片：被覆盖一次的和被覆盖三次的。这里的“覆盖”不一定是走到了这个点，一次向右跳过程中，中间经过的所有的点都算被覆盖的点，其实也就是长成这样：（竖线代表一个点）

![](https://cdn.luogu.com.cn/upload/image_hosting/xumwyw8x.png)

最终我们的路径是由一片片这样的路径片拼起来形成的，我们实际上就是在决策第 $i$ 个位置到第 $i+1$ 个位置的路线变化情况，这些变化是在第 $i$ 个位置发生的。。

我们考虑设状态分别为 $f_{i,x}$ 和 $g_{i,x,y}$。

分别表示：考虑完前 $i$ 个路径片，当前路径片只被覆盖了一次（即右图），此次跳跃终点的字符是 $x$ 的最小代价；考虑完前 $i$ 个路径片，当前路径片被覆盖了三次（即左图），上方跳跃终点是 $x$，下方跳跃终点是 $y$ 的最小代价，详细点的话，一次跳跃-折返-跳跃的过程是被描述成了这种形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/96wgysyv.png)

我们叫第一次跳跃为上方跳跃，第二次为下方跳跃（即两条绿色的曲线）。

注意这个绿色曲线**不一定只跳了一次**，可能是由很多次跳跃组成的。

那我们又怎么计算代价呢？考虑有几种边界情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vh9e7lf3.png)

（只画出了一部分情况）。

就是说，对向右跳这个过程，存在“起跳”和“降落”的位置，而我们考虑只在起跳的位置把贡献加上去就可以了。

通俗一点讲，我们以第一张图为例，假设现在的情况是：

![](https://cdn.luogu.com.cn/upload/image_hosting/m7dnrrds.png)

左边是第 $i$ 个路径片，右边是第 $i+1$ 个，三条竖线分别代表 $i,i+1,i+2$。我们设 $s_i$ 表示 $i$ 位置的字符。考虑什么时候会出现这种情况，出现了又要如何计算贡献。

当且仅当第 $i$ 个路径片，对应的状态是 $f_{i,s_{i+1}}$，那么因为向右跳是跳到第一个对应字符的位置，所以在 $i+1$ 的位置就必须降落，并重新起跳。那么这次新的起跳就会产生 $2$ 的代价。（当然如果你把贡献在降落位置计算是完全没有问题的）

以此类推，这个题就可以 DP 了，转移方程：（$flg_i$ 表示 $i$ 是关键点）
$$
\begin{aligned}
f_{i-1,x}\to f_{i,x} && flg_i=F,x\neq s_i\\
f_{i-1,s_i}+2\to f_{i,x}\\
g_{i-1,s_i,x}\to f_{i,x} && x\neq x_i\\
g_{i-1,s_i,s_i}+2\to f_{i,x}
\end{aligned}
$$
以上是对 $f_{i,x,y}$ 的转移，分别表示：

- 没降落也没起跳，只被覆盖一次，因为 $i$ 不会被经过所以不能是关键点 。
- 在当前位置降落了，并继续向 $x$ 去跳。
- 第 $i-1$ 片被覆盖了三次，并且其对应的上方（就是设计状态那个上）跳跃的终点位置在 $i$。
- 第 $i-1$ 片被覆盖了三次，并且其对应的上方下方的跳跃终点位置都在 $i$，此时需要从 $i$ 处接着下方跳跃起跳。

$$
\begin{aligned}
g_{i-1,x,y}+1\to g_{i,x,y} && x\neq s_i, y\neq s_i\\
g_{i-1,x,s_i}+3\to g_{i,x,y} && x\neq s_i\\
g_{i-1,s_i,y}+3\to g_{i,x,y} && y\neq s_i\\
g_{i-1,s_i,s_i}+5\to g_{i,x,y}\\
f_{i-1,s_i}+5\to g_{i,x,y}\\
f_{i-1,x}+3\to g_{i,x,y} && x\neq s_i
\end{aligned}
$$

以上是对 $g_{i,x,y}$ 的转移，分别表示：

- 上下两个跳跃都没降落也没起跳，向左走的那一步产生了 $1$ 的贡献，接下来的每一个状态都有向左走的 $1$ 的贡献。
- 下方跳跃在点 $i$ 降落并重新起跳，额外产生 $2$ 的贡献。
- 上方跳跃在点 $i$ 降落并重新起跳，额外产生 $2$ 的贡献。
- 上下方跳跃都在 $i$ 降落并重新起跳，额外产生 $4$ 的贡献。
- 第 $i-1$ 片被覆盖了一次，并且其在 $i$ 处降落，所以上方从 $i$ 起跳产生了 $2$ 的贡献，因为左侧只被覆盖一次，所以下方跳跃也从 $i$ 起跳，再次产生 $2$ 的贡献。
- 第 $i-1$ 片只被覆盖了一次，并且上方跳跃没有降落。此时 $i$ 会作为下方跳跃的起点，产生 $2$ 的贡献。

知道这些就可以愉快地  DP 了。初始我们设 $f_{0,s_1}=0$，然后最终我们假设在无限远的地方有一个没有出现过的字符，可以认为是 `k`，使最后一次起跳终点为 `k`，那我们这部分的答案就是 $f_{n,k}-2$，因为最后一次实际上并没有起跳。

#### 代码

转移顺序和上述一致。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=7e4+5,A=10;
int n,a[N],ans0,ans;
char s[N];bool flg[N];
inline void init(){
	int lst=0,_n=0;
	for(int i=1;i<=n;++i){
		if(s[i]!='e'){
			a[++_n]=(s[i]>'e'?s[i]-'a'-1:s[i]-'a');
			if(lst)flg[_n]=true,lst=0;
		}else ans0+=2,lst=i;
	}n=_n;
}int f[2][A],g[2][A][A];
inline void umin(int &x,int y)
	{if(y<x)x=y;}
inline void solve(){
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	f[0][a[1]]=0;	
	for(int i=1;i<=n;++i){
		swap(f[0],f[1]);swap(g[0],g[1]);
		memset(f[0],0x3f,sizeof f[0]);
		memset(g[0],0x3f,sizeof g[0]);
		int c=a[i];
		for(int x=0;x<A;++x){
			if(!flg[i]&&x!=c)umin(f[0][x],f[1][x]);
			umin(f[0][x],f[1][c]+2);
			if(x!=c)umin(f[0][x],g[1][c][x]);
			umin(f[0][x],g[1][c][c]+2);	
		}
		for(int x=0;x<A;++x)
			for(int y=0;y<A;++y){
				if(x!=c&&y!=c)umin(g[0][x][y],g[1][x][y]+1);
				if(y!=c)umin(g[0][x][y],g[1][c][y]+3);
				if(x!=c)umin(g[0][x][y],g[1][x][c]+3);
				umin(g[0][x][y],g[1][c][c]+5);
				umin(g[0][x][y],f[1][c]+5);
				if(x!=c)umin(g[0][x][y],f[1][x]+3);
			}
	}ans=f[0][A-1]-2;
}
int main(){
	freopen("vim.in","r",stdin);
	freopen("vim.out","w",stdout);
	n=read();scanf("%s",s+1);
	init();solve();
	printf("%d",ans0+ans);
	return 0;
}
```

---

## 作者：zzxLLL (赞：10)


**「线头 dp」**，一种和插头 dp 类似的，但是不是补全插头，而是补全线段的 dp。

---

[[BalticOI2013] Vim](https://www.luogu.com.cn/problem/P6758)

题意：给定一个长度为 $N$ 的字符串 $S$，一开始光标在第一个字符处。可以进行如下三种操作，要求删除所有的字符 ``e`` 且费用尽量小：

- 花费 $1$ 删掉当前字符。

- 花费 $1$ 光标向左移动一格。

- 花费 $2$ 跳跃到光标以后某个字符（除 ``e`` 外）第一次出现的位置。

$N \leq 70000$，$S_i \in \{$ ``a`` $\sim$ ``j`` $\}$，$S_1, S_N \neq$ ``e``。

---

首先发现，如果要删除一个 ``e`` 字符，必然是从它后面一个字符花费 $1$ 移动到它，然后花费 $1$ 删掉，即花费为 $2$。

所以可以事先将所有的 ``e`` 挑走，每个花费 $2$，同时将一段 ``e`` 以后的那个字符设为关键点，只有经过了关键点才可能将它左边的 ``e`` 删除。如样例，标红的是关键点：

$$\color{red}c\color{green}he\color{red}f\color{green}e\color{red}d\color{green}die\color{red}f\color{green}e\color{red}d\color{green}je\color{red}f\color{green}fe\color{red}a\color{green}chbigage\color{red}d\color{green}e\color{red}g\color{green}ghe\color{red}h\color{green}ad$$

为了方便，第一个字符也是关键点。显然，**关键点是一定要经过的。**

后文 $s$ 为删除了字符 ``e`` 后的字符串，$n = |s|$。

考虑一个可能最优的方案，会长成这个样子：

![0](https://pic.imgdb.cn/item/64ce7d691ddac507cc96e215.png)

显然路径有重叠就不优，所以是上图这样子的。数轴上每一个点代表一个字符。

然后可以发现，对于 $1 \leq i < n$，$i \sim i+1$ 都被经过了 $1$ 次或 $3$ 次。所以可以设计 dp 状态：

$f_{i, x}$ 表示第 $i \sim i + 1$ 格仅被经过 $1$ 次（只能是操作 3），目标字符是 $x$ 时的最小花费。

$g_{i, x, y}$ 表示第 $i \sim i + 1$ 格被经过 $3$ 次（操作 3 -> 操作 1 -> 操作 3），第一次操作 3 目标字符是 $x$，第二次操作 3 目标字符是 $y$ 的最小花费。

![1](https://pic.imgdb.cn/item/64ce82b11ddac507cca31450.png)

绿色部分是已经被处理过了；蓝色部分是正在处理的部分，即 $i \sim i + 1$，亮紫色是未来会处理的。左边的是 $f$，右边的是 $g$。

在每一格，向左走的操作有 $1$ 的花费。跳的话因为整一段只算一次，所以将贡献移到起跳点，即只有起跳的时候有 $2$ 的贡献。

然后考虑转移，分四类：

### $f$ 转移到 $f$

![2](https://pic.imgdb.cn/item/64ce84761ddac507cca6abfc.png)

考虑得到 $f_{i, x}$。

对于左边的情况，转移是 $f_{i, x} = f_{i - 1, x}$，条件是 $s_i \neq x$ 且 $i$ 不是关键点。

- 如果 $s_i = x$ 那么绿色段应该降落到点 $i$，与左图不符。

- 如果 $i$ 是关键点，根据左图这次跳跃没有降落到点 $i$，后面也没有折回来，所以是无法经过点 $i$ 的，不符合题意。

对于右边的情况，转移是 $f_{i, x} = f_{i - 1, s_i} + 2$。$2$ 是起跳的费用。

### $g$ 转移到 $f$

![3](https://pic.imgdb.cn/item/64ce88bc1ddac507ccafa9c2.png)

考虑得到 $f_{i, x}$。

对于左边的情况，转移是 $f_{i, x} = g_{i - 1, s_i, x}$，条件是 $s_i \neq x$。

- 要保证 $i - 1 \sim i$ 有 $3$ 段经过，所以 $g$ 的第二维应为 $s_i$。

- 还要保证 $g$ 的第二维不是 $s_i$，否则应降落到点 $i$，不符合左图。

对于右边的情况，转移是 $f_{i, x} = g_{i - 1, s_i, s_i} + 2$。$2$ 是起跳的费用。

### $f$ 转移到 $g$

![4](https://pic.imgdb.cn/item/64ce8b8d1ddac507ccb4e876.png)

考虑得到 $g_{i, x, y}$。

对于左边的情况，转移是 $g_{i, x, y} = f_{i - 1, x} + 3$，条件是 $x \neq s_i$。$3$ 是向左走的费用 + 起跳的费用。

对于右边的情况，转移是 $g_{i, x, y} = f_{i - 1, s_i} + 5$，不需要条件。$5$ 是向左走的费用 + 两次起跳的费用。

### $g$ 转移到 $g$

![5](https://pic.imgdb.cn/item/64ce8fb31ddac507ccbc8e79.png)

考虑得到 $g_{i, x, y}$。

对于左上的情况，转移是 $g_{i, x, y} = g_{i - 1, x, y} + 1$，条件是 $x \neq s_i$ 且 $y \neq s_i$。$1$ 是向左走的贡献。

对于右上的情况，转移是 $g_{i, x, y} = g_{i - 1, s_i, y} + 3$，条件是 $y \neq s_i$。$3$ 是向左走的贡献 + 起跳的贡献。

对于左下的情况，转移是 $g_{i, x, y} = g_{i - 1, x, s_i} + 3$，条件是 $x \neq s_i$。$3$ 是向左走的贡献 + 起跳的贡献。

对于右下的情况，转移是 $g_{i, x, y} = g_{i - 1, s_i, s_i} + 5$，不需要条件。$5$ 是向左走的贡献 + 两次起跳的贡献。

### 边界情况

$f_{0, s_1} = 0$，其余的 $f, g$ 均为 $+ \infin$。

设原数列共有 $c$ 个 ``e``，那么答案为 $f_{n, |\Sigma| + 1} - 2 + 2c$，其中 $\Sigma$ 表示字符集。

即假设 $s_{n + 1}$ 为一个特殊字符，标号为 $|\Sigma| + 1$。走完 $s_{[1, n+1]}$，再减去从前面某个点跳跃到 $s_{n + 1}$ 的 $2$ 的花费，再加上每个 ``e`` 字符的 $2$ 的花费即为答案。

---

时间复杂度 $O(n |\Sigma|^2)$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const int M=77777,K=11;
const int inf=1e9+7;

void gmin(int &A,int B){A=std::min(A,B);}

int n,len,cnt_e,s[M];
char str[M];
bool key[M];

int f[M][K],g[M][K][K];

int main(){
	scanf("%d",&len);
	scanf(" %s",str+1);
	
	bool flag=true;
	for(int i=1;i<=len;i++)
		if(str[i]=='e') flag=true,cnt_e++;
		else key[++n]=flag,s[n]=str[i]-'a',flag=false;
	
	for(int i=0;i<=n;i++)
		for(int x=0;x<K;x++) f[i][x]=inf;
	for(int i=0;i<=n;i++)
		for(int x=0;x<K;x++)
			for(int y=0;y<K;y++) g[i][x][y]=inf;
	f[0][s[1]]=0;
	for(int i=1;i<=n;i++){
		// f -> f
		for(int x=0;x<K;x++){
			if(!key[i]&&x!=s[i]) gmin(f[i][x],f[i-1][x]);
			gmin(f[i][x],f[i-1][s[i]]+2);
		}
		
		// f -> g
		for(int x=0;x<K;x++)
			for(int y=0;y<K;y++){
				if(x!=s[i]) gmin(g[i][x][y],f[i-1][x]+3);
				gmin(g[i][x][y],f[i-1][s[i]]+5);
			}
		
		// g -> f
		for(int x=0;x<K;x++){
			if(x!=s[i]) gmin(f[i][x],g[i-1][s[i]][x]);
			gmin(f[i][x],g[i-1][s[i]][s[i]]+2);
		}
		
		// g -> g
		for(int x=0;x<K;x++)
			for(int y=0;y<K;y++){
				if(x!=s[i]&&y!=s[i]) gmin(g[i][x][y],g[i-1][x][y]+1);
				if(y!=s[i]) gmin(g[i][x][y],g[i-1][s[i]][y]+3);
				if(x!=s[i]) gmin(g[i][x][y],g[i-1][x][s[i]]+3);
				gmin(g[i][x][y],g[i-1][s[i]][s[i]]+5);
			}
	}
	printf("%d",f[n][10]-2+2*cnt_e);
	return 0;
}
```

---

## 作者：UniGravity (赞：5)

## Solution P6758 [BalticOI2013] Vim
### 说在前面
这是一道较为经典的**线头**动态规划题目。由于转移方程较为复杂且题解区图片较为简单，故写此篇**带详细图片**的题解。

### 题目思路
线头 dp 就是针对线段进行处理的 dp。

我们先对本题进行转化。  
题目要求删去所有的 `e`，发现每删去一个 `e` 的代价为 $2$，即先从后一个字符移动到它，再删除。  
我们先把所有的 `e` 删去，如果有 $cnt$ 个，最后额外付出的代价为 $2\times cnt$。    


------------

想要删去 `e`，新序列中的 `e` 的后一个字符必须被经过。    
题目现在转化为在新序列上移动，要求某些点必须被经过，求移动的最小代价。

由于要向前走，一个点只会被经过奇数次，想要最优地移动，一个点只会被经过一或三次。

我们设计状态：
* $f_{i,a}$ 表示经过 $i$ **一次**，且目标是**字符** $a$ 的最小代价。
* $g_{i,a,b}$ 表示经过 $i$ **三次**，且第一次目标是**字符** $a$，第二次目标是**字符** $b$ 的最小代价。


------------

记 $need_i$ 表示这个点必须被经过。接下来是转移方程，直接丢张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/52xb7w1r.png)  
第一种方法，直接不走 $i$，要求 $s_i\neq a\&\&!need_i$，因为移动只会到右边的第一个字符。
$$f_{i,a}=f_{i-1,a}\{s_i\neq a\&\&!need_i\}$$
第二种，在 $i$ 处中转，注意一次操作代价为 $2$。
$$f_{i,a}=f_{i-1,s_i}+2$$
剩下两种，从 $g$ 转移，和上面同理：
$$f_{i,a}=g_{i-1,s_i,a}\{s_i\neq a\}$$
$$f_{i,a}=g_{i-1,s_i,s_i}+2$$

对于 $g$，再丢一张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/f420thci.png)  
前两种方法，从 $f$ 转移，一种停留一种不停留，同时因为下方没走，所以需要花费额外代价：
$$g_{i,a,b}=f_{i-1,a}+3\{s_i\neq a\}$$
$$g_{i,a,b}=f_{i-1,s_i}+5$$
另外四种其实也不难理解，就是上方跳或不跳，下方跳或不跳的组合方案：
$$g_{i,a,b}=g_{i-1,a,b}+1\{s_i\neq a\&\&s_i\neq b\}$$
$$g_{i,a,b}=g_{i-1,s_i,b}+3\{s_i\neq b\}$$
$$g_{i,a,b}=g_{i-1,a,s_i}+3\{s_i\neq a\}$$
$$g_{i,a,b}=g_{i-1,s_i,s_i}+5$$

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 70005, K = 10, INF = 0x3f3f3f3f;

int n, m = 0;
char base[N];
int s[N];
bool need[N];

int f[N][K], g[N][K][K];

int main() {
	scanf("%d %s", &n, base + 1);
	int ecnt = 0;
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (base[i] == 'e') {
			ecnt++;
			flag = true;
		} else {
			s[++m] = base[i] - 'a' - ((base[i] < 'e') ? 0 : 1);
			need[m] = flag;
			flag = false;
		}
	}
	
	memset(f, INF, sizeof(f));
	memset(g, INF, sizeof(g));
	f[0][s[1]] = 0; // init
	int f1, g1;
	for (int i = 1; i <= m; i++) {
		for (int a = 0; a < K; a++) {
			f1 = INF;
			if (s[i] != a && !need[i]) f1 = min(f1, f[i - 1][a]);              //  flyU
			                           f1 = min(f1, f[i - 1][s[i]] + 2);       // jumpU
			if (s[i] != a)             f1 = min(f1, g[i - 1][s[i]][a]);        // stayU +  flyD
			                           f1 = min(f1, g[i - 1][s[i]][s[i]] + 2); // stayU + jumpD
			f[i][a] = f1;
			                           
			for (int b = 0; b < K; b++) {
				g1 = INF;
				if (s[i] != a)              g1 = min(g1, f[i - 1][a] + 3);          //  flyU +  flyD
				                            g1 = min(g1, f[i - 1][s[i]] + 5);       // jumpU +  flyD
				if (s[i] != a && s[i] != b) g1 = min(g1, g[i - 1][a][b] + 1);       //  flyU +  flyD + back
				if (s[i] != a)              g1 = min(g1, g[i - 1][a][s[i]] + 3);    //  flyU + jumpD + back
				if (s[i] != b)              g1 = min(g1, g[i - 1][s[i]][b] + 3);    // jumpU +  flyD + back
				                            g1 = min(g1, g[i - 1][s[i]][s[i]] + 5); // jumpU + jumpD + back
				g[i][a][b] = g1;
			}
		}
	}
	
	printf("%d", f[m][K - 1] + ecnt * 2 - 2);
	return 0;
}
```

---

## 作者：dead_X (赞：4)

## 前言
回不了的过去。
## 题解
考虑将每个 $\texttt{e}$ 提前处理贡献，并标记它后面的第一个非 $\texttt{e}$ 字符。

那么我们要求的就是所有打标记的位置的 TSP 问题了。

考虑转移边非常特殊：

- 一定存在向前 $1$ 步的边。
- 一定存在向后 $1$ 步的边。
- 存在一些向前若干步的边。

不难注意到决策一定是向前走若干步，然后往回走到最左侧被打标记的字符，那么在所有决策点上 dp 就可以了。

我们发现决策点之间的转移只有两种，段内转移和段间转移。段内转移只需要记录一条线段的最短路，段间转移需要记录两条线段的最短路，这些最短路是可以 dp 求解的。具体地，设 $f_{x,y}$ 为第 $x$ 个节点，准备转移到字符为 $y$ 的节点的最小费用即可。

时间复杂度 $O(n\Sigma^2)$，细节有点多。
## 代码
```cpp
// Problem: P6758 [BalticOI2013] Vim
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6758
// Memory Limit: 500 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[100003],b[100003],id[100003];
int f[100003][13][13];
int g[100003][13];
char s[100003];
signed main()
{
	int L=read(),n=0,m=0,ex=0;
	scanf("%s",s+1);
	for(int i=1,ok=1; i<=L; ++i)
		if(s[i]=='e') ok=1,ex+=2;
		else a[++n]=s[i]-'a',(ok)&&(b[++m]=n,id[n]=m,ok=0,0);
	memset(f,0x3f,sizeof(f)),
	memset(g,0x3f,sizeof(g));
	for(int i=0; i<10; ++i) g[1][i]=2;
	for(int i=2; i<=n; ++i)
	{
		if(id[i])
		{
			for(int j=0; j<10; ++j)
				for(int k=0; k<10; ++k)
				{
					if(j!=a[i]) f[i][j][k]=min(f[i][j][k],g[i-1][j]+2);
					f[i][j][k]=min(f[i][j][k],g[i-1][a[i]]+4);
				}
			for(int j=0; j<10; ++j)
				g[i][j]=min(g[i][j],g[i-1][a[i]]+2);
		}
		else
		{
			for(int j=0; j<10; ++j)
			{
				if(j!=a[i]) g[i][j]=min(g[i][j],g[i-1][j]);
				g[i][j]=min(g[i][j],g[i-1][a[i]]+2);
			}
		}
		for(int j=0; j<10; ++j)
		{
			if(j!=a[i]) g[i][j]=min(g[i][j],f[i-1][a[i]][j]+1);
			g[i][j]=min(g[i][j],f[i-1][a[i]][a[i]]+3);
		}
		for(int j=0; j<10; ++j)
			for(int k=0; k<10; ++k)
			{
				if(j!=a[i]&&k!=a[i]) f[i][j][k]=min(f[i][j][k],f[i-1][j][k]+1);
				if(k!=a[i]) f[i][j][k]=min(f[i][j][k],f[i-1][a[i]][k]+3);
				if(j!=a[i]) f[i][j][k]=min(f[i][j][k],f[i-1][j][a[i]]+3);
				f[i][j][k]=min(f[i][j][k],f[i-1][a[i]][a[i]]+5);
			}
	}
	printf("%d\n",g[n][4]-2+ex);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# P6758 题解

[Problem Link](https://www.luogu.com.cn/problem/P6758)

## **题目大意**

> 给定一个长度为 $n$ 的字符串和一个光标，初始光标在 $1$ 上，每次操作你可以进行如下三种之一：
>
> - 删除当前光标字符，光标指向原本的下一个字符。只能删除 $s_i=\texttt e$ 的位置，保证末尾不是 $\texttt e$。
> - 光标前移一格，不能在开头进行此操作。
> - 指定一个字符 $c$，跳到当前光标右侧第一个 $c$ 出现的位置，不能选择 $c=\texttt e$。
>
> 其中前两种操作代价为 $1$，第三种操作代价为 $2$，求删除所有 $\texttt e$ 的最小代价。
>
> 数据范围：$n\le 70000,\Sigma=\{\texttt {a,b,c,d,e,f,g,h,i,j}\}$。

## 思路分析

我们发现一个 $\texttt e$ 需要两次操作（一个左移一个删除）才能处理，并且 $\texttt e$ 和其他操作没有关心，因此我们把所有 $\texttt e$ 都删掉，预加上他们的代价，然后标记所有 $\texttt e$ 后面的字符，此时相当于我们要用二、三操作遍历所有被标记的字符。

考虑观察移动路径的形态，一定如下（图源：[Itst 的博客](https://www.cnblogs.com/Itst/p/10339605.html)，下同）：

![pC7UXkj.png](https://s1.ax1x.com/2023/07/19/pC7UXkj.png)

然后考虑插头 dp，记录每个 $i\to i+1$ 时的插头状态，容易证明这样的每个位置只被覆盖一次或三次，对于第一种情况，我们记录对应的跳跃操作的终点字符 $j$，对于第二种操作，我们依次记录两次跳跃操作的终点字符 $j,k$。

对于插头的两种形态，分别设计状态 $f_{i,j},g_{i,j,k}$ 表示 $i\to i+1$ 被覆盖次数为 $1/3$ 时的最小代价，其中回撤操作 $i\to i-1$ 的代价在考虑 $i-1\to i$ 时计算，跳跃操作的代价在起点处计算。

先考虑 $f_{i,j}$ 的转移，参考下图得到：

![pC7UL7Q.png](https://s1.ax1x.com/2023/07/19/pC7UL7Q.png)

1. 在 $i-1$ 之前的跳跃操作直接越过 $i$，要求 $j\ne s_i$ 且 $i$ 未被标记：$f_{i,j}\gets f_{i-1,j}$。
2. 前次跳跃在 $i$ 处停止，从 $i$ 处新建一次跳跃到 $j$：$f_{i,j}\gets f_{i-1,s_i}+2$。
3. 前次跳跃在 $i$ 处停止，回撤一段后从前面跳跃到 $j$：$f_{i,j}\gets g_{i-1,s_i,j}$。
4. 前次跳跃在 $i$ 处停止，回撤一段后从 $i$ 处新建一次跳跃到 $j$：$f_{i,j}\gets g_{i-1,s_i,s_i}+2$。

然后考虑 $g_{i,j,k}$ 的转移，根据下图同样可以得到：

![pC7dixP.png](https://s1.ax1x.com/2023/07/19/pC7dixP.png)

1. 前次跳跃直接到 $j$，回撤操作在 $i$ 处停止，然后从 $i$ 新建一段跳跃到 $k$，要求 $s_i\ne j$：$g_{i,j,k}\gets f_{i-1,j}+3$。
2. 前次跳跃在 $i$ 处停止，从 $i$ 处新建到 $j,k$ 的跳跃，中间的回撤也在 $i$ 处停止：$g_{i,j,k}\gets f_{i-1,s_i}+5$。
3. 前次跳跃直接到 $j$，回撤到 $i$ 之前后直接跳跃到 $k$，要求 $s_i\ne j,s_i\ne k$：$g_{i,j,k}\gets g_{i-1,j,k}+1$。
4. 前次跳跃在 $i$ 处停止，新建一次到 $j$ 的跳跃，回撤到 $i$ 之前后直接跳跃到 $k$，要求 $s_i\ne k$：$g_{i,j,k}\gets g_{i-1,s_i,k}+3$。
5. 前次跳跃直接到 $j$，回撤到 $i$ 之前然后先跳到 $i$ 再从 $i$ 新建一次跳跃到 $k$，要求 $s_i\ne j$：$g_{i,j,k}\gets g_{i-1,j,s_i}+3$。
6. 前次跳跃在 $i$ 处停止，回撤到 $i$ 之前然后跳到 $i$ 再从 $i$ 新建一次跳跃到 $k$：$g_{i,j,k}\gets g_{i-1,s_i,s_i}+5$。

根据如上转移直接操作即可，边界条件为 $f_{0,s_1}=0$，最终结束可以看做经过 $n\to n+1$ 的插头到一个不存在的字符上，可以直接取 $f_{n,\texttt e}-2$ 作为答案，其中 $-2$ 是为了减少最后一次实际不存在的跳跃。

时间复杂度 $\mathcal O(n|\Sigma|^2)$。

## **代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
char str[MAXN];
bool chk[MAXN];
int s[MAXN],f[MAXN][10],g[MAXN][10][10]; 
signed main() {
	freopen("vim.in","r",stdin);
	freopen("vim.out","w",stdout);
	int n=0,m,ans=0;
	scanf("%d%s",&m,str+1);
	for(int i=1,x=0;i<=m;++i) {
		if(str[i]=='e') x=1,ans+=2;
		else chk[++n]=x,s[n]=str[i]-'a',x=0;
	}
	memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	auto upd=[&](int &x,int y) { x=x<y?x:y; };
	f[0][s[1]]=0;
	for(int i=1;i<=n;++i) {
		for(int j=0;j<10;++j) {
			if(j!=s[i]&&!chk[i]) upd(f[i][j],f[i-1][j]);
			upd(f[i][j],f[i-1][s[i]]+2);
			if(j!=s[i]) upd(f[i][j],g[i-1][s[i]][j]);
			upd(f[i][j],g[i-1][s[i]][s[i]]+2);
		}
		for(int j=0;j<10;++j) for(int k=0;k<10;++k) {
			if(j!=s[i]) upd(g[i][j][k],f[i-1][j]+3);
			upd(g[i][j][k],f[i-1][s[i]]+5);
			if(j!=s[i]&&k!=s[i]) upd(g[i][j][k],g[i-1][j][k]+1);
			if(k!=s[i]) upd(g[i][j][k],g[i-1][s[i]][k]+3);
			if(j!=s[i]) upd(g[i][j][k],g[i-1][j][s[i]]+3);
			upd(g[i][j][k],g[i-1][s[i]][s[i]]+5);
		}
	}
	printf("%d\n",ans+f[n]['e'-'a']-2);
	return 0;
}
```

---

## 作者：白鲟 (赞：3)

## 前言
在某次模拟赛中接触到了所谓线头 DP。然后拿到这道例题。

还是不太会。

## 参考资料
[Itst 的博客](https://www.cnblogs.com/Itst/p/10339605.html)，比本文详细。

## 题目分析
首先分析出行动方法为重复执行向右跳到某一格，再一边向左跳一边删除的操作。容易获知每个点向左跳的过程中至多被访问一次。于是可以预先删除所有 $\texttt{e}$ 并在答案中加上 $2|\texttt{e}|$ 以去除其影响。问题转化为求经过所有指定点（每段 $\texttt{e}$ 后第一个点）的最优解。

在两点间建立线段，将向右跳看作空中跨过，可以发现每条线段要么仅被从空中跨过一次，要么被从空中跨过两次并在向左跳的过程中被访问一次。因此，只要线段 $i\rightarrow i+1$ 与 $i-1\rightarrow i$ 中某一条不只被跨过一次，或跨过两者的操作不同，点 $i$ 必定被经过。

线头 DP 大致的意思是对于每个状态记录之前和之后可能做出的选择，形象地称之为“线头”，并在转移时尝试连接过去状态中相匹配的线头，从而消除后效性的影响。

具体到此题而言，设 $f(i,j)$ 为通过 $j$ 字符跨过线段 $i\rightarrow i+1$ 的最优解，$g(i,j,k)$ 为第一次通过 $j$，第二次通过 $k$ 经过的最优解，那么 $j,k$ 即为所谓的线头。转移时要么与上一条线段线头相同的状态相接，要么在上一条线段的线头被强制落地（即为 $s_i$）时执行新的跳跃。每次新的跳跃代价为两字符；在第二种行为中由于未计算的回退，每条线段会产生一字符的代价。

具体的状态转移方程式，可参考代码。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=7e4,alpha='k'-'a'+1;
int n,len,cnte,f[maxn+1][alpha],g[maxn+1][alpha][alpha];
bool key[maxn+2];
char s[maxn+3];
int main()
{
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	scanf("%d\n",&n);
	for(int i=1,check=0;i<=n;++i)
	{
		char t=getchar();
		if(t=='e')
			check=++cnte;
		else
		{
			key[++len]=check;
			s[len]=t-'a';
			check=0;
		}
	}
	f[0][s[1]]=0;
	for(int i=1;i<=len;++i)
		for(int j=0;j<alpha;++j)
		{
			if(j!=s[i])
			{
				if(!key[i])
					f[i][j]=f[i-1][j];
				f[i][j]=min(f[i][j],g[i-1][s[i]][j]);
			}
			f[i][j]=min(f[i][j],min(f[i-1][s[i]],g[i-1][s[i]][s[i]])+2);
			for(int k=0;k<alpha;++k)
			{
				if(j!=s[i]&&k!=s[i])
					g[i][j][k]=g[i-1][j][k]+1;
				if(j!=s[i])
					g[i][j][k]=min(g[i][j][k],min(f[i-1][j],g[i-1][j][s[i]])+3);
				if(k!=s[i])
					g[i][j][k]=min(g[i][j][k],g[i-1][s[i]][k]+3);
				g[i][j][k]=min(g[i][j][k],min(g[i-1][s[i]][s[i]]+5,f[i-1][s[i]]+5));
			}
		}
	printf("%d",f[len][alpha-1]+(cnte<<1)-2);
	return 0;
} 
```

---

