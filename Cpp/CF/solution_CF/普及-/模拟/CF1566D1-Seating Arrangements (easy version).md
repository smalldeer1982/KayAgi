# Seating Arrangements (easy version)

## 题目描述

It is the easy version of the problem. The only difference is that in this version $ n = 1 $ .

In the cinema seats can be represented as the table with $ n $ rows and $ m $ columns. The rows are numbered with integers from $ 1 $ to $ n $ . The seats in each row are numbered with consecutive integers from left to right: in the $ k $ -th row from $ m (k - 1) + 1 $ to $ m k $ for all rows $ 1 \le k \le n $ .

  $ 1 $

 $ 2 $  $ \cdots $  $ m - 1 $  $ m $  $ m + 1 $

 $ m + 2 $  $ \cdots $  $ 2 m - 1 $  $ 2 m $  $ 2m + 1 $

 $ 2m + 2 $  $ \cdots $  $ 3 m - 1 $  $ 3 m $  $ \vdots $

 $ \vdots $  $ \ddots $  $ \vdots $  $ \vdots $  $ m (n - 1) + 1 $

 $ m (n - 1) + 2 $  $ \cdots $  $ n m - 1 $  $ n m $ The table with seats indicesThere are $ nm $ people who want to go to the cinema to watch a new film. They are numbered with integers from $ 1 $ to $ nm $ . You should give exactly one seat to each person.

It is known, that in this cinema as lower seat index you have as better you can see everything happening on the screen. $ i $ -th person has the level of sight $ a_i $ . Let's define $ s_i $ as the seat index, that will be given to $ i $ -th person. You want to give better places for people with lower sight levels, so for any two people $ i $ , $ j $ such that $ a_i < a_j $ it should be satisfied that $ s_i < s_j $ .

After you will give seats to all people they will start coming to their seats. In the order from $ 1 $ to $ nm $ , each person will enter the hall and sit in their seat. To get to their place, the person will go to their seat's row and start moving from the first seat in this row to theirs from left to right. While moving some places will be free, some will be occupied with people already seated. The inconvenience of the person is equal to the number of occupied seats he or she will go through.

Let's consider an example: $ m = 5 $ , the person has the seat $ 4 $ in the first row, the seats $ 1 $ , $ 3 $ , $ 5 $ in the first row are already occupied, the seats $ 2 $ and $ 4 $ are free. The inconvenience of this person will be $ 2 $ , because he will go through occupied seats $ 1 $ and $ 3 $ .

Find the minimal total inconvenience (the sum of inconveniences of all people), that is possible to have by giving places for all people (all conditions should be satisfied).

## 说明/提示

In the first test case, there is a single way to arrange people, because all sight levels are distinct. The first person will sit on the first seat, the second person will sit on the second place, the third person will sit on the third place. So inconvenience of the first person will be $ 0 $ , inconvenience of the second person will be $ 1 $ and inconvenience of the third person will be $ 2 $ . The total inconvenience is $ 0 + 1 + 2 = 3 $ .

In the second test case, people should sit as follows: $ s_1 = 2 $ , $ s_2 = 1 $ , $ s_3 = 5 $ , $ s_4 = 4 $ , $ s_5 = 3 $ . The total inconvenience will be $ 6 $ .

## 样例 #1

### 输入

```
4
1 3
1 2 3
1 5
2 1 5 3 3
1 2
2 1
1 6
2 3 2 1 1 1```

### 输出

```
3
6
0
1```

# 题解

## 作者：Jur_Cai (赞：3)

### 题意
给 $n\times m$ 个座位依次编号（编号方式如题面表格所示），视力差的人座位编号要小（视力相同不要求）。$n\times m$ 个人依次进入（先到所在行的编号较小端，再到所在位置），但如果此人座位所在行编号比它小的座位上已经有人坐着，就会带来一点 $\lceil$ 不便 $\rfloor$，求怎么安排 $\lceil$ 不便 $\rfloor$ 的值最小。
> 本题 $n=1$。

### 分析
唯一能安排的就只有相同视力的座位，可以发现同一视力能坐的位置范围是固定的，很显然的贪心就是坐在尽可能靠后的位置。

实际处理的时候可以化简一下，就只要统计坐着的有多少人在他前面，即视力比他差（利用 $n=1$ 的性质），相同视力就不用特殊处理了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[5][305];
int main() {
	int T,n,m;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&a[i][j]);
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=1;k<j;k++)
					if(a[i][k]<a[i][j]) ans++;
		cout<<ans<<'\n';
	} 
	return 0;
}
```

---

## 作者：Accepted_Error (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1566D1)

## 题目大意

有 $n × m$ 个座位，视力差的人坐在编号小的位置上，视力好的人坐在编号大的位置上。如果在这一行上比这人编号小的位置上有人坐了，就会产生 “不便”。求怎样安排座位使 “不便” 最小。

## 题目分析

“不便” 就是累计矩阵中新增的位置靠后的数比几个位置靠前的数大，换成题目中的语言就是统计有多少人坐在新加入的人前面，运用贪心的思路尽量把人安排在后面即可。

## AC Code
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<cstdlib>
using namespace std;
const int N=310;
int t,n,m,cnt;//cnt记录造成"不便"的次数 
int a[N][N];//矩阵记录上面坐的人 
int main()
{
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				for(int k=1;k<j;k++)
				{
					if(a[i][k]<a[i][j]) cnt++;//如果靠前面的数比靠后面的数小，就造成一次"不便" 
				}
			}
		}
		cout<<cnt<<endl;
	} 
	return 0;
}

```

---

## 作者：Neilchenyinuo (赞：0)

- 本题用贪心来做。

## 题目大意

给 $n\times m$ 个座位依次编号（编号方式如题面表格所示），视力差的人座位编号要小（视力相同不要求）。$n\times m$ 个人依次进入（先到所在行的编号较小端，再到所在位置），但如果此人座位所在行编号比它小的座位上已经有人坐着，就会带来一点 $\lceil$ 不便 $\rfloor$，求怎么安排 $\lceil$ 不便 $\rfloor$ 的值最小。

## Solution

1. 唯一能安排的就只有相同视力的座位，可以发现同一视力能坐的位置范围是固定的，很显然的贪心就是坐在尽可能靠后的位置。

2. 对此，我们可以直接开一维数组存储每个人的视力。

3. 暴力枚举每个人坐座位，计算前面有多少个视力比他好的人就可以得到答案。

4. 时间复杂度 $O(m^2t)$，足以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans,a[1005];
int main(){
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			cin>>a[i];
			for(int j=1;j<i;j++)
				if(a[j]<a[i])	
					ans++;
		}
		cout<<ans<<"\n";
	} 
	return 0;
}
```


---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1566D1)

这道题简单的原因是在于限制条件，即 $n=1$。

对此，我们可以直接开一维数组存储每个人的视力，暴力枚举每个人坐座位，计算前面有多少个视力比他好的人就可以得到答案。

时间复杂度 $O(m^2t)$。由于数据较小，可以通过本题。

代码：

```cpp
#include<cstdio>
int t,n,m,a[10005];
int main(){
	scanf("%d",&t);
	while(t--){
		int s=0;
		scanf("%d%d",&n,&m);
		for(register int i=1;i<=m;++i){
			scanf("%d",&a[i]);
			for(register int j=1;j<i;++j)
				if(a[j]<a[i])//计算不便值 
					s++;
		}
		printf("%d\n",s);
	}
	return 0;
}
```
Bye！

---

## 作者：The_FAKIR (赞：0)

由于题意大家已经说过了，这里就不过多赘述。

## 思路
因为题目限制了 $n=1$，所以相当于一个一维数组。那么我们只需看一下他的前面有多少个视力比他好的人，在统计一下总共的不便值就行了。

而且由于 $ 1 \le m \le 300 $，所以大可不必担心超时。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int x,n,m,ans,sl[10010]; 
int main(){
	cin>>x;
	for(int i=1;i<=x;i++){
		ans=0;
		scanf("%d%d",&n,&m);
		for(int j=1;j<=m;j++){
			scanf("%d",&sl[j]); 
			for(int k=1;k<j;k++){
				if(sl[k]<sl[j]) ans++; 
			}	
		}
		printf("%d\n",ans);
	} 
	return 0;
}
```


---

## 作者：liukangyi (赞：0)

# 题目大意
给你 $T$ 组样例，每组样例中有 $n\times m$ 个人的视力值（但因为题目说 $n$ 等于 $1$，所以也就相当于是 $m$ 个数），现在，想让你求出**靠前的人的视力值比后面的人的小**的组数。


------------

# 分析
这道题完全就是一个暴力题，每枚举到一个位置，就从他前面看看哪个值小于当前位置的值，并且累加起来，最后输出即可。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,ans,a[310]; //定义变量。因为n等于1所以只用一维数组 
int main(){
	cin>>T;
	while(T--){
		ans=0;
		scanf("%d%d",&n,&m); //输入 
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i]); //把它们当一位数组来输入 
			for(int j=1;j<i;j++) //从第一个位置到i的前面一个位置遍历 
				if(a[j]<a[i]) //如果前面的比后面的小，组数++ 
					ans++;
		}
		printf("%d\n",ans); //输出答案 
	} 
	return 0;
}
```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1566D1)

### **[题意解析]**
给定一个 $n \times m$ 的二维数组，表示有 $n \times m$ 个座位，让我们安排每个人坐在那个座位，使不便值最小。而所谓的不便值就是：**视力好的人坐在了视力差的人前面，挡住了后面的人**。这样就会产生不便。

### **[思路分析]**
为了使不便值能尽量的小，**我们可以使用贪心的策略**，考虑局部最优解：**尽量把视力好的人安排在一行的后面，视力差的人安排在一行的前**面。这样就能使我们的不便值最小，且没有后效性。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[110][110],sum; 
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		/*n ×m个座位*/
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				cin>>a[i][j];
		/*n ×m个视力值*/
		sum=0;
		/*统计不便值的变量记得清0*/
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				for(int k=1; k<j; k++)
					/*在一行里找到前面的人比后面的人的的情况数*/
					if(a[i][j]>a[i][k])sum++;/*统计答案*/
		cout<<sum<<"\n";	
	}
    return 0;
}
```


---

## 作者：江户川·萝卜 (赞：0)

题意其他人都已经给了，这里不多赘述。

先来模拟一下样例：

```
1 5
2 1 5 3 3
```
先是 2 下座：
```
_ 2 _ _ _
```
1 下座：
```
1 2 _ _ _
```
5下座：
```
1 2 _ _ 5
```
此时不便次数为 2。

接下来：
```
1 2 _ 3 5
```
```
1 2 3 3 5
```
不便次数为 6。

可以发现，每次不便，是一个大的数经过一个已落座的小的数产生的。也就是后面的数比前面的数大的次数。

这不就是逆序对的个数吗！

由于此题范围小，甚至可以用冒泡求逆序对。

---

## 作者：GaryH (赞：0)

# CF1566D1&D2 题解

**题意**：

给定 $n \times m$ 个数和一个初始为空的 $n \times m$ 大小的矩阵，要求将数一一填入矩阵，并满足任意两个位置的价值的大小关系与两个位置里填入的数的大小关系相同。

求一种方案，使得依次填入每一个数的代价和最小，并输出这个最小值，其中填入一个数的代价是其位置左边已填入的数的个数，位置 $(x,y)$ 的价值是 $x \times m + y$

显然，对于任意两个不相同的数，它们两个填入的位置的价值的大小关系是确定的，那么假设所有数两两不等，则填数的方案数就已经确定了。

那么，若是有相同的数，又该如何处理呢？

为了方便表示，我们记该数值为 $x$ ，等于该值的数的下标分别为 $i_1,i_2,...,i_k$ ，则这些数在一一放置好后，最终所在的位置对应到矩阵上，一定形成了几段连续的区间。并且，这些位置的价值也一定在值域上连续。那么，我们需要确定的，就是相同的数的放置方法。

再理一理思路，我们注意到，放数的先后顺序的决策权不在我们手中，我们手中的决策权，只能确定每个数最终在的位置，并且这个放置位置的方案还必须满足对于数之间大小关系的限制，故我们真正可以决定的，只有相同数的放置位置。

这时，我们采用一个贪心的思路，且一定是最优的。

可以考虑两个相同的数，它们所放置的位置带来的影响：

设有两个数 $a,b$ ，值都为 $x$ ，目前有 $(x,y),(x,y+1)$ 两个位置可供放置,而数 $a,b$ 分别在第 $j,k$ 次放入。不妨设 $j<k$ 。

此时，我们说：将 $a$ 放到位置 $(x,y+1)$ ，将 $b$ 放到位置 $(x,y)$ 一定更优，因为这样放对答案的贡献为 $0$ ；而若是将 $a$ 放到位置 $(x,y)$ ，将 $b$ 放到位置 $(x,y+1)$ ，这样的贡献是 $1$ ,就没有刚才的方法更优。

我们由此可以联想到真正的电影院里的座位：在最里面的人最先进去，在最外面的人最后进去，这样安排一定是最方便的，且每个人经过的人也最少。

那我们只需要按照这个宗旨去处理这个问题即可：

每次找到等于值 $x$ 的所有数的下标 $i_1,i_2,...,i_k$ ，若它们可选的所有位置在同一行，我们就按它们填入的先后顺序倒序安排座位；若它们可选的所有位置不在同一行，则每一行中都倒序排列，而所有位置所在行中最上面那不一定完整的一行放最大的若干个数，最下面那不一定完整的一行放最小的若干个数即可。

（当然，由于 D1题中只有一行，所以D1中直接倒序放即可）

于是我们只需先确定每个数所在的座位，再按题意模拟算贡献即可，时间复杂度是 $O(nm^2)$ ，本题可以通过。

但实际上，在模拟算贡献时，我们需要对每一行支持单点修改，区间查询，这时我们可以不遍历整行，而是每一行维护一个树状数组，来快速的支持这个操作，此时时间复杂度优化到了 $O(nmlogm)$。

至于实现方法，可以在下面的代码和注解里看到。（~~我的实现方法可能很烂~~）

**code:**

```

const int N(305);

int n,m;
int idx;

int a[N*N];

inline bool cmp(int x,int y){return x>y;}

struct BIT{
	// 树状数组
	int t[N<<2];
	void add(int x,int val){
		while(x<=m)t[x]+=val,x+=(x&-x);
	}
	int qry(int x){
		int res=0;
		while(x)res+=t[x],x-=(x&-x);
		return res;
	}
}bit[N];

inline pii gtline(int pos){
	// 算出矩阵中某个权对应的行和列
	int x=(pos/m);
	if(x*m!=pos)x++;
	int y=pos%m;
	if(!y)y=m;
	return mp(x,y);
}

int pla[N*N];

inline void work(){
	// 多组数据
	map < int , vector < int > > buk ;
    	// buk 的作用是将每个数按权值归类
	n=read(),m=read(),idx=0;
	int ALL=n*m,ans=0;
	rep(i,1,ALL)buk[a[i]=read()].pb(i);
	sort(a+1,a+ALL+1); int T=unique(a+1,a+ALL+1)-a-1;
    	// 排序后去重，即可避免处理重复的数
	int now=0;
	rep(i,1,T){
		int sz=buk[a[i]].size();
		int st=now+1,en=now+sz;
		pii tmps=gtline(st),tmpe=gtline(en);
		int sx=tmps.fi,sy=tmps.se;
		int ex=tmpe.fi,ey=tmpe.se;
		sort(buk[a[i]].begin(),buk[a[i]].end());
		if(sx==ex){
			per(j,sz-1,0)pla[buk[a[i]][j]]=(++now);
			continue;
		}
		per(j,m-sy,0)pla[buk[a[i]][j]]=(++now);
		per(j,sz-ey-1,m-sy+1)pla[buk[a[i]][j]]=(++now);
		per(j,sz-1,sz-ey)pla[buk[a[i]][j]]=(++now);
        	// 处理出每个数最终填入的位置
	}
	rep(i,1,ALL){
		pii tmp=gtline(pla[i]);
		int x=tmp.fi,y=tmp.se;
		ans+=bit[x].qry(y-1),bit[x].add(y,1ll);
        	// 按题意算贡献
	}
	cout<<ans<<endl;
	rep(i,0,n)rep(j,0,(m<<2))bit[i].t[j]=0ll;
	rep(i,1,(n*m))pla[i]=0ll;
    	// 多组数据一定要清空！！！
}

int main(){
	int tasks=read();
	while(tasks--)work();
	return 0;
}

```

---

## 作者：KSToki (赞：0)

# 题目大意
有 $m$ 个人和 $m$ 个座位，每个人对应一个值 $a_i$，$a_i$ 越小的人要坐越靠前，从第 $1$ 个人到第 $m$ 个人依次从前往后走，代价为经过的人数，安排座位最小化总代价。
# 题目分析
题目对座位安排已经规定得比较死了，分析可得只有 $a_i$ 相同的才能在内部互换。首先可以找出每一个 $a_i$ 对应了可以坐哪些位置，既然在剩余可坐区间内每个位置的代价都是相同的，每个人都贪心地尽量往后坐就行了。

选座位计算代价可以暴力计算复杂度是 $O(m^2)$ 的，可以通过，但我~~追求复杂度~~比较懒直接套了树状数组。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,a[301],t[301],k,cnt[301],s[301],c[301],v[301];
I void update(int x,int v)
{
	for(;x<=m;x+=lowbit(x))
		c[x]+=v;
} 
I int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=c[x];
	return res;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		For(i,1,m)
		{
			t[i]=a[i]=read();
			cnt[i]=s[i]=v[i]=c[i]=0;
		}
		sort(t+1,t+m+1);
		k=unique(t+1,t+m+1)-t-1;
		For(i,1,m)
		{
			a[i]=lower_bound(t+1,t+k+1,a[i])-t;
			++cnt[a[i]];
		}
		For(i,1,k)
			s[i]=s[i-1]+cnt[i];
		int ans=0;
		For(i,1,m)
		{
			ans+=sum(s[a[i]-1]);
			update(s[a[i]]-v[a[i]],1);
			++v[a[i]];
		}
		putint(ans);
	}
	return 0;
}

```

---

