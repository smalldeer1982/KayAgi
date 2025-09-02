# Get Your Wish

## 题目背景

![Get Your Wish](https://mivik.gitee.io/image/nurture/get_your_wish.png)

> So, tell me how it felt when you walked on water
>
> Did you get your wish?

## 题目描述

Porter 在浅水上完成了他的 MV，但他很快发现了事情不对：他的话筒进水了。

Porter 的话筒内部的关键电子元件可以被看作一个 $n\times m$ 的二维平面。我们用一张 $n\times m$ 的字符画来表示 Porter 的话筒内部状况，其中有三种不同的字符：

- `.`：表示空位

- `x`：表示关键电子原件

- `o`：表示水滴

水滴会沿着重力方向一直流动，直到流出边界或者流到电子原件上。当水滴流到任意一个电子原件上时，Porter 的话筒就会坏掉。Porter 慌忙把话筒转过来，改变了话筒内部的重力方向。重力方向用四种字符之一表示：`^v<>`，分别对应上下左右。

Porter 想知道，在这种重力方向下，他的话筒过一会儿会不会 GG。

## 说明/提示


### 样例解释

样例一：第一行第二列的水滴向下流到了最后一行第二列的电子原件上，因此话筒坏掉了。

样例二：第二行第一列的水滴向右流到了第二行最后一列的电子原件上，因此话筒坏掉了。

样例三：第一行第二列的水滴直接向上流出话筒，因此 Porter 的话筒不会坏掉。

### 数据范围

对于全部数据，保证 $1\le n,m\le 100$，且输入数据合法。

Subtask 1 (10 pts)：话筒中没有 `x`（即电子原件）。

Subtask 2 (10 pts)：话筒中没有 `o`（即水滴）。

Subtask 3 (30 pts)：保证重力方向总是 `v`（向下）。

Subtask 4 (50 pts)：无特殊限制。


## 样例 #1

### 输入

```
3 3 v
.o.
...
xxx```

### 输出

```
GG```

## 样例 #2

### 输入

```
3 3 >
...
o.x
...```

### 输出

```
GG```

## 样例 #3

### 输入

```
3 3 ^
.o.
...
xxx```

### 输出

```
OK```

# 题解

## 作者：Mivik (赞：11)


[欢迎到我的博客查看](https://mivik.gitee.io/2021/solution/mivik-round-nurture-get-your-wish/)

## Subtask 1 & 2

直接输出 `OK` 即可。

## 满分做法

直接模拟即可。可以根据重力改变读入方式，实现会简短一些（吧？）

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/QF78nbzJyD/)


---

## 作者：Little_Cart (赞：8)

## 1. 题意简述

Porter 的话筒内部的关键电子元件可以被看作一个$n×m$的二维平面。

. ：表示空位

x ：表示关键电子原件

o ：表示水滴

水滴会沿着重力方向一直流动，直到流出边界或者流到电子原件上。Porter 想知道，在这种重力方向下，他的话筒过一会儿会不会 GG。会 输出“GG”（不输出引号），不会 输出“OK”（不输出引号）。

$1≤n,m≤100$

## 2. 题目简析

考点：模拟

时间复杂度：$ O(n^3) $（有点高）

先输入方阵，存在二维字符组中。

使用两个计数器，记录关键电子原件，水滴的个数。

若他们有一个为0，输出OK。（水滴为0不能湿，关键电子原件为0不能坏）

否则进行模拟，找到一个水滴就开始向重力方向寻找（推）。

找到电子原件输出GG，出边界就换一个水滴推。

到无水滴时输出OK。

## 3. 全代码 和 简单讲解


```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;
	char c;
	scanf("%d%d",&a,&b);
	cin>>c;
	char ch[a][b];
	int i,j,k,shui=0,jian=0;
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='o'){
				shui++;//记录个数 
			}
			if(ch[i][j]=='x'){
				jian++;
			}
		}
	}
	if(shui==0||jian==0){//如果有一个没有，输出OK 
		printf("OK");
	}
	else{
		for(i=0;i<a;i++){
		    for(j=0;j<b;j++){
			    if(ch[i][j]=='o'){//寻找水滴 
			    	if(c=='^'){
			    		for(k=i;k>=0;k--){//向上推 
			    			if(ch[k][j]=='x'){
			    				printf("GG");
			    			    return 0;//加快结束 
			    			}
			    		}
			    	}
			    	if(c=='v'){
			    		for(k=i;k<a;k++){//向下推 
			    			if(ch[k][j]=='x'){
			    				printf("GG");
			    			    return 0;
			    			}
			    		}
			    	}
			    	if(c=='<'){
			    		for(k=j;k>=0;k--){//向左推 
			    			if(ch[i][k]=='x'){
			    				printf("GG");
			    			    return 0;
			    			}
			    		}
			    	}
			    	if(c=='>'){
			    		for(k=j;k<b;k++){//向右推 
			    			if(ch[i][k]=='x'){
			    				printf("GG");
			    			    return 0;
			    			}
			    		}
			    	}
			    }
		    }
	    }
	    printf("OK");
	}
	return 0;
}
```

## 4. 小结

本题解使用C++，欢迎大佬指正或提出更佳方案！

---

## 作者：rui_er (赞：7)

题意很清楚了这里就不过多解释了，说一下思路：

一看题，感觉很多水滴的时候较难模拟下落过程，因此考虑根据给出的重力方向和电子元件反推。我们使用 $s_{i,j}$ 表示如果 $\left(i,j\right)$ 位置有水滴，是否会影响到电子元件。则以方向竖直向下为例，$s_{i,j}=s_{i,j+1}|\left(\text{当前位置有水滴}\right)$，其他三个方向以此类推，其中 $|$ 表示或，即两个条件中任一满足则为 $1$。

然后枚举整个 $n\times m$ 的图：如果存在水滴使对应位置的 $s_{i,j}=1$，则答案必定为 `GG`；若对于所有水滴对应位置的 $s_{i,j}$ 均为 $0$，则答案为 `OK`。

赛时代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 105;
//const char nxt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m, pos, s[N][N], ans = 0;
char mp[N][N], poss[N];

int main() {
	scanf("%d%d%s", &n, &m, poss+1);
	rep(i, 1, n) scanf("%s", mp[i]+1);
	pos = (poss[1] == 'v' ? 1 : (poss[1] == '<' ? 2 : (poss[1] == '^' ? 3 : 0)));
	if(!pos) rep(i, 1, n) per(j, m, 1) s[i][j] = s[i][j+1] | (mp[i][j] == 'x');
	else if(pos == 1) rep(j, 1, m) per(i, n, 1) s[i][j] = s[i+1][j] | (mp[i][j] == 'x');
	else if(pos == 2) rep(i, 1, n) rep(j, 1, m) s[i][j] = s[i][j-1] | (mp[i][j] == 'x');
	else rep(j, 1, m) rep(i, 1, n) s[i][j] = s[i-1][j] | (mp[i][j] == 'x');
	rep(i, 1, n) rep(j, 1, m) ans |= (s[i][j] && (mp[i][j] == 'o'));
	printf("%s\n", (char*[]){"OK", "GG"}[ans]);
    return 0;
}
```

---

## 作者：Lithium_Chestnut (赞：7)

这是一篇**大模拟**题解。

码量很长，但是基本都在重复，易懂。

思路很简单，最简单的想法就是先扫出棋盘内的水滴，然后根据方向把水滴会落到的地方做上标记。如果此时有电子零件所处的地方被标记了，那么就可以直接输出 `GG` 并结束程序，如果没有被标记的，最后直接输出 `OK` 即可。

这样的话，难点就落到了方向上。其实这个也并不难，给大家举个例子：

```
2 5 <
x.o..
.....
```

有了这个就很好推了。显然我们需要做上标记的地方（也就是水滴流过的地方）是：$(1,1),(1,2),(1,3)$（假设左上角为 $(1,1)$）。那么很快找到规律：

如果是左右流动，那么就找到水滴所在的行数，然后如果是左，那么列数从 $1$ 到水滴所在的列数做上标记；如果是右。那么列数从水滴所在的列数到 $m$ 做上标记。

如果是上下流动，那么就找到水滴所在的列数，然后如果是上，那么行数从 $1$ 到水滴所在的行数做上标记；如果是下，那么行数从水滴所在的行数到 $n$ 做上标记。

剩下就很好办了，话不多说，放代码；前面说的很明确了，代码就不加注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mark[101][101];
char c,s[101][101];
int read()
{
	int x=0,w=0;
	char ch=0;
	while(!isdigit(ch))
	{
		w|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return w?-x:x;
}
int main()
{
	n=read(),m=read();
	scanf("%c",&c);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) cin>>s[i][j];
	}
	if(c=='v')
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='o')
				{
					for(int k=i;k<=n;k++) mark[k][j]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='x')
				{
					if(mark[i][j]==1)
					{
						printf("GG");
						return 0;
					}
				}
			}
		}
		printf("OK");
		return 0;
	}
	else if(c=='^')
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='o')
				{
					for(int k=1;k<=i;k++) mark[k][j]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='x')
				{
					if(mark[i][j]==1)
					{
						printf("GG");
						return 0;
					}
				}
			}
		}
		printf("OK");
		return 0;
	}
	else if(c=='<')
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='o')
				{
					for(int k=1;k<=j;k++) mark[i][k]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='x')
				{
					if(mark[i][j]==1)
					{
						printf("GG");
						return 0;
					}
				}
			}
		}
		printf("OK");
		return 0;
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='o')
				{
					for(int k=j;k<=m;k++) mark[i][k]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='x')
				{
					if(mark[i][j]==1)
					{
						printf("GG");
						return 0;
					}
				}
			}
		}
		printf("OK");
		return 0;
	}
	return 0;
}
```


---

## 作者：xh39 (赞：2)

详细讲重力为```>```的情况,其他类似。

什么情况下元件才会被破坏?肯定左边要有水滴,这样才能流到该元件。

当左边没水的情况下,显然不会有任何水破坏到该元件,元件就保留了下来。

思路很简单,可是代码怎么实现呢?

对于每个元件,需查询左部有没有水滴。对于本题,$n<=100$,所以暴力$O(n\times m^{2})$可以解决,但介绍一个更好的办法,可以做到$O(n\times m)$。

对于每行,从左到右扫一遍。若碰见了水,就把一个临时变量标记为$1$,表示从这个点开始后面所有的元件都会坏掉,这个标记一直会保持到扫完整行。(扫下一行时得把这个变量置零)。若扫的过程中遇到了元件,并且标记为$1$,表示水可以流到这个元件。那么立刻输出``GG``。

若一直没有水碰到元件,那么就输出```OK```就可以了。

对于重力为其它的情况,改变扫描顺序即可,要顺着重力方向扫描,具体见代码。

```cpp
#include<iostream>
using namespace std;
char a[1005][1005];
int main(){
	int n,m,i,j;
	bool ykb;
	char fx;
	cin>>n>>m>>fx;
	for(i=0;i<n;i++){
		cin>>a[i];
	}
	if(fx=='^'){
		for(i=0;i<m;i++){ //逐列枚举。 
			ykb=0;
			for(j=n-1;j>=0;j--){
				if(a[j][i]=='o'){ //有水,后面的格子都会受影响。
					ykb=1;
				}
				if(a[j][i]=='x'&&ykb){ //有元件,并且前面有水。直接返回不可以。
					cout<<"GG";
					return 0;
				}
			}
		}
	}
	if(fx=='v'){
		for(i=0;i<m;i++){ //逐列枚举。 
			ykb=0;
			for(j=0;j<n;j++){
				if(a[j][i]=='o'){
					ykb=1;
				}
				if(a[j][i]=='x'&&ykb){
					cout<<"GG";
					return 0;
				}
			}
		}
	}
	if(fx=='<'){
		for(i=0;i<n;i++){ //逐行枚举。 
			ykb=0;
			for(j=m-1;j>=0;j--){
				if(a[i][j]=='o'){
					ykb=1;
				}
				if(a[i][j]=='x'&&ykb){
					cout<<"GG";
					return 0;
				}
			}
		}
	}
	if(fx=='>'){
		for(i=0;i<n;i++){ //逐行枚举。 
			ykb=0;
			for(j=0;j<m;j++){
				if(a[i][j]=='o'){
					ykb=1;
				}
				if(a[i][j]=='x'&&ykb){
					cout<<"GG";
					return 0;
				}
			}
		}
	}
	cout<<"OK"; //没有任何一个元件有问题,返回可以。
	return 0;
}
```

---

## 作者：Zoe_Granger (赞：2)

~~这个菜鸡难得打了比赛，当然要来水一波题解~~

思路：找出水滴的位置，使用一个 $O(n)$ 的循环看它会不会流到重要元件上。

个人认为这题的难点 ~~（也不是很难）~~ 在4个重力方向上，不过画一画图就能想明白了。具体细节看代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 105;

int n, m;
char c, s[MAXN][MAXN];
bool flag=1;

bool chk(int x, int y) //0:GG 1:OK
{
    if (c=='v') //重力方向向下，每次流动时所在行数+1，也就是x+1
    {
        for (int i=x; i<=n; i++)
            if (s[i][y]=='x')
                return false;
    }
    else if (c=='^') //重力方向向上，每次流动时所在行数-1，也就是x-1
    {
        for (int i=x; i>=1; i--)
            if (s[i][y]=='x')
                return false;
    }
    else if (c=='<') //重力方向向左，每次流动时所在列数+1，也就是y+1
    {
        for (int i=y; i>=1; i--)
            if (s[x][i]=='x')
                return false;
    }
    else //重力方向向右，每次流动时所在列数-1，也就是y-1
    {
        for (int i=y; i<=m; i++)
            if (s[x][i]=='x')
                return false;
    }
    return true;
}

int main() 
{
	cin >>n >>m >>c; //cin防止读入空格
	for (int i=1; i<=n; i++)
	    scanf ("%s", s[i]+1); //scanf小妙招
	
	for (int i=1; i<=n; i++)
	    for (int j=1; j<=m; j++)
	        if (s[i][j]=='o')
	            flag &= chk(i,j); //只要一次GG，所有都GG，使用&运算实现
	
	if (!flag)
	    puts("GG");
	else
	    puts("OK");
	return 0;
}
```


---

## 作者：2simon2008 (赞：2)

## 题目
**题目链接** [P7262 Get Your Wish](https://www.luogu.com.cn/problem/P7262)

**题意简述**：从水滴 `o` （可能有多个）位置开始，向规定方向走，会不会碰到标有 `x` 的格子。

## 思路
对于每一个水滴 `o` 向给定方向不停模拟，如果碰到 `x` 则返回 `GG `，如果到了边界都没有碰到 `x` ，那就下一个。直到最后尝试模拟每一个 `o` 都成功的话，输出 `OK`。

## 细节

### 1. 方向字符与变量数组下标的对应

这个要看我的数组 ，方向分别为右、下、左、上。

```cpp
int xx[4]= {0,1,0,-1},yy[4]= {1,0,-1,0};
```
对应的字符下标为`>`、`v`、`<`、`^`。

判断代码

```cpp
  if(c=='v') k=1;
  if(c=='^') k=3;
  if(c=='<') k=2;
  if(c=='>') k=0;
```

### 2. 水滴的模拟

因为看到水滴时，图并未读完整，所以先存储水滴。
存储后用while循环一个一个模拟。
```cpp
x[i]+=xx[k],y[i]+=yy[k];
```

如果遇到 `x` ，就可以输出 `GG` 然后走人了。

## 最终代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n,m,xx[4]= {0,1,0,-1},yy[4]= {1,0,-1,0},k,x[10005],y[10005],cnt;
char c,cc[205][205];
int main()
{
  cin>>n>>m>>c;
  for(register int i=1; i<=n; i++)
    for(register int j=1; j<=m; j++)
    {
      cin>>cc[i][j];
      if(cc[i][j]=='o') x[++cnt]=i,y[cnt]=j;
    }//输入并存储
  k=1;
  if(c=='^') k=3;
  if(c=='<') k=2;
  if(c=='>') k=0;//判断方向
  for(register int i=1; i<=cnt; i++)//一个一个模拟
  {
    while(x[i]>0&&x[i]<=n&&y[i]>0&&y[i]<=m)//当没有超出界限时
    {
      x[i]+=xx[k],y[i]+=yy[k];//移动
      if(cc[x[i]][y[i]]=='x')
      {
        printf("GG\n");//如果碰到x，输出GG
        return 0;
      }
    }
  }
  printf("OK\n");//模拟如果都成功，输出OK
  return 0;
}
```

------------


 **完结撒花！**

---

## 作者：D2T1 (赞：1)

比赛签到题，直接模拟，一些优化，Mivik最良心的题目

### 1、骗分

```
Subtask 1 (10 pts)：话筒中没有 x（即电子原件）。

Subtask 2 (10 pts)：话筒中没有 o（即水滴）。
```



前两个子任务要么只有电子元件，要么只有水滴，肯定不会GG，所以

```cpp
#include <iostream>
using namespace std;

int main(){
	cout << "OK";
	return 0;
}
```
$20pts$

### 2、暴力

纯模拟，每次循环移动一次，如果水滴与原件重合就GG，如果已经没有水滴就OK

```cpp
//U144730
#include <iostream>
using namespace std;
char a[105][105];
int t[10005][2];

int main(){
	int n,m,zz=0;
	char opt;
	cin >> n >> m >> opt;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			cin >> a[i][j];
			if(a[i][j]=='o')
				t[zz][0]=i,t[zz][1]=j,++zz;
		}
	}
	int kkksc03=zz;
	while(kkksc03){
		for(int i=0; i<zz; ++i){
			switch(opt){
				case '^':
					if(t[zz][1]!=0) --t[zz][1];
					else --kkksc03;
					break;
				case 'v':
					if(t[zz][1]!=m+1) ++t[zz][1];
					else --kkksc03;
					break;
				case '<':
					if(t[zz][0]!=0) --t[zz][0];
					else --kkksc03;
					break;
				default:
					if(t[zz][0]!=n+1) ++t[zz][0];
					else --kkksc03;
					break;
			} 
			if(a[t[zz][0]][t[zz][1]]=='x'){
				cout << "GG";
				return 0;
			}
		}
	}
	cout << "OK";
	return 0;
}
```
$10pts$，T飞，比骗分的还差

### 3、正解~~应该是~~

用一个二维数组存储整个矩阵，另一个二维数组存储每一个水滴的坐标，按照给定的方向从水滴位置找到边界，如果有零件就GG，全部找完没有GG就OK。

两重循环，第一层查水滴，第二层找原件

```cpp
//U144730
#include <iostream>
using namespace std;
char a[105][105];//存矩阵
int t[10005][2];//存水滴坐标

int main(){
	int n,m,zz=0;//zz为值存储在t数组中的位置
	char opt;
	cin >> n >> m >> opt;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			cin >> a[i][j];
			if(a[i][j]=='o')
				t[zz][0]=i,t[zz][1]=j,++zz;
		}
	}
	int kkksc03=zz;
	for(int zz=0; zz<kkksc03; ++zz){
		switch(opt){
			case '<':
				for(int i=t[zz][1]; i>0; --i)
					if(a[t[zz][0]][i]=='x'){
						cout << "GG";
						return 0;
					}
				break;
			case '>':
				for(int i=t[zz][1]; i<=m; ++i)
					if(a[t[zz][0]][i]=='x'){
						cout << "GG";
						return 0;
					}
				break;
			case '^':
				for(int i=t[zz][0]; i>0; --i)
					if(a[i][t[zz][1]]=='x'){
						cout << "GG";
						return 0;
					}
				break;
			default:
				for(int i=t[zz][0]; i<=n; ++i)
					if(a[i][t[zz][1]]=='x'){
						cout << "GG";
						return 0;
					}
				break;
		} 
	}
	cout << "OK";
	return 0;
}
```
AC。




---

## 作者：囧仙 (赞：0)

## 题目大意

- 有一个 $n\times m$ 的矩阵，其中第 $(i,j)$ 个格子上是水滴、空格或者零件。现在所有水滴向同一个方向（上下左右）移动，询问水滴是否会碰到零件。

## 题解

显然，一个水滴只会关系到这一行/这一列（取决于流动方向）的零件的安危。对于不同的方向，我们只需要改变枚举顺序就行了。

现在假设一个水滴在第 $x$ 行/列上流动。我们只需要考虑它前面是否存在零件即可。也就是说，我们能够再次根据流动方向调整枚举顺序，用一个临时的布尔变量 $f$ 存储当前有没有碰到零件。枚举的时候有三种情况：

- 遇到了空格，无事发生。

- 遇到了零件。 $f\gets \verb!true!$ 。

- 遇到了水滴。如果 $f=\verb!true!$ ，那么水滴会流经零件，直接输出 $\verb!GG!$ 并退出。否则水滴流走，无事发生。

顺便改变枚举顺序可能有点麻烦。但你可以根据流动方向旋转矩阵，这样只要处理一种枚举顺序了。~~但是由于作者太懒就没这么写。~~

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=100+3;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
char rdc(){
    char c; while(!isgraph(c=getchar())); return c;
}
int n,m,t; char W[MAXN][MAXN];
int main(){
    n=qread(),m=qread(),t=rdc(),t=(t=='^'?1:t=='v'?2:t=='<'?3:4);
    up(1,n,i) up(1,m,j) W[i][j]=rdc();
    if(t<=2){
        up(1,m,i){
            bool f=0;
            if(t==2){ up(1,n,j) if(f&&W[j][i]=='x') goto nxt; else if(W[j][i]=='o') f=true;}
            if(t==1){ dn(n,1,j) if(f&&W[j][i]=='x') goto nxt; else if(W[j][i]=='o') f=true;}
        }
    } else {
        up(1,n,i){
            bool f=0;
            if(t==4){ up(1,m,j) if(f&&W[i][j]=='x') goto nxt; else if(W[i][j]=='o') f=true;}
            if(t==3){ dn(m,1,j) if(f&&W[i][j]=='x') goto nxt; else if(W[i][j]=='o') f=true;}
        }
    }
    puts("OK");return 0; nxt: puts("GG");
    return 0;
}
```

---

## 作者：novax (赞：0)

#### 题意

给你一个 $N \times M$ 大小的字符矩阵，其中有些点是水滴，有些是电子元件，问当所有水滴都向某一方向流动时，是否会有水滴流到电子元件上。

#### 做法

定义 $f_{i,j}$ 为：若点 $(i,j)$ 是水滴，是否会导致元件损坏。

按照题目中的方向的相反方向进行递推，当遇到某位置为水滴且 $f_{i,j} =1$ 时，就输出``GG``；若一直执行到最后都没有出现问题，则输出``OK``。复杂度最坏情况下为 $O(nm)$，~~然而这题数据范围太小区分不开与暴力的复杂度差距。~~

#### 代码

```cpp
#include <cstdio>
int N,M;
char a[110][110];
int f[110][110];//表示i,j位置若是水滴，是否会损坏元件 1为会 
int main()
{
	char s[5];
	scanf("%d%d",&N,&M);
	scanf("%s",s);
	int i,j,k;
	for(i=1;i<=N;i++)
		scanf("%s",a[i]+1);
	switch(s[0])
	{
		case 'v':
			for(j=1;j<=M;j++)
			{
				for(i=N;i>=1;i--)
				{
					f[i][j]=f[i+1][j];//按照相反方向倒序递推 
					if(f[i][j]&&a[i][j]=='o')//若遇到水滴，判断是否会损坏 
					{
						printf("GG\n");
						return 0;
					}
					if(!f[i][j]&&a[i][j]=='x')//若遇到元件，记录 
						f[i][j]++;
				}
			}
			break;
		case '^':
			for(j=1;j<=M;j++)
			{
				for(i=1;i<=N;i++)
				{
					f[i][j]=f[i-1][j];
					if(f[i][j]&&a[i][j]=='o')
					{
						printf("GG\n");
						return 0;
					}
					if(!f[i][j]&&a[i][j]=='x')
						f[i][j]++;
				}
			}
			break;	
		case '<':
			for(i=1;i<=N;i++)
			{
				for(j=1;j<=M;j++)
				{
					f[i][j]=f[i][j-1];
					if(f[i][j]&&a[i][j]=='o')
					{
						printf("GG\n");
						return 0;
					}
					if(!f[i][j]&&a[i][j]=='x')
						f[i][j]++;
				}
			}
			break;
		case '>':
			for(i=1;i<=N;i++)
			{
				for(j=M;j>=1;j--)
				{
					f[i][j]=f[i][j+1];
					if(f[i][j]&&a[i][j]=='o')
					{
						printf("GG\n");
						return 0;
					}
					if(!f[i][j]&&a[i][j]=='x')
						f[i][j]++;
				}
			}
	}
	printf("OK\n");
}
```


---

## 作者：sycqwq (赞：0)

一道简单的模拟题

可以先找出水滴，然后模拟水滴下落，用一个数组标记出下落中所经过的格子，标为危险格子

然后再找出关键电子原件，判断是不是在危险格子，只要有一个在，那就是“GG”

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char x;
char a[1005][1005];
int bk[1005][1005];//bk数组标记危险格子
int main(){
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='o')
			switch(x)//模拟下落
			{
				case '<':
				{
					for(int k=j;k>=1;k--)
						bk[i][k]=1;//标记
					break;
				}
				case '>':
				{
					for(int k=j;k<=m;k++)
						bk[i][k]=1;
					break;
				}
				case 'v':
				{
					for(int k=i+1;k<=n;k++)
						bk[k][j]=1;
					break;
				}
				case '^':
				{
					for(int k=i;k>=1;k--)
						bk[k][j]=1;
					break;
				}
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='x'&&bk[i][j])//判断关键电子原件在不在危险格子
			{
				cout<<"GG";
				return 0;
			}
		}
	cout<<"OK";
	return 0;
}

```

---

## 作者：honey_ (赞：0)

## 读题   
  简述：判断水滴 $o$ 开始，沿重力方向下落是否会碰到话筒 $x$。
## 简洁思路   
  题目告诉我们 $1\le n,m\le 100$，因此我们这道题就可以用模拟
## 具体思路
  读入数据于 $Map$ 数组，将是 $o$ 的元素的坐标记录，接着再沿着重力方向判断是否碰到 $x$。注：$o$ 不止一个！   
# code :   

```cpp
#include <cstdio> 
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
char Map[105][105];
struct node
{
    int x,y;
}tmp;
queue < node > q;
int main()
{
    int n,m,nr,nc,sr,sc;
    char a;
    scanf("%d %d %c",&n,&m,&a);
    switch(a)  //根据a来判断重力方向
    {
        case '^':
            nr=-1,nc=0;
            break;
        case 'v':
            nr=1,nc=0;
            break;
        case '<':
            nr=0,nc=-1;
            break;
        case '>':
            nr=0,nc=1;
            break;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>Map[i][j];
            if(Map[i][j]=='o') tmp.x=i,tmp.y=j,q.push(tmp);  //记录
        }
    while(!q.empty())
    {
        tmp=q.front();
        q.pop();
        sr=tmp.x,sc=tmp.y;
        while(1)
        {
            if(sr<0 || sr>n-1 || sc<0 || sc>m-1) break; // 判断越界
            if(Map[sr][sc]=='x') {printf("GG\n");return 0;}  //碰到x就直接输出GG,结束程序
            sr+=nr,sc+=nc; //更新位置
        }
    }
    printf("OK\n");  //否则没有碰到输出OK
    return 0;
}
```

---

## 作者：miao5 (赞：0)

###**题面**

给你一个 $n*m$ 的图($1<=n,m<=100$)，以及一个方向 c。求所有为水滴的点在这个方向上有没有为零件的点。


###**思路**

输入的时候统计每一个为水滴的点的坐标，然后分上、下、左、右进行讨论，暴力枚举是否有为零件的点即可。

###**代码**

~~代码有点长，请谅解，毕竟我很弱。~~

```cpp
#include<iostream>
using namespace std;
char a[105][105];
int cnt;
int x[10005],y[10005];
int n,m;
void do_it1(){//向上 
	for(int i=1;i<=cnt;i++){//枚举每一个水滴 
		for(int j=x[i];j;j--){//行减少列不变 
			if(a[j][y[i]]=='x'){
				cout<<"GG"<<endl;
				return;
			}//如果有零件，输出"GG" 
		}
	}
	cout<<"OK"<<endl;//如果没有输出"OK" 
}
void do_it2(){//向下 
	for(int i=1;i<=cnt;i++){ 
		for(int j=x[i];j<=n;j++){//行增加列不变 
			if(a[j][y[i]]=='x'){
				cout<<"GG"<<endl;
				return;
			}
		}
	}
	cout<<"OK"<<endl;//同上 
}
void do_it3(){//向左 
	for(int i=1;i<=cnt;i++){
		for(int j=y[i];j;j--){//行不变列减少 
			if(a[x[i]][j]=='x'){
				cout<<"GG"<<endl;
				return;
			}
		}
	}
	cout<<"OK"<<endl;//同上 
}
void do_it4(){//向右 
	for(int i=1;i<=cnt;i++){
		for(int j=y[i];j<=m;j++){//行不变列增加 
			if(a[x[i]][j]=='x'){
				cout<<"GG"<<endl;
				return;
			}
		}
	}
	cout<<"OK"<<endl;//同上 
}
int main(){
	char c;
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//输入 
			if(a[i][j]=='o'){
				x[++cnt]=i;
				y[cnt]=j;
			}//统计所有为水滴的点的坐标 。 
		}
	}
	if(c=='^') do_it1();
	else if(c=='v') do_it2();
	else if(c=='<') do_it3();
	else if(c=='>') do_it4();//上下左右大力讨论 。 
}
```


~~ 管理大大求过~~~~

---

## 作者：EuphoricStar (赞：0)

简单的模拟。

大致思路就是找出所有的电子元件，如果电子元件垂直或水平方向会有水滴滑落下来，则直接输出 `GG` 并退出。

如果遍历了所有元件与水滴都没有退出程序，代表没有一滴水滴会滴到电子元件上，输出 `OK`。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, dmin[110], dmax[110];
char cmap[110][110], dir;

int main()
{
    ios::sync_with_stdio(0);
    for (int i = 0; i < 110; ++i) dmin[i] = INT_MAX, dmax[i] = INT_MIN;
    cin >> n >> m >> dir;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            cin >> cmap[i][j];
            if (cmap[i][j] == 'x')
            {
                if (dir == '^' || dir == 'v')
                {
                    dmin[j] = min(dmin[j], i);
                    dmax[j] = max(dmax[j], i);
                }
                else
                {
                    dmin[i] = min(dmin[i], j);
                    dmax[i] = max(dmax[i], j);
                }
            }
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (cmap[i][j] == 'o')
            {
                bool f;
                if (dir == '^') f = dmin[j] < i;
                else if (dir == 'v') f = dmax[j] > i;
                else if (dir == '<') f = dmin[i] < j;
                else f = dmax[i] > j;
                if (f) return cout << "GG", 0;
            }
    return cout << "OK", 0;
}
```


---

## 作者：skyfly886 (赞：0)

这是一道并不复杂的模拟题

### 来说说思路

- 开一个二维字符数组，存储这个二维平面

- 遍历整个字符数组，如果发现水滴，就按照方向去寻找有无关键电子元件，找到后立刻 return 0

由于本题的数据量很小（ $1≤n,m≤100$ ），所以就可以用暴力的方法来愉快地通过这道题啦！

# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

char c[105][105]; 

int main(){
	int n,m;
	cin>>n>>m;
	char to;
	cin>>to;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>c[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(c[i][j]=='o'){
				if(to=='^'){//向上
					int t=i;
					while(t>=0){
						if(c[t][j]=='x'){
							cout<<"GG";
							return 0;
						}
						t--;
					}
				}
				if(to=='v'){//向下
					int t=i;
					while(t<=n){
						if(c[t][j]=='x'){
							cout<<"GG";
							return 0;
						}
						t++;
					}
				}
				if(to=='<'){//向左
					int t=j;
					while(t>=0){
						if(c[i][t]=='x'){
							cout<<"GG";
							return 0;
						}
						t--;
					}
				}
				if(to=='>'){//向右
					int t=j;
					while(t<=m){
						if(c[i][t]=='x'){
							cout<<"GG";
							return 0;
						}
						t++;
					}
				}
			}
		}
	}
	cout<<"OK";
	return 0;
}
```


---

## 作者：HYdroKomide (赞：0)

# **正文：**
## 思路
本比赛中唯一一道比较简单的模拟题。数据比较小，所以可以进行三层循环模拟。首先找到一滴水 $o$ ，然后根据重力方向进行循环查找是否在其路径中存在重要电路 $x$ 。如果发现就直接输出 $GG$ ，如果循环到最后就输出 $OK$。
## 程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char c,a[101][101];
bool ok(){
    if(c=='v'){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(a[i][j]=='o'){        //找到o了就开始找x
                    for(int k=i;k<=n;k++)
                        if(a[k][j]=='x')   //如果找到x就直接返回false
                            return false;
                }
        return true;                   //循环到最后返回true
    }
    //后面的代码与以上几乎相同
    if(c=='^'){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(a[i][j]=='o'){
                    for(int k=i;k>=0;k--)
                        if(a[k][j]=='x')
                            return false;
                }
        return true;
    }
    if(c=='<'){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(a[i][j]=='o'){
                    for(int k=j;k>=0;k--)
                        if(a[i][k]=='x')
                            return false;
                }
        return true;
    }
    if(c=='>'){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(a[i][j]=='o'){
                    for(int k=j;k<=m;k++)
                        if(a[i][k]=='x')
                            return false;
                }
        return true;
    }
    return true;
}
int main(){
    cin>>n>>m>>c;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    if(ok())cout<<"OK";
    else    cout<<"GG";
    return 0;
}
```
# **THE END**

---

## 作者：PLDIS (赞：0)

# 大模拟
我们可以开一个数组：**对于每一行或每一列（取决于方向），我们可以存里面离边缘最远的水珠的列号或行号（和上面相反）**，因为这样不会错过零件，也不会浪费空间。如果没有水珠，就存 $-1$。

然后，我们可以枚举每一行或每一列（取决于方向）存下来的水珠的列号或行号（还是和上面相反），**查找它会不会流到一个电子元件上**。如果找到，就输出"GG"并结束程序。

如果没有水珠能到达电子元件，就输出"OK"。

### 注意点：
- 我们枚举过程中，可能会**先枚举列号再枚举行号**，在判断该格是否为电子元件时**不能写坐标时先写列号再写行号**！！！
- 方向相反，枚举列/行号时得**倒过来枚举**，比如方向是上，得**从这个水珠往上**枚举，方向是下，得**从这个水珠往下**枚举！！！

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    char c;
    cin >> n >> m >> c;
    char g[n][m];
    int v[max(n, m)]= {0};
    memset(v, -1, sizeof(int) * max(n, m));
    for(int i = 0;i < n;i++){
        bool temp = true;
        for(int j = 0;j < m;j++){
            cin >> g[i][j];
            if(g[i][j] == 'o' && (c == '^' || c == 'v') && temp){
                v[j] = i;
                temp = false;
            }
            else if(g[i][j] == 'o' && temp){
                v[i] = j;
                temp = false;
            }
        }
    }
    if(c == 'v'){
        for(int i = 0;i < m;i++){
            if(v[i] == -1){
                continue;
            }
            //从距离边缘最远的水珠开始向下枚举
            for(int j = v[i] + 1;j < n;j++){
                //判断
                if(g[j][i] == 'x'){
                    cout << "GG";
                    return 0;
                }
            }
        }
        //都流不到电子元件上
        cout << "OK";
        return 0;
    }
    else if(c == '^'){
        for(int i = 0;i < m;i++){
            if(v[i] == -1){
                continue;
            }
            for(int j = v[i] - 1;j >= 0;j--){
                if(g[j][i] == 'x'){
                    cout << "GG";
                    return 0;
                }
            }
        }
        cout << "OK";
        return 0;
    }
    else if(c == '>'){
        for(int i = 0;i < n;i++){
            if(v[i] == -1){
                continue;
            }
            for(int j = v[i] + 1;j < m;j++){
                if(g[i][j] == 'x'){
                    cout << "GG";
                    return 0;
                }
            }
        }
        cout << "OK";
        return 0;
    }
    else{
        for(int i = 0;i < n;i++){
            if(v[i] == -1){
                continue;
            }
            for(int j = v[i] - 1;j >= 0;j--){
                if(g[i][j] == 'x'){
                    cout << "GG";
                    return 0;
                }
            }
        }
        cout << "OK";
        return 0;
    }
    return 0;
}
```

---

## 作者：ＹｉＣｈｅ (赞：0)

这题真的很不错，是普及/提高选手可以练习的高质量题

我比赛的时候RE卡了很久...

导致我T234都没看 (~~反正看了也不会做~~)



------------

第一眼看上去像个搜索

~~但由于我太蒻了，不会搜索~~

所以我根据题意打了个暴力...

如果是dalao的话可以直接跳过了

## 以下为AC CODE
```cpp
#include<iostream>//头文件 

using namespace std;//命名空间 

long long n,m;//int也可，表示要输入n，m两个整型数 
char gravity;//根据题意，重力，为一个字符 
char a[1005][1005]={};//表示话筒内部的关键电子元件 
bool flag1=false,flag2=false,flag3=false,flag4=false,flag5=false; //用于判断话筒是否坏掉 

int main()//主函数 
{
	cin>>n>>m>>gravity;//根据题意，依次输入n(n行),m(m列),gravity(重力)
	for(int i=1;i<=n;i++)//输入n行 
	{
		for(int j=1;j<=m;j++)//输入m列 
		{
			cin>>a[i][j];
		}
	}
	if(zhong=='v')//判断重力情况 如果为下 
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='o') //判定水滴的位置 
				{
					for(int k=1;k<=n;k++)//定义一个k，用于判断x和o 
					{
						if(a[i+k][j]=='x')//i+k为往下k行，如果这个位置为x 
						{
							flag2=true;//那么我们就将他标记为成立，也就是话筒会坏掉 
						}
					}
				}
			}
		}
		if(flag2==true)//如果成立，话筒会坏掉 
		{
			cout<<"GG"<<endl;//则输出GG 
			return 0;
		}
		else
		{
			cout<<"OK"<<endl;//不成立则输出OK 
			return 0;
		}
	}
	//以下与上面同理，只需判断重力的不同情况即可 
	else if(zhong=='^')
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='o')
				{
					for(int k=1;k<=i/*记住这里一定要用i，不然数组下标很可能是负数，导致RE*/;k++)
					{
						if(a[i-k][j]=='x')
						{
							flag3=true;
						}
					}
				}
			}
		}
		if(flag3==true)
		{
			cout<<"GG"<<endl;
			return 0;
		}
		else
		{
			cout<<"OK"<<endl;
			return 0;
		}
	}
	else if(zhong=='>')
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='o')
				{
					for(int k=1;k<=m;k++)
					{
						if(a[i][j+k]=='x')
						{
						flag4=true;
						}
					}
				}
			}
		}
		if(flag4==true)
		{
			cout<<"GG"<<endl;
			return 0;
		}
		else
		{
			cout<<"OK"<<endl;
			return 0;
		}
	}
	else 
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='o')
				{
					for(int k=1;k<=j/*记住这里一定要用j，不然数组下标很可能是负数，导致RE*/;k++)
					{
						if(a[i][j-k]=='x')
						{
							flag5=true;
						}
					}
				}
			}
		}
		if(flag5==true)
		{
			cout<<"GG"<<endl;
			return 0;
		}
		else
		{
			cout<<"OK"<<endl;
			return 0;
		}
	}
	return 0;//结束返回值 
}
```

**欢迎指正注释中的错误**

---

