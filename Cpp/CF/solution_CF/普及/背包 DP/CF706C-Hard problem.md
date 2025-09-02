# Hard problem

## 题目描述

Vasiliy is fond of solving different tasks. Today he found one he wasn't able to solve himself, so he asks you to help.

Vasiliy is given $ n $ strings consisting of lowercase English letters. He wants them to be sorted in lexicographical order (as in the dictionary), but he is not allowed to swap any of them. The only operation he is allowed to do is to reverse any of them (first character becomes last, second becomes one before last and so on).

To reverse the $ i $ -th string Vasiliy has to spent $ c_{i} $ units of energy. He is interested in the minimum amount of energy he has to spent in order to have strings sorted in lexicographical order.

String $ A $ is lexicographically smaller than string $ B $ if it is shorter than $ B $ ( $ |A|<|B| $ ) and is its prefix, or if none of them is a prefix of the other and at the first position where they differ character in $ A $ is smaller than the character in $ B $ .

For the purpose of this problem, two equal strings nearby do not break the condition of sequence being sorted lexicographically.

## 说明/提示

In the second sample one has to reverse string $ 2 $ or string $ 3 $ . To amount of energy required to reverse the string $ 3 $ is smaller.

In the third sample, both strings do not change after reverse and they go in the wrong order, so the answer is $ -1 $ .

In the fourth sample, both strings consists of characters 'a' only, but in the sorted order string "aa" should go before string "aaa", thus the answer is $ -1 $ .

## 样例 #1

### 输入

```
2
1 2
ba
ac
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 3 1
aa
ba
ac
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
5 5
bbb
aaa
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
3 3
aaa
aa
```

### 输出

```
-1
```

# 题解

## 作者：CDFLS_mao_zx (赞：8)

## 这是一道DP水题。  
但我还是会讲得比较细。  
正好同校有人问。  
~~虽然离这件事已经过去了快一年。~~  
好了，废话不说了，来看题。
## 题意解读
翻译译的还可以，这里再加个细节,~~我绝对没踩坑~~。  
Two equal strings nearby do not break the condition of sequence being sorted lexicographically.   
意思是两个相等的字符串不影响排序。  
~~我绝对没用百度翻译，这很丢CDFLS的脸。~~
## 思考过程
看到这题，第一时间应该想到dp。  
我们考虑用dp[i]来表示考虑到i时最小的代价。  
但显然这样无法成功转移，因为转移是有条件的。  
我们可以对翻转之后的字符串和原串放在一起，做一次排序，求出每一个字符串的权值。  
用dp[i][j]表示考虑到i时末尾权值为j的最小代价。
转移方程就很好推了。   
但此时有一个问题，就是我们的时间和空间复杂度太高了。  
考虑优化，显然我们发现每个字符串最多有两种情况，就是正向和反向。  
于是设dp[i][0]表示正向结尾，dp[i][1]表示反向结尾。 
因为我们是一位一位的考虑，所以只需要将当前权值和上一位比较。  
正确的转移方程就列出来了：  
```cpp
if(a[i+n]>=a[i-1])
dp[i][1]=miin(dp[i][1],dp[i-1][0]+v[i]);
if(a[i]>=a[i-1])
dp[i][0]=miin(dp[i][0],dp[i-1][0]);
if(a[i+n]>=a[i+n-1])
dp[i][1]=miin(dp[i][1],dp[i-1][1]+v[i]);
if(a[i]>=a[i+n-1])
dp[i][0]=miin(dp[i][0],dp[i-1][1]);
```
## 一些细节和具体代码  
```
#include<bits/stdc++.h>
#define y1 y749872
#define next nxt
using namespace std;
int i,j,k,n,s,t,m;
inline int read()
{
	int num=0;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	ch=getchar();
	while(ch<='9'&&ch>='0')
	{
		num=num*10+ch-48;
		ch=getchar();
	}
	return num;
}
const int N=1e5+10;
string a[N*2];
long long v[N],dp[N][2];
long long miin(long long aa,long long bb)
{
	return aa<bb?aa:bb;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	scanf("%lld",&v[i]);
	char ch[N];
	for(i=1;i<=n;i++)
	{
	 	scanf("%s",ch);
	 	int l=strlen(ch);
		for(j=0;j<l;j++)
		a[i]+=ch[j];
		for(j=l-1;j>=0;j--)
		a[i+n]+=ch[j]; 
		dp[i][1]=dp[i][2]=1e17+10;
	}
	dp[1][1]=v[1];
	dp[1][0]=0;
	for(i=2;i<=n;i++)
	{
		if(a[i+n]>=a[i-1])
		dp[i][1]=miin(dp[i][1],dp[i-1][0]+v[i]);
		if(a[i]>=a[i-1])
		dp[i][0]=miin(dp[i][0],dp[i-1][0]);
		if(a[i+n]>=a[i+n-1])
		dp[i][1]=miin(dp[i][1],dp[i-1][1]+v[i]);
		if(a[i]>=a[i+n-1])
		dp[i][0]=miin(dp[i][0],dp[i-1][1]);
	}
	if(dp[n][0]<1e17||dp[n][1]<1e17)
	cout<<miin(dp[n][0],dp[n][1]);
	else
	cout<<-1; 
	return 0;
}

```  
#### 细节一
string对以前未加入的东西是不访问的，说白了就是这样写是错的。  
```
scanf("%s",ch);
int l=strlen(ch);
for(j=0;j<l;j++)
a[i][j]=ch[j];
for(j=l-1;j>=0;j--)
a[i+n][j]=ch[l-1-j]; 
```
string只能用cin或getline读，它们都很慢。 
#### 细节二 
这道题c[i]是小于1e9的，但不代表答案在int以内，所以要用long long inf也要开大点。
#### 细节三
欢迎在评论区提问或hack，也欢迎各路大佬指出不足。





    
        
        

---

## 作者：aRenBigFather (赞：5)

考虑到n的范围问题,是10^5次方,那么只能用空间时间为n或者nlogn的方法

现在面对一个单词就有两个决策，要么反转它，要么不反转。所以很轻易地就想到了二维dp。

用 dp[i][0] 表示不反转第i个单词 **而且能使1~i这i个单词按照字典序排列的** 最小消费

用 dp[i][0] 表示反转第i个单词 **而且能使1~i这i个单词按照字典序排列的** 最小消费

值得关注的是,为了方便操作,降低常数复杂度,可以先预处理反转后的字符串(我代码中的 **revstr[]** )

转移如下
```cpp
for(int i=2;i<=n;i++){
	if(str[i-1] <= str[i]){
		dp[i][0] = min(dp[i][0],dp[i-1][0]);
	}
	if(revstr[i-1] <= str[i]){
		dp[i][0] = min(dp[i][0],dp[i-1][1]);
	}
	if(str[i-1] <= revstr[i]){
		dp[i][1] = min(dp[i][1],dp[i-1][0]+cost[i]);
	}
	if(revstr[i-1] <= revstr[i]){
		dp[i][1] = min(dp[i][1],dp[i-1][1]+cost[i]);
	}
}
```

AC代码如下

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 100010;
const ll inf = 1e15;
ll n;
ll cost[maxn];
string str[maxn],revstr[maxn];
ll dp[maxn][2];
int main(){
	memset(dp,0,sizeof dp);
	cin >> n;
	for(int i=1;i<=n;i++) {
		cin >> cost[i];
	}
	//memset(dp,0x3f3f3f3f,sizeof dp);
	for(register int i=0;i<maxn;i++) dp[i][0] = dp[i][1] = inf;
	dp[1][0] = 0;
	dp[1][1] = cost[1];
	for(int i=1;i<=n;i++) {
		cin >> str[i];
		revstr[i] = str[i];
		reverse(revstr[i].begin(),revstr[i].end());
	}
	for(int i=2;i<=n;i++){
		if(str[i-1] <= str[i]){
			dp[i][0] = min(dp[i][0],dp[i-1][0]);
		}
		if(revstr[i-1] <= str[i]){
			dp[i][0] = min(dp[i][0],dp[i-1][1]);
		}
		if(str[i-1] <= revstr[i]){
			dp[i][1] = min(dp[i][1],dp[i-1][0]+cost[i]);
		}
		if(revstr[i-1] <= revstr[i]){
			dp[i][1] = min(dp[i][1],dp[i-1][1]+cost[i]);
		}
	}
	if(min(dp[n][0],dp[n][1]) == inf){
		cout << "-1\n";
		return 0;
	}
	cout << min(dp[n][0],dp[n][1]) << endl;
	return 0;
}
```

---

## 作者：pitiless0514 (赞：2)

## 题目大意

$n$ 个字符串，可以对每个字符串进行翻转，翻转第 $i$ 个字符串的代价是 $c_i$ ，求最后能不能让 $n$ 个字符串字典序递增排序。

$\text{Data Range :} 2 \le n \le 10^5 , |\sum s| \le 10^5$

----
考虑将每个字符串拆成两个点，代表不翻转点与翻转点，然后让每一层两个点向下面字典序大于等于它的连边。

当连到了翻转点的时候，边权就是这个点翻转的代价，否则为 $0$ ，然后跑最短路，最后第 $n$ 层的两个点距离取更小的就是答案。

如果无解，那么必然中间有一层没有连边，所以最后第 $n$ 层点就不会被更新到，答案为极大值。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 225, INF = 2e16 + 7;
int n, num, c[N], nex[N], first[N], v[N], w[N], vis[N], dis[N];
string s[N], t[N];
void add(int from,int to, int val) {
  nex[++num] = first[from]; first[from] = num; v[num] = to; w[num] = val;
}
void dj(int s) {
  for(int i = 0; i <= 3 * n; i++) dis[i] = INF;
  priority_queue < pair<int,int> > q;  q.push( make_pair(0, s) );  dis[s] = 0;
  while( !q.empty() ) {
    int u = q.top().second;  q.pop();
    if( vis[u] ) continue; vis[u] = 1;
    for(int i = first[u]; i; i = nex[i]) {
      int to = v[i], val = w[i];
      if(dis[to] > dis[u] + val) {
        dis[to] = dis[u] + val;
        q.push( make_pair( -dis[to], to ) );
      }
    }
  }
}
signed main () {
  ios :: sync_with_stdio( 0 );
  cin.tie( 0 ), cout.tie( 0 );
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> c[i];
  for(int i = 1; i <= n; i++) {
    cin >> s[i];  reverse(s[i].begin(), s[i].end());
    t[i] = s[i];  reverse(s[i].begin(), s[i].end());
  }
  add(1, 2, 0); add(1, 3, c[1]);
  for(int i = 1; i <= n; i++) {
    int x = 2 * i, y = 2 * i + 1;
    int dx = 2 * (i + 1), dy = 2 * (i + 1) + 1;
    if(s[i] <= s[i + 1]) add(x, dx, 0);
    if(s[i] <= t[i + 1]) add(x, dy, c[i + 1]);
    if(t[i] <= s[i + 1]) add(y, dx, 0);
    if(t[i] <= t[i + 1]) add(y, dy, c[i + 1]);
  }
  dj(1);
  int ans = min( dis[2 * n], dis[2 * n + 1] );
  if(ans >= INF) cout << "-1\n"; 
  else cout << ans << "\n";
  return 0;
}
```

---

## 作者：black_trees (赞：2)


这一道题真的很水。

----

题面已经不用说了。

从这种求最优价的类型和数据范围来看，很明显可以想到DP。

正常情况下我们对于这种线性DP一般都直接设 $f[i]$ 表示考虑第 $i$ 个元素（这里是字符串）时的最优价值。

但是这里很明显不够（会有后效性）。

结合题面的“翻转”操作可以发现，这是属于`0/1` 类型的决策，所以不难想到：可以在后面加一维。

所以设 $f[i][0/1]$ 表示考虑第 $i$ 个字符串的时候翻转或者不翻转的最优价值（`0`表示不动它，`1`表示翻转）

我们又假设 $revs[i]$ 表示 第 $i$ 个字符串翻转后的字符串（借鉴了一下楼上的做法，开始的时候因为用了太多次 `reverse` 被卡了……）。

所以我们可以考虑以下的四种情况：

+ 第 $i-1$ 个字符串的字典序小于等于第 $i$ 个字符串的字典序，此时不用翻转。

+ 第 $i-1$ 个字符串翻转之后的字符串的字典序小于等于第 $i$ 个字符串的字典序，此时只需要翻转前一个 （$i-1$）字符串就行了（这里不用加体力值，因为我们需要在后面更新）

+ 第 $i-1$ 个字符串的字典序小于等于第 $i$ 个字符串翻转之后的字符串的字典序，此时把第 $i$ 个字符串翻转。（这里要加上体力值）

+ 第 $i-1$ 个字符串翻转后的字符串的字典序小于等于第 $i$ 个字符串翻转之后的字符串的字典序，此时把第 $i$ 个字符串和第 $i-1$ 个字符串翻转。（这里也要加上体力值）

---
可能会有点绕，所以：

用代码（方程）描述如下（所有与字符串相关的变量我全部用结构体储存了）：

~~~cpp

    for(register long long i=2;i<=n;++i){
        if(a[i-1].s<=a[i].s){
            f[i][0]=min(f[i-1][0],f[i][0]);
        }
        if(a[i-1].revs<=a[i].s){
            f[i][0]=min(f[i][0],f[i-1][1]);
        }
        if(a[i-1].s<=a[i].revs){
            f[i][1]=min(f[i][1],f[i-1][0]+a[i].val);//val就是体力值
        }
        if(a[i-1].revs<=a[i].revs){
            f[i][1]=min(f[i][1],f[i-1][1]+a[i].val);
        }
    }
~~~

不过在初始化的时候记得让 $f[1][0]=0$ ，$f[1][1]=a[1].val$

对于无解的判断，我们只需要看 $\min(f[n][0],f[n][1])$ 是不是等于开始赋的超级大的值（`inf`）就行了，如果是，那么就是无解，输出 `-1` 。

----

核心代码已经给出来了，所以就不放完整代码了。

---

## 作者：Yukinoshita_Yukino (赞：1)

一道简单 dp。

[link](https://www.luogu.com.cn/problem/CF706C)

题意：给定 $n$ 个字符串，对于每个字符串，可以花费 $c_i$ 的价值将它反转，求让这 $n$ 个字符串按字典序排序的最小花费。
 
先纪录一下每个字符串反转之后的样子，再考虑 dp，设 dp[i] 表示到第 $i$ 个字符串为止是按字典序排序的最小花费。这样我们发现无法有效转移（因为无法确定现在这个字符串是倒序还是正序），考虑加一维。设 dp[i][0/1] 表示到第 $i$ 个字符串为止是按字典序排序的最小花费，且最后一个字符串是编号为 $i$ 的字符串的正序/倒序。

这样我们就得到了转移方程。


```cpp
	if(str[i]>=str[i-1]) dp[i][0]=min(dp[i][0],dp[i-1][0]);
	if(str[i]>=res[i-1]) dp[i][0]=min(dp[i][0],dp[i-1][1]);
	if(res[i]>=res[i-1]) dp[i][1]=min(dp[i][1],dp[i-1][1]+c[i]);
	if(res[i]>=str[i-1]) dp[i][1]=min(dp[i][1],dp[i-1][0]+c[i]);
    // str 表示正序的字符串，res 表示反转之后的字符串。

```

最后注意一下初值即可。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x7fffffffffff;
const int maxn=100010;
int n,c[maxn];
int dp[maxn][2];
string str[maxn],res[maxn];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++)
	{
		dp[i][0]=dp[i][1]=inf;
		cin>>str[i];
		res[i]=str[i];
		reverse(res[i].begin(),res[i].end());
	}
	dp[1][0]=0,dp[1][1]=c[1];
	for(int i=2;i<=n;i++)
	{
		if(str[i]>=str[i-1]) dp[i][0]=min(dp[i][0],dp[i-1][0]);
		if(str[i]>=res[i-1]) dp[i][0]=min(dp[i][0],dp[i-1][1]);
		if(res[i]>=res[i-1]) dp[i][1]=min(dp[i][1],dp[i-1][1]+c[i]);
		if(res[i]>=str[i-1]) dp[i][1]=min(dp[i][1],dp[i-1][0]+c[i]);
	}
	int ans=min(dp[n][0],dp[n][1]);
	if(ans==inf) cout<<"-1";
	else cout<<ans; 
	return 0;
}


```

---

## 作者：Akoasm_X (赞：1)

~~我是脑瘫我写的最短路~~，第一眼没想到DP，然后无脑最短路了

思路大概就是拆两个点，一个点表示没有转过来，一个点表示转过来了

连边要满足字典序的要求，即从字典序小的点连向字典序大的，比较字典序，如果连向反转的点，那边权就加上代价。

然后无解判断是否可达即可

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL inf = 4557430888798830399;
const int maxn = 200020;
int n,tot;
int va[maxn],head[maxn];
LL dist[maxn];
string a,b,c,d;
priority_queue< pair<int,int> > q;
struct node
{
	int to,net,va;
}data[maxn<<2];

inline int read() 
{
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
}

void add(int a,int b,int c)
{
	data[++tot].net = head[a];
	data[tot].to = b;
	data[tot].va = c;
	head[a] = tot;
}


void Dijstra()
{
	memset(dist,0x3f,sizeof(dist));
	dist[1] = 0;dist[1+n] = va[1];
	q.push(make_pair(-dist[1],1));
	q.push(make_pair(-dist[1+n],1+n));
	while(!q.empty())
	{
		pair<int,int> u = q.top();q.pop();
		int x = u.second;
		if(-u.first>dist[x]) continue;
		for(int i=head[x];i;i=data[i].net)
		{
			int to = data[i].to ;
			int va = data[i].va ;
			if(dist[to]>dist[x]+va)
			{
				dist[to] = dist[x] + va;
				q.push(make_pair(-dist[to],to));
			}
		}
	}
}

int main()
{
	n = read();
	for(int i=1;i<=n;i++) va[i] = read();
	for(int i=1;i<=n;i++)
	{
		cin>>c;int len = c.size();d = c;
		for(int j=0;j<=len-j-1;j++) swap(d[j],d[len-j-1]);
		if(a<=c) add(i-1,i,0);
		if(b<=c) add(i-1+n,i,0);
		if(a<=d) add(i-1,i+n,va[i]);
		if(b<=d) add(i-1+n,i+n,va[i]);
		a = c;b = d;
	}
	Dijstra();
	LL Ans = min(dist[n],dist[n+n]);
	Ans==inf ? puts("-1") : printf("%lld\n",Ans);
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

这道题应该是比较简单的线性 dp 类型。

考虑哪些情况对答案有影响：

1. 当前是第几位

2. 当前是否反转

所以我们把它们记在 dp 中，即 $f_{i,0/1}$ 表示第 $i$ 个正着 / 反着放的时候，前面都按照字典序排列的最小的花费。

考虑进行转移。每次枚举上一位的正反和这一位的正反判断是否可行并更新答案即可。转移方程大概是这样的：（$a$ 和 $b$ 表示 $i-1$ 和 $i$ 对应的字符串，不是反的；$c$ 是 $a$ 反过来，$d$ 是 $b$ 反过来）

伪代码大致如下：

```
if a<=b then: // i-1 正 i 正
	dp[i][0] <- min(dp[i][0],dp[i-1][0])
if c<=b then: // i-1 倒 i 正
	dp[i][0] <- min(dp[i][0],dp[i-1][1])
if a<=d then: // i-1 正 i 倒
	dp[i][1] <- min(dp[i][1],dp[i-1][0]+cost[i])
if c<=d then: // i-1 倒 i 倒
	dp[i][1] <- min(dp[i][1],dp[i-1][1]+cost[i])
```

预处理就 $f_{0,0}=f_{0,1}=0$，其他赋成 `INF` 即可，最后的答案显然是 $\min\{f_{n,0},f_{n,1}\}$。（如果是 `INF` 说明没有方案，输出 `-1` 即可）

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=100005;
const ll INF=114514191981000;
ll dp[MAXN][2],cost[MAXN];
string s[MAXN],t[MAXN];
int main(){
	ios::sync_with_stdio(false);
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>cost[i];
	for(int i=1;i<=n;i++){
		cin>>s[i]; t[i]=s[i];
		reverse(t[i].begin(),t[i].end());
		dp[i][0]=dp[i][1]=INF;
	}for(int i=1;i<=n;i++){
		if(s[i-1]<=s[i]) dp[i][0]=min(dp[i][0],dp[i-1][0]);
		if(t[i-1]<=s[i]) dp[i][0]=min(dp[i][0],dp[i-1][1]);
		if(s[i-1]<=t[i]) dp[i][1]=min(dp[i][1],dp[i-1][0]+cost[i]);
		if(t[i-1]<=t[i]) dp[i][1]=min(dp[i][1],dp[i-1][1]+cost[i]);
	}if(min(dp[n][0],dp[n][1])==INF){
		cout<<-1;
		return 0;
	}cout<<min(dp[n][0],dp[n][1]);
	return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

## 问题描述

[CF706C](https://www.luogu.com.cn/problem/CF706C)

[LG-CF706C](https://www.luogu.com.cn/problem/CF706C)

---

## 题解

显然是个线性DP。

设 $f(i,0)$ 代表前 $i$ 个字符串，且在第 $i$ 个字符串不翻转的情况下，能够达成字典序的最小代价.

设 $f(i,1)$ 代表前 $i$ 个字符串，且在第 $i$ 个字符串翻转的情况下，能够达成字典序的最小代价。

$s,t$ 为字符串，若 $s$ 的字典序比 $t$ 小，记为 $s<t$

$f(i,k)=min\{f(i,k),f(i-1,p)\}$ ，条件为 $S(i-1,p)<S(i,k)$ 。

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh=1;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-') fh=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=fh;
}

const int INF=0x3f3f3f3f3f3f3f3fLL;
const int maxn=100007;

int n;
int c[maxn],opt[maxn][2];
string s[maxn],revs[maxn];

void Init(void){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++){
		cin>>s[i];
		revs[i]=s[i];
		for(int x=0,y=s[i].size()-1;x<=y;x++,y--) swap(revs[i][x],revs[i][y]);
	}
}

void Work(void){
//	memset(opt,INF,sizeof(opt));
//	for(int i=1;i<=n;i++) cout<<s[i]<<" "<<revs[i]<<endl;
	for(int i=1;i<=n;i++){
		opt[i][0]=opt[i][1]=INF;
		if(s[i]>=s[i-1]) opt[i][0]=min(opt[i][0],opt[i-1][0]);
		if(s[i]>=revs[i-1]) opt[i][0]=min(opt[i][0],opt[i-1][1]);
		if(revs[i]>=s[i-1]) opt[i][1]=min(opt[i][1],opt[i-1][0]+c[i]);
		if(revs[i]>=revs[i-1]) opt[i][1]=min(opt[i][1],opt[i-1][1]+c[i]);
	}
	int ans=min(opt[n][0],opt[n][1]);
	if(ans==INF) cout<<-1<<'\n';
	else cout<<ans<<'\n';
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	Init();
	Work();
	return 0;
}
```

---

## 作者：MIN__2500 (赞：0)

**尺取法**
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

const int N = 1e5 + 100;
char arr[N];
set<char> ss;
map<char,int> mm;
int main()
{
        int n;
        cin >> n;
        for(int i=1;i<=n;i++)
        {
                cin >> arr[i];
                ss.insert(arr[i]); //应用set去重的性质
        }
        int size = ss.size(); //set的长度为字符串中不同字符的个数
        int ans = n;
        int l = 1,r = 0; 
        int cnt = 0;
        while( l<=n && r<n )
        {
                r++;  
                if(mm[arr[r]]==0) cnt++;  //移动尺子的右端点，若为新出现的字符，cnt++
                mm[arr[r]]++;  //更新map

                while(cnt==size) //当尺子里面刚好有所有的字符，缩小尺子的区间
                {
                        ans = min(ans, r-l+1); //更新答案
                        mm[arr[l]]--;    //删除map里面的l端点
                        if(mm[arr[l]]==0) cnt--; //删除左端点后，若尺子内没有该字符，则cnt--
                        l++; //把尺子左端点右移
                }
                if( l>r ) break;
        }
        printf("%d\n",ans);
        return 0;
}

```


---

