# 题目信息

# Complementary XOR

## 题目描述

You have two binary strings $ a $ and $ b $ of length $ n $ . You would like to make all the elements of both strings equal to $ 0 $ . Unfortunately, you can modify the contents of these strings using only the following operation:

- You choose two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ );
- For every $ i $ that respects $ l \le i \le r $ , change $ a_i $ to the opposite. That is, $ a_i := 1 - a_i $ ;
- For every $ i $ that respects either $ 1 \le i < l $ or $ r < i \le n $ , change $ b_i $ to the opposite. That is, $ b_i := 1 - b_i $ .

Your task is to determine if this is possible, and if it is, to find such an appropriate chain of operations. The number of operations should not exceed $ n + 5 $ . It can be proven that if such chain of operations exists, one exists with at most $ n + 5 $ operations.

## 说明/提示

In the first test case, we can perform one operation with $ l = 2 $ and $ r = 2 $ . So $ a_2 := 1 - 1 = 0 $ and string $ a $ became equal to 000. $ b_1 := 1 - 1 = 0 $ , $ b_3 := 1 - 1 = 0 $ and string $ b $ became equal to 000.

In the second and in the third test cases, it can be proven that it's impossible to make all elements of both strings equal to $ 0 $ .

In the fourth test case, we can perform an operation with $ l = 1 $ and $ r = 2 $ , then string $ a $ became equal to 01, and string $ b $ doesn't change. Then we perform an operation with $ l = 2 $ and $ r = 2 $ , then $ a_2 := 1 - 1 = 0 $ and $ b_1 = 1 - 1 = 0 $ . So both of string $ a $ and $ b $ became equal to 00.

In the fifth test case, we can perform an operation with $ l = 1 $ and $ r = 1 $ . Then string $ a $ became equal to 011 and string $ b $ became equal to 100. Then we can perform an operation with $ l = 2 $ and $ r = 3 $ , so both of string $ a $ and $ b $ became equal to 000.

## 样例 #1

### 输入

```
5
3
010
101
2
11
10
4
1000
0011
2
10
10
3
111
111```

### 输出

```
YES
1
2 2
NO
NO
YES
2
1 2
2 2
YES
2
1 1
2 3```

# AI分析结果

### 题目内容重写

#### 题目描述
你有两个长度为 $n$ 的二进制字符串 $a$ 和 $b$。你希望通过以下操作将两个字符串中的所有元素都变为 $0$：

- 选择两个下标 $l$ 和 $r$（$1 \le l \le r \le n$）；
- 对于每个 $i$ 满足 $l \le i \le r$，将 $a_i$ 取反，即 $a_i := 1 - a_i$；
- 对于每个 $i$ 满足 $1 \le i < l$ 或 $r < i \le n$，将 $b_i$ 取反，即 $b_i := 1 - b_i$。

你的任务是判断是否可以通过一系列操作将两个字符串的所有元素变为 $0$，并且操作次数不超过 $n + 5$。可以证明，如果存在这样的操作序列，那么一定存在一个操作次数不超过 $n + 5$ 的序列。

#### 说明/提示
在第一个测试用例中，我们可以执行一次操作，选择 $l = 2$ 和 $r = 2$。这样 $a_2$ 变为 $0$，$a$ 变为 `000`，$b_1$ 和 $b_3$ 也变为 $0$，$b$ 变为 `000`。

在第二个和第三个测试用例中，可以证明无法将两个字符串的所有元素变为 $0$。

在第四个测试用例中，我们可以先执行一次操作，选择 $l = 1$ 和 $r = 2$，然后 $a$ 变为 `01`，$b$ 不变。接着执行一次操作，选择 $l = 2$ 和 $r = 2$，$a_2$ 变为 $0$，$b_1$ 也变为 $0$，最终 $a$ 和 $b$ 都变为 `00`。

在第五个测试用例中，我们可以先执行一次操作，选择 $l = 1$ 和 $r = 1$，$a$ 变为 `011`，$b$ 变为 `100`。接着执行一次操作，选择 $l = 2$ 和 $r = 3$，最终 $a$ 和 $b$ 都变为 `000`。

### 题解分析与结论

#### 综合分析
1. **判断条件**：所有题解都提到，如果 $a$ 和 $b$ 的字符既不全部相同，也不全部相异，则无解。这是问题的核心判断条件。
2. **操作策略**：大多数题解都采用了先将 $a$ 中的所有 $1$ 变为 $0$，然后根据 $b$ 的状态进行额外操作的策略。
3. **操作次数**：操作次数通常不超过 $n + 5$，符合题目要求。

#### 最优关键思路
- **判断条件**：首先检查 $a$ 和 $b$ 的字符是否全部相同或全部相异，如果不满足则直接输出 `NO`。
- **操作策略**：先将 $a$ 中的所有 $1$ 变为 $0$，然后根据 $b$ 的状态决定是否需要额外的操作。如果 $b$ 最终不为全 $0$，则通过特定的操作序列将其变为全 $0$。

#### 可拓展之处
- **类似问题**：类似的问题可以通过判断两个序列的关系来决定是否可以进行某种操作。例如，某些问题要求通过特定的操作将两个序列变为相同的状态。
- **算法套路**：这种问题通常需要先判断初始状态是否满足某种条件，然后通过一系列操作将序列变为目标状态。

### 推荐题目
1. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)
2. [P1972 石子合并](https://www.luogu.com.cn/problem/P1972)
3. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)

### 题解评分与亮点

#### 题解1：RNTBW (4星)
- **关键亮点**：提供了详细的证明过程，解释了为什么在某些情况下无解。代码实现简洁，操作次数控制得当。
- **个人心得**：作者通过模拟操作过程，得出了操作次数的控制方法，确保操作次数不超过 $n + 5$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001];
int t,n,i,k,s;
bool f,g,h;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);k=s=f=g=h=0;
		for(i=1;i<=n;i++) scanf("%1d",&a[i]);
		for(i=1;i<=n;i++)
		{
			scanf("%1d",&b[i]);
			if(a[i]==b[i])f=1;
			else g=1;
		}
		if(f&&g)//判断
		{puts("NO");continue;
		}
		puts("YES");
		for(i=1;i<=n;i++)
			if(a[i])k++;
		s=k;
		if((f&&(k%2)) || (g&&(k%2==0)))s+=3,h=1;//此时多了3步操作，具体见上
		printf("%d\n",s);
		for(i=1;i<=n;i++)
			if(a[i])printf("%d %d\n",i,i);//先将a置零
		if(h)printf("1 %d\n1 1\n2 %d\n",n,n); 
	}
	return 0;
}
```

#### 题解2：ningago (4星)
- **关键亮点**：通过异或操作的性质简化了问题，提供了清晰的操作步骤。代码实现简洁，操作次数控制得当。
- **个人心得**：作者通过异或操作的性质，简化了问题的复杂度，使得操作步骤更加清晰。

```cpp
#include <cstdio>
#include <cstring>

#define N 200010
int T;
int n;
char a[N],b[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%s%s",a + 1,b + 1);
		bool flag1 = 1,flag2 = 1;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] != b[i])
				flag1 = 0;
			else
				flag2 = 0;
		}
		if(!flag1 && !flag2)
		{
			printf("NO\n");
			continue;
		}
		int t = 0;
		if(flag1)
			t = 1;
		int cnt = 0;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] == '1')
				cnt++;
		}
		if(t)
		{
			if(cnt % 2 == 0)
			{
				printf("YES\n%d\n",cnt);
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
			else
			{
				printf("YES\n%d\n",cnt + 3);
				printf("1 1\n2 2\n1 2\n");
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
		}
		else
		{
			if(cnt % 2 == 1)
			{
				printf("YES\n%d\n",cnt);
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
			else
			{
				printf("YES\n%d\n",cnt + 3);
				printf("1 1\n2 2\n1 2\n");
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
		}
	}
	return 0;
}
```

#### 题解3：Micnation_AFO (4星)
- **关键亮点**：通过贪心算法和线段树实现了问题的解决，提供了详细的操作步骤。代码实现较为复杂，但操作次数控制得当。
- **个人心得**：作者通过贪心算法和线段树的结合，实现了对问题的有效解决，提供了详细的操作步骤。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 200010;

int T;
string a, b;
vector<int> v;

struct SegmentTree {
    int l, r;
    int dat;
    bool flag;
} t[N << 2];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].dat = b[l] - '0', t[p].flag = false; return; }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build((p << 1) | 1, mid + 1, r);
    t[p].dat = t[p << 1].dat + t[(p << 1) | 1].dat, t[p].flag = false;
}

void spread(int p) {
    if (t[p].flag) {
        t[p << 1].dat = t[p << 1].r - t[p << 1].l + 1 - t[p << 1].dat;
        t[(p << 1) | 1].dat = t[(p << 1) | 1].r - t[(p << 1) | 1].l + 1 - t[(p << 1) | 1].dat;
        t[p << 1].flag = !t[p << 1].flag, t[(p << 1) | 1].flag = !t[(p << 1) | 1].flag;
        t[p].flag = false;
    }
}

void change(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].dat = t[p].r - t[p].l + 1 - t[p].dat;
        t[p].flag = !t[p].flag;
        return;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r);
    if (r > mid) change((p << 1) | 1, l, r);
    t[p].dat = t[p << 1].dat + t[(p << 1) | 1].dat;
}

int main() {
    cin >> T;
    while (T--) {
        int n; cin >> n >> a >> b;
        v.clear(); a = " " + a, b = " " + b;
        build(1, 1, n);
        for (int i = 1; i <= n; i++)
            if (a[i] == '1') v.push_back(i);
        for (auto it : v) {
            if (it != 1) change(1, 1, it - 1);
            if (it != n) change(1, it + 1, n);
        }
        if ((t[1].dat != n && t[1].dat) || (n == 1 && t[1].dat)) { puts("NO"); continue; }
        puts("YES");
        int len = !t[1].dat ? v.size() : v.size() + 3;
        cout << len << "\n";
        for (auto it : v) cout << it << " " << it << "\n";
        if (t[1].dat) {
            cout << 1 << " " << 1 << "\n";
            cout << 2 << " " << n << "\n";
            cout << 1 << " " << n << "\n";
        }
    }
    return 0;
}
```

---
处理用时：89.87秒