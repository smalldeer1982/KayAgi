# 题目信息

# Auto Complete

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041I/2221d29ba6460d0398718df90accbcfb85d92103.png)You are designing a snazzy new text editor, and you want to add a nifty auto-complete feature to help users save time. Here is how it will work: if a user types "App", your editor will magically suggest the word "Application"! Even better, users can personalize the words that auto-complete in your editor.

Your editor will support 4 kinds of operations (Let's say the current text in your editor is $ t $ ):

1. Add an auto complete pattern $ p_i $ .
2. Delete an auto complete pattern $ p_i $ .
3. Append a string $ s $ to the end of $ t $ .
4. Delete $ c $ characters from the end of $ t $ . Note that if $ c $ is larger then the length of $ t $ , delete all the characters from $ t $ .

After each action, your editor should suggest an auto-complete candidate $ i $ that matches the following criteria:

1. The string $ p_i $ has a prefix equal to $ t $ .
2. If there are multiple $ p_i $ , pick the longest one.
3. If there are still multiple $ p_i $ , pick the one with the smallest lexicographic order.
4. If there are still multiple $ p_i $ , pick the one with the smallest ID.

 To simplify the question, for each action, print the suggested auto complete pattern ID. If there's no match, print -1.For example, let us say we have three candidates: "alice", "bob", and "charlie", with ID 1, 2, and 3. At first, there is nothing on the screen, so "charlie" (3) should be suggested because it is the longest. Then, let us say the user types "b". You should suggest "bob" (2) because it is the only one that starts with "b". Finally, let us say the user type "body". You should print -1 because there is no matched pattern.

## 样例 #1

### 输入

```
6
add 1 pattern1_alice
add 2 pattern2_bob
add 3 pattern3_charlie
append pattern
append 2_bobabc
backspace 3```

### 输出

```
1
1
3
3
-1
2```

## 样例 #2

### 输入

```
6
append pattern
add 1 pattern1_alice____
add 2 pattern2_bob______
add 3 pattern3_charlie__
delete 1
delete 2```

### 输出

```
-1
1
1
1
2
3```

# AI分析结果



**唯一算法分类**: 字典树（Trie）

---

### **综合分析与结论**
本题核心在于动态维护输入字符串的前缀匹配，并快速筛选出符合条件的最优模式。通过字典树（Trie）高效管理所有模式的前缀关系，结合动态指针跟踪当前输入状态，实现快速查询。

#### 核心算法流程
1. **字典树结构**：每个节点维护子节点映射（`map<char, Node*>`）和一个按条件排序的候选模式集合（`set`），排序条件依次为：长度最长、字典序最小、ID最小。
2. **动态指针管理**：
   - `append`操作：逐个字符移动指针到对应子节点。
   - `backspace`操作：回退指针到父节点。
3. **模式操作**：
   - `add`：插入模式到其路径上的所有节点集合中。
   - `delete`：从所有相关节点集合中移除模式。
4. **查询**：检查当前指针节点的集合，取首个有效模式。

#### 可视化设计思路
- **字典树可视化**：以树状结构展示节点关系，当前指针用高亮颜色标记。
- **操作动画**：
  - `append`：沿字符路径移动指针，动态扩展树结构。
  - `backspace`：指针回退，路径颜色渐隐。
  - `add/delete`：在对应节点上显示模式插入/删除的闪烁效果。
- **复古游戏化**：
  - **像素风格**：节点用8-bit方块表示，不同颜色区分候选模式集合。
  - **音效**：指针移动时播放“点击”音效，匹配成功时播放上扬音调。

---

### **题解清单 (≥4星)**
1. **沉石鱼惊旋 (5星)**  
   **亮点**：  
   - 使用字典树动态维护前缀匹配，通过父指针高效处理回退操作。  
   - 每个节点维护有序集合，直接取首元素完成最优筛选。  
   - 代码简洁，逻辑清晰，支持大规模输入。

---

### **代码实现核心逻辑**
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    map<char, Node*> ch;
    Node* fa;
    int depth;
    struct Data {
        int id, len;
        string s;
        bool operator<(const Data& o) const {
            if (len != o.len) return len > o.len;
            if (s != o.s) return s < o.s;
            return id < o.id;
        }
    };
    set<Data> cand;
    Node(Node* fa = nullptr) : fa(fa), depth(fa ? fa->depth + 1 : 0) {}
};

struct Pattern {
    string s;
    bool active = true;
};

vector<Pattern> pats; // 模式池
Node* root = new Node();
vector<Node*> nodes; // 所有节点，用于删除时回溯
Node* current = root;

void add(int id, const string& s) {
    Node* p = root;
    pats[id].active = true;
    for (char c : s) {
        if (!p->ch.count(c)) {
            p->ch[c] = new Node(p);
            nodes.push_back(p->ch[c]);
        }
        p = p->ch[c];
        Node::Data data{id, (int)s.size(), s};
        p->cand.insert(data);
    }
}

void del(int id) {
    pats[id].active = false;
    for (Node* p : nodes) {
        auto it = p->cand.find({id, (int)pats[id].s.size(), pats[id].s});
        if (it != p->cand.end()) p->cand.erase(it);
    }
}

int query() {
    if (current == nullptr) return -1;
    for (const auto& data : current->cand) {
        if (pats[data.id].active) return data.id;
    }
    return -1;
}

int main() {
    // 示例操作处理（略）
    return 0;
}
```

---

### **同类型题推荐**
1. **P2580 于是他错误的点名开始了**  
   **标签**：字典树、字符串匹配。
2. **P2922 [USACO08DEC]Secret Message G**  
   **标签**：字典树、前缀统计。
3. **P8306 【模板】字典树**  
   **标签**：字典树模板题。

---
处理用时：290.93秒