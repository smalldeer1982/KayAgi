# Gaining Rating

## 题目描述

Monocarp is playing chess on one popular website. He has $ n $ opponents he can play with. The $ i $ -th opponent has rating equal to $ a_i $ . Monocarp's initial rating is $ x $ . Monocarp wants to raise his rating to the value $ y $ ( $ y > x $ ).

When Monocarp is playing against one of the opponents, he will win if his current rating is bigger or equal to the opponent's rating. If Monocarp wins, his rating is increased by $ 1 $ , otherwise it is decreased by $ 1 $ . The rating of his opponent does not change.

Monocarp wants to gain rating $ y $ playing as few games as possible. But he can't just grind it, playing against weak opponents. The website has a rule that you should play against all opponents as evenly as possible. Speaking formally, if Monocarp wants to play against an opponent $ i $ , there should be no other opponent $ j $ such that Monocarp has played more games against $ i $ than against $ j $ .

Calculate the minimum possible number of games Monocarp needs to gain rating $ y $ or say it's impossible. Note that ratings of Monocarp's opponents don't change, while Monocarp's rating does change.

## 说明/提示

In the first test case, Monocarp can use the following strategy:

1. Monocarp plays against the $ 2 $ -nd opponent to increase rating ( $ 2 \to 3 $ );
2. Monocarp plays against the $ 1 $ -st opponent to increase rating ( $ 3 \to 4 $ );
3. Monocarp plays against the $ 4 $ -th opponent to increase rating ( $ 4 \to 5 $ );
4. Monocarp plays against the $ 5 $ -th opponent to increase rating ( $ 5 \to 6 $ );
5. Now Monocarp have to play with remaining three opponents. So, he will lose $ 3 $ times and get rating $ 3 $ ( $ 6 \to 5 \to 4 \to 3 $ );
6. After that, Monocarp will repeat steps 1-5 again. After $ 14 $ games, he has played twice with each opponent and get final rating $ 4 $ .
7. Monocarp plays against the $ 1 $ -st opponent to increase rating ( $ 4 \to 5 $ );
8. Monocarp plays against the $ 2 $ -nd opponent to increase rating ( $ 5 \to 6 $ );
9. Monocarp plays against the $ 4 $ -th opponent to increase rating ( $ 6 \to 7 $ );
10. Monocarp plays against the $ 5 $ -th opponent to increase rating ( $ 7 \to 8 $ );
11. Monocarp plays against the $ 7 $ -th opponent to increase rating ( $ 8 \to 9 $ );
12. Monocarp plays against the $ 3 $ -rd opponent to increase rating ( $ 9 \to 10 $ );

 In total, Monocarp, played twice against the $ 6 $ -th opponent and three times against other opponents and got rating $ 10 $ in $ 14 + 6 = 20 $ games.In the second test case, it can be proven that whichever games Monocarp plays, he can't get his rating higher than $ 4 $ .

## 样例 #1

### 输入

```
3
7 2 10
3 1 9 2 5 20 8
7 1 10
3 1 9 2 5 20 8
5 10 12
100 1 200 11 300```

### 输出

```
20
-1
2```

# 题解

## 作者：sprads (赞：4)

翻最短解时发现的一个很优雅的做法。

设玩了若干次游戏后，现在的 rating 为 $x$，目标 rating 为 $y$。

首先想到一些基础的操作：

- 将大于 $y$ 的 $a_i$ 赋值为 $y$。

- 将 $a$ 从小到大排序。

接着容易想到枚举 $x$ 在 $a$ 中的范围，即枚举 $i$，当 $a_{i-1}\le x<a_i$ 时，计算 rating 从 $x$ 到 $a_i
$ 所需的最小游戏次数。

但是这样写有不少细节，例如需要求出当 rating 到达 $a_i$ 时与谁游戏，还需要特别考虑 rating 增长形如 $+1 +1 +1\dots -1-1-1$ 的情况，此时不能用与所有人玩一轮游戏后的总 rating 变化量计算……

进一步思考以减少 corner case：

将限制放松，这次计算 rating $x$ **大于等于** $a_i$ 所需的最少游戏次数。同时强制最后一次与 $i-1$ 游戏，结束后再与 $i$ 游戏，就能保证每一次计算游戏次数时是一个从 $i$ 到 $i-1$ 的形如 $-1,-1,-1\dots+1+1+1$ 的循环。

这时就很好计算了：设走完循环后 rating 的变化量为 $s$，所需轮数为 $\lceil\dfrac{a_i-x}{s}\rceil$（若 $s \le 0$ 则无解）。

最后还需注意：

- $x > y$ （求得的 rating 大于等于 $a_i$），所需的游戏次数应减少 $x-y$，因为 $x-y<s\le$ 循环中 $+1$ 的次数，所以只能减少 $x-y$ 次。
- $x<y$（$a_n<y$），这时能赢所有人，任意进行 $y-x$ 次游戏即可，最少游戏次数应加上 $y-x$。

综上：只需要给计算的游戏次数加上 $y-x$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll s,t,a[N];//s 是题解中的 x,t 是题解中的 y
int T,n;
void solve(){
	ll ans = 0,cur = -n;//cur 是题解中的 s
	for(int i = 1;i <= n;i++){
		if(s < a[i]){
			if(cur <= 0)
				return puts("-1"),void();
			ll nd = (a[i] - s + cur - 1) / cur;
			ans += nd * n,s += nd * cur; 
		}
		if(a[i] == t)break;
		ans++,s++,cur += 2;//cur + 1 - (-1) 因此 + 2
	}
	printf("%lld\n",ans + t - s);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%lld",&n,&s,&t);
		for(int i = 1;i <= n;i++)
			scanf("%lld",&a[i]),a[i] = min(a[i],t);
		sort(a + 1,a + 1 + n);
		solve();
	}
	return 0;
}
```


---

## 作者：LiveZoom (赞：4)

## Description

[link](https://www.luogu.com.cn/problem/CF1772G)

## Solution

因为不能有比当前人比赛次数少的，所以一定是每次轮流把 $n$ 个人全打一场。

易知从小到大打最优，因为这样可以先发育大一点再打大的人。

那么此时 $a_1\leq a_2\leq\dots\leq a_n$，设 $b_i=a_i-(i-1)$。由于 $a_i\leq a_{i+1}$，所以 $b_{i+1}-b_i\geq -1$。

如果 $b_i\leq b_{i+1}$，那么 $i$ 和 $i+1$ 的胜负状态是一样的。如果 $b_i-1=b_{i+1}$，此时 $a_i=a_{i+1}$，就要分两种情况讨论了：

1. 赢了 $i$，则 $x\geq a_i$，那么 $x+1\geq a_{i+1}$，所以胜负状态一样。

2. 输了 $i$，则 $x<a_i$，那么 $x-1<a_{i+1}$，所以胜负状态也一样。

所以每一轮肯定是赢了 $1\sim i$，输了 $i+1\sim n$。

这样就可以枚举 $i$，设初始值为 $x(b_i\leq x<b_{i+1})$。则每一轮 $x$ 会增加 $2i-n$。

那么 $x$ 从 $b_i$ 过渡到 $b_{i+1}$ 的过程中要进行 $\bigg\lceil\dfrac{b_{i+1}-x}{2i-n}\bigg\rceil$ 轮比赛，即 $\bigg\lceil\dfrac{b_{i+1}-x}{2i-n}\bigg\rceil\times n$ 场比赛。

注意，如果 $x$ 在过渡的过程中达到了 $y$ 要及时输出，这个过程中就进行了 $k=\bigg\lceil\dfrac{y-x-i}{2i-n}\bigg\rceil$ 轮完整的比赛，以及 $y-x-(2i-n)\times k$ 场不完整的比赛。

最后如果 $i=n$，就输出当前答案加 $y-x$。

时间复杂度：$O(n\log n)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 2e5 + 5;

int n, x, y;
int a[kMaxN], b[kMaxN];

int cei(int x, int y) {
  // assert(y > 0);
  if (x < 0) return 0;
  if (x % y == 0) return x / y;
  else return x / y + 1;
}

void solve(int cs) {
  cin >> n >> x >> y;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  // if (cs == 4437) cout << n << '=' << x << '=' << y << '=' << a[1] << '=' << a[2] << '=' << a[3] << '=' << a[4] << '\n';
  sort(a + 1, a + 1 + n);
  b[0] = -1e9;
  for (int i = 1; i <= n; ++i) {
    b[i] = a[i] - i + 1;
    b[i] = max(b[i - 1], b[i]);
  }
  // sort(b + 1, b + 1 + n);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (x + ans >= a[i]) {
      ++ans;
      cerr << "黑哥\n";
      if (x + ans == y) {
        cout << i << '\n';
        return;
      }
    } else {
      --ans;
    }
  }
  if (ans <= 0) {
    cout << "-1\n";
    return;
  }
  // ans = 0;
  x += ans;
  ans = n;
  cerr << x << '\n';
  b[n + 1] = LLONG_MAX;
  for (int i = 1; i <= n - 1; ++i) {
    if (b[i] >= b[i + 1] || x < b[i] || x >= b[i + 1]) continue;
    // cerr << b[i] << ' ' << b[i + 1] << '\n';
    if (2 * i == n) {
      if (x + i >= y) {
        cout << ans + y - x << '\n';
        return;
      } else {
        cout << "-1\n";
      }
      return;
    }
    int tmp = cei(b[i + 1] - x, 2 * i - n) * (2 * i - n);
    // cerr << tmp << '\n';
    if (x + tmp + (n - i) >= y) {
      int k = cei(y - x - i, 2 * i - n);
      // cerr << "***" << k << '\n';
      cout << ans + n * k + (y - x - (2 * i - n) * k) << '\n';
      return;
    }
    // cerr << x << ' ' << b[i + 1] << '\n';
    ans += cei(b[i + 1] - x, 2 * i - n) * n;
    x += tmp;
    // cerr << b[i] << ' ' << x << ' ' << ans << '\n';
  }
  // cerr << "黑哥\n";
  // assert(x < y);
  cout << ans + y - x << '\n';
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) solve(i);
  return 0;
}
```

---

## 作者：MSqwq (赞：2)

你会发现这题思路是一眼的，但是细节挺多，如果你写不明白，我建议你先把整个过程模拟一遍想好了再写。  
题意：   
给你 $n$ 个人，每个人有一个能力值 $a_i$ 你的能力值最开始从 $x$ 开始，目标是到 $y$。如果你打赢了一个能力值小于等于你的人，那么你的能力值 $+1$，反之 $-1$。问你在尽可能平均的情况下，也就是如果你要打 $i$ 那么不应该存在一个 $j$ 使得打 $i$ 的场次比打 $j$ 的场次多。求最少场次，或者判断无解。  

------------
题解：  
那么显然的有一个性质，就是如果你排了序，每个数的全局贡献一定是连续不上升的，因为你的能力值在变大，可以战胜越来越多的人。  
那么考虑临界情况，也就是考虑以当前能力值，打不过那个人的位置，也是贡献开始从正变负的那个位置，假设这个位置为 $now$，那么就有 $x+now \ge a_{now}$，而且是第一个满足和这个关系的位置。那么我们就要算前面 $now$ 个人的在若干轮中的总贡献，和现在 $x$ 的值是多少，这是我们需要更新的。特殊的，因为你的 $x$ 存的是上一个矛盾点的状态，可能到这一轮的时候 $x+now \le a_{now}$ 就满足了，所以计算的时候按上一个完整的一轮为界限，就是算贡献算到当前这轮开始的 $1$ 号位结束。  
那么问题就变成从上一个 $x$ 开始经过了多少个完整轮次，每轮次都是从 $1$ 到 $n$。那么我们思考一下，每一轮都是前 $now$ 为 $+1$,后面 $n-now$ 为 $-1$。那么每一轮的贡献就是 $2\times now - n$。如果这轮贡献都小于等于 $0$ 了，那么 $x$ 就不可能变大了，也就永远不可能达到 $y$ 所以无解。那么总贡献其实就是 $a_{now}-now-x$，为什么呢，因为我们是尽可能平均的进行，而且要减去当前的前 $now$ 个，最后算轮次就是 $\lceil \frac{a_{now}-now-x}{2\times now-n} \rceil$，然后更新 $x$。   
特殊讨论一下，如果最开始 $a_i > y$ 就不讨论了。你可以顺便在最后添加一个 $y$，如果当前的 $x$ 都超过 $y$ 就停止了。  
可能说的比较绕和复杂，如果上面都没看懂就看代码吧：  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e5+10;
int m;
ll a[N],b[N];
void solve()
{
	m=0;
	ll n=read(),x=read(),y=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)if(a[i]<y)b[++m]=a[i];
	b[++m]=y;sort(b+1,b+1+m);

	ll ans=0,now=1;
	while(now<=m)
	{
		while(now<=m&&x+(now-1)>=b[now])now++;
		if(now>m)
		{
			printf("%lld\n",ans+(b[m]-x));
			return;
		}
		ll np=(now-1)*2-n;
		if(np<=0)
		{
			printf("-1\n");
			return;
		}
		ll diff=b[now]-(now-1)-x;
		ll cnt=(diff/np)+(diff%np!=0);
		ans+=n*cnt,x+=np*cnt;
	}
	printf("%lld\n",ans);
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

小 M 初始有 $x$ 点能力，现在他想通过和别人下棋达到 $y$ 点能力。具体的，有 $n$ 个人，每个人有能力 $a_i$。小 M 和第 $i$ 个人下一局棋，如果小 M 当前能力 $x$ 大于等于 $a_i$，则 $x$ 增加 $1$，反之减少 $1$。

特别地，小 M 必须保证在每一刻，与任意两个人的下棋局数之差的绝对值不能超过 $1$。问至少要下多少局棋才能使小 M 的能力达到 $y$。

## 题目分析

这题思路还是很顺畅的。

我们肯定优先选择 $a_i$ 小的人下棋，所以先按 $a_i$ 升序排序。然后，对于每一个初始值，下完一轮后对能力的贡献是确定的。不妨设 $f_i$ 表示想要一路赢到第 $i$ 个人，初始值最小是多少。显然有初始化 $f_i=a_i$。其次，如果 $f_{i-1}+i-1\ge a_i$，则直接用 $f_i$ 对 $f_{i-1}$ 取最小值。否则，$a_i-(i-1)$ 肯定能够转移到 $f_i$。

显然 $f_i$ 单调递增，所以值域被 $f_i$ 分成了 $O(n)$ 段，对于每一段，扫一轮增加的贡献是固定的，二分并直接计算即可，细节没什么可讲的，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
using namespace std;
int T=read(),n,x,y,a[N],s[N],tp,f[N];
inline int find(int x){
	int l=1,r=tp,ans=1;
	while(l<=r)if(x>=f[s[mid]])ans=mid,l=mid+1;
	else r=mid-1;
	return ans;
}
signed main(){
	while(T--){
		n=read(),x=read(),y=read();
		rep(i,1,n)a[i]=read();
		sort(a+1,a+n+1);
		int nw=x;
		bool fl=0;
		rep(i,1,n){
			if(nw>=a[i])nw++;
			else nw--;
			if(nw==y){
				cout <<i<<endl;
				fl=1;
				break;
			}
		}
		if(fl)continue;
		if(nw<=x){
			cout <<"-1\n";
			continue;
		}
		f[0]=llf;
		rep(i,1,n){
			f[i]=a[i];
			if(f[i-1]+i-1>=a[i])f[i]=min(f[i],f[i-1]);
			else f[i]=min(f[i],a[i]-(i-1));	
		}
		f[n+1]=llf;
		tp=0;
		rep(i,2,n+1)if(f[i]^f[i-1])s[++tp]=i-1;
		int ans=0;
		while(1){
			int np=find(x);
			if(np==tp){
				ans+=y-x;
				break;
			}
			else {
				int nxk=f[s[np+1]];
				int w=2*s[np]-n;
				int t=(nxk-x+w-1)/w;
				if(x+(t-1)*w+s[np]>=y){
					int pur=y-s[np];
					t=(pur-x+w-1)/w;
					ans+=t*n+(y-(x+t*w));
					break;
				}else {
					ans+=t*n,x+=t*w;
				}
			}
		}
		cout <<ans<<endl;
	}
	return 0;
}
```


---

