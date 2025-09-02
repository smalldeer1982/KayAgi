# [THUPC 2022 决赛] riapq

## 题目描述

给出排列 $a_1,\dots,a_n$，你需要维护序列 $b_1,\dots,b_n$，初值为0。

共 $m$ 次操作：

修改操作：给出 $l,r$，对每个 $(i,j)$ 满足 $l\le i\le j\le r,\;a_i\le a_j$，将 $b_j$ 增加1；

查询操作：给出 $x$，查 $b_x$。

## 说明/提示

$1\le n,m\le 2\times 10^5$；

$1\le a_i\le n$，$a_i$ 互不相同；

$1\le l\le r\le n$；

$1\le x\le n$。

## 样例 #1

### 输入

```
8 10
5 4 8 7 1 6 3 2
1 2 5
2 8
1 2 8
1 7 8
2 4
2 1
2 6
2 4
1 8 8
2 4
```

### 输出

```
0
4
0
3
4
4
```

# 题解

## 作者：Umbrella_Leaf (赞：11)

做的时候找了半天都没有找到详细的题解，只能自己写一个。

## 题意

> 给出排列 $a_1,a_2,\cdots,a_n$，你需要维护一个初始全 $0$ 的序列 $b$。$m$ 次操作：
> 
> `1 l r`：对于每对 $l\le i\le j\le r$ 且 $a_i\le a_j$，$b_j\gets b_j+1$。
> 
> `2 x`：查询 $b_x$。
> 
> $n,m\le 2\times 10^5$。

## 题解

对序列以 $\sqrt n$ 为块长分块。

对于一次修改的贡献，我们拆成 $5$ 个部分：

1. 左散块对左散块，右散块对右散块，或者 $l,r$ 在同一块；
2. 整块对整块（包括同一个整块内部）；
3. 整块对右散块；
4. 左散块对右散块；
5. 左散块对整块。

其中，“`X` 对 `Y`”表示 $i$ 在 `X` 中、$j$ 在 `Y` 中。

接下来分别考虑。

#### 一、左散块对左散块/右散块对右散块/$l,r$ 在同一块

预处理 $pnum_{i,j,k}$ 表示第 $i$ 块的前 $k$ 个元素中小于等于第 $i$ 块第 $j$ 个元素的有多少个。修改时暴力在答案数组上加。

#### 二、整块对整块

预处理 $num_{i,j}$ 表示第 $i$ 块中小于等于 $a_j$ 的有多少个。

对每个整块，我们记录前面每一块对它有多少次贡献。

修改：对一段区间内的每个块，左边一段区间内的块对它贡献 $+1$。

询问：扫描 $x$ 所在块左边的块，查询它们对 $x$ 所在的块贡献了多少次，乘上『这个块里小于等于 $a_x$ 的数量』后累加到答案。

维护贡献次数的差分数组即可。

注意同一块内部的贡献需要特殊处理。

#### 三、整块对右散块

预处理 $prenum_{i,j}$ 表示前 $i$ 块中小于等于 $a_j$ 的有多少个。

修改时，对于右散块的每个元素暴力更新答案。

#### 四、左散块对右散块

预处理 $id_{i,j}$ 表示第 $i$ 块第 $j$ 小的数在哪个位置。

使用双指针更新答案，具体不好描述，可浏览代码。

### 五、左散块对整块

最复杂的部分。

我们建立一个平面，$x$ 坐标是块编号，$y$ 坐标是 $a$ 值。假设 $pos_i$ 是下标 $i$ 所在的块。

- 修改 $(l,r)$：对于左散块每个点 $i$，在 $(pos_l+1,a_i)$ 上 $+1$，在 $(pos_r,a_i)$ 上 $-1$。

- 查询 $i$：查询 $x$ 坐标 $\le pos_i$，$y$ 坐标 $\le a_i$ 的点权值和。

转化成 $O(n\sqrt n)$ 次单点修改和 $O(n)$ 次二维数点。

先将 $x$ 坐标按照 $\sqrt[4]n$ 为块长分块。对于每个 $x$ 坐标上的整块和单点，我们需要支持：

- 修改：$O(n)$ 次连续在 $O(\sqrt n)$ 个位置单点修改。

- 查询：$O(n\sqrt[4]n)$ 次查询前缀和。

在 $y$ 坐标上继续以 $\sqrt n$ 为块长分块。把前缀和拆成整块和的前缀和和散块块内前缀和。

对于整块，我们维护前若干块内的和。修改时先差分出每个块内的和，然后暴力修改，最后再做前缀和。

而对于每个散块，我们要做的：

- 修改：$O(n\sqrt n)$ 次单点修改。

- 查询：$O(n\sqrt[4]n)$ 次查询前缀和。

貌似没区别？但是序列长度变成了 $O(\sqrt n)$。

所以再套一个以 $O(\sqrt[4]n)$ 为块长的分块，支持 $O(1)$ 单点修改和 $O(\sqrt[4]n)$ 前缀查询即可。

总复杂度 $O(n\sqrt n)$。

## 代码

比较丑陋，见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+(c^'0'),c=getchar();
	return x;
}
#define ll long long
int n,m;
const int B1=460,B2=23;
int a[200005];
int pos[200005],poss[465],L[465],R[465],L1[25],R1[25];
int num[465][200005],prenum[465][200005];
int pnum[465][465][465];
int id[465][465];
int times[465][465];
ll ans[200005];
int xbyb[25][465],xpyb[465][465],xbypyb[25][465][25],xbypyp[25][465][465],xpypyb[465][465][25],xpypyp[465][465][465];
//b 表示 block 块，p 表示 point 单点
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
	n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        pos[i]=(i-1)/B1+1;
        if(!L[pos[i]])L[pos[i]]=i;
        R[pos[i]]=i;
    }
    for(int i=1;i<=B1;i++){
        poss[i]=(i-1)/B2+1;
        if(!L1[poss[i]])L1[poss[i]]=i;
        R1[poss[i]]=i;
    }
    for(int i=1;i<=pos[n];i++){//预处理
        for(int j=L[i];j<=R[i];j++)num[i][a[j]]++;
        for(int j=1;j<=n;j++)num[i][j]+=num[i][j-1],prenum[i][j]=num[i][j]+prenum[i-1][j];
        for(int j=L[i];j<=R[i];j++)id[i][j-L[i]+1]=j;
        sort(id[i]+1,id[i]+R[i]-L[i]+1+1,cmp);
        for(int j=1;j<=R[i]-L[i]+1;j++)
            for(int k=1;k<=R[i]-L[i]+1;k++)pnum[i][j][k]=pnum[i][j][k-1]+(a[k+L[i]-1]<=a[j+L[i]-1]);
    }
    while(m--){
        int opt=read();
        if(opt==1){
            int l=read(),r=read();
            if(pos[l]==pos[r]){
                // l,r 在同一个块
                for(int i=l;i<=r;i++)ans[i]+=pnum[pos[l]][i-L[pos[l]]+1][i-L[pos[l]]+1]-pnum[pos[l]][i-L[pos[l]]+1][l-L[pos[l]]];
            }else{
                // 第一部分 左散块对左散块/右散块对右散块
                for(int i=l;i<=R[pos[l]];i++)ans[i]+=pnum[pos[l]][i-L[pos[l]]+1][i-L[pos[l]]+1]-pnum[pos[l]][i-L[pos[l]]+1][l-L[pos[l]]];
                for(int i=L[pos[r]];i<=r;i++)ans[i]+=pnum[pos[r]][i-L[pos[r]]+1][i-L[pos[r]]+1];
                // 第二部分 整块对整块
                for(int i=pos[l]+1;i<pos[r];i++)times[pos[l]+1][i]++;
                // 第三部分 整块对右散块
                for(int i=L[pos[r]];i<=r;i++)ans[i]+=prenum[pos[r]-1][a[i]]-prenum[pos[l]][a[i]];
                // 第四部分 左散块对右散块
                for(int i=1,j=0,cnt=0;i<=R[pos[r]]-L[pos[r]]+1;i++){
                    while(i<=R[pos[r]]-L[pos[r]]+1&&id[pos[r]][i]>r)i++;
                    if(i>R[pos[r]]-L[pos[r]]+1)continue;
                    while(j<R[pos[l]]-L[pos[l]]+1&&a[id[pos[l]][j+1]]<=a[id[pos[r]][i]]){
                        j++;
                        if(id[pos[l]][j]>=l)cnt++;
                    }
                    ans[id[pos[r]][i]]+=cnt;
                }
                // 第五部分 左散块对整块
                int x=pos[l]+1;
                // y 整块的部分，差分->暴力修改->前缀和
                for(int i=pos[n];i>=1;i--)xbyb[poss[x]][i]-=xbyb[poss[x]][i-1],xpyb[x][i]-=xpyb[x][i-1];
                for(int i=l;i<=R[pos[l]];i++)xbyb[poss[x]][pos[a[i]]]++,xpyb[x][pos[a[i]]]++;
                for(int i=1;i<=pos[n];i++)xbyb[poss[x]][i]+=xbyb[poss[x]][i-1],xpyb[x][i]+=xpyb[x][i-1];
                // y 散块的部分，块内再分块
                for(int i=l;i<=R[pos[l]];i++){
                    int y=a[i];
                    // x 整块
                    xbypyb[poss[x]][pos[y]][poss[y-L[pos[y]]+1]]++,xbypyp[poss[x]][pos[y]][y-L[pos[y]]+1]++;
                    // x 散块
                    xpypyb[x][pos[y]][poss[y-L[pos[y]]+1]]++,xpypyp[x][pos[y]][y-L[pos[y]]+1]++;
                }
                // 和上面一样
                x=pos[r];
                for(int i=pos[n];i>=1;i--)xbyb[poss[x]][i]-=xbyb[poss[x]][i-1],xpyb[x][i]-=xpyb[x][i-1];
                for(int i=l;i<=R[pos[l]];i++)xbyb[poss[x]][pos[a[i]]]--,xpyb[x][pos[a[i]]]--;
                for(int i=1;i<=pos[n];i++)xbyb[poss[x]][i]+=xbyb[poss[x]][i-1],xpyb[x][i]+=xpyb[x][i-1];
                for(int i=l;i<=R[pos[l]];i++){
                    int y=a[i];
                    xbypyb[poss[x]][pos[y]][poss[y-L[pos[y]]+1]]--,xbypyp[poss[x]][pos[y]][y-L[pos[y]]+1]--;
                    xpypyb[x][pos[y]][poss[y-L[pos[y]]+1]]--,xpypyp[x][pos[y]][y-L[pos[y]]+1]--;
                }
            }
        }else{
            int x=read(),y=a[x];
            ll res=ans[x];// 第一、三、四部分 暴力记录答案
            // 第二部分 整块对整块
            for(int i=1,s=0;i<=pos[x];i++){
                s+=times[i][pos[x]];
                if(i<pos[x])res+=1ll*s*num[i][a[x]];
                else for(int j=L[i];j<=x;j++)if(a[j]<=a[x])res+=s;
            }
            // 第五部分 左散块对整块
            // x 整块
            for(int i=1;i<poss[pos[x]];i++){
                // y 整块
                res+=xbyb[i][pos[y]-1];
                // y 散块内整块
                for(int j=1;j<poss[y-L[pos[y]]+1];j++)res+=xbypyb[i][pos[y]][j];
                // y 散块内单点
                for(int j=L1[poss[y-L[pos[y]]+1]];j<=y-L[pos[y]]+1;j++)res+=xbypyp[i][pos[y]][j];
            }
            // x 散块（和上面一样）
            for(int i=L1[poss[pos[x]]];i<=pos[x];i++){
                res+=xpyb[i][pos[y]-1];
                for(int j=1;j<poss[y-L[pos[y]]+1];j++)res+=xpypyb[i][pos[y]][j];
                for(int j=L1[poss[y-L[pos[y]]+1]];j<=y-L[pos[y]]+1;j++)res+=xpypyp[i][pos[y]][j];
			}
            printf("%lld\n",res);
        }
    }
    return 0;
}
```

---

## 作者：enucai (赞：1)

## Preface

复杂度 $O(n\sqrt n\log n)$ 的解法，但是最优解，因为 $\log n$ 是 cdq 分治的。

## Analysis

首先考虑将修改的贡献差分。即考虑一次修改中的一个位置 $i$，$b_i$ 会加上 $[l,i]$ 中 $a_j\le a_i$ 的 $j$ 的个数，差分成 $[1,i]$ 的个数减去 $[1,l-1]$ 的个数。差分的好处在于把贡献区间和询问区间拆成了两个不交的区间，便于处理贡献。

首先对序列按照块长为 $\sqrt n$ 进行分块。

考虑预处理出 $v_{i,j}$ 表示前 $i$ 个块中 $\le a_j$ 的数的个数，这个预处理是容易的，直接计算前缀和，或者用 $O(\sqrt n)$ 单点加，$O(1)$ 区间求和的值域分块即可。复杂度 $O(n\sqrt n)$。

先考虑 $[1,i]$ 的贡献，可以用树状数组预处理出对于每个 $i$ 的答案，复杂度 $O(n\log n)$。每次操作时直接在对应的整块和散块对应位置上打标记即可，单次操作复杂度 $O(\sqrt n)$。

再考虑 $[1,l-1]$ 的贡献。范围内的整块贡献可以直接给块打标记计算（记录 $\sqrt n$ 个块前缀对每个块的贡献，和对每个散块位置的贡献），单次操作复杂度 $O(\sqrt n)$。但是剩下的右边一些散块无法难以打标记，于是考虑把所有这样的散块操作离线下来，这样的操作只会有 $O(m\sqrt n)$ 个。

那么每次询问可以 $O(\sqrt n)$ 算出整块对他的贡献。但是还要算散块对他的贡献，这样的查询有 $O(m)$ 个。

考虑散块操作和散块贡献查询的实质是什么。如果我们把第 $i$ 个数抽象成二维平面上的点 $(i,a_i)$，那么一次操作 $i$ 对区间 $[l,r]$ 的贡献就是平面上以 $(l,a_i)$ 为左下角，$(r,+\infty)$ 为右上角的矩形做区间 $+1$ 操作，而一次查询则是一个单点求值。

考虑将操作差分，变成单点加，矩形求值，即每次操作将 $(l,a_i)$ 做 $+1$，将 $(r+1,a_i)$ 做 $-1$，然后一次查询就是查一个左下角的矩形和。

这个问题可以 cdq 分治解决，实质是一个三维数点（两维是坐标，一位是时间戳）。考虑按照横坐标分治，每一层分治考虑按时间顺序枚举操作，问题就变成了序列上的单点加，区间求和。由于对于整个分治过程的 $\log n$ 层，单点加有共 $O(m\sqrt n\log n)$ 个，区间求和只有 $O(m\log n)$ 个，于是用 $O(1)$ 单点加，$O(\sqrt n)$ 的区间求和的值域分块即可解决。

设 $n,m$ 同阶，复杂度 $O(n\sqrt n\log n)$，$\log n$ 常数很小，所以跑得很快。

## Code

[Submission](https://www.luogu.com.cn/record/98718087)。听说 Ynoi 最近流行不放代码，所以不放了，要代码私信（~~感觉代码比我在这里瞎逼逼清楚~~）。

---

