# 题目信息

# Concatenation of Arrays

## 题目描述

You are given $ n $ arrays $ a_1 $ , $ \ldots $ , $ a_n $ . The length of each array is two. Thus, $ a_i = [a_{i, 1}, a_{i, 2}] $ . You need to concatenate the arrays into a single array of length $ 2n $ such that the number of inversions $ ^{\dagger} $ in the resulting array is minimized. Note that you do not need to count the actual number of inversions.

More formally, you need to choose a permutation $ ^{\ddagger} $ $ p $ of length $ n $ , so that the array $ b = [a_{p_1,1}, a_{p_1,2}, a_{p_2, 1}, a_{p_2, 2}, \ldots, a_{p_n,1}, a_{p_n,2}] $ contains as few inversions as possible.

 $ ^{\dagger} $ The number of inversions in an array $ c $ is the number of pairs of indices $ i $ and $ j $ such that $ i < j $ and $ c_i > c_j $ .

 $ ^{\ddagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, we concatenated the arrays in the order $ 2, 1 $ . Let's consider the inversions in the resulting array $ b = [2, 3, 1, 4] $ :

- $ i = 1 $ , $ j = 3 $ , since $ b_1 = 2 > 1 = b_3 $ ;
- $ i = 2 $ , $ j = 3 $ , since $ b_2 = 3 > 1 = b_3 $ .

Thus, the number of inversions is $ 2 $ . It can be proven that this is the minimum possible number of inversions.

In the second test case, we concatenated the arrays in the order $ 3, 1, 2 $ . Let's consider the inversions in the resulting array $ b = [2, 1, 3, 2, 4, 3] $ :

- $ i = 1 $ , $ j = 2 $ , since $ b_1 = 2 > 1 = b_2 $ ;
- $ i = 3 $ , $ j = 4 $ , since $ b_3 = 3 > 2 = b_4 $ ;
- $ i = 5 $ , $ j = 6 $ , since $ b_5 = 4 > 3 = b_6 $ .

Thus, the number of inversions is $ 3 $ . It can be proven that this is the minimum possible number of inversions.

In the third test case, we concatenated the arrays in the order $ 4, 2, 1, 5, 3 $ .

## 样例 #1

### 输入

```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20```

### 输出

```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20```

# AI分析结果

### 题目内容重写

#### 数组的拼接

**题目描述**

给定 $n$ 个数组 $a_1, \ldots, a_n$，每个数组的长度为 2，即 $a_i = [a_{i,1}, a_{i,2}]$。你需要将这些数组拼接成一个长度为 $2n$ 的数组，使得最终数组中的逆序对数量尽可能少。注意，你不需要计算实际的逆序对数量。

更正式地，你需要选择一个长度为 $n$ 的排列 $p$，使得数组 $b = [a_{p_1,1}, a_{p_1,2}, a_{p_2,1}, a_{p_2,2}, \ldots, a_{p_n,1}, a_{p_n,2}]$ 中的逆序对数量尽可能少。

**说明/提示**

- 逆序对的定义：在数组 $c$ 中，逆序对是指满足 $i < j$ 且 $c_i > c_j$ 的索引对 $(i, j)$。
- 排列的定义：长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。

**样例**

输入：
```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20
```

输出：
```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20
```

### 题解分析与结论

#### 题解对比与评分

1. **作者：Eddie08012025 (3星)**
   - **思路**：通过比较每个数组的最大值和数组元素的和，确定排列顺序，以减少逆序对数量。
   - **难点**：需要证明这种排序方式能够最小化逆序对数量。
   - **代码实现**：使用 `sort` 函数进行排序，比较函数复杂。
   - **评分**：3星，思路清晰但代码实现较为复杂，且未完全证明其正确性。

2. **作者：zengxuheng (4星)**
   - **思路**：提出了三种排序方式，并通过反例证明了第一种方式的错误性，最终选择第二种和第三种方式。
   - **难点**：需要证明排序方式的传递性和正确性。
   - **代码实现**：使用 `sort` 函数，代码简洁。
   - **评分**：4星，思路清晰，代码简洁，且通过反例证明了某些排序方式的错误性。

3. **作者：aeiouaoeiu (4星)**
   - **思路**：通过将二元组的最小值和最大值作为排序的关键字，确定排列顺序。
   - **难点**：需要证明这种排序方式能够最小化逆序对数量。
   - **代码实现**：使用 `sort` 函数，代码简洁。
   - **评分**：4星，思路清晰，代码简洁，且通过分类讨论证明了排序方式的正确性。

#### 最优关键思路

- **排序策略**：通过比较二元组的最小值和最大值，确定排列顺序，以减少逆序对数量。
- **实现技巧**：使用 `sort` 函数，自定义比较函数，简洁高效。

#### 可拓展之处

- **类似问题**：可以扩展到多维数组的拼接问题，或者更复杂的逆序对最小化问题。
- **算法套路**：贪心算法、排序算法。

#### 推荐题目

1. **P1080 国王游戏**：考察贪心算法和排序策略。
2. **ABC366F**：考察逆序对的最小化问题。
3. **P1908 逆序对**：考察逆序对的计算和优化。

#### 个人心得摘录

- **作者：zengxuheng**：通过反例证明了某些排序方式的错误性，强调了贪心算法的传递性。
- **作者：aeiouaoeiu**：通过分类讨论证明了排序方式的正确性，强调了排序策略的重要性。

### 精选题解代码

#### 作者：zengxuheng

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> a[100010];
inline int read() {
    int x=0,f=1;
    char ch=getchar();
    while (ch<48||ch>57) {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>=48&&ch<=57) {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*f;
}

template<typename T>
inline void write(T x,int f=1) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10,0);
    putchar(x%10+'0');
    if(f==1)putchar('\n');
    if(f==2) putchar(' ');
    return;
}

bool cmp(pair<int,int> x,pair<int,int> y) {
    int a=x.first,a1=x.second,b=y.first,b1=y.second;
    int maxn=max({a,a1,b,b1});
    if((a==maxn||a1==maxn)&&(b==maxn||b1==maxn)) return (a+a1)<(b+b1);
    else if(a==maxn||a1==maxn) return 0;
    else if(b==maxn||b1==maxn) return 1;
}
int  main() {
    int t=read();
    while(t--) {
        int n=read();
        int cnt=0;
        for(register int i = 1; i <= n; i++) a[i]= {read(),read()};
        sort(a+1,a+n+1,cmp);
        for(register int i = 1; i <= n; i++) cout<<a[i].first<<' '<<a[i].second<<' ';
        cout<<'\n';
    }
    return 0;
}
```

#### 作者：aeiouaoeiu

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef __int128 LL;
const ll maxn=200007,ee=1e18;
ll n,a[maxn][2],mn[maxn],mx[maxn],id[maxn];
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T=1; cin>>T;
    for(;T--;){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i][0]>>a[i][1],id[i]=i;
            mn[i]=min(a[i][0],a[i][1]),mx[i]=max(a[i][0],a[i][1]);
        }
        sort(id+1,id+1+n,[&](ll x,ll y){
            if(mn[x]==mn[y]) return mx[x]<mx[y];
            else return mn[x]<mn[y];
        });
        for(int i=1;i<=n;i++) cout<<a[id[i]][0]<<" "<<a[id[i]][1]<<" "; cout<<"\n";
    }
    return 0;
}
```

---
处理用时：49.38秒