# Boring Partition

## 题目描述

你可以把 $n$ 个元素划分到两个序列里。

对于任意两个的元素 $a_i$ 和 $a_j$（$i \ne j$），如果它们在一个序列中，$f(i, \ j) = a_i + a_j$，如果它们在不同序列中，$f(i, \ j) = a_i + a_j + h$，其中 $h$ 是一个给定的参数。

一种划分方式的优美度定义为最大的 $f(i, \ j)$ 与最小的 $f(i, \ j)$ 的差值。

求优美度最小的方案。

## 样例 #1

### 输入

```
3 2
1 2 3
```

### 输出

```
1
1 2 2 
```

## 样例 #2

### 输入

```
5 10
0 1 0 2 1
```

### 输出

```
3
2 2 2 2 2 
```

# 题解

## 作者：是个汉子 (赞：3)

### Solution

想要得到差最大，只能是最小的自己一组或者全部在一组，因为：如果拿另一个和最小的一组，最小值只有可能最小，最大值只有可能更大，反证完毕。

那么我们可以将 $a$ 数组从小到大排序，那么现在 $a_1$ 是 $\min a$ ， $a_n$ 是 $\max a$ ，当全部在一组时， $ans=f(a_n,a_{n-1})-f(a_1,a_2)=a_n+a_{n-1}-a_1-a_2$ ，但是当 $a_1$ 自己一组时， $ans=\max(a_n+a_{n-1},a_n+a_1+h)-\min(a_1+a_2+h,a_2+a_3)$ 。

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int n,h;
struct node{
    int x,id;
    int val;
}a[N];

bool cmp1(node x,node y){
	return x.x<y.x;
} 

bool cmp2(node x,node y){
    return x.id<y.id;
}

int main(){
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].x),a[i].id=i,a[i].val=0;
    sort(a+1,a+n+1,cmp1);
    if(n==2) printf("0\n1 1\n");
    else{
        if(max(a[n].x+a[n-1].x,a[1].x+a[n].x+h)-min(a[1].x+a[2].x+h,a[2].x+a[3].x)<a[n].x+a[n-1].x-a[1].x-a[2].x) a[1].val=1;
        cout<<min(max(a[n].x+a[n-1].x,a[1].x+a[n].x+h)-min(a[1].x+a[2].x+h,a[2].x+a[3].x),a[n].x+a[n-1].x-a[1].x-a[2].x)<<endl;
        sort(a+1,a+n+1,cmp2);
        for(int i=1;i<=n;i++)
            printf("%d%c",a[i].val==0?2:1," \n"[i==n]);
    }
    return 0;
}
```



---

## 作者：AC_love (赞：1)

构造题。

首先我们考虑最大的 $f(i, \ j)$ 和最小的 $f(i, \ j)$ 是怎么产生的。

显然最大的 $f(i, \ j)$ 有两种可能：序列 1 的最大值 + 序列 2 的最大值 + $h$ 或一个序列里的最大值 + 次大值。

最小的 $f(i, \ j)$ 也是类似的两种可能：序列 1 的最小值 + 序列 2 的最小值 + $h$ 或一个序列里的最小值 + 次小值。

我们希望这两个的差尽可能小，其实就是希望最大值尽可能小，最小值尽可能大。

我们发现最大的 $f$ 一定严格大于等于最大值 + 次大值，最小的 $f$ 也一定严格小于等于最小值 + 次小值 + $h$。

我们我们就让最大的 $f$ 等于最大值 + 次大值，最小的 $f$ 等于最小值 + 次小值 + $h$ 即可。

显然构造方法是：把最大值和次大值分到一起，把最小值和次小值分开。

此时我们发现可以把最小值单独拿出来分一组，其他全放在一起，这时一定能满足上面的分法。

但是我们必须考虑一种特殊情况：当 $h$ 很大的时候，最小值 + 次小值 + $h$ 可能比最大值 + 次大值还要大，这时我们就未必需要把最小值单独拿出来了，我们可以把所有值都放一起（比如样例二）。

因此我们对两种情况分别讨论即可。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 114514;
int n, h;
struct num
{
	int val;
	int id;
};

num a[N];

bool cmpv(num i, num j)
{
	return i.val < j.val;
}

bool cmpid(num i, num j)
{
	return i.id < j.id;
}

bool f;
int ans;

signed main() 
{
	cin >> n >> h;
	for(int i = 1; i <= n; i = i + 1)
		cin >> a[i].val,
		a[i].id = i;
	sort(a + 1, a + 1 + n, cmpv);
	int maxn1 = max(a[1].val + a[n].val + h, a[n].val + a[n - 1].val);
	int minn1 = min(a[1].val + a[2].val + h, a[2].val + a[3].val);
	int maxn2 = a[n].val + a[n - 1].val;
	int minn2 = a[1].val + a[2].val;
	if(maxn1 - minn1 > maxn2 - minn2)
		f = 1,
		ans = maxn2 - minn2;
	else
		a[1].val = -1,
		ans = maxn1 - minn1;
	cout << ans << "\n";
	sort(a + 1, a + 1 + n, cmpid);
	for(int i = 1; i <= n; i = i + 1)
	{
		char c = (f == 0 && a[i].val == -1) ? '1' : '2';
		putchar(c);
		putchar(' ');
	}
	return 0;
}
```

---

