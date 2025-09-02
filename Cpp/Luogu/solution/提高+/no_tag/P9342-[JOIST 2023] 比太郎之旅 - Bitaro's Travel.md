# [JOIST 2023] 比太郎之旅 / Bitaro's Travel

## 题目描述

在 JOI 市有一条很长的道路，可以看作是实数轴。道路上的一个位置由一个实数坐标表示。在 JOI 市，沿着这条道路有 $N$ 个观光景点，按坐标递增的顺序编号为 $1$ 到 $N$。第 $i$ 个观光景点 $(1 \le i \le N)$ 的坐标为 $X_i$。

Bitaro 将参观 JOI 市的所有观光景点。由于“贪婪”是他生活的口号，他将重复以下步骤，直到参观完所有的观光景点。

- 设 $x$ 为 Bitaro 当前的坐标。在他尚未参观的观光景点中，选择一个景点 $i$，使得从 Bitaro 当前坐标到该景点的距离 $|x - X_i|$ 最小。然后 Bitaro 移动到景点 $i$ 的位置，并参观它。如果有多个这样的观光景点，他会移动到坐标较小的那个景点。这里，$|t|$ 是 $t$ 的绝对值。

然而，由于多年的经验，Bitaro 知道如果他通过重复上述步骤来移动，总旅行距离可能会比他预期的要长。由于总旅行距离会根据起始坐标的不同而变化，他想知道如果从 $Q$ 个起始坐标候选 $S_1, S_2, \dots, S_Q$ 中的每一个开始，直到参观完所有观光景点的总旅行距离。

为了帮助 Bitaro，编写一个程序，计算如果他从每个起始坐标候选开始的总旅行距离，给定 JOI 市的信息和起始坐标候选。

## 说明/提示

**【样例解释 #1】**

如果 Bitaro 从坐标 $7$ 开始，他将按如下方式参观所有观光景点。
1. 他尚未参观的观光景点有 $1, 2, 3, 4, 5$，从 Bitaro 当前坐标到这些景点的距离分别为 $7, 2, 1, 0, 2$。由于观光景点 $4$ 是离 Bitaro 最近的景点，他停留在坐标 $7$ 并参观观光景点 $4$。
2. 他尚未参观的观光景点有 $1, 2, 3, 5$，从 Bitaro 当前坐标到这些景点的距离分别为 $7, 2, 1, 2$。由于观光景点 $3$ 是离 Bitaro 最近的景点，他从坐标 $7$ 移动到坐标 $6$ 并参观观光景点 $3$。
3. 他尚未参观的观光景点有 $1, 2, 5$，从 Bitaro 当前坐标到这些景点的距离分别为 $6, 1, 3$。由于观光景点 $2$ 是离 Bitaro 最近的景点，他从坐标 $6$ 移动到坐标 $5$ 并参观观光景点 $2$。
4. 他尚未参观的观光景点有 $1, 5$，从 Bitaro 当前坐标到这些景点的距离分别为 $5, 4$。由于观光景点 $5$ 是离 Bitaro 最近的景点，他从坐标 $5$ 移动到坐标 $9$ 并参观观光景点 $5$。
5. 他尚未参观的观光景点有 $1$。由于观光景点 $1$ 是离 Bitaro 最近的景点，他从坐标 $9$ 移动到坐标 $0$ 并参观观光景点 $1$。

由于 Bitaro 的总旅行距离是 $15$，输出 $15$。

该样例满足所有子任务的限制。

**【样例解释 #2】**

该样例满足子任务 $3, 4$ 的限制。

**【数据范围】**

对于所有测试数据，满足 $1 \le N, Q \le 2 \times 10^5$，$0 \le X_i \le 10^9$，$X_i < X_{i+1}$，$0 \le S_j \le 10^9$，保证所有输入均为整数。

|子任务编号|分值|限制|
|:-:|:-:|:-:|
|$1$|$5$|$Q=1, N \le 2 \times 10^3$|
|$2$|$10$|$Q=1$|
|$3$|$30$|$X_{i+1} - X_i \le 100$|
|$4$|$55$|无|

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
0 5 6 7 9
1
7
```

### 输出

```
15```

## 样例 #2

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10
1
2
3
4
5
6
7
8
9
10
```

### 输出

```
9
10
11
12
13
14
15
16
17
9
```

# 题解

## 作者：Cure_Wing (赞：7)

[题目](https://www.luogu.com.cn/problem/P9342)

### 分析

看到题目首先会想到简单的暴力：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using std::cin;using std::cout;
constexpr int N=200005;
int n,a[N],q,s;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    cin>>q;
    for(int i=1;i<=q;++i){
        cin>>s;
        int p=std::lower_bound(a+1,a+n+1,s)-a;//寻找最近点
        if(p==1) p=1;
        else if(p==n+1) p=n;
        else{
            if(a[p]-s<s-a[p-1]) p=p;
            else p=p-1;
        }
        int l=p-1,r=p+1,ans=std::abs(a[p]-s);
        while(p!=1&&p!=n){//暴力扩展两边
            if(a[p]-a[l]<=a[r]-a[p]) ans+=a[p]-a[l],p=l,--l;
            else ans+=a[r]-a[p],p=r,++r;
        }
        cout<<ans+a[n]-a[1]<<'\n';
    }
    return 0;
}
```

但是这个暴力是 $O(qn)$ 的，显然过不去。

考虑优化这个暴力。

如果你对 $a_p-a_l\le a_r-a_p$ 的结果输出一下的话，就会发现有很多 $0$ 和 $1$ 是连续出现的。

这实际上在提醒我们，Bitaro 的转向次数并不会很多。

考虑如果每走一次就要让他转向，那么他距离同向的下一个景点的距离一定大于他已经走过的距离，因为反向的下一个景点一定在上一个景点之后。

这样每次走过的路程将会以指数级增长，而路程总长只有 $10^9$，那么大约至多只有 $31$ 次转向。

接下来继续想，在同向的连续段的行程中，如果后到达的点可以比其它点先被判到达，那么即使先到达的点未搜过，但是它一定可以比这个点先到达。

如果这个时候要转向，唯一的情况就是到前方最近的点的距离大于（或等于）后方的点的距离。这个时候我们假定可以往前走，走的路程为这个点到上一个转向点之后的点的距离（比如现在在 $p$，已经走过了 $[l,r]$，且 $p=r$，那么 $l$ 一定为上一个转向点，$(l-1)$ 为其之后的点）。这个时候我们往前搜，如果能搜到一个位置在这个距离以内，那么说明往前走会有更近的景点。反之就只能转向了。看到在有序数列中搜索一个位置，自然而然想到二分，而二分是 $\log$ 级别的，复杂度在此得到了降低。

最后还可以优化的是，如果这个时候 Bitaro 已经走到 $1$ 或 $n$ 了，如果这个时候他还没走完，那么他一定会从 $1$ 走到 $n$ 或 从 $n$ 走到 $1$ ，直接加上这段距离就可以了，不需要再次搜索。

这样子时间复杂度应该为 $O(n+q\log n\log n)$。一个 $\log$ 是搜索，还有一个是与转向次数有关。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using std::cin;using std::cout;
constexpr int N=200005;
int n,a[N],q,s;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    cin>>q;
    for(int i=1;i<=q;++i){
        cin>>s;
        int p=std::lower_bound(a+1,a+n+1,s)-a;//寻找最近点
        if(p==1) p=1;
        else if(p==n+1) p=n;
        else{
            if(a[p]-s<s-a[p-1]) p=p;
            else p=p-1;
        }
        int l=p,r=p;
		long long ans=std::abs(a[p]-s);
        while(l>1&&r<n){//触碰两端即可结束
            if(p==l){//优化扩展
                int dis=std::abs(a[p]-a[r+1]);
				int u=std::lower_bound(a+1,a+n+1,a[p]-dis)-a;
				if(u<l){//尝试继续往左扩展
					ans+=std::abs(a[p]-a[u]);
					p=l=u;
				}else{//不行则往右
					ans+=dis;
					p=++r;
				}
            }else{
				int dis=std::abs(a[p]-a[l-1]);
				int u=std::lower_bound(a+1,a+n+1,a[p]+dis)-a-1;//注意相等时左侧优先
				if(u>r){//尝试继续往右扩展
					ans+=std::abs(a[u]-a[p]);
					p=r=u;
				}else{//不行则往左
					ans+=dis;
					p=--l;
				}
			}
        }
		ans+=a[n]-a[1];
		cout<<ans<<'\n';
    }
    return 0;
}
```

最后感谢一下 @tyr 和 @lys 的教导！

---

## 作者：Mo默Sh笙 (赞：4)

### [传送门](https://www.luogu.com.cn/problem/P9342)

------------

### 基本思路：
对每个 $A_i$ 的答案进行预处理，对于每个询问，只需要找到第一个到达的景点即可。

那么如何预处理每个点的答案呢？有一条很重要的性质：**最多转向 $\log{X}$ 次**。

要证明这个结论，先放上一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/f79a3g5n.png)

设第 $k$ 段路径长度为 $L$，从图中可以看出，$L_{k}\geq 2\times L_{k-1}$，因为 $1 \leq L_k\leq X$，可以推得 $k\leq \log{X}$。

证明了这个结论，我们就可以在 $\mathcal{O}(n^2\log{n})$ 的时间暴力走一遍预处理出答案，运用ST表倍增可以优化到 $\mathcal{O}(n\log^2{n})$。

对于每个询问，二分找到第一个到达的景点，直接输出对应的答案即可。

整体复杂度 $\mathcal{O}(n\log^2{n}+q\log{N})$。

注释很详细，写在代码里，注释掉的代码是对 Y2hlbnlpa2Fp 题解的改进。

------------

$Code$

```cpp
#include<bits/stdc++.h>//MoSheng
using namespace std;
#define ll long long
#define ul unsigned long long
#define db double
#define il inline
#define re register
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f//ll范围下LINF，够大 
#define int ll//要开longlong 
#define F(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define DF(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)
#define G(i,u) for(int (i)=head[u];(i);(i)=nxt[(i)])
inline ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
const int N=200010;
int n;
int pos[N],ans[N];
int stl[N][25],str[N][25];
signed main()
{
	n=read();
	F(i,1,n) pos[i]=read();
	pos[0]=-LINF;//边界处理I
	pos[n+1]=LINF;//一定要开7f^4或3f^8，1e9范围下3f^4太小 
//	if(n==1)//特判？其实没必要，因为有边界处理 
//	{
//		int q=read();
//		F(i,1,q)
//		{
//			int loc=read();
//			printf("%lld\n",abs(loc-pos[1]));
//		}
//		return 0;
//	}
	F(i,1,n-1) stl[i][0]=pos[i]-(pos[i+1]-pos[i]);//该点向右移动的距离在左边的坐标映射，便于与左节点距离比较 
	stl[n][0]=-LINF;//边界处理II
	F(i,2,n) str[i][0]=pos[i]+(pos[i]-pos[i-1]);//该点向左移动的距离在右边的坐标映射，便于与右节点距离比较 
	str[1][0]=LINF;
	F(k,1,20)
	{
		F(i,1,n)
			if(i+(1<<(k-1))<=n)
				stl[i][k]=min(stl[i][k-1],stl[i+(1<<(k-1))][k-1]);//过程中最远的一次能满足就一定满足全过程，所以取极值 
//			else//不满足则说明扩展到底了，不用继续拓展。但其实这步不需要，因为处理时不满足时会continue 
//				stl[i][k]=stl[i][k-1];
		F(i,1,n)//DF(i,n,1)//正反皆可 
			if(i-(1<<(k-1))>=1)
				str[i][k]=max(str[i][k-1],str[i-(1<<(k-1))][k-1]);
//			else
//				str[i][k]=str[i][k-1];
	}
	F(i,1,n)
	{
		int l=i,r=i,dir=0,now=i;//l和r分别表示左右两边走到的最远点 
		if(pos[i]-pos[i-1]<=pos[i+1]-pos[i]) dir=0;//判断开始时移动方向，0为左，1为右  
		else dir=1; 
		while(1<l||r<n)//还有没走的点 
		{
			if(dir==0)//先向左再向右转 
			{
				now=l;
				now--;//转完向至少走一步，提前走掉 
				DF(k,20,0)//倍增经典倒序，向左走到不能走 
				{
					if(now-(1<<k)<1) continue;//无法往左移动1<<k次就跳过，注意不能带= 
					if(str[now][k]<=pos[r+1]) now-=(1<<k);//向左走的距离更近就走，注意这里now不需要-1，因为我们已经提前走过一步了 
				}
//				now--;//这一步与now的-1一样，其实就是上一次转向后至少要走的那一步，我们在转向后立刻处理就不需要（不能加）这一步 
				ans[i]+=pos[r]-pos[now];
				l=now;
				dir=1;//记得转向 
			}
			else// if(dir==1)//先向右再向左转 
			{
				now=r;
				now++;//转完向至少走一步，提前走掉 
				DF(k,20,0)//倍增经典倒序，向右走到不能走 
				{
					if(now+(1<<k)>n) continue;//无法往右移动1<<k次就跳过，注意不能带=
					if(stl[now][k]>pos[l-1]) now+=(1<<k);//向右走的距离更近就走，与dir==0的情况同理，now不需要+1 
				} 
//				now++;//与dir==0的情况同理，这步不加 
				ans[i]+=pos[now]-pos[l];
				r=now;
				dir=0;//记得转向 
			}
		}
	}
	int q=read();
	F(i,1,q)
	{
		int loc=read();
		int R=upper_bound(pos+1,pos+n+1,loc)-pos;//找右边最近点，lower_bound和upper_bound都可 
		int L=R-1;//左边最近点 
		if(loc-pos[L]<=pos[R]-loc) printf("%lld\n",loc-pos[L]+ans[L]);
		else printf("%lld\n",pos[R]-loc+ans[R]);
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：3)

调试语句 RE 了，什么实力？

题目本身比较简单，就是说 CF1998E1 的经典结论，上述的贪心策略最多只会转向 $\log$ 次，因此直接每一次二分出转向点然后 ST 表来判断是否可以在这里不转向，时间复杂度为 $O(n\log^2n)$ 可以通过，注意处理边界情况，以及一开始要从 $x$ 走到距离其最近的结点所需的距离。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=500010;
int a[N];
int f[N][20],lg[N];
int query(int l,int r){
	assert(l<=r);
	return max(f[l][lg[r-l+1]],f[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	lg[0]=-1;for(int i=1;i<N;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<n;++i)f[i][0]=a[i+1]-a[i];
	for(int i=1;i<20;++i)
	for(int j=1;j<=n-(1<<i)+1;++j)
	f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
	int q;cin>>q;
	while(q--){
		int x;cin>>x;
		int l=1,r=n,best=n+1;
		while(l<=r){
			int mid=l+r>>1;
			if(a[mid]>=x)best=mid,r=mid-1;
			else l=mid+1;
		}
		int liuxu=x;
		int pos1=best-1,pos2=best;
		if(pos1<1||pos1>n)x=pos2;
		else if(pos2<1||pos2>n)x=pos1;
		else if(abs(x-a[pos1])<=abs(x-a[pos2]))x=pos1;
		else x=pos2;
		int L=x,R=x,pos=x,cnt=abs(liuxu-a[x]);
//		cout<<"qwq "<<liuxu<<' '<<x<<' '<<a[x]<<' '<<pos1<<' '<<pos2<<'\n';
		while(L!=1&&R!=n){
			if(abs(a[pos]-a[L-1])<=abs(a[pos]-a[R+1])){
				int l=1,r=L-2,best=L-1;
				while(l<=r){
					int mid=l+r>>1;
					if(query(mid,pos-1)<=a[R]-a[L])best=mid,r=mid-1;
					else l=mid+1;
				}
//					cerr<<"Check1 "<<L<<' '<<R<<' '<<best<<' '<<query(2,L-1)<<' '<<abs(a[2]-a[R+1])<<'\n';
				assert(~best);
				cnt+=a[pos]-a[best];
				L=pos=best;
			}else{
				int l=R+2,r=n,best=R+1;
				while(l<=r){
					int mid=l+r>>1;
					if(query(pos,mid-1)<=a[R]-a[L])best=mid,l=mid+1;
					else r=mid-1;
				}
//					cerr<<"Check2 "<<L<<' '<<R<<' '<<best<<'\n';
				assert(~best);
				cnt+=a[best]-a[pos];
				R=pos=best;
			}
		}
		cout<<cnt+a[n]-a[1]<<'\n';
	}
	return 0;
}
```

---

## 作者：Y2hlbnlpa2Fp (赞：3)

~~趁新题赶紧发一篇题解~~

首先容易发现，我们只需要预处理出每个 $A_i$ 的答案即可。

而且，每次操作完访问过的景点一定是一个连续段，且一次必定访问这个连续段的左边或者右边。

如果把访问左边记作 `L`，右边记作 `R`，并将操作序列看成一个串，那么经过一定观察，可以发现 `L` 和 `R` 组成的连续段个数不是很多。事实上，可以证明连续段的个数是 $\Theta(\log X)$ 的。

证明如下：

考虑每次改变方向时不选择的较大的距离。记第 $k$ 次的距离为 $L_k$。

放一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rk5jk1y0.png)

那么可以看出:

$$L_k\geq L+L_{k-1}=\sum_{i=1}^{k-1}L_{i}$$

设 $S_k=\sum_{i=1}^kL_i$。

则由上面的式子可以得到 $S_k\geq2S_{k-1}$。

又因为 $\forall k,S_k\leq X_n-X_1$，因此只有 $\Theta(\log X)$ 个连续段。

这样只要能快速找到每个连续段的结束位置就做完了。一种简洁的做法是使用 ST 表+倍增。

时间复杂度 $\Theta(n\log^2n+q\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define re(i,a,b) for(ll i=(a);i<(b);i++)
#define pe(i,a,b) for(ll i=(a);i>(b);i--)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
	r=w?-r:r;
}
const ll N=200003,M=3003,INF=2000000000000000007ll;
ll n,q,a[N],ans[N],st1[20][N],st2[20][N];
int main(){
	read(n);
	rep(i,1,n)read(a[i]);
	if(n==1){
		read(q);
		rep(i,1,q){
			ll in;
			read(in);
			printf("%lld\n",abs(in-a[1]));
		}
		return 0;
	}
	rep(i,1,n-1)st1[0][i]=2*a[i]-a[i+1];
	st1[0][n]=-1000000007;
	rep(i,2,n)st2[0][i]=2*a[i]-a[i-1];
	st2[0][1]=1000000007;
	rep(l,1,19){
		rep(i,1,n)if(i+(1<<(l-1))<=n)st1[l][i]=min(st1[l-1][i],st1[l-1][i+(1<<(l-1))]);else st1[l][i]=st1[l-1][i];
		per(i,n,1)if(i-(1<<(l-1))>=1)st2[l][i]=max(st2[l-1][i],st2[l-1][i-(1<<(l-1))]);else st2[l][i]=st2[l-1][i];
	}
	a[0]=-1000000007,a[n+1]=2000000014;
	rep(i,1,n){
		ll tl=i,tr=i;
		bool dir=0;
		if(a[i]-a[i-1]<=a[i+1]-a[i])dir=0;
		else dir=1;
		ll res=0;
		while(tl!=1||tr!=n){
			if(dir==0){
				ll pos=tl;
				per(j,19,0){
					if(pos<=(1<<j)+1)continue;
					ll o=st2[j][pos-1];
					if(o<=a[tr+1])pos-=(1<<j);
				}
				pos--;
				res+=a[tr]-a[pos];
				tl=pos;
				dir=1;
			}
			else{
				ll pos=tr;
				per(j,19,0){
					if(pos+(1<<j)>=n)continue;
					ll o=st1[j][pos+1];
					if(o>a[tl-1])pos+=(1<<j);
				}
				pos++;
				res+=a[pos]-a[tl];
				tr=pos;
				dir=0;
			}
		}
		ans[i]=res;
	}
	read(q);
	rep(i,1,q){
		ll in;
		read(in);
		ll o1=lower_bound(a+1,a+n+1,in)-a;
		ll o2=o1-1;
		if(in-a[o2]<=a[o1]-in)printf("%lld\n",ans[o2]+in-a[o2]);
		else printf("%lld\n",ans[o1]+a[o1]-in);
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

有点牛逼的性质题。

**[题目传送门](https://www.luogu.com.cn/problem/P9342)**

> - 数轴上有 $n$ 个 **从小到大** 的点 $(X_1,\dots,X_n)$。给出 $q$ 个询问。
> - 每个询问会给出一个点 $x$。有一只小 L 初始位于 $x$ 这个点，她会以一种规则行走以到达这 $n$ 个点。若当前小 L 在 $p$ 点，则她会选择最小的 $i$ 使得 $|X_i-p|$ 最小，且 $X_i$ 这个点未到达过。随后，她行走 $|X_i-p|$ 的距离到达 $X_i$ 这个点。若 $n$ 个点都被到达过一次，则整个过程结束。
> - 对于每个询问，求出小 L 行走的距离和。
> - $n,q\le 2\times 10^5$。

下文在描述数轴上的一个点时可能会将其在 $X$ 中的下标和她本身的值混用，请读者甄别。

首先询问的 $x$ 不一定在 $X$ 序列中，因此考虑先处理第一步行走。考虑找到她在 $X$ 中的前驱（最后一个 **不超过** 她的）和后继（第一个 **大于** 她的）然后选较小者并确定接下来行走的方向。此时若 $x$ 在 $X$ 中出现可能会选择错误的方向，但是接下来的做法会使得出现错误的方向时在这个方向上走 $0$ 步，因此不影响正确性。

接下来，所有行走的点都在序列中了。

观察一下性质，发现任意时刻小 L 到达的点都是 $p$ 这个位置在未到达点的集合中的前驱后继，不然对于不相邻的两个点而言，选取位于她们之间的点一定使得距离更短。因此我们有结论：

> $\bf{Obversation\space\space 1}$
>
> 任意时刻小 L 到达的点的集合是 $(X_1,\dots,X_n)$ 中的一个区间，且小 L 一定位于这个区间的端点。
>
> $\bf{Proof}\space\space 1$
>
> 考虑使用数学归纳法。
>
> - 对于第一次行走，到达的点是一个长度为 $1$ 的区间。
> - 若行走 $k$ 次后得到的点构成了 $X$ 序列上的区间 $[L_k,R_k]$，且小 L 走完最后一次之后位于某个端点上，则行走第 $k+1$ 次后，她一定位于 $X_{L_{k}-1}$ 或 $X_{R_{k}+1}$ 中的某个点上。显然仍然构成一个区间，且新加入的点为端点。因此行走 $k+1$ 次后结论仍然是成立的。
>  
> $\mathcal{Q.E.D.}$

因此，小 L 行走的过程一定是往某个方向扩展若干步，再换方向拓展若干步……这样下去。我们考虑统计每一段同方向的行走的距离和。

特别地，对于两段行走之间换方向的那一步，我们认为她是前一段行走中的一部分。即，一段行走的形态形如向某个方向走 **连续** 的若干个点，然后再到达另一个方向的一个点。

在这样的规定下，一段行走可以仅由换方向的一步构成。

乍一眼看上去很暴力，但是我们还有一个很强的性质：

> $\bf{Obversation\space\space 2}$
>
> 设值域为 $V$，则对于一次行走，切换行走方向的次数为 $\mathcal{O}(\log |V|)$。
>
> $\bf{Proof\space\space 2}$
>
> 对于同一段方向的行走而言，她的第一步会选择未到达点中当前位置的前驱或后继。我们称未被选择的那个点为这一段行走的 **劣势点**。显然，一段行走换方向之后会到达她的 **劣势点**。
>
> 称一段行走的起点与 **劣势点** 的距离为 **劣势距离**。显然，劣势距离为某个点前驱、后继与她的距离的最大值。
>
> 以往左走再切换为往右走为例。设进行这一段向左的行走 **之前** 得到的区间为 $[l,r]$；这一段向左的行走结束后，得到的区间为 $[l',r]$。
>
> 可以得到向左的这一段行走的 **劣势点** 为 $X_{r+1}$，向右这一段行走的 **劣势点** 为 $X_{l'-1}$ 或 $X_{r+2}$ 中的一个。则向左走的 **劣势距离** 为 $X_{r+1}-X_l$，向右走的 **劣势距离** 为 $\max\{X_{r+2}-X_{r+1},X_{r+1}-X_{l'-1}\}\ge X_{r+1}-X_{l'-1}$。
>
> 注意到由向左切换为向右时，一定满足 $X_{l'}-X_{l'-1}>X_{r+1}-X_{l'}\ge X_{r+1}-X_l$。因此：
>
> $$\color{red}\boldsymbol{X_{r+1}-X_{l'-1}= X_{l'}-X_{l'-1}+X_{r+1}-X_{l'}\ge 2(X_{r+1}-X_l)}$$
>
> 所以每到一段新的行走，其 **劣势距离** 至少是之前一段行走的两倍。而 **劣势距离** 为 $(X_1,\dots,X_n)$ 中某两个点的距离，不超过值域大小 $|V|$，因此只会进行 $\mathcal{O}(\log |V|)$ 次行走。
>
> 从向右行走切换到向左行走的情况类似。
>
> $\mathcal{Q.E.D.}$

于是我们暴力的想法就正确了。考虑在一次同方向的行走中快速找到换方向的临界点。

以向右行走为例，设行走前的区间为 $[L,R]$。考虑小 L 从 $X_p$ 走到临界点 $X_x$，记最后一步由 $X_y$ 这个点向右一步到达 $X_x$，显然 $y=x-1$。

那么对于这一段行走中的点，一定满足 $\forall\,i\in[p,y],X_{i+1}-X_i<X_i - X_{L - 1}$，不然小 L 会选择往左边走。并且对于 $X_y$ 这个点而言，$X_{y+1}-X_y\ge X_{y}-X_{L-1}$，因为这里换了方向。

因此，$y$ 为最大的下标，满足 $\forall\,i\in[p,y],X_{i+1}-X_i<X_i - X_{L - 1}$。移项得 $2X_i-X_{i+1}>X_{L-1}$。$X_{L-1}$ 为定值，只需要左边的最小值大于她就行。

用 ST 表维护 $2X_i-X_{i+1}$ 的最小值，根据 $\min$ 的性质，这个东西一定是随着 $y$ 的增大而不升的，二分得到 $y$ 即可。

还记得前文说到的“走错误的方向”吗，经过这番分析下来可以发现，若选择了错误的方向，则会使得 $x$ 及她右边任意一个下标不满足成为 $y$ 的条件，从而 $X_x$ 自身成为临界点，不会贡献任何距离。

然后累加 $X_p$ 至 $X_{y}$ 的距离和即可，由于这一段 $X$ 递增，中间的项会被消掉，只剩下 $X_y-X_p$。向左行走的段类似计算。

接下来，若走完了所有点，则结束这个过程。否则扩展 $[L,R]$ 并切换方向。

那么这题基本就做完了。上述的分析均没有讨论边界情况  ，这部分容易特判，具体可以看代码。

时间复杂度为 $\mathcal{O}(q\log n\log|V|)$，空间复杂度为 $\mathcal{O}(n\log n)$。如果把二分 + ST 表换成线段树上二分可以做到线性空间。

[AC Link](https://www.luogu.com.cn/record/172643337)

[AC Code](https://www.luogu.com.cn/paste/jyg947z0)

~~这么说此题涉及到的知识点仅有二分和 ST 表，我反手扔母校普及组模拟赛。~~

---

## 作者：ethan0328 (赞：2)

## $思路$

考虑暴力做法。从一个点出发，每次找到未选中的点中离它最近的转移。时间复杂度 $O(qn)$。

考虑优化。我们发现改变转移方向的次数是 $\log{n}$ 级别的。这是可以证明的。

我们考虑何时转向。假使原来向右走，当 $a_i-a_l < a_r-a_i$ 时转向。显然 $a_i-a_l>a_i-a_{l+1}$，所以当 $a_r-a_i$ 比已走的区间长度小时，都不会转移。

令区间长度为 $len$，二分枚举 $a_i\pm len$ 的位置，并将边界转移。时间复杂度 $O(q\log^2{n})$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,q,ans,a[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int x,y,l,r,len;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>q;
	while(q--)
	{
		cin>>x;
		ans=0;
		y=lower_bound(a+1,a+1+n,x)-a-1;
		if(y==0)
		{
			ans+=a[y+1]-x;
			x=y+1;
		}else if(y==n)
		{
			ans+=x-a[y];
			x=y;
		}else if(x-a[y]<=a[y+1]-x)
		{
			ans+=x-a[y];
			x=y;
		}else
		{
			ans+=a[y+1]-x;
			x=y+1;
		}
		l=r=x;
		while(l>1&&r<n)
		{
			if(x==l)
			{
				len=a[r+1]-a[x];
				y=lower_bound(a+1,a+1+n,a[x]-len)-a;
				if(y<l)
				{
					ans+=a[x]-a[y];
					x=l=y;
				}else
				{
					x=r=r+1;
					ans+=len;
				}
			}else
			{
				len=a[x]-a[l-1];
				y=lower_bound(a+1,a+1+n,a[x]+len)-a-1;
				if(y>r)
				{
					ans+=a[y]-a[x];
					x=r=y;
				}else
				{
					x=l=l-1;
					ans+=len;
				}
			}
		}
		ans+=a[n]-a[1];
		cout<<ans<<endl;
	}
}
```


---

## 作者：UKE_Automation (赞：1)

### P9342 [JOISC 2023] Bitaro's Travel (Day4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P9342)

先找出位置 $x$ 第一个到达的点，接下来会发现我们走的路径一定是一段向右、一端向左，我们考虑何时会发生转折，假如当前我们在向右走，左边第一个没有走的点是 $a_l$，那么找出右边第一个 $i$ 满足 $a_i-a_l\le a_{i+1}-a_i$，即 $2a_i-a_{i+1}\le a_l$ 时我们要向左走到 $i$。

此时会发现一点，当我们转折后，$i+1$ 将会变成右边第一个没有走的点，$l$ 成为了新的起始点。此时考虑两者的差值，由于我们转折的时候要满足 $a_{i}-a_l\le a_{i+1}-a_i$，所以 $a_{i+1}-a_l\ge 2(a_i-a_l)$，那么每一次起始点和下一个未到达点之间的距离都会扩大一倍，显然总转折次数此时是 $O(\log V)$ 的。

那么有了这个条件我们就不用担心复杂度了，对于每一次转折利用上面的式子直接二分求出最远能走到的点，最后特判一下边界情况即可。复杂度 $O(n\log n\log V)$。

```cpp
#include <bits/stdc++.h>
#define il inline
#define int long long

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b, int P = Mod) {int res = 1; for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) res = 1ll * res * a % P; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, q, a[Maxn];
int st1[Maxn][20], st2[Maxn][20];

il int qmin(int l, int r) {
	int k = __lg(r - l + 1);
	return min(st1[l][k], st1[r - (1 << k) + 1][k]);
}

il int qmax(int l, int r) {
	int k = __lg(r - l + 1);
	return max(st2[l][k], st2[r - (1 << k) + 1][k]);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
signed main() {
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
    a[0] = -Inf, a[n + 1] = Inf; 
	for(int i = 1; i <= n; i++) st1[i][0] = 2 * a[i] - a[i + 1], st2[i][0] = 2 * a[i] - a[i - 1];
	st1[n][0] = -Inf, st2[1][0] = Inf + 1;
	for(int j = 1; j <= 18; j++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			st1[i][j] = min(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
			st2[i][j] = max(st2[i][j - 1], st2[i + (1 << j - 1)][j - 1]);
		}
	} 
	read(q);
	while(q--) {
		int x; read(x);
		int pos = lower_bound(a + 1, a + n + 1, x) - a;
		int l = 0, r = 0, res = 0, dir = 0; 
		if(a[pos] - x < x - a[pos - 1]) l = r = pos, dir = 1, res += a[pos] - x;
		else l = r = pos - 1, dir = 0, res += x - a[pos - 1];
		while(l != 1 && r != n) {
			if(dir == 1) {
				int L = r, R = n, nxt = 0;
				while(L <= R) {
					int mid = (L + R) >> 1;
					if(qmin(r, mid) <= a[l - 1]) nxt = mid, R = mid - 1;
					else L = mid + 1;
				}
				res += a[nxt] - a[r] + a[nxt] - a[l - 1];
				r = nxt, l--;
			}
			else {
				int L = 1, R = l, nxt = 0;
				while(L <= R) {
					int mid = (L + R) >> 1;
					if(qmax(mid, l) > a[r + 1]) nxt = mid, L = mid + 1;
					else R = mid - 1;
				}
				res += a[l] - a[nxt] + a[r + 1] - a[nxt];
				l = nxt, r++;
			}
			dir ^= 1;
		}
		if(l == 1 && r != n) {
			if(dir == 1) res += a[n] - a[r];
			else res += a[n] - a[l];
		}
		if(r == n && l != 1) {
			if(dir == 1) res += a[r] - a[1];
			else res += a[l] - a[1];
		}
		write(res);
	}
	Usd();
	return 0;
}
```

---

## 作者：OIer_Automation (赞：1)

首先我们走到的景点一定是一段连续的区间。接着我们考虑每次转换方向都一定意味着下一个点的距离超过了当前两个端点景点之间的距离，也就是说下一次走到这个景点两个端点景点之间的距离会翻一倍，而这样的景点是拐点产生的，由此我们推断出最多存在 $O(\log V)$ 个拐点，只需要能够快速找到这些拐点即可。

以找向右的拐点为例，现在我们走到了 $[L,R]$ 区间，考虑什么时候我们不会向右走而是会向左走，设一个 $L_p$ 表示 $p$ 如果不向右走到 $p+1$ 最远能向左走到的位置，那么就是存在一个 $p$ 使得 $L_p<L$，此时我们一定从 $p$ 走到 $L-1$，也就是要找到 $R$ 右边第一个 $L_p<L$ 的 $p$，这个利用 ST 表+二分可以简单实现，向左的拐点同理。最后特判边界情况统计答案即可，实现可以用记忆化优化掉同一个景点为起点的答案，总复杂度是 $O(n\log n\log V)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long

const int N=2e5+5,K=18;

int n,m;
int L[K][N],R[K][N],f[N];
ll a[N];

il void ST(){
	int l=__lg(n);
	for(int i=1;i<=n;i++)L[0][i]=lower_bound(a+1,a+1+n,(a[i]<<1)-a[i+1])-a,R[0][i]=lower_bound(a+1,a+1+n,(a[i]<<1)-a[i-1])-a-1;
	for(int p=1;p<=l;p++)for(int i=1,len=1<<(p-1),r=n-(len<<1)+1;i<=r;i++)
		L[p][i]=min(L[p-1][i],L[p-1][i+len]),R[p][i]=max(R[p-1][i],R[p-1][i+len]);
}
il int Min(int x,int y){int l=__lg(y-x+1);return min(L[l][x],L[l][y-(1<<l)+1]);}
il int Max(int x,int y){int l=__lg(y-x+1);return max(R[l][x],R[l][y-(1<<l)+1]);}
il void Build(){
	int v,l,r,p,ans=0;cin>>v;
	r=upper_bound(a+1,a+1+n,v)-a,l=r-1,v-a[l]<=a[r]-v?(ans=v-a[l],p=r=l):(ans=a[r]-v,p=l=r);
	if(f[p]!=-1)return cout<<ans+f[p]<<"\n",void();
	for(int op=0,pos,L,R;l!=1&&r!=n;op^=1){
		if(op){
			for(pos=r,L=r,R=n;L<=R;){int mid=(L+R)>>1;Min(L,mid)<l?pos=mid,R=mid-1:L=mid+1;}
			f[p]+=(a[pos]<<1)-a[l]-a[r],r=pos;
		}else{
			for(pos=l,L=1,R=l;L<=R;){int mid=(L+R)>>1;Max(mid,R)>r?pos=mid,L=mid+1:R=mid-1;}
			f[p]+=a[l]+a[r]-(a[pos]<<1),l=pos;
		}
	}
	f[p]++,cout<<ans+(f[p]+=l==1?a[n]-a[r]:a[l]-a[1])<<"\n";
}

int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,a[0]=-1e9-1,a[n+1]=2e9+1;
	for(int i=1;i<=n;i++)cin>>a[i],f[i]=-1;
	ST(),cin>>m;
	for(;m;m--,Build());
}
```

---

## 作者：许多 (赞：1)

通过题意不难知道，当下一个点的距离大于（或等于）身后最近的点时才会转向，为了方便理解，我们设身后的点距离为 $x$，在极端情况下，下一个点的距离也为 $x$，这个时候转向，则转向后身后的点距离为 $2x$，这个距离在最坏情况下是倍增的，即我们最多转向 $\log n$ 次。

那么我们肯定用一个倍增的算法来解决这个题，我们每次向前找 $x$ 个点，查看是否能往前走，如果能，则向前走并更新 $x$，不能则转向，这个找点的过程可以二分实现。则我们的总复杂度为 $O(Q \log ^2 n)$。

# CODE

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 222222
#define inf 2111111111
#define int long long 
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n,q;
int x[N];
signed main(){
    n=read();x[0]=-inf;x[n+1]=inf;
    for(int i=1;i<=n;i++)
        x[i]=read();
    q=read();
    while(q--){
        int now=read(),ans=x[n]-x[1];
        int l=lower_bound(x+1,x+2+n,now)-x-1,r=l+1,turn;
        if(now-x[l]<=x[r]-now){
            ans+=now-x[l];
            r=l;
            turn=0;// turn=0表示向左走，1则表示向右走
        }
        else {
            ans+=x[r]-now;
            l=r;
            turn=1;
        }
        while(l>1&&r<n){
            if(!turn){
                int dis=x[r+1]-x[l];
                int lnext=lower_bound(x+1,x+1+n,x[l]-dis)-x;
                if(lnext<l){
                    ans+=x[l]-x[lnext];
                    l=lnext;
                }
                else {
                    ans+=dis;
                    turn=1;
                    r++;
                }
            }
            else{
                int dis=x[r]-x[l-1];
                int rnext=lower_bound(x+1,x+1+n,x[r]+dis)-x-1;
                if(rnext>r){
                    ans+=x[rnext]-x[r];
                    r=rnext;
                }
                else {
                    ans+=dis;
                    turn=0;
                    l--;
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Raisetsu41 (赞：1)

能直接预处理所有答案吗？  
首先研究答案之间有没有啥关系，手玩发现不太行，于是提示是预处理每个点的答案的复杂度应该不怎么大。  
数据范围是 $2e5$，大概是两个 $\log$ 的。  
关键方法仍然是重新描述题目，检查刻画题目信息的要素，显然去刻画这条路径，要素是：起点，方向，拐点。因为可以用拐点的相对位置刻画方向，所以把方向省略掉。  
于是该路径就表示为 $(s, \{ t \})$，$\{ t \}$ 是包含所有拐点的有序集。  
考察如何生成 $\{ t \}$，先讨论 $x_{pos}$ 出现时调转方向往左走，当一个拐点 $x_{pos}$ 生成，只可能是 $x_{pos + 1} - x_{pos} > x_{pos} - x_{l - 1}$，其中 $l$ 是在 $pos$ 出现之前有序集中最小的下标编号，整理一下这个式子 $x_{pos + 1} + x_{l - 1} > 2x_{pos}$。所以 $x_{pos}$ 出现之后会意味着拐点之间的距离**至少翻倍**，向右调转方向是一个道理。拿到翻倍这个性质，得到 $\{ t \}$ 的大小是 $\log V$ 级别的。  
现在的目标是直接处理出来这个集合，首先在起点处判断一下第一步的方向，从直观感受或是上面的式子都很容易看到在过程中维护最左和最右的拐点即可，于是这一步的二分查找就很容易了。

---

