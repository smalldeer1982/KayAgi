# Death Stars (easy)

## 题目描述

The stardate is 1977 and the science and art of detecting Death Stars is in its infancy. Princess Heidi has received information about the stars in the nearby solar system from the Rebel spies and now, to help her identify the exact location of the Death Star, she needs to know whether this information is correct.

Two rebel spies have provided her with the maps of the solar system. Each map is an $ N×N $ grid, where each cell is either occupied by a star or empty. To see whether the information is correct, Heidi needs to know whether the two maps are of the same solar system, or if possibly one of the spies is actually an Empire double agent, feeding her false information.

Unfortunately, spies may have accidentally rotated a map by 90, 180, or 270 degrees, or flipped it along the vertical or the horizontal axis, before delivering it to Heidi. If Heidi can rotate or flip the maps so that two of them become identical, then those maps are of the same solar system. Otherwise, there are traitors in the Rebel ranks! Help Heidi find out.

## 说明/提示

In the first test, you can match the first map to the second map by first flipping the first map along the vertical axis, and then by rotating it 90 degrees clockwise.

## 样例 #1

### 输入

```
4
XOOO
XXOO
OOOO
XXXX
XOOO
XOOO
XOXO
XOXX
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2
XX
OO
XO
OX
```

### 输出

```
No
```

# 题解

## 作者：zhouchuer (赞：2)

题目大意：有两张 $n \times n$ 的图，只有 `X` 和 `O` 这两种字符，问你能否通过旋转和翻转使得两个图形一致。

纯模拟，考虑分类讨论，去掉重复的有以下 $8$ 种情况：
1. 两个完全一样。
2. 水平翻转一次。
3. 竖直翻转一次。
4. 竖直翻转一次后水平翻转一次。
5. 逆时针旋转 $90$ 度后水平翻转一次。
6. 逆时针旋转 $90$ 度后竖直翻转一次。
7. 逆时针旋转 $90$ 度后竖直翻转一次，再水平翻转一次。
8. 无论如何操作都无法相同。

代码就不贴了，根据给出的情况模拟即可。

---

## 作者：__UrFnr__ (赞：1)

**题目思路：**

题目大意没什么好说的，思路才是重要。

首先一共有 $8$ 种操作的方式。

+ 不进行操作
+ 竖直翻转一次
+ 水平反转一次
+ 水平翻转一次再竖直翻转一次
+ 逆时针旋转 $90^{\circ} $ 再竖直翻转一次
+ 逆时针旋转 $90^{\circ} $ 再水平翻转一次
+ 逆时针旋转 $90^{\circ} $ 再竖直翻转一次再水平翻转一次
+ 无论怎么操作都无法相同

程序模拟实现即可，就不粘代码了。

---

## 作者：cute_overmind (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF958A1)

### 题目大意
给定你**两张** $n\times n$ 的图，每张图只存在 `X` 和 `O` 两种字符。

问你将第一张图通过**旋转**或**翻折**后能不能变成第二张图。
### 题目分析
考虑**分类讨论**。

其实我们可以分为以下 $16$ 种情况进行操作：
- 不变。
- 顺时针旋转 $90$ 度。
- 顺时针旋转 $180$ 度。
- 顺时针旋转 $270$ 度。
- 水平方向进行翻折后不变。
- 水平方向进行翻折后顺时针旋转 $90$ 度。
- 水平方向进行翻折后顺时针旋转 $180$ 度。
- 水平方向进行翻折后顺时针旋转 $270$ 度。
- 竖直方向进行翻折后不变。
- 竖直方向进行翻折后顺时针旋转 $90$ 度。
- 竖直方向进行翻折后顺时针旋转 $180$ 度。
- 竖直方向进行翻折后顺时针旋转 $270$ 度。
- 水平方向进行翻折后竖直方向进行翻折。
- 水平方向进行翻折后竖直方向进行翻折。
- 水平方向进行翻折后竖直方向进行翻折。
- 水平方向进行翻折后竖直方向进行翻折。

但是我们可以发现，在这 $16$ 种情况中是有 $8$ 种情况重复。

所以此时，若可以得到图二，那么最多会有 $8$ 张图。
### 代码
代码就不贴了，纯模拟即可。

---

## 作者：_Michael0727_ (赞：0)

# 题解：

[文章食用效果更佳](https://www.luogu.com.cn/article/kemdig6d)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF958A1)

---

## 思路

总体操作是旋转和翻转，可以编函数进行处理。

- 顺时针旋转 90°

```cpp
	for ( int i = 1 ; i <= n ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ )
		{
			t [i] [j] = a [n + 1 - j] [i] ;
		}
	}
```

- 顺时针旋转 180°

```cpp
	for ( int i = 1 ; i <= n ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ )
		{
			t [i] [j] = a [n + 1 - i] [n + 1 - j] ;
		}
	}
```

- 顺时针旋转 270°

```cpp
	for ( int i = 1 ; i <= n ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ )
		{
			t [i] [j] = a [j] [n + 1 - i] ;
		}
	}
```

- 横向翻转

```cpp
	for ( int i = 1 ; i <= n ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ )
		{
			t [i] [j] = a [i] [n + ( n % 2 ) - j] ;
		}
	}
```

- 竖向翻转

```cpp
	for ( int i = 1 ; i <= n ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ )
		{
			t [i] [j] = a [n + ( n % 2 ) - i] [j] ;
		}
	}
```

枚举得，总共有以下 $8$ 种操作方式

- 两个完全一样。

- 水平翻转一次。

- 竖直翻转一次。

- 竖直翻转一次后水平翻转一次。

- 逆时针旋转 $90$ 度后水平翻转一次。

- 逆时针旋转 $90$ 度后竖直翻转一次。

- 逆时针旋转 $90$ 度后竖直翻转一次后水平翻转一次。

- 无论如何都无法相同。

按以上操作模拟判断即可

---

**AC 代码**

不贴代码。

---

## 作者：GeYang (赞：0)

# 题意

给你两个 $n \times n$ 的由 `X` 和 `O` 组成的矩阵，问能否通过旋转或镜面翻转使这两个矩阵一样。

# 思路
所有情况可分为以下几种情况。

- 两个完全一样不需要做任何改变。

- 水平翻转一次。

- 竖直翻转一次。

- 竖直翻转一次后水平翻转一次。

- 逆时针旋转 $90$ 度后水平翻转一次。

- 逆时针旋转 $90$ 度后竖直翻转一次。

- 逆时针旋转 $90$ 度后竖直翻转一次后水平翻转一次。

- 无论如何都无法相同。

# 代码

模拟即可。

---

## 作者：_mi_ka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF958A1)

## 题目大意

给出两张只含有 `X` 和 `O` 的表，问是否能通过旋转和翻转把其中一个变为另一个。

## 解题思路

~~这题一看就是一道大水题！！！~~

算法：**模拟**所有情况。

首先我们先画出一张简单的表模拟一下（设两张表分别为 $A$ 和 $B$）：

初始的 $A$：

| $A$ | $B$ |
| :-: | :-: |
| $C$ | $D$ |

这里一共有 $8$ 种对 $A$ 操作后的表：

顺时针：$ABCD$（四种）

逆时针：$DCBA$（四种）

Details:

1. 不进行改变

| $A$ | $B$ |
| :-: | :-: |
| $C$ | $D$ |

对应布尔判断式 $A_{i,j}=B_{i,j}$（$A$ 操作后对应 $B$ 的位置）；

2. 竖直翻转一次

| $C$ | $D$ |
| :-: | :-: |
| $A$ | $B$ |

对应布尔判断式 $A_{i,j}=B_{n-i+1,j}$；

3. 水平翻转一次

| $B$ | $A$ |
| :-: | :-: |
| $D$ | $C$ |

对应布尔判断式 $A_{i,j}=B_{i,n-j+1}$；

4. 水平翻转一次再竖直翻转一次

| $D$ | $C$ |
| :-: | :-: |
| $B$ | $A$ |

对应布尔判断式 $A_{i,j}=B_{n-i+1,n-j+1}$；


5. 左旋 $90^{\circ}$ 再竖直翻转一次

| $A$ | $C$ |
| :-: | :-: |
| $B$ | $D$ |

对应布尔判断式 $A_{i,j}=B_{j,i}$；

6. 左旋 $90^{\circ}$ 再竖直翻转一次再竖直翻转一次

| $B$ | $D$ |
| :-: | :-: |
| $A$ | $C$ |

对应布尔判断式 $A_{i,j}=B_{n-j+1,i}$；

7. 左旋 $90^{\circ}$ 再竖直翻转一次再水平翻转一次

| $C$ | $A$ |
| :-: | :-: |
| $D$ | $B$ |

对应布尔判断式 $A_{i,j}=B_{j,n-i+1}$；

8. 左旋 $90^{\circ}$ 再竖直翻转一次再水平翻转一次再竖直翻转一次

| $D$ | $B$ |
| :-: | :-: |
| $C$ | $A$ |

对应布尔判断式 $A_{i,j}=B_{n-j+1,n-i+1}$。

经证明，其他所有翻转旋转情况都是这 $8$ 种情况的任意一种。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#define N 12
using namespace std;
int n,flag;
char A[N][N],B[N][N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>(A[i]+1);
	for(int i=1;i<=n;i++)
		cin>>(B[i]+1);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[i][j])//枚举每一种 
				flag=0;
	if(flag)
		puts("Yes"),exit(0);//某种情况符合直接输出 Yes，然后结束程序 
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-i+1][j])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[i][n-j+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-i+1][n-j+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[j][i])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-j+1][i])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[j][n-i+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-j+1][n-i+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	puts("No");//都不符合，输出 No  
	return 0;
}

```

~~屎山~~代码有点难看，不过还是通俗易懂的吧。

---

## 作者：lol_qwq (赞：0)

# CF958A1 题解

### 分析

一道水题，判断是否可以通过反转或旋转得到图案。

先分四类，旋转，翻转，旋转和反转，不变。

旋转：我们可以分成 $3$ 类，旋转 $90,180,270$ 度。

$90$ 度代码：

```
for(int i = 1;i <= n;i++){
    a++;
    for(int j = 1;j <= n;j++){
       b++;
       //把方块旋转即可
    }
}
```

反转类似旋转，就不放了。

如果两图相等，直接输出 ```Yes```。

因为次数最多只需 $4$ 次，但是代码要运行 $16$ 次，超出 $16$ 次其实可以输出 ```No```。

---

## 作者：zzy0618 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF958A1)

这题其实并不难，评黄应该有点高，和[这题](https://www.luogu.com.cn/problem/P1205)比起来还要简单一些。

由于旋转 $180,270$ 度可以通过多次旋转 $90$ 度完成，所以只用写一个旋转 $90$ 度的函数即可，而翻转这种事情只用在旋转过程中完成即可。

1. 首先是判断是否一样的函数，挨个检查。

```cpp
inline bool check(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]!=b[i][j])
				return 0;
	return 1;
}
```

2. 旋转 $90$ 度的函数，这里读者可以自己推一下式子。使用一个临时数组，翻转以后再复制过去。

```cpp
inline void f1(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[j][n-i+1]=a[i][j];//c是一个临时数组
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=c[i][j];
}
```

3. 翻转的函数，其实就是把方阵每个相对的元素左右交换。

```cpp
inline void f2(){
	for(int i=1;i<=n;i++)
		for(int j=1;j*2<=n;j++)
			swap(a[i][j],a[i][n-j+1]);
}
```

由于旋转 $4$ 个 $90$ 度相当于没转，所以我们只要旋转 $4$ 次，中间再翻转检查一下就行，以下是完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[13][13],b[13][13],c[13][13];
inline bool check(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]!=b[i][j])
				return 0;
	return 1;
}
inline void f1(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[j][n-i+1]=a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=c[i][j];
}
inline void f2(){
	for(int i=1;i<=n;i++)
		for(int j=1;j*2<=n;j++)
			swap(a[i][j],a[i][n-j+1]);
}
signed main(){
	int i,j;cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>b[i][j];
	for(i=1;i<=4;i++){//最多只需要转4次
		f1();
		if(check()){cout<<"Yes";return 0;}
		f2();
		if(check()){cout<<"Yes";return 0;}
		f2();//记得要翻转回去
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF958A1)

这一道题，我们可以分为 $7$ 种情况：
- 图案按顺时针转 $90$ 度。
- 图案按顺时针转 $270$ 度。
- 图案按顺时针转 $180$ 度。
- 图案按水平方向翻转。
- 图案按水平翻转后，再进行情况 $1\sim4$。
- 图案不改变。
- 图案无法改变为目标图案。

接下来，一个一个讲解。

## 第一种情况：图案按顺时针转 $90$ 度。
### 打表：
变化前：

![](https://asset.gitblock.cn/Media?name=A73BB1F09F6197151FC0F5E3250CD8E2.png)

变化后：

![](https://asset.gitblock.cn/Media?name=2B6EDD1E319DD0DDECF13816C9ED776A.png)

### 可以找到规律：
```
for(int i=1,x=1;i<=n;i++,x++)
   for(int j=n,y=1;j>=1;j--,y++)
    	b[x][y]=a[j][i];
```

## 第二种情况：图案按顺时针转 $180$ 度。
### 打表：
变化前：

![](https://asset.gitblock.cn/Media?name=A73BB1F09F6197151FC0F5E3250CD8E2.png)

变化后：

![](https://asset.gitblock.cn/Media?name=6BE6A53D3B90D8CF801C9650129E37A7.png)

### 可以找到规律：
```
for(int i=n,x=1;i>=1;i--,x++)
    for(int j=n,y=1;j>=1;j--,y++)
    	b[x][y]=a[i][j];
```

## 第三种情况：图案按顺时针转 $270$ 度。
### 打表：
变化前：

![](https://asset.gitblock.cn/Media?name=A73BB1F09F6197151FC0F5E3250CD8E2.png)

变化后：

![](https://asset.gitblock.cn/Media?name=7382A8FA662701B8BB87AE9C194A9843.png)
### 可以找到规律：
```
for(int i=n,x=1;i>=1;i--,x++)
    for(int j=1,y=1;j<=n;j++,y++)
    	b[x][y]=a[j][i];
```

## 第四种情况：图案按水平方向翻转。
### 打表：
变化前：

![](https://asset.gitblock.cn/Media?name=A73BB1F09F6197151FC0F5E3250CD8E2.png)

变化后：

![](https://asset.gitblock.cn/Media?name=9ABAF74C76274F520C7B06B9A4E86003.png)

### 可以找到规律：
```
for(int i=1,x=1;i<=n;i++,x++)
    for(int j=n,y=1;j>=1;j--,y++)
    	b[x][y]=a[i][j];
```

## 第五种情况：图案按水平翻转后，再进行情况 $1\sim4$。
这一种情况就是先水平翻转后，再枚举情况 $1\sim4$。
### 具体代码：
```
			for(int i=1,x=1;i<=n;i++,x++)
		    	for(int j=n,y=1;j>=1;j--,y++)
		    		d[x][y]=a[i][j];
			long long y=0,bj2=0;
			while(y<3)
			{
				bj2=0;
				y++;
				if(y==1)
				    for(int i=1,x=1;i<=n;i++,x++)
				    	for(int j=n,y=1;j>=1;j--,y++)
				    		b[x][y]=d[j][i];
				if(y==2)
				    for(int i=n,x=1;i>=1;i--,x++)
				    	for(int j=n,y=1;j>=1;j--,y++)
				    		b[x][y]=d[i][j];
				if(y==3)
				    for(int i=n,x=1;i>=1;i--,x++)
				    	for(int j=1,y=1;j<=n;j++,y++)
				    		b[x][y]=d[j][i];
				for(int i=1;i<=n;i++)
				{    
					for(int j=1;j<=n;j++)
				    	if(b[i][j]!=c[i][j])
				    	{
				    		bj2=1;
						    break;
						}
				    if(bj2==1) break;
				}
				if(bj2==0)break;
			}
			if(bj2==0)
			{
				cout<<"Yes";
				return 0;
			}
```
## 第六种情况：图案不改变。
最简单，直接比较即可。
## 第七种情况：图案无法改变为目标图案。
当上面六种情况都不满足，就是无法改变的这一种情况。

## 我的代码（码丑勿喷）：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
char a[105][105],b[105][105],c[105][105],d[105][105];
long long x=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		cin>>a[i][j];//输入
	for(int i=1;i<=n;i++)
	   	for(int j=1;j<=n;j++)
	    	cin>>c[i][j];//输入
    while(x<6)
    {
    	x++;
    	if(x==1)//情况 1。
    		for(int i=1,x=1;i<=n;i++,x++)
    			for(int j=n,y=1;j>=1;j--,y++)
    				b[x][y]=a[j][i];
   	 	if(x==3)//情况 3。
    		for(int i=n,x=1;i>=1;i--,x++)
    			for(int j=1,y=1;j<=n;j++,y++)
    				b[x][y]=a[j][i];
   		if(x==4)//情况 4。
    		for(int i=1,x=1;i<=n;i++,x++)
    			for(int j=n,y=1;j>=1;j--,y++)
    				b[x][y]=a[i][j];
    	if(x==2)//情况 2。
    		for(int i=n,x=1;i>=1;i--,x++)
    			for(int j=n,y=1;j>=1;j--,y++)
    				b[x][y]=a[i][j];
    	if(x==5)//情况 5。
		{
		    for(int i=1,x=1;i<=n;i++,x++)
		    	for(int j=n,y=1;j>=1;j--,y++)
		    		d[x][y]=a[i][j];
			long long y=0,bj2=0;
			while(y<3)
			{
				bj2=0;
				y++;
				if(y==1)
				    for(int i=1,x=1;i<=n;i++,x++)
				    	for(int j=n,y=1;j>=1;j--,y++)
				    		b[x][y]=d[j][i];
				if(y==2)
				    for(int i=n,x=1;i>=1;i--,x++)
				    	for(int j=n,y=1;j>=1;j--,y++)
				    		b[x][y]=d[i][j];
				if(y==3)
				    for(int i=n,x=1;i>=1;i--,x++)
				    	for(int j=1,y=1;j<=n;j++,y++)
				    		b[x][y]=d[j][i];
				for(int i=1;i<=n;i++)
				{    
					for(int j=1;j<=n;j++)
				    	if(b[i][j]!=c[i][j])
				    	{
				    		bj2=1;
						    break;
						}
				    if(bj2==1) break;
				}
				if(bj2==0)break;
			}
			if(bj2==0)
			{
				cout<<"Yes";
				return 0;
			}
		}
		if(x==6)//情况 6。
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					b[i][j]=a[i][j];
		}
    	long long bj=0;
		for(int i=1;i<=n;i++)
		{
    		for(int j=1;j<=n;j++)
    			if(b[i][j]!=c[i][j])
    			{
    				bj=1;
				    break;
				}
    		if(bj==1)
    		{
    			break;
    		}
    	}
    	if(bj==0)
    	{
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";//情况 7。
	return 0;
}
```

当然，也可以用子函数，你们自己试一试。

----
致审核的管理员：如果有问题，希望能够一次性把问题说完，让我能够认识到自己的错误。（~~管理员留名~~）

致读者：如果有不对的地方，希望指出，共同学习，共同努力。

---

## 作者：LaDeX (赞：0)

## 题意

给定两张仅由 $\mathtt{O}$ 和 $\mathtt{X}$ 组成的 $n\times n$ 的图，问能否通过翻转和旋转将两张图变为一样的。

## 解法

数据范围 $n$ 最大只有 $10$，直接暴力广搜即可。

可以将状态定义为结构体。

每次如果发现之前已经出现过此状态就 `continue`。

我这里用了一个数组记录状态，~~STL写挂了~~。

不好写的是旋转与翻转的操作部分。

$A$ 为原状态，$nxt$ 为新状态。

如果是上下翻转，相当于列不变，第 $i$ 行变为 $n - i + 1$ 行。状态转移式为： $nxt_{n-i+1,j} = A_{i,j}$。

左右翻转同理。
状态转移式为： $nxt_{i,n-j+1} = A_{i,j}$。

如果是左旋，手玩一下可发现就是本来位于第 $i$ 行的人现在在第 $i$ 列，本来在第 $j$ 列的现在位于第 $n-j+1$ 行。
状态转移式为： $nxt_{n-j+1,i} = A_{i,j}$。

右旋也同理。
状态转移式为： $nxt_{j,n-i+1} = A_{i,j}$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mkp(x, y) make_pair(x, y)
#define eb(x) emplace_back(x)
// I Love Yukino Forever!
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 15;
LL n;

struct Status{
	char val[N][N];
	Status(){
		memset(val, 0, sizeof(val));
		return ;
	}
};

const bool operator == (Status a, Status b){
	for (LL i = 1; i <= n; i ++)
		for (LL j = 1; j <= n; j ++)
			if (a.val[i][j] != b.val[i][j])
				return false; 
	return true;
}

const bool operator < (Status a, Status b){
	return a.val[1][1] < b.val[1][1];
}

Status s[10010];
LL len = 0;
bool find(Status x){
	for (LL i = 1; i <= len; i ++)
		if (s[i] == x)
			return true;
	return false;
}

void insert(Status x){
	s[++ len] = x;
	return ;
}

int main(){
	Fcin;
	cin >> n;
	Status A, B;
	for (LL i = 1; i <= n; i ++)
		for (LL j = 1; j <= n; j ++)
			cin >> A.val[i][j];

	for (LL i = 1; i <= n; i ++)
		for (LL j = 1; j <= n; j ++)
			cin >> B.val[i][j];

	queue<Status> q;
	q.push(A);
	while (!q.empty()){
		Status now = q.front(); q.pop();
		if (find(now))
			continue;
		insert(now);

		if (now == B){
			cout << "Yes";
			return 0;
		}

		Status nxt;

		// Flip top to bottom.
		for (LL i = 1; i <= n; i ++)
			for (LL j = 1; j <= n; j ++)
				nxt.val[n - i + 1][j] = now.val[i][j];
		q.push(nxt);

		// Flip left to right.
		for (LL i = 1; i <= n; i ++)
			for (LL j = 1; j <= n; j ++)
				nxt.val[i][n - j + 1] = now.val[i][j];
		q.push(nxt);

		// Rotate left.
		for (LL i = 1; i <= n; i ++)
			for (LL j = 1; j <= n; j ++)
				nxt.val[n - j + 1][i] = now.val[i][j];
		q.push(nxt);

		// Rotate right.
		for (LL i = 1; i <= n; i ++)
			for (LL j = 1; j <= n; j ++)
				nxt.val[j][n - i + 1] = now.val[i][j];
		q.push(nxt);
	}

	cout << "No\n";
	return 0;
}
```


---

## 作者：Swiftie_wyc22 (赞：0)

这道题怎么做的人这么少？难度也不高呀，我觉得可以评橙~黄

就是一个模拟。和官方题解一个思路。

旋转4次还原，水平翻转 2 次还原，垂直翻转 2 次还原。

旋转两次 = 翻转，省略一部分

16 次以内必定还原（实际只用 12 次）

就像官方题解说的
“The constraints allowed to do this in a naive way in $ O(n^2) $ time”、“ Rotations and flips could be also done in a naive way in $ O(n^2) $ ”对于 $n \leq 10$的数据， $ O(n^2) $ 可以轻松切掉

于是模拟就可以写了（说实话一开始我打算写 dfs 的）

```cpp
#include <bits/stdc++.h>

using namespace std;
int n;
char mapa[11][11];
char mapb[11][11];
char mapc[11][11];

bool check() // check if mapa is equals to mapb
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (mapa[i][j] != mapb[i][j])
				return false;
	return true;
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> mapa[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> mapb[i][j];
	
	for (int p = 0; p < 4; p++)
	{
		for (int i = 1; i <= n; i++) // horizontal flip 
			for (int j = n; j > n / 2; j--)
				swap(mapa[i][j], mapa[i][n - j + 1]);
		if (check())
		{
			cout << "Yes" << endl; return 0;
		}
		
		
		for (int i = n; i > n / 2; i--) // vertical flip
			for (int j = 1; j <= n; j++)
				swap(mapa[i][j], mapa[n - i + 1][j]); 
		if (check())
		{
			cout << "Yes" << endl; return 0;
		}
		
		
		for (int i = 1; i <= n; i++)
			for (int j = n; j > n / 2; j--)
				swap(mapa[i][j], mapa[i][n - j + 1]);
		if (check())
		{
			cout << "Yes" << endl; return 0;
		}
		
		
		for (int i = n; i > n / 2; i--) // vertical flip
			for (int j = 1; j <= n; j++)
				swap(mapa[i][j], mapa[n - i + 1][j]); 
		if (check())
		{
			cout << "Yes" << endl; return 0;
		}
		
		
		
		// rotation
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mapc[i][j] = mapa[n - j + 1][i];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mapa[i][j] = mapc[i][j];
	}	
	puts("No");
	return 0;
}
```


---

