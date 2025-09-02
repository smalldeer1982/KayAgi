# [AGC013C] Ants on a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc013/tasks/agc013_c

周の長さ $ L $ の円があります。 この円の周上には座標が設定されていて、座標の値は、ある基準点からどれだけ時計回りに進んだかを表しています。

この円周上に $ N $ 匹の蟻がいます。 蟻には、座標の小さいものから順に、$ 1 $ から $ N $ までの番号がついています。 $ i $ 番目の蟻は座標 $ X_i $ にいます。

これから、$ N $ 匹の蟻は一斉に動き出します。 $ i $ 匹目の蟻は、$ W_i $ が $ 1 $ なら時計回りに、$ W_i $ が $ 2 $ なら反時計回りに動き始めます。 全ての蟻の移動速度は常に、$ 1 $ 秒間にちょうど $ 1 $ の距離を進む速さです。 蟻が動いていくと、二つの蟻がぶつかることがあります。 その時はどちらの蟻も、ぶつかった瞬間に進む向きを反転して動き続けます。

蟻が動き始めてから $ T $ 秒後にそれぞれの蟻がいる位置を求めて下さい。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 1\ \leq\ T\ \leq\ 10^9 $
- $ 0\ \leq\ X_1\ <\ X_2\ <\ ...\ <\ X_N\ \leq\ L\ -\ 1 $
- $ 1\ \leq\ W_i\ \leq\ 2 $

### Sample Explanation 1

蟻が動き始めてから $ 1.5 $ 秒後、蟻 $ 1 $ と 蟻 $ 2 $ が、座標 $ 1.5 $ の位置でぶつかります。 その $ 1 $ 秒後、蟻 $ 1 $ と蟻 $ 3 $ が、座標 $ 0.5 $ の位置ぶつかります。 その $ 0.5 $ 秒後、つまり蟻が動き始めてから $ 3 $ 秒後には、 蟻 $ 1 $ 、$ 2 $ 、$ 3 $ はそれぞれ座標 $ 1 $ 、$ 3 $ 、$ 0 $ にいます。

## 样例 #1

### 输入

```
3 8 3
0 1
3 2
6 1```

### 输出

```
1
3
0```

## 样例 #2

### 输入

```
4 20 9
7 2
9 1
12 1
18 1```

### 输出

```
7
18
18
1```

# 题解

## 作者：_Felix (赞：26)

考虑到原来每只蚂蚁都在相邻之间撞来撞去，所以肯定最后每只蚂蚁的相对顺序是不会改变的。显然可以直接确定最后位置的整个序列，只要确定 $1$ 号蚂蚁在序列的位置（最终编号），就可以知道每只蚂蚁最后实际的位置。


不妨想象成蚂蚁相撞，蚂蚁相互穿过，编号交换。 $i$ 号蚂蚁的实际位置应当在拥有 $i$ 编号的蚂蚁的位置。

考虑在直线上的情况，直接对应就行了。但现在是在环上，如果有一只蚂蚁逆时针经过 $0$ ，那么 $1$ 号蚂蚁最后的位置就会向前一位，顺时针则会向后一位。(想象成这只蚂蚁变成了负数，那么在直线上，他应该是最前面的，但先在在环上，所以他穿过去了，就会变成最后面的，所以原来在他后面的都会往前挪一位）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, l, t, ans[N]; 
int main() {
	scanf("%d%d%d", &n, &l, &t);
	int cnt = 0;
	for(int i = 0, x, w; i < n; i++){
		scanf("%d%d", &x, &w);
		x += ((w == 1) ? t : -t);
		cnt = ((cnt + (int)floor(1.0 * x / l)) % n + n) % n; 
		ans[i] = (x % l + l) % l;
	}
	sort(ans, ans + n);
	for(int i = 0; i < n; i++)
		printf("%d\n", ans[(cnt + i) % n]); 
	return 0;
}
```

---

## 作者：小粉兔 (赞：7)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC013.html](https://www.cnblogs.com/PinkRabbit/p/AGC013.html)。

这是某一道经典题的变形，经典题为：

- 在一根长度为 $L$ 的棍子上，有 $N$ 只蚂蚁，位置互不相同且朝向左或右，其中蚂蚁的行为与本题相同。

- 求出 $T$ 时刻后每只蚂蚁的位置（如果蚂蚁从一端掉下请求出它从哪一段掉下）。

这道经典题的做法是：

- 假设棍子的左右两端都是无限长的，这样暂时不需要考虑掉下的情况。

- 在两只蚂蚁碰撞时，我们假设蚂蚁其实没有掉头，而是直接穿过彼此。

- 这样我们可以在 $\mathcal O (N)$ 的复杂度内，直接算出 $T$ 时刻后哪些位置还存在蚂蚁，将这些位置排序，花费 $\mathcal O (N \log N)$。

- 注意到在任意时刻，无论是有发生碰撞还是没有发生碰撞，所有蚂蚁之间的相对位置都不会改变。

- 所以初始时在最左侧的蚂蚁，在最终时刻的位置一定是最小的那个位置，以此类推。

- 最后如果位置超出了原棍子的范围，那么蚂蚁就是掉下了棍子。

在本题中也是类似的，我们假设蚂蚁是穿过了彼此，这样可以求出 $T$ 时刻后哪些位置上还存在蚂蚁。

但是蚂蚁之间的相对位置无法比较显然地确定，我们仅知道蚂蚁在环上的相对位置是与原来循环同构的。

我们考虑：一开始第 $i$ 只蚂蚁携带着一个显示着数值 $i$ 的电子屏，两只蚂蚁碰撞时看作它们穿过了彼此，但电子屏上的数值交换。

也就是说任意时刻蚂蚁携带的电子屏上的数值，就是**实际上**该蚂蚁的编号（我们假设每只蚂蚁编号从不改变，仅有显示屏变化）。

我们考虑，碰撞时，左侧的蚂蚁携带的电子屏上的数值实际上是增加了 $1$，除非数值为 $N$，那样必然是与携带着数值 $1$ 的蚂蚁碰撞。

同理右侧的蚂蚁携带的数值减少了 $1$，除非数值为 $1$，那样会变成 $N$。

但是，如果在模 $N$ 的剩余系下考虑，就仅仅是左侧的蚂蚁携带的数值增加 $1$，右侧的蚂蚁携带的数值减少 $1$ 而已。

最终取所在剩余类中，在 $[1, N]$ 范围内的元素作为真实值即可。

此时也就是要求每只蚂蚁与反向的蚂蚁碰撞的次数，如果该蚂蚁是朝顺时针方向（正方向）的，其编号增加碰撞次数，否则减少。

这可以通过在另一朝向的所有蚂蚁中计算绕过了几圈，并对剩余的不足一圈的蚂蚁执行二分查找得出。

时间复杂度为 $\mathcal O (N \log N)$。

```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;
const int MN = 100005;

int N, L, T, X[MN], W[MN], Y[MN], Id[MN];
int X1[MN], X2[MN], C1, C2;
int Ans[MN];

inline LL Q1(LL v) {
	LL w = (v % L + L) % L, k = (v - w) / L;
	return std::upper_bound(X1, X1 + C1, w) - X1 + k * C1;
}
inline LL Q2(LL v) {
	LL w = (v % L + L) % L, k = (v - w) / L;
	return std::upper_bound(X2, X2 + C2, w) - X2 + k * C2;
}

int main() {
	scanf("%d%d%d", &N, &L, &T);
	for (int i = 0; i < N; ++i) {
		scanf("%d%d", &X[i], &W[i]);
		if (W[i] == 1) X1[C1++] = X[i];
		if (W[i] == 2) X2[C2++] = X[i];
	}
	for (int i = 0; i < N; ++i) {
		Y[i] = X[i];
		if (W[i] == 1) {
			Y[i] = (Y[i] + T) % L;
			Id[i] = (i + Q2(X[i] + 2ll * T) - Q2(X[i])) % N;
		}
		if (W[i] == 2) {
			Y[i] = (Y[i] - T % L + L) % L;
			Id[i] = ((i - Q1(X[i] - 1) + Q1(X[i] - 2ll * T - 1)) % N + N) % N;
		}
		Ans[Id[i]] = Y[i];
	}
	for (int i = 0; i < N; ++i) printf("%d\n", Ans[i]);
	return 0;
}
```

---

## 作者：龙翔凤翥 (赞：4)

分析:显然蚂蚁的相对位置不变，然后相遇掉头可以理解为改变编号
------------
```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
#define ll long long
const int maxn=100000+10;
int x[maxn],xx[maxn],w[maxn];
int i,j,k,l,r,s,t,n,m;
ll c;
inline int read()
{
    int k=1;int x=0;
    char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')
    k=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
    x=x*10+ch-'0',ch=getchar();
    return k*x;
}
int main()
{
    n=read(),l=read(),t=read();
    fo(i,1,n)
        x[i]=read(),w[i]=read();
    fo(i,1,n)
    {
        if (w[i]==2) w[i]=-1;
        r=x[i]+w[i]*t;
        if (r>0) (c+=r/l)%=n;
        else if (r<0) (c+=(r+1)/l-1)%=n;
        xx[i]=(r%l+l)%l;
    }
    sort(xx+1,xx+n+1);
    c=(c+n)%n;
    fo(i,c+1,n)
        printf("%d\n",xx[i]);
    fo(i,1,c) printf("%d\n",xx[i]);
}

```

---

## 作者：灰鹤在此 (赞：3)

加强版：[CF652F Ants on a Circle](https://www.luogu.com.cn/problem/CF652F)

题意：给你 $n$ 只不同位置的蚂蚁、长度为 $l$ 的一个环和总时间 $t$，每只蚂蚁每秒走 $1$ 长度。然后给你每只蚂蚁的位置和方向（顺时针或逆时针），让你求 $t$ 秒之后每一只蚂蚁的位置（顺序同输入顺序）。

解题思路：假如我们站在很高很高的山上看这群蚂蚁在绕着这个环转，那么我们会很惊奇的发现，两只蚂蚁碰到之后，他们居然穿过了对方！而且，因为是一个环，每一只蚂蚁只要碰到对方就掉头，那么，排在一只蚂蚁顺时针方向的蚂蚁永远不会到这只蚂蚁的逆时针（指相对位置），排在一只蚂蚁逆时针方向的蚂蚁永远不会到这只蚂蚁的顺时针。于是我们得到，他们的相对位置是永不变的。

因为这一题里面输入的蚂蚁位置是升序的，所以我们不需要排序。

于是我们只需要紧盯着一只蚂蚁，我取了排完序后距离最小的第一只蚂蚁，然后求出它的精确位置，于是我们就可以得到所有蚂蚁的位置了。

由于是在环上，我们之前取的第一只蚂蚁走过 $t$ 秒后并不一定就还是最靠前的（相对于环上的位置 $0$），我们记 $0$ 为蚂蚁运动时一个固定的“路标”，如果有蚂蚁顺时针经过了 $0$，那么 $1$ 号蚂蚁前面就多了一只蚂蚁（在以 $0$ 位置为起点 $0\degree\sim360\degree$ 时）。如果有蚂蚁逆时针经过了 $0$，那么 $1$ 号蚂蚁前面就少了一只蚂蚁。因为我们是拿 $0$ 作为参考系的，所以 $1$ 号蚂蚁经过 $0$ 也要处理。由此，我们就可以计算出 $1$ 号蚂蚁前面有多少只蚂蚁了，然后我们从 $1$ 号蚂蚁依次把排序完后的所有蚂蚁最终的位置传给每一只蚂蚁就行了。

我们能这么做的原因是：你可以想象一只带着光源的蚂蚁，然后他从 $x$ 位置出发，如果他碰到了一只蚂蚁，那么他就把光源传给了他碰到的那一只蚂蚁，然后那一只蚂蚁又碰到了另一只蚂蚁，那么那一只蚂蚁就把光源传给了另一只蚂蚁……由此看来，我们根本无需在蚂蚁爬行时那么在意他们的编号。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=1e5+5;
int n,l,t,first_ant_place;
struct hh{
	int place,towards,ends;//towards=1-->往数值大的地方走,towards=2-->往数值小的地方走
	bool friend operator < (hh x,hh y){
		return x.ends<y.ends;
	}
}a[MaxN];
int main(){
	scanf("%d%d%d",&n,&l,&t);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].place,&a[i].towards);
		if(a[i].towards==1){
			a[i].ends=a[i].place+t;
		}else{
			a[i].ends=a[i].place-t;
		}
		first_ant_place=(first_ant_place+(int)floor(1.0*a[i].ends/l)%n+n)%n;
		a[i].ends=(a[i].ends%l+l)%l;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		printf("%d\n",a[(first_ant_place+i-1)%n+1].ends);
	}
	return 0;
}
```

---

## 作者：Kinandra (赞：3)

标签: ?

(看了其他题解发现自己的做法好复杂, 有兴趣就康康吧

将"**两只蚂蚁相遇掉头看成穿过**"这种基操就不赘述了, 我们只需要知道最后第一只蚂蚁的位置就可以推出所有蚂蚁的位置了.

(这个部分由于本人并没有想到其他题解的正常做法, 剑走偏锋搞出了个十分复杂的做法

在第一只蚂蚁身上放一块宝石, 当两只蚂蚁互相穿过时, 没有宝石的蚂蚁会抢走宝石, 那么最后有宝石的蚂蚁的位置及**问题未转化前**的第一只蚂蚁的位置.

我们将蚂蚁按运动方向分成两组 $A,B$, 手动模拟发现宝石随着时间推移轮流到两组的蚂蚁手中. 通过画图等方法, 很容易得出如下结论: 从蚂蚁 $a\in A$ 从蚂蚁 $b\in B$ 抢走宝石, 到被蚂蚁 $c\in B$ 抢走宝石的过程中, $a,c$ 走过的**路程和**恰好为 $b,c$ 间的距离, 所以对于给定的时间 $T$ , 分别预处理两组蚂蚁之间的间距, 我们就可以通过二分(或者其他办法?)得出宝石被抢夺的次数, 然后根据次数推出宝石在那只蚂蚁手中, 就解决了这道题了.

注意最初始第一只蚂蚁没有从任何其它蚂蚁手中抢得宝石(是我们放置的), 故要特判一下.

时间复杂度 $\mathcal O(n+\log n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, L, T;
int M(int x) { return x >= L ? x - L : x; }
int x[200005], dire[200005], q[2];
int res[200005];
vector<int> p[2];

int tmp;
int to(int a) {
    int rt = M((x[a] + (dire[a] ? 1 : -1) * T) % L + L);
    rt += L - tmp;
    return rt > L ? rt - L : rt;
}

bool cmp(int a, int b) { return b == 1 ? 0 : (a > b || a == 1); }

int dis(int a, int b) { return M((x[b] - x[a]) * (dire[a] ? 1 : -1) + L); }

int pre[2][200005];

long long calc(int i, int j) {
    return 1ll * pre[i][q[i] - 1] * (j / q[i]) +
           (j % q[i] ? pre[i][j % q[i] - 1] : 0);
}

int solve() {
    int t;
    if (!p[1].size() || (t = 2 * T - dis(1, p[1][0])) <= 0) return 1;
    for (int i = 0; i < 2; ++i) {
        if ((q[i] = p[i].size()) == 1) {
            pre[i][0] = L;
            continue;
        }
        for (int j = 0; j < q[i] - 1; ++j)
            pre[i][j] = dis(p[i][j + 1], p[i][j]);
        pre[i][q[i] - 1] = dis(p[i][0], p[i][q[i] - 1]);
        for (int j = 0; j < q[i]; ++j) pre[i][j] += pre[i][j - 1];
    }
    int l = 0, r = 1000000000, rs = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        long long len = calc(0, (mid >> 1) + (mid & 1)) + calc(1, mid >> 1);
        if (len <= t)
            l = mid + 1, rs = mid;
        else
            r = mid - 1;
    }
    rs = (rs & 1) ? p[0][((rs >> 1) + 1) % q[0]] : p[1][(rs >> 1) % q[1]];
    return rs;
}

int main() {
    n = read(), L = read(), T = read();
    for (int i = 1; i <= n; ++i)
        x[i] = read(), dire[i] = read() & 1, p[dire[i] ^ dire[1]].push_back(i);
    if (dire[1])
        sort(p[0].begin(), p[0].end(), cmp), sort(p[1].begin(), p[1].end());
    else
        sort(p[0].begin(), p[0].end()), sort(p[1].begin(), p[1].end(), cmp);
    int st = solve();
    tmp = to(st);
    for (int i = 1; i <= n; ++i) res[i] = to(i);
    res[st] = 0, sort(res + 1, res + 1 + n);
    for (int i = 1; i <= n; ++i) printf("%d\n", M(res[i] + tmp));
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：Hilaria (赞：1)

经过我们反复模拟，看这些蚂蚁撞来撞去，我们可以发现（下文所有 ```编号``` 指输入时的序号，题目很良心，蚂蚁是按照位置从小到大给我们的）：

- 两只蚂蚁碰撞可以看作是这两只蚂蚁穿过了对方，编号交换。所以每只蚂蚁如果无视碰撞这条规则，直接顺时针（或逆时针）走 $T$ 秒之后的位置，肯定是这 $n$ 只蚂蚁中任意一只的最终位置。

- 蚂蚁们的**相对位置**是不变的，因为每只蚂蚁都是在**相邻**之间撞来撞去，所以它们撞完之后，一号蚂蚁顺时针往后一只蚂蚁一定还是二号蚂蚁，二号蚂蚁顺时针往后一只蚂蚁一定还是三号蚂蚁，所以其实我们只要求出一号蚂蚁最后的位置，剩下的所有蚂蚁的位置也都可以知道了。

所以综上所述，我们已经知道所有蚂蚁的最终位置（只是不知道每个位置对应的是哪个编号的蚂蚁），然后我们只要算出一号蚂蚁的最终位置，我们就能把所有位置对应上了。

因为是在一个环上吗，那我们设置一个 $0$ 为蚂蚁运动的“基点”。

那其实就有三种情况会影响一号蚂蚁最后的位置：

- 有蚂蚁和一号蚂蚁相撞，位置贡献为 $\pm1$。（非一号蚂蚁相撞时对一号蚂蚁的位置没有影响）

- 有非一号蚂蚁穿过“基点”，位置贡献为 $\pm1$。（有非一号蚂蚁顺时针穿过基点的话，一号蚂蚁前面就多了一只蚂蚁，位置就要 $+1$，反之则 $-1$）

- 一号蚂蚁穿过基点，影响为 $\pm(n-1)$。

这看似十分清晰明了，但是，怎么实现啊，这就很容易把自个绕进去。

还记得**蚂蚁们的相对位置是不变的**吗，所以其实我们根本不用考虑蚂蚁相撞的贡献，我们只需要看一号蚂蚁前面又多了几只亦或是少了几只蚂蚁，那确实就是看每只蚂蚁穿过基点的次数，然后把一号蚂蚁的位置按贡献算出来就行了！！

所以这题就变成了《一滴水经过丽江》，选自八下语文课本。

啊不是，是《一只蚂蚁穿过基点》，选自洛谷题库。

- 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX=1e5+10;

int n,l,t,cnt;
int ans[MAXX];
int main()
{
	cin>>n>>l>>t;
	for(int i=0;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		if(b==1) a+=t;
		else a-=t;
		cnt=((cnt+(int)floor(1.0*a/l))%n+n)%n;		//算第一只蚂蚁的位置
		ans[i]=(a%l+l)%l;
	}
	sort(ans,ans+n);
	for(int i=0;i<n;i++) cout<<ans[(cnt+i)%n]<<endl;

	return 0;
}
```


```cnt=((cnt+(int)floor(1.0*a/l))%n+n)%n;```

这个向下取整如果它是负数时，如 $-0.7$ 取的是 $-1$，所以不会错。








---

## 作者：Honor誉 (赞：0)


其实，这题有一个弱化版，那题并不要求按蚂蚁顺序输出，只用从小到大输出有蚂蚁的位置即可。

那题解题的关键在于相遇时的掉头相当于直接穿过去了（因为不要求编号），那这题中的相遇就相当于交换了编号罢了。

所以蚂蚁们T秒后的位置我们可以非常简单地算出来，只是不知道哪一个位置对应哪一只蚂蚁。

所以我们就算出一号蚂蚁在T秒后的Rank，照着Rank输出即可。

我们以一只蚂蚁为标准，每有一只蚂蚁倒着穿过它，Rank--，正着穿过它，Rank++。

接下来，按顺序输出即可。

### 注意：这里的负数如果不被$l$整除，实际上他是多转了一圈的，要再次$--$

```cpp
#include<bits/stdc++.h>
#define N 1000010
using namespace std;
struct data
{
	int x,w;
}a[N];
bool cmp(data a,data b)
{
	return a.x<b.x;
}
int n,l,t,sum;
int main()
{
	scanf("%d%d%d",&n,&l,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].w);
		a[i].w--;
	}
	for(int i=1;i<=n;i++)
	{
		if(!a[i].w)
		{
			a[i].x+=t;
		}else{
			a[i].x-=t;
		}
		sum+=a[i].x/l;//计算第1只蚂蚁的Rank
		if(a[i].x%l<0)//这里减少了（是负数，但不整除），要再减一次
		{
			sum--;
		}
		a[i].x=(a[i].x%l+l)%l;
	}
	sort(a+1,a+n+1,cmp);
	sum=(sum%n+n)%n;
	for(int i=sum+1;i<=n;i++)
	{
		printf("%d\n",a[i].x);
	}
	for(int i=1;i<=sum;i++)
	{
		printf("%d\n",a[i].x);
	}
	return 0;
}
```

---

