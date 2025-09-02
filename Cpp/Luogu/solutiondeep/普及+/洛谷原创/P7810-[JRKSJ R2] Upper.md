# 题目信息

# [JRKSJ R2] Upper

## 题目描述

有 $n$ 张扑克，第 $i$ 张扑克上写有一个正整数 $a_i$。

现在要把扑克划分成若干个合法的连续子段，其中，一个连续子段 $[l,r]$ “合法”当且仅当这个子段同时满足两个条件： 

* $a_l< a_r$
* $\gcd(a_l,a_r)>1$ 

请问最多能划分多少段。如果没有合法的划分方案，输出 $-1$ 即可。

如果您不知道 $\gcd$ 是什么意思，请看“提示”部分。

## 说明/提示

### 数据范围
本题采用捆绑测试。

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le 10^9$。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^9$ | 无 | $5$ |
| $2$ | $3\times10^3$ | $10^9$ | 无 | $15$ |
| $3$ | $2\times10^4$ | $10^6$ | 无 | $20$ |
| $4$ | $2\times 10^4$ | $10^9$ | 无 | $10$ |
| $5$ | $10^5$ | $10^9$ | 数据随机 | $10$ |
| $6$ | $10^5$ | $10^9$ | 无 | $40$ |

### 样例解释
对于样例 $1$，有且仅有一种划分方案 $\{2,1,8\},\{3,9\}$。\
对于样例 $2$，无合法的划分方案。

### 提示
对于两个正整数 $a,b$，$\gcd(a,b)$ 为它们的最大公因数，即满足既是 $a$ 的因数又是 $b$ 的因数的数中最大的数。

## 样例 #1

### 输入

```
5
2 1 8 3 9```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20
20 9 36 36 40 8 3 10 9 20 18 12 30 20 30 15 8 9 27 45```

### 输出

```
7```

# AI分析结果

• 综合分析与结论：这几道题解都围绕如何优化基于动态规划的解法来解决扑克划分问题。难点在于处理\(\gcd(a_l,a_r)>1\)这个限制条件。多数题解通过对每个数进行质因数分解，将问题转化为在有公共质因数的数之间转移，再利用权值线段树优化转移过程。

所选的题解：
  - 作者：KazamaRuri (5星)
    - 关键亮点：思路清晰，详细阐述从暴力DP到优化DP的过程，对质因子分解和权值线段树的运用讲解透彻，代码实现高效且有注释说明。
    - 重点代码核心思想：先通过线性筛预处理质数，对输入数质因数分解，离散化处理数据后，利用权值线段树维护状态转移。
```cpp
// 核心代码片段
void init(int n){
    for(int i=2;i<=n;i++){
        if(!isp[i]) p[++num]=i;
        for(int j=1;j<=num&&p[j]*i<=n;j++){
            isp[i*p[j]]=1; if(i%p[j]==0) break;
        }
    }
}
int main(){ init(31623),n=read();
    for(int i=1,x;i<=n;i++){
        h[++cnt]=x=a[i]=read();
        for(int j=1;j<=num&&p[j]*p[j]<=x;j++)
            if(x%p[j]==0){
                q[i].push_back(p[j]);
                while(x%p[j]==0) x/=p[j];
            }
        if(x<=48000&&x>1) q[i].push_back(x);
    } sort(h+1,h+1+n),cnt=unique(h+1,h+1+n)-h-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(h+1,h+1+cnt,a[i])-h,f[i]=-inf;
    for(int i=1;i<=n;i++)
        for(auto x:q[i]){
            if(rt[x]) f[i]=max(f[i],ask(rt[x],1,n,a[i]-1)+1);
            if(f[i-1]>=0) upd(rt[x],1,n,a[i],f[i-1]);
        }
    return!printf("%d",f[n]>0?f[n]:-1);
}
```
  - 作者：Spasmodic (4星)
    - 关键亮点：同样采用DP结合权值线段树优化，代码实现完整，对每个步骤的优化有清晰说明，如质因子分解的优化等。
    - 重点代码核心思想：线性筛预处理质数，对每个数质因数分解，离散化后利用动态开点权值线段树维护状态转移。
```cpp
// 核心代码片段
void init(int n){
    rep(i,2,n){
        if(!vst[i])p[++cp]=i;
        for(int j=1;j<=cp&&i*p[j]<=n;j++){
            vst[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
}
void dcp(int id){
    int x=a[id];
    for(int i=1;p[i]*p[i]<=x;i++)if(x%p[i]==0){
        pr[id][++cnt[id]]=p[i];
        while(x%p[i]==0)x/=p[i];
    }
    if(x>1)pr[id][++cnt[id]]=x;
}
int main(){
    IO>>n;
    init(1e5);
    rep(i,1,n)IO>>a[i],sa[i]=a[i],dcp(i);
    sort(sa+1,sa+n+1);
    m=unique(sa+1,sa+n+1)-sa-1;
    rep(i,1,n)ua[i]=lower_bound(sa+1,sa+m+1,a[i])-sa;
    memset(f,-1,sizeof f);
    f[0]=0;
    rep(i,1,n){
        rep(j,1,cnt[i]){
            int p=rt[pr[i][j]];
            chkmax(f[i],ask(p,1,m,1,ua[i]-1)+1);
            if(f[i-1]>=0)insert(p,1,m,ua[i],f[i-1]);
            rt[pr[i][j]]=p;
        }
    }
    IO<<f[n]<<endl;
    return 0;
}
```
  - 作者：ZillionX (4星)
    - 关键亮点：对空间复杂度的分析详细，通过离散化和权值线段树优化DP，代码中运用了一些优化技巧如Exact Division，且运行效率高。
    - 重点代码核心思想：先初始化质数，对输入数质因数分解并离散化，利用权值线段树维护状态转移。
```cpp
// 核心代码片段
void Init(int n) {
    vs[1]=1;
    tot=1,p[1]=2,vs[4]=1;
    for (int i=3;i<=n;i++) {
        if (vs[i]==0)
            p[++tot]=i,pv[tot]=inv32(i),
            pm[tot]=ui(-1)/i;
        if (i*2<=n) vs[i*2]=1;
        else continue;
        if (!(i&1)) continue;
        for (int j=2;j<=tot && i*p[j]<=n;j++) {
            vs[i*p[j]]=1;
            if (i*pv[j]<=pm[j]) break;
        }
    }
}
int main() {
    Init(V-1);
    n=rd();
    int idt(tot);
    for (int i=1;i<=n;i++) {
        a[i]=cp[i]=rd();
        int k(0);
        ui x(a[i]);
        if (!(x&1)) {
            k++,dv[i][k]=1,x>>=1;
            while (!(x&1)) x>>=1;
        }
        for (int j=2;j<=tot;j++)
            if (x*pv[j]<=pm[j]) {
                k++,dv[i][k]=j,x*=pv[j];
                while (x*pv[j]<=pm[j]) x*=pv[j];
                if (x==1) break;
            }
        if (x>1) {
            k++;
            if (!mp[x]) mp[x]=++idt;
            dv[i][k]=mp[x];
        }
        dv[i][0]=k;
    }
    sort(cp+1,cp+n+1);
    int sn(unique(cp+1,cp+n+1)-cp-1);
    for (int i=1;i<=n;i++) a[i]=lower_bound(cp+1,cp+sn+1,a[i])-cp;

    for (int i=1;i<=n;i++) f[i]=-1e9;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=dv[i][0];j++) {
            if (T.rt[dv[i][j]])
                f[i]=max(f[i],T.Qry(T.rt[dv[i][j]],1,sn,1,a[i]-1)+1);
            if (f[i-1]>=0) T.Upd(T.rt[dv[i][j]],1,sn,a[i],f[i-1]);
        }

    printf("%d",f[n]<0?-1:f[n]);
    return 0;
}
```

最优关键思路或技巧：通过质因数分解将\(\gcd(a_l,a_r)>1\)的限制转化为公共质因子问题，利用权值线段树优化动态规划的状态转移，有效降低时间复杂度。同时，对质数的预处理、数据离散化处理等技巧也有助于提升算法效率。

可拓展之处：类似题目可能会改变区间划分的条件，如改变\(\gcd\)的计算范围，或者对区间内元素有其他限制。套路通常是先分析朴素的DP解法，再针对限制条件的难点进行优化，如利用数据结构维护状态转移。

推荐题目：
  - P3372 【模板】线段树 1
  - P1880 [NOI1995] 石子合并
  - P2831 [NOIP2016 提高组] 愤怒的小鸟

个人心得：无。 

---
处理用时：87.99秒