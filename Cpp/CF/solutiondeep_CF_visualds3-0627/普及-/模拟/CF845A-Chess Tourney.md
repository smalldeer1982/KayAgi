# 题目信息

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# AI分析结果



### 算法分类
贪心算法

### 题解思路与核心难点
**核心逻辑**：将选手按评分排序后，判断前 n 个选手的最大值是否严格小于后 n 个选手的最小值。  
**关键证明**：若排序后第 n 项（前 n 个的最大值） < 第 n+1 项（后 n 个的最小值），则前 n 个选手组成的队伍必然无法战胜后 n 个组成的队伍，反之则可以保证全胜。  
**解决难点**：需理解排序后的分割点即为最优分组方式，且相等时的配对失败风险是核心难点。

### 题解评分（≥4星）
1. **ShineEternal（5星）**  
   - 代码最简，直接通过排序后比较分割点  
   - 明确注释贪心思想  
   - 样例处理清晰（如排序范围到 2n+1）

2. **Soshine_溯闪（4星）**  
   - 详细解释分组逻辑与贪心证明  
   - 强调相等情况的处理  
   - 变量命名规范，可读性较强

3. **Elma_（4星）**  
   - 提供数学证明与等价的判断条件分析  
   - 代码注释详细，逻辑分层明确  
   - 包含调试案例辅助理解

### 最优思路提炼
1. **排序分割法**：排序后只需比较分割点 a[n] 与 a[n+1]  
2. **严格不等式判断**：必须满足 a[n] < a[n+1]（若用 != 需确保数组已排序）  
3. **反证法验证**：若存在任意配对失败可能，则分割点不成立

### 类似算法套路
- **中位分割**：如「快速选择」中通过中位数划分数据  
- **边界约束**：如区间调度问题中通过端点排序确定最优解

### 推荐题目
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）  
2. P1223 排队接水（排序+时间计算）  
3. P1106 删数问题（贪心+单调栈）

### 个人心得摘录
> - **Nivi**：第一次提交忘记排序，提醒了排序在贪心中的基础作用  
> - **王炸拆开打**：通过两种条件对比发现排序后 != 与 < 的等价性  
> - **Fat_Fish**：通过 3,3,4,4 的案例理解相等时的配对失败风险

---

### 可视化设计（核心算法演示）
**动画方案**：  
1. **排序过程**：数组元素以像素块上升动画展示排序，每步高亮交换元素  
2. **分割比较**：  
   - 用红色标出第 n 项，绿色标出第 n+1 项  
   - 比较时触发闪烁效果，若红 < 绿则播放胜利音效  
3. **自动演示**：  
   - 支持调节排序速度（0.5x~3x）  
   - 单步模式可暂停观察分割点数值  

**复古风格**：  
- **8-bit 音效**：排序时播放电子合成音，成功/失败用不同音阶提示  
- **像素绘制**：数组元素用 16x16 像素块表示，数值以点阵字体显示  
- **关卡积分**：每通过一个测试案例解锁新速度档位，失败扣分  

**代码片段（Canvas 绘制）**  
```javascript
// 绘制排序动画（伪代码）
function drawArray(ctx, arr, highlightIdx) {
  ctx.fillStyle = "#000";
  ctx.fillRect(0, 0, W, H); 
  arr.forEach((val, i) => {
    if (i === n || i === n+1) { // 高亮分割点
      ctx.fillStyle = (i === n) ? "#FF0000" : "#00FF00";
    } else {
      ctx.fillStyle = "#FFF"; 
    }
    drawPixelBlock(ctx, i*16, H - val*4, 16, val*4);
  });
}
```

---

### 题解代码（ShineEternal）
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[210];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) scanf("%d",&a[i]);
    sort(a+1,a+2*n+1); // 关键排序
    printf(a[n]<a[n+1]?"YES\n":"NO\n"); // 贪心比较
    return 0;
}
```

---
处理用时：196.24秒