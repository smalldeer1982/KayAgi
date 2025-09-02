# Magic, Wizardry and Wonders

## 题目描述

Vasya the Great Magician and Conjurer loves all kinds of miracles and wizardry. In one wave of a magic wand he can turn an object into something else. But, as you all know, there is no better magic in the Universe than the magic of numbers. That's why Vasya adores math and spends a lot of time turning some numbers into some other ones.

This morning he has $ n $ cards with integers lined up in front of him. Each integer is not less than 1, but not greater than $ l $ . When Vasya waves his magic wand, two rightmost cards vanish from the line and a new card magically appears in their place. It contains the difference between the left and the right numbers on the two vanished cards. Vasya was very interested to know what would happen next, and so he waved with his magic wand on and on, until the table had a single card left.

Suppose that Vasya originally had the following cards: 4, 1, 1, 3 (listed from left to right). Then after the first wave the line would be: 4, 1, -2, and after the second one: 4, 3, and after the third one the table would have a single card with number 1.

Please note that in spite of the fact that initially all the numbers on the cards were not less than 1 and not greater than $ l $ , the numbers on the appearing cards can be anything, no restrictions are imposed on them.

It is now evening. Vasya is very tired and wants to return everything back, but does not remember which cards he had in the morning. He only remembers that there were $ n $ cards, they contained integers from 1 to $ l $ , and after all magical actions he was left with a single card containing number $ d $ .

Help Vasya to recover the initial set of cards with numbers.

## 样例 #1

### 输入

```
3 3 2
```

### 输出

```
2 1 2 ```

## 样例 #2

### 输入

```
5 -4 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 -4 4
```

### 输出

```
2 4 1 4 1 ```

# 题解

## 作者：三点水一个各 (赞：2)

### 题意

有一个序列 $a$，序列中的元素均为不大于 $l$ 的正整数。将序列倒数第二个元素减去倒数第一个元素的差作为新的倒数第一个元素，执行这个操作直到序列中只剩一个元素 $d$。

现在给你元素 $d$，让你构造整个序列。

### 做法

尝试分析 $d$ 是怎么来的：

当 $n$ 为奇数时，$d=a_1-(a_2-(\cdots -(a_{n-1}-a_n)))$。

整理得 $d=a_1+a_3+\cdots +a_n-a_2-a_4-\cdots-a_{n-1}$。

当 $n$ 为偶数时，$d=a_1-(a_2-(\cdots -(a_{n-1}-a_n)))$。

整理得 $d=a_1+a_3+\cdots +a_{n-1}-a_2-a_4-\cdots-a_n$。

不难看出，$d$ 的值为序列中奇数位元素之和减去偶数位元素之和。

当序列中奇数位元素都取 $l$，偶数位元素都取 $1$，此时 $d$ 达到最大值，如果此时我们求得的 $d$ 仍小于输入数据中给出的 $d$，则这个序列是无法构造的。

当序列中奇数位元素都取 $1$，偶数位元素都取 $l$，此时 $d$ 达到最小值，如果此时我们求得的 $d$ 仍大于输入数据中给出的 $d$，则这个序列也是无法构造的。

***

现在构造序列，考虑贪心。

如果 $d$ 是正数，则意味着需要取较大数，这里取 $l$。

如果 $d$ 是负数，则意味着需要取较小数，这里取 $1$。

注意在传递 $d$ 时，需要变号，比如原先是奇数位，要 $+d$ 才能满足，现在变为偶数位，则应为 $-(-d)$。

最后处理一下 $a_n$。

在样例一中，$d=3\ ,\ l=2$。

处理第一位时，$d$ 为正数，令 $a_1$ 为 $2$。

处理第二位时，应变号 $d$ 为 $d=-(d-a_1)=a_1-d=2-3=-1$，$d$ 为负数，令 $a_2$ 为 $1$。

处理第三位时，应变号 $d$ 为 $d=-(d-a_2)=a_2-d=1-(-1)=2$，$d$ 为正数，令 $a_2$ 为 $2$。

恰好此时 $d=-(2-2)=0$，构造完成。

$\mathtt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[102],n,l,d,b1,b2;
int main()
{
    scanf("%d%d%d",&n,&d,&l);
    b1=ceil(n*1.0/2); b2=floor(n*1.0/2);
    if(b1*l-b2<d||d<b1-b2*l) 
    {
        printf("-1"); 
        return 0; 
    }
    for(int i=1;i<=n;++i)
      if(d>0) 
      {
          a[i]=l; d=l-d;
      }
      else 
      {
          a[i]=1; d=1-d;
      }
    a[n]-=d;
    for(int i=1;i<=n;++i)
      printf("%d ",a[i]);
    return 0;
}
```

---

