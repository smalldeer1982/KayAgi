# Cardiogram

## 题目描述

In this problem, your task is to use ASCII graphics to paint a cardiogram.

A cardiogram is a polyline with the following corners:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435C/f0f02d0c7c83e26a44852403071814a1b9513d4c.png)That is, a cardiogram is fully defined by a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ .

Your task is to paint a cardiogram by given sequence $ a_{i} $ .

## 说明/提示

Due to the technical reasons the answers for the samples cannot be copied from the statement. We've attached two text documents with the answers below.

http://assets.codeforces.com/rounds/435/1.txt

http://assets.codeforces.com/rounds/435/2.txt

## 样例 #1

### 输入

```
5
3 1 2 5 1
```

### 输出

```
     <span class="tex-span"> / </span><span class="tex-span">\</span>     
  <span class="tex-span"> / </span><span class="tex-span">\</span><span class="tex-span"> / </span>  <span class="tex-span">\</span>    
 <span class="tex-span"> / </span>      <span class="tex-span">\</span>   
<span class="tex-span"> / </span>        <span class="tex-span">\</span>  
          <span class="tex-span">\</span><span class="tex-span"> / </span>
```

## 样例 #2

### 输入

```
3
1 5 1
```

### 输出

```
<span class="tex-span"> / </span><span class="tex-span">\</span>     
  <span class="tex-span">\</span>    
   <span class="tex-span">\</span>   
    <span class="tex-span">\</span>  
     <span class="tex-span">\</span><span class="tex-span"> / </span>
```

# 题解

## 作者：loser_seele (赞：0)

一个不难想但不好写的小模拟题。

观察到对于每次操作我们都可以维护一个当前坐标，然后对当前坐标直接修改数组即可，对于奇数下标暴力模拟上移，否则暴力模拟下移，问题转化为如何确定坐标的上下限。这个也并不难维护，更新坐标的时候直接将 $ x $ 坐标的上下限用当前坐标更新即可。具体实现见代码。注意可能出现负数下标，一个常见的套路是将下标集体平移 $ 1000 $ 即可避免问题。

修改数组的过程可以暴力，总时间复杂度 $ \mathcal{O}(\sum{a_i}) $，题目保证 $ \sum{a_i} \leq 1000 $，所以可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
char ans[2010][2000];
int n,x,y,mu,md,t;
void paint(int d,int u)
{
	ans[x][++y]=u>0?'/':'\\';
	mu=min(mu,x);
	md=max(md,x);
	for (int i=1;i<d;i++)
	{
		y++;
		x+=u;
		ans[x][y]=u>0?'/':'\\';
		mu=min(mu,x);
		md=max(md,x);
	}
}
int main()
{
	scanf("%d",&n);
	mu=0x7fffffff;
	md=-mu;
	x=1000,y=0;
	memset(ans, ' ', sizeof ans);
	for (int i=0;i<n;i++) 
	scanf("%d",&t), paint(t,(i&1)?-1:1);
	for (x=md;x>=mu;x--)
	{
		for (int j=1;j<=y;j++)
		printf("%c",ans[x][j]);
		puts("");
	}
}
```


---

