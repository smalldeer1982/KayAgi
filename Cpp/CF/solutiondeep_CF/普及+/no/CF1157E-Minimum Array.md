# 题目信息

# Minimum Array

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ . All elements of both arrays are from $ 0 $ to $ n-1 $ .

You can reorder elements of the array $ b $ (if you want, you may leave the order of elements as it is). After that, let array $ c $ be the array of length $ n $ , the $ i $ -th element of this array is $ c_i = (a_i + b_i) \% n $ , where $ x \% y $ is $ x $ modulo $ y $ .

Your task is to reorder elements of the array $ b $ to obtain the lexicographically minimum possible array $ c $ .

Array $ x $ of length $ n $ is lexicographically less than array $ y $ of length $ n $ , if there exists such $ i $ ( $ 1 \le i \le n $ ), that $ x_i < y_i $ , and for any $ j $ ( $ 1 \le j < i $ ) $ x_j = y_j $ .

## 样例 #1

### 输入

```
4
0 1 2 1
3 2 1 1
```

### 输出

```
1 0 0 2 
```

## 样例 #2

### 输入

```
7
2 5 1 5 3 4 3
2 4 3 5 6 5 1
```

### 输出

```
0 0 0 1 0 2 4 
```

# AI分析结果

### 题目翻译
# 最小数组

## 题目描述
给定两个长度均为 $n$ 的数组 $a$ 和 $b$，两个数组中的所有元素都在 $0$ 到 $n - 1$ 之间。

你可以对数组 $b$ 的元素进行重新排序（如果你愿意，也可以保持元素的原有顺序）。之后，设数组 $c$ 是一个长度为 $n$ 的数组，该数组的第 $i$ 个元素 $c_i = (a_i + b_i) \% n$，其中 $x \% y$ 表示 $x$ 除以 $y$ 的余数。

你的任务是对数组 $b$ 的元素进行重新排序，以得到字典序最小的数组 $c$。

如果存在一个 $i$（$1 \leq i \leq n$），使得 $x_i < y_i$，并且对于任意的 $j$（$1 \leq j < i$）都有 $x_j = y_j$，那么长度为 $n$ 的数组 $x$ 在字典序上小于长度为 $n$ 的数组 $y$。

## 样例 #1
### 输入
```
4
0 1 2 1
3 2 1 1
```
### 输出
```
1 0 0 2 
```

## 样例 #2
### 输入
```
7
2 5 1 5 3 4 3
2 4 3 5 6 5 1
```
### 输出
```
0 0 0 1 0 2 4 
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即对于数组 $a$ 中的每个元素 $a_i$，在数组 $b$ 中找到一个合适的 $b_i$，使得 $(a_i + b_i) \% n$ 尽可能小。不同题解的区别主要在于实现方式和使用的数据结构。

- **使用 `std::multiset`**：大部分题解使用 `std::multiset` 来维护数组 $b$ 的元素，利用 `lower_bound` 函数快速找到大于等于 $n - a_i$ 的最小元素。
- **使用并查集优化**：部分题解使用并查集来优化查找过程，通过维护一个循环链表，链表里每个数指向比它大的最小的存在的数，并加上路径压缩优化。
- **使用树状数组**：有题解使用树状数组维护桶的前缀和，在桶上二分查找最小的出现过的位置。
- **使用分块**：还有题解使用分块维护，对于每个块维护块内第一个非 $0$ 位置。

### 所选题解
- **作者：「已注销」 (赞：9)，4星**
    - **关键亮点**：代码简洁，直接使用 `std::multiset` 实现贪心算法，思路清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
multiset<int>s;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)scanf("%d",&a[0]),s.insert(a[0]);
    for(int x,i=1;i<=n;++i){
        auto it=s.lower_bound((n-a[i])%n);
        if(it==s.end())x=*s.begin(),s.erase(s.begin());
        else x=*it,s.erase(it);
        printf("%d ",(x+a[i])%n);
    }
}
```
核心实现思想：先读入数组 $a$ 和数组 $b$ 的元素，将数组 $b$ 的元素插入 `multiset` 中。然后遍历数组 $a$，对于每个 $a_i$，使用 `lower_bound` 找到大于等于 $n - a_i$ 的最小元素，如果找不到则取 `multiset` 中的第一个元素，将其从 `multiset` 中删除并计算 $(a_i + b_i) \% n$ 输出。

- **作者：ModestCoder_ (赞：7)，4星**
    - **关键亮点**：使用并查集优化查找过程，思路新颖，代码实现巧妙。
```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
int n, a[maxn], cnt[maxn], nxt[maxn];

inline int read(){
    int s = 0, w = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
    for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
    return s * w;
}

int get(int x){ return cnt[x] ? x : nxt[x] = get(nxt[x]); }

int main(){
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= n; ++i){
        int x = read();
        ++cnt[x];
    }
    for (int i = 0; i < n; ++i) nxt[i] = i + 1; nxt[n] = 0;
    for (int i = 1; i <= n; ++i){
        int x = get(n - a[i]);
        --cnt[x]; printf("%d ", (a[i] + x) % n);
    }
    return 0;
}
```
核心实现思想：先读入数组 $a$ 和数组 $b$ 的元素，统计数组 $b$ 中每个元素的出现次数。然后初始化并查集的 `nxt` 数组，使其构成一个循环链表。遍历数组 $a$，对于每个 $a_i$，使用 `get` 函数找到大于等于 $n - a_i$ 的最小元素，将其出现次数减 1 并计算 $(a_i + b_i) \% n$ 输出。

- **作者：rui_er (赞：5)，4星**
    - **关键亮点**：同样使用并查集优化，代码规范，注释详细。
```cpp
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, a[N], b[N], cnt[N], nxt[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int find(int x) {return cnt[x] ? x : nxt[x] = find(nxt[x]);}

int main() {
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", &a[i]);
    rep(i, 1, n) scanf("%d", &b[i]);
    rep(i, 1, n) ++cnt[b[i]];
    rep(i, 0, n-1) nxt[i] = (i + 1) % n;
    rep(i, 1, n) {
        int ans = find(n-a[i]);
        printf("%d%c", (a[i]+ans)%n, " \n"[i==n]);
        --cnt[ans];
    }
    return 0;
}
```
核心实现思想：与 ModestCoder_ 的题解类似，先读入数组 $a$ 和数组 $b$ 的元素，统计数组 $b$ 中每个元素的出现次数，初始化并查集的 `nxt` 数组。遍历数组 $a$，对于每个 $a_i$，使用 `find` 函数找到大于等于 $n - a_i$ 的最小元素，将其出现次数减 1 并计算 $(a_i + b_i) \% n$ 输出。

### 最优关键思路或技巧
- **贪心策略**：对于数组 $a$ 中的每个元素 $a_i$，优先选择 $n - a_i$ 作为 $b_i$，若不存在则选择大于 $n - a_i$ 的最小元素，若仍不存在则选择数组 $b$ 中的最小元素。
- **数据结构优化**：使用 `std::multiset` 可以快速找到大于等于某个值的最小元素，使用并查集可以优化查找过程，减少时间复杂度。

### 拓展思路
同类型题或类似算法套路：
- 其他贪心算法的题目，如区间调度问题、活动选择问题等。
- 涉及数据结构优化的贪心问题，如使用堆、线段树等数据结构优化查找和更新操作。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：考察贪心算法在背包问题中的应用。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：考察贪心算法和区间调度问题。

### 个人心得摘录与总结
- **Parabola**：认为本题是本场穿越火线最水的题，比 A 题还简单，同时反思自己只切了 3 题，怀疑是晚上精力不好。总结：在比赛中要保持良好的状态和精力，遇到简单题要确保做对。
- **Bpds1110**：提供了一种比较蠢的考场写法，使用树状数组维护桶的前缀和，时间复杂度稍高但能通过。总结：在考场上如果想不到最优解法，可以尝试一些复杂度稍高但能解决问题的方法。

---
处理用时：61.87秒