# 题目信息

# Magic Stick

## 题目描述

Recently Petya walked in the forest and found a magic stick.

Since Petya really likes numbers, the first thing he learned was spells for changing numbers. So far, he knows only two spells that can be applied to a positive integer:

1. If the chosen number $ a $ is even, then the spell will turn it into $ \frac{3a}{2} $ ;
2. If the chosen number $ a $ is greater than one, then the spell will turn it into $ a-1 $ .

Note that if the number is even and greater than one, then Petya can choose which spell to apply.

Petya now has only one number $ x $ . He wants to know if his favorite number $ y $ can be obtained from $ x $ using the spells he knows. The spells can be used any number of times in any order. It is not required to use spells, Petya can leave $ x $ as it is.

## 样例 #1

### 输入

```
7
2 3
1 1
3 6
6 8
1 2
4 1
31235 6578234
```

### 输出

```
YES
YES
NO
YES
NO
YES
YES
```

# AI分析结果

### 题目内容
# 魔法棒

## 题目描述
最近，佩佳在森林里散步时发现了一根魔法棒。

由于佩佳非常喜欢数字，他学到的第一个魔法是改变数字。到目前为止，他只知道两种可以应用于正整数的魔法：
1. 如果选定的数字 $a$ 是偶数，那么魔法会将其变为 $\frac{3a}{2}$；
2. 如果选定的数字 $a$ 大于1，那么魔法会将其变为 $a - 1$。

注意，如果数字是偶数且大于1，那么佩佳可以选择应用哪个魔法。

佩佳现在只有一个数字 $x$。他想知道他最喜欢的数字 $y$ 是否可以通过他所知道的魔法从 $x$ 得到。这些魔法可以以任何顺序使用任意次数。不一定要使用魔法，佩佳可以让 $x$ 保持不变。

## 样例 #1
### 输入
```
7
2 3
1 1
3 6
6 8
1 2
4 1
31235 6578234
```
### 输出
```
YES
YES
NO
YES
NO
YES
YES
```

### 算法分类
数学

### 题解综合分析与结论
所有题解都基于对两种操作特性的分析来解决问题。核心思路是通过对不同取值范围的 $x$ 进行分类讨论，判断能否从 $x$ 得到 $y$ 。主要难点在于找出不同 $x$ 值下操作的规律以及边界情况。各题解思路相近，都利用了 $x = 1$ 时无法增大、$x \leq 3$ 时变化范围有限、$x > 3$ 时可通过操作使 $x$ 大于等于 $y$ 等关键特性。

### 所选的题解
- **作者：B_Qu1e7 (5星)**
    - **关键亮点**：思路简洁清晰，代码实现高效。通过巧妙地将 $X$ 变为最大偶数，再针对 $X = 2$ 等特殊情况进行判断，直接得出结果。
    - **重点代码**：
```cpp
#include<cstdio>
#define R register
int T,X,Y;
template<class T>inline void read(R T &m)
{
    m=0;
    R char c=getchar();
    while(c<48||c>57)c=getchar();
    while(c>47&&c<58)m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
    read(T);
    while(T--)
    {
        read(X),read(Y);
        if(X==Y)puts("YES");
        else if(X==1)puts("NO");
        else
        {
            X-=X&1;
            if(X==2)
            {
                puts(Y>3?"NO":"YES");
            }
            else
            {
                puts("YES");
            }
        }
    }
}
```
    - **核心实现思想**：先判断 $X$ 与 $Y$ 是否相等，若 $X = 1$ 直接输出 `NO` 。否则将 $X$ 变为最大偶数，若此时 $X = 2$ ，根据 $Y$ 是否大于 $3$ 输出结果，否则输出 `YES` 。
- **作者：Sya_Resory (4星)**
    - **关键亮点**：逻辑清晰，先指出 $x \geq y$ 时一定能成功，简化问题，再针对 $x < y$ 的情况进行特判。
    - **重点代码**：
```cpp
// 1257B Magic Stick
#include <cstdio>

int t,x,y;
bool flag; 

int main() {
    scanf("%d",&t);
    for(;t;t --) {
        flag = true; 
        scanf("%d%d",&x,&y);
        if(x >= y) { 
            puts("YES");
            continue;
        }
        if(x == 1) flag = false; 
        if(x <= 3 && y > 3) flag = false; 
        flag? puts("YES") : puts("NO");
    }
    return 0;
}
```
    - **核心实现思想**：初始化标志位 `flag` ，若 $x \geq y$ 直接输出 `YES` 。若 $x = 1$ 或 $x \leq 3$ 且 $y > 3$ 则将 `flag` 设为 `false` ，最后根据 `flag` 输出结果。
- **作者：ivyjiao (4星)**
    - **关键亮点**：分析全面，对各种情况的判断依据阐述清晰，代码简洁明了。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int t,x,y;
int main(){
    cin>>t;
    while(t--){
        cin>>x>>y;
        if(x>=y)cout<<"YES"<<endl;
        else if(x==1)cout<<"NO"<<endl;
        else if(x<=3&&y>3)cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}
```
    - **核心实现思想**：依次判断 $x \geq y$ 、$x = 1$ 、$x \leq 3$ 且 $y > 3$ 的情况，根据不同情况输出相应结果。

### 最优关键思路或技巧
通过对不同取值范围的 $x$ 进行分类讨论，利用操作特性找出规律，如 $x = 1$ 无法增大、$x \leq 3$ 时变化局限于特定值、$x > 3$ 可通过操作使 $x$ 增大到大于等于 $y$ ，从而简化问题求解。

### 拓展思路
此类题目属于数字变换规律探索类型，可拓展到其他类似数字操作规则的题目。例如改变操作规则，或者增加操作种类，依然通过分析操作对不同范围数字的影响来解题。

### 洛谷相似题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)

### 个人心得
无

---
处理用时：56.76秒