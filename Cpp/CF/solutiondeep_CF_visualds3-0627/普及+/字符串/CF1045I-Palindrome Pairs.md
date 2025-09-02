# 题目信息

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出

```
6
```

# AI分析结果



---

**算法分类**  
哈希表与位运算

---

### **题解思路与算法要点**
1. **核心思路**  
   每个字符串转化为一个26位的二进制数（mask），每一位表示对应字母出现次数的奇偶性。目标统计满足以下条件的字符串对：  
   - 两个mask异或结果为0（所有字符出现偶数次）  
   - 或异或结果仅有一位为1（仅一个字符出现奇数次）

2. **关键步骤**  
   - **哈希表统计**：维护一个哈希表，记录已处理的每个mask的出现次数。  
   - **枚举所有位**：对于当前处理的mask，检查哈希表中是否存在以下情况：  
     - 相同的mask（异或结果为0）  
     - 异或后仅有一位不同的mask（枚举所有26位，计算当前mask^1<<j并查询哈希表）  
   - **顺序处理**：逐个处理字符串，确保每个对仅统计一次（j < i时处理）。

3. **解决难点**  
   - **正确性**：必须枚举所有26位，无论当前mask的某位是否为0或1。若仅处理mask为1的位（如yijan的题解），会漏掉部分合法对。  
   - **高效性**：哈希表查询和插入操作均为O(1)，总时间复杂度为O(n·26)，适用于n≤1e5的数据规模。

---

### **题解评分（≥4星）**
1. **mrsrz的题解（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码简洁，正确枚举所有26位，使用`map`维护哈希表，逻辑清晰。  
   - **代码片段**：  
     ```cpp
     for (int j=0;j<26;++j) ans += b[a[i]^(1<<j)];
     ```

2. **lzyqwq的题解（⭐⭐⭐⭐）**  
   - **亮点**：明确分海明距离为0或1的情况，结合排序与二分优化查询。  
   - **代码片段**：  
     ```cpp
     for (auto i:S) ans += S[k] * S[k^(1<<j)];
     ```

3. **codwarm的题解（⭐⭐⭐⭐）**  
   - **亮点**：将问题拆分为“全偶数次”和“单奇数次”两类，逻辑直观。  
   - **代码片段**：  
     ```cpp
     for (int j=0;j<26;j++) ct[x^(1<<j)]++;
     ```

---

### **最优思路提炼**
1. **位运算压缩状态**：将字符奇偶性压缩为26位二进制数，便于快速计算。  
2. **哈希表动态统计**：逐个处理字符串，利用哈希表记录历史状态。  
3. **全位枚举覆盖**：枚举所有26位，确保所有可能的异或结果被统计。

---

### **同类型题与算法套路**
- **相似题目**：  
  - 洛谷P1464（位运算优化）  
  - LeetCode 318. Maximum Product of Word Lengths（位掩码+哈希）  
  - 洛谷P2580（哈希表统计字符串出现次数）

---

### **推荐洛谷题目**
1. **P1464**（位运算优化枚举）  
2. **P2580**（哈希表快速查询）  
3. **P3498**（回文相关，需统计字符奇偶性）

---

### **个人心得摘录**
> “必须枚举所有26位，即使当前位为0，否则会漏掉合法对。”  
> —— 调试发现仅处理mask为1的位导致样例2错误，修正后AC。

---

### **可视化与算法演示**
1. **算法流程动画**  
   - **步骤分解**：  
     1. 字符串转换为二进制mask（颜色标记字符奇偶性）。  
     2. 当前mask与哈希表比对（高亮匹配项）。  
     3. 枚举所有26位，计算异或值并查询哈希表。  
   - **交互控制**：支持暂停/步进，查看当前mask和哈希表状态。

2. **复古像素风格设计**  
   - **颜色方案**：8位色调，绿色表示偶数次，红色表示奇数次。  
   - **音效**：  
     - 字符处理：8-bit按键音。  
     - 匹配成功：短促上扬音效。  
   - **Canvas绘制**：每个mask以像素块显示，异或操作时闪烁对应位。

3. **自动演示模式**  
   - **AI自动运行**：按顺序处理字符串，展示mask生成、哈希表更新及统计过程。  
   - **积分系统**：每统计到一对得10分，连续正确匹配触发连击特效。

---

### **代码实现（核心逻辑）**
```cpp
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> hash;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (char c : s) mask ^= (1 << (c - 'a'));
        
        // 统计相同mask和仅一位不同的mask
        ans += hash[mask];
        for (int j = 0; j < 26; j++) 
            ans += hash[mask ^ (1 << j)];
        
        hash[mask]++;
    }
    cout << ans << endl;
}
```

---
处理用时：324.58秒