# Luxurious Houses

## 题目描述

The capital of Berland has $ n $ multifloor buildings. The architect who built up the capital was very creative, so all the houses were built in one row.

Let's enumerate all the houses from left to right, starting with one. A house is considered to be luxurious if the number of floors in it is strictly greater than in all the houses with larger numbers. In other words, a house is luxurious if the number of floors in it is strictly greater than in all the houses, which are located to the right from it. In this task it is assumed that the heights of floors in the houses are the same.

The new architect is interested in $ n $ questions, $ i $ -th of them is about the following: "how many floors should be added to the $ i $ -th house to make it luxurious?" (for all $ i $ from $ 1 $ to $ n $ , inclusive). You need to help him cope with this task.

Note that all these questions are independent from each other — the answer to the question for house $ i $ does not affect other answers (i.e., the floors to the houses are not actually added).

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
3 2 0 2 0 ```

## 样例 #2

### 输入

```
4
3 2 1 4
```

### 输出

```
2 3 4 0 ```

# 题解

## 作者：wanggk (赞：4)

#### **Key Points:**

1. 从后往前，目的是不断更新从右数的最大值。

2. 当前楼房希望达到的高度为**当前最大值+1**.

3. 若高于希望的高度，输出0；否则输出差值。

---

```cpp
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int mx=0;
	for(int i=n;i>=1;i--){
		if(a[i]>mx) ans[i]=0;
		else ans[i]=mx+1-a[i];
		mx=max(mx,a[i]);
	}
	for(int i=1;i<n;i++) printf("%d ",ans[i]);
	printf("0\n");
	return 0;
}
```


---

## 作者：_ouhsnaijgnat_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF581B)

## 题目大意

求一个数增加多少可以大于他右边的所有数中的最大值。

## 思路

我们可以遍历一遍 $n\backsim1$，用 $mx$ 记录这个数他右边的最大值，在判断这个数是否比 $mx$ 大，大的话输出 $0$，小的话输出相差 $+1$。就这样对了这道 $1\leq n\leq10^5$ 的题，时间复杂度为 $O(n)$。

注意，我们应该用一个数组记下答案，因为我们是从大到小，不能直接输出。
## 代码

```cpp
#include<iostream>
#include<string>
using namespace std;
int n,mx=-1,a[100003],c[100003];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	c[n]=0;
	mx=a[n];
	for(int i=n-1;i>=1;i--){
		if(a[i]>mx)c[i]=0;//如果大直接输出0
		else c[i]=mx-a[i]+1;//否则输出差值。
		mx=max(mx,a[i]);
	}
	for(int i=1;i<=n;i++)
		cout<<c[i]<<' ';
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
一条大街上有 $n$ 个房子，第 $i$ 个房子的楼层数量是 $h_i$。如果一个房子的楼层数量大于位于其右侧的所有房屋，则房屋是豪华的。对于第 $i$ 个房子，请求出至少要添加多少层才能使这个房子变得豪华。注意，对于所有的房子，其答案互不影响。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant h_i\leqslant 10^9$。**
## Solution
我们可以由后往前求出从 $i$ 到 $n$ 的 $h_i$ 最大值 $s_i=\max\{s_{i+1},h_i\}$，然后再记录最大值有变化时的位置，最后很明显，这些房子都不需要盖楼了，否则对于第 $i$ 个房子，需要盖的楼层数就是 $s_i+1-a_i$（$s_i$ 的含义上面有讲）。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[100007], maxi[100007], effo[100007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	maxi[n] = a[n], effo[n] = n;
	for(int i = n - 1; i >= 1; --i) {
        if(a[i] > maxi[i + 1]) {
			maxi[i] = a[i];
			effo[i] = i;
		} else {
            maxi[i] = maxi[i + 1];
            effo[i] = effo[i + 1];
        }
    }
	for(int i = 1; i <= n; ++i) {
        if(effo[i] == i)    printf("0 ");
        else printf("%d ", maxi[i] + 1 - a[i]);
    }
    return 0;
}
```

---

## 作者：lyhqwq (赞：0)

### 思路

从后往前遍历，记录下**已经遍历过的**最大值 $\max$，枚举到 $a_i$ 时，用 $ans_i$ 记录 $a_i$ 的答案：

$ans_i = \begin{cases}
0 ,& a_i>\max\\
\max-a_i+1 ,& \text{otherwise.}
\end{cases}$

最后倒序输出即可。

### ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxn; 
int a[1000005],ans[1000005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i>0;i--){
        if(a[i]>maxn) ans[i]=0;
        else ans[i]=maxn-a[i]+1;
        maxn=max(a[i],maxn);
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}
```


---

## 作者：ckk11288 (赞：0)

看懂题目后，就可以理思路了：

为了使自己的房屋**是豪华的**，就需要比右边所有的房屋高。那么我们可以用一个数组存储每个房屋右边房屋的最大高度值，最后用一个循环输出每个房屋最小需要添加的层数。

**Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],i,b[100005],maxn;//数组b用来记录每个房屋右侧房屋高度的最大值
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=n;i>=1;i--)//逆序扫描，用变量maxn记录当前最大值
	{
		b[i]=maxn;
		maxn=max(a[i],maxn);//记录
     //可以输出b数组看当前结果是否正确
	}
	for(i=1;i<=n;i++)
	{
		a[i]=max(b[i]-a[i]+1,0);//若负数即为不用添加，因此视为0
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：WKAHPM (赞：0)

不难看出，题目要求的是每一个房子后面最高的房子与它的高度差$+1$，（如果比它矮输出$0$）

我们定义

- $maxn[i]$表示第$i$到第$n$个房子高度的最大值（$n$为房子数）

- $h[i]$表示第$i$个房子的高度

因为$maxn[i+1]$存放的已经是第$i+1$到第$n$个房子的最大值了，所以第$i$到第$n$个房子的最大值只要让当前房子的高度与$maxn[i+1]$进行比较即可

即$maxn[i]=max(h[i],maxn[i+1])$

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int n;
int h[MAXN] , maxn[MAXN];
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		cin >> h[i];
	}
	for(int i = n; i >= 2; i --)
	   maxn[i] = max(h[i] , maxn[i + 1]); //预处理最大值
	for(int i = 1; i <= n - 1; i ++)
	  cout << max(maxn[i + 1] - h[i] + 1 , 0) << " ";//如果没比它高要输出0！
	cout << 0;//最后一个后面已经没有房子了当然是0
	return 0;
}

```


---

## 作者：Mysterious_bird (赞：0)

### 题目解析：
给你n栋房子，问你第i栋房子要再搭几层才能比它后面所有的房子高 **（注意：是要严格大于，不能等于）**

所以我们只要找到第i栋房子后面最高的一栋，然后比较

### 样例说明：
5

1 2 3 1 2

第1栋房子高度为1，身后最高的房子高度为3，需要增加3层才能才能大于身后所有房子，为3；

第2栋房子高度为2，身后最高的房子高度为3，需要增加2层才能才能大于身后所有房子，为2；

第3栋房子高度为3，身后最高的房子高度为2，自身已经高于身后最高的房子，不需要增加，为0；

第4栋房子高度为1，身后最高的房子高度为2，需要增加2层才能才能大于身后所有房子，为2；

第5栋房子高度为2，身后没有房子，所以不用增加，为0；

输出：

3 2 0 2 0

怎样来找出第i栋房子身后的最大值呢？
#### 代码实现：
```cpp
for(int i=n;i>=1;i--)	//注意，是从后往前
    maxn[i]=max(a[i],maxn[i+1]);    //处理最大值
```
#### 原理：

让我们来直接模拟一下

2 1 3 2 1（注意：是从后往前）

最后一栋房子身后没有房子了，那他的最大值就是自己

maxn\[i\]=2

倒数第二栋：

前一栋的最大值和自己相比较

maxn\[i\]=(2,1)

maxn\[i\]=2

倒数第三栋：

maxn\[i\]=(2,3)

maxn\[i\]=3

倒数第四栋：

maxn\[i\]=(3,2)

maxn\[i\]=3

倒数第五栋：

maxn\[i\]=(3,1)

maxn\[i\]=3

结束！

那怎么来输出差多少层呢？

#### 代码实现：
```cpp
printf("%d ",max(maxn[i+1]-a[i]+1,0));	//因为可能会有自身本就高于身后房屋的情况，相减出现负数时要输出0
```
这段代码还是很好理解的吧！

接下来就是AC代码了！
```cpp
#include <cstdio>
#include <algorithm>    //包涵max和min函数的头文件
using namespace std;
int a[100010],maxn[100010];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=n;i>=1;i--)   //注意，是从后往前
        maxn[i]=max(a[i],maxn[i+1]);    //处理最大值
    for(int i=1;i<=n;i++)
        printf("%d ",max(maxn[i+1]-a[i]+1,0));  //因为可能会有自身本就高于身后房屋的情况，相减出现负数时要输出0
    return 0;   //完美结束【放烟花】
}
```


---

