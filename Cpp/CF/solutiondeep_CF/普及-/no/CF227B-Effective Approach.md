# 题目信息

# Effective Approach

## 题目描述

Once at a team training Vasya, Petya and Sasha got a problem on implementing linear search in an array.

According to the boys, linear search works as follows. The array elements in a pre-selected order are in turn compared with the number that you need to find. Once you find the array element that is equal to the required one, the search ends. The efficiency of the algorithm is the number of performed comparisons. The fewer comparisons the linear search has made, the more effective it is.

Vasya believes that a linear search would work better if it sequentially iterates through the elements, starting with the $ 1 $ -st one (in this problem we consider the elements of the array indexed from $ 1 $ to $ n $ ) and ending with the $ n $ -th one. And Petya says that Vasya is wrong: the search will need less comparisons if it sequentially iterates the elements starting from the $ n $ -th and ending with the $ 1 $ -st one. Sasha argues that the two approaches are equivalent.

To finally begin the task, the teammates decided to settle the debate and compare the two approaches on an example. For this, they took an array that is a permutation of integers from $ 1 $ to $ n $ , and generated $ m $ queries of the form: find element with value $ b_{i} $ in the array. They want to calculate for both approaches how many comparisons in total the linear search will need to respond to all queries. If the first search needs fewer comparisons, then the winner of the dispute is Vasya. If the second one does, then the winner is Petya. If both approaches make the same number of comparisons, then Sasha's got the upper hand.

But the problem is, linear search is too slow. That's why the boys aren't going to find out who is right before the end of the training, unless you come in here. Help them to determine who will win the dispute.

## 说明/提示

In the first sample Vasya's approach will make one comparison (it starts with the $ 1 $ -st element and immediately finds the required number), and Petya's approach makes two comparisons (first he compares with the $ 2 $ -nd array element, doesn't find the search item and compares with the $ 1 $ -st element).

In the second sample, on the contrary, Vasya's approach will need two comparisons (first with $ 1 $ -st element, and then with the $ 2 $ -nd), and Petya's approach will find the required value in one comparison (the first comparison with the $ 2 $ -nd element).

## 样例 #1

### 输入

```
2
1 2
1
1
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
2
2 1
1
1
```

### 输出

```
2 1
```

## 样例 #3

### 输入

```
3
3 1 2
3
1 2 3
```

### 输出

```
6 6
```

# AI分析结果

### 题目内容
#### 高效方法
1. **题目描述**：在一次团队训练中，瓦夏（Vasya）、佩佳（Petya）和萨沙（Sasha）遇到了一个关于在数组中实现线性搜索的问题。
根据这几个男孩的理解，线性搜索的工作方式如下。按照预先选定的顺序，依次将数组元素与需要查找的数字进行比较。一旦找到与所需数字相等的数组元素，搜索就结束。该算法的效率由执行的比较次数来衡量。线性搜索进行的比较次数越少，效率就越高。
瓦夏认为，如果从第1个元素开始（在本题中，我们认为数组元素的索引从1到n），按顺序迭代到第n个元素，线性搜索会更有效。而佩佳说瓦夏错了：如果从第n个元素开始，按顺序迭代到第1个元素，搜索所需的比较次数会更少。萨沙则认为这两种方法是等效的。
为了最终开始任务，队友们决定解决这个争论，并通过一个例子来比较这两种方法。为此，他们取了一个由1到n的整数排列组成的数组，并生成了m个查询，形式为：在数组中查找值为bi的元素。他们想计算对于这两种方法，线性搜索总共需要多少次比较才能响应所有查询。如果第一种搜索方法需要的比较次数更少，那么争论的获胜者就是瓦夏。如果第二种方法需要的比较次数更少，那么获胜者就是佩佳。如果两种方法的比较次数相同，那么萨沙就占了上风。
但问题是，线性搜索太慢了。这就是为什么除非你介入，否则男孩们在训练结束前都无法确定谁是正确的。帮助他们确定谁将赢得这场争论。
2. **说明/提示**：在第一个样例中，瓦夏的方法将进行一次比较（它从第1个元素开始，立即找到了所需的数字），而佩佳的方法进行两次比较（首先他与第2个数组元素进行比较，没有找到搜索项，然后与第1个元素进行比较）。
在第二个样例中，情况相反，瓦夏的方法将需要两次比较（首先与第1个元素比较，然后与第2个元素比较），而佩佳的方法将在一次比较中找到所需的值（第一次与第2个元素比较）。
3. **样例 #1**
    - **输入**：
```
2
1 2
1
1
```
    - **输出**：
```
1 2
```
4. **样例 #2**
    - **输入**：
```
2
2 1
1
1
```
    - **输出**：
```
2 1
```
5. **样例 #3**
    - **输入**：
```
3
3 1 2
3
1 2 3
```
    - **输出**：
```
6 6
```
• **算法分类**：无算法分类
• **综合分析与结论**：三道题解思路本质相同，都是通过记录每个数在数组中的位置，来快速计算顺序查找和逆序查找所需的比较次数。不同点在于存储数据方式，题解1用map，题解2用桶数组，题解3考虑数据重复用两个数组分别记录每个数出现的最小和最大位置。从空间复杂度看，题解1的map理论上空间占用可能稍大；从代码简洁度和可读性，题解1和题解2更简洁清晰。
• **所选的题解**
  - **题解1**：
    - **星级**：4星
    - **关键亮点**：使用map建立值到序号的对应关系，代码简洁明了，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b;
long long ans1,ans2;
map<int,int>a;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&b);
        a[b]=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b);
        ans1+=a[b];
        ans2+=n-a[b]+1;
    }
    printf("%lld %lld",ans1,ans2);
    return 0;
}
```
核心实现思想：先遍历数组将每个数与其位置存入map，再遍历查询，根据map中记录的位置计算顺序和逆序查找的比较次数。
  - **题解2**：
    - **星级**：4星
    - **关键亮点**：利用桶数组存储数据，同样简洁高效，数组操作相对map可能更易理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define N 100001
#define ll long long
using namespace std;
int n,m;
int flag[N];
ll ans1=0,ans2=0;
void clear(){
    for(int i=1;i<=n;i++)flag[i]=0;
}
int main()
{
    ios::sync_with_stdio(false);
    int x;
    cin>>n;
    clear();
    for(int i=1;i<=n;i++){
        cin>>x;
        flag[x]=i;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>x;
        ans1+=flag[x];
        ans2+=n-flag[x]+1;
    }
    cout<<ans1<<" "<<ans2;
    return 0; 
} 
```
核心实现思想：初始化桶数组，遍历数组将每个数的位置存入桶数组，遍历查询，依桶数组记录计算两种查找方式的比较次数。
• **最优关键思路或技巧**：通过建立值与位置的映射关系（无论是用map还是桶数组），避免每次查询都进行线性遍历，从而快速计算出不同查找顺序下的比较次数，提高效率。
• **可拓展之处**：同类型题可考虑对不同查找策略效率分析的题目，类似算法套路是遇到需要多次查找特定元素位置或计算查找相关次数时，建立元素与位置的映射可优化时间复杂度。
• **推荐洛谷题目**：
  - P1160 队列安排，涉及元素位置的动态维护与查询。
  - P1996 约瑟夫问题，通过模拟元素位置变化解决问题，和本题记录位置思路有相似处。
  - P1083 借教室，可通过建立映射关系优化对资源占用情况的查询。 

---
处理用时：46.33秒