# A BIT of a Construction

## 题目描述

给定 $n,k$，请构造序列 $a_n$，你需要保证 $a_i$ 为自然数，同时满足以下条件：

* $\sum\limits_{i=1}^{n} a_i=k$。

* $a_1|a_2|\dots|a_n$ 二进制下拆位后 $1$ 的数量最大，其中 $|$ 表示[按位或](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E6%88%96/548283?fr=ge_ala)。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le2\times10^5$，$1\le k\le10^9$，$\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
4
1 5
2 3
2 5
6 51```

### 输出

```
5
1 2
5 0
3 1 1 32 2 12```

# 题解

## 作者：Pursuewind (赞：12)

## 题目大意

给你 $n,k$，请构造一个长度为 $n$ 的自然数序列，在满足序列的和为 $k$ 的情况下最大化将它们全部按位或起来的结果在二进制下一的数量。

## 做法

以下将构造序列全部按位或起来的结果设为 $res$，$k$ 在二进制下有 $x$ 位（最高位对应十进制下的 $2^{x-1}$）。

一件很显然的事情是，我们的 $res$ 中 $1$ 的个数最多为 $x+1$（当 $k$ 为 $2^a-1$ 时，$a$ 为自然数），大多时候最多为 $x$（当 $k$ 不为 $2^a-1$ 时，$a$ 为自然数）。

那么我们这样构造：

$2^{x-1},k-2^{x-1},0,0,\dots,0$。

第一个数为了凑出 $x$ 个 $0$，第二个数为了使和为 $k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
	int n, k;
	cin >> n >> k;
	if (n == 1){
		cout << k << "\n";
		return ;
	} 
	int x = 0;
	for (int i = 63; i >= 0; i --){
		if (k & (1ll << i)){
			x = i;
			break;
		}
	}
	cout << (1ll << x) - 1 << " " << k - (1ll << x) + 1 << " ";
	for (int i = 1; i <= n - 2; i ++){
		cout << "0 ";
	}
	cout << "\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：_shine_ (赞：2)

因为 $\sum\limits_{i=1}^na_i=k$，所以必定满足所有的数均小于等于 $k$，那显然满足所有的数位的二进制位数均小于等于 $k$ 的位数。

那么对于所有的数或起来的二进制下的位数显然满足小于等于 $k$ 的二进制下的位数，那么显然最优情况就是把所有的二进制数位全部设置为 $1$。

则可以直接枚举出第一个比 $k$ 大的 $j\left(j=2^i\right)$，则最终答案容证为 $\frac{j}{2}-1$。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int T,n,k,a[maxn];
signed main(){
    cin >> T;
    while(T--){
        cin >> n >> k;int idx=0,num=1;
        while(num<=k)num*=2;num/=2;num--;
        a[++idx]=num;
        if(idx==n && k-num!=0)a[idx]=k;
        else a[++idx]=k-num;
        while(idx<n)a[++idx]=0;
        for(int i=1;i<=idx;++i)cout << a[i] << " ";cout << endl;
    }
    return 0;
}
```

---

## 作者：一只小菜包 (赞：2)

### 分析
题目要求构造一个长度为 $n$ 的非负整数序列，使得序列中所有数的和等于 $k$，同时要求序列中所有数按位或运算的结果中 $1$ 的个数最多。

首先，如果 $n = 1$，那么问题变得非常简单，因为只有一个数，直接让这个数等于 $k$ 即可。

当 $n > 1$ 时，我们需要尽可能使得按位或运算的结果中 $1$ 的个数最多。一个有效的策略是首先找到 $k$ 的最高位 $1$ 所在的位置，然后构造一个数 $a _ {0}$，使得这个数在最高位$1$及其以下的所有位都为 $1$，但不超过 $k$。这样，我们就能确保 $a _ {0}$ 的二进制表示中 $1$ 的个数尽可能多。

接着，我们需要构造第二个数 $a _ {1}$。由于 $a _ {0}$ 已经占据了最高位及其以下的所有位，并且不超过 $k$，因此 $a _ {1}$ 只需要等于 $k$ 减去 $a _ {0}$ 即可。这样， $a _ {0}$ 和 $a _ {1}$ 按位或运算的结果将包含所有 $a _ {0}$ 中的 $1$，并且可能还包含一些额外的 $1$ （如果 $a _ {1}$ 在比 $a _ {0}$ 更低的位上有$1$的话）。

最后，由于 $n$ 可能大于 $2$，我们还需要构造剩余的 $n-2$ 个数。由于 $a _ {0}$ 和 $a _ {0}$ 已经尽可能多地占据了高位，并且它们的和等于 $k$，所以剩余的数可以全部设为 $0$，这样不会影响最终的按位或运算结果。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <climits> 

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);

        if (n == 1) {
            a[0] = k;
        } else {
            int msb = 31 - __builtin_clz(k); // 找到k的最高位1
            a[0] = (1 << msb) - 1; // 构造a[0]，使得其在msb及其以下的所有位都为1

            if (a[0] > k) {
                // 如果a[0]超过了k，说明k的最高位1后面直接跟着0，需要减去一个2的幂
                a[0] -= (1 << (msb - 1));
            }

            a[1] = k - a[0]; // 计算a[1]

            fill(a.begin() + 2, a.end(), 0); // 剩余的数全部设为0
        }

        for (int value : a) {
            cout << value << " ";
        }

        cout << "\n";
    }

    return 0;
}
```

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 CF1957B A BIT of a Construction](https://www.luogu.com.cn/problem/CF1957B)

## 题意简述

构造长度为 $n$ 的数列 $a$（$a_i\ge 0$），满足 $\sum a_i=k$，且让数列 $a$ 按位或结果的二进制 $1$ 的个数最多。

## 解题思路

把第 $i$ 位变成 $1$ 的代价为 $2^i$，显然越低位代价越小，所以要让低位尽可能变成 $1$。

从低到高遍历第 $i$ 位，如果能变成 $1$，就让 $a_1$ 加上 $2^i$。

剩下 $k-a_1$ 没用了，不妨全都放到 $a_2$ 上，然后让其他 $a_i=0$（$3\le i \le n$）。

特别地，当 $n=1$ 时，$a_1$ 只能等于 $k$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		if(n==1)
		{
			cout<<k<<' ';
			continue;
		}
		int a1=0;
		for(int i=0;i<=30;i++)
		{
			int x=1<<i;
			if(a1+x<=k)a1+=x;
		}
		cout<<a1<<' '<<k-a1<<' ';
		for(int i=3;i<=n;i++)cout<<0<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：tanshunyu0913 (赞：1)

因为有 $ \sum\limits_{i = 1}^n a_i = k $ 的条件，显然可得最有情况下二进制中的 $1$ 的个数必然小于等于 $k$ 的二进制位数。根据按位或的性质，为了使 $1$ 最多，应该使结果的二进制中每一位都有一个 $1$。最简单的构造方式就是使 $a_1$ 等于 $2^s-1$，满足 $2^s-1 \leq k$（也就是小于等于 $k$ 的数中最大的且二进制下全为 $1$ 的数），$a_2$ 就等于 $k-a_1$,之后就全是 $0$。可以证明这样构造一定是最优的。当然 $n=1$ 时就可以直接输出 $k$ 了。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,k;
int a[N];
signed main(){
	int T;cin>>T;
	a[0]=1;
	for(int i=1;i<=30;i++)a[i]=a[i-1]+(1<<i);
	while(T--){
		cin>>n>>k;
		int j=0,s=0;
		while(a[j+1]<=k)j++;
		s=k-a[j];
		if(n==1){
			cout<<k<<endl;
			continue;
		}
		cout<<a[j]<<' '<<s<<' ';
		for(int i=1;i<=n-2;i++)cout<<0<<' ';
		puts("");
	}
	return 0;
}

---

## 作者：roumeideclown (赞：1)

# CF1957B A BIT of a Construction 题解

## 题意简述

给出两个整数 $n , k$，构造一个非负整数序列 $ a_1, a_2, \ldots, a_n $ 使得

1. $ \sum\limits_{i = 1}^n a_i = k $
2. 在  $ a_1 | a_2 | \ldots | a_n $ 中 $1$ 的数量须最大化，其中 $|$ 表示按位与。

## 题目分析

为方便讨论，设$ a_1 | a_2 | \ldots | a_n = m $，$ \sum\limits_{i = 1}^n a_i=s  $。

显然地，若 $ n=1 $，则输出 $ k $ 即可。

若 $ n \ge 1 $，设 $ x $ 为 $ k $ 的二进制位数，即 $ 2^x \le k \le 2^{x+1} $。因此不难看出，$ m $ 不可能大于 $ x+1 $，否则 $ s $ 会大于 $ k $。

而 $ m=x+1 $ 的情况当且仅当 $ k=2^{x+1}-1 $，当 $ k $ 小于该值时 $ m $ 都取不到 $ x+1 $，否则 $ s $ 会大于 $ k $。

因此，易知 $ m \le x $，于是我们在序列中总可以使用小于等于 $ 2^x-1 $ 的数（即二进制有 $ x $ 位）。

综上所述，通过观察，可得 $ 2^x-1 , k-(2^x-1) , 0 , 0 , \ldots , 0 $ 是一种合法的构造方式。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
void work() {
	//输入 
	int n,k;
	scanf("%d%d",&n,&k);
	//n=1时特判 
	if(n==1) {
		printf("%d\n",k);
		return;
	}
	//m含义如上述分析 
	int m=0;
	//求出m 
	for(int i=0;i<31;i++) {
		if(k&(1<<i)) {
			m=i;
		}
	}
	//输出答案 
	printf("%d %d ",(1<<m)-1,k-((1<<m)-1));
	for(int i=3;i<=n;i++) {
		printf("%d ",0);
	}
	printf("\n");
}
int main() {
	//多组测试数据 
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) {
		work();
	}
	return 0;
}

```

---

## 作者：sbno333 (赞：1)

考虑贪心，首先我们要节约用 $n$，所以要尽量让一个数来贡献。

我们要节约用 $k$，所以先考虑最低位的贡献，如果可以就进行贡献，然后是第二位进行贡献，然后第三位贡献直到最高位贡献。

接着累计这个解，设为 $a_1$，剩下的为了构成 $k$，设为 $a_2$，此时应特判 $n=1$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void _main(){
	int n,k;
	cin>>n>>k;
	if(n==1){
		cout<<k<<endl;
	}else{
		int z;
		z=1;
		while(z*2+1<=k){//z为最终或的值
			z=z*2+1;
		}
		cout<<z<<" "<<k-z<<" ";
		for(int i=3;i<=n;i++){
			cout<<0<<" ";//剩下 0 填充
		}
		cout<<endl;
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：ManGo_Mouse (赞：0)

#### 题目大意

给定 $n,k$，要求构造一个序列 $a$，使得 $\sum_i^n a_i=k$ 并且 $a_1|a_2|a_3|...|a_{n-1}|a_n$ 的二进制中，数字 $1$ 的数量最大。

#### 思路

这题是一道简单的构造题。

想让 $1$ 的数量最多，就要让序列 $a$ 的二进制中，尽量使得 $1$ 的位置不重合。
例如，$a=\{1,1,1\},b=\{11,0,0\}$（二进制数），它们的和都是 $11$，但显然，$b$ 更优。

那么只要使得第一项的二进制上全为 $1$（也就是 $2^{\lfloor \log^2 k \rfloor} -1$），第二项补齐第一项剩下的数（$k-(2^{\lfloor \log^2 k \rfloor} -1)$），其余项为 $0$ 即可。

需要注意的是，当 $n = 1$ 时，直接输出 $k$。

#### Code

```
#include <bits/stdc++.h>
using namespace std;
int t, n, k;
int main() {
    cin >> t;
    while (t --) {
        cin >> n >> k;
        if (n == 1)
            cout << k << '\n';
        else {
            int qwq = (1 << (int)log2(k)) - 1;
            cout << qwq << " " << k - qwq << " ";
            for (int i = 3; i <= n; i ++)
                cout << "0 ";
            cout << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

[Link](https://www.cnblogs.com/Luxinze/p/18162677#b-a-bit-of-a-construction)

题意：构造包含 $n$ 个非负元素的数组，使得 $\sum a_i = k$，并最大化 $a_1 \mid a_2 \dots \mid a_n$ 中 $1$ 的个数。

如果 $n = 1$，则 $a = \{k\}$。

否则：

+ 将 $k$ 的所有 $1$ 往低位移，得到 $1$ 的个数与 $k$ 相同的最小的数 $x$，如 $(10100)_2 \rightarrow (00011)_2$。
+ 从低到高往 $x$ 上添 $1$，直到大于 $k$。

最终只需选两个位置填 $x$ 和 $k - x$，其余填 $0$。

[submission](https://codeforces.com/contest/1957/submission/258192971)

---

