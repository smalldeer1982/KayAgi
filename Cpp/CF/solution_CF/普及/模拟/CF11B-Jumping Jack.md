# Jumping Jack

## 题目描述

Jack is working on his jumping skills recently. Currently he's located at point zero of the number line. He would like to get to the point $ x $ . In order to train, he has decided that he'll first jump by only one unit, and each subsequent jump will be exactly one longer than the previous one. He can go either left or right with each jump. He wonders how many jumps he needs to reach $ x $ .

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
0
```

### 输出

```
0
```

# 题解

## 作者：Loner_Knowledge (赞：38)

这是一道数学题

---

题意是求到达`x`的最少跳跃次数。首先由于对称，`x`与是`-x`是等效的，因此均把负数看做正数。设最少跳跃次数为`n`，那么可以得到一个结果$d=(\pm1)+(\pm2)+...+(\pm n)$。

最快的跳法是往一个方向一直跳。如果恰好能到`x`，这样肯定是跳跃次数最小。如果不能恰好跳到，那么我们设`y`为以这种跳法得到的第一个比`x`大的点，如果`y-x`为偶数，可以将第`(y-x)/2`步往左跳，这样就能恰好跳到`x`了；如果`y-x`为奇数，那么继续跳直到与`x`的差为偶数即可。

```cpp
#include<cstdio>
int main() {
	int x,ans=0;
	scanf("%d",&x);
	if(x<0)			//将负点转换为正点
		x=-x;
	for(int i=1,t=1;x&&!ans;++i,t+=i)	//i为跳跃次数，t为累计跳跃的距离
		if(t==x||(t>x&&!((t-x)%2)))
			ans=i;						//符合分析中的条件便跳出循环
	printf("%d",ans);
	return 0;
}
```

---


---

## 作者：珅肐 (赞：19)

更优的做法！

其实$O(\sqrt x)$已经足够了，其他两篇题解就是$O(\sqrt x)$模拟了跳的步数

那两篇讲的已经够好了，这里只简单说一下

我们一次一次向右跳，直到刚好跳到或跳过

刚好跳到即最优解，

否则，我们设当前跳到$y$

如果$y-x$为偶数，可以将第$\frac{(y-x)}2$步往左跳，步数减少了$\frac{(y-x)}2*2$，可以恰好跳到$x$.

如果$y-x$为奇数，那么继续跳

但是，我们还有更优的算法

我们二分跳的步数$l$，直到跳到或跳过$x$

然后按上面步骤进行

复杂度$O(log\sqrt x)$

又：

如果$y-x$为奇数

$1.$ 二分到的$l$是奇数，还需要跳两次

$2.$ 二分到的$l$是偶数，还需要跳一次

最多需要两次

### 代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cmath>
using namespace std;
inline int read(){//快读，可快了，虽然这道题没什么用
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x;
}
int main(){
	int x=read(),ans=0,l=0,r=sqrt(x+x)+1;//二分边界设到平方刚好大于x即可
	while(l<=r){
		int m=l+r>>1;
		if(m*(m+1)/2<x)l=m+1;
		else r=m-1;
	}//普通二分
	if((l*(l+1)/2-x)&1)++l;
	if((l*(l+1)/2-x)&1)++l;//最多进行两次
	printf("%d\n",l);
	return 0;//好习惯
}
```


---

