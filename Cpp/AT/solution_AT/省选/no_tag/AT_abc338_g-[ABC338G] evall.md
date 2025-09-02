# [ABC338G] evall

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_g

文字列 $ S $ が与えられます。$ S $ の各文字は `123456789+*` のいずれかで、$ S $ の先頭と末尾の文字は数字であり、$ S $ の中で数字でない文字どうしが隣接することはありません。

整数の組 $ i,\ j $（$ 1\ \leq\ i\ \leq\ j\ \leq\ |S| $）に対して、$ \mathrm{eval}(S_{i..j}) $ を以下のように定義します。

- $ S $ の $ i $ 文字目と $ j $ 文字目がともに数字であれば、$ \mathrm{eval}(S_{i..j}) $ は $ S $ の $ i $ 文字目から $ j $ 文字目まで（両端含む）を通常の数式として評価した結果とする（`*` は乗算とする）。例えば、$ S\ = $ `1+2*151` のとき、$ \mathrm{eval}(S_{1..6})\ =\ 1\ +\ 2\ \times\ 15\ =\ 31 $ である。
- そうでなければ、$ \mathrm{eval}(S_{i..j}) $ は $ 0 $ とする。
 
$ {\displaystyle\ \sum_{i=1}^{|S|}\ \sum_{j=i}^{|S|}\ \mathrm{eval}(S_{i..j})} $ を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^6 $
- $ S $ の各文字は `123456789+*` のいずれかである。
- $ S $ の先頭と末尾の文字は数字である。
- $ S $ の中で数字でない文字どうしが隣接することはない。
 
### Sample Explanation 1

$ \mathrm{eval}(S_{i..j}) $ が $ 0 $ でない場合は以下の通りです。 - $ \mathrm{eval}(S_{1..1})\ =\ 1 $ - $ \mathrm{eval}(S_{1..3})\ =\ 1\ +\ 2\ =\ 3 $ - $ \mathrm{eval}(S_{1..5})\ =\ 1\ +\ 2\ \times\ 3\ =\ 7 $ - $ \mathrm{eval}(S_{1..6})\ =\ 1\ +\ 2\ \times\ 34\ =\ 69 $ - $ \mathrm{eval}(S_{3..3})\ =\ 2 $ - $ \mathrm{eval}(S_{3..5})\ =\ 2\ \times\ 3\ =\ 6 $ - $ \mathrm{eval}(S_{3..6})\ =\ 2\ \times\ 34\ =\ 68 $ - $ \mathrm{eval}(S_{5..5})\ =\ 3 $ - $ \mathrm{eval}(S_{5..6})\ =\ 34 $ - $ \mathrm{eval}(S_{6..6})\ =\ 4 $ 以上の合計は $ 1+3+7+69+2+6+68+3+34+4\ =\ 197 $ です。

## 样例 #1

### 输入

```
1+2*34```

### 输出

```
197```

## 样例 #2

### 输入

```
338*3338*33338*333338+3333338*33333338+333333338```

### 输出

```
527930018```

# 题解

## 作者：Drimpossible (赞：6)

借鉴 qiuzx_ 大佬的做法。

## 思路：
DP

设 $f_i$ 表示以 $i$ 为左端点的算式和，$ap$ 为第一次出现 `+` 的位置，$tp$ 为在 $i$ 之后 $ap$ 之前第一次出现 `*` 的位置，$cnt_i$ 为从 $i$ 到最后出现的数字个数。

显然到在 $i$ 后面第一次出现加法的位置就可以直接累加转移，有：
$$
f_{ap+1}+\text{eval}(S_{i...ap-1})\times cnt_{ap+1}
$$

因为对于 $ap$ 之后的每一个数字，$i$ 到 $ap-1$ 的贡献都会被计算一次，所以相乘。

对于 $i$ 到 $ap$ 中间所有的乘法都要单独算一遍：
$$
\sum_{j<ap} \text{eval}(S_{i...j})
$$

可以再做一个 DP。

具体地，记 $s0_i$ 表示 $i$ 到 $tp-1$ 所有选择数字方式的总和，$s1_i$ 表示到 $ap$ 之前所有连乘的总和。那么可以只在 $i$ 到 $tp-1$ 这一段里面选，也可以把这一段选满连着后面的一起，所以转移有：
$$
s0_i=s0_{i+1}+S_i \times \sum_{j=0}^{j\leq tp-i-1} 10^j
$$
$$
s1_{i}=s1_{tp+1}\times \text{eval}(S_{i...tp-1})+s0_i
$$

所以 $f_i=f_{ap+1}+\text{eval}(S_{i...ap-1})\times cnt_{ap+1}+s1_i$，转移中的两个 $\text{eval}$ 可以在扫的时候单独处理出来，$10$ 的幂可以前缀和预处理，时间复杂度 $O(|S|)$。

答案即为 $\sum f_i$。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
const int mod=998244353;
int n,pw[N],spw[N];
int f[N],cnt[N],s[2][N];
char a[N];
signed main(){
	cin>>(a+1);
	n=strlen(a+1);
	pw[0]=spw[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=pw[i-1]*10%mod,
		spw[i]=(spw[i-1]+pw[i])%mod;
	int tp=n+1,ap=n+1,nw=0,sr=1,ans=0;
	for(int i=n;i;i--){
		cnt[i]=cnt[i+1]+isdigit(a[i]);
		if(a[i]=='+'){
			tp=ap=i,nw=0,sr=1;
			continue;
		}
		if(a[i]=='*'){
			tp=i,(sr*=nw)%=mod,nw=0;
			continue;
		}
		int x=a[i]-'0';
		(nw+=x*pw[tp-i-1])%=mod;
		s[0][i]=(s[0][i+1]+x*spw[tp-i-1])%mod;
		if(ap==tp)s[1][i]=s[0][i];
		else s[1][i]=(s[1][tp+1]*nw%mod+s[0][i])%mod;
		f[i]=(sr*nw%mod*cnt[ap+1]%mod+f[ap+1]+s[1][i])%mod;
		(ans+=f[i])%=mod;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Caiest_Oier (赞：5)

# [AT_abc338_g](https://www.luogu.com.cn/problem/AT_abc338_g)      

为啥这是 2500。      

考虑 dp，对于一个当前正在计算的式子，我们可以将其看成是若干个乘积式相加（由加号分隔），将式子分为三部分，一部分是目前明确已经计算完的乘积式的和，一部分是当前正在计算的乘积式中，末尾不会再被添数字的乘积，一部分是当前乘积式的值。      

比如说式子 $34\times 12+45+56\times 76\times 4$，三部分分别是 $34\times 12+45$，$56\times 76$，$56\times 76\times 4$，容易发现维护这三个值，就能完成所有转移。因为这个东西是可加的，所以令 $dp_{i,0/1/2}$ 记录以 $i$ 为结尾的式子的三种值的和，直接转移即可。     

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,dp[1000003][3],ans,cnt;
string s;
signed main(){
	ios::sync_with_stdio(false);
	cin>>s;
	n=s.length();
	if(s[0]>='1'&&s[0]<='9'){
		dp[1][0]=0;
		dp[1][1]=1;
		dp[1][2]=s[0]-'0';
		ans=s[0]-'0';
		cnt++;
	}
	for(int i=2;i<=n;i++){
		if(s[i-1]>='1'&&s[i-1]<='9'){
			dp[i][0]=dp[i-1][0];
			dp[i][1]=(dp[i-1][1]+1)%MOD;
			dp[i][2]=(dp[i-1][2]*10+(s[i-1]-'0')*(1+dp[i-1][1]))%MOD;
			cnt++;
			ans=(ans+dp[i][0]+dp[i][2])%MOD;
			continue;
		}
		if(s[i-1]=='+'){
			dp[i][0]=(dp[i-1][0]+dp[i-1][2])%MOD;
			dp[i][1]=cnt;
			dp[i][2]=0;
			continue; 
		}
		if(s[i-1]=='*'){
			dp[i][0]=dp[i-1][0];
			dp[i][1]=dp[i-1][2];
			dp[i][2]=0;
			continue;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OldDriverTree (赞：5)

第二次手切 G 题祭。

# Solution
考虑建出表达式树，在表达式树上 $\texttt{DP}$。

设 $f_u$ 表示子树 $u$ 内的答案。

对于根节点 $u$ 为 $+$ 的情况，状态转移方程就为：
$$
\begin{aligned}
f_u&=f_{ls}+f_{rs}+\sum_{suf}\sum_{pre} suf+pre\text{（这里的 $suf$ 表示左子树里的合法后缀的值，$pre$ 表示右子树里的合法前缀的值）}\\
&=f_{ls}+f_{rs}+\sum_{suf}\sum_{pre} suf+\sum_{suf}\sum_{pre} pre\\
&=f_{ls}+f_{rs}+\text{右子树内的合法前缀个数}\times(\sum_{suf} suf)+\text{左子树的合法后缀个数}\times(\sum_{pre}pre)
\end{aligned}
$$

考虑再维护 $pre_u$ 表示 $u$ 子树内所有前缀的和，$suf_u$ 表示 $u$ 子树内的所有后缀的和，$size_u$ 表示 $u$ 子树内合法前 / 后缀的个数，由于合法前缀的个数等于合法后缀的个数，所以只需要维护一个。

对于根节点 $u$ 为 $+$ 的情况，现在状态转移方程就为：

$$f_u=f_{ls}+f_{rs}+suf_{ls}\times size_{rs}+pre_{rs}\times size_{ls}$$

$$
\begin{aligned}
pre_u&=pre_{ls}+\sum_{pre} val+pre\text{（这里的 $val$ 表示左子树表达式的值，$pre$ 表示右子树里所有前缀的值）}\\
&=pre_{ls}+pre_{rs}+val\times size_{rs}
\end{aligned}
$$
再维护一个 $val_u$，表示 $u$ 子树表达式的值。

对于根节点 $u$ 为 $+$ 的情况，现在状态转移方程就为：

$$f_u=f_{ls}+f_{rs}+suf_{ls}\times size_{rs}+pre_{rs}\times size_{ls}$$

$$pre_u=pre_{ls}+pre_{rs}+val_{ls}\times size_{rs}$$

$$suf_u=suf_{rs}+suf_{ls}+val_{rs}\times size_{ls}$$

$$size_u=size_{ls}+size_{rs}$$

$$val_u=val_{ls}+val_{rs}$$

对于根节点 $u$ 为 $\times$ 的情况，状态转移方程就为：

$$f_u=f_{ls}+f_{rs}+suf_{ls}pre_{rs}$$

$$pre_u=pre_{ls}+val_{ls}\times pre_{rs}$$

$$suf_u=suf_{rs}+val_{rs}\times suf_{ls}$$

$$size_u=size_{ls}+size_{rs}$$

$$val_u=val_{ls}\times val_{rs}$$

对于根节点 $u$ 为数字的情况，考虑从高位往低位添加数字，如果当前添加的数为第 $i$ 个，数字为 $num$，状态转移方程就为：

$$f_u=f_u+suf_u\times 10+num\times i$$

$$pre_u=pre_u+val_u\times 10+num$$

$$suf_u=suf_u\times 10+num\times i$$

$$val_u=val_u\times 10+num$$

$$size_u=size_u+1$$

时间复杂度 $O(n)$。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
const int mod=998244353;

struct modint
{
	int x;
	modint(int v=0):x( (v%mod+mod)%mod){}
	modint inv() { return (*this)^(mod-2); }
	modint operator =(int y) { x=(y%mod+mod)%mod; return *this; }
	modint operator +=(modint y) { x=(x+y.x)%mod; return *this; }
	modint operator -=(modint y) { x=(x-y.x+mod)%mod; return *this; }
	modint operator *=(modint y) { x=1ll*x*y.x%mod; return *this;}
	modint operator /=(modint y) { (*this)*=y.inv(); return *this; }
	modint operator ^=(int b)
	{
		modint a=*this;
		(*this)=1;
		while (b) {
			if (b&1) (*this)*=a;
			a*=a,b>>=1;
		}
		return *this;
	}
	friend modint operator +(modint x,modint y) { return x+=y; }
	friend modint operator -(modint x,modint y) { return x-=y; }
	friend modint operator *(modint x,modint y) { return x*=y; }
	friend modint operator /(modint x,modint y) { return x/=y; }
	friend modint operator ^(modint x,int y) { return x^=y; }
	friend istream &operator >>(istream &is,modint &x) { int t; is>>t,x=t; return is; }
	friend ostream &operator <<(ostream &os,modint x) { return os<<x.x; }
};

struct node {
	modint ans,pre,suf,val,size;
};
char s[N];
int A[N],B[N];

node solve(int l,int r)
{
	node res;
	if (l<=A[r]) //区间内含 +
	{
		node ls=solve(l,A[r]-1),rs=solve(A[r]+1,r);
		res.ans=ls.ans+rs.ans+ls.suf*rs.size+ls.size*rs.pre;
		res.pre=ls.pre+ls.val*rs.size+rs.pre;
		res.suf=rs.suf+rs.val*ls.size+ls.suf;
		res.size=ls.size+rs.size;
		res.val=ls.val+rs.val;
	}
	else if (l<=B[r]) //区间内包含 *
	{
		node ls=solve(l,B[r]-1),rs=solve(B[r]+1,r);
		res.ans=ls.ans+rs.ans+ls.suf*rs.pre;
		res.pre=ls.pre+ls.val*rs.pre;
		res.suf=rs.suf+rs.val*ls.suf;
		res.size=ls.size+rs.size;
		res.val=ls.val*rs.val;
	}
	else { //区间内只含一个数字
		res.ans=res.pre=res.suf=res.val=s[l]&15,res.size=r-l+1;
		for (int i=l+1;i<=r;i++) if (isdigit(s[i]) )
		{
			res.ans=res.ans+res.suf*10+(s[i]&15)*(i-l+1);
			res.pre=res.pre+res.val*10+(s[i]&15);
			res.suf=res.suf*10+(s[i]&15)*(i-l+1);
			res.val=res.val*10+(s[i]&15);
		}
	}
	return res;
}
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for (int i=1,a=0,b=0;i<=n;i++)
	{
		if (s[i]=='+') a=i;
		else if (s[i]=='*') b=i;
		A[i]=a,B[i]=b;
	}
	cout<<solve(1,n).ans;
	return 0;
}
```

---

## 作者：0x3F (赞：4)

怎么没人写无脑做法。

我们先考虑按顺序加入字符时，怎么计算答案。我们记当前已经确定的和为 $s$，已经确定的乘积为 $p$，当前的数为 $n$，则按照以下方式进行操作：

1. 初始时 $s\gets0,p\gets1,n\gets0$。

2. 读入数字 $x$ 时，$n\gets10n+x$。

3. 读入乘号时，$p\gets pn,n\gets0$。

4. 读入加号时，$s\gets s+p,p\gets1,n\gets0$。

5. 结束时 $s\gets s+p$，得到的 $s$ 即为答案。

我们想把这些操作写成矩阵的形式。但很遗憾，$p\gets pn$ 这一个操作看起来不是很线性。

处理的方法也很简单：我们不维护 $n$，而直接维护 $pn$ 的值，这样就可以做了。

那么怎么处理所有区间求和呢？我们只需要从左到右扫一遍维护之前的所有数字位置乘到当前位置的矩阵之和，并且在数字位置更新答案即可。

时间复杂度 $\mathcal{O}(\lvert S\rvert)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
struct mat {
    int data[4][4];
};
inline mat operator + (mat lhs, mat rhs) {
    mat ans;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            ans.data[i][j] = (lhs.data[i][j] + rhs.data[i][j]) % mod;
        }
    }
    return ans;
}
inline mat operator * (mat lhs, mat rhs) {
    mat ans;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            ans.data[i][j] = 0;
            for (int k = 0; k <= 3; k++) {
                ans.data[i][j] = (ans.data[i][j] + (long long) lhs.data[i][k] * rhs.data[k][j]) % mod;
            }
        }
    }
    return ans;
}
const mat O = {{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
}};
const mat I = {{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
}};
const mat D = {{
    {1, 0, 0, 0},
    {0, 10, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
}};
const mat M = {{
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 1}
}};
const mat A = {{
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 0, 1}
}};
int main() {
    string str;
    mat S = O;
    int ans = 0;
    cin >> str;
    for (char ch: str) {
        switch (ch) {
            case '+': {
                S = A * S;
                break;
            }
            case '*': {
                S = M * S;
                break;
            }
            default: {
                mat E = D;
                E.data[1][2] = ch - '0';
                S = E + E * S;
                ans = (ans + ((S.data[0][2] + S.data[0][3]) % mod + (S.data[1][2] + S.data[1][3]) % mod) % mod) % mod;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Shunpower (赞：3)

AT 的官方题解有点太猛了，反正我是没怎么看明白。根据 CF 上一个紫名老哥的思路推了一个不太一样的做法。

考虑记 $f^{+}_ i$ 表示以 $i$ 为左端点的所有合法表达式的值，$f^{* }_ i$ 表示以 $i$ 为左端点，**不跨越任何加号**的所有合法表达式的值，$f_ i$ 表示以 $i$ 为左端点，**不跨越任何符号**（即连续数字段）的所有合法表达式的值。为了表达方便，记 $\text{eval}(l,r)$ 表示 $[l,r]$ 作为表达式时的值。

显然答案为 $\sum\limits_{i=1}^n f^{+}_ i$。

考虑从右到左转移。枚举位置 $i$，获取 $f^{+}_ i,f^{* } _ i,f_i$。

## 如何维护 $f^+_ i$

记右边第一个加号的位置 $la$。容易发现，$f^+_ i$ 相对于 $f^+_ {la+1}$ 来说，所有右端点在 $la$ 之后的表达式，都额外加上了 $\text{eval}(i,la-1)$，而所有右端点在 $la$ 之前的表达式在 $f^+_ {la+1}$ 中没有计入答案。但是，我们发现在 $[i,la)$ 之间没有加号，所以我们容易发现这一部分的贡献是 $f^{* }_ i$。

所以，记右侧第一个加号 $la$，$(la,|S|]$ 中数字的数量 $c$，可以得到 $f^+_ i$ 的转移：

$$
f^+_ i\gets f^+_ {la+1}+c\cdot \text{eval}(i,la-1)+f^* _ i
$$

$la,c$ 都是好维护的。

## 如何维护 $f^{* }_ i$

考虑分类讨论 $S_{i+1}$ 处的情况。

1. $S_{i+1}$ 为 $\texttt{+}$。显然，根据定义可以得到 $f^{* }_ i\gets S_i$（当然是要转换为数字之后的 $S_i$，下文同理）。
2. $S_{i+1}$ 为 $\texttt{* }$。显然 $f^{* }_ {i+2}$ 处的每一个表达式的值都多乘上了一个 $S_i$，再加上 $S_i$ 本身，可以得到 $f^{* }_ i\gets S_i+S_i\cdot f^{* }_ {i+2}$。
3. $S_{i+1}$ 为数字。这里会稍微麻烦一点。记右边第一个符号的位置为 $lm$。可以注意到，$f^{* }_ {i+1}$ 可以在 $lm$ 处切一刀分为两部分，一部分没有任何符号就是 $f_{i+1}$；另一部分可以进行转移，就是 $\text{eval}(i,lm-1)\cdot f^{* }_ {lm+1}$，但是需要注意，如果 $S_{lm}$ 不是乘号就不能有这一部分的转移，但可以有前一部分。于是合起来可以得到 $f^{* }_ i\gets f_{i+1}+\text{eval}(i,lm-1)\cdot f^{* }_ {lm+1}\cdot [S_{lm}=\texttt{*}]$。

$lm$ 是好维护的。

## 如何维护 $f_i$

考虑 $f_i$ 从 $i+1$ 到 $i$ 的变化。

记 $i+1$ 及其右侧到第一个符号之前的数字个数为 $ca$。

$f_{i+1}$ 展开后，可以发现形如 $ca$ 个数字的和。进行 $f_i\gets f_{i+1}$ 的转移形如在这些数字前面都加上一位再求和，再加上 $S_i$ 本身。容易得到变化量就是式子：$S_i\times \sum\limits_{j=0}^{ca} 10^j$。使用等比数列求和或者前缀和都可以算出来。

于是有：

$$
f_i\gets f_{i+1}+S_i\times \sum\limits_{j=0}^{ca} 10^j
$$

$ca$ 是好维护的。

## 如何维护 $\text{eval}(i,la-1)$ 以及 $\text{eval}(i,lm-1)$

考虑先维护 $\text{eval}(i,lm-1)$。显然，$i$ 处如果是符号，$\text{eval}(i,lm-1)=0$；反之，$\text{eval}(i,lm-1)$ 每次在 $\text{eval}(i+1,lm-1)$ 的前面增加一位，利用前面记下的 $ca$ 可以得到：

$$
\text{eval}(i,lm-1)\gets \text{eval}(i+1,lm-1) +S_i\cdot 10^{ca}
$$

而想维护 $\text{eval}(i,la-1)$ 也因为维护了 $\text{eval}(i,lm-1)$ 后变得易如反掌。由于 $i$ 到 $la-1$ 之间不是乘号就是没有符号，我们把它除掉一个 $\text{eval}(i,lm-1)$ 之后剩下的就是 $\text{eval}(lm+1,la-1)$，那么我们进一步考虑维护 $\text{eval}(lm+1,la-1)$。

对于 $i$ 处是加号，$\text{eval}(lm+1,la-1)=1$。对于 $i$ 处是乘号，因为相当于拼了一个新的数进来乘，我们选择先更新 $\text{eval}(lm+1,la-1)\gets \text{eval}(lm+1,la-1)\cdot \text{eval}(i+1,lm-1)$ 再更新 $lm$ 即可。

回到原来就有 $\text{eval}(i,la-1)\gets \text{eval}(lm+1,la-1)\cdot \text{eval}(lm+1,la-1)$。

把以上所有都维护一下就能 A 掉本题。注意实现时的常数。虽然要维护很多东西但是整体而言是非常好调的。

[我写的代码](https://atcoder.jp/contests/abc338/submissions/49771763)，比较难看，变量名起得一团糟，但是对着式子看应该还是能明白什么变量表示题解里面的什么含义。此外，代码里维护 $f^{* }_ i$ 的第三种情况（$S_{i+1}$ 是数字）用了一种考虑 $f^{* }_ i$ 与 $f^{* }_ {i+1}$ 差异的方法，读者也可以进行一些思考。

这个做法通过提前预处理 $10$ 的幂及其前缀和等做到 $\mathcal O(|S|)$。但是我的代码写成了 $\mathcal O(|S|\log V)$。

---

## 作者：Cindy_Li (赞：2)

# ABC338G 题解

计数题，没有太多思维难度，就是麻烦。

显然 `+` 和 `*` 是比较难搞的，应考虑子问题。

复杂度要求线性，考虑每个位置的贡献。

## Case 1：只有数字

Ex: `1234`

考虑 `2` 的贡献，枚举一下看看。

- $12=1\times 10+2\times1$
- $123=1\times 100+2\times10+3\times1$
- $1234=\dots$
- $2=2\times1$
- $23=2\times 10+3\times 1$
- $234=\dots$

`2` 贡献了 $2\times 111=222$ 次。

**引理：总贡献次数 $=$ 左边 $\times$ 右边**

例如：`12` 中 `2` 贡献了 $2$ 次，`234` 中 `2` 贡献了 $111$ 次，`1234` 中正好是 $2\times111$ 次。

设当前是第 $p$ 位，长度为 $n$，则总贡献次数为 $p\times\sum\limits_{i=0}^{n-p} 10^i$。

证明显然，请读者自行完成。

## Case 2：只有数字 & `+`

Ex: `99+1234+999`

仍然考虑 `2` 的贡献次数，请读者仿照 Case 1 自行枚举。

发现第一个加号前和第二个加号后的内容是不影响答案的，故可以**只考虑两加号之间的部分**，最后加上前后长度即可。

设当前位置、后面第一个加号位置为 $s,t$，当前**忽略加号**的位置为 $pd$，总数字量为 $n$，则总贡献次数为 
$pd\times\left(\sum\limits_{i=0}^{t-s-1} 10^i+ (n-pd)\times10^{t-s-1}\right)$。

~~好长的式子~~。

## Case 3：数字 & `+` & `*`（原问题）

先解决算重复的问题。

比如 `2*3` 中，$2\times3$ 只应该被计算一次，但如果计算贡献，会在 `2` 和 `3` 上分别统计一次，就算重了。

**key：只在最后一个数上统计乘法答案（结合律）。**

（当然你也可以在第一个数上计算，只不过从左到右扫，在最后统计更方便）

`2*3` 中，`2` 贡献 $1$ 次，`3` 贡献 $2+1=3$ 次。

Ex: `99+345*456*567*12+999`

通过 Case 2 我们发现，可以把整个串用 `+` 号分割，每一小段单独考虑。

故统计 `2` 的答案，只需要看 `345*456*567*12` 这一部分，请读者自行枚举。

发现乘法对 `2` 的贡献就是`345*456*567` 的后缀贡献和，这是很容易 dp 计算的。具体说，就是每个数计算和，乘上后面的数，滚雪球。

$\big[(3\times 100+4\times20+5\times3)\times 456+(4\times100+5\times20+6\times3)\big]\times 567 + \dots$

加法的贡献和 Case 2 相同，不多赘述。

注意：乘法中非最后一个数的，向右只考虑乘号前、加号后的部分（反之亦然）！

例如 `3` 只考虑 `345` 和 `999`，乘法部分不算。

## 小结

- 分成 $3$ 个子问题考虑。
- 从简单开始枚举。
- 考虑每个位置的贡献。
- 分治（左右 & 符号分段）。
- 相同的部分合并计算。
- 乘法只算一次。

代码不难写，注意下标 & 取模的细节。

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给定一个由 $1\sim 9$ 的数字、`+` 和 `*` 组成的字符串。定义一个区间的权值是其表达式的结果，不合法则为 $0$。

求所有区间的权值之和。

## 题目分析

这种题肯定要考虑扫描线，对右端点扫描线，维护每个左端点对应的答案。

我们考虑在每个合法表达式结尾加入 $k$ 对其取值 $w$ 的影响。

 1. 对于没有符号的表达式，$w$ 会变为 $10w+k$。
 2. 对于有乘号而没有加号的表达式，设其最后一项为 $A$。显然这里所有的 $A$ 都一样，是个常数。则新的最后一项变为 $10A+k$，$w$ 就得乘上 $\frac{10A+k}{10A}$。
 3. 对于有加号的表达式，设最后一个加号后面的表达式的值为 $B$，显然 $B$ 也是常数，且在上一类时已经被处理了。变为 $C=\frac{10A+k}{10A}B$，则这一类表达式的值均加上 $C-B$。

只需要扫描线的时候维护这三类表达式的数量、和，以及 $A$ 和 $B$ 的值就行了，~~赛时直接线段树还 T 了~~。

复杂度 $O(n\log V)$，瓶颈在于求 $10A$ 的逆元。

代码还是简单的，稍微有一点小细节，注意计算的先后即可，我赛时的代码是一坨。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L (x<<1)
#define R (L|1)
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e6+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=(1LL<<31)-1;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
string s;
int n,ans,cl,cm,cr,sl,sm,sr,wl,wL;
void Main(){
	cin >>s,n=s.length(),s='#'+s;
	//build(Root);
	repn(i)if(s[i]=='+'){
		add(cl,Add(cm,cr));
		add(sl,Add(sm,sr));
		cm=cr=sm=sr=0;
		wl=wL=0;
	}else if(s[i]=='*'){
		add(cm,cr),add(sm,sr);
		cr=sr=0;
		wL=0;
	}else {
		int k=s[i]-'0';
		add(cr,1);
		int w=wL,W=Add(mul(w,10),k);
		bool fl=0;
		if(!w)w=1,fl=1;
		int ms=wl;
		int K=mul(W,INV(w));
		Mul(sr,10),add(sr,mul(cr,k));
		Mul(sm,K);
		if(wl==0)wl=1;
		Mul(wl,K);
		int nw=wl;
		int del=Red(nw,ms);
		add(sl,mul(del,cl));
		wL=Add(k,mul(wL,10));
		add(ans,Add(sl,Add(sm,sr)));
	}
	cout <<ans;
}
signed main(){
	int T=1;
	while(T--)Main();
    return 0;
}
```


---

## 作者：zhongpeilin (赞：1)

$\Huge Atcoder \ Beginner \ Contest \ 338 \ Problem \ G$
## 题目大意：
有一个数学的字符串，只有 `123456789+*` 这些字符，现在想让你求出他每一个子串的值，模 `998244353`。
## 解题思路：
首先我们设 $solve_{l, r}$ 表示区间 $l \sim r$ 的所有字段的和，由于数学中是先算乘法再算加法，那么我们考虑如果 $l \sim r$ 这一段中：
1. 有加号的话，我们可以任意找一个加号，设他在 $m$ 这个位置，那么将序列分成 $l \sim m - 1$ 和 $m + 1 \sim r$ 这两段，然后再合并。设 $l \sim m - 1$ 是 $l \sim r$ 的左儿子，$m + 1 \sim r$ 是 $l \sim r$ 的右儿子，那么 $l \sim r$ 这段区间的答案就等于左儿子的答案加上右儿子的答案，然后再加上子区间两端分别在左儿子和右儿子的答案。算第三种情况的时候，我们可以对左儿子和右儿子分别算贡献，对于左儿子的每个开头为数字的后缀区间，它的贡献就是右儿子的数字个数，对于右儿子同理。所以我们返回右儿子答案的时候还要维护前缀和，后缀和，数字个数这三个值。而前缀序列之和是左儿子的前缀之和再加上右儿子的前缀之和再加上左儿子的整体的表达式的结果乘右儿子的数字个数，后缀同理，而表达式就是左儿子的表达式加上右儿子的表达式。  
2. 没有加号，但有乘号的话区间的子序列之和就是左儿子的和加上右儿子的和再加上左儿子的后缀和乘右儿子的前缀和。而前缀和就是左儿子的前缀和加上左儿子的表达式之和乘右儿子的前缀和，后缀一样，数字个数就等于左子树的个数加右子树的个数，表达式就是左儿子乘右儿子。  
3. 是一段数字，那么就类似 AT_abc288_e 了。  


## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
struct node{
	int ans, lsum, rsum, sz, sum;
	node(){
		ans = lsum = rsum = sz = sum = 0;
	}
};

string str;
int n, lsta[1000005], lstb[1000005];

node solve(int L, int R){
	node ans;
	if(lsta[R] >= L){
		node l = solve(L, lsta[R] - 1), r = solve(lsta[R] + 1, R);
		ans.ans = (l.ans + r.ans + l.rsum * r.sz + r.lsum * l.sz) % mod;
		ans.lsum = (l.lsum + l.sum * r.sz + r.lsum) % mod;
		ans.rsum = (r.rsum + r.sum * l.sz + l.rsum) % mod;
		
		ans.sum = (l.sum + r.sum) % mod;
		ans.sz = l.sz + r.sz;
	} else if(lstb[R] >= L){
		node l = solve(L, lstb[R] - 1), r = solve(lstb[R] + 1, R);
		ans.ans = (l.ans + r.ans + l.rsum * r.lsum) % mod;
		ans.sz = l.sz + r.sz;
		ans.sum = l.sum * r.sum % mod;
		
		ans.lsum = (l.lsum + l.sum * r.lsum) % mod;
		ans.rsum = (r.rsum + r.sum * l.rsum) % mod;
	} else {
		ans.sz = R - L + 1;
		for(int i = L; i <= R; i++) {
			ans.sum = (ans.sum * 10 + (str[i] - '0')) % mod;
			ans.lsum = (ans.lsum + ans.sum) % mod;
			ans.rsum = (ans.rsum * 10 + (i - L + 1) * (str[i] - '0')) % mod;
			ans.ans = (ans.ans + ans.rsum) % mod;
		}
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin >> str;
	n = str.size();
	str = " " + str;
	for(int i = 1; i <= n; i++){
		if(str[i] == '+') lsta[i] = i, lstb[i] = lstb[i - 1];
		else if(str[i] == '*') lstb[i] = i, lsta[i] = lsta[i - 1];
		else lsta[i] = lsta[i - 1], lstb[i] = lstb[i - 1];
	}
	node Ans = solve(1, n);
	cout << Ans.ans << endl;
	return 0;
}
```

---

## 作者：_saltFish_ (赞：0)

# 简要题意
一个合法的算术表达式 $S$，求这个算术表达式所有合法表达式子段的求值结果之和。
$$
1\le |S|\le 10^{6}
$$
# 思路
本来是想线段树维护矩阵的，但是想起来矩阵是有分配率的。
首先考虑用矩阵刻画这个过程。考虑从左往右计算一个表达式的过程。

先考虑只有乘号的情况。
假设当前答案为 $ans$，上一个乘号之前的结果为 $last$，初始时 $ans=0,last=1$。

- 如果这个位置是数字 $num$，那么 $ans\leftarrow ans+9ans+num\cdot last$。
- 如果这个位置是乘号，那么 $last\leftarrow ans,ans\leftarrow 0$。

接下来考虑有加号的情况，此时遇到数字的贡献会有所不同，因为此时式子中的 $9ans$ 就不对了。但是手玩可以发现，$9$ 后面的值就是以加号为分割，当前数字所在的块的前缀的结果。我们设这个数为 $now$。这里的 $now$ 其实就相当于前面只考虑乘号时的 $ans$。这样在遇到乘号时，就需要 $last\leftarrow now$。在遇到加号的时候，直接重置 $now,last$ 即可。

所以有状态矩阵。
$$
\begin{bmatrix}
ans\\
now\\
last\\
1\\
\end{bmatrix}
$$

那么根据上面的分析我们可以得到三个转移矩阵。
$$
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & 0 & 0 & 0\\
0 & 1 & 0 & 0\\
0 & 0 & 0 & 1\\
\end{bmatrix}\\
$$
$$
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & 0 & 0 & 0\\
0 & 0 & 0 & 1\\
0 & 0 & 0 & 1\\
\end{bmatrix}
$$
$$
\begin{bmatrix}
1 & 9 & num & 0\\
0 & 10 & num & 0\\
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
\end{bmatrix}
$$

这三个矩阵分别为乘号、加号和数字的转移矩阵。

好像直接开始做就可以了。但是实际上是会有问题的。如果一个数字前面是乘号，那么第一行第三列的 $num$ 是需要减 $1$ 的，原因很简单，可以自己手玩一下。

~~现在我们好像什么都没解决~~。实际上这一题已经差不多了。我在开头就说过，矩阵是满足分配率的，所以可以枚举右端点，维护以当前位置为右端点的所有区间的状态矩阵之和。然后直接转移。如果这一位是数字，还要再加上只有当前位置一个数字的矩阵表示一个新的左端点。

```cpp
#include <iostream>
#include <cstring>

using namespace std;

#define LL long long

const int N = 1e6 + 5, mod = 998244353;

struct MATRIX {
    LL a[5][5];

    void clear() {
        for(int i = 1; i <= 4; i++) {
            for(int j = 1; j <= 4; j++) {
                a[i][j] = 0;
            }
        }
    }

    MATRIX operator * (const MATRIX b) {
        MATRIX c;

        c.clear();

        for(int i = 1; i <= 4; i++) {
            for(int k = 1; k <= 4; k++) {
                for(int j = 1; j <= 4; j++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }

        return c;
    }

    MATRIX operator + (const MATRIX b) {
        MATRIX c;

        c.clear();

        for(int i = 1; i <= 4; i++) {
            for(int j = 1; j <= 4; j++) {
                c.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
            }
        }
    }
};

char s[N];
LL ans = 0;
MATRIX res, mul, add, num;

void init() {
    mul.a[1][1] = 1;
    mul.a[3][2] = 1;
    mul.a[4][4] = 1;

    add.a[1][1] = 1;
    add.a[3][4] = 1;
    add.a[4][4] = 1;

    num.a[1][1] = 1;
    num.a[1][2] = 9;
    num.a[2][2] = 10;
    num.a[3][3] = 1;
    num.a[4][4] = 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> (s + 1);
    init();

    int len = strlen(s + 1);

    for(int i = 1; i <= len; i++) {
        if(s[i] == '*') {
            res = mul * res;
        } else if(s[i] == '+') {
            res = add * res;
        } else {
            if(s[i - 1] == '*') {
                num.a[1][3] = s[i] - '0' - 1;
                num.a[2][3] = s[i] - '0';
            } else {
                num.a[1][3] = s[i] - '0';
                num.a[2][3] = s[i] - '0';
            }
            res = num * res;

            res.a[1][1] = (res.a[1][1] + s[i] - '0') % mod;
            res.a[2][1] = (res.a[2][1] + s[i] - '0') % mod;
            res.a[3][1] = (res.a[3][1] + 1) % mod;
            res.a[4][1] = (res.a[4][1] + 1) % mod;

            ans = (ans + res.a[1][1]) % mod;
        }
        // cout << res.a[1][1] << ' ' << res.a[2][1] << ' ' << res.a[3][1] << ' ' << res.a[4][1] << '\n';
    }
    // cout << '\n';
    cout << ans << '\n';
}
```

---

## 作者：Eltaos_xingyu (赞：0)

这是 P6796 的加强版，数字可以拆开了。这道题的解法也很难用文字说清楚了。

先定义几个变量吧，设 $sum$ 为 $[1,i],[2,i]\cdots[i,i]$ 的答案之和，其中第 $i+1$ 位置的字符为 `+`。$mul$ 为一个输入的数的前缀，$nmul$ 为一个输入的数的前缀的所有后缀的和，$ans$ 为 $[1,i]$ 所有子串的答案和。$lstlen$ 当前位置向前走最近的 `+` 的位置前面有多少个数字，$lstmul$ 是当前输入的连乘的前缀答案，$lstnmul$ 则是当前输入的连乘的前缀的所有后缀的答案和。$numlen$ 是正输入的数的长度，$mullen$ 是当前连乘包含的数字个数。

同样进行分讨，对于输入一个数字，首先我们需要更新 $mul$ 和 $nmul$ 的值，这个是 trival 的，有：
$$
mul=10mul+num\\
nmul=10nmul+numlen\times num+num
$$
然后更新 $numlen$ 和 $mullen$，最后更新 $ans$。这里我们需要添加所有以当前点为结尾的子串的贡献，即：
$$
ans\leftarrow nmul+lstnmul\times mul+sum+lstlen\times lstmul\times mul
$$
其中第一个部分是这个数产生的贡献，第二部分是这个连乘前面的一些数产生的贡献，第三，四部分是除该连乘以外的所有数产生的贡献。

对于输入 `*`，我们只需要按定义更新 $lstmul$ 和 $lstnmul$，并将 $mul,nmul,numlen$ 置零即可。

对于输入 `+`，我们需要更新 $sum,lstlen$，在此之前，我们先把 $lstmul$ 和 $lstnmul$ 更新，然后显然有：
$$
sum=sum+lstlen\times lstmul+lstnmul
$$
然后更新 $lstlen$，最后将其它非答案变量全部置为初始状态（初始有 $lstmul=1$）。

最后的答案就是 $ans$。

[AC 记录](https://www.luogu.com.cn/record/150486691) [代码](https://atcoder.jp/contests/abc338/submissions/51169286)

---

## 作者：yshpdyt (赞：0)

## 题意
一个字符串 $s$ 由 `1234567890+*` 构成，记 $eval(i,j)$ 表示 $i$ 到 $j$ 位的算式表达式的值 ，特别的若 $ s_i $ 或 $s_j$ 为 `+` 或 `*`，$eval(i,j)=0$。
例如 `1+2*3` 的值为 $7$，`5*10*2+20+0+1*0` 的值为 $121$，`1` 的值为 $1$, `+1` 或 `*1` 的值为 $0$。

求：
$$\sum ^{ \left|s \right| }_{i=1}\sum ^{ \left|s \right| }_{j=i} eval(i,j) (\bmod \ 998244353)$$
## Sol

开始前先进行一些约定，搭配图片理解。

$a_i$，$i$ 位置上是哪个数字。

$ltj$：上一次**加号后**的位置。

$ltx$：上一次**乘号后**的位置，但是要保证 $ltx \le ltj$

$S(i,j)$：题目中的 $eval(i,j)$。

$ans(l,r,i)$：$\sum^r_{k=l} S(k,i)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nz6lph13.png)

看到询问所有可能的左端点与右端点搭配的值，可以想到扫描线，每次移动右端点，维护前面所有位置到当前节点的答案，查询 $[1,i]$ 并相应加上贡献。

我们查询的是一串多项式，多项式由多个单项式构成，用加法分隔。单项式是一堆数的乘积，用乘法分隔。一个数由各位数位拼接组成。这启示我们将字符串分成如同中的红色区域（单项式），蓝色区域（数），黑色下划线（数位）分开维护答案。

### 对于绿色部分( $[ltx,i]$ )
本质上是一个数在不断扩充一个数的位数。

$$\left.\begin{matrix}
&S(i,i) =a_i\\
&S(i-1,i)=S(i-1,i-1)\times 10 +S(i,i)\\
&S(i-2,i)=S(i-2,i-1)\times 10 +S(i,i)\\
&\vdots\\
&S(ltx,i)=S(ltx,i-1)\times 10 +S(i,i)\\
\end{matrix}\right\} ans(ltx,i,i)=ans(ltx,i-1,i-1)\times 10+S(i,i) \times (i-ltx+1)$$ 
相当于是给每个位置先乘 $10$ 后加上 $a_i$。

### 对于蓝色部分( $[ltj,ltx-1]$ )
本质上是一个单项式乘一个数，即蓝色部分乘绿色部分。

$$\left.\begin{matrix}
&S(ltx,i) =\overline{a_{ltx} \dots a_{i-1}a_i} \\
\\
&S(ltx-1,i)=S(ltx-1,ltx-1)\times S(ltx,i) \\
&\vdots\\
&S(ltj,i)=S(ltj,ltx-1)\times S(ltx,i)\\
\end{matrix}\right\} ans(ltj,ltx-1,i)=ans(ltj,ltx-1,ltx-1)\times S(ltx,i) $$ 

### 对于红色部分( $[1,ltj-1]$ )

本质上是一个多项式加一个单项式，即红色部分加上蓝色部分与绿色部分的积

$$\left.\begin{matrix}
&S(ltj,i) = \dots \times S(ltx,i)\\
&S(ltj-1,i)=S(ltj-1,ltj-1)+ S(ltj,i) \\
&\vdots\\
&S(1,i)=S(1,ltj-1)+ S(ltj,i)\\
\end{matrix}\right\} ans(1,ltj-1,i)=ans(1,ltj-1,ltj-1)+ S(ltj,i) \times(ltj-1) $$ 

然后对于以 $i$ 为右端点，其余位置为左端点的答案和就是：
$$ans(1,ltj-1,i)+ans(ltj,ltx-1,i)+ans(ltx,i,i)$$


### 递推求解
没试过直接维护，因为一开始写的线段树，所以用了递推求解。

进行一些变形。

绿色：
$$cnt=ans(ltx,i,i)=ans(ltx,i-1,i-1)\times 10+S(i,i) \times (i-ltx+1)$$

蓝色：
$$\left\{\begin{matrix}
ans(ltj,ltx-1,i)&=ans(ltj,ltx-1,ltx-1)\times S(ltx,i)\\
ans(ltj,ltx-1,i-1)&=ans(ltj,ltx-1,ltx-1)\times S(ltx,i-1)
\end{matrix}\right.$$

也就是：
$$mul=ans(ltj,ltx-1,i)=ans(ltj,ltx-1,i-1)\times \frac{S(ltx,i)}{S(ltx,i-1)}$$

红色：
$$\left\{\begin{matrix}
ans(1,ltj-1,i)&=ans(1,ltj-1,ltj-1)+ S(ltj,i) \times(ltj-1)\\
ans(1,ltj-1,i-1)&=ans(1,ltj-1,ltj-1)+ S(ltj,i-1) \times(ltj-1)
\end{matrix}\right.$$

也就是：
$$sum=ans(1,ltj-1,i)=ans(1,ltj-1,i-1)\times \left(S(ltj,i)-S(ltj,i-1)\right) \times(ltj-1)$$

所以用递推的方式可以得出以下优先级：

$$lastx=nowx$$

$$nowx=nowx\times 10+a[i]$$

$$cnt=cnt\times 10+a[i]\times (i-ltx+1)$$

$$mul=mul\times \frac{nowx}{lastx}$$

$$sum=sum+nowj\times(nowx-lastx)\times $$

然后每次在 `+` 和 `*` 后面把  $nowx$，$nowj$，$ltx$，$ltj$ ，$mul$，$sum$ 更新成新位置的值就好了。

感觉还是有点细节的。


$O(n\log V)$，带个求逆元的复杂度。

~~题解出现问题请联系更改。~~
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll n,m;
string s;
ll a[N],w[N];
ll ny(ll x){
    ll res=1,y=mod-2;
    while(y){
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>s;
    s=" "+s;
    for(int i=1;i<s.size();i++){
        if(s[i]=='+'){
            w[n+1]=1;
            continue;
        }
        if(s[i]=='*'){
            w[n+1]=2;
            continue;
        }
        a[++n]=s[i]-'0';
    }
    ll ltj=1,ltx=1;
    ll nowj=1,nowx=0,res=0;
    ll sum=0,mul=0,cnt=0;
    for(int i=1;i<=n;i++){
        if(w[i]==1){
            ltj=ltx=i;
            nowj=1;
            nowx=0;
            mul=(mul+cnt)%mod;
            sum=(sum+mul)%mod;
            mul=0;
            cnt=0;
        }
        if(w[i]==2){
            ltx=i;
            nowj=nowj*nowx%mod;
            nowx=1;
            mul=(mul+cnt)%mod;
            cnt=0;
        }
        ll t1=ny(nowx);
        ll t2=-nowj*nowx%mod;
        cnt=(cnt*10+a[i]*(i-ltx+1)%mod)%mod;
        if(w[i]==2)nowx=a[i]%mod;
        else nowx=(nowx*10+a[i])%mod;
        if(ltx>ltj)mul=(mul%mod*nowx%mod*t1%mod)%mod;
        if(ltj>1)sum=(sum+(nowj*nowx+t2+mod)%mod*(ltj-1)%mod)%mod;
        res=(res+mul+cnt+sum)%mod;
    }
    cout<<res<<endl;
    return 0;
}

```


---

## 作者：AzusidNya (赞：0)

## [ABC338G] evall

### Description

给一个由 `123456789+*` 组成的字符串 $S$，保证其构成算术表达式。

定义 $\operatorname{eval}(S_{i..j})$ 表示字符串中 $i$ 到 $j$ 这一段所构成的表达式的值，构成表达式要求 $S_i$ 和 $S_j$ 都是数字，若无法构成表达式则这一段的 $\operatorname{eval}$ 为 $0$。

求 $\sum _{i = 1} ^{|S|} \sum_{j = i} ^{|S|} \operatorname{eval}(S_{i..j})$ 对 $998244353$ 取模的值。 

### Solution

感觉思路不难想，就是写起来有点麻烦。

设 $a_i$ 表示 $S_i$ 位置的数字。

因为乘法的优先级大于加法， 所以可以把原串里的加号当作分割点，先累加 $l, r$ 在同一个连续的乘法段内的 $\operatorname{eval}(S_{l..r})$，最后再处理 $l, r$ 跨过加号的。

在连续的乘法段内的 $l, r$ 也有两种情况，即 $l, r$ 跨过了乘号或没有跨过乘号。

#### 1. $l, r$ 没有跨过乘号

简单的递推。设 $f_i$ 表示在前一个乘号到 $i$ 这一段，以 $i$ 结尾的字符串的 $eval$，$g_i$ 表示前一个乘号与 $i$ 间隔的数字数。则 $g_i = g_{i - 1} + 1, f_i = 10f_{i - 1} + g_i \times a_i$。

这一段的贡献即为 $\sum f_i$，$i$ 的范围是当前考虑的纯数字的区间。

#### 2. $l, r$ 中跨过了乘号

设 $h_i$ 表示从这一个连续的乘法段的开头到 $i$ 这一段，以 $i$ 结尾的字符串的 $eval$。

假设上一个乘号的前一个位置为 $j$，当前位置为 $i$，从 $j + 2$ 位置到 $i$ 位置连起来形成的数是 $now$。

那么有 $h_i = h_j \times now + f_i$。

将 $h_i$ 递推出来后，这一段的贡献即为 $\sum h_i$，$i$ 的范围是当前考虑的连续乘法段。



接下来处理加法。

记录 $val_i$ 表示 $i$ 从所在的连续乘法段到 $i$ 的子串得到的表达式的结果。设 $F_i$ 表示从字符串开头到 $i$ 这一段，以 $i$ 结尾的字符串的 $eval$，再记录 $cnt$ 为从开头到 $i$ 中间的数字个数。

假设上一个加号的前一个位置为 $j$，当前位置为 $i$。

那么有 $F_i = F_j + cnt \times val_i + h_i$。

最终答案即为 $\sum_{i = 1} ^{n} F_i$。

---

然后就是注意一下取模，然后这题就做完了。

我的代码中将 $f, h, F$ 的贡献分开计算了，所以与上面的过程上略有不同，不过大体思路是相同的。

### code

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#define int long long
using namespace std;
namespace solve1{
	int n;
	const int modd = 998244353;
	string s;
	int l[1000005], r[1000005]; 
	int val[1000005], f[1000005];
	int h[1000005];
	int ans;
	int tot;
	int main(){
		cin >> s;
		n = s.length();
		s = " " + s;
		tot = 1, l[1] = 1;
		for(int i = 1; i <= n; i ++)
			if(s[i] == '+') r[tot] = i - 1, l[++ tot] = i + 1;
		r[tot] = n;
		for(int k = 1; k <= tot; k ++){
			int pre = 0, lst = 1, nw = 0, cnt = 0;
			for(int i = l[k]; i <= r[k]; i ++){
				if(s[i] == '*') pre = (pre * nw % modd + f[i - 1]) % modd, lst = (lst * nw % modd), 
					h[r[k]] = (h[r[k]] * nw % modd + f[i - 1]) % modd;
				else if(i == l[k] || s[i - 1] == '*'){
					f[i] = s[i] - '0', cnt = 1;
					(ans += f[i]) %= modd;
					nw = s[i] - '0';
					val[i] = lst * nw % modd;
					ans = (ans + pre * nw % modd) % modd;
				}
				else{
					f[i] = (f[i - 1] * 10 + cnt * (s[i] - '0') % modd) % modd;
					f[i] = (f[i] + (s[i] - '0')) % modd, cnt ++;
					(ans += f[i]) %= modd;
					nw = nw * 10 + (s[i] - '0');
					nw %= modd;
					ans = (ans + pre * nw % modd) % modd;
					val[i] = lst * nw % modd;
				}
			}
			h[r[k]] = (h[r[k]] * nw % modd + f[r[k]]) % modd;
		}
		int lt = 0, ct = 0, un0 = 0;
		for(int i = 1; i <= n; i ++){
			if(s[i] != '+' && s[i] != '*')
				un0 ++, (ans += lt + ct * val[i] % modd) %= modd;
			else if(s[i] == '+'){
				lt = (lt + val[i - 1] * ct % modd + h[i - 1]) % modd;
				ct = ct + un0, un0 = 0;
			}
		}
		cout << ans;
		return 0;
	}
}
signed main(){
	int T = 1;
	while(T --)
		solve1::main();
	return 0;
}
```



---

