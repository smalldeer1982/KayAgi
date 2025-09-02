# 题目信息

# [USACO05OPEN] Lazy Cows G

## 题目描述

地母是这个世界上大地的主宰，在她眼中整个大地呈现两行 $n$ 列的一个状态。在这个大地上如珍珠般散落着各种宝藏，每个宝藏占据一个格子。不过这个消息让天公知道了，他想抢走这些宝藏。地母决定用「无极」牌帆布盖住这些宝藏。

「无极」牌帆布是矩形状的，而且地母现在手头比较紧，她决定用 $k$ 块帆布盖住所有的宝藏。现在希望你求出这 $k$ 块帆布的面积之和的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 1.5 \times 10^7$，$1 \leq k \leq m \leq 10^3$。

## 样例 #1

### 输入

```
8 2 9
1 2
1 6
1 7
1 8
1 9
2 2
2 3
2 4```

### 输出

```
10```

# AI分析结果

### 算法分类
动态规划

### 综合分析与结论
该题解通过动态规划的思路，结合离散化处理，有效地解决了覆盖问题。难点在于如何定义状态和转移方程，题解通过定义五种状态（上下没有矩形、上面没矩形、下面没矩形、上下都有矩形但不联通、上下都有矩形且联通）来覆盖所有可能的情况，并通过转移方程逐步求解最小面积。

### 所选题解
#### 题解作者：SentoAyaka
- **星级**: 4星
- **关键亮点**: 使用了动态规划结合离散化的方法，状态定义清晰，转移方程合理，代码实现较为简洁。
- **个人心得**: 通过离散化处理，减少了状态转移的复杂度，提高了算法的效率。

### 核心代码实现思想
```cpp
int n,m,K,dp[2][N][5];bitset<M> mp[2];
inline void chkmin(int &x,int y){if(x>y)x=y;}
void MAIN(){
    m=read(),K=read(),n=read();vec w;
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        mp[x-1][y]=1;w.pb(y);
    }
    sort(w.begin(),w.end()),w.erase(unique(w.begin(),w.end()),w.end());
    memset(dp,0x3f,sizeof dp);
    int tot=w.size();dp[0][0][0]=0;
    for(int i=0;i<tot;i++){
        int x=w[i],val=((i==0||i==tot)?1:w[i]-w[i-1]);auto &f=dp[i&1],&g=dp[i&1^1];
        memset(g,0x3f,sizeof g);
        for(int j=0;j<=K;j++){
            if(!mp[0][x]&&!mp[1][x])chkmin(g[j][0],f[j][0]);
            if(!mp[0][x])chkmin(g[j][1],f[j][1]+1*val);
            if(!mp[1][x])chkmin(g[j][2],f[j][2]+1*val);
            chkmin(g[j][3],f[j][3]+2*val);
            chkmin(g[j][4],f[j][4]+2*val);
            int res=inf;for(int k=0;k<=4;k++)chkmin(res,f[j][k]);
            chkmin(g[j+1][4],res+2);
            chkmin(g[j+2][3],res+2),
            chkmin(g[j+1][3],min(f[j][1],f[j][2])+1+val);
            if(!mp[0][x]){
                int op=1;
                chkmin(g[j+1][op],res+1),chkmin(g[j][op],f[j][3]+val);
            }
            if(!mp[1][x]){
                int op=2;
                chkmin(g[j+1][op],res+1),chkmin(g[j][op],f[j][3]+val);
            }
        }
    }
    int ans=inf;
    for(int j=0;j<=K;j++)for(int k=0;k<=4;k++)chkmin(ans,dp[tot&1][j][k]);
    cout<<ans<<"\n";
}
```

### 关键思路或技巧
1. **状态定义**: 通过定义五种状态来覆盖所有可能的矩形覆盖情况。
2. **离散化**: 通过离散化处理，减少了状态转移的复杂度，提高了算法的效率。
3. **转移方程**: 通过合理的转移方程，逐步求解最小面积。

### 可拓展之处
类似的问题可以通过动态规划结合离散化的方法来解决，例如覆盖问题、区间选择问题等。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1064 [NOIP2006 提高组] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

---
处理用时：27.18秒