# Binary Inversions

## 题目描述

You are given a binary array $ ^{\dagger} $ of length $ n $ . You are allowed to perform one operation on it at most once. In an operation, you can choose any element and flip it: turn a $ 0 $ into a $ 1 $ or vice-versa.

What is the maximum number of inversions $ ^{\ddagger} $ the array can have after performing at most one operation?

 $ ^\dagger $ A binary array is an array that contains only zeroes and ones.

 $ ^\ddagger $ The number of inversions in an array is the number of pairs of indices $ i,j $ such that $ i<j $ and $ a_i > a_j $ .

## 说明/提示

For the first test case, the inversions are initially formed by the pairs of indices ( $ 1, 2 $ ), ( $ 1, 4 $ ), ( $ 3, 4 $ ), being a total of $ 3 $ , which already is the maximum possible.

For the second test case, the inversions are initially formed by the pairs of indices ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ), being a total of four. But, by flipping the first element, the array becomes $ {1, 1, 0, 0, 1, 0} $ , which has the inversions formed by the pairs of indices ( $ 1, 3 $ ), ( $ 1, 4 $ ), ( $ 1, 6 $ ), ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ) which total to $ 7 $ inversions which is the maximum possible.

## 样例 #1

### 输入

```
5
4
1 0 1 0
6
0 1 0 0 1 0
2
0 0
8
1 0 1 1 0 0 0 1
3
1 1 1```

### 输出

```
3
7
1
13
2```

# 题解

## 作者：litachloveyou (赞：5)

由于题目中只有 $0$ 和 $1$，那么我们可以使用前缀和快速算出前面有几个 $1$ 或者后面有几个 $0$。

于是可以先算出不修改时的逆序对数量，然后枚举每一个位置修改后的数量变化，留下最大值即可。

**注意**这个题是至多修改一次，也就是说可以不修改！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 10;
int a[N], b[N];
void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		b[i] = b[i - 1] + a[i];
	}
	ll cnt = 0, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i])
		{
			int sum = (n - i) - (b[n] - b[i]);
			cnt += sum;
		}
		else
		{
			int sum = b[i - 1];
			cnt += sum;
		}
	}
	cnt = cnt / 2;
	ans = cnt;
	for (int i = 1; i <= n; i++)
	{
		if (a[i])
		{
			int sum = (n - i) - (b[n] - b[i]);
			int mid = b[i - 1];
			ans = max(ans, cnt - sum + mid);
		}
		else
		{
			int sum = b[i - 1];
			int mid = (n - i) - (b[n] - b[i]);
			ans = max(ans, cnt - sum + mid);
		}
	}
	printf("%lld\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：BLX32M_10 (赞：4)

不难看出 $01$ 串中逆序对数为每个 $1$ 之后 $0$ 的个数之和。

题解区大佬用的都是前缀和，但是我一看到的时候想到的是贪心：越在后面增加的 $0$，与前面的 $1$ 形成逆序对越多，显然是单调的。并且越在前面增加 $1$，与后面的 $0$ 形成的逆序对越多，显然也是单调的。

得出结论，有三种情况：不变、改第一个 $0$ 或者改最后一个 $1$。三种情况每种都求一次逆序对数量，求最大值即可。

有人问：逆序对怎么求？

伪代码给出来

```python
int cnt = 0, ans = 0    cnt 累加当前的后方 0 的个数，ans 为答案
for i = n -> 1:    从后向前枚举方便累加
	if a[i] == 0:    累加后方 0 的个数
		cnt++
	else:    向前遇到 1 时向答案增加当前与后方所有 0 构成的逆序对数量
		ans += cnt
ans 即答案
```

AC 代码：

```cpp
#include <cstdio>
#define max(a, b) (a > b ? a : b)
#define int long long
int a[200005];
signed main()
{
	int t;
	scanf("%lld", &t);
	while (t--)
	{
		int n, l1 = 0, f0 = 0, cnt = 0, ans = 0, res = 0;
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%lld", &a[i]);
			if (a[i] == 1)
				l1 = i;
		}
		for (int i = 1; i <= n; i++)
			if (a[i] == 0)
			{
				f0 = i;
				break;
			}
		for (int i = n; i >= 1; i--)    //不变时逆序对数量。
		{
			if (a[i])
				ans += cnt;
			else
				cnt++;
		}
		res = max(res, ans);
		a[l1] = 0;    //更改最后一个 1。
		ans = 0, cnt = 0;
		for (int i = n; i >= 1; i--)
		{
			if (a[i])
				ans += cnt;
			else
				cnt++;
		}
		res = max(res, ans);
		a[l1] = 1;    //别忘了改回来。
		a[f0] = 1;    //更改第一个 0。
		ans = 0, cnt = 0;
		for (int i = n; i >= 1; i--)
		{
			if (a[i])
				ans += cnt;
			else
				cnt++;
		}
		res = max(res, ans);
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：_Remake_ (赞：2)

## 题目分析
给定一个 `01` 序列，求至多改变一个位置的值的情况下，序列内最多能存在多少个逆序对。
首先可以处理出原序列的逆序对个数，再对 `0` 和 `1` 做前缀和，之后从头扫描一遍，如果某个位置的值为 `0`，则改变这个位置可以使逆序对增加（该位置之后  `0` 的数量 $-$ 该位置之前 `1` 的数量），而当该位置为 `1` 时，改变这个位置增加的逆序对数是上面这个式子的结果的相反数。
枚举每个位置并求增加量的最大值，如果最大值小于 `0`，则输出原序列的答案，否则输出原序列的答案加上增加量的值。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
long long read()
{
    long long n=0,k=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m,T;
int A[200001];
int B[200001];
std::string S;
long long pres_0[200001];
long long pres_1[200001];
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int r=1;r<=n;r++)
		{
			A[r]=read();
			pres_0[r]=pres_0[r-1]+(A[r]==0);
			pres_1[r]=pres_1[r-1]+(A[r]==1);
		}
		long long Cnt=0;
		long long Ans=0;
		for(int r=n;r>=1;r--)
		{
			if(A[r]==0)
			{
				Cnt++;
			}
			else
			{
				Ans+=Cnt;
			}
		}
		long long det=0;
		for(int r=1;r<=n;r++)
		{
			if(A[r]==1)
			{
				det=std::max(det,pres_1[r-1]-(pres_0[n]-pres_0[r]));
			}
			else
			{
				det=std::max(det,(pres_0[n]-pres_0[r])-pres_1[r-1]);
			}
		}
		if(det>0)
		{
			Ans+=det;
		}
		printf("%lld\n",Ans);
	}
    return 0;
}

```


---

