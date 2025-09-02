# Bear and Rectangle Strips

## 题目描述

Limak has a grid that consists of $ 2 $ rows and $ n $ columns. The $ j $ -th cell in the $ i $ -th row contains an integer $ t_{i,j} $ which can be positive, negative or zero.

A non-empty rectangle of cells is called nice if and only if the sum of numbers in its cells is equal to $ 0 $ .

Limak wants to choose some nice rectangles and give them to his friends, as gifts. No two chosen rectangles should share a cell. What is the maximum possible number of nice rectangles Limak can choose?

## 说明/提示

In the first sample, there are four nice rectangles:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771E/01e27af3548be65e50eb7b98af0fa04ea831f0c5.png)Limak can't choose all of them because they are not disjoint. He should take three nice rectangles: those denoted as blue frames on the drawings.

In the second sample, it's optimal to choose six nice rectangles, each consisting of one cell with a number $ 0 $ .

In the third sample, the only nice rectangle is the whole grid — the sum of all numbers is $ 0 $ . Clearly, Limak can choose at most one nice rectangle, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
6
70 70 70 70 70 -15
90 -60 -30 30 -30 15
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
0 -1 0 0
0 0 1 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
1000000000 999999999 -1000000000
999999999 -1000000000 -999999998
```

### 输出

```
1
```

# 题解

## 作者：Alex_Wei (赞：9)

> [CF771E Bear and Rectangle Strips](https://www.luogu.com.cn/problem/CF771E)

这题好难啊。

首先，容易借助 `map` 或其它 STL 求出 $na_i, nb_i, nc_i$ 分别表示从第 $i + 1$ 列开始，合法子矩形的右边界的最小值，且该合法子矩形占用第一行 / 第二行 / 第一、二行。

显然有 naive 的 DP：设 $f_{i, j}$ 表示只考虑第一行前 $i$ 列和第二行前 $j$ 列的答案。转移即不选取子矩形转移到 $f_{i + 1, j}, f_{i, j + 1}$，选子矩形转移到 $f_{na_i, j}, f_{i, nb_j}, f_{nc_{\max(i, j)}, nc_{\max(i, j)}}$。这个 DP 显然也是过不去的。

尝试减小状态数到 $\mathcal{O}(n)$。自然的想法是设 $f_i$ 表示原 $f_{i, i}$。

考虑任意选择子矩形的方案，我们总可以每次选择左端点最靠左的矩形，为每个方案钦定其中所有子矩形被考虑到的顺序。

考虑原 $f_{i, j}(i\leq j)$。若 $f_{i, j} > f_{i, i} + 1$，则 $f_{i, j}$ 对应的方案中，一定存在一个子矩形占用了第二行的第 $i + 1$ 列，且其右侧还有一个子矩形。否则与 $f_{i, i}$ 的最大性矛盾。设倒数第二个子矩形覆盖第二行的第 $[p, q]$ 列，接下来我们将说明 $f_{i, j}$ 是不必要的：

- 如果第一行的第 $[i + 1, q]$ 列没有被子矩形覆盖，则可以先转移到 $f_{q, q}$，再转移到 $f_{q, j}$。
- 如果第一行的第 $[i + 1, q]$ 列被子矩形覆盖，则该子矩形的左端点小于第二行最后一个子矩形的左端点，它应该先被枚举到，故 $f_{i, j}$ 不合法。

接下来，根据值域定义域互换的套路，只有使得 $f_{i, j} = f_{i, i} + 1$ 的最小的 $j$ 是重要的。同理，还需记录使得 $f_{j, i} = f_{i, i} + 1$ 的最小的 $j$。分别记它们为 $g_i$ 和 $h_i$。

首先要确定 $f_i$，才能求出 $g_i, h_i$。对每个 $i$ 记录所有转移到 $f_{i, j}(i\leq j)$ 的 $j$ 以及对应值 $v$ 形成的二元组 $(j, v)$ 即可。

这样，总共只需考虑 $\mathcal{O}(n)$ 种状态，而每种状态只有 $\mathcal{O}(1)$ 个后继。因此，DP 部分的时间复杂度为 $\mathcal{O}(n)$。

总时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/771/submission/189835774)，注意 $g, h$ 的定义是反的。

可以做到多次询问 $f_{i, j}$，有空再补。

---

## 作者：LSG_waterlyf (赞：9)

### 一道记搜。

首先观察发现数据只有两行，说明选取的方式有限，即：转移的方式有限，于是联想到$DP$。

首先考虑怎么转移：

$1.$  选取一行，即$1*(y-x+1)$ 的矩形 $:[1,x,y]$ 或者 $[2,x,y]$ 。其中$sum[1][y]-sum[1][x-1]=0,sum[2][y]-sum[2][x-1]=0$

$2.$  选取两行，即$2*(y-x+1)$的矩形 $:$ $[0,x,y]$ 。其中$sum[0][y]-sum[0][x-1]=0$

因为要使$[k,x,y]$ 的和为$0$ ，所以$sum[k][y]-sum[k][x-1]=0 $ ,即$sum[k][y]=sum[k][x-1]$。这个开个$map$ 足以解决。

由于每一行已经考虑的列数对于答案有影响，所以我们设方程$f[i][j]$表示第一行考虑到第$i$个，第二行第$j$个时最多的矩形。

转移方程即$:$ 

$1. f[x][y]=max(dfs(x,p[2][y])+1,dfs(p[1][x],y)+1);$

$2. f[x][y]=max(f[x][y],dfs(p[0][min(x,y)],p[0][min(x,y)])+1);$

其中 $p[k][x]$ 表示选取行的状态为$k$，第$x$列最近的转移点。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300010
#define int long long
int n,a[3][N],s[3][N],p[3][N];
map<int,int> f[N],v[3];
int dfs(int x,int y)
{
	if(x<0||y<0) return -1e9;
	if(x==0&&y==0) return 0;
	if(f[x][y]) return f[x][y];
	f[x][y]=0;
	//f[x][y]=max(dfs(x-1,y),dfs(x,y-1));
	if(p[1][x]>p[2][y]) f[x][y]=max(f[x][y],dfs(p[1][x],y)+1);
	else f[x][y]=max(f[x][y],dfs(x,p[2][y])+1);
	f[x][y]=max(f[x][y],dfs(p[0][min(x,y)],p[0][min(x,y)])+1);
	return f[x][y];
}
signed main()
{
	cin>>n;
	for(int i=1;i<=2;i++)
	  for(int j=1;j<=n;j++) scanf("%lld",&a[i][j]);
	memset(p,-1,sizeof(p));
	for(int i=1;i<=n;i++)
	{
		s[1][i]=s[1][i-1]+a[1][i];
		s[2][i]=s[2][i-1]+a[2][i];
		s[0][i]=s[1][i]+s[2][i];
		if(v[1][s[1][i]]||!s[1][i]) p[1][i]=v[1][s[1][i]];
		if(v[2][s[2][i]]||!s[2][i]) p[2][i]=v[2][s[2][i]];
		if(v[0][s[0][i]]||!s[0][i]) p[0][i]=v[0][s[0][i]];
		p[0][i]=max(p[0][i],p[0][i-1]);
		p[1][i]=max(p[1][i],p[1][i-1]);
		p[2][i]=max(p[2][i],p[2][i-1]);
		v[1][s[1][i]]=i;v[2][s[2][i]]=i;v[0][s[0][i]]=i;
	}
	cout<<dfs(n,n);//puts("nmsl");
	return 0;
}
```


---

## 作者：SnowTrace (赞：3)

首先 $n^2$ 的算法是考虑设 $f_{i,j}$ 表示第一列到第 $i$ 个位置第二列到第 $j$ 个位置时的答案。

从直观感受上来说这样设是非常不优的，我们希望左端点和右端点摆放矩形的顺序可以尽量均匀，从而可以将状态数减少。

我们的主要想法是，对于这样一个问题，你可以去钦定第一列和第二列中选择矩形的顺序。

我们不妨按照左端点从小到大依次选取，同时我们也希望一次只选一个。

我们认为对于一个 $f_{i,j},i<j$，如果这时候第一列我们不在 $[i,j]$ 这个范围内选一个矩形，我们就转移到 $f_{i,i}$，否则 $f_{i,j}$ 的转移就是唯一的（在第一列选一个）。

对于一个 $f_{i,i}$ 也很好考虑，要么在第一列选一个，要么在第二列选一个，要么选一个宽为 $2$ 的矩形。

我们还要钦定宽为 $2$ 的矩形只在 $f_{i,i}$ 处进行转移。

根据钦定，我们可以知道其他的转移要么不优，要么可以由现在的转移顺序从别的地方转移过来。

对于这个东西，考虑记忆化搜索。（或者也可以不写）

随着 $n$ 的增大，状态数只会增加 $O(1)$ 种，而一开始只有 $f_{0,0}$ 一种状态，所以有效的状态数是 $O(n)$ 的。

---

## 作者：__stick (赞：2)

## 题意
给出一个 $2\times n$ 的矩形，问其中最多能选出多少个不相交的子矩形使得每个矩形内部的的和为 $0$。

## 思路

一个非常暴力的思路就是 $F_{i,j}$ 表示第一行选到了 $i$ 列，第二行选到了 $j$ 列的最大值。

这样预处理一下每一行每个位置向前最近能选出一个合法矩形的位置。

然后从那些位置转移即可。

转移有三种：

1. 第一行增加一个矩形
2. 第二行增加一个矩形
3. $i=j$ 的时候增加一个宽度为 $2$ 的矩形


但是这样状态已经爆炸了，考虑优化。


我们定义 $f_{i}$ 表示 $F_{i,i}$。


每次转移找到最近 $j$ 使得 $F_{i,j}=f_{i}+1$ 这样显然对于前两种转移来说不会影响答案，而同时会使得第三种转移尽可能的更大，所以这样需要转移的状态总数就是 $O(n)$ 的。

使用 vector 将转移的状态挂到 $\min(i,j)$ 上即可。

时间复杂度 $O(n)$。

## code



```cpp
const int MAXN=3e5+10;
ll s1[MAXN],s2[MAXN],s3[MAXN];
int n;
int nxt1[MAXN],nxt2[MAXN],nxt3[MAXN];
inline void cal(ll s[],int nxt[])
{
    unordered_map<ll,int>mp;
    for(int i=n;~i;i--)
    {
        if(mp.count(s[i]))nxt[i]=mp[s[i]];
        else nxt[i]=n+1;
        mp[s[i]]=i;
    }
    for(int i=n-1;~i;i--)cmin(nxt[i],nxt[i+1]);
}
int F[MAXN];
vector<tuple<int,int,int> >ve[MAXN];
inline void update(int x,int y,int z){ve[min(x,y)].emplace_back(x,y,z);cmax(F[max(x,y)],z);}
inline void cal(int x,int y,int z)
{
    if(x<n)
    {
        update(x+1,y,z);
        if(nxt1[x]<=n)update(nxt1[x],y,z+1);
    }
    if(y<n)
    {
        update(x,y+1,z);
        if(nxt2[y]<=n)update(x,nxt2[y],z+1);
    }
    if(x==y&&x<n)
    {
        update(x+1,y+1,z);
        if(nxt3[x])update(nxt3[x],nxt3[y],z+1);
    }
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	cin>>n;
    for(int i=1;i<=n;i++)cin>>s1[i],s1[i]+=s1[i-1];
    for(int i=1;i<=n;i++)cin>>s2[i],s2[i]+=s2[i-1];
    for(int i=1;i<=n;i++)s3[i]=s1[i]+s2[i];
    cal(s1,nxt1),cal(s2,nxt2),cal(s3,nxt3);
    for(int i=0;i<=n;i++)
    {
        cal(i,i,F[i]);
        int m1=n+1,m2=n+1;
        for(auto&[x,y,z]:ve[i])if(z==F[i]+1)
        {
            if(x==i)cmin(m2,y);
            else cmin(m1,x);
        }
        if(m1<=n)cal(m1,i,F[i]+1);
        if(m2<=n)cal(i,m2,F[i]+1);
    }
    cout<<F[n];
	return 0;
} 

```





---

## 作者：nullqtr_pwp (赞：1)

显然和为 $0$ 等价于 $l-1,r$ 的前缀和相等，容易求出 $\leq 3n$ 个候选子矩形，因为我们只会选取离他最近的。因此将问题转化为：

>有 $[1,n]$ 的时间区间和两个人 A,B，以及 $m$ 个限制区间。限制形如：
>- I. 占上 A 的 $[l_i,r_i]$；
>- II. 占上 B 的 $[l_i,r_i]$；
>- III. 同时占上 A,B 的 $[l_i,r_i]$。
>
> 目标是最大化选取的限制区间个数，使得 A,B 的每个位置被最多一个限制区间覆盖。


考虑对 III 类区间设计 dp，扫描线时间的过程中，假设当前时间是 $t$，那么 $r\leq t$ 的所有 dp 的更新是确定的，由于 I,II 类区间的权值均为 $1$，因此每次找后继 $r$ 最小的覆盖就是正确的，具体来说每个 III 类区间都会在上下各自对应当前的结尾时间 $c_i,d_i$。在扫描线的过程中，假设区间是左闭右开的，那么我们会将所有当前结尾 $\leq l$ 的进行转移。

由于总的修改次数很多，且很难有什么规律，因此从减少有效转移的角度考虑，观看代码效果更佳。假设考虑 I 类区间，有多个可以转移的，继续利用 I,II 类区间权值为 $1$ 的性质。我们宣称在后续第一行的转移中，只用保留 $f$ 最大的，如果有多个则保留 $d$ 最小的。反证处理，如果一个 $f$ 更小的实现反超，那么需要多选取两个 I,II 类区间才能达到更优。而这在上还是下做这个都是不会更优的。因此在第一行删除这个在后续的转移是不劣的。使用两个 set 各自维护上下的转移，一个大根堆维护当前 $f$ 的最大值以实现插入一个 III 区间 dp 初值的计算。时间复杂度 $\mathcal O(n\log n)$。

根据这个过程，cdq 分治是思维量比较小的做法。没有细想但是可以做。

[提交记录](https://codeforces.com/contest/771/submission/323372142)

---

