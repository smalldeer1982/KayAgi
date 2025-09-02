# Black and White Stripe

## 题目描述

You have a stripe of checkered paper of length $ n $ . Each cell is either white or black.

What is the minimum number of cells that must be recolored from white to black in order to have a segment of $ k $ consecutive black cells on the stripe?

If the input data is such that a segment of $ k $ consecutive black cells already exists, then print 0.

## 说明/提示

In the first test case, $ s $ ="BBWBW" and $ k=3 $ . It is enough to recolor $ s_3 $ and get $ s $ ="BBBBW". This string contains a segment of length $ k=3 $ consisting of the letters 'B'.

In the second test case of the example $ s $ ="BBWBW" and $ k=5 $ . It is enough to recolor $ s_3 $ and $ s_5 $ and get $ s $ ="BBBBB". This string contains a segment of length $ k=5 $ consisting of the letters 'B'.

In the third test case of the example $ s $ ="BBWBW" and $ k=1 $ . The string $ s $ already contains a segment of length $ k=1 $ consisting of the letters 'B'.

## 样例 #1

### 输入

```
4
5 3
BBWBW
5 5
BBWBW
5 1
BBWBW
1 1
W```

### 输出

```
1
2
0
1```

# 题解

## 作者：柳下惠 (赞：14)

[题目链接](https://www.luogu.com.cn/problem/CF1690D)。

### 题意简述

给出 $n$ 和 $m$，还有一个长度为 $n$ 且只包含 `B` 和 `W` 的字符串，问你在字符串中找出一个长度为 $m$ 且只包含 `B` 的子串最少需要修改多少个 `W`。

多组测试。

### Solution

考虑前缀和。先枚举字符串中每个字符，当前字符是 `B` 则为一，否则为零，然后前缀和，相当于把区间内有多少个 `B` 存了下来。然后我们枚举到子串左端点，假设为 $l$，那么 $r$ 就为 $l+m-1$，$l$ 到 $r$ 内有少个 `B` 就相当于该区间的区间和大小，左端点枚举到 $n-m+1$，取最大值即可。

### code

```cpp
	t=read();
	while(t--)
	{
		int cnt=0,tmp=0;
		int n=read(),m=read();
		string s;cin>>s;
		for(int i=0;i<n;i++)
		if(s[i]=='B') a[++cnt]=1;
		else a[++cnt]=0;	
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n-m+1;i++)
			tmp=max(tmp,sum[i+m-1]-sum[i-1]);
		printf("%d\n",m-tmp);
	}

```

---

## 作者：_djc_ (赞：3)

## 背景
这道题是本蒟蒻在美好的高考假期去 CF 通宵时做的，当时信誓旦旦地说这题是 DP 就去睡了，然而第二天想了许久连状态设计都感觉不太合理。于是看到题解区第一行字恍然大悟……

## 不是思路的思路

看到这题其实很容易联想到什么最长子序列啦有关 DP 的东西，但是我们会发现是很难设计状态的（至少是我这个蒟蒻的想法，可能是我确实太弱了）。如果我们用 DP，一维肯定是在字符串中的位置，一维肯定是决策要不要修改这个字符，另一维呢？修改次数还是最长连续字串长度？

其实类似于一个滑动窗口，~~然而暴力就可以~~，因为不是要求区间里最值之类的，所以也只能像暴力似的找，但是其实是不慢的，对于每次询问 $ O(n) $ 就可以了，时间复杂度个人想不出再低的了；

先统计出来前 $ m $ 个字符包含几个``` B ```，然后慢慢向后一个一个推到 $ n $ 就可以了。

## Code
```cpp
#include<bits/stdc++.h>
#define maxn 200005 //注意数据范围
using namespace std;
inline int read(){
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
} 
int n, m;
int T;
int a[maxn];
int win[maxn];//滑动的长度为m的窗口，win[i]表示这个窗口以i结尾
int main() {
	T = read();
	while(T--){
		memset(a, 0, sizeof(a)), memset(win, 0, sizeof(win));
		n = read(), m = read();
		for(int i = 1; i <= n; i++){
			char c; cin >> c;
			if(c == 'B') a[i] = 1; //我是将字符串转化为01，这样后面直接加减就行，当然也可以手动判断一下
			else a[i] = 0;
		}
		for(int i = 1; i <= m; i++){
			win[m] += a[i];
		} 
		int ma = win[m];
		for(int i = m + 1; i <= n; i++){
			win[i] = win[i-1] - a[i-m] + a[i];
			ma = max(win[i], ma);
		}
		cout << max(0, m - ma) << endl; //这个似乎不太需要，主要是第一开始写错了
	}
}
```

~~所以这题是不是还是挺水的~~

我想这就是：
### 完。


------------


---

## 作者：litachloveyou (赞：2)

#### 前缀和
这个题目要求我们找到最小需要修改的区间，使得这一区间的所有格子都是黑色的。

------------
我们可以运用前缀和的思想，把每一个要求的长度的区间的黑色格子数量记录下来，之后枚举每一个区间黑色格子的数量，找到最小的那个修改个数就可以了。**因为题目只要求有一段并且要修改次数最少的那一段。**
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[2 * 100000 + 10];
void solve()
{
	int n, k;
	scanf("%d%d", &n, &k);
	scanf("\n%s", s + 1);
	vector<int>a(n + 1);
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == 'B')a[i] = 1;
		a[i] = a[i - 1] + a[i];
	}
	int ans = 1e9 + 10;
	for (int i = k, j = 0; i <= n; i++, j++)
	{
		ans = min(ans, k - (a[i] - a[j]));
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：BFSDFS123 (赞：2)

看起来像 dp，然而并不是 dp。


----


考虑一个像**滑动窗口**一样的算法。

窗口长度为 $k$，设 $cnt$ 为当前需要变成黑色格子的白色格子的数目。**窗口所囊括的 $k$ 个格子全部是会被染成黑色**

每次窗口向前前进一位的时候，窗口中最后一个字符会被去掉，窗口后第一个字符会被加进来。

考虑这两个字符。

若最后一位是 ``B``，可以发现，移动窗口后，黑色格子的数目减一。

若最后一位是 ``W``，由于窗口的大小只有 $k$，所以这个格子肯定被染成了黑色。于是移动窗口后，黑色格子的数目减一，$cnt$ 减一。

若窗口后的第一位是 ``B``，移动窗口后，黑色格子的数目加一。

若窗口后的第一位是 ``W``，移动窗口后，黑色格子的数目加一，$cnt$ 加一。

~~有点像莫队的转移啊~~

在每次操作后，存储当前 $cnt$ 的最小值，最后输出。

这个方法有一些小 bug，所以我加了一些奇奇怪怪的特判。

代码：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
//#define int long long
#define ull unsigned long long
#define ll long long
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		string str;
		cin>>str;
		int cnt=0;
		for(int i=0;i<k;i++)
		{
			if(str[i]=='W')
			{
				cnt++;
			}
		}
//		cout<<"c="<<cnt<<endl;
		int minn=0x3f3f3f3f;
		minn=min(minn,cnt);
		int lst=0,now=k-1;
		for(int i=k;i<n;i++)
		{
//			cout<<"i="<<i<<endl; 
			int sum=k;
			if(str[lst]=='B')
			{
				sum--;
			}else{
				sum--;
				if(cnt>0) cnt--;
			}
//			cout<<"cnt'="<<cnt<<endl;
			now++;
			if(sum<k)
			{
				if(str[now]=='B')
				{
					sum++;
				}else{
//					cout<<"GOT"<<endl;
					cnt++;
					sum++;
				}
			}
			if(sum==k)
			{
				minn=min(minn,cnt);
			}
//			cout<<sum<<" "<<cnt<<endl;
			lst++;
		}
		printf("%d\n",minn);
	}
	return 0;
}

```


---

## 作者：Night_sea_64 (赞：1)

[CF1690D 题目传送门](https://www.luogu.com.cn/problem/CF1690D)

主要知识点：字符串基本操作、前缀和。

问题其实就是，对于字符串中每个长度为 $m$ 的子串，$\texttt{W}$ 的个数的最小值。

利用前缀和算法可以快速知道某一个区间内某一个东西的和。所以我们可以用前缀和来记录。具体而言，前缀和数组 $sum_i$ 表示从字符串的第 $1$ 个字符到第 $i$ 个字符有多少个 $\texttt{W}$。

这样再枚举一遍字符串的每个字符，就可以用前缀和数组快速求出以这个字符开始，长度为 $m$ 的子串中到底有多少个 $\texttt{W}$ 了。最后再取一遍最小值就可以了。AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int sum[200010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(sum,0,sizeof(sum));
        int n,m;
        string s;
        cin>>n>>m>>s;
        s=" "+s;//为了方便，可以让字符串下标从 1 开始，在前面垫一个字符。
        for(int i=1;i<=n;i++)
        {
            if(s[i]=='W')sum[i]=sum[i-1]+1;
            else sum[i]=sum[i-1];
            //取前缀和
        }
        int minn=1e9;
        for(int i=1;i<=n-m+1;i++)
            minn=min(minn,sum[i+m-1]-sum[i-1]);
        cout<<minn<<endl;
    }
    return 0;
}
```


---

## 作者：y_kx_b (赞：0)

题意很清楚，就不提了。

Sol.
-
一开始看到题目想到 dp，但是发现题解区都是前缀和。

那么我今天用差分做这个题 ~~（虽然还是用到了前缀和）~~

设 `dp[i]` 为以 $i$ 为起点，长度为 $m$ 的子串需要修改的次数。

先假设字符串中全是 `B`，显然所有 `dp` 值均为 $0$。

考虑当字符串中出现一个 `W` 会怎么样。

显然，第 $i$ 个位置出现一个 `W` 会让 `dp[i-m+1]`~`dp[i]` 值加 $1$。

那么很容易想到差分了。

最后统计 `dp[1]`~`dp[n-m+1]` 中的最小值即可。

Q：~~为什么不用线段树/树状数组？~~

A：线段树/树状数组一般用于在线修改/查询，复杂度是 $\mathcal O(n\log n)$。

 $\ \ \ \ \,$ 而差分是离线修改/查询，复杂度是 $\mathcal O(n)$。

此题最后才询问，所以可以用差分。

注意，因为差分区间加的左端点可能是负数，所以我们要把数组集体往右平移 $2\times 10^5$ 格。
### code:

```cpp
char s[N];
int dp[N<<1];
int delta[N<<1];
bool major(){
	memset(delta,0,sizeof delta);
	int n=read(),m=read();
	scanf("%s",s+1);
	for(itn i=1;i<=n;i++)
		if(s[i]=='W')
			delta[i-m+1+N]++,delta[i+1+N]--;
	int ans=0x3f3f3f3f;
	dp[0]=0;
	for(int i=1;i<=N;i++)//负数区间前缀和，不计入答案（因为一大堆0）
		dp[i]=dp[i-1]+delta[i];
	for(int i=N+1;i<=(n-m+1)+N;i++)
		ans=min(ans,(dp[i]=dp[i-1]+delta[i]));
	return printf("%d\n",ans);
}
```
~~细心的你可能会发现上面的代码中 `dp` 数组可以直接去掉……~~

那么，感谢观看。~~也感谢管理员大大没有关上题解通道。~~

---

## 作者：zbk233 (赞：0)

## 解题思路

考虑贪心的思路。

对于一个区间 $[i,i+k-1]$，我们考虑记录下 `W` 的数量，那么这些 `W` 都是要修改的。

那么我们就要找到一个 `B` 最多、`W` 最少的，长度为 $k$ 的区间，记录下 `W` 的数量。

我们可以通过前缀和来记录一个区间 `B` 的数量，那么用 $k$ 减去这个数就是答案了。

## 参考代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int s[200005],T,n,k,maxx=-1145141919;
char a;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        maxx=-1145141919;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a;
            s[i]=s[i-1]+(a=='B'?1:0);
        }
        for(int i=1;i<=n-k+1;i++) maxx=max(s[i+k-1]-s[i-1],maxx);
        cout<<max(k-maxx,0)<<'\n';
    }
    return 0;
}
```


---

## 作者：linyuhuai (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1690/D) & [前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/06/12/CF1690D题解)

### 题意

找到一个长度为 $k$ 区间，使得区间中白色方块尽可能少，输出最少区间的白色方块数量。

### 思路

将 `W` 改为 $1$，将 `B` 改为 $0$，存储在 $a$ 数组当中。

暴力枚举找到

$$\min_{1\le i\le n-k}\sum_{j=i}^{i+k}a_i$$

即可。

时间复杂度为 $O((n-k)\times k)$



```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
#define DEBUG puts("shsyyds")
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a>b?b:a;}
int sum[200005];
void solve(){
    int n,k;
    scanf("%d%d",&n,&k);
    getchar();
    for(int i=1;i<=n;i++){
        char ch;
        scanf("%c",&ch);
        if(ch=='W')sum[i]=sum[i-1]+1;
        else sum[i]=sum[i-1];
    }
    int ans=INF;
    for(int i=0;i<=n-k;i++){
        ans=min(ans,sum[i+k]-sum[i]);
    }
    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}
```





---

## 作者：andrew2012 (赞：0)

# 解题思路

为了获得一段 $k$ 个黑色细胞，我们需要将该段的所有白色细胞涂成黑色。然后遍历所有长度为 $k$ 的片段(只有 $n$  $-$  $k$ 个片段)，从中选择一个片段上白细胞数量最少的片段。你可以通过前缀和快速找出片段中白细胞的数量。

# AC代码

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
string s;//字符串s是每次的输入数据之一
int t,n,k;//数t代表t组数据，n、k是每次的字符数及目标数
int main()
{
    cin>>t;//输入
    while(t--)//t组数据
    {
        cin>>n>>k>>s;//n个字符、目标k、字符串s
        vector<int>w(n+1);//向量类型
        for(int i=1;i<=n;i++)//n个字符串一一判断
            w[i]=w[i-1]+int(s[i-1]=='W');//维护前缀和
        int result=INT_MAX;//极大值INT_MAX
        for (int i=k;i<=n;i++)//每次取最小值
            result=min(result,w[i]-w[i-k]);//min函数取最小值
        cout<<result<<endl;//每次输出得出的最少操作次数（记得换行！）
    }
}
```



---

## 作者：_Ad_Astra_ (赞：0)

一道比较简单的前缀和题。

我们可以枚举字符串 $s$ 中每个长度为 $k$ 的子串，也就是枚举满足 $1 \le i \le n-k+1$ 的每一个 $i$ ，就是 $s_i,s_{i+1},s_{i+2},\cdots,s_{i+k-1}$ 。那么如果我们要把这个字串全部涂成 $\texttt{B}$ （这样就有了长为 $k$ 的连续的 $\texttt{B}$ ），容易想到我们要替换成 $\texttt{B}$ 的 $\texttt{W}$ 的个数就是子串中 $\texttt{W}$ 的个数。

我们可以开一个前缀和数组 $pre$ ，$pre_i$ 表示 $s$ 的前 $i$ 个字符中 $\texttt{W}$ 的个数。那么 $l$ 到 $r$ 中间 $\texttt{W}$ 的个数就是 $pre_r - pre_{l-1}$ 。

所以，问题就能转换成枚举满足 $1 \le i \le n-k+1$ 的每一个 $i$ ， $pre_{i+k-1}-pre_{i-1}$ 的最小值。

复杂度 $O(n)$ 。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,pre[200010],ans;
string s;
void main_solve()
{
	cin>>n>>k>>s;
	s=" "+s;
	memset(pre,0,sizeof(pre));
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+(s[i]=='W');
	ans=0x3f3f3f3f;
	for(int i=1;i<=n-k+1;i++)ans=min(ans,pre[i+k-1]-pre[i-1]);
	cout<<ans<<endl;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)main_solve();
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1690D)
由于是把白色染成黑色，我们只需要统计每个区间的白色数量即可。

使用前缀和维护，枚举每个区间的起点，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n,k,sum[maxn];
string s;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k>>s;
		s=' '+s;
		for(int i=1;i<=n;++i)
			sum[i]=0;
		for(int i=1;i<=n;++i){
			if(s[i]=='B')
				sum[i]=1;
			sum[i]+=sum[i-1];
		}
		int ans=k;
		for(int i=1;i+k-1<=n;++i)
			ans=min(ans,k-(sum[i+k-1]-sum[i-1]));
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：fast_photon (赞：0)

**0. 前言**  
**提醒：本题有多测**  
[这题](https://luogu.com.cn/problem/CF1690D)适合唬人，说白了就是思维题。思考加实现用了九分钟，是本场比赛我用时第三短的题目（第一 A，用了三分钟，第二 C，用了五分钟，B因为【】错误+不开 LL 用了将近二十分钟。。。）  

**1. 分析**  
如果暴力很简单，就枚举每个 $1\le i<i+k-1\le n$，的区间，然后看有多少个白色，统计最小值就完了。  
但是 $n^2$ 原地 T 飞。  
有没有更快的统计方法呢？  
我们先看 $[1,k]$ 这个区间。暴力统计一下。  
然后就该统计 $[2,k+1]$ 了。（倒序枚举也差不多）我们发现，这次还需要再循环 $k$ 次，真是太麻烦了。而 $[1,k]$ 这个区间的答案已经知道了，所以是不是可以...借来用用？  
但是我们要先把 $1$ 的位置踢了。如果是白色，那么用前面的答案减去 $1$。再把 $k+1$ 加进来，如果是白色，那么前面的答案再加上 $1$，就得到了 $[2,k+1]$ 的答案。以此类推，每一次把前面一个的左端点去掉，这一个的右端点加进来，就变成了当前区间的答案。  
~~那你可能就要问了，我太菜了容易写挂怎么办？~~  
我们可以对这个算法进行写法上的优化。  
抡出我们的利器 **前缀和**。  
令白色为 $1$，黑色为 $0$，求前缀和 $s$，满足 $s_i=\sum_{j=1}^ia_j$，对于区间 $[i,j]$，每个元素的和就是 $s_j-s_{i-1}$。直接用上面公式算一下就知道了。  

但是因为我懒得重写，同时也因为第二种方法比较好实现（借口一大堆）所以放的是第一种做法的代码。  

**2. 代码**  
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define maxn 200005

using namespace std;

string s;

void solve() {
	int n, k, ans = 0x3f3f3f3f;
	scanf("%d %d", &n, &k);
	cin >> s;
	int cnt = 0;
	for(int i = 0; i < k; i++) {
		if(s[i] == 'W') cnt++; //暴力统计 [1,k]，我从0开始存储的
	}
	ans = min(ans, cnt);//别忘了这里要统计一次答案
	for(int i = k; i < n; i++) {//这里我枚举右端点
		if(s[i] == 'W') cnt++;//加上后面的
		if(s[i - k] == 'W') cnt--;//扣掉前面的
		ans = min(ans, cnt);
	}
	printf("%d\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);//记得有多测
	while(t--) {
		solve();
	}
}
```

---

## 作者：LOVE_Ynoi (赞：0)

### 题目做法

#### 贪心决策
为了凑齐 $k$ 个连续的 `B`, 我们可以正好尝试凑齐 $k$ 个 `B`。  
枚举区间 $[i,i+k](0\le i \le n-k-1)$。  
寻找这个区间中的 `W` 的个数，这些个数中的最小值就是答案。  

#### 优化
可以用前缀和进行优化。  
用 $sum_i$ 代表前 $i$ 个字符中 `W` 的个数  
那么 区间 $[i,i+k]$ 中字符 `W` 的个数就是 $sum_{i+k}-sum_{i-1}$  

时间复杂度 $O(n)$  
#### 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n,k;
    cin>>n>>k;
    string str;
    cin>>str;
    vector<int> s(n+1);
    s[0] = 0;
    for(int i = 0;i<n;i++){
        s[i+1] = s[i] + 1*(str[i]=='W');
    }
    int ans = 0x7f7f7f7f;
    for(int i = k;i<=n;i++){
        ans = min(ans,s[i]-s[i-k]);
    }
    cout<<ans<<endl;
}
int main(){
    int _ = 1;
    cin>>_;
    while (_--){
        solve();
    }
    return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

# 题目分析

令 $\verb!B!$ 为 $1$,$\verb!W!$ 为 $0$。然后序列就变成了一个 $01$ 序列。

求出这个序列的前缀和，然后枚举每个位置 $i$，假设这个位置 $i$ 为连续 $m$ 个 $1$ 的起点，那么我们要的终点就是 $i+m-1$，看一下 $[i,i+m-1]$ 这段区间里 $0$ 的个数就好了，其实这也就是 $m-(sum[i+m-1]-sum[i-1])$。

# 代码

```cpp
// Problem: D. Black and White Stripe
// Contest: Codeforces - Codeforces Round #797 (Div. 3)
// URL: https://codeforces.com/contest/1690/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date:2022-06-07 23:12
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int INF = 0x3f3f3f3f;
const int N = 2e5 + 5;
int sum[N];
char s[N];
int T,n,m;
inline void init() {
	mst(sum,0);
}
inline int Abs(int x) {
	return x > 0 ? x : -x;
}
inline void solve() {
	n = read(),m = read();
	scanf("%s",s + 1);
	int len = s[1] == 'B';
	for (register int i = 2;i <= n; ++ i) {
		if (s[i] != s[i - 1] && s[i] == 'B') {
			len = s[i] == 'B';
		} else if (s[i] == s[i - 1] && s[i] == 'B') {
			len ++;
		}
	}
	if (len >= m) {
		puts("0");
		return;
	}
	for (register int i = 1;i <= n; ++ i) {
		sum[i] = sum[i - 1] + (s[i] == 'B');
	}
	int ans = INF;
	for (register int i = 1;i <= n; ++ i) {
		int at = i + m - 1;
		if (at > n) continue;
		ans = std::min(ans,(at - i + 1) - (sum[at] - sum[i - 1]));
	}
	printf("%d\n",ans);
}
int main(void) {
	T = read();
	while (T --) {
		init();
		solve();
	}
	
	return 0;
}
```

---

