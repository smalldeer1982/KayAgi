# Special Graph

## 题目描述

In this problem you will need to deal with an $ n×m $ grid graph. The graph's vertices are the nodes of the $ n×m $ grid. The graph's edges are all the sides and diagonals of the grid's unit squares.

The figure below shows a $ 3×5 $ graph. The black lines are the graph's edges, the colored circles are the graph's vertices. The vertices of the graph are painted on the picture for a reason: the coloring is a correct vertex coloring of the $ 3×5 $ graph into four colors. A graph coloring is correct if and only if each vertex is painted and no two vertices connected by an edge are painted the same color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435E/3bf484c3ac261bc390a50b90927cfdf12af83fc1.png)You are given the size of the grid graph $ n×m $ and the colors of some of its vertices. Find any way how to paint the unpainted vertices of the graph in 4 colors to make the final coloring a correct vertex graph coloring. If there is no such correct vertex coloring, say that the answer doesn't exist.

## 说明/提示

The answer to the first sample is shown on the picture (1 — green color, 2 — blue, 3 — dark blue, 4 — pink).

In the second sample there exists 4! answers, each of them is considered correct.

In the third sample two vertices with equal colors are connected. So the correct vertex coloring couldn't be obtained.

## 样例 #1

### 输入

```
3 5
10101
00020
01000
```

### 输出

```
13131
42424
31313
```

## 样例 #2

### 输入

```
2 2
00
00
```

### 输出

```
12
34
```

## 样例 #3

### 输入

```
2 2
11
00
```

### 输出

```
0
```

# 题解

## 作者：int08 (赞：0)

## 前言
我肯定，在几百年前就见过[这个模型](https://www.luogu.com.cn/problem/CF1844E)，只是它忘了，我也没记起。
# Solution
有一个想法是每一行最多出现两种数，奇数行和偶数行各占两种，这样是一定能构造出来的，却不一定是必要条件。

比如如下构造：

```
132
241
```
就满足条件但是每行出现三种数。

但是如果我们尝试**纵向**扩展这个解，就有好玩的事情发生：

第三行第二个由于和上面三个都相邻，显然只能填 $3$，此时边上两个也确定下来，这个过程可以继续下去：
```
132
241
132
241
132
241
...
```
惊喜地发现现在每列只有两种数了。

于是得到结论：每行（或列）必交替出现两个数，且奇数行（或列）和偶数行（或列）的数不同。

证明如下：

> 首先第一行至少出现两种数，如果正好两种，则往下推下去每一行都只有两种了，如果有三种及以上，一定存在某连续的三个数互不相同，提取出这三列进行上面的向下扩展过程，发现每列就只存在两种数了。

于是直接枚举所有的数分配情况检查是否合法即可。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010],i,j,ans[1010][1010],in[5];
int bic(int x)
{
	int ans=0;
	while(x) ans+=x&1,x>>=1;
	return ans;
}
char op;
void print()
{
	for(i=1;i<=n;i++,cout<<"\n")
		for(j=1;j<=m;j++) cout<<ans[i][j];
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) cin>>op,a[i][j]=op-'0';
	for(int x=3;x<=12;x++) if(bic(x)==2)
	{
		vector<int> d,o;
		int tag=1;
		for(i=1;i<=4;i++) x&(1<<i-1)?d.push_back(i):o.push_back(i);
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++) ans[i][j]=i&1?d[j&1]:o[j&1];
			for(j=1;j<=m;j++) if(a[i][j]&&a[i][j]!=ans[i][j]) break;
			if(j>m) continue;
			for(j=1;j<=m;j++) ans[i][j]=i&1?d[(j&1)^1]:o[(j&1)^1];
			for(j=1;j<=m;j++) if(a[i][j]&&a[i][j]!=ans[i][j]) break;
			if(j<=m) tag=0;
		}
		if(tag) print(),exit(0);
	}
	for(int x=3;x<=12;x++) if(bic(x)==2)
	{
		vector<int> d,o;
		int tag=1;
		for(i=1;i<=4;i++) x&(1<<i-1)?d.push_back(i):o.push_back(i);
		for(j=1;j<=m;j++)
		{
			for(i=1;i<=n;i++) ans[i][j]=j&1?d[i&1]:o[i&1];
			for(i=1;i<=n;i++) if(a[i][j]&&a[i][j]!=ans[i][j]) break;
			if(i>n) continue;
			for(i=1;i<=n;i++) ans[i][j]=j&1?d[(i&1)^1]:o[(i&1)^1];
			for(i=1;i<=n;i++) if(a[i][j]&&a[i][j]!=ans[i][j]) break;
			if(i<=n) tag=0;
		}
		if(tag) print(),exit(0);
	}
	cout<<0;
}
```
# The End.

---

## 作者：Aleph_Drawer (赞：0)

单挑抽到这道题，惨败之后回来补题，发现也不是很难。

### 题目大意

给出一个特定构造的矩阵图，其中有一些点已经染上了颜色。

问你是否可以将这个图全部四色染色，使得满足每一条边上的两个点都不是同一个颜色。

请构造出一个合法解。

### 解法

样例非常有规律，不难猜测正确的构造应该是形如样例一的形式，即每一行（亦或者是每一列，下同）由两种颜色交替填涂，相邻的行的两种颜色不同，如果第一行选择的颜色是 $(1,3)$，则第二行就是 $(2,4)$，而整个矩阵就会类似于下图所展示的一样（下图展示了 $n = 4, m = 4$ 的情况）：
$$
\begin{bmatrix}
	1 & 3  & 1 & 3 \\
	2 & 4 & 2 & 4 \\
	3 & 1 & 3 & 1 \\
	2 & 4 & 2 & 4
\end{bmatrix}
$$


下面我们来证明这种做法是正确的。

首先证明这么填一定可以满足题目的要求，这个证明是显然的，假设我们是相邻每一行不同颜色，那么首先就排除行冲突的情况，而我们每一列都是交替的填写的，所以这样肯定可以满足题目要求。

再来证明如果出现不满足这种情况的时候，一定是无解的，具体的，我们可以讨论形如
$$
\begin{bmatrix}
	1 & 0 & 2 & 0 \\
	2 & 0 & 0 & 0 \\
	0 & 1 & 0 & 0 \\
	0 & 0 & 0 & 0
\end{bmatrix}
$$
的解的情况。

考虑直接将其构造，很容易发现是构造不出解的。考虑对于满足其中的一对要求，以上面的 $1$ 作为例子，那么我们要求相邻每一行颜色不同。然而我们会发现，对于与 $2$ 相邻的点，一定是会出现同时与 $1,2,3,4$ 相邻的情况，而这个我们可以将其拓展，便得到了结论。

最后考虑这种构造方法的唯一性，如果存在某一行或者某一列有三种不同的数字，那么与其相邻的行或者列一定是会存在一个位置没有办法放数字的。

这样我们便严谨的证明了这种方法的正确性的。

然后需要做的事情就比较简单了，我们只需要把所有情况枚举一遍，是常数个数的，与 $a$ 比对看是否满足题目条件，就可以通过本题。

对于某些实现方法，需要特判 $n = 1$ 或 $m = 1$ 的情况。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 104;

int n, m;
int a[N][N];
int gen[N][N];

int fil[5];
bool inq[5];

bool check() {
    bool flag = 1;
    for(int i = 1; i <= n + 1; i += 2) {
        for(int j = 1; j <= m + 1; j += 2) {
            gen[i][j] = fil[1], gen[i][j + 1] = fil[2];
        }
        bool tg = 1;
        for(int j = 1; j <= m; j++) {
            if(a[i][j] && gen[i][j] != a[i][j])
                tg = 0;
        }
        if(!tg) {
            for(int j = 1; j <= m + 1; j += 2) {
                gen[i][j] = fil[2], gen[i][j + 1] = fil[1];
            }
            for(int j = 1; j <= m; j++) {
                if(a[i][j] && gen[i][j] != a[i][j])
                    flag = 0;
            }
        }
        for(int j = 1; j <= m + 1; j += 2) {
            gen[i + 1][j] = fil[3], gen[i + 1][j + 1] = fil[4];
        }
        tg = 1;
        for(int j = 1; j <= m; j++) {
            if(a[i + 1][j] && gen[i + 1][j] != a[i + 1][j])
                tg = 0;
        }
        if(!tg) {
            for(int j = 1; j <= m + 1; j += 2) {
                gen[i + 1][j] = fil[4], gen[i + 1][j + 1] = fil[3];
            }
            for(int j = 1; j <= m; j++) {
                if(a[i + 1][j] && gen[i + 1][j] != a[i + 1][j])
                    flag = 0;
            }
        }
    }
    if(flag)
        return 1;
    flag = 1;
    for(int j = 1; j <= m + 1; j += 2) {
        for(int i = 1; i <= n + 1; i += 2) {
            gen[i][j] = fil[1], gen[i + 1][j] = fil[2];
        }
        bool tg = 1;
        for(int i = 1; i <= n; i++) {
            if(a[i][j] && gen[i][j] != a[i][j])
                tg = 0;
        }
        if(!tg) {
            for(int i = 1; i <= n + 1; i += 2) {
                gen[i][j] = fil[2], gen[i + 1][j] = fil[1];
            }
            for(int i = 1; i <= n; i++) {
                if(a[i][j] && gen[i][j] != a[i][j])
                    flag = 0;
            }
        }
        for(int i = 1; i <= n + 1; i += 2) {
            gen[i][j + 1] = fil[3], gen[i + 1][j + 1] = fil[4];
        }
        tg = 1;
        for(int i = 1; i <= n; i++) {
            if(a[i][j + 1] && gen[i][j + 1] != a[i][j + 1])
                tg = 0;
        }
        if(!tg) {
            for(int i = 1; i <= n + 1; i += 2) {
                gen[i][j + 1] = fil[4], gen[i + 1][j + 1] = fil[3];
            }
            for(int i = 1; i <= n; i++) {
                if(a[i][j + 1] && gen[i][j + 1] != a[i][j + 1])
                    flag = 0;
            }
        }
    }
    if(flag)
        return 1;
    return 0;
}

void dfs(int x) {
    if(x == 5) {
        if(check()) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    printf("%d", gen[i][j]);
                }
                printf("\n");
            }
            exit(0);
        }
        return;
    }
    for(int i = 1; i <= 4; i++) {
        if(!inq[i]) {
            inq[i] = 1;
            fil[x] = i;
            dfs(x + 1);
            inq[i] = 0;
        }
    }
    return;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        char str = getchar();
        while(str < 33 || str > 126)
            str = getchar();
        int j = 0;
        while(str >= 33 && str <= 126) {
            a[i][++j] = str - '0';
            str = getchar();
        }
    }
    dfs(1);
    printf("0\n");
    return 0;
}
```



---

## 作者：gdf_yhm (赞：0)

[CF435E](https://www.luogu.com.cn/problem/CF435E)

### 思路

直接猜答案必然形如样例一：

```
13131
42424
31313
```

奇数行两种数字交替，偶数行两种数字交替。每行哪种数字先无所谓。

而 WA14 是因为有这样的情况：

```
1234
3412
```

将行列交换也可以。构造的时候不用枚举所有情况，只用找出奇数行和偶数行分别存在哪些数字，再把没有出现的数字分给奇数行和偶数行。

### code

```cpp
int n,m,a[maxn][maxn],b[maxn][maxn];
char c[maxn];
bool vis[5];
void change(){
	for(int i=1;i<=max(n,m);i++){
		for(int j=1;j<=max(n,m);j++)b[i][j]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)b[j][i]=a[i][j];
	}
	for(int i=1;i<=max(n,m);i++){
		for(int j=1;j<=max(n,m);j++)a[i][j]=0;
	}
	swap(n,m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=b[i][j];
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++)a[i][j]=c[j]-'0',vis[a[i][j]]=1;
	}
	bool flag=1;
	int p1=0,p2=0,p3=0,p4=0;
	for(int i=1;i<=n;i+=2){
		for(int j=1;j<=m;j++)if(a[i][j]){
			if(p1&&p1!=a[i][j]){
				if(!p2)p2=a[i][j];
				if(p2!=a[i][j])flag=0;
			}
			if(!p1)p1=a[i][j];
		}
	}
	for(int i=2;i<=n;i+=2){
		for(int j=1;j<=m;j++)if(a[i][j]){
			if(a[i][j]==p1||a[i][j]==p2)flag=0;
			if(p3&&p3!=a[i][j]){
				if(!p4)p4=a[i][j];
				if(p4!=a[i][j])flag=0;
			}
			if(!p3)p3=a[i][j];
		}
	}
	if(!flag){
		change();
		p1=0,p2=0,p3=0,p4=0;
		for(int i=1;i<=n;i+=2){
			for(int j=1;j<=m;j++)if(a[i][j]){
				if(p1&&p1!=a[i][j]){
					if(!p2)p2=a[i][j];
					if(p2!=a[i][j]){printf("0\n");return ;}
				}
				if(!p1)p1=a[i][j];
			}
		}
		for(int i=2;i<=n;i+=2){
			for(int j=1;j<=m;j++)if(a[i][j]){
				if(a[i][j]==p1||a[i][j]==p2){printf("0\n");return ;}
				if(p3&&p3!=a[i][j]){
					if(!p4)p4=a[i][j];
					if(p4!=a[i][j]){printf("0\n");return ;}
				}
				if(!p3)p3=a[i][j];
			}
		}
	}
	if(!p1){
		for(int i=1;i<=4;i++)if(!vis[i]){p1=i,vis[i]=1;break;}
	}
	if(!p2){
		for(int i=1;i<=4;i++)if(!vis[i]){p2=i,vis[i]=1;break;}
	}
	if(!p3){
		for(int i=1;i<=4;i++)if(!vis[i]){p3=i,vis[i]=1;break;}
	}
	if(!p4){
		for(int i=1;i<=4;i++)if(!vis[i]){p4=i,vis[i]=1;break;}
	}
	for(int i=1;i<=n;i+=2){
		bool fl=0;
		for(int j=1;j<=m;j++)if(a[i][j]){
			fl=1;
			for(int k=2-(j&1);k<=m;k+=2){
				if(a[i][k]&&a[i][k]!=a[i][j]){printf("0\n");return ;}
				a[i][k]=a[i][j];
			}
			for(int k=(j&1)+1;k<=m;k+=2){
				if(a[i][k]==a[i][j]){printf("0\n");return ;}
				a[i][k]=p1+p2-a[i][j];
			}
			break;
		}
		if(!fl)for(int j=1;j<=m;j++)a[i][j]=((j&1)?p1:p2);
	}
	for(int i=2;i<=n;i+=2){
		bool fl=0;
		for(int j=1;j<=m;j++)if(a[i][j]){
			fl=1;
			for(int k=2-(j&1);k<=m;k+=2){
				if(a[i][k]&&a[i][k]!=a[i][j]){printf("0\n");return ;}
				a[i][k]=a[i][j];
			}
			for(int k=(j&1)+1;k<=m;k+=2){
				if(a[i][k]==a[i][j]){printf("0\n");return ;}
				a[i][k]=p3+p4-a[i][j];
			}
			break;
		}
		if(!fl)for(int j=1;j<=m;j++)a[i][j]=((j&1)?p3:p4);
	}
	if(!flag)change();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%lld",a[i][j]);printf("\n");
	}
}
```

---

