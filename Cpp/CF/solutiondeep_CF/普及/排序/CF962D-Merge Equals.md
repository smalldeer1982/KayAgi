# 题目信息

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1
```

### 输出

```
4
3 8 2 1 
```

## 样例 #2

### 输入

```
5
1 1 3 1 1
```

### 输出

```
2
3 4 
```

## 样例 #3

### 输入

```
5
10 40 20 50 30
```

### 输出

```
5
10 40 20 50 30 
```

# AI分析结果

### 题目翻译
## 合并相等元素

### 题目描述
给定一个正整数数组。只要数组中至少有两个相等的元素，我们就会执行以下操作。我们选择数组中出现 2 次或更多次的最小的值 $x$。取这个数组中 $x$ 的前两个出现位置（最左边的两个出现位置）。移除这两个出现位置中左边的那个，右边的那个用这两个值的和（即 $2 \cdot x$）替换。

确定在执行完上述操作后数组会变成什么样子。

例如，考虑给定的数组为 $[3, 4, 1, 2, 2, 1, 1]$。它将按以下方式变化：$[3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1]$。

如果给定的数组为 $[1, 1, 3, 1, 1]$，它将按以下方式变化：$[1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4]$。

### 说明/提示
前两个示例在题目描述中已经给出。

在第三个示例中，给定数组中的所有整数都是不同的，所以它不会改变。

### 样例 #1
#### 输入
```
7
3 4 1 2 2 1 1
```
#### 输出
```
4
3 8 2 1 
```

### 样例 #2
#### 输入
```
5
1 1 3 1 1
```
#### 输出
```
2
3 4 
```

### 样例 #3
#### 输入
```
5
10 40 20 50 30
```
#### 输出
```
5
10 40 20 50 30 
```

### 综合分析与结论
这些题解的核心思路都是模拟题目中的合并操作，主要区别在于实现方式和使用的数据结构。大部分题解使用优先队列（堆）来维护数组元素，方便每次取出最小的元素进行合并操作。部分题解使用 `map` 来记录元素的出现情况，简化合并过程。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Bitter_Tea | 用堆模拟合并过程，每次取两个最小元素，相等则合并，不等则保存第一个元素 | 重载堆的比较运算符，按数值和原始位置排序 | 处理最后一个元素，按位置排序输出结果 | 4星 |
| chenxia25 | 方法1：用堆模拟；方法2：除因数2后排序分类处理 | 方法1：堆的比较方式；方法2：分类处理相同元素 | 方法2：处理每类元素的合并 | 3星 |
| ChenJr | 用优先队列维护数值和位置，不断合并相同元素 | 优先队列重载比较运算符，按数值和位置排序 | 处理最后一个元素，按位置排序输出结果 | 4星 |
| Milmon | 优先队列存储下标，按对应值排序，合并相同元素 | 优先队列比较函数，按值和下标排序 | 按下标排序输出结果 | 4星 |
| issue_is_fw | 用 `map` 记录元素出现的上一次下标，遇到相同元素就合并 | `map` 的使用，合并元素 | 合并过程中元素的更新 | 3星 |
| 永不复行 | 先用数组和布尔数组尝试，后用 `map` 实现 | `map` 的使用，合并元素 | 合并过程中元素的更新 | 2星 |
| hexu2010 | 用优先队列维护点对，分类讨论合并情况 | 优先队列的使用，分类讨论 | 按位置排序输出结果 | 3星 |
| yuheng_wang080904 | 用 `set` 维护下标，优先队列维护小根堆，模拟合并过程 | `set` 和优先队列的使用，模拟合并 | 处理最后一个元素，按顺序输出结果 | 3星 |
| QianianXY | 用两个优先队列，一个维护可能修改的元素，一个维护最终结果 | 优先队列的使用，模拟合并 | 按顺序输出最终结果 | 3星 |
| pengyule | 用优先队列和 `map` 记录元素出现位置，合并相同元素 | 优先队列和 `map` 的使用，合并元素 | 处理元素的更新和删除 | 3星 |

### 所选题解
- **Bitter_Tea（4星）**
  - 关键亮点：思路清晰，代码简洁，使用堆模拟合并过程，重载运算符确保元素按要求排序。
  - 核心代码：
```cpp
struct D{
    ll a;int id;
    bool operator < (const D&x) const	//堆重载运算符应该反着来 
    {
        if(a!=x.a) return a>x.a;
        return id>x.id;
    }
}e,fir,sec;
struct C{int id;ll a;}h[N];
bool cmp(const C&x,const C&y) {return x.id<y.id;}
priority_queue<D> q;
// ...
while(q.size())
{
    fir=q.top();q.pop();
    if(q.empty())	//特判最后一个数 
    {
        h[++tot].a=fir.a;
        h[tot].id=fir.id;
        break;
    }
    sec=q.top();
    if(fir.a==sec.a)
    {
        q.pop();
        e.a=fir.a+sec.a;
        e.id=sec.id;
        q.push(e);
    }
    else
    {
        h[++tot].a=fir.a;
        h[tot].id=fir.id;
    }
}
```
- **ChenJr（4星）**
  - 关键亮点：使用优先队列维护数值和位置，分类讨论合并情况，最后按位置排序输出结果。
  - 核心代码：
```cpp
struct number{//第一个结构体用来输入的数
    ll a;//用来记录数值
    int id;//用来记录位置
    bool operator<(const number &b) const{//优先队列重载
        if(b.a==a){//如果数值相同，则返位置靠前的数
            return b.id<id;
        }
        return b.a<a;//否则返回数值小的
    }
}q[maxn];
struct num{//第二个结构体用来记录答案
    ll ans;//答案的值
    int id;//答案所在的位置
}p[maxn];
bool cmp(num a,num b){//用来使最后的答案按位置升序排序
    return a.id<b.id;
}
// ...
while(que.size()>1){//因为要保证一直可以取到两个数，因此需要满足队列大小大于1，最后再把最后的数pop出即可
    number tmpa=que.top();//取队首第一个数
    que.pop();
    number tmpb=que.top();//取队首第二个数
    que.pop();
    if(tmpa.a!=tmpb.a){//如果两个数不相同，则统计a的答案，重新压入b
        p[cnt].ans=tmpa.a;
        p[cnt++].id=tmpa.id;
        que.push(tmpb);
        continue;
    }
    else if(tmpa.a==tmpb.a){//如果两个数相同，则不对a操作，更新b的值，并将b重新压入优先队列
        tmpb.a=tmpb.a*2;
        que.push(tmpb);
    }
}
```
- **Milmon（4星）**
  - 关键亮点：优先队列存储下标，按对应值排序，代码简洁，实现了合并操作。
  - 核心代码：
```cpp
struct Cmp{
    bool operator()(int x,int y){
        if(a[x]!=a[y])return a[x]>a[y];
        else return x>y;
    }
};
priority_queue<int,vector<int>,Cmp> Q;
vector<int> answer;
// ...
while(Q.size()>=2){
    int x=Q.top(); Q.pop();
    int y=Q.top(); Q.pop();
    if(a[x]==a[y])a[y]<<=1,Q.push(y); // 数值翻倍再放回优先队列
    else Q.push(y),answer.push_back(x); // 直接加入答案序列
}
```

### 最优关键思路或技巧
- **优先队列的使用**：优先队列可以高效地维护数组中的最小元素，方便每次取出最小的元素进行合并操作。
- **重载比较运算符**：通过重载优先队列的比较运算符，可以实现按数值和位置的排序，确保每次取出的元素符合题目要求。
- **`map` 的使用**：`map` 可以记录元素的出现情况，方便在遇到相同元素时进行合并操作。

### 拓展思路
同类型题或类似算法套路：
- 模拟类题目：这类题目通常需要按照题目给定的规则进行模拟操作，关键在于准确实现操作步骤。
- 优先队列的应用：在需要频繁取出最值的问题中，可以考虑使用优先队列来优化时间复杂度。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：也是使用优先队列来合并元素，求最小代价。
- [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)：使用优先队列合并两个有序序列。
- [P2859 [USACO06FEB]Treats for the Cows G](https://www.luogu.com.cn/problem/P2859)：通过模拟操作来求解最优解。

### 个人心得摘录与总结
- **issue_is_fw**：提出“因为这两个相同的数在最左边，迟早要消掉，与顺序无关”，总结出合并操作的顺序不影响最终结果，简化了合并过程。

---
处理用时：72.73秒