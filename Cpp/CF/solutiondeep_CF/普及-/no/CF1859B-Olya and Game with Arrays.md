# 题目信息

# Olya and Game with Arrays

## 题目描述

Artem suggested a game to the girl Olya. There is a list of $ n $ arrays, where the $ i $ -th array contains $ m_i \ge 2 $ positive integers $ a_{i,1}, a_{i,2}, \ldots, a_{i,m_i} $ .

Olya can move at most one (possibly $ 0 $ ) integer from each array to another array. Note that integers can be moved from one array only once, but integers can be added to one array multiple times, and all the movements are done at the same time.

The beauty of the list of arrays is defined as the sum $ \sum_{i=1}^n \min_{j=1}^{m_i} a_{i,j} $ . In other words, for each array, we find the minimum value in it and then sum up these values.

The goal of the game is to maximize the beauty of the list of arrays. Help Olya win this challenging game!

## 说明/提示

In the first test case, we can move the integer $ 3 $ from the second array to the first array. Then the beauty is $ \min(1, 2, 3) + \min(4) = 5 $ . It can be shown that this is the maximum possible beauty.

In the second test case, there is only one array, so regardless of the movements, the beauty will be $ \min(100, 1, 6) = 1 $ .

## 样例 #1

### 输入

```
3
2
2
1 2
2
4 3
1
3
100 1 6
3
4
1001 7 1007 5
3
8 11 6
2
2 9```

### 输出

```
5
1
19```

# AI分析结果

### 题目翻译
# 奥莉娅与数组游戏

## 题目描述
阿尔乔姆向女孩奥莉娅提出了一个游戏。有一个包含 $n$ 个数组的列表，其中第 $i$ 个数组包含 $m_i \geq 2$ 个正整数 $a_{i,1}, a_{i,2}, \ldots, a_{i,m_i}$。

奥莉娅最多可以从每个数组中移动一个（可能为 $0$ 个）整数到另一个数组。请注意，整数只能从一个数组中移动一次，但可以多次添加到一个数组中，并且所有移动操作是同时进行的。

数组列表的美观度定义为 $\sum_{i=1}^n \min_{j=1}^{m_i} a_{i,j}$。换句话说，对于每个数组，我们找到其中的最小值，然后将这些最小值相加。

游戏的目标是最大化数组列表的美观度。帮助奥莉娅赢得这个具有挑战性的游戏！

## 说明/提示
在第一个测试用例中，我们可以将整数 $3$ 从第二个数组移动到第一个数组。然后美观度为 $\min(1, 2, 3) + \min(4) = 5$。可以证明这是最大可能的美观度。

在第二个测试用例中，只有一个数组，因此无论如何移动，美观度都将是 $\min(100, 1, 6) = 1$。

## 样例 #1
### 输入
```
3
2
2
1 2
2
4 3
1
3
100 1 6
3
4
1001 7 1007 5
3
8 11 6
2
2 9
```

### 输出
```
5
1
19
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法。要点在于发现每个数组中只有最小值和次小值可能对结果有贡献，为了使每个数组最小值之和最大，将所有数组的最小值移动到次小值最小的数组中，这样其他数组的最小值就变为原来的次小值，从而增加总和。

各题解的区别主要在于代码实现方式，有的通过排序获取最小值和次小值，有的通过遍历比较获取。难点在于理解为什么要将最小值都移动到次小值最小的数组中，以及如何高效地找到每个数组的最小值和次小值。

### 所选题解
- **作者：2huk (赞：3)，4星**
    - **关键亮点**：思路清晰，代码注释详细，通过遍历比较的方式统计每个数组的最小值和次小值，最后按照贪心策略计算结果。
- **作者：SunnyYuan (赞：3)，4星**
    - **关键亮点**：对贪心思路的解释较为详细，代码结构清晰，使用 `vector` 存储数组，通过排序获取最小值和次小值。
- **作者：zgy_123 (赞：3)，4星**
    - **关键亮点**：通过具体样例解释思路，易于理解，代码简洁，使用 `sort` 排序获取最小值和次小值。

### 重点代码
#### 作者：2huk
```cpp
int T, n;
int k1[N], k2[N]; 	// k1[i] 表示第 i 个数组中的最小值，k2[i] 表示第 i 个数组中的次小值 

int Solve()
{
	n = read();
	
	int res = 0;
	
	fup (i, 1, n)
	{
		int len = read();
		k1[i] = k2[i] = INF;
		while (len -- )
		{
			int a = read();
			if (a < k1[i])
				k2[i] = k1[i], k1[i] = a;
			else if (a < k2[i])
				k2[i] = a;
		}
		res += k2[i];
	}
	
	int mn1 = INF, mn2 = INF;
	fup (i, 1, n)
		mn1 = min(mn1, k1[i]);
	fup (i, 1, n)
		mn2 = min(mn2, k2[i]);
	
	return res - mn2 + mn1;
}
```
**核心实现思想**：遍历每个数组，通过比较更新每个数组的最小值和次小值，同时累加次小值。最后找出所有最小值中的最小值和所有次小值中的最小值，按照贪心策略计算结果。

#### 作者：SunnyYuan
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 25010;

int n;
vector<int> a[N];

void solve() {
	cin >> n;
	int minn = 0x3f3f3f3f3f3f3f3f, mins = 0x3f3f3f3f3f3f3f3f, ans = 0;
	for (int i = 1; i <= n; i++) {
		int sz;
		cin >> sz;
		a[i].resize(sz);
		for (int& x : a[i]) cin >> x;
		sort(a[i].begin(), a[i].end());
		minn = min(minn, a[i][0]);
		mins = min(mins, a[i][1]);
		ans += a[i][1];
	}
	ans += minn;
	ans -= mins;
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;
	while (T--) solve();
	return 0; 
} 
```
**核心实现思想**：使用 `vector` 存储每个数组，对每个数组排序后获取最小值和次小值，累加次小值，找出所有最小值中的最小值和所有次小值中的最小值，按照贪心策略计算结果。

#### 作者：zgy_123
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[50005];
int main(){
	int t,n,m;
	cin>>t;
	while(t--){
		ll min_1=2e9,min_2=2e9,sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m;
			for(int j=1;j<=m;j++) cin>>a[j];
			sort(a+1,a+m+1);
			min_1=min(min_1,a[1]);//min_1表示取出数的最小值
			min_2=min(min_2,a[2]);//min_2表示次小数的最小值
			sum+=a[2];//sum即样例中的9+8+7
		}
		cout<<sum-min_2+min_1<<endl;
	} 
	return 0;
}
```
**核心实现思想**：使用数组存储每个数组的元素，对每个数组排序后获取最小值和次小值，累加次小值，找出所有最小值中的最小值和所有次小值中的最小值，按照贪心策略计算结果。

### 关键思路与技巧
- **贪心策略**：将所有数组的最小值移动到次小值最小的数组中，使其他数组的最小值变为次小值，从而增加总和。
- **高效获取最小值和次小值**：可以通过排序或遍历比较的方式获取每个数组的最小值和次小值。

### 拓展思路
同类型题可能会有更多的限制条件，如移动次数的限制、数组元素的范围限制等，但核心思路仍然是贪心，需要根据具体条件调整策略。

### 推荐洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得
- Iniaugoty：表示这题很简单，但自己未知原因写了 40min 才写出来。
- _Only_this：明明很水，却写了 45 分钟。
- EricWan：一开始读错题了，以为只让移动一个数，没想到是每组只让移动一个数。

总结：做题时要仔细读题，避免因读错题意浪费时间，同时简单的题目也可能因为各种原因花费较多时间，需要提高解题效率。 

---
处理用时：49.22秒