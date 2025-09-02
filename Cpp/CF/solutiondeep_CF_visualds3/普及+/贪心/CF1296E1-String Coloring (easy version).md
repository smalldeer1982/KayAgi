# 题目信息

# String Coloring (easy version)

## 题目描述

This is an easy version of the problem. The actual problems are different, but the easy version is almost a subtask of the hard version. Note that the constraints and the output format are different.

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to color all its characters one of the two colors (each character to exactly one color, the same letters can be colored the same or different colors, i.e. you can choose exactly one color for each index in $ s $ ).

After coloring, you can swap any two neighboring characters of the string that are colored different colors. You can perform such an operation arbitrary (possibly, zero) number of times.

The goal is to make the string sorted, i.e. all characters should be in alphabetical order.

Your task is to say if it is possible to color the given string so that after coloring it can become sorted by some sequence of swaps. Note that you have to restore only coloring, not the sequence of swaps.

## 样例 #1

### 输入

```
9
abacbecfd```

### 输出

```
YES
001010101```

## 样例 #2

### 输入

```
8
aaabbcbb```

### 输出

```
YES
01011011```

## 样例 #3

### 输入

```
7
abcdedc```

### 输出

```
NO```

## 样例 #4

### 输入

```
5
abcde```

### 输出

```
YES
00000```

# AI分析结果


### 💡 Kay的C++算法解析：String Coloring (easy version) 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：贪心算法与二分图判定

🗣️ **初步分析**：
> 本题核心是将字符串划分为两个非降序子序列（颜色0/1）。贪心策略通过维护两个子序列的尾部字符实现高效分配（时间复杂度O(n)）；二分图方法通过逆序对建图验证二染色可行性。  
> - **贪心思路**：优先将字符放入颜色1序列（尽可能保留较大值），剩余放入颜色0序列并检查是否非降序
> - **二分图思路**：所有逆序对字符必须不同色，转化为二染色问题
> - **可视化设计**：采用像素轨道动画（见第5节），用绿色/红色方块表示两种颜色，动态展示字符分配过程，逆序检查时触发闪烁特效和音效

---

#### 精选优质题解参考
**题解一（流绪）**  
* **点评**：巧妙运用动态规划思想，维护每个字母的最大颜色值（26维数组）。代码简洁高效（O(26n)），边界处理严谨，变量命名清晰（`sum[]`存储字母最大颜色值）。亮点在于将导弹拦截问题思路迁移到颜色分配，具有启发性。

**题解二（chinaxjh）**  
* **点评**：创新性地将问题转化为二分图判定，通过冒泡排序建图。虽然时间复杂度较高（O(n²)），但思路独特且代码规范（链式前向星存图）。亮点在于揭示了相邻交换与图染色的本质关联，提供跨算法视角。

**题解五（_masppy_）**  
* **点评**：最简洁的贪心实现，用`stk[]`存储颜色0子序列。代码逻辑清晰（O(n)），核心循环仅10行。亮点在于分离两个子序列的检查逻辑，调试友好（独立存储颜色0序列）。

---

#### 核心难点辨析与解题策略
1. **子序列分割的贪心策略**  
   * **分析**：必须保证两个子序列各自非降序。优质解法通过"当前字符≥前驱则归入序列1，否则归入序列0"的规则，确保序列1尽可能保留大值以降低序列2的排序难度
   * 💡 **学习笔记**：贪心选择中"让序列1尽量大"是保证序列2可排序的关键

2. **逆序对的动态传递性**  
   * **分析**：解法一/四揭示核心规律：若字符a位置在b前且a>b，则b的颜色值必须>a的颜色值。通过维护26个字母的最大颜色值实现高效传递
   * 💡 **学习笔记**：逆序关系具有传递性，动态规划可避免重复计算

3. **二分图转换的思维跳跃**  
   * **分析**：解法二发现相邻交换本质是逆序对节点的染色约束。需注意建图时记录原始位置（`num[]`数组），避免排序后位置丢失
   * 💡 **学习笔记**：复杂规则可转化为图论问题，但需注意n较大时效率问题

### ✨ 解题技巧总结
- **双序列维护技巧**：用两个变量（`last0/last1`）实时跟踪子序列尾字符
- **传递性优化**：26维数组替代全局扫描，复杂度从O(n²)降至O(n)
- **防御性检查**：显式存储序列2并二次验证（题解五），避免隐式错误

---

#### C++核心代码赏析
**通用核心实现（贪心优化版）**  
```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n; string s;
    cin >> n >> s;
    vector<int> ans(n);
    char last0 = '\0', last1 = '\0'; // 双序列尾字符
    
    for (int i = 0; i < n; i++) {
        if (s[i] >= last0) {        // 优先尝试序列0
            last0 = s[i]; ans[i] = 0;
        } else if (s[i] >= last1) { // 再尝试序列1
            last1 = s[i]; ans[i] = 1;
        } else {                    // 无法分配
            cout << "NO"; return 0;
        }
    }
    cout << "YES\n";
    for (int c : ans) cout << c;
}
```
> **代码解读概要**：  
> 1. 初始化`last0/last1`为最小字符（`\0`）  
> 2. 遍历字符：优先放入序列0（若≥`last0`），否则尝试序列1  
> 3. 若均不满足则无解  
> 4. 成功遍历则输出染色方案  

---

**题解一片段（DP优化）**  
```cpp
int maxx = 0;
for(int j = c-'a'+1; j<26; j++)  // 扫描比当前大的字母
    maxx = max(maxx, sum[j]);     // 取最大颜色值
ans[i] = maxx + 1;                // 设定当前颜色
sum[c-'a'] = max(sum[c-'a'], ans[i]); // 更新字母颜色值
```
> **亮点**：26维数组避免全局扫描  
> **学习笔记**：利用字母有限性（26个）将复杂度降至O(26n)

**题解二片段（二分图染色）**  
```cpp
void add(int x, int y) {          // 建图函数
    len++; a[len]=y; 
    nxt[len]=las[x]; las[x]=len;
}
bool dfs(int v, int c) {          // 染色检查
    color[v] = c;
    for(int i=las[v]; i; i=nxt[i]) {
        if(color[a[i]] == c) return false;
        if(!color[a[i]] && !dfs(a[i], -c)) return false;
    }
    return true;
}
```
> **亮点**：链式前向星高效存图  
> **学习笔记**：无向图建边需双向添加（实际代码需补`add(y,x)`）

**题解五片段（贪心实现）**  
```cpp
char p = s[1];                   // 序列1尾字符
a[1] = 1;                        // 首字符归序列1
for(int i=2; i<=n; i++) {
    if(s[i] >= p) {              // 归入序列1
        p = s[i]; a[i] = 1; 
    } else {                     // 归入序列0
        stk[++cnt] = s[i]; a[i] = 0;
    }
}
```
> **亮点**：独立存储序列2便于检查  
> **学习笔记**：序列1的更新策略影响序列2的排序难度

---

#### 算法可视化：像素动画演示
![](https://via.placeholder.com/400x200/000000/FFFFFF?text=8-bit+Pixel+Animation+Demo)  
> **主题**：双轨道字符分配模拟（复古游戏风）  
> **核心设计**：  
> 1. **像素网格**：上方显示原始字符串，下方双轨道（绿/红）对应子序列  
> 2. **动态分配**：字符沿虚线动画滑入对应轨道，伴随8-bit音效  
>  - 成功归入：清脆"叮"声（序列0）/ 低沉"咚"声（序列1）  
>  - 冲突：闪烁红光+警报音  
> 3. **序列检查**：完成分配后，红色轨道启动冒泡检查，逆序对触发像素爆炸特效  
> 4. **交互控制**：  
>  - 步进模式：空格键单步执行  
>  - 自动演示：速度滑块调节（1x-5x）  
>  - 重置按钮：重新初始化场景  
> **设计意义**：轨道可视化强化"子序列独立性"，爆炸特效直观揭示逆序错误  

---

#### 拓展练习
**相似问题迁移**  
1. 多序列分配问题（如P1090 合并果子）  
2. 带约束的相邻交换（如P1966 火柴排队）  
3. 二分图实际应用（如P1330 封锁阳光大学）  

**洛谷推荐**  
1. **P1090** - 合并果子  
   > 🗣️ 贪心策略的直接应用，巩固优先队列使用  
2. **P1908** - 逆序对  
   > 🗣️ 深入练习逆序对处理，强化分治/树状数组应用  
3. **P1330** - 封锁阳光大学  
   > 🗣️ 二分图判定的经典场景，拓展染色问题思路  

---

#### 学习心得
> **来自题解二**："比赛后发现正解是导弹拦截思路，心态崩了"  
> **Kay点评**：算法迁移能力至关重要！本题动态规划解法与导弹拦截的"拦截系统"思路高度相似，日常需积累模型转换经验。  

> **调试经验**：题解五的`stk[]`独立存储验证启示：复杂逻辑应分解验证，避免隐式错误  

---

通过本指南，希望您不仅掌握本题解法，更能理解贪心策略的构建与算法迁移思维。下次遇到相邻交换问题，记得尝试轨道可视化思考哦！🚀

---
处理用时：235.45秒