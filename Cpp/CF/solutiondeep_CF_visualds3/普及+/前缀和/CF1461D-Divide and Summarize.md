# 题目信息

# Divide and Summarize

## 题目描述

Mike received an array $ a $ of length $ n $ as a birthday present and decided to test how pretty it is.

An array would pass the $ i $ -th prettiness test if there is a way to get an array with a sum of elements totaling $ s_i $ , using some number (possibly zero) of slicing operations.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461D/bacc5f6e8a5007e7b78d11e0dd09c5d277e67ed2.png)An array slicing operation is conducted in the following way:

- assume $ mid = \lfloor\frac{max(array) + min(array)}{2}\rfloor $ , where $ max $ and $ min $ — are functions that find the maximum and the minimum array elements. In other words, $ mid $ is the sum of the maximum and the minimum element of $ array $ divided by $ 2 $ rounded down.
- Then the array is split into two parts $ \mathit{left} $ and $ right $ . The $ \mathit{left} $ array contains all elements which are less than or equal $ mid $ , and the $ right $ array contains all elements which are greater than $ mid $ . Elements in $ \mathit{left} $ and $ right $ keep their relative order from $ array $ .
- During the third step we choose which of the $ \mathit{left} $ and $ right $ arrays we want to keep. The chosen array replaces the current one and the other is permanently discarded.

You need to help Mike find out the results of $ q $ prettiness tests.

Note that you test the prettiness of the array $ a $ , so you start each prettiness test with the primordial (initial) array $ a $ . Thus, the first slice (if required) is always performed on the array $ a $ .

## 说明/提示

Explanation of the first test case:

1. We can get an array with the sum $ s_1 = 1 $ in the following way: 1.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.2 $ a = [1, 2, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 2] $ , $ right = [3] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.3 $ a = [1, 2] $ , $ mid = \frac{1+2}{2} = 1 $ , $ \mathit{left} = [1] $ , $ right = [2] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 1 $ .
2. It can be demonstrated that an array with the sum $ s_2 = 8 $ is impossible to generate.
3. An array with the sum $ s_3 = 9 $ can be generated in the following way: 3.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
4. It can be demonstrated that an array with the sum $ s_4 = 12 $ is impossible to generate.
5. We can get an array with the sum $ s_5 = 6 $ in the following way: 5.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ with the sum equalling $ 6 $ .

Explanation of the second test case:

1. It can be demonstrated that an array with the sum $ s_1 = 1 $ is imposssible to generate.
2. We can get an array with the sum $ s_2 = 2 $ in the following way: 2.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 2 $ .
3. It can be demonstrated that an array with the sum $ s_3 = 3 $ is imposssible to generate.
4. We can get an array with the sum $ s_4 = 9 $ in the following way: 4.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
5. We can get an array with the sum $ s_5 = 11 $ with zero slicing operations, because array sum is equal to $ 11 $ .

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
8
9
12
6
5 5
3 1 3 1 3
1
2
3
9
11```

### 输出

```
Yes
No
Yes
No
Yes
No
Yes
No
Yes
Yes```

# AI分析结果


# 💡 Kay的C++算法解析：Divide and Summarize 深入学习指南 💡

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`分治与递归应用`

🗣️ **初步分析**：
> 解决"Divide and Summarize"的关键在于理解递归分治思想。想象你在整理一叠扑克牌：先排序整理，然后不断从中值处分割牌堆，记录每个牌堆的总值。在本题中，我们通过递归模拟切割过程，并用集合记录所有可能的子数组和。
   - 核心思路：先排序数组→计算前缀和→递归分割区间→记录所有可能的子数组和
   - 难点在于高效分割区间和避免重复计算，通过二分查找定位分割点，前缀和优化区间和计算
   - 可视化设计：采用像素风卡牌游戏界面，展示排序后的数组（像素卡片），中值线（发光分割线），区间和（浮动数字）。每次分割时播放"切牌"音效，成功记录和值时触发"收集"特效

---

## 2. 精选优质题解参考

**题解一（作者：Lynkcat）**
* **点评**：思路清晰展现递归分治本质，代码规范（变量名`l/r`直观，`Mp`记录和值），算法高效（二分查找分割点+前缀和优化），边界处理严谨（`nowcut`边界检测）。亮点在于简洁的递归终止条件处理。

**题解二（作者：2021sunzishan）**
* **点评**：教学价值突出，完整展示分治实现流程，代码模块化（独立`dfs`函数）。虽未显式处理边界但通过`mid>=r`检测规避错误。亮点在于使用STL set自动去重，降低实现难度。

**题解三（作者：511_Juruo_wyk）**
* **点评**：最精炼的实现（仅20行核心代码），巧妙利用`upper_bound`定位分割点，递归逻辑紧凑。亮点在于对分治本质的深刻理解（注释强调"这不是暴力而是正解"）。

---

## 3. 核心难点辨析与解题策略

1.  **区间分割点的定位**
    * **分析**：需快速找到首个大于中值的元素位置。优质题解均用二分查找（`upper_bound`或手写二分）实现O(log n)定位，避免O(n)遍历
    * 💡 **学习笔记**：有序数组上的二分查找是优化分治的关键

2.  **递归终止条件设定**
    * **分析**：当区间无法再分割时停止递归。题解通过两种方式判断：①`l == r`（单元素）②`a[l] == a[r]`（全等元素）③分割点无效（如`nowcut==r+1`）
    * 💡 **学习笔记**：明确的递归终止条件避免无限递归

3.  **和值存储与查询优化**
    * **分析**：和值范围大（最大1e11）需用高效数据结构。题解采用`set/map`实现O(log n)插入/查询，优于排序数组+二分
    * 💡 **学习笔记**：根据操作需求选择数据结构——频繁查询用set/map

### ✨ 解题技巧总结
-   **预处理优化**：先排序数组+前缀和，使后续操作均摊O(1)
-   **分治减枝**：当区间元素全等时提前终止递归
-   **STL高效应用**：善用`upper_bound`替代手写二分
-   **数据范围意识**：和值可能超int，统一使用long long

---

## 4. C++核心代码实现赏析

**通用核心实现参考**
* **说明**：综合优质题解优化的标准实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+5;

ll a[N], prefix[N];
set<ll> sums;

void divide(int l, int r) {
    if(l > r) return;
    sums.insert(prefix[r] - prefix[l-1]);
    
    if(a[l] == a[r]) return; // 元素全等时停止分割
    
    ll mid_val = (a[l] + a[r]) >> 1;
    int pos = upper_bound(a+l, a+r+1, mid_val) - a;
    
    divide(l, pos-1);
    divide(pos, r);
}

int main() {
    int T; cin >> T;
    while(T--) {
        sums.clear();
        int n, q; cin >> n >> q;
        for(int i=1; i<=n; i++) cin >> a[i];
        sort(a+1, a+n+1);
        for(int i=1; i<=n; i++) prefix[i] = prefix[i-1] + a[i];
        
        divide(1, n);
        
        while(q--) {
            ll s; cin >> s;
            cout << (sums.count(s) ? "Yes" : "No") << '\n';
        }
    }
}
```
* **代码解读概要**：
  > 1. 输入处理后排序数组并计算前缀和
  > 2. `divide`函数递归分割区间：插入当前区间和→计算中值→二分定位分割点→递归左右子区间
  > 3. 查询时直接检查set中是否存在目标值

---

**题解一核心片段赏析**
```cpp
void dfs(int l,int r) {
    if(l>r) return;
    Mp[s[r]-s[l-1]]=1; // 记录区间和
    mid=(a[l]+a[r])/2;
    int pos = upper_bound(a+l,a+1+r,mid) - a;
    dfs(l,pos-1); dfs(pos,r); 
}
```
* **亮点**：精炼的二分切割与递归调用
* **代码解读**：
  > `Mp`记录当前区间和（通过前缀和数组`s`计算）。`upper_bound`在已排序的`a[l..r]`中查找首个大于中值的位置，将区间分为`[l,pos-1]`和`[pos,r]`。递归终止条件`l>r`处理空区间
* 💡 **学习笔记**：前缀和数组使区间和计算O(1)

**题解二核心片段赏析**
```cpp
void dfs(int l,int r) {
    q.insert(s[r]-s[l-1]); 
    if(l==r) return;
    int mid=upper_bound(a+l,a+1+r,(a[l]+a[r])/2)-a-1; 
    dfs(l,mid); dfs(mid+1,r);
}
```
* **亮点**：极简递归结构，充分利用STL
* **代码解读**：
  > 使用`set`自动去重，`upper_bound`返回值减1得到最后一个≤中值的位置。注意当`mid>=r`时不再递归，避免无效分割
* 💡 **学习笔记**：STL的`upper_bound`返回的是迭代器，需减去数组首地址获得下标

---

## 5. 算法可视化：像素动画演示

* **主题**："卡牌分治大冒险"（8-bit像素风）
* **核心演示**：递归分治过程可视化+和值收集系统

### 动画帧步骤设计
1. **初始化界面**  
   ![初始化](https://via.placeholder.com/400x200?text=排序后的像素卡片+浮动和值显示)  
   - 数组元素显示为彩色像素卡片（大小反映数值）
   - 控制面板：步进/播放/重置按钮+速度滑块

2. **递归分割过程**  
   ```python
   # 伪代码：单步操作
   highlight_current_interval(l, r) # 高亮当前区间
   draw_mid_line((a[l]+a[r])//2)    # 绘制中值分割线
   play_sound("slice")              # 切牌音效
   pos = binary_search(l, r)        # 二分查找动画
   split_cards(pos)                 # 卡片分割特效
   ```
   - 区间高亮：半透明色块覆盖l到r
   - 中值线：红色发光分割线，标出mid值
   - 二分查找：像素箭头在区间内移动，伴随"滴答"音效

3. **和值记录系统**  
   - 计算区间和时：卡片上方弹出`sum=XX`像素数字
   - 存入集合：数字飞入右侧"收集栏"（8-bit宝箱动画）
   - 查询时：目标值在收集栏内闪烁绿光（存在）或红光（不存在）

4. **游戏化元素**  
   - 关卡制：每次完整分割视为1关，通关播放FC胜利音乐
   - 连击系统：连续5次正确查询触发"COMBO!"特效
   - 音效体系：
     * 切割：FC刀剑音效
     * 正确查询：超级马里奥吃金币声
     * 错误查询：俄罗斯方块消除失败声

---

## 6. 拓展练习与相似问题思考

* **分治技巧迁移场景**：
  1. 区间统计问题（如逆序对计数）
  2. 最近点对计算
  3. 归并排序/K路归并

* **洛谷推荐**：
  1. **P1908 逆序对**  
     🗣️ 巩固分治思想在统计问题中的应用
  2. **P1257 平面上的最接近点对**  
     🗣️ 学习分治在几何问题中的变形使用
  3. **P1177 快速排序**  
     🗣️ 理解分治与排序的本质联系

---

## 7. 学习心得与经验分享

> **参考经验（多位作者）**：  
> "排序是解题关键"（IIIIndex）、"set自动去重简化代码"（2021sunzishan）、"二分边界要仔细处理"（Lynkcat）

> **点评**：  
> 这些经验凸显了三个核心要点：  
> 1. 预处理（排序）使后续操作更高效  
> 2. 善用STL避免重复造轮子  
> 3. 边界条件需要严谨验证（可添加断言调试）

---

本次分治算法解析就到这里。记住：好的分治就像切蛋糕——找准分割点，才能得到均匀美味的区块！下次遇到复杂问题时，不妨想想今天的"卡牌分割术"哦~ 🎮✨

---
处理用时：117.25秒