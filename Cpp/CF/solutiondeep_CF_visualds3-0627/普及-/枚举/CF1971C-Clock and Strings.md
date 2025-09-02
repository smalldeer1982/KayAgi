# 题目信息

# Clock and Strings

## 题目描述

There is a clock labeled with the numbers $ 1 $ through $ 12 $ in clockwise order, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)In this example, $ (a,b,c,d)=(2,9,10,6) $ , and the strings intersect.

Alice and Bob have four distinct integers $ a $ , $ b $ , $ c $ , $ d $ not more than $ 12 $ . Alice ties a red string connecting $ a $ and $ b $ , and Bob ties a blue string connecting $ c $ and $ d $ . Do the strings intersect? (The strings are straight line segments.)

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the strings do not intersect, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

## 样例 #1

### 输入

```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES```

# AI分析结果



### 唯一算法分类
几何问题/条件判断

---

### 题解思路与解决难点
**核心思路**：判断两个线段的端点是否分布在对方分割的两个半圆的不同侧。  
**实现关键**：  
1. 将线段端点排序，简化区间判断  
2. 统计另一线段端点是否在区间内  
3. 交替出现模式（如“1212”字符串）可判定相交  

**解决难点**：  
- 环形钟表的区间处理（如 12 到 1 的边界）  
- 需要确保所有可能的交叉情况都被覆盖  

---

### 题解评分（≥4星）
1. **cute_overmind（★★★★★）**  
   - 通过统计点在区间内的数量判断相交，代码简洁高效  
   - 使用 `swap` 统一区间方向，逻辑清晰  
   - 关键代码：  
     ```cpp
     if(a < b) swap(a, b); // 统一区间方向  
     if(c >= b && c <= a) cnt++; // 统计点在区间内的数量  
     if(cnt % 2) cout << "YES"; // 奇数为相交  
     ```

2. **JXR_Kalcium（★★★★）**  
   - 枚举区间内的点统计另一线段的端点数量  
   - 直观展示区间覆盖，易理解  
   - 关键代码：  
     ```cpp
     for(int i=a+1; i<b; ++i) // 遍历区间  
         if(i==c || i==d) bz++;  
     if(bz==1) return YES;  
     ```

3. **L_xcy（★★★★）**  
   - 生成字符序列判断交替模式  
   - 巧妙利用遍历顺序检测交叉  
   - 关键代码：  
     ```cpp
     for(int i=1; i<=12; i++) {  
         if(i==a||i==b) s += '1';  
         if(i==c||i==d) s += '2';  
     }  
     if(s=="1212" || s=="2121") return YES;  
     ```

---

### 最优思路提炼
**关键逻辑**：  
1. **区间排序法**：将线段端点排序后，若另一线段的端点分布在区间内外的不同侧，则相交。  
   ```cpp
   if (a < c && c < b && b < d) || (c < a && a < d && d < b) → YES  
   ```
2. **奇偶计数法**：统计另一线段在区间内的端点数量，奇数个则相交。  
3. **交替模式法**：通过字符串模式匹配判断交叉状态。

**优化技巧**：  
- 使用 `swap` 统一区间方向，避免环形判断  
- 直接遍历钟表数字生成序列，避免复杂几何计算  

---

### 同类型题与算法套路
**通用解法**：  
- **环形区间判断**：将环形结构转化为线性区间处理（如模运算或排序）  
- **线段相交检测**：通过端点分布快速判断相交，避免计算几何  

**推荐题目**：  
1. [P1355 三角形的最大面积](https://www.luogu.com.cn/problem/P1355)  
2. [P2789 直线交点数](https://www.luogu.com.cn/problem/P2789)  
3. [CF1025C 割绳子](https://codeforces.com/problemset/problem/1025/C)  

---

### 个人心得摘录
- **cute_overmind**：通过测试数据发现端点重合问题不影响结果，简化了判断逻辑。  
- **L_xcy**：遍历钟表生成字符串的模式匹配法，灵感来源于观察样例的排列规律。  
- **zzx114514**：条件判断时需注意排序后的区间边界，避免漏判环形情况。

---

### 可视化算法设计
**动画方案**：  
1. **钟表绘制**：  
   - 12个刻度用圆形排列，线段用不同颜色绘制  
   - 高亮当前判断的区间（如红色线段分割的半圆）  

2. **关键步骤演示**：  
   - **步骤1**：绘制线段AB，将钟表分为绿/红两半（动态颜色填充）  
   - **步骤2**：遍历C和D的位置，若在绿/红不同半区，触发相交提示  
   - **步骤3**：显示统计结果（如计数从0→1→1时触发YES）  

**交互设计**：  
- **复古像素风**：  
  - 钟表用16色块表示，线段用8位锯齿线条  
  - 音效：移动指针时播放“哔”声，相交时播放“胜利”音效  
- **自动演示模式**：  
  - AI自动生成随机线段并演示判断流程  
  - 按空格键单步执行，回车键切换自动/手动  

**代码片段（JS伪代码）**：  
```javascript
// 绘制钟表与线段
function drawClock(a, b, c, d) {
    ctx.fillStyle = "#8B0000"; // 复古红
    drawLine(a, b); // 绘制AB线段
    highlightInterval(a, b); // 高亮区间
    // 检查C/D位置
    let cnt = checkPointsInInterval(c, d, a, b);
    if (cnt % 2) playSound("success"); // 奇数次播放音效
}

// 区间高亮逻辑
function highlightInterval(a, b) {
    for (let i = a; i != b; i = i % 12 + 1) {
        drawSegment(i, "rgba(0,255,0,0.3)"); // 绿色半透明
    }
}
```

---

### 完整参考代码
**条件判断法（cute_overmind）**：  
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int a, b, c, d, cnt = 0;
    cin >> a >> b >> c >> d;
    if (a < b) swap(a, b); // 统一为逆时针区间
    cnt += (c >= b && c <= a); // 统计C/D在区间内
    cnt += (d >= b && d <= a);
    cout << (cnt % 2 ? "YES" : "NO") << "\n";
}
int main() {
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
```

---
处理用时：95.04秒