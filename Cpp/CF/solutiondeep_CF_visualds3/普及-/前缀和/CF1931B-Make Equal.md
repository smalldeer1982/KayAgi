# 题目信息

# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4```

### 输出

```
YES
NO
YES
NO
NO
YES```

# AI分析结果


### 💡 Kay的C++算法解析：Make Equal 深入学习指南 💡

#### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`模拟与贪心应用`  

🗣️ **初步分析**：  
> 解决"Make Equal"的关键在于**水量流动的模拟**。想象一群水桶排成一列，前面的水桶只能向后倒水（类似单向水流）。最终目标是所有桶水量相同（即平均值）。核心策略是：  
> - 从左到右遍历，维护一个"水量银行"（当前可用的多余水量）  
> - 当前桶水量＞平均值时，多余水量存入银行  
> - 当前桶水量＜平均值时，从银行取水补足  
> - **核心难点**：银行余额不能为负（否则无法补足）  
>  
> **可视化设计**：  
> 采用**8位像素风格**：每个桶用不同颜色像素方块表示，水面高度随数值变化。银行余额用顶部进度条显示，负数时闪烁红光并播放警告音效。控制面板含单步执行按钮，每步显示当前操作说明（如"桶1存入3单位"）。

---

#### 2. 精选优质题解参考
**题解 (RyanLi)**  
* **点评**：  
  思路清晰直白——维护`diff`变量作为"水量银行"，完美符合题目单向流动特性。代码简洁高效（时间复杂度O(n)）：  
  - 变量名`aver/diff`含义明确，边界处理严谨（即时检测负数）  
  - 亮点：用`ll aver`避免整数溢出，`flag`即时终止优化性能  
  - 实践价值：竞赛级代码，可直接套用类似贪心场景  

---

#### 3. 核心难点辨析与解题策略
1. **难点：水量银行的设计与维护**  
   * **分析**：银行变量(`diff`)必须实时反映可用余量。RyanLi的方案中，`diff += a[i]-aver`同步更新余额，负数检测确保可行性  
   * 💡 **学习笔记**：银行变量是贪心算法的"心脏"，必须精确反映系统状态  

2. **难点：单向流动的约束处理**  
   * **分析**：因水只能向后流，当前桶缺水时只能依赖前面桶的盈余。若银行余额不足，后续无补救机会  
   * 💡 **学习笔记**：单向约束下，必须"边走边查"，无法事后补救  

3. **难点：整数溢出与精度处理**  
   * **分析**：总和可能超`int`范围（如样例最大2e5*1e9）。RyanLi用`ll aver`规避溢出，其他题解忽略此点易出错  
   * 💡 **学习笔记**：涉及大数求和时，优先使用`long long`  

### ✨ 解题技巧总结  
- **即时检测法**：变量更新后立刻检查约束条件（如`diff<0`），避免累积错误  
- **命名即注释**：像`diff`这样的变量名自带解释，减少注释依赖  
- **边界预判**：输入规模较大时，主动预防整数溢出  

---

#### 4. C++核心代码实现赏析
**通用核心实现 (基于RyanLi)**  
```cpp
#include <iostream>
using namespace std;
using ll = long long; // 关键：防溢出

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        ll sum = 0;
        int a[200010];
        for (int i=0; i<n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        ll aver = sum / n; // 目标水量
        ll bank = 0;       // "水量银行"
        bool valid = true;
        
        for (int i=0; i<n; i++) {
            bank += a[i] - aver; // 更新银行余额
            if (bank < 0) {      // 即时检测
                valid = false;
                break;
            }
        }
        cout << (valid ? "YES" : "NO") << '\n';
    }
}
```
**代码解读概要**：  
> 1. 读入总和计算平均值  
> 2. 遍历中实时更新银行余额  
> 3. 银行负数时立即终止并返回NO  
> 4. 全程用`long long`避免溢出  

---

#### 5. 算法可视化：像素动画演示  
* **主题**：`像素水桶银行`  
* **核心演示**：  
  ![动画示意图](https://via.placeholder.com/400x200?text=Pixel+Animation+Here)  
  *8位像素网格中，每个桶显示当前水量（柱状高度）。顶部进度条表示银行余额：*  
  - **绿色**：余额充足  
  - **闪烁红色**：余额为负（伴随"滴嘟"警告音）  

* **交互设计**：  
  1. **单步执行**：按空格键逐步显示`bank += a[i]-aver`  
  2. **高亮机制**：当前桶边框闪烁，水量变化时像素块浮动  
  3. **音效设计**：  
     - 加水时"叮"声（频率随水量升高）  
     - 银行为负时短促警报声  
  4. **AI演示模式**：自动播放速度可调，结束时播放胜利音效  

---

#### 6. 拓展练习与相似问题
* **技巧迁移**：  
  此贪心思想也适用于：  
  1. 资源单向调度（如卡车货运）  
  2. 能量传递问题（如[LeetCode 55]跳跃游戏）  
  3. 分布式任务均衡  

* **洛谷推荐**：  
  1. **P1031 均分纸牌** - 同类贪心模板题  
  2. **P1094 纪念品分组** - 双向贪心应用  
  3. **P1106 删数问题** - 贪心选择策略进阶  

---

#### 7. 学习心得与经验分享
> 本次题解未包含作者个人调试心得，但RyanLi的代码结构暗示重要经验：  
> **变量命名即文档**：如`bank`一词使逻辑不言自明，减少调试成本  

---

通过本次分析，我们掌握了贪心算法中"状态维护"的核心技巧。记住：好算法像水流——自然且不可逆！下次见！💪

---
处理用时：78.74秒