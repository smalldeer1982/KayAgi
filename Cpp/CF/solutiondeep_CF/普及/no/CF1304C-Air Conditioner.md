# 题目信息

# Air Conditioner

## 题目描述

Gildong owns a bulgogi restaurant. The restaurant has a lot of customers, so many of them like to make a reservation before visiting it.

Gildong tries so hard to satisfy the customers that he even memorized all customers' preferred temperature ranges! Looking through the reservation list, he wants to satisfy all customers by controlling the temperature of the restaurant.

The restaurant has an air conditioner that has 3 states: off, heating, and cooling. When it's off, the restaurant's temperature remains the same. When it's heating, the temperature increases by 1 in one minute. Lastly, when it's cooling, the temperature decreases by 1 in one minute. Gildong can change the state as many times as he wants, at any integer minutes. The air conditioner is off initially.

Each customer is characterized by three values: $ t_i $ — the time (in minutes) when the $ i $ -th customer visits the restaurant, $ l_i $ — the lower bound of their preferred temperature range, and $ h_i $ — the upper bound of their preferred temperature range.

A customer is satisfied if the temperature is within the preferred range at the instant they visit the restaurant. Formally, the $ i $ -th customer is satisfied if and only if the temperature is between $ l_i $ and $ h_i $ (inclusive) in the $ t_i $ -th minute.

Given the initial temperature, the list of reserved customers' visit times and their preferred temperature ranges, you're going to help him find if it's possible to satisfy all customers.

## 说明/提示

In the first case, Gildong can control the air conditioner to satisfy all customers in the following way:

- At $ 0 $ -th minute, change the state to heating (the temperature is 0).
- At $ 2 $ -nd minute, change the state to off (the temperature is 2).
- At $ 5 $ -th minute, change the state to heating (the temperature is 2, the $ 1 $ -st customer is satisfied).
- At $ 6 $ -th minute, change the state to off (the temperature is 3).
- At $ 7 $ -th minute, change the state to cooling (the temperature is 3, the $ 2 $ -nd customer is satisfied).
- At $ 10 $ -th minute, the temperature will be 0, which satisfies the last customer.

In the third case, Gildong can change the state to heating at $ 0 $ -th minute and leave it be. Then all customers will be satisfied. Note that the $ 1 $ -st customer's visit time equals the $ 2 $ -nd customer's visit time.

In the second and the fourth case, Gildong has to make at least one customer unsatisfied.

## 样例 #1

### 输入

```
4
3 0
5 1 2
7 3 5
10 -1 0
2 12
5 7 10
10 16 20
3 -100
100 0 0
100 -50 50
200 100 100
1 100
99 -100 0```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

### 题目内容重写

# 空调

## 题目描述

Gildong拥有一家烤肉餐厅。餐厅有很多顾客，因此许多顾客喜欢在到访前进行预订。

Gildong非常努力地满足顾客的需求，甚至记住了所有顾客的偏好温度范围！通过查看预订列表，他希望通过控制餐厅的温度来满足所有顾客。

餐厅有一台空调，有三种状态：关闭、加热和冷却。当空调关闭时，餐厅的温度保持不变。当空调加热时，温度每分钟上升1度。当空调冷却时，温度每分钟下降1度。Gildong可以在任何整数分钟时改变空调的状态，且可以改变任意多次。空调初始状态为关闭。

每个顾客有三个特征值：$ t_i $ —— 第$ i $个顾客到访餐厅的时间（以分钟为单位），$ l_i $ —— 他们偏好温度范围的下限，$ h_i $ —— 他们偏好温度范围的上限。

如果顾客到访时温度在其偏好范围内，则该顾客被满足。形式化地说，第$ i $个顾客被满足当且仅当在$ t_i $分钟时温度在$ l_i $和$ h_i $之间（包括$ l_i $和$ h_i $）。

给定初始温度、预订顾客的到访时间及其偏好温度范围，你需要帮助Gildong判断是否有可能满足所有顾客。

## 说明/提示

在第一个样例中，Gildong可以通过以下方式控制空调来满足所有顾客：

- 在第$ 0 $分钟，将空调状态改为加热（温度为0）。
- 在第$ 2 $分钟，将空调状态改为关闭（温度为2）。
- 在第$ 5 $分钟，将空调状态改为加热（温度为2，满足第1个顾客）。
- 在第$ 6 $分钟，将空调状态改为关闭（温度为3）。
- 在第$ 7 $分钟，将空调状态改为冷却（温度为3，满足第2个顾客）。
- 在第$ 10 $分钟，温度将为0，满足最后一个顾客。

在第三个样例中，Gildong可以在第$ 0 $分钟将空调状态改为加热并保持不变。这样所有顾客都将被满足。注意，第1个顾客和第2个顾客的到访时间相同。

在第二个和第四个样例中，Gildong至少会让一个顾客不满足。

## 样例 #1

### 输入

```
4
3 0
5 1 2
7 3 5
10 -1 0
2 12
5 7 10
10 16 20
3 -100
100 0 0
100 -50 50
200 100 100
1 100
99 -100 0```

### 输出

```
YES
NO
YES
NO```

### 算法分类
贪心

### 题解分析与结论

所有题解的核心思路都是通过维护一个温度区间，表示在某个时刻可能达到的温度范围。通过不断更新这个区间，并与每个顾客的偏好温度范围取交集，来判断是否能够满足所有顾客的需求。如果某个时刻的区间与顾客的偏好范围没有交集，则输出`NO`，否则继续处理下一个顾客，直到所有顾客处理完毕，输出`YES`。

### 精选题解

#### 题解1：作者：_ztyqwq (赞：10)
- **星级**：★★★★★
- **关键亮点**：思路清晰，代码简洁，时间复杂度为$O(n)$，且不需要排序，直接按时间顺序处理顾客。
- **个人心得**：作者提到题目输入已经按时间顺序排列，因此不需要额外排序，这一点在代码实现中得到了体现。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct customer
{
	int t, l, r;
	bool operator < (const customer& ano) const
	{
		return t < ano.t;
	}
}c[101];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			scanf("%d %d %d", &c[i].t, &c[i].l, &c[i].r);
		sort(c + 1, c + n + 1);
		int l = m, r = m;
		bool flag = true;
		for(int i = 1; i <= n; i++)
		{
			int d = c[i].t - c[i - 1].t;
			l -= d;
			r += d;
			l = max(l, c[i].l);
			r = min(r, c[i].r);
			if(l > r)
			{
				flag = false;
				break;
			}
		}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

#### 题解2：作者：dblark (赞：3)
- **星级**：★★★★
- **关键亮点**：思路与题解1类似，代码结构清晰，时间复杂度为$O(n)$，且同样不需要排序。
- **个人心得**：作者提到$ l_i, r_i $范围很大，因此不可能是DP，这一点在题解中得到了体现。

```cpp
#include <cstdio>
#include <algorithm>
#define N 105

struct node {
    int t, l, r;
} a[N];

inline bool cmp(const node &x, const node &y) { return x.t < y.t; }

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].t, &a[i].l, &a[i].r);
        std::sort(a + 1, a + n + 1, cmp); // 先根据时间排序
        int l = m, r = m;
        int fail = 0;
        for (int i = 1; i <= n; ++i) {
            l -= a[i].t - a[i - 1].t, r += a[i].t - a[i - 1].t; // 更新边界
            if (l > a[i].r || r < a[i].l) {
                fail = 1;
                break;
            }
            l = std::max(l, a[i].l); // 调整边界
            r = std::min(r, a[i].r);
        }
        if (fail) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

#### 题解3：作者：serverkiller (赞：3)
- **星级**：★★★★
- **关键亮点**：思路与题解1和题解2类似，代码简洁，时间复杂度为$O(n)$，且同样不需要排序。
- **个人心得**：作者提到可以直接在读入时处理，但要注意读完所有数据，这一点在代码实现中得到了体现。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,m;
 
int main()
{
	int t;
	scanf("%d",&t);
	while (t--)
	{
		int flag = 1;
		scanf("%d%d",&n,&m);
		int time = 0,maxx = m,mini = m;//其实在里面定义就不用老是担心初始化了qwq
		for (int i = 1; i <= n; i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			if (!flag) continue;//记得多组要把所有的数读完
			maxx += x - time;
			mini -= x - time;
			if (maxx < y || mini > z) flag = 0;//无交集的情况
			if (maxx > z) maxx = z;
			if (mini < y) mini = y;
        //将区间维护成两者的交集
			time = x;//保存现在的时间
 		}
 		if (flag) puts("YES");
 		else puts("NO");
	}
	return 0;
}
```

### 最优关键思路或技巧
- **区间维护**：通过维护一个温度区间，表示在某个时刻可能达到的温度范围，并与每个顾客的偏好温度范围取交集，来判断是否能够满足所有顾客的需求。
- **时间复杂度优化**：所有题解的时间复杂度均为$O(n)$，且不需要额外排序，直接按时间顺序处理顾客。

### 可拓展之处
- **类似问题**：类似的问题可以出现在需要维护某个变量的范围，并根据一系列限制条件来判断是否能够满足所有条件的情况下。例如，调度问题、资源分配问题等。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：57.39秒