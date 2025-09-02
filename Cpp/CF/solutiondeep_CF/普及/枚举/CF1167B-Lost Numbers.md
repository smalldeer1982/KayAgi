# 题目信息

# Lost Numbers

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury guessed some array $ a $ consisting of $ 6 $ integers. There are $ 6 $ special numbers — $ 4 $ , $ 8 $ , $ 15 $ , $ 16 $ , $ 23 $ , $ 42 $ — and each of these numbers occurs in $ a $ exactly once (so, $ a $ is some permutation of these numbers).

You don't know anything about their order, but you are allowed to ask up to $ 4 $ queries. In each query, you may choose two indices $ i $ and $ j $ ( $ 1 \le i, j \le 6 $ , $ i $ and $ j $ are not necessarily distinct), and you will get the value of $ a_i \cdot a_j $ in return.

Can you guess the array $ a $ ?

The array $ a $ is fixed beforehand in each test, the interaction program doesn't try to adapt to your queries.

## 说明/提示

If you want to submit a hack for this problem, your test should contain exactly six space-separated integers $ a_1 $ , $ a_2 $ , ..., $ a_6 $ . Each of $ 6 $ special numbers should occur exactly once in the test. The test should be ended with a line break character.

## 样例 #1

### 输入

```
16
64
345
672```

### 输出

```
? 1 1
? 2 2
? 3 5
? 4 6
! 4 8 15 16 23 42```

# AI分析结果

### 题目中文重写
这是一道交互题。在与测试程序通信时，请记得刷新输出。你可以使用 C++ 中的 `fflush(stdout)`、Java 中的 `system.out.flush()`、Python 中的 `stdout.flush()` 或 Pascal 中的 `flush(output)` 来刷新输出。如果你使用其他编程语言，请查阅其文档。你也可以参考交互题指南：<https://codeforces.com/blog/entry/45307>。

评委猜测了一个由 6 个整数组成的数组 $a$。有 6 个特殊的数字 —— 4、8、15、16、23、42，并且这些数字在 $a$ 中恰好各出现一次（所以，$a$ 是这些数字的某种排列）。

你不知道它们的顺序，但你可以进行最多 4 次询问。在每次询问中，你可以选择两个索引 $i$ 和 $j$（$1 \le i, j \le 6$，$i$ 和 $j$ 不一定不同），然后你将得到 $a_i \cdot a_j$ 的值作为回复。

你能猜出数组 $a$ 吗？

数组 $a$ 在每个测试中是预先确定的，交互程序不会根据你的询问进行调整。

### 题解综合分析与结论
- **思路对比**：多数题解采用询问相邻位置乘积再枚举全排列的思路，如 rui_er、mnesia、Haphyxlos、StudyingFather、a1ioua；wasa855 询问特定位置组合乘积后枚举；moosssi 先确定前两位，再枚举后三位；Link_Space 通过询问确定中间数进而确定三个数，需特判；fmj_123 利用倍数关系分情况处理。
- **算法要点**：核心是利用有限询问获取信息，结合全排列枚举或逻辑推理确定数组。
- **解决难点**：关键在于设计合理询问策略以获取足够信息，同时处理好全排列枚举或逻辑推理中的判断条件。

### 评分较高题解
- **rui_er（5星）**
    - **关键亮点**：思路清晰，先分析错误策略，再引出正确策略并给出唯一性证明，代码简洁易懂。
    - **核心代码**：
```cpp
int a[7] = {-1, 4, 8, 15, 16, 23, 42}, multiple[5];
for(int i=1;i<=4;i++) {
    printf("? %d %d\n", i, i+1);
    fflush(stdout);
    scanf("%d", &multiple[i]);
}
do {
    bool _ = true;
    for(int i=1;i<=4;i++) {
        if(a[i] * a[i+1]!= multiple[i]) {
            _ = false;
            break;
        }
    }
    if(_) {
        printf("! ");
        for(int i=1;i<=6;i++) printf("%d ", a[i]);
        puts("");
        break;
    }
}while(next_permutation(a+1, a+7));
```
- **mnesia（4星）**
    - **关键亮点**：对交互题有详细介绍，思路明确，代码结构清晰，有对输出部分的说明。
    - **核心代码**：
```cpp
int num[7];
int product[5];
int ans[7] = {0, 4, 8, 15, 16, 23, 42};
bool check(int *a) {
    for(int i = 1;i <= 4;i++) {
        if(a[i] * a[i + 1]!= product[i]) {
            return false;
        }
    }
    return true;
}
for(int i = 1;i <= 4;i++) {
    printf("? %d %d", i, i + 1);
    cout << endl;
    scanf("%d", product + i);
}
do {
    if(check(ans)) {
        printf("! %d %d %d %d %d %d", ans[1], ans[2], ans[3], ans[4], ans[5], ans[6]);
        break;
    }
} while(next_permutation(ans + 1, ans + 7));
```
- **StudyingFather（4星）**
    - **关键亮点**：思路简洁明了，直接阐述暴力枚举的方法，代码实现清晰。
    - **核心代码**：
```cpp
int a[15]={0,4,8,15,16,23,42},b[15];
for(int i=1;i<=4;i++) {
    printf("? %d %d\n",i,i+1);
    fflush(stdout);
    scanf("%d",&b[i]);
}
while(1) {
    int flag=1;
    for(int i=1;i<=4;i++)
        if(a[i]*a[i+1]!=b[i]) {
            next_permutation(a+1,a+7);
            flag=0;
            break;
        }
    if(!flag)continue;
    printf("! ");
    for(int i=1;i<=6;i++)
        printf("%d ",a[i]);
    fflush(stdout);
    return 0;
}
```

### 最优关键思路与技巧
- 采用询问相邻位置乘积的策略，能方便获取多个位置的关联信息。
- 利用 `next_permutation` 函数进行全排列枚举，简化代码实现。

### 拓展思路
同类型题多为交互题，需根据有限询问获取信息求解。类似算法套路包括合理设计询问策略、结合枚举或逻辑推理确定答案。

### 洛谷相似题目推荐
- P1126 机器人搬重物
- P1525 关押罪犯
- P1880 石子合并

### 个人心得摘录与总结
- mnesia：原本想通过复杂判断求解，发现代码冗长后改用暴力枚举，提醒我们遇到复杂情况可考虑简单暴力方法。
- a1ioua：强调交互题要注意换行，否则会出错，提醒我们注意交互题格式细节。 

---
处理用时：34.59秒