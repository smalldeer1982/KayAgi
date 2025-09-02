# [GCJ 2020 Qualification] Indicium

## 题目描述

Indicium 在拉丁语中意为"迹"。本题中我们将研究拉丁方阵及其矩阵迹。

一个拉丁方阵是指 $\mathbf{N} \times \mathbf{N}$ 的方阵，其中每个单元格包含 $\mathbf{N}$ 个不同值之一，且每行每列都不重复出现相同值。在本题中，我们仅处理"自然拉丁方阵"，即这些 $\mathbf{N}$ 个值为 1 到 $\mathbf{N}$ 的整数。

方阵的迹是指主对角线（从左上到右下）上所有值的和。

给定 $\mathbf{N}$ 和 $\mathbf{K}$，构造任意一个迹为 $\mathbf{K}$ 的 $\mathbf{N} \times \mathbf{N}$ 自然拉丁方阵，或判定其不存在。例如，以下是 $\mathbf{N}=3, \mathbf{K}=6$ 时的两种可能解（贡献迹的值已加下划线）：

$\begin{array}{lll}
\underline{2} & 1 & 3 \\ 
3 & \underline{2} & 1 \\ 
1 & 3 & \underline{2}
\end{array}
\quad
\begin{array}{ll}
\underline{3} & 1 \\ 
2 & \underline{3} \\ 
1 & 2
\end{array}$

## 说明/提示

**样例解释**

样例 #1 对应题目描述中的情况。

样例 #2 无解。所有可能的 2×2 自然拉丁方阵如下：

```
1 2 2 1
2 1 1 2
```

它们的迹分别为 2 和 4，无法得到迹 3。

**数据范围**

- $\mathrm{N} \leqslant \mathrm{K} \leqslant \mathrm{N}^{2}$

**测试集 1（7 分，可见判果）**

- $\mathrm{T}=44$
- $2 \leqslant \mathrm{N} \leqslant 5$

**测试集 2（25 分，隐藏判果）**

- $1 \leqslant \mathrm{T} \leqslant 100$
- $2 \leqslant \mathrm{N} \leqslant 50$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
3 6
2 3```

### 输出

```
Case #1: POSSIBLE
2 1 3
3 2 1
1 3 2
Case #2: IMPOSSIBLE```

# 题解

## 作者：Jorisy (赞：0)

考虑一个矩阵主对角线会是什么样的排布。

首先，一个显然的事情是，不存在合法的方案，使得其主对角线是 $x,x,\cdots,x,x,y$，不然最后一行一列的 $x$ 就没地方放了。

那考虑 $x,x,\cdots,x,y,z$ 的情况。

一个比较简单的结论是：

> 对于任意正整数 $k\in[n,n^2]$，都存在 $x,y,z\in[1,n]$，满足 $(n-2)x+y+z=k$。

证明考虑归纳。$k=n$ 显然成立。对于 $k>n$，假设之前有一组 $x,y,z$，那么如果 $y+z<2n$，那么就可以对 $y,z$ 中较小的那个 $+1$。若 $y+z=2n$，那么就可以让 $x\gets x+1$，这样 $y,z$ 总体就要去掉 $n-2$，又回到上一种情况，再对较小的 $+1$ 即可。

按照以上方式，再进行一些微调，我们可以得到一组 $x,y,z$。

然后我们考虑如何在这个主对角线的基础上构造。

首先被 $y,z$ 占用的行列，剩余的两个 $x$ 是可以确定的。

$$
\begin{bmatrix}
x&&&\\
&x&&\\
&&\ddots&&\\
&&&x&&\\
&&&&y&x\\
&&&&x&z
\end{bmatrix}
$$

由于 $x,y,z$ 是较为特殊的，所以我们钦定第一行为 $x,y,z,1,2,\cdots,n$（即在 $1,2,\cdots n$ 的基础上，将 $x,y,z$ 提到前面来）。

假如没有最后两行列，我们可以直接每行在上一行的基础上循环移位填入。

那现在这两行列较为特殊，我们其实也可以类似地填入。

下面以 $n=7,x=1,y=2,z=3$ 为例。

初始是这样：

$$
\begin{bmatrix}
1&&&&&&\\
&1&&&&&\\
&&1&&&&\\
&&&1&&&\\
&&&&1&&\\
&&&&&2&1\\
&&&&&1&3
\end{bmatrix}
$$

接下来我们填入 $2$。按照原本的循环移位的思路，我们试着填在 $1$ 的后面一个。

$$
\begin{bmatrix}
1&2&&&&\\
&1&2&&&\\
&&1&2&&\\
&&&1&2&\\
&&&&1&\red2&\\
&&&&&\red2&1\\
&&&&&1&3
\end{bmatrix}
$$

发现填到这里的时候爆了，我们跳过这一位。

$$
\begin{bmatrix}
1&2&&&&\\
&1&2&&&&\\
&&1&2&&&\\
&&&1&2&&\\
&&&&1&&2\\
&&&&&2&1\\
2&&&&&1&3
\end{bmatrix}
$$

接下来填 $3$。

$$
\begin{bmatrix}
1&2&3&&&\\
&1&2&3&&\\
&&1&2&3&\\
&&&1&2&3\\
&&&&1&&\red2\\
&&&&&2&1\\
2&&&&&1&\red3
\end{bmatrix}
$$

发现位置冲突了，并且 $3$ 已经出现过，那么 $3$ 自动向后一个填入。

$$
\begin{bmatrix}
1&2&3&&&\\
&1&2&3&&\\
&&1&2&3&\\
&&&1&2&3\\
3&&&&1&&2\\
&3&&&&2&1\\
2&&&&&1&3
\end{bmatrix}
$$

接下来填 $4$。

$$
\begin{bmatrix}
1&2&3&4&&\\
&1&2&3&4&\\
&&1&2&3&4\\
&&&1&2&3&4\\
\red3&&&&1&&2\\
&3&&&&2&1\\
2&&&&&1&3
\end{bmatrix}
$$

发现只是单纯的冲突了，**我们这次跳过，但下面需要找机会补回来**。

$$
\begin{bmatrix}
1&2&3&4&&\\
&1&2&3&4&\\
&&1&2&3&4\\
&&&1&2&3&4\\
3&4&&&1&&2\\
&3&&&&2&1\\
2&&&&&1&3
\end{bmatrix}
$$

发现这一行对应我们没有填的列是可以填的，立刻补回来。后面正常填。

$$
\begin{bmatrix}
1&2&3&4&&\\
&1&2&3&4&\\
&&1&2&3&4\\
&&&1&2&3&4\\
3&4&&&1&&2\\
4&3&&&&2&1\\
2&&4&&&1&3
\end{bmatrix}
$$

填 $5$ 的时候，遇到冲突和解决冲突的过程是一样的。

若有之前冲突的没填的列，在这一行可以填，那就填；若当前列冲突，则向后一列再填，并压入一个栈，栈内都是跳过未填的列。

$$
\begin{bmatrix}
1&2&3&4&5&\\
&1&2&3&4&5\\
&&1&2&3&4&5\\
5&&&1&2&3&4\\
3&4&5&&1&&2\\
4&3&&5&&2&1\\
2&5&4&&&1&3
\end{bmatrix}
$$

$6$ 和 $7$ 用相同的方式可以填完。

$$
\begin{bmatrix}
1&2&3&4&5&6&7\\
7&1&2&3&4&5&6\\
6&7&1&2&3&4&5\\
5&6&7&1&2&3&4\\
3&4&5&6&1&7&2\\
4&3&6&5&7&2&1\\
2&5&4&7&6&1&3
\end{bmatrix}
$$

至于这样为什么一定能得到合法方案，我暂时还不会证明，但是它确实过了。如果你会的话可以评论区提出或私信我，我会给你磕头的。

此外注意一些无解的 corner cases。

尽管 $n\le 50$，时间复杂度却是 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define N 55
#define ll long long
#define mod 
using namespace std;

int n,m,ans[N][N],a[N];
bool fl[N][N];

void sol()
{
    static int cas=0;
    cin>>n>>m;
    cout<<"Case #"<<++cas<<": ";
    if(m<n||m==n+1||m==n*n-1||n==3&&m==5||n==3&&m==7)
    {
        cout<<"IMPOSSIBLE\n";
        return;
    }
    int p=1,q=1,r=1;
    m-=n;
    while(m--)
    {
        if(q+r==n*2)
        {
            p++;
            q-=n-2;
        }
        if(++q>r) swap(q,r);
    }
    if(p==r) swap(q,r);
    if(p==q&&q!=r)
    {
        if(r==n) p++,r-=n-2;
        q--,r++;
    }
    // cerr<<p<<','<<q<<','<<r<<'\n';
    iota(a+1,a+n+1,1);
    sort(a+1,a+n+1,[&](int x,int y){return x==p?1:y==p?0:x==q?1:y==q?0:x==r?1:y==r?0:x<y;});
    memset(fl,0,sizeof(fl));
    memset(ans,0,sizeof(ans));
    ans[n-1][n-1]=q;
    ans[n][n]=r;
    fl[n-1][q]=fl[n][r]=1;
    for(int id=1;id<=n;id++)
    {
        int x=a[id];
        stack<int>st;
        for(int i=1,j=id;i<=n;i++)
        {
            if(ans[i][i]==x) continue;
            if(!st.empty()&&!ans[i][st.top()])
            {
                ans[i][st.top()]=x;
                fl[st.top()][x]=1;
                st.pop();
                continue;
            }
            while(ans[i][j]||fl[j][x])
            {
                // cerr<<i<<','<<j<<' ';
                if(!fl[j][x]) st.push(j);
                j=j%n+1;
            }
            ans[i][j]=x;
            fl[j][x]=1;
        }
    }
    cout<<"POSSIBLE\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<ans[i][j]<<' ';
        }
        cout<<'\n';
    }
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) sol();
    return 0;
}
```

---

