# Bribing FIPA

## 题目描述

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。

# 题解

## 作者：MY_Lee (赞：4)

$\mathrm{Update\ on\ 2020/4/27}$：据说可爱的 $\LaTeX$ 炸了，然而我找不出来。如果您看到有 $\LaTeX$ 炸了请私信。现在先请右转[我的博客](https://moon-snow.blog.luogu.org/)罢。

### 闲聊

> 紫题思维不算非常可怕，毒瘤读入令人心态爆炸。

拿到题目我们一看，啊这是什么 dp 大水题，紫题是不是恶评？

然后看到输入格式：好吧，你赢了。

---
### 思路

思维真的不算难，撑死了蓝题罢。

我们一开题，学过 OI 的应该都知道，这是道 dp。再看，

> 已知不存在一个国家附属于多个国家，且附属关系之间不存在环。

这不就是棵树吗？这不就是道~~可爱的~~树形 dp 吗？

方程也不难罢，就是道树上背包的板子。

~~按套路~~设 $dp_{u,i}$ 表示以 $u$ 为根的子树中，至少“买通” $i$ 个国家的最小费用。

然后方程也是套路：

$$
dp_{u,i}=\min(dp_{u,i},dp_{u,k}+dp_{u,i-k})
$$

其中：

$$
1\le u\le n,0\le i\le size_u,0\le k\le i
$$

$size_u$ 表示 $u$ 的子树大小，可以在做 dp 的同时求。

另外：

$$
dp_{u,i}=\min(dp_{u,i},cost_u)
$$

其中:

$$
1\le u\le n,0\le i \le size_u
$$

那么我们要求的就是 $\min(dp_{1,m},dp_{1,m+1}\cdots dp_{1,n})$

还有初始化：

$$
dp_{u,0}=0,dp_{u,i}=\infty
$$

其中：

$$
1\le i\le size_u
$$

其他的细节还是看代码罢。

```cpp
//省去头文件 and 建图
inline void dfs(int now){//now 为上文的 u
    dp[now][0]=0;//初始化
    sz[now]=1;//sz 为上文的 size
    for(register int i=edge[now].head;i!=0;i=edge[i].nxt){
        int son=edge[i].to;
        dfs(son);
        sz[now]+=sz[son];//更新子树大小
        for(register int j=sz[now];j>=1;j--){
            for(register int k=min(j,sz[son]);k>=0;k--){
                dp[now][j]=min(dp[now][j],dp[now][j-k]+dp[son][k]);//做背包
			}
		}
    }
	for(register int i=0;i<=sz[now];i++){
		dp[now][i]=min(dp[now][i],cost[now]);
	}//表示直接收买 now 这个国家，其所有子树全部被收买了
}
```
---
### 读入(重点)

进入我们今天的重头戏——读入(毒瘤)。

真不知道出题人是有多毒瘤。

我第一次看到输入的时候，第一反应：

**字符串 hash**

很快我就发现：怎么做到不冲突呢？

$1s$ 后我知道了答案：~~我不知道~~

于是换思路。

---
### 读入正解

先来说一下我是怎么想到的。

有一天我水绿题的时候，我不会做 ~~(证明了我是个大菜鸡)~~，于是我看题解，发现了一个至关重要的英文单词和至关重要的一句话：

> 初学者可以认为 map 是一种下标可以为任意类型的数组。

不刚好能用到这题里吗？

我们定义一个下标为 string 类型，值为 int 类型的 map ，然后每输入一个国家名称，把他丢进 map 里，然后就能得到他的 int 映射，就可以做 dp 了。

但是问题仍然没有彻底解决。

以样例为例，我们构造出来的树不是一棵，而是若干棵，形成了森林，导致上面的 dp 不再适用。

不过我们仍然有办法，可以新建一个标号为 $0$ 的节点，然后把森林里所有的树根都连到这个节点。然后就从 $0$ 号节点 dp。

其他一些细节还是详见代码罢。

```cpp
#include<map>
map<string,int>mp;
//省略
string tmp[205];
		for(register int i=1;i<=n;i++){
			tmp[i]="";
			cin>>s;
			mp[s]=i;//进行映射，得到一个整数值
			scanf("%d",&cost[i]);
			char in=getchar();
			if(in==' '){//丢掉空格
				in=getchar();
			}
			while(in!='\n'&&in!='\r'){//一直读入，直到遇到换行，'\r' 是 Linux 系统下的换行，'\n' 是 Windows 系统下的换行。
				tmp[i]=tmp[i]+in;//合并字符串
				in=getchar();
			}
		}
		string name="";//表示附属国家名称
		for(register int i=1;i<=n;i++){
			for(register int j=0;j<tmp[i].size();j++){
				if(tmp[i][j]==' '){//空格表示一个附属国家已经描述完毕
					father[mp[name]]=i;//father 数组表示他的父亲节点
					add_edge(i,mp[name]);//连边
					name="";//清空名称
				}
				else{
					name=name+tmp[i][j];//否则合并名称
				}
			}
			if(name!=""){//如果还有未存储的附属国家
				father[mp[name]]=i;
				add_edge(i,mp[name]);
				name="";
			}
		}
		for(register int i=1;i<=n;i++){
			if(father[i]==0){
				add_edge(0,i);//如果父节点为 0，则与 0 连边。
			}
		}
```

---
### 番外
全部代码我就不放了啊。~~(不要问为什么，因为我懒)~~

这种读入比思维要难的题目还真不多$\cdots$

其实用 map 映射的题目还有一道好题叫 HDU Today。就是 map 映射套 Floyd 板子。但是洛谷没有，就放 vjudge 的链接罢。

[HDU Today](https://vjudge.net/problem/HDU-2112)

---

## 作者：Itst (赞：4)

### ~~蒟蒻又来水题解~~
### 题目就是一道01背包型树形DP，不熟的可以先去$luogu$题库做几道树形DP的基础题（[P2014 选课](https://www.luogu.org/problemnew/show/P2014)跟本题很像），具体来讲做法就是从叶子节点向根节点做01背包转移（一定要倒着转移），额外需要注意的是要将所有没有依赖的节点连向$0$号节点，将森林变成树，方便答案的统计。
### 那么为什么会刷到紫题难度？真相只有一个：
# 输入NB
### 那么接下来就是C艹党的福利：$stringstream$
### $stringstream$是一种特殊的输入输出流，使用方法类似于$cin$，可以进行输入的魔改，对$USACO$与$UVA$的奇葩输入有奇效
### 简述一下平常用于输入时$stringstream$的用法（以后或许会在自己的$blog$里详细谈到$stringstream$）：
```
#include<sstream>//stringstream需要的头文件（包含于万能头）
#include<cstring>
#include<iostream>
using namespace std;
int main(){
	stringstream ss;//定义
	string s;
    getline(cin,s);
    ss.clear();//清空字符串流，一般进行赋值操作的时候都需要使用以防出错
    ss.str(s);//将ss字符串流赋值为字符串s
    int N;
    double K;
    string Q;
    ss>>N>>K>>Q;//stringstream跟cin的用法和特性类似（读入string会在空格处停止）
    cout<<N<<' '<<K<<' '<<Q<<endl;
    return 0;
}
```
### 接下来是代码时间
```
#include<bits/stdc++.h>
using namespace std;

map < string , int > m;
//离散化用map是最不错的选择
queue < int > q;
int M , N , cntLSH , fa[201] , ans[201][201] , size[201] , pri[201] , in[201];

inline int getLSH(string s){
//获得离散化之后的序号
	if(!m.count(s)){
		m.insert(make_pair(s , ++cntLSH));
		return cntLSH;
	}
	else
		return m.find(s)->second;
}

int main(){
	stringstream ss;
	string s;
	while(getline(cin , s) && s[0] != '#'){
    //记得清空！
		memset(ans , 0x3f , sizeof(ans));
		memset(fa , 0 , sizeof(fa));
		memset(in , 0 , sizeof(in));
		memset(size , 0 , sizeof(size));
		cntLSH = ans[0][0] = 0;
		m.clear();
		ss.clear();
		ss.str(s);
		ss >> N >> M;
		in[0] = N;
        //所有无依赖点都要与0连边
		for(int i = 1 ; i <= N ; i++){
			ans[i][0] = 0;
			getline(cin , s);
			ss.clear();
			ss.str(s);
			ss >> s;
			int t = getLSH(s);
			ss >> pri[t];
			while(ss >> s){
				in[0]--;
				in[t]++;
				fa[getLSH(s)] = t;
			}
		}
		for(int i = 1 ; i <= N ; i++)
			if(!in[i]){
				q.push(i);
			}
		while(q.front()){
			int t = q.front();
			q.pop();
			if(!--in[fa[t]])
				q.push(fa[t]);
			ans[t][size[t]] = min(ans[t][++size[t]] , pri[t]);
            //注意这个转移只作用于size[t]
			for(int i = size[fa[t]] ; i >= 0 ; i--)
				for(int j = size[t] ; j ; j--)
                //01背包过程，不理解的可以手动模拟qwq
					ans[fa[t]][i + j] = min(ans[fa[t]][i + j] , ans[fa[t]][i] + ans[t][j]);
			size[fa[t]] += size[t];
		}
		q.pop();
		int all = 0x3f3f3f3f;
		for(int i = M ; i <= N ; i++)
			all = min(all , ans[0][i]);
            //大于等于M均可贡献答案
		cout << all << endl;
	}
	return 0;
}
/*
3 2
Aland 10
Boland 20 Aland
Coland 15
#
*/
```

---

## 作者：block_in_mc (赞：3)

## 解题思路

典型的树上 DP 题目。为了解决原图可能是森林的情况，建立代价为 $+\infty$ 的节点 $n+1$ 连接每棵树的根。用 $dp_{p,i}$ 代表从在以 $p$ 为根的子树中选择恰好 $i$ 个点的最小代价。状态转移方程如下：

- 不选择点 $p$，对于其子节点 $q$，枚举 $j$，在前面的子树中选择 $j$ 个点，在这个子树中选择 $i-j$ 个点。

$$dp_{p,i}=\mathop{\min}\limits_{j=0}^i(dp_{p,i},dp_{q,j}+dp_{p,i-j})$$

- 选择点 $p$，花费 $c_p$ 的代价，选择了点 $p$ 的子树大小 $sz_p$ 个点。

$$dp_{p,sz_p}=\min(dp_{p,sz_p},c_p)$$

对于第一种情况，类似于 01 背包，$i$ 要倒序枚举。

初始值为 $dp_{p,0}=0$，$dp_{p,i}=\inf$，答案即为 $\mathop{\min}\limits_{i=m}^ndp_i$。

## 进行输入

注意到本题十分离谱的输入格式，介绍 `stringstream`：

```cpp
stringstream ss;
ss << "10 8 str";
int n, m; string s;
ss >> n >> m >> s;
// n = 10, m = 8, s = "str"
```
这里我们使用 `getline` 读入每一行，将其转为 `stringstream` 后再使用类似于 `cin` 的格式输入，可以防止提前读入到下一行的数据。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300;
int n, m, r[N], cost[N], dp[N][N], sz[N];
string s, s1, s2;
vector<int> g[N];
vector<string> g2[N];
map<string, int> mp;
void dfs(int p) {
    dp[p][0] = 0, sz[p] = 1;
    for (int ed : g[p]) {
        dfs(ed);
        sz[p] += sz[ed];
        for (int i = sz[p]; i >= 1; i--) {
            for (int j = 0; j <= i; j++) {
                dp[p][i] = min(dp[p][i], dp[ed][j] + dp[p][i - j]);
            }
        }
    }
    dp[p][sz[p]] = min(dp[p][sz[p]], cost[p]);
}
int main() {
    while (true) {
        mp.clear();
        memset(dp, 0x3f, sizeof dp);
        memset(r, 0, sizeof r);
        for (int i = 0; i < N; i++) g[i].clear(), g2[i].clear();
        getline(cin, s);
        if (s == "#") break;
        stringstream ss1;
        ss1 << s;
        ss1 >> n >> m;
        for (int i = 1; i <= n; i++) {
            getline(cin, s);
            stringstream ss2;
            ss2 << s;
            ss2 >> s1 >> cost[i];
            mp[s1] = i;
            while (ss2 >> s2)
                g2[i].push_back(s2);
        }
        for (int i = 1; i <= n; i++) {
            for (string s3 : g2[i]) {
                g[i].push_back(mp[s3]);
                r[mp[s3]]++;
            }
        }
        for (int i = 1; i <= n; i++)
            if (r[i] == 0)
                g[n + 1].push_back(i);
        cost[n + 1] = 0x3f3f3f3f;
        dfs(n + 1);
        int ans = 0x3f3f3f3f;
        for (int i = m; i <= n; i++)
            ans = min(ans, dp[n + 1][i]);
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：andysk (赞：2)

[Vjudge](https://vjudge.net/problem/POJ-3345)

推荐先做[Luogu2014](https://www.luogu.org/problem/P2014)

[Blog](https://tony102.xyz/index.php/2019/11/01/poj3345-uva1222-bribing-fipa/)阅读效果更佳

背包类树形DP入门题，语言NOI题（~~输入就是傻逼~~）

考虑树形DP，设$f[u][i]$表示以$u$为根节点的子树，收买$i$个国家的最小代价。

根据题意，有些国家可能只是其他国家的老大，按照这个状态进行DP可以先建立一个$0$作为这个森林新树根，将原森林中每棵树的树根连到这个点上，就可以DP

转移很简单，写成公式太麻烦，详见代码



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 200 + 5;

int n, m;
int w[SIZE], fa[SIZE], s[SIZE], f[SIZE][SIZE];

std::map < string, int > serial;
std::vector < int > son[SIZE];

inline void DFS(int u)
{
    f[u][0] = 0, s[u] = 1;
    for (int i = 0; i < son[u].size(); i++) {
        int v = son[u][i];
        DFS(v);
        s[u] += s[v];
        for (int j = n; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                f[u][j] = std::min(f[u][j], f[u][j - k] + f[v][k]);
            }
        }
    }
    f[u][s[u]] = std::min(f[u][s[u]], w[u]);
    return;
}   

inline void init()
{
    for (int i = 0; i <= n; i++) son[i].clear();
    serial.clear();
    memset(fa, 0, sizeof(fa)); memset(w, 0, sizeof(w));
    memset(s, 0, sizeof(s)); memset(f, 0x3f, sizeof(f));
}

int main()
{
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    char in[SIZE];
    while (fgets(in, 200, stdin)) {
        if (in[0] == '#') break;
        sscanf(in, "%d%d", &n, &m);
        init();
        int cnt = 0, ans = 2e9;
        string str, s;
        for (int i = 1; i <= n; i++) {
            std::cin >> str;
            if (!serial.count(str)) serial[str] = ++cnt;
            scanf("%d", &w[serial[str]]);
            while (getchar() != '\n') {
                std::cin >> s;
                if (!serial.count(s)) serial[s] = ++cnt;
                son[serial[str]].push_back(serial[s]);
                fa[serial[s]] = 1;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!fa[i]) son[0].push_back(i);
        }
        w[0] = 2e9;
        DFS(0);
        for (int i = m; i <= n; i++) {
            ans = std::min(ans, f[0][i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```



---

## 作者：Uniecho1 (赞：2)

西班牙人可真是强大

真不知道他们是怎么想出如此鬼畜的输入的

思维难度大概就绿题水准

然而这读入难度......还真能直接追紫（可能这就是所谓的语言特性题吧）

上一波读入代码

```cpp
while(getline(cin,temp)) {//cin.getline:读一排（忽略空格）
	if(temp=="#")
		break;
	stringstream strin;
	strin<<temp;//可以这样初始化
	strin>>N>>M;//有点像sscanf，但是好写很多
	Init();
	for(int i=1,x; i<=N; i++) {
		cin>>temp;
		if(!Id[temp])
			Id[temp]=++tot;
		cin>>x;
		W[Id[temp]]=x;
		string tmp;
		getline(cin,tmp);
		stringstream strin;//注意我是开了个新的string流，如果不开要记得clear
		strin<<tmp;
		while(strin>>tmp) {//没错可以直接这样读，每有一个空格会断一次
			if(!Id[tmp])
				Id[tmp]=++tot;
			In[Id[tmp]]++;
			G[Id[temp]].push_back(Id[tmp]);
		}
	}
}
```

---

## 作者：pengyule (赞：1)

树形 DP 题。

对于每个节点，进行分组背包模板。唯一不同的是 $F_j$ 表示的是恰好装满此容量 $j$ 的背包的最小价值。注意倒叙枚举 $j$，循环嵌套顺序是 $i$（组）$j$（容积）$k$（组的每个物品）。状态转移方程：$F[step]_j=\min(F[step]_j,F[step]_{j-k}+F[son_{step}]_{j-k})$，这里 $F[step]$  代表的是节点 $step$ 的 $F$ 数组。请注意这里的体积是 $k$，代价是 $F[son_{step}]_{j-k}$ 。$k$ 枚举的是儿子的 $j$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,b[205],f[205][205],siz[205],fa[205];
string str[205];
vector<int> G[205];
map<string,int> trl;
void DP(int step){
	if(G[step].size()==0){
		f[step][1]=b[step];
		f[step][0]=0;
		siz[step]=1;
		return;
	}
	for(int i=0;i<G[step].size();i++){
		DP(G[step][i]);
		siz[step]+=siz[G[step][i]];
	}
	siz[step]++;
	f[step][0]=0;
	for(int i=0;i<G[step].size();i++)
		for(int j=n;j>=0;j--)
			for(int k=0;k<=j;k++)
				f[step][j]=min(f[step][j],f[step][j-k]+f[G[step][i]][k]);
	f[step][siz[step]]=min(f[step][siz[step]],b[step]);
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void unite(int x,int y){
	fa[find(x)]=find(y);
}
int main()
{
	while(cin>>n>>m){
		getchar();
		
		memset(b,0,sizeof(b));
		memset(siz,0,sizeof(siz));
		memset(fa,0,sizeof(fa));
		trl.clear();
		
		for(int i=1;i<=n;i++){
			G[i].clear();
			getline(cin,str[i]);
			string tmp="";
			for(int j=0;j<str[i].length() && str[i][j]!=' ';j++) tmp+=str[i][j];
			trl[tmp]=i;
		}G[n+1].clear();
		for(int i=1;i<=n+1;i++)fa[i]=i;
		for(int i=1;i<=n;i++){
			int j=0;
			string tmp="";
			for(;j<str[i].length() && str[i][j]!=' ';j++);
			for(j++;j<str[i].length() && str[i][j]>='0' && str[i][j]<='9';j++) b[i]=b[i]*10+str[i][j]-'0';
			for(j++;j<str[i].length();j++){
				if(str[i][j]==' '){
					G[i].push_back(trl[tmp]);
					unite(trl[tmp],i);
					tmp="";
					continue;
				}
				tmp+=str[i][j];
			}
			if(tmp!=""){
				G[i].push_back(trl[tmp]);
				unite(trl[tmp],i);
			}
		}
		set<int>s;for(int i=1;i<=n;i++)s.insert(find(i));
		for(set<int>::iterator it=s.begin();it!=s.end();it++) G[n+1].push_back(*it);
		memset(f,0x3f,sizeof(f));
		b[n+1]=0x3f3f3f3f;
		DP(n+1);
		int ans=0x3f3f3f3f;
		for(int i=m;i<=n;i++) ans=min(ans,f[n+1][i]);
		cout<<ans<<endl;
	}
	return 0;
} 
```
我因为没有 $G_{n+1}.clear()$ 而调了两小时，告诫大家！

---

## 作者：Erica_N_Contina (赞：0)

## 我的博客

本文知识点参考于：[oi-beats/树形 dp](https://ntsc-yrx.github.io/oi-beats/site/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E6%A0%91%E5%BD%A2DP/)，[个人博客](https://ntsc.flowus.cn/)。

## 知识点摘录

树形 DP

树形 DP（树形动态规划）是一种解决树形结构问题的动态规划方法。

树形 DP 可以解决很多树上的问题，如最大独立集、树形背包、最长路径等。掌握树形 DP 的关键在于正确地定义状态和写出状态转移方程。



## 做法

**输入**

本题的输入非常规，我的做法是一次读入一行，在行末添加结束标识，然后按空格和结束标识划分。

**树形 dp**

我们记 $f_{i,j}$ 为考虑子树 $i$ 内取 $j$ 个点的最小代价。$w_x$ 为选点 $x$ 的代价（钻石数量）。

转移有两个：

- 假设我们要求节点 $x$ 的 $f$ 数组，那么我们枚举 $x$ 的子节点 $v$，$f_{x,i}$ 中的第二维 $i$ 以及从 $v$ 中拿来的节点个数 $j$。于是有 $f_{x,i}=\min(f_{x,i},f_{x,i-j}+f_{v,j})$。注意这个转移的情况是**不选 $x$ 这个点**。

- 选 $x$ 这个点。这里就要体现题目的“附属”了。选了 $x$，那么只需要付出 $w_x$ 的代价，并且只可以选 $sz_x$ 个点（$sz$ 是子树大小）。于是有 $f_{x,sz_x}=\min(f_{x,sz_x},w_x)$。

 **特殊情况**

- 本题可能是森林，所以要建一个超级源点 $0$。

- 题目要求只要选的点 $\ge m$ 个即可，所以应该取 $f_{0,m}\sim f_{0,n}$ 的最小值。

- 枚举 $i,j$ 时要倒序，否则会多次选到 $v$ 子树内的点。



```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then MOD : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    if(ch=='#')exit(0);
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
        if(ch=='#')exit(0);

    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 2e2 + 5;
const int INF = 1e18;
const int M = 1e7;




int f[N][N];//在i子树中选j个带你的最小代价
int w[N];
int sz[N];
int n,m;
map<string,int> id;
string name[N];
vector<string> p[N];
vector<int> e[N];
int ind[N];


void dfs(int x,int fa){
    sz[x]=1;
    for(auto v:e[x]){
        if(v==fa)continue;
        dfs(v,x);
        sz[x]+=sz[v];
    }
}

void dfs2(int x,int fa){

    for(auto v:e[x]){
        if(v==fa)continue;
        dfs2(v,x);

        for(int i=min(n,sz[x]);i;i--){//倒序！！
            for(int j=min(i,sz[v]);j;j--){
                f[x][i]=min(f[x][i],f[x][i-j]+f[v][j]);//不选x
            }
        }
    }

    if(x)f[x][sz[x]]=min(f[x][sz[x]],w[x]);
}


void process(itn id,string s){
    string r="";
    int cnt=0;
    for(auto c:s){
        if(c==' '){
            if(!cnt)name[id]=r;
            else if(cnt==1){
                w[id]=atoi(r.c_str());
            }else p[id].pb(r);
            
            r="";
            cnt++;
        }
        else if(c=='$')return ;
        if(c!=' ')r=r+c;
    }
}


void init(){
    for(int i=0;i<=n;i++){
        sz[i]=0;
        while(e[i].size())e[i].pop_back();
        while(p[i].size())p[i].pop_back();
        ind[i]=0;
    }
}

void solve(){
    // string s;
    // getline(cin,s);
    // if(s[0]=='#')exit(0);

    // string r="";
    // for(auto c:s){
    //     if(c==' '){
    //         if(!n)n=atoi(r.c_str());
    //         else m=atoi(r.c_str());
    //         r="";
    //     }
    //     r=r+c;
    // }

    n=rd,m=rd;
    init();

    for(int i=1;i<=n;i++){
        // cin>>name[i];
        // w[i]=rd;
        string s;
        getline(cin,s);
        // cdbg(s);
        s=s+" $";
        process(i,s);
    }

    for(int i=1;i<=n;i++){
        id[name[i]]=i;
    }

    // cerr<<"\'"<<name[1]<<"\'";

    for(int i=1;i<=n;i++){
        for(auto t:p[i]){
            // cdbg(i,id[t],t);
            // cerr<<"\'"<<t<<"\'";
            e[i].pb(id[t]),ind[id[t]]++;}
    }


    for(int i=1;i<=n;i++){
        if(!ind[i])e[0].pb(i);
    }

    memset(f,0x3f3f,sizeof f);
    for(int i=0;i<=n;i++)f[i][0]=0;


    dfs(0,-1);
    dfs2(0,-1);

    // for(int i=1;i<=n;i++)cdbg(sz[i]);
    // cdbg(f[2][2],sz[0]);


    int ans=INF;
        // ans=min(ans,f[0][m]);
    for(int i=m;i<=n;i++)ans=min(ans,f[0][i]);
    cout<<ans<<endl;


}


signed main() {
    // freopen("suffix.in","r",stdin);
    // freopen("suffix.out","w",stdout);

    int T=1;
    int TT=0;
    while(T){
        // printf("Case %lld: ",++TT);
    	solve();
    }
    return 0;
}
```

---

## 作者：rainygame (赞：0)

这道题卡了一天左右吧，最后还是做出来了。

先从输入说起吧。本题有一种很好的输入方法，叫做 `stringstream`，就类似一个 `cin`。具体地，对于每一行，我们可以这样读入：

1. 先 `getline` 一个 `string`。
2. 再用 `stringstream scin(str)` 的形式声明 `stringstream`。
3. 然后就可以 `scin >> str` 已读入字符串了！

对于建图，我们可以用 `map` 对所有的字符串做一个映射，将其映射为一个从 $1$ 到 $n$ 的整数，以方便建图。

读入完之后，我们可以建立一个超级源点 $0$（记得清空！），收买它的代价为无穷大。这样就可以把一个森林变成一棵树了！

设 $f_{i,j}$ 为以 $i$ 为根的子树中收买 $j$ 个国家的代价最小值。那么边界条件为 $f_{i,0}=0$。注意因为是求最小值，所以需要把 $f_{i,j}(j \ne 0)$ 初始化为无穷大。

接下来进行树上背包，对于以 $u$ 为根的子树，转移 $i$ 个国家的支持，枚举 $u$ 的儿子 $v$ 获得 $j$ 个国家的支持。

$$
f_{u,i}=\min\limits_{j=siz_v}^0f_{u,i-j}+f_{v,j}
$$

（其中 $siz_v$ 表示以 $v$ 为根的子树大小）

因为收买 $u$ 就可以获得 $siz_u$ 个国家的支持，所以最后还需要更新：

$$
f_{u,siz_u}=\min\{f_{u,siz_u},a_u\}
$$

注意 $i,j$ 都需要倒序枚举，具体原因请自行思考。

注意答案不是 $f_{0,m}$，而是 $\min\limits_{i=m}^nf_{0,i}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 201
#define int long long

int n, m, ans;
int val[MAXN], siz[MAXN];
int f[MAXN][MAXN];
vector<int> e[MAXN];
map<string, int> mp;
pair<string, vector<string>> pr[MAXN];
string str;
bitset<MAXN> vis;

void clear(){  // 多测不清空，爆零两行泪 
	ans = LLONG_MAX;
	mp.clear();
	vis.reset();
	for (int i(0); i<=n; ++i){
		e[i].clear();
		pr[i].second.clear();
	}
	memset(f, 0x3f, sizeof(f));
}

void dfs(int x, int fa){
	siz[x] = 1;
	for (auto i: e[x]){
		if (i != fa){
			dfs(i, x);
			siz[x] += siz[i];
		}
	}
}

void dfs2(int x, int fa){
	f[x][0] = 0;
	for (auto v: e[x]){
		dfs2(v, x);
		for (int i(siz[x]); i>=1; --i){
			for (int j(min(i, siz[v])); j>=1; --j) f[x][i] = min(f[x][i], f[x][i-j]+f[v][j]);
		}
	}
	f[x][siz[x]] = min(f[x][siz[x]], val[x]);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    while (cin >> n >> m){
    	clear();
    	cin.ignore();
    	for (int i(1); i<=n; ++i){
    		getline(cin, str);
    		stringstream scin(str);
    		scin >> str >> val[i];
    		mp[str] = i;
    		pr[i].first = str;
    		while (scin >> str) pr[i].second.push_back(str);
		}
		
		for (int i(1); i<=n; ++i){
			for (auto j: pr[i].second){
				e[mp[pr[i].first]].push_back(mp[j]);
				vis.set(mp[j]);
			}
		}
		
		val[0] = LLONG_MAX;
		for (int i(1); i<=n; ++i){
			if (!vis.test(i)) e[0].push_back(i);
		}
		dfs(0, -1);
		dfs2(0, -1);
		
		for (int i(m); i<=n; ++i) ans = min(ans, f[0][i]);
		cout << ans << '\n';
	}

    return 0;
}
```


---

