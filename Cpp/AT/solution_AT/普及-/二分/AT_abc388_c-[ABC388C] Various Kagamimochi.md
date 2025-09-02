# [ABC388C] Various Kagamimochi

## 题目描述

有 $N$ 个大小不一的饼。第 $i$ 个饼的大小为 $a_i$（$1 \le i \le N$）。

对于任意两个大小分别为 $a$ 和 $b$ 的饼 $A$ 和 $B$，如果 $a$ 小于或等于 $b$ 的一半，即 $a\le \frac{b}{2}$，则可以将饼 $A$ 放在饼 $B$ 上制作一个“镜饼”。

从 $N$ 个饼中任选两个，使得其中一个饼放在另一个饼上制作一个“镜饼”。

需要求出可以制作多少种不同的“镜饼”。

此外，即使构成镜饼的饼的大小相同，只要至少有一个是不同的饼，就可以算作是另一种类型的镜饼。

**Translate by [chinazhanghaoxun](https://luogu.com.cn/user/684848)。**

## 样例 #1

### 输入

```
6
2 3 4 4 7 10```

### 输出

```
8```

## 样例 #2

### 输入

```
3
387 388 389```

### 输出

```
0```

## 样例 #3

### 输入

```
32
1 2 4 5 8 10 12 16 19 25 33 40 50 64 87 101 149 175 202 211 278 314 355 405 412 420 442 481 512 582 600 641```

### 输出

```
388```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc388_c)

### 思路

可以使用**双指针**解决此题。

首先将序列按升序排序。用两个循环变量，$i$ 在左，$j$ 在右，则 $A_i$ 表示上面的麻薯，$A_j$ 表示下面的麻薯。每一次寻找最小的 $A_j$ 满足 $A_i\le\frac{A_j}{2}$，那么 $i$ 到 $j$ 的区间全部满足要求，故将答案增加 $j-i+1$ 即可。

由于 $i$ 和 $j$ 只会向后移动，时间复杂度为 $N$ 级别，最大时间复杂度来自排序，为 $\mathcal{O}(N\log N)$，可以通过此题。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=5e5+10;
int a[N];
signed main(){
	int n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1,j=1;i<=n;++i){
		while(j<=n&&a[i]*2>a[j])
			++j;
		ans+=n-j+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：FlowerAccepted (赞：4)

## 解题思路

注意到寿司的顺序对答案无影响，可以对 $A$ 数组进行**降序**排序。这可以使用 `std::greater<int>` 来实现。

  排序后可以使用双指针，定义两个指针 $i$，$j$（$1 \le i, j \le N$），都初始化为 $1$；

当 $j$ 大于 $i$ 的一半时将 $j$ 加一，直到 $i >= 2j$ 为止，将答案加上 $(N - j + 1)$（加一是因为 $A_i$、$A_j$ 本身也可以做镜饼），再将 $i$ 加一。接下来不用归位 $j$，因为 $A_i$ 随着 $i$ 的增加而不增，满足条件的 $\min A_j$ 也不增，相应的 $j$ 不会减少。
  
重复执行这一过程直到 $j$ 超过 $n$，之后的 $i$ 将不能做成镜饼。

小心整形溢出：十年OI一场空，不开 `long long` 见祖宗。

## 代码呈现
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring> // 不用万能头
using namespace std;

int a[500005]; // 开大

int main() {
    int n;
    long long ans = 0; // 小心溢出
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, greater<int>()); // 降序
    for (int i = 1, j = 1; j <= n; ) { // 这里变量自增不写
        if (a[j] * 2 > a[i]) {
            j ++;
        } else {
            ans += n - j + 1;
            i ++;
        }
    }
    cout << ans;
    return 0;
}

```

## 复杂度分析

因为 $i$、$j$ 只会从 $1$ 到 $n$ 过一遍，所以算法时间复杂度是 $O(n)$，这正是双指针技巧的魅力所在，AtCoder Beginner Contest 签到题后的 1 至 3 道题会规律性的考察这个技巧，算个彩蛋吧。

---

## 作者：chinazhanghaoxun (赞：2)

## 思路
看到这道题就可以想到，对于每个 $a_i$，所有满足 $1\le a_j\le\frac{a_i}{2}$ 的 $a_j$ 都可以放在上面，而题目中提示我们给定的 $a$ 是按升序排列，那么这道题其实就是让我们求出满足 $a_j\le \frac{a_i}{2}$ 的最大位置 $j_{\max}$。

想到这里，看到题目中 $1\le n\le 10^9$，就不可能用数组开桶。所以想到使用 STL 容器中的 vector，其中的 upper_bound 正好可以满足我们的需求，因为只要 $a_x> \frac{a_i}{2}$ 为第一个，那么前面的一定满足条件。不会的可以看看[介绍](https://oi-wiki.org/lang/csl/algorithm/)。
## 代码
思路有了，代码就非常好写了。但是要注意看范围，开 long long！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> a;
int n,ans;
signed main(){
	cin>>n;
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	for(int i=0;i<n;i++){
		ans+=upper_bound(a.begin(),a.end(),a[i]/2)-a.begin();//按照思路求出即可 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：IronMen (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc388_c)

[AtCoder链接](https://atcoder.jp/contests/abc388/tasks/abc388_c)

---
## 题目
有 $N$ 个年糕，按大小升序排列。第 $i$ 个年糕的大小是 $A_i \ (1 \le i \le N)$。

给定大小分别为 $a$ 和 $b$ 的两个年糕 $A$ 和 $B$，当且仅当 $a$ 小于等于 $b$ 的一半时，你可以将年糕 $A$ 放在年糕 $B$ 的上面，制作一个叠年糕。

你从 $N$ 个年糕中选择两个年糕，并将一个放在另一个上面，组成一个叠年糕。求可以做出多少种不同的叠年糕。

---
## 思路
由于 $2 \le N \le 5 \times 10^5$，很明显直接遍历所有年糕会超时。

既然直接求解不好求，那么我们就换一种思路。我们先选定一个年糕作为叠年糕中上面的年糕，设它的大小为 $a$。因为 $A_i \le A_{i+1}$，所以不难想出如果第 $i$ 个年糕的大小满足 $a \le \dfrac{A_i}{2}$（即可以作为叠年糕中下面的年糕），那么在这个年糕后面的年糕的大小也一定满足，我们就没有必要去判断了。

这样，我们只要求出第一个符合要求的年糕的下标，从而求出符合要求的年糕的数量即可。

这里，我用 C++ 自带的 `lower_bound` 函数（不会用的可自行上网查询）去二分查找这个下标。

---
### 代码
**十年 OI 一场空，不开 long long 见祖宗。**
```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, a[500010], res, pos;

int main()
{
	scanf("%lld", &n);
	for (int i = 0; i < n; i ++ )
		scanf("%lld", &a[i]);
	for (int i = 0; i < n; i ++ )
	{
		pos = lower_bound(a, a + n, a[i] * 2) - a;
		res += n - pos;
	}
	cout << res << '\n';
	return 0;
}
```

---

## 作者：zzwdsj (赞：1)

### 题目大意
给定一个长为 $n$ 的，升序排列的数组 $A$。求数组中满足 $A_i\le A_j\div 2$ 的数对 $(i,j)$ 数量。
### 思路
题目转化一下，变成求数组中满足 $A_i\times2\le A_j$ 的数对 $(i,j)$ 数量。枚举 $i$，求得每个 $i$ 对应的 $j$ 的个数，加起来即为答案。

那么如何求得每个 $i$ 对应的 $j$ 的个数呢？首先在数组里二分找到第一个大于等于 $A_i\times2$ 的数的位置，记作 $k$。那么 $k\le j \le n$ 就是这个 $i$ 对应的 $j$ 的取值范围，共 $n-k+1$ 种取值。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,a[500005];//不开 long long 见祖宗
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans+=n-(lower_bound(a+1,a+n+1,a[i]*2)-a)+1;
	cout<<ans;
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

赛时六分钟秒的简单二分。

形式化题意：给定一个升序排列且长度为 $N$ 的数列 $A$，求有多少对 $\left(i,j\right)$ 满足 $A_i\leq\frac{A_j}2$。

考虑对每个位置 $i$ 分别统计满足条件的 $j$ 的数量。容易发现 $j$ 的分布具有单调性，即若存在 $\left(i,j_1\right)$ 满足条件且 $j_1\leq j_2$，$\left(i,j_2\right)$ 一定满足条件。因此对每个位置二分。设数列中第一个大于等于 $A_x\times 2$ 的位置为 $f(x)$，则答案为 $\sum_{i=1}^NN-f(i)+1$。时间复杂度 $O(N\times\log N)$。

[参考代码](https://atcoder.jp/contests/abc388/submissions/61550162)

---

## 作者：QAQ2012 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc388_c)

## 思路

因为题目所给的数从小到大，当前第 $i$ 个及以前有 $i$ 个，且只要**小于等于**底下的数的一半都可以算作是一种方案数，所以**考虑二分**，查找小于等于当前数的一半的数最大是多少。

## 代码


```cpp
#include<bits/stdc++.h>

using namespace std;
long long n,sums=0,a[500005],l,r,rets;
int main(){
	cin>>n;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
	}
	for(int i = 1 ; i <= n ; i++){
		l=1ll;
		r=i*1ll;
		rets=0;
		while(l <= r){
			long long mid=(double)(l+r)/2;
			if(a[mid]<=(double)(a[i]/2)){
				rets=mid;
				l=mid+1ll;
			}
			else{
				r=mid-1ll;
			}
		}
		sums+=rets;//加上方案数
	}
	cout<<sums;
	return 0;
}


```

---

## 作者：SuyctidohanQ (赞：0)

### 题意简述

题目要求我们计算可以组合成“镜饼”的不同配对数量。组合的条件是其中一个饼的大小必须不超过另一个饼的一半。

我们可以使用双指针的方法来高效地解决这个问题。

### 思路分析

以下是解决方案的步骤：

- 读取饼的数量 $N$ 以及它们的大小。

- 我们维护两个指针，$i$ 和 $j$。指针 $i$ 用来遍历每个饼，作为可能的较大饼，而指针 $j$ 用来查找可以放在 $i$ 上方的最大饼。

- 对于大小为 $A _ i$ 的饼，我们需要找到所有满足 $A_j \leq A _ i \div 2$ 的 $A_j$。
这意味着我们需要找到最大的 $j$，使得 $A _ j$ 满足条件。

- 对于每个有效的 $A _ i$，如果找到的最大有效 $j$，则从 $0$ 到 $j$ 的每个饼都可以与 $A _ i$ 配对。
所以可以形成的有效配对数量是 $j + 1$（因为我们从索引 $0$ 计数到 $j$）。

- 遍历整个列表，同时根据需要调整 $j$ 指针，确保它总是指向当前 $i$ 的最大有效饼。

以上就是解决本题目的基本思路。当然，我们也可以使用**二分**的方法解决这个问题。

### 代码实现

**双指针：**

```python
def findans (N, A):
    count = 0
    j = 0
    for i in range(N):
        while j < N and A[j] <= A[i] / 2:
            j += 1
        count += j
    
    return count
N = int (input ().strip ())
A = list (map (int, input ().strip ().split ()))
result = findans (N, A)
print (result)

```

**二分：**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main () {
    int N; cin >> N;
    vector <int> A (N);
    for (int i = 0; i < N; i ++) cin >> A[i];
    int ans = 0;
    for (int j = 0; j < N; j ++) {
        int b = A[j], len = b / 2, cnt = lower_bound (A.begin (), A.end (), len + 1) - A.begin ();
        ans += cnt;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：DoubleQLzn (赞：0)

我们可以对于每个 $a_i$，找到其最小满足要求的值 $a_i\times 2$，用 `lower_bound` 寻找满足要求的数中下标最小的后表示为 $k$。那么答案就是所有 $n-k+1$ 的和。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[500005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	long long s=0;
	for(int i=1;i<=n;i++){
		int k=lower_bound(a+1,a+n+1,a[i]*2)-a;
		if(k>i&&k<=n)s+=(n-k+1);
	}
	cout<<s;
	return 0;
}
```

---

## 作者：jinhangdong (赞：0)

对于每一个位置，我们二分找到最后面满足条件的，那么它前面的肯定也满足条件，答案就可以加上那个位置了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[500005],sum,l,r;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i)
	{
		l=0,r=i;
		while(l<r)//二分找到最大的满足条件的
		{
			int mid=(l+r+1)/2;
			if(a[mid]*2<=a[i]) l=mid;
			else r=mid-1;
		}
		sum+=l;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：yanghaoyu123 (赞：0)

## [[ABC388C] Various Kagamimochi](https://www.luogu.com.cn/problem/AT_abc388_c)

我看上面很多大佬都是用二分或者双指针做的，而我这样的蒟蒻只能给大家出一个暴力优化的题解。

### 思路

由于大小到了 $10^9$ ，所以我们可以缩短一下它的循环，可以先把第一个输入进去，之后每次输入的时候都只求它前面的值是否大于或等于它的二倍，如果是就加一。


```cpp
if(arr[i]>=v*2){
  while(arr[i]>=arr[l]*2){
     sum++;
      l++;
  }
  v=arr[l];
}
ans+=sum;
```

### 总代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum=0,v,l,arr[(int)5e5+55];
long long ans=0;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    cin>>arr[1];
    v=arr[1];
    l=1;
    for(int i=2;i<=n;i++){
        cin>>arr[i];
        if(arr[i]>=v*2){
            while(arr[i]>=arr[l]*2){
                sum++;
                l++;
            }
            v=arr[l];
        }
        ans+=sum;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

