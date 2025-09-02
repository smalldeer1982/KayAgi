# 题目信息

# Efim and Strange Grade

## 题目描述

Efim just received his grade for the last test. He studies in a special school and his grade can be equal to any positive decimal fraction. First he got disappointed, as he expected a way more pleasant result. Then, he developed a tricky plan. Each second, he can ask his teacher to round the grade at any place after the decimal point (also, he can ask to round to the nearest integer).

There are $ t $ seconds left till the end of the break, so Efim has to act fast. Help him find what is the maximum grade he can get in no more than $ t $ seconds. Note, that he can choose to not use all $ t $ seconds. Moreover, he can even choose to not round the grade at all.

In this problem, classic rounding rules are used: while rounding number to the $ n $ -th digit one has to take a look at the digit $ n+1 $ . If it is less than $ 5 $ than the $ n $ -th digit remain unchanged while all subsequent digits are replaced with $ 0 $ . Otherwise, if the $ n+1 $ digit is greater or equal to $ 5 $ , the digit at the position $ n $ is increased by $ 1 $ (this might also change some other digits, if this one was equal to $ 9 $ ) and all subsequent digits are replaced with $ 0 $ . At the end, all trailing zeroes are thrown away.

For example, if the number $ 1.14 $ is rounded to the first decimal place, the result is $ 1.1 $ , while if we round $ 1.5 $ to the nearest integer, the result is $ 2 $ . Rounding number $ 1.299996121 $ in the fifth decimal place will result in number $ 1.3 $ .

## 说明/提示

In the first two samples Efim initially has grade $ 10.245 $ .

During the first second Efim can obtain grade $ 10.25 $ , and then $ 10.3 $ during the next second. Note, that the answer $ 10.30 $ will be considered incorrect.

In the third sample the optimal strategy is to not perform any rounding at all.

## 样例 #1

### 输入

```
6 1
10.245
```

### 输出

```
10.25
```

## 样例 #2

### 输入

```
6 2
10.245
```

### 输出

```
10.3
```

## 样例 #3

### 输入

```
3 100
9.2
```

### 输出

```
9.2
```

# AI分析结果

### 题目内容重写

#### 题目描述

Efim刚刚收到了他上一次测试的成绩。他在一所特殊学校学习，他的成绩可以是任何正的小数分数。一开始他感到失望，因为他期待着一个更令人愉快的结果。然后，他制定了一个巧妙的计划。每一秒，他都可以要求老师在小数点后的任何位置对成绩进行四舍五入（也可以要求四舍五入到最接近的整数）。

距离休息结束还有$t$秒，所以Efim必须迅速行动。帮助他找出在不超过$t$秒的时间内他能得到的最大成绩。注意，他可以选择不使用所有的$t$秒。此外，他甚至可以选择完全不进行四舍五入。

在这个问题中，使用了经典的四舍五入规则：在将数字四舍五入到第$n$位时，需要查看第$n+1$位。如果它小于$5$，则第$n$位保持不变，而所有后续数字都被替换为$0$。否则，如果第$n+1$位大于或等于$5$，则第$n$位的数字增加$1$（如果这个数字是$9$，则可能会改变其他数字），并且所有后续数字都被替换为$0$。最后，所有末尾的$0$都会被去掉。

例如，如果数字$1.14$被四舍五入到小数点后第一位，结果是$1.1$，而如果我们将$1.5$四舍五入到最接近的整数，结果是$2$。将数字$1.299996121$四舍五入到小数点后第五位，结果是$1.3$。

#### 说明/提示

在前两个样例中，Efim最初有成绩$10.245$。

在第一秒内，Efim可以得到成绩$10.25$，然后在下一秒得到$10.3$。注意，答案$10.30$将被认为是错误的。

在第三个样例中，最优策略是根本不进行任何四舍五入。

#### 样例 #1

##### 输入

```
6 1
10.245
```

##### 输出

```
10.25
```

#### 样例 #2

##### 输入

```
6 2
10.245
```

##### 输出

```
10.3
```

#### 样例 #3

##### 输入

```
3 100
9.2
```

##### 输出

```
9.2
```

### 题解分析与结论

#### 综合分析

该题的核心是通过贪心策略，尽可能在小数点后靠前的位置进行四舍五入，以最大化最终的成绩。由于四舍五入可能会引发连锁反应（即进位后导致更高位的数字也满足四舍五入条件），因此需要在每次操作后检查是否有新的四舍五入机会。

#### 关键思路与技巧

1. **贪心策略**：优先在小数点后靠前的位置进行四舍五入，因为这样可以最大化数值的增长。
2. **连锁反应处理**：每次四舍五入后，检查是否有新的数字满足四舍五入条件，继续进行操作直到次数用尽或无法继续。
3. **细节处理**：需要处理整数部分的进位问题，以及小数部分全为0时的情况。

#### 所选高分题解

##### 题解1：作者：Binary_Lee (5星)

**关键亮点**：
- 通过贪心策略，优先在小数点后靠前的位置进行四舍五入。
- 详细处理了连锁反应和整数部分的进位问题。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
for(int i=1;i<=cx;i++){
    if(x[i]>=5){   //找到第一个可以四舍五入的
        for(int j=i;j>=1;j--){
            if(x[j]>=5) lst=j-1,x[lst]++,t--;  //连锁反应
            if(!t) break;  //次数不够了
        }
        break;
    }
}
if(x[0]){   //向整数进位
    fl=1;
    int tmp=cz;
    z[tmp]++;
    while(z[tmp]>9) z[tmp-1]++,z[tmp]=0,tmp--;  //满10进位
}
```

##### 题解2：作者：When (4星)

**关键亮点**：
- 详细解释了贪心策略的正确性，并处理了整数和小数部分的进位问题。
- 代码中包含了多个细节处理，如最高位进位等。

**核心代码**：
```cpp
for(int i = loc; i <= top; ++ i)
    if(a[i] >= 5){pos = i; break;}
if(pos > 0){
    int pre = 1; pos -= 1; t -= 1;
    for(int i = pos; i >= 1; -- i){
        if(!pre && (!t || i < loc)) break;
        a[i] += pre; pre = 0;
        if(a[i] > 10) pre = 1, a[i] %= 10;
        if(a[i] == 10){
            pre = 1; a[i] %= 10;
            if(i >= loc) pos -= 1;
        } 
        if(a[i] >= 5 && t && i >= loc) pre += 1, pos -= 1, t--;
    }
    if(pre) a[0] = 1;
}
```

##### 题解3：作者：H2O_TX (4星)

**关键亮点**：
- 通过贪心策略，优先在小数点后靠前的位置进行四舍五入。
- 详细处理了整数部分的进位问题，代码简洁明了。

**核心代码**：
```cpp
for(int i=big;i<=n;i++){
    if(a[i]<='4') continue;
    while(t&&i>=big&&a[i]>='5'){
        if(i==big) a[i-2]++;
        else a[i-1]++;
        i--,t--;
    }
    st=i;//记录下最后一位
    break;
}
```

### 扩展思路与推荐题目

#### 扩展思路

- **类似问题**：可以考虑其他涉及贪心策略的数值优化问题，如最小化某个数值、最大化某个数值等。
- **算法套路**：贪心算法在处理数值优化问题时非常有效，尤其是在需要局部最优解的情况下。

#### 推荐题目

1. **洛谷P1007 最小新整数**：通过删除数字来得到最小的新整数，考察贪心策略。
2. **洛谷P1090 合并果子**：通过贪心策略合并果子，考察优先队列的使用。
3. **洛谷P1223 排队接水**：通过贪心策略安排接水顺序，考察排序和贪心算法的结合。

---
处理用时：53.61秒