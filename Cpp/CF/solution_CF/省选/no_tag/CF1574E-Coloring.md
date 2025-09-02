# Coloring

## 题目描述

A matrix of size $ n \times m $ , such that each cell of it contains either $ 0 $ or $ 1 $ , is considered beautiful if the sum in every contiguous submatrix of size $ 2 \times 2 $ is exactly $ 2 $ , i. e. every "square" of size $ 2 \times 2 $ contains exactly two $ 1 $ 's and exactly two $ 0 $ 's.

You are given a matrix of size $ n \times m $ . Initially each cell of this matrix is empty. Let's denote the cell on the intersection of the $ x $ -th row and the $ y $ -th column as $ (x, y) $ . You have to process the queries of three types:

- $ x $ $ y $ $ -1 $ — clear the cell $ (x, y) $ , if there was a number in it;
- $ x $ $ y $ $ 0 $ — write the number $ 0 $ in the cell $ (x, y) $ , overwriting the number that was there previously (if any);
- $ x $ $ y $ $ 1 $ — write the number $ 1 $ in the cell $ (x, y) $ , overwriting the number that was there previously (if any).

After each query, print the number of ways to fill the empty cells of the matrix so that the resulting matrix is beautiful. Since the answers can be large, print them modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 2 7
1 1 1
1 2 1
2 1 1
1 1 0
1 2 -1
2 1 -1
1 1 -1```

### 输出

```
3
1
0
1
2
3
6```

# 题解

## 作者：dottle (赞：15)

对于一种合法的染色方案，它要么是相邻列之间异色，要么是相邻行之间异色，二者至少满足其一。因此，我们考虑对方阵的染色方案计数相当于就是对第一列/行的染色方案计数。

我们先考虑相邻行异色，对于相邻列异色的情况是相似的。

那么对于每一个格子，它将限制第一行它所在列只能填特定颜色（若此格在奇数行，第一行与它同色；反之异色），这就将第一行的格子分为了三种：无限制，有颜色限制和矛盾。有限制的列我们可以不管，我们记录 $cnt$ 代表有多少个无限制的列，$lim$ 代表有多少个矛盾的列。若 $lim\ne0$，则答案为 $0$，否则为 $2^{cnt}$。我们再维护 $C_{0/1,i}$ 代表第 $i$ 列有多少格子限制为白/黑。若黑白都未被限制则是无限制列，都被限制则是矛盾列。在修改一个点颜色的时候维护这些信息即可。

对于相邻列异色我们也这样算。

最后，将所有格子染成黑白相间的两种方案既是相邻行异色，也是相邻列异色，会重复计算，减去即可。这个信息的维护方式与上面几乎一致，就不再赘述了。


---

## 作者：max67 (赞：3)

## 前言

~~果然我还是太菜了做不了构造题。~~

## 正文

### 无修改操作

首先模拟 $2\times 2$ 的情况。

[![qCODKA.png](https://s1.ax1x.com/2022/03/17/qCODKA.png)](https://imgtu.com/i/qCODKA)

经过我多年来的经验（但这种套路的题我并没有做到过），我们能发现一个性质—— $1$ 个合法的 $2\times 2$ 矩形一定满足：（所有的相邻两行相反/所有的相邻两列相反）至少其中一种。

然后我们发现这个规律推广到 $n\times m$ 的矩阵时同样适用，理由如下：

* 首先，满足上述条件的矩阵构造合法一定合法。以行为例，设任意一个 $2\times 2$ 的矩形的第一行的值的和为 $x$，则第二行的值的和为 $2\ xor \ x$。列同理。

* 其次，对于任意一个合法的矩形，他一定满足上述条件。
 
 >  引理：对于一个合法方案的任意相邻的两行，若他不满足所有的相邻两行相反的性质，那么他一定满足所有的相邻两列相反。证明如下:
 
 > > 因为不满足所有的相邻两行相反的性质，则一定有这一行上相同列（设为列 $x$）的两个数，满足他们两个相等。
 
 [![qCvQgg.png](https://s1.ax1x.com/2022/03/17/qCvQgg.png)](https://imgtu.com/i/qCvQgg)
 
 > > 逐个考虑与他相邻的列（设为列 $y$），参照上面 $2\times 2$ 的表格，你会发现这列 $y$ 也满足相邻两个数相等，且与列 $x$ 相反。
 
 > > 这样逐个逐个考虑下去，那么就会变成下面如图这种情况：
 
 [![qCvxMQ.png](https://s1.ax1x.com/2022/03/17/qCvxMQ.png)](https://imgtu.com/i/qCvxMQ)
 
 > > 那么据图可知（主要说起来不方便，但挺水的），对于这两行，任意相邻的两列都相反。
 
 > > 再考虑接下来的一行。因为对于一行中的数，如满足相邻两列相反，那么相邻两个数的和为 $1$。那么对于他的下一行的同样位置的两个数，不可能相等。即下一行也满足相邻两列相反的条件。
 
 > > 这样无限递归下去，整个矩形都满足了相邻两列相反的条件，得证。
 
 > >（pass：不保证所有行都满足相邻两行相等。即不满足所有的相邻两行相反）
 
 > 根据逻辑推理发现，要么合法的矩形满足相邻两行相等，要么满足相邻两列相等，即合法的矩形一定满足两个条件之一。
 
然后考虑特殊情况，同时满足所有的相邻两行相反和所有的相邻两列相反的条件，可以发现若确定了 $(1,1)$ 的值，则其他值都确定了——最多只有两种取法。

除此以外，这两个条件没有相交。那么答案即为：满足所有相邻两行相反的矩阵数量 $+$ 满足所有相邻两列相反的矩阵数量 $-$ 满足两个条件的数量。

以相邻两行相反的矩阵数量为例。易知，若我们知道第一行的每个数则可以推出矩阵的所有数。然后第一行的相邻两个数并没有限制条件，则值为 $2^m$ （$m$ 为列的数量）

### 有修改操作。

考虑这个修改操作对两个条件分别的贡献和总共的贡献。我们以所有的相邻两行相反的条件为例。

若知道了 $(x,y)$ 的值，因为所有的相邻两行相反，我们可以推出 $(1,y)$ 的值——这里要注意判断冲突，即推出来的 $(1,y)$ 值不同。

然后这一行就算固定了（即贡献为 $1$），因为并不影响其他列，所以我们可以轻松的以 $O(1)$ 的代价维护。

然后根据 $(1,y)$ 的值还可以判断两个条件都满足的数量有几个。

具体实现细节康代码吧（懒得说）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1e3,mod=998244353;
int n,m;
int s1,t1,s2,t2;
//s1 表示 (1,y) 中已经固定的数量，t1 表示 (1,y) 中冲突的数量。
int p2[N];
// p2[i] = 2^i
int a[N][2],b[N][2],c[2];
// a[i][j] 表示第 i 列可以推出值为 j 的数量有几个。b 同理
// c[i] 表示满足两个条件，(1,1) 的值为 i 时冲突的数量。
map<int,int>mp[N];
// mp[i][j] 记录 (i,j) 是否有值。
void calc(int x,int y,int z)
//z=-1 表示删除，z=1 表示加入
{
    if(a[y][0])c[y&1]+=z;
    if(a[y][1])c[(y&1)^1]+=z;
    //因为 (1,y) 和 (x,1) 的贡献相同——他们都能推出 (x,y)，即他们在矩阵满足 (1,1) 的值相同。
    //所以只用算一个的贡献
    if(a[y][0]&&a[y][1])t1+=z;
    //冲突
    if(!a[y][0]&&!a[y][1])s1+=z;
    //自由
    if(b[x][0]&&b[x][1])t2+=z;
    if(!b[x][0]&&!b[x][1])s2+=z;
}
void del(int x,int y,int z)
{
    a[y][(x&1)^z]--;
    b[x][(y&1)^z]--;
    mp[x][y]=0;
}
void insert(int x,int y,int z)
{
    a[y][(x&1)^z]++;
    b[x][(y&1)^z]++;
    mp[x][y]=z+1;
}
int main()
{
    p2[0]=1;
    for(int i=1;i<N;i++)p2[i]=(1ll*p2[i-1]<<1ll)%mod;
    int _;
    scanf("%d%d%d",&n,&m,&_);
    s1=m;s2=n;
    while(_--)
    {
        int x,y,z,ans;
        scanf("%d%d%d",&x,&y,&z);
        calc(x,y,-1);
        if(mp[x][y])del(x,y,mp[x][y]-1);
        if(z!=-1)insert(x,y,z);
        calc(x,y,1);
        ans=(p2[s1]*(t1==0)+p2[s2]*(t2==0))%mod;
        ans=(ans-!c[0]-!c[1]+mod)%mod;
        printf("%d\n",ans);
    }
    return 0;
}
```

## 后记

I don't know~,I have no idea~.

---

## 作者：Purslane (赞：2)

# Solution

2021 年 9 月 20 日，我在一场 CF 的 div.2 中获得了一题的好成绩。

![](https://s21.ax1x.com/2024/07/10/pkhZyVK.png)

三年后，OI 生涯也即将到达终点，就速通当时的 E 来纪念一下吧。

-----

如果一个序列是 $01$ 交错的，我们称他是好的。

则我们断言：一种合法的填充方案，必定行都是好的，或者列都是好的。

假设我们知道了第一列的数，$a_1+a_2$、$a_2+a_3$、$\dots$、$a_{n-1}+a_n$ 的和，那么只要不全为 $1$，整列就确定了。

如果全为 $1$，这一列有两种可能，并且都是好的；这时候第二列相邻两数的和也都是 $1$，也是好的，以此类推。

否则，整个棋盘都唯一了。而这时候让每个数都恰好是它右边的数异或 $1$ 是一种合法的方案，那这种方案就是唯一且确定的。这时候发现所有行都是好的。

因此我们只需要判定每一行和列是否能变成好的，如果可以能否两种都变（其实就是空的啦）。注意可能所有行和所有列都是好的，因此还要判断是否为“棋盘”。

这些都可以 $O(1)$ 快速维护。而必然少不掉 `map`，因此要 $O(k \log k)$ 解决。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int n,m,k,pw[MAXN];
int al,tcnt[2],cnth[MAXN],cntl[MAXN],sumh[MAXN][2],suml[MAXN][2];
map<pair<int,int>,int> mp;
int mulh[3],mull[3];
void calc_h(int i,int op) {
	int cnt=(cnth[i]==sumh[i][0])+(cnth[i]==sumh[i][1]);
	mulh[cnt]+=op;
	return ;	
}
void calc_l(int j,int op) {
	int cnt=(cntl[j]==suml[j][0])+(cntl[j]==suml[j][1]);
	mull[cnt]+=op;
	return ;	
}
void recalc(int i,int j,int col,int op) {
	al+=op,tcnt[(i^j^col)&1]+=op;
	cnth[i]+=op,cntl[j]+=op,sumh[i][(col^j)&1]+=op,suml[j][(col^i)&1]+=op;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	pw[0]=1; ffor(i,1,1000000) pw[i]=pw[i-1]*2%MOD;
	mulh[2]=n,mull[2]=m;
	ffor(i,1,k) {
		int x,y,ncol;
		cin>>x>>y>>ncol;
		int lstcol=-1;
		if(mp.count({x,y})) lstcol=mp[{x,y}];
		calc_h(x,-1),calc_l(y,-1);
		if(lstcol!=-1) recalc(x,y,lstcol,-1),mp.erase({x,y});
		if(ncol!=-1) recalc(x,y,ncol,1),mp[{x,y}]=ncol;
		calc_h(x,1),calc_l(y,1);
		int ans=((!(mulh[0]))*pw[mulh[2]]+(!(mull[0]))*pw[mull[2]])%MOD;
		ans-=(al==tcnt[0])+(al==tcnt[1]);
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：stOqwqOrz (赞：0)

[LG CF1574E](https://www.luogu.com.cn/problem/CF1574E)

[CF1574E](https://codeforces.com/problemset/problem/1574/E)

**简要题意**

- 初始给定一个 $n\times  m$ 的空矩阵，有 $k$ 次操作，每次给定 $x,y,op=-1/0/1$，表示将位置 $(x,y)$ 变成空$/0/1$，每次修改后询问此时给剩余的空矩阵填数后满足任意 $2\times 2$ 的矩阵刚好有两个 $1$ 和两个 $0$ 的填数方案，对 `998244353` 取模。

- $n,m\leq 10^6$，$k\leq 3\times 10^5$，$2s$，$250\operatorname{MB}$

**题解**

- 首先可以发现一个满足条件的 $2\times 2$ 的矩阵要么满足行相反，要么满足列相反，扩展到 $n\times m$ 的矩阵上，可以发现满足条件的矩阵要么所有行相反要么所有列相反，要么所有格子黑白相间，也就是行列都相反。

- 以列为例，假设确定了第一行，那么剩下的所有格子就都确定了。对应的，如果确定了一个格子，那么这一列的头就确定了，考虑记录每一列的头将会被变成 $0/1$ 的格子数，那么就可以算出对于每一列属于哪种类型。

- 每一列有三种类型：矛盾/有限制/无限制，假设无限制有 $cnt$ 列，那么对于列相反的方案数就是 $2^{cnt}$，但是前提是没有矛盾列。

- 所以我们还需要记录矛盾列的个数和限制列的个数，这些都可以在修改的同时进行记录。

- 对于行相反的情况是一样的，对于黑白相间的情况可能会被行相反和列相反算重复，最后减去重复的方案数就可以了。

- 时间复杂度为 $O(k)$，空间复杂度为 $O(k+n)$

**参考代码**

```cpp

const int N=1e6+10;
int n,m,k;
int mdl,cntl,mdr,cntr;
int c[N][2],r[N][2];
int d[2];
unordered_map<int,int> mp[N];
inline void del(int x,int y) {
    if(mp[x][y]) {
        int val=mp[x][y]-1;
        if(c[y][0] && c[y][1]) --mdl;
        if(c[y][0] || c[y][1]) --cntl;
        --c[y][!(val^(x&1))];
        if(c[y][0] && c[y][1]) ++mdl;
        if(c[y][0] || c[y][1]) ++cntl;

        if(r[x][0] && r[x][1]) --mdr;
        if(r[x][0] || r[x][1]) --cntr;
        --r[x][!(val^(y&1))];
        if(r[x][0] && r[x][1]) ++mdr;
        if(r[x][0] || r[x][1]) ++cntr;

        --d[((x+y)&1)^val];     
        mp[x][y]=0;
    }
}
inline void add(int x,int y,int val) {
    mp[x][y]=val+1;
    if(c[y][0] && c[y][1]) --mdl;
    if(c[y][0] || c[y][1]) --cntl;
    ++c[y][!(val^(x&1))];
    if(c[y][0] && c[y][1]) ++mdl;
    if(c[y][0] || c[y][1]) ++cntl;

    if(r[x][0] && r[x][1]) --mdr;
    if(r[x][0] || r[x][1]) --cntr;
    ++r[x][!(val^(y&1))];
    if(r[x][0] && r[x][1]) ++mdr;
    if(r[x][0] || r[x][1]) ++cntr;  

    ++d[((x+y)&1)^val];     
}
inline int query() {
    int ans=0;
    if(!mdl) ans=inc(ans,ksm(2,m-cntl));
    if(!mdr) ans=inc(ans,ksm(2,n-cntr));
    if(!d[0] && !d[1]) ans=dec(ans,2);
    else if(!d[0]) ans=dec(ans,1);
    else if(!d[1]) ans=dec(ans,1);
    return ans;
}

signed main(){
//end at 19:59
#ifdef LOCAL
    Fin("1");
#endif
    n=read();m=read();k=read();
    mdl=mdr=cntl=cntr=0;
    FOR(i,1,k) {
        int x=read(),y=read(),op=read();
        del(x,y);
        if(op==0) add(x,y,0);
        else if(op==1) add(x,y,1);
        cout<<query()<<endl;
    }
#ifdef LOCAL        
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
    return 0;
}
```

---

