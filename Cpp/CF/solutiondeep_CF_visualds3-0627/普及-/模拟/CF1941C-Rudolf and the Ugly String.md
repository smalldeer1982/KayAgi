# 题目信息

# Rudolf and the Ugly String

## 题目描述

Rudolf has a string $ s $ of length $ n $ . Rudolf considers the string $ s $ to be ugly if it contains the substring $ ^\dagger $ "pie" or the substring "map", otherwise the string $ s $ will be considered beautiful.

For example, "ppiee", "mmap", "dfpiefghmap" are ugly strings, while "mathp", "ppiiee" are beautiful strings.

Rudolf wants to shorten the string $ s $ by removing some characters to make it beautiful.

The main character doesn't like to strain, so he asks you to make the string beautiful by removing the minimum number of characters. He can remove characters from any positions in the string (not just from the beginning or end of the string).

 $ ^\dagger $ String $ a $ is a substring of $ b $ if there exists a consecutive segment of characters in string $ b $ equal to $ a $ .

## 说明/提示

In the first test case, for example, you can delete the $ 4 $ th and $ 9 $ th characters to make the string beautiful.

In the second test case, the string is already beautiful.

## 样例 #1

### 输入

```
6
9
mmapnapie
9
azabazapi
8
mappppie
18
mapmapmapmapmapmap
1
p
11
pppiepieeee```

### 输出

```
2
0
2
6
0
2```

# AI分析结果



### 算法分类
**贪心算法**

---

### 综合分析与结论
所有题解均采用**贪心策略**，通过遍历字符串检测子串 `map` 和 `pie`，并跳过部分字符避免重复计数。核心难点在于处理重叠子串 `mapie`，需特判以避免重复删除。最优解法需满足：
1. **贪心跳过**：发现子串后跳过足够字符（如 `i += 3`）。
2. **特判 `mapie`**：检测到五字符 `mapie` 时，视为一次删除而非两次。

**可视化设计思路**：
- **动画流程**：以像素风格逐字符高亮扫描，检测到 `map`/`pie` 时闪烁标记并播放音效，`mapie` 用不同颜色高亮。
- **交互设计**：支持步进控制观察跳转逻辑，显示当前删除次数。复古音效配合关键操作（如发现子串时短促“哔”声，特判时上扬音效）。

---

### 题解清单（≥4星）
1. **CJKZS（5星）**  
   - **亮点**：明确处理 `mapie` 特例，代码逻辑清晰，通过优先检测五字符避免重复计数。
   - **关键代码**：
     ```cpp
     if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p'&&s[i+3]=='i'&&s[i+4]=='e'){
         ans++; i+=5; // 特判 mapie 并跳过
     }
     ```

2. **yhylivedream（4星）**  
   - **亮点**：简洁处理 `mapie`，优先五字符检测，逻辑与 CJKZS 类似但代码更紧凑。
   - **代码片段**：
     ```cpp
     if(i+4<=n && s.substr(i,5)=="mapie") cnt++, i+=4;
     ```

3. **Programming_Konjac（4星）**  
   - **亮点**：通过字符串填充避免边界检查，明确删除中间字符策略。
   - **核心思想**：填充字符 `j` 简化边界处理，优先检测 `mapie`。

---

### 核心代码实现
**CJKZS 的完整代码**（处理特例）：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        int n; string s;
        cin >> n >> s;
        int ans = 0;
        for(int i=0; i<s.size(); ){
            if(i+4 < s.size() && s.substr(i,5)=="mapie"){ // 检测 mapie
                ans++; i +=5;
            }
            else if(s.substr(i,3)=="map" || s.substr(i,3)=="pie"){ // 普通情况
                ans++; i +=3;
            }
            else i++;
        }
        cout << ans << endl;
    }
}
```

---

### 同类型题与算法套路
1. **子串处理套路**：优先处理重叠/嵌套的特殊情况，贪心跳过最大可能区间。
2. **类似题目**：  
   - **P1106 删数问题**：贪心删除字符使剩余数最小。  
   - **P2709 子串查找**：KMP 算法优化子串匹配。  
   - **P1039 字符串的展开**：分段处理特殊字符模式。

---

### 推荐洛谷题目
1. **P1106**（贪心删除）  
2. **P2709**（高效子串匹配）  
3. **P1141**（字符串变换，BFS 应用）

---

### 个人心得摘录
- **kczw 的调试经验**：最初使用 `find` 函数导致 TLE，改用暴力匹配后优化性能。  
- **CJKZS 的顿悟**：`mapie` 是唯一需要特判的重叠模式，直接优先检测即可覆盖所有边界情况。

---

### 可视化与游戏化设计
**像素动画方案**：
1. **Canvas 绘制**：字符串以像素块展示，当前扫描位置高亮为红色。
2. **特例高亮**：`mapie` 显示为紫色块，删除时播放合成音效。
3. **自动演示**：AI 自动逐帧扫描，按最优路径标记删除位置，右侧面板显示计数和跳转逻辑。

**复古交互**：
- **音效**：8-bit 风格音效，匹配成功时播放 `♪`，特判时 `♫`。
- **积分系统**：每正确处理一个子串得 10 分，特判额外 +5 分，错误检测扣分。

---
处理用时：76.34秒