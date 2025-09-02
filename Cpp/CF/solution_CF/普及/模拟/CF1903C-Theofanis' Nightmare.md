# Theofanis' Nightmare

## 题目描述

Theofanis easily gets obsessed with problems before going to sleep and often has nightmares about them. To deal with his obsession he visited his doctor, Dr. Emix.

In his latest nightmare, he has an array $ a $ of size $ n $ and wants to divide it into non-empty subarrays $ ^{\dagger} $ such that every element is in exactly one of the subarrays.

For example, the array $ [1,-3,7,-6,2,5] $ can be divided to $ [1] [-3,7] [-6,2] [5] $ .

The Cypriot value of such division is equal to $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i $ where $ k $ is the number of subarrays that we divided the array into and $ \mathrm{sum}_i $ is the sum of the $ i $ -th subarray.

The Cypriot value of this division of the array $ [1] [-3,7] [-6,2] [5] = 1 \cdot 1 + 2 \cdot (-3 + 7) + 3 \cdot (-6 + 2) + 4 \cdot 5 = 17 $ .

Theofanis is wondering what is the maximum Cypriot value of any division of the array.

 $ ^{\dagger} $ An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 说明/提示

In the first test case, to get the maximum Cypriot value we divide the array into $ [1][-3][7][-6][2][5] $ which gives us: $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i = 1 \cdot 1 + 2 \cdot (-3) + 3 \cdot 7 + 4 \cdot (-6) + 5 \cdot 2 + 6 \cdot 5 = 32 $

Similarly, in the second test case we divide the array into $ [2][9,-5,-3] $ which gives us $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i = 1 \cdot 2 + 2 \cdot (9 + (-5) + (-3)) = 4 $ .

## 样例 #1

### 输入

```
4
6
1 -3 7 -6 2 5
4
2 9 -5 -3
8
-3 -4 2 -5 1 10 17 23
1
830```

### 输出

```
32
4
343
830```

# 题解

## 作者：引领天下 (赞：13)

题意：

将一个长度为 $n$ 的序列划分为若干段，最大化 $\sum_{i=1}^k{i\times s_i}$，其中 $s_i$ 表示第 $i$ 段的元素和。

做法：

DP，显然是该从尾部开始往头部做，因为后面的系数更大。做的过程中这个 $i$ 的系数很麻烦，因为我们不知道最后到底分出来了几段；所以我们就不乘了，而是改成累加，即每多一段，就把后面的所有全部加一遍，也就相当于补全了后面缺少的系数。

设 $f_i$ 为 $n$ 到 $i$ 的答案，令 $s$ 为后缀和，则状态转移方程为

$$f_i=\max(f_{i+1}+a_i,f_{i+1}+s+a_i)$$

分别表示了 $a_i$ 接在后面的一段上，和单独开一段的答案。

最后 $f_1$ 就是答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[100005],f[100005];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i],f[i]=-(1ll<<60);
        f[n]=a[n];
        int s=a[n];
        for(int i=n-1;i;i--)f[i]=max(f[i+1]+a[i],f[i+1]+s+a[i]),s+=a[i];
        cout<<f[1]<<'\n';
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：5)

给出一个贪心的做法。

从我的思路讲起。

首先，我们分析一下样例，发现断开的地方是 `1/-3/7/-6/2/5`，和 `2/9,-5,-3`。

由此，我们可以猜测一个做法，后面连过来是正数就断，否则不断，然后统计贡献。

~~打一下发现过了，结束，放代码。~~

怎么可能这么水，我来说明一下。

考虑“断开”的含义，就是把后面的所有数的“基底”同时加上一，就是说加上后面的整体了。

那么如果后面整体是正的，显然加上去更优；否则，不加上去更优。

那么就可以倒着枚举，放到数组里，最后算贡献。

这个证明应该没什么问题吧。

代码就比较容易实现。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int T, n, a[N], ans, aa[N], ccnt, sum, flag, tot;
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), a[i];
		ans = ccnt = sum = tot = 0;
		flag = 0;
		for(int i = n; i >= 1; i--){
			sum += a[i];
			tot += a[i];
			flag = 1;
			if(sum > 0){
				aa[++ccnt] = tot;
				tot = 0;
				flag = 0;
			}
		}
		if(flag) aa[++ccnt] = tot;
		for(int i = 1; i <= ccnt; i++) ans += (ccnt - i + 1) * aa[i];
		printf("%lld\n", ans);
	}
	return 0;
}
```

[评测链接](https://codeforces.com/contest/1903/submission/236448565)

---

## 作者：fish_shit (赞：1)

这道题题意挺明白的，我们来考虑一下每次分段的性质。
我们可以发现每次分段的时候，分段的地方之前的答案没有变化，变化的只是之后的答案。

每次分段会使段数增加一个，也就使后面的所有段的排号（每一段的总和乘上的那个数）都会增加一。与之前的式子相比较，整个式子的答案相当于增加了分段的地方的后缀和。所以这道题分段的地方就是所有后缀和为正数的地方，答案便是原数列和加上每次分段的后缀和的总值。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
#define int long long
int a[maxn];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ans+=a[i];
		}
		int cnt=0;
		for(int i=n;i>=2;i--){
			cnt+=a[i];
			if(cnt>0){
				ans+=cnt;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：AKPC (赞：1)

考虑从哪些地方断开。

对于 $\forall i\in[1,n)$，如果考虑在 $i$ 与 $i+1$ 之间断开，则对答案的贡献为 $\sum_{j=i+1}^na_j$。

显然，如果对于 $\forall i\in[1,n)$，$\sum_{j=i+1}^na_j>0$，则断开一定比不断开更优，如果 $\sum_{j=i+1}^na_j<0$，则断开后会出现负贡献，因此选择不断开，$\sum_{j=i+1}^na_j=0$ 的时候无论是否断开都一样。

可以对 $\sum_{j=i+1}^na_j$ 维护一个后缀和并倒序枚举，存储每个值对应的段的编号，最后计算输出即可。

附上 [code](/paste/a3qa4td8)。

---
另一种解法是，我们不考虑倍数，考虑转化题意：

选择一些 $a$ 数组的后缀（其中 $a$ 本身必须被选到），这些后缀所有元素之和的和即最终答案。

显然只有后缀之和 $\geq0$ 的后缀被选到才不会做负贡献，实现也就是显然了。

附上 [code](/paste/in1tppbx)。

~~其实求的是一个东西，没有很大区别~~。

---

## 作者：MhxMa (赞：1)

# Codeforces Round 912 (Div. 2) C. Theofanis' Nightmare 题解 - 题解

## 分析

这道题要求将一个数组分成若干个非空的子数组，然后计算每个子数组的和，并用每个子数组的和乘以子数组的长度，最后求和。问题的关键在于找到一种分割方式，使得其值最大。

观察发现，我们需要在数组中找到一个位置，将数组分为两个部分，使得右半部分的和尽可能大。对于这个问题，从数组的末尾开始往前遍历是一个比较自然的想法。我们可以维护一个变量 $res$，表示当前遍历到的位置右侧的子数组的和，同时维护一个变量 $sum$，表示值的累加和。每次遍历到一个位置，都更新 $res$，并判断如果 $res$ 大于 $0$ 或者已经遍历到数组的开头，就将 $res$ 累加到 $sum$ 中。最终，$sum$ 即为所求的值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll a[N];

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=0;i<n;i++) cin>>a[i];

        ll sum=0, res=0;

        for(int i=n-1; i>=0; i--)
        {
            res += a[i];
            if(res > 0 || i == 0)
                sum += res;
        }

        cout<<sum<<endl;
    }

    return 0;
}
```

---

