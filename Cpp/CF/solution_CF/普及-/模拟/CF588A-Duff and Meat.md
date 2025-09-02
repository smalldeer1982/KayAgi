# Duff and Meat

## 题目描述

Duff is addicted to meat! Malek wants to keep her happy for $ n $ days. In order to be happy in $ i $ -th day, she needs to eat exactly $ a_{i} $ kilograms of meat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF588A/e0a1a4af93fd8d07e258d5dc1cd3e48db986dfbc.png)There is a big shop uptown and Malek wants to buy meat for her from there. In $ i $ -th day, they sell meat for $ p_{i} $ dollars per kilogram. Malek knows all numbers $ a_{1},...,a_{n} $ and $ p_{1},...,p_{n} $ . In each day, he can buy arbitrary amount of meat, also he can keep some meat he has for the future.

Malek is a little tired from cooking meat, so he asked for your help. Help him to minimize the total money he spends to keep Duff happy for $ n $ days.

## 说明/提示

In the first sample case: An optimal way would be to buy 1 kg on the first day, 2 kg on the second day and 3 kg on the third day.

In the second sample case: An optimal way would be to buy 1 kg on the first day and 5 kg (needed meat for the second and third day) on the second day.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3
1 3
2 1
3 2
```

### 输出

```
8
```

# 题解

## 作者：灵光一闪 (赞：3)

~~我是最短的代码！~~

一眼贪心，边读边判，如果这天的肉特别便宜（跌出目前的最低价，更新最低价），然后``ans+=最低价*今天要用到的数量``

OK，然后就是代码了：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
int a[100005],b[100005],ans,n,num=2e9,tep;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i]>>b[i];
        if(num>b[i]){//跌出了最低价
            num=b[i];//更新最低价
        }
        ans+=num*a[i];//然后相乘再加进ans里
    }
    cout<<ans;//输出……
    return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

本题解提供PY代码。先来看思路。

这道题的关键在于，这个肉是可以囤的。所以，我们可以假设这个人有先见之明，总是在价格最低的那一天买肉。当然，这个价格最低，指的是在当天以及当天前的范围中，价格最低的那一天。

所以，我们可以边输入，边累加，公式就是当天需要的肉的数量$×$目前为止价格的最小值。最小值可以再输入过程中不断更新。

废话不多说，上代码！

```python
n=int(input())
minn=101 #由于p<=100，minn设成101就可以了
ans=0 #答案变量，别忘了赋0
for i in range(n): #n天
    a,b=map(int,input().split())
    minn=min(minn,b) #如果当天价格是有史以来最小的就更新最小值（PY自带min()函数）
    ans+=a*minn #累加总价格，当天需要*最低价
print(ans) #循环结束后输出
```
好了，这题就简单地A了。希望大家喜欢，求赞！

---

## 作者：LYR_ (赞：0)

这是一篇与其他题解思路差不多但另有优化的题解。

### 题意
有一个人，想吃 $n$ 天肉，第 $i$ 天需要吃 $a[i]$ 块肉，第 $i$ 天超市肉价为每块 $b[i]$ 元，买来的肉可以留到后面吃，求这个人在每天都吃到肉的情况下花费的最小值。

**题目标签：贪心**

### 思路
一边输入一边计算，每次记录下最低价格，即  $mini=min(mini,b[i])$ 然后乘以每天所需要的肉的数量。即 $ans+=mini\times a[i]$ 。

### 代码段：
比较容易实现

```cpp
for(int i=0;i<n;i++) {
	cin>>a[i]>>b[i];
    mini=min(mini,b[i]);  // 每次比较出最小肉价
    ans+=mini*a[i]; // 加上需要花的钱
}
```

如果你追求最优解，可以在内存上进行优化，将数组改为变量。

```cpp
for(int i=0;i<n;i++) {
    cin>>a>>b; // 数组改为变量
    mini=min(mini,b);
    ans+=mini*a;
}
```


---

## 作者：树下 (赞：0)

#### 贪一波 小蒟蒻来写题解了
```
#include<bits/stdc++.h>//万能头
using namespace std;
int a[100005],b[100005];//数组要开大一点哈
int n,ans,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&b[i],&a[i]);
	ans=a[1];
	sum=b[1]*ans;
	for(int i=2;i<=n;i++)
	if(a[i]<ans){
		ans=a[i];
		sum+=b[i]*ans;
	}
	else
		sum+=b[i]*ans;
	printf("%d",sum);
}//没有写return 0 结束的习惯，大佬谅解
```

---

