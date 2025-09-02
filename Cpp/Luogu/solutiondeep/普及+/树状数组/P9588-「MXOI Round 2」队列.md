# 题目信息

# 「MXOI Round 2」队列

## 题目描述

小 C 有一个队列，他要对这个队列进行 $q$ 次操作。操作共四种，参数分别如下：

$1\ x$：这是第一种操作，表示从队尾依次插入 $1,2,3,\cdots,x$；

$2\ y$：这是第二种操作，表示弹出队头的前 $y$ 个元素；

$3\ z$：这是第三种操作，表示查询队列中的第 $z$ 个元素；

$4$：这是第四种操作，表示查询队列中所有元素的最大值。

你需要帮助他维护这个队列，并对于每个第三种操作和第四种操作，输出查询的答案。

## 说明/提示

#### 【样例解释 #1】

在进行第四次操作后，队列中的元素依次为 $3,4,5,1,2,3,1,2,3,4$。

在进行第七次操作后，队列中的元素依次为 $2,3,1,2,3,4$。

#### 【样例 #2】

见附加文件中的 `queue/queue2.in` 与 `queue/queue2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `queue/queue3.in` 与 `queue/queue3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该样例满足测试点 $15$ 的限制。

#### 【样例 #6】

见附加文件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

设 $\sum x$ 表示单个测试点内 $x$ 之和。

对于 $100\%$ 的数据，$1 \le q \le 2\times 10^5$，$1 \le x,y,z \le 10^9$，$0 \le \sum x \le 2\times10^{14}$，保证在进行第二种操作前队列内元素个数不小于 $y$，在进行第三种操作前队列内元素个数不小于 $z$，在进行第四种操作前队列内元素个数大于 $0$。

|测试点编号|$q \le$|$x \le$|$\sum x \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1\sim3$|$500$|$500$|$2\times10^5$|C|
|$4\sim8$|$5000$|$5000$|$2\times10^7$|无|
|$9\sim10$|$2\times10^5$|$10^9$|$2\times10^{14}$|AB|
|$11\sim12$|$2\times10^5$|$10^9$|$2\times10^{14}$|B|
|$13\sim14$|$2\times10^5$|$10^9$|$2\times10^9$|AC|
|$15\sim16$|$2\times10^5$|$10^9$|$2\times10^9$|C|
|$17\sim18$|$2\times10^5$|$500$|$2\times10^7$|无|
|$19$|$2\times10^5$|$10^9$|$2\times10^9$|无|
|$20$|$2\times10^5$|$10^9$|$2\times10^{14}$|无|

特殊性质 A：没有第二种操作。

特殊性质 B：没有第三种操作。

特殊性质 C：没有第四种操作。

## 样例 #1

### 输入

```
0 9
1 5
1 3
2 2
1 4
3 6
3 8
2 4
4
3 3```

### 输出

```
3
2
4
1```

# AI分析结果

### 综合分析与结论
本题的核心在于高效维护队列的四种操作，由于数据规模较大，直接模拟会超时，因此各题解采用了不同的数据结构和算法来优化。主要思路是将每次插入的 $x$ 个数作为一组，通过前缀和、二分查找、单调队列、multiset、线段树等方法来实现操作的高效处理。

### 所选题解
1. **作者：Crosser（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `std::multiset` 维护最大值，通过前缀和数组和二分查找实现查询操作，复杂度低。
    - **核心代码**：
```cpp
int a[200005], s[200005], n;
multiset<int> ms;

void push(int w)
{ 
    a[++n] = w;
    s[n] = s[n - 1] + w;
    ms.insert(w);
}
signed main()
{
    int res = 0, id = 1;
    int q = read();
    q = read();
    while (q--)
    {
        int op = read();
        if (op == 1)
        {
            int x = read();
            push(x);
        }
        if (op == 2)
        {
            int y = read();
            res += y;
            while(s[id] <= res && id <= n) {
                ms.erase(ms.find(a[id]));
                id++;
            }
        }
        if (op == 3)
        {
            int z = read() + res;
            int pos = lower_bound(s + 1, s + n + 1, z) - s - 1;
            cout << z - s[pos] << endl;
        }
        if(op == 4)
        {
            cout << *ms.rbegin() << endl;
        }
    }
    return 0;
}
```
    - **核心实现思想**：使用数组 `a` 记录每次插入的 $x$，数组 `s` 记录前缀和，`multiset` 维护最大值。操作 1 插入元素并更新前缀和与 `multiset`；操作 2 通过更新删除数量 `res` 并从 `multiset` 中删除已删除组的元素；操作 3 通过二分查找前缀和数组找到第 $z$ 个元素所在组并计算结果；操作 4 直接输出 `multiset` 的最大值。

2. **作者：Coffee_zzz（4星）**
    - **关键亮点**：对不同测试点进行分类讨论，详细阐述了各种情况下的解题思路，具有很强的指导性。
    - **核心代码**：
```cpp
// Task 11~12 部分代码示例
vector<int> num, las;
multiset<int> s;
int head = 0;

void push(int x) {
    num.push_back(x);
    las.push_back(x);
    s.insert(x);
}

void pop(int y) {
    while (y > 0) {
        if (y >= las[head]) {
            s.erase(s.find(num[head]));
            y -= las[head];
            head++;
        } else {
            las[head] -= y;
            y = 0;
        }
    }
}

int getMax() {
    return *s.rbegin();
}
```
    - **核心实现思想**：对于没有操作三的情况，使用数组 `num` 和 `las` 分别记录每组的原始元素个数和剩余元素个数，`multiset` 维护剩余组的最大值。操作 1 插入元素并更新 `num`、`las` 和 `multiset`；操作 2 按组删除元素并更新 `multiset`；操作 4 直接输出 `multiset` 的最大值。

3. **作者：Milthm（4星）**
    - **关键亮点**：使用线段树维护最大值，通过前缀和数组和二分查找实现查询操作，代码实现较为完整。
    - **核心代码**：
```cpp
// 线段树部分代码
void update(int x, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr) {
        a[x] = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(x * 2, l, mid, ql, qr, k);
    if (qr > mid) update(x * 2 + 1, mid + 1, r, ql, qr, k);
    a[x] = max(a[x * 2], a[x * 2 + 1]);
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return a[x];
    }
    int mid = (l + r) >> 1, sum = 0;
    if (ql <= mid) sum = max(sum, query(x * 2, l, mid, ql, qr));
    if (qr > mid) sum = max(sum, query(x * 2 + 1, mid + 1, r, ql, qr));
    return sum;
}

// 主函数部分代码
signed main() {
    cin >> c >> Q;
    while (Q--) {
        int op, x;
        op = read();
        if (op == 1) {
            x = read();
            l[++t] = 1, r[t] = x;
            update(1, 1, n, t, t, x);
            f[t] = f[t - 1] + x;
        } else if (op == 2) {
            x = read();
            int cnt = 0;
            for (int i = h; i <= t; ++i) {
                cnt += r[i] - l[i] + 1;
                if (cnt >= x) {
                    cnt -= r[i] - l[i] + 1;
                    l[i] += x - cnt;
                    del += x - cnt;
                    if (l[i] > r[i]) update(1, 1, n, i, i, 0), ++h;
                    break;
                }
                del += r[i] - l[i] + 1;
                r[i] = l[i] = 0;
                ++h;
                update(1, 1, n, i, i, 0);
            }
        } else if (op == 3) {
            x = read();
            int qwq = lower_bound(f + h, f + t + 1, del + x) - f;
            printf("%lld\n", del + x - f[qwq - 1]);
        } else {
            printf("%lld\n", query(1, 1, n, h, t));
        }
    }
    return 0;
}
```
    - **核心实现思想**：使用线段树维护每组的最大值，数组 `f` 记录前缀和。操作 1 插入元素并更新线段树和前缀和；操作 2 按组删除元素并更新线段树；操作 3 通过二分查找前缀和数组找到第 $z$ 个元素所在组并计算结果；操作 4 通过线段树查询最大值。

### 最优关键思路或技巧
- **分组处理**：将每次插入的 $x$ 个数作为一组，避免直接存储大量元素，减少空间和时间开销。
- **前缀和与二分查找**：通过前缀和数组记录每组元素的累计数量，利用二分查找快速定位元素所在组，将查询操作的复杂度降低到 $O(\log q)$。
- **数据结构维护最大值**：使用 `multiset`、线段树、单调队列等数据结构维护队列中的最大值，方便进行操作 4。
- **虚拟删除**：不实际删除元素，而是通过记录删除数量来模拟删除操作，减少操作复杂度。

### 可拓展之处
- **同类型题**：涉及队列操作、区间查询、最大值维护的题目，如维护动态数组的插入、删除和查询操作。
- **类似算法套路**：分组处理、前缀和、二分查找、数据结构维护最值等方法在很多数据处理和查询问题中都有应用。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：考察单调队列的应用，用于维护滑动窗口内的最大值和最小值。
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)：经典的线段树题目，涉及区间修改和区间查询操作。
3. [P2068 统计和](https://www.luogu.com.cn/problem/P2068)：需要使用前缀和和二分查找来解决区间查询问题。

### 个人心得摘录与总结
- **作者：Milthm**：赛时因未想到用二分优化操作 3 而痛失 AK，提醒我们在解题时要注意分析复杂度，对于可能超时的操作要及时考虑优化方法。
- **作者：紊莫**：指出操作 3 坚持暴力做法会导致 TLE，应采用二分查找，同时提到删除时用懒标记避免更新所有元素，强调了对不同操作要采用合适的算法，以及懒标记在处理删除操作时的作用。

---
处理用时：55.09秒