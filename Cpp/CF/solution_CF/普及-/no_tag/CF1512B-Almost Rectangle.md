# Almost Rectangle

## 题目描述

There is a square field of size $ n \times n $ in which two cells are marked. These cells can be in the same row or column.

You are to mark two more cells so that they are the corners of a rectangle with sides parallel to the coordinate axes.

For example, if $ n=4 $ and a rectangular field looks like this (there are asterisks in the marked cells):

  $$\begin{matrix}
.&.&*&.\\
.&.&.&.\\
*&.&.&.\\
.&.&.&.\\
\end{matrix}$$

Then you can mark two more cells as follows

 $$\begin{matrix}
*&.&*&.\\
.&.&.&.\\
*&.&*&.\\
.&.&.&.\\
\end{matrix} $$

If there are several possible solutions, then print any of them.

## 样例 #1

### 输入

```
6
4
..*.
....
*...
....
2
*.
.*
2
.*
.*
3
*.*
...
...
5
.....
..*..
.....
.*...
.....
4
....
....
*...
*...```

### 输出

```
*.*.
....
*.*.
....
**
**
**
**
*.*
*.*
...
.....
.**..
.....
.**..
.....
....
....
**..
**..```

# 题解

## 作者：_easy_ (赞：3)

## 题目分析
~~这道题其实就是模拟~~

可以把给定的点分为几种类型： 
1. 给出对角； 
2. 给在一行；
3. 给在一列。

先看第一种：设他们的坐标分别为 $(x1,y1),(x2,y2)$。则我们要改变的就是 $(x1,y2),(x2,y1)$。

再看第二种：我们只需要在这两个点的左或右边加点就行了。

最后看第三种：与第二种类似，我们只需要在这两个点的上或下加点就行了。

最后双手奉上代码：

------------

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,xl,yl,k;
char c[10009][10009];
int main(){
	cin>>m;
	while(m--){
		x=0,y=0,xl=0,yl=0;
		k=0;
		cin>>n;
		for(int i=1;i<=n;i++){
        	for(int j=1;j<=n;j++){
   		        c[i][j]='.';//初始化
            		}	
        	}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>c[i][j];
				if(c[i][j]=='*'){
					if(k==0){
						x=i,y=j;
						k=1;
					}
					else{
						xl=i;yl=j;
					}
				}
			}
		}
		if(x==xl){
			if(x==1&&xl==1){
				c[x+1][y]='*';
				c[xl+1][yl]='*';
				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						cout<<c[i][j];
					}
					cout<<endl;
				}
			}
			else{
				c[x-1][y]='*';
				c[xl-1][yl]='*';
				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						cout<<c[i][j];
					}
					cout<<endl;
				}
			}
		}
		else if(y==yl){
			if(y==1&&yl==1){
				c[x][y+1]='*';
				c[xl][yl+1]='*';
				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						cout<<c[i][j];
					}
					cout<<endl;
					}
			}
			else{
				c[x][y-1]='*';
				c[xl][yl-1]='*';
				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						cout<<c[i][j];
					}
					cout<<endl;
				}
			}
		}
		else{
			c[x][yl]='*';
			c[xl][y]='*';
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					cout<<c[i][j];
				}
				cout<<endl;
			}
		}
	}
    return 0;
}

```


---

## 作者：dalao_see_me (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1512B)
## 题目大意
在一个 $n\times n$ 的矩阵中有两个点，请找出另外两个点的位置使得这四个点是一个矩阵的四个角。
## 做法
这道题要分类讨论。

设已有两个点坐标为 $(x_1,y_1)$ 和 $(x_2,y_2)$。

当两个点不在同一行又不在同一列时，另外两个点的坐标分别是 $(x_1,y_2)$ 和 $(x_2,y_1)$。

来看一下样例吧，第一个点坐标是 $(1,3)$，第二个点是 $(3,1)$，另外两个点的坐标显然为 $(1,1)$ 和 $(3,3)$。

当两个点在同一行时，另外两个点的坐标是 $(x_1\pm1,y_1)$ 以及 $(x_2\pm1,y_2)$，其中 $1$ 是正是负取决于 $x_1$ 是否为 $n$，正确性显然。

当两个点在同一列时，同理可知另外两个点的坐标是 $(x_1,y_1\pm1)$ 以及 $(x_2,y_2\pm1)$。

于是就分类讨论完了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,n,_;
struct Point{
	int x,y;
}a[3];
char c[405][405];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	_=read();
	while(_--){
		n=read();tot=0;//记得把tot置0，不然会数组越界（总之就是挂了）
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				cin>>c[i][j];
				if(c[i][j]=='*'){
					++tot;//此时（自增完以后）的tot代表当前输入到了第几个点
					a[tot].x=i;
					a[tot].y=j;
				}
			}
		if(a[1].x!=a[2].x&&a[1].y!=a[2].y){//两个点既不在同一行也不在同一列
			c[a[1].x][a[2].y]='*';
			c[a[2].x][a[1].y]='*';
		}
		else if(a[1].x==a[2].x){//两个点在同一行
			int x;
			if(a[1].x==n)x=a[1].x-1;//特判x1为n的情况
			else x=a[1].x+1;
			c[x][a[1].y]='*';
			c[x][a[2].y]='*';
		}
		else{//两个点在同一列
			int y;
			if(a[1].y==n)y=a[1].y-1;//特判y1为n的情况
			else y=a[1].y+1;
			c[a[1].x][y]='*';
			c[a[2].x][y]='*';
		}
		for(int i=1;i<=n;i++,puts(""))
			for(int j=1;j<=n;j++)
				putchar(c[i][j]);
	}
	return 0;
}
```


---

## 作者：Da_un (赞：3)

### [题目](https://www.luogu.com.cn/problem/CF1512B)
大体意思是给出 $T$ 个 $N * N$ 的矩形，每一个矩形中都有两个星号，让你再在矩形中将两个点变为星号使四个星号构成一个矩形并将这个矩形输出。
## 思路
用 $(l1,r1)$ 和 $(l2,r2)$ 记录这两个星号的位置，然后分类讨论三种情况 (可以自己画一下图)。
1. 当这两个位置没有相同的行或列即 ```l1!=r1&&l2!=r2``` 时，相当于知道了这个矩形的一条对角线去求另外一条对角线，求的这一条对角线是唯一的，所以只能改变位置 $(l1,r2)$ 和 $(l2,r1)$。
1. 当这两个位置的横坐标相同即 ```l1==l2``` 时，根据矩形特点，要改的两个点的纵坐标与原来两个位置相同，只需同时改变横坐标与原来两个位置不同即可。
1. 当这两个位置的纵坐标相同即 ```r1==r2``` 时，根据矩形特点，要改的两个点的横坐标与原来两个位置相同，只需同时改变纵坐标与原来两个位置不同即可。

第二种情况和第三种情况，就是给出矩形的一条边，求任意的另一条边，还要注意 **越界** 问题，变为星号的坐标不能超出矩阵范围，具体看代码。
## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t,n;
char a[600][600];
int l1,r1,l2,r2;
inline int qread()//快速读入
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	} 
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}  
void ksks()//用于输出 
{
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
		       cout<<a[i][j];
		} 
		printf("\n");
	}
 } 
void k()//分类讨论 
{
	l1=r1=l2=r2=0;//方便记录
	for(int i=1;i<=n;i++)
	   for(int j=1;j<=n;j++)
	       if(a[i][j]=='*'){
		   if(l1==0&&r1==0){
		      l1=i;
		      r1=j;
		      continue;
		   }
		   l2=i;
		   r2=j;
	}//记录两个星号的位置 
	if(l1!=l2&&r1!=r2){
	   a[l2][r1]=a[l1][r2]='*';
	   ksks();
	   return;
	}//第一种情况 
	if(l1==l2){
	   if(l1>1&&l1<=n)
	      a[l1-1][r1]=a[l2-1][r2]='*';//如上，l1和l2减几为个人喜好，只要符合范围即可
	   if(l1==1)
	      a[l1+1][r1]=a[l2+1][r2]='*';//当两个星号横坐标均为1时，所改的两个点的横坐标必须大于1小于n 
	   ksks();
	   return;
	}//第二种情况 
	if(r1==r2){
	   if(r1>1&&r1<=n)
	      a[l1][r1-1]=a[l2][r2-1]='*';//符合范围
	   if(r1==1)
	      a[l1][r1+1]=a[l2][r2+1]='*';//当两个星号纵坐标均为1时，所改的两个点的纵坐标必须大于1小于n 
	   ksks();
	   return;
	}//第三种情况 
}
int main()
{
	t=qread();
	while(t--)
	{
		n=qread();
		for(int i=1;i<=n;i++)
		   for(int j=1;j<=n;j++)
		       cin>>a[i][j];//读入 
		k(); 
	}
	return 0;//完结撒花
}
```
### [ AC记录](https://www.luogu.com.cn/record/51454478)

---

## 作者：Dragonbell_exp (赞：2)

这是一道分情况讨论的题，主要是注意细节。

题意：
有一张大小为 $n \times n$，由两个星号组成的图，你需要添加两个星号，使这四个星号构成一个矩形。

思路：
简单画图并分析样例之后，我们可以比较容易地发现几种情况。我们用 $(x_1,y_1)$ 和 $(x_2,y_2)$ 表示这两个星号的位置（$x$ 相当于数组里的行，$y$ 相当于数组里的列）。

1. 当 $x_1$ 等于 $x_2$ 时（如给出的第 $4$ 个样例）：介于矩阵的特性，我们只需要在不改变对应的 $y$ 的情况下填加两个 $x$ 轴减或加同样的数（推荐为 $1$）的点即可（需要判断点在边界的情况）。

1. 当 $y_1$ 等于 $y_2$ 时（如给出的第 $3$ 个样例）：与情况一同理，添加 $x$ 对应不变，$y$ 加减同一个数的两个点即可。

3. 当 $x_1$ 不等于 $x_2$ 并且 $y_1$ 不等于 $y_2$ 时（如给出的第 $1$ 个样例）：在纸上画图可知，两个星号的坐标轴延长之后的交点组成了矩阵剩下的两个点。而这两个点的坐标分别是 $(x_1,y_2)$ 和 $(x_2,y_1)$。

实现：
读入并存储两个星号的位置，按照规律填充星号并输出即可。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<string>
#include<cstring>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t;//测试数据组数 
int n;//矩阵大小 
char mp[500][500];//存放矩阵 
int x1,x2,o;//第一个星号的坐标以及是否被找到 
int y1,y2;//第二个星号的坐标 
int main(){
	t=read();
	while(t--){
		n=read();
		o=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>mp[i][j];
				if(mp[i][j]=='*'&&o==1){//找出两个星号 
					x2=i;
					y2=j;
					continue;
				}
				if(mp[i][j]=='*'&&o==0){
					x1=i;
					y1=j;
					o=1;
					continue;
				}
			}
		}
		if(y1==y2){//处理情况2 
			if(y1==n&&y2==n){
				mp[x1][y1-1]='*';
				mp[x2][y2-1]='*';
			}
			else{
				mp[x1][y1+1]='*';
				mp[x2][y2+1]='*';
			}
		}
		else{
			if(x1==x2){//处理情况1 
				if(x1==1&&x2==1){
					mp[x1+1][y1]='*';
					mp[x2+1][y2]='*';
				}
				else{
					mp[x1-1][y1]='*';
					mp[x2-1][y2]='*';
				}
			}
			else{//否则为情况3 
				mp[x1][y2]='*';
				mp[x2][y1]='*';
			}
		}
		for(int i=1;i<=n;i++){//输出矩阵 
			for(int j=1;j<=n;j++){
				cout<<mp[i][j];
			}
			cout<<endl;
		}
		
	}
	return 0;
}
```


---

## 作者：zhang1234 (赞：1)

## 1.题意

已知两点，在矩阵**范围内**求另外两点，使四点形成一个矩形。

## 2.思路

此题分以下几种情况：

+ 两点连接后是一条斜线，只要求出两个点在 $x$ 轴和 $y$ 轴方向的**最大值和最小值**，再将这四个数进行**四次**组合，把每个组合成的点赋值为 * （之所以赋值两次是因为我们并不知道它是上升趋势还是下降趋势，而且就算重复了对答案也没有影响）。

+ 两点连接后与 $x$ 轴**平行**，即 $y$ 相等，$x$ 已确定，所以我们只要将这两点向上或向下平移，而且因为要保证在矩阵**范围内**，平移距离尽量**小**，所以在这里将平移距离都定为了 $1$。

+ 两点连接后与 $y$ 轴**平行**，即 $x$ 相等， $y$ 已确定，将这两点向左或向右平移（平移距离同上）。

## 3.代码

```cpp
#include <iostream>
#include <cmath>

using namespace std;

char a[405][405];

int main(void)
{
	int q;//数据组数 
	
	cin>>q;
	
	for(int i = 1;i <= q;i++)
	{
		int x[2],y[2];          //*的坐标 
		int num = 0;            //*已出现的次数 
		int n;                  //矩阵边长 
		int maxx,minx,maxy,miny;
		
		cin>>n;
		
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				cin>>a[i][j];
				
				if(a[i][j] == '*' && num == 0)
				{
					x[0] = i;
					y[0] = j;
					num = 1;
				}
				else if(a[i][j] == '*' && num == 1)
				{
					x[1] = i;
					y[1] = j;
				}
			}
		}//输入矩阵，外加记录*的坐标 
		
		maxx = max(x[0],x[1]);
		minx = min(x[0],x[1]);
		maxy = max(y[0],y[1]);
		miny = min(y[0],y[1]);
		if(maxx == minx)
		{
			if(maxx == n)
			{
				maxx = maxx - 1;
				minx = maxx;
			}//*在矩阵边界 
			else
			{
				maxx = maxx + 1;
				minx = maxx;
			}
		}//两个*与y轴平行 
		if(maxy == miny)
		{
			if(maxy == n)
			{
				maxy = maxy - 1;
				miny = maxy;
			}//*在矩阵边界 
			else
			{
				maxy = maxy + 1;
				miny = maxy;
			}
		}//两个*与x平行 
		a[maxx][maxy] = '*';
		a[maxx][miny] = '*';
		a[minx][miny] = '*';
		a[minx][maxy] = '*';
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				cout<<a[i][j];
			}
			cout<<endl;
		}
	}
}
```


---

## 作者：StayAlone (赞：1)

这道题的题意很明确，也很简单明了:给定一个只含有 \*  和 . 的矩阵。其中 \* 有且仅有2个，增加两个 \* 使得最终的四个 \* 能够组成矩形。

**假设这两点 $(x_1, y_1), (x_2 ,y_2)$**   

**分三种情况：**
+ 两个点行列均不相同
	- 此时答案一定，另外两个点分别是：  
    $(x_1, y_2),(x_2, y_1)$  
    
    
+ 行相同
	- 这里我的处理是如果这个两个点都在最下面，则把另外两个点放在这两个点的上面一行，否则就放在这两个点下面一行。
   - 两点在最下面时，另外两个点分别是：  
   $(x_1-1, y_1),(x_2-1, y_2)$  
 	- 其他情况下，另外两个点分别是：  
   $(x_1+1, y_1),(x_2+1, y_2)$  
   
 
+ 列相同
	- 这里我的处理是如果这个两个点都在最右边，则把另外两个点放在这两个点的左边一列，否则就放在这两个点右边一列。
   - 两点在最右边时，另外两个点分别是：  
     $(x_1, y_1-1),(x_2, y_2-1)$  
 	- 其他情况下，另外两个点分别是：  
     $(x_1, y_1+1),(x_2, y_2+1)$  
	

最后输出数组 c 就可以了。

这里说一个~~弱智~~的小东西，~~大佬请略过~~

输入二维数组 c 时，可以写  
```cpp
for (int i = 1; i <= n; ++i)  
	for (int j = 1; j <= n; ++j) scanf("%c", &c[i][j]);
```


但我们更可以写  
``
for (int i = 1; i <= n; ++i)  
	scanf("%s", c[i]+1);
``

这里的 $c_i+1$ 表示输入字符串 $\texttt{(char *)}$ $c_i$ 且下标从 1 开始


[AC code记录](https://www.luogu.com.cn/record/50216928)

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n; char c[410][410];
struct node
{
	int x, y;
};

node f() //  返回数组内第一个找到的*的下标
{
	node ans;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (c[i][j] == '*')
			{
				ans.x = i, ans.y = j, c[i][j] = '.'; // 找到后把它更改，这样再找一次就能找到第二个*的下标
				return ans;
			}
}
int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%s", c[i]+1);
		node s1 = f(), s2 = f();
		c[s1.x][s1.y] = '*', c[s2.x][s2.y] = '*'; // 由于前面进行了更改，要把这两个位置还原
		if (s1.x != s2.x && s1.y != s2.y) c[s1.x][s2.y] = '*', c[s2.x][s1.y] = '*';
		else if (s1.x != s2.x)
		{
			if (s1.y == n) c[s1.x][s1.y-1] = '*', c[s2.x][s2.y-1] = '*';
			else c[s1.x][s1.y+1] = '*', c[s2.x][s2.y+1] = '*';
		}
		else
		{
			if (s1.x == n) c[s1.x-1][s1.y] = '*', c[s2.x-1][s2.y] = '*';
			else c[s1.x+1][s1.y] = '*', c[s2.x+1][s2.y] = '*';
		}
		for (int i = 1; i <= n; ++i, puts(""))
			for (int j = 1; j <= n; ++j) printf("%c", c[i][j]);
	}
	return 0; 
}
```



---

## 作者：rain2021 (赞：1)

# 题意翻译

一句话题意：给出 $T$ 个矩阵，每个矩阵由 $N$ 行 $N$ 列个 `.` 和 `*` 组成，保证矩阵中有且只有两个 `*`，要求你再在矩阵上将两个 `.` 改成 `*` 使得 $4$ 个 `*` 可以是一个矩阵的 $4$ 个角（提示：两个 `*` 可能在同一行）。
* * *

按照题意模拟就完事儿了

![图像_2021-05-03_095241.png](https://i.loli.net/2021/05/03/IjyJ9mChze6iTwB.png)

比如这个图，

他的两个`*`的横坐标与纵坐标都不一样，所以

`s[x1][y2] = '*'`

`s[x2][y1] = '*'`

然后他就变成了这样：

![捕获.PNG](https://i.loli.net/2021/05/03/vhNra2tf1zocqCB.png)
* * *

再来看看两个的横坐标是一样的情况：

![捕获.PNG](https://i.loli.net/2021/05/03/s92xw7ZiT6UJft1.png)

那么剩下的两个可以这样：

![捕获.PNG](https://i.loli.net/2021/05/03/hgYAGyTsSarFERb.png)

也可以可以这样：

![捕获.PNG](https://i.loli.net/2021/05/03/qE6rJClhd8guTmO.png)

所以我们可以随便输出一种，比如这个：

![捕获.PNG](https://i.loli.net/2021/05/03/qE6rJClhd8guTmO.png)

```cpp
if(y1 == 1)
{
	s[x1][y1 + 1] = '*';
	s[x2][y2 + 1] = '*';
}
else if(x1 == n)
{
	s[x1][y1 - 1] = '*';
	s[x2][y2 - 1] = '*';
}
else
{
	s[x1][y1 - 1] = '*';
	s[x2][y2 - 1] = '*';
}
```
* * *

同理，如果纵坐标一样的话，就这样做：
```cpp
if(x1 == 1)
{
	s[x1 + 1][y1] = '*';
	s[x2 + 1][y2] = '*';
}
else if(x1 == n)
{
	s[x1 - 1][y1] = '*';
	s[x2 - 1][y2] = '*';
}
else
{
	s[x1 - 1][y1] = '*';
	s[x2 - 1][y2] = '*';
}
```

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 405
char s[MAXN][MAXN];
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", s[i] + 1);
			for(int j = 1; j <= n; j++)
			{
				if(s[i][j] == '*')
				{
					if(x1 == 0 && x2 == 0)
					{
						x1 = i;
						y1 = j;
					}
					else
					{
						x2 = i;
						y2 = j;
					}
				}
			}
		}
		if(x1 == x2)
		{
			if(x1 == 1)
			{
				s[x1 + 1][y1] = '*';
				s[x2 + 1][y2] = '*';
			}
			else if(x1 == n)
			{
				s[x1 - 1][y1] = '*';
				s[x2 - 1][y2] = '*';
			}
			else
			{
				s[x1 - 1][y1] = '*';
				s[x2 - 1][y2] = '*';
			}
		}
		else if(y1 == y2)
		{
			if(y1 == 1)
			{
				s[x1][y1 + 1] = '*';
				s[x2][y2 + 1] = '*';
			}
			else if(x1 == n)
			{
				s[x1][y1 - 1] = '*';
				s[x2][y2 - 1] = '*';
			}
			else
			{
				s[x1][y1 - 1] = '*';
				s[x2][y2 - 1] = '*';
			}
		}
		else
		{
			s[x1][y2] = '*';
			s[x2][y1] = '*'; 
		}
		for(int i = 1; i <= n; i++)
			printf("%s\n", s[i] + 1);
	}
	return 0;
}
```


---

## 作者：oimaster (赞：0)

⭐视频版：https://www.bilibili.com/video/BV1DB4y1w7YA⭐

---

我们把第一个 `*` 的位置称为 $(x_1,y_1)$，第二个 `*` 的位置称为 $(x_2,y_2)$。$x$ 是行，$y$ 是列。

接下来，我们分几种情况考虑。

1. $(x_1\not=x_2)\land(y_1\not=y_2)$，显然我们需要建的两个 `*` 在 $(x_1,y_2),(x_2,y_1)$。
2. $(x_1=x_2)\land(y_1\not=y_2)$，那么我们需要把两个 `*` 分别建在 $y_1$ 和 $y_2$ 列上。我们可以把两个 `*` 建在第一行（统一）。如果这两个 `*` 本来就在第一行，我们就把新建的扔在第二行上。
3. $(x_1\not=x_2)\land(y_1=y_2)$ 和 $(x_1=x_2)\land(y_1\not=y_2)$ 同理。

---

代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        char c[n + 1][n + 1];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cin >> c[i][j];
        int x1 = -1, x2;
        int y1, y2;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (c[i][j] == '*')
                    if (x1 == -1)
                    {
                        x1 = i;
                        y1 = j;
                    }
                    else
                    {
                        x2 = i;
                        y2 = j;
                        break;
                    }
        if (x1 != x2 && y1 != y2)
            c[x1][y2] = c[x2][y1] = '*';
        else if (x1 == x2)
            if (x1 == 1)
                c[2][y1] = c[2][y2] = '*';
            else
                c[1][y1] = c[1][y2] = '*';
        else if (y1 == 1)
            c[x1][2] = c[x2][2] = '*';
        else
            c[x1][1] = c[x2][1] = '*';
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                cout << c[i][j];
            cout << endl;
        }
    }
}
```

---

## 作者：WinterRain208 (赞：0)

CF1512B Almost Rectangle

首先题意不再赘述，这题作为div3t2还是比较简单的，分类讨论即可。

### 做法

记已经有标记的两个点坐标为 $(x_1,y_1)$ 和 $(x_2,y_2)$。

那么有以下几种情况：

一：$x,y$ 分别相等，可直接确定另外两个点坐标。

二：$x,y$ 两个坐标有相同的,分在边界上和不在边界上讨论。

根据分类讨论的内容用分支解决。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

int t,n,x=0,y=0,xx,yy;
char a[405][405];

int main(){
	cin>>t;
	while(t--){
		cin>>n;
		x=y=0;
		F(i,1,n)F(j,1,n){
			cin>>a[i][j];
			if(x==0&&a[i][j]=='*')x=i,y=j;
			else if(a[i][j]=='*')xx=i,yy=j;
		}
		if(xx!=x&&yy!=y)a[xx][y]=a[x][yy]='*';
		else if(xx==x){
			if(xx==1)a[xx+1][yy]=a[x+1][y]='*';
			else a[xx-1][yy]=a[x-1][y]='*';
		}
		else if(yy=y){
			if(yy==1)a[xx][yy+1]=a[x][y+1]='*';
			else a[xx][yy-1]=a[x][y-1]='*';
		}
		F(i,1,n){
			F(j,1,n)cout<<a[i][j];
			puts("");
		}
	}
	return 0;
} 
```


---

## 作者：wheneveright (赞：0)

## 题意

一句话题意：给出 $T$ 个矩阵，每个矩阵由 $N$ 行 $N$ 列个 `.` 和 `*` 组成，保证矩阵中有且只有两个 `*`，要求你再在矩阵上将两个 `.` 改成 `*` 使得 $4$ 个 `*` 可以是一个矩阵的 $4$ 个角（提示：两个 `*` 可能在同一行）。

## 分析

这是一道构造题。

其实没必要把图存下来，因为只有两个 `*` 所以我们只需要把两个 `*` 的下标 get 到就行啦。

我们先定义 $4$ 个点中点 $i$ 的坐标 $P_i$ 为 $(x_i,y_i)$，其中 $P$ 的下标从 $0$ 开始，$P_0$、$P_1$ 是读入时读取的，而 $P_2$、$P_3$ 是需要构造的。

先考虑有同行同列的情况出现：

```cpp
if (x[0] == x[1]) {
    y[2] = y[0]; y[3] = y[1];
    x[2] = x[1] + 1; if (x[2] > N) x[2] -= N;
    x[3]= x[2];
}
```

当 $x$ 相同时 $P_2$ 和 $P_3$ 的 $x$ 可以随便取（只要不要与 $x_0$ 相同）那么我设 $x_2 = x_1 + 1$ 可以保证不在同一行，然后再判断有没有出界，如果有的话减去 $N$ 就可以保证它在矩阵范围内。

这里只放 $x$ 相同时的情况， $y$ 相同不作赘述。

而如果没有同行同列的话那就更简单了，因为边平行坐标轴的矩阵可以由对角线上的两个点确定，我们令 $x_2 = x_0, y_2 = y_1, x_3 = x_1, y_3 = y_0$ 交错赋值就好了。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, x[4], y[4], check;

bool get_bool () {
    // 读数据用
    for (char ch = getchar (); ; ch = getchar ())
    if (ch == '.' || ch == '*') return ch == '*';
}

int main () {
    cin >> T;
    while (T--) {
        cin >> N; check = 0;// check 表示第几个出现的 *
        for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
        if (get_bool ()) {
            x[check] = i; y[check] = j;
            check = 1;
        }
        if (x[0] == x[1]) {
            y[2] = y[0]; y[3] = y[1];
            x[2] = x[1] + 1; if (x[2] > N) x[2] -= N;
            x[3]= x[2];
        }   else
        if (y[0] == y[1]) {
            x[2] = x[0]; x[3] = x[1];
            y[2] = y[1] + 1; if (y[2] > N) y[2] -= N;
            y[3] = y[2];
        }   else // 这里前面有说过
        {
            x[2] = x[0]; y[2] = y[1];
            x[3] = x[1]; y[3] = y[0];
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                check = 0; // 输出时判断是否应该输出 *
                for (int k = 0; k <= 3; k++) if (i == x[k] && j == y[k]) check = 1;
                putchar (".*"[check]);
                // 这里编译时会将 ".*" 看做一个字符串
            }
            putchar ('\n');
        }
    }
    return 0;
}
```

---

