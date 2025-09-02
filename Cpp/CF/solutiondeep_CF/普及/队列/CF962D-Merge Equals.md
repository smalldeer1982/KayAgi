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

### 题目中文重写
## 合并相等元素

### 题目描述
给定一个正整数数组。只要数组中至少有两个相等的元素，我们就会执行以下操作。我们选择数组中出现 2 次或更多次的最小的值 $x$。取该数组中 $x$ 的前两个出现位置（最左边的两个出现位置）。移除这两个位置中左边的那个，右边的那个替换为这两个值的和（即 $2 \cdot x$）。

确定经过上述操作后数组的最终状态。

例如，考虑给定的数组为 $ [3, 4, 1, 2, 2, 1, 1] $。它将按以下方式变化：$ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $。

如果给定的数组为 $ [1, 1, 3, 1, 1] $，它将按以下方式变化：$ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $。

### 说明/提示
前两个示例在题目描述中已给出。

在第三个示例中，给定数组中的所有整数都是不同的，因此数组不会发生变化。

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
这些题解的核心思路都是模拟数组元素的合并过程，关键在于如何高效地找出最小且重复的元素并进行合并。大部分题解使用优先队列（堆）来维护元素，利用其特性快速获取最小元素。部分题解使用 `map` 记录元素出现的位置，简化合并操作。

### 所选题解
- **作者：Bitter_Tea（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用优先队列模拟合并过程，重载运算符保证元素按要求排序，最后对结果按位置排序输出。
    - **核心代码**：
```cpp
struct D{
    ll a;int id;
    bool operator < (const D&x) const	//堆重载运算符应该反着来 
    {
        if(a!=x.a) return a>x.a;
        return id>x.id;
    }
};
priority_queue<D> q;
while(q.size())
{
    fir=q.top();q.pop();
    if(q.empty())	
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
sort(h+1,h+tot+1,cmp);
```
- **作者：chenxia25（4星）**
    - **关键亮点**：提供两种方法，方法一使用优先队列模拟，方法二通过去除因数 2 进行分类排序，时间复杂度低且常数小。
    - **核心代码（方法一）**：
```cpp
struct cmp{
    bool operator()(pair<int,int> x,pair<int,int> y){
        if(x.first!=y.first)return x.first>y.first;
        return x.second>y.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp> q;
while(q.size()>1){
    int x1=q.top().first,y1=q.top().second;q.pop();
    int x2=q.top().first,y2=q.top().second;
    if(x1==x2)q.pop(),q.push(make_pair(x1<<1,y2));
    else q0.push(make_pair(x1,y1));
}
q0.push(q.top());
```
- **作者：ChenJr（4星）**
    - **关键亮点**：详细解释题意和思路，使用优先队列维护数值和位置，对不同情况分类处理，最后按位置排序输出结果。
    - **核心代码**：
```cpp
struct number{
    ll a;
    int id;
    bool operator<(const number &b) const{
        if(b.a==a){
            return b.id<id;
        }
        return b.a<a;
    }
};
priority_queue<number> que;
while(que.size()>1){
    number tmpa=que.top();
    que.pop();
    number tmpb=que.top();
    que.pop();
    if(tmpa.a!=tmpb.a){
        p[cnt].ans=tmpa.a;
        p[cnt++].id=tmpa.id;
        que.push(tmpb);
        continue;
    }
    else if(tmpa.a==tmpb.a){
        tmpb.a=tmpb.a*2;
        que.push(tmpb);
    }
}
sort(p,p+cnt,cmp);
```

### 最优关键思路或技巧
- 使用优先队列（堆）维护元素，能高效获取最小元素，时间复杂度为 $O(n\log n)$。
- 重载运算符，使优先队列按数值和位置排序，满足题目要求。
- 利用 `map` 记录元素出现的位置，简化合并操作。

### 可拓展之处
同类型题可考虑元素合并规则变化、元素类型变化等，类似算法套路可用于处理需要频繁获取最值并进行操作的问题。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察优先队列的使用，通过合并果子的过程计算最小代价。
- [P3958 奶酪](https://www.luogu.com.cn/problem/P3958)：可以使用优先队列优化搜索过程，找到满足条件的路径。
- [P1323 删数问题](https://www.luogu.com.cn/problem/P1323)：通过优先队列维护元素，模拟删数过程，找到最小的数。

### 个人心得摘录与总结
- **作者：pengyule**：在洛谷提交一直处于 waiting 状态，最终在 Codeforces 上 AC。详细解释思路，通过优先队列和 `map` 实现元素合并，强调不需要判断元素出现次数的奇偶性。总结为在不同平台提交代码可能会有不同结果，解题时要深入理解题意，简化实现过程。 

---
处理用时：41.78秒