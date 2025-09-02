# Farmer John's Challenge

## 题目描述

[Trade Winds - Patrick Deng](https://soundcloud.com/patrick-deng-392681004/trade-winds-ft-alex-zhu)

⠀



Let's call an array $ a $ sorted if $ a_1 \leq a_2 \leq \ldots \leq a_{n - 1} \leq a_{n} $ .

You are given two of Farmer John's favorite integers, $ n $ and $ k $ . He challenges you to find any array $ a_1, a_2, \ldots, a_{n} $ satisfying the following requirements:

- $ 1 \leq a_i \leq 10^9 $ for each $ 1 \leq i \leq n $ ;
- Out of the $ n $ total cyclic shifts of $ a $ , exactly $ k $ of them are sorted. $ ^\dagger $

If there is no such array $ a $ , output $ -1 $ .

 $ ^\dagger $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . If $ c_{x, i} $ denotes the $ i $ 'th element of the $ x $ 'th cyclic shift of $ a $ , exactly $ k $ such $ x $ should satisfy $ c_{x,1} \leq c_{x,2} \leq \ldots \leq c_{x, n - 1} \leq c_{x, n} $ .

For example, the cyclic shifts for $ a = [1, 2, 3, 3] $ are the following:

- $ x = 1 $ : $ [1, 2, 3, 3] $ (sorted);
- $ x = 2 $ : $ [2, 3, 3, 1] $ (not sorted);
- $ x = 3 $ : $ [3, 3, 1, 2] $ (not sorted);
- $ x = 4 $ : $ [3, 1, 2, 3] $ (not sorted).

## 说明/提示

In the first testcase, $ a = [1, 1] $ satisfies $ n = 2, k = 2 $ :

The two cyclic shifts of $ a $ are $ [a_1, a_2] $ and $ [a_2, a_1] $ , which are both $ [1, 1] $ and are sorted.

In the second testcase, $ a = [69\,420, 69, 420] $ satisfies $ n = 3, k = 1 $ :

The three cyclic shifts of $ a $ are $ [a_1, a_2, a_3] $ , $ [a_2, a_3, a_1] $ , $ [a_3, a_1, a_2] $ , which are $ [69\,420, 69, 420] $ , $ [69, 420, 69\,420] $ , and $ [420, 69\,420, 69] $ , respectively.

Only $ [69, 420, 69\,420] $ is sorted.

## 样例 #1

### 输入

```
3
2 2
3 1
3 2```

### 输出

```
1 1
69420 69 420
-1```

# 题解

## 作者：luobotianle (赞：3)

一道思维题。

看起来很复杂，但仔细想一下就可以发现，如果要将最后一位放在第一位后如果数组还有序，那么只能是数组里所有的数都相等。

所以答案就出来了：

- 如果 $k=1$，直接输出 $1$ 到 $n$；
- 如果 $k=n$，全部输出 $1$；
- 其他情况无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		if(k==1)for(int i=1;i<=n;i++)cout<<i<<" ";
		else if(k==n)for(int i=1;i<=n;i++)cout<<"1 ";
		else cout<<"-1";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：__Cyn__ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1942A)

一道思维题，看上去很懵，但懂了之后就是水题了。

举举例子，想一想，就会发现这题的数据可以分三类：
- $k=1$，输出一个长度为 $n$ 的升序数组即可。
- $k=n$，输出一个长度为 $n$ 且每个数都相同的数组即可。
- 否则无解，输出 $-1$。

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://www.luogu.com.cn/problem/CF1942A)
### 解题思路
这是一道思维题，我们分三种情况来讨论推理此题。
- $k=1$ 数组只有一次被排序。那么我们就需要构造一个严格递增的序列，从 $1$ 到 $n$ 最合适。
- $k=n$ 数组每一次循环移位都可以被排序。那么我们就需要构造一个全部相等的序列，随便输出一个数即可。
- $1 < k < n$ 不可能再有序列满足条件，因为如果一个数组被排过一次序，下一次循环移位后，最大值就被移到前面去了，那么就不可能被排序。
代码很简单，这里就不展示了。

---

## 作者：bjqxszx_liruixuan (赞：2)

## 题目大意
~~这个循环移位我看半天都没看懂。~~ 看他的样例解释我们可以知道，就是一组数据，每次把它的第一个数据放到结尾去，形成新的一种排列。所有的排列只有 $k$ 个有序排列。
## 思路
首先，如果 $k$ 是 $1$，就说明只有一种有序数列。那么就肯定没有相同的两个数，我们可以直接用从 $1$ 到 $n$ 这一组数据。
```
for(int i=1;i<=n;i++)
{
    cout<<i<<" ";
}
```
其次，如果 $k$ 就等于 $n$，那么就说明所有的排列都是有序的。那么就意味着所有的数都是相同的，我们可以用 $n$ 个 $1$ 这一组数据。
```
for(int i=1;i<=n;i++)
{
    cout<<"1"<<" ";
}
```
如果不是第一种也不是第二种，能发现，如果 $1 < k < n$ 时，就说明把最后一个数据放到开头还会有有序数列。也就是说明最后一个数据要小于等于第一个数据。那就只有数据全部相同这一种情况。可是，这样就会有 $n$ 组有序数列（同上），所以只能输出```-1```。
```
cout<<"-1";
```

---

## 作者：__XU__ (赞：2)

# CF1942A 题解

### 前言

一道比较简单的数学题。

### 做法：

看完题目后可以分为两种情况。

情况一：当数组内元素都相同时，此时就有 $n$ 个**已排序**数列，即 $k=n$。

情况二：当数组内有元素不相同，若该序列递增，此时有且仅有 $1$ 个，若不递增，那么他们将不可能组成**已排序**数列，因为数列中必存在 $a_{i-1}>a_i$，那么答案固然为 $-1$。

## AC code

```
#include<bits/stdc++.h>
using namespace std;
int t; 
int main(){
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		if(n==k){
			for(int i=1;i<=n;i++){
				cout<<n<<' ';
			}
			cout<<'\n';
			continue;
		}
		if(k==1){
			for(int i=1;i<=n;i++){
				cout<<i<<' ';
			}
			cout<<'\n';
			continue;
		}
		else{
			cout<<-1<<'\n';
			continue;
		}
	}
	return 0;
}
```

谢谢观看。

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1942A Farmer John's Challenge
## 思路
这是一道思维题，分为三种情况讨论即可。

- 如果 $k = 1$ 就说明只有一种有序数列，输出 $1$ 到 $n$ 即可。

- 如果 $k = n$ 数组每一次循环移位都可以被排序，说明所有的数都是相同的，随便输出即可。

- $k\ne 1,k\ne n$ 无解，输出 $-1$ 即可。
## 代码
代码就不给了，直接判断输出即可。

时间复杂度 $O(tn)$。

---

## 作者：bjqxszx_zhuzixuan (赞：1)

## 主要思路
一道思维题

主要分为以下两种情况 $k=n$ 和 $k=1$。

当 $k=n$ 时，数组内元素全部相等，全部有序，也就有 $n$ 个已排序数列，这时就可以直接输出 $n$ 个 $1$。

当 $k=1$ 时，数组中只有一个有序数列，可以直接输出 $1$ 到 $n$。

其余情况无法构成一个有序数列，所以输出 $-1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(k==1)
		{
		  for(int i=1;i<=n;i++)
		  cout<<i<<" ";
		}
		else if(k==n)
		{
		  for(int i=1;i<=n;i++)
		  cout<<"1 ";
		}    
		else 
		cout<<"-1";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：I_will_AKNOI (赞：0)

CF1942A 题解

容易想到，如果一个数组里面的数不完全相同，那么在题目中它一定只能满足 $k=1$ 的情况。因为如果有 $a_1<a_2$，在某次循环移位后一定会满足 $a_2$ 在 $a_1$ 前面，导致数组未排序，以此类推，只有初始的情况满足数组已排序，导致 $k=1$。但是如果数组所有数都相同，则无论如何循环移位，数组始终有序，$k=n$。由此得出结论：$k=n$ 或 $k=1$ 的情况有解，其余无解。

代码中 $k=n$ 的情况输出的数不仅可以是 $1$，也可以是任意数，只要满足题目要求即可。

代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        if(k==n)for(int i=1;i<=n;i++)cout<<"1 ";
        else if(k==1)for(int i=1;i<=n;i++)cout<<i<<' ';
        else cout<<-1;
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# CF1942A Farmer John's Challenge
## 题意概括
给定两个数 $n$ 和 $k$，找出满足在 $n$ 个循环移位中，正好有 $k$ 个被排序的长度为 $n$ 的数组。
## 思路分析
这道题看起来很复杂，所以我们需要分几种情况来讨论。
- $k=1$    
当 $k=1$ 时，只有一个循环移位被排序，为了简便，我们假设这一个被排序的循环移位是数组的第一个循环移位，即数组中的有序序列只有一个，因此输出输出 $1 \sim n+1$ 即可。 
- $k=n$    
当 $k=n$ 时，所有的循环移位都被排序，所以数组中的所有元素都相等，因此输出一个长度为 $n$ 的、所有元素都为 $1$ 的数组即可。
- $k \ne 1,k \ne n$    
此时问题无解，直接输出 $-1$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
    cin>>t;
    for (int x=0;x<t;x++){
        cin>>n>>k;
        if (k==1) {
            for (int i=1;i<=n;i++) cout<<i<<' ';
        }
        else if (k==n){
            for (int i=1;i<=n;i++) cout<<1<<' ';
        }
        else cout<<-1;
        cout<<'\n';
    }
    return 0;
}

```
7月8日更改了代码中的一些小问题，辛苦管理员再次审核，谢谢！

---

## 作者：天使宝贝 (赞：0)

一道~~简单的~~数学题。

### 思路&分析

可以将其分成三种情况看：

* 当 $k = 1$ 时，则说明数列中仅有 $1$ 个有序的数列，那直接输出 $1$ 到 $n$ 即可。

* 当 $k = n$ 时，则说明所有元素相等，因此输出 $n$ 个 $1$ 即可。

* 当以上两个条件都不满足时，说明无法构成有序的数列，因此输出 $-1$。

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
int T, n, k;
int main()
{
    IOS;  // 读入加速
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        if (k == 1)
        {
            for (int i = 1; i <= n; i++)
                cout << i << " ";
            cout << endl;
        }
        else if (k == n)
        {
            for (int i = 1; i <= n; i++)
                cout << "1 ";
            cout << endl;
        }
        else
            cout << -1 << endl;
    }
    return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题面意思

给出 $t$ 组数据，对于每一组数据，每一次将该数据的第一个数放到数据的末尾处，形成新的一组数据。重点：**只有 $k$ 个有序数列。**

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1942A)

一道思维题。

- 第一种情况，假如 $k$ 为 $1$，就代表只有一种有序数列，直接输出 $1$ 到 $n$ 所有的数字就行了。
- 第二种情况，$k$ 等于 $n$ 时，表示所有的都是有序的，这时我们可以全部都输出 $1$。
- 第三种情况，$1<k<n$ 时，此时无解，直接输出 $-1$。

参考代码：

```
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin>>t;
    while (t--) {
    	int n,k;
    	cin>>n>>k;
    	if (k==1) {for (int i=1;i<=n;i++) cout<<i<<" ";}
    	else if (k==n) {for (int i=1;i<=n;i++) cout<<"1 ";}
    	else cout<<"-1";
    	cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Alexxu2024 (赞：0)

# CF1942A 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1942A)

这道题我是先列一堆情况看是否有解，再从这些里面找规律。

发现 $n \le 5$ 的情况有：

$$n=1,k=1$$

$$n=2,k=1$$

$$n=2,k=2$$

$$n=3,k=1$$

$$n=3,k=3$$

$$n=4,k=1$$

$$n=4,k=4$$

$$n=5,k=1$$

$$n=5,k=5$$

诶，有解情况里怎么 $k$ 不是等于 $n$ 就是等于 $1$ 啊？

其实，我们可以这样分析：

- 如果 $n$ 个位移里面有 $n$ 个有序，那么必定数组内的数完全一样；
- 否则最多有 $1$ 个有序，即为不下降序列，数组内的数也不可能全一样。因此，在把最大的数移位到第一个后，该数组必定非有序。举个例子，把 $1\ 1\ 2\ 3$ 移位，发现把 $3$ 移到第一位后的数组无序，并且以后的移位都无序，只有当 $3$ 为最后一位（唯一的情况）时才有序。

所以只有 $k=n$ 或 $k=1$ 时才有解。

那么到底怎么构造呢？

- $k=n$ 时，输出 $n$ 个相同的数，比如 $1$；
- $k=1$ 时，升序输出 $1$ 到 $n$。

## 代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int a[110];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n,k;
		cin >> n >> k;
		if(k==1){
			for(int i=1;i<=n;i++){
				cout << i << " ";
			}
		}
		else if(k==n){
			while(n--){
				cout << 1 << " ";
			}
		}
		else{
			cout << -1;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：lym12 (赞：0)

不妨分类讨论 $k = 1$，$k = n \neq 1$ 和 $k \neq n$ 的情况。

1. 当 $k = 1$ 时，说明有且仅有一组排列有序，则原序列升序。
2. 当 $k = n \neq 1$ 时，说明所有排列有序，则原序列所有元素相同。
3. 当 $k \neq n$ 时，不难发现无解。

```cpp
// Problem: Farmer John's Challenge
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1942A
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin >> T;
	
	while (T --){
		int n, k;
		cin >> n >> k;
		
		if (k == 1) for (int i = 1; i <= n; i ++) cout << i << ' ';
		else if (k == n)  for (int i = 0; i < n; i ++) cout << "1 ";
		else cout << -1;
		puts("");
	}
}
```

---

## 作者：Fish_redflying (赞：0)

~~我不接受这个挑战~~

一道思维题。分情况讨论即可。

-----
结合第三组测试数据，我们可以发现，当 $a_i$ 全部相同时，不管如何循环位移，与原有序序列始终相等。

所以，循环位移 $n$ 次，就有 $n$ 个符合条件的数组。故当 $n=k$ ，输出一个所有元素相同数组的即可。

-----

通过打表可知，当只期望有**一个**元素与原有序序列相符，这个是可以实现的。

因为它本身就算**一个**，其他不管如何位移，必定有一组不有序。因为循环位移一次，就会把最后一项位移到第一项，导致 $a_1 > a_2$。这也证明了其他情况不符。

代码 ：
```python
for i in range(int(input())) :
	n,k=map(int,input().split())
	if n==k : print("1 "*n)
	elif k==1 : print(" ".join(list(map(str,[i for i in range(1,n+1)]))))
	else : print(-1)
```

---

