# 题目信息

# Economy Game

## 题目描述

Kolya is developing an economy simulator game. His most favourite part of the development process is in-game testing. Once he was entertained by the testing so much, that he found out his game-coin score become equal to $ 0 $ .

Kolya remembers that at the beginning of the game his game-coin score was equal to $ n $ and that he have bought only some houses (for $ 1234567 $ game-coins each), cars (for $ 123456 $ game-coins each) and computers (for $ 1234 $ game-coins each).

Kolya is now interested, whether he could have spent all of his initial $ n $ game-coins buying only houses, cars and computers or there is a bug in the game. Formally, is there a triple of non-negative integers $ a $ , $ b $ and $ c $ such that $ a×1234567+b×123456+c×1234=n $ ?

Please help Kolya answer this question.

## 说明/提示

In the first sample, one of the possible solutions is to buy one house, one car and one computer, spending $ 1234567+123456+1234=1359257 $ game-coins in total.

## 样例 #1

### 输入

```
1359257
```

### 输出

```
YES```

## 样例 #2

### 输入

```
17851817
```

### 输出

```
NO```

# AI分析结果



# 中文题目重写
# 经济游戏

## 题目描述

Kolya正在开发一款经济模拟游戏。他最喜欢的开发环节是游戏内测。一次他在测试时发现自己的游戏币分数变成了$0$。

Kolya记得游戏开始时他有$n$游戏币，并且只购买过房屋（每套$1234567$游戏币）、汽车（每辆$123456$游戏币）和电脑（每台$1234$游戏币）。

现在他想知道是否存在某种购买组合恰好花光所有初始的$n$游戏币。即是否存在非负整数$a$、$b$、$c$满足：$a×1234567 + b×123456 + c×1234 = n$？

## 说明/提示

第一个样例中，一种可行方案是购买1套房屋、1辆汽车和1台电脑，总计花费$1359257$游戏币。

## 样例 #1

### 输入
```
1359257
```

### 输出
```
YES
```

## 样例 #2

### 输入
```
17851817
```

### 输出
```
NO
```

---

**算法分类**：枚举

---

**题解分析与结论**

题目要求判断能否用三个不同价格的物品恰好花光n个游戏币。各题解均采用双重循环枚举前两个物品的数量，通过数学计算直接验证第三个物品数量的可行性，将时间复杂度从O(n³)优化至O(n²)。关键优化点在于将第三层循环转换为取模运算判断。

---

**精选题解**

1. **作者：cyffff**（★★★★★）  
   **亮点**：  
   - 清晰的循环边界控制（`n/1234567`确定a的最大值）  
   - 快速取模判断代替第三层循环  
   **代码核心**：  
   ```cpp
   for(LL a=0; a<=n/1234567; a++){
       for(LL b=0; b<=(n-a*1234567)/123456; b++){
           if((n - a*1234567 - b*123456) % 1234 == 0){
               cout << "YES";
               return 0;
           }
       }
   }
   ```

2. **作者：smoothset**（★★★★☆）  
   **亮点**：  
   - 显式定义常量提升可读性  
   - 循环条件合并减少计算量  
   **代码核心**：  
   ```cpp
   for (int i = 0; i * house <= n; i++)
       for (int j = 0; j * car + i * house <= n; j++)
           if ((n - i * house - car * j) % model == 0)
               return !printf("YES");
   ```

3. **作者：orange166**（★★★★☆）  
   **亮点**：  
   - Python实现中及时退出提升效率  
   - 使用整除运算优化循环范围  
   **代码核心**：  
   ```python
   for i in range(0, a // 1234567 +1):
       for j in range (0, (a-i*1234567) // 123456 +1):
           if (a-i*1234567-j*123456) % 1234 == 0:
               print("YES")
               sys.exit(0)
   ```

---

**关键优化技巧**  
- **数学转化**：将三维问题通过模运算降为二维，时间复杂度从O(1e27)优化到O(1e6)  
- **边界剪枝**：通过`n/price`确定枚举上限，避免无效循环  
- **提前终止**：找到解后立即退出，减少冗余计算  

---

**同类题目推荐**  
1. [P1618 三连击](https://www.luogu.com.cn/problem/P1618)  
2. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)  
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)  

---

**题解心得摘录**  
- *cyffff*："双重循环即可过，注意不要漏判余数非负"  
- *smoothset*："O(n³)会超时，必须用数学优化"  
- *BotDand*："枚举时注意初始值必须从0开始"

---
处理用时：128.40秒