# Discarding Game

## 题目描述

Eulampius has created a game with the following rules:

- there are two players in the game: a human and a computer;
- the game lasts for no more than $ n $ rounds. Initially both players have $ 0 $ points. In the $ j $ -th round the human gains $ a_j $ points, and the computer gains $ b_j $ points. The points are gained simultaneously;
- the game ends when one of the players gets $ k $ or more points. This player loses the game. If both players get $ k $ or more points simultaneously, both lose;
- if both players have less than $ k $ points after $ n $ rounds, the game ends in a tie;
- after each round the human can push the "Reset" button. If the human had $ x $ points, and the computer had $ y $ points before the button is pushed (of course, $ x < k $ and $ y < k $ ), then after the button is pushed the human will have $ x' = max(0, \, x - y) $ points, and the computer will have $ y' = max(0, \, y - x) $ points. E. g. the push of "Reset" button transforms the state $ (x=3, \, y=5) $ into the state $ (x'=0, \, y'=2) $ , and the state $ (x=8, \, y=2) $ into the state $ (x'=6, \, y'=0) $ .

Eulampius asked his friend Polycarpus to test the game. Polycarpus has quickly revealed that amounts of points gained by the human and the computer in each of $ n $ rounds are generated before the game and stored in a file. In other words, the pushes of the "Reset" button do not influence the values $ a_j $ and $ b_j $ , so sequences $ a $ and $ b $ are fixed and known in advance.

Polycarpus wants to make a plan for the game. He would like to win the game pushing the "Reset" button as few times as possible. Your task is to determine this minimal number of pushes or determine that Polycarpus cannot win.

## 说明/提示

In the second test case, if the human pushes the "Reset" button after the second and the fourth rounds, the game goes as follows:

1. after the first round the human has $ 5 $ points, the computer — $ 4 $ points;
2. after the second round the human has $ 7 $ points, the computer — $ 10 $ points;
3. the human pushes the "Reset" button and now he has $ 0 $ points and the computer — $ 3 $ points;
4. after the third round the human has $ 8 $ points, the computer — $ 6 $ points;
5. after the fourth round the human has $ 10 $ points, the computer — $ 9 $ points;
6. the human pushes "Reset" button again, after it he has $ 1 $ point, the computer — $ 0 $ points;
7. after the fifth round the human has $ 5 $ points, the computer — $ 5 $ points;
8. after the sixth round the human has $ 11 $ points, the computer — $ 6 $ points;
9. after the seventh round the human has $ 12 $ points, the computer — $ 13 $ points;
10. after the eighth round the human has $ 14 $ points, the computer — $ 17 $ points;
11. the human wins, as the computer has $ k $ or more points and the human — strictly less than $ k $ points.

## 样例 #1

### 输入

```
3
4 17
1 3 5 7
3 5 7 9
11 17
5 2 8 2 4 6 1 2 7 2 5
4 6 3 3 5 1 7 4 2 5 3
6 17
6 1 2 7 2 5
1 7 4 2 5 3
```

### 输出

```
0

2
2 4
-1```

# 题解

## 作者：Refined_heart (赞：2)

### $\text{Solution:}$

首先观察一下性质。

#### Key Observation: 操作前后游戏双方的差不变。

原因很简单。两人减掉的值相同。

那么考虑如何利用这一点。不妨先求出一个最靠前的位置使其可以胜利，那么每次减掉的一定是两个前缀和的最小值，我们的目的就是在保证人不输的情况下找到一个最靠前的位置使得机器人输（不考虑 $k$ 的限制下）

那这样就可以直接拿指针扫了。我们只需要减掉最低限度的值来保证人不死，因此一旦有一个位置机器人出局，那么这个位置一定是**操作的末尾**。

那么，我们可以 $O(n)$ 获得这个末尾。接下来考虑构造方案。

我们发现，之前的做法唯一没有考虑的就是操作的过程中是否人已经出局，而其中需要添进去的操作，我们可以直接模拟一遍加数的过程。每次到达出局临界，就在此时进行一次操作即可。因为我们的目的仅仅是想要在到达操作末尾前使得人不出局而已，而这个操作次数有显然的单调性，一边扫一边操作就是对的。

那么回过头来思考，我们为什么需要求出那个操作末尾呢？直接扫不对吗？

考虑我们扫的过程使用的策略：尽量晚地进行 `reset` 。这个策略放在长远来看，**容易使得机器人不输**。因此我们需要知道这个策略的结束位置，也就是从哪个位置开始我们可以一击制胜。那么前一段的指针就是为了获得这个位置，由于差值不变，我们只需要找到一个最靠前的位置，使得人不死而机器人出局，那么这个位置的操作前缀末尾就是我们的构造方案末尾。

总复杂度就是 $O(n).$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double db;
#define int long long
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
#define poly vector<int>
#define Bt(a) bitset<a>
#define bc __builtin_popcount
#define pc putchar
#define ci const int&
const int mod = 998244353;
const db eps = 1e-10;
inline int Max(ci x, ci y) {return x > y ? x : y;}
inline int Min(ci x, ci y) {return x < y ? x : y;}
inline db Max(db x, db y) {return x - y > eps ? x : y;}
inline db Min(db x, db y) {return x - y < eps ? x : y;}
inline int Add(ci x, ci y, ci M = mod) {return (x + y) % M;}
inline int Mul(ci x, ci y, ci M = mod) {return 1ll * x * y % M;}
inline int Dec(ci x, ci y, ci M = mod) {return (x - y + M) % M;}
typedef pair<int, int> pii;
inline int Abs(int x) {return x < 0 ? -x : x;}
//char buf[1<<21],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char Obuf[105000],*O=Obuf;//Siz shoule be the size of Out File
int pst[30],ptop;
inline void Fprint(){fwrite(Obuf,1,O-Obuf,stdout);}
inline void Fwrite(int x){
  if(x==0){*O++='0';if(O-Obuf>100000)Fprint(),O=Obuf;return;}
  if(x<0)*O++='-',x=-x;ptop=0;
  while(x)pst[++ptop]=x%10,x/=10;
  while(ptop)*O++=pst[ptop--]+'0';
  if(O-Obuf>100000)Fprint(),O=Obuf;
}
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') w = -1;ch = getchar();}
    while (isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
    return s * w;
}
inline void write(int x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
	pc(x % 10 + '0');
}
inline int qpow(int x, int y) {
    int res = 1;
    while (y) {if (y & 1)res = Mul(res, x);x = Mul(x, x);y >>= 1;}
    return res;
}
inline void cadd(int &x, int y) {x += y;}
inline void cmul(int &x, int y) {x *= y;}
inline void cmax(int &x, int y) {x = Max(x, y);}
inline void cmin(int &x, int y) {x = Min(x, y);}
const int N = 4e5 + 10;
const int inf = 1LL << 60;
namespace Refined_heart{
	int T,n,k,a[N],b[N];
	int sa[N],sb[N],s[N];
	int f[N];
	inline int calc(int x,int y,int op=0){
		if(op==1)return sb[y]-s[x];
		return sa[y]-s[x];
	}
	
	void work(){
		for(int i=1;i<=n+10;++i)sa[i]=sb[i]=s[i]=0;
		poly Ans;
		sa[0]=sb[0]=s[0]=0;
		for(int i=1;i<=n;++i){
			sa[i]=sa[i-1]+a[i];
			sb[i]=sb[i-1]+b[i];
			s[i]=Min(sa[i],sb[i]);
		}
		int pre=0,ans=-1;
		for(int i=1;i<=n;++i){
			while(pre<=n&&sa[i]-k>=s[pre])++pre;
			if(sa[i]-k<s[pre]&&sb[i]-k>=s[pre]){
				ans=i;
				break;
			}
		}
		if(!pre||ans==-1){
			if(ans==-1)puts("-1");
			else puts("0\n");
			return;
		}
		int A=0,B=0;
		int pos=0;
		for(int i=1;i<pre;++i){
			A+=a[i];B+=b[i];
			pos=i;
			if(B>=k)break;
			if(A+a[i+1]>=k){
				Ans.pb(i);
				int vl=Min(A,B);
				A-=vl;
				B-=vl;
				if(A+a[i+1]>=k){
					puts("-1");
					return;
				}
			}
		}
		Ans.pb(pre);
		if(Ans.empty())puts("0\n");
		else{
			cout<<(int)Ans.size()<<"\n";
			for(auto v:Ans)cout<<v<<' ';
			cout<<"\n";
		}
		
	}
	void solve(){
		T=read();
		while(T--){
			n=read();k=read();
			for(int i=1;i<=n+10;++i)a[i]=b[i]=0;
			for(int i=1;i<=n;++i)a[i]=read();
			for(int i=1;i<=n;++i)b[i]=read();
			work();
		}
	}
}
signed main(){
  	freopen("in.txt","r",stdin);
	Refined_heart::solve();
	return 0;
}

```


参考题解：https://www.cnblogs.com/Jiaaaaaaaqi/p/11971732.html

---

## 作者：Loser_Syx (赞：0)

好玩。

我们记 $s_i$ 为 $a$ 的前缀和，$t_i$ 为 $b$ 的前缀和。

首先 $0$ 次操作就赢是好判的，只要是存在一个 $i$ 满足 $s_i < k$ 且 $t_i \geq k$ 即可。

那么我们知道剩下情况若合法肯定是有至少一次操作。考虑如何快速算出剩下合法的情况。

首先我们观察到一个性质，对于每个 $i$，如果无论前面删除几次，因为两边删去的是同一个数，所以两边差值永远是 $s_i - t_i$。

既然差值不变，又操作至少一次，我们不如枚举一个 $i$，并且钦定我们会在第 $i-1$ 次结束后进行一次的删除操作，不难发现剩下的答案里只要有答案一定会存在这种情况，所以是可行的。

然后考虑 $s_j,t_j$ 具有单调性，可以尝试以 $(s_j,t_j)$ 为二元组二分出一个 $s_j - s_{i-1} + x < k$ 且 $t_j - t_{i-1} + y \geq k$ 的，其中 $x$ 为人类剩下的分。$y$ 为人机剩下来的分。

不难发现当 $s_i - s_{i-1}+x > k$ 时或 $i=n$ 时还没有答案时无解。注意一定要在大循环内判。不然会导致比如说我前面有答案后面不合法但是我已经赢了的情况。

对于 $i$ 之前的大小，贪心处理。不必要的就不删。

[code](https://codeforces.com/contest/1250/submission/289768814)。

---

## 作者：robinyqc (赞：0)

一个很重要的注意：不管怎么操作，到第 $i$ 局，双方的差为一个定值，因为 reset 操作并不会使差发生变化。并且，这个差容易求出——两者前缀和的差。

容易得到一个贪心的做法：如果下一步人类的得分小于 $k$，就不 reset；否则必须苟着，按下 reset。这样做直到获胜。这样一定是操作数最少的，并且不会输（除非任意情况必输）：因为若某个 reset 提前做了，那后面的 reset 位置单调不升，可能还得加入一个新的 reset。并且，没有必要再两个 reset 之间加入一个新的。

但是输入样例就会发现这样做有错：有可能人本来能赢的，但是最后平局了。

我们得修正这个做法。发现有另一种做法，这样做能胜必胜，但是操作数不一定最少：枚举从哪一步开始，不再 reset。判断这样做是否能获胜，并且人类可以从开头坚持到这个点（也就是**不输**）。

于是我们把两个做法合起来：枚举最后一个 reset 的点，判断能否获胜，前面贪心地坚持到这个点。这样对于所有最后一个 reset 在这个点的情况，操作数是最小的。再把每个点的答案取最值。这样做便是正确的了，但是 $O(n^2)$。

注意到，随着最后一个 reset 点左移，使人类不败的最右的端点单调不升。因此可以双指针，预处理出每个点是否可以获胜。然后从左往右贪心即可。复杂度 $O(n)$。

当然，你会注意到只有最左边的可以获胜的点有用。因此也可以只保存最左边的能够使人获胜的点（可以参考代码）。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

using i64 = long long;

vector<int> ans;

void solve()
{
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n), b(n);
    for (int& i: a) cin >> i;
    for (int& i: b) cin >> i;
    
    vector<i64> h(n + 1), c(n + 1);
    
    // 预处理出，若在 i 按下 reset，人/机的值分别是多少。
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] + a[i - 1];
        c[i] = c[i - 1] + b[i - 1];
        i64 v = min(h[i], c[i]);
        h[i] -= v;
        c[i] -= v;
    }
    
    int p = n, mn = n;
    i64 hn = 0, cn = 0;
    
    // 双指针判断能够获胜的点
    for (int i = n - 1; i >= 0; i--) {
        hn += a[i], cn += b[i];
        while (h[i] + hn >= k) {
            --p;
            hn -= a[p];
            cn -= b[p];
        }
        if (c[i] + cn >= k) mn = i;
    }
    
    if (mn == n) {
        cout << "-1\n";
        return ;
    }
    else if (mn == 0) {
        cout << 0 << "\n\n";
        return ;
    }
    
    hn = 0, cn = 0;
    ans.clear();
    
    // 贪心地坚持到最左边的能够获胜的点
    for (int i = 0; i < mn; i++) {
        if (hn + a[i] >= k) {
            i64 v = min(hn, cn);
            hn -= v;
            cn -= v;
            ans.push_back(i);
            if (hn + a[i] >= k) {
                cout << "-1\n";
                return ;
            }
        }
        hn += a[i];
        cn += b[i];
    }
    
    ans.push_back(mn);
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << ' ';
    cout << '\n';
}

signed main() 
{
    ios::sync_with_stdio(false); 
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

