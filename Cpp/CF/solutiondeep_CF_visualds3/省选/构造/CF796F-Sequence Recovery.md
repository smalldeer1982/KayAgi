# 题目信息

# Sequence Recovery

## 题目描述

Zane once had a good sequence $ a $ consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ — but he has lost it.

A sequence is said to be good if and only if all of its integers are non-negative and do not exceed $ 10^{9} $ in value.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796F/7c34d2981d5a0342e098e7b1d14d4ca5448e48f2.png)However, Zane remembers having played around with his sequence by applying $ m $ operations to it.

There are two types of operations:

1\. Find the maximum value of integers with indices $ i $ such that $ l<=i<=r $ , given $ l $ and $ r $ .

2\. Assign $ d $ as the value of the integer with index $ k $ , given $ k $ and $ d $ .

After he finished playing, he restored his sequence to the state it was before any operations were applied. That is, sequence $ a $ was no longer affected by the applied type 2 operations. Then, he lost his sequence at some time between now and then.

Fortunately, Zane remembers all the operations and the order he applied them to his sequence, along with the distinct results of all type 1 operations. Moreover, among all good sequences that would produce the same results when the same operations are applied in the same order, he knows that his sequence $ a $ has the greatest cuteness.

We define cuteness of a sequence as the bitwise OR result of all integers in such sequence. For example, the cuteness of Zane's sequence $ a $ is $ a_{1} $ OR $ a_{2} $ OR ... OR $ a_{n} $ .

Zane understands that it might not be possible to recover exactly the lost sequence given his information, so he would be happy to get any good sequence $ b $ consisting of $ n $ integers $ b_{1},b_{2},...,b_{n} $ that:

1\. would give the same results when the same operations are applied in the same order, and

2\. has the same cuteness as that of Zane's original sequence $ a $ .

If there is such a sequence, find it. Otherwise, it means that Zane must have remembered something incorrectly, which is possible.

## 说明/提示

In the first sample, it is easy to verify that this good sequence is valid. In particular, its cuteness is $ 19 $ OR $ 0 $ OR $ 0 $ OR $ 0 $ OR $ 1 $ $ = $ $ 19 $ .

In the second sample, the two operations clearly contradict, so there is no such good sequence.

## 样例 #1

### 输入

```
5 4
1 1 5 19
1 2 5 1
2 5 100
1 1 5 100
```

### 输出

```
YES
19 0 0 0 1
```

## 样例 #2

### 输入

```
5 2
1 1 5 0
1 1 5 100
```

### 输出

```
NO```

# AI分析结果

---
# 💡 Kay的C++算法解析：Sequence Recovery 深入学习指南 💡

<introduction>
  今天我们来一起分析「Sequence Recovery」这道C++编程题。题目需要我们根据Zane回忆的操作序列，还原满足条件的「好序列」——既要让所有查询操作的结果正确，还要让序列的「cuteness」（所有元素的位或）最大。本指南会帮你拆解问题、理解核心算法，并掌握关键技巧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数据结构（线段树）+ 贪心策略`

🗣️ **初步分析**：
解决这道题的关键，是用**线段树**处理「动态区间查询/修改」，再用**贪心**最大化序列的位或结果。打个比方：  
- 线段树就像一个「智能书架管理系统」——你可以快速查某层书架（区间）的最大书号（最大值），也能修改某本书的位置（单点修改）；  
- 贪心策略则像「凑最大拼图」——先填必须的碎片（被限制的位置），再补剩下的部分（未被限制的位置），确保最终的「拼图总和」（位或）最大。  

### 核心思路拆解
1. **正向验证合法性**：用线段树模拟所有操作，检查每个查询结果是否合理（比如修改后的值不能超过查询的最大值）；  
2. **逆向维护限制**：倒序遍历操作，用另一个线段树记录每个位置能取的**最大允许值**（因为修改操作会「覆盖」后续的限制，倒序处理能准确还原每个位置的上限）；  
3. **贪心构造序列**：先填被限制的位置（优先选能贡献高位的数），再处理未被限制的位置——从最高位（30位，因为1e9不超过2^30）开始尝试添加，确保位或结果最大。  

### 可视化设计思路
我们会用**8位像素风**（类似FC红白机）做动画，核心展示：  
- 线段树的「区间查询」：用黄色高亮查询的区间，最大值位置闪烁；  
- 线段树的「单点修改」：目标位置变成蓝色，伴随「叮」的音效；  
- 贪心的「位选择」：未确定位置的二进制位从高位到低位逐个亮起，选中的位用绿色标记，伴随「滴」的音效。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码有效性、实践价值等维度筛选出1份优质题解（评分4.5星），帮你快速抓住核心！
</eval_intro>

**题解一：(来源：KaisuoShutong)**
* **点评**：这份题解的思路非常「闭环」——从正向验证到逆向限制，再到贪心构造，每一步都紧扣题目要求。  
  - **思路清晰**：用两棵线段树分别处理「正向合法性」和「逆向限制」，逻辑链条完整；  
  - **算法高效**：线段树的时间复杂度是O(m log n)，完全能处理题目中的数据规模；  
  - **贪心巧妙**：对于被限制的位置，用`(1<<(int)log2(v))-1`（比如v=5→101，取11=3）确保不超过限制的同时，尽可能保留低位（不影响最终的位或）；对于未被限制的位置，从高位到低位尝试添加，最大化位或结果；  
  - **实践严谨**：代码中处理了「无解」的情况（比如正向验证时发现修改后的值超过查询最大值），边界条件考虑周全。  


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的「坑点」主要集中在「如何用线段树处理动态操作」和「如何贪心最大化位或」。结合题解，我帮你提炼了3个核心关键点：
</difficulty_intro>

1. **关键点1：正向验证——如何用线段树模拟操作？**
    * **分析**：正向遍历操作时，遇到「查询」就用线段树查区间最大值，检查是否等于题目给的结果；遇到「修改」就更新线段树的单点值。如果查询到的最大值大于题目给的结果，说明无解（比如样例2中两次查询结果矛盾）。  
    * 💡 **学习笔记**：线段树是处理「动态区间查询/修改」的「瑞士军刀」，一定要熟练掌握基础操作！

2. **关键点2：逆向限制——如何记录每个位置的最大允许值？**
    * **分析**：倒序遍历操作时，遇到「查询」就用线段树将该区间的所有位置的「最大允许值」更新为查询的结果（因为原序列在查询时的最大值是这个数，所以区间内至少有一个位置等于它，其他位置不能超过它）；遇到「修改」就清除该位置的限制（因为修改后的操作不影响原序列）。  
    * 💡 **学习笔记**：倒序处理能「抵消」修改操作的影响，准确还原原序列的限制！

3. **关键点3：贪心构造——如何让位或结果最大？**
    * **分析**：位或的特性是「只要某一位有1，结果就有1」。所以：  
      - 被限制的位置：优先选能贡献高位的数（比如限制是v，选`(1<<log2(v))-1`能保留所有比最高位低的位，不浪费）；  
      - 未被限制的位置：从最高位（30位）到最低位（0位）尝试添加，如果添加后不超过1e9且能增加位或结果，就选这个位。  
    * 💡 **学习笔记**：贪心的核心是「优先满足高位」，因为高位对结果的影响更大！

### ✨ 解题技巧总结
- **技巧1：线段树的「双向应用」**：正向用单改区查线段树，逆向用区改线段树，处理不同的需求；  
- **技巧2：位运算的「贪心策略」**：位或的最大化需要优先填充高位，这是很多位运算题的通用思路；  
- **技巧3：边界条件的「严谨性」**：一定要处理「无解」的情况（比如正向验证不通过、逆向限制后没有位置能满足查询结果）。  


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份综合题解思路的「通用核心实现」，帮你把握整体框架！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了题解的核心逻辑，包含线段树的实现、正向验证、逆向限制和贪心构造。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;
const long long INF = 1e18;

// 正向线段树：单改区查最大值
struct MaxSegTree {
    long long tree[MAXN << 2];
    void pushup(int rt) { tree[rt] = max(tree[rt<<1], tree[rt<<1|1]); }
    void build(int rt, int l, int r) {
        if (l == r) { tree[rt] = 0; return; }
        int mid = (l + r) >> 1;
        build(rt<<1, l, mid);
        build(rt<<1|1, mid+1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int pos, long long val) {
        if (l == r) { tree[rt] = val; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(rt<<1, l, mid, pos, val);
        else update(rt<<1|1, mid+1, r, pos, val);
        pushup(rt);
    }
    long long query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tree[rt];
        int mid = (l + r) >> 1;
        long long res = 0;
        if (L <= mid) res = max(res, query(rt<<1, l, mid, L, R));
        if (R > mid) res = max(res, query(rt<<1|1, mid+1, r, L, R));
        return res;
    }
} max_st;

// 逆向线段树：区改（赋值最小值），单点查询
struct MinSegTree {
    long long tree[MAXN << 2], lazy[MAXN << 2];
    void pushdown(int rt, int l, int r) {
        if (lazy[rt] == INF) return;
        tree[rt<<1] = min(tree[rt<<1], lazy[rt]);
        tree[rt<<1|1] = min(tree[rt<<1|1], lazy[rt]);
        lazy[rt<<1] = min(lazy[rt<<1], lazy[rt]);
        lazy[rt<<1|1] = min(lazy[rt<<1|1], lazy[rt]);
        lazy[rt] = INF;
    }
    void build(int rt, int l, int r) {
        tree[rt] = INF; lazy[rt] = INF;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt<<1, l, mid);
        build(rt<<1|1, mid+1, r);
    }
    void update(int rt, int l, int r, int L, int R, long long val) {
        if (L <= l && r <= R) {
            tree[rt] = min(tree[rt], val);
            lazy[rt] = min(lazy[rt], val);
            return;
        }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) update(rt<<1, l, mid, L, R, val);
        if (R > mid) update(rt<<1|1, mid+1, r, L, R, val);
    }
    void clear(int rt, int l, int r, int pos) {
        if (l == r) { tree[rt] = INF; return; }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid) clear(rt<<1, l, mid, pos);
        else clear(rt<<1|1, mid+1, r, pos);
    }
    long long query(int rt, int l, int r, int pos) {
        if (l == r) return tree[rt];
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid) return query(rt<<1, l, mid, pos);
        else return query(rt<<1|1, mid+1, r, pos);
    }
} min_st;

int n, m;
int ty[MAXN], L[MAXN], R[MAXN];
long long V[MAXN], lim[MAXN];
long long w[MAXN], a[MAXN];
bool mp[MAXN]; // 标记是否已经使用过某个值

void NO() {
    cout << "NO" << endl;
    exit(0);
}

int main() {
    cin >> n >> m;
    max_st.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        cin >> ty[i];
        if (ty[i] == 1) {
            cin >> L[i] >> R[i] >> V[i];
            long long t = max_st.query(1, 1, n, L[i], R[i]);
            if (t > V[i]) NO(); // 修改后的值超过查询结果，无解
            else if (t < V[i]) lim[i] = 1; // 需要后续处理
        } else {
            cin >> L[i] >> V[i];
            max_st.update(1, 1, n, L[i], V[i]);
        }
    }

    // 逆向处理，维护每个位置的最大允许值
    min_st.build(1, 1, n);
    for (int i = m; i >= 1; i--) {
        if (ty[i] == 1) {
            min_st.update(1, 1, n, L[i], R[i], V[i]);
        } else {
            min_st.clear(1, 1, n, L[i]); // 清除修改操作的影响
        }
    }

    // 收集每个位置的最大允许值
    for (int i = 1; i <= n; i++) {
        w[i] = min_st.query(1, 1, n, i);
        if (w[i] == INF) w[i] = 1e9; // 无限制的位置，上限是1e9
    }

    // 检查是否所有需要的最大值都存在
    memset(mp, 0, sizeof(mp));
    for (int i = 1; i <= n; i++) {
        if (w[i] != 1e9) mp[w[i]] = 1;
    }
    for (int i = 1; i <= m; i++) {
        if (ty[i] == 1 && lim[i] && !mp[V[i]]) NO();
    }

    // 构造序列
    long long all = 0;
    memset(mp, 0, sizeof(mp));
    for (int i = 1; i <= n; i++) {
        if (w[i] != 1e9) {
            if (!mp[w[i]]) {
                a[i] = w[i];
                mp[w[i]] = 1;
            } else {
                // 选(1<<log2(w[i]))-1，不超过限制且保留低位
                int k = log2(w[i]);
                a[i] = (1LL << k) - 1;
            }
            all |= a[i];
        } else {
            a[i] = 0;
        }
    }

    // 处理未被限制的位置，贪心最大化位或
    for (int i = 1; i <= n; i++) {
        if (w[i] == 1e9) {
            for (int j = 30; j >= 0; j--) { // 1e9不超过2^30
                if (!(all & (1LL << j))) { // 该位还没被设置
                    if (a[i] + (1LL << j) <= 1e9) {
                        a[i] += (1LL << j);
                        all |= (1LL << j);
                    }
                }
            }
        }
    }

    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
```
* **代码解读概要**：  
  1. **线段树实现**：`MaxSegTree`处理正向的「单改区查」，`MinSegTree`处理逆向的「区改单点查」；  
  2. **正向验证**：遍历操作，用`MaxSegTree`检查查询结果的合法性；  
  3. **逆向限制**：倒序遍历操作，用`MinSegTree`记录每个位置的最大允许值；  
  4. **贪心构造**：先填被限制的位置，再处理未被限制的位置，从高位到低位尝试添加位，最大化位或结果。


<code_intro_selected>
接下来剖析题解中的「贪心构造」核心片段，这是最大化位或的关键！
</code_intro_selected>

**题解一：(来源：KaisuoShutong)**
* **亮点**：用「位运算贪心」巧妙处理未被限制的位置，确保位或结果最大。
* **核心代码片段**：
```cpp
for(int i=1;i<=n;cout<<a[i++]<<' ') if(w[i]==inf) {
	for(int j=30;~j;j--) if(!(all>>j&1)) {
		if(a[i]+(1<<j)<=1e9) a[i]+=(1<<j);
	}all|=a[i];
}
```
* **代码解读**：  
  - `w[i] == inf`表示该位置未被限制（上限是1e9）；  
  - `j`从30到0遍历（因为1e9不超过2^30），检查`all`的第`j`位是否为0（`!(all>>j&1)`）；  
  - 如果该位为0，且添加`2^j`后不超过1e9，就将`a[i]`加上`2^j`，并更新`all`（位或上这个值）。  
  比如，`all`当前是`1010`（二进制），那么`j=3`（第4位）是0，就尝试添加`8`（1000），让`all`变成`1110`，最大化结果。
* 💡 **学习笔记**：位或的贪心一定要「优先填高位」，因为高位的权重是低位的两倍！  


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观理解「线段树操作」和「贪心位选择」，我设计了一个**8位像素风动画**——《线段树探险家》，结合复古游戏元素，让算法「动」起来！
</visualization_intro>

### 🎮 动画演示主题
你是一位「像素探险家」，需要用线段树解开「序列恢复」的谜题。屏幕左侧是**线段树面板**，右侧是**序列面板**，底部是**操作控制面板**。

### 🎨 设计思路
- **8位像素风**：用红白机的色彩（红、蓝、黄、绿），线段树节点是方块，序列元素是小格子，营造复古氛围；  
- **音效强化**：查询操作伴随「叮」声，修改操作伴随「啪」声，贪心选位伴随「滴」声，胜利时播放「通关音乐」；  
- **交互设计**：支持「单步执行」「自动播放」（速度可调），点击「重置」可重新开始。

### 🚶 动画帧步骤
1. **初始化场景**：  
   - 线段树面板显示空的线段树（所有节点为0）；  
   - 序列面板显示5个空格子（对应样例1的n=5）；  
   - 控制面板显示「开始」「单步」「重置」按钮，速度滑块（1x~5x）。

2. **正向验证阶段**：  
   - 操作1（查询1-5，结果19）：线段树的1-5区间高亮黄色，最大值位置（第1位）闪烁，伴随「叮」声；  
   - 操作2（查询2-5，结果1）：线段树的2-5区间高亮黄色，最大值位置（第5位）闪烁；  
   - 操作3（修改第5位为100）：序列面板第5位变成蓝色，线段树对应节点更新，伴随「啪」声；  
   - 操作4（查询1-5，结果100）：线段树的1-5区间高亮黄色，最大值位置（第5位）闪烁。

3. **逆向限制阶段**：  
   - 倒序处理操作4（查询1-5，结果100）：线段树的1-5区间变成绿色（标记最大允许值100）；  
   - 倒序处理操作3（修改第5位）：序列面板第5位变回白色（清除限制）；  
   - 倒序处理操作2（查询2-5，结果1）：线段树的2-5区间变成绿色（标记最大允许值1）；  
   - 倒序处理操作1（查询1-5，结果19）：线段树的1-5区间变成绿色（标记最大允许值19）。

4. **贪心构造阶段**：  
   - 处理被限制的位置：第1位填19（红色），第5位填1（红色），其他被限制的位置填`(1<<log2(v))-1`（橙色）；  
   - 处理未被限制的位置（第2-4位）：从30位到0位遍历，每个位置的二进制位逐个亮起绿色，伴随「滴」声，最终填0（因为位或已经包含19和1的所有位）。

5. **胜利状态**：  
   - 序列面板所有格子亮起，播放「通关音乐」，屏幕显示「序列恢复成功！」。

<visualization_conclusion>
通过这个动画，你能清晰看到线段树的「查询/修改」过程，以及贪心「填高位」的逻辑——就像玩游戏一样，边看边学，记忆更深刻！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
线段树和贪心是「算法工具箱」里的常用工具，学会了这道题，可以解决很多类似问题！
</similar_problems_intro>

### 🧰 通用思路迁移
- **线段树的应用场景**：需要动态查询区间最大值/最小值/和，或者动态修改单点/区间的值（比如「区间加值」「区间赋值」）；  
- **贪心的应用场景**：需要最大化/最小化某个值（比如位或、和、乘积），且每一步的选择不影响后续的最优解（比如「活动选择问题」「 Huffman编码」）。

### 📝 洛谷练习推荐
1. **洛谷 P3372** - 线段树1  
   * 🗣️ **推荐理由**：基础线段树模板题，练习「区间加值」和「区间求和」，巩固线段树的基本操作。  
2. **洛谷 P3373** - 线段树2  
   * 🗣️ **推荐理由**：进阶线段树题，练习「区间乘值」「区间加值」和「区间求和」，掌握「延迟标记」的用法。  
3. **洛谷 P1816** - 忠诚  
   * 🗣️ **推荐理由**：区间最大值查询题，用线段树解决，和本题的「正向验证」部分思路一致。  


## 7. 学习心得与经验分享 (若有)
<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分，但通过题解的代码和思路，我们能学到「用线段树处理动态操作」和「位运算贪心」的技巧。
</insights_intro>


<conclusion>
本次关于「Sequence Recovery」的分析就到这里！这道题的核心是「线段树+贪心」，关键在于理解「正向验证」和「逆向限制」的逻辑，以及「位或最大化」的贪心策略。记住：算法的学习不是死记硬背，而是理解「为什么这样做」——就像玩游戏一样，多试几次，就能找到通关的钥匙！下次我们再一起探索新的算法挑战！💪
</conclusion>

---

---
处理用时：141.61秒