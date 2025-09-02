# Nearest Beautiful Number (easy version)

## 题目描述

It is a simplified version of problem F2. The difference between them is the constraints (F1: $ k \le 2 $ , F2: $ k \le 10 $ ).

You are given an integer $ n $ . Find the minimum integer $ x $ such that $ x \ge n $ and the number $ x $ is $ k $ -beautiful.

A number is called $ k $ -beautiful if its decimal representation having no leading zeroes contains no more than $ k $ different digits. E.g. if $ k = 2 $ , the numbers $ 3434443 $ , $ 55550 $ , $ 777 $ and $ 21 $ are $ k $ -beautiful whereas the numbers $ 120 $ , $ 445435 $ and $ 998244353 $ are not.

## 样例 #1

### 输入

```
4
1 1
221 2
177890 2
998244353 1```

### 输出

```
1
221
181111
999999999```

# 题解

## 作者：Miraik (赞：8)

仅针对F1的简单做法。

因为本题中 $k \le 2$，容易发现 $10^9$ 以内所有 $\text{k-beautiful}$ 数数量并不高。$\text{1-beautiful}$ 数显然有 $9\times 9=81$ 个，加上 $n=10^9$ 时的特判，一共是 $82$ 个。$\text{2-beautiful}$ 数在不考虑前导 $\text{0}$ 的情况下，也仅有 $C_{10}^{2}\times 2^{10} <5\times 10^4$ 个。

因此直接暴力预处理出所有 $\text{1-beautiful}$ 与 $\text{2-beautiful}$ 数，再每次二分查询即可。时间复杂度 $O(T \log{m})$，其中 $m<5\times 10^4$，可以轻松通过。

代码：

```cpp
/*
+   +   +   +    +++     +++++     ++++
 + +     + +      +         +      +   +
  +       +       +        +       +   +
 + +      +       +       +        +   +
+   +     +      +++     +++++     ++++
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
const int inf=1<<30;
const ll inff=1ll<<60;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,k,l,r,mid,ans,a[N],b[N],cnta,cntb;
void dfs(int k,int x,int y,int res){
	b[++cntb]=res;
	if(k>9)return;
	if(k>1||x>0)dfs(k+1,x,y,res*10+x);//防止前导0（其实没什么影响？）
	dfs(k+1,x,y,res*10+y);
}
void init(){
	for(int i=1;i<=9;i++)
	    for(int j=1,k=i;j<=9;j++)a[++cnta]=k,k=k*10+i;
        //直接枚举得到1-beautiful数
	a[++cnta]=1111111111;
	for(int i=0;i<=9;i++)
	     for(int j=i+1;j<=9;j++)dfs(1,i,j,0);
         //DFS得到2-beautiful数
	b[++cntb]=1e9; 
	sort(a+1,a+cnta+1);
	sort(b+1,b+cntb+1);
	//printf("%d %d\n",cnta,cntb); 
}
int main(){int tests=1;tests=read();init();
while(tests--){
	n=read();k=read();
    //二分查询第一个大于等于n的k-beautiful数
	if(k==1){
		l=1,r=cnta,ans=a[cnta];
		while(l<=r){
			mid=l+r>>1;
			if(a[mid]>=n)ans=min(ans,a[mid]),r=mid-1;
			else l=mid+1;
		}
	}
	else{
		l=1,r=cntb,ans=b[cntb];
		while(l<=r){
			mid=l+r>>1;
			if(b[mid]>=n)ans=min(ans,b[mid]),r=mid-1;
			else l=mid+1;
		}
	}
	printf("%d\n",ans);
}	return 0;
}

```


---

## 作者：zplqwq (赞：2)

只会做 F1 的人爬了。

这题因为 $k\le 2$ 就很好搞。

分两种情况讨论。

- 很自然 $k=1$ 的时候直接枚举就可以。

```cpp
	for(int i=1;i<=9;i++)
	{
		for(int j=1,k=i;j<=9;j++)
		{
			a[++size]=k;
        	k=k*10+i;
		}
	}
 ```
 
 - 当 $k=2$ 的时候其实也不难，暴力枚举状态然后记录所有满足的数，考虑用 $\text{dfs}$ 实现。
 
```cpp
 void dfs(int k,int x,int y,int ret)
 {
       b[++size2]=ret;
       if(k>9)return;
       if(k>1 or x>0) dfs(k+1,x,y,res*10+x);
       dfs(k+1,x,y,res*10+y);
`}
```
 
 
预处理之后直接二分查询即可。
 
复杂度是 $\log$ 级别的，能过。
 

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1560F1)

***2100**，独立切了。

先看了 F1，然后才过来了，那就两个都一起讲了吧。

记 $n$ 数位排到一个数组上记为 $a$。

先看 F1，不同点在 $1\le k\le 2$。

$k=1$ 是容易的，只能用一种数填，那直接枚举用 $[0,9]$ 哪个填就好了，注意可能位数要增加一位的情况。

$k=2$ 同理，枚举使用哪两个数是 $81$ 种可能，可以承受，所以枚举用哪两个数填就行。

这个填的过程就是枚举 $n$ 的每一位，如果当前填的 $x>a_i$，后面填尽可能小的即可。

于是 F1 就是一个暴力枚举题，不懂为什么有 ***1900**。

看 F2。

首先我们不能枚举用了哪些数，时间复杂度无法承受。

不妨换一种构造方式。

回忆我们怎么比较两个数的大小，位数相同时，我们从高到低位比较，当前数位大的那个对应数值更大。

所以，我们只要枚举数位 $i$，钦定它是第一个大于 $a_i$ 的那个位置，这是本题的突破点。

- 对于 $j \in [1,i)$ 的位置，我们构造的每个位就是 $a_j$。

- 对于 $i$ 位置，如果我们不同的数字有剩余，那就安排上 $a_i+1$，否则只能在用过的数值上安排。

- 对于剩下的位置，我们随意安排，贪心即可。如果有剩余，直接安排 $0$ 即可，如果没有剩余，安排用过的最小的即可。

实现略微有点细节。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
#define DEBUG cout<<"when can get npy"<<endl;
stack<int> sta;
int a[N],tot;
bool vis[N],vis1[N];
void Slove(int n,int k){
	for(int i=0;i<=9;i++)	vis[i]=vis1[i]=false;
	int dis=n,len=0;
	while(dis>0)	sta.push(dis%10),dis/=10;
	tot=0;
	while(!sta.empty())	a[++tot]=sta.top(),sta.pop();
	int ans=0,now=0;
	for(int i=1;i<=tot;i++)	ans=ans*10+9;
	for(int i=1;i<=tot+1;i++){
		int dus=0;
		for(int j=0;j<=9;j++)	dus+=vis[j];
		if(i==tot+1){
			if(dus<=k)	ans=n;
			break;
		}
		if(a[i]==9){
			vis[a[i]]=true,now=now*10+a[i];	
			continue;	
		}
		if(dus>k)	continue;
		for(int j=0;j<=9;j++)	vis1[j]=vis[j];
		int lst=k-dus,predus,nowans=now;
		bool f0=false;
		if(vis1[a[i]+1]==true)	predus=a[i]+1;
		else{
			if(lst>0){
				predus=a[i]+1,vis1[a[i]+1]=true,lst--;	
			}
			else{
				predus=-1;
				for(int j=0;j<=9;j++){
					if(vis1[j]==true&&j>a[i]){
						predus=j;break;
					}
				}
				if(predus==-1){
					f0=true;
				}
			}
		}
		if(f0){
			vis[a[i]]=true,now=now*10+a[i];
			continue;
		}
		nowans=nowans*10+predus;
		int lstU;
		if(lst>0)	lstU=0;
		else{
			for(int j=0;j<=9;j++){
				if(vis1[j]==true)	{lstU=j; break;}
			}
		}
		for(int j=i+1;j<=tot;j++)	nowans=nowans*10+lstU;
		ans=min(ans,nowans);
		vis[a[i]]=true,now=now*10+a[i];
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		Slove(n,k);
	}
	return 0;
}

```

---

## 作者：BHDwuyulun (赞：0)

### 1 题目描述
[传送门](https://www.luogu.com.cn/problem/CF1560F1)
### 2 大体思路
根据题目要求，整数 $x$ 要大于等于 $n$，则可以对 $n$ 从高位开始搜索，如果发现种类数超过 $k$ 则数码换一个比较大的继续搜，当然 $x$ 的位数肯定是和 $n$ 相同的，求 $x$ 的递归边界就是位数达到 $n$ 的位数。
### 3 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int main(){
	ll T;
	cin>>T;
	while(T--){
		ll k;
		string n;
		cin>>n>>k;
		while(1){
			set<char> s;
			for(int i=0;i<n.size();i++){
				s.insert(n[i]);
			}
			if(s.size()<=k){
				break;
			}
			s.clear();
			ll t=0;
			while(1){
				s.insert(n[t]);
				if(s.size()>k){
					while('9'==n[t]){
						--t;
					}
					++n[t];
					for(int i=t+1;i<n.size();i++){
						n[i]='0';
					}
					break;
				}
				t++;
			}
		}
		cout<<n;pr;
	}
    return 0;
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF1560F1 Nearest Beautiful Number (easy version)
## 解析
许多打表或二分，来篇暴力深搜。

定义一个变量 $flag$ 表示是否找到最小解，变量 $big$ 表示构造的数 $x$ 是否比题目给定的 $n$ 大，随后桶数组，表示 $x$ 每位数的出现次数。

找数字时，从小到大遍历，一旦找到合适的数，即可直接输出，节省超多时间。如果搜索时新添一位后出现的位数大于 $k$ 并且这一位以前从未出现，那么一定不行，不要搜索了。否则可以继续搜，注意回溯取消操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,k,flag,big,f[1005];
string p,path;
void dfs(string n,int k,int wei,int sum){
	if(flag==1) return ;//已经有解
	if(wei==n.size()){//位数足够
		cout<<path<<"\n",flag=1;
		return ;
	}
	for(char i=big?'0':n[wei];i<='9';i++){
		if(flag==1) return ;
		if(!f[i]&&sum+1>k) continue;
		f[i]++,path+=i;
		if(i>n[wei]) big=1;
		if(f[i]==1) dfs(n,k,wei+1,sum+1);//多一位数位加一
		else dfs(n,k,wei+1,sum);
		big=0,path.erase(path.size()-1),f[i]--;//回溯取消
	}
}
int main(){
	scanf("%lld",&t);
	while(t--){
		cin>>p>>k;big=flag=0,path="",memset(f,0,sizeof(f));//赋初值
		dfs(p,k,0,0);
	}
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：0)

$\Large{\text{Solution}}$

可以看到 F1 的 $k$ 只会是 $1$ 或 $2$，而这两种数由于限制大，所以不多（$k = 1$ 都可以枚举出 $81$ 个），我们可以打表打出来所有满足条件的数，二分大于等于 $n$ 的第一个。

具体方法：

打 $k = 1$ 的方法很简单，只需要枚举是哪种数，每加一位放一次，最多十位。

```cpp
for (int i = 1; i <= 9; i++)
{
	int x = 0;
  	for (int j = 1; j <= 10; j++)
    	{
      		x = 10 * x + i;
      		s1.insert (x);
      		s2.insert (x);//满足k = 1的也满足k = 2
   	}
}
```
打 $k = 2$ 的需要枚举用哪两个数字，再用类似状态压缩的方法枚举每一位放哪个数。

```cpp
for (int i = 1; i <= 9; i++)
	for (int j = i + 1; j <= 9; j++)
		for (int x = 0; x < (1 << 10); x++) //状态压缩
    	{
        	int y = 0;
        	for (int k = 0; i < 10; k++)
			{
				if ((y >> k) & 1) y = 10 * y + i;
				else y = 10 * y + j;
				s2.insert (y); 
			}
        }// 大概同 k = 1
```
这样就能做 F1 了。

如果愿意可以用 [F2](https://www.luogu.com.cn/article/00kycaga) 的方法做这题。

---

## 作者：loser_seele (赞：0)

一个只针对 F1 的奇怪在线做法。其他题解貌似都是离线。

首先不难发现可以直接对 $ k $ 分类讨论。

当 $ k=1 $ 时，显然 $ 1-\text{beautiful} $ 数只有不到 $ 100 $ 个，打表之后取最小值即可。

$ k=2 $ 的时候，枚举所有情况和 $ k=1 $ 的情况取较小值即可。于是下面的讨论中假设 $ k=2 $。

首先不难发现构造 $ n999999 $ 形式的数一定满足题意，因此答案组成中一定有一个数是首位。然后枚举第二种数，一共有 $ 10 $ 种数字，当我们确定两个数字之后直接 dfs 枚举每个位置上是哪个数即可，一共最多 $ 2^9=512 $ 种可能。但如果朴素实现的话情况数很大，无法通过。

我们类似数位 dp 的思路，观察到题目中限制 $ s \leq n $，那么在枚举的时候我们记录一个变量 $ lim $ 表示之前的位数是否和 $ n $ 一致，如果一致只能枚举 $ \geq n $ 当前位的数字，否则可以随便枚举，当一致的时候枚举 $ >n $ 的数字则更新 $ lim $ 即可。

时间复杂度是 $ \mathcal{O}(Tk) $，其中 $ k=2^9 \times 10 =5120 $，但实际上跑不满可以过。

[提交记录](https://codeforces.com/problemset/submission/1560/195826299)

---

## 作者：DaiRuiChen007 (赞：0)

# CF1560F1 题解



## 思路分析

提供一个能解决两个版本的做法。

考虑直接进行 dp，记 $dp_{i,\mathbf S}$ 表示当前填第 $i$ 位，用过的数码构成集合 $\mathbf S$ 时，第 $i\sim 0$ 位所取得的的最小数值，然后状压 $\mathbf S$ 再套一个 dfs 解数位 dp 的板子即可，搜索的时候要记住从理论最高位（第 $9$ 位）开始搜索并且记录一下当前是否在前导零状态下即可。

由于其取得最小数值一定要先让高位尽可能小，因此查到一组解可以直接 `break`。

时间复杂度 $\Theta(2^{10}\cdot\log_{10}n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=11,MAXS=1<<10;
const int b[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
inline int bit(int x) { return 1<<x; }
int n,k,dp[MAXN][MAXS],a[MAXN];
bool vis[MAXN][MAXS];
inline int dfs(int dig,int S,bool lim,bool qd) {
	if(dig<0) return __builtin_popcount(S)<=k?0:-1; 
	if(!lim&&vis[dig][S]) return dp[dig][S];
	int ret=-1;
	for(int i=(lim?a[dig]:0);i<10;++i) {
		int k=dfs(dig-1,(qd&&i==0)?0:S|bit(i),lim&&(i==a[dig]),qd&&(i==0));
		if(k!=-1) {
			ret=b[dig]*i+k;
			break;
		}
	}
	if(!lim) vis[dig][S]=true,dp[dig][S]=ret;
	return ret;
}
inline void solve() {
	memset(dp,-1,sizeof(dp));
	memset(vis,false,sizeof(vis));
	scanf("%d%d",&n,&k);
	int len=0;
	while(n) {
		a[len]=n%10;
		n/=10,++len;
	}
	for(int i=len;i<=9;++i) a[i]=0;
	printf("%d\n",dfs(9,0,true,true));
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
} 
```



---

## 作者：Jr_Zlw (赞：0)

简单版当然用简单的方法来做啦。

# 预处理打表+二分

### 简单的估计一下

简单版的  $1 \leq k\leq2$  是一个很有利的条件 。

考虑到满足这样的数其实不多，由于  $n\leq 10^9$  大概可以如下计算：

对于  $k=1$  :

- 从  $[0,9]$  内选取一位数，共  $9$  种情况。

- 在  $[1,9]$  内枚举生成的数的位数，每一位都只能为上一步所选的那个数字。

- 因此，共  $9\times 10=90$  种情况。

对于  $k=2$  ：

- 从  $[0,9]$  中选出两个无序的数(可以相等)来组成一个满足  $k$  条件的数，记为  $a,b$  。此时共有  $10\times 10  \div 2=50$  种情况。

- 考虑先从  $[1,9]$  中定下生成的数的位数，即为  $m$  。

- 对于一个  $m$  位数，每一位要么为  $a$  要么为  $b$  ，有  $2^m$  种情况 。

- 那么最后的数最多有  $50\times\sum_{i=1}^{9}2^i =55100$  个。由于有前导  $0$  还会有重复的数，算下来情况数也不会太多。

### 真正的实现过程

上面的推论只是一个估计，在实现中完全没有那么复杂。

- 对于  $k=1$  的情况只需要枚举位数和相同的那一个数即可打出所有满足要求的数。

- 对于  $k=2$  的情况也只需要暴力枚举一个状态就可以记录下所有满足的数。

然后我们把上面的内容记录下来，我们就搞出了所有可以满足要求的数。

对于  $2$  个数组分别排序，去重，然后就可以对每一个询问二分查找，找到那个比  $n$  大的最小的数输出即可。

大力讨论进位？不存在的。

令  $n$  为满足要求的数的个数，复杂度为  $O(n+Tlogn)$  。


贴上代码（为了保险我打了  $10$  位数）：

```
#include<bits/stdc++.h>
#define rep(a,b,c) for(int c=(a);c<=(b);++c)
#define drep(a,b,c) for(int c=(a);c>=(b);--c)
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();bool flag=0;
	while(ch<'0'||ch>'9')flag^=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();
	return flag ? -res : res;
}
const int N=1e6+10;
long long lis[N],lis1[N>>2];int cnt,m,m1;
inline void rcd(int s,int b,int n)
{
	rep(0,(1<<n)-1,i)
	{
		int tmp=i;++cnt;
		
		rep(1,n,i)lis[cnt]=lis[cnt]*10+((tmp&1)?s:b),tmp=tmp>>1;
//		if(s==1&&b==2&&n==4&&i==1)printf("%d\n",lis[cnt]);
	}
}
inline void Solve()
{
	int n=read(),k=read();
	if(k==1)
	{
		int l=1,r=m1,res,mid;
		while(l<=r)lis1[mid=(l+r)>>1]<n?(l=mid+1):(r=mid-1,res=mid);
		printf("%lld\n",lis1[res]);return;
	}
	int l=1,r=m,res,mid;
	while(l<=r)lis[mid=(l+r)>>1]<n?(l=mid+1):(r=mid-1,res=mid);
	printf("%lld\n",lis[res]);return;
}
int main()
{
	rep(0,9,i)rep(i,9,j)rep(1,10,k)rcd(i,j,k);
	sort(lis+1,lis+cnt+1);m=unique(lis+1,lis+cnt+1)-lis-1;
	cnt=0;rep(0,9,i)
	{
		rep(1,10,k)
		{
			++cnt;rep(1,k,j)
			{
				lis1[cnt]=lis1[cnt]*10+i;
			}
		}
	}
	sort(lis1+1,lis1+cnt+1);m1=unique(lis1+1,lis1+cnt+1)-lis1-1;
	int T=read();while(T--)Solve();return 0;
}
```

---

