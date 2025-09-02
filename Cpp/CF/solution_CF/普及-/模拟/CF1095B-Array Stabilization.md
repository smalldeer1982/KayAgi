# Array Stabilization

## 题目描述

You are given an array $ a $ consisting of $ n $ integer numbers.

Let instability of the array be the following value: $ \max\limits_{i = 1}^{n} a_i - \min\limits_{i = 1}^{n} a_i $ .

You have to remove exactly one element from this array to minimize instability of the resulting $ (n-1) $ -elements array. Your task is to calculate the minimum possible instability.

## 说明/提示

In the first example you can remove $ 7 $ then instability of the remaining array will be $ 3 - 1 = 2 $ .

In the second example you can remove either $ 1 $ or $ 100000 $ then instability of the remaining array will be $ 100000 - 100000 = 0 $ and $ 1 - 1 = 0 $ correspondingly.

## 样例 #1

### 输入

```
4
1 3 3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 100000
```

### 输出

```
0
```

# 题解

## 作者：红黑树 (赞：5)

## 题意
给定一个序列，删除一个元素使得最大值减最小值最小。
## 做法
我们只需要求最大、次大、最小和次小，然后输出 最大 - 次小 与 次大 - 次小 中小的一个就行了
## 代码
```cpp
#include <algorithm>
#include <iostream>

using namespace std;
constexpr int Hat_N = 100003;

int val[Hat_N];

signed main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }
  stable_sort(val + 1, val + n + 1);
  cout << min(val[n - 1] - val[1], val[n] - val[2]);
  return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$，现在需要从这些数中删除一个数，使得 $\max\limits_{i=1}^na_i-\min\limits_{i=1}^na_i$ 的值最小。

**数据范围：$2\leqslant n\leqslant 10^5,1\leqslant a_i\leqslant 10^5$。**
## Solution
先给这些数排个序，设最大数为 $a_{\max}$，第二大数为 $a'_{\max}$，第二小数为 $a'_{\min}$，最小数为 $a_{\min}$。那么由于只能够删一个数，答案就是 $\max\{a'_{\max}-a_{\min},a_{\max}-a'_{\min}\}$。
## Code
```cpp
int n, a[100007];

int main() {
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	sort(a + 1, a + n + 1);
	int ans = min(a[n] - a[2], a[n - 1] - a[1]);
	writeint(ans);
	return 0;
}
```

---

## 作者：wuwenjiong (赞：0)

# 题意：
一个数列，求删去一个数后，数列中最大值与最小值的差最小。

根据题意，我们考虑贪心，不难想到，只需要取最大值减次小值和次大值减最小值的较小值输出就行了。

数据范围： $2\le n\le 10^5$ ，我们就可以用`sort`，不会超时。

代码如下：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100002];
int main(){
	ios::sync_with_stdio(0);
   cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	cout<<min(a[n-1]-a[1],a[n]-a[2]);
	return 0;
}
```
谢谢！！！

---

## 作者：FP·荷兰猪 (赞：0)

题意：有n个数，求删除一个数后剩下数中的最大数减最小数最小是多少。

核心思想：先将原数组sort排序一遍，在比较a[n]-a[2]和a[n-1]-a[1]谁更小，输出更小的那个。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    cin>>n;
    int a[n+1],i;
    for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
    sort(a+1,a+n+1);
    int ans;
    ans=min(a[n]-a[2],a[n-1]-a[1]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：vocaloid (赞：0)

贪心，由于对答案有影响的只有最大值或最小值，所以我们分别删去最大值最小值后计算答案，删去最大值时为次大值$-$最小值，删去最小值是为最大值$-$次小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	printf("%d\n",min(a[n]-a[2],a[n-1]-a[1]));
}
```

---

## 作者：Zechariah (赞：0)

既然要去掉一个元素，贪心的想，我们肯定是去掉最大或者最小的  
所以答案是min(最大-第二小,第二大-最小)，为了偷懒我们sort一下比较输出就行了
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 10, mod = 998244353, oo = 0x3F3F3F3F3F3F3Fll;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N];

int main()
{
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
    sort(a + 1, a + n + 1);
    fast_IO::write(fast_IO::min(a[n] - a[2], a[n - 1] - a[1]));
    return 0;
}

```

---

## 作者：Thomas_Cat (赞：0)

这题思路如下：

- 特判，如果 $n$ 是 $2$ ，最后答案是 $0$ （可以自己去找下规律）
- 接下来，去掉最大的数和最小的数，看看哪个最小，输出即可

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using
int main(){
    int n,a[100001];//这里定义数组
    cin>>n;//输入
    for(int i=1;i<=n;i++) cin>>a[i];//循环输入
    if(n==2){//特判，如果n是2
        cout<<0;//输出0
        return 0;//直接退出
    }
    sort(a+1,a+n+1);//快排
    cout<<min(a[n-1]-a[1],a[n]-a[2]);//看到最小值然后找到最小值即可
    return 0;    //华丽结束
}
```

---

## 作者：YuanZhizheng (赞：0)

这题求数组“稳定性”，也就是数组中最大值与最小值之差。题目让你删去一个元素，使得删去后最大值与最小值之差达到最小。

“稳定性”只和最大最小值有关，所以我们删除其中一个即可。

我们对数组排个序。假设数组下标是从1到n的。

那么，a[n]-a[2]就是删去最小值，a[n-1]-a[1]就是删去最大值。

有关排序的算法有很多，感兴趣的可以食用下面的链接。

[常见排序方法](https://www.luogu.com.cn/blog/YoungZz/chang-jian-pai-xu-fang-fa)

在此我采用的是归并排序。

AC代码：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200005];
vector<int>ve;
void Sort(int l,int r)//归并排序操作
{
    if(l==r)return ;
    int mid=(l+r)>>1;
    Sort(l,mid);
    Sort(mid+1,r);
    int i=l,j=mid+1;
    ve.clear();
    while(i<=mid&&j<=r)
    {
        if(a[i]<a[j])
            ve.push_back(a[i++]);
        else ve.push_back(a[j++]);
    }
    while(i<=mid)
        ve.push_back(a[i++]);
    while(j<=r)
        ve.push_back(a[j++]);
    for(int len=ve.size(),i=l,j=0;j<len;i++,j++)
        a[i]=ve[j];
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    if(n==2)cout<<0;
    else
    {
        Sort(1,n);
        printf("%d",min(a[n]-a[2],a[n-1]-a[1]));
    }
    return 0;
}
```
感谢观看！


---

