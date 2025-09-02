# 题目信息

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

# AI分析结果



### 唯一算法分类
位运算/数学技巧

---

### 题解思路、算法要点与解决难点
**核心思路**：利用异或运算的性质，通过构造全1二进制数实现最大值。  
**关键步骤**：  
1. **k=1特判**：直接取n本身作为最大值。
2. **k≥2时的构造**：找出n的最高二进制位b，构造全1数 `(1 << (b+1)) - 1`。

**解决难点**：  
- **如何确定全1数的位数**：通过循环右移或左移操作，找到n的最高位b（如n=4的二进制`100`，最高位b=2，构造全1数`111`即`2^3-1=7`）。
- **异或性质的应用**：当存在两个数a和b，使得`a ^ b = S`（全1数），则S为可能的最大值。

---

### 题解评分（≥4星）
1. **BB2655（5星）**：  
   - 思路详细，推导严谨，引用外部资料辅助说明。  
   - 代码简洁高效，直接计算最高位并构造结果。  
2. **SoyTony（4星）**：  
   - 提供数学公式与证明，增强理解。  
   - 代码通过计算对数确定位数，逻辑清晰。  
3. **fisheep（4星）**：  
   - 代码简洁，通过左移构造结果，时间复杂度低。  
   - 注释明确，适合快速理解核心逻辑。  

---

### 最优思路或技巧提炼
1. **位运算构造法**：通过最高位计算全1数 `(1 << (b+1)) - 1`。
2. **特判优化**：k=1时直接取n，避免不必要的计算。
3. **时间复杂度O(logn)**：通过循环移位或对数计算，高效处理大数（n≤1e18）。

---

### 同类型题或类似算法套路
- **最大异或对**：如LeetCode 421，利用Trie树或位运算优化。
- **位构造问题**：通过二进制位操作构造特定数值，如全1数、掩码等。
- **贪心位选择**：按位从高到低选择，最大化结果。

---

### 推荐相似题目
1. [P2114 起床困难综合症](https://www.luogu.com.cn/problem/P2114)  
2. [P3857 彩灯](https://www.luogu.com.cn/problem/P3857)  
3. [P4301 新Nim游戏](https://www.luogu.com.cn/problem/P4301)  

---

### 个人心得摘录
- **注意数据范围**：需使用`long long`防止溢出（BB2655提醒）。  
- **调试技巧**：通过二进制打印验证位运算结果（SoyTony的代码中隐含验证逻辑）。  
- **思维突破**：当k≥2时，仅需两个数即可构造最大值，无需遍历所有可能（fisheep的简洁实现）。  

---

### 可视化与算法演示
**核心算法流程**：  
1. **输入n=4，k=3**：显示二进制`100`。  
2. **寻找最高位**：高亮第三位（值为4）。  
3. **构造全1数**：填充三位为`111`，结果为7。  

**动画设计**：  
- **像素风格**：用8位色块表示二进制位，绿色表示选中位。  
- **步进控制**：逐步右移n，显示当前位数b的变化。  
- **音效提示**：每次移位播放“滴”声，构造完成时播放胜利音效。  

**代码片段（JS）**：  
```javascript
function visualize(n) {
    let b = 0;
    while (n > 0) {
        n >>= 1;
        b++;
        // 在Canvas绘制当前二进制位，高亮最高位
    }
    return (1 << b) - 1;
}
```

---

### 题解核心代码
**BB2655的代码**：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    long long int n,k;
    cin>>n>>k;
    if(k==1) {
        cout<<n;
        return 0;
    }
    long long int b=0;
    for(;n>>b;b++); // 计算最高位位数
    cout<<(1LL<<b)-1;
    return 0;
}
```

**SoyTony的代码**：  
```cpp
ll cnt=0,num=1;
while(1) {
    num<<=1;
    cnt++;
    if(num>n) break;
}
printf("%lld\n", (1LL<<cnt)-1);
```

**fisheep的代码**：  
```cpp
long long ans=1;
while(n) {
    ans<<=1;
    n>>=1;
}
cout<<ans-1;
```

---
处理用时：108.07秒