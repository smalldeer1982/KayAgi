# Presents

## 题目描述

刺猬喜欢给朋友送礼物，但他不喜欢收到礼物。（有钱的刺猬）

所以，刺猬要求你给他写一个程序，计算他在接下来的几天里收到的礼物数。他收到的礼物遵循以下原则：

在每个假日日，刺猬一定会收到礼物
他每K天会收到至少一件礼物（即，如果他在第i天收到了一件礼物，那么他会在i+k天或之前再次收到一见礼物，但在一天里，无论他收到多少礼物，仅被视为收到一件礼物）。
给定的n和k，以及在接下来的n天中的假期列表，请计算刺猬的能获得礼物最少数量。今天的日期视作零，你应该把今天的礼物看作是已经存在的（也就是说，你不应该把它算在答案里）。

## 样例 #1

### 输入

```
5 2
1 3
```

### 输出

```
3```

## 样例 #2

### 输入

```
10 1
3 6 7 8
```

### 输出

```
10```

# 题解

## 作者：Forever1507 (赞：2)

# [传送门](https://www.luogu.com.cn/problem/CF54A)


## 思路：
总的来说就是假期必收礼物，那么可以先定义一个数组用来存假期的日期，
然后处理两个假期之间的空隙（处理端点还是有亿点点坑的）
之后累加起来，最后再处理最后一段没有假期的日子即可(因此无需考虑没有假期的情况)，具体操作见注释。


## ~~码风极丑的~~代码Code：
```cpp
#include<bits/stdc++.h>//懒人专用万能头
using namespace std;
int day[400];//记录假期的日期
int n,k,c,ans;
int main(){
    cin>>n>>k>>c;
    for(int i=1;i<=c;i++){
    	cin>>day[i];
    	ans+=(day[i]-day[i-1]-1)/k+1;//假期一定有礼物，那么我们可以针对假期的间隔进行处理，特别注意括号里去掉端点后别忘了加回来,因为一定有礼物(卡了好久啊。。。)
    }
    ans+=(n-day[c])/k;//所有假期都过完了的日子再处理一下即可
    cout<<ans;
    return 0;
}
```


---

## 作者：lichenfan (赞：1)

## 贪心思路
刚做这题时，以为可以打暴力，后来发现肯定要炸，就去想贪心思路了。思路是这样的：每次处理两个假期中的方案数，并且将端点算上 $+1$，最后用贪心算一下最小值。   
### 循环内代码：

```cpp

    for(int i=1;i<=c;i++){
        cin>>a[i];
        ans+=(a[i]-a[i-1]-1)/k+1;
    }
```
但是最后一个节点没有考虑到，所以外面还需加 $(n-a[i])/k$ 个礼物，即为最终答案。  
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001],ans;
int main()
{
    int n,k,c;
    cin>>n>>k>>c;
    for(int i=1;i<=c;i++)
    {
        cin>>a[i];
        ans+=(a[i]-a[i-1]-1)/k+1;
    }
    ans+=(n-a[c])/k;
    cout<<ans;
}
```





---

## 作者：Allanljx (赞：1)

## 题意
有一个有钱人，他并不想收到礼物，担有许多人都要给他送礼物。他如果在第 $i$ 天收到了一个礼物，那么在 $i+k$ 天前就会收到一个礼物；并且每个假期都会收到一个礼物。请输出他所能收到的礼物的最小数。
## 思路
用 $a$ 数组记录假期的日期，再用贪心去求所能获得的最小值，就是处理两个假期间的礼物数，最后在加上假期数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[370];
int main()
{
    int n,k,m,ans=0;
    cin>>n>>k>>m;
    for(int i=1;i<=m;i++)
	{
    	cin>>a[i];
    	ans+=(a[i]-a[i-1]-1)/k;//处理两个假期中间的空档，-1是因为不算端点 
    }
    ans+=(n-a[m])/k;//处理最后一个假期后的空档 
    cout<<ans+m<<endl;//加上假期数 
    return 0;
}
```


---

## 作者：mzyc_pzx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF54A)

又一道水水的贪心题。
### 注意事项：
1. 假期必收礼物。
2. 不用考虑无假期。
## 思路：
每解决两个假期的空隙，就累加再算最小值，最后处理非假期的时间。
### 奉上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[365],sum,n,k,C;
int main()
{
    cin>>n>>k>>C;
    for(int i=1;i<=C;i++)
    {
        cin>>a[i];
        sum+=(a[i]-a[i-1]-1)/k+1;
    }
    sum+=(n-a[C])/k;
    cout<<sum;
}
```


---

## 作者：DiDi123 (赞：0)

# 题目分析
这道题其实不是很难，可以用模拟的方法 ~~（因为我太弱了）~~ 。我们可以框定一段长为 $k$ 的时间，如果在这一段时间里没有假期，那就说明其中必有一个非假期日刺猬能收到礼物。那就不难得到方法：

首先将所有的假期录入，有假期的天设为 $1$。记录一个长度为 $k$ 的时间区间，和一个 $sum$ 值（$sum$ 值表示这个区间内所有数的和）。每次把这个区间向右移一格，如果 $sum=0$ 说明这段时间没有假期，我们将这段时间的最后一天设为刺猬收到礼物的那天（因为这样这天可以影响最多的其他天，换句话说，就是刺猬能在后面最长一段时间不用收到礼物，可以感性理解一下这句话）。
# 代码
**（注意：数组开大点）**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, c;
int a[400];
int sum, a1, ans;
int main() {
	cin >> n >> k;
	cin >> c;
	for (int i = 1; i <= c; i++) {
		cin >> a1;
		a[a1]++;
		ans++;
	}
	for (int i = 1; i <= k; i++)
		sum += a[i];
	for (int l = 1, r = k; r <= n; r++, l++) {
		if (sum == 0) {
			a[r]++; //将刺猬收到礼物那天设为这段时间的最后一天 
			sum++;
			ans++;
		}
		sum -= a[l];
		sum += a[r + 1]; //sum动态更新 
	}
	cout << ans;
}
```


---

## 作者：laeva (赞：0)

# 贪心大法好
题目中说每k天刺猬就得到至少一个礼物，也就是说，在任意长度为k的序列中，必然有一天他收到了礼物（无论他放不放假）~~（玩过的崩崩崩的都知道）~~，这样的话，我们把每两个假期中间的日期处理一下，再加上假期数，完美解决。
##### 怎么处理？？
当然是找出在两个假期中最多出现互不相交，长度为k的块，在这个块的结尾收到礼物，即为最少的情况~~（崩崩崩k连保底嘛）~~
好好想一想，其实不难啦///（^o^）///
### code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 30
using namespace std;
int a[400]
int read()
{
	int ans=0;char ch=getchar(),last=' ';
	while(ch<'0'||ch>'9'){last=ch;ch=getchar();}
	while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
	if(last=='-') ans=-ans;
	return ans;
}
int main(int argc, char const *argv[])
{
    int n=read(),k=read(),c=read(),ans=0;
    for(int i=1;i<=c;i++){//对假期之间的处理
    	a[i]=read();
    	ans+=(a[i]-a[i-1]-1)/k+1;//-1很重要，端点是不算的（好好想一下）
    }
    ans+=(n-a[c])/k;
    //最后的假期之后也可能收礼啦，这个不-1哦，后端点算进去（再好好想一下）
    cout<<ans;
}
```

---

