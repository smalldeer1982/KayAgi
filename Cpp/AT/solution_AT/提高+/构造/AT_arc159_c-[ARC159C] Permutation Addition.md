# [ARC159C] Permutation Addition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_c

正整数列 $ A=(a_1,\ldots,a_N) $ が与えられます。

次の操作を $ 0 $ 回以上 $ 10^4 $ 回以下繰り返すことで $ A $ の値をすべて等しくできるかを判定し、可能な場合は操作列の一例を示してください。

- $ (1,\ldots,N) $ の順列 $ (p_1,\ldots,p_N) $ を決め、$ A $ を $ (a_1+p_1,\ldots,a_N+p_N) $ に置き換える。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ a_i\ \leq\ 50 $
- 入力はすべて整数
 
### Sample Explanation 1

この出力例の通りに $ 8 $ 回の操作を行うことで $ A $ は $ (24,24) $ となり、値がすべて等しくなります。

### Sample Explanation 3

初めから $ A $ の値がすべて等しいです。

## 样例 #1

### 输入

```
2
15 9```

### 输出

```
Yes
8
1 2
1 2
1 2
1 2
2 1
1 2
1 2
1 2```

## 样例 #2

### 输入

```
5
1 2 3 10 10```

### 输出

```
No```

## 样例 #3

### 输入

```
4
1 1 1 1```

### 输出

```
Yes
0```

# 题解

## 作者：Mashiroqwq (赞：6)

不妨记 $s= \sum a_i$。

- $n$ 是奇数

不难发现如果 $s \bmod n \neq 0$，那么必然无解。

否则记 $t=\dfrac{s}{n}$。

考虑每次选出一对下标 $(i,j)$，满足 $a_i<t$ 且 $a_i>t$，我们相当于可以通过以下操作使得 $a_i$ 变大 $1$，$a_j$ 减小 $1$。

进行两次操作，第 $1$ 次加上 $1,2,3,4,5\dots n$，第二次加上 $n,n-1,n-2\dots 1$。

不妨让 $i$ 加的为 $1,n$，$j$ 加的为 $2,n-1$，那么我们交换第一次操作中两个下标加的数，即 $i$ 加的为 $2,n$，$j$ 加的为 $1,n-1$。

不难发现一定有解。操作次数为 $O(na)$ 的。

- $n$ 是偶数

如果 $s\bmod n=0$，运用上述算法即可。

如果 $s \bmod n=\dfrac{n}{2}$，考虑先随机一次操作之后再进行上述算法即可。

操作次数为 $O(na)$。

---

## 作者：_ZSR_ (赞：2)

### [[ARC159C] Permutation Addition](https://www.luogu.com.cn/problem/AT_arc159_c)

令 $sum= \sum_{i=1}^n a_i$，每一次操作相当于把 $sum$ 加上 $\frac {n(n+1)} {2}$。

如果 $n$ 是奇数，当 $sum \bmod n \neq 0$ 时无解。因为最后每一个数都要相等，因此最后 $n \mid sum$。而 $\frac {n(n+1)} {2} \bmod n=0$，如果 $sum \bmod n \neq 0$，那么无论进行多少次操作都不会使得 $n \mid sum$。

如果 $n$ 是偶数，那么当 $sum \bmod n=0$ 或者 $sum \bmod n=\frac n 2$ 时有解。第一种情况显然。第二种情况因为 $\frac {n(n+1)} {2} \bmod n=\frac n 2$，因此 $sum \bmod n=\frac n 2$ 时可以通过若干次操作使得所有数相等。

接下来考虑怎么构造操作。我们发现给原序列加上一个 $1 \dots n$ 和 $n \dots 1$ 后原序列中的每个数的相对大小并没有发生改变。那么我们可以每次选择两个数 $a_i$ 和 $a_j$，令 $a_i$ 加上 $2$ 和 $n$，令 $a_j$ 加上 $1$ 和 $n-1$，其他数按照之前的方法加。这样操作后 $a_i$ 和 $a_j$ 的差距就缩小了 $2$。重复这样的操作直到每个数都相等。

还记得之前 $n$ 为偶数时 $sum \bmod n = \frac n 2$ 的情况吗？我们需要给序列随便加上一个排列使得 $sum \bmod n=0$，然后再进行构造。

code 
```
#include <bits/stdc++.h>
using namespace std;
const int N=60;
int n;
int a[N];
vector<int> big,small;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    scanf("%d",&n);
    int sum=0;
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    if (n&1&&sum%n!=0) 
    {
        puts("No");
        return 0;
    }
    if (!(n&1)&&sum%n!=0&&sum%n!=n/2)
    {
        puts("No");
        return 0;
    }
    puts("Yes");
    int extra=0;
    if (!(n&1)&&sum%n==n/2)
    {
        extra=1;
        sum+=n*(n+1)/2;
        for (int i=1;i<=n;++i) a[i]+=i;
    }
    int avg=sum/n;
    for (int i=1;i<=n;++i)
    {
        for (;a[i]<avg;++a[i]) small.push_back(i);
        for (;a[i]>avg;--a[i]) big.push_back(i);
    }
    printf("%d\n",(int)big.size()*2+extra);
    if (extra) 
    {
        for (int i=1;i<=n;++i) printf("%d ",i);
        puts("");
    }
    for (int i=0;i<(int)big.size();++i)
    {
        int u=big[i],v=small[i];
        int l=3,r=n-2;
        for (int j=1;j<=n;++j) printf("%d ",j!=u&&j!=v?l++:(j==u?1:2));
        puts("");
        for (int j=1;j<=n;++j) printf("%d ",j!=u&&j!=v?r--:(j==u?n-1:n));
        puts("");
    }
    return 0;
}
```


---

## 作者：roBotic (赞：1)

最终我们想要得到的序列元素全部相等，必要条件是元素之和 $S\equiv0\pmod n$，然而我们每次加上的数的总和为 $\frac{1}{2}n(n+1)$，分讨：

- 当 $n$ 是奇数，$\frac{1}{2}n(n+1)\equiv 0\pmod n$，则只有一开始的元素之和 $S_0\equiv0\pmod n$ 才有解，否则无法无解。
- 当 $n$ 是偶数，$\frac{1}{2}n(n+1)\equiv 0\pmod {\frac{n}{2}}$，则只有 $S_0\equiv 0\pmod {\frac{n}{2}}$，也就是 $S_0\equiv 0,\frac{n}{2}\pmod n$ 的时候才有解，否则无解。

然后再考虑如何构造解。但关于为什么满足以上条件的序列一定有解，在构造过程中会加以叙述。

先考虑 $S_0\equiv 0\pmod n$ 的情况。

我们会发现原序列如果加上这样两个序列，元素之间相对的差值是不变的：$\{1,2,\cdots,n\},\{n-1,n-2,\cdots,1\}$。我们记当前序列的平均数为 $k$，我们选择两个数 $i,j$ 满足 $a_i<k,a_j>k$，那么我们考虑构造一种序列使得其他元素相对不变，$a_i$ 相对加一，$a_j$ 相对减一，于是我们钦定 $a_i$ 加上 $2,n$，$a_j$ 加上 $1,n-1$，并且其他元素加上 $x,n-x+1$，于是就构造出了所需要的序列。然后做完了。记值域为 $V$，会发现每个数这样至多被加减 $V$ 次，所以操作次数 $O(nV)$。

再考虑 $S_0\equiv \frac{n}{2}\pmod n$ 的情况，这时候随便加上一个排列就转化为了前者。

能发现在全部相同之前，每次一定能找到一个 $a_i<k,a_j>k$，并且这样至多减少 $nV$ 次就会全部相同，所以满足前文条件的序列一定有解。

[https://atcoder.jp/contests/arc159/submissions/62886706](https://atcoder.jp/contests/arc159/submissions/62886706)。

---

## 作者：Purslane (赞：1)

## Solution

首先想办法给出一个有解的必要条件 .

发现加上排列的顺序是乱的 , 但是他们总和不变 .

所以每次加上的和为 $\frac{n(n+1)}{2}$ .

而最后序列的总和应当为 $na$ , 为 $n$ 的倍数 .

当 $n \equiv 1 \pmod 2$ 时 , 加上的 $\frac{n(n+1)}{2}$ 必然是 $n$ 的倍数 .

当 $n \equiv 0 \pmod 2$ 时 , 加上的必然为 $\frac{n}{2}$ 的倍数 .

那么 , 也就是说 , 最开始这些数的总和得是 $n$ 的倍数 ( 当 $n$ 是奇数时 ) 或者总和得是 $\frac{n}{2}$ 的倍数 .

而且 , 如果 $n$ 是偶数 , 但是总和是 $\frac{n}{2}$ 的倍数却不是 $n$ 的倍数 , 可以通过随便加一个排列变成 $n$ 的倍数 .

也就是说 , 这时候可以保证 $n$ 个数的平均值是整数 .

这有用吗 ? 还真有用 . 考虑如果 $n$ 个数的平均数是整数 , 每次都可以通过让一个小一点的加一 , 大一点的减一最后达成平衡 .

所以我们想办法让一个小一点的数加一 , 让一个大一点的数减一 .

当然 , 我们不能找到减号 , 这是相对的 . 先让所有数都加上同样一个大小的数 . 具体可以表现为第一次加 $\{1,2,3,\dots,n\}$ , 第二次加 $\{n,n-1,n-2,\dots,1\}$ .

发现如果把第二个序列的前面两个数调整顺序 , 那么相当于加上 $\{n,n+2,n+1,n+1,\dots,n+1\}$ , 刚好满足要求 !

于是就做完了 .

kenkooo 上给的难度似乎有点虚高 .

代码 :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10;
int n,tot,a[MAXN]; 
vector<vector<int>> ans;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i],tot+=a[i];
	if(n%2) {if(tot%n) return cout<<"No",0;}
	else {
		if(tot%(n/2)) return cout<<"No",0;	
		if(tot%n) {
			vector<int> ans1;
			ffor(i,1,n) ans1.push_back(i),tot+=i,a[i]+=i;
			ans.push_back(ans1);	
		}
	}
	queue<int> q1,q2; if(tot%n) return cout<<"No",0; tot/=n;
	ffor(i,1,n) {
		if(a[i]<tot) ffor(j,1,tot-a[i]) q2.push(i);
		else ffor(j,1,a[i]-tot) q1.push(i);
	}
	while(!q1.empty()) {
		int u=q1.front(),v=q2.front(); q1.pop(),q2.pop();
		int id1=3,id2=n-2; vector<int> ans1,ans2;
		ffor(i,1,n) {
			if(i==u) ans1.push_back(1),ans2.push_back(n-1);
			else if(i==v) ans1.push_back(2),ans2.push_back(n);
			else ans1.push_back(id1++),ans2.push_back(id2--);
		}
		ans.push_back(ans1),ans.push_back(ans2);
	}
	cout<<"Yes\n"<<ans.size()<<'\n';
	for(auto vc:ans) {
		for(auto pr:vc) cout<<pr<<' ';
		cout<<'\n';	
	}
	return 0;
}
```

---

## 作者：FyFive (赞：1)

#### 题意

给一个序列 $a$，每次操作可以将 $a$ 加上一个 $1$ 到 $N$ 的排列，问能否使得 $a$ 中每一个元素均相等，如果能，给出方案。

#### 思路

首先不难想到一个非常基础操作方法：$1$ 到 $N$ 的顺序，加上 $1$ 到 $N$ 的逆序，这样就可以白白浪费两次操作。虽然很显而易见，但是基于此可以想到如下性质：
- 如果交换第一次操作中 $p[1]$ 和 $p[2]$ 的值，则两次操作后，$a[1]$ 的相对值会 $+1$，同时，$a[2]$ 的相对值会 $-1$。

基于这个性质，不难构造出操作步骤：
- 将整个 $a$ 减去 $a$ 中元素的平均值；（这一步并非实际操作，只是视作）
- 每次在 $a$ 中选一个正数和一个负数，依照性质进行操作，使得正数 $-1$，负数 $+1$；
- 直到 $a$ 为全 $0$ 数组。

基于这个操作，可得无解的数组即为 $a$ 的平均值不为整数的数组，即 $\displaystyle (\sum a[i]) \% N \not ={0}$。
> 同时，不难发现当 $N \% 2=0$ 且 $\displaystyle (\sum a[i]) \% N = \frac{N}{2}$ 时同样有解，那么此时可以通过随机加一个排列使得其可以操作。
> 
> 因为这个情况可以视作只加了顺序排列而没有加逆序排列，那么再加一个排列就可以继续操作了。

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[55],p[55],did[100005][55],top;
inline void read() {cin>>n; for(int i=1;i<=n;++i) cin>>a[i];}
inline int pd()
{
    int sum=0;
    for(int i=1;i<=n;++i) sum+=a[i];
    if(n%2==1) if(sum%n!=0) return 0; else return 1;
    else if(sum%n==0) return 1; else if(sum%n==n/2) return 2; else return 0;
}
inline void rdn()
{
    for(int i=1;i<=n;++i) p[i]=i;
    random_shuffle(p+1,p+n+1);    
}
inline void sxn(int x,int y) 
{
    p[x]=2,p[y]=1;
    int nws=2; for(int i=1;i<=n;++i) if(i!=x&&i!=y) p[i]=++nws;
}
inline void nxn(int x,int y) 
{
    p[x]=n,p[y]=n-1;
    int nws=n-1; for(int i=1;i<=n;++i) if(i!=x&&i!=y) p[i]=--nws;
}
inline void ins() {++top; for(int i=1;i<=n;++i) did[top][i]=p[i];}
int main()
{
    read(); srand(time(0));
    if(pd()==0) {puts("No"); return 0;}
    else puts("Yes");
    while(pd()==2) {rdn(); ++top; for(int i=1;i<=n;++i) did[top][i]=p[i],a[i]+=p[i];}
    vector<int>sa,sb;
    int mid=0;for(int i=1;i<=n;++i) mid+=a[i]; mid/=n;
    for(int i=1;i<=n;++i) if(a[i]<mid) sa.push_back(i); else if(a[i]>mid) sb.push_back(i);
    while(sa.size()>0)
    {
        int x=sa[0],y=sb[0];
        sxn(x,y); ins();
        nxn(x,y); ins();
        a[sa[0]]++; a[sb[0]]--;
        if(a[sa[0]]==mid) sa.erase(sa.begin());
        if(a[sb[0]]==mid) sb.erase(sb.begin());
    }
    cout<<top<<endl;
    for(int i=1;i<=top;++i) {for(int j=1;j<=n;++j) cout<<did[i][j]<<' '; cout<<endl;}
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc159_c)

## 思路

刚开始可能没有什么思路，我们考虑如何判断无解。

显然的，最后所有数都要等于数列的平均数，设这个平均数为 $sum$。

也显然的，$sum$ 必须是 $n$ 的倍数。

考虑我们每次加一个 $1 \sim n$ 的排列等于给 $sum$ 加上了 $\dfrac{n \times (n-1)}{2}$，而这个东西对 $n$ 取模后的结果等于 $\dfrac{n}{2}$，所以得出结论：如果原序列的 $sum$ 对 $n$ 取模的余数不等于 $0$ 或 $\dfrac{n}{2}$，必然无解。

考虑除了这种情况之外的所有情况，发现必然有解。

例如我们想让 $x$ 加 $1$。

我们需要凑出一种构造方式使得除 $x$ 外的数都加了 $y$，而 $x$ 加了 $y+1$。

这是不可能的。

换一种方式，如果我们想让 $x$ 加 $1$，并且同时 $y$ 减 $1$。

这是可能的，我们只需要构造形如以下的两组排列即可：

$$3,4,5,...,1,a,a+1,...,2,...$$

$$n-2,n-3,n-4,...,n-1,n-a+1,n-a,...,n,...$$

其中 $(1,n-1)$ 对应的位置是 $y$，$(2,n)$ 对应的位置是 $x$。

我们发现 $y$ 加了 $n$，$x$ 加了 $n+2$，别的所有数都加了 $n+1$，则此时相对于所有数，$x$ 加了 $1$，$y$ 减了 $1$，目的达成。

分析一下操作次数，大约 $100n$，因为每个数都小于等于 $100$（为什么是 $100$，因为若 $sum$ 不是 $n$ 的倍数，我们要先加上一个排列），所以我们最多执行 $50n$ 次操作，每次操作需要两个排列，所以次数是 $100n$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
int const N=50+5;
int a[N],pj,n,sum;
inline bool chk(){
    int flg=1;
    for (int i=1;i<=n;++i) flg&=(a[i]==pj);
    return flg;
}
int cnt=0,b[N];
vector<int>ans[114514];
inline void go(int x,int y){
    b[x]=2,b[y]=1;int k=2;
    ++cnt;
    for (int i=1;i<=n;++i) if (i!=x && i!=y) b[i]=++k;
    for (int i=1;i<=n;++i) ans[cnt].push_back(b[i]);
    ++cnt;
    for (int i=1;i<=n;++i)
        if (i!=x && i!=y) ans[cnt].push_back(n-b[i]+1);
        else if (i==x) ans[cnt].push_back(n);
        else ans[cnt].push_back(n-1);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i],sum+=a[i];
    int h=n*(n+1)/2,flg=1;h%=n;
    if (sum%n==0) flg=0;
    for (int i=1;i<=n && flg;++i)
        if ((h*i+sum)%n==0){
            flg=0;
            for (int j=1;j<=i;++j){
                ++cnt;
                for (int k=1;k<=n;++k) ans[cnt].push_back(k),a[k]+=k,sum+=k;
            }
            break;
        }
    if (flg) return cout<<"No\n",0;
    pj=sum/n;
    while (!chk()){
        int x=0,y=0;
        for (int i=1;i<=n;++i){
            if (x && y) break;
            for (int j=1;j<=n;++j)
                if (a[i]<pj && a[j]>pj) x=i,y=j;
        }
        go(x,y),++a[x],--a[y];
    }
    cout<<"Yes\n"<<cnt<<'\n';
    for (int i=1;i<=cnt;++i,cout<<'\n')
        for (auto j:ans[i]) cout<<j<<' ';
    return 0;
}
```

---

## 作者：COsm0s (赞：0)

+ 当 $n$ 为奇数时，$\frac{n(n+1)}{2}\bmod n=0$；

+ 当 $n$ 为偶数时，$\frac{n(n+1)}{2}\bmod n=\frac{n}{2}$。

我们设 $S=\sum a_i$，那么当 $n$ 为奇数时，$S\bmod n\neq 0$，或当 $n$ 为偶数时，$S\bmod n\neq \frac{n}{2}$。

反之无解。

但是对于 $n$ 是偶数和 $n$ 是奇数的两种情况很繁琐。

所以我们可以对于 $n$ 是偶数，第一次随机一个 $n$ 的排列。

这样此时 $S\bmod n$ 就等于 $0$ 了。

接下来我们可以想象一下，让 $a$ 中的数相等，也就是让最大值和最小值一点点靠近。

我们记 $x$ 为 $a$ 中的最小值的下标，$y$ 为 $a$ 中最大值的下标。

我们可以通过两次操作让 $a_x\gets a_x + n + 2, a_y\gets a_y + n$，其余的 $a_i\gets a_i + n + 1$。

这样最大值和最小值缓缓靠近，就完成了。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define REP(i, a, b) for(int i = (a); i <= (b); ++ i)
#define DOW(i, a, b) for(int i = (a); i >= (b); -- i)
#define pii pair<int, int>
namespace Cosmos {
	const int N = 2e5 + 10, inf = 1e18;
	int n, a[N], p[N], cnt;
	vector<int> ans[N];
	int main() {
		int sum = 0;
		cin >> n;
		REP(i, 1, n) cin >> a[i], sum += a[i], p[i] = i;
		if ((n & 1) && sum % n) cout << "No\n";
		else if ((n % 2 == 0) && (sum % n != n / 2) && (sum % n != 0)) cout << "No\n";
		else {
			cout << "Yes\n";
			if (n % 2 == 0 && (sum % n == n / 2)) {
//				random_shuffle(p + 1, p + n + 1);
				REP(i, 1, n) a[i] += p[i];
				++ cnt;
				REP(i, 1, n) ans[cnt].emplace_back(p[i]);
			}
			while (true) {
				int maxn = 1, minn = 1;
				bool flag = 0;
				REP(i, 2, n) {
					if(a[i] != a[i - 1]) {
						flag = 1;
					}
					if (a[maxn] < a[i]) maxn = i;
					if (a[minn] >= a[i]) minn = i;
				}
				if(!flag) break;
				int tot = 0;
				vector<int> p(n + 1), q(n + 1);
				REP(i, 1, n) {
					if (i != maxn && i != minn) {
						p[i] = ++ tot;
					}
				}
				p[maxn] = ++ tot;
				p[minn] = ++ tot;
				REP(i, 1, n) {
					q[i] = n + 1 - p[i];
				}
				swap(q[maxn], q[minn]);
				REP(i, 1, n) a[i] += p[i] + q[i];
				++ cnt;
				REP(i, 1, n) ans[cnt].emplace_back(p[i]);
				++ cnt;
				REP(i, 1, n) ans[cnt].emplace_back(q[i]);
			}
			cout << cnt << '\n';
			REP(i, 1, cnt) {
				for(int j : ans[i]) {
					cout << j << ' ';
				}
				cout << '\n';
			}
		}
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Cosmos::main();
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

设 $S = \frac{N \times \left(N + 1\right)}{2}$，可以发现我们一定有 $N \mid 2 \cdot S$。因此我们可以得出有解的必要条件为 $N \mid \sum A_i \lor N \mid \left(\sum A_i + S\right)$。因此若 $N \nmid \sum A_i$ 且 $N \mid \left(\sum A_i + S\right)$ 我们不妨随意进行一次操作进而得到 $N \mid \sum A_i$ 的问题。

我们下面考虑在 $N \mid \sum A_i$ 的限制下进行操作并逐渐使得序列值相同。根据上述分析，我们必须成对的进行操作才能维持 $N \mid \sum A_i$ 的限制。

考虑若要不改变元素的值，那么我们第一次先任意操作，第二次取 $p_{i, 2} = N + 1 - p_{i, 1}$ 即可。发现在这样的情况下每个元素值均增加 $N + 1$。

同时我们的目标是将序列元素的值均操作为平均值，因此我们考虑每一次选取一个大于平均值的元素和一个小于平均值的元素。后通过调整排列使得大的元素增加的值为 $N$，小的元素增加的值为 $N + 2$。设其分别为 $x, y$，这可以通过改变排列为 $p_{x, 1} = 1, p_{x, 2} = n - 1, p_{y, 1} = 2, p_{y, 2} = n$ 来实现。

因此我们可以通过若干次调整来使得序列满足条件。

---

