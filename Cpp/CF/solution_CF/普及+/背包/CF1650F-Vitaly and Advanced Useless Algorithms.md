# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly enrolled in the course Advanced Useless Algorithms. The course consists of $ n $ tasks. Vitaly calculated that he has $ a_i $ hours to do the task $ i $ from the day he enrolled in the course. That is, the deadline before the $ i $ -th task is $ a_i $ hours. The array $ a $ is sorted in ascending order, in other words, the job numbers correspond to the order in which the assignments are turned in.

Vitaly does everything conscientiously, so he wants to complete each task by $ 100 $ percent, or more. Initially, his completion rate for each task is $ 0 $ percent.

Vitaly has $ m $ training options, each option can be used not more than once. The $ i $ th option is characterized by three integers: $ e_i, t_i $ and $ p_i $ . If Vitaly uses the $ i $ th option, then after $ t_i $ hours (from the current moment) he will increase the progress of the task $ e_i $ by $ p_i $ percent.

For example, let Vitaly have $ 3 $ of tasks to complete. Let the array $ a $ have the form: $ a = [5, 7, 8] $ . Suppose Vitaly has $ 5 $ of options: $ [e_1=1, t_1=1, p_1=30] $ , $ [e_2=2, t_2=3, p_2=50] $ , $ [e_3=2, t_3=3, p_3=100] $ , $ [e_4=1, t_4=1, p_4=80] $ , $ [e_5=3, t_5=3, p_5=100] $ .

Then, if Vitaly prepares in the following way, he will be able to complete everything in time:

- Vitaly chooses the $ 4 $ -th option. Then in $ 1 $ hour, he will complete the $ 1 $ -st task at $ 80 $ percent. He still has $ 4 $ hours left before the deadline for the $ 1 $ -st task.
- Vitaly chooses the $ 3 $ -rd option. Then in $ 3 $ hours, he will complete the $ 2 $ -nd task in its entirety. He has another $ 1 $ hour left before the deadline for the $ 1 $ -st task and $ 4 $ hours left before the deadline for the $ 3 $ -rd task.
- Vitaly chooses the $ 1 $ -st option. Then after $ 1 $ hour, he will complete the $ 1 $ -st task for $ 110 $ percent, which means that he will complete the $ 1 $ -st task just in time for the deadline.
- Vitaly chooses the $ 5 $ -th option. He will complete the $ 3 $ -rd task for $ 2 $ hours, and after another $ 1 $ hour, Vitaly will complete the $ 3 $ -rd task in its entirety.

Thus, Vitaly has managed to complete the course completely and on time, using the $ 4 $ options.

Help Vitaly — print the options for Vitaly to complete the tasks in the correct order. Please note: each option can be used not more than once. If there are several possible answers, it is allowed to output any of them.

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100```

### 输出

```
-1
4
3 4 1 5 
1
1```

# 题解

## 作者：落海沉 (赞：5)

- 题目分析：

	 有 $n$ 个任务，每个任务有一些方案，每个方案可以完成这个任务的百分之几，当累计超过 $100$ 时，任务完成，记录最小时间，如果超出时间限制，输出 -1。
     
- 思路：**背包**

但我们得考虑到底什么事容量，分为两种：
   
   1. 以时间为容量，百分比为价值，好似不可行，因为首先时间大小范围达到了 $10^9$，肯定超空间，再者，价值只需要在 $100$ 到 $200$ 之间，过大没什么意义，所以不以时间为容量。
   
   2. 百分比为容量，时间为价值，那么容量为多大呢？经过计算为 $0$ 到 $199$。
   
证明：
    
   当前百分比之和小于 $100$，现在添加进来一个 $a_i$，和超过了 $100$，但绝不会超过 $200$，因为 $a_i\le100$，所以肯定小于 $200$，此刻就不需要再加了，否则一定不是更优，证毕！
    
   接上文那就是一个二维背包，记录方案，最短时间即为：
   $$dp_{i,j}=\min(dp_{i+1,j-p}+a_i,dp_{i,j})$$
   
   
   




所以贴代码啦：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
const int inf = 0x3f3f3f3f3f3f;
const int N = 1e5+5;
struct node {
	int id,ti,val,p;
} e[N];
int _,Case,n,m,w,t[N],dp[N][205],ans,cnt;
bool cmp(node a,node b) {
	return a.id<b.id;
}
vector<int> bag;
void solve() {
	cnt=0;
	bag.clear();
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>t[i];
	}
	for(int i=1; i<=m; i++) {
		e[i].p=i;
		cin>>e[i].id>>e[i].ti>>e[i].val;
	}
	sort(e+1,e+m+1,cmp);
	int lft=1,rgt;
	for(int i=0; i<m+2; i++) {
		for(int j=0; j<205; j++) {
			dp[i][j]=inf;
		}
	}
	for(int i=1; i<=m+1; i++) {
		dp[i][0]=0;
	}
	for(int i=1; i<=n; i++) {
		for(int j=lft; j<=m; j++) {
			if(e[lft].id!=e[j].id)break;
			else rgt=j;
		}
		for(int j=rgt; j>=lft; j--) {
			for(int k=200; k; k--) {
				dp[j][k]=dp[j+1][k];
				if(k>=e[j].val)dp[j][k]=min(dp[j+1][k-e[j].val]+e[j].ti,dp[j][k]);
			}
		}
		ans=inf;
		for(int i=1;i<=6;i++)
		for(int j=100; j<=200; j++) {
			if(ans>dp[lft][j]) {
				w=j;
				ans=dp[lft][j];
			}
		}
		cnt+=ans;
		if(cnt>t[i]) {
			cout<<"-1"<<endl;
			return ;
		}
		for(int j=lft; j<=rgt; j++) {
			if(w>=e[j].val&&dp[j][w]==dp[j+1][w-e[j].val]+e[j].ti) {
				w-=e[j].val;
				bag.push_back(e[j].p);
			}
		}
		lft=rgt+1;
	}
	cout<<bag.size()<<endl;
	for(int i=0; i<bag.size(); i++) {
		cout<<bag[i]<<" ";
	}
	cout<<endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>Case;
	for(_=1; _<=Case; _++)solve();
	return 0;
}
```


noip rp++


---

## 作者：qianqing (赞：3)

（~~很明显的一道背包题目~~）
### 思路
枚举任务，算出每个任务的最小完成时间（还要记录路径），然后判断是否在每个任务的规定时间内完成。
### 算出每个任务最小完成时间
- 类型：背包 dp，因为每个计划只能选择一次，所以是 01 背包。
- 定义：$dp[i][v]$ 表示在第 $i$ 个计划且这个任务的完成进度为 $v$ 时的最小时间。（因为时间的值的范围是 $10^9$，所以只能用任务完成进度作为 【背包的容量】。因为完成进度可能会超出 $100$，但是如果是一个已经完成的 dp 状态，那他就不用再加上另外的计划了，所以进度最多达到 $199$。还有注意这里枚举的计划只能是该任务的计划，这样时间复杂度就变成了 $O(m \times T)$，此处 $T$ 表示能达到的最大的进度。）
- 转移式：$dp[i][v]=\min(dp[i][v],dp[i-1][v-p[i]]+t[i])$（数组名称按照题目给定(代码中不是，这里只是便于理解)，这里是可以滚动数组的，只是要记得容量是倒着枚举，代码中用的就是滚动数组。（因为是 01 背包））
- 初始化：因为是 $\min$，所以 $dp[i][v]$ 赋值为 $0x3f3f3f3f$，而每个 $dp[i][0]$ 赋值为 0。
- 结果：枚举 $100$ 到 $199$ 的容量值（因为一定是要取完成的），取其中 $dp$ 的最小值。
### 记录路径
在转移 dp 的时候，若 $dp[i][v]>dp[i-1][v-p[i]]+t[i]$，那就代表要从 $v-p[i]$ 的状态转移，那就用数组 $q[v]$ 承接 $q[v-p[i]]$，再加上当前计划下标。最后让最终的路径加上每个任务选出的最优 dp 值的路径。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int t,n,m,a[N],s[N],w[N],x[N],f[N],num,d[210],mi,cnt,ans,p[N],poin,sum;
vector<int>q[210];
bool cmp(int x,int y)
{
	return s[x]<s[y];
}
inline void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>s[i]>>x[i]>>w[i],f[i]=i;
	sort(f+1,f+1+m,cmp);
	num=1,ans=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		for(int v=1;v<=199;v++)d[v]=0x3f3f3f3f;
		d[0]=0,mi=0x3f3f3f3f,cnt=0,poin=num;
		for(int v=0;v<=199;v++)q[v].clear();
		for(int v=num;v<=m&&s[f[v]]==s[f[poin]];v++,num++)
		{
			int it=f[v];
			for(int z=199;z>=w[it];z--)
			{
				if(d[z]>d[z-w[it]]+x[it])q[z]=q[z-w[it]],q[z].push_back(f[v]);
				d[z]=min(d[z],d[z-w[it]]+x[it]);
			}
		}
		for(int v=100;v<=199;v++)
			if(d[v]<mi)mi=d[v],cnt=v;
		if(mi+sum>a[i]){cout<<"-1\n";return;}
		sum+=mi;
		for(int v=0;v<q[cnt].size();v++)p[++ans]=q[cnt][v];
	}
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i++)cout<<p[i]<<" ";
	cout<<"\n";
}
signed main()
{
	cin>>t;
	while(t--)solve(); 
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

有一个显然的贪心结论，就是先完成任务截止时间考前的，若在前面的都无法完成，那么后面的更加不可能完成。题目十分良心，$a_i$ 已经在输入时升序给出。

对于每个任务，需要用尽可能少地耗时完成尽可能多的百分比，每个计划的状态均为选或不选，这不就是 $0-1$ 背包嘛。由于要输出方案，所以我们设二维状态，对于某个任务，设 $dp_{i,j}$ 表示该任务的前 $i$ 个计划完成的百分率为 $j$ 时的最小耗时，这里默认 $j > 100$ 时也表示成 $j = 100$ 的状态。所以可以写成方程 $dp_{i,j}(j \le [1,100]) = \min (dp_{i - 1,j},\min \{dp_{i - 1,j - p} + t\})$，其中有一个是继承上一次的状态。

对于每个任务的方案记录，直接从 $dp_{i,100}$ 进行还原，若 $dp_{i,j} ≠ dp_{i - 1,j}$ 则说明发生有效转移，记录此时的计划编号即可。用一个 `vector` 去记录会比较遍历，每一次 $dp$ 后将每个人物的方案汇总至总的方案数组即可。

思路不算复杂，不过需要注意 $dp$，方案记录数组的初始化以及无解的判断。代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define init(x) memset (x,INF,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
struct node
{
	int id,t,p;
};
int t,n,m,ok,sum,a[MAX],dp[MAX][105];
vector <int> ans,v;
vector <node> e[MAX];
int solve (int x);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();m = read ();ok = 1;sum = 0;ans.clear ();
		for (int i = 1;i <= n;++i) a[i] = read ();
		for (int i = 1;i <= m;++i) 
		{
			int x = read (),ti = read (),pi = read ();
			e[x].push_back ({i,ti,pi});
		}
		for (int i = 1;i <= n;++i)
		{
			int x = solve (i);
			if (x == -1 || sum + x > a[i]){ok = 0;break;}//时间不够
			sum += x;
			for (auto j : v) ans.push_back (j);//答案的汇总
		}
		if (!ok) puts ("-1");
		else
		{
			printf ("%d\n",ans.size ());
			for (auto i : ans) printf ("%d ",i);
			puts ("");
		}
		for (int i = 1;i <= n;++i) e[i].clear ();
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
int solve (int x)
{
	int k = e[x].size ();
	for (int i = 0;i <= k;++i)
		for (int j = 0;j <= 100;++j) dp[i][j] = INF;
	v.clear ();
	dp[0][0] = 0;//初始化
	for (int i = 1;i <= k;++i)
	{
		node nw = e[x][i - 1];//注意 vector 的下标存储
		for (int j = 100;~j;--j)
			dp[i][j] = min (dp[i][j],dp[i - 1][max (0,j - nw.p)] + nw.t),dp[i][j] = min (dp[i - 1][j],dp[i][j]);
	}
	if (dp[k][100] == INF) return -1;//无法完成任务
	int p = k,cnt = 100;
	while (p && cnt > 0)
	{
		if (dp[p][cnt] == dp[p - 1][cnt]) {--p;continue;}//说明并没有发生有效转移
		v.push_back (e[x][p - 1].id);//记录编号
		cnt -= e[x][p - 1].p;
		--p;
	}
	return dp[k][100];//最小时间
}
```

---

## 作者：littlebug (赞：1)

补背包 $5/48$。

卡在 01 背包的记录历史路径上了。

## Solution

首先思路很一眼，显然每个任务相互独立，那么分别 01 背包求出来消耗的最短时间，然后贪心地按照 $a_i$ 从小到大做就行了。

但是这是 01 背包，如果要记录历史路径，那么直接滚动数组的话，就有可能后面把前面方案覆盖掉了。

有两种解决方案：

1. 不滚动数组，然后 $g_{i,j}$ 表示 $f_{i,j}$ 是从 $f_{i-1,g_{i,j}}$ 转移过来的。  
这样时间不变 $O(nm)$；空间变大为 $O(nm)$。

20120712. 直接记录路径，拿个 vector 记录 $f_j$ 的路径，这样就可以滚动数组了。  
这样时间变大为 $O(n^2m)$，不过只是理论值，实际上远远跑不满，1e9 还是比较轻松的；空间不变 $O(m)$。

## Code

用的方案 2。

```cpp
int n,m,f[M];
pii a[N];
struct task{int t,p,id;};
vector <task> b[N];
vector <int> p,g[M];

il void solve()
{
	clr(p);
	read(n,m); rep(i,1,n) read(a[i].st),clr(b[i]);
	{int e,t,p; rep(i,1,m) read(e,t,p),b[e].pb((task){t,p,i});}
	
	rep(i,1,n)
	{
		memset(f,0x3f,sizeof(f)),f[0]=0;
		rep(i,0,200) clr(g[i]);
		for(auto [t,p,id]:b[i]) 
		{
			rpe(j,200,p) 
			{
				if(f[j+1]<f[j]) f[j]=f[j+1],g[j]=g[j+1];
				if(f[j-p]+t<f[j]) f[j]=f[j-p]+t,g[j]=g[j-p],g[j].pb(id);
			}
			rpe(j,p-1,1) if(f[j+1]<f[j]) f[j]=f[j+1],g[j]=g[j+1];
		}
		
		int ans=mnele(f+100,f+200+1);
		if(ans>=inf-20120712) return write(-1ll,'\n');
		
		a[i].nd=ans;
		int pos=-1; rpe(j,200,100) f[j]==ans && (pos=j);
		p.insert(p.end(),all(g[pos]));
	}
	
	sort(a+1,a+n+1);
	int t=0;
	rep(i,1,n)
	{
		t+=a[i].nd;
		if(t>a[i].st) return write(-1ll,'\n');
	}
	
	write((int)p.size(),'\n');
	rep(i,0,(int)p.size()-1) write(p[i],' ');
	write('\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：OIer_ACMer (赞：1)

~~这种题怎么只是个绿题？！~~

------------
注：本题由于只涉及到了 $01$ 背包的知识点，所以笔者不会把证明和原理讲得过于明白，望周知！

------------
## 大致思路：
本题一眼看去 $01$ 背包无疑，但是对于一道 CF 的题来说肯定没那么简单，下面我就来简单地分析一下思路：

首先，我们先将每个任务用一个 vector 类型的变数组 $a$ 存起来，方便我们以后用。

接着，到了重要的 DP 环节，我们首先要考虑一个问题：**该用什么作为 DP 的状态**？我们仔细的想一想，背包无非就是两样东西：**体积**和**价值**。在这道题中，我们可以一下子就想到以时间为容量，但是，当我们仔细阅读一下数据范围，发现在这道题的数据范围中 $t_i \le 10^9$，那么如果我们开一个第二维是 $10^9$ 大小的数组估计会直接 MLE 一片，那么我们这次逆其道而行，将百分比（也就是价值），作为我们的容量，因为题目中说了百分比最多只有 $100$，所以这是个很好的选择。

之后，我们设计状态：我们设 $dp_{i,j}$ 为到了第 $i$ 项时百分比为 $j$ 时的最优解是什么。之后的操作，我们唯二要做的事情就是码一个 $01$ 背包的板子（尽管要用的变量名很多），将原来的状态 $dp_{j,k}$ 加上现在的任务价值 $t$ 就是目前状态的转移式子（说实话就是 $01$ 背包的模板），具体方程如下：

$dp_{j + 1,nk} = \min(dp_{j + 1,nk}, dp_{j,k} + t)$。 

以及写一个记录方案的程序就可以了（这一段我实在是不想讲了，但凡有点基础的人都可以写出来）。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void solve()
{
    int n, m;
    n = read();
    m = read();
    vector<int> lim(n);
    for (int i = 0; i < n; i++)
    {
        lim[i] = read();
    }
    vector<vector<array<int, 3>>> a(n);
    for (int i = 0; i < m; i++)
    {
        int e, t, p;
        cin >> e >> t >> p;
        e--;
        a[e].push_back({t, p, i});
    }
    vector<int> res;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int N = a[i].size();
        vector dp(N + 1, vector<int>(101, 2e9 + 1));
        dp[0][0] = 0;
        for (int j = 0; j < N; j++)
        {
            dp[j + 1] = dp[j];
            auto [t, p, _] = a[i][j];
            for (int k = 0; k <= 100; k++)
            {
                int nk = min(100ll, k + p);
                dp[j + 1][nk] = min(dp[j + 1][nk], dp[j][k] + t);
            }
        }
        sum += dp[N][100];
        if (sum > lim[i])
        {
            cout << -1 << '\n';
            return;
        }
        int nd = 100;
        for (int j = N - 1; j >= 0; j--)
        {
            auto [t, p, id] = a[i][j];
            if (dp[j + 1][nd] == dp[j][nd])
            {
                continue;
            }
            res.push_back(id);
            for (int k = 0; k <= 100; k++)
            {
                int nk = min(100ll, k + p);
                if (nk == nd && dp[j][k] + t == dp[j + 1][nk])
                {
                    nd = k;
                    break;
                }
            }
        }
    }
    cout << res.size() << '\n';
    for (auto x : res)
    {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122564201)

---

## 作者：I_am_Accepted (赞：1)

### Analysis

遵循「哪门作业先交就先写哪门」的原则，我们先将 Opt 按 $e$ 分类。

由于要到达的满额只有 $100$，我们在每种 $e$ 中跑 01 背包即可，让每门课写作业的总时间尽量少。

注意判断无法按时交作业的情况和记录背包的转移。

时间 $O(100(n+m))$。

### Code

[Link](https://codeforces.com/contest/1650/submission/149199429)

---

## 作者：E1_de5truct0r (赞：0)

吐槽：Is this a fake CF `*2200`？

## 思路

首先，贪心的想，最优策略一定是按照 $a$ 升序的顺序进行操作。原因显然，因为如果按照非升序能够完成，升序也一定能够完成。

然后我们对于每一个 $m$，按照 $e_i$ 进行归类，存在 vector 里面。再次贪心的想，我们肯定让每一个 $i$ 都尽可能短时间的完成任务，给后面的腾出时间。因此我们现在变成了：

“给定 $k$ 种选择，第 $i$ 种选择消耗单位为 $t$ 的时间，有 $p$ 的价值，问填满 $100$ 的价值最少需要多少时间。”

显然，这是 01 背包问题，跑一次的复杂度是 $O(k \cdot 100)$。我们对于每一个 $i$ 都跑一次，复杂度就是 $O(\sum k \cdot 100)$。又因为 $\sum k=m$ 所以复杂度实际上就是 $O(100m)$，可以通过。

然后我们求出所有的 $i$ 耗费的最小时间 $dp_i$ 之后，直接从前往后扫一遍，判断是否存在一个 $i$ 使得 $\sum_{j=1}^{i}dp_j>a_i$。如果存在那么就输出 `-1`；否则记录一下，然后输出即可。

## 代码

我的实现比较离谱，各位可以自己写一下更简洁的来吊打我捏~

另外，我发现我这种写法记录路径会 MLE，所以我对下标进行了哈希，然后把这道题用奇奇怪怪的方法草过去了（

然后我发现了天大的秘密：$n,m \leq 10^5$。也就是说我刚才那顿神操作没啥 P 用（打脸.jpg）

不过懒得改了就这样了。这样的话，空间也蛮小的qwq

代码又臭又长勿喷：

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mpair make_pair
using namespace std;
const int MAXN=200005,mod=10001; // 哈希的模数（我相信 CF 没人想到我这种奇怪写法所以肯定不会被卡）
struct Node{
	int fir,sec,id; // 分别表示题目中的 t,p，以及这个操作的编号
};
int a[MAXN],c[MAXN];
int dp[205],from[10005][205],bian[10005][205]; // from[i][j] 记录的是 dp[i][j] 从 dp[i-1][from[i][j]] 转移过来，bian[i][j] 表示这个转移用得边的编号。dp[j] 就是 dp[i][j] 压掉一维。
int cnt=0,ans[MAXN]; // ans 用来存储编号
vector<Node> p[MAXN];
stack<int> s; // 要把顺序反过来，懒得写递归所以用了栈

void DP(int x){
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0; c[x]=1000000001; // 这里不要初始化成 1000000000，有毒瘤数据卡。
	for(int i=0;i<p[x].size();i++){
		for(int j=0;j<=200;j++) from[i%mod][j]=j,bian[i%mod][j]=0; // 下标取模（hhh我真是个【】……）
		for(int j=200;j>=p[x][i].sec;j--){ //这里要从 200 开始，因为一个 p 最大是 100，所以不可能更新到 200 以上的地方
			int t=p[x][i].fir;
			int w=p[x][i].sec;
			if(dp[j-w]+t<dp[j]){ // 转移
				dp[j]=dp[j-w]+t;
				from[i%mod][j]=j-w;
				bian[i%mod][j]=p[x][i].id;
			}
		}
	}
	int u=0,now=p[x].size(),ctn=0;
	for(int i=100;i<=200;i++) // 从 100~200 存最大值。
		if(dp[i]<c[x]) c[x]=dp[i],u=i; // 找到最大值的位置
	while(now) s.push(u),u=from[(--now)%mod][u]; // 向前找路径，压到栈里
	while(!s.empty()){
		if(bian[ctn%mod][s.top()]!=0){
			ans[++cnt]=bian[ctn%mod][s.top()]; // 弹栈就可以反过来，这个时候记录答案
		}s.pop(); ctn++;
	}
}
int main(){
	int T; cin>>T;
	while(T--){
		int n,m; cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i],p[i].clear(); // 记得清空
		for(int i=1;i<=m;i++){
			int x,y,z; cin>>x>>y>>z;
			p[x].pb((Node){y,z,i});
		}
		int sum=0;cnt=0;
		bool flag=1;
		for(int i=1;i<=n;i++) DP(i); // 对于每个 i 进行 dp
		for(int i=1;i<=n;i++){
			sum+=c[i]; // 求一下前缀和
			if(sum>a[i]){ // 看一下是否有解
				flag=0;
				break;
			}
		}
		if(flag){
			cout<<cnt<<endl;
			for(int i=1;i<=cnt;i++) cout<<ans[i]<<" ";
			cout<<endl;
		}else cout<<-1<<endl;
	}
	return 0;
}
```

---

## 作者：AzurIce (赞：0)

# CodeForces 1650F
「Vitaly and Advanced Useless Algorithms」

CodeForces：[Problem - F - Codeforces](https://codeforces.com/contest/1650/problem/F)

洛谷：[CF1650F Vitaly and Advanced Useless Algorithms - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/CF1650F)

## 「题意」

有 $n$ 个任务，每个任务要在 $a_i$ 时刻前做完。（$a$ 升序）

有 $m$ 个计划，每个计划最多只能执行一次，每个计划由 $e_i$, $t_i$, $p_i$ 描述：如果执行了第 $i$ 个计划，那么 $t_i$ 时间后，任务 $e_i$ 会被完成 $p_i$ 的百分比。



输入 $T$ 组数据。

输出每组执行的计划个数 $k$，并按顺序输出执行的计划（若不行则输出 `-1`，若有多种方案输出其中一种即可）。

## 「思路」

首先显然有一个贪心的结论：在当前任务未完成时，优先选择能对当前任务有进展的计划（优先完成离 ddl 近的任务）。

那么对于每一个任务的目标就是 **能使进度达到 100% 的最少时间**。

很容易借助 **差分** 得到 **每一个任务的限制时间**。



对于每一个任务，就是个 **01背包**，对于每一个计划选择 **执行** 或 **不执行**。

在当前任务省下来的时间，就可以添加到下一个任务的时间中去。

## 「码」

```c++
#include <iostream>
#include <cstring>
#include <tuple> // 元组 c++11
#include <vector>

#define INF 0x7f
#define ll long long

using namespace std;

const int MAXN = 1E5 + 7;

int a[MAXN];
ll dp[200 + 7]; // 最少时间
bool f[MAXN][200 + 7];

int solveTask(int a, vector<tuple<int, int, int>> &plans, vector<int> &ans) {
    // memset(f, 0, sizeof(f));
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;

    int n = plans.size();
    int endk = 0;
    for (int j = 0; j < n; j++) {
        auto [e, t, p] = plans[j]; // 结构化绑定 c++17, auto 自动类型推断 c++11
        for (int k = 200; k >= 0; k--) {
            if (k >= p && dp[k - p] + t < dp[k]) {
                dp[k] = dp[k - p] + t;
                f[j][k] = 1;
                if (k >= 100 && dp[k] <= a && (dp[k] < dp[endk] || endk == 0)) {
                    endk = k;
                }
            } else {
                f[j][k] = 0;
            }
        }
    }

    if (endk == 0) return -1;
    int k = endk, j = n-1;
    for (int j = n-1; j >= 0 && k; j--) {
        if (f[j][k]) {
            auto [e, _, p] = plans[j]; // 结构化绑定 c++17, auto 自动类型推断 c++11
            ans.emplace_back(e); // 在vector末尾原位构造 c++11
            k -= p;
        }
    }
    return dp[endk];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T; cin >> T;

    int n, m;
    while (T--) {
        cin >> n >> m;

        a[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i-1] = a[i] - a[i-1];
        }

        vector<vector<tuple<int, int, int>>> plans(n); // 元组 c++11
        for (int i = 1, _e, _t, _p; i <= m; i++) {
            cin >> _e >> _t >> _p;
            plans[_e - 1].emplace_back(i, _t, _p); // 在vector末尾原位构造 c++11
        }

        bool f = 0;
        vector<int> ans;
        int saved_time = 0;
        for (int i = 0; i < n; i++) {
            a[i] += saved_time;
            int mint = solveTask(a[i], plans[i], ans);
            if (mint < 0) {
                f = 1;
                break;
            }
            saved_time = a[i] - mint;
        }

        if (f) {
            cout << -1 << endl;
        } else {
            cout << ans.size() << endl;
            // auto 自动类型推断 c++11
            for (auto iter = ans.begin(); iter != ans.end(); iter++) {
                cout << *iter << ' ';
            }
            cout << endl;
        }
    }

    return 0;
}

```

## 「几个坑点」

看到那个注释掉的 `memset()` 没！

大坏蛋！

调了一个小时，问了别人才知道这个 `memset()` 可能会导致超时！

原因是 `f` 数组太大了，且这个 `memset` 在每个 `case` 中都被调用了 `n` 次！

这回我可记住了！



---

