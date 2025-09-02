# [AGC010D] Decrementing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc010/tasks/agc010_d

黒板に $ N $ 個の整数が書かれています。$ i $ 番目の整数は $ A_i $ であり、これらの最大公約数は $ 1 $ です。

高橋君と青木君はこの数を使ってゲームをします。ゲームでは高橋君から始めて交互に以下の操作を繰り返します。

- 黒板の中から $ 2 $ 以上の数を $ 1 $ つ選び、その数から $ 1 $ を引く。
- その後、黒板に書かれた数の最大公約数を $ g $ として、すべての数を $ g $ で割る。

黒板に書かれた数が全て $ 1 $ となっていて、操作が行えない人の負けです。 二人が最適に行動したとき、どちらが勝つか求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ A_i\ ≦\ 10^9 $
- $ A_1 $ から $ A_N $ の最大公約数は $ 1 $

### Sample Explanation 1

以下のようにすれば先手の高橋君が勝てます。 - 高橋君が $ 7 $ から $ 1 $ を引く。このとき、操作後は $ (1,2,2) $ となる。 - 青木君が $ 2 $ から $ 1 $ を引く。このとき、操作後は $ (1,1,2) $ となる。 - 高橋君が $ 2 $ から $ 1 $ を引く。このとき、操作後は $ (1,1,1) $ となる。

## 样例 #1

### 输入

```
3
3 6 7```

### 输出

```
First```

## 样例 #2

### 输入

```
4
1 2 4 8```

### 输出

```
First```

## 样例 #3

### 输入

```
5
7 8 8 8 8```

### 输出

```
Second```

# 题解

## 作者：juju527 (赞：18)

### $\texttt{Soultion}$
考虑什么样的局面是必胜的

容易发现是 $k,k,k,k+1,...,k,k$ 的类型

对唯一的 $k+1$ 项减1之后对面就输了

然而，再思考一步，$k$ 一定等于 1

因为 $k>1$ 时，前一步对手的状态所有数都大于1，只要避免来到该状态即可，随意减一个为 $k$ 的位置即可

故必胜的状态应该是 $1,1,2,...,1,1$

首先，当序列出现1时，游戏已经结束，奇偶性就能判断

具体判断是有奇个偶元素则先手胜，反之后手胜

**其他情况只需考虑偶数元素奇偶性的变化即可**

下面提及的奇数指大于1的奇数

若目前有奇个偶数，显然我们是优的，只要保持这奇个偶数，最后就能取得胜利

我们只要选一个偶数减一，所有数的奇偶性不发生改变

对面怎么选都改变不了偶数元素个数的奇偶性，先手必胜

若目前有偶个偶数，我们不优，**改变奇偶性的唯一办法就是令2|gcd**

若有多个奇数，我们这一轮让一个变成偶数，下一轮对面就能把它成奇数，无法除2，先手必败

唯一的特例是只有一个奇数时，我们这一轮就能至少除2，**这也是我们唯一的翻盘机会**

考虑做完上面提及的操作，将决策扔给对手

至此，我们所有情况都讨论完了，小结下

1. 若元素中出现1，判断奇偶性即可
2. 若有奇个偶元素，先手必胜
3. 若有偶个偶元素且奇元素数量大于1，后手必胜
4. 若有偶个偶元素且奇元素数量等于1，操作唯一的奇元素后将先手权交给后手，后手继续判断

由于继续的只有 Case4，在 Case4 中元素至少全部除2

求gcd暴力求会多带一个log

复杂度 $O(nlog^2W)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn];
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<48||ch>57){if(ch==45)y=-1;ch=getchar();}
    while(ch>=48&&ch<=57)x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
int gcd(int x,int y){
	while(y){
		x%=y;
		swap(x,y);
	}
	return x;
}
int main(){
//    freopen("AT2305.in","r",stdin);
//    freopen("AT2305.out","w",stdout);
    int n;
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int op=0;
	while(1){
		int c=0,d=0,p;
        bool flag=0;
		for(int i=1;i<=n;i++){
            if(a[i]>1&&(a[i]&1)){c++;p=i;}
            else if(a[i]%2==0)d++;
            if(a[i]==1)flag=1;
        }
        if(flag){
            if(d&1){
                if(!op)puts("First");
			    else puts("Second");
            }
            else{
                if(op)puts("First");
			    else puts("Second");
            }
            return 0;
        }
        if(d&1){
			if(!op)puts("First");
			else puts("Second");
			return 0;
		}
		if((d%2==0)&&c>1){
			if(!op)puts("Second");
			else puts("First");
			return 0;
		}
		if((d%2==0)&&c==1){
			a[p]--;
			int g=0;
			for(int i=1;i<=n;i++)g=gcd(g,a[i]);
			for(int i=1;i<=n;i++)a[i]/=g;
			op^=1;
		}
	}
    return 0;
}


```
> 本题最重要的就是想到考虑偶元素数量的奇偶性，将原本难以下手的除以gcd变成了只要考虑奇偶性的简单问题

---

## 作者：xcyle (赞：12)

首先，如果$a_i$中有$1$那么双方能做的操作只有$-1$，此时胜负已经由$\sum a_i-1$的奇偶性决定

我们再考虑除以最大公因数这个操作，双方会根据上式的奇偶性变化来决策自己的操作，因此我们的关注点应该在奇偶性上。奇公因数是不会改变其局势的

那么我们考虑，如果初态为奇，那么这时候看上去是先手必胜的，因此先手一定会努力维持住这个局面，只要最大公因数一直为1，先手就能将优势持续到最后

我们会发现，先手一步可以将偶数变成奇数，因此新的局面一定不会出现偶公因数。之后的策略也是相同的。因此，如果初态为奇，先手必胜。

然而初态为偶呢？先手必定会努力改变奇偶性，因为一旦在第一步没有改过来，后手将会像刚才那样掌控全局。然而先手一次只能操作一个数，如果操作后有偶公因数，原来的局面只会有一个奇数，并且先手会操作它

在此博弈思想的指导下，我们会发现一个局面除非可以一步判断最终的胜负，先手的操作必然是唯一的

我们在分析一下时间复杂度，每次每个数除以$2$，最多只会操作$log$次，总时间$O(nlog^2a)$

```cpp
#include <iostream>
#include <cstdio>
#define maxn 100005
using namespace std;
int n, a[maxn];
inline int gcd(int x, int y)
{
	if(x < y) swap(x, y);
	return y == 0 ? x : gcd(y, x % y);
}
int work()
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i] - 1;
	}
	if(sum & 1) return 1;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if(a[i] & 1) cnt++;
	}
	if(cnt > 1) return 0;
	for (int i = 1; i <= n; i++)
	{
		if(a[i] & 1)
		{
			if(a[i] == 1) return 0;
			a[i]--;
		}
	}
	int d = a[1];
	for (int i = 2; i <= n; i++)
	{
		d = gcd(d, a[i]); 
	}
	for (int i = 1; i <= n; i++)
	{
		a[i] /= d;
	}
	return (work() ^ 1);
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]); 
	}
	if(work()) printf("First");
	else printf("Second");
	return 0;
}
```

---

## 作者：sky_landscape (赞：5)

首先考虑最简单的情况，如果有一个数是 $1$，那么第二步没有作用，胜负是固定的，先判掉。

然后发现题目给了一个很奇怪的条件：所有数的最大公约数为 $1$，也就是至少有一个奇数，这提示我们从奇偶数下手。

发现第二步中的最大公约数的奇数因子是毫无意义的，因为无论是奇数还是偶数除以一个奇数，奇偶性都不变，没有改变第一步操作次数的奇偶性。

这给了先手一种必胜的思路，如果只进行第一步，先手必胜，先手又能保证两人每一次第二步中的最大公约数为奇数就必胜。

先手只需要每一次随便选一个偶数减 $1$，由于初始至少有一个奇数，所以后手操作的时候至少有两个奇数，最大公约数一定为奇数，先手的操作最大公约数就更显然是奇数了。

这种情况的初始条件是只进行第一步先手必胜，也就是偶数个数为奇数。

如果只进行第一步先手必败呢？这时候先手肯定不能留给后手奇数，否则后手采用前面的方法必胜。所以先手只有一种选择，第一步删奇数。

如果初始奇数的个数大于 $1$，那么先手删不完所有的奇数，后手必胜。

到现在，我们有三种判定了：

- 如果有 $1$ 直接判定。
- 如果有奇数个偶数先手必胜。
- 如果有偶数个偶数并且有大于一个奇数后手必胜。

如果恰好有偶数个偶数而且只有一个奇数，先手会删那个奇数，直接模拟这一次操作将奇数减 $1$，这时所有的数都为偶数，最小公因数最小为 $2$，最多进行 $\log$ 次就会变成上面三种情况的一种。

单次模拟时间复杂度为 $O(n\log a)$，总时间复杂度为 $O(n\log^{2}a)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n;
int a[N];
int ji,ou,now=1,sum=0;
bool flag=false;

void change(){
    for(int i=1;i<=n;i++){
        if(a[i]&1) a[i]--;
    }
    int gcd=a[1];
    for(int i=2;i<=n;i++) gcd=__gcd(gcd,a[i]);
    for(int i=1;i<=n;i++) a[i]/=gcd;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]&1) ji++;
        else ou++;
        if(a[i]==1) flag=true;
        sum+=(a[i]-1);
    }
    if(flag){
        if(sum&1) cout<<"First";
        else cout<<"Second";
        return 0;
    }
    if(ou&1){
        cout<<"First";
        return 0;
    }
    else if(!(ou&1) && ji>1){
        cout<<"Second";
        return 0;
    }
    while(1){
        now=3-now;
        change();
        ji=ou=0;
        sum=0;
        for(int i=1;i<=n;i++){
            if(a[i]&1) ji++;
            else ou++;
            if(a[i]==1) flag=true;
            sum+=(a[i]-1);
        }
        if(flag){
            if(!(sum&1)) now=3-now;
            break;
        }
        if(ou&1){
            break;
        }
        else if(!(ou&1) && ji>1){
            now=3-now;
            break;
        }
    }
    if(now==1) cout<<"First";
    else cout<<"Second";
    return 0;
}
```

---

## 作者：Ebola (赞：5)

这题的难点，是你要发现若干个偶数的gcd居然可能大于2！这个超级难的！

好吧言归正传。。。

**结论一：如果一开始有一个1，其它都是偶数，那么若是奇数个偶数，先手必胜，否则后手必胜（显然）**

**结论二：如果一开始有奇数个偶数，先手必胜。**

说明：如果先手能保证每人每次只能取一个，那么他就赢了。要想保证每人每次只能取一个也很简单，先手只需任选一个偶数减1，再算上初始局面必然包含的一个奇数（否则初始gcd不为1），这样就至少有两个奇数了。此时若序列长度大于2，那么序列的gcd必然为1，并且再让任意一个数减1，序列的gcd仍然为1，后手此时显然非常鸡肋。

特殊情况是序列长度为2，那先手减了1之后，可能两数相等，那正好直接赢了；要是不相等，并且减1之后出现了倍数关系，那没什么影响，显然一个是另一个的奇数倍，约去gcd后就是一个1加上一个奇数，此时显然先手就赢了。

**结论三：如果一开始有大于一个奇数，以及偶数个偶数，后手必胜**

说明：因为有大于一个奇数，所以选任意一个数减一，gcd必然还为1，此时结论二中的情况就轮到了后手的手上，先手就只能咕咕咕了

**其他情况下（一开始有偶数个偶数以及一个奇数），让那个奇数减1，然后序列整体除以gcd（对，是gcd，不是2，艹），再重复进行上述三种判断。因为每次至少除2，所以递归层数是log级别的**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int a[N],n,cnt[2];

bool gao()
{
    for(int i=1;i<=n;i++)
        if(a[i]&1) a[i]--;
    cnt[0]=cnt[1]=0;
    int gcd=a[1];
    for(int i=2;i<=n;i++)
        gcd=__gcd(a[i],gcd);
    for(int i=1;i<=n;i++)
        cnt[(a[i]/=gcd)&1]++;
    if(cnt[0]&1) return 1;
    else if(cnt[1]>1) return 0;
    else
    {
        for(int i=1;i<=n;i++)
            if(a[i]==1) return cnt[0]&1?1:0;
        return gao()^1;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        cnt[a[i]&1]++;
    }
    if(cnt[0]&1) puts("First");
    else if(cnt[1]>1) puts("Second");
    else
    {
        for(int i=1;i<=n;i++)
            if(a[i]==1){puts(cnt[0]&1?"First":"Second");return 0;}
        puts(gao()^1?"First":"Second");
    }
    return 0;
}
```



---

## 作者：lalaouye (赞：2)

有迹可循的思维题，切完之后感觉很爽！

考虑慢慢想一些性质：

1. 可以注意到只会除以 $\log$ 次 $\gcd$。
2. 只要存在了一个数字 $1$，那么之后胜负只与奇偶性有关。对于一名玩家尽可能要在达到存在一个 $1$ 之前调整好奇偶性。
3.  发现大多数操作也改变不了奇偶性，只有所有数字都为偶数之后除一次才有奇偶性变化。
4. 想除一次 $\gcd$ 是很困难的，而阻止对方除一次 $\gcd$ 是简单的。

那么现在如果当前玩家急需调整一次奇偶性，只有可能在最开始只存在一个奇数的时候做除法。因为对方肯定不希望你调整。不难发现如果先手处于奇偶性的优势则先手必胜，因为先手可以保证后手永远无法调整奇偶性。而先手如要调整则会不断调整，直到当前先手处于奇偶性优势或者存在不止两个奇数为止，而顶多只会进行 $\log$ 次除法，那么我们就用优美的做法完成了一道优美的题。

代码：

````
#include <bits/stdc++.h>
#define int long long
#define ls (p << 1)
#define rs (ls | 1)
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define x first
#define y second
#define inf 1000000000
#define linf 1000000000000000000
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5, P = 998244353;
inline int rd () {
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, a[N];
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd ();
  int s = 0;
  rep (i, 1, n) {
    a[i] = rd ();
    s ^= a[i] & 1;
  }
  if (s ^ (n & 1)) {
    puts ("First");
  } else {
    bool win = 0, now = 0;
    while (1) {
      if (win ^ now) {
        break;
      }
      rep (i, 1, n) if (a[i] > 1 && (a[i] & 1)) {
        -- a[i]; break;
      }
      int g = 0, sum = 0;
      rep (i, 1, n) g = __gcd (g, a[i]), sum += a[i];
      if (g == 1) break; sum /= g;
      rep (i, 1, n) a[i] /= g;
      if ((sum & 1) == (n & 1)) win ^= 1; now ^= 1;
    }
    puts (win ? "First" : "Second");
  }
}
````

---

## 作者：do_while_true (赞：2)

[**My cnblogs**](https://www.cnblogs.com/do-while-true/p/15758565.html)

序列中至少有一个奇数，否则就会被 $\gcd$ 除掉了。

如果序列出现了 $1$，说明无论怎样操作之后 $\gcd$ 都只能为 $1$ 了，那么判断偶数个数的奇偶性，若有奇数个偶数那么先手必胜，判掉这个，现在所有的数都是可以被钦点的了。

猜个结论，如果有奇数个偶数，那么先手必胜。

注意到如果钦点一个数 $-1$ 之后，剩余既有奇数又有偶数，则 $\gcd$ 为奇数，除掉 $\gcd$ 之后各个数的奇偶性不变。

那么先手只需要钦点使得给后手 $>1$ 个奇数，$>0$ 个偶数，这样后手无论怎么钦点，轮到先手的时候依然是奇数个偶数。

那么特殊情况就是 $n=2$ 的时候，这个稍微讨论一下就差不多得了发现依然满足结论。

然后看如果先手有偶数个偶数，考虑奇数的个数，如果奇数的个数 $>1$，那先手不管怎么钦点，轮给后手的都是"奇数个偶数"的必胜状态，所以此时先手必败。

如果奇数的个数 $=1$，先手如果钦点偶数的话，轮给后手的就是"奇数个偶数"的必胜状态，所以先手只能钦点奇数，这种情况递归下去继续判即可。

每产生一次递归，所有数至少变为原来的一半，所以总复杂度就是 $\mathcal{O}(N\log^2A)$．

就嗯塞语法糖

```cpp
#include<iostream>
#include<cstdio>
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 100010;
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int n, a[N];
#define Win do{puts(p?"Second":"First");return ;}while(0)
#define Lose do{puts(p?"First":"Second");return ;}while(0)
void check(int p) {
	int ct = 0, g = 0, fl = 0;
	for(int i = 1; i <= n; ++i)
		ct += !(a[i]&1),
		g = a[i]&1 ? gcd(g, a[i]-1) : gcd(g, a[i]),
		fl |= a[i]==1;
	if(ct&1) Win;
	if(fl || n-ct>1) Lose;
	for(int i = 1; i <= n; ++i) a[i] = a[i]&1 ? (a[i]-1)/g : a[i]/g;
	check(p^1);
}
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]);
	check(0);
	return 0;
}
```

---

## 作者：ShanQing (赞：1)

*2795，但是小清新。

首先显然的观察是如果序列中存在 $1$ 那就意味着 $\gcd$ 被锁死在 $1$，也就是第二个操作是冗余的，那么此时如果偶数个数是奇数就是先手赢，否则后手赢。

排除了 $1$ 的情况就讨论当前局面**偶数是奇数个还是偶数个**。

当然，在这之前还需要知道的一个前置的观察是，如果操作 $2$ 除的 $\gcd$ 是一个奇数，那么哪方必胜不变，因为偶数个数不变。否则偶数个数可能变化，即某方必胜局面将被重新洗牌。

**如果偶数个数是奇数个**，由于原序列 $\gcd$ 为 $1$，即原本存在至少 $1$ 个奇数。那么此时先手可以考虑再将一个偶数减去 $1$ 变成奇数，那么奇数就不少于 $2$ 个。

此时**先手必胜策略显然**，接下来只要后手操作了哪个数那先手也操作那个数即可，这样保持偶数个数不变，就可以避免 $\gcd$ 变为偶数导致先手必胜局面的洗牌。

---

**如果偶数个数是偶数个**，那还要继续分类讨论。如果**奇数个数大于等于** $2$ **那后手必胜**，策略同偶数个数为奇数时先手的策略。

否则先手如果选了某个偶数变为奇数必然导致奇数个数大于等于 $2$，然后先手就似了。所以先手必须**选择仅剩的那 $1$ 个奇数**，将 $\gcd$ 变为偶数。整体除以 $\gcd$ 后就又是一个新的局面，继续判断直到出现某方必胜。

---

时间复杂度 $O(n\log V)$。

## code


```cpp
#include <bits/stdc++.h>
//taskkill /f /im 未命名1.exe
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define epb emplace_back
#define pb push_back
#define mk make_pair
#define ins insert
#define fi first
#define se second
#define ll long long
//#define ull unsigned long long
using namespace std;
const int N=1e5+5,INF=2e9,mod=1e9+7;
int t,n,m;
int a[N];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	int res=0,op=0;
	while(1) {
		int cnt=0,ps=0,has=0;
		for(int i=1;i<=n;++i) {
			if(a[i]&1) {
				++cnt,ps=i;
				if(a[i]==1) has=1;
			}
		}
		if(has) {
			int op2=(n-cnt)&1;
			if(op^op2) puts("First");
			else puts("Second");
			break;
		}
		else if((n-cnt)&1) {
			if(!op) puts("First");
			else puts("Second");
			break;
		}
		else if(cnt>1) {
			if(op) puts("First");
			else puts("Second");
			break;
		}
		
		if(ps) --a[ps],op^=1;
		int d=a[1];
		for(int i=2;i<=n;++i) {
			d=__gcd(d,a[i]);
		}
		for(int i=1;i<=n;++i) {
			a[i]/=d;
		}
	}
	return 0;
}

```

---

## 作者：int_R (赞：1)

什么时候才能自己做出来一道博弈啊？

当不考虑除以 $\gcd$ 时，答案只与奇偶性有关。当存在至少一个 $1$ 时，$\gcd$ 等于 $1$ 也相当于不用除。

于是当在这种情况下先手必败时，一定是想要改变奇偶性，唯一的方法就是除以一个偶数才有可能改变奇偶性。

当一组数的 $\gcd=1$ 时，一定有至少一个奇数。

当有 $1$ 时可以直接判断，$n=1$ 时也可以直接判断。

$n=2$ 时一定是先手拿到一奇一偶，先手不想改变奇偶性，于是后手一定拿到两奇，又还给先手一奇一偶。

下面讨论 $n\geq 3$ 且所有数都 $>1$ 的情况。

当先手不想改变奇偶性，一定时刻都能保证操作后有至少两个奇数。

当先手想改变奇偶性时，一定得立刻改变，否则就变成上一个局面。

于是总结一下：

- 当所有数的和的奇偶性与 $n$ 的奇偶性不同时，先手必胜。
- 否则，若 $n=1$，则先手必败。
- 否则，若有数为 $1$，先手必败。
- 否则，有多个奇数时，先手必败。
- 否则，将唯一的奇数减一，递归到子问题求解。

只会递归 $\log$ 次，所以就做完了。

---

## 作者：pioneer2000 (赞：1)

### 思路：

- 不难发现，当序列中出现 $1$ 的时候，序列的最大公约数始终为 $1$ ，所以其第二步操作就等于没有做，此时我们只要判断一下数列的奇偶性就行了（用 $ans$ 统计除了 $1$ 以外的 $a_i-1$ 的总和，若为奇数则当前回合方胜利，反之则对方胜利）。
- 若当前有奇数个偶元素，显然我们只要保持住奇数个偶数的数量，在最后就一定能取得胜利，而在当前我们只需要选择任意一个偶数减一，另一方就无法改变偶数元素的奇偶性，所以此时当前方必胜。
- 若当前有偶数个偶元素，显然我们处于劣势，如果此时有多个奇数，同上面的情况一样，我们无法改变偶数元素的奇偶性，此时操作方必败。
- 上一种情况，若要改变偶数元素的奇偶性，唯一的办法就是在第二步操作中令所有数的最大公约数等于 $2$。所以，**当且仅当**这一轮只有一个奇数时，我们就可以改变序列中的一个偶数，使得每个数都除以二，**这是唯一有机会取胜的办法**（上面一种情况已证明）做完后，我们将选择权交给对手。

以上就是本道题会出现的所有情况，前三种情况可以特判去处理，最后一种情况可以递归到下一轮枚举，用一个 $op$ 记录当前回合是哪一方执行即可。由于每次都只能除以二，所以最多会递归 $ \log n$ 次，而由于还要计算序列的最大公约数，时间复杂度为 $O(n \log^2 a)$。

### code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[100005],op=0;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(1){
		ll sum=0,sum1=0,flag=0,ans=0,p=0;
		for(int i=1;i<=n;i++){
			if(a[i]%2==0) sum++;
			else if(a[i]==1) flag=1;
			else{
				p=i;
				sum1++;
			}
			ans+=a[i]-1;
		}
		//cout<<op<<" "<<sum<<" "<<sum1<<" "<<flag<<" "<<ans<<" "<<p<<endl;
		if(flag==1){
			if(ans%2==0){
				if(op) cout<<"First";
				else cout<<"Second";
				return 0;
			}else{
				if(op) cout<<"Second";
				else cout<<"First";
				return 0;
			}
		}else if(sum%2==1){
			if(!op) cout<<"First";
			else cout<<"Second";
			return 0;
		}else if(sum%2==0){
			if(sum1>1){
				if(!op) cout<<"Second";
				else cout<<"First";
				return 0;
			}else{
				a[p]--;
				ll gc=0;
				for(int i=1;i<=n;i++){
					gc=__gcd(gc,a[i]);
				}
				for(int i=1;i<=n;i++){
					a[i]/=gc;
				}
			}
		}
		op^=1;
	}
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
考虑一种极容易想的情况，如果此序列中有一个 $1$，那么此时除法就废了，那么就只能减 $1$ 了，所以只用维护奇偶性即可。

那么没有 $1$ 怎么办，还是考虑维护奇偶性。假设目前一共有奇数个偶数，并且我们是先手，那么此时一定是优的。但是对手有可能有翻盘机会，对手或许可以通过将唯一的奇数减 $1$ 来同时除以一个偶数来翻盘。但是别忘了我们是先手，每次选择一个偶数减去 $1$ 即可使奇数个数大于 $1$ 从而避免被翻盘，故以上的情况先手必胜。注意：全是偶数的情况不可能会出现。

反过来看，假如此时一共有偶数个偶数，那么此时不优，如果奇数个数还是大于 $1$ 的，那么对手就会用同样的方法来对付我们，故以上的情况后手必胜。

还有最后一种情况，那就是有可能翻盘的情况，此时暴力统计最大公约数，更新 $a$ 数组，将此状态递归交给对手之后判断即可。

最后分析一下时间复杂度，因为递归的情况必然要做除法，所以是 $\log w$ 的，再算上最大公约数的时间复杂度，最后是 $O(n \log w \log n)$。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int n;
int a[N];
int dfs(){
	int sum=0,cnt=0;
	bool f=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(a[i]==1) f=1;
		if(a[i]%2==0) cnt++;
	}
	if(f==1){
		if((sum-n)%2==1) return 1;
		else return 0;
	}
	if(cnt%2==1) return 1;
	if(cnt%2==0 and n-cnt>1) return 0;
	if(cnt%2==0 and n-cnt==1){

		int num;
		int b[N];
		if(a[1]%2==1) num=a[1]-1;
		else num=a[1];
		for(int i=2;i<=n;i++){
			if(a[i]%2==1) num=__gcd(num,a[i]-1);
			else num=__gcd(num,a[i]);
		}
		for(int i=1;i<=n;i++){
			b[i]=a[i];
			a[i]/=num;
		}
		bool op=dfs();
		for(int i=1;i<=n;i++){
			a[i]=b[i];
		}
		return op^1;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(dfs()) cout<<"First";
	else cout<<"Second";
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc010_d)

**题目大意**

> 给定 $a_1\sim a_n$，保证 $\gcd(a_1,\dots,a_n)=1$。
>
> 两人轮流操作，每次给一个大于一的 $a_i$ 减一，然后所有 $a_i$ 约去 $\gcd(a_1,\dots,a_n)$，无法操作者输，求谁必胜。
>
> 数据范围：$n\le 10^5$。

**思路分析**

如果 $a_i$ 中有 $1$，那么说明此后 $\gcd(a)=1$，答案只和 $\sum (a_i-1)$ 的奇偶性有关。

此时先手必胜当且仅当 $a$ 中有奇数个偶数。

然后考虑一般的情况，如果偶数个数仍然为奇数，那么修改一个偶数，此时奇数个数 $\ge 2$（初始至少存在一个偶数），后手无论如何操作一定有 $2\nmid \gcd(a)$，无法改变元素奇偶性。

因此只要 $a$ 中有奇数个偶数，先手必胜。

否则考虑刚才的结果，如果此时奇数个数 $\ge 2$，先手无法改变元素奇偶性，必败，否则必定操作这个元素，然后交换先后手变成一个值域折半的子问题，递归计算即可。

时间复杂度 $\mathcal O(n\log^2V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,a[MAXN];
void solve(string A,string B) {
	int s=0;
	for(int i=1;i<=n;++i) s^=(a[i]-1)&1;
	if(s) return cout<<A,void();
	int o=0;
	for(int i=1;i<=n;++i) {
		if(a[i]==1) return cout<<B,void();
		if(a[i]&1) {
			if(o) return cout<<B,void();
			o=i;
		}
	}
	--a[o];
	int g=a[1];
	for(int i=2;i<=n;++i) g=__gcd(a[i],g);
	for(int i=1;i<=n;++i) a[i]/=g;
	solve(B,A);
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	solve("First\n","Second\n");
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

如果一次操作后 $a_1=a_2=a_3=a_4=\cdots=a_n=1$，则这次操作过后必胜。

则此次操作前的状态是 $1$ 个 $p+1$ 和 $n-1$ 个 $p$，此时操作 $p+1$ 即可。

但对手肯定会尽量阻止这个状态，具体操作为操作一个 $p$。

所以当且仅当 $p=1$ 时无法操作，必胜状态必为 $n-1$ 个 $1$ 以及一个 $2$。

当序列出现 $1$ 时，$\gcd=1$，此时双方操作只能使一个数 $-1$，即如果 $\sum a_i-n$ 为奇则先手必胜，反之先手必败。

注意到如果序列中有奇数，则 $\gcd$ 为奇数，这次操作后每个数的奇偶性不发生改变。

如果目前有奇个偶数，则先手优，保持这奇个偶数到最后就能胜利。

考虑任意选择一个偶数 $-1$，此时对手选偶数则偶数数量 $-1$，选奇数则偶数数量 $+1$，无论怎样偶数个数都是奇数。

此时先手必胜。为何不会出现后文说的翻盘机会？因为此次操作完成后奇数数量必定 $>1$。

证明：

假设此次操作后奇数数量为 $1$。

注意到每次操作后序列的 $\gcd=1$。

此次操作会使奇数数量 $+1$，则操作前序列中没有奇数，$\gcd \mid 2$，矛盾。

如果目前有偶个偶数，则先手劣，考虑如何让偶数数量的奇偶性变化。

唯一办法是让序列中不存在奇数，此时偶数个数的奇偶性才有可能改变。

即如果只有一个奇数，操作这个奇数，否则先手必败。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e5+10;
sd string s[3]={"First","Second"};
int n,now,cnt,a[N];
int pd()
{
	int flag=0;
	F(i,1,n)
	{
		if(a[i]==2)
		{
			if(flag) return 0;
			flag=1;
		}
		if(a[i]>2) return 0;
	}
	return 1;
}
il void solve()
{
	n=read();
	F(i,1,n) a[i]=read();
	while(1)
	{
		// F(i,1,n) printk(a[i]);
		// puts("");
		cnt=0;
		F(i,1,n) if(a[i]==1) cnt++;
		if(cnt)
		{
			int sum=0;
			F(i,1,n) sum+=a[i];
			if((sum-n)&1) return sd cout<<s[now]<<"\n",void();
			return sd cout<<s[!now]<<"\n",void();
		}
		cnt=0;
		F(i,1,n) if((a[i]&1)==0) cnt++;
		if(cnt&1)//奇数个偶数
			return sd cout<<s[now]<<"\n",void();
		else
		{
			cnt=0;
			int c;
			F(i,1,n) if(a[i]&1) cnt++,c=i;
			if(cnt!=1) return sd cout<<s[!now]<<"\n",void();
			a[c]--;
		}
		int gc=a[1];
		F(i,2,n) gc=sd __gcd(gc,a[i]);
		F(i,1,n) a[i]/=gc;
		now^=1;
	}
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

[Decrementing](https://www.luogu.com.cn/problem/AT_agc010_d)

- 若序列中含有一，则答案可以通过判断 $\sum$ 的奇偶性来判断。
- 若序列中有奇数个偶数，则先手必胜。

最优策略是：选一个偶数，由于原序列中的最大公约数是 $1$，则必含有一个奇数，所以后手只能改变一个一个数的奇偶性，先手仍处于必胜态。

- 若序列中有偶数个偶数，则分情况讨论：
- 若有至少 $2$ 个奇数，则后手必胜，先手无法改变全局 $\gcd$。
- 否则先手操作唯一一个奇数，然后将该序列扔给后手操作。

由于操作次数不会超过 $\log W$ 次，算上 $\gcd$ 的复杂度为 $n\log^2W$，其中 $W$ 为值域。


[Submission](https://atcoder.jp/contests/agc010/submissions/49757560)

---

## 作者：Otomachi_Una_ (赞：0)

c. **[[AGC010D] Decrementing](https://atcoder.jp/contests/agc010/tasks/agc010_d)（6）**

妙题。

首先如果 $a_i$ 当中有 $1$，直接判断奇偶性就可以了。

如果给到先手的局面当中有奇数个偶数，那么先手可能会让奇数个偶数的局面留给自己。先手可以通过调整奇偶性使得每次的 $g$ 都是奇数，每个元素的奇偶性都不会改变。那么必败局面 $(1,1,\dots,1)$ 一定留给对手。

如果给先手的局面有 $\leq n-2$ 且偶数个偶数，那么 $g$ 必然是奇数，必胜局面必然留给后手。

剩下一种情况，当前恰好有 $1$ 个奇数。那么先手为了翻盘必然要取这个奇数，后面的局面就和前面相同了。只需要递归判断。

时间复杂度：$\mathcal O(n\log^2 V)$。

[submission](https://atcoder.jp/contests/agc010/submissions/43757111)

---

## 作者：pengyule (赞：0)

> 有一个数列 $(a_1,a_2,...,a_n)$，玩家每次依次执行下列操作：
> - 选一个 $>1$ 的数 $-1$；
> - 将所有数除以其 gcd；
> 
> 问先手有无必胜策略？

首先考虑，**当数列中存在 $1$ 时，有奇数个偶数先手必胜，有偶数个偶数后手必胜**。——所有玩家都只能做 $-1$ 操作。

其次考虑，当数列的 gcd 为奇数时，所有数除以一个奇数奇偶性均不变。

同时考虑，**当数列中偶数的个数为奇数时**，先手 $-1$，一定能让偶数个数偶数并存在一个奇数，那么 gcd 就是奇数，于是把一个偶数个数为偶数的数列给了对方，对方 $-1$，偶数个数又成奇数，从而先手可以保持偶数个数始终为奇数，一直到出现一个 $1$，**他就必胜了**。

再次考虑，**当数列中偶数个数为偶数时**，先手已经较为被动，希望扭转局面，扭转局面的意思是使偶数个数成为奇数，唯一的方法就是除以一个偶的 gcd，他可以这样做**当且仅当给他的数列里只有一个奇数**，便将它 $-1$，再除以偶的 gcd，**他就有可能赢**。注意是“有可能”，因为除以偶的 gcd 并不能保证让偶数个数奇偶性反转。反之，**如果奇数个数 $>1$，他就必败了**，因为无法扭转局面。

将上文粗体部分合并起来，就是这个题的实现方法。
由于只有最后一种分情况需要接下去考虑，而此时一定已经除以了一个 $\ge 2$ 的 gcd，所以迭代次数应不超过 $\log_210^9$; 时间复杂度 $O(n\log 10^9)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
bool dfs(){
	bool flag=0;
	for(int i=1;i<=n;i++)if(a[i]==1){flag=1;break;}
	int cnt=0;
	for(int i=1;i<=n;i++)cnt+=a[i]&1^1;
	if(flag)return (cnt&1);
	if(cnt&1)return 1;
	if(n-cnt>1)return 0;
	int g=0;
	for(int i=1;i<=n;i++){if(a[i]&1)a[i]--;g=gcd(g,a[i]);}
	for(int i=1;i<=n;i++)a[i]/=g;
	return (dfs()^1);
}
int main(){
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	puts(dfs()?"First":"Second");
}
```

---

## 作者：zhylj (赞：0)

注意到：

- 如果有 $1$：若 $2\not |\ \sum (a_i - 1)$，则先手必胜，否则后手必胜。

  在此情况下除的操作无法进行，很好分析。

  注意到此时的条件相当于：奇数个偶数（显然奇数 $-1$ 对奇偶性没有影响）则先手必胜。

- 如果有奇数个偶数，则先手必胜。（此情况由于每回合开始时所有数互质，所以必然至少包含一个奇数）

  注意到先手可以始终保持整个数列的最大公因数为奇数，而所有奇数模 $2$ 意义下的逆元都为 $1$，所以是不会影响奇偶性的。最后总能达到第一种情况中的状态。

- 如果有大于一个奇数，且有偶数个偶数，则后手必胜。

  先手无论怎么操作，都无法让所有数除以一个偶数，且都会导致场面上有奇数个偶数。这样后手就面临了一个先手必胜的局面。

- 否则，剩下的情况是：有偶数个偶数和一个奇数。显然先手要减去奇数，否则后手就必胜。这样的操作是固定的，所以我们可以直接模拟，由于除的最大公因数至少为 $2$，所以时间复杂度为 $\mathcal O(n\log n)$.

（写代码的时候注意最后一种情况先后手会变）

```cpp
const int kN = 1e5 + 5;

int a[kN], n;
int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }
void Div() {
	int g = a[1];
	for(int i = 2; i <= n; ++i) g = Gcd(g, a[i]);
	for(int i = 1; i <= n; ++i) a[i] /= g;
}

int main() {
	int cur = 0; rd(n);
	for(int i = 1; i <= n; ++i) rd(a[i]);
	while(true) {
		int cnt = 0, ecnt = 0, p; bool flag = false;
		for(int i = 1; i <= n; ++i) {
			if(a[i] % 2 == 0) ++cnt;
			else p = i, ++ecnt;
			if(a[i] == 1) flag = true;
		}
		if(flag) return printf((cnt % 2 == 1) ^ cur ? "First" : "Second"), 0;
		if(cnt % 2 == 1) return printf(cur ? "Second" : "First"), 0;
		if(ecnt > 1 && cnt % 2 == 0) return printf(cur ? "First" : "Second"), 0;
		--a[p]; Div(); cur ^= 1;
	}
	return 0;
}
```

---

## 作者：CHU2 (赞：0)

如果这个序列中如果存在1，把这个序列中（不为1的数-1）加起来，如果和为奇数先手胜，否则后手胜。

考虑先后手的一轮操作，在没有除法的情况下，可以保证奇/偶数个数的奇偶性不变，同样，在这个过程中，gcd为奇数，所以除法不影响奇/偶数个数的奇偶性。然后变到1就不能操作，偶数个数总体趋势还是减少的。当只剩一个偶数和一堆1时，根据上面的结论先手胜。所以有偶数个奇数时，先手必胜。

否则如果有偶数个偶数时，考虑游戏中任意一个局面，它的gcd为1，说明原序列中有$\geq 1$个奇数。也就是说，如果先手对偶数执行-1操作，gcd一直为奇数，除掉了以后奇偶数的个数不变，即变成了有奇数个偶数的情况，此时先手必败。那操作奇数呢？只剩下一个奇数时才能这么干，否则还是先手必败,理由同上。所以有偶数个偶数，且奇数个数$> 1$时，后手必胜，否则除掉gcd继续处理。

模拟一下就完了

```cpp
#include <bits/stdc++.h>
#define N 100005
#define ll long long
#define For(i,x,y) for(int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
#define Edge(x) for(int i=head[x];i;i=e[i].nxt)
#define mset(x,y) memset(x,y,sizeof(x))
#define strL strlen
#define p_b push_back
#define mcpy(x,y) memcpy(x,y,sizeof(x))
#define lson l,mid,(o<<1)
#define rson mid+1,r,((o<<1)|1)
#define Ls (t[o].ls)
#define Rs (t[o].rs)
#define mod
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
int cnt[2],a[N];
int gcd(int x,int y){
	if(x<y) swap(x,y);
	return x%y?gcd(y,x%y):y;
}
int main(){
	int n;bool tk=1;
	scanf("%d",&n);
	For(i,1,n) scanf("%d",&a[i]);
	while(1){
		cnt[1]=cnt[0]=0;
		ll sum=0;int _1=0,pos=0;
		For(i,1,n){
			if(a[i]==1) _1++;
			else{
				sum+=a[i]-1;
				if(a[i]%2) cnt[1]++,pos=i;
				else cnt[0]++;
			}
		}
		if(_1){
			if(sum%2==0) tk^=1;
			if(tk) puts("First");
			else puts("Second"); 
			return 0;
		} else{
			if(cnt[0]%2){
				if(tk) puts("First");
				else puts("Second");
				return 0;
			} else{
				if(cnt[1]>1){
					tk^=1;
					if(tk) puts("First");
					else puts("Second");
					return 0;
				} else{
					a[pos]--;int x=a[1];
					For(i,2,n) x=gcd(a[i],x);
					For(i,1,n) a[i]/=x;
					tk^=1;
				}
			}
		}
	}
}
```


---

