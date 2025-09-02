# [ICPC 2020 Nanjing R] Let's Play Curling

## 题目描述

# [ICPC2020 Nanjing R] Let's Play Curling


红队和蓝队在冰面上向目标区域滑动冰壶，距离目标区域中心最近的队伍获胜。

两支队伍在一条直线上竞争。比赛结束后，有   $(n+m)$ 个冰壶在直线上, $n$ 个是红队的，剩下 $m$ 个是蓝队的。 红队的第 $i$ 个冰壶被放在 $a_i$ ，蓝队的第 $i$ 个冰壶被放在 $b_i$ 。

设 $c$ 是中心。如果存在一些 $i$ 使得 $1 \le i \le n$ 并且对于所有 $1 \le j \le m$ 都有 $|c - a_i| < |c - b_j|$ 红队就赢得比赛。另外，如果满足条件的 $i$ 的数目是 $p$ ，则认为红队赢得 $p$ 分。

给你红蓝两队的冰壶的位置，请你确定中心 $c$ 的值，使红队得分最多。注意， $c$ 是任意实数，不一定是整数。

## 说明/提示

对于第一个样例，当 $c = 2.5$ 时，红队的位于 2 和 3 的冰壶可以得分。

对于第二个样例，当 $c = 7$ 时，红队的位于 5 和 7 的冰壶可以得分。

## 样例 #1

### 输入

```
3
2 2
2 3
1 4
6 5
2 5 3 7 1 7
3 4 3 1 10
1 1
7
7```

### 输出

```
2
3
Impossible```

# 题解

## 作者：_Gabriel_ (赞：4)

### 大意

给定两个数组 $a$ 和 $b$，需要找到一个整数 $ans$，它表示在数组 $a$ 中找到一个子数组，使得这个子数组包含数组 $b$ 中的尽可能多的元素。然后，如果无法找到这样的子数组输出 `Impossible`，否则输出 $ans$ 的值。

### 思路

先把 $a$ 数组和 $b$ 数组排好序，以便后续的二分查找。

使用二分查找 `upper_bound` 和 `lower_bound` 来找到数组 $a$ 中与 $b[i]$ 相等或者比它稍大的元素的位置。然后计算这两个位置之间的距离，即长度 $len$。

更新 $ans$，将其设置为当前 $ans$ 和 $len$ 中的较大值。

最后判断 $ans$ 是否为 $0$，如果为 $0$，就是无法找到满足条件的子数组，输出 `Impossible`。否则，输出答案 $ans$。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 5e6 + 10;
int a[N], b[N];
int n, m, t, ans;

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= m; i++) {
			cin >> b[i];
		}
		b[0] = -INF, b[m + 1] = INF;
		sort(a + 1, a + n + 1);
		sort(b, b + m + 1);
		for (int i = 0; i <= m; i++) {
			int pos1 = upper_bound(a + 1, a + n + 1, b[i]) - a;
			int pos2 = lower_bound(a + 1, a + n + 1, b[i + 1]) - a - 1;
			int len = pos2 - pos1 + 1;
			ans = max(ans, len);
		}
		if (ans == 0) {
			cout << "Impossible\n";
		} else {
			cout << ans << "\n";
		}
		ans = 0;
	}
	return 0;
}
```

---

## 作者：Oracynx (赞：3)

## P9633 [ICPC2020 Nanjing R] Let's Play Curling 题解

### [题目翻译](https://www.luogu.com.cn/paste/u3rdv88k)

### 思路分析

阅读题目后，我们发现这道题的重点是在求出最高得分而不是 $c$ 的值。考虑下面这个例子：

$$
\texttt{\textcolor{red}{RRR}\textcolor{blue}{BB}\textcolor{red}{RRRR}\textcolor{blue}{BBB}\textcolor{red}{R}}
$$

我们发现，当 $c$ 放在第 $6,7,8,9$ 个冰壶的位置时，红队最多可以得到 $4$ 分。

所以本题的核心思想便是求出最长的连续红队冰壶的长度。

具体实现方法如下：

1. 枚举起始的蓝色冰壶，即 $b_i$。
2. 二分查找一个 $a_j$，要求 $b_i \le a_j$ 且 $b_{i+1} \ge a_j$ 这样可以是红队的冰壶队列长度最大化。
3. 如果得分为 $0$ 则表示一直没有可以赢过蓝队的位置，输出 $\texttt{Impossible}$，否则输出最大的得分。

### 代码实现

注：为了简洁代码，我们可以使用 C++STL 中的 `lower_bound` 和 `upper_bound` 函数，分别是查找小于等于和大于等于的元素。（注意：这两个函数返回的是指向满足条件的元素的指针而不是 `int`）

```cpp
#include <algorithm>
#include <cstdio>
const int MaxN = 1e5 + 5;
int t;
int n, m;
int answer;
int a[MaxN];
int b[MaxN];
bool lose;
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &b[i]);
    }
    b[m + 1] = 0;
    b[m + 2] = 0x7f7f7f7f;
    m += 2;
    std::sort(a + 1, a + 1 + n);
    std::sort(b + 1, b + 1 + m);
    answer = -1;
    for (int i = 1; i <= m; i++)
    {
        answer = std::max(answer, (int)(std::lower_bound(a + 1, a + n + 1, b[i + 1]) - a) -
                                      (int)(std::upper_bound(a + 1, a + n + 1, b[i]) - a));
    }
    if (answer == 0)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%d\n", answer);
    }
    return;
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：YuYuanPQ (赞：1)

这个题面看上去就很不舒服，但转化一下就非常好想了。

形式化题意：\
在相邻的 $b_i$ 和 $b_{i+1}$ 之间找满足 $b_i\leq a_j\leq b_{i+1}$ 的 $a_j$ 的个数，然后找出这 $m+1$ 段中最多的个数。

于是对 $a$ 数组和 $b$ 数组分别排序，排完序对 $a$ 数组二分，算出在 $[b_i,b_{i+1}]$ 中的 $a_j$ 的个数。而最终答案就是所有个数中的最大值。

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
// typedef __int128 int128;
typedef double DB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))
using namespace std;

const int N=1e5+10,M=N;

int n,m;
int a[N],b[M];

int ans;

void sl_reset();
void solve(){
    sl_reset();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    sort(a+1,a+1+n);
    sort(b+1,b+1+m);
    b[0]=-2e9,b[++m]=2e9;
    for(int i=0;i<m;i++){
    	int l=upper_bound(a+1,a+1+n,b[i])-b;
    	int r=lower_bound(a+1,a+1+n,b[i+1])-b-1;
    	int s=r-l+1;
    	ans=max(ans,s);
    }
    if(ans) printf("%d\n",ans);
    else printf("Impossible\n");
    return;
}

void sl_reset(){
    ans=0;
    return;
}

int main(){
    // freopen("magic.in","r",stdin);
    // freopen("magic.out","w",stdout);
    int T=1;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：luan341502 (赞：1)

特别地，我们设 $b_0=-1$，$b_{n+m+1}=n+m+1$。考虑对于每个 $b_i(0 \leq i \leq n+m)$，中心的位置都一定在 $b_i$ 和 $b_{i+1}$ 的平均值处最优，因为若取的点靠近左端，则可能有的靠近右端的点离中心较远，就无法取到，若靠近右端同理。因此选择的中心应与左端和右端一样近，此时所有 $b_i \leq a_j \leq b_{i+1}$ 都能被取到。枚举即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans=0;
int a[200005];
map<int,int> mp1;
map<int,bool> mp2;
int main(){
	cin>>t;
	while(t--){
		mp1.clear();mp2.clear();ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			mp1[a[i]]++;
		}
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i+n]);
			mp2[a[i+n]]=true;
		}
		sort(a+1,a+n+m+1);
		int cnt=unique(a+1,a+n+m+1)-a-1,sum=0;
		for(int i=1;i<=cnt;i++){
			if(mp2[a[i]]){
				ans=max(ans,sum);
				sum=0;
				continue;
			}
			else sum+=mp1[a[i]];
		}
		ans=max(ans,sum);
		if(ans) printf("%d\n",ans);
		else puts("Impossible"); 
	}
	return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：1)

题解来源于一位和我组队且不愿透露姓名的好兄弟。

贪心。

一个显然的性质是，如果这个 $c$ 被两个 $b$ 夹在了中间，那么这个 $c$ 必然放在两个 $b$ 的算术平均值的位置是最优的，否则都会使得 $\min\{\left\lvert c-b_i\right\rvert\}$ 变小。

于是把 $a$ 和 $b$ 排个序然后逐个枚举夹在两个 $b$ 中间的可能取值，然后二分查找到可行的 $a$ 对应的范围即可。

时间复杂度 $O(n\log n)$，很好写。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace  std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51;
ll test,n,m,lt,gt,res,lb,rb;
ll r[MAXN],b[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline void solve()
{
	n=read(),m=read(),lt=gt=res=0;
	for(register int i=1;i<=n;i++)
	{
		r[i]=read();
	}
	for(register int i=1;i<=m;i++)
	{
		b[i]=read();
	}
	b[0]=-2e9,b[m+1]=2e9;
	sort(r+1,r+n+1),sort(b+1,b+m+1);
	for(register int i=0;i<=m;i++)
	{
		lb=upper_bound(r+1,r+n+1,b[i])-r,rb=lower_bound(r+1,r+n+1,b[i+1])-r;
		res=max(res,rb-lb);
	}
	res==0?puts("Impossible"):printf("%d\n",res);
}
int main()
{
	test=read();
	for(register ll i=1;i<=test;i++)
	{
		solve();
	}
}
```

---

## 作者：liheyang123 (赞：0)

## 简化题意
求在一个不存在 $B_i$ 的区间中，出现 $A_i$ 的最多次数。
## 做法
注意到集合 $A$ $B$ 值域很大，但其中的数很少，所以可以考虑离散化，然后扫描一遍区间就能得出答案，注意应选择一个非常大的数作为右端点与一个非常小的数作为左端点，或者在求答案时将答案初始化为 $C$ 小于所有 $B_i$ 与大于所有 $B_i$ 的结果的较大值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
#define int long long
const int N=1e5+10;
int T,n,m;
ll a[N],b[N],c[N*2],cnt;
ll s[N*2],ss[N*2],ans,ansy;

int find(ll x) {
	int l=1,r=cnt;
	while(l<=r) {
		int mid=l+r>>1;
		if(c[mid]==x)return mid;
		if(c[mid]<x)l=mid+1;
		else r=mid;
	}
	return 0;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	cin>>T;
	while(T--) {
		memset(s,0,sizeof(s));
		memset(c,0,sizeof(c));
		cnt=0,ans=0;
		cin>>n>>m;
		for(int i=1; i<=n; i++) {
			cin>>a[i];
			c[++cnt]=a[i];
		}
		for(int i=1; i<=m; i++) {
			cin>>b[i];
			c[++cnt]=b[i];
		}
		sort(c+1,c+1+cnt);
		int k=unique(c+1,c+1+cnt)-c-1;
		cnt=k;
		for(int i=1; i<=n; i++)s[find(a[i])]++;
		sort(b+1,b+1+m);
		for(int i=1; i<=cnt; i++)ss[i]=s[i]+ss[i-1];
		m=unique(b+1,b+1+m)-b-1;
		ans=max(ss[find(b[1])-1],ss[cnt]-ss[find(b[m])]);
		for(int i=1; i<m; i++) {
			if(b[i]!=b[i+1])ans=max(ans,ss[find(b[i+1])-1]-ss[find(b[i])]);
		}
		if(ans!=0)cout<<ans<<'\n';
		else cout<<"Impossible\n";
	}
	return 0;
}
```

---

## 作者：Pratty (赞：0)

明显的一个二分查找题，可以化简为**在两个蓝色点内红色点最多的数量**，找不到即输出 `Impossible`。

首先要把 $a$ 和 $b$ 数组进行排序，使用 `lower_bound` 和 `upper_bound` 进行简便式的二分查找，用一个 $ans$ 记录当前查找到的最大距离，然后枚举每一个点判断从这个点向后的**最近两个蓝点** $l$ 和 $r$，然后用 $r-l$ 算出红点个数，与 $ans$ 取一个较大值。

这样一个时间复杂度为 $O(n\ \log\ n)$ 的程序就写好了，最后判断如果 $ans=0$ 则无解，输出 `Impossible`，否则输出 $ans$。

---

## 作者：WhitD (赞：0)

## 题目大意
给定长度分别为 $n,m$ 的数组 $a,b$，你需要找到一个合适的 $c$，使 $a$ 中的某个元素 $a_i$，满足 $\forall 1\le j\le m,\left|c-a_i\right|<\left|c-b_j\right|$，输出满足条件的元素的最多个数。
## 思路
结合样例理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/qg443pk1.png)

显然我们的 $c$ 值选在 $a_1,a_2$ 之间是最优的（假如 $c$ 选在了 $a_2,b_2$ 之间，那么 $a_1$ 就不满足条件了，不会更优），也就是说如果有多个 $a_i$ 是连续的（中间没有 $b_j$），最优的 $c$ 值一定是他们的平均值（这样才能保证这连续的几个 $a_i$ 都能满足条件）。

再考虑这种情况（我们用红色代表 $a$，绿色代表 $b$，下标自左向右递增）：

![](https://cdn.luogu.com.cn/upload/image_hosting/74k4iijv.png)

我们发现：$a_2,a_3$ 不可能同时选到，因为在中间夹了一个 $b_2$，不论 $c$ 值放在哪都只能使其中一个满足条件。说明最终结果一定是连续的一段（我们以 $b$ 作为分界点）。但是 $a_1,a_2$ 是可以同时选的，只要 $c$ 在黄色范围就可以，也就印证了上一段我们的结论。

因此，最多的两个 $b$ 之间的 $a$ 的个数就是我们的答案，可以先排序再二分。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main()
{
	cin>>T;
	while(T--)
	{
		int ans=0,n,m,a[100005],b[100005];
		memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>a[i]; 
		for(int i=1;i<=m;i++)
			cin>>b[i];
		b[++m]=0,b[++m]=0x7fffffff;
		sort(a+1,a+n+1),sort(b+1,b+m+1);
		for(int i=1;i<m;i++)
			ans=max(ans,int(lower_bound(a+1,a+n+1,b[i+1])-upper_bound(a+1,a+n+1,b[i])));
		if(!ans) 
			cout<<"Impossible"<<endl;
		else 
			cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Pollococido (赞：0)

### 思路

我们看一下下面这个比赛场面：
$$\color{red}\texttt{R}\color{red}\texttt{R}\color{red}\texttt{R}\color{blue}\texttt{B}\color{blue}\texttt{B}\color{red}\texttt{R}\color{red}\texttt{R}\color{blue}\texttt{B}$$ 
当 $c$ 在 $1,2,3$ 个冰壶时，红队得分最大，所以，我们只要求出最长连续的都是红队冰壶的长度。

### 过程

1. 枚举 $j(1 \le j \le m)$，也就是蓝队冰壶的位置。
2. 二分 $a_i$，$a_i$ 需满足 $b_j \le a_i \le b_{j+1}$。
3. 如果一分也得不到就是 `Impossible`。

### 代码

写一下过程部分的：

```cpp
// 先 m += 2，再把 b[m + 1] 设为 0，把 b[m + 1] 设为极大值，再排序 a 和 b。
int ans = -1;  // 存储结果
for (int i = 1; i <= m; i++) {
	int p1 = (int)(lower_bound(a + 1, a + n + 1, b[i + 1]) - a);
	int p2 = (int)(upper_bound(a + 1, a + n + 1, b[i]) - a);
	ans = max(ans, p1 - p2);
}
if (!ans)
	cout << "Impossible" << endl;
else
	cout << ans << endl;
```

---

## 作者：niuzh (赞：0)

### 思路

题意可以化简为在两个蓝色点内红色点最多的数量，找不到即输出 `Impossible`。

先把 $a$ 数组和 $b$ 数组排好序，以便后续的二分查找。

使用 `upper_bound` 来找到数组 $a$ 中与 $b_i$ 相等或者比它大的元素中最小的位置，使用 `lower_bound` 来找到数组 $a$ 中比 $b_{i+1}$ 比大的元素中最小的位置。将 $ans$ 设为当前 $ans$ 和两个位置之间的距离的最大值。

最后判断 $ans$ 是否为 $0$，如果为 $0$，就是无法找到一对符合要求蓝色点，输出 `Impossible`。否则，输出答案 $ans$。

### 代码

![](https://cdn.luogu.com.cn/upload/image_hosting/1s0tit7n.png)

---

