# Cosmic Tables

## 题目描述

给定一个 $n\times m$ 的矩阵与 $k$ 次操作，每次操作有以下三种类别：

- 交换第 $x_i$ 列与第 $y_i$ 列；
- 交换第 $x_i$ 行与第 $y_i$ 行；
- 查询位于第 $x_i$ 行第 $y_i$ 列的数。

## 样例 #1

### 输入

```
3 3 5
1 2 3
4 5 6
7 8 9
g 3 2
r 3 2
c 2 3
g 2 2
g 3 2
```

### 输出

```
8
9
6
```

## 样例 #2

### 输入

```
2 3 3
1 2 4
3 1 5
c 2 1
r 1 2
g 1 3
```

### 输出

```
5
```

# 题解

## 作者：wmrqwq (赞：3)

# 原题链接

[CF222B Cosmic Tables](https://www.luogu.com.cn/problem/CF222B)

# 题目简述

给定一个 $n\times m$ 的矩阵与 $k$ 次操作，每次操作有以下三种类别：

- 交换第 $x_i$ 列与第 $y_i$ 列；
- 交换第 $x_i$ 行与第 $y_i$ 行；
- 查询位于第 $x_i$ 行第 $y_i$ 列的数。

输入的第一行有三个整数 $n,m,k$，分别表示该矩阵的行数，列数与操作个数。

接下来 $k$ 行，每行输入一个字符 $s_i$ 和两个整数 $x_i$，$y_i$。

- 若 $s_i$ 为 `c`，则交换第 $x_i$ 列与第 $y_i$ 列；
- 若 $s_i$ 为 `r`，则交换第 $x_i$ 行与第 $y_i$ 行；
- 若 $s_i$ 为 `g`，则查询此时位于第 $x_i$ 行第 $y_i$ 列的数。


对于每个 $s_i=$ `g`，输出查询的结果。


# 解题思路

首先输入 $n,m,k$ 和这个 $n$ 行 $m$ 列的矩阵,然后分别用两个数组来分别存储每个数字分别在几行几列，当交换时，直接交换这两个数即可。

注意，这个题一定不能用暴力模拟，不然会像我一样：
![](https://cdn.luogu.com.cn/upload/image_hosting/7n3eyibg.png)

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010][1010],x2[1010],y2[1010],n,m,k,x,y;//a数组存储矩阵，x2数组存储矩阵中的每个数所在的行，y2数组存储矩阵中的每个数所在的列
char c;
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		x2[i]=i;//记录每个数所在的行
		for(int j=1;j<=m;j++)
		{
			y2[j]=j;
			scanf("%d",&a[i][j]);//记录每个数所在的列
		}
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%s %d %d",&c,&x,&y);
		if(c=='c') 
			swap(y2[x],y2[y]);//交换两个数的列
		if(c=='r')
			swap(x2[x],x2[y]);//交换两个数的行
		if(c=='g')
			printf("%d\n",a[x2[x]][y2[y]]);//输出矩阵中的x行y列的数
	}
	return 0;
}
```


---

## 作者：Rosmarinus (赞：3)

## 题目分析

定义输入矩阵为 $a$，$hang_i$ 表示现在的第 $i$ 行对应这原来的第 $hang_i$ 行，$lie_i$ 表示现在的第 $i$ 列对应这原来的第 $lie_i$ 列。

初始化时 $hang_i=i,lie_i=i$。

每次交换的时候交换 $hang_x,hang_y$ 或 $lie_x,lie_y$ 即可，输出时输出 $a_{hang_x,lie_y}$。

详情见代码。

## AC 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1100][1100], hang[1100], lie[1100];
int main()
{
	int n, m, k, x, y;
	char c;
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i ++)
	{
		hang[i] = i;
		for(int p = 1; p <= m; p ++)
		{
			lie[p] = p;
			scanf("%d", &a[i][p]);
		}
	}
	for(int i = 1; i <= k; i ++)
	{
		scanf(" %c %d %d", &c, &x, &y);
		if(c == 'c') swap(lie[x], lie[y]);
		else if(c == 'r') swap(hang[x], hang[y]);
		else printf("%d\n", a[hang[x]][lie[y]]);
	}
	return 0;
}
```

说句题外话，CF222B，真是好题号。

-------------

Written by $\operatorname{Rosmarinus}$.

希望能对您有所帮助。


---

## 作者：LYqwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF222B)

# 题目大意

给定一个 $n \times m$ 的矩阵 $a$，进行 $k$ 次操作，有如下三种操作：

- 交换第 $x_i$ 列与第 $y_i$ 列。
- 交换第 $x_i$ 行与第 $y_i$ 行。
- 查询 $a_{x_i,y_i}$ 的数。

# 思路

真的很让人震惊，$3$ 秒的时限，暴力 + 快读 + 不用 `endl` = $AC$。

对于每次交换操作，只需 $\mathcal{O}(n)$ 的时间复杂度即可：

- 对于交换第 $x_i$ 列与第 $y_i$列：$i$ 从 $1$ 遍历到 $n$，每次交换第 $i$ 行第 $x_i$ 列与第 $i$ 行第 $y_i$ 列，就能完成这次操作。
- 对于交换第 $x_i$ 行与第 $y_i$ 行：同上，只不过 $i$ 从 $1$ 到 $m$，因为有 $m$ 列，每次交换第 $x_i$ 行第 $i$ 列与第 $y_i$ 行第 $i$ 列即可。

暴力代码很好写，就是卡常太难了（doge。

我一向不太喜欢暴力，于是又想出一种操作 $\mathcal{O}(1)$ 时间的方法：再定义两个数组 $row$ 和 $col$，分别表示交换后的行和列对应原来的哪一行哪一列。$row_i$ 表示交换后的第 $i$ 行对应原来的第几行，$col_i$ 也是同理，只不过是列。

来看具体操作如何进行：

- 初始化：$row_i=i$，$col_i=i$，因为刚开始每行每列对应的就是本身嘛。
- 交换第 $x_i$ 列与第 $y_i$列：直接交换 $col_{x_i}$ 和 $col_{y_i}$ 即可，第 $x_i$ 列和第 $y_i$ 列直接交换为对方。
- 交换第 $x_i$ 行与第 $y_i$ 行：同上，交换 $row_{x_i}$ 和 $row_{y_i}$。
- 查询 $a_{x_i,y_i}$：输出 $a_{col_{x_i},row_{y_i}}$ 即可。

嗯，快多了，~~也不用卡常了~~。

# 代码

## 暴力解法

```cpp
#include <iostream>
using namespace std;
int n,m,k,x,y,a[1005][1005];
char c;

// 没有快读，就会看到令人满意的TLE！暴力竟然卡过去了/jk
inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

int main(){
	cin >> n >> m >> k;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			a[i][j]=read();
		}
	}
	while(k--){
		c=getchar(); // 这里 cin 也会 TLE（暴力好难卡过去/kk）
		x=read(),y=read();
		switch(c){
			case 'c': // 交换 x 列与 y 列
				for(int i=1; i<=n; i++){
					swap(a[i][x],a[i][y]); // 直接交换第 i 行第 x 个数与第 i 行第 x 个数
				}
				break;
			case 'r': // 交换 x 行与 y 行
				for(int i=1; i<=m; i++){ // 注意是 1~m 而不是 1~n
					swap(a[x][i],a[y][i]); // 直接交换第 x 行第 i 个数与第 y 行第 i 个数
				}
				break;
			case 'g': // 查询
				cout << a[x][y];
				puts(""); // 换行用 endl 太慢了/kk又不想在cout后面接'\n'所以...
				break;
			default: break;
		}
	}
	return 0;
}
```

## 快速解法

```cpp
#include <iostream>
using namespace std;
int n,m,k,x,y,a[1005][1005];
int row[1005],col[1005]; // row 表示对应的行，col 表示对应的列
char c;

inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

int main(){
	// 前面输入什么的懒得改了/kk
	cin >> n >> m >> k;
	for(int i=1; i<=n; i++) row[i]=i; // 初始化行和列
	for(int i=1; i<=m; i++) col[i]=i;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			a[i][j]=read();
		}
	}
	while(k--){
		c=getchar();
		x=read(),y=read();
		switch(c){
			case 'c': // 交换 x 列与 y 列
				swap(col[x],col[y]);
				break;
			case 'r': // 交换 x 行与 y 行
				swap(row[x],row[y]);
				break;
			case 'g': // 查询
				cout << a[row[x]][col[y]];
				puts("");
				break;
			default: break;
		}
	}
	return 0;
}
```

---

## 作者：_easy_ (赞：2)

# 思路
发现 $k$ 最大只有 $10^5$，时限 $\texttt{3}$ 秒早够了，便想出了下面这种模拟的方法。

我们用两个数组来存储每行和每列执行操作前的数字，在执行操作时只需要交换对应的数组中的数字就行了。但是注意：输入量可能会很大，时限 $\texttt{3}$ 秒也可能会 $\texttt{T}$，需要用 $\texttt{scanf}$ 来优化（快读也行，但是 $\texttt{scanf}$ 足够了）。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[1005][1005],h[1005],l[1005];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		h[i]=i;//初始化
		for(int j=1;j<=m;j++){
			l[j]=j;//初始化
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=k;i++){
		char aa;
		int x,y;
		scanf(" %c%d%d",&aa,&x,&y);//
		if(aa=='c'){
			swap(l[x],l[y]);//交换列
		}else if(aa=='r'){
			swap(h[x],h[y]);//交换行
		}else{
			printf("%d\n",a[h[x]][l[y]]);
		}
	}
	return 0;
}
```

---

## 作者：墨忧 (赞：2)

## 思路
古语有云：暴力出奇迹，这道题给我们整整 3 秒的充足时间，那为什么不直接暴力做法呢？

二维数组存矩阵，对于每次操作直接暴力交换行列，每次查询直接输出对应的元素即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005][1005],n,m,k,x,y;
char ch;
inline int read()//快读 
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch && ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void swap(int &a,int &b)//自己写的swap貌似比内置的swap快一些，不过内置的也能过 
{
	int t=a;
	a=b;
	b=t;
}
inline void exchange1(int x,int y)//暴力交换列 
{
	for(int i=1;i<=n;i++) swap(a[i][x],a[i][y]);
}
inline void exchange2(int x,int y)//暴力交换行 
{
	for(int i=1;i<=m;i++) swap(a[x][i],a[y][i]);
}
int main()
{
	n=read();
	m=read();
	k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=read();//读入矩阵 
	for(int i=1;i<=k;i++)
	{
		ch=getchar();//用scanf也能过，getchar会更快，但是用cin必定 T 飞 
		x=read();
		y=read();
		if(ch=='c') exchange1(x,y);
		if(ch=='r') exchange2(x,y);
		if(ch=='g') cout<<a[x][y]<<'\n';
		//前人曾经说过：慢的不是cout，是endl，cout的输出速度并不比printf慢多少 
	}
	return 0;
} 
```


---

## 作者：cff_0102 (赞：1)

因为每次操作只是交换两行或者两列，交换行时不影响一个数在哪一列，交换列是也不会影响它所在的行数，而且每次查询只查询一个坐标的位置，所以可以尝试直接去记录这一行对应原来矩阵的行和这一列对应的原来矩阵的列。在查询现在 $a_{i,j}$  的值的时候，直接找到这个位置对应原来矩阵的位置，然后输出原来位置上的数即可。

每次操作时，两行/列对应的原来的行/列会互换。用两个数组 $h_i,l_j$ 分别记录下当前的行/列对应原来的行/列，查询时就直接输出 $a_{h_i,l_j}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1145][1145], h[1145], l[1145];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		h[i]=i;
		for(int j=1;j<=m;j++){
			l[j]=j;
			cin>>a[i][j];
		}
	}//预处理及输入
	for(int i = 1; i <= k; i ++){
		char c;
		int x,y;
		cin>>c>>x>>y;
		if(c=='c') swap(l[x],l[y]);
		else if(c=='r')swap(h[x],h[y]);
		else cout<<a[h[x]][l[y]]<<endl;//见上面的解析
	}
	return 0;
}
```

~~最后吐槽一下这道题的题号~~。

---

## 作者：Vibration886 (赞：0)

### [CF222B Cosmic Tables](https://www.luogu.com.cn/problem/CF222B)

## 题意

给定一个 $n\times m$ 的矩阵与 $k$ 次操作，每次操作有以下三种类别：

- 若 $s_i$ 为 "c"，交换第 $x_i$ 列与第 $y_i$ 列；

- 若 $s_i$ 为 "r"，交换第 $x_i$ 行与第 $y_i$ 行；

- 若 $s_i$ 为 "g"，查询位于第 $x_i$ 行第 $y_i$ 列的数并输出。

## 思路

虽然时限 $3$ 秒，但还是要用```scanf()```和```printf()```来优化，避免 TLE。

有两种方法可供选择：

假设 $m$ 为这个矩阵。

- 第一种：$r$ 数组记录每次换完后的行，$c$ 数组记录每次换完后的列，每次输出矩阵对应 $r$ 数组的行与 $c$ 数组对应列的数即可。

- 第二种，按照题意模拟，交换矩阵 $m$ 中的行和列，每次输出矩阵对应行对应列的数即可。

## AC代码：

这里使用第一种方法。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int mp[1005][1005],r[1005],c[1005];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		r[i]=i;
		for(int j=1;j<=m;j++)
		{
			c[j]=j;
			scanf("%d",&mp[i][j]);
		}
	}
	for(int i=1;i<=k;i++)
	{
		char op;
		int x,y;
		scanf(" %c%d%d",&op,&x,&y);
		if(op=='c')
		{
			swap(c[x],c[y]);
		}
		else if(op=='r')
		{
			swap(r[x],r[y]);
		}
		else
		{
			printf("%d\n",mp[r[x]][c[y]]);
		}
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路

这道题很显然不能暴力，可能会被卡常，所以就可以用一种更加快速的做法来避免卡常。

先用 $H_i$ 来代表这一行现在是存的开始的第几行的数，同理可以用$L_i$ 来代表列。

在交换时只用交换 $H_x$ 和 $H_y$ 和 $L_x$ 和 $L_y$ 即可，最后直接用 $H_x$ 和 $L_y$ 来查询。

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1100;
int L[N],H[N],a[N][N],q,n,m;
int main(){
	scanf("%d%d%d",&n,&m,&q); //输入
	for(int i=1;i<=n;i++){
		H[i]=i; // 初始化为自己（行） 
		for(int j=1;j<=m;j++){
			L[j]=j; // 初始化为自己（列） 
			scanf("%d",&a[i][j]); // 输入 
		} 
	} 
	while(q--) {//操作次数 
		char c;
		int x,y;
		cin>>c>>x>>y;
		if(c=='c') swap(L[x],L[y]); // 交换列
		else if(c=='r') swap(H[x],H[y]); // 交换行  
		else printf("%d\n",a[H[x]][L[y]]); // 查询
	}
	return false; // 结束自己罪恶的一生
}
```


---

## 作者：duchengjun (赞：0)

# 题意

给你矩阵的行数 $n$、列数 $m$ 与操作个数 $k$。

每次操作有以下三种类别：

- 交换第 $x_i$ 列与第 $y_i$ 列；

- 交换第 $x_i$ 行与第 $y_i$ 行；

- 查询位于第 $x_i$ 行第 $y_i$ 列的数。

# 分析

暴力需要卡常，但是这题有一个更简单和快速的解法。

因为每次交换一行或一列，所以可以用 $h_i$ 和 $l_i$ 维护矩阵的变换。

### 初始化

$h_i$ 和 $l_i$ 的初始化都是 $i$。

### 变换

因为 $h_x$ 和 $l_y$ 分别存的是原来矩阵的位置，所以查询时就输出 $a[h_x][l_y]$ 即可。

变换则就直接交换 $h_x$ 和 $h_y$ 的值或直接交换 $l_x$ 和 $l_y$ 的值即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//此处为快读代码
const int N=1e3+10;
int n,m,k;
int a[N][N];
int x,y;
char c;
int h[N],l[N];
int main(void){
	read_(n,m,k);
	for(int i=1;i<=n;++i)h[i]=i;
	for(int i=1;i<=m;++i)l[i]=i;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			read_(a[i][j]);
	for(int i=1;i<=k;++i){
		read_(c,x,y);
		if(c=='r')swap(h[x],h[y]);
		if(c=='c')swap(l[x],l[y]);
		if(c=='g')write_(a[h[x]][l[y]],"\n");
	}
	write_("\n");
	return 0;
}


```


---

## 作者：Coros_Trusds (赞：0)

什么神仙题号$\verb!qwq!$。

刚开始没注意到数据范围和题目编号是 `B`，打了半小时的某码农数据结构然后调啊调，调到心态崩了于是翻题解瞅瞅。

看到都是简单 $\mathcal{O}(nm)$ 时疯掉了 ~~，请推理全过程~~。

----
直接切入正题。

令 $h_i$ 表示原先的第 $i$ 行经过变换后的所在行号，$l_i$ 则是列。

于是对于交换行列操作直接交换这两个数组就好了，即直接 $\operatorname{swap}$。

输出可以做到 $\mathcal{O}(1)$，也就是输出 $mp[h_x][l_y]$。

可以发现瓶颈在输入部分。

-----
代码：

```cpp
//2021/12/22

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=1005;

int mp[ma][ma];

int h[ma],l[ma];

int n,m,k;

int main(void)
{
	n=read(),m=read(),k=read();
	
	for(register int i=1;i<=n;i++)
	{
		h[i]=i;
		
		for(register int j=1;j<=m;j++)
		{
			l[j]=j;
			
			mp[i][j]=read();
		}
	}
	
	while(k--)
	{
		char opt[3];scanf("%s",opt);
		
		int x=read(),y=read();
		 
		if(opt[0]=='c')
		{
			swap(l[x],l[y]);
		}
		
		else if(opt[0]=='r')
		{
			swap(h[x],h[y]);
		}
		
		else
		{
			printf("%d\n",mp[h[x]][l[y]]);
		}
	}
	
	return 0;
}
```

---

## 作者：ForeverCC (赞：0)

首先，这题的时间限制很大，但是暴力做法需要一些技巧，这里介绍的是更优的方法。

我们看到这里一整行一整列的交换。每次交换可以只交换各行各列的标号即可。

用 $x_i$ 表示原标号为 $i$，现在为 $x_i$。

同样的，用 $y_i$ 表示原标号为 $i$，现在为 $y_i$。

这样，原下表为 $(a,b)$ 的格子，现下标为 $(x_a,y_b)$。

代码：

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
int n,m,k,a[N][N];
int x[N],y[N];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)x[i]=i;
    for(int i=1;i<=m;i++)y[i]=i;
    for(int i=1;i<=k;i++){
        char t[5];
        int X,Y;
        scanf("%s%d%d",t,&X,&Y);
        if(t[0]=='c')swap(y[X],y[Y]);
    	else if(t[0]=='r')swap(x[X],x[Y]);
        else printf("%d\n",a[x[X]][y[Y]]);
    }
    return 0;
}
```


---

## 作者：Harry_Meng (赞：0)

# CF222B Cosmic Tables题解

## 题目分析
拿到这个题一看——我天，这什么玩意？全是英文，再往下一翻，啊这，原来有翻译啊。

给定一个矩阵和若干次操作，然后接下来若干行，每行输入一个字符和两个数，然后依据[题意](https://www.luogu.com.cn/problem/CF222B)进行模拟即可。

因为这个题的时间很充足，所以**暴力出奇迹**，直接模拟即可通过。

#### 方法：我们可以开一个二维数组存矩阵，题目中每输入一次，我们就对这一次操作直接**暴力**交换行列，然后在每次查询时直接输出对应的查询结果就可以。


## 注意事项
1.输入输出量较大，建议使用**快读**。

2.输出别忘换行哦。

##  _Code_ 

```cpp
#include<iostream>
#include<cstdio>
#define N 1005   //设置数组大小，题目中说n,m≤1000，故设N=1005
using namespace std;
int n,m,k,x,y;
char c;
int a[N][N];   //a数组存矩阵
int h[N],l[N];   //h数组存行，l数组存列，即现在的第i行对应原来的h[i]行，现在的第i列对应原来的第l[i]列。
long long read(){     //由于输入量过大，最好使用快读
	long long x=0,f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-'){
		ch=getchar();
	}
	if(ch=='-'){
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);   //使用位运算，速度更快 
		ch=getchar();
	}
	return x*f;
}
int main(){
	n=read();   //快读读入数据
	m=read();
	k=read();
	for(int i=1;i<=n;i++){     //初始化+存矩阵
		h[i]=i;
		for(int j=1;j<=m;j++){
			l[j]=j;
			a[i][j]=read();
		}
	}
	for(int i=1;i<=k;i++){
		scanf("%c",&c);   //这个地方用c=getchar()也可以
		x=read();
		y=read();
		if(c=='c'){   //判断+暴力交换
			swap(l[x],l[y]);
		} 
		else if(c=='r'){
			swap(h[x],h[y]);
		} 
		else{
			printf("%d\n",a[h[x]][l[y]]);
		} 
	}
	return 0;
}
```


---

## 作者：fuwei123 (赞：0)

首先考虑暴力模拟。

非常好写，每次读到一次交换操作就枚举这一行（列），交换即可。但显而易见，时间复杂度太高，无法通过本题。

考虑优化。

其实，我们只需要记录数组 $fx$，$fy$。

$fx_i$ 表示交换后第 $i$ 行当前实际对应第几行，$fy_i$ 同理。

当读入到交换第 $i$ 行和第 $j$ 行的操作时，我们就交换 $fx_i$ 和 $fx_j$，表示这次操作后，原来的第 $i$ 行实际是原来的第 $j$ 列。读入交换列的操作，同理。

当读入到输出第 $i$ 行第 $j$ 列的操作时，只需要输出 $a_{fx_i, fy_j}$ 即可。其中 $a$ 为读入进来的数组。

最后，记得**预处理** $fx$ 和 $fy$。

注意：本题输入输出卡的很严，必须用**关闭流同步**的 cin/cout，scanf/printf 或是普通的快读快写都会 T 掉。

下面给出 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m, q, a[1005][1005], fx[1005], fy[1005];//fx[x]:询问中 的x实际对应a中的行,fy同理 

inline void swp(int &a, int &b){
	int tmp = b;
	b = a, a = tmp;
	return;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			cin >> a[i][j];

	for(int i = 1;i <= n;i++)fx[i] = i;
	for(int i = 1;i <= m;i++)fy[i] = i;//预处理fx，fy
	while(q--){
		int x, y;
		char opt;
		cin >> opt >> x >> y;
		if(opt == 'c'){
			swp(fy[x], fy[y]);
		}else if(opt == 'r'){
			swp(fx[x], fx[y]);
		}else{
			cout << a[fx[x]][fy[y]] << "\n";// "\n"比endl要快
		}
	}
	return 0;
}
```


---

## 作者：Big_Brain (赞：0)

先上[题目传送门](https://www.luogu.com.cn/problem/CF222B)。

## 题意简述

给定一个大小为 ${n}\times{m}$ 的矩阵，对矩阵进行以下 $3$ 种操作：

1. 交换矩阵的第 $x$ 列和第 $y$ 列；

2. 交换矩阵的第 $x$ 行和第 $y$ 行；

3. 输出矩阵的第 $x$ 行的第 $y$ 个字符。


## 思路总结

刚刚看见这道题，就打了一个大暴力。

![](https://cdn.luogu.com.cn/upload/image_hosting/nnygj6yg.png)

喜提 TLE！因此，这一题不能打暴力。（~~实际上多试几次还是可以过的~~）

### 非暴力正解

定义两个数组 $r$ 和 $c$，用来保存经过变化后，原来的行和列分别在哪里；在查询矩阵第 $x$ 行第 $y$ 个字符时，只需要直接输出矩阵的第 $r_{x}$ 行第 $c_{y}$ 个即可。

## 最后，上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//int的快读模板
{
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline string readstr(){//string的快读模板
    char ch=getchar();string x;
    while(ch==' '||ch=='\n')ch=getchar();
    while(ch!=' '&&ch!='\n')x+=ch,ch=getchar();return x;
}
inline void write(int x,char s='\n')//int的输出模板
{
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;while(tp--) putchar(t[tp]+48);putchar(s);
}
int r[1010],c[1010];
int s[1050][1050];
int main(){
    int n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)r[i]=i;//初始化行、列指向的位置
    for(int i=1;i<=m;i++)c[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            s[i][j]=read();//输入
    while(k--){
        char ch=getchar();int x=read(),y=read();
        if(ch=='c')swap(c[x],c[y]);//将x列、y列指向的位置交换
        if(ch=='r')swap(r[x],r[y]);//同上，将x行、y行指向的位置交换
        if(ch=='g')write(s[r[x]][c[y]]);
    }
}//珍爱生命，拒绝抄袭
```
~~但是我还是要吐槽一下这一题的题号。~~ 

---

