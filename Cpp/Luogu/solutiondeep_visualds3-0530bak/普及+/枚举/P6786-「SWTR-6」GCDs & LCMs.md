# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果



## 算法分类
数学推导 + 贪心

## 综合分析与结论
### 核心思路
题目要求构造满足特定条件的子序列，其数学本质为：对于任意非最大值的元素，必存在另一个元素与其构成2:3的比例关系。通过严格数学推导可得，所有合法子序列去重排序后必然构成公比3/2的等比数列。

### 解决难点
1. **数学推导**：将原式转化为(x-1)(y-1)=2的形式，得到比例关系x:y=2:3  
2. **高效遍历**：通过排序+哈希表/二分查找快速判断数列中的连续元素是否存在  
3. **去重处理**：统计每个数值的出现次数，避免重复计算  

### 可视化设计
1. **动画方案**：  
   - 将数组元素按大小排列为像素方块，初始灰色  
   - 选中起点元素时变为黄色，沿3/2链逐级高亮后续元素（绿色箭头连接）  
   - 每个方块显示数值和出现次数，右侧实时更新当前链总和  
   - 无效分支（如奇数值无法继续）用红色标记并播放低沉音效  

2. **复古游戏化**：  
   - 8位风格背景音乐（类似《超级玛丽》地下关BGM）  
   - 元素选中时播放《塞尔达传说》解谜成功音效  
   - 使用Canvas绘制像素化数值链条，点击元素触发自动扩展  

## 题解清单 (≥4星)
1. **Alex_Wei（五星）**  
   - 官方题解，推导严谨，代码简洁高效  
   - 核心代码仅用map标记已访问元素，时间复杂度O(n log n)  
   - 关键亮点：将数学结论直接转化为贪心遍历  

2. **Konnyaku_LXZ（四星半）**  
   - 提供完整的数学证明过程，适合初学者理解  
   - 代码实现采用结构体存储去重后的数值和频次  
   - 亮点：使用二分查找代替map，减少常数时间  

3. **Rubidium_Chloride（四星）**  
   - 博客风格解析，包含详细的后记与调试建议  
   - 代码实现map与结构体混合使用  
   - 亮点：处理重复元素时采用指针跳跃技巧  

## 核心代码实现
```cpp
// Alex_Wei 题解核心代码
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
map<int, int> mp;
int n, a[N];
long long ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++; // 统计频次
    }
    sort(a + 1, a + n + 1); // 关键排序
    
    for (int i = 1; i <= n; i++) {
        long long tmp = a[i], cnt = 0;
        while (mp[tmp]) { // 沿3/2链扩展
            cnt += tmp * mp[tmp];
            mp[tmp] = 0; // 标记已访问
            if (tmp % 2) break;
            tmp = tmp / 2 * 3; // 计算下一项
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
```

## 同类型题推荐
1. **P1895 数字序列**（等比数列构造）  
2. **P1445 樱花**（分数分解与数学推导）  
3. **P1102 A-B数对**（哈希表统计频次）  

## 个人心得摘录
> "通过打表发现数列规律是竞赛中的重要技巧。当数学推导卡顿时，构造小数据观察比例关系往往能突破瓶颈。" —— lndjy  
> "将map访问标记与数值计算分离，既保证了时间复杂度，又避免了复杂的数据结构嵌套。" —— SymphonyOfEuler  

## 复古像素化演示方案
### 实现要点
1. **Canvas初始化**：  
   ```javascript
   const canvas = document.getElementById("pixel-canvas");
   const ctx = canvas.getContext('2d');
   ctx.imageSmoothingEnabled = false; // 保持像素风格
   ```

2. **元素绘制**：  
   ```javascript
   function drawNumberBlock(x, y, num, count, color) {
       ctx.fillStyle = color; // 黄/绿/红
       ctx.fillRect(x*50, y*50, 48, 48); // 像素方块
       ctx.fillStyle = 'black';
       ctx.font = '8px "Press Start 2P"'; // 复古字体
       ctx.fillText(`${num}×${count}`, x*50+2, y*50+12);
   }
   ```

3. **音效触发**：  
   ```javascript
   const successSound = new Audio('data:audio/wav;base64,UklGRl9...'); // 成功音效
   function playSuccess() {
       successSound.currentTime = 0;
       successSound.play();
   }
   ```

### 自动演示逻辑
```javascript
let currentIndex = 0;
function autoPlay() {
    if (currentIndex >= sortedArray.length) return;
    
    let num = sortedArray[currentIndex];
    let chain = buildChain(num); // 构造3/2链
    highlightChain(chain); // 高亮动画
    updateMaxSum(chain); // 更新最大值显示
    
    currentIndex++;
    setTimeout(autoPlay, 1000); // 每秒步进
}
```

通过这种设计，学习者可直观观察每个候选链的构建过程，理解贪心策略为何能求得最优解。复古元素与音效增强了学习过程的趣味性，而单文件实现保证了易用性。

---
处理用时：92.33秒