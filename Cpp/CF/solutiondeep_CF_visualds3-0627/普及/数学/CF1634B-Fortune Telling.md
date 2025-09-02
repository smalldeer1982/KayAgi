# 题目信息

# Fortune Telling

## 题目描述

Haha, try to solve this, SelectorUnlimited!

— antontrygubO_o



Your friends Alice and Bob practice fortune telling.

Fortune telling is performed as follows. There is a well-known array $ a $ of $ n $ non-negative integers indexed from $ 1 $ to $ n $ . The tellee starts with some non-negative number $ d $ and performs one of the two operations for each $ i = 1, 2, \ldots, n $ , in the increasing order of $ i $ . The possible operations are:

- replace their current number $ d $ with $ d + a_i $
- replace their current number $ d $ with $ d \oplus a_i $ (hereinafter $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Exclusive_or))

Notice that the chosen operation may be different for different $ i $ and for different tellees.

One time, Alice decided to start with $ d = x $ and Bob started with $ d = x + 3 $ . Each of them performed fortune telling and got a particular number in the end. Notice that the friends chose operations independently of each other, that is, they could apply different operations for the same $ i $ .

You learnt that either Alice or Bob ended up with number $ y $ in the end, but you don't know whose of the two it was. Given the numbers Alice and Bob started with and $ y $ , find out who (Alice or Bob) could get the number $ y $ after performing the operations. It is guaranteed that on the jury tests, exactly one of your friends could have actually gotten that number.

Hacks

You cannot make hacks in this problem.

## 说明/提示

In the first test case, Alice could get $ 9 $ using the following operations: $ 7 + 2 = 9 $ .

In the second test case, Alice could get $ 2 $ using this operations: $ (0 + 1) \oplus 3 = 2 $ .

In the third test case, Bob started with $ x+3 = 0+3=3 $ and could get $ 1 $ this way: $ (((3 + 1) + 2) \oplus 3) \oplus 4 = 1 $ .

## 样例 #1

### 输入

```
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000```

### 输出

```
Alice
Alice
Bob
Alice```

# AI分析结果



# 数论

## 综合分析与结论

**核心思路**：利用加法与异或操作在奇偶性上的等价性，将问题简化为奇偶性判断。  
**关键公式**：  
对于任意整数 a, b，有：  
$$(a + b) \equiv (a \oplus b) \mod 2$$  
此公式表明，无论选择加法还是异或，结果的奇偶性相同。

**推导过程**：  
1. Alice 初始值 x 与 Bob 的 x+3 奇偶性必然不同（3 为奇数）。  
2. 每次操作对奇偶性的影响仅取决于当前元素的奇偶性：  
   - 偶数元素不影响奇偶性  
   - 奇数元素会翻转当前奇偶性  
3. 最终结果的奇偶性由初始奇偶性和所有元素的奇偶性异或和决定。

**解决难点**：  
通过数学观察发现操作选择的无关性，将 O(2^n) 的暴力搜索优化为 O(n) 的奇偶性计算。

---

## 题解清单（≥4星）

### 1. Rnfmabj（★★★★★）
- **亮点**：直接异或处理奇偶性，代码简洁高效。  
- **关键代码**：  
  ```cpp
  for(ll i=1;i<=n;i++) x ^= R&1;  // 异或处理奇偶性
  if(!x^y) cout<<"Alice"<<endl;    // 奇偶性匹配判断
  ```

### 2. 8atemak1r（★★★★☆）
- **亮点**：逻辑清晰，代码可读性强。  
- **关键代码**：  
  ```cpp
  for(int i=1;i<=n;i++) a ^= tmp;  // 累计异或奇偶性
  if((a&1) == (y&1)) cout<<"Alice";
  ```

### 3. cyrxdzj（★★★★☆）
- **亮点**：统计奇数数量，数学等价性清晰。  
- **关键代码**：  
  ```cpp
  temp += (k%2);                   // 统计奇数数量奇偶性
  if(temp == (x-y)%2) cout<<"Alice";
  ```

---

## 最优思路提炼

**核心技巧**：  
1. **奇偶性等价**：将加法和异或统一为奇偶性翻转操作。  
2. **累计异或**：用异或运算累计奇偶性变化，替代暴力枚举。  
3. **模运算优化**：仅保留奇偶性信息，避免大数运算。

**代码实现思想**：  
```cpp
int s = x % 2;
for (int num : a) s ^= (num % 2);
return (s == y % 2) ? "Alice" : "Bob";
```

---

## 类似题目推荐

1. **CF1722G. Even-Odd XOR**  
   （利用奇偶性构造异或序列）

2. **P1462 通往奥格瑞玛的道路**  
   （结合奇偶性判断路径可行性）

3. **AT_abc231_g Balls in Boxes**  
   （概率问题中的奇偶性应用）

---

## 可视化设计（复古像素风格）

**动画方案**：  
1. **初始状态**：显示 Alice (x) 和 Bob (x+3) 的像素小人，头顶显示二进制末位（0/1）。  
2. **处理元素**：每个数组元素以像素方块形式下落，奇数元素发红光，偶数发蓝光。  
3. **奇偶翻转**：每遇到奇数元素，角色头顶数字闪烁翻转，播放8-bit音效。  
4. **最终对决**：对比两人最终奇偶性与 y 的像素标志，匹配者放烟花特效。

**交互设计**：  
- 方向键控制单步执行速度  
- 空格键触发自动推导模式（AI自动计算奇偶性）  
- 按 F 键播放胜利音效（8-bit 小调）

---

**总结**：通过数学观察将复杂操作简化为奇偶性判断，是数论在算法中的经典应用。掌握此类技巧可大幅提升对位运算问题的分析能力。

---
处理用时：104.85秒