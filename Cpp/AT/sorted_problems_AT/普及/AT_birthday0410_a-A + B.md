---
title: "A + B"
layout: "post"
diff: 普及/提高-
pid: AT_birthday0410_a
tag: []
---

# A + B

## 题目描述

### 问题描述

> ### A + B 问题
> 
> #### 问题描述
> 
> 编写一个程序来计算两个整数 $A, B$ 的和。
> 
> 保证 $A, B, A + B$ 都能用 $32$ 位有符号整数表示。
>

## 输入格式

> 
> > $A _ 1$ $B _ 1$  
> > $A _ 2$ $B _ 2$  
> > $\dots$  
> > $0$ $0$  
>
> 输入包括最多 $100$ 个测试用例。每个测试用例在一行中给出两个整数 $A$ 和 $B$，用空格分隔。
> 
> 输入以一行 $A = B = 0$ 结束，这一行不需要处理。
> 

> $t$

只有一行包含一个整数 $t$，表示需要找到击败第 $t$ 个回答的测试用例。


### 限制

所有输入数据满足以下限制条件：

- $1 \le t \le 3$

### 评分标准

总共有 3 个测试用例：

- 如果 $t = 1$ 的测试用例正确，将获得 **33 分**。
- 如果 $t = 2$ 的测试用例正确，将获得 **33 分**。
- 如果 $t = 3$ 的测试用例正确，将获得 **34 分**。

---

Translated by User 735713.

## 输出格式

> 
> 对于每个测试用例，输出 $A + B$ 的值，每个结果占一行。

一场比赛的问题 A 已经完成，现在正进入测试阶段。然而，由于疲劳的原因，不幸的是 JAPLJ 在 A + B 问题中出现了 Bug。大学生丸桥，这个比赛的负责人，提出了解决条件……

丸桥说：“你要把错误的源代码改正确，快点！”

你需要为 JAPLJ 的三个错误程序各找出一个能够击败它们的测试用例，并输出这些测试用例。

### 课题

针对 A + B 问题（请参阅问题描述），下面有三个用 C++ 编写的错误程序。为每个错误程序找到一个可以击败它们的测试用例。

更准确地说，对于每个错误程序，请编写一个满足 A + B 问题的描述和输入部分约束的测试用例。当将这个测试用例输入到错误程序中时，该程序将输出错误的答案。编写一个程序来输出这样的测试用例。

回答 1 的源代码:

```cpp
#include <iostream>

using namespace std;

int main()
{
  int A, B;

  while(cin >> A >> B, A+B!=0) {
    cout << A+B << endl;
  }

  return 0;
}
```

回答 2 的源代码：

```cpp
#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
```

回答 3 的源代码：

```cpp
#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
```


输出一个能够击败第 $t$ 个回答的测试用例。

