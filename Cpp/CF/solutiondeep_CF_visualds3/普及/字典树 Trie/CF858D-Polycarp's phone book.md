# 题目信息

# Polycarp's phone book

## 题目描述

There are $ n $ phone numbers in Polycarp's contacts on his phone. Each number is a 9-digit integer, starting with a digit different from $ 0 $ . All the numbers are distinct.

There is the latest version of Berdroid OS installed on Polycarp's phone. If some number is entered, is shows up all the numbers in the contacts for which there is a substring equal to the entered sequence of digits. For example, is there are three phone numbers in Polycarp's contacts: $ 123456789 $ , $ 100000000 $ and $ 100123456 $ , then:

- if he enters $ 00 $ two numbers will show up: $ 100000000 $ and $ 100123456 $ ,
- if he enters $ 123 $ two numbers will show up $ 123456789 $ and $ 100123456 $ ,
- if he enters $ 01 $ there will be only one number $ 100123456 $ .

For each of the phone numbers in Polycarp's contacts, find the minimum in length sequence of digits such that if Polycarp enters this sequence, Berdroid shows this only phone number.

## 样例 #1

### 输入

```
3
123456789
100000000
100123456
```

### 输出

```
9
000
01
```

## 样例 #2

### 输入

```
4
123456789
193456789
134567819
934567891
```

### 输出

```
2
193
81
91
```

# AI分析结果


### 💡 Kay的C++算法解析：Polycarp's phone book 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`字符串处理` + `高效查询技巧`（枚举优化）  
🗣️ **初步分析**：  
> 想象你有一本电话簿📖，每页写着一个9位号码。现在需要为每页贴一个"专属标签"——最短的数字序列，输入时**只显示该页号码**。核心解法是通过**枚举所有子串+高效计数**实现：  
> - **核心思路**：统计所有号码的所有子串出现频次。对每个号码，找到其子串中出现频次为1且最短的那个（即唯一标识）。  
> - **难点对比**：  
>   - *字典树法*：空间换时间（需处理子串去重），适合追求效率  
>   - *哈希映射法*：用`map/set`计数，逻辑简单但查询稍慢  
> - **可视化设计**：像素化电话簿界面（复古翻页动画），高亮当前处理的子串。当发现唯一子串时，播放"叮！"音效+闪光特效，类似解谜游戏找到钥匙🗝️。

---

#### 2. 精选优质题解参考
**题解一（字典树法 by 404Not_Found）**  
* **点评**：思路创新性极强，通过**动态删除自身子串**排除干扰（类似"暂时隐身"），直接定位唯一标识。代码中`trie[to].val--`是关键亮点，但需注意内存消耗（开214MB）。实践价值在于展示字典树灵活运用，但竞赛中需权衡空间限制。  

**题解二（哈希映射法 by Bai_R_X）**  
* **点评**：逻辑直白高效，用`set`避免同号码子串重复计数（如"000"多次出现只算1次）。亮点在`vector<string> sons`存储子串列表，便于后续快速检索。代码可读性好，但`#define int long long`稍显冗余。  

**题解三（哈希映射法 by kimi0705）**  
* **点评**：优化了检索顺序——**按子串长度从小到大枚举**，找到首个`mp[子串]==1`即停止。亮点在`Printed`标志位避免无效循环，显著提升效率。边界处理严谨，适合竞赛直接使用。

---

#### 3. 核心难点辨析与解题策略
1. **子串去重处理**  
   * **分析**：同一号码中重复子串（如"111"出现多次）只应计1次，否则导致计数偏差。题解2/3用`set`过滤，题解1需额外处理。  
   * 💡 **学习笔记**：`set`是天然去重器，优先考虑！  

2. **唯一标识检索效率**  
   * **分析**：暴力枚举所有子串（45个/号码）效率低。优化点：按长度从短到长枚举，找到即退出（题解3）或预处理子串列表（题解2）。  
   * 💡 **学习笔记**：最短解一定在较小子串中，优先搜索！  

3. **数据结构选择**  
   * **分析**：  
     - `map`：代码简单，但`O(log n)`查询耗时  
     - `Trie`：查询`O(1)`但内存消耗大  
   * 💡 **学习笔记**：数据规模小时选`map`，极限优化用`Trie`。  

### ✨ 解题技巧总结
- **去重优先**：同一字符串子串用`set`过滤  
- **剪枝策略**：按子串长度升序枚举，及早终止  
- **空间权衡**：`Trie`适合时间敏感场景，`map`通用性更强  

---

#### 4. C++核心代码实现赏析
**通用核心实现（哈希映射法）**  
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<string> nums(n);
    map<string, int> freq;

    // 统计所有子串频次（去重）
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        set<string> unique_subs;
        for (int len = 1; len <= 9; len++) 
            for (int j = 0; j <= 9 - len; j++) 
                unique_subs.insert(nums[i].substr(j, len));
        
        for (auto& sub : unique_subs) freq[sub]++;
    }

    // 为每个号码找最短唯一子串
    for (auto& num : nums) {
        string ans = num; // 默认用完整号码
        for (int len = 1; len <= 9; len++) {
            for (int j = 0; j <= 9 - len; j++) {
                string sub = num.substr(j, len);
                if (freq[sub] == 1 && sub.size() < ans.size()) 
                    ans = sub;
            }
        }
        cout << ans << endl;
    }
}
```
**代码解读概要**：  
1. 先用`set`收集每个号码的**去重子串**，存入`freq`映射  
2. 二次遍历时，**从小到大**检查子串，首个`freq[sub]==1`即最优解  

**题解一片段（字典树删除操作）**  
```cpp
void del(char *s) {
    int now = 0;
    for (int i = 0; s[i]; i++) {
        int id = s[i] - '0';
        int to = trie[now].next[id];
        trie[to].val--; // 关键！临时删除自身影响
        now = to;
    }
}
```
**学习笔记**：`trie[to].val--`使当前号码子串"隐身"，从而直接检测外部唯一性。  

**题解三片段（早期终止优化）**  
```cpp
for (int Len = 1; Len <= 9; Len++) {
    for (int L = 0; L + Len - 1 < 9; L++) {
        string S = s[i].substr(L, Len);
        if (C[S] == 1) { 
            cout << S << '\n';
            Printed = true; // 找到即退出
            break;
        }
    }
    if (Printed) break;
}
```
**学习笔记**：`Printed`标志实现双层循环跳出，避免无效长串检查。

---

#### 5. 算法可视化：像素动画演示  
**主题**：复古电话簿解谜游戏（FC像素风）  
**核心演示**：  
![](https://via.placeholder.com/400x200?text=Pixel+Phonebook+Interface)  
1. **初始化**：9x9网格显示所有号码，控制面板含`播放/步进`按钮  
2. **统计阶段**：  
   - 高亮当前号码（黄色边框），扫描子串（蓝色滑动框）  
   - 子串插入`map`时播放"滴"音效，计数+1显示在右侧面板  
3. **检索阶段**：  
   - 从长度1子串开始扫描（绿色框），若`freq=1`则闪烁红光+胜利音效🎉  
   - 字典树法额外展示：删除操作时节点变灰，查询时路径高亮  
4. **游戏化元素**：  
   - 每找到一个最短子串得1⭐，集齐n⭐通关  
   - 错误尝试（长串检查）触发"嗡嗡"警示音  

---

#### 6. 拓展练习  
1. **POJ2001** - 最短唯一前缀（字典树经典应用）  
   🗣️ *推荐理由*：巩固前缀统计思想，强化`Trie`实战能力  
2. **洛谷P1481** - 魔族密码（最长包含链）  
   🗣️ *推荐理由*：进阶训练子串关系的动态规划处理  
3. **Leetcode 1044** - 最长重复子串（二分+哈希）  
   🗣️ *推荐理由*：拓展更高效的字串处理方法  

---

#### 7. 学习心得  
> **题解1作者经验**："字典树以空间换时间，但需警惕内存限制"  
> **Kay点评**：深刻提醒我们算法选择需考虑**平台约束**。竞赛中需预判数据规模，`map`通常是更安全的起手式。  

---  
算法世界如同探险，每一次优化都是打开新地图的钥匙🗺️！保持思考，继续前进吧！🚀

---
处理用时：187.06秒