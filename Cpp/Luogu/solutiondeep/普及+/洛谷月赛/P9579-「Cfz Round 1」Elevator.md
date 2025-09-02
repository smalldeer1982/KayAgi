# 题目信息

# 「Cfz Round 1」Elevator

## 题目背景

电梯是一个可以让人充分思考的空间。

## 题目描述

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $p$ 是满足条件的，设 $p$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $p$ 中，$p$ 的长度的最小值。

## 说明/提示

#### 【样例解释 #1】

序列 $p$ 的长度的最小值为 $7$，此时的序列 $p$ 为 $\{1,2,3,2,3,4,5\}$。

#### 【数据范围】

对于所有数据，$1 \le n \le 5\times10^5$，$1 \le a_i,b_i \le 10^9$，保证 $a_i \neq b_i$。

**本题采用捆绑测试。**

|子任务编号|分值|$n \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$9$|$1$|无|
|$2$|$9$|$5\times10^5$|保证 $a_i < b_i$|
|$3$|$21$|$5\times10^5$|数据随机生成|
|$4$|$27$|$2000$|无|
|$5$|$34$|$5\times10^5$|无|

## 样例 #1

### 输入

```
2
3 2
2 5```

### 输出

```
7```

## 样例 #2

### 输入

```
4
4 7
10 8
9 11
4 2```

### 输出

```
18```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何通过贪心或动态规划的方法，解决在给定数组 \(a\) 和 \(b\) 的条件下，找到满足特定条件序列 \(p\) 的最小长度问题。思路上，大多先处理 \(a_i < b_i\) 的情况，再考虑 \(a_i > b_i\) 的情况。算法要点包括对区间的合并、排序以及不同插入方式代价的计算。解决难点在于如何优化插入 \(a_i > b_i\) 区间的方式，使总长度最小。

### 所选的题解
1. **作者：Coffee_zzz (5星)**
    - **关键亮点**：思路简洁清晰，直接舍弃 \(a < b\) 的区间，对 \(a > b\) 的区间排序合并后，通过特定的枚举方式计算最小长度，无需复杂的动态规划。
2. **作者：Komomo (4星)**
    - **关键亮点**：对下降区间（\(a_i > b_i\)）的插入代价分析详细，通过对区间包含、相交情况的处理，得出按 \(b_i\) 排序取前缀最小值的方法，代码实现与思路结合紧密。
    ```cpp
    int n, L, ans, up, lo = 2e9;
    struct Node { int l, r; } p[maxn], r[maxn];
    bool cmp(Node a, Node b) { return a.r < b.r || a.r == b.r && a.l > b.l; } 
    signed main() {
        n = read(); 
        for (int i = 1; i <= n; i ++) {
            int l = read(), r = read(); up = max({up, l, r});
            if (l > r) lo = min(lo, r), p[++ L] = Node {l, r};
        }
        if (lo == 2e9) return cout << up, 0; 
        ans = up + (up - lo), sort(p + 1, p + L + 1, cmp);
        int tmp = L; r[L = 1] = p[1]; 
        for (int i = 2; i <= tmp; i ++)
            if (!(r[L].r <= p[i].r && p[i].l <= r[L].l)) { 
                if (r[L].l >= p[i].r && p[i].r >= r[L].r) r[L].l = p[i].l; 
                else r[++ L] = p[i]; 
            }
        int del = 0, sum = 0; 
        r[L + 1].r = up; 
        for (int i = 1; i <= L; i ++) { 
            sum += 2 * (r[i].l - r[i].r);
            del = min((lo - r[i + 1].r) + sum, del);
        }
        cout << ans + del << endl;
        return 0;
    }
    ```
    - **核心实现思想**：先读入数据，将 \(a > b\) 的区间存入 \(p\) 数组，若不存在则直接输出 \(a\) 和 \(b\) 中的最大值。对 \(p\) 数组按右端点排序，处理区间包含和相交情况并存入 \(r\) 数组。通过遍历 \(r\) 数组计算不同插入方式下的代价变化，得出最小长度。
3. **作者：佬头 (4星)**
    - **关键亮点**：对 \(a_i > b_i\) 的情况分析全面，提出三种插入方式并简化代价计算，通过排序和逐步计算代价的方式得到最终答案，代码简洁明了。
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;
    const int N = 500005;
    int n, cnt, maxx, minn, ans;
    pair <int, int> s[N];
    int read(){
        int x = 0;
        char a = getchar();
        while(a < '0' || '9' < a) a = getchar();
        while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
        return x;
    }
    void write(int x){
        if(x > 9) write(x / 10);
        putchar(x % 10 | 48);
    }
    int main(){
        n = read();
        for(int i = 1; i <= n; ++ i){
            s[++ cnt].first = read(), s[cnt].second = read();
            if(s[cnt].first > maxx) maxx = s[cnt].first;
            if(s[cnt].second > maxx) maxx = s[cnt].second;
            if(s[cnt].first < s[cnt].second) cnt --;
        }
        minn = maxx;
        sort(s + 1, s + 1 + cnt);
        for(int i = cnt; i >= 1; -- i)
            if(s[i].first!= s[i - 1].first && minn > s[i].second){
                ans += (min(minn, s[i].first) - s[i].second) << 1;
                minn = s[i].second;
                if(ans > maxx - minn) ans = maxx - minn;
            }
        write(maxx + ans);
        return 0;
    }
    ```
    - **核心实现思想**：读入数据，去除 \(a < b\) 的区间，找到 \(a\) 和 \(b\) 中的最大值 \(maxx\)。对剩余区间按 \(a\) 降序排序，遍历区间计算插入代价，每次更新最小代价和当前最小值 \(minn\)，最后输出 \(maxx\) 与最小代价之和。

### 最优关键思路或技巧
1. **区间合并与排序**：将 \(a_i > b_i\) 的区间进行合并和排序，减少冗余计算，如按 \(a_i\) 降序或 \(b_i\) 升序排序，方便后续处理。
2. **代价分析与比较**：对不同的插入方式进行代价分析，通过比较不同插入方式的代价来确定最优方案，如从最高点下降、在上升途中下降再上升等方式。

### 可拓展思路
同类型题可关注区间相关的构造、优化问题，类似算法套路包括对区间的预处理（合并、排序），以及对不同操作代价的分析比较。例如，在一些路径规划或资源分配问题中，可将问题转化为区间上的操作，并通过类似的贪心策略求解。

### 相似知识点洛谷题目
1. **P1248 加工生产调度**：涉及任务调度和时间优化，可通过贪心策略解决，与本题对不同情况的代价分析和优化选择类似。
2. **P1080 [NOIP2012 提高组] 国王游戏**：通过对数据的排序和贪心策略来解决最优解问题，与本题处理区间的排序和贪心选择思路相似。
3. **P2859 [USACO06DEC]Milk Patterns G**：需要对数据进行预处理和分析，利用贪心或其他策略找到最优解，与本题的区间处理和优化思路有相通之处。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：85.70秒