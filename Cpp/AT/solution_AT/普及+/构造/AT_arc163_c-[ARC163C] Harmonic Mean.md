# [ARC163C] Harmonic Mean

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc163/tasks/arc163_c

以下の条件を全て満たす長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ が存在するか判定し、存在するならば一つ構築してください。

- $ \sum_{i=1}^{N}\ \frac{1}{A_i}\ =\ 1 $
- $ A $ の要素は全て相異なる。
- $ 1\ \le\ A_i\ \le\ 10^9(1\ \le\ i\ \le\ N) $
 
$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 500 $
- $ 1\ \le\ N\ \le\ 500 $
 
### Sample Explanation 1

$ 1 $ 個目のテストケースでは、$ N=3 $ です。 $ A=(2,3,6) $ は、$ \frac{1}{2}\ +\ \frac{1}{3}\ +\ \frac{1}{6}\ =\ 1 $ かつ他の条件も全て満たすため正当です。 $ 2 $ 個目のテストケースでは、$ N=5 $ です。 $ A=(3,4,5,6,20) $ は、$ \frac{1}{3}\ +\ \frac{1}{4}\ +\ \frac{1}{5}\ +\ \frac{1}{6}\ +\ \frac{1}{20}\ =\ 1 $ かつ他の条件も全て満たすため正当です。 例えば、$ A=(5,5,5,5,5) $ は、$ 1,3 $ 個目の条件を満たしていますが同じ要素が存在するため不適であることに注意してください。

## 样例 #1

### 输入

```
2
3
5```

### 输出

```
Yes
2 3 6 
Yes
3 4 5 6 20```

# 题解

## 作者：syzxzqy (赞：7)

[原题传送门](https://www.luogu.com.cn/problem/AT_arc163_c)  
#### 题目意思  
题目需要求出 $n$ 个不同的分数单位和为 $1$ 的任意解。  
#### 题目思路  
我们可以把 $n$ 分为三种情况：  
- 情况一：$n=1$，有解，且答案为 $a_1=1$
- 情况二：$n=2$，无解。
- 情况三：$n>2$，有解。  

对于情况一、二，我们很好判断。  
对于情况三答案可能多解，我们选用一个较为容易求得的解。  
对于一个分数单位，我们可以拆分成以下等式：  
$\cfrac{1}{n}=\cfrac{1}{n+1}+\cfrac{1}{n(n+1)}$  
由 $n=3$ 时，$1=\cfrac{1}{2}+\cfrac{1}{3}+\cfrac{1}{6}$ 开始拆分，用一个小根堆记录所有数，每一次取最小数拆分（因为分大的容易爆，不想打高精度就拆分小的）。  
因为 $\cfrac{1}{n}=\cfrac{1}{n+1}+\cfrac{1}{n(n+1)}$ 中可能拆分会有重复，我们建立一个数组，记录每个不能拆分的数。  
因为 $\cfrac{1}{2}=\cfrac{1}{3}+\cfrac{1}{6}$ 会和 $\cfrac{1}{3}$、$\cfrac{1}{6}$ 重复，所以直接把 $2$ 放入 $a$ 数组中，做后面的。  
接下来对于小根堆中每一个数，首先取出并保存至变量 $x$，接着删除，求出现在的最小，判断当前数拆分会不会重复，如果重复就保存到 $a$ 数组中，否则在小根堆里加入 $x+1$，$x\times (x+1)$，直到分母总数有 $n$ 个。  
因为 $x$ 是一定变成 $x+1$ 和 $x\times (x+1)$ 或不变的，所以最终答案最大值不会超过 $n\times (n+1)$。
#### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=1e3+10;
int T,n,t,x,x1,x2,s,i,a[N];
priority_queue<int,vector<int>,greater<int> > q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		if(n==1){cout<<"Yes\n1\n";continue;}//注意输出末尾还有换行，否则就像作者本人一样错了几遍才发现
		if(n==2){cout<<"No\n";continue;}//特判
		cout<<"Yes\n";
		a[t=1]=2;q.push(3);q.push(6);//将2加入表示无法拆分的数组，在小根堆加入3、6
		for(i=1;i<=n-3;){//已经有三个数了，还要求出n-3个数
			x=q.top();q.pop();//保存并删除
			if(q.top()==x+1) {a[++t]=x;;continue;}//如果拆分会重复，就加入a数组，个数不变
			x1=x+1;x2=x*(x+1);
			q.push(x1);q.push(x2);++i;//加入新的分母，个数多了1个
		}
		while(t--) q.push(a[t+1]);//偷懒，直接将无法拆分的数加入小根堆，方便从小到大输出
		while(!q.empty()) cout<<q.top()<<" ",q.pop();//从小到大输出
		cout<<"\n";
	} 
}
```


---

## 作者：EuphoricStar (赞：6)

这题是不是想到裂项就会了![](//图.tk/i)但是我赛时没想到![](//图.tk/h)

下面复读 [Ender32k 做法](https://www.luogu.com.cn/blog/Ender32k/arc163c-dian-zhong-dian-zhi-zhu-zhu-chi-da-bian-mu-xing-yu-lie-xiang)。

根据 $\frac{1}{i(i + 1)} = \frac{1}{i} - \frac{1}{i + 1}$，可以构造 $\frac{1}{2}, \frac{1}{6}, ..., \frac{1}{(n - 1)n}, \frac{1}{n}$。但是如果存在正整数 $t$ 使得 $t(t + 1) = n$ 那就寄了，因为会重。

于是我们把 $\frac{1}{n}$ 和 $\frac{1}{t(t + 1)}$ 合并变成 $\frac{1}{\frac{t(t + 1)}{2}}$，把 $\frac{1}{(n - 1)n}$ 变成 $\frac{1}{\frac{3(n - 1)n}{2}}, \frac{1}{3(n - 1)n}$ 即可。

但是 $n = 12, 420$ 时 $\frac{1}{\frac{t(t + 1)}{2}}$ 还可以跟前面的继续合并，因此要特判。

[code](https://atcoder.jp/contests/arc163/submissions/43200713)

---

## 作者：robinyqc (赞：4)

讲一种用 set+贪心 预处理的做法。

这题的关键就是单位分数 $\dfrac 1a$ 等于 $\dfrac 1{a+1}+\dfrac1{a(a+1)}$。因此任何一个大小为 $n$ 的集合总可以扩展成一个大小为 $n+1$ 的集合。因为 $1=\dfrac12+\dfrac13+\dfrac16$，因此对于所有 $n\geq 3$ 都可以从 $\{2,3,6\}$ 经过若干次拆分得到。

考虑贪心。每次选一个最大的分数（也就是分母最小的），然后把它按照刚才所说的拆开即可。选最大是因为要保证数列分母最大值增长最慢，尽量使他小于等于 $10^9$。

当然你会发现有时候拆最大的分数可能在数列中已经存在，与题意不符。那我不拆就完了。拆下一个呗。可以发现重复的实在不多，预估序列最大的数不超过 $n^3$。写完程序跑一下程序发现序列中最大的数就是 $246512$。

预处理部分（核心代码），复杂度 $O(n^2 \log n)$：

```cpp
set<int> ans[501];

void pret() {
    ans[3].insert({2,3,6}); // 基础集合
    for(int i=3;i<500;i++) {
        int x;
        for(int j:ans[i]) if(!ans[i].count(j+1)&& // 找到拆开没有重的数
            !ans[i].count(j*(j+1))) {x=j; break;}
        for(int j:ans[i]) if(j!=x) ans[i+1].insert(j); // 其它保持原样
        ans[i+1].insert(x+1); // 拆分成两个新分数
        ans[i+1].insert(x*(x+1)); // 拆分成两个新分数
    }
}
```

注意特判一下 $n=1$ 和 $n=2$ 的情况。

---

## 作者：rui_er (赞：3)

没想出来什么优美的解法，来个乱搞。

特判平凡情况 $n\le 2$，其中 $n=1$ 显然有 $1=\frac{1}{1}$，$n=2$ 无解。

众所周知 $1=\frac{1}{2}+\frac{1}{4}+\frac{1}{8}+\cdots+\frac{1}{2^k}+\frac{1}{2^k}$。注意到公式中除了 $\frac{1}{2^k}$ 有重复外，其余项均无重复。容易想到将其中一个 $\frac{1}{2^k}$ 拆成 $1:2$ 的两部分，即 $\frac{1}{2^k}=\frac{1}{2^{k-1}\times 3}+\frac{1}{2^k\times 3}$。此时的项数 $n=k+2$，要使得分母不超过 $10^9$，可以解决 $n\le 30$ 的问题。

例如：

- $1=\frac{1}{2}+\frac{1}{2}=\frac{1}{2}+\frac{1}{3}+\frac{1}{6}$。
- $1=\frac{1}{2}+\frac{1}{4}+\frac{1}{4}=\frac{1}{2}+\frac{1}{4}+\frac{1}{6}+\frac{1}{12}$。

尝试将上面的做法推广，使得其不仅能做 $n\le 30$，还能做 $n\le 500$。首先，我们写出 $1=\frac{1}{2}+\frac{1}{4}+\frac{1}{8}+\cdots+\frac{1}{2^{28}}+\frac{1}{2^{27}\times 3}+\frac{1}{2^{28}\times 3}$。我们维护两个集合 $bases$ 和 $ans$，其中 $bases$ 是可以继续拆的分母的集合（见下文），$ans$ 是答案的分母的集合。

那么，当 $|ans| < n$ 时，我们重复执行：

1. 从 $bases$ 中取出最大的分母 $u$（感受一下就会发现最大的比最小的更优），并从 $bases$ 中删除。
2. 如果 $2\mid u$，且分母 $\frac{3}{2}u$ 和 $3u$ 不在 $ans$ 中且不超过 $10^9$，就可以把 $u$ 拆成 $\frac{3}{2}u$ 和 $3u$，加入 $bases$ 和 $ans$ 中。

发现这么做完之后，$|ans|$ 只能达到 $200$，也就是说只能解决 $n\le 200$ 的问题。

这样就没办法了吗？当然不是。既然开始乱搞了，就要把乱搞贯彻到底。

3. 否则如果 $3\mid u$，且分母 $\frac{4}{3}u$ 和 $4u$ 不在 $ans$ 中且不超过 $10^9$，就可以把 $u$ 拆成 $\frac{4}{3}u$ 和 $4u$，加入 $bases$ 和 $ans$ 中。

发现这么做完之后，$|ans|$ 只能达到 $276$，也就是说只能解决 $n\le 276$ 的问题。

4. 否则如果 $4\mid u$，且分母 $\frac{5}{4}u$ 和 $5u$ 不在 $ans$ 中且不超过 $10^9$，就可以把 $u$ 拆成 $\frac{5}{4}u$ 和 $5u$，加入 $bases$ 和 $ans$ 中。

发现这么做完之后，$|ans|$ 已经足够 $500$ 了！其准确值为 $|ans|=1317$。

于是做完了。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

ll T, n;

int main() {
    for(scanf("%lld", &T); T; T--) {
        scanf("%lld", &n);
        if(n == 1) {
            puts("Yes\n1");
            continue;
        }
        if(n == 2) {
            puts("No");
            continue;
        }
        if(n <= 30) {
            puts("Yes");
            rep(i, 1, n-2) printf("%lld ", 1LL << i);
            printf("%lld %lld\n", (1LL << (n - 2)) * 3, (1LL << (n - 3)) * 3);
            continue;
        }
        set<ll> bases;
        rep(i, 1, 28) bases.insert(1LL << i);
        bases.insert((1LL << 28) * 3);
        bases.insert((1LL << 27) * 3);
        set<ll> ans = bases;
        while(!bases.empty() && (ll)ans.size() < n) {
            ll u = *bases.rbegin();
            bases.erase(u);
            if(u % 2 == 0 && u * 3 <= 1000000000 && !ans.count(u * 3) && !ans.count(u / 2 * 3)) {
                bases.insert(u * 3);
                bases.insert(u / 2 * 3);
                ans.erase(u);
                ans.insert(u * 3);
                ans.insert(u / 2 * 3);
            }
            else if(u % 3 == 0 && u * 4 <= 1000000000 && !ans.count(u * 4) && !ans.count(u / 3 * 4)) {
                bases.insert(u * 4);
                bases.insert(u / 3 * 4);
                ans.erase(u);
                ans.insert(u * 4);
                ans.insert(u / 3 * 4);
            }
            else if(u % 4 == 0 && u * 5 <= 1000000000 && !ans.count(u * 5) && !ans.count(u / 4 * 5)) {
                bases.insert(u * 5);
                bases.insert(u / 4 * 5);
                ans.erase(u);
                ans.insert(u * 5);
                ans.insert(u / 4 * 5);
            }
        }
        puts("Yes");
        for(ll i : ans) printf("%lld ", i);
        puts("");
    }
    return 0;
}
```

---

## 作者：_Ad_Astra_ (赞：2)

讲一个与大多数做法不大一样的想法。

~~由多年前学过的小学奥数可知~~，要想构造满足条件的答案，可以考虑**裂项相消**。具体地，利用 $\frac{1}{n}-\frac{1}{n+1}=\frac{1}{n(n+1)}$，对于每个数 $n$，不难想到有一种构造方法为 $\frac{1}{1\times2}+\frac{1}{2\times3}+\cdots+\frac{1}{(n-1)\times n}+\frac{1}{n}$。证明也很简单，将每一项拆开，则原式为 $1-\frac{1}{2}+\frac{1}{2}-\frac{1}{3}+\cdots+\frac{1}{n-1}-\frac{1}{n}+\frac{1}{n}$。

那么这样就满足题意了吗？显然不。当 $n = k(k+1)$ 的时候就会出问题，这时候 $\frac{1}{k(k+1)}$ 就会出现两次。比如 $n=6$ 时的构造就是 $\frac{1}{2}+\frac{1}{6}+\frac{1}{12}+\frac{1}{20}+\frac{1}{30}+\frac{1}{6}$，出现了重复。

这时我们可以考虑：能否在 $n-1$ 的情况下进行某些操作变成 $n$ 的构造？这时我们可以考虑构造 $n-1$ 时的第 $n-2$ 个数 $\frac{1}{(n-2)(n-1)}$，再次运用前面的式子将其拆开，得到 $\frac{1}{(n-2)(n-1)+1}+\frac{1}{(n-2)(n-1)[(n-2)(n-1)+1]}$，这样就不会重复了。例如对于 $n=6$ 时，构造出来就是 $\frac{1}{2}+\frac{1}{6}+\frac{1}{12}+\frac{1}{21}+\frac{1}{420}+\frac{1}{5}$。

但是这样还是有个问题：由于 $n \le 500$，因此可能会出现超过上界的情况。比如当 $n=500$ 时，最大的一个分母就是 $(500-2)\times(500-1)\times[(500-2)\times(500-1)+1]=61,753,492,506$，远远大于 $10^9$。

这时我们想到，我们不一定要选取 $\frac{1}{(n-2)(n-1)}$ 进行拆分，只要满足不出现重复即可。比如在本题中就可以取 $\frac{1}{24\times 25}$（当然也可以取别的不会出现冲突的数），这样拆出来的最大分母为 $360600$，符合要求。

**注意，当 $n=2$ 时不难证明是无解的，一定要特判！**（作者本人就是因为忘了特判而一直挂了一个点，最后没在赛中写出痛失 10+rating）

当然这题也有其他简单的做法，具体可以参照其他的题解。

时间复杂度 $O(n)$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
void solve()
{	
	cin>>n;
	if(n==2)
	{
		cout<<"No"<<endl;
		return;
	}
	for(int i=1;i*i<=n;i++)
		if(i*(i+1)==n)
		{
			cout<<"Yes"<<endl;
			int d;
			d=min(n-2,24LL);
			for(int j=1;j<d;j++)cout<<j*(j+1)<<' ';
			cout<<n-1<<' '<<d*(d+1)+1<<' '<<d*(d+1)*(d*(d+1)+1)<<" ";
			for(int j=d+1;j<=n-2;j++)cout<<j*(j+1)<<" ";
			cout<<endl;
			return;
		}
	cout<<"Yes"<<endl;
	for(int i=1;i<n;i++)cout<<i*(i+1)<<' ';
	cout<<n<<endl;
	return;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Leasier (赞：1)

先来讲讲赛后两分钟 AC 的神必做法（

首先判掉 $n = 2$ 无解。

考虑先将 $\frac{1}{1}$ 放进一个可重集里，每次取出可重集中没讨论过且最大的 $\frac{1}{x}$（如果出现了重复的数，将其视为两两不同并以任意顺序讨论）：

- 若答案数组大小 $< n$ 且 $x + 1, x(x + 1)$ 都没在可重集中出现，则删去一个 $\frac{1}{x}$，然后把 $\frac{1}{x + 1}, \frac{1}{x(x + 1)}$ 放进可重集。
- 否则，把 $\frac{1}{x}$ 从可重集中删去并加入答案。

循环到可重集为空后输出答案即可。$n = 500$ 时输出的最大数为 $267806$，符合题目要求。

------------

下面是非常需要脑子的小学奥数做法！！！

~~其实原理跟上面的一样，都是裂项（~~

考虑一个小学奥数中常见的裂项结论：$\displaystyle\sum_{i = 1}^{n - 1} \frac{1}{i(i + 1)} = 1 - \frac{1}{n}$。

将其移项后即可得到一组解。

但是若 $n$ 可以表示为 $m \in N^*, n = m(m + 1)$，我们发现 $\frac{1}{n}$ 会在前面出现。

此时我们发现 $n - 1$ 一定不能这样表示，于是先拆出一个 $\frac{1}{2}$，然后用 $\displaystyle\sum_{i = 1}^{n - 2} \frac{1}{2i(i + 1)} = \frac{1}{2} - \frac{1}{2(n - 1)}$ 构造剩下 $n - 1$ 个数即可。

代码：
```cpp
#include <stdio.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n;
		scanf("%d", &n);
		if (n == 2){
			printf("No\n");
			continue;
		}
		int m = -1;
		for (int j = 1; ; j++){
			int t = j * (j + 1);
			if (t == n){
				m = j;
				break;
			}
			if (t > n) break;
		}
		printf("Yes\n");
		if (m == -1){
			for (int j = 1; j < n; j++){
				printf("%d ", j * (j + 1));
			}
			printf("%d\n", n);
		} else {
			int nd = n - 1;
			printf("2 ");
			for (int j = 1; j < nd; j++){
				printf("%d ", 2 * j * (j + 1));
			}
			printf("%d\n", nd * 2);
		}
	}
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：1)

$n=1$ 时输出 $1$，$n=2$ 时无解，以上两种情况下文不考虑。

首先需要知道一个我比赛结束前三分钟想到的常识：$\frac{1}{k}=\frac{1}{k+1}+\frac{1}{k(k+1)}$。

然后就可以得到 $\sum_{i=2}^n \frac{1}{i(i-1)} +\frac{1}{n}=1$。

但是，若 $\exists i\in \operatorname{R},n=i(i-1)$。

那么就不行了。

但是 $\sum_{i=2}^n \frac{1}{2i(i-1)} +\frac{1}{2n}=\frac{1}{2}$。

那么 $sum_{i=2}^{n-1} \frac{1}{2i(i-1)} +\frac{1}{2n-2}+\frac{1}{2}=1$。

解决！

Code:

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		if(n==1)
		{
			cout<<"Yes\n"<<"1\n";
			continue;
		}
		if(n==2)
		{
			cout<<"No\n";
		   continue;
		}
		cout<<"Yes\n";
		for(int i=2;;i++)
		{
			int s=i*(i-1);
			if(s>n)
			{
				for(int j=1;j<n;j++)cout<<j*(j+1)<<' ';
				cout<<n<<'\n';
				break;
			}
			if(s==n)
			{
				cout<<"2 ";
				for(int j=2;j<n;j++)cout<<2*j*(j-1)<<' ';
				cout<<2*n-2<<'\n';
				break;
			}
		}
	}
}
```

---

## 作者：Raisetsu41 (赞：0)

~~我是肯尼迪，我脑洞非常大。~~  
有个东西叫裂项相消，就是说 $1 + \sum_{i = 2}^{n} \left(-\frac{1}{i} + \frac{1}{i}\right) = 1$，换个写法 $\frac{1}{2} + \sum_{i = 2}^{n - 1} \left(\frac{1}{i} - \frac{1}{i + 1}\right) + \frac{1}{n} = 1$，于是这道题就会做了。  
然后这样就会 WA，比如对于 $n = 6$ 会得到如下方案 $2, 6, 12, 20, 6$，出现了两个 $6$。显然不对。  
如何避免呢？对于 $n = (i + 1)i$ 的形式，可以先拆一个 $2$ 出来，然后再裂项一下凑出剩下的 $\frac{1}{2}$ 即可。 

```cpp
/*
If the radiance of a thousand suns were to burst into the sky?
...that would be like the splendor of the mighty one.
*/
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx2,fma")
#include <map>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define LL long long
#define ULL unsigned long long
using namespace std;

template <typename T>
inline void read(T& x) {
  x = 0; int f = 1; char c = getchar(); while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
  while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); } x *= f;
}
template <typename T, typename... Args>
inline void read (T &x, Args&... Arg) { read (x), read (Arg...); }
template <typename T>
inline T Abs(T x) { return x < 0 ? -x : x; }
template <typename T>
inline T Max(T x, T y) { return x > y ? x : y; }
template <typename T>
inline T Min(T x, T y) { return x < y ? x : y; }

int t, n;
vector<LL> res;

int main() {

  read(t);
  for (int cas = 1; cas <= t; cas++) {

    bool flag = true;
    read(n), res.clear();

    if (n == 2) { printf("No\n"); continue; }

    for (int i = 1; i <= n; i++) if (i * (i + 1) == n) { flag = false; break; }
    if (!flag) {
      printf("Yes\n%d ", 2);
      for (int i = 1; i < n - 1; i++) printf("%d ", i * (i + 1) * 2);
      printf("%d\n", 2 * (n - 1));
      continue;
    }

    for (int i = 1; i < n; i++) res.push_back((i + 1) * i);
    res.push_back(n);
    sort(res.begin(), res.end());
    printf("Yes\n");
    for (int i : res) printf("%d ", i);
    printf("\n");

  }

  return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 思路

想到这两个字构造就简单了：**裂项**！（虽然的确挺难想，我的第一感是 $\frac{1}{2}+\frac{1}{4}+\frac{1}{8}+\cdots+\frac{1}{2^k}+\frac{1}{2^k}=1$。但你要注意，你构造的 ${A_N}$ 是指数的增长，太快了！然后你应当考虑将幂变为乘积进行尝试，就能想到了。）

裂项的基本式子 $\frac{1}{i(i+1)}=\frac{1}{i}-\frac{1}{i+1}$，移项后就可以用于拆分 $\frac{1}{i}=\frac{1}{i+1}+\frac{1}{i(i+1)}$。我们用两个从小到大排序的 ``priority_queue`` 分别维护正在进行拆分的数字和不再进行拆分的数字（注意初始化可以根据 $n=3$ 时的情况，让 $2$ 不再拆分，让 $3$ 和 $6$ 继续进行拆分），并用一个 ``map`` 维护是否被取过。每次取出正在拆分的数字中最小的进行裂项（注意判断 $i(i+1)$ 是否超过 $10^9$ 以及两数之前是否被取过），直到两容器元素个数和恰好为 $N$ 时停止。

经计算 $3\le N\le 500$ 都有解。

最后注意 $n$ 较小时特判下。

## 代码

放上主要代码：

```cpp
void solve(){
    ll n=read();
    if(n==1){
	cout<<"Yes"<<endl<<1<<endl;
	return;
    }
    if(n==2){
	cout<<"No"<<endl;
	return;
    }
    if(n==3){
	cout<<"Yes"<<endl<<2<<" "<<3<<" "<<6<<endl;
	return;
    }
    cout<<"Yes"<<endl;
    priority_queue<int,vector<int>,greater<int> >pq,a;
    map<int,bool>mp;
    a.push(2);
    pq.push(3);
    pq.push(6);
    mp[3]=mp[6]=1;
    while(a.size()+pq.size()<n){
	ll x=pq.top();
	pq.pop();
	if(x*(x+1)>1e9||mp[x+1]||mp[x*(x+1)])a.push(x);
	else{
	    pq.push(x+1);
	    pq.push(x*(x+1));
	    mp[x+1]=mp[x*(x+1)]=1;
	}
    }
    while(!pq.empty()){
	int x=pq.top();
	pq.pop();
	a.push(x);
    }
    while(!a.empty()){
	int x=a.top();
	cout<<x<<" ";
	a.pop();
    }
    cout<<endl;
    return;
}
```


---

## 作者：DE_aemmprty (赞：0)

## 1 题目大意

### 1.1 题目翻译

给你一个 $n$，你需要构造一组大小为 $n$ 的数组 $\{a_i\}$，使得：

- $\sum_{i = 1}^n\frac{1}{a_i} = 1$

- $a$ 数组内的元素互不相同

- $1 \leq a_i \leq 10^9$

有 $t$ 组数据。

### 1.2 数据范围

对于 $100\%$ 的数据：

- $1 \leq n \leq 500$

- $1 \leq t \leq 500$

## 2 解法分析

### 2.0 前情提要

做这道题之前，你至少要想到 $\frac{1}{n}-\frac{1}{n+1} = \frac{1}{n \times (n + 1)}$，不然别搞 OI 了。~~自己骂自己是吧~~

### 2.1 题目解法

首先，$n = 1$ 有 $a = \{1\}$，$n = 2$ 无解。十分显然。接下来考虑 $n > 3$ 的情况。

由上面的式子得 $\frac{1}{n\times(n + 1)} + \frac{1}{n + 1} = \frac{1}{n}$，容易想到构造出 $a = \{2, 6, \cdots, n \times (n - 1), n\}$。此时，$a$ 满足前两条要求。

但是第三条不一定。因为这个 $n$ 可能是 $k \times (k + 1)$ 的形式，很烦。所以，考虑单独处理 $n = k \times (k + 1)$。

接下来这一步很考验人的构造能力。既然 $n$ 不好构造，我们就可以尝试把 $n$ 变成 $n-1$。这时，可以设 $a' = \{2, 2 \times a_1, 2 \times a_2, \cdots, 2 \times a_{n - 1}\}$。这时，我们把问题的规模缩小到了 $n - 1$，显然 $n - 1 \neq k \times (k + 1)$。这个序列的证明也十分显然，这里不过多叙述。

至此，问题得解。

## 3 AC Code

```cpp
void solve() {
    n = read();
    if (n == 1) { // 特判 1
        printf("Yes\n1\n");
        return ;
    }
    if (n == 2) { // 特判 2
        printf("No\n");
        return ;
    }
    /*判断 n 是否为形如 k * (k + 1) 的数*/
    int k = 1;
    while (k * (k + 1) < n)
        k ++;
    if (k * (k + 1) != n) { // 不是，则 a = {2, 6, ..., n * (n - 1), n}
        printf("Yes\n");
        f (i, 1, n - 1)
            printf("%lld ", i * (i + 1));
        printf("%lld\n", n);
    }
    else { // 是，则 a = {2, 4, 12, ..., 2 * (n - 2) * (n - 1), 2 * n - 2}
        printf("Yes\n2 ");
        f (i, 1, n - 2)
            printf("%lld ", 2 * i * (i + 1));
        printf("%lld\n", 2 * n - 2);
    }
}
```

---

## 作者：Phartial (赞：0)

核心 idea 在于 $\dfrac{1}{n}-\dfrac{1}{n+1}=\dfrac{1}{n(n+1)}$ 这个式子。

由小学奥数，我们知道：

$$
\begin{aligned}
\sum_{i=1}^{n-1}\frac{1}{i(i+1)}
&=\sum_{i=1}^{n-1}\frac{1}{i}-\frac{1}{i+1}\\
&=1+(\sum_{i=2}^{n-1}-\frac{1}{i}+\frac{1}{i})-\frac{1}{n}\\
&=1-\frac{1}{n}
\end{aligned}
$$

于是我们就可以把 $1$ 表示成 $\dfrac{1}{1\times 2}+\dfrac{1}{2\times 3}+\cdots+\dfrac{1}{n(n-1)}+\dfrac{1}{n}$ 的形式。

但当 $n=k(k+1)\quad(k\in\mathbb{Z})$ 时，$\dfrac{1}{n}$ 会和之前的 $\dfrac{1}{k(k+1)}$ 重复。于是我们考虑 $n-1$ 时的解，它为 $\dfrac{1}{1\times 2}+\dfrac{1}{2\times 3}+\cdots+\dfrac{1}{(n-1)(n-2)}+\dfrac{1}{n-1}$，但这只有 $n-1$ 项，我们选出其中除最后一项外的任意一项 $\dfrac{1}{p(p+1)}$，将它用 $\dfrac{1}{n}=\dfrac{1}{n(n+1)}+\dfrac{1}{n+1}$ 这个式子裂项成 $\dfrac{1}{p^2+p+1}+\dfrac{1}{p(p+1)(p^2+p+1)}$ 即可。只需要保证 $p^2+p+1> (n-1)(n-2)$ 且 $p(p+1)(p^2+p+1)\le 10^9$ 即可，我取的是 $p=\min(n-2,100)$。

注意特判 $n=2$ 的情况。

```cpp
#include <cmath>
#include <iostream>

using namespace std;

int t, n;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n;
    if (n == 2) {
      cout << "No\n";
      continue;
    }
    cout << "Yes\n";
    int q = sqrt(n);
    if (q * (q + 1) == n) {
      int p = min(n - 2, 100);
      for (int i = 1; i <= n - 2; ++i) {
        if (i != p) {
          cout << i * (i + 1) << ' ';
        }
      }
      int v = p * (p + 1);
      cout << v + 1 << ' ' << v * (v + 1) << ' ' << n - 1 << '\n';
    } else {
      for (int i = 1; i < n; ++i) {
        cout << i * (i + 1) << ' ';
      }
      cout << n << '\n';
    }
  }
  return 0;
}
```


---

## 作者：Schi2oid (赞：0)

我们充分发扬人类智慧：

不难发现 

$$

\frac{1}{xy}=\frac{y+1}{xy(y+1)}=\frac{1}{xy(y+1)}+\frac{1}{x(y+1)}

$$

根据数学直觉，在按上式随机分裂当前序列中的一个数后，新产生的两个数在序列中肯定不会太容易已经出现

所以我们只需要首先找到一个长度为 $3$ 的初始序列 $[2,3,6]$，不断尝试分裂直到序列长度变为 $500$ 即可处理出答案

这样速度快得飞起，在 $n=500$ 时都可以在 44ms 内卡过


---

## 作者：引领天下 (赞：0)

题意：

构造 $n$ 个**互不相同**的 $1\le a_i\le10^9$ 使得 $\sum_{i=1}^{n}{\frac1{a_i}}=1$。若有解，则输出 `Yes`，然后输出任意一组解；否则输出 `No`。

做法：

人类智慧题。

首先盘一下 $n$ 比较小的情况。

$n=1$ 时做法显然。

$n=2$ 显然是无解的。

$n=3$ 是第一组样例。

注意到 $n\le500$，这个范围让人意识到或许构造的复杂度可以是 $n^2$ 甚至 $n^3$，而且打动态表之后也可以存的下。那我们或许可以考虑预处理之后直接回答询问。

一个非常 naive 的想法是从 $n-1$ 到 $n$ 递推，将 $n-1$ 构造的所有 $a_i$ 乘二，这样 $\sum_{i=1}^{n-1}{\frac1{a_i}}=\frac12$，最后补一个 $a_n=2$ 就可以直接完成构造。

~~然后我兴冲冲的交了，很愉快地吃了一发罚时。~~

思考为什么寄了：在我们的这个构造下，$a_i$ 每次乘二，最后能达到 $2^n$ 的级别，$10^9$ 的范围早不知道炸到哪去了。

那我们考虑换一个构造：

众所周知 $\frac1{n(n+1)}=\frac1n-\frac1{n+1}$，那么我们可以依据这个写出一个式子：

$\sum_{i=1}^{n-1}{\frac1{i(i+1)}}=\sum_{i=1}^{n-1}{(\frac1i-\frac1{i+1})}=1-\frac1n$，于是我们令前 $n-1$ 个数为 $k(k+1)$，最后补一个 $a_n=\frac1n$ 就好。

但是这样的做法有一个缺陷：当 $n=k(k+1)$ 时，$\frac1n$ 会出现两次，不满足 $a_i$ 都不同。

那这个时候我们考虑联合刚刚那个递推的做法，毕竟这样的特殊情况是少数（$500$ 以内能表示成 $k(k+1)$ 的形式的 $n$ 只有 $2,6,12,20,30,42,56,72,90,110,132,156,182,210,240,272,306,342,380,420,462$ 这 $21$ 个数），我们构造的 $a_i$ 的数量级也就在 $2\times n^2\le500000\ll10^9$（因为 $i$ 的情况是根据 $i-1$ 的情况乘二而来，而 $i-1$ 的构造中最大的 $a_i$ 也才 $i^2$ 量级），是满足题意的。

事实上，这个做法构造出来的最大的 $a_i$ 只有 $424120$ 而已。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
vector<int>ans[505],q;
bool z[505];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    ans[1].push_back(1);
    ans[2].push_back(-1);
    ans[3].push_back(2);ans[3].push_back(3);ans[3].push_back(6);
    for(int i=1;i*(i+1)<=500;i++)z[i*(i+1)]=1;//预处理哪些 n 可以表示成 k(k+1) 的形式
    q.push_back(2);q.push_back(6);q.push_back(12);//q 中存的是所有 k(k+1)
    for(int i=4;i<=500;i++)if(!z[i]){
        ans[i]=q;
        ans[i].push_back(i);
        q.push_back(i*(i+1));
    }else{
        ans[i]=ans[i-1];
        for(int j=0;j<ans[i].size();j++){
            ans[i][j]*=2;
            if(ans[i][j]>=1e9)ans[i][0]=-1;
        }
        ans[i].push_back(2);
        q.push_back(i*(i+1));
    }
    cin>>t;
    while(t--){
        cin>>n;
        if(ans[n][0]!=-1){cout<<"Yes\n";for(auto i:ans[n])cout<<i<<' ';cout<<endl;}
        else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：shinzanmono (赞：0)

# ARC163C 题解

题意：给定一个 $n$，请你构造一个长度为 $n$ 的序列 $a$ 使得 $\sum_{i=1}^n \frac1{a_i}=1$。

我们可以推出一个式子：$\frac1u=\frac1{u(u+1)}+\frac1{u+1}$。

然后我们就可以用这个式子进行解题。

使用两个 `std::multiset`，分别称作 $s,t$，分别表示拆过的数和不能再拆的数。首先，在两个 `std::multiset` 中都加入 $2$，因为 $\frac12+\frac12=1$，将构造序列的总长度设为 $2$，然后我们每次查找 `*s.begin()+1` 是否在 $s$ 中，如果在的话就将 `*s.begin()` 加入 $t$ 中，表示这个数不能再拆了。否则将 `*s.begin()*(*s.begin()+1)` 和 `*s.begin()+1` 加入 $s$，将构造序列的长度 $+1$，然后将 `s.begin()` 删除。

这个方法极其容易证明。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin>>t;
    while(t--){
        int n;
        std::cin>>n;
        if(n==1){
            std::cout<<"Yes\n1\n";
            continue;
        }
        if(n==2){
            std::cout<<"No\n";
            continue;
        }
        std::multiset<int>s,t;
        s.insert(2),t.insert(2);
        for(int i=1;i<=n-2;i++){
            int u=*s.begin();
            s.erase(s.begin());
            if(s.find(u+1)==s.end())
                s.insert(u+1),s.insert(u*(u+1));
            else t.insert(u),i--;
        }
        std::cout<<"Yes\n";
        for(int i:s)std::cout<<i<<" ";
        for(int i:t)std::cout<<i<<" ";
        std::cout<<"\n";
    }
    return 0;
}
```

---

