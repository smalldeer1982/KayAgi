# PSTRING - Remove The String

## 题目描述

给你两个字符串$X$和$Y$。在$X$中删除最少的字符，使得$Y$不为$X$的子串。

## 样例 #1

### 输入

```
ababaa
aba```

### 输出

```
1```

# 题解

## 作者：wanggk (赞：2)

单串匹配单串，考虑 KMP。

先对 $Y$ 串求出 $nxt$ 数组，并求出 $g_{j,c}$ 表示此时已经匹配了 $Y$ 的前 $j$ 个字符，再添加一个字符 $c$，此时的匹配长度。

设 $f_{i,j}$ 表示 $X$ 串的前 $i$ 位，匹配长度恰好是 $j$ 时，最小的删除个数（使得该前缀不出现 $Y$ 串）。

两种转移：

- 删掉 $X_{i+1}$：$f_{i,j} \rightarrow f_{i+1,j}+1$。
- 添加 $X_{i+1}$ 继续匹配：$f_{i,j} \rightarrow f_{i+1,g_{j,X_{i+1}}}$。

最后的答案是 $\min_{j=0}^{m-1} f_{n,j}$。

时间复杂度 $O(|X| \times |Y|)$。

$f$ 数组第一维可以滚动掉。题面里没写字符集，只考虑小写字母能过。


```cpp
/*
 * @Author: wanggk
 * @Date: 2025-03-27 15:55:22
 */
#include<bits/stdc++.h>
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
using namespace std;
void ckmin(int &x,int y){ x=(y<x?y:x); }

int n,m;
char X[10005],Y[1005];
int nxt[1005],g[1005][27],f[2][1005];

void getnxt(){
    int j=nxt[1]=0;
    For(i,2,m){
        while(j && Y[i]!=Y[j+1]) j=nxt[j];
        if(Y[i]==Y[j+1]) j++;
        nxt[i]=j;
    }
}
void getg(){
    For(c,0,25) g[0][c]=(c==Y[1]-'a');
    For(i,1,m-1)
        For(c,0,25)
            if(c+'a'==Y[i+1]) g[i][c]=i+1;
            else g[i][c]=g[nxt[i]][c];
}
void solve()
{
    n=strlen(X+1),m=strlen(Y+1);
    getnxt();
    getg();
    memset(f[0],0x3f,4*m);
    f[0][0]=0;
    For(i,0,n-1){
        int nw=i&1,nt=(i&1)^1;
        memset(f[nt],0x3f,4*m);
        For(j,0,m-1){
            if(f[nw][j]>i) continue;
            ckmin(f[nt][j],f[nw][j]+1);
            ckmin(f[nt][g[j][X[i+1]-'a']],f[nw][j]);
        }
    }
    int res=0x3f3f3f3f;
    For(j,0,m-1) res=min(res,f[n&1][j]);
    printf("%d\n",res);
}
signed main(){
    while(scanf("%s%s",X+1,Y+1)==2) solve();
    return 0;
}
```

---

