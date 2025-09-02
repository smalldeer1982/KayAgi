# 题目信息

# k-Amazing Numbers

## 题目描述

You are given an array $ a $ consisting of $ n $ integers numbered from $ 1 $ to $ n $ .

Let's define the $ k $ -amazing number of the array as the minimum number that occurs in all of the subsegments of the array having length $ k $ (recall that a subsegment of $ a $ of length $ k $ is a contiguous part of $ a $ containing exactly $ k $ elements). If there is no integer occuring in all subsegments of length $ k $ for some value of $ k $ , then the $ k $ -amazing number is $ -1 $ .

For each $ k $ from $ 1 $ to $ n $ calculate the $ k $ -amazing number of the array $ a $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
5
4 4 4 4 2
6
1 3 1 5 3 1```

### 输出

```
-1 -1 3 2 1 
-1 4 4 4 2 
-1 -1 1 1 1 1```

# AI分析结果

### 题目内容重写
# k-Amazing Numbers

## 题目描述

给定一个由 $n$ 个整数组成的数组 $a$，编号从 $1$ 到 $n$。

定义数组的 $k$ -amazing number 为在所有长度为 $k$ 的子段中出现的最小数字（子段是指数组中连续的 $k$ 个元素）。如果对于某个 $k$ 值，没有数字在所有长度为 $k$ 的子段中出现，则 $k$ -amazing number 为 $-1$。

对于每个 $k$ 从 $1$ 到 $n$，计算数组 $a$ 的 $k$ -amazing number。

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
5
4 4 4 4 2
6
1 3 1 5 3 1```

### 输出

```
-1 -1 3 2 1 
-1 4 4 4 2 
-1 -1 1 1 1 1```

### 算法分类
贪心、排序

### 题解分析与结论
1. **STDquantum的题解**（5星）
   - **关键亮点**：通过性质1和性质2，巧妙地利用最大距离和前缀最小值来解决问题，代码简洁高效。
   - **核心思想**：计算每个数两两之间的最大距离，然后用一个数组记录这些距离对应的最小数字，最后通过前缀最小值得到答案。
   - **代码实现**：
     ```cpp
     for (int i = 1; i <= n; ++i) {
         read(a[i]);
         max(maxx[a[i]], i - las[a[i]]);
         las[a[i]] = i;
     }
     for (int i = 1; i <= n; ++i) max(maxx[a[i]], n + 1 - las[a[i]]);
     for (int i = 1; i <= n; ++i) min(pos[maxx[a[i]]], a[i]);
     for (int i = 1; i <= n; ++i) {
         min(pos[i], pos[i - 1]);
         write(pos[i] == inf ? -1 : pos[i]), putchar(' ');
     }
     ```

2. **江户川·萝卜的题解**（4星）
   - **关键亮点**：通过排序和栈来优化内存使用，思路清晰。
   - **核心思想**：对每个数找到其最大距离，然后更新答案数组，最后输出时取最小值。
   - **代码实现**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         if (p[i].first == p[i-1].first) {
             maxl = max(maxl, p[i].second - lstp);
             lstp = p[i].second;
         } else {
             maxl = max(maxl, n - lstp + 1);
             if (!ans[maxl]) {
                 ans[maxl] = p[i-1].first;
                 st.push(maxl);
             }
             lstp = p[i].second; maxl = lstp;
         }
     }
     ```

3. **寒冰大大的题解**（4星）
   - **关键亮点**：使用vector记录每个数字的位置，计算最大差值后更新答案数组，思路清晰。
   - **核心思想**：对每个数字的位置进行记录，计算最大差值，然后更新答案数组，最后通过前缀最小值得到答案。
   - **代码实现**：
     ```cpp
     for (i = 1; i <= n; i++) {
         v[i].push_back(n + 1);
         deltammx = 0;
         for (j = 1; j < v[i].size(); j++)
             deltammx = max(v[i][j] - v[i][j - 1], deltammx);
         if (v[i].size() != 2) {
             f[deltammx] = min(f[deltammx], i);
         }
         v[i].clear();
     }
     ```

### 最优关键思路或技巧
1. **性质1和性质2**：通过分析数字在子段中的出现规律，利用最大距离和前缀最小值来高效求解。
2. **排序和栈优化**：通过排序和栈来优化内存使用，提高代码效率。
3. **vector记录位置**：使用vector记录每个数字的位置，方便计算最大差值。

### 可拓展之处
类似的问题可以通过分析数字在子段中的出现规律，利用最大距离和前缀最小值来高效求解。可以扩展到其他需要统计子段中数字出现频率的问题。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)

### 个人心得摘录
- **STDquantum**：通过性质1和性质2，巧妙地利用最大距离和前缀最小值来解决问题，代码简洁高效。
- **江户川·萝卜**：通过排序和栈来优化内存使用，思路清晰。
- **寒冰大大**：使用vector记录每个数字的位置，计算最大差值后更新答案数组，思路清晰。

---
处理用时：36.88秒