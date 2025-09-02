# Playoff Fixing

## 题目描述

$ 2^k $ teams participate in a playoff tournament. The teams are numbered from $ 1 $ to $ 2^k $ , in order of decreasing strength. So, team $ 1 $ is the strongest one, team $ 2^k $ is the weakest one. A team with a smaller number always defeats a team with a larger number.

First of all, the teams are arranged in some order during a procedure called seeding. Each team is assigned another unique value from $ 1 $ to $ 2^k $ , called a seed, that represents its starting position in the playoff.

The tournament consists of $ 2^k - 1 $ games. They are held as follows: the teams are split into pairs: team with seed $ 1 $ plays against team with seed $ 2 $ , team with seed $ 3 $ plays against team with seed $ 4 $ (exactly in this order), and so on (so, $ 2^{k-1} $ games are played in that phase). When a team loses a game, it is eliminated.

After that, only $ 2^{k-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, $ 2^{k-2} $ games are played: in the first one of them, the winner of the game "seed $ 1 $ vs seed $ 2 $ " plays against the winner of the game "seed $ 3 $ vs seed $ 4 $ ", then the winner of the game "seed $ 5 $ vs seed $ 6 $ " plays against the winner of the game "seed $ 7 $ vs seed $ 8 $ ", and so on. This process repeats until only one team remains.

After the tournament ends, the teams are assigned places according to the tournament phase when they were eliminated. In particular:

- the winner of the tournament gets place $ 1 $ ;
- the team eliminated in the finals gets place $ 2 $ ;
- both teams eliminated in the semifinals get place $ 3 $ ;
- all teams eliminated in the quarterfinals get place $ 5 $ ;
- all teams eliminated in the 1/8 finals get place $ 9 $ , and so on.

Now that we established the rules, we do a little rigging. In particular, we want:

- team $ 1 $ (not team with seed $ 1 $ ) to take place $ 1 $ ;
- team $ 2 $ to take place $ 2 $ ;
- teams $ 3 $ and $ 4 $ to take place $ 3 $ ;
- teams from $ 5 $ to $ 8 $ to take place $ 5 $ , and so on.

For example, this picture describes one of the possible ways the tournament can go with $ k = 3 $ , and the resulting places of the teams:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1837E/6784d7734c1bc22d2e87b4af1fba0e4f6b4692a1.png)Some seeds are already reserved for some teams (we are not the only ones rigging the tournament, apparently). We have to fill the rest of the seeds with the remaining teams to achieve the desired placements. How many ways are there to do that? Since that value might be large, print it modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
2
1 2 3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
2
1 3 4 2```

### 输出

```
1```

## 样例 #3

### 输入

```
1
-1 -1```

### 输出

```
2```

## 样例 #4

### 输入

```
2
-1 -1 -1 -1```

### 输出

```
16```

## 样例 #5

### 输入

```
3
-1 -1 -1 -1 2 -1 -1 -1```

### 输出

```
768```

## 样例 #6

### 输入

```
0
1```

### 输出

```
1```

# 题解

## 作者：离散小波变换° (赞：14)

## 题解

记 $n=2^k$。容易发现，编号为 $(n/2+1)\sim n$ 的队伍，必须要在第一轮被淘汰。

那么对于形如 $2i-1$ 和 $2i$ 的位置，这两个位置里必须**恰好**有一支队伍的编号在 $(n/2+1)\sim n$。这能告诉我们安排编号为 $(n/2+1)\sim n$ 的队伍的方案数。对于每一个形如 $2i-1$ 和 $2i$ 的位置对：

- 如果 $a_{2i-1}$ 和 $a_{2i}$ 都为 $-1$，那么可以放恰好一个被淘汰的队伍，有两种放法；
- 如果 $a_{2i-1}$ 和 $a_{2i}$ 有一个是 $-1$，另一个在 $1\sim (n/2)$，那么可以放恰好一个被淘汰的队伍，有一种放法；
- 如果 $a_{2i-1}$ 和 $a_{2i}$ 都在 $1\sim (n/2)$ 或者都在 $(n/2+1)\sim n$，那一定是无解；
- 别的情况不会对方案数产生影响。

公式化一点，假设一共有 $x$ 个被淘汰的队伍需要安排位置，共有 $y$ 个第一种情况，并且在安排被淘汰的队伍时没有出现必定无解的情况，那么这些被淘汰的队伍的安排方法共有 $x!\times 2^y$ 个。

假设现在安排好了那些被淘汰的队伍。然后我们发现剩下来的队伍就变成了一个规模折半的子问题。因为那些被淘汰的队伍的安排方式并不会影响到剩下来的队伍的安排情况，所以可以应用乘法原理，将每个子问题的方案数给乘起来。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = (1 << 19) + 3;
const int MOD  = 998244353;
int F[MAXN], G[MAXN];
int solve(vector <int> V){
    if(V.size() == 1) return 1;
    int ret = 1, n = V.size(), t = n / 2;
    int c = 0, d = n / 2, e = 0;
    vector <int> T;
    up(0, n - 1, i) d -= (V[i] > t);
    up(0, n / 2 - 1, i){
        int p = 2 * i;
        int q = 2 * i + 1;
        if(V[p] != -1 && V[q] != -1){
            if((V[p] <= t) == (V[q] <= t))
                return 0;
        }
        {
            if(V[p] == -1 && V[q] == -1) ++ c;
            if(V[p] != -1 && V[p] <= t) T.push_back(V[p]); else 
            if(V[q] != -1 && V[q] <= t) T.push_back(V[q]); else 
                T.push_back(-1);
        }
    }
    return 1ll * G[c] * F[d] % MOD * solve(T) % MOD;
}
int main(){
    int k = qread(); vector <int> P;
    G[0] = F[0] = 1;
    up(1, 1 << k, i)
        G[i] = 1ll * G[i - 1] * 2 % MOD,
        F[i] = 1ll * F[i - 1] * i % MOD;
    up(1, 1 << k, i) P.push_back(qread());
    printf("%d\n", solve(P));
    return 0;
}
```

---

## 作者：封禁用户 (赞：7)

# 题意
我们有 $2^k$ 支队伍，强弱依次排列，$1$ 号最强，$2^k$ 号最弱。我们从左到右排列这些队伍，每一轮第一支队伍和第二支队伍对决，第三只队伍和第四只队伍对决，等。这些对决同时进行，实力较弱的队伍将在对决中被淘汰，从这一排队伍中删除。一轮淘汰赛后，这一排队伍的长度会减半。如下图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1837E/6784d7734c1bc22d2e87b4af1fba0e4f6b4692a1.png)

那么一些位置已经被内定了，我们要求得队伍可以排列的方案总数，可以使每一轮淘汰的都是当前这一排中最弱的 $2^{k-i}$ 支队伍，即最弱的一半。

# 思路
纯数学解法。

我们先自己造一个数据：

### 输入
```
3
-1 -1 2 -1 -1 6 -1 8
```

### 输出
```
16
```

首先我们先思考已经内定的队伍。先画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m70wth0e.png)

绿色表示内定。

我们发现，其实我们完全可以推断出已经内定的人可以走到哪里。因为第 $i$ 轮淘汰 $2^{k-i}$ 支队伍，剩的也是 $2^{k-1}$ 支队伍，所以只需要枚举，算出什么时候会被淘汰。

![](https://cdn.luogu.com.cn/upload/image_hosting/ngvwoxjz.png)

现在已经画出来了。我们再倒推：第一轮一定只有 $1$，第二轮是 $1$ 和 $2$，以此类推。

所以，这一轮会被淘汰的队伍，放在所有地方都可以，但是不会被淘汰的一定不能放在一起，不然就会淘汰掉不该淘汰的队伍。

那我们先假设，下一轮会晋级的全部先分配在每一个小组固定的位置里，不考虑顺序。

对于这一层要被淘汰的，他们在之前互相调换也不会改变之后的事，所以方案数就是这一层淘汰的数量 $p$ 的全排列数，即 $A_p^p$。但实际上，有一些队伍内定了位置（我们之前预处理算自己在哪一层的时候就会存一下当前层的剩余自由位置），我们设有 $q$ 个会被淘汰的队伍已经内定，所以对于这一层的方案数是 $A_{p-q}^{p-q}$。

拿一张无内定情况的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i9bjvdif.png)

但别忘了，我们要晋级的队伍是不考虑左右交换的。我们把它拉出来考虑。

我们思考每一个小组的左右两个数：如果有某一个或两个是已经被内定的（之前预处理过），左右不能交换。现在都不确定的，可以交换，乘二。

![](https://cdn.luogu.com.cn/upload/image_hosting/3z88afpq.png)

用紫色标出了可以换的。

答案即为每一层的空位安置方案数乘上可以左右交换的带来的贡献。

在本图中，可安放的数量为 $A_1^1 \times A_2^2 \times A_2^2$，可左右交换的为 $2^2$，乘起来即为 $16$。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int k,n;
int a[1000011];
int c[31];
const int mod=998244353;
int zh[1000011][22];
int dg(int l,int r,int lt){
	if(lt==0){
		return 1;
	}else{
		if(zh[l][lt]){
			return ((dg(l,(l+(1<<(lt-1))-1),lt-1)%mod*dg((l+(1<<(lt-1))),r,lt-1)%mod)%mod)%mod;
		}else{
			return (((dg(l,(l+(1<<(lt-1))-1),lt-1)%mod*dg((l+(1<<(lt-1))),r,lt-1)%mod)%mod)*2)%mod;
		}
	}
}
bool ccp=0;
int bg(int l,int r,int lt){
	if(lt==0){
		return a[l];
	}else{
		int ll=bg(l,(l+(1<<(lt-1))-1),lt-1);
		int rr=bg((l+(1<<(lt-1))),r,lt-1);
		if(ll==-1||rr==-1){
			if(ll==-1&&rr==-1){
				return -1;
			}else if(max(ll,rr)<=pow(2,k-lt)){
				return max(ll,rr);
			}else{
				return -1;
			}
		}
		if(ccp){
			return max(ll,rr);
		}
		if(min(ll,rr)>pow(2,k-lt)){
			ccp=1;
		}
		if(max(ll,rr)<=pow(2,k-lt)){
			ccp=1;
		}
		return min(ll,rr);
	}
}
unordered_map<int,bool> mp;
signed main(){
//	freopen("12.out","r",stdin);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld",&k);
	n=pow(2,k);
//	cout<<k<<endl;
	f(i,1,n){
		scanf("%lld",&a[i]);
		if(a[i]!=-1&&mp[a[i]]){
			cout<<0<<endl;
			return 0;
		}
		mp[a[i]]=1;
	}
	int o=bg(1,n,k);
	if(ccp){
		cout<<0<<endl;
		return 0;
	}
	c[k]=c[k+1]=1;
	f(i,1,k-1){
		c[i]=pow(2,k-i);
	}
	f(i,1,n){
		if(a[i]==-1){
			continue;
		}
		int qq=n,j=0;
		while(a[i]<=qq){
//			c[kk]--;
			j++;
			qq/=2;
//			cout<<i<<" "<<j<<" "<<((i-1)/(int)pow(2,j))*(int)pow(2,j)+1<<endl;
			zh[((i-1)/(int)pow(2,j))*(int)pow(2,j)+1][j]=1;
		}
//		cout<<a[i]<<" "<<j<<endl;
		c[j]--;
//		f(j,1,k){
//		}
	}
//	f(i,1,n){
//		for(int j=1;i+(1<<j)-1<=n;j++){
//			cout<<"--"<<i<<' '<<i+(1<<j)-1<<"--\n";
//			cout<<zh[i][j]<<endl;
//		}
//	}
	int cnt=1;
	cnt=dg(1,n,k);
//	cout<<cnt<<endl;
	for(int i=1;i<=k+1;i++){
		f(j,2,c[i]){
			cnt=(cnt%mod*(j%mod))%mod;
		}
	}
	printf("%lld\n",cnt%mod);
	return 0;
}
```

---

## 作者：white_tiger_yyyy (赞：2)

首先来考虑什么情况方案数为 $0$：

1. 可以确定，在某一层中，两个原本都能晋级的队伍比赛；
2. 可以确定，在某一层中，两个原本都不能晋级的队伍比赛。

发现假如写出每一场比赛及其胜者，可以形成一棵树形结构，在里面打标记即可判断是否为 $0$。

我们设 $a_i$ 表示第 $i$ 层新加的队伍中位置没有确定的个数（这里是从根节点为第 $0$ 层），$b_i$ 为可以调换前后顺序的比赛个数，$dp_i$ 表示第 $i$ 层的情况数，则有：

$$dp_i=dp_{i-1}\times2^{a_i}\times b_i!$$

时间复杂度 $O(2^k)$。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=(1<<19)+5;
const ll p=998244353;
int k,n,t[20][N],a[20],b[20];
ll dp[20],jc[N];
ll qpow(ll x,int y){
    ll re=1;
    while(y){
        if(y&1) re=re*x%p;
        x=x*x%p;y>>=1;
    }return re;
}int check(int x,int y,int z){
    if(!x){
        t[x][y]=z;
        return 1;
    }if(t[x][y]) return 0;
    t[x][y]=z;
    if(z>(1<<(x-1))&&t[x][(y+1)/2*4-1-y]&&!t[x-1][(y+1)/2]) return 0;
    if(z>(1<<(x-1))) return 1;
    return check(x-1,(y+1)/2,z);
}int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>k;
    n=1<<k;
    jc[0]=dp[0]=1;
    for(ll i=1;i<=n;i++)
        jc[i]=jc[i-1]*i%p;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        if(x<0) continue;
        int g=check(k,i,x);
        if(!g){
            cout<<0;
            return 0;
        }
    }for(int i=1;i<=k;i++){
        for(int j=1;j<=(1<<i);j++){
            int l=t[i][j];
            if(l>(1<<(i-1))) b[i]++;
        }for(int j=1;j<=(1<<i);j+=2)
            if(t[i][j]||t[i][j+1]) a[i]++;
        a[i]=(1<<(i-1))-a[i];
        b[i]=(1<<(i-1))-b[i];
    }for(int i=1;i<=k;i++)
        dp[i]=dp[i-1]*qpow(2,a[i])%p*jc[b[i]]%p;
    cout<<dp[k];
    return 0;
}
```

---

## 作者：lalaouye (赞：2)

这是一道非常有意思的题。

设 $n$ 为当前队伍数量。

下面对于每个队伍的“数值”不是编号，而是能力。（比如说这时编号为 $1$ 的队伍能力为 $n$）。

思路清晰的，我们发现在初始状态下，每两格一组，每组之间是互相独立的。然后我们当前已经确定了一些队伍的位置，只知道这些发现很难去计算答案，因为这一次竞选完的队伍之后还有顺序要求，所以我们得到的性质仍然不够。

经过观察就会发现，每一组只可能有一个能力小于等于 $\frac{n}{2}$ 和一个能力大于 $\frac{n}{2}$ 的队伍组成。更重要的是，这一轮小于等于 $\frac{n}{2}$ 的队伍无论顺序怎么变都不会影响下一轮，并且直接到下一轮剩下的队伍的数量会减少一半！这提醒我们可以用类似于递归的方法解决问题。


我们设一个函数，$f(a)$ 表示当前编号数组为 $a$ 的安排位置方案，那么考虑一个转移：

$$f(a)=t\times f(a')$$

其中 $t$ 为转移系数，先想办法求 $a'$，考虑 $a'$ 的每一位，如果 $a_{2i}$ 或者 $a_{2i+1}$ 大于 $\frac{n}{2}$，那么显然已经确定，我们给每一个确定的队伍重新分配一个“相对”能力，具体实现可以自己想。反之这一位没有确定，就把 $-1$ 传下去。 当然了，如果每一组内的队伍能力都小于等于 $\frac{n}{2}$ 或者都大于 $\frac{n}{2}$ 显然无解。

接着想办法求转移系数，实际上就是当前这一轮要被淘汰的队伍的位置方案，其实比较好求，设 $tot$ 表示两个队伍都没有确定能力的组数，$k$ 表示可以自由分配位置的要被淘汰的队伍数量，那么 $t=k!\times2^{tot}$。因为完全没有确定的组相当于有 $2$ 个位置都可以放。

接下来就是实现问题，~~运用乘法交换律~~，发现不需要真的去递归，直接循环就可以了。

代码：

```
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rrp(i, l, r) for(int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
using namespace std;
constexpr int N = 6e5 + 5, P = 998244353;
typedef long long ll;
inline int rd ()
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, m, a[N], b[2][N];
int fac[N], inv[N];
int qpow (int x, int y)
{
    int ret = 1;
    for (; y; y >>= 1, x = x * x % P)
        if (y & 1) ret = ret * x % P;
    return ret;
}
void add (int &x, int y) { (x += y) >= P && (x -= P); }
int A (int n, int m) { return fac[n] * inv[n - m] % P; }
auto main () -> signed
{
    // freopen ("1.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    m = rd (); n = 1ll << m; rep (i, 1, n) a[i] = b[0][i] = rd ();
    rep (i, 1, n) if (b[0][i] < 0) b[0][i] = 1e9; else b[0][i] = n - b[0][i] + 1;
    fac[0] = 1;
    rep (i, 1, n) fac[i] = fac[i - 1] * i % P;
    inv[n] = qpow (fac[n], P - 2); inv[0] = 1;
    rrp (i, 1, n - 1) inv[i] = inv[i + 1] * (i + 1) % P;
    int ret = 1, p = 0; while (n > 1)
    {
        int Mi = n >> 1, tot = 0, sum = Mi; 
        rep (i, 2, n) if (b[p][i] <= Mi && b[p][i - 1] <= Mi)
            return puts ("0"), 0; else ++ i;
        rep (i, 2, n)
            if (b[p][i] < 1e9 && b[p][i - 1] < 1e9)
                if (b[p][i] > Mi && b[p][i - 1] > Mi) return puts ("0"), 0;
            else ++ i; else ++ i;
        int tmp = 1; rep (i, 1, n) tot += (b[p][i] <= Mi); rep (i, 1, n) {
            ++ i; if (b[p][i] >= 1e9 && b[p][i - 1] >= 1e9) add (tmp, tmp);
        } ret = (ret * tmp % P * fac[Mi - tot] % P);
        rep (i, 1, Mi)
        { 
            b[p ^ 1][i] = max (b[p][(i << 1) - 1], b[p][i << 1]);
            if (b[p ^ 1][i] >= 1e9)
            {
                if (b[p][(i << 1) - 1] < 1e9 && b[p][(i << 1) - 1] > Mi)
                    b[p ^ 1][i] = b[p][(i << 1) - 1];
                if (b[p][i << 1] < 1e9 && b[p][i << 1] > Mi)
                    b[p ^ 1][i] = b[p][i << 1];
            } if (b[p ^ 1][i] < 1e9) b[p ^ 1][i] -= Mi;
        } p = ! p; n >>= 1;
    } printf ("%lld\n", ret);
}
```


---

## 作者：yshpdyt (赞：1)

## 题意
$2^k$ 位选手进行淘汰赛，每次相邻的两只队伍进行比赛，胜者进入下一轮。编号越靠前的队伍越强。给定 $2^k$ 个位置的选手编号，如果是 $-1$ 则可以任意安排。

求安排位置的方案数，使得每轮比赛都是编号最靠后的 $2^{k-i}$ 名选手被淘汰。
 
## Sol
做法可能在某些方面过复杂，主要看思路。
### Part 1 约定
定义剩下 $2^i$ 个人的局面为第 $i$ 局比赛，第 $0$ 局只有编号为 $1$ 的选手。  

定义第 $i$ 局的高水平选手为编号 $x\in[1,2^{i-1}]$ 的选手，低水平选手 $x\in[2^{i-1}+1,2^i]$ 的选手，不难想到低水平选手会被淘汰。

### Part 2 一定不合法
对于编号为 $x$ 的选手，他可以活到 $\log x$ 局。类似线段树的编号方式，对于 $i(i>\log x)$ 局位于位置 $p$ 的选手，其 $i-1$ 轮位于的位置是 $\left\lceil \frac{p}{2}\right\rceil$ 。我们可以很容易得到每个已确定位置的选手在所有局面当中的位置，单次复杂度 $O(k)$ 。

如果某一局两个高水平选手或低水平选手争夺同一个位置，那么这种情况不合法，说明高水平选手提前淘汰或低水平选手滞后淘汰，反应到操作中，就是某一局两个选手位置重叠，或某一局没有确定选手，而上一局对应的两个位置都已确定。

具体判断如下，记 $a_{i,j}$ 表示 $i$ 局 $j$ 位置的选手编号，位置未确定为 $0$ 或 $-1$ ，若无解有以下二种之一，任意一局任意位置满足即可：
$$j\in[1,2^{i-1}],\left(2^{i-1}<a_{i,2j-1}\right)\land\left (2^{i-1} <a_{i,2j}\right)$$

$$j\in[1,2^{i-1}],\left(0<a_{i,2j-1}\le2^{i-1}\right)\land\left(0<a_{i,2j}\le2^{i-1}\right)$$

此时方案数为 $0$ 。

### Part 3 可能合法方案数
由于一层一层的特性，不妨使用动态规划。

第 $0$ 局状态已知，而 $k$ 局不一定，所以从第 $0$ 局开始。

记 $f_i$ 表示 $i$ 局合法方案数，容易得到 $f_0=1$。

考虑从 $i-1$ 到 $i$ 局的影响，增加了 $x=2^{i-1}$ 名选手，如果一开始没有选手确定位置，那么不难得到转移：

$$f_{i}=f_{i-1}\times2^x\times x!$$

解释一下含义：

$f_{i-1}$ 可以看做 $i$ 局高水平选手放置位置的方案数。

我们要给每一个高水平选手匹配一个低水平选手，从而让高水平选手胜出，所以一定是 $x$ 个位置放高水平选手，$x$ 个位置放低水平选手，而 $f_{i-1}$ 刚好就是上轮放 $x$ 名选手的方案数，低水平选手只需让他们任意排列即可，所以要乘 $x!$。

匹配的高水平选手和低水平选手可以互换上下，对结果不影响，总共 $x$ 对，每对两种方案，所以要乘 $2^x$ 。

考虑已经预定位置的情况：

$f_{i-1}$ 可以直接继承过来。

如果已经有 $lose_i$ 名低水平选手预定了位置，那么可以随便排列的低水平选手只有 $x-lose_i$ 名，所以是 $(x-lose_i)!$。

如果已经有 $p$ 对选手已确定方案，那么这 $p$ 对选手不可互换上下，所以是 $2^{x-p}$，$p$ 怎么求呢？容斥一下，记 $win_i$ 类似 $lose_i$，$i$ 局已经预定位置的高水平选手，以及 $losewin_i$ 表示已经确定位置的**一对选手**的数量，类似判断无解的第二种情况，则 $p=win_i+lose_i-losewin_i$。

最后不难得到答案：

$$f_{i}=f_{i-1}\times2^{x-win_i-lose_i+losewin_i}\times (x-lose_i)!$$

那这三个数组应该如何求？在判断无解时可以顺带求：

$$lose_i=\sum\limits_{j=1}^{2^{i}}\left[0<a_{i,2j}\le2^{i-1}\right]$$

$$win_i=\sum\limits_{j=1}^{2^{i}}\left[2^{i-1}<a_{i,2j}\right]$$

$$losewin_i=\sum\limits_{i=1}^{2^{i-1}}\left[(0<a_{i,2j-1})\land(0<a_{i,2j})\right]$$

这样这道题就做完了，时间复杂度 $O(2^k+V)$，$V$ 是预处理阶乘和幂次的值域。如果像我一样开 $a$ 数组的话，注意用 `vector`，否则会炸掉。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll f[21],n,k,x2[N],fac[N];
ll win[21],lose[21],losewin[21];
vector<ll>a[21];
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>k;
    x2[0]=fac[0]=1;
    a[0].resize(2);
    for(int i=1;i<=N-5;i++){
        x2[i]=x2[i-1]*2%mod;
        fac[i]=fac[i-1]*i%mod;
        if(i<=19)a[i].resize(x2[i]+1);
    }
    for(int i=1;i<=x2[k];i++){
        cin>>a[k][i];
        if(a[k][i]==-1)continue;
        ll p=i;
        for(int j=k;j>=1&&a[k][i]<=x2[j];j--,p=(p+1)/2){
            if(a[k][i]>x2[j-1])lose[j]++;
            else {
                win[j]++;
                if(a[j-1][(p+1)/2]){
                    cout<<"0\n"<<endl;
                    return 0;
                }
                a[j-1][(p+1)/2]=a[k][i];
            }
        }
    }
    for(int i=k;i>=1;i--){
        for(int j=1;j<=x2[i];j+=2){
            if((j&1)&&a[i][j]>0&&a[i][j+1]>0&&a[i-1][(j+1)/2]<=0){
                cout<<0<<endl;
                return 0;
            }
            if(a[i][j]>0&&a[i][j+1]>0)losewin[i]++;
        }
        cout<<endl;
    }
    f[0]=1;
    for(int i=1;i<=k;i++)f[i]=f[i-1]*fac[(x2[i-1]-lose[i])]%mod*x2[(x2[i-1]-lose[i]-win[i]+losewin[i])]%mod;
    cout<<f[k]<<endl;
    return 0;
}
```

---

## 作者：王熙文 (赞：1)

## 思路

题目的本质要求是，每一个数都是在一个类似线段树结构的某个区间下的最小值。比如 $1,3,4,2$，对应的图是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/1u1gr9pj.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

考虑从大到小填。因为每一个数应当是对应层的某个区间的最小值，所以在从大到小填的过程中，如果确定了一个数的区间，则位置也确定了（剩下的位置一定被比它更大的位置填了）。还可以发现，除了第一层，任意一层的第 $2i-1$ 个和第 $2i$ 个区间的最小值不可以都是这一层的数，因为如果都是这一层的数，则上一层也会有这一层的数。

接下来对于每两个对应的区间（$2i-1$ 和 $2i$ 对应），如果这两个区间都没有 确定的上面层或当前层的数填，那么这一层的数便可以填到两个区间的任意一个中，方案数乘 $2$。确定区间后，没有确定的当前层的数可以随便排列，因此方案数乘阶乘。

对于无解，存在于以下情况：当前层的数与上面层的数都填到了某个区间；两个对应的区间都被填了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int jc[1000010];
int k,n; int a[1000010];
int wz[1000010];
int vvis[1000010];
signed main()
{
	jc[0]=1; for(int i=1; i<=1e6+5; ++i) jc[i]=jc[i-1]*i%mod;
	cin>>k; n=(1<<k);
	for(int i=1; i<=n; ++i)
	{
		cin>>a[i];
		if(a[i]!=-1) wz[a[i]]=i;
	}
	int l=1,r,ans=1;
	for(int i=0; i<=k; ++i,l=r+1)
	{
		r=l+(i==0?1:(1<<i-1))-1;
		if(i==0) continue;
		memset(vvis,0,((1<<i)+5)*8);
		for(int j=1; j<=l-1; ++j)
		{
			if(wz[j]!=0) vvis[(wz[j]-1)/(1<<k-i)+1]=1;
		}
		int ccnt=r-l+1;
		bool flag=1;
		for(int j=l; j<=r; ++j)
		{
			if(wz[j]!=0)
			{
				--ccnt;
				if(vvis[(wz[j]-1)/(1<<k-i)+1]!=0) { flag=0; break; }
				vvis[(wz[j]-1)/(1<<k-i)+1]=2;
			}
		}
		if(flag==0) { ans=0; break; }
		for(int j=1; j<=(1<<i); j+=2)
		{
			if(vvis[j]==2 && vvis[j+1]==2) ans=0;
			else if(vvis[j]==0 && vvis[j+1]==0) ans=ans*2%mod;
		}
		ans=ans*jc[ccnt]%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

# 题解
- $ 2^k $ 支球队，按照一定的顺序排列（决定谁与谁比赛）。
- 希望每次淘汰的都是最菜的 $ 2^{k-i} $ 支队伍。

# 思路
先看数据范围 $k\ (0 \le k \le 19)$，也就是 $2^{19}$，约等于 $5 \times 10^6$，相当于 $\sqrt{n} \times n$ 过不了，那么我们就直接找出每轮互相打比赛的两个数，判断他们是不是 $-1$，能不能自己安排就可以了。

### 几种情况如下。

```cpp
if(v[q]!=-1&&v[p]!=-1){
  if((v[q]<=t)==(v[p]<=t)){
		return 0;
	}
}
if(v[q]==-1&&v[p]==-1){
	cnt++;
}
if(v[p]!=-1&&v[p]<=t){
	xx.push_back(v[p]);	
}else if(v[q]!=-1&&v[q]<=t){
	xx.push_back(v[q]);
}else{
	xx.push_back(-1);
}
```
### 记得 ``memset``。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k; 
const int N=(1<<19)+10;
const int MOD=998244353;
int f[N],dp[N],a[N];
int xxall(vector<int> v){
	if(v.size()==1){
		return 1;
	}
	int n=v.size(),t=n/2;
	int cnt=0,dd=n/2;
	vector<int> xx;
//	xx.clear();
	for(int i=0;i<=n-1;i++){
		dd-=(v[i]>t);
	}
	for(int i=0;i<=n/2-1;i++){
		int p=2*i;
		int q=2*i+1;
		if(v[q]!=-1&&v[p]!=-1){
			if((v[q]<=t)==(v[p]<=t)){
				return 0;
			}
		}
		if(v[q]==-1&&v[p]==-1){
			cnt++;
		}
		if(v[p]!=-1&&v[p]<=t){
			xx.push_back(v[p]);	
		}else if(v[q]!=-1&&v[q]<=t){
			xx.push_back(v[q]);
		}else{
			xx.push_back(-1);
		}
	}
	return f[cnt]*dp[dd]%MOD*xxall(xx)%MOD;
}
signed main(){
	memset(f,0,sizeof(f));
	memset(dp,0,sizeof(dp));
	memset(a,0,sizeof(a));
	vector<int> ab;
	cin>>k;
	f[0]=dp[0]=1;
	for(int i=1;i<=1<<k;i++){
		f[i]=f[i-1]*2%MOD;
		dp[i]=dp[i-1]*i%MOD;
	}
	for(int i=1;i<=1<<k;i++){
		cin>>a[i];
		ab.push_back(a[i]);
	}
	cout<<xxall(ab)<<endl;
return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

 对于一个序列，从 $1\sim 2^k$ 排序。每次按顺序两两比较，删除较大的那个。求有多少方案满足每一次删除的数字都是当前轮中最大的那些数字。

---

我们模拟一下。

第一轮。我们肯定要把最大的 $2^{k-1}$ 个数字每两格仅填一个。我们把每两格称为一块。如果一块内有 $1$ 个 $-1$，那么只有一种填法（我们称之为情况一），否则有两种填法（我们称之为情况二）。

第二轮。每 $4$ 格仅填一个，此时一块变成了 $4$ 格。

……

那么这个性质有什么特别的吗？

我们发现，每次处理了一个 $k$ 后，问题的规模就相当于折半了。并且在块长改变后，每一块内还是只有两种情况（即最多只有两个格子未确定）！这一点可以仔细思考一下，是重点。

首先我们知道 $2^{19}$ 小于 $10^6$，那么我们是可以暴力枚举每一个队伍的。那么我们考虑从大到小依次考虑每 $2^k,k=n,n-1,\dots,1$ 个数，并用乘法原理计算答案。

每次扫描整个序列，以 $2^{K-k}$（$K$ 是题目给定的）为块长划分序列，如果块中包含当前的 $2^{k-1}$ 个数中的数字就跳过。否则可以证明填在哪个空位对答案没有影响，我们只需要统计出对于每个 $k$，有多少个块是情况一，多少是情况二，多少已经确定即可。对于那些已经确定的块，也同时要用于判断无解。

实现中我们可以不扫描块，而是扫描当前对于 $k$ 需要分配的那 $2^{k-1}$ 个队伍，并用 `vis[i]` 标记块 $i$ 是否有队伍分配。记得跳过那些已经内定了的队伍。

时间复杂度为$O(2^k\times k)$（可能不准确）。

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;
int ans=1,m;
int f;
int tot;
int n,d,a[N],vis[N],vis2[N],mul[N],fac[N],mo;


void init(){
	
	fac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%MOD;
	mul[0]=1;
	for(int i=1;i<=m;i++)mul[i]=mul[i-1]*2%MOD;


}
signed main(){
    n=rd;
    m=1<<n;
    for(int i=1;i<=m;i++)a[i]=-1;
    for(int i=1;i<=m;i++){
    	int t=rd;
    	if(t>0)a[t]=i;//记录每一个已经内定位置的队伍的位置
	}
	
	init();
	
	for(int i=1;i<=n;i++){
		int cnt=0,tot=0;
		for(int j=(1<<(i-1))+1;j<=(1<<i);j++){//枚举队伍并分配位置
			int t=(a[j]-1)>>(n-i+1);
			if(a[j]==-1)continue;
			if(vis[t]==i){
				cout<<0<<endl;
				return 0;
			}
			vis[t]=i;
			cnt++;
		}
		for(int j=1;j<=(1<<(i-1));j++){
			int t=(a[j]-1)>>(n-i+1);
			if(a[j]==-1)continue;
			if(vis2[t]==i){
//				cerr<<i<<endl;
				cout<<0<<endl;
				return 0;
			}
			vis2[t]=vis[t]=i;
			
		}
		
		for(int j=0;j<=(1<<(i-1))-1;j++){
			if(vis[j]==i)tot++;
		}
		//cnt统计出块内只有一个位置可填的队伍数，tot统计出有两个位置可填的。
		//分别用排列数和2的次幂计算，用乘法原理来组合
		ans=(ans*fac[(1<<(i-1))-cnt]%MOD*mul[(1<<(i-1))-tot]%MOD)%MOD;
	}
	cout<<ans<<endl;
//	cerr<<"OK";
}
```




---

## 作者：stntn (赞：0)

## 题意

有 $2^n$ 个人参加淘汰赛，每场位置相邻的两个人比，编号小者获胜，现在固定若干位置上的人，求在其余位置放人使得以下条件满足的方案数：

- 编号位于 $[2^i,2^{i+1}-1](i \in [0,n-1])$ 的人排名为 $i+1$。

## 分析

把比赛过程看作一棵满二叉树，记根为第 $0$ 层，我们按层次从小到大来安排位置。

先考虑没有固定任何人的情况。

现在考虑安排第 $i$ 层，此时第 $i-1$ 层已经安排好，那么会在该层新增 $2^{i-1}$ 个人，每个人须位于不同的比赛中，那么答案应该乘上 $2^{i-1}!\times 2^{2^{i-1}}$，不难理解前者为这些人排位置，后者安排在同一场比赛中的先后位置。

现在有人固定了，无非就是减去这些固定的位置的贡献，我们记 $cnt$ 为在新增的人中已经固定了的人数，$fix$ 为该层所有比赛中已经固定了先后顺序的数量，那么答案应该改为乘上 $(2^{i-1}-cnt)! \times 2^{2^{i-1}-fix}$。

这两者都很好维护，比如直接枚举所有人，当有固定的两人不满足条件即无解。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 1000010
#define M 1000000
#define LL long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define mod 998244353
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,m,a[N];LL ans=1,fac[N],_2[N];
int vis[N],vis2[N],suc;
signed main()
{
	memset(a,-1,sizeof(a));
	fac[0]=_2[0]=1;
	rep(i,1,M) fac[i]=fac[i-1]*i%mod,_2[i]=_2[i-1]*2%mod;
	read(n);m=1<<n;suc=1;
	rep(i,1,m){int x;read(x);if(x>0) a[x]=i;}
	rep(i,1,n)
	{
		int cnt=0,fix=0;
		rep(j,(1<<(i-1))+1,(1<<i)) if(~a[j])
		{
			if(vis[(a[j]-1)>>(n-i+1)]==i) return printf("0\n"),0;
			vis[(a[j]-1)>>(n-i+1)]=i;cnt++;
		}
		rep(j,1,(1<<(i-1))) if(~a[j])
		{
			if(vis2[(a[j]-1)>>(n-i+1)]==i) return printf("0\n"),0;
			vis[(a[j]-1)>>(n-i+1)]=vis2[(a[j]-1)>>(n-i+1)]=i;
		}
		rep(j,0,(1<<(i-1))-1) if(vis[j]==i) fix++;
		(ans*=fac[(1<<(i-1))-cnt]*_2[(1<<(i-1))-fix]%mod)%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Annihilation_y (赞：0)

## 思路
因为每一次淘汰的队伍的排列方式，都不会影响下一轮的比赛，所以我们可以将每一轮淘汰的选手的情况进行枚举，最后用乘法原理得出答案。

可以通过类似线段树建树的方法来实现。每一个节点分别有这几个值 $val$，$l$，$r$，$Level$。分别代表实力值，左右儿子编号，轮数。

对于每一轮的情况，可以设置 $cnt1$，$cnt2$。分别代表被淘汰的 $-1$ 的个数，以及两个都是 $-1$ 的情况数。每一层的结果就是 $cnt1! \times 2^{cnt2}$。将每一层的结果乘起来就是最终结果。

对于两个相邻的队伍，也就是同一个父亲节点的两个子节点，可以通过以下这几种方式得到它们的父亲节点的值:

- 都是 $-1$，那么父亲节点的 $val$ 也应当是 $-1$，需要注意，这种情况下，两个节点可以交换，所以需要让 $cnt2 \gets cnt2 + 1$。
- 两个都是确定的值，判断是否满足情况，如果不满足直接输出 $0$，否则父亲节点为较小值。
- 一个是确定的值，另一个是 $-1$，则判断这个确定的值是否会被淘汰。如果这个确定的值不会被淘汰，那么父亲节点的 $val$ 为这个值，并且让 $cnt1 \gets cnt1 + 1$。否则，父亲节点的 $val$ 为 $-1$。

需要注意，阶乘以及二的次方数都需要预处理。
## 代码
~~~c++
#include <bits/stdc++.h>
using namespace std;
const long long Mod=998244353;
#define int long long
struct node{
	int l,r,val;
	int Level;
}tr[1200005];
int a[600005];
long long ycl[600005],ycl_pow2[600005];
struct edge{
	int cnt1,cnt2;
}LV[105];
int tot=0;
void Pushup(int u){
	int L=tr[tr[u].l].val,R=tr[tr[u].r].val;
	if(L==-1&&R==-1){
		tr[u].val=-1;
		return ;
	}
	if(L==-1){
		if(R>tr[u].Level) tr[u].val=-1;
		else tr[u].val=R;
		return ;
	}
	if(R==-1){
		if(L>tr[u].Level) tr[u].val=-1;
		else tr[u].val=L;
		return ;
	}
	if((L>tr[u].Level&&R>tr[u].Level)||(L<=tr[u].Level&&R<=tr[u].Level)){
		printf("0\n");
		exit(0);
		return ;
	}
	else{
		tr[u].val=min(L,R);
		return ;
	}
}
void build(int &u,int l,int r,int Layer){
	if(!u) u=++tot;
	tr[u].Level=1<<(Layer-1);
	if(l==r){
		tr[u].val=a[l];
//		if(tr[u].val==-1) LV[layer].cnt1++;
		return ;
	}
	int mid=(l+r)>>1;
	build(tr[u].l,l,mid,Layer+1);
	build(tr[u].r,mid+1,r,Layer+1);
	Pushup(u);
	if(tr[tr[u].l].val==-1&&tr[tr[u].r].val==-1) LV[Layer+1].cnt2++,LV[Layer+1].cnt1++;
	else if((tr[u].val!=tr[tr[u].l].val&&tr[tr[u].l].val==-1)||(tr[tr[u].r].val==-1&&tr[u].val!=tr[tr[u].r].val)) LV[Layer+1].cnt1++;
	return ;
}
signed main(){
	int k,cnt=0;scanf("%lld",&k);
	int n=(1<<k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ycl[0]=ycl_pow2[0]=1;
	for(long long i=1;i<=600000;i++){
		ycl[i]=ycl[i-1]*i%Mod;
		ycl_pow2[i]=ycl_pow2[i-1]*2%Mod;
	}
	build(cnt,1,n,1);
	long long ans=1;
	for(int i=1;i<=k+1;i++) {
		ans=ans*ycl[LV[i].cnt1]%Mod*(ycl_pow2[LV[i].cnt2])%Mod;
	}
	printf("%lld\n",ans);
	return 0;
}

~~~
## 后记
感谢 qiuzijin2026 大佬为我改错。膜拜。

---

