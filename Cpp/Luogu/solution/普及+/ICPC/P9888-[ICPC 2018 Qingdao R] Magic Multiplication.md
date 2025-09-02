# [ICPC 2018 Qingdao R] Magic Multiplication

## 题目描述

BaoBao 现在正在他的魔法书中学习两个正整数之间的一种新的二进制运算，用 $\otimes$ 表示。这本书告诉他，这种运算的结果是通过将两个整数中每个数字的所有多个结果串联起来计算的。

形式上讲，让第一个整数为 $A=A_1a_2\dots A_n$，其中 $A_i$ 表示 $A$ 中的第 $i$ 位，第二个整数为 $B=B_1b_2\dots B_m$，其中 $B_i$ 表示 $B$ 中的第一位。我们有

$$A \otimes B = \sum\limits_{i=1}^n\sum\limits_{j=1}^m a_ib_j = a_1b_1 + a_1b_2 + \dots + a_1b_m + a_2b_1 + \dots + a_nb_m$$

请注意，$a_ib_j$ 的结果被认为是 $\textbf{string}$（如果 $a_ib_j>0$，则不带前导零，或者如果 $a_ib_j > 0$，则仅包含一个 $0$），而不是正常整数。此外，这里的 sum 表示 $\textbf{string concatenation}$，而不是正常的加法运算。

例如，$23\otimes 45=8101215$。因为 $8=2\times 4$，$10=2\times 5$，$12=3\times 4$ 和 $15=3\times 5$。

BaoBao 很聪明，很快就知道如何做 $\otimes$ 的逆运算。现在，他给出了 $\otimes$ 运算的结果以及两个原始整数中的位数。请帮助他恢复两个原始整数 $A$ 和 $B$。

## 样例 #1

### 输入

```
4
2 2
8101215
3 4
100000001000
2 2
80101215
3 4
1000000010000```

### 输出

```
23 45
101 1000
Impossible
Impossible```

# 题解

## 作者：Helenty (赞：3)

### 思路

难点在于我们在枚举 $C$ 时无法确定该取一位数字还是两位数字。

但我们知道，两个长度为 $1$ 的数字相乘，其最小值是 $0$ ，最大值是 $81$ ，即乘积的长度不超过 $2$ 。其次，若乘积的长度是 $2$ ，则乘积的十位数字小于两个数字的任意一个；如果乘积的长度是 $1$ ，则乘积大于等于两个数字的任意一个。

所以我们在枚举数字时，只需要判断一下 $C$ 的数字和我们枚举的数字的大小就可知道该取 $1$ 位还是该取 $2$ 位：

-  如果 $C$ 的数字小于枚举数字，就取 $2$ 位，然后判断是否能整除。
  - 如果 $C$ 的数字大于等于枚举数字，就取 $1$ 位，然后判断是否能整除。

因为 $A$ 和 $B$ 的长度是已知的，所以我们可以先枚举，然后利用 $C$ 的前半部分和枚举 $B$ 对应 $1$ 个或 $0$ 个 $B$，然后再利用枚举的 $B$ 去推导剩余的 $A$。**如果推导成功就得出了答案，而且因为推导的过程是由大到小的，所以第一个满足要求的答案就是最小的答案。**

### CODE


```cpp
#include <bits/stdc++.h>
#define maxn 200005
#define _for(i, a) for(int i = 0; i < (a); ++i)
#define _rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define scl(x) scanf("%lld", &x)
#define sc(x) scanf("%d", &x)
using namespace std;

int T, n, m;
int a[maxn], b[maxn];
char c[maxn];

bool getb() {
	int len = strlen(c), pos = 0;
	_for(i, m) {
		if (pos == len) return 0;					//C不够用了
		int x = c[pos++] - '0';
		if (pos < len && x && x < a[0]) x = x * 10 + c[pos++] - '0';
		if (x % a[0] || x / a[0] > 9) return 0;		//除不尽或者商是两位数
		b[i] = x / a[0];
	}
	_rep(i, 1, n - 1) {
		_for(j, m) {
			if (pos == len) return 0;				//C不够用了
			int x = c[pos++] - '0';
			if (pos < len && x && x < b[j]) x = x * 10 + c[pos++] - '0';
			if (x && (b[j] == 0 || j && a[i] == 0)) return 0;	//a和b都为0但c不为0
			if (x == 0) {
				if (j && a[i] && b[j]) return 0;	//c为0但a和b都不为0；j不为0代表a已经被赋值
				if (!j) a[i] = 0;
			}
			else {
				if (x % b[j] || j && x / b[j] != a[i] || x / b[j] > 9) return 0;	//除不尽或者商是两位数
				a[i] = x / b[j];
			}
		}
	}
	return pos == len;
}

bool sol() {
	sc(n), sc(m);
	scanf("%s", c);
	int x = c[0] - '0';
	_rep(i, 1, 9) {		//利用a[0]找出b
		if (x % i == 0) {
			a[0] = i;
			if (getb()) return 1;
		}
	}
	x = x * 10 + c[1] - '0';
	_rep(i, 1, 9) {		//利用b找出a
		if (x % i == 0) {
			a[0] = i;
			if (getb()) return 1;
		}
	}
	return 0;
}

int main() {
	while (cin >> T) {
		_for(i, T) {
			if (sol()) {
				_for(j, n) printf("%d", a[j]);
				printf(" ");
				_for(j, m) printf("%d", b[j]);
				printf("\n");
			}
			else printf("Impossible\n");
		}
	}
	return 0;
}

```

### 后记

[record](https://www.luogu.com.cn/record/194855197)

---

## 作者：Alex_Wei (赞：1)

### D. [P9888 [ICPC2018 Qingdao R] Magic Multiplication](https://www.luogu.com.cn/problem/P9888)

枚举 $A_1$，则 $B$ 唯一确定。

假设第一个不确定的是 $B_i$，可以取 $x$ 和 $y$，分别等于 $C_j$ 和 $10C_j + C_{j + 1}$。这是不可能的，因为 $A_1x = C_j$，$A_1y = 10C_j + C_{j + 1}$。若 $C_j = 0$，则 $B_i$ 只能为 $0$，否则 $A_1y \geq 10 A_1x$，即 $y \geq 10x$，但 $1\leq x < y\leq 9$，矛盾。

$B$ 唯一确定后，可以反推出 $A$。

时间复杂度 $\mathcal{O}(|C|)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}

// ---------- templates above ----------

constexpr int N = 2e5 + 5;

int n, m, k;
int a[N], b[N], c[N];
char s[N];
void solve() {
  cin >> n >> m >> s + 1;
  k = strlen(s + 1);
  for(int i = 1; i <= k; i++) c[i] = s[i] - '0';
  c[k + 1] = c[k + 2] = c[k + 3] = -1;
  for(int i = 1; i < 10; i++) { // iterate the first digit of A, then we can get B
    int cur = 1, ok = 1;
    a[1] = i;
    for(int j = 1; j <= m && ok; j++) {
      int fnd = 0;
      for(int p = j == 1 ? 1 : 0; p < 10; p++) {
        int v = i * p;
        if(v == c[cur]) {
          fnd = 1;
          b[j] = p;
          cur++;
          break;
        }
        if(v == c[cur] * 10 + c[cur + 1]) {
          fnd = 1;
          b[j] = p;
          cur += 2;
          break;
        }
      }
      if(!fnd) ok = 0;
    }
    for(int j = 2; j <= n && ok; j++) {
      bool fnd = 0;
      for(int q = 0; q < 10; q++) {
        int ori = cur, ok2 = 1;
        for(int p = 1; p <= m && ok2; p++) {
          int v = q * b[p];
          if(v == c[cur]) cur++;
          else if(v == c[cur] * 10 + c[cur + 1]) cur += 2;
          else ok2 = 0;
        }
        if(ok2) {
          fnd = 1;
          a[j] = q;
          break;
        }
        cur = ori;
      }
      if(!fnd) ok = 0;
    }
    if(ok && cur == k + 1) {
      for(int i = 1; i <= n; i++) cout << a[i];
      cout << ' ';
      for(int i = 1; i <= m; i++) cout << b[i];
      cout << "\n";
      return;
    }
  }
  cout << "Impossible\n";
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  cin >> T;
  while(T--) solve();
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：immortal_immortals (赞：1)

## 题意
$A$，$B$ 对应位上的数（十进制），定义一种新运算。现给出运算结果，求 $A$，$B$。若多个答案，以最小的 $A$ 为基准，若仍有多个，以最小的 $B$ 为基准。
## 思路
规律：确定 $A$ 的首位，则可推出剩下的数，且过程中 $C$ 不可能出现一位和两位数都可行的情况，因此无需回溯。

枚举 $A$ 的首位，判断是否可行，那么 $B$ 序列就会被唯一地确定下来，再逐位确定 $A$ 序列。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int T,n,m,a[200005],b[200005];
char c[200005];
bool GetB() 
{
    int len=strlen(c),pos=0;
    for(int i=0; i<m; i++) 
	{
        if(pos==len)return 0;//字符串不够用，不合法
        int x=c[pos++]-'0';//获得对应数字
        if(pos<len&&x&&x<a[0])x=x*10+c[pos++]-'0';
        //如果字符串够用，这一位不为0，数字小于a[0]，就需要多拿一位
        if(x%a[0]||x/a[0]>9)return 0;
        //如果不能整除或者商为两位数
        b[i]=x/a[0];//构造b[i]
    }
    for(int i=1; i<n; i++)
        for(int j=0; j<m; j++) 
		{
            if(pos==len)return 0;
            int x=c[pos++]-'0';//获得对应数字
            if(pos<len&&x&&x<b[j])x=x*10+c[pos++]-'0';
            //如果字符串够用，这一位不为0，数字小于a[0]，就需要多拿一位
            if(x&&(b[j]==0||(j&&a[i]==0)))return 0;
            //如果有结果但是b的对应位为0或者a的对应位为0(j代表已经计算过，根据0~j-1推出a[i]==0)
            if(x==0) 
			{
                if(j&&a[i]&&b[j])return 0;
                //结果有0并且a[i]已经算过，b的对应为有值
                if(!j)a[i]=0;//如果第一次算，结果为0，则a[i]为0
            } else {
                if (x%b[j]||j&&x/b[j]!=a[i]||x/b[j]>9) return 0;
                //如果不能整除或者商为两位数
                a[i]=x/b[j];
            }
        }
    return pos==len;
}
bool Judge(int x) 
{
    for(int i=1; i<=9; i++)
        if(x%i==0) 
		{
            a[0]=i;
            if(GetB())return 1;
        }
    return 0;
}
bool solve() 
{
    int x=c[0]-'0';
    if(Judge(x))return 1;
    x=x*10+c[1]-'0';
    if(Judge(x))return 1;
    return 0;
}
int main() 
{
    scanf("%d",&T);
    while(T--) 
	{
        scanf("%d%d%s",&n,&m,&c);
        if(solve()) 
		{
            for(int i=0; i<n; i++)printf("%d",a[i]);
            putchar(' ');
            for(int i=0; i<m; i++)printf("%d",b[i]);
            putchar('\n');
        } else printf("Impossible\n");
    }
    return 0;
}

```


---

## 作者：zheng_zx (赞：1)

## P9888 [ICPC2018 Qingdao R] Magic Multiplication

[题目传送门](https://www.luogu.com.cn/problem/P9888)

### 分析

---

一道找规律题。我们只需要发现一个规律即可：只要 $A$ 的第一个数确定了，那么剩下的数都可以推出来，而且推的过程中 $C$ 中不可能出现一位和两位数都可行的情况，因此没有回溯的过程，直接枚举 $A$ 的第一个数然后判断是否可行即可。

### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 7;
int na, nb, nc, p, T, a[N], b[N], c[N];
char s[N];
bool set_(int x) {
    a[0] = x, p = 0;
    for(int i = 0; i < nb; ++i) {
        if(p < nc && c[p] % a[0] == 0 && c[p] / a[0] <= 9)
            b[i] = c[p] / a[0], p += 1;
        else if(p + 1 < nc && (c[p] * 10 + c[p + 1]) % a[0] == 0 && (c[p] * 10 + c[p + 1]) / a[0] <= 9)
            b[i] = (c[p] * 10 + c[p + 1]) / a[0], p += 2;
        else return 0;
    }
    return 1;
}
bool check(){
    for(int i = 1; i < na; ++i) {
        if(p < nc && c[p] % b[0] == 0 && c[p] / b[0] <= 9)
            a[i] = c[p] / b[0], p += 1;
        else if(p + 1 < nc && (c[p] * 10 + c[p + 1]) % b[0] == 0 && (c[p] * 10 + c[p + 1]) / b[0] <= 9)
            a[i] = (c[p] * 10 + c[p + 1]) / b[0], p += 2;
        else return 0;
        for(int j = 1; j < nb; ++j) {
            if(p < nc && a[i] * b[j] == c[p])p += 1;
            else if(p + 1 < nc && a[i] * b[j] == c[p] * 10 + c[p + 1])p += 2;
            else return 0;
        }
    }
    return p == nc;
}
int main(){
    cin >> T;
    while(T--){
        cin >> na >> nb >> s;
        nc = strlen(s);
        for(int i = 0; i < nc; ++i)c[i] = s[i] - '0';
        bool flag = 0;
        for(int i = 1; i <= 9; ++i) {
            if(set_(i) && check()) {
                flag = 1;
                for(int i = 0; i < na; ++i) cout << a[i];
                    cout << " ";
                for(int i = 0; i < nb; ++i) cout << b[i];
                    puts("");
                break;
            }
        }
        if(!flag) puts("Impossible");
    }
    return 0;
}
```

---

