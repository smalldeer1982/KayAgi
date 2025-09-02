# [USACO13JAN] Party Invitations S

## 题目描述

农夫约翰要举办一个聚会，他要邀请一些奶牛来参加。在约翰的奶牛朋友圈中，有一些奶牛是好基友，对于每一个奶牛朋友圈，没有一个完全与之相同的，假设这个奶牛朋友圈有 $k$ 头奶牛，如果约翰已经邀请了 $k-1$ 头，那么剩下的那头牛也得邀请。约翰想让你告诉他，他最少需要邀请多少头奶牛？我们假设 $1$ 号奶牛已经被邀请了。

## 说明/提示

$1 \leq  N\leq1000000$。

设所有的奶牛朋友圈的大小之和为 $M$，则 $1 \leq  M\leq250000$。

## 样例 #1

### 输入

```
10 4 
2 1 3 
2 3 4 
6 1 2 3 4 6 7 
4 4 3 2 1 
```

### 输出

```
4 
```

# 题解

## 作者：EarringYYR (赞：8)

因为直接按照存每组的奶牛会存在 _浪费_ 的情况，**会超内存**，因此这里采用线性存储的方法，将 _所有奶牛存在一个数组_ 中，然后每个组保存一个**头和尾标记**来表明这个组的奶牛在数组中的什么位置。然后就是一个~~大暴力~~，一直计算邀请了当前奶牛后还需要邀请哪些奶牛，直到没有奶牛需要邀请。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int kid[1000001],size[250001],zu[250002][3],invite[1000001],use[250001],pa[250001];//kid表示奶牛，size记录每组的大小，zu记录每组的头和尾标记，invite记录此奶牛是否邀请过，use记录此组是否邀请过，
int main()
{
    int n,g,sum=0,ans,daan=100000000;
    cin>>n>>g; 
    for(int i=1;i<=g;i++)
    {
        cin>>size[i];
        for(int j=1;j<=size[i];j++)
            cin>>kid[++sum];
        zu[i][1]=zu[i-1][2]+1;
        zu[i][2]=zu[i-1][2]+size[i];//记录头尾标记
    } 
    ans=0; 
    invite[1]=1;//初始化（奶牛1首先被邀请）
    int pan;
    do
    {
        pan=0;
        for(int k=1;k<=g;k++)
        {
            if(use[k]==0)//如果这个组还没有被邀请就检查现在是否需要邀请
            {
                int len=0;
                for(int j=zu[k][1];j<=zu[k][2];j++)
                    if(invite[kid[j]]==1)
                        len++;//寻找当前组已经有多少头牛被邀请
                if(len==size[k]-1)//如果被邀请的奶牛数为当前奶牛数-1就邀请当前组
                {
                    use[k]=1;
                    pan=1;
                    for(int j=zu[k][1];j<=zu[k][2];j++)
                        invite[kid[j]]=1;
                }
                if(len==size[k])
                    use[k]=1;//排除一个组的奶牛已经全部被邀请却没有被标记的，节省时间
            }
        }
    }while(pan==1);//只有有新的奶牛被邀请时才需要再此寻找新的组
    for(int i=1;i<=n;i++)//找哪些奶牛被邀请了
    if(invite[i]==1)
  	  ans++;
    cout<<ans;
    return 0;
} 
```

---

## 作者：xiaozeyu (赞：5)


### 既然不好写就换一个思路

------------


**这道题如果按每一小块直接算，既麻烦又费时，所以我们可以转换一下思路**


**我们可以把所有的数据接到一起，用一个算前缀和的数组进行标号，在每一次循环有效的处理每一组数据**


------------

```c
#include<bits/stdc++.h>
using namespace std;
int n,g,sum[2050],t[2050],a[250005],ans=1;
bool f[250005];//定义
int main()
{
	f[1]=1;
	scanf("%d%d",&n,&g);
	for(int i=1;i<=g;i++)
	{
		scanf("%d",&t[i]);//输入每组大小
		sum[i]=sum[i-1]+t[i];//记录总数
		for(int j=sum[i-1]+1;j<=sum[i];j++)
			scanf("%d",&a[j]);//在每一小段输入每个
	}
	while(1)//多次循环一直找
	{
		int k=ans;//继承上一次循环结果
		for(int i=1;i<=g;i++)
		{
			int q,s=0;//清零
			for(int j=sum[i-1]+1;j<=sum[i];j++)//枚举每一段
			{
				if(f[a[j]])//是否参加
					s++;
				else 
					q=a[j];//标记
			}	
			if(t[i]-s==1)//至少k-1个奶牛参加派对时，必须邀请最后的一头奶牛
			{
				f[q]=1;//参加
				ans++;//总数加上这个
			}
		}
		if(k==ans)//两次循环结果不再变化，则已最优
		{
			cout<<ans;//输出
			return 0;
		}
	}
}
```


---

## 作者：不便透露 (赞：5)

in[i]表示第i组牛数，vis[i]表示第i头牛有没有请过，G[i]表示第i头牛在那几组中，g[i]表示第i组有哪几头牛，来一遍拓扑，再加上1号，就可以了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5e4+50,maxm=1e6+50;
int n,m,num;
int in[maxn];
bool vis[maxm];
vector<int>G[maxm],g[maxm];
queue<int>q,p;
void Push(int a){
    int i,u;
    for(i=0;i<g[a].size();i++){
        u=g[a][i];
        if(!vis[u]){
            vis[u]=1;
            p.push(u);
            num++;
        }
    }
}
int main(){
    cin>>n>>m;
    int i,k,j,u;
    for(i=1;i<=m;i++){
        scanf("%d",&j);
        in[i]=j;
        for(;j;j--){
            scanf("%d",&k);
            G[k].push_back(i);
            g[i].push_back(k);
        }
    }
    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        while(!q.empty()){
            k=q.front();
            q.pop();
            for(i=0;i<G[k].size();i++){
                u=G[k][i];
                in[u]--;
                if(in[u]==1){
                    Push(u);
                }
            }
        }
        q=p;
        while(!p.empty())
            p.pop();
    }
    printf("%d",num+1);
    return 0;
}
```


---

## 作者：曹老师 (赞：5)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13jan-piset.html)

这是一篇需要好多容器的题解：$vector$ $queue$ $set$。我们用$vector$存下与$i$有关的集合是多少，用$set$存下每一个集合，用$queue$存下被邀请的奶牛。

第一次就是$1$入队，然后循环$vector$，把循环到的集合中的$1$都删去，判断删去后的集合大小是否为$1$，如果是$1$，就入队，重复操作。坑点就是，出来的可能会被重复做，加一个数组判断一下是否已经选了这头奶牛。


## Code ##

```
#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<queue>
using namespace std;

int n , m , ans , vis[1000005];
set<int>s[250005];
vector<int>about[1000005];
queue<int>q;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m; i++) {
        int t;
        scanf("%d",&t);
        for(int j=1; j<=t; j++) {
            int x;
            scanf("%d",&x);
            about[x].push_back(i);
            s[i].insert(x);
        }
    }
    q.push(1);
    vis[1] = 1;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        ans++;
        for(int i=0; i<about[now].size(); i++) {
            s[about[now][i]].erase(now);
            if(s[about[now][i]].size() == 1 && !vis[*s[about[now][i]].begin()]) {
                int t = *s[about[now][i]].begin();
                q.push(t);
                vis[t] = 1;
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3068

---

## 作者：king_xbz (赞：3)

拿到这道题，我首先考虑到一个暴力，开g个数组储存其中每个牛之间的关系。然而这肯定会TLE/MLE

后来，收到 xiaozeyu 大佬的启发用前缀和后分块解决了此题。

首先是前缀和，这一处理方式能有效地降低时空间复杂度
```cpp
for(fint i=1;i<=g;i++)
{
	num[i]=read();
	s[i]=s[i-1]+num[i];//前缀和预处理
	for(fint j=s[i-1]+1;j<=s[i];j++)
	a[j]=read();//在预处理后的分块区间内输入
}
```
- 接下来就是分块进行模拟；
注意两个特判（第一头必选；当FJ邀请组中的至少k-1个奶牛参加派对时，他必须邀请最后的一头奶牛）
```cpp
int ans=0,cnt=0;
		vis[1]=1;//根据题意，一定要选第一头牛
do
{
	cnt=ans;
	for(fint i=1;i<=g;i++)
	{
		int now=inf,must=1;//初始化now为inf便于检查是否更新
		for(fint j=s[i-1]+1;j<=s[i];j++)
		if(!vis[a[j]])//在区间内解决
		now=a[j];//更新
		else
		must++;//参加的数量累加上去
		if(!(num[i]-must)&&now!=inf)//如果符合必须邀请最后的一头奶牛的条件且此时已经选了一个位置的奶牛来更新
		vis[now]=1,ans++;
       //设为已取用，并叠加答案
	}
}
while(cnt!=ans);//循环边界，如果cnt==ans则证明没有更新，循环结束
```
- 最后输出ans，注意这里由于初始化的原因，ans需要+1
```cpp
cout<<++ans;
```
- 写在最后

其实仔细品味一下这道题其实和[菜肴制作](https://www.luogu.com.cn/problem/P3243)有一点点像，都是考虑了依赖关系。看到题解区也有拓扑AC的神犇，有兴趣的可以试一试

完整AC代码[点我](https://www.luogu.com.cn/paste/68nysarc)，最后祝大家AC愉快。

---

## 作者：Celtic (赞：2)

题目链接[[USACO13JAN]派对邀请函Party Invitations](https://www.luogu.com.cn/problem/P3068)

看见有人说开一个大数组的，其实完全没必要吧，理论上是MLE的。

而且题上只说所有组的大小之和$<=250,000$，完全可以一个测试点只有一组，里面有$250,000$头奶牛，另一个有$250,000$个组，每组里只有一头奶牛。完美卡炸内存。

正确的姿势是用$vector$。由于$vector$内存是动态的，所以不会出现MLE的情况。剩下的就是一个暴力就解决了。

```cpp
#include<bits/stdc++.h>
#define N 101001
#define re register
#define MAX 11001
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re char c=getchar();re bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,m,ans,lef[N],num[N];
vector<ll>g[N];
vector<ll>v[N];
bool vis[N];
inline void dfs(re ll deep)
{
	vis[deep]=true;
	ans++;
	for(re int i=0;i<v[deep].size();i++)
	{
		re ll tmp=v[deep][i];
		lef[tmp]--;
		if(lef[tmp]==1)
		{
			for(re int j=0;j<g[tmp].size();j++)
			{
				if(!vis[g[tmp][j]])
					dfs(g[tmp][j]);
			}
		}
	}
	return;
}
signed main()
{
	read(n); 
	read(m);
	for(re int i=1;i<=m;i++)
	{
		read(num[i]);
		lef[i]=num[i];
		re ll tmp;
		for(re int j=1;j<=num[i];j++)
		{
			read(tmp);
			v[tmp].push_back(i);
			g[i].push_back(tmp);
//			c[q[i].a[j]].a[++c[q[i].a[j]].num]=i;
		}
	}
	dfs(1);
	printf("%lld\n",ans);
    exit(0);
}

```


---

## 作者：巨型方块 (赞：2)

我也恨无奈啊，这道题目其实只要模拟里面用set维护就可以了

之所以不会tle是因为集合的大小最多只有250000

这样就不会被卡成n\*n

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e6+5;
struct cs{int to,nxt;}a[N];
int head[N],ll;
bool b[N];
set<int>S[N];
queue<int>Q;
int n,m,x,y,ans;
void init(int x,int y){
    a[++ll].to=y;
    a[ll].nxt=head[x];
    head[x]=ll;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&x);
        for(int j=1;j<=x;j++){
            scanf("%d",&y);
            init(y,i);
            S[i].insert(y);
        }
    }
    Q.push(1);
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int k=head[x];k;k=a[k].nxt){
            S[a[k].to].erase(x);
            if(S[a[k].to].size()==1){
                set<int>::iterator it=S[a[k].to].begin();
                if(!b[*it])b[*it]=1,Q.push(*it),ans++;
            }
        }
    }
    printf("%d",ans+1);
}
```

---

