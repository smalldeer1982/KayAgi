# Lights Out

## 题目描述

$Lenny$ 正在操作一个 $3×3$ 大小的网格。 在游戏开始时，所有数都为 $1$ 。 操作任何一个指示灯都会改变它以及它上下左右四个相邻的网格（要在 $3×3$ 网格内）。每次操作时，所有需要改变的数均由 $0$ 变为 $1$ 或者由 $1$ 变为 $0$ 。
 
现在 $Lenny$ 已经操作了每一格一定次数。给定每个方格的操作次数，请输出每个方格的最终数值。

## 样例 #1

### 输入

```
1 0 0
0 0 0
0 0 1
```

### 输出

```
001
010
100
```

## 样例 #2

### 输入

```
1 0 1
8 8 8
2 0 3
```

### 输出

```
010
011
100
```

# 题解

## 作者：封禁用户 (赞：1)

蒟蒻来发一篇Pascal题解啦！

题目传送门：[CF275A Lights Out](https://www.luogu.com.cn/problem/CF275A)

题目大意：不用讲了吧。。。

**题解：** 很显然，当网格中的数是偶数，无论多大，都会变回来；若是奇数，就改变一下上下左右和自己就好了。

$Code:$

```pascal
var f:array[0..5,0..5] of boolean;
    n,i,j,p,q:longint;
begin
  for i:=1 to 3 do //变为1
    for j:=1 to 3 do
      f[i,j]:=true;
  for i:=1 to 3 do
    for j:=1 to 3 do
    begin
      read(n);
      if n and 1=1 then //假如是奇数就变
      begin
        f[i,j]:=not f[i,j];
        f[i-1,j]:=not f[i-1,j];
        f[i+1,j]:=not f[i+1,j];
        f[i,j-1]:=not f[i,j-1];
        f[i,j+1]:=not f[i,j+1];
      end;
    end;
  for i:=1 to 3 do //输出
  begin
    for j:=1 to 3 do
    begin
      if f[i,j]=true then write('1')
      else write('0');
    end;
    writeln('');
  end;
end.
```


---

## 作者：Rosmarinus (赞：0)

## 题目大意

开/关灯类题目。

## 思路分析

由于数据范围不大，似乎暴力也不会炸。

显然在一个地方开关 $2$ 次和不开关是完全一样的。

因此对于每一个输入可以模 $2$ 后再操作，会大大减少时间复杂度。

## Code

```cpp
#include<iostream>
using namespace std;

int a[10][10];

int main()
{
	int x;
	for(int i = 1; i <= 3; i ++)
	{
		for(int p = 1; p <= 3; p ++)
		{
			cin >> x;
			x %= 2;
			if(x) a[i][p] ^= 1, a[i + 1][p] ^= 1, a[i - 1][p] ^= 1, a[i][p + 1] ^= 1, a[i][p - 1] ^= 1;
		}
	}
	for(int i = 1; i <= 3; i ++)
	{
		for(int p = 1; p <= 3; p ++)
		{
			cout << 1 - a[i][p];
		}
		cout << endl;
	}		
}
```

---

## 作者：小杨小小杨 (赞：0)

## 题意
给你一个矩阵，对于每一个格子，每进行一次变化就会使上下左右和自己取反。初始每一个格子都是一，取反一次变成零。问你对每一个格子进行输入次操作，结果如何？
## 思路
暴力出奇迹，对于每一个格子，直接暴力做输入次，把上下左右和自己全部取反（用一减去当前状态）即可。数据比较小，绝对不超时。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,x,k,a[11][11];
void nots(int i,int j){//把上下左右和自己全部取反
	a[i][j]=1-a[i][j];
	a[i+1][j]=1-a[i+1][j];
	a[i][j+1]=1-a[i][j+1];
	a[i-1][j]=1-a[i-1][j];
	a[i][j-1]=1-a[i][j-1];
}
int main(){
	for (i=1;i<=3;i++)
		for (j=1;j<=3;j++) 
			a[i][j]=1;//初始化
	for (i=1;i<=3;i++){
		for (j=1;j<=3;j++){
			scanf("%d",&x);
			for (k=1;k<=x;k++)//暴力做输入次
				nots(i,j);//逐个取反
		}
	}	
	for (i=1;i<=3;i++,putchar(10))
		for (j=1;j<=3;j++) 
			printf("%d",a[i][j]);//输出
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
有一个 $3\times 3$ 的矩阵。一开始每个元素都为 $1$。

你可以对任意的位置进行操作，每次操作将在这个位置上的元素及其上下左右的元素全部由 $1$ 改为 $0$ 或者将 $0$ 改为 $1$。

现在给定每个位置上的操作次数 $x_{i,j}$，求执行完全部的操作后矩阵里每个元素的值。

**数据范围：$0\leqslant x_{i,j}\leqslant 100$。**
## Solution
我们可以发现两个非常显然的结论：

- 如果在某个位置上的操作次数为偶数，那么就相当于没有做。因为你做了偶数次之后，总会变回原来的元素的值，比如 $0\rightarrow1\rightarrow0,1\rightarrow0\rightarrow1$。
- 如果在某个位置上的操作次数为奇数，那么就相当于只做了一次。由上面我们可以发现，做偶数次之后就相当于没做，所以做奇数次肯定只有最后一次有效果。

所以我们想到了这样的一个算法：先将矩阵上的元素全部初始化为 $1$，然后找那个位置上的操作次数是奇数次，是奇数次就将这个位置上的元素以及其上下左右的元素全部调换，最后输出结果。
## Code
```cpp
#include <cstdio>
using namespace std;

int a[7][7], ans[7][7];
const int dx[5] = {0, 0, 0, 1, -1};
const int dy[5] = {0, 1, -1, 0, 0};

int main() {
	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 3; ++j)
			ans[i][j] = 1;
	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 3; ++j) {
			scanf("%d", &a[i][j]);
			if(a[i][j] % 2)	
				for(int k = 0; k < 5; ++k)
					ans[i + dx[k]][j + dy[k]] = 1 - ans[i + dx[k]][j + dy[k]];
		}
	for(int i = 1; i <= 3; puts(""), ++i)
		for(int j = 1; j <= 3; ++j)	printf("%d", ans[i][j]);
}
```

---

## 作者：引领天下 (赞：0)

来一发比较简单的题解。

由于每个格子只有 0 和 1 两种状态，所以我们完全可以开一个 bool 数组模拟，每次操作即为取非。

然后由于一个数连续取非两次相当于没取，所以我们只用考虑奇数次的操作。

至于越界的问题，我们与其去写一堆 if 进行判断，不如直接数组开大一点，让他自然越界呗。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[5][5];//数组开大一点，就能避免越界
//全局数组初始全 0 ，并不影响。到时候输出的时候统一取非一下就可以了。
int x;
int main(){
    for (int i=1;i<=3;i++)
    for (int j=1;j<=3;j++){
        scanf("%d",&x);
        if(x&1)a[i-1][j]=!a[i-1][j],a[i][j-1]=!a[i][j-1],a[i+1][j]=!a[i+1][j],a[i][j+1]=!a[i][j+1],a[i][j]=!a[i][j];//如果是奇数，按题面模拟
    }
    for (int i=1;i<=3;i++,puts(""))
    for (int j=1;j<=3;j++)printf("%d",!a[i][j]);//取非输出
}
```

---

## 作者：Peter0701 (赞：0)

给定一张 $3 \times 3$ 的棋盘（起初全为 $1$ ），每格均有一个操作次数。操作是将其上的数以及上下左右四格的数取反（ $0$ 变为 $1$ , $1$ 变为 $0$ ）。请输出所有操作结束后的局面。

题目比较简单，直接按题意模拟即可。

从本质上来说，对于同一格进行偶数次操作后局面不会有任何变化（即不影响答案），于是不用考虑对它们进行操作。为了加速算法，判断只有操作次数为偶数次时才修改。（当然，由于本题数据范围小，不加速也是可以通过的。）修改前要判定被修改的格子是否合法，即是否在 $3 \times 3$ 的棋盘内。

然后输出最终局面这道题就结束了。请注意输出格式。如有疑问，评论区见。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int a[4][4];
bool b[4][4];
inline void modify(int x,int y)
{
	if(b[x][y])
		b[x][y]=0;
	else
		b[x][y]=1;
}
int main()
{
	for(register int i=1;i<=3;i++)
		for(register int j=1;j<=3;j++)
			a[i][j]=read();
	for(register int i=1;i<=3;i++)
		for(register int j=1;j<=3;j++)
			b[i][j]=1;
	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=3;j++)
		{
			if(a[i][j]&1)
			{
				modify(i,j);
				if(i-1>0)
					modify(i-1,j);
				if(j-1>0)
					modify(i,j-1);
				if(i+1<4)
					modify(i+1,j);
				if(j+1<4)
					modify(i,j+1);
			}
		}
	}
	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=3;j++)
			printf("%d",b[i][j]);
		printf("\n");
	}
	return 0;
}
```


---

