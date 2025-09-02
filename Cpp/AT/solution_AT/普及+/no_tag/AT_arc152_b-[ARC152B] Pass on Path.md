# [ARC152B] Pass on Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc152/tasks/arc152_b

長さ $ L $ の細長い一直線の道が東西に伸びており、この道を $ 2 $ 人の旅人が訪れます。 この道には $ N $ 個の休憩所があり、$ i $ 番目の休憩所は、道の西端から $ a_i $ の地点にあります （ただし、どの休憩所も道の端には存在しません）。 この道はとても細いため、休憩所以外の地点で $ 2 $ 人がすれ違ったり、横に並んで歩いたりすることはできません。

$ 2 $ 人の旅人は、この道で次のような旅をします。

- 時刻 $ 0 $ に、それぞれ好きな休憩所を選んで出発点とする（ $ 2 $ 人が同じ休憩所を選んでもよい）。 その後、それぞれ道の両端を訪れたあと、自身の出発点に戻る。
 
$ 2 $ 人は、毎秒 $ 1 $ 以下の速さで道を歩くか、休憩所で休憩することができます。 休憩所以外の地点ですれ違わない限り、旅の途中いつでも向きを変えることは可能です。 両者が道の両端を訪れて出発点に戻ってくるまで、最短で何秒かかるでしょうか。 ただし、この問題の制約下では答えが整数になることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 0\ <\ a_1\ <\ a_2\ <\ \ldots\ <\ a_N\ <\ L $
- 入力される値はすべて整数である
 
### Sample Explanation 1

$ 2 $ 人の旅人を A、B とします。また、以下では $ i $ 番目の休憩所を単に休憩所 $ i $ と呼びます。 例えば、$ 2 $ 人は以下のような旅をすることができます。 最初に A が休憩所 $ 1 $ から東側に、B が休憩所 $ 2 $ から東側に速さ $ 1 $ で歩き始め、両者とも東端→西端の順に訪れることにします。 すると、B は $ 2 $ 秒後に東端を訪れて休憩所 $ 2 $ に戻って来ることができますが、A はまだ休憩所 $ 1 $ と $ 2 $ の間です。 ここで B が $ 1 $ 秒休憩すると、A も休憩所 $ 2 $ にたどり着き、すれ違いが可能になります。 その後、再び両者が速さ $ 1 $ で歩き続け、A が休憩所 $ 1 $ で $ 2 $ 秒だけ休憩した場合、 B は出発から $ 13 $ 秒後、A は $ 14 $ 秒後に元の休憩所に戻り、旅を終えることができます。 実はこれは最善の方法の $ 1 $ つであり、答えは $ 14 $ となります。

### Sample Explanation 2

この場合は、適切な方法を取ると、両者が休憩することなく速さ $ 1 $ で歩き続けることができます。

## 样例 #1

### 输入

```
2 6
2 5```

### 输出

```
14```

## 样例 #2

### 输入

```
2 3
1 2```

### 输出

```
6```

# 题解

## 作者：_Life_ (赞：2)

### 题解

结论：从同一个休息站出发，背向而行。

A 和 B 必定相遇两次，相遇地点在休息站，相遇时面向对方。

第一次相遇在位置 $p$ 的休息站。

第二次相遇在距离位置 $L-p$ 最近的休息站。

所以第一次相遇的位置决定第二次相遇的位置。

两次相遇额外花费的时间加上两倍长度就是答案。

第二次相遇额外花费时间受第一次相遇站点位置控制。

把两个人初始安排在同一个休息站可以认为是第一次相遇，第一次相遇额外花费的时间为 $0$。

枚举初始出发休息站，计算第二次额外花费的时间即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
//#define mod 1000000007
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
typedef pair<int,int> pii;
void setIn(string s){freopen(s.c_str(),"r",stdin);}
void setOu(string s){freopen(s.c_str(),"w",stdout);}
void setIO(string s){setIn(s+".in"),setOu(s+".out");}
template<class T>void chkmax(T &a,T b){a=max(a,b);}
template<class T>void chkmin(T &a,T b){a=min(a,b);}
template<class T>T read(T &x)
{
	x=0;T f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*=f;
}
template<class T,class ...L>void read(T &x,L &...l){read(x),read(l...);}
template<class T>void write(T x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
template<class T>void write(T x,char c){write(x),putchar(c);}
int n,m,ans=0x3f3f3f3f3f3f3f3f,a[200005];
vector <int> pos;
signed main()
{
	read(n,m);
	rep(i,1,n)pos.push_back(read(a[i]));
	sort(pos.begin(),pos.end());
	rep(i,1,n)
	{
		int t=m-a[i];
		int p=lower_bound(pos.begin(),pos.end(),t)-pos.begin();
		int tmp=abs(pos[p]-t);
		if(p-1>=0)chkmin(tmp,abs(pos[p-1]-t));
		if(p+1<n)chkmin(tmp,abs(pos[p+1]-t));
		chkmin(ans,tmp);
	}
	write(2*m+2*ans);
}
```

---

## 作者：有趣的问题 (赞：2)

# ARC152B  题解

### 题意简述

在一条细长的路上有若干个休息区，有两个人在走路。每个人都需要从某一休息区出发，到达路的两个端点并返回初始休息区。由于路很狭窄，两人只能在休息区相遇，也就是说某人可能需要在某一休息区等另外一个人。请你做出合适的安排使得从两人出发到两人都回到出发点的总时间最少。

### 思路分析

约定：令 $x,y$ 分别表示两人的出发点，钦定 $x<y$；令 $t,w$ 分别表示两次的相遇点。

阅读题目后，不难发现，除非两人从同一点出发，否则他们一定会相遇两次。

由于两人必须在等候区相遇，我们容易发现两人在第一次相遇后会同时同地反向出发。

由此，我们可以容易地找到他们第二次相遇的等候区。设第一次在 $t$ 相遇，则第二次在离 $l-t$ 最近两个等候区之一相遇。

我们令 $S$ 表示两次相遇之间经过的时间，则有 $S=\max(t+w,2l-t-w)$，这个式子的两部分分别表示到达左边的端点并折返与到达右边的端点并折返。

如果两人从同一端点出发，则答案就为 $2S$，原因显然。

否则答案为 $\text{第一次相遇的时间}+\text{第二次相遇后回出发点的时间}+S$。

下面我们来研究这个第一次相遇的时间。

+ 同向出发：
  $$
  ans=\max(t+x,y-t)+\max(w-x,2l-w-y)+S
  $$
  
+ 反向出发：
  $$
  ans=max(x+t,2l-t-y)+max(w-x,y-w)+S
  $$


我们发现，无论是哪一种情况，这个 $ans$ 的左边部分都一定不小于 $S$，因为 $S$ 中的两种情况在 $ans$ 中都有出现。因此，我们证明了两人从同一端点出发一定能获得最优解。

以上过程明晰了过后，代码也就很简单了（鸣谢 @[Sukwants](https://github.com/Sukwants) @ [Song_gch](https://www.luogu.com.cn/blog/songgch/) 两位大佬的思路和代码）：

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 2e5;

int N;
long long L, a[MAXN + 5];
long long Ans = 0x3f3f3f3f3f3f3f3f;

int main()
{
    scanf("%d%lld", &N, &L);
    for (int i = 1; i <= N; ++i) scanf("%lld", a + i);

    for (int i = 1; i <= N; ++i)
    {
        int x = lower_bound(a + 1, a + N + 1, L - a[i]) - a;
        Ans = min(Ans, min(x <= N ? (a[i] + a[x]) : 0x3f3f3f3f3f3f3f3f, x > 1 ? ((L << 1) - a[i] - a[x - 1]) : 0x3f3f3f3f3f3f3f3f));
    }

    printf("%lld\n", Ans << 1);

    return 0;
}
```



---

## 作者：_ZSR_ (赞：0)

### [[ARC152B] Pass on Path](https://www.luogu.com.cn/problem/AT_arc152_b)

假设两个人分别从 $x,y$ 出发，其中 $x<y$。显然，他们如果不在同一休息站出发，必定会相遇两次。由于他们速度一样，所以相遇后肯定会反向出发。假设他们在 $a$ 第一次相遇，如果每个位置都有休息站的话，那么他们第二次相遇会在 $L-a$。事实上并不是每个位置都有休息站，但为了让时间最小，他们会在离 $L-a$ 最近的两个休息站中的一个相遇，把这个休息站记为 $b$。

考虑两次相遇的间隔为多长。向西走的人需要花费 $a-b+2 \times b=a+b$ 的时间走到西边的尽头并且来到相遇的休息站，向东走的人需要花费 $2 \times (L-a)+a-b=2 \times L-a-b$ 的时间走到东边的尽头并且来到相遇的休息站。间隔时间 $T$ 就是两人要花费的时间取 $\max$，因为时间短的人要等时间长的人。

如果两个人一开始从同一个休息站反向出发，那么最终花费的时间就是 $2 \times T$。如果不是从同一个休息站出发的，那么最终花费的时间就是到达第一次相遇的休息站的时间 $+$ 从第二次相遇的休息站回去的时间 $+T$。如果是同向出发（假设同时向西走），时间为 $\max(x+a,y-a)+\max(b-x,2 \times L-y-b)+T$。如果是反向出发，时间为 $\max(x+a,2 \times L-y-a)+\max(b-x,y-b)+T$。可以发现，两个式子中除了 $T$ 以外的部分都不小于 $T$，因此我们可以证明两个人一开始从同一个休息站反向出发是最优的。

关于代码实现，这里提一个点。我们每次二分找到大于等于 $L-a$ 的第一个 $x_i$，答案和 $\min(a+x_i,2 \times L-a-x_{i-1})$ 取 $\min$。我们之前说 $T=\max(a+b,2 \times L-a-b)$，但这里为什么不用了呢？因为当 $b=L-a$ 时，两式相等。那么 $b$ 变大，$a+b$ 就一定大于 $2 \times L-a-b$；$b$ 变小，$2 \times L-a-b$ 一定大于 $a+b$，所以就省去了取 $\max$ 这一步。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,INF=1e18;
int n,l,ans=INF;
int a[N];
signed main()
{
    scanf("%lld%lld",&n,&l);
    for (int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for (int i=1;i<=n;++i)
    {
        int p=lower_bound(a+1,a+n+1,l-a[i])-a;
        ans=min(ans,min(p<=n?a[i]+a[p]:INF,p>1?l*2-a[i]-a[p-1]:INF));
    }
    printf("%lld\n",ans<<1);
    return 0;
}
```


---

## 作者：EnofTeiPeople (赞：0)

场上把 $\inf$ 设为 $10^9$ 炸了，后来发现答案甚至会超过 $2\times10^9$，结果只切了了一题掉大分。

通过分析和猜测，我们发现，两个人从同一起点出发一定不劣，考虑从休息区 $x$ 出发，两个人一个往左走，一个往右走，在令其于 $y$ 休息区错开，即一个人等另一个人，这时答案为 $2\max\{a_x+a_y,2L-a_x-a_y\}$，相当于枚举 $x$ 找到离 $L-a_x$ 最近的两个 $y$，全部取 $\min$ 得到答案：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
using ll=long long;
ll n,L,a[N],ans=1e18;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>L;
    int i,sum=0,x;
    for(i=1;i<=n;++i)cin>>a[i];
    for(i=1;i<=n;++i){
        x=upper_bound(a+1,a+n+1,L-a[i])-a-1;
        if(x>=1&&x<=n)ans=min(ans,L+L-(a[i]+a[x]));++x;
        if(x>=1&&x<=n)ans=min(ans,a[i]+a[x]);
    }
    printf("%lld\n",ans<<1);
    return 0;
}
```

---

