# [ARC118C] Coprime Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc118/tasks/arc118_c

正の整数 $ N $ が与えられます。整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ であって、次の条件をすべて満たすものをひとつ出力してください。

- $ 1\leq\ A_i\leq\ 10000 $
- $ i\neq\ j $ に対して、$ A_i\neq\ A_j $ かつ $ \gcd(A_i,\ A_j)\ >\ 1 $
- $ \gcd(A_1,\ A_2,\ \ldots,\ A_N)\ =\ 1 $

なお、この問題の制約のもとで、条件を満たす整数列が存在することが証明できます。

## 说明/提示

### 制約

- $ 3\leq\ N\leq\ 2500 $

### Sample Explanation 1

\- $ \gcd(84,60)\ =\ 12 $ - $ \gcd(84,105)\ =\ 21 $ - $ \gcd(84,70)\ =\ 14 $ - $ \gcd(60,105)\ =\ 15 $ - $ \gcd(60,70)\ =\ 10 $ - $ \gcd(105,70)\ =\ 35 $ - $ \gcd(84,60,105,70)\ =\ 1 $ が成り立ち、すべての条件が満たされていることが確認できます。

## 样例 #1

### 输入

```
4```

### 输出

```
84 60 105 70```

# 题解

## 作者：_hxh (赞：1)

### 题意

构造一个大小为 $n$ 的数组 $A$，使 $A$ 满足以下条件：

1. $\forall A_i$，$1 \le A_i \le 10^4(1 \le i \le n)$；
2. 任意两数的最大公约数**大于** 1；
3. 所有数的最大公约数**等于** 1。

### 分析

既然是构造题，就不要被样例迷惑。设三个互质的数 $a,b,c(a,b,c > 1)$，那么 $ab,ac,bc$ 就是一组满足条件的数。最小的满足条件的数就是 $2,3,5$，这时 $ab,ac,bc$ 为 $6,10,15$。这是 $n = 3$ 时的答案。发现 $6,10,15$ 的倍数也是符合要求的答案，所以当 $n > 3$ 时只要补上 $6k,10k,15k(k \in \mathbb N+,k \ge 2)$ 就行了。计算得出符合要求的数的数量大于 $2500$ 个，所以此方案可行。

**一定要注意去重**。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int n,cnt = 3;
bool a[N];
int main()
{
	cin >> n;
	cout << "6 10 15 ";
	for (int i = 1;;i++)
	{
		if ((i % 6 == 0 || i % 10 == 0 || i % 15 == 0) && i != 6 && i != 10 && i != 15)
		{
			cout << i << " ";
			cnt++;
		}
		if (cnt == n)
			break;
	}
	return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

给定 $n$，构造一个长度为 $n$ 的数组，满足任意两个数不互质且不相同，所有数的最大公因数为 $1$，且每个数最大为 $10000$。

## 分析

这种限制了数的大小，不限制大小和位置关系的构造题有一个套路。

先找出几个最小的满足条件的数，然后找出延申的条件。

对于本题，当 $n=3$ 时，有一组最简单的答案是 $6,10,15$，它们分别是 $2\times3,2\times 5,3\times5$。

可以发现这三个数的倍数只要不是另外两个数的倍数都可以加入数组。

所以可以枚举这三个数的倍数，把符合条件的数保留。

总时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar(' ');return;}char top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar(' ');}
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const ll mod=1e9+7,maxn=1e5+5,maxt=505;
ll n;
vector<ll>q;
inline void solve(){
    n=read()-3;
    write(6),write(10),write(15);
    for(ll i=2;i*6<=10000&&q.size()<n;++i){
        q.push_back(i*6);
    }
    for(ll i=2;i*10<=10000&&q.size()<n;++i){
        if(i*10%6==0)continue;
        q.push_back(i*10);
    }
    for(ll i=2;i*15<=10000&&q.size()<n;++i){
        if(i*15%6==0||i*15%10==0)continue;
        q.push_back(i*15);
    }
    for(auto x:q)write(x);
}
signed main(){
    ll t=1;
    while(t--){
        solve();
    }
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：wwqwq (赞：1)

构造题。

设 $a=x\times y,b=x\times z,c=y\times z$，其中 $x,y,z$ 互质，则 $(a,b)=x,(a,c)=y,(b,c)=z,(a,b,c)=1$。

因为 $1$ 和任意数的最大公因数都为 $1$，所以我们只需要构造三个数满足上文的 $a,b,c$ 即可。因为 $A_i\le 10000$，所以构造的越小越好，$2\times 3,2\times 5,3\times 5$ 即 $6,10,15$ 能很好的满足要求。

已经解决了第三个要求，接下来完成第一和第二个要求。因为 $(a,b),(a,c),(b,c)$ 都不为 $1$，所以它们的倍数的最大公约数也不为 $1$。因此只需要构造 $6,10,15$ 的倍数即可，注意去重和判断有没有超过 $10000$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
	int n;
	cin >> n;
	int cnt = 0;
	cout << "6 10 15 ";
	for (int i = 2; cnt <= n - 4 && 6 * i <= 10000; i++) {
		cout << 6 * i << ' ';
		cnt++;
	} 
	for (int i = 2; cnt <= n - 4 && 10 * i <= 10000; i++) {
		if (10 * i % 6 != 0) {
			cout << 10 * i << ' ';
			cnt++;
		}
	} 	
	for (int i = 2; cnt <= n - 4 && 15 * i <= 10000; i++) {
		if (15 * i % 6 != 0 && 15 * i % 10 != 0) {
			cout << 15 * i << ' ';
			cnt++;
		}
	} 
	return 0;
}
```

---

## 作者：incra (赞：0)

### Sol
不难想到可以构造 `6 10 15 x x x`，显然两两最大公约数不为 $1$，且三项的最大公约数为 $1$，后面的只需要填入 `6,10,15` 的倍数即可，注意不能重复。
### Code
[Link](https://atcoder.jp/contests/arc118/submissions/63927233)。

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

可以先考虑 $n=3$ 的做法。

拿三个互质的数 $a,b,c$，那么答案 $ab,bc,ac$ 一定是满足条件的。$A_i$ 的限制比较紧，我们尽量让 $a,b,c$ 小，所以 $a=2,b=3,c=5$。

考虑让 $n$ 更大。

显然若有一个数 $d$ 满足 $d|2,d|3,d|5$ 中的任意两项，那么 $d$ 就是合法的。所以 $d$ 可以是 $6,10,15$ 的任意 $\le 10^4$ 的倍数。

打表可知 $[1,10^4]$ 中 $6,10,15$ 的倍数总共有 $2663$ 个，满足题目要求。

如果像我一样从小到大在数组里输出的话，注意一定要先输出 `6 10 15` 再输出它们的倍数。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
typedef __int128 lint;
//typedef long long ll;	
typedef pair<int,int> pii;
const int N=1e4,mod=998244353;
const db eps=1e-9;

int n,cnt=0;
bool vis[N+5];

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(Ri i=2;i*6<=N;i++)vis[i*6]=1;
	for(Ri i=2;i*10<=N;i++)vis[i*10]=1;
	for(Ri i=2;i*15<=N;i++)vis[i*15]=1;
	cin>>n;cout<<"6 10 15 ";n-=3;
	for(Ri i=1;cnt^n;i++)if(vis[i]){cout<<i<<' ';cnt++;}
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

我们可以考虑一组满足条件的“汤底”，这可以由三个质数两两相乘，这里我们取最小三个质数构成的 $6,10,15$。我们可以发现，比如说我们在这组汤底里加入 $6,10,15$ 的任意倍数，这组数仍然满足条件。那么构造方法就出来了，我们不断往这个汤底里加入 $6,10,15$ 的倍数，不过注意不能重复。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 998244353
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll n;
//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	cout << 6 << " " << 15 << " " << 10;//汤底
	n -= 3;
	for(int i = 2; i * 6 <= 10000 && n > 0; i++){
		cout << " " << i * 6;
		n--;
	}
	if(n != 0){
		for(int i = 2; i * 10 <= 10000 && n > 0; i++){
			if(i * 10 % 6 != 0){//不能重复
				cout << " " << i * 10;
				n--;
			}
		}
		if(n != 0){
			for(int i = 2; i * 15 <= 10000 && n > 0; i++){
				if(i * 15 % 6 != 0 && i * 15 % 10 != 0){//不能重复
					cout << " " << i * 15;
					n--;
				}
			}
		}
	}
	cout << endl;
	return 0;
}



```

---

## 作者：loser_seele (赞：0)

喜提了最劣解。

首先考虑 $ n $ 较小的情况，显然可以构造出一个子集 $ 6,10,15 $。接下来考虑 $ n $ 较大的情况。

不难发现 $ \gcd(ka,b) \geq \gcd(a,b) $，则我们可以直接把 $ 6,10,15 $ 的倍数全部塞进去一个数组里，最后排序后输出前 $ n $ 大的即可。

注意 $ n=3 $ 的时候要特判，时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=1e7+10;
vector<int>p;
bitset<maxn>vis;
int main() 
{
	int n;
	cin>>n;
	if(n==3) 
	{
		cout<<"6 10 15";
		return 0;
	}
	for (int i=1;i<=maxn/6;i++)
	if(!vis[i*6])
	p.push_back(i*6),vis[i*6]=1;
	for (int i=1;i<=maxn/10;i++)
	if(!vis[i*10])
	p.push_back(i*10),vis[i*10]=1;
	for (int i=1;i<=maxn/15;i++)
	if(!vis[i*15])
	p.push_back(i*15),vis[i*15]=1;
	sort(p.begin(),p.end());
	for (int i=0;i<n;i++)
	cout<<p[i]<<' ';
}
```


---

