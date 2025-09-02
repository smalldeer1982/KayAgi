# [ABC221D] Online games

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc221/tasks/abc221_d

あるオンラインゲームがあり、 $ N $ 人のプレイヤーが登録しています。  
 サービス開始日から $ 10^{100} $ 日を迎えた今日、 開発者である高橋君がログイン履歴を調べたところ、 $ i $ 番目のプレイヤーはサービス開始日を $ 1 $ 日目として、 $ A_i $ 日目から $ B_i $ 日間連続でログインし、 それ以外の日はログインしていなかったことが判明しました。 すなわち、$ i $ 番目のプレイヤーはサービス開始日から、$ A_i $ , $ A_i+1 $ , $ \ldots $ , $ A_i+B_i-1 $ 日目に、 かつそれらの日にのみログインしていたことが分かりました。  
 $ 1\leq\ k\leq\ N $ をみたす各整数 $ k $ について、 サービス開始日から今日までの間で、ちょうど $ k $ 人がログインしていた日数を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 番目のプレイヤーは $ 1 $ 日目と $ 2 $ 日目に、 $ 2 $ 番目のプレイヤーは $ 2 $ 日目と $ 3 $ 日目と $ 4 $ 日目に、 $ 3 $ 番目のプレイヤーは $ 3 $ 日目だけにログインしています。 よって、$ 1 $, $ 4 $ 日目には $ 1 $ 人が、$ 2 $, $ 3 $ 日目には $ 2 $ 人がログインしており、 それ以外の日は誰もログインしていない事が分かります。 答えはちょうど $ 1 $ 人がログインした日数が $ 2 $ 日、 ちょうど $ 2 $ 人がログインした日数が $ 2 $ 日、 ちょうど $ 3 $ 人がログインした日数が $ 0 $ 日となります。

### Sample Explanation 2

$ 2 $ 人以上のプレイヤーがちょうど同じ期間にログインしていることもあり得ます。

## 样例 #1

### 输入

```
3
1 2
2 3
3 1```

### 输出

```
2 2 0```

## 样例 #2

### 输入

```
2
1000000000 1000000000
1000000000 1000000000```

### 输出

```
0 1000000000```

# 题解

## 作者：PineappleSummer (赞：5)

[[ABC221D] Online games](https://www.luogu.com.cn/problem/AT_abc221_d)

简化题意：一个长度为 $2\times 10^9$ 初始全为 $0$ 的序列，进行 $n$ 次操作，每次在一段区间 $[l,r]$ 上加 $1$。对于 $1\le k \le n$，最后输出值为 $k$ 的点的个数。

首先看到区间加 $1$，考虑差分，将区间修改变为单点修改。但是区间长度为 $2\times 10^9$，需要考虑离散化。所以我们开一个 `pair<int,int>` 记录该点的**实际位置和差分值**。按照实际位置从小到大排序。用 $s$ 记录当前点的真正值，每次将 $s$ 加上差分值来更新当前点真正值。**则真正值为 $s$ 的区间为 $p_{i}\sim p_{i+1}$ 这一段，用 $ans_s$ 加上这一段的长度即可。** 最后从 $1$ 到 $n$ 输出 $ans_k$。

核心代码：
```cpp
bool cmp(pii a,pii b){
	return a.first<b.first;//按照实际位置从小到大排序
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		p[++tot]={x,1},p[++tot]={x+y,-1};//差分
	}
	sort(p+1,p+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	{
		s+=p[i].second;//更新真正值
		ans[s]+=p[i+1].first-p[i].first;//累加区间长度
	}
```

复杂度瓶颈在于排序，时间复杂度 $O(n\log n)$。

[完整代码](https://atcoder.jp/contests/abc221/submissions/51411042)

---

## 作者：cjh20090318 (赞：4)

**Update on 2023.6.9 15:58：发现有几个错别字，已改正。**

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给定 $n$ 个区间，第 $i$ 个区间的范围是 $[A_i,A_i+B_i)$。

设 $D_k$ 为有 $k$ 个区间覆盖的长度，请你求出 $\forall k \in [1,n],D_k$。

## 分析

其实这一道题大可不必使用离散化（~~虽然我有很多同学都用了~~），其实只需要在 **`map` 上差分**就可以了！

知道了这一点，其实就并不难了。

时间复杂度 $O(n \log n)$，其中 $O(\log n)$ 为 `map` 所占用的时间复杂度。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<map>
int n;
std::map<int,int> M;//有多少人登录。
int d[200002];
int main(){
	scanf("%d",&n);
	for(int i=0,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		++M[a],--M[a+b];//进行差分。注意是左闭右开，所以右边不需要再加一。
	}
	int lt=0;//记录上一个节点的值。
	for(auto it=M.begin();it!=M.end();++it) it->second+=lt,lt=it->second;//还原差分。
	for(auto it=M.begin(),nx=++M.begin();nx!=M.end();it=nx,++nx) d[it->second]+=(nx->first)-(it->first);
    /*
    两个迭代器，it 为当前迭代器，nx 为下一个的迭代器。
    所以只需要给当前的人数对应的答案加上下一次迭代器的时间减去当前迭代器的时间即可。
    */
	for(int i=1;i<=n;i++) printf("%d ",d[i]);
	return 0;
}

```



---

## 作者：wjr_jok (赞：2)

差分，在每个人开始玩的地方加上 $1$，离开的地方减去 $1$，然后跑一遍输出前缀和就行了。

但是数据范围太大了，考虑离散化，把中间没有发生变化的天数省略掉，在进行求和的时候加上距离即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,cnt;
int x[2100001],y[2100001],xl[2100001],ans[2100001];
map<int,int> fp,cz,wz;//用map离散化
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(!fp[x[i]]){//加入新的点
			fp[x[i]]=1;
			xl[++xl[0]]=x[i];
		}
		if(!fp[x[i]+y[i]]){//同上，这里是结束的点
			fp[x[i]+y[i]]=1;
			xl[++xl[0]]=x[i]+y[i];
		}
	}
	sort(xl+1,xl+xl[0]+1);//将离散化后的点排序
	for(int i=1;i<=xl[0];i++){//记录原位置
		fp[xl[i]]=i;
		wz[i]=xl[i];
	}
	for(int i=1;i<=n;i++){//求出差分数组
		cz[fp[x[i]]]++;
		cz[fp[x[i]+y[i]]]--;
	}
	for(int i=1;i<=xl[0];i++){//通过前缀和得出答案
		ans[cnt]+=wz[i]-wz[i-1];
		cnt+=cz[i];
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
} 
```

---

## 作者：2020luke (赞：2)

# [[ABC221D] Online games](https://www.luogu.com.cn/problem/AT_abc221_d) 题解

## 思路解析

可以发现题目就是单纯区间加和查询每一个值有多少次出现。首先看到区间修改加结束时查询可以想到差分，但是通过 $A_i \le 10^9$ 发现值域很大没法直接根据值差分。于是想到离散化，将每个点离散下来，统计每两个离散的时间之间在线的人乘上时间段的长度即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], b[N], c[5 * N], ans[N];
int main() {
	cin >> n;
	vector<int> v;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		v.push_back(a[i]);
		v.push_back(a[i] + b[i]);
	}
	v.push_back(n + 1);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());	//离散化去重
	for(int i = 1; i <= n; i++) {
		int pa = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		int pb = lower_bound(v.begin(), v.end(), a[i] + b[i]) - v.begin() + 1;
		c[pa]++; c[pb]--;	//差分
	}
	for(int i = 1; i < v.size(); i++) {
		c[i] += c[i - 1];
		ans[c[i]] += v[i] - v[i - 1];	//统计区间
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路

一个显而易见的思路，每次区间修改将天数 $[a_i,a_i+b_i)$ 增加 $1$，然后统计每一天有多少个玩家登录过，最后根据题意统计答案。

使用差分实现修改。

但是数据范围比较大，所以可以离散化或是使用 map。

这里叙述 map 解法，可以在遍历时自动排序。

遍历 map，统计 map 中相邻两个端点内有多少个玩家，计算答案。

复杂度 $O(n\log n)$。
## Code
```cpp
#include<bits/stdc++.h>
#define sd std::
#define il inline
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define X first
#define Y second
#define Fr(a) for(auto it:a)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);putchar(' ');}
const int N=2e5+10;
int n;
int a,b;
sd map<int,int> t;
int ans[N];//ans[i]:有i名玩家登录的有多少天 
il void solve()
{
	n=read();
	F(i,1,n)
	{
		a=read(),b=read();
		t[a]++;
		t[a+b]--;
	}
	int now=0,last=0;//last为上一个端点
	Fr(t)
	{
		ans[now]+=it.X-last;//统计两个端点之间的答案 
		now+=it.Y;
		last=it.X;
	}
	F(i,1,n) printk(ans[i]);
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
我本来和某同学一起 VP 这一场时，都被 D 卡住了，便提议取看一下题解的思路，这不看不知道一看吓一跳，一下就有思路了，然后便有了这一篇题解，但是我竟然发现旁边的同学在对着题解改代码！
# 思路
我们可以发现 $a,b$ 都相当的大，所以我们需要离散化一下并使用差分，然后我们就可以用一个 $now$ 变量存下当前的被覆盖的数量，然后我们要先将每一种操作按照下标排序，然后我们的 $ans_{now}$ 就加上 $f_{i+1}-f_i$ 即可，这里的 $f$ 存的就是位置了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
pair<int,int> f[400100];
int ans[400100],idx;
fire main() {
	in(n);
	rep(i,1,n) {
		int l,r;
		cin>>l>>r;
		f[++idx]={l,1};
		f[++idx]={l+r,-1};
	}
	sort(f+1,f+1+idx);
	int now=0;
	rep(i,1,idx-1) {
		now+=f[i].second;
		ans[now]+=f[i+1].first-f[i].first;
	}
	rep(i,1,n) cout<<ans[i]<<" ";
	return false;
}

```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/AT_abc221_d)

# 题意
给定一个 $n$ 和 $n$ 个区间，求若干个区间被覆盖了 $k$ 层时，这若干个区间的长度和（$k \in [1,n]$）。

# 思路
### 线段树/树状数组
这道题我第一眼看就想到了**线段树**，因为含区间修改和查询，但第二个样例很明显用线段树或是树状数组都是开不下空间的，所以还要在原来的基础上加上**离散化**。这样代码的复杂程度有增加了不少，而且我还~~很懒~~，所以我果断放弃了这种方法，但这绝对也是比赛时一次可以的尝试。

### 我的做法
方法如下：
1. 将每个区间拆成两个时间点。
2. 将拆成的时间点进行排序。
3. 按照顺序遍历时间点。
4. 统计数量。

拆成的时间点要用双关键字储存（比如 ```pair```），第一个关键字储存时间点，第二个关键字储存类型（如果是一个区间的开始就记为 $1$，结束就记为 $-1$）。记录区间时由于输出的是区间长度，所以 ```cnt``` 数组每次要加的是区间长度，而不是 $1$。
## AC Code
```cpp
#include<bits/stdc++.h>  // 开始了！！！
#define ll long long
using namespace std;
const int maxn=2e5+10;
int n,cnt[maxn];
pair<ll,ll> ti9m[maxn*2];  // 用于记录时间点数据
pair<ll,ll> a[maxn];  // 用于记录输入
int main() {
	scanf("%d",&n);  // 输入
	for(int i=1; i<=n; i++) {
		scanf("%lld%lld",&a[i].first,&a[i].second);
//		update(1,1,n,a[i].first,a[i].second);
	}
	// 1. 将每个区间拆成两个时间点。
	for(int i=1; i<=n; i++) {  
		tim[2*i-1]=make_pair(a[i].first,1);
		tim[2*i]=make_pair(a[i].first+a[i].second,-1);
	}
    
	// 2. 将拆成的时间点进行排序。
	sort(tim+1,tim+2*n+1);
	
	// 3. 按照顺序遍历时间点。
	for(int i=1,now=0; i<=2*n; i++) {
		int r=i;
		while(tim[r+1].first==tim[i].first) {
			r++;
			now+=tim[r].second;
		}
		now+=tim[i].second;
		i=r;
        
		// 4. 统计数量+输出。
		cnt[now]+=(tim[i+1].first-tim[i].first);
	}
	for(int i=1; i<=n; i++)	printf("%d ",cnt[i]);
    
	// 我就不打 return 0，就是玩！
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：

很明显是区间修改，所以用差分来解决问题，数据有点大，要进行离散化就做出来了。

### 代码
```
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
typedef long long LL;
using namespace std;

struct node
{
	int end,num;
};
int ans[400010];
node p[400010];
bool cmp(node x,node y)
{
	return x.end<y.end;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		p[++cnt].end=a;
		p[cnt].num=1;
		p[++cnt].end=a+b;
		p[cnt].num=-1;
	}
	sort(p+1,p+cnt+1,cmp);
	int cntt=0;
	for(int i=1;i<=cnt;i++)
	{
		ans[cntt]+=p[i].end-p[i-1].end;
		cntt+=p[i].num;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
}
/*
 */



```

---

## 作者：ttq012 (赞：0)

区间加，单点求值。考虑线段树。

每一次 $a$，$b$ 的修改直接修改 $[a,a+b)$ 区间的值即可。

因为 $a$，$b$ 太大了，所以需要离散化一下。

时间复杂度为 $O(n\log n)$。

然后发现这个东西在查询的时候是静态的，所以考虑先修改再求值。离散化差分一下即可。时间复杂度还是 $O(n\log n)$。

---

## 作者：Saint_ying_xtf (赞：0)

直接差分然后前缀和即可，由于 $a_i \le 10^9$ 所以需要离散化一下。

对于每一个点差分值是 $1$ 或者 $-1$。

对于每一个点和上一个点之间的距离都是上一个点的值。

所以在统计的时候要乘上这个区间长度。

[link](https://atcoder.jp/contests/abc221/submissions/51444473)。

---

## 作者：run_away (赞：0)

## 题意

给 $n$ 组整数 $a_i$ 和 $b_i$，表示有一个人在 $[a_i,a_i+b_i)$ 登录。

求 $\forall k\in [1,n]$，有 $k$ 个玩家登录的天数。

## 分析

很明显的差分，但是因为 $a_i,b_i\le 10^9$，不能直接开差分数组。

注意到 $n\le 2\times 10^5$，所以可以用 pair 数组代替差分数组，每输入一组区间，就用一个 pair 存储。

最后排一下序，像正常差分一样处理就行了。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
ll n,tot,ans[200005];
pair<ll,ll>p[400005];
signed main(){
    n=read();
    for(ll i=1;i<=n;++i){
        ll l=read(),r=read();
        p[++tot]={l,1};
        p[++tot]={l+r,-1};
    }
    sort(p+1,p+tot+1);
    ll sum=0;
    for(ll i=1;i<=tot;++i){
        ans[sum]+=p[i].first-p[i-1].first;
        sum+=p[i].second;
    }
    for(ll i=1;i<=n;++i)printf("%lld ",ans[i]);
}
```

---

## 作者：Autream (赞：0)

#### 题意简述
有 $N$ 个区间，第 $i$ 个区间覆盖 $[x_i,x_i+y_i)$，求 $\forall k \in [1,N]$，被覆盖 $k$ 次的区间长度。

---
#### 题目分析
一开始想到用差分区间修改，然后用循环遍历统计，但是数据范围并不允许我们这样做，所以考虑优化。

因为差分可以通过前缀和还原，所以我们可以使用一个变量累加记录第 $i$ 个位置被覆盖了几次，然后再通过这个区间与相邻区间的长度的差直接求解，时间复杂度 $O(N \log N)$。

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=2e5+5;
int n,cnt,c,ans[N];
PII b[N];
signed main() {
    std::cin>>n;
    rep(i,1,n){
        int x,y;
        std::cin>>x>>y;
        b[++b[0].ff]=m_p(x,1);
        b[++b[0].ff]=m_p(x+y,-1);
    }
    std::sort(arrall(b,b[0].ff));
    rep(i,1,b[0].ff-1){
        cnt+=b[i].ss;
        ans[cnt]+=b[i+1].ff-b[i].ff;
    }
    arrout(ans,n);
    return 0;
}
```

---

