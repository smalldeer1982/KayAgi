# Game

## 题目描述

F 和 R 喜欢玩电脑游戏。F 最近发现了一个新游戏，R 也觉得很有趣。
这个游戏包括 $n$ 个部分，而为了完成某个部分，可能需要先完成其它的几个部分。
我们知道这个游戏总是能够完成的，也就是说，它的各个部分之间不会发生循环依赖关系。

R有3个可以玩游戏的电脑，我们用1，2，3来给电脑编号。电脑被放置在不同的房间。
同时需要注意的是，游戏的每个部分只能在其中的一台电脑上完成。

R可以完成下面的动作：
- 在某些电脑上完成某些工作，并且在任意电脑上完成任意的工作都需要花费 1 小时。
- 从 1 号电脑移动到 2 号电脑，花费的时间是 1 小时。
- 从 1 号电脑移动到 3 号电脑，花费的时间是 2 小时。
- 从 2 号电脑移动到 1 号电脑，花费的时间是 2 小时。
- 从 2 号电脑移动到 3 号电脑，花费的时间是 1 小时。
- 从 3 号电脑移动到 1 号电脑，花费的时间是 1 小时。
- 从 3 号电脑移动到 2 号电脑，花费的时间是 2 小时。

帮助R找到花费最少时间完成游戏的方法。在开始的时候，R 可以选择在任意电脑的位置。

## 说明/提示

注意第二个样例：在开始游戏的时候，最好的策略是选择 3 号电脑的位置。
首先完成第 5 部分，然后到 1 号电脑完成第 3 和第 4 部分，然后到 2 号电脑完成第 1 和第 2 部分。
这样总的花费的时间是 $1+1+2+1+2 = 7$。

## 样例 #1

### 输入

```
1
1
0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 2 1 1 3
1 5
2 5 1
2 5 4
1 5
0
```

### 输出

```
7
```

# 题解

## 作者：Transparent (赞：1)

不难看出，要让总时间最少，
就一定要让移动位置消耗的时间减少，
因为完成任务需要的总时间（不计移动）是不变的。

可以看出，（如果把它们看成环的话）
从编号小的电脑向编号大的电脑（当然$3→1$也算）移动更优，
因为电脑一共只有 $3$ 台，
而向编号大的方向移动两次和
向编号小的方向移动一次用时是相等的，
但是向编号大的方向移动可以多经过一台电脑，
说不定就有任务可以在那里完成。

所以只需要考虑向编号大的方向移动。

为了节省时间，在一台电脑上当然要尽可能多地完成任务，
为了统计这个任务的先决条件是否达成，
可以用和拓扑排序类似的思想：
找到入度为 $0$ 的点，
把它删除（即完成任务），
那么从它出发的所有边都要删除，
删边就是把这条边指向的点的入度减 $1$ ，
当然开始也要从一个入度为 $0$ 的点开始。

最后，因为可以从 $3$ 台电脑中任意选择一台开始，
所以还要分 $3$ 中情况来讨论，
最终答案就取最小值。

因为题目保证不存在循环依赖关系，
所以跑完拓扑后不用判断是否有点没有被走到。

代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int fir[201],tot,in[201],In[201];//两个in，一个用来拓扑，一个用来备份 
int nxt[400201],to[400201];
inline void add_edge(int u,int v)//链式前向星存图 
{
	to[++tot]=v;
	nxt[tot]=fir[u];
	fir[u]=tot;
}
int n,c[201],cc[4][201];
queue<int>q[5];//队列，之后拓扑要用 
inline int solve(int x)
{
	int ans=0;
	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=cc[i][0];j++)
		{
			if(!in[cc[i][j]])//找到入度为0的点 
			q[i].push(cc[i][j]); //加入队列 
		}
	}
	int now=x-1;//从x-1开始是因为进入while后要先加一 
	while(1)
	{
		now++;
		if(now==4) now=1;//转了一圈，再从头开始 
		while(!q[now].empty())//如果有没有处理的入度为0的点 
		{
			ans++;//完成任务花费时间 
			int u=q[now].front();
			q[now].pop();//弹掉当前点 
			for(register int i=fir[u];i;i=nxt[i])//枚举以队首元素为起点的边 
			{
				int v=to[i];
				in[v]--;//入度减一 
				if(!in[v])//如果入度为0 
				{
					q[c[v]].push(v);//加入队列 
				}
			}
		}
		if(q[1].empty()&&q[2].empty()&&q[3].empty())
		//如果每台电脑上都没有任务等待完成 
		return ans;//返回答案 
		ans++;//移动需要的时间 
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",c+i);
		cc[c[i]][++cc[c[i]][0]]=i;//方便第一次入队的操作 
	}
	for(register int i=1;i<=n;i++)
	{
		int sze=0,tmp=0;
		scanf("%d",&sze);
		for(register int j=1;j<=sze;j++)
		{
			scanf("%d",&tmp);
			add_edge(tmp,i);//加边建图 
			In[i]++;//统计入度 
			in[i]++;
		}
	}
	int ans=0x7fffffff;//赋极大值，便于取最小值 
	ans=min(ans,solve(1));
	for(register int i=1;i<=n;i++)in[i]=In[i];//恢复入度 
	ans=min(ans,solve(2));
	for(register int i=1;i<=n;i++)in[i]=In[i];//同上 
	ans=min(ans,solve(3));
	printf("%d\n",ans);
	return 0;
}
```

警告还真有用，
RE一直没调出来，
开最多警告后在16行报了一个 iteration 2u invokes undefined behavior，
一查是编译器提醒你循环中涉及到的数组可能越界了……

~~不过数组越界在本地跑还没问题……~~

---

## 作者：ZLCT (赞：0)

# CF213A Game
## 题面描述
一个环上有 $3$ 个点，每个点上有若干任务，这些任务有可能有依赖关系，每次顺时针走需要花费 $1$ 的代价，逆时针走需要花费 $2$ 的代价，每个任务需要花费 $1$ 的代价。可以从任意点出发，保证数据有解，求完成任务最小代价。
## 几个小观察
- 首先我们可以发现完成任务需要的时间是固定的，我们最小化的只是移动的代价。
- 其次我们肯定不会选择逆时针走。证明：假设存在一个更优解存在逆时针走，那么我们可以调整为顺时针走两次，这样同样的代价还可以多走到一个点，一定比原解不劣。
## 于是就做完了？
### 做法1：模拟
我们模拟上述过程，通过 dfs 不断重复，最后直到所有点都被遍历。\
复杂度分析：由于最多三次就会完成一个任务（否则就成环无法完成了），所以完成所有任务的总次数最多为 $3n$ 次。加上维护所用的数据结构和递归的常数，在不开 O2 的情况下完全能过。\
tips：因为有可能出现同一个点的任务有依赖关系，所以如果这个点中有任务被完成，下一次递归需要再重新扫一遍这个点。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[214];
set<int>s1[214];
set<int>st1[4];
set<int>sst1[214];
set<int>s[214],st[4],sst[214];
int ans=1e9+7;
int nxt(int id){
    if(id==1)return 2;
    if(id==2)return 3;
    return 1;
}
void dfs(int id,int sum,int num){
    if(num==n){
        ans=min(ans,sum);
        return;
    }
    bool flag=0;
    vector<int>del;
    for(int i:st[id]){
        if(s[i].empty()){
            num++;
            flag=1;
            del.push_back(i);
            for(int j:sst[i]){
                s[j].erase(i);
            }
        }
    }
    for(int p:del){
        st[id].erase(p);
    }
    if(flag)dfs(id,sum,num);
    else dfs(nxt(id),sum+1,num);
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        st[a[i]].insert(i);
        st1[a[i]].insert(i);
    }
    for(int i=1;i<=n;++i){
        int ki,x;
        cin>>ki;
        for(int j=1;j<=ki;++j){
            cin>>x;
            s[i].insert(x);
            s1[i].insert(x);
            sst[x].insert(i);
            sst1[x].insert(i);
        }
    }
    dfs(1,0,0);
    for(int i=1;i<=n;++i){
        s[i]=s1[i];
        sst[i]=sst1[i];
    }
    for(int i=1;i<=3;++i){
        st[i]=st1[i];
    }
    dfs(2,0,0);
    for(int i=1;i<=n;++i){
        s[i]=s1[i];
        sst[i]=sst1[i];
    }
    for(int i=1;i<=3;++i){
        st[i]=st1[i];
    }
    dfs(3,0,0);
    cout<<ans+n<<'\n';
    return 0;
}
```
### 做法2：topo
考虑是否能完成任务的条件，就是这个任务的出度为 $0$，于是我们就可以按 topo 的思想，不断把当前点出度为 $0$ 的任务完成，如果不存在这样的任务，就继续完成下一个点。\
复杂度：这样可以省去枚举无用点和递归的复杂度——于是在开 O3 的情况下比上一种方法快 60ms。~~（不开还过不了，有点玄学了）~~
### code
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
int n,a[214];
vector<int>v[214];
queue<int>q[4],q1[4];
int deg[214],deg1[214];
int ans=1e9+7;
void topo(int id,int sum,int num){
    while(true){
        while(!q[id].empty()){
            int st=q[id].front();
            q[id].pop();
            for(int x:v[st]){
                if(--deg[x]==0){
                    q[a[x]].push(x);
                }
            }
        }
        if(q[1].empty()&&q[2].empty()&&q[3].empty()){
            ans=min(ans,sum);
            return;
        }
        sum++;id++;
        if(id==4)id=1;
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        int ki,x;
        cin>>ki;
        for(int j=1;j<=ki;++j){
            cin>>x;
            v[x].push_back(i);
            deg[i]++;deg1[i]++;
        }
    }
    for(int i=1;i<=n;++i){
        if(deg[i]==0){
            q[a[i]].push(i);
            q1[a[i]].push(i);
        }
    }
    topo(1,0,0);
    for(int i=0;i<=3;++i){
        q[i]=q1[i];
    }
    for(int i=1;i<=n;++i){
        deg[i]=deg1[i];
    }
    topo(2,0,0);
    for(int i=0;i<=3;++i){
        q[i]=q1[i];
    }
    for(int i=1;i<=n;++i){
        deg[i]=deg1[i];
    }
    topo(3,0,0);
    cout<<ans+n<<'\n';
    return 0;
}
```

---

## 作者：YFF1 (赞：0)

来一发不用拓扑排序的。先把游戏部分之间的关系抽象成一张有向图，使用贪心的策略，每次遍历所有没有约束条件的点作为搜索的起点，然后遍历到一个点时就去掉被它对其他点的约束，优先处理与它在同一台机器上的游戏部分，根据所处机器编号优先处理其他机器的游戏部分。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,w[200005],k,a,st[20005],cnt[200005],cnt2[200005],ans=1e9,use[5][5],h=0;
vector<int>g[200005],s[200005];
bool vis[200005];
void dfs(int x,int sum){//因为是贪心策略，所以不用回溯
	vis[x]=1;
	int tot=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==1)tot++;
	}
	if(tot==n){
		ans=min(ans,sum);
		return ;
	}
	for(int i:g[x])cnt[i]--;
	for(int i=1;i<=n;i++){
		if(cnt[i]==0&&!vis[i]&&w[i]==w[x])dfs(i,sum+1);
	}//优先处理同一机器
	if(w[x]==1){
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==2)dfs(i,sum+use[w[x]][w[i]]+1);
		}
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==3)dfs(i,sum+use[w[x]][w[i]]+1);
		}
	}
	if(w[x]==2){
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==3)dfs(i,sum+use[w[x]][w[i]]+1);
		}
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==1)dfs(i,sum+use[w[x]][w[i]]+1);
		}
	}
	if(w[x]==3){//分讨
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==1)dfs(i,sum+use[w[x]][w[i]]+1);
		}
		for(int i=1;i<=n;i++){
			if(cnt[i]==0&&!vis[i]&&w[i]==2)dfs(i,sum+use[w[x]][w[i]]+1);
		}
	}
	return ;
}
signed main () {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i];
		s[w[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		cin>>k;
		if(k==0)st[++h]=i;
		cnt[i]=k;
		cnt2[i]=k;
		for(int j=1;j<=k;j++){
			cin>>a;
			g[a].push_back(i);//建图
		}
	}
	use[1][2]=1;
	use[1][3]=2;
	use[2][1]=2;
	use[2][3]=1;
	use[3][1]=1;
	use[3][2]=2;//走过去花的时间
	for(int i=1;i<=h;i++){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;j++)cnt[j]=cnt2[j];
		dfs(st[i],1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

### 思路
贪心让移动次数最小，拓扑排序找优先级，用 set 记录每台电脑当前可完成的任务。 

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2005],in[2005],b[2005],x,mn=1e9;
vector<int>e[2005];
set<int>s[10];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i){
		cin>>b[i];
		for(int j=1;j<=b[i];++j) cin>>x,e[x].push_back(i);
	}
	for(int i=1;i<=3;++i){
		int ans=0,pos=i;
		for(int j=0;j<=3;++j) s[j].clear();
		for(int j=1;j<=n;++j){
			in[j]=b[j];
			if(!in[j]) s[a[j]].insert(j);
		}
		while(s[1].size()+s[2].size()+s[3].size()>0){
			while(s[pos].empty()) pos=pos%3+1,++ans;
			int h=*s[pos].begin();
			s[pos].erase(h);
			for(int v:e[h])
				if(--in[v]==0) s[a[v]].insert(v);
		}
		mn=min(mn,ans);
	}
	cout<<mn+n;
	return 0;
}
```

---

