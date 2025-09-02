# Counting Rectangles

## 题目描述

You have $ n $ rectangles, the $ i $ -th rectangle has height $ h_i $ and width $ w_i $ .

You are asked $ q $ queries of the form $ h_s \ w_s \ h_b \ w_b $ .

For each query output, the total area of rectangles you own that can fit a rectangle of height $ h_s $ and width $ w_s $ while also fitting in a rectangle of height $ h_b $ and width $ w_b $ . In other words, print $ \sum h_i \cdot w_i $ for $ i $ such that $ h_s < h_i < h_b $ and $ w_s < w_i < w_b $ .

Please note, that if two rectangles have the same height or the same width, then they cannot fit inside each other. Also note that you cannot rotate rectangles.

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722E/eea41631a59a3be709b240003a8697e693220564.png)In the first test case, there is only one query. We need to find the sum of areas of all rectangles that can fit a $ 1 \times 1 $ rectangle inside of it and fit into a $ 3 \times 4 $ rectangle.

Only the $ 2 \times 3 $ rectangle works, because $ 1 < 2 $ (comparing heights) and $ 1 < 3 $ (comparing widths), so the $ 1 \times 1 $ rectangle fits inside, and $ 2 < 3 $ (comparing heights) and $ 3 < 4 $ (comparing widths), so it fits inside the $ 3 \times 4 $ rectangle. The $ 3 \times 2 $ rectangle is too tall to fit in a $ 3 \times 4 $ rectangle. The total area is $ 2 \cdot 3 = 6 $ .

## 样例 #1

### 输入

```
3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000```

### 输出

```
6
41
9
0
54
4
2993004```

# 题解

## 作者：ScottSuperb (赞：17)

# 解法分析
使用二位前缀和解决此题。使用一个二维数组 $s$ 记录前缀和，每读入一个矩形的 $h$ 和 $w$ 就在对应位置加上它的面积，即执行 $s_{h, w}\gets s_{h, w}+ h\times w$，读入完后计算一遍前缀和。对于每个询问，由于 $h_{s}<h_{i}<h_{b}$ 且 $w_{s}<w_{i}<w_{b}$，计算 $s_{hs+1, ws+1}$ 到 $s_{hb-1, wb-1}$ 的值，即 $s_{hb - 1, wb - 1}- s_{hb - 1, ws}- s_{hs, wb - 1}+ s_{hs, ws}$。
# 代码
快读快输函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll s[1005][1005];

int main() {
	int t = read(), n, q, h, w, hs, ws, hb, wb;
	while (t--) {
		n = read(), q = read();
		for (int i = 1; i <= 1000; ++i)
			for (int j = 1; j <= 1000; ++j)
				s[i][j] = 0;
		while (n--)
			h = read(), w = read(), s[h][w] += h * w;
		for (int i = 1; i <= 1000; ++i)
			for (int j = 1; j <= 1000; ++j)
				s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		while (q--)
			hs = read(), ws = read(), hb = read(), wb = read(), write(s[hb - 1][wb - 1] - s[hb - 1][ws] - s[hs][wb - 1] + s[hs][ws]);
	}
	return 0;
}
```

---

## 作者：Zvelig1205 (赞：6)

# CF1722E Counting Rectangles 题解报告

## 前言

先吐槽一下这个翻译，写得这短小精悍……

多亏了有 dalao @yangshiyu10 的帮助。

## 题意

给定 $n$ 个矩阵，$q$ 次询问。

每次给定四个整数 $h_s,w_s,h_b,w_b$，长在 $(h_s,h_b)$，宽在 $(w_s,w_b)$ 之间的所有矩阵的面积之和。

## 题解

长和宽都是长度，很容易想到权值线段树。

但是有两个限制区间，有很容易想到树套树。

那么就可以用 **权值线段树套权值线段树** 来解决这道题。

第一维权值树维护 $h$，第二维权值树维护 $w$。

每次在一维线段树单点修改，对应一维线段树的 $\log n$ 个节点。

而一维线段树的每个节点，又对应这一棵二维线段树。

二维线段树的单点修改，又对应其 $\log n$ 个节点。

故每次单点修改时间复杂度为 $O(n\log^2n)$。

而区间查询，同样是 $O(n\log^2n)$ 的。

至于细节实现，看代码吧：

```cpp
#include<cstdio>
#include<cstring>
#define int long long//题干明确说明要开 long long
using namespace std;
int re()
{
	int s=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		s=s*10+ch-48,ch=getchar();
	return s*f;
}
void wr(int s)
{
	if(s<0)putchar('-'),s=-s;
	if(s>9)wr(s/10);
	putchar(s%10+48);
}
const int inf=1e3+7;
int qwq,n,m;
struct Segment_Tree{//第二维
	struct Seg_Tree{
		int lc,rc;
		int sum;//权值和
	}T[inf*inf*10];
	int cnt;//习惯性动态开点
	void insert(int &i,int l,int r,int h,int w)
	{//单点修改
		if(i==0)i=++cnt;
		if(l==r)
		{
			T[i].sum+=h*w;//面积和
			return;
		}
		int mid=(l+r)>>1;
		if(w<=mid)insert(T[i].lc,l,mid,h,w);
		else insert(T[i].rc,mid+1,r,h,w);
		T[i].sum=T[T[i].lc].sum+T[T[i].rc].sum;
	}
	int ask(int i,int l,int r,int x,int y)
	{//区间查询
		if(i==0)return 0;
		if(x<=l&&r<=y)return T[i].sum;
		int mid=(l+r)>>1,ans=0;
		if(x<=mid)ans+=ask(T[i].lc,l,mid,x,y);
		if(mid<y)ans+=ask(T[i].rc,mid+1,r,x,y);
		return ans;
	}
}xds;
int rot[inf*10];//第一维
void insert(int i,int l,int r,int h,int w)
{//单点修改
	xds.insert(rot[i],1,1000,h,w);//修改 log n 个节点
	if(l==r)return;
	int mid=(l+r)>>1;
	if(h<=mid)insert(i<<1,l,mid,h,w);
	else insert(i<<1|1,mid+1,r,h,w);
}
int ask(int i,int l,int r,int x,int y,int wx,int wy)
{//区间查询
	if(x<=l&&r<=y)return xds.ask(rot[i],1,1000,wx,wy);
	int mid=(l+r)>>1,ans=0;
	if(x<=mid)ans+=ask(i<<1,l,mid,x,y,wx,wy);
	if(mid<y)ans+=ask(i<<1|1,mid+1,r,x,y,wx,wy);
	return ans;
}
signed main()
{
	qwq=re();
	while(qwq--)
	{//多测清空
		memset(rot,0,sizeof(rot));
		memset(xds.T,0,sizeof(xds.T));
		n=re();m=re();
		for(int i=1;i<=n;i++)
		{//单点修改
			int h=re(),w=re();
			insert(1,1,1000,h,w);
		}
		for(int i=1;i<=m;i++)
		{//区间查询，记得是开区间
			int hs=re(),ws=re(),hb=re(),wb=re();
			wr(ask(1,1,1000,hs+1,hb-1,ws+1,wb-1)),putchar('\n');
		}
	}
	return 0;
}
```

## 后记

关于树套树的博客，小蒟蒻还没开始写，等写完之后再打广告吧（雾。

今年 NOIp 之后就要退役了，多写点东西纪念一下我活在过这个世上。

今年欢笑复明年，不知退役在眼前。

哎。

---

## 作者：lihanwen12 (赞：5)

题目大意：  
有 $n$ 个矩形，第 $i$ 个矩形的高度为 $h_i$，宽度为 $w_i$。  
有 $q$ 个询问，每一个询问表示为 $h_s,w_s,h_b,w_b$。  
对于每一个询问，你需要输出所有满足条件 $h_s<h_i<h_b$ 和 $w_s<w_i<w_b$ 的矩形面积之和。  

解题思路：  
赛时没有注意到此题给的时间限制为 $6$ 秒，用二维前缀和可以解决，当时直接想着用可持久化线段树能做。首先将所有矩形以高度为关键字从小到大排序，这样对于每一个询问我们可以二分查找出满足 $h_s<h_i$ 的最小的 $i$ 记为 $L$，满足 $h_i<h_b$ 的最大的 $i$ 记为 $R$。构造 $n$ 棵权值线段树，第 $j$ 棵权值线段树表示前 $j$ 个矩形中，在某个宽度区间内出现的矩形面积之和是多少。为了满足 $w_s<w_i<w_b$，查询权值线段树的宽度区间为 $[w_s+1,w_b-1]$。根据前缀和思想，每一个询问的答案就是第 $R$ 棵权值线段树中 $[w_s+1,w_b-1]$ 的面积和减去第 $L-1$ 棵权值线段树中 $[w_s+1,w_b-1]$ 的面积和。时间复杂度为 $O(n\times \log(n)+n\times \log(1000)+q\times \log(n)+q\times \log(1000))=O((n+q)\times (\log(n)+\log(1000)))$。  

代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}

struct node{
	long long  h,w,s;
}a[100010];
bool cmp(node x,node y){
	return x.h<y.h;
}
long long t,n,q,l,r,mid,L,R,ans,Hs,Ws,Hb,Wb,tot,root[100010];
long long lson[4000010],rson[4000010],sum[4000010];
long long build(long long l,long long r){
	tot++;
	if(l==r)return tot;
	int save=tot;
	lson[save]=build(l,(l+r)/2);
	rson[save]=build((l+r)/2+1,r);
	sum[save]=0;
	return save;
}
long long insert(long long i,long long l,long long r,long long now,long long f){
	tot++;
	int save=tot;
	lson[tot]=lson[i];
	rson[tot]=rson[i];
	sum[tot]=sum[i]+f;
	if(l==r)return save;
	if(now<=(l+r)/2)
		lson[tot]=insert(lson[i],l,(l+r)/2,now,f);
	else
		rson[tot]=insert(rson[i],(l+r)/2+1,r,now,f);
	return save;
}
void ask(long long x,long long y,long long l,long long r,long long L,long long R){
	if(L<=r && R>=l){//有交集 
		if(L<=l && R>=r){//完全覆盖 
			ans+=sum[y]-sum[x];
			return;
		}
		ask(lson[x],lson[y],l,(l+r)/2,L,R);
		ask(rson[x],rson[y],(l+r)/2+1,r,L,R);
	}
	
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i].h>>a[i].w;
			a[i].s=a[i].h*a[i].w;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=tot;i++){
			lson[i]=0;
			rson[i]=0;
			sum[i]=0;
		}
		tot=0;
		root[0]=build(1,1000);
		for(int i=1;i<=n;i++)
			root[i]=insert(root[i-1],1,1000,a[i].w,a[i].s);
		for(int i=1;i<=q;i++){
			cin>>Hs>>Ws>>Hb>>Wb;
			L=-1;
			R=-1;
			l=1;r=n;
			while(l<=r){
				mid=(l+r)/2;
				if(a[mid].h<=Hs)l=mid+1;
				else{
					L=mid;
					r=mid-1;
				}
			}
			l=1;r=n;
			while(l<=r){
				mid=(l+r)/2;
				if(a[mid].h>=Hb)r=mid-1;
				else{
					R=mid;
					l=mid+1;
				}
			}
			if(L==-1 || R==-1){//根本就塞不进去 
				cout<<0<<endl;
				continue;
			}
			ans=0;
			ask(root[L-1],root[R],1,1000,Ws+1,Wb-1);
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Lantrol (赞：5)

### 题目描述

分别给定 $n$ 个正整数 $h_i,w_i$，有 $q$ 次询问。

对于每次询问，输入四个整数 $h_s,w_s,h_b,w_b$，输出满足 $h_i \in (h_s,h_b),w_i\in(w_s,w_b)$ 的 $\sum h_i \cdot w_i$ 。

### 思路

不难想到 $O(nq)$ 的暴力，每次询问扫一遍统计答案。

考虑怎么优化。

注意到 $h_i,w_i≤1000$，可以用 $O(hw)$ 预处理出的二维前缀和（前缀和数组存的是 $(1,1)$ 到 $(x,y)$ 中，所有的 $h_i\cdot w_i$ 之和），然后每次询问时 $O(1)$ 出答案。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,q;
long long juz[1005][1005];
void solve(){
	memset(juz,0,sizeof(juz));
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int h,w;
		cin>>h>>w;
		juz[h][w]+=h*w;
	}
	for(int i=1;i<=1000;i++){
		for(int j=1;j<=1000;j++){
			juz[i][j]+=juz[i-1][j]+juz[i][j-1]-juz[i-1][j-1];
		}
	}
	while(q--){
		int xs,ys,xb,yb;
		cin>>xs>>ys>>xb>>yb;
		xs++;ys++;xb--;yb--;
		cout<<juz[xb][yb]-juz[xs-1][yb]-juz[xb][ys-1]+juz[xs-1][ys-1]<<endl;
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```


---

## 作者：EXODUS (赞：3)

# Part 1：前言
~~场上数组开小了啊啊啊啊啊，为啥不报 RE 啊啊啊啊啊啊~~

因为看题解都是二维前缀和，所以来补充个二维数点。

# Part 2：正文

问题可以转化为在二维平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(h_i,w_i)$，求在矩形 $(h_s,w_s,h_b,w_b)$ 中点的个数（不包括边缘）。

显然二维数点，对横坐标进行排序，树状数组维护对应纵坐标上点的个数，枚举横坐标，每次扫到点就在对应纵坐标位置加 $1$，扫到询问的左端就在答案上减去区间 $(w_s,w_b)$ 的点的个数，扫到询问的右端就在答案上加上区间 $(w_s,w_b)$ 的点的个数，思想类似于前缀和，~~由于这里不是扫描线模板，~~ 不过多赘述，不懂的可以去学习一下。

这里简单提下我的实现，在扫描时，按照 **询问右端点-点-询问左端点** 的顺序进行处理，就可以达到询问开区间的效果，这点~~读者自证不难~~（真的很简单啊qwq）。

时间复杂度 $O(q\log V)$，其中 $V$ 是 $h$ 的值域。

# Part 3：代码
```cpp
bool DataS=1,FilE=0;
int T;
void init(){
	return;
}
const int N=1e3+7,M=1e5+7;
struct point{
	int h,w1,w2,id;
}p[M<<2];
bool cmp(point x,point y){
	return x.h==y.h?x.id<y.id:x.h<y.h;
}
ll arr[N];
ll ans[M];
int n,q;
void add(int x,int v){for(int i=x;i<=1000;i+=lowbit(i))arr[i]+=v;}
ll ask(int x){ll res=0;for(int i=x;i;i-=lowbit(i))res+=arr[i];return res;}
ll query(int l,int r){return ask(r-1)-ask(l);}
signed main(){
	if(FilE){
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	}
	T=(DataS?read():1);
	while(T--){
		init();
		n=read();q=read();memset(arr,0,sizeof(arr));
		for(int i=1;i<=n;i++){
			p[i].h=read();p[i].w1=read();p[i].w2=0,p[i].id=0;
		}
		for(int i=1;i<=q;i++){
			p[n+i].h=read(),
			p[n+i].w1=read();
			p[n+q+i].w1=p[n+i].w1;
			p[n+i].id=i;
			p[n+q+i].h=read(),
			p[n+q+i].w2=read();
			p[n+i].w2=p[n+q+i].w2;
			p[n+q+i].id=-i;
		}
		sort(p+1,p+2*q+n+1,cmp);
		for(int i=1;i<=n+2*q;i++){
			if(p[i].id==0)add(p[i].w1,p[i].h*p[i].w1);
			else if(p[i].id>0){
				ans[p[i].id]-=query(p[i].w1,p[i].w2);
			}
			else{
				ans[-p[i].id]+=query(p[i].w1,p[i].w2);
			}
		}
		for(int i=1;i<=q;i++){
			printf("%lld\n",ans[i]);ans[i]=0;
		}
	}
	return 0;
}
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：luo_shen (赞：0)

**题意**  
每次给定 $n$ 个点 $(x_i,y_i)$，其权值为 $x_i\times y_i$，共有 $q$ 次询问，每次给出 $x_s,y_s,x_t,y_t$，求在左上角顶点坐标为 $(x_s+1,y_s+1)$，右下角顶点坐标为 $(x_t-1,y_t-1)$ 的矩形中所有点的权值之和。  
**解析**  
非常典型的一个二维前缀和和差分求平面上一个矩形内权值之和的题。

常用公式（公式均用于整点上的前缀和和差分）：
- 二维前缀和通用公式:
$$d_{ij}=d_{{i-1}j}+d_{i{j-1}}-d_{{i-1}{j-1}}+w_{ij}$$
其中 $w_{ij}$ 表示点 $(i,j)$ 上的权值。
- 二维差分通用公式：
$$ans=d_{x_1y_1}-d_{x_1{y_0-1}}-d_{{x_0-1}y_1}+d_{{x_0-1}{y_0-1}}$$
其中 $(x_0,y_0)$ 表示矩形上横纵坐标均最小的顶点，$(x_1,y_1)$ 表示矩形上横纵坐标均最大的顶点。  
注：记得开`long long`。  
**Code**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,d[1010][1010],t;
signed main(){
    // freopen("1.out","w",stdout);
    cin>>t;
    while(t--){
        cin>>n>>q;
        for(int i=1;i<=1000;i++){
            for(int j=1;j<=1000;j++){
                d[i][j]=0;
            }
        }//虽然这题memset并不会有什么事，但最好不要用，尽量手动清零
        int x,y;
        for(int i=1;i<=n;i++){
            cin>>x>>y;
            d[x][y]+=x*y;//记录每个位置的权值之和
        }
        for(int i=1;i<=1000;i++){
            for(int j=1;j<=1000;j++){
                d[i][j]=d[i][j]+d[i-1][j]+d[i][j-1]-d[i-1][j-1];
            }
        }//统计前缀和
        int xs,xt,ys,yt;
        while(q--){
            cin>>xs>>ys>>xt>>yt;
            cout<<d[xt-1][yt-1]-d[xt-1][ys]-d[xs][yt-1]+d[xs][ys]<<endl;//计算矩形内权值的差分结果
        }
    }
    return 0;
}
```

---

## 作者：hayzxjr (赞：0)

### 题意简述

给出 $n$ 个矩阵的长 $h_i$ 和宽 $w_i$。然后给出 $q$ 组询问，每组包含四个正整数 $h_s,w_s,h_b,w_b$，求 $\sum h_i\cdot w_i$，其中 $h_s<h_i<h_b,w_s<w_i<w_b$。

### 题目分析

（下文中涉及数学符号可能使用不规范，但意对即可。）

将 $h_s, w_s$ 和 $h_b,w_b$ 分别构造成两个矩形 $S$ 和 $B$，根据数据范围可以得出 $S\subseteq B$，我们要求的是所有满足 $s\subseteq I \subseteq B$ 的矩形 $I$ 的面积总和。

显然暴力枚举是通过不了的，我们考虑将矩形 $S,I,B$ 的左上角对齐进行分析。

我们设 $m_{i,j}$ 表示点 $(0,0),(0,i),(0,j),(i,j)$ 四个点构成的矩形区域中真包含的所有矩形面积和。

（在下文中我们为书写方便，将上一行中四个点组成的矩形记作 $R_{i,j}$，不规范但能看懂就好。）

那么首先就能在输入时将 $m_{i,j}$ 加上目前输入的矩形面积。（注意是加上而不是赋值，要考虑两个完全相同的矩形。）

那么便可以用 **二维前缀和** 的方式进行计算，可得如下式子：
$$
m'_{i,j}=m_{i,j}+m_{i-1,j}+m_{i,j-1}-m_{i-1,j-1}
$$
其中 $m'$ 表示 $m_{i,j}$ 新的值，即编程中的赋值后的数。

那么为什么这个式子成立呢？

首先我们知道，若 $i>p,j>q$，那么 $R_{p,q}$ 能被 $R_{i,j}$ 完全包含（即真包含），那么 $R_{p,q}$ 能完全包含的矩形 $R_{i,j}$ 也一定能包含，所以 $m'_{i,j}=m_{i,j}+m_{i-1,j}+m_{i,j-1}$ 便明确了。

那么为什么要减去 $m_{i-1,j-1}$ 呢？

我们可以这么想，将 $m_{p,q}$ 分成 $R_{p-1,q}$ **就能** 包含的矩形面积 与 有了第 $p$ 行 **才能** 包含的矩形面积之和。我们容易发现这两部分是不相交的且覆盖了所有情况。同样地，也可分成 $R_{p,q-1}$ **就能** 包含的矩形面积 与 有了第 $q$ 列 **才能** 包含的矩形面积之和。

于是，我们将 $m_{i-1,j}$ 和 $m_{i,j-1}$ 都如此分解，会发现重合部分 $m_{i-1,j-1}$ 所以便可以减去。这是 **容斥原理**，也是二维前缀和实现的重要基础，这样，我们便只剩下最后一部分了。

在上面的推导中，我们的 $m_{i,j}$ 始终是包含而不是真包含（两者的差距我们暂且看作真包含不能边界重合）。而根据数据都是整数，并且我们有整数集中的这样一个式子：若 $x,y\in\mathbb{Z},x<y$，则 $x+1\leq y$。

所以既然 $m_{i,j}$ 是包含，那么 $m_{i-1,j-1}$ 一定是 $R_{i,j}$ 的真包含。然而还没结束，因为我们还得解决一个被包含的关系。

也使用容斥，我们将现在的答案减去能被 $R_{h_s,w_s}$ **包含** 的矩形面积（这里因为边界重合不能算进答案，于是可以一起减去）。

但仔细想想还会发现，有一部分不能被 $R_{h_w,w_s}$ 包含但还在答案里。这是什么？

其实是因为这些矩形有一条边和 $R_{h_s,w_s}$ 其中一条边所在直线重合，但另一条边却很长，就不能被 $R_{h_s,w_s}$ 包含，这部分我们直接从下面的式子中看：
$$
ans_{R_{h_s,w_s},R_{h_b,w_b}} = m_{h_b-1,w_b-1}-m_{h_s,w_b-1}-m_{h_b-1}{w_s}+m_{h_s,w_s}
$$


### 代码实现

注意多测，记得清空 $m$ 数组。

不开 `ll` 见祖宗。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
#define M 1005
using namespace std;
int t, n, q, h, w;
ll m[M][M], ans;
int h1, w1, h2, w2;
int main()
{
	scanf("%d", &t);
	for(int z = 1; z <= t; z++){
		memset(m, 0, sizeof m);
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; i++){
			scanf("%d%d", &h, &w);
			m[h][w] = m[h][w] + h * w;
		}
		for(int i = 1; i <= M + 2; i++)
		  for(int j = 1; j <= M + 2; j++)
		    m[i][j] = m[i][j] + m[i - 1][j] + m[i][j - 1] - m[i - 1][j - 1];
		for(int i = 1; i <= q; i++){
			scanf("%d%d%d%d", &h1, &w1, &h2, &w2);
			ans = m[h2 - 1][w2 - 1] - m[h1][w2 - 1] - m[h2 - 1][w1] + m[h1][w1];
			printf("%lld\n", ans);
		}
	}
    return 0;
}
```

---

## 作者：孤芒星河233 (赞：0)

# CF1722E Counting Rectangles

  [CF题面](http://codeforces.com/problemset/problem/1722/E)
  
  [洛谷题面](https://www.luogu.com.cn/problem/CF1722E)

  有 $T$ 组数据，每组数据给出 $n$ 个矩形以及它们的长宽 $h_i,w_i$。有 $q$ 次询问，每次询问输入四个数 $h_s,w_s,h_b,w_b$（这些数和刚刚输入的矩形**无关**），输出满足  的矩形面积之和。

  数据范围：$1\leq T\leq 100,1\leq n,q\leq 10^5,1\leq h_i,w_i \leq 1000,1\leq h_s<h_b,w_s<w_b \leq 1000$

## 思路

  对于询问，我们肯定不能暴力枚举每个矩形，否则时间复杂度 $O(qn)$ 会超时。从另一个角度看，给出的坐标范围为 $[1,1000]$，我们可以用一个二位数组来存储每一个矩形，下标代表坐标，值为面积。怎么才能快速算出满足 $h_i \in (h_s,h_w),w_i\in (w_s,w_w)$ 矩形总面积呢？

  通过**二维前缀和**或**二维树状数组**来解决本题。

## 代码
  
  题解都是前缀和，于是我写了份二维树状数组的

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define ll long long

  const int M=1e3+9;
  int T,n,q;
  ll tr[M][M];
  
  int lowbit(int x){
      return x&-x;
  }
  void add(int x,int y,ll d){//在(x,y)处加上矩形的面积
      for(int i=x;i<=1e3;i+=lowbit(i)){
          for(int j=y;j<=1e3;j+=lowbit(j)) tr[i][j]+=d;
      }
  }
  ll sum(int x,int y){//求前缀和
      ll ans=0;
      for(int i=x;i;i-=lowbit(i)){
          for(int j=y;j;j-=lowbit(j)) ans+=tr[i][j];
      }
      return ans;
  }
  
  int main(){
      scanf("%d",&T);
      while(T--){
          memset(tr,0,sizeof(tr));//记得清空树状数组
          scanf("%d%d",&n,&q);
         ll x,y;
          for(int i=1;i<=n;i++){
              scanf("%lld%lld",&x,&y);
              add(x,y,x*y);
          }
          int c,d,e,f;
          while(q--){
              scanf("%d%d%d%d",&c,&d,&e,&f);
              printf("%lld\n",sum(e-1,f-1)-sum(c,f-1)-sum(e-1,d)+sum(c,d));//求出区间内的矩形面积总和
          }
      }
      return 0;
  }
  ```

---

## 作者：zsseg (赞：0)

### 题目描述：

给定 $n$ 个矩形，每个矩形有长 $h_i$ , 宽 $w_i$ ，$q$ 组询问，每次给定 $h_s,w_s,h_b,w_b$ 求 $\sum\limits_{i=1}^n h_i\times w_i\times [h_s<h_i<h_b] \times [w_s<w_i<w_b]$。

数据范围 $n,q\leq 10^5, h_i,w_i\leq 10^3$。

### solution:

观察到 $h,w$ 的范围都很小，考虑以此着手，我们用 $a_{i,j}$ 表示 $h=i,w=j$ 的矩形的面积，不难发现每次询问即求 $\sum\limits_{i=h_s+1}^{h_b-1}\sum\limits_{j=w_s+1}^{w_b-1}a_{i,j}$。这样的时间复杂度为 $\varTheta(n+qhw)$，无法通过。

可以发现我们能将复杂度转移到预处理上，以前缀和的思想，我们用 $a_{i,j}$ 表示 $h=i,w\leq j$ 的矩形的面积和，每次询问就变成求 $\sum\limits_{i=h_s+1}^{h_b-1}(a_{i,wb-1}-a_{i,ws})$。 时间复杂度为 $\varTheta(nw+qh)$，可以通过。

### Code:
```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
#define g(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define end() putchar('\n')
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return f?x:-x;
}
inline void write(ll x,char end=' '){
    static int k[31];
    int f=0;
    if(x<0)x=-x,putchar('-');
    do{k[f++]=x%10,x/=10;}while(x);
    while(f)putchar(k[--f]^'0');
    putchar(end);
}
ll T=read(),n,q,h[100010],w[100010];
ll a[1010][1010];
int main(){
	while(T--){
		memset(a,0,sizeof(a));
		n=read(),q=read();
		f(i,1,n){
			h[i]=read(),w[i]=read();
			f(j,w[i],1000)a[h[i]][j]+=h[i]*w[i];
		}
		while(q--){
			ll hs=read(),ws=read(),hb=read(),wb=read();
			ll tot=0;
			f(i,hs+1,hb-1)tot+=a[i][wb-1]-a[i][ws];
			write(tot,'\n');
		}
	}
	return 0;
}
```


---

