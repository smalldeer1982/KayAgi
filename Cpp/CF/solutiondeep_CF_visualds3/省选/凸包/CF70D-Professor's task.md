# 题目信息

# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1
```

### 输出

```
YES
YES
YES
NO
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Professor's task 深入学习指南 💡

<introduction>
今天我们来分析一道**动态凸包**的经典题目——《Professor's task》。这道题需要我们实时维护点集的凸包，并快速判断新点是否在凸包内。动态凸包是计算几何中的重要问题，也是锻炼“动态数据结构维护”能力的好题。让我们一起拆解它的核心逻辑吧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（动态凸包维护）

🗣️ **初步分析**：
解决这道题的核心是**动态维护凸包**——就像给气球“动态充气”：每次加新点时，如果点在现有凸包外，就把凸包“撑大”，删掉被新点“挡住”的旧点；查询时，只需判断点是否在“气球皮”（凸包）的内部或表面。

### 动态凸包的核心思想
凸包是包围所有点的“最小凸多边形”，可以拆成**上凸壳**（从最左点到最右点，线段向上凸）和**下凸壳**（线段向下凸）。比如，想象一个“山顶”（上凸壳）和“山谷”（下凸壳），合起来就是完整的凸包。我们的目标是**分别维护上下凸壳**：
- 加点时：检查新点是否在上下凸壳外，若是则插入，并删除凸壳上被新点“覆盖”的旧点（用叉积判断凸性）。
- 查询时：点必须**在上凸壳下方**且**在下凸壳上方**（包括边界），才属于凸包内部。

### 可视化设计思路
为了直观理解，我设计了一个**8位像素风的“凸包探险家”动画**：
- **场景**：像素化坐标系（网格背景），上凸壳用红色像素块，下凸壳用蓝色像素块，新点用黄色闪烁。
- **关键操作**：
  - 加点：黄色点“蹦”到屏幕，若在凸包外，红/蓝凸壳块会“滑出”（删除旧点），新点“粘”到凸壳上（插入），伴随“叮”的音效。
  - 查询：绿色箭头指向查询点，若在凸包内，箭头变成彩虹色，播放“滴”的提示音；否则变红，伴随“哔”的音效。
- **交互**：支持“单步执行”（逐帧看凸壳变化）、“自动播放”（像贪吃蛇AI一样完成加点），还有“重置”按钮。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等维度筛选了4道优质题解，帮你快速抓住核心逻辑：
</eval_intro>

### 题解一：Elegia（赞24）
* **点评**：这是动态凸包的**经典坐标排序实现**，完美解决了精度问题。作者用`std::map`维护上下凸壳（以x为键，保证有序），通过叉积判断凸性，每次插入点时删除左右不符合条件的旧点。代码结构清晰，注释少但逻辑自洽，摊还时间复杂度O(logn)——每个点最多被插入和删除一次，非常高效。

### 题解二：旋转卡壳（赞9）
* **点评**：作者尝试用**极角排序**实现动态凸包，但意识到精度问题后，将坐标乘以3缩小误差。代码中用`set`维护极角排序的点，插入时调整凸壳的逻辑与坐标排序一致。虽然极角排序容易丢精度，但作者的“乘3技巧”是很好的启发——遇到精度问题时，先想“如何避免浮点数运算”。

### 题解三：xukuan（赞4）
* **点评**：这道题解的**注释非常详细**，适合入门者理解。作者同样用`map`维护上下凸壳，将`check`（判断点是否在凸壳内）、`delete`（删除无效点）、`insert`（插入新点）拆分成独立函数，逻辑链清晰。代码中用到了`std::prev`和`std::next`（C++11的迭代器工具），展示了标准库的便捷性。

### 题解四：OIer_Tan（赞4）
* **点评**：作者注意到一个**关键细节**——横坐标相同的点必须保留最新的，否则会“神秘WA”。他用`set`维护上下凸壳，插入时先删除同x坐标的旧点，避免凸壳出现“竖线”。这个细节体现了对凸包性质的深刻理解（凸壳上的点x坐标严格递增）。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
动态凸包的难点在于“动态调整”和“精度控制”。结合优质题解，我总结了3个核心问题及解决方法：
</difficulty_intro>

### 1. 如何避免精度误差？
- **问题**：用斜率判断凸性会因浮点数运算产生误差（比如极角排序的`atan2`）。
- **解决**：用**叉积**代替斜率！叉积是整数运算（题目中x、y都是整数），能准确判断向量的转向：
  - 上凸壳：若`叉积(AB, AC) ≥ 0`，说明B点在AC线段的下方，需要删除B。
  - 下凸壳：若`叉积(AB, AC) ≤ 0`，说明B点在AC线段的上方，需要删除B。

### 2. 如何动态调整凸壳？
- **问题**：插入新点后，凸壳可能出现“凹陷”，需要删除无效点。
- **解决**：插入新点后，**向左右两边遍历**，用叉积判断相邻三点是否“凸”：
  - 以上凸壳为例：插入点P后，检查左边的点A、B——若B在AP的下方，删除B；再检查右边的点C、D——若C在PD的下方，删除C。

### 3. 如何快速判断点是否在凸包内？
- **问题**：直接遍历凸壳所有边会超时（O(n)）。
- **解决**：利用凸壳的**单调性**（x坐标递增），用`map::lower_bound`找新点的**前驱**（x比它小的最近点）和**后继**（x比它大的最近点），只需判断这两个点与新点的叉积方向：
  - 上凸壳：新点必须在“前驱→后继”线段的**下方**（叉积≤0）。
  - 下凸壳：新点必须在“前驱→后继”线段的**上方**（叉积≥0）。

💡 **学习笔记**：动态凸包的关键是“拆分上下凸壳+用有序数据结构（map/set）维护x的单调性”。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用的动态凸包实现**，它综合了Elegia和xukuan的思路，结构清晰，适合入门。
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码用`std::map`维护上下凸壳，通过叉积判断凸性，实现动态加点和查询。
* **完整核心代码**：
```cpp
#include <iostream>
#include <map>
using namespace std;

typedef long long ll;
map<int, int> top_hull, down_hull; // 上凸壳（top）、下凸壳（down）

// 叉积：向量AB × 向量AC
ll cross(int x1, int y1, int x2, int y2) {
    return (ll)x1 * y2 - (ll)x2 * y1;
}

// 检查点(x,y)是否在上凸壳下方（包括边界）
bool check_top(int x, int y) {
    auto it = top_hull.lower_bound(x);
    if (it == top_hull.end() || it == top_hull.begin()) return false;
    if (it->first == x) return y <= it->second;
    auto prev_it = prev(it);
    int dx1 = it->first - prev_it->first, dy1 = it->second - prev_it->second;
    int dx2 = x - prev_it->first, dy2 = y - prev_it->second;
    return cross(dx1, dy1, dx2, dy2) <= 0;
}

// 检查点(x,y)是否在下凸壳上方（包括边界）
bool check_down(int x, int y) {
    auto it = down_hull.lower_bound(x);
    if (it == down_hull.end() || it == down_hull.begin()) return false;
    if (it->first == x) return y >= it->second;
    auto prev_it = prev(it);
    int dx1 = it->first - prev_it->first, dy1 = it->second - prev_it->second;
    int dx2 = x - prev_it->first, dy2 = y - prev_it->second;
    return cross(dx1, dy1, dx2, dy2) >= 0;
}

// 删除上凸壳中的无效点（返回true表示删除成功）
bool delete_top(map<int, int>::iterator it) {
    if (it == top_hull.begin()) return false;
    auto prev_it = prev(it), next_it = next(it);
    if (next_it == top_hull.end()) return false;
    int dx1 = it->first - prev_it->first, dy1 = it->second - prev_it->second;
    int dx2 = next_it->first - prev_it->first, dy2 = next_it->second - prev_it->second;
    if (cross(dx1, dy1, dx2, dy2) >= 0) {
        top_hull.erase(it);
        return true;
    }
    return false;
}

// 删除下凸壳中的无效点
bool delete_down(map<int, int>::iterator it) {
    if (it == down_hull.begin()) return false;
    auto prev_it = prev(it), next_it = next(it);
    if (next_it == down_hull.end()) return false;
    int dx1 = it->first - prev_it->first, dy1 = it->second - prev_it->second;
    int dx2 = next_it->first - prev_it->first, dy2 = next_it->second - prev_it->second;
    if (cross(dx1, dy1, dx2, dy2) <= 0) {
        down_hull.erase(it);
        return true;
    }
    return false;
}

// 向上凸壳插入点(x,y)
void insert_top(int x, int y) {
    if (check_top(x, y)) return;
    top_hull[x] = y;
    auto it = top_hull.find(x);
    // 向左删除无效点
    if (it != top_hull.begin()) {
        auto left = prev(it);
        while (delete_top(left++)) left--;
    }
    // 向右删除无效点
    auto right = next(it);
    if (right != top_hull.end()) {
        while (delete_top(right--)) right++;
    }
}

// 向下凸壳插入点(x,y)
void insert_down(int x, int y) {
    if (check_down(x, y)) return;
    down_hull[x] = y;
    auto it = down_hull.find(x);
    if (it != down_hull.begin()) {
        auto left = prev(it);
        while (delete_down(left++)) left--;
    }
    auto right = next(it);
    if (right != down_hull.end()) {
        while (delete_down(right--)) right++;
    }
}

int main() {
    int q; cin >> q;
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            insert_top(x, y);
            insert_down(x, y);
        } else {
            cout << (check_top(x, y) && check_down(x, y) ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
```
* **代码解读概要**：
  1. **数据结构**：用`map<int, int>`维护上下凸壳，键是x坐标（保证有序），值是y坐标。
  2. **核心函数**：
     - `cross`：计算叉积，判断向量转向。
     - `check_top/check_down`：判断点是否在上下凸壳内。
     - `delete_top/delete_down`：删除凸壳上的无效点。
     - `insert_top/insert_down`：插入新点并调整凸壳。
  3. **主逻辑**：处理两种操作——加点时更新上下凸壳，查询时判断点是否在两个凸壳之间。

---

<code_intro_selected>
接下来看优质题解中的**关键片段**，感受不同实现的细节差异：
</code_intro_selected>

### 题解一：Elegia（来源：综合题解）
* **亮点**：用坐标排序代替极角排序，彻底避免精度误差。
* **核心代码片段**：
```cpp
ll det(int x1, int y1, int x2, int y2) {
    return (ll)x1 * y2 - (ll)x2 * y1;
}

bool remove_top(iterator it) {
    if (it == top.begin()) return false;
    iterator jt = it, kt = it;
    --jt; ++kt;
    if (kt == top.end()) return false;
    if (det(it->first - jt->first, it->second - jt->second, 
           kt->first - jt->first, kt->second - jt->second) >= 0) {
        top.erase(it);
        return true;
    }
    return false;
}
```
* **代码解读**：
  - `det`函数就是叉积，计算`(it-jt) × (kt-jt)`——如果≥0，说明it点在jt→kt的下方，需要删除。
  - `remove_top`函数遍历左右点，用叉积判断凸性，逻辑简洁。

* **学习笔记**：叉积是动态凸包的“核心工具”，所有凸性判断都依赖它！

### 题解四：OIer_Tan（来源：综合题解）
* **亮点**：处理了“同x坐标点”的细节，避免凸壳出现“竖线”。
* **核心代码片段**：
```cpp
void update_up(const point &s) {
    if (check_up(s)) return;
    // 删除同x坐标的旧点
    up.erase(up.lower_bound(point(s.x, -1e9)), up.upper_bound(point(s.x, 1e9)));
    auto it = up.insert(s).first;
    // 调整左右点
    if (it != up.begin()) {
        auto left = prev(it);
        while (remove_up(left++)) left--;
    }
    auto right = next(it);
    if (right != up.end()) while (remove_up(right--)) right++;
}
```
* **代码解读**：
  - 插入新点前，先用`erase`删除所有x等于s.x的旧点——因为凸壳上的点x必须严格递增，同x的点只能保留一个（最“凸”的那个）。
  - 这个细节容易被忽略，但直接影响正确性（比如样例中的点(2,0)和(2,2)，同x但y不同，必须保留y最大的上凸壳点）。

* **学习笔记**：处理边界情况是编程的重要能力，要对数据结构的“单调性”敏感！


## 5. 算法可视化：像素动画演示

### 动画设计方案：像素凸壳探险家
**主题**：用8位像素风模拟“凸壳搭建”，像玩《贪吃蛇》一样直观理解动态凸包。

### 核心演示内容
1. **场景初始化**：
   - 屏幕显示像素化坐标系（网格背景），上凸壳用红色方块，下凸壳用蓝色方块，新点用黄色闪烁。
   - 控制面板：“开始/暂停”“单步执行”“重置”按钮，速度滑块（1~5档）。
   - 8位风格BGM（循环播放《超级马里奥》小关卡音乐）。

2. **算法动态演示**：
   - **加点操作**：
     1. 黄色点“蹦”到屏幕中央，伴随“嗒”的音效。
     2. 若点在凸包外，红/蓝凸壳块会“滑出”（删除旧点），新点“粘”到凸壳上（变成红/蓝），伴随“叮”的音效。
     3. 若点在凸包内，黄色点“消失”，伴随“噗”的音效。
   - **查询操作**：
     1. 绿色箭头指向查询点，伴随“滴”的提示音。
     2. 若在凸包内，箭头变成彩虹色，屏幕下方显示“YES”；否则箭头变红，显示“NO”，伴随“哔”的音效。

3. **交互设计**：
   - **单步执行**：点击“单步”，动画走一帧（比如插入点→删除一个旧点），便于观察细节。
   - **自动播放**：点击“开始”，动画按设定速度自动执行，像“AI搭积木”一样完成所有操作。
   - **重置**：恢复初始状态，重新开始演示。

### 技术实现
- 用HTML5 Canvas绘制像素图形，CSS设置复古风格（比如像素字体、8位颜色 palette）。
- 用JavaScript实现动画逻辑：
  - 叉积计算：用整数运算，避免浮点数误差。
  - 音效：用Web Audio API播放8位音效（比如“叮”用200Hz正弦波，“哔”用400Hz方波）。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
动态凸包的思路可以推广到**所有需要“动态维护几何形状”的问题**，比如：
1. 维护动态线段的凸包（比如《防线修建》）。
2. 动态查询点集的最远点对（旋转卡壳+动态凸包）。
3. 实时计算点集的最小包围圆（类似凸包的动态维护）。

### 洛谷练习推荐
1. **P2521 [HAOI2011] 防线修建**：动态维护上凸壳，是本题的“简化版”，适合入门。
2. **P4166 [SCOI2007] 最大土地面积**：静态凸包+旋转卡壳，巩固凸包的基础应用。
3. **CF70D Professor's task**：本题原题，强化动态凸包的实现细节。


## 7. 学习心得与经验分享 (若有)

> **参考经验 (来自 Elegia)**：“坐标排序比极角排序更稳定，因为极角的atan2会有精度误差，而坐标排序是整数运算。”
>
> **点评**：这个经验非常实用！计算几何中，能不用浮点数就不用——叉积、曼哈顿距离等整数运算才是“稳赢”的选择。


<conclusion>
动态凸包的核心是“拆分上下凸壳+用有序数据结构维护x单调性”，而叉积是连接所有逻辑的“桥梁”。通过这道题，我们学会了如何用`map`/`set`动态调整数据结构，如何处理精度问题，如何关注边界细节。

记住：编程的进步来自“拆解问题”——把复杂的动态凸包拆成“上下凸壳”“叉积判断”“插入调整”三个小问题，每个小问题解决了，大问题也就迎刃而解了！下次我们再挑战更难的计算几何问题～💪
</conclusion>

---
处理用时：120.32秒