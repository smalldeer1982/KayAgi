# 题目信息

# [USACO1.1] 贪婪的送礼者 Greedy Gift Givers

## 题目描述

对于一群 $n$ 个要互送礼物的朋友，GY 要确定每个人送出的钱比收到的多多少。在这一个问题中，每个人都准备了一些钱来送礼物，而这些钱将会被平均分给那些将收到他的礼物的人。  

然而，在任何一群朋友中，有些人将送出较多的礼物(可能是因为有较多的朋友)，有些人有准备了较多的钱。  

给出一群朋友，没有人的名字会长于 $14$ 字符，给出每个人将花在送礼上的钱，和将收到他的礼物的人的列表，请确定每个人收到的比送出的钱多的数目。

## 说明/提示

【数据范围】  
$1\le n \le 10$。

题目翻译来自NOCOW。

USACO Training Section 1.1

## 样例 #1

### 输入

```
5
dave
laura
owen
vick
amr
dave
200 3
laura
owen
vick
owen
500 1
dave
amr
150 2
vick
owen
laura
0 2
amr
vick
vick
0 0
```

### 输出

```
dave 302
laura 66
owen -359
vick 141
amr -150
```

# AI分析结果



# [USACO1.1] 贪婪的送礼者 Greedy Gift Givers

## 算法分类
**模拟**

## 题解思路与核心难点
### 核心算法流程
1. **名字映射**：使用 `map<string, int>` 建立名字到金额的映射，解决线性查找的低效问题
2. **金额分配**：
   - 送礼者总支出 = 总金额 - 余数（`money - money % num_recipients`）
   - 每个收礼者增加 `money / num_recipients`
   - 送礼者保留余数 `money % num_recipients`
3. **边界处理**：当 `num_recipients=0` 时跳过分配，避免除零错误

### 关键实现对比
| 方法                | 优点                     | 缺点                  |
|---------------------|--------------------------|-----------------------|
| 结构体+线性查找     | 直观易懂                 | O(n²) 查找效率低      |
| STL map             | O(1) 查找，代码简洁      | 需要理解映射概念      |
| 字典树              | 理论最优时间复杂度       | 实现复杂，小题大做    |

## 题解评分（≥4星）
### 1. BlueArc（★★★★★）
- **亮点**：STL map 实现简洁，处理余数逻辑清晰
- **核心代码**：
```cpp
map<string, int> cnt;
cnt[s] -= num*p;  // 扣除总送出金额
cnt[person] += num; // 收礼者增加金额
```

### 2. w1049（★★★★☆）
- **亮点**：使用 vector 保持输入顺序，map 维护金额
- **关键技巧**：
```cpp
vector<string> id;  // 保持原始顺序
map<string,int> m;   // 金额映射
m[tmp] += money/num; // 分发逻辑
```

### 3. 蒟蒻炒扇贝（★★★★☆）
- **亮点**：详细注释解释余数处理逻辑
- **关键注释**：
```cpp
// 送礼者：嘿嘿，省下来的钱返还到答案数组！
money[x] += (have - l*give);
```

## 最优思路提炼
1. **映射代替查找**：使用 STL map 实现 O(1) 快速定位
2. **余数数学处理**：`total_given = money - (money % num)` 确保整数分配
3. **输入顺序维护**：单独存储名字列表保证输出顺序

## 相似题目推荐
1. P1177 【模板】快速排序（映射思想）
2. P1059 明明的随机数（数据去重与统计）
3. P1305 新二叉树（结构体与树形数据处理）

## 可视化设计（复古像素风格）
### 动画方案
1. **数据结构展示**：
   - 8-bit 风格名字列表横向排列
   - 每个名字下方显示发光金币数（16x16 像素图标）
   
2. **分钱过程演示**：
   - 送礼者名字闪烁黄色
   - 金币图标飞向收礼者位置，伴随 8-bit 音效
   - 余数金币原地旋转后变暗保留

3. **控制面板**：
   - 方向键选择送礼者
   - A键加速动画，B键单步执行
   - 背景音乐：FC《超级马里奥》金币音效改编

### 关键代码片段（Canvas 绘制）
```javascript
// 绘制像素风格名字
ctx.fillStyle = '#8B8B8B';
names.forEach((name, idx) => {
    drawPixelText(name, 30, 50 + idx*40);
});

// 金币飞行动画
animateCoin(fromX, fromY, toX, toY) {
    const coin = new Image();
    coin.src = '8bit-coin.png'; // 16x16 像素素材
    let progress = 0;
    const animate = () => {
        const x = fromX + (toX - fromX)*progress;
        const y = fromY + (toY - fromY)*progress;
        ctx.drawImage(coin, x, y);
        progress += 0.1;
        if(progress < 1) requestAnimationFrame(animate);
    }
}
```

## 完整代码（BlueArc 优化版）
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n, money, num;
    vector<string> names;
    map<string, int> balance;
    
    cin >> n;
    for(int i=0; i<n; ++i) {
        string name;
        cin >> name;
        names.push_back(name);
        balance[name] = 0;
    }
    
    for(int i=0; i<n; ++i) {
        string giver;
        cin >> giver >> money >> num;
        if(num == 0) continue;
        
        int per = money / num;
        balance[giver] -= per * num; // 关键余数处理
        for(int j=0; j<num; ++j) {
            string receiver;
            cin >> receiver;
            balance[receiver] += per;
        }
    }
    
    for(auto& name : names) 
        cout << name << " " << balance[name] << endl;
}
```

---
处理用时：81.32秒