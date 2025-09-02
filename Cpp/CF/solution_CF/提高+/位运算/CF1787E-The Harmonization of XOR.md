# The Harmonization of XOR

## 题目描述

给定 $n$ 个数 $[1,2,3,\ldots,n]$ 和两个正整数 $k$ 和 $x$。

将这些数分成恰好 $k$ 组使得每组的异或和都是 $x$。具体地，每个数都必须出现在恰好一组内。

例如，$n = 15,k = 6,x = 7$ 时，下列分法是合法的（$\oplus$ 表示按位异或运算）：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[8,15]$, $8 \oplus 15 = 7$
- $[7]$, $7 = 7$

下列分法是不合法的：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[7]$, $7 = 7$

因为 $8$ 和 $15$ 没有出现。

下列分法也不合法：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$,
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$,
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$,
- $[3,4]$, $3 \oplus 4 = 7$,
- $[8,15]$, $8 \oplus 15 = 7$,
- $[7]$, $7 = 7$.

因为 $1$ 和 $2$ 未出现且 $3$ 出现两次。

~~这题本来是 C~~


保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 样例 #1

### 输入

```
7
15 6 7
11 4 5
5 3 2
4 1 4
6 1 7
11 5 5
11 6 5```

### 输出

```
YES
3 6 10 11
3 5 12 14
3 3 9 13
3 1 2 4
2 8 15
1 7
YES
2 1 4
2 2 7
2 3 6
5 5 8 9 10 11
NO
YES
4 1 2 3 4
YES
6 1 2 3 4 5 6
NO
NO```

# 题解

## 作者：yimuhua (赞：6)

首先，我们发现，由于 $x\oplus x=0$，我们可以将三个集合并成一个，所以我们只需要考虑如何最大化集合数量。

$[a,a\oplus x]$ 和 $[x]$ 显然是合法的，于是尽量构造这两种，剩下的数组成一个集合，最后合并。

### 正确性证明：

显然构造两种合法集合已经是最优的了，于是只需要证明剩下的数所构成的集合不能再被拆成多个。

设 $p$ 为二进制下 $x$ 的最高位，在 $1$ 到 $n$ 中有 $q$ 个数的第 $p$ 位为 $1$。

$\because$ 每个集合的异或和都为 $x$，

$\therefore$ 每个集合中必须有一个数第 $p$ 位为 $1$。

假设有至少一个第 $p$ 位为 $1$ 的数没有在构造两种集合时被用到。

$\because p$ 为 $x$ 的最高位，

$\therefore q$ 个数中的每一个异或 $x$ 都小于自己本身。

于是在构造两种集合时我们会用到这些数，矛盾。

### 证毕。

所以按上面的方法构造即可。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> b;
int t, n, k, x, s, f;
vector<vector<int> > a, ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> k >> x, s = 0, f = (k & 1) ? x : 0, a.clear(), b.clear(), ans.clear();
        for(int i = 1; i <= n; i++)
            s ^= i;
        if(s ^ f) {
            cout << "NO\n";
            continue;
        }
        for(int i = 1; i <= n; i++)
            if(i == x)
                a.push_back({x});
            else if((x ^ i) > n)
                b.push_back(i);
            else if((x ^ i) < i)
                a.push_back({x ^ i, i});
        if(a.size() < k) {
            cout << "NO\n";
            continue;
        }
        for(int i = 0; i < k; i++)
            ans.push_back(a[i]);
        for(int i = k; i < a.size(); i++)
            for(int j : a[i])
                ans[0].push_back(j);
        for(int i : b)
            ans[0].push_back(i);
        cout << "YES\n";
        for(int i = 0; i < k; i++) {
            cout << ans[i].size() << ' ';
            for(int j : ans[i])
                cout << j << ' ';
            cout << '\n';
        }
    }
    return 0;
}
```


---

## 作者：2018ljw (赞：5)

## 构造
先判断比较基础的无解：

1. $x\ge 2^{\lfloor\log n\rfloor+1}$，此时最高位一定构造不出来，必定无解。
2. $k$ 为奇数，且所有数异或和不为 $x$。
3. $k$ 为偶数，且所有数异或和不为 $0$。

恰好 $k$ 个的限制比较难搞，转化成最多能划分成多少个集合。

以下规定 $\oplus$ 符号表示异或运算。

我们先尽可能两两分组，即对于每一个 $i$，若 $x=i$ 或 $i\oplus x\le n$，我们将 $i$ 与 $x\oplus i$ 分为一组。注意这样 $x$ 与 $0$ 可能分入同一组，判掉 $0$ 就行。对于剩下的数，让它们和前面任意一组合并。

## 证明
首先证明这样分法下，分出的子集个数最多。

假设 $x$ 的最高位为第 $a$ 位，有 $t$ 个数的二进制在该位为 $1$。

显而易见的，每组中必须要有奇数个这种数，换而言之，我们至多能分出 $t$ 组。

接下来，我们证明我们的做法至少能分出 $t$ 组：

对于任意一个第 $a$ 位为 $1$ 的数 $s$，考虑与其配对的数 $s^\prime$。

由于第 $a$ 位为 $1$，一定有 $s^\prime=s-2^a+g$，其中 $g$ 为 $s\oplus x$ 时后 $a-1$ 位的变化值。

由于 $x$ 的更高位均为 $0$，并且 $s-2^a$ 的第 $a$ 位必定为 $0$，故有 $g<2^a$。

进一步的，对于每个第 $a$ 位为 $1$ 的数 $s$，与其配对的数一定有 $s^\prime<s$，并且 $s^\prime$ 的第 $a$ 位为 $0$。

换而言之，当我们从大到小枚举每个数找配对时，这 $t$ 个数一定会找更小的数与之配对，并且这 $t$ 个数不会两两配对。因此，我们至少会分出来 $t$ 组。

所以，这样分组，组数达到最大值。

进一步的，既然这 $t$ 个第 $a$ 位为 $1$ 的数都找到配对了，那么对于剩下的数，它们第 $a$ 位一定不为 $1$。换而言之，剩下的数无论怎么选取，均无法使得选出的数异或和为 $x$。那么如果有解，则必须有其异或和为 $0$。

但不难发现这一部分实际上就是最初的无解判断，因此此时异或和必定为 $0$。

因此，我们将前 $t-k$ 组、没被选出的数与第 $t-k+1$ 组合并到一起，之后输出所有组即可。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int n,k,s;
bool use[200001];
vector<int>usl;
int gh[200001][2];
priority_queue<int>d;
int main(){
	int i,t;
	scanf("%d",&t);
	while(t--){
		usl.resize(0);
		for(i=1;i<=n;i++)use[i]=0;
		scanf("%d%d%d",&n,&k,&s);
		int r=0,mul=1;
		for(i=1;i<=n;i++)r^=i;
		while(mul<=n)mul*=2;
		if(s>=mul||(k%2==1&&s!=r)||(k%2==0&&r)){
			printf("NO\n");
			continue;
		}
		int tm=0,rtm;
		for(i=n;i;i--){
			if(use[i])continue;
			int tr=s^i;
			if(tr>n)usl.push_back(i);
			else tm++,gh[tm][0]=i,gh[tm][1]=tr,use[tr]=1;
		}
		if(tm<k){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		int dis=tm-k;
		for(i=1;i<=dis;i++){
			d.push(-gh[i][0]);
			d.push(-gh[i][1]);
		}
		for(i=dis+1;i<tm;i++){
			d.push(-gh[i][0]);
			d.push(-gh[i][1]);
			if(d.top()==0)d.pop();
			printf("%d ",d.size());
			while(d.size())printf("%d ",-d.top()),d.pop();
			printf("\n");
		}
		for(i=0;i<usl.size();i++)d.push(-usl[i]);
		d.push(-gh[tm][0]);
		d.push(-gh[tm][1]);
		if(d.top()==0)d.pop();
		printf("%d ",d.size());
		while(d.size())printf("%d ",-d.top()),d.pop();
		printf("\n");
	}
}
```

---

## 作者：jiangtaizhe001 (赞：3)

虽然放在 d1C，但是真实难度是 d1B-d1C。

由于异或满足交换律和结合律，所以首先需要保证 $1$ 到 $n$ 所有数字异或和等于 $k$ 组的异或和。  
其次我们考虑到 $x \oplus x \oplus x=x$，也就是说 $3$ 组可以合并成 $1$ 组，所以我们只需要最大化能够分的组数。

考虑最大化组数的一个方法：
- 如果 $x$ 存在，单独分组
- 其余两两一组
- 剩下的在一组

证明：设 $B$ 为 $x$ 的最高位，即 $x$ 的第 $B$ 位为 $1$（类似 popcount）
设 $M$ 是从 $1$ 到 $n$ 的数字，并且使得第 $B$ 位为 $1$ 的数量，显然答案小于等于 $M$，因为在每个组中，必须至少有一个数字表示第 $B$ 位为 $1$。  
这 $M$ 个数字异或 $x$ 之后肯定更小，所以一定存在 $M$ 组。

时间复杂度 $O(n)$。


```cpp
int n,k,x,p[maxn],vis[maxn];
int getsum(int x){ int i,s=0; for(i=1;i<=x;i++) s^=i; return s; }
struct JTZ{ int x,y; }a[maxn]; int cnt,now;
void work(){
	n=read(); k=read(); x=read(); int i; if((k&1)?getsum(n)!=x:getsum(n)){ puts("NO"); return; }
	cnt=now=0; for(i=1;i<=n;i++) p[i]=vis[i]=0;
	for(i=1;i<=n;i++){
		if(i==x) a[++cnt]=(JTZ){i,0},p[i]=1;
		if((i^x)<=n&&!p[i]&&!p[i^x]) p[i]=1,p[i^x]=1,a[++cnt]=(JTZ){i,i^x};
	} if(cnt<k){ puts("NO"); return; } puts("YES");
	for(i=1;i<k;i++){
		if(a[i].y) pc('2'),pc(' '),print(a[i].x),pc(' '),print(a[i].y),pc('\n'),now+=2;
		else pc('1'),pc(' '),print(a[i].x),pc('\n'),now++;
		vis[a[i].x]=vis[a[i].y]=1;
	} print(n-now),pc(' ');
	for(i=1;i<=n;i++) if(!vis[i]) print(i),pc(' ');
	pc('\n'); return;
}
```

---

## 作者：MortisM (赞：3)

[题目链接](https://codeforces.com/contest/1787/problem/E)

## 题意简述

$t$ 组 testcase，每组给定 $n,k,x$ 三个数。求将 $1\sim n$ 划分成 $k$ 个**子序列**（可以不连续），使得每个子序列的异或和都为 $x$。输出方案。

数据范围：$n,k\le 2\times 10^5,x\le 10^9$，并且保证 $\sum n\le 2\times 10^5$。

## 题解

由于所有组一共异或起来就是 $1\oplus 2\oplus\cdots\oplus n$，而又因为每组异或起来都是 $x$，所以总共又是 $k$ 个 $x$ 异或起来，这个要首先判断是否相等。

然后还有一个判断就不是那么显然了。发现每一组要想凑到 $x$，则必然要有至少一个 $x$ 最高位是 $1$，所以一共至少要有 $k$ 个 $x$ 最高位是 $1$ 的数，这个也要判断一下（脑洞好大）。

下面的一定都是 `YES` 了，给出构造方案（需要特判一下 $k=1$）：

+ 如果 $x\le n$，就先把 $x$ 作为单独的一组。
+ 枚举每一个 $v$，如果 $v$ 和 $x\oplus v$ 都还没用的话就把这两个合并为一组，直到已经一共组成 $k-1$ 组了为止。
+ 把剩余没用过的做为一组。

下面给出该做法的正确性证明（不太严谨）：

首先，设一共有 $m$ 个 $x$ 最高位为 $1$ 的数，通过前面的判断我们有如下两条性质：

1. $m\ge k$
2. $m\equiv k\pmod 2$

我们将 $v$ 和 $x\oplus v$ 配对可以得到至少 $m$ 组，要减少的话奇偶性相同也可以。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,n) for(int i=0;i<n;i++)
#define rept(i,n) for(int i=1;i<=n;i++)
#define repe(i,l,r) for(int i=l;i<=r;i++)
#define FOR(i,r,l) for(int i=r;i>=l;i--)
#define fi first
#define se second
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define sz(v) (int)(v.size())
using namespace std;
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template<typename T>void chmax(T& a,T b){if(a<b)a=b;return;}
template<typename T>void chmin(T& a,T b){if(a>b)a=b;return;}
set<int> st;
void solve(){
	int n,k,x;
	cin>>n>>k>>x;
	int xsum=0;
	rept(i,n)xsum^=i;
	int wish=(k&1?x:0);
	if(xsum!=wish){
		cout<<"NO\n";
		return;
	}
	int cnt=0;
	rept(i,n){
		if((x&i)>(x>>1LL))cnt++;
	}
	if(cnt<k){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
	if(k==1){
		cout<<n<<" ";
		rept(i,n)cout<<i<<" ";
		cout<<"\n";
		return;
	}
	st.clear();
	rept(i,n)st.insert(i);
	cnt=0;
	if(x<=n){
		cnt++;
		st.erase(x);
		cout<<"1 "<<x<<"\n";
	}
	rept(i,n){
		if(!st.count(i)||!st.count(x^i))continue;
		if(cnt==k-1)break;
		cout<<"2 "<<i<<" "<<(x^i)<<"\n";
		st.erase(i);
		st.erase(x^i);
		cnt++;
	}
	cout<<sz(st)<<" ";
	for(auto v:st)cout<<v<<" ";
	cout<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
//Jerry_Jiang
```

---

## 作者：hsaht2426 (赞：0)

(这道题但凡改改就是个 $\text{NP}$ 问题了)

首先题目让我们构造恰好为 $k$ 组和为 $x$ 的方案数，这是不好做的，考虑先判无解。

首先把式子写出来，由于异或的交换率与结合律，我们组合后容易得到 $k$ 个 $x$ 的异或和等于 $1$ 到 $n$ 的异或和，可以用它判第一层无解。

但这只保证了前者可以推导出后者，即必要条件，我们还需要一个供检验的充分条件。由于我们保证了前者能分成由 $k_2$ (奇偶固定)个 $x$ 与 $0$ (不存在分组时必为 $0$)的组合，我们只需要求出最大的分组数量，和 $k$ 比较一下，这就是充分条件。

但是这个时候还是很像 $\text{NP}$ 问题。

我们考虑还是形式化题面。

对于一组数，它要满足这样一个式子: $p_1 \oplus p_2 ... \oplus p_m = x$。

不妨取一个数出来，得到 $p_2 \oplus p_3 ...\oplus p_m = x \oplus p_1$。

于是我们得到对于一个 $p_1$，$p_2 \oplus p_3 ...\oplus p_m$ 是一个定值。（当然这几步也可以用异或逆元唯一性解释）

我们显然不能枚举，这应该是因为我们的选择集合过大，那么什么样的 $p_2 \oplus p_3 ...\oplus p_m$ 对答案有贡献呢？

从简单集合开始，首先如果匹配了空集，即 $x \oplus p_1=0$，显然无需匹配。

从简单集合开始，如果 $x \oplus p_1$ 本身就是合法的，即 $x \oplus p_1 \le n$，此时 $[p_2,p_3,\dots,p_m]$ 的选择集合大于 $x \oplus p_1$。(或者说决策包容性，具体的，该集合可以成为 $p_2 \oplus p_3 \dots \oplus p_m$ ，也可以拆开与其他的匹配）

此时我们必然将 $x \oplus p_1$ 与 $x$ 匹配。

由于这东西对所有数成立，我们可以先把满足条件的匹配上。

接下来考虑剩下的数，每个数 $y$ 都满足 $x \oplus y>n$。我们显然只能将多个逆元不合法的数异或后使存在 $p_2 \oplus p_3 ...\oplus p_m \le n$ 与 $q_2 \oplus q_3 ...\oplus q_M \oplus x \le n$。

这个时候就没有适配的性质了，我们不妨直接按位考虑。由于我们在二进制比大小，考虑比较最高位，记作第 $i$ 位。

分析条件三，结合原有的显然条件 $q_2 \oplus q_3 ...\oplus q_M \le n$，所以 $x$ 与 $n$ 必然最高位相同。

分析条件一，$x \oplus y>n$，其最高位显然满足 $x_p \oplus y_p\ge n_p$，由于 $y_p = n_p =1$，所以 $x_p=0$。

那么带入条件二，最高位全为 $0$ 的数异或后绝对没有最高位为 $1$ 的数大，于是条件不成立，也就是说后面的数必然对组数无贡献。

于是这样就可以求出最多的分组了，然后合成一下即可。

[代码](https://codeforces.com/contest/1787/submission/219906981)

---

## 作者：Meteor_ (赞：0)

# CF1787E The Harmonization of XOR

## 题目大意

给定 $n$ 个数 $[1, 2, 3, \cdots, n]$ 和两个正整数 $k$ 和 $x$。

将这些数分成恰好 $k$ 组使得每组的异或和都是 $x$。

（$1 \le k \le n \le 2 \cdot 10^5, 1 \le x \le 10^9$）。

## 题解

首先，我们知道，如果我们无法从 $n$ 个数中提取出 $k$ 个异或和为 $x$ 的集合，那么一定无解。所以我们想要尽量多的取提取集合，让每一个集合里的数尽量少。所以我们可以将所以异或和为 $x$ 的集合写成 $[a \oplus x, a]$（$a$ 为正整数）这种形式。

证明如下：

假设我们现在已经无法提取出 $[a \oplus x, a]$ 这种形式的集合。

我们令 $p$ 为 $x$ 在二进制下的最高位，且 $1 \sim n$ 中有 $q$ 个数第 $p$ 位为 $1$。

我们可以得到，对于 $[a \oplus x, a]$ 这个形式的集合，$a \oplus x$ 与 $a$ 中只有一个数第 $p$ 位为 $1$。如果在没有选择的数中，仍有数第 $p$ 位为 $1$，那么它与 $x$ 的异或和也一定没有选择，并且它们可以组成 $[a \oplus x, a]$ 这个形式的集合。因为 $a \oplus x$ 一定比 $a$ 小，并且 $a$ 与 $a \oplus x$ 一一对应，不会有其他数选中 $a \oplus x$。

有了上面的结论，我们就可以先去枚举 $a$，尝试提取出 $k$ 个形式为 $[a \oplus x, a]$ 或 $[x]$ 的集合。如果 $a$ 已经从一枚举到了 $n$，但仍未提出来 $k$ 组集合，那么显然无解。如果能够提出来，去考虑剩下的数的异或和是否等于零。如果等于零，可以放在任意一个集合中，不影响这个集合最终的异或和。如果不为零，那么一定无解，因为我们想要满足条件就一定无法选中所有的数。实现就很简单了。

## 代码

```cpp
#include <bits/stdc++.h>
#define M 200005

using namespace std;

int T, n, k, x, cnt, tot;
bool vis[M];
pair<int, int> pa[M];

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    for(int t = 1; t <= T; ++ t) {
        cnt = 0; 
        tot = 0;
        for(int i = 0; i <= n; ++ i)
            vis[i] = 0;
        cin >> n >> k >> x;
        for(int i = 0; i <= n; ++ i) {
            if(vis[i])
                continue;
            if((i ^ x) <= n) {
                vis[i] = 1;
                vis[x ^ i] = 1;
                tot += (i == 0 ? 1 : 2);
                pa[++ cnt] = {x ^ i, i};
                if(cnt == k)
                    break;
            }
        }
        if(cnt != k)
            cout << "NO\n";
        else {
            int sum = 0;
            for(int i = 0; i <= n; ++ i)
                if(!vis[i])
                    sum ^= i;
            if(sum == 0) {
                cout << "YES\n";
                for(int i = 1; i < k; ++ i) {
                    if(pa[i].second != 0)
                        cout << '2' << ' ' << pa[i].first << " " << pa[i].second << '\n';
                    else
                        cout << '1' << ' ' << pa[i].first << '\n';
                }
                int pos1 = pa[k].first, pos2 = pa[k].second;
                cout << n - tot + (pos2 == 0 ? 1 : 2) << ' ';
                for(int i = 1; i <= n; ++ i)
                    if(!vis[i] || i == pos1 || i == pos2)
                        cout << i << ' ';
                cout << '\n';
            }
            else
                cout << "NO\n";
        }
    }
}
```

---

## 作者：User_Authorized (赞：0)

## 题面
将集合 $\left\{1, 2, \cdots, n\right\}$ 划分为 $k$ 个非空不交子集，使得每个子集的异或和均为 $x$。

（$1 \le n,k \le 2 \times 10^5$）。

## 题解
首先显而易见的判断一下无解的情况，记 $sum = \bigoplus\limits_{i = 1}^{n} i$，如果 $k$ 为奇数但 $sum \neq x$ 或者 $k$ 为偶数但 $sum \neq 0$ 都一定无解，下文假定已经判断出这种情况。

可以发现任意三个满足要求的子集可以合并为满足要求的一个大集合，所以任务转化为最大化合法子集的数量。可以发现 $\left\{a, a\oplus x\right\}$ 和 $\left\{x\right\}$ 这两种集合显然是满足要求的，所以优先构造这两种集合，剩下的元素最后合并到这些集合中。

下面对这种构造方式最优进行证明，该种构造方式最优，当且仅当剩下的元素构成的集合 $S$ 不能分裂成多个满足要求的集合。

设 $x$ 在二进制表示下的最高位为 $B$，如果 $S$ 可以分裂成多个满足要求的集合，那么 $S$ 中一定存在二进制下第 $B$ 位为 $1$ 的数，假定其为 $p$。因为 $B$ 为 $x$ 二进制表示下的最高位，所以 $x$ 二进制下第 $B$ 位一定为 $1$。进而可以得出 $x \oplus p < p$，考虑 $m = x \oplus p$ 是否会在其他集合构造时被使用，首先第一种集合 $\left\{a, a\oplus x\right\}$，显然如果 $m$ 在该集合中，那集合的另一个元素一定为 $p$，与 $p$ 未使用矛盾；考虑第二种情况 $\left\{x\right\}$，因为 $p > 0 \Rightarrow m \neq x$，矛盾。

因此在这种构造方式下，剩下的元素构成的集合 $S$ 的异或和不可能为 $x$，又考虑到最开始判出了总异或和不合法的情况，所以集合 $S$ 的异或和一定为 $0$，所以在最终求解时直接将 $S$ 并入任意一个先前构造出的合法集合中。

## Code
```cpp
//Codeforces - 1787E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, K, X;

        std::cin >> N >> K >> X;

        valueType xorSum = 0;

        for (valueType i = 1; i <= N; ++i)
            xorSum ^= i;

        if (((K & 1) == 1 && xorSum != X) || ((K & 1) == 0 && xorSum != 0)) {
            std::cout << "NO" << '\n';

            continue;
        }

        ValueVector remain;
        ValueMatrix ans;

        for (valueType i = 1; i <= N; ++i) {
            if (i == X) {
                ans.emplace_back(1, i);
            } else if ((i ^ X) > N) {
                remain.emplace_back(i);
            } else if ((i ^ X) < i) {
                ans.push_back({i, i ^ X});
            }
        }

        if (ans.size() < K) {
            std::cout << "NO" << '\n';

            continue;
        }

        for (valueType i = K; i < ans.size(); ++i)
            ans[0].insert(ans[0].end(), ans[i].begin(), ans[i].end());

        ans[0].insert(ans[0].end(), remain.begin(), remain.end());

        std::cout << "YES" << '\n';

        for (valueType i = 0; i < K; ++i) {
            std::cout << ans[i].size() << ' ';

            for (auto const &value: ans[i])
                std::cout << value << ' ';

            std::cout << '\n';
        }
    }
}
```

---

