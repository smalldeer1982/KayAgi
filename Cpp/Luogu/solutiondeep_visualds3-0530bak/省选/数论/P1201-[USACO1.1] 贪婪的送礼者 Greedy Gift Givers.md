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



# 算法分类  
**模拟**

---

# 题解思路、算法要点与解决难点  

## **核心逻辑与难点**  
1. **数据结构选择**  
   - **map<string, int>**：将名字映射到金额，快速查找和更新。  
   - **结构体数组**：直接存储每个用户的姓名和金额，通过线性搜索匹配。  
   - **字典树**：优化字符串匹配，但实现复杂度较高，适用于更大规模数据。  

2. **关键步骤**  
   - **送礼者处理**：  
     - 总金额减去平均分配后的总支出（`money -= total / num * num`）。  
     - 剩余未分配的钱返还给送礼者（`money += total % num`）。  
   - **收礼者处理**：每个收礼者增加平均分配的钱。  
   - **边界处理**：当收礼人数为0时，直接跳过除法操作避免运行时错误。  

3. **解决难点**  
   - **除数为0的陷阱**：所有题解均需特判 `num == 0` 的情况。  
   - **剩余金额返还**：通过 `total % num` 计算未分配的钱并返还。  

---

# 题解评分（≥4星）  

1. **BlueArc（5星）**  
   - **亮点**：使用 `map<string, int>` 简化查找逻辑，代码简洁高效，边界处理清晰。  
   - **代码片段**：  
     ```cpp
     cnt[s] -= num * p;  // 计算送礼者净支出
     for (收礼者列表) cnt[person] += num;
     ```

2. **w1049（4.5星）**  
   - **亮点**：结合 `vector` 保持输入顺序，输出时按顺序遍历，避免 `map` 的无序性。  
   - **代码片段**：  
     ```cpp
     vector<string> id;  // 存储原始输入顺序
     m[tmp] -= money;    // 直接操作map
     ```

3. **至成天下（4星）**  
   - **亮点**：双 `map` 分别记录收入和支出，逻辑直观易懂。  
   - **代码片段**：  
     ```cpp
     give[a] += (x / y) * y;   // 记录总支出
     receive[b] += x / y;      // 记录总收入
     ```

---

# 最优思路提炼  
1. **map快速映射**：利用 `map<string, int>` 实现 O(1) 查找，避免线性搜索。  
2. **剩余金额处理**：通过 `总金额 % 人数` 计算未分配部分并返还。  
3. **边界特判**：对 `人数为0` 的情况直接跳过，避免除零错误。  

---

# 类似题目推荐  
1. **P1305 新二叉树**（字符串处理与树结构）  
2. **P1177 快速排序**（模拟与边界处理）  
3. **P1603 斯诺登的密码**（字符串映射与模拟）  

---

# 可视化设计  
## **动画演示方案（Canvas实现）**  
1. **核心流程**：  
   - **送礼者高亮**：红色框标记当前送礼者。  
   - **金额变化**：送礼者金额减少时显示绿色负值，收礼者增加时显示红色正值。  
   - **分钱过程**：用箭头动画表示钱从送礼者流向多个收礼者。  

2. **交互设计**：  
   - **步进控制**：按钮支持暂停/继续/单步执行。  
   - **速度调节**：滑动条控制动画速度（100ms~2s）。  

3. **复古像素风格**：  
   - **8位色彩**：使用FC红白机调色板（#FF0000红、#00FF00绿等）。  
   - **音效**：分钱时播放“金币掉落”音效，错误操作时播放“哔”声。  

4. **代码片段（伪代码）**：  
   ```javascript
   // Canvas绘制送礼者
   ctx.fillStyle = '#FF0000';
   ctx.fillRect(x, y, 50, 50);  // 红色方块表示送礼者

   // 分钱动画
   function animateTransfer(giver, receivers) {
     receivers.forEach(receiver => {
       drawArrow(giver.pos, receiver.pos);  // 绘制箭头
       receiver.money += amount;            // 更新金额
     });
   }
   ```

---

# 个人心得摘录  
- **BlueArc**：“注意判断除数是否为0，否则会RE。”  
- **蒟蒻炒扇贝**：“map的下标可以是string类型，这题用它简化了逻辑。”  
- **kisah**：“剩余的钱要返还，否则会少算22分。”  

---

# 核心代码实现（C++）  
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> names(n);
    map<string, int> balance;
    
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
        balance[names[i]] = 0;
    }
    
    for (int i = 0; i < n; ++i) {
        string giver;
        int total, num;
        cin >> giver >> total >> num;
        
        if (num == 0) continue;
        int avg = total / num;
        balance[giver] -= avg * num;  // 送礼者净支出
        
        for (int j = 0; j < num; ++j) {
            string receiver;
            cin >> receiver;
            balance[receiver] += avg;  // 收礼者收入
        }
    }
    
    for (auto &name : names) {
        cout << name << " " << balance[name] << endl;
    }
    return 0;
}
```  
**核心思想**：通过 `map` 快速更新金额，按原始顺序输出结果，处理除数为0的边界情况。

---
处理用时：68.65秒