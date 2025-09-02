# [ABC215D] Coprime 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc215/tasks/abc215_d

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられるので、以下の条件を満たす $ 1 $ 以上 $ M $ 以下の整数 $ k $ を全て求めてください。

- 全ての $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ について、 $ \gcd(A_i,k)=1 $ である。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,M\ \le\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^5 $

### Sample Explanation 1

例えば、 $ 7 $ は $ \gcd(6,7)=1,\gcd(1,7)=1,\gcd(5,7)=1 $ を満たすので答えとなる整数の集合に含まれます。 一方、 $ 9 $ は $ \gcd(6,9)=3 $ となるため、答えとなる整数の集合に含まれません。 条件を満たす $ 1 $ 以上 $ 12 $ 以下の整数は $ 1,7,11 $ の $ 3 $ つです。これらを小さい方から出力することに注意してください。

## 样例 #1

### 输入

```
3 12
6 1 5```

### 输出

```
3
1
7
11```

# 题解

## 作者：So_noSlack (赞：10)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc215_d)&[Atcoder 链接](https://atcoder.jp/contests/abc215/tasks/abc215_d)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定 $N$，$M$ 及含有 $N$ 个整数的序列 $A$。

求 $1 \sim M$ 中与所有 $a_i$ 均互质的整数及个数。

## 思路

首先说一下**最开始的想法**。

直接**暴力枚举** $1 \sim M$ 的数，再**分别枚举**每个数与 $a_i$ 是否互质，时间复杂度 $O(N \times M)$ 左右，一看数据范围**直接爆炸**，[提交结果](https://www.luogu.com.cn/record/117176579)就可想而知了。

TLE $0$ 分代码如下，因为是暴力就不写注释了：

```cpp
#include<iostream>
#include<cmath>
using namespace std;

int n, m, a[100005], num[100005], ans = 0;

int gcd(int x, int y) {
    return (y == 0 ? x : gcd(y, x % y));
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    for(int i = 1; i <= m; i ++) {
        bool flag = false;
        for(int j = 1; j <= n; j ++) 
            if(gcd(a[j], i) != 1) { flag = true; break; }
        if(!flag) ans ++, num[ans] = i;
    }
    cout << ans << endl;
    for(int i = 1; i <= ans; i ++) cout << num[i] << endl;
    return 0;
}
```

接下来让我们进行一点小优化。

既然对于 $1 \sim M$ 每个数进行暴力枚举会超时，那么就需要**在输入时进行一些标记**，经过一些尝试后发现，可以在输入时**记录每个数的因数**并标记在 $flag$ 数组中，看到 $a_i$ 的数据范围后发现**可以用桶存**。因为 $a_i$ 的因数会重复，所以在输入后需要另开一个 $vul$ 存储序列 $A$ 的**所有因数**，不必用桶存。

如：

```cpp
#define MAXN 1000000

void f(int x) {
    flag[x] = true;
    for(int i = 2; i * i <= x; i ++) 
        if(x % i == 0) flag[i] = flag[x / i] = true;
    return;
}
                             
int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) { cin >> x; f(x); }
    for(int i = 2; i <= MAXN; i ++) 
        if(flag[i]) vul[++ t] = i;
    return 0;
}
```

接着就可以**不那么暴力的枚举**了。

首先枚举 $1 \sim M$ 是一定的，但在第二层循环中仅需**枚举当前** $i$ **是否为** $vul$ **中因数的倍数**，如果是直接跳出当前循环，如果跑了一遍 $vul$ 发现当前 $i$ **不是任何** $vul$ 中因数的倍数，则**记录答案**至数组 $num$ 中即可。

经过以上**一点小优化**，很容易即可写出**代码**：

```cpp
#include<iostream>
#include<cmath>
using namespace std;

#define MAXN 1000000 // 最大值

int n, m, x, t, vul[MAXN + 5], num[MAXN + 5], ans, j;
bool flag[MAXN + 5];

void f(int x) {
    flag[x] = true;
    for(int i = 2; i * i <= x; i ++) // 遍历 x 求因数
        if(x % i == 0) flag[i] = flag[x / i] = true; // 标记 x 的因数
    return;
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) { cin >> x; f(x); } // 输入中处理
    for(int i = 2; i <= MAXN; i ++) 
        if(flag[i]) vul[++ t] = i;
    for(int i = 1; i <= m; i ++) {
        for(j = 1; j <= t; j ++)
            if(i % vul[j] == 0) break; // 不满足情况直接跳出循环
        if(j == t + 1) num[++ ans] = i; // 满足情况记录答案
    }
    cout << ans << endl; // 输出个数
    for(int i = 1; i <= ans; i ++) cout << num[i] << endl; // 输出答案
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117177800)

$$\text{The End!!!}$$

---

## 作者：User_Unauthorized (赞：3)

## 题意
给定数列 $A_N$ 和一个正整数 $M$，求出所有的 $1 \le k \le M$ 满足 $\forall i \in \left[1,N\right],\gcd(k, A_i) = 1$。

## 题解
**本题存在线性复杂度算法。**

记 $\operatorname{lpf}(n) = [1 < n] \min\{p : p \mid n\} + [1 = n]$，即 $n$ 的最小质因数。特别地，$n=1$ 时，其值为 $1$。

考虑线性筛筛出合数的过程，合数 $n$ 会被 $\dfrac{n}{\operatorname{lpf}(n)}$ 筛掉，从 $n$ 向其连边，可以发现最终会形成一棵树。建树过程的复杂度为 $\mathcal{O}(N)$，接下来我们在这棵树上进行操作。

首先对数列 $A_n$ 的每个元素 $A_i$，在这棵树上的对应节点打上一个 $tag$，然后我们暴力向上跳，给路过的每个节点和边打上 $tag$，其中给边 $\left(u, pa_u\right)$ 打 $tag$ 直接给 $\operatorname{lpf}(u)$ 对应的节点打上 $tag$ 即可，如果我们跳到已经打过 $tag$ 的点那么就停止向上跳。其中我们是通过给边打 $tag$ 来处理出在这个数列中所有作为质因子出现的质数，给节点打 $tag$ 是为了避免多余的处理，可以看出每条边最多被处理一次，所以这部分复杂度也是线性。

现在我们已经处理出了所有在这个数列中出现的质因子，易证符合题目条件的 $k$ 就是不含有这其中任意一个质因子的数，所以我们下面考虑将 $tag$ 下方，只要一条边对应的质数被打上了 $tag$，那么所有到根节点路径上有这条边的数都含有该质因子，所以我们考虑从上而下的下方 $tag$，同时可以断定 $pa_u < u$，即 $u$ 节点的父节点值一定比 $u$ 小，所以从小到大遍历节点，考虑父亲节点是否打上 $tag$ 和 当前节点与父亲节点相连的边是否打上 $tag$ 即可，同上面一样，给节点打 $tag$ 一是为了记录答案，二是可以减少不必要的重复遍历，这部分中每条边最多被处理一次，所以这部分复杂度也是线性。总复杂度也为线性。

考虑到本题数据过水，不能体现出线性算法的效率，所以造了一个加强版：[T358758](https://www.luogu.com.cn/problem/T358758)。

## Code
```cpp
//A
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bool> bitset;

constexpr valueType MAX = 1e5 + 5;

int main() {
    std::ios_base::sync_with_stdio(false);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector source(N);

    for (auto &iter: source)
        std::cin >> iter;

    ValueVector father(MAX + 1, 1);

    bitset tag(MAX + 1, true);

    ValueVector primeList;

    primeList.reserve(std::ceil((long double) MAX / std::log((long double) MAX)));

    for (valueType i = 2; i <= MAX; ++i) {
        if (__builtin_expect(tag[i], false)) {
            father[i] = 1;
            primeList.emplace_back(i);
        }

        for (auto const &iter: primeList) {
            valueType const t = iter * i;

            if (t > MAX)
                break;

            tag[t] = false;
            father[t] = i;

            if (__builtin_expect(i % iter == 0, false))
                break;
        }
    }

    std::fill(tag.begin(), tag.end(), false);

    typedef std::function<void(valueType)> TagFunction;

    TagFunction solve = [&father, &tag](valueType n) {
        while (n > 1 && !tag[n]) {
            tag[n] = true;
            tag[n / father[n]] = true;
            n = father[n];
        }
    };

    for (auto const &iter: source)
        solve(iter);

    tag[1] = false;
    for (valueType i = 2; i <= MAX; ++i)
        tag[i] = tag[i] || (tag[father[i]] || tag[i / father[i]]);


    ValueVector result;

    result.reserve(M);

    result.push_back(1);

    for (valueType i = 2; i <= M; ++i)
        if (!tag[i])
            result.push_back(i);

    std::cout << result.size() << '\n';

    for (auto const &iter: result)
        std::cout << iter << '\n';

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：To_Carpe_Diem (赞：2)

## 基本概括
当解决这个问题时，我们需要找到满足条件的整数 $k$，使得对于给定的序列 $A=(A_1,A_2,\dots,A_N)$ 中的每个数 $A_i$，都**满足** $\gcd(A_i, k) = 1$。
## 实现思路
首先，我们可以观察到，如果 $k$ 是 $A_i$ 的质因数或其倍数，那么 $\gcd(A_i, k)$ 将不等于 1。因此，我们可以推断出，我们需要找到不是序列 $A$ 中任何数的**质因数**或**倍数的整数** $k$。

为了找到满足条件的整数 $k$，我们可以使用**质因数分解**的思想。对于序列 $A$ 中的每个数 $A_i$，我们可以将其进行质因数分解，然后将分解得到的质因数及其倍数标记为不满足条件的。**剩下的整数**即为满足条件的整数 $k$。
## 实现过程
为了实现质因数分解和标记的过程，我们可以使用一个布尔数组 `vis` 来记录 $1$ 到 $m$ 之间的整数是否满足**互质条件**。初始化时，我们将 `vis` 数组的所有元素都设置为 true。

对于序列 $A$ 中的每个数 $A_i$，我们将其进行**质因数分解**。对于每个质因数 $j$，我们将从 $j$ 开始，递增地将 `vis` 数组中的对应整数位置设置为 false，保证**不满足互质条件**。注意要在循环中**跳过已经被其他质因数标记的位置**。

具体来说，对于每个 $a_i$，我们从 $2$ 开始**遍历**到 $\sqrt{a_i}$，如果当前数能整除 $a_i$，那么它就是 $a_i$ 的一个质因子。我们将其标记在 `vis` 中对应位置的整数置为 false，然后不断除以这个**质因子**，直到 $a_i$ **不再能整除**这个质因子为止。如果 $a_i$ 大于 $1$，那么它本身也是一个质因子，我们将其标记在 vis 中对应位置的整数置为 false。这样，我们就完成了对于每个 $a_i$ 的**质因子**的处理。

最后，我们遍历整数 $1$ 到 $m$，将 `vis` 的第 k 项设置为 true 的整数加入结果向量 `ans` 中。至此，我们找到了所有**满足条件**的整数。

在代码的最后，我们按照题目要求输出结果，首先输出结果向量 `ans` 的长度，然后逐行输出结果。
## 整体总结
整体而言，通过**筛法**的思想和**质因数分解**的方法，我们可以高效地找到满足条件的整数。
## AC Code
```cpp
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> a;
vector<int> ans;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<bool> vis(m + 1, true);
    for (int i = 0; i < n; i++) {
        int num = a[i];
        for (int j = 2; j * j <= num; j++) {
            if (num % j == 0) {
                while (num % j == 0) {
                    num /= j;
                }
                for (int k = j; k <= m; k += j) {
                    vis[k] = false;
                }
            }
        }
        if (num > 1) {
            for (int k = num; k <= m; k += num) {
                vis[k] = false;
            }
        }
    }

    for (int k = 1; k <= m; k++) {
        if (vis[k]) {
            ans.push_back(k);
        }
    }

    cout << ans.size() << endl;
    for (int k : ans) {
        cout << k << endl;
    }

    return 0;
}//看在我写的如此详细，就点个赞吧
```

---

## 作者：Bpds1110 (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/AT_abc215_d)
## 题面：
给出 $N$ 个数字，求出在 $1$ 到 $N$ 中，哪些数和每一个给出的数互质。
## Solution:
因为要互质，所以这个数一定要与给出的**任何数的因数互质**。我们先求出每个数的因数，把它们用桶 $f$ 记录是否出现（去重），再把每个因数存放到数组 $p$ 中，最后暴力枚举每一个可能与其它数互质的数，如果它能被 $\mathit{p}_{i}$ 整除，那么它们一定不是互质数，因为至少有因数 $\mathit{p}_{i}$。最后，把可能性记录到答案数组中，输出即可。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std ;
const int maxn = 1e6 + 1;
int n, m, i, j, x, ans, t, a[maxn ], p[maxn ] ;
bool f[maxn ] ;
void find (int x )
{
	f[x] = 1;//x一定是x的因数 
	for (int i = 2; i*i <= x; i ++)
		if (! (x % i))//整除，i是x的因数 
		{
			f[i] = 1;
			f[x / i] = 1;
		}
}
int main()
{
	cin >> n >> m;
	for( i = 1; i <= n; i ++)
	{
		cin >> x;
		find (x);//求出所有因数 
	}
	for ( i = 2; i <= maxn ; i ++)
		if (f[i]) p[++ t] = i;//存放到数组p中 
	for( i = 1; i <= m; i ++)//暴力枚举可能性 
	{
		for( j = 1; j <= t; j ++)
			if (! (i % p[j]) ) break;//并不互质 
		if (j == t +1 ) a[++ ans] =i;//记录到答案数组中 
	}
	cout << ans << "\n" ;
	for ( i = 1;i <= ans; i ++)
		cout << a[i] << "\n" ;
	return 0 ;
}

```


---

## 作者：syzxzqy (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc215_d)  
#### 思路:
此题意思十分明确，求出有多少 $k$ 满足：$\gcd(k,a_1)=1,\gcd(k,a_2)=1,\cdots,\gcd(k,a_n)=1$。  
首先，$k$ 只要与 $a_1,a_2,\cdots,a_n$ 的质因数互质，即可与这些数互质。  
其次，$k$ 要枚举 $1$ 至 $m$ 每个数，使我们想起筛质数——可以用较小的质数筛除较大数。  
因此，此题也可用筛素数的方法，先求出 $a$ 中所有的质因数，再筛除质因数的倍数，求得答案。  
#### 代码:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000001,M=1001;
int n,m,i,x,j,t,s,prime[N],f[N],e[N],ans[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;++i){
		cin>>x;
		for(j=2;j*j<=x;++j)//分解质因数
			if(x%j==0){//如果j是x的质因数
				if(!f[j]) f[j]=1,prime[++s]=j;//判断保存过这个质因数没，如果没保存，就保存j
				while(x%j==0) x/=j;
			}
		if(x>1&&!f[x]) f[x]=1,prime[++s]=x;//最大的质因数，方法如上
	} 
	for(i=1;i<=s;++i)//类似于筛质数
		for(j=prime[i];j<=m;j+=prime[i])
			e[j]=1;//e[j]=1表示j不满足条件
	for(i=1;i<=m;++i)
		if(e[i]==0) ans[++t]=i;//找出答案
	cout<<t<<"\n";
	for(i=1;i<=t;++i) cout<<ans[i]<<"\n";
}
```


---

## 作者：xiaoyuchenp (赞：1)

思路比较简单的 $O(n \sqrt{n})$ 复杂度做法。

**思路一**

暴力枚举 $1$ 与 $m$ 之间的所有数，再枚举与每一个 $a_i$ 是否互质，显然超时。代码很好实现，因此就不放在这里了。

**思路二**

正解做法。

设要找到的答案为 $k$，若 $k$ 与每一个 $a_i$ 都互质，显然 $k$ 与 $a_i$ 的因数都互质。注意 $a_i$ 的范围较小，因此可以用标记数组标记 $a_i$ 的每一个因数，再与 $k$ 进行比较。一个优化的小细节：枚举 $a_i$ 的因数只需枚举到 $\sqrt{a_i}$ 即可，很容易证明 $\sqrt{a_i}$ 后的因数均为 $\sqrt{a_i}$ 前因数的倍数。找因数时同理。

坑点：标记完因数后需要再跑一遍标记数组，将因数全部处理出来存储到另一个整型数组里，不能在求解的时候逐一搜索，不然时间复杂度实质上没有进行任何优化。

**code**

```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
using namespace std;
int n,m,a,j;
bool flg[MAXN];
int tmp[MAXN],cnt=0,ans[MAXN],anstot=0;
void init(int n){
	flg[n]=true;
	for(int i=2;i*i<=n;i++)
		if(n%i==0)flg[i]=flg[n/i]=true;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a;init(a);
	}
	for(int i=2;i<=MAXN;i++)
		if(flg[i])tmp[++cnt]=i;
	for(int i=1;i<=m;i++){
		for(j=1;j<=cnt;j++)
			if(i%tmp[j]==0)break;
		if(j==cnt+1)ans[++anstot]=i;
	}
	cout<<anstot<<'\n';
	for(int i=1;i<=anstot;i++)cout<<ans[i]<<'\n';
	return 0;
} 
```

---

## 作者：fmdd_szx (赞：1)

[原题](https://www.luogu.com.cn/problem/AT_abc215_d)
# 题意
给定 $N$，$M$ 和序列 $A$，求 $1$ 到 $i$ 中与 $a_i$ 互质的数。
# 思路
一个数互质另一个数，这个数必须与另一个数所有因数互质。因此先要求出每个数的因数，再把因数保存到 $r$ 数组中。最后暴力枚举，判断这个数是否与其它数互质。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,cnt,x,t,f[1000001],r[1000001],ans[1000001];
int main(){
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>x;
        for(j=2;j*j<=x;j++)
            if(x%j==0) f[j]=1,f[x/j]=1;//给因数做上标记
        f[x]=1;//自己也是自己的因数
    }
    for(i=2;i<=1e6;i++)
        if(f[i]==1) r[++t]=i;//把因数保存到数组r中
    for(i=1;i<=m;i++){//开始暴力枚举
        for(j=1;j<=t;j++)
            if(i%r[j]==0) break;//如果不互质
        if(j==t+1) ans[++cnt]=i;//把这个数存入答案中
    }
    cout<<cnt<<"\n";
    for(i=1;i<=cnt;i++)
        cout<<ans[i]<<"\n";
    return 0;
}
```

---

## 作者：guanyf (赞：1)

### 题意
- 给定长度为 $N$ 的序列 $A$，现在要你求出 $1 \sim M$ 中有哪些数可以跟 $A$ 中的所有元素互质。

- $1 \le N,M,A_i \le 10^5$

### 分析、思路

先说一个暴力做法：枚举 $x(1 \le x \le M)$，再判断 $\gcd(x,A_j(1\le j \le N))$ 是否等于 $1$。

上述做法由两部分组成：枚举、检验。如果能将**检验**这一部分优化成 $\operatorname O(1)$，则程序可以通过。

我们不妨反其道而行之，先预处理出哪些数是不合法的，在检验的时候直接判断就行了。

思考互质的本质：当两个数只共同拥有一个因数 $1$ 时，则互质。但这样依然复杂。我们可以分析**不互质**的本质：当两个数拥有除 $1$ 以外的因数时，则不互质。**因次可以枚举因数，当它的倍数是 $A$ 中的元素时，则它所有的倍数都不合法。**

接着按照一开始的思路去做就行了：如果一个数没有被标记，则它是合法的。切记：**枚举因数时要从 $2$ 开始。**

时间复杂度：$\operatorname O(\max (A_i)\times \log \max( A_i))$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5, INF = 1e5;
int n, m, a[MAXN], cnt;
unordered_map<int, bool> v, vis;  // 记录 A 中元素是否存在，记录是否合法
void init() {                     // 预处理
  for (int i = 2; i <= INF; i++) {
    bool flag = 0;
    for (int j = i; j <= INF; j += i) {
      flag |= v[j];
    }
    for (int j = i; j <= INF; j += i) {
      vis[j] |= flag;
    }
  }
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], v[a[i]] = 1;
  }
  init();
  for (int i = 1; i <= m; i++) {
    cnt += !vis[i];
  }
  cout << cnt << '\n';
  for (int i = 1; i <= m; i++) {
    if (!vis[i]) {
      cout << i << '\n';
    }
  }
  return 0;
}
```


---

## 作者：Trump_ (赞：0)

将输入的数的质数公因数用埃氏筛筛出来，用一个数组存下来。每次将质因数的倍数用 ``flag`` 标记，表示这个数存在因数与输入的数重复的情况。

正确性的话：一个合数一定会被分解成一种或多种质因数，所以每次找质因数就行辣。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector> 

using namespace std;

int n, a[5211314], m;
int gcd_sum, ans[2000010], sum, is_gcd[2000010], rec_gcd[2000010];
bool barrel[2000010], is_prime[2000010], flag[2000010];

void Prime() {
	//正经的埃氏筛
	memset(is_prime, true, sizeof(is_prime));
	for (int i = 2; i <= m; ++ i) {
		if (is_prime[i] == false) continue;
		for (int j = i; j <= m; j = j + i) {
			is_prime[j] = false;
			//找输入的数的质因数
			if (barrel[j] == true && rec_gcd[i] == false) {
				//如果i的倍数是输入的数并且质因数i没有被存过
				is_gcd[++ gcd_sum] = i;
				rec_gcd[i] = true;
				//这里记录的原因是保证复杂度
			}
		}
	}
	return;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", &a[i]);
		barrel[a[i]] = true;
		//将输入的数用桶先存下来
	}
	Prime();
	for (int i = 1; i <= gcd_sum; ++ i) {
		for (int j = is_gcd[i]; j <= m; j += is_gcd[i]) {
			//将每个质数因数的倍数标记
			flag[j] = true;
		}
	}
	for (int i = 1; i <= m; ++ i) {
		if (flag[i] == false) {
			//不存在输入的数的质因数
			ans[++ sum] = i;
		}
	}
	//输出
	printf("%d\n", sum);
	for (int i = 1; i <= sum; ++ i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}


---

## 作者：白简 (赞：0)

#### 题目大意
给定一个长度为 $n$ 的数列 $a$，要求出 $1 \sim m$ 中与 $a$ 中的所有元素互质的数。
数据范围：$1\ \leq\ n,m\ \leq\ 10^5,1\ \leq\ a_i\ \leq\ 10^5$。
#### 思路
模拟赛加强了数据，卡了 $\mathcal{O}(n \sqrt{n})$，于是来写一个 $\mathcal{O}(n \log n)$ 的。

考虑互质是什么意思，是指两个数只有一个共同因数 $1$。那么如果两个数有除 $1$ 以外的共同因数，二者不互质。

所以我们可以枚举因数，若其倍数是 $a$ 中的元素，就可以标记我们枚举的这个因数的所有倍数都是不合法的，然后可以标记。

没标记的数都是合法的，到时候直接计数输出就行了。

---

## 作者：ylch (赞：0)

# AT_abc215_d [ABC215D] Coprime 2 题解

[-题目传送门-](https://www.luogu.com.cn/problem/AT_abc215_d)

## 题目大意

~~这题算是 AT 里最清楚的题之一了~~

就是让你求存在多少个 $k$，使得 $k$ 与数组 $a$ 的每一个元素都互质。

## 解题思路

要求 $k$ 与 $a$ 数组所有元素互质，那么 $k$ 一定也是与 $a$ 数组所有元素的因数互质的。

所以可以用集合（set）存储 $a$ 数组所有元素的因数，再暴力枚举 $k$ 的个数，存储到答案数组中即可（如果 $k$ 都不能整除集合中的数，答案加一）。

可以再优化一下细节，我们在判断质数时要找被判断数的因数，但是只要枚举到 $\sqrt{n}$ 就行，这是因为 $\sqrt{n} \sim (n-1)$ 中的数字一定是 $2 \sim \sqrt{n}$ 中数字的倍数。

那么找因数的时候也可以这样，枚举到 $\sqrt{n}$，如果 $n$ 能整除 $i$，那么 $i$ 和 $n \div i$ 就都是 $n$ 的因数了。这样做将时间复杂度由 $\text{O}(n)$ 降为 $\text{O}(\sqrt{n})$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

set<int> se;	//用集合是因为自动排序去重，不用打标记了

void find_factors(int n)
{
	if (n != 1)	// 1 是所有数的因数，所以不能算
		se.insert(n);	// n 一定是 n 的因数
	for (int i=2; i*i<=n; i++)	//小技巧，省去 sqrt 的复杂度
		if (n%i == 0)
		{
			se.insert(i);
			se.insert(n/i);
		}
}

vector<int> a(100005),b;
int n,m;

signed main()
{
	cin >> n >> m;
	for (int i=0; i<n; i++)
	{
		cin >> a[i];
		find_factors(a[i]);
	}
	for (int i=1; i<=m; i++)
	{
		set<int>::iterator it;
		for (it=se.begin(); it!=se.end(); it++)
			if (i % (*it) == 0)	break;
		if (it == se.end())	b.push_back(i);
	}
	cout << b.size() << endl;
	for (auto it=b.begin(); it!=b.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}
```

题解完毕。。。吗？——代码超时了

想了想，set 插入复杂度可能过高，还是老老实实打标记吧。

## AC 代码（不坑人）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5;

int n,m,i,j,x,ans,t,a[maxn],p[maxn];
bool f[maxn];

void find_factors(int x)
{
	f[x] = 1;	// x 一定是 x 的因数 
	for (int i=2; i*i<=x; i++)
		if (x%i == 0)	// i 是 x 的因数 
		{
			f[i] = true;
			f[x/i] = true;
		}
}

signed main()
{
	cin >> n >> m;
	for (i=1; i<=n; i++)
	{
		cin >> x;
		find_factors(x);	//求出所有因数 
	}
	for (i=2; i<=maxn; i++)
		if (f[i]) p[++t] = i;	//因数存放到数组p中 
	for (i=1; i<=m; i++)	//暴力枚举可能性 
	{
		for (j=1; j<=t; j++)
			if (i%p[j] == 0) break;
		if (j == t+1) a[++ans] = i; 
	}
	cout << ans << endl;
	for (i=1; i<=ans; i++)
		cout << a[i] << endl;
	return 0 ;
}
```

End
------------

管理员大大辛苦啦~

谢谢大家！

---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/AT_abc215_d)
# 解题思路：
因为 $m$ 比较小，所以我们考虑用一个数组来存储每一个数是否可选。

对于每一个输入的 $a_i$，我们把它所有除了 $1$ 以外的所有因数都在数组中赋成 $1$，即这个数不可选。

因为题目要求求出有多少个对 $k$ 与所有的 $a_i$ 都互质，所以我们也应该排除当前数组中的所有不可选数的倍数。最后数组中还为 $0$ 的是就是可选的数。
# Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
typedef long long LL;
LL n, m, x, f[100010], g[100010], ans; 
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m; 
	for(re int i = 1; i <= n; i ++) {
		cin >> x; 
		if(x != 1) f[x] = 1; //这边要注意排除是1的情况
		for(re int i = 2; i * i <= x; i ++) //找除1以外的因数
			if(x % i == 0)f[i] = f[x / i] = 1; 
	}
	for(re int i = 1; i <= m; i ++) 
		if(f[i]) 
			for(re int j = i; j <= m; j += i)
				g[j] = 1; //排除所有不可选数的倍数
	for(re int i = 1; i <= m; i ++)
		if(!g[i]) ans ++; //统计总数
	cout << ans << "\n"; 
	for(re int i = 1; i <= m; i ++)
		if(!g[i]) cout << i << "\n"; 
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路

把每一个数分解质因数，这一步是保证的筛掉的数是质数，然后把 $m$ 以内的所有质因数的倍数全部筛掉，这样就保证了 $m$ 以内没筛掉的数与那个数的 $\gcd$ 等于 $1$，最后没有被筛掉的就是我们要的答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000;
bool st[maxn];
vector<int>f(int x){
	vector<int>vec;
	for(int i=2;i*i<=x;i++){
		while(x%i==0){
			vec.push_back(i);
			x/=i;
		}
	}
	if(x!=1){vec.push_back(x);}
	return vec;
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		vector<int>vec=f(a);
		for(auto &x:vec){
			if(!st[x]){
				for(int j=x;j<=m;j+=x){
					st[j]=1;
				}
			}
		}
	}
	vector<int>ans;
	for(int i=1;i<=m;i++){
		if(st[i]==0){
			ans.push_back(i);
		}
	}
	cout<<ans.size()<<"\n";
	for(auto x:ans){
		cout<<x<<"\n";
	}
	return 0;
}
```

最后说一个好玩的事，作者在做着一道题的时候把分解质因数复杂度想成了 $O(n)$，最后没想出来看了一下题解才想起来是根号，希望大家不会和我犯一个错误。

---

## 作者：zeekliu (赞：0)

**温馨提示：这个方法比较简单好想，但最慢点跑了接近 1s，可能会比较悬，可能要卡常，我太菜了。**

![](https://cdn.luogu.com.cn/upload/image_hosting/jtiw14oz.png)

首先~~傻子都知道~~如果这个数对数组内任何一个数最大公因数为 $1$，那么可以知道这个数不是任何一个数组内的数的因数。

所以，思路很明显，将数组中的数分解因数，然后记录到一个数组内。一开始将其中所有数设为 $0$，然后枚举（设这个枚举的数为 $n$），遇到 $n$ 的因数 $i$ ，就记录至数组内，同时将 $\frac{n}{i}$ 记录至数组内。

**要注意的是，要特别将 $n$ 记录，因为这里并不会枚举 $1$,所以也同样不会枚举到 $n$，这时候就要特别记录（否则可能会出现 $n$ 是一个大素数的情况）。**

当记录完后，从 $1$ 枚举至 $m$，需要判断正在枚举的数是否是其中某个记录因数的倍数，为了防止复杂度过高（$n=10^5$ 时 $O(n^2)$ 直接爆炸），我们将其中因数提取出来，放入一个新数组内，就会好很多。如果满足要求，再开一个数组记录其中符合要求的数即可。

代码（上面的说法太复杂，看代码比较直观）：

```cpp
//ABC215D 23.01.05
#include <bits/stdc++.h>
using namespace std;
int n,m,cnt=0,t=0,tt=0;
int a[100010],b[100010],c[100010],d[100010];

inline void factor(int n)
{
    for (int i=2;i<=sqrt(n);i++)
        if (n%i==0) b[i]=1,b[n/i]=1;
    b[n]=1;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    memset(b,0,sizeof(b));
    cin>>n>>m;
    for (int i=1;i<=n;i++) cin>>a[i],factor(a[i]);
    for (int i=2;i<=1e5;i++)
        if (b[i]) t++,c[t]=i;
    for (int i=1;i<=m;i++)
    {
        for (int j=1;j<=t;j++)
            if (i%c[j]==0) goto bk;
        cnt++,tt++,d[tt]=i;
        bk:;
    }
    cout<<cnt<<endl;
    for (int i=1;i<=tt;i++) cout<<d[i]<<endl;
    exit(0);
}
```

附：[官方题解 (en)](https://atcoder.jp/contests/abc215/editorial/2513)

---

## 作者：loser_seele (赞：0)

首先不难得到一个结论：若 $ k $ 与数列中每一个数互质，则 $ k $ 质因数分解后的质因子集合不出现在 $ a $ 的每一项质因子集合中。

所以对 $ a $ 的每一项质因数分解，然后对于所有的质因子 $ d $，将所有 $ [1,m] $ 内能被 $ d $ 整除的数类似筛子一样标记，最后所有没有被标记的数即为答案。这里使用 Pollard-rho 分解质因数，时间复杂度 $ \mathcal{O}(n \times a_i^{\frac{1}{4}}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x) 
{
	x=0;
	T k=1;
	char gc;
	while(!isdigit(c)) 
    {
		if(c=='-')k=-1;
		gc;
	}
	while(isdigit(c)) 
    {
		x=x*10+c-'0';
		gc;
	}
	x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p) 
{
	a+=b;
	if(a>=p)
	    a-=p;
	return a;
}
inline int mul(int a,int b,int mod) 
{
	return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
	ll ans = 1;
	for (a %= m; b; b >>= 1, a = mul(a, a, m))
	    if (b & 1) 
	    ans = mul(ans, a, m);
	return ans;
}
ll gcd(ll a,ll b) 
{
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b) 
{
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
	ll k = pow(a, s, p);
	if (k == 1) 
    return true;
	for (; d; --d, k = mul(k, k, p))
    {
		if (k == p - 1) 
		    return true;
		if (k == 1) 
		    return false;
	}
	return k == 1;
}
bool MR(ll x) 
{
	static const int cnt = 12;
	static const int p[cnt] = {2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251};
	if (x == 1) 
	  return false;
	ll s = x - 1;
	int d = 0;
	while (!(s & 1)) 
	  ++d, s >>= 1;
	for (int i = 0; i < cnt; ++i) 
    {
		if (x % p[i] == 0) 
		    return x == p[i];
		if (!MR_check(p[i], x, s, d)) 
		    return false;
	}
	return true;
}
namespace Pollard_Rho 
{
	ll PR_check(ll c, ll p) 
    {
		ll y = rand() % p, z = y;
		int k = 1, j = 0;
		while(1145141919810) 
        {
			z = (mul(z, z, p) + c) % p;
			ll t = gcd(p, std::abs(z - y));
			if (t > 1) 
			    return t;
			if (++j == k) 
			    y = z, k <<= 1;
		}
	}
	void factor_(ll x, std::vector<ll> &v) 
    {
		if (x == 1) 
        return;
		if (MR(x)) 
        {
			v.push_back(x);
			return;
		}
		ll y = x;
		while (y == x) 
        y = PR_check(rand() % x, x);
		factor_(y, v);
		factor_(x / y, v);
	}
	void factor(ll x, std::vector<ll> &v) 
    {
		v.clear();
		if (!(x & 1)) 
        {
			v.push_back(2);
			x /= (x & -x);
		}
		factor_(x, v);
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
	}
}
using Pollard_Rho::factor;
unordered_map<int,int>vis;
bitset<2000020>cur;
signed main() 
{
	int T=1;
	int SIZE=1e5;
	for (;T;--T) 
    {
		int n,lim;
		r(n),r(lim);
		for (int i=1;i<=n;i++) 
        {
			int x;
			r(x);
			vector<int>d;
			factor(x,d);
			for (auto x:d)
			        vis[x]=1;
		}
		for (auto x:vis)
		        for (int j=1;j*x.first<=lim;j++)
		        cur[j*x.first]=1;
		vector<int>ans;
		for (int i=1;i<=lim;i++)
		        if(!cur[i])
		        ans.push_back(i);
		cout<<ans.size()<<'\n';
		for (auto x:ans)
		        cout<<x<<'\n';
	}
}
```


---

