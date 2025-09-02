# [COTS 2013] 图形计数 / POLIGONI

## 题目描述

枚举平面直角坐标系具有下列性质的多边形：

- 多边形顶点为坐标系整数点。
- 多边形每条边平行于坐标轴。
- 对于顶点 $(x,y)$，满足 $0 \le x \le N,0\le y\le K$。

形状相同，位置不同的两个多边形我们认为是不同的，且根据定义，多边形的边是一条不接触自身的闭合多边形线。

下图显示了一个合法的多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/at50ulf8.png)

下图显示了两个不合法的多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/snvgig3p.png)

## 说明/提示

【数据范围与约定】

- 对于所有数据，均满足 $1\le K \le 6,1 \le N \le 1000$。

| 测试点编号 | $K=$ | $N\le$ | 特殊性质 | 分值 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $1$ | $1000$ | 是 | $5$  |
| $2$ | $1$ | $1000$ | 否 | $5$ |
| $3$ | $2$ | $1000$ | 是 | $5$ |
| $4$ | $2$ |$1000$  | 否 | $5$  |
| $5$ | $3$ | $1000$ | 是 | $10$ |
| $6$ | $3$ |$1000$  | 否 |$10$  |
| $7$ | $4$ |$1000$  | 是 | $10$ |
| $8$ | $4$ | $1000$ | 否 | $10$ |
| $9,10$ | $5$ | $1000$ | 否 |$10$  |
| $11,12$ | $6$ |$1000$  | 否  |$10$  |

- 特殊性质： $N\times K \le 20$。

## 样例 #1

### 输入

```
2 2 ```

### 输出

```
13```

## 样例 #2

### 输入

```
3 2```

### 输出

```
40```

## 样例 #3

### 输入

```
3 3 ```

### 输出

```
213 ```

# 题解

## 作者：BreakPlus (赞：0)

一个莫名其妙的题。

将所有在多边形内的点视作黑点，否则视作白点。

则一个黑白染色方案能对应一个合法的多边形的充要条件是：

+ 不存在以下 $2\times2$ 的子矩形：

> 左上、右下同色，左下、右上同色，左上、左下异色。

+ 不存在一个白色格子被黑色格子包围（包围的定义：**八连通意义下**，以这个白色格子为起点，只能经过白色格子，无法到达整个网格图中所有白色格子）（注：由于条件 1 的存在，加粗处原本为四连通，现在可以改成八连通）。

+ 黑色格子连通。



条件 1 很好处理。条件 3 可以利用 $K$ 很小的性质，暴力维护扫描到当前列，目前这一列 $K$ 个格子的连通状态（状态数 $\operatorname{Bell}(K) < 1000$）。暴搜预处理出所有状态即可。

枚举**当前列**的各个黑色连通状态 $S$，再枚举**下一列**的黑白状态 $T$。令 $f(S,T)$ 表示其后继状态编号，若不合法则记作 $0$。

为了让连通状态 $S$ 更形象化，我们给每个黑点一个编号（白点编号为 $0$），编号相同的黑点在一个连通块中。

以下是计算 $f(S,T)$ 的流程：

1. 判断条件 1。若不合法则为 $0$。
2. 将**当前列**的连通状态继承到**下一列**（可以将连通块编号直接复制过去，前提是**下一列**中对应位置要是黑点）。

> 如果**当前列**的某个连通块在**下一列**中丢失（即这个连通块的所有点在**下一列**中的对应位置均为白点，无法继承），则不合法。
> 
> 如果**下一列**中的某个黑点在**当前列**中的对应位置为白点（没有可以继承的），则新加一个连通块。

3. 把在**下一列**中的两个相邻黑点对应的连通块合并起来。从左到右合并，同时判断条件 2。

> 若在合并位于 $x$ 和 $x+1$ 处的黑点时，发现它们本来就是同一个连通块，则会形成一个包围圈。但是这个包围圈有可能没有包围白点（例：$2 \times 2$ 的全黑矩形）。事实上只需要判**当前列**中 $x$ 处是不是白点即可，这里可以自行思考一下为什么）

直接一列一列 DP 过去即可。注意要求**最后一个有黑点的列**中的所有黑点在同一个连通块中。


```cpp
const int mod = 10007;
inline void addmod(int &x){ if(x >= mod) x -= mod; }

int n,k,cur=0,now[10];
int seq[1005][10], cnt, f[1005][100];
void dfs(int x){
    if(x==k){
        ++cnt;
        for(int i=0;i<k;i++) seq[cnt][i]=now[i];
        return;
    }
    for(int i=0;i<=cur;i++){
        now[x]=i; dfs(x+1);
    }
    cur++; now[x]=cur; dfs(x+1); cur--;
}

int tmp[10], fa[10], czy[10], lcq[10], vis[10];
int find(int x){
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}

int dp[1005][1005];
void procedure(){
    k=read(),n=read();
    dfs(0);

    for(int i=1;i<=cnt;i++){
        for(int j=0;j<(1<<k);j++){
            for(int l=0;l<k;l++) tmp[l]=(j>>l)&1;
            bool flg=0, debug=(i==3&&j==1);
            for(int l=0;l+1<k;l++){
                if(seq[i][l] && tmp[l+1] && !tmp[l] && !seq[i][l+1]) flg=1;
                if(seq[i][l+1] && tmp[l] && !tmp[l+1] && !seq[i][l]) flg=1;
            }
            if(flg) continue; 

            memset(czy,0,sizeof(czy)); memset(vis,0,sizeof(vis));
            memset(lcq,0,sizeof(lcq));

            
            for(int l=0;l<k;l++) 
                if(tmp[l]) czy[l]=seq[i][l], vis[seq[i][l]]=1;
            
            int lzy = 0;
            for(int l=0;l<k;l++){
                lzy = max(lzy, seq[i][l]);
                if(seq[i][l] && !vis[seq[i][l]]) flg=1;
            }
            if(flg) continue;

            for(int l=0;l<k;l++)
                if(tmp[l]) if(!czy[l]) czy[l]=(++lzy);   

            assert(lzy <= k); 

            for(int l=1;l<=lzy;l++) fa[l]=l;

            for(int l=1;l<k;l++){
                if(czy[l] && czy[l-1]){
                    int x=find(czy[l-1]), y=find(czy[l]);
                    if(x==y && !seq[i][l-1]) flg=1;
                    fa[x]=y;
                }
            }
            if(flg) continue;

            for(int l=0;l<k;l++)
                if(czy[l]) lcq[l]=find(czy[l]);
                else lcq[l]=0;
            
            memset(vis,0,sizeof(vis));

            int fjy=0;
            for(int l=0;l<k;l++){
                if(!lcq[l]) continue;

                if(!vis[lcq[l]]) vis[lcq[l]]=(++fjy);
                lcq[l]=vis[lcq[l]];
            }

            for(int t=1;t<=cnt;t++){
                bool flg=1;
                for(int l=0;l<k;l++) flg&=(lcq[l]==seq[t][l]);
                if(flg){
                    f[i][j] = t;
                    break;
                }
            }
        }
    }

    int ans = 0;
    dp[0][1]=1;
    for(int i=0;i<n;i++){
        for(int m=1;m<=cnt;m++)
        for(int j=0;j<(1<<k);j++){
            if(!f[m][j]) continue;
            addmod(dp[i+1][f[m][j]] += dp[i][m]);
        }
        for(int m=1;m<=cnt;m++){
            int mx=0;
            for(int l=0;l<k;l++) mx=max(mx, seq[m][l]);
            if(mx==1) addmod(ans += dp[i+1][m]);
        }
    }
    printf("%d\n", ans);
}
```

---

