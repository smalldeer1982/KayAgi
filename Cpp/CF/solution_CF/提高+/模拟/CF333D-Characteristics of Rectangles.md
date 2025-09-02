# Characteristics of Rectangles

## 题目描述

Gerald 发现一个 n 行 m 列的表格。作为一个矩形表格的杰出专家，他立刻统计了表格的信息，即表格四个角数字的最小值。但是他并没有满足于最终结果:这个值太小了。为了让它更大，他准备对表格稍加修剪:删除左右的一些列，还有上下的几行。你需要找出在这样修剪后表格上述属性(即四角数字最小值)的最大值。请注意，在修剪后，表格要至少有 2 行 2列。剪去的行和列数目可以为 0。

## 样例 #1

### 输入

```
2 2
1 2
3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 0 0
0 1 1
1 0 0
```

### 输出

```
0
```

# 题解

## 作者：DreamsChaser (赞：4)

$\mathsf{Solution}$

首先这道题要求的是“最小值最大”，考虑到二分。

本题的关键点是：如何判断能否找到一个四个角都 $\ge x$ 的矩形）？

考虑到一种打标记的思路，图示如下（黄色表示 $\ge x$ 的数）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vfgu0bqr.png)

我们依次遍历这张图，例如：

- 遍历到第一行，发现 $\text{1, 2, 4}$ 是黄色，我们将 $(1,2)(1,4)(2,4)$ 打上标记。
- 遍历到第二行，发现 $\text{3, 5}$ 是黄色，我们将 $(3,5)$ 打上标记。
- 遍历到第三行，发现 $\text{5}$ 是黄色，不做处理。
- 遍历到第四行，发现 $\text{1, 4, 5}$ 是黄色，我们将 $(1,4)(1,5)(4,5)$ 打上标记。但 $(1,4)$ 在第一行以打上标记，这就说明：第一行的 $(1,4)$ 与第四行的 $(1,4)$ 均是黄色，那么我们就找到了一个四个角都 $\ge x$ 的矩形。

简单来说：

- 我们遍历所有行
- 将所在行内为黄色的格子两两打上标记
- 如果打标记时找到了打过标记的点，那么就找到了一个四个角都 $\ge x$ 的矩形。
- 否则找不到。

-----

$\mathsf{Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 1010;

int n, m, pla[N], vis[N][N];
LL val[N][N], l, r;

bool check(LL x)
{
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i ++ )
    {
        int tmp = 0;
        for (int j = 1; j <= m; j ++ )
            if (x <= val[i][j])
                pla[ ++ tmp] = j;
		
        for (int j = 1; j <= tmp; j ++ )
            for (int k = 1; k < j; k ++ )
            {
                if (vis[pla[k]][pla[j]]) return true;
                else vis[pla[k]][pla[j]] = 1;
            }
    }
    return false;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
        {
            scanf("%lld", &val[i][j]);
            r = max(r, val[i][j]);
        }
    
    while (l < r)
    {
        LL mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    
    printf("%lld\n", r);
    
    return 0;
}

```

$\huge\mathcal{The\ End}$

---

## 作者：ZLCT (赞：0)

# CF333D Characteristics of Rectangles
## 题目大意
给定一个 $n\times m$ 的矩形。若从其中找一个任意大小的矩形，这个矩形的价值定义为矩形四个角元素的最小值。求子矩形的最大值。
## 由暴力到正解
我们从暴力一步步进行优化。
### 原始暴力
一个最直接的暴力就是分别枚举四个点并判断是否构成矩形，若构成则算一下价值取 $\max$，四个点任意取，复杂度 $O((nm)^4)$。
### 古代暴力
根据初中学习的矩形判定定理中三个角是直角的四边形是矩形，我们可知确定矩形三个点则能确定一个矩形，这样我们就可以少枚举一个点。但是复杂度是 $O((nm)^3)$ 这样一个抽象数字。
### 近代暴力
继续根据上面的定理，我们枚举完第一个点后与他相邻的两个点一定分别在他的同行和同列，这样复杂度就变成了 $O(nm\min(n,m)^2)$。\
在这里还有一种暴力考虑。\
我们考虑一个矩形一定是由两条平行于横坐标轴且起始终止位置相同的线段链接而成的，所以我们在每一行更新时都两两连边，储存到点对 $(x1,x2)$ 中，而一个矩形的上下边肯定来自同一个点对，这样维护复杂度就是 $O(n\binom{m}{2})$。
### 现代方法
关于暴力枚举的探索我们无法继续优化了，于是我们需要从其他角度继续考虑。\
题目要求求最值，而最值就告诉我们可以考虑二分答案，那是否可行呢？\
我们对于一个 $x$，我们可以将 $a_{i,j}\ge x$ 的点涂成黑色，其余涂成白色，这样问题就变成了找到一个四角全黑的矩形。\
这个时候我们还需要暴力去找啊，不还是不行吗？\
这个时候我们回头去看最后一个暴力，我们只储存全涂黑的点对，因为不涂黑的肯定不满足条件。那么如果有一个点对出现了两次，就说明我们找到了一个可行矩形，直接返回即可。\
根据鸽笼原理，$\binom{m}{2}$ 个点对我们最多连 $\binom{m}{2}+1$ 条边就一定能找到一个可行矩形，若不存在合法矩形，则只相当于枚举一遍矩形。所以复杂度就是 $O(\log{V}(\binom{m}{2}+nm))$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,m,ans;
int g[N][N];
bool vis[N][N];
bool check(int x){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i){
        vector<int>vec;
        for(int j=1;j<=m;++j){
            if(g[i][j]>=x)vec.push_back(j);
        }
        for(int j=0;j<vec.size();++j){
            for(int k=j+1;k<vec.size();++k){
                if(vis[vec[j]][vec[k]])return 1;
                vis[vec[j]][vec[k]]=1;
            }
        }
    }
    return 0;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>g[i][j];
        }
    }
    int l=0,r=1e9;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

# 前言

这是一篇玄学的卡常题解，复杂度并不正确但可以通过此题。
# 题意
找到一个长宽均大于二的子矩阵使得四个角的权值的最小值最大。

# 思路

考虑将权值排序后从大到小插入元素，每次判断已插入的元素中是否构成了一个子矩阵，我们可以使用 bitset 维护每一行有哪些已插入元素，每次插入新元素时，枚举每一行，判断这两行的 bitset 与起来元素个数是否大于二即可。

但如果仅仅这样写还无法通过此题，我们注意到插入元素的顺序经过排序过后是比较乱的，所以我们枚举每一行时，判断每一行的**新插入元素的这一列**是否已经插入，若没有就直接 continue，这样剪枝可以通过此题，时间复杂度 $O(\frac{n^4}{\omega})$。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m;
struct node{
	int x,y,w;
	bool operator<(const node &a)const{return w>a.w;}
}a[1000005];
int top;
bitset<1005>t[1005];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			a[++top]={i,j,x};
		}
	}
	sort(a+1,a+1+top);
	for(int i=1;i<=top;i++){
		t[a[i].x][a[i].y]=1;
		if(t[a[i].x].count()<=1)continue;
		for(int j=1;j<=n;j++){
			if(j==a[i].x)continue;
			if(!t[j][a[i].y])continue;//剪枝 
			if((t[a[i].x]&t[j]).count()>=2){
				cout<<a[i].w;
				return 0;
			}
		}
	}
}
```

---

## 作者：WorldMachine (赞：0)

### Solution

最小值最大化，考虑二分答案。

考虑当前二分的是 $x$，我们将所有 $\geq x$ 的元素打上标记，现在唯一的问题就是怎样快速判断是否存在一个四个角都打了标记的矩形。

对于每行，假设第 $j$ 列和第 $k$ 列的元素被打上了标记，则将数对 $(j,k)$ 存下来。之后每行，枚举到 $(j,k)$ 时，如果之前已经有了数对 $(j,k)$，则说明存在一个合法的矩形，直接退出。

由于一共有 $\mathcal O(n^2)$ 个不同的数对，时间复杂度为 $\mathcal O(n^2\log V)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &a) { a = 0; char c = getchar(); bool f = 0; while (c < '0' || c > '9') f |= c == '-', c = getchar(); while (c >= '0' && c <= '9') a = a * 10 - '0' + c, c = getchar(); if (f) a = -a; } struct qread { template <typename T> inline qread& operator>>(T &a) { read(a); return *this; } } qwq;
const int N = 1005;
int n, m, a[N][N], L, R, mid, b[N];
bool v[N][N];
inline bool check(int x) {
	memset(v, 0, sizeof(v));
	for (int i = 1, t; i <= n; i++) {
		t = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i][j] >= x) b[++t] = j;
		}
		for (int j = 1; j <= t; j++) {
			for (int k = 1; k < j; k++) {
				if (v[b[j]][b[k]]) return 1;
				v[b[j]][b[k]] = 1;
			}
		}
	}
	return 0;
}
int main() {
	qwq >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) qwq >> a[i][j], R = max(R, a[i][j]);
	}
	while (L < R) {
		mid = L + R + 1 >> 1;
		if (check(mid)) L = mid;
		else R = mid - 1;
	}
	printf("%d\n", L);
}
```

---

## 作者：small_john (赞：0)

## 思路

神仙题。

首先发现求的是最小值的最大值，容易想到二分。

如何判断是否有一个子矩阵的四个角的最小值大于等于 $k$ 呢？

对于第 $i$ 行，如果 $x,y$ 满足 $a_{i,x}\ge k,a_{i,y}\ge k$ 那就标记数对 $(x,y)$。如果一个数对被标记多次（即在多行出现过）那么就说明存在这样的矩阵。

但这样做判断的时间复杂度是 $O(n^3)$ 的。考虑一有满足条件的数对就退出，由于总共只有 $\frac{n(n-1)}{2}$ 个数对，所以复杂度降为 $O(n^2)$。

最后的时间复杂度为 $O(n^2\log V)$，其中 $V$ 表示值域。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1e3+5;
int n,m,a[N][N],p[N],cnt;
bool vis[N][N];
inline bool ok(int x)
{
	for(int i = 1;i<m;i++)
		for(int j = i+1;j<=m;j++)
			vis[i][j] = 0;
	for(int i = 1;i<=n;i++)
	{
		cnt = 0;
		for(int j = 1;j<=m;j++)
			if(a[i][j]>=x) p[++cnt] = j;
		for(int j = 1;j<cnt;j++)
			for(int k = j+1;k<=cnt;k++)
				if(vis[p[j]][p[k]]) return 1;
				else vis[p[j]][p[k]] = 1;
	}
	return 0;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			read(a[i][j]);
	int l = 0,r = 1e9,res = 0;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(ok(mid)) l = mid+1,res = mid;
		else r = mid-1;
	}
	write(res);
	return 0;
}
```

---

## 作者：MadokaKaname (赞：0)

本文同时发表于个人[博客园](https://www.cnblogs.com/monster-hunter/p/17911810.html)

## 前言

duel 的时候做的题，做出来的时候感觉很神，看了题解做法感觉自己是个傻逼。


本做法时间复杂度是 $O(n^{\tfrac{5}{2}})$，可以作为补充了解。

## 题解

一个矩阵四个角的最大值有点烦，我们把它们排序，从小到大依次插入，则问题变为：

在 $n\times m$ 的平面中，每次插入一个点，求在什么时候会出现一个矩形的四个顶点。

我们发现插入点数并不多，自然想到直接每次暴力向左右扫描。

设插入点数为 $k$，则时间复杂度为 $O(mk)$。

那么插入点数的上界是多少呢？

~~其实我也不会证qaq~~

感谢EI老师 [@Elegia](https://www.luogu.com.cn/user/21423) 给出一篇博客，证明了插入点数的上界是 $O(n\sqrt{n})$，有兴趣的可以在此处阅读。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
struct point{
	LL x,y,val;
}b[1000005];
LL n,i,j,k,m,cnt=0;
LL a[1005][1005];
bool flag[1005][1005];
bool tmp[1005][1005];
LL cmp(point x,point y){
	return x.val>y.val;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
			b[++cnt].val=a[i][j];
			b[cnt].x=i;b[cnt].y=j; 
		}
	}
	sort(b+1,b+cnt+1,cmp);
	for(i=1;i<=cnt;i++){
		flag[b[i].x][b[i].y]=true;
		for(j=1;j<b[i].x;j++)
		  if(flag[j][b[i].y]==true){
		  	if(tmp[j][b[i].x]==true){
		  		printf("%lld",b[i].val);
		  		return 0;
			}
			else{
				tmp[j][b[i].x]=true;
			}
		  } 
		for(j=b[i].x+1;j<=n;j++)
		  if(flag[j][b[i].y]==true){
		  	if(tmp[b[i].x][j]==true){
		  		printf("%lld",b[i].val);
		  		return 0; 
			}
			else{
				tmp[b[i].x][j]=true;
			}
		  }
	}
	return 0;
}
```




---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2100}$
---
### 解题思路：

二分是很明显的，关键是如何快速找出是否存在四个角都大于二分出的答案的矩形。

考虑记录下每一行中所有被可行的点两两组成的点对，如果这一个点对在之前已经被标记过，就表示在之前的某一行中出现了完全一样的点对，也就一定有至少一个满足条件的矩形。

由于最多只有 $O(n^2)$ 个点对会被标记到，所以总复杂度是 $O(n^2\log a)$ 可以接受。

---
### 代码：

```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[1005][1005],s[1005][1005],l,r,mid,ans;
vector <int> v;
int check(int num){
	memset(s,0,sizeof(s));
	for(int i=1;i<=n;i++){
		v.clear();
		
		for(int j=1;j<=m;j++)
		if(a[i][j]>=num)
		v.push_back(j);
		
		for(int j=0;j<v.size();j++)
		for(int k=j+1;k<v.size();k++){
			if(s[v[j]][v[k]]==1)return 1;
			s[v[j]][v[k]]=1;
		}
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&a[i][j]);
		r=max(r,a[i][j]);
	}
	l=0;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
```


---

