# Vasya And Array

## 题目描述

```Vasya```有一个数组$a[1...n]$

你从来没听说过这个数组，但```Vasya```会告诉你 $m$ 条关于这个数组的信息。每条信息包含三个参数$t_i,l_i,r_i(0\leq t_i \leq 1 ,1 \leq l_i < r_i \leq n)$，其含义分别为：

- 如果 $t_i=1$ 则说明子数组$a[l_i...r_i]$ 是一个不降序列

- 如果 $t_i=0$ 则说明子数组$a[l_i...r_i]$ 不是一个不降序列。一个数组 $a$ **不是一个不降序列**说明存在两个相邻元素$a[i] ,a[i+1]$使得$a[i]>a[i+1]$

举个栗子：假设$a=[2,1,1,3,2]$ ，然后 ```Vasya``` 告诉你：

$t_1=1,l_1=2,r_1=4$，意思是 $a[2...4]=[1,1,3]$是一个不降序列

$t_1=0,l_1=4,r_1=5$，意思是 $a[4...5]=[3,2]$不是一个不降序列
$t_1=0,l_1=3,r_1=5$，意思是 $a[4...5]=[1,3,2]$不是一个不降序列

然而就算```Vasya``` 告诉你这么多条件，你依然不会知道数组 $a$，但是请你找出一种可能的情况。

## 样例 #1

### 输入

```
7 4
1 1 3
1 2 5
0 5 6
1 6 7
```

### 输出

```
YES
1 2 2 3 5 4 4
```

## 样例 #2

### 输入

```
4 2
1 1 4
0 2 3
```

### 输出

```
NO
```

# 题解

## 作者：emptysetvvvv (赞：9)

## 模拟

### 背景

小萌新$\varnothing$看了下，大部分题解都是$O(n^2)$的，对于本题的数据来说可以轻松$\mathtt{AC}$，**但是$O(n)$的方法也是存在的**，甚至更好写一点。

### 思路

- $mark[i]$表示$a[i]$是否必须小于等于$a[i+1]$，对于每一个$t_i=1$的$[l_i,r_i]$，我们需要标记$[l_i,r_i-1]$区间内的$mark$值都为$1$，为了实现这一点，我们可以$mark[l_i]++,mark[r_i]--$，最终线性扫一遍累加，就可以得到每个点的$mark$值，$mark[i]$为假就意味着$a[i]$必须大于$a[i+1]$。

- 在得到正确的$mark$值之后，对于每个$t_i=0$的$[l_i,r_i]$，我们需要检验$[l_i,r_i-1]$的$mark$值是否全为真，若全为真则说明矛盾。为了$O(1)$判断每个$[l_i,r_i-1]$，我们对$mark$数组的布尔值求前缀和，判断$s[r_i-1]-s[l_i-1]$是否等于$(r_i-1)-l_i+1$即可。

### 代码

```cpp
#include <iostream>
using namespace std;
int l[1005], r[1005], mark[1005], s[1005], n, m, cnt;
int main() {
	ios :: sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1, f, x, y; i <= m; i++) {
		cin >> f >> x >> y;
		if(f) ++mark[x], --mark[y];
		else l[++cnt] = x, r[cnt] = y; 
	}
	for(int i = 1; i < n; ++i) mark[i] += mark[i-1];
	for(int i = 1; i < n; ++i) mark[i] = mark[i] ? true : false, s[i] = mark[i] + s[i-1];	
	for(int i = 1; i <= cnt; ++i) 
		if(s[r[i]-1] - s[l[i]-1] == r[i] - l[i]) { puts("NO"); return 0; }
	puts("YES");
	for(int i = 1, num = n + 2; i <= n; i++) printf("%d ", mark[i-1] ? num : --num);
	return 0;
}
```

### p.s

小萌新$\varnothing$写的很仓促，不知道有没有什么问题，欢迎诸位神犇 hack。

---

## 作者：zcxnb (赞：3)

### 题目链接[CF1187C](https://www.luogu.com.cn/problem/CF1187C)
考虑 $t=0$ 时当且仅当区间内存在一个严格降序，这显然是不好处理的。

$t=1$ 时区间内所有的数都要满足不降序列，这显然是很好处理的。

我们先设 $z[i]=1$ 为 $a[i]\leq a[i+1]$，为 $z[i]=0$ 则有 $a[i]\leq a[i+1]$，$z[i]=2$ 则不确定。

然后我们先处理 $t=1$ 的情况，因为 $t=0$ 时无法立即处理。

将所有的 $t=1$ 的区间暴力修改为 $z[i]=1$，然后再暴力判断 $t=0$ 区间内是否存在 $z[i]\neq 1$ 的情况，若没有则不合法，否则修改为 $z[i]=0$。

在处理完 $z$ 数组后，我们按照 $z$ 的大小关系构造一种可行方案即可。

注意：因为 $z$ 数组的定义 $z[i]=1$ 为 $a[i]\leq a[i+1]$，所以区间要从 $l$ 枚举到 $r-1$。


```
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m,op,l,r,cnt;
int z[N],el[N],er[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)  z[i]=2;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&op,&l,&r);
		if(op==1){
			for(int j=l;j<r;j++){
				z[j]=1;
			}
		}
		else{
			cnt++;
			el[cnt]=l,er[cnt]=r;
		}
	}
	for(int i=1;i<=cnt;i++){
		bool tot=1;
		for(int j=el[i];j<er[i];j++){
			if(z[j]!=1){
				z[j]=0;
				tot=0;
				break;
			}
		}
		if(tot){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	int num=1000;
	for(int i=1;i<=n;i++){
		printf("%d ",num);
		if(z[i])  num++;
		else  num--;
	}
}
```

---

## 作者：伟大的王夫子 (赞：1)

首先，思路不难。就是先考虑$t_i = 1$的操作，再看看$t_i =0 $的操作里有没有与其矛盾。

构造一个差分数组$b_i = a_i - a_{i - 1}$


$\forall  i \in [1, m] t_i = 1$

我们有$a_j \ge a_{j - 1} 
(j \in [l_i+1, r_i])$

但是为了我们后面方便做标记，省去不必要的bool数组，排除等于的情况，即令$b_j=1$

然后再看看$t_i=0$时，若存在一个$j \in [l_i+1, r_i]$,使得$a_j < a_{j - 1}$或其大小关系不确定，则可行，否则不可行。

而$a_j,a_{j-1}$的大小关系可由数组$b_j$判断

我们以$a_1$为基准数，为了防止其余数字小于0，可赋值$a_1 = 10^5$

具体看代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, b[1010];//b[i] = a[i] - a[i - 1]
struct rec {
	int t, l, r;
	bool operator < (const rec &a) const {
		return t > a.t;
	}
} a[1010];
int main() {
	cin >> n >> m;
	for (register int i = 1; i <= m; ++i) scanf("%d%d%d", &a[i].t, &a[i].l, &a[i].r);
	sort(a + 1, a + m + 1);
	memset(b, 0, sizeof b);
	for (register int i = 1; i <= m; ++i) {
		if (a[i].t == 1) {
			for (register int j = a[i].l + 1; j <= a[i].r; ++j)
				b[j] = 1;//a[j] > a[j - 1]
		} else {
			bool flag = 1;
			for (register int j = a[i].l + 1; j <= a[i].r; ++j) {
				if (b[j] != 1) {
					b[j] = -1;//a[j] < a[j - 1]
					flag = 0;
					break;
				} 
			}
			if (flag) {
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	int ans = 1;////
	for (register int i = 1; i <= n; ++i) ans += b[i], cout << ans + 100000 << ' ';
}

```

---

## 作者：世末OIer (赞：1)

在开放hack时间段，试图hack了很多人，他们的解法都和我的不一样。。。

一题也没有FST，好开心。。
 
---

题解:

我们可以先将a[1]赋值为-1，a[2]赋值为9999,一次类推。a[i]=a[i-1]-1

这样所有的0区间就直接可以了！

接下来，对于每一个1区间，从l+1至r，a[i]=a[i-1]+1

这样1区间也满足了！

记得要使得所有的值>=1 !

最后判断一下新构造的数组是否合法就可以了。

程序:

```cpp
using namespace std;
pair<pair<int,int>,int> p[1001];
int n,m;
int a[1001];
inline bool cmp(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b){
	if(a.second!=b.second) return a.second==1;
	return a.first.first<b.first.first;
}
int mian(){
	cin>>n>>m;
	int i,j;
	for(i=1;i<=m;++i) cin>>p[i].second>>p[i].first.first>>p[i].first.second;
	for(i=1;i<=m;++i) for(j=1;j<=m;++j) if(i!=j and p[i].second==1 and p[j].second==0) if(p[i].first.first<=p[j].first.first and p[i].first.second>=p[j].first.second){
		cout<<"NO\n";
		return 0;
	} //如果一个1区间直接包含一个0区间，就直接输出“NO”
	sort(p+1,p+m+1,cmp); //排个序，左端点越小越靠前
	for(i=1;i<=n;++i) a[i]=-i;                 
	for(i=1;i<=m and p[i].second==1;++i) for(j=p[i].first.first+1;j<=p[i].first.second;++j) a[j]=a[j-1]+1;  //直接算1区间
//	for(i=1;i<=n;++i) cout<<a[i]<<' ';
//	cout<<endl;
	int mn=2147483647;
	for(i=1;i<=n;++i) mn=min(mn,a[i]); //使得所有的数都>=1
	if(mn<1){
		--mn;
		mn=-mn;
		for(i=1;i<=n;++i) a[i]+=mn;
	}
	for(i=1;i<=m;++i){  //最后的检查
		if(p[i].second==1){
			for(j=p[i].first.first+1;j<=p[i].first.second;++j) if(a[j]<a[j-1]){
				cout<<"NO\n";
				return 0;
			}
		}else{
			bool ok=1;
			for(j=p[i].first.first+1;j<=p[i].first.second;++j) if(a[j]<a[j-1]){
				ok=0;
				break;
			}
			if(ok){
				cout<<"NO\n";
				return 0;
			}
		}
	}
	cout<<"YES\n";
	for(i=1;i<=n;++i) cout<<a[i]<<' ';
	cout<<endl;
}
```

---

## 作者：Imakf (赞：1)

新鲜出炉的CF题

本题有个最初的想法，存下所有的$t,l,r$

开个```bool occ[1001]```

1.单独拿出所有 $t=1$ 的区间$[l,r]$赋值 $occ[i]=1$

2.再单独拿出 $t = 0$ 的区间$[l,r]$查看是否有存在一个点 $occ[i]\not =1$

如果都存在那就是```YES``` ，方案随便模拟

但是显然这是错的，比如下列数据

```cpp
4 3 
1 1 2 
1 3 4 
0 2 3
```

经过赋值，数组变为：
![](https://cdn.luogu.com.cn/upload/pic/61829.png)

但是```3 3 2 2```可以满足要求，答案是```YES```

所以这个算法错了

那我们是不是该放弃呢？

我们发现在这个样例中 $a[2],a[3]$ 之间

并不是真正的"连接"在一起的

其实是$a[2]$的"尾巴"接着$a[3]$的"头"

我们考虑把一个点拆成两个

其中原 $i$ 点对应的是新的 $i*2-1 \ , i*2$ 两个端点

![](https://cdn.luogu.com.cn/upload/pic/61830.png)

对于第一步区间赋值，我们做出下列调整

**对于左端点拆出来的两个点我们只赋值右边的**

**对于右端点拆出来的两个点我们只赋值左边的**

如图

![](https://cdn.luogu.com.cn/upload/pic/61833.png)

对于第二步检查合法性，也做出相应调整

![](https://cdn.luogu.com.cn/upload/pic/61835.png)

按照原先的套路，我们既然把一个点拆成两个

我们应该检查一个点里的点拆出来的两个点是否都为 $1$

但我们还这么做就失去了拆点的意义

所以我们改一下，去掉最左最右的两个端点

重新对齐一下方框，变得和区间赋值一样

![](https://cdn.luogu.com.cn/upload/pic/61836.png)

简直完美。

看看我给出的样例

```cpp
4 3 
1 1 2 
1 3 4 
0 2 3
```

![](https://cdn.luogu.com.cn/upload/pic/61837.png)

确实可以解决，查询出来是两个连续的 $0$

然后数组记得开两倍长度

```cpp
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
 
#define rg register
#define il inline
#define MX (1000 + 5)
 
struct qujian{
	int l ,r;
}p1[MX] ,p0[MX];
int t1 ,t0;
 
int add[MX * 2];
int n ,m;
int main(){
	scanf("%d%d" ,&n ,&m);
	add[n * 2 + 1] = true;
	for(rg int i = 1 ,op ,l ,r ; i <= m ; ++i){
		scanf("%d%d%d" ,&op ,&l ,&r);
		if(op == 1){
			p1[++t1] = (qujian){l ,r};	//单独提取t = 0（好像没用上）
			for(rg int i = (l != 1 ? l * 2 : 1) ; i <= (r != n ? r * 2 - 1 : n * 2) ; ++i)	//从左端点右侧到右端点左侧
				add[i] = true;
		}
		else p0[++t0] = (qujian){l ,r};	//提取 t = 1
	}
	for(rg int i = 1 ; i <= t0 ; ++i){
		int l = p0[i].l ,r = p0[i].r ,ok = false;
		for(rg int i = l ; i < r ; ++i){
			ok |= (!add[i * 2] && !add[i * 2 + 1]);
		}
		if(!ok)	return puts("NO") ,0;
	}
	int st = 2000;	//2000肯定降不到0了
	printf("YES\n%d ",st);
	for(rg int i = 1 ; i < n ; ++i){
		if(!add[i * 2] && !add[i * 2 + 1])	--st;	//能降就降
		printf("%d ",st);
	}
	return 0;
}
```

---

## 作者：songhn (赞：0)

~~很明显这是一道构造题~~
### 题解
这里讲一下我的构造思路，下文把单调不增作为条件1，另一个是条件2

画几个图我们就会发现，除非条件2被完全包含在一个条件1里，否则就可以构造，注意这里指的条件1可以是多个条件1合起来的大区间，这个还是比较显然的，一个连续的区间无法同时满足两个条件

但假如跨越多个条件1区间，或者中间有未被条件1包含的区间，就一定有解，可以构造出波浪形，每个条件1区间按照$1,2,3,\cdots$这样构造，因为区间长度至少是2，那么跨越多个条件1区间的条件2是肯定满足的（因为中间有断崖）

之后对于未被包含的区间，我们可以按照$N,N-1,N-2,\cdots$这样构造，$N$是一个极大的数，我选择了1e8，这样无论是不是包含条件1的区间条件2都是显然成立的

所以现在只要统计出所有连续条件1即可，一开始本来想把条件1的位置标记成1，后来发现假了，所以可以用并查集处理，把相邻点合并，这样对于相同祖先的点，我们就累加构造，遇到新的就从1重新开始

然后最后把所有的条件1区间末尾重置为$N$，这是因为我们$N,N-1,N-2,\cdots$构造要形成条件2区间至少要2个位置，但但假如条件1在$[i,j]$而条件2在$[i,j+1]$的话 这么在末尾补$N$就不满足了，所以对于所有末梢变成$N$，之后对于空白节点直接顺延递减就好了，注意开头要特判一下，如果开头就没有被区间覆盖过直接置成$N$即可
### 代码
```cpp
const int inf=0x3f3f3f3f;
const int maxn=1050;
const int N=1e8;
int n,m;
int t[maxn],l[maxn],r[maxn];
int a[maxn],fa[maxn];
int get(int x){if(fa[x]!=x)fa[x]=get(fa[x]);return fa[x];}
void merge(int x,int y)
{
  x=get(x),y=get(y);
  if(x==y) return;
  fa[x]=y;
}
int main()
{
  cin>>n>>m;
  rep(i,1,m) rd(t[i]),rd(l[i]),rd(r[i]);
  rep(i,0,n) fa[i]=i;
  rep(i,1,m)
  {
    if(t[i]==0) continue;
    rep(j,l[i],r[i]-1) merge(j+1,j),a[j]=1;
    a[r[i]]=1;
  }
  rep(i,1,m)
  {
    if(t[i]==1) continue;
    int flag=0;
    rep(j,l[i],r[i]-1)
    {
      if(get(j+1)!=get(j)) {flag=1;break;}
    }
    if(!flag)
    {
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  rep(i,1,n)
  {
    if(!a[i]) continue;
    if(get(i)==get(i-1)) a[i]=a[i-1]+1;
    else a[i]=1;
  }
  rep(i,1,n)
  {
    if(a[i]&&a[i+1]==0) a[i]=N;
  }
  rep(i,1,n)
  {
    if(a[i]==0)
    {
      if(i==1) a[i]=N;
      else a[i]=a[i-1]-1;
    }
  }
  rep(i,1,n) printf("%d ",a[i]);
  cout<<endl;
  return 0;
}
```

---

## 作者：xlqs23 (赞：0)

这个题的解答分两部分。

第一种是如何判断$NO$：当1式区间和0式区间存在矛盾时自然会无解。什么时候存在矛盾呢？题设所说，1代表非递减，0代表非非递减，（无论什么顺序，总之不是非递减，乱序什么的也罢）。由于解题方便，这里不考虑乱序（可行但是较繁琐）。当一个应该是0式区间的范围内全体出现了1式区间的元素（也就是说这个0式区间内不存在0式元素，或者说这个区间被1式覆盖了），那么这个0式区间自然不可能是“非非递减”，因为它里边全是非递减序列。我们知道，非递减的临界是公差为0的序列，而非非递减的临界是一个子数列内至少存在一个元素使得本数列不是非递减顺序。那么，当0式区间内只要存在一个0式元素，这个区间段就可以被构造出来。

第二种是如何判断$YES$：如上文所述，如果不是$NO$就是$YES$。而如何把答案序列输出出来呢？可以设一个初始值，把非递减区间简单看做“无变化”，把递减区间简单看做逐步减一，得出来的就是答案。

怎么去标记所谓的0式区间和1式区间呢？一个最简单也是最暴力的办法就是构造一个标志数组，对每个元素进行标记。惊喜的是，本题数据范围出乎意料的小，这种方式确实可行。

**所以有如下思路：**

1.利用标记数组，首先标记1式区间

2.再对0式区间进行分析

3.得出结论，并输出答案

**AC代码**
```cpp

#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include <map>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <cstring>
#include <cmath>
#define DETERMINATION main
#define lldin(a) scanf("%lld", &a)
#define println(a) printf("%lld\n", a)
#define reset(a, b) memset(a, b, sizeof(a))
const int INF = 0x3f3f3f3f;
using namespace std;
const double PI = acos(-1);
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const int mod = 1000000007;
const int tool_const = 19991126;
const int tool_const2 = 33;
inline ll lldcin()
{
	ll tmp = 0, si = 1;
	char c;
	c = getchar();
	while (c > '9' || c < '0')
	{
		if (c == '-')
			si = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		tmp = tmp * 10 + c - '0';
		c = getchar();
	}
	return si * tmp;
}
const int DEED = 50000;
ll imformation[DEED][3],mark[DEED];
int DETERMINATION()
{
	ll n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> imformation[i][0] >> imformation[i][1] >> imformation[i][2];//用这种方式来储存信息
	for (int i = 1; i <= m; i++)
	{
		if (imformation[i][0] == 1)//对一式区间进行标记
			for (int j = imformation[i][1]; j < imformation[i][2]; j++)
				mark[j] = 1;
	}
	for (int i = 1; i <= m; i++)
	{
		bool sign = false;
		if (imformation[i][0] == 0)
		{
			for (int j = imformation[i][1]; j < imformation[i][2]; j++)
			{
				if (mark[j] == 0)
				{
					sign = true;
					break;//存在一个0式元素，全体成立
				}
			}
			if (sign == false)
			{
				cout << "NO" << endl;
				return 0;//否则GG
			}
		}
	}
	cout << "YES" << endl;
	ll lim = n+1;
	for (int i = 1; i <= n; i++)
		if (mark[i-1] == 0)//由于这是从前往后构造，所谓的递增递减都是根据前一个元素“相对”出来的概念，所以要根据前一个元素的标志判断
		{
			lim -=1;
			cout << lim << " ";
		}
		else
			cout << lim << " ";
	cout << endl;
	return 0;



---

## 作者：_蒟蒻__ (赞：0)

这题还是卡了我很久的(其实是我菜)。

其实仔细想一想，保存输入，按照区间左端点从小到大排序。先处理t=1（不下降）的情况，比较好想的方法就是暴力把整个区间枚举赋值。

处理完t=1时，对于其他没有赋值的区间，或者是两个不下降区间之间，我们假设它们全部都是下降的。之后用t=2给出的区间检验序列是否满足条件，就可以AC啦。

萌新过弱，望各位大佬指点指点。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#define mk make_pair
#define pli pair<int,int>
const int N=5000;
using namespace std;
int scnt=2001;
int a[2010];
int n,m;
vector<pli>v1,v2;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int t,x,y;
		cin>>t>>x>>y;
		if(t)v1.push_back(mk(x,y));//存一下 
		else v2.push_back(mk(x,y));
	}
	
	sort(v1.begin(),v1.end()); 
	sort(v2.begin(),v2.end());
	
	for(unsigned k=0;k<v1.size();k++)
	{
		int x=v1[k].first,y=v1[k].second; 
		
		if(!a[x])scnt=n-x;//赋值为n-x保证相对于x-1一定是下降的 
		
		for(int i=x;i<=y;i++)//不下降就可以看做相等 
			a[i]=scnt;
	} 

	for(int i=1;i<=n;i++)
	if(!a[i])
		a[i]=n-i;//保证a[i]一定小于a[i-1] 
	
	for(unsigned k=0;k<v2.size();k++)//检验一下是否满足条件 
	{
		bool fl=0;
		
		int x=v2[k].first,y=v2[k].second;
		
		int t=a[x];	
			
		for(int i=x;i<=y;i++)
		if(a[i]<t)
		{
			fl=1;break;
		}
		
		if(!fl)
		{
			cout<<"NO";return 0;
		}
	}
	
	cout<<"YES\n";
	
	for(int i=1;i<=n;i++)
		cout<<a[i]+N<<' ';//+N保证不出现负数 
		
	return  (0 - 0) ;
}
```


---

## 作者：Frozencode (赞：0)

看到这个问题，我们先分析下什么时候不可行。

为了方便我们称$t=0$的区间为$0$区间，称$t=1$的区间为$1$区间

经过~~漫长的~~讨论，我们发现只有当一个$0$区间是一个$1$区间的子区间时答案是不存在，其他情况都可以通过构造得到。

那么问题就转化为判断每一个$0$区间是否是某个$1$区间的子区间。

不难想到把$0$区间要求离线下来，同时对于每个点用并查集维护它所在$1$区间的左端点和右端点（即把连续的$1$区间拼接起来）。只要一个$0$区间里的每一个点都满足它所在的$1$区间的左端点不大于$0$区间的左端点**且**它所在的$1$区间的右端点不小于$0$区间的右端点，那么这个$0$区间就是$1$区间的子区间。

构造的话我们只要搞一个差分数组就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
struct node
{
	ll x,y;
};
node f[maxn],c[maxn];
ll n,m,t,l,r,a[maxn],s[maxn],sum,cur,pd,cnt,fal[maxn],far[maxn];
vector<ll>e;
bool vis[maxn];
ll findl(ll x)
{
	if(fal[x]==x)return x;
	return fal[x]=findl(fal[x]);
}
ll findr(ll x)
{
	if(far[x]==x)return x;
	return far[x]=findr(far[x]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		fal[i]=i;
		far[i]=i;
	}
	while(m--)
	{
		cin>>t>>l>>r;
		if(t==1)//对于1区间我们更新信息
		{
			for(int i=l;i<=r;i++)
			{
				if(i!=r)a[i]+=1000;//差分
				vis[i]=1;
				if(findl(i)>l)fal[findl(i)]=l;
				if(findr(i)<r)far[findr(i)]=r;
			}
		}
		else//0区间就离线下来
		{
			c[++cnt].x=l;
			c[cnt].y=r;
		}
	}
	for(int i=1;i<=n;i++)//f数组是该点最终所处1区间的左右端点
	{
		f[i].x=(vis[i] ? findl(i) : INF);
		f[i].y=(vis[i] ? findr(i) : -1);
	}
	for(int i=1;i<=cnt;i++)
	{
		pd=0;
		for(int j=c[i].x;j<=c[i].y;j++)
		{
			if(f[j].x!=INF&&f[j].y!=-1)
			{
				if(c[i].y<=f[j].y&&c[i].x>=f[j].x)pd=1;
			}
			if(j!=c[i].y)a[j]--;//差分
		}
		if(pd)//是子区间
		{
			cout<<"NO";
			return 0;
		}	
	}
	s[1]=1;
	sum=1;
	for(int i=2;i<=n;i++)
	{
		sum+=a[i-1];
		s[i]=sum;
		cur=max(1-s[i],cur);//这里防止出现小于1的数
	}
	cout<<"YES"<<"\n";
	for(int i=1;i<=n;i++)cout<<s[i]+cur<<" ";
	return 0;
}
```


---

