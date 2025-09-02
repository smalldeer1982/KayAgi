# 题目信息

# Sad powers

## 题目描述

You're given $ Q $ queries of the form $ (L,R) $ .

For each query you have to find the number of such $ x $ that $ L<=x<=R $ and there exist integer numbers $ a&gt;0 $ , $ p&gt;1 $ such that $ x=a^{p} $ .

## 说明/提示

In query one the suitable numbers are $ 1 $ and $ 4 $ .

## 样例 #1

### 输入

```
6
1 4
9 9
5 7
12 29
137 591
1 1000000
```

### 输出

```
2
1
0
3
17
1111
```

# AI分析结果

### 题目内容
# Sad powers
## 题目描述
给定$Q$个形如$(L,R)$的查询。
对于每个查询，你需要找出满足$L\leq x\leq R$，且存在整数$a>0$、$p>1$使得$x = a^p$的$x$的数量。
## 说明/提示
在第一个查询中，合适的数字是$1$和$4$。
## 样例 #1
### 输入
```
6
1 4
9 9
5 7
12 29
137 591
1 1000000
```
### 输出
```
2
1
0
3
17
1111
```
### 算法分类
数学、二分
### 题解综合分析与结论
这些题解的核心思路都是利用数据范围的特点，将$p = 2$和$p\geq3$的情况分开处理。对于$p = 2$，利用完全平方数个数公式$\lfloor\sqrt{r}\rfloor-\lfloor\sqrt{l - 1}\rfloor$计算；对于$p\geq3$，由于满足条件的数相对较少，通过预处理并二分查找来确定满足条件的数的个数。各题解的主要差异在于预处理的方式、二分查找的实现以及对精度问题的处理。

### 所选的题解
- **作者：Eason_AC（5星）**
    - **关键亮点**：思路清晰，先分析数据范围，联想到$\sqrt{10^{18}} = 10^9$，$\sqrt[3]{10^{18}} = 10^6$，从而确定将$p = 2$和$p\geq3$的情况分开处理的方法，代码简洁明了，对边界和精度问题有提示。
    - **个人心得**：第一次独立做出紫题，发题解纪念。
    - **重点代码**：
```cpp
namespace Solution {
    const int N = 3e6 + 7;
    const ll MX = 1e18;
    int q, cnt;
    ll l, r, num[N];

    ill solve(ll x) {
        ll idx = lower_bound(num + 1, num + cnt + 1, x) - num;
        if((idx <= cnt && num[idx] > x) || idx > cnt) idx--;
        return idx + (ll)sqrt(x);
    }

    iv Main() {
        F(ll, i, 2, 1000000) {
            long long k = i * i;
            for(; k <= MX / i; ) {
                k *= i;
                ll sqrtk = sqrt(k);
                if(sqrtk * sqrtk!= k) num[++cnt] = k;
            }
        }
        sort(num + 1, num + cnt + 1), cnt = unique(num + 1, num + cnt + 1) - num - 1;
        read(q); while(q--) read(l, r), print(solve(r) - solve(l - 1), '\n');
        return;
    }
}
```
核心实现思想：通过循环预处理出所有$p\geq3$且不为完全平方数的数存入`num`数组，排序去重后，`solve`函数通过二分查找`num`数组中小于等于$x$的数的个数，再加上$x$以内完全平方数的个数得到结果。

- **作者：max0810follower（4星）**
    - **关键亮点**：指出本题是容斥原理，与莫比乌斯函数相关，通过存储每个$k$对应的$a$的最大值来优化二分查找，提高效率。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mu[74]={0,0,1,1,0,1,-1,1,0,0,-1,1,0,1,-1,-1,0,1,0,1,0,-1,-1,1,0,0,-1,0,0,1,1,1,0,-1,-1,-1,0,1,-1,-1,0,1,1,1,0,0,-1,1,0,0,0,-1,0,1,0,-1,0,-1,-1,1,0,1,-1,0,0};
const int maxx[74]={0,0,1000000000,1000000,31622,3981,1000,372,177,100,63,43,31,24,19,15,13,11,10,8,7,7,6,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1};
bool check(ll a,int b,ll n) {
    ll sum = 1;
    while(b) {
        if(b & 1) {
            if((__int128)sum * a > n)
                return false;
            sum *= a;
        }
        b >>= 1;
        if((__int128)a * a > n && b)
            return false;
        a *= a;
    }
    return true;
}
ll calc(ll n) {
    if(!n)
        return 0;
    ll ans = 1;
    for(int i = 2; i <= 64; i++) {
        int l = 1, r = maxx[i];
        while(l < r) {
            int mid = l + (r - l + 1) / 2;
            if(check(mid, i, n))
                l = mid;
            else
                r = mid - 1;
        }
        ans += mu[i] * (l - 1);
    }
    return ans;
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        ll l, r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",calc(r)-calc(l-1));
    }
    return 0;
}
```
核心实现思想：利用莫比乌斯函数处理容斥问题，`check`函数判断$a^b$是否小于等于$n$，`calc`函数通过枚举$i$（指数），利用二分查找确定满足$a^i\leq n$的最大$a$，根据莫比乌斯函数计算结果。

- **作者：开始新的记忆（4星）**
    - **关键亮点**：思路直接，先分析出$p$的最大值不会超过61，然后分别处理$p = 2$和$p\geq3$的情况，代码实现简洁易懂。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<long long> v;
void init() {
    long long n = 1e18;
    for(long long i = 2; i * i * i <= n; i++) {
        long long s = i * i;
        while(s <= n / i) {
            s *= i;
            long long t = sqrt(s);
            if(t * t!= s) 
                v.push_back(s);
        }
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}
long long calc(long long n) {
    long long idx = lower_bound(v.begin(),v.end(),n)-v.begin();
    if(idx<v.size() && v[idx]>n)
        idx--;
    if(idx==v.size())
        idx--;
    return (long long)sqrt(n)+idx;
} 
int main() {
    long long Q,l,r;
    init(); 
    cin>>Q;
    while(Q--) {
        cin>>l>>r;
        cout<<calc(r)-calc(l-1)<<endl;
    }
    return 0;
}
```
核心实现思想：`init`函数预处理出所有$p\geq3$且不为完全平方数的数存入`v`数组，排序去重后，`calc`函数通过二分查找`v`数组中小于等于$n$的数的个数，再加上$n$以内完全平方数的个数得到结果。

### 最优关键思路或技巧
1. **分情况处理**：根据数据范围特点，将$p = 2$和$p\geq3$的情况分开计算，$p = 2$利用完全平方数个数公式，$p\geq3$通过预处理和二分查找，有效降低时间复杂度。
2. **避免重复计算**：在预处理$p\geq3$的数时，排除可以写成完全平方数形式的数，防止重复计数。

### 可拓展思路
同类型题可拓展到求满足特定幂次形式的数在区间内的个数问题，类似算法套路是根据数据范围分析不同幂次下满足条件数的数量级，分情况处理，结合预处理和二分查找等方法优化计算。

### 洛谷推荐题目
1. **P1028 [NOIP2001 普及组] 数的计算**：通过递推和记忆化搜索的方式处理数字组合问题，与本题分析数字规律有相似之处。
2. **P1306 [NOIP2011 普及组] 机器翻译**：考察队列的应用以及数据的处理，与本题对数据的处理和优化思路有一定关联。
3. **P2678 [NOIP2015 普及组] 跳石头**：利用二分查找解决最优解问题，与本题中二分查找满足条件数的思路类似。 

---
处理用时：70.29秒