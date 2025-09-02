# [POI 2010] TES-Intelligence Test

## 题目描述

**译自 POI 2010 Stage 1.「[Intelligence Test](https://szkopul.edu.pl/problemset/problem/Arkza0f7GKKb-m1YZJulnlMk/site/?key=statement)」**

给出一个母串 $a_1,a_2,a_3,\cdots ,a_n$ ，若干次询问，每次询问给出一个子串 $b_1,b_2,\cdots b_m$ ，请你求出这个子串是不是母串的子序列。

## 样例 #1

### 输入

```
7
1 5 4 5 7 8 6
4
5
1 5 5 8 6
3
2 2 2
3
5 7 8
4
1 5 7 4```

### 输出

```
TAK
NIE
TAK
NIE```

# 题解

## 作者：aldmsxdczxca (赞：8)

二分答案法。

vector记录位置。然后二分跑找到最小的符合位置就行了啊。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
int poi;
bool yes;
vector <int> a[1000010];
int b[1000010];
int dd(int now,int l,int r)
{
    int ans=-1;
    while (l<=r)
    {
        int m=(l+r)/2;
        if (a[now][m]>poi)
        {
            ans=a[now][m];
            yes=true;
            r=m-1;
        }
        else
            l=m+1;
    }
    return ans;
}
int main()
{
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        int t;
        scanf("%d",&t);
        a[t].push_back(i);
    }
    int T;
    scanf("%d",&T);
    while (T--)
    {
        bool flag=true;
        int n;
        poi=0;
        scanf("%d",&n);
        for (int j=1;j<=n;j++)
            scanf("%d",&b[j]);
        for (int j=1;j<=n;j++)
        {
            int now=b[j];
            int l=0,r=a[now].size();
            if (r==0)
            {
                flag=false;
                break;
            }
            r--;
            yes=false;
            int ttt=dd(now,l,r);
            if (yes)
                poi=ttt;
            else
            {
                flag=false;
                break;
            }
        }
        if (flag)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
```

---

## 作者：stoorz (赞：7)

考虑暴力。对于每一个询问，我们都维护两个指针，分别扫描原串 $a$ 和询问的串 $b$。如果 $a[i]=b[j]$，那么两个指针都往后扫，否则仅 $a$ 的指针往后扫即可。

时间复杂度 $O(nm)$。

容易发现，其实没必要对于每一个询问的串都扫描一次 $a$，我们其实可以只扫描一次 $a$，对于 $a$ 的每一位，分别去匹配每一个 $b$ 即可。
具体一点，设一个串 $b_i$ 的前 $x$ 位都被扫完并比配了，我们就需要在 $a$ 串中找到下一个 $b_i[x+1]$ 的位置。

扫描 $a$ 串，设现在扫描到第 $i$ 位，$b_i$ 串已经匹配完前 $num_i$ 个位置了。那么所有 $a_i=b_j[num_j]$ 的 $b_j$ 第 $num_j$ 位就匹配上了，对于这些 $b_j$，我们将 $num_j$ 加一即可。

如何求出扫描到第 $i$ 位时有哪些 $b$ 串满足正好需要匹配 $a_i$ 呢？用 $\operatorname{vector}$ 即可。设 $pos[x]$ 表示现在需要匹配数字 $x$ 的 $b$ 串有哪些，对于 $a_i=k$，我们将 $pos[k]$ 里面的 $b$ 全部往下匹配一个位置即可。

时间复杂度 $O(n+\sum^{m}_{i=1}len[i])$。其中 $len[i]$ 表示第 $i$ 个 $b$ 串的长度。

```cpp
#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp make_pair
using namespace std;

const int N=1000010;
int n,m,len,a[N],b[N],st[N];
bool ans[N];
vector<pair<int,int> > pos[N],cpy;
// pos[x][j].first 表示第 j 个需要匹配的数字为 x 的 b 串编号是几
// pos[x][j].second 表示第 j 个需要匹配的数字为 x 的 b 串 现在匹配到哪个位置了

int read()
{
	int d=0,f=1; char ch=getchar();
	while (!isdigit(ch)) f=ch=='-'?-1:f,ch=getchar();
	while (isdigit(ch)) d=(d<<1)+(d<<3)+ch-48,ch=getchar();
	return f*d;
}

int main()
{
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	m=read();
	for (int i=1,x;i<=m;i++)
	{
		x=read(); st[i]=len+1;  //省空间，将所有 b 串压缩在一个数组里
		for (int j=1;j<=x;j++)
			b[++len]=read();
		pos[b[st[i]]].push_back(mp(i,st[i]));
        // 一开始所有串都匹配到第一个位置
	}
	st[m+1]=len+1;
	for (int i=1;i<=n;i++)
	{
		cpy.clear();
		for (int j=0;j<pos[a[i]].size();j++)  // 枚举所有能匹配的串
		{
			int k=pos[a[i]][j].first,p=pos[a[i]][j].second;
			if (p+1==st[k+1]) ans[k]=1;  // 这个串已经全部匹配完了
				else cpy.push_back(mp(k,p+1));  //记录匹配下一位
		}
		pos[a[i]].clear();
		for (int j=0;j<cpy.size();j++)  //将上面匹配的串的下一位插入
		{
			int k=cpy[j].first,p=cpy[j].second;
			pos[b[p]].push_back(mp(k,p));
		}
	}
	for (int i=1;i<=m;i++)
		if (ans[i]) printf("TAK\n");
			else printf("NIE\n");
	return 0;
}
```

---

## 作者：z7z_Eta (赞：4)

## O(n)解法

本题也不是很难想啊，由于支持离线，我们就**多路归并**一下，很容易就O(n)了

如果字符集小的话，就是序列自动机裸体了，但字符集有1e6，不过仍然可以做到O(n)。

像序列自动机一样，每次查询最靠近的下一个字符

然后就是值域上邻接表，存下来所有查询序列的下一个数字，直接扫描，如果扫到一个数字，更新所有存储下来的下一个数字。

本来用vector也可以存，担心卡空间用了邻接表。

下面是代码

模拟题重要的还是理清楚a

```cpp
// SeptEtavioxy
#include<cstdio>
#include<cctype>
#include<cstring>
#define re register
#define ll long long
#define il inline
#define rep(i,s,t) for(re int i=(s);i<=(t);i++)
#define pt(ch) putchar(ch)
#define pti(x) printf("%d",x)
using namespace std;
// c_ints
il int ci(){
	re char ch;
	while(!isdigit(ch=getchar()));
	re int x= ch^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return x;
}
enum{N=1000024};

class node{
public:
	int nxt,pos;//pos是所属的序列id
}bow[N];
int tot;
int head[N];
il void add(int x,int y){
	bow[++tot].nxt= head[x];
	bow[tot].pos= y;
	head[x]= tot;
}//邻接表，bow[x]表示数字x上的询问

int a[N];
int k[N],*p[N];
int d[N*2],*last=d;//指针存储

int cur[N];//询问序列当前位置
bool ok[N];//答案

int main(){
	
    int m= ci();
	rep(i,1,m) a[i]= ci();
	
    int n= ci();
	rep(i,1,n){
		k[i]= ci();
		p[i]= last;
		rep(j,1,k[i]) p[i][j]= ci();
		last+= k[i]+1;
		add(p[i][1],i);//加入首项
	}
    
	rep(i,1,m){
		int u= a[i];
		int j= head[u];
		head[u]= 0;//清除邻接表
		for(;j;j=bow[j].nxt){
			int t= bow[j].pos;
			if( ++cur[t] == k[t] ) ok[t]= 1;//成功匹配
			else add(p[t][cur[t]+1],t);//加入下一位
		}
	}
    
	rep(i,1,n) puts(ok[i]?"TAK":"NIE");
    
	return 0;
	//end面()
}
```

祝$rp$++

---

## 作者：年华天地 (赞：3)

### 方法：vector+二分
### 思路
题目就是叫我们去求多个序列是不是一个序列的子序列。

首先，暴力做法就是两个指针依次动，然后依次判断两个序列是否匹配，时间复杂度$O(nm)$，那么怎么优化呢？我们发现指针一个个的跳太慢了，我们可以用vector记录每一个数出现的位置，然后二分的去查找。

我这里简单的简绍一下vector吧。

vector是一个可变数组，也就是说它的大小是不确定的，取决于你放多少个数进去。

调用vector要#include<vector>
  
vector的函数
  
vec.size(); //返回向量的实际大小\
vec.begin(); //返回向量的开始指针的位置\
vec.end(); //返回向量的结束指针的下一个位置\
vec.push_back(x); //在对象末尾插入数据x\
vec.pop_back(); //在对象末尾删除数据\
vec.clear(); //清除对象中的所有数据\
vec.at(i); //访问容器中第i个数的值\
vec[i]: //访问容器中第i个数的值

注意：vector下标从0开始。

发一下完整代码吧
```
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e6+1000;
int a[maxn],n,m,x,y,last;
vector<int>s[maxn];
int ef(int x,int last,int l,int r)//二分查找位置
{
	if (r-l<=5)
	{
		for (int i=l;i<=r;i++)
			if (s[x][i]>last)
				return s[x][i];
		return n+1;//表示没有这个位置，也就是说不是子序列
	}
	else
	{
		int mid=(l+r)/2;
		if (s[x][mid]<=last)return ef(x,last,mid,r);
		else return ef(x,last,l,mid);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)s[a[i]].push_back(i);//存储每一个数出现的位置
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		last=-1;//last存的是上一个数在原数组的位置，那么当前数的位置必须大于last
		scanf("%d",&y);
		for (int j=1;j<=y;j++)
		{
			scanf("%d",&x);
			if (last!=n+1)
			last=ef(x,last,0,s[x].size()-1);//下标从0开始，寻找
		}
		if (last==n+1)printf("NIE\n");
		else printf("TAK\n");
	}
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：3)

## 题外话
萌新一看题目一下就想到了用DP来做，打完，运行！提交！   
……五分钟后，我重新开始审题
## 题意
给定一个数串，和 $m$ 个小数串，问这些小串都是不是大数字串的子序列。
## 思路
利用 vector 进行储存每一个值为 $ai$ 的位置，然后利用二分进行查找其中最小的一个能够大于前一个位置的位置。  
说到底就是进行 $m \times L$ 次二分啦！  
将每一个小串的每一个数字在原大串中进行查找，查找到第一个能够大于上一个位置 $las$ 的位置，并进行保存。若找不到了，那么就输出 ```NIE```。若全部找到了，那么输出 ```TAK```。   
因为二分要保证数据有序，那么我们可以用一个 vector 保存位置，那么就太简单了，对吧！
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,bao,las,x,y,a[1200100],flag,mid,t,w,m;
vector<int> f[1200100];
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]),f[a[i]].push_back(i);
	scanf("%d",&m);
	for (i=1;i<=m;i++){
		scanf("%d",&x);las=-1;
		flag=true;
		for (j=1;j<=x;j++){
			scanf("%d",&y);
			t=0;w=f[y].size()-1;bao=-1;
			while (t<=w){
				mid=(t+w)/2;
				if (f[y][mid]>las) bao=mid,w=mid-1;
				else t=mid+1;
			}
			if (bao==-1) flag=false;
			else las=f[y][bao];
		}
		if (flag) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}

```


---

## 作者：kczno1 (赞：2)

匹配的时候，

比如说小串匹配到了数字x，

我们就是要找到后面第一个出现了x的地方。

一开始想到的是树套树或者记录归并排序过程，之后暴力的在树上类似二分的跑，nlog^2n,

或者主席树记录x最早出现的位置，直接拿i+1->n的权值线段树就可以得到，nlogn。

后来发现记录每个x出现的所有位置，之后就可以直接二分了,nlogn。


---

## 作者：YinyuDream (赞：1)

# 题解：

本题是给定一个序列$a$，多次询问某数列是否是该序列的子序列。对于每一个询问的序列$b$，对于$b_1$，我们可以在原序列在$[1,n]$中寻找第一个$b_i$出现的位置$p_1$,再在$[p_1+1,n]$中寻找$b_2$出现的位置$p_2$，以此类推，如果对于存在一个位置不能找到则无解，反之有解。那么如何快速求解在原序列中第一次出现的位置呢？我们可以用二分查找，对于每一个数建立一个vector，在其中二分查找出第一个大于$p$的位置。

# 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
int n,m;
int a[maxn],c[maxn];
vector<int>pos[maxn];
int read(){
	int x=0,sign=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')sign=-sign;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	x=x*10+ch-48,
	ch=getchar();
	return x*sign;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		pos[a[i]].push_back(i);
	m=read();
	for(int i=1;i<=m;i++)
	{
		int l=read(),p=0,book=0;
		for(int j=1;j<=l;j++)
		c[j]=read();
		for(int j=1;j<=l;j++)
		{
			auto t=upper_bound(pos[c[j]].begin(),pos[c[j]].end(),p);
			if(t==pos[c[j]].end()){
				book=1;
				puts("NIE");
				break;
			}
			else p=*t;
		}
		if(!book)
		puts("TAK");
	}
	return 0;
}
```


---

## 作者：阔睡王子 (赞：1)

## 可以是一道简单的分治与可变数组的应用题

题意：给定一个原序列，再给定多个序列，询问每个序列是否是原序列的子序列。

且，划重点： $m\leq 10^6,a_i,b_i \leq 10^6$ 。

我们可以用桶来记录每个元素的出现位置，但是普通的桶会原地 SPFA ,于是考虑用vector存储原数组中每个元素值的出现位置。

然后对于一个序列询问的每个元素进行匹配：在它的元素值的vector中尝试找到一个大于上一次匹配位置的一个最小位置。

代码实现如下：
```
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1000010;
vector<int>v[maxn];//建立可变数组vector
int a[maxn],pos,n,m,T;
bool book,flag;
void check(int x)//对当前元素在原数列中进行匹配
{
	int l=0,r=v[x].size()-1,temp=pos;//temp存储当前元素【最小的】合法匹配位置
	while(r-l>5)//二分大幅减少时间复杂度,之所以这样写是方便处理边界，减少思维量
	{
		int mid=(l+r)/2;
		if(v[x][mid]>pos)//匹配是成功的，pos记录上一次匹配到的位置
		{
			temp=v[x][mid];//temp记录下这个匹配位置
			book=true;//标记当前元素匹配结果是【成功】
			r=mid;
		}
		else l=mid;
	}
	for(int i=l;i<=r;i++)
	{
		if(v[x][i]>pos)//从小到大找到了最小匹配位置
		{
			temp=v[x][i];
			book=1;
			break;
		}
	}
	pos=temp;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		v[x].push_back(i);//把出现位置存储入vector数组
	}
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		flag=1;
		pos=0;
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
		 	scanf("%d",&a[i]);
		}
		for(int i=1;i<=m;i++)
		{
			int x=a[i];
			if(!v[x].size())//如果这个元素从未出现在原数列，匹配失败
			{
				flag=false;
				break;
			}
			book=0;//book记录当前元素匹配是否成功
			check(x);
			if(!book)//如果匹配不成功
			{
				flag=false;
				break;
			}
		}
		if(flag==1)printf("TAK\n");
		else printf("NIE\n");
	}
}
```



---

## 作者：Jayun (赞：1)

# 题目大意：

判断一个序列是否是另外一个序列删除若干个数字之后得到的。

# 正文：

## 方法1：

我们可以定义两个指针，分别指向长序列和短序列。

拿样例来举例：

![](https://s2.ax1x.com/2020/02/26/3UfEB4.png)


如果指针指的数相同，两个指针都往右跳：

![](https://s2.ax1x.com/2020/02/26/3UfmNR.png)

![](https://s2.ax1x.com/2020/02/26/3UfK9x.png)

如果不同，则指向长序列的指针往右跳：

![](https://s2.ax1x.com/2020/02/26/3Uf3uD.png)

以此类推。

超时，得分 $\texttt{30}$ 分。

## 方法2：

考虑将长序列每一个出现过的数的位置存起来，然后用二分找合适的位置。可以用 $vector$ 来存，再用一个变量 $last$ 记录短序列每一个数字在长序列出现的位置，二分时就可以找大于上一个数的 $last$ 的最小的数。

# 代码：

```cpp
bool flag = 1;
l = 0;
scanf ("%d", &n);
for (int i = 1; i <= n; i++)
{
	scanf ("%d", &x);
	if(f[x].empty())
		flag = 0;
	if(!flag)
		continue;
	it = upper_bound(f[x].begin(), f[x].end(), l);
	if(it == f[x].end()) flag = 0;
	l = *it; 
}
if(flag) puts("TAK");
else puts("NIE");
```

---

## 作者：老壁灯 (赞：0)

**vector初体验**

一道子序列匹配，关键是如何快速查找一个数在另一个数组的位置。
看了看数据范围，a数值只有~~可怜的~~一百万，干脆直接把原序列的每个值的下标扔进vector里。因为vector里的元素一定上升，直接二分查询看看这个位置是否存在。
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e6+100;
vector<int>pos[maxn];
int a[maxn],n,m,t,b[maxn];
int rad()
{
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int main()
{
	n=rad();
	for(int i=1;i<=n;++i)
	{
		a[i]=rad();
		pos[a[i]].push_back(i);//记录原数组中a[i]出现的位置，这个序列一定是升序的
	}
	m=rad();
	for(int i=1;i<=m;++i)
	{
		int p=0,book=0;
		t=rad();
		for(int j=1;j<=t;++j)
		{
			b[j]=rad();
		}
		for(int j=1;j<=t;++j)
		{
			vector<int>::iterator pp;//一个迭代器，我把它yy成vector的指针
			pp=upper_bound(pos[b[j]].begin(),pos[b[j]].end(),p);//查找该元素 
			if(pp==pos[b[j]].end())//upper_bound找不到该元素会返回最后一个元素的位置，借此判断该元素是否出现过； 
			{
				book=1;
				printf("NIE\n");
				break;
			}
			else p=*pp;//取出当前的的位置 
		}
		if(book==0)printf("TAK\n");
	}
	return 0;
}
```



---

## 作者：SkYFly (赞：0)

#### 题目大意：判断所给出的数列是不是已知数列的子序列。
### 正解
我们可以将序列中每个数的位置记下来，然后将需要查询的序列中的每个数字，在原序列没找过的区间中找相同数字并且最靠左的数字，依次向后找，能找完整个序列就说明是子序列。
由于是区间中找位置，显然可以二分，但由于是找数组中最靠左的数，并且每个数的vector是严格递增的，这样最靠左的数也就是大于last最小的数，所以完全可以用upper_bound代替二分进行查找。
##
#### 下面是代码
``` c++
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;

vector <int> v[MAXN];
vector <int> ::iterator it;
int m,x,kase,t,last;
bool flag;

int main(){
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&x),v[x].push_back(i);
	scanf("%d",&kase);
	while(kase--){
		flag=1,last=0;
		scanf("%d",&t);
		for(int i=1;i<=t;i++){
			scanf("%d",&x);
			if(flag==0)continue;//边读边处理,因为必须要读完,所以不能直接break
			if(v[x].empty()){flag=0;continue;}//不存在此数
			it=upper_bound(v[x].begin(),v[x].end(),last);//返回非递减序列[begin,end)中的第一个>last的位置(实际上因为不存在相同的数，用lower_bound和upper_bound都能过)
			if(it==v[x].end())flag=0;
			last=*it;//记录已经查找过的位置
		}
		if(flag)printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
```


---

