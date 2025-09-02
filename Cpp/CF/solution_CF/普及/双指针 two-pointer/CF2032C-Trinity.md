# Trinity

## 题目描述

给定 $n$ 个元素的数组 $a_1, a_2, \ldots, a_n$。 

你可以进行如下操作任意次（包括 0 次）：

- 选择两个下标 $i, j\ (1 \le i, j \le n)$，令 $a_i := a_j$。

现请你求出使数组 $a$ 满足下列条件所需的最少操作次数。

- 对每个下标三元组 $(x, y, z)\ (1 \le x, y, z \le n, x \neq y, y \neq z, z \neq x)$ ，都有以 $a_x, a_y, a_z$ 为长度的三条线段可以构成一个非退化三角形。

## 说明/提示

对第一组样例，一种可能的操作方式如下：

- 令 $a_1 := a_4 = 4$，数组变为 $[4, 2, 3, 4, 5, 6, 7]$。
- 令 $a_2 := a_5 = 5$，数组变为 $[4, 5, 3, 4, 5, 6, 7]$。
- 令 $a_7 := a_4 = 4$，数组变为 $[4, 5, 3, 4, 5, 6, 4]$。

可以证明最终的数组符合条件，并且 3 次操作是最少的。

对第二组样例，我们令 $a_1 := a_2 = 3$ 使数组变为 $a = [3, 3, 2]$ 即可。

对第三组样例，既然 $3, 4, 5$ 已经可以构成三角形的三条边，我们并不需要进行任何操作。

## 样例 #1

### 输入

```
4
7
1 2 3 4 5 6 7
3
1 3 2
3
4 5 3
15
9 3 8 1 6 5 3 8 2 1 4 2 9 4 7```

### 输出

```
3
1
0
8```

# 题解

## 作者：Drifty (赞：11)

### Preface

赛场解法和官解写法有一点不一样，发一篇。

### Solution

我们注意到本题的要求与下标无关，只与具体的 $a_i$ 的值有关，因此直接考虑排序。

我们对 $a$ 进行升序排序。此时我们考虑枚举每个 $a_i(1 \le i < n)$ 作为修改完后序列的最小值，那么显然次小值即为 $a_{i + 1}$，此时我们再去算序列中可以存在的最大值，也就是最后一个使得 $a_i + a_{i + 1} < a_j$ 的 $j$，直接二分查找就好，在 $j$ 之后的 $a_k$ 都直接改成 $a_j$，而对于在 $i$ 之前的 $a_k$ 也都改成 $a_j$ 就满足了要求。此时对于这个 $i$ 我们共需要 $n - j + i - 1$ 次操作。

那么我们对于每个 $i$ 求操作次数取个 $\min$，做完了。

时间复杂度 $\mathcal{O}(n\log n)$，可以通过测试。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int T; cin >> T;
    for (int n; T --; ) {
        cin >> n;
        vector <int> a(n);
        for (int i = 0; i < n; i ++) cin >> a[i];
        sort (a.begin(), a.end());
        int ans = n - 1;
        for (int i = 0; i + 1 < n; i ++) {
            int x = lower_bound(a.begin(), a.end(), a[i] + a[i + 1]) - a.begin();
            ans = min(n - x + i, ans);
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：fishing_cat (赞：7)

[传送门](https://codeforces.com/contest/2032/problem/C)

### 做法

对于题目的要求，不会被修改的一定是排完序后的有序数列中连续的一段。由小学二年级的数学直觉可知，假设连续段为 $a$，那么一定会满足 $a_{min} + a_{min+1} < a_{max}$。

那么，现在就非常好做了。排完序后，枚举最大值 $a_{max}$，二分 $a_{min}$，看是否满足 $a_{min} + a_{min+1} < a_{max}$，则选此时的最大值时的最小修改次数就是 $n - max + min - 1$。最后统计出最小值即可。

单次时间复杂度 $O(n \log n)$。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
/*快读省了*/
ll t, n, a[200100], ans;

int main() {
	read(t);
	while (t--) {
		ans = 2e18;
		read(n);
		for (int i = 1; i <= n; i++) 
			read(a[i]);
		sort(a+1, a+n+1); // 排序
		for (int i = 2; i <= n; i++) { // 枚举最大值
			ll l = 1, r = i;
			while (l < r) { // 二分最小值
				ll mid = (l + r) >> 1;
				if (a[mid] + a[mid+1] > a[i]) {
					r = mid;
				} else l = mid + 1;
			}
			ll res = n - i + r - 1;
			ans = min(ans, res);
		}
		cout << ans << "\n";
	}
	return 0;// 完结撒花 ！
}
```

---

## 作者：__little__Cabbage__ (赞：3)

## Solution

赛时先想到排序后从左往右贪心，不过 WA 了。

hack：`1 1 5 5 5 5 5 20 20`，应该输出 `3`。

所以不一定操作最小的就是最优的。

对于每个本来就合法的最长区间计算答案（固定右端点），则不在这个区间内的一定要操作，设这个区间为 $[l,r]$，证明：

- 若 $a_{l-1}$ 可以不操作，则 $a_{l-1} + a_l > a_r$，与「固定右端点本来就合法的最长区间」不符。
- 由于固定右端点，所以 $a_{r+1}$ 是默认必须操作的。

然后这个区间拿个双指针去维护即可。

正确性可以感性理解一下，这样我们枚举到了固定右端点的每个合法最大区间，所以不会存在比这个区间更优的区间。

时间复杂度 $O(n)$。

注：关于操作，每次在允许的数的范围内随便选一个就行，这个不重要，总之对于一个数一次操作一定能使其合法

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;

const int MAXN=2e5+5;
int n,a[MAXN];

il void solve()
{
    cin>>n;
    rep(i,1,n) cin>>a[i];
    sort(a+1,a+n+1);

    int ans=n-1,l=1;
    rep(r,2,n)
    {
        while(a[r]>=a[l]+a[l+1]) ++l;
        ans=min(ans,n-(r-l+1));
    }

    cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int T; cin>>T; while(T--) solve();
    return 0;
}
```

---

## 作者：RainySoul (赞：2)

注意到，仅有**最小的两个数相加大于最大的那个数**了这个序列才是合法的。

先将整个数组排序。

考虑枚举你修改了前 $i$ 大的值，这时候可以直接二分求出现在还需要修改前 $l$ 小的值。

$i+l$ 就是总修改次数，枚举 $i$，对 $i+l$ 取 $\min$ 得到答案。

时间复杂度 $O(n \log n)$。

AC code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=200010;
int T,n,a[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+1+n);
        int ans=inf;
        for(int i=n;i>=1;i--){
            int maxn=a[i];//[i+1,n]这段已经被改得全部合法了
            int l=1,r=n;
            while(l<=r){
                int mid=(l+r)>>1;
                if(a[mid]+a[mid+1]>maxn)r=mid-1;
                else l=mid+1;
            }//[1,i-1]这段是需要修改的
            ans=min(ans,n-i+l-1);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：_mi_ka_ (赞：2)

## 题目描述

给定长度为 $n$ 的序列 $a$，修改其中的一些数使得对于序列 $a$ 中的任意三个数都能组成三角形，即两短边之和大于最长边。求出最少修改的数的个数。

## 解题思路

考虑到如果一个序列的最小的两个数之和大于第三个数，那么这个序列一定合法。那么进行修改的时候尽量修改最小连续的几个（或 $0$ 个）数和最大连续的几个（或 $0$ 个）数，**使得中间没有被修改的序列为一个合法序列**，被修改的数只需修改成中间这个合法序列中的数即可使整个序列合法。

那么这个问题就转化成了：**找出 $a$ 排序后的最长的连续合法子序列**，若这个序列的长度为 $k$，则答案就是 $n-k$。

寻找这个连续序列的长度，考虑排序后**双指针**。令 $l$ 和 $r$ 分别为这个序列的首尾，若 $a_l+a_{l+1}>a_r$ 则此序列合法，此时 `r++`，判断将 $r$ 右移后是否还合法，合法继续右移，不合法就用合法序列的长度更新答案，然后右移 $l$ 继续判断。特别地，当 $r-l<3$ 时，此序列组不成三元组，无法判断合法，此时必须将 $r$ 右移。

此外，如果整个序列都不存在合法的三元组，此时只需要选择两个数不变，剩下的数都修改为这两个数中较大的那个数即可满足合法，答案为 $n-2$。

排序时间复杂度 $O(n\log n)$，双指针时间复杂度 $O(n)$，总时间复杂度 $O(n\log n)$。

## AC Code

```cpp
#include<iostream>
#include<algorithm>
#define N 200005
using namespace std;
int T,n;
int a[N];
int re()//防止作弊不放快读快写
void wr(int x)
signed main()
{
	T=re();
	while(T--)
	{
		n=re();
		for(int i=1;i<=n;i++)
			a[i]=re();
		sort(a+1,a+n+1);
		int maxx=0;//答案 
		int l=1,r=3;//保证区间长度
		while(r<=n)
		{
			while((a[l]+a[l+1]>a[r]||r-l<3)&&r<=n)//合法或者是长度小于 3 则 r 右移 
				r++;
			if(a[l]+a[l+1]>a[r-1])//合法序列：l~r-1，长度为 r-l 
				maxx=max(maxx,r-l);
			l++;//不合法 l 右移
		}
		if(!maxx)
			wr(n-2),putchar('\n');
		else
			wr(n-maxx),putchar('\n');
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

先写了个贪心，然后发现[假了](https://codeforces.com/contest/2032/submission/298056090)。

再看一下数据发现这是错的，考虑别的做法。

---

根据小学数学知识，三角形两边之和大于第三边，那么这个序列满足条件时，最小值和次小值之和必定大于最大值，那么我们就得到了以下做法：

- 排序，方便计算。
- 对于每一个 $i\leq n-1$，求出一个 $s=a_i+a_{i-1}$，这个就是三角形较短的 $2$ 边之和，再二分找一下这个序列里有多少个比 $s$ 小的数，即不满足条件的（需要更改的）数。
- 设上一步中二分得到的位置为 $res$，那么得到了 $[i,res]$ 就可以算出更改的长度，对所有这些长度取个 $\max$ 即可。
（容易证明的是 $res>i$）

## Code
[Link](https://codeforces.com/problemset/submission/2032/298058630)

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18523933) 中阅读。

#### 题意

给一个数组 $a$，每次可以任选 $(i,j)$ 将 $a_i$ 赋值为 $a_j$。问满足下述条件的最小操作次数。

- 对每一个没有相同元素的三元组 $(i,j,k)$，$a_i,a_j,a_k$ 作为一个三角形的三条边是合法的。

#### 分析

排个序，注意到最容易不合法的地方是 $(1,2,n)$ 组合，如果这个组合合法，那整体肯定合法。

那我们有两种选择：把最小值改大、把最大值改小。

怎么选？我们不妨枚举选了几个把最大值改小。由于我们的更改肯定会一步到位，那改成了什么其实已经无所谓了，反正肯定只花费了一步。

枚举把几个最大值改小之后，可以直接二分出最小值改到了哪里恰好合法。注意到二分出的位置是单调递减的，所以双指针也行。

---

## 作者：Milky_Cat (赞：0)

考虑我们怎么判断三角形。

我们知道，三角形两边之和大于第三边，贪心可以发现，短的两条边之和大于最长边才能组成不退化的三角形。

于是我们把边进行排序，每次枚举两条相邻的边，二分严格小于这两条边长度之和的最长边统计答案就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n, a[200005];
int qry(int x){//二分
	int l = 1, r = n, ans = n;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (a[mid] < x)
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + 1 + n);
		int ans = 0;
		for (int i = 1; i < n; i++)//枚举两条相邻边
			ans = max(qry(a[i] + a[i + 1]) - i + 1, ans);
		cout << n - ans << "\n";
	}
	return 0; 
}
```

---

