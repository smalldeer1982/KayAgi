# 题目信息

# Divide The Students

## 题目描述

A group of students has recently been admitted to the Faculty of Computer Sciences at the Berland State University. Now the programming teacher wants to divide them into three subgroups for practice sessions.

The teacher knows that a lot of programmers argue which language is the best. The teacher doesn't want to hear any arguments in the subgroups, so she wants to divide the students into three subgroups so that no pair of students belonging to the same subgroup want to argue.

To perform this division, the teacher asked each student which programming language he likes. There are $ a $ students who answered that they enjoy Assembler, $ b $ students stated that their favourite language is Basic, and $ c $ remaining students claimed that C++ is the best programming language — and there was a large argument between Assembler fans and C++ fans.

Now, knowing that Assembler programmers and C++ programmers can start an argument every minute, the teacher wants to divide the students into three subgroups so that every student belongs to exactly one subgroup, and there is no subgroup that contains at least one Assembler fan and at least one C++ fan. Since teaching a lot of students can be difficult, the teacher wants the size of the largest subgroup to be minimum possible.

Please help the teacher to calculate the minimum possible size of the largest subgroup!

## 说明/提示

Explanation of the answers for the example $ 1 $ :

1. The first subgroup contains $ 3 $ Assembler fans and $ 2 $ Basic fans, the second subgroup — $ 5 $ C++ fans, the third subgroup — $ 2 $ C++ fans and $ 3 $ Basic fans.
2. The first subgroup contains $ 4 $ Assembler fans, the second subgroup — $ 6 $ Basic fans, the third subgroup — $ 2 $ Basic fans and $ 4 $ C++ fans.
3. The first subgroup contains all Assembler fans, the second subgroup — all Basic fans, the third subgroup — all C++ fans.
4. The first subgroup contains all Assembler fans, the second subgroup — all Basic fans, the third subgroup — all C++ fans.
5. The first subgroup contains $ 12 $ Assembler fans and $ 2 $ Basic fans, the second subgroup — $ 1 $ Assembler fan and $ 13 $ Basic fans, the third subgroup — $ 7 $ Basic fans and $ 7 $ C++ fans.

## 样例 #1

### 输入

```
5
3 5 7
4 8 4
13 10 13
1000 1000 1000
13 22 7
```

### 输出

```
5
6
13
1000
14
```

## 样例 #2

### 输入

```
5
1 3 4
1000 1000 1
4 1 2
325 226 999
939 861 505
```

### 输出

```
3
667
3
517
769
```

# AI分析结果

### 中文重写题目内容

#### 题目描述

一群学生最近被录取到Berland州立大学的计算机科学学院。现在，编程老师希望将他们分成三个小组进行实践课程。

老师知道很多程序员会争论哪种语言是最好的。老师不希望在小组成员之间听到任何争论，因此她希望将学生分成三个小组，使得没有一对属于同一小组的学生会争论。

为了进行这种划分，老师询问了每个学生他们喜欢的编程语言。有 $a$ 名学生回答他们喜欢汇编语言，$b$ 名学生表示他们最喜欢的语言是Basic，剩下的 $c$ 名学生声称C++是最好的编程语言——汇编语言爱好者和C++爱好者之间发生了激烈的争论。

现在，老师知道汇编语言程序员和C++程序员每分钟都可能开始争论，因此她希望将学生分成三个小组，使得每个学生恰好属于一个小组，并且没有任何小组包含至少一个汇编语言爱好者和至少一个C++爱好者。由于教授大量学生可能很困难，老师希望最大小组的规模尽可能小。

请帮助老师计算最大小组的最小可能规模！

#### 说明/提示

样例1的答案解释：

1. 第一个小组包含3名汇编语言爱好者和2名Basic爱好者，第二个小组包含5名C++爱好者，第三个小组包含2名C++爱好者和3名Basic爱好者。
2. 第一个小组包含4名汇编语言爱好者，第二个小组包含6名Basic爱好者，第三个小组包含2名Basic爱好者和4名C++爱好者。
3. 第一个小组包含所有汇编语言爱好者，第二个小组包含所有Basic爱好者，第三个小组包含所有C++爱好者。
4. 第一个小组包含所有汇编语言爱好者，第二个小组包含所有Basic爱好者，第三个小组包含所有C++爱好者。
5. 第一个小组包含12名汇编语言爱好者和2名Basic爱好者，第二个小组包含1名汇编语言爱好者和13名Basic爱好者，第三个小组包含7名Basic爱好者和7名C++爱好者。

#### 样例 #1

##### 输入

```
5
3 5 7
4 8 4
13 10 13
1000 1000 1000
13 22 7
```

##### 输出

```
5
6
13
1000
14
```

#### 样例 #2

##### 输入

```
5
1 3 4
1000 1000 1
4 1 2
325 226 999
939 861 505
```

##### 输出

```
3
667
3
517
769
```

### 算法分类
贪心

### 题解分析与结论

#### 题解1：_Violet_Evergarden
- **思路**：通过分类讨论，根据不同情况计算最大小组的最小可能规模。主要思路是将Basic学生分配到其他两组，使得汇编语言和C++学生不在一起。
- **难点**：需要处理多种情况，确保计算正确。
- **评分**：4星
- **关键亮点**：分类讨论清晰，代码简洁。
- **核心代码**：
```cpp
if(a>=b&&b>=c){
    if((a+1)/2>=(b+c)){
        cout<<(a+1)/2<<endl;
    }
    else{
        cout<<(a+b+c+2)/3<<endl;
    }
    continue;
}
```

#### 题解2：postpone
- **思路**：枚举将Basic学生分配到汇编语言和C++学生中的数量，计算每种情况下的最大小组规模，取最小值。
- **难点**：需要枚举所有可能的分配方式。
- **评分**：4星
- **关键亮点**：枚举思路清晰，代码易于理解。
- **核心代码**：
```cpp
int ans = 1e9;
for (int i = 0; i <= b; i++) {
    int u = a + i;
    int v = c + b - i;
    if (u < v) {
        swap(u, v);
    }
    int t = u / 2 + (u % 2);
    t = max(t, v);
    ans = min(ans, t);
}
cout << ans << "\n";
```

#### 题解3：LaDeX
- **思路**：暴力枚举前两组的人数，计算第三组的人数，判断是否满足条件，取最小值。
- **难点**：暴力枚举时间复杂度较高，但数据范围允许。
- **评分**：3星
- **关键亮点**：暴力枚举思路简单，但效率较低。
- **核心代码**：
```cpp
LL Ans = 1e18;
for (LL i = 1; i <= n - 2; i ++){
    for (LL j = 1; j <= n - i - 1; j ++){
        LL k = n - i - j;
        if (i <= 0 || j <= 0 || k <= 0)
            continue;
        LL t1 = A, t2 = B, t3 = C;
        if (t1 >= i)
            t1 -= i;
        else{
            if (t2 >= i - t1)
                t2 -= i - t1, t1 = 0;
            else
                continue;
        }
        if (t3 >= j)
            t3 -= j;
        else{
            if (t2 >= j - t3)
                t2 -= j - t3, t3 = 0;
            else
                continue;
        }
        if (t1 > 0 && t3 > 0)
            continue;
        Ans = min(Ans, max({i, j, k}));
    }
}
```

### 最优关键思路或技巧
- **贪心策略**：通过将Basic学生合理分配到汇编语言和C++学生中，使得最大小组规模最小化。
- **枚举优化**：在枚举分配方式时，可以通过数学计算减少枚举次数，提高效率。

### 可拓展之处
- 类似问题可以扩展到更多组别或更多种类的学生，需要更复杂的分配策略。
- 可以结合动态规划或二分查找进一步优化算法。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：42.67秒