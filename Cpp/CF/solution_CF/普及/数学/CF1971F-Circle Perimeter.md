# Circle Perimeter

## 题目描述

Given an integer $ r $ , find the number of lattice points that have a Euclidean distance from $ (0, 0) $ greater than or equal to $ r $ but strictly less than $ r+1 $ .

A lattice point is a point with integer coordinates. The Euclidean distance from $ (0, 0) $ to the point $ (x,y) $ is $ \sqrt{x^2 + y^2} $ .

## 说明/提示

The points for the first three test cases are shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971F/aff456cddb623f0decb8386de3943888d72800f7.png)

## 样例 #1

### 输入

```
6
1
2
3
4
5
1984```

### 输出

```
8
16
20
24
40
12504```

# 题解

## 作者：_QyGyQ_ (赞：6)

乍一看，这道题设计平面直角坐标系，没学过，不会。再一看，不就是数正方形吗，简单。只需要用两个变量来记录正方形一条边的左右端点，求出长度，乘以四，就是正方形的周长。所有正方形周长的总和就是答案。
```cpp
#include<bits/stdc++.h>
#define int long long
#define lc(p) (p<<1)
#define rc(p) (p<<1|1)
#define lowbit(x) (x&-x)
#define debug puts("-----------")
#define endl puts("")
#define re register
#define in inline
#define mod 998244353
using namespace std;
const int N=1e6+7;

char *p1,*p2,buf[N];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
in int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57) x=(x<<3)+(x<<1)+ch-48,ch=nc();
   	return x*f;
}

int ans;
signed main(){
	int t=read();
	while(t--){
		int r=read();
		ans=0;
		int st=0,ed=0;
		for(re int i=r;i>=1;i--){
			while(i*i+st*st<r*r) st++;
			while(i*i+ed*ed<(r+1)*(r+1)) ed++;
			ans+=(ed-st);//注意不是 ed-st+1。因为是求周长点的个数。 
		}
		printf("%lld\n",ans<<2);
	}
	return 0;
}
```

---

## 作者：tder (赞：4)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

给定 $r$，求满足 $r\le\sqrt{x^2+y^2}<r+1$ 的整点对 $(x,y)$ 的数量。多测。

**【思路】**

考虑坐标系除原点外可以被分成四个部分，而 $r\ge1$ 故原点对答案无贡献，因此仅计算第一象限部分的答案，再乘上 $4$ 即为最终答案。

不妨枚举 $0\le x\le r$，令 $y_{\max}$ 表示满足条件的最大 $y$ 值，而 $y_{\min}$ 同理，则其对答案的贡献为 $y_{\max}-y_{\min}+1$。于是答案为：

$$
\begin{aligned}
\text{ans}&=4\cdot\sum_{x=0}^{r}(y_{\max}-y_{\min}+1)
\end{aligned}
$$

接下来只需考虑如何求出对应的 $y$ 的最值即可。

由 $r\le\sqrt{x^2+y^2}<r+1$ 可得：

$$
\begin{aligned}
  &r\le\sqrt{x^2+y^2}<r+1 \\
  \Rightarrow~&r^2\le x^2+y^2<(r+1)^2 \\
  \Rightarrow~&r^2-x^2\le y^2<(r+1)^2-x^2 \\
  \Rightarrow~&\sqrt{r^2-x^2}\le y<\sqrt{(r+1)^2-x^2}
\end{aligned}
$$

因此，$y_{\max}=\left\lfloor\sqrt{(r+1)^2-x^2-\text{eps}}\right\rfloor$ 且 $y_{\min}=\left\lceil\sqrt{r^2-x^2}\right\rceil$。

单组数据时间复杂度 $O(r)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5; const double EPS = 0.5;
int r, ans;
int f(int n) {
	return n * n;
}
void solve() {
	cin>>r;
	ans = 0;
	for(int i = 1; i <= r; i++) {
		int mx = floor(sqrt(f(r + 1) - f(i) - EPS));
		int mn = ceil(sqrt(f(r) - f(i)));
		// cout<<i<<" ["<<mn<<", "<<mx<<"]"<<endl;
		ans += mx - mn + 1;
	}
	cout<<ans * 4<<endl;
}
int t;
void file(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
#define file(x) file(#x)
signed main() {
	// file(cf);
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意
给定一个 $r$，求格点的数量，要求格点到原点的欧几里得距离大于等于 $r$，并且小于 $r+1$。

## 解题思路
### 暴力
可以枚举半径为 $r$ 的圆内的格点，时间复杂度为 $O(r^2)$。

### 优化一点的暴力
我们发现，不等式中有一个根号，所以可以把不等式优化，变成 $\sqrt{r^2-x^2}\le y<\sqrt{(r+1)^2-x^2}$。四个象限中的格点是对称的，所以只需枚举一个象限即可。

还有，当 $x=r$ 时，$y$ 只有可能是 $0$（为了满足不等式）；当 $x=r-1$ 时，我们只需把这个 $x$ 值代入到不等式中，求出 $y$ 的整数解数量，用累加器累加，这样只需枚举 $x$，$y$ 的数量就都确定了。

需要注意的是，确定数量需要用不等式中较大值减较小值，又因为根号会自动向下取整，会漏掉一些数字，所以应向上取整。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

long long t,r,ans;

int main()
{
	scanf("%lld",&t);
	
	while(t--)
	{
		scanf("%lld",&r); ans=0;
		for(long long i=1; i<=r; ++i)
		ans+=ceil(sqrt((r+1)*(r+1)-i*i))-sqrt(r*r-i*i);
		printf("%lld\n",ans*4);
	}

	return 0;
}

```

---

## 作者：GJX_Algorithm (赞：0)

# CF1971F 题解
## 题目描述
- 给定整数 $r$，求出与 $(0,0)$ 的欧几里得距离大于等于 $r$ 小于 $r+1$ 的格点的数量。
- 格点：具有整数坐标的点；从点 $(0,0)$ 到点 $(x,y)$ 的欧几里得距离： $\sqrt{x^2+y^2}$。

## 解题思路
- 观察图形，发现其是类似圆的形状，圆是具有对称性的，故我们只需要如图这样分割图形（每部分包括一个象限+$x$ 轴的半轴或 $y$ 轴的半轴），即可通过一个部分的答案得到整体答案。
  ![](https://cdn.luogu.com.cn/upload/image_hosting/n908wtvi.png)
  
- 将原不等式等价转换：$r \le \sqrt{x^2 + y^2} < r + 1 \iff r^2 \le x^2 + y^2 < (r + 1)^2$，用于确定范围时避免精度问题。

- 观察上述不等式，若 $x$ 不断增加，为确保不等式成立，$y$ 会不断下降，所有满足条件的 $y$ 会构成非严格递减序列。由此，可以减少枚举次数。

- 接下来就可以愉快的枚举啦！

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, r;
int solve(int r)
{
	int ans = 0, y = r;
	for (int x = 0; x <= r; x++)
	{
		while (x * x + y * y >= r * r + 2 * r + 1)
			y--;
		int top = y;
		while (x * x + top * top >= r * r && top > 0) 
			top--;
		ans += y - top;
	}
	return ans * 4;
}
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> r;
		cout << solve(r) << "\n";
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

VP 赛时被诈骗了，来点不一样的解法。

我们注意到答案实际上是半径为 $ r+1 $ 的圆和半径为 $ r $ 的圆中间那个部分，然后发现半径为 $ r $ 内的圆内整点数量可以简单计算，枚举 $ x $，则显然有整点数量为 $ 1+\sum\limits_{x=0}^r \lfloor \sqrt{r \times r-x \times x} \rfloor $，这个可以朴素枚举计算。

现在发现我们多计算了半径为 $ r+1 $ 的圆上的整点，且把半径为 $ r $ 的圆上的整点多扣除了。

于是问题转化为计算一个半径为 $ r $ 的圆上有多少整点。然后就变成了 [这道题](https://www.luogu.com.cn/problem/P2508) 的弱化版本。

设半径为 $ r $ 的圆内整点数为 $ f(r) $，圆上整点数为 $ g(r) $，则最后答案即为 $ f(r+1)-f(r)-g(r+1)+g(r) $。

时间复杂度 $ \mathcal{O}(\sum r) $，来自 $ f(r) $ 的枚举，可以通过。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020];
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int vis[200020];
int f(int n)
{
int a=0;
for(int i=0;i<=n;i++)
a+=sqrt(n*n-i*i);
return 4*a+1;
}
int r,ans;
inline void work(int d)
{
    int t,s,k=r/d;
    for(s=1;s*s<=k;++s)
    {
        t=sqrt(k-s*s);
        if(__gcd(t,s)==1&&s*s+t*t==k)
        {
            int x=(s*s-t*t)/2*d,y=d*s*t;
            if(x>0&&y>0&&x*x+y*y==(r/2)*(r/2))
            ans+=2;
        }
    }
}
int final(int qwq)
{
    r=qwq;
    ans=0;
    r<<=1;
    for(int i=1;i*i<=r;++i)
    if(!(r%i))
    {
        work(i);
        if(i*i!=r)
        work(r/i);
    }
    return 1+ans<<2;
}
signed main()
{
int T;
cin>>T;
while(T--)
{
    int R;
    cin>>R;
    cout<<f(R+1)-f(R)-final(R+1)+final(R)<<endl;
}
}
```

---

## 作者：coderJerry (赞：0)

根据题目条件，列出不等式：$r\le \sqrt{x^2+y^2} < r+1$。

考虑从 $r$ 到 $-r$ 枚举 $y$ 的值，解得 $\sqrt{r^2-y^2} \le x < \sqrt{(r+1)^2-y^2},-\sqrt{r^2-y^2} < x \le \sqrt{(r+1)^2-y^2}$，统计有多少个整数 $x$ 满足即可。

结果就是 $(\lfloor \sqrt{(r+1)^2 -y^2} \rfloor - \lceil \sqrt{r^2-y^2} \rceil +1)\times 2$。

乘以 $2$ 是因为 $y$ 轴左右各有一半的点满足，最终结果还要减 $2$，因为在 $y$ 轴上 $(0,n)$ 和 $(0,-n)$ 被统计了两次。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        int res=0;
        for(int y=n;y>=-n;y--){
            int l=(int)(ceil(sqrt(n*n-y*y)));
            int r=(int)(sqrt((n+1)*(n+1)-y*y));
            if((n+1)*(n+1)-y*y==r*r) r--;
            res+=2*(r-l+1);
        }
        cout<<res-2<<"\n";
    }
    return 0;
}
```

---

## 作者：swww77 (赞：0)

提供一个二分思路，在第一象限内，对于每个横坐标 $x$，都去枚举满足条件的 $y$，最后把答案乘以四求出整个圆即可，很好想。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int>
#define endl '\n'
const int N=1e6+10;
const int N1=1e3+10;
const int mod=1e9+7;
const int element=3;
int a[N],n;
bool check(int k,int i){
    return k*k+i*i<n*n;
}
bool check1(int k,int i){
    return k*k+i*i<(n+1)*(n+1);
}
void solve(){
    cin>>n;
    int ans1=0;
    for(int i=1;i<=n;i++){
        int l=-1,r=2e5+1;
        int ans=0;
        while(l+1<r){
            int mid=l+r>>1;
            if(check(mid,i)) l=mid;
            else r=mid;
        }
        ans=l;
        l=-1,r=2e5+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(check1(mid,i)) l=mid;
            else r=mid;
        }
        ans=l-ans;
        ans1+=ans;
    }
    ans1*=4;
    cout<<ans1<<endl;
}   
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
其实很简单，评个橙没问题。题意是给定半径 $r$，要求求出有几个点满足到原点的欧几里得距离小于 $r + 1$ 且大于或等于 $r$。

考虑暴力枚举，时间复杂度为 $O(T\times r^2)$，数据范围一看，$r \le 10^5$，$T \le 10^2$，超一亿了，会炸。**这时我们考虑简化公式**，题目中给出了欧几里得距离计算公式是：
$$\sqrt{x^2+y^2}$$
结合满足条件推出范围：
$$\sqrt{r^2-x^2} \le y < \sqrt{(r+1)^2-x^2}$$
由于题目中图片一说明了四个区域的点为对称的，所以我们可以做出一个时间复杂度为 $O(T\times r)$ 的程序，~~刚好卡一亿~~，不过注意要向上取整，还有答案有四个区域，最后要乘四。
## 代码
码风太烂了，各位见笑了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n;
int main(){
	cin>>T;
while(T--){cin>>n;
ll ans=0;
for(ll i=1;i<=n;i++) ans+=ceil(sqrt(pow((n+1),2)-pow(i,2)))-sqrt(pow(n,2)-pow(i,2));
cout<<ans*4<<endl;
	}
	return 0;
}
```

---

## 作者：ReturnXI (赞：0)

题目要求计算给定半径的圆周上满足条件的格点数量。我们可以使用一种思路，首先只计算一个象限有多少点满足条件。具体步骤如下：

1. 遍历圆周上的每个点，横坐标从 $0$ 到 $r$。
2. 对于每个横坐标，计算出纵坐标的范围。
3. 检查在这个范围内哪些点满足条件。
4. 将满足条件的点数量乘以 $4$，坐标轴上每一个到原点距离为 $r$ 的点都被计算了两次，减去后就是最终结果。
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e5+10;
ll t,r;

long long count()
{
    long long ans=0;
    for(long long i=0;i<=r;i++)
    {
        long long height=sqrt(r*r-i*i);
        while(1)
        {
            if(i*i+height*height<(r+1)*(r+1))
            {
//                cout<<i<<" "<<height<<endl;
                height++;
                if(i*i+(height-1)*(height-1)>=r*r)
                    ans++;
            }
            else
            {
                break;
            }
        }
    }
    ans*=4;
    ans-=4;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>r;
        cout<<count()<<endl;
    }
    return 0;
}
```

---

## 作者：huanglihuan (赞：0)

## [原题链接](https://codeforces.com/contest/1971/problem/F)
### 题目大意和目的
在一个平面直角坐标系当中，以 $(0,0)$ 作为起点，在这个坐标上，统计所有满足表达式 $r \le \sqrt {x ^ 2 + y ^ 2} < r + 1$ 的结点数量。
### 题目分析和思路
这里给定两种方法：
- 使用深搜暴力枚举。

结论：代码较难，容易卡时间（我卡了[999ms](https://www.luogu.com.cn/record/159008798)）

- 枚举所有的 $y$，找到相应的 $x_1,x_2$

公式：

$$
x _ 1 ^ 2 + y ^ 2 = r ^ 2
$$

$$
x _ 2 ^ 2 + y ^ 2 = (r + 1) ^ 2
$$

结论：代码简单，运行时间短

总结：使用第二种方法更优
### Code：
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define ll long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 1e5 + 5;

void solve(){
	int x;
	cin >> x;
	int ans = 0;
	int l = x * x,r = (x + 1) * (x + 1);
	for (int i = 1; i <= x; i ++)
	{
		int lc = l - i * i, rc = r - i * i - 1;
		int lx = sqrt (lc), rx =  sqrt(rc);
		if (lx * lx < lc) lx ++;
		ans += (rx - lx + 1) * 4;
	}
	cout << ans << endl;
}
signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0),cout.tie (0);
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
/*
#include <bits/stdc++.h>
#include <cstdio>
//#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 1e5 + 5;

int a [N];

int dir [8] [2] = {1,0,0,1,-1,0,0,-1,1,1,-1,1,-1,-1,1,-1};
int ans;
int r;
map <pair <int,int>,bool> mp;
bool check (int x,int y)
{
	return ! mp [{x,y}] && int (sqrt (pow (x,2) + pow (y,2))) == r;
}
void dfs (int x,int y)
{
	ans ++;
	mp [{x,y}] = true;
	for(int i = 0;i < 8;i ++)
	{
		int next_x = dir [i][0] + x;
		int next_y = dir [i][1] + y;
		if(check (next_x,next_y)) dfs (next_x,next_y);
	}
}

void solve()
{
	cin >> r;
	mp.clear();
	ans = 0;
	if(! mp [{0,r}]) dfs (0,r);
	if(! mp [{r,0}]) dfs (r,0);
	if(! mp [{0,-r}]) dfs (0,-r);
	if(! mp [{-r,0}]) dfs (-r,0);
	cout << ans << endl;
}
signed main()
{
	int T;
	cin >> T;
	while(T --) solve();
	return 0;
}
*/
```

---

