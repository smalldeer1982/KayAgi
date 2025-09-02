# [ARC124B] XOR Matching 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc124/tasks/arc124_b

非負整数のみからなる長さ $ N $ の数列 $ a,b $ が与えられます。$ a,b $ の $ i $ 番目の要素はそれぞれ $ a_i,\ b_i $ です。

非負整数 $ x $ が以下の条件を満たすとき、$ x $ を **よい数** と呼びます。

- 条件：$ b $ を並べ替えて、$ 1\ \leq\ i\ \leq\ N $ を満たすどの整数 $ i $ についても $ a_i\ \text{\ XOR\ }\ b_i\ =\ x $ が成立するようにすることができる。ここで、$ \text{XOR\ } $ はビットごとの排他的論理和である。

よい数を小さい方からすべて列挙してください。

 $ \text{\ XOR\ } $ とは 整数 $ x,\ y $ のビットごとの排他的論理和 $ x\ \text{\ XOR\ }\ y $ は、以下のように定義されます。

- $ x\ \text{\ XOR\ }\ y $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ x,\ y $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \text{\ XOR\ }\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \text{\ XOR\ }\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ a_i,\ b_i\ <\ 2^{30} $

### Sample Explanation 1

\- $ b $ を $ (4,\ 7,\ 6) $ と並び替えたとき、$ a_1\ \text{\ XOR\ }\ b_1\ =\ a_2\ \text{\ XOR\ }\ b_2\ =\ a_3\ \text{\ XOR\ }\ b_3\ =\ 5 $ となるため、$ 5 $ はよい数です。他によい数はありません。

## 样例 #1

### 输入

```
3
1 2 3
6 4 7```

### 输出

```
1
5```

## 样例 #2

### 输入

```
2
0 1
0 2```

### 输出

```
0```

## 样例 #3

### 输入

```
24
14911005 70152939 282809711 965900047 168465665 337027481 520073861 20800623 934711525 944543101 522277111 580736275 468493313 912814743 99651737 439502451 365446123 198473587 285587229 253330309 591640417 761745547 247947767 750367481
805343020 412569406 424258892 329301584 123050452 1042573510 1073384116 495212986 158432830 145726540 623594202 836660574 380872916 722447664 230460104 718360386 620079272 109804454 60321058 38178640 475708360 207775930 393038502 310271010```

### 输出

```
8
107543995
129376201
139205201
160626723
312334911
323172429
481902037
493346727```

# 题解

## 作者：hellolin (赞：3)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_arc124_b)

[题面(AtCoder)](https://atcoder.jp/contests/arc124/tasks/arc124_b)

AtCoder Problems 评级难度：$\texttt{\color{#ffb972}{788}}$。

## 题意

- 给你长度为 $N$ 的序列 $a$ 和 $b$。
- 求有多少个非负整数 $x$ 满足：有一种修改序列 $b$ 的方法使得 $\forall i (1\le i\le N),  a_i \oplus b_i = x$。
- 按升序输出所有满足条件的 $x$。
- $1\le N\le 2000, 0\le a_i,b_i<2^{30}$。

## 思路

不难证明，当 $a\oplus b=c$ 时，$a\oplus c=b$ 成立。

所以说，问题可以从求 $a_i \oplus b_i=x$ 转化为求 $a_i \oplus x=p_i$（若 $p=b$，则 $x$ 符合条件）。

枚举 $x$，让 $p_i = a_1 \oplus x$，再对两个序列进行比较，时间复杂度 $O(N^2 \log N)$。

注意答案可能有重复的，可以把答案扔到 set 里，既能去重还能自动排序。

``` cpp
#include <bits/stdc++.h>
#define each(x,y) for(auto &x:y)
using namespace std;

const int N = 2020;
int n, tmp;
vector<int> a, b, p;
set<int>ans;

bool judge(int x)
{
    p=a;
    each(i,p)
        i^=x;
    
    sort(p.begin(), p.end());
    return b==p;
}

void solve()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>tmp;
        a.push_back(tmp);
    }
    for(int i=1; i<=n; i++)
    {
        cin>>tmp;
        b.push_back(tmp);
    }
    sort(b.begin(), b.end());
    each(i,b)
    {
        tmp=a[0]^i;
        if(judge(tmp)) ans.insert(tmp);
    }
    cout<<ans.size()<<endl;
    each(i,ans)
        cout<<i<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
```



---

## 作者：XYstarabyss (赞：2)

# 思路

我们先拿 $a_1$ 来与 $b_{1 \sim n}$ 进行异或操作，获得一组数据 $x$，好数一定会全部包含于这一组数据中，这是因为好数一定会等于 $a_1 \oplus b_{\pi_{i}}$，假设有好数不包含于 $x$ 中，那么 $a$ 异或任意一个 $b_i$ 都无法得到该好数，假设不成立，故得证。

之后，我们再验证数据 $x$ 中的各项是否为好数，把 $x_i \oplus a_{1 \sim n}$ 放进 $map$ 里，然后看其是否能与 $b_{1 \sim n}$ 一一配对，若能的话用 $ans$ 记录一下就行了。

注意输出答案时一定要记得去重。

# code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define dbug(x) cerr<<(#x)<<':'<<x<<' ';
#define ent cerr<<'\n';
#define f(n,m,i) for (int i = n;i <= m;i ++)
#define fc(n,m,i) for (int i = n;i >= m;i --)
#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)<(b))?(a):(b)
void C(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0),cerr.tie(0);
}
long long n;
long long a[2005],b[2005];
long long cnt(0),ans[2005];
unordered_map <long long,long long> map0;
int main(){
    C();
    cin >> n;
    f(1,n,i){
        cin >> a[i];
    }
    f(1,n,i){
        cin >> b[i];
    }
    f(1,n,i){
        bool yn(true);
        long long x(a[1] ^ b[i]);
        f(1,n,j){
            map0[x ^ a[j]] ++;
        }
        f(1,n,j){
            if(!map0[b[j]]){
                yn = false;
                break;
            }
            map0[b[j]] --;
        }
        if (yn){
            ans[++ cnt] = x;
        }
        map0.clear();
    }
    sort(ans + 1,ans + cnt + 1);
    cnt = unique(ans + 1,ans + cnt + 1) - ans - 1;//记得去重！！！（惨痛教训）
    cout << cnt << '\n';
    f(1,cnt,i){
        cout << ans[i] << '\n';
    }
    return 0;
}
/*
g++ arc124b.cpp -o code
./code

3

1 2 3

6 4 7

*/
```

---

## 作者：cjh_trailblazer (赞：1)

## 前言（一些废话）：
刷异或性质题时，发现这道题还能交题解，那么直接水一发。
## 题目分析：
发现 $n\le 2000$，可以 $O(n^2)$ 的做。

考虑如何处理 $x$，发现对于一个合法的 $x$，最多只有 $n$ 个。  
因为 $a_i\oplus b_i=x$，则 $a_i\oplus x=b_i$，考虑固定一个 $x$，因为如果 $x$ 是合法的，则 $a_i$ 和 $b_i$ 中任意一组异或起来值都是 $x$。

那么我们固定一个 $a_i\oplus b_1$ 即可求出所有可能的合法 $x$，（这里 $a_i\oplus b_1$ 和 $a_1\oplus b_i$ 效果是一样的，至于为什么选择 $b_1$，后面会讲），接下来求出一个新的排列 $p_i=a_i\oplus x$，判断排列 $p$ 是否等于 $b$ 即可，当然，记得对 $x$ 去重。  
至于升序排序，由于我们要对 $x$ 去重，则开个 set 就行，一举两得。

注意：判断 $p$ 和 $b$ 是否相等时，如果你用 sort 再 $O(n)$ 比较的话，记得在枚举 $x$ 前就定义一个变量记录 $b_1$，不然 sort 后 $b_1$ 的值会有所变化。

解答前面选择 $a_i\oplus b_1$ 的问题，我们如果选择 $a_1\oplus b_i$ 枚举 $x$，就不能用 sort 判断，会造成 $x$ 枚举不充分的情况。  
当然，如果你用别的方法判断，那就无所谓了。
## Code:
```cpp
#include<bits/stdc++.h>
#define starrail main
#define re register
#define il inline
using namespace std;
typedef long long ll;
il int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=(s<<1)+(s<<3)+(ch^48);ch=getchar();}
	return w*s;
}
const int N=2010;
int a[N],b[N],p[N],n;
set<int>q;
signed starrail(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	int tot=b[1];
	for(int i=1;i<=n;i++){
		int x=a[i]^tot;
		bool f=1;
		for(int j=1;j<=n;j++)
			p[j]=a[j]^x;
		sort(p+1,p+1+n);
		sort(b+1,b+1+n);
		for(int j=1;j<=n;j++)
			if(p[j]!=b[j])
				f=0; 
		if(f==1) q.insert(x);
	}
	printf("%d\n",q.size());
	for(auto ans:q)
		printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_O_w_O_ (赞：0)

我们发现最多有 $n^2$ 个 $x$。

我们又发现一个 $x$ 是好的当且仅当至少有 $n$ 个 $(i,j)$ 满足 $a_i\oplus b_j=x$，我们发现，这一步过后，最多只有 $n$ 个可能的 $x$。

那么我们就暴力枚举每一对 $(i,j)$，用 `std::map` 来记录出现次数，保留出现次数 $\ge n$ 的 $x$。

我们考虑如何检查一个 $x$ 是否满足要求。

我们注意到 $a_i\oplus b_j=x$ 可以转化为 $a_i\oplus x=b_j$，那么我们就可以将每个 $a_i\leftarrow a_i\oplus x$，排序后检查 $a$ 是否与 $b$ 相同即可。

---

## 作者：Laoshan_PLUS (赞：0)

模拟赛上是有 $n\le10$ 的部分分的，直接暴力枚举 $b$ 的全排列即可，可以得到 10pts。

我们考虑优化。以前我们是通过枚举 $b$ 的全排列，和 $a$ 异或后判断是否相等，而 $b$ 的全排列是有 $n!$ 种的，浪费了时间。我们优化就只有改变枚举方式，我们发现 **$\boldsymbol x$ 的取值只可能有 $\boldsymbol n$ 种，分别用 $\boldsymbol{a_1\oplus b_{1\dots n}}$ 就可以枚举出 $\boldsymbol x$，然后用 $\boldsymbol{a_{2\dots n}\oplus x}$ 得到一个序列记为 $\boldsymbol t$，将 $\boldsymbol b$ 和 $\boldsymbol t$ 比较就可以验证答案**。具体地，将 $a,b$ 序列都排序，将得到的 $t$ 序列也排序，然后验证，这样就不会有漏掉的情况了。总时间复杂度 $O(n^2\log n)$，因为还要排序。

### 坑点

**一定一定要去重**！给 $a,b$ 去重是为了节省时间，同时若 $a,b$ 去重后的序列长度不一致可以直接输出 `0`；给答案去重更是必要的。可以把答案扔到一个 set 里，既能自动去重还能自动排序。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2005;
int n, a[MAXN], b[MAXN], x;
set<int> ans;
int tn, Tm, t[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	sort(a + 1, a + n + 1);
	tn = unique(a + 1, a + n + 1) - (a + 1);
	sort(b + 1, b + n + 1);
	Tm = unique(b + 1, b + n + 1) - (b + 1);
	if (tn != Tm) return puts("0"), 0;
	for (int i = 1; i <= tn; i++) {
		int tt = a[i] ^ b[i];
		for (int j = 1; j <= tn; j++) t[j] = a[j] ^ tt;
		sort(t + 1, t + tn + 1);
		for (int j = 1; j <= tn; j++) if (b[j] != t[j]) goto ru;
		ans.insert(tt);
		ru:;
	}
	cout << ans.size() << '\n';
	for (auto v : ans) cout << v << '\n';

	return 0;
}
```

---

## 作者：TG_Space_Station (赞：0)

# 前置知识
异或拥有自反性，什么是自反性呢，即自己是自己的逆运算。  
即：$a \oplus b \oplus b = a$，是不是和 $a + b - b = a$ 很像？
# 本题讲解
暴力即可，不需优化。  
不难发现，答案只有可能是 $b$ 中取一个，$a$ 中取一个，再异或起来。  
定义 $B$ 为 $b$ 的重排。  
题目要求了对于每个合法答案必须满足 $B_i \oplus a_i = x$。  
则：答案只有可能是 $b$ 中取一个，再取 $a_1$，再异或起来。  
根据则自反性易得：$B_i = x \oplus a_i$。  
那你就可以对于每种可能的 $x$ 所得出的 $B$ 进行判断，判断它是否为 $b$ 的重排，具体方法：排序。  
时间复杂度：$O(n^2 \log n)$，可以通过本题。  
# 避坑
**答案记得去重。  
答案记得去重。  
答案记得去重。**  
我因为这个问题搞了40min。
# [AC Code](https://atcoder.jp/contests/arc124/submissions/44794780)

```
#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
int n;
int i, j;
int a[N], b[N];
int cur, tmp[N];
vector <int> ans;

int main()
{
	//freopen("xor.in", "r", stdin);
	//freopen("xor.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	
	for(i = 1; i <= n; i++)
		cin >> a[i];
	for(i = 1; i <= n; i++)
		cin >> b[i];

	sort(b + 1, b + n + 1);
	
	for(i = 1; i <= n; i++)
	{
		cur = a[1] ^ b[i];
		
		for(j = 1; j <= n; j++)
			tmp[j] = cur ^ a[j];

		sort(tmp + 1, tmp + n + 1);
		
		for(j = 1; j <= n; j++)
			if(tmp[j] != b[j])
				break;
		
		if(j == n + 1)
			ans.push_back(cur);
	}

	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	cout << ans.size() << "\n";
	
	for(i = 0; i < ans.size(); i++)
		cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先不难发现答案最多只有 $ n $ 个取值，分别是 $ a_1 $ 异或每个 $ b_i $ 得到的结果。

于是考虑枚举答案的取值 $ x $，则 $ b_i $ 必须满足重新排列 $ b $ 后，对于每个 $ i $，都有 $ b_i=x \oplus a_i $。这个可以开一个 unordered_map 比对每个值的出现次数实现，所以这步是 $ \mathcal{O}(n) $ 的。

于是总时间复杂度显然为 $ \mathcal{O}(n^2) $，可以通过。注意答案要去重。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=1e4+10;
int a[maxn],b[maxn];
vector<int>ans;
int main() 
{
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	cin>>a[i];
	for (int i=1;i<=n;i++)
	cin>>b[i];
	for (int i=1;i<=n;i++) 
	{
		int x=a[1]^b[i];
		unordered_map<int,int>p;
		for (int i=1;i<=n;i++)
		p[b[i]]++;
		bool ok=1;
		for (int i=1;i<=n;i++)
		if(p[a[i]^x])
		p[a[i]^x]--; 
		else
		ok=0;
		if(ok)
		ans.push_back(x);
	}
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	cout<<ans.size()<<'\n';
	for (auto x:ans)
	cout<<x<<'\n';
}
```


---

