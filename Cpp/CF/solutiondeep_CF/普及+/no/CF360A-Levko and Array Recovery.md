# 题目信息

# Levko and Array Recovery

## 题目描述

Levko loves array $ a_{1},a_{2},...\ ,a_{n} $ , consisting of integers, very much. That is why Levko is playing with array $ a $ , performing all sorts of operations with it. Each operation Levko performs is of one of two types:

1. Increase all elements from $ l_{i} $ to $ r_{i} $ by $ d_{i} $ . In other words, perform assignments $ a_{j}=a_{j}+d_{i} $ for all $ j $ that meet the inequation $ l_{i}<=j<=r_{i} $ .
2. Find the maximum of elements from $ l_{i} $ to $ r_{i} $ . That is, calculate the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360A/b8abcd9e917cd04eb743a84b9d9be23896e61fc8.png).

Sadly, Levko has recently lost his array. Fortunately, Levko has records of all operations he has performed on array $ a $ . Help Levko, given the operation records, find at least one suitable array. The results of all operations for the given array must coincide with the record results. Levko clearly remembers that all numbers in his array didn't exceed $ 10^{9} $ in their absolute value, so he asks you to find such an array.

## 样例 #1

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 8
```

### 输出

```
YES
4 7 4 7```

## 样例 #2

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 13
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Levko和数组恢复

## 题目描述
Levko非常喜欢由整数组成的数组\(a_{1},a_{2},\cdots,a_{n}\)。这就是为什么Levko会对数组\(a\)进行各种操作。Levko执行的每个操作属于以下两种类型之一：
1. 将从\(l_{i}\)到\(r_{i}\)的所有元素增加\(d_{i}\)。换句话说，对所有满足不等式\(l_{i}\leq j\leq r_{i}\)的\(j\)执行赋值\(a_{j}=a_{j}+d_{i}\)。
2. 找到从\(l_{i}\)到\(r_{i}\)的元素中的最大值。即，计算值\(\max_{l_{i}\leq j\leq r_{i}}a_{j}\)。

遗憾的是，Levko最近丢失了他的数组。幸运的是，Levko记录了他对数组\(a\)执行的所有操作。请帮助Levko，根据操作记录找到至少一个合适的数组。对于给定数组的所有操作结果必须与记录结果一致。Levko清楚地记得他数组中的所有数字的绝对值都不超过\(10^{9}\)，所以他要求你找到这样一个数组。

## 样例 #1
### 输入
```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 8
```
### 输出
```
YES
4 7 4 7
```

## 样例 #2
### 输入
```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 13
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
该题解的核心思路是通过维护每个元素当前的增量\(add_i\)和初始最大值\(mx_i\)来解决问题。在第一次遍历操作序列时，对于操作二，通过\(mx_j\gets \min(mx_j,m_i - add_j)\)更新每个元素的初始最大值。第二次遍历操作序列时，对于操作二，检查当前区间内元素的实际最大值是否与记录的最大值相等，若不相等则报告无解，若遍历完所有操作都未出现无解情况，则输出\(mx_{1...n}\)作为构造的序列。该题解思路清晰，代码实现较为直接，能够有效解决问题。

### 所选的题解
- **星级**：4星
  - **关键亮点**：通过两次遍历操作序列，巧妙地利用增量和初始最大值的维护来构造数组或判断无解，思路简洁明了。
  - **重点代码核心实现思想**：第一次遍历操作序列时，根据操作类型分别更新增量数组\(add\)和初始最大值数组\(mx\)。第二次遍历操作序列时，再次根据操作类型更新增量数组\(add\)，并检查操作二的结果是否符合记录。若符合则继续，不符合则报告无解。最后若所有操作都通过检查，则输出构造的数组。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5005;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
int mx[N],add[N];
struct query{
  int op,l,r,x;
}q[N];
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  memset(mx,0x3f,sizeof(mx));
  for(int i=1;i<=m;i++){
    q[i]=(query){(int)read(),(int)read(),(int)read(),(int)read()};
    if(q[i].op==1){
      for(int j=q[i].l;j<=q[i].r;j++) add[j]+=q[i].x;
    }
    else{
      for(int j=q[i].l;j<=q[i].r;j++) mx[j]=min(mx[j],q[i].x-add[j]);
    }
  }
  memset(add,0,sizeof(add));
  for(int i=1;i<=m;i++){
    if(q[i].op==1){
      for(int j=q[i].l;j<=q[i].r;j++) add[j]+=q[i].x;
    }
    else{
      int o=-2e9;
      for(int j=q[i].l;j<=q[i].r;j++) o=max(o,mx[j]+add[j]);
      if(o!=q[i].x){
	printf("NO\n");return 0;
      }
      //printf("i=%d o=%d\n",i,o);
    }
  }
  printf("YES\n");
  for(int i=1;i<=n;i++) printf("%d ",min(mx[i],1000000000));
  return 0;
}
```
### 最优关键思路或技巧
通过引入两个辅助数组分别记录元素的增量和初始最大值，利用两次遍历操作序列的方式，将构造数组和判断无解的过程巧妙结合，简化了问题的解决流程。

### 可拓展之处
此类题目属于构造类型题目，通常需要根据给定的条件和操作，构造出满足要求的数据结构。类似的题目套路还包括根据特定的操作规则构造图、树等数据结构。解决这类问题的关键在于深入理解操作规则对数据结构的影响，并通过合理的数据维护方式来实现构造或判断可行性。

### 洛谷相似题目推荐
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找与统计，可锻炼对字符串操作和条件判断的能力。
 - [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟开关灯的操作，理解状态变化与条件判断，与本题构造数组并验证结果的思路有相似之处。
 - [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及到对排列的操作与构造，与本题根据操作构造数组的思路类似，可锻炼构造和验证数据的能力。 

---
处理用时：60.97秒