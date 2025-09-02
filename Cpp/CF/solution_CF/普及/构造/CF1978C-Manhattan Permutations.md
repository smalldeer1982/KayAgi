# Manhattan Permutations

## 题目描述

设排列 $p$ 的曼哈顿值为 $ |p_1 - 1| + |p_2 - 2| + \ldots + |p_n - n| $ 。

例如，对于排列 $ [1, 2, 3] $ , 它的曼哈顿值为 $ |1 - 1| + |2 - 2| + |3 - 3| = 0 $ ；
对于排列 $ [3, 1, 2] $ , 它的曼哈顿值为 $ |3 - 1| + |1 - 2| + |2 - 3| = 2 + 1 + 1 = 4 $ 。

给出 $ n $ 和 $ k $ . 询问是否存在一个长度为 $ n $ 的排列 $ p $ 的曼哈顿值为 $ k $ ，若存在，输出排列 $ p $ 。

## 样例 #1

### 输入

```
8
3 4
4 5
7 0
1 1000000000000
8 14
112 777
5 12
5 2```

### 输出

```
Yes
3 1 2
No
Yes
1 2 3 4 5 6 7
No
Yes
8 2 3 4 5 6 1 7
No
Yes
5 4 3 1 2
Yes
2 1 3 4 5```

# 题解

## 作者：szh_AK_all (赞：12)

### 分析
排列 $p$ 的哈曼顿值一定为偶数，为什么呢？注意，$|x|,x$ 的奇偶性是相同的，那么 $\sum_{i=1}^n |p_i-i|$ 的奇偶性与 $\sum_{i=1}^n p_i-i=\sum_{i=1}^n p_i-\sum_{i=1}^ni=0$ 的奇偶性也是相同的，所以排列 $p$ 的哈曼顿值一定为偶数。

也就是，当给出的 $k$ 为奇数或者超过排列 $p$ 的最大哈曼顿值时，便无解；否则，便考虑构造。

首先，令我们要得到的排列 $p$ 为单调递增的，也就是 $p_i=i(1\le i\le n)$，那么此时 $p$ 的哈曼顿值为 $0$。很明显，如果在此基础上交换两个数 $x,y$，那么 $p$ 的哈曼顿值便会增加 $2\times|x-y|$。也就是说，可以将一些数字两两配对，由于它们所产生的贡献值是互不干扰的，所以相当于是将 $\frac{k}{2}$ 拆分成若干个不超过 $n-1$，且互不相等的数的和。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		if (k % 2 == 1)
			cout << "No" << endl;
		else {
			int ans = 0;
			for (int i = 1, j = n; i <= n; i++, j--) {
				a[i] = i;
				ans += abs(j - i);
			}
			if (k > ans)
				cout << "No" << endl;
			else {
				int x = k / 2;
				for (int i = 1, j = min(x, n - 1);; i++) {
					swap(a[i], a[i + j]);
					x -= j;
					j = min(x, n - 2 * i - 1);
					if (!x)
						break;
				}
				cout << "Yes" << endl;
				for (int i = 1; i <= n; i++)
					cout << a[i] << " ";
				cout << endl;
			}
		}
	}
}
```

---

## 作者：int_R (赞：5)

首先 $k$ 是奇数无解，因为那个式子的值显然是偶数。

先猜一手上界是将 $p$ 降序排列，很有道理。

每次从 $1$ 开始扫到 $\lfloor \dfrac{n}{2}\rfloor$，不断交换 $i$ 与 $n-i+1$，得到的贡献是 $(n-i+1-i)\times 2$，最后也可以到达上界。

这样可能某一次操作产生的贡献大于当前所需要的值，但是 $[i,n-i+1]$ 中的数都是没有被操作的，可以直接交换 $i$ 与 $i+\dfrac{k}{2}$ 来得到想要的贡献（$k$ 是当前需要的贡献）。

```cpp
inline void work()
{
    cin>>n>>k;
    if(k&1){cout<<"No\n";return ;}
    for(int i=1;i<=n;++i) a[i]=i;
    for(int i=1;i<=n/2;++i)
    {
        ll now=min(k/2,(n-i+1-i));
        swap(a[i],a[i+now]),k-=now*2;
    }
    if(k){cout<<"No\n";return ;}
    cout<<"Yes\n";
    for(int i=1;i<=n;++i) cout<<a[i]<<' ';
    cout<<'\n';return ;
}
```

---

## 作者：BAKABAKABAKABAKA (赞：3)

给出一个莫名奇妙的构造。

先考虑最大合法的 $ k $，奇偶分讨一下，对于偶数，建立两个集合为小于等于 $ {n\over 2} $ 和大于的，两个集合相互对应。奇数类似，考虑将中间一个点孤立即可（这是显然的）。然后由于是排列，那么一定珂以通过多次或一次交换变换为其他排列，然后注意到交换一次后 $ |a_i - i|, |a_j - j| $ 要么奇偶性不变，要么全变。无论哪种，都不会改变和的奇偶。所以所有排列的曼哈顿值全为偶数。（当然珂以直接打表找规律，也是显然的。

然后你可以考虑在 $ k \ge 2(n-1) $ 的时候，将 $ p_1=n,p_n=1 $，然后对 $ [2, n-1] $ 进行构造 $ k - 2(n-1) $ 贡献。注意到 $ [2,n-1] $ 为连续一段区间，于是珂以递归 $ n - 2, k - 2(n-1) $ 进行构造。容易证明，只要 $ k $ 合法，这样就珂以构造出一种答案（因为对于 $ k $ 是成立的条件，并不存在下界，也就是说，若 $ n, k $ 有答案，则 $ n-2, k-2(n-1) $ 也一定有答案。因为这样对 $ p_1, p_n $ 是使答案最大的其中一中。或者从代数的角度，对奇偶分讨，然后珂以证明也是合法的，不在展开）。那么就考虑 $ k < 2(n-1) $ 的情况。

打表可得排列可为: $ 1\ \ 2\ \ \cdots\ \ n-{k\over2}-1\ \ n-{k\over2}+1\ \ n-{k\over2}+2\ \ \cdots\ \ n\ \ n-{k\over2} $。大致原因如下：前面 $ n-{k\over2}-1 $ 成一个曼哈顿值为 $ 0 $ 的排列，于是考虑将后面弄成长度为 $ l(l={k\over2}+1) $ 的新排列：$ 2\ \ 3\ \ \cdots\ \ l\ \ 1 $。显然答案为 $ 2(l-1)=k $。

总结一下，构造函数 $ \text{build}(n, l, r, k) $，表示构造长度为 $ n $ 的排列，放入答案数组的 $ [l, r] $中，曼哈顿值为 $ k $。

- $ k \ge 2(n-1) $，让 $ ans_l \Leftarrow n, ans_r \Leftarrow 1 $。并递归 $ \text{build}(n-2,l+1,r-1,k-2(n-1)) $。同时将 $ [l+1,r-1] $ 整体加 $ 1 $，差分即可。

- $ k < 2(n-1) $，按照如上方式构造即可。

窝还是太菜了，讲的这么啰嗦。

[Code & submission](https://codeforces.com/contest/1978/submission/266151566)（本人代码非常抽象，不喜勿喷）

---

## 作者：Fu_Da_Ying (赞：1)

## [原题链接](https://www.luogu.com.cn/problem/CF1978C)
## 题意：

设排列 $p$ 的曼哈顿值为 $ |p_1 - 1| + |p_2 - 2| + \cdot\cdot\cdot + |p_n - n| $。

给出 $n$ 和 $k$。询问是否存在一个长度为 $n$ 的排列 $p$ 的曼哈顿值为 $k$，若存在，输出排列 $p$。

## 思路：

设排列 $p$ 的曼哈顿值为 $l$。

先考虑 $l = 0$ 的情况，此时所有的 $p_i = i(1\le i\le n)$。但并不是所有的 $k = 0$，所以考虑其他情况。

容易想到使排列不变的方式是交换任意两个数，考虑交换 $p_i$ 和 $p_j(j>i)$ 且 $p_i=i,p_j=j$。那么会让 $l$ 增加 $2 \times(j-i)$。

据上面推出，$l$ 一定为偶数，那么当 $k$ 为奇数时，无解，可是还有一种无解的情况，即 $k$ 大于 $n$ 个数最大的 $l$ 时，无解。

那么如何去算 $n$ 个数最大的 $l$ 呢？我是递归的思想，将 $f_i(f_i$ 代表 $n$ 个数最大的 $l$，$i>1)$ 转化成 $2(x-1)+f_{x-2}$。证明：$f_i = 2 \times(x-1+x-3+\cdot\cdot\cdot+0)=2 \times(x-1)+f_{x-2}(i>1)$，这样就好做了。

可以的情况分两种：

1. $k$ 超过了现在最大数与最小数的差，则交换最大数和最小数，并将 $k$ 减去最大数与最小数的差。
2. $k$ 不超过了现在最大数与最小数的差，交换最小数和与最小数的差为 $k$ 的数。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,p[200015],ans;
long long d(long long x){//递归求n个数最大的曼哈顿值 
	if(x<=1){
		return 0;
	}
	return x*2-2+d(x-2);
}
int main(){
	scanf("%lld",&t);
	while(t--){
		ans=0;
		scanf("%lld %lld",&n,&k);
		for(int i=1;i<=n;i++){//初始化p数组 
			p[i]=i;
	    }
		if(k%2==1||k>d(n)){//如果k为奇数或超过了n个数最大的曼哈顿值时 
		    printf("No\n");//输出No 
			continue;
		}
		k/=2;
		for(int i=1;;i++){
			if(k>n-2*i+1){//如果k超过了现在最大数与最小数的差 
				swap(p[i],p[n-i+1]);//交换最大数和最小数
				k=k-n+2*i-1;//k减去最大数与最小数的差 
			}else{//反之 
				swap(p[i],p[i+k]);//交换最小数和与最小数的差为k的数 
				break;
			}
		}
		printf("Yes\n");
		for(int i=1;i<=n;i++){
			printf("%lld ",p[i]);
		}
		printf("\n");
	}
    return 0;

}
```

### [AC 记录](https://www.luogu.com.cn/record/169606018)

---

## 作者：Ghosty_Neutrino (赞：1)

### 题意

让我们把排列的曼哈顿值 $p$ 表示为 $|p_1-1|+|p_2-2|+...+|p_n-n|$ 的值。

例如，对于排列 $[1,2,3]$，曼哈顿值为 $|1-1|+|2-2|+|3-3|=0$，而对于排列 $[3,2,1]$，曼哈顿值为 $|3-1|+|1-2|+|2-3|=2+1+1=4$。

给出整数 $n$ 和 $k$。请找出长度为 $n$ 的排列 $p$ 使其曼哈顿值等于 $k$，或者确定不存在这样的排列。

长度为 $n$ 的排列是一个数组，由 $n$ 个不同的整数组成，这些整数从 $1$ 到 $n$ 按任意顺序排列。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是一个排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是一个排列，($n=3$，但数组中有 $4$)。

### 分析

首先我们可以发现，排列 $p$ 的哈曼顿值一定为偶数，不存在为奇数的情况。

因此无解的情况有两种：

$k$ 为奇数或超过排列 $p$ 的最大哈曼顿值。

对于有解的情况，考虑构造。

首先，令我们要得到的排列 $p$ 为单调递增的，也就是 $p_i=i$，那么此时 $p$ 的哈曼顿值为 $0$。很明显，如果在此基础上交换两个数 $x$ 和 $y$，那么 $p$ 的哈曼顿值便会增加 $2\times|x-y|$。也就是说，可以将一些数字两两配对，由于它们所产生的贡献值是互不干扰的，所以相当于是将 $\frac{k}{2}$ 拆分成若干个不超过 $n-1$，且互不相等的数的和。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=200010;
const LL MOD=998244353;
LL a[N];
void fun() {
    LL n,k;
    scanf("%lld%lld",&n,&k);
    if(k%2==1) printf("No\n");
    else {
        LL ans = 0;
        for(LL i=1,j=n;i<=n;i++,j--) {
            a[i]=i;
            ans+=abs(j-i);
        }
        if(k>ans) printf("No\n");
        else{
            LL x=k/2;
            for(LL i=1,j=min(x,n-1);;i++) {
                swap(a[i],a[i+j]);
                x-=j;
                j=min(x,n-2*i-1);
                if(!x) break;
            }
            printf("Yes\n");
            for(LL i=1;i<=n;i++)
                printf("%lld ",a[i]);
            printf("\n");
        }
    }
}

int main() {
    LL t;
    scanf("%lld",&t);
    while(t--)
        fun();
    return 0;
}

```

---

## 作者：Dtw_ (赞：1)

[cf](https://codeforces.com/contest/1978/problem/C)
# 题目大意

定义一个排列的值为 $\sum_{i=1}^{n} \left | p_i - i \right | $。给你 $n$ 和 $k$，问是否有长度为 $n$ 的排列 $p$ 满足他的值为 $k$。

# 思路
首先显然如果 $k$ 是奇数，那绝对不行，然后你可以算出这个排列可以得到的最大值，即倒着放，$p_1=n,p_2=n-1,\cdots,p_n=1$。然后只要在这个最大值之内的偶数全部都可以凑出来，可以自己推一推，就是相邻的两个可以凑出来一个 $2$，即 $p_i=i+1,p_{i+1}=i$，同理我距离为 $2$ 的可以凑出来 $4$ 即 $p_i = i+2, p_{i+2} = i$，然后后面的偶数以此类推。

那现在这个 $k$ 一定能凑出来，考虑每一位上放啥。

因为计算这个值的时候带着绝对值号，并且跟下标有关，容易想到这个值跟他数的大小无关，而是跟相对大小有关，所以我们可以考虑一个大的由许多小的拼接而来。

首先我们要凑这个 $k$ 我们一定是先用大的凑，在用小的凑，否则会出现超了的情况。

比如我要凑 $4$，先用小的会是这样凑：$2+4$ 而这样就超了，所以我们先用大的凑，凑不了在用小的凑。

关键在于凑的这个过程，按照从大到小凑，那什么时候是最大的呢？就是我首尾两个交换过来，设当前的左端点为 $l$，右端点为 $r$，即 $p_l=r,p_r=l$ 此时贡献是 $2\times \left | l-r \right |$，如果 $k$ 大于他，我们就把 $k$ 减去他，左右端点各向里移动，然后接着凑。否则不行，那我这位凑不了就不要了，那他的贡献是 $0$ 所以这个位置就放他自己，接着左端点或者是右端点向里移动一位接着凑。这里左右端点都一样，动哪个都行，因为我们只需要考虑他的相对位置。

然后这题就结束了。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int a[N];

signed main()
{
	fst; 
	int t;
	cin >> t;
	while(t--)
	{
		int n, k;
		cin >> n >> k;
		int j = n, res = 0;
		for(int i=1; i<=n; i++)
		{
			res += abs(i - j);
			j--;
		}
		if(res < k || k % 2)
		{
			cout << "No" << endl;
			continue;
		}
		int End = n, i = 1;
		while(i <= n)
		{
			if(k >= 2 * abs(n - i))
			{
				k -= 2 * abs(n - i);
				a[i] = n, a[n] = i;
				i++, n--;
			}
			else
			{
				a[n] = n;
				n--;
			}
		}
		cout << "Yes" << endl;
		for(int i=1; i<=End; i++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
	}
	return 0;
}




```

---

## 作者：Day_Tao (赞：1)

### 题目大意

构造一个排列 $p$，使得 $\sum\limits_{i=1}^n|p_i-i|=k$。

### Sol

先给出两个结论：

- $n,n-1,n-2\cdots 1$，即 $i$ 与 $n-i+1$ 是使得总贡献最大的排列。  
- 当 $k\bmod 2=0$ 时才可能存在解。

对于第一个结论的正确性很好证明，随便交换两个数之后总贡献不会增加。

对于第二个结论的正确性，要想使得 $k$ 为奇数，那么当且仅当有奇数个位置的 $p_i$ 与 $i$ 的奇偶性不同。若存在一个位置的奇偶性不同，则必定存在另一个位置的奇偶性不同，所以奇偶性不同的位置总是存在偶数个，故 $k$ 不能为奇数。

然后考虑如何做这个题。

先看结论一的排列，假设 $n=6$，可以得到：

```
排列：6 5 4 3 2 1
贡献：5 3 1 1 3 5
```

交换 $i$ 与 $n-i+1$ 的贡献之和分别是是 $10,6,2$，是一个公差为 $4$ 等差数列。发现如果是交换若干对，$i$ 从小到大进行尝试，并且 $k$ 不断减去相应的贡献，合法的排列只有最终 $k=2$ 的情况构造不出，例如原始的 $k=4,14$。对于这种情况需要加以特判，考虑怎么交换才能使得总贡献增加 $2$。显然，交换相邻的两个才有可能使贡献加 $2$。但是如果交换两个已经跟后面的数交换过的数，或者前面那个数已经交换过了，后面一个数等于下标，那么总贡献不变。这个容易证明。所以我们就要交换一个没交换过的数与其后面的一个数。

若 $n$ 为奇数情况差不多，就留给读者自己推导了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAX = 2e5 + 5;
int T, n, k, a[MAX];
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &k);
        // if (k % 2 == 1) 这里可以省略，因为若 k 为奇数则最终答案减不到 0
        // {
        //     puts("No");
        //     continue;
        // }
        int p = 0;
        for (int i = 1; i <= n / 2; i++) // 枚举 i 并尝试交换
            if (k >= (n - i + 1 - i) * 2)
                k -= (n - i + 1 - i) * 2, a[i] = n - i + 1, a[n - i + 1] = i;
            else
                a[i] = i, a[n - i + 1] = n - i + 1, p = i; // p 记录没被交换过的数
        if (n % 2 == 1) // 奇数特判
            a[n / 2 + 1] = n / 2 + 1;
        if (k == 2 && p != 0) // 存在没被交换过的数并且 k = 2
            swap(a[p], a[p + 1]), k = 0;
        if (k > 0)
        {
            puts("No");
            continue;
        }
        puts("Yes");
        for (int i = 1; i <= n; i++)
            printf("%lld ", a[i]);
        puts("");
    }
    return 0;
}
```
---

### END

---

## 作者：Phartial (赞：1)

**注意到**以下构造符合题意：

1. $k$ 为奇数或 $k>\lfloor\dfrac{n^2}{2}\rfloor$ 时无解；
2. 否则必然有解，将 $k$ 除以 $2$；
3. 对所有 $n-\lfloor\sqrt{k}\rfloor<i\le n$，取 $\displaystyle p_{i}=i-\left\lfloor\frac{k+n-i}{\lfloor\sqrt{k}\rfloor}\right\rfloor$；
4. 对所有 $1\le i\le n-\lfloor\sqrt{k}\rfloor$，将剩下的数按大小顺序依次填入 $p_i$。

证明：

以下默认令 $k$ 除以 $2$。

考虑按 $\lfloor\sqrt{k}\rfloor$ 对 $k$ 分类。

对于 $\sqrt{k}$ 是整数的情况，设 $k=a^2$，则对 $n-a<i\le n$，有 $p_i=i-a-\left\lfloor\dfrac{n-i}{a}\right\rfloor$，因为 $0\le n-i<a$，所以后面那一项为 $0$，$p_i=i-a$，贡献为 $a$；剩下的值为 $[1,n]\setminus(n-2a,n-a]$，顺序填入后 $1\le i\le n-2a$ 的 $p_i=i$，贡献为 $0$；$n-2a<i\le n-a$ 的 $p_i=i+a$，贡献为 $a$。于是总贡献为 $2a^2=2k$，正确。

然后对 $a^2+1\le k\le a^2+a$ 的情况，$\lfloor\sqrt{k}\rfloor=a$，对 $n-a<i\le n$，有 $p_i=i-a-\left\lfloor\dfrac{(k-1)\bmod a+n-i+1}{a}\right\rfloor$，因为 $1\le n-i+1\le a$，所以 $p_i=i-a-[(k-1)\bmod a+n-i+1\ge a]=i-a-[n-i+1\ge a-(k-1)\bmod a]$，感性理解一下这个东西，当 $k$ 从 $a^2+1$ 增大到 $a^2+a$ 时，这些 $p_i$ 会以 $i$ 从 $n-a+1$ 到 $n$ 依次减一，依次空出来 $n-2a+1$ 到 $n-a$ 里的每一个数并填到 $p_{n-2a}$ 里。前面的减一会贡献 $1$，$p_{n-2a}$ 的加一也会贡献 $1$，于是每次贡献 $2$，正确。

最后对 $a^2+a+1\le k\le a^2+2a$ 的情况，$\lfloor\sqrt{k}\rfloor=a$，对 $n-a<i\le n$，有 $p_i=i+a+1-\left\lfloor\dfrac{(k-1)\bmod a+n-i+1}{a}\right\rfloor$，后面的推理和 $a^2+1\le k\le a^2+a$ 是高度相似的，每次空出来的数会被填到 $p_{n-2a+1}$，于是贡献每次加 $2$，正确。

于是这就完成了证明。

```cpp
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int tt, n;
LL k;
bool v[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--;) {
    cin >> n >> k;
    if ((k & 1) || k > 1LL * n * n / 2) {
      cout << "No\n";
      continue;
    }
    k /= 2;
    fill_n(v + 1, n, 0);
    cout << "Yes\n";
    LL i = sqrt(k);
    for (int j = n - i + 1; j <= n; ++j) {
      v[j - (k - j + n) / i] = 1;
    }
    int t = 0;
    for (int j = 1; j <= n; ++j) {
      if (!v[j]) {
        cout << j << ' ';
      }
    }
    for (int j = n - i + 1; j <= n; ++j) {
      cout << j - (k - j + n) / i << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```

（Fun fact：答案的式子一开始是一坨大的，具体可以见 [link](https://codeforces.com/contest/1978/submission/266014457)。）

---

## 作者：Exp10re (赞：0)

VP 的时候用时 $C\geq F$。 

## 解题思路

显然的结论是 $k$ 为偶数或者很大则无解，此处的很大指有一个实际上界，但是~~我懒得算~~后面的操作过程中可以判断出来。

并且注意到 $p$ 单调递增时 $k$ 显然达到下界 $0$，单调递减时不难证明 $k$ 达到上界，我们只需要通过构造保证可以遍历上下界当中的每一个可能值即可。

考虑如下的构造：首先钦定左右指针 $L=1,R=n$。

- 若 $k\geq \frac {R-L+1} {2}$，那么交换 $p_L,p_R$，然后使 $k\leftarrow\frac {R-L+1} {2},L\leftarrow L+1,R\leftarrow R-1$。
- 若 $0\lt k\lt \frac {R-L+1} {2}$，那么遍历 $i\in[L+1,R-1]$，直到 $k= \frac {i-L+1} {2}$ 然后交换 $p_L,p_i$，找到了一个解，退出。
- 特殊的，若任意时刻 $k=0$ 则表明找到了一个解，退出；若任意时刻 $L\gt R$ 则无解。

其保证可以遍历上下界当中的每一个可能值，$L\gt R$ 的无解情况表明 $k$ 大于上界。

没细节，不放代码了。

---

