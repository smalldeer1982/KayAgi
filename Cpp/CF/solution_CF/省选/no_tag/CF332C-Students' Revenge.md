# Students' Revenge

## 题目描述

系主任每天要处理繁重的事务，但学生们对她非常反感。现在有 $n$ 个任务，学生们先选出 $p$ 个，系主任再在其中选出 $k$ 个来完成。

对于第 $i$ 项任务，完成它会使系主任的头发变白 $a_i$，不完成就会使校领导的不满意度增加 $b_i$。系主任会先使校领导的不满意度尽可能少，在此基础上使自己的头发变白尽可能少。

但是学生们想要使系主任的头发变白尽可能多，其次使得校领导的不满意度尽可能大。

请你帮学生们求他们应该选择的 $p$ 个数。

## 样例 #1

### 输入

```
5 3 2
5 6
5 8
1 3
4 3
4 11
```

### 输出

```
3 1 2 ```

## 样例 #2

### 输入

```
5 3 3
10 18
18 17
10 20
20 18
20 18
```

### 输出

```
2 4 5 ```

# 题解

## 作者：xtx1092515503 (赞：3)

黑题绝对是恶评了（~~诶我说出来干嘛~~）

首先，观察到主席从我们给出的 $p$ 个任务中选择 $k$ 个完成的时候，是有顺序的——准确地说，假如我们将所有任务按照某种次序排序后，主席选择的，一定是 $p$ 个任务中次序最小的那 $k$ 个。

那么这个顺序是什么呢？实际上，就是按照**不满意度**递减排序，如果相同的话再按照**头发根数**递增排序。这很好理解——完成的任务的不满意度越高，剩下未完成的任务的不满意度就会越低。

我们发现，在排完序后，倒数 $p-k$ 个任务**一定不会被选择**。但是，剩下 $n-(p-k)$ 个任务，都是有可能被选到的。

于是我们就需要从这 $n-(p-k)$ 个任务中选择头发最多的$k$个给主席完成。这个可以通过按照头发递减顺序排序求出。但是为了保证主席一定会选择所有我们希望他选的任务，当头发相同时，我们应该将它按照**上一次排序的次序**作为第二关键字。这全部搞完后，我们只需要找出前 $k$ 个任务即可。

然后剩下的任务中，我们需要找出不满意度最大的 $p-k$ 个。显然这个我们已经在第一轮排序中求出了。于是我们只需要找出前 $k$ 个任务中在第一轮中次序最大的那一个，记作 $mxp$，然后选取第一轮排序后 $mxp$ 后面 $p-k$ 个任务即可。

时间复杂度$O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,o,ord1[100100],ord2[100100];
pair<int,int>p[100100];
bool cmp1(const int &x,const int &y){
	return p[x].second==p[y].second?p[x].first<p[y].first:p[x].second>p[y].second;
}
bool cmp2(const int &x,const int &y){
	return p[ord1[x]].first==p[ord1[y]].first?x<y:p[ord1[x]].first>p[ord1[y]].first;
}
bool cho[100100];
int main(){
	scanf("%d%d%d",&n,&m,&o);
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].first,&p[i].second),ord1[i]=i;
	sort(ord1+1,ord1+n+1,cmp1);
	for(int i=1;i<=n;i++)ord2[i]=i;
	sort(ord2+1,ord2+n-(m-o)+1,cmp2);
	int mxp=0;
	for(int i=1;i<=o;i++)mxp=max(mxp,ord2[i]),cho[ord1[ord2[i]]]=true;
	for(int i=mxp+1;i<=mxp+m-o;i++)cho[ord1[i]]=true;
	for(int i=1;i<=n;i++)if(cho[i])printf("%d ",i);puts("");
	return 0;
}
```


---

## 作者：Hoks (赞：1)

## 前言
比较有意思但是难度还能接受的贪心题。

这个翻译真的很烂，建议用 CF better 机翻看。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
因为主席完成任务的顺序是按照满意度从高到低排序。

对于一个被选中的任务 $i$，他会被主席完成，就当且仅当排名在他前面且被选中的任务个数小于 $k$ 个。

也就是我们把这选出来的 $p$ 个任务单独看，原本编号为 $i$ 的任务新编号 $j\le k$ 则会被完成。

那么对于任务 $i$ 如果我想要让它被完成，肯定是选择编号比他大的任务。

不难发现即是是在这样的最优决策下，最后的 $p-k$ 个任务也不会被完成。

接着考虑剩下的任务怎么决策。

肯定是白头发更多的先给主席。

那如果白头发数相等呢？

按照满意度从大到小排序即可。

最后随便挑一堆主席不会去完成的都塞进去就行了。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int n,p,k,mx,a[N],b[N],id[N],d[N],mp[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool cmp1(int x,int y){return (b[x]^b[y])?b[x]>b[y]:a[x]<a[y];}
inline bool cmp2(int x,int y){return (a[id[x]]^a[id[y]])?a[id[x]]>a[id[y]]:x<y;}
signed main()
{
    n=read(),p=read(),k=read();for(int i=1;i<=n;i++) a[i]=read(),b[i]=read(),id[i]=d[i]=i;
    sort(id+1,id+n+1,cmp1);sort(d+1,d+n-p+k+1,cmp2);
    for(int i=1;i<=k;i++) mx=max(mx,d[i]),mp[id[d[i]]]=1;
    for(int i=mx+1;i<=mx+p-k;i++) mp[id[i]]=1;
    for(int i=1;i<=n;i++) if(mp[i]) print(i),put(' ');
    genshin:;flush();return 0;
}
```

---

## 作者：XL4453 (赞：1)

我寻思为什么CF的c题都是黑的。。。



------------
解题思路：

首先我们知道主席的行为是可以预判的，他一定会选择最让学生满意的 $k$ 个任务。那么学生就可以预判出主席的行为。也就是先放 $k$ 个最让学生相对满意的任务，然后再放 $p-k$ 个掉头发最多的任务，这样主席就一定会选择完成掉头发最多的任务，这样学生任务就完成了，这样你就会发现自己预判了学生对主席的预判。



------------
代码：
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
struct arr
{
	int a,b;
	int num,num2;
}x[100005],x2[100005];
bool cmp(arr a,arr b)//议员不高兴递减 
{
	if(a.b==b.b)return a.a<b.a;
	return a.b>b.b;
}
bool cmp2(arr a,arr b)//掉头发数递减 
{
	if(a.a==b.a)return a.b>b.b;
	return a.a>b.a;
}
int n,m,k,maxn;
bool choose[100005];
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i].a>>x[i].b;
		x[i].num=i;
		x2[i].num=i;
	}
	
	sort(x+1,x+n+1,cmp);
	memcpy(x2,x,sizeof(x));
	for(int i=1;i<=n;i++)x[i].num2=i;
	
	sort(x+1,x+n+1-(m-k),cmp2);
	for(int i=1;i<=k;i++)
	{
		maxn=max(maxn,x[i].num2);
		choose[x[i].num]=1;
	}
	
	sort(x2+1+maxn,x2+n+1,cmp); 
	for(int i=maxn+1;i<=m-k+maxn;i++)choose[x2[i].num]=1;
	for(int i=1;i<=n;i++)
	if(choose[i])cout<<i<<" ";
	cout<<endl;
	return 0;
}
```


---

