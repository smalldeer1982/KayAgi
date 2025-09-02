# Roadside Trees (Simplified Edition)

## 题目描述

Squirrel Liss loves nuts. There are $ n $ trees (numbered $ 1 $ to $ n $ from west to east) along a street and there is a delicious nut on the top of each tree. The height of the tree $ i $ is $ h_{i} $ . Liss wants to eat all nuts.

Now Liss is on the root of the tree with the number $ 1 $ . In one second Liss can perform one of the following actions:

- Walk up or down one unit on a tree.
- Eat a nut on the top of the current tree.
- Jump to the next tree. In this action the height of Liss doesn't change. More formally, when Liss is at height $ h $ of the tree $ i $ ( $ 1<=i<=n-1 $ ), she jumps to height $ h $ of the tree $ i+1 $ . This action can't be performed if $ h&gt;h_{i+1} $ .

Compute the minimal time (in seconds) required to eat all nuts.

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
2
1
2
1
1
```

### 输出

```
14
```

# 题解

## 作者：_H17_ (赞：6)

## 思路分析

既然不可以往前走任何一棵树，那么我们的顺序只能是从第 $1$ 课吃到第 $n$ 课。

可以直接进行模拟，高度不够就往上爬，然后吃掉，如果下一棵树比较矮就往下爬，否则不动，然后跳到下一棵树上。最后第 $n$ 棵树跳到第 $n+1$ 棵树（不存在的树）可以这样：假设第 $n+1$ 棵树的高度等于第 $n$ 棵树，这样不用趴下去，但是多执行了一次“跳”的操作，所以最后输出答案的值减一即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100002],ans,now;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    a[n+1]=a[n];//特殊设置
    for(int i=1;i<=n;i++){
        ans+=a[i]-now+1,now=a[i];//爬上去+吃果子
        if(a[i]>a[i+1])
            now=a[i+1],ans+=a[i]-a[i+1];//趴下去
        ans++;//跳到下一棵树上
    }
    printf("%d",ans-1);
    return 0;
}
```

---

## 作者：Marshall001 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF265B)

## 题目大意

大街上有 $n$ 棵树，每棵树的树顶都有一个坚果。一只松鼠在第一棵树的最底端，这只松鼠可以在一秒钟完成以下几个动作。

- 往下或往上爬一米。
- 如果松鼠在树顶，就可以吃掉树顶的坚果。
- 从第 $i$ 棵树跳到第 $i+1$ 棵树。（这时松鼠的高度不变，如果第 $i$ 棵比第 $i+1$ 棵高，就不可以执行此动作）

这只松鼠想要吃掉所有的坚果，请求出吃掉所有坚果一共需要用多少秒。

## 思路

观察可以发现，从第 $i$ 棵树跳到第 $i+1$ 棵树，一共要用 $h_{i}-h_{i+1}+1$。为什么要加一呢？以为吃掉一个坚果也要一秒的时间。可从第 $i$ 棵树跳到第 $i+1$ 棵树的时间呢？我么可以提前初始化好，这样就不用在加一了。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n,last,h,ans;//last是上一棵树的高度。
int main(){
	cin>>n;
	ans=n-1;//初始化
	for(int i=1;i<=n;i++){
		cin>>h;
		ans+=labs(last-h)+1;
		last=h;
	}
	cout<<ans;
	return 0;
}
```

## THE END

---

## 作者：WoodReal12 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF265B)

## 题目大意：
- 有 $n$ 棵树；
- 有三个操作：上下爬，吃松果，换一颗树（在同一个高度）；
- 求最短时间；

## 解题方案：
当站在第 $i$ 棵树上时，先爬到树顶，吃松果。再判断：如果下一棵比这一棵矮，就往下爬。否则就直接去下一颗树。

**注意: 因为循环到第 $n$ 棵树时会找不到第 $n+1$ 棵树，所以只循环到 $n-1$ 即可（第 $n$ 棵最后算）。**

## 代码：
```cpp
#include <iostream>
using namespace std;

int n,a[100005];
int main(){
    int h=0,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n-1;i++){//只循环到n-1！
        ans+=(a[i]-h),ans++,h=a[i];
        if(a[i+1]<a[i]){//如果比这棵矮
            ans+=(a[i]-a[i+1]),ans++,h=a[i+1];
        }
        else if(a[i+1]>a[i]){//如果比这棵高
            ans++;
        }
        else{//与这棵树相等
            ans++;
        }
    }
    ans+=(a[n]-h+1);//最后算第n棵树
    cout<<ans<<endl;
    return 0;
}
```

本蒟蒻第一篇题解，请多关照！QwQ！

---

## 作者：_ouhsnaijgnat_ (赞：2)

## 题目大意

给你 $n$ 棵树的高度，每次有 $3$ 个操作。

第一个，在树顶上停留。

第二个，将树的高度 $+1$ 或 $-1$。

第三个，从第 $i$ 棵树跳到第 $i-1$ 棵树。

以上操作都需要 $1$ 秒的时间，问你最少要花多少秒才能到最后一棵树。

## 思路

模拟题，但要注意，每次跳到下一棵树上，这个操作一共只有 $n-1$ 秒！

先输入高度 $h$，用 $ans$ 记录下要改变多少个高度，再用 $cnt$ 来记录这棵树高度就行了。

代码奉上。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n,a,h,ans;//ans累加，h为记录树的高度 
int main(){
	cin>>n;
	ans=n*2-1;//先把能算出来的算出来 
	for(int i=1;i<=n;i++){
		cin>>a;
		ans=ans+labs(a-h);
		h=a;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：123456zmy (赞：1)

题意：  
给你一个序列 $h$，表示一排树的高度，你每秒可以完成下列事件之一：

- 将自己的高度改变 $1$。
- 在树顶停留不动。
- 跳到下一棵树的同一高度，要求下一棵树的高度不低于你现在的高度。

最开始你位于第一棵树的底下（高度为 $0$）输出在每一棵树的树顶都停留 $1s$ 需要的最短时间。
___
经过观察可以发现，你从第 $i$ 棵树到第 $i+1$ 棵树的树顶需要的时间是 $|{h_{i+1}-h_{i}}|+1$ ，把 $h$ 数组扫一遍即可得出答案，最后记得加上在每一棵树顶上停留的时间。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,h,a;
int main()
{
	scanf("%d",&n);
	ans=(n<<1)-1;
	while(n--)
	{
		scanf("%d",&a);
		ans+=abs(a-h);
		h=a;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 分析

模拟大水题！

首先，我们可以知道，松鼠只能按 $1\sim n$ 的树的顺序吃坚果，因为他只能一棵一棵树地跳。那就直接模拟。

设松鼠当前高度为 $h$，第 $i$ 棵树的高度为 $a_i$。那么对于每一棵树，就有以下操作：

1. 爬上去吃掉第 $i$ 棵树上的坚果。耗时 $a_i-h+1$（加 $1$ 是因为松鼠要花 $1$ 秒来吃坚果）；

2. 如果 $h>a_{i+1}$，那么就要爬下去，耗时 $h-a_{i+1}$；

3. 最后，跳到第 $i+1$ 棵树上，耗时 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10002],ans,h;
int main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	a[n+1] = n; 
	for(int i = 1;i<=n;i++)
		ans+=a[i]-h+(a[i]>a[i+1])?(a[i]-a[i+1]):0+2,//整合了耗时 
		h = (a[i]>a[i+1])?a[i+1]:a[i];//好用的三目运算符 
	cout<<ans-1;//最后会多跳一棵树，所以-1
	return 0;
}
```

---

## 作者：Leaves_xw (赞：0)


### 先看大意：

大街上有 $n$ 棵树，每棵树的树顶都有一个坚果。一只松鼠在第一棵树的最底端，这只松鼠可以在一秒钟完成以下几个动作。

* 往下或往上爬一米。
* 如果松鼠在树顶，就可以吃掉树顶的坚果。
* 从第 $i$ 棵树跳到第 $i+1$ 棵树。（这时松鼠的高度不变，如果第 $i$ 棵比第 $i+1$ 棵高，就不可以执行此动作）

问：这只松鼠想要吃掉所有的坚果，请求出吃掉所有坚果一共需要用多少秒。

### 思路整理：

首先我们要初始化，将 $ans$ 先+ $1$，因为松鼠吃掉一个坚果也需要 $1$ 秒。看着像贪心，其实是一道模拟题目。 $ans$ 来记录改变的高度数量， $cnt$ 记录这棵树的高度。

### code：

```
#include<bits/stdc++.h>
using namespace std;
long long n,a,h,ans;//使用long long,int可能会爆 
//h记录上一棵树的高度
int main()
{
	cin>>n;
	ans=n*2-1;//先初始化 
	for(int i=1;i<=n;i++)
        {
		cin>>a;//输入每棵树的高度
		ans=ans+abs(a-h);
		h=a;
	}
	cout<<ans<<endl;
	return 0;
}
```
欢迎指出问题。

---

## 作者：许多 (赞：0)

一道小模拟，把在每棵树上用的时间加起来即可。但有一个细节需要处理：

从第一棵树上跳到下一棵树上，这个过程只用 $n-1$ 次。但要吃 $n$ 次松果。

更多细节见代码。

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
long long n,a,h,ans=0;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a=read();
		ans+=abs(a-h)+2;//+2一次是从这棵树上跳到下一棵树上，一次是吃松果所用的时间
		h=a;//更新树的高度
	}
	cout<<ans-1;//松鼠只需要跳n-1次
	return 0;
}

```



---

