# 题目信息

# The Number of Pairs

## 题目描述

You are given three positive (greater than zero) integers $ c $ , $ d $ and $ x $ .

You have to find the number of pairs of positive integers $ (a, b) $ such that equality $ c \cdot lcm(a, b) - d \cdot gcd(a, b) = x $ holds. Where $ lcm(a, b) $ is the least common multiple of $ a $ and $ b $ and $ gcd(a, b) $ is the greatest common divisor of $ a $ and $ b $ .

## 说明/提示

In the first example, the correct pairs are: ( $ 1, 4 $ ), ( $ 4,1 $ ), ( $ 3, 6 $ ), ( $ 6, 3 $ ).

In the second example, the correct pairs are: ( $ 1, 2 $ ), ( $ 2, 1 $ ), ( $ 3, 3 $ ).

## 样例 #1

### 输入

```
4
1 1 3
4 2 6
3 3 7
2 7 25```

### 输出

```
4
3
0
8```

# AI分析结果

### 题目翻译
## 数对的数量

### 题目描述
给定三个正整数（大于零）$ c $、$ d $ 和 $ x $。

需要找出满足等式 $ c \cdot lcm(a, b) - d \cdot gcd(a, b) = x $ 的正整数数对 $ (a, b) $ 的数量。其中 $ lcm(a, b) $ 是 $ a $ 和 $ b $ 的最小公倍数，$ gcd(a, b) $ 是 $ a $ 和 $ b $ 的最大公约数。

### 说明/提示
在第一个样例中，正确的数对是：( $ 1, 4 $ )、( $ 4,1 $ )、( $ 3, 6 $ )、( $ 6, 3 $ )。

在第二个样例中，正确的数对是：( $ 1, 2 $ )、( $ 2, 1 $ )、( $ 3, 3 $ )。

### 样例 #1
#### 输入
```
4
1 1 3
4 2 6
3 3 7
2 7 25
```
#### 输出
```
4
3
0
8
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过数学推导将给定等式进行变形，然后利用枚举和质因数分解的方法来计算满足条件的数对数量。具体步骤如下：
1. **数学推导**：设 $ \gcd(a,b) = g $，将 $ a = g \times a' $，$ b = g \times b' $（其中 $ \gcd(a', b') = 1 $）代入原式，经过化简得到 $ g \times (c \times a' \times b' - d) = x $，进而得到 $ c \times a' \times b' - d = \frac{x}{g} $。
2. **枚举因数**：枚举 $ x $ 的所有因数 $ g $，对于每个因数 $ g $，计算 $ y = \frac{x}{g} $，并检查 $ \frac{y + d}{c} $ 是否为整数。
3. **质因数分解**：若 $ \frac{y + d}{c} $ 为整数，设其值为 $ k $，由于 $ a' $ 和 $ b' $ 互质，所以 $ k $ 的每个质因数要么全部分配给 $ a' $，要么全部分配给 $ b' $，因此满足条件的数对 $ (a', b') $ 的数量为 $ 2^{t} $，其中 $ t $ 是 $ k $ 的不同质因数的个数。
4. **累加结果**：将每个因数 $ g $ 对应的 $ 2^{t} $ 累加到答案中。

不同题解的主要区别在于质因数个数的预处理方式和代码实现细节。一些题解使用线性筛预处理每个数的质因数个数，而另一些题解则使用埃拉托色尼筛法预处理最小质因数，然后在需要时进行质因数分解。

### 所选题解
- **作者：Andy_Li (赞：11)，4星**
  - **关键亮点**：思路清晰，代码注释详细，使用线性筛预处理每个数的质因数个数，时间复杂度较低。
  - **个人心得**：感谢[Wf_yjqd](https://www.luogu.com.cn/user/526094)帮忙调过。
- **作者：H6_6Q (赞：9)，4星**
  - **关键亮点**：思路简洁明了，代码实现简洁，同样使用线性筛预处理质因数个数。
- **作者：Warriors_Cat (赞：6)，4星**
  - **关键亮点**：思路和代码都很清晰，对推导过程的解释详细，线性筛预处理质因数个数。

### 重点代码
以下是 Andy_Li 题解的核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int,int> mp;
int vis[20000010];
int prime[5000010],cnt=0,N=2e7;

// 欧拉筛预处理质因数个数
void oula()
{
    for(int i=2;i<=N;i++)
    {
        if(vis[i]==0)
        {
            prime[++cnt]=i;
            vis[i]=1;
        }
        for(int j=1;j<=cnt && i*prime[j]<=N;j++)
        {
            mp[i%prime[j]]=1;
            vis[i*prime[j]]=vis[i]+1;
            if(i%prime[j]==0)
            {
                vis[i*prime[j]]=vis[i];
                break;
            }
        }
    }
    return ;
}

int main()
{
    cin.tie(0);
    std::ios::sync_with_stdio(false);
    int t;
    cin>>t;
    oula();
    while(t--)
    {
        ll c,d,x,ans=0;
        cin>>c>>d>>x;
        // 枚举 x 的因数
        for(int i=1;i*i<=x;i++)
            if(x%i==0)
            {
                ll y1=i,y2=x/i;
                if((y1+d)%c==0)
                {
                    ll k1k2=(y1+d)/c;
                    ans+=(1ll<<(1ll*vis[k1k2]));
                }
                if(y1==y2)
                    continue;
                if((y2+d)%c==0)
                {
                    ll k1k2=(y2+d)/c;
                    ans+=(1ll<<(1ll*vis[k1k2])); 
                }
            }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：
1. `oula` 函数使用欧拉筛预处理每个数的质因数个数，存储在 `vis` 数组中。
2. 在 `main` 函数中，首先调用 `oula` 函数进行预处理，然后对于每组询问，枚举 $ x $ 的因数，对于每个因数 $ y $，检查 $ (y + d) $ 是否能被 $ c $ 整除，若能，则计算 $ k1k2 = \frac{y + d}{c} $，并将 $ 2^{vis[k1k2]} $ 累加到答案中。

### 最优关键思路或技巧
- **数学推导**：通过设 $ \gcd(a,b) = g $，将原式进行变形，将问题转化为枚举 $ x $ 的因数和质因数分解的问题。
- **线性筛预处理**：使用线性筛预处理每个数的质因数个数，避免了在每次询问时进行质因数分解，降低了时间复杂度。

### 拓展思路
同类型题目通常涉及数学推导和数论知识，例如求满足特定等式的数对数量、计算数的因数个数、质因数分解等。类似的算法套路包括：
- 利用数学公式将问题进行转化，简化计算。
- 使用筛法预处理一些数论函数，如质因数个数、欧拉函数等。
- 枚举因数时，通过 $ i \times i \leq n $ 的方式将时间复杂度从 $ O(n) $ 降低到 $ O(\sqrt{n}) $。

### 推荐题目
1. [P1072  Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及最大公约数和最小公倍数的计算，与本题思路类似。
2. [P1463  [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：需要对因数和质因数的性质有深入理解。
3. [P2152  [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察高精度计算和最大公约数的求解。

### 个人心得总结
- Andy_Li 感谢 Wf_yjqd 帮忙调试，说明在解题过程中，他人的帮助和交流可能会对解决问题有很大的帮助。
- zjjws 提到赛场上式子推对了都没写出来，提醒我们在比赛中不仅要能推导出正确的式子，还要有良好的代码实现能力和时间管理能力。

---
处理用时：61.41秒