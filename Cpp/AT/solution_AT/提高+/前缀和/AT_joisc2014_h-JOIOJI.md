# JOIOJI

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_h



# 题解

## 作者：D_14134 (赞：14)

 首先令s1[i],s2[i],s3[i]分别表示1~i位中'J','O','I'的个数，那么某一个子串i~j中'J','O','I'的个数相同的条件为：

s1[j]-s1[i-1]=s2[j]-s2[i-1]=s3[j]-s3[i-1]


然后上式等号减去sJ[j]-sJ[i-1]，得到：

s1[j]-s2[j]-(s1[i-1]-s2[i-1])=s3[j]-s1[j]-(s3[i-1]-s1[i-1])，

那么如果令x[i]=sO[i]-sJ[i],y[i]=sI[i]-sJ[i]，那么就变成

x[i-1]=x[j]且y[i-1]=y[j]
       
如果当前字符是“J”，即s1[i]=s1[i-1]+1,s2[i],s3[i]不变
则x[i]=x[i-1]-1,y[i]=y[i-1]-1;
如果当前字符是“O”，即s2[i]=s2[i-1]+1,s1[i],s3[i]不变
则x[i]=x[i-1]+1,y[i]=y[i-1];
如果当前字符是“I”，即s3[i]=s3[i-1]+1,s1[i],s2[i]不变
则x[i]=x[i-1],y[i]=y[i-1]+1;

那么令一个点i为(x[i],y[i])，点权为i，那么就相当于查询最大的相同位置的
差。快排一下扫一遍即可。
# code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
char ch;
struct node{
	int x,y,id;
}a[200005];
bool cmp(node u,node v){return u.x<v.x||u.x==v.x&&u.y<v.y||u.x==v.x&&u.y==v.y&&u.id<v.id;}
int main(){
	//freopen("joioji.in","r",stdin);
	//freopen("joioji.out","w",stdout);
	scanf("%d",&n);
	ch=getchar();
	while(ch<'A'||ch>'Z') ch=getchar();
	for(int i=1;i<=n;i++){
		if(ch=='J'){
			a[i].x=a[i-1].x-1;
			a[i].y=a[i-1].y-1;
		}
		else if(ch=='O'){
			a[i].x=a[i-1].x+1;
			a[i].y=a[i-1].y;
		}
		else if(ch=='I'){
			a[i].x=a[i-1].x;
			a[i].y=a[i-1].y+1;
		}
		a[i].id=i;
		if(i<n) ch=getchar();
	}
	sort(a,a+n+1,cmp);
	int now=a[0].id,ans=0;
	for(int i=1;i<=n;i++){
		if(a[i].x==a[i-1].x&&a[i].y==a[i-1].y) ans=max(ans,a[i].id-now);
		else now=a[i].id;
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：Michael_Bryant (赞：12)

# 老规矩先推一发我的博客
[传送门](https://lfd2002.com/archives/747)    
前缀和    
J是1 O是200001 I是-200002    
（这个数的原因是为了很多个J也不能起到O的作用 不然不能起到代替的效果）    
然后前缀和做    
和为0的时候满足题意    
如果不是0的时候 在前面找一个和相等的 一减还是0 继续搞    
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
#define ll long long
#define max(a,b) a>b?a:b
char ch[N];
int n;
map<ll,int>m;
int main()
{
    scanf("%d%s",&n,ch+1);
    ll s=0,ans=0;
    for(int i=1;i<=n;i++)
    {
        if(ch[i]=='J') s++;
        else if(ch[i]=='O') s+=200001;
        else s-=200002;
        if(s==0) {ans=max(ans,i);continue;}
        if(m[s+200001ll*200001ll]!=0)ans=max(ans,i-m[s+200001ll*200001ll]);
        else m[s+200001ll*200001ll]=i;
    }
    printf("%lld\n",ans);
}

```

---

## 作者：xiezheyuan (赞：5)

## 简化题意

有一个由 `J`，`O`，`I` 组成的字符串，求一个子串，使得这三个字符出现次数一样。输出子串的长度的最大值。

## 思路

本题可以用一个前缀和来维护。

令 $J=1,O=1145141,I=-1145142$，那么就转换成了一个最长的和为 $0$ 的子串。（之所以取 $1145141$，是应为这个数比较大）。

枚举 $i\ (\text{from } 1 \text{ to } n)$。如果当前子串 $[1,i]$ 的和是 $0$，那么更新答案。然后就判断存储器中有没有答案，如果有，更新，否则就记录当前和。

至于存储器，可以使用 `std::map` 实现。

时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
char poem[200005];
int qzh,result=0;
map<int,int> mem;

signed main(){
	cin>>n;
	cin>>(poem+1);
	for(int i=1;i<=n;i++){
		char nch=poem[i];
		switch(nch){
			case 'J':
				qzh++;
				break;
			case 'O':
				qzh+=1145141;
				break;
			case 'I':
				qzh+=(-1145141-1);
				break;
		}
		if(qzh==0){
			result=max(result,i);
		}
		if(mem[qzh]!=0){
			result=max(result,i-mem[qzh]);
		}
        else {
        	mem[qzh]=i;	
		}
	}
	cout<<result<<endl;
	return 0; 
}
```

---

## 作者：Saber_Master (赞：3)

[AT1224 JOIOJI](https://www.luogu.com.cn/problem/AT1224)

区间$'J''O''I'$个数相等，不难想到利用前缀和.

我们考虑用$sJ_i,sO_i,sI_i$表示$[1,i]$区间内三个字符出现的次数，那一个满足要求的区间$[j,i]$应该是这样的：

$$sJ_i-sJ_{j-1}=sO_i-sO_{j-1}=sI_i-sI_{j-1}$$

也就是从$[j,i]$这段区间内三个字符出现次数加上了同样的值

区间加上同样值，有什么共性呢？答案是其差分数组不变.

所以我们可以构造出每个区间的差分数组$\{sO_i-sJ_i, sI_i-sO_i\}$

用$map$记录一下每个差分数组出现的第一个位置后统计答案即可.

```cpp
const ll N=2e5+5;

ll n;
ll sJ, sO, sI;
char wn[N];
map<pair<ll, ll>, ll> mp;
ll res;
int main(){
	read(n); scanf("%s", wn+1);
	mp[make_pair(0, 0)]=0;
	for (R ll i=1; i<=n; i++){
		sJ+=(wn[i]=='J');
		sO+=(wn[i]=='O');
		sI+=(wn[i]=='I');
		if (mp.find(make_pair(sO-sJ, sI-sO))!=mp.end()) chkmax(res, i-mp[make_pair(sO-sJ, sI-sO)]);
		else mp[make_pair(sO-sJ, sI-sO)]=i;
	}
	writeln(res);
}

```


---

## 作者：BotDand (赞：1)

# $\text{Problems}$

TD 有一个长度为 $\text{n}$ 的字符串 $\text{S}$，这个字符串非常的特别，每个字符一定是 `J, O, I` 中
的一个。

TD 觉得这个串的一个区间 $\text{[l, r]}$ 是完美的当且仅当 `J, O, I` 在这个区间中的出现次数相同。

TD 想知道这个串最长的完美的区间有多长，于是它把这个串告诉了你，希望你能回答
它的问题。

# $\text{Answer}$

令 $a_{i},b_{i},c_{i}$ 分别表示前 $\text{i}$ 个字符中 `J, O, I` 出现的次数。

则题目要求一个区间 $\text{[l, r]}$ 满足如下条件：

* $a_{r}-a_{l-1}=b_{r}-b_{l-1}$
* $b_{r}-b_{l-1}=c_{r}-c_{l-1}$

移项得：

* $a_{r}-b_{r}=a_{l-1}-b_{l-1}$
* $b_{r}-c_{r}=b_{l-1}-c_{l-1}$

于是从左往右扫，记录每对 $(a_{i}-b_{i}, b_{i}-c_{i})$ 最早出现的位置，取最大值即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200002],b[200002],c[200002];
char ch;
map<int,map<int,int> > f;
int ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        cin>>ch;
        if(ch=='J') a[i]=1;
        if(ch=='O') b[i]=1;
        if(ch=='I') c[i]=1;
    }
    for(register int i=1;i<=n;++i) a[i]=a[i-1]+a[i];
    for(register int i=1;i<=n;++i) b[i]=b[i-1]+b[i];
    for(register int i=1;i<=n;++i) c[i]=c[i-1]+c[i];
    for(int i=1;i<=n;++i)
        if(!f[a[i]-b[i]][b[i]-c[i]]) f[a[i]-b[i]][b[i]-c[i]]=i;
            else ans=max(ans,i-f[a[i]-b[i]][b[i]-c[i]]);
    for(register int i=1;i<=n;++i) if(a[i]==b[i]&&b[i]==c[i]) ans=max(ans,i);
    print(ans);
    return 0;
}
```

---

## 作者：jichi (赞：1)

一道很好的思考题，希望你们不要直接看题解

我们通过读题可以发现一个区间内不是J就是O或I，那么我们可以每读入一个字符就进行记录，然后进行差分，由差分我们可以知道一个性质，如果一个区间$[l,r]$可能是答案，那么$chafen[r]-chafen[l-1]$对于$J$，$O$，$I$，都是相同的，也就是说在$[l.r]$中$J$，$O$，$I$三个字符的**增量**相同，那么我们处理出差分数组并进行排序以优化复杂度，其中增量相同且最大的一项就是答案了！

$AC$ $Code$

```cpp
#include<bits/stdc++.h> 

#define int long long
 
using namespace std;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	int xx=x%10;
	putchar(xx+'0');
}

struct node{
	int jo,ji,len;
	bool operator < (const node &a){
		if(jo!=a.jo) return jo<a.jo;
		if(ji!=a.ji) return ji<a.ji;
		return len<a.len;
	}
}t;
int n,c1,c2,c3,ans;
string s;
vector<node> q;

signed main(){
	n=read();cin>>s;
	t.ji=t.jo=t.len=0;
	q.push_back(t);
	for(int i=0;i<n;i++){
		node tmp;
		if(s[i]=='J') c1++;//J
		else if(s[i]=='O') c2++;//O
		else c3++;//I
		tmp.ji=c1-c3;tmp.jo=c1-c2;tmp.len=i+1;
		q.push_back(tmp);
	}
	sort(q.begin(),q.end());
	int now=0;
	for(int i=1;i<q.size();i++){
		if(q[i].jo==q[now].jo&&q[i].ji==q[now].ji){
			ans=max(ans,q[i].len-q[now].len);
		}
		else now=i;
	}
	cout<<ans<<endl;
	return 0; 
}
```


---

## 作者：羽儇 (赞：1)

挺水一蓝题


------------

$Solution$

1、先用存入每个字母的数目的前缀和

  相减可得出一段区间的$J、O、I$ 的数量

2、存入结构体

  我萌需要使一段区间的$J$、$O$、$I$的数量相同
  
  就有$J1 - J2 = O1 - O2 = I1 - I2$
  
  即$J1 - J2 = O1 - O2$且$O1 - O2 = I1 - I2$
  
  转移一下可得到$J1 - O1 = J2 - O2$且$ I1 - O1 =  I2 - O2$
  
  那么我萌每次存入$J - O$与$ I - O$与序号(用来算长度即可)

------------

$AC$の$Code$
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int M = 200010;
int J,O,I,N;
char s[M];
struct node
{
	int x,y,id;
	bool operator == (const node &z)
	const
	{
		return x==z.x&&y==z.y;
	}
	bool operator < (const node &z)
	const
	{
		return x!=z.x?x<z.x:(y!=z.y?y<z.y:id<z.id);
	}
}p[M];
int main()
{
	scanf("%d%s",&N,s+1);
	for(int i = 1 ; i <= N ; i++)
	{
		if(s[i] == 'J')J++;
		if(s[i] == 'O')O++;
		if(s[i] == 'I')I++;
		p[i] = (node){J-O,I-O,i};
	}
	sort(p,p+1+N);
	int ans = 0 , last = 0 ;
	for(int i = 1 ;i <= N ; i++)
	{
		if(p[i]==p[i-1])ans = max(ans,p[i].id - p[last].id);
		else last = i;
	}
	printf("%d\n",ans);
	return 0;
}

```
$\text{注意，不加换行就会WA}$

---

## 作者：ollo (赞：0)

## [AT1224](https://www.luogu.com.cn/problem/AT1224)
# 题意
在一个只包含 J, O, I 的字符串 s 中找到一个最长区间使得 J, O, I 的个数相等。

# 题解

###### ~~大水题~~

使用前缀和维护

$j$, $o$ 和 $i$ 分别表示 J, O, I 的出现次数

读题可以发现其实是要求一个区间 $[l, r]$ 满足

1. $j_{r} - j_{l - 1} = o_{r} - o_{l - 1}$

2. $o_{r} - o_{l - 1} = i_{r} - i_{l - 1}$

移项后变成

1. $j_{r} - o_{r} = j_{l - 1} - o_{l - 1}$

2. $o_{r} - i_{r} = o_{l - 1} - i_{l - 1}$

接下来就只要从左往右扫一遍，记录每个形如 $(j_i - o_i, o_i - i_i)$ 的区间的最大值即可。

但是因为数据过大，所以还要 hash 一下。

# 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

map<long long, int> mp;
char s[N];
long long jx, i1, o1;
int n;
int ans = 0;

int main(){
 	cin >> n;
	cin >> s + 1; 
 	mp.clear();
 	mp[0] = 0;
 	for(int i = 1; i <= n; i++){
 		jx += s[i] == 'J' ? 1 : 0;
 		i1 += s[i] == 'I' ? 1 : 0;
 		o1 += s[i] == 'O' ? 1 : 0; 
 		long long hah = 100000 * (jx - i1) + (jx - o1);
 		if(mp.find(hah) != mp.end()) ans = max(ans, i - mp[hah]);
 		else mp[hah] = i;
	}
 	cout << ans;
 	return 0;
}
```


---

## 作者：wangyibo201026 (赞：0)

## 提前声明

AT 的题目最后要换行，否则会 WA。

## 思路

本人在考场上写不出正确思路，就用宝石串的方法写了一下。

我们发现，在宝石串这道题中我们是将两种颜色分别设为 $1$ 和 $-1$。但是，在本题中并不能这样进行变化，因为可能会出现错误情况。这里提供一种转化方式：

J 变为 $100000$，O 变为 $200001$，I 变为 $-300001$。

这样就可以避免错误情况了。

## 代码

代码：

```cpp
#include<bits/stdc++.h>
#define int long long    //注意，n 个 200001 相加会爆 int

using namespace std;

const int N = 2e5 + 5;

int n, maxi = -1e9;
char a[N];

int f[N];

map<int, int> vis;     //因为有负数，所以用 map

signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		if(a[i] == 'J'){    //如上所述
			f[i] = f[i - 1] + 100000;
		}
		if(a[i] == 'O'){
			f[i] = f[i - 1] + 200001;
		}
		if(a[i] == 'I'){
			f[i] = f[i - 1] - 300001;
		}
	}
	for(int i = n; i >= 1; i--){     //记录每个 f[i] 最早出现的下标
		vis[(long long)f[i]] = i;
	}
	vis[(long long)0] = 0;    //这里注意 0 最早出现在下标为 0 的位置
	for(int i = 1; i <= n; i++){
		maxi = max(maxi, i - vis[(long long)f[i]]);
	}
	cout << (maxi == -1e9 ? 0 : maxi) << endl;    //如果是 1e9 输出 0 就行了（其实不写也没关系）
	return 0;
}
```

---

