# [ARC134D] Concatenate Subsequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc134/tasks/arc134_d

長さ $ 2N $ の数列 $ a $ が与えられます。

すぬけ君が $ (1,2,\ \ldots,\ N) $ の**空でない**（連続するとは限らない）部分列 $ x=(x_1,x_2,\ldots,x_k) $ を用いて、数列を作ろうとしています。 作られる数列は、$ a $ の $ x_1 $ 番目、$ x_2 $ 番目、$ \ldots $、$ x_k $ 番目、$ x_{1}+N $ 番目、$ \ldots $、$ x_{k}+N $ 番目の要素を抜き出してこの順で連結した数列です。

すぬけ君が作ることができる数列のうち、辞書順最小のものを求めてください。

 数列の辞書順とは？ 相異なる数列 $ S $ と数列 $ T $ の大小を判定するアルゴリズムを以下に説明します。

以下では $ S $ の $ i $ 番目の要素を $ S_i $ のように表します。また、 $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と表します。

1. $ S $ と $ T $ のうち長さが短い方の数列の長さを $ L $ とします。$ i=1,2,\dots,L $ に対して $ S_i $ と $ T_i $ が一致するか調べます。
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合、そのような $ i $ のうち最小のものを $ j $ とします。そして、$ S_j $ と $ T_j $ を比較して、 $ S_j $ が $ T_j $ より（数として）小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合、 $ S $ と $ T $ の長さを比較して、$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ 、長い場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

\- $ x\ =\ (2) $ とします。 - このとき、作られる数列は $ (1,2) $ となり辞書順最小です。

## 样例 #1

### 输入

```
3
2 1 3 1 2 2```

### 输出

```
1 2```

## 样例 #2

### 输入

```
10
38 38 80 62 62 67 38 78 74 52 53 77 59 83 74 63 80 61 68 55```

### 输出

```
38 38 38 52 53 77 80 55```

## 样例 #3

### 输入

```
12
52 73 49 63 55 74 35 68 22 22 74 50 71 60 52 62 65 54 70 59 65 54 60 52```

### 输出

```
22 22 50 65 54 52```

# 题解

## 作者：灵茶山艾府 (赞：6)

设输入的数组为 $A$。对于**字典序最小子序列问题**，通常用单调栈解决：从左往右遍历 $A$，把 $A[i]$ 入栈，入栈前，把栈中大于 $A[i]$ 的数都弹出。这样最后可以得到一个字典序最小且递增的序列。

求出 $A$ 的前 $n$ 个数的最小字典序，记作数组 $a$。此时后 $n$ 个数中的剩余元素，记作数组 $b$。

那么当前剩余元素组成的序列就是 $a+b$。接下来，看看能否得到比 $a+b$ 更小的字典序。

下面的讨论，下标从 $0$ 开始。

设 $\textit{mn}$ 为满足 $a[i]=a[0]$ 的 $b[i]$ 的最小值，分类讨论：

- 如果 $\textit{mn}\le a[0]$，例如 $a=[2,2,3,3],\ b=[3,1,2,4]$，我们只需要保留 $a[1]$ 和 $b[1]$ 即可，组成最小字典序 $[2,1]$。
- 如果 $\textit{mn}> a[0]$，继续分类讨论：
    - 例如 $a=[2,2,2,4,4,5,6],\ b=[4,3,\cdots]$，无论 $\cdots$ 是什么数，我们都可以把 $a$ 中 $4$ 以及后面的数字去掉，从而得到更小的字典序。
    - 例如 $a=[2,2,2,4,4,5,6],\ b=[4,7,\cdots]$，无论 $\cdots$ 是什么数，我们都可以把 $a$ 中 $5$ 以及后面的数字去掉，从而得到更小的字典序。注意不能去掉 $a$ 中 $4$ 以及后面的数字，那样会得到更大的字典序。
    - 为避免复杂的分类讨论，我们可以直接算出 $a$ 中去掉 $\ge b[0]$ 和 $> b[0]$ 后剩余的序列，哪个字典序更小，就是答案。

```py
from bisect import bisect_left, bisect_right

n = int(input())
A = list(map(int, input().split()))

a, b = [], []
for x, y in zip(A[:n], A[n:]):
    while a and x < a[-1]:
        a.pop()
        b.pop()
    a.append(x)
    b.append(y)

i = bisect_right(a, a[0])
mn = min(b[:i])
if mn <= a[0]:
    print(a[0], mn)
    exit()

l = bisect_left(a, b[0])
r = bisect_right(a, b[0])
print(*min(a[:l] + b[:l], a[:r] + b[:r]))
```

时间复杂度：$\mathcal{O}(n)$。


---

## 作者：EuphoricStar (赞：2)

我一年前甚至不会做/qd

发现 $a_{x_1}$ 为 $k = \min\limits_{i=1}^n a_i$ 时最优。然后开始分类讨论：

- 如果 $\min\limits_{a_i = k} a_{i+n} \le k$，答案为 $(k, \min\limits_{a_i = k} a_{i+n})$。这是因为如果再选一个 $k$ 肯定不优。
- 否则我们肯定尽可能先把 $k$ 选完。接下来讨论最后一个 $k$ 的位置直到 $n$ 还能不能再选。设 $p$ 为第一个 $a_p = k$ 的位置。
	- 每次选的数要保证 $\le a_{p+n}$ 且是当前区间内的最小值，不然不优。
   - 当当前区间内最小值 $= a_{p+n}$ 时有些特殊。如果 $a_{p+n}$ 大于它后面被选的第一个 $\ne a_{p+n}$ 的数，或者它后面不存在 $\ne a_{p+n}$ 的数，那么选了这个区间最小值也不优。

实现时使用 ST 表查询区间最小值，复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/arc134/submissions/41155823)

---

## 作者：lfxxx (赞：0)

什么神秘分讨。

首先确定第一位，不难发现是 $\min_{i=1}^n a_i$。

也就是前 $n$ 个的最小值位置一定选一个，记这些位置集合为 $S$，假若 $\min_{(i-n) \in S}a_i \leq \min_{i=1}^n a_i$，那么你直接选 $\min_{i=1}^n a_i,\min_{(i-n) \in S}a_i$ 一定是最优解。

否则你一定会选择所有最小值位置，然后你会从最后一个最小值位置后面开始选，注意到你在前半段剩下的部分中选出来的数总是前半段剩下的部分的最小字典序子序列的子序列（这里认为空字符字典序最大），不妨先用单调栈把这个求出来。

不妨令 $s=\min_{i \in S}i+n$，对于求出来的这个子序列，其小于 $s$ 的部分必选，大于 $s$ 的部分必不选，于是我们只需要来决策等于 $s$ 的部分选不选。

假若目前已经确定的后半段必选部分为 $T$，显然 $T$ 应当行如 $s,s,s,\dots ,s,a,b,c\dots$，我们考察 $a,s$ 的大小关系，假若 $a<s$，那么我们希望尽快到 $a$，于是等于 $s$ 的部分一定不会选，如果 $a>s$，我们希望尽量慢地填到 $a$，于是一定会选全部等于 $s$ 的部分，如果 $a$ 根本不存在，因为实际上空字符字典序最小，还是等于 $s$ 的部分一定不会选。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int a[maxn],n;
int vis[maxn];
int minv;
int mv;
int stk[maxn],tp;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>a[i+n];
    minv=1e9+1;
    for(int i=1;i<=n;i++) minv=min(minv,a[i]);
    mv=1e9+1;
    for(int i=1;i<=n;i++){
        if(a[i]==minv){
            mv=min(mv,a[i+n]);
        }
    }
    if(mv<=minv){
        cout<<minv<<" "<<mv<<"\n";
    }else{
        int s,e;
        for(int i=1;i<=n;i++){
            if(a[i]==minv){
                s=i;
                break;
            }
        }
        for(int i=1;i<=n;i++){
            if(a[i]==minv){
                vis[i]=1;
                e=i;
            }
        }
        for(int i=e+1;i<=n;i++){
            if(tp==0) stk[++tp]=i;
            else{
                while(a[stk[tp]]>a[i]&&tp>0) tp--;
                stk[++tp]=i;
            }
        }
        vector<int> vec;
        while(a[stk[tp]]>=a[s+n]&&tp>0){
            if(a[stk[tp]]==a[s+n]) vec.push_back(stk[tp]);
            tp--;
        }
        for(int i=1;i<=tp;i++) vis[stk[i]]=1;
        bool flag=false;
        int lst=0;
        for(int i=1;i<=n;i++){
            if(vis[i]==1){
                if(lst==0) lst=a[i+n];
                else if(a[i+n]>lst){
                    flag=true;
                    break;
                }else if(a[i+n]<lst) break;
            }
        }
        if(flag==true){
            for(int x:vec) vis[x]=1;
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==1) cout<<a[i]<<' ';
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==1) cout<<a[i+n]<<' ';
        }
    }  
    return 0;
}
```

---

