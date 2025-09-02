# 题目信息

# [USACO17FEB] Why Did the Cow Cross the Road I S

## 题目描述

Farmer John 的奶牛们正在学习如何有效地过马路。回想起古老的“鸡为什么要过马路？”笑话，他们认为鸡一定是过马路的专家，于是去寻找鸡来帮助它们。

事实上，鸡是非常忙碌的生物，它们只有有限的时间来帮助奶牛。农场上有 $C$ 只鸡（$1 \leq C \leq 20,000$），方便地用编号 $1 \ldots C$ 标识，每只鸡 $i$ 只愿意在确切的时间 $T_i$ 帮助一头奶牛。奶牛们从不着急，它们的日程安排更加灵活。农场上有 $N$ 头奶牛（$1 \leq N \leq 20,000$），方便地用编号 $1 \ldots N$ 标识，其中奶牛 $j$ 能够在时间 $A_j$ 到时间 $B_j$ 之间过马路。考虑到“伙伴系统”是最好的方式，每头奶牛 $j$ 理想情况下希望找到一只鸡 $i$ 来帮助她过马路；为了使它们的日程安排兼容，$i$ 和 $j$ 必须满足 $A_j \leq T_i \leq B_j$。

如果每头奶牛最多只能与一只鸡配对，每只鸡也最多只能与一头奶牛配对，请计算可以构建的最大奶牛-鸡配对数。

## 样例 #1

### 输入

```
5 4
7
8
6
2
9
2 5
4 9
0 3
8 13```

### 输出

```
3```

# AI分析结果



### 综合分析与结论
本题核心是区间匹配问题，最优解法需结合排序策略与高效数据结构。关键思路为：将牛区间按右端点排序，鸡时间排序，用贪心策略为每个区间匹配最小可用鸡。主流解法分为两种流派：
1. **双排序+multiset**：O(n log n) 时间复杂度，利用STL容器快速查找
2. **单排序+优先队列**：O(n log n) 时间复杂度，动态维护候选区间

### 高分题解推荐

#### 1. 作者：Cutest_Junior（★★★★☆）
**核心亮点**：
- 详细数学证明贪心正确性
- 提供暴力与multiset优化双解法对比
- 代码简洁，利用STL实现高效匹配
```cpp
multiset<int> s;
sort(cow, cow+m); // 按右端点排序
for(auto &c : cow) {
    auto it = s.lower_bound(c.l);
    if(it != s.end() && *it <= c.r) {
        ans++;
        s.erase(it);
    }
}
```

#### 2. 作者：StudyingFather（★★★★★）
**核心亮点**：
- 创新性使用优先队列维护候选区间
- 时间复杂度严格O(n log n)
- 代码简洁高效，逻辑清晰
```cpp
priority_queue<seg> q; // 小根堆按右端点排序
sort(cow, cow+m, cmp_l); // 按左端点排序
for(int i=1; i<=n; i++) {
    while(cur<=m && cow[cur].l <= T[i]) 
        q.push(cow[cur++]);
    while(!q.empty() && q.top().r < T[i])
        q.pop();
    if(!q.empty()) ans++, q.pop();
}
```

#### 3. 作者：MyukiyoMekya（★★★★☆）
**创新点**：
- 并查集优化二分过程
- 实现O(n log n)时间且常数更小
- 独特的数据删除处理方式
```cpp
// 并查集维护可用点
int getf(int x) { 
    return f[x]==x ? x : f[x]=getf(f[x]);
}
for(区间排序后) {
    int pos = lower_bound(b+1, b+n+1, l);
    int root = getf(pos);
    if(b[root] <= r) {
        cnt[root]--;
        if(cnt[root]==0) f[root] = root+1;
    }
}
```

### 关键思路总结
1. **排序策略**：牛区间按右端点升序，鸡时间升序
2. **贪心原则**：为每个区间匹配满足条件的最小可用鸡
3. **数据结构**：
   - multiset实现快速查找删除
   - 优先队列动态维护候选区间
   - 并查集优化二分后的删除操作

### 同类题目推荐
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)（区间调度问题）
2. [P2859 [USACO06FEB] Stall Reservations S](https://www.luogu.com.cn/problem/P2859)（贪心+优先队列）
3. [P5021 赛道修建](https://www.luogu.com.cn/problem/P5021)（二分答案+贪心匹配）

### 调试心得摘录
- **Cutest_Junior**：初始按左端点排序导致WA，修正为右端点排序后AC
- **MC_Launcher**：暴力枚举TLE后意识到数据规模，改用正确排序策略
- **MVP_Harry**：实现平衡树时注意重复元素的处理

> "排序策略的选择直接影响贪心的正确性，右端点排序能保证优先处理更紧迫的区间" —— 来自多个题解的共同经验

---
处理用时：80.79秒