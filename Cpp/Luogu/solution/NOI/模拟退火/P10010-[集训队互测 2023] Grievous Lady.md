# [集训队互测 2023] Grievous Lady

## 题目背景

对立从那灰暗的塔楼进入，逐步踏入这个扭曲的迷宫深处。

对立的心突然绞痛起来。

对立后退了一步，扑腾了一下便跪倒下来。

未及碰到，灰黑的地板就突然崩裂瓦解，先一步向下坠落。

先前收集的纷争碎片，连同塔楼本身，一同化作了一场倾盆大雨，包围在对立四周。

异象骤起，对立的思维也陷入一片混乱。

塔楼落入了先前的由光芒碎片组成的欢乐海洋，但对立却被纷争碎片紧紧地包裹着。

在那由光芒和纷争碎片交错的风暴之中，对立所见的只有那些令人厌恶的纷争碎片。

那枚世界尽头的记忆映入了对立的视野。

面对着世界一点点地走向终结的景象，对立的理性在碎裂。

对立意识到，一切美好的记忆不过是须臾，最终都会走向破灭。

四周的碎片依旧在飞旋，对立试图看清那些玻璃碎片的变换。

对立意识到，现在围绕着的那些碎片，正以最恐怖的方式运转。

这个碎片风暴所带来的「忧郁度」，可以被简单地描述为外侧碎片的旋转速度之和乘上内侧碎片的旋转速度之和。

一片玻璃碎片在外侧总是以一种速度正旋，而在内侧总是以另一种速度逆旋。

每片碎片都是是来自不同世界的刹那记忆，故而其转速总可以认为是独立随机指定的。

在残存无几的希望将尽未尽之时，对立只想知道，现在的碎片风暴的忧郁度，也就是最大可能的忧郁度，究竟是多少。

## 题目描述

共有 $n$ 个元素，标号 $1\sim n$，每个元素 $j$ 有两个正整数权值 $a_j,b_j$。

你要确定一个 $[1,n]\cap\mathbb N$ 的子集 $S$，从而最大化

$$
\left(\sum_{k=1}^na_k[k\in S]\right)\left(\sum_{k=1}^nb_k[k\notin S]\right)
$$

这个问题显然不可做，因此**保证每个 $a_j,b_j$ 分别在 $[1,A]\cap\mathbb N,[1,B]\cap\mathbb N$ 内独立均匀随机生成**。

现在给定 $n,A,B$ 和每个元素的两个权值 $(a_j,b_j)$，请求出这个最大的答案。

## 说明/提示

#### 输入输出样例

**因为本题数据规模太大，直接提交评测会对评测机带来很大压力，本题将提供很多大样例；请尽量减少本题的提交次数。**

请参见下发文件 `grievouslady*.in/ans`，共 $50$ 组，基本按照部分分的方法造。

由于本题保证数据随机，不提供手搓样例。

#### 数据范围与提示

对于所有的数据，保证 $10\le n\le3000$，$10^4\le A,B\le10^{12}$，$1\le T\le50$。

~~本题设置子任务，各子任务~~共 $100$ 个测试点。具体的测试点分布可以见下表。

**本题在洛谷上的版本不设置子任务**。

（**由于表格比较宽，洛谷上较难完整显示，你可能要使用题目页面的“展开”功能**）

|测试点编号|$n$|$A$|$B$|测试点编号|$n$|$A$|$B$|测试点编号|$n$|$A$|$B$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1\sim2$|$=10$|$=10^4$|$=10^4$|$33\sim34$|$=100$|$=10^4$|$=10^4$|$67\sim68$|$=1000$|$=10^5$|$=10^{12}$|
|$3\sim4$|$=10$|$=10^9$|$=10^9$|$35\sim36$|$=100$|$=10^5$|$=10^5$|$69\sim70$|$=1000$|$=10^9$|$=10^9$|
|$5\sim6$|$=10$|$=10^{12}$|$=10^{12}$|$37\sim38$|$=100$|$=10^5$|$=10^9$|$71\sim72$|$=1000$|$=10^{12}$|$=10^{12}$|
|$7\sim8$|$=20$|$=10^4$|$=10^4$|$39\sim40$|$=100$|$=10^9$|$=10^9$|$73\sim74$|$=1500$|$=10^5$|$=10^{12}$|
|$9\sim10$|$=20$|$=10^9$|$=10^9$|$41\sim42$|$=100$|$=10^{12}$|$=10^{12}$|$75\sim76$|$=1500$|$=10^9$|$=10^9$|
|$11\sim12$|$=20$|$=10^{12}$|$=10^{12}$|$43\sim44$|$=200$|$=10^5$|$=10^{12}$|$77\sim78$|$=1500$|$=10^{12}$|$=10^{12}$|
|$13\sim14$|$=30$|$=10^4$|$=10^4$|$45\sim46$|$=200$|$=10^9$|$=10^9$|$79\sim80$|$=2000$|$=10^5$|$=10^{12}$|
|$15\sim16$|$=30$|$=10^9$|$=10^9$|$47\sim48$|$=200$|$=10^{12}$|$=10^{12}$|$81\sim82$|$=2000$|$=10^9$|$=10^9$|
|$17\sim18$|$=30$|$=10^{12}$|$=10^{12}$|$49\sim50$|$=300$|$=10^5$|$=10^{12}$|$83\sim84$|$=2000$|$=10^{12}$|$=10^{12}$|
|$19\sim20$|$=40$|$=10^4$|$=10^4$|$51\sim52$|$=300$|$=10^9$|$=10^9$|$85\sim86$|$=2500$|$=10^4$|$=10^9$|
|$21\sim22$|$=40$|$=10^9$|$=10^9$|$53\sim54$|$=300$|$=10^{12}$|$=10^{12}$|$87\sim88$|$=2500$|$=10^5$|$=10^{12}$|
|$23\sim24$|$=40$|$=10^{12}$|$=10^{12}$|$55\sim56$|$=500$|$=10^5$|$=10^{12}$|$89\sim90$|$=2500$|$=10^9$|$=10^9$|
|$25\sim26$|$=50$|$=10^4$|$=10^4$|$57\sim58$|$=500$|$=10^9$|$=10^9$|$91\sim92$|$=2500$|$=10^{12}$|$=10^{12}$|
|$27\sim28$|$=50$|$=10^4$|$=10^9$|$59\sim60$|$=500$|$=10^{12}$|$=10^{12}$|$93\sim94$|$=3000$|$=10^4$|$=10^9$|
|$29\sim30$|$=50$|$=10^9$|$=10^9$|$61\sim62$|$=800$|$=10^5$|$=10^{12}$|$95\sim96$|$=3000$|$=10^5$|$=10^{12}$|
|$31\sim32$|$=50$|$=10^{12}$|$=10^{12}$|$63\sim64$|$=800$|$=10^9$|$=10^9$|$97\sim98$|$=3000$|$=10^9$|$=10^9$|
|||||$65\sim66$|$=800$|$=10^{12}$|$=10^{12}$|$99\sim100$|$=3000$|$=10^{12}$|$=10^{12}$|

~~我们按如下方式布局各测试点~~：
* ~~subtask $1$：$1\sim12$，占 $\rm12pts$~~。
* ~~subtask $2$：$13\sim32$，占 $\rm20pts$~~。
* ~~subtask $3$：$33\sim36$，占 $\rm4pts$~~。
* ~~subtask $4$：$37\sim48$，占 $\rm12pts$~~。
* ~~subtask $5$：$49\sim50$，占 $\rm2pts$~~。
* ~~subtask $6$：$51\sim60$，占 $\rm10pts$~~。
* ~~subtask $7$：$61\sim72$，占 $\rm12pts$~~。
* ~~subtask $8$：$73\sim84$，占 $\rm12pts$~~。
* ~~subtask $9$：$85\sim92$，占 $\rm8pts$~~。
* ~~subtask $10$：$93\sim100$，占 $\rm8pts$~~。

~~**本题不设置子任务依赖，因此请确保经样例测试后你的算法正确后再提交，以免卡评测机**。~~

#### 后记

这个世界——一切——都源于过去。过去的影像，哪怕是欢乐的记忆，就像是白昼过后的黑夜，渐渐导致了这份世界末日。

泪水盈眶。对立的眼神转为一片黑暗。

对立与这些玻璃起了共鸣，围绕于四周的回忆之壳开始崩裂。

对立就身处其中，站在那炫目的光芒前方，已经没有任何情感了。

扭曲的迷宫，也在对立的力量下，悉数损毁……

时光逝去，对立变了。不再激情地收集回忆，而是近乎无意识地走在这世界之中，并不再抱有任何雄心壮志。

如今，对立正在一个破旧坍塌的建筑旁行走着，旋转着某天在废墟中找到的太阳伞。

# 题解

## 作者：Aventurine_stone (赞：15)

## 1. 题目分析
这道题一眼搜索或者动规，~~因为我看不出来怎么动规~~，所以准备用搜索解这道题。


------------
## 2. 题目做法
### (1) 直接暴力搜索 (12pts)
我们将 $r$ 当作题目中 $a$，$b$ 数组的长度，将 $c$ 当作搜索到哪一层了，这样我们便可以写出暴力代码：
```cpp
__int128 ans;
__int128 x,y;
void dfs(int r,int c)
{
	if(c==r+1)
	{
		__int128 s=x*y;
		if(s>ans)
			ans=s;
		return ;
	}
	x+=a[c].x;
	dfs(r,c+1);
	x-=a[c].x;
	y+=a[c].y;
	dfs(r,c+1);
	y-=a[c].y;
}
```
此算法时间复杂度为 $O(2^n)$ 让我们再看看数据范围，$n\le3000$，这不得直接 T 飞？
### (2) 整体贪心+局部搜索(100pts)
~~本蒟蒻也是看了第一篇题解才有的思路~~，我们发现，因为题目数据范围是随机的，并且值域非常大，所以 $a$ 和 $b$ 的值一般不会太接近，我们只需要取更大的那个数即可。

但是这样做会有缺点，如果有 $a$ 和 $b$ 比较接近的情况出现，便很容易举出反例，这一部分我们就只能用搜索解决。

于是，我们可以先将 $a$，$b$ 数组以 $\frac{a}{b}$ 为排序标准进行降序排列，然后取正中间的 $100$ 个左右的断点进行枚举，先将断点左边大部分数和右边大部分数加入总数中，再暴力搜索断点附近的一些数更新答案就行了。

求总和的代码大概是这样：
```cpp
void sum(int k)
{
	x=0,y=0;
	//确定搜索范围
	int l=max(1,k-5),r=min(n,k+5);
	//整体贪心
	for(int i=1;i<l;i++)
		x+=a[i].x;
	for(int i=r+1;i<=n;i++)
		y+=a[i].y;
	//局部搜索
	dfs(r,l);
}
```
这样就可以将这道题切掉了。

---

## 作者：Wf_yjqd (赞：7)

数据随机的友好的乱搞题。不知道咋是黑的。

------------

随机数据下 $a$，$b$ 的和相差不会太大。

显然对于任意一个 $i$，若 $a_i$ 和 $b_i$ 的差较大，一定会选更大的，这样能获得更多倍的较小数的和。

于是直接按 $\frac{a_i}{b_i}$ 排序，枚举一个断点，一边选 $a$，另一边选 $b$。

由于 $a_i$ 和 $b_i$ 差较小的时候上面的结论容易出现反例，将断点附近的几个暴搜下分给 $a$ 和 $b$。

这样复杂度是 $\operatorname{O}(2^kn)$，其中 $k$ 表示断点附近暴搜的个数，实际 $k$ 取到 $10$ 就足以通过所有了。

不过如果你想跟我抢最优解，还可以利用一个性质。

随机数据下最终 $a$ 和 $b$ 选的个数也不会相差太多，考虑断点会在最中间的几个（$100$ 个就能稳过）。

这样上面复杂度中的 $n$ 可以取到 $100$，虽然实测没快多少是了。

------------

为防 xxs 水黑，不放代码了就。

---

## 作者：Fujxxx (赞：6)

先考虑贪心，对每个元素按照 $\frac{a}{b}$ 从大到小排序，靠前的元素取 $a$ 更好，靠后则取 $b$ 更好。

发现不难构造这个贪心思路的反例。但是出现问题的元素总是出现在排序后的序列中点左右，因为中点附近 $a$ 和 $b$ 相差不大。

因此我们对大部分元素进行贪心，中点附近的元素可以随机处理，也可以暴搜。

有一些细节，如前缀和优化，特别要注意的是中点附近的范围和随机处理的范围界定，这两个范围要注意大小，同时注意不要越界。多测记得清空。

下面给出参考代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
const int MAXN=3010,DELTA=100,TEMP=7;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
inline void print(int x){ string res; while(x) res+=(x%10+'0'),x/=10; reverse(res.begin(),res.end()); cout<<res<<'\n'; }
struct Node{ int x,y; double pri; }a[MAXN];
int T,n,A,B,ans,cntx[MAXN],cnty[MAXN];
inline bool cmp(Node x,Node y){ return x.pri>y.pri; }
void dfs(int pos,int ed,int nowx,int nowy){
	if(pos>ed) ans=max(ans,nowx*nowy);
	else{
		dfs(pos+1,ed,nowx+a[pos].x,nowy);
		dfs(pos+1,ed,nowx,nowy+a[pos].y);
	}
}
signed main(){
	T=read(),n=read(),A=read(),B=read();
	while(T--){
		for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read(),a[i].pri=(double)a[i].x/a[i].y;
		sort(a+1,a+1+n,cmp);
		ans=cntx[0]=cnty[n+1]=0;
		for(int i=1;i<=n;i++) cntx[i]=cntx[i-1]+a[i].x;
		for(int i=n;i>=1;i--) cnty[i]=cnty[i+1]+a[i].y;
		for(int i=max((int)1,n/2-DELTA);i<=min(n/2+DELTA,n);i++)
			dfs(max((int)1,i-TEMP+1),min(n,i+TEMP-1),cntx[max((int)0,i-TEMP)],cnty[min(n+1,i+TEMP)]);
		print(ans);
	}return 0;
}
```

---

## 作者：LinkCatTree (赞：4)

首先发现，因为数据随机，所以选取 $a_i,b_i$ 中较大的那一个应该比较优。不过这样贪心显然是有问题的，可以随便举一组反例：

```
3 2
4 1
```

显然选取 $S=\{2\}$ 最优，而根据选择较大数的贪心则发生错误。感性理解一下，当 $a$ 与 $b$ 接近时，贪心发生错误的可能性就更大，于是我们可以在贪心的基础上对 $a,b$ 较为接近的数据进行暴力搜索来提高正确性。

具体的，我们可以先按照 $\dfrac{a_i}{b_i}$ 进行排序，选取中间的若干对数据进行暴搜。假设选取以 $i$ 为中心的 $k$ 个数暴搜 $m$ 次，总的时间复杂度就为 $\mathcal{O}(T \cdot 2^km)$。

主要代码：

```cpp
void dfs(int now,int r,__int128 suma,__int128 sumb) {
	if(now>r) {
		ans=max(ans,suma*sumb);
		return ;
	}
	dfs(now+1,r,suma+vec[now].first,sumb);
	dfs(now+1,r,suma,sumb+vec[now].second);
	return ;
}
void solve(int pos) {
	int l=max(pos-8,0),r=min(pos+8,n-1);
	__int128 suma=0,sumb=0;
	for(int i=0;i<l;i++) suma+=vec[i].first;
	for(int i=r;i<n;i++) sumb+=vec[i].second;
	dfs(l,r-1,suma,sumb);
	return ;
}

int main() {
	scanf("%d%d%lld%lld",&T,&n,&mxa,&mxb);
	while(T--) {
		vec.clear(),ans=0;
		for(int i=1;i<=n;i++) {
			scanf("%lld%lld",&a,&b);
			vec.emplace_back(a,b);
		}
		sort(vec.begin(),vec.end(),[](pll a,pll b) {
			return (db)a.first/a.second>(db)b.first/b.second;
		});
		__int128 suma=0,sumb=0;
		l=max(n/2-36,0),r=min(n/2+36,n-1);
		for(int i=l;i<=r;i++) solve(i);
		write(ans),putchar('\n');
	}
	return 0;
}
```

不要超代码，我们共建新洛谷。

---

## 作者：gghack_Nythix (赞：3)

## 前言：

感觉这个题目数据过于友好了，瞎搞都能过。

## 分析：

对于这种不可做题目，我们尝试使用随机化算法。具体来说，我们先初始化一个我们认为的最优状态，然后尝试每次随机让一个点更换集合。我们猜测，在数据随机的情况下，$|S|=\frac{n}{2}$ 应该是比较优秀的。然后我们就令 $|S|=\frac{n}{2}$，开始对原序列使用爬山法，每次只接受比当前状态更优秀的状态，这样爬山大约十几次就可以通过了。

```cpp
# include <bits/stdc++.h>
# define int __int128
using namespace std;
const int N = 5e5 + 5;
mt19937 rnd (1145141919810);
inline int rint(){
	int res=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
void print(int x){
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline int bbs(int x){ return (x > 0 ? x : -x); }
int n , A , B , a[N] , b[N] , ans , Ca , Cb , id[N] , op[N];
void Random_adjustment () {
	for (int i = 80808 ; ~ i ; i --) {
		int pos = rnd () % n + 1;
		if (op[id[pos]] && (Ca + a[id[pos]]) * (Cb - b[id[pos]]) > ans) 
		ans = (Ca + a[id[pos]]) * (Cb - b[id[pos]]) , Ca += a[id[pos]] , Cb -= b[id[pos]] , op[id[pos]] ^= 1;
		if (!op[id[pos]] && (Ca - a[id[pos]]) * (Cb + b[id[pos]]) > ans) 
		ans = (Ca - a[id[pos]]) * (Cb + b[id[pos]]) , Ca -= a[id[pos]] , Cb += b[id[pos]] , op[id[pos]] ^= 1;
	}
}
void solve () {
	ans = 0 , Ca = Cb = 0;
	int rans = 0;
	for (int i = 1;i <= n;++i) a[i] = rint() , b[i] = rint() , id[i] = i;
	for (int sanb = 1 ; sanb <= 18; ++ sanb) {
		shuffle (id + 1 , id + n + 1 , rnd);//随机编号
		Ca = 0 , Cb = 0;
		for (int i = 1;i <= (n >> 1) ; ++i) op[id[i]] = 0 , Ca += a[id[i]];
		for (int i = (n >> 1) + 1 ; i <= n; ++i) op[id[i]] = 1 , Cb += b[id[i]];
		ans = Ca * Cb;
		Random_adjustment ();
		rans = max (rans , ans);
	}
	print (rans);
	putchar ('\n');
	return void();
}
signed main () {
	// freopen ("grievouslady5.in" , "r" , stdin);
	int T; T = rint();
	n = rint() , A = rint() , B = rint();
	while (T -- >0) solve ();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P10010)

**题目大意**

> 给定 $a_1\sim a_n,b_1\sim b_n$，选出一个子集 $S$ 最大化 $\sum_{i\in S}a_i\times \sum_{i\not \in S}b_i$。
>
> 数据范围：$n\le 3000$，数据随机。

**思路分析**

由于数据随机，因此考虑一些随机化算法，随机一组初始态出发开始爬山，每次翻转一个点的状态，如果更优就转移。

但这样显然难以通过，利用数据随机的性质，我们发现此时 $|S|$ 应该很接近 $\dfrac n2$，因此从一组 $|S|=\dfrac n2$ 的解出发开始爬山即可。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LL __int128
using namespace std;
const int MAXN=3005;
mt19937 rnd(998244353);
int n,id[MAXN];
ll a[MAXN],b[MAXN];
bool s[MAXN];
void solve() {
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i],id[i]=i;
	LL Z=0;
	for(int o=32;o;--o) {
		shuffle(id+1,id+n+1,rnd);
		LL A=0,B=0;
		for(int i=1;i<=n/2;++i) s[i]=0,A+=a[i];
		for(int i=n;i>n/2;--i) s[i]=1,B+=b[i];
		LL X=A*B;
		for(int q=62500;q;--q) {
			int x=rnd()%n+1;
			if(s[x]) {
				if(X<=(A+a[x])*(B-b[x])) s[x]^=1,A+=a[x],B-=b[x],X=A*B;
			} else {
				if(X<=(A-a[x])*(B+b[x])) s[x]^=1,A-=a[x],B+=b[x],X=A*B;
			}
		}
		Z=max(Z,X);
	}
	string z;
	while(Z) z+=Z%10+'0',Z/=10;
	reverse(z.begin(),z.end());
	cout<<z<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; ll A,B; cin>>T>>n>>A>>B;
	while(T--) solve();
	return 0;
}
```

---

## 作者：hypixel_zhb666 (赞：1)

# 题目大意

给出 $n$ 个元素，每个元素有两个权值 $a_i$ 和 $b_i$，从中选出若干元素，令取出元素的 $a_i$ 之和为 $S_a$，其余元素的 $b_i$ 之和为 $S_b$，最大化 $S_a\times{S_b}$。

# 分析

$a_i$，$b_i$ 的值分别在 $[1,A]$，$[1,B]$ 间均匀随机生成，所以 $a_i$，$b_i$ 之和相差并不大，贪心选更大的 $S_a$ 和 $S_b$ 即可得出最优解。

可以按 $\frac{a_i}{b_i}$ 排好序后在中点附近枚举断点，差不多枚举 $100$ 个即可。

最后断点左边都选 $b_i$，右边都选 $a_i$，得出的结果取 max，记得开 int_128。

# 优化

但是当 $a_i$，$b_i$ 本身相差很小甚至相等时，按如上方法求解很容易举出反例。

所以每个断点附近还要进行几次暴搜来保证正确性（实测搜 $10$ 个即可）。

# 代码

```cpp
#include <bits/stdc++.h>
#define cys __int128
using namespace std;
const int maxn=3009;
int T,n;
long long A,B;
cys ans,l,r;
struct node{
	cys a,b;
}s[maxn];
inline cys read(){
	cys res=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
void write(cys x){
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
bool cmp(node x,node y){return 1.0*x.a/x.b>1.0*y.a/y.b;}
cys dfs(int step,cys X,cys Y){
	if(step==r+1) return X*Y;
	return max(dfs(step+1,X+s[step].a,Y),dfs(step+1,X,Y+s[step].b));
}
int main(){
	scanf("%d%d%lld%lld",&T,&n,&A,&B);
	while(T--){
		for(int i=1;i<=n;i++) s[i].a=read(),s[i].b=read();
		sort(s+1,s+n+1,cmp);ans=0;
		for(int k=max(1,n/2-50);k<=min(n,n/2+50);k++){
			cys x=0,y=0;
			l=max(1,k-5),r=min(n,k+5);
			for(int i=1;i<l;i++) x+=s[i].a;
			for(int i=r+1;i<=n;i++) y+=s[i].b;
			ans=max(ans,dfs(l,x,y));
		}
		write(ans),puts("");
	}
	return 0;
}
```

~~那么多随机算法标签结果只有数据是随机的，好水的黑题~~。

---

## 作者：zhangxiaoyu008 (赞：0)

[题目传送门](/problem/P10010)

[$\mathtt{My \ Blog}$——题解：P10010 [集训队互测 2023] Grievous Lady](/article/lw39clee)

注意到~~几乎~~所有这道题的题解都是搜索+贪心或 Local search[^1]。

[本题正解](https://qoj.ac/download.php?type=solution&id=7768)

对于这种一看就没有思路的题目，我们可以用随机化~~骗分~~。

首先随机一个顺序，然后让一开始的 $S$ 为 $1$ ~ $\displaystyle\lfloor\frac{n}{2}\rfloor$（因为随机，所以最终答案的 $|S|$ 应该是 $\displaystyle\lfloor\frac{n}{2}\rfloor$ 左右）。

后面做下面的操作若干次。
1. 随机选择一个编号
2. 如果这个编号在 $S$ 里，把这个编号从 $S$ 里去除，否则把这个编号加入 $S$。
3. 如果答案更优，更新答案，否则撤回刚才的 2. 操作

还有，就是怎么写 `mt19937` 的 `seed`（代码高亮部分），可以参考 [这个 $\mathtt{Blog}$](https://codeforces.com/blog/entry/61675) 和 [ 另一个 $\mathtt{Blog}$](https://codeforces.com/blog/entry/60442)。

俗话说的好
> 代码五分钟，调参五小时

:::info[$\large{\mathbf{Code}}$]{open}
[AC 记录](https://www.luogu.com.cn/record/227375540)

如果过不了，多交几遍就可以了。（逃
```cpp lines=23-28 line-numbers
#include <bits/stdc++.h>
using namespace std;‌‍
typedef long long LL;‌‍
typedef __int128 i128;‌‍
const int N = 3e3 + 10;‌‍
int T, n, p[N];‌‍
LL A, B, a[N], b[N];‌‍
i128 suma, sumb, ans;‌‍
bool is_in[N];‌‍
template<typename T> inline void read(T &x) {‌‍‌‍
	x = 0;‌‍ T f = 1;‌‍ char ch = getchar();‌‍
	while(!isdigit(ch)) {‌‍‌‍ if(ch == '-') f = -1;‌‍ ch = getchar();‌‍ }‌‍‌‍
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();‌‍
	x *= f;‌‍
}‌‍‌‍
template<typename T, typename... Args> inline void read(T &x, Args &...args) {‌‍‌‍
	read(x), read(args...);‌‍
}‌‍‌‍
void print(i128 x) {‌‍‌‍
	if(x > 9) print(x / 10);‌‍
	putchar(x % 10 + '0');‌‍
}‌‍‌‍
seed_seq seq{‌‍‌‍
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) new char
}‌‍‌‍;‌‍
mt19937 rnd(seq);‌‍
void local_search() {‌‍‌‍
	for(int i = 0;‌‍ i < 62500;‌‍ i ++) {‌‍‌‍
		int r = rnd() % n + 1;‌‍
		if(is_in[p[r]]) {‌‍‌‍ // is in B
			if((suma + a[p[r]]) * (sumb - b[p[r]]) > ans) {‌‍‌‍
				suma += a[p[r]];‌‍
				sumb -= b[p[r]];‌‍
				ans = suma * sumb;‌‍
				is_in[p[r]] = false;‌‍
			}‌‍‌‍
		}‌‍‌‍
		else {‌‍‌‍ // is in A
			if((suma - a[p[r]]) * (sumb + b[p[r]]) > ans) {‌‍‌‍
				suma -= a[p[r]];‌‍
				sumb += b[p[r]];‌‍
				ans = suma * sumb;‌‍
				is_in[p[r]] = true;‌‍
			}‌‍‌‍
		}‌‍‌‍
	}‌‍‌‍
}‌‍‌‍
void solve() {‌‍‌‍
	i128 res = 0;‌‍
	for(int i = 1;‌‍ i <= n;‌‍ i ++) {‌‍‌‍
		read(a[i], b[i]);‌‍
		p[i] = i;‌‍
	}‌‍‌‍
	for(int i = 1;‌‍ i <= 25;‌‍ i ++) {‌‍‌‍
		shuffle(p + 1, p + n + 1, rnd);‌‍
		suma = sumb = 0;‌‍
		for(int i = 1;‌‍ i <= (n >> 1);‌‍ i ++) {‌‍‌‍
			is_in[p[i]] = false;‌‍
			suma += a[p[i]];‌‍
		}‌‍‌‍
		for(int i = (n >> 1) + 1;‌‍ i <= n;‌‍ i ++) {‌‍‌‍
			is_in[p[i]] = true;‌‍
			sumb += b[p[i]];‌‍
		}‌‍‌‍
		ans = suma * sumb;‌‍
		local_search();‌‍
		res = max(res, ans);‌‍
	}‌‍‌‍
	print(res);‌‍
	putchar('\n');‌‍
}‌‍‌‍
int main()
{‌‍‌‍
	read(T, n, A, B);‌‍
	while(T --) solve();‌‍
	return 0;‌‍
}‌‍‌‍
```
:::
[^1]: 即[爬山算法](https://baike.baidu.com/item/%E7%88%AC%E5%B1%B1%E6%B3%95)

---

