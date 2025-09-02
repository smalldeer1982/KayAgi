# 题目信息

# [USACO22FEB] Blocks B

## 题目描述

为了提高词汇量，母牛贝西得到了一套四块木块，其中每块都是一个立方体，六面各写着一个字母。她正在通过将木块排成一排使得木块顶部的字母拼出单词来学习拼写。

给定 Bessie 的四个木块上的字母，以及她想拼写的单词列表，请确定列表中哪些单词可被她使用木块成功拼写。

## 样例 #1

### 输入

```
6
MOOOOO
OOOOOO
ABCDEF
UVWXYZ
COW
MOO
ZOO
MOVE
CODE
FARM```

### 输出

```
YES
NO
YES
YES
NO
NO```

# AI分析结果



### 题解综合分析与结论
本题需判断能否用四个方块（每个选一字母）按顺序组成目标单词。各题解均采用回溯法，核心思路是为每个字符选择未被使用的方块。其中，CANTORSORT的解法高效且正确，通过DFS及时剪枝，预处理存在性检查，代码简洁。

---

### 精选题解列表

#### 1. 作者：CANTORSORT ★★★★★
**关键亮点**  
- 预处理每个方块的字符存在性，DFS中及时剪枝。
- 代码简洁，每层递归处理一个字符，仅需检查当前方块是否存在该字符。
- 使用`vis`数组确保每个方块只用一次，`break`跳过同一方块的重复检查。

**核心代码**  
```cpp
void dfs(int now) {
    if(now >= len) { flag = 1; return; }
    for(int i=1; i<=4; i++) {
        if(vis[i]) continue;
        for(int j=0; j<6; j++) {
            if(s[i][j] == word[now]) {
                vis[i] = 1;
                dfs(now+1);
                vis[i] = 0;
                break; // 同一方块找到字符后无需继续检查其他面
            }
        }
    }
}
```

#### 2. 作者：junxis ★★★★☆
**关键亮点**  
- 预处理`exist`数组快速判断字符是否存在于方块。
- DFS枚举每个字符对应的方块编号，最后统一检查可行性。
- 代码结构清晰，分离DFS与检查逻辑。

**核心代码**  
```cpp
void dfs(int dep) {
    if(flag) return;
    if(dep > len) {
        if(checkit()) flag = 1;
        return;
    }
    for(int i=1; i<=4; i++) {
        if(!used[i]) {
            used[i] = 1;
            tmp[dep] = i;
            dfs(dep+1);
            used[i] = 0;
        }
    }
}
```

#### 3. 作者：oddy ★★★★☆
**关键亮点**  
- 递归构建字符串，通过`push_back`和`pop_back`动态维护。
- 及时返回可行解，减少冗余递归。

**核心代码**  
```cpp
bool dfs(int k) {
    if(k > t.size()) return str == t;
    for(int i=1; i<=4; i++) if(!vis[i]) 
        for(auto ch : s[i]) {
            str.push_back(ch);
            vis[i] = true;
            if(dfs(k+1)) return true;
            str.pop_back();
            vis[i] = false;
        }
    return false;
}
```

---

### 最优思路总结
**关键技巧**  
- **预处理存在性**：提前记录每个方块的字符，避免DFS中重复查找。
- **回溯剪枝**：一旦找到可行解立即返回，减少不必要的搜索。
- **顺序无关排列**：按字符顺序选择方块，隐含排列可能性，无需显式生成全排列。

**拓展建议**  
- 类似题目：全排列（P1706）、组合选择（P1036）、存在性剪枝（P1019）。
- 可练习的洛谷题目：P1036、P1706、P1219（回溯经典）。

---
处理用时：289.20秒