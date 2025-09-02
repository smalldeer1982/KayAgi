# JOIOI 王国 (Kingdom of JOIOI)

## 题目描述

JOIOI 王国是一个 $H$ 行 $W$ 列的长方形网格，每个 $1 \times 1$ 的子网格都是一个正方形的小**区块**。为了提高管理效率，我们决定把整个国家划分成两个省 JOI 和 IOI。

我们定义，两个同省的区块**互相连接**，意为从一个区块出发，不用穿过任何一个不同省的区块，就可以移动到另一个区块。有公共边的区块间可以任意移动。

我们不希望划分得过于复杂，因此划分方案需满足以下条件：

- 区块不能被分割为两半，一半属 JOI 省，一半属 IOI 省。
- 每个省必须包含至少一个区块，每个区块也必须属于且只属于其中一个省。
- 同省的任意两个小区块互相连接。
- 对于每一行/列，如果我们将这一行/列单独取出，这一行/列里同省的任意两个区块互相连接。这一行/列内的所有区块可以全部属于一个省。

现给出所有区块的海拔，第 $i$ 行第 $j$ 列的区块的海拔为 $A_{i,j}$ 。设 JOI 省内各区块海拔的极差（最大值减去最小值）为 $R_{JOI}$，IOI 省内各区块海拔的极差为 $R_{IOI}$ 。在划分后，省内的交流有望更加活跃。但如果两个区块的海拔差太大，两地间的交通会很不方便。 因此，理想的划分方案是 $\max(R_{JOI},R_{IOI})$ 尽可能小。

你的任务是求出 $\max(R_{JOI},R_{IOI})$ 至少为多大。

## 说明/提示

对于 $15\%$ 的数据，$H,W \leqslant 10$。

对于另外 $45\%$ 的数据，$H,W \leqslant 200$。

对于所有数据，$2 \leqslant H,W \leqslant 2000,A_{i,j} \leqslant 10^9$（$1 \leqslant i \leqslant H,1 \leqslant j \leqslant W$）。

## 样例 #1

### 输入

```
4 4
1 12 6 11
11 10 2 14
10 1 9 20
4 17 19 10```

### 输出

```
11```

## 样例 #2

### 输入

```
8 6
23 23 10 11 16 21
15 26 19 28 19 20
25 26 28 16 15 11
11 8 19 11 15 24
14 19 15 14 24 11
10 8 11 7 6 14
23 5 19 23 17 17
18 11 21 14 20 16```

### 输出

```
18```

# 题解

## 作者：Melon_Musk (赞：4)

## [题目链接](https://www.luogu.com.cn/problem/AT2444)

## 思路

由题意得我们的答案一定是类似于这样的形状的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/twmdeyyn.png)

此时我们注意到题目要求的是个最大值最小，我们可以往二分答案的思路去思考。

如果一个比较显然的想法就是把最大值和最小值放在不同的两块，一边全是比较大的数，一边全是比较小的数，这样的话我们要求的极差会更小，我们令全图最大值为 $mx$，最小值为 $mn$。

假设我们二分了一个题目要求的答案 $max(R_{JOI},R_{IOI})$，即左右两边的极差的最大值，设当前二分在 $mid$ 这个值。

以上图为例，令左下红色区域是较大的那个块，那么它的每个值都应该在 $mx-mid$ 到 $mx$ 之间，则右上蓝色区域的值域为 $mn$ 到 $mn+mid$。

所以值小于 $mx-mid$ 的点不能被划分到红色区域，大于 $mn+mid$ 的点不能被划分到蓝色区域。就是说我们要找一条单调不升或者单调不降的点使得这两种点被分开，我们思考什么时候方案不可行。

回到上图，令小于 $mx-mid$ 的是黄色点，只能被分到蓝色区域，大于 $mx-mid$ 的是绿色点，只能被分到绿色区域。那么显然这是一个合法的方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/5u7bot8r.png)![](https://cdn.luogu.com.cn/upload/image_hosting/t8zagpg3.png)

这两个都是合法答案，如图的红蓝切分即为一种方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/78xmk6zh.png)

这不是合法方案，因为有个黄色点在红色区域，且我们没有办法使得它被划在蓝色区域，不然的话旁边的绿色点也会到在蓝色区域，所以不合法。

思考怎么用代码实现。

我们对绿色和黄色的分别找一个划分线，使得从左下开始到划分线内包含了所有的绿点而且要试包含的空间最小，黄点同理。然后我们直接看一下是否有重合就行。

![](https://cdn.luogu.com.cn/upload/image_hosting/y8z93bhl.png)

rt，两条红蓝线。此时他们有重合，所以不合法。

在代码中的实现就是从上到下求一个下表的前缀最大值（红线）和一个从下到上的区间最小值（蓝线）。

然后题目其实有 $4$ 种可能的划分，分别是（即红色区域在矩形的四个脚的方案（蓝色区域反正就在它对面））：

![](https://cdn.luogu.com.cn/upload/image_hosting/twmdeyyn.png)![](https://cdn.luogu.com.cn/upload/image_hosting/yz6xe1mu.png)![](https://cdn.luogu.com.cn/upload/image_hosting/lomo95lm.png)![](https://cdn.luogu.com.cn/upload/image_hosting/w6dadnke.png)

分别做一遍就行了，和这个区别不大，不再赘述，想要理解可以自行看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e4+7;
const ll inf=1e14; 
#define int long long
ll read() 
{
	ll res=0,f=1;
	char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-48,c=getchar();
	return res*f;
}
int n,m;
ll mn,mx;
ll a[maxn][maxn];
ll Mx[maxn],Mn[maxn];
bool check(ll mid)
{
	Mx[n+1]=-inf;Mn[0]=inf; bool bl=1;
	for(int i=1;i<=n;i++) { Mn[i]=Mn[i-1]; for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) Mn[i]=min(Mn[i],j);}
	for(int i=n;i;i--)    { Mx[i]=Mx[i+1]; for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) Mx[i]=max(Mx[i],j); if(Mx[i]>=Mn[i]) bl=0;}
	if(bl) return 1;
	
	bl=1;
	for(int i=1;i<=n;i++) { Mn[i]=Mn[i-1]; for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) Mn[i]=min(Mn[i],j);}
	for(int i=n;i;i--)    { Mx[i]=Mx[i+1]; for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) Mx[i]=max(Mx[i],j); if(Mx[i]>=Mn[i]) bl=0;}
	if(bl) return 1;
	
	Mx[0]=-inf;Mn[n+1]=inf; bl=1;
	for(int i=1;i<=n;i++) { Mx[i]=Mx[i-1]; for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) Mx[i]=max(Mx[i],j);}
	for(int i=n;i;i--)    { Mn[i]=Mn[i+1]; for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) Mn[i]=min(Mn[i],j); if(Mx[i]>=Mn[i]) bl=0;}
	if(bl) return 1;
	
	bl=1;
	for(int i=1;i<=n;i++) { Mx[i]=Mx[i-1]; for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) Mx[i]=max(Mx[i],j);}
	for(int i=n;i;i--)    { Mn[i]=Mn[i+1]; for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) Mn[i]=min(Mn[i],j); if(Mx[i]>=Mn[i]) bl=0;}
	if(bl) return 1;
	
	return 0;
}
signed main()
{
	n=read(),m=read();
	mx=-inf,mn=inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			mx=max(mx,a[i][j]);
			mn=min(mn,a[i][j]);
		} 
	ll l=0,r=mx-mn,ans;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid;
	} 
	printf("%lld\n",ans);
	return 0;
}
  
```


---

## 作者：Peter0701 (赞：4)

给定 $H \times W$ 的网格，每个小格（ $1 \times 1$ 的网格）都有一个权值。

现在要将其分为两部分，一个为阶梯型（从上往下每行长度单调递增）、另一个为倒阶梯型（从下往上每行长度单调递增）。请合理地划分这个网格使得两边极差（该部分最大值 $-$ 最小值）较大的一个最小。输出较大的极差。

注意关键词。“较大的一个最小” $\rightarrow$ “最大值最小”！

二分答案，出来吧！

显然，我们二分那个较大的极差，二分左边界是 $0$ ，右边界是全局最大值 $maxn$ 与全局最小值 $minn$ 的差。那么 $check()$ 函数怎么写呢？

假设当前二分到的答案是 $mid$ 。显然我们可以钦定全局最大值在左边一部分，全局最小值在右边一部分。那么将所有符合 $mid$ 极差（即 $maxn-x \leqslant mid$ ）的数 $x$ 全都分到左边，注意保留倒阶梯型（左边部分每行的长度依次递减）；而右边的数 $x$ 只要不符合 $mid$ 极差（即 $x-minn \leqslant mid$ ）答案就显然不成立。

当然，钦定全局最大值在左边一部分，全局最小值在右边一部分的答案不一定是最优的。我们还应当将原图 $90 \degree $ 旋转 $3$ 次分别按上面的步骤解答一次，更新答案。

整个过程就是这样，如果还没明白或者觉得需要证明的，评论区见！感谢您的耐心阅读！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
const int inf=1<<30;
int h,w,a[2005][2005],minn=inf,maxn=-inf,ans=inf;
inline bool ck(int mid)
{
	int f=w+1;
	for(register int i=1;i<=h;i++)
	{
		int t=0;
		for(register int j=1;j<=min(f,w);j++)
		{
			if(maxn-a[i][j]<=mid)
				t=max(t,j);
			else
				break;
		}
		f=t;
		for(register int j=t+1;j<=w;j++)
			if(a[i][j]-minn>mid)
				return 0;
	}
	return 1;
}
inline int work()
{
	int l=0,r=maxn-minn+1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(ck(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}
inline void turn1()
{
	for(register int i=1;i<=h;i++)
		for(register int j=1;j<=w/2;j++)
			swap(a[i][j],a[i][w-j+1]);
}
inline void turn2()
{
	for(register int i=1;i<=h/2;i++)
		for(register int j=1;j<=w;j++)
			swap(a[i][j],a[h-i+1][j]);
}
int main()
{
	h=read();
	w=read();
	for(register int i=1;i<=h;i++)
	{
		for(register int j=1;j<=w;j++)
		{
			a[i][j]=read();
			maxn=max(maxn,a[i][j]);
			minn=min(minn,a[i][j]);
		}
	}
	ans=min(ans,work());
	turn1();
	ans=min(ans,work());
	turn2();
	ans=min(ans,work());
	turn1();
	ans=min(ans,work());
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：chenxia25 (赞：3)

**[Portal](https://www.luogu.com.cn/problem/AT2444)**

这题并不是很难，但却是我所看了题解的题………………

最大值最小，一眼二分。check 的时候就看是否能够 JOI 和 IOI 的极差都 $\leq x$。

这个 JOIOI 的分布条件显然等价于，就是每行是前缀是 JOI，后缀是 IOI，然后每行的前缀长度要单调（增或减）。我们考虑枚举 JOI 部分的最小值（$\mathrm O\!\left(n^2\right)$），然后把那些 $\in[mn,mn+x]$ 的都给整合起来，然后搞出每行的最长前缀。这是个 two-pointers，显然每个位置只会被先加入后删除一遍，实时维护每行的最长前缀，如果删除位置在前面就把当前行最长前缀移到前面去，如果加入那就暴力往后拓展。这样易证每个位置只会被访问常数次，于是维护每行的最长前缀是平方的。

但是我们对于每组最长前缀，还需要算剩下的 IOI 是否可以极差 $\leq x$ 啊。我们可以搞出右上角矩形和右下角矩形的最值数组，那么显然 IOI 的最值就是每行最长前缀右边的上 / 下面的最值最起来。这个当一行的最长前缀改变的时候，需要用 `set` 维护，多一个 log。那么总的就是 2log，不行了。

于是我便去看题解了，发现一个性质（可能我大多数次看题解都是发现不了性质，然后看了题解就恍然大悟了吧）。我们考虑整个 $a$ 数组的最小值，它显然不分布在 JOI 就在 IOI。我们从它入手，如果某省里面有它的话，就不用枚举最小值了，那就傻子都会了。于是我们考虑枚举最小值在 JOI / IOI，每种还要分成单调增和减两种情况，一共四种情况，每种随便搞出当前省的包含最多元素的状态，然后随便算一下就可以了。

复杂度平方对数，**_[code](https://www.luogu.com.cn/paste/bu3cc0ne)_**。

---

## 作者：哈撒各一 (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT2444)

首先我们来看一个简单的例子：

```
1   2
100 111
```
那么很显然我们会把（1,2）划分在一起，（100,111）划分在一起。

我们在看一个例子：

```
1   100
101 102
```

我们也可以很轻易地把 $（1）$ 划分在一起， $（100,101,102）$ 划分在一起。

在我们手模上诉例子的过程中，我们可以发现我们人类在划分的时候总是想把小的划到一个省里，大的划到一个省里。

为什么会有这样的想法呢？

首先我们知道一个性质：每一个区域一定会在一个省里。

我们令三个区域的值分别为 $a,b,c$ ，满足 $a<b<c$ 。

那么此时我们把 $b，c$ 或把 $a，b$ 划分到一个区域一定是比把 $a，c$划分到一个区域更优的。

那么我们可以得出一个结论：为了让答案更优，我们要尽量让大的值与小的值分开。

所以我们可以想到一个贪心策略：每一次安排最大值和最小值，然后按照这些已经安排了的值划分区域，直到没有办法让最小值与最大值分开，那么此时就是答案。

而且我们发现省份的分布情况是大致趋近对角线的，所以我们只需要枚举小省在哪个角落，大省在另一个角落即可。

如果不明白可以手模一下样例。

可以发现在这样的操作过后，一定会出现以下两种情况：

**1.我这次要选择的点在另一个省内。**

**2.所有的点都按照需要选完了，没有冲突。**

那么对于这两种情况，答案分别是：

**1.这个点的点权-这个省的极值。**

**2.两个省分别极值的最大值。**

时间复杂度$O(n^2logn^2)$ 。

如果还不明白，就看代码吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2020
#define PII pair<int,int>
int n,m,a[N][N],used[N][N],ans[4];
int mx[4]={1,-1,0,0},my[4]={0,0,1,-1};
struct Node{
	int val,x,y;
	Node(){}
	Node(int a,int b,int c){
		val=a;x=b;y=c;
	}
}num[N*N];
inline bool operator <(Node A,Node B){
	return A.val<B.val;
}
inline int read(){
	int x=0,f=1;char op=getchar();
	while(!isdigit(op)){if(op=='-')f=-1;op=getchar();}
	while(isdigit(op)){x=(x<<1)+(x<<3)+(op^48);op=getchar();}
	return x*f;
}
queue<PII> q;
void bfs(int x,int y,int m1,int m2,int type){
	m1--;m2--;
	q.push(make_pair(x,y));
	while(!q.empty()){
		PII u=q.front();q.pop();
		if(used[u.first][u.second])continue;
		used[u.first][u.second]=type;
		int nx=u.first+mx[m1],ny=u.second+my[m1];
		if(!used[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m)q.push(make_pair(nx,ny));
		nx=u.first+mx[m2],ny=u.second+my[m2];
		if(!used[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m)q.push(make_pair(nx,ny));
	}
}
int main(){
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	//ios::sync_with_stdio(false);
	//cin.tie(0),cout.tie(0);
	n=read();m=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			a[i][j]=read();
			num[(i-1)*m+j]=Node(a[i][j],i,j);
		}
	}
	sort(num+1,num+n*m+1);
	{
		int it1=1,it2=n*m;
		memset(used,0,sizeof(used));
		while(it1<it2){
			if(num[it1].val-num[1].val<num[n*m].val-num[it2].val){
				if(used[num[it1].x][num[it1].y]==2){
					ans[0]=num[n*m].val-num[it1].val;
					break;
				}
				bfs(num[it1].x,num[it1].y,2,4,1);
				it1++;
			}else{
				if(used[num[it2].x][num[it2].y]==1){
					ans[0]=num[it2].val-num[1].val;
					break;
				}
				bfs(num[it2].x,num[it2].y,1,3,2);
				it2--;
			}
		}
		if(!ans[0])ans[0]=min(num[n*m].val-num[it1].val,num[it2].val-num[1].val);
	}
	{
		int it1=1,it2=n*m;
		memset(used,0,sizeof(used));
		while(it1<it2){
			if(num[it1].val-num[1].val<num[n*m].val-num[it2].val){
				if(used[num[it1].x][num[it1].y]==2){
					ans[1]=num[n*m].val-num[it1].val;
					break;
				}
				bfs(num[it1].x,num[it1].y,1,4,1);
				it1++;
			}else{
				if(used[num[it2].x][num[it2].y]==1){
					ans[1]=num[it2].val-num[1].val;
					break;
				}
				bfs(num[it2].x,num[it2].y,2,3,2);
				it2--;
			}
		}
		if(!ans[1])ans[1]=min(num[n*m].val-num[it1].val,num[it2].val-num[1].val);
	}
	{
		int it1=1,it2=n*m;
		memset(used,0,sizeof(used));
		while(it1<it2){
			if(num[it1].val-num[1].val<num[n*m].val-num[it2].val){
				if(used[num[it1].x][num[it1].y]==2){
					ans[2]=num[n*m].val-num[it1].val;
					break;
				}
				bfs(num[it1].x,num[it1].y,2,3,1);
				it1++;
			}else{
				if(used[num[it2].x][num[it2].y]==1){
					ans[2]=num[it2].val-num[1].val;
					break;
				}
				bfs(num[it2].x,num[it2].y,1,4,2);
				it2--;
			}
		}
		if(!ans[2])ans[2]=min(num[n*m].val-num[it1].val,num[it2].val-num[1].val);
	}
	{
		int it1=1,it2=n*m;
		memset(used,0,sizeof(used));
		while(it1<it2){
			if(num[it1].val-num[1].val<num[n*m].val-num[it2].val){
				if(used[num[it1].x][num[it1].y]==2){
					ans[3]=num[n*m].val-num[it1].val;
					break;
				}
				bfs(num[it1].x,num[it1].y,1,3,1);
				it1++;
			}else{
				if(used[num[it2].x][num[it2].y]==1){
					ans[3]=num[it2].val-num[1].val;
					break;
				}
				bfs(num[it2].x,num[it2].y,2,4,2);
				it2--;
			}
		}
		if(!ans[3])ans[3]=min(num[n*m].val-num[it1].val,num[it2].val-num[1].val);
	}
	cout<<min(min(ans[0],ans[1]),min(ans[2],ans[3]))<<endl;
	return 0;
}
```


---

## 作者：Aaplloo (赞：2)

## 题目
[戳这](https://www.luogu.com.cn/problem/AT2444)

## 思路
首先，根据题意，假设所选取的某一个省图像必须为一个阶梯状，这样才能符合横竖中没有被岔开的。

因为要求是最大的值最小，很显然，可以进行二分答案。

对图中的方差，得到最大值和最小值，答案的方差一定会是在0 ~ max - min 的范围内。那么分别就设定了l 和 r， mid就是二分的答案。

那么，怎么验证这个mid是否合法呢？这里，我们划分的图像为不上升的阶梯。假设前一个阶梯划分的位置为x，并且最大值会在被划分的这个阶梯里，那么如果当前阶梯的max - 任意元素 <= mid 并且 另一阶梯的任意元素 - min <= mid.那么当前阶梯的划分位置是在0-x的，当前阶梯的划分位置应该在哪里呢？因为我们不但要满足当前阶梯满足max - 任意元素 <= mid， 并且另一个阶梯应该满足 任意元素 - min <= mid，发现当满足当前阶梯时，尽量多的选取一定会让另一个阶梯更容易被满足。所以当前阶梯的划分位置要尽可能大。

这样得到一个答案后，并不一定是最小的。为什么呢？因为答案的划分可能是左右或上下的不上升或不下降的。一开始我们只得到了一种情况的最优解，这时候我们还需要进行3次旋转，分别求解取最优的。

## code:
~~~cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 2005
#define LL long long
#define INF 0x3f3f3f3f
#define Int register int
inline void read(int &x)
{
	x = 0;
	int f = 1;
	char s = getchar();
	while (s < '0' || s > '9')
	{
		if (s == '-')
			f = -1;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 3) + (x << 1) + (s ^ 48);
		s = getchar();
	}
	x *= f;
}
int Max(int x,int y)
{
	return x > y ? x : y;
}
int Min(int x,int y)
{
	return x < y ? x : y;
}
int a[MAXN][MAXN], h, w;
void Swap(int &x,int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
void Turnh()
{
	for (Int i = 1; i <= h; ++ i)
		for (Int j = 1; j <= w / 2; ++ j)
			Swap(a[i][j], a[i][w - j + 1]);
}
void Turnw()
{
	for (Int i = 1; i <= h / 2; ++ i)
		for (Int j = 1; j <= w; ++ j)
			Swap(a[i][j], a[h - i + 1][j]);
}
int Ans = INF;
int Maxx = 0, Minn = INF;
bool Check(int x)
{
	int Pre = w + 1;
	for (Int i = 1; i <= h; ++ i)
	{
		int Mid = 0;
		for (Int j = 1; j <= Min(Pre, w); ++ j)
		{
			if (Maxx - a[i][j] <= x)
				Mid = Max(Mid, j);
			else break;
		}
		Pre = Mid;
		for (Int j = Mid + 1; j <= w; ++ j)
			if (a[i][j] - Minn > x)
				return 0;
	}
	return 1;
}
int main()
{
	read( h ); read( w );
	for (Int i = 1; i <= h; ++ i)
		for (Int j = 1; j <= w; ++ j)
		{
			read( a[i][j] );
			Maxx = Max(Maxx, a[i][j]);
			Minn = Min(Minn, a[i][j]);
		}
	int l = 0, r = Maxx - Minn;
	while (l <= r)
	{
		int Mid = l + r >> 1;
		if (Check( Mid ))
			 r = Mid - 1;
		else l = Mid + 1;
	}
	Ans = Min(Ans, l);
	Turnh();
	l = 0, r = Maxx - Minn;
	while (l <= r)
	{
		int Mid = l + r >> 1;
		if (Check( Mid ))
			 r = Mid - 1;
		else l = Mid + 1;
	}
	Ans = Min(Ans, l);
	Turnw();
	l = 0, r = Maxx - Minn;
	while (l <= r)
	{
		int Mid = l + r >> 1;
		if (Check( Mid ))
			 r = Mid - 1;
		else l = Mid + 1;
	}
	Ans = Min(Ans, l);
	Turnh();
	l = 0, r = Maxx - Minn;
	while (l <= r)
	{
		int Mid = l + r >> 1;
		if (Check( Mid ))
			 r = Mid - 1;
		else l = Mid + 1;
	}
	Ans = Min(Ans, l);
	printf("%d\n", Ans);
	return 0;
}
~~~


---

## 作者：嘉然小姐的狗 (赞：1)

提供一个 $O(n^2 \log n)$ 的解法。

首先划分的方式在其他题解里已经提到了，就是类似于下面的形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/blqrr4pd.png)

由于所有区块都必须被划分，因此那个最大的区块也一定会被划分到某个省去；所以**必定有一个省的最大值为全局最大值**。

根据这一点，我们可以钦定包含左上角 $(1, 1)$ 的 IOI 省为这个包含全局最大值的省，然后从大到小枚举 IOI 省的最小值，不断拓展 IOI 省的边界；相对地，JOI 省的面积也会越来越小。我们可以用优先队列在 $O(n^2 \log n)$ 时间内维护这个过程。

当然，包含全局最大值的省也可能在左下角或是别的位置，因此我们需要把矩阵旋转或翻转多次统计答案。

时间复杂度：$O(n^2 \log n)$。

---

当然，在 OI 通常时限内，这一做法和 $O(n^2 \log a_i)$ 的二分做法只有常数倍的常数差异，是难以卡过后面那个算法的。比起这个复杂度来说，还是**必定有一个省的最大值为全局最大值**这个想法比较有趣一些。

---

## 作者：封禁用户 (赞：1)

# 题目
__题目描述__

$JOIOI$王国是一个$h$行$w$列的长方形网格，每个  的子网格都是一个正方形的小区块。为了提高管理效率，我们决定把整个国家划分成两个省$JOI$和$IOI$。

我们定义，两个同省的区块互相连接，意为从一个区块出发，不用穿过任何一个不同省的区块，就可以移动到另一个区块。有公共边的区块间可以任意移动。

我们不希望划分得过于复杂，因此划分方案需满足以下条件：

- 区块不能被分割为两半，一半属$JOI$省，一半属$IOI$省。
- 每个省必须包含至少一个区块，每个区块也必须属于且只属于其中一个省。
- 同省的任意两个小区块互相连接。
- 对于每一行/列，如果我们将这一行/列单独取出，这一行/列里同省的任意两个区块互相连接。这一行/列内的所有区块可以全部属于一个省。

现给出所有区块的海拔，第$i$行第$j$列的区块的海拔为$a_{ij}$。设$JOI$省内各区块海拔的极差（最大值减去最小值）为$R_{_{JOI}}$，$IOI$省内各区块海拔的极差为$R_{_{IOI}}$。在划分后，省内的交流有望更加活跃。但如果两个区块的海拔差太大，两地间的交通会很不方便。 因此，理想的划分方案是$D=\max(R_{_{JOI}},R_{_{IOI}})$尽可能小。

你的任务是求出$D$至少为多大。

__输入输出格式__

`输入格式：`
第一行，两个整数$h,w$，用空格分隔。

在接下来的$h$行中，第$i$行有$w$个整数$a_{i1},a_{i2},a_{i3},\dots,a_{iw}$，用空格分隔。

输入的所有数的含义见题目描述。

`输出格式：`
一行，一个整数，表示$D$可能的最小值。
# 思路
直接将某个角落作为一个省，至少有$\max_a-\min_a$的答案。

不妨设$\max_a\in JOI,\min_a\in IOI$（否则一定不优）。

此时我们就要$\min_a\in JOI$最大。__最小值最大__？二分答案$\min JOI$。

写成奇怪格式：（就是值域啦）

$$JOI:[x,\max_a]$$

$$IOI:[\min_a,\min_a+(\max_a-x)]$$

$IOI$的最大值之所以是那个玩意儿，是因为这样的取值不会影响答案——$D=\max_a-x$。

如何判断是否可行？$\Bbb{DP}$扫描一遍就是了！

根据题意，发现可能的方案其实很少，应该是如图所示的样子——

![在这里插入图片描述](https://img-blog.csdnimg.cn/20191130104116735.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQyMTAxNjk0,size_16,color_FFFFFF,t_70)

没错，每一行都有清晰的分界线，并且分界线一定是不断右移（或左移）的。每一行的分界线左边隶属于同一个州。读者自证不难。

所以用$f(x,y,0/1/2)$表示前$x$行，第$x$行的分界线是$y$（即，左边的$y$个属于同一个州），分界线曾经有这样的案底：$1$左移、$2$右移、$0$没移。

转移也很简单。记得用上二分的值的判断！

# 代码
代码实现有个技巧——将列翻转，再跑一遍$\Bbb{DP}$。

这样就枚举了分界线左边是$JOI$和右边是$JOI$的情况。

一个州是否有区块不需要判断。有总比没有好。

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
inline int readint(){
	int a = 0, f = 1; char c = getchar();
	for(; c<'0' or c>'9'; c=getchar())
		if(c == '-') f = -1;
	for(; '0'<=c and c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(long long x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) writeint(x/10);
	putchar(x%10+'0');
}

const int MaxN = 2005;
int a[MaxN][MaxN], h, w, max_a, min_a = (1<<30)-1;

void input(){
	h = readint(), w = readint();
	for(int i=1; i<=h; ++i)
		for(int j=1; j<=w; ++j){
			a[i][j] = readint();
			if(max_a < a[i][j])
				max_a = a[i][j];
			if(a[i][j] < min_a)
				min_a = a[i][j];
		}
}

bool dp[MaxN][MaxN][3];
// joi的最右边一个区块在哪里 
// 0:没推 1:左推 2:右推 
bool check(int x,int y){
	for(int i=1; i<=h; ++i){
		for(int j=0; j<=w; ++j)
			dp[i][j][0] = dp[i-1][j][0];
		for(int j=0; j<=w; ++j){
			dp[i][j][2] = dp[i-1][j][2] or dp[i-1][j][0];
			if(j) dp[i][j][2] = dp[i][j][2] or dp[i][j-1][2];
		}
		for(int j=w; ~j; --j){
			dp[i][j][1] = dp[i-1][j][1] or dp[i-1][j][0];
			if(j != w) dp[i][j][1] = dp[i][j][1] or dp[i][j+1][1];
		}
		bool f = true; // 检查[x,max_a] 
		for(int j=1; j<=w; ++j){
			f = f and a[i][j] >= x;
			dp[i][j][0] = f and dp[i][j][0];
			dp[i][j][1] = f and dp[i][j][1];
			dp[i][j][2] = f and dp[i][j][2];
		}
		f = true; // 检查[min_a,y] 
		for(int j=w-1; ~j; --j){
			f = f and a[i][j+1] <= y;
			dp[i][j][0] = f and dp[i][j][0];
			dp[i][j][1] = f and dp[i][j][1];
			dp[i][j][2] = f and dp[i][j][2];
		}
// 这里本来可以剪枝，但是优化效果可能不大，就没打 
// 如果本行dp数组已经全部为false，就return false 
	}
	for(int j=0; j<=w; ++j)
		if(dp[h][j][0] or dp[h][j][1] or dp[h][j][2])
			return true;
	return false;
}
void solve(){
	for(int j=0; j<=w; ++j)
		dp[0][j][0] = true; // 初始化 
	int ans = max_a-min_a; // 至多是这么大 
	int L = min_a, R = max_a;
	while(L != R){
		int mid = (L+R+1)>>1;
		if(check(mid,min_a+max_a-mid)) L = mid;
		else R = mid-1;
	}
	ans = min(ans,max_a-L);
	for(int i=1; i<=h; ++i) // 列翻转！ 
		for(int j=1; j<w+1-j; ++j)
			swap(a[i][j],a[i][w+1-j]);
	L = min_a, R = max_a; // do it again ~ 
	while(L != R){
		int mid = (L+R+1)>>1;
		if(check(mid,min_a+max_a-mid)) L = mid;
		else R = mid-1;
	}
	ans = min(ans,max_a-L);
	writeint(ans), putchar('\n');
}

int main(){
	input(), solve();
	return 0;
}
```

---

## 作者：kouylan (赞：0)

这里提供一种除读入外理论复杂度 $O(n\log^2n)$，~~写起来比 $n^2\log n$ 还慢~~的一种方法。

首先，这个题的划分的 border 只会有以下四种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/5w64x6l0.png)

我们可以二分答案，然后贪心的定 border，假设我们先看 $J$ 块，那它肯定越大越好，所以每一行/列的 border 不仅在整个矩阵上具有单调性，内部也符合单调性，所以定每一列/行的 border 都可以二分得到。

但这样依旧会被卡，所以对于每种情况，我们正着跑一遍，再反着跑一遍即可。（有点乱搞内味儿了）

所以计算的复杂度是 $8n\log^2n$ 的。

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int n,m,a[2005][2005],ans,bor[2005];
int mxc1[2005][2005],mxc2[2005][2005],mnc1[2005][2005],mnc2[2005][2005];
int mxl1[2005][2005],mxl2[2005][2005],mnl1[2005][2005],mnl2[2005][2005];

bool check(int lim)
{
	for(int j=0;j<=m;j++) bor[j] = 1;
	int mx=mxc2[1][1],mn=mnc2[1][1];
	for(int j=2;j<=m;j++)
	{
		int l=bor[j-1],r=n,p=n+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxc2[j][mid]),mnn=min(mn,mnc2[j][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[j] = p;
		mx = max(mx,mxc2[j][p]), mn = min(mn,mnc2[j][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int j=1;j<=m;j++)
			mx = max(mx,mxc1[j][bor[j]-1]), mn = min(mn,mnc1[j][bor[j]-1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int j=0;j<=m;j++) bor[j] = n;
	mx = mxc1[1][n], mn = mnc1[1][n];
	for(int j=2;j<=m;j++)
	{
		int l=1,r=bor[j-1],p=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxc1[j][mid]),mnn=min(mn,mnc1[j][mid]);
			if(mxx-mnn<=lim)
				p = mid, l = mid+1;
			else
				r = mid-1; 
		}
		bor[j] = p;
		mx = max(mx,mxc1[j][p]), mn = min(mn,mnc1[j][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int j=1;j<=m;j++)
			mx = max(mx,mxc2[j][bor[j]+1]), mn = min(mn,mnc2[j][bor[j]+1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int i=0;i<=n;i++) bor[i] = 1;
	mx = mxl2[1][1], mn = mnl2[1][1];
	for(int i=2;i<=n;i++)
	{
		int l=bor[i-1],r=m,p=m+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxl2[i][mid]),mnn=min(mn,mnl2[i][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[i] = p;
		mx = max(mx,mxl2[i][p]), mn = min(mn,mnl2[i][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int i=1;i<=n;i++)
			mx = max(mx,mxl1[i][bor[i]-1]), mn = min(mn,mnl1[i][bor[i]-1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int i=0;i<=n;i++) bor[i] = m;
	mx = mxl1[1][m], mn = mnl1[1][m];
	for(int i=2;i<=n;i++)
	{
		int l=1,r=bor[i-1],p=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxl1[i][mid]),mnn=min(mn,mnl1[i][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[i] = p;
		mx = max(mx,mxl1[i][p]), mn = min(mn,mnl1[i][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int i=1;i<=n;i++)
			mx = max(mx,mxl2[i][bor[i]+1]), mn = min(mn,mnl2[i][bor[i]+1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int j=0;j<=m;j++) bor[j] = 1;
	mx = mxc2[m][1], mn = mnc2[m][1];
	for(int j=m-1;j>=1;j--)
	{
		int l=bor[j+1],r=n,p=n+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxc2[j][mid]),mnn=min(mn,mnc2[j][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[j] = p;
		mx = max(mx,mxc2[j][p]), mn = min(mn,mnc2[j][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int j=1;j<=m;j++)
			mx = max(mx,mxc1[j][bor[j]-1]), mn = min(mn,mnc1[j][bor[j]-1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int j=0;j<=m;j++) bor[j] = n;
	mx = mxc1[m][n], mn = mnc1[m][n];
	for(int j=m-1;j>=1;j--)
	{
		int l=1,r=bor[j+1],p=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxc1[j][mid]),mnn=min(mn,mnc1[j][mid]);
			if(mxx-mnn<=lim)
				p = mid, l = mid+1;
			else
				r = mid-1; 
		}
		bor[j] = p;
		mx = max(mx,mxc1[j][p]), mn = min(mn,mnc1[j][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int j=1;j<=m;j++)
			mx = max(mx,mxc2[j][bor[j]+1]), mn = min(mn,mnc2[j][bor[j]+1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int i=0;i<=n;i++) bor[i] = 1;
	mx = mxl2[n][1], mn = mnl2[n][1];
	for(int i=n-1;i>=1;i--)
	{
		int l=bor[i+1],r=m,p=m+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxl2[i][mid]),mnn=min(mn,mnl2[i][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[i] = p;
		mx = max(mx,mxl2[i][p]), mn = min(mn,mnl2[i][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int i=1;i<=n;i++)
			mx = max(mx,mxl1[i][bor[i]-1]), mn = min(mn,mnl1[i][bor[i]-1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	for(int i=0;i<=n;i++) bor[i] = m;
	mx = mxl1[n][m], mn = mnl1[n][m];
	for(int i=n-1;i>=1;i--)
	{
		int l=1,r=bor[i+1],p=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int mxx=max(mx,mxl1[i][mid]),mnn=min(mn,mnl1[i][mid]);
			if(mxx-mnn<=lim)
				p = mid, r = mid-1;
			else
				l = mid+1; 
		}
		bor[i] = p;
		mx = max(mx,mxl1[i][p]), mn = min(mn,mnl1[i][p]);
	}
	if(mx-mn<=lim)
	{
		mx = 0, mn = INF;
		for(int i=1;i<=n;i++)
			mx = max(mx,mxl2[i][bor[i]+1]), mn = min(mn,mnl2[i][bor[i]+1]);
//		cout<<mx<<' '<<mn<<endl;for(int i=1;i<=n;i++)cout<<bor[i]<<' ';cout<<endl; //
		if(mx-mn<=lim)
			return 1;
	}
	return 0;
}

int main()
{
//	freopen("joioi.in","r",stdin);
//	freopen("joioi.out","w",stdout);
	scanf("%d%d",&n,&m);
	int mxx=0,mnn=INF;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]), mxx = max(mxx,a[i][j]), mnn = min(mnn,a[i][j]);
	memset(mnc1,INF,sizeof(mnc1)), memset(mnc2,INF,sizeof(mnc2));
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
			mxc1[j][i] = max(mxc1[j][i-1],a[i][j]), mnc1[j][i] = min(mnc1[j][i-1],a[i][j]);
		for(int i=n;i>=1;i--)
			mxc2[j][i] = max(mxc2[j][i+1],a[i][j]), mnc2[j][i] = min(mnc2[j][i+1],a[i][j]);
	}
	memset(mnl1,INF,sizeof(mnl1)), memset(mnl2,INF,sizeof(mnl2));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			mxl1[i][j] = max(mxl1[i][j-1],a[i][j]), mnl1[i][j] = min(mnl1[i][j-1],a[i][j]);
		for(int j=m;j>=1;j--)
			mxl2[i][j] = max(mxl2[i][j+1],a[i][j]), mnl2[i][j] = min(mnl2[i][j+1],a[i][j]);
	}
	int l=0,r=mxx-mnn;
	while(l<=r)
	{
		int mid=(l+r)>>1;
//		cout<<"# "<<mid<<endl; //
		if(check(mid))
			ans = mid, r = mid-1;
		else
			l = mid+1;
	}
	printf("%d\n",ans);
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：tzc_wk (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/AT2444)

记 $mxi$ 为 IOI 国海拔的最大值，$mni$ 为 IOI 国海拔的最小值，$mxj$ 为 JOI 国海拔的最大值，$mnj$ 为 JOI 国海拔的最小值。

不难发现 $mxi,mni,mxj,mnj$ 中有 2 个值已经确定下来了，$\max(mxi,mxj)$ 一定等于矩阵的全局最大值 $mx$，$\min(mni,mnj)$ 一定等于矩阵的全局最小值 $mn$。

如果我们把海拔最高和最低的点分配到了同一个国家中，答案即为 $mx-mn$。

如果我们把海拔最高和最低的点分配到了不同的国家中，我们不妨假设海拔最高的点分配到了 JOI 国，海拔最低的点分配到了 IOI 国。

二分答案。

假设二分到 $mid$，那么所有 IOI 国的城市的海拔 $\leq mn+mid$，所有 JOI 国的城市的海拔 $\geq mx-mid$。

也就是所有海拔 $>mn+mid$ 的城市全部属于 JOI 国，所有海拔 $<mx-mid$ 的城市全部属于 IOI 国。

此时题目转化为：已知某些点属于 IOI 国，某些点属于 JOI 国，判断是否存在一种合法的分配方案。

根据题意两国的地形一定呈阶梯分部。所以可以分出四种情况，这里以 JOI 国占据左上角，IOI 国占据右下角为例。

考虑第 $i$ 两国之间的分界线 $b_i$，那么一定有 $b_i \leq b_{i-1}$，而第 $i$ 行 $b_i$ 左边肯定都是 JOI 国的城市，第 $i$ 行右边肯定都是 IOI 国的城市，根据这个你可以求出 $b_i$ 的最大值和最小值，然后判断是否有交集即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e3+5;
int n,m,a[MAXN][MAXN],mx=0,mn=0x3f3f3f3f;
int l[MAXN],r[MAXN];
bool check(int mid){
	memset(l,0,sizeof(l));memset(r,0,sizeof(r));r[0]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) l[i]=max(l[i],j);
	for(int i=n;i;i--) l[i]=max(l[i],l[i+1]);
	for(int i=1;i<=n;i++) r[i]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) r[i]=min(r[i],j);
	for(int i=1;i<=n;i++) r[i]=min(r[i-1],r[i]);
	bool flg=1;for(int i=1;i<=n;i++) flg&=(l[i]<r[i]);if(flg) return 1;
	memset(l,0,sizeof(l));memset(r,0,sizeof(r));r[n+1]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) l[i]=max(l[i],j);
	for(int i=1;i<=n;i++) l[i]=max(l[i],l[i-1]);
	for(int i=1;i<=n;i++) r[i]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) r[i]=min(r[i],j);
	for(int i=n;i;i--) r[i]=min(r[i+1],r[i]);
	flg=1;for(int i=1;i<=n;i++) flg&=(l[i]<r[i]);if(flg) return 1;
	memset(l,0,sizeof(l));memset(r,0,sizeof(r));r[0]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) l[i]=max(l[i],j);
	for(int i=n;i;i--) l[i]=max(l[i],l[i+1]);
	for(int i=1;i<=n;i++) r[i]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) r[i]=min(r[i],j);
	for(int i=1;i<=n;i++) r[i]=min(r[i-1],r[i]);
	flg=1;for(int i=1;i<=n;i++) flg&=(l[i]<r[i]);if(flg) return 1;
	memset(l,0,sizeof(l));memset(r,0,sizeof(r));r[n+1]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]<mx-mid) l[i]=max(l[i],j);
	for(int i=1;i<=n;i++) l[i]=max(l[i],l[i-1]);
	for(int i=1;i<=n;i++) r[i]=m+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]>mn+mid) r[i]=min(r[i],j);
	for(int i=n;i;i--) r[i]=min(r[i+1],r[i]);
	flg=1;for(int i=1;i<=n;i++) flg&=(l[i]<r[i]);if(flg) return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) mx=max(mx,a[i][j]),mn=min(mn,a[i][j]);
	int l=0,r=mx-mn-1,ans=mx-mn;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	} printf("%d\n",ans);
	return 0;
}
```

---

