# [USACO2.3] 控制公司 Controlling Companies

## 题目描述

有些公司是其他公司的部分拥有者，因为他们获得了其他公司发行的股票的一部分。

据说，如果至少满足了以下三个条件之一，公司 $A$ 就可以控制公司 $B$ 了：

- 公司 $A$ = 公司 $B$。
- 公司 $A$ 拥有大于 $50\%$ 的公司 $B$ 的股票。
- 公司 $A$ 控制 $K$（$K \geq 1$）个公司，记为 $C_1, \ldots, C_K$，每个公司 $C_i$ 拥有 $x_i\%$ 的公司 $B$ 的股票，并且 $x_1+ \ldots + x_K \gt 50\%$。

给你一个表，每行包括三个数 $i,j,p$：表明公司 $i$ 享有公司 $j$ 的 $p\%$ 的股票。计算所有的数对 $(h,s)$，表明公司 $h$ 控制公司 $s$。至多有 $100$ 个公司。

## 说明/提示

翻译来自NOCOW

USACO 2.3


## 样例 #1

### 输入

```
3
1 2 80
2 3 80
3 1 20```

### 输出

```
1 2
1 3
2 3```

# 题解

## 作者：以墨 (赞：31)

直接用dfs




```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[102][102];//a[i][j]表示公司i拥有公司j百分之a[i][j]的股份
int cnt[102]；//cnt[i]表示当前阶段中公司x拥有公司i累计有百分之cnt[i]的股份
int m;
bool f[102]；//f[i]表示当前阶段中第i个公司是否被搜索过
bool own[102];//own[i]表示当前阶段中公司x是否能控制公司i
void EMILY(int x)
{
    if(f[x]==true)//边界条件，如果当前公司已被搜索过，则直接返回
        return ;
    f[x]=true;//标记为搜索过
    for(int i=m;i;i--)//枚举所有公司
    {
        cnt[i]+=a[x][i];//加上当前公司的股份百分点
        if(cnt[i]>50)//满足条件
        {
            own[i]=true;//设置为能够控制
            EMILY(i);//递归
        }
    }
}
int main()
{
    freopen("1475.in","r",stdin);
    freopen("1475.out","w",stdout);
    int i,j,k,u,v,w,n;
    for(scanf("%d",&n);n;n--)
    {
        scanf("%d%d%d",&u,&v,&w);
        a[u][v]=w;//公司u拥有公司v百分之w的股份
        m=max(u,max(m,v));//m为公司的个数
    }
    for(i=1;i<=m;i++)
    {
        memset(f,false,sizeof(f));//把遍历情况全部清空
        memset(own,false,sizeof(own));//把所属情况全部置为false
        memset(cnt,0,sizeof(cnt));//把累计百分点全部清零
        EMILY(i);//从第i个公司开始搜索
        for(j=1;j<=m;j++)
            if(own[j]==true&&i!=j)//如果公司j属于公司i且i不等于j
                printf("%d %d\n",i,j);//输出公司i控制公司j
    }
    return 0;
}

```

---

## 作者：「QQ红包」 (赞：13)

题解by：redbag

原题地址：http://www.luogu.org/problem/show?pid=1475

题解地址：http://redbag.duapp.com/?p=1334

我说这道题可以用dfs？不会爆，还很快

>USER: lanxuan yi [ylx14271]
>TASK: concom
>LANG: C++

>Compiling...
>Compile: OK

>Executing...
>Test 1: TEST OK [0.000 secs, 4336 KB]
>Test 2: TEST OK [0.000 secs, 4336 KB]
>Test 3: TEST OK [0.000 secs, 4336 KB]
>Test 4: TEST OK [0.000 secs, 4336 KB]
>Test 5: TEST OK [0.000 secs, 4336 KB]
>Test 6: TEST OK [0.000 secs, 4336 KB]
>Test 7: TEST OK [0.000 secs, 4336 KB]
>Test 8: TEST OK [0.000 secs, 4336 KB]
>Test 9: TEST OK [0.011 secs, 4336 KB]

>All tests OK.

>Your program ('concom') produced all correct answers!  This is your
>submission #7 for this problem.  Congratulations!
接下来是代码

```cpp
/*
ID: ylx14274
PROG: concom
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm>
#define LL unsigned long long
using namespace std;
int x,y,k,n,t,i,j;
int a[201][201];//a[i][j]表示i公司控制j公司的股权数量 
int pd[201];//判重 
int he[201];
void dfs(int c)//c是i公司控制的公司 
{
    pd[c]=1;//标记 
    int i;
    for (i=1;i<=n;i++)
    { 
        he[i]+=a[c][i];//加上c公司拥有i的股权 
        if (he[i]>50)//c拥有公司i 
        {
            if (pd[i]==0)//没被搜过
            dfs(i);//搜 
        } 
    } 
    return;
}
int main() 
{
    freopen("concom.in","r",stdin);
    freopen("concom.out","w",stdout);//文件 
    scanf("%d",&t);//读入 
    n=0; 
    for (i=1;i<=t;i++)
    {
        scanf("%d%d%d",&x,&y,&k);
        if (x>n) n=x;
        if (y>n) n=y;//找公司数量？标号最大？ 
        a[x][y]+=k;//标记
    } 
    for (i=1;i<=n;i++) 
    {
        for (j=1;j<=200;j++) pd[j]=0;//数组赋初值 
        for (j=1;j<=200;j++) he[j]=0;//数组赋初值 
        dfs(i); //搜，自己控制自己 
        for (j=1;j<=n;j++) 
        if (he[j]>50&&i!=j)//不能是自己 
            printf("%d %d\n",i,j); //输出 
    }
    return 0; 
}
```

---

## 作者：ABCDXYZ (赞：13)

这样的好题，怎么能因为数据水而用爆搜水过呢？！

其实一看到题目，许多人都会想到并查集吧

但这又不是普通的并查

具体来说：

- 一个公司可能有多个祖先

- 输出时要把祖先链上的所有祖先输出

所以，只要运用树状数据结构就可以了~~

代码不精的我借用并查思想打了一份代码，权当抛砖引玉了（。。就叫树状并查吧）






```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=505;
int f[maxn][maxn];//f[x][y]表示x公司拥有的y公司的股份 
bool vis[maxn][maxn];//vis表示x是不是y的父亲 
struct node{
    int c,ff;
}cop[maxn*maxn*maxn];//应输出的答案（c是父亲，ff是儿子） 
int ccnt;
inline int read(){
    int k=0,base=1;char s;
    while(s=getchar()){if(s=='-')base=-1;if(s>='0' && s<='9')break;}
    while(s>='0' && s<='9'){k=(k<<3)+(k<<1)+(s^'0');s=getchar();}
    return k*base;
}
int son[maxn][maxn],cnt[maxn];//son[x][y]表示x的第y个儿子 
int linker[maxn][maxn],cnt1[maxn];//linker[x][y]表示x拥有其股份的第y个公司 
void link(int x,int y){
    if(vis[x][y])return;
    son[x][++cnt[x]]=y;
    vis[x][y]=1;
```
}//加一个儿子

```cpp
void add(int x,int y,int w){
    if(!vis[x][y])
        f[x][y]+=w,linker[x][++cnt1[x]]=y;
    if(f[x][y]>50 && !vis[x][y]){
        link(x,y);
    }
```
}//多一个关系

```cpp
void Find1(int x,int fa){
    for(int i=1;i<=cnt1[x];i++){
        if(f[x][linker[x][i]] && !vis[fa][linker[x][i]] && !vis[x][linker[x][i]]){
            f[fa][linker[x][i]]+=f[x][linker[x][i]];
            if(f[fa][linker[x][i]]>50)
                link(fa,linker[x][i]);//如果子公司拥有某个公司z的股份，并且f[fa][z]>50,就把z放进x的子树中 
        }
    }
```
}//寻找fa的子公司所拥有的股份

```cpp
void Find(int x,int fa){
    int head=0;
    while(son[x][++head]!=0){
        if(fa==son[x][head])continue;//这句话必加，不然会有死循环 
        cop[++ccnt].c=fa;
        cop[ccnt].ff=son[x][head];
        Find(son[x][head],fa);
    }
```
}//寻找以fa为最大的祖先树上的所有子公司

```cpp
bool cmp(node a,node b){
    if(a.c>b.c)return false;
    if(a.c<b.c)return true;
    else {
        if(a.ff>b.ff)return false;
    }
    return true;
```
}//按题目要求排序

```cpp
int main( ){
    int m,n,j,k,i;
    n=read();
    for(i=1;i<=n;i++){
        int x=read(),y=read(),w=read();
        add(x,y,w);
```
}//加关系
```cpp
    for(i=1;i<=100;i++){
        int j=0;
        while(son[i][++j]!=0){
            Find1(son[i][j],i);
```
}//寻找i的子公司所拥有的股份
```cpp
    }
    for(i=1;i<=100;i++)
        Find(i,i);//寻找以fa为最大的祖先的树上的的所有子公司 
    sort(cop+1,cop+ccnt+1,cmp);
    for(i=1;i<=ccnt;i++)
        printf("%d %d\n",cop[i].c,cop[i].ff);//输出祖先和儿子 
    return 0;
}
```
其实这并不是真正的并查，因为是父亲不断寻找儿子而不是儿子寻找父亲
但时间效率也不错了，作者我将十分感激各位提出宝贵意见


---

## 作者：Celebrate (赞：9)

这一道题是因为数据小才容易的，我们直接dfs来搜索就可以

了，如果不用搜索或并查集的话应该很难做出来

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n;//表示出现公司的大小 
int a[110][110],f[110];//a表示掌握股份（不会改变），f[k]表示在搜索第i个公司时，第i个公司所占第k个公司的总股份 
bool v[110],c[110];//v表示这个公司是否搜索过，c表示控制 
void dfs(int k)//搜索第k个公司 
{
	if(v[k]==true) return;//如果搜索过了，就不用管了 
	v[k]=true;//改为被搜索过 
	for(int i=1;i<=n;i++)//枚举每个公司 
	{
		f[i]+=a[k][i];
		if(f[i]>50)//如果控制了这个公司 
		{
			c[i]=true;//记为被控制 
			dfs(i);//往下深搜 
		}
	}
}
int main()
{
	int i,j,x,y,z,t;
	scanf("%d",&t);//输入 
	for(i=1;i<=t;i++) 
	{
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=z;n=max(n,max(x,y));//因为有些公司可能是假的，就找出现过最大的公司就好了 
	}
	for(i=1;i<=n;i++)//枚举n个出现过的公司 
	{
		memset(v,false,sizeof(v));//初始化 
		memset(c,false,sizeof(c));
		memset(f,0,sizeof(f));
		dfs(i);//从第i个公司开始深搜 
		for(j=1;j<=n;j++)
			if(c[j]==true && i!=j)//如果控制了，就输出 
				printf("%d %d\n",i,j);
	}
	return 0;
}
```

---

## 作者：kokodayou (赞：6)

 _本蒟蒻的第一篇题解。谨以此题纪念我的AC200吧，望管理员爸爸审核通过！_ 

[原题传送门](https://www.luogu.org/problem/P1475)

****看到这道题我第一秒就想到：水题！并查集秒切！ 
忽然转念一想，本蒟蒻还不会并查集鸭。。。。点开标签，简单的搜索二字饱含大大地深意（其实就是个普通的暴搜），那我们就利用离散化搞一下这道题吧!

## 所谓离散化：

#### 官方定义：
把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。

Emmmm。。。这么有技术含量的定义想来我这种蒟蒻也看不懂

#### 通俗一点：
就是把没有用的数据全部删掉，换成一些比较小的数来代替这些大数据，用小数据来处理大数据。

数据比较水，所以再简单的写一个暴搜，快乐的提交
AC其实很简单。

### 附：点开提交记录第一页便有两名小可怜抄题解棕名了。。题解虽好，小心中毒噢！

本题解离散化过程思维难度略大，不过还是很好理解的
## 请君放心食用！


详情见注释吧，附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,q,m,num,hh[2333333],h[6333][6333],w[6333][6333];
int a[6333][6333],b[2333333],c[6333][6333],f[2333333],g[6333][6333],o[2333333];
bool d[6333][6333],e[23333];
int yes(int x,int y){
	for(int i=1;i<=num;i++){
		a[x][i]+=a[y][i];       //最初的公司对其他的公司控制力又强了几分 
		if(a[x][i]>50&&!d[x][i]){      //又有公司要凉了 
			d[x][i]=1;
			c[x][++b[x]]=i;
			yes(x,i);             //继续寻找可供最初的公司控制的子公司 
		}
	}
}
int kuo(int x){
	for(int i=1;i<=num;i++)
		if(a[x][i]>50&&!d[x][i]){        //如果可以控制且1公司还没控制2公司 
			d[x][i]=1;
			c[x][++b[x]]=i;          //2公司沦陷了。。。。 
			yes(x,i);         //进入递归，扩展1公司通过2公司可以控制的其他公司 
		}
}
int main(){
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>p>>q>>m;                //朴素的不能再朴素的输入  （逃 
		if(!e[p]){o[++num]=p;e[p]=1;}          //记录下来每个值 
		if(!e[q]){o[++num]=q;e[q]=1;}          //为离散化做准备 
		g[p][++hh[p]]=q;              //记录和某一个公司有连接的所有其他公司 
		h[p][q]=m;
	}
	sort(o+1,o+num+1);                   //做一个排序保证数据输出升序排列 
	for(i=1;i<=num;i++)f[o[i]]=i;          //
	for(i=1;i<=num;i++)                //离散化 
		for(j=1;j<=hh[o[i]];j++)
			a[i][f[g[o[i]][j]]]=h[o[i]][g[o[i]][j]];
	for(i=1;i<=num;i++)kuo(i);               //查找被i公司控制的公司，dfs开始！  
	for(i=1;i<=num;i++)                 //输出i公司控制的公司 
		for(j=1;j<=num;j++)
			if(d[i][j]&&o[i]!=o[j])             //自己不能控制自己所以o[i]!=o[j] 
				cout<<o[i]<<" "<<o[j]<<endl;       //输出结果 
	return 0;            //每天return 0，快乐赛神仙！！ 
}
```
 _小生不才，题解不如各位dalao有技术含量，若有疑问评论区讨论！
祝各位OIer永葆黑发！_ 

---

## 作者：JCY_ (赞：6)

~~本蒟蒻第二篇题解，求管理员大大让过~~  

[本蒟蒻博客连接](https://www.luogu.org/blog/JCY-86181/#)   

贡献一篇C++无dfs题解：  

(1) 先把每个公司通过第一、二种方法控制的公司记录下来

(2) 根据(1)把通过第三种方法能控制的公司记录下来，**并让他们也参与计算**(见程序"十分巧妙"的那一行)  

(3) 排序后输出

```cpp
/*
ID: jcy_5371
TASK: concom
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;
#define ms(a,b) memset(a,b,sizeof a)//我太懒了
const int maxn=110;
int n=0/*计算有多少个公司*/,e[maxn][maxn]/*e[i][j]表示i控制j的股份数*/,cnt[maxn]/*见后文解释*/;
bool vis[maxn]/*见后文解释*/;
vector<int> con[maxn]/*con[i]记录i所控制的公司*/;
int main()
{
	ios::sync_with_stdio(0);//关闭流同步
	freopen("concom.in","r",stdin);//忽略它
	freopen("concom.out","w",stdout);//也忽略它
	ms(e,0);//初始化
	for(int i=0;i<maxn;i++)
	{
		con[i].clear();//初始化
		con[i].push_back(i);//公司i控制其本身(即第一个控制方式)
	}
	int T;
	cin>>T;
	while(T--)
	{
		int u,v,w;//u控制v的w股份
		cin>>u>>v>>w;
		n=max(n,max(u,v));//更新公司数
		e[u][v]=w;//记录股份
		if(w>50) con[u].push_back(v);//如果u控制v的股份大于50%，则u控制v(即第二个控制方式)
	}
	for(int i=1;i<=n;i++)
	{
		ms(cnt,0);//cnt[j]表示i目前控制的所有公司共拥有的j的股份数(即第三个控制方式)
		ms(vis,0);//vis[j]表示i控制j
		for(int j=0;j<(int)con[i].size();j++) vis[con[i][j]]=1;//vis初始化
		for(int j=0;j<(int)con[i].size();j++)//遍历i控制的公司(*标记*)
		{
			int t=con[i][j];//i控制t
			for(int k=1;k<=n;k++)//寻找t所拥有公司的股份
			{
				if(vis[k]) continue;//如果i已控制k，便无需更新cnt[k]，同时也是为了去重(见两行后)
				cnt[k]+=e[t][k];//更新cnt[k]
				if(cnt[k]>50)//如果i控制k
				{
					vis[k]=1;//标记
					con[i].push_back(k);//这里十分的巧妙(手动狗头)，因为con[i].size()也会随之改变(见有*标记*的行)
				}
			}
		}
		sort(con[i].begin(),con[i].end());//手动排个序
		for(int j=0;j<(int)con[i].size();j++)
		{
			if(con[i][j]==i) continue;//不输出自己
			cout<<i<<" "<<con[i][j]<<endl;
		}
	}
	return 0;
}
```

求各位巨佬给一个赞

---

## 作者：R·Buffoon (赞：5)

**真·暴力**
***
有这么多爆搜题解了，怎么就没一篇暴力题解勒（毕竟$n<=100$）

既然是暴力，那么就不多讲了，来

**Code:**
~~~cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;

int in()
{
    int qwq=0;char c=getchar();//输入都是正数，就不判‘-’了
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar()) qwq=(qwq<<1)+(qwq<<3)+(c&15);
    return qwq;
}

const int N=105;

int n,m;
int u,v,w;
int a[N][N],cnt[N];
int vis[N];
int flag;

int main()
{
    n=in();
    for(RI i=1;i<=n;++i)
    {
    	u=in(),v=in(),w=in();
    	a[u][v]=w;//u公司拥有v公司w%的股份
    	m=max(m,max(u,v));//计算共有多少个公司（其实直接给m赋值100就可以了，时间差不多）
	}
	
	for(RI i=1;i<=m;++i)
	{
		memset(vis,0,sizeof(vis));//清空
		memset(cnt,0,sizeof(cnt));//数组
		cnt[i]=100;//对自己公司的控制权为100%
		flag=1;
		
		while(flag)
		{
			flag=0;
			for(RI j=1;j<=m;++j)
			{
				if(!vis[j] && cnt[j]>50)//i公司控制了j公司且之前未拜访（滑稽）
				{
					vis[j]=1;
					for(RI k=1;k<=m;++k) cnt[k]+=a[j][k];//加上j公司拥有的股份
					flag=1;//加上j公司拥有的股份后，i公司可能还有公司可以控制，所以继续找
				}
			}
		}
		
		for(RI j=1;j<=m;++j)
		{
			if(vis[j] && i!=j) printf("%d %d\n",i,j);//不输出控制自己的公司（即自己）
		}
	}
	
    return 0;
}
~~~

---

## 作者：梦景 (赞：5)

dijkstra算法，典型的搜索

一遍可以过，数据不大

```cpp
uses math;
const
    MAXN = 100;
type
    arrn = array[1..MAXN] of longint;
var
    M,i,N,x,y,p,node,j : longint;
    hash : array[1..MAXN] of boolean;
    dist : arrn;
    map : array[1..MAXN] of arrn;
begin
    readln(M);
    for i := 1 to M do begin
        readln(x,y,p); map[x,y] := p;
        N := max(N,x); N := max(N,y);
    end;
    for node := 1 to N do begin
        fillchar(hash,MAXN,0); hash[node] := true;
        dist := map[node];
        repeat
            for i := 1 to N do
                if not hash[i] and (dist[i] > 50) then break;
            if hash[i] or (dist[i] <= 50) then begin
                for i := 1 to node-1 do
                    if hash[i] then writeln(node,' ',i);
                for i := node+1 to N do
                    if hash[i] then writeln(node,' ',i);
                break;
            end;
            hash[i] := true;
            for j := 1 to N do inc(dist[j],map[i,j]);
        until false;
    end;
end.
```

---

## 作者：resftlmuttmotw (赞：3)

$USACO$ 上 $CHAPTER 2$

的题

黄题难度 但我写了一个网络流

看了下题解 只有我是写的网络流

其他好像都是搜索

思想

网络流中进行是否可以増广和増广是

即(我写的$dinic$)DINIC中的$BFS$和$DFS$

判断是否可以走的时候 改成

```cpp
if(depth[v = edge[e].v] == -1&&(edge[e].w&&able[tp]))//BFS
if(depth[v = edge[e].v] == depth[x] + 1&&(edge[e].w&&able[x]))//DFS
```
就行了 还有一些要注意的点 各位神仙写的时候很容易想到

对了 我用了$set$优化

可去重 可排序 为什么不用呢？

时间复杂度

$O(min(N^{0.67},M^{0.5}) * M*N^2)$ 

时间复杂度不比搜索优秀 但练练网络流也挺好的

```cpp
#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
const int MAXN = 10000;
int n,cnt,ori_[MAXN];
struct node
{
	int v,w,_nxt;
}edge[MAXN],pos_[MAXN];
inline void addedge(int u,int v,int w)
{
	edge[++cnt].v = v;
	edge[cnt]._nxt = ori_[u];
	edge[cnt].w = w;
	ori_[u] = cnt;
}
inline void add(int u,int v,int w) {addedge(u,v,w),addedge(v,u,0);}
set<int> pany;
bool able[MAXN],pr[MAXN];
namespace Dinitz
{
    const int inf = 0x7f7f7f7f;
    int depth[MAXN],fire[MAXN];
    inline bool Bfs(int s,int t)
    {
        memset(depth,-1,sizeof(depth));
        queue<int> q;
        q.push(s),depth[s] = 0;
        while(!q.empty())
        {
            int v,tp = q.front();q.pop();
            for(reg e = ori_[tp];e;e = edge[e]._nxt)
                if(depth[v = edge[e].v] == -1&&(edge[e].w&&able[tp]))
                {
                	depth[v] = depth[tp] + 1,q.push(v);
                	if(edge[e].w >= 50) able[v] = 1;
				}
        }
        return (depth[t] != -1);
    }
    inline int dfs(int x,int t,int _flow)
    {
        if(x == t) return _flow; int v,flow_ = 0;
		for(reg e = fire[x];e;e = edge[e]._nxt)
        {
            fire[x] = e;
            if(depth[v = edge[e].v] == depth[x] + 1&&(edge[e].w&&able[x]))
            {
            	if(edge[e].w >= 50) able[v] = 1;
                int flow = dfs(v,t,min(_flow,edge[e].w));
                _flow -= flow,flow_ += flow;
                edge[e].w -= flow,edge[e ^ 1].w += flow;
                if(!_flow) break;
            }
        }
        if(!flow_) depth[x] = -1;
        return flow_;
    }
    inline int Dinic(int s,int t)
    {
        int ans = 0;
        while(Bfs(s,t))
        {
            for(set<int>::iterator i = pany.begin();i != pany.end();i++) fire[*i] = ori_[*i];
            ans += dfs(s,t,inf);
        }
        return ans;
    }
}
int main()
{
	cnt = 1,n = Read(1);
	for(reg i = 1;i <= n;i++)
	{
		int u = Read(1),v = Read(1),w = Read(1);
		add(u,v,w);
		pany.insert(u),pany.insert(v);
	}
	for(reg i = 1;i <= cnt;i++) pos_[i] = edge[i];
	for(set<int>::iterator i = pany.begin();i != pany.end();i++)
	{
		memset(able,0,sizeof(able));
		memset(pr,0,sizeof(pr));
		set<int> pr_;
		able[*i] = 1;
		int num = 1;
		while(num)
		{
			num = 0;
			for(set<int>::iterator j = pany.begin();j != pany.end();j++)
			{
				if(*i == *j||pr[*j]) continue;
				int max_ = Dinitz::Dinic(*i,*j);
				for(reg k = 1;k <= cnt;k++) edge[k] = pos_[k];
				if(max_ >= 50) pr_.insert(*j),num++,pr[*j] = able[*j] = 1;
			}
		}
		for(set<int>::iterator j = pr_.begin();j != pr_.end();j++) printf("%d %d\n",*i,*j);
	}
	return 0;
}
```

---

## 作者：qhy_ (赞：2)

根据USACO上的分区，这道题应该用DFS

------------


1）思路

1.首先先把一开始能控制的搜出来

2.把能控制的公司对其他公司的股份加起来

3.一直进行第二步，把所有能控制的公司都找出来

------------
code

```
#include <string.h>

#include <iostream>

using namespace std;

const int kMaxN = 100;

int n, t;
int a[101][101]; 
int dont[101];
int com[101]; 

void dfs(int x) { 
  dont[x] = 1; 
  for (int i = 1; i <= n; i++) {
    com[i] += a[x][i];
    if (com[i] > 50) {
      if (dont[i] == 0) {  //判重
        dfs(i);
      }
    }
  }
  return;
}

int main() {
  cin >> t;
  for (int i = 0; i < t; i++) {
    int x, y, k;
    cin >> x >> y >> k;
    a[x][y] += k;
    if (x > n) {
      n = x;
    }
    if (y > n) {
      n = y;
    }
  }
  for (int i = 1; i <= n; i++) {
    memset(dont, 0, sizeof(dont));
    memset(com, 0, sizeof(com));
    dfs(i);         
    for (int j = 1; j <= n; j++) {
      if (com[j] > 50 && i != j) {
        cout << i << ' ' << j << endl;
      }
    }
  }
  return 0;
}
```


---

## 作者：离散小波变换° (赞：2)

## 题目大意

若公司$A,B$满足公司$A$所控制的公司持有$B$的股票总和大于$50\%$或$A=B$则$A$控制$B$。现给出$n$条关系$(i,j,p)$表示公司$i$持有公司$j\ p\%$的股票，求满足$A$控制$B$且$A\not=B$的$(A,B)$。

公司总数小于$100$。

## 题解

虽然代码比较简单，但的确不是一道容易思考的题目。

假设当前各公司的关系为$C_{i,j}$，若$C_{i,j}=1$则公司$i$控制了公司$j$。由题意，$C_{i,i}=1$。

我们设**初始情况**下公司$A$持有公司$B$的股票占比为$P_{i,j}$。每一轮我们先算出**当前这一轮**公司$i$持有公司$j$的股票为$Q_{i,j}$。即：

$$Q_{i,k}=\sum_{C_{i,j}=1}P_{j,k}$$

然后我们根据$Q_{i,j}$来更新$C_{i,j}$。反复操作使得不再产生更新即可。


## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =100+3;
int n,m=100;
int P[MAXN][MAXN],Q[MAXN][MAXN]; bool C[MAXN][MAXN];
int main(){
    n=qread(); up(1,n,i){
        int u=qread(),v=qread(),p=qread();
        P[u][v]+=p;
    }
    up(1,m,i) C[i][i]=true;
    up(1,m,T){
        memset(Q,0,sizeof(Q));
        up(1,m,i) up(1,m,j) if(C[i][j]) up(1,m,k) Q[i][k]+=P[j][k];
        up(1,m,i) up(1,m,j) if(Q[i][j]>50) C[i][j]=true;
    }
    up(1,m,i) up(1,m,j) if(i!=j&&C[i][j]) printf("%d %d\n",i,j);
    return 0;
}
```

---

## 作者：Thaumaturge (赞：2)

思路：
## 一个公司想要通过他控制的公司来控制其他公司的前提是他有控制了的公司
这虽然是句废话，但是我们可以发现：
## 可以先判断某公司直接控制的公司，再考虑其他公司。
所以先以每个公司为基准点出发，遇到能控制的公司就连起来，对它掌控股权的公司进行搜索，结果累加到他的父亲（也就是控制它的公司中），直至在加了一次后发现该公司对刚刚获取股权的公司的股权达到了50%以上，就可以对他继续搜索

~~这不就是dfs吗~~

哦，对了，可能有环的存在，所以对于已经控制的公司就不要再搜了，因为你控制它的那一刻就对他搜索过了。

代码如下：


```cpp
#include <iostream>

using namespace std;

int a[120][120],b[120][120],ak[120][120],a0[120],i,j,k,o,p,q,m;//ak是专门用来标记的，监测每个公司分别掌握了哪些公司的股权来提高查找效率
//b用来标记已经控制的公司来避免死循环
//a用来标记公司之间掌握的股权数,通过累加实现查找 
//a0专门标记每个公司掌握了多少公司的股权 
int fh;//没有返回值也给他安个返回值 

int search(int x,int y){
	for(int w=1;w<=a0[y];w++)
	{
		a[x][ak[y][w]]+=a[y][ak[y][w]];
		if(a[x][ak[y][w]]>=50 && b[x][ak[y][w]]!=1)
		{
			b[x][ak[y][w]]=1;
			fh=search(x,ak[y][w]);
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>o>>p>>j;
		a[o][p]=j;
		ak[o][++a0[o]]=p;
	}

	for(i=1;i<=100;i++)
	{
		b[i][i]=1;
		if(ak[i][1]!=0)
		for(j=1;j<=a0[i];j++)
		{
			if(a[i][ak[i][j]]>=50 && b[i][ak[i][j]]!=1 && i!=ak[i][j])//去重
			{
				b[i][ak[i][j]]=1;
				fh=search(i,ak[i][j]);
			}
		}
	}
	for(i=1;i<=100;i++)
		for(j=1;j<=100;j++)
		if(b[i][j]==1 && i!=j)
		{
			cout<<i<<" "<<j<<"\n";
		}
	return 0;
}
```


---

## 作者：Sarah (赞：2)

这道题可以用BFS
对于每一个节点都bfs一次，入队条件是这个节点是当前正在计算节点的子公司，或者说这个节点被当前节点控制了,每个节点只入队一次即可，话不多说，看代码
```cpp
/*
ID: z8493331
LANG: C++
TASK: concom
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using std::queue;
queue<int> q;
bool con[200][200];
struct Edge{
	int from,to,val,next;
	void init(int f,int t,int v,int pos[],int cnt){
		from=f;to=t;val=v;
		next=pos[from];
		pos[from]=cnt;
	}
};
Edge edges[10005];
int pos[105],cnt=0;
int n;
void init(){
	scanf("%d",&n);
	memset(con,0,sizeof(con));
	memset(edges,0,sizeof(edges));
	for(int i=1;i<=n;i++){
		int x,y,p;
		scanf("%d%d%d\n",&x,&y,&p);
		cnt++;
		edges[cnt].init(x,y,p,pos,cnt);
	}
}
int p_cnt[2000];
void bfs(int s){
	memset(p_cnt,0,sizeof(p_cnt));
	while(!q.empty()) q.pop();
	q.push(s);
	while(!q.empty()){
		int x=pos[q.front()];
		q.pop();
		for(;x;x=edges[x].next){
			p_cnt[edges[x].to]+=edges[x].val;
			if((p_cnt[edges[x].to]>50)&&(!con[s][edges[x].to])){
				q.push(edges[x].to);
				con[s][edges[x].to]=true;
			}
		}
	}
}
void process(){
	for(int i=1;i<=100;i++){
		bfs(i);
	}
	for(int i=1;i<=100;i++){
		for(int j=1;j<=100;j++){
			if(i==j)
				continue;
			if(con[i][j])
				printf("%d %d\n",i,j);
		}
	}
}
int main(){
	freopen("concom.in","r",stdin);
	freopen("concom.out","w",stdout);
	init();
	process();
	return 0;
}
```

---

## 作者：ws_fuweidong (赞：2)

其实这样能够通过中间点更新状态的题可以考虑Floyd算法

但要写成递归的形式（因为有环）






```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[105][105]={0};
bool con[105][105]={0};
int n,m=0;
void dfs(int i,int j)
{
    if (con[i][j]) return;    
    con[i][j]=true;
    for (int k=1;k<=m;k++)
    {
        a[i][k]+=a[j][k];
        if (a[i][k]>50) dfs(i,k); 
    }
}
int main()
{
    int u,v,w;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>u>>v>>w;
        a[u][v]=w;
        if (u>m) m=u;
        if (v>m) m=v;
    }
    for (int i=1;i<=m;i++) 
        for (int j=1;j<=m;j++)
        if (a[i][j]>50) dfs(i,j);
    for (int i=1;i<=m;i++)
        for (int j=1;j<=m;j++)
        if (i!=j && con[i][j]) 
        printf("%d %d\n",i,j);
    return 0;
}
```

---

## 作者：endless_loop (赞：1)

**这题如果不加思考直接用 dfs 一定会错。**

为什么会这样呢，于是我们画了张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fdwgsggn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这张图里节点 $1$ 控制了节点 $2,6$，节点 $2,6$ 又同时控制了节点 $3$，同时节点 $3$ 有节点 $5$ 的 $30\%$ 股票，显然节点 $1$ 是无法控制节点 $5$ 的，但我们的dfs程序会将节点 $3$ 有节点 $5$ 的 $30\%$ 股票同时传递给节点 $2,6$ 让节点 $1$ 有 $60\%$，因此出错。

简单来说就是直接用 dfs 会**重复统计**。

于是我们考虑换一种 dfs 的策略，先考虑能直接控制的公司，然后打上标记，防止再被统计，于是我们就 AC 了这道题。

方法慢了点，但易理解很多。
```
#include<iostream>
#include<vector>
using namespace std;
int G[200][200],control[1000][1000];
//G代表初始情况，control[i][j]代表i实际上有j的control[i][j]的股票
bool vis[1000][1000];
void dfs(int u,int v){
	vis[u][v]=1;
	for(int i=1;i<=100;++i){
		control[u][i]+=G[v][i];
		if(control[u][i]>50&&!vis[u][i])
			dfs(u,i);
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
		int u,v,dis;
		cin>>u>>v>>dis;
		G[u][v]=dis;
		control[u][v]=dis;
	}
	for(int i=1;i<=100;++i)
		for(int j=1;j<=100;++j)
			if(i!=j&&G[i][j]>50&&!vis[i][j])//如果超过50才有可能更新
				dfs(i,j);
	for(int i=1;i<=100;++i)
		for(int j=1;j<=100;++j)
			if(i!=j&&control[i][j]>50)cout<<i<<" "<<j<<endl;
	return 0;
} 
```

蒟蒻第一次交题解，有错误请指出哦

---

## 作者：你祖奶我很ok (赞：1)

原题戳这儿——>[原题](https://www.luogu.com.cn/problem/P1475)

题解来源戳这儿——>[题解](https://blog.csdn.net/Akatsuki__Itachi/article/details/82503438)

类似Floyd找可达路径，不过这题有环，所以在Floyd外面再加一个循环，当不再有点更新的时候，就可以跳出了。


```cpp

#include<iostream>

#include<cstdio>

#include<cstring>

#include<cmath>

#include<algorithm>

#include<queue>

#define memset(a,v)  memset(a,v,sizeof(a))

#define eps 1.0E-8

using namespace std;

const int MAXL(100);

const int INF(0x3f3f3f3f);

const int mod(1e9+7);

typedef long long int LL;

int a[MAXL+50][MAXL+50];

bool is[MAXL+50][MAXL+50];//判断i是否包含j

int main()

{

    int n;

    cin>>n;

    for(int i=1; i<=n; i++)

    {

        int x,y,z;

        cin>>x>>y>>z;

        a[x][y]=z;

        if(z>50)

            is[x][y]=true;

    }

    while(true)

    {

        int loop=0;

        for(int i=1; i<=100; i++)

        {

            for(int j=1; j<=100; j++)

            {

                if(i==j) continue;

                if(!is[i][j])

                {

                    int temp=0;

                    for(int k=1; k<=100; k++)

                        if(is[i][k]!=0||i==k) temp+=a[k][j];//i==k的时候代表还要找自己所含的子公司。

                    if(!is[i][j]&&temp>50)

                        loop=1,is[i][j]=true;

                }

 

            }

        }

        if(!loop) break;//当没有点可以更新的时候，跳出即可。

    }

    for(int i=1; i<=100; i++)

        for(int j=1; j<=100; j++)

            if(i!=j&&is[i][j]==true)

                cout<<i<<" "<<j<<endl;

}

 

```


---

## 作者：LikeJ (赞：1)

## ***控制公司***
**题目描述**
有些公司是其他公司的部分拥有者，因为他们获得了其他公司发行的股票的一部分。(此处略去一句废话）据说，如果至少满足了以下三个条件之一，公司A就可以控制公司B了：
公司A = 公司B。
公司A拥有大于50%的公司B的股票。
公司A控制K(K >= 1)个公司，记为C1, ..., CK，每个公司Ci拥有xi%的公司B的股票，并且x1+ .... + xK > 50%。
给你一个表，每行包括三个数(i,j,p)；表明公司i享有公司j的p%的股票。计算所有的数对(h,s)，表明公司h控制公司s。至多有100个公司。
写一个程序读入N组数(i,j,p)，i,j和p是都在范围(1..100)的正整数，并且找出所有的数对(h,s)，使得公司h控制公司s。
**输入格式**
第一行： N，表明接下来三个数的数量，即(i,j,p)的数量。
第二行到第N+1行： 每行三个整数作为一个三对数(i,j,p)，表示i公司拥有j公司 p%的股份。
**输出格式**
输出零个或更多个的控制其他公司的公司。每行包括两个整数A、B,表示A公司控制了B公司。将输出的数对以升序排列。
请不要输出控制自己的公司(应该是不输出自己，互相控制的公司还是要输出的）。
**输入输出样例**
**输入**
3
1 2 80
2 3 80
3 1 20
**输出** 
1 2
1 3
2 3
**分析**
这题我们直接用深搜（DFS）
搜下去就行了
**注意自己虽然可以控制自己，但不能输出来**
**AC代码**
```cpp
#include<iostream>
#include<cstring> 
using namespace std;
int m,n,x,y,k,a[105][105],f[105][105],b[105],c[105];
void dfs(int x,int y)
{
	if(c[y]==1)return;//判断是否搜过
	c[y]=1;//标记 
	for(int i=1;i<=n;i++)
	{
		b[i]+=a[y][i];//加股份
		if(b[i]>50)//大于50，不是大于等于50
		{
			f[x][i]=1;//说明可以控制
			dfs(x,i);//搜下去
		}
	}
}
int main()
{
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>k;
		a[x][y]=k;
		n=max(n,max(x,y));//这并不是
	}
	for(int i=1;i<=n;i++)
	{
		memset(b,0,sizeof(b));//清空
		memset(c,0,sizeof(c));
		dfs(i,i);
	}
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=n;j++)
	  if(f[i][j]&&i!=j)cout<<i<<' '<<j<<endl;//判断输出
}
```
## ***谢谢***


---

## 作者：Jasonggg15 (赞：1)

**本人蒟蒻，不足之处望包容**

数据比较水，最大的公司编号较小，因此可以开两个一维数组，一个标记，一个计数，用dfs苟过

奉上代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
int n,f[1005][1005],mx,x,y,k,sum[1005],check[1005];
//f[i][j]记录公司i拥有公司j的股票
void wjl(int now)
{
    if(check[now]) return;
    else check[now]=1;//标记找过
    for(int i=1;i<=mx;i++)
    {
        sum[i]+=f[now][i];
        if(sum[i]>50)wjl(i);
		//公司now控制公司i，公司now拥有每一个公司的股票要加上公司i拥有所对应公司的股票
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y>>k;
        f[x][y]=k;
        mx=max(mx,max(x,y));//记录最大的公司编号
    }
    for(int i=1;i<=mx;i++)//控制公司升序排列，1到mx
    {
    	memset(sum,0,sizeof(sum));//清零数组sum
        memset(check,0,sizeof(check));//清零数组check
        wjl(i);
        for(int j=1;j<=mx;j++)//被控制公司升序排列，1到mx
        {
        	if(sum[j]>50&&i!=j) cout<<i<<" "<<j<<endl;//公司i控制公司j，输出数对(i,j)
        }
    }
    return 0;
}
```
~~管理员大大给过啊啊啊~~

---

## 作者：ttq012 (赞：0)

这一个题目我们可以使用一个图来代表控股关系，如果有一条边是从 $a$ 点连向 $b$ 点的，那么就可以认为，$a$ 公司被 $b$ 公司控制。

如果 $a$ 公司被 $b$ 公司控制，而且 $b$ 公司被 $c$ 公司控制，那么就说明：$a$ 公司被 $c$ 公司控制了。

这个时候我们就可以发现，这个题目可以使用并查集求解了。

---

## 作者：Snow_Dreams (赞：0)

这道题可以用图论去做

观察一下样例：
```cpp
3
1 2 80
2 3 80
3 1 20
```
不难发现其实它有点像图论中的加边，边权为第三个数

然后这道题的n<=100

然后可以通过邻接矩阵存图，然后用floyd直接去求最短路，然后如果有一条有向边的边权大于50，就输出，并把编号改变，用并查集思想，把两个公司合并在一起就好了

---

