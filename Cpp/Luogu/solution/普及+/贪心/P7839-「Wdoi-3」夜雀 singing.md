# 「Wdoi-3」夜雀 singing

## 题目背景

“唉，今天可真是多事的一天呢。不过一晚的忙碌结束了，接下来就是我尽展歌喉的时刻啦！”

作为幻想乡妖精中的一份子，米斯蒂娅在闲暇之余（也就是夜雀食堂闭店之后）也会去参加由夜雀们自发组织而成的夜雀歌会。夜雀们会按照一种约定好的方式进行歌唱。在今夜的歌会中，米斯蒂娅成为了歌会的组织者。

然而因为大家都是夜雀，因此所谓的“舞台”其实是由若干个高度不一的树组成的。夜雀都会飞（显然），因此它们可以不断地变换自己的位置。

然而，由于夜雀的数目实在是太多，以至于作为组织者的米斯蒂娅搞不清楚活动的组织方案了。你能帮帮她吗？

## 题目描述

我们可以将这 $n$ 棵树从 $1$ 到 $n$ 编号。其中，在 $m$ 个点上分布着参加舞会的夜雀。第 $i$ 棵树的高度为 $h_i$ 。

夜雀们的歌会一共会进行 $t$ 时刻。第 $i$ 个时刻，夜雀们**只能**在高度严格大于 $i$ 的树上唱歌。因为这些树木都是事先被选择好的，因此总是有 $\max\{h_i\}>t$。夜雀们每个时刻，**可以选择站着不动**，或移动到**编号相邻**的一棵树上（例如，原先在编号为 $i$ 的树上的夜雀，下个时刻可以移动到编号为 $i-1$ 或者 $i+1$ 的树上。不过，她们不能移动到编号为 $0$ 或 $n+1$ 的树上）。初始时为第 $0$ 时刻。也就是说，假使一个夜雀初始时在高度为 $1$ 的树上，那么她下一时刻不得不去高度大于 $1$ 的树上。

但这样一些夜雀可能无法顺利完成歌会，会遇到“无处可走”的情况，于是夜雀们决定选择若干个大树作为飞行点。如果一个夜雀到达了某个飞行点，那么下一时刻她除了能移动到编号相邻的树上，还能**到达其他的飞行点**。

然而，飞行点太多容易使得歌会变得非常混乱。因此，米斯蒂娅希望最小化飞行点的数目。你能帮帮她吗？

## 说明/提示

#### 样例 1 解释

一个最优方案是，分别在第 $2,5$ 棵树建立飞行点，下表为各夜雀的一个可行移动方案：

$$\def{\arraystretch}{1.8}
\begin{array}{|c|c|c|c|} \hline
\textsf{\textbf{夜雀编号}} & \textsf{\textbf{时刻 $0$ 所在位置}} & \textsf{\textbf{时刻 $1$ 所在位置}} & \textsf{\textbf{时刻 $2 \sim 4$ 所在位置}} \cr\hline
\textsf1 & 5 & 5 & 5 \cr\hline
\textsf2 & 3 & 2 & 5 \cr\hline
\textsf3 & 2 & 5 & 5 \cr\hline
\end{array}$$  

可以证明不存在更优解。

---

#### 数据范围及约定

$$
\def{\arraystretch}{1.6}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{特殊性质} & \textbf{分值} \cr\hline
1 & 16 & - & 15 \cr\hline
2 & 5\times 10^5 & \text{A} & 5 \cr\hline
3 & 5\times 10^5 & \text{B} & 15 \cr\hline
4 & 10^3 & - & 25 \cr\hline
5 & 5\times 10^5 & - & 20 \cr\hline
6 & 5\times 10^6 & - & 20 \cr\hline
\end{array}$$

- 特殊性质 A：$\min(h_i) > t$。
- 特殊性质 B：$t > n$ 且 $h_i \in \{1,t-1,t+1\}$。

对于 $100\%$ 的数据，满足 $1 \le n,m \le 5 \times 10^6$，$1 \le h_i,t \le 10^9$，$1 \le p_i \le n$。保证 $p$ 互不相同，且 $\max(h_i) > t$。

---
    
#### 提示

显然你可以将所有位置都作为飞行点，然后在第 1 时刻让所有夜雀都飞到一棵 $h_i > t$ 的树来得到一组答案为 $n$ 的合法解。因此本题不会存在无解情况。

## 样例 #1

### 输入

```
5 3 4
1 2 1 4 5
5 3 2 
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 7 9
8 1 1 5 13 10 1 1 6 3 
2 4 7 10 6 8 9 
```

### 输出

```
3```

# 题解

## 作者：itisover (赞：6)

被神仙slzs安利做了一下，可惜神仙slzs没能赛时切掉。

对于每一个鸟，我们可以处理出它左边最远能走到的点和右边能走到的最远的点，那么这个鸟能活动的范围就是一个区间。对于这个区间里面，如果有一个点的高度大于给出的时刻总数 $t$，那么这只鸟就是安全的，我们不用管了。对于不安全的鸟，我们要给它们放一些传送点，让它能够传到安全的地方。

首先，有一个传送点要放在一个高度大于给出的时刻总数 $t$ 的位置，单独加上。可以发现，剩下的问题可以转化为：对于所有不安全的鸟的区间，放置最少的点使得所有区间都被覆盖，这是经典的最少点覆盖区间问题，可以用贪心解决。

我们把所有区间按左端点从小到大排序，然后贪心地选当前区间最远的点（右端点），如果这个区间的左端点大于上个区间的右端点，则说明需要再添加一个点，总点数加一即可，注意要处理一下有区间完全包含另一个区间的情况，这种情况只能取被包含的区间来算，我用了取 $min$ 也可以解决这个问题。

回到处理每只鸟能走的区间的问题，如果单独考虑左右端点中的一个可以发现它具有单调不降，可以像马拉车类似的思想，如果之前的鸟能走到的最远的点小于等于当前鸟的位置，则暴力跑一遍跑出当前鸟的最远点并记录下来，如果之前的鸟能走到的最远点大于当前鸟的位置，则当前的鸟也一定可以走到那个最远点（因为走到最远点用掉的时间会比前一个点用时更少），所以直接从最远点开始跑暴力就行了。复杂度 $\Theta(n+m)$。

至此我们解决了这题，别忘了最后的答案加上最开始单独考虑的 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T>
inline T read(){
    T ans=0,f=0;char ch=getchar();
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch)) ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
    return f?-ans:ans;
}
const int N=5e6+5;
int n,m,t,ans;
int a[N],p[N],sum[N],vis[N];
struct zfz{
    int l,r;
}line[N];
bool cmp(zfz x,zfz y){return x.l<y.l;}
int main(){
    n=read<int>(),m=read<int>(),t=read<int>();
    for(int i=1;i<=n;++i) a[i]=read<int>();
    for(int i=1;i<=m;++i) p[i]=read<int>();
    sort(p+1,p+1+m);
    int Max=0,T;
    for(int i=1;i<=m;++i){
        if(p[i]>Max) T=0,Max=p[i];
        else T=Max-p[i];
        while(T+1<a[Max+1]) ++T,++Max;
        line[i].r=Max;
    }
    Max=n;
    for(int i=m;i;--i){
        if(p[i]<Max) T=0,Max=p[i];
        else T=p[i]-Max;
        while(T+1<a[Max-1]) ++T,--Max;
        line[i].l=Max;
    }
    sort(line+1,line+1+m,cmp);
    for(int i=1;i<=n;++i) sum[i]=sum[i-1]+(a[i]>t);
    for(int i=1;i<=m;++i) vis[i]=sum[line[i].r]-sum[line[i].l-1]>0?1:0;
    int last=0;
    for(int i=1;i<=m;++i){
        if(vis[i]) continue;
        if(line[i].l>last) ++ans,last=line[i].r;
        else last=min(last,line[i].r);
    }
    if(!ans) puts("0");
    else printf("%d",ans+1);
    return 0;
}
```



---

## 作者：VioletIsMyLove (赞：5)

拿到题目首先要想明白一个东西。

那就是对于所有夜雀，它们肯定只会飞 $1$ 次，这一次就是飞到高度大于 $T$ 的树上。

那么接下来只需要判断每一只夜雀，它是否能走到高度大于 $T$ 的树上，如果可以就不管，不行的话就需要记录一下。

在处理在哪些地方放飞行点的问题时，肯定是放在能让尽可能多的不能到达高度大于 $T$ 的树或者不能到达之前放过的飞行点的夜雀所能到达的地方。

构造上述的东西，只需要开 $2$ 个数组，分别记录当前的夜雀往左能走到最远的地方和往右能走到最远的地方。

那具体怎么处理在哪里放飞行点呢?

首先找到最靠左的一只不能到达高度大于 $T$ 的树的夜雀，在它往右所能到达的最远处的地方放一个飞行点，接着就可以往后去扫夜雀，直到扫到第一只往左走最远到不了这个飞行点的夜雀，以它为起点往右找到第一只能到达高度大于 $T$ 的树的夜雀(包括它)，在它往右所能到达的最远处的地方放一个飞行点，之后一直做上述操作即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,ans;
int h[5000005],a[5000005],L[5000005],R[5000005],s[5000005];
bool vis[5000005];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main(){
//	freopen("T4.in","r",stdin);
//	freopen("T4.out","w",stdout);
	n=read();m=read();t=read();
	for(int i=1;i<=n;i++)h[i]=read(),s[i]=s[i-1]+(h[i]>t);
	for(int i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+1+m);
	int x=a[1],t=0;
	for(int i=1;i<=m;i++){
		if(a[i]<=x){
			t=x-a[i];
			while(t+1<h[x+1]&&x<n)t++,x++;
			R[i]=x;
		}else{
			t=0;x=a[i];
			while(t+1<h[x+1]&&x<n)t++,x++;
			R[i]=x;
		}
	}
	for(int i=m;i>=1;i--){
		if(a[i]>=x){
			t=a[i]-x;
			while(t+1<h[x-1]&&x>1)t++,x--;
			L[i]=x;
		}else{
			t=0;x=a[i];
			while(t+1<h[x-1]&&x>1)t++,x--;
			L[i]=x;
		}
	}
	for(int i=1;i<=m;i++)if(s[R[i]]-s[L[i]-1])vis[i]=1;
	for(int i=1;i<=m;)if(!vis[i]){
		int x=R[i],j=i+1;
		while((L[j]<=R[i]||vis[j])&&j<=m)j++;
		i=j;ans++;
	}else i++;
	printf("%d\n",ans+(ans>0));
	return 0;
}
```


---

## 作者：0tAp (赞：2)

题目链接：[P7839 「Wdoi-3」夜雀 singing](https://www.luogu.com.cn/problem/P7839)


------------
这是一道关于贪心和找公共区间的题。

不难从题目中所给的关于**飞行点**的概念可以想到，只要可以传送，那么一定会传送到 $h_i>t$ 的一颗树上，如果不考虑要最少的飞行点的话，我们可以在每一个夜雀所在的点都与一个 $h_i>t$ 的点作为飞行点，考虑到要取到最少的飞行点的话，我们不妨看看是否存在一个点使得至少一个夜雀可以到达，对于相邻的两个夜雀来说，这个点一定是它们所能到达的公共区间内的一个点（**区间：一个夜雀所能到达的最右边的位置和最左边的位置**），那么对于这个点来说，我只用设一个飞行点，还有一种情况，就是对于公共区间内存在一个 $h_i>t$ 的点，那么很明显，我只需要使夜雀到这个位置即可，不需要飞行点，对于这个问题的解决，我们可以利用前缀和的思想：
$$
pre_i=pre_{i-1}+(h_i>t)
$$

利用这个思想，我们就可以很快的求出区间内是否存在这样一个点。

那么处理完以上情况就可以快乐 coding 了！！！



------------
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
const int N=5e6+10;

#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}


int n,m,t;
int h[N],p[N];
int pre[N];
bool bz[N];
struct A{
	int l,r;
}c1[N];

bool cmp(A a,A b){
	return a.l<b.l;
}

int main()
{
	n=read();m=read();t=read();
	rep(i,1,n){
		h[i]=read();
		if(h[i]>t){
			pre[i]=pre[i-1]+1;
		}
		else pre[i]=pre[i-1];
	}
	rep(i,1,m)p[i]=read();
	sort(p+1,p+1+m);
	
	int now_id=p[1],now=0;
	rep(i,1,m){
		now=(now_id>=p[i])?(now_id-p[i]):0;
		now_id=(now!=0)?now_id:p[i];
		while(h[now_id+1]>now+1&&now_id<n){
			now++;now_id++;
		}
		c1[i].r=now_id;
	}
	dwn(i,m,1){
		now=(p[i]>=now_id)?(p[i]-now_id):0;
		now_id=(now!=0)?now_id:p[i];
		while(h[now_id-1]>now+1&&now_id>1){
			now++;now_id--;
		}
		c1[i].l=now_id;
	}
	sort(c1+1,c1+1+m,cmp);
	
	rep(i,1,m){
		if(pre[c1[i].r]-pre[c1[i].l-1]>0){
			bz[i]=1;
		}
	}
	
	int ans=0;
	int last=0;
	
	rep(i,1,m)
	{
		if(bz[i])continue;
		if(c1[i].l>last){ans++;last=c1[i].r;}
		else last=min(last,c1[i].r);
	}
	if(ans==0)puts("0");
	else printf("%lld\n",ans+1);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

## 题目简述

有 $m$ 只鸟，$n$ 颗树，第 $i$ 个鸟在编号为 $p_i$ 的树上，第 $i$ 颗树高 $h_i$。

现在为零时刻，要求一直到 $t$ 时刻，每一只鸟在 $t_0$ 时刻所在树的高度均大于 $t_0$，并且鸟可以在一个时刻（不包括零时刻）跳到其他相邻树上。

要求建造一些传送门，每个传送门都可以去到任意有传送门的树上。为保证要求可实现，至少要建造多少的传送门？

## 题目分析

#### Subtask 1

直接爆枚，时间复杂度为 $\mathcal{O}(2^n\times n^2)$。

#### Subtask 2

每个鸟原地不动都能存活，输出 $0$。

#### Subtask 3

对于在高度为 $t+1$ 树上的鸟不动。

对于在高度为 $t-1$ 树上的鸟，如果一直向左或右能到达高度为 $t+1$ 的树上也不用考虑，否则在 $t-1$ 所组成的块位置打传送门均合法。

对于在高度为 $1$ 树上的鸟，若左右均为高度为 $1$ 的数就原地打传送门，否则往左右跑。

#### Subtask 4

下面称高度大于 $t$ 的树为安全树。

每只鸟最优解时必然只往左右单一方向跑，假设一只鸟最左能跑到 $l_i$ 最右能跑到 $r_i$，若 $[l_i,r_i]$ 内没有安全树，则在 $[l_i,r_i]$ 内打一传送门。

$l_i,r_i$ 可以用 $\mathcal{O}(n^2)$ 的方法求之，剩下的问题就转换成了一个简单的贪心。

以 $r_i$ 为关键字排序，从左到右，遇到要打传送门就放。

最后别忘了答案要加 $1$。（因为还有一个门要放到安全树上）。

#### Subtask 5

对枚举 $l_i,r_i$ 进行优化。

发现若对于 $i$ 鸟来说，一个树 $j$ 跑不上去的充要条件为


$$|p_i-j|\leq h_j$$

现在拿枚举 $l_i$ 作为例子，$r_i$ 类同。

因为 $j$ 一定在 $p_i$ 左边，所以即求 $p_i\leq j+h_j$ 的最大解，从 $p_i$ 往左枚举即可。（理论上是卡不过去的，但数据比较水）。

#### Subtask 6

正解，下面的 $i,j$ 的定义同上。

发现枚举 $l_i,r_i$ 还是不够快，但是可以发现 $j+h_j$ 是一个定值。

我们先对 $p_i$ 进行排序。容易发现当 $u$ 鸟在 $v$ 鸟左边时 $l_u\leq l_v$。于是每一次枚举只需要从上一个 $l$ 的位置开始枚举即可，时间复杂度 $\mathcal{O}(m+n)$。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN=5e6+5;
int n,m,t;
int h[MAXN],p[MAXN];
struct node{
	int l,r;
	bool live;
}a[MAXN]; 
int last=0,ans=0;
inline int read(){
	int re=0;char c=getchar();
	while(c>'9'||c<'0') c=getchar();
	while(c<='9'&&c>='0') re=10*re+c-'0',c=getchar();
	return re;
}
bool cmp(node x,node y){
	return x.r<y.r;
}
int main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
		h[i]=read();
	for(int i=1;i<=m;i++)
		p[i]=read();
	sort(p+1,p+m+1);
	a[0].r=p[1],a[m+1].l=p[m];
	for(int i=m;i>=1;i--){
		for(int j=min(a[i+1].l,p[i]);j>=0;j--){
			if(h[j]>t){
				a[i].live=true;
				a[i].l=j;
				break;
			}
			if(j+h[j]<=p[i])
				{a[i].l=j;break;}
			}
	}
	for(int i=1;i<=m;i++){
		for(int j=max(p[i],a[i-1].r);j<=n+1;j++){
			if(h[j]>t){
				a[i].live=true;
				a[i].r=j;
				break;
			}
			if(p[i]<=j-h[j])
				{a[i].r=j;break;}
		}
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)
		if(!a[i].live&&last<=a[i].l){
			ans++;
			last=a[i].r-1;
		}
	if(ans==0)
		cout<<"0";
	else
		cout<<ans+1;
	return 0;
}
```


---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/P7839)

不就是一个非常~~水~~的贪心吗？

对于每一只~~麻雀~~夜雀，可以预先处理出，它最左边能飞到哪，最右边能飞到哪，这样就行成了一个区间，这只~~麻雀~~夜雀只能在这里活动。如果在这个区间里，有一棵树的高度**大于** $t$，就证明这只~~麻雀~~夜雀是安全的，我们不用管它。

那如果没有呢？

那就需要安放一些飞行点，以帮助这些~~麻雀~~夜雀。

那怎么放呢？

至少有一个飞行点得放在一颗大于 $t$ 的树上。自证不难。

所以问题就转换成了：对于那些**不安全**的区间，需要放置最少的顶点，以覆盖整个区间。

很显然，这就是一个贪心的**区间覆盖问题**。

我们把这些不安全的区间的左端点，从小到大排序。

再遍历枚举：

1. 若这个区间的左端点比上一个的右端点小或相等，不用考虑。自证不难。

2. 若这个区间的左端点比上一个的右端点大，需要加一个飞行点。同样自证不难。

**特殊情况**：如题所述，别忘了可以将所有位置都作为飞行点，然后在最开始让所有~~麻雀~~夜雀都飞到一棵高度大于 $h$ 的树来得到一组答案。所以**答案还要加一**！

麻雀？夜雀？

---

## 作者：Aw顿顿 (赞：1)

首先简单讲一下特殊性质 Subtask 和小数据的过法：

- Subtask 1：爆搜可以过。
- 性质 A：不需要飞行点。
- 性质 B：考虑贪心策略，简单分类。

接着考虑一步步的优化。

首先每只夜雀如果要飞行，那么最优的策略一定是一次飞到高度大于 $t$ 的某颗树上，此后就无需再飞行了。而我们所需要考虑的重点在于：他们是否能够走到高度大于 $t$ 的某颗树上。

当然，在这过程中，有一些夜雀肯定是无法单凭走路到达目的地的，他们的活动范围被限制了，这个限制有什么意义呢？他们所能到达的范围内，如果有一个飞行点，那么他们就能够飞行到达目的地。

我们的目的显然是建立尽可能少的飞行点，那么如果一个飞行点能够供给给尽可能多的夜雀使用，是不是就更优呢？我们的飞行点需要供给给一类夜雀：他们既不能到达已经放置的飞行点，也不能到达符合要求的目的地。

因而具体的实现上可能还有所困难，我们已经可以开始着手准备了：预处理出每一个夜雀向左和向右可以到达的顶端。我们只要能够找到一个合理的顺序，一切就能迎刃而解，而从左往右是一个直观的解决方法。

那么我们考虑找到最靠左的一只符合上述条件的夜雀，在它往右所能到达的最远处的地方放一个飞行点。这样就可以尽可能扩展这一区间的贡献，然后将之后的夜雀进行判断——一旦找到另一只夜雀不能走到这个飞行点，就再按照同样的思想进行放置。这样的贪心策略是正确的，此处略去不证。

为体现主要过程，这里给出核心代码：

```cpp
//在读入和预处理之后：
	for(rint i=1;i<=m;++i){
		if(a[i]<=x){
			tmp=x-a[i];
			while(tmp+1<height[x+1]&&x<n)
				++tmp,++x;
			rig[i]=x;
		}else{
			tmp=0;x=a[i];
			while(tmp+1<height[x+1]&&x<n)
				++tmp,++x;
			rig[i]=x;
		}
	}
	for(rint i=m;i>0;--i){
		if(a[i]>=x){
			tmp=a[i]-x;
			while(tmp+1<height[x-1]&&x>1)
				++tmp,--x;
			lef[i]=x;
		}else{
			tmp=0;x=a[i];
			while(tmp+1<height[x-1]&&x>1)
				++tmp,--x;
			lef[i]=x;
		}
	}
	for(rint i=1;i<=m;++i)
		if(s[rig[i]]-s[lef[i]-1])
			vis[i]=1;
	int c=1;
	while(c<=m){
		if(!vis[c]){
			x=rig[c];tmp=c+1;
			while((lef[tmp]<=rig[c]||vis[tmp])&&tmp<=m)
				++tmp;
			c=tmp;++res;
		}else ++c;
	}
//之后分情况输出答案即可
```

---

## 作者：_shine_ (赞：0)

显然可以发现，一个安全的地点 $k$ 显然满足 $k>t$，而一只夜雀显然必须要到达任意一个 $k$。

则显然可见的是对于最初夜雀所站的位置 $p$，最优点必然是 $p$ 左右的两个 $k$，而如果左右两个点均不满足能直接到达，显然要加入飞行点。

但是直接查看在这一步显然不行，因时间超时的缘由考虑优化。

首先可以发现任意一只夜雀所能到达的点是拥有一个固定的区间的，而在这只夜雀右边的夜雀显然是能到达这只夜雀的右端点的（左边同理），那么显然这只夜雀不能直接到达的最优方案显然是在其左右端点建立飞行点，这样显然能拓展到最优。

但在这里显然要再次进行优化，因为此时的状态是在左右端点拓展，要拥有统一性在这里不妨考虑尝试每次在最右端点放置同时对今后的夜雀进行判断。

对于夜雀判断区间内是否有飞行点的一看就想到了区间修改区间查询的分块，但发现上文有分析一条性质（而在这只夜雀右边的夜雀显然是能到达这只夜雀的右端点的（左边同理）），则只需要记录下当前最右的飞行点即可。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=5e6+10;
int n,m,t,h[maxn],p[maxn];
pii a[maxn];int b[maxn];
int vis[maxn];
void out_put(){
    for(int i=1;i<=m;++i)cout << a[i].lx << " " << a[i].ly << endl;
    for(int i=1;i<=n;++i)cout << vis[i] << " ";cout << endl;    
}
signed main(){
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;++i)scanf("%d",h+i);
    for(int i=1;i<=m;++i)scanf("%d",p+i);
    sort(p+1,p+m+1);
    for(int i=1;i<=m;++i)a[i].lx=a[i].ly=p[i];
    a[0]=a[1],a[m+1]=a[m];
    for(int i=m;i>=1;--i){
        int num=p[i],cnt=a[i+1].lx;
        while(h[cnt]>num-cnt && cnt>=1)--cnt;
        a[i].lx=cnt+1;
    }
    for(int i=1;i<=m;++i){
        int num=p[i],cnt=a[i-1].ly;
        while(h[cnt]>cnt-num && cnt<=n)++cnt;
        a[i].ly=cnt-1;
    }
    sort(a+1,a+m+1);
    for(int i=1;i<=n;++i){if(h[i]>t)vis[i]=1;vis[i]+=vis[i-1];}
    // out_put();
    int num=-1,ans=0;
    for(int i=1;i<=m;++i){
        if(vis[a[i].ly]-vis[a[i].lx-1]!=0)continue;
        else if(num<a[i].lx)ans++,num=a[i].ly;  
    }
    if(ans!=0)printf("%d\n",ans+1);
    else puts("0");
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

比较套路的一个贪心。

可以发现，所有的雀最后都需要跳到一棵高度大于 $t$ 的树上。标记每一个高度超过 $t$ 的位置，如果有一些雀可以不用飞行点直接跳到这些位置上就直接不用考虑了。

否则就需要算出这些雀的可能活动范围，这个范围内至少需要有一个飞行点。这样问题也就转化为了：由若干个区间，要求这些区间中每一个区间内至少有一个被标记的点，求最小的标记点的个数。特殊地，需要额外标记一个高于 $t$ 的点以供飞行。当然，如果没有任何一个点需要被标记，那么这个高于 $t$ 的点也同样不需要被标记。

---
然后发现数据范围比较大，如果直接模拟这个进程是无法通过这道题的。考虑进一步挖掘一下求跳跃区间的范围的性质。

设当前雀的位置在 $p$，需要考虑的点在 $i$。为了方便，不妨令 $i>p$。写出式子：$i-p<a_{i}$，发现如果对于某一个位置 $p$ 有 $i$ 满足条件，一定有：$p+1$ 满足条件，通过 $i-p-1<i-p<a_i$ 简单推导出。

那么就可以利用这个性质进行解题了，将左右分开考虑，维护当前可以跳跃到的最左端后者最右端的位置 $r,l$，然后依次移动当前位置，并推动 $r$ 和 $l$ 指针移动。

由于每一个位置只会被考虑常数次，计算区间的复杂度就是 $O(n)$ 的。

总复杂度为 $O(n\log n)$，瓶颈在于排序。

---
### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10000006;
int n,m,t,h[MAXN],b[MAXN],ri,le,ans,x,sum[MAXN],cnt,cnt1;
struct str{
	int l,r;
	bool operator < (const str a)const{
		return r<a.r;
	}
}p[MAXN],q[MAXN];
int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++){
		scanf("%d",&h[i]);
		sum[i]=sum[i-1]+(h[i]>t);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		b[x]=i;
	}
	ri=1;
	for(int i=1;i<=n;i++){
		if(b[i]==0)continue;
		while(h[ri]>ri-i&&ri<=n)ri++;
		p[b[i]].r=ri-1;
	}
	
	le=n;
	for(int i=n;i>=1;i--){
		if(b[i]==0)continue;
		while(h[le]>i-le&&le>=1)le--;
		p[b[i]].l=le+1;
	}
	
	for(int i=1;i<=m;i++)
	if(sum[p[i].r]-sum[p[i].l-1]==0)
	q[++cnt]=p[i];
	
	sort(q+1,q+cnt+1);
	ri=0;
	
	for(int i=1;i<=cnt;i++){
		if(q[i].l<=ri)continue;
		ans++;ri=q[i].r;
	}
	
	if(ans==0)printf("0\n");
	else printf("%d\n",ans+1);
	
	return 0;
}
```


---

## 作者：haotian1234 (赞：0)

这道题目有点难难呢。（~~虽然说这只是一道贪心~~）
## 题意暗示
- 每一只夜雀最好飞一次，飞到高度大于 $T$ 的树上（如果这只夜雀已经在高度大于 $T$ 的树上，那么它就不用动了）
- 飞行点一定有一个在高度大于 $T$ 的树上面（~~否则你所有飞行点传送到高度小于$T$的树上那不就等于白传~~）
## 题目分析
主要的问题就是如何设置传送门了

我们可以将所有鸟可以飞到的区域给记录出来，然后这道题就变成了一道区间覆盖问题（大家可以看一下这道题 [$P2082$](https://www.luogu.com.cn/problem/P2082)），然后在这几个区间里建立飞行点，这样所有的鸟都可以飞到高度大于 $T$ 的树上

那如何找到所有鸟可以飞到的区域呢

那就要分情况讨论了：

1. 鸟可以走到的最远点的高度小于现在所在的树的高度，那么你就得用暴力找出这个鸟可以走到的最远点
1. 鸟可以走到的最远点的高度大于现在所在的树的高度，那么它可以走到的最远点就是这个最远点

然后你就可以找到这只鸟可以飞到的区域
## 题目坑点
1. 注意答案后面一定要加1，就是在高度大于 $T$ 的树上面的
1. 区间的数组与代表鸟在哪一棵树上的数组都要排序（都是从小到大）！！！
1. 要加快读，否则会超时

下面就要上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,t,w,ma,ans,i,a[5000100],p[5000100],f[5000100],b[5000100];
inline int read(){
	int re=0;char c=getchar();
	while(c>'9'||c<'0') c=getchar();
	while(c<='9'&&c>='0') re=10*re+c-'0',c=getchar();
	return re;
}//快读
struct no{
    int x,y;
}h[5000100];//结构体
bool cmp(no x,no y){return x.x<y.x;}//快排的自打算子
int main(){
    scanf("%d%d%d",&n,&m,&t);
    for(i=1;i<=n;i++) a[i]=read();
    for(i=1;i<=m;i++) p[i]=read();
    sort(p+1,p+1+m);//排序
    ma=0;
    for(i=1;i<=m;i++){
        if(p[i]>ma) T=0,ma=p[i];
        else T=ma-p[i];
        while(T+1<a[ma+1]) T++,ma++;
        h[i].y=ma;
    }//寻找左最远点
    ma=n;
    for(i=m;i>=1;i--){
        if(p[i]<ma) T=0,ma=p[i];
        else T=p[i]-ma;
        while(T+1<a[ma-1]) T++,ma--;
        h[i].x=ma;
    }//寻找右最远点
    sort(h+1,h+1+m,cmp);//区间的数组排序
    for(i=1;i<=n;i++) f[i]=f[i-1]+(a[i]>t);
    for(i=1;i<=m;i++) b[i]=f[h[i].y]-f[h[i].x-1]>0?1:0;
    w=0;
    for(i=1;i<=m;i++){
        if(b[i]) continue;
        if(h[i].x>w) ans++,w=h[i].y;
        else w=min(w,h[i].y);
    }//区间覆盖问题
    if(!ans) puts("0");
    else printf("%d",ans+1);
    return 0;
}
```


---

