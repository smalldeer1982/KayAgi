# Olympiad in Programming and Sports

## 题目描述

There are $ n $ students at Berland State University. Every student has two skills, each measured as a number: $ a_{i} $ — the programming skill and $ b_{i} $ — the sports skill.

It is announced that an Olympiad in programming and sports will be held soon. That's why Berland State University should choose two teams: one to take part in the programming track and one to take part in the sports track.

There should be exactly $ p $ students in the programming team and exactly $ s $ students in the sports team. A student can't be a member of both teams.

The university management considers that the strength of the university on the Olympiad is equal to the sum of two values: the programming team strength and the sports team strength. The strength of a team is the sum of skills of its members in the corresponding area, so the strength of the programming team is the sum of all $ a_{i} $ and the strength of the sports team is the sum of all $ b_{i} $ over corresponding team members.

Help Berland State University to compose two teams to maximize the total strength of the university on the Olympiad.

## 样例 #1

### 输入

```
5 2 2
1 3 4 5 2
5 3 2 1 4
```

### 输出

```
18
3 4 
1 5 
```

## 样例 #2

### 输入

```
4 2 2
10 8 8 3
10 7 9 4
```

### 输出

```
31
1 2 
3 4 
```

## 样例 #3

### 输入

```
5 3 1
5 2 5 1 7
6 3 1 6 3
```

### 输出

```
23
1 3 5 
4 
```

# 题解

## 作者：lndjy (赞：14)

首先，如果运动团队的人已经确定了，编程团队只要取剩下的大的就好了。

那么我们可以先把最大的 $p$ 个丢到编程团队，然后通过反悔贪心，每次让一个人进入运动团队，一共 $s$ 次。

有两种情况：

1. 将一个没选过的人直接进入运动团队，价值 $b_i$。
2. 将一个选过的人进入运动团队，再找一个人进入编程团队，价值 $b_i-a_i+a_j$。

用 $3$ 个堆维护 $a_i,b_i,b_i-a_i$ 每次取最大值。

```
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int N=3e3+5;
struct node
{
	int id,num;
	node(int x=0,int y=0)
	{
		id=x;num=y;
	}
	bool operator <(const node &p)
	const{
		return num>p.num;
	}
	bool operator >(const node &p)
	const{
		return num<p.num;
	}	
}a[N],b[N];
bool cmp(node x,node y)
{
	return x.id<y.id;
}
priority_queue<node,vector<node>,greater<node> > q1,q2,q3;
int op[N],ans,n,p,s;
int main()
{
	cin>>n>>p>>s;
	for(int i=1;i<=n;i++)
	cin>>a[i].num,a[i].id=i;
	for(int i=1;i<=n;i++)
	cin>>b[i].num,b[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=p;i++)
	op[a[i].id]=1,ans+=a[i].num;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		q1.push(node(i,a[i].num));
		q2.push(node(i,b[i].num));
		q3.push(node(i,b[i].num-a[i].num));
	}
	for(int zwz=1;zwz<=s;zwz++)
	{
		int now=-1e9,i,j,opt;
		while(!q2.empty()&&op[q2.top().id]!=0) q2.pop();
		if(!q2.empty())
		{
			if(q2.top().num>now)
			{
				now=q2.top().num;
				i=q2.top().id;
				opt=1;
			}
		}
		while(!q3.empty()&&op[q3.top().id]!=1) q3.pop();
		while(!q1.empty()&&op[q1.top().id]!=0) q1.pop();
		if(!q1.empty()&&!q3.empty())
		{
			int sum=q1.top().num+q3.top().num;
			if(sum>now)
			{
				now=sum;
				i=q3.top().id;
				j=q1.top().id;
				opt=2;
			}
		}
		ans+=now;
		if(opt==1)
		{
			q2.pop();
			op[i]=2;
		}
		else
		{
			q1.pop();q3.pop();
			op[i]=2;
			op[j]=1;
			q3.push(node(j,b[j].num-a[j].num));
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	if(op[i]==1)
	cout<<i<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)
	if(op[i]==2)
	cout<<i<<" "; 
 	return 0;
}

```


---

## 作者：xfrvq (赞：13)

[$\tt Link$](/problem/CF730I "Easy Problem")。

首先这个问题 $n\le3\times10^3$ 一看就很网络流。

我们考虑建出两个虚拟点 $p,q$ 代表是两种选择。

然后对于每个 $1\le i\le n$，我们连出三种边

+ 源点连向 $i$，流量 $1$ 费用 $0$。
+ $i\to p$，流量 $1$ 费用 $a_i$（选择编程）。
+ $i\to q$，流量 $1$ 费用 $b_i$（选择体育）。

最后 $p,q$ 连向汇点，流量分别是读入的 $p,s$（保证总共只会有 $p+s$ 个人会被选出来），费用为 $0$。

输出方案就在跑完最大费用最大流的网络上看，如果流量不是 $1$ 就代表这条边被选上了。

---

## 作者：GalwayGirl (赞：10)

~~说来惭愧，这种题 WA 了十几次才过~~
## Solution
考虑用反悔贪心，按照惯例就先把编程团队最大的 $p$ 人选上，再来考虑选上体育团队的 $s$ 人。

本题最大的难点就在于两个团队选的人是不能够重复的，所以当在选择体育团队的人与编程团队有重复时，选前者而不选后者,贡献就为 $b_i-a_i$，然后在将编程团队缺的人选上，整体贡献为 $b_i-a_i+a_j$。

要最大化贡献，就要维护三个堆: $a_i$ 堆，$b_i$ 堆和 $b_i-a_i$ 堆。
```cpp
priority_queue<node> q1,q2,q3;
int main(){
    scanf("%d%d%d",&n,&p,&s);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        q1.push({i,a[i]});
    }
    while(p--){
        vis[q1.top().id]=1;
        ans+=q1.top().val;
        q1.pop();
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        if(vis[i])q3.push({i,b[i]-a[i]});
        else q2.push({i,b[i]});
    }
```
## Detail
- 选完之后，记得打上标记，防止重复。
- 在将程团队缺的人选上时，也就是$a_j$，它还需要放入$b_i-a_i$堆中，~~博主就是这个地方 WA 了十几次。~~

最后贴上完整代码。
```cpp
#include<include>
using namespace std;
const int N=3e3+100;
int n,p,s;
int a[N],b[N],ans,vis[N];
struct node{
    int id,val;
    bool operator <(const node&x)const{
        return x.val>val;
    }
};
priority_queue<node> q1,q2,q3;
int main(){
    scanf("%d%d%d",&n,&p,&s);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        q1.push({i,a[i]});
    }
    while(p--){
        vis[q1.top().id]=1;
        ans+=q1.top().val;
        q1.pop();
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        if(vis[i])q3.push({i,b[i]-a[i]});
        else q2.push({i,b[i]});
    }
    while(s--){
        int s1,s2,s3=q3.top().val;
        while(!q2.empty()&&vis[q2.top().id])q2.pop();
        while(!q1.empty()&&vis[q1.top().id])q1.pop();
        s1=q1.top().val;
        s2=q2.top().val;
        if(s2>s1+s3){
            ans+=s2;
            vis[q2.top().id]=2;
            q2.pop();
        }
        else {
            ans+=s1+s3;
            vis[q1.top().id]=1;
            vis[q3.top().id]=2;
            q3.pop();
            q3.push({q1.top().id,b[q1.top().id]-a[q1.top().id]});
            q1.pop();
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)if(vis[i]==1)printf("%d ",i);
    printf("\n");
    for(int i=1;i<=n;i++)if(vis[i]==2)printf("%d ",i);
    printf("\n");
    return 0;
}
```
最后祝大家 CSP/NOIP RP++。

---

## 作者：legendgod (赞：9)

[CF730I Olympiad in Programming and Sports](https://www.luogu.com.cn/problem/CF730I)

看到题解里面没有 Dp 的思路，笔者来提供一篇。

笔者想题的时候发现有两个变量，如果 $s + p = n$ 的话，那么直接 $O(n^2)$ 处理即可，但是这里 $s + p \le n$ 所以不能直接处理。

我们考虑设状态 $f(i,j)$ 表示我们已经处理了 $i$ 个数，被选到编程队的人数为 $j$。那么转移的时候就看当前这一位的人是否加入队即可。

$$
f(i,j) = \max
\begin{cases}
f(i - 1, j) \\
f(i - 1, j - 1) + a_i \\
f(i - 1, j) + b_i
\end{cases}
$$

但是这里有一个问题，直接选不一定保证答案是最优的，而且不一定能保证选到另一个队伍的人数符合标准。我们可以考虑将一维排序之后选，根据我们的状态我们可以将选到运动队伍的人从大到小排序。如果我们当前转移不选这个人加入编程队伍，那么肯定将其加入运动队伍更优，这样也方便我们记录路径。

之后考虑如果 $i - j > s$ 那么肯定是不用再进行加入运动队的转移了。因为越前面的数 $b_i$ 越大，所以选前面的肯定会更优。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread

#ifdef Fread
char buf[1 << 21], *iS, *iT;
#define gc() (iS == iT ? (iT = (iS = buf) + fread (buf, 1, 1 << 21, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
	for(; '0' <= c && c <= '9';c = getchar()) x = (x * 10) + (c ^ 48);
	x *= f;
}

const int maxn = 3e3 + 5;
const int maxm = maxn << 1;

typedef int room[maxn];

int n, s, p;

struct Node {
    int a, b, id;
    inline bool operator < (const Node &z) const {
        return b > z.b;
    }
}c[maxn];
int f[maxn][maxn];
pair<int, int> pre[maxn][maxn];
int vis[maxn];

void calc(int i,int j) {
    if(i == 0) return ;
    if(pre[i][j].second == 0) vis[i] = 1;
    calc(i - 1, pre[i][j].first);
}

signed main() {
//    freopen(".in", "r", stdin);
//    freopen(".out", "w", stdout);
	int i, j;
	memset(f, -0x3f, sizeof(f));
    r1(n), r1(p), r1(s);
    for(i = 1; i <= n; ++ i) r1(c[i].a), c[i].id = i;
    for(i = 1; i <= n; ++ i) r1(c[i].b);
    sort(c + 1, c + n + 1);
    f[0][0] = 0;
    for(i = 1; i <= n; ++ i) {
        for(j = 0; j <= min(i, p); ++ j) {
            #define mp make_pair
            if(j - 1 >= 0 && f[i - 1][j - 1] + c[i].a > f[i][j])
                f[i][j] = f[i - 1][j - 1] + c[i].a, pre[i][j] = mp(j - 1, 0);
            if(f[i - 1][j] > f[i][j])
                f[i][j] = f[i - 1][j], pre[i][j] = mp(j, 1);
            if(i - j <= s && f[i - 1][j] + c[i].b > f[i][j])
                f[i][j] = f[i - 1][j] + c[i].b, pre[i][j] = mp(j, 2);
            #undef mp
        }
    }
    printf("%d\n", f[n][p]);
    calc(n, p);
    for(i = 1; i <= n; ++ i) if(vis[i]) printf("%d ", c[i].id);
    int sum(0);
    puts(""); for(i = 1; i <= n; ++ i) if(!vis[i] && sum < s) ++ sum, printf("%d ", c[i].id);
    puts("");
	return 0;
}


```



---

## 作者：Mr_Wu (赞：7)

~~复习联赛~~

考虑费用流模型：

$$ V=\{S,T,A,B,1,2,\cdots,n\} $$

$$ E=\{(S,A,lim_1,0),(S,B,lim_2,0)\}\cup \{(A,i,1,a_i)\}\cup \{(B,i,1,b_i)\}\cup \{(i,T,1,0)\}$$

观察每次增广，可以发现是四种情况之一：

- 增一个到 $A$ 里。
- 增一个到 $B$ 里。
- 将一个 $A$ 中的扔到 $B$ 里，并增一个到 $A$ 里。
- 将一个 $B$ 中的扔到 $A$ 里，并增一个到 $B$ 里。

使用 4 个堆维护这个过程即可，时间复杂度为 $O(n\log n)$。由于本题数据范围小，代码全程使用 int：

```cpp
#include<cstdio>
#include<queue>
using namespace std;

const int MAXN=1e5+5,INF=2147483647;
int N,P,S,a[MAXN],b[MAXN],st[MAXN],ans;
struct data{
	int id,val;
	data(int id=0,int val=0):id(id),val(val){}
	bool operator<(const data& t)const{
		return val<t.val || (val==t.val&&id<t.id);
	}
};
priority_queue<data> q01,q02,q12,q21;
void upd(int x){
	if(st[x]==0)q01.push(data(x,a[x])),q02.push(data(x,b[x]));
	else if(st[x]==1)q12.push(data(x,b[x]-a[x]));
	else if(st[x]==2)q21.push(data(x,a[x]-b[x]));
}
 
int main(){
	scanf("%d%d%d",&N,&P,&S);
	for(int i=1;i<=N;++i)scanf("%d",&a[i]),q01.push(data(i,a[i]));
	for(int i=1;i<=N;++i)scanf("%d",&b[i]),q02.push(data(i,b[i]));
	while(P||S){
		int delta=-INF,op=0;
		while(!q01.empty() && st[q01.top().id]!=0)q01.pop();
		while(!q02.empty() && st[q02.top().id]!=0)q02.pop();
		while(!q12.empty() && st[q12.top().id]!=1)q12.pop();
		while(!q21.empty() && st[q21.top().id]!=2)q21.pop();
		if(P){
			if(!q01.empty() && q01.top().val>delta)delta=q01.top().val,op=1;
			if(!q02.empty() && !q21.empty() && q02.top().val+q21.top().val>delta)delta=q02.top().val+q21.top().val,op=2;
		}
		if(S){
			if(!q02.empty() && q02.top().val>delta)delta=q02.top().val,op=3;
			if(!q01.empty() && !q12.empty() && q01.top().val+q12.top().val>delta)delta=q01.top().val+q12.top().val,op=4;
		}
		ans+=delta;
		if(op==1){
			int id=q01.top().id;
			st[id]=1,upd(id),--P;
		}else if(op==2){
			int id1=q02.top().id,id2=q21.top().id;
			st[id1]=2,upd(id1),st[id2]=1,upd(id2),--P;
		}else if(op==3){
			int id=q02.top().id;
			st[id]=2,upd(id),--S;
		}else{
			int id1=q01.top().id,id2=q12.top().id;
			st[id1]=1,upd(id1),st[id2]=2,upd(id2),--S;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=N;++i)if(st[i]==1)printf("%d ",i);putchar('\n');
	for(int i=1;i<=N;++i)if(st[i]==2)printf("%d ",i);putchar('\n');
	return 0;
}
```



---

## 作者：starrylasky (赞：6)

[体验更佳](https://www.cnblogs.com/hhhsky001/articles/16588914.html)

# Solution

提供一种直接贪心的做法。

关于本题有很多种做法。事实上这题是 [AT2672](https://www.luogu.com.cn/problem/AT2672) 的弱化版和简化版。

按照 $a_i+b_j>a_j+b_i$ 排序后，显然在前一段选 $a$ ，后一段选 $b$ 。

贪心，用优先队列维护前缀选 $a$ 的最大和后缀选 $b$ 的最大。

对于选的集合，从上继承后再根据优先队列的弹出进行删除就可以了。

# Code

```cpp
/*
太弱了，被zsq大佬吊打了。zsq是一个十分牛逼的选手，手切黑题，AT和CF5000分，拥有IOI Au的水平，
可他谦虚谨慎，不慕名利，想要隐藏在众人之间，可是金子总会发光，他即将在NOIP 2022上AK。
*/
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define re register
#define fep(i,l,r) for(re int i=l;i<=r;++i)
#define For(i,u) for(re int i=head[u];i;i=e[i].nxt)
#define feb(i,r,l) for(re int i=r;i>=l;--i)
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define LL long long
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
//#define int long long
#define pr pair<int,int>
#define mpr make_pair
using namespace std;

const int N = 3e3+5;
int n,a,b,sum1[N],sum2[N],ans; bool vis1[N][N],vis2[N][N];
struct Node
{
	int x,y,id;
	inline bool operator <(const Node d1) const {return x+d1.y>y+d1.x;}
}p[N];
priority_queue<int,vector<int>,greater<int> > q;

inline int read() { int s=0,w=1; char ch=getchar(); while(!(ch<='9'&&ch>='0')) {if(ch=='-') w=-1; ch=getchar();} while(ch<='9'&&ch>='0') {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();} return s*w; }
inline void write(int x) { if(x>=10) write(x/10); putchar(x%10+'0'); }
inline void print(int x,char ch) { if(x<0) putchar('-'),x=~(x-1); write(x); putchar(ch);}

signed main()
{
	n=read(),a=read(),b=read();
	fep(i,1,n) p[i].x=read(),p[i].id=i;
	fep(i,1,n) p[i].y=read();
	sort(p+1,p+1+n);
	fep(i,1,n)
	{
		q.push(p[i].x); sum1[i]=sum1[i-1]+p[i].x;
		fep(j,1,n) vis1[i][j]=vis1[i-1][j]; vis1[i][p[i].id]=1;
		if(q.size()>a) 
		{
			sum1[i]-=q.top();
			fep(j,1,n) if(vis1[i][p[j].id]&&q.top()==p[j].x)
			{
				vis1[i][p[j].id]=0; break;
			}
			q.pop();
		}
	}
	while(!q.empty()) q.pop();
	feb(i,n,1)
	{
		q.push(p[i].y); sum2[i]=sum2[i+1]+p[i].y;
		fep(j,1,n) vis2[i][j]=vis2[i+1][j]; vis2[i][p[i].id]=1;
		if(q.size()>b)
		{
			sum2[i]-=q.top();
			fep(j,1,n) if(vis2[i][p[j].id]&&q.top()==p[j].y)
			{
				vis2[i][p[j].id]=0; break;
			}
			q.pop();
		}
	}
	fep(i,a,n-b) ans=max(ans,sum1[i]+sum2[i+1]);
	print(ans,'\n');
	fep(i,a,n-b) if(ans==sum1[i]+sum2[i+1])
	{
		fep(j,1,n) if(vis1[i][j]) print(j,' '); puts("");
		fep(j,1,n) if(vis2[i+1][j]) print(j,' '); puts("");
		break;
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：4)

各位大佬都用了费用流这些高级算法，只会最大流的我表示难以理解，这里给出一种较为简单的反悔贪心。

[题目传送门](https://www.luogu.com.cn/problem/CF730I)
## 思路
首先把 $a_i$ 前 $p$ 大的人塞给编程团队，然后考虑给体育团队加人。假设我们加入的人的编号是 $x$，$x$ 有这些可能：

   1. $x$ 不在被编程团队选的人里面，此时 $sum$ 直接加上 $b_x$。
   2. $x$ 在被编程团队选的人里面，但是被体育团队挖走了，这时我们的答案减少了 $a_x$，但是又增加了 $b_x$，但是由于编程团队被挖走了一个人，此时编程团队少一个人，那么根据贪心的思想，我们需要加入一个没有被选过的 $a_i$ 最大的那个人，此时 $sum$ 就加上 $b_x-a_x+a_y$，其中 $y$ 是没有被选过的。
   
这样，我们的思路就很清楚了，维护三个优先队列，一个表示 $a_i$，一个表示 $b_i$，一个表示 $a_i-b_i$，注意在算答案前弹出不合法的堆顶即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int opt[N],cnt;
struct node{int val,id;}a[N],b[N];
inline bool cmp(node x,node y){return x.val>y.val;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,p,s;cin>>n>>p>>s;
	for (int i=1;i<=n;++i) cin>>a[i].val,a[i].id=i;
	for (int i=1;i<=n;++i) cin>>b[i].val,b[i].id=i;
	sort(a+1,a+n+1,cmp);//先按 a[i] 排序
   int sum=0;
	priority_queue< pair<int,int>,vector< pair<int,int> >,less< pair<int,int> > >q1,q2,q3;
	for (int i=1;i<=p;++i) opt[a[i].id]=1,sum+=a[i].val;
	for (int i=1;i<=n;++i)
		q1.push(make_pair(a[i].val,a[i].id)),
		q2.push(make_pair(b[a[i].id].val-a[i].val,a[i].id)),
		q3.push(make_pair(b[i].val,b[i].id));//加入优先队列
	while (s--){
		while (!q1.empty() && opt[q1.top().second]!=0) q1.pop();//如果堆顶的 a[i] 已经被选过了，显然不能再选了
		while (!q2.empty() && opt[q2.top().second]!=1) q2.pop();//如果堆顶的 b[i]-a[i] 中的 a[i] 已经不在编程队里了，显然也不能选
		while (!q3.empty() && opt[q3.top().second]!=0) q3.pop();//如果堆顶的 b[i] 已经被选了，显然也不能选
        if (q2.top().first+q1.top().first>q3.top().first && !q2.empty() && !q3.empty() && !q1.empty()){
        	sum+=q2.top().first+q1.top().first,opt[q2.top().second]=2;
        	opt[q1.top().second]=1;
			q2.pop();
			q2.push({b[a[q1.top().second].id].val-a[q1.top().second].val,a[q1.top().second].id});
			q1.pop();
		}else if (!q3.empty()){
			sum+=q3.top().first,opt[q3.top().second]=2;
			q3.pop();
		}
	}
    cout<<sum<<'\n';
    for (int i=1;i<=n;++i) if (opt[i]==1) cout<<i<<' ';cout<<'\n';
    for (int i=1;i<=n;++i) if (opt[i]==2) cout<<i<<' ';cout<<'\n';
	return 0;
}
```


---

## 作者：Leap_Frog (赞：4)

### P.S.
提供一个可撤销贪心的思路，其实本质就是模拟费用流。  
毕竟楼上楼下全都写的费用流/模拟费用流，注意这题才 2000 啊。。。

### Discription.
给定一个序列 $\{a_i\}$，$\{b_i\}$。  
现在需要选出两个集合 $S=\{u_i\}$ 和 $T=\{v_i\}$。  
满足 $S\cap T=\varnothing$，且 $|S|=p,|T|=s$  
求 $\max\{\sum_{i\in S}a_i+\sum_{j\in T}b_j\}$

### Solution.
首先，我们强行钦定选 $p$ 个数，然后接下来对于每个 $T$ 中的元素考虑。  
它有两种情况：
1. 直接把一个没被选过的元素扔到 |T| 里。
2. 把一个 |S| 中的元素扔到 |T| 中，再把一个没选过的元素扔到 |S| 里。  

### Coding.
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
//1. make an Empty to B ( B[i]
//2. make an Empty to A than make this A to B ( A[i]+B[j]-A[j]
typedef pair<int,int> pi;typedef priority_queue<pi> qpi;
int n,p,s,a[3005],b[3005],id[3005];pi w[3005];qpi q1,q2,q3;long long res=0;
inline void ins(int i)
{
	if(id[i]==0) q1.push(make_pair(b[i],i)),q2.push(make_pair(a[i],i));
	else if(id[i]==1) q3.push(make_pair(b[i]-a[i],i));
}
int main()
{
	read(n),read(p),read(s);
	for(int i=1;i<=n;i++) read(a[i]),w[i]=make_pair(a[i],i);
	for(int i=1;i<=n;i++) read(b[i]);
	sort(w+1,w+n+1,greater<pi>());
	for(int i=1;i<=p;i++) res+=w[i].first,id[w[i].second]=1;
	for(int i=1;i<=n;i++) ins(i);
	for(int i=1;i<=s;i++)
	{
		int mx=-1e9,typ=0;
		while(!q1.empty()&&id[q1.top().second]!=0) q1.pop();
		while(!q2.empty()&&id[q2.top().second]!=0) q2.pop();
		while(!q3.empty()&&id[q3.top().second]!=1) q3.pop();
		if(!q1.empty()&&mx<q1.top().first) mx=q1.top().first,typ=1;
		if(!q2.empty()&&!q3.empty()&&mx<q2.top().first+q3.top().first) mx=q2.top().first+q3.top().first,typ=2;
		if(!typ) return puts("ZKAK"),0;else res+=mx;
		if(typ==1) id[q1.top().second]=2,ins(q1.top().second);
		if(typ==2) id[q2.top().second]=1,id[q3.top().second]=2,ins(q2.top().second),ins(q3.top().second);
	}
	printf("%lld\n",res);
	for(int i=1;i<=n;i++) if(id[i]==1) printf("%d ",i);
	putchar('\n');for(int i=1;i<=n;i++) if(id[i]==2) printf("%d ",i);
	return putchar('\n'),0;
}
```

---

## 作者：Cylete (赞：4)

~~居然没有题解害我做了好久~~

本来是贪心打了，对着CF的数据把自己搞的不会贪了

老老实实打最小费用最大流

### 建图

- 源点s到每个点建一条流量为1，费用为0的边（每个人只能只能参加一种比赛）

- 建三个汇点，汇点t1控制参加编程的，汇点t2控制参加体育的，汇点t控制参加t1和t2的总人数

- 每个人两种实力分别向t1，t2建流量为1，费用为负实力

然后就跑最小费用最大流啦

还要输出方案呢QwQ

考虑网络流的边，因为流量是1，如果选择了这个，那么它的反流量就是1

题目不要求按顺序，所以直接输出即可

```cpp
#define int long long
#define next kkksc03
#define R register

const int N = 3010;
const int M = 1e5 + 10;
const int inf = 1e9;

int T, n, m, k, ans;

int num1, num2, s, t, t1, t2;

int cut = 1, ver[M], next[M], head[N], w[M], f[M];

inline void add(int x, int y, int z, int v) {
	ver[++cut] = y; next[cut] = head[x]; head[x] = cut; w[cut] = z; f[cut] = v;
}

inline void link(int x, int y, int z, int v) {
	add(x, y, z, v); add(y, x, 0, -v);
}

int dis[N], book[N], incf[N], pre[N], last[N], dede[N];

inline bool spfa() {
	queue<int> q;
	for(R int i = s; i <= t; i++) dis[i] = inf, book[i] = 0;
	q.push(s);
	dis[s] = 0;
//	incf[s] = inf;
	pre[t] = -1;
	while(!q.empty()) {
		R int x = q.front();
		q.pop();
		book[x] = 0;
		for(R int i = head[x]; i; i = next[i]) {
			R int y = ver[i], z = w[i], v = f[i];
			if(!z) continue;
			if(dis[y] > dis[x] + v) {
				dis[y] = dis[x] + v;
//				incf[y] = min(incf[x], z);
				pre[y] = x;
				last[y] = i;
				if(!book[y]) {
					q.push(y);
					book[y] = 1; 
				}
			}
		}
	}
	return pre[t] != -1;
}

inline void update() {
	R int x = t;
	while(x != s) {
		w[last[x]] -= 1;
		w[last[x] ^ 1] += 1;
		x = pre[x];
	}
	ans -= dis[t]/* * incf[t]*/;
}

inline void solve() {
	read(n); read(num1); read(num2);
	s = 0; t1 = n + 1; t2 = n + 2; t = n + 3;
	for(R int i = 1; i <= n; i++) link(s, i, 1, 0);
	for(R int i = 1, x; i <= n; i++) read(x), link(i, t1, 1, -x);
	for(R int i = 1, x; i <= n; i++) read(x), link(i, t2, 1, -x);
	link(t1, t, num1, 0); link(t2, t, num2, 0);
	while(spfa()) update();
	writeln(ans);
	for(R int i = head[t1]; i; i = next[i]) if(w[i] == 1) writesn(ver[i]);
	puts("");
	for(R int i = head[t2]; i; i = next[i]) if(w[i] == 1) writesn(ver[i]);
	puts("");
}
```

---

## 作者：XL4453 (赞：2)

题目分析：

考虑贪心。

首先按编程水平从大到小选择 $p$ 个人加入编程队中，然后再去考虑运动人。

对于运动队 $s$ 个人选中的每一个，可以直接从未选中的人中选一个运动强的人 $x$，价值直接为 $b_x$，也可以选一个编程队中的但是运动更强的人 $y$ 放到运动队中然后再找一个编程强的人 $z$ 替补他，价值为 $b_y-a_y+a_z$。

那么就维护三个堆，一开始不在编程队中的人分别维护 $a$ 和 $b$ 的堆，编程队中的人维护 $ b-a $ 堆。

决策时比较两种抉择的价值哪个更优即可。

------------
细节：

作决策 2 时，替补进编程队的人也要加入 $b-a$ 堆。

有时候，由于决策 2 的存在，会使得有一些人进入编程队，无法无代价的进入运动队或是由于已经进入运动队而不能作为编程队的替补，所以要在决策开始前判断堆顶的可行性。

------------
代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
struct node{
	int a,b,num;
	bool operator <(const node x)const{
		return a<x.a;
	}
}hu[3005];
node mn(int a,int b){
	node x;
	x.a=a;
	x.b=b;
	return x;
}
int n,p,s,ans,res[3005];
priority_queue <node> q1,q2,q3;
int main(){
	scanf("%d%d%d",&n,&p,&s);
	for(int i=1;i<=n;i++)scanf("%d",&hu[i].a),hu[i].num=i;
	for(int i=1;i<=n;i++)scanf("%d",&hu[i].b);
	sort(hu+1,hu+n+1);
	for(int i=n;i>=n-p+1;i--){
		res[i]=1;
		ans+=hu[i].a;
		q3.push(mn(hu[i].b-hu[i].a,i));
	}
	for(int i=n-p;i>=1;i--){
		q1.push(mn(hu[i].a,i));
		q2.push(mn(hu[i].b,i));
	}
	for(int t=1;t<=s;t++){
		while(!q1.empty()&&res[q1.top().b]!=0){q1.pop();}
		while(!q2.empty()&&res[q2.top().b]!=0){q2.pop();}
		int c1=q2.top().a;
		int c2=q3.top().a+q1.top().a;
		if(c1>c2){
			ans+=c1;
			res[q2.top().b]=2;
			q2.pop();
		}
		else{
			ans+=c2;
			res[q3.top().b]=2;
			res[q1.top().b]=1;
			q3.pop();
			q3.push(mn(hu[q1.top().b].b-hu[q1.top().b].a,q1.top().b));
			q1.pop();
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		if(res[i]==1)
		printf("%d ",hu[i].num);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		if(res[i]==2)
		printf("%d ",hu[i].num);
	}
	printf("\n");
	return 0;
}
```
注：阅读代码时请注意原数组和决策方案共用了一个定义，在原数组中 $a$，$b$，$num$ 表示本意，而在决策中 $a$ 表示价值，$b$ 表示在排好序中的数组的位置。~~就是懒得写两个结构体。~~

---

## 作者：Code_星云 (赞：1)

一道套路得不能在套路的反悔贪心。这道题和 [P3045](https://www.luogu.com.cn/problem/P3045) 很像。一般这种分两块的反悔贪心都是这样做。

先把学生按 $p$ 从大到小排序，先贪心地把他们都选上。然后把剩下的未选的值加入优先队列（$a$ 开一个，$b$ 开一个）。需要注意的是，我们贪心选的学生也需要将他们的差值加入另一个优先队列，作为反悔操作。

然后进行 $s$ 次取最大值即可。注意不能选选过的。然后维护方案用 $set$ 维护一下就可以了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
#include<set>
#include<utility>
using namespace std;
#define int long long
typedef pair<int, int> pii;
#define mp make_pair
#define px first
#define py second
 
const int N = 3005;
const int inf = 1e18;
struct person{
	int a, b, id;
}p[N];
priority_queue<pii, vector<pii>, less<pii> > qd, qa, qb;
set<int> sa, sb;
int n, pp, s, ans = 0;
bool use[N] = {false};
 
bool cmp(person rhs1, person rhs2){
	return rhs1.a > rhs2.a;
}
signed main(){
	scanf("%lld %lld %lld", &n, &pp, &s);
	for(int i = 1; i <= n; i ++) scanf("%lld", &p[i].a);
	for(int i = 1; i <= n; i ++){
		scanf("%lld", &p[i].b);
		p[i].id = i;
	}
	sort(p + 1, p + n + 1, cmp);
	for(int i = 1; i <= pp; i ++){
		ans += p[i].a;
		qd.push(mp(p[i].b - p[i].a, i));
		sa.insert(p[i].id);
	}
	for(int i = pp + 1; i <= n; i ++){
		qa.push(mp(p[i].a, i));
		qb.push(mp(p[i].b, i));
	}
	for(int i = 1; i <= s; i ++){
		while(qa.size() && use[qa.top().py]) qa.pop();
		while(qb.size() && use[qb.top().py]) qb.pop();
		int tmp1 = qa.top().px + qd.top().px;
		int tmp2 = qb.top().px;
		int pa = qa.top().py, pb = qb.top().py, pd = qd.top().py;
		if(tmp2 > tmp1){
			ans += tmp2; sb.insert(p[pb].id);
			use[pb] = true; qb.pop();
		}else{
			ans += tmp1; sb.insert(p[pd].id);
			sa.erase(p[pd].id); sa.insert(p[pa].id);
			use[pa] = true; 
			qa.pop(); qd.pop();
			qd.push(mp(p[pa].b - p[pa].a, pa));
		}
	}
	printf("%lld\n", ans);
	set<int>:: iterator i;
	i = sa.begin();
	while(i != sa.end()){
		printf("%lld ", (* i));
		i ++;
	}
	puts("");
	i = sb.begin();
	while(i != sb.end()){
		printf("%lld ", (* i));
		i ++;
	}
	puts(""); 
	return 0;
}
```


---

## 作者：_ZSR_ (赞：1)

### [CF730I	Olympiad in Programming and Sports](https://www.luogu.com.cn/problem/CF730I)

如果只要选择一个团队的人是非常简单的，因此我们先选择 $p$ 个编程能力最强的加入编程团队，然后再选 $s$ 个人加入体育团队。

假如已经选好了 $i$ 个人加入体育团队，考虑怎么选择第 $i+1$ 个人。

$1.$ 直接选择一个没有被选过的人加入，答案加上 $b_i$。

$2.$ 选择一个加入编程团队的人，把他变成加入体育团队，然后再选择一个人加入编程团队，答案加上 $b_i-a_i+a_j$。

用三个大根堆分别维护 $a_i,b_i,b_i-a_i$，每次从两种情况中选择最大的。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=3010;
typedef pair<int,int> pii;
int n,p,s,ans;
int a[N],b[N],g[N];
priority_queue<pii> q1,q2,q3;
int main()
{
	scanf("%d%d%d",&n,&p,&s);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]),q1.push({a[i],i});
	for (int i=1;i<=n;++i) scanf("%d",&b[i]),q2.push({b[i],i});
	for (int i=1;i<=p;++i) 
	{
		ans+=q1.top().first;
		int j=q1.top().second;
		q3.push({b[j]-a[j],j});
		g[j]=1;
		q1.pop();
	}
	for (int i=1;i<=s;++i)
	{
		int op,maxn=0,p,q;
		while (q2.size()&&g[q2.top().second]!=0) q2.pop();
		if (q2.size()&&q2.top().first>maxn) 
		{
			op=2;
			maxn=q2.top().first;
			p=q2.top().second;
		}
		while (q1.size()&&g[q1.top().second]!=0) q1.pop(); 
		while (q3.size()&&g[q3.top().second]!=1) q3.pop();
		if (q1.size()&&q3.size()&&q1.top().first+q3.top().first>maxn) 
		{
			op=3;
			maxn=q1.top().first+q3.top().first;
			p=q1.top().second;
			q=q3.top().second;
		}
		ans+=maxn;
		if (op==2) g[p]=2;
		else if (op==3) 
		{
			g[p]=1,g[q]=2;
			q3.push({b[p]-a[p],p});
		}
	}
	printf("%d\n",ans);
	for (int i=1;i<=n;++i) if (g[i]==1) printf("%d ",i);
	puts("");
	for (int i=1;i<=n;++i) if (g[i]==2) printf("%d ",i);
	puts("");
	return 0;
}
```


---

## 作者：UperFicial (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF730I)

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16152053.html)。

### $\texttt{Description}$

有 $n$ 个二元组 $(a_i,b_i)$，你需要将这 $n$ 个数分配到两个组，第一个组获得的价值是 $\sum a_i$，第二个组是 $\sum b_i$，每个组有一个容量，请你求出价值总和的最大值。

$1\le n\le 3\times 10^3$。

### $\texttt{Solution}$

我焯怎么全都是反悔贪心啊，这不赤裸裸的费用流吗。

考虑一个二分图，左边是所有的二元组，右边两个点分别代表两个集合。

然后思路就十分的清晰了。

每个数只能进入一个集合中，所以令 $s\to i$ 连一条容量为 $1$，费用为 $0$ 的边。

然后每一个二元组分别向两个集合连容量为 $1$，费用为 $a_i$ 或 $b_i$ 的边。表示分配到某个集合可以获取相应的价值。

最后每个集合向 $t$ 连一条容量为该集合容量，费用为 $0$ 的边。

基本上算是费用流的板子题了。

输出方案只需要找流量为 $0$ 的边即可。

代码：

```cpp
int main()
{
	n=read(),w1=read(),w2=read();
	s=0,t=n+3;
	for(register int i=1;i<=n;i++) a[i]=read();
	for(register int i=1;i<=n;i++) b[i]=read();
	for(register int i=1;i<=n;i++) add_edge(s,i,1,0);
	for(register int i=1;i<=n;i++) add_edge(i,n+1,1,a[i]),add_edge(i,n+2,1,b[i]);
	add_edge(n+1,t,w1,0),add_edge(n+2,t,w2,0);
	MCMF();
	return 0;
}
```

$$\texttt{The End.by UF}$$

---

## 作者：happybob (赞：0)

容易发现可以直接转化成费用流模型。将学生分在一边，两个团队分在一边，就是一个二分图上的东西。由于 $n \leq 3000$，右边只有 $2$ 个点，所以直接费用流应该是可过的。但是我们考虑更优的做法。

既然可以转化成费用流，不妨考虑模拟费用流。我们考虑增广路的实际意义有可能是以下 $4$ 种：

- 一个目前没有加入团队的人加入了编程团队。
- 一个目前没有加入团队的人加入了体育团队。

- 一个目前在编程团队的人去了体育团队，另一个没加入团队的人去了编程团队。

- 一个目前在体育团队的人去了编程团队，另一个没加入团队的人去了体育团队。

容易发现我们可以用堆维护之，本质上是个反悔贪心，复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int N = 1e4 + 5;

int n, p, s, a[N], b[N];
int id[N];
struct Node
{
	int id, val;
	Node(int _u, int _v) : id(_u), val(_v) {}
	Node() {}
	bool operator<(const Node& g) const
	{
		return (val ^ g.val) ? (val < g.val) : (id < g.id);
	}
};

priority_queue<Node> pq1, pq2, pq3, pq4;

/*
pq1：能在A集合中的
pq2：能在B集合中的
pq3：能在A集合中的bi-ai
pq4：能在B集合中的ai-bi
*/

int main()
{
	scanf("%d%d%d", &n, &p, &s);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		pq1.push(Node(i, a[i]));
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		pq2.push(Node(i, b[i]));
	}
	int ans = 0;
	while (p > 0 || s > 0)
	{
		int maxp = -1, opt = 0;
		while (pq1.size() && id[pq1.top().id]) pq1.pop();
		while (pq2.size() && id[pq2.top().id]) pq2.pop();
		while (pq3.size() && id[pq3.top().id] != 1) pq3.pop();
		while (pq4.size() && id[pq4.top().id] != 2) pq4.pop();
		if (p && pq1.size() && pq1.top().val > maxp)
		{
			maxp = pq1.top().val;
			opt = 1;
		}
		if (s && pq2.size() && pq2.top().val > maxp)
		{
			maxp = pq2.top().val;
			opt = 2;
		}
		if (s && pq3.size() && pq1.size() && pq3.top().val + pq1.top().val > maxp)
		{
			maxp = pq3.top().val + pq1.top().val;
			opt = 3;
		}
		if (p && pq4.size() && pq2.size() && pq4.top().val + pq2.top().val > maxp)
		{
			maxp = pq4.top().val + pq2.top().val;
			opt = 4;
		}
		//printf("!: %d %d\n", maxp, opt);
		ans += maxp;
		if (opt == 1)
		{
			id[pq1.top().id] = 1;
			pq3.push(Node(pq1.top().id, b[pq1.top().id] - a[pq1.top().id]));
			p--;
		}
		else if (opt == 2)
		{
			int i = pq2.top().id;
			id[i] = 2;
			pq4.push(Node(i, a[i] - b[i]));
			s--;
		}
		else if (opt == 3)
		{
			s--;
			int i = pq3.top().id;
			id[i] = 2;
			pq4.push(Node(i, a[i] - b[i]));
			i = pq1.top().id;
			id[i] = 1;
			pq3.push(Node(i, b[i] - a[i]));
		}
		else
		{
			p--;
			int i = pq4.top().id;
			id[i] = 1;
			pq3.push(Node(i, b[i] - a[i]));
			i = pq2.top().id;
			id[i] = 2;
			pq4.push(Node(i, a[i] - b[i]));
		}
		//printf("!: %d %d\n", p, s);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) if (id[i] == 1) printf("%d ", i);
	printf("\n");
	for (int i = 1; i <= n; i++) if (id[i] == 2) printf("%d ", i);
	printf("\n");
	return 0;
}
```


---

## 作者：plank_black (赞：0)

&emsp;&emsp;看到各路大佬都用了费用流等高级的算法，奈何蒟蒻技术力不够，在此仅讲解一种反悔贪心的思路。

&emsp;&emsp;首先考虑一个普通的贪心思路，先在这群人中选出编程能力最强的前 $q$ 个人，再选出除了这 $q$ 个人外运动能力最强的 $s$ 个人，答案就是这些个各自项目的实力之和。

&emsp;&emsp;明显上面的做法有局限性，反例很好构造，所以我们来考虑怎么反悔。

&emsp;&emsp;前半段同样的选出编程能力最强的前 $q$ 个人，但是当我们考虑选择运动能力强的人的时候就不能一刀切掉已经选过的人，考虑以下两种情况：

- 选择没有被选过的人（编号为 $i$），贡献为 $B_i$。

- 选择在编程团队里的人（编号为 $i$），再在没选过的人里选取编程能力最强的人补位（编号为 $j$），贡献为 $B_i - A_i + A_j$。

&emsp;&emsp;观察上边两个算式我们发现，我们只需要维护三个大根堆，即 $A_i$ 的最大值、$B_i$ 的最大值、$B_i - A_i$ 的最大值。



```cpp
#include<algorithm>
#include<iostream>
#include<climits>
#include<queue>
using namespace std;

const int N = 3e3 + 10;
int n, p, s;
int arr[N];

struct node {
	int id, val;
	bool operator< (const node a) const {
		return val < a.val;
	}
}A[N], B[N];

priority_queue<node> q1, q2, q3;

bool cmp1(node a, node b);
bool cmp2(node a, node b);

int main( ) {
	cin >> n >> p >> s;
	for(int i = 1; i <= n; i++) {
		A[i].id = i;
		cin >> A[i].val;
	}
	for(int i = 1; i <= n; i++) {
		B[i].id = i;
		cin >> B[i].val;
	}
	
	sort(A + 1, A + n + 1, cmp1);
	
	int sum = 0;
	for(int i = 1; i <= p; i++) {
		arr[A[i].id] = 1;
		sum += A[i].val;
	}
	sort(A + 1, A + n + 1, cmp2);
	
	for(int i = 1; i <= n; i++) {
		q1.push({i, A[i].val});
		q2.push({i, B[i].val});
		q3.push({i, B[i].val - A[i].val});
	}
	
	for(int i = 1; i <= s; i++) {
		int add = INT_MIN, a, b, op;
		while(!q2.empty( ) && arr[q2.top( ).id]) q2.pop( );
		if(!q2.empty( ))
			if(q2.top( ).val > add) {
				add = q2.top( ).val;
				a = q2.top( ).id;
				op = 1;
			}
		
		while(!q1.empty( ) && arr[q1.top( ).id]) q1.pop( );
		while(!q3.empty( ) && arr[q3.top( ).id] != 1) q3.pop( );
		if(!q1.empty( ) && !q3.empty( )) {
			int tmp = q1.top( ).val + q3.top( ).val;
			if(tmp > add) {
				add = tmp;
				a = q3.top( ).id;
				b = q1.top( ).id;
				op = 2;
			}
		}
		sum += now;
		
		if(op == 1) {
			q2.pop( );
			arr[a] = 2;
		} else {
			q1.pop( );
			q3.pop( );
			arr[a] = 2;
			arr[b] = 1;
			q3.push({b, B[b].val - A[b].val}); //选了一个人到编程团队里就应该多一次反悔的机会
		}
	}
	
	cout << sum << endl;
	for(int i = 1; i <= n; i++)
		if(arr[i] == 1) cout << i << ' ';
	cout << endl;
	for(int i = 1; i <= n; i++)
		if(arr[i] == 2) cout << i << ' ';
	cout << endl;
	return 0;
}

bool cmp1(node a, node b) {
	return a.val > b.val;
}

bool cmp2(node a, node b) {
	return a.id < b.id;
}
```


---

## 作者：Arghariza (赞：0)

想复杂了……

这种分到两边的问题，考虑建立费用流模型，建立两个点 $A,B$ 表示分到 $A$ 的数或者分到 $B$ 的数：

- $S\to A$，流量 $p$，费用 $0$。
- $S\to B$，流量 $s$，费用 $0$。
- $A\to i\in[1,n]$，流量 $1$，费用 $a_i$。
- $B\to i\in [1,n]$，流量 $1$，费用 $b_i$。
- $i\in[1,n]\to T$，流量 $1$，费用 $0$。

建图方式很好理解，跑费用流（最大费用）后如果 $A\to i$ 的边流量为 $0$ 就代表选到了 $A$，$B$ 同理。

然后考虑每次增广的过程，有 $2$ 种情况：

一种是 $S\to C(A\text{\ 或者\ }B)\to i\to T$，由于 $C\to i$ 和 $i\to T$ 本来流量为 $1$，可以增广说明原本就没选。对应**取一个没被选的 $i$ 加进 $C$ 集合的方案**，那肯定是选 $\max\limits_{i\notin A\cup B}\{a_i\}$。

另一种是 $S\to A\to i\to B\to j\to T$（或者 $S\to B\to i\to A\to j\to T$，不难发现绕多几圈肯定不优），不难发现 $i\to B$ 如果能流，代表原本 $i$ 在 $B$ 集合里，现在被移动到了 $A$ 集合。原本 $j$ 也没有被选过。所以对应**从 $B$ 里面取一个 $i$ 扔到 $A$，再从没选过的数里选一个扔进 $B$ 的方案**。由于对答案的贡献为 $a_i-b_i+b_j$，所以肯定是取 $\max\limits_{i\in B}\{a_i-b_i\}+\max\limits_{j\notin A\cup B}\{b_j\}$，$A$ 扔到 $B$ 的情况类似。

所以只需要维护 $4$ 种情况，开 $4$ 个堆，分别维护**还没被选的数中最大 $a_i$、还没被选数中最大 $b_i$、$B$ 集合中最大 $a_i-b_i$ 以及 $A$ 集合中最大 $b_i-a_i$** 即可。

复杂度 $O(n\log n)$。代码很好写。


```cpp
#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define rd read
	#define wr write
	#define pc putchar
	#define pi pair<int, int>
	#define mp make_pair
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int N = 3e3 + 300;
int n, ans, p1, p2, a[N], b[N], in[N];
priority_queue<pi> q0, q1, q2, q3;

int main() {
	n = rd(), p1 = rd(), p2 = rd();
	for (int i = 1; i <= n; i++) a[i] = rd(), q0.push(mp(a[i], i));
	for (int i = 1; i <= n; i++) b[i] = rd(), q1.push(mp(b[i], i));
	while (p1 || p2) {
		int d = -1e9, op = -1;
		while (!q0.empty() && in[q0.top().se]) q0.pop();
		while (!q1.empty() && in[q1.top().se]) q1.pop();
		while (!q2.empty() && in[q2.top().se] != 2) q2.pop();
		while (!q3.empty() && in[q3.top().se] != 1) q3.pop();
		if (p1 && !q0.empty()) if (q0.top().fi > d) d = q0.top().fi, op = 0;
		if (p2 && !q1.empty()) if (q1.top().fi > d) d = q1.top().fi, op = 1;
		if (p1 && !q2.empty() && !q1.empty()) if (q2.top().fi + q1.top().fi > d) d = q2.top().fi + q1.top().fi, op = 2;
		if (p2 && !q3.empty() && !q0.empty()) if (q3.top().fi + q0.top().fi > d) d = q3.top().fi + q0.top().fi, op = 3;
		if (!op) {
			auto tp = q0.top(); q0.pop();
			p1--, ans += d, in[tp.se] = 1;
			q3.push(mp(b[tp.se] - a[tp.se], tp.se));
		} else if (op == 1) {
			auto tp = q1.top(); q1.pop();
			p2--, ans += d, in[tp.se] = 2;
			q2.push(mp(a[tp.se] - b[tp.se], tp.se));
		} else if (op == 2) {
			auto t1 = q2.top(), t2 = q1.top(); q2.pop(), q1.pop();
			p1--, ans += d, in[t2.se] = 2, in[t1.se] = 1;
			q2.push(mp(a[t2.se] - b[t2.se], t2.se));
			q3.push(mp(b[t1.se] - a[t1.se], t1.se));
		} else if (op == 3) {
			auto t1 = q3.top(), t2 = q0.top(); q3.pop(), q0.pop();
			p2--, ans += d, in[t2.se] = 1, in[t1.se] = 2;
			q2.push(mp(a[t1.se] - b[t1.se], t1.se));
			q3.push(mp(b[t2.se] - a[t2.se], t2.se));
		} else break;
	}
	wr(ans), puts("");
	for (int i = 1; i <= n; i++)
		if (in[i] == 1) wr(i), pc(' ');
	puts("");
	for (int i = 1; i <= n; i++)
		if (in[i] == 2) wr(i), pc(' ');
	return 0;
}

```

---

