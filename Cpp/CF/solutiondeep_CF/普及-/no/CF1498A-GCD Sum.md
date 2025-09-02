# 题目信息

# GCD Sum

## 题目描述

The $ \text{ $ gcdSum $ } $ of a positive integer is the $ gcd $ of that integer with its sum of digits. Formally, $ \text{ $ gcdSum $ }(x) = gcd(x, \text{ sum of digits of } x) $ for a positive integer $ x $ . $ gcd(a, b) $ denotes the greatest common divisor of $ a $ and $ b $ — the largest integer $ d $ such that both integers $ a $ and $ b $ are divisible by $ d $ .

For example: $ \text{ $ gcdSum $ }(762) = gcd(762, 7 + 6 + 2)=gcd(762,15) = 3 $ .

Given an integer $ n $ , find the smallest integer $ x \ge n $ such that $ \text{ $ gcdSum $ }(x) > 1 $ .

## 说明/提示

Let us explain the three test cases in the sample.

Test case 1: $ n = 11 $ :

 $ \text{ $ gcdSum $ }(11) = gcd(11, 1 + 1) = gcd(11,\ 2) = 1 $ .

 $ \text{ $ gcdSum $ }(12) = gcd(12, 1 + 2) = gcd(12,\ 3) = 3 $ .

So the smallest number $ \ge 11 $ whose $ gcdSum $ $ > 1 $ is $ 12 $ .

Test case 2: $ n = 31 $ :

 $ \text{ $ gcdSum $ }(31) = gcd(31, 3 + 1) = gcd(31,\ 4) = 1 $ .

 $ \text{ $ gcdSum $ }(32) = gcd(32, 3 + 2) = gcd(32,\ 5) = 1 $ .

 $ \text{ $ gcdSum $ }(33) = gcd(33, 3 + 3) = gcd(33,\ 6) = 3 $ .

So the smallest number $ \ge 31 $ whose $ gcdSum $ $ > 1 $ is $ 33 $ .

Test case 3: $ \ n = 75 $ :

 $ \text{ $ gcdSum $ }(75) = gcd(75, 7 + 5) = gcd(75,\ 12) = 3 $ .

The $ \text{ $ gcdSum $ } $ of $ 75 $ is already $ > 1 $ . Hence, it is the answer.

## 样例 #1

### 输入

```
3
11
31
75```

### 输出

```
12
33
75```

# AI分析结果

### 题目内容
#### GCD和
1. **题目描述**：一个正整数的“gcdSum”是该整数与其各位数字之和的最大公约数。正式地，对于正整数$x$，$\text{gcdSum}(x) = \gcd(x, \text{ $x$的各位数字之和})$ 。$\gcd(a, b)$表示$a$和$b$的最大公约数，即能同时整除$a$和$b$的最大整数$d$。
例如：$\text{gcdSum}(762) = \gcd(762, 7 + 6 + 2)=\gcd(762,15) = 3$ 。
给定一个整数$n$，找到最小的整数$x \geq n$，使得$\text{gcdSum}(x) > 1$ 。
2. **说明/提示**：
    - 让我们解释一下样例中的三个测试用例。
    - **测试用例1**：$n = 11$ 。
        - $\text{gcdSum}(11) = \gcd(11, 1 + 1) = \gcd(11,\ 2) = 1$ 。
        - $\text{gcdSum}(12) = \gcd(12, 1 + 2) = \gcd(12,\ 3) = 3$ 。
        - 所以大于等于$11$且$\text{gcdSum}$大于$1$的最小数是$12$ 。
    - **测试用例2**：$n = 31$ 。
        - $\text{gcdSum}(31) = \gcd(31, 3 + 1) = \gcd(31,\ 4) = 1$ 。
        - $\text{gcdSum}(32) = \gcd(32, 3 + 2) = \gcd(32,\ 5) = 1$ 。
        - $\text{gcdSum}(33) = \gcd(33, 3 + 3) = \gcd(33,\ 6) = 3$ 。
        - 所以大于等于$31$且$\text{gcdSum}$大于$1$的最小数是$33$ 。
    - **测试用例3**：$n = 75$ 。
        - $\text{gcdSum}(75) = \gcd(75, 7 + 5) = \gcd(75,\ 12) = 3$ 。
        - $75$的$\text{gcdSum}$已经大于$1$。因此，它就是答案。
3. **样例 #1**：
    - **输入**：
```
3
11
31
75
```
    - **输出**：
```
12
33
75
```

### 算法分类
数学

### 题解综合分析与结论
所有题解都利用了“任何能被3整除的数，其各位和能被3整除”这一数学性质，即3的倍数一定满足$\text{gcdSum}(x)>1$ 。由于连续三个自然数中必有一个是3的倍数，所以最多枚举3个数就能找到符合条件的$x$ 。各题解主要区别在于代码实现细节，如输入输出方式、函数封装等。

### 所选的题解
- **作者：Leasier (赞：1，4星)**
    - **关键亮点**：思路清晰简洁，代码结构紧凑，直接利用$3$的倍数性质进行暴力枚举，可读性强。
    - **重点代码核心实现思想**：通过`gcdsum`函数计算$\text{gcdSum}(n)$，在`main`函数中从$n$开始枚举，直到找到$\text{gcdSum}(ans)>1$的数。
```cpp
#include <stdio.h>

typedef long long ll;

ll gcd(ll a, ll b){
    return b == 0? a : gcd(b, a % b);
}

inline ll gcdsum(ll n){
    ll m = 0;
    for (register ll i = n; i > 0; i /= 10){
        m += i % 10;
    }
    return gcd(n, m);
}

int main(){
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++){
        ll n, ans;
        scanf("%lld", &n);
        ans = n;
        while (gcdsum(ans) == 1) ans++;
        printf("%lld\n", ans);
    }
    return 0;
}
```
- **作者：vectorwyx (赞：0，4星)**
    - **关键亮点**：利用$3$的倍数性质，通过`check`函数判断数字是否满足条件，在`work`函数中对$n,n + 1,n + 2$分别进行判断，代码逻辑清晰。
    - **重点代码核心实现思想**：`check`函数计算数字与其各位数字和的最大公约数判断是否大于1，`work`函数从$n$到$n + 2$枚举判断，找到符合条件的数输出。
```cpp
bool check(ll x){
    ll t=x,s=0;
    while(x){
        s+=x%10;
        x/=10;
    }
    return __gcd(t,s)>1;
}

void work(){
    ll n;
    cin>>n;
    fo(i,n,n+2)	if(check(i)){
        printf("%lld\n",i);
        return;
    }
}
```
- **作者：SpeedStar (赞：0，4星)**
    - **关键亮点**：简洁明了地实现了利用$3$的倍数性质解题，在`main`函数中直接对$n,n + 1,n + 2$分别判断$\text{gcdSum}$是否大于1，代码简洁。
    - **重点代码核心实现思想**：`gcd_sum`函数计算$\text{gcdSum}(n)$，在`main`函数中对$n,n + 1,n + 2$依次判断，输出符合条件的数。
```cpp
ll gcd_sum(ll n) {
    ll tmp = n, digitsum = 0;
    
    while (tmp) {
        digitsum += tmp % 10;
        tmp /= 10;
    }
    
    ll res = std::gcd(n, digitsum);
    return res;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        ll n;
        cin >> n;
        if (gcd_sum(n) > 1) cout << n << '\n';
        else if (gcd_sum(n + 1) > 1) cout << n + 1 << '\n';
        else if (gcd_sum(n + 2) > 1) cout << n + 2 << '\n';
    }
    
    return 0;
}
```

### 最优关键思路或技巧
利用数论中“3的倍数的各位数字之和也是3的倍数”这一性质，将原本可能的大范围枚举优化为最多只需要枚举3个数，大大降低了时间复杂度。在代码实现上，通过封装计算数字各位和以及最大公约数的函数，使代码结构更清晰。

### 拓展
同类型题目通常围绕数论性质展开，例如给定某种自定义运算，结合整除、余数等性质求解满足条件的数。类似算法套路是深入挖掘数论中的各种性质，如其他数字的整除特性，利用这些性质简化枚举过程，优化算法时间复杂度。

### 推荐洛谷题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察最大公约数和最小公倍数的性质及应用。
- [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602)：涉及数字各位上数字出现次数的统计，与本题对数字各位的处理有相似之处。
- [P1890 [USACO03NOV] 滑雪课Ski Lessons](https://www.luogu.com.cn/problem/P1890)：虽然表面是滑雪课时间安排问题，但本质上利用了数论中余数的性质，与本题利用数论性质优化算法思路类似。 

---
处理用时：64.02秒