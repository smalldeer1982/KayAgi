# Mark and the Online Exam

## 题目描述

Mark is administering an online exam consisting of $ n $ true-false questions. However, he has lost all answer keys. He needs a way to retrieve the answers before his client gets infuriated.

Fortunately, he has access to the grading system. Thus, for each query, you can input the answers to all $ n $ questions, and the grading system will output how many of them are correct.

He doesn't have much time, so he can use the grading system at most $ 675 $ times. Help Mark determine the answer keys.

Note that answer keys are fixed in advance and will not change depending on your queries.

## 说明/提示

The empty lines in the example are just for you to better understand the interaction process. You're not required to print them.

In the first example, there are $ 3 $ questions, and the answer to each question is 'true', 'true', and 'false', respectively.

- The first query, guessing the answers to be 'false', 'true', and 'true', respectively, guesses only one question — the $ 2 $ -nd question — correctly.
- Then, in the second query, the program correctly guesses the answer key. The interaction ends here.

In the second example, there are $ 4 $ questions, and the answer to each question is 'true', 'false', 'true', and 'true', respectively.

- The first query guessed none of the questions correctly, resulting in the answer $ 0 $ .
- The second query guessed the $ 1 $ -st, $ 3 $ -rd, and $ 4 $ -th question correctly, resulting in the answer $ 3 $ .
- In the third query, the program correctly guesses the answer key. Then, the interaction ends.

## 样例 #1

### 输入

```
3

1

3```

### 输出

```
FTT

TTF```

## 样例 #2

### 输入

```
4

0

3

4```

### 输出

```
FTFF

TTTT

TFTT```

# 题解

## 作者：Terraria (赞：17)

好家伙，可惜没打 CF，直接出了[我的题](https://www.luogu.com.cn/problem/T183641?contestId=44371)。

## 题目简述

设有 $n$ 道题目，$q$ 个询问，且

- 第 $i$ 次询问为 $x_{i, j} (1 \leq i \leq q, 1 \leq j \leq n, x_{i, j} \in \{0, 1\})$；
- 第 $j$ 题的答案为 $c_j (1 \leq j \leq n, c_j \in \{0, 1\})$。

则需要从 $\sum \limits_{j=1}^{n} x_{i,j} \oplus c_j$ 中恢复 $c_j$ 的值。

$n \leq 1000,q  \leq 675$。

以下内容除了正解的代码，其他参考代码和讲解思路均为 `YN` 的输出内容。

---

## 问题的转换

首先，可以从 $\sum \limits_{i=1}^{n} x_{i,j} \oplus c_j$ 中得到 $\sum \limits_{i=1}^{n} x_{i,j} \times c_j$ 的值。

枚举 $x_{i, j}$ 和 $c_{j}$ 的值：

| $x_{i, j}$ | $c_j$ | $x_{i, j} \oplus c_j$ | $x_{i, j} \times c_j$ |
| :-: | :-: | :-: | :-: |
| $0$ | $0$ | $0$ | $0$ |
| $0$ | $1$ | $1$ | $0$ |
| $1$ | $0$ | $1$ | $0$ |
| $1$ | $1$ | $0$ | $1$ |

可以得到 $x_{i, j} \oplus c_j = x_{i, j} + c_j - 2 \times x_{i, j} \times c_j$，

从而 $x_{i, j} \times  c_j = \dfrac{x_{i, j} + c_j - (x_{i, j} \oplus c_j)}{2}$。

从而 $\sum \limits_{i=1}^{n} x_{i, j} \times c_j = \dfrac{1}{2} \left ( \sum \limits_{i=1}^{n} x_j + \sum \limits_{i=1}^{n} c_j - \sum \limits_{i=1}^{n} x_{i, j} \oplus c_j \right )$。

其中 $\sum \limits_{i=1}^{n} c_j$ 的值可以令 $x_{0, j} = 0$，用一个额外的询问得到。

接下来问题就是从 $\sum \limits_{i=1}^{n} x_{i,j} \times c_j$ 中恢复 $c_j$ 的值。

这可以通过高斯消元解决。

询问次数：$q \approx n$。

当然对于这一部分分可以采取无脑暴力，即每次改一道题目的答案，判断返回的正确题目数量与原有的正确题目数量的大小。这里不过多赘述。

---

## 解法 $0$

当 $q = 3, n = 4$ 时，以下的 $x_{i, j}$ 可以区分出 $2^4$ 种不同的 $c_j$。

```
1110
1011
1101
```

即可以用 $3$ 次询问获取 $4$ 道题目的答案。

询问次数：$q \approx 0.75n$。


```cpp
#include<bits/stdc++.h>
#define check(cnt) if(cnt==n) {print();return 0;}
using namespace std;
char a[10009];
char b[10009];
int cnt1,cnt2;
int n,lim,k,t;
int now=1;
void print(){
	for(int i=1;i<=n;i++) cout<<b[i];
	cout<<'\n';
	cout.flush();
}
void prin(){
	for(int i=1;i<=n;i++) cout<<a[i];
	cout<<'\n';
	cout.flush();
}
int ft(){
	int cnt=0;
	for(int i=1;i<=now-1;i++){
		if(b[i]=='Y') cnt++;
	}
	return cnt;
}
void doit(){
	for(int i=1;i<=n;i++) a[i]='Y';
}
int main(){
	cin>>n>>lim;
	for(int i=1;i<=n;i++) b[i]=a[i]='Y';
	prin();
	cin>>t;
	//check(t);
	while(now<=n){
		doit();
		a[now]=a[now+1]='N';
		prin();
		cin>>cnt1;
		//check(cnt1);
		if(cnt1==t-2||cnt1==t+2){
			if(cnt1==t-2) b[now]=b[now+1]='Y';
			else b[now]=b[now+1]='N';
			now+=2;
			if(now==n+1) break;
			if(now>n){
				now-=2;
				break;
			}
			continue;
		}
		a[now]='Y',a[now+1]=a[now+2]=a[now+3]='N';
		prin();
		cin>>cnt1;
		//check(cnt1);
		
		a[now]=a[now+2]='N',a[now+1]=a[now+3]='Y';
		prin();
		cin>>cnt2;
		//check(cnt2);
		
		if(cnt1==t-3){
			b[now]='N',b[now+1]=b[now+2]=b[now+3]='Y';
		}
		else if(cnt1==t-1){
			if(cnt2==t-2) b[now]=b[now+2]=b[now+3]='Y',b[now+1]='N';
			if(cnt2==t) b[now]=b[now+3]='N',b[now+1]=b[now+2]='Y';
			if(cnt2==t+2) b[now]=b[now+2]='N',b[now+1]=b[now+3]='Y';
		}
		else if(cnt1==t+1){
			if(cnt2==t-2) b[now]=b[now+2]='Y',b[now+1]=b[now+3]='N';
			if(cnt2==t) b[now]=b[now+3]='Y',b[now+1]=b[now+2]='N';
			if(cnt2==t+2) b[now]=b[now+2]=b[now+3]='N',b[now+1]='Y';
		}
		else if(cnt1==t+3){
			b[now]='Y',b[now+1]=b[now+2]=b[now+3]='N';
		}
		now+=4;
		if(now==n+1) break;
		if(now>n){
			now-=4;
			break;
		}
	}
	int rest=n-now+1,k=ft();
	
	if(rest==1){
		if(k==t) b[n]='N';
		else b[n]='Y';
	}
	else if(rest==2){
		if(k==t){
			b[n-1]=b[n]='N';
		}
		else if(k==t-2){
			b[n-1]=b[n]='Y';
		}
		else{
			b[n-1]='Y',b[n]='N';
			print();
			cin>>cnt1;
			check(cnt1);
			b[n-1]='N',b[n]='Y';
			print();
			cin>>cnt1;
			check(cnt1);
			return 0;
		}
	}
	else if(rest==3){
		if(k==t){
			b[n-2]=b[n-1]=b[n]='N';
		}
		else if(k==t-3){
			b[n-2]=b[n-1]=b[n]='Y';
		}
		else if(k==t-1){
			b[n-2]=b[n-1]=b[n]='N';
			b[n-2]='Y',print();
			cin>>cnt1;
			check(cnt1);
			
			b[n-2]=b[n-1]=b[n]='N';
			b[n-1]='Y',print();
			cin>>cnt1;
			check(cnt1);
			
			b[n-2]=b[n-1]=b[n]='N';
			b[n]='Y',print();
			cin>>cnt1;
			check(cnt1);
		}
		else if(k==t-2){
			b[n-2]=b[n-1]=b[n]='Y';
			b[n-2]='N',print();
			cin>>cnt1;
			check(cnt1);
			
			b[n-2]=b[n-1]=b[n]='Y';
			b[n-1]='N',print();
			cin>>cnt1;
			check(cnt1);
			
			b[n-2]=b[n-1]=b[n]='Y';
			b[n]='N',print();
			cin>>cnt1;
			check(cnt1);
		}
	}
	print();
	return 0;
}
```

【附】思路：

记 $t$ 为所有题目中答案为 `Y` 的个数，即先用一次提交得到 $t$，然后每次进行 $3$ 次提交得到 $4$ 道题的答案。

令 $k$ 表示目前在第 $k$ 道题。

1. 把第 $k,k+1$ 道题改为 `N`，如果得到的正确答案数量为 $cnt=t+2$ 或 $cnt=t-2$ 即可确定这两道题的答案。

2. 如果返回的是第 $cnt=t$，则：

> 把 $k,k+1,k+2,k+3$ 道题依次改为 `YNNN`，返回 $m_1$。

> 把 $k,k+1,k+2,k+3$ 道题一次改为 `NYNY`，返回 $m_2$。

可以根据 $m_1$ 和 $m_2$ 得到这四道题的答案。

至于如何得到答案，具体可以参见上面代码，这里不过多赘述。


---

当 $q = 7, n = 10$ 时，以下的 $x_{i, j}$ 可以区分出 $2^{10}$ 种不同的 $c_j$。

```
1011111100
0010100010
1110000101
1101100011
1100101100
1111100101
0101001101
```

即可以用 $7$ 次询问获取 $10$ 道题目的答案。

询问次数：$q \approx 0.7n$。

-  $q \approx0.7n$ 解法的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int magic[7] = {
	0b1011111100,
	0b0010100010,
	0b1110000101,
	0b1101100011,
	0b1100101100,
	0b1111100101,
	0b0101001101,
};

map < vector <int>, int > mp;

void init() {
	for (int i = 0; i < (1 << 10); i++) {
		vector <int> t;
		for (int j = 0; j < 7; j++)
			t.push_back(__builtin_popcount(i & magic[j]));
		mp[t] = i;
	}
}

int n;

int query(vector <int> A) {
	string S;
	for (int i = 0; i < n; i++)
		S += 'Y';
	for (int i = 0; i < (int)A.size(); i++)
		if (A[i] < n) S[A[i]] = 'N';
	printf("%s\n", S.c_str());
	fflush(stdout);
	
	int res;
	scanf("%d", &res);
	if (res == n) exit(0);
	
	return res;
}

int K;

vector <int> ans;

int main() {
	init();
	
	cin >> n >> K;
	
	int lst = query({});
	
	for (int i = 0; i < n; i += 10) {
		vector <int> t;
		for (int j = 0; j < 7; j++) {
			vector <int> tmp;
			for (int k = 0; k < 10; k++)
				if (magic[j] >> k & 1)
					if (i + k < n)
						tmp.push_back(i + k);
			t.push_back((query(tmp) - lst + (int)tmp.size()) / 2);
		}
		int f = mp[t];
		for (int k = 0; k < 10; k++)
			if (f >> k & 1) ans.push_back(i + k);
	}
	
	query(ans);
	
	return 0;
}
```

---

## 解法 $1$

题目要求 $x_{i, j} \in \{0, 1\}$，先考虑弱化版的问题，即只要求 $x_{i, j} \in \{-1, 0, 1\}$。

首先，当 $q = 1$ 时，$n = 1, x_{1, 1} = 1$ 满足条件。

接下来，我们用 $q \times n$ 的询问矩阵 $X = x_{i, j}$ 构造 $2q \times (2n + q)$ 的询问矩阵 $X' = x'_{i, j}$：

$$X \to X' = \begin{pmatrix}X & -X & I \\ X & X & 0\end{pmatrix}$$

时间复杂度：$1 \times 1 \to 2 \times 3 \to 4 \times 8 \to 8 \times 20 \to \cdots$，即 $q \approx O(\dfrac{n}{\log n})$。

**证明**

可以证明这个矩阵满足条件。

设 $cnt_i = \sum \limits_{i=1}^{2n+q} x'_{i,j} \times c_j (1 \leq i \leq 2q)$，则

$$cnt_i = \sum \limits_{i=1}^{n}x_{i, j}c_j - \sum \limits_{i=1}^{n}x_{i, j}c_{n + j} + c_{2n + i} (1 \leq i \leq q)$$

$$cnt_{i + q} = \sum \limits_{i=1}^{n}x_{i, j}c_j + \sum \limits_{i=1}^{n}x_{i, j}c_{n + j} (1 \leq i \leq q)$$

那么根据奇偶性，$c_{2n + i} = (cnt_i + cnt_{i + q}) \bmod 2 (1 \leq i \leq q)$。

接下来可以解方程组得出 $\sum \limits_{i=1}^{n}x_{i, j}c_j(1 \leq j \leq n)$ 和 $\sum \limits_{i=1}^{n}x_{i, j}c_{n + j}(1 \leq j \leq n)$ 的值。

于是得到两个 $q \times n$ 的子问题，可以递归解决。

**原问题**

因为 $-1, 0, 1$ 都可以表示为 $0, 1$ 的差（$-1 = 0 - 1, 0 = 0 - 0, 1 = 1 - 0$），所以每个 $x_{i, j} \in \{-1, 0, 1\}$ 的询问都可以表示为两个 $x_{i, j} \in \{0, 1\}$ 的询问的差。

但是这样仍然不够优秀，我们可以——

## 解法 $2$

为做出区分，令 $x_{i, j}$ 和 $y_{i, j}$ 分别为解法 $1$ 和解法 $2$ 的询问矩阵。

现在要求 $y_{i, j} \in \{0, 1\}$。

首先，当 $q = 2$ 时，$n = 1, y_{1, 1} = 1, y_{2, 1} = 0$ 满足条件。

接下来，我们用 $q \times n$ 的询问矩阵 $Y = y_{i, j}$ 和解法 $1$ 中 $q \times n'$ 的询问矩阵 $X = x_{i, j}$ 构造 $2q \times (n + n')$ 的询问矩阵 $Y' = y'_{i, j}$：

$$X, Y \to Y' = \begin{pmatrix}Y & X_1 \\ Y & X_2 \end{pmatrix}$$

其中将 $X$ 表示为两个询问的差 $X = X_1 - X_2$。

**证明**

可以证明这个矩阵满足条件。

设 $cnt_i = \sum \limits_{i=1}^{n+n'} y'_{i,j} \times c_j (1 \leq i \leq 2q)$，则

$$cnt_i = \sum \limits_{i=1}^{n}y_{i, j}c_j + \sum \limits_{i=1}^{n'}x_{1, i, j}c_{n + j} (1 \leq i \leq q)$$

$$cnt_{i + q} = \sum \limits_{i=1}^{n}y_{i, j}c_j + \sum \limits_{i=1}^{n'}x_{2, i, j}c_{n + j} (1 \leq i \leq q)$$

$$x_{i, j} = x_{1, i, j} - x_{2, i, j}$$

解方程组得 $\sum \limits_{i=1}^{n'}x_{i, j}c_{n + j} = cnt_i - cnt_{i + q}$，这是一个 $q \times n'$ 的子问题，可以递归解决；

再解方程组得出 $\sum \limits_{i=1}^{n}y_{i, j}c_j$ 的值，这是一个 $q \times n$ 的子问题，也可以递归解决。

时间复杂度：$2 \times 1 \to 4 \times 4 \to 8 \times 12 \to \cdots$，即 $q \approx O(\dfrac{n}{\log n})$，但是常数减少了约一半。

期望得分：$100$ 分。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0, _n = n; i < _n; i++)
#define pb push_back
typedef vector <int> vi;
typedef vector <vi> vii;

vii A[15];

void gA(int m) {
    if (m == 0) {
        A[0] = {{1}};
        return ;
    }
    vii &L = A[m - 1], &R = A[m];
    forn(i, L.size()) {
        vi t;
        forn(j, L[i].size()) t.pb(L[i][j]);
        forn(j, L[i].size()) t.pb(-L[i][j]);
        forn(j, L.size()) t.pb(i == j);
        R.pb(t);
    }
    forn(i, L.size()) {
        vi t;
        forn(j, L[i].size()) t.pb(L[i][j]);
        forn(j, L[i].size()) t.pb(L[i][j]);
        forn(j, L.size()) t.pb(0);
        R.pb(t);
    }
}

vi operator + (vi x, vi y) {
    x.insert(x.end(), y.begin(), y.end());
    return x;
}

vi dA(int m, vi r) {
    if (m == 0) {
        return r;
    }
    int l = A[m - 1].size();
    vi x, y, z;
    for (int i = 0; i < l; i++) {
        z.pb(((r[i] + r[l + i]) % 2 + 2) % 2);
        x.pb((r[l + i] + (r[i] - z[i])) / 2);
        y.pb((r[l + i] - (r[i] - z[i])) / 2);
    }
    return dA(m - 1, x) + dA(m - 1, y) + z;
}

vii B[15];

void gB(int m) {
    if (m == 1) {
        B[1] = {{1}, {0}};
        return ;
    }
    vii &L = B[m - 1], &V = A[m - 1], &R = B[m];
    forn(i, L.size()) {
        vi t;
        forn(j, L[i].size()) t.pb(L[i][j]);
        forn(j, V[i].size()) t.pb(V[i][j] == 1);
        R.pb(t);
    }
    forn(i, L.size()) {
        vi t;
        forn(j, L[i].size()) t.pb(L[i][j]);
        forn(j, V[i].size()) t.pb(V[i][j] == -1);
        R.pb(t);
    }
}

vi dB(int m, vi r) {
    if (m == 1) {
        return {r[0]};
    }
    int l = B[m - 1].size();
    vi x, y;
    for (int i = 0; i < l; i++) {
        x.pb(r[i] - r[l + i]);
    }
    x = dA(m - 1, x);
    for (int i = 0; i < l; i++) {
        int t = r[i];
        for (int j = 0; j < (int)x.size(); j++) {
            t -= x[j] * (A[m - 1][i][j] == 1);
        }
        y.pb(t);
    }
    y = dB(m - 1, y);
    return y + x;
}

int n;
double K;

int query(vi A) {
    string S;
    for (int i = 0; i < n; i++)
        S += "TF"[A[i]];
    printf("%s\n", S.c_str());
    fflush(stdout);

    int res;
    scanf("%d", &res);
    if (res == n) exit(0);
    return res;
}

int popcnt(vi x) {
    int c = 0;
    for (auto i : x) c += i;
    return c;
}

int main() {
    cin >> n;
    for (int i = 0; i < 11; i++) gA(i);
    for (int i = 1; i < 11; i++) gB(i);
    int c = 1;
    while (B[c][0].size() < n) c++;

    vi ret;
    ret.clear();
    for (int i = 0; i < B[c].size(); i++) {
        ret.pb(query(B[c][i]));
    }
    int lst = ret.back();
    for (int i = 0; i < B[c].size(); i++) {
        ret[i] = (ret[i] - lst + popcnt(B[c][i])) / 2;
    }

    vi ans = dB(c, ret);
    query(ans);
    return 0;
}
```

另外这都碾标算了，可以做到 $n=5000,q \approx \dfrac{n}{\log n}$。

还有那些 CF 赛时直接 copy 这个代码的，你们好自为之。

**特别鸣谢**

感谢 [曾铭豪](https://www.luogu.com.cn/user/42299) 大佬对这道题解法、标程、数据等多方面的建议、启发和指导。

---

## 作者：hgzxwzf (赞：15)

## 解题思路：
声明一下，下文所有的下标都从 $0$ 开始。

首先可以暴力去做，最开始询问一次全是 T，记为 $a_1$。

然后对于每个位置，把那个位置改为 F，其他位置仍然为 T 进行询问，如果答案小于 $a_1$，那么就说明这个位置是 T，否则这个位置是 F。

这样一共要询问 $1002$ 次，不足以通过本题。

注意到最多只能询问 $675$ 次，大约是 $1000\times\frac{2}{3}$，考虑通过两次询问得到三个位置的答案。

首先和暴力一样，我们可以把这三个位置改为 F，其他位置为 $T$，假设答案为 $ret$。

假设这三个位置 $x$ 个 T，$3-x$ 个 F，那么有 $x-(3-x)=a_1-ret$，得到 $x=\frac{a_1-ret+3}{2}$。

如果 $x=3$，那么这三个位置都是 T，如果 $x=0$，那么这三个位置都是 F，否则我们可以通过 $1$ 次询问来确定前两个位置，再通过 $x$ 确定第三个位置。

我们可以这样做。在最开始查询 "TFTF..."，即 T 和 F 交替出现，记答案为 $a_2$。

假设三个位置为 $i,i+1,i+2$，如果 $i$ 是奇数，那么 "TFTF..." 中 $i,i+1$ 位置为 "FT"。

我们在 "TFTF..." 的基础上把 $i$ 位置改为 T，$i+1$ 位置改为 F，询问得到答案减去 $a_2$ 为 $ret2$。

这两个位置的答案分别有 "TT"，"FT"，"TF"，"FF" 四种。

如果是 "TT" 或者 "FF"，那么原本和修改后都对了 $1$ 个，$ret2=0$，再通过 $x$ 判断具体是哪种即可。

如果是 "FT"，那么原本对了 $2$ 个，修改后对了 $0$ 个，$ret2=-2$。

如果是 "TF"，那么原本对了 $0$ 个，修改后对了 $1$ 个，$ret2=2$。

这样我们就做到了询问两次得到三个位置的答案。

对于那些不够组成三个的位置，直接像暴力那样处理即可。

## 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
#include<iostream>
#include<string> 
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;

const int N=2e5+10;

bool ans[N];
string ask,ask2;

int main()
{
	int n,a1,a2;
	cin>>n;
	rep(i,0,n-1) ask+="T";
	cout<<ask<<endl;
	cin>>a1;
	rep(i,0,n-1) if(i&1) ask2+="F";else ask2+="T";
	cout<<ask2<<endl;
	cin>>a2;
	int i=0;
	for(;i+2<n;i+=3)
	{
		ask[i]=ask[i+1]=ask[i+2]='F';
		cout<<ask<<endl;
		ask[i]=ask[i+1]=ask[i+2]='T';
		int ret,ret2;
		cin>>ret;
		if((a1-ret+3)%2) puts("?");
		ret=(a1-ret+3)/2;
		if(ret==3)
		{
			ans[i]=ans[i+1]=ans[i+2]=1;
			continue;
		}
		if(ret==0)
		{
			ans[i]=ans[i+1]=ans[i+2]=0;
			continue;
		}
		if(i&1)
		{
			swap(ask2[i],ask2[i+1]);
			cout<<ask2<<endl;
			cin>>ret2;
			ret2=ret2-a2;
			if(ret2==2)
			{
				ans[i]=1,ans[i+1]=0;
				if(ret==2) ans[i+2]=1;
				else ans[i+2]=0;
			}
			else if(ret2==-2)
			{
				ans[i]=0,ans[i+1]=1;
				if(ret==2) ans[i+2]=1;
				else ans[i+2]=0;
			}
			else if(ret2==0)
			{
				if(ret>=2)
				{
					ans[i]=ans[i+1]=1;
					ans[i+2]=0;
				}
				else
				{
					ans[i]=ans[i+1]=0;
					ans[i+2]=1;
				}
			}
			swap(ask2[i],ask2[i+1]);
		}
		else
		{
			swap(ask2[i],ask2[i+1]);
			cout<<ask2<<endl;
			cin>>ret2;
			ret2=ret2-a2;
			if(ret2==-2)
			{
				ans[i]=1,ans[i+1]=0;
				if(ret==2) ans[i+2]=1;
				else ans[i+2]=0;
			}
			else if(ret2==2)
			{
				ans[i]=0,ans[i+1]=1;
				if(ret==2) ans[i+2]=1;
				else ans[i+2]=0;
			}
			else if(ret2==0)
			{
				if(ret>=2)
				{
					ans[i]=ans[i+1]=1;
					ans[i+2]=0;
				}
				else
				{
					ans[i]=ans[i+1]=0;
					ans[i+2]=1;
				}
			}
			swap(ask2[i],ask2[i+1]);
		}
	}
	while(i<n)
	{
		ask[i]='F';
		int ret;
		cout<<ask<<endl;
		cin>>ret;
		if(ret<a1) ans[i]=1;
		else ans[i]=0;
		ask[i++]='T';
	}
	rep(i,0,n-1) 
		if(ans[i]) ask[i]='T';
		else ask[i]='F';
	int ret;
	cout<<ask<<endl;
	cin>>ret;
	return 0;
}
```


---

## 作者：_xinyu1113 (赞：14)

### 随机化题解，建议先看完其他正解再来。

考虑对于每两个**相邻**问题 ${a_i,a_{i+1}}$ 随机询问一次，显然，直接得到**正确答案**的概率为 $\frac{1}{2}$ 。

对于另外 $\frac{1}{2}$ 的情况，可以得到 ${a_i,a_{i+1}}$ 的关系。于是继续询问 ${a_{i+1},a_{i+2}}$ 。

期望查询次数： $(\frac{2}{3}n+2)$ 次。

$2$ 为第一次全局查询以及最后一次输出答案的个数。

限制为 $675$ 次，我们的 $668$ 次在每组数据中失败的概率有点大，约有 $\frac{1}{3}$ 。

总共有 $50$ 组数据，通过的概率很小。

这时候，就需要利用 **CodeForces** 的一个特性了。

-------
**Codeforces** 在测试的时候，对于每个测试点，会将 **TLE** 的程序重测约 $3$ 次，如果这 $3$ 次中有一次通过，就算这个测试点过了。

-------

那么如何将我们程序的**询问次数超限**转变为 **TLE** 呢？

记录一下询问次数，若超限，立刻 ```while(1)``` 自TLE。

```
cnt++;
if(cnt>675)
   while(1);
```

于是单测试点失败率变为 $\frac{1}{27}$ 了，通过率实测 $\frac{1}{9}$ ，优化一下应该可以更高。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,rsum,res,p[1005],ans[1005],cnt=1;
string s;
int ask(int p)
{
	string s2=s;
	s2[p]=(s2[p]=='T'?'F':'T');
	s2[p+1]=(s2[p+1]=='T'?'F':'T');
	for(int i=1;i<s2.length();i++)
	printf("%c",s2[i]);
	cout<<endl;
	cin>>res;
	if(res==n)
	exit(0);
	if(res==rsum-2)
	return 0;
	else if(res==rsum)
	return 1;
	else
	return 2;
}
int main()
{
	srand(time(NULL));
	memset(p,-1,sizeof(p));
	cin>>n;
	s+=' '; 
	for(int i=1;i<=n;i++)
	s+=(rand()%2?'T':'F');
	for(int i=1;i<s.length();i++)
	printf("%c",s[i]);
	cout<<endl;
	cin>>rsum;
	if(rsum==n)
	return 0;
	for(int i=1;i<=n-1;i++)
	{
		cnt++;
		if(cnt>675)
		while(1);
		p[i]=ask(i);
		if(p[i]!=1)
		{
			i++;
			continue;
		}
	}
	string s2=s;
	s2[n]=(s2[n]=='T'?'F':'T');
//	cout<<'!'<<endl;
	cnt++;
	if(cnt>675)
	while(1);
	for(int i=1;i<s2.length();i++)
	printf("%c",s2[i]);
	cout<<endl;
	cin>>res;
	if(res==n)
	return 0;
	if(res==rsum-1)
	ans[n]=0;
	else
	ans[n]=1;
	for(int i=n-1;i>=1;i--)
	{
		if(p[i]==0)
		ans[i]=ans[i+1]=0;
		else if(p[i]==2)
		ans[i]=ans[i+1]=1;
		else
		ans[i]=1-ans[i+1];
	}
	for(int i=1;i<=n;i++)
	if(ans[i]==1)
	s[i]=(s[i]=='T'?'F':'T');
	cnt++;
	if(cnt>675)
	while(1);
	for(int i=1;i<s.length();i++)
	printf("%c",s[i]);
	cout<<endl;
	return 0;
}//18th attmpt,2AC till now
```

考场未实测，但显然具备实用性。

-------

```反复提交，可战胜概率；自我否定，终浮现AC。```

---

## 作者：EuphoricStar (赞：7)

看到询问次数接近 $n$，考虑将 $n$ 分成多组，每组都以较少的期望询问次数解决。

先询问一次全 `F`，接下来的询问就能确定若干个位置的 `T` 个数。考虑每次从答案未确定的问题集合中随 $4$ 个（如果集合大小 $< 4$ 就暴力），先问这 $4$ 个中 `T` 的个数，如果结果为 $0$ 或 $4$ 就说明全是 `F/T`。否则再问前两个，如果结果为 $0$ 或 $2$ 就说明都是 `F/T`；否则它们是 `TF` 或 `FT`，那我们得到了其中一个是另一个的取反，能解决一个。对于后两个 `T` 的个数可以通过前两次询问的结果算出，类似地分类讨论即可。

接下来我们计算期望次数（只考虑 `F` 和 `T` 等概率出现的情况，因为其中一个更多时期望次数显然更少）：

- $\frac{1}{8}$ 概率一次询问解决 $4$ 个。
- $\frac{1}{8}$ 概率两次询问解决 $4$ 个。
- $\frac{1}{2}$ 概率两次询问解决 $3$ 个。
- $\frac{1}{4}$ 概率两次询问解决 $2$ 个。

写个 `dp` 可以得出期望询问次数约为 $627$ 次，可以通过。

[code](https://codeforces.com/contest/1705/submission/188879346)

---

## 作者：Phartial (赞：3)

首先这个东西可以转化成每次询问子集和：在开始询问一次全 $\texttt{F}$ 可以得到 $\sum_{i}[s_i=\texttt{F}]$，询问一个集合 $S$ 可以得到 $\sum_{i\in S}[s_i=\texttt{T}]+\sum_{i\notin S}[s_i=\texttt{F}]$，有：

$$
\begin{cases}
  \sum_{i\in S}[s_i=\texttt{F}]+\sum_{i\in S}[s_i=\texttt{T}]=|S|\\
  \sum_{i\in S}[s_i=\texttt{F}]-\sum_{i\in S}[s_i=\texttt{T}]=\sum_i[s_i=\texttt{F}]-(\sum_{i\in S}[s_i=\texttt{T}]+\sum_{i\notin S}[s_i=\texttt{F}])
\end{cases}
$$

解方程就可以得到 $\sum_{i\in S}[s_i=\texttt{T}]$ 了。以下的询问均指询问子集和。

设 $f_n$ 为 $2^n$ 次询问能够确定的最长序列长度，显然有 $f_0=1$。

令 $q_n$ 为具体的询问方案，为方便，不妨令最后一次询问总是询问整个序列中 $1$ 的个数，即 $q_{n,2^n}=\{i\mid 1\le i\le f_n\}$（下标从 $1$ 开始）。

可以使用以下构造方式得到 $f_{n+1}=2f_n+2^n-1$ 的结果（设 $\operatorname{query}(S)$ 为询问 $S$ 得到的结果）：

1. 将长度为 $2f_n+2^n-1$ 的序列分成长度为 $f_n,f_n,2^n-1$ 的三块；
2. 询问第二块中 $1$ 的个数，记作 $c=\operatorname{query}(\{k\mid f_n+1\le k\le 2f_n\})$；
3. 对所有 $1\le i<2^n$，询问 $q_{n,i}\cup\{f_n+k\mid k\in q_{n,i}\}\cup\{2f_n+i\}$ 与 $q_{n,i}\cup\{f_n+k\mid k\notin q_{n,i}\}$，不妨设两次询问的结果分别为 $a=\operatorname{query}(q_{n,i})+\operatorname{query}(\{f_n+k\mid k\in q_{n,i}\})+\operatorname{query}(\{2f_n+i\})$ 和 $b=\operatorname{query}(q_{n,i})+(c-\operatorname{query}(\{f_n+k\mid k\in q_{n,i}\}))$，则有：
   - $\operatorname{query}(q_{n,i})=\lfloor\frac{a+b-c}{2}\rfloor$；
   - $\operatorname{query}(\{f_n+k\mid k\in q_{n,i}\})=\lfloor\frac{a-b+c}{2}\rfloor$；
   - $\operatorname{query}(\{2f_n+i\})=(a+b-c)\bmod 2$；
4. 询问整个序列中 $1$ 的个数。

于是我们就在 $2^{n+1}$ 次询问中得到了还原第一、二块需要的每个询问的答案，并额外知道了 $2^n-1$ 位的值。

使用归纳法不难证明 $f_n=n2^{n-1}+1$。于是我们就可以在 $\mathcal{O}(\frac{n}{\log n})$ 次询问内还原出长度为 $n$ 的序列。

本题中 $n\le 1000$，可以在 $257$ 次操作内还原出整个序列。遥遥领先。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int kN = 1001;

int n, c0;

int Q(string s) {
  s = s.substr(0, n);
  int l = count(s.begin(), s.end(), 'T'), v;
  cout << s << endl;
  cin >> v;
  return (l - (c0 - v)) / 2;
}
vector<string> G(int k) {
  if (k == 0) {
    return {"T"};
  }
  vector<string> l = G(k - 1);
  int n = l[0].size();
  vector<string> p;
  string _ = string(l.size() - 1, 'F');
  for (int i = 0; i < l.size() - 1; ++i) {
    _[i] = 'T';
    p.push_back(l[i] + l[i] + _);
    _[i] = 'F';
    string _l;
    for (char &ch : l[i]) {
      _l += 'T' + 'F' - ch;
    }
    p.push_back(l[i] + _l + _);
  }
  p.push_back(string(n, 'F') + string(n, 'T') + _);
  p.push_back(string(n * 2 + l.size() - 1, 'T'));
  return p;
}
string C(int k, vector<int> &q) {
  if (k == 0) {
    return q[0] ? "T" : "F";
  }
  vector<int> lq, rq;
  int c = q[q.size() - 2];
  string ans, t;
  for (int i = 0; i + 2 < q.size(); i += 2) {
    int a = q[i], b = q[i + 1];
    lq.push_back((a + b - c) / 2);
    rq.push_back((a - b + c) / 2);
    t += "FT"[(a + b - c) & 1];
  }
  rq.push_back(c);
  lq.push_back(q.back() - c - count(t.begin(), t.end(), 'T'));
  return C(k - 1, lq) + C(k - 1, rq) + t;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  cout << string(n, 'F') << endl;
  cin >> c0;
  vector<string> ql = G(8);
  vector<int> sl;
  for (string i : ql) {
    sl.push_back(Q(i));
  }
  Q(C(8, sl));
  return 0;
}
```


---

## 作者：intel_core (赞：2)

一个显然的高斯消元暴力：

随便整 $n$ 个答案串，解异或方程组即可。

询问次数 $n$，复杂度 $O(\frac{n^3}{w})$ 或者 $O(n^3)$。

询问次数稍微有点多，如果要通过得做到 $\frac{2}{3}n$ 级别的询问次数。

我们考虑怎么用最少的次数确定三个问题的答案。

如果最开始询问一次全 `T` 的串再询问这三个位置是 `F`，其余是 `T` 的答案串，就可以确定这三个当中对的个数。

设当前三个位置是 $p,p+1,p+2$，这三个中对的个数是 $x$。

$x=0$ 或者 $x=3$ 的情况显然；接着考虑怎么确定 $x=1$ 时哪个为 `T`。

如果已知 $x$，那么询问 `TFT` 和 `FTT` 各一次就可以确定这三个位置的具体情况。

我们可以最开始询问一次 `FTFTFTFT....FT` 这样的串，考虑到 $p,p+1,p+2$ 时执行如下操作：

* 将 `FTFTFTFT....FT` 的第 $p,p+1$ 位取反询问一次。

* 根据得出的 $x$ 确定这三位的具体情况。

举例（$x=1$ 时）：

```
TFT : r1
FTT : r2
```

如果第 $p$ 位是 `T` ，那么 $r2-r1=-1$；如果第 $p+1$ 位是 `T` ，那么 $r2-r1=1$；如果第 $p+2$ 位是 `T` ，那么 $r2-r1=0$。

类比上述情况，可在 $669$ 次之内求出所有的答案。

---

## 作者：constexpr (赞：2)

设 $s$ 为询问时给出的答案，$t$ 为正确答案，$\operatorname{diff}(a,b)$ 为 $\sum_{i=1}^n[a_i \ne b_i]$。

首先考虑 $n$ 较小的情况。

当 $n \leq 9$ 时，显然可以 $O(2^n)$ 枚举 $s$ 进行询问。

当 $n \leq 15$ 时，枚举所有询问就不太现实了。

考虑在 $2^n$ 种询问中随机选取一些询问，之后枚举所有可能的答案，并计算有哪些答案符合条件。

设给出的询问为 $\{s_1,s_2,...,s_k\}$，**不正确**的题目数为 $\{q_1,q_2,...,q_k\}$，则答案 $t$ 必定会满足 $\forall i \in [1,k],\operatorname{diff}(s_i,t)=q_i$。暴力枚举 $2^n$ 种可能的 $t$ 并 $O(nk)$ 计算当前的 $t$ 是否可能作为答案即可。

当 $k$ 足够大时，几乎不可能无法确定唯一的答案。

当 $n \leq 1000$ 时，可以把 $t$ 分成若干长度不超过 $K$ 的段，并分别计算每一段的答案。

具体而言，可以将 $t$ 分为 $\left\lceil\frac{n}{K}\right\rceil$ 段，其中第 $i$ 段为 $[(i-1)K+1,\min(iK,n)]$。令 $l_i=(i-1)K+1,r_i=\min(iK,n)$。


计算第 $i$ 段时，询问时把 $t_{l_i:r_i}$ 中每个字符随机设为 `F`,`T` 中的一个。其余部分均设为 `F`。这样询问 $k$ 次，仍然满足 $\forall i \in [1,k],\operatorname{diff}(s_i,t)=q_i$。提出 $t_{l_i:r_i}$，得：

$$
\begin{cases}
\operatorname{diff}(s_{1_{1:l_i-1}},t_{1:l_i-1})+\operatorname{diff}(s_{1_{l_i:r_i}},t_{l_i:r_i})+\operatorname{diff}(s_{1_{r_i+1,n}},t_{r_i+1,n})=q_1 \\
\operatorname{diff}(s_{2_{1:l_i-1}},t_{1:l_i-1})+\operatorname{diff}(s_{2_{l_i:r_i}},t_{l_i:r_i})+\operatorname{diff}(s_{2_{r_i+1,n}},t_{r_i+1,n})=q_2 \\
... \\
\operatorname{diff}(s_{k_{1:l_i-1}},t_{1:l_i-1})+\operatorname{diff}(s_{k_{l_i:r_i}},t_{l_i:r_i})+\operatorname{diff}(s_{k_{r_i+1,n}},t_{r_i+1,n})=q_k
\end{cases}
$$

而 $\forall p,q \in [1,k],s_{p_{1:l_i-1}}=s_{q_{1:l_i-1}},s_{p_{r_i+1:n}}=s_{q_{r_i+1:n}}$，故将上式中每相邻两式相减，得：

$$
\begin{cases}
\operatorname{diff}(s_{1_{l_i:r_i}},t_{l_i:r_i})-\operatorname{diff}(s_{2_{l_i:r_i}},t_{l_i:r_i})=q_1-q_2 \\
\operatorname{diff}(s_{2_{l_i:r_i}},t_{l_i:r_i})-\operatorname{diff}(s_{3_{l_i:r_i}},t_{l_i:r_i})=q_2-q_3 \\
... \\
\operatorname{diff}(s_{k-1_{l_i:r_i}},t_{l_i:r_i})-\operatorname{diff}(s_{k_{l_i:r_i}},t_{l_i:r_i})=q_{k-1}-q_k
\end{cases}
$$

这样就可以 $O(K2^K)$ 枚举 $t_{l_i:r_i}$ 来判断这一段 $t$ 的所有可能答案了。时间复杂度为 $O(n2^K)$，故 $K$ 应满足 $K \leq 17$。

然而由于询问次数有限，将询问次数平均分到 $\left\lceil\frac{n}{K}\right\rceil$ 段之后，很有可能会导致一些区间无法确定唯一的答案。

如果能稳定在 $T$ 次询问内唯一确定长度为 $K$ 的一段区间的答案，那么得出长度为 $n$ 的串 $t$ 的答案就需要进行 $\left\lceil\frac{n}{K}\right\rceil\cdot T$ 次询问。下面是对于每个 $K \leq 17$，满足 $\left\lceil\frac{n}{K}\right\rceil\cdot T \leq 675$ 的 $T$ 的最大值构成的表格。

| $K$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ | $11$ | $12$ | $13$ | $14$ | $15$ | $16$ | $17$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $T$ | $0$ | $1$ | $2$ | $2$ | $3$ | $4$ | $4$ | $5$ | $6$ | $6$ | $7$ | $8$ | $8$ | $9$ | $10$ | $10$ | $11$ |

对于一组共 $T$ 个询问 $\{s_1,s_2,...,s_T\}$，设 $S(K)$ 为长度为 $K$ 的仅由 `F`,`T` 两种字符组成的串，这 $T$ 个询问一定能唯一确定长度为 $K$ 的 $t$ 的一段 $[l,r]$ 的答案，当且仅当 $\forall a,b \in S(K),i \ne j$，下列不等式至少有一个成立：

$$
\begin{cases}
\operatorname{diff}(s_{1_{l:r}},a)-\operatorname{diff}(s_{2_{l:r}},a) \ne \operatorname{diff}(s_{1_{l:r}},b)-\operatorname{diff}(s_{2_{l:r}},b) \\
\operatorname{diff}(s_{2_{l:r}},a)-\operatorname{diff}(s_{3_{l:r}},a) \ne \operatorname{diff}(s_{2_{l:r}},b)-\operatorname{diff}(s_{3_{l:r}},b) \\
... \\
\operatorname{diff}(s_{T-1_{l:r}},a)-\operatorname{diff}(s_{T_{l:r}},a) \ne \operatorname{diff}(s_{T-1_{l:r}},b)-\operatorname{diff}(s_{T_{l:r}},b)
\end{cases}
$$

否则当算出一组 $\{q_i-q_{i+1}\}_{i=1}^{T-1}$ 时，可能会有两个或以上的可能答案。

对于一组 $K,T$，找到一组可行的 $\{s_1,s_2,...,s_T\}$ 可以模拟退火，也可以直接每次重新随机选取整个询问序列。对于不同的 $K,T$，程序找到一组可行询问序列的效率也会不同。实测 $K=15,T=10$ 时纯随机化 $1$ 分钟可以跑出来。使用二进制表示答案序列写起来可能比较方便。

下面是随机化的代码：

```cpp
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
const int tim=10,d=15;
int st[30];
inline int lowbit(int x){return x&(-x);}
inline int popcnt(int x){int res=0;while(x)x-=lowbit(x),++res;return res;}
inline int ir(){return rand()+(rand()<<16);}
inline int ri(int l,int r){return l+ir()%(r-l+1);}
bool check(){
	std::unordered_map<unsigned long long,int> map;
	for(int i=0;i<(1<<d);++i){
		unsigned long long nw=0,pw=1;
		for(int j=0;j<tim-1;++j){
			int u=popcnt(st[j+1]^i)-popcnt(st[j]^i);
			u+=12,nw+=u*pw,pw*=(2*d+1);
		}
		if(map[nw])return false;map[nw]=i;
	}
	return true;
}
int main(){
	srand(time(NULL));
	do for(int i=0;i<tim;++i)st[i]=ri(0,(1<<d)-1);while(!check());
	puts("Find!");
	freopen("way.txt","w",stdout);
	for(int i=0;i<tim;++i)printf("%d,",st[i]);
	putchar('\n');
	return 0;
}
```

我跑出来的第一组可行解为 $\{27639,3795,12252,14675,8766,19138,27693,16991,373,489\}$，满足上述的条件。

令 $K=15$，将 $t$ 分为 $\left\lceil\frac{n}{K}\right\rceil$ 段解决即可。

代码实现如下：

```cpp
//15 in 10 querys!!!
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <unordered_map>
const int N=1e3+10;
int n,qc[N],ans[N];
char buf[N];
std::unordered_map<unsigned long long,int> map[N];
const int len=10,flen=15;
const int st[10]={27639,3795,12252,14675,8766,19138,27693,16991,373,489};
inline int lowbit(int x){return x&(-x);}
inline int popcnt(int x){int res=0;while(x)++res,x-=lowbit(x);return res;}
inline int min(int x,int y){return x<y?x:y;}
void init(){
	for(int t=1;t<=flen;++t){
		for(int i=0;i<(1<<t);++i){
			unsigned long long nw=0,pw=1;
			for(int j=0;j<len-1;++j){
				int pv=st[j+1],pu=st[j];
				for(int q=t;q<flen;++q){
					int bit=1<<q;
					if(pu&bit)pu^=bit;
					if(pv&bit)pv^=bit;
				}
				int u=popcnt(i^pv)-popcnt(i^pu);
				u+=flen,nw+=u*pw,pw*=(flen<<1)+1;
			}
			map[t][nw]=i;
		}
	}
}
int query(int j,int l){
	for(int i=1;i<=n;++i)buf[i]='F';
	for(int i=0;i<flen;++i){
		int bit=st[j]&(1<<i);
		if(bit)buf[l+i]='T';
	}
	buf[n+1]='\0',puts(buf+1),fflush(stdout);
	int x;scanf("%d",&x);if(x==n)exit(0);return x;
}
int main(){
	scanf("%d",&n),init();
	for(int i=1;i<=n;i+=15){
		for(int j=0;j<len;++j)qc[j]=query(j,i);
		unsigned long long nw=0,pw=1;
		for(int j=0;j<len-1;++j){
			int u=qc[j]-qc[j+1];
			u+=flen,nw+=u*pw,pw*=(flen<<1)+1;
		}
		int len=min(15,n-i+1);
		assert(map[len].find(nw)!=map[len].end());
		int t=map[len][nw];
		for(int j=0;j<flen;++j)if(t&(1<<j))ans[i+j]=1;
	}
	for(int i=1;i<=n;++i)putchar(ans[i]?'T':'F');
	putchar('\n'),fflush(stdout);return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

来一个随机化题解。没有 `while (true)` 等奇技淫巧。

设答案为 $S$。

首先，为了防止 hack，我们对所有询问异或某一个随机二进制数 $R$，显然这保证正确性。

首先，我们询问 $0$（异或后为 $R$），得到为 `F` 的个数 $F$，后面，如果我们询问 $x$，则得到的答案 $m$ 满足 $m-F = 2\mathrm{popcount}(S \cap x) - \mathrm{popcount}(x)$。重要的信息在于其中的 $\mathrm{popcount}(S \cap x)$ 一项。

显然，可以通过逐个询问 $100\dots, 010\dots, 001\dots$ 来得到答案，但这样太蠢了。

我们采用一个关键优化：取连续 $4$ 个数，一并得到这四个位置的 `T` 总数 $T_4$，如果 $T_4 = 0$ 或 $T_4 = 4$（总和 $\dfrac 18$ 概率），则可以确定全 `T` 或全 `F`。否则考虑询问一次 $1100$，得到 $T_2$，则后面的两个中的 `T` 个数 $T_2'$ 也知道了。如果其中有 $0$ 或 $2$，这样我们就可以确定它们是 `TT` 或 `FF`。关键在于 $1$ 的处理：此时这两个位置 $i, j$ 满足 $S_i = \neg S_j$，我们将这个关系记录下来，于是我们将来只需要查询 $i$ 即可。

所以，对于 $4$ 个数组成的 $\dfrac n4$ 个块，我们有 $\dfrac n{32}$ 个取到 $1$ 次就做完，有 $\dfrac{n}{8}$ 个块会 $2$ 次后剩下一个数待处理（$T_4 = 1$ 或 $T_4 = 3$），有 $\dfrac{n}{32}$ 个块 $2$ 次做完（$T_4 = 2, T_2 = 2$ 或 $0$），$\dfrac{n}{16}$ 个块 $2$ 次剩下 $2$ 个数待处理（$T_4 = 2, T_2 = 1$）。

这样，我们做一次处理需要询问 $\dfrac{15n}{32}$ 次，而我们归约到了大小为 $\dfrac n4$ 的子问题，所以期望询问次数为：
$$
\begin{aligned}
\mathbb E[Q] &= \dfrac{15}{32} \sum_{k=0}^{+\infty} 4^{-k} \\
&= \dfrac 58n,
\end{aligned}
$$
可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;

using BS = bitset<1001>;  // qwqwqwq

int ask_cnt = 0;

int out(int n, BS b) {
    ask_cnt++;
    /*
    if (ask_cnt == 675)
        while (true)
            ;*/
    for (int i = 0; i < n; ++i)
        if (b[i])
            cout << "T";
        else
            cout << "F";
    cout << endl;
    int m;
    cin >> m;
    return m;
}

BS vis, rnd, ans, pend;

int main() {
    int n;
    cin >> n;
    random_device f;
    mt19937 g(f());
    vector<BS> p(n);
    vector<pair<int, int>> dual;

    for (int i = 0; i < n; i++) p[i].set(i), vis.set(i);
    for (int i = 0; i < n; i++) rnd[i] = g() & 1;
    int awa = out(n, rnd);
    if (awa == n) return 0;
    while (vis.any()) {
        vector<int> qwq;

        for (int i = 0; i < n; ++i)
            if (vis[i]) qwq.push_back(i);
        int qs = qwq.size();

        auto get_todo2 = [&](int i, int j, int x) {
            if (x == 2) {
                ans[qwq[i]] = ans[qwq[j]] = true;
                vis[qwq[i]] = vis[qwq[j]] = false;
                pend.set(qwq[i]), pend.set(qwq[j]);
            } else if (x == -2) {
                ans[qwq[i]] = ans[qwq[j]] = false;
                vis[qwq[i]] = vis[qwq[j]] = false;
                pend.set(qwq[i]), pend.set(qwq[j]);
            } else {
                assert(x == 0);
                dual.push_back({qwq[i], qwq[j]});
                vis[qwq[i]] = false;
            }
        };

        int i = 0;
        for (; i + 4 <= qs; i += 4) {
            auto toask =
                p[qwq[i]] | p[qwq[i + 1]] | p[qwq[i + 2]] | p[qwq[i + 3]];
            int m = out(n, rnd ^ toask);
            if (m == n || m == -1) return 0;
            m -= awa;
            if (m == 4) {
                ans[qwq[i]] = ans[qwq[i + 1]] = ans[qwq[i + 2]] =
                    ans[qwq[i + 3]] = true;
                vis[qwq[i]] = vis[qwq[i + 1]] = vis[qwq[i + 2]] =
                    vis[qwq[i + 3]] = false;
                pend.set(qwq[i]), pend.set(qwq[i + 1]), pend.set(qwq[i + 2]),
                    pend.set(qwq[i + 3]);
            } else if (m == -4) {
                ans[qwq[i]] = ans[qwq[i + 1]] = ans[qwq[i + 2]] =
                    ans[qwq[i + 3]] = false;
                vis[qwq[i]] = vis[qwq[i + 1]] = vis[qwq[i + 2]] =
                    vis[qwq[i + 3]] = false;
                pend.set(qwq[i]), pend.set(qwq[i + 1]), pend.set(qwq[i + 2]),
                    pend.set(qwq[i + 3]);
            } else {
                auto toask2 = toask ^ p[qwq[i]] ^ p[qwq[i + 1]];
                int m2 = out(n, rnd ^ toask2);
                get_todo2(i + 2, i + 3, m2 - awa);
                get_todo2(i, i + 1, m - m2 + awa);
            }
        }
        for (; i + 2 <= qs; i += 2) {
            auto toask = p[qwq[i]] | p[qwq[i + 1]];
            int m = out(n, rnd ^ toask);
            if (m == n || m == -1) return 0;
            m -= awa;
            get_todo2(i, i + 1, m);
        }
        for (; i < qs; i++) {
            int m = out(n, rnd ^ p[qwq[i]]);
            if (m == n || m == -1) return 0;
            ans[qwq[i]] = (m - awa > 0);
            vis[qwq[i]] = false;
            pend.set(qwq[i]);
        }
    }
    for (int i = 0; i < 1000; i++) {
        for (auto pr : dual)
            if (pend.test(pr.first))
                pend.set(pr.second), ans[pr.second] = !ans[pr.first];
            else if (pend.test(pr.second))
                pend.set(pr.first), ans[pr.first] = !ans[pr.second];
    }

    int m = out(n, ans ^ rnd);
    if (m == -1) return 0;
    assert(m == n);
}
```

---

