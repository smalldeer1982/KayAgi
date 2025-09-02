# 题目信息

# Maximum Xor Secondary

## 题目描述

Bike loves looking for the second maximum element in the sequence. The second maximum element in the sequence of distinct numbers $ x_{1},x_{2},...,x_{k} $ $ (k&gt;1) $ is such maximum element $ x_{j} $ , that the following inequality holds: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280B/cbffb592db1e3f6cc63c23bba8878833c080a3b3.png).

The lucky number of the sequence of distinct positive integers $ x_{1},x_{2},...,x_{k} $ $ (k&gt;1) $ is the number that is equal to the bitwise excluding OR of the maximum element of the sequence and the second maximum element of the sequence.

You've got a sequence of distinct positive integers $ s_{1},s_{2},...,s_{n} $ $ (n&gt;1) $ . Let's denote sequence $ s_{l},s_{l+1},...,s_{r} $ as $ s[l..r] $ $ (1<=l&lt;r<=n) $ . Your task is to find the maximum number among all lucky numbers of sequences $ s[l..r] $ .

Note that as all numbers in sequence $ s $ are distinct, all the given definitions make sence.

## 说明/提示

For the first sample you can choose $ s[4..5]={4,3} $ and its lucky number is $ (4 xor 3)=7 $ . You can also choose $ s[1..2] $ .

For the second sample you must choose $ s[2..5]={8,3,5,7} $ .

## 样例 #1

### 输入

```
5
5 2 1 4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5
9 8 3 5 7
```

### 输出

```
15
```

# AI分析结果

### 题目内容
# 最大异或次大值

## 题目描述
Bike喜欢在序列中寻找次大元素。对于由不同数字$x_{1},x_{2},\cdots,x_{k}$（$k > 1$）组成的序列，次大元素$x_{j}$满足不等式：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280B/cbffb592db1e3f6cc63c23bba8878833c080a3b3.png)。

由不同正整数$x_{1},x_{2},\cdots,x_{k}$（$k > 1$）组成的序列的幸运数，等于该序列中最大元素与次大元素的按位异或值。

给定一个由不同正整数$s_{1},s_{2},\cdots,s_{n}$（$n > 1$）组成的序列。记序列$s_{l},s_{l + 1},\cdots,s_{r}$为$s[l..r]$（$1 \leq l < r \leq n$）。你的任务是找出所有序列$s[l..r]$的幸运数中的最大值。

注意，由于序列$s$中的所有数字都不同，所有给定的定义都是有意义的。

## 说明/提示
对于第一个样例，你可以选择$s[4..5] = \{4, 3\}$，其幸运数为$(4 \text{ xor } 3) = 7$。你也可以选择$s[1..2]$。

对于第二个样例，你必须选择$s[2..5] = \{8, 3, 5, 7\}$。

## 样例 #1
### 输入
```
5
5 2 1 4 3
```
### 输出
```
7
```

## 样例 #2
### 输入
```
5
9 8 3 5 7
```
### 输出
```
15
```

### 算法分类
单调栈

### 综合分析与结论
这些题解的核心思路大多是通过枚举次大值，利用单调栈找到其左右两侧第一个比它大的数（即可能的最大值），然后计算这些组合的异或值，并取其中的最大值。难点在于理解为什么枚举次大值而不是最大值，以及如何正确使用单调栈维护数据。若枚举最大值，次大值的确定需要考虑区间内所有数的关系，时间复杂度为$O(n^2)$，而枚举次大值，利用单调栈可将时间复杂度优化到$O(n)$。

### 所选的题解
- **作者：Egg_eating_master (赞：8)  星级：4星  关键亮点：思路清晰，代码简洁明了，详细解释了单调栈的使用过程，适合初学者理解。**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
stack<int>s;
int ans=-1e9;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++){
        while(!s.empty()&&s.top()<a[i])s.pop();//维护单调栈，找到距离a[i]最近的大于a[i]的数
        if(!s.empty())ans=max(ans,s.top()^a[i]);//答案打擂台取最大值
        s.push(a[i]);
    }
    while(!s.empty())s.pop();
    for(int i=n;i>=1;i--){//同上
        while(!s.empty()&&s.top()<a[i])s.pop();
        if(!s.empty())ans=max(ans,s.top()^a[i]);
        s.push(a[i]);
    }
    cout<<ans<<endl;
    return 0;
} 
```
核心实现思想：先正向遍历数组，利用单调栈找到每个数左边最近的比它大的数，并计算异或值更新答案；然后反向遍历数组，重复上述操作，最终得到所有子序列中最大与次大值异或的最大值。

- **作者：liuyifan (赞：1)  星级：4星  关键亮点：代码注释详细，对单调栈的维护和边界处理讲解清晰，且考虑了左右端点的特判。**
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3fll//注意后缀ll,不加可能会死得惨烈
using namespace std;
ll n,a[1000005],l[1000005],r[1000005],maxx=-iinf;
stack<ll>s1,s2;//使用STL栈维护
int main()
{
    scanf("%lld",&n);
    for(reg int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(reg int i=n;i>=1;i--)
    {
        while(s1.empty()==0&&a[s1.top()]<a[i])s1.pop();//弹出违背单调性的点
        l[i]=s1.empty()?n+1ll:s1.top();//如果栈空了的特殊处理
        s1.push(i);//加入栈
    }//维护单调递减栈
    for(reg int i=1;i<=n;i++)//注意循环顺序的区别
    {
        while(s2.empty()==0&&a[s2.top()]<a[i])s2.pop();
        r[i]=s2.empty()?0ll:s2.top();
        s2.push(i);//操作流程大体同上
    }//维护单调递增栈
    for(reg int i=1;i<=n;i++)
    {
        if(l[i]!=n+1)maxx=max(maxx,a[i]^a[l[i]]);
        if(r[i])maxx=max(maxx,a[i]^a[r[i]]);
    }//求最大异或值
    //C++ ^运算符为按位异或,直接用就行了
    printf("%lld",maxx);//输出答案
    return 0;
}
```
核心实现思想：先反向遍历数组构建单调递减栈，记录每个数左边第一个比它大的数的位置；再正向遍历数组构建单调递减栈，记录每个数右边第一个比它大的数的位置；最后遍历所有数，计算其与左右两侧比它大的数的异或值，取最大值。

### 最优关键思路或技巧
通过枚举次大值，利用单调栈在$O(n)$时间复杂度内找到其左右两侧第一个比它大的数，从而避免了暴力枚举所有子序列带来的$O(n^2)$时间复杂度。这种思维方式巧妙地将复杂的子序列最值问题转化为利用单调栈维护局部最值的问题。

### 可拓展之处
此类题目属于单调栈在序列最值关系求解的应用。类似套路可用于求解一些需要在序列中找到特定大小关系元素组合，并对这些组合进行某种运算求最值的问题。例如，寻找序列中相邻的最大和次大元素的乘积最大值等。

### 洛谷相似题目推荐
- [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)：基础的单调栈练习题，帮助理解单调栈的基本应用。
- [P3949 宝藏](https://www.luogu.com.cn/problem/P3949)：需要利用单调栈优化暴力枚举，与本题通过单调栈优化子序列相关计算的思路类似。
- [P4185 [USACO18JAN]MooTube G](https://www.luogu.com.cn/problem/P4185)：在处理区间问题时，借助单调栈思想优化算法，可锻炼对单调栈应用场景的拓展理解。 

---
处理用时：70.67秒