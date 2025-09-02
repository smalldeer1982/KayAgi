# Too Much Money

## 题目描述

Alfred wants to buy a toy moose that costs $ c $ dollars. The store doesn’t give change, so he must give the store exactly $ c $ dollars, no more and no less. He has $ n $ coins. To make $ c $ dollars from his coins, he follows the following algorithm: let $ S $ be the set of coins being used. $ S $ is initially empty. Alfred repeatedly adds to $ S $ the highest-valued coin he has such that the total value of the coins in $ S $ after adding the coin doesn’t exceed $ c $ . If there is no such coin, and the value of the coins in $ S $ is still less than $ c $ , he gives up and goes home. Note that Alfred never removes a coin from $ S $ after adding it.

As a programmer, you might be aware that Alfred’s algorithm can fail even when there is a set of coins with value exactly $ c $ . For example, if Alfred has one coin worth $3, one coin worth $4, and two coins worth $5, and the moose costs $12, then Alfred will add both of the $5 coins to $ S $ and then give up, since adding any other coin would cause the value of the coins in $ S $ to exceed $12. Of course, Alfred could instead combine one $3 coin, one $4 coin, and one $5 coin to reach the total.

Bob tried to convince Alfred that his algorithm was flawed, but Alfred didn’t believe him. Now Bob wants to give Alfred some coins (in addition to those that Alfred already has) such that Alfred’s algorithm fails. Bob can give Alfred any number of coins of any denomination (subject to the constraint that each coin must be worth a positive integer number of dollars). There can be multiple coins of a single denomination. He would like to minimize the total value of the coins he gives Alfred. Please find this minimum value. If there is no solution, print "Greed is good". You can assume that the answer, if it exists, is positive. In other words, Alfred's algorithm will work if Bob doesn't give him any coins.

## 说明/提示

In the first sample, Bob should give Alfred a single coin worth $5. This creates the situation described in the problem statement.

In the second sample, there is no set of coins that will cause Alfred's algorithm to fail.

## 样例 #1

### 输入

```
12
3
5
3
4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
50
8
1
2
4
8
16
37
37
37
```

### 输出

```
Greed is good
```

# 题解

## 作者：syk666 (赞：3)

首先有一个性质，**最优答案加且只用加一枚硬币** 。

证明：若需要加两枚硬币 $ a,b $ ，钦定$ a \ge b $  
 
共有三种情况：

$ 1. $ 若当前只用 $ a $ ，不用 $ b $ ，那么有没有 $ b $ 无所谓，最优情况不需要 $ b $ 。

$ 2. $ 若当前只用 $ b $ ，同理也不需要 $ a $ 。

$ 3. $ 若当前 $ a,b $ 均用，则到使用 $ a $ 之前，目前的值是 $ \ge a+b $ 的，且至少在使用完 $ b $ 之后，才可能被卡掉，所以对于任意一个 $ b \le x \le a $ ，在这两种情况下，选与被选的情况相同，不产生影响
。

综上，在最优答案下，我们只会恰好加入一枚硬币，否则无解

考虑枚举 $ 1 $ 到 $ c $ 之间的硬币面额，将其加入。

如何检验？我会暴力！但是 $ O(nc) $ 复杂度太炸了。

考虑记录每一个权值的个数，由枚举硬币到枚举硬币面额。

考虑 $ \sum_{1}^{k} = k \times (k+1) \div 2 $ ，所以枚举到的面额的数量为 $ \sqrt(c) $ 级别的，那么总复杂则为 $ O(c\sqrt c) $ 。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int c,n;
int w[N];
set<int> s;
int cnt[N];
vector<int> tmp;
bool check(){
	int now=c;
	tmp.clear();
	while(now&&s.size()){
		auto pre=s.upper_bound(now);
		if(pre==s.begin()) return true;
		pre--;
		int need=now/(*pre);
		now-=min(need,cnt[*pre])*(*pre);
		tmp.push_back(*pre);
		s.erase(pre);
	}
	if(now) return true;
	for(int i=0;i<tmp.size();i++){
		s.insert(tmp[i]);
	}
	return false;
}
int main(){
	scanf("%d%d",&c,&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		cnt[w[i]]++;
		s.insert(w[i]);
	}
	for(int i=1;i<=c;i++){
		s.insert(i);
		cnt[i]++;
		if(check()){
			cout<<i<<endl;
			return 0;
		}
		cnt[i]--;
		if(cnt[i]==0) s.erase(s.find(i));
	}
	cout<<"Greed is good"<<endl;
	return 0;
}
```



---

## 作者：幻影星坚强 (赞：3)

首先只加入一个硬币是最优的。

假如加入两个硬币a，b且a>b。如果你既拿到了了a也拿到了b，那么假如加入了a+b肯定能拿到（假如不能拿到a+b肯定会使拿a时的面额小于a+b，即不能拿到b），如果不能拿到b那么b显然可以不加。

所以我们可以暴力枚举每一种钱数，之后判断可不可行（方法见代码）

```
#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
int c, n;
int a[200010], tot[200010];
set<int>s, s1;
bool check()
{
	int now = c, next = c;
	while(now)
	{
		int d = *s.lower_bound(-next);//找到最大的哪一个
		if(d == 0)return 1;
		if(now / d * d > tot[-d] * -d)//看看当前数字能不能拿完
		next = - d - 1;//如果这个数字拿完了下一次不能拿
		d = -min(now / d * d, tot[-d] * -d);//能拿就拿当前数字
		now += d;
		next = min(next, now);//下一个数字的范围
	}
	return 0;
}
int main()
{
	scanf("%d%d", &c, &n);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%d", &a[i]);
		++ tot[a[i]];
		s.insert(-a[i]);
	}
	s.insert(0);
	for (int i = 1; i <= c; ++ i)
	{
		++ tot[i];
		s.insert(-i);
		if(check())
		{
			printf("%d", i);
			return 0;
		}
		-- tot[i];
		if(tot[i] == 0)
		s.erase(-i);
	}
	printf("Greed is good\n");
}
```


---

## 作者：Yuno (赞：2)

一般这种任意数量的，都是只有一个或两个 ~~都是套路~~

~~主要是太多了也做不了~~

这题也不例外，最多只可能加入一个硬币。

可以感性理解一下，两个硬币 $a$ 与 $b$ 肯定不如 $a+b$ 来的优秀。

于是可以考虑从小到大枚举那个硬币的权值。

然后判断是否可行，如果不可行说明找到了答案。

当然直接这么做是不行的（$O(nc)$的复杂度）。

需要加入一些剪枝。

假设当前枚举的权值为 $w$

首先判断时可以预处理出比 $w$ 大的那些物品的使用情况，因为当前物品对它们没有影响。

然后有一个很重要的，对于相同的数只扫一次，假如 $x$ 可以使用，那么其他的 $x$ 也可以使用，取决于当前还需要多少钱。

复杂度：$O$ $($ 能过 $)$

应该可以证明是正确的。

$Code:$

```cpp
#include <bits/stdc++.h>

const int N = 2e5 + 7;
int n, c, val[N], s[N], v[N], sum[N];

inline int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x;
}

int main() {
	c = read();
	n = read();
	for (int i = 1; i <= n; ++ i) {
		val[i] = read();
	}
	std::sort(val + 1, val + 1 + n);
	int tot = 1, cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		if (val[i] == val[i + 1]) ++ tot;
		else v[++ cnt] = val[i], sum[cnt] = tot, tot = 1;
	}
	int x = c;
	for (int i = cnt; i >= 1; -- i) {
		if (v[i] <= x) {
			int k = x / v[i];
			k = std::min(k, sum[i]);
			x -= k * v[i];
			s[i] = x;
		} else s[i] = x;
	}
	int pos = 2, ans = 0;
	bool flag = 0;
	for (int i = v[1] + 1; i <= c; ++ i) {
		while (i > v[pos] && pos <= cnt) ++ pos;
		int x = c;
		if (pos <= cnt) x = s[pos];
		else x = c;
		bool tag = 0;
		if (i > x) continue;
		x -= i;
		if (x == 0) continue;
		for (int j = pos - 1; j >= 1; -- j) {
			if (v[j] <= x) {
				int k = x / v[j];
				k = std::min(k, sum[j]);
				x -= k * v[j];
			}
			if (x == 0) {
				tag = 1;
				break;
			}
		}
		if (!tag) {
			flag = 1;
			ans = i;
			break;
		}
	}
	if (!flag) {
		puts("Greed is good");
		return 0;
	}
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：SFlyer (赞：1)

首先一定最多加上一个硬币。为什么呢？考虑如果选了两个 $x,y$，不如一个 $x+y$ 优，因为 $x+y$ 一定选择，$y\le a\le x$ 的 $a$ 位置一样，执行到这些 $a$ 之前价格一样。

因此枚举加的价值。现在考虑怎么求出 $n+1$ 个硬币可不可以。

性质：这些 $n+1$ 个硬币有些选择，有些不选择，选择的**段**数是 $\mathcal{O}(\log n)$ 的。

证明：考虑在可以选的时候尽量选，那么第一次不能选了（设为 $x$），那么现在的价格 $<x$。但是我们选的第一个 $\ge x$，那么我们的价格至少减少了一半，归纳即可。

那么我们直接暴力+二分选择/不选择的段就可以做到 $\mathcal{O}(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

ll n,c,a[N],s[N],p;

int ch(int rb,int cur){
	int l=0,r=rb+1;
	while (l+1<r){
		int mid=l+r>>1;
		if (s[rb]-s[mid-1]<=cur) r=mid;
		else l=mid;
	}
	return r;
}

int nch(int rb,int cur){
	int l=0,r=rb+1;
	while (l+1<r){
		int mid=l+r>>1;
		if (a[mid]<=cur) l=mid;
		else r=mid;
	}
	return r;
}

int cal(int lb,int rb,int cur){
	int fl=(cur>=a[rb]),pos=rb;
	while (pos>=lb){
		if (fl){
			int nxt=ch(pos,cur);
			nxt=max(nxt,lb);
			cur-=s[pos]-s[nxt-1];
			pos=nxt-1;
		}
		else{
			int nxt=nch(pos,cur);
			nxt=max(nxt,lb);
			pos=nxt-1;
		}
		fl=(cur>=a[pos]);
	}
	return cur;
}

void sol(int ad){
	// a_{p+1}~a_n
	int cur=c;
	if (p<n){
		cur=cal(p+1,n,cur);
	}
	if (cur>=ad) cur-=ad;
	if (p){
		cur=cal(1,p,cur);
	}
	if (cur!=0){
		cout<<ad<<"\n";
		exit(0);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>c>>n;
	for (int i=1; i<=n; i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for (int i=1; i<=n; i++){
		s[i]=s[i-1]+a[i];
	}
	for (int i=0; i<=c; i++){
		while (p<n && a[p+1]<=i) p++;
		sol(i);
	}
	cout<<"Greed is good\n";
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 思路

小曹给我们的结论题，被秒了qwq。

首先由于是结论题，所以我们猜个结论：最多只会加一枚硬币。

这个结论看着就很对，然后我们去枚举加的硬币的权值，然后每次去模拟这个过程，即可做到 $O(n^2)$。发现将相同权值的硬币压一下，再用一个 set 查一下目前需要减去的元素，减去的次数是个自然根号级别，于是做到 $O(V \sqrt V \log n)$，可能要写个垃圾回收之类的东西保证复杂度。

然后我们尝试证明一下这个结论：

容易发现多个硬币可以归纳到两个硬币的情况，假设两个硬币权值为 $x, y$，那么有两种情况：

- 只需要 $x, y$ 中的任意一枚即可卡掉这个贪心。
- 如果需要两枚，那么可以加入 $x + y$ 达到同样的效果。

于是这个结论就是对的了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

bool ST;

const int N = 2e5 + 5;

int c, n;
int a[N], tong[N];
set < int > p;
vector < pii > q;

bool ED;

void Solve () {
  ios :: sync_with_stdio ( false );
  cin.tie ( 0 ), cout.tie ( 0 );
  cin >> c >> n;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
    tong[a[i]] ++;
  }
  for ( int i = 200000; i >= 1; i -- ) {
    if ( tong[i] ) {
      p.insert ( i );
    }
  }
  for ( int i = 1; i <= 200000; i ++ ) {
    tong[i] ++;
    if ( tong[i] == 1 ) {
      p.insert ( i );
    }
    int tmp = c, pcnt = 0;
    while ( tmp >= *p.begin () ) {
      auto it = p.upper_bound ( tmp );
      it --;
      pcnt ++;
      int cnt = min ( tmp / *it, tong[*it] );
      tmp -= cnt * *it;
      tong[*it] -= cnt;
      if ( !tong[*it] ) {
        p.erase ( *it );
      }
      q.push_back ( { *it, cnt } );
    }
    if ( tmp ) {
      cout << i;
      return ;
    }
    for ( pii x : q ) {
      if ( !tong[x.first] ) {
        p.insert ( x.first );
      }
      tong[x.first] += x.second;
    }
    q.clear ();
    if ( tong[i] == 1 ) {
      p.erase ( i );
    }
    tong[i] --;
  }
  cout << "Greed is good";
}

signed main () {
#ifdef judge
  cout << ( double ) ( &ST - &ED ) / 1024.0 / 1024.0 << " MB" << '\n';
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

## 题外话

注意到连续成段的选最多只有 $O(\log V)$ 段（经典每次选至少一半的结论），然后我们二分这个段的右端点即可做到更优的 $O(V \log V \log n)$ 复杂度（但是不想写了）。

---

## 作者：Nephren_Sakura (赞：0)

打 CF duel 的时候遇到的题，有点意思，但是绝对没有紫难度。

首先有一个比较显然的结论，你加入进去的硬币一定要被选，不然的话你直接不加入这个硬币肯定更优。

那么我们思考，如果我们现在加入了一个大小为 $a$ 的硬币和一个大小为 $b$ 的硬币可以卡掉贪心，那么一定在这四种情况之一会有一种可以卡掉贪心，并且硬币重量不会劣于分开加入。

1. 加入一个大小为 $a$ 的硬币。

2. 加入一个大小为 $b$ 的硬币。

3. 加入一个大小为 $a+b$ 的硬币。

4. 不加入硬币。

那么我们就可以发现一个很有意思的东西，那就是我们最多加入一个硬币。然后又因为值域很小，于是我们考虑暴力枚举加入的硬币重量然后 check。

那么我们应该怎么 check 呢？首先显然有一个 $O(n)$ 的暴力枚举，事实上因为 CF 神机这已经能过了，但我们还是考虑进一步优化。

然后再思考一下，可以感觉到我们选出的**重量不同**的硬币数量很少，那么这个东西是多少呢，我们套路性的考虑根号分治。

因为我们选出的所有硬币总和必须不超过 $c$，那么硬币重量大于 $\sqrt{c}$ 的硬币至多有不超过 $\sqrt{c}$ 种。而硬币重量小于等于 $\sqrt{c}$ 的硬币总共也就 $\sqrt{c}$ 种，所以总共至多选出 $2 \times \sqrt{c}$ 种。为了好写我用了 set 维护。代码在最后。

似乎有两只 log 的做法，不过我没细想。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int c,n,a[1000005],sum[1000005];
multiset<pair<int,int> > s;
vector<pair<int,int> > v;
bool check(int x){
	v.clear();
	if(sum[x]) s.erase({x,sum[x]});
	sum[x]++;
	s.insert({x,sum[x]});
	int st=x;
	x=c;
	while(x){
		auto k=s.upper_bound({x+1,0});
		if(k==s.begin()){
			x=st;
			for(auto p:v) s.insert(p);
			s.erase({x,sum[x]});
			sum[x]--;
			if(sum[x]) s.insert({x,sum[x]});
			return false;
		}
		k--;
		if(!(*k).first){
			v.push_back(*k);
			s.erase(k);
			continue;
		}
		v.push_back(*k);
		int val=x/(*k).first;
		if(val>(*k).second) val=(*k).second;
		x-=val*(*k).first;
		s.erase(k);
	}
	x=st;
	for(auto p:v) s.insert(p);
	s.erase({x,sum[x]});
	sum[x]--;
	if(sum[x]) s.insert({x,sum[x]});
	return true;
}
signed main(){
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	cin>>c>>n;
	for(int i=1; i<=n; i++) cin>>a[i],sum[a[i]]++;
	for(int i=1; i<=c; i++) if(sum[i]) s.insert({i,sum[i]});
	for(int i=0; i<=c; i++) if(check(i)==false){
		cout<<i;
		return 0;
	}
	cout<<"Greed is good";
	return 0;
}
```

---

