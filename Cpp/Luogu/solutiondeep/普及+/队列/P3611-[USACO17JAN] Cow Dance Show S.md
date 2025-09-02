# 题目信息

# [USACO17JAN] Cow Dance Show S

## 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。

## 样例 #1

### 输入

```
5 8
4
7
8
6
4```

### 输出

```
4
```

# AI分析结果

### 综合分析与结论
这些题解大多采用二分答案的方法来确定满足条件的最小 $K$ 值，对于每次二分得到的 $K$ 值，通过模拟奶牛跳舞的过程来判断是否满足时间限制 $T_{max}$。在模拟过程中，多数题解使用优先队列（小根堆）来维护舞台上奶牛的结束时间，方便找出最先完成舞蹈的奶牛。部分题解还给出了不同的数据结构实现，如线段树、冒泡排序等。

### 所选题解
- **作者：Strong_Jelly (赞：28)，4星**
  - **关键亮点**：思路清晰，对二分答案和模拟过程的解释详细，代码注释丰富，适合初学者理解。
  - **个人心得**：无
- **作者：从不再见 (赞：18)，4星**
  - **关键亮点**：代码简洁，对二分和模拟过程的实现较为精炼，能准确抓住问题的核心。
  - **个人心得**：指出二分的难点在 check 函数中，明确了思路方向。
- **作者：Histone (赞：11)，4星**
  - **关键亮点**：不仅给出了二分答案的解法，还提供了直接枚举的解法，并给出了测试详情，方便对比不同解法的效率。
  - **个人心得**：提到如果觉得二分太麻烦，$K$ 值直接从 $1$ 枚举到 $n$ 也是可以的，且给出了相应代码。

### 重点代码
#### Strong_Jelly 的核心代码
```cpp
inline bool f(int x) {
    int y = 0;
    int ans = 0;
    priority_queue < int, vector < int >, greater < int > > pru;
    for(register int i = 1; i <= x; ++i) {
        pru.push(q[i]);
    }
    for(register int i = x + 1; i <= n; ++i) {
        ans += pru.top() - y;
        y = pru.top();
        pru.pop();
        pru.push(q[i] + y);
        if(ans > m) {
            return false;
        }
    }
    while(x--) {
        ans += pru.top() - y;
        y = pru.top();
        pru.pop();
        if(ans > m) {
            return false;
        }
    }
    return ans <= m;
}
inline int half() {
    int l = 0;
    int r = 100000;
    int ans = 0;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(f(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}
```
**核心实现思想**：`f` 函数模拟奶牛跳舞过程，使用小根堆维护奶牛的结束时间，计算总时间并判断是否超过 $T_{max}$。`half` 函数进行二分查找，不断缩小 $K$ 的范围，找到满足条件的最小 $K$ 值。

#### 从不再见的核心代码
```cpp
bool check(int x) {
    priority_queue<int, vector<int>, greater<int> > dance;
    for(register int i=1;i<=x;i++)
        dance.push(cow[i]);
    for(register int i=x+1;i<=n;i++) {
        int cur = dance.top();
        dance.pop();
        dance.push(cur + cow[i]);
    }
    int cur;
    while(!dance.empty()) {
        cur = dance.top();
        dance.pop();
    }
    return cur <= t_max; 
}
int main() {
    cin >> n >> t_max;
    for(register int i = 1; i <= n; ++i) {
        cin >> cow[i];
    }
    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + ((r - l) >> 1);
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r;
    return 0;
}
```
**核心实现思想**：`check` 函数模拟奶牛跳舞，使用小根堆维护舞台上奶牛的结束时间，最后判断最大结束时间是否超过 $T_{max}$。`main` 函数进行二分查找，找到满足条件的最小 $K$ 值。

#### Histone 的核心代码
```cpp
bool c(int x) {
    int at = 0;
    priority_queue < int, vector<int>, greater<int> > q;
    for(int i = 1; i <= x; i++) q.push(num[i]);
    for(int i = x + 1; i <= n; i++) {
        int temp = q.top(); q.pop();
        q.push(temp + num[i]);
    }
    while(!q.empty()) {
        at = q.top(); q.pop();
    }
    return at <= t;
}
int main(void) {
    cin >> n >> t;
    for(int i = 1; i <= n; i++)
        cin >> num[i];
    int l = 0, r = n, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(c(mid)) r = mid - 1;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}
```
**核心实现思想**：`c` 函数模拟奶牛跳舞，使用小根堆维护奶牛的结束时间，最后判断最大结束时间是否超过 $T_{max}$。`main` 函数进行二分查找，找到满足条件的最小 $K$ 值。

### 最优关键思路或技巧
- **二分答案**：通过二分查找在可能的 $K$ 值区间内快速找到满足条件的最小 $K$ 值，时间复杂度为 $O(\log n)$。
- **优先队列（小根堆）**：在模拟奶牛跳舞过程中，使用小根堆可以方便地找到最先完成舞蹈的奶牛，时间复杂度为 $O(\log n)$，从而高效地模拟整个过程。

### 可拓展之处
同类型题或类似算法套路：
- 当遇到求最大值中的最小值或最小值中的最大值问题时，可以考虑使用二分答案的方法。
- 在模拟过程中，如果需要频繁地查找最小值或最大值，可以使用优先队列（堆）来优化时间复杂度。

### 推荐题目
- P1873 [COCI 2011/2012 #5] EKO / 砍树
- P2678 [NOIP2015 提高组] 跳石头
- P3853 [TJOI2007] 路标设置

---
处理用时：36.85秒