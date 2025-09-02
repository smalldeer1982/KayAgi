# [SDOI/SXOI2022] 整数序列

## 题目描述

小 D 三岁就学会了出题。

小 D 有一个正整数序列 $a_1, a_2, \dots a_n$ 和一个整数序列 $b_1, b_2, \dots ,b_n$。

小 D 有 $q$ 次查询，每次给出 $x, y$，构造一个新的序列 $c_1,c_2,\dots ,c_n$，其中 $c_i=\begin{cases}1 & a_i=x \\-1 & a_i = y \\ 0 & \text{else}\end{cases}$。

保证 $c_i$ 中至少存在一个 $1$ 与一个 $-1$。他想让你帮他找到一个区间 $[l,r]$，满足 $\sum\limits_{i = l}^r c_i = 0$，并使得 $\sum\limits_{i = l}^r b_i \times [c_i \neq 0]$ 最大，并且区间里的 $c_i$ 不能都为 $0$。你需要输出这个最大值。

注：当条件 $[P]$ 为真时，$[P]=1$，否则 $[P]=0$。

## 说明/提示

### 数据规模与约定
本题共 $20$ 个测试点。
- 对于测试点 $1,2,3,4$，保证 $n, q ≤5000$。
- 对于测试点 $5,6$，保证 $a$ 的取值不超过 $500$ 种。
- 对于测试点 $7,8$，保证 $n \le 150000$。$q \le 500000$，$b_i>0$。
- 对于测试点 $9$，保证 $n \le 150000$，$q \le 500000$。
- 对于测试点 $10,11$，保证 $n \le 200000$，$q \le 500000$。
- 对于测试点 $12,13,14$，保证 $b_i=1$。
- 对于测试点 $15,16$，保证 $b_i>0$。

对于所有测试点，$1 \le n \le 300000$，$1 \le q \le 1000000$，$1 \le a_i \le n$，$-10^9<b_i \leq 10^9$，$1 \leq x, y \leq n$，$x \neq y$，保证对于每次查询，$c_i$ 中均至少含有一个 $1$ 与一个 $-1$。



## 样例 #1

### 输入

```
5 3
1 2 3 1 2
-2 3 2 -1 2
1 2
1 3
2 3
```

### 输出

```
2
1
5
```

## 样例 #2

### 输入

```
见附加样例文件中的 ex_sequence2.in```

### 输出

```
见附加样例文件中的 ex_sequence2.out```

# 题解

## 作者：donghanwen1225 (赞：24)

upd on $2022-05-17$：补充了一些证明。

------------

SDOI 2022 D1T1。在考场上没有想出来小块对大块的做法，写了个 $O(q(len_x+len_y))$ 的暴力喜提 $\text{30pts}$。

------------

**Part 1 :** 考虑暴力该怎么做。

对于每次询问，首先我们将 $a_i=x$ 和 $a_i=y$ 的所有 $i$ 按照顺序放到一起。令这些 $i$ 组成的序列为 $p$，令 $len_x$ 表示整个 $a$ 序列中 $x$ 的数量，容易得到 $p$ 的长度为 $len_x+len_y$。

那么题意可以转化为，找出一个区间 $[l,r]$，使得 $\sum\limits_{i=l}^{r}[a_{p_i}=x]=\sum\limits_{i=l}^{r}[a_{p_i}=y]$，并令 $\sum\limits_{i=l}^{r}b_{p_i}$ 最大。

设当前考虑到了第 $i$ 个数，在 $p$ 序列的前 $i$ 个数中有 $c_1$ 个是 $x$，$c_2$ 个是 $y$，当前的 $b$ 数列的前缀和为 $sum_i$。令 $q_i=c_1-c_2+len_y$，可以发现，对两个相等的 $q_l,q_r$，区间 $[l,r]$ 是一个满足题意的区间。

考虑维护当前每个 $q_i$ 所对应的 $sum_i$ 的最小值 $mn_{q_i}$。那么在计算到 $i$ 时，只需将答案与 $sum_i-mn_{q_i}$ 比较取最大值即可。另外若 $c_1=c_2$，即 $q_i=len_y$ 时，答案也可以直接更新为当前的前缀和。

时间复杂度为 $O(q(len_x+len_y))$。

**Part 2 :** 考虑根号平衡。

思考为什么上面的暴力无法通过此题。假设 $a$ 序列是这样构成的：其中有 $\dfrac{n}{2}$ 个 $1$，剩余 $\dfrac{n}{2}$ 个全部不同。那么只要每次询问 $1,i$，时间复杂度就将达到 $O(n^2)$。

我们根据 $len_i$ 大小是否达到 $B$，将数分为 “大块” 和 “小块” 两类。

下面分三类讨论：

**1.** 小块对小块。显然直接套用暴力即可。复杂度为 $O(qB)$。

**2.** 大块对大块。因为大块的长度要超过 $B$，所以大块最多有 $\dfrac{n}{B}$ 个。本质不同的询问数只有 $\dfrac{n^2}{B^2}$ 种（对相同的询问，我们将答案用 `unordered_map` 存下来，如果遇到相同的询问直接调用答案即可），直接套用暴力，这部分的复杂度最大为 $O\left(\dfrac{n^2}{B}\right)$。

**3.** 小块对大块。现在我们不能将两部分直接拼起来了。

考虑利用小块的大小不超过 $B$ 的性质。根据暴力的做法，我们将 $p$ 序列中的数分为**有效点**和**无效点**两类。

显然，小块中每个点都是需要考虑在内的有效点。

然而大块中，许多点对答案是不可能产生贡献的。这是因为，选中的区间 $[l,r]$ 中，$x$ 和 $y$ 的数量必须相等，而大块因为点数多，而往往导致其远远压过小块，所以有很多点是无效点。

具体的，我们仍然考虑 $p$ 序列，令 $len_x\leq B<len_y$，

设 $p$ 中有一段极长的 $x$ 连续子段，其长度为 $l$，这个连续子段的左右端点分别为 $L,R$。那么，$p$ 序列中只有在 $L$ 左侧和 $R$ 右侧的 $l+1$ 个 $y$ 才可能成为有效点。这是因为，更多的 $y$ 会压过 $x$ 的个数。我们把这些点加入真正计算的 $p$ 序列中。

另外注意，若 $L$ 左侧 $l+1$ 个 $y$ 中间还包含了另外一些 $x$ 的极长连续子段，则这些 $x$ 子段向两侧拓展时要跳过这些已经成为有效点的 $y$。这个过程可以使用 `set` 去快速维护。

得到有效点后将其离散化，再套用暴力即可。有效点的个数始终只与大小 $\leq B$ 的小块相关，所以是 $O(B)$ 级别的。

考虑到大块的数量不多，且复杂度取决于实际的小块长度，这部分的复杂度应当为 $O\left(\dfrac{n^2\log n}{B}\right)$。虽然有效点个数带大常数，但从下面的复杂度分析来看，实际上还要带一个非常小的常数，整体来看常数较小。

大块对大块的复杂度较小直接忽略，总复杂度为 $O\left(qB+\dfrac{n^2\log n}{B}\right)$。由均值不等式，在 $B=\sqrt{\dfrac{n^2\log n}{q}}$ 时，复杂度为 $O\left(n\sqrt{q\log n}\right)$ 最优。这式子看起来好像能达到 $10^9$，不过因为跑不满 + 常数小，而且时限 $7s$，所以是可以通过的。

按理论计算出来 $B=1200$ 左右最优，但由于数据非常离谱，实际上取 $100,200,300,550$ 时间都差不多，但是取 $1000$ 的时候反而会 TLE。这样就通过了此题。

代码中为了简便，拓展 $l+1$ 个有效点时直接是拓展了 $2l$ 个。

------------

upd 1：补充大块对大块、小块对大块的复杂度的证明。

大块对大块：假设有 $k$ 个大块，第 $i$ 个的长度为 $len_i$。极限情况下令 $\sum\limits_{i=1}^{k}len_i=n$。

考虑令这 $k$ 个大块两两配对进行询问，共进行 $\dfrac{k(k-1)}{2}$ 次询问。总计算次数为 $\sum\limits_{1\leq i<j\leq k}len_i+len_j=(k-1)\sum\limits_{i=1}^{k}len_i=n(k-1)$。

由于 $len_i\geq B$，得 $k\leq\dfrac{n}{B}$，故极限复杂度为 $O\left(\dfrac{n^2}{B}\right)$。

小块对大块：设有 $k_1$ 个大块，第 $i$ 个的长度为 $l_i$；有 $k_2$ 个小块，第 $i$ 个的长度为 $L_i$。则有 $\sum\limits_{i=1}^{k_1}l_i+\sum\limits_{i=1}^{k_2}L_i=n$。

考虑到小块对大块的复杂度只取决于小块长度，我们用最长的 $\dfrac{q}{k_1}$ 个小块对着大块进行询问。极限情况下，有 $k_2=\dfrac{q}{k_1}$，也即每个小块都对着每个大块查了一次。总计算次数为 $\sum\limits_{i=1}^{k_2}\sum\limits_{j=1}^{k_1}L_i\log l_j\leq k_1\log n\sum\limits_{i=1}^{k_2}L_i$。

最强的情况下，可构造 $\dfrac{n}{2B}$ 个长度略大于 $B$ 的大块，和总长度大约为 $\dfrac{n}{2}$ 的一些小块，此时 $k_1\approx\dfrac{n}{B},\sum\limits_{i=1}^{k_2}L_i\approx n$，故极限复杂度为 $O\left(\dfrac{n^2\log n}{B}\right)$。此时要有 $k_2\leq\dfrac{qB}{n}$。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
typedef long long ll;
const int blo=300;
int n,q,x,y,a[300005],len[300005],st[300005],tim[300005],pre[300005],cl[300005];
ll b[300005],mn[300005];unordered_map<int,ll> mp[300005];set<int> pos[300005];
struct node{int id;ll v;} xl[300005];
vector<node> tj[300005];vector<ll> qz[300005];
template<typename T> void Read(T &x)
{
	x=0;bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=f||(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	x=f==0?x:-x;
}
int main()
{
	Read(n);Read(q);
	for(int i=1;i<=n;i++) Read(a[i]),tim[i]=tim[pre[a[i]]]+1,pre[a[i]]=i;
	for(int i=1;i<=n;i++) Read(b[i]);
	for(int i=1;i<=n;i++) tj[a[i]].push_back({i,b[i]}),pos[a[i]].insert(i);
	for(int i=1;i<=n;i++)
		if(tj[i].size())
		{
			len[i]=tj[i].size();qz[i].resize(len[i]+1);
			for(int j=0;j<len[i];j++) qz[i][j+1]=qz[i][j]+tj[i][j].v;
		}
	for(int i=0;i<=n;i++) mn[i]=1ll<<60;
	while(q--)
	{
		Read(x);Read(y);
		if(mp[x].find(y)!=mp[x].end()){printf("%lld\n",mp[x][y]);continue;}
		if((len[x]>blo&&len[y]>blo)||(len[x]+len[y]<=blo))
		{
			int tl=0,tr=0;ll ans=-(1ll<<60);
			while(tl<len[x]&&tr<len[y])
			{
				if(tj[x][tl].id<tj[y][tr].id) xl[tl+tr]=tj[x][tl],tl++;
				else xl[tl+tr]=tj[y][tr],tr++;
			}
			while(tl<len[x]) xl[tl+tr]=tj[x][tl],tl++;
			while(tr<len[y]) xl[tl+tr]=tj[y][tr],tr++;
			int cur1=0,cur2=0;
			for(int i=0;i<len[x]+len[y];i++)
			{
				if(a[xl[i].id]==x) cur1++;
				if(a[xl[i].id]==y) cur2++;
				int sl=cur1-cur2+len[y];
				if(sl==len[y]) ans=max(ans,qz[x][cur1]+qz[y][cur2]);
				ans=max(ans,qz[x][cur1]+qz[y][cur2]-mn[sl]);
				mn[sl]=min(mn[sl],qz[x][cur1]+qz[y][cur2]);cl[i]=sl;
			}
			mp[x][y]=mp[y][x]=ans;printf("%lld\n",ans);
			for(int i=0;i<len[x]+len[y];i++) mn[cl[i]]=1ll<<60;
		}
		else
		{
			if(len[x]>len[y]) swap(x,y);
			int top=0;ll ans=-(1ll<<60);
			for(int i=0;i<len[x];i++)
			{
				if(!pos[y].size()) continue;
				auto tmp=pos[y].lower_bound(tj[x][i].id);
				if(tmp==pos[y].begin()) continue;--tmp;st[++top]=*tmp;
				auto del=tmp;if(tmp==pos[y].begin()) continue;--tmp;
				st[++top]=*tmp;pos[y].erase(del);pos[y].erase(tmp);
			}
			for(int i=0;i<len[x];i++)
			{
				if(!pos[y].size()) continue;
				auto tmp=pos[y].upper_bound(tj[x][i].id);
				if(tmp==pos[y].end()) continue;st[++top]=*tmp;
				auto del=tmp;++tmp;if(tmp==pos[y].end()) continue;
				st[++top]=*tmp;pos[y].erase(del);pos[y].erase(tmp);
			}
			for(int i=1;i<=top;i++) pos[y].insert(st[i]);
			for(int i=0;i<len[x];i++) st[++top]=tj[x][i].id;
			sort(st+1,st+1+top);int cnt=unique(st+1,st+1+top)-st-1;
			for(int i=1;i<=cnt;i++) xl[i]={st[i],b[st[i]]};
			int cur1=0,cur2=0,las1=0,las2=0;
			for(int i=1;i<=cnt;i++)
			{
				if(a[xl[i].id]==x) cur1+=tim[xl[i].id]-las1,las1=tim[xl[i].id];
				if(a[xl[i].id]==y) cur2+=tim[xl[i].id]-las2,las2=tim[xl[i].id];
				int sl=cur2-cur1+len[x];
				if(sl==len[x]) ans=max(ans,qz[x][cur1]+qz[y][cur2]);
				ans=max(ans,qz[x][cur1]+qz[y][cur2]-mn[sl]);
				mn[sl]=min(mn[sl],qz[x][cur1]+qz[y][cur2]);cl[i]=sl;
			}
			mp[x][y]=mp[y][x]=ans;printf("%lld\n",ans);
			for(int i=1;i<=cnt;i++) mn[cl[i]]=1ll<<60;
		}
	}
	return 0;
}
```

---

## 作者：whiteqwq (赞：15)

[P8349 [SDOI/SXOI2022] 整数序列](https://www.luogu.com.cn/problem/P8349) 解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/16281978.html)

## 题意

给定序列 $a,b$，$q$ 次询问两种颜色 $(x,y)$，定义一个区间的权值为其中 $a$ 值为 $x$ 或 $y$ 的 $b$ 值之和，求 $x$ 数量等于 $y$ 数量的子区间权值最大值。

$1\leqslant n\leqslant 3\times 10^5,1\leqslant q\leqslant 10^7,\text{7s}$。

## 分析

轻视了这道题啊。

考虑根号分治，令阈值为 $S$。

小集合对小集合直接把位置归并成一个序列暴力扫一遍即可，大集合对大集合可以直接暴力+记忆化，这里的复杂度是 $O(qS+\frac{n^2}{S})$。

难点主要是小集合对大集合（令 $x$ 为小集合，$y$ 为大集合），我们发现我们将 $x$ 和 $y$ 对应位置取出来之后，对于一个 $y$ 连续段，只要其长度大到没有合法子区间能跨越它，那么它的长度就是无关紧要的了，可以缩到恰好满足条件的长度。

更具体地说，我们维护一个 $y$ 坐标集合，对于每个长度为 $x$ 的连续段，都向前找 $x+1$ 个没加入集合的 $y$ 加入集合，向后找 $x+1$ 个没加入集合的 $y$ 加入集合，那么保留集合内的 $y$ 与 $x$ 进行运算也能保证答案的正确性。

而这样得到的集合大小是不超过 $2S$ 的，那么我们得到了一个 $O(qS\log n+\frac{n^2}{S})$ 的做法，令 $S=\frac{n}{\sqrt{q\log n}}$ 就是 $O(n\sqrt{q\log n})$ 了。

实际上这个 $\log$ 可以去掉。我们离线，把询问挂在对应大集合上。

扫两遍，分开维护向左取的 $y$ 和向右取的 $y$，每次用一个栈维护若干个连续的连续段集合，判断新加入的集合能否和栈顶合并显然可以 $O(1)$。最后我们将每个连续段内部的 $y$ 以及其向左（或向右）还能扩展的 $y$ 加入集合即可。

这样的复杂度就是 $O(qS+\frac{n^2}{S})$ 了，令 $S=\frac{n}{\sqrt q}$ 即可得到 $O(n\sqrt q)$ 的复杂度。

## 代码
```
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<map>
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
using namespace std;
const int maxn=300005,maxq=1000005,S=300;
int n,m,ps,top,tmps,stp;
int a[maxn],b[maxn],stk[maxn][3],pos[maxn],tmp[maxn],tmpp[maxn],c[maxn],xx[maxq],yy[maxq],cnt[maxn],vis[maxn];
long long inf;
long long ans[maxq],mn[maxn<<1];
vector<int>v[maxn],q[maxn];
map<pair<int,int>,long long>mp;
long long solve(int x,int y){
	for(int i=1;i<=ps;i++)
		c[i]=c[i-1]+(a[pos[i]]==x? 1:-1);
	long long res=-1e18,s=0;
	mn[ps]=0;
	for(int i=1;i<=ps;i++)
		s+=b[pos[i]],res=max(res,s-mn[c[i]+ps]),mn[c[i]+ps]=min(mn[c[i]+ps],s);
	for(int i=0;i<=ps;i++)
		mn[c[i]+ps]=inf;
	return res;
}
void read(int &x){
	x=0;
	char c=getchar();
	int f=0;
	for(;c<'0'||c>'9';c=getchar())
		f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-48;
	if(f==1)
		x=-x;
}
void print(long long x){
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		print(x/10);
	putchar(x%10+48);
}
int main(){
//	freopen("tmp.in","r",stdin);
//	freopen("tmp.out","w",stdout);
	memset(mn,127,sizeof(mn)),inf=mn[0];
	read(n),read(m);
	for(int i=1;i<=n;i++)
		read(a[i]),v[a[i]].push_back(i);
	for(int i=1;i<=n;i++)
		read(b[i]);
	for(int t=1,x,y;t<=m;t++){
		read(x),read(y),xx[t]=x,yy[t]=y;
		if((v[x].size()>S)+(v[y].size()>S)==1){
			if(v[x].size()>S)
				q[x].push_back(t);
			else q[y].push_back(t);
			continue;
		}
		if(mp.count(make_pair(min(x,y),max(x,y)))){
			ans[t]=mp[make_pair(min(x,y),max(x,y))];
			continue;
		}
		int i=0,j=0;
		ps=0;
		while(i<v[x].size()||j<v[y].size()){
			if(i<v[x].size()&&(j==v[y].size()||v[x][i]<v[y][j]))
				pos[++ps]=v[x][i],i++;
			else pos[++ps]=v[y][j],j++;
		}
		ans[t]=mp[make_pair(min(x,y),max(x,y))]=solve(x,y);
	}
	for(int t=1;t<=n;t++)
		if(v[t].size()>S&&q[t].size()){
			for(int i=1;i<=n;i++)
				cnt[i]=cnt[i-1]+(a[i]==t);
			for(int p=0;p<q[t].size();p++){
				int k=q[t][p],r=xx[k]+yy[k]-t;
				ps=top=tmps=0,stp++;
				for(int i=0;i<v[r].size();i++)
					pos[++ps]=v[r][i];
				for(int i=0;i<v[r].size();i++){
					int j=i;
					while(j+1<v[r].size()&&cnt[v[r][j+1]-1]==cnt[v[r][j]])
						j++;
					int p=v[r][i],q=v[r][j],c=j-i+2;
					while(top){
						int w=cnt[p-1]-cnt[stk[top][2]];
						if(w<=c)
							p=stk[top][1],c=c+stk[top][3]-w,top--;
						else break;
					}
					top++,stk[top][0]=c,stk[top][1]=p,stk[top][2]=q,i=j;
				}
				int lst=0;
				for(int i=1;i<=top;i++){
					int c=stk[i][0],p=stk[i][1],q=stk[i][2];
					lst=max(lst,cnt[p]-c);
					while(lst<=cnt[q]-1){
						if(vis[v[t][lst]]!=stp)
							tmp[++tmps]=v[t][lst],vis[v[t][lst]]=stp;
						lst++;
					}
				}
				merge(pos+1,pos+1+ps,tmp+1,tmp+1+tmps,tmpp+1);
				int tmpps=ps+tmps;
				tmps=top=0;
				for(int i=v[r].size()-1;i>=0;i--){
					int j=i;
					while(j>=1&&cnt[v[r][j-1]]==cnt[v[r][j]-1])
						j--;
					int p=v[r][j],q=v[r][i],c=i-j+2;
					while(top){
						int w=cnt[stk[top][1]-1]-cnt[q];
						if(w<=c)
							q=stk[top][2],c=c+stk[top][3]-w,top--;
						else break;
					}
					top++,stk[top][0]=c,stk[top][1]=p,stk[top][2]=q,i=j;
				}
				lst=cnt[n]-1;
				for(int i=1;i<=top;i++){
					int c=stk[i][0],p=stk[i][1],q=stk[i][2];
					lst=min(lst,cnt[q]+c-1);
					while(lst>=cnt[p]){
						if(vis[v[t][lst]]!=stp)
							tmp[++tmps]=v[t][lst],vis[v[t][lst]]=stp;
						lst--;
					}
				}
				reverse(tmp+1,tmp+1+tmps),merge(tmpp+1,tmpp+1+tmpps,tmp+1,tmp+1+tmps,pos+1);
				ps=tmpps+tmps,ans[k]=solve(t,r);
			}
		}
	for(int i=1;i<=m;i++)
		print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：critnos (赞：6)

发现了一个好的 trick。

设 $S_i$ 表示所有 $i$ 出现的下标。我们先记忆化对每对 $(x,y)$ 只计算一次。根据经典结论，$\sum \min(|S_x|,|S_y|)$ 是 $O(n\sqrt q)$ 的。不妨设 $|S_x|\le |S_y|$，$S_y$ 中的点可能成为区间端点的当且仅当其最大前缀或后缀和 $\ge 0$。容易发现这只有 $O(|S_x|)$ 个，可以全部求出来就做完了。

瓶颈在于，对所有 $S_x$ 中的数求出其在 $S_y$ 中的后继。这个可以通过根号分治，离线双指针之类的方法去掉二分的 $\log$，但很不优美，也比较劣。有更好的方法。

考虑做一个双指针，在移动指针的时候，先尝试跳 $1,2,4,8\dots 2^k$ 步，直到跳不了了就从当前的 $2^k$ 开始尝试跳 $2^{k-1},2^{k-2}\dots 1$ 步。根据 $\log$ 的凸性，算一次时间复杂度是 $O(|S_x|\log(|S_y|/|S_x|))$。

[代码实现](https://www.luogu.com.cn/paste/s4u763pj)

时间复杂度是 $O(n\sqrt q)$。下面是证明。

对所有大小在 $(2^{i-1},2^i]$ 中的集合一起作为 $S_x$ 考虑（显然其内部贡献是 $O(n\sqrt q)$），将其大小扩展到 $2^i$，记 $c_i$ 表示这样的集合数量，再把 $c_i$ 扩展到实数。

考虑将这些集合与 $|S_y|\ge2^i$ 的贡献最大化，即 $2^ic_i\sum_{|S_y|\ge 2^i} \log(|S_y|/2^i)$，$\sum_{|S_y|\ge 2^i} c_i\le q$，$\sum_{|S_y|\ge n} |S_y|\le n$。

根据 $\log$ 的凸性，所有 $|S_y|$ 相同，我们把其个数也扩展到实数。

如果 $n/2^i<q/c_i$，也就是 $|S_y|=2^i$ 还是不够 $q/c_i$ 个。贡献是 $nc_i$。考虑 $\sum_i \min(nc_i,q/2^i)=\sum_i \min(nc_i2^i,q)/2^i$。令 $t_i=nc_i2^i$，有 $\sum t_i=n^2$。显然从小往大分配 $t_i=q$ 是最优的，简单计算可知是 $O(n\sqrt q)$。

否则贡献是 $q2^i\log(nc_i/q/2^i)$，满足 $2^i\le n/\sqrt q$。沿用上面的 $t_i$ 就是 $q2^i\log(t_i/q/2^{2i})$，$t_i\ge q2^{2i}$。求导可知最大时满足所有 $q^22^{3i}/t_i$ 相等，计算得 $t_i=q^{1.5}2^{3i}/n$，满足限制条件。贡献和就是 $\sum q2^i\log(q^{0.5}2^i/n)$，是 $O(n\sqrt q)$。

---

## 作者：云浅知处 (赞：6)

考虑一组询问怎么做。注意到 $\sum_{i=l}^rc_i=0$ 等价于 $S_r=S_{l-1}$，其中 $S$ 是 $c$ 的前缀和。

对每种 $S$ 分别考虑，发现只需要求最大子段和。

由于区间的端点只会是 $x,y$ 出现的位置，不难得到 $O(c_x+c_y)$ 的做法，其中 $c_x$ 是 $x$ 的出现次数。

接下来考虑将序列按照 $x,y$ 的连续段分段，那么对于一个极长的 $y$ 连续段，若其长度为 $L$，只有它向前/向后的最开头 $L+1$ 个数是有效的。

> 许多题解没有提到啊，看上去只有 $L$ 个就够了，为什么需要 $L+1$ 个？
>
> 考虑这样的一段 `xxyyyyyyyyyyyyyxx`，那么左右两侧的 `xx` 是连不到一起的，但是如果我们只保留 $L$ 个，那么最后会留下来 `xxyyyyxx`，可能会把左右两侧的 `xx` 连到一起。如果这两个 `xx` 刚好权值都比较大就寄了对不对，因此方便的处理方式是保留 $L+1$ 个，或者也可以像 rsy 题解里那样保留 $L$ 个，然后每一段分别做。

这样就得到了 $O(\min(c_x,c_y))$ 的做法。

我们证明暴力记忆化的复杂度是对的：

- 若 $\min(c_x,c_y)\le \frac{n}{\sqrt{q}}$，则这部分复杂度不超过 $q\times \frac{n}{\sqrt{q}}=n\sqrt{q}$。
- 若 $\min(c_x,c_y)>\frac{n}{\sqrt{q}}$，这样的 $x$ 至多 $\sqrt{q}$ 个，对于每个 $x$，由于 $y$ 同样也只有 $\sqrt{q}$ 个，对所有 $c_y>\frac{n}{\sqrt{q}}$ 的 $y$ 求和 $\min(c_x,c_y)$ 的结果不会超过 $\sum_y c_x+c_y\le n+c_x\times \sqrt{q}$，再把这一结果对 $x$ 求和就得到了这部分的复杂度同样是 $O(n\sqrt{q})$。

总复杂度 $O(n\sqrt{q})$。多一个 $\log$ 或许也无所谓？

[代码](https://www.luogu.com.cn/paste/sj9y7zr7)

---

## 作者：Renshey (赞：5)

#### 题解。

考虑将出现数量 $\le B$ 与 $>B$ 的分开处理。不妨设 $cnt_x \le cnt_y$。

1. $cnt_x \le B,cnt_y \le B$

将两个序列归并在一起后可以 $O(B)$ 暴力，时间复杂度 $O(qB)$。

2. $cnt_x > B, cnt_y > B$

本质不同的询问不会太多，考虑每个 $x$ 对应的 $\sum cnt_y \le n$，则 $\sum cnt_x + cnt_y \le \frac{n}{B} \times \sum cnt_y \le \frac{n^2}{B}$，仍然归并在一起暴力，时间复杂度 $O(\frac{n^2}{B})$。

3. $cnt_x \le B, cnt_y > B$

考虑离线，对于每个 $y$ 处理所有 $x$ 的答案。不难发现对于一组 $(x,y)$，$y$ 中只有 $O(B)$ 个数是有可能对答案产生贡献的，如果和 $x$ 中的数间隔过远就不需要考虑。于是可以对于 $x$ 中的每个位置 $p$ 分析，如果 $x$ 只取这一个 $p$，那么只需要找到 $p$ 向前/后第一个 $y$ 进行匹配。因此对于每个 $p$ 可以找到一个二元组 $(pre_p, nxt_p)$，接下来考虑相邻的二元组的合并关系，只要两段之间没有间隔一个 $y$ 就可以拼接，重叠的部分需要额外在两侧都补上。最后对于每一段做一次暴力即可。对于每个 $y$ 可以 $O(n)$ 预处理所有信息，然后用栈维护上述过程，时间复杂度 $O(\frac{n^2}{B}+qB)$。

综上，时间复杂度 $O(\frac{n^2}{B}+qB)$，取 $B = \frac{n}{\sqrt q}$ 时得到最小值 $O(n\sqrt{q})$，空间复杂度 $O(n+q)$。

#### 代码

```cpp
#include <bits/stdc++.h>
#define Getchar() p1 == p2 and (p2 = (p1 = Inf) + fread(Inf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
#define Putchar(c) p3 == p4 and (fwrite(Ouf, 1, 1 << 21, stdout), p3 = Ouf), *p3++ = c
char Inf[1 << 21], Ouf[1 << 21], *p1, *p2, *p3 = Ouf, *p4 = Ouf + (1 << 21);
inline int read (void)
{
	int x = 0; char c = Getchar(); bool f = (c != '-');
	while (c < '0' or c > '9') c = Getchar(), f &= c != '-';
	while (c >= '0' and c <= '9') x = x * 10 + c - 48, c = Getchar();
	return f ? x : -x;
}
inline void write (long long x)
{
	if (x < 0) Putchar('-'), x = -x;
	if (x >= 10) write(x / 10), x %= 10;
	Putchar(x ^ 48);
}
const long long inf = 1LL << 60;
const int maxn = 300000 + 10;
int n, m, q, B, a[maxn], b[maxn]; long long ans[1 << 20];
int cnt[maxn], pre[maxn], nxt[maxn], pos[maxn], id[maxn];
std::pair<int, int> st[maxn]; int tp;
std::vector<int> g[maxn];
std::vector<std::pair<int, int>> Q[maxn];
std::unordered_map<int, long long> map[maxn];
inline std::vector<int> merge (std::vector<int> A, std::vector<int> B)
{
	std::vector<int> C;
	for (int p = 0, q = 0; p < (int)A.size() or q < (int)B.size(); )
		C.push_back(p < (int)A.size() and (q == (int)B.size() or A[p] < B[q]) ? A[p++] : B[q++]);
	return C;
}
inline long long calc (std::vector<int> c, int x, int y)
{
	static int val[maxn]; static long long sum[maxn], min[maxn << 1];
	long long res = -inf; int m = (int)c.size();
	for (int i = 1; i <= m; i++) val[i] = val[i - 1] + (a[c[i - 1]] == x ? 1 : -1), sum[i] = sum[i - 1] + b[c[i - 1]];
	for (int i = 0; i <= 2 * m; i++) min[i] = i == m ? 0 : inf;
	for (int i = 1; i <= m; i++) res = std::max(res, sum[i] - min[val[i] + m]), min[val[i] + m] = std::min(min[val[i] + m], sum[i]);
	return res;
}
inline long long force (int x, int y)
{
	if (x > y) std::swap(x, y);
	if (map[x].count(y)) return map[x][y];
	return map[x][y] = calc(merge(g[x], g[y]), x, y);
}
signed main ()
{
	n = read(); q = read(); B = n / sqrt(q);
	for (int i = 1; i <= n; i++) g[a[i] = read()].push_back(i);
	for (int i = 1; i <= n; i++) b[i] = read();
	for (int i = 1; i <= q; i++)
	{
		int x = read(), y = read();
		if (g[x].size() > g[y].size()) std::swap(x, y);
		if ((int)g[x].size() > B or (int)g[y].size() <= B) {ans[i] = force(x, y); continue;}
		Q[y].push_back({x, i});
	}
	for (int x = 1; x <= n; x++) if (!Q[x].empty())
	{
		m = 0; nxt[n + 1] = n + 1;
		for (int i = 1; i <= n; i++) cnt[i] = cnt[i - 1] + (a[i] == x);
		for (int i = 1; i <= n; i++) pre[i] = a[i] == x ? i : pre[i - 1];
		for (int i = n; i >= 1; i--) nxt[i] = a[i] == x ? i : nxt[i + 1];
		for (int i = 1; i <= n; i++) if (a[i] == x) pos[id[i] = ++m] = i;
		pos[id[n + 1] = ++m] = n + 1; cnt[n + 1] = cnt[n];
		for (auto [y, k]: Q[x])
		{
			ans[k] = -inf; tp = 0;
			for (int p: g[y])
			{
				std::pair<int, int> w = {pre[p], nxt[p]};
				while (tp and id[st[tp].second] + 1 >= id[w.first])
				{
					if (st[tp].first < w.first) std::swap(st[tp].first, w.first);
					if (st[tp].second > w.second) std::swap(st[tp].second, w.second);
					int r = cnt[st[tp].second] - cnt[st[tp].first - 1]; tp--;
					w.first = pos[std::max(id[w.first] - r, 0)];
					w.second = pos[std::min(id[w.second] + r, m)];
				}
				st[++tp] = w;
			}
			for (int i = 1, l = 0, r = -1; i <= tp; i++, l = r + 1)
			{
				while (r + 1 < (int)g[y].size() and g[y][r + 1] <= st[i].second) r++;
				std::vector<int> A, B;
				for (int j = cnt[st[i].first - 1] + 1; j <= cnt[st[i].second]; j++) A.push_back(pos[j]);
				for (int j = l; j <= r; j++) B.push_back(g[y][j]);
				ans[k] = std::max(ans[k], calc(merge(A, B), x, y));
			}
		}
	}
	for (int i = 1; i <= q; i++) write(ans[i]), Putchar('\n');
	fwrite(Ouf, 1, p3 - Ouf, stdout); fflush(stdout);
	return 0;
}
```

---

## 作者：FjswYuzu (赞：5)

先做掉 ZJOI2022 众数，这个题就显得比较简单了。

一眼顶针没感觉到有什么 $\log$ 的可能性，考虑到每次给两个颜色可能需要一个根号做法。

先想如何暴力。现在我们把 $c_i$ 不是 $0$ 的位置拿出来拍成序列，其长度为 $L$。做一个 $c$ 的前缀和得到 $C$，再做一个 $b$ 的前缀和得到 $B$。容易发现对于所有 $C_{l-1}=C_r$ 的 $[l,r]$ 合法，因此 $B_r-B_{l-1}$ 可以作为答案（特殊的，我们令 $C_0=0$）。这样的话通过 `unordered_map` 就可以做到 $O(L)$。

总不可能分块吧……那么分治，把颜色按出现次数分类，一种是出现次数不多于 $B$ 次的，一种是出现次数多于 $B$ 次的，然后询问给定两种颜色，询问时将  $c_i=0$ 的位置全部扔掉，分类讨论：

- 两种颜色出现次数都不多于 $B$ 次：这样序列长度不足 $2B$，可以 $O(B)$ 暴力；   
- 两种颜色出现次数都大于 $B$ 次：最坏情况下查询完所有本质不同的询问，总共有 $O\left(\dfrac{n}{B}\right)$ 个出现次数大于 $B$ 次的颜色，那么时间复杂度是 $O\left(\dfrac{n^2}{B}\right)$ 的；   
- 一种颜色出现次数不多于 $B$ 次，另一种颜色出现次数大于 $B$ 次：这个东西比较麻烦，我们暂时没有好的方法保证复杂度。

注意到，一种颜色出现次数不足 $B$，同时这意味着选择的方案中另一种颜色出现的最多次数也是 $B$，因此另一种颜色中有很多东西我们并不需要。我们找到所有的可能需要的位置就好了，容易证明可能的位置集合大小也是 $O(B)$ 的。

这样我们转化成了两种颜色出现次数不多于 $O(B)$ 次，这样就可以再暴力了。平衡复杂度，$B$ 取 $\sqrt n$，可以做到 $O(n \sqrt n)$。

下面的代码中用了很多 `vector` 所以很慢，同时上面的暴力在代码里面改成了后缀和，原因懂得都懂。在找需要的位置的时候比较麻烦，如果要借鉴实现需要留心一下那里。

[完整代码](https://www.luogu.com.cn/paste/xdm3hvni)。

```cpp
const LL Brk=550;
#define mp make_pair
#define len(x) (LL(x.size()))
map<LL,LL> Ans[300005];
LL n,a[300005],b[300005];
vector<LL> Pos[300005];
LL Solve(vector<LL> A,vector<LL> B)
{
	unordered_map<LL,LL> M;
	LL ret=-inf,sum=0,pc=0;
	M[0]=0;
	while(!A.empty() || !B.empty())
	{
		if(A.empty())
		{
			LL p=B.back();
			B.pop_back();
			--sum;
			pc+=b[p];
			if(M.find(sum)!=M.end())	ret=max(ret,pc-M[sum]),M[sum]=min(M[sum],pc);
			else	M[sum]=pc;
		}
		else if(B.empty())
		{
			LL p=A.back();
			A.pop_back();
			++sum;
			pc+=b[p];
			if(M.find(sum)!=M.end())	ret=max(ret,pc-M[sum]),M[sum]=min(M[sum],pc);
			else	M[sum]=pc;
		}
		else
		{
			LL u=A.back(),v=B.back();
			if(u<v)
			{
				LL p=B.back();
				B.pop_back();
				--sum;
				pc+=b[p];
				if(M.find(sum)!=M.end())	ret=max(ret,pc-M[sum]),M[sum]=min(M[sum],pc);
				else	M[sum]=pc;
			}
			else
			{
				LL p=A.back();
				A.pop_back();
				++sum;
				pc+=b[p];
				if(M.find(sum)!=M.end())	ret=max(ret,pc-M[sum]),M[sum]=min(M[sum],pc);
				else	M[sum]=pc;
			}
		}
	}
	return ret;
}
int main(){
	LL T;
	n=read(),T=read();
	for(LL i=1;i<=n;++i)	a[i]=read();
	for(LL i=1;i<=n;++i)	b[i]=read();
	for(LL i=1;i<=n;++i)	Pos[a[i]].push_back(i);
	for(LL C=1;C<=T;++C)
	{
		LL x=read(),y=read();
		if(Ans[x].find(y)!=Ans[x].end())	write(Ans[x][y]),puts("");
		else
		{
			if((len(Pos[x])<=Brk && len(Pos[y])<=Brk) || (len(Pos[x])>=Brk && len(Pos[y])>=Brk))
			{
				LL ans=Solve(Pos[x],Pos[y]);
				Ans[x][y]=Ans[y][x]=ans;
				write(ans),puts("");
			}
			else
			{
				if(len(Pos[x])>len(Pos[y]))	swap(x,y);
				vector<LL> A,B;
				LL ans=-inf;
				LL reach;
				reach=-1;
				for(LL i=0;i<len(Pos[x]);++i)
				{
					LL p=Pos[x][i];
					auto it=upper_bound(Pos[y].begin(),Pos[y].end(),p);
					LL st=i;
					while(i<len(Pos[x]) && upper_bound(Pos[y].begin(),Pos[y].end(),Pos[x][i])==it)	++i;
					--i;
					LL d=i-st+1;
					if(it==Pos[y].end())
					{
						if(max(len(Pos[y])-d,0ll)>reach+1)
						{
							ans=max(ans,Solve(A,B));
							A.clear(),B.clear();
						}
						for(LL j=st;j<len(Pos[x]);++j)	A.push_back(Pos[x][j]);
						for(LL j=max(reach+1,len(Pos[y])-d);j<len(Pos[y]);++j)	B.push_back(Pos[y][j]);
					}
					else
					{
						LL id=it-Pos[y].begin();
						if(reach+1>=id-d)
						{
							for(LL j=reach+1;j<=id-1;++j)	B.push_back(Pos[y][j]);
							for(LL j=st;j<=i;++j)	A.push_back(Pos[x][j]);
						}
						else
						{
							ans=max(ans,Solve(A,B));
							A.clear(),B.clear();
							for(LL j=max(id-d,0ll);j<=id-1;++j)	B.push_back(Pos[y][j]);
							for(LL j=st;j<=i;++j)	A.push_back(Pos[x][j]);
						}
						LL up=0;
						for(LL j=max(reach+1,id);j<=max(reach+1,id)+d-1 && j<len(Pos[y]);++j)	up=j,B.push_back(Pos[y][j]);
						reach=max(reach,up);
					}
				}
				ans=max(ans,Solve(A,B));
				Ans[x][y]=Ans[y][x]=ans;
				write(ans),puts("");
			}
		}
	}
	return 0;
}
```

真的巨慢！！！巨慢！！！

---

## 作者：Anita_Hailey (赞：4)

## [SDOI2022] 整数序列

### 题意

你有两个长度为 $n$ 的整数序列 $a,b$，然后有 $q$ 次查询，每次给你两个数字 $x,y$，构造一个新的序列 $c$。满足
$$
c_i = \begin{cases}
1&a_i = x
\\
-1 & a_i = y
\\
0 & \text{else}
\end{cases}
$$
保证 $c$ 中至少存在一个 $1$ 和 $-1$，然后他想让你找到一个区间 $[l,r]$ 满足 $\sum c_i = 0$ 并且 $c_i$ 不能都为 $0$，然后要求选出来区间的 $\sum_{i} b_i[c_i \not = 0]$ 最大。

满足 $1\le n\le 3\times 10^5,1\le q\le 10^6,1\le a_i \le n,-10^9\le b_i\le 10^9,1\le x,y\le n,x\not = y$，对于每次查询，至少有一个 $1$ 和 $-1$。

限制为 7s，512MB

### 题解

一开始在想有没有什么高妙的 polylog 做法，然后发现根本不可能。

首先可以想到一个 $Oq(len_x + len_y)$ 的暴力，每次暴力把两个颜色的位置拿出来然后线性的扫一遍即可。

考虑根号分治（似乎很自然），设定一个阈值 $B$，对于小于等于 $B$ 的询问直接套用上面的暴力，对于两个都大于 $B$ 的也直接套用暴力，因为一个大于 $B$ 的颜色在这种情况下最多只会被计算 $O(\frac{N}{B})$ 次，然后这部分的复杂度是 $O(\frac{N^2}{B})$。

难点是小块和大块之间的贡献怎么算。考虑一个大块实际上有很多点不可能成为答案，能成为答案的只有一个小颜色极长颜色连续的两边的那些长度的点才可以，于是可以对于大颜色维护一个集合，然后直接对于一个小颜色里的元素取出来两边的（各两个）元素即可，因为可能会出现 `yxxy` 的情况。

```cpp
// Siriqwq
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::vector;
using std::copy;
using std::reverse;
using std::sort;
using std::get;
using std::unique;
using std::swap;
using std::array;
using std::cerr;
using std::function;
using std::map;
using std::set;
using std::pair;
using std::mt19937;
using std::make_pair;
using std::tuple;
using std::make_tuple;
using std::uniform_int_distribution;
using ll = long long;
namespace qwq {
	mt19937 eng;
	void init(int Seed) {return eng.seed(Seed);}
	int rnd(int l = 1, int r = 1000000000) {return uniform_int_distribution<int> (l, r)(eng);}
}
template<typename T>
inline void chkmin(T &x, T y) {if (x > y) x = y;}
template<typename T>
inline void chkmax(T &x, T y) {if (x < y) x = y;}
template<typename T>
inline T min(const T &x, const T &y) {return x < y ? x : y;}
template<typename T>
inline T max(const T &x, const T &y) {return x > y ? x : y;}
template<typename T>
inline void read(T &x) {
	x = 0;
	bool f = 0;
	char ch = getchar();
	while (!isdigit(ch)) f = ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (f) x = -x;
}
template<typename T, typename ...Arg>
inline void read(T &x, Arg &... y) {
	read(x);
	read(y...);
}
#define O(x) cerr << #x << " : " << x << '\n'
const double Pi = acos(-1);
const int MAXN = 3e5 + 10, MOD = 998244353, inv2 = (MOD + 1) / 2, I32_INF = 0x3f3f3f3f;
const long long I64_INF = 0x3f3f3f3f3f3f3f3f;
auto Ksm = [] (int x, int y) -> int {
	if (y < 0) {
		y %= MOD - 1;
		y += MOD - 1;
	}
	int ret = 1;
	for (; y; y /= 2, x = (long long) x * x % MOD) if (y & 1) ret = (long long) ret * x % MOD;
	return ret;
};
auto Mod = [] (int x) -> int {
	if (x >= MOD) return x - MOD;
	else if (x < 0) return x + MOD;
	else return x;
};
template<const int N_num, const int M_num>
struct Graph {
	int H[N_num];
	struct Edge {int to, lac;} e[M_num];
	inline void add_edge(int x, int y) {e[*H] = {y, H[x]};H[x] = (*H)++;}
	inline void init() {memset(H, -1, sizeof H);*H = 0;}
};
#define go(x, y) for (int i = x.H[y], v; (v = x.e[i].to) && ~i; i = x.e[i].lac)
inline int ls(int k) {return k << 1;}
inline int rs(int k) {return k << 1 | 1;}
const int blk_sz = 400;
int N, Q, A[MAXN], B[MAXN], pos[MAXN], id[MAXN];
ll mn[MAXN];
vector<int> vec[MAXN];
vector<ll> s[MAXN];
set<int> p[MAXN];
map<int, ll> mp[MAXN];
int main() {
	// std::ios::sync_with_stdio(0);
	// cout << std::fixed << std::setprecision(8);
	// cin.tie(0);
	// cout.tie(0);
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	qwq::init(20050112);
	read(N, Q);
	for (int i = 1; i <= N; ++i) read(A[i]);
	for (int i = 1; i <= N; ++i) read(B[i]);
	for (int i = 1; i <= N; ++i) {
		vec[A[i]].push_back(i);
		pos[i] = vec[A[i]].size();
		p[A[i]].insert(i);
	}
	for (int i = 1; i <= N; ++i) if (vec[i].size()) {
		s[i].push_back(0);
		for (auto &j: vec[i]) s[i].push_back(B[j] + s[i].back());
	}
	memset(mn, 63, sizeof mn);
	for (int x, y; Q--; ) {
		read(x, y);
		assert(x != y);
		if (mp[x].count(y)) {
			printf("%lld\n", mp[x][y]);
			continue;
		}
		ll ans = -I64_INF;
		*id = 0;
		if ((vec[x].size() <= blk_sz && vec[y].size() <= blk_sz) || (vec[x].size() > blk_sz && vec[y].size() > blk_sz)) {
			int tl = 0, tr = 0;
			while (tl < vec[x].size() || tr < vec[y].size()) {
				if (tr == vec[y].size() || (tl != vec[x].size() && vec[x][tl] < vec[y][tr])) id[++*id] = vec[x][tl++];
				else id[++*id] = vec[y][tr++];
			}
			vector<int> vk;
			vk.push_back(vec[x].size());
			mn[vec[x].size()] = 0;
			int c1 = 0, c2 = 0;
			for (int i = 1; i <= *id; ++i) {
				if (A[id[i]] == x) ++c1;
				else ++c2;
				int sl = c2 - c1 + tl;
				chkmax(ans, s[x][c1] + s[y][c2] - mn[sl]);
				chkmin(mn[sl], s[x][c1] + s[y][c2]);
				vk.push_back(sl);
			}
			printf("%lld\n", mp[x][y] = mp[y][x] = ans);
			for (auto &i: vk) mn[i] = I64_INF;
			continue;
		}
		if (vec[x].size() > vec[y].size()) swap(x, y);
		for (auto &j: vec[x]) {
			auto tmp = p[y].lower_bound(j);
			if (tmp == p[y].begin()) continue;
			id[++*id] = *--tmp;
			if (tmp == p[y].begin()) {
				p[y].erase(tmp);
				continue;
			}
			auto jk = tmp;
			id[++*id] = *--tmp;
			p[y].erase(tmp);
			p[y].erase(jk);
		}
		for (auto &j: vec[x]) {
			auto tmp = p[y].upper_bound(j), jk = tmp;
			if (tmp == p[y].end()) continue;
			id[++*id] = *(tmp++);
			if (tmp == p[y].end()) {
				p[y].erase(jk);
				continue;
			}
			id[++*id] = *tmp;
			p[y].erase(tmp);
			p[y].erase(jk);
		}
		for (int i = 1; i <= *id; ++i) p[y].insert(id[i]);
		for (auto &i: vec[x]) id[++*id] = i;
		sort(id + 1, id + 1 + *id);
		int c1 = 0, c2 = 0, l1 = 0, l2 = 0;
		mn[vec[x].size()] = 0;
		vector<int> vk;
		vk.push_back(vec[x].size());
		for (int i = 1; i <= *id; ++i) {
			if (A[id[i]] == x) {
				c1 += pos[id[i]] - l1;
				l1 = pos[id[i]];
			}
			else {
				c2 += pos[id[i]] - l2;
				l2 = pos[id[i]];
			}
			int sl = c2 - c1 + (int)vec[x].size();
			chkmax(ans, s[x][c1] + s[y][c2] - mn[sl]);
			chkmin(mn[sl], s[x][c1] + s[y][c2]);
			vk.push_back(sl);
		}
		printf("%lld\n", mp[x][y] = mp[y][x] = ans);
		for (auto &i: vk) mn[i] = I64_INF;
	}
	// cout << (-3 / 2);
	cerr << ((double) clock() / CLOCKS_PER_SEC) << '\n';
	return (0-0);
}
```


---

## 作者：_SeeleVollerei_ (赞：3)

好难呀，断断续续想了好久，要是连续起来算时间应该大概三四个小时吧。

出于个人习惯，将每一个 $a_i$ 看作一个颜色。

发现对于单次询问，能想到的唯一做法就是对两种颜色的所有数单独提出来，然后从左往右扫一遍，然后按照 $c_i$ 的前缀和分类，每一类维护 $b_i$ 的前缀和的最小值，然后每次将答案对**当前的前缀和**减去**同一类的最小前缀和**取 $\max$ 即可。

要从这个相对暴力且看上去没啥前途的做法优化，只能根号了。

定义一个常数 $B$，对每一个颜色的数，按照数量关于 $B$ 的大小分为两类。这意味着数量 $>B$ 的颜色只有至多 $\frac{n}{B}$ 种。然后分类讨论。

1.两种颜色的数量都 $\le B$。

把所有点暴力提出来直接扫一遍即可。复杂度 $O(qB)$。

2.两种颜色的数量都 $>B$。

因为 $>B$ 的颜色数很少，不妨直接预处理一个 $ans_{x,y}$ 表示颜色 $x$ 和颜色 $y$ 的答案。

考虑暴力枚举 $x,y$ 然后暴力求解。考虑对于 $x$ 内的每个数，它被扫的次数就是 $y$ 的个数。所以复杂度为 $O(n\times\frac{n}{B})=O(\frac{n^2}{B})$。

3.颜色 $x$ 的数量 $\le B$，颜色 $y$ 的数量 $>B$。

考虑一个比较奇怪的扫描方式。

考虑每个点往右匹配会是怎样的。意思就是，选中的区间中的每个颜色为 $x$ 的位置，与它匹配的颜色为 $y$ 的位置都在它右边。**显然实际情况不可能只有这种，但是可以从这个情况出发考虑。**

考虑从左往右扫一遍，然后维护一个计数器 $cnt$，大概的含义是能往右匹配多少个 $y$，那么遇到颜色 $x$ 就计数器 +1，遇到颜色 $y$ 且计数器的值 $>0$ 的时候就将这个位置加入一个集合，并将计数器 -1。

然后同理从右往左扫一遍，然后注意这一遍遇到已经加入了集合的 $y$ 要跳过，以防匹配到同一个点。

这个过程是在我感性猜测下得出的过程，形式化地就是，每个 $x$ 找到它往左和往右第一个未加入集合的 $y$ 将其加入集合。

因为每个 $x$ 只会贡献 $O(1)$ 个点，所以得出来集合内的点只有 $O(B)$ 个，能在区间内出现的点只能是集合内的点。

考虑证明。

考虑对于一个不在集合内的 $y$，它往左往右都存在一个在集合内的 $y$。那么它左边第一个选了的 $y$ 一定是左边所有的 $x$ 都往右匹配的结果，以及它右边第一个选了的 $y$ 一定是右边所有的 $x$ 都往左匹配的结果。所以它两边已经往它靠近了，没法再延申了。

每个 $x$ 找点大概需要一个二分或者 set 的 $O(\log n)$，所以复杂度为 $O(qB\log n)$。

综上，总的复杂度为 $O(\frac{n^2}{B}+qB\log n)$。平衡复杂度的话令 $B=\sqrt{\frac{n^2}{q\log n}}$ 最优。可以适当上调下调卡常。

代码还没写，心情好再写吧，写完再投题解。

写好了。

值得注意的是每个点要往外找两个点，原因的话考虑这样一个相对位置 $x1<y<x2$。如果先处理 $x2$ 的左边，那 $x1$ 的右边会在 $x2$ 的右边去找，但是如果先处理 $x1$ 的右边，那么 $x2$ 的左边就找不到东西了，这样就会少点。

```cpp
#include<cstdio>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=3e5+5;
const int block=70;
const int M=5005;
const LL INF=1ll<<60;
int n,q;
int a[N],b[N];
int to[N],pos[M],m;
LL ans[M][M];
vector<int>in[N];
set<int>s[N];
inline int Read(){
	char ch;
	int f=1;
	while((ch=getchar())<'0'||ch>'9')
		if(ch=='-') f=-1;
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
inline void print(LL x){
	if(x>=10) print(x/10);
	putchar(x%10+48);
	return ;
}
inline void Print(LL x,char ch='\n'){
	if(x<0){
		putchar('-');
		print(-x);
	}
	else print(x);
	putchar(ch);
	return ;
}
inline LL Max(LL x,LL y){
	return x>y?x:y;
}
inline LL Min(LL x,LL y){
	return x<y?x:y;
}
inline void Cmax(LL&x,LL y){
	if(y>x) x=y;
	return ;
}
inline void Cmin(LL&x,LL y){
	if(y<x) x=y;
	return ;
}
vector<int>pi;
LL mn[N<<1];
inline LL Get(int x,int y){
	int siz=pi.size();
	for(int i=-siz;i<=siz;i++)
		mn[i+N]=INF;
	mn[N]=0;
	int cnt=0;
	LL ss=0,ans=-INF;
	for(int i=0;i<pi.size();i++){
		int ii=pi[i];
		ss+=b[ii];
		if(a[ii]==x) cnt++;
		else cnt--;
		Cmax(ans,ss-mn[cnt+N]);
		Cmin(mn[cnt+N],ss);
	}
	return ans;
}
inline LL Query(int x,int y){
	int sizx=in[x].size(),sizy=in[y].size();
	int i=0,j=0;
	while(i<sizx&&j<sizy){
		int ii=in[x][i],jj=in[y][j];
		if(ii<jj){
			pi.push_back(ii);
			i++;
		}
		else{
			pi.push_back(jj);
			j++;
		}
	}
	while(i<sizx) pi.push_back(in[x][i++]);
	while(j<sizy) pi.push_back(in[y][j++]);
	LL ans=Get(x,y);
	pi.clear();
	return ans;
}
inline void Init(){
	n=Read(),q=Read();
	for(int i=1;i<=n;i++){
		a[i]=Read();
		in[a[i]].push_back(i);
		s[a[i]].insert(i);
	}
	for(int i=1;i<=n;i++)
		b[i]=Read();
	for(int i=1;i<=n;i++)
		if(in[i].size()>block){
			++m;
			pos[m]=i;
			to[i]=m;
		}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			ans[i][j]=ans[j][i]=Query(pos[i],pos[j]);
	return ;
}
inline LL Ask(int x,int y){
	for(int i=0;i<in[x].size();i++){
		int ii=in[x][i];
		pi.push_back(ii);
		for(int j=0;j<=1;j++){
			if(s[y].size()){
				set<int>::iterator it=s[y].lower_bound(ii);
				if(it!=s[y].begin()){
					it--;
					pi.push_back(*it);
					s[y].erase(it);
				}
			}
			if(s[y].size()){
				set<int>::iterator it=s[y].upper_bound(ii);
				if(it!=s[y].end()){
					pi.push_back(*it);
					s[y].erase(it);
				}
			}
		}
	}
	sort(pi.begin(),pi.end());
	LL ans=Get(x,y);
	while(pi.size()){
		int ii=pi.back();
		pi.pop_back();
		if(a[ii]==y) s[y].insert(ii);
	}
	return ans;
}
inline void Swap(int&x,int&y){
	int tmp=x;
	x=y;y=tmp;
	return ;
}
inline void Solve(){
	for(;q;q--){
		int x=Read();
		int y=Read();
		if(in[x].size()>in[y].size()) Swap(x,y);
		if(in[x].size()>block) Print(ans[to[x]][to[y]]);
		else if(in[y].size()<=block) Print(Query(x,y));
		else Print(Ask(x,y));
	}
	return ;
}
int main(){
	Init();
	Solve();
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：1)

感觉显式的根号分治还是太不优美了。

## Solution

设 $s_x$ 表示颜色为 $x$ 的下标组成的集合。考虑现在询问 $x,y$，并且 $\lvert s_x\rvert\le \lvert s_y\rvert$（不满足就交换）。

设 $f(i)=\max(\max_{j\le i}\sum_{k\in[j,i]}c_k,\max_{j\ge i}\sum_{k\in[i,j]}c_k)$，也就是以 $i$ 为一个端点的区间的最大 $c_k$ 和。如果 $f(i)<0$，那么这个 $i$ 永远不会在答案区间中。

对于一个只包含在 $s_y$ 中且 $f(i)<0$ 的 $i$ 的极大连续段，选择的区间和这个连续段不能有交，因此随意保留一个连续段中的数，剩下的数可以删掉。为了方便，统一保留 $f(i)=-1$ 的数。

因此，把 $f(i)\ge -1$ 的 $i$ 全部抠出来，放到集合 $B$ 里面。我们显然有 $\mathcal O(\lvert B\rvert)$ 求解答案的算法。

考虑怎么把这些点抠出来。从左往右枚举 $s_x\cup s_y$ 中的点，维护以当前点为右端点的区间的最大 $c_k$ 和 $t$，如果 $t<-1$ 就 $t\gets 0$ 并跳到下一个 $s_x$ 中的位置。同样地在从右往左枚举一遍。

只会有 $\lvert s_x\rvert$ 次 $+1$，因此每次加入的点不超过 $2\lvert s_x\rvert$ 个，故 $\lvert B\lvert\le 5\lvert s_x\rvert$。

一次询问复杂度为 $\mathcal O(\lvert s_x\rvert\log\lvert s_y\rvert)\le\mathcal O(\min(\lvert s_x\rvert,\lvert s_y\rvert)\log n)$。根据经典结论，记忆化一下，复杂度为 $\mathcal O(n\sqrt q\log n)$。$\log$ 可以通过一些方法优化掉，但是没有必要。

## Code

很短。

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#define ppc(x) __builtin_popcount(x)
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	typedef vector<int>::iterator IT;
	const int N = 3e5 + 5;
	LL n, q, x, y, a[N], c[N], b[N * 2];
	vector<int> s[N]; map<int, LL> mp[N];
	int main() {
		cin >> n >> q;
		REP(i, 1, n) cin >> c[i], s[c[i]].pb(i);
		REP(i, 1, n) cin >> a[i];
		REP(te, 1, q) {
			cin >> x >> y;
			if (SZ(s[x]) > SZ(s[y])) swap(x, y);
			if (mp[x].count(y)) { cout << mp[x][y] << '\n'; continue; }

			vector<int> B; vector<IT> A{s[y].begin()};
			for (int i : s[x])
				A.pb(lower_bound(ALL(s[y]), i)), B.pb(i);
			A.pb(s[y].end());

			int t = 0;
			REP(i, 1, SZ(A) - 2) {
				auto it = A[i];
				for (t ++; ~t && it != A[i + 1]; )
					B.pb(*it ++), t --;
				t = max(t, 0);
			}
			t = 0;
			DEP(i, SZ(A) - 2, 1) {
				auto it = A[i];
				for (t ++; ~t && it != A[i - 1]; )
					B.pb(*-- it), t --;
				t = max(t, 0);
			}

			sort(ALL(B)), B.erase(unique(ALL(B)), B.end());
			LL rs = -1e18, sm = 0, d = SZ(B); t = d;
			REP(i, 0, d * 2) b[i] = (i == d ? 0 : 1e18);
			for (int i : B) {
				t += (c[i] == x ? 1 : -1), sm += a[i];
				rs = max(rs, sm - b[t]), b[t] = min(b[t], sm);
			}
			cout << (mp[x][y] = rs) << '\n';
		}
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：1)

考虑一种暴力做法。记 $tx_i$ 表示前 $i$ 位中 $x$ 的个数，$ty_i$ 表示前 $i$ 位中 $y$ 的个数。那么区间 $[l,r]$ 合法，当且仅当 $tx_r-tx_l=ty_r-ty_l\ne 0$，移项一下，就是 $tx_r-ty_r=tx_l-ty_l$，不妨记 $p_i=tx_i-ty_i$，这样条件就转化为 $p_l=p_r$。对于每种数字，分别预处理出 $b$ 的前缀和 $S$。再维护一个数组 $mn_x$ 表示所有 $p_i=x$ 中最小的 $S_i$。故枚举右端点，对 $S_i-mn_{p_i}$ 取最大值即可。该做法做一次是 $O(L)$ 的，$L$ 是整个序列中 $x$ 和 $y$ 的总数。

考虑根号平衡，记 $x$ 在整个序列中的个数为 $c_x$，对 $c$ 进行根号分治，需要简单分讨一下：

若 $c_x,c_y\le B$，即小块对小块，直接暴力，复杂度 $O(nB)$。

若 $c_x,c_y>B$，即大块对大块。发现这类块最多有 $\frac{n}{B}$ 个，本质不同的询问至多 ${\left(\frac{n}{B}\right)}^2$ 个，直接用 map 将操作存下来，然后跑暴力就行了，复杂度 $O(\frac{n^2}{B})$。

若 $c_x\le B<c_y$，即小块对大块，这个就比较麻烦了。此时需要善于利用 $c_x\le B$ 的性质。我们将等于 $y$ 的点分为 **有效点** 和 **无效点** 两类。显然，小块中每个点都是需要考虑在内的有效点，大块中，许多点对答案是不可能产生贡献的。具体做法：我们将 $x,y$ 都抽出来，组成一个新的序列来看，对于每个全是 $x$ 的连续段，设其长度为 $l$，那么只有向前的 $l+1$ 个未被选中的 $y$ 和向后 $l+1$ 个未被选中的 $y$ 可能成为有效点，把这些点都扔进去，然后暴力一遍。这个过程可以用 set 加速，单次的复杂度 $O(B\log n)$。

所以总复杂度就是 $O(qB\log n+\frac{n^2}{B})$，令 $B=\sqrt{\frac{n^2}{q\log n}}$ 时最优，就是 $O(n\sqrt{q\log n})$ 了。

---

## 作者：Jorisy (赞：1)

$\gdef\s{\sum\limits}$

这个时限 $7\text s$ 看着就很根号。

题目等价于询问 $\max\left\{\left.\s_{i=l}^rb_i\right|\s_{i=l}^r[a_i=x]=\s_{i=l}^r[a_i=y]>0\right\}$。

问题和出现次数相关，考虑根分。

下面令数 $x$ 在 $a$ 中的出现次数为 $c_x$，根分的阈值为 $B$。

对于询问的 $x,y$，钦定 $c_x\le c_y$。

接下来分类讨论：

- $c_x,c_y\le B$。

取原序列中只包含 $x,y$ 所构成的长度为 $c_x+c_y$ 的子序列，然后直接遍历。；遍历时记 $t_x,t_y$ 分别表示当前子序列中 $x,y$ 的出现次数。维护 $\text{mins}_{i}$ 表示 $x-y=i$ 时的**最小**代价（比较时与当前和减一下即可）即可。

时间复杂度 $O(qB)$。

- $c_x,c_y>B$。

这样的话最多有 $\left(\dfrac nB\right)^2$ 个本质不同的询问组。直接暴力跑加一个记忆化即可。

假设有 $m$ 个 $c_i>B$，则最多计算次数为 $\s_{\substack{1\le i<j\le n\\c_i,c_j>B}}c_i+c_j=(m-1)\s_{\substack{1\le i\le n\\c_i>B}}c_i\le (m-1)k$，由于 $m\le\dfrac nB$，故时间复杂度为 $O\left(q+\dfrac{n^2}B\right)$。

- $c_x\le B<c_y$。

对于颜色 $y$，我们发现由于 $c_x$ 很小，这导致我们其实有相当一部分 $a_i=y$ 是没有用的。我们直接去掉没用的部分。

具体地，只保留每个颜色为 $x$ 极长子段 $a_{[l,r]}$ 的两侧分别长度为 $r-l+1$ 的部分。实际做的时候由于会出现无关的子段拼成额外的答案，如两个 $\tt yxy$ 拼接起来会有 $\tt y\red{xyyx}y$，红色部分是额外出现的。一种办法是两侧延伸 $r-l+2$ 的长度，即 $\tt yyxyyyyxyy$，这样就没有影响了。此外，由于延伸时会出现其它 $\tt x$ 和已经加入的 $\tt y$，处理的时候可以用 set 快速查找和删除。

这样就剩下长度为 $O(B)$ 级别的序列了。套用上述的暴力做法即可。时间复杂度取决于 $c_x$，套上 set 的时间复杂度大约为 $O\left(q+\dfrac{n^2\log n}B\right)$。

取 $B=\sqrt n$ 就能过了。但是数据过于神秘，实测取 $B=1$ 的时候，可以在洛谷上以最慢 $6.94\text s$ 的时间通过。有点魔怔。

---

## 作者：L0vely_NaiL0ng (赞：1)

有一个归并之后 $O(cnt_x + cnt_y)$ 的做法，我们根号分治，对于小小、大大的情况用刚刚的做法复杂度是对的。

难点是小大，注意到刚刚的做法我们只需要保证最终选择方案的右端点、左端点的上一个点在候选集合中即可，感受一下小大的情况大的在候选集合中的点应该也是 $O(B)$ 的，考虑一些大的点根本不存在覆盖它的两种颜色个数相等的段，具体的我们找出 $x$ 的每个连续段，长度为 $len$，我们找到它右边 $len$ 个颜色为 $y$ 的位置，这些也是关键集合中的点，然后把这些位置删除，本质上是贪心用 $x$ 尽可能去覆盖一些 $y$ 的位置，如果覆盖不到说明一定不存在经过它的两种颜色个数相等的段，无论怎么选经过它的段 $y$ 的个数一定比 $x$ 多，向左边找类似，但是对于每个连续段要多找一个位置，因为我们要确保答案段的左端点的上一个点也在候选集合中。

代码实现上可以不找连续段，对于每个 $x$ 中的点，找到右边 $1$ 个，左边 $2$ 个即可，接着套用前面的做法复杂度还是对的。

#### 收获

**这题贪心用 $x$ 去覆盖来踢出没有用的 $y$ 的位置的思想很巧妙。**

[代码](https://www.luogu.com.cn/paste/we9kt6i9)

---

## 作者：nullqtr_pwp (赞：1)

山东省选 D1T1，有点吓人了。

数据结构题，但是这道题几乎无法 $\operatorname{polylog}$ 来做。

这个询问的限制性实际上非常强，几乎无法用更优的方法单独解决一次询问。也就是单独提取出来 $a_i=x,a_j=y$ 的所有 $i,j$ 组成一个序列才能做。 

考虑 $q=1$ 的暴力，注意到我们只关心 $x,y$ 的位置，找出这些位置然后排序，扫一遍就能得出答案。

注意到这道题和出现次数严重挂钩，考虑根号分治，记阈值为 $B$。注意到这道题 $x,y$ 的顺序没有影响。所以钦定 $x$ 的出现次数更少。设 $c_x$ 为 $x$ 在数列 $a_i$ 中的出现次数。 

分类讨论，分为以下三种：

- $c_x\leq c_y\leq B$。这个直接找出所有 $x,y$ 的位置，然后暴力跑即可，单次的复杂度是 $O(B)\sim O(B\log B)$。（我的实现就是带 $\log$ 的，这道题时间给的还行。）

- $c_y\ge c_x>B$。本质不同的询问较少，这样的 $(x,y)$ 最多只有 $\left (\dfrac{n}{B}\right )^2$ 对。考虑记忆化每次询问即可。这一部分时间复杂度是 $O\left (\dfrac{n^2}{B}\right )$ 的。

以上部分直接跑暴力复杂度就是对的。

根号分治往往需要提出不同复杂度的暴力，但是这道题在小对大的时候有另类的处理方式。

我们考虑 $c_x<B,c_y\ge B$ 的情况。这一部分较难，考虑将 $y$ 相同的放在一起询问。那么我们可以对于每种 $y$ 预处理，然后每个 $x$ 去遍历它的位置求解。

重新回顾这道题的要求：**$\boldsymbol{x}$ 在区间的出现次数等于 $\boldsymbol{y}$ 在区间中的出现次数。**

注意到 $c_x<B$，那么我们可以找到的 $[l,r]$ 的要求就很强了。我们找到的 $[l,r]$ 中的 $y$ 的次数不能比 $x$ 多很多。考虑造成贡献的 $y$ 在哪里，只能是距离 $x$ 最近的几个。思考一下，我们只需要加入有用的 $y$ 去跑那个暴力。

具体的，对于每个 $x$，有用点加入 $y$ 的前驱和后继。这还不够，因为可能跳过这一段，需要有些 $y$ 做间隔。因此还需要加入**二级**前驱以及二级后继。

这样的话，有用的 $y$ 的个数就是 $O(c_x)$ 个，然后再跑暴力就会因为总点数是少的，从而时间复杂度正确。

这一部分复杂度大概是 $O\left (\dfrac{n^2}{B}\log n\right)$。

取 $B=\sqrt n$ 就可以通过本题了。

[LOJ 提交记录](https://loj.ac/s/2002492)

---

## 作者：_Ch1F4N_ (赞：0)

有趣。

考虑一个根号分治状物，如果 $cnt_x,cnt_y$ 均小于等于 $\sqrt n$ 我们暴力归并两个数的出现位置集合扫一遍即可。

不妨
$cnt_x \geq cnt_y$，当 $cnt_x > \sqrt n$ 时如果我们可以 $O(cnt_y)$ 地回答询问，再记忆化一下即可做到 $O(n \sqrt q)$。

考虑怎么 $O(cnt_y)$ 地回答询问，不妨认为每经过一个 $a_i=x$ 的 $i$ 就让一个计数器加 $1$ 每经过 $a_i=y$ 的 $i$ 就让计数器减 $1$，计数器的值形成了一个折线，折线上两处同高度位置会产生贡献。

显然不能考虑折线上所有位置，考虑进行一些剪枝，首先所有下降的位置可以考虑进来，然后你会发现对于一段极长的上升段，中间有些位置如果在前后都不再出现就可以不考虑，但是怎么找出这些位置呢？

考虑这样一个算法，对于一个极长的下降段，假若是从点 $(x,a)$ 到点 $(y,b)$，你将段前面第一次下降到 $b$ 处的位置到段后面第一次上升到 $a$ 处的位置之间的点全部加入考虑，容易通过归纳证明这样可以覆盖到所有出现了至少两次的位置，求出这些位置的方法是从前往后扫，维护一个计数器，在扫到 $a_i=y$ 的位置时增加 $1$ ，在扫到 $a_i=x$ 时的位置时如果计数器不为 $0$ 就减少 $1$ 否则就跳过这个位置，然后再从后往前扫一遍做类似的事情（注意倒着扫时需要在扫一段极长的上升段时如果给计数器借 $1$ 以处理谷的底端），通过这个处理方法可以得知这样的位置是 $O(cnt_y)$ 个，处理每个位置前面或者后面第一个 $x$ 可以离线后挂到 $x$ 上然后预处理，于是这个题就做到了 $O(q \sqrt n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e5+114;
const int maxq =1e6+114;
const int warma = 700;
vector<int> pos[maxn];
int a[maxn],b[maxn];
int dp[maxn];
vector< pair<int,int> > Q[maxn];//y id
int ans[maxq];
int n,q;
int ask(int x,int y){
    int res=-1e18;
    vector<int> vec(pos[x].size()+pos[y].size());
    merge(pos[x].begin(),pos[x].end(),pos[y].begin(),pos[y].end(),vec.begin());
    for(int i=0;i<=2*warma;i++) dp[i]=1e18;
    dp[warma]=0;
    int sum=0,s=0;
    for(int p:vec){
        if(a[p]==x) sum++;
        else sum--;
        s+=b[p];
        res=max(res,s-dp[sum+warma]);
        dp[sum+warma]=min(dp[sum+warma],s);
    }
    return res;
}
int use[maxn];//记忆化
int pre[maxn];//a[i]=x 的位置前缀和
int prect[maxn];
int nxt[maxn];
int lst[maxn];
int vis[maxn];
void work(int x){
    for(int i=0;i<maxn;i++) use[i]=-1e18,dp[i]=1e18;
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+(a[i]==x?b[i]:0);
        prect[i]=prect[i-1]+(a[i]==x);
        lst[i]=(a[i]!=x?lst[i-1]:i);
    }
    nxt[n+1]=n+1;
    for(int i=n;i>=1;i--){
        nxt[i]=(a[i]!=x?nxt[i+1]:i);
    }
    for(pair<int,int> now:Q[x]){
        int y=now.first,id=now.second;
        if(use[y]!=-1e18) ans[id]=use[y];
        else{
            vector<int> vec=pos[y];
            vector<int> ins;
            int sum=0;
            for(int i=0;i+1<pos[y].size();i++){
                sum++;
                int u=pos[y][i];
                while(sum>0&&nxt[u+1]<pos[y][i+1]){
                    ins.push_back(nxt[u+1]);
                    vis[nxt[u+1]]=1;
                    u=nxt[u+1];
                    sum--;
                }
            }
            sum++;
            int u=pos[y].back();
            while(sum>0&&nxt[u+1]<=n){
                ins.push_back(nxt[u+1]);
                vis[nxt[u+1]]=1;
                u=nxt[u+1];
                sum--;
            }
            vector<int> New(vec.size()+ins.size());
            merge(vec.begin(),vec.end(),ins.begin(),ins.end(),New.begin());
            swap(New,vec);
            New.clear();
            ins.clear();
            sum=0;
            for(int i=(int)pos[y].size()-1;i>=1;i--){
                sum+=2;
                int u=pos[y][i];
                while(sum>0&&lst[u-1]>pos[y][i-1]){
                    if(vis[lst[u-1]]==0){
                        ins.push_back(lst[u-1]);
                    }
                    vis[lst[u-1]]=1;
                    u=lst[u-1];
                    sum--;
                }
                if(sum>0) sum--;
            }
            sum+=2;
            u=pos[y][0];
            while(sum>0&&lst[u-1]>=1){
                if(vis[lst[u-1]]==0){
                    ins.push_back(lst[u-1]);
                }
                vis[lst[u-1]]=1;
                u=lst[u-1];
                sum--;
            }
            reverse(ins.begin(),ins.end());
            New.resize(vec.size()+ins.size());
            merge(vec.begin(),vec.end(),ins.begin(),ins.end(),New.begin());
            swap(New,vec);
            New.clear();
            ins.clear();
            for(int p:vec) vis[p]=0;
            dp[pos[y].size()]=0;
            sum=0;
            int s=0;
            int res=-1e18;
            for(int p:vec){
                if(a[p]==y) sum--;
                if(a[p]==y) s+=b[p];
                res=max(res,s+pre[p]-dp[sum+prect[p]+pos[y].size()]);
                dp[sum+prect[p]+pos[y].size()]=min(dp[sum+prect[p]+pos[y].size()],s+pre[p]);
            }
            sum=0;
            for(int p:vec){
                if(a[p]==y) sum--;
                dp[sum+prect[p]+pos[y].size()]=1e18;
            }
            dp[pos[y].size()]=1e18;
            use[y]=res;
            ans[id]=res;
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(pos[x].size()<pos[y].size()||(pos[x].size()==pos[y].size()&&x<y)) swap(x,y);
        if(pos[x].size()<=warma) ans[i]=ask(x,y);
        else Q[x].push_back(make_pair(y,i));
    }
    for(int i=1;i<=n;i++){
        if(Q[i].size()>0) work(i);
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑根号分治，若 $cnt_x < B$ 且 $cnt_y < B$ 或 $cnt_x \ge B$ 且 $cnt_y \ge y$ 时暴力记忆化计算。第一种情况复杂度为 $O(B)$，第二种情况最多有 $O(\frac{n^2}{B^2})$ 种，直接做时间复杂度为 $O(\frac{n^2}{B})$。

暴力即将 $x$ 与 $y$ 出现的位置归并起来，扫一遍维护前缀和，维护某个权值时的最小和即可线性。

现在只用考虑 $cnt_x \ge B$ 且 $cnt_y < B$ 情况，由于 $cnt_x \ge B$ 的 $x$ 最多只有 $\frac{n}{B}$ 个，故考虑对于每个暴力预处理出其它所有的答案。

如果你做过 [P4062 [Code+#1] Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062) 的线性做法，那你就应该会了。

考虑对于 $y$ 出现的每个位置，找到左边第一个未被标记的 $x$ 的位置后将 $x$ 标记；清空标记后再找右边第一个未被标记的 $x$ 的位置后将 $x$ 标记。

此时区间和可能为 $0$ 的贡献只可能对标记中的数有贡献，因为你考虑往左标记时没有标记到这个位置，那么从 $x$ 位置向右延申的前缀和肯定恒大于或恒小于 $0$；向右标记同理。

那么一个位置未被标记说明任何一个包含这个区间的 $c$ 的和肯定恒大于 $0$ 或恒小于 $0$，一定不会造成贡献。

我们需要支持维护上面找左边与右边第一个未被标记的点，需要支持撤销，于是只能使用 `set` 维护。

于是这部分时间复杂度为 $O(\frac{n}{B} n \log n) = O(\frac{n^2}{B} \log n)$，取 $B = \sqrt{n}$，总时间复杂度为 $O(N \sqrt{N} \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e5 + 10, M = 1e6 + 10;
const ll INF = 1e18;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll Ans;
int n, q, len, x, y, cnt;
int a[N], h[N], f[N], id[N], g[N], p[N];
ll ans[M], Min[N << 1], chk[N];
vector<int> now;
vector<int> V[N];
unordered_map<int, ll> mp[N];
vector<pair<int, int>> Q[N];
set<int> T, T1, T2;
inline ll get(){
	stack<int> T;
	Ans = -INF;
	ll vum = 0;
	int lst = 0, sum = 3e5;
	Min[sum] = 0;
	for(auto v : now){
		if(g[v] && g[v] != lst + 1){
			vum = 0, sum = 3e5;
			while(!T.empty()){
				int x = T.top();
				T.pop();
				Min[x] = INF;
			}
			Min[sum] = 0;
		}
		sum += f[v], vum += h[v];
		Ans = max(Ans, vum - Min[sum]);
		Min[sum] = min(Min[sum], vum);
		T.push(sum);
		if(g[v])
		  lst = g[v];
	}	
	while(!T.empty()){
		int x = T.top();
		T.pop();
		Min[x] = INF;
	}	
	return Ans;
}
inline void solve(int i){
	if((int)V[i].size() > len || V[i].empty() || !chk[i])
	  return ;
	reverse(V[i].begin(), V[i].end());
	for(auto v : V[i]){
		T.insert(v); 
		auto it = T2.upper_bound(v);
		if(it != T2.end()){
			T.insert(*it);
			T2.erase(*it);
		}
	}
	reverse(V[i].begin(), V[i].end());
	for(auto v : V[i]){
		auto it = T1.lower_bound(v);
		if(it != T1.begin()){
			--it;
			T.insert(*it);
			T1.erase(*it);
		}
	}
	for(auto v : T)
	  now.push_back(v);
	for(auto v : now){
		if(g[v]){
			f[v] = 1;
			T1.insert(v);
			T2.insert(v);
		}
		else
		  f[v] = -1;
	}
	chk[i] = get();
	T.clear(), now.clear();
}
bool End;
int main(){
//	open("A.in", "A.out");
	n = read(), q = read();
	len = sqrt(n);
	for(int i = 0; i < (N << 1); ++i)
	  Min[i] = INF;
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		V[a[i]].push_back(i);
	}
	for(int i = 1; i <= n; ++i){
		h[i] = read();
		if((int)V[i].size() > len){
			p[++cnt] = i;
			id[i] = cnt;
		}
	}
	for(int i = 1; i <= q; ++i){
		x = read(), y = read();
		if(V[x].size() < V[y].size())
		  swap(x, y);
		if(((int)V[x].size() <= len && (int)V[y].size() <= len) || ((int)V[x].size() > len && (int)V[y].size() > len)){
			if(mp[x].count(y)){
				ans[i] = mp[x][y];
				continue;
			}
			auto it1 = V[x].begin(), it2 = V[y].begin();
			while(it1 != V[x].end() || it2 != V[y].end()){
				int t = 1e9;
				if(it1 != V[x].end())
				  t = min(t, *it1);
				if(it2 != V[y].end())
				  t = min(t, *it2);
				if(it1 != V[x].end() && (*it1) == t){
					f[t] = 1;
					++it1;
				}
				if(it2 != V[y].end() && (*it2) == t){
					f[t] = -1;
					++it2;
				}
				now.push_back(t);
			}
			mp[x][y] = ans[i] = get();
			now.clear();
		}
		else
		  Q[id[x]].push_back({i, y});
	}
	for(int tim = 1; tim <= cnt; ++tim){
		int x = p[tim], num = 0;
		for(auto v : V[x]){
			g[v] = ++num;
			T1.insert(v), T2.insert(v); 
		}
		for(auto t : Q[tim])
		  chk[t.se] = 1;
		for(int i = 1; i <= n; ++i)
		  if(i != p[tim])
		    solve(i);
		for(auto t : Q[tim])
		  ans[t.fi] = chk[t.se];
		for(auto t : Q[tim])
		  chk[t.se] = 0;
		x = p[tim];
		for(auto v : V[x])
		  g[v] = 0;
		T1.clear(), T2.clear();
	}
	for(int i = 1; i <= q; ++i){
		write(ans[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# P8349 [SDOI/SXOI2022] 整数序列 题解

## 前言

VP SDOI 2022 Day1 的时候 T2 数位 DP 拿 35pts，T3 平方做法 MLE，这题想到和根号分治有关，但因为算错复杂度连第二档部分分都没想出来，鉴定为纯纯的耻辱。

## 题意回顾

给定长度为 $ n $ 的颜色序列 $ a $ 和数值序列 $ b $，每次询问所有颜色 $ x $ 和 $ y $ 的位置构成的子序列中，满足两种颜色数量相等的所有**非空连续子序列**的最大数值和。

$ 1 \le n \le 3 \times 10^5 $，$ 1 \le q \le 10^6 $，$ 1 \le a_i,x,y \le n $，$ x \ne y $，$ -10^9 < b_i \le 10^9 $，保证每次询问至少存在一个合法的非空连续子序列。

## 分析

* 考虑根号分治，记 $ S $ 为颜色出现次数多和少的分界点。

* 对于每个颜色出现次数都很少的情况，预先把每个颜色的所有位置拎出来，显然可以直接每次询问归并两种颜色的出现位置，以与两种颜色出现次数线性相关的算法解决，复杂度显然是 $ O(Sn) $ 量级。

* 对于两种出现次数很多的颜色，可以发现这些颜色不会很多，所有本质不同的询问的复杂度之和也不过 $ O(\frac{n^2}{S}) $ 量级。

* 注意记忆化本质相同的询问，显然将 $ x,y $ 调换是等价的。

* 以上两种情况均可暴力计算，我们可以拿到前 $ 6 $ 个测试点的合计 $ 30 $ 分。

* 显然，会有两种颜色出现次数一多一少的情况。我们发现对于一个出现少的颜色的每个位置，只有前两个未被标记为对答案有影响和后两个为被标记对答案有影响的出现次数多的位置可以被标记对答案有影响。因为如果连续太多只有多的那种颜色的话，显然这段区间如果被包含在答案里，则少的那种颜色无法与多的那种颜色平衡。故可以把区间长度缩减为 $ O(S) $ 量级。

* 找到最小的大于和最大的小于特定数的位置并标记可以用 `set` 实现，因为要找两次所以可以封装。

* 这里我们取 $ S $ 为一个和 $ \sqrt{n} $ 同阶的量，本代码中我们取 $ S=720 $。

* 因为本质上三类情况都是暴力，所以可以将暴力求解函数封装，注意清空颜色的 $ +1 $ 或 $ -1 $ 构成的前缀和桶子与撤销出现次数多的那种颜色的标记时，不能暴力清空，应该只更改被影响的部分。

* 不开 `long long` 见祖宗。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
const int N = 300005;
const int S = 720;
int n, q;
int a[N];
int b[N];
vector<int> g[N];
long long mp[N * 2];
int tp[N];
int yy[N];
set<int> se[N];
map<int, map<int, long long> > rem;
void solve(int x, int y, int tl) {
    int cur = 300000;
    long long val = 0;
    long long ans = -1e18 - 5;
    for(int i = 1; i <= tl; i++) {
        mp[cur] = min(mp[cur], val);
        if(a[tp[i]] == x) cur++;
        else cur--;
        val += b[tp[i]];
        ans = max(ans, val - mp[cur]);
    }
    cur = 300000;
    for(int i = 1; i <= tl; i++) {
        mp[cur] = 1e18 + 5;
        if(a[tp[i]] == x) cur++;
        else cur--;
    }
    if(x > y) swap(x, y);
    rem[x][y] = ans;
    printf("%lld\n", ans);
}
void gety(int y, int xi, int &ty) {
    set<int>::iterator it = se[y].lower_bound(xi);
    int ya = -1, yb = -1;
    if(it != se[y].end()) ya = yy[++ty] = *it;
    if(it != se[y].begin()) {
        it--;
        yb = yy[++ty] = *it;
    }
    if(ya != -1) se[y].erase(ya);
    if(yb != -1) se[y].erase(yb);
}
int main() {
    for(int i = 0; i <= 600000; i++) mp[i] = 1e18 + 5;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for(int i = 1; i <= n; i++) g[a[i]].push_back(i), se[a[i]].insert(i);
    int x, y;
    for(int i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);
        if(x > y) swap(x, y);
        if(rem.find(x) != rem.end() && rem[x].find(y) != rem[x].end()) {
            printf("%lld\n", rem[x][y]);
            continue;
        }
        if((g[x].size() <= S && g[y].size() <= S) || (g[x].size() > S && g[y].size() > S)) {
            int tl, tx, ty;
            tl = tx = ty = 0;
            for(int i = 1; i <= g[x].size() + g[y].size(); i++) {
                if(tx == g[x].size()) tp[++tl] = g[y][ty++];
                else if(ty == g[y].size()) tp[++tl] = g[x][tx++];
                else if(g[x][tx] < g[y][ty]) tp[++tl] = g[x][tx++];
                else tp[++tl] = g[y][ty++];
            }
            solve(x, y, tl);
            continue;
        }
        if(g[x].size() > S) swap(x, y);
        int ty = 0;
        for(int i = 0; i < g[x].size(); i++) {
            gety(y, g[x][i], ty);
            gety(y, g[x][i], ty);
        }
        sort(yy + 1, yy + ty + 1);
        int tl, tx, tyy;
        tl = tx = 0, tyy = 1;
        for(int i = 1; i <= g[x].size() + ty; i++) {
            if(tx == g[x].size()) tp[++tl] = yy[tyy++];
            else if(tyy > ty) tp[++tl] = g[x][tx++];
            else if(g[x][tx] < yy[tyy]) tp[++tl] = g[x][tx++];
            else tp[++tl] = yy[tyy++];
        }
        solve(x, y, tl);
        for(int i = 1; i <= ty; i++) {
            se[y].insert(yy[i]);
        }
    }
    return 0;
}

```

---

## 作者：Fzrcy (赞：0)

这个问题似乎没有 $\log$ 算法，于是我们朝根号分治方面想，设 $cnt_x$ 表示 $x$ 的出现次数，则我们按 $cnt_x \le B$ 分类讨论。

- 当 $cnt_x\le B$、$cnt_y\le B$ 时，我们直接将 $x$ 和 $y$ 的序列合并，暴力计算即可，时间复杂度 $O(qB)$。
- 当 $cnt_x\ge B$、$cnt_y\ge B$ 时，我们直接将 $x$ 和 $y$ 的序列合并，暴力计算即可，并用 `unordered_map` 保存，若遇到相同的直接查询即可。时间复杂度 $O(\frac{n^2}{B})$，证明：因为 $cnt_x\ge B$，所以最多只有 $\frac{n}{B}$ 个 $x$，所以 $\sum_{x}\sum_{y}cnt_x+cnt_y=\sum_{x}cnt_x\frac{n}{B}=\frac{n^2}{B}$。
- 当 $cnt_x\le B$、$cnt_y\ge B$ 时，我们发现 $y$ 中的许多点是不可能产生贡献的，例如当序列形如 `xyyyyyyyyxx` 时，中间的 $y$ 是不可能对答案产生贡献的，我们可以将其删去变成 `xyyyyxx` （$y$ 保留四个的原因是因为最左面的 $x$ 和最右面的 $x$ 不可能同时对答案产生贡献），我们发现 $y$ 中的无用点删去后序列大小是 $O(B)$ 的，暴力计算即可，时间复杂度最大为 $O(\frac{n^2\log n}{B})$。

```cpp
// qwq
#include <bits/stdc++.h>
#define gc getchar()
using namespace std;
typedef long long ll;
constexpr int N=3e5+20;
unordered_map<ll,ll>Ans;
vector<int>e[N];
ll b[N];
bool vis[N<<2]; ll s[N<<2];
set<int>P[N];
int a[N],n,q,c[N],num,B,typ[N];
inline void mer(int x,int y){
    int xn=e[x].size(),yn=e[y].size();
    int i=0,j=0; num=0;
    while(i<xn||j<yn){
        if(i==xn){c[++num]=e[y][j++];continue;}
        if(j==yn){c[++num]=e[x][i++];continue;}
        c[++num]=(e[x][i]<e[y][j]?(e[x][i++]):(e[y][j++]));
    }
}
inline ll calc(int x,int y){
    vis[n]=1; s[n]=0;
    ll ans=-1e18,sum=0;
    for(int i=1,cur=n;i<=num;i++){
        cur+=(a[c[i]]==x?1:-1),sum+=b[c[i]];
        if(vis[cur])
            ans=max(ans,sum-s[cur]),
            s[cur]=min(s[cur],sum);
        else vis[cur]=1,s[cur]=sum;
    }
    sum=0; vis[n]=0;
    for(int i=1,cur=n;i<=num;i++){
        cur+=(a[c[i]]==x?1:-1);
        vis[cur]=0;
    }
    return ans;
}
inline ll bl(int x,int y){return mer(x,y),calc(x,y);}
vector<set<int>::iterator>itr;
inline ll small_big(int x,int y){
    if(e[x].size()>e[y].size())swap(x,y); num=0;
    for(auto pos:e[x]){
        c[++num]=pos; auto it=P[y].lower_bound(pos);
        if(it!=P[y].begin()){
            --it,itr.push_back(it),c[++num]=*it;
            if(it!=P[y].begin())
                --it,itr.push_back(it),c[++num]=*it,++it;
            ++it;
        }
        if(it!=P[y].end()){
            itr.push_back(it),c[++num]=*it,++it;
            if(it!=P[y].end())itr.push_back(it),c[++num]=*it;
            --it;
        }
        for(auto it:itr)P[y].erase(it);
        itr.clear();
    }
    sort(c+1,c+num+1);
    ll res=calc(x,y);
    for(int i=1;i<=num;i++)
        if(a[c[i]]==y)P[y].insert(c[i]);
    return res;
}
inline int in();
inline void wr(ll x);
int main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    n=in(),q=in(),B=400;
    for(int i=1;i<=n;i++)
        e[a[i]=in()].push_back(i),P[a[i]].insert(i);
    for(int i=1;i<=n;i++)typ[i]=(e[i].size()<=B);
    for(int i=1;i<=n;i++)b[i]=in();
    while(q--){
        static int x,y;
        x=in(),y=in();
        if(Ans.count(1ll*x*(n+1)+1ll*y)){
            cout<<Ans[1ll*x*(n+1)+1ll*y]<<'\n';
            continue;
        }
        if(typ[x]==typ[y]){
            ll res=bl(x,y);
            Ans[1ll*x*(n+1)+1ll*y]=Ans[1ll*y*(n+1)+1ll*x]=res;
            wr(res),putchar('\n');
            continue;
        }
        ll res=small_big(x,y);
        Ans[1ll*x*(n+1)+1ll*y]=Ans[1ll*y*(n+1)+1ll*x]=res;
        wr(res),putchar('\n');
    }
    return 0;
}
inline int in(){
    int x=0,bo=0; char c;
    while(!isdigit(c=gc))if(c=='-')bo=1;
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=gc;
    return bo?-x:x;
}
inline void wr(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>=10)wr(x/10);
    putchar(x%10+48);
}
```



---

## 作者：huazai676 (赞：0)

[题目](https://www.luogu.com.cn/problem/P8349)

### $n,q \leq 5000$

每次询问把两个序列取出来分别对序列 $ \left\{ b_i \right\}$ 和 $ \left\{ c_i \right\}$ 求前缀和为 $ \left\{ sb_i \right\} \left\{ sc_i \right\}$，每次即求 $\max\limits_{i>j,sc_i-sc_j=0}sb_i-sb_j$，拿桶从左到右扫一遍。

### $a$ 的取值不超过 $500$ 种

本题的关键点1，发现本质不同的询问只有 $500 \times 500=k^2$ 种，记 $cnt_i$ 为 $i$ 的出现次数，看似单次询问 $x \ y$ 为 $O(cnt_x+cnt_y)$ 最后被卡到 $O(k^2n)$，实际上复杂度均摊 $O(\sum\limits_{i=1}^k\sum\limits_{j=1}^kcnt_i+cnt_j)=O(\sum\limits_{i=1}^kk \times (cnt_i+cnt_j))=O(kn)$，可过。

### $n \leq 3 \times 10^5,q \leq 10^6$

结合以上两种做法，考虑根号分治。当 $cnt_x,cnt_y \leq B$ 时，用法1；$cnt_x,cnt_y>B$ 时，法2复杂度为 $O(\frac{n^2}{B})$；本题关键点2在于 $cnt_x \leq B,cnt_y>B$ 的情况，回到题目本身限制区间内两种数个数相等，$y$ 个数太多后很多区间本身便不合法了，所以可以对于每个 $x$，在左右两边与其它 $x$ 不重复的选两个（选两个是为了保留那些起分割作用的 $y$，防止最后答案取到原本不合法的区间）相近的 $y$，再扔到法1中复杂度依然是对的，可以用 set 实现。

代码不长，但常数很大。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<set>
#include<cmath>
#define PII pair<int,int>
#define x first
#define y second

using namespace std;

typedef long long ll;

const int N=3e5+10;
const ll inf=0x7f7f7f7f7f7f7f7f;

int n,m,B,cnt[N],w[N];
vector<int> pos[N];
set<int> s[N];
unordered_map<int,ll> mp[N];

vector<PII> t;
ll buc[N<<1];
ll calc(vector<int>&a,vector<int>&b)
{
	vector<PII>().swap(t);
	buc[n]=0;
	ll res=-inf;
	for(auto i:a) t.push_back({i,1});
	for(auto i:b) t.push_back({i,-1});
	sort(t.begin(),t.end());
	int now=0;
	ll sum=0;
	for(auto i:t)
	{
		now+=i.y,sum+=w[i.x];
		res=max(res,sum-buc[now+n]);
		buc[now+n]=min(buc[now+n],sum);
	}
	now=0;
	for(auto i:t)
	{
		now+=i.y;
		buc[now+n]=inf;
	}
	return res;
}

vector<int> tmp;
bool add(int v,set<int>::iterator& it)
{
	if(abs(*it)!=1e9)
	{
		auto it0=it;
		it0++;
		tmp.push_back(*it);
		s[v].erase(it);
		it=it0;
		return true;
	}
	return false;
}
int main()
{
	memset(buc,0x7f,sizeof buc);
	scanf("%d%d",&n,&m);
	B=sqrt(n)+1;
	for(int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		pos[k].push_back(i);
		cnt[k]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>B)
		{
			s[i].insert(1e9),s[i].insert(-1e9);
			for(int j:pos[i])
				s[i].insert(j);
		}
	}
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(cnt[u]>cnt[v]) swap(u,v);
		if(cnt[u]<=B&&cnt[v]<=B) printf("%lld\n",calc(pos[u],pos[v]));
		else if(cnt[u]>B&&cnt[v]>B)
		{
			if(mp[u].count(v)) printf("%lld\n",mp[u][v]);
			else printf("%lld\n",mp[u][v]=calc(pos[u],pos[v]));
		}
		else
		{
			vector<int>().swap(tmp);
			for(auto i:pos[u])
			{
				auto it=s[v].lower_bound(i);
				auto it0=it;
				if(add(v,--it0)) add(v,--it0);
				if(add(v,it)) add(v,it);
			}
			printf("%lld\n",calc(pos[u],tmp));
			for(auto i:tmp) s[v].insert(i);
		}
	}
	
	return 0;
}
```


---

