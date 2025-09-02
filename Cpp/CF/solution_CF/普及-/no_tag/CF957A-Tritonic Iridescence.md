# Tritonic Iridescence

## 题目描述

Overlooking the captivating blend of myriads of vernal hues, Arkady the painter lays out a long, long canvas.

Arkady has a sufficiently large amount of paint of three colours: cyan, magenta, and yellow. On the one-dimensional canvas split into $ n $ consecutive segments, each segment needs to be painted in one of the colours.

Arkady has already painted some (possibly none or all) segments and passes the paintbrush to you. You are to determine whether there are at least two ways of colouring all the unpainted segments so that no two adjacent segments are of the same colour. Two ways are considered different if and only if a segment is painted in different colours in them.

## 说明/提示

For the first example, there are exactly two different ways of colouring: CYCMY and CYMCY.

For the second example, there are also exactly two different ways of colouring: CMCMY and CYCMY.

For the third example, there are four ways of colouring: MCYCM, MCYCY, YCYCM, and YCYCY.

For the fourth example, no matter how the unpainted segments are coloured, the existing magenta segments will prevent the painting from satisfying the requirements. The similar is true for the fifth example.

## 样例 #1

### 输入

```
5
CY??Y
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
C?C?Y
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
5
?CYC?
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
5
C??MM
```

### 输出

```
No
```

## 样例 #5

### 输入

```
3
MMY
```

### 输出

```
No
```

# 题解

## 作者：幻影星坚强 (赞：2)

这题最好不要去考虑“？”所代表的颜色。

我们在这里直接根据已知颜色与未知颜色的关系去判断。
### 1.
如果已知颜色中有相邻两个颜色相同，那肯定不能完成。
### 2.
如果未知颜色只有单独一块，如：

`
M?M
`

`
?M
`

`
M?Y
`

#### ①
如果是第一、二种情况，那么这个问号一定有两种填法。（C,Y）
#### ②
如果是第三种情况，那么这个问号只有一种填法。（C）
### 3.
如果有相邻多个“？”相邻,如：

`
M??M
`

`
??C
`

`
M???????C
`

无论如何都能转化成2-①。
### 4.
如果满足1，则不能画成。

如果不满足1，且满足2-①或3，则一定能画成。

如都不满足，则不能画成。

代码如下：
```
#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool b=0;
char p[110];
int main()
{
	scanf("%d",&n);
	scanf("%s",p);
	for(int i=0;i<n;i++)
	{
		if(p[i]!='?')//如果这块有颜色
		{
			if(p[i+1]==p[i])//如果这块与相邻的已知颜色相同
			{
				printf("No");
				return 0;
			}
		}
		else
		if(i==0||i==n-1||p[i-1]=='?'||p[i+1]=='?'/*“？”是否连续*/||(p[i-1]!='?'&&p[i+1]!='?'&&p[i-1]==p[i+1])/*是否满足2-①*/)
		{
			b=1;
		}
	}
	if(b)
	printf("Yes");
	else
	printf("No");	
}
```

---

