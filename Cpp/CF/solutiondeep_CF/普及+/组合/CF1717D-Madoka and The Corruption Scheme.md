# 题目信息

# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
7```

# AI分析结果

### 题目中文重写
# Madoka与比赛腐败方案

## 题目描述
Madoka决定负责组织一场大型电脑游戏锦标赛“OSU”！

在这场锦标赛中，比赛按照“奥运赛制”进行。换句话说，锦标赛有 $2^n$ 名参赛者，编号为从 $1$ 到 $2^n$ 的整数。锦标赛总共进行 $n$ 轮。在第 $i$ 轮中，有 $2^{n - i}$ 场比赛，每场比赛在两名选手之间进行（一名在左，一名在右），比赛结束后，获胜者晋级下一轮，失利者则被淘汰出锦标赛。同时，晋级选手在下一轮中的相对顺序保持不变。而锦标赛的获胜者就是最后剩下的那名选手。

但是，参赛者的编号越小，如果他获胜，给Madoka的报酬就越多，所以Madoka希望编号最小的参赛者获胜。为此，她可以随意安排第一轮的参赛者顺序，还能决定每场比赛的胜者是左边的选手还是右边的选手。

但Madoka知道，锦标赛赞助商最多可以改变 $k$ 场比赛的胜者。（也就是说，如果原本左边的选手获胜，改变后右边的选手将获胜；反之亦然。）

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)
所以，第一张图展示了Madoka安排的比赛赛程，其中红线表示该场比赛的胜者。第二张图展示了赞助商改变一场比赛结果后的赛程（选手 $1$ 和 $3$ 之间的比赛）。

请输出Madoka无论赞助商如何改变比赛结果都能得到的锦标赛获胜者的最小可能编号。但由于答案可能非常大，请将结果对 $10^9 + 7$ 取模。注意，我们需要先最小化答案，然后再取模。

## 说明/提示
在第一个样例中，只有选手 $1$ 和 $2$ 之间的一场比赛，所以赞助商总能让选手 $2$ 获胜。

第二个样例中的比赛赛程在题目描述的图片中展示。

## 样例 #1
### 输入
```
1 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
2 1
```
### 输出
```
3
```

## 样例 #3
### 输入
```
3 2
```
### 输出
```
7
```

### 题解综合分析与结论
- **思路对比**：大部分题解都将比赛过程转化为树结构，从根节点到叶子节点的路径来分析。有的题解（如Hedgehog_210508）将比赛看作树，倒着从上往下走；有的题解（如whhsteven）为每个选手的路径赋予二进制属性值；还有的题解（如zsseg）对节点进行编号，通过二进制中 $1$ 的个数来计算。
- **算法要点**：核心算法是计算组合数 $\sum_{i = 0}^{\min(n, k)}C_{n}^{i}$。不同题解采用不同方法计算组合数，如快速幂和逆元（Hedgehog_210508）、线性递推（zsseg）、预处理逆元（fast_photon）等。
- **解决难点**：主要难点在于如何将比赛过程转化为数学模型，以及处理组合数的计算和取模操作。各题解通过将比赛抽象为树结构、赋予二进制属性值等方式解决了问题转化的难点，通过不同的组合数计算方法解决了计算和取模的问题。

### 所选题解
- **Hedgehog_210508（5星）**
    - **关键亮点**：思路清晰，通过将比赛看作树结构，直观地展示了问题的转化过程；代码实现简洁，对组合数的计算和取模操作处理得当。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 1000000007
ll n,k,p[200009];
ll qp(ll a,ll b){
    if(b==1) return a;
    if(b==0) return 1;
    ll ans=1;
    if(b%2) b--,ans*=a;
    ll tmp=qp(a,b/2);
    ans*=tmp%M*tmp%M;
    return ans%M;
}
ll c(ll a,ll b){
    return p[a]%M*qp(p[b],M-2)%M*qp(p[a-b],M-2)%M; 
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n>>k;
    if(k>=n){
        cout<<qp(2,n);
        return 0;
    }
    p[0]=1;
    for(ll i=1;i<=n;i++) p[i]=p[i-1]*i%M;
    ll tmp=0;
    for(ll i=0;i<=k;i++) tmp+=c(n,i),tmp%=M;
    cout<<tmp;
    return 0;
}
```
    - **核心实现思想**：先判断 $k$ 是否大于等于 $n$，若是则直接输出 $2^n$。然后预处理阶乘数组 $p$，通过快速幂计算逆元，进而计算组合数 $C_{n}^{i}$，最后累加得到结果。
- **whhsteven（4星）**
    - **关键亮点**：思路独特，通过为选手的路径赋予二进制属性值，清晰地阐述了赞助商调整比赛结果与选手获胜的关系，计算过程简洁明了。
    - **核心思路**：将选手到根节点路径上的比赛胜负情况用二进制表示，赞助商送一个人获胜最少调整次数是该二进制表示中 $0$ 的个数。所有属性值二进制表示中 $0$ 的个数小于等于 $k$ 的人都可能成为冠军，答案即为这些人的数量 $\sum_{i = 0}^{\min(n, k)}C_{n}^{i}$。
- **DaiRuiChen007（4星）**
    - **关键亮点**：思路清晰，通过将每个选手到根节点的路径对应一个二进制数，直观地说明了问题的本质；代码实现规范，对组合数的计算和取模操作处理正确。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,MOD=1e9+7;
int fac[MAXN],inv[MAXN];
inline int ksm(int a,int b=MOD-2,int m=MOD) {
    int res=1;
    while(b) {
        if(b&1) res=res*a%m;
        a=a*a%m;
        b=b>>1;
    }
    return res;
}
inline int C(int n,int m) {
    if(m<0||m>n) return 0;
    if(m==0||m==n) return 1;
    return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
} 
signed main() {
    fac[0]=inv[0]=1;
    for(int i=1;i<MAXN;++i) fac[i]=fac[i-1]*i%MOD,inv[i]=ksm(fac[i]);
    int n,k,res=0;
    scanf("%lld%lld",&n,&k);
    for(int i=0;i<=min(n,k);++i) res=(res+C(n,i))%MOD;
    printf("%lld\n",res);
    return 0;
}
```
    - **核心实现思想**：预处理阶乘数组 $fac$ 和逆元数组 $inv$，通过快速幂计算逆元。根据组合数公式 $C_{n}^{m}=\frac{fac[n]}{fac[m] \times fac[n - m]}$ 计算组合数，最后累加得到结果。

### 最优关键思路或技巧
- **思维方式**：将比赛过程抽象为树结构，通过根节点到叶子节点的路径来分析问题，将问题转化为组合数的计算。
- **算法优化**：使用快速幂和逆元计算组合数，避免了除法运算，同时处理了取模操作，提高了计算效率。

### 可拓展之处
同类型题或类似算法套路：
- 其他涉及比赛赛制和结果调整的问题，如淘汰赛、循环赛等，可以采用类似的树结构分析方法。
- 组合数计算在其他计数问题中的应用，如排列组合、二项式定理等。

### 推荐洛谷题目
- [P1869 愚蠢的组合数](https://www.luogu.com.cn/problem/P1869)
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)
- [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)

### 个人心得摘录与总结
- **fast_photon**：提到之前有过多次组合数带取模正向枚举结果 $k > n$ 然后炸飞的经历，养成了反向枚举的习惯。总结：在处理组合数计算和取模操作时，要注意边界情况和枚举顺序，避免出现错误。

---
处理用时：53.66秒