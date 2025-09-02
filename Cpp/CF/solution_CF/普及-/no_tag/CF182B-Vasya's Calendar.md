# Vasya's Calendar

## 题目描述

Vasya lives in a strange world. The year has $ n $ months and the $ i $ -th month has $ a_{i} $ days. Vasya got a New Year present — the clock that shows not only the time, but also the date.

The clock's face can display any number from $ 1 $ to $ d $ . It is guaranteed that $ a_{i}<=d $ for all $ i $ from $ 1 $ to $ n $ . The clock does not keep information about the current month, so when a new day comes, it simply increases the current day number by one. The clock cannot display number $ d+1 $ , so after day number $ d $ it shows day $ 1 $ (the current day counter resets). The mechanism of the clock allows you to increase the day number by one manually. When you execute this operation, day $ d $ is also followed by day $ 1 $ .

Vasya begins each day checking the day number on the clock. If the day number on the clock does not match the actual day number in the current month, then Vasya manually increases it by one. Vasya is persistent and repeats this operation until the day number on the clock matches the actual number of the current day in the current month.

A year passed and Vasya wonders how many times he manually increased the day number by one, from the first day of the first month to the last day of the $ n $ -th month inclusive, considering that on the first day of the first month the clock display showed day $ 1 $ .

## 说明/提示

In the first sample the situation is like this:

- Day 1. Month 1. The clock shows $ 1 $ . Vasya changes nothing.
- Day 2. Month 1. The clock shows $ 2 $ . Vasya changes nothing.
- Day 1. Month 2. The clock shows $ 3 $ . Vasya manually increases the day number by $ 1 $ . After that the clock shows $ 4 $ . Vasya increases the day number by $ 1 $ manually. After that the clock shows $ 1 $ .
- Day 2. Month 2. The clock shows $ 2 $ . Vasya changes nothing.

 In total, Vasya manually changed the day number by $ 1 $ exactly $ 2 $ times.

## 样例 #1

### 输入

```
4
2
2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
3
3 4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
31
12
31 28 31 30 31 30 31 31 30 31 30 31
```

### 输出

```
7
```

# 题解

## 作者：zhangchengyan (赞：1)

$\texttt{Solution}$
### Step 0：题意简述
有一个记录日期的机器，它的日期上限为 $d$ ，即在第 $d+1$ 天它会重置为第 $1$ 天。

现在给出 $n$ 个月份和每个月份的天数 $a_i$ ，保证 $a_i \leq d$ 。

每天机器显示的日期都会加 $1$ ，如果当机器显示的日期和当前月份的日期不相同时，你就需要手动调整机器，每次可以让机器显示的日期加 $1$ （超过上限依然会重置）。

请求出你需要调整机器的次数。

### Step 1：解题思路
每次需要调整的次数是 $d-a_{i}$ ，用累加器 $ans$ 累加每一次的答案即可。

注意：
- 本题可以不使用数组，节省空间。
- 最后一天不需要调整机器。

### Step 2：代码呈现
```cpp
#include<bits/stdc++.h>
using namespace std;
int d,n,x,ans;
int main()
{
	cin>>d>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>x;//无需使用数组
		if(i!=n)//特判，最后一天不需要调整机器
		  ans+=d-x;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：幻想繁星 (赞：1)

# 思路

我们只需要将每个月缺少的天数补上，也就是要补上 $d-a_i$ 天。

但是有一个特殊情况，如果 $i=n$ 最后一天不需要调整机器，那就需要直接跳过。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a,sum;
int main()
{
	
    cin>>d>>n;
    for(int i=1;i<n;i++)//最后一个月不需要调整，少跑一次循环
    {
		cin>>a;
   		sum+=d-a;//计算每个月要调整的天数
    }
    cin>>a;//最后一个月不需要调整
    cout<<sum;
    return 0;
}
```


---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
有一个机器，它能记录日期，每过一天就会加一，如果它显示的日期超过了 $d$  那么它就会变回 $1$。现在让我们求出调整机器的最少次数。

### 题目分析：
我们需要将缺少的天数补上，也就是要补上 $d-a_i$ 天。
也就是每次将答案加上 $d-a_i$。

### 提示：
如果是 $i$ 等于 $n$ 的这一天，不需要做处理，在 `for` 循环里加一个判断就行。

### 具体代码：
```cpp
#include<iostream>
using namespace std;
int d, n, x, ans;
int main(){
	cin>>d>>n;
	for(int i=1;i<=n,i!=n;i++)cin>>x,ans+=d-x;
	//循环，第n天不用做处理
	//每次输入x
	//把少的天数补上 
	cout<<ans;
	//输出答案 
	return 0;
}
```

---

## 作者：Tear_stains (赞：0)

## 题意解释:
 
有一个计时机器，它的上限为 $d$ 天，即在第 $d+1$ 天它会重置 $1$ 。

给出 $n$ 个月和每月的天数 $a$ 。

机器每天都会加 $1$ ，当日期和本月的日期不同时，你要调整---每次可以让日期加 $1$ 

求需要调整机器的次数。

## 思路：

我们只需要把每个月少的天数补上即可
即 ```
ans+=(d-a)```
 天
 
 
特殊情况：第 $n$ 个月不需要调整直接忽略即可。

## 代码呈上

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,a,ans;
int main()
{
    cin>>d>>n;
    for(int i=1;i<n;i++)//只用跑n-1次，最后一个月不用调
    {
        cin>>a;
        ans+=(d-a);//记录天数，可负
    }
    cin>>a;//最后一个月不用更改
    cout<<ans;
    return 0;
}
```


---

## 作者：_lzy_ (赞：0)

## 题目大意：
有个机器，他每过一天显示的日期都会加一，如果它显示的日期超过了 $d$ 那么他就会变回 $1$。
然后现在要我们求出调整机器的最少次数。
## 思路：
我们就只需要将每个月缺少的天数补上，也就是要补上 $d-a_i$ 天。

但是有一个特殊情况，如果 $i=n$ 那就需要直接跳过。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,x;
int sum=0;
int main()
{
   scanf("%d\n%d",&d,&n);
   for(int i=1;i<n;i++){
   	scanf("%d",&x);	
   	sum+=d-x;
   }
   scanf("%d",&x);
   printf("%d",sum);
   return 0;
}
```


---

## 作者：S__X (赞：0)

### 思路：
有三种情况：
1. 当前月份的天数刚好等于机器的日期上限时，我们就不需要进行调整，机器会在下一天重置为 $1$。
2. 当前月份的天数小于于机器的日期上限时，我们就要进行手动调整，调整次数为 $d-a_i$。
3. 当前月份为最后一个月时，不需要进行调整。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int d,n,ans,a[1000005]; 
int main(){
	cin>>d>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=d&&i!=n) ans+=(d-a[i]);//分别表示第一种情况和第三种情况
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ninelife_Cat (赞：0)

### 题目大意：

有一个记录日期的机器，它的日期上限为 $d$，即在第 $d+1$ 天它会重置为第 $1$ 天。

现在给出 $n$ 个月份和每个月份的天数 $a_i$，保证 $a_i \leq d$。

每天机器显示的日期都会加 $1$，如果当机器显示的日期和当前月份的日期不相同时，你就需要手动调整机器，每次可以让机器显示的日期加 $1$（超过上限依然会重置）。

请求出你需要调整机器的次数。

### 思路：

首先如果当前月份的天数刚好等于机器的日期上限时，显然我们不需要调整机器。因为当这个月结束后，机器的日期会自动重置为 $1$。

否则我们就需要手动补上不足的那几天，保证在下一个月的第 $1$ 天机器的显示日期为 $1$。

注意最后一个月不用操作。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int d,ans,n,x; 
signed main()
{
	cin>>d>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(x!=d&&i!=n) ans+=d-x;//补上不足的天数
	}
	cout<<ans;
	return 0;
}

---

