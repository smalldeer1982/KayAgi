# Long Inversions

## 题目描述

给定一个长度为$ n $的01字符串$ s $。01字符串是指只包含字符'1' 和'0'的字符串

可以选定一个整数$ k $ ( $ 1 \le k \le n $ )，将字符串中的连续k个字符进行替换，将0替换成1，1替换成0。

当 $ n=5 $ , $ s=00100 $时 , 你可以指定$ k=3 $ ，做如下操作：

- 翻转1-3的子串：$ s=\color{blue}{110}00 $ ;
- 反转3-5的子串：$ s=11\color{blue}{111} $ ;

经过不限次操作后，寻找能将01字符串中的所有字符转换成1的最大$ k $值。

## 样例 #1

### 输入

```
5
5
00100
5
01000
7
1011101
3
000
2
10```

### 输出

```
3
2
4
3
1```

# 题解

## 作者：菲斯斯夫斯基 (赞：8)

## CF1955E Long Inversions 题解

### 前言

很早之前就把 [F](https://www.luogu.com.cn/article/elv44qm8) 和 [G](https://www.luogu.com.cn/article/e7qne9oo) 的题解写了。无聊回来一看标签为啥是线段树？现有的两篇题解都是 $\mathcal O(n^2 \log n)$ 的，那还是回来写写 E 的题解吧。感觉题目很套路，甚至在 D 花的时间比这题多。

### 思路

注：以下的「翻转」指题目中的：将 $0$ 替换为 $1$，将 $1$ 替换为 $0$。

注意到 $n\le 5000$，考虑 $\mathcal O(n^2)$ 怎么做。

不难想到 $\mathcal O(n)$ 枚举 $k$，然后 $\mathcal O(n)$ check。

做这种题目做多了你就会发现：对于第 $1$ 位，只有在操作第 $1$ 至 $k$ 位的时候才能有影响，同时你不会对同样的连续 $k$ 个字符做两次操作。

然后就很好做了。从第 $1$ 位开始枚举，如果当前这一位是 $0$，那么就以当前为起点进行翻转。做到第 $i$ 位时，就能够保证前 $i-1$ 位都是 $1$。第 $i$ 位是 $0$ 就应当翻转，是 $1$ 时就没有必要了。

做到第 $n-k+2$ 位之后就不能再翻转了，因为没有 $k$ 位来操作了。如果剩下还有 $0$，那么这个 $k$ 就是错误的。

最后就是如何维护翻转标记。可以直接用差分，没必要用线段树或者树状数组。根据异或的性质：$a \oplus a=0$。维护一个差分数组 $f$。当 $f_i$ 为 $1$ 时表示这一位被翻转了。翻转区间 $[i,i+k-1]$ 只需在 $i$ 处和 $i+k$ 处添加标记，然后不断传递即可。

### 代码

只要理解了差分，代码并不难写。下面是我赛时写的，有点丑陋。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int t,n;
int f[N];
string s;
bool check(int k)
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=n-k+1;i++)
	{
		int c=s[i]-'0';
		f[i]^=f[i-1];
		c^=f[i];
		if(!c)f[i]^=1,f[i+k]^=1;//两个差分标记
	}
	for(int i=n-k+2;i<=n;i++)
	{
		int c=s[i]-'0';
		f[i]^=f[i-1];
		c^=f[i];
		if(!c)return false;
	}
	return true;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		s=' '+s;//我喜欢让字符串从1开始
		for(int i=n;i>=1;i--)
			if(check(i))
			{
				cout<<i<<endl;
				break;
			}
	}
	return 0;
}
```

---

## 作者：littlebug (赞：4)

看题解区里还没有 $O(n^2)$ 的做法，过来写一个。

## Solution

我们可以想到，从大到小暴力枚举每个 $k$，对于每个 $k$ 做一次检查其是否有解，如果有解就直接输出。

下面讨论对于每个 $k$ 的检查。

首先，我们可以贪心一下，从左往右扫，遇到一个 $0$ 就进行一次操作（设其位置为 $i$），如果到最后出现一个 $a_i=0$ 但是 $a_i$ 往后已经不足 $k$ 个字符（不能进行操作了）就无解。

然而，如果我们在检查 $k$ 的时候只是暴力枚举每次操作，时间复杂度会达到 $O(n^3)$ 的级别，于是考虑优化掉一个 $O(n)$。

很容易想到，我们可以把每次操作的那一维 $O(n)$ 压掉。我们考虑**只记录操作，但不执行**。具体地，可以使用一个 $cnt$ 来记录当前位置被进行的操作数量（理解一下，就是对于 $a_i$ 共进行了几次操作）。

于是，在遍历的过程中，设当前遍历到了位置 $i$：

- 若 $cnt$ 是奇数，则对 $a_i$ 取反，因为将一个 $a_i$ 反转 $2$ 次（偶数次）后得到的依然是 $a_i$。
- 若 $cnt$ 是偶数，则 $a_i$ 不变。

在完成上面关于 $a_i$ 的处理之后，再考虑对 $cnt$ 的处理：

- 若 $a_i=0$，则需要进行操作。一次操作更改的是 $[a_i,a_{i+k})$ 内的值，于是**这次操作会结束于 $a_k$**，所以我们需要在遍历到 $a_k$ 的时候将操作数 $-1$，可以用一个数组记录哪些位置是**一次操作的结束位置**。
- 若 $a_i=1$，则证明这个位置不需要进行操作，直接跳过即可。

所以，在遍历时我们**最先**要检查当前位置是否是一次操作的结束位置，如果是，则 $cnt-1$ 即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#define il inline
using namespace std;
const int MAXN=5000+5;
int n;
bitset <MAXN> a,b;
bitset <MAXN> ed; //是否是结束位置 
il bool check(int k)
{
	ed&=0;
	b=a;
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		if(ed[i]) //是结束位置，cnt-1 
			--cnt;
		if(cnt&1) //cnt为奇数，对当前位置的元素取反 
			b[i]=!b[i];
		if(!b[i])
		{
			if(i+k-1>n) //已经不能再进行操作了 
				return 0;
			ed[i+k]=1; //记录结束位置 
			++cnt; //操作数+1 
			b[i]=1;
		}
	}
	return 1;
}
il void solve()
{
	cin>>n;
	char _ch;
	for(int i=1;i<=n;++i)
	{
		cin>>_ch;
		a[i]=(_ch=='1');
	}
	for(int k=n;k>=1;--k)
	{
		if(check(k))
		{
			cout<<k<<'\n';
			return;
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Starrykiller (赞：1)

好像爆标了。

首先先把差分数组搞出来，不妨记为 $a_{0\sim n-1}$。

我们枚举每一个 $k$，check 是否合法。

根据题目要求，最终我们的 $a$ 数组形如 $a_i=[i=0]$。每次操作，可以选择 $0\le i\le n-k$，flip $a_i$ 和 $a_{i+k}$（特别地，如果 $i+k=n$，则不做任何事）。

观察到同一个模 $k$ 的同余类内可以任意调整，只需要满足最终这个同余类内的 $1$ 的数量在模 $2$ 意义下不变即可。所以只需要 check：

- $\forall 1\le i\lt k$，$i$ 对应的同余类 $a_i$ 的和是否能够被 $2$ 整除；（我们想要将它调整为 $0$）
- $0$ 对应的同余类的和是否**不能**够被 $2$ 整除；（我们想要将它调整为 $1$）

特别地，我们注意到 $n$ 所在的同余类可以任意调整，也就是不受上面两条规则约束，特判即可。

朴素地实现是 $\Theta(n^2)$ 的。但是发现这个东西是一个很典的根号分治，可以非常容易地做到 $\Theta(n^{1.5})$。

[代码](https://codeforces.com/problemset/submission/1955/282600481)。

Madoka 酱亲亲！

---

## 作者：ZhaoV1 (赞：1)

很久没有做**差分**的题目，是时候温习一下了。

**解析：**

由于 $n$ 的范围给予我们一定的想象空间，我们是可以执行两层 for 循环嵌套的。直接从 $n$ 到 $1$ 遍历最大的 $k$,内部应当是一套完整的模拟，最终判断是否能将所有位都变为 $1$。

具体地，在模拟中，可以从字符串的左边向右边轧过去，见到 $0$ 就执行一次自当前位到右边共计 $k$ 位的字符替换，当然不要用简单模拟去实现（会超时），可以借助差分，很明显当字符串某一位 $s_i=1$ 时，若 $f_i$ 为奇数，那么实际上这一位数应当是 $0$，同理其他情况也如此分析。

在我的代码中，最后还写了一个自 $n-k+1$ 至 $n$ 的遍历，这是为了验证该字符串最后的一些死角位置（无法再改变值的位置）是否都同为 $1$，是则答案合理，退出大循环，否则继续循环。


AC Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5005;
int t,n;
//f[i]为差分数组
int f[N];//更改的次数
string s;

void solve(){
	cin >> n;
	cin >> s; s = " " + s;
	int res = 0;
	for(int k=n;k>=1;k--){
		for(int i=1;i<=n;i++) f[i] = 0;//init
		for(int i=1;i<=n-k+1;i++){
			f[i] = f[i] + f[i-1];
			if((s[i] == '0' && !(f[i]&1)) || (s[i] == '1' && f[i]&1)){//说明此时实际上s[i]=0
				f[i]++;
				f[i+k]--;//差分的处理
			}
		}

		bool zero = false;
		bool one = false;
		for(int i=n-k+2;i<=n;i++){
			f[i] = f[i] + f[i-1];
			if((s[i]=='0'&&!(f[i]&1)) || (s[i]=='1'&&f[i]&1)) zero = true;
		}
		if(!zero){
			res = k;
			break;
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Nacky7_ix (赞：1)

## 题意与分析
给你一个二进制串，你需要选定一个整数 $k$。你的每一次操作都要选取一个长度为 $k$ 的子串，把它反转（$1\rightarrow0$ 或 $0\rightarrow1$）。最终目标是把整个串变成 $1$。求最大的 $k$ 的值。

要求最大的 $k$，考虑从大到小遍历 $k$。思考如何判定一个 $k$ 是否合法。从左到右遍历这个串，如果遇到 $a_i=0$，则对区间 $[i,\;i+k-1]$ 做一次操作。

考虑到这个操作会对后续的 $a_j$ 有影响，需要维护对 $a_j$ 进行操作的次数，于是每次操作后都对区间 $[i,\;i+k-1]$ 进行区间加 $1$。如果 （$a_j + query(j))\bmod2=1$，说明这个点不需要更改，否则需要。

最后看这个串最后小于 $k$ 的一小部分有没有 $0$ 就行了。

需要对区间 $[i,\;i+k-1]$ 加 $1$ 与单点查询，可以直接上[树状数组+差分](https://www.luogu.com.cn/problem/P3368)。（其实不用这样做，但是赛时没想到 qaq）。时间复杂度 $O(n^2\log n)$，非常丑陋。

## AC代码
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define pii pair<int, int>
#define int long long
using namespace std;
const int MAXN = 5e5 + 10;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        if(s[i - 1] == '0') a[i] = 0;
        else a[i] = 1;
    }
  
    for(int k = n; k >= 1; --k) {
        vector<int> tr(n + 2);
        auto lowbit = [&](int x) -> int {
            return x & -x;
        };
        auto modify = [&](int x, int val) -> void {
            while(x <= n) {
                tr[x] += val;
                x += lowbit(x);
            }
        };
        auto query = [&](int x) -> int {
            int res = 0;
            while(x) {
                res += tr[x];
                x -= lowbit(x);
            }
            return res & 1;
        };
        // 检查每一个点的 a[l] + query(l)
        // 奇数是正常的, 偶数是异常的
        for(int l = 1; l + k - 1 <= n; ++l) {
            int r = k + l - 1;
            if((a[l] + query(l)) & 1) continue;
            // 对区间 [l, r] 进行一次修改, 区间 +1, 记录区间的操作次数, 于是考虑差分
            modify(l, 1);
            modify(r + 1, -1);
        }
        bool valid = true;
        for(int l = n + 1 - k; l <= n; ++l) {
            if((a[l] + query(l)) & 1) continue;
            valid = false;
            break;
        }
        if(valid) {
            cout << k << endl;
            return;
        }
    }
    return;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}

---

## 作者：C_Pos_Princess (赞：0)

## 题意
给定一个长度为 $n$ 的序列，你可以选择一个值 $k$，使得进行若干次操作后，数列变成全 1 的形式。求出最大的一个 $k$。

## 题解
差分好题。

看到题面，很多人会想二分。但是仔细想想可以知道这个并没有单调性。

我们从大往小枚举 $k$ 的值。那么如何判断合法与否呢？

我们用一个数组来差分维护当前这个数字被异或过了几次，遍历到当前这个位置只需要抑或上当前数组的值即可。

时间复杂度 $O(\log n)$，显然大概率跑不到。

## 代码
```cpp
int n;
string s;
int t;

int f[5010];
bool check(int k){

	memset(f,0,sizeof f);
	for(int i = 1;i<=n-k+1;i++){
		int val = s[i]-'0';
		f[i]^=f[i-1];
		val^=f[i];
		if(!val) f[i]^=1,f[i+k]^=1;
	}
	for(int i = n-k+2;i<=n;i++){
		int val = s[i]-'0';
		f[i]^=f[i-1];
		val^=f[i];
		if(!val) return false;
	}
	return true;
	
}


int main(){
	read(t);
	while(t--){
		read(n);
		cin>>s;
		s = ' '+s;
		for(int i =n;i>=1;i--){
			if(check(i)){
				write(i);
				LF;
				
				break;
			}
		}
		
	}

	return 0;
}

```

---

## 作者：_Delete_ (赞：0)

## 思路

我们需要找出一个 $k$ 使得字符串中所有字符转换成 $1$，可以通过枚举求得。

显然，我们可以枚举取反左端点时，每次在 $i$ 处遇到 $0$ 时就对于 $a_i+k-1$ 这一区间进行变换。

对于每个 $k$ 在进行变换时显然是区间修改，单点查询，可以选择使用差分进行维护。注意到，本题的修改操作是取反，可用异或进行差分。

因为在枚举取反的左端点时，我们最多枚举到 $n-k+1$，所以我们要再次对于区间 $n-k+2$ 到 $n$ 对差分数组进行前缀和。

## 代码


```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
int a[5005];
int cf[5005];

//function 
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		char q;
		cin>>q;
		a[i]=q-'0';
	}
	int ans=1;
	for(int k=2;k<=n;k++){
		for(int i=1;i<=n;i++)cf[i]=0;
		for(int i=1;i<=n-k+1;i++){
			cf[i]=cf[i-1]^cf[i];
			if(a[i]^cf[i]==0){
				cf[i]^=1;
				cf[i+k]^=1;
			}
		}
		for(int i=n-k+2;i<=n;i++)cf[i]^=cf[i-1];
		bool tmp=1;
		for(int i=1;i<=n;i++){
			if(a[i]^cf[i]==0){
				tmp=0;
				break;
			}
		}
		if(tmp)ans=max(ans,k);
	}
	cout<<ans<<endl;
}

 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int t;
	cin>>t;
	while(t--)solve();
	
	
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

简单题。

考虑贪心地进行修改，每次选择字符串中最左侧第一个 $0$，并以该位置为左端点进行一次修改，可以发现若 $len$ 合法则这样一定构造出全 $1$ 串。

然而直接暴力实现是 $O(n^2)$ 的，但是发现每次选择的 $0$ 的位置一定是递增的，且一个位置在若干次修改后是否为 $0$ 仅与其初始值与该位置被修改次数（即被区间覆盖次数）有关，于是考虑在顺序枚举位置并进行区间修改时，差分维护每个位置被修改次数即可判断某个位置是否需要被修改。

单次检查时间复杂度变为 $O(n)$ 级别，总时间复杂度 $O(n^2)$ 级别。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e4+5;
int n,d[maxn];
string s;
bool check(int len){
	memset(d,0,sizeof(d));
	for(int i=0;i<n;i++){
		d[i]=d[i]+d[i-1];
		int tmp=s[i]-'0';
		if(d[i]%2==1){
			tmp^=1;
		}
		if(tmp==0){
			if(i<=n-len){
				d[i]++;
				d[i+len]--;
			}
			else{
				return 0;
			}
		}
	}
	return 1;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n>>s;
		for(int i=n;i>=1;i--){
			if(check(i)){
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
}
```

---

