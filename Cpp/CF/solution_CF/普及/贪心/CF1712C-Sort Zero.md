# Sort Zero

## 题目描述

An array is sorted if it has no inversions

A Young Boy



You are given an array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ .

In one operation you do the following:

1. Choose any integer $ x $ .
2. For all $ i $ such that $ a_i = x $ , do $ a_i := 0 $ (assign $ 0 $ to $ a_i $ ).

Find the minimum number of operations required to sort the array in non-decreasing order.

## 说明/提示

In the first test case, you can choose $ x = 3 $ for the operation, the resulting array is $ [0, 0, 2] $ .

In the second test case, you can choose $ x = 1 $ for the first operation and $ x = 3 $ for the second operation, the resulting array is $ [0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
5
3
3 3 2
4
1 3 1 3
5
4 1 5 3 2
4
2 4 1 2
1
1```

### 输出

```
1
2
4
3
0```

# 题解

## 作者：LKY928261 (赞：10)

## 简化题意

给定一个正整数列 $a_1,a_2,\dots,a_n$，每次操作选择一个正整数 $x$，使数列中所有满足 $a_i=x$ 的元素都变为 $0$，求使数列单调不降所需的最小操作次数。

## 题目分析

因为原数列中的元素均为正整数，所以 $0$ 是操作后整个数列中的最小值。

而题目要求通过若干次操作使数列单调不降，即 $\forall 1\le i<n,a_i\le a_{i+1}$。

因此在操作结束后，数列的形态为 $0,0,\dots,0,a_k,a_{k+1},\dots,a_{n-1},a_n$，其中 $a_k,\dots,a_n$ 未被改变过且单调不降。

显然，若在某次操作中 $a_k$ 被改为了 $0$，那么在后续的操作中，必须把 $a_1,\dots,a_{k-1}$ 的值均改为 $0$。如果存在 $i(1\le i<n)$ 使得 $a_i>a_{i+1}$，则 $a_1,\dots,a_i$ 均需设为 $0$。

为了使序列单调不降，最长不降后缀之前的元素必定会在某一时刻被更改。

在程序中，设 $t$ 为需要更新为 $0$ 的最后一个位置。开始时将 $t$ 设为最长不降后缀的起始位置的前一元素。每次操作，若需要更改 $t$ 以后的位置，则更新 $t$ 的值。如此不断循环直到不用继续更新为止。

由于 $1\le a_i\le n$，值域较小，直接开数组记录每个可能的 $x$ 所能改变的最后一个元素的下标即可。

## 参考代码

~~参考代码仅供参考(bushi)~~

以下是 赛时代码 + 码风优化 + 注释。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,t,ans,a[100005],nxt[100005],i;bool f[100005];
//a保存原数组，nxt记录最后一个被改变的元素下标，f记录该数是否已被改变过
void work(){
	cin>>n;
	for(i=1;i<=n;i++)nxt[i]=f[i]=0;//多测记得初始化
	for(i=1;i<=n;i++){
		cin>>a[i];
		nxt[a[i]]=max(nxt[a[i]],i);//记录a[i]对应值的最晚出现的下标
	}
	for(i=n;i>1;i--)if(a[i]<a[i-1])break;//找第一个不满足单调性的数
	t=i-1;ans=0;
	for(i=1;i<=t;i++){//从头开始枚举
		ans+=(!f[a[i]]);//若没有标记过则操作次数+1
		f[a[i]]=1;//添加标记
		t=max(t,nxt[a[i]]);//更新枚举次数
	}
	cout<<ans<<'\n';
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;while(T--)work();
}
```

---

## 作者：Hovery (赞：6)

## Problem

[Sort Zero](https://www.luogu.com.cn/problem/CF1712C)

## Sol

首先从答案开始考虑，一定是一些 $0$ （或没有）加上一段不下降的序列。

那我们为什么不把后面一段不下降的序列求出来呢？

我们先求出最长的后缀，使其满足不下降。

之后将前面的所有数都变为 $0$。

$3\ 5\ 1\ 2\ 3$

对于上面这一串数，显然后缀为 $1\ 2\ 3$。

按照我们刚刚的做法，我们要将第一个 $3$ 变为 $0$，根据题目要求，那么最后一个 $3$ 也要变为 $0$。

显然是不满足单调的。

那么要使它变成单调，我们需要把 $2\ 1$ 给删除（这里 $2\ 1$ 也是删的顺序）。

对于最后面的单调的序列，若一个数要被删，就给它赋为 $1$ 否则为 $0$ 。

那么 $1\ 2\ 3$ 就可以变成 $1\ 1\ 0$。

接下来的问题就变成了，给你一个由 $0$ 和 $1$ 组成的序列，可以将 $1$ 变成 $0$ ，问：使这个序列变成单调最少要多少次操作。

还是考虑 $1\ 1\ 0$。

从前往后做不大好判断，那就从后往前做。

若一个 $1$ 的右边为 $0$ 就把它变成 $0$。

对于统计答案，就把最长的后缀需要的操作次数加上把前面所有数变成 $0$ 的操作次数即可。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int> 
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

int n, vis[100010], sum, ans, p, a[100010];

void solve()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	cin >> a[i], vis[a[i]] = 0;
	int p = 1, ans = 0, sum = 0;
	for (int i = 1;i <= n;i++)
	{
		if (!vis[a[i]])
		sum++;
		vis[a[i]] = 1;
	}
	for (int i = 1;i <= n;i++)
	vis[a[i]] = 0;
	for (int i = n - 1;i >= 1;i--)
	if (a[i] > a[i + 1])
	{
		p = i + 1;
		break;
	}
	for (int i = 1;i < p;i++)
	{
		if (!vis[a[i]])
		ans++;
		vis[a[i]] = 1;
	}
	for (int i = n;i > p;i--)
	{
		if ((vis[a[i - 1]] ^ 1) > (vis[a[i]] ^ 1))
		{
			ans++;
			vis[a[i - 1]] = 1;
		}
	}
	cout << ans << endl;
}

signed main()
{
	IOS;
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：ran_qwq (赞：6)

本蒟蒻第一次过掉 CF 的 C 题，写篇题解纪念一下。

如果消除 $x$ 次可以，那么消除 $x+1$ 次肯定可以，所以消除 $x$ 次可不可以满足单调性。

而要求的是最小消除多少次，所以可以用**二分答案**来解决这个问题。

因为要让序列单调不降，所以尽量把前面的变为 $0$。消除 $x$ 次就是把第一次出现时间在所有数中排前 $x$ 的数全部消除。然后再判断数列是否单调。

最小可能要消除 $0$ 次，这个序列共有 $x$ 种数，最多就要消除 $x$ 次。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,a[N],b[N],d[N];
vector<int> v[N];//v 记录每一个数出现的位置，把二分时间复杂度从 O(n^2) 降为 O(n)
bool check(int x)
{
	for(int i=1;i<=n;i++)
		d[i]=1,v[i].clear();
	for(int i=1;i<=n;i++)
		v[a[i]].push_back(i);
	for(int i=1,cnt=0;cnt<x;i++)
		if(d[i])
		{
			cnt++,d[i]=0;
			int len=v[a[i]].size();
			for(int j=0;j<len;j++)
				d[v[a[i]][j]]=0;
		}
	for(int i=1;i<=n;i++)
		if(a[i]*d[i]<a[i-1]*d[i-1])
			return 0;
	return 1;
}
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			b[i]=0;
		for(int i=1;i<=n;i++)
			a[i]=read(),b[a[i]]=1;
		int l=0,r=0;
		for(int i=1;i<=n;i++)
			if(b[i])
				r++;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(check(mid))
				r=mid-1;
			else
				l=mid+1;
		}
		printf("%d\n",l);
	}
	return 0;
}
```


---

## 作者：hanyuchen2019 (赞：1)

$1158$ 分，以此题解纪念第一次 CF Div.2 过 $3$ 题。

### part 1 思路

本题的关键在于“连锁反应”。

如：

```
7
3 2 4 3 6 4 7
```

首先，$a_1>a_2$，所以执行操作将所有 $3$ 改为 $0$。

```
0 2 4 0 6 4 7
```

但是，$a_1$ 的修改牵扯到了 $a_4$，这导致了 $a_2$ 与 $a_3$ 都需要修改为 $0$。

```
0 0 0 0 6 0 7
```

最后把 $a_5$ 改为 $0$，变为 `0 0 0 0 0 0 7`。

在以上操作中，我们不难得出一些结论：

1. 如果 $a_i=0$，则 $a_1=a_2=\dots=a_{i-1}=0$。
2. 执行完这些操作后的序列的形式一定为：

$$0,0,0,\dots,0,a_k,a_{k+1},\dots,a_n$$

其中 $a_k \le a_{k+1} \le \dots \le a_n$。

（写的不太严谨勿喷）

#### 于是本题的思路：

* 定义 `gg[i]` 表示数字 $i$ 有没有被修改为 $0$；
* 定义 `l[i]` 表示数字 $i$ 最后一次出现的位置；
* 从头到尾找逆序对，并把 `l[i]` 及之前的所有数修改为 $0$（连锁反应）。

### part 2 Code

赛时代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int r()//快读，略
int a[100005],l[100005];
bool gg[100005];
int main()
{
	int t=r(),n;
	while(t--)
	{
		memset(gg,0,sizeof gg);
		memset(l,0,sizeof l);
		n=r();
		for(int i=1;i<=n;++i)a[i]=r(),l[a[i]]=i;
		int lst=0,ans=0;
		for(int i=1;i<n;++i)
		{
			if(gg[a[i]])a[i]=0;
			if(a[i+1]<a[i])
			{
				int ri=i;
				for(int j=lst+1;j<=ri&&j<=n;++j)
				{
					if(!gg[a[j]])
						gg[a[j]]=1,ans++,ri=max(ri,l[a[j]]);
				}
				lst=ri;//优化，从第一个没有置0的数开始
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：孤芒星河233 (赞：0)

# CF1712C Sort Zero

[洛谷题面](https://www.luogu.com.cn/problem/CF1712C)

[CF原题面](http://codeforces.com/problemset/problem/1712/C)

## 题意

  有 $T$ 组数据，每组数据给出一个正整数 $n$ 和 $n$ 个正整数 $a_1,a_2,\cdots ,a_n$ ，这 $n$ 个正整数形成一个 $1$ 到 $n$ 的排列。你可以任意把其中一个正整数 $x$ 变为 $0$。求数组 $a$ 变为**不降序列**的最小操作次数。

  数据范围：$1\leq T\leq 10^4 ,1\leq n\leq 10^5 ,1\leq a_i\leq n$

## 思路

  因为要满足 $\forall i,a_{i-1}\leq a_i$，所以出现 $a_{i-1}>a_i$ 时，需要把 $a_{i-1}$ 变为 $0$，而在 $a_{i-1}$ 以前的数也会因此变为 $0$。我们只需要维护一个不下降的序列，每当出现一个数 $x$ 小于序列中最后一个数，就把序列中所有数变为 $0$，标记一下变为 $0$ 的数，**排空序列**防止重复遍历，最后加入 $x$。最后从 $1$ 到 $n$ 遍历，统计被标记数的个数。这样保证时间复杂度为 $O(Tn)$

## 代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  const int N=1e5+9;
  int T,n,a[N];
  bool vis[N];//记录变为0的数
  
  int main(){
      scanf("%d",&T);
      while(T--){
          scanf("%d",&n);
          int tot=0,x,ans=0;
          for(int i=1;i<=n;i++){
              scanf("%d",&x);
              if(vis[x]) x=0;//之前变为0的数，在读入时直接修改为0
              if(tot>0&&a[tot]>x){
                  while(tot>0){
                      vis[a[tot]]=1;
                      tot--;
                  }
              }
              a[++tot]=x;
          }
          for(int i=1;i<=n;i++){
              if(vis[i]) ans++;//统计答案
          }
          printf("%d\n",ans);
          for(int i=0;i<=n;i++) a[i]=vis[i]=0;
      }
      return 0;
  }
  ```

---

## 作者：GI录像机 (赞：0)

## 思路：

考虑正着扫一遍，一旦发现 $a_{i-1}>a_i$，显然应该把 $a_{i-1}$ 变为零，使序列维持顺序。前面的所有数也应该 $\le0$，因此要将前面的所有数也改为零。我用的是 map 和队列维护（这俩东西实际上是在模拟布尔数组和双指针）。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), n, a[N];
signed main() {
	while (t--) {
		int ans = 0;
		n = read();
		for (int i = 1; i <= n; i++)a[i] = read();
		queue<int>q;
		q.push(a[1]);
		map<int, bool>mp;
		for (int i = 2; i <= n; i++) {
			if (mp[a[i]])a[i] = (1 - 1) * 4514;
			if (a[i] < a[i - 1]) {
				while (!q.empty()) {
					if(!mp[q.front()])ans++;
					mp[q.front()] = 1;
					q.pop();
				}
				if (mp[a[i]])a[i] = 0;
			}
			if(a[i])q.push(a[i]);
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：cachejtt (赞：0)

## 题意
给你一个序列，可以进行若干次操作。每次操作，选定一个数 $x$，把所有 $a_i=x$ 的数赋值为 $0$。问你把序列变为单调不降序列，至少需要多少次操作。
## 思路
从前往后搜，若当前这个数已不满足单调不降，则把上一次推平的地方到现在全部数都推平，并打上标记，并更新推平的地方。

最后统计有几个数被打上了标记，即为答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ms(x, i) memset((x),(i),sizeof x)
#define endl "\n"
using namespace std;
int t=1,n,a[100005],vis[100005],sum,lst;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    sum=0;
    ms(vis,0);
    rep(i,1,n){
      cin>>a[i];
    }
    lst=1;
    rep(i,2,n){
      if(vis[a[i]]==1)a[i]=0;
      if(vis[a[i-1]]==1)a[i-1]=0;
      if(a[i]<a[i-1]){
        rep(j,lst,i-1){
          vis[a[j]]=1;
          a[j]=0;
        }
        lst=i;
      }
    }
    rep(i,1,100002){
      if(vis[i]==1)sum++;
    }
    cout<<sum<<endl;
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

我们可以发现，最后得出的数列，肯定是前一大段 $0$，后面一个不下降数列。

那么，我们可以首先看看，原数列的所有不下降的后缀中，最长的那个。

既然已经找出了这个不下降后缀，前面的所有数都要删除了。

但是，我们还要记录每个数字最右边出现的地方。

删除前面的数时，我们还要留意它们有没有对后面的数造成影响。如果有影响，被影响的数和前面的所有数都要一并删除。

模拟即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 100000
int t;
int n;
int a[max_n+2];
int r[max_n+2];
int ansr;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712C_1.in","r",stdin);
	freopen("CF1712C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	a[0]=0;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		memset(r,0,sizeof(r));
		for(int i=1;i<=n;++i)r[a[i]]=i;
		ansr=n;
		while(ansr>1&&a[ansr-1]<=a[ansr])--ansr;
		for(int i=1;i<ansr;++i)ansr=max(ansr,r[a[i]]+1);
		sort(a+1,a+ansr);
		ans=0;
		for(int i=1;i<ansr;++i){
			if(a[i-1]^a[i])++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727158)

By **dengziyue**

---

## 作者：luo_shen (赞：0)

**题意**  
给定一个序列 $p$，可以将序列中的一些元素变为 $0$，求使变换后的序列 $p'$ 为不下降序列的最小变换次数。  
**分析**  
记元素 $a_i$ 最后出现的位置为 $mx_{a_i}$。若将 $i$ 的元素 $a_i$ 变为 $0$，则所有 $j\le i$ 的元素 $a_j$ 都需要变为 $0$。所以可以统计到 $i$ 为止的元素数量，及若 $1-i$ 的元素变为 $0$，整个序列需要变为 $0$ 的截止位置（详情见代码）。  
**代码**  
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100100],mx[100100],b[100100];
int main(){
    cin>>t;
    while(t--){
        memset(mx,0,sizeof(mx));
        memset(b,0,sizeof(b));
        cin>>n;
        a[n+1]=n+1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            mx[a[i]]=max(mx[a[i]],i);//统计每个元素最后出现的位置
        }
        int end=0,ans=0,sum=0,maxi=0;//end表示清零的结束位置，ans表示最少需要变成0的元素个数
        							//sum表示到i为止总共的不同元素的个数，maxi表示到i为止所有元素最后出现位置的最大值
        for(int i=1;i<=n;i++){
            if(!b[a[i]]){
                sum++;
                b[a[i]]=1;
                maxi=max(maxi,mx[a[i]]);
            }//若该元素未出现过，则统计不同元素个数及所有元素最后出现的位置
            if(a[i]>a[i+1]){
                end=maxi;
            }//若出现了降序列，则1-maxi的所有元素都要变为0
            else if(end>i){
                end=maxi;//维护结束位置
            }
            if(i==end){//到达结束位置，统计变为0的元素个数
                ans=sum;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：BorisDimitri (赞：0)

## 题意
给出一个长为 $n$ 的序列 $a$，每一次操作可以选择一个数 $x$，将 $a$ 中的所有等于 $x$ 的数变为 $0$，求将序列变成不下降序列所需要的最少操作次数。

## 思路
我们发现，一旦出现了 $a_i > a_{i+1}$，那么我们就要将下标为 $1 \sim i$ 的数都变成 $0$。

**Proof:**
> 如果只是将 $a_i$ 变为 $0$，由于原序列中所有数都是大于 $0$ 的，所以如果 $a_{i-1} \ne 0$，就有 $a_{i-1} > a_i$。
>
> 如此类推，下标为 $1 \sim i$ 的数都一定为 $0$。

所以我们只要用 set 维护 $1 \sim i$ 值的个数，如果出现 $a_i > a_{i+1}$，就将 $1 \sim i$ 中的所有值标记为 $0$，答案更新为 $1 \sim i$ 中值的个数即可。

## Code
```cpp
const int N = 1e5 + 10;

int n;
int a[N];
bool st[N];

int main()
{
	int t = 1;
	cin>>t;

	while(t--) 
	{
		scanf("%d",&n);
		for(int i=0;i<=n;i++) st[i] = 0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		
		int ans = 0, last = 0;
		set<int> S;
		for(int i=1;i<n;i++)
		{
			if(st[a[i]]) a[i] = 0;
			if(st[a[i+1]]) a[i+1] = 0;
			if(a[i] != 0) S.insert(a[i]);
			
			if(a[i] > a[i+1])
			{
				for(int j=last;j<=i;j++) st[a[j]] = 1;
				last = i;
				ans = S.size();
			}
		}
		
		cout<<ans<<endl;
	}

    return 0;
}
```

---

## 作者：YYHDoggy (赞：0)

## 题意简述

给定一个长度为 $n$ 的数列 $\{a_n\}$。

单次操作可以：
 
- 选择任意整数 $x$
- 将数列中**所有**等于 $x$ 的项均赋值为 $0$

要求求出使该数列变为单调不减数列（$a_i \leq a_{i+1}$）的最小操作数。

初始时所有 $a_i \in [1,n]$。

## Solution

首先，不难看出，从后往前看，如果某一个点比它后面的数要大，就必须把它之前的数全部置 $0$。

> 因为使 $a_i$ 减小的唯一方法就是将其置 $0$，而由于所有 $a_i$ 均为正数，为了满足单调不减的性质，必须将其前面的元素一起置 $0$。

如果这题没有“单次必须对所有等于 $x$ 的项操作”这一项性质，那么这道题已经结束了：只需求出从后往前第几个元素比后一项元素大即可。

然而这道题确实存在这样一项性质，并且对解题产生了影响。考虑样例第 $2$ 组：
```
4
1 3 1 3
```
在这组样例中，从后开始数，第一个打破单调不增性质的元素显然是第 $2$ 项：$3$。然而将该项置 $0$ 会使得第 $4$ 项同时被置 $0$，迫使第 $4$ 项之前的所有数也必须置 $0$。

由此大约就能想到此题的解法：从后向前遍历，同时记录从第几个数开始，前面的数必须全部置 $0$。

不妨将上面出现的这个数记为 $del$。因此，我们可以在读入数据时维护一个 `lst` 数组，记录每个数最后出现的位置。只需要递归维护  
$$del = \max_{i=1}^n\{lst_i\}\ (\text{第}\ i \ \text{个或其后某个元素不符合单调不减性质})$$ 
即可。

求出 $del$ 以后就是将其前面所有数删除。

如何保证每个数只被删一次？`lst` 数组记录每个数最后出现的位置，可以规定如果 $lst_i$ 为 $0$ 即代表这个数没有出现过。于是在删掉一个数的同时，将 $lst_i$ 赋值为 $0$ 即可。

下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 100007
using namespace std;
int t,n,a[MAXN],lst[MAXN];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)lst[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            lst[a[i]]=i;
        }
        int del=0,pre=10000007;
        for(int i=n;i>=1;i--){
            if(a[i]>pre){
                del=max(del,lst[a[i]]);
            }
            else{
                pre=a[i];
            }
        }
        int ans=0;
        for(int i=1;i<=del;i++){
            if(lst[a[i]]){
                ans++;
                lst[a[i]]=0;
            }
        }
        printf("%d\n",ans);
    }
return 0;}
```

---

## 作者：fast_photon (赞：0)

**0. 前言**  
这场比赛可能是最惨的一次了  
A 00:06 B 00:11 C 00:24 D -7 。。。  

**1. 分析**  
题目要求最后变成**单调不降**的数组。  
很显然，如果对于任意的 $1\le i<n$ 有 $a_i\le a_{i+1}$ 就满足要求了。  
如果本来存在 $a_i<a_{i+1}$，但是后来因为某种原因导致所有和 $a_{i+1}$ 相等的都赋为 $0$，那么就需要再考虑一次 $a_i$ 和 $a_{i+1}$ 这对数。不难发现，**只需要从大到小判断每个数值是否应该被赋为 $0$** 就可以了。（证明甩在后面）  
我们又发现，$a_i$ 的值域是 $[1,n]$，那么又可以省去离散化了。  
只需要从大到小枚举每个可能的值 $k$，然后判断对于 $a_i=k$ 是否满足 $a_i\le a_{i+1}$ 如果不满足，那么记录一下，跳出循环，然后再把每个 $a_i=k$ 赋值为 $0$。  
**但是这里有一个坑。** 正常程序在数组最后一个元素后面一定存着一个 $0$，但是实际上是不需要考虑这个 $0$ 的，所以要特判一下。也就是说判断是否满足的时候要避开最后一个元素，**但是赋值的时候不要**。  

然后就是轻松愉快的证明了。  
假设数组里的元素从大到小排序再去重得到的结果是 $k_1,k_2,\dots,k_m$。  
那么对于每个 $k$ 只有赋值和不赋值两种选择。  
假设当前已经进行过了前 $j$ 个 $k$ 的选择，我们来到了第 $j+1$ 个。如果我们不执行操作，并且存在一个相邻数的逆序对（很显然靠左的那个等于 $k_{j+1}$，因为另一情况已经在枚举前 $j$ 个 $k$ 的时候判断过了。），那么就会出现矛盾。因为无论以后怎么操作靠右的那个数肯定只会不变或者变成 $0$，这个逆序对就永远存在了，不合题意，因而必须执行操作。  

反之，如果没有一个相邻数的逆序对其中靠左的是 $k_{j+1}$，那么就无需执行操作，显然对于任意的 $a_i=k_{j+1}$ 此时满足 $a_i\le a_{i+1}$（$i=n$ 除外），那么 $a_{i+1}$ 由于已经枚举过了（或者等于 $a_i$），则永远不会被赋值，不会制造一个逆序对。  

**2. 代码**  
实际上可以用 `vector` 记录一个值的每次出现的下标，枚举的时候直接遍历 `vector`，由于每个数最多遍历 $2$ 次（判断一次，赋值一次）故不超时。  
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define maxn 100005

using namespace std;

int t, n, a[maxn];
bool z[maxn];

vector<int> g[maxn];

int main() {
	cin >> t;
	while(t--) {
		int ans = 0;
		memset(z, 0, sizeof(z));
		cin >> n;
		for(int i = 1; i <= n; i++) {
			g[i].clear();
		}
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			g[a[i]].push_back(i);
		}
		for(int i = n; i >= 1; i--) {
			for(int j : g[i]) {
				if((a[j] > a[j + 1] || z[a[j + 1]] == 1) && j != n - 1) {
					z[i] = true;
					ans++;
					break;
				}
			} 
		}
		cout << ans << endl;
	}
}  
```

---

## 作者：LazYQwQ (赞：0)

## 题意简述
- 给出一个正整数 $t$ 代表数据组数。

- 对于每一组数据给定一个长度为 $n$ 的序列。

- 在一次操作中可以挑选一个整数 $x$, 将序列中所有的 $x$ 修改为 $0$。

- 求出最少操作数使序列为不下降序列。

## 解题思路
0. 预设 $pos$ 为开始修改为 $0$ 的位置。

1. 若要求序列为不下降序列，则最后一项应为最大值，故在读入后从后往前遍历一遍，若数据较自己的后一位更大，则准备将数值修改为 $0$，再往前的数值也将修改。

2. 注意到修改时会将所有指定的数值修改为 $0$，所以即使某一位置上的数小于或等于后面的每一个数，但该数的数值被标记为待修改，则也不满足条件。

3. 可以看出若一个数值在之前出现过且上次出现该数值的位置与当前位置不相邻则该数值一定会被修改。

4. 因此我们用 $a$ 数组存储数值是否被打上标记，找到第一个不满足本身符合规律或数值被修改的位置，并统计在此之前有多少的不同数值并输出统计结果即可。

## 参考代码如下
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n;
		int a[100010];
		int bef[100010];
		int from[100010]; 
		memset(a,0,sizeof(a));
		memset(bef,0,sizeof(bef));
		memset(from,0,sizeof(from));
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			from[i]=bef[a[i]]; 
			bef[a[i]]=i;
		}
		long long num=0,pos=n;
		long long now=1e9;
		for(int i=n;i>=1;i--)
		{
			if(a[i]>now)break;
			if(i-from[i]>1 and from[i]!=0)break;
			now=a[i];
			pos--;
		}
		bool f[100010];
		memset(f,0,sizeof(f));
		for(int i=1;i<=pos;i++)
		{
			if(!f[a[i]])
			{
				f[a[i]]=1;
				num++;
			}
		}
		cout<<num;
		printf("\n");
	}
	return 0;
} 
```


---

## 作者：Scorilon (赞：0)

给定一个长度为 $n$ 的序列，定义一个操作：每次选择一个数 $x$，将这个序列中所有值为 $x$ 的更改为 $0$。问改变为一个非递减序列的最小操作数。

思路与其他人略有不同，基本上是根据题意模拟。

每次操作从后往前扫，找到最后一个递减序列的位置，然后将这个位置 $i$ 即 $1 \sim i$ 位置上的数都更改为 $0$，每次操作过后，要将整个数组后的数字即每次更改的 $x$ 全部更改为 $0$。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int t;
int n;
int a[100005];
bool cnt[100005];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
		}
		int ans=0;
		while(1) {
			int i;
			for(i=n;i>=2;i--) {
				if(a[i]<a[i-1]) break;
			}
			i--;
			if(i==0) break;
			for(int j=1;j<=i;j++) {
				if(!cnt[a[j]]&&a[j]!=0) {
					ans++;
					cnt[a[j]]=true;
				}
				a[j]=0;
			}
			for(int j=i+1;j<=n;j++) {
				if(cnt[a[j]]) a[j]=0;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：ztlh (赞：0)

**题意**：给定 $n$ 个**正整数** $a_1, a_2, ...,a_n$，每次操作可以任选一个正整数 $x$，并将所有 $a_i = x$ 赋值为 $0$。求将此序列变为**非严格单调递增**的**最小**操作次数。

**我的做法**：观察可知，如果 $a_i = a_k = x$ 且存在 $a_j \neq x$（$i < j < k$），则所有 $a_l$（$i \leq l \leq k$）及一切等于 $x$ 的项都会被置 $0$。

因此，只要逆序遍历，并开桶记录每个数字（值域不大）已经出现的次数（记为 $cnt1$）和总共出现的次数（记为 $cnt2$），直到满足以下两点之一便停止循环：

- $a_{i-1} > a_i$ 

- $a_{i-1} \neq a_i$ 且当前 $cnt1_{a_i} \neq cnt2_{a_i}$

将前面的数字删除即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[100005];
bool vis[100005];
int ans;
int cnt[100005];
int ncnt[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n); ans=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			cnt[i]=ncnt[i]=vis[i]=0;
		}
		for(int i=1;i<=n;i++) cnt[a[i]]++;
		int r;
		for(r=n;r>=1;r--){
			ncnt[a[r]]++;
			if(a[r-1]>a[r]) break;
			if(a[r-1]!=a[r]&&ncnt[a[r]]!=cnt[a[r]]) break;
		}
		for(int i=1;i<r;i++) vis[a[i]]=1;
		for(int i=1;i<=n;i++) ans+=vis[i];
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：qwq___qaq (赞：0)

一个比较有意思的思维题。

首先，容易想到，因为 $a_{i}>0$，所以说若 $i$ 被赋为 $0$，那么 $[1,i]$ 就会被赋为 $0$。

那么，我们可以记录一个数组 $r$，$r_i$ 表示 $a_i$ 最后一次出现的位置。然后记 $R$ 表示我们需要清空 $[1,R]$。

然后找到最右边的使序列拥有降序的位置 $i$，那么此时需要覆盖的区间是 $[1,r_i]$，但是这步之后还没有结束，因为容易发现，$\max\limits_{j=1}^{r_i}r_j\ge r_i$，也就是说，此时我们需要清空的区间转化为 $[1,\max\limits_{j=1}^{r_i}r_j]$。

注意到此时区间继续加长，那么可以 $R$ 就会一直往右跳，知道 $R=n$（此时不能往右跳）或 $\max\limits_{i=1}^Rr_i=R$（此时在原地跳）就结束。

那么我们就只需要模拟这个往右跳的过程即可，注意到所有的对于最大值的信息左端点都是 $1$，所以可以使用前缀 $\max$。

时间复杂度 $O(\sum n)$，注意 $r$ 需要动态清空。

---

