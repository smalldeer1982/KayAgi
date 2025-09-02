# 题目信息

# [ABC008B] 投票

## 题目描述

题目大意
某个组织进行了选拔领导人的选举。组织由n人组成，每个人都写了最领导的人物的名字。投票数最多的人的名字就是领袖。如果有多个得票数最多的人物，输出其中一个即可。

## 说明/提示

1<=名字长度<=50


感谢@Andysun06  提供的翻译

## 样例 #1

### 输入

```
4

taro

jiro

taro

saburo```

### 输出

```
taro```

## 样例 #2

### 输入

```
1

takahashikun```

### 输出

```
takahashikun```

## 样例 #3

### 输入

```
9

a

b

c

c

b

c

b

d

e```

### 输出

```
b```

# AI分析结果



## 唯一算法分类  
哈希表（map）

---

## 题解思路与算法要点  
### 核心思路对比  
| 方法类型       | 时间复杂度 | 空间复杂度 | 实现难度 | 核心思路                                                                 |
|----------------|------------|------------|----------|--------------------------------------------------------------------------|
| map实时统计    | O(n)       | O(k)       | ★★       | 输入时用map计数，同时维护当前最大值和对应名字                               |
| 排序后统计平台 | O(nlogn)   | O(n)       | ★★☆      | 先排序，统计连续相同名字的最长平台                                         |
| 结构体暴力统计 | O(n²)      | O(n)       | ★★★      | 手动维护候选名单，每次输入都遍历已有名单判断是否重复                       |
| 哈希+双模数    | O(n)       | O(k)       | ★★★☆     | 自定义哈希函数处理字符串，用双模数避免哈希冲突                             |

### 解决难点  
1. **实时更新最大值**（map方法）：  
   - 在每次输入名字时，`m[a]++`后立即判断是否超过历史最大值，避免了二次遍历  
   - 关键代码：`if (m[a] > maxn) { maxn = m[a]; name = a; }`  

2. **排序边界处理**（排序方法）：  
   - 需要多循环一次（`i <= n+1`）确保最后一段连续名字被统计  
   - 示例代码片段：  
     ```cpp
     for (int i=2; i<=n+1; i++) {
         if (a[i] == a[i-1]) t++;
         else {
             if (t > maxn) { maxn = t; ansn = a[i-1]; }
             t = 1;
         }
     }
     ```

---

## 题解评分（≥4星）  
### 1. 翼德天尊（★★★★☆）  
**亮点**：  
- 单次遍历同时完成统计和最大值更新  
- 代码简洁（仅15行核心逻辑）  
- 实时更新机制避免了二次遍历  

### 2. lzqy_（★★★★）  
**亮点**：  
- 用`string数组`辅助去重，降低迭代器理解门槛  
- 完整演示map与数组的配合使用  
- 明确提示去重的必要性  

### 3. HsKr（★★★★）  
**亮点**：  
- 使用迭代器规范遍历map  
- 代码结构清晰展示map的遍历方式  
- 注释详细解释迭代器操作  

---

## 最优思路提炼  
### 核心技巧  
**实时双维护**：  
```cpp
map<string, int> m;
string name;
int maxn = 0;

for (输入每个名字s) {
    m[s]++;
    if (m[s] > maxn) {  // 实时比较
        maxn = m[s];
        name = s;
    }
}
```
**优势**：  
1. **时间复杂度最优**：O(n) 单次遍历  
2. **空间节省**：仅存储必要候选名字  
3. **处理平局**：自动保留第一个出现的最高票候选  

---

## 同类题目推荐  
1. **P1308 统计单词数**（字符串频率统计）  
2. **P1059 明明的随机数**（排序去重+计数）  
3. **P2550 彩票摇奖**（数字频率匹配）  

---

## 可视化设计  
### 动画方案  
**像素风格演示**：  
```html
<canvas id="voteAnim"></canvas>
<script>
// 初始化参数
const names = ["taro", "jiro", "taro", "saburo"];
const map = new Map();
let maxName = "", maxCount = 0;

function drawFrame() {
    // 绘制当前map状态（8位像素风格）
    ctx.fillStyle = "#2D2D2D";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    // 高亮当前操作的名字（闪烁效果）
    if (currentName) {
        ctx.fillStyle = "#FFD700";
        ctx.fillText(`↑ ${currentName} +1`, xPos, yPos);
    }
    
    // 绘制所有候选名字及票数
    map.forEach((val, key) => {
        ctx.fillStyle = "#FFFFFF";
        ctx.fillText(`${key}: ${val}票`, x, y);
        if (val === maxCount) {
            ctx.fillStyle = "#FF0000"; // 最大值红色高亮
            ctx.fillRect(x-5, y-12, 100, 16);
        }
    });
}

// 音效触发
function playSound(type) {
    if (type === 'update') new Audio('blip.wav').play();
    if (type === 'newMax') new Audio('powerup.wav').play();
}
</script>
```

### 交互功能  
- **步进控制**：按空格键单步执行输入  
- **自动模式**：点击"▶"按钮连续播放（速度可调）  
- **高亮规则**：  
  - 黄色闪烁：当前正在处理的名字  
  - 红色背景：当前最高票候选  
- **音效方案**：  
  - `blip.wav`：每次票数更新  
  - `powerup.wav`：最高票变更时  

---

## 代码实现  
### 翼德天尊题解核心代码  
```cpp
map<string, int> m;
string name;
int maxn = 0;

cin >> n;
for (int i=0; i<n; i++) {
    string a;
    cin >> a;
    m[a]++;
    if (m[a] > maxn) { // 实时比较关键点
        maxn = m[a];
        name = a;
    }
}
cout << name;
```

### 像素动画JS核心片段  
```javascript
function simulateStep() {
    if (step >= names.length) return;
    
    const current = names[step];
    playSound('update');
    
    // 更新map和最大值
    const count = (map.get(current) || 0) + 1;
    map.set(current, count);
    
    if (count > maxCount) {
        maxCount = count;
        maxName = current;
        playSound('newMax');
    }
    
    step++;
    requestAnimationFrame(drawFrame);
}
```

---

## 总结提升  
**关键学习点**：  
- 哈希表（map）在频率统计中的统治级效率  
- 实时更新技巧可扩展到其他极值追踪场景（如实时排行榜）  
- 排序法虽然时间复杂度更高，但在内存受限时可能更优（如数据可分批排序）  

**避坑指南**：  
- 避免在未初始化时访问map值（使用`m[a]++`而非`m[a] = m[a]+1`）  
- 排序法必须处理最后一个连续平台（通过`i <= n+1`循环）  
- 暴力法仅适用于极小数据量（n≤50）

---
处理用时：75.95秒