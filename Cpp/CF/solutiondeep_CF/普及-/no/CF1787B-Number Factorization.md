# 题目信息

# Number Factorization

## 题目描述

Given an integer $ n $ .

Consider all pairs of integer arrays $ a $ and $ p $ of the same length such that $ n = \prod a_i^{p_i} $ (i.e. $ a_1^{p_1}\cdot a_2^{p_2}\cdot\ldots $ ) ( $ a_i>1;p_i>0 $ ) and $ a_i $ is the product of some (possibly one) distinct prime numbers.

For example, for $ n = 28 = 2^2\cdot 7^1 = 4^1 \cdot 7^1 $ the array pair $ a = [2, 7] $ , $ p = [2, 1] $ is correct, but the pair of arrays $ a = [4, 7] $ , $ p = [1, 1] $ is not, because $ 4=2^2 $ is a product of non-distinct prime numbers.

Your task is to find the maximum value of $ \sum a_i \cdot p_i $ (i.e. $ a_1\cdot p_1 + a_2\cdot p_2 + \ldots $ ) over all possible pairs of arrays $ a $ and $ p $ . Note that you do not need to minimize or maximize the length of the arrays.

## 说明/提示

In the first test case, $ 100 = 10^2 $ so that $ a = [10] $ , $ p = [2] $ when $ \sum a_i \cdot p_i $ hits the maximum value $ 10\cdot 2 = 20 $ . Also, $ a = [100] $ , $ p = [1] $ does not work since $ 100 $ is not made of distinct prime factors.

In the second test case, we can consider $ 10 $ as $ 10^1 $ , so $ a = [10] $ , $ p = [1] $ . Notice that when $ 10 = 2^1\cdot 5^1 $ , $ \sum a_i \cdot p_i = 7 $ .

## 样例 #1

### 输入

```
7
100
10
864
130056192
1000000000
2
999999018```

### 输出

```
20
10
22
118
90
2
333333009```

# AI分析结果

### 题目内容
# 数字分解

## 题目描述
给定一个整数 $n$ 。
考虑所有长度相同的整数数组 $a$ 和 $p$ 对，使得 $n = \prod a_i^{p_i}$ （即 $a_1^{p_1}\cdot a_2^{p_2}\cdot\ldots$ ）（$a_i>1$；$p_i>0$），并且 $a_i$ 是一些（可能是一个）不同质数的乘积。
例如，对于 $n = 28 = 2^2\cdot 7^1 = 4^1 \cdot 7^1$ ，数组对 $a = [2, 7]$ ，$p = [2, 1]$ 是正确的，但数组对 $a = [4, 7]$ ，$p = [1, 1]$ 是不正确的，因为 $4 = 2^2$ 是由非不同质数相乘得到的。
你的任务是在所有可能的数组 $a$ 和 $p$ 对中，找到 $\sum a_i \cdot p_i$ （即 $a_1\cdot p_1 + a_2\cdot p_2 + \ldots$ ）的最大值。注意，你不需要最小化或最大化数组的长度。

## 说明/提示
在第一个测试用例中，$100 = 10^2$ ，所以当 $a = [10]$ ，$p = [2]$ 时，$\sum a_i \cdot p_i$ 达到最大值 $10\cdot 2 = 20$ 。同样，$a = [100]$ ，$p = [1]$ 不成立，因为 $100$ 不是由不同的质因数组成的。
在第二个测试用例中，我们可以将 $10$ 看作 $10^1$ ，所以 $a = [10]$ ，$p = [1]$ 。注意，当 $10 = 2^1\cdot 5^1$ 时，$\sum a_i \cdot p_i = 7$ 。

## 样例 #1
### 输入
```
7
100
10
864
130056192
1000000000
2
999999018
```
### 输出
```
20
10
22
118
90
2
333333009
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路都是先对 $n$ 进行质因数分解，然后基于两个大于1的数之积大于等于两数之和的性质（对于质数 $p,q \geq 2$，$p + q + 2 \leq pq + 1$ ），通过将不同质因数乘在一起组成更大因数的方式来构造使 $\sum a_i \cdot p_i$ 最大的分解方案。部分题解给出了具体实现，如分解质因数的方法、对结果数组按指数排序后计算答案等。不同题解在细节处理和代码实现上略有差异。

### 所选的题解
- **作者：D23lhc（4星）**
    - **关键亮点**：思路清晰，不仅阐述了核心思路，还给出了完整且注释详细的代码。代码中分解质因数部分只遍历到 $\sqrt{n}$ ，提高了效率，并且对结果数组按指数从小到大排序后通过循环计算答案，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int, int>a[100000];
int tot = 0;
int x = 1;
void cal(int n)//分解质因数        
{
    for (int i = 2; i*i <= n; i++)
    {//只需遍历到sqrt(n)
        bool flag = 0;//当前数字是否是质因数
        int cnt = 0;//记录指数
        while (n % i == 0)
        {//n除尽这个因数
            cnt++;
            n /= i;
            flag = 1;
        }
        if (flag)
        {
            x *= i;//记录所有不同的质因数的乘积
            a[++tot] = make_pair(cnt, i);//记录底数和指数
        }
        if (n == 1)
            return;
    }
    if (n > 1)
    {//还有大于sqrt(n)的因数
        a[++tot] = make_pair(1, n);
        x *= n;
    }
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        x = 1;
        int n;
        cin >> n;
        tot = 0;
        cal(n);
        sort(a + 1, a + 1 + tot);//按指数从小到大排序
        int ans = 0;//记录答案
        int mi = 0;//记录当前已选择的指数
        for (int i = 1; i <= tot; i++)
        {
            ans += x * (a[i].first - mi);
            mi = a[i].first;//更新选择的指数
            x /= a[i].second;//所有数的乘积减小
            if (x == 1)
                break;
        }
        cout << ans << endl;
    }
    return 0;
}
```
    - **核心实现思想**：`cal` 函数分解质因数，将质因数及其指数记录在 `a` 数组中，同时记录所有不同质因数的乘积 `x` 。主函数中，对 `a` 数组按指数排序后，通过循环每次用当前所有不同质因数乘积 `x` 乘以当前质因数指数与已选指数的差值累加到答案 `ans` 中，并更新已选指数和 `x` 。
- **作者：我梦见一片焦土（4星）**
    - **关键亮点**：代码实现简洁明了，逻辑清晰。先通过函数 `get` 分解质因数，再对结果排序后通过两次循环计算答案，与其他题解相比代码结构更紧凑。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
vector<pair<int,int> >get(int n){
    vector<pair<int,int> >res;
    for(int i=2;i<=n/i;i++){
        if(n%i==0){
            int s=0;
            while(n%i==0){
                n/=i;
                s++;
            }
            res.push_back({s,i});
        }
    }
    if(n>1){
        res.push_back({1,n});
    }
    return res;
}
int t,n;
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        vector<pair<int,int> > res=get(n);
        sort(res.begin(),res.end());
        int sum=1,last=0,ans=0;
        for(int i=0;i<res.size();i++){
            sum*=res[i].second;
        }
        for(int i=0;i<res.size();i++){
            ans+=sum*(res[i].first-last);
            sum/=res[i].second;
            last=res[i].first;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：`get` 函数分解质因数并记录质因数及其指数到 `res` 数组。主函数中先对 `res` 排序，然后第一次循环计算所有质因数的乘积 `sum` ，第二次循环用 `sum` 乘以当前质因数指数与已选指数的差值累加到答案 `ans` 中，并更新已选指数和 `sum` 。

### 最优关键思路或技巧
1. **质因数分解优化**：在分解质因数时，只需遍历到 $\sqrt{n}$，可以减少不必要的计算，提高效率。
2. **基于贪心策略的计算**：利用两个大于1的数之积大于等于两数之和的性质，将不同质因数组合成更大因数，通过对质因数按指数排序后逐步计算因数与幂指数乘积之和，以得到最大值。

### 可拓展思路
此类题目属于数论中基于质因数分解和贪心策略的问题。类似套路包括先进行质因数分解，再根据题目要求对质因数进行组合或分配，以满足特定的优化目标（如求最大、最小等）。同类型题可能会在质因数的使用规则、组合方式或优化目标上进行变化。

### 洛谷相似题目推荐
1. **P1072 [NOIP2009 普及组]  Hankson 的趣味题**：同样涉及数论中对数字分解及性质运用，通过对最大公约数和最小公倍数的条件限制，求解满足条件的数的个数。
2. **P2568 GCD**：需要利用质因数分解来计算多个数的最大公约数相关问题，考察对质因数性质的理解和运用。
3. **P3951 小凯的疑惑**：虽然表面是关于数论中不定方程的问题，但本质也涉及到对数字性质的分析和贪心思想的运用，与本题在思维方式上有相似之处。 

---
处理用时：63.55秒