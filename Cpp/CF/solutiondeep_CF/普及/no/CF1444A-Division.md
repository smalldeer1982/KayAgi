# 题目信息

# Division

## 题目描述

Oleg's favorite subjects are History and Math, and his favorite branch of mathematics is division.

To improve his division skills, Oleg came up with $ t $ pairs of integers $ p_i $ and $ q_i $ and for each pair decided to find the greatest integer $ x_i $ , such that:

- $ p_i $ is divisible by $ x_i $ ;
- $ x_i $ is not divisible by $ q_i $ .

 Oleg is really good at division and managed to find all the answers quickly, how about you?

## 说明/提示

For the first pair, where $ p_1 = 10 $ and $ q_1 = 4 $ , the answer is $ x_1 = 10 $ , since it is the greatest divisor of $ 10 $ and $ 10 $ is not divisible by $ 4 $ .

For the second pair, where $ p_2 = 12 $ and $ q_2 = 6 $ , note that

- $ 12 $ is not a valid $ x_2 $ , since $ 12 $ is divisible by $ q_2 = 6 $ ;
- $ 6 $ is not valid $ x_2 $ as well: $ 6 $ is also divisible by $ q_2 = 6 $ .

 The next available divisor of $ p_2 = 12 $ is $ 4 $ , which is the answer, since $ 4 $ is not divisible by $ 6 $ .

## 样例 #1

### 输入

```
3
10 4
12 6
179 822```

### 输出

```
10
4
179```

# AI分析结果

【题目内容】
# 除法

## 题目描述

Oleg最喜欢的科目是历史和数学，而他最喜欢的数学分支是除法。

为了提高他的除法技能，Oleg提出了$t$对整数$p_i$和$q_i$，并为每对整数决定找到最大的整数$x_i$，使得：

- $p_i$能被$x_i$整除；
- $x_i$不能被$q_i$整除。

Oleg非常擅长除法，很快就找到了所有答案，你呢？

## 说明/提示

对于第一对整数，$p_1 = 10$，$q_1 = 4$，答案是$x_1 = 10$，因为它是$10$的最大除数，且$10$不能被$4$整除。

对于第二对整数，$p_2 = 12$，$q_2 = 6$，注意：

- $12$不是一个有效的$x_2$，因为$12$能被$q_2 = 6$整除；
- $6$也不是有效的$x_2$，因为$6$也能被$q_2 = 6$整除。

下一个可用的$p_2 = 12$的除数是$4$，它是答案，因为$4$不能被$6$整除。

## 样例 #1

### 输入

```
3
10 4
12 6
179 822```

### 输出

```
10
4
179```

【算法分类】
数学

【题解分析与结论】
该题的核心在于找到最大的$x$，使得$x$是$p$的因数且$x$不是$q$的倍数。大部分题解都采用了质因数分解的思路，通过分解$q$的质因数，然后调整$p$中对应质因数的次数，使得$x$不满足$q$的倍数条件。主要难点在于如何高效地分解质因数和优化计算过程。

【评分较高的题解】
1. **Zesty_Fox (4星)**
   - **关键亮点**：详细解释了质因数分解的思路，并通过枚举每个质因数来调整$p$的质因数次数，确保$x$不被$q$整除。代码实现清晰，逻辑严谨。
   - **代码核心**：
     ```cpp
     ll ans = 1, tmp = q;
     for(int i = 1; i <= cnt; i++){
         ll cs = 0, res = 1;
         while(tmp % pr[i] == 0) tmp /= pr[i], cs++, res *= pr[i];
         if(!cs) continue;
         res /= pr[i];
         if(p % res == 0){
             ll tmp1 = p; while(tmp1 % pr[i] == 0) tmp1 /= pr[i];
             ans = max(ans, res * tmp1);
         }
     }
     ```

2. **AsunderSquall (4星)**
   - **关键亮点**：通过预处理质数表，优化了质因数分解的效率，并详细解释了如何通过调整质因数次数来确保$x$不被$q$整除。代码结构清晰，注释详细。
   - **代码核心**：
     ```cpp
     for(int i = 1; i <= cnt; i++){
         if(q % prim[i] == 0){
             num[++Cnt] = prim[i];
             CNT[Cnt] = 0;
             while(q % prim[i] == 0){
                 CNT[Cnt]++;
                 q /= prim[i];
             }
         }
     }
     ```

3. **灵茶山艾府 (4星)**
   - **关键亮点**：简洁明了地解释了质因数分解的思路，并通过枚举每个质因数来调整$p$的质因数次数，确保$x$不被$q$整除。代码实现简洁，逻辑清晰。
   - **代码核心**：
     ```go
     for i := int64(2); i*i <= q; i++ {
         e := 0
         for ; q%i == 0; q /= i {
             e++
         }
         if e > 0 {
             c := 0
             for v := p; v%i == 0; v /= i {
                 c++
             }
             v := p
             for ; c >= e; c-- {
                 v /= i
             }
             ans = max(ans, v)
         }
     }
     ```

【最优关键思路或技巧】
- **质因数分解**：通过分解$q$的质因数，调整$p$中对应质因数的次数，确保$x$不被$q$整除。
- **枚举质因数**：枚举每个质因数，计算对应的$x$值，并取最大值作为最终答案。

【可拓展之处】
- 类似的问题可以扩展到多个数的最大公约数或最小公倍数的计算中，质因数分解的思路同样适用。

【推荐题目】
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1069)
3. [P1072 最大公约数](https://www.luogu.com.cn/problem/P1072)

【个人心得】
- **调试经历**：在质因数分解时，需要注意处理质数大于$\sqrt{q}$的情况，否则会导致遗漏。
- **踩坑教训**：在调整质因数次数时，需要确保$x$不被$q$整除，否则会导致错误答案。

---
处理用时：41.13秒