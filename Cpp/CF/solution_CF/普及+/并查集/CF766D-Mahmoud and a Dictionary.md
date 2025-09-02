# Mahmoud and a Dictionary

## 题目描述

Mahmoud wants to write a new dictionary that contains $ n $ words and relations between them. There are two types of relations: synonymy (i. e. the two words mean the same) and antonymy (i. e. the two words mean the opposite). From time to time he discovers a new relation between two words.

He know that if two words have a relation between them, then each of them has relations with the words that has relations with the other. For example, if like means love and love is the opposite of hate, then like is also the opposite of hate. One more example: if love is the opposite of hate and hate is the opposite of like, then love means like, and so on.

Sometimes Mahmoud discovers a wrong relation. A wrong relation is a relation that makes two words equal and opposite at the same time. For example if he knows that love means like and like is the opposite of hate, and then he figures out that hate means like, the last relation is absolutely wrong because it makes hate and like opposite and have the same meaning at the same time.

After Mahmoud figured out many relations, he was worried that some of them were wrong so that they will make other relations also wrong, so he decided to tell every relation he figured out to his coder friend Ehab and for every relation he wanted to know is it correct or wrong, basing on the previously discovered relations. If it is wrong he ignores it, and doesn't check with following relations.

After adding all relations, Mahmoud asked Ehab about relations between some words based on the information he had given to him. Ehab is busy making a Codeforces round so he asked you for help.

## 样例 #1

### 输入

```
3 3 4
hate love like
1 love like
2 love hate
1 hate like
love like
love hate
like hate
hate like
```

### 输出

```
YES
YES
NO
1
2
2
2
```

## 样例 #2

### 输入

```
8 6 5
hi welcome hello ihateyou goaway dog cat rat
1 hi welcome
1 ihateyou goaway
2 hello ihateyou
2 hi goaway
2 hi hello
1 hi hello
dog cat
dog hi
hi hello
ihateyou goaway
welcome ihateyou
```

### 输出

```
YES
YES
YES
YES
NO
YES
3
3
1
1
2
```

# 题解

## 作者：Alex_Wei (赞：7)

> [洛谷题面传送门](https://www.luogu.com.cn/problem/CF766D) & [CF题面传送门](http://codeforces.com/problemset/problem/766/D)

> 题意简述：给定 $n$ 个单词，并给定 $m$ 条它们之间的关系，忽略和之前给定的关系相矛盾的关系，最后有 $q$ 次询问两个单词之间的关系。

扩展域并查集的入门题，竟然是道黑题 $(2020.2.7)$。

考虑将一个单词 $x$ 拆成两个点，$x_s$ 和 $x_a$，分别表示 $x$ 的近义词域和反义词域。

有一种情况与 $x$ 和 $y$ 是近义词矛盾：$x_s$ 和 $y_a$ 在同一集合，表示 $x$ 是 $y$ 的反义词。

有一种情况与 $x$ 和 $y$ 是反义词矛盾：$x_s$ 和 $y_s$ 在同一集合，表示 $x$ 是 $y$ 的近义词。

确认关系正确，合并的时候：如果 $x$ 和 $y$ 是近义词，就将 $x_s$ 和 $y_s$，$x_a$ 和 $y_a$ 合并起来；否则就将 $x_a$ 和 $y_s$，$x_s$ 和 $y_a$ 合并起来。

查询的时候：如果 $x_s$ 和 $y_s$ 在同一集合里，就说明它们是近义词；否则如果 $x_s$ 和 $y_a$ 在同一集合里，就说明它们是反义词；否则它们间就没有任何关系。

```cpp
#include <bits/stdc++.h>
using namespace std;
map <string,int> mp;
int n,m,q,f[200005];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
string s,t; 
int main(){
	cin>>n>>m>>q;
	for(int i=0;i<n;i++)cin>>s,mp[s]=i,f[i]=i,f[i+n]=i+n;
	for(int i=0;i<m;i++){
		int rel,u,v;
		cin>>rel>>s>>t;
		u=mp[s],v=mp[t];
		if(rel==1){
			if(find(u)==find(v+n))puts("NO");
			else puts("YES"),f[find(u)]=find(v),f[find(u+n)]=find(v+n);
		}
		else{
			if(find(u)==find(v))puts("NO");
			else puts("YES"),f[find(u)]=find(v+n),f[find(u+n)]=find(v);
		}
	}
	for(int i=0;i<q;i++){
		cin>>s>>t;
		int u=mp[s],v=mp[t];
		if(find(u)==find(v))puts("1");
		else if(find(u)==find(v+n))puts("2");
		else puts("3");
	}
	return 0;
}
```


---

## 作者：est1ck_0tto (赞：6)

[cf传送](https://codeforces.com/problemset/problem/766/D)&[洛谷传送](https://www.luogu.com.cn/problem/CF766D)


------------
## 题意：
 第1行：输入3个数 n1，n，m

 第2行：输入n1个单词

 第3至3+n1：每行输入2个单词和它们的关系
	
1为同义
    
2为反义
    
如果关系成立（与上面的给定的关系不矛盾）就加入关系并输出“YES”不成立输出"NO"

第3+n1+1行至3+n1+m行：每行输入两个单词

要求输出它们的关系：1为同义 2为反义 3为没关系

------------
这其实就是道扩展域并查集的入门题~~好水的黑题~~

下面是我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000000];
string st1,st2;
map<string,int>mp;//map用来印射 
int find(int a){
	if(f[a]==a){
		return a;
	}
	return f[a]=find(f[a]);
}//模板 
int main(){
	int n,m,n1;
	string t;
	int t1;
	cin>>n1>>n>>m;
	for(int i=1;i<=n1;i++){
		cin>>t;
		mp[t]=i;//印射，免的后面再查一次 
		f[i]=i;f[i+n1]=i+n1;
	}
	int u,v;
	for(int i=1;i<=n;i++){
		cin>>t1>>st1>>st2;
		u=mp[st1],v=mp[st2]; 
		if (t1==1){
			if (find(u)==find(v+n1)){//反义 
				puts("NO"); //这里不能打endl，不然会WA（亲测） 
			} 
			else {
				puts("YES"); 
				f[find(u)]=find(v);
				f[find(u+n1)]=find(v+n1); 
			}
		}
		if (t1==2){
			if (find(u)==find(v)){
				puts("NO");
			} 
			else {
				puts("YES"); 
				f[find(u+n1)]=find(v);
				f[find(u)]=find(v+n1);

			}
		}
	}
	for(int i=1;i<=m;i++){
		cin>>st1>>st2;
		u=mp[st1],v=mp[st2];
		if (find(u)==find(v))puts("1");//这里也不能打endl 
		else if (find(u)==find(v+n1))puts("2");
			 else puts("3");		
	}
	return 0;
}

```


---

## 作者：ღꦿ࿐ (赞：6)

### CF766D
#### 算法： 带权并查集
~~看到许多大佬都用的扩展域，不会，是黑题，有点激动，因为终于有一道黑题了QwQ~~

进入正题


------------

题意： 有一些单词，每次给出两个单词的关系（近义词或反义词），输出与前面的关系是否矛盾，在有一些询问，询问两个单词的关系，近义词的近义词是近义词，近义词的反义词是反义词，反义词的反义词是近义词，~~虽然这不合理~~。

乍一看，觉得应该没有权值，仔细思考才发现近义词或反义词本质上就是到根的异或和。  

类似于转移方程的东东（关键步骤）：sum[x]^=sum[pa[x]];

可以用map来把单词映射到数组上，这样会方便的多

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,pa[100001],sum[100001],tp,x,y;
string s,s1,s2;
map<string,int> mp;
int root(int x)
{
	if (pa[x]==x) return x;
	int rt=root(pa[x]);
	sum[x]^=sum[pa[x]];
	pa[x]=rt;
	return rt;
}
signed main()
{
	cin>>n>>m>>q;
	for (int i=1;i<=n;i++)
	{
		cin>>s;
		mp[s]=i;
	}
	for (int i=1;i<=n;i++) pa[i]=i;
	for (int i=1;i<=m;i++)
	{
		cin>>tp>>s1>>s2;
		x=mp[s1];y=mp[s2];
		if (tp==1)
		{
			int rx=root(x),ry=root(y);
			if (rx==ry)
			{
				if (sum[x]!=sum[y]) printf("NO\n");
				else printf("YES\n");
			}
			else
			{
				printf("YES\n");
				pa[rx]=ry;
				sum[rx]=sum[x]^sum[y];
			}
		}
		else
		{
			int rx=root(x),ry=root(y);
			if (rx==ry)
			{
				if (sum[x]==sum[y]) printf("NO\n");
				else printf("YES\n");
			}
			else
			{
				printf("YES\n");
				pa[rx]=ry;
				sum[rx]=sum[x]^sum[y]^1;
			}
		}
	}
	for (int i=1;i<=q;i++)
	{
		cin>>s1>>s2;
		x=mp[s1];y=mp[s2];
		int rx=root(x),ry=root(y);
		if (rx!=ry) printf("3\n");
		else 
		{
			if (sum[x]==sum[y]) printf("1\n");
			else printf("2\n");
		}
	}
	return 0;
}
```

## 不！准！抄！ ~~除非你真的看懂了~~









---

## 作者：火羽白日生 (赞：1)

> 给出 $n$ 个单词，$m$ 次操作和 $q$ 次询问。每个操作可以将两个单词定义为同义词或反义词，若有跟之前定义相矛盾输出 `NO` 并忽略这次操作，否则输出 `YES`。每个询问要求回答两个单词之间的关系。

挺水的一道题。

看见这种互相之间有关系的题就考虑并查集，这里我用的是扩展域并查集。

$f_{1\sim n}$ 存的是同义词集合，$f_{n+1\sim 2n}$ 存的是反义词集合。

每次操作都查出来两个单词的同义词集合和反义词集合，判断两个单词的关系是否和操作有矛盾即可。

查询也是一样，查出两个单词的同义词集合和反义词集合直接判断即可。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=1e5+5;
	
	int n,m,q;
	map<string,int> H;// map 将字符串进行映射
	namespace UnionSet{
		int f[maxn<<1];// 扩展域并查集，开两倍大小
		inline void init(){for(int i=1;i<=(n<<1);i++) f[i]=i;}
		inline int find(int x){
			if(x==f[x]) return x;
			return f[x]=find(f[x]);
		}
	}using namespace UnionSet;
	
	inline int main(){
		n=read(); m=read(); q=read();
		init();
		for(int i=1;i<=n;i++){
			string s; cin>>s;
			H[s]=i;
		}
		for(int i=1;i<=m;i++){
			int op=read(); string x,y; cin>>x>>y;
			int fx=find(H[x]),fy=find(H[y]),ex=find(H[x]+n),ey=find(H[y]+n);
			if(op==1){
				if(fx==ey || ex==fy){puts("NO"); continue;}// 是反义词却要定义为同义词
				else{puts("YES"); f[fx]=fy; f[ex]=ey;}
			}
			if(op==2){
				if(fx==fy || ex==ey){puts("NO"); continue;}// 是同义词却要定义为反义词
				else{puts("YES"); f[ex]=fy; f[ey]=fx;}
			}
		}
		for(int i=1;i<=q;i++){
			string x,y; cin>>x>>y;
			int fx=find(H[x]),fy=find(H[y]),ex=find(H[x]+n),ey=find(H[y]+n);
			if(fx==fy || ex==ey) puts("1");// 同义词
			else if(fx==ey || ex==fy) puts("2");// 反义词
			else puts("3");
		}
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：pipiispig (赞：1)

##
map+扩展域并查集

这个题就是个带权并查集或者是扩展域并查集，看了下其他人写的怎么都是用本蒟蒻不会的带权并查集做的QwQ,这里我就用扩展域并查集来发个题解吧；
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;

map<string,int>Map;

const int N=2*100005;

int n,m,q,fa[N];

int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=2*n;i++)fa[i]=i;//有几种关系就要开几倍，因为这里只有同义词和反义词所以开2倍就可以；
	for(int i=1;i<=n;i++)
	{
		string a;
		cin>>a;
		Map[a]=i;//map转化；
	}
	for(int i=1;i<=m;i++)
	{
		int c;
		string u,v;
		cin>>c>>u>>v;
		int x=Map[u],y=Map[v];//map转成数字QwQ
		int xx=find(x),yy=find(y),xe=find(x+n),ye=find(y+n);//xx是和x意义相同的集合,yy是和y意义相同的集合，xe是和x意义不同的集合,ye是和y意义不同的集合;
		if(c==1)
		{
			if(xx==ye||yy==xe)//如果是和x意义不同的集合和与y意义相同的集合肯定有矛盾；
			{
				cout<<"NO"<<endl;	
			}
			else{
				if(xx!=yy)
				{
					fa[xx]=yy;//合并意义相同的集合;
				}
				if(xe!=ye)
				{
					fa[xe]=ye;//合并与x意义不同的集合和与y意义不同的集合，这个千万不能忘；
				}
				cout<<"YES"<<endl;
			}
		}
		else if(c==2)
		{
			if(xx==yy)//同理当和x意义相同的集合与和y意义相同的集合时输出NO;
			{
				cout<<"NO"<<endl;
			}
			else{
				if(xe!=yy)fa[xe]=yy;//将和x意义不同的集合与和y意义相同的集合合并；
				if(xx!=ye)fa[ye]=xx;;//将和y意义不同的集合与和x意义相同的集合合并；
				cout<<"YES"<<endl;
			}
		}
	}
	for(int i=1;i<=q;i++)
	{
		string a,b;
		cin>>a>>b;
		int x=Map[a],y=Map[b];//同样是map转化；
		int xx=find(x),yy=find(y),xe=find(x+n),ye=find(y+n);//这里的xx,yy,xe,ye的含义和上半部分相同；
		if(xx==yy)cout<<"1"<<endl;
		else if(xx==ye||yy==xe)cout<<"2"<<endl;
		else cout<<"3"<<endl; 
	}
    //这个题我们就可以简单的水过去了QwQ
}
```
悄咪咪的说一句,扩展域并查集比带权并查集简单多了QwQ,嘻嘻

---

## 作者：SpectatorX (赞：1)

听老师说，这道题应该用**带权并查集**来做，但由于~~我太蒟~~看见这题就想起了 [P2024 [NOI2001]食物链](https://www.luogu.com.cn/problem/P2024)，所以我用了**拓展域并查集**来做。

用$map$将字符串映射到数字上，再用开$2$倍空间的并查集存储关系，这样就可以将近义词和反义词分开。在读入一组关系时判断它们关系是否矛盾（即$S_1$与$S_2$同时既是近义词又是反义词）。

查询时，若$S_1$与$S_2$在同一集合内（即同在$father$数组的一段内），则可判断是近义词/反义词，若不在，则无关系。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int f[300005];//多开空间
map<string,int> mp;//映射
string s,st;
int rel;
int find(int a)
{
	if(f[a]==a) return a;
	return f[a]=find(f[a]);//路径压缩
}
void com(int x,int y)
{
	int a=find(x),b=find(y);
	f[a]=f[b];
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++) cin>>s,mp[s]=i,f[i]=i,f[i+n]=i+n;
	for(int i=1;i<=m;i++)
	{
		cin>>rel>>s>>st;
		int a=mp[s],b=mp[st];
		if(rel==1)
		{
			if(find(a)==find(n+b)) puts("NO");
			else puts("YES"),f[find(a)]=find(b),f[find(a+n)]=find(b+n);
		}
		if(rel==2)
		{
			if(find(a)==find(b)) puts("NO");
			else puts("YES"),f[find(a)]=find(b+n),f[find(a+n)]=find(b);
		}
	}
	for(int i=1;i<=q;i++)
	{
		cin>>s>>st;
		int a=mp[s],b=mp[st];
		if(find(a)==find(b)) puts("1");
		else if(find(a)==find(b+n))puts("2");
		else puts("3");
	}
	return 0;
}

```

---

## 作者：happybob (赞：0)

考虑并查集维护。

我们设 $1 \sim n$ 维护同义词并查集，$n + 1 \sim 2n$ 维护反义词并查集。

每次合并只需要判断是否和这次给出的情况不一样即可。

询问时与合并类似，判断同义或反义。

---

## 作者：psychosocial (赞：0)

题意：

给一些单词，它们可能是同义或者反义，给出一些关系定义，从前面的定义开始建立

关系，如果有的关系定义和之前的冲突输出NO,否则输出YES。然后查询q次单词x和单

词y的关系。




解题思路：



很明显就是带权并查集，但是我不太会用，去网上找了食物链的代码，改了下代码
，
但是每改公式，强行把关系差为2和3的都当做反义关系，结果错了。结束后去学习了
下带权并查集，然后直接把公式改了改就过了，发现其实当时xjb改也能过。

用一个数组rank[x]表示x和他的祖先直接的关系，0表示他们是同义，1表示他们是反义。

点于点之间的关系可以用向量来理解，为什么是向量我也不知道。
比如说题目定义x与y的关系为x->y,那么x->fa[y]=x->y+y->fa[y]。

也就是rank[x]=x与y的关系+rank[y];




```cpp
#include <bits/stdc++.h>
 
using namespace std;
const int maxn=1e5+5;
struct p
{
    char x[22];
}a[maxn+5];
int fat[maxn],ran[maxn], n;
bool cmp(p a, p b)
{
    if(strcmp(a.x,b.x)<0)return true;
    else return false;
}
int fin(char key[])
{
    int l=1, r=n, mid=(1+n)/2;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(strcmp(key, a[mid].x)>0)
        {
            l=mid+1;
        }
        else if(strcmp(key, a[mid].x)<0)
        {
            r=mid-1;
        }
        else return mid;
//        printf("%d %s\n", mid, a[mid].x);
    }
    return 0;
}
void Init(int n)//初始化重要
{
    for(int i=1; i<=n; i++)
    {
        fat[i]=i;//初始化都是指向（看做）自己
        ran[i]=0;//0同义 1反义
    }
    return;
}
int Find(int x)//找寻父节点+路径压缩
{
    if(x==fat[x])
        return fat[x];
    int y=Find(fat[x]);
    ran[x]=(ran[x]+ran[fat[x]])%2;//递归后从祖先节点向后到每个孩子来计算
    return fat[x]=y;//路径压缩
}
int main()
{
    int  m, q;
    scanf("%d%d%d", &n, &m, &q);
    int i;
    for(i=1; i<=n; i++)scanf("%s", a[i].x);
    sort(a+1, a+n+1, cmp);
    Init(n);
    int e, xx, yy;
    char x[22], y[22];
    for(i=0; i<m; i++)
    {
        scanf("%d%s%s", &e, x, y);
        xx=fin(x);
        yy=fin(y);
        int x1=Find(xx);
        int y1=Find(yy);
//        printf("%d %d\n", x1, y1);
        int ans=0;
        if(x1==y1)//共父节点才能判断出关系
        {
            if((ran[xx]-ran[yy]+2)%2==e-1)
                printf("YES\n");
            else printf("NO\n");
        }
        else printf("YES\n"), ans=1;
        if(ans)
        {
        fat[x1]=y1;//连接两父节点
        ran[x1]=(-ran[xx]+e-1+ran[yy]+2)%2;
        /*这里只对祖先x1赋值，可能有童鞋就疑问为什么xx没有赋值，其实xx在路径压缩里会根据
          它和祖先的关系赋值,所以这里不用对xx赋值*/
        }
    }
    for(i=0; i<q; i++)
    {
        scanf("%s%s", x, y);
        xx=fin(x);
        yy=fin(y);
 
        int x1=Find(xx);
        int y1=Find(yy);
        if(x1==y1)//共父节点才能判断出关系
        {
            int ans=(ran[xx]-ran[yy]+2)%2+1;
 
            printf("%d\n", ans);
        }
        else printf("3\n");
    }
    return 0;
}

```


---

