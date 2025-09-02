# Coffee and Coursework (Hard Version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Polycarp has to write a coursework. The coursework consists of $ m $ pages.

Polycarp also has $ n $ cups of coffee. The coffee in the $ i $ -th cup Polycarp has $ a_i $ caffeine in it. Polycarp can drink some cups of coffee (each one no more than once). He can drink cups in any order. Polycarp drinks each cup instantly and completely (i.e. he cannot split any cup into several days).

Surely, courseworks are not being written in a single day (in a perfect world of Berland, at least).

Let's consider some day of Polycarp's work. Consider Polycarp drinks $ k $ cups of coffee during this day and caffeine dosages of cups Polycarp drink during this day are $ a_{i_1}, a_{i_2}, \dots, a_{i_k} $ . Then the first cup he drinks gives him energy to write $ a_{i_1} $ pages of coursework, the second cup gives him energy to write $ max(0, a_{i_2} - 1) $ pages, the third cup gives him energy to write $ max(0, a_{i_3} - 2) $ pages, ..., the $ k $ -th cup gives him energy to write $ max(0, a_{i_k} - k + 1) $ pages.

If Polycarp doesn't drink coffee during some day, he cannot write coursework at all that day.

Polycarp has to finish his coursework as soon as possible (spend the minimum number of days to do it). Your task is to find out this number of days or say that it is impossible.

## 说明/提示

In the first example Polycarp can drink fourth cup during first day (and write $ 1 $ page), first and second cups during second day (and write $ 2 + (3 - 1) = 4 $ pages), fifth cup during the third day (and write $ 2 $ pages) and third cup during the fourth day (and write $ 1 $ page) so the answer is $ 4 $ . It is obvious that there is no way to write the coursework in three or less days.

In the second example Polycarp can drink third, fourth and second cups during first day (and write $ 4 + (2 - 1) + (3 - 2) = 6 $ pages) and sixth cup during second day (and write $ 4 $ pages) so the answer is $ 2 $ . It is obvious that Polycarp cannot write the whole coursework in one day in this test.

In the third example Polycarp can drink all cups of coffee during first day and write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15 $ pages of coursework.

In the fourth example Polycarp cannot drink all cups during first day and should drink one of them during the second day. So during first day he will write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) = 14 $ pages of coursework and during second day he will write $ 5 $ pages of coursework. This is enough to complete it.

In the fifth example Polycarp cannot write the whole coursework at all, even if he will drink one cup of coffee during each day, so the answer is -1.

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

# 题解

## 作者：LinuF (赞：3)

### 思路分析

刚拿到这道题目，我第一思路是去思考怎么样喝咖啡能最优秀。

我们可以知道对于同一天来说我选择了 $a_{1},a_{2},a_{3},...,a_{k}$ 获得的贡献是 $\sum_{i=1}^{k}a_{i}-\frac{k(k-1)}{2}$。但是！这实则是错的，倘若最小值被减成了 $0$ 那么它是无法再被减下去的。

既然如此我们就确定了思路，尽量把最小值往后放，把最大值往前放。但在此之前我们应当确定在第几天结束。对于第几天结束很显然具有二分的性质，对于最小的满足条件的那一天，它前面那一天不满足这个条件，然而它后面都满足这个条件。

这样我们就知道了这道题的思路，首先二分在第几天结束，然后用上述最优秀的喝咖啡的方式来计算最多能写的作业量是否大于 $m$，就可以得到最终的答案了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int a[N],n,m;
int check(int x){
    int cnt=0,ans=0,times=0;
    while(true){
        for(int i=1;i<=x;i++){
            ans+=max((int)0,a[++cnt]-times);
        }
        times++;
        if(cnt>=n) break;
    }
    return ans>=m;
}
void solve(){
    int l=1,r=n;
    while(l<r){
        int mid=l+r>>1;
        if(check(mid)){
            r=mid;
        }
        else l=mid+1;
    }
    if(!check(l)) cout<<-1<<endl;
    else cout<<l<<endl;
}
int cmp(int a,int b){
    return a>b;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    solve();
}
```




---

## 作者：櫻尘ིོི༹ (赞：1)

**Part 1 思路**

有题目可以推得，每天喝下的第 $n$ 杯咖啡会加速任务 $\max(0,a_i-n+1)$，又因为每天可以喝任意多杯咖啡，所以在   $a_i\leq n-1$ 时，对任务没有任何加速。

所以我们需要尽可能多的让每天喝的咖啡加速更多，同时每一杯咖啡都存在一个损失，但这个损失是由每天喝的顺序而定的。由此，我们可以知道，我们所要做的事情就是让加速越多的咖啡所产生的损失越少。

**Part 2 过程**

首先，将每一杯咖啡的加速排序，从大到小。

接着，二分答案天数。

最后，查看总加速是否超过作业总数。

**Part 3 Code**
 ```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define int long long
using namespace std;
int n,m;
int sum;
int s[MAXN];
int cmp(int a,int b){
	return a>b;
}
inline bool check(int x){
	int num=1,num1=0;
	int nsum=sum;
	while(num<=n){
		if(num+x-1<=n){
			if(s[num+x-1]>=num1){
				nsum-=num1*x;
				num+=x;
				num1++;
			}else{
				int i;
				for(i=num;i<=num+x-1;i++){
					if(s[i]>num1)nsum-=num1;
					else break;
				}
				for(;i<=n;i++)nsum-=s[i];
				break;
			}
		}else{
			if(s[n]>=num1){
				nsum-=(n-num+1)*num1;
				num=n;
			}else{
				int i;
				for(i=num;i<=n;i++){
					if(s[i]>num1)nsum-=num1;
					else break;
				}
				for(;i<=n;i++)nsum-=s[i];
			}
			break;
		}
	}
	if(nsum>=m)return true;
	return false;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		sum+=s[i];
	}
	sort(s+1,s+n+1,cmp);
	if(sum<m){
		puts("-1");
		return 0;
	}
	int l=1,r=n,ans=0;;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```





---

## 作者：Merge_all (赞：0)

### 思路：
- 由于答案具有单调性，所以考虑用二分答案。
- 所以我们可以将数组进行降序排列，**先判断从大到小喝能否完成**，若不能就输出 -1。
- 对于每个 $mid$，**我们尽量先喝效果大的**，这样可以让效果得到最大化。如果发现能量大于等于了 $sum$ 则让右边界 $R=mid$，否则让左边界 $L=mid$。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

const int N=2*10e5+100;

int n,m,a[N];
int L,R,mid,sum;
bool check(){
	sum=0;
//	cout<<"------------------\nmid="<<mid<<"\n";
	for(int i=1;i<=n;i++){
//		cout<<a[i]<<" "<<i/mid-1<<"=======\n";
		sum+=max(0ll*1.0,a[i]-ceil(1.0*i/mid)+1);
//		cout<<"i="<<i<<"   "<<"sum="<<sum<<"\n";
		if(sum>=m){
			return true;
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum<m){
		cout<<"-1\n";
		return 0;
	}
	sort(a+1,a+n+1,greater<int>());
	L=1,R=n;
	while(L<R){
		mid=(L+R)/2;
		if(check()){
			R=mid;
		}
		else{
			L=mid+1;
		}
	}
	cout<<R;
	return 0;
}

```

---

## 作者：yaaaaaan (赞：0)

### 思路

首先观察这道题，答案明显具有二分的特性，所以我们可以用二分来做。

首先给数组从大到小排序，先判 -1 的情况，当每天喝一杯咖啡都肝不完作业，就永远写不完。

然后二分答案，每次对于一个天数 $x$，安排最小值在后，最大值在前，尽量消耗最小值，计算总共的能量，如果能量大于等于 $m$，保存答案，继续寻找有没有更小的答案，否则就往后面寻找更大的答案。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m,sum,ans;
int a[200001];
bool cmp(int x,int y)
{
	return x>y;
}
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=max(a[i]-1LL*ceil(1.0*i/x)+1,1.0*0);
	}
	return cnt>=m;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+n+1,cmp);
	if(sum<m) cout<<-1<<"\n";
	else
	{
		int l=1,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid)) 
			{
				r=mid-1;
				ans=mid;
			}
			else 
			{
				l=mid+1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# CF1118D2 Coffee and Coursework 题解

注：本篇题解对于 [CF1118D1](https://www.luogu.com.cn/problem/CF1118D1) 同样适用。

[洛谷传送门](https://www.luogu.com.cn/problem/CF1118D2)

[CF 传送门](https://codeforces.com/problemset/problem/1118/D2)

[博客，更好的阅读体验](https://www.luogu.com.cn/blog/827018/cf1118d2-ti-xie)

## 思路

既然本题是 D1 的数据加强版，我们不妨先想想 D1 怎么做。

天数最少，那不就是每天喝的最多吗？

贪心思路就明显了，把 $a$ 按降序排序，枚举所有天数，如果可以，就记录答案。

## $O(n^2)$ 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define Debug(a) cout<<a<<endl
using namespace std;
const int N=2e5+10,INF=INT_MAX;
int n,m,a[N];
bool cmp(int x,int y)
{
	return x>y;
}
bool check(int k)
{
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=max(0,a[i]-(i-1)/k);
		if(sum>=m) return 1;
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(check(i))
		{
			cout<<i;
			return 0;
		}
	cout<<-1;
	return 0;
}
```

由于思路代码过于简单，这里就不做解释了。

## AC 代码

我们发现，对于 $1\sim n$ 而言，$check$ 函数的返回值具有**单调性**。

易而想到二分。

于是时间复杂度就降到了对数级别，可以轻松跑过此题。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define Debug(a) cout<<a<<endl
using namespace std;
const int N=2e5+10,INF=INT_MAX;
int n,m,a[N];
bool cmp(int x,int y)
{
	return x>y;
}
bool check(int k)
{
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=max(0,a[i]-(i-1)/k);
		//计算所增加的咖啡值 
		if(sum>=m) return 1;
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,cmp);
	//贪心 
	int l=1,r=n,mid,ans=INF;
	//二分的一些变量 
	while(l<=r)
	{
		mid=l+(r-l)/2;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	//二分过程 
	if(ans==INF) cout<<-1;
	else cout<<ans;
	//输出答案 
	return 0;
}
```

---

## 作者：Helium_Ship (赞：0)

有个很显然的贪心，对于大的 $a_i$ 我们需要优先喝，因为当小的 $a_i$ 减至 $\le0$ 时，就不会使答案更劣，而我们这个贪心跟最终的答案有关，所以我们可以考虑直接二分答案，再使用贪心 $O(n)$ 判是否可行，总时间复杂度为 $O(n\log(n))$。

提示：二分里写的 $l<r$ 最后还需判那个长度为 $1$ 的区间。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010];
bool ansflag;
inline bool check(int x){
	int ans=0,cnt=0,tmp=1;
	bool flag=1;
	while (ans<m&&flag){
		for (int i=1;i<=x;i++){
			ans+=a[tmp]-cnt,tmp++;
			if (a[tmp]-cnt<=0||tmp>n){
				flag=0;
				break;
			}
		}
		cnt++;
	}
	return ans>=m;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ansflag=1;
	cin>>n>>m;
	for (int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,greater<int>());
	int l=1,r=n;
	while (l<r){
		int mid=(l+r)/2;
		if (check(mid)){
			ansflag=0;
			r=mid;
		}
		else l=mid+1;
	}
	if (ansflag&&!check(r))cout<<"-1";
	else cout<<r;
	return 0;
}
```

---

## 作者：EDqwq (赞：0)

这道题的范围告诉我们，不能使用弱化版的 $O(n^2)$ 做法。

如何优化呢？我们朴素的 $O(n^2)$ 做法是枚举天数，而一个显然的优化，我们可以把枚举天数改成二分天数，这样就可以得到一个 $O(nlogn)$ 的做法。

具体就是，对于一个 $mid$ ，用 $O(n)$ 判断是否可行，如果可行更新答案缩小 $r$ ，不可行就改大 $l$ 。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m;
int a[1000010];
int all;
int l,r,mid;
int ans = 2147483647;

bool cmp(int x,int y){
	return x > y;
}

bool check(int x){
	int le = 0;
	int now = 0;
	int num = 0;
	for(int j = 1;j <= n;j ++){
		num ++;
		now += max(a[j] - le,0ll);
		if(num >= x)num = 0,le ++;
	}
	if(now >= m)return true;
	return false;
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++)a[i] = read(),all += a[i];
	sort(a + 1,a + n + 1,cmp);
	l = 1,r = n;
	while(l <= r){
		mid = (l + r) / 2;
		if(check(mid))r = mid - 1,ans = mid;
		else l = mid + 1;
	}
	if(ans == 2147483647)puts("-1");
	else cout<<ans;
	return 0;
}
```

---

## 作者：oneman233 (赞：0)

你有n杯咖啡，每天可以喝任意多杯咖啡，每杯咖啡有一个贡献，但是喝的咖啡过多会有损益

喝第一杯咖啡损益为0，第二杯为1，第三杯以此类推

进入下一天时损益清零

你需要找到最少多少天可以使贡献大于等于一个给定的值

首先把贡献从大到小排序

**考虑二分天数，在check答案时应该这样考虑，比如你有三天时间去完成任务，那么就让最大的三杯咖啡损益都为0，之后三杯咖啡损益为1，以此类推**

这样一定能找到当前天数下最多能达到多少贡献

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define sc(a) scanf("%lld",&a)
#define scc(a,b) scanf("%lld %lld",&a,&b)
#define sccc(a,b,c) scanf("%lld %lld %lld",&a,&b,&c)
#define scs(a) scanf("%s",a) 
#define schar(a) scanf("%c",&a)
#define pr(a) printf("%lld",a)
#define fo(i,a,b) for(int i=a;i<b;++i)
#define re(i,a,b) for(int i=a;i<=b;++i)
#define rfo(i,a,b) for(int i=a;i>b;--i)
#define rre(i,a,b) for(int i=a;i>=b;--i)
#define prn() printf("\n")
#define prs() printf(" ")
#define mkp make_pair
#define pii pair<int,int>
#define pub(a) push_back(a)
#define pob() pop_back()
#define puf(a) push_front(a)
#define pof() pop_front()
#define fst first
#define snd second
#define frt front()
#define bak back()
#define mem0(a) memset(a,0,sizeof(a))
#define memmx(a) memset(a,0x3f3f,sizeof(a))
#define memmn(a) memset(a,-0x3f3f,sizeof(a))
#define debug
#define db double
#define yyes cout<<"YES"<<endl;
#define nno cout<<"NO"<<endl;
using namespace std;
typedef vector<int> vei;
typedef vector<pii> vep;
typedef map<int,int> mpii;
typedef map<char,int> mpci;
typedef map<string,int> mpsi;
typedef deque<int> deqi;
typedef deque<char> deqc;
typedef priority_queue<int> mxpq;
typedef priority_queue<int,vector<int>,greater<int> > mnpq;
typedef priority_queue<pii> mxpqii;
typedef priority_queue<pii,vector<pii>,greater<pii> > mnpqii;
const int maxn=500005;
const int inf=0x3f3f3f3f3f3f3f3f;
const int MOD=100000007;
const db eps=1e-10;
int qpow(int a,int b){int tmp=a%MOD,ans=1;while(b){if(b&1){ans*=tmp,ans%=MOD;}tmp*=tmp,tmp%=MOD,b>>=1;}return ans;}
int lowbit(int x){return x&-x;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int mmax(int a,int b,int c){return max(a,max(b,c));}
int mmin(int a,int b,int c){return min(a,min(b,c));}
void mod(int &a){a+=MOD;a%=MOD;}
bool chk(int now);
int half(int l,int r){while(l<=r){int m=(l+r)/2;if(chk(m))r=m-1;else l=m+1;}return l;}
int ll(int p){return p<<1;}
int rr(int p){return p<<1|1;}
int mm(int l,int r){return (l+r)/2;}
int lg(int x){if(x==0) return 1;return (int)log2(x)+1;}
bool smleql(db a,db b){if(a<b||fabs(a-b)<=eps)return true;return false;}
bool bigeql(db a,db b){if(a>b||fabs(a-b)<=eps)return true;return false;}
bool eql(db a,db b){if(fabs(a-b)<eps) return 1;return 0;}
db len(db a,db b,db c,db d){return sqrt((a-c)*(a-c)+(b-d)*(b-d));}
bool isp(int x){if(x==1)return false;if(x==2)return true;for(int i=2;i*i<=x;++i)if(x%i==0)return false;return true;}
inline int read(){
    char ch=getchar();int s=0,w=1;
    while(ch<48||ch>57){if(ch=='-')w=-1;ch=getchar();}
    while(ch>=48&&ch<=57){s=(s<<1)+(s<<3)+ch-48;ch=getchar();}
    return s*w;
}
inline void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
}
int gcd(int a, int b){
    if(a==0) return b;
    if(b==0) return a;
    if(!(a&1)&&!(b&1)) return gcd(a>>1,b>>1)<<1;
    else if(!(b&1)) return gcd(a,b>>1);
    else if(!(a&1)) return gcd(a>>1,b);
    else return gcd(abs(a-b),min(a,b));
}
int lcm(int x,int y){return x*y/gcd(x,y);}

int n,m,a[maxn];
int sum[maxn],del[maxn];

bool chk(int now){
    re(i,1,now) del[i]=0;
    int cnt=0;
    re(i,1,n){
        cnt+=a[i]-(i-1)/now;
        if(cnt>=m) return 1;
    }
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;re(i,1,n) cin>>a[i],sum[i]=sum[i-1]+a[i];
    if(sum[n]<m){
        cout<<-1;
        return 0;
    }
    else if(sum[n]==m){
        cout<<n;
        return 0;
    }
    sort(a+1,a+1+n,greater<int>());
    cout<<half(1,n);
    return 0;
}
```


---

## 作者：信息学carryHarry (赞：0)


### 策略1：
$O(n^2)$ 暴力枚举天数，显然超时。
### 策略2：
先从大到小将权值排序，再二分完成任务的天数（当前 $mid$ 是否能完成 $m$ 个任务），最后若没有可行的 $mid$，就输出 $-1$，时间复杂度 $O(n \log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=2e5+5;
int n,a[M],k,ans=1e9,m;
bool check(int x)//二分天数
{
	int i=0,j=0,k=0;
	for(int s=1;s<=n;s++){
		k++;
		j+=max(a[s]-i,(long long)0);
		if(k>=x){
			i++;
			k=0;
			
		}
	}
	return j>=m;
}

bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		k+=a[i];
	}
	sort(a+1,a+1+n,cmp);
	int lt=1,rt=n;
	while(lt<=rt){
		int mid=(lt+rt)/2;
		if(check(mid)){
			rt=mid-1;
			ans=mid;
		}
		else
			lt=mid+1;
	}
	if(ans==1e9)//是否有解
		cout<<-1;
	else
		cout<<ans;
	return 0;
}

```


---

## 作者：wwldx (赞：0)

思路：一天可以喝无限杯咖啡（话说不会喝死吗？？？），每天喝的第n瓶，会加速max（0， a[i]-n+1），所以当n-1大于等于a[i]的时候，你等于白喝了，所以你完全可以二分枚举多少天喝完，假如n天喝完，设asd=0，先把a按由高到低排序，先取最大的n瓶，每瓶-asd，也就是-0,然后再取第二大的n瓶，同时asd+1，他们要各自-asd，也就是-1，循环此项操作，直到咖啡的价值小于等于asd或者饮料被取完了，比较总价值能否大于等于作业数量即可
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200050
long long a[maxn];
long long sum;
long long n,m;
long long cmp(int a,int b)
{
	return a>b;
}
bool check(long long x)
{
	//前x项 a[i]-0 x+1到2x项 a[i]-1 2x+1项到3x项 a[i]-2
	//nx+1到(n+1)x项 a[i]-n 
	long long num=1,asd=0;//num用于a[i]的计数，asd用于每次减少的个数
	long long qwe=sum;//qwe初始值等于sum
	while(num<=n)
	{
		if(num+x-1<=n)//即使一次拿x瓶，咖啡数量仍然够
		{
			if(a[num+x-1]>=asd)//这一组里咖啡的最小价值仍大于等于asd，也就是喝咖啡是有用的
			{
				qwe-=asd*x;
				num+=x;
				asd++;
			}
			else//最小的咖啡已经失效了
			{
				int i;
				for(i=num;i<=num+x-1;i++)
				{
					if(a[i]>asd)//咖啡还没失效
					qwe-=asd;
					else//找到了失效的第一瓶咖啡
					break;
				}
				for(;i<=n;i++)//因为从i开始的咖啡已经失效，后面的咖啡只会越来越小，没有意义，直接减去
				qwe-=a[i];
				break;
			}
		}
		else//剩下的数量不够一次拿x瓶了
		{
			if(a[n]>=asd)//大概意思与上面相同，只不过a[num+x-1]直接可以确定是a[n]了
			{
				qwe-=(n-num+1)*asd;
				num=n;
				break;
			}
			else
			{
				int i;
				for(i=num;i<=n;i++)
				{
					if(a[i]>asd)
					qwe-=asd;
					else
					break;
				}
				for(;i<=n;i++)
				qwe-=a[i];
				break;
			}
		}
	}
	return qwe>=m;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+1+n,cmp);//从大到小排序
	if(sum<m)//如果sum<m，即使每天只喝一杯，那也不够
	{
		cout<<"-1\n";
		return 0;
	}
	int l=0,r=n;
	while(r-l>1)//二分查找
	{
		int mid=(l+r)/2;
		if(check(mid))
		r=mid;
		else
		l=mid;
	}
	cout<<r<<"\n";
	return 0;
}
```


---

