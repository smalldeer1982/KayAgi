# 题目信息

# Sofia and the Lost Operations

## 题目描述

Sofia had an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . One day she got bored with it, so she decided to sequentially apply $ m $ modification operations to it.

Each modification operation is described by a pair of numbers $ \langle c_j, d_j \rangle $ and means that the element of the array with index $ c_j $ should be assigned the value $ d_j $ , i.e., perform the assignment $ a_{c_j} = d_j $ . After applying all modification operations sequentially, Sofia discarded the resulting array.

Recently, you found an array of $ n $ integers $ b_1, b_2, \ldots, b_n $ . You are interested in whether this array is Sofia's array. You know the values of the original array, as well as the values $ d_1, d_2, \ldots, d_m $ . The values $ c_1, c_2, \ldots, c_m $ turned out to be lost.

Is there a sequence $ c_1, c_2, \ldots, c_m $ such that the sequential application of modification operations $ \langle c_1, d_1, \rangle, \langle c_2, d_2, \rangle, \ldots, \langle c_m, d_m \rangle $ to the array $ a_1, a_2, \ldots, a_n $ transforms it into the array $ b_1, b_2, \ldots, b_n $ ?

## 样例 #1

### 输入

```
7
3
1 2 1
1 3 2
4
1 3 1 2
4
1 2 3 5
2 1 3 5
2
2 3
5
7 6 1 10 10
3 6 1 11 11
3
4 3 11
4
3 1 7 8
2 2 7 10
5
10 3 2 2 1
5
5 7 1 7 9
4 10 1 2 9
8
1 1 9 8 7 2 10 4
4
1000000000 203 203 203
203 1000000000 203 1000000000
2
203 1000000000
1
1
1
5
1 3 4 5 1```

### 输出

```
YES
NO
NO
NO
YES
NO
YES```

# AI分析结果

### 题目内容重写
# Sofia and the Lost Operations

## 题目描述

Sofia 有一个包含 $n$ 个整数的数组 $a_1, a_2, \ldots, a_n$。有一天她对这个数组感到无聊，于是决定依次对其应用 $m$ 次修改操作。

每次修改操作由一对数字 $\langle c_j, d_j \rangle$ 描述，表示将数组中索引为 $c_j$ 的元素赋值为 $d_j$，即执行赋值操作 $a_{c_j} = d_j$。在依次应用所有修改操作后，Sofia 丢弃了最终的数组。

最近，你发现了一个包含 $n$ 个整数的数组 $b_1, b_2, \ldots, b_n$。你想知道这个数组是否是 Sofia 的数组。你知道原始数组的值，以及修改操作中的值 $d_1, d_2, \ldots, d_m$。然而，索引 $c_1, c_2, \ldots, c_m$ 丢失了。

是否存在一个序列 $c_1, c_2, \ldots, c_m$，使得依次应用修改操作 $\langle c_1, d_1 \rangle, \langle c_2, d_2 \rangle, \ldots, \langle c_m, d_m \rangle$ 将数组 $a_1, a_2, \ldots, a_n$ 转换为数组 $b_1, b_2, \ldots, b_n$？

## 样例 #1

### 输入

```
7
3
1 2 1
1 3 2
4
1 3 1 2
4
1 2 3 5
2 1 3 5
2
2 3
5
7 6 1 10 10
3 6 1 11 11
3
4 3 11
4
3 1 7 8
2 2 7 10
5
10 3 2 2 1
5
5 7 1 7 9
4 10 1 2 9
8
1 1 9 8 7 2 10 4
4
1000000000 203 203 203
203 1000000000 203 1000000000
2
203 1000000000
1
1
1
5
1 3 4 5 1```

### 输出

```
YES
NO
NO
NO
YES
NO
YES```

### 题解分析与结论

#### 综合分析
本题的核心在于判断是否存在一个操作序列，使得通过修改操作将数组 $a$ 转换为数组 $b$。所有题解的思路基本一致，主要分为以下几个步骤：
1. **统计需要修改的元素**：遍历数组 $a$ 和 $b$，统计 $a_i \neq b_i$ 的元素及其出现次数。
2. **统计可用的修改值**：统计 $d$ 数组中每个值的出现次数。
3. **判断是否满足条件**：检查 $d$ 数组中的值是否足够覆盖 $a$ 到 $b$ 的修改需求，并且最后一个操作的值必须在 $b$ 中出现。

#### 最优关键思路
1. **使用 `map` 进行统计**：由于数值范围较大，使用 `map` 来统计 $a$ 和 $b$ 的差异以及 $d$ 数组的值。
2. **最后一个操作的关键性**：最后一个操作的值必须在 $b$ 中出现，否则无法通过后续操作覆盖。

#### 推荐题解
1. **作者：toolong114514 (5星)**
   - **关键亮点**：代码清晰，逻辑严谨，使用 `map` 进行统计，且考虑了最后一个操作的关键性。
   - **核心代码**：
     ```cpp
     map<int,int> mp1,mp2,mp3;
     for(int i=1;i<=cnt;i++){
         mp1[t[i]]++;
         if(mp1[t[i]]>mp2[t[i]]){
             cout<<"NO\n";
             flag=false;
             break;
         }
     }
     for(int i=m;i>0;i--){
         if(!flag) break;
         if(mp1[d[i]]||mp3[d[i]]) sb=true;
         if((!mp1[d[i]]&&!sb)){
             cout<<"NO\n";
             flag=false;
             break;
         }
     }
     if(flag) cout<<"YES\n";
     ```

2. **作者：ArcNick (4星)**
   - **关键亮点**：思路清晰，代码简洁，使用 `map` 进行统计，且详细分析了可能的情况。
   - **核心代码**：
     ```cpp
     for (auto x : need) {
         int val = x.first;
         if (have[val] < x.second) {
             cout << "NO\n";
             return;
         }
     }
     bool flag = 0;
     for (int i = m; i >= 1; i--) if (have.count(d[i])) {
         if (!need.count(d[i]) && !flag && cnt[d[i]] == 0) {
             cout << "NO\n";
             return;
         }
         flag = 1;
         if (have[d[i]] < need[d[i]]) {
             cout << "NO\n";
             return;
         }
     }
     cout << "YES\n";
     ```

3. **作者：MuQYun (4星)**
   - **关键亮点**：思路清晰，代码简洁，使用 `map` 进行统计，且考虑了 $a$ 和 $b$ 相同的情况。
   - **核心代码**：
     ```cpp
     if (dif.empty()) {
         if (s1.count(d[m])) {
             puts("YES");
             return;
         }
         puts("NO");
         return;
     } else {
         for (auto item : mp1) {
             int x = item.first;
             int y = item.second;
             if (!mp2.count(x)) {
                 puts("NO");
                 return;
             } else {
                 if (mp2[x] < y) {
                     puts("NO");
                     return;
                 }
             }
         }
         puts("YES");
     }
     ```

### 拓展与推荐题目
1. **洛谷 P3383 【模板】线性筛素数**（题号：P3383）
   - **考察知识点**：线性筛法，素数判断。
2. **洛谷 P3374 【模板】树状数组 1**（题号：P3374）
   - **考察知识点**：树状数组，区间查询与单点修改。
3. **洛谷 P3368 【模板】树状数组 2**（题号：P3368）
   - **考察知识点**：树状数组，区间修改与单点查询。

### 个人心得总结
- **调试经历**：在使用 `unordered_map` 时，由于哈希冲突导致超时，改用 `map` 后问题解决。
- **顿悟感想**：最后一个操作的值必须在 $b$ 中出现，否则无法通过后续操作覆盖，这一点的理解对解题至关重要。

---
处理用时：54.06秒