# 题目信息

# Constructive Problem

## 题目描述

给定整数 $n$ 和一个非负整数序列 $a$。  
对于非负整数序列 $c$，记 $\text{MEX}(c)$ 表示**不存在**于 $c$ 中的最小非负整数。  
记初始时 $m=\text{MEX}(a)$。  
你需要进行下列操作恰好一次：

- 选择整数 $l,r,k(1\leq l\leq r\leq n;0\leq k)$，然后将 $a_l,a_{l+1},\cdots,a_r$ 的值均变为 $k$。

判断能否通过恰好一次上述操作使操作后的 $a$ 满足 $\text{MEX}(a)=m+1$。  
能输出 `Yes`，不能输出 `No`。  
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
4
3
1 2 1
4
0 2 2 0
4
3 2 0 2
1
0```

### 输出

```
Yes
Yes
No
No```

# AI分析结果

### 题目内容重写

#### 构造性问题

##### 题目描述

给定整数 $n$ 和一个非负整数序列 $a$。  
对于非负整数序列 $c$，记 $\text{MEX}(c)$ 表示**不存在**于 $c$ 中的最小非负整数。  
记初始时 $m=\text{MEX}(a)$。  
你需要进行下列操作恰好一次：

- 选择整数 $l,r,k(1\leq l\leq r\leq n;0\leq k)$，然后将 $a_l,a_{l+1},\cdots,a_r$ 的值均变为 $k$。

判断能否通过恰好一次上述操作使操作后的 $a$ 满足 $\text{MEX}(a)=m+1$。  
能输出 `Yes`，不能输出 `No`。  
每个测试点包含 $t$ 组数据。

##### 样例 #1

###### 输入

```
4
3
1 2 1
4
0 2 2 0
4
3 2 0 2
1
0```

###### 输出

```
Yes
Yes
No
No```

### 算法分类
构造

### 题解分析与结论

本题的核心在于通过一次操作改变序列 $a$ 的某个子区间，使得操作后的序列的 MEX 值比原序列的 MEX 值大 1。具体来说，我们需要找到一种操作，使得新序列的 MEX 值为 $m+1$，其中 $m$ 是原序列的 MEX 值。

#### 关键思路
1. **MEX 值的计算**：首先计算原序列的 MEX 值 $m$。MEX 值是序列中缺失的最小非负整数。
2. **操作的影响**：通过一次操作将某个子区间的值全部改为 $k$，我们需要确保操作后的序列的 MEX 值为 $m+1$。
3. **条件判断**：
   - 如果 $m$ 不在原序列中，那么直接输出 `No`，因为无论如何操作，MEX 值不会改变。
   - 如果 $m$ 在原序列中，我们需要找到一个子区间，将其改为 $m+1$，并且确保操作后的序列的 MEX 值为 $m+1$。

#### 难点
- 如何确定操作的子区间和 $k$ 的值，使得操作后的序列的 MEX 值为 $m+1$。
- 需要确保操作后的序列中不包含 $m$，否则 MEX 值不会增加。

#### 最优思路
1. 首先计算原序列的 MEX 值 $m$。
2. 检查 $m$ 是否在原序列中，如果不在，则输出 `No`。
3. 如果 $m$ 在原序列中，尝试将某个包含 $m$ 的子区间改为 $m+1$，并检查操作后的序列的 MEX 值是否为 $m+1$。

### 推荐题目
1. [P3919 【模板】可持久化线段树 1（主席树）](https://www.luogu.com.cn/problem/P3919)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3368 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3368)

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // 计算 MEX
        set<int> s(a.begin(), a.end());
        int mex = 0;
        while (s.count(mex)) mex++;
        
        // 检查 mex 是否在 a 中
        bool contains_mex = false;
        for (int x : a) {
            if (x == mex) {
                contains_mex = true;
                break;
            }
        }
        
        if (!contains_mex) {
            cout << "No\n";
            continue;
        }
        
        // 尝试将某个包含 mex 的子区间改为 mex+1
        bool possible = false;
        for (int i = 0; i < n; i++) {
            if (a[i] == mex) {
                int j = i;
                while (j < n && a[j] == mex) j++;
                // 将 [i, j-1] 改为 mex+1
                vector<int> b = a;
                for (int k = i; k < j; k++) b[k] = mex + 1;
                // 计算新的 MEX
                set<int> s_new(b.begin(), b.end());
                int mex_new = 0;
                while (s_new.count(mex_new)) mex_new++;
                if (mex_new == mex + 1) {
                    possible = true;
                    break;
                }
                i = j - 1;
            }
        }
        
        cout << (possible ? "Yes\n" : "No\n");
    }
    return 0;
}
```

### 总结
本题的关键在于理解 MEX 值的定义，并通过一次操作改变序列的某个子区间，使得操作后的序列的 MEX 值比原序列的 MEX 值大 1。通过计算原序列的 MEX 值，并检查是否可以通过一次操作实现目标，可以有效地解决问题。

---
处理用时：35.38秒