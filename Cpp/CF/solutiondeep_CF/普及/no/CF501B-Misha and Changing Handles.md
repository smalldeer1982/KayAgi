# 题目信息

# Misha and Changing Handles

## 题目描述

Misha hacked the Codeforces site. Then he decided to let all the users change their handles. A user can now change his handle any number of times. But each new handle must not be equal to any handle that is already used or that was used at some point.

Misha has a list of handle change requests. After completing the requests he wants to understand the relation between the original and the new handles of the users. Help him to do that.

## 样例 #1

### 输入

```
5
Misha ILoveCodeforces
Vasya Petrov
Petrov VasyaPetrov123
ILoveCodeforces MikeMirzayanov
Petya Ivanov
```

### 输出

```
3
Petya Ivanov
Misha MikeMirzayanov
Vasya VasyaPetrov123
```

# AI分析结果



**题目内容中文重写**  
（题目已为中文，无需重写）

**算法分类**  
哈希表

---

### 题解综合分析  
本题需维护用户多次改名的链式关系，最终输出每个用户的初始名和当前名。核心思路是通过高效的数据结构记录新旧名字的映射关系，常见解法包括队列、并查集和哈希表。哈希表法通过直接映射新旧名字，时间复杂度最优，代码最简洁。

---

### 精选题解  

#### 1. 作者：X2H_tato（⭐⭐⭐⭐⭐）  
**关键思路**  
- 使用 `map<string, string>` 维护每个新名字到初始名的映射。  
- 若旧名存在，将新名映射到旧名的初始名，并删除旧名记录。  
**代码亮点**  
```cpp
map<string, string> mp;
// 处理改名请求
if (mp.find(str1) == mp.end()) {
    mp[str2] = str1; // 新名字映射到初始名
} else {
    mp[str2] = mp[str1]; // 继承旧名的初始名
    mp.erase(str1); // 删除旧名记录
}
```

#### 2. 作者：AveMarina（⭐⭐⭐⭐）  
**关键思路**  
- 用 `map` 模拟链表，记录每个名字的下一个节点。  
- 最终遍历链表找到初始名和当前名。  
**代码亮点**  
```cpp
map<string, string> mp;
vector<string> vec; // 存储所有初始名
// 处理改名请求
if (mp[a] == "") vec.push_back(a);
mp[a] = b; // 更新链表
mp[b] = "114514"; // 标记链尾
```

#### 3. 作者：wuyixiang（⭐⭐⭐⭐）  
**关键思路**  
- 双 `map` 分别记录名字链和当前有效名。  
- 倒序查找初始名，避免重复处理。  
**代码亮点**  
```cpp
map<string, string> mp;
map<string, int> mp2; // 记录当前有效名
// 输出时反向查找初始名
string t = kk->first;
while (mp[t] != "") t = mp[t];
```

---

### 最优技巧总结  
**核心技巧**：使用哈希表维护新旧名字的链式映射，确保每个新名直接指向初始名。删除中间旧名避免冗余查询，达到 O(n) 时间复杂度。  

**同类型拓展**  
- 链式关系维护（如员工上下级、家谱）  
- 并查集与哈希表的替代性应用  

**推荐题目**  
1. [P2814 家谱](https://www.luogu.com.cn/problem/P2814)  
2. [CF455A Boredom](https://codeforces.com/problemset/problem/455/A)（哈希表优化DP）  
3. [P3405 Cities and States](https://www.luogu.com.cn/problem/P3405)（哈希统计特殊对）  

---

### 题解个人心得摘录  
- **X2H_tato**：意识到中间名无需保留，直接映射新名到初始名可简化查询。  
- **rainbow_cat**：并查集合并后需倒序处理才能获取最终名字，易错点在于根节点映射。  
- **AveMarina**：模拟链表时需标记链尾，防止循环遍历。

---
处理用时：106.18秒