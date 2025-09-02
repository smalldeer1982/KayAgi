# 题目信息

# Permutations & Primes

## 题目描述

You are given a positive integer $ n $ .

In this problem, the $ \operatorname{MEX} $ of a collection of integers $ c_1,c_2,\dots,c_k $ is defined as the smallest positive integer $ x $ which does not occur in the collection $ c $ .

The primality of an array $ a_1,\dots,a_n $ is defined as the number of pairs $ (l,r) $ such that $ 1 \le l \le r \le n $ and $ \operatorname{MEX}(a_l,\dots,a_r) $ is a prime number.

Find any permutation of $ 1,2,\dots,n $ with the maximum possible primality among all permutations of $ 1,2,\dots,n $ .

Note:

- A prime number is a number greater than or equal to $ 2 $ that is not divisible by any positive integer except $ 1 $ and itself. For example, $ 2,5,13 $ are prime numbers, but $ 1 $ and $ 6 $ are not prime numbers.
- A permutation of $ 1,2,\dots,n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, there are $ 3 $ pairs $ (l,r) $ with $ 1 \le l \le r \le 2 $ , out of which $ 2 $ have a prime $ \operatorname{MEX}(a_l,\dots,a_r) $ :

- $ (l,r) = (1,1) $ : $ \operatorname{MEX}(2) = 1 $ , which is not prime.
- $ (l,r) = (1,2) $ : $ \operatorname{MEX}(2,1) = 3 $ , which is prime.
- $ (l,r) = (2,2) $ : $ \operatorname{MEX}(1) = 2 $ , which is prime.

 Therefore, the primality is $ 2 $ .In the second test case, $ \operatorname{MEX}(1) = 2 $ is prime, so the primality is $ 1 $ .

In the third test case, the maximum possible primality is $ 8 $ .

## 样例 #1

### 输入

```
3
2
1
5```

### 输出

```
2 1
1
5 2 1 4 3```

# AI分析结果

### 题目翻译
# 排列与质数

## 题目描述
给定一个正整数 $n$。

在这个问题中，一组整数 $c_1,c_2,\dots,c_k$ 的 $\operatorname{MEX}$ 被定义为不在这组整数 $c$ 中出现的最小正整数 $x$。

一个数组 $a_1,\dots,a_n$ 的素性被定义为满足 $1 \le l \le r \le n$ 且 $\operatorname{MEX}(a_l,\dots,a_r)$ 是质数的数对 $(l,r)$ 的数量。

在 $1,2,\dots,n$ 的所有排列中，找出素性最大的任意一个排列。

注意：
- 质数是大于或等于 $2$ 且除了 $1$ 和它自身外不能被任何正整数整除的数。例如，$2$、$5$、$13$ 是质数，但 $1$ 和 $6$ 不是质数。
- $1,2,\dots,n$ 的排列是一个由 $n$ 个从 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n = 3$ 但数组中有 $4$）。

## 说明/提示
在第一个测试用例中，有 $3$ 对数对 $(l,r)$ 满足 $1 \le l \le r \le 2$，其中有 $2$ 对数对的 $\operatorname{MEX}(a_l,\dots,a_r)$ 是质数：
- $(l,r) = (1,1)$：$\operatorname{MEX}(2) = 1$，不是质数。
- $(l,r) = (1,2)$：$\operatorname{MEX}(2,1) = 3$，是质数。
- $(l,r) = (2,2)$：$\operatorname{MEX}(1) = 2$，是质数。

因此，素性为 $2$。在第二个测试用例中，$\operatorname{MEX}(1) = 2$ 是质数，所以素性为 $1$。在第三个测试用例中，最大可能的素性为 $8$。

## 样例 #1
### 输入
```
3
2
1
5
```
### 输出
```
2 1
1
5 2 1 4 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过合理安排 $1$、$2$、$3$ 的位置来构造出素性最大的排列。由于 $1$ 不是质数，要使包含 $1$ 的子区间尽可能多，根据和一定差小积大的原理，将 $1$ 放在中间位置能使包含 $1$ 的子区间对数最多。又因为 $2$ 和 $3$ 是质数，为避免子区间同时包含 $2$ 和 $3$ 导致 $\operatorname{MEX}$ 不是质数，将 $2$ 和 $3$ 放在排列的两端。其他位置的数字可以随意填充。

### 所选题解
- **wanghaoran00（4星）**：
    - **关键亮点**：思路清晰，代码简洁，通过数学原理分析出 $1$ 放中间、$2$ 和 $3$ 放两端的构造方法，并给出了详细的代码实现。
- **Larryyu（4星）**：
    - **关键亮点**：对 $\operatorname{MEX}$ 的定义和构造思路进行了详细的分析，给出了代码实现，逻辑清晰。
- **Coffee_zzz（4星）**：
    - **关键亮点**：详细分析了 $\operatorname{MEX}$ 取质数的条件，进而得出构造排列的方法，代码实现简洁。

### 重点代码及核心思想
#### wanghaoran00 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,x;
int main(){
    cin>>t;
    while(t--){
        x=4;
        scanf("%d",&n);
        if(n==1){
            printf("1\n");
        }
        else if(n==2){
            printf("2 1\n");
        }
        else{
            printf("2 ");
            for(int i=2;i<=n/2;i++){
                printf("%d ",x);
                x++;
            }
            printf("1 ");
            for(int i=n/2+2;i<n;i++){
                printf("%d ",x);
                x++;
            }
            printf("3\n");
        }
    }
    return 0;
}
```
**核心思想**：先处理 $n = 1$ 和 $n = 2$ 的特殊情况，对于 $n > 2$ 的情况，先输出 $2$，然后按顺序输出中间部分的数字，接着输出 $1$，再输出剩余部分的数字，最后输出 $3$。

#### Larryyu 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
void solve(){
    int n;
    cin>>n;
    int now=3;
    if(n<3){
        for(int i=1;i<=n;i++){
            cout<<i<<" ";
        }
        return;
    }
    cout<<"3 ";
    for(int i=1;i<n-1;i++){
        if(i+1==ceil((float)n/2)) cout<<"1 "; //i+1是因为前面有个3
        else cout<<++now<<" ";
    }
    cout<<2<<endl;
}
int main(){
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```
**核心思想**：先处理 $n < 3$ 的特殊情况，对于 $n \geq 3$ 的情况，先输出 $3$，然后按顺序输出中间部分的数字，当到中间位置时输出 $1$，最后输出 $2$。

#### Coffee_zzz 的代码
```c++
int a[200005];
void solve(){
    int n=read();
    if(n==1) cout<<"1\n";
    else if(n==2) cout<<"1 2\n";
    else{
        int cnt=1;
        for(int l=1,r=n;l<r;l++,r--) a[l]=++cnt,a[r]=++cnt;
        a[n/2+1]=1;
        for(int i=1;i<=n;i++) cout<<a[i]<<' ';
        cout<<endl;
    }
}
```
**核心思想**：先处理 $n = 1$ 和 $n = 2$ 的特殊情况，对于 $n > 2$ 的情况，从数组两端向中间填充数字，最后将 $1$ 放在中间位置，然后输出数组。

### 最优关键思路或技巧
- **贪心构造思路**：通过分析 $\operatorname{MEX}$ 的性质，利用贪心策略，确定 $1$、$2$、$3$ 的位置，从而构造出满足条件的排列。
- **数学原理应用**：利用和一定差小积大的原理，确定 $1$ 的位置，使包含 $1$ 的子区间对数最多。

### 拓展思路
同类型题目可能会改变 $\operatorname{MEX}$ 的定义或质数的判断条件，或者增加其他限制条件，但解题的核心思路仍然是通过分析条件，利用贪心和构造的方法来解决问题。

### 洛谷题目推荐
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：考察动态规划和路径构造。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：考察动态规划和路径构造。
- [P1434 [SHOI2002] 滑雪](https://www.luogu.com.cn/problem/P1434)：考察深度优先搜索和路径构造。

### 个人心得摘录与总结
- **Crazyouth**：赛时怕吃罚时，加了个 $n \leq 4$ 的特判，后来发现只需要判 $n \leq 2$ 就行。总结：在解题时要仔细分析特殊情况，避免不必要的特判，提高代码的简洁性。

---
处理用时：46.77秒