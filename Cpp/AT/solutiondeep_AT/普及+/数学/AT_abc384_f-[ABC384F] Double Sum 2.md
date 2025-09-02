# 题目信息

# [ABC384F] Double Sum 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_f

正整数 $ x $ に対して $ f(x) $ を「 $ x $ が偶数である間 $ x $ を $ 2 $ で割り続けたときの、最終的な $ x $ の値」として定義します。例えば $ f(4)=f(2)=f(1)=1 $ 、 $ f(12)=f(6)=f(3)=3 $ です。

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,\ A_N) $ が与えられるので、 $ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i}^N\ f(A_i+A_j) $ を求めてください。

## 说明/提示

### 制約

- $ 1\le\ N\le\ 2\times\ 10^5 $
- $ 1\le\ A_i\le\ 10^7 $
- 入力は全て整数
 
### Sample Explanation 1

$ f(A_1+A_1)=f(8)=1 $ 、 $ f(A_1+A_2)=f(12)=3 $ 、 $ f(A_2+A_2)=f(16)=1 $ です。したがって、 $ 1+3+1=5 $ を出力してください。

## 样例 #1

### 输入

```
2

4 8```

### 输出

```
5```

## 样例 #2

### 输入

```
3

51 44 63```

### 输出

```
384```

## 样例 #3

### 输入

```
8

577752 258461 183221 889769 278633 577212 392309 326001```

### 输出

```
20241214```

# AI分析结果

### 题目内容重写

#### 题目描述

对于正整数 \( x \)，定义 \( f(x) \) 为“当 \( x \) 为偶数时，不断将 \( x \) 除以 2，直到 \( x \) 为奇数，最终得到的 \( x \) 的值”。例如，\( f(4) = f(2) = f(1) = 1 \)，\( f(12) = f(6) = f(3) = 3 \)。

给定一个长度为 \( N \) 的整数序列 \( A = (A_1, A_2, \ldots, A_N) \)，求 \( \displaystyle \sum_{i=1}^N \sum_{j=i}^N f(A_i + A_j) \) 的值。

#### 说明/提示

##### 约束

- \( 1 \leq N \leq 2 \times 10^5 \)
- \( 1 \leq A_i \leq 10^7 \)
- 输入均为整数

##### 样例解释 1

\( f(A_1 + A_1) = f(8) = 1 \)，\( f(A_1 + A_2) = f(12) = 3 \)，\( f(A_2 + A_2) = f(16) = 1 \)。因此，输出 \( 1 + 3 + 1 = 5 \)。

##### 样例 #1

###### 输入

```
2
4 8
```

###### 输出

```
5
```

##### 样例 #2

###### 输入

```
3
51 44 63
```

###### 输出

```
384
```

##### 样例 #3

###### 输入

```
8
577752 258461 183221 889769 278633 577212 392309 326001
```

###### 输出

```
20241214
```

---

### 题解分析与结论

#### 题解对比

1. **KazamaRuri**（★★★★☆）
   - **亮点**：通过枚举末尾的0的个数，利用桶或trie计算贡献，时间复杂度为 \( O(n \log V) \)。
   - **难点**：如何高效地计算末尾恰好有 \( k \) 个0的和。
   - **代码实现**：使用桶记录模数，差分计算贡献。

2. **2022dyx**（★★★★☆）
   - **亮点**：采用“正难则反”的思路，先计算总和，再减去多余部分，利用map记录余数。
   - **难点**：如何高效地计算每个 \( 2^k \) 的倍数和。
   - **代码实现**：使用map记录余数的个数和总和，动态维护贡献。

3. **Moya_Rao**（★★★★☆）
   - **亮点**：详细解释了“正难则反”的思路，并通过余数分类计算贡献，代码清晰易懂。
   - **难点**：如何通过余数分类计算每个 \( 2^k \) 的倍数和。
   - **代码实现**：使用数组记录余数的个数和总和，动态维护贡献。

#### 最优关键思路

- **正难则反**：先计算总和，再减去多余部分，利用余数分类计算每个 \( 2^k \) 的倍数和。
- **余数分类**：通过模数分类，动态维护余数的个数和总和，高效计算贡献。

#### 可拓展之处

- **类似问题**：可以扩展到其他进制的问题，如三进制、五进制等。
- **算法套路**：余数分类和动态维护的思路可以应用于其他需要计算倍数和的问题。

#### 推荐题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3380 【模板】线段树 1](https://www.luogu.com.cn/problem/P3380)

#### 个人心得摘录

- **Moya_Rao**：通过“正难则反”的思路，详细解释了如何通过余数分类计算贡献，代码清晰易懂。
- **2022dyx**：利用map记录余数的个数和总和，动态维护贡献，思路清晰，代码简洁。

---

### 所选高分题解

#### 1. KazamaRuri（★★★★☆）

**关键亮点**：通过枚举末尾的0的个数，利用桶或trie计算贡献，时间复杂度为 \( O(n \log V) \)。

**代码实现**：
```cpp
#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll=long long;
const int N=2e5+5,V=1e7+5;
ll n,a[N],t[1<<24],c[1<<24],f[25],ans;
inline ll inv(ll x,ll s){ return s&(s+1-(x&s)); }
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",a+i);
    reverse(a+1,a+1+n);
    for(int k=24;~k;k--){
        ll s=(1<<k)-1;
        for(int i=1;i<=n;i++){
            t[a[i]&s]+=a[i],c[a[i]&s]++,
            f[k]+=t[inv(a[i],s)]+c[inv(a[i],s)]*a[i];
        }
        for(int i=1;i<=n;i++) t[a[i]&s]=c[a[i]&s]=0;
        ans+=f[k]-f[k+1]>>k;
    }
    return printf("%lld",ans)&0;
}
```

#### 2. 2022dyx（★★★★☆）

**关键亮点**：采用“正难则反”的思路，先计算总和，再减去多余部分，利用map记录余数。

**代码实现**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], ans;
unordered_map <int, int> cnt, mp;
signed main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int now = 0;
    for (int i = 1; i <= n; ++i) now += a[i], ans += now + i * a[i];
    for (int i = 2; i < 2e7; i <<= 1) {
        int now = 0;
        for (int j = 1; j <= n; ++j) {
            ++cnt[a[j] % i];
            mp[a[j] % i] += a[j];
            now += mp[(i - a[j] % i) % i] + a[j] * cnt[(i - a[j] % i) % i];
        }
        for (int j = 1; j <= n; ++j) {
            --cnt[a[j] % i];
            mp[a[j] % i] -= a[j];
        }
        ans -= now / i;
    }
    cout << ans;
}
```

#### 3. Moya_Rao（★★★★☆）

**关键亮点**：详细解释了“正难则反”的思路，并通过余数分类计算贡献，代码清晰易懂。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5 , M = 2e7+5;
long long n,a[N],cnt[M],sum[M],mx,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];mx=max(mx,a[i]);
        ans+=a[i]*(n-1);
        long long tmp=a[i];
        while(tmp%2==0)tmp/=2;
        ans+=tmp;
    }
    for(int k=2;k<=mx*2;k*=2){
        memset(cnt,0,sizeof(cnt));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            int zm=a[i]%k,fm=(k-a[i]%k)%k;
            if(cnt[fm])ans-=(sum[fm]+cnt[fm]*a[i])/k;
            cnt[zm]++,sum[zm]+=a[i];
        }
    }
    cout<<ans;
    return 0;
}
```

---
处理用时：62.37秒