# 题目信息

# Field Division (easy version)

## 题目描述

This is an easy version of the problem; it differs from the hard version only by the question. The easy version only needs you to print whether some values are non-zero or not. The hard version needs you to print the exact values.

Alice and Bob are dividing the field. The field is a rectangle of size $ n \times m $ ( $ 2 \le n, m \le 10^9 $ ), the rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The cell at the intersection of row $ r $ and column $ c $ is denoted as ( $ r, c $ ).

Bob has $ k $ ( $ 2 \le k \le 2 \cdot 10^5 $ ) fountains, all of them are located in different cells of the field. Alice is responsible for dividing the field, but she must meet several conditions:

- To divide the field, Alice will start her path in any free (without a fountain) cell on the left or top side of the field and will move, each time moving to the adjacent cell down or right. Her path will end on the right or bottom side of the field.
- Alice's path will divide the field into two parts — one part will belong to Alice (this part includes the cells of her path), the other part — to Bob.
- Alice will own the part that includes the cell ( $ n, 1 $ ).
- Bob will own the part that includes the cell ( $ 1, m $ ).

Alice wants to divide the field in such a way as to get as many cells as possible.

Bob wants to keep ownership of all the fountains, but he can give one of them to Alice. First, output the integer $ \alpha $ — the maximum possible size of Alice's plot, if Bob does not give her any fountain (i.e., all fountains will remain on Bob's plot). Then output $ k $ non-negative integers $ a_1, a_2, \dots, a_k $ , where:

- $ a_i=0 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot does not increase (i.e., remains equal to $ \alpha $ );
- $ a_i=1 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot increases (i.e., becomes greater than $ \alpha $ ).

## 说明/提示

Below are the images for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1980F1/50ede57a92b2f87fd310741ab01efa95ca5a8eab.png) The indices of the fountains are labeled in green. The cells belonging to Alice are marked in blue.Note that if Bob gives Alice fountain $ 1 $ or fountain $ 3 $ , then that fountain cannot be on Alice's plot.

## 样例 #1

### 输入

```
5
2 2 3
1 1
1 2
2 2
5 5 4
1 2
2 2
3 4
4 3
2 5 9
1 2
1 5
1 1
2 2
2 4
2 5
1 4
2 3
1 3
6 4 4
6 2
1 3
1 4
1 2
3 4 5
2 1
3 2
1 4
1 3
2 4```

### 输出

```
1
1 0 1 
11
0 1 0 1 
1
0 0 1 1 0 0 0 0 0 
6
1 0 0 0 
1
1 1 0 0 0```

# AI分析结果



**唯一算法分类**  
单调栈/扫描线法

---

**综合分析与结论**  
本题核心在于找出所有阻挡Alice路径的喷泉关键点，移除这些点将允许Alice获得更多区域。通过按坐标排序并维护纵坐标递减的单调栈，筛选出必须保留的喷泉。计算初始最大值α后，仅关键点对应的喷泉移除时可能增加α，其余喷泉不影响结果。

**算法流程与可视化设计**  
1. **排序处理**：将所有喷泉按x升序、y升序排列，确保同一列中先处理较小y的喷泉。  
2. **单调栈筛选**：维护纵坐标递减的栈，若当前喷泉y小于栈顶则弹出栈顶（非关键点），最终栈中保留关键点。  
3. **面积计算**：遍历栈中相邻元素，计算(x差 × (y-1))的累加和。  
4. **结果标记**：栈中喷泉对应a_i=1，其余为0。

**可视化设计要点**  
- **像素网格**：用Canvas绘制n×m网格，喷泉标记为绿色，栈操作用红色高亮。  
- **动态栈显示**：右侧显示当前栈内元素的坐标，弹出/压入时播放8-bit音效。  
- **面积区块**：关键点间区域用不同蓝色块填充，实时更新面积数值。  
- **自动模式**：按处理顺序自动播放，空格键暂停/继续，速度可调。

---

**题解清单 (≥4星)**  
1. **banned_gutongxing (4.5星)**  
   - 思路清晰，利用单调栈维护关键点，处理同一x的喷泉逻辑严谨。  
   - 代码可读性较好，变量命名规范，但未处理边界需注意。  
   - 关键亮点：通过排序后单调栈直接筛选有效喷泉，时间复杂度O(k)。

2. **FiraCode (4星)**  
   - 逆向维护后缀最小值，实现简洁，但处理相同x的喷泉稍显复杂。  
   - 代码较短，但未明确解释如何确保正确性。  
   - 关键亮点：后缀min思路直观，适合理解路径分割的影响。

3. **ATION001 (4星)**  
   - 与首解思路一致，代码结构相似但注释更少。  
   - 提供图示辅助说明，帮助理解单调栈的作用。  
   - 关键亮点：详细图解关键点筛选逻辑，增强直观性。

---

**最优思路提炼**  
1. **排序策略**：x优先升序，y次优先升序，确保同一列处理最小y。  
2. **单调递减栈**：维护纵坐标严格递减，排除被阻挡的非关键喷泉。  
3. **面积分段计算**：每段面积为(x_i - x_{i-1}) × (y_i - 1)，总和为α。  
4. **关键点标记**：仅栈内喷泉移除可能增加面积，标记a_i=1。

---

**同类型题与算法套路**  
- **Largest Rectangle in Histogram**：利用单调栈维护高度递增，计算最大矩形。  
- **Skyline Problem**：扫描线法处理建筑轮廓，类似坐标排序与极值维护。  
- **Convex Hull**：筛选极值点构成边界，与关键点筛选思路相通。

**推荐相似题目**  
1. 洛谷P2742 [凸包模板题]  
2. 洛谷P1904 [天际线扫描线应用]  
3. 洛谷P1565 [二维区域分割问题]

---

**代码核心实现（banned_gutongxing）**  
```cpp
sort(a+1,a+1+k,cmp); // 按x升序，y升序排序
stack<pair<int,pair<int,int>>> st;
for(int i=1; i<=k; i++){
    if(a[i].x == a[i-1].x) ans[a[i].id]=0; // 同x非最小y，直接排除
    else{
        while(!st.empty() && st.top().second.second >= a[i].y){
            ans[st.top().first] = 0; // 弹出非关键点
            st.pop();
        }
        st.push({a[i].id, {a[i].x, a[i].y}});
        ans[a[i].id] = 1; // 栈内标记为关键点
    }
}
// 计算面积总和
int anss = 0;
st.push({0, {n, m+1}}); // 虚拟终点
while(!st.empty()){
    auto tmp = st.top(); st.pop();
    if(st.empty()) anss += tmp.second.first * (tmp.second.second-1);
    else anss += (tmp.second.first - st.top().second.first) * (tmp.second.second-1);
}
```

---

**可视化与复古游戏化设计**  
- **8-bit风格渲染**：喷泉用绿色方块，关键点路径红色闪烁，面积区块渐变色填充。  
- **音效触发**：压栈时播放“哔”声，弹栈时“啵”声，计算面积时播放金币声。  
- **交互控制**：方向键调整动画速度，Enter键单步执行，Esc暂停背景音乐。  
- **自动演示AI**：模拟喷泉处理流程，动态显示栈变化和面积累加，每秒2步节奏。

**算法演示步骤**  
1. 初始化网格，加载所有喷泉位置。  
2. 按x排序后，逐个喷泉高亮处理，比较y与栈顶。  
3. 若y较小，弹出栈顶并标记为非关键（灰色），压入当前（红色）。  
4. 最终栈元素生成蓝色区域块，右侧显示面积总和α。  
5. 结果界面显示每个喷泉的a_i标记，关键点闪烁提示。

---
处理用时：121.74秒