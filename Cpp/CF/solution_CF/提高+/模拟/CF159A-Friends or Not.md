# Friends or Not

## 题目描述

Polycarpus has a hobby — he develops an unusual social network. His work is almost completed, and there is only one more module to implement — the module which determines friends. Oh yes, in this social network one won't have to add friends manually! Pairs of friends are deduced in the following way. Let's assume that user $ A $ sent user $ B $ a message at time $ t_{1} $ , and user $ B $ sent user $ A $ a message at time $ t_{2} $ . If $ 0&lt;t_{2}-t_{1}<=d $ , then user $ B $ 's message was an answer to user $ A $ 's one. Users $ A $ and $ B $ are considered to be friends if $ A $ answered at least one $ B $ 's message or $ B $ answered at least one $ A $ 's message.

You are given the log of messages in chronological order and a number $ d $ . Find all pairs of users who will be considered to be friends.

## 说明/提示

In the first sample test case Vasya and Petya are friends because their messages' sending times are one second apart. Anya and Ivan are not, because their messages' sending times differ by more than one second.

## 样例 #1

### 输入

```
4 1
vasya petya 1
petya vasya 2
anya ivan 2
ivan anya 4
```

### 输出

```
1
petya vasya
```

## 样例 #2

### 输入

```
1 1000
a b 0
```

### 输出

```
0
```

# 题解

## 作者：wuyixiang (赞：5)

~~题目已经很明确了，所以不需要题目大意。~~

我们看一眼数据范围：$n,d \le 1000$。

这就说明我们可以直接暴力枚举两条信息来判断那两个人是不是好友。去重有很多种方法，这里选用 `map<pair<string,string>,int>mp;` 来存储与存储与判重。最后直接输出去重后的操作即可。

另外：不用担心数组会存爆，一来一回最多只有 $500$ 个好友关系。

完整代码：

```cpp
#include <iostream>
#include <map>
using namespace std;
int n,d,cnt;
struct pp
{
	string x,y;
	int t;
}c[10005];
string a[20005],b[20005];
map<pair<string,string>,int>mp;
int main()
{
    cin >> n >> d;
    for(int i = 1;i <= n;i ++)cin >> c[i].x >> c[i].y >> c[i].t;//输入
    for(int i = 1;i <= n;i ++)
		for(int j = i + 1;j <= n;j ++)
		    if(c[i].x == c[j].y && c[i].y == c[j].x && 1 <= c[j].t - c[i].t && c[j].t - c[i].t <= d && !mp[{c[i].x,c[i].y}])//分别为：判断是否为同两个人、间隔时长是否 <= d 且 >= 1、去重
		    {
		        mp[{c[i].x,c[i].y}] = mp[{c[i].y,c[i].x}] = 1;
		        a[++cnt] = c[i].x,b[cnt] = c[i].y;
		    }
	cout << cnt << '\n';
	for(int i = 1;i <= cnt;i ++)cout << a[i] << " " << b[i] << '\n';//最后将去重的结果输出
}
```

---

## 作者：sLMxf (赞：3)

看见数据 $n,d\le 1000$，可以想到直接暴力。

每次判断 $i,j$ 两条信息是否符合要求便可。注意查重。这里我使用的是 `pair<string,string>`，因为我比较懒（逃~）

注意题目中给的是：$0<t_j-t_i\le d$，别看成 $0\le t_j-t_i\le d$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct mail{
      string a,b;
      int t;
}x[10008];
string ans1[10008],ans2[10008];
map<pair<string,string>,bool> q;
signed main()
{
      int n,d,ans=0;
      cin>>n>>d;
      for(int i=1;i<=n;i++) cin>>x[i].a>>x[i].b>>x[i].t;
      for(int i=1;i<=n;i++)
          for(int j=i+1;j<=n;j++)
          {
              if(x[i].a==x[j].b&&x[i].b==x[j].a&&0<x[j].t-x[i].t&&x[j].t-x[i].t<=d)
              {
                  if(q[{x[i].a,x[i].b}]==0)
                  {
                      ans1[++ans]=x[i].a,ans2[ans]=x[i].b;
                      q[{x[i].a,x[i].b}]=1;
                      q[{x[i].b,x[i].a}]=1;
                  }
              }
          }
      cout<<ans<<endl;
      while(ans)
      {
          cout<<ans1[ans]<<" "<<ans2[ans]<<'\n';
          ans--;
      }
      return 0;
}
```

---

## 作者：123456zmy (赞：3)

题意：  
如果 $A$ 向 $B$ 发了一条信息，在**之后**的 $d$ 秒内，$B$ 又向 $A$ 发了一条信息，则他们之间会建立朋友关系。输出朋友关系的数量和所有的朋友对。
___
~~题目不难，但是有坑。~~

记录每个人到另一个人的发的最后一条信息的时间，然后每次看是否满足条件即可。
___
~~如果这么简单我会交6遍吗~~
___
坑：**之后**，~~就是题意里加粗的那个~~不包括同时互发（~~WA~~）。加了特判后要改一下统计了。比如下面这个数据就会挂：(~~WA~~)  
input:
```plain
3 2
a b 1
a b 2
b a 2
```
output:
```plain
0
```
ans:
```plain
1
a b
```
因为同时发不会计入答案，所以后面的更新了前面可以计入答案的时间就会使输出比标准答案小，记录最后和严格在最后时间之前的时间即可。

代码：（~~交了6遍才过~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,an,t;
int f[2001][2001],ansn,f1[2001][2001];
bitset<2001> e[2001];
string s1,s2,sn[2001];
map<string,int>a;
int main()
{
	memset(f,-0x3f,sizeof(f));//WA
	memset(f1,-0x3f,sizeof(f1));
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
	{
		cin>>s1>>s2;
		scanf("%d",&t);
		if(!a[s1])sn[a[s1]=++an]=s1;
		if(!a[s2])sn[a[s2]=++an]=s2;
		if(f[a[s1]][a[s2]]!=t)f1[a[s1]][a[s2]]=f[a[s1]][a[s2]],f[a[s1]][a[s2]]=t;//WA
		if((f[a[s2]][a[s1]]>=t-d&&f[a[s2]][a[s1]]!=t)||(f1[a[s2]][a[s1]]>=t-d&&f1[a[s2]][a[s1]]!=t))//WA
		{
			if(!e[a[s1]][a[s2]])++ansn;
			e[a[s1]][a[s2]]=1;
			e[a[s2]][a[s1]]=1;
		}
	}
	printf("%d\n",ansn);
	for(int i=1;i<=an;i++)for(int j=1;j<=an;j++)if(e[i][j]==1)cout<<sn[i]<<" "<<sn[j]<<endl,e[j][i]=0;
	return 0;
}
```

---

## 作者：Epoch_L (赞：1)

## Solution
数据规模较小，字符串长度只有 $20$，判断相等时使用 hash 或暴力均可。

具体地，我们枚举一个消息记录，然后暴力扫一遍，如果满足以下条件：

- 传递的方向相反。
- 时间之差不为 $0$ 且小于等于 $d$。

就加入答案，注意需要判断重复，用 map 套 pair 就可以了。

这里给出 hash 的实现方法，时间复杂度 $O(n^2\log n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define mkp make_pair
#define int long long
using namespace std;
#define fi first
#define se second
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=1007,K=133;
struct node{
  int a,b,t;
}p[N];
char c[N][43],cc[N][43];
int get(char *s,int n){
  ull res=0;
  for(int i=1;i<=n;i++)
    res=res*K+s[i];
  return res;
}
int ans[N];
map<pair<int,int>,bool>mp;
main(){
  int n,d;read(n);read(d);
  for(int i=1;i<=n;i++){
    scanf("%s",c[i]+1);p[i].a=get(c[i],strlen(c[i]+1));
    scanf("%s",cc[i]+1);p[i].b=get(cc[i],strlen(cc[i]+1));
    read(p[i].t);
  }
  int ss=0;
  for(int i=1;i<n;i++){
    for(int j=i+1;j<=n;j++){
      int tt=abs(p[i].t-p[j].t);
      if(p[i].a==p[j].b&&p[i].b==p[j].a&&tt>0&&tt<=d){
        int aa=p[i].a,bb=p[i].b;
        if(aa>bb)swap(aa,bb);
        if(mp[mkp(aa,bb)])continue;
        mp[mkp(aa,bb)]=1;ans[++ss]=i;
      }
    }
  }
  printf("%lld\n",ss);
  for(int i=1;i<=ss;i++){
    for(int j=1;j<=strlen(c[ans[i]]+1);j++)
      putchar(c[ans[i]][j]);
    putchar(' ');
    for(int j=1;j<=strlen(cc[ans[i]]+1);j++)
      putchar(cc[ans[i]][j]);
    putchar('\n');
  }
  return 0;
}
```

---

## 作者：WinterRain208 (赞：1)

CF159A Friends or Not

### 翻译

给你$n$条记录，每个记录包含$a_i,b_i,t_i$，分别为发件人，收件人和时间。

求这样的朋友对：$a$给$b$发了一条消息，然后$b$再有限时间$d$内回了一条消息，你需要求出他们的名字和朋友对总数。

输出顺序随意， $0<t_i-t_j<=d$。

### 做法

挺不错的一道联系$map$搞映射的题目，~~但我调了快要一个小时心态崩了~~

基本思路：用$m[i][j]$记录两个人发的最后一条记录的时间，当两人之间再有信息来往时判断，记录。

注意使用$m4[i][j]$记录与当前$t_i$不相等的一条信息。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

int n,d,t,tot=0;
string x,y;
map < string , map < string , int > > m,m3,m4;
vector < string > v;
map < string , int > m2;
int main(){
	scanf("%d%d",&n,&d);
	F(i,1,n){
		cin>>x>>y>>t;
		++t;
		if((m[y][x]!=0&&t-m[y][x]<=d&&t-m[y][x]>0&&m3[x][y]==0)||(m4[y][x]!=0&&t-m4[y][x]<=d&&t-m4[y][x]>0&&m3[x][y]==0)){
			v.push_back(y+" "+x);
			m3[x][y]=m3[y][x]=1;
		}
		else if(m[x][y]!=t)m4[x][y]=m[x][y],m[x][y]=t;
	}
	if(v.size()==0){
		puts("0");
		exit(0);
	}
	F(i,0,v.size()-1)
		if(m2[v[i]]==0)++tot,m2[v[i]]=1;
	cout<<tot<<endl;m2.clear();
	F(i,0,v.size()-1)
		if(m2[v[i]]==0){
			m2[v[i]]=1;
			cout<<v[i]<<endl;
		}
	return 0;
}  
```


---

## 作者：Fkxxx (赞：0)

## 题目简述

给出 $1\leq n \leq 10^3$ 条记录，每条记录有时间 $t_i$，发出者 $a_i$ 和接收者 $b_i$。

若有任意两条方向相反的记录时间差 $1 \leq d \leq 10^3$，则认定发出者与接收者为好朋友。

## 思路过程

因为 $n$ 较小，可以直接强行枚举任意两人之间是否符合要求，若是，标记他们两人。最后直接输出标记过的关系。

不过，每个人的信息都是字符串，该怎么标记呢？

于是就有了 `STL:map`，把 `map` 的第一维度拿 `pair` 塞两个人代表一个关系，也就是定义 `map<pair<string,string>,bool>`，时间复杂度仅为 $O(\log n)$。

## 去重细节

众所周知，本体需要去重，我在此使用的是排序再去重的办法。压 `pair` 时，`first` 是一组关系的两个名字中字典序更小的一个，`second` 则反之。

## 参考代码

[Turn to Codeforces.com](https://codeforces.com/contest/159/submission/257834862)

---

## 作者：CQ_Bab (赞：0)

# 前言
~~水题~~。
# 思路
看到 $n\leq 1000$ 直接 $n^2$ 暴力，这里先按照 $t$ 排序然后枚举一个 $i$ 再去 $i$ 后看是否有一条消息能满足条件，注意这里的 $t$ 不能相同，如果 $t$ 之差大于 $d$ 直接退出即可，但是这里有可能会算重，直接用 set 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=1e3+10;
struct node{
	string a,b;
	int t;
	friend bool operator<(const node&a,const node&b) {
		return a.t<b.t;
	}
}s[N];
int n,d;
set<pair<string,string>>ans;
fire main() {
	in(n),in(d);
	rep(i,1,n) cin>>s[i].a>>s[i].b>>s[i].t;
	sort(s+1,s+1+n);
	rep(i,1,n) {
		rep(j,i+1,n) {
			if(s[j].t-s[i].t>d) break;
//			cout<<j<<endl<<s[i].a<<' '<<s[i].b<<' '<<s[j].a<<' '<<s[j].b<<endl;
			if(s[i].a==s[j].b&&s[i].b==s[j].a&&s[j].t-s[i].t>0) {
				ans.insert({max(s[i].a,s[i].b),min(s[i].a,s[i].b)});
			}
		}
	}
	cout<<ans.size()<<endl;
	for(auto x:ans) {
		cout<<x.first<<' '<<x.second<<endl;
	}
	return false;
}

```

---

## 作者：zzy_zzy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF159A)
### 题目大意
有 $n$ 条记录，每一条记录包括 $a_i,b_i,t_i$，分别表示发信息的人，收信息的人和时间。

现在让你求满足这样的朋友有多少对：$a$ 给 $b$ 在第 $c$ 个时刻发了一条信息，然后 $b$ 又在 $c+1$ 至 $c+d$ 的时刻内（左闭右闭区间）给 $a$ 回复了一条消息。你需要求出他们的名字和朋友对总数。

数据范围：$1\le{}n,d\le10^3,t_i\le10^4$。
### 思路：
由于题目给的是字符串，不好开数组作标记，所以考虑把每一个字符串映射成一个正整数（有点像离散化）。在作判断的时候，考虑 $O(n^2)$ 暴力，先枚举每一条信息，再来枚举这一条之前的每一条信息，看这两条信息是否呼应（也就是说这两个人是不是好朋友），如果是，就存进一个答案数组。

**注意：**
1. 对于这些信息，我们要先排序。
2. 要开一个数组判断重复。
3. 两个人同时互发不算。

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	string x,y;
	int timem;
}a[1010];
struct node2{
	int f,s;
}e[1010];
bool cmp(node i,node j){
	return i.timem<j.timem;
}
bool b1[2010][2010];
string c[2010];
map<string,int>ma;
map<int,string>mma;
int main(){
	int n,d,tot=0,cnt=0;
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].timem;
		c[++tot]=a[i].x,c[++tot]=a[i].y;
	}
	sort(a+1,a+n+1,cmp); //注意排序 
	for(int i=1;i<=tot;i++){
		if(i==tot||c[i]!=c[i+1]){
			ma[c[i]]=++cnt;
			mma[cnt]=c[i]; //为了输出方便，把数字也映射成字符串 
		}
	}
	int ans=0,sum=0;
	for(int i=1;i<=n;i++){
		int o=ma[a[i].x],p=ma[a[i].y],q=a[i].timem;
		if(b1[o][p]==0){ //判断是否重复 
			for(int j=i;j>=1;j--){
				int o1=ma[a[j].x],p1=ma[a[j].y],q1=a[j].timem;
				if(o1==p&&p1==o&&q-q1>0&&q-q1<=d&&b1[o][p]==0){ //判断是否对应 
					ans++;
					e[++sum].f=o1,e[sum].s=p1;
					b1[o][p]=1,b1[p][o]=1;
				}
			}
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++){
		cout<<mma[e[i].f]<<" "<<mma[e[i].s]<<endl;
	}
	return 0;
}
```

---

## 作者：_Dreamer_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF159A)

### 主要思路

主要就是通过 STL map 搞一个字符串到整数 的映射

再搞一个 string  映射回去 

然后枚举每个整数 看看相反的关系上有没有符合要求的  再搞个 ans 数组 记下来就好了

映射的目的是为了方便枚举

### 坑点

- 有 $1000 $ 条来往信息 所以至多有 $2000$ 个人
- $t_i=t_j$ 时不能算作朋友

其他细节可以看代码

```cpp

#include<bits/stdc++.h>
using namespace std;
map<string ,int> m;
string rem[2001];
int f[2001][2001][15];
int c[2001][2001];
int n,d;
int cnt;
int res=0;
pair<string,string> ans[2005];
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
	{
		string ta,tb;int tt;
		cin>>ta>>tb>>tt;
		if(m[ta]==0)m[ta]=++cnt,rem[cnt]=ta;
		if(m[tb]==0)m[tb]=++cnt,rem[cnt]=tb;
		f[m[ta]][m[tb]][++c[m[ta]][m[tb]]]=tt;
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=i+1;j<=cnt;j++)
		{
			bool flag=0;
			for(int k=1;k<=c[i][j];k++)
			{
				for(int l=1;l<=c[j][i];l++)
				{
					if(f[i][j][k]==f[j][i][l])continue;
					if(abs(f[i][j][k]-f[j][i][l])<=d&&flag==0)
					{
						res++;
						ans[res]=make_pair(rem[i],rem[j]);
						flag = 1;
					}
				}
			}
		}
	}
	cout<<res<<endl;
	for(int i=1;i<=res;i++)
	{
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}

```

---

