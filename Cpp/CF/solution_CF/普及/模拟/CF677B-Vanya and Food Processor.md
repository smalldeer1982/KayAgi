# Vanya and Food Processor

## 题目描述

瓦尼亚在一个垂直的食品处理器中粉碎土豆。  
你可以把它想象成一个圆柱体，从上面塞入，从下面粉碎后吐出。    
每个土豆可以视为条状。

处理器中的土豆高度不超过$h$(否则会满出来)，处理器每秒粉碎$k$厘米的土豆。如果处理器里剩不到$k$厘米土豆，则粉碎所有剩余的土豆。



瓦尼亚有$n$条土豆，第$i$块的长度等于$a_i$。他把它们按顺序从$1$号到$n$号放进食品处理器，从$1$号开始，到$n$号结束。

每秒会发生如下事件：

1.如果还有至少一条土豆没放进去，瓦尼亚将它们逐一放入处理器，直到没有足够的空间放置下一片，即塞到塞不进为止。

2.处理器粉碎了$k$厘米或剩下全部的土豆。

## 样例 #1

### 输入

```
5 6 3
5 4 3 2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 6 3
5 5 5 5 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5 6 3
1 2 1 1 1
```

### 输出

```
2
```

# 题解

## 作者：Jr_Zlw (赞：5)

## 模拟 + 数论

这题乍一看想到竟然是一个简单的直接模拟，但是，诶，伤不起~~~

给大家参考一下能绿一排的模拟：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define u unsigned long long  
using namespace std;
u int a[100001],ans;
int main()
{
	u int n,h,k;cin>>n>>h>>k;
	u int que=0,res,p=1,now=1;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
	}
	while(p<=n||que>0)
	{
		while(que+a[p]<=h&&p<=n)
		{
			que+=a[p];
			p++;
		}
		if(int(que)-int(k)>0)que-=k;
		else que=0;
		ans++;
	}
	cout<<ans;return 0;
}
```
这个代码只能A第一排的测试点，第二排开始就会TLE了

其实我早就意识到这个代码是可以改进的，于是——我兴冲冲的改完，就是如下思路：

```
1、首先我们尽可能地把土豆塞进去

2、机子里土豆的长度除k其实就是把它们消灭得只剩一点点次数所以就能这样统计次数了，然后剩下的再加上现输入的就能说以此类推了

3、于是我的第一个已经剪过枝的程序出现了
```
但是，我兴冲冲的交上去，A了两排（~~太难了~~）

于是我在死死地检查以后，终于发现问题——还能再优化

我可以不用数组，对于每一个被塞进机子的土豆，如果长度比k小，那除以k直接就是0，于是我们并不需要用数组。

吭哧吭哧地改了一顿，第二版出来了。

其实已经做得差不多了，大部分同学相信都能做到，但是，要讨论最后还有没有剩余的土豆，如果有，还得+1，于是代码出来了。

于是奉上AC代码：

```
#include<iostream>
#include<cstdio>
#define u unsigned long long  
using namespace std;
int main()
{
	u int n,h,k,res=0,a=0,ans=0;
	cin>>n>>h>>k;
	for(int i=1;i<=n;++i)
	{
		cin>>a;
		if(a+res>h)
		{
			ans++;res=0;
		}
		res+=a;ans+=res/k;res%=k;
	}
	if(res)ans++;
    printf("%lld",ans);
    return 0;
}

```
其实比模拟的代码还短，但数论题就是这样，祝大家OI快乐

---

## 作者：shiziyu111 (赞：2)

## 题意
将 $n$ 个土豆**依次**放进高度为 $h$ 厘米的食品处理器，土豆处理器每秒可处理 $k$ 厘米的土豆，如果土豆的高度和食品处理器内未处理的土豆之和 $>h$，就不能放进土豆，问：最少要多少秒才能处理完这些土豆？
## 分析
因为 $n\le100000$，所以我们可以依次把它们放进去。具体做法如下：设总用时为 $time$，处理器内土豆高度为 $r$，此时处理第 $i$ 个土豆。

先让处理器将能够在**不浪费处理空间**的情况下处理，即 $time$ 加上 $r\div k$，$r$ 更新为 $r \bmod k$。

再判断能否将第 $i$ 个土豆装下，如果不行，将剩下的土豆也处理了。

最后，把第 $i$ 个土豆装入，就可以 AC 了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a;
	int n,h,k,times=0,r=0;
	cin>>n>>h>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a;	
		times+=r/k;
		r%=k;
		if(h-r<a)
		{
			r=0;
			times++;
		}
		r+=a; 
	}
	if(r%k!=0)
	{
		times+=r/k+1;
	}
	else
	{
		times+=r/k;
	}
	cout<<times;
	return 0;
}
```

---

## 作者：Fearliciz (赞：1)

这是一道比较普通的模拟题。

#### 题目翻译：

用一个能每秒粉碎 $\texttt{k}$ 单位长度的土豆粉碎机粉碎 $\texttt{n}$ 条土豆，第 $\texttt{i}$ 条土豆长为 $a_i$。土豆粉碎机只能放长度不超过 $\texttt{h}$ 的土豆，且只能在整数秒放，现在给你一个放土豆的顺序，求粉碎完土豆用的最短时间。

#### 解题思路：

1. 依次读入土豆的长度。

2. 如果机器剩余的长度能放下此土豆，则放下，否则不放。

3. 将机器中土豆粉碎完，时间增加。

4. 判断上一条中没粉碎完的土豆和下一条土豆能否在机器里放下。

5. 读入所有数据后，将机器里剩下的一点没粉碎的土豆粉碎。

这样代码就写好了：

```cpp
#include<bits/stdc+++.h>
using namespace std;
int n,h,k,a[100005];
int main()
{
	cin>>n>>h>>k;
	long long now=0,x,t=0; //now-现在机器里的钢管长度 t-花费的总时间
	for(int i=1;i<=n;i++){
		cin>>x;
		if(now+x<=h){
			now+=x;
			continue;
		}
		t+=now/k;
		now%=k;
		if(now+x>h){
			now=0;
			t++;
		}
		now+=x;
	}
	t+=now/k;
	now%=k;
	if(now>0) t++;
	cout<<t;
	return 0;
}
```


---

## 作者：_WHX985_ (赞：0)

这是一道比较简单的数论题。
## 具体思路
因为 $n\le100000$ 所以我们可以依次把所有土豆放进去。具体做法如下：当处理第 $i$ 个土豆时，先让处理器将能够在不浪费处理空间的情况下处理，即总时间加上此时土豆高度除以处理土豆的速度，土豆的高度更新为原高度除以处理土豆的速度的余数。再判断能否将第 $i$ 个土豆装下，如果不行，将剩下所有的土豆也处理了。最后，把第 $i$ 个土豆装入。
## 代码，有注释

```cpp
#include<iostream>
using namespace std;
long long a[1000005];
int si,ans;
int main(){
	long long n,h,k;
	cin>>n>>h>>k;//输入个数，高度上限，速度
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]+si>h){//放不进去
            si=0;
			ans++;
		}
		si+=a;
        ans+=si/k;
        si%=k;//更新高度
	}
	if(si){//如果未处理完再加一
        ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：szh_AK_all (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF677B)

这道题需要根据题意，模拟过程。我们用变量 $tim$ 来记录所花时间，用变量 $chang$ 来记录处理器中土豆的长度。先依次读入每根土豆的长度，将它加进处理器中，一直到不能加为止。如果不能加，那么计算时间，注意时间必须是整数，所以处理器中可能会有剩余的土豆。如果有剩余的土豆，那么再判断我们读入的这根土豆是否能放进处理器中，如果能，就直接放进去；否则，先将剩余的土豆处理完，再放进去。

一直重复如上过程，直到剩下最后一根土豆。如果按照如上过程处理后，还有剩余，那么直接让 $tim$ 加 $1$，因为不需要再放土豆了。

# Code
```c
#include<iostream>
using namespace std;
int main()
{
    long long n,h,k;
    cin>>n>>h>>k;
    long long tim=0,chang=0;
    for(int i=1;i<=n;i++)
    {
        int tu;
        cin>>tu;
        if((tu+chang)<=h)//如果还可以放，就接着放
            chang+=tu;
        else//如果不可以，那么先处理处理器中的土豆，再放进去
        {
            tim+=chang/k;
            chang%=k;
            if((chang+tu)>h)
            {
                chang=0;
                tim++;
            }
            chang+=tu;
        }
        if(i==n)//特判
        {
            tim+=chang/k;
            chang%=k;
            if(chang>0)
            tim++;
        }
    }
    cout<<tim;
    return 0;
}
```
最后，我想说，一定要开 `long long` 呀！

[此处观看效果更佳](https://www.luogu.com.cn/blog/jdsndjknddb/solution-cf677b)


---

## 作者：yyyymh (赞：0)

题目分析：这道题直接对于每一个需要粉碎的土豆进行时间模拟会超时，因此需要想到一个思路：对于一块土豆，如果它的高度小于 $ k $  ，那么一秒钟直接就磨完了，再定义一个 $ res $ 记录当前粉碎机里剩余的高度，当所有的土豆循环完以后再判断一次 $ res $ 是否大于零，若大于零说明还得再磨一次，也就是时间再次增加一秒，最终输出时间就可以了。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
	int k,n,h,p,height=0;
	long long ans=0;
	scanf("%d%d%d",&n,&h,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
    for(int i=1;i<=n;i++){
    	if(a[i]+height>h){
    		ans++,height=0;
		}
		height+=a[i];
		ans+=height/k;
		height%=k;
	}	
	if(height>0){
		ans++;
	}
	printf("%lld",ans);
	return 0;
}
```


---

