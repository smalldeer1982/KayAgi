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
这些题解主要围绕如何处理数组 \(a\) 和 \(b\) 中 \(a_i > b_i\) 的区间来使满足条件的序列 \(p\) 长度最小。多数题解采用贪心策略，少数使用动态规划。主要思路是先确定序列 \(p\) 至少要达到 \(a\) 和 \(b\) 中的最大值 \(mx\)，以满足 \(a_i < b_i\) 的情况，再考虑 \(a_i > b_i\) 的情况如何插入到序列中。解决难点在于如何优化 \(a_i > b_i\) 区间的处理，避免不必要的步数浪费，例如合并相交区间、按特定顺序插入区间等。

### 所选的题解
- **作者：Coffee_zzz（5星）**
    - **关键亮点**：思路简洁清晰，直接将 \(a_i,b_i\) 看成区间，舍弃 \(a < b\) 的区间，对 \(a > b\) 的区间以 \(a_i\) 为第一关键字从大到小排序，合并相交区间后，通过特定方式枚举计算答案，无需复杂的动态规划。
- **作者：Komomo（5星）**
    - **关键亮点**：对问题分析全面细致，将区间分为「上升区间」和「下降区间」，通过对样例的分析得出向前插入下降区间的规律，即按 \(b_i\) 从小到大排序取前缀插入更优，同时考虑了区间包含和相交的情况并进行优化处理，代码实现清晰。
    - **核心代码**：
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
    - **核心实现思想**：先读入数据，记录下降区间，若没有下降区间直接输出 \(a\) 和 \(b\) 的最大值。对下降区间按右端点排序，处理区间包含和相交情况，再通过前缀和的方式计算不同插入方式下的代价，从而得到最小长度。
- **作者：佬头（4星）**
    - **关键亮点**：先构造上升序列解决 \(a_k < b_k\) 的情况，再对 \(a_k > b_k\) 的情况按 \(a\) 降序排列，针对同一 \(a\) 选最小 \(b\)，并分析出三种插入情况，通过计算不同插入方式的代价取最小值得到最终答案，思路较清晰。
    - **核心代码**：
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
    - **核心实现思想**：读入数据，去除 \(a < b\) 的情况，对剩余情况按 \(a\) 降序排序，遍历计算不同插入方式代价，更新最小代价，最后加上上升序列长度得到答案。

### 最优关键思路或技巧
1. **区间合并**：将相交的 \(a_i > b_i\) 区间合并，能避免在满足这些区间要求时产生不必要的步数浪费，从而优化序列长度。
2. **排序策略**：对 \(a_i > b_i\) 的区间按 \(a_i\) 降序或 \(b_i\) 升序等特定顺序排序，有助于找到最优插入方式，减少计算量。

### 可拓展思路
同类型题通常围绕序列构造与优化，类似算法套路为分析不同条件对序列的影响，通过贪心策略选择最优的构造方式，例如在满足某些元素先后顺序要求下，使序列长度最短或代价最小。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序贪心求解最优解。
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需分析游戏规则，利用贪心和排序策略寻找最优策略。
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对元素排序，贪心得到最小总时间。 

---
处理用时：66.63秒