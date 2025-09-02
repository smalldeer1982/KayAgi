# Multiple Lamps

## 题目描述

[Kid2Will - Fire Aura](https://soundcloud.com/xgp/kid2will-fire-aura)

⠀



You have $ n $ lamps, numbered from $ 1 $ to $ n $ . Initially, all the lamps are turned off.

You also have $ n $ buttons. The $ i $ -th button toggles all the lamps whose index is a multiple of $ i $ . When a lamp is toggled, if it was off it turns on, and if it was on it turns off.

You have to press some buttons according to the following rules.

- You have to press at least one button.
- You cannot press the same button multiple times.
- You are given $ m $ pairs $ (u_i, v_i) $ . If you press the button $ u_i $ , you also have to press the button $ v_i $ (at any moment, not necessarily after pressing the button $ u_i $ ). Note that, if you press the button $ v_i $ , you don't need to press the button $ u_i $ .

You don't want to waste too much electricity. Find a way to press buttons such that at the end at most $ \lfloor n/5 \rfloor $ lamps are on, or print $ -1 $ if it is impossible.

## 说明/提示

In the first test case, you need to turn at most $ \lfloor 4/5 \rfloor $ lamps on, which means that no lamp can be turned on. You can show that no choice of at least one button turns $ 0 $ lamps on.

In the second test case, you can press buttons $ 3 $ , $ 5 $ , $ 1 $ , $ 2 $ .

- Initially, all the lamps are off;
- after pressing button $ 3 $ , the lamps whose index is a multiple of $ 3 $ (i.e., $ 3 $ ) are toggled, so lamp $ 3 $ is turned on;
- after pressing button $ 5 $ , the lamps whose index is a multiple of $ 5 $ (i.e., $ 5 $ ) are toggled, so lamps $ 3 $ , $ 5 $ are turned on;
- after pressing button $ 1 $ , the lamps whose index is a multiple of $ 1 $ (i.e., $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ) are toggled, so lamps $ 1 $ , $ 2 $ , $ 4 $ are turned on;
- after pressing button $ 2 $ , the lamps whose index is a multiple of $ 2 $ (i.e., $ 2 $ , $ 4 $ ) are toggled, so lamp $ 1 $ is turned on.

This is valid because

- you pressed at least one button;
- you pressed all the buttons at most once;
- you pressed button $ u_2 = 5 $ , which means that you had to also press button $ v_2 = 1 $ : in fact, button $ 1 $ has been pressed;
- at the end, only lamp $ 1 $ is on.

In the third test case, pressing the buttons $ 8 $ , $ 9 $ , $ 10 $ turns only the lamps $ 8 $ , $ 9 $ , $ 10 $ on.

## 样例 #1

### 输入

```
4
4 0
5 2
4 1
5 1
15 9
7 8
8 9
9 10
10 9
11 1
12 2
13 3
14 4
15 5
5 4
1 2
2 3
3 4
4 5```

### 输出

```
-1
4
3 5 1 2
3
8 9 10
1
5```

# 题解

## 作者：igAC (赞：3)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1909E)

[CFlink](https://codeforces.com/contest/1909/problem/E)

简要题意：

有 $n$ 盏灯，起初都是灭的，如果你打开了第 $i$ 盏灯的开关，那么编号为 $i$ 的倍数的灯都会改变状态。

有 $m$ 个限制，形如 $(x,y)$，如果你打开了第 $x$ 盏灯的开关就必须打开第 $y$ 盏灯的开关。

问是否有打开开关的方式使得满足 $m$ 个限制的同时最后亮着的灯数不超过 $\lfloor \dfrac{n}{5} \rfloor$，不能一盏灯都不开。

# $\text{Solution}$

很巧妙的一道题，题面中 $\lfloor \dfrac{n}{5} \rfloor$ 这个数字非常的丑陋，也没有什么优美性质，所以思考如何把这个限制去掉。

思考如果将全部的开关都打开会发生什么。

很容易发现只有因数个数为奇数的灯才开着，也就是编号为完全平方数的灯是亮着的。

我们知道 $n$ 以内的完全平方数的个数为 $\lfloor \sqrt n \rfloor$，所以 $\lfloor \sqrt n \rfloor \le \lfloor \dfrac{n}{5} \rfloor$ 的数就直接将全部开关打开就行了，容易解得 $n \ge 20$。

接下来考虑 $n \le 19$ 的请况。

考虑没有 $m$ 个限制的话怎么做，因为 $n$ 很小所以很自然的想到把选择开关的状态转化为二进制数，暴力枚举去做。

打完表我们发现可行的状态数很少，于是可以预处理可行状态再对于 $m$ 个限制进行判断。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,m;
vector<int>ans[20];
bool check(int x,int base){return x>>base&1;}
void solve(){
	n=read(),m=read();
	vector<pair<int,int>>vec(m);
	for(auto &[x,y]:vec) x=read(),y=read();
	if(n>=20){
		printf("%d\n",n);
		for(int i=1;i<=n;++i) printf("%d ",i);
		puts("");return;
	}
	for(int s:ans[n]){
		for(auto [x,y]:vec) if(check(s,x-1) && !check(s,y-1)) goto nxt;
		printf("%d\n",__builtin_popcount(s));
		for(int i=1;i<=n;++i) if(check(s,i-1)) printf("%d ",i);
		puts("");return;
		nxt:;
	}
	puts("-1");
}
int main(){
	for(int i=1;i<=19;++i){
		for(int s=1;s<(1<<i);++s){//不能一盏灯都不开，所以状态从 1 开始
			int r=0;
			for(int j=1;j<=i;++j){
				if(!check(s,j-1)) continue;
				for(int k=j;k<=i;k+=j) r^=(1<<k-1);
			}
			if(__builtin_popcount(r)<=i/5) ans[i].push_back(s);
		}
	}
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：2)

注意到有个 $\lfloor \dfrac{n}{5} \rfloor$，感觉很不好处理，但是还有一句话：“第 $i$ 个开关控制了编号是 $i$ 的倍数（包括 $i$）的所有灯”，你可以联想到小学数学的那道题，从 $1$ 按到 $n$ 只有平方数编号的灯亮着，因为他们的因数个数是奇数。解一下 $\lfloor\sqrt{n}\rfloor \le \lfloor \dfrac{n}{5} \rfloor$，发现 $n \ge 25$，但由于下取整其实是 $n \ge 20$。

那剩下的 $n < 20$ 直接状压枚举一下不就行了。先不考虑限制预处理出所有按法，再对于每个询问在合法状态中找即可。

```cpp
vector<int>ok[20];
inline void prework()
{
	for(int n{1};n<=19;n++)
	{
		for(int s{1};s<(1<<n);s++)
		{
			bitset<21>nowi(s);
			nowi<<=1;
			bitset<21>light;
			for(int i{1};i<=n;i++)
			{
				if(nowi[i])
				{
					for(int j{i};j<=n;j+=i) light[j] = !light[j];
				}
			}
			if((int)light.count() > n/5) continue;
			ok[n].push_back(s);
		}
	}
}
inline void work()
{
	int n = read();
	if(n >= 20)
	{
		writeln(n);
		for(int i{1};i<=n;i++) writek(i);
		int m = read();
		while(m--) read(),read();
		return;
	}
	int m = read();
	vector<int>a(m+1),b(m+1);
	for(int i{1};i<=m;i++) a[i] = read(),b[i] = read();
	for(int s : ok[n])
	{
		bitset<25>nowi(s);
		nowi<<=1;
		bool tg = true;
		for(int i{1};i<=m;i++)
			if(nowi[a[i]] && !nowi[b[i]]) {	tg = false;break;}
		if(!tg) continue;
		writeln(nowi.count());
		for(int i{1};i<=n;i++) 
			if(nowi[i]) writek(i);
		putchar(10);return;
		
	}
	puts("-1");
}
```

---

## 作者：sunkuangzheng (赞：2)

一个经典结论是，如果你按下所有的开关，最终打开的灯都是完全平方数，只有 $\lfloor \sqrt n\rfloor$ 个。你发现这个值在 $n \ge 20$ 时都是合法的，我们只需要处理 $n \le 19$。此时，打开的灯不能超过 $3$ 个。那么思路就显然了：枚举开灯的编号，检验答案。检验答案是简单的：打开 $i$ 号开关只会影响 $i \sim n$ 号灯，因此如果这个位置灯的实际状态和目标状态不等，就需要按开关，单次检验复杂度 $\mathcal O(n \log n)$。计算一下需要枚举的情况总数：$\dbinom{19}{1}+\dbinom{19}{2}+\dbinom{19}{3}=1159$。那么最坏情况下只需要运行 $10^4 \times 1159 \times 19 \times 4 = 8.8 \times 10^8$ 次，可以通过。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 24.12.2023 17:47:25
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,a[N],b[N],c[N],d[N],ans[N];
bool ck(){
    for(int i = 1;i <= n;i ++) d[i] = 0,ans[i] = 0;
    for(int i = 1;i <= n;i ++)
        if(d[i] != c[i]){
            ans[i] = 1;
            for(int j = i;j <= n;j += i) d[j] ^= 1;
        }
    for(int i = 1;i <= m;i ++) if(ans[a[i]] && !ans[b[i]]) return 0;
    return 1;
}void op(){
    vector<int> acc;
    for(int i = 1;i <= n;i ++) if(ans[i]) acc.push_back(i);
    cout << acc.size() << "\n";
    for(int i : acc) cout << i << " ";
    cout << "\n";
}void sol(){
    for(int i = 1;i <= n;i ++) c[i] = 0;
    for(int i = 1;i <= n;c[i ++] = 0){
        c[i] = 1; if(ck()) return op();
        if(n / 5 < 2) continue;
        for(int j = i + 1;j <= n;c[j ++] = 0){
            c[j] = 1; if(ck()) return op();
            if(n / 5 < 3) continue;
            for(int k = j + 1;k <= n;c[k ++] = 0)
                if(c[k] = 1,ck()) return op();
        }
    }cout << "-1\n";
}void los(){
    cin >> n >> m;
    for(int i = 1;i <= m;i ++) cin >> a[i] >> b[i];
    if(n >= 20){
        cout << n << "\n";
        for(int i = 1;i <= n;i ++) cout << i << " ";
        cout << "\n";return ;
    }if(n <= 4) return cout << "-1\n",void();
    sol();
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：naroto2022 (赞：2)

# CF1909E 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1909E)

### 思路

首先，我们考虑一个灯最后亮着的条件是什么。对于一个灯的编号为 $light$，当且仅当按下的数列中可以被 $light$ 整除的数的个数为奇数的时候灯会亮着。

于是很自然的想到一个很经典的结论：当且仅当一个数为完全平方数时，其因子个数为奇数。

于是就可以考虑把所有的灯都开起来，最终剩下亮着的必然是编号为完全平方数的灯，而个数是 $\lfloor\sqrt n\rfloor$ 的，而这个数在 $n\geqslant20$ 时是小于等于 $\lfloor\frac{n}{5}\rfloor$ 的，于是暴力考虑 $n\leqslant19$ 的情况即可。

继续考虑可以发现，当 $n\leqslant4$ 的时候也是无解的，因为要求最终不亮灯，而题目中说开关可以是认为最后同时按下，所以，必然至少亮着一个灯，故可以直接判断无解。

对于 $5\leqslant n\leqslant19$ 的情况，会发现 $n$ 很小，可以考虑将按灯的状态压成二进制，要是有按灯的话，哪一位就为 $1$，否则为 $0$，可以发现 $2^{19}$ 还是能接受的，所以就可以预处理，爆搜每一种按灯状态，算出对应的按过灯之后的状态（也是压成二进制，亮着为 $1$，否则为 $0$），判断是否合法（其中 $1$ 的个数是否小于 $\lfloor\frac{n}{5}\rfloor$），最后再对于每一个限制进行判断，详情见代码。

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
using namespace std;
const int MN=200005;
ll T,n,m,u[MN],v[MN];
vector<ll>ans[20];
void write(ll n){if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll gs(ll x){ll res=0;while(x){x&=(x-1);/*移除最后一个1*/res++;}return res;}//计算二进制中1的个数 
void solve(){
	for(ll i=0; i<ans[n].size(); i++){//枚举所有按灯情况 
		bool flag=false;
		for(ll j=1; j<=m; j++) if(ans[n][i]>>(u[j]-1)&1&&!(ans[n][i]>>(v[j]-1)&1)){//判断是否满足给的要求 
			flag=true;//不满足就直接结束 
			break;
		} 
		if(!flag){//满足条件 
			write(gs(ans[n][i]));putchar('\n');
			for(ll j=1; j<=n; j++) if(ans[n][i]>>(j-1)&1) write(j),putchar(' ');
			putchar('\n');return; 
		}
	}
	printf("-1\n");
}
int main(){
	for(ll i=5; i<=19; i++)/*枚举位数*/for(ll s=1; s<(1<<i); s++){//因为必须至少亮一盏灯，所以枚举的状态从1开始，注意这里的状态不是灯的，而是按灯的状态。 
		ll num=0;//记录按灯之后灯的状态 
		for(ll j=1; j<=i; j++) if((s>>(j-1))&1)/*第j盏灯是亮的，因为s是从第0位开始的，所以用j-1*/for(ll k=j; k<=i; k+=j) num^=(1<<(k-1));//k-1同前
		if(gs(num)<=i/5) ans[i].push_back(s);//这是一种合法的情况 
	}
	T=read();while(T--){//多组数据 
		n=read();m=read();
		for(int i=1; i<=m; i++) u[i]=read(),v[i]=read();
		if(n<=4){printf("-1\n");continue;}//无解情况直接输出-1
		if(n>=20){//保证有解，输出把所有灯都点亮的方案 
			write(n);putchar('\n');//输出方案个数 
			for(ll i=1; i<=n; i++) write(i),putchar(' ');//每个灯都点亮
			putchar('\n');continue; 
		}
		solve();
	}
	return 0;
}
```

---

## 作者：wosile (赞：2)

场切了，但是做法是 $O(2^{n}t)$ 的，赛时做法现在会 `Time limit exceeded on test 65`。

首先这道题这个 $\lfloor\dfrac{n}{5}\rfloor$ 显得非常不友好。这个条件基本没法做。

然后发现这是个长得跟质数筛一样的东西，每个数会被自己的因数翻转，翻转奇数次会变成亮的。

然后和因数个数奇偶相关的就是平方数。具体来讲，平方数的因数个数是奇数，而如果我们按下所有按钮，就只有平方数会是亮的。

只要 $n \ge 20$，$[1,n]$ 内的平方数个数就不超过 $\lfloor\dfrac{n}{5}\rfloor$ 个。此时可以按下所有按钮，显然这样做一定满足限制条件。

否则 $n\le19$，考虑大力枚举。

赛时我直接枚举了按下哪些按钮然后一通缩点剪枝 $O(2^n)$，居然过了 Pretest 和 System Test。出题人还是太年轻了。

正解是枚举最终哪些灯是亮的，然后直接扫一遍就可以求出需要怎么按（跟线性基一样），再扫一遍判断限制是否满足，这样是小常数 $O(n^4)$，可以通过。

附一种正解代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
int lim[25],val[25];
vector<int>v[25];
int main(){
	scanf("%d",&T);
	for(int i=1;i<=19;i++)for(int j=2;j<(1<<(i+1));j+=2)if(__builtin_popcount(j)<=i/5)v[i].push_back(j);
	while(T--){
		scanf("%d%d",&n,&m);
		if(n<20)for(int i=1;i<=n;i++)lim[i]=val[i]=0;
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			if(n<20)lim[u]|=(1<<v);
		}
		if(n>=20){
			printf("%d\n",n);
			for(int i=1;i<=n;i++)printf("%d ",i);
			printf("\n");
			continue;
		}
		for(int i=1;i<=n;i++)for(int j=i;j<=n;j+=i)val[i]|=(1<<j);
		int ans=-1;
		for(int r:v[n]){
			int b=0,p=0,l=0;
			for(int i=1;i<=n;i++){
				if(((1<<i)&b)!=((1<<i)&r)){
					p^=(1<<i);
					b^=val[i];
					l|=lim[i];
				}
			}
			if((l&p)==l){
				ans=p;
				break;
			}
		}
		if(ans==-1)printf("-1\n");
		else{
			printf("%d\n",__builtin_popcount(ans));
			for(int i=1;i<=n;i++)if((1<<i)&ans)printf("%d ",i);
			printf("\n");
		}
	}
	// quod erat demonstrandum
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

[题目传送门（luogu）](https://www.luogu.com.cn/problem/CF1909E)

[题目传送门（CF）](https://codeforces.com/problemset/problem/1909/E)

典题。

非常容易发现一个结论，就是当 $20 \le n$ 时，点燃所有灯即可满足所有要求，同样好求的，当 $n \le 4$ 时，一定无法满足要求，接下来我们考虑 $5 \le n \le  19$ 的情况。我们可以考虑直接枚举最后亮着的灯是哪几盏，容易发现，当 $n \le 9$ 时，最后亮着的灯的情况**最多**只有一盏，当 $n \le 14$ 时，最后亮着的灯的情况**最多**只有两盏，当 $n \le 19$ 时，最后亮着的灯的情况**最多**只有三盏，因此我们就可以在这个方面去剪枝，剪枝后可以通过此题。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define QwQ return 0;
#define ll long long
#define endl '\n'
ll t,n,m,a[500010],b[500010],vis[500010],fl[500010],ans[500010];
//fl每盏灯灯泡状况，vis点燃灯泡编号
bool pd()
{
    forl(i,1,n)
		fl[i]=0,ans[i]=0;
    for(int i=1;i<=n;i++)
        if(vis[i]!=fl[i])
		{
            ans[i]=1;
            for(int j=i;j<=n;j+=i) 
				fl[j]^=1;
        }
    forl(i,1,m)
		if(ans[a[i]] && !ans[b[i]]) 
			return 0;
    return 1;
}
void solve()
{
	forl(i,1,n)
		vis[i]=0;
    for(int i=1;i<=n;vis[i++]=0)
	{
        vis[i]=1; 
		if(pd())
		{
		    vector<int>id;
		    forl(ii,1,n)
				if(ans[ii])
					id.pb(ii);
		    cout<<id.size()<<endl;
		    for(int ii:id) 
				cout<<ii<<" ";
		    cout<<endl;
			return ;
		}
		if(n/5>=2) 
	        for(int j=i+1;j<=n;vis[j++]=0)
			{
	            vis[j]=1; 
					if(pd()) 
					{
					    vector<int>id;
					    forl(ii,1,n)
							if(ans[ii])
								id.pb(ii);
					    cout<<id.size()<<endl;
					    for(int ii:id) 
							cout<<ii<<" ";
					    cout<<endl;	
						return ;
					}
				if(n/5>=3) 
		            for(int k=j+1;k<=n;vis[k++]=0)
		            {
		            	vis[k]=1;
		                if(pd()) 
		                {
						    vector<int>id;
						    forl(ii,1,n)
								if(ans[ii])
									id.pb(ii);
						    cout<<id.size()<<endl;
						    for(int ii:id) 
								cout<<ii<<" ";
						    cout<<endl;
		                	return ;
						}
					}
			}
    }
	cout<<-1<<endl;
}
int main()
{
	IOS;
	cin>>t;
    while(t--)
	{
	    cin>>n>>m;
	    forl(i,1,m) 
			cin>>a[i]>>b[i];
	    if(n>=20)
		{
	        cout<<n<<endl;
	        forl(i,1,n)
				cout<<i<<" ";
	        cout<<endl;
	    }
		else if(n<=4) 
			cout<<-1<<endl;
	    else
			solve();		
	}
	QwQ;
}
```

---

## 作者：EuphoricStar (赞：1)

感觉这个题比较难蚌。

发现按 $1 \sim n$ 最后可以把 $1 \sim n$ 中的所有平方数点亮。所以 $n \ge 20$ 就直接输出 $1 \sim n$。

考虑 $n \le 19$。猜测合法的方案（即按完后亮灯数 $\le \left\lfloor\frac{n}{5}\right\rfloor$ 的方案，不考虑 $(u, v)$ 的限制）不会很多。打表发现 $n = 19$ 时仅有 $1159$ 种。于是把合法方案预处理出来即可。

赛时智障了，所以直接把表放到代码里了。

[code](https://codeforces.com/contest/1909/submission/238582910)

---

## 作者：User_Unauthorized (赞：0)

可以发现，若将按钮全部操作一遍，灯 $i$ 被点亮当且仅当 $i$ 的约数个数为奇数，即 $i$ 为完全平方数。可以发现这样的数有 $\lfloor \sqrt{n} \rfloor$ 个，因此当 $n \ge 20$ 时将按钮全部操作一遍即可。

对于 $n < 20$ 的情况，可以预处理出不考虑边的限制下所有合法方案，然后枚举每一个方案，若其满足边的限制那么就找到了一组合法方案。

---

