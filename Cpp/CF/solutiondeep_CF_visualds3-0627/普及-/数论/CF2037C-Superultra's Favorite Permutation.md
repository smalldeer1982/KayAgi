# 题目信息

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
-1
1 8 7 3 6 2 4 5```

# AI分析结果



---

## 唯一算法分类
构造

---

## 综合分析与结论

### 核心思路与难点
题目要求构造一个排列，使得任意相邻两数之和为合数。通过数学观察发现：
1. **奇偶分块**：两个奇数相加或两个偶数相加的结果都是偶数（必为合数，除2外）
2. **交界处理**：奇偶分块的交界处需满足奇+偶=合数，最小的奇合数9可由4+5得到
3. **特判n≤4**：此时无法构造满足条件的排列

### 可视化设计思路
1. **分块动画**：左侧区域显示奇数（蓝色方块），右侧显示偶数（绿色方块），中间用黄色高亮显示4和5
2. **步进演示**：按顺序展示奇数块构造 → 插入4/5 → 偶数块构造的过程
3. **音效提示**：成功插入4/5时播放上扬音效，完成构造时播放胜利音效
4. **8位像素风格**：用16色像素画风表示数字块，移动时添加马赛克过渡效果

---

## 题解清单（≥4星）

### 1. ridewind2013（4.5星）
- **亮点**：代码最简练，直接分两次遍历处理奇偶，逻辑清晰
- **关键实现**：先输出奇数（除5），再输出4/5，最后输出偶数（除4）

### 2. K_yuxiang_rose（4星）
- **亮点**：用相反顺序（先偶数后奇数）实现相同逻辑，验证思路灵活性
- **优化点**：代码缩进风格略不统一，但核心逻辑等价

### 3. RAY091016（4星）
- **亮点**：详细数学推导说明，强调分块后的奇偶和性质
- **个人心得**：提到通过DFS暴力验证小数据无解，加强思路可信度

---

## 最优思路与代码实现

### 核心逻辑
```cpp
if(n <=4) 输出-1;
else {
  输出所有奇数（跳过5） → 输出5 → 输出4 → 输出所有偶数（跳过4） 
}
```

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        if(n <=4) cout<<-1<<endl;
        else {
            // 输出除5外的奇数
            for(int i=1; i<=n; i+=2) if(i !=5) cout<<i<<" ";
            // 关键连接点
            cout<<"5 4 ";
            // 输出除4外的偶数
            for(int i=2; i<=n; i+=2) if(i !=4) cout<<i<<" ";
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 相似题目推荐
1. **CF1174D** - 构造特定异或和的数组
2. **P1216** - 数字三角形（构造路径和特性）
3. **CF1325C** - 树边赋值构造互质路径

---

## 可视化算法演示（伪代码）
```javascript
// Canvas初始化
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

// 像素参数
const BLOCK_SIZE = 32;
const COLORS = {
  ODD: '#4A90E2',   // 奇数块
  EVEN: '#50E3C2',  // 偶数块
  KEY: '#F5A623'    // 关键数4/5
};

function drawStep(numbers, highlightIndex) {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  numbers.forEach((num, i) => {
    // 绘制带边框的数字块
    ctx.fillStyle = (i >= highlightIndex[0] && i <= highlightIndex[1]) 
      ? COLORS.KEY : (num % 2 ? COLORS.ODD : COLORS.EVEN);
    ctx.fillRect(i*BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE);
    // 绘制数字（8位像素字体）
  });
}

// 动画序列
animateConstruction(n) {
  let arr = [];
  // 1. 添加奇数（除5）
  for(let i=1; i<=n; i+=2) if(i!=5) arr.push(i);
  // 2. 添加5和4
  arr.push(5,4);
  // 3. 添加偶数（除4） 
  for(let i=2; i<=n; i+=2) if(i!=4) arr.push(i);
  
  // 分步高亮
  setTimeout(() => drawStep(arr, [arr.length-2, arr.length-1]), 1000);
}
```

---

## 复古游戏化设计
1. **音效设计**：
   - 添加数字块时播放8-bit "blip"音效（Web Audio生成方波）
   - 完成构造时播放《超级马里奥》通关音效片段
2. **积分系统**：
   - 正确放置一个数字+10分
   - 成功连接4/5时+50分
3. **自动演示AI**：
   ```javascript
   class ConstructionAI {
     constructor() {
       this.step = 0; // 0:奇数块,1:关键点,2:偶数块
     }
     nextMove() {
       switch(this.step) {
         case 0: return this.addNextOdd();
         case 1: return this.addKeyPair(); 
         case 2: return this.addNextEven();
       }
     }
   }
   ```

---
处理用时：90.99秒