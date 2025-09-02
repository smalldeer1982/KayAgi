# Tyndex.Brome

## 题目描述

每个测试字符串$S$都有一个**独立**的$ans$。

对于测试字符串$S$的每个字母$S_{i}$，可以找到标准字符串$C$中字母$S_{i}$的离$i$的最近位置$j$。将位置的绝对差$\left|i-j \right|$加到$ans$中。也就是说对于每个$i$，取位置$j$，使得 $S_i = C_j$ 且$\left|i-j \right|$最小。

如果标准字符串中不存在字母$C_i$，则将测试字符串$S$的长度添加到$ans$。

## 样例 #1

### 输入

```
2 10
codeforces
codeforces
codehorses
```

### 输出

```
0
12
```

## 样例 #2

### 输入

```
9 9
vkontakte
vcontacte
vkontrakte
vkollapse
vkrokodile
vtopke
vkapuste
vpechke
vk
vcodeforcese
```

### 输出

```
18
14
36
47
14
29
30
0
84
```

# 题解

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF62B)

### 思路

对于标准字符串，用一个 `vector` 数组用来储存每一个字母所出现的下标。

接下来的每一次询问，答案是每一次与 $S_i$ 下标差值的最小值的和。

### 具体实现

1. 读入，开一个 `vector`，标准字符串中的每一个字符的下标都相应 `push_back` 到对应的字符中。

2. 对于每次询问，用循环遍历询问字符串的每一位。在该循环中，要取与 $S_i$ 下标差值的最小值。如果一个字符没有对应的下标，就加上 $S$ 的长度。最后将所有的最小值（其中也包括 $S$ 的长度）加和，就是该询问的答案。

**注意事项**

1. 每个测试字符串 $S$ 都有一个**独立**的 $ans$，所以 $ans$ 每次询问完要**清空**。

2. 不开 `long long` 见祖宗。另外，本题用 `%lld` 也能过，并不需要 `%I64d`。

---

## 作者：wangshi (赞：3)

[CF62B](https://www.luogu.com.cn/problem/CF62B)

题解区的大佬都用了一些本蒟蒻看不懂的算法。

但模拟好像就行，虽然代码有一点长。

下面蒟蒻分成几块来说一下。

## 1.题意。

一个字符串作为标准。

然后每个字符串都与这个对比。

每个字符串的每个字母的位置，与标准字符串中这个字母的位置，相减绝对值最小的结果加到 $ans$ 中。

如果没有就加上这个字符串的长度。

然后蒟蒻发现模拟不就行了吗。

## 2.基本框架。
$a \sim{z}$ 的数组是存这个字母在标准字符串中出现的位置。

$a2 \sim{z2}$ 是给数组计数。

```c
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1e5;//a~z存位置,a2~z2计数 
int a[N],b[N],c[N],d[N],e[N],f[N],g[N],h[N],i[N],j[N],k[N],l[N],m[N],n[N],o[N],p[N],q[N],r[N],s[N],t[N],u[N],v[N],w[N],x[N],y[N],z[N];
int a2,b2,c2,d2,e2,f2,g2,h2,i2,j2,k2,l2,m2,n2,o2,p2,q2,r2,s2,t2,u2,v2,w2,x2,y2,z2;
int main()
{
	int n1,k1;
	scanf("%d%d",&n1,&k1);//基本输入 
	long long ans=0;//存答案，要开long long 
	string s1;
	getchar();//蒟蒻也不知道为什么要吞换行，但不写getline就读不进去 
	getline(cin,s1);
	for(int i1=0;i1<=k1;i1++)//3里讲 
	{ 

	}
	for(int i1=1;i1<=n1;i1++)//4理讲 
	{
		string s1;
		getline(cin,s1);
		for(int j1=0;j1<s1.size();j1++)
		{	
			int minn=1e5+10; 
 
 
 
			ans+=minn;
		}
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}

```
## 3.标准字符串处理。

把每个字母的位置存进相应的数组。

```c
for(int i1=0;i1<=k1;i1++)
{ 
    if(s1[i1]=='a') a[++a2]=i1;
    //b~z同理就不写了 
}
```
$b \sim{z}$这么多而且基本相似，我们肯定不能自己输了。

所以这里给出代码生成。

```c
for(char i='a';i<='z';i++)
{
    cout<<"        if(s1[i1]=='"<<i<<"') "<<i<<"[++"<<i<<"2=i1"<<endl;
}
```
## 4.输入字符串的处理。

每个字符从头遍历，与标准字符串比较。

其他注释很详细，直接看代码即可。

```c
for(int i1=1;i1<=n1;i1++)
{
	string s1;
	getline(cin,s1);//平平无奇的输入 
	for(int j1=0;j1<s1.size();j1++)
	{	
		int minn=1e5+10;//找最小值
        if(s1[j1]=='a')
        {
            if(a2==0)//标准字符串中没有就加上输入字符串的长度 
            {
                ans+=s1.size();
                continue;
            }
            for(int k1=1;k1<=a2;k1++)//从头开始遍历，找绝对值差最小的 
                minn=min(abs(a[k1]-j1),minn); 
        }
        //b~z还是同理 
		ans+=minn;//输出 
		ans=0;//清零 
	}
	cout<<ans<<endl;
	ans=0;
}
```
$b \sim{z}$ 还是如此，给出代码生成。

```c
for(char i='a';i<='z';i++)
{
    cout<<"            if(s1[j1]=='"<<i<<"')"<<endl<<"            {"<<endl;
    cout<<"                if("<<i<<"2==0)"<<endl<<"                {"<<endl; 
    cout<<"                    ans+=s1.size();"<<endl<<"                    continue;"<<endl<<"                }"<<endl;
    cout<<"                "<<"for(int k1=1;k1<="<<i<<"2;k1++)"<<endl;
    cout<<"                    "<<"minn=min(abs("<<i<<"[k1]-j1),minn);"<<endl;
    cout<<"            }"<<endl;
}
```
## 5.完结撒花。

### 本蒟蒻的第二篇题解。

[AC记录](https://www.luogu.com.cn/record/63789057)

完整代码三百多行，就放在云剪贴板里吧。

[AC代码](https://www.luogu.com.cn/paste/a4h4ee77)

### 如果有问题，希望大佬指教。

---

## 作者：HyGeoIceFairy (赞：3)

这里是奇怪的set解法
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<set>
using namespace std;
int n,k,ls,lc;
string c,s;
long long ans,temp;
set<int> se[27];
set<int>::const_iterator li,ui;
const int maxx=114514893;
int main() 
{
	scanf("%d%d",&n,&k);
	cin>>c;
	lc=c.length();
	for(register int i=0;i<=26;++i)
	{
		se[i].insert(-maxx);
		se[i].insert(maxx);
	}//两边用maxx判断是否存在字母
	for(register int i=0;i<lc;++i)
	{
		se[c[i]-'a'+1].insert(i);
	}//将出现字母的位置放入字母对应的集合中
	for(register int i=1;i<=n;++i)
	{
		cin>>s;
		ans=0;
		ls=s.length();
		for(register int j=0;j<ls;++j)
		{
			ui=se[s[j]-'a'+1].upper_bound(j);//获取大于j的最近一个位置
			li=ui;
			--li;//这个操作获取了小于等于j的最近一个位置
			temp=min(j-*li,*ui-j);//选择更小的那个
			if(temp<=200000)//如果存在字母则加上位置差
			{
				ans+=temp;
			}
			else//否则加上长度
			{
				ans+=ls;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

[upper_bound不会可以看看这个](https://blog.csdn.net/qq_40160605/article/details/80150252)

---

## 作者：dingyyds11111 (赞：1)

### 题解：CF62B Tyndex.Brome

[题目传送门](https://www.luogu.com.cn/problem/CF62B)

### 思路：

保存标准字符串每个字母的位置，每次用二分查询代价。

### 实现：

用 `vector` 存储标准字符串每个字母的位置，`lower_bound` 找，因为两个字符串相同字母的位置有可能一样，相减得到价值，求总和即可，二分的部分比较难写，有一些细节需要注意，以及要开 `long long`。

---

## 作者：fjy666 (赞：1)

### 0x01 思路
我们可以用`std::set`来储存每一个字母对应的所有下标，再用`lower_bound`来搜索对应的上下界。时间复杂度$\Theta(n\times Len \times \log k)$  
实现时要注意
1. 当迭代器指向`begin`时的特殊处理
2. 当迭代器指向`end`时的特殊处理
3. 计数器要开**long long**！
4. 当不存在这样的字母时的特殊处理

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cstring>
#include <set>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
std::set<int> S[26+1];
char str[501000];

il int abs_(int x)
{
	if(x<0)rtn -x;
	rtn x;
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	scanf("%s",str+1);
	fo(i,1,k)
		S[str[i]-'a'].insert(i);
	ll ans;
	fo(i,1,n)
	{
		ans = 0;
		scanf("%s",str+1); 
		int Len = strlen (str+1);
		fo(j,1,Len)
		{
			if(!S[str[j]-'a'].size())
			{
				ans += Len;
				continue;
			}
			It(std::set<int>) it = S[str[j]-'a'].lower_bound(j);
			//it 为第一个大于或等于j的地方的迭代器
			It(std::set<int>) it2 = it ;
			if(it!=S[str[j]-'a'].begin())
				--it; //it 为 最后一个小于 j 的位置；
			if(it2 == S[str[j]-'a'].end())
				it2 = it; 
			int Min = std::min(abs_(*it - j),abs_(*it2 - j));
			ans += Min;
		}
		printf("%lld\n",ans);
	}
    rtn 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## CF62B Tyndex.Brome 题解
### 标签
字符串，二分
### 分析
水题无人。

我们想求测试串字母与标准串中相同字母的最近相对距离。很容易想到用 $\text{map}$ 中套 $\text{vector}$ 把标准串中每个字母出现的位置存下来。然后遍历测试字符串的每一位，遍历到第 $j$ 位时，在 $\text{map}$ 相应字母的位置二分找一下第一个小于 $j$ 的位置，将最大的小于 $j$ 的和最小的大于 $j$ 的位置取 $\text{min}$ 加到 $ans$ 中即可。注意没有相同字母时加上测试串长度。

时间复杂度 $\mathcal{O(\sum k \log n)}$，因为题目约束了 $\sum k\le 2\times10^5$ 所以不会 $\texttt{TLE}$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,k;
string s,c;
map<char,vector<int> >mp;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k>>s;
    for(int i=0;i<s.size();i++)
        mp[s[i]].push_back(i);
    for(int i=1;i<=n;i++) 
    {
        int ans=0;
        cin>>c;
        for(int j=0;j<c.size();j++)
        {
            int l=0,r=mp[c[j]].size()-1;
            if(mp[c[j]].size()==0)
            {
                ans+=c.size();
                continue;
            }
            int mid;
            bool flag=0;
            while(l<=r)
            {
                mid=(l+r)>>1;
                if(j>mp[c[j]][mid])l=mid+1;
                if(j<mp[c[j]][mid])r=mid-1;
                if(j==mp[c[j]][mid])
                {
                    flag=1;
                    break;
                }
            }
            if(flag)ans+=1ll*abs(mp[c[j]][mid]-j);
            else ans+=min(1ll*abs(mp[c[j]][l]-j),1ll*abs(mp[c[j]][r]-j));
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

无意间发现的 CF 远古题，水篇题解记录一下。

这**不是正解**。这里给出一种不太好想的差分做法，~~虽然听起来很冗杂而且没必要~~。

---

考虑预处理一个数组 $P$，其中 $p_{i,j}$ 表示标准字符串中离第 $j$ 个位置最近第 $i$ 个字母的位置。

预处理完之后对于每一个询问就可以直接求答案了，关键是如何求解 $P$。

考虑标准字符串中每一个字符对于 $P$ 数组的影响。

这里的思考有两个切入点：

1. 对于字符 $c$ 第一次出现的位置 $i$，$p_{c,1}\sim p_{c,i}$ 均为 $i$，因为之前没有字符 $c$，而最先一次出现 $c$ 的位置就是离 $1\sim i$ 这一段最近的位置。

比如字符串 $S$ 为 `abbc`，在处理第一个 `b` 时我们发现 $p_{s_2,1}\sim p_{s_2,2}$ 均为 $2$。

2. 对于字符 $c$ 最后一次出现的位置 $i$，$p_{c,i}\sim p_{c,k}$ 均为 $i$，因为其后已经没有字符 $c$，而最后一次出现 $c$ 的位置就是离 $i\sim k$ 这一段最近的位置。

比如字符串 $S$ 为 `abbc`，在处理第二个 `b` 时我们发现 $p_{s_3,3}\sim p_{s_3,4}$ 均为 $3$。

在思考完边界情况后，很自然的我们就想到了处理两个在**不同位置出现的相同**字符。

设上一个出现此字符的位置为 $last$，当前出现此字符的位置为 $now$，考虑 $last\sim now$ 这段区间内 $P$ 数组如何赋值。

那么根据区间长度的奇偶性有两种情况（在程序中我把它们变成了一种情况，但本质上是需要分讨的）：

* 奇数情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ep3htaz.png)

发现中间到两端的距离相等，所以赋 $last$ 或 $now$ 均可，而其他点则有唯一答案。

* 偶数情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/plhk45ay.png)

发现所有位置均有唯一答案。

所以考虑使用树状数组维护差分来实现这个区间赋答案的过程。

由于所有位置答案都只赋一次值所以和区间加是等价的，不过要注意加的区间要不重不漏。

时间复杂度 $O((n+k)\log k)$。

---

细节比较多，可能需要一些时间用于调试。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 2e9
#define linf 1e18
#define db double
#define ldb long double
#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i++)
#define me(x,y) memset(x,y,sizeof x)
#define sd std::
#define pii sd pair<int,int>
#define X first
#define Y second
#define umap(x,y) sd unorded_map<x,y>
#define pque(x) sd priority_queue<x>
#define kg putchar(' ')
#define dbg(x) sd cout<<#x<<":"<<x<<"\n"
#define Fr(a) for(auto it:a)
#define il inline
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),x=-x;printt(x);}
il void printk(int x){print(x);kg;}
il void put(int x){print(x);puts("");}
const int N=5e5+10;
char c[N],s[N];
int n,k,last[30];//last[i]记录字母i上一个出现的位置 
struct tree_arr
{
	#define lowbit(x) (x&(-x))
	int s[N];
	int operator[](int x){return s[x];}
	void update(int x,int y){for(;x<=2*k;x+=lowbit(x)) s[x]+=y;}
	int ask(int x){int res=0;for(;x;x-=lowbit(x)) res+=s[x];return res;}
}p[30];
int vis[N];
il void solve()
{
	n=read(),k=read();
	scanf("%s",c+1);
	F(i,0,25) last[i]=1;
	F(i,1,k)
	{
		int d=c[i]-'a';
		int len=i-last[d]+1;
		if(!vis[d])//第一次出现 
		{
			vis[d]=1;
			p[d].update(1,i);
			p[d].update(i+1,-i);//将1~i全赋i 
		}
		else
		{
			p[d].update(last[d]+1,last[d]);
			p[d].update(last[d]+(len+1)/2,-last[d]);
			p[d].update(last[d]+(len+1)/2,i);
			p[d].update(i+1,-i);//赋last~now，我把两种情况写一起了
		}
		last[d]=i;
	}
	me(vis,0);
	F(i,1,k)
	{
		int d=c[i]-'a';
		if(last[d]!=k&&!vis[d])//最后一次出现，并且没赋完 
		{
			vis[d]=1;
			p[d].update(last[d]+1,last[d]);
			p[d].update(k+1,-last[d]);//将 last[d]~k 全赋last[d]
		}
	}
	F(i,1,n)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		int ans=0;
		F(i,1,len)
		{
			int d=s[i]-'a';
			int pp=i>k?k:i;//如果区间长度超出就取k
			ans+=p[d].ask(pp)==0?len:abs(p[d].ask(pp)-i);//记录答案
		}
		put(ans);
	}
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 思路
数据水。

大佬厉害，在下能力不足，写了个模拟，还是过了。

我看前面那位朋友写了 $26$ 个数组来存每个字母的下标，其实不用，拿个二维的桶呗。

在输入标准字符串的时候，预处理，把每个字母的下标放进对应的桶里。有多少个就放在下表为 $0$ 的地方。

每次输入时循环遍历判断最小值，加进 ``ans`` 里就好了。

### 友情提示
像我这样开全局变量的一定要初始化，我改了半个小时，最后发现没重置。看 $17$ 行。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
string stand,test;
long long a[101][200001];
signed main(){
	long long n,m;
	cin>>n>>m;
	getchar();
	getline(cin,stand);
	f(i,0,m-1){
		int now=stand[i]-'a';
		a[now][++a[now][0]]=i;
	}
	while(n--){
		test="";
		getline(cin,test);
		long long ans=0;
		f(i,0,test.size()-1){
			long long now=test[i]-'a',minn=INT_MAX/2;
			if(a[now][0]==0){
				ans+=test.size();
				continue;
			}
			f(j,1,a[now][0]){
				minn=min(minn,abs(a[now][j]-i));
			}
			ans+=minn;
		}
		cout<<ans<<endl;
	} 
	return 0;
}
```

---

## 作者：zibenlun (赞：0)

# 思路

用动态数组记录下所有的字母的位置，每一次搜索到的字符都从记录的下标中找到距离最小的字符（直接循环遍历），如果没有记录就加上 $S$ 的长度。

# 超级简单的代码

主函数前三行没有太大用处可以不写。

```cpp
#include<bits/stdc++.h>
using namespace std;
string c;
vector<int> v[1005];
int n,m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cin>>c;
	for(int i=0;i<c.size();i++)v[c[i]-'a'].push_back(i);
	while(n--){
		long long ans=0;
		string s;
		cin>>s;
		for(int i=0;i<s.size();i++){
			int minn=0x3f3f3f3f;
			if(v[s[i]-'a'].size()==0){
				ans+=s.size();
				continue;
			}
			for(int j=0;j<v[s[i]-'a'].size();j++){
				minn=min(minn,abs(v[s[i]-'a'][j]-i));
			}
			ans+=minn;
		}
		cout<<ans<<"\n";
		ans=0;
	}
	return 0;
}
```


---

## 作者：Guoliyuan2023 (赞：0)

# 题解：CF62B Tyndex.Brome
## 题目
[CF62B 原题传送门](https://www.luogu.com.cn/problem/CF62B)

给定一个字符串作为标准字符串，然后每个字符串都与这个对比。每个字符串的每个字母的位置和标准中这个字母的位置相减取绝对值，最小的结果加到 $ans$ 中，如果没有，把这个字符串的长度加到 $ans$ 中。

## 思路
可以用 `set` 和 `lower_bound` 解，也可以用其他方法。

具体的，用 `set` 存储每个字母对应的所有下标，用 `lower_bound` 搜索对应的上界和下界。

这样题目就简单了许多。

## 温馨提示：
1. 十年 OI 一场空，不开 `long long` 见祖宗。

2. 迭代器指向 `begin` 和 `end` 的时候必须要特殊处理。

3. 题目千万条，诚信第一条，代码不规范，棕名两行泪。（虽然我没放代码，但也别抄别人的昂）
## The End

---

## 作者：yxy666 (赞：0)

题意：给我们一个标准串，然后给我们 $n$ 个测试串进行匹配。对于测试串的每个字母 $B_i$，找到标准串中相同的字母 $A_i$，使 $|i-j|$ 最小并将其加入答案中。若标准串中没有 $B_i$ 这个字母，则将测试串的长度加入答案中。

由于这是多组数据与同一组数据进行比较，我们想要让时间复杂度较优，应该能想到对标准串进行处理。我们将标准串按照 26 个字母进行分类，并从小到大把位置存储起来。

接下来我们对于测试串的处理就方便多了。对于字符 $B_i$，如果标准串中有这个字母，我们就从那些存储的下标找一个最优的就好了。由于这些下标具有单调性，还可以通过二分查找来降低时间复杂度。


```cpp
#include<bits/stdc++.h>
using namespace std;
int Q,m,Ans,size[26];
char mp[100005];
struct yxy{
	int a[10005];
}pos[26];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	Q=read();m=read();
	char ch;
	for(int i=1;i<=m;i++){
		ch=getchar();while(ch<'a'||ch>'z')ch=getchar();
		pos[ch-'a'].a[++size[ch-'a']]=i;
	}
	while(Q--){
		scanf("%s",mp+1);
		int len=strlen(mp+1);Ans=0;
		int L,R,mid,cnt=0;
		for(int i=1;i<=len;i++){
			L=1,R=size[mp[i]-'a'];cnt=0;
			while(L<=R){
				mid=(L+R)/2;
				if(pos[mp[i]-'a'].a[mid]==i){cnt=mid;break;}
				if(pos[mp[i]-'a'].a[mid]>i)R=mid-1;
				else L=mid+1,cnt=mid;
			}//二分查找标准串中第一个小于等于Bi位置
			if(!size[mp[i]-'a'])Ans+=len;
			else {
				int x=(1<<30);
				if(cnt>=1)x=min(x,abs(pos[mp[i]-'a'].a[cnt]-i));
				if(cnt+1<=size[mp[i]-'a'])x=min(x,abs(pos[mp[i]-'a'].a[cnt+1]-i));
				if(cnt>1)x=min(x,abs(pos[mp[i]-'a'].a[cnt-1]-i));
				Ans+=x;//printf("%d value %d\n",i,x);
			}//为了避免出错，将前后各一个位置都刷一遍，图安心
		}
		printf("%d\n",Ans);
	}
	return 0;
}
```


---

