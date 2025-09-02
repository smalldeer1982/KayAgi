# Boboniu Chats with Du

## 题目描述

Have you ever used the chat application QQ? Well, in a chat group of QQ, administrators can muzzle a user for days.

In Boboniu's chat group, there's a person called Du Yi who likes to make fun of Boboniu every day.

Du will chat in the group for $ n $ days. On the $ i $ -th day:

- If Du can speak, he'll make fun of Boboniu with fun factor $ a_i $ . But after that, he may be muzzled depending on Boboniu's mood.
- Otherwise, Du won't do anything.

Boboniu's mood is a constant $ m $ . On the $ i $ -th day:

- If Du can speak and $ a_i>m $ , then Boboniu will be angry and muzzle him for $ d $ days, which means that Du won't be able to speak on the $ i+1, i+2, \cdots, \min(i+d,n) $ -th days.
- Otherwise, Boboniu won't do anything.

The total fun factor is the sum of the fun factors on the days when Du can speak.

Du asked you to find the maximum total fun factor among all possible permutations of $ a $ .

## 说明/提示

In the first example, you can set $ a'=[15, 5, 8, 10, 23] $ . Then Du's chatting record will be:

1. Make fun of Boboniu with fun factor $ 15 $ .
2. Be muzzled.
3. Be muzzled.
4. Make fun of Boboniu with fun factor $ 10 $ .
5. Make fun of Boboniu with fun factor $ 23 $ .

Thus the total fun factor is $ 48 $ .

## 样例 #1

### 输入

```
5 2 11
8 10 15 23 5```

### 输出

```
48```

## 样例 #2

### 输入

```
20 2 16
20 5 8 2 18 16 2 16 16 1 5 16 2 13 6 16 4 17 21 7```

### 输出

```
195```

# 题解

## 作者：KellyFrog (赞：7)

小贪心，首先分成 $>m$ 和 $\le m$ 的两组 $big$ 和 $small$，分别从大到小排序。

考虑枚举从 $big$ 中选几个。

根据贪心的思想，这几个 $big$ 一定是在最后几天出现，那么对于选了 $i$ 个的情况，占据的最后的 $(i-1)\cdot(d+1)+1$ 天，为前面空出尽量多的天数选 $small$，注意下细节就行了。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

const int MAXN = 1e5 + 5;

int big[MAXN], small[MAXN], sum[MAXN];
int p1 = 1, p2 = 1;
int n, m, k, x;

signed main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) {
		cin >> x;
		if(x <= k) {
			small[p1++] = x;
		} else {
			big[p2++] = x;
		}
	}
	sort(small + 1, small + 1 + p1, greater<int>());
	sort(big + 1, big + 1 + p2, greater<int>());
	for(int i = 1; i <= p1; i++) {
		sum[i] = sum[i - 1] + small[i];
	}
	int ans = sum[p1], cur = 0;
	for(int i = 1; i <= p2; i++) {
		cur += big[i];
		int days = (i - 1) * (m + 1) + 1; //¨°??-1y¨¢?¦Ì?¨¬¨¬¨ºy¡ê?¡ã¨¹¨¤¡§??¨¬¨¬
		if(days > n) {
			break;
		}
		int left = min(n - days, p1); //?1¨º¡ê??¨¬¨¬??<=k¦Ì?
		ans = max(ans, sum[left] + cur);
	}
	cout << ans << endl;
}

```

---

## 作者：绝顶我为峰 (赞：4)

看完题目感觉是 $dp$ 题目，考虑做法。

发现从前往后推不好做，我们考虑倒着做。

首先将 $a$ 按照和 $m$ 的大小关系分成两组，每组从小到大排序。显然 $dp_n=\max\{a_i\}$，然后考虑每一天，有不禁言和禁言两种选择。

- 如果不禁言，首先 $a_i\leq m$ 的一堆应不为空，那么从 $a_i\leq m$ 的一堆选择没有被使用过的最大值 $maxa$，然后 $dp_i=dp_{i+1}+maxa$。

- 如果禁言，首先 $i+d+1\leq n$ 且 $a_i>m$ 的一堆不为空，那么从 $a_i>m$ 的一堆选择没有被使用过的最大值 $maxa'$，然后 $dp_i=dp_{i+d+1}+maxa'$。

如果以上两种转移都无法进行，那么 $dp_i=dp_{i+1}$。

我们发现这样需要 $n$ 组堆或其他数据结构维护未使用的 $a$，无法承受。

于是我们改用 $vector$ 或数组存储，将先前的 $dp_i$ 记为 $dp_{i,0}$，并且增加 $dp_{i,1},dp_{i,2}$，分别表示未被使用的最大值的位置，这样我们只需要两个 $vector$ 即可。

最后的答案是 $\max\{dp_{i,0}\}$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int n,m,d,a[100001],dp[100001][3],sum,cnt1,cnt2;
vector<int> q1,q2;
signed main()
{
    cnt1=cnt2=-1;
    scanf("%lld%lld%lld",&n,&d,&m);
    for(register int i=1;i<=n;++i)
    {
        dp[i][0]=-1;
        scanf("%lld",&a[i]);
        if(a[i]>m)
        {
            q1.push_back(a[i]);
            ++cnt1;
        }
        else
        {
            q2.push_back(a[i]);
            sum+=a[i];
            ++cnt2;
        }
    }
    if(q1.empty())
    {
        printf("%lld\n",sum);
        return 0;
    }
    sort(q1.begin(),q1.end());
    sort(q2.begin(),q2.end());
    dp[n][0]=q1[cnt1];
    dp[n][1]=cnt1-1;
    dp[n][2]=cnt2;
    for(register int i=n-1;i>=1;--i)
    {
        if(dp[i+1][2]>=0)
        {
            dp[i][0]=dp[i+1][0]+q2[dp[i+1][2]];
            dp[i][1]=dp[i+1][1];
            dp[i][2]=dp[i+1][2]-1;
        }
        if(i+d<n&&dp[i+d+1][1]>=0)
            if(dp[i+d+1][0]+q1[dp[i+d+1][1]]>dp[i][0])
            {
                dp[i][0]=dp[i+d+1][0]+q1[dp[i+d+1][1]];
                dp[i][1]=dp[i+d+1][1]-1;
                dp[i][2]=dp[i+d+1][2];
            }
        if(dp[i][0]==-1)
        {
            dp[i][0]=dp[i+1][0];
            dp[i][1]=dp[i+1][1];
            dp[i][2]=dp[i+1][2];
        }
    }
    int ans=0;
    for(register int i=1;i<=n;++i)
        ans=max(ans,dp[i][0]);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：luogu_gza (赞：2)

考虑一个贪心。

发现一个大于 $m$ 的玩笑一定会引发占位 $d+1$ 天。

考虑将所有大于 $m$ 的开的玩笑都放在最后，那么 $x$ 的大于 $m$ 的玩笑将花费 $1+(x+1) \times (d+1)$ 天。

剩下的使用小于 $m$ 的玩笑。

这道题目只要枚举大于 $m$ 的玩笑的个数就好了。

注意各种边界。

1. 只有大于 $m$ 的玩笑。
2. `vector` 的下标从 $0$ 开始。
3. 记得判掉全部使用小于 $m$ 的玩笑的情况。

### [$\texttt{\color{green}{AC\ code\ is\ here}}$](https://codeforces.com/contest/1394/submission/209918107)

---

## 作者：Dzhao (赞：2)

# 题解 CF1394A
十分有趣的一道贪心题。

我们可以显然发现最后答案的序列一定是长这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/bnjes9e7.png)
而为了使杜以的欢乐值最大，我们所取的 $>m$ 的 $a_i$ 一定是最大的几个，而前面 $x$ 个 $\leq m$ 的 $a_i$ 一定也是最大的几个。于是我们可以将序列 $a$ 排序一下，在一便循环找到最后一个满足 $a_i\leq m$ 的位置，设他为 $pos$ ，然后贪心去做。

我们可以枚举一个 $x$ ， 这样可以算出剩下的还可以取的个数为 $\lceil\dfrac{m-x}{d+1}\rceil$，因为这些天都会导致杜以受到波波牛禁言 $d$ 天的惩罚，所以我们还需要判断一下能能导致禁言的天数是否大于等于 $\lceil\dfrac{m-x}{d+1}\rceil$，满足条件再做下面的步骤。

已经判断满足条件了，那么我们就可以贪心的取，当前状态下的答案就是：

$$\sum_{i=1}^{x}a_i+\sum_{i=1}^{\lceil\frac{m-x}{d+1}\rceil}a_{n-i+1}$$

所以最后的答案就是（若第$i$位不满足上述条件，直接跳过）：

$$\max_{i=1}^{pos} \{\sum_{i=1}^{x}a_i+\sum_{i=1}^{\lceil\frac{m-x}{d+1}\rceil}a_{n-i+1}\}$$

$\mathcal{View \ \ Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x)
{
	x=0;bool f=0;char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x; 
}
typedef long long ll;
const int N=1e5+5;
int n,d,pos=-1;
ll ans,a[N],m,p[N],res;

int main()
{
	rd(n),rd(d),rd(m);
	for(int i=1;i<=n;i++) rd(a[i]); 
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) 
		if(a[i]>m)
		{
			pos=i-1;
			break;
		}
	if(pos==-1) pos=n;
	for(int i=1;i<=n;i++) p[i]=p[i-1]+a[i];
	for(int x=0;x<=pos;x++)
	{
		res=0;
		int k=(n-x)/(d+1);
		int y=n-x-(d+1)*k;
		if(k+(y>0)>n-pos) continue; 
		res=p[n]-p[n-k-(y>0)]+p[pos]-p[pos-x];
		ans=max(res,ans);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Demoe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1394A)

## 题意

- 给定一些数字，求一个序列使满足题意条件的权值和最大，输出权值和。

## Sol

考虑贪心。

每次用大的换掉小的段之和。

我们按照这个枚举即可。

枚举单独的**小于$m$的数的个数**。

（当然这些数一定是选大的。qwq）

我们剩下来就还能用 $[\dfrac{n-i}{d+1}] +(bool)((n-i)\%(d+1))$ 个大的。

不断枚举即可。qwq

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,m,d,a[N],b[N],c[N],cntb,cntc,ans;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(d);rd(m);
	for(ll i=1;i<=n;i++) rd(a[i]);
	sort(a+1,a+n+1);
	for(ll i=n;i>0;i--)
		if(a[i]>m) b[++cntb]=a[i];
		else c[++cntc]=a[i];
	for(ll i=1;i<=n;i++) b[i]+=b[i-1],c[i]+=c[i-1];
	for(ll i=0;i<=n;i++)
		ans=max(ans,c[i]+b[(n-i)/(d+1)+(bool)((n-i)%(d+1))]);
	wr(ans);puts("");
	return 0;
}
```

---

## 作者：Fairicle (赞：1)

简短看题之后应该能发现是个贪心。

但是具体怎么贪值得思考。如果直接贪，会发现这题有种种情况，不好做。

一种解法是枚举选了 $x$ 个小于等于 $m$ 的数，随后大于 $m$ 的数最多就只能选 $min(num,ceil((n-x)/(d+1)))$ 个了。$num$ 代表所有数中大于 $m$ 的数的个数。

code：
```cpp
#define N 100010
ll n,d,m,sa[N],sb[N];
ll ans;
vector<int>a;
vector<int>b;
int main()
{
	std::ios::sync_with_stdio(false);
 	n=rd(),d=rd(),m=rd();
	for(ri i=1;i<=n;++i){
		int x=rd();
		if(x<=m) a.push_back(x);
		else b.push_back(x);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	int siza=a.size(),sizb=b.size();
	for(ri i=1;i<=siza;++i) sa[i]=a[i-1]+sa[i-1];
	for(ri i=1;i<=sizb;++i) sb[i]=b[i-1]+sb[i-1];
	ll ans=0;
	for(ri i=0;i<=siza;++i){
		int can=(n-i-1)/(d+1)+1;
		ans=max(ans,sa[siza]-sa[siza-i]+sb[sizb]-sb[max(0,sizb-can)]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Meaninglessness (赞：0)

## D. Boboniu Chats with Du

**题目大意:**
> Du 会在 Boboniu 的群中待 $n$ 天,如果此时 Du 没有禁言,Ta会开一个玩笑,如果这个玩笑大于 Boboniu 的心情 $m$,Du 就会被禁言 $d$ 天,否则可以继续发言,求出 Du 可以在群里发出玩笑的最大值。
***

**解题思路:**

我们可以模拟求出答案。

考虑到 $>m$ 和 $\le m$ 对于 Boboniu 的影响分为两种情况,我们可以将给出的玩笑值分为两组:

$joke1$:大于心情 $m$ 的所有玩笑值 ;

$joke2$:小于等于心情 $m$ 的所有玩笑值。

分组后两组中的玩笑值对 Boboniu 是没有区别的,根据贪心原则我们可以**优先选组中较大的数**。

接下来我们可以通过枚举选 $Joke1$ 的个数,因为一定会被 Boboniu禁言,所以可以在将它们放在最后,就算被禁言此时$Du$也已经离群。剩下还能发言的时间就去选 $Joke2$ 中较大的数。

***
那么如何求 $joke1$ 占用了几天呢？

我们假设一共选了 $x$ 个 $joke1$ 中的数,每选中一个数就会被禁言 $d$ 天，则可以得出下图:

![Boboniu Chats with Du_1](https://cdn.luogu.com.cn/upload/image_hosting/p286gp0q.png)

得出结论:**$joke1$ 占用 $(x-1)(d-1)+1$ 天,$joke2$ 占用 $n-[(x-1)(d-1)+1]天$**。得出玩笑值后取最大的即可。

根据图上信息我们还要保证 $(x+1)(d+1)+1\le n$ ,取 $min(t2,n-[(x-1)(d-1)+1])$ **($t2$表示$joke2$的长度)**

最后注意前缀和优化和 long long。

***

**代码实现:[Code](https://www.luogu.com.cn/paste/yhleez7m)　时间复杂度$O(n)$**　

---

## 作者：liuyongle (赞：0)

#### 题意简述

提示：这里的“大内容”即为将会被禁言的话，“小内容”即为不会被禁言的话。
> 如果 $a_i > m$，则将其考虑为一个值为 $a_i$ 的“大内容”，否则将其考虑为一个值为 $a_i$ 的“小内容”。选择一些内容并使总值最大。如果未选择某个内容，则意味着被禁言。

#### 思路分析

枚举所选“大内容”的数量，用 $x$ 表示。因此会被禁言 $(x-1)(d+1)+1$ 天。剩余的天数用来放置“小内容”。

考虑使用贪心算法。比如，按值从最大到最小的顺序对内容进行排序，选择先前的 $x$ 个大内容和前的 $n-(x-1)(d+1)-1$ 个小内容并更新答案。

总时间复杂度为 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=int(b);++i)

using namespace std;

typedef long long ll;

const int maxn=1e5+5;
int n,d,m,k,l;
ll a[maxn],b[maxn];

inline int max(int a,int b) { return a>b?a:b; }

void solve(ll a[],int n) {
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	rep(i,1,n)
    	a[i]+=a[i-1];
    return ;
}

int main() {
	scanf("%d%d%d",&n,&d,&m);
	for (int i=0,x;i<n;++i) {
		scanf("%d",&x);
		if (x>m)
        	a[++k]=x;
		else
        	b[++l]=x;
	}
	if(!k) {
		ll s=0;
		rep(i,1,n)
        	s+=b[i];
		printf("%lld\n",s);
		exit(0);
	}
	solve(a,k);
	solve(b,l);
	fill(b+l+1,b+n+1,b[l]);
	ll res=0;
	rep(i,(k + d)/(1+d),k)
    	if(1ll*(i-1)*(d+1)+1<=n)
		res=max(res,a[i]+b[n-1ll*(i-1)*(d+1)-1]);
	printf("%lld\n",res);
	return 0;
}	
```

---

## 作者：引领天下 (赞：0)

设 $f_i$ 表示第 $1\sim i$ 天所能获得的最大快乐值，数组 $b$ 为所有 $\le m$ 的 $a_i$，数组 $c$ 为所有 $>m$ 的 $a_i$，则有以下几种情况：

- 可以说话：

  - 说一句快乐值 $\le m$ 的话，不被禁言，即 $f_i=f_{i+1}+\max{b_j}$，但是需要注意不能重复选取。
  - 说一句快乐值 $>m$ 的话，被禁言，即 $f_i=f_{\min{(i+d+1,n)}}+\max{c_j}$，同样需要注意不能重复选取。
  
那么从后往前做就可以了，答案为 $\max{f_i}$。

**注意！作为边界条件的 $f_n$ 同样需要被统计！我就是因为没统计才惨遭FST的！！！**

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int n,d,m,t,cnt1=-1,cnt2=-1;
long long ans,a[100005],f[100005][3],sum;
/*f[i][0]即是题解中提到的f[i]，f[i][1]和f[i][2]分别存储了到第i天为止，>m和≤m的ai各用到了第几个*/
vector<long long>b1,b2;
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>d>>m;
    for(int i=1;i<=n;f[i++][0]=-1)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)if(a[i]<=m)b2.push_back(a[i]),cnt2++,sum+=a[i];
    else b1.push_back(a[i]),cnt1++;//将a[i]分类存下，因为a已经排过序了，所以b1,b2一定有序
    if(b1.empty()){cout<<sum;return 0;}//不会被禁言，直接输出
    f[n][0]=b1[cnt1];ans=max(ans,f[n][0]);
    f[n][1]=cnt1-1;
    f[n][2]=cnt2;//边界条件，第n天一定选取一个快乐值最大的说话，反正是租后一天，被禁言了也不心疼
    for(int i=n-1;i;i--){
        if(f[i+1][2]!=-1)f[i][0]=f[i+1][0]+b2[f[i+1][2]],f[i][1]=f[i+1][1],f[i][2]=f[i+1][2]-1;//从i+1转移
        if(i+d<n&&f[i+d+1][1]!=-1)
        if(f[i+d+1][0]+b1[f[i+d+1][1]]>f[i][0])f[i][0]=f[i+d+1][0]+b1[f[i+d+1][1]],f[i][1]=f[i+d+1][1]-1,f[i][2]=f[i+d+1][2];//从i+d+1转移
        if(f[i][0]==-1)f[i][0]=f[i+1][0],f[i][1]=f[i+1][1],f[i][2]=f[i+1][2];//继承i+1的答案
        ans=max(ans,f[i][0]);//统计
    }
    cout<<ans;
    return 0;
}
```

---

