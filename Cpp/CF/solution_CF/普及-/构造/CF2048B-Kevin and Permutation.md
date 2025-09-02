# Kevin and Permutation

## 题目描述

### 题意
给定 $n,k$，构造一个长度为 $n$ 序列 $a$ 使得
$$\sum^{n-k+1}_{i=1}\left(\min^{i+k-1}_{j=i}a_j\right)$$
的值尽量小。其中，$a$ 满足各项均不相等。

请注意，共有 $t$ 次询问。

## 说明/提示

$1\le t\le10^3,1\le k\le n\le10^5$。

保证所有数据中 $\sum n\le 10^5$。

## 样例 #1

### 输入

```
3
4 2
6 1
8 3```

### 输出

```
3 1 2 4
5 2 1 6 4 3
4 6 2 8 3 1 5 7```

# 题解

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF2048B Kevin and Permutation](https://www.luogu.com.cn/problem/CF2048B)

## 题意简述

构造一个长度为 $n$ 的排列，最小化所有长度为 $k$ 的子区间的最小值之和。

## 解题思路

考虑每个长度为 $k$ 的子区间的最小值对结果的影响。为了最小化所有子区间的最小值之和，我们可以采取以下策略：

- 从最小的数 $1$ 开始，将 $1$ 放置在位置 $k$，这样前 $k$ 个区间的最小值为 $1$。
- 接着考虑数 $2$，将 $2$ 放置在位置 $2k$，这样接下来的 $k$ 个区间的最小值为 $2$。
- 以此类推，将数 $x$ 放置在位置 $xk$，使得每个位置上的数尽可能影响到最少的区间，从而最小化区间的最小值之和。

对于剩下的数，可以随意放置，因为它们的放置不会影响已经确定的最小值。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cout<<(i%k?i+n/k-i/k:i/k)<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Christmas_Defunct (赞：1)

非常有意思的贪心题。
## 题意简化
给定 $n,k$，构造一个长度为 $n$ 序列 $a$ 使得
$$\sum^{n-k+1}_{i=1}\left(\min^{i+k-1}_{j=i}a_j\right)$$
的值尽量小。其中，$a$ 满足各项均不相等。
## 题解
这道题是非常明显的贪心题。考虑以下策略：使每一个较小的 $a_t$ 被尽量多的区间覆盖，其中，每一个下标 $i$ 所代表的数 $a_i$ 在序列 $a$ 中被覆盖的次数 $f(i)=\min(i,n-i+1,k)$。

分析 $i,n-i+1,k$ 的大小，我们发现：
$$\displaystyle f_n(x)= \left\{\begin{array}{l} x,\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ x\in[1,k) \\ k,\ \ \  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ x\in[k,n-k+1] \\ n-x+1,\ \ \ \ \ \ \ x\in(n-k+1,n] \end{array}\right.$$
故选择将正整数 $x$ 放在 $a_{xk}(x\le \lfloor\dfrac{n}{k}\rfloor)$ 即可。

（补充）此时，我们便得到了最小值的表达式：
$$\sum^{n-k+1}_{i=1}\left(\min^{i+k-1}_{j=i}a_j\right)=\sum_{x=1}^{\lfloor\frac{n-k+1}{k}\rfloor}xk+\left\lceil\frac{n-k+1}{k}\right\rceil\cdot\left(n-k+1-k\cdot\left\lfloor\frac{n-k+1}{k}\right\rfloor\right)$$
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[100005];

signed main() {
	int t;
	cin >> t;
	while (t--) {
		memset(a, 0, sizeof a);
		int n, k, tmp_l, tmp_r;
		cin >> n >> k;
		tmp_l = 1, tmp_r = n;
		for (int i = 1; i < k; i++) a[i] = tmp_r--;
		for (int i = k; i <= n; i++) {
			if (i % k == 0) a[i] = tmp_l++;
			else a[i] = tmp_r--;
		}
		for (int i = 1; i <= n; i++) cout << a[i] << ' ';
		puts("");
	}
	return 0;
}
```

---

## 作者：Wind_love (赞：0)

## 思路
题目要求用 1 到 $n$ 的所有数构造一个序列，使得每一个长度为 $k$ 的子区间内最小值的和最小。  
我们可以想到一个思路，即每 $k$ 个，放入当前可放入的最小值。  
想让需要放入时可放入的值尽量小，则我们让其他数尽量大。  
所以我们可以，使用两个指针，为当前可放入最大值，另一个为最小值，每 $k$ 个中放入当前可放入最小值，其他的放入最大值即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		int l=1,r=n;
		for(int i=1;i<=n;i++){
			if(i%k==0)cout<<l<<" ",l++;
			else cout<<r<<" ",r--;
		}
		cout<<"\n";
	}
	return 0;
}

---

## 作者：Wide_Master (赞：0)

## 题意

 $t$ 组数据。

构造一个由 $1\sim n$ 组成的全排列。使得所有长度为 $k$ 的子串的最小值之和最小化。

## 分析

由于是要最小值最小化，那么我们就要让一个较小的值影响到较多的区间。我们发现，如果一个小的数字放在 $k$ 的倍数的位置上，那么一个较小的数就能影响到较多的区间。其他数字可以随便填，因为不影响答案。注意多测清空。

所以我们可以将 $1$ 放在第 $k$ 个位置上，$2$ 放在第 $2k$ 个位置上。也就是说，$x$ 放在第 $xk$ 个位置。

## 代码

```cpp
//By xiaozhou001
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            if(i%k==0){
                cout<<i/k<<endl;
            }else{
                cout<<i+n/k-i/k<<endl;
            }
        }
    }
    return 0;
}
``````

---

## 作者：All_Wrong_Answer (赞：0)

[原题](https://codeforces.com/problemset/problem/2048/B)

## 题目大意：

构造一个排列 $n$ 使得所有长度为 $k$ 的子区间中最小值的和最小。

## 思路：

**贪心**，先找规律，假设 $n=6$ 吧：

$k=1$：```1 2 3 4 5 6``` 是一组合适的方案。

$k=2$：```6 1 5 2 4 3``` 是一组合适的方案。

$k=3$：```6 5 1 4 3 2``` 是一组合适的方案。

$k=4$：```6 5 4 1 3 2``` 是一组合适的方案。

$k=5$：```6 5 4 3 1 2``` 是一组合适的方案。

$k=6$：```6 5 4 3 2 1``` 是一组合适的方案。

观察，发现一个小的数 $q$ 可以将前面 $k-1$ 个子区间的最小值和后面 $1$ 个子区间的最小值变为 $q$。

例如，在上文 $k=3$ 的情况，比较小的数 $1$ 就将它前面的 $k-1$ 也就是 $2$ 个子区间的最小值变为了 $1$，即区间 ```6 5 1```、```5 1 4``` 和它后面的 $1$ 个子区间的最小值变为了 $1$，即子区间```1 4 3```。

那么就可以进行贪心了，每次将当前最大的 $k-1$ 个数直接输出，在后面跟进一个当前最小的数，把前面含有大数的子区间的最小值变小即可。 

## 完整代码：


```cpp
#include <queue>
#include <iostream>
using namespace std;
priority_queue<int>q;
int main(){
	int t;
	int x,y;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>x>>y;
		while(!q.empty()) q.pop();//多测要清空！ 
		for(int j=1;j<=x;j++){
			q.push(j);
		}
		int us=0,f=0;
		while(1){
			if(us==q.size()) break;//所有数都已经用过了 
			for(int j=1;j<y;j++){
				cout<<q.top()<<" ";
				q.pop();
				if(us==q.size()){
					f=1;
					break;
				}
			}//直接输出当前最大的k-1个数 
			if(f==1) break;
			us++;
			cout<<us<<" ";//输出当前最小的数，覆盖前面的子区间 
			if(us==q.size()) break;
		}
		cout<<endl;
	}
	return 0;
}

```

[CF](https://codeforces.com/contest/2048/submission/298740910) 上可过。

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2048B)

## Statement

求对于长度为 $n$ 的排列 $p$，问哪种排列方式可以使 $p$ 中任意长度为 $k$ 的连续子段的最小值之和最小。

## Solution

不难发现，要使每一长为 $k$ 的段最小值之和最小，只需要在 $k$ 的正整数倍的位置依次放 $1,2,\dots,\lfloor{\frac{n}{k}}\rfloor$，其余位置如何填都可以保证最小。

> 证明：
>
> 对于一段区间的开头 $\forall p \in [1,n - k + 1]$，我们所取的区间范围为 $[p,p + k - 1]$，无论 $p$ 取其值域内的任意一个值，由于区间的覆盖长度为 $k$，一定会有 $k$ 的一个正整数倍数属于所取区间，换一种说法，总是存在系数 $t \in \mathbb{N_{+}}$，使得 $tk \in [p,p + k - 1]$，因此，我们选择在 $tk \leq n$ 的位置依次放置 $1,2,\dots,\lfloor{\frac{n}{k}}\rfloor$，对于 $\forall{[p,p + k - 1]}$，定能在区间内取到相对最小值。

可能证明的不是很详细，期望读者能够理解就行。

## code

[代码 click here](https://codeforces.com/contest/2048/submission/297371249)

---

## 作者：_lmh_ (赞：0)

考虑一个数最多能“管辖”多少个区间，也就是说，以其为最小值的区间有多少个。

显然一个数字最多只能是 $k$ 个区间的最小值，所以我们要尽可能让小的数取满 $k$。考虑如何构造来取到这个下界。

给出一个构造方案：在 $1\le xk\le n(x\in \Z)$ 的位置上放 $x$，其余位置放更大的数。显然右端点为 $xk\sim (x+1)k-1$ 的区间最小值都是 $x$，因此我们成功取满了这个最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,k,a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for (int i=1;i<=n;++i){
			if (i%k==0) cout<<i/k<<' ';
			else cout<<n-i+i/k+1<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

