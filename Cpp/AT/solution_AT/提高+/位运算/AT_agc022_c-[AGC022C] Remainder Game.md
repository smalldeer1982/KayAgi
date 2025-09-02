# [AGC022C] Remainder Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc022/tasks/agc022_c

アオキは数列 $ a_{1},\ a_{2},\ ...,\ a_{N} $ で遊んでいます。$ 1 $ 秒ごとに、アオキは次の操作を行います。

- 正の整数 $ k $ を選ぶ。数列のそれぞれの要素 $ v $ について、アオキは $ v $ を「$ v $ を $ k $ で割った余り」に置き換えるか、$ v $ をそのままにするかを選べる。この一連の操作のコストは（書き換えた要素の数によらず）$ 2^{k} $ である。

アオキは、数列を $ b_{1},\ b_{2},\ ...,\ b_{N} $ に変えたいです（要素の順番も考慮します）。この目的を達成することが可能か判定し、可能である場合は必要な最小のコストを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 0\ \leq\ a_{i},\ b_{i}\ \leq\ 50 $
- 入力中の値はすべて整数である。

### Sample Explanation 1

操作手順の例を挙げます。 - $ k\ =\ 7 $ を選ぶ。$ 19 $ を $ 5 $ に、$ 10 $ を $ 3 $ に置き換えて $ 14 $ はそのままにする。数列は $ 5,\ 3,\ 14 $ となる。 - $ k\ =\ 5 $ を選ぶ。$ 5 $ を $ 0 $ に置き換え、$ 3 $ はそのままにして $ 14 $ を $ 4 $ に置き換える。数列は $ 0,\ 3,\ 4 $ となる。 合計コストは $ 2^{7}\ +\ 2^{5}\ =\ 160 $ です。

### Sample Explanation 2

$ k\ =\ 1 $ を選び、すべてを $ 0 $ に変えるとよいです。コストは $ 2^{1}\ =\ 2 $ です。

### Sample Explanation 3

与えられた操作では $ 8 $ を $ 5 $ に変えることができないため、目的の達成は不可能です。

### Sample Explanation 4

この場合は何もする必要がありません。コストは $ 0 $ です。

### Sample Explanation 5

オーバーフローにご注意。

## 样例 #1

### 输入

```
3
19 10 14
0 3 4```

### 输出

```
160```

## 样例 #2

### 输入

```
3
19 15 14
0 0 0```

### 输出

```
2```

## 样例 #3

### 输入

```
2
8 13
5 13```

### 输出

```
-1```

## 样例 #4

### 输入

```
4
2 0 1 8
2 0 1 8```

### 输出

```
0```

## 样例 #5

### 输入

```
1
50
13```

### 输出

```
137438953472```

# 题解

## 作者：邈云汉 (赞：3)

和楼下差不多的思路，~~感觉本人码风更易读~~。就是贪心去做，从高位开始，除非不得不选，不然坚决不选，这样一定是最优的。

证明：

对于一个二进制数的第 $k$ 位，就算后面全是 $1$，那么后面部分的值就是 $2^k -1$，而若第 $k$ 位为 $1$，就算后面全是 $0$，则后 $k$ 位的值就是 $2^k$，显然大于 $2^k -1$。所以，从高位开始，如果通过后面的操作能完成任务，就交给后面的去完成，这样答案一定更优。

这么一来，我们的核心任务就转变为如何判定某一个 $k$ 不得不选。根据贪心原则，到某一位时，比它更高的位置必然已经确定好了。我们先假设不选，看看能不能在已有的必选的模数中通过操作完成任务，如果不能，就只能选了。这个判定有点类似于传递闭包，数据范围很小，直接暴力枚举就好。

```
#include<bits/stdc++.h>
using namespace std;
const int N=55;
int n,a[N],b[N],used[N],s[N][N];
bool check()
{
	memset(s,0,sizeof s);
	for(int i=1;i<=n;i++)s[i][a[i]]=1;
	for(int i=51;i;i--)
	{
		if(!used[i])continue;
		for(int j=1;j<=n;j++)
			for(int k=a[j];k>=i;k--)
				s[j][k%i]|=s[j][k];
	}
	for(int i=1;i<=n;i++)if(!s[i][b[i]])return false;
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	long long ans=0;
	for(int i=1;i<=51;i++)used[i]=1;
	if(!check()){printf("-1");return 0;}
	for(int i=51;i;i--)
	{
		used[i]=0;
		if(!check())used[i]=1,ans+=1ll<<i;
	}
	printf("%lld",ans);
	return 0;
}

---

## 作者：Krimson (赞：3)

~~一开始脑抽还想跑费用流，才发现根本没法跑~~  
其实仔细想一想题目里的暗示已经很明显了，$2^k$ 这种权值意味着是从高位往低位贪心。  

那么从高位往低位贪心，枚举当前位能不能不选。  
这个贪心部分可以 $O(n)$ 实现~~不是n，但是同阶~~，接下来考虑如何实现一次 check。  
对于单个数 $a_i$，对它开一个大小为 $50$ 的桶，然后枚举当前能取的模数（有交换律，怎么枚举都行），判断一下是否出现过 $b_i$ 。这个部分是 $n^2$ 的，可以用bitset优化到 $O(n\log n)$。  
最后统计一下答案就行了。  


_Code_
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n;
const int MAXN=512;
ll a[MAXN],b[MAXN],c[MAXN],ans,base[MAXN];
char vis[64][64],is[64];
bool check(){
    for(ri i=1;i<=n;++i){
        memset(vis[i],0,sizeof(vis[i]));
        vis[i][a[i]]=1;
    }
    for(ri i=50;i;--i){
        if(!is[i]) continue;
        for(ri j=1;j<=n;++j){
            for(ri k=a[j];k>=i;--k){
                if(vis[j][k]) vis[j][k%i]=1;
            }
        }
    }
    for(ri i=1;i<=n;++i){
        if(!vis[i][b[i]]) return 0;
    }
    return 1;
}
int main(){
    n=read();
    base[0]=1;
    memset(is,1,sizeof(is));
    for(ri i=1;i<=50;++i) base[i]=base[i-1]<<1;
    for(ri i=1;i<=n;++i) a[i]=read();
    for(ri i=1;i<=n;++i) b[i]=read();
    if(!check()) return !puts("-1");
    for(ri i=50;i;--i){
        is[i]=0;
        if(!check()) is[i]=1;
    }
    for(ri i=50;i;--i) 
        if(is[i]) ans=ans+base[i];
    print(ans);
    return 0;
}
```


---

## 作者：run_away (赞：1)

## 题意

给 $n$ 个整数 $a_i$，可以对它们进行若干次操作：每次可以选择一个整数 $k$ 和数组中的一些数，花费 $2^k$ 的代价，给这些数赋值为原值对 $k$ 取模的值。

求出最小的花费，使得数组 $a$ 变成数组 $b$，如果不存在这种方案，输出 $-1$。

## 分析

注意到题目里的 $n,k$ 范围都很小，并且每次操作的代价都是 $2$ 的次幂，所以可以按位考虑。

如果选择一个数 $k$，那么选它的代价比选择 $1\sim k-1$ 的代价和都要大，所以从大到小枚举 $k$，写一个 check 判断这个数是不是必须选取。

给每一个位置开一个 bool 数组，记录当前位置是否可以变成一个数，每次初始给 $vis_{i,a_i}$ 赋值为 $1$。

然后再枚举一遍 $k,n$，枚举可能产生的值，把它们对应的位置赋为 $1$，具体可以看代码。

最后看看第 $i$ 位能不能变成 $b_i$ 就可以了，注意开始的时候判断一下有没有解。

代码里用了 bitset，还能给时间复杂度除个 $w$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const ll mod=998244353,maxn=55,maxt=505;
ll n,a[maxn],b[maxn],f[maxn];
bitset<maxn>vis[maxn];
inline bool chk(){
	for(ll i=1;i<=n;++i)vis[i].reset();
	for(ll i=1;i<=n;++i)vis[i][a[i]]=1;
	for(ll i=51;i>=1;--i){
		if(!f[i])continue;
		for(ll j=1;j<=n;++j){
			for(ll k=a[j];k>=i;--k){
				vis[j][k%i]=vis[j][k%i]|vis[j][k];
			}
		}
	}
	for(ll i=1;i<=n;++i)if(!vis[i][b[i]])return 0;
	return 1;
}
inline void solve(){
	n=read();
	for(ll i=1;i<=n;++i)a[i]=read();
	for(ll i=1;i<=n;++i)b[i]=read();
	for(ll i=1;i<=51;++i)f[i]=1;
	if(!chk())return write(-1),void();
	ll ans=0;
	for(ll i=51;i>=1;--i){
		f[i]=0;
		if(!chk())f[i]=1,ans+=(1ll<<i);
	}
	write(ans);
}
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	ll t=1;
	while(t--){
		solve();
	}
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

你看到这个 $2^k$ 和这个非常小的数据范围就会想到按位贪心，从高到低枚举 $k$，如果即使后面的 $k$ 全用上都不能合法就不得不选这个 $k$ 了。

判断合法时设计状态 $f_{i, j}$ 表示从 $a_i$ 可以走到 $j$，被动转移有 $f_{i, j \bmod k} \gets f_{i, j \bmod k} \vee f_{i, j}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 55;
int n, a[N], b[N];

bool o[N], f[N][N];
bool check() {
	memset(f, false, sizeof f);
	for (int i = 1; i <= n; i++) f[i][a[i]] = true;
	for (int k = N - 1; k >= 1; k--) if (o[k])
		for (int i = 1; i <= n; i++) 
			for (int j = a[i]; j >= k; j--)
				f[i][j % k] |= f[i][j];
	for (int i = 1; i <= n; i++) if (!f[i][b[i]])
		return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	fill(o + 1, o + N, true);	
	if (!check()) return cout << -1, 0;
	ll ans = 0;
	for (int k = N - 1; k >= 1; k--) {
		o[k] = false;
		if (!check()) o[k] = true, ans += (1ll << k);
	}
	cout << ans;
	return 0;
}
```

---

