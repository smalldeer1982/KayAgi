# [ARC124C] LCM of GCDs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc124/tasks/arc124_c

赤い袋と青い袋と $ N $ 個のカードパックがあります。はじめどちらの袋も空です。 それぞれのカードパックには整数が書かれた $ 2 $ 枚のカードが封入されており、$ i $ 番目のカードパックに入っているカードにはそれぞれ $ a_i,b_i $ が書かれていることがわかっています。

それぞれのカードパックについて、一方のカードを赤い袋に、他方のカードを青い袋に入れます。

カードを袋に入れ終えたのち、赤い袋に入ったカードに書かれた整数全体の最大公約数を $ X $ とします。 同様に、青い袋に入ったカードに書かれた整数全体の最大公約数を $ Y $ とします。 $ X $ と $ Y $ の最小公倍数の値が得点となります。

得点としてありうる値の最大値を求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ 10^9 $

### Sample Explanation 1

\- $ 2 $ が書かれたカードを赤い袋に入れ、$ 15 $ が書かれたカードを青い袋に入れ、$ 6 $ が書かれたカードを赤い袋に入れ、$ 10 $ が書かれたカードを青い袋に入れるのが最適な入れ方の $ 1 $ つです。 - このとき、赤い袋に入ったカードに書かれた整数全体の最大公約数は $ 2 $、青い袋に入ったカードに書かれた整数全体の最大公約数は $ 5 $ です。 - このときの得点は $ 10 $ です。

## 样例 #1

### 输入

```
2
2 15
10 6```

### 输出

```
10```

## 样例 #2

### 输入

```
5
148834018 644854700
947642099 255192490
35137537 134714230
944287156 528403260
68656286 200621680```

### 输出

```
238630```

## 样例 #3

### 输入

```
20
557057460 31783488
843507940 794587200
640711140 620259584
1901220 499867584
190122000 41414848
349507610 620259584
890404700 609665088
392918800 211889920
507308870 722352000
156850650 498904448
806117280 862969856
193607570 992030080
660673950 422816704
622015810 563434560
207866720 316871744
63057130 117502592
482593010 366954816
605221700 705015552
702500790 900532160
171743540 353470912```

### 输出

```
152594452160```

# 题解

## 作者：HomuraAkemi (赞：2)

考虑到 $\gcd$ 有着每次值域至少减半的优良性质，考虑 DP：设 $f(x,y)$ 表示是否能到达 $\gcd\{A\}=x,\gcd\{B\}=y$，转移显然。

用 $\texttt{std::set}$ 存储有用的状态即可。好想，好写。

[代码](https://atcoder.jp/contests/arc124/submissions/58132678)。

---

## 作者：Cure_Wing (赞：2)

[AT_arc124_c [ARC124C] LCM of GCDs](https://www.luogu.com.cn/problem/AT_arc124_c)

### 思路

看到这种题目会想到一种贪心：

假设现在将前 $k$ 个数分成了两组，分别为 $k1,k2$，现在要加入的数分别是 $a,b$。计算一下 $\gcd(k1,a)$ 和 $\gcd(k1,b)$ 的值。如果前者更大那么把 $a$ 并入 $k1$，把 $b$ 并入 $k2$；如果后者更大或两者相等那么把 $b$ 并入 $k1$，把 $a$ 并入 $k2$。

这样虽然是 $O(n)$ 的，但是这个贪心是有问题的，因为很有可能加入的数把 $k2$ 的 $\gcd$ 大大削弱。

但是发现 $n\le50$，所以想到用模拟退火，每次交换两组数的插入顺序，通过改变加入顺序来避免特定情况加入时可能会产生的问题。此时如果更优就接受交换，否则一定概率不接受此次交换，这样就可以逐步接近答案。

而且参数也很好调，没有出现卡常的情况。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<ctime>
using std::cin;using std::cout;
constexpr int N=55;
constexpr double sp=1e18,del=0.9998,ed=1e-10;
int n,a[N][2],b[2],p[N];
long long ans;
signed main(){
	freopen("euterpe.in","r",stdin);
	freopen("euterpe.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;srand(time(nullptr));
    for(int i=1;i<=n;++i) cin>>a[i][0]>>a[i][1],p[i]=i;
    for(double i=sp;i>=ed;i*=del){
        int d=rand()%n+1,c=rand()%n+1;
        std::swap(p[c],p[d]);
        b[0]=b[1]=0;
        for(int j=1;j<=n;++j){
            int k=std::__gcd(b[0],a[p[j]][0]),q=std::__gcd(b[0],a[p[j]][1]);
            if(k<q){
                b[0]=std::__gcd(b[0],a[p[j]][1]);
                b[1]=std::__gcd(b[1],a[p[j]][0]);
            }else{
                b[0]=k;
                b[1]=std::__gcd(b[1],a[p[j]][1]);
            }
        }
        long long now=1ll*b[0]/std::__gcd(b[0],b[1])*b[1];
        if(now>ans) ans=now;
        else if(exp((ans-now)/ans)<1.0*rand()/RAND_MAX) std::swap(p[c],p[d]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Pt_crN (赞：2)

又是不会做的纸张题。

直接暴力搜索很明显会爆炸，所以考虑枚举最后两个集合的 $\gcd$ 值。但是值域去到了 $10^9$，明显爆炸。但是发现集合只要确定了一个数，可能的 $\gcd$ 值就一定是该数的因数，枚举复杂度降到 $d^2(10^9)$，大约是 $10^6$ 级别。然后 $O(n)$ 检查能不能取到这个值即可。

code：

```cpp
int n,m,e[57],d[57];
vector<int> v1,v2;
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
inline ll Lcm(ll a,ll b){
	return a*b/gcd(a,b);
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&e[i],&d[i]);
	}
	int a=e[1],b=d[1];
	for(int i=1;i*i<=a;i++){
		if(a%i==0){
			v1.push_back(i);
			v1.push_back(a/i);
		}
	}
	for(int i=1;i*i<=b;i++){
		if(b%i==0){
			v2.push_back(i);
			v2.push_back(b/i);
		}
	}//找因数
	ll ans=1;
	for(int i:v1){
		for(int j:v2){
			bool flag=true;
			for(int k=2;k<=n;k++){
				if((e[k]%i!=0||d[k]%j!=0)&&(e[k]%j!=0||d[k]%i!=0)){
					flag=false;
					break;
				}
			}//检查是否可行
			if(flag){
				ans=max(ans,Lcm(i,j));
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：User_Authorized (赞：2)

## 题面

给定 $N$ 个正整数对 $(a_i, b_i)$ 和两个初始为空的集合 $S, T$，你可以选择将每个数对的两个元素划分到两个不同的集合中。求 

$$\max\operatorname{lcm}(\gcd\limits_{x \in S}x, \gcd\limits_{y \in T}y)$$

（$1 \le N \le 50, 1 \le a_i, b_i \le 10^9$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC124C.html)

首先，对于任意正整数 $x, y$，有 $\gcd(x, y) \mid x$，所以我们设 $A = a_1, B = b_1$，因为两个集合等价，故我们钦定 $A \in S, B \in T$，所以有 $\gcd\limits_{x \in S}x \mid A, \gcd\limits_{y \in T}y \mid B$。

因为有 $A, B \le 10^9$，所以 $A, B$ 的约数个数是很少的，所以我们可以枚举 $A, B$ 的约数 $x, y$，并 $\mathcal{O}(N)$ 判断其是否可以成为集合的最大公约数，若可行则更新答案。

总复杂度 $\mathcal{O}(d(A)d(B)N)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;

valueType lcm(valueType a, valueType b) {
    return a / std::__gcd(a, b) * b;
}

ValueVector divisor(valueType n) {
    ValueVector result;

    for (valueType i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);

            if (i * i != n)
                result.push_back(n / i);
        }
    }

    std::sort(result.begin(), result.end());

    return result;
}

bool check(valueType a, valueType b, PairVector const &data) {
    return std::all_of(data.begin(), data.end(), [a, b](ValuePair const &iter) {
        return (iter.first % a == 0 && iter.second % b == 0) || (iter.second % a == 0 && iter.first % b == 0);
    });
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    PairVector data(N);

    for (auto &iter: data)
        std::cin >> iter.first >> iter.second;

    ValueVector const A = divisor(data[0].first), B = divisor(data[0].second);

    valueType ans = 0;

    for (auto const &a: A)
        for (auto const &b: B)
            if (check(a, b, data))
                ans = std::max(ans, lcm(a, b));

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Tastoya (赞：1)

#### 题目大意

有 $N$ 组写了数字的卡片每组两张，每组卡片需要各放一张到两个袋子中，令两个袋子里数的最大公约数分别为 $X$ 和 $Y$，求 $X$ 和 $Y$ 的最小公倍数的最大值。

#### 思路
一个数的约数个数增长较慢，上界到 $10^9$ 的最大约数个数只有 $1344$ 个。
![](https://cdn.luogu.com.cn/upload/image_hosting/2cjzkhon.png)
考虑直接分解 $a,b$ 中开头的两个元素的约数，去枚举约数求解。

分别枚举约数，可以直接判断枚举的这两个数是否分别是其序列的最大公约数。

由于 $a_i$ 与 $b_i$ 是可以交换的，所以我们要判断一下这一位下 $a_i$ 和 $b_i$ 交换后是否为公约数。

如果枚举的两个数分别是其序列的最大公约数可以求最小公倍数记录最大值。
#### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;

int a[55],b[55];

vector<int> Fac1,Fac2;

bool Check(int x,int y) {
    for(int i = 1;i <= n; i++)
        if((a[i] % x != 0 || b[i] % y != 0) && (a[i] % y != 0 || b[i] % x != 0))
            return false;
    
    return true;
}

int lcm(int a,int b) {
    return a / __gcd(a,b) * b;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for(int i = 1;i <= n; i++)
        cin >> a[i] >> b[i];
    
    for(int i = 1;i * i <= a[1]; i++) {
        if(a[1] % i != 0)
            continue;

        Fac1.push_back(i);
        Fac1.push_back(a[1] / i);
    }

    for(int i = 1;i * i <= b[1]; i++) {
        if(b[1] % i != 0)
            continue;

        Fac2.push_back(i);
        Fac2.push_back(b[1] / i);
    }

    int ans = 0;
    for(auto const &i : Fac1) {
        for(auto const &j : Fac2) {
            if(Check(i,j)) {
                ans = max(ans,lcm(i,j));
            }
        }
    }

    cout << flush;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

发现一个数字的约数个数不大，而且题中的 $n$ 也不大，所以我们可以暴力枚举可能的 $X,Y$。

由于 $X,Y$ 一定都在第一组卡片的因数中，所以不妨找到第一组卡片的所有因数，存储起来。

然后枚举所有可能的 $X,Y$ 组合，带到每组卡片里面看看是否合法，合法的话更新最大值即可。

[提交记录](https://atcoder.jp/contests/arc124/submissions/58285895)

---

## 作者：zhengpie (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc124_c)

### 1.思路

首先，我们要意识到一件事情：
$$\gcd(a_1,a_2,\cdots,a_n) \leq a_i(i \in [1,n])$$
（因为一个数的因数肯定会小于他们本身）

于是，不妨设 $a_1$ 落到第一个袋子里，$b_1$ 落到第二个袋子里。那么根据上面的结论（或者说是性质？），题目中的 $X \leq a_1,Y \leq b_1$。

所以说我们只需用 $A_i$ 记录 $a_1$ 的正因子，用 $B_i$ 记录 $b_1$ 的正因子，然后两重循环枚举 $A_i,B_j$ 表示 $X,Y$，再开一重循环检查是否是其他数的因子即可。

### 2.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ioimprove(); ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define FILE(x); freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
int n,a[55],b[55];
vector<int> A,B;
inline bool chk(int x,int y) 
{
    for(int i = 2;i <= n;i++)
        if((a[i] % x != 0 || b[i] % y != 0) && (a[i] % y != 0 || b[i] % x != 0))
            return false;
    return true;
}
inline int gcd(int a,int b)
{
	return ((b == 0) ? a : gcd(b,(a % b)));
}
inline int lcm(int a,int b) 
{
    return a / gcd(a,b) * b;
}
inline char qgetchar()
{
	static char buf[1 << 14],*begin = buf,*end = buf;
	if(begin == end) 
	{
		begin = buf;
		end = buf + fread(buf,1,1 << 14,stdin);
	}
	return *begin++;
}
inline int qread()//快读的板子
{
    int f = 1,x = 0;char op;
    do
	{
		op = qgetchar();
		if(op == '-')f = -1;
	}
	while(op < '0' || op > '9');
    do
	{
		x = x * 10 + op - '0';
		op = qgetchar();
	}
	while(op >= '0' && op <= '9');
    return f * x;
}
signed main() 
{
    //FILE("greeting");
	ioimprove();
    n = qread();
    for(int i = 1;i <= n;i++) a[i] = qread(),b[i] = qread();
	for(int i = 1;i * i <= a[1];i++) 
	{
        if(a[1] % i != 0) continue;
        A.push_back(i);
        if(a[1] / i != i) A.push_back(a[1] / i);
    }
    for(int i = 1;i * i <= b[1];i++) 
	{
        if(b[1] % i != 0) continue;
        B.push_back(i);
        if(b[1] / i != i) B.push_back(b[1] / i);
    }
    int ans = 1ll;
    for(auto &i : A)
        for(auto &j : B)
            if(ans < lcm(i,j))	//这样子会快一点，因为chk()的复杂度是O(n)
				if(chk(i,j)) ans = lcm(i,j);
    cout<<flush<<ans;
    return 0;
}
```

---

