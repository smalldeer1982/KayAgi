# 题目信息

# Phone Number

## 题目描述

Alas, finding one's true love is not easy. Masha has been unsuccessful in that yet. Her friend Dasha told Masha about a way to determine the phone number of one's Prince Charming through arithmancy.

The phone number is divined like that. First one needs to write down one's own phone numbers. For example, let's suppose that Masha's phone number is $ 12345 $ . After that one should write her favorite digit from $ 0 $ to $ 9 $ under the first digit of her number. That will be the first digit of the needed number. For example, Masha's favorite digit is $ 9 $ . The second digit is determined as a half sum of the second digit of Masha's number and the already written down first digit from her beloved one's number. In this case the arithmetic average equals to $ (2+9)/2=5.5 $ . Masha can round the number up or down, depending on her wishes. For example, she chooses the digit $ 5 $ . Having written down the resulting digit under the second digit of her number, Masha moves to finding the third digit in the same way, i.e. finding the half sum the the third digit of her number and the second digit of the new number. The result is $ (5+3)/2=4 $ . In this case the answer is unique. Thus, every $ i $ -th digit is determined as an arithmetic average of the $ i $ -th digit of Masha's number and the $ i-1 $ -th digit of her true love's number. If needed, the digit can be rounded up or down. For example, Masha can get:

 $ 12345 $   $ 95444 $  Unfortunately, when Masha tried dialing the number, she got disappointed: as it turned out, the number was unavailable or outside the coverage area. But Masha won't give up. Perhaps, she rounded to a wrong digit or chose the first digit badly. That's why she keeps finding more and more new numbers and calling them. Count the number of numbers Masha calls. Masha calls all the possible numbers that can be found by the described means of arithmancy, except for, perhaps, her own one.

## 样例 #1

### 输入

```
12345
```

### 输出

```
48
```

## 样例 #2

### 输入

```
09
```

### 输出

```
15
```

# AI分析结果

### 题目内容
# 电话号码

## 题目描述
唉，找到自己的真爱可不容易。玛莎至今仍未成功。她的朋友达莎告诉玛莎一种通过算术占卜来确定自己白马王子电话号码的方法。

电话号码是这样推算的。首先，需要写下自己的电话号码。例如，假设玛莎的电话号码是12345。之后，应该在她号码的第一位数字下面写下她最喜欢的0到9中的数字。这将是所需号码的第一位数字。例如，玛莎最喜欢的数字是9。第二位数字由玛莎号码的第二位数字与已经写下的她爱人号码的第一位数字的和的一半来确定。在这种情况下，算术平均值等于(2 + 9)/2 = 5.5。玛莎可以根据自己的意愿向上或向下取整。例如，她选择数字5。在她号码的第二位数字下面写下结果数字后，玛莎以同样的方式继续寻找第三位数字，即找到她号码的第三位数字与新号码的第二位数字的和的一半。结果是(5 + 3)/2 = 4。在这种情况下答案是唯一的。因此，第i位数字由玛莎号码的第i位数字与她真爱号码的第i - 1位数字的算术平均值确定。如果需要，可以向上或向下取整。例如，玛莎可能得到：
12345 
95444 
不幸的是，当玛莎试着拨打这个号码时，她很失望：结果发现，该号码无法接通或不在覆盖范围内。但玛莎不会放弃。也许，她取整到了错误的数字，或者选错了第一个数字。这就是为什么她不断寻找越来越多的新号码并拨打它们。计算玛莎拨打的号码数量。玛莎拨打通过上述算术占卜方法能找到的所有可能的号码，也许除了她自己的号码。

## 样例 #1
### 输入
```
12345
```
### 输出
```
48
```

## 样例 #2
### 输入
```
09
```
### 输出
```
15
```

### 算法分类
动态规划

### 综合分析与结论
这几道题解均采用动态规划的方法来解决问题。思路核心都是通过定义状态 \(dp_{i,j}\) 来表示前 \(i\) 位且第 \(i\) 位为 \(j\) 的方案数，然后根据题目规则进行状态转移。不同之处在于对是否生成原号码的判断以及状态转移的具体实现方式。

### 所选的题解
- **作者：一扶苏一 (5星)**
  - **关键亮点**：通过递推布尔量 \(flag\) 来判断能否拼出原号码，简化了数位DP中复杂的转移讨论，代码实现简洁高效。
  - **重点代码核心思想**：用 \(f_{i,j}\) 记录方案数，通过刷表法进行状态转移，同时利用 \(flag\) 数组记录每一位是否能与原号码完全相同，最后根据 \(flag[n]\) 判断是否能拼出原号码来计算最终答案。
```cpp
// 核心代码片段
for(rg int i=1;i<n;++i) {
    rg int di=i+1;
    for(rg int j=0;j<10;++j) {
        int _temp=j+MU[di];
        int k=_temp>>1;
        if(_temp&1) frog[di][k]+=frog[i][j],frog[di][k+1]+=frog[i][j];
        else frog[di][k]+=frog[i][j];
        if((MU[i] == j) &&flag[i]) {
            if(MU[di] == k) flag[di]=true;
            else if((_temp&1) && (MU[di] == (k+1))) flag[di]=true;
        }
    }
}
rg ll ans=flag[n]?-1:0;
for(rg int i=0;i<10;++i) ans+=frog[n][i];
```
- **作者：Juanzhang (4星)**
  - **关键亮点**：给出了记搜、填表、刷表三种动态规划的实现方式，全面展示了解题思路，方便读者理解动态规划不同实现的特点。
  - **重点代码核心思想（刷表法为例）**：初始化 \(dp[1]\) 全为1，通过两层循环，根据当前位和前一位的关系进行状态转移，最后累加 \(dp[n]\) 得到方案总数，并判断是否会生成原号码来修正答案。
```cpp
// 核心代码片段（刷表法）
fill(dp[1], dp[1] + 10, 1);
for (int i = 1; i < n; i++) {
    int x = str[i + 1] ^ 48;
    for (int j = 0; j < 10; j++) {
        dp[i + 1][j + x >> 1] += dp[i][j];
        if (j + x & 1) {
            dp[i + 1][j + x + 1 >> 1] += dp[i][j];
        }
    }
}
for (int i = 0; i < 10; i++) {
    ans += dp[n][i];
}
for (int i = 2; i <= n; i++) {
    if (abs(str[i] - str[i - 1]) > 1) {
        break;
    }
    if (i == n) {
        ans--;
    }
}
```
- **作者：kimi0705 (4星)**
  - **关键亮点**：思路清晰，先给出基础的动态规划状态转移方程，再分析新号码是否与原号码相同的条件，逻辑连贯。
  - **重点代码核心思想**：通过循环实现状态转移，根据当前位和前一位的关系更新 \(dp\) 数组，最后通过 \(check\) 函数判断是否会生成原号码来修正答案。
```cpp
// 核心代码片段
for (int i = 1; i < s.size(); i++) {
    for (int j = 0; j <= 9; j++) {
        if (0 <= j * 2 - s[i] + '0' && j * 2 - s[i] + '0' <= 9)
            dp[i][j] += dp[i - 1][j * 2 - s[i] + '0'] ;
        if (0 <= j * 2 - s[i] + '0' + 1 && j * 2 - s[i] + '0' + 1 <= 9)
            dp[i][j] += dp[i - 1][j * 2 - s[i] + '0' + 1] ;
        if (0 <= j * 2 - s[i] + '0' - 1 && j * 2 - s[i] + '0' - 1 <= 9)
            dp[i][j] += dp[i - 1][j * 2 - s[i] + '0' - 1] ;
    }
}
for (int i = 0; i <= 9; i++) ans += dp[s.size() - 1][i];
cout << ans - check();
```

### 最优关键思路或技巧
通过定义合适的状态和状态转移方程解决计数问题，在处理能否生成原号码这一难点时，一扶苏一通过递推布尔量的方式简化了复杂的数位DP转移讨论，是较为巧妙的优化技巧。

### 同类型题或类似算法套路拓展
此类题目属于动态规划中的计数类问题，通常需要根据题目给定的规则定义状态，通过状态转移方程来计算方案数。类似套路还包括根据条件判断是否需要排除某些特殊情况（如本题中排除原号码）。

### 洛谷相似题目推荐
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)

### 个人心得摘录与总结
无。 

---
处理用时：70.36秒