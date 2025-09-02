# True Liars

## 题目描述

在小船上漂流了几天后，Akira Crusoe Maeda 终于被抛到了一个雾蒙蒙的岛上。尽管他疲惫不堪，绝望不已，但他仍然幸运地记得他童年时从族长那里听到的雾岛传说。这一定是传说中的岛屿。传说中有两个部落居住在岛上，一个是神圣的，另一个是邪恶的，一旦神圣部落的成员保佑你，你的未来就会光明有希望，你的灵魂最终会去天堂，相比之下，一旦邪恶部落的成员诅咒你，你们的未来就会黯淡无望，你的心灵最终会坠入地狱。

为了防止最坏的情况发生，Akira Crusoe Maeda 应该区分恶魔和神灵。但是怎么做？他们看起来完全一样，他无法仅凭外表区分他们。然而，他还有最后的希望。神圣部落的成员是说实话的人，也就是说，他们总是说实话，而邪恶部落的成员则是骗子，也就是他们总是撒谎。

他问他们中的一些人是否有些是神圣的。他们彼此非常了解，总是根据自己的个性“忠实地”回应他（即，他们总是说实话或撒谎）。他不敢问任何其他形式的问题，因为传说中，当一个恶魔成员不喜欢这个问题时，他会永远诅咒一个人。他有另一条有用的信息，传说告诉了两个部落的人口。传说中的这些数字是值得信赖的，因为生活在这个岛上的每个人都是不朽的，至少在这几千年里没有人出生过。

你是一名优秀的计算机程序员，因此被要求帮助 Akira 编写一个程序，根据居民对他的询问的回答对他们进行分类。

## 说明/提示

对于 $100\%$ 的数据，每个数据点内最多 10 组数据，$n<1000$，$p_1,p_2<300$，$1\le x_i, y_i \le p_1+p_2$。

## 样例 #1

### 输入

```
2 1 1
1 2 no
2 1 no
3 2 1
1 1 yes
2 2 yes
3 3 yes
2 2 1
1 2 yes
2 3 no
5 4 3
1 2 yes
1 3 no
4 5 yes
5 6 yes
6 7 no
0 0 0```

### 输出

```
no
no
1
2
end
3
4
5
6
end```

# 题解

## 作者：lym2022 (赞：14)

## 题目大意
现在有 $p1$ 个天神和 $p2$ 个恶魔，天使说真话，恶魔说假话，共有 $n$ 条信息，第 $i$ 条信息表示问编号为 $x_i$ 的人 $y_i$ 是否是天神，问全部的人中有几个是天神

### 思路
可以先从条件入手，当 $x_i$ 回答 yes 时，如果 $x_i$ 是神那么 $y_i$ 为神，如果 $x_i$ 是恶魔那么 $y_i$ 也为恶魔；当 $x_i$ 回答 no 时，如果 $x_i$ 是神那么 $y_i$ 为恶魔，如果 $x_i$ 是恶魔那么 $y_i$ 为神。

我们发现 $x_i$ 回答 yes 时 $x_i$ 和 $y_i$ 同族，反之异族，有种并查集得感觉。考虑用带权并查集（~~扩展域不好写~~）。

设数组 $v$ 表示节点 $i$ 和根节点的关系，如果 $v_i$ 为 $0$，表示 $i$ 和根节点同族，反之异族，这样设的好处在于可以用异或来更新 $i$ 的孩子与根节点的关系。

在输入时如果为 yes 那么两点同族，合并时传递一个值，表示是否相同，如果相同那么异或 $1$，否则异或 $0$。接着记录每个点所属的集合，每个集合中与根节点同族的节点数量和异族的节点数量。

由于我们确定的只是集合中各点与根的关系，因此并不能判断集合中与根同种的还是不同种的节点是神。所以我们可以进行背包 dp。$f[i][j]$ 表示已经从前 $i$ 个集合中选取了 $j$ 个人当神的方案数，然后看是否能凑出从前 $tot$ 个集合中凑出 $p1$ 个神就好了，由于他让判断接是否唯一，所以只要看 $f[tot][p1]$ 是否等于 $1$ 就好了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

bool flag = true;

int n,que,angel,demon,f[N][N],bel[N],sm[N][2],fa[N],tot;
 
//n为总共人数，que为条件数，angel为天神数，demon为恶魔数，f为dp数组，bel为节点所属集合，sm为与根节点的关系，第二维 0为相同，1为不同，fa为并查集数组，tot为集合数量 

bool vis[N][2],v[N];

//vis为第 i 个集合中与根节点相同的点选，还是与根节点不同的点选，v为与根节点得关系，0为同族，1为异族 

int find(int x) {              //查询根节点并更新关系 
	if(fa[x] != x) {
		int fax = fa[x];
		fa[x] = find(fa[x]);
		v[x] = v[x] ^ v[fax];
	}
	return fa[x];
}

void unionn(int x,int y,int t) {   //合并两个集合并重新确定关系 
	int xx = find(x);
	int yy = find(y);
	if(xx == yy) return;
	fa[xx] = yy;
	v[xx] = v[x] ^ v[y] ^ t;
}

void init() {                      //初始化 
	n = angel + demon,tot = 0;
	for(int i = 1;i<=n;i++) bel[i] = v[i] = 0;
	for(int i = 1;i<=n;i++) fa[i] = i;
	for(int i = 1;i<=n;i++) for(int j = 0;j<=1;j++) sm[i][j] = vis[i][j] = 0;
	for(int i = 1;i<=n;i++) for(int j = 1;j<=n;j++) f[i][j] = 0;
}

void solve() {
	cin >> que >> angel >> demon;
	if(que == 0 && angel == 0 && demon == 0) { 
		flag = false;
		return;
	}
	init();
	while(que--) {
		int x,y;
		string op;
		cin >> x >> y >> op;
		if(op == "yes") unionn(x,y,0);            //同族合并 
		else unionn(x,y,1);                       //异族合并 
	}
	for(int i = 1;i<=n;i++) if(find(i) == i) bel[i] = ++tot;        //如果自己为根节点，那么将自己所属的集合编号设为 ++tot (tot为已经存在集合数） 
	for(int i = 1;i<=n;i++) sm[bel[find(i)]][v[i]]++;               //传递 
	f[0][0] = 1;                       //一定要初始化！！！
	for(int i = 1;i<=tot;i++) {
		for(int j = 0;j<=angel;j++) {
			if(j >= sm[i][0]) f[i][j] += f[i-1][j-sm[i][0]];        //如果与根节点同族结点个数能放得下，那么累加方案 
			if(j >= sm[i][1]) f[i][j] += f[i-1][j-sm[i][1]];        //如果与根节点异族结点个数能放得下，那么累加方案 
		}
	}
	if(f[tot][angel] != 1) {         //如果最终的方案数不是 1，那么无解 
		cout << "no\n";
		return;
	}
	for(int i = tot;i>=1;i--) {
		if(f[i-1][angel-sm[i][0]] == 1) {   //f[tot][angel] 是由状态 f[tot-1][angel-cnt[i][0/1]]转来的，又由于 f[tot][angel] == 1，
			angel -= sm[i][0];              //也就是说 f[tot-1][angel-sm[i][0]]和 f[tot-1][angel-sm[i][1]] 中,一定是 一个所存方案书数为 1, 另一个所存方案数为 0,因为只有这样,才能保证 f[tot][angel] 等于 1。 
			vis[i][0] = true;               //如果 f[tot-1][angel-sm[i][0]] == 1,那么说明在集合 i 中我选的是与根节点同族的节点当作神;
		}else {                             //如果 f[tot-1][angel-sm[i][1]] == 1, 那么说明在集合 i 中我选的是与根节点【不同】的节点当作神。 
			angel -= sm[i][1];              //我们只需要用一个 vis[i][0/1] 数组记录,
			vis[i][1] = true;               //记录在集合 i 中我用的是哪个种类。 
		}
	}
	for(int i = 1;i<=n;i++) if(vis[bel[find(i)]][v[i]]) cout << i << '\n';          //每个节点所属的集合是否用的是与这个节点种类相同的节点，是就输出 
	cout << "end\n";             //不要忘了输出end 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	while(flag) solve();
	return 0;
}
```
这是本 xxs 的第二篇题解，不喜勿喷

---

## 作者：shinzanmono (赞：5)

[](看起来题解队列有点空，给各位志愿者上点压力/fendou。)

考虑一条消息，如果状态是 $1$，假设 $x$ 是好的，那么 $y$ 也是好的；$x$ 是坏的，那么 $y$ 也是坏的。同理考虑状态是 $0$，发现 $x$ 和 $y$ 的阵营相反，那么我们就可以把问题转化的简单一点了。

接下来考虑如何恰好地凑出 $p$ 和 $q$，发现可以跑一个背包，然后求凑出 $p$ 的方案数是否为 $1$ 即可，输出方案没啥难度。

```cpp
#include<iostream>
#include<algorithm>
#include<numeric>
using ll=long long;
const int sz=610;
const ll mod=1000000000000002493;
int a[sz<<1],b[sz<<1];
struct UFS{
  int fa[sz<<1];
  std::basic_string<int>point[sz<<1];
  void clear(int n){
    std::iota(fa+1,fa+n+1,1);
    for(int i=1;i<=n;i++)point[i].assign(1,i);
  }
  int find(int u){
    if(fa[u]==u)return u;
    return fa[u]=find(fa[u]);
  }
  void merge(int u,int v){
    int fu=find(u),fv=find(v);
    if(fu==fv)return;
    if(point[fu].size()>point[fv].size())std::swap(fu,fv);
    fa[fu]=fv,point[fv]+=point[fu],point[fu].clear();
  }
}ufs;
int f[sz][sz];
bool vis[sz];
std::basic_string<int>point[sz][2];
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n,m,p,q;
  while(std::cin>>m>>p>>q,n=p+q){
    ufs.clear(n*2);
    std::fill(a+1,a+n+1,1);
    std::fill(a+n+1,a+2*n+1,0);
    std::fill(b+1,b+n+1,0);
    std::fill(b+n+1,b+2*n+1,1);
    for(int i=1,u,v;i<=m;i++){
      std::string s;
      std::cin>>u>>v>>s;
      if(s=="yes")ufs.merge(u,v),ufs.merge(u+n,v+n);
      else ufs.merge(u+n,v),ufs.merge(u,v+n);
    }
    f[0][0]=1;
    std::fill(vis+1,vis+n+1,0);
    bool flag=false;
    int N=0;
    for(int i=1;i<=n*2&&!flag;i++)[&]{
      if(ufs.find(i)!=i)return;
      for(int u:ufs.point[i]){
        int p=u>n?u-n:u;
        if(vis[p])return;
        vis[p]=true;
      }
      ++N,std::fill(f[N],f[N]+n+1,0);
      point[N][0].clear(),point[N][1].clear();
      for(int u:ufs.point[i])point[N][u>n]+=u>n?u-n:u;
      int a=point[N][0].size(),b=point[N][1].size();
      for(int j=n;j>=0;j--){
        f[N][j]=f[N-1][j];
        if(j>=a)f[N][j]=(f[N][j]+f[N-1][j-a]);
        if(j>=b)f[N][j]=(f[N][j]+f[N-1][j-b]);
      }
    }();
    if(flag||f[N][p]!=1){
      std::cout<<"no\n";
      continue;
    }
    int cur=p;
    std::basic_string<int>ans;
    for(int i=N;i>=1;i--){
      if(f[i-1][cur]==1)continue;
      int a=point[i][0].size(),b=point[i][1].size();
      if(f[i-1][cur-a]==1)cur-=a,ans+=point[i][0];
      else cur-=b,ans+=point[i][1];
    }
    std::sort(ans.begin(),ans.end());
    for(int x:ans)std::cout<<x<<"\n";
    std::cout<<"end\n";
  }
  return 0;
}
```

---

## 作者：yuantc (赞：3)

题目大意：

有 $p1$ 个好人，$p2$ 个坏人，好人只说真话，坏人只说假话。

首先，我们发现：

* 如果 A 说 B 是好人，那么 A 和 B 是同一类人。
* 否则 A 和 B 不是同一类人。

利用这个性质，用并查集维护这些人之间的关系。

### 于是

问题就转化成了有 $cnt$ 个集合，每个集合里包含两类人，我们在每个集合里选出一类人，使得最后共有 $P1$ 个人。

由于最后要输出哪些是好人，因此，只需判断方案是否唯一，沿着 $dp$ 数组递推即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1010
#define MAX 610

int i,j,n,p1,p2,tot,now,x,y;
int a[MAXN],b[MAXN],fa[MAX],d[MAX],ID[MAX];
char k[MAXN][5];
int dp[MAX][MAX];
vector<int> ans;
vector<int> p[MAX][2];

int find(int x) 
{ 
    if (fa[x]==x) return x; 
    int f=find(fa[x]);
	d[x]=d[x]^=d[fa[x]]; 
	return fa[x]=f; 
}

int main()
{
    
    while (scanf("%d%d%d",&n,&p1,&p2) != EOF && (n || p1 || p2))
    {
        for (i=1;i<=n;i++) scanf("%d%d%s",&a[i],&b[i],&k[i]);
        for (i=1;i<=p1+p2;i++) 
        {
            fa[i]=i;
            d[i]=0;
        }
        for (i=1;i<=n;i++)
        {
            x=find(a[i]);
            y=find(b[i]);
            if(strcmp(k[i],"yes")==0)    
            {
                fa[x]=y;
                d[x]=d[a[i]]^d[b[i]];
            }
			else
            {
                fa[x]=y;
                d[x]=d[a[i]]^d[b[i]]^1;
            }    
        }
        tot=0;
        memset(ID,0,sizeof(ID));
        for(i=1;i<=p1+p2;i++)     
        {
            p[i][0].clear();
            p[i][1].clear();
        }
        for(i=1;i<=p1+p2;i++)
        {
            x=find(i);
            if (!ID[x]) ID[x]=++tot;
            p[ID[x]][d[i]].push_back(i);
        }
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(i=1;i<=tot;i++)
        {
            for(j=0;j<=p1+p2;j++)
            {
                if(j-p[i][0].size()>= 0) dp[i][j]+=dp[i-1][j-p[i][0].size()];
                if(j-p[i][1].size()>= 0) dp[i][j]+=dp[i-1][j-p[i][1].size()];
            }
        }
        if(dp[tot][p1]==1)
        {
            ans.clear();
            now=p1;
            for(i=tot;i>=1;i--)
            {
                if(now-p[i][0].size()>=0 && dp[i-1][now-p[i][0].size()])
                {
                    for (j=0;j<p[i][0].size();j++)
                    {
                    	    ans.push_back(p[i][0][j]);
					}
                    now-=p[i][0].size();
                }
				else
                {
                    for(j=0;j<p[i][1].size();j++)
                    {
                    	ans.push_back(p[i][1][j]);
					}
                    now-=p[i][1].size();
                }
            }
            sort(ans.begin(),ans.end());
            for(i=0;i<ans.size();i++) printf("%d\n",ans[i]);
            printf("end\n");
        }
		else
		{
			printf("no\n");
		}
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

### 题意：

给出 $p1$ 个好人，$p2$ 个坏人，这里面好人只说真话，坏人只说假话。

然后会有回答 $x$，$y$ `yes` 或 `no`，代表的意思是 $x$ 说 $y$ 是好人/坏人。

最后就问你能否通过这些回答判断出哪些是好人（个数等于 $p1$）并且输出。

### 题解：

这题我当时只是把思路想出来了，最后代码的实现并没有独立完成，主要是代码的后半部分...

我们先分析题目，假定 $x$ 说 $y$ 是好人，那么现在  $x$ 有两种情况（好/坏），根据这两种情况也可以确定出 $y$ 的好坏；同理，如果 $x$ 说 $y$ 是坏人，也有两种情况。通过对这两种情况的分析，我们会发现，当 $x$ 说 $y$ 是好人是，他们是同类的；当 $x$ 说 $y$ 是坏人时，他们不是同类的。

根据这个我们可以想到带权的并查集，用数组 $v_x$ 代表 $x$ 与其父节点的关系，当 $v_x$ 为 $0$ 时 $x$ 与其父亲同类，为 $1$ 时不同类。由于这是一个环状的关系，所以会模 $2$。

假定我们已经分好了类，那么就会有 $n$ 个集合，每个集合有与父节点同类的，也有不同类的。

如果我们现在要确定出好人的数量，那么在每个集合里面只能选一种，这时就用 dp 来处理：设 $dp_{i,j}$ 的含义是处理到第 $i$ 个集合时，和为 $j$ 的方案总数。

那么初始化 $dp_{0,0}=1$，动态转移方程为 $dp_{i,j}=dp_{i,j}+dp_{i-1,j-k0,k1}$，$k0$，$k1$ 为 $i$ 集合中的两类的数量。

最后输出路径的时候有许多种方法，有兴趣的可以看下其它的代码~

最后注意，如果 $p1$ 等于 $0$，也会输出一个 `end`。我就是在这里被坑了好久。
### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1505 ;    
int n,p1,p2,cnt;
int f[N],dp[N][N],v[N],g[N],set[N][5];

int find(int x){
    if(f[x]==x) return x;
    int tmp = f[x];
    f[x]=find(f[x]);
    v[x]=(v[x]+v[tmp])%2;
    return f[x];
}

int main(){
    while(~scanf("%d%d%d",&n,&p1,&p2)){
        if(!n && !p1 &&!p2) break;
        cnt = 0;memset(set,0,sizeof(set));memset(dp,0,sizeof(dp)); 
        memset(f,-1,sizeof(f));
        for(int i=1;i<=p1+p2;i++) f[i]=i,v[i]=0;
        char s[10];int x,y;
        for(int k=1;k<=n;k++){
            scanf("%d%d %s",&x,&y,s);
            int fx=find(x),fy=find(y);
            if(fx==fy) continue ;
            f[fx]=fy;
            if(s[0]=='y') v[fx]=(v[x]+v[y])%2;
            else v[fx]=(v[x]+v[y]+1)%2;
        }
        for(int i=1;i<=p1+p2;i++){
            if(find(i)==i) g[i]=++cnt;
        }
        for(int i=1;i<=p1+p2;i++) set[g[find(i)]][v[i]]++;//set数组记录第几组两类的个数 
        dp[0][0]=1;//dp[i,j]前i个集合，和为j的情况数量 
        for(int i=1;i<=cnt;i++){
            for(int j=0;j<=p1;j++){  //注意p1等于0的情况 
                if(j>=set[i][0]) dp[i][j]+=dp[i-1][j-set[i][0]]; 
                if(j>=set[i][1]) dp[i][j]+=dp[i-1][j-set[i][1]];
            }
        } 
        int tmp = p1;
        int choose[N];
        memset(choose,-1,sizeof(choose));
        if(dp[cnt][p1]==1){
            for(int i=cnt;i>=1;i--){
                if(dp[i-1][tmp-set[i][0]]==dp[i][tmp]){
                    choose[i]=0;
                    tmp-=set[i][0];
                }else if(dp[i-1][tmp-set[i][1]]==dp[i][tmp]){
                    choose[i]=1;
                    tmp-=set[i][1];
                }
            }
            for(int i=1;i<=p1+p2;i++){
                if(choose[g[find(i)]]==v[i]) printf("%d\n",i);
            }
            puts("end");
        }else puts("no");
    }
    return 0;
}
```

---

## 作者：zzx11211_floyd (赞：1)

# 题目大意：

小A问 $N$ 个人另一个人是否是 angels ，对于 angels （天使），他会回答真话，对于 demons （恶魔），它会回答假话。

# 思路：
首先，我们可以看出这是个并查集（~~标签都说了~~）。因为他让我们给人分类，并且给出了一些人之间的关系。  
易知，当一个人说另一个人是 angels 时，他们一定是同类。（因为 angels 一定说真话，所以那个人一定是 angels。demons 一定说假话，它说另一个人是 angels，则另一个必然是 demons，也就是它们是同类）。同理可知，当一个人说另一个人是 demons 时，他们一定是异类。一个人说自己是什么人没有意义（因为 angle 一定说自己是 angle (真话)，demon 一定说自己是 angle (假话)），可以直接跳过。   
我们用一个权值并查集来维护关系（~~种类并查集太玄学了~~）。因为只有两类人（ angels 和 demons ），所以种类转化为 $jl[i][j]=(jl[i][k]+jl[k][j])\bmod2$ 。  
在合并完并查集之后，他变成了一个森林。我们把森林里每棵树的两类人数统计出来，然后通过01背包求解。每扫到一项有两种选择：相信包含根节点的一组和不包含的一组。用一个 $GG_{i,j}$ 来储存第 $i$ 项共 $j$ 人时的选择。最后根据 $GG$ 储存的结果排序，输出。

# 示例代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
struct UnionFindSet{
private:
	vector<int> fa;//存储每棵树的上级 。
	vector<queue<int>> Set;
	vector<queue<int>> Set2;
	vector<int> jl;//存储每个节点与其上级的关系 。
public:
	UnionFindSet(int n){//初始化 。
		fa.resize(n+1005);
		Set.resize(n+1005);
		Set2.resize(n+1005);
		jl.resize(n+1005); 
		for(int i=1;i<=n;i++){
			fa[i]=i;
			jl[i]=0;
		}
	}
	pair<int,int> Find(int x){//距离压缩，可以大幅提升运行效率 。
		if(fa[x]==x){
			return {x,0};
		}
		pair<int,int> P1=Find(fa[x]);
		fa[x]=P1.first;
		jl[x]=(P1.second+jl[x])%2;//更新距离 。
		return {P1.first,jl[x]};
	}
	void Union(int x,int y,bool ri){
		pair<int,int> px=Find(x);
		pair<int,int> py=Find(y);
		if(Find(x).first==Find(y).first) return;//如果为同一类，不再合并 。
		fa[py.first]=px.first;
		if(ri){
			jl[py.first]=!(jl[x]==jl[y]);//同类情况 。
		}
		else{
			jl[py.first]=!(jl[x]==jl[y])+1;//异类情况 。
		}
		jl[py.first]%=2;
	}
	int onot(int x[],int y[],queue<int> qq[],queue<int> qq2[],int n){
		//数组传参为传入一个地址，或者说数组本身就是一个指针。因此在函数中修改数组内容会影响原数组 。
		for(int i=1;i<=n;i++){
			if(Find(i).second==0){
				Set[Find(i).first].push(i);//与根节点同类的 。
			}
			else{
				Set2[Find(i).first].push(i);//与根节点异类的 。
			}
		}
		int cnt=1;
		for(int i=1;i<=n;i++){
			if(Find(i).first==i){//判断是否为根节点 。
				int g=Set[Find(i).first].size(),b=Set2[Find(i).first].size();
				x[cnt]=g;//存储同类的数字进代价数组 。
				y[cnt]=b;//存储异类的数字进代价数组 。
				qq[cnt]=Set[Find(i).first];//存储第 cnt 项的数字（同类） 。
				qq2[cnt]=Set2[Find(i).first];//存储第 cnt 项的数字（异类）。
				cnt++;
			}
		}
		return cnt-1;//返回总项数 。
	}
};
int in1,in2;
string in3;
int g[2005],b[2005];//存储每一项相信不同组的人数 。
int dp[2005];//存储 angels 人数 。
bool ge[1005][305];//储存第 I 组第 V 项时是选择相信那一组？ 
bool can[1005];// V 个 angels 是否可以组成 。
int locker(){//每一组数据调用一次 。
	memset(g,0,sizeof g);
	memset(b,0,sizeof b);
	memset(dp,0,sizeof dp);
	memset(ge,false,sizeof ge);
	memset(can,false,sizeof can);
	queue<int> qq[10005];
	queue<int> qq2[10005];//初始化。
	int n,G,B;
	cin>>n>>G>>B;
	if(n==0 and G==0 and B==0){
		return 0;//程序结束 。
	}
	UnionFindSet unionFindSet=UnionFindSet(G+B);//初始化并查集 。
	for(int i=1;i<=n;i++){
		cin>>in1>>in2>>in3;
		if(in1==in2) continue;
		unionFindSet.Union(in1,in2,in3=="yes");//通过关系链接人 。
	}
	if(G==B){
		cout<<"no\n";//如果 angels 与 demons 总人数相同，无法判断某人是否是 angels ，因此输出 "no"  。
		return 1;
	}
	
	if(n==0){
		if(B>0 and G>0){
			cout<<"no\n";//没有询问，无法判断 。
			return 1;
		}
		if(B==0){
			for(int i=1;i<=G;i++){//但如果只有angels，那么可以确定。） 
				cout<<i<<'\n';
			}
		}
		cout<<"end\n";
		return 1;
	}
	n=unionFindSet.onot(g,b,qq,qq2,G+B);//初始化代价数组。
	for(int i=1;i<=n;i++){
		if(g[i]==b[i]){//如果人数相等，无法判断这一批人是否是 angels，因此输出 no。
			cout<<"no\n";
			return 1;
		}
		for(int V=G;V>=0;V--){//01背包改编代码。 
			if(V<g[i] and V<b[i]){
				can[V]=true;
				continue;
			}
			if(V<g[i]){
				if(can[V-b[i]]){
					can[V]=true;
					continue;
				}
				ge[i][V]=false;//选择不包含根节点的。
				dp[V]=dp[V-b[i]]+b[i];
				can[V]=false;
				continue;
			}
			if(V<b[i]){
				if(can[V-g[i]]){
					can[V]=true;
					continue;
				}
				ge[i][V]=true;//选择包含根节点的。 
				dp[V]=dp[V-g[i]]+g[i];
				can[V]=false;
				continue;
			}
			if(can[V-b[i]] and can[V-g[i]]){
				can[V]=true;
				continue;
			}
			if(can[V-b[i]]){
				can[V]=false;
				ge[i][V]=true;
				dp[V]=dp[V-g[i]]+g[i];
				continue;
			}
			if(can[V-g[i]]){
				can[V]=false;
				ge[i][V]=false;
				dp[V]=dp[V-b[i]]+b[i];
				continue;
			}
			if(dp[V-g[i]]+g[i]>dp[V-b[i]]+b[i]){
				can[V]=false;
				ge[i][V]=true;
				dp[V]=dp[V-g[i]]+g[i];
			}
			else{
				can[V]=false;
				ge[i][V]=false;
				dp[V]=dp[V-b[i]]+b[i];
			}
		}
	}
	int GG=G;
	int sum=0;
	priority_queue<int,vector<int>,greater<int> > st;//优先队列维护输出顺序 。
	for(int i=n;i>=1;i--){
		if(ge[i][GG]){//相信根节点所在的组。 
			GG-=qq[i].size();
			while(!qq[i].empty()){
				st.push(qq[i].front());
				qq[i].pop();
			}
			
		}
		else{//相信非根节点所在的组 。
			GG-=qq2[i].size();
			while(!qq2[i].empty()){
				st.push(qq2[i].front());
				qq2[i].pop();
			}
			
		}
	}
	while(!st.empty()){
		cout<<st.top()<<'\n';//输出 。
		st.pop();
	}
	cout<<"end\n";
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	while(locker());
	return 0;
}
~~~
有没有神犇能把这代码再简化一下，本蒟蒻写的太长了。

---

## 作者：Tenil (赞：1)

# Solution

这里是博客：[Tenil](https://www.cnblogs.com/Tenil/p/18864567)，有更好的看题体验哦~

## 题意
[原题链接](https://www.luogu.com.cn/problem/P10687)

岛上有 $p_1$ 个好人和 $p_2$ 个坏人按 $1$ 到 $p_1 + p_2$ 编号，好人说真话，坏人说谎话。现在有 $n$ 条信息表示 $x$ 说 $y$ 是（$\texttt{yes}$）不是（$\texttt{no}$）好人，问：是否能确定所有好人。

多测，$T \le 10$，$n \le 1000$，$p_1,p_2 \le 300$。

## 分析

对每条信息，我们先考虑：

1. 如果 $x$ 是好人，他说 $\texttt{yes}$ 则 $y$ 也为好人，否则 $y$ 为坏人；
2. 如果 $x$ 是坏人，他说 $\texttt{yes}$ 则 $y$ 也为坏人，否则 $y$ 为好人；

于是得出：若信息为 $\texttt{yes}$，则 $x$ 与 $y$ 定同为一类人，反之。自然想到并查集。因为要维护是否为同一类人，可以使用带权并查集或拓展域并查集，这里本蒟蒻使用的是拓展域并查集。对此不清楚的可以去 [P2024 食物链](https://www.luogu.com.cn/problem/P2024)。

现在考虑如何具体确定好人。

其实我们只需考虑好人能否是“唯一”的，也即拼出 $p_1$ 个人的方案是否唯一。可以直接背包 dp：$dp(i,j)$ 表示前 $i$ 个集合中选 $j$ 个好人的方案数。但是这样有一个小问题：“前 $i$ 个集合中”可能有一些集合是确定不能合并的。比如：有信息 $1$ $2$ $\texttt{no}$ 的情况下，$1$，$2$ 所在集合不能同时选中，所以我们加一维：$dp(i,j,c)$ 表示前 $i$ 个集合中选 $j$ 个好人，$c=1$ 表示当前集合选择，反之，的方案数。

状态转移方程：

$$
dp(i,j,1) = \begin{cases}
  0 & j<\operatorname{card}(S_{i-1})\\
  dp(i-1,j-\operatorname{card}(S_{i-1}),0) & j \ge\operatorname{card}(S_{i-1}) \text{且} S_i \text{与} S_{i-1} \texttt{不可同时选中}\\
  dp(i-1,j-\operatorname{card}(S_{i-1}),0)+dp(i-1,j-\operatorname{card}(S_{i-1}),1) & j \ge\operatorname{card}(S_{i-1}) \text{且} S_i \text{与} S_{i-1}\texttt{可同时选中}
\end{cases}
$$

$$
dp(i,j,0) = dp(i-1,j,0)+dp(i-1,j,1
)$$

最后，如果 $dp(cnt,p_1,1)+dp(cnt,p_1,0)=1$，则可以确定，再逆向转移一遍，标记答案，输出即可。

## 实现

1. 维护一个 $2$ 倍拓展域并查集；
2. 把分好的集合“离散化”，跑背包 dp。

## Code


```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

inline ll fr() {
	ll x=0,f=1;char c=getchar();
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}

const int maxn=6.6e2;

int n,p1,p2;

int g[maxn],card[maxn],gf[maxn];
//g：离散化后的集合编号
//gf：从离散化后编号到原集合的映射
bool vis[maxn],ans[maxn];
int dp[maxn][maxn][2];

int f[maxn*2];

int getf(int x) {return x==f[x]?f[x]:f[x]=getf(f[x]);}

inline void merge(int x,int y) {f[getf(y)]=getf(x);}

int main() {
	while(1) {
		n=fr();p1=fr();p2=fr();
		if(!n&&!p1&&!p2) break;
		int N=p1+p2,cnt=0;
		memset(vis,0,sizeof(vis));
		memset(ans,0,sizeof(ans));
		memset(card,0,sizeof(card));
		memset(g,0,sizeof(g));
		memset(gf,0,sizeof(gf));
		memset(dp,0,sizeof(dp));//多测不清空，。。。。
		for(register int i = 1; i <= 2*N; i++) f[i]=i;
		for(register int i = 1; i <= n; i++) {
			int x=fr(),y=fr();
			char ans='#';
			while(!(ans=='n'||ans=='y')) ans=getchar();//避免读到神秘的东西
			switch (ans) {
				case 'n':
					merge(x,y+N);
					merge(y,x+N);
					break;
				case 'y':
					merge(x,y);
					merge(x+N,y+N);
					break;
			}
		}
		for(register int i = 1; i <= N; i++) {
			if(!vis[getf(i)]) {
				vis[getf(i)]=1;
				g[getf(i)]=++cnt;
				card[cnt]++;
				gf[cnt]=getf(i);
			}
			else card[g[getf(i)]]++;
		}
		dp[0][0][0]=1;//一定要记得初始化！！！
		for(register int i = 1; i <= cnt; i++) {
			for(register int j = 0; j <= N; j++) {
				dp[i][j][0]=dp[i-1][j][0]+dp[i-1][j][1];
				if(j>=card[i]) {
					dp[i][j][1]=dp[i-1][j-card[i]][0];
					if(getf(gf[i])!=getf(gf[i-1]+N)) {//判断两集合是否可以同时选中
						dp[i][j][1]+=dp[i-1][j-card[i]][1];
					}
				}
			}
		}
		if(dp[cnt][p1][0]+dp[cnt][p1][1]!=1) printf("no\n");
		else {
			int now=p1;
			for(register int i = cnt; i; i--) {//反着跑一遍，标记
				if(dp[i-1][now][0]==0) {
					now-=card[i];ans[i]=1;
				}
			}
			for(register int i = 1; i <= N; i++) {
				if(ans[getf(i)]) printf("%d\n",i);
			}
			printf("end\n");
		}
	}
	return 0;
}
```
## 闲话

如果觉得有用，点个赞吧！

---

## 作者：Toorean (赞：0)

$p$ 个好人，$q$ 个坏人。好人只说真话，坏人只说假话。给出 $n$ 句话，求是否能确定好人的集合。

我们先考虑每句话意味着什么。
- 若这句话为 `yes`：假设 $x$ 为好人，那么 $y$ 为好人，$x$ 与 $y$ 同族；假设 $x$ 为坏人，那么 $y$ 为坏人，$x$ 与 $y$ 同族。
- 若这句话为 `no`：假设 $x$ 为好人，那么 $y$ 为坏人，$x$ 与 $y$ 异族；假设 $x$ 为坏人，那么 $y$ 为好人，$x$ 与 $y$ 异族。

综上，对于 `x y yes` 这句话，我们可以得到 $x$ 与 $y$ **同族**；对于 `x y no` 这句话，我们可以得到 $x$ 与 $y$ **异族**。由于数据保证不发生冲突，我们只需按照所说的话合并集合即可。

可以采用边带权并查集或者扩展域并查集的方式。这里采用扩展域并查集。

具体的，我们开两倍大小并查集。若 $x$ 与 $y$ 同族，我们合并 $(x,y)$ 以及 $(x+N,y+N)$；反之，我们合并 $(x,y+N)$ 以及 $(x+N,y)$。

接下来，我们继续考虑“确定”的意思。换句话说，也就是在 $p+q$ 个人中是否能**唯一**选择 $p$ 个人为好人，也就是说选 $p$ 个人的方案数只有一个。

考虑 01 背包。设 $f(i,j,0/1)$ 表示前 $i$ 个集合，选了 $j$ 个人，第 $i$ 个集合不选/选的方案数。假设前面 $n$ 句话将所有人划分成了 $cnt$ 个集合。当且仅当 $f(cnt,p,0)+f(cnt,p,1)=1$ 时方案唯一确定。

```cpp
int find (int x) { return fa[x] == x ? x : fa[x] = find (fa[x]); }
void unite (int x, int y) { x = find (x), y = find (y); if (x == y) return; fa[max (x, y)] = min (x, y);}

void work () {
    if (!n && !p && !q) break;
    vector <quest> Q;
    int m = n, n = p + q;
    for (int i = 1; i <= n * 2; i ++) fa[i] = i;
    for (int i = 1; i <= m; i ++) {
        int x, y; char opt[10];
        scanf ("%d%d%s", &x, &y, opt + 1);
        if (opt[1] == 'y') unite (x, y), unite (x + n, y + n);
        else               unite (x, y + n), unite (x + n, y);
    } 

    vector <int> ss[MAXN];
    int cnt = 0;
    for (int i = 1; i <= n; i ++) if (fa[i] == i) ++ cnt, cor[i] = cnt;
    for (int i = 1; i <= n; i ++) ss[ cor[find (i)] ].push_back (i);

    memset (f, 0, sizeof f); f[0][0][0] = 1;
    for (int i = 1; i <= cnt; i ++) {
        for (int j = 0; j <= n; j ++) {
            f[i][j][0] = f[i - 1][j][0] + f[i - 1][j][1];
            if (j >= ss[i].size ()) {
                f[i][j][1] = f[i - 1][j - ss[i].size ()][0];
                if (i != 1 && find (ss[i][0]) != find (ss[i - 1][0] + n))
                    f[i][j][1] += f[i - 1][j - ss[i].size ()][1];
            }
        }
    }


    if (f[cnt][p][0] + f[cnt][p][1] != 1) { puts ("no"); continue;}
    else {
        vector <int> ans;
        int now = cnt, cur = f[cnt][p][1];
        while (now) {
            if (cur) {for (auto v : ss[now]) ans.push_back (v); p -= ss[now].size ();}
            now --;
            cur = f[now][p][1];
        }
        sort (ans.begin (), ans.end ());
        for (auto v : ans) printf ("%d\n", v);
        puts ("end");
    }
}
```

---

## 作者：_zuoqingyuan (赞：0)

假设问 $x$ 关于 $y$ 是否是天使。

1. $x,y$ 均是天使，$x$ 会说实话，$y$ 是天使。

2. $x$ 是天使，$y$ 是恶魔，$x$ 会说实话，$y$ 不是天使。

3. $x$ 是恶魔，$y$ 是天使，$x$ 会说谎话，$y$ 不是天使。

4. $x,y$ 均是恶魔，$x$ 会说谎话，$y$ 是天使。

虽然无法直接通过询问确定一个人是天使与恶魔，不过可以发现，若回答 `no`，则两人身份一定不同；若回答 `yes`，则两人身份一定相同。

一个人不是天使就是恶魔，考虑建图；如果两个人身份不同，就连一条边权为 $1$ 的边，反之则连边权为 $0$ 的边。然后二分图染色，确定黑点和白点。

二分图可能不连通，我们接下来要确定的是否存在唯一方案，我们在每个二分图中只取黑点或白点，使得取出来的数量为 $p1$，且这么取方案数唯一。

这个问题直接背包就行，同时用辅助数组记录决策转移，最后输出方案。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
const int N=6050;
int n,p1,p2,tot,col[N],m,f[N][N],g[N][N];
vector<pii>G[N];
vector<int>ans;
void add(int x,int y,int z){
	G[x].push_back(mp(y,z)); 
}
struct node{
	int a,b;
	vector<int>u,v;
}v[N];
void clear(){
	for(int i=1;i<=m;i++)col[i]=0,G[i].clear();
	for(int i=0;i<=tot;i++){
		v[i].a=0,v[i].b=0;
		v[i].u.clear(),v[i].v.clear();
		for(int j=0;j<=m;j++)f[i][j]=g[i][j]=0;
	}
	tot=0;ans.clear();
	return;
}
void dfs(int x,int co,int id){
	col[x]=co;
	if(co==1)v[id].a++,v[id].u.push_back(x);
	else v[id].b++,v[id].v.push_back(x);
	for(auto e:G[x]){
		if(e.second&&!col[e.first])dfs(e.first,3-co,id);
		if(!e.second&&!col[e.first])dfs(e.first,co,id);
	} 
	return;
}
void print(int n,int m){
	if(!n&&!m)return;
	if(g[n][m]==1){
		for(auto u:v[n].u)ans.push_back(u);
		print(n-1,m-v[n].a);
	}else{
		for(auto u:v[n].v)ans.push_back(u);
		print(n-1,m-v[n].b);
	}
	return;
}
int work(){
	m=p1+p2;
	for(int i=1;i<=n;i++){
		int u,v,w;char s[5];
		scanf("%d %d %s",&u,&v,s);
		w=(s[0]=='n');
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=m;i++)if(!col[i])++tot,dfs(i,1,tot);
	f[0][0]=1;
	for(int i=1;i<=tot;i++){
		for(int j=v[i].a;j<=m;j++)if(f[i-1][j-v[i].a])f[i][j]+=f[i-1][j-v[i].a],g[i][j]=1;
		for(int j=v[i].b;j<=m;j++)if(f[i-1][j-v[i].b])f[i][j]+=f[i-1][j-v[i].b],g[i][j]=2;
	}
	if(f[tot][p1]!=1){
		printf("no\n");
	}else{
		print(tot,p1);
		sort(ans.begin(),ans.end());
		for(auto u:ans)printf("%d\n",u);
		printf("end\n");
	}
	return 0;
} 
int main(){
	while(233){
		scanf("%d %d %d",&n,&p1,&p2);
		if(!n&&!p1&&!p2)break;
		work(),clear();
	}
	return 0;
}
```


因为方案数很大，所以 dp 数组会爆，记得特判。

如有错误，请指出。

---

