# [GCJ 2022 #1C] Squary

## 题目描述

加法与平方运算不可交换。也就是说，一个整数列表中所有元素的和的平方，不一定等于这些元素各自的平方和。然而，某些列表满足这一性质，例如 $[3,-2,6]$，因为 $(3+(-2)+6)^{2}=49=3^{2}+(-2)^{2}+6^{2}$。我们将这样的列表称为**平方性列表**。

![](https://cdn.luogu.com.cn/upload/image_hosting/qa49q9z1.png)

给定一个（不一定是平方性的）由较小整数构成的列表，我们想知道是否可以通过添加至少 $1$ 个、至多 $\mathbf{K}$ 个元素，使得最终的列表具有平方性。每个添加的元素必须是介于 $-10^{18}$ 和 $10^{18}$（含）之间的整数，且这些元素不必互不相同，也不必与初始列表中的元素不同。

## 说明/提示

**样例解释**

在样例 #1 中，我们可以得到题目描述中的示例列表。

在样例 #2 中，必须恰好添加一个元素 $x$。此时整个列表的和为 $x$，其平方为 $x^{2}$。而所有元素的平方和为 $x^{2}+10^{2}+(-10)^{2}=x^{2}+200 \neq x^{2}$，因此该用例无法实现。

在样例 #3 中，$\left[-10^{18}, 10^{18}\right]$ 范围内的任意整数均为合法答案。

在样例 #4 中，注意输入可能包含重复元素，且通过添加元素创建更多重复也是合法的。

样例 2 符合测试集 2 的限制，但不会用于测试你的提交。

在附加样例的用例 #1 中，我们给出了题目描述中的示例列表（已是平方性列表），但需要至少添加一个元素。添加 0 可以保持列表的平方性。

在附加样例的用例 #3 中，我们展示了一种可能的合法答案。注意可以添加少于 $\mathbf{K}$ 个元素；此处 $\mathbf{K}=12$，但我们仅添加了 11 个元素。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{N} \leq 1000$。
- 对所有 $i$，$-1000 \leq \mathbf{E}_{\mathbf{i}} \leq 1000$。

**测试集 1（9 分，可见判定）**

- 时间限制：5 秒。
- $\mathbf{K}=1$。

**测试集 2（22 分，可见判定）**

- 时间限制：10 秒。
- $2 \leq \mathbf{K} \leq 1000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 1
-2 6
2 1
-10 10
1 1
0
3 1
2 -2 2```

### 输出

```
Case #1: 3
Case #2: IMPOSSIBLE
Case #3: -1000000000000000000
Case #4: 2```

## 样例 #2

### 输入

```
3
3 10
-2 3 6
6 2
-2 2 1 -2 4 -1
1 12
-5```

### 输出

```
Case #1: 0
Case #2: -1 15
Case #3: 1 1 1 1 1 1 1 1 1 1 1```

# 题解

## 作者：Belia (赞：1)

### 题意：

给定一个整数列表，要求添加至少 $1$ 个、至多 $K$ 个整数（范围在 $[-10^{18}, 10^{18}]$ 内），使得最终的列表满足：所有元素之和的平方等于所有元素的平方和。

### 思路：

**核心问题**：设初始列表元素之和为 $S$，平方和为 $Q$，定义 $C = Q - S^2$。我们需要添加 $r$ 个元素 $x_1, x_2, \dots, x_r$（$1 \leq r \leq K$），使得添加后满足：
$$
\left(S + \sum_{i=1}^r x_i\right)^2 = Q + \sum_{i=1}^r x_i^2
$$
展开并整理得：
$$
2S \left(\sum_{i=1}^r x_i\right) + 2 \sum_{1 \leq i < j \leq r} x_i x_j = C
$$

#### 分类讨论
1. **当 $K = 1$ 时（只能添加一个元素 $x$）**：
   - 则方程简化为 $2Sx = C$。
   - 若 $C = 0$，添加 $0$ 即可。
   - 若 $S = 0$ 且 $C \neq 0$，无解。
   - 若 $S \neq 0$ 且 $C$ 能被 $2S$ 整除，则添加 $x = \frac{C}{2S}$。
   - 否则无解。

2. **当 $K \geq 2$ 时**：
   - **情况 1：$C = 0$**
     - 若 $S \leq 0$ 且 $1 - 2S \leq K$，添加 $(1 - 2S)$ 个 $1$。
     - 否则，添加一个 $0$。
   - **情况 2：$C \neq 0$**
     - **子情况 1：$S = 0$**
       - 则方程变为 $2 \sum_{1 \leq i < j \leq r} x_i x_j = C$（$r \geq 2$）。
       - 若 $C$ 是偶数，添加 $1$ 和 $\frac{C}{2}$。
       - 否则无解。
     - **子情况 2：$S \neq 0$**
       - 尝试添加一个数：若 $C$ 能被 $2S$ 整除，添加 $x = \frac{C}{2S}$。
       - 否则尝试添加两个数：取 $x = 1 - S$，则 $y = \left \lfloor\frac{C - 2S(1 - S)}{2}\right \rfloor $。
       - 最后尝试枚举 $x \in [-10, 10]$ 且 $x \neq -S$，求解 $y$。
       - 若以上均不满足，无解（理论上不会发生）。

时间复杂度为 $\mathcal{O}(T \cdot N + T \cdot k)$，其中 $T$ 为测试用例数，$N$ 为初始列表长度，$k$ 为常数。处理每个测试用例时，计算 $S$ 和 $Q$ 为 $\mathcal{O}(N)$，后续操作为常数时间。

### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long//#define ll long long你值得拥有
using namespace std;
const int maxn=1e3+5;
ll t,n,k,a[maxn];
void solve(ll cas)
{
    ll sum=0,sq=0;
    for(ll i=1;i<=n;i++)
    sum+=a[i],sq+=a[i]*a[i];
    ll C=sq-sum*sum;
    if(k==1)
    {
        if(C==0)
        {
            cout<<"Case #"<<cas<<": 0\n";
            return;
        }
        if(sum==0)
        {
            cout<<"Case #"<<cas<<": IMPOSSIBLE\n";
            return;
        }
        if(C%(2*sum)==0)
        {
            ll x=C/(2*sum);
            cout<<"Case #"<<cas<<": "<<x<<"\n";
            return;
        }
        cout<<"Case #"<<cas<<": IMPOSSIBLE\n";
        return;
    }
    if(C==0)
    {
        if(sum<=0&&(1-2*sum)<=k)
        {
            cout<<"Case #"<<cas<<":";
            for(int i=0;i<1-2*sum;i++)
            cout<<" 1";
            cout<<"\n";
            return;
        }
        cout<<"Case #"<<cas<<": 0\n";
        return;
    }
    if(sum==0)
    {
        if(C%2==0)
        {
            cout<<"Case #"<<cas<<": 1 "<<C/2<<"\n";
            return;
        }
        cout<<"Case #"<<cas<<": IMPOSSIBLE\n";
        return;
    }
    if(C%(2*sum)==0)
    {
        ll x=C/(2*sum);
        cout<<"Case #"<<cas<<": "<<x<<"\n";
        return;
    }
    ll tmp=C-2*sum*(1-sum);
    if(tmp%2==0)
    {
        ll x=1-sum,y=tmp/2;
        cout<<"Case #"<<cas<<": "<<x<<" "<<y<<"\n";
        return;
    }
    ll ok=0,ansx,ansy;
    for(ll x=-10;x<=10;x++)
    {
        if(x==-sum)
		continue;
        ll t=C-2*sum*x,d=2*(sum+x);
        if(d==0)
		continue;
        if(t%d==0)
        {
            ok=1,ansx=x,ansy=t/d;
            break;
        }
    }
    if(ok)
    cout<<"Case #"<<cas<<": "<<ansx<<" "<<ansy<<"\n";
    else
    cout<<"Case #"<<cas<<": IMPOSSIBLE\n";
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//cincout加速代码
    cin>>t;
    for(ll i=1;i<=t;i++)
    {
        cin>>n>>k;
        for(ll j=1;j<=n;j++)
        cin>>a[j];
        solve(i);
    }
    return 0;
}
```
不容易啊。。。

---

## 作者：qwqerty (赞：1)

令 $s=\sum\limits_{i=1}^{N} E_i$，$q=\sum\limits_{i=1}^{N} E_i^2$。容易证明 $s\equiv q \pmod{2}$。故 $s\not\equiv q \pmod{2}$ 一定无解。  
先把 $s^2=q$ 的情况判掉。  
考虑 $k=1$ 时的情况，设增添的数为 $x$，则有 $(s+x)^2=q+x^2$。即 $2sx+(s^2-q)=0$，解得 $x=\dfrac{q-s^2}{2s}$。若 $2s\nmid q-s^2$ 则无解。  
若 $k=2$，设增添的两个数为 $x$ 和 $y$，则有 $(s+x+y)^2=q+x^2+y^2$，即 $2xy+2sx+2sy+(s^2-q)=0$。取 $x=1-s,y=\dfrac{q+s^2-2s}{2}$。在 $s\equiv q \pmod{2}$ 时一定有解。所以对于 $k>2$ 时的情况也可以使用此构造方法。

---

