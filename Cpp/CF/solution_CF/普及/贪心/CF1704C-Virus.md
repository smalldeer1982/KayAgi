# Virus

## 题目描述

There are $ n $ houses numbered from $ 1 $ to $ n $ on a circle. For each $ 1 \leq i \leq n - 1 $ , house $ i $ and house $ i + 1 $ are neighbours; additionally, house $ n $ and house $ 1 $ are also neighbours.

Initially, $ m $ of these $ n $ houses are infected by a deadly virus. Each morning, Cirno can choose a house which is uninfected and protect the house from being infected permanently.

Every day, the following things happen in order:

- Cirno chooses an uninfected house, and protect it permanently.
- All uninfected, unprotected houses which have at least one infected neighbor become infected.

Cirno wants to stop the virus from spreading. Find the minimum number of houses that will be infected in the end, if she optimally choose the houses to protect.

Note that every day Cirno always chooses a house to protect before the virus spreads. Also, a protected house will not be infected forever.

## 说明/提示

In the first test case:

At the start of the first day, house $ 3 $ , $ 6 $ , $ 8 $ are infected. Choose house $ 2 $ to protect.

At the start of the second day, house $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ are infected. Choose house $ 10 $ to protect.

At the start of the third day, no more houses are infected.

In the second test case:

At the start of the first day, house $ 2 $ , $ 5 $ are infected. Choose house $ 1 $ to protect.

At the start of the second day, house $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ are infected. No more available houses can be protected.

## 样例 #1

### 输入

```
8
10 3
3 6 8
6 2
2 5
20 3
3 7 12
41 5
1 11 21 31 41
10 5
2 4 6 8 10
5 5
3 2 5 4 1
1000000000 1
1
1000000000 4
1 1000000000 10 16```

### 输出

```
7
5
11
28
9
5
2
15```

# 题解

## 作者：Hovery (赞：8)

# Problem

[Virus](https://www.luogu.com.cn/problem/CF1704C)

注：题目是先保护，后感染。

# Sol

首先对于这样一串房子考虑。

■ 表示被感染。

□ 表示被保护。

⚪表示空房子。

■⚪⚪⚪⚪⚪⚪■

■■ ⚪⚪⚪⚪□■

■■□⚪⚪⚪□■

像上面这种连续空房子只有一个，我们最多保护一个，仅需一次保护操作。

如果这种连续空房有 $x$ 个，我们最多保护 $x - 1$ 个，需要两次保护操作。

那么我们有很多串连续空房怎么办。

■⚪⚪⚪⚪■⚪■

我们是先保护长度为 $4$ 的还是，长度为 $1$ 的？

若先保护长度为 $1$ 的。

■■⚪⚪■■□■

■■■□■■□■

若先保护长度为 $4$ 的。

■■⚪⚪□■■■

■■□⚪□■■■ 

显然保护长度为 $4$ 的更优。

至于为什么，我先~~口胡一下~~。

每次我们保护任意一个的，其他连续空房子串的长度每次会减少 $2$ 或 $1$ ，直到不能再减。

那么肯定是大的减的次数多啊，小的刚好减到零，大的一定不会减完。

所以先保护小的话损失会更大。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

bool cmp(int x, int y)
{
	return x > y;
}

int cnt, m, n, a[100010], b[100010], t;

void solve()
{
	cin >> n >> m;
	for (int i = 1;i <= m;i++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + m + 1);
	b[cnt = 1] = n - a[m] + a[1] - 1;
	for (int i = 2;i <= m;i++)
	{
		b[++cnt] = a[i] - a[i - 1] - 1;
	}
	sort(b + 1, b + cnt + 1, cmp);
	int now = 0, ans = 0;
	for (int i = 1;i <= cnt;i++)
	if (now * 2 < b[i])
	{
		ans += b[i] - now * 2 - ((b[i] - now * 2 == 1) ? 0 : 1);
		now += ((b[i] - now * 2 == 1) ? 1 : 2);//当前这个串该进行多少次感染。
	}
	cout << n - ans << endl;
}

signed main()
{
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：yinhy09 (赞：5)

## 思路讲解：

首先我们可以先把所有未感染城市的段算出来，并把长度存到第二个数组里。（第一个数组要排序，这里赛时卡了我一次）

我们只需要堵住一个段的两端病毒就不会向内传播了，基于此，我们永远会先堵当前最长的段。我们把一个段拿出来看：我们先堵上了左边，那么右边会有一个格子被感染，下一轮我们再堵住右边，就完成了一段的保护。简单画一下可以知道一个长度为 $len$ 的段，我们最多可以保护

$f(len) = \begin{cases}
1 ,& len \le 2 \\
len-1 ,& otherwise.
\end{cases}$

注意这里需要特判 $1$ 和 $2$，否则可能会吃罚时...

保护完了一个段，如果有机会我们肯定能希望保护次大的段，方法同上，只不过次大的段长度要 $-4$，因为已经有四个被感染了。如果次大段的长度 $-4$ 依旧大于 $0$ 就可以保护。

如此类推，保护第三大的段时要判断 $-8$ 是不是大于零，然后根据当前长度套上面的 $f$ 函数即可。

注意：求得是最少感染，我们算的是最多保护，记得用 $n$ 减一下。

讲了这么多，放代码：

## AC Code：

```cpp
// Problem: C. Virus
// Contest: CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Author: Luogu-yinhy09(575320),Codeforces-yinhy09
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll T;
ll n,m;
const int maxn=1e5+5;
ll a[maxn],b[maxn];
ll tot=0,ans=0,k;
int main()
{
	T=read();
	while(T--)
	{
		tot=0;ans=0;
		n=read(),m=read();
		for(int i=1;i<=m;i++)a[i]=read();
		if(n==m)
		{
			printf("%lld\n",n);
			continue;
		}
		if(m==1)
		{
			printf("%lld\n",2);
			continue;
		}
		sort(a+1,a+m+1);
		for(int i=1;i<=m;i++)if(i>1&&a[i]!=a[i-1]+1)b[++tot]=a[i]-a[i-1]-1;
		if(a[m]!=n||a[1]!=1)b[++tot]=(a[1]+n-a[m]-1);
		sort(b+1,b+tot+1);
		if(b[tot]<=2)
		{
			printf("%lld\n",n-1);
			continue;
		}
		if(b[tot]>2)ans+=b[tot]-1;
		k=0;
		for(int i=tot-1;i>=1;i--)
		{
			k++;
			if(b[i]==4*k+1)ans++;
			else if(b[i]>4*k+1)ans+=b[i]-4*k-1;
		}
		printf("%lld\n",n-ans);
	}
	return 0;
}
```
谢谢观看~

---

## 作者：litachloveyou (赞：3)

首先，当被感染的房屋只有一个点时，也就是 $m=1$ 时，我们只需要将被感染房屋两侧的房屋保护起来，这样最终被感染的房屋就只有两个。

当 $m>1$ 时，也就是被感染房屋超过两个以上，此时会形成一个个未感染房屋的区间，类似地，假设被感染房屋为 $0$，未受感染房屋为 $1$，那么第一个样例可以表示为 $1101101011$,因为是个环，所以我们可以看到最大的区间为从第 $9$ 个开始直到第 $2$ 个，也就是说这一段有 $4$ 个未被感染的房屋，很容易就想到贪心，每一次选取最大的区间进行保护，依次往下保护。

每一次保护一段区间需要两天，也就是说，其他未受保护的区间每一次会减少 $4$ 个未感染的房屋，我们只需要每保护 $1$ 次就减少 $4$ 个就可以了。以第一个样例为例，说明第一次应该减少 $1$ 个，之后每次减少 $4$ 个。

注意，当最长区间只有一个未保护的房屋时，要加回去，并且首尾的感染屋也要形成一个区间。

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int>a(m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &a[i]);
	}
	sort(a.begin(), a.end());
	if (m == 1)
	{
		printf("%d\n", 2);
		return;
	}
	priority_queue<int, vector<int>, less<int>>q;
	for (int i = 0; i < m - 1; i++)
	{
		q.push(a[i + 1] - a[i] - 1);
	}
	int dis = n - a[m - 1], diss = a[0] - 1;//首尾感染屋形成区间。
	q.push(dis + diss);
	int cnt = 0;
	int sum = 1;
	while (!q.empty())
	{
		if (q.top() - sum >= 0)
		{
			cnt += max(q.top() - sum, 1);
			sum += 4;//每次少4个。
			q.pop();
		}
		else
			break;
	}
	printf("%d\n", n-cnt);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1BU4y1Y7Tc)

### 2 思路

我们可以只看两座感染的房子之间有多少健康的房子。这 $m$ 段健康的房子的个数我们可以建成一个长为 $m$ 的数列 $b$。

然后，我们要从大到小地排序 $b$。

我们要维护两个数：$cnt$ 和 $ans$，分别为琪露诺的操作次数和永远健康的房子个数。初始均为 $0$。

我们依次枚举 $b$。设当前枚举到 $b_i$。

首先 $b_i\gets b_i-cnt\times2$。这意味着，当琪露诺做完操作的时候 $b_i$ 已经被感染一些了。

+ 如果 $b_i\le0$，意味着琪露诺无法保护任何房子，立刻离开吧。

+ 如果 $b_i\le2$，意味着琪露诺可以通过执行 $1$ 次操作的同时让 $1$ 间房子永远健康。

+ 如果 $b_i>2$，意味着琪露诺可以通过执行 $2$ 次操作的同时让 $b_i-1$ 间房子永远健康。

之所以当初要排序，是因为我们要尽可能保护间隔大于 $2$ 的房子。可以证明，这是最优的。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_m 100000
int t;
int n;
int m;
int a[max_m+2];
int b[max_m+2];
int ans;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1704C_1.in","r",stdin);
	freopen("CF1704C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;++i)scanf("%d",a+i);
		sort(a+1,a+m+1);
		for(int i=1;i<m;++i)b[i]=a[i+1]-a[i]-1;
		b[m]=n-a[m]+a[1]-1;
		sort(b+1,b+m+1,cmp);
		ans=0;
		for(int i=1,cnt=0;i<=m;++i){
			b[i]-=(cnt<<1);
			if(b[i]<=0)continue;
			if(b[i]<=2){
				++cnt;
				++ans;
			}
			else{
				cnt+=2;
				ans+=b[i]-1;
			}
		}
		printf("%d\n",n-ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82185787)

By **dengziyue**

---

## 作者：IYSY2009I (赞：0)

[我的翻译](https://www.luogu.com.cn/paste/erql3h55)

我们很~~不~~容易地发现几点：

1. 如果一段区间内没有病毒感染，且区间的两端都被保护了，那么这段区间永远不会感染。
2. 每次最优操作我们都会去保护一个连续的区间，不会半途而废
3. 当我们选择的区间越大，最后保护的区间就会越大。具体的，假设我们对一段长度为 $x$ 且该区间左右房子都被感染了的区间，最后保护的房子数量
$$pro= \begin {cases} 1 & x\le 2 \\ x-1 & x>2 \end {cases}$$
4. 对于每天，如果我们没有对一个区间进行保护，那么这个区间的长度就会减小 $2$（当然，$x=1$ 除外）。换句话说，今天最大的区间，如果我们不进行保护，到了明天它还是最大。
5. 如果一个区间被保护了，那么以后就不需要再保护了。

结合上面我们发现的性质，我们很容易地想到使用大根堆维护每天的尚未被保护的区间长度的最大值。具体实现请看代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[100005];
priority_queue<int> q;
bool cmp(int x,int y){
	return x<y;
}
void cf(){
	int n=read(),m=read();
	for(int i=1;i<=m;i++)
		a[i]=read();
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(i==m) q.push(n-a[i]+a[1]-1);
		else q.push(a[i+1]-a[i]-1);
	}
	int day=0,ans=0;
	while(!q.empty()){
		int x=q.top();
		q.pop();
		x-=day*2;
		if(x<=0) continue;
		if(x<=2){
			ans++;
			day++;
		}
		else{
			ans+=x-1;
			day+=2;
		}
	}
	printf("%d\n",n-ans);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：happybob (赞：0)

## 题意

有 $n$ 个点首尾相连形成一个环，有其中 $m$ 个点初始时收到了感染。接着会进行若干次操作，每次可以选择一个没有被感染的点，让这个点永远不被感染。然后每个感染的点会感染它旁两个点。问最少感染多少个点。

## 做法

考虑相邻两个被感染的点之间会有若干个点，$n$ 个点总共会形成 $n$ 个连通块，对连通块排序依次保护即可。复杂度 $O(n \log n)$，注意细节处理。


---

## 作者：codemap (赞：0)

## 题目分析
可以发现，最初未被感染的房子可以分成多个连续的段。每一天，每一段两端的两个房子没被感染。

每一天我们的保护只能免疫一个房子，而对于其它的段，每个段健康的房子都会减少两个，直到这个段不足两个房子。

于是，由于我们要最小化的是**感染房子数量**，而**不是**感染段数，策略即为：优先保护长度大的段。这样做的话，长度小的段全部被感染之后就不会新增感染，而更长且拥有更多时间传播的段则可以被保护。

这样，具体做法就很简单了，找出所有的段并从大到小排序，然后依次处理，如果当前这个段还有未被感染的房子，就用两天保护两端，不够就退出。

时间复杂度为 $O(m \log m)$。

## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100001],b[100001];
bool cmp(int x,int y)
{
    return x>y;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t,n,m,i,p,tot,s,ans;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(i=1;i<=m;i++)
            cin>>a[i];
        sort(a+1,a+m+1);
        tot=0;
        if(a[1]>1)//特殊处理第一段
        {
            tot++;
            b[tot]=a[1]-1;
        }
        for(i=1;i<=m;i++)
        {
            p=i;
            while(a[p+1]==a[p]&&p<m)//找到下一个未被感染的段
                p++;
            if(p<m)
            {
                tot++;
                b[tot]=a[p+1]-a[p]-1;
            }
            i=p;
        }
        if(a[m]<n&&a[1]==1)//特殊处理最后一段
        {
            tot++;
            b[tot]=n-a[m];
        }
        if(a[m]<n&&a[1]>1)//如果两段能连上
            b[1]+=n-a[m];
        sort(b+1,b+tot+1,cmp);
        s=0;
        ans=0;
        for(i=1;i<=tot;i++)
        {
            if(b[i]<=s)//如果这段已经全部被感染
                break;
            if(b[i]-s<3)//特判只剩一个房子
            {
                ans++;
                break;
            }
            ans+=b[i]-s-1;
            s+=4;//其他段这段时间会多感染四个
        }
        cout<<n-ans<<"\n";
    }
    return 0;
}
```


---

## 作者：Andrewzdm (赞：0)

思考一下传染的过程：$m$ 个初始感染点会把 $n$ 个点分隔成 $m$ 个区间（当然有的区间长度为 $0$），每个区间在不加任何干预的情况下会每次感染最左端和最右端的点，不断向中间推进直至全部感染。

要让感染的点最少，也就是让健康的点最多。

怎么样才能让健康的点最多呢？

~~古人云：“求木之长者，必固其根本；欲流之远者，必浚其泉源；思国之安者，必积其德义。”要从源头抓起防患于未然。~~

只要在每一段先堵上最左边的传染源再堵上最右边的传染源，就能让中间的点全部不被感染。

那么不难想到一个贪心的思想：先保最长的区间。

时间复杂度 $O(m\log m)$，代码见下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxm = 1e5 + 10;
int n, m, a[maxm], b[maxm];
inline int read();

void work()
{
    n = read();
    m = read();
    for(int i = 1; i <= m; ++i) a[i] = read();
    sort(a + 1, a + m + 1);
    b[1] = n - a[m] + a[1] - 1;
    for(int i = 2; i <= m; ++i)
        b[i] = a[i] - a[i - 1] - 1;
    sort(b + 1, b + m + 1);
    reverse(b + 1, b + m + 1);  //懒人式排序，从大到小
    //其实是赛时智障了一不小心搞成从小到大排序了
    //于是直接加了个reverse补救一下
    int ans = 0, t = 0;
    for(int i = 1; i <= m; ++i)
    {
        ll inf = 2LL * t;  //infected
        if(b[i] - inf <= 0) continue;
        if(b[i] - inf <= 2)  //这种情况只能保一个点
        {
            ans++;
            t++;
            continue;
        }
        ans += b[i] - inf - 1;
        //先堵上左边，然后损失一个点，再堵右边
        t += 2;
    }
    cout << n - ans << endl;
    return;
}

int main()
{
    int T;
    cin >> T;
    while(T--) work();
    return 0;
}

inline int read()
{
    int x = 0; bool f = true; char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = false; ch = getchar(); }
    while(isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return f ? x : -x;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
给你一个环，环上有 $n$ 个房屋，其中有 $m$ 个传染源，每一天，已经感染病毒的房屋会向左右两个房子传染。每一天的开始，你都可以选择一个未传染的房子，并给予其永久保护，在之后的传染中，这座房子永远不会被传染。

传染结束后，问你最少传染多少座房子？

注意：每一天是先选择保护房子，再开始当天的传染。

## 思路
### 性质
在一个环上有 $m$ 个传染源，那么就会把房子分成 $m$ 条安全房的链（链长可能为 $0$）。随着天数的增加，这些安全链都会变短。而我们的永久保护任务就是阻止其变短。

注意到当一条安全链的两端都被永久保护时，那么它就永远不会变短了。而且，保护长的安全链肯定比保护短的优。

当目前链长已被减为负数时，则总和不变即可。
### 实现
注意每一条链每一天变短的长度，第一条链是 $0+1$，第二条链是 $2+3$，第三条链是 $4+5$ 等等。

注意当目前安全链长度缩短后若为 $0$，则其实可以保护住一座房子，因为两端延伸需要两天，可以在第二天前保护住中间的房子。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,m,sum;
int v[100005];
int e[100005];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>m;
    sum=0;
    rep(i,1,m)cin>>v[i];
    sort(v+1,v+m+1);
    rep(i,1,m-1){
      e[i]=v[i+1]-v[i]-1;
    }
    e[m]=n+v[1]-v[m]-1;
    sort(e+1,e+m+1,greater<int>() );
    rep(i,1,m){
      if(e[i]-(i*4-3)>=1)sum+=e[i]-(i*4-3);
      else if(e[i]==(i*4-3))sum+=1;
    }
    cout<<n-sum<<endl;
  }
  return 0;
}
```

---

