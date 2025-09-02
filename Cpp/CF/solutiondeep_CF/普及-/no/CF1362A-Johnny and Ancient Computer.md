# 题目信息

# Johnny and Ancient Computer

## 题目描述

Johnny has recently found an ancient, broken computer. The machine has only one register, which allows one to put in there one variable. Then in one operation, you can shift its bits left or right by at most three positions. The right shift is forbidden if it cuts off some ones. So, in fact, in one operation, you can multiply or divide your number by $ 2 $ , $ 4 $ or $ 8 $ , and division is only allowed if the number is divisible by the chosen divisor.

Formally, if the register contains a positive integer $ x $ , in one operation it can be replaced by one of the following:

- $ x \cdot 2 $
- $ x \cdot 4 $
- $ x \cdot 8 $
- $ x / 2 $ , if $ x $ is divisible by $ 2 $
- $ x / 4 $ , if $ x $ is divisible by $ 4 $
- $ x / 8 $ , if $ x $ is divisible by $ 8 $

For example, if $ x = 6 $ , in one operation it can be replaced by $ 12 $ , $ 24 $ , $ 48 $ or $ 3 $ . Value $ 6 $ isn't divisible by $ 4 $ or $ 8 $ , so there're only four variants of replacement.

Now Johnny wonders how many operations he needs to perform if he puts $ a $ in the register and wants to get $ b $ at the end.

## 说明/提示

In the first test case, Johnny can reach $ 5 $ from $ 10 $ by using the shift to the right by one (i.e. divide by $ 2 $ ).

In the second test case, Johnny can reach $ 44 $ from $ 11 $ by using the shift to the left by two (i.e. multiply by $ 4 $ ).

In the third test case, it is impossible for Johnny to reach $ 21 $ from $ 17 $ .

In the fourth test case, initial and target values are equal, so Johnny has to do $ 0 $ operations.

In the fifth test case, Johnny can reach $ 3 $ from $ 96 $ by using two shifts to the right: one by $ 2 $ , and another by $ 3 $ (i.e. divide by $ 4 $ and by $ 8 $ ).

## 样例 #1

### 输入

```
10
10 5
11 44
17 21
1 1
96 3
2 128
1001 1100611139403776
1000000000000000000 1000000000000000000
7 1
10 8```

### 输出

```
1
1
-1
0
2
2
14
0
-1
-1```

# AI分析结果

### 题目内容
# Johnny和古老的计算机

## 题目描述
Johnny最近发现了一台古老且损坏的计算机。这台机器只有一个寄存器，允许在其中放入一个变量。然后在一次操作中，可以将其位向左或向右移动最多三个位置。如果右移会截断一些1，则禁止右移。所以，实际上，在一次操作中，可以将数字乘以或除以2、4或8，并且仅当数字能被所选除数整除时才允许除法。

正式地说，如果寄存器中包含正整数x，在一次操作中它可以被替换为以下之一：
 - \(x \cdot 2\)
 - \(x \cdot 4\)
 - \(x \cdot 8\)
 - \(x / 2\)，如果x能被2整除
 - \(x / 4\)，如果x能被4整除
 - \(x / 8\)，如果x能被8整除

例如，如果\(x = 6\)，在一次操作中它可以被替换为12、24、48或3。值6不能被4或8整除，所以只有四种替换变体。

现在Johnny想知道，如果他在寄存器中放入a并最终想得到b，需要执行多少次操作。

## 说明/提示
在第一个测试用例中，Johnny可以通过向右移一位（即除以2）从10得到5。

在第二个测试用例中，Johnny可以通过向左移两位（即乘以4）从11得到44。

在第三个测试用例中，Johnny无法从17得到21。

在第四个测试用例中，初始值和目标值相等，所以Johnny无需进行任何操作。

在第五个测试用例中，Johnny可以通过两次右移从96得到3：一次移2位，另一次移3位（即除以4和除以8）。

## 样例 #1
### 输入
```
10
10 5
11 44
17 21
1 1
96 3
2 128
1001 1100611139403776
1000000000000000000 1000000000000000000
7 1
10 8
```
### 输出
```
1
1
-1
0
2
2
14
0
-1
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是围绕判断a能否通过给定的乘除操作变成b，以及如何以最少操作次数实现。难点在于确定操作的策略和判断不可达的情况。

不同题解在实现方式上有所差异。有的先判断a和b的大小关系，统一成一种情况处理；有的直接判断整除关系和商是否为2的幂次方；还有的将数字拆分为奇数部分和2的幂次方部分来分析。

### 所选的题解
 - **作者：_jimmywang_ (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。先判断a和b的整除关系，若能整除则将b除以a，然后贪心的从最大的8开始除，统计操作次数，最后判断是否能除尽得到1，以此确定能否从a变到b。
    - **核心代码**：
```cpp
while(t--){
    ll a=d,b=d;
    if(a>b)swap(a,b);
    if(b%a)cout<<"-1\n";
    else{
        ll ans=0;
        b/=a;
        while(b%8==0)b/=8,ans++;
        while(b%4==0)b/=4,ans++;
        while(b%2==0)b/=2,ans++;
        if(b!=1)cout<<"-1\n";
        else cout<<ans<<endl;
    }
}
```
 - **作者：SpeedStar (4星)**
    - **关键亮点**：分情况讨论清晰，先处理a和b相等的情况，再统一为a > b的情况，判断a能否被b整除以及商是否为2的整数次幂，最后统计2的幂次中3、2、1的个数得到操作次数。
    - **核心代码**：
```cpp
while (t--) {
    int a, b;
    cin >> a >> b;
    if (a == b) {
        cout << 0 << '\n';
        continue;
    }
    if (a < b) swap(a, b);
    int res = 0;
    int cnt = 0;
    if (a % b == 0) {
        a /= b;
        if (a & (a - 1)) {
            cout << -1 << '\n';
            continue;
        }
        while (a) {
            if (a % 2 == 0) cnt++;
            a /= 2;
        }
        res += cnt / 3;
        cnt %= 3;
        res += cnt / 2;
        cnt %= 2;
        res += cnt;
        cout << res << '\n';
        continue;
    }
    cout << -1 << '\n';
}
```
 - **作者：zjr0330 (4星)**
    - **关键亮点**：思路直接，先交换a和b使a <= b ，判断b能否被a整除，若能则从8开始贪心的除，最后判断是否除尽，逻辑清晰。
    - **核心代码**：
```cpp
while (t--) {
    long long a = 1, b = 1;
    scanf("%lld%lld", &a, &b);
    if (a > b) {
        long long an = b;
        b = a;
        a = an;
    }
    if (b % a) {
        cout << "-1\n";
    } else {
        long long ans = 0;
        b /= a;
        while (b % 8 == 0) {
            b = b / 8, ans++;
        }
        while (b % 4 == 0) {
            b = b / 4, ans++;
        }
        while (b % 2 == 0) {
            b = b / 2, ans++;
        }
        if (b!= 1) {
            printf("-1\n");
        } else {
            printf("%lld\n", ans);
        }
    }
}
```

### 最优关键思路或技巧
贪心策略，优先使用除以8（或乘以8）的操作，因为这样能在每次操作中最大程度改变数字，减少操作次数。同时，通过判断整除关系和商是否为2的幂次方来确定能否从a变到b。

### 可拓展之处
同类型题通常围绕数字的特定变换规则，判断能否从初始状态到达目标状态以及最少操作次数。类似算法套路是先分析操作对数字的影响，确定能否通过操作实现转换，再利用贪心或其他策略寻找最少操作次数。

### 洛谷相似题目
 - P1075 [NOIP2012 普及组] 质因数分解
 - P1028 [NOIP2001 普及组] 数的计算
 - P1004 [NOIP2000 提高组] 方格取数

### 个人心得
无。

---
处理用时：54.52秒