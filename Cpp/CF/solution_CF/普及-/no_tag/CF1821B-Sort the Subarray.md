# Sort the Subarray

## 题目描述

Monocarp had an array $ a $ consisting of $ n $ integers. He has decided to choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , and then sort the subarray $ a[l..r] $ (the subarray $ a[l..r] $ is the part of the array $ a $ containing the elements $ a_l, a_{l+1}, a_{l+2}, \dots, a_{r-1}, a_r $ ) in non-descending order. After sorting the subarray, Monocarp has obtained a new array, which we denote as $ a' $ .

For example, if $ a = [6, 7, 3, 4, 4, 6, 5] $ , and Monocarp has chosen $ l = 2, r = 5 $ , then $ a' = [6, 3, 4, 4, 7, 6, 5] $ .

You are given the arrays $ a $ and $ a' $ . Find the integers $ l $ and $ r $ that Monocarp could have chosen. If there are multiple pairs of values $ (l, r) $ , find the one which corresponds to the longest subarray.

## 样例 #1

### 输入

```
3
7
6 7 3 4 4 6 5
6 3 4 4 7 6 5
3
1 2 1
1 1 2
3
2 2 1
2 1 2```

### 输出

```
2 5
1 3
2 3```

# 题解

## 作者：Czy_Lemon (赞：11)

### 先解释一下题意： 

- 给你两个长度为 $n$ 的数组。
- 一个是原来的数组。
- 一个是将原来数组中的 $[l,r]$ 按照一种排序策略排序了之后的数组。
- 让你依据两个数组求出**最长**可能满足排序策略的 $[l,r]$。 

### 然后我们进行分析：

首先我们明确一下题目中的排序策略“**non-descending order**”，意思是**非降序**，也就是说序列中所有的元素都**不大于**它的下一个元素就行（最后一个元素除外）。

其次我们可以知道，虽然题中没有明确说，但是我们通过分析可以知道，Monocarp只会进行一次对 $[l,r]$ 的升序排序。这就意味着被排序的区间**一定包含了原数组与排序后数组的不同部分**。或者换句话说就是**两个数组不同的部分一定是被排序的部分或者是被排序部分的一部分**。

那么具体的思路就可以出来了。首先，我们用比较的方法得出一定属于被排序部分的那一部分，假设其为 $[a,b]$。对于 $a$，我们从 $a$ 向前枚举，如果能满足非降序，就将 $a$ 减少一，直到 $a=1$ 或者不再满足非降序。对于 $b$，我们从 $b$ 向后枚举，如果能满足非降序，就将 $b$ 增加一，直到 $b=n$ 或者不再满足非降序。最后的 $a,b$ 就是题目中所求的答案了。

### 以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2*1e5+10;
int t,n,a[N],b[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		int l,r;
		for(int i=1;i<=n;i++)
			if(a[i]!=b[i]){
				l=i;
				break;
			}
		for(int i=n;i>=1;i--)
			if(a[i]!=b[i]){
				r=i;
				break;
			}
		for(int i=l;i>=1;i--){
			if(b[i]>b[i+1]) break;
			l=i;
		}
		for(int i=r;i<=n;i++){
			if(b[i-1]>b[i]) break;
			r=i;
		}
		printf("%d %d\n",l,r);
	}
	return 0;
}
```

### 后记

如果对题解的内容有建议或者指正，请在在评论区里说或者私信我也行。

---

## 作者：Elaina_ (赞：4)


本题主要解题方法是：
## 先找出必须要排序的序列，再前和向后扩展。


------------

我们不难知道，最短的选择长度一定是从 $a$ 和 $a'$ 第一个不一样的字符到最后一个不一样的字符，比如：

```c
1 2 3 4 5

1 2 4 3 5
```


最短的选择就是 $3$ 和 $4$ 。

- 更加具体的证明方法：根据操作只有一种——排序，可以得到只要同一位置有不同的数就必须要进行排序，将二者变为相同。

接下来我们思考排序的性质对我们的选择进行扩大：

- 先考虑向前扩大：

如果添加的数比我们已经选择的那段数中最小值更小，那么添加进去后必然是放在我们序列前的，又因为单调递增的序列在从小到大排序时顺序不会改变，因此我们只需要在选择的序列前面扩展的序列是单调递增，且最大值小于我们选择序列中的最小值即可。

- 再考虑向后扩大：

如果添加的数比我们已经选择的那段数中最大值更大，那么添加进去后必然是放在我们序列后的，因此我们只需要只需要在选择的序列后面扩展的序列是单调递增，且最小值大于我们选择序列中的最大值即可。

另外的直接在求完基础序列后考虑向前向后扩展是会超时的，因此需要在求基础序列的时候求单调增序列。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int F = 3000000;

int out, len, s, t, flag, n, op, last, k, ml;
int a1[F], a2[F];

void work1()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a1[i];
	for (int i = 1; i <= n; i++)
		cin >> a2[i];
	last = a1[1];
	ml = 0;
	for (int i = 1; i <= n; i++)
		if (!flag)
		{
			if (a1[i] != a2[i])
			{
				s = i;
				flag = 1;
				if (a1[i - 1] <= a2[s])
					s -= ml;
			}
			else
			{
				if (last <= a1[i])
					ml++;
				else
					ml = 1;
				last = a1[i];
			}
		}
		else
		{
			if (a1[i] != a2[i])
				t = i;
		} // 求s和向前扩展的序列
	k = t + 1;
	last = a2[t];
	if (k <= n)
		while (a1[k] >= last)
		{
			last = a1[k];
			k++;
			if (k > n)
				break;
		}
	t = k - 1; // 直接求向后扩展的序列
	cout << s << " " << t << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> op;
	while (op--)
	{
		work1();
		s = t = 0;
		flag = 0;
	}
	return 0;
}
```


---

## 作者：Loser_Syx (赞：2)

## 思路

首先看到题目，它想要让你排列一个序列，而且排序的区间最长，排序后的第一个数组应该与第二个一样。

首先我们不妨考虑一下，什么样的情况才是必须要排序的呢？显然是两个数组不相同的地方，分别求一下最小的坐标与最大的坐标。

写到这里还没完，本题还有一个另外的要求：如果在此区间外还有些数，他们满足升序，这些数也可以被排列进去。

这样子的话复杂度是 $O(Tn)$，不超时。

## 代码

```cpp
//Author: Saint_ying_xtf
//Timelimit: 1000ms
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
namespace fastIO{
	inline int read(){
		int x = 0, s = 1;
		char c = getchar();
		while(c < '0' || c > '9'){
			if(c == '-') s = -1;
			c = getchar();
		}
		while(c >= '0' && c <= '9'){
			x = (x << 3) + (x << 1) + (c ^ '0');
			c = getchar();
		}
		return x * s;
	}
	inline void Write(int x){
		if(x < 0){
			putchar('-');
			x = -x;
		}
		if(x > 9) Write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x, char c){
		Write(x);
		putchar(c);
	}
}
using namespace fastIO;
namespace SyxQwQ{
	inline int qwq(){
		return 0;
	}
	int a[114514<<1], b[114514<<1];
	inline int main(){
		//todo
		int T = read();
		while(T--){
			int n = read();
			f(i, 1, n, 1) a[i] = read();
			f(i, 1, n, 1) b[i] = read();
			int Left = 0, Right = 0;
			f(i, 1, n, 1){
				if(a[i] != b[i]){
					if(Left == 0) Left = i;//最近
					Right = i;//最远
				}
			}
			//printf("%lld %lld\n", Left, Right);
			while(Left > 1 && b[Left] >= b[Left-1]) Left--;//左边满足升序一起排列
			while(Right < n && b[Right] <= b[Right+1]) Right++;//右边满足升序也排列
			write(Left, ' ');
			write(Right, '\n');
		}
		return qwq();
	}
}
signed main(){
	SyxQwQ::main();
	return 0;
}
```

过不了的话看一下这个 Hack：

```
1
3
3 1 3
1 3 3
```

输出应该是 `1 3`。

你的可能是 `1 2`，我一开始也是这么错的。。。

---

## 作者：cff_0102 (赞：0)

翻译：有一个序列 $a$，cff 排序了其中一段子序列 $[l,r]$，得到了另一个新的序列。给出这两个序列，求 cff 排序的那一段子序列的左右端点 $l,r$。输出最长的可能的子序列。

数据较小，直接贪心。

- 先找到第一个两个序列不一样的数字，再找到最后一个不一样的数字，这一段区间必然是经过排序的。
- 然后在这两个端点继续往外延伸，看看下一个数字是否满足递增/递减，直到碰到第一个不满足递增/递减的数字，说明这个数肯定没有被 cff 选中，那么就得到了最大的子序列。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int b[200010];
int main(){
    ios::sync_with_stdio(0);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }for(int i=1;i<=n;i++){
            cin >> b[i];
        }
        int l,r;
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]){//第一个不一样的
                l=i;
                break;
            }
        }
        for(int i=n;i>=1;i--){
            if(a[i]!=b[i]){//最后一个不一样的
                r=i;
                break;
            }
        }//接着开始拓展延伸
        while(b[l-1]<=b[l]&&l>1){//向左延伸，如果不再递减或者到了左边界就不再循环
            l--;
        }
        while(b[r+1]>=b[r]&&r<n){//向右延伸
            r++;
        }
        cout<<l<<" "<<r<<endl;//记得多测换行
    }
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/108759614)。

---

## 作者：_299817_ (赞：0)

## Part 1: 思路
首先，我们可以发现一个求出一个最简单的解的方法，就是求出最左边第一个和原数组不同的地方和右边第一个和原数组不同的地方，但是题目要求求最大的区间，那么怎么办呢？

我们可以看区间的左端点的左边的数是不是小于左端点，如果是，就把左端点往左移，如果不是，就立即停止这种操作，右端点同理。

## Part 2: 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n;
int a[200010];
int b[200010];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        int index1 = -1; // 区间左端点
        int index2 = -1; // 区间右端点
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        for(int i = 1; i <= n; i++){
            cin >> b[i];
        } // 输入
        for(int i = 1; i <= n; i++){
            if(a[i] != b[i]){
                index1 = i;
                break;
            }
        }
        for(int i = n; i >= 1; i--){
            if(a[i] != b[i]){
                index2 = i;
                break;
            }
        } // 求出最小的合法解
        while(b[index1 - 1] <= b[index1] && index1 >= 2){
            index1--;
        } // 向左侧拓展
        while(b[index2 + 1] >= b[index2] && index2 <= n - 1){
            index2++;
        } // 向右侧拓展
        cout << index1 << " " << index2 << endl;
    }
    return 0;
}
 
```

---

## 作者：yuanruiqi (赞：0)

## 题目分析

$a$ 和 $b$ 数组第一个不同的地方一定是选中区域中的。先记这个位置是 $l$

然后从 $l$ 开始往后推 $r$，记录最大值及其数量，直到 $b$ 数组已经有这么多数量的最大值后退出循环，并记录索引为 $r$。

然后在 $l$ 前和 $r$ 后如果 $a$ 和 $b$ 的值满足相等且单调不减，就可以拓展 $l$ 和 $r$。

## 代码

```cpp
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i=0;i<n;++i)
        cin >> a[i];
    for (int i=0;i<n;++i)
        cin >> b[i];
    int l = 0, r = 0;
    for (int i=0;i<n;++i)
        if (a[i] != b[i])
        {
            l = i;
            break;
        }
    int mx = 0, cnt = 0;
    for (int i=l;i<n;++i)
    {
        if (i != l && b[i] < b[i-1]) break;
        if (a[i] == mx) ++cnt;
        if (a[i] > mx) mx = a[i], cnt = 1;
        if (b[i] == mx) --cnt;
        if (cnt == 0) r = i;
    }
    while (l && b[l-1] <= b[l]) --l;
    while (r < n - 1 && b[r+1] >= b[r] && a[r+1] == b[r+1]) ++r;
    cout << l + 1 << ' ' << r + 1 << '\n';
}
```


---

## 作者：aeiouaoeiu (赞：0)

### 题意
给你长度为 $n$ 的两个数组 $a$ 和 $a'$，问最长的区间 $[l,r]$，使得在给数组 $a$ 中 $[l,r]$ 范围内的数升序排序后和 $a'$ 一样，数据保证必定有解，且 $a$ 与 $a'$ 至少有一处不同。
### 解法
既然必定有解，那么 $a$ 和 $a'$ 内的数就是一样的，所以我们可以关注那些下标相同但值不同的数，它们必然是被排序的数。我们把这些最左边和最右边的这些数记录下来，就可以得到一段区间，这段区间必然被排序。除了这段区间里的数，区间外满足升序的数也可以被排序，所以我们可以从这段区间起向外延申，直到不满足升序为止，此时的区间一定是最大的。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
const ll p=1000000007;
ll n,a[maxn],b[maxn];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		ll l=-1,r=-1;
		for(int i=1;i<=n;i++){
			if(a[i]!=b[i]){
				if(l==-1) l=i;
				r=i;
			}
		}
		for(;b[l]<=b[l+1]&&l>=1;l--);
		for(;b[r]>=b[r-1]&&r<=n;r++);
		cout<<l+1<<" "<<r-1<<"\n";
	}
	return 0;
}
```

---

## 作者：Scrolling_Ball (赞：0)

显然我们可以把答案分成两部分来讨论：

```
1.必须进行排序的。
2.就算排序也没有影响的。
```

## case1

因为题目保证有解，所以可以直接从左往右找到第一个 $b$ 跟 $a$ 不同的，记作 $l$。从右往左找到第一个不同的，记作 $r$。这段区间是必须要排序的那些数。

## case2

对于那些就算排序也没有影响的，我们就从第一种情况中求出的 $l$ 和 $r$ 分别往左和右拓展就行了。因为 $l\sim r$ 区间保证是单调不递减的，所以往左找更小的，往右找更大的才能不破坏单调性。

**注意**：这里讨论的是 $b$ 数组，讨论 $a$ 数组的话就会出现 $l\sim r$ 这个区间不保证单调不递减的情况。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int t, n;
int a[N], b[N];
int main()
{
	scanf("%d", &t);
	while(t -- )
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++ )
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i ++ )
			scanf("%d", &b[i]);
		int l, r;
		for(int i = 1; i <= n; i ++ )
			if(a[i] != b[i])
			{
				l = i;
				break;
			}
		for(int i = n; i >= 1; i -- )
			if(a[i] != b[i])
			{
				r = i;
				break;
			}
		while(b[l - 1] <= b[l] && l > 1)l -- ;
		while(b[r + 1] >= b[r] && r < n)r ++ ;
		printf("%d %d\n", l, r);
	}
	return 0;
}
```

---

