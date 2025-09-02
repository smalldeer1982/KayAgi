# We Were Both Children

## 题目描述

Mihai and Slavic were looking at a group of $ n $ frogs, numbered from $ 1 $ to $ n $ , all initially located at point $ 0 $ . Frog $ i $ has a hop length of $ a_i $ .

Each second, frog $ i $ hops $ a_i $ units forward. Before any frogs start hopping, Slavic and Mihai can place exactly one trap in a coordinate in order to catch all frogs that will ever pass through the corresponding coordinate.

However, the children can't go far away from their home so they can only place a trap in the first $ n $ points (that is, in a point with a coordinate between $ 1 $ and $ n $ ) and the children can't place a trap in point $ 0 $ since they are scared of frogs.

Can you help Slavic and Mihai find out what is the maximum number of frogs they can catch using a trap?

## 说明/提示

In the first test case, the frogs will hop as follows:

- Frog 1: $ 0 \to 1 \to 2 \to 3 \to \mathbf{\color{red}{4}} \to \cdots $
- Frog 2: $ 0 \to 2 \to \mathbf{\color{red}{4}} \to 6 \to 8 \to \cdots $
- Frog 3: $ 0 \to 3 \to 6 \to 9 \to 12 \to \cdots $
- Frog 4: $ 0 \to \mathbf{\color{red}{4}} \to 8 \to 12 \to 16 \to \cdots $
- Frog 5: $ 0 \to 5 \to 10 \to 15 \to 20 \to \cdots $

 Therefore, if Slavic and Mihai put a trap at coordinate $ 4 $ , they can catch three frogs: frogs 1, 2, and 4. It can be proven that they can't catch any more frogs.In the second test case, Slavic and Mihai can put a trap at coordinate $ 2 $ and catch all three frogs instantly.

## 样例 #1

### 输入

```
7
5
1 2 3 4 5
3
2 2 2
6
3 1 3 4 9 10
9
1 3 2 4 2 3 7 8 5
1
10
8
7 11 6 8 12 4 4 8
10
9 11 9 12 1 7 2 5 8 10```

### 输出

```
3
3
3
5
0
4
4```

# 题解

## 作者：Crazyouth (赞：9)

**翻译**

给出 $n$ 个数的数列 $a$，构造一个满足 $1\le x\le n$ 的 $x$，最大化 $a$ 中 $x$ 的因数个数，求这个最多个数。

**分析**

首先有一个基本结论：$a$ 中大于 $n$ 的数没有意义。接下来，对于有意义的数，我们计算它的出现次数，这样可以避免全都是同一个数的毒瘤数据卡掉我们的程序。然后，统计在 $[1,n]$ 里所有数在 $a$ 中的因数个数，取出最大的即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int a[MAXN],num[MAXN],cnt[MAXN];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		memset(num,0,sizeof num);//多测清空
		memset(cnt,0,sizeof cnt);
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]<=n)
			num[a[i]]++;//统计出现次数
		}
		for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j+=i)
		{
			cnt[j]+=num[i];//计算因数个人
		}
		int ans=-1;
		for(int i=1;i<=n;i++) ans=max(ans,cnt[i]);//取出最大
		cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：Wf_yjqd (赞：5)

橙题差不多吧。。

没用官方做法，自己赛时的垃圾做法。

------------

首先考虑暴力啊。

直接枚举所有倍数标记，然后枚举出标记次数最多的位置即可。

然后就会 TLE 掉，于是有些人自作聪明的特判了 $1$。

然后被 hack 了。其实我猜多特判几个还是能过。

但这样是没有正确性的，所以考虑根号分治。

直接特判所有小于 $\sqrt{n}$ 的数。

枚举每个位置，判断是否是小于 $\sqrt{n}$ 的数的倍数，增加标记即可。

复杂度 $\operatorname{O}(n\times\sqrt{n})$。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
inline ll maxx(register ll x,register ll y){
    return x>y?x:y;
}
ll T,n,sqn,a,ans,cnt[maxn],cntt[maxn],st[maxn],top;
int main(){
    T=read();
    while(T--){
        n=read(Sherry);
        sqn=sqrt(n+1);
        for(ll i=1;i<=n;i++)
            cnt[i]=cntt[i]=Sherry;
        top=0;
        for(ll i=1;i<=n;i++){
            a=read();
            if(a>sqn){
                for(ll j=a;j<=n;j+=a)
                    cnt[j]++;
            }
            else{
                if(!cntt[a])
                    st[++top]=a;
                cntt[a]++;
            }
        }
        ans=Sherry;
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=top;j++)
                if(i%st[j]==0)
                    cnt[i]+=cntt[st[j]];
            ans=maxx(ans,cnt[i]);
        }
        write(ans);
        putchar('Sherry');
    }
    return 0;
}
```


---

## 作者：Dream__Sky (赞：5)

题意简述：

米哈伊和斯拉夫克正在观察一组从 $1$ 到 $n$ 编号为 $n$ 的青蛙，它们最初都位于 $0$ 点。青蛙 $i$ 的跳跃长度为 $a_i$。

每秒钟，青蛙 $i$ 向前跳跃 $a_i$ 个单位。在任何青蛙开始跳跃之前，斯拉夫和米哈伊可以在一个坐标上放置 $1$ 个捕捉器，以便捕捉所有经过相应坐标的青蛙。

但是，孩子们不能离家太远，所以他们只能在前 $n$ 个点（即坐标在 $1$ 和 $n$ 之间的点）放置一个陷阱，而且孩子们不能在 $0$ 点放置陷阱，因为他们害怕青蛙。

您能帮助斯拉夫和米哈伊找出使用陷阱最多能捕捉多少只青蛙吗？

分析：

首先我们交一发暴力，每次枚举每一只青蛙以及它在 $1$ 到 $n$ 中可以跳的点，在枚举过程中用一个桶来记录每一个点能抓到几只青蛙。最后再在桶中找一个数量最大的点，这就是最大的捕捉数量。但是会 TLE。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,a[200001],p[200001],maxn,n;
int main()
{
	cin>>T;
	while(T--)
	{
		memset(p,0,sizeof p);
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		
		for(int i=1;i<=n;i++)
			for(int j=a[i];j<=n;j+=a[i])
				p[j]++;
			
		maxn=0;
		for(int i=1;i<=n;i++) maxn=max(maxn,p[i]);
		cout<<maxn<<endl;
	 } 
	return 0;
}
 
```

我们尝试优化。

我们让跳的距离一样的青蛙在记录跳的点的时候只枚举一次，每次在能跳到的点上直接加上这种青蛙的个数，这样就能减少一些重复的计算。利用这个优化，就可以 AC。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int T,a[200001],p[200001],maxn,n;
map<int,int> pp,ppp;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--)
	{
		memset(p,0,sizeof p);
		pp.clear(),ppp.clear();
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],ppp[a[i]]++;//ppp记录了每种青蛙有几个。
		
		for(int i=1;i<=n;i++)
		{
			if(!pp[a[i]])//如果还未被搜到，那么枚举一遍
			{
				pp[a[i]]=1;
				for(int j=a[i];j<=n;j+=a[i])
				p[j]+=ppp[a[i]];//记录下这个位置能有几只青蛙经过。
			}
		}
			
			
		maxn=0;
		for(int i=1;i<=n;i++) maxn=max(maxn,p[i]);//找一个最大值
		cout<<maxn<<"\n";
	 } 
	return 0;
}
 
```


---

## 作者：Dreamer_Boy (赞：3)

将一个好理解的方法。

题目说有 $n$ 只青蛙，每只青蛙初始都在 $0$ 位置，每秒会往前跳 $a_i$。你可以在位置 $1$ 到 $n$ 设置一个陷阱，陷阱会抓住经过它的所有青蛙，求你最多能抓住多少青蛙。

很简单，只要枚举质因数并判断是否合法即可。

```
int n, ans = 0;
  cin >> n;
  memset(cnt, 0, sizeof cnt);
  for (int i = 1, x; i <= n; ++i)
  {
    cin >> x;
    if (x <= n)cnt[x]++;
  }
  for (int i = 1; i <= n; ++i)
  {
    int s = 0;
    for (int j = 1; j * j <= i; ++j)
    {
      if (i % j == 0)
      {
        s += cnt[j];
        if (j * j != i)
          s += cnt[i / j];
      }
    }
    ans = max(ans, s);
  }
  cout << ans << endl;
```
#### 结语
蒟蒻第一次打英文比赛，请多多指教。

---

## 作者：cjh20090318 (赞：2)

**Update on 2023/7/23 18:52：经管理员 @[CSP_Sept](https://www.luogu.com.cn/user/224931) 提醒，修改整除符号表示。**

## 题意

给定 $n$ 个整数 $a$，你需要找到一个整数 $x \in [1,n]$ 使得 $\sum\limits_{i=1}^n[a_i \mid x]$ 最大。

## 分析

**这一道题根本就不需要筛因数！**

其实只要你稍微优化一下暴力，这个是可以过的。

如果你不优化就会像我的同学一样[被 Hack](https://codeforces.com/contest/1850/submission/214910868)。

我们可以用一个 `std::map` 存储有多少只距离为 $x$ 的青蛙。

设一个 $b$ 数组表示 $b_i$ 为青蛙会经过 $i$ 这个位置的只数。

然后对于每一个 $x\mid i$，只需要每一次加距离为 $x$ 青蛙的只数就可以了，如果每一次遍历都只加一个会显得十分浪费。

还有一个小优化就是特判 $a_i=1$，这种情况可以特殊处理，因为它对于每一个位置都是可行的，所以单独讨论。

最坏情况下，时间复杂度是 $O(n\sum\limits_{i=1}^n\dfrac{1}{i}) \approx O(n \log n)$，使用 `std::map` 维护需要再乘一个 $\log n$，所以总的时间复杂度为 $O(n \log^2 n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<utility>
int n,a[200002],b[200002];
std::map<int,int> M;
void solve(){
	M.clear();
	scanf("%d",&n);
	memset(b,0,sizeof(int)*(n+1));//清空数组，并不需要清空全部。
	int s=0;//为 1 的个数。
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1) ++s;//特判为 1 的情况。
		else if(a[i]<=n) ++M[a[i]];//如果大于 n 则不需要考虑。
	}
	for(std::pair<int,int> it:M){
		for(int i=it.first;i<=n;i+=it.first) b[i]+=it.second;//暴力加答案。
	}
	int ans=s;
	for(int i=1;i<=n;i++)ans=std::max(ans,b[i]+s);//当前位置加一的个数即为当前答案，然后取最大值。
	printf("%d\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：2011FYCCCTA (赞：1)

# [原题](https://www.luogu.com.cn/problem/CF1850F)

### 题目
输入 $n$ 和一个长度为 $n$ 的数列 $a$，求出一个在 $1$ 到 $n$ 之间的数，使得这个数有最多的因子在数列 $a$ 中出现。

---
### 思路

先预处理出从 $1$ 到 $2 \times 10 ^ 5$（$n$ 的最大值）之中所有数的因数。再桶记录数列 $a$ 中各个数出现的次数，这里直接开 $10 ^ 9$（$a_i$ 的最大值）的数组太大了，但可以发现，比 $n$ 大的数一定不是 $1$ 到 $n$ 之间的数的因数（都比 $n$ 大了）因此只用开到 $n$ 的最大范围即可。最后枚举 $1$ 到 $n$ 之间的数，每次累加此数在数列 $a$ 中的出现次数（即对应的桶的数字）找最大值即可。

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int t , n , a[MAXN + 5] , s[MAXN + 5] , ans;
vector<int> f[MAXN + 5];

void init_factor()
{
    for (int i = 1 ; i <= MAXN ; i++)
    {
        for (int j = 1 ; j * j <= i ; j++)
            if (i % j == 0) {f[i].push_back(j); f[i].push_back(i / j);}
        //如果i是完全平方数，那么在如上计算因数是时，会存入2个i的平方根，需减去一个
        if (pow((int)sqrt(i) , 2) == i) f[i].pop_back();
    }
    return;
}

int main()
{
    init_factor();

    cin >> t;
    while (t--)
    {
        memset(s , 0 , sizeof(s));

        cin >> n;
        for (int i = 1 ; i <= n ; i++)
        {
            cin >> a[i];
            if (a[i] <= n) ++s[a[i]];
        }

        ans = 0;
        for (int i = 1 ; i <= n ; i++)
        {
            int sum = 0;
            for (int j = 0 ; j < f[i].size() ; j++)
                sum += s[f[i][j]];
            ans = max(ans , sum);
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：sto_5k_orz (赞：1)

# F

先预处理出 $1$ 到 $2\times 10^5$ 的所有数的约数，复杂度 $\mathcal{O(n\log n)}$。

考虑维护所有 $a_i\le n$ 的情况，做桶维护。

然后暴力枚举 $1$ 到 $n$ 的所有约数在桶内的出现次数之和即可。

总时间复杂度为 $\mathcal{O(n\log n)}$，赛时和我一样傻逼的写了 $\mathcal{O(n\sqrt n)}$ 的预处理也可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
vector<int> c[N]; int a[N], v[N];
void init(int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j * j <= i; j++) if(i % j == 0) {
			c[i].push_back(j);
			if(j * j != i) c[i].push_back(i / j);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	int t; cin >> t; init(2e5);
	while(t--) {
		int n; cin >> n;
		for(int i = 1; i <= n; i++) v[i] = 0;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			if(a[i] <= n) v[a[i]]++;
		}
		int mx = 0;
		for(int i = 1; i <= n; i++) {
			int cnt = 0;
			for(int j: c[i]) {
				cnt += v[j];
			}
			mx = max(mx, cnt);
		}
		cout << mx << '\n';
	}
	return 0;
}
```

---

## 作者：Zaku (赞：1)

赛时想到正解了，多测不清空/jk
### $\mathrm{Problem:}$
$n$ 只青蛙在一条数轴的原点上向右跳。给定每只青蛙每秒钟的跳跃长度，可以在 $1\sim n$ 的位置上放陷阱，问最多抓住多少青蛙？

### $\mathrm{Sol:}$
使用一个桶 $t$，找到 $1\sim n$ 中，倍数包含最多青蛙的数即可。

因为只能在 $1\sim n$ 放陷阱，所以跳跃长度大于 $n$ 的忽略，其余入桶；然后倒序遍历桶，对于所有 $t_i$ 小于 $n$ 的 $i$ 的倍数 $j$，$t_j\gets t_j + t_i$。

最后桶中最大的数即为所求。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int t[N];
signed main() {
    int T;
    cin >> T;
    while (T -- ){
        int n; 
        cin >> n;
        memset(t + 1, 0, sizeof t);
        for (int i = 1; i <= n; i ++ ){
            int x; 
            cin >> x;
            if (x <= n) t[x] ++;
        }
        for (int i = n; i >= 1; i -- )
            for(int j = 2 * i; j <= n; j += i) 
                t[j] += t[i];
        cout << *max_element(t + 1, t + 1 + n) << endl;
    }
    return 0;
}
```

---

## 作者：lilong (赞：1)

不难想到，可以枚举每个 $a_i$ 的倍数，并用一个数组统计出现次数，最后求最大值，理论时间复杂度 $O(n \log n)$。但如果 $a_i$ 较小且重复出现，可能退化到 $O(n^2)$。因此可以做一个小优化：对于每个 $a_i \le n$，提前统计出每个数出现的次数，枚举倍数时只计算一次，可以提升计算效率。

```cpp

#include <bits/stdc++.h>
#define int long long

using namespace std;

int a[1000001],cnt[1000001],b[1000001];

signed main()
{
    int T,n,ans;
    cin >> T;
    while( T -- )
    {
        ans = 0;
        cin >> n;
        for( int i = 1 ; i <= n ; i ++ )
            b[i] = 0;
        for( int i = 1 ; i <= n ; i ++ )
        {
            cin >> a[i];
            if( a[i] <= n ) b[a[i]] ++;
            cnt[i] = 0;
        }
        for( int i = 1 ; i <= n ; i ++ )
            for( int j = 0 ; j <= n ; j += i )
                cnt[j] += b[i];
        for( int i = 1 ; i <= n ; i ++ )
            ans = max( ans , cnt[i] );
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Qerucy (赞：0)

看到题解区没有我的做法，就来写一发题解。

其实这道题我们暴力即可，枚举 $1$ 到 $n$ 中拥有最多的因数且因数在数列 $a$ 中即可。

我们用普通的方法枚举 $1$ 到 $n$ 各个数的因数，在判断这些因数有多少个在数列 $a$ 中就能得出答案了。

时间复杂度：$\mathcal{O}(n\sqrt {n})$

这里放出我赛时写的代码：

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
int n,a[200010],t;
int vis[200010];
 
int f(int x){
    int ans=0;
    for(int i=1;i*i<=x;i++){
        if(x%i==0){
            if(x/i!=i){
                ans+=vis[i];
                ans+=vis[x/i];
            }
            else{
                ans+=vis[i];
            }
        }
    }
    return ans;
}
 
signed main(){
	scanf("%d",&t);
	while(t--){
	    int ans=0;
	    scanf("%d",&n);
	    for(int i=1;i<=n;i++){
	        scanf("%d",&a[i]);
	        if(a[i]<=n) vis[a[i]]++;
	    }
	    for(int i=1;i<=n;i++){
	        int qwq=f(i);
	        ans=max(ans,qwq);
	    }
	    printf("%d\n",ans);
	    for(int i=1;i<=n;i++) vis[i]=0;
	}
	return 0;
}
```


---

## 作者：Phartial (赞：0)

题意：给你一个长度为 $n$ 的序列 $a_i$，求 $\displaystyle\max_{i=1}^n\{\sum_{j=1}^n[a_j\mid i]\}$。

考虑对每个 $i$ 维护一个桶 $f_i$ 表示对应的 $\sum_{j=1}^n[a_j\mid i]$，对每个 $a_i$，我们暴力枚举它能够贡献到的 $f_j$（需要 $a_i\mid j$，即 $j$ 是 $a_i$ 的倍数）。最后暴力枚举 $f_i$ 求出最大值即可。

该算法的时间复杂度为 $\mathcal{O}(n\sum_i\frac{1}{a_i})$，当所有 $a_i=1$ 时，此算法达到最坏时间复杂度 $\mathcal{O}(n^2)$。

考虑优化，可以发现，当 $a_i=i$ 时，有 $\mathcal{O}(n\sum_i\frac{1}{i})=\mathcal{O}(n\log n)$，于是考虑从值域角度入手。

我们忽略 $>n$ 的 $a_i$（因为不存在 $\le n$ 的 $j$ 使得 $a_i\mid j$，所以 $a_i$ 没贡献），对 $\le n$ 的 $a_i$，我们额外使用一个桶 $b_i$ 来存 $a_j=i$ 的 $j$ 的个数。枚举 $i$，将 $b_i$ 贡献到 $f_{ki}$ 即可（其中 $k$ 是正整数）。最后扫一遍统计答案即可。

由于我们不重不漏的枚举了 $[1,n]$ 内的所有 $i$，所以时间复杂度是严格的 $\mathcal{O}(n\log n)$。

```cpp
#include <iostream>

using namespace std;

const int kN = 2e5 + 1;

int t, n, b[kN], f[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--; ) {
    cin >> n;
    fill_n(b + 1, n, 0), fill_n(f + 1, n, 0);
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      if (x <= n) {
        ++b[x];
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; j += i) {
        f[j] += b[i];
      }
    }
    cout << *max_element(f + 1, f + n + 1) << '\n';
  }
  return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Description:
-----
给定一个长为 $n$ 的序列，第 $i$ 个元素为 $a_i$。

求一个数 $k(1\le k \le n)$，使得 $\sum\limits_{k \equiv 0\pmod {a_i}} 1$ 最大（即序列中 $k$ 能整除的数最多）。
### Solution:
-----
由于 $1\le k \le n$，因此若 $a_i > n$，我们可以舍去不管。

那么 $a_i$ 的范围就变成了 $1 \le a_i \le 2\times 10^5$。

将每个 $a_i$ 扔进桶中，枚举 $k$，将 $k$ 分解因数，统计每个因数在序列中出现个数（即每个因数桶中元素数），最后输出最大值即可。

时间复杂度 $\Theta(n\sqrt n)$，足以通过本题。

需要注意的是，清空桶时需要用遍历，而不能用 `memset`，否则会超时。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
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
ll n,a[N],ans;
ll t;
int main(){
	t=read();
	while(t--){
		n=read();ans=0;
		for(int i=1;i<=n;i++){
			ll x=read();
			if(x>n)continue;
			a[x]++;
		}
		for(int i=1;i<=n;i++){
			ll sum=0,j;
			for(j=1;j*j<i;j++)
				if(i%j==0){
					sum+=a[j]+a[i/j];
				}
			if(j*j==i)sum+=a[j];
			ans=max(ans,sum);
		}
		for(int i=1;i<=n;i++)a[i]=0;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1850F)    
## 题意
给定一个长度为 $n$ 的数列 $a$，找到一个数，使得 $a$ 里面是这个数因数的数的个数最大。要求这个数在 $[1,n]$ 里。      
## 解法
我们设 $cnt_i$ 为 $i$ 在 $a$ 中出现的个数。    
那么我们可以去贡献答案：任何一个数 $i$ 都可以对它的倍数贡献 $cnt_i$ 的答案贡献。     
我们再设 $sum_i$ 为选定数字为 $i$ 的 $a$ 所含因数个数情况。     
那么枚举 $i$，每次去贡献答案即可。    
最后答案为最大的 $sum_i$。   
时间复杂度为 $O(n\log n)$，可以通过。    
[CODE](https://www.luogu.com.cn/paste/2cezujez)

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目大意】**

长度为 $n$ 的序列 $a$，定义 $f(x) = \sum\limits_{i=1}^n [a_i | x]$，求 $\max \limits _{i = 1}^n f(i)$。$1 \le n \le 2 \times 10^5,1 \le a_i \le 10^9$。

其中 $[a_i|x]$ 值为 $1$ 当且仅当 $a_i$ 整除 $x$，否则为 $0$。

**【题目分析】**

首先发现大于 $n$ 的 $a_i$ 对答案没有贡献，我们只需要考虑小于等于 $n$ 的数字。简单的思路是对于每个 $a_i$ 暴力枚举，但是遇到 $2 \times 10^5$ 个 $1$ 就寄了。因此我们考虑预处理。

我们用埃氏筛 $\Theta(n \log n)$ 预处理出每个数字的因数并存储，然后查询时枚举 $1 \sim n$ 的每一个数的所有因数，统计答案。

为什么这样是对的呢？这就需要我们的“神图”：

![](https://cdn.luogu.com.cn/upload/image_hosting/d7jvn808.png)

$n \le 10^5$ 时最大约数量级仅有 $128$，因此不会爆时空。

**【代码】**

```cpp
    #include <bits/stdc++.h>
    using namespace std;
    #define int long long
    int t,n,a[500005],b[200005];
    vector<int> ans[200005];
    void init(){
        for(int i = 1;i <= 200000;i ++){
            for(int j = i;j <= 200000;j += i) ans[j].push_back(i);
        }
    }
    signed main(){
        cin >> t;
        init();
        while(t --){
            cin >> n;int mx = 0;
            for(int i = 1;i <= n;i ++) b[i] = 0;
            for(int i = 1;i <= n;i ++) {cin >> a[i];if(a[i] <= n) b[a[i]] ++;}
            for(int i = 1;i <= n;i ++){
                int res = 0;
                for(int j = 0;j < (int)ans[i].size();j ++) res += b[ans[i][j]];
                mx = max(res,mx);
            }
            cout << mx << "\n";
        }
    }
 ```

---

## 作者：_Only_this (赞：0)

### CF1850F We Were Both Children 题解

------------

这题是道 F，一起打比赛的大佬 5 分钟 A 了，跟我们说是根号分治，赛时本蒟蒻没写出来......

一眼觉得可以直接暴力，但 $a_i$ 如果太小的话会超时。

所以考虑记录重复数字出现的次数，然后去个重，最后直接暴力模拟青蛙的跳跃过程，统计每个位置经过青蛙的最大数量即可。

因为复杂度里带个调和级数，所以只有 $\operatorname{O}(n\log{n})$。

------------

最后贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		map<int,int>A,mp;
		scanf("%d",&n);
		for(int x,i=1;i<=n;i++)
			scanf("%d",&x),A[x]++;
		for(auto it: A){
			int x=it.first;
			for(int i=1;i*x<=n;i++){
				mp[i*x]+=it.second;
			}
		}
		int ans=0;
		for(auto it: mp){
			ans=max(ans,it.second);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

