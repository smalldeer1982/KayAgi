# [ABC343D] Diversity of Scores

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_d

高橋君が主催するコンテストに、$ 1 $ から $ N $ までの番号が付けられた $ N $ 人の選手が参加しています。 このコンテストは各選手がその得点を競うものであり、現在の得点はどの選手も $ 0 $ 点です。

未来予知の能力を持つ高橋君は、今から選手たちの得点がどのように変動するかを知っています。 具体的には、$ i=1,2,\dots,T $ について、今から $ i $ 秒後に選手 $ A_i $ の得点が $ B_i $ 点増加します。 逆に、それ以外に得点の変動はありません。

得点の多様性を好む高橋君は、各時点における選手たちの得点に何種類の値が現れるかを知りたがっています。 $ i=1,2,\dots,T $ それぞれについて、今から $ i+0.5 $ 秒後の選手たちの得点には何種類の値が現れるか求めてください。

例えば、ある時点における選手たちの得点がそれぞれ $ 10,20,30,20 $ 点であった場合、この時点での選手たちの得点には $ 3 $ 種類の値が現れています。

## 说明/提示

### 制約

- $ 1\leq\ N,\ T\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ N $
- $ 1\leq\ B_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

選手 $ 1,2,3 $ の得点をこの順に並べた数列を $ S $ とします。 現在、$ S=\lbrace\ 0,0,0\rbrace $ です。 - $ 1 $ 秒後に選手 $ 1 $ の得点が $ 10 $ 点増加し、$ S=\lbrace\ 10,0,0\rbrace $ になります。よって、$ 1.5 $ 秒後の選手たちの得点には $ 2 $ 種類の値が現れます。 - $ 2 $ 秒後に選手 $ 3 $ の得点が $ 20 $ 点増加し、$ S=\lbrace\ 10,0,20\rbrace $ になります。よって、$ 2.5 $ 秒後の選手たちの得点には $ 3 $ 種類の値が現れます。 - $ 3 $ 秒後に選手 $ 2 $ の得点が $ 10 $ 点増加し、$ S=\lbrace\ 10,10,20\rbrace $ になります。よって、$ 3.5 $ 秒後の選手たちの得点には $ 2 $ 種類の値が現れます。 - $ 4 $ 秒後に選手 $ 2 $ の得点が $ 10 $ 点増加し、$ S=\lbrace\ 10,20,20\rbrace $ になります。よって、$ 4.5 $ 秒後の選手たちの得点には $ 2 $ 種類の値が現れます。

## 样例 #1

### 输入

```
3 4
1 10
3 20
2 10
2 10```

### 输出

```
2
3
2
2```

## 样例 #2

### 输入

```
1 3
1 3
1 4
1 3```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
10 10
7 2620
9 2620
8 3375
1 3375
6 1395
5 1395
6 2923
10 3375
9 5929
5 1225```

### 输出

```
2
2
3
3
4
4
5
5
6
5```

# 题解

## 作者：Little_x_starTYJ (赞：7)

### 解题思路
首先，我们思考用一个数组存储每个分数的出现次数，但是数据范围中，$1\le B_i \le 10^9$，很明显，会爆空间，于是我们就用 `map` 存储。既然统计的问题解决了，那统计不同的分数的个数怎么办呢？总不可能暴力吧？由于最开始时，大家的分数都为 $0$，而每次修改时只有一个数，所以我们定义一个变量初始为 $1$，然后再判断该分数是否出现，动态维护不同的分数的个数即可。

我们用一个 `map` 统计该分数的出现次数，再用一个数组统计每位选手的分数，对于每次操作，我们先减去原分数出现的次数，然后用一个变量动态维护统计不同的分数的个数，最后再修改分数与其出现次数即可。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010], b[200010], c[200010];
map<int, int> m;
int number = 1;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, t;
	cin >> n >> t;
	for (int i = 1; i <= t; i++) {
		cin >> a[i] >> b[i];
	}
	m[0] += n;
	for (int i = 1; i <= t; i++) {
		m[c[a[i]]]--;
		if (m[c[a[i]]] == 0)
			number--;
		c[a[i]] += b[i];
		m[c[a[i]]]++;
		if (m[c[a[i]]] == 1)
			number++;
		cout << number << endl;
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：3)

## 题意
有 $N$ 个人的分数，共有 $T$ 次操作，每次增加一个人的分数，在每次操作后输出有多少种不同的分数。

## 思路
我们可以使用 `map` 或 `unordered_map` 来保存每种分数的个数。最初，分数 $0$ 会有 $N$ 个；每一次操作之后，就将被操作人原来分数的个数减掉 $1$（如果为 $0$ 就 `erase` 掉这个分数），修改后分数的个数加上 $1$。在每次操作后输出 `map` 或 `unordered_map` 的长度即可。

## 代码
下面是我赛时用 `unordered_map` 写的。
```cpp
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , t ;

ll a [N] , b [N] , s [N] ;

unordered_map <ll,ll> cnt ;

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> t ;
	cnt [0] = n ;
	for ( ll i = 1 ; i <= t ; i ++ )
	{
		cin >> a [i] >> b [i] ;
		cnt[s [a [i]]] -- ;
		if ( ! cnt [s [a [i]]] )
		{
			cnt.erase ( s [a [i]] ) ;
		}
		s [a [i]] += b [i] ;
		cnt [s [a [i]]] ++ ;
		cout << cnt.size () << endl ;
	}
//	for ( ll i = 1 ; i <= n ; i ++ )
//	{
//		cout << s [i] << endl ;
//	}
	return 0 ;
}
```

---

## 作者：f_hxr_ (赞：2)

[洛谷传送门 ](https://www.luogu.com.cn/problem/AT_abc343_d)[AT 传送门](https://atcoder.jp/contests/abc343/tasks/abc343_d)

~~怎么都没人来写题解？~~

大水题！看到“分数的种类数”，我们很容易想到用桶来计数；由于一次只修改一个数，所以我们可以在桶里，先把原来的数的出现次数减 $1$，再把新的数的出现次数加 $1$。

当“次数”从 $0$ 变成 $1$ 时，就说明“数的种类”多了 $1$；当“次数”从 $1$ 变成 $0$ 时，就说明“数的种类”少了 $1$。

直接模拟即可。

[AC](https://www.luogu.com.cn/record/149564749) 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,T,val[200005],ans=1;
LL A[200005],B[200005];
map<LL,LL>mp;
int main(){
	cin>>N>>T;
	for(int i=1;i<=T;i++)cin>>A[i]>>B[i];
	mp[0]=N;
	for(int i=1;i<=T;i++){
		mp[val[A[i]]]--;if(mp[val[A[i]]]==0)--ans;
		val[A[i]]+=B[i]; 
		mp[val[A[i]]]++;if(mp[val[A[i]]]==1)++ans;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：2)

用的是类似 P2058 海港的思路，设 $cnt$ 表示当前有多少种不同的分数，初始时 $cnt=1$。同时开一个 map 当桶计数。

每次增加，把桶中原本的分数的数量减一。如果减完后没有了，即少了一个种类，$cnt \gets cnt-1$。

然后把新的分数放进桶里。如果当前桶原本是空的，即新增了一个种类，$cnt \gets cnt+1$。

每次输出 $cnt$ 即可，每次询问复杂度是 $\log$ 的（map）。

[code](https://atcoder.jp/contests/abc343/submissions/50819833)

---

## 作者：jerry1717 (赞：2)

### 题意

给 $t$ 个点，第 $a_i$ 个点的值在第 $i$ 秒会加上 $b_i$。求第 $i$ 秒时有几个值不同的点。

### 思路

显而易见，若每个点的值都比较小，我们可以用一个桶记录已有点的值，每次加时就把原值减一，现值加一。减到零时就将答案减一，加到一时就将答案加一。

可是点的值很大，不过没关系，我们可以将所有的值离线后离散。代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,t,x,a[500001],b[500001],h[500001],c[500001],l=1,d[500001],to[500001];
map<long long,int>mp;
signed main(){
	scanf("%d %d",&n,&t);
	c[++x]=0;
	for(int i=1;i<=t;i++){
		scanf("%d %d",&a[i],&b[i]);
		h[a[i]]+=b[i];
		c[++x]=h[a[i]];//把值离线下来
	}
	sort(c+1,c+1+x);//排序
	for(int i=1;i<=n;i++){
		if(c[i]==c[i-1]){//去重
			c[i-1]=0;
			l++;//累计一个初值，把0全放在前面
		}
	}
	sort(c+1,c+1+x);
	for(int i=l;i<=x;i++){
		d[i-l+1]=c[i];
		mp[c[i]]=i-l+1;
	}//离散过程
	int ans=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		to[mp[h[i]]]++;
	}
	for(int i=1;i<=t;i++){
		to[mp[h[a[i]]]]--;//注意，每个值都得离散
		if(to[mp[h[a[i]]]]==0){
			ans--;
		}
		h[a[i]]+=b[i];
		to[mp[h[a[i]]]]++;
		if(to[mp[h[a[i]]]]==1){
			ans++;
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：Otue (赞：1)

开一个 map 存储每个数出现的次数。最初 $0$ 出现了 $n$ 次。再开一个全局变量 $res$ 表示有多少个不同的数。

添加一个数时：如果这个数第一次出现，计数器加一，并且更新 `map`。

删除一个数时：如果这个数在数列中只出现一次，计数器减一。

代码：

```cpp
map<int, int> vis;

void del(int x) { // 删除 x
	if (vis[x] == 1) res--;
	vis[x]--;
}

void add(int x) { // 添加 x
	if (vis[x] == 0) res++;
	vis[x]++;
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
	vis[0] = n; res = 1;
	for (int i = 1; i <= m; i++) {
		del(t[a[i]]);
		t[a[i]] += b[i];
		add(t[a[i]]);
		cout << res << endl;
	}
}
```

---

## 作者：xxboyxx (赞：1)

### 翻译

有 $N$ 个人，初始分数为 $0$，$T$ 次操作，每次操作让一位人的分数增加，询问每次操作后不同分数的个数。

### 思路

看到这道题，不同的分数，就想到了莫队思想，由于分数可能为长整型，数组是存不下的，这时候就需要 `map`，用来记录某一种分数使用的人数。当某人分数增加时，增加前使用的分数使用的人数减少一，增加后使用的分数使用的人数增加一。

- 在增加后某种分数使用的人数为 $1$，这就代表多了一种不同的分数，答案增加一。
- 在增加后某种分数使用的人数为 $0$，这就代表少了一种不同的分数，答案减少一。

### 注意

一开始不同分数的个数为 $1$，分数 $0$ 的使用人数为 $N$。

### 代码

```
#include<bits/stdc++.h>
#define int long long//记得开long long 
using namespace std;
int n,t,ans=1;
int a[1000005];
int b[1000005];
int c[1000005];
map<int,int> mp;
signed main()
{
	cin>>n>>t;
	mp[0]=n;
	for (int i=1;i<=t;i++)
		cin>>a[i]>>b[i];
	for (int i=1;i<=t;i++)
	{
		mp[c[a[i]]]--;//增加前使用的分数使用的人数减少一
		if (mp[c[a[i]]]==0)//少了一种不同的分数
			ans--;//答案减少一
		c[a[i]]+=b[i];
		mp[c[a[i]]]++;//增加后使用的分数使用的人数增加一
		if (mp[c[a[i]]]==1)//多了一种不同的分数
			ans++;//答案增加一
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：0)

## Description

[**Link**](https://atcoder.jp/contests/abc343/tasks/abc343_d)

## Solution

给每个数开一个计数桶，初始时只有一种元素 $0$，个数为 $n$。

对于每次操作，必定会有一种元素个数减一，如果这种元素在操作后没有了，种类数减一；如果在这次操作，原本没有的元素多出来一个，那么种类数加一即可。

## Code

```cpp
// 2024/3/10 PikachuQAQ

#include <iostream>
#include <map>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 7;

int n, t, a[kMaxN], b[kMaxN], c[kMaxN], ans = 1;
map<ll, int> mat;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> t;
    for (int i = 1; i <= t; i++) {
        cin >> a[i] >> b[i];
    }
    mat[0] = n;
    for (int i = 1; i <= t; i++) {
        ans -= --mat[c[a[i]]] == 0;
        ans += mat[c[a[i]] + b[i]]++ == 0;
        c[a[i]] += b[i];
        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：zhuhongye (赞：0)

## 题意
本题给定 $n$ 和 $m$，表示一共有 $n$ 个数，要在这 $n$ 个数上做 $m$ 次操作。

每次操作的定义为： 
1. 给定 $a$ 和 $b$。
2. 将第 $a$ 个数加上 $b$。
3. 统计此时数列中有多少个不同的数。

## 解题思路
首先考虑暴力做法，每次操作完后暴力统计，时间复杂度为 $O(nm)$，$n,m \le 1e5$，所以肯定会超时。

我们要怎么优化呢？

这里我用的是数组标记的做法。

设 $d_i$ 为第 $i$ 个下标的值，$sum$ 为当前不同数字的个数，$s_i$ 为数列中值为 $i$ 的下标个数。

输入 $a$ 和 $b$ 时，先把 $s_{d_a}$ 减一，如果 $s_{d_a}$ 为 $0$ ，$sum$ 减一。

然后 $d_a$ 加 $b$ 。

再把当前的 $s_{d_a}$ 加一，如果 $s_{d_a}$ 为 $1$，$sum$ 加一。

最后输出 $sum$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 2e5+5;
ll n,m;
ll x[N],ans=1;
map<ll,ll> s;
int main(){
	cin>>n>>m;
	
	s[0]=n;
	for(int i=1;i<=m;i++){
		ll a,b;
		cin>>a>>b;
		s[x[a]]--;
		if(s[x[a]]==0)ans--;
		x[a]+=b;
		s[x[a]]++;
		if(s[x[a]]==1)ans++;
		cout<<ans<<"\n";
	}
	return 0;
} 
```

---

## 作者：code_hyx (赞：0)

先占个坑。  
考虑用 map 记录每个分数出现的次数，分数修改后，将新分数的出现次数 $+1$，旧分数的出现次数 $-1$。  
然后，需要同时记录不同的分数个数。  
显然，相邻两次修改后的不同分数个数之差不超过 $1$。如果改后的分数是从未出现的分数，就多了一个分数；如果改前的分数是唯一一个，就少了一个分数。当然，也有可能既多一个，又少一个，这样不同分数个数就不变。  
注意，最开始不同的分数个数是 $1$。还有，开 long long！  
代码：  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long n,t,a[200005]={0},cnt=1;
map<long long,int> mp;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	mp[0]=n;
	while(t--)
	{
		long long x,y,pre;
		cin>>x>>y;
		pre=a[x];
		a[x]+=y;
		if(mp[a[x]]==0)
		{
			cnt++;
			mp[a[x]]=1;
		}
		else mp[a[x]]++;
		if(mp[pre]==1)
		{
			cnt--;
			mp[pre]=0;
		}
		else mp[pre]--;
		cout<<cnt<<"\n";
	}
	return 0;
} 
```

---

## 作者：coderJerry (赞：0)

### 题目描述
有 $N$ 个人，$T$ 次改变，每次把第 $A_i$ 个人的分数增加 $B_i$（初始分数都是 $0$）。问每次操作完共有多少不同的分数。
### 题目分析
建议对着代码阅读哦！

显然暴力复杂度 $O(TN)$，两秒根本跑不过二十万。想想用什么数据结构能把分数和出现次数对应起来？没错，就是 ```map```（下文使用 ```mp``` 表示）。

接下来按照题意模拟：先开一个数组存着每个人当前分数（下文使用 ```f``` 表示）。注意 ```mp[0]``` 要给初值 $n$（初始分数都是 $0$）。每次 $a$ 的分数变成 $b$，那么  ```mp[f[a]]--;mp[b]++;```。注意接下来要检查 ```mp[f[a]]``` 是否还存在，不存在就抹去，最后。然后 $a$ 的分数要加上 $b$，并且 ```mp``` 里还要存入这个新的分数。最后输出 ```mp.size()``` 即可。
### AC 代码
代码复杂度是 $O(T\log n)$ 的，至于代码里的 ```--a``` 和 ```--mp[f[a]]```，那是因为我用的是 ```vector```，下标从 $0$ 开始。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,t,a,b;
vector<int> f(200010);
map<int,int> mp;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>t;
    mp[0]=n;
    for(int i=1;i<=t;i++){
        cin>>a>>b;
        --a;
        if(--mp[f[a]]==0) mp.erase(f[a]);
        f[a]+=b;
        ++mp[f[a]];
        cout<<mp.size()<<endl;
    }
    return 0;
}
```

---

## 作者：cqbzcjh (赞：0)

## 分析
题目要求我们维护不同分数的个数，还需要进行修改，自然想到可以用 $\operatorname{map}$ 来存储每个分数在当前时间点出现的次数。

注意需要初始化 $0$ 的个数为 $N$，即初始时所有玩家的得分为 $0$。只用输出 $\operatorname{map}$ 的大小即为所求值。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int n,t,a,b;
ll s[N];
map<ll,int> mp;
int main(){
	scanf("%d%d",&n,&t);
	mp[0]=n;//初始化
	for(int i=1;i<=t;i++){
		scanf("%d%d",&a,&b);
		mp[s[a]]--;//将加分前分数的个数减1
		if(!mp[s[a]])mp.erase(s[a]);
		s[a]+=b;
		mp[s[a]]++;
		printf("%lld\n",mp.size());
	}
	return 0;
}
```

---

## 作者：vectorxyz (赞：0)

模拟题。

#### 题目分析
如果这题没更改一个数就排一下序时间复杂度太高了，所以我们只要判断更改后的数对一共有几个不同的数这个答案有没有影响。

如果改之前这个数在当前数改完后不会出现了，我们就把 $ans$ 减去 $1$，$ans$ 表示一共有几个不同的数，相反的，如果这个数更改后是第一次出现，就 $ans$ 加 $1$，如果更改后的数本来就出现过，$ans$ 不变，然后每次输出 $ans$ 即可。

考虑到出现次数问题可以用 map 维护。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T>
T read(T x){T opt = 1, sum = 0;char ch = getchar();while(!isdigit(ch)) {if(ch == '-') opt = -1;ch = getchar();}while(isdigit(ch)){sum = sum * 10 + ch - '0';ch = getchar();}return sum * opt;}
#define read read(0)

const int N = 2e5 + 5;
map<int, int> mp;
struct node
{
    int time, plus;
}a[N];
int c[N];
int cnt = 1;
signed main()
{
    int n = read, T = read;
    mp[0] = n;
    for(int i = 1;i <= T;i ++ ){
        int ai, bi;
        cin >> ai >> bi; 
        if(mp[c[ai] + bi] == 0){

            
            cnt ++ ;
            mp[c[ai]] -- ;
            // cout << c[ai];
            // cout << "----------\n";
            if(mp[c[ai]] == 0) cnt -- ;
            c[ai] += bi;
            mp[c[ai]] ++ ;
        }
        else {
            mp[c[ai]] -- ;
            if(mp[c[ai]] == 0) cnt --;
            c[ai] += bi;
            mp[c[ai]] ++ ;
        }
       
        cout << cnt << endl;
    }
    return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc343/submissions/50828925)。

---

## 作者：Lian_zy (赞：0)

我们只需要统计每个数字出现的次数即可。

这时候 map 就有大用了，因为加的数字可能会很大，直接用数组内存会炸，所以用 map 方便一点。

设原来的分数为 $x$，现在的分数为 $x'$。

每次操作的时候就相当于把 $x$ 移除，并添加一个 $x'$。

如果移除 $x$ 的时候当前分数为 $x$ 的人数为 $0$ 了，则分数种类减一。

根据这样的思想，我们也可以得出如果添加 $x'$ 的时候 $x'$ 的人数为 $1$（即只有他一个人），那么分数种类加一。

然后就很好办啦~

别忘了开 `long long` 哦~

[不开 `long long` 的结果](https://www.luogu.com.cn/record/149910122)
``` cpp
#include <map> 
#include <cstdio> 
#include <cstring> 
#include <algorithm> 
using namespace std;

const int maxn = 2e5 + 10;
map<long long, long long> mp;
long long T, n, x, y, cnt, cntnum[maxn];
int main() {
	scanf("%lld %lld", &n, &T);
	mp[0] = n, cnt = 1;
	while (T--) {
		scanf("%lld %lld", &x, &y);
		if (mp[cntnum[x]] == 1) cnt--;
		mp[cntnum[x]]--;
		cntnum[x] += y;
		mp[cntnum[x]]++;
		if (mp[cntnum[x]] == 1) cnt++;
		printf("%lld\n", cnt);
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc343_d)。

显然，如果每一次进行操作都重新枚举，一定超时。

但是每一次操作只会对一个数修改，所以我们只需要记录一个数的改变即可。

约定 $p$ 为修改前的数，$q$ 为修改后的数。

- 若修改后 $q$ 的个数为 $1$，则 $q$ 是首次出现，答案加 $1$。
- 若修改后 $p$ 的个数为 $0$，则 $p$ 没有了，答案减 $1$。

由于 $B_i\le10^9$，所以使用 ```map```。

```
#include<iostream>
#include<map>
using namespace std;
map<long long,int>a;
int n,t,now[200005];
int x,y,ans=1;
int main(){
	cin>>n>>t;
	a[0]=n;
	for(int i=1;i<=t;i++){
		cin>>x>>y;
		a[now[x]]--;
		if(a[now[x]]==0)ans--;
		now[x]+=y;
		a[now[x]]++;
		if(a[now[x]]==1)ans++;
		cout<<ans<<endl;
	} 
	return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc343_d)

## 思路

用 map 进行模拟，对于每次询问，进行判断，判断方法如下：

- 更新值前，如果当前数的出现次数只有 $1$ 次，那么记录不同数的次数的变量需要减 $1$。

- 更新值后，如果当前数的出现次数为 $0$ 的话，那么记录不同数的次数的变量则需要加 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 2e5 + 10;

unordered_map<ll, int> mp;

ll a[N];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	mp[0] = n;
	for(int i = 1; i <= n; i++)a[i] = 0;
	int cnt = 1;//一开始，只有 0 一个数
	while(m--){
		ll x, y;
		cin >> x >> y;
		if(mp[a[x]] == 1)cnt--;//只出现了 1 次
		mp[a[x]]--; 
		ll tmp = a[x] + y;
		if(mp[tmp] == 0)cnt++;//没有出现过
		mp[tmp]++;//更新
		a[x] = tmp;
		cout << cnt << endl;
	}
}
```

---

## 作者：Floating_Trees (赞：0)

### 题意
有 $n$ 个人，每个人刚开始有 0 分，在第 $i=1,2,…,T$ 秒，第 $a_i$ 个人会增加 $b_i$ 分，请你分别输出第 $i$ 次加分后有多少种不同的分数。

### 思路
显然每次加分只会有一个人改变，其他人的分数都不会变化，再用 map 来记录每个分数有多少人，那么每次就只要判断第 $a_i$ 个人的分数变化后有多少种分数。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = (int)2e5 + 10,mod = 1000007;
int n,T;
int a,b; ll s[N];
map<ll,int> mp;

int main()
{
	scanf ("%d%d",&n,&T);
	mp[0] = n;
	int ans = 1; // 用 ans 来记录有多少种分数，刚开始都是 0，所以就只有 1 种 
	while (T--)
	{
		scanf ("%d%d",&a,&b);
		mp[s[a]]--; // 改变后就不是之前的分数了，之前分数的人就会少一 
		if (mp[s[a]] == 0) // 如果改变前的分数的人没有了，ans 就减一 
			ans--;
		s[a] += b; 
		mp[s[a]]++; // 改变之后的分数的人就会多一 
		if (mp[s[a]] == 1) // 如果这个人是改变之后的分数的第一个人，也就是之前没有人是这个分数，那么 ans 就加一 
			ans++;
		printf ("%d\n",ans);
	}
	
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

定义第 $i$ 个数当前的值为 $t_i$。

那么考虑用一个数组 $p$ 记录每一个数的出现次数，初始 $p_0=n$，记当前答案为 $ans=1$。

对于第 $i$ 秒，如果 $p_{t_{a_i}}=1$ 了，那么这个数将删除后，要将这个数的贡献消掉，则将 $ans \to ans-1$。

然后将 $t_{a_i} \to t_{a_i} + b_i$，同时如果 $p_{t_{a_i} + b_i}=0$，则该数是新出现的，将 $ans \to ans+1$。

其中 $p$ 可以用 ``map`` 进行维护，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans;
ll a[N],b[N],t[N];
map<ll,ll> p;
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
		b[i]=read();
	}
	p[0]=n;
	ans=1;
	for(int i=1;i<=m;i++){
		if(p[t[a[i]]]==1)
		  ans--;
		p[t[a[i]]]--;
		t[a[i]]+=b[i];
		if(!p[t[a[i]]])
		  ans++;
		p[t[a[i]]]++;
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 思路
~~本蒟蒻赛时三遍过。~~

暴力一定时间超限，所以考虑使用映射数组 map。

两个 map 数组，$m$ 和 $mm$，$m$ 的下标为第 $i$ 个位置，值为当前的这个位置的和，$mm$ 的下标是出现的数字，值为出现的次数，然后一个变量 $ans=1$，赋值为 $1$ 是因为 $0$ 也算。

对于每一次操作的步骤：

1. 如果 $mm_{m_{a_i}}$（$m_{a_i}$ 没有累加上 $b_i$）存储的值等于 $1$，因为这样子是少了一个数，所以 $ans-1$，然后 $mm_{m_{a_i}}=0$，否则 $ans$ 不变，让 $mm_{m_{a_i}}-1$。

2. 把 $m_{a_i}$ 累加上 $b_i$。

3. 如果 $mm_{m_{a_i}}$（$m_{a_i}$ 已经累加上 $b_i$）存储的值等于 $0$，那么 $ans+1$，因为这样子是多了一个数。

4. 把 $mm_{m_{a_i}}+1$。

5. 输出 $ans$ 并换行。

记得一开始把 $mm_0$ 赋值为 $n$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
map<ll,ll> m,mm;
ll a[200005],b[200005],ans=1;
int main(){
	int n,t;
	cin>>n>>t;
	mm[0]=n;
	for(int i=1; i<=t; i++){
		cin>>a[i]>>b[i];
		if(mm[m[a[i]]]==1){
			mm[m[a[i]]]=0;
			ans--;
		}
		else{
			mm[m[a[i]]]=max(mm[m[a[i]]]-1,0ll);
		}
		m[a[i]]+=b[i];
		if(mm[m[a[i]]]==0){
			ans++;
		}
		mm[m[a[i]]]++;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：WhxStar2024 (赞：0)

## 本题思路：
这道题其实很简单，我们用一个数组记录每一名选手的分数，然后开一个桶记录每个分数出现的次数，如果改了这个数没有了就答案减一，如果新改的这个数以前没有就答案加一。这样直接输出即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200001],ans;
map<int,int>s;
signed main()
{
	int n,jl,t;
	cin>>n>>t;s[0]=n;ans=1;
	for(int i=1;i<=t;i++){
		int x,y;
		cin>>x>>y;
		if(s[a[x]]==1) {
			ans--;s[a[x]]=0;
		}
		else s[a[x]]--;
		if(s[a[x]+y]==0) ans++;
		s[a[x]+y]++,a[x]+=y;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_d)

#### 思路

由于加的分值可能很大，所以考虑用 `map` 存，同时由于每次更改只会改变一个数，直接模拟即可。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int>c;
int n,t,a[200010],b[200010],sum[200010],ans;
signed main()
{
	scanf("%d%d",&n,&t);
	for(int i = 1;i <= n;i++)
	{
		if(!c[sum[i]]) ans++;
		c[sum[i]]++;
	}
	for(int i = 1;i <= t;i++) 
	{
		scanf("%d%d",&a[i],&b[i]);
		c[sum[a[i]]]--;
		if(!c[sum[a[i]]]) ans--;
		sum[a[i]] += b[i];
		if(!c[sum[a[i]]]) ans++;
		c[sum[a[i]]]++;
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

因为本题数据范围为 $1\le N,T\le 2\times 10^5$，单纯模拟显然不行。

我们可以用一个 `map` 和一个 `set` 分别表示一共有多少人是这个分数，有哪些分数（因为这两种数据结构可以自动去重）。在中间变化的时候，如果 `map` 中的一个分数没有人了，就把它从 `map` 和 `set` 中删去。

最后每次输出 `set` 的大小即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2E5+5;
map<int,int> mp;
set<int> st;
int a[N];
signed main(){
	int n,t;
	cin>>n>>t;
	int x,y;
	mp[0]=n;
	st.insert(0);
	while(t--){
		cin>>x>>y;
		int ee=a[x];
		--mp[ee];
		if(mp[ee]==0){
			st.erase(ee);
		}
		a[x]+=y;
		++mp[a[x]];
		st.insert(a[x]);
		cout<<st.size()<<endl;
	}
	return 0;
}
```

---

