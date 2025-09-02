# Maximum of Maximums of Minimums

## 题目描述

You are given an array $ a_{1},a_{2},...,a_{n} $ consisting of $ n $ integers, and an integer $ k $ . You have to split the array into exactly $ k $ non-empty subsegments. You'll then compute the minimum integer on each subsegment, and take the maximum integer over the $ k $ obtained minimums. What is the maximum possible integer you can get?

Definitions of subsegment and array splitting are given in notes.

## 说明/提示

A subsegment $ [l,r] $ ( $ l<=r $ ) of array $ a $ is the sequence $ a_{l},a_{l+1},...,a_{r} $ .

Splitting of array $ a $ of $ n $ elements into $ k $ subsegments $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , ..., $ [l_{k},r_{k}] $ ( $ l_{1}=1 $ , $ r_{k}=n $ , $ l_{i}=r_{i-1}+1 $ for all $ i>1 $ ) is $ k $ sequences $ (a_{l1},...,a_{r1}),...,(a_{lk},...,a_{rk}) $ .

In the first example you should split the array into subsegments $ [1,4] $ and $ [5,5] $ that results in sequences $ (1,2,3,4) $ and $ (5) $ . The minimums are $ min(1,2,3,4)=1 $ and $ min(5)=5 $ . The resulting maximum is $ max(1,5)=5 $ . It is obvious that you can't reach greater result.

In the second example the only option you have is to split the array into one subsegment $ [1,5] $ , that results in one sequence $ (-4,-5,-3,-2,-1) $ . The only minimum is $ min(-4,-5,-3,-2,-1)=-5 $ . The resulting maximum is $ -5 $ .

## 样例 #1

### 输入

```
5 2
1 2 3 4 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 1
-4 -5 -3 -2 -1
```

### 输出

```
-5
```

# 题解

## 作者：HD0X (赞：5)

### [传送门](https://www.luogu.com.cn/problem/CF870B)

# 题意
给出由 $n$ 个整数组成的数列和整数。你需要将这个数列分为正好 $k$ 个非空片段，然后计算每个片段中的最小数，最后得到这些最小数中的最大值。通过这些操作，你能得到的值最大是多少？
# 分析
我们分别考虑几种情况：

- $k=1$

一个片段只能选取最小数，在输出时排序再输出 $a[1]$ 就可以啦。

- $k>2$

我们可以把最大的单独划分开，像上面一样在输出时排序输出 $a[n]$ 就可以了。

- $k=2$

两个片段中，一个包含 $a[1]$，一个包含 $a[n]$。
我们只需要比较它们两个大小输出大的，因为：
想变大，则需在 $a[2]$ 到 $a[n-1]$ 中找到更大的，但更大不会被选上，所以不能更大。选更小的则变小了，什么用也木有。

# 代码

```c
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[100001];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(k==1)
	{
		sort(a+1,a+1+n);
		cout<<a[1];
	}
	else if(k>=3)
	{
		sort(a+1,a+1+n);
		cout<<a[n];
	}
	else
	{
		if(a[1]>=a[n])
		{
			cout<<a[1];
		}
		else
		{
			cout<<a[n];
		}
	}
	return 0;
}

```

---

## 作者：tanghg (赞：1)

### 题目大意：

- 有一段长度为 $n$ 的数组，让你把它分成 $k$ 组，注意，不需要原来的顺序，也不需要长度一样。
- 每一组都会有一个最小值，把它找出来，取所有的最大值。

### 思路：

这道题要分三种情况。

#### 当 $k=1$ 时：

我们可以对数组进行排序，取其中的最大值即可。

差不多长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/gt5fl8nf.png)

#### 当 $k=2$ 时：

这是最难的情况。

先说结论，输出 $\max(a[0],a[n-1])$ 即可。

为什么呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/drc41dny.png)

看这张图，根据我们的结论可以这样分。

我们知道，在黑框中比 $1$ 大的数字不会被挑出来，而小一点的数字还是比 $5$ 小，所以把五挑出来以后其他的放到一个框里面就行了。反过来也一样。

#### 当 $k\geq 3$ 时：

我们把最大的挑出来然后其他的随便分就行了，还算简单。

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const long long MAX=1e+5;
typedef long long ll;
ll n,a[MAX],k;
int main(){
    cin>>n>>k;
    for (int i = 0; i <n ; ++i) {
        cin>>a[i];
    }
    if(k==1){
        sort(a,a+n);
        cout<<a[0];
    }else if(k==2){
        cout<<max(a[0],a[n-1]);
    }else if(k>2){
        sort(a,a+n);
        cout<<a[n-1];
    }
    return 0;
}
```

---

## 作者：lu_run_ting (赞：1)

题意：

有一个长度为$n$序列，把它分成$k$组，求每组最小值，再求最大值


分析：   

我们采用贪心思想，先分类讨论：

- 当$k=1$时，只有一个区域，所以最小值就是整个序列的最小值，直接算一下就可以了。

- 当$k=2$时，有两个区域，一个带头，一个带尾，我们只需要在首尾两个元素中选最大值就可以了。为什么呢？我们举例带头的情况。
	- 当任何一个元素比它大的时候，选的是最小值，所以还是它，不用考虑比它大的数。
    - 当任何一个元素比它小的时候，就会选小的，那么就不是最大值了，所以不能选比它小的。   
    
 	结论就是，最终的最大可能就是首和尾，我们只能选首尾中大的一个，然后单独给它一个子序列，结果就是它。

- 当$k>=3$时，即有三个区域，可以把任何一个数单独分到一个组里，如果是两头，两个区间就可以，如果是中间，就用两头的两个区间把两边占满就可以了。所以要求最大值的话就十分简单了，只需要在所有的元素中选最大值就可以了，因为每个都可以选出来。

蒟蒻的辣鸡代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int n,k,a[N];
int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++) cin>>a[i];
	if(k==1) cout<<*min_element(a,a+n)<<endl;
	else if(k==2) cout<<max(a[0],a[n-1])<<endl;
	else cout<<*max_element(a,a+n)<<endl;
	return 0; 
} 
```
~~STL是个好东西~~

---

## 作者：WLR__jr (赞：1)

### 无意间发现了一道很~~难~~（水）的题，先发一波题解占个沙发（奆佬不要来D我啊！！！）

#### 直接放一波代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[11100000];
int main()
{
    int minn=1061109567,maxn=-1061109567;//千万不能定小，第一次就是跪在了999999999上
    int n,k;scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        minn=min(minn,a[i]);//记录最小值
        maxn=max(maxn,a[i]);//记录最大值
    }
    if(k==1)printf("%d\n",minn);//貌似1是找最小值
    else if(k>2)printf("%d\n",maxn);//输出最大值
    else if(k==2)printf("%d\n",max(a[1],a[n]));//找头尾中大的那个
    return 0;//完结撒花~~~
}

---

## 作者：Neilchenyinuo (赞：0)

## 题目大意

给出由 $n$ 个整数组成的数列和整数。你需要将这个数列分为正好 $k$ 个非空片段，然后计算每个片段中的最小数，最后得到这些最小数中的最大值。通过这些操作，你能得到的值最大是多少？

## Solution

- 我们分多种情况讨论：

1. 当 $k=1$ 时，

一个片段只能选取最小数，在输出时排序再输出 $a_1$ 就可以了。

2. 当 $k\ge3$ 时，

我们把最大的单独分开，向上面一样在输出时排序输出 $a_n$ 就可以了。

3. 当 $k=2$ 时，

我们就将 $a_1$ 和 $a_n$ 取最大值就结束了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[100005];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(k==1)
	{
		sort(a+1,a+1+n);
		cout<<a[1];
	}
	else if(k>=3)
	{
		sort(a+1,a+1+n);
		cout<<a[n];
	}
	else
		cout<<max(a[1],a[n]);
	return 0;
}
```


---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF870B)

# 思路

分情况讨论。

1. $k=1$ 时，也就是不用分割，此时即求原数组中最小值。

1. $k>2$ 时，考虑最优策略，我们将最大的数单独分成一组，这样那组最小的就是这个最大的数，这些最小值的最大值也即为这个最大的数，此时即求原数组中最大值。

1. $k=2$ 时，分成两组，此时只需比较 ${a}_{1}$ 和 ${a}_{n}$ 即可。

AC 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,k,a[N];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(k==2)
    {
        if(a[1]>=a[n])cout<<a[1]<<endl;
        else cout<<a[n]<<endl;
    }
    else
    {
        sort(a+1,a+n+1);
        if(k==1)cout<<a[1]<<endl;
        else cout<<a[n]<<endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/113267397)

---

## 作者：Firstly (赞：0)

## **题目思路：**

这是一道分类讨论问题。我们可以大致分为三种情况。

- 当 $k=1$，也就是只分为一份时，答案就是所有元素中的最小值，不需要将最小值再比较。

- 当 $k=2$ 时，因为序列是非空的，所以第一份必须包含第一个元素，第二份必须包含最后一个元素。那么第一份的最小值必定不大于首元素，第二份的最小值必定不大于最后一个元素，这样我们不妨把首尾较大值起来，其余元素全部归于另一部分，就可求出最优值。在此情况下，答案就是 $\max(a_1,a_n)$。

- 当 $k>2$ 时，因为首尾各自能分为一组，剩余的就不强求了。不妨将序列中最大值独自分为一组，其余的任意分即可。答案就是序列中的最大值。

## **Code：**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int N=1e5+5;
int maxn=-0x3f3f3f3f,minn=0x3f3f3f3f,n,k,a[N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(k==1){
	    for(int i=1;i<=n;i++)minn=min(minn,a[i]);
	    cout<<minn;
	}else if(k==2)cout<<max(a[1],a[n]);
	else{
	    for(int i=1;i<=n;i++)maxn=max(maxn,a[i]);
	    cout<<maxn;
	}return 0;
}
```


---

## 作者：user470883 (赞：0)

社供掉了，赶紧补补。（

## 思路：
贪心+分类讨论。

考虑到 $k$ 有多种情况，我们进行分类讨论。

1. 当 $k=1$ 时

这时，我们输出最小值。

2. 当 $k\geq2$ 时

这时，我们最大值即可。

3. 当 $k=2$ 时

最难的一个分类，我们需要再次分类进行思考。

* 如果任一元素比其大，则不变，因为时要求选最小值
* 如果任一元素比其小，则不能选比它要小的

综上，我们选择首尾两个数中的最大值即可。

代码就几个特判就好了。

## AC CODE:
```
# include <bits/stdc++.h>
 
using namespace std; 
 
main(){
	int n, k, Min = 1e9, Max = -1e9; 
	cin>>n>>k ;
	int a[n]; 
	for (int i = 0; i<n; i++){
		cin>>a[i];
		Min = min(Min, a[i]); 
		Max = max(Max, a[i]);
	}
	if (k == 1) cout<<Min; 
	else if (k >= 3 or a[0] == Max or a[n-1] == Max) cout<<Max<<endl; 
	else cout<<max(a[0], a[n-1])<<endl;
}
/*Things to check before submit:
1. did you forget long long ?
2. did you still CE?
3. = or == , n or m ,++ or -- , i or j , > or >= , < or <=
4. If contains "not", why not Reverse thinking or few affect?
5. is there anything extra to output?
6. keep it simple
7. can part of the code can with c++function replace?
8. smile while submit the code*/
```


---

