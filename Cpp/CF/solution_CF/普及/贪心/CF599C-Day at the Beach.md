# Day at the Beach

## 题目描述

一天Squidward，Spongebob，Patrick决定一起去沙滩玩。不幸的是，天气实在不好，他们没法冲浪了。然鹅，他们决定建一个沙堡。
那天快结束的时候，他们建了n个城堡。城堡被编号为1到n，第i个城堡的高度是hi。就在大家都要走的时候，Squidward注意到，沙堡没有按它们的高度排序，这看起来很不和谐,。现在，他们将重新排列城堡，使对于所有的i，（0<=i<=n-1）都有hi<=hi+1。
Squidward建议用下列方式给城堡排序：
- 城堡被分成几个连续的段，因此从i到j的城堡段应该包括i,i+1...j-1,j。一个城堡段可以只有一个城堡组成。
- 使所有城堡都在一个段内。
- 每个段独立于其他段进行排序，即序列hi,hi+1...hj-1,hj是有序的。
- 段的划分应满足在每个段被排序之后，序列也变得有序。这总是可以被满足因为可以把整个序列看做一段。
Patrick知道在分区中增加块的数量将简化排序过程。现在，他们要求你计算满足所有上述要求的分区中的最大可能块数。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
2 1 3 2
```

### 输出

```
2
```

# 题解

## 作者：zym20249_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF599C)

## 题意
有 $n$ 座城堡，编号为 $1$ 到 $n$，第 $i$ 座城堡的高度为 $h_i$。现在要将这些城堡重新排序，使得对于所有的 $i$（从 $1$ 到 $n−1$ ），都满足：$h_i\le h_{i+1}$。\
排序过程：

- 将城堡被分成若干个块，每块包含连续的城堡，一个块里可以只有一个城堡，每一个城堡都在某一个分块中。
- 每个块独立排序，使得 $h_i,h_{i+1},\dots,h_j$ 有序。
- 分块方式应保证所有的块内部排序后，整个序列 $h_i$ 也变得有序。

你的任务是确定满足上述要求最多可以将城堡分成多少个块。

## 思路
我们输入时，设原输入未排序的高度为一个数组 $x$，排序完的高度视为数组 $y$。我们可以枚举一遍数组的相邻的两项之差存入一个计算器里面累加，如果此计数器的最终结果为 $0$ 那么就是有序的。最后用一个变量存储答案，结果直接输出答案就行。

### 注意事项
如果数组 $x$，数组 $y$ 相等，那么这个数组本来就是有序的。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
ll h[maxn],nh[maxn],x,sum,ans,i,j,n,c;
signed main()
{
	scanf("%lld",&n);
	for(i=1;i<=n;++i)
	{
		scanf("%lld",&x);
		nh[i]=h[i]=x;
	}
	sort(nh+1,nh+1+n);
	for(i=1;i<=n;i++)
	{
        c=h[i]-nh[i];
        if(sum+c==0)ans++;
        sum+=c;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zlqwq (赞：1)

输入 $h$ 数组后，我们设一个数组 $nh$ 表示排序后的数组。

然后我们从 $1$ 到 $n$ 枚举，每次将原本的城堡和其对应的城堡的差值计算在和中。

然后注意一个细节，如果说当前 $sum$ 为 $0$，说明当前城堡的高度是有序的。

我们定义一个变量 $ans$ 去存储上述序列的个数。

最后直接输出 $ans$ 即可。


```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18

using namespace std;
const int N = 1e5 + 5;
int h[N],nh[N];
int n;
signed main() {
	cin >> n;
	for(int i = 1;i <= n;++i) {
		int x;
		cin >> x;
		nh[i] = h[i] = x;
	}
	sort(nh + 1,nh + 1 + n);
	int ans = 0,sum = 0;
	for(int i = 1;i <= n;++i) {
		int c = h[i] - nh[i];
		if(sum + c == 0) ans++;
		sum += c;
	} 
	cout << ans;
	return 0;
}
```

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF599C)

# 题意：

给定一个数列 $H$，你需要将它划分成几个连续的部分，使得各部分升序排序后组成的序列与原序列升序排序后相同。

# 思路：
我们先排序，记原序列为 $a$，排序后的序列为 $b$。

如果原数列与排序后的数列一样，那么原序列本来就是有序，这种情况下让每一个城堡独立作为一个段。

我们遍历数组 $a$ 和 $b$。算每个城堡高度与排序后对应的城堡高度的差，将差累加到 $ans$ 中，如果 $anss$ 为 0，则说明当前段的城堡是有序的，将答案 $cnt$ 加 $1$。输出最大可能的序列被划分的段数 $ans$。

# 代码:


```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
#include<utility>
#include<set>
#include<bitset>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
using namespace std;
const int N=1e5+10;
int ans,cnt,n, a[N],b[N];
int main() {
	int n=read();
	for(int i = 1; i<=n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b+1,b+n+1);
	for(int i = 1; i<=n; i++){
		ans+=(a[i]-b[i]);
		cnt+=!ans;
	}
	cout<<cnt;
	return 0; 
}
```

---

## 作者：_Kimi_ (赞：0)

# CF599C题解

### 题意

给定一个数列 $H$，你需要将它划分成几个连续的部分，使得各部分升序排序后组成的序列与原序列升序排序后相同。

### 思路

如果要把 $h_1,h_2,h_3 \dots h_i$ 划为一部分，需满足：

$$\max(h_1,h_2,h_3 \dots h_i) \le \min(h_i,h_{i+1},h_{i+2} \dots h_n)$$

很好理解，即为了让排序后是有序的，以此类推。

实现也很简单，预处理出 $\max(1,i)$ 和 $\min(i,n)$ 划分时按照上文提到的条件分即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define WA AC
using namespace std;
const int maxn = 1e5 + 10;
int n, ans = 1, A[maxn], MIN[maxn], MAX[maxn]; 
void input(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen("beach.in", "r", stdin);
	//freopen("beach.out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> A[i];
	MAX[1] = A[1];
	MIN[n] = A[n];
}
signed main(){
	input();
	for(int i = 2; i <= n; i++) MAX[i] = max(MAX[i - 1], A[i]);
	for(int i = n - 1; i >= 1; i--) MIN[i] = min(MIN[i + 1], A[i]);
	for(int i = 1; i <= n - 1; i++){
		if(MAX[i] <= MIN[i + 1]) ans++;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

## 思路

我们先对该序列进行排序，记原序列为 $a$，排序后的序列为 $b$。

如果原数列与排序后的数列一样，那么就说明原序列本身就是有序的了（如样例一），因此这种情况下可以让每一个城堡独立作为一个段。

解决这道题的通法，我们需要遍历数组 $a$ 和数组 $b$，计算每个城堡高度与排序后对应位置的城堡高度的差值，将差值累加到变量 $s$ 中。如果 $s$ 为  $0$，则说明当前段的城堡是有序的，将答案 $ans$ 加 $1$。最后输出最大可能的序列被划分的段数 $ans$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int ans,s,n, a[N],b[N];
int main() {
	cin>>n;
	for(int i = 1; i<=n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b+1,b+n+1);
	for(int i = 1; i<=n; i++){
		s+=(a[i]-b[i]);
		ans+=!s;
	}
	cout<<ans;
	return 0; 
}
```

---

