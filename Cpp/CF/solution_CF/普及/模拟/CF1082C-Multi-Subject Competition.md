# Multi-Subject Competition

## 题目描述

现在有 $n$ 个人分成 $m$ 组，第 $i$ 个人属于第 $s_i$ 组，能力值为 $r_i$ 。 现在你要选择任意一些组，在这些组中选择相同数目的人，最大化他们的能力值总和。

## 样例 #1

### 输入

```
6 3
2 6
3 6
2 5
3 5
1 9
3 1
```

### 输出

```
22
```

## 样例 #2

### 输入

```
5 3
2 6
3 6
2 5
3 5
1 11
```

### 输出

```
23
```

## 样例 #3

### 输入

```
5 2
1 -1
1 -5
2 -1
2 -1
1 -10
```

### 输出

```
0
```

# 题解

## 作者：redegg (赞：7)

这题，我们选一个组的人，一定考虑选择最优秀的嘛。

但是由于数据比较大，我们不从选哪些组来考虑，我们从选人来考虑。

核心代码：

```cpp
sum[a[i].id]+=a[i].v;
num[a[i].id]++;
maxn=max(maxn,num[a[i].id]);
if(sum[a[i].id]>0)ans[num[a[i].id]]+=sum[a[i].id];
```

$i$表示所有人按能力值排序后第$i$强的人

$a[i].id$表示第$i$强的人的组编号。

$sum[a[i].id];$表示第$a[i].id$组把所有人中前$i$强的人里面属于自己组的人的能力和。

$num[a[i].id]$表示这个组在前$i$强里面本组人的个数。

$ans[i]$表示我选的组，每个组选$i$人的能力最大值。

那么我考虑只选择前$i$强的人，那么这个组最多能给$ans[num[a[i].id]]$贡献自己的能力值，前提是自己的能力值要大于$0$（不然要你拖后腿用吗？）。所以我们枚举我们选择前$i$强的人，每次就按核心代码更新就行了。


总代码：

```
#include <bits/stdc++.h>
using namespace std;

int n,m;
int sum[100005];
int num[100005];
int ans[100005];
struct ha
{
    int id,v;
}a[100005];

bool cmp(const ha &aa,const ha &bb)
{
    return aa.v>bb.v;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].id,&a[i].v);
    sort(a+1,a+1+n,cmp);
    int maxn=0;
    for(int i=1;i<=n;i++)
    {
        sum[a[i].id]+=a[i].v;
        num[a[i].id]++;
        maxn=max(maxn,num[a[i].id]);
        if(sum[a[i].id]>0)ans[num[a[i].id]]+=sum[a[i].id];
    }
    int an=0;
    for(int i=1;i<=maxn;i++)
        an=max(an,ans[i]);
    printf("%d\n",an);
    return 0;
}

```

---

## 作者：_louhc (赞：7)

# CF1087 Multi-Subject Competition  

# 思路

其实这道题解法很多，除了楼上的前缀和大法，我再来一发诡异解法QAQ  

枚举人数，为了不重复查找，我们先按照每组人数对组别进行排序，以便于当人数不够时不再去找。用一个f数组记录之前每一组对上次答案的贡献，本次查找只要加上剩余人中能力值最大的就可以了。同样，为了不重复查找，我们对于每组的人按能力值排序，直接取下表为当前要求人数-1(从0开始)的人即可。当f值为负时，不可能取到，直接变为0。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define open(s) freopen( s".in", "r", stdin ), freopen( s".out", "w", stdout )
#define MAXN 100005
#define LL long long
#define vec vector<LL>

int N, M;
LL ans;
vec a[100005];
LL s, r, f[MAXN];
int b[MAXN], tot;
bool v[MAXN];

bool cmp( int x, int y ){ return a[x].size() < a[y].size(); }
bool comp( int x, int y ){ return x > y; }

int main(){
	scanf( "%d%d", &N, &M );
	for ( int i = 1; i <= N; ++i ){
		scanf( "%lld%lld", &s, &r );
		a[s].push_back( r );
		if ( !v[s] ) v[s] = 1, b[++tot] = s;
	}
	for ( int i = 1; i <= tot; ++i ) sort( a[b[i]].begin(), a[b[i]].end(), comp );
	sort( b + 1, b + tot + 1, cmp );
	int cur(1);
	for ( int i = 1; i <= N; ++i ){
		while( cur <= tot && (int)a[b[cur]].size() < i ) cur++;
		LL sum(0);
		for ( int j = cur; j <= tot; ++j ){
			f[b[j]] = max( 0ll, f[b[j]] + a[b[j]][i - 1] );
			sum += f[b[j]];
		}
		ans = max( ans, sum );
	}
	printf( "%lld\n", ans );
	return 0;
}

```



---

## 作者：王熙文 (赞：5)

这是一篇暴力算法优化的题解。

## 题意

有 $n$ 个人，$m$ 个组，第 $i$ 个人在第 $s_i$ 组，他有一个能力值 $r_i$（$r_i$ 可以是负数）。有可能有组没有任何人。选择若干组，在这些组里选择相同数目的人（每个组选出来的人数相同）是他们的能力值最大，求这个最大值是多少。如果最大值小于 $0$ 就输出 $0$。

$1 \le n,m \le 10^5,1 \le s_i \le m,|r_i| \le 10^4$

## 暴力的思路

先考虑一种暴力的算法：

使用 `vector` 存每个组的人的能力值，对于每一个组，将 `vector` 中的数从大到小排序，求出排序后的数的前缀和。从 $0$ 到最多的组的人数枚举每组选择多少人，如果当前组选这么多人的能力值和为负数，就不选这个组，否则选。

这里是暴力的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
vector<int> group[100010];
 
vector<int> qzh[100010];
 
bool cmp(int a,int b) { return a>b; }
 
int main()
{
	int n,m,s,r,maxlen=0,ans=0;
	cin>>n>>m;
	for(int i=1; i<=n; ++i)
	{
		cin>>s>>r;
		group[s].push_back(r);
	}
	for(int i=1; i<=m; ++i)
	{
		sort(group[i].begin(),group[i].end(),cmp);
		int len=group[i].size();
		if(len)
			qzh[i].push_back(group[i][0]);
		for(int j=1; j<len; ++j)
			qzh[i].push_back(qzh[i][j-1]+group[i][j]);
		maxlen=max(maxlen,len);
	}
	for(int i=0; i<maxlen; ++i)
	{
		int sum=0;
		for(int j=1; j<=m; ++j)
		{
			if(i<qzh[j].size())
				sum+=max(qzh[j][i],0);
		}
		ans=max(ans,sum);
	}
	cout<<ans;
	return 0;
}
```

## 正解

这个暴力代码时间复杂度的瓶颈在哪里？在枚举长度更新答案这里。因为极限数据 `maxlen` 可能达到 $n$，里面又套一个 $m$，肯定 TLE。那我们考虑一下，当 $i$ 比较大的时候，大多数组的元素个数已经不够 $i$ 个了，这些个可以跳过。

那么，我们可以这么优化：当 `i<qzh[j].size()` 的时候，`sum` 更新，同时把这组放到 `qzh` 的前面，覆盖这一次前面的组（因为已经统计答案过了）；否则这一组在 $i$ 更大的时候，不会被统计了，不把它放到 `qzh` 的前面，相当于已经淘汰了。

最后，把 $m$ 更新为不被淘汰的组的个数。

这种优化的方式只用了一个数组（`vector`），即可更新答案。

这是优化后的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> group[100010],qzh[100010];

inline bool cmp(int a,int b) { return a>b; }

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m,s,r,maxlen=0,ans=0;
	cin>>n>>m;
	for(int i=1; i<=n; ++i)
	{
		cin>>s>>r;
		group[s].push_back(r);
	}
	for(int i=1; i<=m; ++i)
	{
		sort(group[i].begin(),group[i].end(),cmp);
		int len=group[i].size();
		if(len)
			qzh[i].push_back(group[i][0]);
		for(int j=1; j<len; ++j)
			qzh[i].push_back(qzh[i][j-1]+group[i][j]);
		maxlen=max(maxlen,len);
	}
	for(int i=0; i<maxlen; ++i)
	{
		int sum=0,m1=0;
		for(int j=1; j<=m; ++j)
		{
			if(i<qzh[j].size())
			{
				sum+=max(qzh[j][i],0);
				qzh[++m1]=qzh[j];
			}
		}
		m=m1;
		ans=max(ans,sum);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：卷王 (赞：1)

首先，我们可以想到一个贪心：当要选一个组里面的 $i$ 个人的时候，肯定要选能力值最大的，所以可以用一个数组 $all_i$ 表示所有组前 $i$ 个人的能力值的和。注意如果一个组的前 $i$ 个人的能力值的和为负数，则不可取。求答案的时候把所有的 $all_i$ 取 $\max$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0,minn=2e9,maxx=0;
vector<int> a[100007];
int sum[100007];
int all[100007];
bool cmp(int x,int y){
	return x>y;
}
signed main() {
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[read()].push_back(read());
	for(int i=1;i<=m;i++){
		sort(a[i].begin(),a[i].end(),cmp);
		int t=a[i].size();
		if(t==0) continue;
		sum[1]=a[i][0];
		if(sum[1]>0) all[1]+=sum[1];
		else continue;
		for(int j=1;j<t;j++) {
			sum[j+1]=sum[j]+a[i][j];
			if(sum[j+1]>0) all[j+1]+=sum[j+1];
			else break;
		}
	}
	for(int i=1;i<=n;i++) ans=max(ans,all[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：hovny (赞：1)

**~~人生第一篇题解，虽然这道题做的人暂时不多，但我相信它——迟早有一天会发扬光大的！！！~~**  
**~~说完废话~~**  
步入正题  

### 题意：  

### [传送门](https://www.luogu.org/problemnew/show/CF1082C)  

### 思路：  

### 模拟、枚举  

对于每个组里的数字，先排序，然后从一到最大可能的情况，枚举要选几个数  
记录选取的和（用前缀和会更方便），然后就是选择  
那些前缀和  
为 **正数**的组 加进来  
为 **负数**的组 舍去（因为出现负数的情况说明这组还未选进来的数**都是负数**，没有利用价值了，故舍去）  
具体实现起来比较麻烦  
把每个数分到相应的组，并把每个组里的数排序  ——》 先对全部的数排序，再用链式**前向星**分组
枚举 数的个数：  ——》 用**queue**记录遍历的顺序，再用两个while循环遍历，res表示**有价值的组**的**个数**，里面的num表示这一次遍历了几个组（方便终止）  
具体见代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int s,r;
}a[100010];
int nxt[100010];
int head[100010];
int s[100010];
int sum,cur,ans,num,res;
int n,m;
int read()//快读不解释
{
	int s=0,p=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			p=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s*p;
}
bool cmp(node x,node y)
{
	return x.r<y.r;
}
int main()
{
	int i;
	n=read();m=read();
	for(i=1;i<=n;i++)
		a[i].s=read(),a[i].r=read();
	sort(a+1,a+1+n,cmp);//先进行排序
	for(i=1;i<=n;i++)//分组
	{
		nxt[i]=head[a[i].s];
		head[a[i].s]=i;
	}
	queue<int>p;
	for(i=1;i<=m;i++)//起始遍历顺序就是组号
		p.push(i);
	res=m;
	while(res)//有价值的组数
	{
		num=res;//更新下次
		sum=0;//记录这次的结果
		while(num--)
		{
			cur=p.front();p.pop();
			s[cur]+=a[head[cur]].r;//前缀和
			sum+=max(s[cur],0);
			head[cur]=nxt[head[cur]];//更新头结点
			if(head[cur]&&s[cur]>0)//如果还有利用价值就加入下一次的遍历序列
				p.push(cur);
			else//否则更新组数
				res--;
		}
		ans=max(ans,sum);//全部的答案
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：little_sun (赞：0)

# 题解 CF1082C 【Multi-Subject Competition】

[安利博客](https://www.cnblogs.com/little-sun0331/p/10046308.html)

这个$C$好难啊

这是道前缀和好题

首先，读入后，把每一个分数扔进相应学科的桶

然后贪心地对每个桶排序

然后对于每一个桶，求前缀和，如果大于$0$，就加到对应的$ans[i]$中($ans[i]$记录的是每个学科$i$个人的最大得分)

最后输出
$$\max_{1<=i<=n}{ans[i]}$$

```cpp
#include <bits/stdc++.h>

# define int long long

using std::vector;
const int MaxN = 100010;

int ans;
int sum[MaxN];
vector<int> v[MaxN];
int s[MaxN], rank[MaxN];

int cmp(int a, int b) { return a > b; }

signed main()
{
    int n, m, maxn = 0;
    scanf("%I64d%I64d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%I64d%I64d", &s[i], &rank[i]);
        v[s[i]].push_back(rank[i]);
        maxn = std::max(rank[i], maxn);
    }
    if (maxn == 0)
        return 0 * printf("0\n");
    for (int i = 1; i <= m; i++)
    {
        if (v[i].size())
            std::sort(v[i].begin(), v[i].end(), cmp);//排序
    }
    for(int i = 1; i <= m; i++)
    {
        int tmp = 0;
        for(int j = 0; j < v[i].size(); j++)
        {
            tmp += v[i][j];
            if(tmp <= 0)
                break;
            sum[j + 1] += tmp;//前缀和
        }
    }
    printf("%d", *std::max_element(sum + 1, sum + n + 1));
    return 0;
}
```


---

