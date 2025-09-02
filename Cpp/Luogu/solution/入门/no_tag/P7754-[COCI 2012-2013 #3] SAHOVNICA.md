# [COCI 2012/2013 #3] SAHOVNICA

## 题目背景

Mirko 已经成为一个铁杆爱国者，所以他要求你给他画一个克罗地亚棋盘。

## 题目描述

棋盘由红色格子和白色格子组成。棋盘左上角的格子是红色。其余的格子在棋盘中交替显示成白色和红色。我们在本题中用 `X` 表示红色区域，用 `.` 表示白色区域。Mirko 的棋盘应该由 $r\times c$ 的格子组成，并且每个格子是由字符 `X` 和 `.` 组成的 $a\times b$ 的字符矩阵。请你帮助他画出这个棋盘。

## 说明/提示

**【数据范围】**

对于所有数据，$1\leqslant r,c,a,b\leqslant 10$。

**【题目来源】**

本题来源自 **_[COCI 2012-2013](https://hsin.hr/coci/archive/2012_2013/) [CONTEST 3](https://hsin.hr/coci/archive/2012_2013/contest3_tasks.pdf) T1 SAHOVNICA_**，按照原题数据配置，满分 $50$ 分。

由 [Eason_AC](https://www.luogu.com.cn/user/112917) 翻译整理提供。

## 样例 #1

### 输入

```
2 4
2 2```

### 输出

```
XX..XX..
XX..XX..
..XX..XX
..XX..XX```

## 样例 #2

### 输入

```
5 5
2 3```

### 输出

```
XXX...XXX...XXX
XXX...XXX...XXX
...XXX...XXX...
...XXX...XXX...
XXX...XXX...XXX
XXX...XXX...XXX
...XXX...XXX...
...XXX...XXX...
XXX...XXX...XXX
XXX...XXX...XXX```

# 题解

## 作者：ImposterAnYu (赞：6)

# 理解题意
这道题就是将一个大小为 $r \times c$ 的由 `X` 和 `.` 组成的交叉矩阵（自定义名称）的长变为原来的 $a$ 倍，宽变为原来的 $b$ 倍后输出。

交叉矩阵的定义：一个大小为 $3 \times 5$ 的由 `s` 和 `b` 组成的交叉矩阵如下：
```
sbsbs
bsbsb
sbsbs
```
（默认靠前的那个字符为矩阵的第一个字符！）
# 1
我们可以先把一个大小为 $r \times c$ 的由 `X` 和 `.` 组成的交叉矩阵构造出来（设矩阵为 $x$）。那么具体要怎么做呢？

我们可以发现：当 $(i + j) \bmod 2 = 0$ 时，$p_{i,j}$ 为 `X`；否则，$p_{i,j}$ 为 `.`。

所以，代码的其中一部分就出来啦！
```cpp
for(i = 1; i <= r; i++){
		for(j = 1; j <= c; j++){
			x[i][j] = ((i + j) % 2? '.' : 'X');//用三目运算符判断当前位置上是哪个字符。 
		}
	}
```
# 2
那怎样得到最后的输出呢？

对比一下样例 $1$ 中的交叉矩阵：
```
X.X.
.X.X
```
和最后的输出：
```
XX..XX..
XX..XX..
..XX..XX
..XX..XX
```
发现没？其中的 $p_{i \times a + x,j \times b + y}$ 均等于 $p_{i \times a,j \times b}$（$x$ 为任意不大于 $r$ 的正整数，$y$ 为任意不大于 $c$ 的正整数）！

那么如果 $i = i + x$、$j = j + y$ 时，原来的 $i$、$j$ 又等于什么呢？

$$i = (i - 1) \div a + 1$$

$$j = (j - 1) \div b + 1$$

没毛病吧？
```cpp
for(i = 1; i <= r * a; i++){
		for(j = 1; j <= c * b; j++){
			cout<< x[(i - 1) / a + 1][(j - 1) / b + 1] ;//核心公式！ 
		}
		cout<< endl;
	}
```
整道题就这么讲完啦！
# 3（坑）
不要输出空格！不要输出空格！绝对不要输出空格！！！

（不知道为什么，输出空格还能A两个点……）
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,a,b,i,j;
char x[15][15];
int main(){
	cin >> r >> c >> a >> b;
	for(i = 1; i <= r; i++){
		for(j = 1; j <= c; j++){
			x[i][j] = ((i + j) % 2? '.' : 'X');//用三目表达式判断当前位置上是哪个字符。 
		}
	}
	for(i = 1; i <= r * a; i++){
		for(j = 1; j <= c * b; j++){
			cout<< x[(i - 1) / a + 1][(j - 1) / b + 1] ;//核心公式！ 
		}
		cout<< endl;
	}
    return 0;
}
```

---

## 作者：Shunpower (赞：4)

**观前提示：棋盘上的行、一大行都是指的 $a\cdot b\cdot c$ 的一行。一小行则是 $1\cdot c$ 的一行。**

## 思路

先初始化出 $r$ 个值表示棋盘第 $r$ 行的开头颜色，用数组 $col$ 进行存储，$col_i$ 表示棋盘第 $i$ 行的开头颜色。比如 $col_1$ 是红色，我们就存储为 $0$；比如 $col_2$ 是白色，就储存为 $1$。

然后再按照题意进行模拟即可。可以采用一次构造一小行，再循环 $a$ 次构造棋盘上的一大行，最后循环 $r$ 次构造整个棋盘。

## 代码实现

### 2.1 初始化

```
for(int i=1;i<=r;i++){
	if(i%2==1){
		col[i]=0;
	}
	else{
		col[i]=1;
	}
}
```
通过简单的找规律，我们发现第一行开头那个格子一定是红色，第二行开头那个格子一定是白色。依次类推很容易得到**如果行数 $\bmod \ 2$ 为 $1$，那么开头一定是红色。如果行数 $\bmod \ 2$ 为 $0$，那么开头一定是白色**的结论。

我们就可以按照得出的结论初始化 $col$ 数组。

### 2.2 构造棋盘

```
for(int i=1;i<=r;i++){
	for(int k=1;k<=a;k++){
		f=col[i];
		for(int j=1;j<=c*b;j++){
			if(!f){
				cout<<"X";
			}
        else{
				cout<<".";
			}
			if(j%b==0){
				f=!f;
			}
		}
		cout<<endl;
	}
}
```
用 $f$ 表示当前颜色，如果 $f=0$ 则输出`X`表示红色区域，反之若 $f=1$ 输出`.`表示白色区域。

注意在输出一小行之前要将 $f$ 初始化成 $col_i$。并且每输出完 $b$ 个字符就要将颜色反过来。

## AC Code

各部分已拆解放出。

[AC记录](https://www.luogu.com.cn/record/54646226)

---

## 作者：Wu_while (赞：3)

# 题意概括

画出 $r \times c$ 的`X`、`.`相间的棋盘，棋盘的每个格子由大小为 $a \times b$ 的，只有`X`和`.`中的一种字符的字符矩阵构成。

# 算法分析

这个题其实也不是很好想，容易糊涂。

我们可以发现，对于每一行，有下列两种情况：

- 连续 $b$ 个`X`，然后连续 $b$ 个`.`，然后再连续 $b$ 个`X`，然后……

- 连续 $b$ 个`.`，然后连续 $b$ 个`X`，然后再连续 $b$ 个`.`，然后……

也就是说，我们可以 `if` 两种情况：先`X`后`.` 以及 先`.`后`X`。

那又应该怎样讨论呢？

容易发现，如果当前**格子**（指的是棋盘的格子，就是一共有 $r \times c$ 个的）的行数为奇数，则先`X`后`.`，否则为`.`后`X`。

而对于每一行，可以通过当前的列数奇偶来划分是`X`还是`.`，具体参见代码。

# $Code$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int r,c,a,b;
int main()
{
	scanf("%d%d%d%d",&r,&c,&a,&b);
	for(int i=1;i<=r;i++)//格子行数
		for(int j=1;j<=a;j++)//字符在字符矩阵中的行数
		{
			for(int k=1;k<=c;k++)//格子列数
				if(i%2==1)//若当前行为先X后.
					if(k%2==1)//填入
						for(int l=1;l<=b;l++)
							cout<<'X';
					else
						for(int l=1;l<=b;l++)
							cout<<'.';
				else//若当前行为先.后X
					if(k%2==1)
						for(int l=1;l<=b;l++)
							cout<<'.';
					else
						for(int l=1;l<=b;l++)
							cout<<'X';
			cout<<endl;
		}
	return 0;
}
```

---

## 作者：little_cindy (赞：3)

# 思路

这题其实并不难，整体思路可以分为两步：**压缩**和**解压**。

## 压缩

压缩是什么意思？

其实我们可以想一想，把每个格子**压缩成一个点**，也就是在 $a=1,b=1$ 时，输出会是什么样的呢？

很明显，是像一个国际象棋的棋盘一样红色和白色**交错出现**。又有一个问题：我们如何这样输出呢？

数一数，因为同种颜色相距必为 $2$ 的倍数，即**任意两个点所在位置的横坐标与纵坐标模 $2$ 同余**。

于是，我们可以轻易得出：
- 若 $(x+y) \mod 2=0$，则输出```X```。
- 若 $(x+y) \mod 2=1$，则输出```.```。

也就可以写出以下代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define inl inline
using namespace std;
const int maxn=0;
int r,c;
int main(){
	cin>>r>>c;
    for(int i=1;i<=r;i++){
    	for(int j=1;j<=c;j++){
    		if((i+j)%2==0){
    			cout<<"X";
			}
			else{
				cout<<".";
			}
		}
		cout<<endl;
	} 
	return 0;
}
```

压缩完了，也是时候解压了。

## 解压

我们上面只得出了 $a=1,b=1$ 时的方案，而 $a,b$ 不一定等于 $1$，我们肯定还需要加上两个维度。即 $a$ 和 $b$。

所以，我们需要做四个循环：
- 循环压缩后的行数，即 $r$。
- 循环压缩后的列数，即 $c$。
- 每一个格子的行数，即 $a$。
- 每一个格子的列数，即 $b$。

我给一个无序列表是有原因的。因为，依照这个顺序输出是会WA的。

思考一下，我们有 $r$ 行格子，每行分为 $a$ 个小格子。有 $c$ 列格子，每列分为 $b$ 个小格子。

我们一般做题时，一个二维的东西怎么处理？先循环行再循环列啊！

我们做题的时候，大格子包含小格子怎么分？先循环大格子的个数再循环小格子的个数啊!

那么，再排一下序……
1. 循环压缩后的行数，即 $r$。
1. 每一个格子的行数，即 $a$。
1. 循环压缩后的列数，即 $c$。
1. 每一个格子的列数，即 $b$。

这不就简简单单吗？在按照我们考虑压缩时总结的规律：
> - 若 $(x+y) \mod 2=0$，则输出```X```。
> - 若 $(x+y) \mod 2=1$，则输出```.```。

正解也就出来了。

# $\color{yellowgreen}\textrm{AC}$code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define inl inline
using namespace std;
const int maxn=0;
int r,c,a,b;
int main(){
	cin>>r>>c>>a>>b;
    for(int i=1;i<=r;i++){
    	for(int k=1;k<=a;k++){
    		for(int j=1;j<=c;j++){
    			for(int m=1;m<=b;m++){
    				if((i+j)%2==0){
    					cout<<"X";
					}
					else{
						cout<<".";
					}
				}
			}
			cout<<endl;
		}
	} 
	return 0;
}

```

---

## 作者：lskksl (赞：0)

理解这道题的题意是关键的。

题目说，输出的是 $r \times a$ 行，每行 $c \times b$ 列。想一想这是为什么？再仔细看你就会发现，每一个由 $X$ 或 $.$  组成的矩阵，都是 $a$ 行，$b$ 列的。而且，它们在无论横行还是竖行，都是轮换的。

这就可以模拟了！

先循环 $r$ 行：
```
for(int t=1;t<=r;t++)
```
再进行是输入 $X$ 的矩阵或 $.$ 的矩阵。而这一点则可以通过 $t$ 的奇偶性来判断。由于第一个 $a$ 行是  $X$ 的矩阵先开始的，并在   $t$ 为奇数时轮换。所以便可以表示为：
```
if(t%2==1)
```
便可以先输入  $X$ 的矩阵了。不然则相反。

这样便可以循环  $a$ 行来输入矩阵了。而每一行也是两种矩阵交替输出的，所以也进行如上的就判断即可。判断好了，便可以循环  $b$  次输出了。

没看懂的朋友可以看代码，注释都在代码里了：

```
#include<cstdio>
using namespace std;
int main()
{
	int r,c,a,b;
	scanf("%d%d%d%d",&r,&c,&a,&b);
	for(int t=1;t<=r;t++)//输出列数
	{    
	    if(t%2==1)//判断奇偶来进行选择输出哪一种矩阵，先是 X 矩阵。
		{
		    for(int h=1;h<=a;h++)//循环 a 行来进行输出矩阵，即扩散a行
		    {
		        for(int i=1;i<=c;i++)//输出行数
	            {  
		            if(i%2==1)//二次奇偶判断
					{
						for(int j=1;j<=b;j++)////循环 b 行进行输出，及每种矩阵列数。
						{
							printf("X");//Aya，输出了。下面部分同上了qwq。
						}
					}
		            else 
				    {
				        for(int k=1;k<=b;k++) 
					    {
						    printf(".");
					    } 
				    }
		        }
	        printf("\n");
		    }
	    } 
		else
		{
		    for(int h=1;h<=a;h++)
		    {
		        for(int i=1;i<=c;i++)
	            {
		            if(i%2==1) 
					{
						for(int j=1;j<=b;j++) 
						{
							printf(".");
						}
					}
		            else 
		            {
		        	    for(int k=1;k<=b;k++) 
					    {
						    printf("X");
					    }
		            }
	            }
			printf("\n");
		    }
		}	
	}
	return 0;KO!
} 
```


---

## 作者：CPPfive (赞：0)

## 题目分析
直接模拟就好了。

具体来说，外层两层循环枚举棋盘的每一格，内层的两层循环枚举一格内的矩形。使用一个变量来记录当前的格子应该填什么。最后再循环一遍输出即可。

## 代码

```cpp
//洛谷P7754 

#include <bits/stdc++.h>
using namespace std;
const int MAXN=110;
int a[MAXN][MAXN],R,C,A,B;
int id=1;							
//用于记录当前的格子要填什么 

int main()
{
	scanf("%d%d%d%d",&R,&C,&A,&B);
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			id^=1;
			for(int k=1;k<=A;++k){
				for(int t=1;t<=B;++t){
					a[(i-1)*A+k][(j-1)*B+t]=id;
				}
			}
		}
		id^=(C%2==0);				
		//根据一行的格子数的奇偶来判断是否要更新 
	}
	for(int i=1;i<=R*A;++i){
		for(int j=1;j<=C*B;++j){
			if(a[i][j]) printf(".");
			else printf("X");
		}
		printf("\n");
	}
}
```


---

## 作者：ifnotab (赞：0)

这是我第一次发题解，若有错误，请不要见怪，并私信。

------------
# 书归正传
根据本题题意，我们可以得知：这是一道用程序来控制输出图形的题。关键是，他一共有两种图形，分别为X和"."。若只用一种变量控制图形，则会出现与目标图形不相符的形状，即每一列的图形是交错的。此题注意点如下：

1. 需要两个变量控制。
1. 输出的图形是什么要搞清楚。
1. 一定要加回车！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e=1,f=1;//创建变量
	cin>>a>>b>>c>>d;
	for(int i=1;i<=a*c;i++){
		e=f;//控制第一个出来的（每列的第一个）
		for(int j=1;j<=b*d;j++){
			if(e){
				cout<<"X";
			}else{
				cout<<".";
			}
			if(j%d==0){//判断输出的是X还是.
				if(e){
					e=0;
				}else{
					e=1;
				}
			}
		}
		cout<<endl;
		if(i%c==0){//判断第一个输出的是X还是.
			if(f){
				f=0;
			}else{
				f=1;
			}
		}
	}
	return 0;
}

```


---

## 作者：CRH2C (赞：0)

# 题意
一个 $r \times c$ 格的棋盘，每格由 $a \times b$ 个字符组成，已知第一个格子是$\texttt{ 'X' }$，第二个格子是$\texttt{ '.' }$，以此类推，其余的格子在棋盘中交替显示$\texttt{ 'X' }$和$\texttt{ '.' }$，现在给出 $r,c,a,b$ 请你打印这个棋盘。

# 思路
我们可以先判断每个格子该输什么，可以用一个变量来记上一个的状态，但如果 $c$ 是双数，我们要改变一下（改变第一列），然后后期再按它的要求放大。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int r,a,c,b;
bool f[20][20],lf=1;// f 数组代表每一个格子的内容，lf 是上一个格子的内容。
int main(){
	cin>>r>>c>>a>>b;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(c%2==0 && j==1 && i!=1) lf=1-lf;//因为要交替显示，然而，如果 c 是双数时就不对了，所以我们要更改它。
			f[i][j]=1-lf;//将本格的内容设为上一格的相反值。
			lf=f[i][j];//更新
		}
	}
	for(int i=1;i<=r;i++){
		for(int ii=1;ii<=a;ii++){//放大a倍
			for(int j=1;j<=c;j++){
				for(int jj=1;jj<=b;jj++){//放大b倍
					if(f[i][j]) cout<<'.';
					else cout<<'X';
				}
			}
			cout<<endl;
		}
	}
	return 0;
}

```

---

