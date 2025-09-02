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



### 综合分析
本题解需判断能否用四个各含6字符的块拼出给定单词。各题解主要采用DFS回溯或排列枚举的思路，核心在于确保每个字符来自不同块且顺序正确。高效的解法通过预处理存在性数组，结合排列枚举将时间复杂度降至O(k!)，显著优化性能。

### 精选题解
#### 1. junxis（5星）
**关键亮点**：  
- 预处理块的存在性数组，快速查询。  
- 枚举字符对应块的全排列，确保每个字符来源合法。  
- 时间复杂度O(k!)，极为高效，适合大数据量。  
**核心代码**：  
```cpp
bool exist[5][30]; // exist[i][j]表示块i是否含字符j
void dfs(int dep) {
    if(dep > len) {
        if(checkit()) flag = 1;
        return;
    }
    for(int i=1; i<=4; i++) {
        if(!used[i] && exist[i][word[dep-1]-'A'+1]) {
            used[i] = 1;
            tmp[dep] = i;
            dfs(dep+1);
            used[i] = 0;
        }
    }
}
```

#### 2. CANTORSORT（5星）
**关键亮点**：  
- 简洁回溯，逐字符匹配并标记块使用状态。  
- 及时剪枝，找到可行解立即返回。  
- 代码清晰易读，时间复杂度O(k!)。  
**核心代码**：  
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
                break;
            }
        }
    }
}
```

#### 3. oddy（4星）
**关键亮点**：  
- 构造字符串时优化尾部添加操作，用`push_back`提升效率。  
- 明确递归终止条件，结构清晰。  
**核心代码**：  
```cpp
bool dfs(int k) {
    if(k > t.size()) return str == t;
    for(int i=1; i<=4; i++) if(!vis[i]) {
        for(char ch : s[i]) {
            str.push_back(ch);
            vis[i] = true;
            if(dfs(k+1)) return true;
            str.pop_back();
            vis[i] = false;
        }
    }
    return false;
}
```

### 最优关键思路
**预处理存在性+排列枚举**：  
1. **预处理**每个块包含的字符，生成存在性数组。  
2. **排列枚举**字符与块的对应关系，确保每个字符来自不同块。  
3. **剪枝优化**：及时回溯，避免无效搜索。

### 拓展练习
1. **全排列问题**（P1706）：练习基础排列生成。  
2. **八皇后问题**（P1219）：经典回溯法应用。  
3. **选数问题**（P1036）：组合选择与质数判断结合。  

### 心得摘录
- **oddy**提到使用`str.push_back(ch)`而非`+=`，因前者时间复杂度更低。  
- **junxis**通过预处理存在性数组，将字符查询降至O(1)，显著优化效率。  
- **CANTORSORT**在找到解后立即返回，减少不必要的递归，体现高效剪枝思想。

---
处理用时：310.99秒