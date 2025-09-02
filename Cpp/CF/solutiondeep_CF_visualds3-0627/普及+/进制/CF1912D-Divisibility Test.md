# 题目信息

# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0```

# AI分析结果



---

**唯一算法分类**：数论

---

**综合分析与结论**  
题目要求在给定基数b和模n时，找到最小的k使得存在特定类型的整除规则。核心思路基于数论中的模运算性质：  
1. **类型1**：当b^k ≡0 (mod n)时，取最后k位。  
2. **类型2**：当b^k ≡1 (mod n)时，k位一组求和。  
3. **类型3**：当b^k ≡-1 (mod n)时，k位一组交替求和。  

**算法流程**：  
- 枚举k从1到n，逐步计算b^k mod n。  
- 若当前余数满足上述任一条件，记录最小k并终止。  
- 若k超过n仍未找到解，则无解。  

**关键难点**：正确理解三种条件对应的数学性质，并高效枚举k值。  

**可视化设计**：  
- **动态演示**：用Canvas展示k的递增和余数变化，颜色标记余数（红/绿/蓝对应三种条件）。  
- **复古风格**：采用8位像素界面，每次k增加时播放“滴”音效，找到解时触发“胜利”音效。  
- **交互控制**：允许用户调整枚举速度，单步观察余数变化。  

---

**题解清单 (≥4星)**  

1. **FFTotoro（4星）**  
   - **亮点**：代码简洁，直接枚举k到n，逻辑清晰。  
   - **代码片段**：  
     ```cpp  
     for(int k=1; k<=n && !f; k++){  
         if((c *= b) %= n, !c) // 类型1条件判断  
         else if(c == 1)       // 类型2条件判断  
         else if(c == n-1)     // 类型3条件判断  
     }  
     ```  

2. **Robin_kool（4星）**  
   - **亮点**：处理模运算时用逐步乘b取模，避免溢出。  
   - **代码片段**：  
     ```cpp  
     now = (now * b) % n;  
     if(now == 0)  // 类型1  
     else if(now == 1) // 类型2  
     else if(now == n-1) // 类型3  
     ```  

---

**核心实现思想**  
- **关键变量**：`now`存储当前b^k mod n的值。  
- **循环逻辑**：每次循环将now乘以b并取模，检查是否满足条件。  

**完整代码（FFTotoro题解）**：  
```cpp  
#include<bits/stdc++.h>  
using namespace std;  
int main(){  
    ios::sync_with_stdio(false);  
    int t; cin>>t;  
    while(t--){  
        int b,n; cin>>b>>n;  
        long long c=1; bool f=false;  
        for(int k=1; k<=n && !f; k++){  
            if((c*=b)%=n, !c) cout<<"1 "<<k<<'\n',f=true;  
            else if(c==1) cout<<"2 "<<k<<'\n',f=true;  
            else if(c==n-1) cout<<"3 "<<k<<'\n',f=true;  
        }  
        if(!f) cout<<"0\n";  
    }  
    return 0;  
}  
```  

---

**类似算法套路**  
- **模运算性质**：如快速幂、循环节问题。  
- **枚举优化**：通过数学性质缩小枚举范围（如k≤n）。  

**推荐题目**  
1. P1226（快速幂）  
2. P1061（模线性方程）  
3. P1313（模运算与组合数）  

---

**复古游戏化动画实现**  
- **像素界面**：显示当前k值和余数，背景为8-bit网格。  
- **音效触发**：  
  - 每次k增加时播放“按键”音效。  
  - 找到解时播放经典FC过关音效。  
- **自动演示**：AI自动步进，速度可调，支持暂停/继续。  

```javascript  
// 伪代码示例：Canvas绘制余数变化  
ctx.fillStyle = '#8B8B8B';  
ctx.fillRect(0, 0, width, height); // 像素背景  
ctx.fillStyle = getColorByRemainder(now); // 根据余数选颜色  
ctx.fillRect(k * 10 % width, 50, 8, 8); // 移动像素块  
if (found) playSound('victory');  
```

---
处理用时：64.67秒