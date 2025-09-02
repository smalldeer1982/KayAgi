# Summation Game

## 题目描述

Alice and Bob are playing a game. They have an array $ a_1, a_2,\ldots,a_n $ . The game consists of two steps:

- First, Alice will remove at most $ k $ elements from the array.
- Second, Bob will multiply at most $ x $ elements of the array by $ -1 $ .

Alice wants to maximize the sum of elements of the array while Bob wants to minimize it. Find the sum of elements of the array after the game if both players play optimally.

## 说明/提示

In the first test case, it is optimal for Alice to remove the only element of the array. Then, the sum of elements of the array is $ 0 $ after the game is over.

In the second test case, it is optimal for Alice to not remove any elements. Bob will then multiply $ 4 $ by $ -1 $ . So the final sum of elements of the array is $ 3+1+2-4=2 $ .

In the fifth test case, it is optimal for Alice to remove $ 9, 9 $ . Bob will then multiply $ 5, 5, 3 $ by $ -1 $ . So the final sum of elements of the array is $ -5-5-3+3+3+2=-5 $ .

## 样例 #1

### 输入

```
8
1 1 1
1
4 1 1
3 1 2 4
6 6 3
1 4 3 2 5 6
6 6 1
3 7 3 3 32 15
8 5 3
5 5 3 3 3 2 9 9
10 6 4
1 8 2 9 3 3 4 5 3 200
2 2 1
4 3
2 1 2
1 3```

### 输出

```
0
2
0
3
-5
-9
0
-1```

# 题解

## 作者：kczw (赞：3)

# 题意
共 $t$ 组数据，对于每组数据给定 $n,k,x$ 以及一个长为 $n$ 的序列 $a$。

现在有小凉和小皮对 $a$ 操作。小凉先操作并最多操作 $k$ 次，每次可以删除一个数。小皮后操作并最多操作 $x$ 次，每次可以让一个数取它的相反数。

小凉想要答案更大，小皮想要答案更小，问两人操作都是最优策略的情况下，答案为多少。
# 思路
首先最开始时 $a_i\ge1(1\le i\le n)$，可以知道，小皮每次对数操作肯定择大数对她来说最优，所以小凉的操作更需要分析。

小凉每次删数为了什么，为了使答案更大。虽然 $a_i\ge1$，但是小皮可以使 $a_i\le-1$，所以小凉删数是为了防止小皮操作。因为如果 $sum=\sum_{i=1}^na_i$，那么小皮每次操作会使答案 $sum$ 变成 $sum-2 \times a_i$，而小凉每次操作会使答案 $sum$ 变成 $sum-a_i$ 再减去其他小皮操作变小的大小。

因为小皮择大数操作，为了避免答案变得过小，小凉定是择小皮会选择的数操作，但是我们并不知道小凉操作后是否更优，我们可以枚举小凉操作的区间，然后取其最大值。
# 实现
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,k,x,a[400005];
bool cmp(int c,int d){return c>d;}
int main(){
    scanf("%d",&t);
    while(t--){
        int sum=0,an=0,s;
        scanf("%d%d%d",&n,&k,&x);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+n+1,cmp);
        int l=1,r=x;
        for(int i=1;i<=x;i++)an+=-2*a[i];
        s=an;
        for(;l<=k;l++,r++){
            s=s+a[l]-a[r+1<=n?r+1:0]*2;
            an=max(an,s);
        }
        printf("%d\n",sum+an);
    }
    return 0;
}
```

---

## 作者：_smart_stupid_ (赞：2)

# [题目](https://www.luogu.com.cn/problem/CF1920B)

## 思路：

这里 Alice 如果要删除数，那么他一定会删尽量大的，这样 Bob 只能将较小的数取反，Bob 也会尽量将较大的数取反，使总和变得尽量小，而且他会将他能取反的数都取反。举个例子，假如数组里面有大于等于 $k$ 个数，那么他会将第 $1$ 大的到第 $k$ 大的全部取反，如果数组里面不到 $k$ 个数，那么他会将剩下的所有数全部取反。

所以可以无脑枚举 Alice 删除的个数，维护删除后的总和和 Bob 取反数字的总和，具体参考滑动窗口。

**注意：答案初始化为负无穷!**

## AC Code:

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int t;
int n, k, x, a[200100];
int sum;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> k >> x;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		sort (a + 1, a + n + 1);
		sum = 0;
		for (int i = 1; i <= n; i ++) sum += a[i];
		int ans = 0;
		int tmp = 0;
		for (int i = n; i >= max(n - x + 1, 1); i --) {
			tmp += a[i];
		}
		ans = -0x3f3f3f3f;
		for (int i = 0; i <= k; i ++) {
			ans = max(ans, sum - tmp * 2);
			sum -= a[n - i];
			tmp -= a[n - i];
			if (n - i - x >= 1) tmp += a[n - i - x];
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Addicted_Game (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF1920B)

## 题目大意
先进行最多 $k$ 次操作，删去一个数；再进行最多 $x$ 次操作，将一个数取为相反数。第一次操作者想让结果总和**最大化**，第二次操作者想让结果总和**最小化**，求最终结果。

## 思路
对于第二个操作者，他会尽可能将大数取反（这样会使总和减少两倍的这个数，又因没有负数，一定会将 $x$ 次用完），所以说第一个操作者就会删去当前最大数，又因使结果变小，就枚举操作一的次数，取和最大值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,k;
int a[200005];
bool cmp(int x,int y){
	return x>y;
}
long long sum[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+a[i];前缀和优化。
		}
		long long ans=-0x7f7f7f7f;
		for(int i=0;i<=k;i++){//删除0~x个数。
			ans=max(ans,sum[n]-2*sum[min(i+x,n)]+sum[i]);//取反。
		}
		cout<<ans<<endl;
	}
	return 0; 
}
```


---

## 作者：mark0575 (赞：1)

## 思路：

首先，我们不难发现，Bob 为了让和尽量小，一定会把尽可能多、尽可能大的数乘上 $-1$。所以 Bob 一定会把能乘的数都乘上 $-1$。而把一个较小数乘上 $-1$ 对和产生的影响一定比把较大的数乘上 $-1$ 小。因此 Alice 一定会把大的数去掉。那么我们可以枚举 Alice 删除的个数 $i$，把剩下前 $\min(x,n-i)$ 个数乘上 $-1$，计算和。计算的过程可以用前缀和优化。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void read() {  }
template < typename T, typename... T2 >
inline void read(T &x, T2 &... oth)
{
	x = 0;
	int ch = getchar(), f = 0;
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
		f = 1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	if (f)
	x = -x;
	read(oth...);
}
int t;
int n,k,x;
int a[201010];
int s[201010];
signed main()
{
	read(t);
	while(t--)
	{
		read(n,k,x);
		for(int i=1;i<=n;i++)
		{
			read(a[i]);
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		{
			s[i]=s[i-1]+a[i];
		}
		int ma=-1e9;
		for(int i=n-k;i<=n;i++)
		{
			ma=max(ma,s[max(i-x,0)]-(s[i]-s[max(i-x,0)]));
		}
		cout<<ma<<"\n";
	}
	return 0;
}

```


---

## 作者：_anll_ (赞：1)

又是一道赛时卡我很久的简单题。
## 题目大意
一共 $T$ 组询问。对于每组询问，给你 $n$ 个数组成的数列，两个人共进行两次操作：第一次操作，你最多可以删除 $k$ 个整数。第二次操作，你最多选择 $x$ 个数将其变为相反数。进行第二次操作的人希望答案最小，进行第一次操作的人希望答案最大，问你在保证两人都采用最优策略的情况下的得分的多少。

## 大体思路
不妨对于两个操作分开分析。对于第二次操作，显然易见，取前 $x$ 大的数变成最小数是最优的。而对于第一个操作，显然要去掉大数才对结果贡献更大，但问题就出在不好判断具体去掉几个才能使最优，所以我们就要**暴力枚举**了。

不妨枚举第一次操作到底去掉几个数。我们拿 $sum$ 存目前的得分，每次都去判断一轮，最后取 $k+1$ 个 $sum$ 的最大值即可。

于是考虑如何维护 $sum$。不难发现，如果我们把还存在的数全都加起来，每次把一个数变负，就是把这个和减去该数的两倍。而如果从负数情况到删除的话只需要再加上这个数即可。于是我们先预处理出 $k=0$ 的情况，之后每次减去新进入滑窗的数的两倍，再加上离开滑窗的那个数即可。

## 代码展示
大体思路就是这样，如果有说的不清楚的地方欢迎结合代码或注释理解。
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int t,n,k,x,num[2000005];
bool cmp(int a,int b){
    return a>b;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--){
        int sum=0;
        for(int i=1;i<=n;i++) num[i]=0;
        cin>>n>>k>>x;
        for(int i=1;i<=n;i++){
            cin>>num[i];
            sum+=num[i];
        }
        sort(num+1,num+1+n,cmp);//保证数组从大到小 
        for(int i=1;i<=x;i++) sum-=num[i]*2;
        int ans=sum;
        for(int i=1;i<=k;i++){
            sum+=num[i];//离开滑窗 
			sum-=num[i+x]*2;//新入滑窗 
            ans=max(ans,sum);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Pyrf_uqcat (赞：1)

### 题意
多组数据，给定一串正整数，爱丽丝从中最多删去 $k$ 个数，鲍勃从中选择 $x$ 个数乘上 $-1$，爱丽丝想让这串数的和最大，而鲍勃想让和最小，求操作一次后的这串数。
### 思路
先看鲍勃，将一个正整数乘上 $-1$，那就是将它变为它的相反数，而一个正数变成了一个负数，减小的值为这个正数的两倍，而鲍勃是想让总和变小，那么减小的值要大，所以鲍勃会选择最大的几个数变成相反数。

再看爱丽丝，爱丽丝是想让总共最大，但是爱丽丝只能删除数，所以再怎么删除，总和都无法变大，因此爱丽丝想要总和最大的办法只有减小鲍勃造成的损失。而前面说过，鲍勃选择的数越大，总和越小，爱丽丝唯一的优势是优先删除数，所以为了减小损失，爱丽丝优先将最大的几个数字删去，这样鲍勃就不能改变这些较大的数，只能改变较小的数了。

那么这道题的思路也就理清楚了：爱丽丝删去几个最大的数，鲍勃将剩下的数中较大的几个变为相反数。

### 代码
输入序列，计算总和，再将最大的 $k$ 个数删去，紧接着再剩下的数中找到最大的 $x$ 个数，将总和减去两倍的这个数（应该很好理解，在分析鲍勃时说过），最后输出答案，结束。

思路都知道了，代码就自己思考一下吧。完结！

---

## 作者：Saint_ying_xtf (赞：1)

首先，先把所有的数排序。

如果让爱丽丝操作，相当于减去 $a_i$。

让鲍勃操作，相当于减去 $2\times a_i$。

所以大的数肯定尽量让爱丽丝来处理（相对比与鲍勃）。但是也有可能过多会造成过多答案的答案损失。

所以直接枚举爱丽丝要选几个，然后从后往前选，因为要求 $O(n)$。所以要动态维护一下即可。

[link](https://codeforces.com/contest/1920/submission/241464626)。

---

## 作者：ThySecret (赞：0)

## [题目大意](https://www.luogu.com.cn/problem/CF1920B)

给定一个序列 $a_1, a_2,\ldots, a_n$，首先 A 先选择至多 $k$ 个数删除，然后 B 在剩下的数中选择至多 $x$ 个数乘上 $-1$，加上剩余的数后，A 想要和尽可能大，B 想要和尽可能小。若两者都通过最佳决策，求结果为多少。

## 解题思路

不难看出这是一道贪心题，数组中较大的数对结果的影响更大，因此我们可以进行从大到小的排序。但是不可以想当然让两者都选择当前序列中最大的数进行操作（样例中有反例）。

仔细分析样例后不难看出，A 选择的个数不大相同，但是 B 一定是尽可能选择完最大的，这样子最后的结果才会最小化。

到这里思路就很显然了，遍历枚举一遍 A 选择的个数，把每一个结果取一个 $\max$ 即可。

你说循环求和会超时？用前缀和优化即可。

单次询问时间复杂度 $O(n \log n)$。

## 公式详推

定义 $pre_i = a_1 + a_2 + a_3 + \ldots + a_i$，得出 A 删去的元素之和为：
$$
pre_A = pre_{i}
$$
得出 B 选择的元素之和为：
$$
pre_B = pre_{i + x} - pre_{i}
$$
由此可以得出结果为
$$
pre_n - 2 \times pre_B - pre_A  = pre_n - 2\times pre_{i + x} + pre_i
$$
需要注意的是，$i + x$ 可能会超过 $n$，因此两者之间要取 $\min$。

## AC Code

```c++
// Problem: B. Summation Game
// Contest: Codeforces - Codeforces Round 919 (Div. 2)
// URL: https://codeforces.com/contest/1920/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

// #define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;

int a[N], pre[N], maxn;

void solve()
{
	maxn = -INF;		// 多测注意还原
	
	int n, k, x; cin >> n >> k >> x;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + 1 + n, greater<>());	// 从大到小排序
	for (int i = 1; i <= n; i ++) pre[i] = pre[i - 1] + a[i];	// 预处理前缀和数组
	
	for (int i = 0; i <= k; i ++) 		// i 指的是 Alice 要删除元素的个数
	{
		int res = 0;
		res = pre[n] - 2 * pre[min(i + x, n)] + pre[i];
		maxn = max(maxn, res);
	}
	cout << maxn << '\n';
}

signed main()
{
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T --) solve();
	
	return 0;
}
```

---

## 作者：yyrwlj (赞：0)

## 题意简述

给定一个**正整数**序列，爱丽丝先从中删除最多 $k$ 个数，鲍勃再从中选出最多 $x$ 个数乘上 $-1$。

爱丽丝想让数列的和最大，鲍勃想让数列的和最小。求出双方操作一次后的数列和。

## 思路

先看鲍勃的操作，因为鲍勃想让数列的和最小，又因为是正整数数列，所以肯定会优先将更大的数乘上 $-1$。

同理，爱丽丝删除时，也要优先删除更大的数。

但是我们并不知道爱丽丝删多少个数最优，从 $0$ 到 $k$ 枚举即可。

为了方便用 $O(1)$ 的时间求出每次枚举的结果，要将排完序的数列做一个正前缀和和负前缀和。

## Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200005;
int a[N], s1[N], s2[N];
bool cmp(int x,int y)
{
    return x > y;
}
void work()
{
    int n, k, x;
    scanf("%d%d%d", &n, &k, &x);
    for (int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1, cmp);
    for (int i=1;i<=n;i++)
    {
        s1[i] = s1[i - 1] + a[i];
        s2[i] = s2[i - 1] - a[i];
    }
    int ans = -2e9;
    for (int i=0;i<=k;i++)
    {
        int l = i + 1, r = min(i + x, n);
        int res = s2[r] - s2[l - 1];
        ans = max(ans, res + s1[n] - s1[r]);
    }
    printf("%d\n", ans);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

