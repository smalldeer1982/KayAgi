# The Feast and the Bus

## 题目描述

某公司的员工们要庆祝今天的第$256$天！该公司有$n$名员工和$k$个团队，每个员工仅属于$1$个团队，每个团队至少有$1$名员工。团队编号从$1$到$k$。现在给出$n$个数字：$t_1,t_2,……t_n$，$t_i$表示第$i$个员工属于第$t_i$个团队。该公司雇佣了一辆班车，这辆班车将会往返多次承载员工去参加宴会，每一次可以承载$1$个团队或者$2$个团队，且每一个团队不能分离，必须在同一次车上。这辆车可以承载$s$个员工，$s$可以为任意值，假设通过$r$次运输，所有的员工都到达宴会目的地了，该公司需要支付$s*r$元(只有$1$辆班车)。现在要你计算$r*s$的最小值。

## 样例 #1

### 输入

```
6 3
3 1 2 3 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
10 1
1 1 1 1 1 1 1 1 1 1
```

### 输出

```
10
```

## 样例 #3

### 输入

```
12 4
1 2 3 1 2 3 4 1 2 1 2 1
```

### 输出

```
12
```

# 题解

## 作者：Waldin (赞：1)

## 题目分析
首先考虑枚举有$\,i\,$次车是运$\,2\,$个团队的，然后在每个$\,i\,$的情况下分别统计出$\,s\,$和$\,r$，最后最终答案就是每种情况下$\,s\times r\,$的最小值。这个枚举算法为总时间复杂度贡献了$\,O(\frac k2)\,$的因数，可以接受。

显然，$r=k-i$，所以问题来到了如何统计$\,s$。这时可以考虑一个贪心算法：由于每个团队最终必须运走，所以$\,s\,$至少得是人数最多的那个团队的人数。既然如此，只要让运$\,2\,$个团队的情况所需要的载重量尽可能小就行了，也就是让运$\,2\,$个团队的车一共运的那$\,2i\,$个团队都是人数前$\,2i\,$小的团队中的。然后在这$\,2i\,$个团队中选乘车组合时，每次选当前人数最多的和当前人数最少的$\,2\,$个团队共乘一辆车，这样就可以保证一次运$\,2\,$个团队的情况对载重量的贡献最小了。这个贪心算法为总时间复杂度贡献了$\,O(\frac{\frac k2(\frac k2+1)}{2})\,$的因数，可以接受。

综上，算法的总时间复杂度为$\,\frac{k^3+2k^2}{16}$。
## 代码实现
[这题](https://www.luogu.com.cn/problem/CF1250B)代码上也没什么细节需要特别注意的。参考代码里变量的范围开的都是刚刚好的，~~因为我比较喜欢卡常，同时也~~便于读者对每个变量的值域有一个较清楚的把握。

以下是在洛谷 Luogu 上拿到了[「最优解」](https://www.luogu.com.cn/record/list?pid=CF1250B&orderBy=1)的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr size_t MAXk = 8000;

#ifndef _getchar_nolock
#define _getchar_nolock getchar_unlocked
#endif
class FastIn_Base {
public:
	template<typename _Ty>
	FastIn_Base& operator>>(_Ty& __restrict__ int_var) noexcept {
		int c; bool f;
		if (is_signed<_Ty>::value)
			f = false;
		while (!isdigit(c = _getchar_nolock()))
			if (is_signed<_Ty>::value && c == 45)
				f = true;

		int_var = c - 48;
		while (isdigit(c = _getchar_nolock()))
			int_var = int_var * 10 + (c - 48);

		if (is_signed<_Ty>::value && f)
			int_var = -int_var;
		return *this;
	}

	FastIn_Base& operator>>(nullptr_t) noexcept {
		while (!isdigit(_getchar_nolock()));
		while (isdigit(_getchar_nolock()));
		return *this;
	}
};
#define intIn ((FastIn_Base) {})
#define cin intIn

template<typename _Ty>
bool to_max(_Ty& x, const _Ty y) noexcept {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<typename _Ty>
bool to_min(_Ty& x, const _Ty y) noexcept {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

int main(void) noexcept {
	ios::sync_with_stdio(false);
	#ifndef cin
	cin.tie(nullptr);
	#endif

	unsigned long n; unsigned short k;
	cin >> n >> k;
	unsigned long team[MAXk + 1];
	memset(team, 0x00, sizeof(team));
	while (n--) {
		unsigned short t; cin >> t;
		++team[t];
	}

	sort(team + 1, team + 1 + k);  // 按团队人数排序
	unsigned long ans = ULONG_MAX;
	for (unsigned long i = 0; i <= k / 2; ++i) {  // 枚举有 i 次车运 2 个团队
		unsigned long s = team[k];  // 至少得是人数最多的那个团队的人数
		for (unsigned short j = 1; j <= i; ++j)
			to_max(s, team[j] + team[i * 2 + 1 - j]);  // 在人数最小的 2i 个团队中每次选两头的(最大的和最小的)组一辆车
		to_min(ans, s * (k - i));  // 统计答案
	}
	cout << ans;
	return 0;
}

```

---

## 作者：Wander_E (赞：1)

这题其实就是贪心+双指针+枚举。

先来看贪心+双指针部分。

由于题目要求至多只能有 $2$ 个团队同乘一辆车而且在**车辆最大空间一定**的情况下车辆往返次数最少。所以我们希望让车内空间的利用率尽可能高，也就是尽量将每辆车都坐满。所以就尽量让**人最多的团队与人最少的团队坐在一起**。

基于以上这个贪心思路我们就可以将团队人数（记为 $team$）排序（这里不用记录编号，因为不求方案）然后定义指针 $l$ 和 $r$。

- 如果 $l = r$，此时只剩一个团队，往返次数 $+1$，退出循环。
- 如果 $team_l+team_r \le limit$（下面会讲到如何枚举 $limit$ ），那么就将这两个团队放在一起，往返次数 $+1$，$l+1$，$r-1$。
- 如果 $team_l+team_r > limit$ 就让人数多的先走，人数少的等待匹配， 往返次数 $+1$，$r-1$。

#### 贪心代码：
```cpp
int calc(int lim)
{
	int cnt = 0;
	int l = 1, r = k;
	while(l <= r)
	{
		cnt++;
		if(l == r) break;
		if(team[l] + team[r] <= lim && l < r) 
			l++, r--;
		else r--;
	}
	return cnt;
}
```
接下来我们再讨论枚举的方法。

其实我们不需要枚举每一种人数上限，因为题目中的方案只有两种：两个团队一起走或一个团队自己走。

在让**每个团队都能走的**前提下只需将一个团队自己走和两个团队一起走之间的人数枚举一遍即可。

为了使每个团队都能坐上车，所以枚举下限就是**团队人数的最大值**。

每辆车最多坐两个团队于是一辆车最多坐团队人数的**最大值与次大值之和**，也就是枚举下限。

#### 枚举代码：
```cpp
sort(team + 1, team + k + 1);
for(int i = team[k]; i <= team[k - 1] + team[k]; i++)
{
	ans = min(ans, 1ll * i * calc(i));
}
```

到这里题目就算做完了，但是还有一些细节，这题时间比较紧，稍有不慎就会 TLE，有两个坑点：
- **不要**全部无脑开 Long Long，只把 $ans$ 开成 Long Long 即可。

- 请不要使用 C++20，使用 C++14 及以下的版本。

~~CF 数据是真的严~~。

最后附上 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 8005;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int n, k;
int team[N];
long long ans = INF;
 
int calc(int lim)
{
	int cnt = 0;
	int l = 1, r = k;
	while(l <= r)
	{
		cnt++;
		if(l == r) break;
		if(team[l] + team[r] <= lim && l < r) 
			l++, r--;
		else r--;
	}
	return cnt;
}

signed main()
{
	cin >> n >> k;
	for(int i = 1, x; i <= n; i++)
	{
		cin >> x;
		team[x]++;
	}
	sort(team + 1, team + k + 1);
	for(int i = team[k]; i <= team[k - 1] + team[k]; i++)
	{
		ans = min(ans, 1ll * i * calc(i));
	}
	cout << ans << endl; 
	return 0;
}
```

---

