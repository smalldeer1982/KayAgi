# [GCJ 2013 #1A] Manage your Energy

## 题目描述

你今天的日程非常繁忙，安排了许多重要的事情要做。你已经努力做好准备，确保所有活动之间不会重叠。现在早晨到来，尽管你充满热情，但你担心自己的精力不足以全身心投入到所有活动中。

你必须谨慎地管理自己的能量。你一开始拥有充沛的精力——准确地说，是 $E$ 焦耳。你知道自己不能让能量低于 $0$ 焦耳，否则你会因精疲力竭而倒下。你可以在每项活动上花费任意非负整数数量的能量（如果你很懒，也可以花费 $0$），每完成一项活动后，你会恢复 $R$ 焦耳的能量。但无论你多么懒惰，你在任何时刻能拥有的能量都不会超过 $E$ 焦耳；如果恢复后能量超过 $E$，则超出的部分会被浪费。

有些事情（比如解决 Code Jam 问题）比其他事情更重要。对于第 $i$ 个活动，你有一个价值 $v_i$，表示这项活动对你的重要程度。你从每项活动中获得的收益等于活动价值与你在该活动上花费的能量（单位：焦耳）的乘积。你希望通过合理分配能量，使得总收益尽可能大。

注意，你不能调整日程中活动的顺序。你只能在既定顺序下尽量合理地管理能量。


## 说明/提示

**样例解释**

在第一个样例中，我们可以在第一个活动上花费全部 $5$ 焦耳（收益为 $10$），恢复 $2$ 焦耳后，在第二个活动上花费这 $2$ 焦耳。在第二个样例中，我们在第一个活动上花费 $2$ 焦耳，恢复 $2$，然后在第二个活动上花费 $5$。在第三个样例中，恢复速度等于最大能量，因此每次活动后都能恢复满能量——所以每次都可以用满 $3$ 焦耳。

**限制条件**

- $1 \leq T \leq 100$

**小数据集（12 分，测试集 1 - 可见）**

- $1 \leq E \leq 5$
- $1 \leq R \leq 5$
- $1 \leq N \leq 10$
- $1 \leq v_i \leq 10$

**大数据集（23 分，测试集 2 - 隐藏）**

- $1 \leq E \leq 10^7$
- $1 \leq R \leq 10^7$
- $1 \leq N \leq 10^4$
- $1 \leq v_i \leq 10^7$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5```

### 输出

```
Case #1: 12
Case #2: 12
Case #3: 39```

# 题解

## 作者：MEGA_V (赞：5)

## 题目描述
你的能量上限为 $E$，有 $N$ 场活动等着你去参加，每场活动有价值 $v_i$。参加活动具体规则如下：

- 你一开始的能量为 $E$。
- 对于第 $i$ 场活动，当你在这场活动中消耗 $u$ 的能量（可能为 $0$，即你不参加这场活动），那你在本场活动的收益为 $u \times v_i$。**每场活动之后你的能量都会增加 $R$（不管你参不参加本次活动）**

求 $N$ 场活动后你的最大总收益。

**数据范围：$1 \le E, R, v_i \le 10^7$，$1 \le N \le 10^4$。**

## 思路
> 知识点：单调栈

假设当前正在进行第 $i$ 场活动，我们当前剩余能量为 $cur$，分为以下两种情况：

1. 在第 $i$ 场后没有收益比第 $i$ 场更大的，那么我们一定是把所有能量都用在这一场（因为乘积大），即：$cur \times v_i$。
2. 在第 $i$ 场后有收益比第 $i$ 场更大的，我们假设后面收益更大的第一场是第 $j$ 场，**我们肯定想尽可能地让第 $j$ 场的使用的能量最大（这样收益也就最大）**。为了避免浪费，在第 $i$ 场最多可以使用 $\max(0, cur + R \times (j - i))$ 个能量。

怎么算出第二种情况的 $j$ ？我们可以使用单调栈预处理一个 $nxt$ 数组，$nxt_i$ 表示在第 $i$ 场之后第第一个价值比第 $i$ 场大的编号。

时间复杂度：$O(N)$，空间复杂度 $O(N)$。

## 坑点
- 多测。
- 本题需要开 `long long`。
- 注意特判 $R \ge E$ 的情况，当回复大于等于上限的时候说明每场活动都可以使用完能量再回复到满。答案为 $\sum_{i = 1}^{N}{E \times v_i}$。
- 注意输出格式。~~（[别问我怎么知道的](https://www.luogu.com.cn/record/228940950)）~~

## Code
[$AC$ 记录](https://www.luogu.com.cn/record/228941142)
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = (int)1e4 + 5;

ll e, r, n;
ll v[MAXN];
int nxt[MAXN];
int stk[MAXN], stktop;

void sol(int id) {
    cin >> e >> r >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        nxt[i] = -1;
    }

    if (r >= e) { // 特判：说明每次都能恢复到满的值
        ll ans = 0;
        for (int i = 1; i <= n; i++) ans += e * v[i];
        cout << "Case #" << id << ": " << ans << "\n";
        return ;
    }

    stktop = 0;
    for (int i = 1; i <= n; i++) { // 单调栈求出nxt数组
        while (stktop && v[stk[stktop]] < v[i]) {
            nxt[stk[stktop]] = i;
            stktop--;
        }

        stk[++stktop] = i;
    }

    ll ans = 0, cur = e;
    for (int i = 1; i <= n; i++) {
        if (nxt[i] == -1) { // 后面没有比自己更大的值了
            ans += cur * v[i];
            cur = 0;
        } else {
            ll k = (nxt[i] - i);
            if (cur + k * r > e) {
                ll tmp = min(cur, cur + k * r - e);
                ans += v[i] * tmp;
                cur -= tmp;
            }
        }
        cur += r; // 每次恢复r能量
        if (cur > e) cur = e;
    }
    cout << "Case #" << id << ": " << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        sol(i);
    }

    return 0;
}
```

---

## 作者：__CuSO4__ (赞：4)

### 题解

思路：贪心 + 单调栈。

首先，我们知道：

- 高价值活动应优先分配更多能量；

- 能量分配需避免浪费，要保证后续更高价值的活动的能量。

所以，对于每一个活动 $i$，有如下策略：

- 情况1：若 $i$ 之后无更高价值活动，则分配当前全部能量；
  
- 情况2：若存在 $j>i$ 使得 $v_j > v_i$，那我们要保证后面活动的能量，则花费能量最多为 $cur+(j-i)*R-E$（$cur$ 表示当前能量）。

这时我们发现，要找的就是每个 $i$ 右边第一个比它大的元素，可以用单调栈线性地预处理，用 $nxt$ 储存。

那么就做完了，时间复杂度 $O(n)$，绰绰有余。

此外还要注意两点：

1. 开 `long long`；
2. 当 $R>E$，即每次都能回满时，需要特判。

### 代码：
``` cpp
#include <iostream>
using namespace std;

const int N = 1e4 + 5;

int v[N];
int nxt[N];  // 下一个更高价值的活动下标
int stk[N], top; // 手写栈

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        long long E, R;
        int N;
        cin >> E >> R >> N;
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }

        // 特判：每次都能恢复满能量
        if (R >= E) {
            long long ans = 0;
            for (int i = 0; i < N; i++) {
                ans += v[i] * E;
            }
            cout << "Case #" << t << ": " << ans << '\n';
            continue;
        }

        // 单调栈找下一个更高价值的活动
        top = 0;
        for (int i = 0; i < N; i++) {
            nxt[i] = -1;
            while (top > 0 && v[stk[top-1]] < v[i]) {
                nxt[stk[top-1]] = i;
                top--;
            }
            stk[top++] = i;
        }

        long long ans = 0;
        long long cur = E;  // 当前能量
        for (int i = 0; i < N; i++) {
            if (nxt[i] == -1) {
                // 后面没有更高价值的，花光能量
                ans += v[i] * cur;
                cur = R;
            } else {
                // 计算能花多少能量
                long long t = min(cur, cur + (nxt[i] - i) * R - E);
                if (t > 0) {
                    ans += v[i] * t;
                    cur -= t;
                }
                cur += R;
                if (cur > E) cur = E;
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}
``

---

## 作者：LZC_AK_CRZ (赞：0)

# Solution
题意还是比较清晰的，这里就不解释了。  
由**贪心思想**，我们可以得出两个~~显然~~的结论：
1. 应将更多的能量留给更高价值的活动。
2. 出现能量浪费的方案一定不优。

那么，为了实现**结论 1**，我们引入一个数据结构：**单调栈**。 
何为单调栈？顾名思义，单调栈即满足单调性的栈结构。与单调队列相比，其只在一端进行进出。——引自 *OI Wiki*  
我们这里需要的是栈顶元素最小的单调栈。为什么呢？如果当前活动价值比栈顶元素高，那么根据**结论 1**，我们应该把栈内比当前活动价值低元素的能量留给当前活动。于是，我们不断地弹出栈顶元素，为当前活动预留能量，直到栈顶元素的价值高于当前元素为止。这时，当前元素进栈。这样的操作维护了栈的单调性。

又因为每个活动分配的能量最多为 $E$，则根据**结论 2**，如果已经为当前活动预留了 $E$ 的能量，我们就不需要再为它预留了。

其实在这里，我们又可以从另一个角度理解单调栈的使用了：我们总是先修改后来的（也就是价值较低的）元素，而尽量保持价值较高的元素不变。

那么，看看代码吧：

```cpp
#include <iostream>
#include <stack>
#define int long long
using namespace std;
const int N = 1e4 + 5;
int T, E, R, n, v[N], e[N], ans;
stack<int> st;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> T;
	for (int tsk = 1; tsk <= T; tsk++) {
		cout << "Case #" << tsk << ": ";
		cin >> E >> R >> n;
		for (int i = 1; i <= n; i++) cin >> v[i];
		e[1] = E;
		st.push(1);
		for (int i = 2; i <= n; i++) {
			e[i] = min(E, R);
			while (!st.empty() && v[i] > v[st.top()]) {
				if (e[i] + e[st.top()] <= E) {
					e[i] += e[st.top()];
					e[st.top()] = 0;
					st.pop();
				} else {
					e[st.top()] -= E - e[i];
					e[i] = E;
					st.pop();
				}
			}
			st.push(i);
		}
		ans = 0;
		for (int i = 1; i <= n; i++) ans += e[i] * v[i];
		cout << ans << '\n';
	}
	return 0;
}
```
Thanks for your time!

---

