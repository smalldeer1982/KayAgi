# [ICPC 2020 WF] Which Planet is This?!

## 题目描述

这是2521年，星际探测器已经到达了遥远的太阳系的行星。星际行星制图者联盟(ICPC)已经绘制了这些行星的详细地图，它们似乎表明外星生命的存在!ICPC在每张地图上都记录了疑似外星人住所的位置。

ICPC本打算向公众公布这一激动人心的消息，但在最后一刻，灾难发生了。ICPC的一名实习生删除了所有与地图相关的元数据。因此，虽然地图本身是安全的，但ICPC并不知道哪些地图属于哪些行星。为此，他们及时回来请求您的帮助。给定两幅地图，你能确定它们是否描述的是同一颗行星吗?希望领先500年的时间足以解决这个重要的问题!

行星图由(球面)行星表面的点集组成。它们是根据纬度(赤道南北的夹角)和经度(正午子午线的西半球或东半球的夹角，这是地图数据采集时太阳的位置)来指定的。同一颗行星的两幅地图在纬度上总是一致的，因为行星的轴是不变的。然而，这两个点的经度可能不同，因为行星在两次测量之间会旋转。

## 样例 #1

### 输入

```
4
0.0000 0.0000
30.0000 90.0000
-45.0000 -30.0000
30.0000 60.0000
30.0000 150.0000
30.0000 120.0000
0.0000 60.0000
-45.0000 30.0000```

### 输出

```
Same```

## 样例 #2

### 输入

```
3
0.0000 0.0000
30.0000 0.0000
30.0000 90.0000
0.0000 0.0000
30.0000 0.0000
30.0000 -90.0000```

### 输出

```
Different```

# 题解

## 作者：ctzm (赞：4)

纯最小表示法做法，应该是尽可能做的最简洁的。

---

题意：给你两个地图，有 $n$ 个点分别是坐标 $x,y$。两个地图本质相同，当且仅当题面有一种方式一一对应，并且对应点 $x$ 相同，$y$ 的差值是固定的 $k$，对于所有点都适用（$y$ 在模 $360$ 意义下）。判断两个地图是否本质相同。

首先，题目的坐标是小数，最多 $4$ 位（但是甚至有数据可能没有小数点）。为了简化，我们想到读入浮点数，乘上 $10^4$ 再转成整数，但事实是会有浮点误差。**直接下结论：必须写快读（或之类的处理）**。

直接展示我的处理代码，该函数读入一个浮点数，并返回它的 $10^4$ 倍：

```cpp
int get(){
	string s;
	cin>>s;
	int sgn=1,res=0,dot=0,cnt=4;
	for(char i:s){
		if(i=='-')sgn=-1;
		if(i=='.')dot=1;
		if('0'<=i&&i<='9'){
			if(dot)cnt--;
			res=res*10+(i-'0');
		}
	}
	res=sgn*res*pow(10,cnt);
	return res;
}
```

然后，由于合法的判定是存在合法差值 $k$，不影响它们的两两之间的大小关系和差值，我们先按照 $y$ 排个序。为了排序唯一，$y$ 相等就按照 $x$ 排序。然后，我们只需要判断两组点对应位置 $x$ 是否相等就好了。

**以上只是一个初步思路**，因为 $y$ 是要模 $360$ 的，因此原本一个大值可能加上偏移量就变小了，直接排序比较是错的，但也肯定可以将其旋转得到正确的原序列。所以，我们需要判断有没有一种旋转方式使得 $x$ 匹配，这就是最小表示法的应用之一。还有一个问题，即使 $x$ 匹配，$y$ 的相对大小正确，但我们依然需要 $y$ 的绝对大小作为参考，例如下面这组数据：

```
3
1 50
2 100
3 150
1 66
2 127
3 148
```

就能理解了吧。注意到全局加 $k$，其差分数组是不变的，我们重新把每个点的 $y$ 设置成差分即可。注意这是一个类似环形的差分。

总结以下，合法的判定是：

- 按 $y$ 排序后，存在一种循环同构方案使得它们 $x$ 一一对应，$y$ 的差分也一一对应。

~~随机凭做题直觉就感觉感觉到这个条件也是充分的~~。不理解的看代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,del1,del2;
pair<int,int> p[400040],q[400040];
int get(){
	string s;
	cin>>s;
	int sgn=1,res=0,dot=0,cnt=4;
	for(char i:s){
		if(i=='-')sgn=-1;
		if(i=='.')dot=1;
		if('0'<=i&&i<='9'){
			if(dot)cnt--;
			res=res*10+(i-'0');
		}
	}
	res=sgn*res*pow(10,cnt);
	return res;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){int a=get(),b=get();p[i]={b,a};}
	for(int i=0;i<n;i++){int a=get(),b=get();q[i]={b,a};}
	sort(p,p+n);
	sort(q,q+n);
	p[n]={p[0].first+3600000,0};
	for(int i=0;i<n;i++){
		p[i].first=p[i+1].first-p[i].first;
	}
	q[n]={q[0].first+3600000,0};
	for(int i=0;i<n;i++){
		q[i].first=q[i+1].first-q[i].first;
	}	
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		if(p[(i+k)%n]==p[(j+k)%n])k++;
		else if(p[(i+k)%n]<p[(j+k)%n])j=j+k+1,k=0;
		else i=i+k+1,k=0;
		if(i==j)i++;
	}
	del1=min(i,j);
	
	i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		if(q[(i+k)%n]==q[(j+k)%n])k++;
		else if(q[(i+k)%n]<q[(j+k)%n])j=j+k+1,k=0;
		else i=i+k+1,k=0;
		if(i==j)i++;
	}
	del2=min(i,j);
	
	for(int i=0;i<n;i++){
		if(p[(i+del1)%n]!=q[(i+del2)%n]){
			cout<<"Different";
			return 0; 
		}
	}
	cout<<"Same";





	return 0;
}
```

---

## 作者：__Aaaaaaaa (赞：3)

题目大意：给定两个地球仪，上面各有 $n$ 个点（$n\leq 4\times 10^5$），以经纬的形式给出，现在判定在转动地球仪之后（转动只能改变一个点的经度，不能改变它的纬度），两个地球仪是否是相同的。

Solution：
首先需要考虑在这种情况下，相同的定义是什么。因为纬度不能改变，那么说明两个地球仪上所有点的纬度的集合是一样的。   
满足了这个条件后，如果两个地球仪上存在某种对点的编号，使得所有点对的相对位置关系是一样的。

那么可以先想到一个充满直观感受 ~~（抽象形容词）~~ 的做法，因为地球仪可以转动经度，那么就很像字符串的置换求最小表示法，判定两个地球仪的最小表示法是否相同不就行了吗。就有了按照经度排序后求纬度的最小表示法的做法。

很显然错了，因为此处并不是点的先后关系是本质一样的就行，还要保证点对之间的角度一样。那么我就多加了一个关键字，就是它与排序后（排序是经纬双关键字）的下一个点的欧几里得距离，就这样通过了。

tips:  
1. 输入量很大，对自己的常数不自信建议写快读。  
2. 求两点之间的距离时，横纵坐标之差需要考虑地球仪是圆的，例如 $|X_A-X_B|$ 要考虑和 $360-|X_A-X_B|$ 取个较小。  

### Code:
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef double D;
const D eps=1e-7;
const int N=8e5+10;
int n;
int cmp(D x,D y){
	if(abs(x-y)<eps)return 0;
	if(x-y<0)return -1;
	return 1;
}
struct node{
	D x,y;
	bool operator<(const node &t)const{
		return x==t.x?cmp(y,t.y)<0:cmp(x,t.x)<0;
	}
	bool operator!=(const node &t)const{
		return cmp(x,t.x)||cmp(y,t.y);
	}
}m1[N],m2[N],A[N],B[N];
D dis(D x1,D y1,D x2,D y2){
	double dy=x1-x2;
	double dx=y1-y2;
	if(dx<0)dx+=360;
	if(dy<0)dy+=360;
	return sqrt(dx*dx+dy*dy);
}
bool cmp1(const node &A,const node &B){
	return A.y==B.y?A.x<B.x:A.y<B.y;
}
int get_min(node K[N]){
	for(int i=1;i<=n;++i)K[i+n]=K[i];
	int i=1,j=2;
	while(i<=n&&j<=n){
		if(i==j)++i;
		for(int k=0;k<n;++k){
			if(K[i+k]!=K[j+k]||k==n-1){
				if(K[i+k]<K[j+k])j+=k+1;
				else i+=k+1;
				break;
			}
		}
	}
	return min(i,j);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf%lf",&m1[i].x,&m1[i].y);
	for(int i=1;i<=n;++i)scanf("%lf%lf",&m2[i].x,&m2[i].y);
	sort(m1+1,m1+1+n);
	sort(m2+1,m2+1+n);
	for(int i=1;i<=n;++i){
		if(m1[i].x!=m2[i].x){
			puts("Different");
			return 0;
		}
	}
	sort(m1+1,m1+1+n,cmp1);
	sort(m2+1,m2+1+n,cmp1);
	for(int i=1;i<n;++i)A[i]=(node){m1[i].x,dis(m1[i+1].x,m1[i+1].y,m1[i].x,m1[i].y)};
	A[n]=(node){m1[n].x,dis(m1[1].x,m1[1].y,m1[n].x,m1[n].y)};
	for(int i=1;i<n;++i)B[i]=(node){m2[i].x,dis(m2[i+1].x,m2[i+1].y,m2[i].x,m2[i].y)};
	B[n]=(node){m2[n].x,dis(m2[1].x,m2[1].y,m2[n].x,m2[n].y)};
	int x=get_min(A),y=get_min(B);
	for(int i=0;i<n;++i){
		if(A[i+x]!=B[i+y]){
			puts("Different");
			return 0;
		}
	}
	puts("Same");
	return 0;
}
```

---

## 作者：mRXxy0o0 (赞：1)

# 题意

由于题面太难理解了，我们形象化一下。

你面前有一个地球仪，用记号笔涂了 $n$ 个点，告诉你这 $n$ 个点的经纬度坐标。然后又告诉你另外 $n$ 个点的经纬度坐标，让你判断可不可以通过转动地球仪，来让他们重合。

# 分析

首先注意到题目限制，对于给出的经纬度坐标 $(a,b)$，有 $-90<a<90$、$-180<b<180$，这样我们就可以不用考虑类似在极点这样的边界情况。~~（出题人我谢谢你）~~

注意到**不管怎么转，一个点所在的纬度不会改变**，这提示我们对于不同纬度分开考虑，然后再思考如何合并不同的纬度。

首先，对于同一个纬度，最基本的要求是所含点的个数一样。其次，明显可以发现，不管如何转动，经度的差分数组始终是不变的。关注到这一点，我们就考虑如何判断两个差分数组是不是可以经过转动得到的。

事实上，这是判断两个串是否循环同构，我们可以使用最小表示法，也可以使用把其中一个复制一倍，再跑 KMP 就可以简单判断出。

如果两个数组可以转动得到，我们就记录下所有可以使他们重合需要转的角度。再对所有纬度的角度集合判断交集是否为空。

> 注意到同层的点可能有循环节，这意味着不止有一个角度可以使他们重合，需要全部记下。

注意实现上的一些细节。

- 求交集可以使用 `map`，也可以用记到数组里，减小常数。

- 浮点数可能有误差，由于最多四位小数，可以转成 `int` 来存。

- 如果你转成 `int` 了，一定不能直接把输入的乘上 $10000$，这样会发生神秘错误，一定要用快读板子魔改一下来输入。

- 在这道题里，$-90$ 和 $270$ 是一样的角度，可以直接把负数加上 $360$ 避免特判。

剩下的看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=4e5+10;
int n,ne[N],Q[N],Q1[N],hh,hh1;
int A[N],B[N];
struct node{
	int x,y;
}a[N],b[N];
inline bool cmp(node x,node y){
	return x.x==y.x?x.y<y.y:x.x<y.x;
}
char buf[1<<21],*p1=buf,*p2=buf;
inline char gc(){
	if(p1==p2) p2=(p1=buf)+fread(buf,1,1<<21,stdin);
	return *p1++;
}
inline int read(){
	int res=0;
	char ch=gc();
	bool f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=0;
		ch=gc();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=gc();
	}
	if(ch=='.'){
		ch=gc();
		int cnt=0;
		while(ch>='0'&&ch<='9'){
			++cnt;
			res=(res<<1)+(res<<3)+(ch^48);
			ch=gc();
		}
		while(cnt<4) res*=10,++cnt;
	}
	else{
		res*=10000;
	}
	return f?res:-res;
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<=n;++i){
		x=read();y=read();
		a[i]=/**/{x,y};
	}
	for(int i=1,x,y;i<=n;++i){
		x=read();y=read();
		b[i]=/**/{x,y};
	}
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n,cmp);
	int p1=1,tim=0;
	bool fi=1;
	while(p1<=n){
		++tim;
		int m=1,ne1=p1,ne2=p1;
		A[0]=a[p1].y,B[0]=b[p1].y;
		while(ne1<n&&a[ne1].x==a[ne1+1].x) A[m++]=a[++ne1].y;
		m=1;
		while(ne2<n&&b[ne2].x==b[ne2+1].x) B[m++]=b[++ne2].y;
		if(ne1!=ne2||a[p1].x!=b[p1].x){
			puts("Different");
			return 0;
		}
		int tmp=A[m-1];
		for(int i=m-1;i>0;--i){
			A[i]=A[i]-A[i-1];
			if(A[i]<0) A[i]=3600000+A[i];
		}
		A[0]=A[0]-tmp;
		if(A[0]<0) A[0]=3600000+A[0];
		tmp=B[m-1];
		for(int i=m-1;i>0;--i){
			B[i]=B[i]-B[i-1];
			if(B[i]<0) B[i]=3600000+B[i];
		}
		B[0]=B[0]-tmp;
		if(B[0]<0) B[0]=3600000+B[0];
		ne[m+1]=0;
		for(int i=2,j=0;i<=m;++i){
			while(j&&A[i-1]!=A[j]) j=ne[j];
			ne[i]=(A[i-1]==A[j]?++j:j);
		}
		int i=0,j=1,k=0;
		while(i<m&&j<m&&k<m){
			if(A[(i+k)%m]==A[(j+k)%m]) ++k;
			else{
				A[(i+k)%m]<A[(j+k)%m]?j+=k+1:i+=k+1;
				if(i==j) ++i;
				k=0;
			}
		}
		int bg1=min(i,j);
		i=0,j=1,k=0;
		while(i<m&&j<m&&k<m){
			if(B[(i+k)%m]==B[(j+k)%m]) ++k;
			else{
				B[(i+k)%m]<B[(j+k)%m]?j+=k+1:i+=k+1;
				if(i==j) ++i;
				k=0;
			}
		}
		int bg2=min(i,j);
		for(int i=0;i<m;++i){
			if(A[bg1]!=B[bg2]){
				puts("Different");
				return 0;
			}
			bg1=(bg1+1)%m,bg2=(bg2+1)%m;
		}
		bool hav=0;
		tmp=a[p1+bg1].y-b[p1+bg2].y;
		if(tmp<0) tmp=3600000+tmp;
		hh1=0;
		Q1[++hh1]=tmp;
		int len=m-ne[m];
		if(m%len==0){
			for(int i=(bg1+len)%m;i!=bg1;i=(i+len)%m){
				tmp=a[p1+i].y-b[p1+bg2].y;
				if(tmp<0) tmp=3600000+tmp;
				Q1[++hh1]=tmp;
			}
		}
		sort(Q1+1,Q1+1+hh1);
		tmp=unique(Q1+1,Q1+1+hh1)-Q1-1;
		hh1=tmp;
		if(fi){
			for(int i=1;i<=hh1;++i) Q[i]=Q1[i];
			hh=hh1;
		}
		else{
			int tot=0;
			j=1;
			for(int i=1;i<=hh1;++i){
				while(j<=hh&&Q[j]<Q1[i]) ++j;
				if(Q[j]==Q1[i]) Q[++tot]=Q[j],hav=1;
			}
			hh=tot;
		}
		if(!fi&&!hav){
			puts("Different");
			return 0;
		}
		fi=0;
		p1=ne1+1;
	}
	puts("Same");
	return 0;
}
```


---

## 作者：naoliaok_lovely (赞：0)

~~水了一发最优解 hh~~

## 题目大意
有两个地图，每个地图都有 $n$ 个点。问能否找到一个偏移量 $d$，使得第一张地图的点对 $(x,y)$ 变为 $(x,y+d)$ 后和第二张地图完全重合。（在第二维模 $360$ 的意义下）

# Solution
**标签：最小表示法，kmp，excrt。**

首先把题目的小数坐标 $\times10^4$ 方便后续处理（埋下伏笔）。  
显然，对于不同的 $x$ 坐标是相对独立的，我们可以分开处理。对于 $x$ 坐标相同的很多点，可以想象到应该是一个圆圈的形状。于是问题就变成了：给定两个有很多点的圈，问他们在可以旋转的情况下是否一样。显然，这可以使用 **差分+最小表示法** 轻松解决。即：对于原数组求出其对应的差分数组，如果这两个差分数组循环同构，显然这两个环应该是一样的。

解决了这一步，即每个圆圈都是同构的，但这也并不代表全局就是有解的。这可以从样例二体现出来——对于 $x=30$ 这个圆圈，他们的确是循环同构的，但是因为他们同构的条件是 $d=-90$，而这会使得原本同构的 $x=0$ 这个圈不同构，即这两个圈没有办法同时同构。  
我们可以从上面的分析得到灵感：随便拿一个圈，求出它的 $d$ 值，然后直接带入验证。~~当然这很快就会发现问题……~~ 容易发现，对于一个圈，它的 $d$ 值可能不是唯一的——如果对应关系确定了，偏移量当然是一个定值。但是有一些 **循环同构** 的环，导致对应关系出现偏移。想想修正方案——其实只需要改改模数就好了。举个例子：

![圆圈.PNG](https://cdn.acwing.com/media/article/image/2023/09/22/104910_c53163c659-圆圈.PNG) 

对于这张图，我们如果列出所有的偏移量即为 $d\equiv0,120,240\pmod{360}$，但并没有必要这样——直接写成 $d\equiv0\pmod{120}$ 即可。（其实上面的过程有点套路）  
实现的时候，我们只需要先用 kmp 求出循环节，然后使用 excrt 合并同余方程判断是否有解即可。

## 回收开头
按照上面的思路写，会发现 Wa on 19。  
经测试，在 $\times10^4$ 的时候会出现精度误差，改用快读即可。

# Code
```
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int, int>

const int N = 8e5 + 10, mod = 3600000;
int n;
PII a[N], b[N];
int len, c[N], d[N], ne[N];
int ans, m = 1;

char buf[1 << 21], *p1 = buf, *p2 = buf;
inline char gc()
{
	if(p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin);
	return p1 == p2 ? EOF : *p1++;
}
inline int read()
{
	int f = 1, w = 0;
	char ch = gc();
	while(ch < '0' || '9' < ch)
	{
		if(ch == '-') f = -1;
		ch = gc();
	}
	while('0' <= ch && ch <= '9')
	{
		w = (w << 1) + (w << 3) + (ch ^ 48);
		ch = gc();
	}
	return f * w;
}
inline int readd()
{
	int f = 1, w = 0, cnt = 4;
	char ch = gc();
	while(ch < '0' || '9' < ch)
	{
		if(ch == '-') f = -1;
		ch = gc();
	}
	while('0' <= ch && ch <= '9')
	{
		w = (w << 1) + (w << 3) + (ch ^ 48);
		ch = gc();
	}
	if(ch == '.')
	{
		ch = gc();
		while('0' <= ch && ch <= '9')
		{
			cnt--;
			w = (w << 1) + (w << 3) + (ch ^ 48);
			ch = gc();
		}
	}
	while(cnt--) w = (w << 1) + (w << 3);
	return f * w;
}

int get(int c[])
{
	memcpy(c + len + 1, c + 1, len << 2);
	int i = 1, j = 2;
	while(i <= len && j <= len)
	{
		int k = 0;
		while(k < len && c[i + k] == c[j + k]) k++;
		if(k == len) break;
		if(c[i + k] < c[j + k]) j += k + 1;
		else i += k + 1;
		if(i == j) j++;
	}
	return min(i, j);
}

int kmp(int c[])
{
	for(int i = 2, j = 0; i <= len; i++)
	{
		while(j && c[j + 1] != c[i]) j = ne[j];
		if(c[j + 1] == c[i]) j++;
		ne[i] = j;
	}
	int res = len - ne[len];
	if(len % res) return len;
	return res;
}

int exgcd(int a, int b, int &x, int &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main()
{
	n = read();
	for(int i = 1, x, y; i <= n; i++) x = readd(), y = readd(), a[i] = {x, y};
	for(int i = 1, x, y; i <= n; i++) x = readd(), y = readd(), b[i] = {x, y};
	sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
	
	for(int i = 1; i <= n; i++)
	{
		int j = i, k = i;
		if(a[i].first != b[i].first)
		{
			puts("Different");
			return 0;
		}
		while(j < n && a[j].first == a[j + 1].first) j++;
		while(k < n && a[k].first == a[k + 1].first) k++;
		if(j != k)
		{
			puts("Different");
			return 0;
		}
		
		for(len = 1; len < j - i + 1; len++)
			c[len] = a[i + len].second - a[i + len - 1].second,
			d[len] = b[i + len].second - b[i + len - 1].second;
		c[len] = (a[i].second - a[j].second + mod) % mod, d[len] = (b[i].second - b[j].second + mod) % mod;
		
		int p1 = get(c), p2 = get(d), r = (a[p1 + i - 1].second - b[p2 + i - 1].second + mod) % mod;
		for(int j = p1 == len ? 1 : p1 + 1, k = p2 == len ? 1 : p2 + 1; j != p1; j = j == len ? 1 : j + 1, k = k == len ? 1 : k + 1)
			if((a[j + i - 1].second - b[k + i - 1].second + mod) % mod != r)
			{
				puts("Different");
				return 0;
			}
		int p = kmp(c);
		p = a[(p == len ? 0 : p) + i].second - a[i].second;
		if(!p) p = mod;
		
		int x, y, d = exgcd(m, p, x, y);
		if((r - ans) % d)
		{
			puts("Different");
			return 0;
		}
		x = (1ll * (r - ans) / d * x % (p / d) + p / d) % (p / d);
		ans = (ans + x * m) % (p / d * m);
		m *= p / d;
		
		i = j;
	}
	
	puts("Same");
	return 0;
}
```

---

