# String Problem

## 题目描述

小男孩 Valera 喜欢字符串。当它们是相同的时候，他会更喜欢它们。这就是为什么 Valera 会在空闲时间玩下面这个游戏。
他有两个由小写字母组成的字符串，根据游戏规则，Valera 每次可以将其中一个字符串中的任何一个字母 $A_i$ 变为 $B_i$，但要支付 $W_i$ 的代价。请你输出让两个字符串相同的最小代价，无解输出 $-1$。

## 样例 #1

### 输入

```
uayd
uxxd
3
a x 8
x y 13
d c 3
```

### 输出

```
21
uxyd
```

## 样例 #2

### 输入

```
a
b
3
a b 2
a b 3
b a 5
```

### 输出

```
2
b
```

## 样例 #3

### 输入

```
abc
ab
6
a b 4
a b 7
b a 8
c b 11
c a 3
a c 0
```

### 输出

```
-1
```

# 题解

## 作者：Dream_weavers (赞：15)

[题目传送门](https://www.luogu.com.cn/problem/CF33B)

## 思路

此题有点类似[P1037 产生数](https://www.luogu.com.cn/problem/P1037)，Floyd 和 Dijkstra 都可以通过，我贡献的是 Floyd 的做法。

设第一个字符串为 $str1$，第二个字符串为 $str2$，有向带权图为 $d$，最小代价为 $sum$，最后相同的字符串为 $ans$。

建图时，要把字母转化为数字（建议 $a$ 转化为 $0$，$b$ 转化为 $1$，$c$ 转化为 $2$，以此类推），建一条从 $A_i$ 到 $B_i$ 边权为 $W_i$ 的**单向边**。建完图，进行一次 Floyd 求出最短路。

然后开始循环遍历 $str1$：若 $str1_i$ 与 $str2_i$ 字母相同，则直接在 $ans$ 末尾添加 $str1_i$；其他情况下进行**贪心**：循环每一个字母，求出 $str1_i$ 与 $str2_i$ 能一起变化为另一个相同字母的**最小代价值**。若 $str1_i$ 与 $str2_i$ 无法变化为相同的字母，则直接输出 $-1$ 结束程序。循环过每个字母后，要更新 $sum$ 和 $ans$：$sum$ 加上最小代价值，$ans$ 在末尾添加对应最小代价值的相同字母。

最后输出 $sum$ 和 $ans$ 即可。

### 注意

- 如果 $str1$ 和 $str2$ 的长度不相等，可以直接输出 $-1$ 结束程序。

- 预处理要将 $d_{i,j}$ 都赋值一个**比所有边权都要大**的数（除了 $d_{i,i}$）。

## 代码

以下为此题关键部分：

```cpp
for(int i=0;i<str1.size();i++){//遍历str1
	if(str1[i]==str2[i]){//特判字母相同情况
		ans+=str1[i];
		continue;
	}
	tmp=' ';cnt=INF;//遍历字母前赋初始值，tmp记录字母，cnt记录最小代价值
	for(int j=0;j<n;j++){//遍历字母
		int s1=d[str1[i]-'a'][j];
		int s2=d[str2[i]-'a'][j];
		if(cnt>s1+s2){//出现更小的代价值
			cnt=s1+s2;//赋值并记录字母
			tmp=char(j+'a');
		}
	}
	if(cnt==INF){//若无法变化为相同的字母
		printf("-1");//则输出-1结束程序
		return 0;
	}
	sum+=cnt,ans+=tmp;//更新sum和tmp
}
```

---

## 作者：Xeqwq (赞：3)

用 floyd 处理每两个字母之间的距离，倒着建边，最后在统计结果的时候一位一位统计。对于字符串的每一位来说，枚举从 $a$ 到 $z$ 的每个字母作为源点，计算它向两个字符串对应位置的字母的距离之和，加到 $ans$ 里面。  
```cpp
#include <iostream>
#include <string>
#include <cstring> 
using namespace std;
int chartoint(char c){return c-'a'+1;}//字母转数字
char inttochar(int r){return r+'a'-1;}//数字转字母
int g[30][30];
int n=26,m;
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
string s1,s2;
char c1,c2;
int u,v,w,v1,v2;
int main()
{
	cin>>s1>>s2>>m;
	if(s1.size()!=s2.size())//位数不同肯定不可达
	{
		cout<<-1;
		return 0;
	}
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=n;i++) g[i][i]=0;
	while(m--)
	{
		cin>>c1>>c2>>w;
		u=chartoint(c1);
		v=chartoint(c2);
		g[v][u]=min(g[v][u],w);//倒着建图
	}
	floyd();
	string as=s1;
	int p,ans=0;
	for(int i=0;i<s1.size();i++)
	{
		if(s1==s2) continue;
		p=0x3f3f3f3f;
		v1=chartoint(s1[i]);
		v2=chartoint(s2[i]);
		for(u=1;u<=n;u++)//枚举源点
		{
			if(g[u][v1]==0x3f3f3f3f||g[u][v2]==0x3f3f3f3f) continue;
			if(p>g[u][v1]+g[u][v2])
			{
				p=g[u][v1]+g[u][v2];
				as[i]=inttochar(u);
			}
		}
		if(p==0x3f3f3f3f)
		{
			cout<<-1;
			return 0;
		}
		ans+=p;
	}
	cout<<ans<<endl<<as;
	return 0;
}
```

---

## 作者：_Emiria_ (赞：2)

同步于[我的cnblogs](https://www.cnblogs.com/Violet-Ever-Garden/p/14870238.html)

### 废话

重铸dijkstra荣光，我辈义不容辞！

~~说实话我刚看到这道题还以为是dp。~~

----

### 分析 & 思路

一道比较裸的最短路 + 字符串，下文中用$dis(a,b)$表示从字母 $a$ 到字母 $b$ 的最短路。

题意已经很明确了，就是问我们把 $A$ 串和 $B$ 串变成同样的字符串，所需的最小代价以及最后相同的串。考虑遍历一遍 $A$ 串和 $B$ 串，求 $\sum^{len(a)}_{i = 1} Min\{dis(a_i ,k) + dis(b_i, k)\}$（ $k$ 为 $a \sim z$ 的一个字母）。
即找出一个字母 $k$ ，使得$A_i$ 到 $k$ 的最短路加上 $B_i$ 到 $k$ 的最短路最小。

显然我们并不能每遍历到一个字母就做一次 dijk，但是想到点数非常少，最多只有 26 个，所以考虑遍历 26 个字母，对于每个字母做一次 dijk，然后把这个字母到每个字母的最短路存到一个`dis[start][end]`数组里面。这样就可以做到 $O(n(n + m)\log{n})\;(n \le 26)$ 预处理， $O(26  \times len(a))$ 求解，还是挺快的。

建图时，给每一个字母一个编号，从 0 开始。当然`dis`数组的下标也是字母的编号。

还有什么不太懂的可以看代码注释。

----

### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <queue>

#define pair std::pair
#define make_pair std::make_pair
#define inf 114514 // 随便赋一个大一点的数就行
#define maxn 100005

struct Edge{
    int start, end, val, nexty;
}edge[maxn];

char u, v, ans[maxn], a[maxn], b[maxn];
// ans记录最后相同的串

int m, w, cnt_edge, head[maxn], dis[30][30];
int sum, minn, a1, b1, pay;

bool vis[30];

inline void add_edge(int u, int v, int w){
    edge[++cnt_edge] = (Edge){u, v, w, head[u]};
    head[u] = cnt_edge;
}

inline void dijk(int s){ // 普通的dijkstra模板
    // 初始化
    std::memset(vis, 0, sizeof vis);
    for(register int i = 0; i < 26; i++) dis[s][i] = inf;
    dis[s][s] = 0;
    std::priority_queue < pair < int , int > > q;
    q.push(make_pair(0, s));
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = edge[i].nexty){
            int v = edge[i].end;
            if(dis[s][v] > dis[s][u] + edge[i].val){
                dis[s][v] = dis[s][u] + edge[i].val;
                q.push(make_pair(-dis[s][v], v));
            }
        }
    }
}

int main(){
    scanf("%s\n%s", a + 1, b + 1);
    int lena = strlen(a + 1), lenb = strlen(b + 1);
    if(lena != lenb){
    	// 如果a串和b串的长度不同是显然无法变为相同的串的
        puts("-1");
        return 0;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        scanf(" %c %c %d", &u, &v, &w);
        // 建议用cin读，我被这卡了一年
        add_edge((u - 'a'), (v - 'a'), w);
    }
    for(register int i = 0; i < 26; i++){
        dijk(i); // 预处理出26个字母间的最短路
    }
    for(int i = 1; i <= lena; i++){
        if(a[i] == b[i]){
            ans[i] = a[i]; // 如果a和b这一位相同就不用改了，直接记录下来。
            continue;
        }
        minn = inf;
        a1 = (a[i] - 'a'), b1 = (b[i] - 'a');
        // 找最小dis和
        for(int j = 0; j < 26; j++){
            if(dis[a1][j] == inf || dis[b1][j] == inf) continue;
            // dis[u][v] = inf 说明不存在u -> v这条边
            pay = dis[a1][j] + dis[b1][j];
            if(pay < minn) ans[i] = j + 'a', minn = pay;
        }
        if(minn == inf){puts("-1"); return 0;}
        // 如果发现有两个字母无法变成一样的就输出-1，结束
        sum += minn;
    }
    printf("%d\n%s", sum, ans + 1 /*因为ans的下标是从1开始的*/);
    return 0;
}
```
----
最慢的点 30ms，但还是被写 floyd 的大佬暴踩了 orz，傻子自带大常数。


---

## 作者：tzc_wk (赞：2)

这是一道字符串最短路问题，dijkstra是肯定能过的，但是这里我用Floyd算法。

代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int main()
{
    string s, t;
    cin>>s>>t;
    if (s.size()!=t.size()) {//如果大小不一样那么肯定转换不了
        cout<<"-1"<<endl;
        return 0;
    }
    int k;
    cin>>k;
    vector<vector<int> >g(26,vector<int>(26,inf));//这其实就是Floyd里存放距离的二维数组，只不过这里把它改成了vector形式
    for (int i=0;i<26;i++) {
        g[i][i] = 0;
    }
    while(k--){
        char a,b;
        int C;
        cin>>a>>b>>C;
        g[a-'a'][b-'a']=min(g[a-'a'][b-'a'],C);//从a变为b的代价为C
    }
    for (k=0;k<26;k++) {
        for (int i=0;i<26;i++) {
            for (int j=0;j<26;++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);//这就是Floyd的核心
            }
        }
    }
    int ans=0;
    string p="";
    for (int i=0;i<s.size();++i) {
        if (s[i]==t[i]) {
            p+=s[i];//相等就不用换了
            continue;
        }
        char r=' ';
        int R=inf;
        for (int c=0;c<26;c++) {
            if (g[s[i]-'a'][c]+g[t[i]-'a'][c]<R) {//找到变换代价更小的了
                R=g[s[i]-'a'][c]+g[t[i]-'a'][c];
                r=(char)(c+'a');
            }
        }
        if(R==inf) {
            cout<<"-1"<<endl;//没有可换的
            return 0;
        }
        ans+=R;//答案加上它所需的代价
        p+=r;
    }
    cout<<ans<<endl<<p<<endl;
    return 0;
}
```

---

## 作者：黑影洞人 (赞：0)

最近在板刷 CF，碰到这道题眼前一亮。

一开始想的是 DP 的做法，但是字符串直接有很多变化，并且状态之间没有联系。

实际上是图论题。

对于处理字符串的变换，我直接构造一个图跑一遍全源最短路。

一种字符能变换成另一种字符，我们就连一条边，边权就是变化的代价。

值得注意的是，这道题的边是单向的，并且会有重边产生。

~~我绝对不会告诉你我没看样例 2 直接交上去结果 WA 了~~

```cpp
scanf("%lld",&n);
memset(dis,0x3f,sizeof(dis));
for(int i=1;i<=n;i++){
	char a,b;int val=0;
	cin>>a>>b>>val;
	dis[(int)a][(int)b]=min(val,dis[(int)a][(int)b]);
}
for(int k=1;k<=200;k++){
	for(int i=1;i<=200;i++){
		for(int j=1;j<=200;j++){
			dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		}
	} 
}
```
很好，我们处理完字符转化的关系后，就开始统计答案。

```cpp
int l=a.size(),l1=b.size();
if(l!=l1)return puts("-1"),0;//如果长度不一样，直接输出-1退出
int ans=0;//ans为最小变化值
for(int i=0;i<l;i++){
	c[i]=a[i];
	if(a[i]==b[i])continue;//如果a和b在这一位一样，那就没必要再处理这一位了
	int now=2147483647;
	for(int j='a';j<='z';j++){//假如有一些字母，a,b转化到他代价和最小，这也是可行的，我们直接从'a'到'z'枚举一下
		if(dis[a[i]][j]+dis[b[i]][j]<now){
			now=dis[a[i]][j]+dis[b[i]][j];
			c[i]=j;
		}
	}
   //下面的就是判断把a的第i为改成b，或者反过来需要的最小代价
	if(now>dis[b[i]][a[i]])c[i]=a[i],now=dis[b[i]][a[i]];
	if(now>dis[a[i]][b[i]])c[i]=b[i],now=dis[a[i]][b[i]];
	ans+=now;//答案增加上最小增量
}
if(ans>2147483647)return puts("-1"),0;//如果答案是无穷大，说明无法到达，直接输出-1退出
printf("%lld\n",ans);
puts(c);
```
管理员同志审核题解辛苦了

完结撒花

---

## 作者：XL4453 (赞：0)

### 解题思路：

~~第一眼看成 DP。~~

先解释一下为什么不能直接用 DP，由于这个变化是可以叠加的，也就是可以先将某一个字符变成另一个，再由另一个再更改到想要的字符，而这个代价并不一定比直接变的代价大，所以直接 DP 肯定是要出问题的。

那么就先处理一种字符到另一种字符的最小改变代价，然后再用一开始的 DP 思路处理字符串。

而这种由一个中转点优化另外若干点的形式可以转换为用最短路的方式求解，这个问题直接套模板就可以了。

然后是最后的求解 DP 问题，需要枚举两个走到一起（可以两个都不同）的最小代价。由于转移点一定是前面那一个，所以数组都不用开，~~所以这个可能不叫 DP~~。

---

话说这道题的出题人真的良心，第二个数据点就给你重复的两点。

----
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string a,b;
char x,y,c[100005];
int f[30][30],n,num;
int main(){
	cin>>a>>b;
	if(a.length()!=b.length()){
		printf("-1\n");
		return 0;
	}
	scanf("%d",&n);
	for(int i=1;i<=26;i++)
	for(int j=1;j<=26;j++)
	f[i][j]=1e9;
	for(int i=1;i<=26;i++)
	f[i][i]=0;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		scanf("%d",&num);
		f[x-'a'+1][y-'a'+1]=min(num,f[x-'a'+1][y-'a'+1]);
	}
	for(int k=1;k<=26;k++)
	for(int i=1;i<=26;i++)
	for(int j=1;j<=26;j++)
	f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	int ans=0;
	for(int i=0;i<a.length();i++){
		int now=2e9;
		for(int j=1;j<=26;j++){
			if(f[a[i]-'a'+1][j]==1e9||f[b[i]-'a'+1][j]==1e9)continue;
			if(f[a[i]-'a'+1][j]+f[b[i]-'a'+1][j]<now){
				now=f[a[i]-'a'+1][j]+f[b[i]-'a'+1][j];
				c[i]=j+'a'-1;
			}
		}
		if(now==2e9){
			printf("-1\n");
			return 0;
		}
		ans+=now;
	}
	printf("%d\n",ans);
	cout<<c<<endl;
	return 0;
}
```


---

## 作者：Ryo_Yamada (赞：0)

字符串最短路。假设输入两字符串 $s,\,t$。如果 $s$ 和 $t$ 长度不同则一定不能转换，输出 $-1$。

随后首先使用 Floyd 算法计算出将每个字母转换成每个字母的最小代价，若无法转换则代价为 $+\infty$。随后枚举 $s$ 和 $t$ 每个相同位置转换为相同字符的最小代价，若为 $+\infty$ 则输出 $-1$，否则 $\text{sum}$ 加上这个最小代价，将字符串 $s$ 当前位置改为这个字符。

此题有两个坑点：

- 输入中可能有重边，需要取最小而不是直接赋值。~~好在 CF 出题人良心~~，样例 2 就是这种情况，若不判断是过不了的。

- 对于 $s_i$ 和 $t_i$，不一定只有将 $s_i$ 变为 $t_i$ 和将 $t_i$ 变为 $s_i$ 才是最值，需要枚举每个字母，计算最小值。

$\text{Code}$：

```cpp
const int N = 30;
const int inf = 0x3f3f3f3f;

int m, sum;
string s, t;
int trans[N][N];

int main() {
	memset(trans, 0x3f, sizeof trans);
 	cin >> s >> t >> m;
 	if(s.size() != t.size()) return puts("-1"), 0;
 	while(m--) {
 		char c, cc;
 		int d;
 		scanf(" %c %c", &c, &cc);
 		scanf("%d", &d);
 		To_min(trans[c - 'a' + 1][cc - 'a' + 1], d);
	}
	rep(i, 1, 26) trans[i][i] = 0;
	rep(k, 1, 26) {
		rep(i, 1, 26) {
			rep(j, 1, 26) {
				To_min(trans[i][j], trans[i][k] + trans[k][j]);
			}
		}
	}
	rep(i, 0, s.size() - 1) {
		int ss = s[i] - 'a' + 1, tt = t[i] - 'a' + 1;
		int mn = inf, f;
		rep(j, 1, 26) {
			if(mn > trans[ss][j] + trans[tt][j]) mn = trans[ss][j] + trans[tt][j], f = j;
		}
		if(mn == inf) return puts("-1"), 0;
		sum += mn, s[i] = char(f - 1 + 'a');
	}
	cout << sum << endl << s << endl;
	return 0;
}
```


---

## 作者：Meatherm (赞：0)

AC之后发现了楼下有人用$O(N^3)$的$Floyd$。于是我就写了一个$dijkstra+$堆优化的题解，理论复杂度是$O(N^2*logN)$，再怎么也比$Floyd$快一点吧（其实都能AC）。

===========↑上面是废话请跳过↑=============

这道题目，其实就是一个字符串最短路问题。所以跑最短路之后在加一个贪心，就珂以完美的AC这道题（还是蓝题哦~）。

细节很少。我觉得的细节就是需要将字符进行离散化，也就是说'a'=1,'b'=2,···'z'=26。

其它的话，实在是没什么细节。

这里就不废话了，直接放上代码。

```
# include <bits/stdc++.h>
# define rr register 
const int N=40;
int mdis[N][N];
std::string a,b,ans;
int m;
struct Edge
{
	int to,next,v;
}edge[N*N];//邻接表存边
int sum,head[N];
bool c[N]; 
struct node
{
	int id,w;
};
bool operator < (node A,node B)
{
	return A.w>B.w;
}
std::priority_queue <node> k;// 重载运算符 & 优先队列
inline void add(int x,int y,int v)
{
	edge[++sum].to=y;
	edge[sum].next=head[x];
	edge[sum].v=v;
	head[x]=sum;
	return;
} // 建边
inline void dijkstra(int); // 最短路
int main(void)
{
	std::cin>>a>>b;
	if(a.size()!=b.size())// 长度判等
	{
		puts("-1");
		return 0;
	}
	std::memset(mdis,0x3f3f3f3f,sizeof(mdis)); //初始化为+∞
	for(rr int i=1;i<=26;++i)
		mdis[i][i]=0; // 自己转换为自己肯定为0
	scanf("%d",&m);// 输入变换数量
	char tx,ty;
	for(rr int i=1,w;i<=m;++i)
	{
		std::cin>>tx>>ty;
		scanf("%d",&w);
		add(tx-96,ty-96,w);//将下标进行离散化，减去96，使得编号为1~26。
	}
	for(rr int i=1;i<=26;++i)
		memset(c,false,sizeof(c)),dijkstra(i);//跑最短路之前初始化一遍c数组，然后跑 方便接下来的计算
	int len=a.size(),money=0;
	
	for(rr int i=0,minx,id;i<len;++i)
	{
		if(a[i]==b[i])// 如果相等的话 不用去加了 
		{
			ans+=a[i];
			continue;
		}
		minx=0x3f3f3f3f;
		id=-1；
		for(rr int j=1;j<=26;++j)
			if(mdis[a[i]-96][j]+mdis[b[i]-96][j]<minx)// 运用贪心 不断的取最小的
				minx=mdis[a[i]-96][j]+mdis[b[i]-96][j],id=j;
		if(id==-1)// 如果一个都没找到的话 那就是不能转换了 直接输出-1然后结束
		{
			puts("-1");
			return 0;
		}
		money+=minx;// 总花费加上这一次的花费
		ans+=(char)id+96;// 把离散化之后的字符转换回去（加上ASCLL96）
	}
	std::cout<<money<<"\n"<<ans;
	return 0;
}
inline void dijkstra(int g)// dijkstra 堆优化不解释 唯一要注意的是最短路数组要开成二维
{
	k.push((node){g,0});
	while(!k.empty())
	{
		node tmp=k.top();
		k.pop();
		int i=tmp.id;
		c[i]=true;
		for(rr int j=head[i];j;j=edge[j].next)
		{
			if(!c[edge[j].to]&&mdis[g][i]+edge[j].v<mdis[g][edge[j].to])
			{
				mdis[g][edge[j].to]=mdis[g][i]+edge[j].v;
				k.push((node){edge[j].to,mdis[g][edge[j].to]});
			}
		}
	}
	return;
}
```

---

