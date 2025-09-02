# 题目信息

# [ICPC 2020 Shanghai R] Gitignore

## 题目描述

Your git project (you don't need to be familiar with git to solve this problem) has some files that should be ignored from synchronizing. You need to calculate the minimum number of lines needed for gitignore.

Formally, your project is a folder. A folder can have files and sub folders. There are no empty folders (i.e. folders without any files or sub folders inside). Initially, the git software will synchronize all the files in your project. However, you can specify some files and folders in the settings (which is called gitignore) to exclude them from synchronizing. For each line in gitignore, you can specify either a file or all the files in a folder. You can $\textbf{not}$  ignore the whole project folder (i.e. an empty line in gitignore).

You are given paths for all the files in the project and whether they should be ignored or shouldn't. Your task is to calculate the minimum number of lines for gitignore.

## 说明/提示

In the first sample test case, the corresponding gitignore file contains $2$ lines: a folder line ``data/`` and a file name ``model``.

In the second sample test case, the corresponding gitignore file contains $3$ file lines: ``data/train``, ``data/test`` and ``model``.

## 样例 #1

### 输入

```
2
3 0
data/train
data/test
model
3 1
data/train
data/test
model
data/sample```

### 输出

```
2
3```

# AI分析结果



### 算法分类
贪心

### 题解分析与结论
题目核心是**贪心策略**：优先通过忽略高层级文件夹来覆盖更多子文件，减少规则行数。所有题解均使用路径层级分解与哈希映射技术，通过预处理不可忽略文件的父路径标记，再逐层判断可忽略的最优路径层级。

---

### 评分较高的题解

#### 1. 作者：BetterGodPig（4星）
**关键亮点**：
- 使用双 `map` 结构高效标记保留路径和已处理路径
- 逐字符解析路径，避免字符串分割函数开销
- 清晰的层级判断逻辑，遇到可忽略父文件夹立即跳出循环

**核心代码思想**：
```cpp
// 预处理不可忽略文件的父路径
for (不可忽略文件路径 str) {
    string tmp = "";
    for (每个字符 c in str) {
        if (c == '/') mp[tmp] = 1; // 标记父路径必须保留
        tmp += c;
    }
}

// 处理可忽略文件
for (可忽略文件路径 s) {
    string tmp = "";
    for (每个字符 c in s) {
        if (c == '/') {
            if (mp[tmp]) continue; // 父路径必须保留
            if (!vis[tmp]) {        // 发现可忽略的最优层级
                vis[tmp] = 1;
                ans++;
                break;
            }
        }
        tmp += c;
    }
}
```

#### 2. 作者：DFM_O（4星）
**关键亮点**：
- 使用结构体存储输入路径，增强可扩展性
- 清晰的布尔标记系统（pd/pd2）处理层级判断
- 完整处理路径结尾无'/'的情况

**个人心得**：
> "路径分割时特别要注意处理最后一个字符不是'/'的情况，需要手动添加层级标记"

---

### 最优思路总结
**核心技巧**：
1. **路径逆向标记**：预处理不可忽略文件的所有父路径，确保后续层级判断时能快速排除无法整体忽略的文件夹
2. **贪心层级截断**：从文件路径的根目录开始逐层检查，找到第一个可忽略的父文件夹后立即终止更深的层级检查
3. **双哈希去重**：使用 `mp` 标记保留路径，`vis` 记录已添加的忽略规则，避免重复计数

---

### 拓展练习
1. [P1784 后缀表达式](https://www.luogu.com.cn/problem/P1784) - 贪心策略与层级处理
2. [P3958 奶酪](https://www.luogu.com.cn/problem/P3958) - 三维空间路径覆盖问题
3. [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082) - 贪心区间合并的变式应用

---
处理用时：62.41秒