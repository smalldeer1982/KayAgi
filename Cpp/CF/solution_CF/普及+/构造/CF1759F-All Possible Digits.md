# All Possible Digits

## 题目描述

A positive number $ x $ of length $ n $ in base $ p $ ( $ 2 \le p \le 10^9 $ ) is written on the blackboard. The number $ x $ is given as a sequence $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < p $ ) — the digits of $ x $ in order from left to right (most significant to least significant).

Dmitry is very fond of all the digits of this number system, so he wants to see each of them at least once.

In one operation, he can:

- take any number $ x $ written on the board, increase it by $ 1 $ , and write the new value $ x + 1 $ on the board.

For example, $ p=5 $ and $ x=234_5 $ .

- Initially, the board contains the digits $ 2 $ , $ 3 $ and $ 4 $ ;
- Dmitry increases the number $ 234_5 $ by $ 1 $ and writes down the number $ 240_5 $ . On the board there are digits $ 0, 2, 3, 4 $ ;
- Dmitry increases the number $ 240_5 $ by $ 1 $ and writes down the number $ 241_5 $ . Now the board contains all the digits from $ 0 $ to $ 4 $ .

Your task is to determine the minimum number of operations required to make all the digits from $ 0 $ to $ p-1 $ appear on the board at least once.

## 样例 #1

### 输入

```
11
2 3
1 2
4 2
1 1 1 1
6 6
1 2 3 4 5 0
5 2
1 0 1 0 1
3 10
1 2 3
5 1000
4 1 3 2 5
3 5
2 3 4
4 4
3 2 3 0
1 3
2
5 5
1 2 2 2 4
3 4
1 0 1```

### 输出

```
1
1
0
0
7
995
2
1
1
1
2```

# 题解

## 作者：linyihdfj (赞：6)

## CF1759F All Possible Digits
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
可以发现答案一定不会超过 $p-1$，因为我们将第一位加 $p-1$ 次就一定可以使得每一个数都出现一次。

而这个前提下也就是意味着我们最多进一位，所以显然可以考虑分进位与不进位分类讨论。

进位的条件显然就是存在小于它的数且没有出现。

这样讨论完了之后假设第一位为 $x$ 那么小于等于 $x$ 的都出现过，那么我们只需要找到一个最大的且没有出现过的数让 $x$ 加到那个数就好了。

因为我们最多有 $100$ 个数，那么就从可能的最大值直接向下找 $300$ 个数就一定可以找到，但是其实感觉上 $200$ 次就够。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6+5;
int a[N];
map<int,bool> vis;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,p;scanf("%d%d",&n,&p);
		for(int i=1; i<=n; i++)	scanf("%d",&a[i]);
		for(int i=1; i<=n; i++)	vis[a[i]] = true;
		reverse(a+1,a+n+1);
		bool flag = true;
		for(int i=a[1]; i>=max(a[1]-300,0); i--){
			if(!vis[i]){
				flag = false;
			}
		}
		set<int> st;
		int ans = 0;
		int limit = p - 1;
		if(!flag){  //必须进位 
			ans += p - 1 - a[1] + 1;
			limit = a[1] - 1;a[1] = 0;
			a[2]++;
			for(int i=2; i<=n; i++){
				if(a[i] == p)	a[i] = 0,a[i+1]++;
			}
		}
		for(int i=1; i<=n; i++)	vis[a[i]] = true;
		if(a[n+1])	vis[a[n+1]] = true;
		for(int i=limit; i>=max(limit-300,0); i--){
			if(!vis[i]){
				ans = ans + i - a[1]; 
				break;
			}
		}
		printf("%d\n",ans);
		vis.clear();
		for(int i=1; i<=n+1; i++)	a[i] = 0;
	}
	return 0;
}
```

---

## 作者：Exschawasion (赞：4)

题意简述：黑板上有一个 $p$ 进制数 $x$。每次可以从黑板上任意拿出一个数，加一后写到黑板上去。问操作多少次之后可以让黑板上出现从 $0$ 到 $p$ 的所有**数位**。

主要考察思维的严谨全面性。建议评绿或蓝。

***

首先，如果盯紧某个数，对它操作 $p-1$ 次，显然就可以得到所有的数位。不过，有些数字已经存在了，操作的次数可以不需要这么多。

考虑这个 $10$ 进制数：$124567890$。此时唯独 $3$ 没有出现。虽然 $1,2$ 都已经出现了，但是因为每次只能递增 $1$，所以仍然需要操作 $3$ 次。

也就是说可以从两端向中间考虑。首先找到最大的 $x$ 和最小的 $y$ 使得 $[1,x]$、$[y,p-1]$ 都已存在。然后看个位，记作 $a_1$。

- 如果 $a_1<x$，说明只要一直递增上去到 $y$ 就完事了。
- 如果 $a_1>x$，此时你需要一直加，加到进位，然后你才能去解决那些 $[x,a_1)$ 的部分。

两种情况都是好处理的：第一种直接算；第二种需要注意：进位之后可能会产生新的数字，所以必须模拟高精度进位的过程，并且把新的数字统计进去。

可能会有人问：有没有更优解？为什么 $a_1<x$ 一定要递增到 $y$ 呢？建议自行思考后再看文末的解释。~~（能做 *1800 大概都有这个水平自己思考了吧~~

```cpp
void sol(){
	set<int>s;
	cin>>n>>p;
	for(int i=n;i;i--)cin>>a[i],s.insert(a[i]);
	a[n+1]=0;
	if(s.size()==p)return cout<<0<<endl,void();
	int L=0,R=p-1;
	while(s.count(R))R--;
	while(s.count(L))L++;
	if(a[1]<L)return cout<<R-a[1]<<endl,void();
	int ans=0,v=a[1];
	ans+=p-a[1],a[1]=p;
	for(int i=1;i<=n;i++){
		if(a[i]>=p){
			a[i+1]+=a[i]/p,a[i]%=p;
		}
		s.insert(a[i]);
	}
	if(a[n+1])s.insert(a[n+1]);
	while(s.count(v))v--;
	cout<<ans+max(v,0)<<endl;
}
```
解释：显然从 $x$ 到 $y$ 的过程中不可能发生进位。所以唯一的制造新数位的方式就是在个位不停加一。就算 $a_1$ 和 $y$ 中间已经有数字出现过了，但是不经过这些数字你照样到不了 $y$。所以只能一步一步走过去，即 $y-a_1$ 步。

---

## 作者：Z_X_D_ (赞：3)

~~sort 单核~~
# 题目分析
对于每个 $p$ 进制数，最坏的情况就是其最后一位加 $p-1$ 次后使 $0 \sim p-1$ 之间的数都出现一次，因此，答案最大为 $p-1$。

然而，题目给的 $p$ 进制数有 $n$ 位，有一定数量的数是出现过的。

我们可以想到，设这个数的最后一位为 $y$，对于某数 $x$，若 $(x,y]$（$x>y$ 时为 $(x,p-1] \bigcup [0,y]$）之间的数都出现过，我们就只需加 $p-y+x$（$x>y$ 时为 $y-x$）次。

**但是**，在 $y$ 需要进位的情况，也就是 $x<y$ 情况下，进位会使这个数其它位置上的数改变。也就是说在这种情况下，我们还需要对进位后的数进行判断，具体操作和上面差不多。

再看这个题的数据范围，$2 \le p \le 10^9$，开个 $10^9$ 的 ``bool`` 数组判断某数是否出现过显然会炸。除此之外，注意到 $n \le 100$，因此，把这个数各个位置上的数字排一下序，遍历一遍找下标最大的断区在哪，其右端即为最大未出现过的数，再加上之前的判断，复杂度大概是 $O(t \times (n+n \log n))$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[210],b[110];//a开两倍存进位后的数和原数
signed main()
{
	int t,n,p,x,ma,i,j,ans;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&p);
		ma=-1;//记录最大未出现的数
		for(i=1;i<=n;i++)
			scanf("%d",a+i),b[i]=a[n+i]=a[i];//a数组存两遍原数
		x=a[n];//记录最低位上的数
		sort(b+1,b+n+1);
		b[0]=-1;
		b[n+1]=p;//判断0和p-1是否为未出现的数
		for(i=1;i<=n+1;i++)
		{
			if(b[i]>b[i-1]+1)ma=b[i]-1;//可能有重复数字，用大于号
        	//若有断区，右端-1即为最大未出现的数
			if(b[i]==x)break;//0到x都出现过，即后面if里的ma==-1
		}
		if(ma==-1)
		{
			for(j=i;j<=n;j++)
				if(b[j]+1<b[j+1])ma=b[j+1]-1;//找x到p-1没出现过的数（前面已对b排过序）
			if(ma==-1)//全出现过
				printf("0\n");
			else printf("%d\n",ma-x);
		}
		else
		{
			a[n]=p;
			ans=p-x;//最后一位先加到进位
			for(i=n;i>=1;i--)
			{
				if(a[i]>=p)a[i]-=p,a[i-1]+=1;//判断进位
				else break;//如果从某位开始没进位，其前面的位也一定不会进位
			}
			sort(a,a+2*n+1);//对进位后的所有数位和原数数位排序
            //因为a[0]=0=进位后最后一位，所以排序带上a[0]不会有影响
            //况且前面如果一直进位会让a[0]变成1，所以要带上
			ma=-1;
			for(i=1;i<=2*n;i++)
			{
				if(a[i]-1>a[i-1])ma=a[i]-1;
				if(a[i]==x)break;
			}//再找一遍0到x的最大未出现过的数
			if(ma!=-1)printf("%d\n",ma+ans);
			else printf("%d\n",ans);//0到x全出现过则直接输出ans=p-x
		}
	}
    return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/116150640)。

---

## 作者：honglan0301 (赞：2)

没看懂题卡了半天……
## 题意简述
$t\ (1\leq t\leq2\cdot10^3)$ 组数据，每组给一个 $p\ (1\leq p \leq 10^9)$ 进制下的 $n\ (1\leq n\leq100)$ 位数 $x$, 你可以把 $x,x+1,x+2,...,x+k$ 写在黑板上，求最小的正整数 $k$, 使得黑板上出现了 $0$ 到 $p-1$ 间的所有数至少一次。

## 题目分析
首先，$n$ 很小，而 $p$ 又没什么用，所以题目在没有进位的情况下做法是很简单的。记数的末位为 $x_n$, 我们只需要先从 $x_n$ 枚举到 $x_n-n$, 如果还需要就再从 $p-1$ 枚举到 $p-1-n$ 就能知道末位至少要加到多少。  

那我们再来考虑进位。进位时产生的另一个新数字显然来自于 $x_n$ 之前的最近一位 $\neq p-1$ 的数，不妨记这个数为 $x_m$。我们发现只有当 $x_m+1<x_n$, 且 $x_m+1$ 未在初始数列中出现过时才有可能会对结果产生影响，因为如果 $x_m+1>x_n$, 那这个新数字早就已经在进位之前被得到了。  

那么我们只需在最初的基础上，在从 $x_n$ 枚举到 $x_n-n$ 的过程中认为 $x_m+1$ 已经出现过就好了。需要特判的是，如果在进位的影响下才让 $x_n$ 到 $x_n-n$ 都“出现过”，那么就不能再去枚举 $p-1$ 到 $p-1-n$ 了，因为末位至少要加到 $0$ 才会产生进位。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int t,p,n,x[105];
map <int,bool> mp;
int findb()//找"Xm" 
{
	for(int i=n-1;i>=0;i--) 
	{
		if(x[i]!=p-1) 
		{
			return x[i];
		}
	}
}
int calc()//计算答案 
{
	int low=0;
	bool flag=0;
	for(int i=x[n];i>=0;i--)//枚举0~x[n] 
	{
		if(!mp[i])
		{
			if(findb()+1==i)
			{
				flag=1;
				continue;
			}
			low=i+1;
			break;
		}
	}
	if(low)//需要加到一个小于x[n]的数low
	{
		return p-x[n]-1+low;
	}
	else//0~x[n]都已经出现过了 
	{
		if(flag)//特判必须要进位的情况 
		{
			return p-x[n];
		}
		for(int i=p-1;i>=x[n];i--)
		{
			if(!mp[i])
			{
				return i-x[n];
			}
		}
	}
	return 0;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>p;
		mp.clear();
		for(int i=1;i<=n;i++)
		{
			cin>>x[i];
			mp[x[i]]=1;
		}
		cout<<calc()<<endl;
	}
}
```
代码有点乱qwq

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1759F All Possible Digits(luogu)](https://www.luogu.com.cn/problem/CF1759F)

[CF1759F All Possible Digits(codeforces)](https://codeforces.com/contest/1759/problem/F)

# 题意简述

有一个长度为 $n$ 的 $p$ 进制数，你需要求出至少通过几次操作才可以让 $0 \sim p - 1$ 这 $p$ 个数字都**至少**出现过一遍（包括中间过程）。

# 解题思路

我们很容易就能发现答案是具有单调性的，也就是说，如果操作 $x$ 次是合法的，那么操作 $x + 1$ 次也一定是合法的。

然后我们还可以发现一个性质，就是答案一定小于 $p$，因为每一次操作都会使最后一位数字变化，所以操作 $p - 1$ 次最后一位数字会变化 $p$ 次，因此这个性质是正确的。

于是我们可以直接二分最少的操作次数即可，这里我选择使用分讨数字操作后是否进位的方式来进行二分。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
//#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,m;
ll a[110],b[110];
bool check(ll Mid)
{
	forl(i,0,n)
		a[i]=b[i];
	if(Mid+a[n]>=m)
	{
		map<ll,ll>mp;
		forl(i,1,n)
			mp[a[i]]++;
		ll pd=0;
		Mid-=m-a[n];
		ll lst=a[n]-1;
		a[n]=0,a[n-1]++;
		if(n-1==0)
			pd=1;
		forr(i,n-1,1)
		{
			if(a[i]==m)
			{
				a[i]=0,a[i-1]++;
				if(i==1)
					pd=1;
			}
		}
		if(pd)
			forl(i,0,n)
				mp[a[i]]++;
		else
			forl(i,1,n)
				mp[a[i]]++;
		while(mp[lst])
			lst--;
		return lst<=Mid;
	}
	else
	{
		map<ll,ll>mp;
		forl(i,1,n)
			mp[a[i]]++;
		ll lst=m-1;
		while(mp[lst])
			lst--;
		ll nxt=0;
		while(mp[nxt])
			nxt++;
//		cout<<Mid<<":"<<lst-a[n]<<endl;
		if(nxt<a[n])
			return 0;
		return max(0ll,lst-a[n])<=Mid;
	}
}
void solve()
{
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i],b[i]=a[i];
	ll L=0,R=m;
	while(L<R)
	{
		ll Mid=(L+R)/2;
		if(check(Mid))
			R=Mid;
		else
			L=Mid+1;
	}
	cout<<L<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：luo_shen (赞：1)

## 题意描述
初始黑板上有一个 $n$ 位的 $m$ 进制数 $a$，每次可以选择黑板上一个 $m$ 进制数，使它加 $1$，成为一个新的 $m$ 进制数，并写在黑板上，问至少要操作多少次才能使所有的 $m$ 进制数字在黑板上出现至少一次。
## 题目分析
首先只有操作最后出现在黑板上的数才是有效的操作，因为这样得到的数字才是没有出现过的。

有一个显而易见的结论，最低位只会进位一次。因为若进位两次，那么在第一次进位和第二次进位之间，最低位上会出现每一个数字，便可能不会是最少的操作次数。

可以发现若 $k$ 次操作可以使所有数字在黑板上，$k+1$ 次操作也可以，因此可以二分操作次数判断可行性。
## Code
```cpp
int n,m,a[10000];
bool check(int x){
    vector<pii>vis;//存储的二元组(x,y)表示区间[x,y]中的数都出现了至少一次
    int now=x;//now表示当前位增加多少
    for(int i=1;i<=n;i++){
        if(a[i]+now<m){//如果当前位不进位，那么下一位肯定不能增加，[a[i],a[i]+now]出现至少一次
            vis.pb(mp(a[i],a[i]+now));
            now=0;
        }
        else{//进位，区间[a[i],m-1]和[0,now-m+a[i]]中的数出现至少一次
            vis.pb(mp(a[i],m-1));
            vis.pb(mp(0,now-m+a[i]));
            now=1;//下一位增加1
        }
    }
    if(now){
        vis.pb(mp(1,1));
    }//如果所有位都有进位还要记得1也会出现至少一次
    sort(vis.begin(),vis.end());//将二元组按x排序
    if(vis[0].first){//如果0未出现
        return 0;
    }
    int num=vis[0].second;//num表示已经出现的最大的数
    for(int i=1;i<vis.size();i++){
        if(vis[i].first>num+1){//因为是闭区间，所以num是已经出现了的，因此只需要判断num+1是否出现
            return 0;
        }
        num=max(num,vis[i].second);
    }
    return num==m-1;//判断m-1是否出现
}
void solve(){
    read(n),read(m);
    for(int i=n;i;i--){
        read(a[i]);
    }
    int l=0,r=m,ans=0;//因为已知最低位最多进位一次，二分上界设为m即可
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid-1;
            ans=mid;
        }
        else{
            l=mid+1;
        }
    }
    write_endl(ans);
}
```

---

## 作者：LHQing (赞：1)

### 题目分析：

一个直观的性质，答案的上界为 $p-1$。因为最后一位重复加 $1$，会依次出现 $a_n,a_n+1,\dots,p-1,0,1,2,\dots a_n-1$。这个上界可能取不到。因为 $a_n-1,a_n-2,\dots$ 可能在其他位已经有了，或是 $a_n$ 进位时产生。

同时，还有一个性质，就是答案具有单调性。也就是说，记操作次数为 $ans$，若是 $ans$ 不满足题设，而 $ans+1$ 满足题设，那么 $0\sim ans$ 也不满足题设，$ans+1\sim p-1$ 满足题设。因为，若当前已经出现完所有的数的时候，几遍再操作几次，仍然满足题设。

因此我们可以二分答案。在二分答案的时候我们要注意进不进位的问题。每次检查答案的时候，我们开一个 `map` 来记录每个数是否出现过。对于进位的问题，我们特判即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd push_back
#define all(x) x.begin(),x.end()
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
int T;
ll n,p;
ll a[N];
int t;
bool check(map<int,bool> mp,int l,int r,bool flag){
	for(int i=l;i<=r;i++){
		if(flag&&i==t)continue;
		if(!mp.count(i))return false;
	}return true;
}bool check2(map<int,bool> mp,int mid){
	if(a[n]+mid>=p){return check(mp,a[n]+mid+1-p,a[n]-1,true);}
	else{return check(mp,0,a[n]-1,false)&&check(mp,a[n]+mid+1,p-1,false);}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&n,&p);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		map<int,bool> mp;
		for(int i=1;i<=n;i++)mp[a[i]]=true;
		if(mp.size()==p){puts("0");continue;}
		for(int i=n-1;~i;i--)if(a[i]<p-1){t=a[i]+1;break;}
		int l=0,r=p-1;
		while(l<=r){
			int mid=l+r>>1;
			if(check2(mp,mid))r=mid-1;
			else l=mid+1;
		}printf("%d\n",l);
	}return 0;
}
/*
1
5 5
1 2 2 2 4
*/
```

---

## 作者：_NightFire666_ (赞：0)

### 在[博客](https://www.luogu.com.cn/blog/20111219zhr/cf1759f)食用更佳!
## _Brief Description_  
给你一个 $n$ 位的 $p$ 进制数，第 $i$ 位为 $a_i$。

请问最少要让该数加多少次 $1$，可以让数码 $0,\cdots,p−1$ 都出现过（包含在中间过程出现）。
## _Solution_
因为是 $p$ 进制，不难发现答案一定不会超过 $p−1$，也就是说在**最坏情况**下就是其最后一位加至多 $p−1$ 次才可以使得 $0, \cdots ,p-1$ 每一个数码都出现一次。

然而题目给的数有 $n$ 位，是有一定量的数码是出现过的。
所以显然可以考虑分**进位**与**不进位**分类讨论。

进位的条件其实就是存在**小于它的数**且**它没有出现过**。

这样讨论完了之后假设第一位为 $x$ 那么小于等于 $x$ 的都出现过，那么我们只需要找到一个**最大的**且**没有出现过**的数让 $x$ 加到这个数就好了。
### _Code_
```cpp
#include<bits/stdc++.h>                              
using namespace std;              
const int N = 5e6+5;           
int a[N];           
map<int,bool> vis;        
int main(){          
	int t;             
	scanf("%d",&t);          
	while(t--){        
		int n,p;	                  		
		scanf("%d%d",&n,&p);	                   
		for(int i=1; i<=n; i++)	scanf("%d",&a[i]);                
		for(int i=1; i<=n; i++)	vis[a[i]] = true;                
		reverse(a+1,a+n+1);                    
		bool flag = true;                         
		for(int i=a[1]; i>=max(a[1]-300,0); i--)              
			if(!vis[i])                                  
				flag = false;     
		set<int> st;          
		int ans = 0;          
		int limit = p - 1;            
		if(!flag){                       
			ans += p - 1 - a[1] + 1;       
			limit = a[1] - 1;a[1] = 0;     
			a[2]++;                   
			for(int i=2; i<=n; i++){                 
				if(a[i] == p)	a[i] = 0,a[i+1]++;     
			}  
		}                                           
		for(int i=1; i<=n; i++)	vis[a[i]] = true;            
		if(a[n+1])	vis[a[n+1]] = true;              
		for(int i=limit; i>=max(limit-300,0); i--){          
			if(!vis[i]){             
				ans = ans + i - a[1];          
				break;    
			}       
		}                                        
		printf("%d\n",ans);vis.clear();         
		for(int i=1; i<=n+1; i++)	a[i] = 0; 
	}                             
	return 0;              
}
```

---

