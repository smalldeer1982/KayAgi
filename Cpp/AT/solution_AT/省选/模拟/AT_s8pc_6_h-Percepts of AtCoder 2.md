# Percepts of AtCoder 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/s8pc-6/tasks/s8pc_6_h

E869120 は square1001 に、今年から $ Q $ 年間誕生日に数列をプレゼントすることにしました。  
 square1001 は、「プレゼントする数列の長さが短い方がよりコンパクトで良い」と言ったので、プレゼントする数列は出来るだけ短くしたいです。また、古から伝わる AtCoder 社の教えに基づいて、プレゼントする数列を決める必要があります。

AtCoder 社の教えとは、以下のようなものです。

- 数列の要素は全て **異なる**。
- プレゼントする数列に部分列として出現する数列のうち、単調増加列であるようなものの種類数はちょうど、聖なる数 $ K $ 個である。

ここで、数列 $ A\ =\ (A_1,\ A_2,\ ...,\ A_N) $ の「部分列」とは、$ A $ から $ 0 $ 個以上 $ N $ 個以下の値を消して、残った値の順序を変えずにできる数列のことです。  
 また、数列 $ A\ =\ (A_1,\ A_2,\ ...,\ A_N) $ が「単調増加列」である条件は、$ A_1\ <\ A_2\ <\ ...\ <\ A_N $ であることです。

例えば、$ A\ =\ (3,\ 4,\ 1,\ 2) $ の時、部分列として出現する「単調増加列」は $ (),\ (1),\ (2),\ (3),\ (4),\ (1,\ 2),\ (3,\ 4) $ の $ 7 $ 個です。

AtCoder 社では、毎年「聖なる数」が変わります。具体的には、$ i $ 年目の聖なる数は $ K_i $ です。  
 E869120 君のために、$ i $ 年目にプレゼントするべき数列を求めてください。

## 说明/提示

### 制約

- $ Q $ は $ 1 $ 以上 $ 1\ 000 $ 以下の整数
- $ K_i $ は $ 1 $ 以上 $ 5\ 000\ 000\ 000\ 000\ 000\ 000\ (=\ 5\ \times\ 10^{18}) $ 以下の整数

### 小課題・得点

1. (30 点)：$ K_i\ \leq\ 100 $ を満たす。
2. (70 点)：$ K_i\ \leq\ 1\ 500 $ を満たす。
3. (1400 点) : 追加の制約はない。

ただし、小課題 $ 3 $ について、以下のように得点が決定します。  
 ここでは、$ Q $ 年間における $ N $ の最大値を $ L $ とします。また、全てのテストケースにおける $ L $ の最大値を $ L' $ とします。

- $ 120\ \leq\ L'\ \leq\ 128 $ のとき、この小課題の得点は $ 125 $ 点
- $ 100\ \leq\ L'\ \leq\ 119 $ のとき、この小課題の得点は $ 1400\ \times\ 5^{-(L'\ -\ 99)\ /\ 20} $ 点
- $ 0\ \leq\ L'\ \leq\ 99 $ のとき、この小課題の得点は $ 1400 $ 点

### Sample Explanation 1

$ 1 $ 年目のプレゼントとして渡す数列は、$ (2,\ 3,\ 1) $ です。 この数列には、増加部分列が $ 5 $ 個あります。$ (),\ (1),\ (2),\ (3),\ (2,\ 3) $ です。

## 样例 #1

### 输入

```
2
5
10```

### 输出

```
3 2 3 1
6 8 6 9 1 2 0```

## 样例 #2

### 输入

```
3
20
100
869120```

### 输出

```
9 9 7 3 6 5 8 4 1 2
10 0 5 9 3 6 1 4 2 7 8
72 47 45 28 9 41 50 33 61 27 15 38 54 52 22 57 7 30 12 46 21 19 8 71 20 23 6 18 26 17 39 4 53 44 3 31 68 29 42 62 37 69 67 40 65 2 55 36 35 11 49 24 25 43 48 0 1 16 10 70 66 64 32 5 51 60 63 58 56 59 13 14 34```

# 题解

## 作者：DengDuck (赞：3)

我的做法是 [APIO2022 排列](https://www.luogu.com.cn/problem/P8376) 的 91 分做法，这道题还是可以过的。

我们考虑在 $n-1$ 排列下将 $n$ 插入在最前面或者最后面。

设原先的序列有 $k$ 个上升子序列。

- 若插入在最前面，只会增加一个由其自身组成的上升子序列，$k\gets k+1$。

- 若插入在最后面，之前所有的上升子序列都可以把 $n$ 作为末尾扩展，上升子序列的数量刚好翻倍，$k\gets 2k$。

我们考虑将题目给出的 $k$ 二进制拆分，则末尾为 $1$ 选择第一种方案，否则选择第二种方案。

可以考虑递归求解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long 
LL n,x,cnt;
vector<int>ans;
void solve(LL x)
{
	if(x==1)return;
	if(x&1)solve(x-1),ans.insert(ans.begin(),++cnt);
	else solve(x/2),ans.push_back(++cnt);
}
std::vector<int> construct_permutation(LL k)
{
	ans.clear();
	cnt=0;
	solve(k);
	return ans;
}
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>x;
		vector<int>p=construct_permutation(x);
		cout<<cnt<<' ';
		for(auto i:p)
		{
			cout<<i<<' ';
		}
		cout<<endl; 
	}
}
```

---

## 作者：淸梣ling (赞：3)

考虑构造，假设已经加进去了 $1$ 到 $n-1$，考虑加入 $n$ 能产生的贡献。

如果放在最前面，那么只新加了选他自己的 $1$ 种方案。

如果放在最后面，那么就是原来的方案数乘以 $2$，那么二进制拆分即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> q;
int cnt;
void solve(long long n)
{
    if(n==1) return;
    else if(n&1) solve(n-1), q.push_front(++cnt);
    else solve(n>>1), q.push_back(++cnt);
}
int main()
{
    int t;
    cin>>t;
    while(t-->0)
    {
        long long n; cnt=0; q.clear();
        scanf("%lld", &n);
        solve(n);
        cout<<cnt<<" ";
        for(int x : q) printf("%d ", x);
        putchar('\n');
    }
    return 0;
}
```



---

## 作者：Purslane (赞：0)

# Solution

一种显然的想法：将最大数放在序列最前面可以将 IS 个数 $+1$，放在最后面可以 $\times 2$。

这样过不去，最坏情况需要 $2 \log_2 V$ 次。

考虑合并两次 $+1$ 的操作，也就是能不能 $+3$。

发现只要整个序列最前面两个数是递减的，把最大数插到第三个位置就可以 $+3$。

而只要最初由两个递减的数，就永远不会被破坏（即，不会在开头出现递增的结构）

因此我们在 $k \le 4$ 的时候暴力，其他情况递归处理掉后缀的一个或两个 $1$ 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int T;
vector<int> construct_permutation(ll k) {
	if(k<=4) {
		vector<int> ans;
		ffor(i,1,k-1) ans.push_back(k-i);
		return ans;	
	}
	vector<int> ans;
	if(k%2==0) ans=construct_permutation(k/2),ans.push_back(ans.size()+1);
	else if(k%4==1) ans=construct_permutation(k-1),ans.insert(ans.begin(),ans.size()+1);
	else ans=construct_permutation(k-3),ans.insert(ans.begin()+2,ans.size()+1);
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		ll k;
		cin>>k;
		auto ans=construct_permutation(k);
		cout<<ans.size()<<' ';
		for(auto id:ans) cout<<id<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：__Louis__ (赞：0)

### 题解：AT_s8pc_6_h Percepts of AtCoder 2

从 CF2032E 过来的，说一下方法。

### 思路

考虑二进制拆分，因为在每一个长度为 $n$ 的上升序列中都有 $2^n$ 个子序列。

那么第一种想法就是对于每一个二进制位都做一个上升序列，答案长度是 $\log^2 n$。不满足，考虑优化。

发现其实每一个序列可以合并，具体就是可以利用最长的上升序列中的前面部分，这样只需要 $1$ 的代价就可以加上某一个二进制位的贡献。

ex: 我们可以把 ${4567123}$ 变为 ${12354}$。

那么长度便是 $2\log n$，可以接受。

最后注意一下细节。

- 每一个数不相同，在编号的时候利用奇偶区分。
- 注意最大值，尽量开最大的。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
signed main(){
	int T;
	scanf("%llu",&T);
	while(T--){
		int n;
		scanf("%llu",&n);
		int i=1;
		vector<int> v;
		for(;i<64;i++){
			if((1ll<<i)<=n){
				v.push_back(2*i-1);
			}else{
				break;
			}
		}
		i--;
		n-=((1ll<<i));
		while(i>0){
			while(n>=(1ll<<(i-1))){
				v.push_back(2*(i-1));
				n-=(1ll<<(i-1));
			}
			i--;
		}
		int f=v.size();
		printf("%llu ",f);
		for(int i=0;i<v.size();i++){
			printf("%llu ",v[i]);
		}
		printf("\n");
	}
}
```

---

## 作者：phigy (赞：0)

我们考虑一位一位贪心的在不超过答案的情况下选择最大的数。

我们可以直接通过浮点数二分完成这个事情。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int T;
int n;
int f[3000005],cnt;
double a[3000005];
double b[3000005];
int x;
bool cmp(double A,double B) {return A<B;}

signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        for(i=1;i<=cnt;i++) {f[i]=a[i]=b[i]=0;}
        f[0]=1;
        a[0]=0;
        cin>>x;
        x--;
        cnt=0;
        while(x!=0)
        {
            cnt++;
            double L=0.1,R=10*cnt;
            int lst=0;
            while(R-L>0.1)
            {
                double mid=(L+R)/2;
                int sum=0;
                for(int i=0;i<=cnt;i++)
                {
                    if(a[i]<mid) {sum+=f[i];}
                }
                if(sum<=x) {L=mid;lst=sum;}
                else       {R=mid;}
            }
            f[cnt]=lst;
            a[cnt]=L;
            x-=lst;
        }
        for(i=1;i<=cnt;i++) {b[i]=a[i];}
        sort(b+1,b+cnt+1,cmp);
        cout<<cnt<<' ';
        for(i=1;i<=cnt;i++) {cout<<lower_bound(b+1,b+cnt+1,a[i])-b<<' ';} cout<<'\n';
    }

}
```

---

## 作者：Iniaugoty (赞：0)

一个平凡的思想是在已经排好 $ 1, 2, \sim n - 1 $ 的序列中添加一个 $ n $，计算这样做导致的上升子序列个数变化，然后考虑构造方式。有 $3$ 中添加方式：

1. 在开头添加 $ n $，上升子序列个数将增加 $ 1 $。

2. 在中间添加 $ n $，上升子序列个数将增加 $ n $ 前面的部分的上升子序列个数。这是难搞的。

3. 在末尾添加 $ n $，上升子序列个数将乘上 $ 2 $。

1 和 3 两种情况启发我们对 $ k $ 二进制分解，得到一个构造序列。

```cpp
for (; k > 1; k >>= 1) {
    if (k & 1) st[++tp] = 1;
    st[++tp] = 2;
}
reverse(st + 1, st + tp + 1);
// st 中，1 表示在开头添加 n，2 表示在末尾添加 n
```

然后从头扫一遍这个构造序列，用双端队列模拟一下就好了。

不难发现，构造序列的长度最大为 $2 \log _ 2 k$，而在题中这个范围下，这几乎就是 $n$ 的上界 $128$，所以这么构造是满足限制的。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 405;

int _, tp, st[N], l, r, ans[N]; LL k;

int main() {
    freopen("wmyr.in", "r", stdin);
    freopen("wmyr.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> _;
    while (_--) {
        cin >> k, tp = 0, l = 201, r = 200;
        for (; k > 1; k >>= 1) {
            if (k & 1) st[++tp] = 1;
            st[++tp] = 2;
        }
        reverse(st + 1, st + tp + 1);
        F(i, 1, tp)
            if (st[i] == 1) ans[--l] = i;
            else ans[++r] = i;
        cout << r - l + 1 << " ";
        F(i, l, r) cout << ans[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

