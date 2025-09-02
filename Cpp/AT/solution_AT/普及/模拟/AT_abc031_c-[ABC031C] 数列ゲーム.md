# [ABC031C] 数列ゲーム

## 题目描述

高桥和青木用长度为N的数列S玩游戏。

游戏中，高桥和青木各进行一回合。

游戏按照以下规则进行：

	首先，高桥在数列中圈一个数字。
	然后，青木在高桥没圈的数字中圈一个。
	接着，留下圈中的数字以及它们之间的数字，去掉其它数字。留下的数列叫T。
	最后，在数列T中，从左开始奇数个数字的和为高桥的得分，偶数个数字为青木的得分。

青木在能圈的数字中，圈出能使他得到最多分数的数字。如果这样的数有多个，圈出最左的数字。

高桥知道青木的圈数方法。请求出高桥能得到的最大得分。

## 样例 #1

### 输入

```
6
1 -3 3 9 1 6```

### 输出

```
6```

## 样例 #2

### 输入

```
3
5 5 5```

### 输出

```
10```

## 样例 #3

### 输入

```
8
-1 10 -1 2 -1 10 -1 0```

### 输出

```
-1```

# 题解

## 作者：xps0606 (赞：1)

对于青木君来说，他只会选择得分最多的局部最优解。

这时候高桥君循环判断最优解就好了。

先预处理单偶区间分数，再开两个单偶循环。

```
#include<bits/stdc++.h> 
#define ll long long
using namespace std;  
const int inf=1<<14;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}	
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-48);
		ch=getchar();
	}
	return x*f;
}
/*
Sample Explanation 1
高桥君最适合从左边选出第2个要素。
在这种情况下，青木君从左开始选择第5个要素，得到的数列T从左开始依次是-3,3,9,1。
高桥得6分，青木得4分。
//附赠说明 
Sample Explanation 2
对青木君来说，不管选择哪个要素都能得的得分是5这一点是不变的。
但是如果能得的分数最大的话，就要在其中选择最左的，所以高桥君的得分可能是10。
*/
int a[101],x[101],y[101];
int main()
{  
	int n=read();
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	for(int i=0;i<n;i++) a[i]=read();
	for(int i=0;i<n;i++)
	{
		if(!(1&i))//单偶数决定得分 
		{
			x[i+1]=a[i]+x[i];
			y[i+1]=y[i];
		}
		else
		{
			y[i+1]=a[i]+y[i];
			x[i+1]=x[i];
		}
	}
	int b=0,c=0,ans=-inf;
	for(int i=0;i<n;i++)//枚举 
	{
		int minn=-inf,w;
		for(int j=0;j<i;j++)
		{
			if(!(1&j))
			{
				b=x[i+1]-x[j];
				c=y[i+1]-y[j];
			}
			else
			{
				c=x[i+1]-x[j];
				b=y[i+1]-y[j];
			}
			if(minn<c)//是否是最高得分 
			{
				minn=c;
				w=b;
			}
		}
		for(int j=i+1;j<n;j++)
		{
			if(!(1&i))
			{
				b=x[j+1]-x[i];
				c=y[j+1]-y[i];
			}
			else
			{
				c=x[j+1]-x[i];
				b=y[j+1]-y[i];
			}
			if(minn<c)
			{
				minn=c;
				w=b;
			}
		}
		ans=max(ans,w);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

