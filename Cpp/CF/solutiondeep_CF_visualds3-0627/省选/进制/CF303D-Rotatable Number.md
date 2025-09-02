# 题目信息

# Rotatable Number

## 题目描述

Bike is a smart boy who loves math very much. He invented a number called "Rotatable Number" inspired by $ 142857 $ .

As you can see, $ 142857 $ is a magic number because any of its rotatings can be got by multiplying that number by $ 1,2,...,6 $ (numbers from one to number's length). Rotating a number means putting its last several digit into first. For example, by rotating number $ 12345 $ you can obtain any numbers: $ 12345,51234,45123,34512,23451 $ . It's worth mentioning that leading-zeroes are allowed. So both $ 4500123 $ and $ 0123450 $ can be obtained by rotating $ 0012345 $ . You can see why $ 142857 $ satisfies the condition. All of the $ 6 $ equations are under base $ 10 $ .

- $ 142857·1=142857 $ ;
- $ 142857·2=285714 $ ;
- $ 142857·3=428571 $ ;
- $ 142857·4=571428 $ ;
- $ 142857·5=714285 $ ;
- $ 142857·6=857142 $ .

Now, Bike has a problem. He extends "Rotatable Number" under any base $ b $ . As is mentioned above, $ 142857 $ is a "Rotatable Number" under base $ 10 $ . Another example is $ 0011 $ under base 2. All of the $ 4 $ equations are under base $ 2 $ .

- $ 0011·1=0011 $ ;
- $ 0011·10=0110 $ ;
- $ 0011·11=1001 $ ;
- $ 0011·100=1100 $ .

So, he wants to find the largest $ b $ $ (1&lt;b&lt;x) $ so that there is a positive "Rotatable Number" (leading-zeroes allowed) of length $ n $ under base $ b $ .

Note that any time you multiply a rotatable number by numbers from 1 to its length you should get a rotating of that number.

## 样例 #1

### 输入

```
6 11
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 8
```

### 输出

```
-1
```

# AI分析结果



---

## **算法分类**  
数论 (原根、质数判定)

---

## **综合分析与结论**  
**核心思路**：  
当且仅当 `n+1` 是质数且 `b` 是其原根时，存在长度为 `n` 的 Rotatable Number。需从大到小遍历 `b<x` 找到最大原根。

**解决难点**：  
1. **数学建模**：将循环数的旋转特性转化为模运算与原根问题。  
2. **原根判定**：快速验证 `b` 是否为质数 `p=n+1` 的原根，需分解 `p-1` 的质因数并检验 `b^{(p-1)/d} ≠1 (mod p)`。  

**可视化设计**：  
- **动画流程**：  
  1. 高亮 `n+1`，判断其是否为质数（红色表示非质数，绿色为质数）。  
  2. 倒序遍历 `b`，对每个 `b` 分解质因数并快速幂检验，用进度条展示计算过程。  
  3. 命中原根时，像素风格爆炸特效 + 上扬音效；遍历结束无解则播放失败音效。  
- **复古元素**：  
  - 8-bit 字体显示 `b` 的遍历过程，用网格表示质因数分解结果。  
  - 背景音乐为低循环芯片音乐，关键步骤触发“哔”声。  

---

## **题解清单 (4星以上)**  
1. **ACAね（4星）**  
   - **亮点**：结合分数循环节推导，代码简洁高效，直接调用快速幂。  
   - **代码片段**：  
     ```cpp  
     bool check(long long k) {  
         for (long long i=1; i*i<=n; i++)  
             if (n%i == 0) {  
                 if (i < n && ksm(k,i) == 1) return false;  
                 if (i!=1 && ksm(k,n/i) == 1) return false;  
             }  
         return true;  
     }  
     ```  
2. **lzytag（4星）**  
   - **亮点**：严格数学证明 `T=n+1`，代码逻辑清晰，预处理质数优化原根判定。  

---

## **最优思路提炼**  
1. **质数判定**：若 `n+1` 非质数，直接输出 `-1`。  
2. **原根判定**：对 `p=n+1`，检查所有 `b` 是否满足对 `p-1` 的每个质因数 `d`，`b^{(p-1)/d} ≠1 (mod p)`。  

**关键代码**：  
```cpp  
bool is_primitive_root(int b, int p, vector<int>& factors) {  
    for (int d : factors)  
        if (qpow(b, (p-1)/d, p) == 1)  
            return false;  
    return true;  
}  
```

---

## **同类题型与套路**  
- **原根应用**：判断/构造某质数的原根（如 POJ 1284）。  
- **循环数问题**：与分数展开的循环节长度相关。  

---

## **推荐题目**  
1. [POJ 1284] Primitive Roots（原根计数）  
2. [洛谷 P1092] 虫食算（数论与搜索）  
3. [Codeforces 1025B] Weakened Common Divisor（质因数分解）  

---

## **个人心得摘录**  
> “昨天学了欧拉定理今天考原根，老师的良心呢” —— 调试中对数学推导的深刻理解是关键。  

---

## **可视化代码片段 (JS)**  
```javascript  
// 像素动画：原根判定过程  
function drawPixel(b, result) {  
    ctx.fillStyle = result ? '#00FF00' : '#FF0000';  
    ctx.fillRect(b * 10 % 300, Math.floor(b / 30) * 10, 8, 8);  
}  

// 播放音效  
function playSound(effect) {  
    const sfx = { pass: [,,,[0.5]], fail: [,,,[0.2]] };  
    new AudioContext().decodeAudioData(sfx[effect], (buffer) => {  
        const source = audioCtx.createBufferSource();  
        source.buffer = buffer;  
        source.connect(audioCtx.destination);  
        source.start();  
    });  
}  
```

---
处理用时：63.23秒