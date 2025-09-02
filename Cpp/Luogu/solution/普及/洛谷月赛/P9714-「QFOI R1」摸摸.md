# 「QFOI R1」摸摸

## 题目描述

小 R 是一个可爱的女孩子，她喜欢被摸头。

但是摸头之前，必须答对她提出的一个问题。

她有一个长度为 $n$ 的数列 $a$，初始时所有元素均为 $0$。另有两个长度为 $n$ 的数列 $t,b$。

她可以进行两种操作：

1. 将 $t$ 与 $t$ 的倒序对应元素相加，得到新的 $t$。
    - 例如，$t=[1,4,2]$ 变为 $t'=[1+2,4+4,2+1]=[3,8,3]$。
2. 将 $a$ 与 $t$ 对应元素相加，得到新的 $a$。
    - 例如，$a=[1,2,3],t=[1,4,2]$ 变为 $a'=[1+1,2+4,3+2]=[2,6,5]$。

是否可能通过若干次以上操作将 $a$ 变为 $b$？

你希望摸她的头 $T$ 次，因此有 $T$ 组数据。

## 说明/提示

**样例解释**

对于第一组数据：

- 初始时：$a=[0,0,0]$，$t=[1,2,2]$，$b=[5,8,7]$。
- 执行操作二：$a=[1,2,2]$，$t=[1,2,2]$，$b=[5,8,7]$。
- 执行操作二：$a=[2,4,4]$，$t=[1,2,2]$，$b=[5,8,7]$。
- 执行操作一：$a=[2,4,4]$，$t=[3,4,3]$，$b=[5,8,7]$。
- 执行操作二：$a=[5,8,7]$，$t=[3,4,3]$，$b=[5,8,7]$。

此时 $a=b$，符合要求。

对于第二组数据，可以证明不存在合法方案。

---

**数据范围**

本题共 $20$ 个测试点，每个测试点 $5$ 分。

记 $\sum n$ 表示每组数据的 $n$ 之和。

对于全部数据，保证 $1\le\sum n\le 2\times 10^3$，$n\ge 1$，$1\le t_i,b_i\le 2\times 10^3$。

- 对于测试点 $1\sim 4$：保证 $n\le 2$。
- 对于测试点 $5\sim 8$：保证所有 $t_i$ 都相等。
- 对于测试点 $9\sim 12$：保证 $b_i=b_{n-i+1}$。
- 对于测试点 $13\sim 16$：保证 $\sum n,t_i,b_i\le 200$。
- 对于测试点 $17\sim 20$：无特殊限制。

---

**Hack 数据**

本题在赛后添加了 Hack 数据，从 $21$ 开始编号。

原有测试点依然计 $5$ 分，Hack 数据计 $0$ 分，但只有通过所有数据才会被判为 Accepted。

为区分原有测试点和 Hack 数据，本题添加了子任务，但子任务的计分方式为“加和”，不会影响正常评测。

## 样例 #1

### 输入

```
2
3
1 2 2
5 8 7
3
1 2 2
2 4 3```

### 输出

```
Yes
No```

# 题解

## 作者：rui_er (赞：22)

这里是官方题解。

记数列 $a$ 的倒序为 $\bar{a}$，记两个数列 $a,b$ 对应元素相加得到的新数列为 $a+b$。操作一即为 $t\gets t+\bar{t}$，操作二即为 $a\gets a+t$。

考察一次操作一对 $t$ 的影响，此时 $t$ 变为 $[t_1+t_n,t_2+t_{n-1},\cdots,t_{n-1}+t_2,t_n+t_1]$，成为回文数列（即 $t=\bar{t}$）。此后再进行操作一是没有意义的，因为 $t+\bar{t}=t+t$，再进行一次操作一后进行操作二，等价于直接进行两次操作二。

至此，我们证明了操作一最多进行一次。

我们枚举在唯一一次操作一之前进行了几次操作二，可以得到此时的 $a$ 和 $t$，容易检查是否可能再进行若干次操作二，使得 $a=b$。

时间复杂度 $O(nw)$，其中 $w$ 为值域。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e3+5;

int T, n, t[N], b[N], a[N], s[N];

int main() {
    for(scanf("%d", &T); T; T--) {
        scanf("%d", &n);
        rep(i, 1, n) scanf("%d", &t[i]);
        rep(i, 1, n) scanf("%d", &b[i]);
        rep(i, 1, n) a[i] = 0;
        rep(i, 1, n) s[i] = t[i] + t[n-i+1];
        bool ans = false;
        while(true) {
            bool valid = true;
            rep(i, 1, n) if(a[i] > b[i]) valid = false;
            if(!valid) break;
            if((b[1] - a[1]) % s[1] == 0) {
                int steps = (b[1] - a[1]) / s[1];
                bool ok = true;
                rep(i, 1, n) if(b[i] != a[i] + steps * s[i]) ok = false;
                if(ok == true) {ans = true; break;}
            }
            rep(i, 1, n) a[i] += t[i];
        }
        puts(ans ? "Yes" : "No");
    }
    return 0;
}
```

---

## 作者：Jorisy (赞：4)

考虑到 $t$ 的一次相加会使得 $t'=\{t_i+t_{n-i+1}\}$，所以可以知道 $a_i=pt_i+qt_{n-i+1}(p,q\in\mathbb N)$。

于是我们知道能够产生 $b$ 当且仅当 $\exists p,q\in\mathbb N\ s.t.\ b_i=pt_i+qt_{n-i+1}$。

于是我们枚举 $p$，并看 $b_i$ 的整除性和 $q$ 是否相同即可。

注意 $p\ge q$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,t[2005],b[2005];

void sol()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i*t[1]<=b[1];i++)
	{
		int x=b[1]-i*t[1];
		if(x%t[n]) continue;
		for(int j=2;j<=n;j++)
		{
			int p=b[j]-i*t[j];
			if(p%t[n-j+1]||p/t[n-j+1]!=x/t[n]||i<x/t[n]) goto pp;
		}
		puts("Yes");
		return;
		pp:;
	}
	puts("No");
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol();
 	return 0;
}
```

---

## 作者：MoonCake2011 (赞：2)

此题我们发现最多做一次操作一。

因为做了一次操作一之后 $t$ 将会是对称的。

如果再做一次的话，那么 $t$ 数组将会被整体乘 2。

是没有意义的。

于是问题被转化为了。

$t$ 与 $t'$ 能否组成 $b$。

列出 $n$ 个条件等式。

$x \times t_i + y \times t'_i=b_i$。

现在问题被转化为了找到一组 $x,y$ 使这 $n$ 个等式成立。

我们可以暴力枚举判断。

时间复杂度 $O(nw^2)$。

其中 $w$ 为值域。

能得 80 分。

前四个点因为 $T$ 太大而 $TLE$。

我们可以枚举 $x$ 进而可以通过其中一组等式求出 $y$。

如果 $y$ 是小数或者负数，肯定不行。

时间复杂度 $O(nw)$。

可以通过。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int t1[signed(2e3)+10],t2[signed(2e3)+10];
int b[signed(2e3)+10];
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>t1[i];
	for(int i=1;i<=n;i++)
		t2[i]=t1[i]+t1[n-i+1];//计算t'
	for(int i=1;i<=n;i++) cin>>b[i];
	bool flag=0;
	for(int i=0;i<=2e3;i++){
		bool p=1;
		int j=0;
		if((b[n]-i*t1[n])%t2[n]!=0) continue;//判断y是否是小数
		else j=(b[n]-i*t1[n])/t2[n];
		if(j<0) continue;
		for(int k=1;k<=n;k++)
			if(i*t1[k]+j*t2[k]!=b[k]){//判断成不成立
				p=0;
				break;
			}
		if(p){
			flag=1;
			break;
		}
	}
	if(flag) cout<<"yEs\n";
	else cout<<"nO\n";
}
signed main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
} 
```

当然有 $O(n)$ 的解方程。

我这个蒟蒻没写出来。

此做法惊艳了我旁边的两位暴力哥。

---

## 作者：LCat90 (赞：2)

首先，考虑 $t$ 倒序修改后的序列性质。拿例子来说：$[1,4,2]\to [3,8,3]\to [6,14,6]\to [12,28,12]$，发现后面的操作都是把每个元素乘以 $2$。并且比较好证，因为 $a_{i}\gets a_{i}+a_{n-i+1},a_{n-i+1}\gets a_{i}+a_{n-i+1}$，所以 $a_i=a_{n-i+1}$；然后后面就是乘 $2$ 了。

并且我们可以加任意次，所以乘 $2$ 的序列是可以通过加法来维护的。

于是我们只保留两个操作序列 $t,a$，最终要使得两者带上一定系数相加后等于 $b$。即 $\forall i,x\times t_i+y\times a_i=b_i$。

枚举 $x$，然后求出 $y$，看是否满足非负整数条件并相等。时间复杂度为 $O(nX)$，其中 $X$ 为 $x$ 的最大值，约为 $2\times 10^3$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e3 + 5;
int T, n, t[N], b[N], cnt, a[N], c[N]; 
signed main() {
	cin >> T;
	while(T--) {
		cin >> n; cnt = 0;
		for(int i = 1;i <= n; ++i) cin >> t[i];
		for(int i = 1;i <= n; ++i) cin >> b[i];
		for(int i = 1;i <= n; ++i) a[i] = t[i] + t[n - i + 1];
		// xt + ba = b？
		bool f = 0;
		for(int i = 0;i <= 2000; ++i) {
			int sum = -1; f = 1;
			for(int j = 1;j <= n; ++j) {
				c[j] = b[j] - t[j] * i;
				if(c[j] % a[j] or c[j] < 0) {
					f = 0;
					break ;
				}
				if(sum != -1) {
					if(sum != c[j] / a[j]) {
						f = 0;
						break ;
					}
				}
				sum = c[j] / a[j];
			} 
			if(f) break ;
		}
		puts(f ? "Yes" : "No");
	} 
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：2)

本题作为第三题，个人认为质量还是相当不错的，很好的一道思维题。

将本题转化：

1.将 $t$ 与 $t$ 的倒序对应元素相加，得到新的 $t$；

2.将 $b$ 与 $t$ 对应元素相减，得到新的 $b$。

问有没有方法能让 $b$ 数列的全部元素都为 $0$。

对于操作一，我们可以注意到，进行操作一之后 $t$ 就会变为一个类似于回文数的回文串。

同样可以分析出，如果 $b$ 不为回文串，那么不断地将其减去一个回文串肯定是不能得到 $0$ 的。如果 $b$ 为回文串，不断地将其减去一个非回文串也是不能得到 $0$ 的。

综上所述，我们可以得出该题的做法：

当 $b$ 不为回文时，不断进行操作二，直到 $b$ 数列不满足都为 $0$ 的条件、任意的 $b_i<t_i$ 或者 $b$ 为回文串为止。

如果是因为 $b_i<t_i$ 而退出，输出 `No` 即可，否则继续操作：

将 $t$ 数列进行一次操作一，相当容易证明 $t$ 数列只进行一次操作一相比于多进行操作一不会将 `Yes` 变为 `No`，而多进行操作一相比于只进行一次操作一不会将 `No` 变为 `Yes`；

不断将 $b_i$ 减去 $t_i$，直到 $b$ 数列满足条件或者未满足条件并且有任意 $b_i<t_i$ 为止（此处可以使用除法进行优化，具体见代码）。

最后判断输出就可以了，代码：

```
#include<bits/stdc++.h>
using namespace std;
int t[100005];
int temp[100005];
int b[100005];
int n;
bool check(int a[]){
	for(int i=1;i<=n;i++){
		if(a[i]!=a[n-i+1]){
			return false;
		}
	}
	return true;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>t[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		int flag=0;
		while(!check(b)){
			for(int i=1;i<=n;i++){
				if(b[i]<t[i]){
					flag=1;
					break;
				}
				b[i]-=t[i];
			}
			if(flag){
				break;
			}
		}
		if(flag){
			cout<<"No\n";
			continue;
		}
		if(!check(t)){
			for(int i=1;i<=n;i++){
				temp[i]=t[i];
			}
			for(int i=1;i<=n;i++){
				t[i]=temp[i]+temp[n-i+1];
			}
		}
		bool pf=0;
		int ccnt=-1;
		for(int i=1;i<=n;i++){
			if(b[i]%t[i]!=0||pf&&b[i]/t[i]!=ccnt){//除法加快判断
				flag=1;
				break;
			}
			pf=1;
			ccnt=b[i]/t[i];
		}
		if(flag){
			cout<<"No\n";
			continue;
		}
		cout<<"Yes\n";
	}
	return 0;
}
/*
2
2
4 2
16 8
5
1 4 3 2 1
5 16 15 14 5
*/
```

顺便说一句，如果你 $90$ 分可以测一下代码下面挂着的数据，可能的一种原因是你先减去的是进行自增过后的 $t$ 数列然后再减去原来的 $t$ 数列。

根据题面上的测试点 $9\sim12$ 的特殊性质，相对来说可能容易推出来正解一些。

---

## 作者：MrPython (赞：1)

这篇题解使用了数学方法，$O\left(n\right)$ 解决本题。

## 思路
首先，容易发现**操作一最多进行一次，之后的操作一均可用若干操作二等价代替**。具体证明请参考 [官方题解](https://www.luogu.com.cn/blog/ak-ioi/mo-mo-guan-fang-ti-xie-qwq)，这里不再赘述。

在本题解中，下标从 $0$ 开始，且所有的 $i$ 都保证 $i$ 为整数且 $0\le i<n$。

让我们重点关注 $a$ 数组的变化过程中的 $2$ 次——对 $t$ 进行操作一前最后一刻的样子与结束后的样子。

对 $t$ 进行操作前最后一刻，$a$ 数组为若干个 $b$ 数组元素依次相加得到的，可记作：
$$
x\times t_0,x\times t_1,k\times t_2,\dots k\times t_{n-3},x\times t_{n-2},x\times t_{n-1}
$$
即 $a_i=x\times t_i$。其中 $x$ 表示在进行唯一的操作一之前进行了 $k$ 次操作二。

在对 $t$ 进行操作一后，记操作二后的数组为 $t'$：
$$
t_0+t_{n-1},t_1+t_{n-2},t_2+t_{n-3},\dots t_2+t_{n-3},t_2+t_{n-2},t_1+t_{n-1}
$$
即 $t'_i=t_i+t_{n-i-1}$。

记操作结束后的数组 $a$ 为 $a'$。$a'$ 为操作 $2$ 前的 $a$ 数组与若干个 $b'$ 元素依次相加得到，即
$$a'_i=a_i+y\times t'_i=x\times t_i+y\times\left(t_i+t_{n-i-1}\right)$$
其中 $y$ 表示进行操作一之后操作二的次数。

我们先假设答案为 `Yes`，即 $b$ 数组与 $a'$ 相同。由此，我们已知 $a'_i,a'_{n-i-1},t_i,t_{n-i-1}$，列出方程：
$$
\begin{cases}
	a'_i=x\times t_i+y\times\left(t_i+t_{n-i-1}\right)\\
	a'_{n-i-1}=x\times t_{n-i-1}+y\times\left(t_i+t_{n-i-1}\right)
\end{cases}
$$
可解得：
$$
\begin{cases}
    x=\dfrac{a'_i-a'_{n-i-1}}{t_i-t_{n-i-1}}\\
    y=\dfrac{a'_i-x\cdot k_i}{t_i+t_{n-i-1}}
\end{cases}
$$
尝试解这个方程。当出现无法整除或解是负数的情况时直接输出 `No`。  
但是还有一个问题：当 $t_i=t_{n-i-1}$ 时，分母为 $0$，该方程无意义。我们先打上标记，一会再说。

之后，我们从每个 $i$ 得到的有意义的解中任意选一个，在 $k$ 与 $b$ 数组中依次代回验证，不符合时说明没有一组符合的解适用于任意的 $i$，此时输出 `No`。

但是还有一个问题，当任意 $t_i=t_{n-i-1}$ 时（即 $t$ 是回文序列），无法找到一组有意义的解。不过此时我们可以证明操作一可以被若干操作二平替，因此将 $t$ 数组的每个元素依次相加若干次必然可以得到 $a'$。因此，我们说，对于任意 $i$ 都有 $a'_i$ 被 $t_i$ 整除且 $\dfrac{a'_i}{t_i}$ 都相等。以此为条件判断即可。

## 代码
以下是代码。不过这份写的非常混乱，要考虑的细节问题过多，还请各位见谅。我会以尽可能清晰的注释帮助大家理解每一部分。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
#define NO {cout<<"No\n";goto nexturn;}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n;
        cin>>n;
        vector<li> b(n),t(n);
        for (li& i:t) cin>>i;
        for (li& i:b) cin>>i;
        vector<pair<li,li>> pr(n>>1);pair<li,li> useful(-1,-1); // first存x，second存y
        if (n==1){cout<<(b[0]%t[0]?"No\n":"Yes\n");goto nexturn;} // n=1时特判
        for (size_t i=0,j=n-1;i<pr.size();++i,--j){ // j=n-i-1
            if (t[i]==t[j]) // t[i]=t[j]，分式无意义
                pr[i]={-1,-1}; // 特殊标记
            else{
                if ((b[i]-b[j])%(t[i]-t[j])) NO // 不能整除
                pr[i].first=(b[i]-b[j])/(t[i]-t[j]); // x
                if ((b[i]-pr[i].first*t[i])%(t[i]+t[j])) NO // 同理，求y时判断是否整除
                pr[i].second=(b[i]-pr[i].first*t[i])/(t[i]+t[j]); // y
                if (pr[i].first<0||pr[i].second<0) NO;  // 解<0，不合理
            }
        }
        for (pair<li,li> const& i:pr) if (i!=useful){  // 寻找一组有意义的解
            useful=i;break;
        }
        if (useful==pair<li,li>(-1,-1)){  // 没找到
            li times=b[0]/t[0]; 
            for (size_t i=0;i<n;++i) if (b[i]%t[i]||b[i]/t[i]!=times) NO // 判断是否整除、商均相等
        }else for (size_t i=0,j=n-1;i<(n+1>>1);++i,--j)
            if (b[i]!=useful.first*t[i]+useful.second*(t[i]+t[j])
                ||b[j]!=useful.first*t[j]+useful.second*(t[i]+t[j])) NO // 代回验证
        cout<<"Yes\n";
        nexturn:;
    }
    return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先发现对于操作 1 显然进行一次就可以将 $t$ 变为一个回文序列。

那么，不难发现如果进行两次操作 1，在进行一次操作 2，是与进行一次操作 1，在进行两次操作 2 等效的。

所以考虑处理出 $tt$ 表示 $t$ 进行操作 1 后的序列。

不妨枚举一个 $x,y$ 分别表示使用 $t$ 和 $tt$ 的使用数量。

然后可以 $\Theta(n)$ 求出 $a$，判断是否与 $b$ 相等即可。

**注意：我们可以在枚举 $x,y$ 时，加上 $x \times t_1 \leq b_1$ 与 $x \times t_1 + y \times t_1 \leq b_1$ 的条件，如果它们大于 $b_1$ 一定凑不出来，同时能保障时间复杂度是 $\Theta(nw)$ 的，其中 $w$ 表示值域。**

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2010;
int T,n;
int b[N],t[N],tt[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		bool falg = false;
		n = read();
		for (re int i = 1;i <= n;i++) b[i] = t[i] = tt[i] = 0;
		for (re int i = 1;i <= n;i++) t[i] = read();
		for (re int i = 1;i <= n;i++) b[i] = read();
		for (re int i = 1;i <= n;i++) tt[i] = t[i] + t[n - i + 1];
		for (re int x = 0;x * t[1] <= b[1];x++){
			for (re int y = 0;x * t[1] + y * tt[1] <= b[1];y++){
				bool ok = true;
				for (re int i = 1;i <= n;i++){
					if (b[i] != x * t[i] + y * tt[i]){
						ok = false;
						break;
					}
				}
				if (ok){
					falg = true;
					break;
				}
			}
		}
		if (falg) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：1)

## [P9714 「QFOI R1」摸摸](https://www.luogu.com.cn/problem/P9714)

### 题意

数组 $a$ 初始为 $0$，给出数组 $t,b$，有两种操作：

* 把每个 $t_i$ 加上 $t_{n-i+1}$。

* 把每个 $a_i$ 加上 $t_i$。

问能否将 $a$ 变为 $b$。

------

### 解法

设一开始的 $t$ 数组为 $t'$，我们发现，经过 $k$ 次操作一后 $t_i=(t'_i+t'_{n-i+1})\times 2^{k-1}$，一定是 $t'_i+t'_{n-i+1}$ 的倍数。

于是我们如果进行了第一次操作一，那么 $b_i-a_i$ 一定是 $t'_i+t'_{n-i+1}$ 的倍数，否则不可能使 $a_i=b_i$。

那么我们需要先进行若干次操作二，使得每个 $b_i-a_i$ 都是 $t'_i+t'_{n-i+1}$ 的倍数，暴力减即可，如果减到负数那么肯定无解。

又因为 $t_i=(t'_i+t'_{n-i+1})\times 2^{k-1}$，我们只需要进行一次操作一，然后一直加给 $a$，并且能保证正确。因为 $(t'_i+t'_{n-i+1})\times 2^{(k+1)-1}$ 一定是 $(t'_i+t'_{n-i+1})\times 2^{k-1}$ 的倍数。

于是我们判断每个 $\dfrac{b_i-a_i}{t'_i+t'_{n-i+1}}$ 是否都相等即可。

------

### 代码

代码中直接减 $b$ 数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int T,n,t[N],b[N];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&t[i]);
    for(int i=1;i<=n;++i) scanf("%d",&b[i]);
    bool f=0;
    while(!f){
        for(int i=1;i<=n;++i) if(b[i]%(t[i]+t[n-i+1])!=0) f=1;
        //是否还有不能整除的
        if(f){
            for(int i=1;i<=n;++i){
                b[i]-=t[i];
                if(b[i]<0){
                    printf("NO\n");
                    return;
                }
            }
            f=0;
            //减一遍t
        }
        else break;
    }
    int tmp=b[1]/(t[1]+t[n]);
    for(int i=2;i<=n;++i){
        if(b[i]/(t[i]+t[n-i+1])!=tmp){
            printf("NO\n");
            return;
        }
    }
    //是否(b[i]-a[i])/(t[i]+t[n-i+1])都相等
    printf("YES\n");
    return;
}
int main(){
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：irris (赞：1)

## Preface

尺子好闪。

## Solution

考虑到，在经过一次操作后，$t'_i \gets t_i + t_{n+1-i}$，$t'_{n+1-i} \gets t_{n+1-i} + t_i$，也即 **$\bm t'$ 是一个回文序列**。更具体地，一旦我们继续去考察这样一件事情，也就是说对 $t$ 进行两次操作会发生什么，也就是说对回文序列 $t'$ 进行操作会发生什么，你会得到 $t''_i \gets 2t'_i$（由回文易得）！

那么考虑如果我们向 $b$ 上累加了 $t''$ 或者甚至是 $t''', t'''', t'''''$，它们都可以分别改写成累加 $2, 4, 8, 16$ 次 $t'$ 来达成同样的目的，也就是说事实上只有 $t$ 和 $t'$ 是有用的。

此外，由于我们知道因为 $t'$ 是一个回文序列，那么累加 $t'$ 若干次后得到的 $b$ 也一定回文。也就是说，如果 $b$ 不回文，那么它不回文带来的影响一定是由累加 $t$ 得到的。我们尝试每次向 $\forall b_i \gets b_i - t_i$，并判断新的 $b$ 是否回文。直到 $\exists b_i \lt 0$ 时我们退出，因为已经不符合条件了。

否则，我们判断 $b$ 是否由 $t'$ 累加而成的，也就是说是否 $\frac{b_i}{t'_i}$ 相同且全为整数，这样就做完......了吗？考虑若 $t$ 本身回文且 $b_i = t_i$，答案是 `Yes` 但我们会输出 `No`，并且我们发现这种情况当且仅当 $t$ 本身回文而我们用了 $t'$ 累加去判断，所以特例是只有这一个的。判掉即可。

## Code

不放，因为我写的 $\mathcal O(\sum n\times V)$。容易做到 $\mathcal O(\sum n)$。

---

## 作者：C202301 (赞：1)

### 题意简述
将一个初始时所有元素均为 $0$ 且长度为 $n$ 的序列 $a$ 经过两种操作变成长度为 $n$ 的序列 $b$。还有一个数列 $t$。有以下两种操作：
1. 将 $t$ 与 $t$ 的倒序相加，得到新的 $t$。
1. 将 $a$ 与 $t$ 的倒序相加，得到新的 $a$。

问可否经过若干次操作后把数列 $a$ 变成数列 $b$。
### 解题思路
首先可以发现，不管任何序列，进过操作 $1$ 后都会变成一个回文序列（即第序列 $i$ 个元素跟第 $n-i+1$ 个元素相等）。而任何回文序列，经过操作 $1$ 后每个元素会变成原来的两倍。如果是变成原来序列的两倍，其实不用操作 $1$ 也可以，只需要用两次加和即可（例如序列 $t=[2,4,2]$，序列 $a=[0,0,0]$，序列 $b=[4,8,4]$，可使用操作 $1$ 后使用操作 $2$，或者使用两次操作 $2$ 也可将序列 $a$ 变成序列 $b$）。这样可以证明，其实操作 $1$ 只需要使用 $1$ 次变为回文数列后，若继续使用操作 $1$ 可以变成序列 $b$，那么不继续操作也可以。所以本题其实为将原始 $t$ 序列（后文称原始 $t$ 序列）和经过 $1$ 次操作后的 $t$ 序列（后文称回文 $t$ 序列）分别使用不同的次数相加（最终总会加到 $a$ 序列上），最后若可变为 $b$ 序列说明可以，否则不行。
### 代码实现
可以发现，本题数据范围很小，所以可以枚举。可以对序列中的任意一项当做基准，初始完全不使用回文 $t$ 序列，然后使用次数递增，若这个位置相应次数相加和为 $b$ 数列同位置项，那么将这个当做基准次数，来计算后面每一个元素。如果全部满足，输出 ```Yes``` 。当这一项已经超过 $b$ 数列同位置项，说明没有任何可能，输出 ```No```。

下面贴代码：
```
#include<iostream>
using namespace std;
int main()
{
	int T;
	cin>>T;//T组数据 
	for(int l=1;l<=T;l++)
	{
		int n;
		cin>>n;
		int t[n+1],b[n+1],c[n+1],pep=0,ans=0;//数据范围很小，所以就直接在循环内定义了，pep为回文 t序列的使用数量，ans为初始 t序列的使用数量
		bool ru=1,yes;//ru变量判断是否全部满足，yes变量表示是否要输出Yes 
		for(int i=1;i<=n;i++)
		cin>>t[i];//初始 t序列 
		for(int i=1;i<=n;i++)
		cin>>b[i];
		for(int i=1;i<=n;i++)
		c[i]=t[i]+t[n-i+1];//回文 t序列 
		while(true)
		{
			//基准数为每个序列第一项 
			ru=1;
			if(b[1]-pep*c[1]<0)//如果回文 t序列的使用数量乘基准数已经大于b序列同位置数 
			{ 
				yes=0;//输出No 
				break;//跳出循环 
			}
			ans=(b[1]-pep*c[1])/t[1];//ans=原始t序列的使用数量 
			if((b[1]-pep*c[1])%t[1]!=0)//如果无法整除（即无法凑出b数列这一项的数） 
			{
				pep++;//回文 t序列的使用数量加一 
				continue;
			}
			for(int i=1;i<=n;i++)
			if(pep*c[i]+ans*t[i]!=b[i])//如果按照使用数量无法得到这个位置上的数 
			{
				ru=0;//不满足 
				break;
			}
			if(ru==1)
			{
				yes=1;//满足，可行 
				break;
			}
			else
			pep++;//无法满足，回文 t序列的使用数量加一  
		}
		if(yes==1)
		cout<<"Yes"<<endl;
		else
		cout<<"No"<<endl;
	}
	return 0;
}
```


---

## 作者：SakurajiamaMai (赞：0)

## 思路:
本题考察思维，可以发现，目标序列和初始序列一定存在某种关系使得初始序列可以转化为目标序列，由于对目标序列进行操作一之后，发现进行一次操作之后，无论再进行多少次操作都是第一次操作后的序列的倍数关系，那么我们有了以下结论。

对于一个目标序列，我们把他分成两步，第一步是需要多少次初始序列，第二步是需要多少次进行操作一之后的序列。例如初始序列为 $1$，$2$，$2$，目标序列为 $5$，$8$，$7$。而进行操作之后变成 $3$，$4$，$3$。所以我们需要一次操作一之后的序列，两次未操作的序列，枚举我们需要操作一多少次即可。

```cpp
#include <iostream>

#define int long long

using namespace std;

const int N = 5e3 + 10;

int n, m, t;
int a[N], b[N], c[N];

void solve_pro() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    
    int cnt = 0;
    bool Vis = true, Flag = true;
    
    while (Vis) { //枚举需要多少次操作一
        Flag = true;
        
        for (int i = 1; i <= n; i++) {
            int x = a[i] + a[n - i + 1];
            
            if (cnt * x > b[i]) { // 超过范围，退出
                Vis = false;
                break;
            }
            
            if (!Flag) break;
            
            int k = b[i] - cnt * x;
            int ans = (b[1] - cnt * (a[1] + a[n])) / a[1];
            
            if (k % a[i] == 0 && k / a[i] == ans) 
                continue;
            else 
                Flag = false;
        }
        
        cnt++;
        
        if (!Vis) break; // 退出标记
        
        if (Flag) {
            cout << "Yes" << endl;
            return;
        }
    }
    
    cout << "No" << endl;
}

signed main() {
    
    std::ios::sync_with_stdio(false);
    
    cin.tie(0),cout.tie(0);

    cin >> t;
    
    while (t--) {
        solve_pro();
    }
    
    return 0;
}
```



---

## 作者：lovely_AKCode (赞：0)

# 题解
在推断是，会有一个性质：$b_i = x \times (t_i + t_{n-i+1}) + t_i \times y$。在这条公式中， $x$ 和 $y$ 是未知数，因此我们要推出 $x$ 的定制范围，如下：

```cpp
now=b[n]/(t[1]+t[n])
```

我们以 $1$ 和 $n$ 为例子，省略 $t_i \times y$ ,此时的 $x$ 一定为最大值。算出 $x$ 后，枚举 $x$ 到 $0$ ,将 $x$ 带入公式，算出 $y$ ，在验算是否正确即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int N=1e3+5;
int s[N],a[N],t[N],b[N],n,ans,T;
bool check(){
	int now=b[n]/(t[1]+t[n]),old,ans;
	for(int x=now;x>=0;x--){
		int flag=1;
		for(int i=1;i<=n;i++){
			old=b[i]-(t[i]+t[n-i+1])*x;
			if(old%t[i]!=0){
				flag=0;
				break;
			}else{
				if(old/t[i]!=ans&&i!=1){
					flag=0;
					break;
				}else{
					ans=old/t[i];
				}
			}
		}
		if(flag) return true;
	}
	return false;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",t+i);
		for(int i=1;i<=n;i++) scanf("%lld",b+i);
		if(check()) printf("Yes\n");
		else printf("No\n");
	}
}

```

---

## 作者：Loser_Syx (赞：0)

考虑 $t_i = t_{n-i+1}$ 且 $b_i = b_{n-i+1}$ 的解法。

发现其成立的可能性当且仅当 $b_i \bmod t_i \neq 0$ 且所有 $b_i \div t_i$ 均相等。

考虑转化至上述情况。

发现对 $t$ 进行操作一次后 $t$ 满足 $t_i = t_{n-i+1}$。

而 $b$ 可以一直减 $t$。

转化到了上面的情况之后就可以直接做了。

```cpp
#include <iostream>
using namespace std;
#define yes puts("Yes")
#define no puts("No")
int a[101010], b[101001], c[101010];
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= n; ++i) cin >> b[i];
		auto hf = [&]() -> bool {
			for (int i = 1; i <= n; ++i) if (b[i] < 0) return 0;
			return 1;
		};
		auto check = [&]() -> bool {
			for (int i = 1; i <= n; ++i) if (b[i] != b[n - i + 1]) return 0;
			return 1;
		};
		while (!check() && hf()) {
			for (int i = 1; i <= n; ++i) b[i] -= a[i];
		}
		if (!hf()) no;
		else {
			bool flg = 0;
			for (int i = 1; i <= n; ++i) {
				if (b[i] % a[i] || b[i] / a[i] != b[1] / a[1]) {
					flg = 1;
					break;
				}
			}
			if (!flg) {
				yes;
			} else {
				flg = 0;
				for (int i = 1; i <= n; ++i) {
					if (b[i] % (a[i] + a[n - i + 1]) != 0 || b[i] / (a[i] + a[n - i + 1]) != b[1] / (a[1] + a[n])) {
						flg = 1;
						no;
						break;
					}
				}
				if (flg == 0) yes;
			}
		}
	}
	return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

首先我们设原数组为 $t$，操作一之后的数组为 $t_2$。发现无论怎么加，怎么变化，$b$ 数组总可以表示为几个 $t$ 数组和几个 $t_2$ 数组的和（这个结论可以这么想：$t_2$ 一定是回文的，反转加后只是相当于翻了个倍），遂枚举个数，即可通过。枚举个数的时候下界要取 $0$，上界可以通过试，太小了会 WA，太大了会 TLE，最后我测得取 $700$ 时可以通过。这就是 IOI 赛制的好处。

```
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        int t[10005],b[10005],t2[10005],tt[10005];
        for(int i=1;i<=n;i++){
            cin >> t[i];
            t2[n-i+1]=t[i];
        }

        for (int i=1;i<=n;i++){
            cin>>b[i];
            tt[i]=t[i]+t2[i];
        }
        // for (int i=1;i<=n;i++){
        //     cout<<tt[i]<<" ";
        // }cout<<endl;
        int fg=0;
        for(int i=0;i<=700;i++)
        {
          for(int j=0;j<=700;j++)
          {
            int fgg=1;
            for(int ii=1;ii<=n;ii++)
            {
              if(tt[ii]*i+t[ii]*j!=b[ii])fgg=0;
            }
            if(fgg==1){fg=1;goto mk;}
          }
          
        }
        mk:
        if(fg)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
       
          
        
    }

    return 0;
}
```


---

## 作者：Null_h (赞：0)

## 前言

裴楚定理似乎不是普及内容。

## 思路

不难发现，如果一个数列可以满足条件，那么一定存在一种至多进行一次操作一的方案。由于操作一是倒序相加，所以在进行过一次操作一后，该数列一定是回文的，那么后续的操作一就相当于使它翻倍。这样，可被表出的本质不同的数列只有两个。

知道了这个性质，我们就可以转化问题了。相当于给定了两个数列，询问是否存在一种方案，使这两个数列相加任意次后可以得到目标序列。因为是每位相加，所以只要找到两个数 $x$ 和 $y$，使得 $a_ix+b_iy=c_i$，那么就是可行的。

于是我们发现，这就是裴楚定理啊！对于每一个 $i$，先判断是否有解，再记录所有可行解。最后判断是否有公共解就可以了。

至此，该算法已经可以通过本题。

## 优化

不难发现，时间消耗最大的地方在记录这里，于是开始剪枝。

首先，只有之前已经有 $i-1$ 个方案的解是可行的，仅记录目前可行解。

如果一次操作没有更新，直接跳出。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int h[3000],l[3000],k[3000];
map<pair<int,int>,int> f;
signed main(){
	ios::sync_with_stdio(false);
	int a;
	cin>>a;
hbr:while(a--){
		int b;
		cin>>b;
		f.clear();
		for(int i=0;i<b;i++){
			int x;
			cin>>x;
			h[i]=x;	
		}
		for(int i=0;i<b;i++){//反转后数列
			k[i]=h[i]+h[b-i-1];
		}
		for(int i=0;i<b;i++){
			int x;
			cin>>x;
			l[i]=x;
		}
		for(int i=0;i<b;i++){
			int z=__gcd(h[i],k[i]);
			if(l[i]%z!=0){//方程无解
				cout<<"no\n";
				goto hbr;
			}
			int x=l[i]/h[i],y=0;
			while(x>=0){
				int p=x*h[i]+y*k[i];
				if(p>l[i]){
					x--;
				}else if(p<l[i]){
					y++;
				}else{//找到一组解
					int fl=0;
					while(x>=0){
						if(f[make_pair(x,y)]==i){//可能成为一个解
							fl=1;
							if(i==b-1){
								cout<<"yes\n";
								goto hbr;
							}
							f[make_pair(x,y)]++;
						}
						x-=k[i]/z;
						y+=h[i]/z;	
					}
					if(!fl){//没有更新
						cout<<"no\n";
						goto hbr;
					}
					break;
				}
			}
		}
		cout<<"no\n";
	}
	return 0;
}
```

---

## 作者：66xyyd (赞：0)

## 题意

（提炼后的结果，自行理解题意的转换或看注释）

给定 $t_1,t_2,\cdots,t_n$，已知 $t'_i=t_i+t_{n-i+1}$，求能否找到 $x,y$ 使得 $t_ix+t'_iy=b_i$ 恒成立。

$T$ 的存在只是多测，不影响题意。

## 题解

考虑枚举 $x$。取 $y=\frac{b_i-t_ix}{t'_i}$，如果 $y$ 不是整数直接舍去；否则验证每一个 $i$ 得到的 $y$ 是否都相等。如果全部相等则输出 `Yes`。

$x$ 枚举的范围是多少呢？$t_ix=b_i-t'_iy \le b_i$，所以 $x$ 枚举到 $t_ix>b_i$ 了跳出循环，如果还没有输出 `Yes` 就直接输出 `No`。

代码（这份代码中的 $a,b,t$ 下标从 $0$ 开始）：

```cpp
#include<iostream>
using namespace std;
int a[100001],t[100001],b[100001];
int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for(int i=0;i<n;i++){
			cin >> t[i];
		}
		for(int i=0;i<n;i++){
			cin >> b[i];
		}
		bool flag=true;
		for(int x=0;t[0]*x<=b[0];x++){
			bool f=true;
			int y=(b[0]-t[0]*x)/(t[0]+t[n-1]);
			if(y*(t[0]+t[n-1])!=(b[0]-t[0]*x))	continue;
			
			for(int i=1;i<n;i++){
				int tmp=(b[i]-t[i]*x)/(t[i]+t[n-i-1]);
				if(tmp*(t[i]+t[n-i-1])!=b[i]-t[i]*x|| tmp!=y){
					f=false;
					break;
				}
			}
			if(f){
				flag=false;
				cout << "yes\n";
				break;
			}
		}
		if(flag){
			cout << "no\n";
		}
	}
	return 0;
}
```

## 注释

1. 题意如何转换？

考虑执行操作 $1$ 前执行 $x$ 次操作 $2$，执行操作 $1$ 后执行 $y$ 次操作 $2$ 得到 $b$。执行操作 $1$ 后序列 $t$ 就变成了 $t'$，这样 $t_ix+t'_iy=b_i$。由于 $t'$ 一定是回文的，所以操作 $1$ 最多执行 $1$ 次，这保证了我们思考的正确性。


---

