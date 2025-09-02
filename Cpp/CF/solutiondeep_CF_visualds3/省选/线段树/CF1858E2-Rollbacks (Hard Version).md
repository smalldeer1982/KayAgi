# 题目信息

# Rollbacks (Hard Version)

## 题目描述

This is a hard version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1, 1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# AI分析结果


### 💡 Kay的C++算法解析：Rollbacks (Hard Version) 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`数据结构应用`（树状数组+集合维护）  
🗣️ **初步分析**：
> 解决本题关键在于**高效维护序列状态**，特别是处理回滚操作。想象一个可以"存档读档"的游戏系统：
> - **树状数组**作为"计数器"，标记每个数字首次出现的位置
> - **集合(set)** 作为"位置记录本"，跟踪每个数字的所有出现位置
> - **操作栈**作为"存档点"，保存完整操作上下文
> 
> 核心流程：
> 1. 添加元素时更新集合和树状数组，重点维护数字的首次出现位置
> 2. 删除操作仅修改逻辑长度`len`（"伪删除"）
> 3. 回滚时从栈顶恢复状态
> 
> **像素动画设计**：
> - 8-bit网格：每格代表序列位置，不同颜色方块表示不同数字
> - 高亮特效：新添加位置(绿色闪烁)、删除区间(红色边框)
> - 树状数组动态：条形图实时显示前缀和变化
> - 操作栈可视化：存档点列表，回滚时播放"嗖"的音效
> - 交互控制：单步执行(方向键)、速度滑块、AI自动演示模式

---

#### 2. 精选优质题解参考
**题解一 (CSP_Sept)**：
* **点评**：思路清晰度极佳，完整阐述树状数组维护首次出现位置的原理。代码规范性强：变量名`a`(序列)、`s`(集合数组)、`c`(树状数组)含义明确；边界处理严谨（检查集合非空）。算法有效性高：O(q log q)时间复杂度，巧妙用`len`避免物理删除。实践价值突出：可直接用于竞赛，作者调试心得"注意检查空集合"极具参考价值。亮点在于操作栈存储多维状态实现高效回滚。

**题解二 (Register_int)**：
* **点评**：代码简洁性突出，封装`modify()`函数统一处理位置更新。逻辑推导合理：将操作类型(+/-)与状态变量绑定存入栈中。算法亮点在于模块化设计，树状数组更新与集合操作解耦，增强可维护性。实践时需注意栈中存储的旧值完整性，适合学习代码组织技巧。

**题解三 (Leasier)**：
* **点评**：创新性提出优化方向：用`fir`数组替代集合降复杂度。虽然未完全实现，但思路启发性强（潜在O(q)解法）。代码中`ask()`函数采用标准树状数组实现，可作为模板参考。学习价值在于展示算法优化思路的推导过程。

---

#### 3. 核心难点辨析与解题策略
1. **难点：首次位置动态维护**
   * **分析**：添加元素时需判断是否首次出现，若数字已存在，需更新其首次位置（可能因删除而改变）
   * **解决**：用`set`存储所有位置，取`begin()`获取最小位置（首次出现），配合树状数组更新标记

2. **难点：回滚状态一致性**
   * **分析**：需同步恢复序列值、集合、树状数组和长度变量
   * **解决**：操作栈保存四元组`(操作类型, 位置, 旧值, 辅助信息)`，回滚时逆序执行

3. **难点：高效伪删除**
   * **分析**：物理删除数据会导致回滚时无法恢复
   * **解决**：用`len`表示逻辑长度，实际数据保留，删除仅修改变量值

💡 **学习笔记**：树状数组+集合是维护数字首次出现的黄金组合；操作栈是处理回滚的通用范式

✨ **解题技巧总结**：
- **状态封装**：将操作影响的所有变量绑定存储
- **增量更新**：仅修改变化部分（如首次位置改变时才更新树状数组）
- **防御性检查**：操作集合前验证`!set.empty()`
- **逻辑分离**：树状数组仅负责前缀和，集合专注位置管理

---

#### 4. C++核心代码实现赏析
```cpp
// 通用核心实现 (综合优质题解优化)
#include <set>
#include <stack>
#include <cstring>
using namespace std;
const int MAXN = 1e6+5;

int c[MAXN], a[MAXN], len; // 树状数组/序列/逻辑长度
set<int> posSet[MAXN];     // posSet[x]: x的所有位置
stack<tuple<char, int, int, int>> stk; // (操作类型,位置,旧值,辅助信息)

void add(int idx, int v) { 
    for(; idx < MAXN; idx += idx&-idx) c[idx] += v; 
}

int query(int idx) {
    int res = 0;
    for(; idx; idx -= idx&-idx) res += c[idx];
    return res;
}

void rollback() {
    auto [op, pos, oldVal, aux] = stk.top(); stk.pop();
    if(op == '+') {
        int curVal = a[pos];
        // 从集合移除当前位置
        posSet[curVal].erase(pos);
        if(!posSet[curVal].empty() && *posSet[curVal].begin() == pos) 
            add(pos, -1); // 移除首次标记
        // 恢复旧值
        a[pos] = oldVal;
        if(oldVal != -1) {
            posSet[oldVal].insert(pos);
            if(*posSet[oldVal].begin() == pos) 
                add(pos, 1); // 标记新首次位置
        }
        len--;
    } else if(op == '-') {
        len += aux; // 恢复删除的长度
    }
}

int main() {
    memset(a, -1, sizeof(a));
    int q; scanf("%d", &q);
    while(q--) {
        char op; scanf(" %c", &op);
        if(op == '+') {
            int x; scanf("%d", &x);
            stk.push({'+', len+1, a[len+1], 0});
            if(a[len+1] != -1) { // 清理旧值
                posSet[a[len+1]].erase(len+1);
                if(!posSet[a[len+1]].empty()) 
                    add(*posSet[a[len+1]].begin(), 1);
            }
            a[++len] = x; // 添加新值
            if(!posSet[x].empty()) 
                add(*posSet[x].begin(), -1); // 移除旧首次标记
            posSet[x].insert(len);
            add(*posSet[x].begin(), 1); // 标记新首次位置
        } else if(op == '-') {
            int k; scanf("%d", &k);
            stk.push({'-', 0, 0, k});
            len -= k; // 伪删除
        } else if(op == '!') {
            rollback();
        } else if(op == '?') {
            printf("%d\n", query(len));
            fflush(stdout);
        }
    }
}
```

**代码解读概要**：
- **树状数组**：标记首次出现位置（值1），`query(len)`即不同数字数
- **集合管理**：`posSet[x]`自动排序位置，快速获取首次出现(`begin()`)
- **操作栈**：存储完整操作上下文，支持多步回滚
- **增量更新**：仅当首次位置变化时才修改树状数组

---

#### 5. 算法可视化：像素动画演示
**主题**：8-bit风格"序列探险"  
**核心演示流程**：
```mermaid
graph TD
    A[开始] --> B{操作类型}
    B -- + --> C[新方块滑入]
    B -- - --> D[红框标记删除区间]
    B -- ! --> E[跳转存档点]
    B -- ? --> F[显示答案气泡]
    C --> G[首次出现? 闪烁绿光 : 灰光]
    G --> H[树状数组条形图更新]
    D --> I[len指针左移]
    E --> J[播放'嗖'音效+存档点弹跳]
    F --> K[显示query(len)结果]
```

**交互控制面板**：
- 步进控制：←/→单步执行，空格暂停
- 速度滑块：调整AI演示速度
- 模式切换：手动操作/AI自动演示
- 高亮开关：显示树状数组变化

**关键动画细节**：
1. 添加操作：
   - 新方块从右侧滑入，伴随"叮"音效
   - 树状数组对应位置+1，条形图动态上升
   - 首次出现时方块顶部显示"1st"像素字

2. 删除操作：
   - 红色半透明覆盖删除区间
   - `len`指针向左滑动，伴随"咔嗒"音效

3. 回滚操作：
   - 画面跳转到存档点，显示操作栈弹出动画
   - 被恢复的方块绿色闪烁0.5秒

**技术实现**：Canvas绘制网格+Web Audio API音效，数据结构变化实时映射到像素动画

---

#### 6. 拓展练习与相似问题思考
1. **通用技巧迁移**：
   - 树状数组+集合维护首次出现：适用于需频繁查询不同元素数的场景
   - 操作栈回滚模式：可扩展至文本编辑器、数据库事务管理
   - 逻辑删除策略：在内存受限场景优化性能

2. **洛谷推荐**：
   - [P3919 可持久化数组](https://www.luogu.com.cn/problem/P3919)  
     → 巩固主席树实现版本回溯
   - [P3369 普通平衡树](https://www.luogu.com.cn/problem/P3369)  
     → 强化set维护有序数据能力
   - [CF896C](https://codeforces.com/problemset/problem/896/C)  
     → 学习操作栈结合ODT的实现

---

#### 7. 学习心得与经验分享
> **CSP_Sept的调试经验**：  
> "在维护首次出现位置时，必须检查集合是否为空，否则取`begin()`会RE。通过打印中间变量调试边界条件"  
>   
> **Kay点评**：  
> 这是处理STL容器的黄金准则——始终验证容器状态（`empty()`/`size()`）。建议学习者添加断言如`assert(!posSet[x].empty())`，或在关键操作前打印容器大小。

---

### 结语
通过本指南，我们系统剖析了Rollbacks问题的核心解法——树状数组+集合的优雅组合，配合操作栈实现高效回滚。记住：算法学习如探险，每个难点都是提升的契机。现在就用洛谷练习题巩固技能吧！下次算法之旅再见！🚀

---
处理用时：177.75秒