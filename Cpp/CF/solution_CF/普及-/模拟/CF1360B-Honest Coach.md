# Honest Coach

## 题目描述

你面前有 n 名运动员 运动员的编号从左到右分别是1--n你知道每个运动员的力量 编号为i的运动员的力量为si
   	你需要把所有运动员分到两队里，每队至少有一人，每名运动员必须在其中一队里。
    你需要在第一队里最强壮的运动员和第二队里最虚弱的运动员的差距尽可能的小。
    正式的，你想把运动员分成A，B两队导致价值∣max(A)−min(B)∣尽可能的小。
    其中max（A）是A队中力量最大的，min（B）是队伍中力量最小的。
    例如，如果n=5，力量分别为s={3,1,2,4,6}；则最理想的分配是：
    第一队 A={1,2,4}；第二队B={3，6}；
    这样一来最大的价值的绝对值是|4-3|=1，这个例子说明了一种最佳的分成两个团队的方法。输出最小的价值|max(A)-min(B)|。

## 样例 #1

### 输入

```
5
5
3 1 2 6 4
6
2 1 3 2 4 3
4
7 9 3 1
2
1 1000
3
100 150 200```

### 输出

```
1
0
2
999
50```

# 题解

## 作者：Warriors_Cat (赞：0)

## CF1360B

简单的贪心题。

我们先把 $s$ 数组排个序，然后找出相邻两个数之差的最小值即可。因为你可以把所有小于等于较小值的放到 $A$，所有大于等于较大值的放到 
$B$。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
#define F(i, a, b) for(int i = a; i <= b; ++i)
#define R(i, a, b) for(int i = a; i >= b; --i)
int t, n, a[110];
int main(){
	t = read();
	while(t--){
		n = read();
		for(int i = 1; i <= n; ++i) a[i] = read();
		sort(a + 1, a + n + 1);
		int ans = 0x7fffffff;
		for(int i = 1; i < n; ++i) ans = min(ans, abs(a[i] - a[i + 1]));//入门级程序
		printf("%d\n", ans);
	}
	return 0;
}

```


---

## 作者：SpeedStar (赞：0)

### 算法分析
首先对这$n$个数进行排序，然后求出相邻两数的差值，最后不断更新相邻两数之差的最小值就行了。

### C++代码
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		int s[n + 1];
		for (int i = 1; i <= n; cin >> s[i], ++i);
		sort(s + 1, s + n + 1);
		for (int i = n; i >= 2; --i) s[i] -= s[i - 1];
		int res = 0x3f3f3f3f;
		for (int i = 2; i <= n; ++i) res = min(res, s[i]);
		cout << res << '\n';
	}
	
	return 0;
}
```


---

## 作者：rui_er (赞：0)

这题有点复杂，简化一下问题。

把这些数分为两组，要求一组的最大值与另一组的最小值的差尽量小。

所以我们可以知道，若 $a_i$ 与 $a_j$ 差最小，则把比 $a_i$ 小的分一组，比 $a_j$ 大的分一组即可。

为了优化时间，提前排个序即可。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T, n, a[51];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i=1;i<=n;i++) {
			scanf("%d", &a[i]);
		}
		sort(a+1, a+1+n);
		int mi = 0x3f3f3f3f;
		for(int i=2;i<=n;i++) {
			mi = min(mi, a[i]-a[i-1]);
		}
		printf("%d\n", mi);
	}
	return 0;
}
```

---

