# Flag

## 题目描述

Innokenty 在跳蚤市场工作，出售一些稀有物品。最近他发现了一条旧的矩形毯子。结果发现，这条毯子被分成了 $n \times m$ 个有颜色的格子，形成了一个有 $n$ 行 $m$ 列的矩形。

这些彩色的格子引起了 Innokenty 的注意，于是他立刻想出了如下的商业计划：如果他从毯子上裁剪出一个由三条彩色条纹组成的子矩形，他就可以把它当作某个国家的国旗来出售。Innokenty 认为，如果一个子矩形由三条等高、上下排列的条纹组成，并且每条条纹的所有格子颜色相同，那么它就足够像某个国家的国旗。当然，最上面那条条纹的颜色必须与中间那条不同，中间那条的颜色也必须与最下面那条不同。

Innokenty 还没有决定要裁剪哪一部分，但他确定国旗的边界必须沿着网格线，并且不会旋转毯子。请帮助 Innokenty 统计他可以裁剪并出售的不同子矩形的数量。即使两个子矩形形成的国旗完全相同，只要它们的位置不同，也被视为不同的子矩形。

## 说明/提示

下图中选中的子矩形在第一个样例中是合法的国旗。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/05a1643de7735bba2acb4c3894fc0301d9b8432b.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/e8fe611a7e2f3e5dd18a97bf8757649395a7b53d.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3
aaa
bbb
ccb
ddd
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 1
a
a
b
b
c
c
```

### 输出

```
1
```

# 题解

## 作者：cccgift (赞：5)

## 这是一道让我的第一次$CF$赛全盘崩溃的题。

乍一眼看还是比较简单的，统计方案数的题。

首先，维护两个数组$pre1$和$pre2$，其中$pre1$表示点$(x,y)$向下延伸的最长连续相同颜色的个数。

例如样例$2$：

```cpp
6 1
a
a
b
b
c
c
```

那么它的$pre1$数组就是：

```cpp
2
1
2
1
2
1
```

$pre2$数组则表示向右延伸，这两个数组都可以$O(nm)$预处理出来。

接下来，我们可以枚举每一个点$(i,j)$，尝试$O(1)$统计以该点为左上角的$flag$的个数。

那么，假设旗子存在，它的第二个颜色的左上角$x$坐标即为$i+pre1[i][j]$，第三个就为$i+pre1[i][j]*2$。

于是，我们只要考虑$pre1[i+pre1[i][j]]$是否等于$pre1[i][j]$，以及$pre1[i+pre1[i][j]*2]$是否大于等于$pre1[i][j]$即可。（注意，是大于等于！接下来会解释）

最后的问题就是，如何求出$x$在$[i,i+3*pre1[i][j]-1]$中，$pre2[x][j]$的最小值，因为这就是该点对答案的贡献（想想为什么）。

P.S. 我看到有人用暴力出了奇迹，但这种方法毕竟不太可取。

我们把$pre2[i][j]$改一下，改为$x$在$[i,i+pre1[i][j]-1]$中原来$pre2[i][j]$的最小值，那么贡献就是$min(pre2[i][j],pre2[i+pre1[i][j]][j],pre2[i+2*pre1[i][j]][j])$……吗？

### 考虑以下两组数据（这也是把我坑了导致没有$AC$的地方）：

#### 1、

```cpp
4 3
aab
aaa
bbb
ccc
```

#### 2、

```cpp
4 3
aaa
bbb
ccc
cca
```

如此，也就是为什么上面说的大于等于了，因为这样，上面的部分也可以形成答案。

还有，我们要求的是旗子内部的最小值，但是我们求出的$pre2$数组是前缀最小值数组，不保证正确性（上面的$2$即是hack）。

那么考虑维护后缀最小值？

结果上面的$1$就能hack。

最后，我想到了一个解决方法：

同时维护前缀最小值和后缀最小值，在上面的部分就用后缀最小值，在下面的部分就用前缀最小值，中间部分随意，这样就能保证正确性了。

时间复杂度$O(nm)$。

再来一句提醒：别忘了开$longlong$。

### 代码如下：

```cpp
#include<cstdio>
#include<cctype>
#include<utility>
#include<cstring>
#include<algorithm>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
	template<typename T>
	inline void read(T &x)
	{
	    static char ch;bool f=1;
	    for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
	    for(;isdigit(ch);x=(x<<1)+(x<<3)+ch-48,ch=getchar());x=f?x:-x;
	}
	template<typename T>
	inline void print(T x,char ch=0)
	{
		if(!x) {putchar(48);if(ch) putchar(ch);return;}
		if(x<0) putchar('-'),x=-x;
		static int Stack[sizeof(T)*3],top=-1;
		for(;x;Stack[++top]=x%10,x/=10);
		for(;~top;putchar(Stack[top--]+48));
		if(ch) putchar(ch);
	}
	template<typename T>
	inline T max(T x,T y) {return x>y?x:y;}
	template<typename T>
	inline T min(T x,T y) {return x<y?x:y;}
	template<typename T>
	inline void chkmax(T &x,T y) {x=x>y?x:y;return;}
	template<typename T>
	inline void chkmin(T &x,T y) {x=x<y?x:y;return;}
}
using wode::read;using wode::chkmin;using wode::chkmax;
char a[1003][1003];
int pre1[1003][1003],pre2[1003][1003],pre3[1003][1003],n,m;
ll tot;
int main()
{
	scanf("%d%d",&n,&m);
	for(res i=1;i<=n;++i) scanf("%s",a[i]+1);
	for(res i=n;i;--i)
	  for(res j=m;j;--j) {
	  	pre1[i][j]=pre1[i+1][j],pre2[i][j]=pre2[i][j+1];
	  	if(a[i][j+1]==a[i][j]) ++pre2[i][j];else pre2[i][j]=1;
		if(a[i+1][j]==a[i][j]) ++pre1[i][j];else pre1[i][j]=1;
	  }
	for(res i=n-1;i;--i)
	  for(res j=1;j<=m;++j) {
	  	pre3[i][j]=pre2[i][j];
	  	if(a[i+1][j]==a[i][j]) chkmin(pre3[i][j],pre3[i+1][j]);
	  } //这里的pre3就是原来pre2的后缀min
	for(res i=2;i<=n;++i)
	  for(res j=1;j<=m;++j) if(a[i-1][j]==a[i][j]) chkmin(pre2[i][j],pre2[i-1][j]);
	#ifdef cccgift
	for(res i=1;i<=n;++i) {
		for(res j=1;j<=m;++j) printf("%d ",pre1[i][j]);
		puts("");
	}puts("");
	for(res i=1;i<=n;++i) {
		for(res j=1;j<=m;++j) printf("%d ",pre2[i][j]);
		puts("");
	}
	#endif
	for(res i=1;i<=n;++i)
	  for(res j=1;j<=m;++j)
	    if(i+3*pre1[i][j]<=n+1&&pre1[i+pre1[i][j]][j]==pre1[i][j]&&pre1[i][j]<=pre1[i+(pre1[i][j]<<1)][j])
	      tot=tot+wode::min(wode::min(pre3[i][j],pre2[i+3*pre1[i][j]-1][j]),pre2[i+(pre1[i][j]<<1)-1][j]); //处理贡献的部分
	printf("%lld\n",tot); //long long！
    return 0;
}
```

---

## 作者：灵光一闪 (赞：2)

~~这是一道很恶心的题~~

### 注明：此代码是我们机房一个学长写的 ~~（TA马上高中了，我才小学qaq）~~ 我们教练把TA的解法当成了题解来讲 ~~（%%%）~~ 如果网上代码雷同，请不要意外，谢谢

这题可以先把每个字符最下面联通块大小预处理出来（算本身）

例：
```
4 3
123
132
112
333
|
v
311
212
101
111
```
代码实现：
```
for(int i=n;i>=1;i--){//倒着循环，如果不一样就是1，不然就是上一个加1
        for(int j=1;j<=m;j++){
            dp[i][j]=g[i][j]==g[i+1][j]?dp[i+1][j]+1:1;
        }
    }
```
然后就是判断环节：
```
    int cnt;
    for(int i=1;i<=n;i++){
    /*
    讲解一下大概的意思：循环每一个矩形的左上角
    然后判断能否变成“Flag”，如果能，++
    如果发现有两个并一起了，ans++
    最后输出
    */
        cnt=0;
        int pa=-1,pb=-1,pc=-1,pd=-1;
        for(int j=1;j<=m;j++){
            int a=i,b=a+dp[a][j],c=b+dp[b][j],d=c+dp[c][j];
            if(c<=n&&b-a==c-b&&b-a<=d-c){
                if(pc<=n&&pa==a&&pb==b&&pc==c&&pb-pa<=pd-pc&&g[a][j]==g[a][j-1]&&g[b][j]==g[b][j-1]&&g[c][j]==g[c][j-1]){
                    cnt++;
                }
                else{
                    ans+=(cnt*(cnt+1))>>1;
                    cnt=1;
                }
            }
            pa=a;
            pb=b;
            pc=c;
            pd=d;
        }
        ans+=(cnt*(cnt+1))>>1;
    }

```
完整代码来辣！//就不加注释了
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
int n,m,dp[1005][1005];
long long ans;
string g[1005];
string inline readstr(){
    string res;
    char c=getchar();
    for(;!isalpha(c);c=getchar());
    for(;isalpha(c);res+=c,c=getchar());
    return res;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        g[i]=' '+readstr();
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
            dp[i][j]=g[i][j]==g[i+1][j]?dp[i+1][j]+1:1;
        }
    }
    int cnt;
    for(int i=1;i<=n;i++){
        cnt=0;
        int pa=-1,pb=-1,pc=-1,pd=-1;
        for(int j=1;j<=m;j++){
            int a=i,b=a+dp[a][j],c=b+dp[b][j],d=c+dp[c][j];
            if(c<=n&&b-a==c-b&&b-a<=d-c){
                if(pc<=n&&pa==a&&pb==b&&pc==c&&pb-pa<=pd-pc&&g[a][j]==g[a][j-1]&&g[b][j]==g[b][j-1]&&g[c][j]==g[c][j-1]){
                    cnt++;
                }
                else{
                    ans+=(cnt*(cnt+1))>>1;
                    cnt=1;
                }
            }
            pa=a;
            pb=b;
            pc=c;
            pd=d;
        }
        ans+=(cnt*(cnt+1))>>1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Fading (赞：1)

记录一个$sb$做法。

考场上睿智了，求错了区间最值，无限罚时$gg$

设$up[i][j]$表示$(i,j)$可以向上延伸到（只能走颜色相同的点）的最小位置。

$left[i][j]$表示$(i,j)$可以向左延伸到的最小位置与$(i,j)$的距离。

那么思路就显而易见了。

我们枚举子矩阵右下角$(i,j)$，设$pos_1=i,pos_2=up[pos_1][j]-1,pos_3=up[pos_2][j]-1$

有很多无解的情况：

$1:pos_2=0$

$2:pos_3=0$

$3:pos_1-pos_2\not=pos_2-pos_3$

$4:pos_3-up[pos_3][j]+1<pos_1-pos_2$

可以画画图理解一下。。。

显然以$(i,j)$为右下角的“国旗”数量为：

$$\min_{k=pos_3-pos_1+pos_2+1}^{pos_1}left[k][j]$$

直接$ST$表即可，复杂度$O(nmlog_2n)$。

代码细节很多：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,m,a[1021][1021],x[1021][1021][2],f[1021][22];
//0 up,1 left
signed main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            char cc=gc();
            while (!isalpha(cc)) cc=gc();
            a[i][j]=cc-'a'+1;
            if (a[i][j]==a[i-1][j]) x[i][j][0]=x[i-1][j][0];
            else x[i][j][0]=i;
            if (a[i][j]==a[i][j-1]) x[i][j][1]=1+x[i][j-1][1];
            else x[i][j][1]=1;
        }
    }
    ll ans=0;
    for (int j=1;j<=m;j++){
        for (int i=1;i<=n;i++) f[i][0]=x[i][j][1];
        for (int jj=1;jj<=12;jj++){
      		for (int i=1;i<=n-(1<<jj)+1;i++){
        	    f[i][jj]=min(f[i][jj-1],f[i+(1<<jj-1)][jj-1]);
    	    }
    	}
        for (int i=1;i<=n;i++){
            if (i<3&&j<3) continue;
            int pos1=i,pos2=x[pos1][j][0]-1;
            if (pos2==0) continue;//特判1
            int pos3=x[pos2][j][0]-1;
            if (pos3==0) continue;//特判2
            if (pos1-pos2!=pos2-pos3) continue;//特判3
            if (pos3-x[pos3][j][0]+1<pos1-pos2) continue;//特判4
            ll l=pos3-(pos1-pos2)+1,r=pos1;
            ll k=log2(r-l+1);
            ans+=min(f[l][k],f[r-(1<<k)+1][k]);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：蒟酱 (赞：0)

题意：问在一个 $n\times m$ 的平面里有多少旗帜，旗帜的定义是三条宽度相等的带子，相邻的带子颜色不能相同（第一和第三条的颜色可以相同）。

考虑以左上角统计旗帜，预处理每个点向下走遇到颜色不同的点的距离记为 $d=f_{i,j}$，设当前的点颜色为 $a_{i,j}$，那么必须满足 `f[i+d][j]==d&&f[i+2*d][j]>=d&&a[i][j]!=a[i+d][j]&&a[i+d][j]!=a[i+2*d][j]`，`f[i+d][j]==d` 是为了确保第一和第二条的宽度相等，`f[i+2*d][j]>=d` 是为了保证第三条的宽度至少是第一第二条的宽度，至于 `a[i][j]!=a[i+d][j]&&a[i+d][j]!=a[i+2*d][j]` 是为了保证第一和第二条，第二和第三条的颜色不同。  
现在只是确定了向下的方向，固定左上角的点，第二第三条的颜色与宽度是确定的，但是向右延申的距离是不知道的，比如这个（蓝粉白粉蓝）：
```
BBBBBBBBBB
PPPPPPPPPP
WWWWWWWWWW
PPPPPPPPPP
BBBBBBBBBB
```
在枚举到 $(1,1)$ 这个点时，已经确定每条的高度是 $1$ 并且颜色是 $\text{B,P,W}$ 但是没法快速统计出右边能延申几个，不妨把贡献挂在右边的节点上，比如 $(1,1)$ 的贡献是 $1$，$(1,2)$ 的贡献是 $2$，$(1,3)$ 的贡献是 $3$，这样就很好办了。  
记录往下是否可行为条件 $1$，和左边是否一样为条件 $2$，因为要枚举每个点，先枚举行，在枚举列时记录一个 $k$，如果不满足条件 $1$ 那么 $k=0$，否则进行判断，如果这三带和前面那一带一模一样，也就是 `f[i][j-1]==d&&f[i+d][j-1]==d&&f[i+2*d][j-1]>=d&&a[i][j-1]==a[i][j]&&a[i+d][j-1]==a[i+d][j]&&a[i+2*d][j-1]==a[i+2*d][j]` 那么就 $k=k+1$，否则 $k=1$，执行完操作后 $ans=ans+k$ 就行了。

代码：
```cpp
//不向焦虑与抑郁投降，这个世界终会有我们存在的地方。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<tuple>
#include<ctime>
#include<random>
using std::cin;using std::cout;
using loli=long long;
constexpr int N=1002;
int n,m,f[N][N];
char a[N][N];
loli ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=n;i>=1;i--)for(int j=1;j<=m;j++)
		if(a[i][j]==a[i+1][j])f[i][j]=f[i+1][j]+1;else f[i][j]=1;
	for(int i=1;i<=n;i++)for(int j=1,k=0;j<=m;j++){
		int d=f[i][j];
		if(i+3*d-1<=n&&f[i+d][j]==d&&f[i+2*d][j]>=d&&a[i][j]!=a[i+d][j]&&a[i+d][j]!=a[i+2*d][j]){
			if(f[i][j-1]==d&&f[i+d][j-1]==d&&f[i+2*d][j-1]>=d&&a[i][j-1]==a[i][j]&&a[i+d][j-1]==a[i+d][j]&&a[i+2*d][j-1]==a[i+2*d][j])
				k++;
			else k=1;
		}else k=0;
		ans+=k;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：0)

## 题解：CF1181C Flag

### 题意简述

现在你有一个 $n\times m$ 的矩形，你需要计算其中能够由自上而下三条横向的相邻颜色带颜色不同且宽度相等的颜色带组成的子矩形数量。

### 解题思路

记点 $(i , j)$ 的颜色为 $c_{i , j}$。

对于每个点 $(i , j)$，记 $d_{i , j}$ 为下方有连续多少点的颜色和 $c_{i , j}$ 相同，记 $r_{i , j}$ 为右侧有连续多少点的颜色和 $c_{i , j}$ 相同。

下图是例子：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/68iyhy0n.png)

- 若 $d_{i , j} = d_{i + d_{i , j} , j} \le d_{i + 2 \times d_{i , j} , j}$，则点 $(i , j)$ 对答案的贡献为 $\min(r_{i , j} , r_{i + 1 , j} \dots r_{i + 2 \times d_{i , j} , j})$。由上面的生成方式可得，此式子的答案 $\ge 1$。
- 否则，点 $(i , j)$ 对答案的贡献为 $0$。

此时，最劣复杂度 $O(n^3)$，难以通过。

开 $m$ 棵线段树，每一棵维护每列中 $\min(r_{i , j} , r_{i + 1 , j} \dots r_{i + 2 \times d_{i , j} , j})$ 的大小即可。

复杂度 $O(n^2 \log n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , m , ans , qzhd[1005][1005] , qzhr[1005][1005];
char c[1005][1005];
struct node
{
	int l , r , tag;
};
struct xds
{
	node tree[4005];
	inline void build(int p , int q , int l , int r)
	{
		tree[p].l = l;
		tree[p].r = r;
		if(l == r)
		{
			tree[p].tag = qzhr[l][q];
			return;
		}
		int mid = (l + r) / 2;
		build(p * 2 , q , l , mid);
		build(p * 2 + 1 , q , mid + 1 , r);
		tree[p].tag = min(tree[p * 2].tag , tree[p * 2 + 1].tag);
		return;
	}
	inline int query(int p , int l , int r)
	{
		if(l <= tree[p].l && tree[p].r <= r)
		{
			return tree[p].tag;
		}
		int cnt = 1000000007;
		if(tree[p * 2].r >= l)
		{
			cnt = min(cnt , query(p * 2 , l , r));
		}
		if(tree[p * 2 + 1].l <= r)
		{
			cnt = min(cnt , query(p * 2 + 1 , l , r));
		}
		return cnt;
	}
}xds[1005];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> c[i][j];
		}
	}
	for(int i = n ; i >= 1 ; i--)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			if(c[i][j] == c[i + 1][j])
			{
				qzhd[i][j] = qzhd[i + 1][j] + 1;
				continue;
			}
			qzhd[i][j] = 1;
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = m ; j >= 1 ; j--)
		{
			if(c[i][j] == c[i][j + 1])
			{
				qzhr[i][j] = qzhr[i][j + 1] + 1;
				continue;
			}
			qzhr[i][j] = 1;
		}
	}
	for(int i = 1 ; i <= m ; i++)
	{
		xds[i].build(1 , i , 1 , n);
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			if(qzhd[i][j] * 2 > n)
			{
				continue;
			}
			if(qzhd[i][j] != qzhd[i + qzhd[i][j]][j])
			{
				continue;
			}
			if(qzhd[i][j] > qzhd[i + qzhd[i][j] * 2][j])
			{
				continue;
			}
			ans += xds[j].query(1 , i , i + qzhd[i][j] * 3 - 1);
		}
	}
	cout << ans;
	return 0;
}
```

---

