# 题目信息

# [ARC160A] Reverse and Count

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc160/tasks/arc160_a

$ (1,\ 2,\ \dots,\ N) $ の順列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ が与えられます。  
 $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たす整数の組 $ (L,\ R) $ に対して、$ A $ の $ L $ 番目から $ R $ 番目までの要素を反転してできる順列を $ f(L,\ R) $ とします。  
 ここで、「$ A $ の $ L $ 番目から $ R $ 番目までの要素を反転する」とは、$ A_L,\ A_{L+1},\ \dots,\ A_{R-1},\ A_R $ を $ A_R,\ A_{R-1},\ \dots,\ A_{L+1},\ A_{L} $ に同時に置き換えることを言います。

$ (L,\ R) $ を $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たすように選ぶ方法は $ \frac{N(N\ +\ 1)}{2} $ 通りあります。  
 このような $ (L,\ R) $ の組全てに対して順列 $ f(L,\ R) $ をすべて列挙して辞書順にソートしたときに、先頭から $ K $ 番目にある順列を求めてください。

  数列の辞書順とは？数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $
  - $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 7000 $
- $ 1\ \leq\ K\ \leq\ \frac{N(N\ +\ 1)}{2} $
- $ A $ は $ (1,\ 2,\ \dots,\ N) $ の順列
 
### Sample Explanation 1

$ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たす $ (L,\ R) $ の組全てに対して順列 $ f(L,\ R) $ をすべて列挙すると次のようになります。 - $ f(1,\ 1)\ =\ (1,\ 3,\ 2) $ - $ f(1,\ 2)\ =\ (3,\ 1,\ 2) $ - $ f(1,\ 3)\ =\ (2,\ 3,\ 1) $ - $ f(2,\ 2)\ =\ (1,\ 3,\ 2) $ - $ f(2,\ 3)\ =\ (1,\ 2,\ 3) $ - $ f(3,\ 3)\ =\ (1,\ 3,\ 2) $ これらを辞書順にソートしたときに $ 5 $ 番目に来る順列は $ f(1,\ 3)\ =\ (2,\ 3,\ 1) $ です。よってこれを出力します。

### Sample Explanation 2

答えは $ f(1,\ 5) $ です。

## 样例 #1

### 输入

```
3 5

1 3 2```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
5 15

1 2 3 4 5```

### 输出

```
5 4 3 2 1```

## 样例 #3

### 输入

```
10 37

9 2 1 3 8 7 10 4 5 6```

### 输出

```
9 2 1 6 5 4 10 7 8 3```

# AI分析结果

### 题目翻译
给定一个 $(1, 2, \dots, N)$ 的排列 $A = (A_1, A_2, \dots, A_N)$。
对于满足 $1 \leq L \leq R \leq N$ 的整数对 $(L, R)$，将 $A$ 的第 $L$ 个到第 $R$ 个元素反转后得到的排列记为 $f(L, R)$。
这里，“将 $A$ 的第 $L$ 个到第 $R$ 个元素反转” 是指将 $A_L, A_{L + 1}, \dots, A_{R - 1}, A_R$ 同时替换为 $A_R, A_{R - 1}, \dots, A_{L + 1}, A_{L}$。

满足 $1 \leq L \leq R \leq N$ 的 $(L, R)$ 组合共有 $\frac{N(N + 1)}{2}$ 种。
将所有这样的 $(L, R)$ 组合对应的排列 $f(L, R)$ 全部列出并按字典序排序后，求从开头数第 $K$ 个排列。

数列的字典序定义：数列 $S = (S_1, S_2, \ldots, S_{|S|})$ 在字典序上小于数列 $T = (T_1, T_2, \ldots, T_{|T|})$ 是指以下两种情况之一成立。这里，$|S|$ 和 $|T|$ 分别表示 $S$ 和 $T$ 的长度。
1. $|S| < |T|$ 且 $(S_1, S_2, \ldots, S_{|S|}) = (T_1, T_2, \ldots, T_{|S|})$。
2. 存在一个整数 $1 \leq i \leq \min\{ |S|, |T| \}$，使得以下两个条件同时成立：
  - $(S_1, S_2, \ldots, S_{i - 1}) = (T_1, T_2, \ldots, T_{i - 1})$
  - $S_i$ 在数值上小于 $T_i$。

### 综合分析与结论
这些题解主要围绕如何高效求出所有翻转区间得到的排列中字典序第 $K$ 小的排列。大部分题解的时间复杂度在 $O(n^2)$ 或 $O(n \log n)$ 。

思路上，主要有两种方向：一是通过比较不同翻转区间对应的排列的字典序，利用 `nth_element` 函数直接找到第 $K$ 小的排列；二是从左到右考虑每一位，根据不同的翻转情况计算方案数，逐步确定第 $K$ 小的排列。

算法要点方面，涉及到排列的翻转、字典序比较、计数以及使用数据结构（如树状数组）辅助计算。

解决的难点在于如何高效地比较不同翻转区间对应的排列的字典序，以及在不枚举所有排列的情况下找到第 $K$ 小的排列。

### 所选题解
- **作者：SqrtSecond (赞：8)，4星**
    - **亮点**：思路清晰，详细说明了如何比较不同翻转区间对应的排列的字典序，并巧妙地使用 `nth_element` 函数在 $O(n^2)$ 时间复杂度内解决问题，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[7010],cnt;
struct node{int l,r;}b[25000000],ans;
bool operator <(node b,node c)
{
	if(b.l==c.l)return a[b.r]<a[c.r];
	if((b.l<c.l&&b.l!=b.r)||c.l==c.r)return a[b.r]<a[b.l];
	return a[c.l]<a[c.r];
}
signed main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		for(int j=i;j<=n;++j)b[++cnt]={i,j};
	}
	nth_element(b+1,b+k,b+cnt+1);
	reverse(a+b[k].l,a+b[k].r+1);
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
```
    - **核心实现思想**：定义结构体 `node` 存储翻转区间的左右端点，重载 `<` 运算符来比较不同翻转区间对应的排列的字典序。将所有可能的翻转区间存储在数组 `b` 中，使用 `nth_element` 函数找到第 $K$ 小的翻转区间，最后对原数组进行相应的翻转并输出。

- **作者：Hypercube (赞：7)，4星**
    - **亮点**：先特判 $l = r$ 的情况，然后从左到右考虑每一位是否作为翻转区间的左端点，通过计算比当前位置小和大的数的个数来确定第 $K$ 小的排列，精细实现可以达到 $O(n \log n)$ 的时间复杂度。
    - **核心代码**：
```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,k,cnt,p[200005],p1[200005],p2[200005];
struct pri {int num,p;};
bool operator < (pri a,pri b) {return a.num<b.num;}
priority_queue <pri> q;
struct BIT {
    int c[200005];
    int lowbit(int x) {return x&(-x);}
    void add(int x) {for(; x<=n; x+=lowbit(x)) c[x]++;}
    int Query(int x) {if(!x) return 0;int ans=0;for(; x; x-=lowbit(x)) ans+=c[x];return ans;}
    int query(int l,int r) {return Query(r)-Query(l-1);}
} bit;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0); 
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>p[i];
    for(int i=n; i>=1; i--) {
        p1[i]=bit.query(1,p[i]);
        p2[i]=bit.query(p[i],n);
        bit.add(p[i]);
        cnt+=p1[i];
    }
    if(k>cnt&&k<=cnt+n) {
        for(int i=1; i<=n; i++) cout<<p[i]<<' ';
        cout<<'\n';
        return 0;
    }
    if(k>cnt+n) k-=n;
    for(int i=1; i<=n; i++) {
        int num1=p1[i],num2=p2[i],num=(n-i)*(n-i-1)/2;
        if(k<=num1) {
            for(int j=i+1; j<=n; j++) q.push((pri) {
                -p[j],j
            });
            for(int j=1; j<k; j++) q.pop();
            for(int j=1; j<i; j++) cout<<p[j]<<' ';
            for(int j=q.top().p; j>=i; j--) cout<<p[j]<<' ';
            for(int j=q.top().p+1; j<=n; j++) cout<<p[j]<<' ';
            cout<<'\n';
            return 0;
        } else if(k>num1+num) {
            k-=(num1+num);
            k=(num2-k+1);
            for(int j=i+1; j<=n; j++) q.push((pri) {
                p[j],j
            });
            for(int j=1; j<k; j++) q.pop();
            for(int j=1; j<i; j++) cout<<p[j]<<' ';
            for(int j=q.top().p; j>=i; j--) cout<<p[j]<<' ';
            for(int j=q.top().p+1; j<=n; j++) cout<<p[j]<<' ';
            cout<<'\n';
            return 0;
        } else {
            k-=num1;
        }
    }
    return 0;
}
```
    - **核心实现思想**：使用树状数组 `BIT` 计算每个位置后面比它小和大的数的个数。先特判 $k$ 在原序列排名范围内的情况，然后从左到右考虑每一位，根据 $k$ 的值判断是否以当前位为左端点进行翻转，通过优先队列找到合适的翻转区间并输出结果。

### 最优关键思路或技巧
- **字典序比较优化**：通过分析排列的特点，直接比较翻转区间的端点值来确定字典序大小，避免了对整个排列进行比较。
- **使用 `nth_element` 函数**：该函数可以在 $O(n)$ 平均时间复杂度内找到序列的第 $K$ 小元素，避免了对所有元素进行排序。
- **从左到右逐步确定**：从左到右考虑每一位，根据不同的翻转情况计算方案数，逐步缩小范围，确定第 $K$ 小的排列。

### 可拓展之处
同类型题目可能会改变排列的操作方式（如旋转、交换等），或者改变排序规则（如逆字典序等）。类似的算法套路可以应用在需要在大量排列或组合中找到特定排名元素的问题中，关键在于高效地比较元素的大小和利用数据结构辅助计算。

### 推荐洛谷题目
1. [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)
2. [P1138 第 k 小整数](https://www.luogu.com.cn/problem/P1138)
3. [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)

### 个人心得
这些题解中未包含明显的个人心得内容。 

---
处理用时：61.00秒