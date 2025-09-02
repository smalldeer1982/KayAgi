# Balanced Round

## 题目描述

你是codeforces round的出题人，现在你将设置n个问题，第i个问题的难度是ai。你将进行以下操作步骤：
1.	从题单中移除一部分题目（移除的题目的数量可能是0）
2.	按你想要的任何顺序重新排列剩余的问题

当且仅当任意两道连续的题目的难度之差的绝对值最多为k时（即绝对值小于等于k），这一回合（round）会被认为是平衡的。

你最少需要移除多少道题目，才能使问题的安排是平衡的？

## 说明/提示

对于第一个样例，我们可以移除前两个问题并得到一个问题的排列，其难度为【4，5，6】，连续的两个问题的难度之差的绝对值满足|5-4|=1≤1，|6-5|=1≤1

对于第二个样例，我们可以得到一个问题并将这一个问题（难度10）作为一个回合(round)

## 样例 #1

### 输入

```
7
5 1
1 2 4 5 6
1 2
10
8 3
17 3 1 20 12 5 17 12
4 2
2 4 6 8
5 3
2 3 19 10 8
3 4
1 10 5
8 1
8 3 1 4 5 10 7 3```

### 输出

```
2
0
5
0
3
1
4```

# 题解

## 作者：Andy_Li (赞：6)

# CF1850D Balanced Round题解

### 题意

给定一个长度为 $n$ 的数组，删除一些数并排序后需要使其相邻的两个数差值 $ \le k$，问最少删除几个数。

### 思路

先将 $a$ 数组从小到大排序，考虑将其分成多个块，每个块中相邻两个数的差值 $ \le k$。求出块长度最大的块的长度，用总数 $n$ 减去长度最大的块的长度便是答案。

### 赛时代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int s[200010];
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
// srand((unsigned)time(NULL));
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,cnt=1,ans=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>s[i];
		sort(s+1,s+n+1);
		for(int i=2;i<=n;i++)
			if(abs(s[i-1]-s[i])>k)
			{
				ans=max(ans,cnt);
				cnt=1;
			}
			else
				cnt++;
		ans=max(ans,cnt);
		cout<<n-ans<<endl;
	}
	return 0;
}
```


---

## 作者：WsW_ (赞：4)

题意略。

---

### 思路：
为了使相邻两个数尽可能小，先将数列排序。  
排序后的数列显然满足 $a_1\le a_2\le\dots\le a_n$。  

当 $a_i-a_{i-1}>k$ 时，说明 $a_i$ 和 $a_{i-1}$ 必须扔掉一个。  
如果扔 $a_i$，因为 $a_{i+1}\ge a_i$，所以仍然 $a_{i+1}-a_{i-1}>k$，那 $a_{i+1}$ 也要扔掉。  
以此类推，如果扔 $a_i$，那么后面的都要扔。  
同理，如果扔 $a_{i-1}$，那么前面的也都要扔。

此时，可以发现保留数字的是排序后数列中的**连续的一段**，当 $a_i-a_{i-1}>k$ 时，我们就必须在这里分段。  
要求扔的数最少，也就是保留的数最多，设最大的段长为 $ans$，那么扔的最少数量就是 $n-ans$。

循环遍历数列，每次分段时就可以求出这一段的段长。$ans$ 更新，取较大值。

---

### 代码和[提交记录](https://codeforces.com/problemset/submission/1850/214865874)
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
int ans;
int a[200003];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		int ans=0,l=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+1+n);
		for(int i=2;i<=n;i++){
			if(a[i]-a[i-1]>k){
				ans=max(ans,i-1-l);
				l=i-1;
			}
		}
		ans=max(ans,n-l);
		printf("%d\n",n-ans);
	}
	return 0;
}
```

---

## 作者：___w (赞：4)

### [ CF1850D Balanced Round](https://www.luogu.com.cn/problem/CF1850D)

#### 题意简述
给一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，可以对序列进行重新排列和删除一些数，满足任意相邻两个数的差的绝对值不能超过 $k$，求最小删除个数。

#### 题目分析
我们考虑贪心。先将 $a$ 按升序排序，然后进行判断。

对于第 $i$ 个位置，若 $|a_i-a_{i+1}|>k$，由于单调性，后面的数就全都得删掉了。所以说所有满足相邻两个数的差的绝对值不能超过 $k$ 的序列都为一个块。我们可以统计每个块的大小，最后答案就是 $n$ 减去最大的块的长度。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
int t, n, k, a[N];

int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		sort(a+1, a+n+1);
		int Max = 0, len = 1;
		for (int i = 2; i <= n; ++i) {
			if (a[i]-a[i-1] <= k) ++len;
			else Max = max(Max, len), len = 1;
		}
		Max = max(Max, len);
		cout << n-Max << '\n';
	}
	return 0;
} 
```

---

## 作者：_Only_this (赞：3)

### CF1850D Balanced Round 题解

------------

本题读题后不难发现，贪心是一个比较合理的思路，因此考虑贪心。

先将数组排序，因为要维护数组中相邻的数字之差 $\leq k$，所以可以将差 $>k$ 的地方分开，成为一个块，不难发现，最后的答案只能保留一个块，所以保留最大的那个块就行了。

下面附个代码，

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int T,n,k;
int a[maxn];
int Solve(){
	int sz=1,maxx=0;
	bool flag=0;
	for(int i=2;i<=n;i++){
		if(a[i]-a[i-1]<=k){
			sz++;
		}
		else{
			sz=1;
			flag=1;
		}
		maxx=max(maxx,sz);
	}
	return (!flag) ? 0 : n-maxx;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		printf("%d\n",Solve());
	}
	return 0;
}
```


---

## 作者：Awsdkl (赞：1)

 [原题传送门](https://codeforces.com/contest/1850/problem/D)  

## 题意翻译  

给定一个长度为 $n$ 的数组 $a$ 与一个整数 $k$，询问将数组 $a$ 删去几个数，重排列后，存在的是最长的满足相邻两数的差不大于 $k$ 的 $a$ 的子串。  

求这个数的最小值。  

## 思路

我们不妨先将 $a$ 排序。  

既然题目让我们求删去数的最小值，那我们只需要求保留数的个数的最大值，在用 $n$ 减去这个数，即可算出答案。  

那么如何求这个最大值呢？  

我们先将这个最大值定义为 $ans$。  

现在我们只需要扫一遍 $a$ 数组，判断两两之差 $|a_i-a_{i-1}|$，当这个值小于 $k$ 时，我们将计数器 $cnt$ 加 $1$，否则就将 $cnt$ 设为 $1$，然后每一次都将 $ans$ 设为 $\max(ans,cnt)$。  

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int t;
int n,k;
int a[MAXN];

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a + 1,a + n + 1); //将 a 排序。
		int cnt = 0;
		int ans = 1; //将 ans 设为 1 ，放置只有一个数且第一个数和 0 的差的绝对值大于 k 时，在下面for循环中被if直接跳出，无法给 ans 赋值。
		for(int i = 1;i <= n;i++)
		{
			if(abs(a[i-1] - a[i]) > k) //如果不符合要求，就将计数器设为 1
			{
				cnt = 1;
				continue;
			}
			cnt++; //计数器加 1
			ans = max(ans,cnt); //每次对 ans 做最大值。
		}
		printf("%d\n",n - ans); //因为我们求的是保留数的个数，所以答案要用 n - ans。
	}
	
	
	return 0;
}

```



---

## 作者：Dream__Sky (赞：1)

题意简述：

您是 `Codeforces` 一轮的作者，您准备了 $n$ 个问题，问题 $i$ 有难度 $a_i$。您将完成以下过程：

- 从列表中删除一些问题（可能是零）；
- 将剩下的问题按任意顺序重新排列。

当且仅当任意两个连续问题的难度绝对值最多相差 $k$（小于或等于 $k$）时，一轮比赛才算平衡。

为了使问题的排列平衡，你至少要删除多少个问题？

分析：

这道题用贪心来做。

首先先排序一遍，每当两个点只见相差超过了 $k$，我们就分段。接着我们找到最长的一段保留下来，剩下的就是要删除的。

为什么这么讲？因为是排序后分段，所以当前面那个段的最大值也比不过后一个段的最小值时，这两个段无论如何都不能组合，肯定要删去一个段。那么问题就变成了，求最长的相邻两个绝对值不超过 $k$ 的段的长度。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k,a[200005];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);//排序
		a[n+1]=a[n]+k+1;
		int maxn=0,daan=1;
		for(int i=2;i<=n+1;i++)
		{
			if(a[i]-a[i-1]<=k) daan++;
			else  
			{
				maxn=max(maxn,daan);
				daan=1;
			}
		}//找最大的段（只有它要保留）
		cout<<n-maxn<<endl;//输出删除的。
	}
	return 0;
}


```


---

## 作者：cjh20090318 (赞：1)

## 题意

给你一个有 $n$ 个整数的序列 $a$，求最多需要删除多少个数才能让任意两个问题的绝对值之差小于等于 $k$。

## 分析

首先我们将序列 $a$ 排序。

经过分析，如果 $a_i-a_{i-1}>k$，那么 $a_i$ 左侧的都会被删除。

经过观察可以发现，我们可以算出最多保留多少个。

个数即为相邻两个绝对值小于等于 $k$ 的最大长度。

最后答案即为 $n$ 减去最多保留个数。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
int n,k;
int a[200002];
void solve(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	std::sort(a+1,a+n+1);
	if(n==1){puts("0");return;}//特判 n=1 时一定为 0。
	int ans=0,c=1;//连续段数至少为 1。
	for(int i=2;i<=n;i++)
		ans=std::max(ans,c=((a[i]-a[i-1]<=k)?c:0)+1);//如果绝对值小于等于 k，那么加一，否则归为 1。
	printf("%d\n",n-ans);//即 n 减去最大长度。
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve(); 
	return 0;
}

```

---

## 作者：I_am_kunzi (赞：1)

# CF1850D 题解

### 题目翻译

有 $ t $ 组数据，每组数据给定 $ n $ 和 $ k$，分别代表题目数量和最终保留题目中相邻两题间最大的差值，例如当 $ k = 2 $ 时代表 $ \left| a_i - a_{i + 1} \right| \le k$。可以删除若干个题目并且可以重排题目顺序，求最终需要删除的题目数的最小值。

### 题目思路

题目中并没有说只能删除一段区间中的题目，并且可以重新排序，所以自然想到了可以选择题目难度最相近一段，所以需要先将这个数组排序。

排序完成后再对整个数组进行遍历，并记录两个变量 $ maxx , combo $ 分别代表目前最大满足要求的题目数量和现在这一段满足要求的题目数量，每次遇到不符合要求的题目就更新 $ maxx $ 并将 $ combo $ 设为 $ 0$，当然不要忘记最后还需要重新更新 $ maxx $ 的值。

### 题目代码

```cpp
int a[200005];
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(a , 0 , sizeof(a)); // 每次使用记得清空，避免奇怪的错误
		int n;
		cin >> n;
		int k;
		cin >> k;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		sort(a + 1 , a + n + 1); // 先给数组排序，为了后面的遍历
		int maxx = 0 , combo = 0;
		for(int i = 1 ; i < n ; i++)
		{
			if(a[i + 1] - a[i] <= k) // 满足条件的题目
			{
				combo++;
			}
			else // 不满足条件的题目，更新 maxx 的值并清空 combo
			{
				maxx = max(maxx , combo);
				combo = 0;
			}
		}
		maxx = max(maxx , combo);
		cout << n - (maxx + 1) << endl; // 需要注意的是，maxx 和 combo 的值初始为 0，所以这里做减法时需要用 maxx + 1
	}
    return 0;
}
```

---

## 作者：破壁少年 (赞：1)

### CF1850D Balanced Round 题解

------------
前言：这道题是 CF 比赛第 $4$ 题，比较水。

做法：数据点不大，考虑贪心，首先把给的数组 $a$ 排个序，顺序枚举每个合法区间的长度，枚举到这个数减去上个数大于 $k$ 的话，长度清空，同时用   $ans$ 更新最大长度，输出即可。

具体看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define naipaokuikui main
long long t;
long long a[1000010],ans,cnt,beg,last;
int naipaokuikui(){
	long long t;
	cin>>t;
	while(t--){
		ans=1;
		long long n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		cnt=1;
		for(int i=2;i<=n;i++){
			if((a[i]-a[i-1])>k){
				ans=max(ans,cnt);
				cnt=0;
			}
			 cnt++;
		} 
		ans=max(ans,cnt);
		cout<<n-ans<<endl;
	}
	return 0;
}




```


---

## 作者：Dreamer_Boy (赞：1)

[原题链接](https://codeforces.com/contest/1850/problem/D)。

#### 题目大意
给你一些数，问至少删掉多少数后两两不大于 $k$。

我们可以画图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/9nhuzas0.png)

最后我们取 $\max(2,1)$，由于我们求的是合法的，所以还得用长度减去 $2$，最终答案就是 $2$。

根据图我们就知道可以遍历一遍数组，用 $t$ 记录下最长合法序列长度，最后用 $n - t$ 即可。

#### 代码
```

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
void work()
{
  int a[N];
  int n, k;
  cin >> n >> k;
  for(int i = 1;i <= n;i ++ ){
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n);
  int maxn = 1;
  for(int i = 2, t = 1;i <= n;i ++ ){
    if(a[i] - a[i - 1] > k) t = 1;
    else t ++;
    maxn = max(maxn, t);
  }
  cout << n - maxn << endl;
}
int main()
{
  int T;
  cin >> T;
  while(T -- ){
    work();
  }
  return 0;
}
```
#### 

---

## 作者：tang_mx (赞：1)

刚刚写的题解忘保存了，重写一次。

本人第一次参加 CF,只做到了这一题，赛时用 dp 做的，过了，然而赛后似乎被 hack 了。改完之后来交一发题解。

此题的正解应该考虑**贪心**。

为了使相邻两数之差尽可能小，应当对数列进行排序。排序之后对数列进行遍历，当前后两数之差大于 $k$ 时，进行分段。因为问的时删掉的最少的数目，因此看前后两段哪一段长，用 $ans$ 来存这个保留的最大值，最后 $n-ans$ 就是所要删掉的最小值。

CODE

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+10;

int t,n,k,a[N];

inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

int main(){
	scanf("%d",&t);
	while(t--){
		int ans=0;
		n=read(),k=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		int x=1;
		for(int i=2;i<=n;i++){
			if(a[i]-a[i-1]>k)ans=max(ans,x),x=0;
			x++; 
		}
		ans=max(ans,x);
		printf("%d\n",n-ans);
	}
	return 0;
}

```

放个[赛时代码](https://codeforces.com/contest/1850/submission/214880002)，最后一点被 hack 了

---

## 作者：Crazyouth (赞：0)

**翻译**

有一个 $n$ 个数的数列 $a$，可以对它进行排序（按任意顺序）或删去某个数，使对于 $\forall 1< i\le n$，都有 $|a_i-a_{i-1}|\le k$，求最少删去多少数。

**分析**

易发现我们首先需要从小到大排序。

接下来考虑删除，会发现假如排序后有 $|a_i-a_{i-1}|>k$，那 $a_i$ 左边的数都不能要了，知道这个策略之后开始模拟。考虑正难则反，计算最多保留多少个，最后用 $n$ 减去它就是答案。使用一个计数器，每次有 $|a_i-a_{i-1}|>k$ 就计数器归一，否则就加一，然后每次扫完更新 $ans$ 即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(2e5+10)];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		int ans=-1,tp=1;//ans与计数器
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);//从小到大
		for(int i=2;i<=n;i++)
		{
			if(a[i]-a[i-1]>k)//计数器归一
			{
				tp=1;
				continue;
			}
			tp++;
			ans=max(ans,tp);//更新ans
		}
		ans=max(ans,tp);//最后还要更新一次
		if(ans==-1) ans=1;//假如ans=-1，说明没有被更新，说明只有一个数
		cout<<n-ans<<endl;
	}
	return 0;
}

---

## 作者：lilong (赞：0)

根据题意，不难想到贪心，将 $a$ 从小到大排序，使得相邻两数之差的绝对值尽可能小。若存在两数之差的绝对值大于 $k$，则将两数之间作为一个“分界线”。在确定所有“分界线”后，序列被分成了多个子段，这些子段中**最多保留一个**才能满足条件。根据贪心，选择保留最长的一段，用 $n$ 减去其长度即为答案。

```cpp

#include <bits/stdc++.h>
#define int long long

using namespace std;

int a[1000001];

signed main()
{
    int T,n,k,cnt,ans;
    cin >> T;
    while( T -- )
    {
        cin >> n >> k;
        for( int i = 1 ; i <= n ; i ++ )
            cin >> a[i];
        sort( a + 1 , a + n + 1 );
        cnt = 1;
        ans = 1;
        for( int i = 2 ; i <= n ; i ++ )
            if( a[i] - a[i - 1] > k )
            {
                ans = max( ans , cnt );
                cnt = 1;
            }
            else cnt ++;
        ans = max( ans , cnt );
        cout << n - ans << endl;
    }
    return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：0)

将数组由小到大排序，$|a_i-a_{i-1}|$ 可转化成 $a_i-a_{i-1}$。

由于求删去的数取最小值，则剩下的数取最大值。

所以只要差值小于等于 $k$，则保留当前项；如果大于 $k$，计数器从 $1$ 重新开始计算，之前的每一项相当于全部删除。取其中的最大值，最终将总共的个数 $n$ 与之相减即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
void solve()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	int ma=0,c=0;
	for(int i=1;i<=n;i++){
		if(a[i]-a[i-1]<=k)c++;
		else c=1;
		ma=max(ma,c);
	}
	cout<<n-ma<<'\n';
}
int main()
{
	int t;
	cin>>t;
	while(t--)solve();
}
```

---

## 作者：fengxiaoyi (赞：0)

由于限制是在相邻的两个数上，所以考虑从小到大排序，这样可以最小化相邻两个数的差的绝对值。

我们可以把排序后的序列分成若干段，每段段内两两之差的绝对值一定是小于等于 $k$ 的，而不同段的两个数之差一定是大于 $k$ 的。

显然，我们只能保留一段，由于要划去最少得数，所以要保留最长的那一段。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200010];
bool cmp(int x,int y){
	return x<y;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1,cmp);
		int ans=0,sum=0;
		for(int i=1;i<=n;i++){
			if(sum==0||a[i]-a[i-1]<=k) sum++;
			else{
				ans=max(ans,sum);
				sum=1;
			}
		}
		ans=max(ans,sum);
		printf("%d\n",n-ans);
	}
	return 0;
}
```


---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定一个长度为 $n$ 的序列 $a$，请删去 $a$ 中的一些数（可以不删）并将其任意重排，使得 $\forall 1\le i <n, |a_{i+1}-a_i|\le k$。

本题有多测，共 $t$ 组数据，题目保证 $1\le t\le 1000, n\ge 1, \sum_{i=1}^{t} n_i \le 2 \times 10^5, 1\le k \le 10^9, 1\le a_i\le 10^9$。

### 题目分析

首先我们可以发现，题目中的两次操作可以互换顺序（即，先任意重排，再删去一些数，因为重排不会影响删数）；其次，为了使相邻两数的差值的最大值最小，我们应该使数列**有序**。所以，我们在读入以后应该将 $a$ 从小到大（从大到小亦可）排序。

排序以后，我们遍历 $a$，将其分为多个不同的段，如果两个相邻数之间的差值大于 $k$，我们就分一个段。例如，$k=1, a=\{1,2,4,5,6\}$，那么我们就会将 $a$ 分成两个段：$\{1,2\}$ 和 $\{4,5,6\}$。

对于每个段，因为它的最后一个数和它的下一个段的第一个数相差超过了 $k$，那么，**无论这个段之后的部分留下多少个数，这个段最后一个数和其后一个数的差值将一直大于 $k$**，应该将其右边的数全部删除，这个段之前的部分同理应该删除，所以最终，我们只能留下一个段。问题就转化为了：**求 $a$ 中最长的段的长度**。按照题意模拟即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int t, n, m, a[MAXN], ind, ans;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		for(int i = 1;i <= n;i++){
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + n + 1); // 先排序
		ind = 1;
		ans = 0;
		for(int i = 1;i < n;i++){
			if(a[i + 1] - a[i] > m){
				ans = max(ans, i - ind + 1); // 求出每一个段的长度并更新最大值
				ind = i + 1;
			}
		}
		ans = max(ans, n - ind + 1); // 注意最后一个段的长度也要更新
		printf("%d\n", n - ans);
	}
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目大意】**

给你一个序列 $a$ 和整数 $k$，要求你删去一些数字后重排序列使得任意两个相邻整数的绝对值的差不超过 $k$，问最少删掉多少个数。

**【题目分析】**

首先常见的 trick 是，要让相邻的整数的差的绝对值的最大值最小，策略是将序列排序。又发现排好序后，合法的答案一定是连续的区间，因为若 $a_j - a_i > k(j > i)$，那么对于所有的 $p > j$ 一定都有 $a_p - a_i > k$，都不合法。

所以我们顺序向后遍历，每次遇到 $a_{i+1} - a_i > k$ 就将答案清零，最后把所有答案取 $\max$ 即可得到答案。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[500005],k;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> k;int ans = 1,mx = 0;
        for(int i = 1;i <= n;i ++) cin >> a[i];
        if(n == 1) {cout << 0 << "\n";continue;}
        sort(a+1,a+n+1);
        for(int i = 2;i <= n;i ++){
            if(a[i] - a[i-1] <= k) ans ++,mx = max(ans,mx);
            else mx = max(ans,mx),ans = 1;
        }
        cout << n - mx << "\n";
    }
}
```

---

## 作者：Phartial (赞：0)

赛时想复杂了，不过还是说一下我的思路吧。

显然升序排列 $a$ 是最优的选择，证明可以考虑邻项交换法。

对 $a$ 升序排序后，考虑使用一个栈维护当前保留的序列，按顺序加入一个元素 $a_i$ 时，我们将其和当前栈的栈顶 $a_t$ 比较：

- $a_i-a_t\le k$：直接将 $a_i$ 压栈即可；
- $a_i-a_t> k$：此时我们有两种选择：
	- 丢弃 $a_i$：由于我们是升序排序，对 $i<j\le n$，都有 $a_j-a_t>k$，我们肯定要将 $a_j$ 全部丢弃（如果在某个 $j$ 我们选择丢弃 $a_t$，那方案必定劣于 在一开始就不选择丢弃 $a_i$，而是丢弃 $a_t$），对于这种情况，我们可以直接算出最终的答案；
   - 丢弃 $a_t$：同上，我们肯定需要丢弃整个栈，清空栈后将 $a_i$ 压栈即可。
   
时间复杂度 $\mathcal{O}(n\log n)$，实现时可以记录当前丢弃的数的数量 $c$。

```cpp
#include <algorithm>
#include <iostream>
 
using namespace std;
 
const int kN = 2e5 + 1;
 
int tt, n, k, a[kN], q[kN], t, ans, c;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--;) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    t = 0, ans = 1e9, c = 0;
    for (int i = 1; i <= n; ++i) {
       if (!t || a[i] - a[q[t]] <= k) {
        q[++t] = i;
       } else {
        ans = min(ans, c + n - i + 1);
        c += t, t = 0, q[++t] = i;
       }
    }
    cout << min(ans, c) << '\n';
  }
  return 0;
}
```


---

## 作者：Zaku (赞：0)

### $\mathrm{Problem:}$
给定长为 $n$ 的数列 $a$ 和整数 $k$，可以任意删除数列中的数或任意排列数列，问：要使得排列后连续两个数的绝对差都小于 $k$，最少删除多少个数？

### $\mathrm{Sol:}$
不难想到要使操作数最小，必须升序排序。

然后我们观察样例，发现有些样例是删除前面，也有些样例是删除后面，所以单纯模拟是行不通的。所以需要逆向地做。

我们发现，最后剩余的数列，不就是最长的，前后两项差值不大于 $k$ 的子数组吗！所以可以求出这个东西的长度，$n$ 减去它即为答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
int f(int n, int k) {
    int ans = 0, cnt = 1;
    for (int i = 2; i <= n; i ++ ){
        if (a[i] - a[i - 1] <= k)
            cnt ++;
        else {
            ans = max(ans, cnt);
            cnt = 1;
        }
    }
    ans = max(ans, cnt);
    return ans;
}
int main() {
    int T;
    cin >> T;
    while (T -- ){
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i ++ )
            cin >> a[i];
        sort(a + 1, a + 1 + n);
        cout << n - f(n, k) << endl;
    }
    return 0;
}

```

---

## 作者：zct_sky (赞：0)

### Description:
-----
您有 $n$ 道题目，构成了一个题目列表，第 $i$ 道题有一个难度值 $a_i$。

您可以对该列表进行以下操作：

- 删除几道题目。
- 任意排列剩余题目。

当且仅当剩余题目列表中任意两道相邻题目 $i,i+1$ 满足 $\left| a_i - a_{i+1} \right| \le k$ 时，该题目列表被称为是“平衡的”。

求使得原题目列表变为“平衡的”最小要删去几道题目。

该题有多组数据。
### Solution:
-----
我们可以对原题目列表进行排序，使得相邻题目难度值的差最小。

然后找出列表中最长“平衡的”列表，易证该列表在排序后的原列表中一定是连续的。

最后删去题目数即为原列表长度减去最长“平衡的”列表长度。

特别的，对于 $n=1$ 时，应输出 $0$。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int N=2e5+7;
int n,a[N],k; 
ll t;
int main(){
	t=read();
	while(t--){
		n=read();k=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		if(n==1){
			puts("0");
			continue;
		}
		sort(a+1,a+1+n);
		int len=1,ans=0;
		for(int i=2;i<=n;i++){
			if(a[i]-a[i-1]>k){
				ans=max(ans,len);
				len=1;
			}else len++;
		}
		ans=max(ans,len);
		printf("%d\n",n-ans);
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1850D)

## 思路

可以用贪心的思想做此题。

读入数组后排序找相邻的两个数相差大于 $k$ 的计数。如果相邻的两个数之差不大于 $k$，取此时计数器和以前计数器最大值最大的计入 $ans$ 变量，计数器归一。判断完后有可能相邻的两数之差都不大于 $k$，此时**还要再判断一次最大值**，输出。

- 有多组测试数据，记得清空数组和标记变量等。

- 记得给计数器赋初始值为 $1$，因为第 $1$ 个数前面没有数了，差是小于 $k$ 的。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,a[N];
inline void solve(){
	int ans=-1e9,cnt=1;//cnt 就是前面提到的计数器。
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	sort(a+1,a+1+n);
	for(int i=2;i<=n;++i){
		if(a[i]-a[i-1]>k){
			ans=max(ans,cnt);
			cnt=1;
		}
		else ++cnt;	
	}
	ans=max(ans,cnt);
	printf("%d\n",n-ans);//别忘用 n 减和输出换行。
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/116998541)

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1850D)    
## 题意  
给你一个数列 $a$，第 $i$ 项为 $a_i$。     
现在可以任意重排列这个数列，也可以任意删除数字，求如果要使 $\forall i\in[2,n]$ 有 $\left|a_i-a_{i-1}\right|\le k$ 需要删除的最小数字个数。$n$ 为数列在经过操作后的数字个数。      
## 解法
因为相邻两项之差不能大于 $k$，所以我们需要最小化相邻两项之差，容易想到先排序。     
这样，这个数列被分成了几个段，这些段都满足条件，而两个相邻段合并起来无法满足。    
那么，这道题又转化成：保留一个段，使剩下被删除的数的数量最小。       
容易想到保留最长段，我们扫一遍记录答案即可。     
[CODE](https://www.luogu.com.cn/paste/ig4qsr54)

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1850D)

这题挺简单的。我们排序肯定从小到大或从大到小排序，这样子才能使相邻两个数的差值最小，使差值小于等于 $k$ 的地方最多。接下来我们遍历整个序列，统计一下其中所有符合连续相邻元素差值小于等于 $k$ 的子序列的长度，最后我们找到最长的长度，用序列总长 $n$ 去减就好了。

为什么要找这样的一个连续相邻元素差值小于等于 $k$ 的子序列的长度？因为每一段这样的子序列都是删除完别的元素后所留下的序列的可能性，我们要使删去的元素最少，那么就要使这样的序列长度最大，最后用 $n$ 去减就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,k,a[200010],v[200010],m=1,ans=999999999;
		scanf("%d%d",&n,&k);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		v[m]=1;
		for(register int i=2;i<=n;i++)
			if(abs(a[i]-a[i-1])>k) m++,v[m]=1;
			else v[m]++;
		for(register int i=1;i<=m;i++) ans=min(ans,n-v[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

