# Vasya and Multisets

## 题目描述

Vasya has a multiset $ s $ consisting of $ n $ integer numbers. Vasya calls some number $ x $ nice if it appears in the multiset exactly once. For example, multiset $ \{1, 1, 2, 3, 3, 3, 4\} $ contains nice numbers $ 2 $ and $ 4 $ .

Vasya wants to split multiset $ s $ into two multisets $ a $ and $ b $ (one of which may be empty) in such a way that the quantity of nice numbers in multiset $ a $ would be the same as the quantity of nice numbers in multiset $ b $ .

## 样例 #1

### 输入

```
4
3 5 7 1
```

### 输出

```
YES
BABA
```

## 样例 #2

### 输入

```
3
3 5 1
```

### 输出

```
NO
```

# 题解

## 作者：傅天宇 (赞：3)

#### 8.4更：更新博客园链接，之前的链接给错了，抱歉。

[在此观看效果更佳~](https://www.cnblogs.com/F-T-Y/p/1500-2000-DP-Greedy.html#t12-1051c-vasya-and-multisets)

## CF1051C 【Vasya and Multisets】

洛谷链接：https://www.luogu.com.cn/problem/CF1051C

CF链接：https://codeforces.com/problemset/problem/1051/C

### 前言：

题解里没有跟我一样的做法，那我就交一篇不一样的吧qwq。

### 题意：

我有一个由 $n$ 个整数组成的多集合。如果它在 $multisets$ 中出现一次，我会调用一些数字为 不错的数字。 例如：$multisets_{1,1,2,3,3,3,4}$ 包含不错的数字 $2$ 和 $4$。

我希望将 $multisets$ 分成两个多重集 $a$ 和 $b$（其中一个可能是空的），使得 $amultisets$ 中的漂亮数字的数量与 $bmultisets$ 中的漂亮数量的数量相同。

### 题解：

因为出现 $1$ 次情况时候是一定是不错的，与答案有关，出现 $2$ 次情况时候只有 $2,0$ 或 $1,1$ ，与答案无关，所以跟出现次数 $\geq 3$ 次情况时候是与答案有关的，可以分为 $1,n-1$。

### Code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
inline void write(int x)
{
    if(x<0) putchar('-'),write(-x);
    else{if(x>9)write(x/10);putchar('0'+x%10);}
}
inline void writeputs(int x){write(x),putchar('\n');}
inline void writeputchar(int x){write(x),putchar(' ');}
int n,a[105],tong[105],ANS,ans;
bool flag;
int main()
{
    n=read();
    FOR(i,1,n) a[i]=read(),tong[a[i]]++;
    FOR(i,1,100)
    {
        if(tong[i]==1) ANS++;
        if(tong[i]>=3) ans++;
    }
    if(ans>=1&&ANS%2==1) flag=1,puts("YES");
    else if(ANS%2==0) puts("YES");
    else 
    {
        puts("NO");
        return 0;
    }
    int num=0;
    if(ANS%2==0)
    {
        FOR(i,1,n) 
        {
            if(tong[a[i]]==1&&num<ANS/2) putchar('A'),num++;
            else putchar('B');
        }
        return 0;
    }
    if(ANS%2==1)
    {
        FOR(i,1,n)
        {
            if(tong[a[i]]==1&&num<=ANS/2-1) putchar('A'),num++;
            else if(tong[a[i]]==1&&num>=ANS/2) putchar('B');
            else if(tong[a[i]]>=3&&flag) putchar('A'),flag=0;
            else putchar('B');
        }
    }
    return 0;
}

```

---

## 作者：Na2PtCl6 (赞：0)

通过观察我们可以发现，$s$ 中出现次数为 $k$ 的数对答案的贡献呈现如下规律：

- $k=1$：能对一个可重集贡献一个 nice number。

- $k=2$：能同时对两个可重集贡献都贡献一个 nice number，或者不对任何一个可重集做贡献，两种情况对答案的影响都是一样的。

- $k\geq3$：能对两个其中一个可重集做贡献或者不对任何一个可重集做贡献。

所以我们只考虑出现次数 $=1,\geq3$ 的数，出现次数分别设为 $c_1,c_3$。如果 $2|c_1$，那么肯定可以完成目标，直接把 $k=1$ 的数对半分，然后其他数堆到一个可重集里就行了。如果 $c_1 \operatorname{mod} 2 =1$，此时如果 $c_3>0$，就用一个 $k\geq3$ 的数来抵消贡献就可以了；否则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
char dv[]={'A','B'},res[104];
int n,once,var,a[104],cnt[104];
vector< int > num[104];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		++cnt[a[i]];
	}
	for(int i=1;i<=n;i++)
		num[cnt[a[i]]].push_back(i);
	for(int i=1;i<=100;i++){
		if(cnt[i]==1)
			++once;
		if(cnt[i]>=3)
			++var;
		
	}
	once%=2;
	if(once==0){
		puts("YES");
		int sw=0;
		for(int i:num[1]){
			res[i]=dv[sw];
			sw^=1;
		}
		for(int i=2;i<=n;i++)
			for(int j:num[i])
				res[j]='B';
		puts(res+1);	
		return 0;
	}
	if(var){
		puts("YES");
		int sw=0;
		for(int i:num[1]){
			res[i]=dv[sw];
			sw^=1;
		}
		vector< int > tmp;
		for(int i=2;i<=n;i++)
			for(int j:num[i])
				tmp.push_back(j);
		res[tmp.back()]='B';
		tmp.pop_back();
		for(int i:tmp)
			res[i]='A';
		puts(res+1);
	}
	else
		puts("NO");
	return 0;
}

```

---

## 作者：Light_Star_RPmax_AFO (赞：0)

# Vasya and Multisets

### 前言

[传送门](https://www.luogu.com.cn/problem/CF1051C)

## 思路

很好想的思路，我们把出现个数的贡献分类讨论一下。

设贡献为 $x$, 一个数的出现个数为 $g_i$：

$$
\left\{  
             \begin{array}{lr}  
                x = 1 & g_i = 1 \\
x = 0 & g_i = 2\\
x = 0 ∨ 1 & g_i \ge 3
             \end{array}  
\right.  
$$

发现一个很特殊的贡献，为什么 $g_i \ge 3$ 时，有 $0$ 和 $1$ 两种不同贡献呢？因为我们可以把 $g_i$ 全部放在集合 $A$ 中，或者把一个放在 $B$ 中，另一些放在 $A$ 中，这样就可以产生 $0$ 或者 $1$ 两种贡献了。

既然贡献出来了，那么如何算可行解呢？

首先我们知道 $(\sum_i [g_i=1])\mid2$ 时是必定可以的，反之，我们需要分类讨论，当 $\sum_i [g_i=3] \ge 1$ 我们可以让一个出现了三次的数贡献变为 $1$，剩下的就是大模拟了。

```cpp
#include <bits/stdc++.h>
#define rint register int
using namespace std;

inline int read(){
  int f = 1,x = 0;
  char ch = getchar();
  while(!isdigit(ch)){
	if(ch == '-')f = -1;
  	ch = getchar();
  }
  while(isdigit(ch)){
  	x = (x << 1) + (x << 3) + (ch ^ 48);
  	ch = getchar();
  }
  return x * f;
}
inline void print(int x){
	if(x > 9)print(x / 10);
  putchar(x % 10 + '0');
}

int a[101], g[101];

signed main(){
	int n = read();
	for(rint i = 1; i <= n; ++i)
		a[g[i] = read()]++;
	rint sum = 0, cnt = 0;
	for(rint i = 1; i <= 100; ++i)
		if(a[i] == 1)sum++;
		else if(a[i] >= 3)cnt++;
	bool ok = 0;
	if(sum & 1)
	{
		if(cnt >= 1)
		{
			puts("YES");
			ok = 1;
			rint num = 0;
			for(rint i = 1; i <= n; ++i)
			{
				if(a[g[i]] == 1 && num <= (sum >> 1))
				{
					putchar('A'), ++num;
				}else
				{
					if(a[g[i]] == 1 && num > (sum >> 1))
					{
						putchar('B'); 
					}else
					{
						if(a[g[i]] >= 3 && ok)
						{
							putchar('B');
							ok = 0;
						}else{
							putchar('A');
						}
					}
				}
			}
		}else
		{
			puts("NO");
			return 0;	
		}
	}else
	{
		puts("YES");
		rint num = 0;
		for(rint i = 1; i <= n; ++i){
			if(a[g[i]] == 1 && num < (sum >> 1))
				putchar('A'), ++num;
			else putchar('B');
		}
	}
  return 0;
}
```




---

## 作者：wuyixiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1051C)

题目大意：给你 $n$ 个数分成两个集合，使得每一个集合的单一数字的个数相同。

经过~~仔细阅读~~，我们可以发现：当 $n$ 个数中，如果一个数只出现了一次，那么它不管在哪一个集合里，那个集合的结果都要加一。很显然这个变量需要均匀分布在两个集合中的。当有偶数个只出现了一次这样的数的时候，将所有的出现次数 $\ge 2$ 的全部放一个集合，而那些均匀分布两个集合即可。但是当奇数个的时候，是否就一定不可行了呢？很显然不是。因为如果一个数的出现次数 $\ge 3$，他可以借一个数给一个数少的那个集合，而这个集合的数量不变。注意当出现次数等于 $2$ 时是不可取的。所以结论就出来了：当只出现了一次的数为奇数且没有出现次数 $\ge 3$ 的时候，没有方案，反之亦然。

附代码：

```cpp
#include <iostream>
using namespace std;
int n,a[10003],b[111],sum,num,sum2,r;
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++)
        cin >> b[i],a[b[i]] ++;//桶计数
    for(int i = 1;i <= 100;i ++)
    {
        if(a[i] == 1)sum ++;
        if(a[i] >= 3)sum2 ++;//判断出现次数有没有大于等于3的
    }
    if(sum % 2 && !sum2)//两个皆不满足输出NO
    {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for(int i = 1;i <= n;i ++)
    {
        if(a[b[i]] == 1)
        {
            if(num < sum / 2)cout << "B";//均匀分布
            else cout << "A";
            num ++;
        }
        else if(a[b[i]] >= 3 && r == 0 && sum % 2)cout << "B",r = 1;//有，则借一个给集合少的，这个else if只能进入一次
        else cout << "A";
    }
    return 0;//输出答案
}
```

---

## 作者：FiraCode (赞：0)

## 题意：
给你 $n$ 个数，一个数是好的当且仅当它只出现了一次，给你一个序列，求是否可以把这个序列分成两组，是的他们好的的数字相同。

## 题解思路：
我们先排序，然后统计每个数字出现的次数，设 $t1$ 为出现 $1$ 次的数的个数，$t2$ 为出现两次的数的个数，$tn$ 表示出现了大于 $2$ 的数的个数。

若他出现以此的数的个数是奇数，并且没有大于 $2$ 的数的个数，那么就无解，输出 `NO`。

否则一定有解输出 `YES`。

然后我们分两种况来讨论，第一种情况是 $t1$ 是偶数，那么若这个块的长度是 $1$ 那么我们用一个 $cnt$ 来计数，若 `cnt == 1` 则把他分给 `A` 否则分给 `B`，然后 `cnt = 1 - cnt`。

否则都给他分给 `A` 或者 `B`。

那么若 $t1$ 是奇数，那么若这个块的长度是 $1$ 那么我们用一个 $cnt$ 来计数，若 `cnt == 1` 则把他分给 `A` 否则分给 `B`，然后 `cnt = 1 - cnt`。

若他的长度是 `2` 就直接都分给 `A` 或 `B`。

否则若是第一次长度 $\ge 3$，若当前的 `cnt == 0` 则第一个就分给 `B` 否则分给 `A`，然后后面的数字都分给 `B` 或 `A`(若上一次选了 `A` 那么后面就该给 `B` 反之亦然)。

然后 `cnt = 1 - cnt`。

若他不是第一次长度 $\ge 3$ 就把他都给 `A` 或者都给 `B`。

## CODE:
~~又臭又长的代码~~
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
pair<int, int> a[N];
int n;
char ans[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);
    int t1 = 0, t2 = 0, tn = 0;
    for (int i = 1; i <= n;) {
        int t = a[i].first;
        int sz = 0;
        int temp = i;
        while (a[i].first == t) {
            i ++;
            sz++;
        }
        if (sz == 1) {
            t1 ++;
        }
        else if (sz == 2) {        
            t2 ++;
        }else {
            tn ++;
        }
    }
    if (t1 & 1) {
        if (!tn) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    if (t1 & 1) {
        int cnt = 0;
        bool ok = false;
        for (int i = 1; i <= n;) {
            int sz = 0;
            int t = a[i].first;
            int id = a[i].second;
            int ttemp = i;
            while(a[i].first == t)
                i ++, sz ++;
            if (sz == 1) {
                if (cnt == 0)
                    ans[id] = 'B';
                else
                    ans[id] = 'A';
                cnt = 1 - cnt;
            }else if (sz == 2) {
                ans[id] = ans[a[ttemp + 1].second] = 'A';
            }else {
                if (!ok) {
                    char c = cnt == 0 ? 'B' : 'A';
                    ans[id] = c;
                    for (int j = 1; j < sz; ++j)
                        ans[a[ttemp + j].second] = c == 'A' ? 'B' : 'A';
                    cnt = 1 - cnt;
                    ok = true;
                }else {
                    for (int j = 1; j <= sz; ++j)
                        ans[a[ttemp + j - 1].second] = 'B';
                }
            }
        }
    }else {
        int cnt = 0;
        bool ok = false;
        for (int i = 1; i <= n;) {
            int sz = 0;
            int t = a[i].first;
            int id = a[i].second;
            int ttemp = i;
            while(a[i].first == t)
                i ++, sz ++;
            if (sz == 1) {
                if (cnt == 0)
                    ans[id] = 'B';
                else
                    ans[id] = 'A';
                cnt = 1 - cnt;
            }else if (sz == 2) {
                ans[id] = ans[a[ttemp + 1].second] = 'A';
            }else {
                for (int j = 1; j <= sz; ++j)
                    ans[a[ttemp + j - 1].second] = 'B';
            }
        }    
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i];
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

简单题，同时也是细节题。
## 思路
不难发现，在原序列中只出现一次的数在划分到两个集合中后也仍然是只出现一次的。

所以我们可以分类讨论，如果这些原序列中只出现一次的数的**个数是偶数**，我们可以把这些数平均分配给集合 $\verb!A!$ 和 $\verb!B!$。剩下的数全都扔给 $\verb!B!$ 即可。

而如果这些原序列中只出现一次的数的**个数是奇数**，我们就需要考虑另外的数。首先我们发现出现次数为 $\verb!2!$ 的数完全没用，因为如果把它们全都划给一个集合或是分别给两个集合，它们对两个集合中“不错的数字”的差值都是没有影响的。而**出现次数 $\verb!>2!$ 的数**则**可以改变差值**，具体就是给一个集合分配 $\verb!1!$ 个，剩下的给另一个集合。

这样这题就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=1e2+10;
int vis[N],vs[N],q[N],x[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (rint i=1;i<=n;++i) cin>>x[i],++vis[x[i]],vs[x[i]]=i;
    vector<int>a,b;
	for (rint i=0;i<=100;++i)
        if (vis[i]==1) a.push_back(vs[i]);
        else if (vis[i]>2) b.push_back(i);
	sort(a.begin(),a.end());
	if (a.size()%2 && !b.size()) return cout<<"NO\n",0;
    cout<<"YES\n";
    for (rint i=0;i<(a.size()>>1);++i) q[a[i]]=1;
    int go=-1;
	if (a.size()%2) go=b[0];
    for (rint i=1;i<=n;++i)
    	if (q[i]) cout<<"A";
    	else if (go!=-1 && x[i]==go) go=-1,cout<<"A";
    	else cout<<"B";
    cout<<'\n';
	return 0;
}
```


---

## 作者：c1910903 (赞：0)

构造题

定义d为a的好数个数-b的好数个数

如果一个数只出现过一次，那么它可以使d±1

如果一个数出现过两次以上，那么它可以使d±1或不变

因此根据两种数的个数的奇偶性判断即可

------------
```cpp
%:pragma GCC optimize "-O3"
#include<iostream>
#include<cstdio>
#define maxn 105
#define maxr 105
using namespace std;
typedef long long ll;
ll n,s[maxn],cnt[maxr],num,num1,num2;
bool f,vis;
inline void _read(ll &x){
	x=0;
    ll f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    x*=f;
    return;
}
inline void _print(ll x){
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>=10)
        _print(x/10);
    putchar(x%10+'0');
    return;
}
int main(){
	_read(n);
	for(ll i=1;i<=n;i++)
	{
		_read(s[i]);
		cnt[s[i]]++;
	}
	for(ll i=1;i<maxr;i++)
		if(cnt[i])
		{
			num++;
			if(cnt[i]==1)
				num1++;
			if(cnt[i]==2)
				num2++;
		}
	if((num1&1)==0)
	{
		cout<<"YES\n";
		for(ll i=1;i<=n;i++)
			if(cnt[s[i]]==1)
			{
				putchar(!f?'A':'B');
				f=!f;
			}
			else
				putchar('A');
	}
	else
	{
		if(num-num2==num1)
			cout<<"NO";
		else
		{
			cout<<"YES\n";
			for(ll i=1;i<=n;i++)
				if(cnt[s[i]]==1)
				{
					putchar(!f?'A':'B');
					f=!f;
				}
				else if(cnt[s[i]]==2)
					putchar('A');
				else if(!vis)
				{
					putchar('B');
					vis=1;
				}
				else
					putchar('A');	
		}
		
	}
	return 0;
}
```

---

## 作者：codeLJH114514 (赞：0)

[Problem](https://codeforces.com/problemset/problem/1051/C)

# Problem

给定一个长度为 $N$ 的整数数组 $S$，你需要把 $S$ 分成两个数组 $A$ 和 $B$，满足 $F(A) = F(B)$。

$F(x)$ 为 $x$ 这个数组内所有只出现一次的数字的个数。

如果无解输出 $\texttt{NO}$，有解输出 $\texttt{YES}$，并输出方案（即对于每一个数组元素都输出在你的方案中这个元素在哪一个数组）。

# Analysis

定义 $G(x) = $ $S$ 中 $x$ 出现的次数。

首先，如果 $G(x) = 2$，那么 $x$ 对于答案**毫无影响**（即无论怎么选答案都不会有任何区别）。

因为如果这种元素只出现了两次，要么两个元素都在同一个数组中，这个数组的 $F$ 没有变化；要么两个元素不在同一个数组中，那么等于 $F(A)$ 和 $F(B)$ 同时加一，对答案也没影响。

那么我们就可以知道无解的条件了：只出现了一次的元素的种数为奇数**并且**没有出现次数 $>2$ 的元素。

因为如果只出现了一次的元素的种数为偶数，那么我们只需要把这些元素一半给 $A$，一半给 $B$，然后把剩下的全部给 $A$ 就行。

如果有出现次数 $>2$ 的元素且只出现了一次的元素的种数为奇数，那么我们可以把出现了一次的元素以 `ABABABA...A` 的顺序分，对于出现次数 $>2$ 的元素：把其中任何一个元素给 $B$，其他全给 $A$，这样也行。

所以当且仅当**只出现了一次的元素的种数为奇数并且没有出现次数 $>2$ 的元素**时，无解。

如果有解，我们直接按照上面给的方法构造就行。

# Coding

如果还不理解就看代码吧。

```cpp
#include <iostream>
#include <set>
#define maxn 128
int N, a[maxn], b[maxn];
char Ans[maxn];
const int M = 100;
int main() {
	std::cin >> N;
	for (int i = 1; i <= N; i++) 
		std::cin >> a[i],
		b[a[i]] += 1;
	int A = 0, B = 0, C = 0;
	for (int i = 1; i <= M; i++) {
		if (b[i] == 1)
			A += 1;
		if (b[i] == 2)
			B += 1;
		if (b[i] > 2)
			C += 1;
	}
	if (A % 2 == 1 and C == 0)
		std::cout << "NO\n";
	else {
		std::cout << "YES\n";
		if (A % 2 == 0) {
			int Multiset = 0;
			for (int i = 1; i <= N; i++)
				if (b[a[i]] == 1)
					Ans[i] = Multiset + 'A',
					Multiset = 1 - Multiset;
				else Ans[i] = 'A';
		} else {
			int Multiset = 0;
			for (int i = 1; i <= N; i++)
				if (b[a[i]] == 1)
					Ans[i] = Multiset + 'A',
					Multiset = 1 - Multiset;
				else if (b[a[i]] == 2)
					Ans[i] = 'A';
			std::set<int> S;
			for (int i = 1; i <= N; i++)
				if (b[a[i]] > 2)
					S.insert(a[i]);
			int Stage = false;
			for (int i = 1; i <= N; i++)
				if (b[a[i]] > 2) 
					if (a[i] == *S.begin() and not Stage)
						Ans[i] = 'B',
						Stage = true;
					else
						Ans[i] = 'A';
		}
		for (int i = 1; i <= N; i++)
			std::cout << Ans[i] << (i == N ? "\n" : "");
	}
	return 0;
} 
```

因为 Luogu CF RMJ 炸了，所以给一个 AC 证明：[Accepted](https://codeforces.com/contest/1051/submission/182105186)。

---

