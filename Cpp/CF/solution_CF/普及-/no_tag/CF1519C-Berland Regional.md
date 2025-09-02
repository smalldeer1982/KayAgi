# Berland Regional

## 题目描述

Polycarp is an organizer of a Berland ICPC regional event. There are $ n $ universities in Berland numbered from $ 1 $ to $ n $ . Polycarp knows all competitive programmers in the region. There are $ n $ students: the $ i $ -th student is enrolled at a university $ u_i $ and has a programming skill $ s_i $ .

Polycarp has to decide on the rules now. In particular, the number of members in the team.

Polycarp knows that if he chooses the size of the team to be some integer $ k $ , each university will send their $ k $ strongest (with the highest programming skill $ s $ ) students in the first team, the next $ k $ strongest students in the second team and so on. If there are fewer than $ k $ students left, then the team can't be formed. Note that there might be universities that send zero teams.

The strength of the region is the total skill of the members of all present teams. If there are no teams present, then the strength is $ 0 $ .

Help Polycarp to find the strength of the region for each choice of $ k $ from $ 1 $ to $ n $ .

## 说明/提示

In the first testcase the teams from each university for each $ k $ are:

- $ k=1 $ : 
  - university $ 1 $ : $ [6], [5], [5], [3] $ ;
  - university $ 2 $ : $ [8], [1], [1] $ ;
- $ k=2 $ : 
  - university $ 1 $ : $ [6, 5], [5, 3] $ ;
  - university $ 2 $ : $ [8, 1] $ ;
- $ k=3 $ : 
  - university $ 1 $ : $ [6, 5, 5] $ ;
  - university $ 2 $ : $ [8, 1, 1] $ ;
- $ k=4 $ : 
  - university $ 1 $ : $ [6, 5, 5, 3] $ ;

## 样例 #1

### 输入

```
4
7
1 2 1 2 1 2 1
6 8 3 1 5 1 5
10
1 1 1 2 2 2 2 3 3 3
3435 3014 2241 2233 2893 2102 2286 2175 1961 2567
6
3 3 3 3 3 3
5 9 6 7 9 7
1
1
3083```

### 输出

```
29 28 26 19 0 0 0 
24907 20705 22805 9514 0 0 0 0 0 0 
43 43 43 32 38 43 
3083```

# 题解

## 作者：Mophie (赞：8)

~~这题我 Hack 了别人 50 发，然后来写篇题解~~

我们发现首先对于每一所大学都是互相独立的。就是说答案必然是每所大学的最优解拼起来。

然后就会有一个比较朴素的思路：

对于每一所大学建一个 vector，然后对于 vector 里面的数从大到小排序。

那么显然比如说一个 vector 里面的数有 $x$ 个，然后一个队伍里有 $k$ 个人，那么就应该可以取 $ \lfloor\frac{x}{k}\rfloor \times k $ 个最大的。

首先暴力是 $O(n^3)$ 的，然后做一个前缀和优化可以到 $O(n^2)$，~~而且这个做法可以过 pretest~~。

但我们发现这个做法太拉了，考虑优化。

我们设对于一个 $k$，答案为 $ans_k$。

然后发现对于每一所大学，设它有 $x$ 个人，那它最多对 $ans_1,ans_2,\cdots ans_x$ 有贡献。

那么计算贡献即可，时间复杂度因为有排序故是 $O(n logn)$。

```cpp
//红太阳zhouakngyang txdy!
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
const int N=2e5+9;
vector<long long> G[N];
int n,taxi,id[N],s[N];
long long ans[N];
inline bool cmp(int xxx,int yyy)
{
	return xxx>yyy;
}
int main()
{
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		n=read();
		for(int i=1;i<=n;i++)G[i].clear(),ans[i]=0;
		for(int i=1;i<=n;i++)id[i]=read();
		for(int i=1;i<=n;i++)s[i]=read();
		for(int i=1;i<=n;i++)G[id[i]].push_back(s[i]);
		for(int i=1;i<=n;i++)
			if(G[i].size()!=0)
			{
				sort(G[i].begin(),G[i].end(),cmp);
				for(int j=1;j<G[i].size();j++)G[i][j]+=G[i][j-1];
			}
		for(int i=1;i<=n;i++)
			if(G[i].size()!=0)
			{
				int len=G[i].size();
				for(int k=1;k<=len;k++)
					ans[k]+=G[i][len/k*k-1];	
			}
		for(int i=1;i<=n;i++)printf("%lld ",ans[i]);puts("");
	}
	return 0;
}

```




---

## 作者：oimaster (赞：5)

主要点在于时间复杂度。

几种做法我都说一下，复杂度会慢慢变得优秀。

1. 
- 每个学校的所有学生能力存储下来，进行递减排序。
- 循环计算每个 $k$ 的答案。内循环遍历每个学校学生数组，当发现本学校剩余学生大于 $k$ 时我们就计算这 $k$ 个学生所给出的贡献值。
- 时间复杂度：$\text{O}(n^3)$。无法通过。
2. 
- 不难发现如果一个学校有 $tots$ 个学生，那么最后选择的选手**组数**为 $\lfloor\frac{tots}{k}\rfloor$，选手**数量**就会是 $\lfloor\frac{tots}{k}\rfloor\cdot k$ 位。
- 那么在第一个算法上改进最内部的循环，成为一个前缀和计算。
- 时间复杂度：$\text{O}(n^2)$。fst。
3. 
- 发现一个学校如果有 $tots$ 个学生，当 $k>tots$ 时这个学校就无法派出学生，无法为答案做出贡献。
- 那么就可以对于每个学校，我们计算对于每个 $k$，学校可以做出的贡献。只需要开一个数组统计一下即可。
- 因为所有 $tots$ 加起来为 $n$，还知道 $k\le tots$，那么核心部分循环总共的复杂度就是 $\text{O}(n)$。不过排序复杂度就有 $\text{O}(n\log n)$ 了，所以总时间复杂度为 $\text{O}(n\log n)$。

其他注意的地方：

- Q：WA #4？
- A：你开 `long long` 了吗？

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define zb(x,y) ((x)/(y)*(y))
#define int long long
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a[n+1];
        int b[n+1];
        for(int i=1;i<=n;++i)
            cin>>b[i];
        for(int i=1;i<=n;++i){
            int tmp;
            cin>>tmp;
            a[b[i]].push_back(tmp);
        }
        for(int i=1;i<=n;++i){
            sort(a[i].begin(),a[i].end(),greater<int>());
            for(int j=1;j<a[i].size();++j)
                a[i][j]+=a[i][j-1];
        }
        int res[n+1];
        for(int i=1;i<=n;++i)
            res[i]=0;
        for(int i=1;i<=n;++i){
            int tots=a[i].size();
            for(int j=1;j<=tots;++j)
                res[j]+=a[i][zb(tots,j)-1];
        }
        for(int i=1;i<=n;++i)
            cout<<res[i]<<' ';
        cout<<endl;
    }
}
```

---

## 作者：RedreamMer (赞：3)

[$\Large\texttt{CF1519C}$](https://www.luogu.com.cn/problem/CF1519C)

## 题意

给定多个序列 $A_i$ 其中 $\sum|A_i|=n$，对于每个 $j$ 你需要求出对于所有 $A_i$，每 $j$ 个数一组，所有序列组成的组的最大权值和，不足 $j$ 个不被计算。

## 思路

模拟题。

显然，对于每个组，最好的办法就是让 $|A_i| \texttt{ mod } j$ 为序列中最小的几个数，所以只需要对每个序列排序后做一个前缀和，对于要求的 $j$，只需算出 $\sum{A_i}-\sum_{i=1}^{i\le |A_i| \texttt{ mod } j}$ 即可。

注意不要枚举 $j$ ，要枚举每个 $i$ 并枚举 $|A_i|$。

## 代码

```cpp
int t, a, s[N + 5], ans[N + 5], p[N + 5];
vector<int> st[N + 5];

signed main() {
    // freopen("in1.in", "r", stdin);
    t = read();
    while (t--) {
        a = read();
        int tmp = 0;
        rep(i, 1, a) s[i] = read(), st[i].clear(), ans[i] = p[i] = 0;
        rep(i, 1, a) st[s[i]].PB(read());
        rep(i, 1, a) {
            if (!siz(st[i])) continue;
            sort(st[i].begin(), st[i].end());
            rep(j, 1, siz(st[i]) - 1) st[i][j] += st[i][j - 1];
            tmp += st[i][siz(st[i]) - 1];
            rep(j, 1, siz(st[i])) {
                int q = siz(st[i]) % j;
                if (q) ans[j] -= st[i][q - 1];
            }
            p[siz(st[i]) + 1] -= st[i][siz(st[i]) - 1];
        }
        rep(i, 1, a) p[i] += p[i - 1], printf("%lld ", ans[i] + tmp + p[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：ChenZQ (赞：2)

观察题目我们便可发现，对于每一个 $k$，每一个队的贡献值都是一样的。而通过观察，我们可以进一步推出，每个学校被选的人得个数一定是排序后的数组前 $t \div k \times k$ 个。（整数除法，$t$ 表示人数，$k$ 表示每个队人数。）

为什么呢？

因为计算机运行中除法是省略余数的，$t \div k$ 会求出能分出几队，**并且省略掉凑不成一队的**，再乘 $k$ 就可以得到有多少个人能贡献了。

然后使用前缀和优化，代码就出来了。

**注：由于此做法完美地和时限重合，所以要用很多优化来卡进时限。**

```
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;


inline int read() //读入优化。
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}

const int N = 200010;
vector<long long> v[N];
int a[N];
long long ans[N];

bool cmp(long long x,long long y)
{
	return x>y;
}


int main()
{
	int __;
	__=read();
	while(__--)
	{
		int n;
		n=read();
		int mx=0;
		for(int i=1;i<=n;i++) a[i]=read(),mx=max(mx,a[i]);
		for(int i=1;i<=n;i++) v[i].clear(),ans[i]=0;//初始化。
		for(int i=1;i<=n;i++) 
		{
			long long x;
			x=read();
			v[a[i]].push_back(x);
		}
		for(int i=1;i<=mx;i++)
		{
			int tt=v[i].size();
			if(tt>0)
			{
				sort(v[i].begin(),v[i].end(),cmp);//排序。
				for(int j=1;j<tt;j++) v[i][j]+=v[i][j-1];//前缀和。
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(v[i].size()!=0)
			{
				int t=v[i].size();
				for(int k=1;k<=t;k++) ans[k]+=v[i][t/k*k-1];//相加贡献值。
			}
		}
		for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
		
		puts("");
		
	}
	return 0;
} 
```

---

## 作者：ydkxj (赞：1)

## 题意简述

每个队伍有 $k$ 个人。这个地区有 $n$ 所学校和 $n$ 个人，每个人有一个水平和一个学籍。水平前 $k$ 的为一个队伍；剩下的人中在选出前 $k$ 
的人重复此操作。

## 写法

结构体存储，vector 动态数组存储与转移，定义 $sum$ 存储精彩程度。

## CODE
```cpp
#include <bits/stdc++.h>
#define int long long
const long long N=2e5+9;
using namespace std;
struct st{
	int jincaidu;
	int xueji;
}a[N];
vector<long long> cty[N];        //二维数组存数据。
int sum[N]={0};
inline bool cmp(int k,int l)     //排序。 
{
	return k>l;
};
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);                //快读。 
	cout.tie(0);
	int n,k;
	cin>>n;
	while(n--)
	{
		cin>>k;
		for(int i=1;i<=k;i++)
		{
			cty[i].clear();   //重置。 
			sum[i]=0;
		}
		for(int i=1;i<=k;i++)
		{
			cin>>a[i].xueji;   
		}
		for(int i=1;i<=k;i++)  //输入。 
		{
			cin>>a[i].jincaidu;
		}
	    for(int i=1;i<=k;i++)cty[a[i].xueji].push_back(a[i].jincaidu);   //二维动态数组存图。 
		for(int i=1;i<=k;i++)
			if(cty[i].size()!=0)
			{
				sort(cty[i].begin(),cty[i].end(),cmp);                   //排序。 
				for(int j=1;j<cty[i].size();j++)cty[i][j]+=cty[i][j-1];  //累加。 
			}
		for(int i=1;i<=k;i++)
			if(cty[i].size()!=0)
			{
				int l=cty[i].size();
				
				for(int qq=1;qq<=l;qq++)
				{
				    if(l/qq*qq-1<0){                                     //统计。 
					continue;
					}
					sum[qq]+=cty[i][l/qq*qq-1];	
			}
		}
		for(int i=1;i<=k;i++)cout<<sum[i]<<" ";                         //输出。 
		cout<<endl;
	}
	return 0;
}
```

求过。

---

## 作者：tssys (赞：0)

## 前言
一道好的数据结构题，建议升黄。
## 分析
对于这道题，我们不难发现每个大学是**互相独立**的，所以我们用一个数据结构来维护每一个大学的位置，又因为 $ 1 \le u_i \le n \le 2 \cdot 10^5 $ ，所以我们可以用**动态数组**来维护它。

然后又因为对于每一个大学要从能力值大的队员取向能力值小的队员，且对于所有人，他分不分组并不影响，影响的只是他去不去参加，所以我们只要去掉最后的不去的队员能力值之和就可以达到。
所以我们考虑对于每一所大学的内部进行**排序**。排完所有序后，进行**前缀和**，这样就可以以极快的速度来求出，连续一段没去的队员的能力值之和，具体细节可以看代码。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>a[200005],s[200005];
int qwq[200005];
bool cmp(int x,int y)
{
    return x>y;
}
main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            int x;
            cin>>qwq[i];
        }
        for(int i=1;i<=n;i++)
        {
            int x;
            cin>>x;
            a[qwq[i]].push_back(x);
        }
        for(int i=1;i<=n;i++)
            sort(a[i].begin(),a[i].end(),cmp);
        for(int i=1;i<=n;++i)
        {
            if(a[i].size()==0)
                continue;
            for(int j=0;j<a[i].size();j++)
            {
                if(j==0)
                    s[i].push_back(a[i][j]);
                else
                s[i].push_back(a[i][j]+s[i][j-1]);
            }
        }
//        cout<<"我擦";
        memset(qwq,0,sizeof(qwq));
        for(int i=1;i<=n;i++)
        {
            if(a[i].size()==0)
                continue;
            for(int k=1;k<=a[i].size();k++)
            {
                qwq[k]+=s[i][(int)(a[i].size())/k*k-1];
            }
        }
        for(int i=1;i<=n;i++)
            cout<<qwq[i]<<" ";
        for(int i=1;i<=n;i++)
        {
            a[i].clear();
            s[i].clear();
        }
        memset(qwq,0,sizeof(qwq));
        cout<<endl;
    }
}

~~~

---

## 作者：RaymondOccam (赞：0)

### 思路
本人第一反应是用前缀和做。

实际上这道题就是用前缀和。

观察得到：

- 如果当前大学的人数为 $p$，显然 $k\gt p$ 时精彩程度为 $0$。

因此只需要确定，$k$ 的取值范围是 $[1,p]$。

因此前缀和配合上述的优化就可以优化后通过本题。

### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#define int long long
using namespace std;
// bool m1;
int T;
const int maxn = 200007;
int n;
int res[maxn];
int uni[maxn];
vector <int> a[maxn];
vector <int> tmp;
// bool m2;
/**
 * @brief cases
 */
void solve () {
    memset (res, 0, sizeof res);
    int x;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> uni[i];
        a[i].clear ();
    }
    for (int i = 1; i <= n; i++) {
        cin >> x;
        a[uni[i]].push_back (x);
    }
    for (int i = 1; i <= n; i++) {
        sort (a[i].begin (), a[i].end (), greater <int> ());
        tmp.clear ();
        tmp.push_back (0);
        for (int j = 0; j < a[i].size (); j++)
            tmp.push_back (*(tmp.end () - 1) + a[i][j]);
        for (int j = 1; j <= a[i].size (); j++) {
            res[j] += tmp[a[i].size () / j * j];
        }
    }
    for (int i = 1; i <= n; i++)
        cout << res[i] << ' ';
    cout << '\n';
    return;
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0);
    cout.tie (0);
    cin >> T;
    while (T--) {
        solve ();
    }
    return 0;
}
```

---

## 作者：dengruijie2 (赞：0)

对于每所大学 $i$，对 $k$ 的贡献即为前 $n-n \bmod k$ 的学生能力值之和。

如果它拥有 $siz_i$ 
  个学生，它所能够提供贡献的最大的 $k$ 即为 $k=siz_i$	
  时的情况，这减少了我们的工作量。

而每所大学的贡献显然是独立的，所以对于每所大学枚举 $k$，然后用前缀和算贡献即可。

## 上代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;

const int INF = 1e18;

struct node{
    int u, s;
    bool operator < (const node &px) const{
        if(u != px.u){
            return u < px.u;
        }
        return s > px.s;
    }
}a[N];

int T, n, s[N], sum[N];

signed main(){
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i].u;
        }
        for(int i = 1; i <= n; i++){
            cin >> a[i].s;
        }
        memset(sum, 0, sizeof(sum));
        sort(a + 1, a + n + 1);
        for(int i = 1; i <= n; i++){
            int l = i,r = i;
            s[1] = a[i].s;
            while(r < n && a[r + 1].u == a[l].u){
                r++;
                s[r - l + 1] = s[r - l] + a[r].s;
            }
            int len = r - l + 1;
            for(int j = l; j <= r; j++){
                sum[j - l + 1] += s[len - len % (j - l + 1)];
            }
            i = r;
        }
        for(int i = 1; i <= n; i++){
            cout << sum[i] << ' ';
        }
        cout << '\n';
    }
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## CF1519C Berland Regional 题解

### 思路分析

显然我们可以通过排序后模拟得到 $O(n ^ 3)$ 的复杂度，不再赘述。

然后，利用前缀和计算出大学 $i$ 选出前 $x$ 个学生的精彩度，记为 $s_{i, x}$。

接着，记大学 $i$ 的人数为 $a$ 人，则精彩度为 $\displaystyle s_{i, \lfloor \frac{a}{k} \rfloor \times k}$。

我们获得了一个 $O(n ^ 2)$ 的做法。

发现对于一个没有人参加的大学，仍然计算了 $k = 1 \sim n$，考虑优化。

显然，在 $k > a$ 之后的精彩度为 $0$。

所以，对于每一个大学，$k$ 的取值范围为 $1 \sim a$。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n;
int p[MaxN];
long long answer[MaxN];
std::vector<int> v[MaxN];
std::vector<long long> sum;
int solve()
{
    memset(answer, 0, sizeof(answer));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        v[i].clear();
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        v[p[i]].push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        std::sort(v[i].begin(), v[i].end(), std::greater<>());
        sum.clear();
        sum.push_back(0);
        for (auto x : v[i])
        {
            sum.push_back(*sum.rbegin() + x);
        }
        for (int j = 1; j <= int(v[i].size()); j++)
        {
            answer[j] += sum[int(v[i].size()) / j * j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", answer[i]);
    }
    printf("\n");
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1519C)

---

# 思路：

对于每所大学 $i$，对 $k$ 的贡献即为前 $n − n \bmod k$ 的学生能力值之和。

如果它拥有 $siz_i$ 个学生，它所能够提供贡献的最大的 $k$ 即为 $k=siz_i$ 时的情况，这减少了我们的工作量。

而每所大学的贡献显然是独立的，所以对于每所大学枚举 $k$，然后用前缀和算贡献即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
struct node{
    int u,s;
    bool operator<(const node &px)const{
        if(u!=px.u){
            return u<px.u;
        }
        return s>px.s;
    }
}p[N];
int T,n,pre[N],ans[N];
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>p[i].u;
        }
        for(int i=1;i<=n;i++){
            cin>>p[i].s;
            ans[i]=0;
        }
        sort(p+1,p+n+1);
        for(int i=1;i<=n;i++){
            int l=i,r=i;
            pre[1]=p[i].s;
            while(r<n&&p[r+1].u==p[l].u){
                r++;
                pre[r-l+1]=pre[r-l]+p[r].s;
            }
            int len=r-l+1;
            for(int j=l;j<=r;j++){
                ans[j-l+1]+=pre[len-len%(j-l+1)];
            }
            i=r;
        }
        for(int i=1;i<=n;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
	return 0;
}
```

完结撒花~

---

## 作者：Awatesolo (赞：0)

# CF1519C Berland Regional 题解

## 题目重述

* 给定学生们的编程能力及其所属学校编号。
* 每个学校会将该学校水平前 $k$ 的人组为一个队伍。然后再将剩余人中水平前 $𝑘$ 的人组为一个队伍，直到剩下的人不足 $k$ 个 **（此时不为答案增加贡献）**。
* 某个地区 IPIC 的精彩程度为所有参赛人的水平之和。
* 计算分别当 $𝑘=1,2,3...𝑛−1,n$ 时， IPIC 的精彩程度。

## 题目思路

* 模拟每个学校的选人。
* 利用前缀和快速计算。

## 实现细节

* 数据范围 $n\le2\times10^5$，因此我们无法使用二维数组储存。
  * 我们可以采用存图时的常用方法：**vector 邻接表**。
* 把排序规则改为 ``greater`` 使得我们的排序从大到小而非从小到大，可以因不用手写 ``cmp`` 而有效减少码量。
* 由于剩下的人不足 $k$ 人时不计答案，因此我们在计算答案时可以直接用

$$
len \div k
$$
其中 $len$ 指这个学校的人数。这样做可以让 c++ 自动向 0 取整，过滤掉不足 $k$ 人时的情况。
## $CODE$
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x) {
    x = 0;
    register char c = getchar();
    register short f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...temps)
{
	read(x), read(temps...);
}
int t;
int u[200005],v[200005];
vector<int >a[200005];
int ans[200005];
int n,m;
signed main(){
	cin>>t;
	while(t--){
		read(n);
		for(int i=1;i<=n;i++){
			a[i].clear();
			ans[i]=0;//由于多测，要清空数组避免影响答案
			read(u[i]);
		}
		int x;
		for(int i=1;i<=n;i++){
			read(x);
			a[u[i]].push_back(x);//将人和学校对应储存
		}
		for(int i=1;i<=n;i++){
			sort(a[i].begin(),a[i].end(),greater<int>());//从大到小排序
			for(int j=1;j<a[i].size();j++){
				a[i][j]+=a[i][j-1];//直接将原队列变为前缀和
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i].size()){
				int len=a[i].size();
				for(int k=1;k<=len;k++) ans[k]+=a[i][len/k*k-1];//计算贡献
			}
		}
		
		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}

```
谢谢观看。

---

## 作者：Tulip_ (赞：0)

### 题意

每个队伍有 $k$ 个人。这个地区有 $n$ 所学校和 $n$ 个人，每个人有一个水平和一个学籍。水平前 $k$ 的为一个队伍；剩下的人中在选出前 $k$ 的人重复此操作。

### 思路

这道题其实是**结构体存储**，`vector` 动态数组**存储与转移**。

而对于结构体：

将 `a[i].s` 设为水平。

将 `a[i].x` 设为学籍。

既然有了结构体，就少不了排序：

```
inline bool cmp(int x,int y){
	return x>y;
}
```

最后存一个数组 $ans$ 作为**储存答案**。

模拟：

1. 将输入的数据储存到**二维动态数组存图**。

2. 进行**排序和累加**。

3. 统计数组，将答案储存进数组 $ans$。

最后就是输出答案（数组 $ans$）。

### 注意

- 进行模拟时，**记住清空**。

- 输出答案时，**记住换行**。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct mode{
	int s,x;
}a[N];
vector<int>o[N];
int ans[N]={0};
inline bool cmp(int x,int y){
	return x>y;
}
int t,n,m;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
    	cin>>n;
    	for(int i=1;i<=n;i++)o[i].clear(),ans[i]=0;
    	for(int i=1;i<=n;i++)cin>>a[i].x;
    	for(int i=1;i<=n;i++)cin>>a[i].s;
    	for(int i=1;i<=n;i++)o[a[i].x].push_back(a[i].s);
    	for(int i=1;i<=n;i++)
    		if(o[i].size()!=0){
    			sort(o[i].begin(),o[i].end(),cmp);
    			for(int j=1;j<o[i].size();j++)o[i][j]+=o[i][j-1];
    		}
    	for(int i=1;i<=n;i++){
    		if(o[i].size()!=0){
    			int l=o[i].size();
    			for(int j=1;j<=l;j++){
    				if(l/j*j-1<0)continue;
    				ans[j]+=o[i][l/j*j-1];
    			}
    		}
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
		cout<<endl;
    }
	return 0;
}
```

---

