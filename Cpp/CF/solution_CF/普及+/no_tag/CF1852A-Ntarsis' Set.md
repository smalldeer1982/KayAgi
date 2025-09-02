# Ntarsis' Set

## 题目描述

Ntarsis has been given a set $ S $ , initially containing integers $ 1, 2, 3, \ldots, 10^{1000} $ in sorted order. Every day, he will remove the $ a_1 $ -th, $ a_2 $ -th, $ \ldots $ , $ a_n $ -th smallest numbers in $ S $ simultaneously.

What is the smallest element in $ S $ after $ k $ days?

## 说明/提示

For the first test case, each day the $ 1 $ -st, $ 2 $ -nd, $ 4 $ -th, $ 5 $ -th, and $ 6 $ -th smallest elements need to be removed from $ S $ . So after the first day, $ S $ will become $ \require{cancel} $ $ \{\cancel 1, \cancel 2, 3, \cancel 4, \cancel 5, \cancel 6, 7, 8, 9, \ldots\} = \{3, 7, 8, 9, \ldots\} $ . The smallest element is $ 3 $ .

For the second case, each day the $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, $ 6 $ -th and $ 7 $ -th smallest elements need to be removed from $ S $ . $ S $ will be changed as follows:

 Day $ S $ before $ S $ after1 $ \{\cancel 1, 2, \cancel 3, 4, \cancel 5, \cancel 6, \cancel 7, 8, 9, 10, \ldots \} $  $ \to $  $ \{2, 4, 8, 9, 10, \ldots\} $ 2 $ \{\cancel 2, 4, \cancel 8, 9, \cancel{10}, \cancel{11}, \cancel{12}, 13, 14, 15, \ldots\} $  $ \to $  $ \{4, 9, 13, 14, 15, \ldots\} $ 3 $ \{\cancel 4, 9, \cancel{13}, 14, \cancel{15}, \cancel{16}, \cancel{17}, 18, 19, 20, \ldots\} $  $ \to $  $ \{9, 14, 18, 19, 20, \ldots\} $ The smallest element left after $ k = 3 $ days is $ 9 $ .

## 样例 #1

### 输入

```
7
5 1
1 2 4 5 6
5 3
1 3 5 6 7
4 1000
2 3 4 5
9 1434
1 4 7 9 12 15 17 18 20
10 4
1 3 5 7 9 11 13 15 17 19
10 6
1 4 7 10 13 16 19 22 25 28
10 150000
1 3 4 5 10 11 12 13 14 15```

### 输出

```
3
9
1
12874
16
18
1499986```

# 题解

## 作者：Kedit2007 (赞：30)

## CF1852A Ntarsis' Set 题解

首先，不妨根据题意模拟一下操作过程，这里以样例中第二个测试点为例。

最开始，集合元素为 $[1, 2, 3, 4, 5, 6, 7, ...]$，执行一次操作后，$1, 3, 5, 6, 7$ 被删除，集合元素变为 $[2, 4, 8, 9, 10, 11, 12, ...]$。

继续删除操作，$2, 8, 10, 11, 12$ 被删除，集合变为 $[4, 9, 13, 14, 15, 16, 17, ...]$。继续执行最后一次删除操作，$4, 13, 15, 16, 17$ 被删除，集合变为 $[9, 14, 18, ...]$。此时集合的第一个元素为 $9$，得到答案。

容易发现，当操作数组 $a$ 以 $1$ 开头时，每一次操作后，没有被删掉的数都会向前移，同时，越靠前的数可能被移动的距离越短。

---

不妨假设我们已经知道了答案，现在关注答案在集合中位置的变化。

仍然以第二个测试点为例。我们已经知道了答案是 $9$。在操作过程中，第一次操作后，所有被删掉的数都在 $9$ 的前面，所以 $9$ 被向前移动了 $5$ 个位置，此时 $9$ 变为了第 $4$ 个数。第二次操作后，只有 $2$ 个被删掉的数在 $9$ 前面，所以 $9$ 被向前移动了 $2$ 个位置，此时 $9$ 变为了第 $2$ 个数。最后一次操作后，只有一个被删掉的数在 $9$ 前面，所以 $9$ 被向前移动一个位置，成为第 $1$ 个数。

我们发现，在执行一次操作时，如果给定一个数原来的位置，推出操作后的位置是很简单的，而如果给定一个数操作后的位置，推出操作前的位置同样是简单的。而我们一开始无法得知答案最初的位置，但可以确定答案最后一定在第一位，所以考虑从最后一步开始倒推。

---

仍以第二个测试点为例，将答案记为 $ans$，则最后的集合应为 $[ans, ...]$。这时我们开始倒推最后一次操作前的集合，由于我们只关注 $ans$，所以如果操作后被删掉的数原先在它后面，我们可以在倒推时将其忽略。

倒推过程可以这样进行：记录 $ans$ 目前所在的位置，**按顺序**遍历操作数组，如果遍历到的元素**小于等于**目前 $ans$ 所在的位置，则代表操作前该位置有数被删除，且在 $ans$ 前，这时便将 $ans$ 的位置向后移动。

倒推最后一次操作时，操作数组为 $[1, 3, 5, 6, 7]$，$ans$ 的位置为 $1$。遍历操作数组，操作数组中第一个元素 $1 = 1$，所以将 $ans$ 的位置向后移动，变为 $2$。继续遍历，发现操作数组中第二个元素 $3 > 2$，已经不能继续将 $ans$ 往后移动，而操作数组是又递增的，所以可以在此处结束遍历。

倒推倒数第二次操作时，$ans$ 的位置为 $2$。遍历操作数组，操作数组中第一个元素为 $1 < 2$，将 $ans$ 位置后移至 $3$。继续遍历，操作数组中第二个元素为 $3 = 3$，将 $ans$ 位置后移至 $4$。继续遍历，操作数组中第三个元素为 $5 > 4$，结束遍历。

倒推倒数第三次操作的方法相同，最后 $ans$ 的位置变为 $9$，即为该测试点的答案。

注意到 $ans$ 的位置在倒推过程中只会不断后移，所以若在上一次倒推过程中操作数组的第 $i$ 个元素能够将 $ans$ 的位置后移，则下一次倒推过程中操作数组的第 $i$ 个元素一定能将 $ans$ 的位置后移。所以只需记录遍历结束时的位置，下一次倒推过程中从同样的位置继续判断接下来的元素能否将 $ans$ 后移即可。

---
最后，共需进行 $k$ 次倒推，所有倒推过程中最多完整遍历一次操作数组，时间复杂度为 $O(n + k)$，除输入外只需常数空间。

### 参考代码

```cpp
void work()
{
	long long n, k;
	cin >> n >> k;
	vector<int> arr(n);
	for (long long i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	long long cur = 1, index = 0;
	while (k--)
	{
		cur += index;
		while (index < n && arr[index] <= cur)
		{
			index++;
			cur++;
		}
	}
	cout << cur << '\n';
}
```

---

## 作者：Che_001 (赞：7)

## 题意

给定一个包含 $1$ 到 $10^{1000}$ 的集合 $S$。每次**同时**删除 $S$ 中的第 $a_1$ 个、第 $a_2$ 个、$\ldots$ 个、$a_n$ 个最小的数。

询问经过 $ k $ 天后，集合 $S$ 中最小的元素。

## Solution

发现答案具有单调性，考虑二分答案。对于一个 $mid$，发现删除操作事实上是降低剩余数字的排名，故不断减去小于等于 $mid$ 的 $a_i$ 个数，即 $mid$ 在 $k$ 次删除中每次降低的排名。最后若排名大于 $0$，则当前 $mid$ 合法，寻找最小的合法的 $mid$ 即可。

注意特判 $a_1 \ne 1$ 的情况，此时答案一定为 $1$。

时间复杂度为 $\mathcal{O}(k\log nk)$，可以通过本题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
long long n,k;
long long val[200010];
bool check(long long mid)
{
	int point=n;
	for(int i=1;i<=k;i++)
	{
		while(val[point]>mid)
			point--;
		mid-=point;
	}
	return mid>0;
}
int main(int argc,const char *argv[])
{
	int T=read();
	while(T--)
	{
		n=read(),k=read();
		for(int i=1;i<=n;i++)
			val[i]=read();
		long long left=1,right=n*k+n,ans=n*k+n;
		if(val[1]!=1)
		{
			printf("1\n");
			continue;
		}
		while(left<right)
		{
			long long mid=(left+right+1)>>1;
			if(check(mid)==true)
				ans=mid,right=mid-1;
			else 
				left=mid;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

## Solution

其实这道题有时间复杂度为 $\mathcal{O}(n+k)$ 的做法。

假设序列 $a$ 递增。考虑反向模拟，我们每次不删除操作中位置 $a_1,a_2,\cdots,a_n$ 的数字，然后再 check 第 $k$ 次操作后的第一个数字。从数字 $1$ 开始，再每次运算中，尽量在 $a_1-1, a_2-2, \cdots, a_{n}-n$ 后插入 $0$，使 $0$ 在插入结束后占据位置 $a_1, a_2, \cdots, a_n$。在插入 $k$ 次后，$1$ 所在的位置即为答案。

定义 $1$ 的位置为 $now$，在具体实现中，我们记 $cnt$ 为 $now$ 之前有多少个 $a_1-1,a_{2}-2,\cdots,a_{n}-n$，则每个插入可以以 $\mathcal{O}(1)$ 的时间复杂度处理。即如果 $a_1-1$ 到 $a_i-i$ 都在 $x$之前，那么在 $now$ 之前插入 $i$ 个零。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
long long val[200010];
int main(int argc,const char *argv[])
{
	int T=read();
	while(T--)
	{
		long long n=read(),k=read();
		for(int i=1;i<=n;i++)
			val[i]=read();
		if(val[1]!=1)
		{
			printf("1\n");
			continue;
		}
		long long cnt=1,now=1;
		for(int i=1;i<=k;i++)
		{
			while(cnt<=n&&val[cnt]<=now+cnt-1)
				cnt++;
			now+=cnt-1;
		}
		printf("%lld\n",now);
	}
	return 0;
}
```

---

## 作者：_adil_ (赞：5)

**【题意】**

有一个 $1$ 到 $10^{1000}$ 的从小到大的排列，经过 $k$ 次操作，每次同时删除序列中第 $a_i$ 小的数，求最后序列中剩下的最小数。

**【结论】**

1. 显然，如果 $a_1\neq1$ ，答案就是 $1$ ，因为 $a$ 递增， 每次只会改后面的。
2. 只需模拟每次答案的位置，发现 ‘删除’ 不容易实现，即可从后往前，改为 ‘加回’ 被删掉的数。

设答案为 $ans$， 显然最后它的位置为 $1$ 。对于每次操作，我们查看有多少 $a_i-i<ans$ ，并把 $ans$ 加上这个数。这是因为一个数位置为 $x$ 且 $a_i\leq x<a_{i+1}$ ，如果它没被删掉， 操作后它的位置会变成 $x-i$ ，这样就可以巧妙地将一些在前几天就被删掉，但只对后面会被遍历到的位置算进去了。

计算过程中，因为 $a_i-i$ 也是不降的，所以 $i$ 可以增量式地更新，时间复杂度 $O(n)$。

**【代码】**

```cpp
#include<bits/stdc++.h>
#define N 500009
#define INF 0x3f3f3f3f
#define mod 998244353
using namespace std;
typedef long long ll;
ll n,k,t,mx;
ll a[N];
inline void solve(){
   cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(a[1]!=1){cout<<"1\n";return;}
    for(int i=1;i<=n;i++)a[i]-=i;
    ll onepos=1,cur=1;//onepos表示ans，cur表示i
    for(int i=1;i<=k;i++){
      while(onepos>a[cur+1]&&cur+1<=n){cur++;}
       onepos+=cur;
    }
    cout<<onepos<<endl;
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>t;
  for(int j=0;j<t;j++){
   solve();
  }
  return 0;
}
```


---

## 作者：Meowco (赞：5)

## 题意

有一个集合，初始状态里面有数字 $1$、$2$、$3$、$4$、$5$、......

现在给你一个长度为 $n$ 数组 $a (1\leq a_i \leq 10^9 )$，要进行 $k$ 次操作，每次操作将当前集合中第 $a_1$ 小、第 $a_2$ 小、......、第 $a_n$ 小的数同时移除。

请问 $k$ 次操作之后，最小的数是多少。

## 一个预备的结论

首先特判掉 $a[1] \neq 1$ 的情况，因为答案很显然为 $1$。

---

一个数 $x$，当集合一个数都没有删除的时候，它是第 $x$ 小。

那么进行了一次操作，这次操作中有 $y$ 个小于等于 $x$ 的 $a_i$，那么 $x$ 就会变成 $x-y$ 小（**无论这次操作是否可以直接删除 $x$**）。

那么换个思路，我们是不是可以每次操作之后都给 $x$ 赋新值，这个值为操作之后 $x$ 的排位。

比如 $a=[1,3,5,6,7]$，操作一次后，集合变成 $S=\{2,4,8,9,10,......\}$

我们之后给集合每个数以它的排位重新排位：

$2$ => $1$

$4$ => $2$

$8$ => $3$

$9$ => $4$

$10$ => $5$

...

如果 $x$ 最开始等于 $9$，它最开始的排位是第 $9$ 小，那么一次操作之后，$x$ 的排位为 $4$。

## 做法

有了上面这个结论，我们可以通过 $O(k\log{n})$ 查询一个数 $x$ 是否能够在 $k$ 轮内将排位修改成 $0$。

可以通过下面的代码理解一下：

```cpp
int check(int k, ll x, vector<int> &a)
{
	while (k--)
	{
		int p = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
		if (p >= a.size() || a[p] > x)
			p--;
		x -= p;
	}
	if (x >= 1)
		return 0;
	return 1;
}
```

每次操作，都去找 $a$ 里最后一个小于等于 $x$ 的 $a_i$ 的下标 $y$，这个下标就是在本次操作要删除的排位小于 $x$ 的数的个数。

理所应当的，$x$ 的排位减少了 $y$，那么就可以把 $x$ 赋值为 $x-y$。

---

一个数 $x$，如果它能在 $k$ 次操作排位被修改成 $0$，我们的答案肯定大于等于 $x$；

一个数 $x$，如果它的排位不能在 $k$ 轮内被修改成 $0$，那么它就有可能是我们的答案。

一个数 $x$，如果它是答案，那么 **所有小于** $x$ 的数的排位都会被修改为 $0$，所有大于 $x$ 的数，它们的排位都大于等于 $1$。根据这个，我们可以二分 $x$，求得最小的不能在 $k$ 轮被删除的数。总复杂度 $O(k\log{n}\log{C})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define pii pair<int, int>


int check(int k, ll x, vector<int> &a)
{
	while (k--)
	{
		int p = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
		if (p >= a.size() || a[p] > x)
			p--;
		x -= p;
	}
	if (x >= 1)
		return 0;
	return 1;
}

int main()
{
	fastio;
	int t;
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		vector<int> a(n + 1);
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		ll l = 1, r = 1e12, ans = 1;
		while (l <= r)
		{
			ll mid = l + r >> 1;
			if (check(k, mid, a))
				l = mid + 1;
			else
			{
				ans = mid;
				r = mid - 1;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：信息向阳花木 (赞：3)

这里讲一个通俗易懂的做法：二分。

首先，如果 $a_1 \neq 1$，那么 $1$ 这个数永远不会被删除，答案就是 $1$。

我们可以枚举 $k$ 天，对于每天，二分答案 $x$。

对于一个数 $x$，如果它在某天没有删除，且对于某个 $i$ 满足 $a_i \le x < a_{i + 1}$，那么它在当天，前面会有 $i$ 个数被删除。所以它在前一天的位置就是 $x - i$。这个 $i$ 我们可以用二分找到。我们必须要保证前一天 $x$ 的位置 $x - i$ 大于等于前一天答案 $res$ 的位置（$x - i \ge res$），根据这个性质二分即可。

时间复杂度 $O(k \log n \log nk)$。

代码很短：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long 

const int N = 200010;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int t, n, k;
int a[N];

signed main()
{
	in(t);
	while (t -- )
	{
		in(n); in(k);
		for (int i = 1ll; i <= n; i ++ ) in(a[i]);
		
		if(a[1ll] != 1ll) { puts("1"); continue; }
		
		int res = 1ll;
		while (k -- )
		{
			int l = 1ll, r = 1e18;
			while (l <= r)
			{
				int mid = l + r >> 1ll; 
				if(mid - (upper_bound(a + 1ll, a + n + 1ll, mid) - a - 1ll) >= res) r = mid - 1ll;
				else l = mid + 1ll;
			}
			res = l;
		}
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：白简 (赞：0)

### 题目大意

集合 $S:1,2,3,4,\dots,10^{1000}$。

给定长度为 $n$ 的单调递增正整数序列，给定一个数 $k$。

对 $S$ 进行 $k$ 次删除操作，每次以序列为下标删除最小元素，即每次同时删除集合中第 $a_1,a_2,\dots,a_n$ 小的元素。

求 $k$ 次删除操作后 $S$ 中最小元素。

### 思路

考虑二分答案。

对于一个数 $x$，假设删除了 $y$ 个小于 $x$ 的数，那么数 $x$ 的新排名变成 $x-y$。

那么我们就枚举 $k$ 次。对于每一次操作，我们找到最后一个小于等于 $x$ 的数 $a_i$ 的下标 $y$，那么 $x$ 的新排名就变成了 $x-y$。

对于一个数 $x$，如果它是答案，那么所有小于 $x$ 的数的排名都会被修改成 $0$；所有大于 $x$ 的数的新排名都大于等于 $1$。

对于二分的上界，就算 $a_1,a_2,\dots,a_n$ 是 $1 \sim n$ 的排列，那么最多也就删掉前面 $n \times k$ 个数，所以答案一定小于等于 $n \times k + 1$。

对于 $ans$ 的初始值，我们直接设成 $1$，这样相当于起到了特判的作用。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long

using namespace std;

int N,K;
int a[200500],ans;

bool Check(ll x) {
    int k = K;
    while(k--) {
        int cur = lower_bound(a + 1,a + N + 1,x) - a;
        if(a[cur] > x || cur > N)
            cur --;
        // ↑ 找到 a 里最后一个小于等于 x 的下标 cur 
        x -= cur;// 删了数后它的新排名 
        if(x <= 0)
            return 0;
    }
    return 1;
}

signed main() {
    ios::sync_with_stdio(false);
    int T = 1;
    while(T--) {
        cin >> N >> K;
        for(int i = 1;i <= N; i++) 
            cin >> a[i];

        int l = 1,r = N * K + 1,ans = 1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(Check(mid)) {
                ans = mid;
                r = mid - 1;
            }
            else 
                l = mid + 1;
        }
        cout << ans << "\n";
        for(int i = 1;i <= N; i++)
            a[i] = 0;
    }
  
    return 0;
}
```


---

