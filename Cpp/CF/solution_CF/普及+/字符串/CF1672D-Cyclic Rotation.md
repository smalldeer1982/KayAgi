# Cyclic Rotation

## 题目描述

There is an array $ a $ of length $ n $ . You may perform the following operation any number of times:

- Choose two indices $ l $ and $ r $ where $ 1 \le l < r \le n $ and $ a_l = a_r $ . Then, set $ a[l \ldots r] = [a_{l+1}, a_{l+2}, \ldots, a_r, a_l] $ .

You are also given another array $ b $ of length $ n $ which is a permutation of $ a $ . Determine whether it is possible to transform array $ a $ into an array $ b $ using the above operation some number of times.

## 说明/提示

In the first test case, we can choose $ l=2 $ and $ r=5 $ to form $ [1, 3, 3, 2, 2] $ .

In the second test case, we can choose $ l=2 $ and $ r=4 $ to form $ [1, 4, 2, 2, 1] $ . Then, we can choose $ l=1 $ and $ r=5 $ to form $ [4, 2, 2, 1, 1] $ .

In the third test case, it can be proven that it is not possible to transform array $ a $ to $ b $ using the operation.

## 样例 #1

### 输入

```
5
5
1 2 3 3 2
1 3 3 2 2
5
1 2 4 2 1
4 2 2 1 1
5
2 4 5 5 2
2 2 4 5 5
3
1 2 3
1 2 3
3
1 1 2
2 1 1```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：Kzh_root (赞：12)

##### CF1672D Cyclic Rotation
观察题目后，我们发现：因为需要记录下标与比较大小，如果尝试直接将数组 $a$ 变换到 $b$，那么将会使得问题的解决变复杂。于是，我们可以尝试将数组 $b$ 变换到 $a$。
观察题目要求的操作：
> 选择两个数 $l,r$ 满足 $1\le l< r\le n$ 并且 $a[l]=a[r]$ ，将 $a[l...r]$ 替换为 $a[l+1,l+2,...r,l]$。

这反映到从 $b$ 变换到 $a$ 的过程中时，就是将两个紧挨着的相同的数，其中一个数往左调到对应 $a$ 中的一定位置上去。
那么，我们尝试从右到左对 $b$ 进行处理。我们可以将 $b$ 中的连续相同元素暂时记录下来。我们将在之后使用它们匹配 $a$ 中的相关元素。那怎么记录呢？储存它们的个数即可，并且对于两个相邻的相同的数，只计算一次贡献。同时对于 $a$ 的匹配，我们也将是向左匹配。
我们可以用双指针模拟这个过程。
参考代码如下：
```
#include <bits/stdc++.h>

using namespace std;

const long long maxN=200010;

int t;
int n;
int a[maxN]={0},b[maxN]={0};
map<int,int>cnt;
bool flag=0;

int main()
{
	cin>>t;
	while(t--)
	{
		cnt.clear();
		flag=true;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i]; 
		int ai=n,bi=n;
		b[n+1]=0;//防止一些毒瘤数据
		while(bi)
		{
			if(ai&&bi&&a[ai]==b[bi])
			{
				ai--,bi--;
				continue;
			}
			if(b[bi]==b[bi+1])
				cnt[b[bi--]]++;
			else if(cnt[a[ai]])
				cnt[a[ai--]]--;
			else
			{
				flag=false;
				break;
			}
		}
		cout<<(flag?"YES":"NO")<<'\n';
	}
	return 0;
}
```
这道题目的分析也就到这里了，欢迎各位神犇巨巨指出不足提出建议！

---

## 作者：Alex_Wei (赞：6)

很奇妙的一道题。

考虑依次归位 $b_1\sim b_n$，假设当前需要归位 $b_i$，$b_1\sim b_{i - 1}$ 已经处理完毕。

- 若 $a_i \neq b_i$，我们显然需要将 $i$ 移走。因为移动到某个位置还继续向后移动，但如果移动到后面就无法移回前面。根据贪心的决策包容性，我们肯定会移动到第一个可以放置的位置。
- 若 $a_i = b_i$，我们一定不会将 $i$ 移走。否则，考虑下一个等于 $a_i$ 的位置 $j$，我们需要将 $i\sim j - 1$ 的数全部向后移动。根据贪心的决策包容性，不移动一定比移动更优。

因此，不断执行 $[i, j]$，其中 $j$ 为第一个大于 $i$ 且 $a_j = a_i$ 的位置，直到 $a_i = b_i$ 或不存在 $a_j = a_i(j > i)$。若出现前者，则 $b_i$ 归位，继续考虑 $b_{i + 1}$。若出现后者则无解。

加速上述过程。过程中，我们不需要真的找到后继并移动。记录 $cnt_i$ 表示移动的 $i$ 的数量，并维护指针 $j$ 表示当前尝试匹配 $a_j = b_i$。若 $a_j\neq b_i$，则令 $cnt_{a_j}$ 加 $1$，且 $j$ 加 $1$，直到满足条件或 $j > n$（无解），此时

- 若 $cnt_{a_j} > 0$，则我们让一个向后移动的 $a_j$ 在 $a_j$ 前停下，代替 $a_j$ 匹配 $b_i$，即 $cnt_{a_j}$ 减 $1$。
- 否则 $a_j$ 匹配 $b_i$，$j$ 加 $1$。

然后令 $i$ 加 $1$ 即可。时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
constexpr int N = 2e5 + 5;
int n, a[N], b[N], cnt[N];
void solve(int T) {
  cin >> n, b[n + 1] = 0;
  for(int i = 1; i <= n; i++) cnt[i] = 0;
  for(int i = 1; i <= n; i++) a[i] = read();
  for(int i = 1; i <= n; i++) b[i] = read();
  int pt = 1;
  for(int i = 1; i <= n; i++) {
    while(b[i] != a[pt] && pt <= n) cnt[a[pt++]]++;
    if(pt > n) return puts("NO"), void();
    if(cnt[a[pt]]) cnt[a[pt]]--;
    else pt++;
  }
  puts("YES");
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T;
  cin >> T;
  while(T--) solve(T);
  return 0;
}
```

---

