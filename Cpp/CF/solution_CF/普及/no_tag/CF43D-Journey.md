# Journey

## 题目描述

你现在处于 $n\times m$ 的矩阵中 $(1,1)$ 这个点上。你现在的目标是走完全部点且不能走重复的点。你每一次只能移动 $1$ 格。

但是，你可以在迷宫中的任意一点放置一个传送门，这个传送门可以将你单向传送到一个传送门标记的点。现在求放置传送门次数最少的移动方案。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\le n,m\le100$，$n\times m>1$。
## 提醒
$(1,1)$ 会在起始与末尾各出现一次！

---
Translated by [残阳如血](/user/726139)。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
0
1 1
1 2
2 2
2 1
1 1
```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
1
3 3 1 1
1 1
1 2
1 3
2 3
2 2
2 1
3 1
3 2
3 3
1 1
```

# 题解

## 作者：_int123_ (赞：3)

题目：

# Journey

## 题面翻译

## 题目描述
你现在处于 $n\times m$ 的矩阵中 $(1,1)$ 这个点上。你现在的目标是走完全部点且不能走重复的点。你每一次只能移动 $1$ 格。

但是，你可以在迷宫中的任意一点放置一个传送门，这个传送门可以将你单向传送到一个传送门标记的点。现在求放置传送门次数最少的移动方案。
## 输入格式
输入共 $1$ 行，输入 $n$ 和 $m$。
## 输出格式
第一行输出传送门的最少放置个数 $k$。

接下来 $k$ 行，每行输出一组 $x_0,y_0,x_2,y_1$，表示有一个 $(x_0,y_0)\to(x_1,y_1)$ 的传送门。

接下来 $n\times m$ 行，每行输出此时所在的点的坐标。
## 数据范围
对于 $100\%$ 的数据，保证 $1\le n,m\le100$，$n\times m>1$。
## 提醒
$(1,1)$ 会在起始与末尾各出现一次！

---
Translated by [残阳如血](/user/726139)。

## 题目描述

The territory of Berland is represented by a rectangular field $ n×m $ in size. The king of Berland lives in the capital, located on the upper left square $ (1,1) $ . The lower right square has coordinates $ (n,m) $ . One day the king decided to travel through the whole country and return back to the capital, having visited every square (except the capital) exactly one time. The king must visit the capital exactly two times, at the very beginning and at the very end of his journey. The king can only move to the side-neighboring squares. However, the royal advise said that the King possibly will not be able to do it. But there is a way out — one can build the system of one way teleporters between some squares so that the king could fulfill his plan. No more than one teleporter can be installed on one square, every teleporter can be used any number of times, however every time it is used, it transports to the same given for any single teleporter square. When the king reaches a square with an installed teleporter he chooses himself whether he is or is not going to use the teleport. What minimum number of teleporters should be installed for the king to complete the journey? You should also compose the journey path route for the king.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=100,2<= $ $ n $ $ · $ $ m $ ) — the field size. The upper left square has coordinates $ (1,1) $ , and the lower right square has coordinates of $ (n,m) $ .

## 输出格式

On the first line output integer $ k $ — the minimum number of teleporters. Then output $ k $ lines each containing 4 integers $ x_{1} $ $ y_{1} $ $ x_{2} $ $ y_{2} $ ( $ 1<=x_{1},x_{2}<=n,1<=y_{1},y_{2}<=m $ ) — the coordinates of the square where the teleporter is installed ( $ x_{1},y_{1} $ ), and the coordinates of the square where the teleporter leads ( $ x_{2},y_{2} $ ).

Then print $ nm+1 $ lines containing 2 numbers each — the coordinates of the squares in the order in which they are visited by the king. The travel path must start and end at $ (1,1) $ . The king can move to side-neighboring squares and to the squares where a teleporter leads. Besides, he also should visit the capital exactly two times and he should visit other squares exactly one time.

## 样例 #1

### 样例输入 #1

```
2 2
```

### 样例输出 #1

```
0
1 1
1 2
2 2
2 1
1 1
```

## 样例 #2

### 样例输入 #2

```
3 3
```

### 样例输出 #2

```
1
3 3 1 1
1 1
1 2
1 3
2 3
2 2
2 1
3 1
3 2
3 3
1 1
```


------------
###### ~~juruo 的第一篇题解，不喜勿喷~~

此题非常**坑**，请做好准备。

我试了 20+ 次试出了答案，这么辛苦能不能点个赞呢？

## 题前说明：

1. 不难观察出传送门数量最多为 1，且只可能为 0 或 1。

2. 接着对 $m$，$n$ 分类讨论（下面说）。

**3. 输出时必须按下面说的输出，负责后果自负。**

4. 本题虽然有多种输出方法，但只有一种是对的。（题目没说那种对）

------------
### 解题过程：

#### 1. 输入（不用说了）。

```cpp
scanf("%d%d",&n,&m);
```

#### 2. 对特殊情况 $n=m=1$ 或 $n=1,m=2$ 或 $n=2,m=1$ 特判。

这些显然是不需要传送门的。

```cpp
	if(n==1&&m==1)
	{
		cout<<0<<endl<<"1 1"<<endl;
		return 0;
	}
	if(n==1&&m==2)
	{
    	cout<<0<<endl<<"1 1"<<endl<<"1 2"<<endl<<"1 1"<<endl;
    	return 0;
    }
	if(m==1&&n==2)
	{
    	cout<<0<<endl<<"1 1"<<endl<<"2 1"<<endl<<"1 1"<<endl;
    	return 0;
    }
```

#### 3. 除了特殊情况，当 $n=1$ 或 $m=1$ 时，要传送门。

以 $n=1$ 为例，从 $(1,1)$ 到 $(1,m)$ 顺序输出即可。

```cpp
	if(n==1)
	{
    	cout<<1<<endl<<1<<" "<<m<<" 1 1"<<endl;
    	for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    }
```

同理，$m=1$ 的情况类似。

```cpp
 	if(m==1)
	{
    	cout<<1<<endl<<n<<" 1 1 1"<<endl;
    	for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    }
```
#### 4. $m$ 为偶数或 $n$ 为偶数（ $m$，$n$ 均为偶数的情况也算）。

注意，此时要先写 $m$ 的，别问我为什么，问就是试出来的，不然当 $m$ 与 $n$ 都为偶数时就会 **wa** 了。

当 $m$ 为偶数时举例，经过我多次试验，发现，正解为：

1. 先一条横着的直线到底。

2. 再蛇形绕回来。

上代码：

```cpp
	if(m%2==0)
	{
    	cout<<0<<endl;
    	for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
    	for(int i=m;i>=1;i--)
		{
    		if(i%2==0)
    		{
    			for(int j=2;j<=n;j++) cout<<j<<" "<<i<<endl;
			}	
    		else
			{
				for(int j=n;j>=2;j--) cout<<j<<" "<<i<<endl;
			}
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```

同理，$n$ 为偶数时一样，

1. 先一条竖着的直线到底。

2. 再蛇形绕回来。

代码：

```cpp
	if(n%2==0)
	{
    	cout<<0<<endl;
    	for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
    	for(int i=n;i>=1;i--)
		{
    		if(i%2==0)
    		{
    			for(int j=2;j<=m;j++) cout<<i<<" "<<j<<endl;
			}	
    		else
			{
				for(int j=m;j>=2;j--) cout<<i<<" "<<j<<endl;
			}
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```

#### 5. $m$，$n$ 都为奇数。

此时，不难发现，需要一个传送门从 $(m ,n)$ 到 $( 1, 1 )$ ，走法为：从 $( 1,1 )$ 横着蛇形走到 $(m,n)$（**只能这么走**）再从传送门回到 $( 1,1 )$。

代码：

```cpp
	if(n%2==1&&m%2==1)
	{
    	cout<<1<<endl<<n<<" "<<m<<" 1 1"<<endl;
    	for(int i=1;i<=n;i++)
		{
    		if(i%2==1)
    		{
    			for(int j=1;j<=m;j++) cout<<i<<" "<<j<<endl;
			}
    		else
    		{
    			for(int j=m;j>=1;j--) cout<<i<<" "<<j<<endl;
			}	
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```



------------
最后，将这些整合一下，就有了 AC 代码。

AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	if(n==1&&m==1)//特例
	{
		cout<<0<<endl<<"1 1"<<endl;
		return 0;
	}
	if(n==1&&m==2)//特例
	{
    	cout<<0<<endl<<"1 1"<<endl<<"1 2"<<endl<<"1 1"<<endl;
    	return 0;
    }
	if(m==1&&n==2)//特例
	{
    	cout<<0<<endl<<"1 1"<<endl<<"2 1"<<endl<<"1 1"<<endl;
    	return 0;
    }
	if(n==1)//一行的情况
	{
    	cout<<1<<endl<<1<<" "<<m<<" 1 1"<<endl;
    	for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    }
    if(m==1)//一列的情况
	{
    	cout<<1<<endl<<n<<" 1 1 1"<<endl;
    	for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    }
    if(m%2==0)//m,n中有一个为偶数
	{
    	cout<<0<<endl;
    	for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
    	for(int i=m;i>=1;i--)
		{
    		if(i%2==0)
    		{
    			for(int j=2;j<=n;j++) cout<<j<<" "<<i<<endl;
			}	
    		else
			{
				for(int j=n;j>=2;j--) cout<<j<<" "<<i<<endl;
			}
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
    if(n%2==0)//m,n中有一个为偶数
	{
    	cout<<0<<endl;
    	for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
    	for(int i=n;i>=1;i--)
		{
    		if(i%2==0)
    		{
    			for(int j=2;j<=m;j++) cout<<i<<" "<<j<<endl;
			}	
    		else
			{
				for(int j=m;j>=2;j--) cout<<i<<" "<<j<<endl;
			}
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
    if(n%2==1&&m%2==1)//m,n都为奇数
	{
    	cout<<1<<endl<<n<<" "<<m<<" 1 1"<<endl;
    	for(int i=1;i<=n;i++)
		{
    		if(i%2==1)
    		{
    			for(int j=1;j<=m;j++) cout<<i<<" "<<j<<endl;
			}
    		else
    		{
    			for(int j=m;j>=1;j--) cout<<i<<" "<<j<<endl;
			}	
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
	return 0;
}
```

完结，撒花！！！

望管理员通过。

---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF43D)

这个题其实是一个很水的模拟啦~~只不过细节很多。

 PS：这题其实不用考虑 $n=1$，$m=1$ 的情况，因为题目说了 $m \times n > 1$。

* $n=1$
  
  我们需分情况讨论：
  
   * $m=2$
  
     这是 $n=1$ 中的特殊情况，他是唯一一种不需传送门的情况
    
     只需输出：
    
     ```
     0
     1 1
     1 2
     1 1
     ```
     自证不难。
   * $m \ne 2$
     
     这时需要一个传送门，从（$1$，$m$）至（$1$，$1$）。
     
     这时只需从（$1$，$1$）到（$1$，$m$）皆走一遍，在回到（$1$，$1$）就行了。
* $m=1$
  
  我们需分情况讨论：
  
  * $n=2$
  
     这是 $m=1$ 中的特殊情况，他是唯一一种不需传送门的情况
    
     只需输出：
    
     ```
     0
     1 1
     2 1
     1 1
     ```
     自证不难。
   * $n \ne 2$
     
     这时需要一个传送门，从（$n$，$1$）至（$1$，$1$）。
     
     这时只需从（$1$，$1$）到（$n$，$1$）皆走一遍，在回到（$1$，$1$）就行了。
     
* $m \bmod 2 = 1$ 且 $n \bmod 2 = 1 $

  我们可以用“蛇形环绕法”：
  
  对于每个 $i$（$1 \le i \le n$）
  
  若 $i \bmod 2 = 1$ 则从（$i$，$1$）到（$i$，$m$）走一遍。
  
  若 $i \bmod 2 = 0$ 则从（$i$，$m$）到（$i$，$1$）走一遍。
  
  这样你就可以发现他走的路是蛇形的。
  
  唉，先别急，他最后是落在了（$n$，$m$）的格子上，所以需一个传送门从（$n$，$m$）到（$1$，$1$）。
  
* $m \bmod 2 = 0$
  
  我们还是采用“蛇形环绕法”，但不一样的是：
  
  对于每个 $i$（$1 \le i \le m$）
  
  若 $i \bmod 2 = 1$ 则从（$2$，$i$）到（$n$，$i$）走一遍。
  
  若 $i \bmod 2 = 0$ 则从（$n$，$i$）到（$2$，$i$）走一遍。
  
  最后到达的点是（$1$，$m$），所以还要从（$1$，$m$）到（$1$，$1$）走回来。
  
* 剩余的情况

  换句话说就是 $n \bmod 2=0$ 且 $m \bmod 2=1$ 的情况。
  
  还是“蛇形环绕法”，跟上一种情况唯一的差别就是 $i$ 的表示不同。
  
  对于每个 $i$（$1 \le i \le n$）
  
  若 $i \bmod 2 = 1$ 则从（$i$，$2$）到（$i$，$m$）走一遍。
  
  若 $i \bmod 2 = 0$ 则从（$i$，$m$）到（$i$，$2$）走一遍。
  
  最后到达的点是（$n$，$1$），所以还要从（$n$，$1$）到（$1$，$1$）走回来。
  
总代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;

int main()
{
    cin>>n>>m;
    if(n==1 && m==2) return cout<<"0\n1 1\n1 2\n1 1\n",0;
    if(n==2 && m==1) return cout<<"0\n1 1\n2 1\n1 1\n",0;
    if(n==1) 
    {
        cout<<"1\n1 "<<m<<" 1 1\n";
        for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
        cout<<"1 1\n";
        return 0;
    }
    if(m==1)
    {
        cout<<"1\n"<<n<<" 1 1 1\n";
        for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
        cout<<"1 1\n";
        return 0;
    }
    if(n%2==1 && m%2==1)
    {
        cout<<"1\n"<<n<<" "<<m<<" 1 1\n";
        for(int i=1;i<=n;i++)
        {
            if(i%2==1)
            {
                for(int j=1;j<=m;j++)
                {
                    cout<<i<<" "<<j<<endl;
                }
            }
            else
            {
                for(int j=m;j>=1;j--)
                {
                    cout<<i<<" "<<j<<endl;
                }   
            }
        }
        cout<<"1 1\n";
        return 0;
    }
    if(m%2==0)
    {    
        cout<<"0\n1 1\n";
        for(int i=1;i<=m;i++)
        {
            if(i%2==1)
            {
                for(int j=2;j<=n;j++)
                {
                    cout<<j<<" "<<i<<endl;
                }
            }
            else
            {
                for(int j=n;j>=2;j--)
                {
                    cout<<j<<" "<<i<<endl;
                } 
            }
        }
        for(int i=m;i>=1;i--) cout<<"1 "<<i<<endl;
        return 0;
    }
    cout<<"0\n"<<"1 1\n";
    for(int i=1;i<=n;i++)
    {
        if(i%2==1)
        {
            for(int j=2;j<=m;j++)
            {
                cout<<i<<" "<<j<<endl;
            }
        }
        else
        {
            for(int j=m;j>=2;j--)
            {
                cout<<i<<" "<<j<<endl;
            }
        }
    }
    for(int i=n;i>=1;i--) cout<<i<<" 1\n";
    return 0;
}
```

---

## 作者：David_yang (赞：2)

[传](https://www.luogu.com.cn/problem/CF43D)送[门](https://codeforces.com/problemset/problem/43/D)

第八篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

你现在在一个 $n\times m$ 矩阵中的 $(1,1)$ 上，问你如何走能不重不漏的走一圈并回到 $(1,1)$，可以用传送门。

## 算法：

搜索。

## 解析：

拿到题先想一下，是不是传送门的数量要么为 $0$，要么为 $1$？当数量为 $0$ 时，$m$ 和 $n$ 至少其中一个是偶数；当数量为 $1$ 是，$m$ 和 $n$ 都为奇数。根据这两个大方向，分别写就行了，绕出来像一个蛇形（注意不同情况绕出来的蛇形方法不一样）。

最重要的是，**这里面有好几个特判！**（把我坑惨了……）这些可能不说就不知道，一说出来就会觉得我怎么这也想不到。我把几个特判列出来，解决方法你肯定想得出来。

1. $n=1$ 且 $m=1$
2. $n=1$ 且 $m=2$
3. $n=2$ 且 $m=1$
4. 单独的 $n=1$
5. 单独的 $m=1$

好了，这些注意到这道题也就能做出来了，下面我把代码摆出来。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,flag;
int main()
{
	scanf("%d%d",&n,&m);
	if(n==1 && m==1)			//五个特判
	{
		printf("0\n1 1");
		return 0;
	}
	if(n==1 && m==2)
	{
		printf("0\n1 1\n1 2\n1 1");
		return 0;
	}
	if(n==2 && m==1)
	{
		printf("0\n1 1\n2 1\n1 1");
		return 0;
	}
	if(n==1)
	{
		printf("1\n%d %d 1 1\n",n,m);
		for(int i=1;i<=m;i++)
		{
			printf("1 %d\n",i);
		}
		printf("1 1");
		return 0;
	}
	if(m==1)
	{
		printf("1\n%d %d 1 1\n",n,m);
		for(int i=1;i<=n;i++)
		{
			printf("%d 1\n",i);
		}
		printf("1 1");
		return 0;
	}
	if(n&1 && m&1)				//分两种情况输出
	{
		printf("1\n%d %d 1 1\n",n,m);
		for(int i=1;i<=n;i++)	//绕蛇形
		{
			if(!flag)			//flag代表该往哪个方向绕
			{
				for(int j=1;j<=m;j++)
				{
					printf("%d %d\n",i,j);
				}
				flag=1;
			}
			else
			{
				for(int j=m;j;j--)
				{
					printf("%d %d\n",i,j);
				}
				flag=0;
			}
		}
		printf("1 1");
	}
	else
	{
		printf("0\n");
		for(int i=1;i<=m;i++)
		{
			printf("1 %d\n",i);
		}
		if(!(m&1))				//注意这里也有两种情况绕蛇形（当时我也在这被坑了一下）
		{
			for(int i=m;i;i--)
			{
				if(!flag)
				{
					for(int j=2;j<=n;j++)
					{
						printf("%d %d\n",j,i);
					}
					flag=1;
				}
				else
				{
					for(int j=n;j>1;j--)
					{
						printf("%d %d\n",j,i);
					}
					flag=0;
				}
			}
		}
		else
		{
			for(int i=2;i<=n;i++)
			{
				if(!flag)
				{
					for(int j=m;j>1;j--)
					{
						printf("%d %d\n",i,j);
					}
					flag=1;
				}
				else
				{
					for(int j=2;j<=m;j++)
					{
						printf("%d %d\n",i,j);
					}
					flag=0;
				}
			}
			for(int i=n;i>1;i--)
			{
				printf("%d 1\n",i);
			}
		}
		printf("1 1");
	}
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：syf159 (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF43D)  
[codeforces](https://codeforces.com/problemset/problem/43/D)

## Analysis

现在有 $n × m$ 的一个矩阵，要求不重复的走完所有点，并回到原点。

并且，你可以建**单向的**传送门，求传送门放置最少的方案。

**注意：** $ (1,1) $ 会在起始与末尾各出现一次！

首先，我们可以轻易地得到：$k$ 只有可能是 $1$ 或 $0$（具体的请看后面的图）。

### 分类

**1.** $ n = 1 $，$ m = 1 $。

对于上面这种情况，我们直接走 $ (1 , 1) $ 就可以啦！

``` cpp
	if(n==1&&m==1)
	{
		cout<<"0\n1 1\n";
		return 0;
	}
```

**2.** $ n = 1 $，$ m = 2 $。

![CF43D-syf159-solution-1.png](https://s2.loli.net/2024/12/23/GLVkEyj3KlAfJpz.png)

如图，我们按照图示步骤走就可以啦（依次输出）！

``` cpp
	if(n==1&&m==2)
	{
		cout<<"0\n1 1\n1 2\n1 1\n";
		return 0;
	}
```

**3.** $ n = 2 $，$ m = 1 $。

同上。

![CF43D-syf159-solution-2.png](https://s2.loli.net/2024/12/23/DvBQChfGlyMHxtY.png)

``` cpp
	if(n==2&&m==1)
	{
		cout<<"0\n1 1\n2 1\n1 1\n";
		return 0;
	}
```

**4.** $ n = 1 $ 或 $ m = 1 $。

1. $ n = 1 $。
![CF43D-syf159-solution-3.png](https://s2.loli.net/2024/12/23/3txoz8uwIXmW6qE.png)

此时，我们需要一个传送门，因为我们从 $ ( 1 , 1) $ 一步一步走到 $ ( 1 , n ) $ 后，根据题意，我们需要一个传送门以从 $ ( 1 , n) $ 回到 $ (1,1) $。

```cpp
	if(n==1)
	{
		cout<<"1\n1 "<<m<<" 1 1\n";
		for(int i=1; i<=m; i++)
		{
			cout<<"1 "<<i<<"\n";
		}
		cout<<"1 1\n";
		return 0;
	}
```

2. $ m = 1 $。

![CF43D-syf159-solution-4.png](https://s2.loli.net/2024/12/23/1RjTov5aVtGQ6PK.png)

同上。

``` cpp
	if(m==1)
	{
		cout<<"1\n"<<n<<" 1 1 1\n";
		for(int i=1; i<=n; i++)
		{
			cout<<i<<" 1"<<"\n";
		}
		cout<<"1 1\n";
		return 0;
	}
```

**5.** $ n $ 是偶数或 $ m $ 是偶数。

1. $ n $ 是偶数。

![CF43D-syf159-solution-5.png](https://s2.loli.net/2024/12/23/bfmUVeFS76yirET.png)

``` cpp
	if(n%2==0)
	{
		cout<<"0\n";
		for(int i=1; i<=n; i++)
		{
			cout<<i<<" 1"<<"\n";
		}
		for(int i=n; i>=1; i--)
		{
			if(i%2==0)
			{
				for(int j=2; j<=m; j++)
				{
					cout<<i<<" "<<j<<"\n";
				}
			}
			else
			{
				for(int j=m; j>=2; j--)
				{
					cout<<i<<" "<<j<<"\n";
				}
			}
		}
		cout<<"1 1";
		return 0;
	}
```

2. $ m $ 是偶数。

~~至于图片嘛，把上面那张转过来看就好了（逃）~~。 

对于这一种情况，和 $ n $ 是偶数的情况同理。

```cpp
	if(m%2==0)
	{
		cout<<"0\n";
		for(int i=1; i<=m; i++)
		{
			cout<<"1 "<<i<<"\n";
		}
		for(int i=m; i>=1; i--)
		{
			if(i%2==0)
			{
				for(int j=2; j<=n; j++)
				{
					cout<<j<<" "<<i<<"\n";
				}
			}
			else
			{
				for(int j=n; j>=2; j--)
				{
					cout<<j<<" "<<i<<"\n";
				}
			}
		}
		cout<<"1 1";
		return 0;
	}
```

**6.** $ n $ 是奇数，并且 $ m $ 也是奇数（既上面几种情况都不是)。

![CF43D-syf159-solution-6.png](https://s2.loli.net/2024/12/24/Hr2QmGADJcMI7xS.png)

如图所示，对于这种情况，我们无论怎么走都需要一个传送门，我的做法就是“之”字型走到 $ ( n , m ) $，建一个传送门跑回 $ ( 1 , 1 ) $。

``` cpp
	cout<<"1\n"<<n<<" "<<m<<" 1 1\n";
	for(int i=1; i<=n; i++)
	{
		if(i%2==1)
		{
			for(int j=1; j<=m; j++)
			{
				cout<<i<<" "<<j<<"\n";
			}
		}
		else
		{
			for(int j=m; j>=1; j--)
			{
				cout<<i<<" "<<j<<"\n";
			}
		}
	}
	cout<<"1 1";
```
## [AC code](https://www.luogu.com.cn/paste/updcxmcf)

---

## 作者：Light_az (赞：1)

# 文字题解

只要我们仔细观察题目就会发现，当 $n$ 和 $m$ 都是奇数时，需要一个传送门，否则不需要，结论可以如下图证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/xu22diqi.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/dpjslayp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这之后我们只需要进行特判：

- 当 $n$ 是偶数，$m$ 是偶数时：

像图 $1$ 一样给上面留一行最后通过，之后下面蛇形遍历，因为 $m$ 是偶数，所以不需要担心没解。

- 当 $n$ 是奇数，$m$ 是偶数时：

像图 $1$ 一样直接遍历，肯定有解。

- 当 $n$ 是偶数，$m$ 是奇数时：

其实就是上面那种情况向右翻转 $90°$，也肯定有解。

- 当 $n$ 是奇数，$m$ 是奇数时：

像图 $2$ 一样肯定需要 $1$ 个传送门，坐标是 $(n,m)$ 到 $(1,1)$。

大致思路就是这样，可以根据样例再理解一下，之后循环输出答案就可以了。

### Hack

谢谢 $yszkddzyh$ 指出，题解没有考虑 $n,m==1$ 的情况，当 $n,m==1$ 时，答案为 `1,1`，不需要传送门。

---

## 作者：YangXiaopei (赞：0)

## 	Solution

~~简单~~但是细节贼多的~~小~~模拟。

大致可以分为几种情况。

* $n = 1, m = 2$

	这是 $n = 1$ 时最特殊的情况，唯一的一种不需要传送门的。

	当走到 $(1, m)$ 也就是 $(1, 2)$ 时，不需要传送门就可回到 $(1, 1)$。

* $m = 1, n = 2$

	同上。

* $n \bmod 2 = 0$

	举个例子。
    
  	![](https://ice.frostsky.com/2024/04/27/4a464489e144e75394b2f2cd5cfe4523.jpeg)
    
    有也就是说，一直在第 $2$ 列到第 $m$ 列绕蛇形，最后在第一列上去。

* $m \bmod 2 = 0$

	同上。
    
   ![](https://ice.frostsky.com/2024/04/27/e156fa2148df58f8ac85f11e8a12a213.jpeg)
   
   一直在第 $2$ 行到第 $n$ 行饶绕形最后从第一行回去。

* $n \bmod 2 = 1, m \bmod 2 = 1$

	只能直接到 $(n, m)$，再从传送门回去。
    
## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int main() {
	cin >> n >> m;
	if(n == 1 && m == 2){
		cout << 0 << "\n";
		for(int i = 1; i <= m; i++){
			cout << 1 << " " << i << "\n";
		}
		cout << 1 << " " << 1;
		return 0;
	}
	if(m == 1){
		cout << 0 << "\n";
		for(int i = 1; i <= n; i++){
			cout << i << " " << 1 << "\n";
		}
		cout << 1 << " " << 1;
		return 0;
	}
	if(!(n % 2)){
		cout << 0 << "\n" << 1 << " " << 1 << "\n";
		for(int i = 1; i <= n; i++){
			if(i % 2){
				for(int j = 2; j <= m; j++){
					cout << i << " " << j << "\n";
				}
			}
			else{
				for(int j = m; j >= 2; j--){
					cout << i << " " << j << "\n";
				}
			}
		}
		for(int i = n; i >= 1; i--){
			cout << i << " " << 1 << "\n";
		}
		return 0;
	}
	if(!(m % 2)){
		cout << 0 << "\n" << 1 << " " << 1 << "\n";
		for(int i = 1; i <= m; i++){
			if(i % 2){
				for(int j = 2; j <= n; j++){
					cout << j << " " << i << "\n";
				}
			}
			else{
				for(int j = n; j >= 2; j--){
					cout << j << " " << i << "\n";
				}
			}
		}
		for(int i = m; i >= 1; i--){
			cout << 1 << " " << i << "\n";
		}
		return 0;
	}
	cout << 1 << "\n" << n << " " << m << " " << 1 << " " << 1 << "\n";
	for(int i = 1; i <= n; i++){
		if(i % 2){
			for(int j = 1; j <= m; j++){
				cout << i << " " << j << "\n";
			}
		}
		else{
			for(int j = m; j >= 1; j--){
				cout << i << " " << j << "\n";
			}
		}
	}
	cout << 1 << " " << 1 << "\n";
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 题意
本题说有个人在矩阵上走，可以传送，也可以走挨着的格子，最后回到出发点 $(1,1)$。你可以在某处放置传送门，在后来可以传送回来，求放置传送门次数最少。

# 思路
分类讨论。

首先，传送门放置在起点即可，因为你放其他地方，那岂不是绕回去了，浪费次数。

因为我们要让放置传送的次数最小，所以尽量要绕回去。

两个都是奇数时，我们从最简单的角度思考，也就是蛇形，依次走到底，再回头。不管我们是先右还是先下，肯定是右左右或者下上下，最后一次一定回不到起点。这种情况一定是绕不回起点，也就是说要放一个。

![up](https://cdn.luogu.com.cn/upload/image_hosting/80l409kv.png)

下图是其他情况，不需要传送。

![down](https://cdn.luogu.com.cn/upload/image_hosting/5n26ser9.png)

我们分类讨论：

- 有一个偶数，即可以不用传送门
	
   - 在两边有一个为偶数的时候，可以采用留出空间，回形移动，等到了最下面再返回。

   - $n$ 为偶数，$m$ 为偶数时，像下图第一种情况走。

   - $n$ 为奇数，$m$ 为偶数时，像下图第二种情况走。

   - $n$ 为偶数，$m$ 为奇数时，像下图第三种情况走。
   
   - 这三种都需要在绕的时候留出最上面或最左面的一条边，这样才能回到起点。
   
- 没有偶数，即要用一个传送门

   - 竖着蛇形走到底，再用一次传送回去。
   
- 当然，当 $n,m \le 2$ 时，不需要传送门，这时特判输出即可。


## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
#define fa(i,j,n) for(int i=j;i>=n;i--)
#define cij cout<<i<<" "<<j<<endl;
#define cji cout<<j<<" "<<i<<endl;
using namespace std;
signed main(){
	int n,m;
	cin>>n>>m;
	if(n==1&&m==1){//特判 
		cout<<"0\n1 1";
		return 0;
	}
	if(n==1&&m!=2){
		cout<<"1\n1 "<<m<<" 1 1\n";
		f(i,1,m){
			cout<<"1 "<<i<<endl;
		}
    	cout<<"1 1\n";
    	return 0;
	}
	if(n!=2&&m==1){
		cout<<"1\n"<<n<<" 1 1 1\n";
		f(i,1,n){
			cout<<i<<" 1\n";
		}
    	cout<<"1 1\n";
    	return 0;
	}
	if(n&1&&m&1){
		cout<<"1\n"<<n<<" "<<m<<" 1 1\n";
		f(i,1,n){
			if(i&1){
				f(j,1,m){
					cij
				}
			}else{
				fa(j,m,1){
					cij
				}
			}
		}
		cout<<"1 1\n";
	}else if(m%2==0){
   		cout<<0<<endl;
    	f(i,1,m){
    		cout<<"1 "<<i<<endl;
		}
    	fa(i,m,1){
    		if(i%2!=m%2){
    			fa(j,n,2){
    				cji
				}
			}else{
    			f(j,2,n){
    				cji
    			}
			}
		}
    	cout<<"1 1\n";
	}else{
   		cout<<0<<endl;
    	f(i,1,n){
    		cout<<i<<" 1\n";
		}
    	fa(i,n,1){
    		if(i%2!=n%2){
    			fa(j,m,2){
    				cij
				}
			}else{
    			f(j,2,m){
    				cij
    			}
			}
		}
    	cout<<"1 1\n";
    }
	return 0;
}
```

---

## 作者：ys_kylin__ (赞：0)

注意：本题没有 SPJ，因此对方案的要求十分严格。

本题其实就是矩阵一笔画问题。不难发现，传送门只可能放一个或不放，具体情况为：（以下操作必须按顺序做）

1. $m$ 为偶数：从左上角走到右上角，走到右下角，开始蛇形绕（左，上到底，左，下到底等等）。
2. $n$ 为偶数：从左上走到左下，走到右下，开始蛇形绕（上，左到底，上，右到底等等）。
3. 两个都是奇数：从左上横着蛇形到右下，传送门回来。（右到底，下，左到底，下等等）。

然后还有以下需要特判的特殊情况：
1. 对 $n=m=1$，$n=1,m=2$，$n=2,m=1$ 特判，这些情况显然可以通过
2. 对 $n=1,m>2$ 和 $n>2,m=1$ 特判，这些情况显然无法通过，走到底放一个传送门即可。

代码部分比较简单，按照描述的方法操作即可。

---

## 作者：AirQwQ (赞：0)

## 思路

- 首先，传送门要么 $ 1 $ 个，要么 $ 0 $ 个。

- 有多种情况分类讨论即可。

## 实现&坑点

#### 前置提醒：
1. **必须按照图示输出，尽管有多组解但其他都会WA**。

2. **必须先 ```m``` 再 ```n``` 不然它俩都是偶数会WA掉**。

#### 分类讨论

1. $n=1\text{ 并且 }m=2$ 特判直接输出，不需要传送门。

```cpp
if(n==1&&m==2){
    	cout<<"0\n1 1\n1 2\n1 1"<<endl;
    	return 0;
    }

```

2. $n=2\text{ 并且 }m=1$ 特判直接输出，不需要传送门。


```cpp
if(m==1&&n==2){
    	cout<<"0\n1 1\n2 1\n1 1"<<endl;
    	return 0;
    }

```

3. $ n = 1 \text{ 并且 }m \ne 2$ 无论如何回不去，要一个传送门。


```cpp

if(n==1){
    	cout<<"1"<<endl;
    	printf("1 %d 1 1\n",m);
    	for(int i=1;i<=m;i++)
    		cout<<"1 "<<i<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    } 
```

4. $ m = 1 \text{ 并且 }n \ne 2$ 无论如何回不去，要一个传送门。

```cpp
if(m==1){
    	cout<<"1"<<endl;
    	printf("%d 1 1 1\n",n);
    	for(int i=1;i<=n;i++)
    		cout<<i<<" 1"<<endl;
    	cout<<"1 1"<<endl;
    	return 0;
    }

```

5. $ n \equiv 1 \pmod 2 \text{ 并且 }m \equiv 1 \pmod 2 $ 两个均为奇数，需要一个传送门，先走到终点，然后飞回 $ (1,1) $。

[link](https://www.luogu.com.cn/paste/m2wmi4iv)

```cpp
if(n%2&&m%2){
    	cout<<"1"<<endl;
    	printf("%d %d 1 1\n",n,m);
    	for(int i=1;i<=n;i++){
    		if(i%2)
    			for(int j=1;j<=m;j++)
    				cout<<i<<' '<<j<<endl;
    		else 
    			for(int j=m;j>=1;j--)
    				cout<<i<<' '<<j<<endl;
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```

6. $ m \equiv 0 \pmod 2 $ 有至少一个为偶数，先一条直线到底再绕回来。

[link](https://www.luogu.com.cn/paste/4zke95ki)

```cpp
if(m%2==0){
    	cout<<0<<endl;
    	for(int i=1;i<=m;i++)
    		cout<<"1 "<<i<<endl;
    	for(int i=m;i>=1;i--){
    		if(i%2==m%2)
    			for(int j=2;j<=n;j++)
    				cout<<j<<' '<<i<<endl;
    		else 
    			for(int j=n;j>=2;j--)
    				cout<<j<<' '<<i<<endl;
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```

7. $ n \equiv 0 \pmod 2 $ 有至少一个为偶数，先一条直线到底再绕回来。

[link](https://www.luogu.com.cn/paste/xojkyeeu)
```cpp
if(n%2==0){
      cout<<0<<endl;
    	for(int i=1;i<=n;i++)
    		cout<<i<<" 1"<<endl;
    	for(int i=n;i>=1;i--){
    		if(i%2==n%2)
    			for(int j=2;j<=m;j++)
    				cout<<i<<' '<<j<<endl;
    		else 
    			for(int j=m;j>=2;j--)
    				cout<<i<<' '<<j<<endl;
    	}
    	cout<<"1 1"<<endl;
    	return 0;
    }
```
~~每一部分都有了，只剩框架和输入，所以完整代码就不放了~~

---

## 作者：Wsy_flying_forever (赞：0)

这题几乎没人写题解，我就来补一发！（QAQ）
### 题意  
给定 $n*m$ 的矩阵，求不重复的遍历所有的点,从起始点 $a_{1,1}$ 再到 $a_{1,1}$ ，使所用传送门的数目最少的路径。  
### 思路  
乍看题目，这并不像一道橙题，但稍加思索，我们发现：传送门的数目只有可能是0或1。   
1. 当 $n$,$m$ 小于等于 $2$ 时，显然传送门的数目为 $0$ 。   
2. 当 $n\neq1$ 且 $m\neq1$ 且 $n,m$ 中至少有一个不是奇数时，先一口气走到底，再绕回去，显然传送门的数目也为 $0$     
3. 其余情况跑到终点再用一个传送门送回去即可。   
### 实现
实现就是 dfs 并记录路径，这里不再赘述。  
  
    
    完结撒花！

---

