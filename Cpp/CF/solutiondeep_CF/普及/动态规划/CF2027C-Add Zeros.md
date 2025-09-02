# 题目信息

# Add Zeros

## 题目描述

You're given an array $ a $ initially containing $ n $ integers. In one operation, you must do the following:

- Choose a position $ i $ such that $ 1 < i \le |a| $ and $ a_i = |a| + 1 - i $ , where $ |a| $ is the current size of the array.
- Append $ i - 1 $ zeros onto the end of $ a $ .

After performing this operation as many times as you want, what is the maximum possible length of the array $ a $ ?

## 说明/提示

In the first test case, we can first choose $ i = 4 $ , since $ a_4 = 5 + 1 - 4 = 2 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0] $ . We can then choose $ i = 3 $ since $ a_3 = 8 + 1 - 3 = 6 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0, 0, 0] $ , which has a length of $ 10 $ . It can be shown that no sequence of operations will make the final array longer.

In the second test case, we can choose $ i=2 $ , then $ i=3 $ , then $ i=4 $ . The final array will be $ [5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0] $ , with a length of $ 11 $ .

## 样例 #1

### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1```

### 输出

```
10
11
10
1```

# AI分析结果

### 题目内容中文重写

#### 题目描述

给定一个初始包含 $n$ 个整数的数组 $a$。在一次操作中，你必须执行以下步骤：

- 选择一个位置 $i$，满足 $1 < i \le |a|$ 且 $a_i = |a| + 1 - i$，其中 $|a|$ 是数组的当前长度。
- 在数组 $a$ 的末尾添加 $i - 1$ 个零。

在任意次操作后，数组 $a$ 的最大可能长度是多少？

#### 说明/提示

在第一个测试用例中，我们可以首先选择 $i = 4$，因为 $a_4 = 5 + 1 - 4 = 2$。操作后，数组变为 $[2, 4, 6, 2, 5, 0, 0, 0]$。然后我们可以选择 $i = 3$，因为 $a_3 = 8 + 1 - 3 = 6$。操作后，数组变为 $[2, 4, 6, 2, 5, 0, 0, 0, 0, 0]$，长度为 $10$。可以证明，没有其他操作序列能使最终数组更长。

在第二个测试用例中，我们可以依次选择 $i=2$、$i=3$、$i=4$。最终数组为 $[5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0]$，长度为 $11$。

#### 样例 #1

##### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1
```

##### 输出

```
10
11
10
1
```

---

### 题解分析与结论

#### 题解综合分析与评分

1. **Mirage_Insane**（4星）
   - **关键亮点**：使用动态规划（DP）和记忆化搜索，通过 `map` 存储状态转移，优化了时间复杂度。
   - **代码实现**：通过 `dfs` 函数进行记忆化搜索，状态转移时更新最大长度。
   - **优化程度**：利用 `map` 进行状态存储，避免了重复计算，适合大数据范围。

2. **LEE114514**（4星）
   - **关键亮点**：通过排序和集合维护，线性扫描数组，更新最大长度。
   - **代码实现**：使用 `set` 维护可到达的长度，通过排序后的数组进行线性扫描。
   - **优化程度**：排序和集合操作的时间复杂度较低，适合中等规模数据。

3. **Him_shu**（4星）
   - **关键亮点**：通过结构体存储数组元素的可贡献长度和贡献值，排序后线性扫描更新最大长度。
   - **代码实现**：使用 `set` 维护可到达的长度，通过排序后的数组进行线性扫描。
   - **优化程度**：结构体排序和集合操作的时间复杂度较低，适合中等规模数据。

#### 最优关键思路或技巧

- **动态规划与记忆化搜索**：通过 `map` 存储状态转移，避免重复计算，适合大数据范围。
- **排序与集合维护**：通过排序和集合操作，线性扫描数组，更新最大长度，适合中等规模数据。
- **结构体存储与排序**：通过结构体存储数组元素的可贡献长度和贡献值，排序后线性扫描更新最大长度。

#### 可拓展之处

- **类似算法套路**：动态规划、记忆化搜索、排序与集合维护等算法套路可以应用于其他类似问题，如最大子数组和、最长递增子序列等。
- **同类型题目**：可以考虑类似的操作序列问题，如通过特定条件进行数组扩展或修改。

#### 推荐洛谷题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划经典问题。
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 动态规划与排序结合的问题。
3. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216) - 动态规划与状态转移问题。

#### 个人心得摘录

- **Mirage_Insane**：利用 `map` 进行状态存储，避免了重复计算，适合大数据范围。
- **Him_shu**：只因开小了，超时了好多发。提醒我们在处理大数据时要注意数组大小和内存限制。

---

### 所选高分题解

#### 1. Mirage_Insane（4星）

**关键亮点**：使用动态规划（DP）和记忆化搜索，通过 `map` 存储状态转移，优化了时间复杂度。

**代码实现**：
```cpp
long long dfs(long long now) {
    if(dp[now]) return dp[now];
    long long ans = now;
    for(int i : g[now]) ans = max(ans, dfs(now + i));
    return dp[now] = ans;
}
```
**核心思想**：通过 `dfs` 函数进行记忆化搜索，状态转移时更新最大长度。

#### 2. LEE114514（4星）

**关键亮点**：通过排序和集合维护，线性扫描数组，更新最大长度。

**代码实现**：
```cpp
set<int> st;
for(int i=1;i<=n;++i) if(st.count(a[i].first)) st.emplace(a[i].first+a[i].second-1);
cout<<*st.rbegin()<<'\n';
```
**核心思想**：使用 `set` 维护可到达的长度，通过排序后的数组进行线性扫描。

#### 3. Him_shu（4星）

**关键亮点**：通过结构体存储数组元素的可贡献长度和贡献值，排序后线性扫描更新最大长度。

**代码实现**：
```cpp
for(int i=1;i<=n;i++){
    if(ss.find(a[i].av)==ss.end()) continue;
    ans=max(ans,a[i].av+a[i].ad);
    ss.insert(a[i].av+a[i].ad);
}
```
**核心思想**：使用 `set` 维护可到达的长度，通过排序后的数组进行线性扫描。

---
处理用时：47.29秒