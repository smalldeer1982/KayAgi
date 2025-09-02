# 题目信息

# [ABC378C] Repeating

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc378/tasks/abc378_c

给定一个长度为 $N$ 的正数序列  $A = (A_1, A_2, \ldots, A_N)$，请找出按照以下定义的长度为 $N$ 的序列 $B = (B_1, B_2, \ldots, B_N)$。

- 对于 $ i = 1, 2, \ldots, N$，给出 $B_i$ 定义如下：
  
  - 与 $A_i$ 相等的元素在 $i$ 之前出现的位置为 $b$。如果不存在这样的位置，则 $B_i = -1$。
  - 更具体地说，如果存在正整数 $j$，使得 $A_i = A_j$ 且 $j<i$ 存在，则 $B_i$ 是所有这样的 $j$ 中的最大值。如果不存在这样的 $j$，则 $B_i = -1$。。

## 说明/提示

### 约定

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 输入均为整数

### 样例解释

- $ i=1$：$A_1=1$ 前没有 $1$ 出现，因此 $B_1=-1$。
- $ i=2 $：$A_1=2$ 前没有 $2$ 出现，因此 $B_2=-1$。
- $ i=1 $：$A_1=1$ 前 $1$ 出现在 $A_1$，因此 $B_3=1$。
- $ i=1 $：$A_1=1$ 前 $1$ 出现在 $A_3$，因此 $B_4=3$。
- $ i=5 $：$A_5=3$ 前没有 $3$ 出现，因此 $B_5=-1$。

## 样例 #1

### 输入

```
5
1 2 1 1 3```

### 输出

```
-1 -1 1 3 -1```

## 样例 #2

### 输入

```
4
1 1000000000 1000000000 1```

### 输出

```
-1 -1 2 1```

# AI分析结果

### 题目中文重写
# [ABC378C] 重复

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc378/tasks/abc378_c

给定一个长度为 $N$ 的正数序列  $A = (A_1, A_2, \ldots, A_N)$，请找出按照以下定义的长度为 $N$ 的序列 $B = (B_1, B_2, \ldots, B_N)$。

- 对于 $ i = 1, 2, \ldots, N$，给出 $B_i$ 定义如下：
  
  - 与 $A_i$ 相等的元素在 $i$ 之前出现的位置为 $b$。如果不存在这样的位置，则 $B_i = -1$。
  - 更具体地说，如果存在正整数 $j$，使得 $A_i = A_j$ 且 $j<i$ 存在，则 $B_i$ 是所有这样的 $j$ 中的最大值。如果不存在这样的 $j$，则 $B_i = -1$。。

## 说明/提示

### 约定

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 输入均为整数

### 样例解释

- $ i=1$：$A_1=1$ 前没有 $1$ 出现，因此 $B_1=-1$。
- $ i=2 $：$A_2=2$ 前没有 $2$ 出现，因此 $B_2=-1$。
- $ i=3 $：$A_3=1$ 前 $1$ 出现在 $A_1$，因此 $B_3=1$。
- $ i=4 $：$A_4=1$ 前 $1$ 出现在 $A_3$，因此 $B_4=3$。
- $ i=5 $：$A_5=3$ 前没有 $3$ 出现，因此 $B_5=-1$。

## 样例 #1

### 输入

```
5
1 2 1 1 3
```

### 输出

```
-1 -1 1 3 -1
```

## 样例 #2

### 输入

```
4
1 1000000000 1000000000 1
```

### 输出

```
-1 -1 2 1
```

### 综合分析与结论
这些题解的核心思路都是要记录每个数最后一次出现的位置，从而确定序列 $B$ 中每个元素的值。由于 $A_i$ 的范围达到 $10^9$，直接开数组存储会超出内存限制，所以大部分题解使用 `map` 或 `unordered_map` 来解决这个问题。

#### 思路对比
- **`map` 或 `unordered_map` 解法**：多数题解采用这种方法，通过 `map` 或 `unordered_map` 存储每个数最后一次出现的下标，遍历序列 $A$ 时，若当前数已存在于映射中，则输出其最后一次出现的下标，否则输出 `-1`，并更新映射中该数的下标。
- **动态开点线段树解法**：xyz123 的题解使用动态开点线段树，虽然能解决问题，但实现复杂，代码量较大，且时间复杂度没有明显优势。

#### 算法要点
- **`map` 或 `unordered_map` 解法**：时间复杂度为 $O(n\log n)$（`map`）或接近 $O(n)$（`unordered_map`），空间复杂度为 $O(k)$，其中 $k$ 是序列 $A$ 中不同元素的个数。
- **动态开点线段树解法**：时间复杂度为 $O(n\log 10^9)$，空间复杂度为 $O(n\log 10^9)$。

#### 解决难点
- **内存限制**：通过使用 `map` 或 `unordered_map` 避免了直接开 $10^9$ 大小数组的内存问题。
- **查找效率**：`unordered_map` 的查找效率更高，平均时间复杂度为 $O(1)$，而 `map` 的查找时间复杂度为 $O(\log n)$。

### 所选题解
- **ikunTLE（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `unordered_map` 提高查找效率，并且有自定义的快速读入函数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
int a[N],b[N];
unordered_map<int,int>mp;
int main(){
    memset(b,-1,sizeof(b));
    int n=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    for(int i=1;i<=n;++i){
        if(mp.find(a[i])!=mp.end())
            b[i]=mp[a[i]];
        mp[a[i]]=i;
    }
    for(int i=1;i<=n;++i)
        printf("%d ",b[i]);
    printf("\n");
    return 0;
}
```
- **Chenyanxi0829（4星）**
    - **关键亮点**：代码简洁，使用 `map` 实现，且利用 `ios::sync_with_stdio(0), cin.tie(0)` 加速输入输出。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a;
map<int, int> h;
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a, cout << (h.count(a) ? h[a] : -1) << ' ', h[a] = i;
    }
    return 0;
}
```
- **PineappleSummer（4星）**
    - **关键亮点**：思路清晰，使用 `unordered_map` 实现，代码结构清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, a[N], b[N];
unordered_map <int, int> f;
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (f[a[i]]) b[i] = f[a[i]];
        else b[i] = -1;
        f[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) cout << b[i] << ' ';
    return 0;
}
```

### 最优关键思路或技巧
- **使用 `unordered_map`**：利用 `unordered_map` 的平均 $O(1)$ 查找时间复杂度，提高算法效率。
- **动态更新**：在遍历序列的过程中，动态更新每个数最后一次出现的下标，避免重复计算。

### 可拓展之处
同类型题目可能会有更多的限制条件，如序列长度更长、元素范围更大等。类似的算法套路可以应用在需要记录元素出现位置或频率的问题中，例如统计字符串中每个字符最后一次出现的位置、找出数组中重复元素的最早和最晚出现位置等。

### 推荐洛谷题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：需要统计元素出现的频率，可使用 `map` 或 `unordered_map` 解决。
2. [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)：需要模拟元素的删除和位置的变化，可使用链表或数组模拟。
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要根据元素的属性进行分组统计，可使用 `map` 存储分组信息。

### 个人心得摘录与总结
题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：53.14秒