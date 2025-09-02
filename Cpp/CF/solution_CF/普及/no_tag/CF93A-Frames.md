# Frames

## 题目描述

$Igor.$ $K$在D盘中有$n$个文件夹，分别以$1$~$n$编号。                    
他使用的$Pindows$ $XR$系统有一个参数$m$。                
在D盘中，这些文件会排成 $\left\lceil\dfrac{n}{m}\right\rceil$ 行（每行$m$个文件夹，如果剩下的不到$m$个文件夹则另占一行）。          
他想删除D盘中的第$a$~$b$个文件夹。         
每次删除，他需要用一个矩形框出他要删除的一个文件夹矩阵。                
$Igor.$ $K$想用最少的次数删除且仅删除第$a$~$b$个文件夹。输出最少的次数。


$Tip$：由于这是神奇的$Pindows$ $XR$系统，所以被删除的文件不会消失，还会占位（但它已经被删除了）

## 样例 #1

### 输入

```
11 4 3 9
```

### 输出

```
3
```

## 样例 #2

### 输入

```
20 5 2 20
```

### 输出

```
2
```

# 题解

## 作者：Transparent (赞：6)

### 找规律

直接想肯定不方便，自己建一个文件夹就方便多了。

[![3q6MY8.png](https://s2.ax1x.com/2020/03/06/3q6MY8.png)](https://imgchr.com/i/3q6MY8)

首先，无论如何，用3个矩形框都可选中任意符合题意的情况：

> 1. 先删除第一行；
> 1. 再删除中间的所有行；
> 1. 最后删除最后一行；

~~因此也让这题有了一种名叫“随机输出”的方法~~

但是总有一些情况可以使用更少的次数来删除所有需要删除的文件夹。

- ~~0次：没有~~

- $1$ 次：
> 1. 需要删除的第一个文件夹在第一列，需要删除的最后一个文件夹在最后一列。
> > 例： $21~5~6~20$
> > 
> > ~~有图有真相~~
> >
> > [![3qR1Nq.png](https://s2.ax1x.com/2020/03/06/3qR1Nq.png)](https://imgchr.com/i/3qR1Nq)
> 2. 需要删除的第一个文件夹和需要删除的最后一个文件夹在同一行。
> > 例： $21~5~2~4$
> > 
> > [![3qf3lT.png](https://s2.ax1x.com/2020/03/06/3qf3lT.png)](https://imgchr.com/i/3qf3lT)
> 3. 需要删除的第一个文件夹在第一列，需要删除的最后一个文件夹是最后一个文件夹（第 $n$ 个）。
> > 例： $21~5~6~21$
> >
> > [![3qhKDe.png](https://s2.ax1x.com/2020/03/06/3qhKDe.png)](https://imgchr.com/i/3qhKDe)
> >
> > （注意，这里是可以框选空白部分的）
>
> 共 $3$ 种

- $2$ 次：
> 1.需要删除的第一个文件夹是第一个文件夹。
> > 例： $21~5~1~13$
> >
> > 第一步：
> >
> > [![3q4vOU.png](https://s2.ax1x.com/2020/03/06/3q4vOU.png)](https://imgchr.com/i/3q4vOU)
> >
> > 第二步：
> >
> > [![3q5N7Q.png](https://s2.ax1x.com/2020/03/06/3q5N7Q.png)](https://imgchr.com/i/3q5N7Q)
> >
> >（图中浅色文件夹代表已删除的文件夹）
> 
> 2.需要删除的的最后一个文件夹是最后一个文件夹。
> > 例： $21~5~8~21$ 
> >
> > 第一步：
> >
> > [![3qIlE4.png](https://s2.ax1x.com/2020/03/06/3qIlE4.png)](https://imgchr.com/i/3qIlE4)
> > 
> > 第二步：
> >
> > [![3qoFsK.png](https://s2.ax1x.com/2020/03/06/3qoFsK.png)](https://imgchr.com/i/3qoFsK)
> 
> 3.需要删除的第一个文件夹和需要删除的的最后一个文件夹在相邻的行中。
> > 例： $21~5~7~14$
> >
> > 第一步：
> >
> > [![3qoreU.png](https://s2.ax1x.com/2020/03/06/3qoreU.png)](https://imgchr.com/i/3qoreU)
> >
> > 第二步：
> >
> > [![3qTAlq.png](https://s2.ax1x.com/2020/03/06/3qTAlq.png)](https://imgchr.com/i/3qTAlq)
>
> 4.需要删除的第一个文件夹所在的列正好位于最后一个文件夹所在的列的右边一个。
> > 例： $21~5~4~13$
> > 
> > 第一步：
> >
> > [![3q71Ug.png](https://s2.ax1x.com/2020/03/06/3q71Ug.png)](https://imgchr.com/i/3q71Ug)
> >
> > 第二步：
> >
> > [![3q7qMt.png](https://s2.ax1x.com/2020/03/06/3q7qMt.png)](https://imgchr.com/i/3q7qMt)
>
> 共 $4$ 种情况。

- 3次：若以上情况都不符合，则一定最少需要 $3$ 次操作。

**注意**：若满足多种情况，则去操作次数最少的作为答案。

------------

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,ans=3;
int main()
{
	scanf("%d%d%d%d",&n,&m,&a,&b);
	int a1=(a%m==0)?a/m:a/m+1;
	int a2=(a%m==0)?m:a%m;
	int b1=(b%m==0)?b/m:b/m+1;
	int b2=(b%m==0)?m:b%m;
	if(a1==b1)//第一个和最后一个文件夹在同一行中 
	{
		ans=1;
	}
	else if(a2==1&&b2==m)//第一个文件夹在第一列，最后一个文件夹在最后一列
	{
		ans=1;
	}
	else if(a2==1&&b==n)//第一个文件夹位于第一列，最后一个文件夹为n
	{
		ans=1;
	}
	else if(b1-a1==1)//第一个和最后一个文件夹在相邻的行中
	{
		ans=2;
	}
	else if(a2==1)//第一个文件夹位于第一列
	{
		ans=2;
	}
	else if(b2==m)//最后一个文件夹位于最后一列
	{
		ans=2;
	}
	else if(a2-b2==1)//最后一个文件夹是n
	{
		ans=2;
	}
	else if(b==n)//第一个文件夹所在的列正好位于最后一列所在的列的右边
	{
		ans=2;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：ljk8886 (赞：2)

这道题其实并不难，只是枚举情况时有点恶心。
# 题目分析
首先我们可以知道最多 $3$ 次就可以删完，关键在于要枚举得**不重不漏**。

## 枚举：
- 第 $a$ 个和第 $b$ 个在同一行时，$1$ 次就可以删完。

- 第 $a$ 个在第一列，第 $b$ 个在最后一列时，$1$ 次就可以删完。

- 第 $a$ 个在第一列，第 $b$ 个是最后一个时，$1$ 次就可以删完。

- 第 $a$ 个在第一列时，$2$ 次就可以删完。

- 第 $b$ 个在最后一列时，$2$ 次就可以删完。

- 第 $a$ 个和第 $b$ 个在相邻的行时，$2$ 次就可以删完。

- 第 $a$ 个和第 $b$ 个在相邻的列时，$2$ 次就可以删完。

- 第 $b$ 个是最后一个时，$2$ 次就可以删完。

- 其余情况，$3$ 次删完。

# 完整代码
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,m,a,b,x_1,y_1,x_2,y_2,ans;
    cin>>n>>m>>a>>b;
    if(a%m==0)x_1=a/m,y_1=m;//此文件夹在最后一列
    else x_1=a/m+1,y_1=a%m;//不在最后一列
    if(b%m==0)x_2=b/m,y_2=m;//同理
    else x_2=b/m+1,y_2=b%m;
    if(x_1==x_2)ans=1;//在同一行
    else if(y_1==1&&y_2==m)ans=1;//第a个在第一列，第b个在最后一列
    else if(y_1==1&&b==n)ans=1;//第a个在第一列，第b个是最后一个
    else if(y_1==1)ans=2;//第a个在第一列
    else if(y_2==m)ans=2;//第b个在最后一列    
    else if(x_2-x_1==1)ans=2;//第a个和第b个在相邻的行
    else if(y_1-y_2==1)ans=2;//第a个和第b个在相邻的列
    else if(b==n)ans=2;//第b个是最后一个，但第a个不在第一列
    else ans=3;//其余情况，一定3次删完
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Paris_Commune (赞：1)

### 分析

如果你无法理解分类的情况，可以在自己的电脑上尝试。

- $a$ 和 $b$ 在同一行，直接选中删除，需要 $1$ 次。

- $a$ 是某一行的第一个，$b$ 是某一行的最后一个或所有文件的最后一个，直接选中删除，需要 $1$ 次。

- $a$ 是某一行的第一个，但 $b$ 不是是某一行的最后一个或所有文件的最后一个，先删除 $b$ 所在行的文件，再直接删除其他文件，需要 $2$ 次。

- $a$ 不是是某一行的第一个，$b$ 是某一行的最后一个或所有文件的最后一个，先删除 $a$ 所在行的文件，再直接删除其他文件，需要 $2$ 次。

- $a$ 和 $b$ 在相邻的行，先删除 $a$ 所在行再删除 $b$ 所在行，需要 $2$ 次。

- $a$ 和 $b$ 在相邻的列，假设 $a$ 所在列在 $b$ 所在列的右侧，先删除 $a$ 所在列的右侧再删除 $b$ 所在列的左侧，需要 $2$ 次。

- $a$ 和 $b$ 不在同一行上，$a$ 不是某一行的第一个，$b$ 是最后一个，先删除 $a$ 所在行，再直接删除其他文件，需要 $2$ 次。

- 不满足以上条件，先删除 $a$ 所在行的文件，再删除 $b$ 所在行的文件，再直接删除其他文件，需要 $3$ 次。

注意不要遗漏情况。

### 注意

代码预处理 $a$ 和 $b$ 行和列时注意 $a$ 和 $b$ 在行末的情况。

[AC 代码](https://www.luogu.com.cn/paste/kqerf0mf)

---

## 作者：Z_M__ (赞：1)

题目坑点实在太多了

最多只要用3次！（~~应该很显然吧~~）

那就只有3种情况 ：1/2/3次

具体分类见注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, la, lb, ha, hb, ln, hn;
int main ()
{
	cin >> n >> m >> a >> b;
	ha = ceil (a * 1.0 / m); // a所在行数 
	hb = ceil (b * 1.0 / m); // b所在行数
	hn = ceil (n * 1.0 / m); 
	la = a - (ha - 1) * m; // a所在列数 
	lb = b - (hb - 1) * m; // b所在列数
	ln = n - (hn - 1) * m;
	if (m == 1 /*只有1列*/|| ha == hb /*a,b同行*/ || (lb == m && la == 1) /*a在列首,b在列尾*/ || (b == n && la == 1) /*b为最后一个文件，a在第1列*/)
	   return puts ("1"), 0; // 1次的情况 
	if (hb - ha == 1 /*a,b为相邻行*/ || (la == 1 || lb == m)/*a在列首或b在行尾*/ || la - lb == 1 || m == 2 /*只有两列*/ || b == n /*b为最后一个*/)
	   return puts ("2"), 0; // 2次的情况 
	puts ("3"); // 其他则为3次 
	return 0;
}
```

---

## 作者：qingchenMC (赞：0)

## 思路

首先注意到情况最多有 $3$ 种。因为：

||1|1|1|1|
|:-:|:-:|:-:|:-:|:-:|
|**2**|**2**|**2**|**2**|**2**|
|**2**|**2**|**2**|**2**|**2**|
|**3**|**3**|**3**|||

处理第一行，中间完整的区域，以及最后一行，只需 $3$ 步就可以完成。

但是有些情况，只需要不到 $3$ 步就可以完成。由于情况可能有很多种，所以这里按照删除的次数进行分类讨论。

### 1. 删除 $1$ 次

这个有 $3$ 种情况。

1. 起点在第一列，终点在最后一列，这样要删除的文件夹就排成了一个矩形。图就不放了。

2. 起点和终点在同一行。图也不放了。

3. 起点在第一列，终点是**最后一个文件夹**。我们都知道，在文件资源管理器中是可以选空白的，所以这种情况我们也只需删除一次。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rzm58cp2.png)

### 2.删除 $2$ 次

这个有 $4$ 种情况。

1. 起点在第一列或者终点在最后一列。在这种情况下，我们只需先删除一个矩形区域，再删除不完整的单独一行就可以了。如图：（`#` 代表需要删掉，`%` 代表已经删掉）

```
# # # # #		. . . . #
# # # # #		# # # # #
# # # # .		# # # # #
. . . . .		. . . . .
第一步
% % % % %		. . . . #
% % % % %		% % % % %
# # # # .		% % % % %
. . . . .		. . . . .
第二步
% % % % %		. . . . %
% % % % %		% % % % %
% % % % .		% % % % %
. . . . .		. . . . .
```
看，没骗你吧？两次就全删完了。

2. 终点是最后一个文件夹。在这种情况下，我们只需要先删除起点所在的一行，再把下面的都框起来删掉了。原理和情况 $1-3$ 相同，只是起点不在第一列。如图：

```
. . . . .
. . . # #
# # # # #
# # # #
第一步 
. . . . .
. . . % %
# # # # #
# # # #
第二步 
. . . . .
. . . % %
% % % % %
% % % %
```

3. 起点在终点前面一列。这个比较难想，但是我们有图。如图：

```
. . # # #
# # # # #
# # . . .
第一步
. . # # #
% % # # #
% % . . .
第二步
. . % % %
% % % % %
% % . . . 
```

不难看出，只需要先后删除左右两个矩形就行了。

4. 要删除的文件夹只占据了两行。此时我们只需要先后删除两行的文件夹即可。如图：

```
. . # # #
# # # # .
第一步
. . % % %
# # # # .
第二步
. . % % %
% % % % . 
```

到这里，我们就把删除 $2$ 次的所有情况讨论完了。

### 3.删除 $3$ 次

如果到了这里，程序还没结束，那剩下的就一定是 $3$ 次的，直接输出即可。

### 代码实现

求出起点，终点的 $x,y$ 坐标，这样方便比较，计算。为避免重复输出，我 `define` 了一下，这样输出答案后会直接退出。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define o(x) cout<<x;return 0;

int main(){
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	int stx=a%m;
	if(stx==0){stx=m;}
	int edx=b%m;
	if(edx==0){edx=m;}
	int sty=a/m;
	if(a%m!=0){sty++;}
	int edy=b/m;
	if(b%m!=0){edy++;}
	//result=1 
	if(stx==1&&edx==m){
		o(1);
	}
	else if(stx==1&&b==n){
		o(1);
	}
	else if(sty==edy){
		o(1);
	}
	//result=2
	if(stx==1||edx==m){
		o(2);
	}
	else if(b==n){
		o(2);
	}
	else if(stx-1==edx){
		o(2);
	}
	else if(sty+1==edy){
		o(2);
	}
	//result=3 
	o(3);
}
//https://codeforces.com/contest/93/submission/302860844
```

总结：做这道题需要非常细心，把所有的情况都考虑到。

~~最后附上一张图：~~

![](https://cdn.luogu.com.cn/upload/image_hosting/eniqtczc.png)

---

## 作者：billtun (赞：0)

关于这一道分支题目竟然卡了我一个半小时。

## 题目大意：
给出 $n$ 个数，一行 $m$ 个，一共排成 $\left\lceil\dfrac{n}{m}\right\rceil$ 行。想给出连续的一些数字 $a \sim b$，求最少用几个矩形方框把它们都框起来。

## 思路：挨个判断。

### 判断过程：

- 若 $a,b$ 在同一行：要一次。

- 若 $a,b$ 在相邻行：

	- 若 $a$ 为第一个：

		- 若 $b$ 在该行最后一个或 $b$ 是最后一个：要一次。

		- 否则：要两次。

	- 若 $b$ 为第 $n$ 个：
    
		- 若 $a$ 在第一行（或 $a$ 为第一个）：要一次。

		- 否则：要两次。

	- 若 $a$ 在第一列且 $b$ 在最后一列：要一次。

	- 否则：要两次。

- 若 $a,b$ 所在行不相邻：

	- 若 $a$ 为第一个：

		- 若 $b$ 在该行最后一个或 $b$ 是最后一个：要一次。

		- 否则：要两次。

	- 若 $b$ 为第 $n$ 个：
    
		- 若 $a$ 在第一行（或 $a$ 为第一个）：要一次。

		- 否则：要两次。

	- 若 $a$ 在第一列：

		- 若 $b$ 在第一列：要两次。

		- 若 $b$ 不在第一列也不在最后一列：要两次。

		- 若 $b$ 在最后一列：要一次。

	- 若 $a$ 不在第一列也不在最后一列：

		- 若 $b$ 在第一列：

			- 若 $a$ 在第二列：要两次。

			- 否则：要三次。

		- 若 $b$ 不在第一列也不在最后一列：

			- 若 $b$ 所在列为 $a$ 所在列前一列：要两次。

			- 否则：要三次。

		- 若 $b$ 在最后一列：要两次。
    
	- 若 $a$ 在最后一列：

		- 若 $b$ 在第一列：

			- 如果一共就 $2$ 列：要两次。

			- 否则：要三次。

		- 若 $b$ 不在第一列也不在最后一列：

			- 若 $b$ 所在列为倒数第二列：要两次。

			- 否则：要三次。

		- 若 $b$ 在最后一列：要两次。

切记：`return 0;` 不可漏！

## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll n, m, a, b, line_a, line_b;

int main()
{
	cin>>n>>m>>a>>b;
	line_a=a/m+(a%m!=0); // a所在列数
	line_b=b/m+(b%m!=0); // b所在列数
	
	if(m==1){ cout<<1; return 0; } // 小特判
	
	if(line_a==line_b){
		cout<<1;
		return 0;
	} else if(line_a+1==line_b){
		if(a==1){
			if(b%m==0 || b==n){
				cout<<1;
			} else{
				cout<<2;
			}
			return 0;
		} if(b==n){
			if(a%m==1 || a==1){
				cout<<1;
			} else{
				cout<<2;
			}
			return 0;
		}
		
		if(a%m==1 && b%m==0){
			cout<<1;
			return 0;
		} else{
			cout<<2;
			return 0;
		}
	} else{
		if(a==1){
			if(b%m==0 || b==n){
				cout<<1;
			} else{
				cout<<2;
			}
			return 0;
		} if(b==n){
			if(a%m==1 || a==1){
				cout<<1;
			} else{
				cout<<2;
			}
			return 0;
		}
		
		if(a%m==1){
			if(b%m==1){
				cout<<2;
				return 0;
			} else if(b%m!=0){
				cout<<2;
				return 0;
			} else{
				cout<<1;
				return 0;
			}
		} else if(a%m!=0){
			if(b%m==1){
				if(a%m==2){
					cout<<2;
					return 0;
				} else{
					cout<<3;
					return 0;
				}
			} else if(b%m!=0){
				if(a%m-1==b%m){
					cout<<2;
					return 0;
				} else{
					cout<<3;
					return 0;
				}
			} else{
				cout<<2;
				return 0;
			}
		} else{
			if(b%m==1){
				if(m==2){
					cout<<2;
					return 0;
				} else{
					cout<<3;
					return 0;
				}
			} else if(b%m!=0){
				if(b%m==m-1){
					cout<<2;
					return 0;
				} else{
					cout<<3;
					return 0;
				}
			} else{
				cout<<2;
				return 0;
			}
		}
	}
	return 0;
}
```

## 较清楚的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll n, m, a, b, line_a, line_b;

int main()
{
	cin>>n>>m>>a>>b;
	line_a=a/m+(a%m!=0); // a所在列数
	line_b=b/m+(b%m!=0); // b所在列数
	
	if(m==1){ cout<<1; return 0; } // 小特判
	
	if(line_a==line_b)
	{
		cout<<1;
		return 0;
	}
	else if(line_a+1==line_b)
	{
		if(a==1)
		{
			if(b%m==0 || b==n)
			{
				cout<<1;
			}
			else
			{
				cout<<2;
			}
			return 0;
		}
		if(b==n)
		{
			if(a%m==1 || a==1)
			{
				cout<<1;
			}
			else
			{
				cout<<2;
			}
			return 0;
		}
		
		if(a%m==1 && b%m==0)
		{
			cout<<1;
			return 0;
		}
		else
		{
			cout<<2;
			return 0;
		}
	}
	else
	{
		if(a==1)
		{
			if(b%m==0 || b==n)
			{
				cout<<1;
			}
			else
			{
				cout<<2;
			}
			return 0;
		}
		if(b==n)
		{
			if(a%m==1 || a==1)
			{
				cout<<1;
			}
			else
			{
				cout<<2;
			}
			return 0;
		}
		
		if(a%m==1)
		{
			if(b%m==1)
			{
				cout<<2;
				return 0;
			}
			else if(b%m!=0)
			{
				cout<<2;
				return 0;
			}
			else
			{
				cout<<1;
				return 0;
			}
		}
		else if(a%m!=0)
		{
			if(b%m==1)
			{
				if(a%m==2)
				{
					cout<<2;
					return 0;
				}
				else
				{
					cout<<3;
					return 0;
				}
			}
			else if(b%m!=0)
			{
				if(a%m-1==b%m)
				{
					cout<<2;
					return 0;
				}
				else
				{
					cout<<3;
					return 0;
				}
			}
			else
			{
				cout<<2;
				return 0;
			}
		}
		else
		{
			if(b%m==1)
			{
				if(m==2)
				{
					cout<<2;
					return 0;
				}
				else
				{
					cout<<3;
					return 0;
				}
			}
			else if(b%m!=0)
			{
				if(b%m==m-1)
				{
					cout<<2;
					return 0;
				}
				else
				{
					cout<<3;
					return 0;
				}
			}
			else
			{
				cout<<2;
				return 0;
			}
		}
	}
	return 0;
}
```

~~不知道为什么其他题解的代码都一模一样~~。

---

## 作者：Nuclear_Fish_cyq (赞：0)

情况很多，很难枚举，这也是这道题恶心的点。

第一，如果 a 与 b 同行，那么只需要一次即可完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/aqz6k42g.png)

第二，如果 a 在第一列且 b 在最后一列，那么也可以一次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/vrd9bjdy.png)

第三，如果 a 在第一列且 b 在最后，也是可以一次的。

![](https://cdn.luogu.com.cn/upload/image_hosting/og9ezja6.png)

第四，如果前面的都不是（后面都假设这条），如果 a 在第一列，那么可以二次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/2zr9ixdm.png)

第五，如果 b 在最后一列，那么也可以二次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/ivous918.png)

第六，如果 a 在 b 上面一行，那么也可以二次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ji5r4ew.png)

第七，如果 a 在 b 左边一列，也可以二次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/ln0gochc.png)

第八，如果 b 在结尾，也可以二次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/9qie3167.png)

最后，一定可以三次完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/mrmb8lb7.png)

上代码，码风可能偏奇怪，不要在意。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, a, b, xa, xb, ya, yb;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> a >> b;
	xa = (a - 1) / m + 1;//a在第几行 
	ya = (a - 1) % m + 1;//a在第几列 
	xb = (b - 1) / m + 1;//b在第几行 
	yb = (b - 1) % m + 1;//b在第几列 
	if(xa == xb){//a和b在同一行 
		cout << 1 << endl;
		return 0;
	}
	if(ya == 1 && yb == m){//a第一列，b最后一列 
		cout << 1 << endl;
		return 0;
	}
	if(ya == 1 && b == n){//a第一列，b最后一个 
		cout << 1 << endl;
		return 0;
	}
	if(ya == 1){//a在第一列，b无限制 
		cout << 2 << endl;
		return 0;
	}
	if(yb == m){//a无限制,b在最后一列
		cout << 2 << endl;
		return 0;
	}
	if(xb - xa == 1){//a在b上面一行 
		cout << 2 << endl;
		return 0;
	}
	if(ya - yb == 1){//a在b右边一列 
		cout << 2 << endl;
		return 0;
	}
	if(b == n){//a无限制，b最后一个 
		cout << 2 << endl;
		return 0;
	}
	cout << 3 << endl;//无限制
	return 0;
}

```


---

## 作者：taikongsha (赞：0)

# **题意**

在一个 $D$ 盘中有 $n$ 个文件夹，序号分别是从 $1\sim n$ 的正整数。

让你删除 $a\sim b$ 的文件夹，让你求删除他们的最小次数。


# **思路**

要删的文件夹有十分多种情况，但删除他们的次数却是固定在 $1\sim 3$ 上。只要找到次数分别是 $1$、$2$、$3$ 时文件夹的情况就行。~~（这道顶多是个黄题）~~

## 1. -答案为 $1$ 的情况

- 只有一行或一列。

- 只要选择一行内的。

- 是一个矩形。

- 开头是整行，选到整个n个文件的末尾（实现时可以一开始如果 $b=n$ 直接把 $b$ 变到最后一行的末尾）。

- 选择全部。

## 2. 答案为 $2$ 的情况

- 只有两行。

- 只要选两行内的。

- 一种比较隐蔽的情况。
![](https://i0.hdslb.com/bfs/article/a8749baee8852b6e2ffa03ae3c107848c8762b63.png@1256w_650h_!web-article-pic.webp)

## 3. 答案为 $3$ 的情况
- 如果不是答案为 $1$ 或 $2$ 的情况就都输出 $3$。


# **上代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

long long int n,m;	// n 是文件夹的个数，m 是每行文件夹的个数 
long long int a,b;	// a 是第 1 个删除文件的下标，b 是最后一个删除文件的下标  

int main(){
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	if(b==n) b=ceil(b*1.0/m)*m;
	int ans=0;
	if(a==b){
		cout<<1<<endl;
		return 0;
	}
	if(ceil(a*1.0/m)==ceil(b*1.0/m)){
		cout<<1<<endl;
		return 0;
	}
	if(m==1){
		cout<<1<<endl;
		return 0;
	}
	if(a%m==1&&b%m==0) cout<<1<<endl;
	else if(ceil(b*1.0/m)-ceil(a*1.0/m)==1) cout<<2<<endl;
	else if((a-1)%m==b%m) cout<<2<<endl;
	else if(ceil(b*1.0/m)-ceil(a*1.0/m)==1) cout<<2<<endl;
	else if(a%m==1&&b%m!=0) cout<<2<<endl;
	else if(a%m!=1&&b%m==0) cout<<2<<endl;
	else if(b<=(a-1)/m*m+m) cout<<1<<endl;
	else if(b==n&&a%m==1) cout<<1<<endl;
	else if(b<=(a-1)/m*m+2*m) cout<<2<<endl;
	else cout<<3<<endl;
	return 0;
}
```


---

