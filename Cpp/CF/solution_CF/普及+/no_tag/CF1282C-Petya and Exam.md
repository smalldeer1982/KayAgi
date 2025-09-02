# Petya and Exam

## 题目描述

Petya has come to the math exam and wants to solve as many problems as possible. He prepared and carefully studied the rules by which the exam passes.

The exam consists of $ n $ problems that can be solved in $ T $ minutes. Thus, the exam begins at time $ 0 $ and ends at time $ T $ . Petya can leave the exam at any integer time from $ 0 $ to $ T $ , inclusive.

All problems are divided into two types:

- easy problems — Petya takes exactly $ a $ minutes to solve any easy problem;
- hard problems — Petya takes exactly $ b $ minutes ( $ b > a $ ) to solve any hard problem.

Thus, if Petya starts solving an easy problem at time $ x $ , then it will be solved at time $ x+a $ . Similarly, if at a time $ x $ Petya starts to solve a hard problem, then it will be solved at time $ x+b $ .

For every problem, Petya knows if it is easy or hard. Also, for each problem is determined time $ t_i $ ( $ 0 \le t_i \le T $ ) at which it will become mandatory (required). If Petya leaves the exam at time $ s $ and there is such a problem $ i $ that $ t_i \le s $ and he didn't solve it, then he will receive $ 0 $ points for the whole exam. Otherwise (i.e if he has solved all such problems for which $ t_i \le s $ ) he will receive a number of points equal to the number of solved problems. Note that leaving at time $ s $ Petya can have both "mandatory" and "non-mandatory" problems solved.

For example, if $ n=2 $ , $ T=5 $ , $ a=2 $ , $ b=3 $ , the first problem is hard and $ t_1=3 $ and the second problem is easy and $ t_2=2 $ . Then:

- if he leaves at time $ s=0 $ , then he will receive $ 0 $ points since he will not have time to solve any problems;
- if he leaves at time $ s=1 $ , he will receive $ 0 $ points since he will not have time to solve any problems;
- if he leaves at time $ s=2 $ , then he can get a $ 1 $ point by solving the problem with the number $ 2 $ (it must be solved in the range from $ 0 $ to $ 2 $ );
- if he leaves at time $ s=3 $ , then he will receive $ 0 $ points since at this moment both problems will be mandatory, but he will not be able to solve both of them;
- if he leaves at time $ s=4 $ , then he will receive $ 0 $ points since at this moment both problems will be mandatory, but he will not be able to solve both of them;
- if he leaves at time $ s=5 $ , then he can get $ 2 $ points by solving all problems.

Thus, the answer to this test is $ 2 $ .

Help Petya to determine the maximal number of points that he can receive, before leaving the exam.

## 样例 #1

### 输入

```
10
3 5 1 3
0 0 1
2 1 4
2 5 2 3
1 0
3 2
1 20 2 4
0
16
6 20 2 5
1 1 0 1 0 0
0 8 2 9 11 6
4 16 3 6
1 0 1 1
8 3 5 6
6 20 3 6
0 1 0 0 1 0
20 11 3 20 16 17
7 17 1 6
1 1 0 1 0 0 0
1 7 0 11 10 15 10
6 17 2 6
0 0 1 0 0 1
7 6 3 7 10 12
5 17 2 5
1 1 1 1 0
17 11 10 6 4
1 1 1 2
0
1
```

### 输出

```
3
2
1
0
1
4
0
1
2
1
```

# 题解

## 作者：Erica_N_Contina (赞：1)

好吧其实本题可以贪心地去做。

我们考虑到我们在某个 $t_i-1$ 或者 $T$ 时交卷是最优的。

所以我们可以从前往后扫描每一个时间点 $t_i$，设当前交卷时间为 $t_i-1$，每次扫描到一个时间点 $t_i$ 就把新的必答题（第 $i-1$ 道题目）添加进来。

我们用一个变量 $bit$ 记录当前完成所有必答题需要的时间，枚举到 $i$ 时，即在 $t_i-1$ 时交卷，我们就把 $bit$ 加上 $i-1$ 题对应的用时，判断是否可以完成所有必答题。如果可以，则考虑空余时间（空余时间即 $t_i-1-bit$）。

我们可以 $O(1)$ 计算出空余时间可以做几道题，因为本题中完成题目的所需时间是固定的且只有两种情况。我们优先做简单题，然后如果还有多的时间就去做复杂题。最后求出当前时间交卷可以完成多少题目，尝试更新答案。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

struct node{
	int t,p;
}e[N];
int n,m,p,q,T,s[N],ans;
int cnt[2],a,b;

bool cmp(node a,node b){
	return a.t<b.t;
}

void solve(){
	cnt[1]=cnt[0]=0;
	ans=0;
	
	scanf("%lld%lld%lld%lld",&n,&T,&a,&b);
	for(int i=1;i<=n;i++)scanf("%lld",&e[i].p),cnt[e[i].p]++;
	for(int i=1;i<=n;i++)scanf("%lld",&e[i].t);
	
	sort(e+1,e+n+1,cmp);
	
	int bit=0;//必做题用时 
	for(int i=1;i<=n+1;i++){
		int tm=e[i].t-1;
		if(i==n+1)tm=T;
		
		if(i-1)bit+=e[i-1].p?b:a;
		if(i-1)cnt[e[i-1].p]--;
		
		if(tm>=bit){
			tm-=bit;//剩余时间 优先分配给a后给b 
			int tpa=tm/a;
			tpa=min(tpa,cnt[0]);
			int tpb=(tm-tpa*a)/b;
			ans=max(ans,i-1+min(cnt[1],tpb)+tpa);
		}
		
	}
	
	cout<<ans<<endl;
}

signed main(){
	
	cin>>m;
	while(m--){
		solve();
	}
	
	return 0;
}


```




---

## 作者：liuyz11 (赞：1)

# 题解 CF1282C 【Petya and Exam】

该场比赛题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12173579.html)

题目大意：Petya将会参加一场考试，这场考试从时间点0开始，到T结束。考试中有n道题，分为两种，简单（需要花a时间做完）的题和困难（需要花b时间做完）的题（a <= b），即在时间点x开始做这道题，将会在x+a或x+b时间点完成。现在每道题会在时间点 ti 变成必须完成，Petya可以在0 ~ T任意一个时间点离开，若离开时有必须要完成的题目没有完成，他将会得到0分，否则会得到他完成的题目的分数。求他最大能得到的分数。

我们可以得到一个贪心策略，若是在时间点i离开且i+1没有必须要完成的题目，那么在i点离开肯定不如在i+1时间点离开，所以我们只要比较所有 ti - 1 离开能得到的最大分数。

只需要将时间点 ti 排序以后，即可记录下当时需要完成的题目和所要花的时间。

另外，对于每一个点，在完成所有需要完成的题目后，肯定要先去做简单的题目，若还有时间再去做困难的题目。

代码如下:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

pii pro[MAXN];
int num[MAXN];

int main(){
	int q;
	scanf("%d", &q);
	rep(times, 1, q){
		int n, T, a, b;
		scanf("%d%d%d%d", &n, &T, &a, &b);
		int tot0 = 0, tot1 = 0;
		rep(i, 1, n){
			scanf("%d", &num[i]);
			if(!num[i]) tot0++;
			else tot1++;
		}
		rep(i, 1, n){
			int x;
			scanf("%d", &x);
			pro[i] = mp(x, num[i]);
		}
		pro[++n] = mp(T + 1, 0);
		sort(pro + 1, pro + n + 1);
		int ans = 0, sta0 = 0, sta1 = 0;
		rep(i, 1, n){
			if(sta0 > T) break;
			if(pro[i - 1].fi != pro[i].fi){
				int tim = pro[i].fi - 1;
				tim -= sta0;
				int res = sta1;
				if(tim >= 0){
					res += min(tim / a, tot0);
					tim -= min(tim / a, tot0) * a;
					res += min(tim / b, tot1);
					ans = max(ans, res);
				}
			}
			if(pro[i].se){
				tot1--;
				sta0 += b;
			}
			else{
				tot0--;
				sta0 += a;
			}
			sta1++;
		}
		printf("%d\n", ans);
	}
    return 0;
}
```

---

## 作者：lucifer1004 (赞：1)

### Petya and Exam

[Codeforces-1282C](https://codeforces.com/problemset/problem/1282/C)

#### 题目大意

Petya参加考试，这场考试一共有$n$道题目，考试的总时长是$T$。题目一共有两种：简单的和困难的。Petya做一道简单的题目要花的时间是$a$，做一道困难的题目要花的时间是$b$（$a<b$）。

每道题目都有一个关键时间$t_i$，意思是，从$t_i$时刻起，这道题目将变成必答题。Petya每做完一道题目可以得1分，并且可以在任意时刻交卷。但如果在Petya交卷时，有必答题没做完，他的成绩就是0分。

问：Petya最多能得多少分？

#### 题目分析

因为在每个$t_i$时刻会有新的题目变成必答题，因此最佳的交卷时间一定是某个$t_i-1$，或者是$T$。

因此，我们可以对时间进行离散化。需要保留的时间点为所有的$t_i$，$t_i-1$以及$T$。接下来，我们就可以使用扫描算法，从前向后处理每个时间点。在每个时间点，如果有新的题目变为必答题，我们先将其加入。然后，我们检查在当前时间点是否能完成所有必答题。如果能完成，我们再做其他的题目，先做简单的，再做困难的。这样，我们就能得到这个时间点交卷的最高得分。

检查完所有时间点后，我们就能找到最优解。

#### 参考代码（Python）

```python
m = int(input())
for case_num in range(m):
    n, T, a, b = map(int, input().split(' '))
    d = list(map(int, input().split(' ')))
    t = list(map(int, input().split(' ')))
    critical = set()
    for ti in t:
        critical.add(ti)
        if ti >= 1:
            critical.add(ti - 1)
    critical.add(T)
    critical = list(critical)
    critical.sort()
    k = len(critical)
    lut = dict()
    for i in range(k):
        lut[critical[i]] = i
    easy = [0 for i in range(k)]
    hard = [0 for i in range(k)]
    for i in range(n):
        idx = lut[t[i]]
        if d[i] == 0:
            easy[idx] += 1
        else:
            hard[idx] += 1
    mandatory_easy = 0
    mandatory_hard = 0
    total_hard = sum(d)
    total_easy = n - total_hard
    ans = 0
    for i in range(k):
        mandatory_easy += easy[i]
        mandatory_hard += hard[i]
        time = critical[i] - mandatory_easy * a - mandatory_hard * b
        if time < 0:
            continue
        rest_easy = total_easy - mandatory_easy
        extra_easy = min(time // a, rest_easy)
        time -= extra_easy * a
        rest_hard = total_hard - mandatory_hard
        extra_hard = min(time // b, rest_hard)
        score = mandatory_easy + mandatory_hard + extra_easy + extra_hard
        ans = max(ans, score)
    print(ans)
```

---

## 作者：_Lazy_whr_ (赞：0)

本题使用贪心。

首先我们要对每道题最晚完成的时间（即每道题的时间限制）从小到大排序，接着需要记录当前的时间。

其次，我们发现最佳的交卷时间肯定位于 $t_i - 1$ 或 $T$ 时刻。

所以我们枚举每一道题目，显而易见的是如果这道题的时间限制大于目前的时间，那么前 $i$ 道题可做，接下来剩余的时间就可以全部拿来做简单题。

解释一件事情，有些人可能不明白为什么剩下的时间只做简单题而不做难题。因为随着 $i$ 的枚举，如果当前的 $i$ 满足有难题能做，那后面的 $i$ 也会满足能做这道难题，就避免了少算的问题。

~~其实是一开始忘了然后懒得写~~

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define x0 x00
#define x1 x10
#define y0 y00
#define y1 y10
#define rep(i, l, r, x) for (int i = l; i <= r; i += x)
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
//#pragma GCC target("avx")
//#pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	
	template <typename T> inline void read (T &x) {
		x = read();
	}
	
	template <typename T, typename... Args> inline void read (T &x, Args &...x_) {
		read (x);
		read (x_...);
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = acos (-1);
}

using namespace std;
using namespace FastIO;
using namespace Constants;

struct Problem {
	int dif, lim;
	bool operator < (const Problem &cmp) const {
		return lim < cmp.lim;
	}
};

int n, a, b, T;
Problem p[200010];

main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	int Test = read();
	while (Test--) {
		read(n, T, a, b);
		for (int i = 1; i <= n; i++) read(p[i].dif);
		for (int i = 1; i <= n; i++) read(p[i].lim);
		sort(p + 1, p + 1 + n);
		
		int easy = 0, hard = 0;
		for (int i = 1; i <= n; i++) {
			if (p[i].dif == 0) easy++;
			else hard++;
		}
		
		int now = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			if (p[i].lim > now) ans = max(ans, i + min((p[i].lim - now - 1) / a, easy) - 1); // 剩下的时间就多做简单题放松身心
			if (p[i].dif == 0) {now += a; easy--; } // 注意，简单题少了一道
			else {now += b; hard--; }
		}
		if (now <= T) ans = n; // 如果最后没有到达 T，说明都能做出来
		cout << ans << endl;
	}

	return 0;
}

```

---

## 作者：ivyjiao (赞：0)

来源：CF 决斗场。

被 1800 杀了，丢人。

首先我们可以想到把所有题目按照必须要做的时间排序。

其次我们可以想到：最佳交卷时间一定是 $t_i-1$ 或 $T$，就算时间有空余也不影响。

设我们做前 $i$ 道题用了 $cnt$ 分钟，那么若 $t_{i+1}>cnt$，则前 $i$ 道题可以做，然后我们还有空余时间，我们可以在里面穿插一些简单题，记录一下简单题剩余的数量就行，把这个数与剩余时间还能做简单题的数量取 $\min$。

最后判断一下如果能够全做，那答案就是 $n$。

记得开 long long。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int N=2e5+1;
int T,n,m,a,b,cnt,cnt1,cnt2,ans;
pair<int,bool>t[N];
signed main(){
    cin>>T;
    while(T--){
        cnt=0,ans=0;
        cnt1=0,cnt2=0;
        cin>>n>>m>>a>>b;
        for(int i=1;i<=n;i++) cin>>t[i].se,cnt1+=t[i].se;
        cnt2=n-cnt1;
        for(int i=1;i<=n;i++) cin>>t[i].fi;
        sort(t+1,t+1+n);
        for(int i=1;i<=n;i++){
            if(t[i].fi>cnt){
                ans=max(ans,i-1);
                ans=max(ans,i-1+min((t[i].fi-1-cnt)/a,cnt2));
            }
            if(t[i].se==0) cnt+=a,cnt2--;
            else cnt+=b;
        }
        if(cnt<=m) ans=n;
        cout<<ans<<endl;
    }
}
```

---

