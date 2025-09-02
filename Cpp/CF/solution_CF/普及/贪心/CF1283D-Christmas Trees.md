# Christmas Trees

## 题目描述

There are $ n $ Christmas trees on an infinite number line. The $ i $ -th tree grows at the position $ x_i $ . All $ x_i $ are guaranteed to be distinct.

Each integer point can be either occupied by the Christmas tree, by the human or not occupied at all. Non-integer points cannot be occupied by anything.

There are $ m $ people who want to celebrate Christmas. Let $ y_1, y_2, \dots, y_m $ be the positions of people (note that all values $ x_1, x_2, \dots, x_n, y_1, y_2, \dots, y_m $ should be distinct and all $ y_j $ should be integer). You want to find such an arrangement of people that the value $ \sum\limits_{j=1}^{m}\min\limits_{i=1}^{n}|x_i - y_j| $ is the minimum possible (in other words, the sum of distances to the nearest Christmas tree for all people should be minimized).

In other words, let $ d_j $ be the distance from the $ j $ -th human to the nearest Christmas tree ( $ d_j = \min\limits_{i=1}^{n} |y_j - x_i| $ ). Then you need to choose such positions $ y_1, y_2, \dots, y_m $ that $ \sum\limits_{j=1}^{m} d_j $ is the minimum possible.

## 样例 #1

### 输入

```
2 6
1 5
```

### 输出

```
8
-1 2 6 4 0 3 
```

## 样例 #2

### 输入

```
3 5
0 3 1
```

### 输出

```
7
5 -2 4 -1 2 
```

# 题解

## 作者：dd_d (赞：5)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15400451.html)
### Sol  
首先，显然要先放距离为 $1$ 的位置，再放 $2$ 的，以此类推。  
因为是最短距离，考虑 bfs。  
一开始把圣诞树全部丢到队列里，然后用这些圣诞树来扩展距离为 $1$ 的，再用距离为 $1$ 的去扩展距离为 $2$ 的。  
然后开个 map 防止一个位置被多次扩展。  
当扩展到的点的个数为 $m$ 时停止扩展。  
时间复杂度 $O(n+m)$  
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=2e5+10;
int n,m,sum;
const int dx[]={-1,1};
queue<int> q;
map<int,int> dis;
vector<int> ans;
void bfs()
{
	while (ans.size()<m)
	{
		int u=q.front(); q.pop();
		sum+=dis[u];
		if (dis[u]) ans.push_back(u);
		for (int i=0;i<2;i++)
		{
			int xx=u+dx[i];
			if (dis.count(xx)) continue;
			dis[xx]=dis[u]+1; q.push(xx);
		}
	}
}
signed main()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++)
	{
		int x=read();
		q.push(x); dis[x]=0;
	}
	bfs();
	writeln(sum);
	for (auto x:ans)
		writesp(x);
}




```

---

## 作者：Konnyaku_LXZ (赞：3)

这题明显是个贪心。当然要尽量让每个人与圣诞树的距离越小越好，所以从距离 $1$ 开始放人，放完之后放距离 $2$ ，然后再放距离 $3$ ，以此类推。

我们可以采用二分答案的做法。

二分一个最远距离 $mid$ ，判断能否有放下大于等于 $M$ 个人即可。

设最后得出的最远距离为 $d$ ，则我们先将距离为 $d-1$ 的所有点都加入答案中，然后再加距离为 $d$ 的点，人数到 $M$ 之后就立刻 break 掉即可。

具体见代码。

Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN=2e5+50;
typedef long long LL;

LL N,M,a[MAXN],ans[MAXN],Ans=0;

bool check(LL d){//判断能否放下大于等于M个人 
	LL cnt=0;
	cnt+=2*d;
	for(int i=1;i<N;++i) cnt+=min(a[i+1]-a[i]-1,2*d);
	return cnt>=M;
}

void get(LL d){
	int cnt=0;
	for(int i=1;i<d;++i) ans[++cnt]=a[1]-i,ans[++cnt]=a[N]+i,Ans+=i*2;//头尾特殊处理 
	for(int i=1;i<N;++i){
		if(2*(d-1)>a[i+1]-a[i]-1){//距离为d的先不要加上去 
			for(int j=a[i]+1;j<a[i+1];++j){
				ans[++cnt]=j;//加入答案 
				Ans+=min(j-a[i],a[i+1]-j);
			}
		}
		else{
			for(int j=a[i]+1;j<a[i]+d;++j){//同理 
				ans[++cnt]=j;
				Ans+=j-a[i];
			}
			for(int j=a[i+1]-1;j>a[i+1]-d;--j){
				ans[++cnt]=j;
				Ans+=a[i+1]-j;
			}
		}
	}
	if(cnt!=M) ans[++cnt]=a[1]-d,Ans+=d;//先处理头尾距离为d的情况 
	if(cnt!=M) ans[++cnt]=a[N]+d,Ans+=d;
	while(cnt!=M){
		for(int i=1;i<N;++i){
			if(a[i+1]-a[i]-1>2*(d-1)){ 
				ans[++cnt]=a[i]+d;
				Ans+=d;
				if(cnt==M) break;//这里记得break 
				if(a[i]+d!=a[i+1]-d){
					ans[++cnt]=a[i+1]-d;
					Ans+=d;
				}
				if(cnt==M) break;//这里记得break
			}
		}
	}
}

void Init(){
	scanf("%lld%lld",&N,&M);
	for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
}

void Solve(){
	sort(a+1,a+1+N);
	LL l,mid,r;
	for(l=1,r=M,mid=(l+r)>>1;l<r;mid=(l+r)>>1){
		if(check(mid)) r=mid;//能放下则缩小距离 
		else l=mid+1;//否则增大距离 
	}
	get(r);//计算答案 
}

void Print(){
	printf("%lld\n",Ans);
	for(int i=1;i<=M;++i) printf("%lld ",ans[i]);
	printf("\n");
}

int main()
{
	Init();
	Solve();
	Print();
	return 0;
}
```

---

## 作者：123zbk (赞：1)

明显是贪心。先从离圣诞树距离为 $1$ 的点开始放，然后放距离为 $2$ 的，....

直接把圣诞树全放到队列里，开始拓展点，当拓展的点的个数为 $m$ 时停止。

要注意防止一个位置被拓展多次。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5,dx[]={-1,1};
int n,m,x,sum;
queue <int> q;
vector <int> ans;
map <int,int> dis;
void bfs()
{
    while(ans.size()<m)
    {
        int u=q.front();
        q.pop();
        sum+=dis[u];
        if(dis[u]!=0)
        {
            ans.push_back(u);
        }
        for(int i=0;i<2;i++)
        {
            int xx=u+dx[i];
            if(dis.count(xx)!=0)
            {
                continue;
            }
            dis[xx]=dis[u]+1;
            q.push(xx);
        }
    }
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        dis[x]=0;
        q.push(x);
    }
    bfs();
    printf("%lld\n",sum);
    for(int i=0;i<ans.size();i++)
    {
        printf("%lld ",ans[i]);
    }
    return 0;
}
```

---

## 作者：decoqwq (赞：1)

大家好，我又来刷水题了(

显然我们一希望能将人摆的和圣诞树尽量靠近，一开始肯定是相邻一格的最好，当相邻一格的摆满后就只能摆相邻两格的，那么就考虑到维护所有相邻一格的位置，摆满后维护相邻两格的位置...如此这般，一直到填满位置位置

就考虑每次新加入一个位置的时候在位置集合里扩展出它分别向左向右的格子，答案最多只会增加一，如此下去，每次选择的一定都是当前能够选择最近的，就可以用 $map$ 维护位置，用 $priority\_queue$ 维护可选择的位置集合

考虑到一开始加入的都是 $1$ ，扩展出来的距离都是 $2$ ， $2$ 扩展出来距离是 $3$，这样下去，可以直接用一个队列，满足加入的一定是有序的，并且要注意，如果对应的起始点在右边就只向左扩展，在左边同理

那么就做完了QwQ

---

## 作者：_JellyFish_ (赞：0)

# 1.分析
我们很容易想到思路：对于每一棵圣诞树，如果它的两边可以放人，我们就放，否则就再往两边扩展一个位置。我们发现这个思路跟BFS异曲同工，所以我们考虑开一个队列，然后进行以下两步：

1.将每一棵圣诞树加入队列。

2.每次对于队首元素，如果这个位置不是圣诞树，就说明这个位置的确可以放人，先把它加到答案里面。然后看一看队首元素旁边的两个位置可不可以放人，如果可以就加到队列里。

那么，对于总距离，我们也可以在队列之中存放，如果把一个点称作父亲，它左右的两个点称作儿子，那么对于每个儿子到圣诞树的距离，我们只需要记录它父亲到圣诞树的距离然后加 $1$ 即可。而对于每一棵圣诞树，他们自己到圣诞树的距离就是 $0$。不需要担心可能有更优的计算方法，因为显然我们队列中的每个点到圣诞树的距离是依次递增的。

# 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,M,ans[200005],a[200005],num;
long long cnt;
//cnt记录最后总答案，num累计目前已经选好了多少个位置，ans存这些位置 
map<int,int>m;//判断某个点是否可以加入队列 
queue<pair<int,int> >q;
//bfs队列，first是这个位置距离最近圣诞树的长度，second是点的位置
signed main(){
	cin>>n>>M;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		m[a[i]]=1;//打标记
		q.push(make_pair(0,a[i]));
	}
	while(num!=M){
		pair<int,int>t=q.front();
		q.pop();
		int fi=t.first,se=t.second;
		if(fi!=0){
			cnt+=fi;
			ans[++num]=se;
		}	
		if(!m[se+1])q.push(make_pair(fi+1,se+1)),m[se+1]=1;
		if(!m[se-1])q.push(make_pair(fi+1,se-1)),m[se-1]=1;
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=M;i++)cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：zsyyyy (赞：0)

## CF1283D 1800

### 题目描述：

有 $n$ 棵圣诞树和 $m$ 个人，现在需要你给每个人安排一个位置，使得所有人到离他最近的圣诞树的距离的和最小。注意任何位置最多只能有一个人或者圣诞树。



### 输入格式：

第一行两个整数 $n$ 和 $m$，表示圣诞树的数量和人数。

第二行 $n$ 个数，表示每棵圣诞树的位置。



### 输出格式：

第一行一个数，表示最小的距离和。

第二行 $m$ 个数，表示每个人的位置。



### 思路

队列中存储 $n$ 棵圣诞树，进行若干轮操作。第 $i$ 轮安排所有到圣诞树的距离为 $i$ 的人的位置，看当前这棵圣诞树往左和往右 $i$ 个位置是否空着，空着就放一个人。如果这棵圣诞树往左和往右 $i$ 个位置都不为空，那么在下面几轮的操作中，这棵圣诞树一定不再有利用价值，也就是这棵圣诞树往左和往右 $i+k$ 的位置一定不为空，所以这棵圣诞树不用再进队列了。



### 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int n,m,a[MAXN],ans[MAXN],sum,cnt,tmp;
int maxx,minn=LONG_LONG_MAX,t,p[MAXN],ii;
bool flag;
struct node
{
	int pos,x,tt;
};
queue<node> q;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		maxx=max(maxx,a[i]);
		minn=min(minn,a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)  q.push((node){i,a[i],1});
	while(q.size())
	{
		ii=q.front().pos;
		tmp=q.front().x;
		t=q.front().tt;
		q.pop();
		flag=0;
		if((tmp==minn||tmp-t>a[ii-1]+p[ii-1])&&m)
		{
			flag=1;
			m--;
			ans[++cnt]=tmp-t;
			sum+=t;
		}
		if((tmp==maxx||tmp+t<a[ii+1]-p[ii+1])&&m)
		{
			flag=1;
			m--;
			ans[++cnt]=tmp+t;
			sum+=t;
		}
		if(flag)
		{
			q.push((node){ii,tmp,t+1});
			p[ii]=t;
		}
		else  p[ii]=t-1;
        //p[i]表示第i棵树往左和右多少个位置放了到该树距离最近的人
	}
	printf("%lld\n",sum);
	for(int i=1;i<=cnt;i++)  printf("%lld ",ans[i]);
	return 0;
}
```


---

