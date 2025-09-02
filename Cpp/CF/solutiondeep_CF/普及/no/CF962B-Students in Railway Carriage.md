# 题目信息

# Students in Railway Carriage

## 题目描述

There are $ n $ consecutive seat places in a railway carriage. Each place is either empty or occupied by a passenger.

The university team for the Olympiad consists of $ a $ student-programmers and $ b $ student-athletes. Determine the largest number of students from all $ a+b $ students, which you can put in the railway carriage so that:

- no student-programmer is sitting next to the student-programmer;
- and no student-athlete is sitting next to the student-athlete.

In the other words, there should not be two consecutive (adjacent) places where two student-athletes or two student-programmers are sitting.

Consider that initially occupied seat places are occupied by jury members (who obviously are not students at all).

## 说明/提示

In the first example you can put all student, for example, in the following way: \*.AB\*

In the second example you can put four students, for example, in the following way: \*BAB\*B

In the third example you can put seven students, for example, in the following way: B\*ABAB\*\*A\*B

The letter A means a student-programmer, and the letter B — student-athlete.

## 样例 #1

### 输入

```
5 1 1
*...*
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 2 3
*...*.
```

### 输出

```
4
```

## 样例 #3

### 输入

```
11 3 10
.*....**.*.
```

### 输出

```
7
```

## 样例 #4

### 输入

```
3 2 3
***
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

有一个长度为 $n$ 的连续座位序列，每个座位要么是空的，要么被乘客占据。

大学的奥林匹克团队由 $a$ 个学生程序员和 $b$ 个学生运动员组成。你需要确定最多可以在这列火车上安排多少名学生，满足以下条件：

- 没有两个学生程序员坐在相邻的位置；
- 没有两个学生运动员坐在相邻的位置。

换句话说，相邻的两个座位不能同时被两个学生程序员或两个学生运动员占据。

初始时，被占据的座位由评委占据（显然评委不是学生）。

#### 说明/提示

在第一个样例中，你可以安排所有学生，例如：\*.AB\*

在第二个样例中，你可以安排四个学生，例如：\*BAB\*B

在第三个样例中，你可以安排七个学生，例如：B\*ABAB\*\*A\*B

字母 A 表示学生程序员，字母 B 表示学生运动员。

#### 样例 #1

##### 输入

```
5 1 1
*...*
```

##### 输出

```
2
```

#### 样例 #2

##### 输入

```
6 2 3
*...*.
```

##### 输出

```
4
```

#### 样例 #3

##### 输入

```
11 3 10
.*....**.*.
```

##### 输出

```
7
```

#### 样例 #4

##### 输入

```
3 2 3
***
```

##### 输出

```
0
```

### 算法分类
贪心

### 题解分析与结论

#### 综合分析
所有题解都采用了贪心算法，核心思想是尽可能多地安排学生，同时保证相邻座位不安排相同类型的学生。主要策略是优先安排剩余数量较多的学生类型，并在遇到相邻座位时交替安排不同类型的学生。

#### 关键思路
1. **优先安排剩余数量较多的学生类型**：在可以选择时，优先安排剩余数量较多的学生类型（A 或 B），以最大化利用资源。
2. **交替安排学生类型**：在遇到相邻座位时，交替安排不同类型的学生，确保不违反题目条件。
3. **处理特殊情况**：对于字符串的第一个字符，需要单独处理，确保初始安排的正确性。

#### 所选高分题解

##### 1. 作者：Nuyoah_awa (赞：3)
- **星级**：4
- **关键亮点**：代码简洁，逻辑清晰，优先处理第一个字符，确保初始安排的正确性。
- **核心代码**：
```cpp
for(int i = 0;i < n;i++)
{
    if(s[i] != '.')
        continue;
    if(s[i-1] == '*' || s[i-1] == '.')
    {
        if(a > b)
            a--, s[i] = 'A', ans++;
        else if(b)
            b--, s[i] = 'B', ans++;
    }
    else
    {
        if(b && s[i-1] == 'A')
            b--, s[i] = 'B', ans++;
        if(a && s[i-1] == 'B')
            a--, s[i] = 'A', ans++;
    }
}
```

##### 2. 作者：qW__Wp (赞：3)
- **星级**：4
- **关键亮点**：详细解释了贪心策略，代码结构清晰，处理了字符串的第一个字符。
- **核心代码**：
```cpp
for(int i=1;i<l;i++){
    if(s[i]=='.'){
        if(s[i-1]=='*'||s[i-1]=='.'){
            if(a>=b&&a>0){
                s[i]='A';
                a--;
                ans++;
            }
            if(b>=a&&b>0){
                s[i]='B';
                b--;
                ans++;
            }
        }else if(s[i-1]=='A'&&b>0){
            s[i]='B';
            b--;
            ans++;
        }else if(s[i-1]=='B'&&a>0){
            s[i]='A';
            a--;
            ans++;
        }
    }
}
```

##### 3. 作者：Fu_Da_Ying (赞：0)
- **星级**：4
- **关键亮点**：详细分类讨论了奇数和偶数个连续 `.` 的情况，代码逻辑清晰，处理了字符串的第一个字符。
- **核心代码**：
```cpp
for(long long i=1;i<n;i++){
    if(s[i]!='.'){
        continue;
    }
    if(s[i-1]=='*'||s[i-1]=='.'){
        if(a>b){
            a--;
            s[i]='A';
            ans++;
        }else if(b!=0){
            b--;
            s[i]='B';
            ans++;
        }
    }else{
        if(b!=0&&s[i-1]=='A'){
            b--;
            s[i]='B';
            ans++;
        }
        if(a!=0&&s[i-1]=='B'){
            a--;
            s[i]='A';
            ans++;
        }
    }
}
```

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：30.56秒