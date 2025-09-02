# PUBLICAT - Publication

## 题目描述

Orizondo 数用于衡量某个科学家与 Rodrigo Orizondo 在学术论文合著中的“合作距离”。Rodrigo Orizondo 的 Orizondo 数是零。要获得有限的 Orizondo 数，科学家必须与至少一个已有有限 Orizondo 数的科学家共同发表论文。一个科学家的 Orizondo 数是他所有合作者中最低的 Orizondo 数加一。论文发表的顺序和编号分配顺序无关，因为每次发表后，系统会自动更新所有作者的 Orizondo 数。

你将得到一组 **论文** 数据，每篇论文包含一组作者，格式为 “AUTHOR\_1 AUTHOR\_2 ... AUTHOR\_N”（引号仅为明确表示）。其中，Rodrigo Orizondo 用 “ORIZONDO” 表示。

请输出所有作者的 Orizondo 数。输出格式为 “AUTHOR NUMBER”，若无法为某作者赋予有限的 Orizondo 数，仅输出 “AUTHOR”。作者的输出顺序应按字典序排列。

## 样例 #1

### 输入

```
3
1
ORIZONDO
2
KLEITMAN LANDER
ORIZONDO KLEITMAN
4
ORIZONDO B
A B C
B A E
D F```

### 输出

```
ORIZONDO 0
KLEITMAN 1 LANDER 2 ORIZONDO 0
A 2 B 1 C 2 D E 2 F ORIZONDO 0```

# 题解

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP9255)

偶然找到一道远古题，居然没人交，不过题目问题有点多，等着管理大大处理吧。题目很好，而且本题提供的 tric 很有用，属于是第一次做不好想，但是做过一题后再做这一类的就很简单了。

# 题目简意
可以将原问题等价为如下图论问题：平面上有 $n$ 个点，且存在若干个集合，其中每个集合包含若干个点，这些点之间相互可达，且距离均为 $1$，求其中一个指定点到所有点的最短路是多少。

# 分析
一个很朴素的想法就是把每篇文章的作者之间相互连边，但是这样子最坏就是要建 $n^2$ 条边，其中 $n$ 是所有作者的个数，然后跑一个最短路就做完了，时间复杂度 $O(cn^2)$。至于这道题能不能过我不知道，~~因为我没试过~~，不过到 SPOJ 上看了一眼数据范围，数据总数 $C$ 十分大，最多可能是 $1e4$，然后 $n$ 应该是最多 $100$，不过开 $100$ 的数组会 [RE](https://www.luogu.com.cn/record/212152089)，就说明不止这么多（~~也可能是英语太烂了就看错了~~）。虽然本题时限很大，可能可以卡过，不过在这里提供一种复杂度非常优秀的 $O(cn)$ 的做法，~~就肯定不会被卡了~~。

注意到上述算法的瓶颈在于建边，处理这样的图肯定不是把所有边建出来，可以考虑只保存有用的边（比如判断是否可达就可以只保留搜索树的边）或者是建立虚点再进行连边可以减少许多冗余边。而本题可以采用第二个办法，我们对于每一篇文章建一个虚点，让文章内部的作者都连向这个虚点，即不再让作者之间相互连边，而是将文章作为桥梁使得两个作者间接连通。也就是说假设有 $m$ 篇文章，总共 $n$ 个作者，点 $1\sim n$ 表示作者编号，而点 $n+1\sim n+m$ 表示文章。这样子新图的可达性就与原图一致，而权值大小关系呢？我们需要对每一条边适当的钦定边权以方便计算答案，这里提供两种做法。

## 法一 直接 BFS 之后答案减半
我们钦定每个作者向文章连的边权都为 $1$，本来一个集合内部的两点距离为 $1$，但是这样子操作后这个集合内部的每条边就都汇合于这个虚点，也可以理解为把这个虚点塞进每条边中，这样子两点之间的距离就变为 $2$。而原图的每条边都塞了个虚点进去，变相地把所有边权都变为 $2$，也就需要把最后的答案除以 $2$。

## 法二 01BFS 之后直接求解答案
我们也可以把每一对双向边拆成两条权值不同的边，具体地，我们把作者向文章的连边权值钦定为 $1$，而文章向作者的连边权值钦定为 $0$，这样子集合内两个点的距离不变，直接跑 01BFS 即可得到答案。

# 代码实现
## 法一
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;//开的太小会RE，1000没问题
const int INF=0x3f3f3f3f;
int T,m,n,cnt,dis[N<<1];//dis表示距离，n和m意义同上
vector<int> g[N<<1];//存图用的
queue<int> q;//BFS用的队列
map<string,int> vis;//把每个人的名字映射为一个数字
pair<int,int> p[N];//就是把边先存下来再一起加入，因为刚开始不知道n是多大，建议直接看代码理解

int num(string s)//映射
{
	if(vis.find(s)==vis.end()) return vis[s]=++n;
	return vis[s];
}

int main()
{
	cin>>T;
	while(T--)
	{
		n=0;vis.clear();cnt=0;
		for(int i=1;i<(N<<1);i++) g[i].clear();
		cin>>m;char c=getchar();//先把m后面的'\n'滤掉
		for(int i=1;i<=m;i++)
		{
			while(1)//这个处理比较麻烦要一个字符一个字符的读然后存
			{
				string s;
				char c=getchar();
				while(c>='A'&&c<='Z') s+=c,c=getchar();
				int a=num(s);
				p[++cnt]=make_pair(a,i);
				if(c=='\n') break;
			}
		}
		for(int i=1;i<=cnt;i++)//加边，此时n已经确定
			g[p[i].first].push_back(p[i].second+n),g[p[i].second+n].push_back(p[i].first);
		memset(dis,0x3f,sizeof(dis));
		int start=num("ORIZONDO");//起点
		dis[start]=0;q.push(start);//BFS框架，因为边权均为1可以保证第一次访问到就是最优，就不用像Dijkstra那样用堆一直扩展
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int v:g[u])
				if(dis[v]>dis[u]+1)
				{
					dis[v]=dis[u]+1;
					q.push(v);
				}
		}
		for(auto it=vis.begin();it!=vis.end();it++)
		{
			int i=(*it).second;
			string ans=(*it).first;
			if(dis[i]>INF/2) cout<<ans<<" ";//不可达就只输出作者
			else cout<<ans<<" "<<dis[i]/2<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

## 法二
不会 01BFS 的可以先做做[这题](https://www.luogu.com.cn/problem/P4667)。
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> PII;
const int N=1010;
const int INF=0x3f3f3f3f;
int T,m,n,cnt,dis[N<<1];
vector<PII> g[N<<1];
deque<int> q;
map<string,int> vis;
pair<int,int> p[N];

int num(string s)
{
	if(vis.find(s)==vis.end()) return vis[s]=++n;
	return vis[s];
}

int main()
{
	cin>>T;
	while(T--)
	{
		n=0;vis.clear();cnt=0;
		for(int i=1;i<(N<<1);i++) g[i].clear();
		cin>>m;char c=getchar();
		for(int i=1;i<=m;i++)
		{
			while(1)
			{
				string s;
				char c=getchar();
				while(c>='A'&&c<='Z') s+=c,c=getchar();
				int a=num(s);
				p[++cnt]=make_pair(a,i);
				if(c=='\n') break;
			}
		}
		for(int i=1;i<=cnt;i++)
			g[p[i].fi].push_back(make_pair(p[i].se+n,1)),g[p[i].se+n].push_back(make_pair(p[i].fi,0));
		memset(dis,0x3f,sizeof(dis));
		int start=num("ORIZONDO");
		dis[start]=0;q.push_back(start);//只有这里不一样，边权为0插入队头，否则插入队尾，这样保证了广搜的单调性
		while(!q.empty())
		{
			int u=q.front();q.pop_front();
			for(auto v:g[u])
				if(dis[v.fi]>dis[u]+v.se)
				{
					dis[v.fi]=dis[u]+v.se;
					if(v.se) q.push_back(v.fi);
					else q.push_front(v.fi);
				}
		}
		for(auto it=vis.begin();it!=vis.end();it++)
		{
			int i=(*it).se;
			string ans=(*it).fi;
			if(dis[i]>INF/2) cout<<ans<<" ";
			else cout<<ans<<" "<<dis[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

最后提供两道类似的题大家可以练练手：

[CF1263D Secret Passwords](https://www.luogu.com.cn/problem/CF1263D)

[AT_abc302_f [ABC302F] Merge Set](https://www.luogu.com.cn/problem/AT_abc302_f)

完结撒花！！！

---

