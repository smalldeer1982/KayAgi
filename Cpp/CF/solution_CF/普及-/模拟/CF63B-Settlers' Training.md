# Settlers' Training

## 题目描述

In a strategic computer game "Settlers II" one has to build defense structures to expand and protect the territory. Let's take one of these buildings. At the moment the defense structure accommodates exactly $ n $ soldiers. Within this task we can assume that the number of soldiers in the defense structure won't either increase or decrease.

Every soldier has a rank — some natural number from $ 1 $ to $ k $ . $ 1 $ stands for a private and $ k $ stands for a general. The higher the rank of the soldier is, the better he fights. Therefore, the player profits from having the soldiers of the highest possible rank.

To increase the ranks of soldiers they need to train. But the soldiers won't train for free, and each training session requires one golden coin. On each training session all the $ n $ soldiers are present.

At the end of each training session the soldiers' ranks increase as follows. First all the soldiers are divided into groups with the same rank, so that the least possible number of groups is formed. Then, within each of the groups where the soldiers below the rank $ k $ are present, exactly one soldier increases his rank by one.

You know the ranks of all $ n $ soldiers at the moment. Determine the number of golden coins that are needed to increase the ranks of all the soldiers to the rank $ k $ .

## 说明/提示

In the first example the ranks will be raised in the following manner:

1 2 2 3 $ → $ 2 2 3 4 $ → $ 2 3 4 4 $ → $ 3 4 4 4 $ → $ 4 4 4 4

Thus totals to 4 training sessions that require 4 golden coins.

## 样例 #1

### 输入

```
4 4
1 2 2 3
```

### 输出

```
4```

## 样例 #2

### 输入

```
4 3
1 1 1 1
```

### 输出

```
5```

# 题解

## 作者：良知 (赞：8)

正版题面(翻译部分有误，在此更正)：

一个共有n个数的非递减数列，还有一个整数target，每次操作可以让满足以下两个要求的数+1：

1. 该数比target小；

2. 该数不等于它后面的那个数。

特别地，最后一个数默认满足要求2.

你的任务是求出最小的操作数m，使得第m操作后，该数列中的所有数都等于target.

n,target<=100.

题解：

首先，我们可以注意到题目中的数列是**非递减**的。

我们可以先想象一个暴力模拟：

```cpp
记录步数=0；
while(1){
	判断数列中每一个数是否==target{
		是：输出步数，程序结束；
		否：找到每一个符合要求的数，步数+1.
	}

}
```
这个应该已经能过了(我没有试过，理论上平方阶的应该能过)

但是还能再快吗？

我们观察这个数列，它是一直保持非递减的吗？

是的！

我们想一下，如果一个数列中的数全都一样而且不到target，那么一波操作之后会有什么发生？

只有最后面的一个数会改变！

那么，一个普通数列是不是可以看做是由若干个上面的数列拼接而成的数列呢？

所以：

正解闪亮登场！

```cpp
#include<cstdio>
using namespace std;
int a[105];
int main()
{
	int num, target;
	scanf("%d%d", &num, &target);//见题面。
	for(int i=1; i<=num; ++i){
		scanf("%d", &a[i]);//a[i]存储初始数列。
	}
	int ans = 0;
	for(;;){
		for(int i=1; i<=num; ++i){
			if(a[i] == target && i == 1){printf("%d\n", ans);return 0;}//注意到这个了吗？就是上面所说的优化！如果第一个数都达到了target，那么由于数列的非递减性质，所有的数都一定等于target。少了一个n啊！
			else if(a[i] != a[i+1] && a[i] < target)++a[i];//模拟操作。
		}
		++ans;//记录步数+1
	}
	return 0;
 } 
```


---

## 作者：rui_er (赞：2)

思路：数据这么小，根据题意模拟即可。

---

具体做法：

- 判断第一个数的值，若等于 $k$ 则进入第四步。
- 根据题意对每个数遍历进行修改。
- 回到第一步，直到符合题意为止。
- 输出统计得到的结果即可。

但是这个程序的正确性依赖于整个过程中的单调不降性质，需要证明：

对于相邻两个数 $a$ 和 $b$：

- 如果 $a=b$，不进行修改， $a$ 与 $b$ 依然相等。
- 如果 $a\lt b$，将 $a$ 加一，此时 $a\le b$。

由于初始序列单调不降，因此任意时刻，数列满足单调不降。

程序的正确性得证。

---

一个小 trick：C++ 中单独的逗号语句的值为最后一个逗号后的表达式的值，与前面无关，因此可以通过这个简写一些代码。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int N = 105;

int n, k, a[N], ans;

int main() {
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++) scanf("%d", &a[i]);
	do {
		if(a[1] == k) return printf("%d\n", ans), 0;
		for(int i=1;i<=n;i++) {
			if(a[i] < k && a[i] != a[i+1]) ++a[i];
		}
	}while(++ans, true);
	return 0;
}
```

---

## 作者：EDqwq (赞：1)

#### 表面上，这道题就是个简单模拟，实际上，还是有~~亿~~一点点坑点，本题解将会总结一下。

***
题意：给出一个拥有$n$个元素的数组$a$，保证递增，问最少进行多少次以下操作，可以使所有的元素都为$k$：

1. 如果该元素小于$k$，并且它不等于它后面一个的元素的话，它加1。

1. 最后一个元素默认不等于后面一个元素。

***

这道题的数据范围是$1 <= n,k <= 100$，十分水，所以暴力模拟即可。

过程如下：

1. 从1循环到$n$，判断是否可以加1，如果可以直接加

1. 判断是否符合退出条件，如果可以，直接退出并输出答案

1. 如果不行，计数器++

这时，好奇的小朋友就会问了：**怎么判断退出条件呢？难道直接循环？**

虽然这样可以，但是比较慢，我们可以考虑这样一种方法：**由于我们是从1开始循环，而原本就是递增的，所以我们只需要看元素1是不是等于k即可**。

***

下面是坑点：

判断是否符合条件的语句一定要放在循环开头，如果你放在计数器++前面，就无法判断直接满足的数据，这也是这道题唯一的坑点，也是其他题解并没有阐述的地方。

***
上代码，请配合注释食用：
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,k;
int a[100000];
int ans;

int main(){
	cin>>n>>k;
	for(int i = 1;i <= n;i ++)cin>>a[i];
	a[n + 1] = 2147483600;//最后一个设为一个不可能达到的值
	while(1){
		if(a[1] == k)break;//把判断放在循环开头
		for(int i = 1;i <= n;i ++){
			if(a[i] < k && a[i + 1] != a[i])a[i] ++;//判断是否可以++
		}
		ans ++;//计数器++
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

这道题纯模拟。

增加1有两个条件：

```
1.该数比k小
2.该数不等于它后面的那个数。

特别地，最后一个数默认满足要求2。
```

首先，最后一位默认满足要求2，所以答案一定**有解**，而且也不需要特判，是因为全局变量默认为0自动满足要求。

之后一定要从前到后更新，因为从前往后更新对后面的更新不会产生影响，但从后往前就会产生，例如将 $1,2,2,3$ 第一轮从前向后更新为 $2,2,3,4$ ，从后往前变为 $2,3,3,4$ 。

因为原来的序列是递增的，前面的数最多只能和后面的数相等，不能继续满足第1个条件，所以只判断第一个就行了。

上代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
int n,a[101],ans,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	a[n+1]=0;
	while(1){//循环
		if(a[1]==k)
			break;
		for(int i=1;i<=n;i++)
			if(a[i]<k&&a[i]!=a[i+1])//判断，不到k而且相邻不相等
				a[i]++;
		ans++;//一定记住要+1
	}
	cout<<ans<<endl;
	return 0;
}

```

谢谢大家！

---

## 作者：RainFestival (赞：1)

这道题目直接模拟即可

注意循环方向

附代码
```cpp
#include<cstdio>
int n,a[105],sum,k;
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    a[n+1]=0;
    while (1)
    {
        if (a[1]==k) break;
        for (int i=1;i<=n;i++)
            if (a[i]<k&&a[i]!=a[i+1]) a[i]++;
        sum++;
    }
    printf("%d",sum);
}
```


---

## 作者：Mint_Flipped (赞：0)

简单的模拟

注意两个条件：

1：相邻的且不同的两个数才能操作。

2：操作为前一个数加1。

我们只要模拟这一个过程，走N遍，直到所有数为k。

注意：因为条件2，后面的数先为k，所以循环结束条件就为第一个数为k。

~~PS：我真的觉得这道题应该调到普及题去的 QAQ~~

代码如下：
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e2+5;
const int mod=1e9+7;
const double eps=1e-6;
int p[maxn],ans;
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    fo2(i,n)
    scanf("%d",&p[i]);
    while(1){
        if(p[1]==k)
            break;
        fo2(i,n){
            if(p[i]<k&&p[i]!=p[i+1])
            p[i]++;
        }
        ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```


---

