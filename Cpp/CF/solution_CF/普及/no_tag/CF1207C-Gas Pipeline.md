# Gas Pipeline

## 题目描述

You are responsible for installing a gas pipeline along a road. Let's consider the road (for simplicity) as a segment $ [0, n] $ on $ OX $ axis. The road can have several crossroads, but for simplicity, we'll denote each crossroad as an interval $ (x, x + 1) $ with integer $ x $ . So we can represent the road as a binary string consisting of $ n $ characters, where character 0 means that current interval doesn't contain a crossroad, and 1 means that there is a crossroad.

Usually, we can install the pipeline along the road on height of $ 1 $ unit with supporting pillars in each integer point (so, if we are responsible for $ [0, n] $ road, we must install $ n + 1 $ pillars). But on crossroads we should lift the pipeline up to the height $ 2 $ , so the pipeline won't obstruct the way for cars.

We can do so inserting several zig-zag-like lines. Each zig-zag can be represented as a segment $ [x, x + 1] $ with integer $ x $ consisting of three parts: $ 0.5 $ units of horizontal pipe + $ 1 $ unit of vertical pipe + $ 0.5 $ of horizontal. Note that if pipeline is currently on height $ 2 $ , the pillars that support it should also have length equal to $ 2 $ units.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/f1dfe38b83de03ccc78e9e23fedbdc3223f970d0.png)Each unit of gas pipeline costs us $ a $ bourles, and each unit of pillar — $ b $ bourles. So, it's not always optimal to make the whole pipeline on the height $ 2 $ . Find the shape of the pipeline with minimum possible cost and calculate that cost.

Note that you must start and finish the pipeline on height $ 1 $ and, also, it's guaranteed that the first and last characters of the input string are equal to 0.

## 说明/提示

The optimal pipeline for the first query is shown at the picture above.

The optimal pipeline for the second query is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/2782d7e4c7012251045217f9f050b1e333f47c33.png)The optimal (and the only possible) pipeline for the third query is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/7e72ed8fa647ff66b04ca0425394c874c1b110fe.png)The optimal pipeline for the fourth query is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/248de9c02a0298296e2131b26213178e9c6ad6ba.png)

## 样例 #1

### 输入

```
4
8 2 5
00110010
8 1 1
00110010
9 100000000 100000000
010101010
2 5 1
00
```

### 输出

```
94
25
2900000000
13
```

# 题解

## 作者：兮水XiShui丶 (赞：10)

个人感觉挺水的一道DP吧qwq....

题目里要求铺设柱子和管子的总花费最小.  

我们显然可以发现,当有交叉路口的时候,我们必须让这里的高度为2(废话)  

但是在没有交叉路口的时候,我们可以让它的高度为2,也可以让它的高度为1.  

所以dp方程就很显然了:我们设$f[i][j]$表示铺设到了前i的区域,当前铺设的高度为$1/2$时的最小花费.  

那么转移方程就是$f[i+1][0] = min(f[i][0],f[i][1] + a) + a + b;f[i+1][1] = min(f[i][0] + a , f[i][1]) + a + 2*b;(s[i]=='0')$  

和$f[i+1][1] = f[i][1] + a + 2*b;f[i+1][0] = oo;(s[i]=='1')$  


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int oo=(1ll<<62); 
const int N=2e5+10;
int n,a,b;
string s;
int f[N][2];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n >> a >> b;
        cin >> s;
        f[0][0] = b;
        f[0][1] = oo;
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                f[i+1][0] = min(f[i][0],f[i][1] + a) + a + b;
                f[i+1][1] = min(f[i][0] + a , f[i][1]) + a + 2*b;
            }
            else{
                f[i+1][1] = f[i][1] + a + 2*b;
                f[i+1][0] = oo;
            }
        }
        cout << f[n][0] << endl;
    }
    return 0;
}
```

---

## 作者：引领天下 (赞：8)

这个题就是裸的dp，然而我还是莫名其妙手残打错了一次。

思路：对于每个位置，我们令$f[i][0]$为到达$i$时高度为$1$的最小答案，$f[i][1]$为到达$i$时高度为$2$的最小答案，分情况讨论之后dp：

- 是路口
  - 那么$i$位置高度不能为$0$，反映在dp上就是$f[i][0]=inf$
  - 我们对$f[i][1]$取$min$：看是从上一个位置下来再上来便宜，还是直接拉过来便宜。
  
- 不是路口
  - 那么$f[i][0]$就是对从上一个位置下来和直接平的过来取$min$
  - $f[i][1]$同是路口的情况，也是分上来和直接平行过来取$min$。
  
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string s;
#define ll long long
#define inf 884888488848997
//注意！inf要开大！不然会WA的QAQ
ll a,b,f[200005][2];
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>a>>b>>s;
        memset(f,0,sizeof(f));
        f[0][1]=inf;f[0][0]=a+b;
        for (int i=1;i<s.size();i++){
            k=(s[i]=='1');
            if(k){//是路口
                f[i][0]=inf;
                f[i][1]=min(f[i-1][0]+2*a+2*b,f[i-1][1]+2*b+a);//从f[i-1][0]和f[i-1][1]转移
            }else{
                f[i][0]=min(f[i-1][0]+a+b,f[i-1][1]+2*a+2*b);
                f[i][1]=min(f[i-1][0]+2*a+b,f[i-1][1]+2*b+a);//同上，思路已经说过了
            }
        }
        cout<<f[n-1][0]+b<<endl;//输出答案的时候要注意，最后要求高度降为1，而且1的高度也是需要柱子的
    }
}
```

---

## 作者：a_grain (赞：2)



------------
[题面](https://www.luogu.com.cn/problem/CF1207C)

------------
这道题目的意思是让我们合理分配管道和支柱，然后求出最少的花费，有一些位置有限制。

第 $0$ 和第 $n$ 位只能放 $1$ 个单位支柱，$s[i]==1$ 的位置只能放 $2$ 个单位支柱。

------------

了解题目后，可以发现这题能够用 DP 做，所以只要列出动态转移方程就能 AC 了。

用 $dp[i][j]$ 表示从第 $0$ 位做到第 $i$ 位，且第 $i$ 位放 $j$ 个单位支柱的最小花费。

初始化把所有赋最大，但 $dp[0][1]=b$。

- $dp[i][1]=a+b+min(dp[i-1][1],dp[i-1][2]+a)$
- $dp[i][2]=a+b*2+min(dp[i-1][1]+a,dp[i-1][2])$

做完后判断 $s[i]$ 或 $s[i+1]$ 是否是'$1$'，是的话 $dp[i][1]$ 赋一个超大值。

最后输出 $dp[n][1]$。

------------
**AC code**
```cpp
#include<bits/stdc++.h>
#define I(x) ios::sync_with_stdio(x),cin.tie(x),cout.tie(x)
#define int long long
using namespace std;
int T,n,a,b,i,dp[200005][3];
char s[200005];
signed main(){
	I(0);
	cin>>T;
	while(T--){
		cin>>n>>a>>b>>s+1;
		memset(dp,127,sizeof(dp))dp[0][1]=b;//初始化 
		for(i=1;i<=n;i++){
			dp[i][1]=a+b+min(dp[i-1][1],dp[i-1][2]+a);//做j是1的情况
			dp[i][2]=a+b*2+min(dp[i-1][1]+a,dp[i-1][2]);//做j是2的情况
			if(s[i]=='1'||s[i+1]=='1')//判断是否有限制
				dp[i][1]=1e18;
		}
		cout<<dp[n][1]<<endl;
	}
	return 0;
}
```


------------
# The End.

---

## 作者：开始新的记忆 (赞：1)

发现下一堆大佬用DP，我这个菜鸡只会暴力。

主要思路：贪心思路，每次不需要通车时（除了头尾）只需要判断是把高度还是维持在2还是把高度降低的花费哪个少用哪个即可。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
 
int main()
{	cin>>t;
	while(t--)
	{
		long long n,a,b,ans=0,num=0,flag=0,fl=0;
		string s;
		cin>>n>>a>>b>>s;
		ans=(n+1)*b+2*a;
		for(int i=0;i<n;++i)
		{
			if(s[i]=='1')
				ans=ans+a+b,flag=1,fl=1;
			else
			{
				if(s[i-1]=='1')
					ans+=b,num=0;
				if(i<n && s[i+1]=='1' && flag)
					ans+=min(2*a,num*b)+a,num=0;
				else
					ans+=a,num++;
			}
		}
		if(fl==0)
			ans-=(2*a);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：fmj_123 (赞：1)

本题算是一道较简单的DP题吧。。。（~~我写了1h~~

设$f[i][j]$表示第$i$根柱子高度为$j$所花费的最小值，那么

$f[i][1]=min(f[i-1][2]+2*a+b,f[i-1][1]+b+a);$
$f[i][2]=min(f[i-1][2]+a+2*b,f[i-1][1]+2*a+2*b);$

显然，第$i$根柱子高度为1，只能在$st_{i-1}$和$st_i$同时为$0$才能出现。注意特判即可

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[201000][3];
long long t,n,a,b;string st;
int main()
{
	cin>>t;
	for (int tt=1;tt<=t;tt++)
	{
		cin>>n>>a>>b;
		cin>>st;
		st[n]='0';
		for (int i=0;i<=n;i++)
		  f[i][1]=f[i][2]=1e15;
		f[0][1]=b;	
		for (int i=1;i<=n;i++)
		{
			f[i][1]=min(f[i-1][2]+2*a+b,f[i-1][1]+b+a);
			f[i][2]=min(f[i-1][2]+a+2*b,f[i-1][1]+2*a+2*b);
			if (st[i-1]=='1'||st[i]=='1') f[i][1]=1e15;
		}
		cout<<f[n][1]<<endl;
	}
	return 0;
}
```

---

## 作者：Lian_zy (赞：0)

# [**题目传送门**](https://www.luogu.com.cn/problem/CF1207C)
这道题是一道 dp 题。

我们先想状态：  
用 $dp_{i,j}$ 表示已经铺设到 $i$ 的时候，此时的高度为 $j + 1$ 的最小花费。

此时有两种情况

- 第 $i$ 个点通车

这个点高度不能为 $1$，故 $dp_{i,0} = 10^{18}$（只要是极大值就行）。

$dp_{i,1}$ 可以选择前面高度是 $1$，搭一个管道上来或者前面高度是 $2$，直接拉过来，两者取 $\min$。

- 第 $i$ 个点不通车

此时可以选择高度为 $1$ 或 $2$，两者取 $\min$，算式交给大家去思考。

注意最后的高度为 $1$，所以还要 $+b$。
``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2e5 + 10;
char s[maxn];
long long T, n, a, b, dp[maxn][2];
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld %lld %lld %s", &n, &a, &b, s + 1);
		dp[1][0] = a + b;
		dp[1][1] = 1e18;
		for (int i = 2; i <= n; i++) {
			if (s[i] == '1') {
				dp[i][0] = 1e18;
				dp[i][1] = min(dp[i - 1][0] + (a << 1) + (b << 1), dp[i - 1][1] + (b << 1) + a);
			} else {
				dp[i][0] = min(dp[i - 1][0] + a + b, dp[i - 1][1] + (b << 1) + (a << 1));
				dp[i][1] = min(dp[i - 1][0] + (a << 1) + (b << 1), dp[i - 1][1] + (b << 1) + a);
			}
		}
		printf("%lld\n", dp[n][0] + b);
	}
	return 0;
}
```

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1207C)
这道题在不需要通车的地方的高度有 $1$ 和 $2$ 两种状态，所以一眼 dp。

思路：设 $dp_{i,0}$ 为到位置 $i$ 时高度为 $1$ 的最小费用，$dp_{i,1}$ 为到位置 $i$ 时高度为 $2$ 的最小费用。

那么就可以得到状态转移方程。

1.当 $s_i$ 为 $0$ 时
$$\begin{cases}dp_{i+1,0}=\min\left(dp_{i,0},dp_{i,1}+a\right)+a+b\\dp_{i+1,1}=\min\left(dp_{i,0}+a,dp_{i,1}\right)+a+b\times2\end{cases}$$
2.当 $s_i$ 为 $1$ 时
$$\begin{cases}dp_{i+1,1}=dp_{i,1}+a+b\times2\end{cases}$$
AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long//此题需开long long
using namespace std;
int t,dp[200005][2];
string s;
signed main(){
	scanf("%lld",&t);
	while(t--){
		int n,a,b;
		scanf("%lld%lld%lld",&n,&a,&b);
		cin>>s;
		dp[0][0]=b;
		dp[0][1]=1e18;//不可能存在，赋极大值
		for(int i=0;i<n;i++){
			if(s[i]=='0'){
				dp[i+1][0]=min(dp[i][0],dp[i][1]+a)+a+b;
				dp[i+1][1]=min(dp[i][1],dp[i][0]+a)+a+b*2;
			}
			else{
				dp[i+1][1]=dp[i][1]+a+b*2;
				dp[i+1][0]=1e18;//不可能存在，赋极大值
			}
		}
		printf("%lld\n",dp[n][0]);
	}
	return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[题目传送门](https://www.luogu.com.cn/problem/CF1207C)

# 思路

这道题第一眼肯定会想到 dp 。

这题在不需通车的地方可以保持 $2$ 的高度，也可以下降变成 $1$。

那么我们分类讨论一下，发现可以用二维 dp 来实现，第一层表示低，第二层表示高。

设 $dp_{i,0/1}$ 为到这个位置的最小费用，$0$ 表示低，$1$ 表示高。

状态转移方程就是：当他为低的时候，$dp_{i+1,0} = min(dp_{i-1,0}+ a + 2b) $；$dp_{i+1,1} = min(dp_{i-1,0}+ a ,dp_{i,1}) + a + 2b $。

当他为高的时候，$dp_{i+1,0} = 10^{18} $；$dp_{i+1,1} = dp_{i,1} + a + 2b $。

最后输出 $dp_{n,0}$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a,b;
int x[200005],dp[200005][2];
string s;
void solve(){
	int ans=0,cnt=0;
	bool f=0;
	cin>>n>>a>>b>>s;
	for(int i=0;i<n;i++){
		x[i]=(s[i]-'0');
	}
	dp[0][0]=b;
	dp[0][1]=1e18;
	for(int i=0;i<n;i++){
		if(x[i]==0){
			dp[i+1][0]=min(dp[i][0],dp[i][1]+a)+a+b;
			dp[i+1][1]=min(dp[i][0]+a,dp[i][1])+a+2*b;
		}else{
			dp[i+1][1]=dp[i][1]+a+2*b;
			dp[i+1][0]=1e18;
		}
	}
	cout<<dp[n][0]<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/141294083)

---

## 作者：hjfjwl (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1207C)

题目描述：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/f1dfe38b83de03ccc78e9e23fedbdc3223f970d0.png)
这道题一眼动态规划，我们设 $dp_{i,0/1}$ 表示上图中数轴下表为 $i$ 时所用的代价，$0$ 表示低，$1$ 表示高。初始化 $dp_{0,0} = b$。
状态转移方程式如下：
$dp_{i,1} = \min(dp_{i-1,0} + a + 2 \times b + a,dp_{i-1,1} + a + 2 \times b)$

如果 $a_i$ 是 $0$，那么加上 $dp_{i,0} = \min(dp_{i-1,1} + a + 2\times b + a,dp_{i-1,0} + a + b)$

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[200005][4];
char aa[200005];
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		memset(dp,0x3f,sizeof(dp));
		int n,a,b;
		scanf("%lld%lld%lld",&n,&a,&b);
		dp[0][0] = b;
		for(int i = 1;i <= n;i++)
		{
			cin >> aa[i];
		}
		for(int i = 1;i <= n;i++)
		{
			if(aa[i] == '1')
			{
				dp[i][1] = min(dp[i - 1][0] + a + 2 * b + a,dp[i - 1][1] + a + 2 * b);
			}
			else
			{
				dp[i][1] = min(dp[i - 1][0] + a + 2 * b + a,dp[i - 1][1] + a + 2 * b);
				dp[i][0] = min(dp[i - 1][1] + a + 2 * b + a,dp[i - 1][0] + a + b);
			}
		}
		printf("%lld\n",dp[n][0]);
	}
	return 0;
}
```

---

## 作者：LevenKoko (赞：0)

$dp[i][0/1]$表示在第i个位置建高度为1 $or$ 2的管子

$s[i]=0$的时候高度可以为1可以为2

$s[i]=1$的时候高度只能为2

显然横着的一排管子，和竖着的高度为1的支撑杆是必须的，可以预先算出来是     $(n+1)*b+n*a$，不用转移的时候考虑

#### 转移式子：
$$dp[i][0]=min(dp[i-1][1]+a,dp[i-1][0])$$

$$dp[i][1]=min(dp[i-1][0]+a,dp[i-1][1])+b$$

这个很好理解，和上一个有高度差的话就要加一个竖着的管子，如果高度为2就得加一个支撑杆

然而有个坑点是最后**只能取高度为1的**，不能去高度为2的，因为这个熬夜打CF的时候这题直接调了1h,一直WA第13个点....当然也就导致直接下分

还有这个明显可以把第一维压掉，但是并没有卡空间，就懒得写了


```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (9223372036854775807)
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-')f=-1;chr=getchar();}
	while(isdigit(chr)) {ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}const int M = 2e5+5;
int T,dp[M][2],n,a,b;
char s[M];
signed main(){
	T=read();
	while(T--){
		n=read(),a=read(),b=read();
		scanf("%s",s+1),memset(dp,0x7f,sizeof(dp));
		dp[1][0]=0,dp[1][1]=a+b;
		for(int i=2;i<=n;i++){
			dp[i][1]=min(dp[i-1][0]+a+b,dp[i-1][1])+b;
			if(s[i]=='0')dp[i][0]=min(dp[i-1][1]+a,dp[i-1][0]);
		}cout<<(n+1)*b+n*a+dp[n][0]<<endl;
	}
	return 0;
}

```

---

## 作者：LJB00131 (赞：0)

我们把一个长度的十字路口转化为它两边的点的限制

于是就可以DP了

用$f[i][0/1]$表示这个点的高度为1或2的最小花费，按题意转移即可

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 200005
typedef long long ll;
const ll INF = 1e15;

int T, n;

ll a, b, f[N][2];

string s;

string get()
{
	string x;
	x.clear();
	// x[0] = ' ';
	char c = getchar();
	while(c != '0' && c != '1') c = getchar();
	while(c == '0' || c == '1') x += c, c = getchar();
	return x;
}

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		memset(f, 0, sizeof(f));
		scanf("%d%lld%lld", &n, &a, &b);
		s = get();
		// cout << s << endl;
		f[0][1] = INF;
		for(int i = 1; i <= n; i++)
		{
			f[i][0] = min(f[i - 1][0], f[i - 1][1] + a) + a + b;
			f[i][1] = min(f[i - 1][0] + a, f[i - 1][1]) + a + 2 * b;
			if(s[i] == '1' || s[i - 1] == '1') f[i][0] = INF;
			// cout << f[i][0] << ' ' << f[i][1] << endl;
		}
		cout << f[n][0] + b << endl;
	}
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

[在窝的博客阅读](https://froldh.github.io/2019/08/23/OI/codeforcesPlan/ER71/1207C/)  
[在luogu博客阅读](https://www.luogu.org/blog/oldherd/solution-cf1207c)  
这题可以贪心解决的说。  
观察可以发现,可能有效的操作是,我们把一整片高度为1的管道全部拔高为2使得这片高度为1的点和两边高度相等从而减少之字形中额外消耗的竖条。我们记这片高度为1的管道的长度为len,显然,它有$len+1$个支撑物。这样做,拔高消耗的代价为$b* (len-1)$,减少消耗的代价为$2a$。每一片的拔高决策是相互独立的,因此只需要比较其大小取较小的一个即可。  
注意,题目给出的两边的管道高度必定为1,且不允许拔高。考的时候辣鸡翻译器没有翻出这句话导致爆了QaQ.  

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 200010;
char str[maxn];
int pp[maxn], pu;

int main() {
	long long ans;
	int n, a, b, t, len, plr;
	char las = '0';
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d %s", &n, &a, &b, str);
		las = '0'; pu = 0; len = 1; plr = 2;
		for(int i = 1; i < n; i++) {
			plr += ((str[i]&15)||str[i-1]&15)?2:1;
			if(str[i] == las) len++;
			else {
				pp[pu++] = len;
				las = str[i];
				len = 1;
			}
		}
		pp[pu++] = len;
		ans = (long long)a*n + plr*(long long)b;
		for(int i = 2; i + 1 < pu; i += 2)
			ans += min((pp[i]-1)*(long long)b, (long long)a*2);
		if(pu!=1) ans += 2*a;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：曦行夜落 (赞：0)

非常优(jian)秀(dan)典(du)型(liu)的一道DP题目          
首先我们看到这道题的贪心是显然会被卡掉的（~~我都没想~~）  
这道题的Dp明显之处就在于他是一个线性的，而且**后面的选择与前面无关**的题，发现了这点就发现了Dp       
然后，对于这样的每个点出两种选择的题目，只需要把两种选择都作为状态存在Dp数组里面                 
比如本题，我们用$dp[i][1]$和$dp[i][2]$表示该点在高度为$1$和$2$的状态下最小的代价（**第一步，确定状态**）             
那么显然可以得到转移方程（**第二步，写出方程**）               
$dp[i][1]=min(dp[i-1][1]+a+b,dp[i-1][2]+2a+b)$  
$dp[i][2]=min(dp[i-1][1]+2a+2b,dp[i-1][2]+a+2b)$              
下面对照着讲一下      
第一条，这里修高度为$1$的柱子，如果上一个修的也是$1$，平着过来代价为$a$，修一个高为$1$的柱子代价为$b$。           
其他的此处不多叙说，留给读者思考              
然后**第三步，确定边界**，显然这里要从$0$点开始，那么$dp[0][1]=b$，题目里说要从高度$1$开始从高度$1$结束，所以答案就是$dp[n][1]$        
同时在Dp过程中，要注意十字路口高度必须为$2$，此时直接把$1$跳过即可，具体见代码（还是比较简单的一道DpQwQ）     


------------
```cpp
#include<bits/stdc++.h>
#define maxn (200000+500)
#define ll long long
using namespace std;
char s[maxn];
ll a,b,n;
ll f[maxn][3];
     
int main()
{
    int T;
    scanf("%d",&T);
    	
    while (T--)
   	{
    	scanf("%I64d%I64d%I64d",&n,&a,&b);
    	scanf("%s",s+1);
    	memset(f,0x3f,sizeof(f)); //最小化，设无穷大
    	f[0][1]=b; //初始化
    	for (int i=1;i<=n;++i)
    	{
    		f[i][2]=min(f[i-1][1]+2*a+2*b,f[i-1][2]+a+2*b); //方程2
    		if (s[i]==49 || s[i+1]==49) continue; //如果有路口不考虑1
    		f[i][1]=min(f[i-1][2]+2*a+b,f[i-1][1]+a+b); //方程1
    	}
   		printf("%I64d\n",f[n][1]); //输出答案
   	} 
   	
   	return 0;
}
```

---

## 作者：Konnyaku_ljc (赞：0)

我太弱了，昨天晚上被这道题坑坏了。。。  
言归正传——一眼，便看出是个DP，所以，我们的思想便要往dp上想  
首先,因为每个单位管道都有一个管道和一个支柱，所以输出答案时要加*a * n + b * (n+1)*  
因为一条路上有0有1，所以我们分类讨论——  
无论为0还是为1时，
```cpp
dp[x][1] = min (dp[x-1][0],dp[x-1][1]+a+b);
```
为1时，dp[x][0]不可取，赋值为1e18；  
为0时
```cpp
dp[x][0]  = min (dp[x][0],dp[x][1]+a+b);
```
附代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long t,n,a,b,dp[200005][2];
string s;
int main()
{
    cin >> t;
    while (t--)
    {
        for ( int i = 0; i <= n+1; i++ )
            for (int j = 0; j <= 2; j++ )
            {
                dp[i][j] = 1e18;//赋初值
            }
        cin >> n >> a >> b >> s;
        dp[1][0] = 0;
        for (int i = 1; i < n; i++ )
        {//动态转移
            if ( s[i] == '1' ) dp[i+1][0] = 1e18;
            dp[i+1][1] = min (dp[i][0]+a+b,dp[i][1]+b);
            if ( s[i] == '0' ) dp[i+1][0] = min (dp[i][0],dp[i][1]+a+b);
        }
        cout << dp[n][0] + a*n + b*(n+1) << endl;
        //输出时一定别忘记加上！！！
    }
}
```

---

