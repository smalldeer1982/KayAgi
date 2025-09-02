# Serval and Modulo

## 题目描述

给定一个由 $n$ 个非负整数组成的数组 $a$ 和一个魔法数 $k$（$k \ge 1$ 且为整数）。Serval 构造了另一个长度为 $n$ 的数组 $b$，其中对于所有 $1 \leq i \leq n$，满足 $b_i = a_i \bmod k^{\text{∗}}$。随后，他将 $b$ 打乱了顺序。

现在给定数组 $a$ 和 $b$，请找出一个可能的魔法数 $k$。如果 Serval 欺骗了你且这样的整数不存在，则输出 $-1$。

可以证明，在题目约束下，若这样的 $k$ 存在，则存在一个不超过 $10^9$ 的有效答案。你需要在输出中保证 $k \leq 10^9$。

$^{\text{∗}}$符号 $a_i \bmod k$ 表示 $a_i$ 除以 $k$ 的余数。

## 说明/提示

第一个测试案例中，若 $k \ge 3$，则 $2 = a_3 \bmod k$ 必须出现在数组 $b$ 中，但这会导致矛盾。当 $k = 1$ 时，$[a_1 \bmod k, a_2 \bmod k, a_3 \bmod k, a_4 \bmod k] = [0,0,0,0]$，无法通过打乱顺序得到 $b$。当 $k = 2$ 时，$[a_1 \bmod k, a_2 \bmod k, a_3 \bmod k, a_4 \bmod k] = [1,1,0,1]$，可以打乱为 $b$。因此唯一可能的答案是 $k = 2$。

第二个测试案例中，注意 $b$ 可以通过打乱 $a$ 直接得到。因此所有 $6$ 到 $10^9$ 的整数都是合法答案。

第三个测试案例中，可以证明这样的 $k$ 不存在。Serval 欺骗了你！

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4
3 5 2 7
0 1 1 1
5
3 1 5 2 4
1 2 3 4 5
6
2 3 4 7 8 9
1 2 3 6 7 8
5
21 22 25 28 20
0 1 2 1 0
6
1 1 2 3 5 8
0 0 1 1 0 0```

### 输出

```
2
31415926
-1
4
-1```

# 题解

## 作者：ZMQ_Ink6556 (赞：6)

## 题解：CF2085E Serval and Modulo

### 解题思路

以下两个数组相同表示两个数组排序后所有元素都能对应。

如果数组 $a$ 和数组 $b$ 相同，那么 $k$ 一定大于 $a$ 中的最大元素，直接输出一个极大值即可。

否则因为是取模，所以 $a$ 数组所有元素之和一定大于 $b$ 数组所有元素之和。

我们把取模运算看作是连续的减法，将 $a$ 数组中的元素连续减去 $k$，直到这个元素 $< k$。

由此可知，$a$ 数组所有元素之和与 $b$ 数组所有元素之和的差一定是 $k$ 的倍数。

枚举这个差的所有因数，然后暴力去 check 即可。

复杂度：$O(n \sqrt{\sum{a_i}} \log n)$。

虽然这个公式给出的运算量是 $2 \times 10^{11}$，但是能过，原因如下：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/eadj2ez8.png)

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
int t , n , a[10005] , b[10005] , c[10005] , sum;
bool flag;
inline bool same()
{
	for(int i = 1 ; i <= n ; i++)
	{
		if(a[i] != b[i])
		{
			return 0;
		}
	}
	return 1;
}
inline bool check(int q)
{
	for(int i = 1 ; i <= n ; i++)
	{
		c[i] = a[i] % q;
	}
	sort(c + 1 , c + n + 1);
	for(int i = 1 ; i <= n ; i++)
	{
		if(b[i] != c[i])
		{
			return 0;
		}
	}
	return 1;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> b[i];
		}
		sort(a + 1 , a + n + 1); 
		sort(b + 1 , b + n + 1);
		if(same())
		{
			cout << "999999999\n";
			continue; 
		}
		sum = 0;
		flag = 1;
		for(int i = 1 ; i <= n ; i++)
		{
			sum += a[i] - b[i];
		}
		for(int i = 1 ; i * i <= sum ; i++)
		{
			if(sum % i == 0)
			{
				if(check(i))
				{
					cout << i << '\n';
					flag = 0;
					break;
				}
				if(i * i < sum)
				{
					if(check(sum / i))
					{
						cout << sum / i << '\n';
						flag = 0;
						break;
					}
				}
			}
		}
		if(flag)
		{
			cout << "-1\n";
		}
	}
	return 0;
}
```

---

## 作者：WA_csp_noip (赞：3)

## 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF2085E)

[CF](https://codeforces.com/problemset/problem/2085/E)


## 解题思路

我们考虑先分别给数组 $a$ 和数组 $b$ 排个序，此时分两种情况讨论：

- $a$ 数组和 $b$ 数组一摸一样，这说明取模后和取模前一样，也就是说模数一定大于数组 $a$ 中的所有数，且 $a$ 中的最大值一定小于等于 $10^6$，所以直接输出 $10^9$ 一定是对的。

- $a$ 数组和 $b$ 数组不一样，那我们看一看取模的本质，对于 $a$ 数组，每个元素对 $k$ 取模后相当于减少了若干个 $k$。此时我们对 $a$ 和 $b$ 一一对应的去看，令 $p$ 为 $$\sum_{i=1}^{n} a_i - b_i$$，那么求出这个 $p$ 后，$k$ 一定是 $p$ 的因数，然后我们对于每个 $p$ 的因数暴力的去判断，最后不要忘了无解输出 `-1`。

时间复杂度 $O(n \sqrt{\sum_{i=1}^{n} a_i - b_i} \log n)$。

此时有人就会说了：啊，同学，你这个不是 $10^{10}$ 级别的吗，不会 `T` 飞吗？ 

但其实从 $1$ 到 $10^{10}$ 中的数的最多因子个数也就 $1344$ 个，不信你问 `deepseek`，那我们就可以把 $\sqrt{\sum_{i=1}^{n} a_i - b_i}$ 最多当作 $1344$ 就行了，于是我们就可以轻松过掉这题了。



## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[10001], b[10001], c[10001];

bool check(int k) {
    for (int i = 1; i <= n; i++)
		c[i] = a[i] % k;
	sort(c + 1, c + n + 1);
	for (int i = 1; i <= n; i++)
		if (b[i] != c[i])
			return 0;
	return 1;
}

int main() {
    int t;
    scanf("%d", &t);
    for (; t--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        long long sum = 0;
        bool ok = 1;
        for (int i = 1; i <= n; i++) {
            sum += a[i] - b[i];
            if (a[i] != b[i])
                ok = 0;
        }
        if (ok) {
            printf("%d\n", (int)1e9);
            continue;
        }
        ok = 0;
        for (int i = 1; 1LL * i * i <= sum; i++)
            if (!(sum % i)) {
                if (check(i)) {
                    printf("%d\n", i);
                    ok = 1;
                    break;
                }
                if (i * i != sum) {
                    if (check(sum / i)) {
                        printf("%d\n", sum / i);
                        ok = 1;
                        break;
                    }
                }
            }
        if (!ok)
            printf("-1\n");
    }
}
```

[提交记录](https://codeforces.com/problemset/submission/2085/314868057)。

---

#### 说句闲话
这题真的有蓝吗？

---

## 作者：A_R_O_N_A (赞：1)

## 题意

有两个长度为 $n$ 的序列 $a_1,a_2,a_3,\dots,a_n$ 和 $b_1,b_2,b_3,\dots,b_n$。现在有个小孩哥告诉你对于每一个 $1\le i\le n$ 都有 $a_i \bmod k=b_i$，但是小孩哥把 $b$ 序列给**打乱了**。你需要实现一个程序找出任意一个 $k$，只需要满足 $1\le k\le 10^9$ 就可以了。当然小孩哥可能在骗你，所以可能没有符合条件的 $k$，输出 `-1`。

数据范围：$1\le n\le 10^4,0\le a_i,b_i\le 10^6$。

## 思路

首先我们可以很清楚地知道 $a_i-b_i=x\times k$，其中 $x$ 是一个未知非负整数。然后你就可以很轻松地发现这个结论对于总和也是成立的，所以有 $\sum a-\sum b=x\times k$。然后你就又会发现这个 $x\times k$ 最多最多只有 $10^{10}$。那么对于每一个可能的 $k$，其一定是这个数的因数，然后这题就做完了。我们直接枚举因子，然后每次都暴力检查就好了，因为 $10^{10}$ 大小的数字的因子个数也就不到 $2500$，根号枚举是能过的，单组数据的时间复杂度是 $O(n\times d(\sum a)+\sqrt{\sum a})$，其中 $d(\sum a)$ 表示 $\sum a$ 的因子个数。实际上时间比较紧的是后面的那个根号，因为这是多测。算上多测的话是 $O(T\sqrt{\sum a})$。

检查的话开个桶就行了，把 $a_i \bmod k$ 的结果都放进去然后遍历 $b$ 序列，遇到桶里面有的数就减一，如果遇到没有的数或者说减成 $0$ 了就说明桶里面数字不够匹配不上。因为单个 $a_i$ 只有 $10^6$ 所以普通数组就够用。~~我才不会告诉你我偷懒用 `map` 被卡常了~~。

当然，如果 $\sum a-\sum b=0$ 就说明这两个序列要么完全相同要么匹配不上，用一个大数检查一遍就好了。


```cpp
#include<bits/extc++.h>
#include<bits/stdc++.h>
#define ll long long
using namespace std;
using namespace __gnu_pbds;
mt19937 myrand(time(0));
inline ll read(){
	ll x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*w;
}
void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	static int sta[35];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top)putchar(sta[--top]+'0');
}
int n,a[10005],b[10005];
ll suma,sumb,de;
gp_hash_table<int,int>mp;
bool check(int k){
	mp.clear();
	for(int i=1;i<=n;i++)mp[a[i]%k]++;
	for(int i=1;i<=n;i++){
		if(mp[b[i]]<=0)return 0;
		mp[b[i]]--;
	}
	return 1;
}
inline void work(){
	n=read();suma=0,sumb=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		suma+=a[i];
		sumb+=b[i];
	}
	if(suma==sumb){check(1919810)?puts("1919810"):puts("-1");return;}
	de=suma-sumb;
	for(int i=1;1ll*i*i<=de;i++){
		if(de%i==0){
			if(check(i)){
				write(i);puts("");
				return;
			}
			if(check(de/i)){
				write(de/i);puts("");
				return;
			}
		}
	}
	puts("-1");
}
int _;
int main(){
	_=read();
	while(_--)work();
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

## Solution

考虑 $b_i = a_i \bmod k$ 这一语句的性质。

很显然的 $a_i \equiv b_i \pmod k$，也就是说 $\Delta =  a_i - b_i$ 是 $k$ 的倍数，同理可得 $\Delta = \sum\limits_{i=1}^{n}{a_i} - \sum\limits_{i=1}^{n}{b_i}$ 也是 $k$ 的倍数，从这里入手。

有一个性质：记 $d_x$ 表示 $x$ 的因数个数，对于 $x \leq 10^{10}$ 都有 $d_x \leq 2304$。

也就说我们想要的 $k$，在 $\Delta \neq 0$ 的情况下要么是 $\Delta$ 的因数，要么是大于 $a_i$ 的一个数，那么我么就可以找 $\Delta$ 的因数，复杂度 $O(nd_{\sum{a_i}} + \sqrt{\sum{a_i}})$。

## Code
[Submission](https://codeforces.com/contest/2085/submission/312137787)

---

## 作者：ax_by_c (赞：0)

## Statement

有一个长度为 $n$ 的非负整数序列 $a$，小 S 选定了一个正整数 $k$，令 $b_i=a_i\bmod k$，然后将 $b$ 任意排列。

现在给你 $a,b$，你需要求出任意可能的 $k$ 或判定不存在合法的 $k$。

多测，$1\le t,\sum n\le 10^4,0\le a_i,b_i\le 10^6$。

## Solution

发现一个数取模前后的差一定是 $k$ 的倍数，所以序列和的差也是 $k$ 的倍数。

令序列和的差为 $sum$，则有 $k\mid sum$。

- $sum<0$

  显然无解。
  
- $sum=0$

  只可能是打乱了序列，用各种手段判一下即可，此时 $k$ 可取 $1000001$。

- $sum>0$

  因为 $sum\le 10^{10}$，所以 $d(sum)\le 2304$。

  直接枚举 $k\mid sum$，用各种手段判一下即可。

时间复杂度 $O(\sqrt{sum}+nd(sum))$。


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef unsigned long long ull;
typedef long long ll;
const int N=1e4+5;
const int V=1e6+5;
mt19937 Brnd(time(0));
set<ull>S;
ull getrnd(){
	ull res=Brnd();
	while(S.count(res))res=Brnd();
	S.insert(res);
	return res;
}
ull f[V];
int n,a[N],b[N];
ll sum;
bool check(int x){
	ull xs=0;
	for(int i=1;i<=n;i++)xs+=f[a[i]%x];
	for(int i=1;i<=n;i++)xs-=f[b[i]];
	return !xs;
}
void slv(){
	scanf("%d",&n);sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),sum-=b[i];
	if(sum<0){
		puts("-1");
		return ;
	}
	if(check(1000001)){
		puts("1000001");
		return ;
	}
	if(!sum){
		puts("-1");
		return ;
	}
	for(ll i=1;i*i<=sum;i++){
		if(sum%i==0){
			if(check(i)){
				printf("%lld\n",i);
				return ;
			}
			if(check(sum/i)){
				printf("%lld\n",sum/i);
				return ;
			}
		}
	}
	puts("-1");
}
void main(){
	for(int i=0;i<=1000000;i++)f[i]=getrnd();
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

