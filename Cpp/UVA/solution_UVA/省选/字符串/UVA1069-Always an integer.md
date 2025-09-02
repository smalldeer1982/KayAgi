# Always an integer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3510

[PDF](https://uva.onlinejudge.org/external/10/p1069.pdf)

# 题解

## 作者：andyli (赞：3)

本题实际上是判断一个整系数多项式$P$的值是否总是正整数$D$的倍数。一个容易想到的方法是，随机代入很多整数计算$P/D$，如果全都是整数，那么很有可能是`Always an integer`；如果有的不是整数，那么答案必然是`Not always an integer`。  
这个方法看起来有些投机取巧，但效果非常不错。事实上，不需要随机代入，只需要把$n=1,2,3,...,k+1$全试一遍就可以了，其中$k$试多项式中最高项的次数。  
为什么可以这样做呢？让我们从$k$较小的情况开始研究。  
- 当$k=0$时，$P$里根本就没有$n$个变量，所以只需代入$P(1)$计算即可。  
- 当$k=1$时，$P$时$n$的一次多项式，设为$an+b$，则$P(n+1)-P(n)=a$。如果把$P(n)$看成一个数列的第$n$项，则$\{P(n)\}$是一个首项为$P(1)$，公差为整数$a$的等差数列，因此只要首项和公差均为$D$的倍数，整个数列的所有项都会是$D$的倍数。因此只需验证$P(1)$和$P(2)$。  
- 当$k=2$时，$P$是$n$的二次多项式，设为$an^2+bn+c$，则$P(n+1)-P(n)=2an+a+b$。注意到这个$2an+a+b$是$n$的一次多项式，根据刚才的结论，只要$n=1$和$n=2$时它都是$D$的倍数，对于所有的正整数$n$，它都将是$D$的倍数。这样，相邻两项的差为$D$的倍数，再加上首项也为$D$的倍数，则$P(n)$将总是$D$的倍数。整理一下，只要$P(1),P(2)-P(1),P(3)-P(2)$都是$D$的倍数即可。这等价于验证$P(1),P(2)$和$P(3)$。  
看到这里，结论已经不难猜到了。对于$k$次多项式$P(n)$，相邻两项之差$P(n+1)-P(n)$是关于$n$的$k-1$次多项式，根据数学归纳法，命题得证。顺别说一句，数列$dP(n)=P(n+1)-P(n)$称为$P(n)$的**差分数列**(difference series)。而差分数列的差分数列为二阶差分数列$d^2P(n)$，以此类推。  
本题还要注意输入二项式的格式问题。输入格式翻译如下：  
输入包含多组数据。每组数据仅一行，即一个多项式$(P)/D$，其中$P$是若干个形如$Cn^E$的项之和，其中系数$C$和$E$满足以下条件：  
1. $E$是一个满足$0\le E\le 100$的整数。如果$E=0$，则$Cn^E$写作$C$；如果$E=1$，则$Cn^E$写成$Cn$；除非$C$等于$1$或者$-1$（$C=1$时写作$n$，$C=-1$时写作$-n$）。
2. $C$是一个整数。如果$C$等于$1$或$-1$，且$E$不是$0$或者$1$，则$Cn^E$写成$n^E$或者$-n^E$。
3. 只有不在第一项的非负$C$的前面才会有一个加号。
4. $E$的数值严格递减。
5. $C$和$D$都在$32$位带符号整数范围内。
输入结束标志为单个**英文**句号(`.`)。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
struct Polynomial
{
    vector<int> a, p;  // 第i项为a[i] * n^p[i]
    void parse_polynomial(string expr)
    {  // 解析多项式（不带括号）
        int i = 0, len = expr.size();
        while (i < len)
        {  // 每次循环体解析一个a*n^p
            int sign = 1;
            if (expr[i] == '+')
                i++;
            if (expr[i] == '-')
            {
                sign = -1;
                i++;
            }
            int v = 0;
            while (i < len && isdigit(expr[i]))
                v = v * 10 + expr[i++] - '0';  // 系数的绝对值
            if (i == len)
            {
                a.push_back(v);
                p.push_back(0);
            }  // 常数项
            else
            {
                if (v == 0)
                    v = 1;  // 无系数，按1处理
                v *= sign;
                if (expr[++i] == '^')
                {  // 有指数项
                    a.push_back(v);
                    v = 0;  // 清空v，接下来用v保存指数
                    i++;
                    while (i < len && isdigit(expr[i]))
                        v = v * 10 + expr[i++] - '0';
                    p.push_back(v);
                }
                else
                {  // 无指数项
                    a.push_back(v);
                    p.push_back(1);
                }
            }
        }
    }

    // 计算f(x)除以MOD的余数
    int mod(int x, int MOD)
    {
        int n = a.size(), ans = 0;
        for (int i = 0; i < n; i++)
        {
            int m = a[i];
            for (int j = 0; j < p[i]; j++)
                m = m * 1LL * x % MOD;    // 注意避免溢出
            ans = (ans * 1LL + m) % MOD;  // 加法也可能会溢出！
        }
        return ans;
    }
};

bool check(string expr)
{
    int p = expr.find('/');
    Polynomial poly;
    poly.parse_polynomial(expr.substr(1, p - 2));
    int D = stoi(expr.substr(p + 1));  // stoi是C++11新增的函数
    for (int i = 1; i <= poly.p[0] + 1; i++)
        if (poly.mod(i, D))
            return false;
    return true;
}

int main()
{
    int kase = 0;
    string expr;
    while (getline(cin, expr) && expr[0] != '.')
        printf("Case %d: %s\n", ++kase,
               check(expr) ? "Always an integer" : "Not always an integer");
    return 0;
}
```

---

## 作者：frankchenfu (赞：2)

### 解法
这道题目的解决方法如下：对于每一个$n(1\le n \le 101)$，都把它带进去试一遍，如果每一个$n$都能够使多项式$P$被$D$整除，那么这个式子就总是一个整数。

那么为什么可以这么做呢？

我们不妨设这里多项式的次数最高项次数是$k$

（即$P(n)=a_1\cdot n^k+a_2\cdot n^{k-1}+...+ a_k\cdot n+a_{k+1}$）

那么：
* 当$k=0$的时候，那么只有常数项，总是成立的。
* 当$k=1$的时候，设多项式表示为$P(n)=xn+y$，则$$P(n+1)-P(n)=[x(n+1)+y]-(xn+y)=x.$$所以等差数列$P(1)+P(2)+...+P(n)$的公差就是$x$。由于需要验证每一个$n$均为$D$的倍数，等价于验证$P(1)$和$P(2)-P(1)$均为$D$的倍数。又因为如果其中一个条件$P(1)$是$D$的倍数得到验证，那么验证$P(2)-P(1)\equiv 0\pmod{D}$等价于验证$P(2)\equiv 0\pmod{D}$，所以只需验证$P(1),P(2)$
* 当$k=2$的时候，设多项式表示为$P(n)=xn^2+yn+z$，则$$P(n+1)-P(n)=2an+a+b.$$类似的道理，我们需要验证$P(1),P(2)-P(1),P(3)-P(2)$，也等价于验证$$\begin{cases} P(1)\equiv 0\pmod{D} \\ P(2)\equiv 0\pmod{D} \\ P(3)\equiv 0\pmod{D} \end{cases}$$

以下$(k\le 100)$的数据同理可得。

所以，由于$k\le 100$我们只要验证每一个$n(1\le n \le 101)$是否都满足即可。

### 代码
作为一道直接输入多项式的题目，小伙伴们的字符串处理能力就需要好好锻炼一下了！（这道题目字符串确实调了我比较久的时间，细节比较多）这里我给几个提醒吧。
* 如果系数$c_i=1$或$c_i=-1$，那么正负号后面没有数字，就需要特判了。
* 输入数字的时候注意判断正负号。
* 注意次数$e_i=0$和$e_i=1$的情况，后面没有`^`。
* 由于只需要验证是否是$D$的倍数，所以就可以边算边取模，避免溢出，否则验算时$n^k=(k+1)^k\approx 100^{100}$。
代码比较乱，大家凑合着吧：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
const int MAXN=100010;
typedef long long ll;
char opt[MAXN];
int d,c[MAXN];

ll qpow(ll x,int b){
	ll res=1;
	while(b){
		if(b&1)
			res=res*x%d;
		x=x*x%d;b>>=1;
	}
	return res;
}

int readint(char *s,char *t){
	int res=0;char *pos=s;
	do{
		res=(res<<3)+(res<<1)+*pos-'0';
		pos++;
	}while(pos<t);
	return res;
}

bool solve(char *s,char *t){
	bool fir=1;
	while(s<t){
		bool neg;int res=0,top=0;
		if(*s!='+'&&*s!='-')
			if(fir){
				fir=0;
				neg=0;
			}
			else{
				printf("\nError in pos %d,char %c\n",s-opt,*s);
				return 0;
			}
		else{
			neg=(*s=='-');
			s++;
		}
		if(!isdigit(*s))
			res=1;
		else while(s<t&&isdigit(*s)){
			res=(res<<3)+(res<<1)+*s-'0';
			s++;
		}
		if(*s=='n'){
			top=1;
			s++;
		}
		else
			top=0;
		if(*s=='^'){
			s++;top=0;
			while(s<t&&isdigit(*s)){
				top=(top<<3)+(top<<1)+*s-'0';
				s++;
			}
		}
		c[top]=neg?-res:res;
	}
	for(int i=0;i<=100;i++){
		ll tot=0;
		for(int j=0;j<=100;j++)
			if(c[j])
				tot=(tot+c[j]*qpow(i,j))%d; 
		if(tot%d)
			return 0;
	}
	return 1;
}

int main(){
	for(int CAS=1;~scanf("%s",opt+1);CAS++){
		int n=strlen(opt+1),pos=n;
		if(n==1&&opt[1]=='.')
			break;
		for(int i=n;i;i--,pos--)
			if(opt[i]=='/'&&opt[i-1]==')')
				break;
		memset(c,0,sizeof(c));
		d=readint(opt+pos+1,opt+n+1);
		if(solve(opt+2,opt+pos-1))
			printf("Case %d: Always an integer\n",CAS);
		else
			printf("Case %d: Not always an integer\n",CAS);
	}
	return 0;
}
```

---

## 作者：chroneZ (赞：1)

我们要判断的是对于一个整系数多项式 $P$ 及一个整数 $d$，是否有 $d | P(x), \forall x \in \mathbb Z$。

如果能确定 $d|P(1)$，考虑建立一个增量函数 $\Delta(x) = P(x + 1) - P(x)$，这样一来为了判断 $P(x + 1) = P(x) + \Delta(x)$，如果 $d|P(x)$，仅需判断是否有 $d| \Delta(x)$。这么建立的好处是什么呢，记 $P(x) = \sum \limits_{i = 0} ^ n a_i x^i$，则 $\Delta(x) = \sum \limits_{i = 0} ^ n a_i((x + 1) ^ i - x ^ i)$。使用二项式定理可以将此式展开为多项式形式，但此处暂时不需将其展开。观察式子，比较显然的一点是，$\Delta(x)$ 的最高次项的次数为 $n - 1$。这就是一个使用归纳法的线索了，我们重复上述过程，判断是否有 $d | \Delta(1)$，再对 $\Delta(x)$ 建立增量函数 $\Delta_2(x)$，判断是否有 $d|\Delta_2(1)$。直到重复到 $\Delta_n(x)$ 时，此时仅剩下了常数项，无需再建立 $\Delta_{n + 1}(x)$ 了。

这样得到了一个复杂度与多项式最高次数相关的算法，问题来到了，如何实现这个过程。由于 $\Delta(1) = P(2) - P(1)$，因此在 $d | P(1)$ 的前提下，$d | \Delta(1)$ 等价于 $d|P(2)$。现在我们知道了 $d|P(1), P(2)$，考虑怎么判断 $d | \Delta_2(1)$。因为 $\Delta_2(1) = \Delta(2) - \Delta(1) = P(3) - 2\times P(2) + P(1)$，所以 $d | \Delta_2(1)$ 等价于 $d | P(3)$。猜想 $d | \Delta_n(1)$ 等价于 $d | P(n + 1)$，其实事实上有 $\Delta_n(1) = \sum \limits_{i = 0} ^ {n} (-1) ^ i \binom{n}{i} P(n + 1 - i)$，故成立。

所以记原多项式 $P$ 的最高次数为 $n$，原条件等价于 $d|P(x), \forall x \in [1, n + 1]$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<int, int>;

inline int ksm(int a, int b, int p){
	int r = 1;
	while(b){
		if(b & 1) r = 1ll * r * a % p;
		a = 1ll * a * a % p, b >>= 1;
	}
	return r;
}

inline int calc(vector<pii> &P, int x, int d){
	i64 res = 0;
	for(auto [c, p] : P){
		res += 1ll * ksm(x, p, d) * c % d;
		res %= d;
	}
	return res;
}

void solve(string s, int tc){
	int pos = s.find(')'); string p = s.substr(1, pos - 1);

	vector<pii> P;
	for(int i = 0; i < p.length(); ){
		int co = 0, po = 0;
		if(p[i] == 'n') co = 1;
		else if(p[i] == '-'){
			i++;
			if(p[i] == 'n') co = -1;
			else {
				while(i < p.length() && '0' <= p[i] && p[i] <= '9')
					co = (co << 3) + (co << 1) + (p[i] ^ 48), i++;
				co = -co;
			}
		} else {
			if(i != 0) i++;
			if(p[i] == 'n') co = 1;
			else {
				while(i < p.length() && '0' <= p[i] && p[i] <= '9')
					co = (co << 3) + (co << 1) + (p[i] ^ 48), i++;
			}
		}
		if(i == p.length()) po = 0;
		else if(p[i] == 'n' && (i == p.length() - 1 || p[i + 1] != '^')) po = 1, i++;
		else {
			i += 2;
			while(i < p.length() && '0' <= p[i] && p[i] <= '9')
				po = (po << 3) + (po << 1) + (p[i] ^ 48), i++;
		}
		P.emplace_back(co, po);
	} // 处理多项式

	int d = 0; pos += 2;
	while(pos < s.length() && '0' <= s[pos] && s[pos] <= '9')
		d = (d << 3) + (d << 1) + (s[pos] ^ 48), pos++;
	
	int ans = 1;
	for(int i = 1; i <= P[0].second + 1; i++)
		ans &= (calc(P, i, d) == 0);
	cout << "Case " << tc << ": " << (ans ? "Always an integer" : "Not always an integer") << "\n";
}

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	string s; cin >> s;
	int tc = 1;
	while(s != "."){
		solve(s, tc);
		cin >> s; tc++;
	}
}
```


---

## 作者：o06660o (赞：0)

# UVA1069 题解

[英文题面](https://onlinejudge.org/external/10/1069.pdf)

## 题意

给出一个多项式，判断这个多项式是否恒取整数值。

## 思路

本题难点实际上在字符串处理，我自认为这部分代码写的相对简单。

在开始之前，我们可以照着快读来完成整数的读入，不过这里对 `-n` 一类做了特判。

```cpp
// 从+-^/开始读一个数字
ll read(int& cur) {
    ll x = 0, f = (s[cur++] == '-' ? -1 : +1);
    char ch = s[cur++];
    while (isdigit(ch)) x = x * 10 + (ch - '0'), ch = s[cur++];
    return (x == 0 ? f : x * f);
}
```

理想状态下我们希望读取的每一项都是 `Cn^E` 的形式，对于不属于这一形式的有一下几种可能。

- $C$ 为正的时候，前面可能没有加号，这只会出现在字符串的第一项，所以只要第一项非负我们就插入一个加号
- $C = \pm 1$ 的时候，数字部分会被省略，这个在 `read()` 函数中加了特判。
- $E = 0$ 的时候，这时 `n^E` 都不存在了，那么读取完 `C` 就可以判断。
- $E = 1$ 的时候，这时 `^E` 不存在，那么就是存在 `n` 不存在 `^`。

具体实现如下，思路跟着 `read()` 读完一次之后 `cur` 的位置往下写就可以了。

```cpp
void parse(const string& s) {
    int cur = 1;
    // 处理多项式部分
    while (cur < (int)s.size() && s[cur] != ')') {
        int C = 0;
        C = read(cur);
        if (s[cur - 1] != 'n') {
            P.push_back({C, 0});
            cur--;
        } else {
            int E = 1;
            if (s[cur] == '^') {
                E = read(cur);
                cur--;
            }
            P.push_back({C, E});
        }
    }
    // 读取除数
    cur++;
    d = read(cur);
}
```

## 代码

我的实现是随机代入一些数字，确实可以过。

```cpp
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
using ll = long long;  // 2.15e9, 9.22e18
using pii = pair<int, int>;

int d;
string s;
vector<pii> P;  // first: 系数, second: 次数

// 从+-^/开始读一个数字
ll read(int& cur) {
    ll x = 0, f = (s[cur++] == '-' ? -1 : +1);
    char ch = s[cur++];
    while (isdigit(ch)) x = x * 10 + (ch - '0'), ch = s[cur++];
    return (x == 0 ? f : x * f);
}
void parse(const string& s) {
    int cur = 1;
    // 处理多项式部分
    while (cur < (int)s.size() && s[cur] != ')') {
        int C = 0;
        C = read(cur);
        if (s[cur - 1] != 'n') {
            P.push_back({C, 0});
            cur--;
        } else {
            int E = 1;
            if (s[cur] == '^') {
                E = read(cur);
                cur--;
            }
            P.push_back({C, E});
        }
    }
    // 读取除数
    cur++;
    d = read(cur);
}

ll pow_mod(ll a, ll b, ll MOD) {
    a %= MOD;
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
const int INF = 1e5;
mt19937_64 rng(random_device{}());
uniform_int_distribution<int> INT(0, INF);
// 对多项式进行cnt轮随机测试
bool check(int cnt) {
    for (int i = 0; i < cnt; i++) {
        int x = INT(rng), ok = 0;
        for (const pii& p : P) ok = (ok + p.first * pow_mod(x, p.second, d)) % d;
        if (ok != 0) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int kase = 1;
    while (cin >> s && s != ".") {
        cout << "Case " << kase++ << ": ";
        if (s[1] != '-') s.insert(s.begin() + 1, '+');
        P.clear();
        parse(s);
        cout << (check(2333) ? "Always " : "Not always ") << "an integer\n";
    }
    return 0;
}
```

---

