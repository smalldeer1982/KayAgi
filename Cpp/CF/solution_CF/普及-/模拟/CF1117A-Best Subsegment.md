# Best Subsegment

## 题目描述

You are given array $ a_1, a_2, \dots, a_n $ . Find the subsegment $ a_l, a_{l+1}, \dots, a_r $ ( $ 1 \le l \le r \le n $ ) with maximum arithmetic mean $ \frac{1}{r - l + 1}\sum\limits_{i=l}^{r}{a_i} $ (in floating-point numbers, i.e. without any rounding).

If there are many such subsegments find the longest one.

## 说明/提示

The subsegment $ [3, 4] $ is the longest among all subsegments with maximum arithmetic mean.

## 样例 #1

### 输入

```
5
6 1 6 6 0
```

### 输出

```
2
```

# 题解

## 作者：LB_tq (赞：4)

```
//在一个区间内最大的平均值一定是此区间中的最大值
//那么最长序列长度为连续最大值区间的长度
#include<iostream>
#include<cstdio>
using namespace std;
int n,ans,s;//s存储区间中的最大值
int a[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s=max(s,a[i]);
	}//读入时取最大值
	int t=0;
	for(int i=1;i<=n;i++){
		if(a[i]==s)
			t++;
		else
			t=0;
		ans=max(ans,t);//O（n）更新最长长度
	}
	cout<<ans;//输出答案
	return 0;
}
```


---

## 作者：ruruo (赞：1)

因为在一个区间内最大的平均值一定是此区间中的最大值，所以题目要求我们求的就是最长的连续最大值序列。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[100005] = {0}, maxx = -1, cnt = 0, ans = -1;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        maxx = max(maxx, a[i]);
    }
    for(int i = 1; i <= n; i++){
        if(a[i] == maxx){
            cnt++;
        }else{
            cnt = 0;
        }
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}
```



---

## 作者：Otue (赞：1)

## 题意
求平均值最大的区间。

## 思路
我们需要知道区间 $[l,r]$ 的平均值最大是多少，很显然，为整个数列的最大值。

则我们选择的区间只出现最大值即可，那么他的平均数就是最大的。

于是就转化为整个数列最多有几个连续最大值。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N], maxn, t;
int ans;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], maxn = max(maxn, a[i]);
	for (int i = 1; i <= n; i++) {
		if (a[i] == maxn) t++;
		else t = 0;
		ans = max(ans, t);
	}
	cout << ans;
}
```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 题目大意

求一个平均值最大的子段的最大长度。

## 题目分析

Q：平均值最大是多少？

A：很明显，就是整个数列中的最大值。

Q：为什么呢？

A：当最大值单独为一个子段，那么子段的平均值就是这个最大值，当然最大了。

-----

令 $s$ 为数列中最大值 即 $ s = \max_{i \le n} a_i $，

所以我们把问题转化成：最多有几个 $s$ 相连。

那么这问题也就迎刃而解！



## 代码


```
#include<bits/stdc++.h>
using namespace std;
int s=-1e9,t,a[100001],n,ans; //t为最大长度 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s=max(a[i],s); //求最大值 
	}
	for(int i=1;i<=n;i++) 
	{
		if(a[i]==s) t++; //判断是否为最大值，如果是长度+1
		else t=0; //否则清0
		ans=max(ans,t); 
	}
	cout<<ans; 
} 

```
还有一个 9行 ~~压行版~~  精简版

```
#include<bits/stdc++.h>
int s=-1e9,t,a[100001],n,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),s=max(a[i],s);
	for(int i=1;i<=n;i++) a[i]==s?t++,ans=max(ans,t):t=0;
	cout<<ans; 
} 
```

~~求过QWQ~~

---

## 作者：Fly_AFO (赞：0)

区间平均最大值显然即为最大值，那么我们只需要求哪一段最大值最多且连续即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxx=-9999999;
int a[100005];
int ans,summ;
//ans表示最长的最大值的区间长度 
//summ记录各段最大值的区间长度 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxx=max(maxx,a[i]);//最大值 
	}
	for(int i=1;i<=n;i++){
		if(a[i]==maxx)//如果仍然是最大值 
			summ++;//就加 
		else//否则 
			summ=0;//从0开始 
		ans=max(ans,summ);//不断刷新最大值区间长度 
	}
	cout<<ans;
}
```


---

## 作者：wbs200 (赞：0)

实际上，本题题意为：给出一个长度为 $n$ 的数组，你需要找到一个区间也就是子数组，在满足子数组内各元素的算术平均数（即所有元素之和除以元素个数）尽可能大的情况下使数组的长度尽可能长。数据范围是 $10^5$。

其实此题并不难，我们可以很轻松求出平均数，也就是这个数组中所有元素的最大值。于是这个问题就变成了寻找一个区间使这个区间所有数都等于最大值且这个区间长度最大。这个问题可以使用双指针算法来解决。我们遍历数组，当遇到最大值的时候使用另一个指针寻找该段最大值的数量，对答案不断进行最大值更新即可。

```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int a[N];

int main()
{
    int n;
    cin >> n;
    int maxn = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        maxn = max(maxn, a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == maxn)
        {
            int j = i + 1;
            while (j < n && a[j] == maxn) j++;
            ans = max(ans, j - i);
            i = j - 1;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：YYen (赞：0)

### 思路：数学+双指针实现
题目第一优先级为算数平均数尽可能大，那么就算最大的数只出现 $ 1 $ 次，也比次大的数出现 $ n - 1 $ 次优先级更高。因此做法就是统计最大的数的连续最大个数。
### 代码
```cpp
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int a[100005];

int main()
{
    int n, maxv = -1;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        maxv = max(maxv, a[i]);
    }
    int l = 1, ans = 1;
    while (l <= n)
    {
        if (a[l] == maxv)
        {
            int r = l + 1;
            while (r <= n && a[r] == maxv)
            {
                r++;
            }
            ans = max(ans, r - l);
            l = r + 1;
        }
        else
        {
            l++;
        }
    }
    cout << ans << endl;
    return 0; 
}
```


---

## 作者：xyf007 (赞：0)

# 根据题意模拟即可
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,a[100001]; 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int mx=-1,ans=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>mx)
		{
			mx=a[i];
			ans=1;
		}
		if(a[i]==mx)
		{
			if(a[i-1]==mx)
			{
				sum++;
			}
			else
			{
				sum=1;
			}
		}
		if(a[i]<mx)
		{
			sum=0;
			continue;
		}
		if(ans<sum)
		{
			ans=sum;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

