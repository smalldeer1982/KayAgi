# Little Elephant and Sorting

## 题目描述

The Little Elephant loves sortings.

He has an array $ a $ consisting of $ n $ integers. Let's number the array elements from 1 to $ n $ , then the $ i $ -th element will be denoted as $ a_{i} $ . The Little Elephant can make one move to choose an arbitrary pair of integers $ l $ and $ r $ $ (1<=l<=r<=n) $ and increase $ a_{i} $ by $ 1 $ for all $ i $ such that $ l<=i<=r $ .

Help the Little Elephant find the minimum number of moves he needs to convert array $ a $ to an arbitrary array sorted in the non-decreasing order. Array $ a $ , consisting of $ n $ elements, is sorted in the non-decreasing order if for any $ i $ $ (1<=i&lt;n) $ $ a_{i}<=a_{i+1} $ holds.

## 说明/提示

In the first sample the array is already sorted in the non-decreasing order, so the answer is $ 0 $ .

In the second sample you need to perform two operations: first increase numbers from second to third (after that the array will be: \[3, 3, 2\]), and second increase only the last element (the array will be: \[3, 3, 3\]).

In the third sample you should make at least 6 steps. The possible sequence of the operations is: (2; 3), (2; 3), (2; 3), (3; 3), (3; 3), (3; 3). After that the array converts to \[7, 7, 7, 47\].

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
3 2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
7 4 1 47
```

### 输出

```
6
```

# 题解

## 作者：_byta (赞：3)

题目大意：

给定一个长度为 $n$ 的数组，每次可以任选 $l$ 和 $r$ ，将 $l$ ， $r$ 区间每个数

加一。问最少操作几次才能使序列变为不降序。

题解：

显然对于连续两个数 $x$ 和 $y$ ， $x$ 在前 ， $y$ 在后， 只有 $x$ 大于 $y$ ，我们

才进行操作，操作次数为 $x$ 和 $y$ 的差值。因此我们从前往后扫描整个序列，

对每个满足上述要求的数进行操作。将差值累加即为答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,p,q,ans,sum,tot,cnt,a[100002];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		if(a[i]>a[i+1])
		{
			ans+=a[i]-a[i+1];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：DLDZD (赞：1)

我也不知道怎么，莫名其妙就 AC 了。
### 题意：
给你 $n$ 个数，定义一次操作：任选一个区间 $+1$ ，目的是让后一个数不能小于前一个数（不下降子序列），然后最小操作数是多少？
### 思路：
看样例：
“3 1 2 3” 与 “3 3 2 1”可以发现只要 $a_i$ 小于 $a_{i-1}$ 累加器就加他们的差（后面样例可以用来证明）。

## 可得代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[100001];
long long ans; 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入n个数
	}
	for(int i=2;i<=n;i++){//从2开始不然越界
		if(a[i]<a[i-1]){
			ans+=a[i-1]-a[i];//加上
		}
	}
	cout<<ans<<"\n";//"\n"可以在双引号中
	return 0;
}
```



---

## 作者：codemap (赞：1)

一道水题

思路:

若一个数比前一个数小,计数器就加上它们两个的差

然后就做完了(~~是不是很简单~~)

注意要开long long

上代码
```cpp
#include<iostream>
using namespace std;
long long a[100001];
int main()
{
    long long n,i,s=0;
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i];
    for(i=2;i<=n;i++)
        if(a[i]<a[i-1])//如果比前一个小
            s+=a[i-1]-a[i];//加上两数之差
    cout<<s;//输出
    return 0;//完美结束
}
```
# 请勿抄袭

---

## 作者：违规用户名gAGt8$%z (赞：0)

**这是一道很简单的暴力枚举**

### 思路

枚举每两个数，若一个数比前一个数小,计数器就加上它们两个的差即可。

Tip : 十年 OI 一场空 ， 不开 LongLong 见祖宗 !

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans,a[100005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n-1;i++)
        if(a[i]>a[i+1]) ans+=a[i]-a[i+1];
    cout<<ans;
    return 0;
}
```




---

## 作者：rai1gun (赞：0)

### 1.题目思路

暴力查找一遍 $a$ 数组，寻找 $a_i > a_{i+1} $ 的情况，此时，要满足不降序列的要求，必须将 $a_{i+1}$ 后面的所有数加上 $a_i-a_{i+1}+1$ ，这样才能满足不降序列且差值不变。保证此方法为最优解。

### 2.题目代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+5; 
int n,ans,a[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n-1;i++)
        if(a[i]>a[i+1])
            ans+=a[i]-a[i+1];
    cout<<ans;
    return 0;
}
```

---

## 作者：Dream_weavers (赞：0)

## 题意

给出一个长度为 $n$ 的数组 $a$，并定义一次操作为：任选从 $l$ 到 $r$ 的一个区间，让区间内（也就是 $a_l$ 到 $a_r$）的每一个数 $+1$。问**最少**几次操作能让后一个数（$a_i$）不小于前一个数（$a_{i-1}$）。

## 思路

我们把数组 $a$ 从前往后扫描一遍。若 $a_{i-1} < a_i$，只需让累加器加上前后两项的差（$ a_{i-1} - a_i$）即可。因为当 $a_i$ 进行多次“$+1$”后，$a_i$ 后面的数都要进行相同次数的“$+1$”，而后面的数任意前后两项的差都不会发生改变，也就是“**同增同减差不变原理**”。

## $AC\ Code$

### 注意

- $a_i$ 最大为 $10^9$，用 int 容易存不下，所以要开 long long。

- 扫描数组应该从第二个数开始

```cpp
#include<iostream>
#define int long long//不开long long见祖宗
using namespace std;
int n,a[100005],ans=0; 
signed main(){
    cin>>n;//输入n
    for(int i=1;i<=n;i++)cin>>a[i];//输入数组
    for(int i=2;i<=n;i++)//从第二个数开始
        if(a[i]<a[i-1])//判断是否小于前一个数
            ans=ans+a[i-1]-a[i];//是则累加两个数的差
    cout<<ans;
    return 0;
}

```


---

## 作者：BlackPanda (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF205B)

------------
### 题意：
给定 $n$ 个数，每次任选一个区间，将区间内的每个数 $+1$，问最少操作几次才能使得原序列变成一个不下降子序列？

------------
### 思路：
不下降子序列就是序列中后一个数不能小于前一个数。

可以从前往后遍历整个序列，如果前一个数大于后一个数，则操作次数就是**两个数的差值**。最后把所有操作次数累加就能得出答案。

------------
### 注意：
这道题一定开 long long！否则就会[错误](https://www.luogu.com.cn/record/68084663)。

------------
### code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long a[100005],cnt; 
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++)	cin>>a[i];
	for(long long i=1;i<n;i++){
		if(a[i]>a[i+1])
			cnt+=a[i]-a[i+1];
	}
	cout<<cnt<<endl;
	return 0;
}


```



---

## 作者：3a51_ (赞：0)

### 题目大意

给定一个数组 $a$，每次任选一个区间加 $1$。求最少几次才能把原数组 $a$ 变成不降序列。

### 思路分析

搜索一遍 $a$ 数组，如果我们发现 $a_i>a_{i+1}$，那么，我们有必要将 $a_i$ 及其后面的元素都加 $1$。因为我们不知道后面的元素都是啥，所以我们需要将他们都加 $1$，保证他们的差值不变。所以答案就需要加上 $a_i-a_{i-1}$。最后我们输出答案就行。


**注意一定要开```long long```！**

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,a[100002];
int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	for(long long i=1;i<=n-1;i++)
		if(a[i]>a[i+1])
			ans+=a[i]-a[i+1];
	cout<<ans;
	return 0;
}
```
ps:洛谷有点慢，在[CF上A了](https://codeforces.com/contest/205/submission/144112212)。

---

## 作者：_easy_ (赞：0)

# 思路
通过读题可以发现：输出的答案一定是每项小于等于他的前一项时他们的差值之和。证明如下：

当我们遇到 $a_{i-1}>a_i>a_{i+1}\le a_{i+2}$ 时，很明显如果将 $a_i$ 和 $a_{i+1}$ 一起加上 $a_i-a_{i-1}$，可能会导致 $a_{i+1}>a_{i+2}$。为了避免这种情况，我们就只能考虑单独给 $a_i$ 加上 $a_i-a_{i-1}$。于是得出最优方案：每次遇到不符合不下降子序列时就将答案加上两项之差就行了。
# 代码
挺好写的，这里就不放出来了。

**注意**：要开 $\texttt{long long}$

---

