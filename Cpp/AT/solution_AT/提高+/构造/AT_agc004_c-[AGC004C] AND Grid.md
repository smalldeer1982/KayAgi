# [AGC004C] AND Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc004/tasks/agc004_c

高橋君と青木君は、縦 $ H $ マス、横 $ W $ マスの透明な方眼紙を $ 1 $ 枚ずつ手に入れました。

高橋君は、自分の方眼紙のいくつかのマスを赤く塗りました。 このとき、赤いマスは上下左右に連結でした。 つまり、どの赤いマスからどの赤いマスへも、上下左右に隣り合う赤いマスのみを辿って行き来できます。

また、青木君は、自分の方眼紙のいくつかのマスを青く塗りました。 このとき、青いマスは上下左右に連結でした。

その後、高橋君と青木君は、$ 2 $ 枚の方眼紙をそのままの向きでぴったりと重ねました。 すると、赤いマスと青いマスが重なるマスのみが紫色になって見えました。

紫色のマスの配置が、長方形に並ぶ文字 $ a_{ij} $ ($ 1\ <\ =i\ <\ =H $，$ 1\ <\ =j\ <\ =W $) として与えられます。 上から $ i $ 行目、左から $ j $ 列目のマスが紫色ならば、$ a_{ij} $ は `#` であり、紫色でなければ、$ a_{ij} $ は `.` です。 このとき、**最も外側のマスは紫色でない**ことが保証されます。 つまり、$ i=1，H $ または $ j=1，W $ ならば、$ a_{ij} $ は `.` です。

問題文の条件を満たすような、赤いマスの配置と青いマスの配置のペアをひとつ求めてください。 解は必ず存在することが示せます。

## 说明/提示

### 制約

- $ 3\ <\ =H，W\ <\ =500 $
- $ a_{ij} $ は `#` または `.` である。
- $ i=1，H $ または $ j=1，W $ ならば、$ a_{ij} $ は `.` である。
- $ a_{ij} $ のうち少なくとも $ 1 $ つは `#` である。

### Sample Explanation 1

例えば、次のような赤いマスの配置と青いマスの配置のペアが考えられます。 !\[\](/img/agc/004/gatbantar/C\_1.png)

### Sample Explanation 2

例えば、次のような赤いマスの配置と青いマスの配置のペアが考えられます。 !\[\](/img/agc/004/gatbantar/C\_2.png)

## 样例 #1

### 输入

```
5 5
.....
.#.#.
.....
.#.#.
.....```

### 输出

```
.....
#####
#....
#####
.....

.###.
.#.#.
.#.#.
.#.#.
.....```

## 样例 #2

### 输入

```
7 13
.............
.###.###.###.
.#.#.#...#...
.###.#...#...
.#.#.#.#.#...
.#.#.###.###.
.............```

### 输出

```
.............
.###########.
.###.###.###.
.###.###.###.
.###.###.###.
.###.###.###.
.............

.............
.###.###.###.
.#.#.#...#...
.###.#...#...
.#.#.#.#.#...
.#.#########.
.............```

# 题解

## 作者：精神小火 (赞：12)

一个不用保证边界没有颜色的做法。(但是四个角落有颜色还是不行)

![](https://cdn.luogu.com.cn/upload/image_hosting/7utaadqk.png)

只需要像图中那样，把一个贪吃蛇的形状染上色，再把读入的有颜色的格子给两个都染上色即可。

为什么是对的呢，因为这两个图形当中，任何一个空格子染上色，仍然是四连通的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define uu unsigned
#define scanf abc=scanf
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)
#define forg(i,x) for(int i=fir[x];i;i=nxt[i])
int abc;
typedef pair<int,int>pii;
typedef long long ll;
typedef uu long long ull;
typedef vector<int>VI;
inline int rd(int l,int r){return rand()%(r-l+1)+l;}

const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,vs[503][503];char s[503][503],s1[503][503],s2[503][503];

int main(){
    cin>>n>>m;for(int i=1;i<=n;++i)cin>>s[i]+1;
    for(int i=0;i<=n+1;++i)vs[i][0]=vs[i][m+1]=3;for(int i=0;i<=m+1;++i)vs[0][i]=vs[n+1][i]=3;
    int x1=1,y1=1,x2=n,y2=m,ls=0;
    while(1){
        vs[x1][y1]=1,vs[x2][y2]=2;
        int k=-1;
        if(!vs[x1+dx[ls]][y1+dy[ls]])k=ls;else for(int o=0;o<4;++o)if(!vs[x1+dx[o]][y1+dy[o]])assert(k==-1),k=o;
        if(k==-1)break;
        x1+=dx[k],y1+=dy[k],x2-=dx[k],y2-=dy[k];ls=k;
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)s1[i][j]=s2[i][j]='.';
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(vs[i][j]==1)s1[i][j]='#';else s2[i][j]='#';
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(s[i][j]=='#')s1[i][j]=s2[i][j]='#';
    for(int i=1;i<=n;++i)cout<<s1[i]+1<<endl;puts("");
    for(int i=1;i<=n;++i)cout<<s2[i]+1<<endl;
    return 0;
}
```

---

## 作者：BFqwq (赞：9)

乍一看感觉没有思路，然而我们发现了一个条件：

边界没有 `#`。

于是这个题就变得非常简单了。

我们让第一张图，第一列全部是 `#`，第二张图最后一列全部是 `#`；

然后对于中间的部分，奇数行在第一张图全部染色，偶数行在第二张图全部染色。

这样得到的图应该是这样的（以 $5\times 5$ 为例）：

```
####.   ....#
#....   #####
####.   ....#
#....   #####
####.   ....#
```

然后对于原图中的 `#`，在另一张图也染上色就 ok 啦~

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register long long x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
char get(){
    char ch=getchar();
    while (ch!='.'&&ch!='#') ch=getchar();
    return ch;
}
const int maxn=505;
char a[maxn][maxn],b[maxn][maxn];
signed main(){
	int n=read(),m=read();
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char ch=getchar();
			while(ch!='.' && ch!='#') ch=getchar();
			a[i][j]=b[i][j]=ch;
		}
	for(int i=1;i<=n;i++){
		a[i][1]='#',b[i][m]='#';
		if(i&1)
			for(int j=2;j<=m-1;j++) a[i][j]='#';
		else
			for(int j=2;j<=m-1;j++) b[i][j]='#';
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) putchar(a[i][j]);
		puts("");
	}
	puts("");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) putchar(b[i][j]);
		puts("");
	}
	return 0; 
}
```

---

## 作者：ljqqq123✅ (赞：4)

其实这题不难，~~像我这种蒟蒻都会~~,主要是理解题意。

**大致题意**：题目给出一个由“ # ”和“ . ”组成的矩阵，让你给出两个大小相同且“ # ”是相连的矩阵，且这两个矩阵的“ * ”重叠部分刚好是给出的这个矩阵。(答案不唯一，只要满足题目要求就行)~~（其实这题应该打个spj标签的）~~

**主要思路**：题目中给到："题目保证边界上不会被涂色"，即：边界中不会有“ * ”，那我们就可以以此来连接两个图中的“ # ”，你可以像这样先把外围搞定（上，下两侧的暂时不画，后面会提到）：
```
(以5*5为例)
①   ②
#....  ....#
#....  ....#
#....  ....#
#....  ....#
#....  ....#

```
然后在把内围用几根线线连起来，像这样：（~~叠词词，恶心心~~）
```
(你可以看成是左边奇数行，右边偶数行填满，但要注意最左边和最右边两列不能同时为“ * ”，不然就违背题目了)
①      ②
####.  ....#
#....  .####
####.  ....#
#....  .####
####.  ....#

```
然后在依据题目给的“ # ”的位置把两个矩阵相对应的位置换成“ # ”即可。
```
（样例1）
①      ②
####.  ....#
##.#.  .####
####.  ....#
##.#.  .####
####.  ....#
```
~~然后是最期待的代码环节~~

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char r[1001][1001],b[1001][1001];
char a;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a;
			r[i][j]=a;
			b[i][j]=a;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i%2&&j!=m)r[i][j]='#';
			else if(j==1)r[i][j]='#';
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i%2==0&&j!=1)b[i][j]='#';
			else if(j==m)b[i][j]='#';
		}
	}
	putchar('\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<r[i][j];
		}
		putchar('\n');
	}
	putchar('\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<b[i][j];
		}
		putchar('\n');
	}
	return 0;
}
```

就这样，拜拜(～￣▽￣)～

---

## 作者：installb (赞：4)

## 前言  
当你没思路的时候 注意运用那些玄学的条件 它们有时候是解题(或帮助你想出思路)的关键  
**no outermost cell is purple**  

## 正文  
这是一道**多解输出任意一种可行解**的题目 所以不用管样例输出 ~~这道题目谁知道这个输出是怎么弄出来的~~  一般用正解是不会得到那种东西的  

无论测试数据如何 我们其实都可以构造一种通解  
要求对于红色或蓝色 每一格均**沿四连通拓宽一格** 各自都可以覆盖除了最外面一圈以外的所有方块  

**奇数行红色 偶数行蓝色** 可以做到  
怎么保证它们联通呢  
用那个神奇的条件  
**最左边一列全红 最右边一列全蓝**  
**此题完结。**  

代码是为了表现代码的本质很短很多都是重复故意压成这样
## code:  
```cpp
#include <map>
#include <list>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL n,m;
char p[505][505] = {0},k;
int r[505][505] = {0},b[505][505] = {0};
// r[i][j] b[i][j] 分别存i,j是否需要染红、蓝

int main(){
	cin >> n >> m;
	for(int i = 1;i <= n;i ++){ for(int j = 1;j <= m;j ++){ cin >> k; if(k == '#') r[i][j] = b[i][j] = p[i][j] = 1; // 紫色都染 } }
	for(int i = 1;i <= n;i ++) r[i][1] = b[i][m] = 1; // 染第一、最后一列
	for(int i = 1;i <= n;i ++){ for(int j = 2;j < m;j ++){ if(i & 1) r[i][j] = 1; else b[i][j] = 1; // 奇偶行染色 } }
	for(int i = 1;i <= n;i ++){ for(int j = 1;j <= m;j ++) printf("%c",r[i][j] ? '#' : '.'); printf("\n"); } printf("\n");
	for(int i = 1;i <= n;i ++){ for(int j = 1;j <= m;j ++) printf("%c",b[i][j] ? '#' : '.'); printf("\n"); }
    // 这两段输出
	return 0;
}
```

---

## 作者：MY（一名蒟蒻） (赞：4)

[原题传送门](https://www.luogu.com.cn/problem/AT2043)

不知道为什么翻译要把关于颜色的描述去掉，我认为这样并没有使题意得到简化。

这里再翻译一遍。

## 题面简述

给你一个$H×W$的网格图，有一些格子涂了紫色。

请你构造出两个大小相等的网格图，其中一个部分格子涂了红色，且四联通，另一个部分格子涂了蓝色，且四联通。

要求原网格紫色的位置必须对应于两个网格中的红和蓝，其余都不能同时涂红和蓝。**保证边界没有紫色。**

---
输出样例就是在放屁，如果这题谁能写出一种正解输出是样例的话这题就应该名垂青史了。

题目保证有解的话，我们留意到一个细节，**边界没有紫色**。

要保证四联通，最简单的当然是整个图都是一种颜色。但是这题有两种，所以考虑五五开。

但是直接从中间把这个图剪开一半一半的话，很难保证四联通。

那么想到可以两种颜色一行一行穿插，然后在**绝对不会有紫色的边界**各弄一列。最后的成品就像两个梳子卡在一起。

具体理解请看代码。

## Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n,m;
char a[510][510],red[510][510],blue[510][510];

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf(" %c",&a[i][j]);//目标矩阵
	for(int i=1;i<=n;i++) {red[i][m]=blue[i][1]='.'; red[i][1]=blue[i][m]='#';}//染一列
	for(int i=1;i<=n;i++)
		for(int j=2;j<m;j++)
		{
			if(i&1) {red[i][j]='#'; blue[i][j]='.';}
			else {red[i][j]='.'; blue[i][j]='#';}
			if(a[i][j] == '#') red[i][j]=blue[i][j]='#';
		}//按照奇偶和数据给定紫色涂剩下的
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) printf("%c",red[i][j]);
		puts("");
	}
	puts("");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) printf("%c",blue[i][j]);
		puts("");
	}	//直接输出
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
时间复杂度$\text{O}(n^2)$，可以通过本题。

## $\text{Thank you for your reading!}$
您的点赞和评论是对作者最大的支持！

---

## 作者：听取MLE声一片 (赞：3)

简单构造题。

本题解中称填上或填满为填入 `#`。

不难发现，如果将一整行全部填满，那么会保证上行本行下行都是连通的。

我们设两张图分别为图一和图二，图一和图二开始都存着原图。

然后自然想到图一奇数行填满，图二偶数行填满。

这有个问题，是你填的奇数行偶数行可能不连通。

这也好办，我们把图一的第一列填满，图二的最后一列填满。注意填行的时候不能填首尾。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=510;
int n,m;
char a[N][N],b[N][N];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++)
			b[i][j]=a[i][j];
	}
	for(int i=1;i<=n;i+=2)
		for(int j=2;j<m;j++)
			a[i][j]='#';
	for(int i=1;i<=n;i++)
		a[i][1]='#';
	for(int i=2;i<=n;i+=2)
		for(int j=2;j<m;j++)
			b[i][j]='#';
	for(int i=1;i<=n;i++)
		b[i][m]='#';
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%c",a[i][j]);
		putchar('\n');
	}
	putchar('\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%c",b[i][j]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：风浔凌 (赞：2)

（题目翻译发到讨论区了~~）  
这个题刚一看还是蛮难的，
但是仔细想想——要求只输出任意一种情况啊！所以——这奇葩题啊qwq......  
完全不需要和样例一样啊  
考虑一下，将红蓝间隔染色（比如说红色染奇数行，蓝色染偶数行），最后为了确保它的连通性，第一列染成红色，最后一列染成蓝色即可！

综上，代码如下：
```c
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
char r[600][600],b[600][600],a[600][600];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i+=2)
    	for(int j=1;j<=m;j++)
    		r[i][j]='#';
    for(int i=2;i<=n;i+=2)
    	for(int j=1;j<=m;j++)
    	{
            r[i][j]='.';
    	}
    for(int i=2;i<=n;i+=2)
    	for(int j=1;j<=m;j++)
    		b[i][j]='#';
    for(int i=1;i<=n;i+=2)
    	for(int j=1;j<=m;j++)
    	{
            b[i][j]='.';
    	}
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char cur;
            cin>>cur;
            if(cur=='#')
            {
                r[i][j]='#';
                b[i][j]='#';
            }
        }
    }
    for(int i=1;i<=n;i++)
        r[i][1]='#',b[i][1]='.';
    for(int i=1;i<=n;i++)
        r[i][m]='.',b[i][m]='#';
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
          cout<<r[i][j];
        cout<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
          cout<<b[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：冰糖鸽子 (赞：1)

**Update：矩阵出了一些小问题，麻烦管理员再看一下**

比较水的一道构造吧，看清题目条件就差不多了

----

看题，发现边界一圈都是不填色的，所以可以通过边界实现四联通。

尝试构造两个长这样的互补的矩阵：

```
        _____
|_____       |
|       _____|
|_____       |
|       _____|

```
也就是对于第一个矩阵，涂第一列和所有偶数行（但要留出最后一列），第二个矩阵则涂最后一列和所有奇数行（同样留出第一列）

当然两个矩阵可以交换，或者整个转一半变成涂最上面和最下面的。

这两个矩阵叠在一起便是一个完整的矩阵了，且没有重复的格子。构造完之后，对于原矩阵中每个涂了色的格子，在两个矩阵的相应位置上也涂上色，即是答案。

这是因为两个矩阵连通不上的地方都在边界，而边界并不会被涂。

代码：

```cpp

// Problem: AT2043 [AGC004C] AND Grid
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2043
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define M 600
int n,m;
char c[M][M],a[M][M],b[M][M];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		a[i][1]='#';
		b[i][m]='#';
	}
	for(int i=1;i<=n;i+=2)
	{
		for(int j=2;j<m;j++)
		{
			a[i][j]='#';
			b[i+1][j]='#';//这里可能会涂出去一个，但没关系，输出时不会考虑到
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=='#') a[i][j]=b[i][j]='#';
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<(a[i][j]=='#'?'#':'.');
		}
		cout<<endl;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<endl;//小细节
		for(int j=1;j<=m;j++)
		{
			cout<<(b[i][j]=='#'?'#':'.');
		}
	}
	return 0;
}
```

---

## 作者：bifanwen (赞：0)

[博客园同步](https://www.cnblogs.com/bifanwen/p/15887281.html)

[原题链接](https://www.luogu.com.cn/problem/AT2043)

简要题意：

给定一个 $n \times m$ 的字符矩阵 $p$，仅由 `.`（表示未涂色） 和 `#`（表示涂色） 构成。保证边界无色。

要求构造出两个 $n \times m$ 的字符矩阵（也由 `.` 和 `#` 构成）$a,b$，满足 $a$ 和 $b$ 均涂色的部分恰为 $p$，且均为一个连通块。

$n,m \leq 500$.（可强化至 $n,m \leq 5 \times 10^3$.）

典型构造题，以样例 $n = 5$ 为例：

注意到 **边界无色** 这个条件。所以我们可以考虑一种从边界出发的染色方式。

即先把 $a,b$ 染成这样：

```
####.
#....
####.
#....
####.
```

```
....#
.####
....#
.####
....#
```

注意到，下面对于每一个，出现在 $p$ 中而未出现在 $a,b$ 中的格子，直接染即可。因为一定是一个连通块。

时间复杂度：$\mathcal{O}(nm)$.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e2 + 1;

int n, m;
char a[N][N], b[N][N];

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++) {
		if(i % 2 == 1 && j < m || i % 2 == 0 && j == 1) a[i][j] = '#';
		else a[i][j] = '.';
		if(i % 2 == 0 && j > 1 || i % 2 == 1 && j == m) b[i][j] = '#';
		else b[i][j] = '.';
 	}
 	
 	char s[N];
 	for(int i = 1; i <= n; i++) {
 		scanf("%s",s);
 		for(int j = 0 ; j < m; j++)
 			if(s[j] == '#') a[i][j + 1] = b[i][j + 1] = '#';
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) putchar(a[i][j]);
		puts("");
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) putchar(b[i][j]);
		puts("");
	}
}

```

---

## 作者：Ebola (赞：0)

边界全白？那不是随便乱搞……

对于新网格一，把奇数列全部染黑，第一排和最后一排不要染，这样所有原本就有的黑色，就至少与一列构成了四联通。再把第一排全部染黑，所有列就四联通了，搞定！

对于新网格二，奇数列染不得了，那就染偶数列，再把最后一排染黑，搞定！

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c!='#'&&c!='.') c=Get();
        while(c=='#'||c=='.') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
}

using namespace IO;
const int N=510;
char A[N][N],B[N][N],C[N][N];
int n,m;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            B[i][j]=C[i][j]='.';
    for(int i=1;i<=n;i++)
    {
        reads(A[i]);
        for(int j=1;j<=m;j++)
            if(A[i][j]=='#') B[i][j]=C[i][j]='#';
    }
    for(int i=2;i<n;i++)
        for(int j=1;j<=m;j+=2)
            B[i][j]='#';
    for(int i=2;i<n;i++)
        for(int j=2;j<=m;j+=2)
            C[i][j]='#';
    for(int i=1;i<=m;i++)
        B[1][i]=C[n][i]='#';
    for(int i=1;i<=n;i++)
        B[i][m+1]='\0',prints(B[i]+1);
    putc('\n');
    for(int i=1;i<=n;i++)
        C[i][m+1]='\0',prints(C[i]+1);
    flush();
    return 0;
}
```

---

