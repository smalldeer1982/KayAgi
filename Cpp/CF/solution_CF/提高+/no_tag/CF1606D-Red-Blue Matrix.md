# Red-Blue Matrix

## 题目描述

### 题意简述

给一个 $n$ 行 $m$ 列的矩阵，第 $i$ 行 $j$ 列的元素是 $a_{i,j}$。

现在要求把矩阵的每一行涂成红色或蓝色，要求至少有一行为红，一行为蓝。

将矩阵沿第 $k$ 列分割，第 $1$\~$k$ 列称作左矩阵，第 $k+1$\~$m$ 列称作右矩阵。分割方案要求满足：

* 左矩阵中所有**红色**元素比所有**蓝色**元素大；
* 右矩阵中所有**蓝色**元素比所有**红色**元素大；

求出一种染色及分割方案。

## 样例 #1

### 输入

```
3
5 5
1 5 8 8 7
5 2 1 4 3
1 6 9 7 5
9 3 3 3 2
1 7 9 9 8
3 3
8 9 8
1 5 3
7 5 7
2 6
3 3 3 2 2 2
1 1 1 4 4 4```

### 输出

```
YES
BRBRB 1
NO
YES
RB 3```

# 题解

## 作者：RyexAwl (赞：9)

对于任意一组的合法染色解，一定存在一种分割方案 $cut(idx)$ （我们用 $cut(idx)$ 表示一种分割矩形的方案，意为将矩阵分割成 $1\sim idx$ 列,$idx+1\sim m$ 列的分割方案），满足题目的关于颜色格子权值大小关系的限制。

因此考虑枚举分割方案 $cut(idx)$ ，对每种分割方案尝试构造一种染色方案使其满足题目要求。

考虑题目对于切割出的左边的矩阵的限制：

* 左矩阵中所有红色元素比所有蓝色元素大。

对该限制做一个等价的转换：

* 左矩阵中红色元素的最小值大于蓝色元素的最大值。

因此，我们实际只在意切割出的矩阵每行的最小值与最大值，等价于对问题进行了一个降维。

转化后的限制即：

* $n$ 个二元组 $(Mn,Mx)$ ， 要求从中选出若干个，使得选出的每个二元组满足 $\forall (Mn_i,Mx_i),Mn_i$ 大于任意一个不在集合中二元组的 $Mx'$ 。

因为对于任意二元组 $(Mn,Mx)$ 有 $Mn > Mx$ ，所以选出的每个二元组满足 $\forall (Mn_i,Mx_i),Mn_i$ 大于任意一个不在集合中二元组的 $Mn'$ 。

（将二维不容易确定点对相对关系的限制转化到一维容易确定相对关系的限制上。）

因此如果我们选了一个二元组 $(Mn_k,Mx_k)$ 那么所有 $(Mn_i,Mx_i),Mn_i \ge Mn_k$ 的是必选的。

因此我们将所有的二元组按 $Mn$ 升序排序，对于任一合法的涂色方案涂红色的行一定是排序后的一个后缀。

因此，我们可以得出以下的做法：

* 枚举 $cut(idx)$ 。

* 对于每个固定的 $cut(idx)$ 将所有行按分割出的左边矩阵每行的 $(Mn,Mx)$ 按 $Mn$ 排序。

* 枚举后缀 $O(1)$ check 方案合法性。

如果我们可以在 $O(1)$ 的时间内 check 方案的合法性，那么就可以在 $O(nm\log n)$ 的时间内解决这个问题。

我们发现，实质上在将所有行排列后，相当于枚举两条直线将矩阵分成四个部分，我们的限制为 $\min(C) > \max(A),\min(B) > \max(D)$ ，在枚举的过程维护前缀 $\min,\max$ 即可。


![](https://cdn.luogu.com.cn/upload/image_hosting/5f1u6rnm.png)



我们考虑上述做法正确的根本性原因。

一个很重要的转化是，我们用每一行的前缀 $\min$ 代表出每行的相对关系，即选了 xx 行，一定选 yy 行。

但实际上，回归题目限制，我们从每一行的前缀中随便选一个代表元素 $d_i$ ，如果我们选了第 $k$ 行，那么所有 $d_i\ge d_k$ 的行 $i$ 也一定必选。

因为每个前缀都包含第一列的元素，因此我们可以只按第一列元素排序一次，可以做到 $O(n\log n + nm)$ 的复杂度。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 5e5 + 50;

std::vector<int> a[N],rmax[N],rmin[N];

int p[N],lmin[N],lmax[N],ll[N],rr[N];

int col[N];

void solve(){
	int n,m; gin >> n >> m;
	rep(i,1,n) a[i].resize(m+1),rmin[i].resize(m+1),rmax[i].resize(m+1);
	rep(i,1,n){
		rep(j,1,m) gin >> a[i][j];
		rmin[i][m] = rmax[i][m] = a[i][m];
		per(j,m-1,1) rmin[i][j] = std::min(rmin[i][j+1],a[i][j]),rmax[i][j] = std::max(rmax[i][j+1],a[i][j]);
	}
	rep(i,1,n) p[i] = i;
	std::sort(p+1,p+1+n,[](int x,int y){return a[x][1] > a[y][1];});
	rep(k,1,m-1) {
		if (k == 1) rep(i,1,n) lmin[i] = lmax[i] = a[p[i]][1];
		else rep(i,1,n) lmin[i] = std::min(lmin[i],a[p[i]][k]),lmax[i] = std::max(lmax[i],a[p[i]][k]);
		ll[n] = lmax[n],rr[n] = rmin[p[n]][k+1];
		per(i,n-1,1) ll[i] = std::max(ll[i+1],lmax[i]),rr[i] = std::min(rr[i+1],rmin[p[i]][k+1]);
		int lm = lmin[1],rm = rmax[p[1]][k+1];
		rep(i,1,n-1) {
			lm = std::min(lm,lmin[i]),rm = std::max(rm,rmax[p[i]][k+1]);
			if (lm > ll[i+1] && rm < rr[i+1]) {
				puts("YES");
				rep(j,1,i) col[p[j]] = 1;
				rep(j,i+1,n) col[p[j]] = 0;
				rep(j,1,n) if (col[j]==1) prt << "R"; else prt << "B"; prt << " " << k << edl;
				return;
			}
		}
	} puts("NO");
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    int t; gin >> t; while (t--) solve();
}

}signed main(){wxy::main(); return 0;}
```



---

## 作者：y0y68 (赞：4)

很套路的一个题。

显然，纵列的切割只有 $m-1$ 种方案。

由题意，经切割后，左边矩阵蓝色部分的最大值一定小于左边矩阵红色部分的最小值。弱化这个条件，只考虑第一列，将第一列的数字从小到大排序，以此重组矩阵中每一行的顺序。此时如果第 $i$ 行第一格为蓝色，第 $i+1$ 行第一格为红色，那么 $1 \sim i$ 行第一列均为蓝色，$(i+1) \sim n$ 行第一格均为红色。于是枚举这个 $i$，由于 $i$ 最多只能取 $n-1$。所以需要枚举的情况总数为 $(n-1)(m-1)$，接下来只需 $O(1)$ 验证即可。

显然，若切割前 $i$ 行，前 $j$ 列，只需保证切割后的左上部最大值小于左下部最小值并且右上部最小值大于右下部最大值，即可得到一组合法解。这四个量可以用前缀和与后缀和计算。

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5+5;
int T,n,m,p[N];char ans[N];
vector<int>a[N],fmn[N],fmx[N],gmn[N],gmx[N],zsmx[N],zxmn[N],ysmn[N],yxmx[N];
//p[i]表示排完序后的第i个是第几行
//fmn表示每行的前缀最小，同理fmx（这里的前缀以排完序后的矩阵来算，一下同理）
//gmn表示每行的后缀最小，同理gmx
//zxmn表示位置(i,j)左下部的最小值
//zsmx表示位置(i,j)左上部的最大值
//ysmn表示位置(i,j)右上部的最小值
//yxmx表示位置(i,j)右下部的最大值
bool cmp(int x,int y){
	return a[x][1]<a[y][1];
}
int main(){
	for(cin>>T;T;T--){
		cin>>n>>m;
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=m+1;j++){
				a[i].push_back(0);
				fmn[i].push_back(1e6+5);
				gmn[i].push_back(1e6+5);
				fmx[i].push_back(0);
				gmx[i].push_back(0);
				zsmx[i].push_back(0);
				zxmn[i].push_back(1e6+5);
				ysmn[i].push_back(1e6+5);
				yxmx[i].push_back(0);
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&a[i][j]);
		for(int i=1;i<=n+1;i++)
			p[i]=i;
		sort(p+1,p+n+1,cmp);
		for(int j=1;j<=m;j++){
			for(int i=1;i<=n;i++){
				fmx[p[i]][j]=max(a[p[i]][j],fmx[p[i-1]][j]);
				fmn[p[i]][j]=min(a[p[i]][j],fmn[p[i-1]][j]);
			}
			for(int i=n;i>=1;i--){
				gmx[p[i]][j]=max(a[p[i]][j],gmx[p[i+1]][j]);
				gmn[p[i]][j]=min(a[p[i]][j],gmn[p[i+1]][j]);
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				zsmx[p[i]][j]=max(zsmx[p[i]][j-1],fmx[p[i]][j]);
		for(int i=1;i<=n;i++)
			for(int j=m;j>=1;j--)
				ysmn[p[i]][j]=min(ysmn[p[i]][j+1],fmn[p[i]][j]);
		for(int i=n;i>=1;i--)
			for(int j=1;j<=m;j++)
				zxmn[p[i]][j]=min(zxmn[p[i]][j-1],gmn[p[i]][j]);
		for(int i=n;i>=1;i--)
			for(int j=m;j>=1;j--)
				yxmx[p[i]][j]=max(yxmx[p[i]][j+1],gmx[p[i]][j]);
		int t1=-1,t2=-1;
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++)
				if(zsmx[p[i]][j]<zxmn[p[i+1]][j]&&ysmn[p[i]][j+1]>yxmx[p[i+1]][j+1]){
					t1=i,t2=j;break;
				}
		if(t1==-1)puts("NO");
		else{
			puts("YES");
			for(int i=1;i<=t1;i++)ans[p[i]]='B';
			for(int i=t1+1;i<=n;i++)ans[p[i]]='R';
			for(int i=1;i<=n;i++)putchar(ans[i]);
			printf(" %d\n",t2);
		}
		for(int i=0;i<=n+1;i++){
			a[i].clear();
			fmn[i].clear(),gmn[i].clear(),fmx[i].clear(),gmx[i].clear();
			zsmx[i].clear(),zxmn[i].clear(),ysmn[i].clear(),yxmx[i].clear();
		}
	}
	return 0;
}
```

---

## 作者：Cupids_Bow (赞：3)

## 思路：前缀和 + 暴力

### 题意

题目大意为在给定的 $n \cdot m$ 的矩形中选出若干行涂成红色，剩下部分为蓝色，若涂色之后能够选定一个分界线 $k$ 使得左边 $k$ 列中红色格子内的数都大于蓝色格子内的数，右边 $m - k$ 列中蓝色格子内的数都大于红色格子内的数，就称为一个合法的划分。问给定矩阵是否存在一个合法的划分。

### 思路

不妨假定 $k = 1$ ，若第一列合法，则第一列中红色的方块一定是取最大的连续若干个，所以可以根据第一列的数 $a_{i,1}$ 对行进行排序，排完序之后红色的格子一定只能取第 $i$ 到 $n$ 行，其中 $i \geq 2$ 。那么再枚举列进行判断就可以了，按照下图这样判断。

![](https://cdn.luogu.com.cn/upload/image_hosting/vzdkfkjn.png)

用 4 个前缀和预处理一下 4 个角的 $\max$ 和 $\min$ 后枚举中间点判断即可。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll=long long;

const int N=(int)5e5+5;
int _;

vector<int> a[N];
vector<int> p1[N],p2[N],p3[N],p4[N];
int n,m;
int p[N];
char ans[N];

void work(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;i++){
        p1[i].clear();
        p2[i].clear();
        p3[i].clear();
        p4[i].clear();
        a[i].clear();
        p1[i].resize(m+5,0);
        p2[i].resize(m+5,(int)1e6);
        p3[i].resize(m+5,(int)1e6);
        p4[i].resize(m+5,0);
        a[i].resize(m+5,0);
    }
    for(int i=1;i<=n;i++)
        for(int j=1,x;j<=m;j++) scanf("%d",&a[i][j]);
    iota(p,p+2+n,0);
    sort(p+1,p+1+n,[](const int& x,const int& y){
        return a[x][1]<a[y][1];//排序另用一个数组排下表，可以不用直接交换vector
    });
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            p1[p[i]][j]=a[p[i]][j];
            p1[p[i]][j]=max(p1[p[i]][j],p1[p[i-1]][j]);
            p1[p[i]][j]=max(p1[p[i]][j],p1[p[i]][j-1]);
        }
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--){
            p2[p[i]][j]=a[p[i]][j];
            p2[p[i]][j]=min(p2[p[i]][j],p2[p[i-1]][j]);
            p2[p[i]][j]=min(p2[p[i]][j],p2[p[i]][j+1]);
        }
    for(int i=n;i>=1;i--)
        for(int j=1;j<=m;j++){
            p3[p[i]][j]=a[p[i]][j];
            p3[p[i]][j]=min(p3[p[i]][j],p3[p[i+1]][j]);
            p3[p[i]][j]=min(p3[p[i]][j],p3[p[i]][j-1]);
        }
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--){
            p4[p[i]][j]=a[p[i]][j];
            p4[p[i]][j]=max(p4[p[i]][j],p4[p[i+1]][j]);
            p4[p[i]][j]=max(p4[p[i]][j],p4[p[i]][j+1]);
        }
    for(int i=n;i>=2;i--){
        for(int j=1;j<=m-1;j++){
            if(p3[p[i]][j]>p1[p[i-1]][j]&&p2[p[i-1]][j+1]>p4[p[i]][j+1]){
                for(int k=1;k<=n;k++) ans[k]='B';
                for(int k=n;k>=i;k--) ans[p[k]]='R';
                printf("YES\n");
                for(int k=1;k<=n;k++) printf("%c",ans[k]);
                printf(" %d\n",j);
                return;
            }
        }
    }
    printf("NO\n");
}

int main(){
    _=1;
    scanf("%d",&_);
    while(_--){
        work();
    }
    return 0;
}
```

---

## 作者：Michael1234 (赞：1)

- 本题可以是用**模拟**的思路：

- 考虑到数据范围的特殊，本题**只能**使用 `vector` 解决，下文将使用 $v$ 数组代替题面中的 $a$ 数组。

- 通过分析题目，若第一列的红色部分的**最小值**小于蓝色部分的**最大值**时，其不满足分割要求。

- 这是因为此时红色部分的最小值**只能更小**，蓝色部分的最大值**只能更大**，所以此条件在红蓝行不变情况下**永远成立**。

- 所以在确定红蓝行时，可以按照**第一个元素**的大小**排序每一行**，并标记每行的**原来位置**。

- 则有形如：（`B` 为蓝，`R` 为红）

```
BBB
BBB
RRR
```

- 则可计算四个**前缀和**，分别计算左上（$a$）与右下（$d$）的**最大值**与右上（$b$）与左下（$c$）的**最小值**。

- 当前 $h$ 行为蓝，前 $l$ 行为左矩阵时若 $a_{i,j}<c_{i+1,j}$ 且 $b_{i,j+1}>d_{i+1,j+1}$，则当前解合法，记录，输出。

## CODE

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=5e5+5,inf=0x3f3f3f3f;
int t,n,m,x,ansh,ansl;
char ans[N];
vector<int>a[N],b[N],c[N],d[N];
struct vec
{
	vector<int>v;
	inline int& operator [](int id)
	{
		return v[id];
	}
	inline bool operator <(vec x)const
	{
		return v[1]<x.v[1];//按第一位排序
	}
	inline void clear()
	{
		v.clear();
		return;
	}
	inline void pb(int x)
	{
		v.pb(x);
		return;
	}
}v[N];//只为能排序,已贴心设计成vector
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(cin>>t;t;t--)
	{
		cin>>n>>m;
		for(int i=0;i<=n+1;i++)
		{
			a[i].clear();
			b[i].clear();
			c[i].clear();
			d[i].clear();
			v[i].clear();
			a[i].resize(m+2,0);
			b[i].resize(m+2,inf);
			c[i].resize(m+2,inf);
			d[i].resize(m+2,0);//初始化好大小，以防RE
			v[i].pb(i);//细节:把原位置存在第0位
			if(i==0||i==n+1)//边框也要初始化
			{
				continue;
			}
			for(int j=1;j<=m;j++)
			{
				cin>>x;
				v[i].pb(x);
			}
		}
		sort(v+1,v+n+1);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				a[i][j]=max(v[i][j],max(a[i-1][j],a[i][j-1]));
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=m;j>=1;j--)
			{
				b[i][j]=min(v[i][j],min(b[i-1][j],b[i][j+1]));
			}
		}
		for(int i=n;i>=1;i--)
		{
			for(int j=1;j<=m;j++)
			{
				c[i][j]=min(v[i][j],min(c[i+1][j],c[i][j-1]));
			}
		}
		for(int i=n;i>=1;i--)
		{
			for(int j=m;j>=1;j--)
			{
				d[i][j]=max(v[i][j],max(d[i+1][j],d[i][j+1]));
			}
		}//四个前缀和
		ansh=0;
		ansl=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
			{
				if(a[i][j]<c[i+1][j]&&b[i][j+1]>d[i+1][j+1])
				{//找合法情况
					ansh=i;
					ansl=j;
					break;
				}
			}
		}
		if(!ansh&&!ansl)
		{//若无合法情况,无解
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
		{
			if(i<=ansh)
			{
				ans[v[i][0]]='B';
			}
			else
			{
				ans[v[i][0]]='R';
			}//重置答案
		}
		for(int i=1;i<=n;i++)
		{
			cout<<ans[i];
		}
		cout<<" "<<ansl<<"\n";
	}
	exit(0);
}

```

---

## 作者：Genius_Star (赞：1)

### 题意：

现有一个 $n \times m$ 的矩阵，每个格子上写有一个数字。

将矩阵的 $n$ 行中选取一些涂成红色，剩余涂成蓝色。

并竖着分成左右两块。

对于左边的几列，满足：红色格子上的数严格大于蓝色格子上的数。

对于右边的几列，满足：红色格子上的数严格小于蓝色格子上的数。

问：是否能满足？能的话给出一种染色与分开方案。

### 思路：

我们考虑直接枚举一个分开点 $j$，我们需要快速求出对于这样一个分开点，满足要求的染色方案。

因为实现是 4s，$O(n \times m)$ 的时间复杂度是可以过去的，也就是说我们需要在 $O(n)$ 的时间对于一个分开点求染色方案。

考虑将左侧的每一行的最小值进行排序，我们可以枚举 $i$，表示要选 $i$ 行为蓝色，那么肯定是选其中最小值最小的那 $x$ 行染色为蓝色。

因为要使得红色格子上的数严格大于蓝色格子上的数，只要有一个蓝色的数大于等于了红色的数，那么不成立，所以我们要选最小的数。

但是这并不保证满足了这个条件，必须要蓝色区域的最大数要小于红色区域的最大数，这样才可以保证满足。

所以我们现在要求左侧蓝色区域的最大数与左侧红色区域的最小数，但是我们之前的复杂度已经高达 $O(n \times m)$，所以这里我们要 $O(1)$ 求。

虽然使用线段树可以 $O(\log n)$ 查询，但是被卡了……

但是我们发现这里没有修改操作，所以我们可以用 $O(n \times m)$ 的时间先对于初始的矩阵求出 $L1,L2,R1,R2$，其中 $L1_{i,j},L2_{i,j}$ 表示第 $i$ 行从左向右前 $j$ 个数的最大值/最小值，$R1_{i,j},R2_{i,j}$ 则表示第 $i$ 行从第 $j$ 个数到第 $m$ 个数的最大值/最小值。

初始的话肯定是：

$$L1_{i,1}=L2_{i,1}=a_{i,1}$$
$$R1_{i,m}=R2_{i,m}=a_{i,m}$$

然后我们转移：

$$L1_{i,j}=\min(L1_{i,j-1},a_{i,j})$$

$$L2_{i,j}=\max(L2_{i,j-1},a_{i,j})$$

这个的意思就是对于第 $i$ 行的前 $j$ 个数的最大值/最小值，等于前 $j-1$ 个数的最大值/最小数与当前这个数的最大值/最小值。

对于从右向左的转移也差不多：

$$R1_{i,j}=\min(R1_{i,j+1},a_{i,j})$$

$$R2_{i,j}=\max(R2_{i,j+1},a_{i,j})$$

求出这个以后，我们枚举分开点 $j$，然后将其左侧的每一行的最小值和行的编号加入一个向量之中，然后我们按照最小值进行排序。

然后我们在将已经按照最小值排序的行的编号放在 $t$ 数组中，我们现在要求的就是左侧蓝色区域的最大数与左侧红色区域的最小数右左侧蓝色区域的最小数与右侧红色区域的最大数（因为两边条件都要满足）。

我们再定义四个数组 $L3,L4,R3,R4$，其中 $L3_i$ 代表对于排序过后的顺序，左侧中前 $i$ 个数中的最大值，$L4_i$ 代表对于排序过后的顺序，左侧中从第 $i$ 个数到第 $n$ 个数的最小值，右侧中$R3_i$ 代表对于排序过后的顺序，从第 $i$ 个数到第 $n$ 个数的最大值，$R4_i$ 代表对于排序过后的顺序，右侧中从第 $i$ 个数到第 $n$ 个数的最小值。

注意，上面的表达可能有点儿绕，对于左侧和右侧的最大值/最小值定义是不同的。

那我们现在考虑如何求：

$$L3_i=\max(L3_{i-1},L2_{t_i,j})$$

$$R4_i=\min(R4_{i-1},R1_{t_i,j+1})$$

$$L4_i=\min(L4_{i+1},L1_{t_i,j})$$

$$R3_i=\max(R3_{i+1},R2_{t_i,j+1})$$

所以对于每次分割的时候我们都要算一次，计算的时间为 $O(n)$，这样我们后面枚举选 $i$ 个点为蓝色时，我们只需要判断 $L3_i > L4_{i+1}$ 并且 $R4_i>R3_{i+1}$，这个条件是满足的，那么就可以输出这次染色的方案。

时间复杂度：$O(n \times m)$。

~~emm……这预处理有亿点儿多，我这个作者写着写着也写蒙了……~~

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=500500;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,m;
void solve(){
	n=read(),m=read();
	ll L1[n+1][m+1],L2[n+1][m+1],R1[n+1][m+1],R2[n+1][m+1],t[n+1];
	ll a[n+1][m+1];
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    a[i][j]=read();			
	for(int i=1;i<=n;i++){
	    L1[i][1]=L2[i][1]=a[i][1];
	    R1[i][m]=R2[i][m]=a[i][m];
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
		    L2[i][j]=max(L2[i][j-1],a[i][j]);
		    L1[i][j]=min(L1[i][j-1],a[i][j]);
		}		
	}
	for(int i=1;i<=n;i++){
		for(int j=m-1;j>=1;j--){
		    R2[i][j]=max(R2[i][j+1],a[i][j]);
		    R1[i][j]=min(R1[i][j+1],a[i][j]);
		}
	}
	for(int j=1;j<m;j++){
	    vector<pair<ll,ll>> v;
	    for(int i=1;i<=n;i++) 
		  v.push_back(make_pair(L1[i][j],i));
	    sort(v.begin(),v.end());
	    ll t[n+1]; 
	    ll L3[n+2],L4[n+2],R3[n+2],R4[n+2];
		for(int i=1;i<=n;i++) 
		  t[i]=v[i-1].second;
	    for(int i=0;i<=n+1;i++) 
		  L3[i]=R3[i]=0,L4[i]=R4[i]=1e9;
	    for(int i=1;i<=n;i++){
	        L3[i]=max(L3[i-1],L2[t[i]][j]);
	        R4[i]=min(R4[i-1],R1[t[i]][j+1]);
	    }
	    for(int i=n;i>=1;i--){
	        L4[i]=min(L4[i+1],L1[t[i]][j]);
	        R3[i]=max(R3[i+1],R2[t[i]][j+1]);
	    }
		for(int i=1;i<n;i++){
			if(L3[i]<L4[i+1]&&R4[i]>R3[i+1]){
				char s[n+1]={'\0'};
				puts("YES");
				for(int k=1;k<=n;k++)
				  s[t[k]-1]=(k<=i?'B':'R');
				printf("%s",s);
				putchar(' ');
				write(j);
				putchar('\n');
				return ;
			}
		}
	}
	puts("NO");
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```


---

