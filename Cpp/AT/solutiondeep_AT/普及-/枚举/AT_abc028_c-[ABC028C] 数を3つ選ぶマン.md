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
### 示例解释 1
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
这些题解的核心思路都是先枚举从 5 个数中选 3 个数的所有组合，计算它们的和，然后对这些和进行排序和去重，最后找出第 3 大的数。不同题解在实现细节上有所不同，主要体现在数据结构的选择和排序去重的方法上。

### 所选题解
- **happybob（4星）**
    - **关键亮点**：使用 `set` 自动去重和排序，引入 `reverse_iterator` 逆序遍历 `set` 找到第 3 大的数，思路清晰，代码简洁。
    - **重点代码**：
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
- **Egg_eating_master（4星）**
    - **关键亮点**：同样使用 `set` 自动去重和排序，通过迭代器自减找到第 3 大的数，代码简洁明了。
    - **重点代码**：
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
- **pbdean（4星）**
    - **关键亮点**：使用插入排序算法对和进行排序并去重，代码实现有一定的技巧性。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
bool isort(int* a,int b,int);
int main(){
    int a[5]={0},b[10]={0},len=0;
    cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];
    for(int i=0;i<3;i++)
        for(int j=i+1;j<4;j++)
            for(int k=j+1;k<5;k++)if(isort(b,a[i]+a[j]+a[k],len))len++;
    cout<<b[2]<<endl;
    return 0;
}
bool isort(int* a,int b,int len){
    int j=len-1;
    for(;j>=0;j--)if(a[j]==b) return false;
    j=len-1;
    while((j>=0)&&b>a[j]){
        a[j+1]=a[j];
        j--;
    }
    a[j+1]=b;
    return true;
}
```

### 最优关键思路或技巧
- **数据结构**：使用 `set` 可以自动去重和排序，简化代码实现。
- **迭代器**：`reverse_iterator` 可以方便地逆序遍历容器，找到第 3 大的数。

### 可拓展之处
同类型题可能会增加输入的数的个数，或者要求找出第 k 大的数。可以使用堆（优先队列）来优化排序过程，时间复杂度为 $O(n log k)$。

### 推荐洛谷题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察去重和排序。
- [P1177 快速排序](https://www.luogu.com.cn/problem/P1177)：考察排序算法。
- [P1271 选举学生会](https://www.luogu.com.cn/problem/P1271)：考察排序和查找第 k 大的数。

### 个人心得摘录与总结
- **pbdean**：评测时 WA 了，回头看日文原题发现“末尾”“改行”提示，加上 `endl` 后 AC，提醒做题时要仔细看题，注意输出格式。
- **A_Plus_Gu**：69 分代码只考虑了一种简单情况，提醒不能想当然，要全面枚举所有情况。 

---
处理用时：33.97秒