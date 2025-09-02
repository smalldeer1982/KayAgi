# Space Formula

## 题目描述

Formula 1 officials decided to introduce new competition. Cars are replaced by space ships and number of points awarded can differ per race.

Given the current ranking in the competition and points distribution for the next race, your task is to calculate the best possible ranking for a given astronaut after the next race. It's guaranteed that given astronaut will have unique number of points before the race.

## 说明/提示

If the third ranked astronaut wins the race, he will have 35 points. He cannot take the leading position, but he can overtake the second position if the second ranked astronaut finishes the race at the last position.

## 样例 #1

### 输入

```
4 3
50 30 20 10
15 10 7 3
```

### 输出

```
2
```

# 题解

## 作者：DennyQi (赞：5)

我们可以贪心的假设选手$D$将会在本场比赛中获得第一。而由于单调性，$D$之后的选手肯定不可能超过$D$。因此只需要考虑$D$能够超越多少它前面的选手即可。在它前面的肯定离它越近越好超，并且我们只需要保证那个人加上某个得分恰好小于等于$D$的，这样才能给其他人留更多的机会。于是只需要$O(n)$扫一遍就可以了。

```cpp
/*By DennyQi 2018*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define  r  read()
using namespace std;
typedef long long ll;
const int MAXN = 200010;
const int INF = 1061109567;
inline int Max(const int a, const int b){ return (a > b) ? a : b; }
inline int Min(const int a, const int b){ return (a < b) ? a : b; }
inline int read(){
    int x = 0; int w = 1; register char c = getchar();
    for(; c ^ '-' && (c < '0' || c > '9'); c = getchar());
    if(c == '-') w = -1, c = getchar();
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x<<3) + (x<<1) + c - '0'; return x * w;
}
int N,D,Ans,st(2);
int s[MAXN],p[MAXN];
int main(){
//	freopen(".in","r",stdin);
	N = r, Ans = D = r;
	for(int i = 1; i <= N; ++i) s[i] = r;
	for(int i = 1; i <= N; ++i) p[i] = r;
	for(int i = D-1; i > 0; --i){
		while(s[i] + p[st] > s[D] + p[1] && st <= N) ++st;
		if(st > N) break;
		--Ans, ++st;
	}
	printf("%d", Ans);
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 这道题可以使用类似**贪心**的思想

- 先将 $D$ 设为最大，即加上最大的 $P$。 

- 然后将 $S$ 从前往后枚举至 $D-1$，如果这个 $S_i$ 加上最小的 $P$ 可以让 $D$ 排名向前，则需要更新最小的 $P$，因为一个 $P$ 不可以用两次。
- 时间复杂度为 $O(n)$

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,d,s[N],p[N],minp,best_rank;
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];//输入s数组
	}
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];//输入p数组
	}
	best_rank=d;//现在的排名
	s[d]+=p[1];//将d尽可能设成最大
	minp=n;//最小的p
	for(int i=1;i<=d-1;i++)//只有d前面的数能让名次升高
	{
		if(s[i]+p[minp]<=s[d])//可以使排名更高
		{
			minp--;//更新最小的p
			best_rank--;//更新排名
		}
	}
	cout<<best_rank;//输出最高排名
	return 0;
}
~~~

[直接最优解第一](https://www.luogu.com.cn/record/list?pid=CF1046C&orderBy=1&status=&page=1)

---

## 作者：ThySecret (赞：0)

## 题目大意

给定两个长度均为 $n$ 的单调不上升的序列 $S$ 和 $P$，让 $S_{i}(1 \le i \le n)$ 中的每一个元素加上 $P_{j}(1 \le j \le n)$，使得原 $S$ 序列中的第 $D$ 个数经过降序排序后的排名最靠前。


## 解题思路
### 方法一（二分查找）
通过题目不难看出，如果要使 $S_{D}$ 最靠前，那么要加上 $P_{1}$（因为 $P$ 是降序排序的）。其次，通过贪心的思想，让比 $S_{D}$ 大的所有数列都加上一个最大可以使得和小于 $S_{D} + P_{1}$ 的数列 $P_{j}$。

由于两个序列都满足单调性，因此我们可以使用**二分**的思想完成：即通过每次二分查找搜索到最优解，再使用一个 `bool` 数组记录下已经使用过的序列数，直到用完了第二大的 $P$ 序列或者第 $i$ 个数直接大于 $S_{D} + P_{1}$ ，此时输出 $i + 1$。

此时复杂度为 $O(n \log n)$。


### 方法二（双指针优化）
但是其实通过仔细思考发现，根本不需要通过二分查找寻找最优值，我们只需要一个指针 `cur` 指向当前未使用过的最大 $P$ 元素值。

对于第 $i (1 \le i \le D)$ 个数，如果 $S_{i} + P_{cur} > S_{D} + P_{1}$，那么指针向右一位，如果指针超出了界限，则跳出循环。每一次循环结束的时候就将答案减 $1$，同时将 `cur` 向右移一位。

此时复杂度仅为 $O(n)$。


## AC Code 

```C++
// Problem: Space Formula
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1046C
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;
int s[N], p[N];

int main()
{
	int n, pos; cin >> n >> pos;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = 1; i <= n; i++) cin >> p[i];
		
	int maxn = s[pos] + p[1], ans = pos; // 先让答案为当前位置
	for (int i = pos - 1, cur = 2; i >= 1; i--)
	{
		while (s[i] + p[cur] > maxn && cur <= n) cur ++; // 如果条件成立，则将指针向右一位
		if (cur > n) break; // 如果指针超出界限，则终止循环
		ans --, cur ++; // 每一次循环过后更新答案和指针
	}
    
	cout << ans << '\n'; // 输出答案
	return 0;
}
```

---

## 作者：so_find_skind (赞：0)

提前说一句，本人太逊了，所以题解在部分思路与代码上是参照 DennyQi 大佬的题解所写的，但与抄袭是两回事，请谅解。

我们可以假设选手 $D$ 会在比赛中获得第一，此时为了让它的排名更靠前，显然要选择最大的分数，然后由于 $D$ 后面的人本来分数就小，而且拿得的分数也较小，因此 $D$ 在拿分数之后的排名显然不会比之前要低。

故我们只需要考虑 $D$ 最多能够超越多少位本来排在它前面的选手即可。在他前面的选手显然离他本来的排名越近越好超越，并且我们只需要保证那个人加上某个得分正好是小于等于 $D$ 的最大分数，这样才能给超越其他选手留下更多的机会。于是只需要以 $O(n)$ 的时间复杂度遍历一遍就可以了。

code（代码是参照 DennyQi 大佬的题解代码写的）：

```cpp
#include<iostream>
using namespace std;
int n,d,ans,st;
int s[200005],p[200005];
int main(){
	cin>>n>>d;
    ans=d;
	for(int i=1;i<=n;i++)
        cin>>s[i];
	for(int i=1;i<=n;i++)
        cin>>p[i];
	for(int i=d-1;i>=1;i--){
		while(s[i]+p[st]>s[d]+p[1] && st<=n)
            ++st;
		if(st>n)
            break;
		ans--;
        ++st;
	}
	cout<<ans;
	return 0;
}
```


---

