# [BalticOI 2004] ships 船

## 题目描述

有一个由 $n\times n$ 的正方形组成的“船”的游戏棋盘。每个单元格可能属于某艘船(黑色)或为空。如果两个边相邻的单元格都是黑色，那么这两个单元格属于同一艘船。不同船之间没有公共边。船的吨位是这些相邻的单元格数。

下边样例，棋盘中(黑色)的单元格属于船，共有一艘 $29$ 吨的船，三艘 $7$ 吨的船，二艘 $4$ 吨的船，三艘 $1$ 吨的船。

![样例](https://cdn.luogu.com.cn/upload/image_hosting/uk57lz80.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

请写一个程序，对给定的游戏棋盘计算出每艘船的吨位和数量。

## 说明/提示

对于所有的数据，$1\le n\le 3\times 10^4$，船舶总数和船舶吨位都不超过 $10^3$。

## 样例 #1

### 输入

```
12
2-4,7,9;
1,4,11-12;
1,4,10,12;
1,4-8,10-12;
1,8;
1,3-6,8,10-12;
1,3,5-6,8,11;
1,8,10-12;
1-8;
;
2;
2-4,7-10,12;```

### 输出

```
29 1
7 3
4 2
1 3```

# 题解

## 作者：SUNCHAOYI (赞：8)

**这道题目让我们从大到小输出连通块的大小及其对应的个数。**

首先最容易想到的是开个**二维数组**，然后就是很裸的**搜索**题目。但是一看 $n$ 的数据范围是 $1 \le n \le 3 \times 10 ^ 4$，所以 $n$ 较大是肯定会 $\texttt{MLE}$，只能拿到部分分。(应该能过前 $18$ 个点，但 $72$ 分我觉得~~也挺多的~~)

其次我们就要想着如何把**二维降到一维**，单纯的搜索肯定是过不去了，再次读题发现**船舶总数和船舶吨位都不超过** $10^3$，这便是本题的突破口。我们可以用**并查集**，每次记录当前行和上一行，如果与上一行的船有**相交**，则将其**合并**。下面详细来讲该做法：

- $\textbf{输入}$ 

题目中描述的共有两种情况：单独的一个船--用**单独的一个数**表示，连续的若干个船--用 `x - y` 的形式表示。这两个不同的情况之间用 `,` 隔开；行与行之间用 `;` 表示结束。

```
for (int i = 1;i <= n;++i)
{
	cin>>str;
	if (str == ";")//该行为空行 
	{
		Do something!
	} 
	for (int j = 0;j < str.size ();++j)
	{
		if ('0' <= str[j] && str[j] <= '9')//具体信息 
		{
			Do something!
		} 
		if (str[j] == '-')//分隔符 
		{
			Do something!
		}
		if (str[j] == ',' || str[j] == ';')//一个信息的结束标志 
		{
			Do something!	
		}
	}
}
```
根据以上程序，我们可以将处理输入分成四个部分(四个 `if ` 语句)。
1. 如果该行只有一个 `;`，那么没有需要处理的船，直接**跳过**即可。
2. 如果遇到**数字**，那么**转化**成 `int` 类型进行存储。
3. 如果遇到分隔符 `-`，说明有**连续一段**，标记并记录 `-` **左边**的数 `a = num`。
4. 如果遇到**结束**的标志 `,` 或 `;`，根据之前的标记进行判断是**一个数**还是**一段区间**，然后记录下来 `a = b = num` 或是 `b = num`(此处 $a$ 在**分隔符的位置**已经记录下来)

----

- $\textbf{判断相交}$

不难发现应该在第四个 `if ` 语句中操作。开两个数组分别记录**最新连通块的结点与大小**，并开一个记录每个**起始位置与终止位置**的结构体。
```
fa[++cnt] = cnt,sz[cnt] = b - a + 1;//结点与大小
_now[++k] = {a,b,cnt};//结点为 cnt 的连通块的信息
```
然后就是判断与上一行**有无相交**，有相交就直接**合并**，用 `while` 循环就能解决。
```
//kk 上一行的结点个数
//be[i] 上一行的信息 b[i].f,b[i].s,b[i].tmp 分别表示终止，起始与结点
//w 从 1 开始循环
while (w <= kk && be[w].f < a) ++w;//与上一行没有相交 
while (w <= kk && be[w].s <= b) _union (_now[k].tmp,be[w].tmp),++w;//有相交就合并 
```
当然，在 $i$ 循环的时候每一次都要**复制**一遍上一行的信息，如果当前行为 `;` 则需要**清空**上一行的信息。(因为下一行对应的是当前行空行，**一定没有相交**)

----

- $\textbf{并查集操作}$

1. 合并：如果**不是**同一个父亲结点上的就把**结点**与**连通块数量**一起合并。
```
int dx = find (x),dy = find (y);
if (dx != dy) fa[dy] = dx,sz[dx] += sz[dy];//合并
```
2. 查询：**递归式**查找，记得保存**最新的父结点信息**。
```
int find (int x)
{
	return fa[x] == x ? x : fa[x] = find (fa[x]);//查询根结点 
}
```

----

- $\textbf{答案的输出}$

如果一个**结点的父结点是它自己**，则这个结点上的**连通块数量**就是一个答案(说明其它连通的结点都**已经被合并**)，将其记录。
```
for (……)
	if (fa[i] == i) Record it!
```

题目中说明**最大**的连通块 $\le 10^3$，所以我们**倒序循环输出**即可。
```
for (int i = 1000;i >= 1;--i)
	if (连通块的数量为 i 时有解) cout<<i<<" "<<连通块个数为 i 的数量<<endl;
```

----

- $\textbf{完整的代码}$

```
#include <iostream>
#include <cstring>
using namespace std;
const int MAX = 1000005;
int n,a,b,num,cnt,k,kk,w,ans[MAX],fa[MAX],sz[MAX];
struct node
{
	int s,f,tmp;//起点，终点，结点序号 
} be[MAX],_now[MAX];
bool ty;string str;
void _union (int x,int y);
int find (int x);
int main ()
{
	cin>>n;
	for (int i = 1;i <= n;++i)
	{
		cin>>str;
		if (str == ";")
		{
			k = 0;//清零(别忘了!!!) 
			continue;
		}
		for (int j = 1;j <= k;++j) be[j] = _now[j];//上一行的记录 
		kk = k;//上一行的连块计数器 
		k = 0;//当前行的连块计数器 
		for (int j = 0;j < str.size ();++j)
		{
			w = 1;
			if ('0' <= str[j] && str[j] <= '9') num = num * 10 + str[j] - '0';
			if (str[j] == '-') a = num,num = 0,ty = 1;
			if (str[j] == ',' || str[j] == ';')	
			{
				//ty = 0 为一整段；否则为一个点 
				if (ty) b = num;
				else a = b = num;
				fa[++cnt] = cnt,sz[cnt] = b - a + 1;
				_now[++k] = {a,b,cnt};	
				while (w <= kk && be[w].f < a) ++w;//与上一行没有相交 
				while (w <= kk && be[w].s <= b) _union (_now[k].tmp,be[w].tmp),++w;//有相交就合并 
				a = b = num = ty = 0;		
			}
		}
		//for (int j = 1;j <= k;++j) cout<<_now[j].s<<" and "<<_now[j].f<<" "; 
		//cout<<endl;
		//for (int j = 1;j <= kk;++j) cout<<be[j].s<<" and "<<be[j].f<<" "; 
		//cout<<endl;
	}
	for (int i = 1;i <= cnt;++i)
		if (fa[i] == i) ++ans[sz[i]];//说明这个是根结点
	for (int i = 1000;i >= 1;--i)//船舶总数和船舶吨位都不超过 10^3
		if (ans[i]) cout<<i<<" "<<ans[i]<<endl;
	return 0;
}
void _union (int x,int y)
{
	int dx = find (x),dy = find (y);
	if (dx != dy) fa[dy] = dx,sz[dx] += sz[dy];//合并 
}
int find (int x)
{
	return fa[x] == x ? x : fa[x] = find (fa[x]);//查询根结点 
}
```

---

## 作者：UltiMadow (赞：4)

我提供的题，今天才做完

~~这题太TM坑了啊！！！！！！~~

看到这题，窝的第一反应：不就是个联通块嘛，水题水题

然后看到数据范围：$1\le n\le 3\times 10^4$

然后平方 $n^2\le 9\times10^8$ 这数组开不下啊！！！

好，继续想如何优化

我们发现黑格子最多只有 $10^6$ 个，那么，我们可以动态开点然后合并就行了

具体实现看代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;
int n;
int fa[MAXN],sz[MAXN],cnt;
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void merge(int x,int y)
{
	int a=get(x),b=get(y);
	if(a==b)return;
	if(sz[a]<sz[b])fa[a]=b,sz[b]+=sz[a];
	else fa[b]=a,sz[a]+=sz[b];
}
int create(){fa[++cnt]=cnt;sz[cnt]=1;return cnt;}
char s[MAXN];
int pre[MAXN],now[MAXN];
int ton[MAXN];
int getnum(int& pos)
{
	int ret=0;
	while(isdigit(s[pos]))
		ret=ret*10+s[pos++]-48;
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		memcpy(pre,now,sizeof(pre));//pre记录上一行
		memset(now,0,sizeof(now));
		scanf("%s",s+1);
		for(int j=1;j<=strlen(s+1);j++)
		{
			if(s[j]==';')break;
			int x=getnum(j);
			if(s[j]==','||s[j]==';')//单独的一个数
			{
				now[x]=create();
				if(pre[x])merge(now[x],pre[x]);//和上一行合并
			}
			else if(s[j]=='-')//多个数
			{
				j++;int y=getnum(j);
				now[x]=create();
				if(pre[x])merge(now[x],pre[x]);//和上一行合并
				for(int k=x+1;k<=y;k++)
				{
					now[k]=create();
					if(pre[k])merge(now[k],pre[k]);//和上一行合并
					merge(now[k],now[k-1]);//和左边的合并
				}
			}
		}
	}
	for(int i=1;i<=cnt;i++)
		if(fa[i]==i)ton[sz[i]]++;//记录
	for(int i=1000;i>0;i--)
		if(ton[i])printf("%d %d\n",i,ton[i]);
	return 0;
}
```
然后交上去发现只有52分，其余的TLE了qwq

于是我们就要想优化的方法

我们发现我们在新建一个节点的时候完全可以把同一行连续的节点直接合并成一个节点

于是我们就可以AC啦

放上AC代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;
int n;
int fa[MAXN],sz[MAXN],cnt;
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void merge(int x,int y)
{
	int a=get(x),b=get(y);
	if(a==b)return;
	if(sz[a]<sz[b])fa[a]=b,sz[b]+=sz[a];
	else fa[b]=a,sz[a]+=sz[b];
}
int create(int siz){fa[++cnt]=cnt;sz[cnt]=siz;return cnt;}
//新建节点
char s[MAXN];
struct Node{int l,r,pos;}pre[MAXN],now[MAXN];
int pcnt,ncnt;
int ton[MAXN];
int getnum(int& pos)
{
	int ret=0;
	while(isdigit(s[pos]))
		ret=ret*10+s[pos++]-48;
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		memcpy(pre,now,sizeof(Node)*ncnt);
		pcnt=ncnt;ncnt=0;int p=0;//p为指针
		scanf("%s",s+1);
		for(int j=1;j<=strlen(s+1);j++)
		{
			if(s[j]==';')break;
			int x=getnum(j),y=x;//x:左端点，y:右端点
			if(s[j]=='-'){j++;y=getnum(j);}
			now[ncnt]={x,y,create(y-x+1)};
			for(;p<pcnt&&pre[p].r<x;p++);
			for(;p<pcnt&&pre[p].l<=y;p++)
				merge(now[ncnt].pos,pre[p].pos);//向上合并
			ncnt++;
			if(p)p--;
		}
	}
	for(int i=1;i<=cnt;i++)
		if(fa[i]==i)ton[sz[i]]++;
	for(int i=1000;i>0;i--)
		if(ton[i])printf("%d %d\n",i,ton[i]);
	return 0;
}
```
这题还是非常不错滴，特别是这个读入实在是太太太太太太太烦啦！

---

## 作者：zeb6666 (赞：3)

## 思路

注意到本题 $1\leq n\leq 3\times 10^4$，所以只能另寻他法，考虑用并查集将同艘船的所有块合并在一起。

用一个一维数组表示上一行的地图，$st$ 表示上一行第一个块的编号，当前行的块可以和数组中编号大于 $st$ 的块合并，这样就不用还原数组了。

注意最后先要先进行一次 find 操作，保证一艘船的所有块都指向最终、正确的父块。然后将所有非父块的值累加至父块上，再用桶统计哪些容量出现了几次。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[1000006],k=0,mmap[30004],t[1000006],ans[1003];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
int main(){
	int n,st=1,lk=0; cin>>n;
	for(int i=1;i<=n;i++){
		string s; cin>>s;
		if(s==";"){st=lk+1,lk=k; continue;}
		string a="",b=""; int aa=0,bb=0;
		for(int j=0;j<s.length();j++){
			if(s[j]=='-') aa=stoi(a);
			else if(s[j]==','||s[j]==';'){
				if(b!="") bb=stoi(b);
				else aa=stoi(a),bb=aa; // stoi 是字符串转 int
				k++; fa[k]=k,t[k]=bb-aa+1;
				for(int kk=aa;kk<=bb;kk++){
					if(mmap[kk]>=st) merge(k,mmap[kk]);
					mmap[kk]=k;
				}
				aa=0,bb=0,a="",b="";
			}
			else if(aa==0) a+=s[j];
			else b+=s[j];
		}
		st=lk+1,lk=k;
	}
	for(int i=1;i<=k;i++) fa[i]=find(fa[i]);
	for(int i=1;i<=k;i++) if(fa[i]!=i) t[fa[i]]+=t[i];
	for(int i=1;i<=k;i++) if(fa[i]==i) ans[t[i]]++;
	for(int i=1003;i>=1;i--)
		if(ans[i]) cout<<i<<" "<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：angiing1222 (赞：2)

好像没人写暴力 dfs 啊。。。那我写一篇。

## 题目大意

使用**特殊的输入方式**给你一个 $n\times n$ 的黑白网格图，让你求黑色连通块的大小和数量。

## 解题方法

正如开篇所说，暴力 dfs 即可。

但是题解里都提到了一个问题：开 $n=3\times 10^4$ 的二维数组开不下。

但是，由于题目中给的图每个点只有两种状态（黑与白），所以不难想到使用 STL 中的 bitset 存储。

众所周知，bool 类型的变量占用 $1$ 个字节的空间，但是实际使用的只有字节中的第一个比特，这造成了极大的浪费。而 STL 中的 bitset 提供了一个每个元素只占用 $1$ 比特的布尔数组，这使得在声明同样的长度下，bitset 数组的空间大小大约是普通的 bool 类型数组的 $\frac{1}{8}$。

在本题中，我们可以开一个 $n*n$ 的 bitset，所占用空间为
$$
\begin{equation}
\begin{split}
(3\times 10^4)^2\times\frac{1}{8}\texttt{Byte}&=1.125\times10^8\texttt{Bytes}\\
&\doteq 107 \texttt{MiB}
\end{split}
\end{equation}
$$

是可以开下的（虽然很极限）。

然后就是大家都会的暴力了：
- 记录每行内的连通块的位置；
- 对于每个记录的行内的联通块，遍历，如果没有被之前的搜索搜到过，就标记并搜索；
- 最后记录每个连通块的大小和数量，使用 map 输出。
- 
时间复杂度 $O(kq)$，$k,q$ 分别是连通块大小和数量。

**本题最麻烦的一点就在于输入。一定要注意细节！**

代码：

```cpp
请在c++17及更高版本的标准上运行此代码。
#include <bits/stdc++.h>
using namespace std;
struct abc{
	int i,l,r;//行、起点、终点 
}a[1000005];
bitset<30005>vis[30005];
map<int,int,greater<int>>ans;
int n,d[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
int dfs(int x,int y){
	if(!vis[x][y])return 0;
	vis[x][y]=0;
	int ANS=0;
	for(auto [dx,dy]:d){
		int nx=x+dx,ny=y+dy;
		if(nx>0&&nx<=n&&ny>0&&ny<=n)ANS+=dfs(nx,ny);
	}
	return ANS+1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int cnt=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		string s;
		cin>>s;
		int rit=0,lft=-1;
		for(char ch:s){
			if('0'<=ch&&ch<='9')rit=rit*10+ch-'0';
			if(ch==','||ch==';'){
				if(rit==0){
					break;
				}
				if(lft==-1){
					lft=rit;
				}
				for(int j=lft;j<=rit;++j)vis[i][j]=1;
				a[cnt++]={i,lft,rit};
				lft=-1;
				rit=0;
			}
			if(ch=='-'){
				lft=rit;
				rit=0;
			}
		}
	}
	for(int i=0;i<cnt;++i){
		int an=dfs(a[i].i,a[i].l);
		if(an!=0)ans[an]++;
	}
	for(auto [key,val]:ans)cout<<key<<" "<<val<<"\n";
	return 0;
}
```

---

## 作者：billtun (赞：2)

本题的难点就在于 ~~再也不想见到这种~~ 输入。

重点来了，我这里输入了一个字符串 $str$ 表示一行，再遍历这个字符串，相对好操作一点。

其中 $tgt$ 表示将两个点放入一个并查集。

```cpp
void tgt(int x, int y){
	int dx=find(x),dy=find(y);
	if(dx!=dy) fa[dy]=dx, sz[dx]+=sz[dy]; 
}
```

要用到 `find()` 看两个点是否已经在一个并查集里了，如果已经在一个并查集里，那就不用连边了。

然后后看父亲等于自己的点的个数就行了，因为一条船上的点的父亲一定是一样的，所以有且仅有一个点的父亲等于自己，所以求出父亲等于自己的点的个数就是船的个数，给 $ans$ 加上就好了。

最后遍历 $ans$ （从大到小）直接输出。

完整代码：

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
int n, a, b, num, cnt, k, kk, w;
int ans[1000005], fa[1000005], sz[1000005];
struct node{
	int s, f, tmp;
} be[1000005], now[1000005];
bool ty;
string str;
int find(int x){ // 并查集必备
	return x==fa[x] ? x : fa[x]=find(fa[x]);
}
void tgt(int x, int y){ // 放入一个并查集
	int dx=find(x),dy=find(y);
	if(dx!=dy) fa[dy]=dx, sz[dx]+=sz[dy]; 
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>str;
		if(str==";"){
			k=0;
			continue;
		}
		for(int j=1;j<=k;j++)
			be[j]=now[j];
		kk=k;
		k=0;
		for(int j=0;j<str.size();j++){
			w=1;
			if('0'<=str[j] && str[j]<='9')
				num=num*10+str[j]-'0';
			if(str[j]=='-')
				a=num, num=0, ty=1;
			if(str[j]==',' || str[j]==';'){
				if(ty) b=num;
				else a=b=num;
				fa[++cnt]=cnt, sz[cnt]=b-a+1;
				now[++k].s=a, now[k].f=b, now[k].tmp=cnt;	
				while(w<=kk && be[w].f<a) w++;
				while(w<=kk && be[w].s<=b){
					tgt(now[k].tmp, be[w].tmp);
					w++;
				}
				a=b=num=ty=0;		
			}
		}
	}
	for(int i=1;i<=cnt;i++)
		if(fa[i]==i)
			ans[sz[i]]++;
	for(int i=1000;i>=1;i--)
		if(ans[i]!=0)
			cout<<i<<" "<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：Acestar (赞：2)

本题不难发现是找连通块，但是这样做会 $M$ （没试过不知道会不会 $T$），所以我们再考虑优化，观察输入，会发现给的是区间，所以我们只需要把区间存下来，把相邻两行相交的区间合并就行了。

用 $line1$ 存当前行每艘船的位置，$line2$ 存上一行每艘船的位置。都是结构体，包括船的左端点 $l$，右端点 $r$，编号 $pos$。

并查集，当然要有 $f$ 数组，然后再用 $siz$ 存船的大小。

找祖先时路径压缩，合并时判断两个 $siz$ 的大小，把小的接在大的下面。

```cpp
inline int Find(int x)
{
	return f[x]==x?x:f[x]=Find(f[x]);
}

inline void Union(int a,int b)
{
	int fa=Find(a),fb=Find(b);
	if(fa==fb) return;
	if(siz[fa]>siz[fb]) f[fb]=fa,siz[fa]+=siz[fb];
	else f[fa]=fb,siz[fb]+=siz[fa];
}
```

~~本题输入也比较恶心，没见过这样的输入，不过也没办法。~~

可以先输入一个字符串，然后枚举一遍，把数读出来。

```cpp
inline int read(int &pos)
{
	int res=0;
	while(s[pos]>='0'&&s[pos]<='9')
		res=res*10+s[pos++]-'0';
	return res;
}
```

其他就没什么了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010

using namespace std;

struct node
{
	int l,r,pos;	//l:左端点,r:右端点,pos:编号 
}line1[N],line2[N];	//line1:当前行,line2:上一行 
int n,len1,len2;
int f[N],siz[N],cnt,ans[1010];	//f:父亲,siz:大小,cnt:船的个数,ans:输出时的桶 
char s[N];	//输入 

inline int read(int &pos)
{
	int res=0;
	while(s[pos]>='0'&&s[pos]<='9')
		res=res*10+s[pos++]-'0';
	return res;
}

inline int creat(int x)	//新建船 
{
	f[++cnt]=cnt;
	siz[cnt]=x;
	return cnt;
}

inline int Find(int x)
{
	return f[x]==x?x:f[x]=Find(f[x]);
}

inline void Union(int a,int b)
{
	int fa=Find(a),fb=Find(b);
	if(fa==fb) return;
	if(siz[fa]>siz[fb]) f[fb]=fa,siz[fa]+=siz[fb];
	else f[fa]=fb,siz[fb]+=siz[fa];
}

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		memcpy(line2,line1,sizeof(node)*len1);	//这里一定要这样写，因为这是结构体 
		len2=len1;
		len1=0;
		int p=0;	//枚举上一行 
		scanf("%s",s);
		int len=strlen(s);
		for(int j=0; j<len; j++)
		{
			if(s[j]==';') break;
			int x=read(j);
			int y=x;
			if(s[j]=='-') j++,y=read(j);
			line1[len1]=(node){x,y,creat(y-x+1)};
			for(; p<len2&&line2[p].r<x; p++);	//上一行的船和当前的船不相交 
			for(; p<len2&&line2[p].l<=y; p++)	//相交 
				Union(line1[len1].pos,line2[p].pos);
			len1++;
			if(p) p--;
		}
	}
	for(int i=1; i<=cnt; i++)
		if(f[i]==i) ans[siz[i]]++;
	for(int i=1000; i>=1; i--)	//答案在1000以内，直接枚举 
		if(ans[i]) printf("%d %d\n",i,ans[i]);
	return 0;
}
```


---

## 作者：WuMin4 (赞：1)

## [[BalticOI 2004] ships 船](https://www.luogu.com.cn/problem/P5962)

## 思路

$n^2=9\times 10^8$ 的时空复杂度显然跑不了，考虑如何优化。

发现船舶总数与吨位都不超过 $10^3$，于是我们考虑将每行与上一行有交的集合使用并查集合并并维护块大小，若没有交则开一个新块出来。

注意到当两个线段集合 $a,b$ 均有序时，当 $b_i$ 与 $a_i$ 无交且 $b_i$ 在 $a_i$ 右边时，$b_{i+1},b_{i+2},\cdots$ 均不与 $a_i$ 有交。因此我们可以维护一个指针表示上一行枚举到了哪个区间，可以证明它是一定不减的。

因此该算法时间复杂度为 $O(V)$，其中 $V$ 为总段数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,f[1000005],sz[1000005],tc[1000005],tot;
bool vis[1000005];
int find(int x){
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void uni(int x,int y){
	int p1=find(x),p2=find(y);
	if(p1!=p2) f[p1]=p2,sz[p2]+=sz[p1];
}
struct node{
	int l,r,id;
};
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	vector<node> lst,nw;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		int num=0,n1=0,n2=0,r=0;
		for(char v:s){
			if('0'<=v&&v<='9') num=num*10+v-'0';
			else if(v=='-') n1=num,num=0;
			else if(v==','||v==';'){
				if(num==0) continue;
				if(n1) n2=num;
				else n1=n2=num;
				while(r<lst.size()&&lst[r].r<n1)
					r++;
				if(r==lst.size()||lst[r].l>n2)
					nw.push_back({n1,n2,++tot}),f[tot]=tot,sz[tot]=n2-n1+1;
				else{
					int lr=lst[r].id;
					while(r<lst.size()&&lst[r].l<=n2){
						uni(lr,lst[r].id);
						r++;
					}
					sz[find(lr)]+=n2-n1+1;
					nw.push_back({n1,n2,find(lr)});
				}
				r=max(r-1,0);
				n1=n2=num=0;
			}
		}
		lst.clear();
		for(node v:nw) lst.push_back(v);
		nw.clear();
	}
	for(int i=1;i<=tot;i++)
		if(!vis[find(i)])
			vis[find(i)]=true,tc[sz[find(i)]]++;
	for(int i=10000;i>=0;i--)
		if(tc[i]) cout<<i<<" "<<tc[i]<<endl;
	return 0;
}
```

---

## 作者：Hyc_ (赞：1)

### 本题解提供一种不用并查集但是可过且时空复杂度正确的做法。

#### 想法一：

暴力连通块，加上一点遍历技巧和`bitset`（省空间），可过。

代码见[记录](https://www.luogu.com.cn/record/113210148)（好险，空间差点炸了）。

#### 想法二（另一种正解？）：

可以对棋盘的储存进行优化，只储存有船的格子，就是每行用一个`vector`记录本行的情况。

仍然 dfs 找船，并记录走过的格子。

在同一行中，左右各尝试查找。

在去上下列时，二分查找是否有符合要求的格子。

此做法相对于想法一，空间大幅减少，时间增加不大。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e4+5;
int n,len,cnt,ans[1008];
string s;
vector<int>a[N];
vector<bool>vis[N];
inline int find(int i,int x){
	int l=0,r=a[i].size()-1,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[i][mid]==x)return mid;
		else if(a[i][mid]>x)r=mid-1;
		else l=mid+1;
	}
	return -1;
}//二分查找
void dfs(int x,int y){
	if(vis[x][y]==1)return;
	cnt++;vis[x][y]=1;
	if(y>0&&a[x][y-1]==a[x][y]-1)dfs(x,y-1);
	if(y<(int)a[x].size()-1&&a[x][y+1]==a[x][y]+1)dfs(x,y+1);
	int to;
	if(x>1){
		to=find(x-1,a[x][y]);
		if(to!=-1)dfs(x-1,to);
	}
	if(x<n){
		to=find(x+1,a[x][y]);
		if(to!=-1)dfs(x+1,to);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int k=1;k<=n;k++){
		cin>>s;
		if(s==";")continue;
		int l=0,r=0;
		for(int i=0;i<s.size();i++){
			if(s[i]>='0'&&s[i]<='9')r=r*10+(s[i]^48);
			else if(s[i]==','||s[i]==';'){
				if(l==0)l=r;
				for(int j=l;j<=r;j++){
					a[k].push_back(j);
					vis[k].push_back(0);
				}
				l=r=0;
			}
			else if(s[i]=='-')l=r,r=0;
		}
	}//读入、储存
	for(int i=1;i<=n;i++){
		for(int j=0;j<a[i].size();j++){
			cnt=0;
			dfs(i,j);
			ans[cnt]++;
		}
	}
	for(int i=1000;i;i--)
		if(ans[i])
			cout<<i<<" "<<ans[i]<<"\n";
	return 0;
}
```
附[提交记录](https://www.luogu.com.cn/record/113210610)

---

## 作者：Fla_Akebono (赞：0)

# P5962 [BalticOI 2004] ships 船
## 0.前言

好题，自己虽然过了但是都不知道怎么过的总是感觉有点问题但是确实好像没有问题，遂发题解纪念之。

~~絮叨：“这是我见过最阴间的输入方式了。”~~

## 1.题目大意

给出一个边长为 $L$ 的正方形点阵，求其中联通块的大小及其数量。保证 $L \le 3 \times 10^4$，且联通块的总数及其大小均不超过 $10^3$。

## 2.题目分析

为了行文方便，下文中令 $L=3 \times 10^4$，$n=10^3$。

显然，对于直接存图再进行搜索的时间复杂度和空间复杂度均是 $O(L^2)$，无法通过此题。

注意到较为特殊的输入方式。考虑自上而下，从左往右地将**每一行**的块表示为 $(l,r)$ 的形式，其中 $l$ 代表该块的左端点，$r$ 代表该块的右端点。例如，样例中第一行可以表示为 $(2,4)$，$(7,7)$，$(9,9)$ 三个区间。

考虑如何合并这 $L$ 行的区间。观察到如果上一行的某个区间 $(l_i,r_i)$ 和当前行的某个区间 $(l_j,r_j)$ 有交，则这两个块必属于同一个联通块。于是每次记录当前行和上一行所有的区间，将能和当前行的区间 $(l_j,r_j)$ 有交的所有区间合并，并计算贡献即可。

于是问题变为合并若干个区间并记录大小，考虑使用并查集实现。

## 3.细节分析/警示后人

对于每个区间，我们可以为其赋一个特有的值 $id$ 作为并查集的编号。

预处理输入时间复杂度为 $O(n)$，枚举当前行所有区间是否和上一行的区间有交的最坏时间复杂度为 $O(n^2)$，平均时间复杂度为 $O(n^{1.5})$，空间复杂度为 $O(n^2)$，可通过此题。

建议将并查集数组大小设为设为 $n^2$ 而不是 $L$。

## 4.Code


```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <bits/extc++.h>

#define mkp(i, j) make_pair(i, j)
#define num(x) (x - '0')

const int MAXN = 1e6;
using namespace std;
using namespace __gnu_pbds;

int n;
int fa[MAXN], siz[MAXN], id;
bool vis[MAXN];
gp_hash_table<int, int> dic;
vector<pair<int, int>> ans;

inline int findf(int x)
{
    return x == fa[x] ? x : fa[x] = findf(fa[x]);
}

inline void join(int x, int y)
{
    x = findf(x), y = findf(y);
    if (x != y)
        fa[x] = y, siz[y] += siz[x];
}

inline int tnum(const string &s)
{
    int res{}, p = 1;
    for (int i = s.length() - 1; i >= 0; i--)
        res += p * num(s[i]), p *= 10;
    return res;
}

struct node
{
    int l, r, id;
};

vector<node> init(string &s)
{
    vector<node> dat{};
    if (s != ";")
    {
        s.insert(s.begin(), ',');
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            if (s[i] == ',')
            {
                bool f{};
                int l = -1, r = -1, pos{};
                string x{};
                for (int j = i + 1; s[j] != ',' && s[j] != ';'; j++)
                {
                    if (s[j] == '-')
                    {
                        l = tnum(x);
                        x = "", f = 1;
                        continue;
                    }
                    x.insert(x.end(), s[j]);
                    pos = j;
                }
                f ? r = tnum(x) : (l = tnum(x), r = l);
                id += 1, dat.push_back(node{l, r, id});
                fa[id] = id, siz[id] = r - l + 1;
                i = pos;
            }
        }
    }
    return dat;
}

int main()
{
    scanf("%d", &n);
    string s{};
    vector<node> past{};
    for (int step = 1; step <= n; step++)
    {
        cin >> s;
        auto dat = init(s);
        if (!past.empty() && !dat.empty())
            for (auto i = dat.begin(); i != dat.end(); i++)
                for (auto j = past.begin(); j != past.end(); j++)
                    if (max(i->l, j->l) <= min(i->r, j->r))
                        join(j->id, i->id);

        past = dat;
    }
    for (int i = 1; i <= id; i++)
        if (!vis[findf(i)])
            dic[siz[findf(i)]]++, vis[findf(i)] = 1;
    for (auto i : dic)
        ans.push_back(i);
    sort(ans.begin(), ans.end(), greater<pair<int, int>>());
    for (auto i : ans)
        printf("%d %d\n", i.first, i.second);
    return 0;
}

```

---

## 作者：0x3F (赞：0)

看到题目第一反应：不就是个裸的连通块题吗！

但是我们立即发现，$n \le 3 \times 10^4$，如果把它们全部存储下来需要 $9 \times 10^8$，别说超时了，连这么一个 **`bool`** 数组也装不下。

考虑优化，将输入的每一“条”黑格作为一个整体，只需要判断“条”和“条”是否相交，就可以用并查集维护了。

显然这样的“条”的数量不会超过所有黑格的数量即 $10^3 \times 10^3 = 10^6$。

下面只剩下两个问题：

1. 如何读入？

1. 如何判断两“条”是否相交？

读入很烦，我是一个一个字符读入，然后提取其中的数字，再加入到适当的位置。

首先如果是一个数字字符，就加入当前的计数器。

否则将当前计数器的值提取出来并清零。

如果是 `,` 或 `;`， 就说明这一“条”结束了，若此时本行还没有任何读入或是当前右端点已经确定，说明这是新的一“条”，且该“条”只有一个点。如果左端点值已确定而右端点值未确定，说明是当前一“条”的右端点。如果是 `;`，则说明不仅该“条”结束了，该行也结束了。

如果是 `-`，说明是一个非“点”的“条”的左端点。

好了，只剩一个问题：如何判断两个“条”是否相交？

显然同一行的两个“条”不会相交（题目已说明），隔着一行或以上的两个“条”也不会相交（显然），只能是相邻两行的“条”相交。

我这里读一行处理一行，只需判断该行与上一行的“条”是否相交即可。

最暴力的方法是：对于本行的每一“条”，枚举上一行的所有“条”是否与之相交。

但是开动你聪明的小脑筋再想一想，一定要从头枚举到尾吗？

显然不用。这一“条”与上一“条”由于不相交，所以上一行最多最多只有一“条”与本行的两“条”同时相交。

换句话说，只需要从上一次的“尾”开始枚举即可。

那么这一次的“尾”又在哪里呢？

这个简单，最后一个符合条件的不就是“尾”了吗？

还有一个问题：如何维护带有权值的并查集？

把当前每一个点所管辖的权值之和记录下来，合并时相加即可。

见代码：

```cpp
#include <bits/stdc++.h>
#define _ 1000010
using namespace std;
int n, m, lef, rit, llef, lrit;
int l[_], r[_], siz[_], fa[_], cnt[_];
char ch;
int num;
bool flag;
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx != fy) {
		siz[fx] += siz[fy];
		fa[fy] = fx;
	}
}
int main() {
	cin >> n;
	while (n--) {
		lef = m+1;
		while (1) {
			ch = getchar();
			switch (ch) {
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
					num = num * 10 + ch - 48;
					break;
				}
				case ';': {
					if (num) {
						if (r[m]) {
							m++;
							l[m] = r[m] = num;
						} else {
							r[m] = num;
						}
						num = 0;
					}
					
					goto end;
					break;
				}
				case ',': {
					if (m == lef - 1 || r[m]) {
						m++;
						l[m] = r[m] = num;
					} else {
						r[m] = num;
					}
					num = 0;
					break;
				}
				case '-': {
					l[++m] = num;
					num = 0;
					break;
				}
				default: {
					break;
				}
			}
		}
		end:
		rit = m;
		for (int i = lef; i <= rit; i++) fa[i] = i, siz[i] = r[i] - l[i] + 1;
		if (flag) {
			for (int i = lef, j = llef; i <= rit; i++) {
				while (j <= lrit && r[j] < l[i]) j++;
				if (j == lrit + 1) break;
				while (j <= lrit && r[i] >= l[j]) merge(i, j), j++;
				if (j != llef) j--;
			}
		}
		llef = lef;
		lrit = rit;
		flag = 1;
	}
	for (int i = 1; i <= m; i++) {
		if (fa[i] == i) {
			cnt[siz[i]]++;
		}
	}
	for (int i = 1000; i >= 1; i--) {
		if (cnt[i]) {
			cout << i << ' ' << cnt[i] << endl;
		}
	}
	return 0;
}
```

$$\huge{\color{white}{\texttt{求过，求赞}}}$$

---

