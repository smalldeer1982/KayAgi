# 题目信息

# Maxim and Array

## 题目描述

Recently Maxim has found an array of $ n $ integers, needed by no one. He immediately come up with idea of changing it: he invented positive integer $ x $ and decided to add or subtract it from arbitrary array elements. Formally, by applying single operation Maxim chooses integer $ i $ ( $ 1<=i<=n $ ) and replaces the $ i $ -th element of array $ a_{i} $ either with $ a_{i}+x $ or with $ a_{i}-x $ . Please note that the operation may be applied more than once to the same position.

Maxim is a curious minimalis, thus he wants to know what is the minimum value that the product of all array elements (i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721D/ae24ba75281e48338d849938ea05477ca771d520.png)) can reach, if Maxim would apply no more than $ k $ operations to it. Please help him in that.

## 样例 #1

### 输入

```
5 3 1
5 4 3 5 2
```

### 输出

```
5 4 3 5 -1 
```

## 样例 #2

### 输入

```
5 3 1
5 4 3 5 5
```

### 输出

```
5 4 0 5 5 
```

## 样例 #3

### 输入

```
5 3 1
5 4 4 5 5
```

### 输出

```
5 1 4 5 5 
```

## 样例 #4

### 输入

```
3 2 7
5 4 2
```

### 输出

```
5 11 -5 
```

# AI分析结果

### 题目重写
# 马克西姆和数组

## 题目描述
最近，马克西姆发现了一个由 $n$ 个整数组成的、无人问津的数组。他立刻想出了一个改变它的主意：他想出了一个正整数 $x$，并决定对任意数组元素加上或减去 $x$。形式上，通过一次操作，马克西姆选择一个整数 $i$（$1 \leq i \leq n$），并将数组的第 $i$ 个元素 $a_{i}$ 替换为 $a_{i} + x$ 或 $a_{i} - x$。请注意，该操作可以多次应用于同一位置。

马克西姆是个好奇的极简主义者，因此他想知道，如果对数组应用不超过 $k$ 次操作，所有数组元素的乘积（即 $\prod_{i=1}^n a_{i}$）能达到的最小值是多少。请在这方面帮助他。

## 样例 #1
### 输入
```
5 3 1
5 4 3 5 2
```
### 输出
```
5 4 3 5 -1 
```
## 样例 #2
### 输入
```
5 3 1
5 4 3 5 5
```
### 输出
```
5 4 0 5 5 
```
## 样例 #3
### 输入
```
5 3 1
5 4 4 5 5
```
### 输出
```
5 1 4 5 5 
```
## 样例 #4
### 输入
```
3 2 7
5 4 2
```
### 输出
```
5 11 -5 
```

### 算法分类
贪心

### 综合分析与结论
两道题解思路基本一致，均采用贪心策略。思路要点在于先让乘积变为负数（若初始乘积为正数），方法是找到绝对值最小的数并改变其符号，这样能用较小代价使乘积为负。之后，为使乘积的绝对值更大（即乘积更小），每次选择绝对值最小的数，通过加上或减去 $x$ 来增大其绝对值。算法要点是利用优先队列（小根堆）来高效获取绝对值最小的数。解决难点在于理解如何通过贪心策略使得乘积最小，即先变号再增大绝对值小的数的绝对值。

### 所选的题解
- **xzggzh1题解**：
  - **星级**：4星
  - **关键亮点**：思路清晰，代码简洁明了，直接利用优先队列实现核心逻辑。优先队列自定义比较函数，按元素绝对值从小到大排序，方便每次取出绝对值最小的数进行操作。
  - **核心代码**：
```cpp
struct qnode {
    ll v;
    bool operator < (const qnode &r) const {return abs(a[v])>abs(a[r.v]);}
    qnode (ll vv) {v=vv;}
};
int main () {
    n=read();k=read();x=read();
    for (int i=1;i<=n;i++) a[i]=read();
    int cnt=0;for (int i=1;i<=n;i++) if (a[i]<0) cnt++;
    priority_queue<qnode>q;
    for (int i=1;i<=n;i++)q.push(i);
    int tot=0,f=0;
    while (q.size()&&tot<k) {
        qnode tt=q.top();
        q.pop();
        if (a[tt.v]<0) {
            if (cnt%2==0) {
                //负变成正 
                a[tt.v]+=x;
                if (a[tt.v]>=0) cnt--;
            } else a[tt.v]-=x;
        } else {
            if (cnt%2==0) {
                //正变成负 
                a[tt.v]-=x;
                if(a[tt.v]<0) cnt++;
            } else a[tt.v]+=x;
        }
        q.push(tt.v);
        tot++;
    }
    for (int i=1;i<=n;i++) printf("%lld ",a[i]);
}
```
  - **核心实现思想**：自定义结构体qnode，存储数组元素下标，通过重载小于号按元素绝对值从大到小排序（优先队列默认大根堆）。统计初始数组中负数个数cnt，在操作过程中，根据cnt的奇偶性和当前取出元素的正负，决定是加x还是减x来改变元素，以达到先让乘积变负，再增大绝对值小的数的绝对值的目的。
- **Misty_Post题解**：
  - **星级**：4星
  - **关键亮点**：代码逻辑清晰，使用pair类型的优先队列，直观地存储元素绝对值和下标。通过位运算判断正负，代码实现较为简洁。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > q;
ll n,k,x,a[1000000],re[1000000];
int main(){
    ll rep=0;//判断正负，0为正，1为负 
    cin>>n>>k>>x;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<0){
            rep^=1;
            re[i]=-1;//负数 
        }
        else{
            re[i]=1;//正数 
        } 
        q.push({abs(a[i]),i});
    }
    while(1){
        if(q.empty()||!(k)){
            break;
        }
        pair<ll,ll> xx=q.top();
        //cout<<"*"<<xx.first<<" "<<xx.second<<endl;
        q.pop();
        if(a[xx.second]<0){
            if(rep==0){
                a[xx.second]+=x;
                if(a[xx.second]>=0){
                    rep=1;
                }
            }
            else{
                a[xx.second]-=x;
            }
        }
        else{
            if(rep==0){
                a[xx.second]-=x;
                if(a[xx.second]<0){
                    rep=1;
                }
            }
            else{
                a[xx.second]+=x;
            }
        }
        k--;
        q.push({a[xx.second],xx.second});
    }
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }
}
```
  - **核心实现思想**：使用优先队列q，按元素绝对值从小到大排序（通过greater<>指定为小根堆）。rep用于判断当前乘积的正负，在操作过程中，根据rep的值和当前取出元素的正负，决定对元素加x还是减x，以实现先让乘积变负，再增大绝对值小的数的绝对值。

### 最优关键思路或技巧
利用优先队列（小根堆）这一数据结构，能够高效地获取数组中绝对值最小的元素，从而实现贪心策略，每次对绝对值最小的数进行操作，使得乘积最小。

### 拓展思路
同类型题通常围绕通过有限次操作优化某个目标值，类似算法套路是先分析目标值的性质（如本题乘积的正负性），再利用贪心思想确定每次操作的最优选择，常借助优先队列等数据结构辅助实现。

### 洛谷题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，优化结果。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则，利用贪心思想找到最优策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过推导排序规则，运用贪心算法解决问题。 

---
处理用时：62.84秒