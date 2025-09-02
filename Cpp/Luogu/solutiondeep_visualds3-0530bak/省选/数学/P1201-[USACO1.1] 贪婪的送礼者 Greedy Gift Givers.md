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



## 算法分类
无算法分类（纯模拟题）

## 综合分析与结论
### 核心思路
所有题解均采用模拟思路，核心流程为：
1. 建立姓名与金额的映射关系（数组遍历或map）
2. 计算送礼者总支出与接收者收入
3. 处理除数为0的特殊情况
4. 最终计算净收入（收到金额 - 送出金额）

### 解决难点对比
| 题解方案                  | 数据结构        | 关键优化点                  | 难点处理方式               |
|---------------------------|----------------|---------------------------|--------------------------|
| 线性查找数组（Aoki_灏）     | 结构体数组      | 双循环暴力匹配              | 特判除数为0               |
| STL map（BlueArc）         | map<string,int> | O(1)复杂度查找             | 利用map特性直接操作       |
| 结构体+双重标记（大魔鬼灿灿）| 自定义结构体    | 单独记录收支                | 精确计算剩余金额返还      |

### 可视化设计
1. **动画流程设计**：
   - 送礼者高亮显示（红色边框）
   - 钱数流动动画：从送礼者处飞出金币到接收者
   - 余数保留特效：未分配完的金额产生金色粒子效果返回送礼者
2. **交互功能**：
   - 速度调节滑块控制动画速度
   - 单步执行按钮观察每个送礼操作
3. **音效设计**：
   - 金币流动时播放"coin.wav"
   - 除数为0时播放"error.wav" 
   - 完成所有分配时播放"success.mp3"

## 题解评分（≥4星）
### BlueArc（★★★★☆）
- **亮点**：使用map实现O(1)查找，代码简洁清晰
- **核心代码**：
```cpp
map<string,int> cnt;
cnt[s] -= num*p; // 关键操作
```

### 蒟蒻炒扇贝（★★★★☆）
- **亮点**：详细注释解释map用法，包含调试心得
- **心得摘录**："注意，这里有一个坑点...得到22分的好成绩"

### w1049（★★★★☆）
- **亮点**：结合vector保留输入顺序，STL组合使用优雅
- **核心逻辑**：
```cpp
vector<string> id; // 保留原始顺序
map<string,int> m; // 快速查找
```

## 最优技巧提炼
1. **映射加速**：使用map实现姓名→金额的O(1)查找
2. **余数处理**：`送出金额 = 总金额 - 总金额 % 人数`
3. **输入顺序保留**：vector存储原始姓名顺序用于最终输出
4. **防御性编程**：严格判断除数为0的情况

## 同类题目推荐
1. P1179 数字统计（字符串处理）
2. P1308 统计单词数（字符串映射）
3. P1056 排座椅（模拟+排序）

## 核心算法可视化代码（JavaScript片段）
```javascript
// 钱数流动动画
function animateTransfer(sender, receiver, amount) {
  const senderElem = document.getElementById(sender);
  const coin = document.createElement('div');
  coin.className = 'coin-animation';
  coin.textContent = amount;
  
  senderElem.appendChild(coin);
  setTimeout(() => {
    document.getElementById(receiver).appendChild(coin);
    playSound('coin'); // 触发音效
  }, 500);
}

// 8位风格音效
const audioCtx = new (window.AudioContext)();
function play8bitSound(freq) {
  const oscillator = audioCtx.createOscillator();
  oscillator.type = 'square';
  oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

## 复古游戏化设计
1. **像素风格**：使用NES调色板（#6D6D6D背景，#FFFFFF文字）
2. **角色设计**：每个姓名显示为16x16像素角色，钱数用金币图标表示
3. **自动演示**：按Y键启动AI自动分步演示
4. **积分系统**：正确完成一个送礼操作+10分，处理异常情况+20分
5. **音效配置**：
   - 背景音乐：8位风格《俄罗斯方块》remix
   - 正确操作：250Hz方波短音
   - 错误操作：150Hz锯齿波长音

## 关键实现代码（完整版）
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
    
    // 读取姓名并初始化
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
        balance[names[i]] = 0;
    }
    
    // 处理每个送礼者
    for (int i = 0; i < n; ++i) {
        string name;
        int total, num;
        cin >> name >> total >> num;
        
        if (num == 0) continue;
        
        int each = total / num;
        balance[name] -= each * num; // 关键计算
        
        for (int j = 0; j < num; ++j) {
            string receiver;
            cin >> receiver;
            balance[receiver] += each;
        }
    }
    
    // 按输入顺序输出
    for (auto& name : names) {
        cout << name << " " << balance[name] << endl;
    }
    
    return 0;
}
```

---
处理用时：64.27秒