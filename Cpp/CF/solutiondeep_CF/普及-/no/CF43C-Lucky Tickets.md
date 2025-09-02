# 题目信息

# Lucky Tickets

## 题目描述

Vasya thinks that lucky tickets are the tickets whose numbers are divisible by 3. He gathered quite a large collection of such tickets but one day his younger brother Leonid was having a sulk and decided to destroy the collection. First he tore every ticket exactly in two, but he didn’t think it was enough and Leonid also threw part of the pieces away. Having seen this, Vasya got terrified but still tried to restore the collection. He chose several piece pairs and glued each pair together so that each pair formed a lucky ticket. The rest of the pieces Vasya threw away reluctantly. Thus, after the gluing of the $ 2t $ pieces he ended up with $ t $ tickets, each of which was lucky.

When Leonid tore the tickets in two pieces, one piece contained the first several letters of his number and the second piece contained the rest.

Vasya can glue every pair of pieces in any way he likes, but it is important that he gets a lucky ticket in the end. For example, pieces 123 and 99 can be glued in two ways: 12399 and 99123.

What maximum number of tickets could Vasya get after that?

## 样例 #1

### 输入

```
3
123 123 99
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
1 1 1 23 10 3
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 幸运车票

## 题目描述
瓦夏认为，幸运车票是那些号码能被3整除的车票。他收集了相当多的这类车票，但有一天，他的弟弟列昂尼德生气了，决定毁掉这些收藏。首先，他把每张车票都撕成了两半，但他觉得这还不够，列昂尼德还扔掉了一部分碎片。看到这一幕，瓦夏吓坏了，但他还是试图恢复这些收藏。他选择了几对碎片，并将每对碎片粘在一起，使得每对碎片组成一张幸运车票。其余的碎片，瓦夏不情愿地扔掉了。这样，在粘了2t个碎片后，他最终得到了t张车票，每张车票都是幸运的。

当列昂尼德把车票撕成两半时，其中一片包含号码的前几个数字，另一片包含其余部分。

瓦夏可以以任何他喜欢的方式粘贴每对碎片，但重要的是最后要得到一张幸运车票。例如，碎片123和99可以以两种方式粘贴：12399和99123。

瓦夏在这之后最多能得到多少张车票呢？

## 样例 #1
### 输入
```
3
123 123 99
```
### 输出
```
1
```

## 样例 #2
### 输入
```
6
1 1 1 23 10 3
```
### 输出
```
1
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路一致，均基于“一个数若各位数字之和是3的倍数，那么这个数是3的倍数”这一数学知识。将输入的数按模3的余数分类，统计余数为0、1、2的数的个数，分别记为a[0]、a[1]、a[2] 。因为两个模3余0的数拼接，或一个模3余1与一个模3余2的数拼接，得到的数能被3整除，所以答案为a[0]/2 + min(a[1], a[2]) 。各题解在思路清晰度和代码可读性上略有差异。

### 所选的题解
 - **作者：Plozia（5星）**
    - **关键亮点**：思路阐述详细，从分析拼成3的倍数的情况入手，逐步推导出答案的计算方式，逻辑连贯清晰，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000+10;
int n,three,two,one;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);
        if(t%3==0) three++;
        if(t%3==1) one++;
        if(t%3==2) two++;
    }
    printf("%d\n",three/2+min(one,two));
    return 0;
}
```
核心实现思想：通过循环读入每个数，根据其模3的余数对相应计数器累加，最后按公式计算并输出结果。
 - **作者：test_check（4星）**
    - **关键亮点**：表述简洁，直接给出解题关键思路，即统计余数各类别的个数并按公式计算答案，代码也简洁易懂。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,x,a[3]={0};
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        a[x%3]++;  //统计
    }
    int ans=a[0]/2+min(a[1],a[2]);  //更新ans的值
    cout<<ans;
}
```
核心实现思想：利用数组a统计每个数模3后的余数类别个数，按公式计算并输出最终答案。
 - **作者：Tune_ （4星）**
    - **关键亮点**：简洁明了地阐述了配对规则，即两个3的倍数配对或除以3余2和除以3余1的两个数配对，代码短小精悍。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[3]={0},c;
    for(int i=1;i<=n;i++)
    {
        cin>>c;
        a[c%3]++;
    }
    cout<<a[0]/2+min(a[1],a[2]);
    return 0;
}
```
核心实现思想：循环读入数据，用数组a记录余数为0、1、2的数的个数，按公式计算并输出答案。

### 最优关键思路或技巧
利用3的倍数的数学性质，通过对输入数字按模3的余数分类统计，快速得出可组成3的倍数的组合数量。这种基于数学性质简化问题的思维方式是关键技巧。

### 可拓展之处
同类型题可考察其他数的整除特性，类似算法套路是先分析目标数的整除性质，再根据该性质对数据进行分类处理，从而简化问题求解。

### 洛谷相似题目推荐
 - P1909 [NOIP2016 普及组] 买铅笔：通过分析不同包装铅笔数量与所需铅笔数量关系，利用数学计算选择最优方案。
 - P1075 [NOIP2012 普及组] 质因数分解：利用数学知识对给定数字进行质因数分解。
 - P1147 连续自然数和：通过数学推导找出满足和为给定值的连续自然数序列。 

---
处理用时：50.70秒