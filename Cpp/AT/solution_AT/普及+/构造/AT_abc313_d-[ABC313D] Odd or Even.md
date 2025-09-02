# [ABC313D] Odd or Even

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc313/tasks/abc313_d

この問題は **インタラクティブな問題**（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です。

整数 $ N $ および $ N $ 未満の **奇数** $ K $ が与えられます。  
ジャッジシステムは、$ 0 $ および $ 1 $ からなる長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ を隠し持っています。

あなたは数列 $ A $ の要素の値を直接知ることはできません。  
その代わりに、ジャッジシステムに対して以下の質問を $ N $ 回まで行うことができます。

- $ 1 $ 以上 $ N $ 以下の相異なる整数 $ x_1,\ x_2,\ \dots,\ x_K $ を選ぶ。そして、$ A_{x_1}\ +\ A_{x_2}\ +\ \dots\ +\ A_{x_K} $ の偶奇を聞く。

$ N $ 回以下の質問で $ (A_1,\ A_2,\ \dots,\ A_N) $ を全て特定して、答えを出力してください。  
ただし、**ジャッジは適応的です**。言い換えると、ジャッジシステムは今までの質問の回答に矛盾しない範囲で$ A $ の内容を自由に変更することができます。  
そのため、出力が次の条件を満たす場合にあなたの作成したプログラムは正解とみなされます。それ以外の場合は不正解とみなされます。

- ここまでの質問の回答と矛盾しないような数列が一意に定まっており、かつそれがプログラムが出力した数列と一致している。

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です。

最初に、$ N $ および $ K $ を標準入力から受け取ってください。

> $ N $ $ K $

次に、$ (A_1,\ A_2,\ \dots,\ A_N) $ を全て特定できるまで質問を繰り返してください。  
質問は、以下の形式で標準出力に出力してください。ここで $ x_1,\ x_2,\ \dots,\ x_K $ は $ 1 $ 以上 $ N $ 以下の相異なる $ K $ 個の整数です。

> $ ? $ $ x_1 $ $ x_2 $ $ \dots $ $ x_K $

これに対する応答は、次の形式で標準入力から与えられます。

> $ T $

ここで、$ T $ は質問に対する答えで、

- $ T $ が `0` である場合は $ A_{x_1}\ +\ A_{x_2}\ +\ \dots\ +\ A_{x_K} $ は偶数であることを、
- $ T $ が `1` である場合は $ A_{x_1}\ +\ A_{x_2}\ +\ \dots\ +\ A_{x_K} $ は奇数であることを意味します。

ただし、$ x_1,\ x_2,\ \dots,\ x_K $ が制約を満たしていないか、質問の回数が $ N $ 回を超えた場合は $ T $ は `-1` となります。

ジャッジが `-1` を返した場合、プログラムはすでに不正解とみなされています。この場合、ただちにプログラムを終了してください。

$ A $ の要素を全て特定できたら、特定した $ A $ の要素を以下の形式で出力してください。その後、ただちにプログラムを終了してください。

> $ ! $ $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \lt\ N\ \leq\ 1000 $
- $ K $ は奇数
- $ A_i $ は $ 0 $ または $ 1 $

### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で誤った出力形式による出力を行った、あるいはプログラムが途中で終了した場合のジャッジ結果は不定です。**
- 解答を出力したらただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。
- ジャッジは適応的です。言い換えると、ジャッジシステムは今までの質問の回答に矛盾しない範囲で $ A $ の内容を変更することができます。

### 入出力例

以下の入出力例は $ N=5,\ K=3 $ の場合の入出力例です。**この入出力例の通りに出力するとジャッジ結果は WA になることに注意してください。**  
入出力例では、プログラムが出力した $ A\ =\ (1,\ 0,\ 1,\ 1,\ 0) $ はここまでの質問の回答に矛盾しない数列ですが、例えば $ (0,\ 0,\ 1,\ 0,\ 0) $ もここまでの質問の回答に矛盾しない数列であるため、数列 $ A $ は一意に定まっていません。そのため、このプログラムは不正解とみなされます。

  入力 出力 説明    `5 3`  まず整数 $ N $ および $ K $ が与えられます。   `? 2 4 1 `  $ (x_1,\ x_2,\ x_3)\ =\ (2,\ 4,\ 1) $ として質問を行います。  `0`  質問の答えは $ 0 $ なので、ジャッジはその値を返します。   `? 5 3 2` $ (x_1,\ x_2,\ x_3)\ =\ (5,\ 3,\ 2) $ として質問を行います。   `1`  質問の答えは $ 1 $ なので、ジャッジはその値を返します。   `! 1 0 1 1 0` $ A $ の答えとして $ (1,\ 0,\ 1,\ 1,\ 0) $ を出力します。$ A $ を一意に特定できていないのでジャッジ結果は WA になります。

# 题解

## 作者：Fire_flame (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc313_d)

关于这场干出与 ABC288 一样的逆天操作这件事。

## $\mathtt{Solution}$

如果 $k=1$，显然每次询问 $a_i$ 即可。

然后就不会做了……

那就先考虑一种简单的情况：$n=k+1$。

令 $b_i(1\le i\le n)$ 为询问除 $a_i$ 以外的数的和的奇偶性，即：

$$b_i=a_1\oplus a_2\oplus\dots\oplus a_{i-1}\oplus a_{i+1}\oplus \dots \oplus a_n$$

根据任意整数 $x$ 满足 $x\oplus x=0$，可得 $b_i\oplus b_{i+1}=a_i\oplus a_{i+1}$。

因为 $k$ 为奇数，所以 $n$ 为偶数，就可以得到：$a_1=b_2\oplus b_3\oplus\dots \oplus b_{k+1}$，这里不理解的同学可以自己举个例子消一下。

又因为 $b_i\oplus b_{i+1}=a_i\oplus a_{i+1}$，在求出 $a_1$ 之后就可以往后消元得到 $a_2\dots a_{k+1}$ 了。

那么把情况推广到 $n$ 为大于 $k$ 的任意值。

现在就很简单了，按照上面的步骤求出 $a_1\dots a_{k+1}$ 的值，对于 $a_t(k+1<t)$，从 $a_1\dots a_{k+1}$ 选择 $k-1$ 个和 $a_t$ 一起询问，可以得到最后答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 1e3 + 5;
int n, k, a[MAXN], b[MAXN];
int main(){
	cin >> n >> k;
	if(k == 1){
		for(int i = 1;i <= n;i ++){
			cout << "? " << i << endl;
			a[i] = read();
		}
		cout << "! ";
		for(int i = 1;i <= n;i ++)cout << a[i] << " ";
		cout << endl;
		return 0;
	}
	for(int i = 1;i <= k + 1;i ++){
		cout << "? ";
		for(int j = 1;j <= k + 1;j ++){
			if(i == j)continue;
			cout << j << " ";
		}
		cout << endl;
		cin >> b[i];
	}
	int op = b[k + 1];
	for(int i = 2;i <= k;i += 2)
		op ^= b[i] ^ b[i + 1];
	a[1] = op;
	for(int i = 2;i <= k + 1;i ++)
		a[i] = a[i - 1] ^ b[i - 1] ^ b[i];
	for(int i = k + 2;i <= n;i ++){
		int tmp = 0;
		cout << "? ";
		for(int j = 1;j < k;j ++){
			cout << j << " ";
			tmp ^= a[j];
		}
		cout << i << endl;
		cin >> a[i];
		a[i] ^= tmp;
	}
	cout << "! ";
	for(int i = 1;i <= n;i ++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：_liuyi_ (赞：3)

# 思路
我们先特别地考虑 $n=k+1$ 的情况，这种情况我们可以构造询问，第 $i$ 次询问的序列 $S_i$ 中不包含 $i$，$(1\le i\le k+1)$。易证  ${\textstyle \sum_{i=1}^{k+1}S_i=k\times\textstyle \sum_{i=1}^{k+1}a_i}$ ，因为 $k$  为奇数，所以  ${\textstyle \sum_{i=1}^{k+1}S_i\equiv \textstyle \sum_{i=1}^{k+1}a_i}\pmod 2$，所以 $a_i= {\textstyle \sum_{i=1}^{k+1}a_i\bmod2-S_i\bmod2}= {\textstyle \sum_{i=1}^{k+1}S_i\bmod2-S_i\bmod2}$。那么我们就用了 $k+1$ 次询问求出了  $a_1 \sim a_{k+1}$。那么对于一般情况，我们先求出 $a_1 \sim a_{k+1}$。那剩下的怎么办呢，我们很容易想到剩下的 $n-(k+1)$ 次询问中，我们只问一个未知的 $a_i$，剩下的都是已知的，那么可以求出 $a_i$ 的奇偶性，最终我们刚好只用了 $n$ 次询问，为了实现方便，我下面的代码中已知的是 $a_1,a_2...a_{k-1}$，最终的实现的复杂度为 $O(k^2+n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define mem(a, x) memset(a, x, sizeof(a)) 
#define pb push_back
#define SZ(x) ((int)(x).size())
#define debug(x) cout<<#x<<":"<<x<<endl;
#define all(a) a.begin(),a.end()
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
const int N=2e5+10;
const int mod=1e9+7;
//const int mod=998244353;
inline int query(VI a){
	int x;
	printf("? ");
	for(auto y:a) printf("%d ",y);
	puts("");
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
int n,k,s[N],ans[N],sum,cnt;
VI a;
int main(){
	scanf("%d%d",&n,&k);
	rep(i,1,k+1){
		rep(j,1,k+1)
			if(i!=j) a.pb(j);
		ans[i]=query(a);
		ans[i]%=2;
		sum+=ans[i];
		a.clear();
	}
	sum%=2;
	rep(i,1,k+1) ans[i]=(ans[i]+sum)%2;
	sum=0;
	a.clear();
	rep(i,1,k-1){ 
		sum+=ans[i];
		a.pb(i);
	}
	sum%=2;
	rep(i,k+2,n){
		a.pb(i);
		ans[i]=sum^query(a);
		a.pop_back();
	}
	printf("! ");
	rep(i,1,n) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：robertuu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc313_d)

很神奇的一种做法（居然正好能 AC）。

如果你询问了 $a_1,a_2,\dots,a_k$ 和 $a_1,a_2,\dots,a_{k-1},a_x$ 两组数，$a_1,a_2,\dots,a_{k-1}$ 都是相同的，答案是否相同只取决于 $a_k$ 和 $a_x$ 是否相同，因此就诞生了一种很投机取巧的方法。

先不妨设 $a_k = 1$（后面会改）询问 $a_1,a_2,\dots,a_{k-1},a_x (k \le x \le n)$，就可以确定 $a_{k+1},a_{k+2},\dots,a_n$ 的值。

之后再询问 $a_2,a_3,\dots,a_{k+1}$，把 $a_1$ 也搞出来。

然后再询问 $a_1,\dots,a_{x-1},a_{x+1},\dots,a_{k+1}(2 \le x \le k-1)$，把 $2$ 至 $k-1$ 都通过 $1$ 求出来（式子与求 $1$ 的式子只相差一位）。

最后检验一开始的假设，由于已经询问了 $n$ 次，再询问就超了，需要再利用其中一次询问（比如 $a_1,a_2,\dots,a_k$），把求出的值代入检验一下，如果和评测机那次返回的答案不同，说明假设错误，所有的值全部取反即可。

注意：每次询问后要清空缓冲区（用 `fflush(stdout)`、`cout << flush` 或 换行用 `endl` 自动清空）！！

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag[1001];
int main()
{
	int n,m,ans1,ans2,anss;
	scanf("%d%d",&n,&m);
	for(int i = m;i <= n;i++)
	{
		printf("? ");
		for(int j = 1;j < m;j++)
			printf("%d ",j);
		printf("%d\n",i);
		fflush(stdout);
		scanf("%d",&ans2);
		if(i != m)
			if(ans1 == ans2) flag[i] = flag[i-1];
			else flag[i] = !flag[i-1];
		else anss = ans2;
		ans1 = ans2;
	}
	for(int i = 1;i < m;i++)
	{
		printf("? ");
		for(int j = 1;j < i;j++) printf("%d ",j);
		for(int j = i+1;j <= m+1;j++) printf("%d ",j);
		printf("\n");
		fflush(stdout);
		scanf("%d",&ans2);
		if(i == 1)
		{
			if(ans2 == anss) flag[1] = flag[m+1];
			else flag[1] = !flag[m+1];
		}
		else
		{
			if(ans2 == ans1) flag[i] = flag[i-1];
			else flag[i] = !flag[i-1];
		}
		ans1 = ans2;
	}
	int sum = 0;
	for(int i = 1;i <= m;i++) sum += flag[i];
	if(anss == sum % 2)
	{
		printf("! ");
		for(int i = 1;i <= n;i++)
			printf("%d ",flag[i]);
		fflush(stdout);
	}
	else
	{
		printf("! ");
		for(int i = 1;i <= n;i++)
			printf("%d ",!flag[i]);
		fflush(stdout);
	}
	return 0;
}
```

感谢各位管理员！

---

## 作者：ggwj (赞：2)

首先，当 $N = K + 1$ 时如何解决这个问题。我们用 $s_i$ 表示对应的查询

在第 $i$ 个查询中 $i, i+1, \dots, i+K-1$（如果超过 $N$，则从中减去 $N$）。举个例子，对于 $N=4, K=3$，会进行一下查询：
$$
\begin{aligned}

A_1 + A_2 + A_3 = s_1\\
A_2 + A_3 + A_4 = s_2\\
A_3 + A_4 + A_1 = s_3\\
A_4 + A_1 + A_2 = s_4\\

\end{aligned}
$$
在 $N$ 个查询中，每个 $A_1, A_2, \dots, A_N$ 在左侧会出现 $K$ 次。在这个例子中，由于 $K$ 是奇数，$A_1 + A_2 + \dots + A_N$ 的奇偶性与 $s_1 + s_2 + \dots + s_N$ 相同。所以，将两侧的总和取模可以得到 $A_1 + A_2 + \dots + A_N$ 的奇偶性。

然后，适当地进行差分，依次确定所有的 $A_1, A_2, \dots, A_N$。例如，当 $N=4, K=3$ 时，
$A_4 = (A_1 + A_2 + A_3 + A_4) - (A_1 + A_2 + A_3),$

所以 $A_4$ 的奇偶性由 $s_1$ 和 $A_1 + A_2 + A_3 + A_4$ 的奇偶性决定（对于 $A_1$，$A_2$ 和 $A_3$ 也同样适用）。因此，对于 $N=K+1$ 这种特殊情况，问题可以被解决。

实际上，下面解法可以适用于全部的 $N$。首先，就像我们在 $N=K+1$ 时做的那样，使用 $K+1$ 个查询来确定 $A_1, A_2, \dots, A_{K+1}$。对于$i = K+2, K+3, \dots, N$，在第 $i$ 个查询中 $1, 2, \dots, K-1, i$。然后，$A_i = s_i - (A_1 + A_2 + \dots + A_{K-1}),$

所以 $A_i$ 的奇偶性由 $A_1, A_2, \dots, A_{K-1}, s_i$ 决定。重复这个过程，可以确定所有 $A$ 元素的奇偶性。

**最后，终于完成了这道题！！！**

以下是实例代码 **（来自官方）** ：
###### 附上链接：https://atcoder.jp/contests/abc313/editorial/6928

```cpp
#include <bits/stdc++.h>
using namespace std;

void out(vector<int> v) {
  for (unsigned i = 0; i < v.size(); i++) {
    cout << v[i] << " \n"[i + 1 == v.size()];
  }
}
int main() {
  int N, K;
  cin >> N >> K;
  auto send = [&](vector<int> v) {
    for (auto& x : v) x++;
    cout << "? ", out(v);
    cout.flush();
    int x;
    cin >> x;
    return x;
  };
  vector<int> ans(N);
  {
    int r = 0;
    for (int i = 0; i < K + 1; i++) {
      vector<int> v;
      for (int j = 0; j < K + 1; j++)
        if (i != j) v.push_back(j);
      ans[i] = send(v);
      r ^= ans[i];
    }
    for (int i = 0; i < K + 1; i++) ans[i] ^= r;
  }
  {
    vector<int> v(K);
    int s = 0;
    for (int i = 0; i < K - 1; i++) v[i] = i, s ^= ans[i];
    for (int i = K + 1; i < N; i++) {
      v.back() = i;
      int t = send(v);
      ans[i] = s ^ t;
    }
  }
  cout << "! ", out(ans);
  cout.flush();
}
```


---

## 作者：hcywoi (赞：2)

[[abc313D Odd or Even]](https://atcoder.jp/contests/abc313/tasks/abc313_d)。

好有趣捏。

我们考虑 $N=K+1$。

设 $s_i$ 为 $\displaystyle\sum_{j\neq i}a_j\bmod 2$。

因为 $K$ 为奇数，我们可以得到 $\displaystyle\sum_{i=1}^{K+1}s_i\equiv\sum_{i=1}^{K+1}a_i\pmod2$。

所以 $a_i=\displaystyle\sum_{i=1}^{K+1}a_i\bmod 2-s_i$，即 $a_i=\displaystyle\sum_{i=1}^{K+1}s_i\bmod 2-s_i$。

我们考虑 $N\neq K+1$ 的情况。

我们先用 $N=K+1$ 的做法求出 $a_{1\sim K+1}$，然后对于 $\forall i\in[K+2, N]$，询问 $\{1, 2,\cdots, K-1, i\}$，即可得到 $a_i$。

时间复杂度：$\mathcal O(n^2)$。

[代码。](https://atcoder.jp/contests/abc313/submissions/44310531)

---

## 作者：CarroT1212 (赞：1)

怄火。虽说赛前看到分数不对劲就把这场 ABC unr 了但是这种题赛时没做出来真的是非常令人难绷。扔篇题解记一下。

首先很明显这个返回的 $A_{x_1}+A_{x_2}+\cdots+A_{x_K}$ 的奇偶性其实就是 $A_{x_1}\operatorname{xor}A_{x_2}\operatorname{xor}\cdots\operatorname{xor}A_{x_K}$。

可以找到一些性质：由于 $k$ 是奇数，$(A_{1}\operatorname{xor}A_{2}\operatorname{xor}\cdots\operatorname{xor}A_{K})\operatorname{xor}(A_{2}\operatorname{xor}A_{3}\operatorname{xor}\cdots\operatorname{xor}A_{K}\operatorname{xor}A_{K+1})\operatorname{xor}$ $(A_{3}\operatorname{xor}A_{4}\operatorname{xor}\cdots\operatorname{xor}A_{K+1}\operatorname{xor}A_1)\operatorname{xor}\cdots\operatorname{xor}(A_{K+1}\operatorname{xor}A_{1}\operatorname{xor}\cdots\operatorname{xor}A_{K-1})$ 就等于 $(A_{1}\operatorname{xor}A_{2}\operatorname{xor}\cdots\operatorname{xor}A_{K+1})$，因为每个数都被恰好异或了 $K$ 遍。再用这个值去异或上 $A_{1}\operatorname{xor}A_{2}\operatorname{xor}\cdots\operatorname{xor}A_{K}$ 就可以求出 $A_{K+1}$，其它数以此类推；

如果 $(A_{1}\operatorname{xor}A_{2}\operatorname{xor}\cdots\operatorname{xor}A_{K})$ 与 $(A_{2}\operatorname{xor}A_{3}\operatorname{xor}\cdots\operatorname{xor}A_{K}\operatorname{xor}A_{K+1})$ 的值相同，那么 $A_1$ 和 $A_{K+1}$ 也相同，否则不同，同样以此类推。

也就是说可以 $K+1$ 次询问确定 $A_{1\sim K+1}$，然后又可以通过每个 $A_{i}$ 加上一次询问来确定 $A_{i+K}$，正好 $N$ 次询问做完了。

赛时两个性质都想到了，就是不放一起用。

```cpp
ll n,k,a[N],s[N],sum;
int main() {
	scanf("%lld%lld",&n,&k);
	for (ll i=0;i<=k;i++) {
		printf("? ");
		for (ll j=0;j<k;j++) printf("%lld ",(i+j)%(k+1)+1);
		printf("\n"),flsh;
		scanf("%lld",&s[(i+k-1)%(k+1)]),sum^=s[(i+k-1)%(k+1)];
	}
	for (ll i=0;i<=k;i++) a[i]=sum^s[(i+k)%(k+1)];
	for (ll i=k+1;i<n;i++) {
		printf("? ");
		for (ll j=0;j<k;j++) printf("%lld ",i-j+1);
		printf("\n"),flsh;
		scanf("%lld",&s[i]),a[i]=a[i-k]^(s[i]!=s[i-1]);
	}
	printf("! ");
	for (ll i=0;i<n;i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：1)

## 思路

这题还是有一定思维难度的。

我觉得应该会有人和我一开始一样想到把每个元素问 $k$ 遍，但这样并不容易做 $(n,k)\neq 1$ 的情况。

我们先考虑简单的 $n=k+1$ 的情况。

这个我们就可以每个元素问 $k$ 遍，求和即可得到这 $k+1$ 个元素和的奇偶性，从而容易得到每个元素的奇偶性。

那扩展到更大的 $n$ 呢？我们可以对前 $k+1$ 个元素进行 $k+1$ 次询问，求出这其中每个元素的奇偶性。然后对于剩下的元素都和前 $k-1$ 个元素做一次询问，由于前 $k-1$ 个元素的奇偶性已知，因此可以得到剩下元素的奇偶性。总询问次数恰好 $n$ 次。

## 代码

```cpp
ll n,k,ans[1005],f[1005],sum;
int main(){
	cin>>n>>k;
	for(int i=1;i<=k+1;i++){
		cout<<"? ";
		for(int j=0;j<k;j++){
			if((i+j)%(k+1)==0)cout<<k+1<<" ";
			else cout<<(i+j)%(k+1)<<" ";
		}
		cout<<endl;
		cin>>ans[i];
	}
	for(int i=1;i<=k+1;i++)sum+=ans[i];
	sum%=2;
	f[k+1]=sum^ans[1];
	for(int i=2;i<=k+1;i++)f[i-1]=sum^ans[i];
	sum^=f[k+1];
	sum^=f[k];
	for(int i=k+2;i<=n;i++){
		cout<<"? ";
		for(int j=1;j<=k-1;j++)cout<<j<<" ";
		cout<<i<<endl;
		cin>>ans[i];
		f[i]=sum^ans[i];
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<f[i]<<" ";
	cout<<endl;
	return 0;
}
```


---

## 作者：Neil_Qian (赞：1)

# [ABC313D] Odd or Even 题解

## 题目描述

有一个长度为 $n$ 的 $01$ 序列，给定一个**奇数** $k$，每次可以询问任意 $k$ 个数的奇偶性，最多询问 $n$ 次，最后输出这个序列。$k<n\le 10^3$。

## 解决方案

一道很有趣的交互题，~~也是我第一次做出交互题~~。

转化：一次询问的结果就是所有数的异或值。

如果固定 $k-1$ 个数，每次询问不同的其它数，可以得到它们之间的关系：相同或不同，如下图，使用 $n-k+1$ 次询问，得到了 $a_k\sim a_n$ 之间的关系。不妨先令 $a_k=0$。（因为 $k-1$ 是偶数，红色部分取反对答案无影响）

![https://cdn.luogu.com.cn/upload/image_hosting/r5zmdp3h.png](https://cdn.luogu.com.cn/upload/image_hosting/r5zmdp3h.png)

还剩下 $k-1$ 次，显然要解决前 $k-1$ 个，每一次解决一个。不能利用上面的套路（因为有可能 $n-k+1<k-1$）。利用转化，每次去掉 $a_1\sim a_{k-1}$ 中的一个，再加上 $a_k$ 和 $a_{k+1}$ 进行运算。注意之前令 $a_k=0$，有可能不满足，随便找一个检查即可。恰好询问 $n$ 次。

## 代码

听说有人写了 $100$ 多行，恐怖。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,diff[1002],last=-1,i,j,s,sl,p[1002],res[1002],f,X;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(i=k;i<=n;i++){//第一部分
		cout<<"? ";
		for(j=1;j<=k-1;j++)cout<<j<<" ";
		cout<<i<<endl,cin>>s,res[i]=s;
		if(i==k)p[i]=0,sl=s;
		else{
			if(s==last)p[i]=p[i-1];
			else p[i]=(p[i-1]^1);
		}
		last=s;
	}
	for(i=1;i<=k-1;i++){//第二部分
		cout<<"? ";
		for(j=1;j<=k-1;j++)if(i!=j)cout<<j<<" ";
		cout<<k<<" "<<k+1<<endl,cin>>s,res[i]=s,p[i]=(sl^(s^p[k+1]));
	}
	for(j=1;j<=k-1;j++)if(j!=1)f^=p[j];
	if((f^p[k]^p[(k>=2?k+1:0)])!=res[1])X=1;//注意n=2,k=1的情况
	cout<<"! ";
	for(i=1;i<=n;i++)cout<<(p[i]^X)<<" ";
	return cout<<endl,0;
}
```


---

## 作者：zzx12345678 (赞：0)

# 首先
## 解释题面
给两个数 $n,k$，其中 $k$ 一定是奇数且 $k$ 一定小于 $n$；有 $n$ 个数，每个数可能是 $0$ 或 $1$；你可以进行不超过 $n$ 次询问来猜出这 $n$ 个数的值；每次询问输出 $k$ 个数，然后可以得到这 $k$ 个数之和模 $2$ 的值。

# 然后
## 寻找思路
我们可以考虑先求出 $[1,k+1]$ 的值，方法如下：

比如 $n=5$，$k=3$，答案是 $1$ $0$ $1$ $1$ $0$。


------------


首先 

$?\ 1\ 2\ 3$ 回答： $a_1=0$

然后 

$?\ 2\ 3\ 4$ 回答： $a_2=0$

因为其中都有 $2$ 和 $3$，只有 $1$ 和 $4$ 不同，但答案相同，说明 $1$ 和 $4$ 的值相同。

依次类推，

$?\ 1\ 3\ 4$ 回答： $a_3=1$

$?\ 1\ 2\ 4$ 回答： $a_4=0$

于是我们大致可以得到这样一个东西：$1$ 和 $4$ 相同，$2$ 和 $4$ 不同，$3$ 和 $4$ 相同。所以 $1$ 和 $3$ 和 $4$ 都是同一个值，而 $2$ 是另一个值；而无论那个值是什么，只要 $1$ 和 $3$ 相同，那对 $?\ 1\ 2\ 3$ 都是没影响的，所以 $2$ 的值就是 $a_1$。

------------
简单推理可得，只要看一下 $1$ 到 $k$ 中有多少相同多少不同，分别模 $2$，余 $1$ 的那个数所在的那类答案就是 $a_1$。由此我们可以得到 $1$ 到 $k+1$ 的答案。

------------
此时我们已经进行了 $k+1$ 次询问，只需再进行 $n-(k+1)$ 次询问即可用 $n$ 次询问得出 $n$ 个数的值。



# 良心AC代码，简单易懂
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define N 1000005
#define ll long long
using namespace std;
ll n,k,l,r,ans,u;  
ll a[N],pd[N],an[N],f[5]={1,0}; 
int main(){
	cin>>n>>k;
	
	cout<<"? ";//询问1-k 
	for(int i=1;i<=k;i++){
		cout<<i<<" ";
	} 
	cout<<endl; 
	cin>>a[1]; 
	
	for(int i=1;i<=k;i++){
		cout<<"? ";
		for(int j=1;j<=k+1;j++){//再进行k次询问，a数组记录每次询问得到的回答 
			if(i==j)continue;
			cout<<j<<" "; 
		} 
		cout<<endl;
		cin>>a[i+1]; 
	} 
	
	for(int i=2;i<=k+1;i++){  //统计 相同||不同 的个数 
		if(a[i]==a[1])l++;
		else r++; 
	} 
	
	//an数组记录1-k的答案 
	if(l%2==1){            //如果 相同=a[1] 
		for(int i=2;i<=k+1;i++){
			if(a[i]==a[1]){
				an[i-1]=a[1];
			}
			else an[i-1]=f[a[1]];
		}
	} 
	//cout<<f[]an[2]<<an[3];
	else{               //如果 不同=a[1] 
		for(int i=2;i<=k+1;i++){
			if(a[i]!=a[1]){
				an[i-1]=a[1];
			}
			else an[i-1]=f[a[1]];
		}
	}
	
	if(a[1]==a[2])an[k+1]=an[1];//记录k+1的答案 
	else an[k+1]=f[an[1]];
	
	for(int i=1;i<=k-1;i++){    //预处理1到k-1的ans; 
		ans+=an[i];
	}
	ans=ans%2;
	
	for(int i=k+2;i<=n;i++){//每次使用1到k-1和第i个数进行询问 
		cout<<"? ";
		for(int j=1;j<=k-1;j++){
			cout<<j<<" ";
		}
		cout<<i<<endl;
		cin>>u;//临时变量u 
		if(u==ans)an[i]=0;
		else an[i]=1;
	}
	
	cout<<"! ";    //输出答案 
	for(int i=1;i<=n;i++)cout<<an[i]<<" ";
	cout<<endl;
   return 0;
}
```


---

## 作者：mRXxy0o0 (赞：0)

# 题意

有一个包含 $N$ 个元素为 $0$ 或 $1$ 的序列，你最多可以提问 $N$ 次，每次询问 $K$ 个不同下标所代表的元素的异或和。当可以唯一确定这个序列时，输出它。

# 分析

观察到限制条件 $1\le K<N$，不妨从边界入手思考。$K=1$ 时不用说，考虑一下 $K=N-1$ 时。

很容易发现，问 $N$ 次，只有一种问法。例如 $N=4,K=3$ 时，问题就是 $(234),(134),(124),(123)$。

在满足题目条件 $K$ 为奇数的前提下，是一定可以推断出每一个元素的值的，只需要把所有回答异或起来就可以得到整个序列的异或和。然后依次与每个回答异或，就可以还原出原序列了。

据此，我们可以把整个序列分成数个长为 $K+1$ 的段，分别求解。

对于最后的一小部分，可以通过询问要求的和另外 $K-1$ 个已知元素的异或和得到。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e3+10;
int n,k,a[N],b[N];
inline void solve(int l,int r){
	int s=0;
	for(int i=l;i<=r;++i){
		cout<<"?";
		for(int j=l;j<=r;++j){
			if(i==j) continue;
			cout<<" "<<j;
		}
		cout<<endl;
		cin>>a[i];
		s^=a[i];
	}
	for(int i=l;i<=r;++i) b[i]=s^a[i];
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		if(i+k<=n){
			solve(i,i+k);
			i+=k;
		}
		else{
			int res=0;
			cout<<"?";
			for(int j=1;j<k;++j){
				cout<<" "<<j;
				res^=b[j];
			}
			cout<<" "<<i<<endl;
			cin>>b[i];
			b[i]^=res;
		}
	}
	cout<<"!";
	for(int i=1;i<=n;++i) cout<<" "<<b[i];
	cout<<endl;
	return 0;
}
```


---

## 作者：MYiFR (赞：0)

### 题目大意
这是一道自适应的交互题，给定两个整数 $N$ 和 $K$，其中 **$K$ 是奇数**，交互的结果是一个由 $0$ 和 $1$ 组成的序列 $A$。你需要给出至多 $N$ 次询问，每次询问可以获得序列 $A$ 中 $K$ 个元素的异或和，最后给出唯一确定的序列 $A$ 。

### 解题思路
首先注意到题目是自适应的，说明询问要足够“好”，使得结果唯一确定。

这题解法有挺多，有一种绝妙的方法是询问 $A_1\oplus A_2 \oplus A_3\cdots A_K$，$A_2\oplus A_3 \oplus A_4\cdots A_{K+1}$， $\cdots$，$A_N\oplus A_1 \oplus A_2\cdots A_{K-1}$，然后一套高斯消元就能秒掉。但赛时我不会高消，所以我就花了 $60$ 分钟思考加写代码糊了另一个很不绝妙的解法。

首先考虑当 $N=K+1$ 时怎么解。很显然我们可以问 $N$ 次，第 $i$ 次询问除了 $A_i$ 以外其他元素的异或和，记作 $s_i$。这个时候 **$K$ 是奇数**这个条件就很妙了，因为这样的话在 $\sum s_i$ 中，每个 $A_i$ 都恰好贡献了奇数次，结果也就是整个 $A$ 的异或和，记作 $sum$，那么显然 $A_i$ 就等于 $sum\oplus s_i$。

现在考虑广泛的情况。我们把 $A$ 分成若干组，前面的每组都有 $K+1$ 个元素，最后一组显然有 $N\bmod(K+1)$ 个元素。前面的若干组都可以用上述的解法求出，最后一组的每个元素就用前面的任意 $K-1$ 个元素和自身的异或和求出即可。

其实这个做法真的很扯，毕竟你最后一组都能这样解决了，为啥其他的不行呢？求出前 $K+1 $ 个元素的具体值，后面的也是询问前面的任意 $K-1$ 个元素和自身再异或上前 $K-1$ 个元素的异或和就能求出了是不是？但是赛时脑子不好使，于是就没这样写。
### AC 代码
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const int N=1e3+5;
int n,m,t,f[N],sumt;
int main(){
	cin>>n>>m;
	for(int i=0;i<n/(m+1);++i){
		int sum=0;
		for(int j=1;j<=m+1;++j){
			cout<<"? ";
			for(int k=i*(m+1)+1;k<=(i+1)*(m+1);++k){
				if(k-i*(m+1)==j) continue;
				cout<<k<<" ";
			}
			cout<<endl;
			cin>>f[i*(m+1)+j];
			sum^=f[i*(m+1)+j];
		}
		for(int j=1;j<=m+1;++j){
			f[i*(m+1)+j]^=sum;
		}
	}
	for(int i=n/(m+1)*(m+1)-m+2;i<=n/(m+1)*(m+1);++i) sumt^=f[i];
	int sum=0;
	for(int i=1;i<=n%(m+1);++i){
		cout<<"? ";
		for(int j=n/(m+1)*(m+1)-m+2;j<=n/(m+1)*(m+1);++j) cout<<j<<" ";
		cout<<n/(m+1)*(m+1)+i<<" ";
		cout<<endl;
		cin>>f[n/(m+1)*(m+1)+i];
		f[n/(m+1)*(m+1)+i]^=sumt;
	}
	cout<<"! ";
	for(int i=1;i<=n;++i) cout<<f[i]<<" ";
	cout<<endl;
	return 0;
}
//Ltwcfm.
```

---

## 作者：SnapYust (赞：0)

# 题目传送门

[Odd or Even](https://www.luogu.com.cn/problem/AT_abc313_d)

# 思路

提供一个与其他题解不太一样的**暴力做法**。

一道友好的交互题。我们首先观察数据范围，$N^2$ 和 $K^2$ 都可以做。很容易想到先摸清**每两个元素是否相同**，再根据询问结果判断孰奇孰偶，然后**逐步解决**，**暴力判断**：

- 当 $K=1$ 时，每个都问一遍，没有思维含量，直接过，需要 $N$ 次询问。

- 当 $K=N-1$ 时，我们发现对于两个下标 $i,j$，若 $(\sum^n_{k=1}{A_k}-A_i)\mod 2\ne(\sum^n_{k=1}{A_k}-A_j)\mod 2$，则 $A_i\ne A_j$，即 $A_i$ 与 $A_j$ 奇偶性不同。证明简单，遂略。然后即可解决，需要 $N$ 次询问。

- 当 $K\le\lceil\frac{N}{2}\rceil$ 时，我们可以这样询问来确定相同或不同：第一次询问 $1,2···K$，第二次询问 $1,2,···K+1$ 以此类推，确定了 $K$ 到 $N$ 的元素，然后询问 $N-K+1,N-K+2···N$，确定了这些元素的奇偶，前面 $K-1$ 个元素也可以很好判断出来了。对于第 $K-1$ 个元素，因为我们确定了其他元素，也知道前 $K$ 个元素的奇偶性，所以我们也可以推出来。需要 $N$ 次询问。

- 当 $K>\lceil\frac{N}{2}\rceil$ 时，我们可以用同样的策略，但我们要换个方向，从后往前推，因为从前往后推的话因为 $K$ 比较大，所以就不能确定后面 $N-K+1$ 个元素的值，需要 $N$ 或 $N-1$ 此询问，但 $N$ 次询问的代码量会少一些。

然后这道题的思路就讲完了，如果您认为以上写的有点怪，可以看以下代码。因为本人的思路是暴力思路，所以可读性会好一点（？大雾）。

# Code

最坏时间复杂度 $O(N^2)$，空间复杂度 $O(N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1005]={0},m2,m3,c2=0,c3=0;
//当 K=1 时
void solve1(){
    for(int i=1;i<=n;i++){
        cout<<"? "<<i<<endl;
        cin>>a[i];
    }
}
//当 K=N-1 时
void solve2(){
    int tmp;
    cout<<"? ";
    for(int i=2;i<=n;i++)
        cout<<i<<' ';
    cout<<endl;
    cin>>tmp;
    a[1]=2;
    for(int i=2;i<=n;i++){
        cout<<"? ";
        for(int j=1;j<=n;j++)
            if(i!=j)cout<<j<<' ';
        cout<<endl;
        int tmpp;
        cin>>tmpp;
        if(tmp==tmpp)a[i]=2;
        else a[i]=3;
    }
    for(int i=2;i<=n;i++){
        if(a[i]==2)c2++;
        else c3++;
    }
    if(c2%2==tmp)m2=1,m3=0;
    else m2=0,m3=1;
    for(int i=1;i<=n;i++){
        if(a[i]==2)a[i]=m2;
        else a[i]=m3;
    }
}
//当 K<=(N+1)/2 时
void solve3(){
    int tmp;
    cout<<"? ";
    for(int i=1;i<=k;i++)
        cout<<i<<' ';
    cout<<endl;
    cin>>tmp;
    a[k]=2;
    for(int i=k+1;i<=n;i++){
        cout<<"? ";
        for(int j=1;j<k;j++)
            cout<<j<<' ';
        cout<<i<<endl;
        int tmpp;
        cin>>tmpp;
        if(tmp==tmpp)a[i]=2;
        else a[i]=3;
    }
    cout<<"? ";
    for(int i=n-k+1;i<=n;i++)
        cout<<i<<' ';
    cout<<endl;
    int tmpp;
    cin>>tmpp;
    for(int i=n-k+1;i<=n;i++){
        if(a[i]==2)c2++;
        else c3++;
    }
    if(c2%2==tmpp)m2=1,m3=0;
    else m2=0,m3=1;
    int tmppp=0;
    for(int i=n-k+2;i<=n;i++){
        if(a[i]==2)tmppp+=m2;
        else tmppp+=m3;
    }
    tmppp%=2;
    for(int i=1;i<=k-2;i++){
        cout<<"? "<<i<<' ';
        for(int j=n-k+2;j<=n;j++)
            cout<<j<<' ';
        cout<<endl;
        int tmpppp;
        cin>>tmpppp;
        if(tmppp==tmpppp)a[i]=0;
        else a[i]=1;
    }
    for(int i=k;i<=n;i++){
        if(a[i]==2)a[i]=m2;
        else a[i]=m3;
    }
    int tmpppp=0;
    for(int i=1;i<=k-2;i++)
        tmpppp+=a[i];
    tmpppp+=a[k];
    tmpppp%=2;
    if(tmpppp==tmp)a[k-1]=0;
    else a[k-1]=1;
}
//其他情况
void solve4(){
    int tmp;
    cout<<"? ";
    for(int i=n-k+1;i<=n;i++)
        cout<<i<<' ';
    cout<<endl;
    cin>>tmp;
    a[n-k]=2;
    for(int i=n-k+1;i<=n;i++){
        cout<<"? ";
        for(int j=n-k;j<=n;j++)
            if(i!=j)cout<<j<<' ';
        cout<<endl;
        int tmpp;
        cin>>tmpp;
        if(tmp==tmpp)a[i]=2;
        else a[i]=3;
    }
    for(int i=n-k+1;i<=n;i++){
        if(a[i]==2)c2++;
        else c3++;
    }
    if(c2%2==tmp)m2=1,m3=0;
    else m2=0,m3=1;
    int tmpp=0;
    for(int i=n-k+2;i<=n;i++){
        if(a[i]==2)tmpp+=m2;
        else tmpp+=m3;
    }
    tmpp%=2;
    for(int i=1;i<=n-k-1;i++){
        cout<<"? "<<i<<' ';
        for(int j=n-k+2;j<=n;j++)
            cout<<j<<' ';
        cout<<endl;
        int tmppp;
        cin>>tmppp;
        if(tmpp==tmppp)a[i]=0;
        else a[i]=1;
    }
    for(int i=n-k;i<=n;i++){
        if(a[i]==2)a[i]=m2;
        else a[i]=m3;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    if(k==1)solve1();
    else if(k==n-1)solve2();
    else if(k<=(n+1)/2)solve3();
    else solve4();
    cout<<"! ";
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}
```

---

