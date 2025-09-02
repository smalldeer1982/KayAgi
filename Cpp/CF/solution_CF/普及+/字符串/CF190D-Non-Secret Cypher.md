# Non-Secret Cypher

## 题目描述

Berland starts to seize the initiative on the war with Flatland. To drive the enemy from their native land, the berlanders need to know exactly how many more flatland soldiers are left in the enemy's reserve. Fortunately, the scouts captured an enemy in the morning, who had a secret encrypted message with the information the berlanders needed so much.

The captured enemy had an array of positive integers. Berland intelligence have long been aware of the flatland code: to convey the message, which contained a number $ m $ , the enemies use an array of integers $ a $ . The number of its subarrays, in which there are at least $ k $ equal numbers, equals $ m $ . The number $ k $ has long been known in the Berland army so General Touristov has once again asked Corporal Vasya to perform a simple task: to decipher the flatlanders' message.

Help Vasya, given an array of integers $ a $ and number $ k $ , find the number of subarrays of the array of numbers $ a $ , which has at least $ k $ equal numbers.

Subarray $ a[i...\ j] (1<=i<=j<=n) $ of array $ a=(a_{1},a_{2},...,a_{n}) $ is an array, made from its consecutive elements, starting from the $ i $ -th one and ending with the $ j $ -th one: $ a[i...\ j]=(a_{i},a_{i+1},...,a_{j}) $ .

## 说明/提示

In the first sample are three subarrays, containing at least two equal numbers: (1,2,1), (2,1,2) and (1,2,1,2).

In the second sample are two subarrays, containing three equal numbers: (1,2,1,1,3) and (1,2,1,1).

In the third sample any subarray contains at least one 1 number. Overall they are 6: (1), (1), (1), (1,1), (1,1) and (1,1,1).

## 样例 #1

### 输入

```
4 2
1 2 1 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
5 3
1 2 1 1 3
```

### 输出

```
2```

## 样例 #3

### 输入

```
3 1
1 1 1
```

### 输出

```
6```

# 题解

## 作者：__yrq__ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF190D)

## 题目分析：

首先我们考虑 $O(n^{2})$ 的暴力做法，但是很明显它一定会超时，因为 $n$ 是小于等于 $4 \times 10^{5}$ 的。

然后我们考虑使用双指针来优化。

我们先枚举区间的左端点，然后我们维护满足条件的最靠左的区间右端点。

因为 $a_{r}$ 在区间 $[l,r]$ 中出现的次数 $\ge k$，所以区间 $[l,r+1] \sim [l,n]$ 也一定是满足条件的。

那么对于当前的区间左端点 $l$，可以对答案带来 $n-r+1$ 的贡献，最后输出答案即可。

时间复杂度为 $O(n)$。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int>mp;
int n,k,a[400005],r=1,s1=0;
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int l=1;l<=n;l++)
    {
        while(r<=n)
        {
        	if(mp[a[r]]+1>=k) break;
        	mp[a[r++]]++;
		}
        s1+=n-r+1;
        mp[a[l]]--;
    }
    cout<<s1<<endl;
    return 0;
}
```

---

## 作者：npqenqpve (赞：2)

### 思路：
枚举左端点 $i-1$，维护扔掉 $i-1$ 后大于等于出现次数 k 的数的个数 $cnt$。

显然右端点 $j$ 只会右移，当 $cnt=0$ 时一直往右移，每移以为可能改变的只有 $a_j$ 这个数的出现次数。

知道出现 $a_j$ 出现次数大于等于 $k$，说明 $i$ 这个左端点对答案有 $n-j+1$ 个贡献，直接统计即可。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[(int)(1e6+10)];
map<int,int>m;
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int i=1,j=0,cnt=0,ans=0;
	while(i<=n)
	{
		m[a[i-1]]--;
		if(m[a[i-1]]==k-1) cnt--;
		if(cnt>0)
		{
			ans+=(n-j+1);
			i++;
			continue;
		}
		while(j<=n&&cnt<1)
		{
			j++;
			m[a[j]]++;
			if(m[a[j]]==k)
			{
//				cout<<i<<" "<<j<<"\n";
				cnt++;
				ans+=(n-j+1);
				break;
			}
		}
		i++;
	}
	cout<<ans;
}
```

---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意

给定一个长度为 $n$ 的序列，请问有多少子段，使得这个子段里出现最多的数的出现次数大于 $k$。

## 思路

首先我们看看数据， $n \le 4 \cdot 10 ^ 5$，可以发现，$O(n ^ 2)$ 的时间复杂度是明显过不了的，考虑 $O(n \log n)$，或者 $O(n)$。

我们先考虑 $O(n \log n)$ 的时间复杂度，明显需要使用二分或者倍增，但是我们二分明显是 $O(n ^ 2 \log n)$，倍增不考虑。

再来考虑 $O(n)$ 的时间复杂度，首先，我们可以发现，如果当前字段 $[l, r]$ 满足题目的条件，那么 $[l, r + 1]$，$[l, r + 2]$，$\dots$， $[l, n]$，都会满足条件；

很明显可以看出双指针，我们看看这个序列在左端点移动时，右端点是否会减少，明显不会，也满足双指针的要求，尝试双指针；

再来考虑怎么判断子段是否满足条件，首先我们用一个桶来存储出现次数，在子段不满足条件时，我们移动右指针，每次桶记录，我们用一个值记录，来看是否满足条件的，有就记录答案，同时退出循环，没有就继续；

那么再来考虑移动左指针的情况，移动左指针时，桶自然也要记录，但我们怎么知道什么时候子段会由满足条件变为不满足，我们发现，在桶最少满足条件的情况为刚好出现 $k$ 次，那么减去后就会变为 $k - 1$ 次，那我们就可以在减去左指针时看是否桶正好为 $k - 1$ 次，那么这个我们记录的值就减一。

我们还要注意一些细节，$a_i \le 10^9$，我们需要离散化或者使用 map；

## Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 4e5 + 5;

int n, k, a[N], ans, cnt;
map <int, int> sum; 

signed main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int l = 1, r = 0; l <= n && r <= n; l++){ // 在这里就已经移动了左指针
		for(; cnt == 0 && r < n; ){ // cnt 判断是否满足条件
			r++; // 移动左指针
			sum[a[r]]++; // 桶自然要更新
			if(sum[a[r]] >= k){ // 满足条件
				cnt++;
				break;
			}
		}
		if(cnt){ 
			ans += (n - r + 1); // 满足条件，把所有以 l 为左端点可以满足的答案全部加上
		}
		sum[a[l]]--; 
		if(sum[a[l]] == k - 1){ // 由满足条件变为不满足
			cnt--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：hjsxhst2022 (赞：1)

题意不用看了，裸题。
### 思路
从小到大，依次枚举左端点，找对应的最左区间右端点，然后计算最大值。时间复杂度为 $O(n)$。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[1000001];//开long long！！！
map<long long,long long>qwq;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	long long awa=1,j=0,cnt=0,qaq=0;
	while(awa<=n){
		qwq[a[awa-1]]--;
		if(qwq[a[awa-1]]==k-1)
		cnt--;
		if(cnt>0){
			qaq+=(n-j+1);
			awa++;
			continue;
		}
		while(j<=n&&cnt<1){
			j++;
			qwq[a[j]]++;
			if(qwq[a[j]]==k){
				cnt++;
				qaq+=(n-j+1);
				break;
			}
		}
		awa++;
	}
	cout<<qaq;
}
```

---

## 作者：hinin (赞：0)

典型的双指针/单调队列

题目要求我们计算出数组中所有满足条件的连续子数组的数量。具体来说，我们需要找出所有的子数组，其中至少有一个数字的出现次数大于等于给定的 $k$。

#### 解题思路

我们可以使用双指针（滑动窗口）的方法来高效地解决这个问题。具体步骤如下：

1.  **定义指针和数据结构**：
    
    *   使用两个指针 $l$ 和 $r$ 分别表示当前子数组的左右边界。
    *   使用一个哈希表（或数组）来记录当前窗口内每个数字的出现次数。
2.  **扩展右指针**：
    
    *   逐步增加右指针 $r$，并更新当前数字的计数。
    *   检查当前窗口内是否存在某个数字的出现次数达到 $k$。
3.  **收缩左指针**：
    
    *   一旦发现窗口内有数字的出现次数达到 $k$，我们可以计算从 $l$ 到 $r$ 的所有子数组。
    *   然后，尝试移动左指针 $l$，并更新计数，直到窗口内不再满足条件。
4.  **计算结果**：
    
    *   每次找到满足条件的窗口时，计算从 $l$ 到 $r$ 的所有子数组数量，并累加到结果中。

#### 复杂度分析

*   **时间复杂度**：$O(n)$，每个指针最多遍历数组一次。
*   **空间复杂度**：$O(n)$，用于存储数字的计数。

这种方法有效地利用了滑动窗口的特性，避免了暴力解法的高时间复杂度.

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define ll long long
 
using namespace std;

const int N = 4e5 +5;

bool flg = false; 
int n, k, l = 1, r, a[N];
ll ans; 
map<int, int> Map;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin  >> n >> k;
	for(int i = 1; i <= n; i++) { cin>>a[i]; }

	while(r <= n){
		if(flg){
			ans += n - r + 1;
			if(--Map[a[l++]] == k - 1) { flg = false; }
		} else {
			if(++Map[a[++r]] == k) { flg = true; }
		}
	}

	cout << ans << endl; 

	return 0;
}
```

---

