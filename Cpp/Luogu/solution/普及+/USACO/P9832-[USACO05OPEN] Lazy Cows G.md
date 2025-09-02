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

# 题解

## 作者：SentoAyaka (赞：1)

离散化后考虑设 $f_{i,j,0\sim 4}$ 表示到 $i$，用了 $j$ 个矩形，当前上下没有矩形$(0)$，上面没矩形$(1)$，下面没矩形$(2)$，上下都有矩形但不联通$(3)$，上下都有矩形且联通$(4)$，转移即可。

```cpp
const int N=1e3+5,M=1.5e7+5,inf=0x3f3f3f3f;
int n,m,K,dp[2][N][5];bitset<M> mp[2];
inline void chkmin(int &x,int y){if(x>y)x=y;}
//0:no_all
//1:no_up
//2:no_down
//3:all_but_no_connect
//4:all_and_connect
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


---

