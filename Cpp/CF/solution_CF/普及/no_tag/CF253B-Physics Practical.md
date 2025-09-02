# Physics Practical

## 题目描述

One day Vasya was on a physics practical, performing the task on measuring the capacitance. He followed the teacher's advice and did as much as $ n $ measurements, and recorded the results in the notebook. After that he was about to show the results to the teacher, but he remembered that at the last lesson, the teacher had made his friend Petya redo the experiment because the largest and the smallest results differed by more than two times. Vasya is lazy, and he does not want to redo the experiment. He wants to do the task and go home play computer games. So he decided to cheat: before Vasya shows the measurements to the teacher, he will erase some of them, so as to make the largest and the smallest results of the remaining measurements differ in no more than two times. In other words, if the remaining measurements have the smallest result $ x $ , and the largest result $ y $ , then the inequality $ y<=2·x $ must fulfill. Of course, to avoid the teacher's suspicion, Vasya wants to remove as few measurement results as possible from his notes.

Help Vasya, find what minimum number of measurement results he will have to erase from his notes so that the largest and the smallest of the remaining results of the measurements differed in no more than two times.

## 说明/提示

In the first sample you can remove the fourth and the sixth measurement results (values 8 and 7). Then the maximum of the remaining values will be 5, and the minimum one will be 3. Or else, you can remove the third and fifth results (both equal 3). After that the largest remaining result will be 8, and the smallest one will be 4.

## 样例 #1

### 输入

```
6
4 5 3 8 3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
4 3 2 4
```

### 输出

```
0
```

# 题解

## 作者：vanueber (赞：3)

[原题传送门](https://codeforces.com/problemset/problem/253/B)

# 题目大意

给定一个长度为 $n$ 的数列，求最少删除多少个数能满足其中任意的 $x$ 与 $y$，有 $y \le 2x$。

# 分析

首先考虑暴力枚举，时间复杂度 $\Theta(n^2)$，显然无法通过此题。如果我们先对这个数列进行排序，那么发现对于数列中的 $x$，我们只需要二分地找到满足条件的最大的 $y$（即找到大于 $2x$ 的最小的数），则因为有序性，中间的区间就是符合要求的，其他的就要删去，这样我们就只需枚举 $x$。时间复杂度：排序复杂度 $\Theta(n \log n)$，二分与枚举复杂度 $\Theta(n \log n)$，总复杂度 $\Theta(n \log n)$。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n,a[100005];
int ans=0x7fffffff;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//文件！
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		int* s=upper_bound(a+1,a+n+1,a[i]*2);
		ans=min(ans,(int)(a+i-s+n));
	}
	printf("%d",ans);
	return 0;
}
```
[AC记录](https://codeforces.com/problemset/submission/253/219031493)

---

## 作者：huangrenheluogu (赞：1)

显然，可以转化为保留最多的数量。

如果确定上下界 $l,r$，我们应该贪心地保留所有满足 $l\le a_i\le r$ 的 $a_i$。

**做法一：**

可以把 $a$ 排序之后枚举 $a_l$，找到最大的 $r$ 满足 $a_r\le 2a_l$，这个可以双指针完成，瓶颈是排序的 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, inf = 0x3f3f3f3f;
int n, a[N], ans;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    a[++n] = inf;
    for(int l = 1, r = 1; r < n; l++){
        while(r < n && a[r] <= a[l] * 2) r++;
        ans = max(ans, r - l);
    }
    printf("%d\n", n - ans - 1);
    return 0;
}
```

**做法二：**

考虑值域 $V$ 非常小，因此可以桶排序，记录 $a_i$ 表示值为 $i$ 的元素数量。

稍微预处理可以得到 $a$ 数组的前缀和，枚举保留数的上下界 $l,2l$，即可快速计算。

复杂度 $\mathcal{O}(n+V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, a[N], ans, x;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        a[x]++;
    }
    for(int i = 2; i <= 5000; i++){
        a[i] += a[i - 1];
    }
    for(int i = 1; i <= 2500; i++){
        ans = max(ans, a[i * 2] - a[i - 1]);
    }
    printf("%d\n", n - ans);
    return 0;
}
```

---

## 作者：zhjzhmh (赞：1)

考虑将数组排序，“因为对任意的 ${x,y}$，满足 $y \leq 2 \times x$”可以转化为“对于一个数列 $a$，$\max(a_i) \leq \min(a_i) \times 2$”。将删数转化为取排序后数组的一段连续区间，使得区间长度最长，因为排过序，所以区间左端点越靠右，则右端点越靠右，变为尺取法。详见代码。

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],l,r=1,mx;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//注意
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(l=1;l<=n;mx=max(mx,r-l),l++)
	  for(;r<=n;r++)
	    if(a[r]>a[l]*2) break;//l为左端点，r为右端点
	cout<<n-mx;
} 
```

---

## 作者：A524 (赞：1)

- 题目大意：
- 给你一个长度为 $n$ 的数组，问你在任取两个数 $x$ ， $y$ 都满足 $y \leq 2 \times x$ 的情况下，最少删去多少个数。

**前置知识**：[二分](https://oi-wiki.org/basic/binary/)或[尺取](https://zhuanlan.zhihu.com/p/101089139)(看一下思路就行）。

把题目给出序列的最小值记为 $min$ 。序列的最大值记为 $max$。在 $ max \leq min \times 2 $ 的情况下，题目给出的条件肯定是成立的。

因为在 $ max  \leq min \times 2 $：
1. 当 $max$ 变小时，式子也肯定成立。
1. 当 $min$ 变大时，式子也肯定成立。

所以，我们只需要判断 $ max \leq min \times 2 $就行。为了方便，我们先将数组进行从小到大的排序。因为只要比较最小值和最大值，所以我们肯定只删 $[1,l-1]$ 和 $[r+1,n]$ （ $1 \leq l \leq r \leq n$）。保留的部分是为$[l,r]$。为了使删除的最少，肯定是 $[l,r]$ 的长度尽量要长。所以我们可以用**尺取**或**二分**来处理。

我们在这里只讲述**尺取**的做法，**二分**的做法可以自己尝试打一下。

### 1. 尺取
尺取的思路大家都明白了（当做你们已经懂了思路）。

对于这题，我们先将数组给从小到大排序，我们记头指针为 $l$ ，尾指针为 $r$。然后尾指针从前往后移动。每一次，尾指针移动后，进行判断，如果不成立就让头指针往后移动，直至成立（判断$ max \leq min \times 2 $ ，头指针指向的值就是 $min$，尾指针指向的值是 $max$）。每一次，算出 $[l,r]$ 的区间长度，取一个最大值，最大长度记为 $Max$ 。最后输出 $n-Max$ 的值就行。

贴上程序：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,i,l,r,Max,a[100100];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); //注意：这题必须加，不然连第一个点都过不了。
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n); 	   //进行从小到大的排序。
   l=1;             //头指针初始化。
	for (r=1;r<=n;r++){   //尾指针从前往后移动。
		while (l<=r&&a[l]*2<a[r]) l++;  //当条件不成立时，头指针往后移动。
		if (r-l+1>Max) Max=r-l+1; //找出区间长度的最大值。
	}
	printf("%d\n",n-Max);  //算出需要删除的最小值。
	return 0;
} 

```

### 2. 二分
因为数组从小到大排了序，所以可以用二分。

排完序后，枚举 $l$ 从 $1$ 到 $n$ ，然后用二分找出此时 $r$ 的最大值，删去的数的数量就是 $(l-1)+(n-r)$ ，取一个最大值，最后输出。

代码大家可以自己尝试一下。

PS：翻译中的描述是任取两个数 $x$，$y$ ，而前面文章的内容却是最小值和最大值。但对做法并无影响。


---

## 作者：LouYiYang1 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF253B)
一眼二分，根据思考得出：我们只需要二分找到大于 2$x$ 的最小的数，又因为有序性，中间的区间就是符合要求的，其他的就要删去，这样我们就只需枚举 $x$。
# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100005];
int ans = 0x7fffffff;
int main() {
	cin>>n;
	for (int i = 1; i <= n; i++) cin>>a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		int* s = upper_bound(a + 1, a + n + 1, a[i] * 2);
		ans = min(ans, (int)(a + i - s + n));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：I_am_wjr_I_AK_IOI (赞：0)

# 题目大意：
题意：给一个长度为 $n$ 的序列，要求删除若干数后，使得剩下的序列中 **最大值** $\le2\times$ **最小值**，求删除多少个数，要求删除的个数最少。

## 思路：
 排序后后，从前向后暴力枚举，记录最小即可。

~~（配合代码使用更佳）~~

## Code:

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define int  long long
#define N 200000+5
#define AC return 0
using namespace std;
int a[N];
int n;
signed main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    L1:
    cin>>n;
    for (int i=1; i<=n; i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    int ans=INF;
    int cnt=1;
    for(int i=1;i<=n;i++){
        while(cnt<=n&&a[cnt]<=2*a[i])
            cnt++;
        ans=min(ans,i+n-cnt);
    }
    cout<<ans<<endl;//写个防抄袭，不过分吧！！！ 
    goto L1;
    AC;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

题意是最少删除的数量，且任意都满足，所以先排序一下，此时需要删除的数都在左边和右边，中间就是满足情况的。

之后对于每一个数都找到大于他两倍的数，此时可以取到这个数和大于他两倍的数的中间部分，外面就是答案，也就是左边 $i-1$ 和 右边 $n-r$ 的和，这里 $n-r$ 包括大于他两倍的数。

最后对每一个和取最小值就是答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,c[100010];
signed main()
{
   	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>c[i];	
	sort(c+1,c+n+1);
	if(c[1]*2>=c[n]) {cout<<0;return 0;}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++)//枚举每一个数
	{
		int l=i,r=n,mid;
		while(l<=r)//二分查找大于他的数的位置
		{
			mid=(l+r)/2;
			if(c[mid]>2*c[i]) r=mid-1;
			else              l=mid+1;
		}
		ans=min(ans,i-1+n-r);
	}
	cout<<ans;
	return 0;
```

---

## 作者：_int123_ (赞：0)

题目：

## Physics Practical

### 思路：

简单题。

我们只需先排序，再对每个数二分查找它两倍的数，算出答案再更新最小值即可，最后注意一下要用文件读写。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n;
int a[100005];
int ans=INT_MAX;//答案，设为最大值 
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	freopen("input.txt","r",stdin);//文件 
	freopen("output.txt","w",stdout);//文件 
	cin>>n;//输入 
	for(int i=1;i<=n;i++) cin>>a[i];//输入 
	sort(a+1,a+n+1);//排序 
	for(int i=1;i<=n;i++)
	{
		int s=upper_bound(a+1,a+n+1,a[i]*2)-a;//二分查找 
		ans=min(ans,n-s+i);//更新答案 
	}
	cout<<ans;//输出 
	return 0;
}
```

完结撒花！！！

---

## 作者：OIer_ACMer (赞：0)

~~这种题还要用什么高难度算法？？~~

------------
## 大致思路：
首先，题目要求是任意取两个数 $x$ 和 $y$，则一定要满足 $y \le 2\times x$，由于是小于等于，为了更方便暴力，我们就要先给这个数组从小到大排个序，为后面的暴力做准备。

之后，我们先从 $1$ 枚举到 $n$，将每个位置的数并从 $n$ 开始再次往后枚举，而再次枚举的下标变量定义为 $cnt$，之后的操作就很简单：只要此时 $a[cnt] \le 2 \times x$，则 $cnt$ 加一，往后枚举，枚举完后，再定义一个 $ans$ 变量记录要删除多少个数，所以 $ans=\min(ans, n - cnt + i)$，至于为什么要加 $i$ 是因为我们前面已经枚举了 $i$ 个数，不用再次加在这次枚举的答案里面了。


------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n;
int a[100009];
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    sort(a + 1, a + n + 1);
    int ans = INT_MAX;
    int cnt = 1;
    for (int i = 1; i <= n; i++)
    {
        while (cnt <= n && a[cnt] <= 2 * a[i])
        {
            cnt++;
        }
        ans = min(ans, i + n - cnt);
    }
    cout << ans;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122182544)

---

