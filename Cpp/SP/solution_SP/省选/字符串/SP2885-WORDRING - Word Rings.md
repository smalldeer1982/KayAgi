# WORDRING - Word Rings

## 题目描述

如果字符串A的**结尾两个**字符与字符串B的**开头两个**字符相匹配，我们称A与B能 **“ 相连 ”** ( 注意：A与B能相连，不代表B与A能相连 ) 

 当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算） 

 我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长     
 
```
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```

如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( **首尾重复部分需计算两次** ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

## 样例 #1

### 输入

```
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0```

### 输出

```
21.66```

# 题解

## 作者：哲学家 (赞：14)

## Word rings
### **[题目描述](https://www.luogu.com.cn/problem/SP2885)**

### 题目大意
这道题就是想求出所有的环，然后在所有环中比较出环串的平均长度最长的那一个，然后就输出平均长度最长的，如果在一个点当中的样例中没有环的话我们就应该输出“**No Sulution.**”


------------

### - 注意是No Sulution.（没有句点就会wa）


------------

- 首先我们的思路应该是跑最长路，因为无论我们想求平均长度最长，我们肯定希望每一个都非常长，刚好边权为字符串长度，那么跑一下当正环出来之后就跑不出来了。**但是这题数据太大了我们过不了**

- 当我们首先用枚举环来求出答案士失败时那么我们接下来的思路应该是尝试枚举答案，然后求出是否有满足答案的环，但若我们此时枚举的答案为ans，有k个字符串，那么就有了这样一个式子ans∗k=len1+len2+len3+...+lenkans∗k=len1+len2+len3+...+lenk

- 在我们得到那道这个式子之后，我们对它进行必要的移项

len1−ans+len2−ans+len3−ans+...+lenk−ans=0

- 所以说我们可以得到对于满足以下式子，也可以判断是否是正环

0≤len1−ans+len2−ans+len3−ans+...+lenk−ans0

- 那么对于这个ans值，ans值越大，那么存在正环的概率也就越小，当ans值越小时，ans大的情况肯定也会包含在里面，这就保证了单调性，我们在确定这个方法的单调性之后我们就可以直接使用二分答案来做这道题了。

- 对于最长路的求解我们应该使用Dijkstra对此进行判断正环（因为Dijkstra不能处理负数情况，时间的复杂度比较低），但是我们也可以用SPFA来判正环（我们可以将每一条边的权值乘以负一），然后我们再加一个spfa优化就可以了。

### 补充

在这里讲一下如何进行缩点，在题目中我们不难发现对于一串字符串来说只有首尾的各两个数字是有用的，其他的字符我们可以忽略不计，但是我们学要用一下哈希来使我们的aa到zz中间的所有的字符不会冲突，（第一位可以乘以26，第二位用1到25表示，那么我们得到的那个数整除26的和然后再+1就代表第一个字符在a到z中的第几个位置，之后我们可以再用那个数模26然后再+1就代表第二个字符在a到z中的第几个位置）这样可以保证不会出现冲突了。

直接把一个字符串当中的首尾各两个字符变为两个点整个字符串的长度为我们的边权建立一条边这样就可以进行建边用spfa就可以解决了。

------------

### 好题推荐
（**spfa的优化的题目**）
- **[【例 1】Word Rings](http://ybt.ssoier.cn:8088/problem_show.php?pid=1504)**

- **[【例 2】双调路径](http://ybt.ssoier.cn:8088/problem_show.php?pid=1505)**

- **[【练习1】最小圈](http://ybt.ssoier.cn:8088/problem_show.php?pid=1506)**

- **[【练习2】虫洞 Wormholes](http://ybt.ssoier.cn:8088/problem_show.php?pid=1507)**

- **[【练习3】Easy SSSP](http://ybt.ssoier.cn:8088/problem_show.php?pid=1508)**


------------

## 代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
const int N=100005;
const double eps=1e-6;//分度值
int n;
char s[1005];
int ord(char a,char b) {//是有用的开头和结尾的两个字符全都不冲突
	return (a-'a')*26+b-'a';
}
int lnk[N],ne[N],la[N],co[N],tot;
double dis[N];
bool vis[N];
void add(int x,int y,int z) {//链式前向星
	ne[++tot]=y;
	co[tot]=z;
	la[tot]=lnk[x];
	lnk[x]=tot;
}
bool dfs(int x,double v) {//dfs优化的spfa算法（模板）
	vis[x]=1;
	for(int j=lnk[x]; j; j=la[j]) {
		if(dis[ne[j]]<dis[x]+co[j]-v) {
			dis[ne[j]]=dis[x]+co[j]-v;
			if(vis[ne[j]])return 1;
			else {
				if(dfs(ne[j],v))return 1;
			}
		}
	}
	vis[x]=0;
	return 0;
}
bool check(double mid) {//检查是否成环
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	for(int i=0; i<=5000; ++i)
		if(dfs(i,mid))return 1;
	return 0;
}
int main() {
	while(cin>>n) {//有多组数据
		memset(lnk,0,sizeof(lnk));
		tot=0;
		if(n==0){
			return 0;//结束程序
		}
		for(int i=1; i<=n; ++i) {//预处理
			scanf("%s",s+1);//使char类型的数组从s【1】开始输出直接跳过s【0】
			int l=strlen(s+1);//抛弃中间没用的字符只记录整个字符串的长度
			add(ord(s[1],s[2]),ord(s[l-1],s[l]),l);
		}
		double l=0,r=1005;
		while(r-l>eps) {//二分答案（用eps来确定分度值，esp=1e-6即是精确到小数点后六位）
			double mid=(l+r)/2;
			if(check(mid))l=mid;
			else r=mid;
		}
		if(l==0)cout<<"No solution."<<endl;//输出答案
		else cout<<l<<endl;
	}
}
```

---

## 作者：ELLIAS (赞：7)

### SPFA
本题求平均环长,可以将每个字符串的前后两个字符看做点,这两个点存在于一个字符串的关系视为一条边,接着二分枚举答案(单调性是很显然的),用队列优化BellmanFord判断即可.
关键代码:
```cpp
static bool __fastcall spfa_dfs (Re int fr, Re double mid)
{
	vis[fr] = true;
	register int to;
	for (Re int i = head[fr]; i; i = nxt[i])
	{
		to = too[i];
		if (dis[fr] + wei[i] - mid > dis[to])
		{
			dis[to] = dis[fr] + wei[i] - mid;
			if (vis[to] || spfa_dfs(to, mid))
				{vis[fr] = false; return true;}
		}
	}
	vis[fr] = false; return false;
}
```
```cpp
inline bool judge (register double mid)
{
	memset (dis, 0, sizeof dis);
	for (Re int i = 1; i <= hhsh; ++ i)
		if (spfa_dfs (i, mid)) return true;
	return false;
}
```
```cpp
while (true)
	{
		n = read (); if (!n) return 0;
		memset (head, 0, sizeof head);
		memset (hash, 0, sizeof hash);
		ecnt = hhsh = 0;
		while (n --)
		{
			c = gc(), len = 0;
			while (c == '\n' || c == '\r') c = gc ();
			while ((c != '\n') && (c != '\r')) s[++ len] = c, c = gc();
			fr = calc(s[1], s[2]), to = calc(s[len-1], s[len]);
			if (!hash[fr]) hash[fr] = ++ hhsh;
			if (!hash[to]) hash[to] = ++ hhsh;
			addedge (hash[fr], hash[to], len);
		}
		l = 0.0, r = 1000.0;
		while (r - l >= eps)
		{
			mid = (l + r) / 2;
			if (judge(mid)) l = mid;
			else r = mid;
		}
		if (l == 0) puts ("No solution.");
		else printf ("%.2lf\n", l);
	}
```
祝大家 ```RP++``` !

---

## 作者：EBeason (赞：6)

# **算法：SPFA**


  ------------

  ### **题目大意：**
   基本是要把单词都串成一个环，输出一个平均长度最长的环  
   （注意：平均长度是把所有的环加起来除个数）。  
   
------------

  ### **思路分析：**

   刚看始开题会的觉得没什么思路，仔细一看其实可以把两边的字符看成点，长度看成边，这么一连转化成了一道图论题，求平均最长的 环,我们可以用 ~~BFS 优化的的 SPFA~~ 来求最短路的问题，这里我用的是 DFS 优化的 SPFA 。


  ### **具体分析：**
   我们如何来保存这个点呢？？


  ------------

  点：把字符当成$26$进制，这样就可以得到$1000$以内的点。


  ------------
  边：边处理更简单了，长度即使边长。
  ```cpp
  void add1(ll x,ll y,long double w)
  {
  	  nex[++tot]=fir[x];fir[x]=tot;go[tot]=y;ww[tot]=w;
  }
  ```
  这是图论中基本存边的方式。


  ------------
  接下来就是重要的部分了；我们没有什么好的方法来求平均最长的方法，但我们可以用 dfs 很好的判断是否有环。

  我们用 $l_1$ 来表示第一条边，$l_2$ 第二条等等。  
  
平均数 $\bar{l}=\Large\Large\frac{l_1+l_2+l_3+...+l_N}{N}$。

即  
$(l_1-\bar{l})+(l_2-\bar{l})+(l_3-\bar{l})+...+(l_N-\bar{l})=\large\sum_{i=1}^{N}(l_i-\bar{l})=0$


  我们可以直接在1000内用二分查找的办法找在每条边减去当前平均值   情况下是否存在一个正环，如果有则 ```l=mid``` ，否则 ```r=mid``` 。

------------
  ```cpp
  long double l=1,r=1000,best=-1,mid，jd=0.001;
  while(l+jd<r)//0.001用来精度处理，避免程序死循环。
  {
	  mid=(l+r)/2;
	  if(sovle(mid))
	  {
		  best=mid;
		  l=mid;
	  }
	  else 
          r=mid;
  }
  if(best==-1) printf("No solution.\n");
  else printf("%.2Lf\n",best);
  ```

  ```jd``` 可以巧妙地解决精度问题。


------------
  ### **SPFA部分：**


  ```solve``` 函数主要就是确定在当前平均值的情况下，存在不存在大于等于此平均值的正环。

  ```cpp
  void spfa(ll x,ll fa,long double w)
  {
	  if(PC) return;//如果有环就返回
	  pd[x]=fa;
	  for(int i=fir[x];i;i=nex[i])//循环找边
	  {
		  ll v=go[i];
		  if(d[x]+ww[i]-w>d[v])// 注意这个w一定要全部减去目前  这个平均值
		  {
			  d[v]=d[x]+ww[i]-w;
			  if(d[v]>maxedge){PC=1;return;}//边已经超过所有  边的和，有环。
			  if(!pd[v])
			  spfa(v,fa,w);
			  if(PC) return;
			  else if(pd[v]==fa)//如果已经第二次来这个地方返  回
			  {
				  PC=1;
				  return;
			  }
		  }
	  }
	  pd[x]=0;//回溯
  }
  bool sovle(long double x)
  {
	  PC=0;
	  memset(d,0,sizeof(d));
	  memset(pd,0,sizeof(pd));
	  for(int i=1;i<=702;i++)//不是从每个点都可以找到一个正环，要从每个点试一试。
	  {
	  spfa(i,i,x);
	  if(PC)
	  break;
	  }
	  return PC;
  }
  ```
  这道题就差不多完成了，下面直接上代码。

  ------------

  ### **代码部分：**
  ```cpp
  #include<cstdio>
  #include<iostream>
  #include<string>
  #include<cstring>
  using namespace std;
  #define ll long long
  const int MaxM=1e5+100;
  const int MaxN=1e3+10;
  const long double inf=1e9+10;
  const long double jd=0.001;
  ll N,maxedge,top,PC,pd[MaxN],yw[MaxN];
  ll fir[MaxM],nex[MaxM],go[MaxM],tot;
  long double ww[MaxM],d[MaxN];
  void add1(ll x,ll y,long double w)
  {
	  nex[++tot]=fir[x];fir[x]=tot;go[tot]=y;ww[tot]=w;//添加边的基本模板
  }
  void spfa(ll x,ll fa,long double w)
  {
	  if(PC) return;
	  pd[x]=fa;
	  for(int i=fir[x];i;i=nex[i])
	  {
		  ll v=go[i];
		   if(d[x]+ww[i]-w>d[v])
		  {
			   d[v]=d[x]+ww[i]-w;
			  if(d[v]>maxedge){PC=1;return;}//边已经超过所有边的和，有环。
			  if(!pd[v])
			  spfa(v,fa,w);
			  if(PC) return;
			  else if(pd[v]==fa)//如果已经第二次来这个地方返回
			  {
				  PC=1;
				  return;
			  }
		  }
	  }
	  pd[x]=0;
  }
  bool sovle(long double x)
  {
	  PC=0;
	  memset(d,0,sizeof(d));
	  memset(pd,0,sizeof(pd));
	  for(int i=1;i<=702;i++)//从所有点开始搜索
	  {
	  spfa(i,i,x);
	  if(PC)
	  break;
	  }
	  return PC;
  }
  int main()
  {
	  while(scanf("%lld",&N)&&N)
	  {
		  maxedge=0;
		  memset(fir,0,sizeof(fir));tot=0;top=0;
		  for(int i=1;i<=N;i++)//处理边和点
		  {
			  string ss;
			  cin>>ss;
			  ll len=ss.size();
			maxedge=max(maxedge,len);
			ll x=(ss[0]-'a'+1)*26+ss[1]-'a'+1;//26进制保存点
			ll y=(ss[len-2]-'a'+1)*26+ss[len-1]-'a'+1;
## 			yw[x]=1;yw[y]=1;
			long double lg=len;//把边开成实数型的
			add1(x,y,lg);
		  }
		  maxedge*=N;//所有边和的最大值
		  long double l=1,r=1000,best=-1,mid;
		  while(l+jd<r)
		  {
			  mid=(l+r)/2;
		  	  if(sovle(mid))
			  {
				  best=mid;
				  l=mid;
			  }
			  else r=mid;
		  }
		  if(best==-1) printf("No solution.\n");
		  else printf("%.2Lf\n",best);
	  }
	  return 0;
  } 

  ```

---

## 作者：Eleven谦 (赞：4)

# Wordring
[题目传送门](https://www.luogu.com.cn/problem/SP2885)

#### 前言

说实话，这题一看我还真没思路（是我太菜）

在草稿本上写写画画了一点时间，就有了一点思路，好了，开始讲题

#### 算法

二分答案 & $SPFA$（$dfs$版）

------------
#### $SPFA$

没思路，就来看样例，如图：

![](https://img2020.cnblogs.com/blog/2055990/202007/2055990-20200704155816047-1037238146.png)

我们发现，两个能相连的字符串$A$、$B$，**看的只有$A$的前后两个字符和$B$的前后两个字符**，中间的冗余字符其实并不重要，因为我们**需要的只是整个字符串的长度**而已

所以我们何必留下冗余无用的字符呢？所以我们可以把上图简化为下图（有点丑，见谅啊qwq）：

![](https://img2020.cnblogs.com/blog/2055990/202007/2055990-20200704160252180-518415863.png)

有点图论的思路了吗？

即：

1. 将每个字符串的前两个字符和后两个字符当做一个节点

2. 将每个字符串的长度当做这两个节点的边权，然后将它们连起来

于是我们就构建出了如上的图（2）

那么剩下的就是找环了，这时我们一般会想到：遍历整个图，找到每一个环，然后算出它们的平均值，最后比较出最大值

但是这题多组数据，还不说图的大小，所以这种思路肯定会T飞的

那怎么做？——不能找环，那我们就直接找答案啊！（这里要转换一下思想）

找实数域的答案，那第一个想到的肯定就是**实数域上的二分答案！**

------------
#### 二分答案

不懂的，可以看看[二分答案的讲解](https://www.cnblogs.com/Eleven-Qian-Shan/p/13187609.html)

然后这里我们直接来讨论为什么以及怎么二分答案

我们能将求答案$ans$的式子表示如下：

$ans=(len_1+len_2+len_3+···+len_k)/K$

数学转换一下：

$ans*K=len_1+len_2+len_3+···+len_k$

移项一下：

$(len_1+len_2+len_3+···+len_k)+ans*k=0$

最后我们可得：

$(len_1-ans)+(len_2-ans)+(len_3-ans)+···+(len_k-ans)≥0$

为什么是$≥$？因为最开始的式子是整除，会有精度问题，所以是$≥$

------------
#### 代码$Code$

好了，二分答案和$SPFA$的思路就是如上这么多了，现在贴一发代码吧

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
double ans,dis[520010];
int n,tot,vis[520010],head[520010];

struct node {
	int to,net,val;
} e[520010];

inline void add(int u,int v,int w) {
	e[++tot].to=v;
	e[tot].val=w;
	e[tot].net=head[u];
	head[u]=tot;
}

inline bool dfs(int now,double x) {  //dfs版的SPFA 
	vis[now]=1;
	for(register int i=head[now];i;i=e[i].net) {
		int v=e[i].to;
		if(dis[v]<dis[now]+e[i].val-x) {
			dis[v]=dis[now]+e[i].val-x;
			if(vis[v]==1||dfs(v,x)==true) return true;
		}
	}
	vis[now]=0;
	return false;
}

inline bool check(double x) {
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	for(register int i=1;i<=1000;i++) {
		if(dfs(i,x)==true) return true;
	}
	return false;
}

int main() {
	while(scanf("%d",&n)) {
		if(n==0) break;
		tot=0;
		memset(head,0,sizeof(head));
		for(register int i=1;i<=n;i++) {
			cin>>s;
			int len=s.length();
			int u=(s[0]-'a')*26+(s[1]-'a')+1;  //将字符转换为节点连边 
			int v=(s[len-2]-'a')*26+(s[len-1]-'a')+1;
			add(u,v,len);
		}
		double l=0,r=1000;
		while(r-l>1e-4) {  //二分答案 
			double mid=(l+r)/2.0;
			if(check(mid)==true) {
				l=mid;
			}
			else r=mid;
		}
		if(l==0) puts("No solution.");
		else printf("%.2lf\n",l);
	}
	return 0;
} 
```


------------

最后，如果这篇题解有任何问题或您有任何不懂，欢迎在下面留言区评论，我会及时回复、改正，谢谢各位dalao啊qwq

------------






---

## 作者：Polar_Night (赞：4)

这道题目看第一眼的确想不到用最短路做~~可能是我太弱了~~  
但确实是SPFA解决的  
我们把头部的两个字母和尾部的两个字母映射成两个节点，然后建图。  
比如"abcabc"，就是点“ab”到点“bc”有一条长为6的边  
这样我们就只用求图中找一个边权平均值最大的正环。  
很朴素的做法：  
由于Average=(dist[1]+dist[2]+...+dist[k])/k  
所以Average*k=dist[1]+dist[2]+...+dist[k]  
即（dist[1]-Average）+(dist[2]-Average)+...+(dist[k]-Average)=0  
另外注意到上式中的等于号可以改写为小于等于，那么我们可以二分答案ans，然后判断是否存在一组解满足（dist[1]+dist[2]+…..+dist[k]）/k>ans,即判断
（dist[1]- ans）+（dist[2]- ans）+….+ （dist[k]- ans）>0  
二分答案后，更新边权。  
**PS：数据有点大，小心RE！！本人被坑多次。**   
详细代码如下：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100001;
struct node
{
    int to;
    int len;
    node(int tt,int ll)
    {
        to=tt;
        len=ll;
    }
    node()
    {
    }
};
vector <node> g[N];
int n;
bool flag[N];
double dis[N];
char s[N];
void init()
{
    for(int i=1;i<=n;i++)
        g[i].resize(0);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        if(len==1)
            continue;
        int a=(s[0]-'a')*26+s[1]-'a'+1;
        int b=(s[len-2]-'a')*26+s[len-1]-'a'+1;
        g[a].push_back(node(b,len));
    }
    return;
}
bool spfa(int id,double aver)
{
    flag[id]=true;
    int size=g[id].size();
    for(int i=0;i<size;i++)
    {
        int to=g[id][i].to;
        int len=g[id][i].len;
        if(dis[to]<dis[id]+len-aver)
        {
            dis[to]=dis[id]+len-aver;
            if(flag[to] || spfa(to,aver))
            {
                flag[to]=false;
                return true;
            }
        }
    }
    flag[id]=false;
    return false;
}
bool find(double mid)
{
    memset(dis,0,sizeof(dis));
    memset(flag,0,sizeof(flag));
    for(int i=1;i<=100000;i++)
    {
        if(spfa(i,mid))
            return true;
    }
    return false;
}
int main()
{
    while(scanf("%d",&n))
    {
        if(n==0)
            break;
        init();
        double l=0.0,r=100000000.0;
        while(r-l>=0.0001)
        {
            double mid=(l+r)/2;
            if(find(mid))
                l=mid;
            else
                r=mid;
        }
        if(l==0)
            printf("No solution.\n");
        else
            printf("%.2lf\n",l);
    }
    return 0;
}
```  
希望大家能早日过此题。

---

## 作者：Space_Gold_Trash (赞：3)

这道题很显然是一个最短路

毕竟搜索时间复杂度太高(或者我太弱无法剪枝

那么我们就要想办法转化成一个图

## 关于建图

显而易见,以每一个子串做节点来建图

那我们以什么为边呢？

显然是子串的长度

## 关于如何跑最短路？

我做题的历程:

思路1:

我们只要找出所有环然后求出平均值再一一比较就是了

但是似乎有点麻烦,时间复杂度也有些看不过去

思路2:

根据思路1改编

对只有一个节点的环,特判就是了

对于有两个以上节点的环,我们就弄一下$af_{ij}+bf_{ji}$就是了

$af_{ij}$  //最长路

$bf_{ij}$  //次长路

但是一个节点只能使用一个,我们的最长路和次长路可能经过同一个点,直接WA

思路3:

貌似找出环然后求出答案的思路有点不行

但是我们可以找出答案然后求出环试试

我们枚举答案然后求出是否有环

那怎么求出是否有环?

$ans*k=len_1+len_2+\dots+len_k$

那么我们稍稍变化一下



$0\leq len_1-ans+len_2-ans+\dots+len_{k}-ans$

这就是$ans$符合条件的情况

那么就变成了一个判断正环的题

正环怎么判断,做省选+的题了肯定知道吧
```
#include<bits/stdc++.h>
#define N 100011
using namespace std;
int n;
string s[N];
int len[N];
double dis[N];
vector<int>to[N];
inline void build(int x,int y){
	to[x].push_back(y);
}
inline void check(int i,int j){
	if(s[i][len[i]-1]==s[j][1]&&s[i][len[i]-2]==s[j][0])build(i,j);
}
bool vis[N];
inline bool dfs(int x,double mid){
	vis[x]=1;
	int y;
	vector<int>::iterator i;
	for(i=to[x].begin( );i!=to[x].end( );++i){
		y=*i;
		if(dis[y]<dis[x]+len[y]-mid){
			dis[y]=dis[x]+len[y]-mid;
			if(vis[y]||dfs(y,mid))return 1;
		}
	}
	return vis[x]=0;
}
inline bool find(double k){
	int i;
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	for(i=1;i<=n;++i)
	if(dfs(i,k))return 1;
	return 0;
}
inline void pre( ){
	scanf("%d",&n);
	if(!n)exit(0);
	int i,j,ans=-1;
	for(i=1;i<=n;++i)to[i].clear( );
	for(i=1;i<=n;++i){
		cin>>s[i];
		len[i]=s[i].size( );
	}
	for(i=1;i<=n;++i)
	for(j=1;j<=n;++j)
	check(i,j);
	double mid;
	double l=0,r=1e8;
	while(r-l>1e-3){
		mid=(l+r)/2;
		if(find(mid))l=mid;
		else r=mid;
	}
	if(l==0)puts("No solution.");
	else printf("%.2f\n",1.0*int(l*100)/100.0);
}
int main( ){
	while(1)pre( );
}
```

---

## 作者：Rainsleep (赞：2)

**前置芝士：分数规划、二分、正环**

## $\text{Solution}$

### 数据范围
+ $n \le 10^5$
+ $1 \le |s| \le 1000$

默认读者已经充分理解题意。

+ 以下设共有最优方案中 $k$ 个字符串。

实际上从题目给定的要求中，我们可以抽象出一个表达式，使其最大：

$$\dfrac{\sum |s|}{k}$$

问题就转化成了分数规划的经典模型，考虑对于分数规划问题的经典解法，即二分分数值。

### 建图

首先考虑建图的策略，比较显然的想法是将每个字符串单独视为一个节点，若两个字符串可以相连，则在两点之间连边。这样建图的点数为 $10^5$，边数即为最劣情况下完全图的边数，即约 $10^{10}$，这样的边数无论是空间上还是时间上都是显然难以承受的。

考虑这样一种新的建图策略，将每个字符串当作是一条边：
+ 左端点为字符串的首两位字符
+ 右端点为字符串的末两位字符
+ 边权即为 $|s|$

得益于我们并不关心字符串中除了首尾两位的其他字符，所以该建图方法是可取的。

对于每个点的两个字母来说，每一位我们都有 $26$ 种选择，所以这样建图的点数即为 $26^2 = 676$，对于边数来说，即约 $676^2=456976$。相比于之前，时空复杂度都大大进行了降低。

### 分数规划

按照分数规划的经典解法，我们对分数值进行二分，以下约定二分值为 $mid$。

对于：

$$\dfrac{\sum |s|}{k}$$

我们首先考虑出答案的范围：
 + 本题目中边权都为正，且不能不选字符串（下界）
 + 我们对于该分数的最大情况，即分子最大，分母最小，可以得到为 $\dfrac{1000}{1} = 1000$
 
二分值域即为 $(0,1000]$。

对于原分数进行二分，即有：

$$\dfrac{\sum |s|}{k} > mid$$
$$\sum |s| > mid \times k$$
$$\sum |s| - mid \times k>0$$

于是问题就转化为在图上跑正环的问题了。

#### 无解

考虑对于当前柿子来讲，左侧有最大取值当且仅当 $mid=0$，若此时图中仍然跑不出正环，则无解。

#### 一些Trick

+ 处理首末两位字母时，直接转化为一个 $26$ 进制的数字处理即可。
+ 当松弛操作的次数超过 $2 \times n$ 时，我们可以武断的认为，该图存在负环，根据经验来看，这样可以让程序运行效率大大提高，但是笔者不保证不被卡。例如本题，两种做法的时间整整差出了 $1.54s$。~~玄学~~

![](https://cdn.luogu.com.cn/upload/image_hosting/zh7pj58v.png)

下面就是代码啦，展示版本为无玄学判负环版：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 910;
const int M = N * N;
const int S = 1010;
const double eps = 1e-4;

int n, m;
int head[N], idx = 0;

struct Edge
{
    int to, nxt;
    int w;
} edges[M];

inline void link(int a, int b, int w)
{
    ++ idx;
    edges[idx] = {b, head[a], w};
    head[a] = idx;
    return ;
}

char str[S];
bool state[N];
double dist[N];
int cnt[N];

inline bool check(double mid)
{
    queue<int>q;
    for(int i(0);i < 676; ++ i) // 即使有点不存在，因为该点无连边，所以不影响答案。
    {
        q.push(i);
        state[i] = true;
        dist[i] = cnt[i] = 0;
    }
    int anc = 0;
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        state[t] = false;
        for(int i(head[t]);i;i = edges[i].nxt)
        {
            int to = edges[i].to;
            int w = edges[i].w;
            if(dist[to] < dist[t] + w - mid)
            {
                dist[to] = dist[t] + w - mid;
                cnt[to] = cnt[t] + 1;
                if(cnt[to] >= N)
                    return true;
                //if ( ++ anc > 10000) return true; // 经验上的trick
                if(!state[to])
                {
                    q.push(to);
                    state[to] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    while(scanf("%d", &n) and n)
    {
        memset(head, 0, sizeof head);
        idx = 0;
    
        for(int i(1);i <= n; ++ i)
        {
            scanf("%s", str);
            int len = strlen(str);
            if(len >= 2) // 当字符串长度不足2时，一定无法连接任何一个字符串。
            {
                int left = (str[0] - 'a') * 26 + str[1] - 'a';
                int right = (str[len - 2] - 'a') * 26 + str[len - 1] - 'a';
                link(left, right, len);
            }
        }
        
        if(!check(0)) // mid最小还跑不出正环就无解
        {
            puts("No solution.");
            continue;
        }
        
        double l = 0.00, r = 1010.00;
        while(r - l > eps)
        {
            double mid = (l + r) / 2;
            if(check(mid))
                l = mid;
            else
                r = mid;
        }
        
        printf("%lf\n", r);
    }
}
```



---

## 作者：blank_space (赞：2)

# Word rings

[更好的 ~~运毒~~ 阅读体验](https://www.cnblogs.com/blank-space-/p/14349412.html)

## [题目链接](https://www.luogu.com.cn/problem/SP2885)

## 题目：
>给定数个字符串 一个字符串的最后两个字符与另一字符串的前两个字符相同则称两个字符串能够相连
当若干个串串成一个环时 求最大的字符环的平均长度

## 思路：
首先 我们把每一个字符串的前两个字符以及后两个字符以哈希思想分别映射成整数 以每组字符为点 字符串的长度为边
这样 题目就变成了在图中找到一个环 使得这个环的平均边权最大

然后考虑求解平均数
设 最终的平均边权为 ave
则 有：
$$ave = \frac{\sum_{i = 1}^{k}e_i}{k}$$
移项：
$$ave \times k = \sum_{i = 1}^{k}e_i$$
即：
$$\sum_{i = 1}^{k}e_i - ave \times k = 0$$
$$\sum_{i = 1}^{k}e_i - \sum_{i = 1}^{k}ave = 0$$
$$\sum_{i = 1}^{k}(e_i - ave) = 0$$
此处的$ave$是最优解 而范围内的其他合法解（题目允许有0.01的误差）则是将等于号改为小于等于号 这里就可以采用二分答案
我们直接二分一个平均值 判断是否满足$\sum_{i = 1}^{k}(e_i - ave) \geq 0$
换句话说 就是判断正环
对于正环的判断 采用 spfa_dfs 效率很高

最后注意输出要求里面 No solution. 后面这个点(~~不要问为什么~~）

## code：
```cpp
/*
  Time: 1.30
  Worker: Blank_space
  Source: #10082. 「一本通 3.3 例 1」Word Rings
*/
/*--------------------------------------------*/
#include<cstdio>
#include<cstring>
#include<vector>
#define emm(x) memset(x, 0, sizeof x)
#define fil(x) fill(x, x + tot, 0)
using namespace std;
/*--------------------------------------头文件*/
const int A = 1e4 + 7;
const int B = 1e5 + 7;
const int C = 1e6 + 7;
const int D = 1e7 + 7;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int FFF = 0x8fffffff;
/*------------------------------------常量定义*/
struct edge {int v; double w;};
vector <edge> e[B];
int n, c[D], tot, maxx, vis[700];
double dis[700], ans, eps = 1e-3;
char s[B];
bool p;
/*------------------------------------变量定义*/
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
/*----------------------------------------快读*/
int max(int x, int y) {return x > y ? x : y;}
void clear() {int i = 0; emm(e); tot = 0; emm(c); maxx = 0; ans = 0;}
void spfa(int u, int tp, double x)
{
	if(p) return ;
	vis[u] = tp;
	for(int i = 0; i < e[u].size(); i++)
	{
		int v = e[u][i].v; double w = (double)e[u][i].w - x;
		if(dis[v] >= dis[u] + w) continue;
		dis[v] = dis[u] + w;
		if(!vis[v]) spfa(v, tp, x);
		if(p) return ;
		else if(vis[v] == tp) {p = 1; return ;}
	}
	vis[u] = 0;
}
bool check(double x)
{
	p = 0; fil(dis); fil(vis);
	for(int i = 1; i <= tot; i++)
	{
		spfa(i, i, x);
		if(p) return p;
	}
	return p;
}
/*----------------------------------------函数*/
int main()
{
//	freopen("i1.in", "r", stdin);
    while(scanf("%d", &n) && n)
    {
    	clear();
    	for(int i = 1; i <= n; i++)
		{
			scanf("%s", s + 1);
			int len = strlen(s + 1); maxx = max(maxx, len);
			int x = (s[1] - 96) * 30 + s[2] - 96, y = (s[len - 1] - 96) * 30 + s[len] - 96;
			if(!c[x]) c[x] = ++tot; if(!c[y]) c[y] = ++tot;
			e[c[x]].push_back((edge){c[y], (double)len});
		}
		double l = 0, r = (double)maxx;
		while(l + eps < r)
		{
			double mid = (l + r) / 2;
			if(check(mid)) {ans = mid; l = mid;}
			else r = mid;
		}
		if(ans) printf("%.3f\n", ans);
		else puts("No solution");
	}
	return 0;
}

```

---

## 作者：那一条变阻器 (赞：2)

最近做了好多二分+最短路的题啊

------------

看到环之后就能想到SPFA判环了，但是具体怎么建边呢？我们把一个字符串的前两个字符看作一个节点，后两个字符看作一个节点，前面的向后面的连边（有向），边权为这个字符串的长度，这样，就把图建了起来，并且符合我们跑最长路找环的思想。但是，我们总不可能把所有环找出来看最大值吧，所以我们换种思路，来枚举答案，看是否找得到满足我们枚举的答案的环。但是，枚举太耗费时间了，这时，我们就引入二分。显然，答案越大越容易找到满足条件的环，所以，有了单调性，就可以二分了。

代码（细节挺多的...）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double l , r , mid;
double eps = 1e-6;
double dis[200010];
int vis[200010];
vector<pair<int , double> > e[200010];
int id(char x , char y){	//注意这里的转化成数字的方式，决定了节点应该如何枚举
							//因为我直接转化的，没有用hash之类的去使节点数固定，所以枚举节点时直接到3000（其实1000就行，一开始没算） 
	return (x - 'a') * 26 + y - 'a' + 1;
}
void add(int x , int y , double z){
	e[x].push_back(make_pair(y , z));
}
bool dfs(int now , double k){	//判环还是dfs_spfa好用 
	vis[now] = 1;
	for(int i = 0; i < e[now].size(); i++){
		int nx = e[now][i].first;
		double w = e[now][i].second;
		if(dis[nx] < dis[now] + w - k){	//注意这里减k，因为如果减去平均值（答案）还是正环的话，那说明这个环是符合条件的
										//如果减去平均值之后变成负环后，说明这个平均值太大了，要重新二分k 
			dis[nx] = dis[now] + w - k;
			if(vis[nx]) return 1;	//如果找到环，返回找到 
			else if(dfs(nx , k)) return 1;	//继续寻找是不是环 
		}
	}
	vis[now] = 0;
	return 0;
}
bool cheak(double k){
	memset(vis , 0 , sizeof(vis));
	memset(dis , 0 , sizeof(dis));
	for(int i = 1; i <= 3000; i++)	//枚举每一个节点，图有可能不是联通的 
		if(dfs(i , k)) return 1;
	return 0;
}
int main(){
	while(1){
		cin >> n;
		if(!n) break;
		for(int i = 1; i <= 3000; i++) e[i].clear();	//清空一下图 
		for(int i = 1; i <= n; i++){
			char a[3010];
			cin >> a + 1;	//从一开始输入 
			int len = strlen(a + 1);
			add(id(a[1] , a[2]) , id(a[len - 1] , a[len]) , len);	//建边 
		}
		l = 0 , r = 3000;	//r别取太大了，不然会T，也别太小了，说不定正确答案都比r大 
		while(r - l > eps){
			mid = (l + r) / 2.0;
			if(cheak(mid)) l = mid;
			else r = mid;
		}
		if(l == 0) cout << "No solution" << endl;	//使平均值为0都没有环，果断无解 
		else printf("%.2f\n" , l);
	}
	return 0;
}
```


---

## 作者：torque (赞：2)

## 算法
最短路算法

二分

## 题目

### 描述
如果字符串A的结尾两个字符与字符串B的开头两个字符相匹配，我们称A与B能 “ 相连 ” ( 注意：A与B能相连，不代表B与A能相连 )

当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算）

我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长
```cpp
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```
如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( 首尾重复部分需计算两次 ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

### 输入输出格式

#### 输入格式

多组数据

每组数据第一行一个整数n，表示字符串数量

接下来n行每行一个长度小于等于1000的字符串

读入以n=0结束

#### 输出格式

若不存在环串，输出"No solution"。否则输出最长的环串平均长度。

### 输入输出样例

#### 输入样例
```cpp
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
```

#### 输出样例
```cpp
21.66
```

## 思路

这道题乍一看是一个给出边(可以把两个字符视作一个整体，给出的每一个字符串$S_i$视作是讲$S_i$的前两个字母与$S_i$的后两个字母连起来，即:
```cpp
scanf("%s",s);
int leng=strlen(s);
int a=(s[0]-'a')*26+s[1]-'a'+1;
int b=(s[leng-2]-'a')*26+s[leng-1]-'a'+1;
```
这里面的a是将S的前两个字符视作一个整体化为整数
```cpp
int a=(s[0]-'a')*26+s[1]-'a'+1;
```

b将S的后两个字符视作一个整体化为整数
```cpp
int b=(s[leng-2]-'a')*26+s[leng-1]-'a'+1;
```

因此，对于每一组样例，就是一个有26*26个点、n条边的图，而第i条边的长度就是字符串$S_i$的长度

根据题意，我们就是要在这个图上找一个平均长度最长的环。。。

~~突然懵逼？~~

~~这怎么求？~~

其实要想求“平均长度最大”的环可以说是不可能的

~~n<=100000~~

**所以说 这是一道技巧性极强的题目**

$\color{red}\text{接下来就是玄学操作了}$

我们记最终找到的环节点编号为$d_1$、$d_2$、$d_3$、···、$d_k$，最终答案为g

那么，我们就是要找对于所有的d，满足下式的g的最大值：

$\boxed{\frac{\sum_{i=1}^{k}d_k}{k}>=g}$

变一下，得到

$\boxed{\sum_{i=1}^{k}d_k>=k*g}$

也即

$d_1+d_2+d_3+\cdots+d_k$>=$g+g+g+\cdots+g$

因此

**$(d_1-g)+(d_2-g)+(d_3-g)+\cdots+(d_k-g)>=0$**

结合上面的分析，我们终于明白了题意：找出使 **$(d_1-g)+(d_2-g)+(d_3-g)+\cdots+(d_k-g)>=0$**  
成立的g的最大值

为了方便求解，题意也可以理解成求使得 **$(d_1-g)+(d_2-g)+(d_3-g)+\cdots+(d_k-g)<0$** \
成立的g的最小值

我们前面已经说到$d_i$是第i条边的权值，第$1,2,3,\cdots,k$个节点构成一个环，它们边权和为负，就是说——存在负环

至此，这道题就很好做了

我们可以用如下代码来判断当g取值为k时是否存在负环：
```cpp
bool BellmanFord(int id,double k){
    vis[id]=true;
    for(node *i=fir[id];i;i=i->nxt)
        if(dis[id]+i->len-k>dis[i->to]){
            dis[i->to]=dis[id]+i->len-k;
            if(vis[i->to] || BellmanFord(i->to,k)){
                vis[id]=false;
                return true;
            }
        }
    vis[id]=false;
    return false;
}
bool Judge(double k){
    memset(dis,0,sizeof(dis));
    memset(vis,false,sizeof(vis));
    for(rnt i=1;i<=26*26;i++)
        if(BellmanFord(i,k))
            return true;
    return false;
}
```

至于为什么这么写在此不再赘述，如果不懂建议先去学学图论怎么判负环

另外，值得注意的是，答案的获取需要二分，容易证明：**答案不会超过最长的字符串的长度**，因此定义下确界dll(down length limit)为0，上确界ull(up length limit)为最大长度，最后二分：

```cpp
while(ull-dll>0.01){
	double mid=(ull+dll)/2.0;
   bool flag=Judge(mid);
   if(flag)
   	dll=mid;
   else
   	ull=mid;
}
```

## 代码
```cpp
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 26*26
#define K 500001
#define rnt register int
using namespace std;
struct node{
    int to,len;
    node *nxt;
} link[K];
node *fir[N];
node *las[N];
bool vis[N];
char s[1001];
int n;
double ull,dll,dis[N];//ull:up length limit;dll:down length limit
bool BellmanFord(int id,double k){
    vis[id]=true;
    for(node *i=fir[id];i;i=i->nxt)
        if(dis[id]+i->len-k>dis[i->to]){
            dis[i->to]=dis[id]+i->len-k;
            if(vis[i->to] || BellmanFord(i->to,k)){
                vis[id]=false;
                return true;
            }
        }
    vis[id]=false;
    return false;
}
bool Judge(double k){
    memset(dis,0,sizeof(dis));
    memset(vis,false,sizeof(vis));
    for(rnt i=1;i<=26*26;i++)
        if(BellmanFord(i,k))
            return true;
    return false;
}
int main(){
    while(scanf("%d",&n)){
        if(!n)
            break;
        ull=0.0,dll=0.0;
        for(rnt i=1;i<=n;i++)
            fir[i]=las[i]=NULL;
        for(rnt i=1;i<=n;i++){
            scanf("\n%s",s);
            int leng=strlen(s);
            int a=(s[0]-'a')*26+s[1]-'a'+1,b=(s[leng-2]-'a')*26+s[leng-1]-'a'+1;
            if(leng>ull)
                ull=leng*1.0;
            link[i].to=b;
            link[i].len=leng;
            link[i].nxt=NULL;
            if(fir[a])
                las[a]->nxt=&link[i],las[a]=&link[i];
            else
                fir[a]=las[a]=&link[i];
        }
        while(ull-dll>0.01){
            double mid=(ull+dll)/2.0;
            bool flag=Judge(mid);
            if(flag)
                dll=mid;
            else
                ull=mid;
        }
        if(!dll)
        	printf("No solution.\n");
        else
            printf("%.2lf\n",dll);
    }
    return 0;
}
```

---

## 作者：Zxsoul (赞：1)

## 二分最长路

### 题面

 给一定数量的字符串，找到其最长且首尾相连的环


### 思路

​	开始看到字符串，在加上匹配，感觉这题放错地方，可细想一下感觉不好办

正解开始：

- 大体：二分最长路

- 找到主干信息，我们只需要**子串的长度**以及前后两端的字母即可，如图下：

![](https://cdn.luogu.com.cn/upload/image_hosting/uffswquq.png)

- 我们将每个字符串的首位连在一起，权值是子串的长度。不拿发现，如果可以首位相连，那么自然地在边表中即可完成

- 暴力的思路有了，但是肯定会 $T$, 那么换个思路，**倒推**！

- 由最终答案 $ans$ 我们推论得

$$
  \begin{alignedat}{3}
  ans &= \sum_{i=1}^jlen_i/j\\
  &=\overline{x}*j\\
    0& =\sum_{i=1}^jlen_ij-ans\\
  	 0& =\sum_{i=1}^jlen_i-j*\overline{x}\\
    &=\sum_{i=1}^jlen_i-\sum_{i=1}^j\overline{x}\\
    &=\sum_{i=1}^j(len_i-\overline{x})\\
  \end{alignedat}
$$

- 因为上述是最理想的情况，即所二分的答案为真正答案，那么满足单调性的条件就是
- $$ \sum_{i=1}^j(len_i-\overline{x}) >= 0$$
- 完毕，看代码

### Code

```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

/*
  「一本通 3.3 例 1」Word Rings
  二分最长路  
*/
const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int v, nxt, w;
} e[B << 1]; 
int n, m, cnt, vis[B], head[B];
double dis[B];
char a[1009];  
void add(int u, int v, int w){
  e[++cnt].nxt = head[u]; e[cnt].v = v; e[cnt].w = w; head[u] = cnt;
}
bool dfs(int u, double lim){//dfs跑SPFA
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(dis[v] < dis[u] + w - lim){
          dis[v] = dis[u] + w - lim;
          if(vis[v] == 1)
          {
            if(dis[v] >= 0) //满足二分条件
            return 1;
          }
          if(dfs(v, lim)) return 1;
      }
      }
    vis[u] = 0;
    return 0;
  
}
bool check(double lim){
  memset(vis, 0, sizeof(vis));
  memset(dis, 0, sizeof(dis));
  for (int i = 1; i <= 1000; i++){
    if(dfs(i, lim)) return 1;
  }
  return 0;
}
int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  while(scanf("%d", &n)){
    if(n == 0) break;
    cnt = 0;
    memset(head, -1, sizeof(head));
    int maxx = 0;
    for (int i = 1; i <= n; i++){
      cin >> a;
      int s = strlen(a); 
      int u = (a[0] - 'a') * 26 + (a[1] - 'a' )+ 1;
      int v = (a[s - 2] - 'a') * 26 + (a[s - 1] - 'a')+ 1;
      add(u, v, s);
    }
    double l = 0, r = 1000;
    while(r - l > 1e-4 ){
      double mid = (l + r) / 2.0;
      if(check(mid)){//数据上说可以有0.01的误差，以前的代码却过不了，奇怪
        l = mid ;
      } else r = mid ;
    }
    if(l == 0) cout << "No solution." << endl;
    else printf("%.2lf\n", l);
  }
  fclose(stdin);
  fclose(stdout);
  return 0;
}
/*
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
*/

```



---

## 作者：Poetic_Rain (赞：1)

这道题是能够一眼看出思路的（然而我是错的），就是想求出所有的环，然后在所有环中比较出环串的平均长度最长的那一个，然后就完了

但是很明显这个东西基本无法实现（或者是我单纯太弱），因为无论我们想求平均长度最长，我们肯定希望跑最长路，刚好边权为字符串长度，那么跑进去正环之后就跑不出来了，所以这个想法换掉

那么继续想，我们无法枚举环来求出答案，我们就试着枚举答案，然后求出是否有满足答案的环就可以了

若我们此时枚举的答案为$ans$，有$k$个字符串，那么就有

$ans * k = len1 + len2 + len3  + ... + lenk$

那道这个式子之后，我们对它进行移项

$0=len1-ans+len2-ans+len3-ans+...+lenk-ans$

那么对于满足以下式子，也可以判断是正环

$0 \leq len1-ans+len2-ans+len3-ans+...+lenk-ans$

那么对于这个$ans$，$ans$越大，那么存在正环的概率也就越小，当$ans$越小时，$ans$大的情况肯定也会包含在里面，这就保证了单调性，可以使用二分答案来做

至于以上的最长路，应该可以使用Dijkstra判断正环，但是我还是喜欢用SPFA，因为可以判负环，而且大部分时候快一些（什么鬼才逻辑）

这里就直接上代码吧：

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+51;
int n;
string s[MAXN];
struct node {
	int net,to,w;
} e[MAXN];
int head[MAXN],tot;
void add(int x,int y,double z) {
	e[++tot].net=head[x];
	e[tot].to=y;
	e[tot].w=z;
	head[x]=tot;
} 
int len[MAXN];
bool v[MAXN];
double d[MAXN];
bool dfs(int x,double k) {
	v[x]=true;
	for(register int i=head[x]; i; i=e[i].net) {
		int y=e[i].to;
		double z=e[i].w;
		if(d[y]<d[x]+z-k) {
			d[y]=d[x]+z-k; //不能理解这个式子的参考上面的解题思路 
			if(v[y]==true||dfs(y,k)==true) return true; 
			//如果当前点走过说明有正环 
		}
	}
	return v[x]=false; //记得回溯 
}
int main() {
	while(scanf("%d",&n)) {
		if(n==0) return 0;  //结束程序 
		memset(head,0,sizeof head);
		tot=0; //记得清空 
		double l=0.0,r=1e8; //二分答案的范围，可以写大一点 
		for(register int i=1; i<=n; i++) {
			cin>>s[i];
			len[i]=s[i].length();
		} //输入，记录长度，每次调用函数会慢一点 
		for(register int i=1; i<=n; i++) {
			for(register int j=1; j<=n; j++) {
				if(s[i][len[i]-1]==s[j][1]&&s[i][len[i]-2]==s[j][0]) {
					add(i,j,len[i]); //枚举每两个字符串，如果可以相连就建边，边权就为字符串长度 
				}
			}
		}
		bool ok=false; //记录是否有答案 
		while(r-l>0.001) { //实数域的二分，我的太丑啦~~ 
			double mid=(l+r)/2;
			bool op=0; //是否更新l和r 
			memset(v,false,sizeof v);
			memset(d,0,sizeof d); //清空数组 
			for(register int i=1; i<=n; i++) {
				if(dfs(i,mid)==true) { //如果有正环，说明有答案 
					ok=true;
					op=1;
					l=mid;
					break;
				}
			}
			if(!op)r=mid; //搜不出来说明r太大了 
		}
		if(ok==false) puts("No solution");
		else printf("%.2lf\n",l*1.0);
	}
	return 0;
}
```


---

## 作者：J2a0m0e8s (赞：0)

首先感谢 [@xs_siqi](https://www.luogu.com.cn/user/401088) 巨佬在最关键的一段给了我提示，让我成功地做出了这道题。为了感谢他，也为了继承他的~~遗志~~，我决定也来写一篇题解（想看他的题解的请戳[这里](https://www.luogu.com.cn/blog/family233333/solution-sp2885)）
## 题目大意
输出一个平均长度最大的正环。
## 分析
这题显然是一道寻找正环的题目，而~~众所周知~~寻找正环肯定是有 ```DFS``` 加持的 ```SPFA``` 最快。但是在开始写 ```SPFA``` 之前，我们应该先解决两个问题。
# 建边
有些达瓦里氏们看到题目可能会把字符串看做点，在字符串中间连边，但是这是错的！如果每个字符串间都能首尾相连，则会有 $10^5$ 个点，两两相连就有 $(10^5)^2=10^{10}$ 条边，显然不行，因此我们应该换个思路。

注意到首尾都只取两个字母，只有 $676$ 种可能，若将其作为点只有 $676$ 个，也只有 $10^5$ 条边，符合条件，故可以这样建图。而将字符串变为数字显然想到 ```std::map``` ，因此这段思路便~~应运而生~~。

这段的代码如下，建议大家先思考再看。

```
      cin>>s; //存储字符串
      int l=s.size();
      st[0]=s[0],st[1]=s[1];
      ed[0]=s[l-2],ed[1]=s[l-1];
      M[st]=M[st]?M[st]:++tot;//M为map
      M[ed]=M[ed]?M[ed]:++tot;
      add(M[st],M[ed],l);//邻接表建边，注意绝不能建反向边，当初xs_siqi巨佬就是这样被卡了一个上午
```

# 二分
根据我的计算，常规找环可能会取到 $n^2$ 左右的复杂度，显然不可取，而本题可以转化成如下式子。

设 $ans$ 为最终答案， $s_{1},s_{2}……s_{n}$ 为最终所取的环上的每条边的长度，则有 $ ans=\frac{\sum^n_{i=1}s_{i}}{n} $ ，经转化可得 $\sum^n_{i=1}(s_{i}-ans)=0$ ，而等号左边的式子为关于 $ans$ 
的一次函数，具有单调递减性，因此将式子改成 $\sum^n_{i=1}(s_{i}-ans)\geq0$ 后可以用二分答案来做。

这部分代码如下：

```
double L=0,R=1009;
	while(L+del<R){//由于原题误差为1e-6,为防止无限循环，因此采用del,当L与R差距小于1e-7时即停止。对于luogu可以改成1e-4
		double mid=(L+R)/2;
		if(check(mid))L=mid;//check函数为判断是否有平均长度大于等于mid的环路的函数
		else R=mid;
	}
	return L;
```


最后，我将完整的代码写在下面，供大家参考：

```
#include<bits/stdc++.h>
#define del 1e-7
using namespace std;
int n,tot,fir[100009],nxt[2100009],son[2100009],w[2100009];double dis[100009];
string s;char st[3],ed[3];
bool vis[100009];
map<string,int>M;
void add(int x,int y,int z){ //建边
	son[++tot]=y,w[tot]=z,nxt[tot]=fir[x],fir[x]=tot;
	return ;
}
bool search(int a,double x){ //a为当前点，x为现在所二分到的ans值
    vis[a]=true;
	for(int i=fir[a];i;i=nxt[i]){
		if(dis[a]+w[i]-x>dis[son[i]]){
			dis[son[i]]=dis[a]+w[i]-x;  //spfa模板，w[i]-x由前面式子所得
			if(vis[son[i]]&&dis[son[i]]>=0)return true;
			if(search(son[i],x))return true; //深搜模板
		}
	}
	return vis[a]=false; //回溯
}
bool check(double x){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=tot;i++)
		if(search(i,x))return true; //判环搜索
	return false;
}
double find(){
	double L=0,R=1009;
	while(L+del<R){//由于原题误差为1e-6,为防止无限循环，因此采用del,当L与R差距小于1e-7时即停止。对于luogu可以改成1e-4
		double mid=(L+R)/2;
		if(check(mid))L=mid;//check函数为判断是否有平均长度大于等于mid的环路的函数
		else R=mid;
	}
	return L;
}
int main()
{
	while(1){
		tot=0;
		memset(fir,0,sizeof(fir));
		M.clear(); //初始化
		cin>>n;
		if(n==0)break;
		for(int i=1;i<=n;i++){
			cin>>s;
			int l=s.size();
			st[0]=s[0],st[1]=s[1];
			ed[0]=s[l-2],ed[1]=s[l-1];
            M[st]=M[st]?M[st]:++tot;//M为map
            M[ed]=M[ed]?M[ed]:++tot;
			add(M[st],M[ed],l);//邻接表建边，注意绝不能建反向边，当初xs_siqi巨佬就是这样被卡了一个上午
		}
		double p=find();//二分答案
		if(p==0)cout<<"No solution."<<endl;
		else printf("%.6lf\n",p);
	}
    return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

环上分数规划题。

# 题目大意

给定一张图，图中有若干个环，求这个图中所有权值的平均值最大的一个环的平均值。

# 题目大意

建图不必多说。

先介绍下分数规划，就是给定 $a_i,b_i$，求一组 $w_i\in\{0,1\}$ 最小/大化 $\dfrac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}$。

对于这类问题，我们可以通过实数域上的二分来解决。

当前二分值为 $mid$，则（题目中求的是最大值）：

$$\dfrac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}\gt mid$$

$$\to\sum\limits_{i=1}^nw_i\times(a_i-mid\times b_i)\gt0$$

所以求出左边的最大值即可判断当前 $mid$ 可不可行。

-------------
这道题显然没这么简单，这道题是环上分数规划的模板题。

环上分数规划的 $b_i=1$，所以把 $a_i-mid$ 作为每条边的权值，那么找到权值最大的环即可。求具体的值用二分答案，而我们只需要判断可不可行，注意到其实就是判断负环的存在性问题，$\rm spfa$ 求解。

---
注意这道题最后的答案输出不是四舍五入，而是直接暴力截小数点后两位。可以这样求：

```cpp
printf("%.2lf\n",(double)((int)(l * 100)) / 100.0);//l 就是二分出来的答案
```

# 代码

未刻意卡常也比绝大多数代码快：

```cpp
// Problem: SP2885 WORDRING - Word Rings
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/SP2885
// Memory Limit: 1500 MB
// Time Limit: 3000 ms
// Date:2022-06-23 22:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	#ifndef ONLINE_JUDGE
	#define getc getchar
	#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const double INF = 0x3f3f3f3f;
const double eps = 1e-4;
const int N = 1e5 + 5;
struct Graph {
	int v,nxt;
	double w;
} gra[N];
int head[N];
double dis[N];
bool vis[N];
int n,idx;
inline void add(int u,int v,double w) {
	gra[++ idx] = (Graph){v,head[u],w},head[u] = idx;
}
inline bool dfs(int now,double mid) {
	vis[now] = true;
	for (register int i = head[now];i;i = gra[i].nxt) {
		int v = gra[i].v;
		double w = gra[i].w;
		if (dis[v] < dis[now] + w - mid) {
			dis[v] = dis[now] + w - mid;
			if (vis[v] || dfs(v,mid)) return true;
		}
	}
	vis[now] = false;
	return false;
}
inline bool check(double now) {
	mst(dis,0x3f),mst(vis,false);
	for (register int i = 1;i <= 1000; ++ i) {
		if (dfs(i,now)) {
			return true;
		}
	}
	return false;
}
int main(void) {
	while (scanf("%d",&n) == 1 && n != 0) {
		idx = 0;
		mst(head,0),mst(gra,0);
		for (register int i = 1;i <= n; ++ i) {
			char a[1005];
			scanf("%s",a);
			int len = strlen(a);
			int u = (a[0] - 'a') * 26 + (a[1] - 'a') + 1;
			int v = (a[len - 2] - 'a') * 26 + (a[len - 1] - 'a') + 1;
			add(u,v,len);
		}
		double l = 0,r = 1000;
		while (l + eps <= r) {
			double mid = (l + r) / 2.0;
			if (check(mid)) l = mid;
			else r = mid;
		}
		if (l == 0) puts("No solution.");
		else printf("%.2lf\n",(double)((int)(l * 100)) / 100.0);
	}
	
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP2885)

## 1.建图

看完这个题目的第一时间就想到了一个建图方式：将每个字符串看成一个点，如果字符串 $A$ 与 $B$ 相连，那么就连一条从 $A$ 到 $B$ 长度为 $A.length()$ 的有向边，但是仔细一想，在最坏情况下，我们的图中会有 $10^5$ 个点，$10^{10}$ 条边，这显然是我们不能接受的。

但是我们观察到每个字符串中其实只有前两个字符和后两个字符是有用的，所以我们可以只取每个字符串的前两个字符和后两个字符，在它们之间连一条长度为这个字符串长度的有向边，这样做其实是和第一种建图方式等价的，但是我们最多只要 $26 \times 26 = 676$ 个点，$10^5$ 条边，这样的时空复杂度是我们能够接受的。

样例建的图如下:

![image-20220324211047901](https://s2.loli.net/2022/03/24/wBClfXQpRvWLt3y.png)

这样建完图以后，我们还可以使用类似**字符串哈希**的做法，把字符串映射为 $1 \sim 676$ 中的数字，方便建图。

## 2.求解

建完图以后，我们的目标就变成了找到一个环，使得 $\frac{\sum w}{s}$ 最大（$w$ 指的是边权，$s$ 为边数）

看到这个式子，首先想到的就是 $0/1$ 分数规划二分答案的思想（显然有单调性）

考虑一个数 $x$，使得 $\frac{\sum w}{s} > x$，将这个式子变形得到 $\sum w - s \cdot x > 0$，所以，我们可以将原图中每一条边的边权设为 $w -  x$（$w$ 表示该边边权），那么就可以将问题转化为原图中是否存在正环，我们可以用 dfs 版的 SPFA 求最长路解决这个问题。

## 3.代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 676, M = 1e5 + 10, L = 1010;
int h[N], e[M], ne[M], w[M], idx; // 邻接表存图
char s[L];
bool flag;
double d[N];
bool vis[N];
int n;

inline void spfa(int u, double x) // dfs版spfa
{
    if (flag) return;
    vis[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (d[v] < d[u] + w[i] - x) // 将边权变为 w[i] - x, 注意判断正环是求最长路
        {
            d[v] = d[u] + w[i] - x;
            if (vis[v]) flag = true;
            spfa(v, x);
        }
    }
    vis[u] = false;
}

inline void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

inline void check(double x)
{
    flag = 0;
    memset(d, 0, sizeof d);
    memset(vis, 0, sizeof vis);
    for (int i = 0; i <= N; i++)
    {
        spfa(i, x); // 注意图不一定联通，要每个点都dfs一次
        if (flag) return; // 找到正环，退出
    }
}

int main()
{
    scanf("%d", &n);
    while (n)
    {
        memset(h, -1, sizeof h);
        idx = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", s);
            int l = strlen(s);
            if (l >= 2)
            {
                int u = (s[0] - 'a') * 26 + (s[1] - 'a'); 
                int v = (s[l - 2] - 'a') * 26 + (s[l - 1] - 'a'); // 将字符串映射为数字
                add(u, v, l); // 连一条有向边
            }
        }
        
        double l = 0, r = L;
        while (r - l > 1e-4) // 精度要求,保留k位小数时就是 (r - l > 1e-(2+k))
        {
            double mid = (l + r) / 2;
            check(mid);  // 判断是否存在正环
            if (flag) l = mid; // 如果存在正环，说明mid比要求的最大值小，就l=mid
            else r = mid; // 不存在正环，说明mid比要求的最大值大，就r=mid
        }
        if (l) printf("%lf\n", l);
        else puts("No solution.");
        scanf("%d", &n);
    }
    return 0;
}
```

---

