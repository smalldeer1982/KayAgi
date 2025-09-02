# Reposts

## 题目描述

One day Polycarp published a funny picture in a social network making a poll about the color of his handle. Many of his friends started reposting Polycarp's joke to their news feed. Some of them reposted the reposts and so on.

These events are given as a sequence of strings "name1 reposted name2", where name1 is the name of the person who reposted the joke, and name2 is the name of the person from whose news feed the joke was reposted. It is guaranteed that for each string "name1 reposted name2" user "name1" didn't have the joke in his feed yet, and "name2" already had it in his feed by the moment of repost. Polycarp was registered as "Polycarp" and initially the joke was only in his feed.

Polycarp measures the popularity of the joke as the length of the largest repost chain. Print the popularity of Polycarp's joke.

## 样例 #1

### 输入

```
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
SoMeStRaNgEgUe reposted PoLyCaRp
```

### 输出

```
2
```

# 题解

## 作者：封禁用户 (赞：13)

# dijkstra+map大法！
看到楼下大佬都是用的Floyd，却没人用~~简洁易懂的~~dijkstra

**先化简一下题意：**

- 输入格式：name1 转发 name2 

- 输出格式：从Polycarp开始的一个转发的最长路线

**解题思路：**

对于输入，都是string类型的（~~鬼都知道~~），

那么**我们便要将它通过map来射映出以数字为编号的顶点，**

便设立一个变量pos来记录此时的还没有出现的名字应设立的编号（可能有些绕）

再维护一个map<string,int>name来记录名字u的编号，

**特别地**，若u(name1)或v(name2)为Polycarp，便将起点设为pos

当然还要记录顶点总数，也就是n

**但是，坑点来了：** 在进行连边操作之前，

要先有一个操作：将u和v的每一个字符都设为小写！

之后连边：G[name[u]].push_back(edge{name[v],1});

**不过要先输入v再输入u**，毕竟是一个转发的过程（u->v）;

连边结束后，再愉快地写一遍dijkstra~~的板子~~，但最后要从1~n遍历d[ ]数组，找一个最大值

# 这个世界上并不缺少水题，
# 而是缺少发现水题的眼睛。

 _**Code:**_ 

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN=1010;
int t,n,start,pos=1,d[MAXN],ans;
map<string,int>name;
struct edge
{
	int to,cost;
};
vector<edge>G[MAXN];
typedef pair<int,int>P;
inline void dijkstra(int s)
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d[i]=1e9;
	d[s]=0;
	q.push(P{0,s});
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(d[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				q.push(P{d[e.to],e.to});
			}
		}
	}
	for(register int i=1;i<=n;i++) if(d[i]!=1e9&&ans<d[i]) ans=d[i]; 
	printf("%d\n",ans+1);
	return;
}
string change(string s)
{
	for(register int i=0;i<s.size();i++) s[i]=tolower(s[i]);
	return s;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		string u,y,v;
		cin>>v>>y>>u;
		v=change(v),u=change(u);//现将所有的字符都转换成小写 
		if(!name[u]) name[u]=pos,n++,pos++;//更新 
		if(!name[v]) name[v]=pos,n++,pos++;
		if(u=="Polycarp") start=name[u];//特判 
		if(v=="Polycarp") start=name[v];
		G[name[u]].push_back(edge{name[v],1});//连边 
	}
	dijkstra(1);
	return 0;
}
```
看看蒟蒻写的这么认真，是否可以点个赞再走呢？


---

## 作者：_FILARET_ (赞：8)

这道题难度大概是在**提高组D1T2~D1T3**难度的，有兴趣打TG的可以来试一下。本题是**2015VKcup**的题，CF评分为**Rating1700**以上。所以说普及组的各位dalao们强♂肛不出来也不用太着急呦~

本题用到了两个东东：字符串的散列表处理（可以用map直接解决）和弗洛伊德（Floyd）算法。

先来看一看弗洛伊德算法的原理：

弗洛伊德算法是用来求**最长路**的算法，通过不停循环找出可以进行松弛操作的三个点，经过比较后按照情况进行松弛。

不需松弛的情况：![](https://cdn.luogu.com.cn/upload/pic/50359.png)

需要松弛的情况：![](https://cdn.luogu.com.cn/upload/pic/50360.png)

接下来我们看一下代码主要部分：

**弗洛伊德算法函数**
```cpp
void floyd(){
	for(int i = 1 ; i <= tmp ; i ++){
		f[i][i] = 0;
	}
	for(int k = 1 ; k <= tmp ; k ++){
		for(int i = 1 ; i <= tmp ; i ++){
			for(int j = 1 ; j <= tmp ; j ++){
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]); // 松弛
			}
		}
	}
	return;
}
```

**初始化邻接矩阵**
```cpp
void init(){
	for(int i = 0 ; i < MAXN ; i ++){
		for(int j = 0 ; j < MAXN ; j ++){
			f[i][j] = INF; // 将所有边权标成Infinity
		}
	}
	return;
}
```

**the Grand Finale - 完整代码**

```cpp
//DeadPool123 [INC] - All Fxxking Right Reserved
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300 + 10;
const int INF = 1e6;
int N, tmp = 0; // N为回复次数，tmp为人数
map<string, int> hsh; // 用map实现的fake散列表
int f[MAXN][MAXN]; // 邻接矩阵
int plcp, ans = -INF; // plcp为Polycarp小哥哥的map值，ans为最终答案

void init(){
	for(int i = 0 ; i < MAXN ; i ++){
		for(int j = 0 ; j < MAXN ; j ++){
			f[i][j] = INF; // 初始化将邻接矩阵设为Infinity
		}
	}
	return;
}

void l_case(string &x){
	int len = x . length();
	for(int i = 0 ; i < len ; i ++){
		if(x[i] >= 'A' && x[i] <= 'Z'){
			x[i] += 32; // 将一个字符串中的大写字母全部转成小写字母，便于用Map进行散列
		}
	}
}

void floyd(){
	for(int i = 1 ; i <= tmp ; i ++){
		f[i][i] = 0; // 自己连自己的距离肯定为0嘛~
	}
	for(int k = 1 ; k <= tmp ; k ++){
		for(int i = 1 ; i <= tmp ; i ++){
			for(int j = 1 ; j <= tmp ; j ++){
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]); // 两个点间边权进行松弛操作
			}
		}
	}
	return;
}

int main(){
	init();
	cin >> N;
	for(int i = 1 ; i <= N ; i ++){
		string v, rep, u;
		cin >> v >> rep >> u; // name1 reposted name2 的回复操作
		l_case(v); // 转小写
		l_case(u);
		if(hsh[v] == 0){
//			cout << v << endl; // 在map中记录散列
			hsh[v] = ++ tmp;
		}
		if(hsh[u] == 0){
//			cout << u << endl;
			hsh[u] = ++ tmp;
		}
		f[hsh[v]][hsh[u]] = 1; // 连边
		f[hsh[u]][hsh[v]] = 1; // 连反向边
//		cout << endl;
	}
//	printf("%d\n", tmp);
	plcp = hsh["polycarp"]; // 记录Polycarp小哥哥的散列值
//	for (int i = 1 ; i <= N ; i ++) {
//		for (int j = 1 ; j <= N ; j ++) {
//			printf("%d ", f[i][j]);
//		}
//		printf("\n");
//	}
	floyd(); // 程序的肮脏本体
	for(int i = 0 ; i <= tmp ; i ++){
		if(f[plcp][i] >= INF){
			continue; // 如果这条回复不存在，则ctn
		}
		else{
			ans = max(ans, f[plcp][i]); // 不然就通过max记录进ans
		}
	}
	cout << ans + 1; // 输出时要带上Polycarp小哥哥玩
	return 0;
} 
```

---

## 作者：long_long (赞：5)

我看大佬们都用的是map大法或floyd,但这道题我有一个更简单些的思路和大家分享（话说应该不会UKE）。

# **思路：** 
首先输入n，while循环n--。再循环里定一个a,b,c。a和b表示两个名字，然后c表示中间那个‘reposted’。输入完把a和b都变成小写。用last表示下一个人应该repost谁（每一次的last是上一次的a）。判断一下last是否等于这次的b如果等于，把sum++。如果不等于，这就意味着这一个友联在此断了，所以把他改回初始的2。为什么是2呢？因为看第三个样例可得出如果只有一个人repost Polycarp那么友联的长度就是2。然后把max(sum,maxn)记到maxn中。再把下次的last记为a。如果n==0 break。

```
while(n--){
        string a,c,b;
        cin>>a>>c>>b;
        for (char & i : a) if(i>='A'&&i<='Z') i+=' ';
        for (char & i : b) if(i>='A'&&i<='Z') i+=' ';
        if(last==b) sum++;
        if(last!=b) sum=2;
        maxn=max(sum,maxn);
        last = a;
        if(n==0) break;
    }
```

最后输出maxn

---

## 作者：ifyml (赞：2)

把**字符串映射为数字**，然后就找最长路径，~~但读入时处理不是很好~~...
```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;
int n,ok,t,p,ans;
int head[201],op[201][201];
string a[601];
map<string,int>mp;//映射字符串
void zh(int x)
{
	for(int j=0;a[x][j]!='\0';j++)
	 if(a[x][j]<'a')a[x][j]+=32;//大写转换成小写
}
int main()
{
	scanf("%d",&n);ok=3*n;
	for(int i=1;i<=ok;i++){cin>>a[i];zh(i);}
	for(int i=1;i<=n+1;i++)for(int j=1;j<=n+1;j++)op[i][j]=989898989;//初始化
	for(int i=1;i<=n;i++)
	{
	   if(mp[a[3*i-2]]==0)mp[a[3*i-2]]=++t;//开始映射
	   if(mp[a[3*i]]==0)mp[a[3*i]]=++t;//开始映射
	   op[mp[a[3*i]]][mp[a[3*i-2]]]=1;//建边
	}
	for(int i=1;i<=t;i++)op[i][i]=0;//相同点距离为零
	for(int k=1;k<=t;k++)
	 for(int i=1;i<=t;i++)
	  for(int j=1;j<=t;j++)
	  	op[i][j]=min(op[i][j],op[i][k]+op[k][j]);//找出路径
	for(int i=1;i<=t;i++)
	 if(op[2][i]!=989898989)
	  ans=max(ans,op[2][i]);//找出最大值
	printf("%d\n",ans+1);//输出时答案加上自己
	return 0;
}
```

---

## 作者：Southern_Dynasty (赞：1)

不太理解为什么题解区基本上都用的 Dijkstra/Floyd，这里写个简单点的做法。

注意题目里有一条关键性质：

对于每一条 `name1 reposted name2`，满足 `name1` 肯定是还没有转发过照片的，`name2` 这个人已经有这个照片了。

这样如果我们从 `name1` $\to$ `name2` 连边，会得到一个**内向树森林**。

这样，对于每一棵内向树，我们只需要求出其最大深度，然后对所有的内向树的最大深度取 $\max$ 就是答案。

那么怎么求内向树的最大深度？

考虑找到内向树的每个叶子，从下往上走，记录路径长度并更新答案即可。

怎么找到内向树的叶子？

根据内向树的性质，入度为 $0$ 且出度为 $1$ 的点就是叶子。

最后是字符串处理的问题：用 `map` 之类的转换一下编号即可，这里我用的 `gp_hash_table`。还有注意一下大小写的问题，可以把所有小写字母都换成大写。

然后就做完了。

时间复杂度 $O(n)$，可以通过此题。

[Code](https://codeforces.com/contest/522/submission/207563158)

---

