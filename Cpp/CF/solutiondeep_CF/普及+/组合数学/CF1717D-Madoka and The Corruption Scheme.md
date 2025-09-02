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

在这场锦标赛中，比赛按照“奥运赛制”进行。换句话说，锦标赛有 $2^n$ 名参赛者，编号为从 $1$ 到 $2^n$ 的整数。锦标赛总共有 $n$ 轮。在第 $i$ 轮中，有 $2^{n - i}$ 场比赛，每场比赛在两名选手之间进行（一名在左，一名在右），之后获胜者将进入下一轮比赛，而失败的参赛者将被淘汰。此外，下一轮中选手的相对顺序不会改变。锦标赛的获胜者是最后剩下的参赛者。

但参赛者的编号越小，如果他获胜，他给Madoka的报酬就越多，所以Madoka希望编号最小的参赛者获胜。为此，她可以随意安排第一轮的参赛者，还可以决定每场比赛的获胜者是左边的参赛者还是右边的参赛者。

但Madoka知道，锦标赛赞助商最多可以改变 $k$ 场比赛的获胜者。（也就是说，如果在改变之前左边的参赛者获胜，那么改变之后右边的参赛者将获胜；如果右边的参赛者获胜，那么改变之后左边的参赛者将获胜）。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)
所以，第一张图展示了Madoka安排的比赛赛程，其中红线表示应该获胜的选手。第二张图展示了赞助商改变一场比赛结果后的比赛赛程（1号和3号选手之间的比赛）。
请输出Madoka无论赞助商如何改变比赛结果都能得到的锦标赛获胜者的最小可能编号。但由于答案可能非常大，请将其对 $10^9 + 7$ 取模后输出。注意，我们需要先最小化答案，然后再取模。

## 说明/提示
在第一个样例中，只有一场1号和2号选手之间的比赛，所以赞助商总是可以让2号选手获胜。
第二个样例的比赛赛程在题目描述的图片中展示。

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

### 综合分析与结论
- **思路**：各题解核心思路一致，均将问题转化为求在锦标赛树中，赞助商最多改变 $k$ 次比赛结果时，能让成为冠军的人的最小最大编号，即属性值二进制表示中 $0$ 的个数小于等于 $k$ 的人数，可通过组合数 $\sum_{i=0}^{\min(n,k)}C_{n}^{i}$ 计算。
- **算法要点**：
    - 构建锦标赛树模型，将比赛过程抽象为树结构。
    - 利用组合数计算满足条件的人数。
    - 运用快速幂和逆元计算组合数取模结果。
- **解决难点**：
    - 如何将比赛过程转化为树结构并分析赞助商操作。各题解通过将比赛过程倒推、对节点编号等方式，将问题转化为树的路径问题。
    - 组合数的计算与取模。使用快速幂和逆元解决组合数取模问题，避免大数运算溢出。

### 所选题解
- **Hedgehog_210508（5星）**：
    - **关键亮点**：思路清晰，通过具体例子展示将比赛转化为树的过程，代码实现完整，对组合数计算和取模处理详细。
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
核心实现思想：先判断 $k$ 是否大于等于 $n$，若是则直接输出 $2^n$。然后预处理阶乘数组 $p$，通过快速幂函数 $qp$ 计算逆元，利用组合数公式 $c$ 计算组合数，最后累加组合数得到结果。
- **whhsteven（4星）**：
    - **关键亮点**：思路阐述详细，对节点属性值的定义和性质分析清晰，时间复杂度分析明确。
    - **核心思路**：为每个节点定义属性值，根据属性值二进制表示中 $0$ 的个数与 $k$ 的关系确定能成为冠军的节点，进而得出答案为 $\sum_{i=0}^{\min(n,k)}\binom{n}{i}$。
- **DaiRuiChen007（4星）**：
    - **关键亮点**：思路简洁，代码规范，对判断节点能否获胜的条件分析清晰。
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
核心实现思想：预处理阶乘数组 $fac$ 和逆元数组 $inv$，通过快速幂函数 $ksm$ 计算逆元，利用组合数函数 $C$ 计算组合数，最后累加组合数得到结果。

### 最优关键思路或技巧
- **思维方式**：将比赛过程转化为树结构，通过树的路径分析赞助商的操作，将问题转化为组合数计算。
- **算法优化**：使用快速幂和逆元计算组合数取模结果，避免大数运算溢出。

### 拓展思路
同类型题或类似算法套路：
- 其他比赛赛制相关问题，如淘汰赛、循环赛等，可通过构建图或树结构分析比赛过程。
- 组合计数问题，涉及到排列组合的计算和取模，可使用快速幂和逆元解决。

### 推荐题目
- [P1869 愚蠢的组合数](https://www.luogu.com.cn/problem/P1869)
- [P2679 子串分值和](https://www.luogu.com.cn/problem/P2679)
- [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)

### 个人心得摘录与总结
- **fast_photon**：有过多次组合数带取模正向枚举结果 $k>n$ 然后出错的经历，因此养成反向枚举的习惯。总结：在处理组合数取模问题时，要注意边界情况和枚举顺序，避免出错。 

---
处理用时：46.61秒