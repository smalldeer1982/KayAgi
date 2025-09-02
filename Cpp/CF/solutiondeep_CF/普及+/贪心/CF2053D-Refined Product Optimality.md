# 题目信息

# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429```

# AI分析结果



# Refined Product Optimality 精炼产品最优性

## 题目描述

作为测试者，当我的解决方案在测试中与示例输出不同时，我首先怀疑作者。

— Chris, [评论](https://codeforces.com/blog/entry/133116?#comment-1190579)

尽管 Iris 偶尔会设置可能存在错误解法的问题，但她仍坚持用想象力创造问题；毕竟每个人始终都带着自己的固执前行... 和往常一样，Iris 设置了一个给出错误解法的问题，而 Chris 总是要拯救它！你现在将扮演 Chris：

- Chris 得到两个由 $n$ 个整数组成的数组 $a$ 和 $b$。
- Iris 关心在任意重排 $b$ 后，$P = \prod\limits_{i=1}^n \min(a_i, b_i)$ 的最大可能值。注意她只想知道 $P$ 的最大值，无需实际重排 $b$。
- 有 $q$ 次修改。每次修改由两个整数 $o$ 和 $x$ 表示（$o$ 为 1 或 2，$1 \leq x \leq n$）。若 $o=1$，则 Iris 将 $a_x$ 增加 1；否则，将 $b_x$ 增加 1。
- Iris 询问 Chris $P$ 的最大值共 $q+1$ 次：首次在修改前，之后每次修改后。
- 由于 $P$ 可能极大，Chris 只需计算模 $998\,244\,353$ 的结果。

Chris 很快解决了问题，但因疲倦入睡。现在轮到你编写程序计算给定输入的答案。

注意：输入输出较大，需优化处理。

## 题解分析

### 关键思路
1. **排序贪心**：将 $a$ 和 $b$ 分别升序排序后对应位置取 $\min$ 的乘积最大。可通过邻项交换法证明该策略最优。
2. **维护排序数组**：维护排序后的数组 $c$（对应 $a$）和 $d$（对应 $b$），每次修改仅调整特定元素位置，保持数组有序。
3. **快速更新策略**：
   - **二分定位**：通过 `upper_bound` 找到最后一个等于原值的元素位置。
   - **逆元处理**：利用模逆元快速更新乘积，避免重新计算整个数组。
4. **时间复杂度**：初始排序 $O(n \log n)$，每次修改 $O(\log n)$，总复杂度 $O(n \log n + q \log n)$。

### 解决难点
- **修改后数组维护**：每次仅修改排序数组中最后一个匹配元素，确保数组仍保持有序。
- **模运算下的除法**：使用快速幂计算逆元，确保模运算的正确性。

## 精选题解

### 题解1（作者：cjh20090318）⭐⭐⭐⭐⭐
**亮点**：代码简洁高效，思路清晰，通过二分快速定位修改位置。
```cpp
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
typedef long long LL;
constexpr int mod=998244353;
int n,q;
int qpow(int a,int b=mod-2){
    int ret=1;
    for(;b;b>>=1,a=(LL)a*a%mod)if(b&1)ret=(LL)ret*a%mod;
    return ret%mod;
}
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i],c[i]=a[i];
    for(int i=1;i<=n;i++) cin>>b[i],d[i]=b[i];
    sort(c+1,c+n+1),sort(d+1,d+n+1);
    int ans=1;
    for(int i=1;i<=n;i++) ans=(LL)ans*min(c[i],d[i])%mod;
    cout<<ans<<' ';
    for(int o,x,p;q--;){
        cin>>o>>x;
        p=0;
        if(o==1)
            p=upper_bound(c+1,c+n+1,a[x])-c-1,
            ans=(LL)ans*qpow(min(c[p],d[p]))%mod,
            ++a[x],++c[p];
        else
            p=upper_bound(d+1,d+n+1,b[x])-d-1,
            ans=(LL)ans*qpow(min(c[p],d[p]))%mod,
            ++b[x],++d[p];
        ans=(LL)ans*min(c[p],d[p])%mod;
        cout<<ans<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T; while(T--) solve(); 
    return 0;
}
```

### 题解2（作者：Drifty）⭐⭐⭐⭐
**亮点**：使用 STL 容器管理排序数组，代码结构清晰。
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using i64 = long long;
constexpr int P = 998244353;
int T, n, q;
i64 inv(i64 a, int x = P - 2) {
    i64 res = 1;
    for(;x;x>>=1,a=a*a%P) if(x&1) res=res*a%P;
    return res;
}
void solve() {
    cin >> n >> q;
    vector<int> a(n+1), b(n+1), u(a), v(b);
    for(int i=1;i<=n;i++) cin>>a[i]; sort(a.begin(),a.end());
    for(int i=1;i<=n;i++) cin>>b[i]; sort(b.begin(),b.end());
    i64 ans=1; for(int i=1;i<=n;i++) ans=ans*min(a[i],b[i])%P;
    cout<<ans<<' ';
    for(int op,x,p;q--;){
        cin>>op>>x;
        if(op==1){
            p=upper_bound(a.begin(),a.end(),u[x])-a.begin()-1;
            ans=ans*inv(min(a[p],b[p]))%P; u[x]++; a[p]++;
        } else {
            p=upper_bound(b.begin(),b.end(),v[x])-b.begin()-1;
            ans=ans*inv(min(a[p],b[p]))%P; v[x]++; b[p]++;
        }
        ans=ans*min(a[p],b[p])%P;
        cout<<ans<<' ';
    }
    cout<<'\n';
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    for(cin>>T;T--;) solve();
    return 0;
}
```

### 题解3（作者：_lmh_）⭐⭐⭐⭐
**亮点**：代码简洁，变量命名规范，适合快速理解。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+7,mod=998244353;
int T,n,m,a[N],b[N],c[N],d[N],ans;
int qpow(int x,int k=mod-2){
    int s=1;
    while(k){
        if(k&1)s=s*x%mod;
        x=x*x%mod;k>>=1;
    } return s;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;ans=1;
        for(int i=1;i<=n;i++)cin>>a[i],c[i]=a[i];
        for(int i=1;i<=n;i++)cin>>b[i],d[i]=b[i];
        sort(c+1,c+n+1);sort(d+1,d+n+1);
        for(int i=1;i<=n;i++)ans=ans*min(c[i],d[i])%mod;
        cout<<ans<<' ';
        while(m--){
            int o,x;cin>>o>>x;
            if(o==1){
                int p=upper_bound(c+1,c+n+1,a[x])-c-1;
                ans=ans*qpow(min(c[p],d[p]))%mod;
                c[p]++;a[x]++;
                ans=ans*min(c[p],d[p])%mod;
            } else {
                int p=upper_bound(d+1,d+n+1,b[x])-d-1;
                ans=ans*qpow(min(c[p],d[p]))%mod;
                d[p]++;b[x]++;
                ans=ans*min(c[p],d[p])%mod;
            }
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
```

## 关键技巧总结
- **排序贪心**：最优解基于双数组升序排列后的对应位置。
- **单点维护**：修改时仅调整最后一个匹配元素，保持数组有序。
- **逆元快速更新**：利用快速幂求逆元处理模下除法。

## 相似题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908) - 排序与逆序对维护。
2. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966) - 贪心排序与最优匹配。
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 维护有序结构的最优策略。

## 心得摘录
- **调试经验**：确保二分定位正确，特别注意 `upper_bound` 的返回值为第一个大于目标的位置。
- **模运算陷阱**：除法必须转换为逆元乘法，直接使用整数除法会导致错误。
- **思维突破**：通过调整法证明排序策略最优，避免陷入暴力枚举的误区。

---
处理用时：151.94秒