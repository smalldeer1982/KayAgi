# Following Orders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=60

[PDF](https://uva.onlinejudge.org/external/1/p124.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/a4a2f6fd96f29dbbab122912895a18a100222b62.png)

## 样例 #1

### 输入

```
a b f g
a b b f
v w x y z
v y x v z v w v```

### 输出

```
abfg
abgf
agbf
gabf
wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy```

# 题解

## 作者：Silence_water (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/UVA124)


------------

### Description

> 给出所有的字符和字符间的先后顺序，按字典序最小的方式输出所有满足条件的字符排列。


------------

### Analyse

- 题目要求输出**所有满足条件**的字符排列，因此我们可以用 dfs 全排列来构造。

- 对于字符间的先后顺序，我们可以使用拓扑排序。但考虑到数据范围较小，我用数组 $app$ 来表示字符 $a$ 是否应在 $b$ 前。当然，在构造字符串时，我们要对当前这个字符是否符合与前面所有已选字符的关系进行判断。


------------

### Pay attention

1. 由于是多组数据题，记得要清空每个数组，并且要注意控制行末换行。

2. 由于字符关系是两两之间的，但读入是整行的，所以要过滤空格。

3. 全排列时记得回溯。


------------

### Code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int M=30;
bool avi[M],vis[M],app[M][M];
int ans[M],num;
string s;
bool check(int a,int b)
{
    for(int i=0;i<a;i++)
        if(app[b][ans[i]])return false;
    return true;
}//判断是否符合要求 
void clear()
{
	num=0;
    memset(vis,false,sizeof(vis));//全排列中是否选过 
    memset(ans,0,sizeof(ans));//存储答案 
    memset(avi,false,sizeof(avi));
    memset(app,false,sizeof(app));//是否存在该种大小关系 
}
void dfs(int now)
{
    if(now==num)
    {
        for(int i=0;i<now;i++)
			cout<<(char)(ans[i]+'a');
        cout<<endl;
        return;
    }
	for(int i=0;i<26;i++)
        if(avi[i]&&!vis[i]&&check(now,i))//判断是否能接下去 
        {
            vis[i]=true,ans[now]=i;
            dfs(now+1);
            vis[i]=false;//回溯 
        }
}
int main()
{
	bool tof=false;
    while(getline(cin,s))
    {
		if(tof)cout<<endl;//控制换行 
        clear();//数组清空 
        int len=s.size();
        for(int i=0;i<len;i++)
			if(s[i]!=' ')//过滤空格
	        {
	            num++;
	            avi[s[i]-'a']=true;//说明该字符属于原串 
	        }
        getline(cin,s);
        len=s.size();
        for(int i=0;i<len;i+=4)
            app[s[i]-'a'][s[i+2]-'a']=true;//每次处理一对 
        dfs(0);
        tof=true;
    }
    return 0;
}
```


------------
感谢观看。

---

## 作者：user100566 (赞：1)

## 题目分析

如果阅读英文图片存在困难，请看完整版[翻译](https://www.luogu.com.cn/discuss/992795)。

将字母抽象为点，字母关系抽象为有向边，本题就是标准的求所有拓扑排序方案，但本题细节较多。

## 思路

### 关于方案总数

拓扑排序的方案数最多是**阶乘**级别的，下面这张图虽然是连通的，但是扩展为阶乘方案数的大图***一目了然，不言而喻***。

![](https://cdn.luogu.com.cn/upload/image_hosting/g7j0nazb.png)

[源代码](https://www.luogu.com.cn/paste/ebybqzow)

更极端的，如果这个图由 $n$ 个孤立点组成，方案数等于 $n$ 的全排列方案数 $n!$。

目前没有已知的多项式时间算法能精确地计算出一个图的拓扑排序方案数，但是如果图是一颗树，就可以在  $O(n)$ 的时间内计算，不过这是题外话。

由于方案总数很多，因此这种题的数据范围一般较小，总方案数可以是隐式的 $n!$，也可以直接指出，在本题中，最多方案数为 $300$。

以上分析说明没有很好的算法能求解大规模的全拓扑排序问题，即使只要求输出总方案数。掌握下面~看起来很简单~的算法即可。

### 编码

如果使用 BFS 输出全拓扑排序，需要记忆队列，例如上面的图中，初始队列中有 $1,3,5,7,9$，如果选择 $1$ 第一个出队，后面仍需处理 $3,5,7,9$ 第一个出队的情况，这些情况下仍需将 $1$ 放回队列。代码实现的话你就会发现本质上还是 DFS。

输出所有拓扑排序的标准解法是 DFS，记 $turpo$ 数组为拓扑排序，则 DFS 的前进即为 $turpo$ 排序的扩展，注意这和树上 DFS 有区别。下面的代码在 DFS 中枚举所有可能的下一个拓扑排序值。

枚举下一个拓扑排序值时，优先 DFS 字典序小的节点（题目要求），后 DFS 字典序大的节点，当拓扑排序完成时，输出当前拓扑排序。

本题需要将小写字母转化为计算机方便处理的数字 id，同时需要将小写字母间的全序关系转移到数字的全序关系上，以便 DFS 中按字典序输出拓扑排序方案。下面的代码用**离散化**做到了这一点。~当然你也可以直接将小写字母视为 ASCII 值来做。~

相关细节已在代码中给出。

## 复杂度分析

$20!$ 是一个天文数字，因此 $O(n\times n!)$ 是没有什么意义的，我们设方案总数为 $k$，本题中 $k\le 300$，可以轻易证明后文给出的算法的时间复杂度的一个上界为 $O(kn^2)$，简单证明：

> 只要拓扑排序存在，任何有效的部分拓扑排序都能扩展为完整的拓扑排序。这一事实说明**递归树**上的叶子节点等价于底部节点。
> 
> 因为方案总数为 $k$，所以底部节点数有 $k$ 个，由上面的事实可知叶子节点有 $k$ 个，因为树高为 $n$，所以总节点数最多为 $kn$。
>
> 显然每个节点对应的 DFS 调用（递归部分的贡献算在子节点上）的复杂度为 $O(n)$。
>
> 综上，该算法的一个复杂度上界为 $O(kn^2)$。
> 
似乎真实上界是 $O(kn)$，大致思路是：整棵递归树不太可能是相互不交的 $k$ 条长度为 $n$ 的链，大部分节点是多条链的公共点，实际总节点数远远小于 $kn$。但具体证明困难，望神犇证明/证伪。

~本题中没什么必要的优化：~

> 如果我们假设枚举的下一个拓扑排序节点全部有效，那么可以证明复杂度为 $O(kn)$。
> 
> 利用这一性质进行优化，我们最好能随时知道下一个可取的节点而不用暴力枚举，同时还要支持从小到大枚举，使用一个动态有序数组维护即可，例如 STL set，这样复杂度上界降为 $O(kn\log n)$，当然对于本题没有必要。

## 总结

### 主程序

1. 读入小写字母变量，离散化为数字 id，即图上的节点。
2. 读入变量约束关系，将小写字母间的约束关系按离散化规则转化为数字 id 间的关系，即图上的有向边。
3. DFS 输出所有拓扑排序。
4. 回到 1. 处理多组数据，注意处理清 0 和输出的组间换行问题。

### DFS
入口：在主程序中枚举可能的第一个拓扑排序结点。

1. 如果完成拓扑排序，输出。
2. 标记当前节点被访问。
3. 更新其它节点的入度。
4. DFS 前进：按字典序枚举所有可能的下一个拓扑排序结点，递归。
5. 回溯：移除当前结点的被访问标记，恢复入度到当前调用之前。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
char character[20];
vector<int> graph[20];
int indegree[20];
int turpo[20];
bool visited[20];

inline void print(){
	for(int i=0; i<n; ++i){
		putchar(character[turpo[i]]);
	}
	putchar('\n');
}
void dfs(int u, int depth){
	turpo[depth] = u;
	if(depth==n-1){
		print();
		return;
	}
	visited[u] = true;
	for(int v:graph[u]){
		if(!visited[v]) --indegree[v];
	}
	// 注意，这里的 DFS 前进是"前进到下一个拓扑排序结点"，与 u 的边无关 
	for(int v=0; v<n; ++v){
		if(!visited[v] && !indegree[v]) dfs(v, depth+1);
	}
	for(int v:graph[u]){
		if(!visited[v]) ++indegree[v];
	}
	visited[u] = false;
}

int main(){
	char buffer[100];
	while(gets(buffer)){ // 读取到 EOF 时，gets 返回 nullptr 
		// UVA 评测不过滤行末空格，否则 Presentation Error
		// 在除第一个测试点外的测试点前输出换行
		// 正确性依赖于测试点后没有对 n 清 0 
		if(n) putchar('\n');
		n = (strlen(buffer)+1)>>1;
		for(int i=0; i<n; ++i){
			character[i] = buffer[i<<1];
		}
		// 离散化，将"字母字典序的先后"转移到"节点 id 上的先后"
		sort(character, character+n);
		gets(buffer);
		m = (strlen(buffer)+1)>>2;
		for(int i=0; i<m; ++i){
			// 离散化 
			int from = lower_bound(character, character+n, buffer[i<<2])-character;
			int to = lower_bound(character, character+n, buffer[i<<2|2])-character;
			graph[from].push_back(to);
			++indegree[to];
		}
		// 从 [0, n-1] 中选任意一个点作为拓扑排序的起点
		// 字典序的先后关系体现在 i 从小增大上，DFS 中同
		for(int i=0; i<n; ++i){
			if(!indegree[i]){
				dfs(i, 0);
			}
		}
		// 清 0 indegree 和 graph
		// n, m, ch, turpo 是覆盖的不需要清空
		// visited 在 dfs 中自动清空，也不需要额外清空 
		memset(indegree, 0, sizeof(int)*n);
		for(int i=0; i<n; ++i) graph[i].clear();
	}
}
```

---

## 作者：封禁用户 (赞：1)

一个很明显的拓扑排序。因为本题要求输出所有的拓扑排序，$\text{dfs}$ 会更为方便。

讲一下拓扑排序的方法：找一个没有遍历过的子节点字母，如果断开正在遍历的字母和子节点字母以后子节点字母的入度为 $0$，就以这个字母为父节点继续 $\text{dfs}$。记得要回溯。

记得在输入完所有字母以后从小到大排序，不然输出的就不是字典序。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=130;
char a[30];
vector<int> G[N];
int r[N];
char topo[N];
int idx;
bool vis[N];
void top_sort(char z,int x){
	topo[x]=z;
	if(x==idx){
		for(int i=1;i<=idx;++i){
			cout<<topo[i];
		}
		cout<<endl;
		return ;
	}
	vis[z]=1;
	for(auto i:G[z]){
		if(!vis[i]) --r[i];
	}
	for(int i=1;i<=idx;++i){
		if(!r[a[i]]&&!vis[a[i]]){
			top_sort(a[i],x+1);
		}
	}
	for(auto i:G[z]){
		++r[i];
	}
	vis[z]=0;
} 
signed main(){
	string s;
	bool f=0;
	while(getline(cin,s)){
		if(f){
			cout<<endl;
		}
		memset(r,0,sizeof(r));
		memset(vis,0,sizeof(vis));
		for(int i='a';i<='z';++i){
			G[i].clear();
		}
		int len=s.size();
		idx=0;
		for(int i=0;i<len;++i){
			if(s[i]<='z'&&'a'<=s[i]){
				a[++idx]=s[i];
			}
		}
		sort(a+1,a+idx+1);
		getline(cin,s);
		len=s.size();
		char qaz;
		for(int i=0;i<len;++i){
			if(i%4==0) qaz=s[i];
			if(i%4==2){
				G[qaz].push_back(s[i]);
				++r[s[i]];
			}
		}
		for(int i=1;i<=idx;++i){
			if(!r[a[i]]){
				top_sort(a[i],1);
			}
		}
		f=1;
	}
	return 0;
}
```

---

## 作者：ningago (赞：1)

### 题意
给定若干个字符，以及若干个大小关系，按字典序求出满足大小关系的**所有**排序方式。

### 思路

乍一看很明确的是一道拓扑排序，但不同于往常要输出所有排序方式，所以要以 dfs 的方式进行排列。

坑点：

- 多组数据输出之间有空行！！！样例有误！！！
- 要根据字典序大小输出，样例很坑，需要先排个序。

### Code：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

#define N 30
using namespace std;

map <char,int> mp1;
map <int,char> mp2;
vector <int> g[N];
int ru[N];
char num[N];
int ans[N],idx;
void dfs(int u)
{
    if(u == idx + 1)
    {
        for(int i = 1;i <= idx;i++)
            printf("%c",mp2[ans[i]]);
        printf("\n");
        return;
    }
    for(int i = 1;i <= idx;i++)
    {
        if(!ru[i])
        {
            ru[i]--;
            ans[u] = i;
            for(int j = 0;j < g[i].size();j++)
                ru[g[i][j]]--;
            dfs(u + 1);
            ru[i]++;
            for(int j = 0;j < g[i].size();j++)
                ru[g[i][j]]++;
        }
    }
}

int main()
{
    string str;
    bool flag = 0;
    while(getline(cin,str))
    {
        if(flag)
            printf("\n");
        memset(ru,0,sizeof(ru));
        memset(ans,0,sizeof(ans));
        mp1.erase(mp1.begin(),mp1.end());
        mp2.erase(mp2.begin(),mp2.end());
        for(int i = 1;i <= N;i++)
            g[i].clear();
        idx = 0;
        for(int i = 0;i < str.size();i++)
            if(str[i] >= 'a' && str[i] <= 'z')
            {
                num[++idx] = str[i];
            }
        sort(num + 1,num + 1 + idx);
        for(int i = 1;i <= idx;i++)
        {
            mp1[num[i]] = i;
            mp2[i] = num[i];
        }
        getline(cin,str);
        int a,b;
        for(int i = 0;i < str.size();i++)
        {
            if(str[i] >= 'a' && str[i] <= 'z')
            {
                if(i % 4 == 0)
                    a = mp1[str[i]];
                if(i % 4 == 2)
                {
                    b = mp1[str[i]];
                    g[a].push_back(b);
                    ru[b]++;
                }
            }
        }
        dfs(1);
        flag = 1;
    }
    return 0;
}
```
End.

---

## 作者：cly312 (赞：0)

考虑深搜和拓扑排序。从入度为零的节点开始，逐步添加到当前的排列结果中，并在每一步递减相邻节点的入度。如果某个节点的入度变为零，就递归地将其添加到当前排列中。一旦达到排列的叶节点，就存储起来，并按字典顺序排序。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

void readVar(map<char,string>&graph,map<char,int>&inedge,string&input);
void mr(map<char,string>&graph,map<char,int>&inedge,string&input);
void alltopsort(map<char,string>&graph,map<char,int>&inedge);
void gettopsort(map<char,string>&graph,map<char,int>inedge,map<char,bool>visited,char start,set<string>&topos,string result);

int main(){
	string input;
	bool new_line=false;
	while(getline(std::cin,input)){
		if(new_line)cout<<endl;
		new_line=1;
		map<char,string>graph;
		map<char,int>inedge;
		readVar(graph,inedge,input);
		getline(std::cin,input);
		mr(graph,inedge,input);
		alltopsort(graph,inedge);
	}
	return 0;
}
void readVar(map<char,string>&graph,map<char,int>&inedge,string&input){
	stringstream ss(input);
	char tmp;
	string str;
	while(ss>>tmp){
		graph[tmp]=str;
		inedge[tmp]=0;
	}
	return;
}
void mr(map<char,string>&graph,map<char,int>&inedge,string&input){
	stringstream ss(input);
	char tmp1,tmp2;
	while(ss>>tmp1){
		ss>>tmp2;
		graph[tmp1].push_back(tmp2);
		++inedge[tmp2];
	}
	return;
}

void alltopsort(map<char,string>&graph,map<char,int>&inedge){
	set<string>topos;
	map<char,bool>visited;
	for(auto a:inedge)
		visited[a.first]=false;

	for(auto a:inedge)
		if(a.second==0)
			gettopsort(graph,inedge,visited,a.first,topos,"");
	for(auto a:topos)
		cout<<a<<endl;
	return;
}
void gettopsort(map<char,string>&graph,map<char,int>inedge,map<char,bool>visited,char start,set<string>&topos,string result){
	result=result+start;
	visited[start]=true;
	for(auto a:graph[start])
		inedge[a]--;
	bool leaf=true;
	for(auto a:inedge)
		if(!visited[a.first]&&a.second==0){
			leaf=false;
			gettopsort(graph,inedge,visited,a.first,topos,result);
		}
	if(leaf) topos.insert(result);
	return;
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：
如果只需要输出一个**字典序最小**的**拓扑排序**，先考虑广搜实现，修改广搜代码，把普通队列改为**优先队列**。在优先队列中放进入度为 $0$ 的点，每次输出编号最小的节点，然后把它的后续节点的入度 $-1$，入度为 $0$ 的再放入队列。这样就能输出一个字典序最小的拓扑排序。


------------
本题需要输出**所有的排序**，用深搜更方便一些。把所有字母排序，每次深搜时，按字母顺序进行深搜，就能输出字典序。当深搜结束，就输出了所有的拓扑排序。

### 代码：
```
#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
typedef long long LL;
using namespace std;
		
int n,a[305],dir[305][305];					//dir[i][j] = 1 表示 i,j 是先后关系。
int topo[305],vis[305],indegree[305];		//topo[] 记录拓扑排序，indegree[] 记录入度，vis[] 标记是否访问
		
void dfs(int z,int cnt)
{
	int i;
	topo[cnt]=z;								//记录拓扑排序
	if(cnt==n-1)								//所有点取完了，输出一个拓扑排序
	{
		for(i=0;i<n;i++)
		{
			printf("%c",topo[i]+'a');
		}
		printf("\n");
		return ;
	}
	vis[z]=1;									//标记已访问
	for(i=0;i<n;i++)
	{
		if(!vis[a[i]] && dir[z][a[i]])
		{
			indegree[a[i]]--;					//把所有下属入度减1
		}
	}
	for(i=0;i<n;i++)
	{
		if(!indegree[a[i]] && !vis[a[i]])		//入读为0的继续取
		{
			dfs(a[i],cnt+1);
		}
	}
	for(i=0;i<n;i++)
	{
		if(!vis[a[i]] && dir[z][a[i]])
		{
			indegree[a[i]]++;
		}
	}
	vis[z]=0;									//恢复
}
		
signed main()
{
	char s[305];
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	int len;
	while(gets(s) != NULL)
	{
		memset(dir,0,sizeof(dir));
		memset(vis,0,sizeof(vis));
		memset(indegree,0,sizeof(indegree));
		len = strlen(s);
		n = 0;
		for(int i=0;i<len;i++)
			if(s[i]<='z' && s[i]>='a')
			{
				a[n++] = s[i] - 'a';
			}
			sort(a,a+n);						//对字母排序，这样就能够按字典序输出了
			gets(s);
			len = strlen(s);
			int first = 1;						//first = 1 表示当前字母是起点
			for(int i=0;i<len;i++)				//处理先后关系
			{
				int st,ed;
				if(first && s[i]<='z' && s[i]>='a')	//起点
				{
					first = 0;
					st = s[i] - 'a';			//把字母转换为数字
					continue;
				}
				if(!first && s[i]<='z' && s[i]>='a') //终点
				{
					first = 1;
					ed = s[i] - 'a';
					dir[st][ed] = 1;			//记录先后关系
					indegree[ed]++;				//记录入度，终点的入度加1
					continue;
				}
			}
			for(int i=0;i<n;i++)					//从所有入度为0的点开始
			{
				if(!indegree[a[i]])
				{
					dfs(a[i],0);
				}
			}
			printf("\n");
	}
	return 0;
}
/*
 */
		
		

```

---

## 作者：Jorisy (赞：0)

约束排列组合。

暴力 dfs 枚举所有可能的排列，然后判断是否满足约束要求即可。

注意多测清空，注意输出数据之间的空行，注意输出数据末尾没有空行，注意按字典序输出。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int n,a[15],g[305][305],c[305],d[305],f[305];

bool jd()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!g[a[i]][a[j]]) continue;
			if(d[a[i]]>d[a[j]]) return 0;//不满足约束要求
		}
	}
	return 1;
}

void dfs(int dep)
{
	if(dep>n)
	{
		if(!jd()) return;
		for(int i=1;i<=n;i++) cout<<(char)c[i];
		puts("");
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]) continue;
		f[i]=1;
		c[dep]=a[i];
		d[a[i]]=dep;
		dfs(dep+1);
		f[i]=0;
	}
}

int main()
{
	bool fl=0;
	while(getline(cin,s))
	{
		if(fl) puts("");//注意数据间的空行
		fl=1;
		memset(g,0,sizeof(g));
		memset(f,0,sizeof(f));//清空
		n=s.size()+1>>1;
		for(int i=1;i<=n;i++) a[i]=s[i-1<<1];
		sort(a+1,a+n+1);//按字典序
		getline(cin,s);
		for(int i=0;i<s.size();i+=4) g[s[i]][s[i+2]]=1;//记录约束条件
		dfs(1);
	}
 	return 0;
}
```

---

