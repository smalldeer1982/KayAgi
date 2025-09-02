# 「ALFR Round 3」B Swap & Delete

## 题目描述

给定一个长为 $n$ 的序列 $a_1, a_2,a_3, \dots ,a_n$，你需要执行 $k$ 次操作使这个序列为空。

每次操作可以执行下列内容之一：

1. 选择两个数 $i, j$，交换 $a_i, a_j$（需要满足 $1 \le i < j \le n$）。
2. 选择两个数 $i, j$，删除 $a_i,a_{i+1}, \dots ,a_j$（需要满足 $1 \le i \le j \le n$，且 $a_i = a_j$）。

请输出最小的操作数 $k$。


## 说明/提示

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $n\le 3$ |
| $2$ | $20$ | $n\le 10$ |
| $3$ | $20$ | $a_i\le 2$ |
| $4$ | $10$ | 保证所有 $a_i$ 相等 |
| $5$ | $40$ | - |

对于 $100\%$ 的数据，$1\le T \le 5$，$1\le n\le 10^5$，$0\le a_i\le 10^9$。

## 样例 #1

### 输入

```
2
5
1 2 3 2 3
3
1000000000 1000000000 99999999```

### 输出

```
2
2```

# 题解

## 作者：Christmas_Defunct (赞：14)

很简单的分类讨论题，赛时 AC 了。
## 题意简化
你可以对序列 $a$ 进行如下两类操作 $k(k\in\N^+)$ 次。
1. 交换 $a_i$ 和 $a_j$，其中 $i\not=j$。
2. 删除 $a_i\sim a_j$，但是必须满足 $a_i=a_j$。

显然的，有 $+\infty$ 种方法可以使 $a$ 为空串，现在想知道所有方法中 $\min k$ 的大小。
## 解法
这题求 $\min k$ 的做法很显然：使操作 $2$ 的效率最大化，因为只有操作 $2$ 可以删除数，而操作 $1$ 却无法删除。

这时候问题聚焦于另一个地方：如何使操作 $2$ 的效率最大化呢？

注意到 $a_i=a_j$，所以可以猜测做法为**通过操作 $1$ 构造满足 $a_1=a_n$ 的序列**，这样的话就可以满足仅需修改首尾便可满足操作的 $2$ 条件。

这里，我们只需要分析 $a_1$ 和 $a_n$。
> 1. 若 $a_1=a_n$，进行 $1$ 次操作 $2$ 即可，$\min k=1$。
> 2. 若 $a_1\not=a_n$，继续分类讨论。
>    > 记 $b_{a_{i}}$ 为 $a_i$ 在序列中出现的次数。
>    > 1. 若 $b_{a_1}\geq2$，记另外任意一个值为 $a_1$ 且在 $a$ 中出现的数的位置为 $pos_l$，进行一次操作 $1$，交换 $a_{pos_l} 和 a_{n}$，随即转换为 $a_1=a_n$，故 $\min k=2$。
>    > 2. 若 $b_{a_n}\geq2$，记另外任意一个值为 $a_n$ 且在 $a$ 中出现的数的位置为 $pos_r$，进行一次操作 $1$，交换 $a_{pos_r} 和 a_{1}$，随即转换为 $a_1=a_n$，故 $\min k=2$。
>    > 3. 若不满足 $b_{a_1}\geq2$ 和 $b_{a_n}\geq2$ 但是 $\exist\ b_{a_i}\ge2$，此时记 $pos_l$ 和 $pos_r$ 为其中相异的两个值为 $a_i$ 的数的下标，进行 $2$ 次操作 $1$，分别交换 $a_1,a_{pos_l}$ 和 $a_n,a_{pos_r}$，随即转换为 $a_1=a_n$，故 $\min k=3$。
>    > 4. 若 $\forall\ b_{a_i}=1$，则无论如何进行多少次操作 $1$ 都无法转化为 $a_1=a_n$，此时只能使 $i=j$，必定满足 $a_i=a_j$，有 $n$ 个数，所以此时 $\min k=n$。

这样，我们便完成了分类讨论，下面进行整理。

整理得
- 若 $a_1=a_n$，$\min k=1$；
- 若 $b_{a_1}\geq2$ 或 $b_{a_n}\geq2$，$\min k=2$；
- 若 $\exist\ b_{a_i}\geq2(i\not=1,n)$，则 $\min k=3$；
- 否则 $\min k=n$。

这里的 $b$ 又被称之为桶数组，用了**空间换时间**的优化方法。用 $\mathcal{O}(\max a)$ 的空间换掉了 $\mathcal{O}(n)$ 的时间。此时空间复杂度为 $\mathcal{O}(\max a)$，时间复杂度为 $\mathcal{O}(n)$。时间上可以通过 $n=10^5$ 的数据，但是无法满足 $\max a=10^9$。

注意到 $a_i$ 的数量最多为 $n$ 个，所以用离散化可以去掉多占用的空间，将空间复杂度优化至 $\mathcal{O}(n)$，此处仅使用 `map` 进行优化即可，此处不再赘述 `map` 的使用方法，不会用的可以参考别的文章。

综上，我们的每个过程复杂度变化如下：
- 时间复杂度：$\mathcal{O}(n^2)\to\mathcal{O}(n)\to\mathcal{O}(n)$。
- 空间复杂度：$\mathcal{O}(n)\to\mathcal{O(\max a)}\to\mathcal{O}(n)$。

## 代码
下面是本题的代码，请勿抄袭，~~这么简单的题目咱还是别抄了~~。
```cpp
#include <bits/stdc++.h>
using namespace std;

void work() {
	int n, a[100005];
	bool flag = false;
	cin >> n;
	map<int, int> mp;
	memset(a, 0, sizeof a);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]]++;
		if (mp[a[i]] == 2) flag = true;
	}
	if (mp[a[1]] >= 2 || mp[a[n]] >= 2) {
		if (a[1] == a[n]) cout << 1 << '\n';
		else cout << 2 << '\n';
	} else if (mp[a[1]] == 1 && mp[a[n]] == 1) {
		if (flag) cout << 3 << '\n';
		else cout << n << '\n';
	}
}

signed main() {
	int t;
	cin >> t;
	while (t--) work();
	return 0;
}
```
此文是本人的第 $2$ 篇题解，欢迎参考！

---

## 作者：szh_AK_all (赞：8)

简单的分类讨论。

- 当 $a_i$ 互不相同时，可以发现操作一是没有意义的，所以答案为 $n$，即每次删掉一个数。

- 若 $a_1=a_n$，则进行一次操作二即可，答案为 $1$。

- 若存在一个 $x$ 满足 $a_x=a_1$ 或 $a_x=a_n$，那么答案为 $2$。可以将 $a_x$ 与 $a_n$ 或者 $a_1$ 交换，此后便成为了第二种情况。答案为 $2$。

- 若存在一个数对 $(x,y)$ 满足 $a_x=a_y$ 且 $x<y$，那么可以将 $a_x$ 与 $a_1$ 交换，此后便成了第三种情况。答案为 $3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
map<int, int>q;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		q.clear();
		int one = 0, two = 0, three = 0;
		for (int i = 1; i <= n; i++) {
			if (q[a[i]] == 1)
				two = 1;
			else if (q[a[i]] && i == n)
				two = 1;
			else if (q[a[i]])
				three = 1;
			q[a[i]] = i;
		}
		if (a[1] == a[n])
			one = 1;
		if (one)
			cout << 1;
		else if (two)
			cout << 2;
		else if (three)
			cout << 3;
		else
			cout << n;
		cout << "\n";
	}
}
```

---

## 作者：Tomwsc (赞：4)

## 题意

通过交换和删除两个操作来使数列为空。

## 思路及做法

首先，我们来分两类讨论：

### 1.若数列里的数没有相同的

则每个数只能一个一个的消，所以直接输出 $n$。

### 2.若数列里的数有相同的

不难想到，如果有相同的数，则在当相同的数中有两个数分别在数列的两端时所需要的次数最少。所以，我们要尽可能的把数调换到数列的两端。

现在我们来讨论调换加消除的步数：

1. 若相同的数中有两个数分别在数列的两端，即 $a_1 = a_n$ 不用说，直接输出 ```1```。
  2. 若相同的数中有一个数在数列的一端，即则需要把另外一个相同的数移到数列的另外一端。移加消共需要两步，所以输出 ```2```。
  3. 若相同的数中没有任何一个数在数列的两端，则需要移动两次加消一次，共三次。所以直接输出```3```。

我们发现，若数字 $x$ 在数列中出现过，且这些相同的数的下标分别是：$i$，$i+1$，$i+2$，$\cdot\cdot\cdot$，$i+m$。则需要消除的次数只和 $i$，$i+m$ 有关。

所以，我们只需要找到重复数字中的下标最靠前和最靠后的两个就可以了。

## 代码实现

我们需要判重复的数，考虑进行一次排序。但排序完后，数的下标就不知道了。所以，我们要用一个结构体存储数的值和下标。然后只需要二分找到每个数最后一个出现的位置即可。

时间复杂度 $O(n \log n)$ 可以通过该题。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 10;
int t , n;
struct Node {
	int num , x;
};
Node a[MAXN];

inline bool cmp(Node a , Node b) {
	if(a.x != b.x)
		return a.x < b.x;
	else
		return a.num < b.num;
} 

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n;
		memset(a , 0 , sizeof(a));
		for(register int i = 1;i <= n;i ++) {
			cin >> a[i].x;
			a[i].num = i;
		}
		sort(a + 1 , a + 1 + n , cmp);
		int minn = n;
		bool flag = false;
		int l , r;
		for(register int i = 1;i <= n;i ++) {
			l = 1;
			r = n;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(a[mid].x <= a[i].x)
					l = mid + 1;
				else
					r = mid - 1;
			}
			l --;
			if(i == l)
				continue;
			if(a[i].num == 1 && a[l].num == n) {
				cout << 1 << '\n';
				flag = true;
				break;
			}
			if(a[i].num == 1 || a[l].num == n)
				minn = min(minn , 2ll);
			else
				minn = min(minn , 3ll);
		}
		if(flag)
			continue;
		cout << minn << '\n';
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11446)

可以很容易想到一种最优策略：如果在数列中有两个相同的数，就把它们分别放到头和尾然后删除即可。所以我们先统计一下每个元素的出现次数，如果它们互不相同，那就只能一个一个删除，输出 $n$；否则，遍历每一个元素，如果有元素的出现次数 $\ge2$，就把它们分别移到 $a_1$ 和 $a_n$（如果相同就不用移了），最后统计操作次数（注意还有一个删除的操作次数要加上）取最小值就可以了。

```cpp
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int N = 1e5 + 5;

int T, n, a[N];
map<int, int> cnt;

bool Check()
{
	for (int i = 1; i <= n; i++)
        if (cnt[a[i]] != 1) return false;
	return true;
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		cnt.clear(); // 多测清空！
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			cnt[a[i]]++; // 统计出现次数
		}
		if (Check()) cout << n << "\n"; // 互不相同
		else
		{
			int ans = 1e9;
			for (int i = 1; i <= n; i++)
				if (cnt[a[i]] >= 2)
				{
                    int sum = 1; // 把最后删除的操作次数算上
                    if (a[1] != a[i]) sum++; // 如果不相同就移到 a[1]
                    if (a[n] != a[i]) sum++; // 如果不相同就移到 a[n]
                    ans = min(ans, sum); // 取最小值
				}
			cout << ans << "\n";
		}
	}
	return 0;
}
```

---

## 作者：___AaAa_bBcCd___ (赞：4)

容易发现，对于长度大于等于 $3$ 的序列，我们都希望将 $a_1$ 和 $a_n$ 变得相同，然后一次性消掉。因为这样：

- 如果 $a_1$ 已经等于 $a_n$，则一次操作二就行。

- 如果可以通过一次交换使得 $a_1=a_n$，则总共需要两次操作。

- 如果序列中有任意两个元素相同，则最多需要两次交换、一次消除（把那两个相同的元素交换到 $a_1$ 和 $a_n$）。

- 如果序列中元素两两不同，则交换不起作用，所以只能每次选择 $i=j$，消除 $n$ 次。

$n=1$ 时需操作一次，$n=2$ 时看 $a_1$ 是否等于 $a_n$ 决定一次还是两次。

结论：答案只有为 $1$、$2$、$3$、$n$ 的情况。代码好写。

---

## 作者：cff_0102 (赞：4)

如果 $a_i$ 互不相同，那么操作 $1$ 没有意义，进行 $n$ 次操作 $2$ 即可全部删除。

如果 $a$ 中有两个重复的数，那么答案最多是 $3$：先将这两个数换到序列的两端再将其一次全部删除即可。

特殊情况 $1$：如果 $a_1=a_n$，只需要操作一次。

特殊情况 $2$：如果存在一个 $i$（$2\le i\le n-1$）使得 $a_1=a_i$ 或 $a_n=a_i$，只需要交换一次即可让序列两端的数相同，再花费一次操作全部删除。

我的验题代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N];
void mian(){
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(a[1]==a[n]){
		cout<<1<<endl;return;
	}
	bool f=0;
	set<int>st;
	for(int i=2;i<n;i++){
		if(a[i]==a[1]||a[i]==a[n]){
            cout<<2<<endl;return;
        }
		if(st.find(a[i])!=st.end())f=1;
		st.insert(a[i]);
	}
	if(f){
		cout<<3<<endl;return;
	}
	cout<<n<<endl;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--){
		mian();
	}
	return 0;
}
```

---

## 作者：easy42 (赞：1)

是一道分类讨论题。

1. 如果序列的头和尾都相同，只需要一次。

解释：如果序列的头和尾都相同，可以直接删除整个序列，只需要一次。

代码：

```cpp
if(a[1]==a[n]){
   cout<<1<<endl;
   continue;
}
```
2. 在剩余的情况下，如果序列的头或尾在队列里出现过两次，只需要两次。

解释：把队列里一个和头相等或者和尾相等的数与头互换或者与尾互换，再将整个队列删除，只需要两次。

代码：

```cpp
int ans1=0,ans2=0;
for(int i=1;i<=n;i++){
   if(a[i]==a[1]) ans1++;
   if(a[i]==a[n]) ans2++;
}
if(ans1>=2||ans2>=2){
     cout<<2<<endl;
     continue;
}
```
3. 在剩余的情况下，如果队列里面出现过相同的数，只需要三次。

解释：把一个数移到队头，另一个数移到队尾，再将整个队列删除，只需要三次。

代码：

```cpp
for(int i=1;i<=n;i++){
   cin>>a[i];
   ds.insert(a[i]);//使用集合
}
if(ds.size()<n){
   cout<<3<<endl;
   continue;
}
```
4. 在剩余的情况下，输出队列长度。

解释：一个一个删除。

代码：
```cpp
else{
   cout<<n<<endl;
   continue;
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000005];
set<int>ds;
signed main(){
   int t;
   cin>>t;
   while(t--){
      ds.clear();
      cin>>n;
      for(int i=1;i<=n;i++){
         cin>>a[i];
         ds.insert(a[i]);
      }
      if(a[1]==a[n]){
         cout<<1<<endl;
         continue;
      }
      int ans1=0,ans2=0;
      for(int i=1;i<=n;i++){
         if(a[i]==a[1]) ans1++;
         if(a[i]==a[n]) ans2++;
      }
      if(ans1>=2||ans2>=2){
         cout<<2<<endl;
         continue;
      }
      if(ds.size()<n){
         cout<<3<<endl;
         continue;
      }
      else{
         cout<<n<<endl;
         continue;
      }
   }
   return 0;
}
```

---

