# 题目信息

# [Violet] 天使玩偶/SJY摆棋子

## 题目描述


Ayu 在七年前曾经收到过一个天使玩偶，当时她把它当作时间囊埋在了地下。而七年后 的今天，Ayu 却忘了她把天使玩偶埋在了哪里，所以她决定仅凭一点模糊的记忆来寻找它。

我们把 Ayu 生活的小镇看作一个二维平面坐标系，而 Ayu 会不定时地记起可能在某个点 $(x, y)$ 埋下了天使玩偶；或者 Ayu 会询问你，假如她在 $(x,y)$，那么她离近的天使玩偶可能埋下的地方有多远。

因为 Ayu 只会沿着平行坐标轴的方向来行动，所以在这个问题里我们定义两个点之间的距离为 $\operatorname{dist}(A,B)=|A_x-B_x|+|A_y-B_y|$。其中 $A_x$ 表示点 $A$ 的横坐标，其余类似。


## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据 保证 $1 \leq n,m\leq 3 \times 10^5$，$0 \leq x_i,y_i \leq 10^6$。

## 样例 #1

### 输入

```
2 3 
1 1 
2 3 
2 1 2 
1 3 3 
2 4 2```

### 输出

```
1 
2```

# AI分析结果


### 题目分析
本题需要处理两种操作：添加新点或查询与给定点曼哈顿距离最小的点。曼哈顿距离定义为 |x1-x2| + |y1-y2|。由于数据规模大（n, m ≤ 300,000），我们需要高效算法。CDQ分治通过四次坐标变换将问题转化为三维偏序问题，每次处理一个方向（左下、左上、右下、右上），利用树状数组维护前缀最大值，实现 O(n log²n) 的解法。

### 算法思路
1. **坐标变换**：通过翻转坐标将四个方向的问题统一转化为左下方向处理。
2. **CDQ分治**：对操作序列分治，处理左区间修改对右区间查询的影响。
3. **树状数组**：维护 y 坐标对应的 x+y 最大值，支持高效查询和更新。
4. **归并排序**：优化排序效率，减少常数。

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 600005;
const int MAXV = 1000005;
const int INF = 0x3f3f3f3f;

struct Point {
    int op, x, y, id;
} q[MAXN], tmp[MAXN];
int ans[MAXN], tree[MAXV], maxn;

inline void read(int &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = (x<<3) + (x<<1) + (c^48), c = getchar();
}

inline void update(int pos, int val) {
    for (; pos <= maxn; pos += (pos & -pos))
        tree[pos] = max(tree[pos], val);
}

inline int query(int pos) {
    int res = 0;
    for (; pos; pos -= (pos & -pos))
        res = max(res, tree[pos]);
    return res ? res : -INF;
}

inline void clear(int pos) {
    for (; pos <= maxn; pos += (pos & -pos))
        if (tree[pos]) tree[pos] = 0;
        else break;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (q[i].x <= q[j].x) {
            if (q[i].op == 1) update(q[i].y, q[i].x + q[i].y);
            tmp[k++] = q[i++];
        } else {
            if (q[j].op == 2) 
                ans[q[j].id] = min(ans[q[j].id], q[j].x + q[j].y - query(q[j].y));
            tmp[k++] = q[j++];
        }
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) {
        if (q[j].op == 2)
            ans[q[j].id] = min(ans[q[j].id], q[j].x + q[j].y - query(q[j].y));
        tmp[k++] = q[j++];
    }
    for (int i = l; i <= mid; i++)
        if (q[i].op == 1) clear(q[i].y);
    for (int i = l; i <= r; i++) q[i] = tmp[i];
}

int main() {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; i++) {
        read(q[i].x), read(q[i].y);
        q[i].x++, q[i].y++;
        q[i].op = 1, q[i].id = i;
        maxn = max(maxn, max(q[i].x, q[i].y));
    }
    for (int i = n + 1; i <= n + m; i++) {
        read(q[i].op), read(q[i].x), read(q[i].y);
        q[i].x++, q[i].y++;
        q[i].id = i;
        maxn = max(maxn, max(q[i].x, q[i].y));
    }
    maxn++;
    memset(ans, 0x3f, sizeof(ans));
    int tot = n + m;

    // 第一次CDQ（左下）
    cdq(1, tot);
    for (int i = 1; i <= tot; i++) q[i].x = maxn - q[i].x;
    cdq(1, tot);
    for (int i = 1; i <= tot; i++) q[i].y = maxn - q[i].y;
    cdq(1, tot);
    for (int i = 1; i <= tot; i++) q[i].x = maxn - q[i].x;
    cdq(1, tot);

    for (int i = n + 1; i <= tot; i++)
        if (q[i].op == 2) printf("%d\n", ans[i]);
    return 0;
}
```

### 算法流程
1. **读入数据**：初始点和操作，坐标+1避免0值问题。
2. **初始化**：设置坐标范围 `maxn`，初始化答案数组。
3. **四次CDQ分治**：
   - 第一次：处理左下方向（原始坐标）
   - 第二次：处理右下方向（x = maxn - x）
   - 第三次：处理左上方向（y = maxn - y）
   - 第四次：处理右上方向（x = maxn - x, y = maxn - y）
4. **输出结果**：针对每个查询操作输出最小曼哈顿距离。

### 复杂度分析
- **时间复杂度**：O(n log²n)，CDQ分治的递归深度 O(logn)，每层树状数组操作 O(n logn)。
- **空间复杂度**：O(n)，存储操作序列和树状数组。

### 注意事项
1. 坐标整体+1避免树状数组下标为0。
2. 树状数组清零时只清理修改过的位置。
3. 使用快读优化输入效率。
4. 四次坐标变换覆盖所有方向，确保正确性。

---
处理用时：110.76秒