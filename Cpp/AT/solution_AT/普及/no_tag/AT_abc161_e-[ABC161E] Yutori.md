# [ABC161E] Yutori

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc161/tasks/abc161_e

高橋君は明日からの $ N $ 日間のうち $ K $ 日を選んで働くことにしました。

整数 $ C $ と文字列 $ S $ が与えられるので、次の $ 2 $ つの条件を満たすようにして働く日を選びます。

- ある日働いたら、その直後の $ C $ 日間は働かない
- $ S $ の $ i $ 文字目が `x` のとき、今日から $ i $ 日後には働かない

高橋君が必ず働く日をすべて求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N $
- $ 0\ \leq\ C\ \leq\ N $
- $ S $ の長さは $ N $
- $ S $ の各文字は `o` か `x`
- 問題文中の条件を満たすように働く日を選ぶことが可能

### Sample Explanation 1

高橋君は $ 11 $ 日間のうち $ 3 $ 日働こうとしています。ある日働いたらその後 $ 2 $ 日間は働きません。 働く日としてありえる組み合わせは「$ 1,6,10 $ 日目」「$ 1,6,11 $ 日目」「$ 2,6,10 $ 日目」「$ 2,6,11 $ 日目」の $ 4 $ 通りです。 したがって、$ 6 $ 日目に必ず働きます。

### Sample Explanation 2

働く日としてありえる組み合わせは「$ 1,5 $ 日目」のみです。

### Sample Explanation 3

必ず働く日が存在しないこともあります。

## 样例 #1

### 输入

```
11 3 2
ooxxxoxxxoo```

### 输出

```
6```

## 样例 #2

### 输入

```
5 2 3
ooxoo```

### 输出

```
1
5```

## 样例 #3

### 输入

```
5 1 0
ooooo```

### 输出

```
```

## 样例 #4

### 输入

```
16 4 3
ooxxoxoxxxoxoxxo```

### 输出

```
11
16```

# 题解

## 作者：SpeedStar (赞：6)

## 算法分析
为了使某个时段的工作日数最大化，最好贪婪地确定工作日。 因此，通过考虑从头到尾贪婪地确定工作日，我们可以得到一个数组$L$，使得“第$x$个工作日不早于$L [x]$天”。类似地，通过考虑从头到尾贪婪地确定工作日，我们可以得到一个数组$R$，使得“第$x$个工作日不晚于$R [x]$”。当且仅当存在$x$使得$L [x] = R [x] = i$时，高桥才能在第$i$天工作，因此可以在$O(N)$的时间内解决该问题。


## C++代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k, c;
	cin >> n >> k >> c;
	string s;
	cin >> s;
	
	vector<int> L, R;
	int t = 1e9;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'o' && t >= c) {
			L.push_back(i);
			t = 0;
		}
		else t++;
		if (L.size() == k) break;
	}
	
	t = 1e9;
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == 'o' && t >= c) {
			R.push_back(i);
			t = 0;
		}
		else t++;
		if (R.size() == k) break;
	}
	
	reverse(R.begin(), R.end());
	for (int i = 0; i < k; i++) {
		if (L[i] == R[i]) cout << L[i] + 1 << '\n';
	}
	
	return 0;
}
```


---

## 作者：fighter (赞：4)

首先如果可以工作的天数>k的话，肯定每天都不需要强制工作

接着考虑通过贪心求出第$i$次工作最早和最晚的时间。

具体就是从前往后扫，能工作就工作，这样每个工作一定最早的。我们把每个工作最早开始的时间记为$l[i]$

同理，倒着扫一遍就可以求出每个工作最迟开始的时间，记为$r[i]$。

那么接下来很简单，如果一天需要强制工作，那么这个工作一定时只能在这个时间开始，即$l[i]=r[i]$。

所以最后线性判断一下就好了。复杂度$O(n)$。

```cpp
#include <bits/stdc++.h>
#define MAX 500005
#define ll long long
using namespace std;

int n, m, c, t;
int l[MAX], r[MAX];
char s[MAX];

int main() {
    cin >> n >> m >> c;
    scanf("%s", s+1);
    int now = -c-1, cnt = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] == 'x' || i-now < c+1) continue;
        l[++cnt] = i, now = i;
    }
    now = n+c+1;
    if(cnt > m) return 0;
    t = cnt;
    for(int i = n; i >= 1; i--){
        if(s[i] == 'x' || now-i < c+1) continue;
        r[cnt--] = i, now = i;
    }
    for(int i = 1; i <= t; i++){
        if(l[i] == r[i]) printf("%d\n", l[i]);
    }

    return 0;
}
```

---

## 作者：Alexandra (赞：3)

## 题目大意
一共有 $n$ 天，高桥君打算从其中选 $k$ 天工作，他的要求：  
1. 只有 $S_i$ 为 $o$，高桥君才有可能选择在第 $i$ 天上班。  
2. 高桥君工作后会**连续**休息 $c$ 天。

求出在哪些天他**不得不**工作以达到在 $n$ 天中**恰好**工作 $k$ 天的要求。



## 题目思路
先从前向后枚举每一天，贪心的计算第 $i$ 天工作的情况下，到第 $i$ 天前**最多**可以工作天数 $l_i$。  
同理，从后向前求出第 $i$ 天工作的情况下，此后最多可以工作天数 $r_i$。  

当 $l_i+r_i+1=k$ 时，说明第 $i$ 天时不得不选择的。



## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 200100
#define INF 0x3f3f3f3f3f3f3f3f
long long l[N],r[N],n,k,c,p,q;
char s[N];
int main ()
{
	scanf("%lld%lld%lld",&n,&k,&c);
	cin>>s+1;
	p=-INF;
	for(long long i=1;i<=n;i++)
	{
		l[i]=l[i-1];
		if(s[i]=='o'&&i-p>=c+1)l[i]++,p=i;
	}
	q=INF;
	for(long long i=n;i>=1;i--)
	{
		r[i]=r[i+1];
		if(s[i]=='o'&&q-i>=c+1)r[i]++,q=i;
	}
	for(long long i=1;i<=n;i++)
	{
		if(s[i]=='o'&&l[i-1]+r[i+1]+1==k)printf("%lld\n",i);
	}
	return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc161_e)

## 思路

这道题我们考虑用贪心来做。

贪心确定每段工作日。对于第 $i$ 段工作日，日期是从 $l_i$ 到 $r_i$。用正序循环枚举每个 $l_i$，并在找到 $K$ 个工作日左端点后退出循环。之后再用倒序循环枚举每个 $r_i$，并在找到 $K$ 个工作日右端点后退出循环。然后从小到大排序 $r$（因为现在是从大到小贪心后的结果），每次找到一组相等的 $l_i$ 和 $r_i$，输出 $l_i+1$（$+1$ 是因为字符串输入后下标从 $0$ 开始）。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>l,r;//vector 数组更省空间
int n,k,c;
string s;
int main(){
    cin>>n>>k>>c>>s;
    int tmp=c;
    /*tmp 为连续的工作日天数，要赋初始值为 c，保证第一次贪心就能选中。*/
    for(int i=0;i<n;++i){
        if(s[i]=='o'&&tmp>=c){
            tmp=0;
            l.push_back(i+1);//这里 i+1 下面输出时就可以不加了。
        }
        else tmp++;
        if(l.size()==k)break;
    }
    tmp=c;//tmp 再次赋值
    for(int i=n-1;i>=0;--i){
        if(s[i]=='o'&&tmp>=c){
            tmp=0;
            r.push_back(i+1);
        }
        else tmp++;
        if(r.size()==k)break;
    }
    sort(r.begin(),r.end());//vector 数组排序需要这样写。
    for(int i=0;i<k;++i){
        if(l[i]==r[i])cout<<l[i]<<endl;
    }
    return 0;
}
~~~

[成功 AC](https://www.luogu.com.cn/record/96131934)

---

## 作者：xiaomuyun (赞：0)

- [Luogu 传送门](https://www.luogu.com.cn/problem/AT_abc161_e)
- [Atcoder 传送门](https://atcoder.jp/contests/abc161/tasks/abc161_e)

## 思路分析

因为需要求的是那些天 **一定** 要工作，所以有一些可以今天做也可以明天做的那些工作不算进答案里。

那我们如何判断一次工作一定要在这一天进行呢？不难想到，我们可以求出每次工作在什么时间段内需要做完，如果这个时间段只有 $1$ 天的话，就说明这次工作是一定要在这一天做的。

## 代码实现

具体地，我们对于第 $i$ 次工作（$1\le i\le k$），分别求出 $l_i$ 和 $r_i$，表示这次工作要在什么时间段内做完。

实现起来很简单，如果是求 $l$ 的话，就从 $1$ 到 $n$ 搜，如果第 $i$ 天（$i\in[1,n]$）可以进行工作（即不是 `x`）而且距离上一次工作的时间（即 $l_{i-1}$）**大于** $c$，那么如果这次工作是第 $j$ 次工作的话，就可以使 $l_j=i$ 了。求 $r$ 也差不多，只不过是倒着搜而已。

还要注意一个地方：就是如果求 $l$ 和 $r$ 的时候，已经求完 $k$ 次工作了，就要及时 `break` 掉，不然会出一些奇奇怪怪的错误。

```cpp
#include<iostream>
#include<string>
using namespace std;
const int maxn = 2e5 + 1;
int n, k, c, lres[maxn], rres[maxn];
string s;
int main() {
	cin >> n >> k >> c >> s;
	s = "#" + s;
	for (int i = 1, cur = 214514; i <= n; ++i, ++cur) {
		if (cur <= c || s[i] != 'o') continue;
		lres[++lres[0]] = i, cur = 0;
		if (lres[0] == k) break;//很重要
	}
	rres[0] = k + 1;
	for (int i = n, cur = 214514; i >= 1; --i, ++cur) {//倒着搜
		if (cur <= c || s[i] != 'o') continue;
		rres[--rres[0]] = i, cur = 0;
		if (k - rres[0] + 1 == k) break;
	}
	for (int i = 1; i <= k; ++i) {
		if (lres[i] == rres[i]) cout << lres[i] << '\n';
	}
	return 0;
}
```

---

## 作者：LJB00131 (赞：0)

[blog](https://www.cnblogs.com/LJB00131/p/12634775.html)内食用更佳

本次比赛最难的题，但是实际上也很简单.

考虑"一定要工作的天"，其实就是"不工作就不能完成的天"。再发现如果我们要让他工作最多天(不管K的限制)，一定是能工作就工作最优。所以我们正着算一遍，反着算一遍，再判断一下这天不工作是否正反加起来小于k。小于k的就是我们要求的天。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 200005

int n, k, c, maxn[N], f[N], g[N], p[N];

char s[N];

bool is[N];

int main()
{
	scanf("%d%d%d", &n, &k, &c);
	scanf("%s", (s + 1));
	for(int i = 1; i <= n; i++)
		if(s[i] == 'x')
		{
			is[i] = 1;
		}
	for(int i = 1; i <= n; i++)
	{
		maxn[i] = maxn[i - 1];
		f[i] = f[i - 1];
		if(i > maxn[i] && !is[i]) 
		{
			f[i]++;
			maxn[i] = i + c;
		}
	}
	p[n + 1] = n + 1;
	for(int i = n; i >= 1; i--)
	{
		g[i] = g[i + 1];
		p[i] = p[i + 1];
		if(i < p[i] && !is[i]) 
		{
			g[i]++;
			p[i] = i - c;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		// cout << i << ' ' << f[i] << ' ' << g[i] << endl;
		if(!is[i])
		{
			if(f[i - 1] + g[max(maxn[i - 1] + 1, i + 1)] < k)
			{
				printf("%d\n", i);
			}
		}
	}
	printf("\n");
	return 0;
}
```

---

## 作者：Sqrtyz (赞：0)

一道有一点思维含量的题目。考试时因为时间不够（都用来划水了），没有做这道题（当时看 F 题 AC 人数更多就先做的 F）。

一个 Tag：贪心。其实这道题不是很难，问题是需要保持头脑清醒并理性转化问题。

考虑令 $L[i]$ 表示前 $i$ 天最多可以安排多少工作日，$R[i]$ 表示后 $i$ 天最多可以安排多少工作日。

这个 $L[i]$ 和 $R[i]$ 可以显然地用贪心求出，细节可以康代码，这里便不再赘述。

对于第 $i$ 天必须成为工作日的条件就是 $L[i-1]+R[i+1]+1=K$，这个不难理解。这么想：前 $i-1$ 天最多工作 $L[i-1]$ 天，后 $i+1$ 天最多工作 $R[i+1]$ 天。这两边做到极致，如果都无法完成 $K$ 天的任务，那么就必须让第 $i$ 天参与工作。反之我们总有方案使得第 $i$ 天不用工作。

其实这个解法有一个小瑕疵——前 $i-1$ 天工作的 $L[i-1]$ 天中，可能有某一天与第 $i$ 天的距离小于等于 $C$，按理说这样第 $i$ 天便不能参与工作，此题无解。但显然这道题默认是有解的，恰好规避了这种情况，减少了我们的讨论。

细节请移步代码。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define Maxn 200010

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') f = -1;
        c = getchar();
    }
    while('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

int n, k, c, l[Maxn], r[Maxn];
char ch[Maxn];

int main() {
    n = read(); k = read(); c = read();
    scanf(" %s", ch + 1);
    int j = 0;
    for(int i = 1; i <= n; ++i) {
        if(ch[i] == 'o' && i > j) {
            l[i] = l[i - 1] + 1;
            j = i + c;
        }
        else l[i] = l[i - 1];
    }
    j = n + 1;
    for(int i = n; i; --i) {
        if(ch[i] == 'o' && i < j) {
            r[i] = r[i + 1] + 1;
            j = i - c;
        }
        else r[i] = r[i + 1];
    }
    for(int i = 1; i <= n; ++i) {
        if(ch[i] == 'o' && l[i - 1] + r[i + 1] + 1 == k) printf("%d\n", i);
    }
    return 0;
}
```

---

## 作者：iiawaKL (赞：0)

这题想起来很难，但是其实不然。

很简单地想，可以从左边开始，枚举一遍，然后再从右边开始枚举一遍，都没被打到的点就算入答案。

不多说，我赶紧上代码。

 _Code->_ 
 
 ```
#include <bits/stdc++.h>
#define MAXN 500005
#define ll long long
using namespace std;
int n,m,c,t;
int l[MAXN],r[MAXN];
char s[MAXN];
int main() {
    cin>>n>>m>>c;
    scanf("%s",s+1);
    int now=-c-1,cnt=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='x'||i-now<c+1)continue;
        l[++cnt]=i,now=i;
    }
    now=n+c+1;
    if(cnt>m)return 0;
    t=cnt;
    for(int i=n;i>=1;i--){
        if(s[i]=='x'||now-i<c+1)continue;
        r[cnt--]=i,now=i;
    }
    for(int i=1;i<=t;i++){
        if(l[i]==r[i])cout<<l[i]<<endl;
    }
   return 0;
}

```


---

