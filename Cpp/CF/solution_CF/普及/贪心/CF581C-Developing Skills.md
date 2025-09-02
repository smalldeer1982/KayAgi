# Developing Skills

## 题目描述

Petya 正在玩一个游戏，主角有 $n$ 个技能，每个技能值 $a_i$ 在 $[0,100]$ 之间，当然技能值越高，技能越强；而主角的综合能力值为 $\sum\left \lfloor \dfrac{a_{i}}{10} \right \rfloor $，其中 $\left \lfloor\right \rfloor$ 为取整运算。

游戏开始时，Petya 有一个技能奖励包，包含 $k$ 点技能提升值，可以给任何一项技能提升一点技能值。现在编程计算 Petya 利用这个奖励包，可以把主角的综合能力值提升到的最大可能值。

注意：每个技能值最多能提升到 $100$。

## 样例 #1

### 输入

```
2 4
7 9
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 8
17 15 19
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 2
99 100
```

### 输出

```
20
```

# 题解

## 作者：_HMZ_ (赞：1)

## 题目大意：
在信息社团里有 $n$ 个人，每个人都有一个技能值，技能值越高，代表他越强。

你有 $k$ 的资金，每花费一点资金，你就可以请让一个人的技能值提高一点。

如果某人的技能值是 $0$ ，那么在花费一点资金之后就变为了 $1$。

但要注意，每个人的技能值不能超过 $100$。

计算整体评级的方法是将每个人的技能值除以 $10$，再向下取整，最后加和。

## 解题思路：

简单贪心即可，先排个序，每个数的个位越大，就放在越前面。

假设当前数为 $15$，那么加上 $5$ 就可以进位了。

如果当前数是 $11$，那么加上 $9$ 才能进位。

最后如果还剩下，就 $10$ 个 $10$ 个加上。

## AC 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n, k, a[100005], ans;
bool cmp(int x, int y)
{
	return x % 10 > y % 10;//排序
}
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 100)
			continue;
		if (k >= 10 - a[i] % 10)
		{
			k -= 10 - a[i] % 10;
			a[i] += 10 - a[i] % 10;
		}
		else
			break;
	}
	for (int i = 1; i <= n; i++)
	{
		if (k >= 10)
		{
			int s = min(100, a[i] + k);//每个人的技能值最多是100
			k -= s - a[i];
			a[i] = s;
		}
		ans += a[i] / 10;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：D_xbang (赞：0)

## 题意：
给出一个数 $k$ 和 $n$ 个正整数 $a_i$，其中 $a_i$ 可以加上 $x_i$，$\sum_{}x_i$ 的总和 $\le k$，求 $\sum_{} \frac{a_i}{10}$ 的最大值。
## 思路：
因为要求最大值，即要使花费较小，使 $a_i$ 成为 $10$ 的倍数。

先在输入时预处理 $a_i$ 的个位，和 $a_i$ 还能在十位能加多少，答案加上 $a_i$ 的十位，通过排序从小到大，循环 $k-a_i$，每次答案加一。之后处理 $k$ 且存在 $a_i$ 还能加的情况，最后输出即可。

具体看代码。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5;
int n, sum, a[N], k,ans;
bool cmp(int x, int y) {
	return x < y;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i] / 10;
		ans += (10 - a[i] / 10 - 1);
		a[i] = (10 - a[i] % 10);
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		if (k - a[i] >= 0 ) {
			k -= a[i];
			sum++;
		} else {
			break;
		}
	}
	if(k >= 10 && ans){
		sum += min(k / 10, ans);
	}
	cout << sum;
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑贪心，对于由于每个人增加到下一个 $10$ 的倍数的贡献都是 $1$，所以可以考虑贪心每次选最小能变成下一个 $10$ 的倍数最小的数，然后把他变成下一个 $10$ 的倍数。

然后就是动态查最小/最大值，就可以用堆来做。

例如：$[1,2] \to [1,10] \to [10,10]$。

注意一点，若 $a$ 原来就是 $10$ 的倍数，那么要特判一下，或者写成 $10 - a \bmod 10$；若一开始 $a$ 就是 $100$，那么就不要入队。。

## Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;
int a[100010];
priority_queue<pair<int, int>> q;

signed main() {
	scanf("%d%d", &n, &k);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		ans += a[i] / 10;
		if (a[i] != 100)
			q.push({a[i] % 10, i});
	}
	while (q.size()) {
		auto t = q.top();
		q.pop();
		if (k >= 10 - t.first) {
			k -= 10 - t.first;
			++ans;
			a[t.second] += 10 - t.first;
			if (a[t.second] != 100) q.push({0, t.second});
		} else break;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/581/C)|[链接](https://www.luogu.com.cn/problem/CF581C)

### 题意简述

一款游戏的主角有 $n$ 个技能，每个技能的技能点范围为 $[0,100]$。

你有 $k$ 个改进单位，每个改进单位可以使任意一技能的技能点加 $1$（不能超过 $100$）。

每个技能评分的计算方法是 $\lfloor\frac {a_i} {10}\rfloor$，而总评分则是把所有技能的评分相加。请你选择最优的方法，使得总评分最高。

### 题目分析

$k$ 个改进单位肯定是能用就用的，由于最终是让总评分最高，所以无论加给哪个技能都行。

但每个技能评分计算的方式是 $\lfloor\frac {a_i} {10}\rfloor$，所以肯定要把改进单位优先分给技能点 $\bmod\ 10$ 更大的技能。剩下的改进单位，就 $10$ 个 $10$ 个分给每个技能。注意，技能的技能点上限为 $100$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define o for(int i=1;i<=n;i++)
using namespace std;
int n,k,a[100005],ans;
bool cmp(int q,int p){
	return (q%10)>(p%10);
}//排序方式
int main(){
	scanf("%d%d",&n,&k);
	o scanf("%d",a+i);
	sort(a+1,a+n+1,cmp);
	o{
		if(a[i]>99)continue;
		int s=10-a[i]%10;
		if(k>=s)k-=s,a[i]+=s;
		if(!k)break;
	}
	if(k>9)
		o{
			if(a[i]>99)continue;
			else if(k>100-a[i])k-=100-a[i],a[i]=100;
			else {a[i]+=k/10*10;break;}
		}
	o ans+=a[i]/10;
	return !printf("%d",ans);
}
```
**最后，祝洛谷 $10$ 周年快乐！**

---

