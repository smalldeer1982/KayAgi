# The Light Square

## 题目描述

爱丽丝在她的生日那天收到了朋友们送她的一件有趣的礼物——光明方板。光明方板游戏是在一个n×n灯泡方板上玩的，方板上有一个n×1大小的具有魔法属性的魔法灯棒。游戏开始时，方块板和魔法棒上的一些灯都会亮起。这个游戏的目标是在不旋转方板的情况下，使用魔法棒将起始方板图案转换成其他图案。神奇魔法棒的工作原理如下：


它可以放在任何行或列上


魔法棒的方向必须从左到右或从上到下，这样才能保持其魔法特性


整根魔法棒都要放在方板上


魔法棒的灯光永不改变


如果魔法棒上的灯和方板上的灯的状态是一样的，它会把方板上的灯关掉，否则它会把灯打开


魔法棒可以无限次使用


爱丽丝很难把她的方板变成鲍勃给她的式样。你能帮她把方板上的灯改变成想要的样子或者让她知道这是不可能的么？如果有多种解决方案，请输出任何解决方案。

## 样例 #1

### 输入

```
2
11
11
00
01
11
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
10
00
00
00
10
```

### 输出

```
1
row 0
```

## 样例 #3

### 输入

```
3
110
011
100
100
011
100
100
```

### 输出

```
3
row 0
col 0
col 1
```

# 题解

## 作者：chlchl (赞：1)

## 题意简述
给定一个 $n\times n$ 的初始矩阵和目标矩阵，并给出一个 $1\times n$ 的操作序列（上述矩阵都由 $0$ 和 $1$ 组成）。每次可以选择一行或一列按顺序异或上操作序列。问几次操作可以从初始矩阵变成目标矩阵，并要求输出方案。

## 做法
一道非常好的思维题，**建议评绿**。

明显 $n\leq 2000$ 不可能直接深搜（$n\leq 20$ 都过不了）。我们需要更为高级的做法。

明显地，一个矩阵最多操作 $2n$ 次，因为异或两次回回到原来状态，所以最多每一行、每一列都操作一次。

这种矩阵变换问题的思考方向大体是一致的，让我们先看一个铺垫。

### 铺垫：开灯问题
有一个 $5\times 5$ 的 01 矩阵，每次可以选择一个点异或上 $1$，但每一次都会使上下左右四个点都异或上 $1$。问能否通过有限次操作使矩阵全部变成 $1$？

这道题目，我们容易发现，对于某一行，当它们和下一行所有元素都**操作完毕后**，这一行的数就**不会再变了**。

因此，我们逐行判断，发现某个数为 $0$ 时，就把它下面那个数异或上 $1$。这样这个数就会被修改为 $1$。

为什么不直接修改这个数？因为有可能影响到左右两个数和上一行的数，而我们规定**上一行的数不能再变**。

------------
看完这个问题，我们回到这题的题解。

这题是一行、一列的操作。我们发现，对于每个点，它仅可以通过所在行、所在列的改变而改变自身的状态。并且由于不能翻转操作序列，其对应操作序列的位置是固定的。

所以，如果其对应的两个位置都是 $0$，那就无法修改。

但是这么思考太麻烦了，我们换个角度。

用初始矩阵异或目标矩阵，我们得到哪些位置是需要被改动的。而对于操作序列来说，**当且仅当某个位置为 $1$ 时，对应矩阵上的数才能改变**。

换句话来说，我们不需要考虑矩阵上需要改动的点是否能改，而是考虑**操作序列能使哪些点被改动**。

考虑贪心，一旦遍历到操作序列有一个为 $1$，就去暴力扫每一行、每一列，看看有没有其对应的位置为 $1$，如果有就修改。

为什么这样贪心是对的呢？我们从两个角度证明。

Q1：操作序列**其他位置**上的 $1$ 为什么不需要管？

A1：设操作序列第一个 $1$ 的位置为 $i$。对于其他 $1$ 位置 $j$，如果在矩阵的某一行或某一列，第 $j$ 位为 $1$，第 $i$ 位为 $0$，那就算修改，$i$ 也会变成 $1$，仍然达不成目的；而对于矩阵第 $i$ 个位置是 $1$ 的情况，$j$ 也会跟着 $i$ 一起修改（因为一放就是一整列）。

Q2：一发现矩阵某一行或某一列 $i$ 位置是 $1$ 就修改，那其它位置的状态也会改变，为什么不需要管？

A1：因为矩阵上的一个点可以被它所在的行、列各修改一遍。就算它某次 $0\rightarrow 1$（比如说所在列的修改），也可以通过后续所在行的修改变回来。如果它不能变回来，恰恰说明初始矩阵是无法变成目标矩阵的。

至此，这道题就做完了。

截止至 2022.9.26，还是最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2000 + 10;
int n, m, idx;
char st[N][N], g[N][N], b[N];
struct instruction{
	string rc;
	int idx;
} a[N << 1];

bool check(){
	for(int i=1;i<=n;i++)	for(int j=1;j<=n;j++)	if(g[i][j] == '1')	return 0;
	return 1;
}

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)	scanf("%s", st[i] + 1);
	for(int i=1;i<=n;i++){
		scanf("%s", g[i] + 1);
		for(int j=1;j<=n;j++)	g[i][j] ^= (int)(st[i][j] - '0');
	}
	scanf("%s", b + 1);
	bool f = 0;
	for(int i=1;!f&&i<=n;i++)	if(b[i] == '1')	idx = i, f = 1;
	if(!f)	return printf("-1\n"), 0;
	
	for(int i=1;i<=n;i++){
		if(g[idx][i] == '1'){
			a[++m] = (instruction){"col", i - 1};
			for(int j=1;j<=n;j++)	g[j][i] ^= (int)(b[j] - '0');
		}
	}
	
	for(int i=1;i<=n;i++){
		if(g[i][idx] == '1'){
			a[++m] = (instruction){"row", i - 1};
			for(int j=1;j<=n;j++)	g[i][j] ^= (int)(b[j] - '0');
		}
	}
	
	if(check()){
		printf("%d\n", m);
		for(int i=1;i<=m;i++)	cout << a[i].rc << ' ' << a[i].idx << endl;
	}else	printf("-1\n");
	return 0;
}
```


---

## 作者：wgyhm (赞：1)

# CF1218I The Light Square

## 题意

给定两个 $n\times n$ 的矩阵 $A$ 和 $B$ ，以及一个 $1\times n$ 的矩阵 $C$。

每次可以进行一下两个操作之一：

* 对于第 $i$ 行， $A_{i,j}=A_{i,j} \bigotimes C_{1,j}$
* 对于第 $j$ 列，$A_{i,j}=A_{i,j} \bigotimes  C_{1,i}$

问进行若干操作以后是否可以使 $A$ 与 $B$ 相等。如果可以，输出任意一组方案。

## 题解

根据异或的性质，显然对于一行或者一列，操作最多执行一次是最优的。所以对于一个格子，操作最多执行两次。

设 $x_i,1\le i\le n$ 为第 $i$ 行是否被操作；$x_i,n+1\le i\le 2n$ 为第 $(i-n)$ 列是否被操作，$x_{i}=0/1$。

如果 $A=B$ ，那么有 $A_{i,j} \bigotimes {(C_{1,j}\times x_i)\bigotimes (C_{1,i}\times x_j)=B_{i,j}}$

移项得，${(C_{1,j}\times x_i)\bigotimes (C_{1,i}\times x_j)=A_{i,j} \bigotimes B_{i,j}}$

这就是 $2-SAT$ 的形式 。套板子然后输出一组通解即可。

## Code:

好像写烦了。。。

```cpp
#define maxn 10005
int n,m;
int h[maxn],head=1;
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[2005*2005*4];
bool f[2005][2005],c[2005];
inline void ins(int x,int y){a[++head].add(x,y);a[++head].add(y,x);}
int scc[maxn],sccnum,dfn[maxn],low[maxn],stac[maxn],tot,times,vis[maxn];
//tarjan板子你们应该都会
signed main(){
    rg int i,j,ans=0,x;rg char ch;
    read(n);
    for (i=1;i<=n;i++){
    	ch=getchar();while (ch!='0'&&ch!='1') ch=getchar();
    	for (j=1;j<=n;j++,ch=getchar()) f[i][j]=ch-'0';
	}
	for (i=1;i<=n;i++){
    	ch=getchar();while (ch!='0'&&ch!='1') ch=getchar();
    	for (j=1;j<=n;j++,ch=getchar()) f[i][j]^=ch-'0';
	}
	ch=getchar();while (ch!='0'&&ch!='1') ch=getchar();
	for (i=1;i<=n;i++,ch=getchar()) c[i]=ch-'0';//读入
	for (i=1;i<=n;i++)
	    for (j=1;j<=n;j++)
	        if (f[i][j]==0){
				if (c[j]&&c[i]) ins(i+2*n,j+3*n),ins(i,j+n);
	            else if (!c[j]&&c[i]) a[++head].add(i,j+n),a[++head].add(i+2*n,j+n),a[++head].add(j+3*n,j+n);
	            else if (c[j]&&!c[i]) a[++head].add(j+n,i),a[++head].add(j+3*n,i),a[++head].add(i+2*n,i);
			}
			else{
				if (c[j]&&c[i]) ins(i,j+3*n),ins(i+2*n,j+n); 
				else if (!c[j]&&c[i]) a[++head].add(i,j+3*n),a[++head].add(i+2*n,j+3*n),a[++head].add(j+n,j+3*n);
				else if (c[j]&&!c[i]) a[++head].add(j+n,i+2*n),a[++head].add(j+3*n,i+2*n),a[++head].add(i,i+2*n);				
				else if (!c[j]&&!c[i]) return puts("-1"),0;
			} //建边
	for (i=1;i<=4*n;i++) if (!dfn[i]) tarjan(i);
	for (i=1;i<=2*n;i++) if (scc[i]==scc[i+2*n]) return puts("-1"),0;//判无解
	for (i=1;i<=2*n;i++) ans+=scc[i]>scc[i+2*n];
	for (printf("%d\n",ans),i=1;i<=n;i++) if (scc[i]>scc[i+2*n]) printf("row %d\n",i-1);
	for (i=n+1;i<=n*2;i++) if (scc[i]>scc[i+2*n]) printf("col %d\n",i-n-1);
	return 0;
}
```



---

