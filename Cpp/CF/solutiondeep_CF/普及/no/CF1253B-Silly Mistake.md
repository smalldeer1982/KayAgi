# 题目信息

# Silly Mistake

## 题目描述

The Central Company has an office with a sophisticated security system. There are $ 10^6 $ employees, numbered from $ 1 $ to $ 10^6 $ .

The security system logs entrances and departures. The entrance of the $ i $ -th employee is denoted by the integer $ i $ , while the departure of the $ i $ -th employee is denoted by the integer $ -i $ .

The company has some strict rules about access to its office:

- An employee can enter the office at most once per day.
- He obviously can't leave the office if he didn't enter it earlier that day.
- In the beginning and at the end of every day, the office is empty (employees can't stay at night). It may also be empty at any moment of the day.

Any array of events satisfying these conditions is called a valid day.

Some examples of valid or invalid days:

- $ [1, 7, -7, 3, -1, -3] $ is a valid day ( $ 1 $ enters, $ 7 $ enters, $ 7 $ leaves, $ 3 $ enters, $ 1 $ leaves, $ 3 $ leaves).
- $ [2, -2, 3, -3] $ is also a valid day.
- $ [2, 5, -5, 5, -5, -2] $ is not a valid day, because $ 5 $ entered the office twice during the same day.
- $ [-4, 4] $ is not a valid day, because $ 4 $ left the office without being in it.
- $ [4] $ is not a valid day, because $ 4 $ entered the office and didn't leave it before the end of the day.

There are $ n $ events $ a_1, a_2, \ldots, a_n $ , in the order they occurred. This array corresponds to one or more consecutive days. The system administrator erased the dates of events by mistake, but he didn't change the order of the events.

You must partition (to cut) the array $ a $ of events into contiguous subarrays, which must represent non-empty valid days (or say that it's impossible). Each array element should belong to exactly one contiguous subarray of a partition. Each contiguous subarray of a partition should be a valid day.

For example, if $ n=8 $ and $ a=[1, -1, 1, 2, -1, -2, 3, -3] $ then he can partition it into two contiguous subarrays which are valid days: $ a = [1, -1~ \boldsymbol{|}~ 1, 2, -1, -2, 3, -3] $ .

Help the administrator to partition the given array $ a $ in the required way or report that it is impossible to do. Find any required partition, you should not minimize or maximize the number of parts.

## 说明/提示

In the first example, the whole array is a valid day.

In the second example, one possible valid solution is to split the array into $ [1, -1] $ and $ [1, 2, -1, -2, 3, -3] $ ( $ d = 2 $ and $ c = [2, 6] $ ). The only other valid solution would be to split the array into $ [1, -1] $ , $ [1, 2, -1, -2] $ and $ [3, -3] $ ( $ d = 3 $ and $ c = [2, 4, 2] $ ). Both solutions are accepted.

In the third and fourth examples, we can prove that there exists no valid solution. Please note that the array given in input is not guaranteed to represent a coherent set of events.

## 样例 #1

### 输入

```
6
1 7 -7 3 -1 -3
```

### 输出

```
1
6
```

## 样例 #2

### 输入

```
8
1 -1 1 2 -1 -2 3 -3
```

### 输出

```
2
2 6
```

## 样例 #3

### 输入

```
6
2 5 -5 5 -5 -2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
-8 1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写

#### 题目描述

中央公司有一个配备复杂安全系统的办公室。公司有 $10^6$ 名员工，编号从 $1$ 到 $10^6$。

安全系统记录了员工的进出情况。第 $i$ 名员工的进入事件用整数 $i$ 表示，离开事件用整数 $-i$ 表示。

公司对办公室的进出有以下严格规定：

- 每位员工每天最多只能进入办公室一次。
- 如果员工当天没有进入办公室，则不能离开办公室。
- 每天开始和结束时，办公室必须为空（员工不能过夜）。办公室在一天中的任何时刻也可能为空。

任何满足这些条件的事件数组被称为一个“有效的一天”。

一些有效或无效的例子：

- $[1, 7, -7, 3, -1, -3]$ 是一个有效的一天（$1$ 进入，$7$ 进入，$7$ 离开，$3$ 进入，$1$ 离开，$3$ 离开）。
- $[2, -2, 3, -3]$ 也是一个有效的一天。
- $[2, 5, -5, 5, -5, -2]$ 不是有效的一天，因为 $5$ 在同一天内进入了办公室两次。
- $[-4, 4]$ 不是有效的一天，因为 $4$ 在未进入办公室的情况下离开了。
- $[4]$ 不是有效的一天，因为 $4$ 进入了办公室但没有在当天结束前离开。

现在有 $n$ 个事件 $a_1, a_2, \ldots, a_n$，按发生顺序排列。这个数组对应一个或多个连续的天。系统管理员误删了事件的日期，但没有改变事件的顺序。

你需要将事件数组 $a$ 划分为连续的若干子数组，每个子数组必须表示一个非空的有效的一天（或报告这是不可能的）。每个数组元素必须属于且仅属于一个连续的子数组。每个连续的子数组必须是一个有效的一天。

例如，如果 $n=8$ 且 $a=[1, -1, 1, 2, -1, -2, 3, -3]$，则可以将其划分为两个连续的有效子数组：$a = [1, -1~ \boldsymbol{|}~ 1, 2, -1, -2, 3, -3]$。

帮助管理员将给定的数组 $a$ 按要求划分，或报告这是不可能的。找到任意一个有效的划分即可，不需要最小化或最大化划分的部分数。

### 算法分类

模拟

### 题解综合分析与结论

本题的核心是通过模拟员工的进出事件，判断是否可以将事件序列划分为多个有效的天数。所有题解都采用了模拟的思路，通过维护员工的状态（是否进入、是否离开）来判断当前事件是否合法，并在办公室为空时划分新的一天。

### 所选高星题解

#### 题解1：作者：liuzhongrui (赞：4)

**星级：★★★★★**

**关键亮点：**
- 使用数组 `state` 维护每个员工的状态（未进入、已进入、已离开），并通过 `ofs` 记录当前办公室内的员工数量。
- 当办公室为空时，划分新的一天，并重置相关员工的状态。
- 代码简洁高效，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int state[borne];
bool solve() {
    ios::sync_with_stdio(false);
    int nbEvents;
    cin >> nbEvents;
    vector<int> res, cur;
    int ofs = 0;
    for (int ind = 0; ind < nbEvents; ++ind) {
        int ev;
        cin >> ev;
        int guy = abs(ev);
        cur.push_back(guy);
        if (ev > 0) {
            if (state[guy] != WAIT) return 0;
            state[guy] = ENTERED;
            ++ofs;
        } else {
            if (state[guy] != ENTERED) return 0;
            state[guy] = LEFT;
            --ofs;
        }
        if (ofs == 0) {
            res.push_back(cur.size());
            for (int x : cur) state[x] = WAIT;
            cur.clear();
        }
    }
    if (! cur.empty()) return 0;
    int nbDays = res.size();
    cout << nbDays << "\n";
    for (int i = 0; i < nbDays; ++i) {
        cout << res[i];
        if (i+1 < nbDays) cout << " ";
        else cout << "\n";
    }
    return 1;
}
```

#### 题解2：作者：_HMZ_ (赞：1)

**星级：★★★★**

**关键亮点：**
- 使用队列 `q` 存储当天有进出记录的员工，避免使用 `memset` 清空状态数组，优化了时间复杂度。
- 在办公室为空时，清空队列并划分新的一天。
- 代码逻辑清晰，细节处理得当。

**核心代码：**
```cpp
queue<int> q;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] >= 0 && vis[abs(a[i])]) {
            cout << -1;
            return 0;
        }
        vis[abs(a[i])] = true;
        q.push(abs(a[i]));
        map[abs(a[i])] += a[i];
        if (map[abs(a[i])] < 0) {
            cout << -1;
            return 0;
        }
        else if (map[abs(a[i])] == 0)
            --cnt;
        else
            ++cnt;
        if (cnt == 0) {
            while (!q.empty())
                vis[q.front()] = false, q.pop();
            ++ansn;
            ans[ansn] = i - last;
            last = i;
        }
    }
    if (cnt != 0) {
        cout << -1;
        return 0;
    }
    cout << ansn << endl;
    for (int i = 1; i <= ansn; i++)
        cout << ans[i] << ' ';
    return 0;
}
```

#### 题解3：作者：Lan_yan (赞：0)

**星级：★★★★**

**关键亮点：**
- 使用队列 `bgs` 存储当天有进出记录的员工，避免使用 `memset` 清空状态数组，优化了时间复杂度。
- 在办公室为空时，清空队列并划分新的一天。
- 代码逻辑清晰，细节处理得当。

**核心代码：**
```cpp
queue<int> bgs;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &peo);
        if (peo > 0) {
            if (yg[peo] != 0) {
                printf("-1");
                return 0;
            }
            bgs.push(peo);
            yg[peo] = 1;
            num++;
        }
        if (peo < 0) {
            peo *= -1;
            if (yg[peo] != 1) {
                printf("-1");
                return 0;
            }
            yg[peo] = -1;
            num--;
        }
        if (num == 0) {
            while (!bgs.empty()) {
                yg[bgs.front()] = 0;
                bgs.pop();
            }
            dat[++ds] = i - la;
            la = i;
        }
    }
    if (num != 0) {
        printf("-1");
        return 0;
    }
    printf("%d\n", ds);
    for (int i = 1; i <= ds; i++)
        printf("%d ", dat[i]);
    return 0;
}
```

### 最优关键思路或技巧

1. **状态维护**：使用数组维护每个员工的状态（未进入、已进入、已离开），并通过计数器记录当前办公室内的员工数量。
2. **队列优化**：使用队列存储当天有进出记录的员工，避免使用 `memset` 清空状态数组，优化时间复杂度。
3. **贪心划分**：在办公室为空时，立即划分新的一天，确保划分的有效性。

### 可拓展之处

本题的模拟思路可以应用于其他需要按事件顺序进行状态维护的问题，如任务调度、资源分配等。类似的题目可以考察事件序列的合法性判断或划分。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：59.31秒