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
这些题解主要围绕二分答案和模拟奶牛跳舞过程来解决问题。二分答案用于确定满足时间上限的最小舞台大小 `K`，模拟跳舞过程则通过不同的数据结构实现，如优先队列、线段树、冒泡排序等。大部分题解思路清晰，利用二分法缩小 `K` 的范围，再用模拟判断可行性。其中，优先队列是最常用的数据结构，能高效找出最早结束跳舞的奶牛。

### 所选题解
- **作者：Strong_Jelly (赞：28)  4星**
    - **关键亮点**：思路清晰，详细解释了二分答案的过程和堆的使用，代码注释丰富，易于理解。
- **作者：从不再见 (赞：18)  4星**
    - **关键亮点**：明确指出二分答案的思路，对 `check` 函数的实现解释清晰，代码简洁。
- **作者：Histone (赞：11)  4星**
    - **关键亮点**：不仅给出了二分答案的解法，还提供了直接枚举的方法，并给出测试详情，适合不同水平的学习者。

### 重点代码及核心思想
#### Strong_Jelly 的代码
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
**核心思想**：`f` 函数模拟奶牛跳舞过程，用小根堆存储奶牛结束时间，计算总时间并判断是否超过上限。`half` 函数使用二分法确定最小的 `K`。

#### 从不再见的代码
```cpp
bool check(int x) {
    priority_queue<int, vector<int>, greater<int> > dance;
    for(register int i=1;i<=x;i++)
        dance.push(cow[i]);
    for(register int i=x+1;i<=n;i++) {
        int cur=dance.top();
        dance.pop();
        dance.push(cur+cow[i]);
    }
    int cur;
    while(!dance.empty()) {
        cur=dance.top();
        dance.pop();
    }
    return cur<=t_max; 
}
int main() {
    cin>>n>>t_max;
    for(register int i=1;i<=n;++i) {
        cin>>cow[i];
    }
    int l=0,r=n+1;
    while(l+1<r) {
        int mid=l+((r-l)>>1);
        if(check(mid)) {
            r=mid;
        } else {
            l=mid;
        }
    }
    cout<<r;
    return 0;
}
```
**核心思想**：`check` 函数用优先队列模拟跳舞过程，找出最终用时并与时间上限比较。主函数使用二分法确定最小的 `K`。

#### Histone 的代码
```cpp
bool c(int x) {
    int at = 0;
    priority_queue < int,vector<int>,greater<int> > q;
    for(int i=1;i<=x;i++) q.push(num[i]);
    for(int i=x+1;i<=n;i++) {
        int temp = q.top();q.pop();
        q.push(temp+num[i]);
    }
    while(!q.empty()) {
        at = q.top();q.pop();
    }
    return at<=t;
}
int main() {
    cin>>n>>t;
    for(int i=1;i<=n;i++)
        cin>>num[i];
    int l=0,r=n,mid;
    while(l<=r) {
        mid = (l+r)>>1;
        if(c(mid)) r = mid-1;
        else l = mid+1;
    }
    cout<<l;
    return 0;
}
```
**核心思想**：`c` 函数用优先队列模拟跳舞过程，找出最终用时并与时间上限比较。主函数使用二分法确定最小的 `K`。

### 最优关键思路或技巧
- **二分答案**：对于求最大值中的最小值或最小值中的最大值问题，二分答案是一种高效的解决方法。
- **优先队列**：使用小根堆（优先队列）可以高效地找出最早结束跳舞的奶牛，时间复杂度为 $O(log n)$。

### 可拓展之处
同类型题或类似算法套路：
- 涉及最大值最小化或最小值最大化的问题，都可以考虑使用二分答案。
- 模拟过程中需要频繁找出最值的问题，可以使用优先队列或线段树等数据结构优化。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录
- **zy小可爱ღ**：提到用冒泡排序代替 `sort` 避免超时，说明在不同场景下需要选择合适的排序算法。
- **zhaimingshuzms**：表示本来用链表维护超时，改用优先队列后 AC，强调了数据结构选择对性能的影响。

---
处理用时：42.95秒