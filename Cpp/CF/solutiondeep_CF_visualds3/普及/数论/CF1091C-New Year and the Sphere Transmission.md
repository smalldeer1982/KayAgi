# 题目信息

# New Year and the Sphere Transmission

## 题目描述

There are $ n $ people sitting in a circle, numbered from $ 1 $ to $ n $ in the order in which they are seated. That is, for all $ i $ from $ 1 $ to $ n-1 $ , the people with id $ i $ and $ i+1 $ are adjacent. People with id $ n $ and $ 1 $ are adjacent as well.

The person with id $ 1 $ initially has a ball. He picks a positive integer $ k $ at most $ n $ , and passes the ball to his $ k $ -th neighbour in the direction of increasing ids, that person passes the ball to his $ k $ -th neighbour in the same direction, and so on until the person with the id $ 1 $ gets the ball back. When he gets it back, people do not pass the ball any more.

For instance, if $ n = 6 $ and $ k = 4 $ , the ball is passed in order $ [1, 5, 3, 1] $ .

Consider the set of all people that touched the ball. The fun value of the game is the sum of the ids of people that touched it. In the above example, the fun value would be $ 1 + 5 + 3 = 9 $ .

Find and report the set of possible fun values for all choices of positive integer $ k $ . It can be shown that under the constraints of the problem, the ball always gets back to the $ 1 $ -st player after finitely many steps, and there are no more than $ 10^5 $ possible fun values for given $ n $ .

## 说明/提示

In the first sample, we've already shown that picking $ k = 4 $ yields fun value $ 9 $ , as does $ k = 2 $ . Picking $ k = 6 $ results in fun value of $ 1 $ . For $ k = 3 $ we get fun value $ 5 $ and with $ k = 1 $ or $ k = 5 $ we get $ 21 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091C/d99b7ec9698661c180178c4296e69ed6a8f083c5.png)In the second sample, the values $ 1 $ , $ 10 $ , $ 28 $ , $ 64 $ and $ 136 $ are achieved for instance for $ k = 16 $ , $ 8 $ , $ 4 $ , $ 10 $ and $ 11 $ , respectively.

## 样例 #1

### 输入

```
6
```

### 输出

```
1 5 9 21
```

## 样例 #2

### 输入

```
16
```

### 输出

```
1 10 28 64 136
```

# AI分析结果


### 💡 Kay的C++算法解析：New Year and the Sphere Transmission 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：`数学因数枚举` + `等差数列求和`  
🗣️ **初步分析**：  
> 解决本题的关键在于发现：传球步长k的有效取值仅与n的约数相关。想象n个玩家围成时钟，每次跳k步相当于指针移动。当k不是n的约数时，路径会重复已有模式。核心流程分两步：  
> 1. **枚举约数**：遍历1到√n，找出所有n的约数（如n=6时约数为1,2,3,6）  
> 2. **等差数列求和**：对每个约数d，计算循环节长度t=n/d，传球序列为1, 1+d, 1+2d,...1+(t-1)d，其和为（首项+末项）×项数/2  
> 可视化设计：采用8位像素风格时钟界面，高亮当前枚举的约数d，用彩色像素块展示传球路径（如d=2时路径1→3→5→1），伴随“叮”音效标记每次跳跃。控制面板支持单步调试和自动播放，速度可调。

---

### 2. 精选优质题解参考  
**题解一（作者：一扶苏一）**  
* **点评**：思路严谨，用裴蜀定理证明只有约数有效；代码规范（set自动去重）；核心亮点是将编号转为0~n-1简化计算，再通过末项修正还原编号和。实践性强，边界处理完整（如√n优化），时间复杂度O(√n)是标准解法。  

**题解二（作者：woshishei）**  
* **点评**：直击本质，快速识别约数与答案的对应关系；代码简洁但包含关键优化（i*i=n去重）。亮点是等差数列公式直接套用：(1 + n - i + 1)*n/i/2 清晰体现首项、末项与项数关系。稍显不足是去重逻辑可优化。  

**题解三（作者：lahlah）**  
* **点评**：解题脉络清晰，用“分鸽”比喻降低理解门槛；代码极简（仅10行），但完整包含枚举约数、求和、排序输出三步骤。亮点是check函数封装求和公式，凸显模块化思维。适合初学者理解核心逻辑。

---

### 3. 核心难点辨析与解题策略  
1. **难点1：如何识别有效k值？**  
   * **分析**：非约数k会导致路径重复（如k=4与k=2在n=6时结果相同）。优质题解通过数学推导（裴蜀定理）或观察发现：有效k必为n的约数。  
   * 💡 **学习笔记**：缩小枚举范围是优化关键！  

2. **难点2：求和公式的构造**  
   * **分析**：序列1, 1+d,...1+(t-1)d中，末项需满足1+(t-1)d ≡1 mod n。优质题解统一用等差数列求和公式：S = [2 + (t-1)d] * t / 2，再通过末项修正处理取模（如题解一加t减n）。  
   * 💡 **学习笔记**：等差数列求和是处理环形序列的利器。  

3. **难点3：避免重复计算**  
   * **分析**：当i与n/i为不同约数时需分别计算（i²≠n）。题解用set或排序后去重确保结果唯一。  
   * 💡 **学习笔记**：容器去重需考虑数据规模（n≤1e9时约数仅O(√n)个）。  

### ✨ 解题技巧总结  
- **数学建模**：将环形问题转化为线性等差数列  
- **因数枚举优化**：只遍历√n范围，i和n/i成对获取  
- **代码健壮性**：用`long long`防溢出，边界特判(i*i==n)  

---

### 4. C++核心代码实现赏析  
**通用核心实现参考**  
```cpp
#include <iostream>
#include <set>
using namespace std;
typedef long long ll;

int main() {
    ll n; cin >> n;
    set<ll> ans;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i != 0) continue;
        ll t1 = n / i, sum1 = (1 + (n - i + 1)) * t1 / 2;
        ll t2 = i, sum2 = (1 + (n - t1 + 1)) * t2 / 2;
        ans.insert(sum1);
        if (i * i != n) ans.insert(sum2);
    }
    for (auto x : ans) cout << x << " ";
}
```
* **说明**：综合优质题解，直接枚举约数并计算两组成对结果（i和n/i），set自动排序去重。  
* **代码解读概要**：  
  1. 枚举约数i（1≤i≤√n）  
  2. 计算约数i对应序列和：项数t1=n/i，和=(首项1+末项(n-i+1))×t1/2  
  3. 计算对称约数n/i的和  
  4. set存储结果并遍历输出  

**题解一片段赏析**  
```cpp
void work(cl s) {
    ll y = n / s;  // 项数
    ll ans = (((s + y * s) * y) >> 1) + y - n; // 求和公式
    ss.insert(ans);
}
```
* **亮点**：位运算优化除2（>>1），末项修正逻辑清晰  
* **学习笔记**：位运算替代除法可提升性能，但需注释说明  

**题解二片段赏析**  
```cpp
ans[++cnt] = (ll)(1 + n - i + 1) * (n/i) / 2;
```
* **亮点**：单行实现求和，公式直白体现首项（1）、末项（n-i+1）、项数（n/i）  
* **学习笔记**：将数学公式直接转化为代码是高效实现的关键  

**题解三片段赏析**  
```cpp
void check(long long x){
    ans[++ sz] = (1 + n - x + 1) * n / x / 2;
}
```
* **亮点**：封装函数提升可读性，变量命名直观（x为公差）  
* **学习笔记**：功能拆解使主逻辑简洁  

---

### 5. 算法可视化：像素动画演示  
**主题**：8-bit像素风“时钟寻宝”  
**核心演示**：  
1. **场景**：像素化圆盘时钟（FC风格），n个等分格子标号1~n  
2. **初始化**：红色像素块标记起点1，控制面板含步进/调速/重置按钮  
3. **枚举约数**：  
   - 高亮当前约数d（如d=3），黄色箭头从1跳至4（伴随“叮”音效）  
   - 显示当前等差数列：1 → 4 → 7 → ...（同步显示公式推导）  
4. **路径完成**：回到起点时播放胜利音效，显示求和结果  
5. **自动模式**：AI自动遍历所有约数（速度可调），不同路径用不同颜色  

**设计细节**：  
- **关键操作音效**：跳跃(8-bit跳跃音)、完成(胜利旋律)  
- **游戏化**：每完成一条路径解锁“成就星星”，积分=路径长度×10  

---

### 6. 拓展练习  
**相似问题**：  
1. 环形约瑟夫问题（约数决定淘汰间隔）  
2. 循环数组的最大公约数遍历  
3. 固定步长遍历矩阵  

**洛谷推荐**：  
1. **P2306** 被污染的牛奶 - 约数性质应用  
2. **P2926** 约数研究 - 强化因数枚举思维  
3. **P1445** 樱花 - 数学约数变形题  

---

### 7. 学习心得  
> **作者经验**：多位作者提到“非约数路径必然重复”，这是缩小枚举范围的关键洞见。  
> **Kay点评**：本题训练数学建模能力——将物理环形问题转化为离散数学特性（约数+数列）。调试时可打印中间约数验证，避免漏算对称因子。  

**结语**：掌握因数枚举与数列求和的组合，即可高效解决此类问题！下次见~ 💪

---
处理用时：110.01秒