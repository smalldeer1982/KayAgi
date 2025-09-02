# 题目信息

# [ABC028C] 数を3つ選ぶマン

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc028/tasks/abc028_c

異なる整数が $ 5 $ 個与えられます。

この中から $ 3 $ つ選んでその和で表すことの出来る整数のうち、$ 3 $ 番目に大きいものを出力してください。

## 说明/提示

### Sample Explanation 1

$ 3 $ つ選んでその和で表すことのできる整数は $ 6,\ 7,\ 8,\ 9,\ 10,\ 11,\ 12 $ です。なので、このなかで $ 3 $ 番目に大きい $ 10 $ を出力します。

## 样例 #1

### 输入

```
1 2 3 4 5```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2 3 5 8```

### 输出

```
14```

# AI分析结果

### 题目翻译
# [ABC028C] 选三个数的人

## 题目描述
[problemUrl]: https://atcoder.jp/contests/abc028/tasks/abc028_c

给定 5 个不同的整数。

请输出从这些数中选 3 个数相加所能得到的整数中，第 3 大的数。

## 说明/提示
### 样例解释 1
选 3 个数相加所能得到的整数为 6、7、8、9、10、11、12。因此，输出其中第 3 大的 10。

## 样例 #1
### 输入
```
1 2 3 4 5
```
### 输出
```
10
```

## 样例 #2
### 输入
```
1 2 3 5 8
```
### 输出
```
14
```

### 综合分析与结论
这些题解的核心思路都是先枚举从 5 个数中选 3 个数的所有组合并计算其和，然后对这些和进行去重与排序，最后找出第 3 大的数。不同题解在实现方式上各有不同，有的使用了 STL 容器（如 `set`），有的使用了排序算法（如 `sort`），还有的使用了桶排序。

### 所选的题解
- **happybob（4星）**
    - **关键亮点**：使用 `set` 容器自动去重和排序，利用 `reverse_iterator` 逆序遍历 `set` 找到第 3 大的数，代码简洁且思路清晰。
    - **个人心得**：介绍了 `reverse_iterator` 的使用方法和 `set` 迭代器的一些小误区，如 `end` 的返回值是最后那个数据 + 1 的迭代器，而 `rbegin` 是最后一个数据的迭代器。
```cpp
#include <cstdio>
#include <set>
using namespace std;

int a[10];
set<int> sum;

int main()
{
    scanf("%d %d %d %d %d", &a[1], &a[2], &a[3], &a[4], &a[5]);
    for(register int i = 1; i <= 5; i++)
    {
        for(register int j = i + 1; j <= 5; j++)
        {
            for(register int k = j + 1; k <= 5; k++)
            {
                sum.insert(a[i] + a[j] + a[k]);
            }
        }
    }
    int i = 0;
    set<int>::reverse_iterator endd = sum.rbegin(), beginn = sum.rend();
    for(set<int>::reverse_iterator it = endd; it != beginn; ++it)
    {
        i++;
        if(i == 3) {printf("%d\n", *it); return 0;}
    }
    return 0;
}
```
核心实现思想：通过三重循环枚举所有选 3 个数的组合，将其和插入 `set` 中，利用 `set` 的特性自动去重和排序，再使用 `reverse_iterator` 逆序遍历找到第 3 大的数。

- **Egg_eating_master（4星）**
    - **关键亮点**：同样使用 `set` 容器，直接通过 `end` 迭代器自减找到第 3 大的数，代码简洁明了。
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>s;
int a[6];
int main(){
    for(int i=1;i<=5;i++)
        cin>>a[i];
    for(int i=1;i<=3;i++)
        for(int j=i+1;j<=4;j++)
            for(int k=j+1;k<=5;k++)
                s.insert(a[i]+a[j]+a[k]);
    set<int>::iterator it=s.end();
    it--;it--;it--;
    cout<<*it<<endl;
    return 0;
}
```
核心实现思想：通过三重循环枚举所有选 3 个数的组合，将其和插入 `set` 中，利用 `set` 的特性自动去重和排序，然后通过 `end` 迭代器自减找到第 3 大的数。

- **zzhhf（4星）**
    - **关键亮点**：使用桶排序的思想，通过枚举组合并将和放入桶中，再从大到小遍历桶找到第 3 大的数，思路独特。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],x[1000];  
int main()
{
    int n,i,j,s,b,sum;
    n=5;
    s=0;
    for(i=1;i<=n;i++)
        cin>>a[i];
    for(i=1;i<n-1;i++)
        for(j=i+1;j<=n-1;j++)
            for(int k=j+1;k<=n;k++)
            {
                s++;
                sum=a[i]+a[j]+a[k];
                x[sum]++;
            }
    s=0;
    for(i=300;i>=1;i--)
    {
        if(x[i]>0){
            s++;
            if(s==3){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
} 
```
核心实现思想：通过三重循环枚举所有选 3 个数的组合，将其和作为桶的下标，桶中记录该和出现的次数，再从大到小遍历桶，当累加次数达到 3 时输出当前桶的下标。

### 最优关键思路或技巧
- **使用 `set` 容器**：`set` 可以自动去重和排序，能大大简化代码实现。
- **桶排序**：对于范围较小的数值，桶排序是一种简单有效的排序和去重方法。

### 可拓展之处
同类型题可能会改变数据范围、选择的数字个数或要求找到其他位置的数，解题思路仍然是枚举组合、去重和排序。类似算法套路可以应用于组合枚举、排序算法的选择等场景。

### 推荐洛谷题目
- P1059 [NOIP2006 普及组] 明明的随机数（去重和排序）
- P1177 [模板] 快速排序（排序算法）
- P1271 [深基9.例1] 选举学生会（排序和查找）

### 个人心得总结
- **Egg_eating_master**：强调了 `set` 容器的便捷性，认为其是为这道题量身定做的。
- **pbdean**：评测时因未注意输出换行而 WA，提醒要仔细看题。
- **A_Plus_Gu**：69 分代码未通过，强调要按照枚举、排序去重、找第 3 大的数的步骤来解题。 

---
处理用时：40.87秒