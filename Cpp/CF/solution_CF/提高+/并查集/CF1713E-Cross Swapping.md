# Cross Swapping

## 题目描述

You are given a square matrix $ A $ of size $ n \times n $ whose elements are integers. We will denote the element on the intersection of the $ i $ -th row and the $ j $ -th column as $ A_{i,j} $ .

You can perform operations on the matrix. In each operation, you can choose an integer $ k $ , then for each index $ i $ ( $ 1 \leq i \leq n $ ), swap $ A_{i, k} $ with $ A_{k, i} $ . Note that cell $ A_{k, k} $ remains unchanged.

For example, for $ n = 4 $ and $ k = 3 $ , this matrix will be transformed like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/d1b19f5b512e1f5ff57fc09bc0db3a4a06f7217c.png)The operation $ k = 3 $ swaps the blue row with the green column.You can perform this operation any number of times. Find the lexicographically smallest matrix $ ^\dagger $ you can obtain after performing arbitrary number of operations.

 $ {}^\dagger $ For two matrices $ A $ and $ B $ of size $ n \times n $ , let $ a_{(i-1) \cdot n + j} = A_{i,j} $ and $ b_{(i-1) \cdot n + j} = B_{i,j} $ . Then, the matrix $ A $ is lexicographically smaller than the matrix $ B $ when there exists an index $ i $ ( $ 1 \leq i \leq n^2 $ ) such that $ a_i < b_i $ and for all indices $ j $ such that $ 1 \leq j < i $ , $ a_j = b_j $ .

## 说明/提示

Note that in every picture below the matrix is transformed in such a way that the blue rows are swapped with the green columns.

In the first test case, we can perform $ 1 $ operation for $ k = 3 $ . The matrix will be transformed as below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/88f476fc46013e92b5ee2e2b1dd8db92737cd1fe.png) In the second test case, we can perform $ 2 $ operations for $ k = 1 $ and $ k = 3 $ :  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/7dca46c6a1cae82c4c4f4ef39e7a9d0c69d58c39.png)  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/64667956c5c35ceed44d4424defaf36a557d6e58.png)

## 样例 #1

### 输入

```
2
3
2 1 2
2 1 2
1 1 2
4
3 3 1 2
1 1 3 1
3 2 3 2
2 3 3 1```

### 输出

```
2 1 1
2 1 1
2 2 2
3 1 1 2
3 1 2 1
3 3 3 3
2 3 2 1```

# 题解

## 作者：Licykoc (赞：9)

对于矩阵中的 $a_{x,y}$，它只有经过 $k=x$ 或 $k=y$ 的操作后才能与 $a_{y,x}$ 对调。于是我们可以单独考虑每个 $a_{x,y}$ 。

要求字典序最小，所以从上到下，从左到右进行枚举。这里注意，我们不用考虑 $x \lt y$ 的情况，因为 $a_{y,x}$ 已经被枚举过。

具体一些，
- 如果 $a_{x,y} \gt a_{y,x}$，显然交换更优，交换的条件是进行 $k=x$ **或** $k=y$ 的操作。

- 如果 $a_{x,y} = a_{y,x}$，直接略过，因为交换后无影响。

- 如果 $a_{x,y} \lt a_{y,x}$，不交换更优，这样的条件是 $k=x$ **与** $k=y$ 操作都进行或都不进行。

发现对于每个操作 $k=i$ 都有两种状态：进行或不进行。并且我们只关心操作之间的关系，所以可以使用带权异或并查集来维护。

实现：

```cpp
#include<bits/stdc++.h>
#define UP(x,l,r) for (int x=(int)l;x<=(int)r;++x)
#define DOWN(x,l,r) for (int x=(int)l;x>=(int)r;--x)
#define IOS ios::sync_with_stdio(0),cin.tie(0)
#define low(x) (x&(-x))
#define fi first
#define se second
#define pb push_back
#define isdigit(c) (c>='0'&&c<='9')
using namespace std;
inline void read (int &x) {
    char c=getchar(); int w=0; x=0;
    for (;!isdigit(c);c=getchar()) w^=!(c^45);
    for (;isdigit(c);c=getchar()) x=(x*10)+(c^48);
    x=w?-x:x;
}
typedef pair<int,int> pii;
const int MAXN=1e3+10;
int T,n;
int a[MAXN][MAXN];
int f[MAXN],s[MAXN];
int get (int x) {
    if (f[x]==x) return x;
    int to=get(f[x]);
    s[x]^=s[f[x]];
    return f[x]=to;
}
signed main () {
    read(T);
    while (T--) {
        read(n);
        UP(i,1,n) UP(j,1,n) read(a[i][j]);
        iota(f+1,f+n+1,1); //set f[1]=1,f[2]=2,...f[n]=n
        fill(s+1,s+n+1,0);
        UP(i,1,n) UP(j,i+1,n) if (a[i][j]!=a[j][i]) {
            int fx=get(i),fy=get(j);
            if (a[i][j]>a[j][i]) {
                if (fx!=fy) {
                    f[fx]=fy; s[fx]=(s[i]^s[j]^1);
                    swap(a[i][j],a[j][i]);
                } else if (s[i]^s[j]) swap(a[i][j],a[j][i]);
            } else
            if (a[i][j]<a[j][i]) {
                if (fx!=fy) {
                    f[fx]=fy; s[fx]=(s[i]^s[j]);
                } else if (s[i]^s[j]) swap(a[i][j],a[j][i]);
            }
        }
        UP(i,1,n) {UP(j,1,n) printf("%d ",a[i][j]); puts("");}
    }
}
```

---

## 作者：_•́へ•́╬_ (赞：8)

## 思路

操作 $i$，就是把第 $i$ 行和第 $i$ 列交换。

大眼观察题目性质：

1. 主对角线上的东西永远不变。
2. $a[i][j]$ 能且仅能与 $a[j][i]$ 交换，其做法有两种：进行操作 $i$，或进行操作 $j$。
3. 要求字典序最小，所以我们从上往下从左往右贪心。
4. - 如果我想让 $a[i][j]$ 与 $a[j][i]$ 交换，那么我应该操作 $i$ 并不操作 $j$，或操作 $j$ 并不操作 $i$，即 $i$ 与 $j$ 操作情况相反。
	- 如果我不想让 $a[i][j]$ 与 $a[j][i]$ 交换，那么我应该不操作 $i$ 并不操作 $j$，或操作 $i$ 并操作 $j$（转两次转回来了），即 $i$ 与 $j$ 操作情况相同。

我选择使用带权并查集维护操作情况相同或相反的关系。

## code

```cpp
#include<stdio.h>
#define N 1000
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,a[N][N],f[N],ff[N];
inline int find(const int&x)//路径压缩
{
	if(x==f[x])return x;
	int tmp=find(f[x]);
	ff[x]^=ff[f[x]];
	return f[x]=tmp;
}
main()
{
	for(read(t);t--;)
	{
		read(n);
		for(int i=0;i<n;f[i]=i,ff[i++]=0)for(int j=0;j<n;read(a[i][j++]));
		for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(i^j)if(find(i)^find(j))
		{
			if(a[i][j]<a[j][i])//不换
			{
				ff[f[i]]=ff[i]^ff[j];//ij边权为0
				f[f[i]]=f[j];
			}
			if(a[i][j]>a[j][i])//换
			{
				ff[f[i]]=ff[i]^ff[j]^1;//ij边权为1
				f[f[i]]=f[j];
			}
		}
		for(int i=0;i<n;++i)if(find(i),ff[i])
			for(int j=0;j<n;++j)if(i^j)//进行操作
				a[i][j]^=a[j][i]^=a[i][j]^=a[j][i];
		for(int i=0;i<n;putchar('\n'),++i)//输出
			for(int j=0;j<n;printf("%d ",a[i][j++]));
	}
}
```

挺简单的啊，可惜赛时没搞出来。

---

## 作者：Purslane (赞：5)

## Solution

首先观察性质 :

- $a_{x,y}$ 只和 $a_{y,x}$ 有联系 .
- 只要对 $x$ 或 $y$ 进行操作 , 就一定会交换 .
- 操作的先后顺序没有影响 .
- 对同一个数进行两次操作等于没操作 .

所以现在开一个数组 $flg_i$ 表示是否对 $i$ 进行了操作 . 

如果 $a_{x,y}$ 与 $a_{y,x}$ 交换了 , 那么 $flg_x \oplus flg_y=1$ . 那么必有 $flg_x \neq flg_y$ . 如果不交换 , 就有 $flg_x = flg_y$ . 

显然可以用扩展域并查集维护 . 

贪心考虑 . 从前往后考虑 . 这时应满足 $i>j$ . 不然会对之前有影响 .

所以可以看是否必须翻转 , 或必须不翻转 . 然后用并查集维护即可 .

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10;
int T,n,fa[MAXN],a[MAXN][MAXN];
int find(int k) {
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);	
}
void merge(int x,int y) {
	if(find(x)==find(y)) return ;
	fa[find(x)]=find(y);
	return ;	
}
void work(void) {
	memset(fa,0,sizeof(fa));
	cin>>n;	
	ffor(i,1,n+n) fa[i]=i;
	ffor(i,1,n) ffor(j,1,n) cin>>a[i][j];
	ffor(i,1,n) ffor(j,i+1,n) if(a[j][i]<a[i][j]) {
		if(find(i)==find(j)) continue;
		merge(i,j+n),merge(i+n,j);
	}
	else if(a[j][i]>a[i][j]) {
		if(find(i)==find(j+n)||find(i+n)==find(j)) continue;
		if(find(i)==find(j)) continue;
		merge(i,j),merge(i+n,j+n);
	}
	ffor(i,1,n) ffor(j,i+1,n) if(find(i)==find(j+n)) swap(a[i][j],a[j][i]);
	ffor(i,1,n) {ffor(j,1,n) cout<<a[i][j]<<' ';cout<<'\n';}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) work();
	return 0;	
}
```

---

## 作者：Butterfly_Effect (赞：3)

## Part1.题目大意
  对于一个 $n\times n$ 的矩阵，每次操作可以调换第 $i$ 行和第 $i$ 列的数字，求若干次操作时之后的字典序最小值
  
## Part2.思路
- $a_{i,j}$ 只可能和 $a_{j,i}$ 的值相关

   那么显然的贪心思路就是,尽量让字典序在前的位置 $(i-1)\times n+j$
   
   当  $i \leq j$  时， $a_{i,j} \leq a_{j,i}$
      
-  对于 $a_{i,j}$

    $k=i$ 和 $k=j$ 时的效果是一样的，如果执行奇数次则与$a_{j,i}$互换，  偶数次则不变
     
 
## Part3.代码实现
执行奇数次与偶数次，也就是换与不换，很容易让我们想到并查集，我们用 $i$ 来表示对第 $i$ 行执行操作，$i+n$ 表示不对第 $i$ 行执行操作，则对于 $i<j$

- $a_{i,j}>a_{j,i}$  $    $

  对于这种情况，我们将 $i$ 和 $j+n$ 、 $i+n$ 和 $j$ 放在一个集合，这样就可以保证 $a_{i,j}$ 与 $a_{j,i}$ 值互换
- $a_{i,j}<a_{j,i}$ 
 
     对于这种情况，我们将 $i$ 和 $j$ 、 $i+n$ 和 $j+n$ 放在一个集合，这样就可以保证 $a_{i,j}$ 与 $a_{j,i}$ 值不互换

当然，我们将字典序排序在前的位置优先考虑


## Part4.丑陋的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int N=1005;
int T,n,a[N][N],fa[N<<1];

int find(int k)
{
	if(fa[k]==k) return k;
	else return fa[k]=find(fa[k]);
}

void add(int x,int y)//并查集
{
	int fx=find(x),fy=find(y);
	if(abs(fx-fy)%n!=0) fa[fx]=fy; 	
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);	
		for(int i=1;i<=2*n;i++) fa[i]=i;
		for(int i=1;i<=n;i++)	
			for(int j=i+1;j<=n;j++) 
				if(a[i][j]<a[j][i]) add(i,j),add(i+n,j+n);
				else if(a[i][j]>a[j][i]) add(i,j+n),add(i+n,j);
		for(int i=1;i<=n;i++)
		{
			if(find(i)>n) continue;//只要取其中一组操作即可
			for(int j=1;j<=n;j++) swap(a[i][j],a[j][i]);	
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++) printf("%d ",a[i][j]);
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：Zeardoe (赞：2)

题意：给定一个 $n \times n$ 的矩阵 $a$，矩阵里有数字。可以进行若干个如下操作：
```
modify(k):

for i in range [1,n]:
	swap(a[i][k],a[k][i])
```
使得这个矩阵的字典序最小化。输出这个矩阵。

分析：赛时连贪心都没想到。字典序问题，就是要贪心，争取把当前位置搞到最优化，然后再考虑其他位置。

如果做一次操作 `modify(i)`，那么可以将 $a[i][j]$ 和 $a[j][i]$ 交换，并且 $a[i][j]$ 不可能和别的位置交换了。
那么我们对于从先到后的 $(i,j)|j>i$，要尽可能让 $a[i][j]<a[j][i]$。
如果一开始 $a[i][j]>a[j][i]$，那么就要考虑 `modify(i)` **或者** `modify(j)`。但是不能两个都做，否则没有起到交换的作用。
如果一开始 $a[i][j]<a[j][i]$，我们不可以让它改变。那么要么两个都不 `modify`，要么两个都 `modify`。
如果一开始 $a[i][j]=a[j][i]$，爱咋咋地。
并且如果给一个位置交换多次，其中的偶数次都可以相互抵消，所以只交换至多一次是足够并且最优的。

那么我们的问题变成了：进行一系列的 `modify` 操作，使得按顺序（优先级）满足以下条件，如果无法满足就跳过：
- $i$ 和 $j$ 需要 `modify` 其中一个。
- $i$ 和 $j$ 不能只 `modify` 其中一个。

这样的条件，类比到“朋友敌人并查集”，**第一种关系相当于“敌人”关系，第二种关系相当于“朋友”关系。**
可以使用扩展域并查集（也叫种类并查集）。

我们先遍历一遍 $(i,j)|j>i$，并视情况加上“朋友”/“敌人”关系或不加关系。然后会变成两个连通块加一些孤点（因为不加关系的存在）这时候我们选择其中一个连通块（假设是标号为 $1$ 的连通块）并 `modify` 这个连通块里所有的元素。

但是还有一个问题，如果 $1$ 就是孤点不就找不到连通块了吗？这可不行。我们干脆直接让孤点全选，就避免了这个问题。
具体做法是：在开找连通块之前，如果 $i$ 和 $1$ 没有朋友关系也没有敌人关系，那么就让 $i$ 和 $1$ 存在朋友关系。（存在敌人关系也是可以的）这样做之后，整张图变成两个连通块，直接找 $1$ 所在的一个即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
int a[1010][1010];
int n; 
int fa[2010];
int get(int x) {
    if(fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y) {
    x = get(x), y = get(y);
    if(x == y) return;
    fa[x] = y;
}
bool same(int x, int y) {return get(x) == get(y);}
void modify(int k) {
    f(i, 1,n) swap(a[i][k], a[k][i]);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    //think twice,code once.
    //think once,debug forever.
    int t; cin >> t;
    while(t--) { 
        cin >> n;
        f(i, 1, n)f(j, 1, n) cin >> a[i][j];
        f(i, 1,2*n) fa[i] = i;
        f(i, 1, n) f(j, i + 1, n) {
            if(a[i][j] > a[j][i]) {
                if(same(i, j)) continue;
                merge(i, j + n); merge(j, i + n);
            }
            else if(a[i][j] < a[j][i]){
                if(same(i, j + n)) continue;
                merge(i, j); merge(i + n, j + n);
            }
        }
        f(i, 1, n) if(!same(1, i) && !same(1, i+n)) merge(1, i);
        f(i, 1, n) {
            if(same(i, 1)) modify(i);
        }
        f(i, 1,n) f(j ,1 ,n)cout << a[i][j]<<" \n"[j==n];
    }
    return 0;
}
```

---

## 作者：lzytag (赞：1)

## 并查集模板（雾

我们观察这个操作，对于每一次操作 $k$，相当于使第 $k$ 行于第 $k$ 列沿着正方形从左上到右下的对角线做了一次对称，于是我们可以很快得到以下三点**重要结论**。

- 对于每一个节点 $A_{i,j}$，他能且只能于节点 $A_{j,i}$ 进行交换。
- 若 $A_{i,j}$ 与 $A_{j,i}$ 发生了交换，则 $i$ 与 $j$ 中**有且只有一个进行了操作**。
- 若 $A_{i,j}$ 未与 $A_{j,i}$ 发生了交换，则 $i$ 与 $j$ **要么同时被操作。要么同时未被操作**。

既然这题最后要求是使字典序最小，那么我们很明显可以**贪心**。

我们依次看正方形对角线上方的点，对于对角线上方的点 $A_{i,j}(i>j)$，很明显他的优先度大于 $A_{j,i}$ ，如果 $A_{i,j} < A_{j,i}$ 则贪心地要求他**被换**，也就是“$i$ 与 $j$ 中有且只有一个进行了操作”；若$A_{i,j} > A_{j,i}$ 则贪心地要求他**不被换**，也就是“$i$ 与 $j$ 要么同时被操作。要么同时未被操作”。

于是问题就变成了如何处理这些要求，而处理这些要求可以使用**带权并查集**，具体用法可以参考[P1525关押罪犯](https://www.luogu.com.cn/problem/P1525)。

当要求之间互相冲突时，我们就只能不满足后提出的要求了，毕竟很显然，先提出的要求比后提出的要求重要。

具体实现可以看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
//file head over
bool w[1005];
int fa[1005],n,a[1005][1005];
int GetFa(int x)
{
	if(fa[x] == x) return x;
	GetFa(fa[x]);
	w[x] = w[fa[x]]^w[x];
	return fa[x] = fa[fa[x]];
}
bool merge(int u,int v,int e)
{
	int fu = GetFa(u),fv = GetFa(v);
	if(fu == fv) return w[u]^w[v]^e == 0;
	fa[fu] = fv;
	w[fu] = w[u]^w[v]^e;
	return 1;
}
int main()
{
	int T = read();
	while(T--)
	{
		n = read();
		for(int i = 1;i <= n;i++) fa[i] = i,w[i] = 0;
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++) 
			{
				a[i][j] = read();
			}
		}
		for(int i = 1;i <= n;i++)
		{
			for(int j = i+1;j <= n;j++)
			{
				if(a[i][j] > a[j][i])
				{
					if(merge(i,j,1)) swap(a[i][j],a[j][i]); //i,j只能选一个 
				}
				else if(a[i][j] < a[j][i])
				{
					if(!merge(i,j,0)) swap(a[i][j],a[j][i]); //i,j同时选或同时不选
				}
			}
		}
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++) printf("%d ",a[i][j]);
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：Error_Eric (赞：1)

#### 题意

给定一个 $n\times n$ 的矩阵。一次操作可以给定一个 $k$ 然后交换所有的 $A_{i,k}$ 和 $A_{k,i}$ 。

如图表示 $n=4,k=3$ 的情况。 

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/d1b19f5b512e1f5ff57fc09bc0db3a4a06f7217c.png)

求若干次操作后字典序最小的矩阵。

#### 解法

对于一个 $k$ ，执行超过一次没有意义。

$C_i$ 表示 $k=i$ 时是否执行。

显然 $A_{x,y}$ 仅仅可以和 $A_{y,x}$ 交换。其中 $A_{x,x}$ 动不了。

对于 $A_{x,y}$ 和 $A_{y,x}$ ,最终交换了，当且仅当 $C_x \not=C_y$ 。

那么按照字典序枚举矩阵中所有满足 $j>i$ 的元素，如果 $A_{i,j}<A_{j,i}$ 则说明 $C_x$ 和 $C_y$ 在同一集合。如果 $A_{i,j}>A_{j,i}$ 则说明两者不在同一集合。

左转 [BOI2003团伙](https://www.luogu.com.cn/problem/P1892) 。

注意若前后矛盾取前者。

#### Code

没啥好讲解的。

[Link](https://codeforces.ml/contest/1713/submission/167691079)

---

## 作者：Symbolize (赞：0)

# 思路
不难发现一下两点：
1. 对角线上的数怎么都不会被换走。
2. 对于 $a_{i,j}$ 来说，只能与 $a_{j,i}$ 交换，而且交换两次就换回来了，没有改变。

进一步思考，对于第二条，显然操作 $k=i$ 与操作 $k=j$ 的效果一致，先后无影响。

那对于每个数，面临的问题不过是交换与不交换而已。

那他要字典序最小，不就从上往下贪心吗？

只需要用并查集来维护翻转与不翻转的信息就行了。
# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>//万能头 
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=2e3+10;//别开太大，就因为我之前开了1e6，调了好久qwq 
using namespace std;
int t,n,fa[N],a[N][N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
int find(int x)//找祖宗 
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);//记忆化 
}
void merge(int x,int y){fa[find(x)]=find(y);return;}//并查集的合并 
void getans() 
{
	memset(fa,0,sizeof fa);//记得清空 
	n=read();
	rep1(i,1,2*n) fa[i]=i;
	rep1(i,1,n) rep1(j,1,n) a[i][j]=read();
	//循环以对角线为分割，遍历的下标形成的是一个等腰直角三角形 
	rep1(i,1,n)//外层循环 
	{
		rep1(j,i+1,n)//内层循环 
		{
			if(a[j][i]<a[i][j])//是不是要小点（为了满足字典序最小） 
			{
				if(find(i)==find(j)) continue;//对角线 
				//合并 
				merge(i,j+n);
				merge(i+n,j);
			}
			else if(a[j][i]>a[i][j])
			{
				if(find(i)==find(j+n)||find(i+n)==find(j)) continue;
				if(find(i)==find(j)) continue;//对角线 
				//合并 
				merge(i,j);
				merge(i+n,j+n);
			}
		}
	}
	rep1(i,1,n) rep1(j,i+1,n) if(find(i)==find(j+n)) swap(a[i][j],a[j][i]);//交换操作 
	rep1(i,1,n) //输出 
	{
		rep1(j,1,n) cout<<a[i][j]<<' ';
		putchar('\n');//换行别忘记 
	}
	return;//好习惯 
}
signed main() 
{
	t=read();
	while(t--) getans();//循环要答案 
	return 0;//收场 
}

```

---

