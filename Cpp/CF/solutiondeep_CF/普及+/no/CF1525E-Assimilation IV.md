# 题目信息

# Assimilation IV

## 题目描述

Monocarp is playing a game "Assimilation IV". In this game he manages a great empire: builds cities and conquers new lands.

Monocarp's empire has $ n $ cities. In order to conquer new lands he plans to build one Monument in each city. The game is turn-based and, since Monocarp is still amateur, he builds exactly one Monument per turn.

Monocarp has $ m $ points on the map he'd like to control using the constructed Monuments. For each point he knows the distance between it and each city. Monuments work in the following way: when built in some city, a Monument controls all points at distance at most $ 1 $ to this city. Next turn, the Monument controls all points at distance at most $ 2 $ , the turn after — at distance at most $ 3 $ , and so on. Monocarp will build $ n $ Monuments in $ n $ turns and his empire will conquer all points that are controlled by at least one Monument.

Monocarp can't figure out any strategy, so during each turn he will choose a city for a Monument randomly among all remaining cities (cities without Monuments). Monocarp wants to know how many points (among $ m $ of them) he will conquer at the end of turn number $ n $ . Help him to calculate the expected number of conquered points!

## 说明/提示

Let's look at all possible orders of cities Monuments will be build in:

- $ [1, 2, 3] $ : 
  - the first city controls all points at distance at most $ 3 $ , in other words, points $ 1 $ and $ 4 $ ;
  - the second city controls all points at distance at most $ 2 $ , or points $ 1 $ , $ 3 $ and $ 5 $ ;
  - the third city controls all points at distance at most $ 1 $ , or point $ 1 $ .
  
   In total, $ 4 $ points are controlled.
- $ [1, 3, 2] $ : the first city controls points $ 1 $ and $ 4 $ ; the second city — points $ 1 $ and $ 3 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [2, 1, 3] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [2, 3, 1] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [3, 1, 2] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ and $ 3 $ ; the third city — points $ 1 $ and $ 5 $ . In total, $ 3 $ points.
- $ [3, 2, 1] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — points $ 1 $ and $ 5 $ . In total, $ 3 $ points.

 The expected number of controlled points is $ \frac{4 + 3 + 3 + 3 + 3 + 3}{6} $ $ = $ $ \frac{19}{6} $ or $ 19 \cdot 6^{-1} $ $ \equiv $ $ 19 \cdot 166374059 $ $ \equiv $ $ 166374062 $ $ \pmod{998244353} $

## 样例 #1

### 输入

```
3 5
1 4 4 3 4
1 4 1 4 2
1 4 4 4 3```

### 输出

```
166374062```

# AI分析结果

### 题目内容（中文重写）
# 同化 IV

## 题目描述
Monocarp正在玩一款名为“同化 IV”的游戏。在这个游戏中，他管理着一个伟大的帝国：建造城市并征服新的土地。

Monocarp的帝国有 $n$ 座城市。为了征服新的土地，他计划在每座城市建造一座纪念碑。游戏是回合制的，由于Monocarp还是个新手，他每回合恰好建造一座纪念碑。

Monocarp在地图上有 $m$ 个他想要用建造的纪念碑控制的点。对于每个点，他都知道该点与每座城市之间的距离。纪念碑的工作方式如下：当在某座城市建造纪念碑后，该纪念碑在第一回合控制所有与该城市距离至多为 $1$ 的点；下一回合，控制所有距离至多为 $2$ 的点；再下一回合，控制所有距离至多为 $3$ 的点，依此类推。Monocarp将在 $n$ 个回合内建造 $n$ 座纪念碑，他的帝国将征服所有至少被一座纪念碑控制的点。

Monocarp想不出任何策略，所以在每个回合，他将在所有剩余的城市（没有纪念碑的城市）中随机选择一座城市建造纪念碑。Monocarp想知道在第 $n$ 回合结束时，他将征服多少个点（在 $m$ 个点中）。请帮助他计算被征服点的期望数量！

## 说明/提示
让我们看看建造纪念碑的城市的所有可能顺序：
- $ [1, 2, 3] $ ： 
  - 第一座城市控制所有距离至多为 $3$ 的点，换句话说，是点 $1$ 和 $4$ ；
  - 第二座城市控制所有距离至多为 $2$ 的点，即点 $1$ 、 $3$ 和 $5$ ；
  - 第三座城市控制所有距离至多为 $1$ 的点，即点 $1$ 。
  
  总共控制了 $4$ 个点。
- $ [1, 3, 2] $ ：第一座城市控制点 $1$ 和 $4$ ；第二座城市控制 点 $1$ 和 $3$ ；第三座城市控制 点 $1$ 。总共控制了 $3$ 个点。
- $ [2, 1, 3] $ ：第一座城市控制 点 $1$ ；第二座城市控制 点 $1$ 、 $3$ 和 $5$ ；第三座城市控制 点 $1$ 。总共控制了 $3$ 个点。
- $ [2, 3, 1] $ ：第一座城市控制 点 $1$ ；第二座城市控制 点 $1$ 、 $3$ 和 $5$ ；第三座城市控制 点 $1$ 。总共控制了 $3$ 个点。
- $ [3, 1, 2] $ ：第一座城市控制 点 $1$ ；第二座城市控制 点 $1$ 和 $3$ ；第三座城市控制 点 $1$ 和 $5$ 。总共控制了 $3$ 个点。
- $ [3, 2, 1] $ ：第一座城市控制 点 $1$ ；第二座城市控制 点 $1$ 、 $3$ 和 $5$ ；第三座城市控制 点 $1$ 和 $5$ 。总共控制了 $3$ 个点。

被控制的点的期望数量是 $ \frac{4 + 3 + 3 + 3 + 3 + 3}{6} $ $ = $ $ \frac{19}{6} $ 或 $ 19 \cdot 6^{-1} $ $ \equiv $ $ 19 \cdot 166374059 $ $ \equiv $ $ 166374062 $ $ \pmod{998244353} $

## 样例 #1

### 输入
```
3 5
1 4 4 3 4
1 4 1 4 2
1 4 4 4 3
```

### 输出
```
166374062
```

### 算法分类
概率论

### 综合分析与结论
这些题解的核心思路都是将每个点被控制的概率分开计算，再求和得到期望控制的点的个数。由于直接计算每个点被控制的排列数较困难，大部分题解采用了补集转化的方法，即先计算每个点不被控制的排列数，再用总排列数减去不被控制的排列数得到被控制的排列数，进而求得概率。

各题解的算法要点主要包括：
1. **预处理距离信息**：统计每个点到各城市不同距离的城市数量。
2. **计算总排列数**：$n$ 个城市的全排列数为 $n!$。
3. **计算不被控制的排列数**：根据点不被控制的条件，利用乘法原理计算不被控制的排列数。
4. **计算概率并求和**：用总排列数的逆元乘以不被控制的排列数得到不被控制的概率，用 $1$ 减去不被控制的概率得到被控制的概率，最后将所有点的被控制概率求和。

解决的难点在于如何高效地计算每个点不被控制的排列数，大部分题解通过合理的循环和乘法原理解决了这个问题。

### 所选题解
- **7KByte（4星）**：
  - **关键亮点**：思路清晰，代码简洁，直接计算不被控制的排列数，时间复杂度较低。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 50005
#define P 998244353
using namespace std;
int n,m,c[N][22];
int Pow(int x,int y){
    int now=1;
    for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;
    return now;
}
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,n){
        rep(j,1,m){
            int x;scanf("%d",&x);
            c[j][x]++;
        }
    }
    int ed=0,fac=1;
    rep(i,1,n)fac=1LL*fac*i%P;
    rep(i,1,m){
        int sum=0,ans=1;
        pre(j,n,1)sum+=c[i][j+1],ans=1LL*ans*sum%P,sum--;
        ed=(ed+1-1LL*Pow(fac,P-2)*ans%P+P)%P;
    }
    printf("%d\n",ed);
    return 0;
} 
```
  - **核心实现思想**：先统计每个点到各城市不同距离的城市数量，然后计算 $n$ 的阶乘。对于每个点，从后往前计算不被控制的排列数，最后用 $1$ 减去不被控制的概率并累加得到答案。
- **monstersqwq（4星）**：
  - **关键亮点**：代码中加入了特判，逻辑清晰，对补集转化的思路解释详细。
  - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#include<cmath>
#include<ctime>
#define mod 998244353
using namespace std;
typedef long long ll;
ll qpow(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
ll inv(ll a)
{
    return qpow(a,mod-2);
}
ll fac(int a)
{
    ll res=1;
    for(int i=1;i<=a;i++) res=(res*i)%mod;
    return res;
}
int n,m;
int d[25][50005];
ll ans=0;
bool vis[50005];
int pos[25];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&d[i][j]);
            if(d[i][j]==1) vis[j]=true;
        }
    }
    ll tmp=inv(fac(n));
    for(int i=1;i<=m;i++)
    {
        if(vis[i])
        {
            ans=(ans+1)%mod;continue;
        }
        ll res=1;
        for(int j=1;j<=n;j++)
        {
            pos[j]=d[j][i]-1;
        }
        sort(pos+1,pos+n+1);
        bool flag=false;
        for(int j=1;j<=n;j++)
        {
            if(pos[j]-j+1<=0)
            {
                flag=true;break;
            }
            res=res*(pos[j]-j+1)%mod;
        }
        if(flag)
        {
            ans=(ans+1)%mod;continue;
        }
        res=(res*tmp)%mod;
        ans=(ans+1-res+mod)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
```
  - **核心实现思想**：先读入数据，标记距离为 $1$ 的点。对于每个点，如果有距离为 $1$ 的城市，则该点必然被控制；否则，将距离减 $1$ 后排序，计算不被控制的排列数，最后用 $1$ 减去不被控制的概率并累加得到答案。
- **Erica_N_Contina（4星）**：
  - **关键亮点**：思路解释详细，对正难则反的思想阐述清晰，代码实现简洁。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int MOD=998244353;
const int INF=1e5;

int n,m,p,q,T,fac[N],ans;
int c[N][22];

int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int rd(){
    int t;
    cin>>t;
    return t;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        c[j][rd()]++;//c[j][k]表示离点j距离为k的点的个数
    }
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=(i*fac[i-1])%MOD;
    int inv=ksm(fac[n],MOD-2);
    for(int i=1;i<=m;i++){
        int sum=0,tmp=1;
        for(int j=n;j;j--){
            sum+=c[i][j+1];
            tmp=tmp*sum%MOD;
            sum--;
        }
        ans=(ans+1-inv*tmp%MOD+MOD)%MOD;//1为总方案的概率，inv*tmp为不合法的概率
    }
    cout<<ans<<endl;               
}
```
  - **核心实现思想**：先统计每个点到各城市不同距离的城市数量，计算 $n$ 的阶乘及其逆元。对于每个点，从后往前计算不被控制的排列数，最后用 $1$ 减去不被控制的概率并累加得到答案。

### 最优关键思路或技巧
- **补集转化**：当直接计算某个事件发生的情况数较困难时，考虑计算其对立事件的情况数，再用总情况数减去对立事件的情况数得到该事件的情况数。
- **乘法原理**：在计算排列数时，利用乘法原理逐步确定每个位置的可选方案数，从而高效计算出总的排列数。

### 拓展思路
同类型题或类似算法套路：
- 涉及随机事件的期望计算问题，通常可以将每个事件的期望分开计算，再求和得到总期望。
- 当正面计算复杂时，考虑补集转化，将问题转化为更容易计算的对立问题。

### 推荐洛谷题目
1. [P1297 [国家集训队]单选错位](https://www.luogu.com.cn/problem/P1297)
2. [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)
3. [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)

### 个人心得摘录与总结
- **喵仔牛奶**：提到做这道 $2100$ 难度的题花了很长时间，说明该题有一定难度。
总结：这类期望计算的题目通常需要巧妙的思维转化，如补集转化等，在解题时需要仔细分析问题，找到合适的解题方法。 

---
处理用时：95.08秒