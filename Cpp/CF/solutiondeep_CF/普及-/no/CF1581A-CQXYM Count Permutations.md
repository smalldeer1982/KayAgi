# 题目信息

# CQXYM Count Permutations

## 题目描述

CQXYM is counting permutations length of $ 2n $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A permutation $ p $ (length of $ 2n $ ) will be counted only if the number of $ i $ satisfying $ p_i<p_{i+1} $ is no less than $ n $ . For example:

- Permutation $ [1, 2, 3, 4] $ will count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 3 $ ( $ i = 1 $ , $ i = 2 $ , $ i = 3 $ ).
- Permutation $ [3, 2, 1, 4] $ won't count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 1 $ ( $ i = 3 $ ).

CQXYM wants you to help him to count the number of such permutations modulo $ 1000000007 $ ( $ 10^9+7 $ ).

In addition, [modulo operation](https://en.wikipedia.org/wiki/Modulo_operation) is to get the remainder. For example:

- $ 7 \mod 3=1 $ , because $ 7 = 3 \cdot 2 + 1 $ ,
- $ 15 \mod 4=3 $ , because $ 15 = 4 \cdot 3 + 3 $ .

## 说明/提示

$ n=1 $ , there is only one permutation that satisfies the condition: $ [1,2]. $

In permutation $ [1,2] $ , $ p_1<p_2 $ , and there is one $ i=1 $ satisfy the condition. Since $ 1 \geq n $ , this permutation should be counted. In permutation $ [2,1] $ , $ p_1>p_2 $ . Because $ 0<n $ , this permutation should not be counted.

 $ n=2 $ , there are $ 12 $ permutations: $ [1,2,3,4],[1,2,4,3],[1,3,2,4],[1,3,4,2],[1,4,2,3],[2,1,3,4],[2,3,1,4],[2,3,4,1],[2,4,1,3],[3,1,2,4],[3,4,1,2],[4,1,2,3]. $

## 样例 #1

### 输入

```
4
1
2
9
91234```

### 输出

```
1
12
830455698
890287984```

# AI分析结果

### 题目内容
# CQXYM计数排列

## 题目描述
CQXYM正在对长度为\(2n\)的排列进行计数。

排列是一个由\(1\)到\(n\)的\(n\)个不同整数按任意顺序组成的数组。例如，\([2,3,1,5,4]\)是一个排列，但\([1,2,2]\)不是排列（数组中\(2\)出现了两次），\([1,3,4]\)也不是排列（\(n = 3\)但数组中有\(4\)）。

只有当满足\(p_i < p_{i + 1}\)的\(i\)的数量不少于\(n\)时，长度为\(2n\)的排列\(p\)才会被计数。例如：
 - 排列\([1, 2, 3, 4]\)会被计数，因为满足\(p_i < p_{i + 1}\)的\(i\)的数量等于\(3\)（\(i = 1\)，\(i = 2\)，\(i = 3\)）。
 - 排列\([3, 2, 1, 4]\)不会被计数，因为满足\(p_i < p_{i + 1}\)的\(i\)的数量等于\(1\)（\(i = 3\)）。

CQXYM希望你帮助他计算满足条件的排列数量对\(1000000007\)（\(10^9 + 7\)）取模的结果。

此外，[取模运算](https://en.wikipedia.org/wiki/Modulo_operation)是求余数。例如：
 - \(7 \bmod 3 = 1\)，因为\(7 = 3 \cdot 2 + 1\)。
 - \(15 \bmod 4 = 3\)，因为\(15 = 4 \cdot 3 + 3\)。

## 说明/提示
当\(n = 1\)时，只有一个排列满足条件：\([1,2]\)。

在排列\([1,2]\)中，\(p_1 < p_2\)，有一个\(i = 1\)满足条件。由于\(1 \geq n\)，这个排列应被计数。在排列\([2,1]\)中，\(p_1 > p_2\)。因为\(0 < n\)，这个排列不应被计数。

当\(n = 2\)时，有\(12\)个排列：\([1,2,3,4],[1,2,4,3],[1,3,2,4],[1,3,4,2],[1,4,2,3],[2,1,3,4],[2,3,1,4],[2,3,4,1],[2,4,1,3],[3,1,2,4],[3,4,1,2],[4,1,2,3]\)。

## 样例 #1
### 输入
```
4
1
2
9
91234
```
### 输出
```
1
12
830455698
890287984
```

### 算法分类
数学

### 综合分析与结论
这几道题解主要围绕寻找满足特定条件（满足\(p_i < p_{i + 1}\)的\(i\)的数量不少于\(n\)）的长度为\(2n\)的排列个数展开。多数题解通过建立满足条件和不满足条件排列之间的关系，得出满足条件的排列个数为总排列数\((2n)!\)的一半这一结论。部分题解通过打表找规律得到答案，而部分题解给出了严谨证明。

### 所选的题解
 - **作者：vectorwyx（4星）**
    - **关键亮点**：通过分析值为\(i\)的排列与值为\(2n - i\)的排列之间的双射关系，快速得出满足条件的排列个数为\(\frac{(2n)!}{2}\)，思路简洁清晰。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define int ll
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=1e6+5,qlr=1e9+7;

void solve(){
    int n=read(),ans=1;
    fo(i,3,2*n) ans=ans*i%qlr;
    cout<<ans<<endl;
}

signed main(){
    int T=read();
    while(T--) solve(); 
    return 0;
}
```
核心思想：通过循环从\(3\)到\(2n\)累乘并取模，得到\((2n)!\)除\(1\times2\)后的结果，即\(\frac{(2n)!}{2}\bmod(10^9 + 7)\)。
 - **作者：C_S_L（4星）**
    - **关键亮点**：定义\(count(p)\)表示满足\(p_i < p_{i + 1}\)的\(i\)的数量，通过将满足\(count(p)\geqslant n\)的排列反转，证明满足\(count(p)\geqslant n\)和\(count(p)<n\)的排列是两两对应的，从而得出满足条件的排列个数为\(\frac{(2n)!}{2}\)，证明过程严谨。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=(1e9)+7;
int T;
ll n;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        ll ans=1;
        for(ll i=3;i<=2*n;++i){
            ans=(ans*i)%MOD;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
核心思想：与vectorwyx题解类似，通过循环累乘并取模计算\(\frac{(2n)!}{2}\bmod(10^9 + 7)\)。
 - **作者：phigy（4星）**
    - **关键亮点**：通过构造映射关系，说明满足\(a_i < a_{i + 1}\)个数\(\geqslant n\)的排列与满足\(a_i < a_{i + 1}\)个数\(< n\)的排列一一对应，进而得出满足条件的排列个数为\(\frac{(2n)!}{2}\)，并计算出\(2\)在\(\bmod(10^9 + 7)\)下的乘法逆元，代码实现较为完整。
    - **核心代码**：
```cpp
#include <iostream>
 
using namespace std;
 
int mod=1000000007;
int t;
unsigned long long a[1000005];
 
int main()
{
    int i,j,k;
    a[1]=2;
    for(i=2;i<=1000000;i++)
    {
        a[i]=a[i-1]*(i*2-1)%mod*(i*2)%mod;
    }
    cin>>t;
    for(i=1;i<=t;i++)
    {
        int x;
        cin>>x;
        cout<<a[x]*500000004%mod<<endl;
    }
    return 0;
}
```
核心思想：通过循环递推计算\((2n)!\)，并利用已计算出的\(2\)在\(\bmod(10^9 + 7)\)下的乘法逆元\(500000004\)，直接得出满足条件排列个数对\(\bmod(10^9 + 7)\)的结果。

### 最优关键思路或技巧
利用排列与其反转排列（或构造的对应排列）中满足\(p_i < p_{i + 1}\)的数量关系，建立满足条件和不满足条件排列之间的一一对应，从而快速得出满足条件的排列个数为总排列数的一半，简化计算过程。

### 可拓展之处
此类题目属于组合数学中关于排列计数的问题，常见的类似套路是通过建立不同排列集合之间的映射关系，将问题转化为已知排列数的计算。例如，在一些限制条件下的排列组合问题，可尝试寻找排列之间的对称关系或对应关系来简化求解。

### 洛谷推荐题目
 - [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考察组合数学中的二项式定理应用。
 - [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)：涉及组合数的计算及取模运算，与本题在组合数学和取模计算上有相似点。
 - [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：通过卢卡斯定理解决大组合数取模问题，同样是组合数学在取模运算下的应用。 

---
处理用时：89.89秒