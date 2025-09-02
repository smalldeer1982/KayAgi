# Salazar Slytherin's Locket

## 题目描述

Harry came to know from Dumbledore that Salazar Slytherin's locket is a horcrux. This locket was present earlier at 12 Grimmauld Place, the home of Sirius Black's mother. It was stolen from there and is now present in the Ministry of Magic in the office of Dolorous Umbridge, Harry's former Defense Against the Dark Arts teacher.

Harry, Ron and Hermione are infiltrating the Ministry. Upon reaching Umbridge's office, they observed a code lock with a puzzle asking them to calculate count of magic numbers between two integers $ l $ and $ r $ (both inclusive).

Harry remembered from his detention time with Umbridge that she defined a magic number as a number which when converted to a given base $ b $ , all the digits from $ 0 $ to $ b-1 $ appear even number of times in its representation without any leading zeros.

You have to answer $ q $ queries to unlock the office. Each query has three integers $ b_{i} $ , $ l_{i} $ and $ r_{i} $ , the base and the range for which you have to find the count of magic numbers.

## 说明/提示

In sample test case $ 1 $ , for first query, when we convert numbers $ 4 $ to $ 9 $ into base $ 2 $ , we get:

- $ 4=100_{2} $ ,
- $ 5=101_{2} $ ,
- $ 6=110_{2} $ ,
- $ 7=111_{2} $ ,
- $ 8=1000_{2} $ ,
- $ 9=1001_{2} $ .

Out of these, only base $ 2 $ representation of $ 9 $ has even number of $ 1 $ and $ 0 $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
2
2 4 9
3 1 10
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
2
2 1 100
5 1 100
```

### 输出

```
21
4
```

# 题解

## 作者：Ginger_he (赞：10)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15844504.html)
# 题目描述
求 $l\le x\le r$ 中所有满足 $x_{(b)}$ 中各个数码均出现偶数次的 $x$ 的个数。
# 题解
由于最多只有 $10$ 个不同的数字，因此我们可以对每个数字出现的个数进行**二进制状态压缩**，$0$ 表示出现偶数次，$1$ 表示出现奇数次。下面说一下状态如何转移，因为我们每次要将某一位上的 $0$ 变为 $1$，$1$ 变为 $0$，因此我们将 $sta$ 与 $2^i$ 按位异或即可（$i$ 表示填入的数）。  
接下来就是的**数位 dp** 了，我们传四个参数 $k,sta,p,q$ 进入 dfs，分别表示枚举到第 $k$ 位，当前每个数字出现次数的状态，是否为前导 $0$，以及这一位填的数有没有限制，用 $f$ 数组记忆化即可。
## 注意
- 我们不用计算 $sta$ 中 $1$ 的个数，因为当且仅当 $sta=0$ 时所有数码出现的次数均为偶数
- 只有将 $f$ 数组添加一维表示当前的数是 $b$ 进制才能只初始化一遍，我第一次就是因为这个 WA 了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int q,b,len,a[65];
ll l,r,f[11][65][1024];
ll dfs(int k,int sta,int p,int q)
{
	if(!k)
		return !sta;
	if(!p&&!q&&f[b][k][sta]!=-1)
		return f[b][k][sta];
	int y=q?a[k]:(b-1);
	ll res=0;
	for(int i=0;i<=y;i++)
		res+=dfs(k-1,(p&&!i)?0:(sta^(1<<i)),p&&!i,q&&(i==y));
	if(!p&&!q)
		f[b][k][sta]=res; 
	return res;
}
ll divide(ll x)
{
	len=0;
	while(x)
	{
		a[++len]=x%b;
		x/=b;
	}
	return dfs(len,0,1,1);
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%lld%lld",&b,&l,&r);
		printf("%lld\n",divide(r)-divide(l-1));
	}
	return 0;
}
```

---

## 作者：clamee (赞：4)

这是一道数位dp入门题。

大概只要注意一个优化。

我们记录f[pos][s]为到pos位s状态下的答案。转移也很好转移，具体见代码。

然后我们会发现一遍一遍计算会超时，所以我们把所有进制下的f数组记下来即可。

下面是代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()//fread
{
	int re=0,k=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')k=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){re=re*10+ch-48;ch=getchar();}
	return re*k;
}
int ll=64,f[11][75][2205],ans,l[75],r[75],s1,s2,q,b;//f的第一维为进制
int dfs(int typ,int now,int s,bool lim,bool c)//dp
{
	if(!now)return !s;
	if(f[typ][now][s]!=-1&&lim!=1&&c!=1)return f[typ][now][s];
	int st,sum=0;
	if(lim)st=r[now];
	else st=b-1;
	for(int i=st;i>=0;i--)
	{
		if(c&&(!i))
		{
			sum+=dfs(typ,now-1,s,(i==r[now])&lim,1);
			continue;
		}
		sum+=dfs(typ,now-1,s^(1<<i),(i==r[now])&lim,0);
	}
	if(lim|c)return sum;
	return f[typ][now][s]=sum;
}
signed main()
{
	q=read();
	memset(f,-1,sizeof(f));
	while(q--)
	{
		b=read();s1=read();s2=read();
		s1--;
		for(int i=1;i<=ll;i++)
		{
			l[i]=s1%b;
			s1/=b;
			r[i]=s2%b;
			s2/=b;
		}//转进制
		ans=dfs(b,64,0,1,1);
		for(int i=1;i<=ll;i++)
			r[i]=l[i];
		cout<<ans-dfs(b,64,0,1,1)<<endl;
	}
}
```

---

## 作者：Alex_Eon (赞：2)

[博客内食用效果更佳](https://www.luogu.com.cn/blog/Ksy/solution-cf855e)

思路：数位 DP

本题是一道较为基础的数位 DP，不同数字最多有 $10$ 个，所以用二进制状压表示当前情况：若数字 $i$ 出现次数为偶数，则对应的二进制下的第 $i+1$ 位（即 $2^i$ 的位置）用 $0$ 表示，反之则 $1$。

我们设以下参数进行 DP:
- $now$，表示当前搜索到的位数（采用从高位到低位的顺序）。
- $sta$，对于当前情况的状态压缩。
- $lim$，是否达到数字上限。
- $ze$，是否含前导零。

不同的是，本题多测，所以 DP 所用的 $f$ 数组要多开一个维度表示 $b$ 进制下的结果，方便记忆化。

代码实现需要注意的地方：
- 前导零不计入计算。
- 若不达到上限，则当前最大搜索数字为 $b-1$（$b$ 为进制数）。
- $sta$ 转移时只需采用异或操作：`sta^(1<<i)`。
- 若超时可以尝试检查记忆化部分。

参考代码：
```cpp
#define LL long long
#define UN unsigned
#include<bits/stdc++.h>
using namespace std;
//--------------------//
const int N=100;

LL l,r,b;
//--------------------//
int num[N];
LL f[N][5000][20];//第二维是状态，第三位是进制

LL DFS(int now,bool lim,bool ze,int sta)
{
	if(now==0)
		return sta==0;//只有全出现偶数次才对答案产生贡献
	if(!lim&&!ze&&f[now][sta][b]!=-1)//记忆化
		return f[now][sta][b];
	int lst=lim?num[now]:b-1;//注意上限取值
	LL res=0;
	for(int i=0;i<=lst;i++)
		res+=DFS(now-1,lim&&i==lst,ze&&i==0,(ze&&i==0)?sta:(sta^(1<<i)));//状态转移
	if(!lim&&!ze)
		f[now][sta][b]=res;
	return res;
}

LL solve(LL x)
{
	int len=0;
	while(x)
	{
		num[++len]=x%b;
		x/=b;
	}
	return DFS(len,true,true,0);
}
//--------------------//
int main()
{	
	int T;
	scanf("%d",&T);
	memset(f,-1,sizeof(f));
	while(T--)
	{
		scanf("%lld%lld%lld",&b,&l,&r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
    return 0;
}
```

---

## 作者：peterwuyihong (赞：2)

题意：$1e5$ 组询问，每次询问 $b,l,r$，求 $[l,r]$ 中有多少数在 $b$ 进制下所有数的出现次数都是偶数，$l,r$ 是十进制，$2\le b\le10,1\le l\le r\le 10^{18}$。

首先先差分了，他说 $b$ 进制那你就在 $b$ 进制下搞，你用 $f_{i,j,k}$ 表示 $i$ 进制，奇偶状态为 $k$ 的 $[0,i^j)$ 有几个。

$$f_{i,j,k}=\sum_{num=0}^{i-1}f_{i,j-1,k\oplus2^{num}}$$

边界 $f_{i,0,0}=1,f_{i,1,2^j}=1$。

```cpp
#define maxn 100010
typedef long long i64;
int b;
i64 l,r;
i64 f[11][65][1024];
i64 G(int i,int j,int k){
  if(f[i][j][k]>=0)return f[i][j][k];
  if(j==0)return 0;
  i64 ans=0;
  rep(num,0,i-1)ans+=G(i,j-1,k^(1<<num));
  return f[i][j][k]=ans;
}
int a[20],top;
i64 ask(int jz,i64 x){
  top=0;while(x)a[top++]=x%jz,x/=jz;
  i64 ans=0;int mask=0;
  per(i,top-1,0){
    rep(j,i==(top-1),a[i]-1)ans+=G(jz,i,mask^(1<<j));
    mask^=1<<a[i];
  }
  rep(i,1,top-2)
  if(i&1)rep(j,1,jz-1)
  ans+=G(jz,i,1<<j);
  return ans;
}
void solve(){
  cin>>b>>l>>r;
  cout<<ask(b,r+1)-ask(b,l)<<endl;
}
signed main(){
  memset(f,-1,sizeof f);
  rep(i,2,10){
    f[i][0][0]=1;
    rep(j,0,i-1)f[i][1][1<<j]=1;
  }
  int T;for(cin>>T;T;T--)solve();
}
```
中间大 E 了，边界处理错了。。。

---

## 作者：Fishing_Boat (赞：2)

一道罕见的数位 dp 蓝题。

这道题我们只需要记录是否有前导 $0$，然后通过状态压缩记录每一位是否出现偶数次，然后就有了下面这份代码。

```cpp
ll dfs(ll pos,ll lim,ll zer,ll s){
/*
pos 记录当前枚举到哪一位
lim 记录是否达到上限
zer 记录是否有前导 0
s 记录当前状态
*/
	if(!pos) return !s;
	if(dp[pos][lim][zer][s]!=-1) return dp[pos][lim][zer][s];
	ll up=lim?a[pos]:b-1,res=0;
	for(int i=0;i<=up;i++){
		if(zer&&(!i)){
			res+=dfs(pos-1,0,1,0);
		}else{
			res+=dfs(pos-1,lim&&(i==up),0,s^(1<<i));
		}
	}
	return dp[pos][lim][zer][s]=res;
}
ll work(ll x){
	memset(dp,-1,sizeof(dp));
	ll tot=0;
	while(x){
		a[++tot]=x%b;
		x/=b;
	}
	return dfs(tot,1,1,0);
}
```
不过它成功 TLE 了。为什么会 TLE 呢，我们注意到中间的 ```memset(dp,-1,sizeof(dp));```，这一句话要执行 $q$ 次！那我们要想办法解决掉这个问题。不难发现，在同一进制下，我们在之前记录的可以在之后使用，于是就可以多加一维记录进制，并将 ```memset(dp,-1,sizeof(dp));``` 放在主函数里即可。

---

## 作者：封禁用户 (赞：1)

## 分析

用记忆化搜索来实现数位 DP。

我们定义 $\mathit{f}_{i,j}$ 表示当前搜索到了第 $i$ 为，$0,1,\dots,b-1$ 出现的次数的情况为 $j$ 时的答案。但 $0,1,\dots,b-1$ 一共有 $b$ 个数字，我们如何将其转化成一个数字呢？结合[这篇文章](https://www.luogu.com.cn/blog/734533/p2518-haoi2010-ji-shuo-ti-xie)，我们考虑将 $j$ 变成字符串类型，方法与其相同。得到代码：

```cpp
int a[N],len;
int cnt[M];
map<int,map<string,int>> f;
string get(int b){
	string now="";
	for(int i=0;i<b;i++){
		now+=to_string(cnt[i])+',';
	}
	return now;
}
bool check(string s){
	for(int i=0;i<s.size();i++){
		if(s[i+1]==','){
			if((s[i]-'0')&1){
				return 0;
			}
		}
	}
	return 1;
}
int dfs(int now_where,int if_le,int if_z,int b,string now){
	if(!now_where) return check(now);
	if((!if_le&&!if_z)&&f[now_where].count(now)) return f[now_where][now];
	int ans=0,up=if_le?a[now_where]:b-1;
	for(int i=0;i<=up;i++){
		if(if_z&&!i) ans+=dfs(now_where-1,if_le&&i==up,1,b,now);
		else{
			cnt[i]++;
			ans+=dfs(now_where-1,if_le&&i==up,0,b,get(b));
			cnt[i]--;
		}
	}
	if(!if_le&&!if_z) f[now_where][now]=ans;
	return ans;
}
int check(int x,int b){
	f.clear();
	len=0;
	while(x){
		a[++len]=x%b,x/=b;
	}
	return dfs(len,1,1,b,get(b));
}
int q,b,l,r;
void solve(){
	cin>>q;
	while(q--){
		cin>>b>>l>>r;
		memset(cnt,0,sizeof(cnt));
		cout<<check(r,b)-check(l-1,b)<<"\n";
	}
}
```
很显然的是，我们每次都去转化成字符串是不行的，所以考虑优化。

注意到，对于一个 $b$ 进制数 $x$，若令 $\mathit{cnt}_{i}$ 表示在 $x$ 的数位中 $i$ 出现的次数。则 $x$ 满足要求的条件是：$\mathit{cnt}_{0} \bmod 2=0,\mathit{cnt}_{1} \bmod 2=0,\dots,\mathit{cnt}_{b-1} \bmod 2=0$。这只跟 $\mathit{cnt}_{i}$ 的奇偶性有关。故放弃字符串的方法，使用更快更方便的二进制压缩。

一个 $b$ 位的二进制数 $x$，我们用其从高到低的第 $i$ 位表示在 $b$ 进制数 $y$ 中，$\mathit{cnt}_{i-1}$ 的奇偶性。则 $y$ 满足要求的条件就变成了：$x=0$，也就是说二进制数 $x$ 的每一位的值都是 $0$。将 $\mathit{cnt}_{i}$ 的奇偶性反转（$0$ 变成 $1$，$1$ 变成 $0$），我们就可以这样写：`x=x^(1<<i)`。因为亦或有性质 $1 \oplus 0=1,1 \oplus 1=0$。得到代码：

```cpp
int a[N],len,f[N][M];
inline int dfs(int now_where,int if_le,int if_z,int b,int now_ans){
	if(!now_where) return !now_ans;
	if((!if_le&&!if_z)&&f[now_where][now_ans]!=-1) return f[now_where][now_ans];
	int ans=0,up=if_le?a[now_where]:b-1;
	for(register int i=0;i<=up;i++)
		if(if_z&&!i) ans+=dfs(now_where-1,if_le&&i==up,1,b,now_ans);
		else ans+=dfs(now_where-1,if_le&&i==up,0,b,now_ans^(1<<i));
	if(!if_le&&!if_z) f[now_where][now_ans]=ans;
	return ans;
}
inline int check(int x,int b){
	memset(f,-1,sizeof(f));
	len=0;
	while(x) a[++len]=x%b,x/=b;
	return dfs(len,1,1,b,0);
}
```
如果把代码写成这样，还是会在第 $10$ 个点 TLE……具体的原因，不难发现是 $\mathit{f}$ 数组清空的问题。我们需要优化这个，注意到，对于同一个进制 $b$，我们是只需要清空 $\mathit{f}$ 数组 $1$ 次的，而 $1 \le b \le 10,1 \le q \le 10^5$。我们可以给 $\mathit{f}$ 多加一维：$\mathit{f}_{k,i,j}$ 表示在 $k$ 进制下，搜索到第 $i$ 为，二进制状态为 $j$ 时的答案。

注：二进制状态转化成 $10$ 进制的最大值为：$2^{10}=1024$，也就是 $f$ 数组中，$j$ 的这一维不大于 $1024$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=65,M=1024;
int q,b,l,r;
int a[N],len,f[11][N][M];
inline int dfs(int now_where,int if_le,int if_z,int b,int now_ans){
	if(!now_where) return !now_ans;
	if((!if_le&&!if_z)&&f[b][now_where][now_ans]!=-1) return f[b][now_where][now_ans];
	int ans=0,up=if_le?a[now_where]:b-1;
	for(register int i=0;i<=up;i++)
		if(if_z&&!i) ans+=dfs(now_where-1,if_le&&i==up,1,b,now_ans);
		else ans+=dfs(now_where-1,if_le&&i==up,0,b,now_ans^(1<<i));
	if(!if_le&&!if_z) f[b][now_where][now_ans]=ans;
	return ans;
}
inline int check(int x,int b){	
	len=0;
	while(x) a[++len]=x%b,x/=b;
	return dfs(len,1,1,b,0);
}
inline void solve(){
	memset(f,-1,sizeof(f));
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld",&b,&l,&r);		
		printf("%lld\n",check(r,b)-check(l-1,b));
	}
}
signed main(){
	solve();
	return 0;
}
```


---

## 作者：UltiMadow (赞：1)

这题好水啊，不至于黑吧（

我来提供一个空间更优的解法

注：本解法时间复杂度 $\Theta(q\log q + 2^bb \log n)$，比其他题解里解法多了一个 $\Theta(q\log q)$，空间复杂度 $\Theta(2^b\log n)$，其他题解是 $\Theta(2^bb\log n)$

其实算法本质没啥区别，数位dp部分也没啥区别，就是我们把所有的询问离线下来以 $b$ 为关键字排序，接下来每做到一个新的 $b$ 就初始化一次

这种做法时间上只增加了一个小常数，空间上优化了 $b=10$ 倍，还是比较值得的

~~如果出题人再恶毒一点卡空间的话，本做法的优越性就体现出来了~~

code here:
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
#define int long long
using namespace std;
int T;
struct Node{int l,r,b,q;}que[MAXN];
bool cmp(Node x,Node y){return x.b<y.b;}
int f[70][1<<11],num[70],ans[MAXN];
int dfs(int len,int st,bool mx,bool zero,int b)
{
	if(!len)return st?0:1;
	if(f[len][st]!=-1&&mx&&zero)return f[len][st];
	int lmt=mx?b-1:num[len],ret=0;
	for(int i=0;i<=lmt;i++)
		ret=(ret+dfs(len-1,(zero||i)?st^(1<<i):st,mx||(i<lmt),zero||i,b));
	if(mx&&zero)f[len][st]=ret;
	return ret;
}//数位dp
int solve(int x,int b,bool init)
{
	if(init)memset(f,-1,sizeof(f));//如果b不一样则初始化
	int cnt=0;
	while(x){num[++cnt]=x%b;x/=b;}
	return dfs(cnt,0,0,0,b);
}
signed main()
{
	cin>>T;
	for(int i=1;i<=T;i++)cin>>que[i].b>>que[i].l>>que[i].r,que[i].q=i;
	sort(que+1,que+T+1,cmp);//离线+排序
	for(int i=1;i<=T;i++)
	{
		bool init=false;
		if(i==1||que[i].b!=que[i-1].b)init=true;
		ans[que[i].q]=solve(que[i].r,que[i].b,init)-solve(que[i].l-1,que[i].b,false);//记录答案
	}
	for(int i=1;i<=T;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

毒瘤数位 DP 题。

首先，你可以用一个 `vector` 储存每一个数字出现的次数，然后用 `map` 记忆化。

然后可以得到如下 [TLE #8 的代码](https://www.luogu.com.cn/paste/nhfv2271)。

因为 `map` 自带一只 $\log$ 所以，考虑将 `map` 优化掉。但是，现在每一种数字可能会出现很多次，所以要用 `vector` 维护出现次数，但这样必定需要用 `map` 一类的东西维护。

但是，本题只需要维护每一个数字出现次数的奇偶性，所以，你就可以用二进制来维护一下，这样就把 `map` 优化掉了。

然后可以得到如下 [TLE #11 的代码](https://www.luogu.com.cn/paste/ixc6f2wt)。

因为 $q$ 是一个很大的数，然而，我们在每一次记忆化搜索的时候都要 `memset(dp,-1,sizeof(dp))`，所以时间复杂度直接降为 $\Theta(q2^mm)$。（其中 $m$ 为数字的长度）

但是，在对于同一个进制 $s$ 时，每一次相同位置的 $dp$ 值是相同的，所以，直接再开一维表示进制即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 110,M = 2010,K = 15;
int T,s,l,r;
int arr[N];
int dp[K][N][M];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int dfs(int u,int st,bool z,bool lm){
	if (!u) return (!st);
	if (!z && !lm && ~dp[s][u][st]) return dp[s][u][st];
	int res = 0,Max = s - 1;
	if (lm) Max = arr[u];
	for (re int i = 0;i <= Max;i++){
		if (i || !z) st ^= (1ll << i);
		res += dfs(u - 1,st,z && (!i),lm && (i == Max));
		if (i || !z) st ^= (1ll << i);
	}
	if (!z && !lm) dp[s][u][st] = res;
	return res;
}

inline int calc(int x){
	int len = 0;
	while (x){
		arr[++len] = x % s;
		x /= s;
	}
	return dfs(len,0,true,true);
}

signed main(){
	memset(dp,-1,sizeof(dp));
	T = read();
	while (T--){
		s = read();
		l = read();
		r = read();
		printf("%lld\n",calc(r) - calc(l - 1));
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

这个很明显是数位 dp，我们要考虑的是怎么做这个 dp。

我们发现对于每个 $b$ 问题是类似的，我们可以直接在 $f$ 上加一维 $b$ 记录。

现在的问题就是问在 $b$ 进制下 $[l,r]$ 有多少满足条件的数。我们考虑用一种快速的方式表示出某一个数 $X_{(b)}$ 每个数字出现的次数。发现其实并不关心具体多少，$2,4,6,8,10$ 次 在我们眼中是一样的。所以记录奇偶性就行。

奇偶性只有两种，可以自然地想到状压。

那么现在设 $f[b][i][sta]$ 表示目前在 $b$ 进制下，前 $i$ 个数，状态为 $sta$ 的方案数。

接下来这一位比如说是 $x$，那么 $sta\gets sta \oplus 2^x$，也就是这一位原来是奇数现在就是偶数次，原来偶数次同理。直接套一个数位 dp 板子就可以通过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll f[15][70][1<<12];
ll lg[70];
int cnt,t,b;
ll l,r;
inline ll dp(bool limit,bool lzero,int dep,int sta,int b)
{
	if(dep==0)return sta==0;
	else if(!limit && !lzero && f[b][dep][sta]!=-1)return f[b][dep][sta];
	else
	{
		ll ret=0;
		int i,nxt=limit?lg[dep]:b-1;
		for(i=0;i<=nxt;++i)
			ret+=dp(limit&&(i==nxt),lzero&&(i==0),dep-1,(lzero&&i==0)?0:(sta^(1<<i)),b);
		if(!limit && !lzero)f[b][dep][sta]=ret;
		return ret;
	}
}
inline ll solve(ll x,int b)
{
	cnt=0;while(x)
	{
		lg[++cnt]=x%b;
		x/=b;
	}
	return dp(1,1,cnt,0,b);
}
int main()
{
	memset(f,-1,sizeof f);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %lld %lld",&b,&l,&r);
		printf("%lld\n",solve(r,b)-solve(l-1,b));
	}
}
```

---

## 作者：无钩七不改名 (赞：0)

数位 dp 板子题，采用记忆化 dfs 解决。

我们定义 $dp[i][js][qz0][sx]$ 为当前是从高位往低位数第 $i$ 个位，前面 $0$~$b-1$ 中出现次数有 $js$ 个是奇数。$qz0$ 表示前面是否都是前缀 $0$，$sx$ 表示是否到达上限。

用一个数组 $o_i$ 表示数字 $i$ 出现的次数是奇数还是偶数，采用位运算进行转化即可。

还有不要用 memset 初始化，会 TLE ……原因是每次 dp 数组不一定会用满。

## 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int q,b;
long long l,r;
int a[70],len,o[70];
long long dp[70][70][2][2];

long long dfs(int i,int js,bool qz0,bool sx){
	//cout<<i<<" "<<" "<<lst<<endl;
	if(i>len)return js==0;
	if(len-i+1<js)return dp[i][js][qz0][sx]=0,0;
	if(dp[i][js][qz0][sx]!=-1)return dp[i][js][qz0][sx];
	dp[i][js][qz0][sx]=0;
	int maxn=b-1;
	if(sx)maxn=a[i];
	for(int j(0);j<=maxn;j++){
		if(qz0&&j==0){
			dp[i][js][qz0][sx]+=dfs(i+1,0,1,sx&&j==a[i]);
		}
		else{
			o[j]^=1;
			dp[i][js][qz0][sx]+=dfs(i+1,js+o[j]-(o[j]==0),0,sx&&j==a[i]);
			o[j]^=1;
		}
	}
	return dp[i][js][qz0][sx];
} 

long long f(long long x){
	//cout<<x<<":"<<endl;
	len=0;
	while(x){
		a[++len]=x%b;
		x/=b;
	}
	//memset(dp,-1,sizeof(dp));
	//memset(o,0,sizeof(o));
	for(int i(0);i<=b;i++)o[i]=0;
	for(int i1(0);i1<=len;i1++)
		for(int i2(0);i2<=len;i2++)
			for(int j1(0);j1<=1;j1++)
				for(int j2(0);j2<=1;j2++)
					dp[i1][i2][j1][j2]=-1;
	reverse(a+1,a+1+len);
	return dfs(1,0,1,1);
}

int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d%lld%lld",&b,&l,&r);
		printf("%lld\n",f(r)-f(l-1));	
	}
	return 0;
} 
```


---

## 作者：Utilokasteinn (赞：0)

## [Link](https://www.luogu.com.cn/problem/CF855E)

题目大意：已知 $l$ 和 $r$，求在 $k$ 进制下区间 $[l,r]$ 中有几个数满足每个数码都出现偶数次。

挺显然这是一道数位dp。

因为要求每个数码只能出现偶数次，所以我们在做dp时需要记录每个数码出现的次数。进一步，只需要记录当前数码出现次数的奇偶性。

但这样需要开一个 $10$ 维数组，很不好做。这里可以状压一下。

我们设 $f_{i,j}$ 表示前 $i+1$ 位中，各个数字出现次数的奇偶性状态为 $j$，且后 $i$ 为可以是任意数时，一共有几个数可以满足各数码出现的次数为偶数 。

令 $j$ 的最低为第 $0$ 位，那么第 $k$ 位为 $0$ 则表示数码 $k$ 出现了奇数次，否则为偶数次。

考虑有多个进制，所以数组还要多开一维表示进制数。

注意前导零不算在内。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()
{
	ll s=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s;
}
int q,base;
ll l,r,f[11][65][2050];
int cnt,num[65];
ll dfs(int pos,int state,bool lead,bool limit)
{
	if(!pos)return !state;
	if(!lead&&!limit&&f[base][pos][state]!=-1)
		return f[base][pos][state];
	int len=limit?num[pos]:base-1;ll res=0;
	for(int i=0;i<=len;i++)
		if(!i&&lead)res+=dfs(pos-1,0,1,limit&&i==len);
		else res+=dfs(pos-1,state^(1<<i),0,limit&&i==len);
	if(!lead&&!limit)f[base][pos][state]=res;
	return res;
}
ll solve(ll x)
{
	cnt=0;
	while(x)num[++cnt]=x%base,x/=base;
	return dfs(cnt,0,1,1);
}
int main()
{
	q=read();
	memset(f,-1,sizeof(f));
	while(q--)
	{
		base=read(),l=read(),r=read();
		printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}
```


---

## 作者：orz_z (赞：0)



数位 `dp` 板子。

先差分，再记 $f_{i,j,k}$ 表示在 $i$ 进制下有 $j$ 位，并且每个数字出现次数的奇偶性是 $k$ 的数的个数。

转移方程：$f_{i,j,k}=\sum\limits_{m=0}^{i - 1}f_{i,j-1,k⊕2^{m}}$。

时间复杂度 $\mathcal O(\log_b(r)2^bb^2)$。

---

