# Competitive Fishing

## 题目描述

Alice 和 Bob 参加了一个钓鱼比赛，他们一共钓到了 $n$ 条鱼，鱼的大小从 $1$ 到 $n$ 升序排序。

两人的总分计算如下：首先，选择一个整数 $m$，所有鱼都被依次分到 $m$ 个非空连续区间，一条鱼只能被分到一个区间，并且区间从小到大排列。比如：第二个区间的鱼必须全部大于第一个区间的鱼。

接着，每条鱼都按照区间编号被分配了分数，第 $1$ 个区间的鱼分数全部为 $0$，第 $1$ 个区间鱼的分数全部为 $1$……第 $i$ 个区间鱼的分数全部为 $(i-1)$。

两人的分数即为他们各自钓到鱼的分数之和。

你想要让 Bob 的分数比 Alice 高至少 $k$ 分。求划分的区间个数 $m$ 的最小值。

## 样例 #1

### 输入

```
7
4 1
1001
4 1
1010
4 1
0110
4 2
0110
6 3
001110
10 20
1111111111
5 11
11111```

### 输出

```
2
-1
2
-1
3
4
-1```

# 题解

## 作者：HYdroKomide (赞：4)

### 题意：

给一个 0-1 串分段，每段内元素的分数从左到右递增，问使得位置为 $1$ 的总分数至少比位置为 $0$ 的总分数多 $k$ 的最小段数。

### 思路：

算是一道有些反直觉的题目，一眼让人容易想到直接给序列本身分段，陷入错误循环。实际上得到正解只需要注意到一个结论：在某个位置 $i$ 后断点，对总分数的贡献是一定的。而这个贡献等于 $i$ 后的 $1$ 个数减去 $0$ 个数。

证明也不难，在 $i$ 后断点，所有 $i$ 之后的元素分数全部增加 $1$，对于前面答案的统计没有任何影响，断点之间也不会有任何影响。

只需从后往前枚举断点并且算出所有 $n-1$ 个断点对答案的贡献，然后从大到小排序，贪心的取断点即可。

举个例子，考虑样例中 $[0,0,1,1,1,0]$ 的字符串，设 $i$ 后断点的贡献为 $a_i$，则有 $a=[1,2,1,0,-1]$。我们贪心的取断点，最多可以使得 $1$ 个数和 $0$ 个数之差达到 $4$。满足 $k=3$ 的条件只需取两个 $a$，将序列分成三段。

### 程序如下：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int T,n,k,a[N];
char str[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%s",&n,&k,str+1);
		int cnt0=0,cnt1=0;
		for(int i=n;i>=1;i--){
			if(str[i]=='0')cnt0++;
			else cnt1++;
			a[i]=cnt1-cnt0;//对于每个位置求它的贡献
		}
		sort(a+2,a+n+1);//排序，注意不能包含首项
		long long sum=0,ans=1;
		bool flag=true;
		for(int i=n;i>1;i--){
			if(a[i]<=0){
				flag=false;
				break;
			}
			sum+=a[i],ans++;
			if(sum>=k)break;
		}
		if(!flag||sum<k)printf("-1\n");
		else printf("%d\n",ans);
	}
} 
```

### THE END

---

## 作者：__vector__ (赞：2)

考虑将一个完整的区间拆成两段的贡献是什么。  

假设 $[l,r]$ 拆为 $[l,mid],[mid+1,r]$。  

那么 $[mid,n]$ 所有鱼的价值加 $1$。  

注意到，此时本质上是从 $mid+1$ 开始，每个点的编号加了 $1$。  

也就是说，问题转化为：$[2,n]$ 共 $n-1$ 个点，对于每个点，都可以选择是否将从这个点开始的所有点的价值加 $1$。    

假设一条鱼如果是 Bob 获得，那么是 $1$，反之 $-1$，设 $p_i$ 代表前 $i$ 个鱼的前缀和。  

假设第 $i$ 个点选择将其开始的所有点价值加 $1$，那么 Bob 领先 Alice 的分数将会增加 $p_n-p_{i-1}$。  

接下来排序贪心就可以。

---

## 作者：Hide_In_The_Shadow (赞：1)

智慧+注意力题。

将 $01$ 序列划分成若干非空段，每段中的点可获得其段下标 $-1$ 的分数，使 $1$ 所得分数比 $0$ 至少大 $k$；

场上被卡成伞兵了。其实只需要注意到当前点前划分与否对后续序列造成的影响是固定的，问题就迎刃而解了。

我们记 $sum[i]$ 表示到 $i$ 为止的后缀中 $1$ 的个数减去 $0$ 的个数。如果我们在 $i$ 之前划分，则无论后缀序列怎么划分，此处划分的贡献总是 $sum[i]$。可以感性理解成为后缀赋了一个新的初值继续在后缀上处理原问题。

然后，我们可以对除了 $sum[1]$ 之外的值排序，从大到小取，直到取的值之和 $\geq  k$ 或者 $sum$ 为非正数为止，分别对应着最小可行划分数和无解。段数等于划分数 $+1$。

时间复杂度 $O(n\log(n))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,k,sum[N];
char s[N];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>k>>s;
        for(int i=n;i>=1;--i){
            sum[i]=sum[i+1]+(s[i-1]-'0'?1:-1);
        }
        sort(sum+2,sum+n+1);
        int ans=0,now=0;
        for(int i=n;i>=2;--i){
            if(sum[i]<=0)break;
            now+=sum[i];
            ans++;
            if(now>=k)break;
        }
        if(now>=k)cout<<ans+1<<'\n';
        else cout<<"-1\n";
        for(int i=1;i<=n;++i)sum[i]=0;
    }
    return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[传送门](http://codeforces.com/problemset/problem/2042/C)

![](https://s21.ax1x.com/2024/12/03/pAIvAA0.png)

## solution

将所有的 `0` 视作 `-1`，这样就可以利用前缀和或者后缀和维护，本人用的后缀和，将后缀和从大到小排序后从大的那一头开始遍历，用 $tmp$ 统计后缀和数组的和，遍历过程中若有 $tmp \geq k$，意为两人分差已经 $\geq k$，输出然后 $i + 1$ 即可，若遍历完仍未有 $tmp \geq k$ 则无解。

## code


```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 10;
int T,n,k,sum[MAXN],a[MAXN];

inline void read(int &T)
{
    T = 0;
    int f = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1;ch = getchar();}
    while(isdigit(ch)){T = (T << 1) + (T << 3) + (ch ^ 48);ch = getchar();}
    T *= f;
}

void write(int x)
{
    if(x > 9) write(x / 10);
    if(x < 0) putchar('-'),x = -x;
    putchar(x % 10 + '0');
}

signed main()
{
    read(T);
    while(T --)
    {
        read(n),read(k);
        for(int i = 1;i <= n;i ++)
        {
            scanf("%1d",&a[i]);
            if(!a[i]) a[i] = -1;
        }
        sum[n] = 0;
        for(int i = n - 1;i >= 1;i --)
            sum[i] = sum[i + 1] + a[i + 1];
        sort(sum + 1,sum + n + 1,greater <int>());
        int tmp = 0;
        bool flag = false;
        for(int i = 1;i <= n;i ++)
        {
            tmp += sum[i];
            if(tmp >= k)
            {
                write(i + 1),putchar('\n');
                flag = true;
                break;
            }
        }
        if(!flag)
            write(-1),putchar('\n');
    }
    return 0;
}
```

---

## 作者：Phrvth (赞：0)

# CF2042 C

牛逼题。

## 题目

给定一个 $0/1$ 序列，给定一个 $k$，你可以将这个序列分成若干连续段，假设分成 $m$ 段，第 $i$ 段每个元素的权值为 $i-1$，问分最少得段使得 $1$ 的权值比 $0$ 的权值大至少 $k$。

## Solution：

其实你可以发现答案只跟分割线有关系，为啥？考虑设 $s_i$ 表示 $i\sim n$ 的后缀和，即考虑 $1$ 为 $+1$，$0$ 为 $-1$。

那就记 $l_i,r_i$ 表示某一段的左端点和右端点，其中 $r_i+1=l_{i+1}$，那么答案可以表达为：$0 \cdot (s_{l_1} - s_{r_1+1}) + 1\cdot (s_{l_2}-s_{r_2+1})+\cdots$，然后把同项移到一块去就变成了 $0 \cdot (s_{l_1}) + (1-0)\cdot (s_{l_2})+(2-1)\cdot (s_{l_3})+\cdots+s_{l_m}$。

所以最后我们发现原贡献变成了 $s_{l_1}+\cdots s_{l_n}$。

所以后面就很简单了，排个序选最大的即可。

```cpp
#include <bits/stdc++.h>
#define dbg(x) cerr << #x" = " << (x) << endl
#define	debug(format,...) printf(format, ##__VA_ARGS__)

using namespace std;

typedef long long ll;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define ms memset
template < typename T > void read(T &x) {
	x = 0; char s = getchar(); bool f = 0;
	while (! isdigit(s)) { f |= s == '-'; s = getchar(); }
	while (isdigit(s)) { x = x * 10 + s - 48; s = getchar(); }
	x = f ? -x : x;
}
template < typename T, typename ...Args> void read(T &x, Args &...xs) { read(x); read(xs...); }

void Solve() {
	int n, k;
	cin >> n >> k; string s;
	cin >> s;
	vector < int > a;
	int sum = 0;
	for (int i = s.size() - 1; i > 0; i --) {
		sum += s[i] == '1' ? 1 : -1;
		if (sum > 0) a.push_back(sum);
	}
	sort(a.begin(), a.end());
	int ans = 1;
	while (! a.empty() && k > 0) k -= a.back(), a.pop_back(), ans ++;
	if (k > 0) cout << -1 << '\n';
	else cout << ans << '\n';
}

int main () {
	ios :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T; cin >> T;
	while (T --) Solve();	
	return 0;
}
```

---

## 作者：wawatime1 (赞：0)

### 题意
给一个 01 串，每段内元素的分数从左到右递增，问使得位置为 $1$ 的总分数至少比位置为 $0$ 的总分数多 $k$ 的最小段数。
### 思路
考虑将一个完整的区间拆成两段的贡献。

假设原本区间为 $[l, r]$，把区间拆成 $[l,i]$ 和 $[i+1,r]$ 

那么 $i$ 到 $n$ 所有鱼的价格 $+1$。

这样一来，这道题就很简单了，问题便转化为 $[2,n]$ 共 $ n−1 $ 个点，对于每个点，都可以选择将从这个点开始的所有点的价值加 $ 1$。

接下来求出每个位置的贡献后缀和后，从大往小贪心即可。

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

假若段之间的分界点为 $a _ 1, a _ 2, \ldots, a _ k$，那么相当于每次给 $[a _ i, n]$ 内所有数加上 $1$ 的贡献系数。求出每个位置的贡献后缀和后，从大往小贪心即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
ll n, k, T, cnt = 0, ans = 0;
string s;
void read () {
	s = ""; cnt = 0; ans = 0;
    cin >> n >> k >> s;
    priority_queue <ll> q;
    for (ll i = s.size () - 1; i >= 1; i --) {
        if (s[i] == '1') cnt ++;
        else cnt --;
        q.push (cnt);
    }
    while (q.size() >= 1) {
        k -= q.top ();
        if (q.top () <= 0) break;
        ans ++;
        if (k <= 0) {
            cout << ans + 1 << endl;
            return ;
        }
        q.pop ();
    }
    cout << -1 << endl;
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}

```

---

## 作者：lfxxx (赞：0)

贡献摊到每次分割两段的操作上。

假若段之间的分界点为 $p_1,p_2,...,p_k$，那么相当于每次给 $[p_i,n]$ 内所有数加上 $1$ 的贡献系数，求出每个位置的贡献的后缀和后在每个位置进行分割的代价都是已知的，从大往小贪心即可。

注意不能在位置 $1$ 处分割。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int n,k;
void work(){
    cin>>n>>k;
    string S;
    cin>>S;
    priority_queue<int> q;
    int sum=0;
    for(int i=S.size()-1;i>=1;i--){
        if(S[i]=='1') sum++;
        else sum--;
        q.push(sum);
    }
    int ans=0;
    while(q.size()>0){
        k-=q.top();
        if(q.top()<=0) break;
        ans++;
        if(k<=0){
            cout<<ans+1<<'\n';
            return ;
        }
        q.pop();
    }
    cout<<"-1\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

