# Magic Triples (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, $ a_i \le 10^6 $ .

For a given sequence of $ n $ integers $ a $ , a triple $ (i, j, k) $ is called magic if:

- $ 1 \le i, j, k \le n $ .
- $ i $ , $ j $ , $ k $ are pairwise distinct.
- there exists a positive integer $ b $ such that $ a_i \cdot b = a_j $ and $ a_j \cdot b = a_k $ .

Kolya received a sequence of integers $ a $ as a gift and now wants to count the number of magic triples for it. Help him with this task!

Note that there are no constraints on the order of integers $ i $ , $ j $ and $ k $ .

## 说明/提示

In the first example, there are $ 6 $ magic triples for the sequence $ a $ — $ (2, 3, 5) $ , $ (2, 5, 3) $ , $ (3, 2, 5) $ , $ (3, 5, 2) $ , $ (5, 2, 3) $ , $ (5, 3, 2) $ .

In the second example, there is a single magic triple for the sequence $ a $ — $ (2, 1, 3) $ .

## 样例 #1

### 输入

```
7
5
1 7 7 2 7
3
6 2 18
9
1 2 3 4 5 6 7 8 9
4
1000 993 986 179
7
1 10 100 1000 10000 100000 1000000
8
1 1 2 2 4 4 8 8
9
1 1 1 2 2 2 4 4 4```

### 输出

```
6
1
3
0
9
16
45```

# 题解

## 作者：FFTotoro (赞：7)

本题可以使用 STL `std::map` 解决。

记 $x$ 出现的次数为 $c_x$。考虑先枚举等比三元组中最大的数 $x$，然后枚举等比三元组的共公比 $b$，如果 $b^2|x$，根据乘法原理，答案即为 $c_{x/b^2}\cdot c_{x/b}\cdot c_x$。另外记得特判三元组中 $3$ 个数相等的情况。时间复杂度 $O(n\sqrt{\max\{a_i\}})$。

注意到 Easy Version 中 $a_i$ 的值域很小，只有 $[1,10^6]$；所以 $b$ 的大小是 $\sqrt{\max\{a_i\}}$ 级别的，最大仅有 $10^3$，该做法可以通过题目。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 开 long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,c=0; cin>>n;
    map<int,int> m;
    for(int i=1;i<=n;i++){
      int x; cin>>x; m[x]++; // 统计次数
    }
    for(auto [a,f]:m){
      for(int i=2;i<=1000;i++)
        if(!(a%(i*i)))c+=m[a]*m[a/i]*m[a/(i*i)];
      c+=f*(f-1)*(f-2); // 记得相同的情况
    }
    cout<<c<<endl;
  }
  return 0;
}
```

---

## 作者：Xiphi (赞：1)

### CF1822G1

考虑先枚举 $b$，再枚举合法的 $a_j$，然后开个桶子，用 $box$ 数组记录每个 $a_i$ 出现次数。对于每个 $a_j$，其对答案的贡献为 $box_{a_j/b} \times box_{a_j} \times box_{a_j\times b}$。复杂度是调和级数。特别的，当 $b$ 为 $1$ 时，且 $box_{a_j}\geq 3$ 的情况下，贡献为 $(box_{a_j}-1)\times box_{a_j} \times (box_{a_j}-2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int a[200005],box[1000005],maxn;
long long lastans=0;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		maxn=0;
		int flag=1;
		for(int i=1;i<=n;++i){
			int t=a[i];
			cin>>a[i];
			if(t!=a[i]) flag=0;
			box[a[i]]++;maxn=max(maxn,a[i]);
		}
		if(flag){
			cout<<lastans<<'\n';continue;
		}
		long long ans=0;
		for(int i=1;i<=maxn;++i){
			for(long long j=i;j*i<=maxn;j+=i){
				long long eps=box[j/i];
				if(box[j/i]>0) box[j/i]--;
				else{
					continue;
				}
				eps*=box[j];
				if(box[j]>0) box[j]--;
				else {
					box[j/i]++;
					continue;
				}
				eps*=box[j*i];
				box[j]++;
				box[j/i]++;
				ans+=eps;
			}
		}
		for(int i=1;i<=n;++i) box[a[i]]--;
		lastans=ans;
		cout<<ans<<'\n';
	}
	return 0;
} 	 	

```

### CF1822G2

G2 做法很妙，考虑根号分治，对于一个 $a_i$，若其 $\le 10^6$，则枚举 $1-\sqrt a_i$（这里枚举的是 $b$），否则枚举 $a_i$ 的倍数，这里枚举的是 $a_j$。这样就可以保证复杂度在根号以内。

---

## 作者：Hisaishi_Kanade (赞：1)

我们显然可以枚举 $a_j$ 和 $b$，由此 $a_i\gets \dfrac {a_j} b,a_k\gets {a_j}\cdot b$。

因为 $a_i\in\mathbb N$ 所以 $b\mid a_j$。

那么对 $a_j$ 分解即可。复杂度 $O(n\sqrt V)$。

注意特判 $b=1$ 的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
int n, i, j, t, x;
using ll=long long;
map<ll, ll> q;
ll va, ti;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		q.clear();
		scanf("%d", &n);
		rep(i, 1, n)
		{
			scanf("%d", &x);
			++q[x];
		}
		ll ret=0;
		for(auto& nxt : q)
		{
			va=nxt.first; ti=nxt.second;
			ret+=ti*(ti-1)*(ti-2);
			for(j=1; j*j<va; ++j)
			{
				if(j!=1 && va%j==0 && q.count(va/j) && q.count(va*j))
					ret+=q[va/j]*ti*q[va*j];
				if(va%j==0 && q.count(j) && q.count(va/j*va))
					ret+=q[j]*ti*q[va/j*va];
			}
			if(j!=1 && j*j==va && q.count(j) && q.count(va*j)) ret+=q[j]*ti*q[va*j];
		}
		printf("%lld\n", ret);
	}
}
```

---

## 作者：Erica_N_Contina (赞：0)

## EV

下文中 $V$ 为 $a_i$ 的最大值。

我们对于每个值 $i\in[1,V]$ 都记录其在 $a$ 中出现的次数 $cnt_i$，这个我们可以用 `map` 来实现。

因为我们的 $n$ 和 $V$ 都不大，我们可以枚举 $a_j$ 是哪一个值，然后再去枚举 $b$ 的值。因为题目要求 $a_i \times b=a_j$，$a_i$ 是整数，所以我们的 $b$ 一定是 $a_j$ 的因子，故我们只需要枚举 $a_j$ 的因子即可。又因为 $V$ 比较小，所以 $a_j$ 的因子个数也在可以枚举的范围之内。

枚举一个 $a_j$ 的因子（不一定是质因子哦）的复杂度是 $\sqrt{V}$ 的，所以总的复杂度是 $O(n\sqrt V)$ 的，可过简单版。


## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
const int E=1e6;
const int M=1e9;

#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}


int n,K,m;
int a[N],stk[N],top,T;
map<int,int>cnt;
int ans;

int prime[E],notprime[E],tot;

void init(){
	cnt.clear();
}

void solve(){
	for(auto &t : cnt){
        int val=t.first,cntt=t.second;
        {
			int j;
            for(j=1; j*j<val; ++j){
                if(j!=1 && val%j==0 && cnt.count(val/j) && cnt.count(val*j))
                    ans+=cnt[val/j]*cntt*cnt[val*j];
                if(val%j==0 && cnt.count(j) && cnt.count(val/j*val))
                    ans+=cnt[j]*cntt*cnt[val/j*val];
            }
            if(j!=1 && j*j==val && cnt.count(j) && cnt.count(val*j)) ans+=cnt[j]*cntt*cnt[val*j];
            
        }
    }
}

signed main() {
	
	T=rd;
	while(T--){
		n=rd;
		init();
		ans=0;
		for(int i=1;i<=n;i++){
			a[i]=rd;
			cnt[a[i]]++;
		}
		solve();
		cout<<ans<<endl;
	}

	return 0;
}

```


注意，如果我们用 `unordered_map` 是会 TLE 的。



---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1822G1) & [CF 传送门](//codeforces.com/problemset/problem/1822/G1)
# 思路
这题我们可以定义一个 STL 中的 map，$mp_i$ 表示数字 $i$ 出现的次数。如果 $i$ 是任意一个数 $b$ 的平方 $b^2$ 的倍数（$b\ge2$），那 $i$、$\frac ib$、$\frac i{b^2}$ 这 $3$ 个数能组成 $mp_i\times mp_\frac ib\times mp_\frac i{b^2}$ 组数。还有一种情况，就是在 $mp_i\ge3$ 时，$i$、$i$、$i$ 这三个数可以组成 $mp_i\times(mp_i-1)\times(mp_i-2)$ 组数。
# 注意事项
记得开 long long！
# 代码
```cpp
//CF1822G1
# include <bits/stdc++.h> //万能头 
typedef long long ll;
using namespace std;
ll t, n, x, sum;
map <ll, ll> mp;
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法
		cin >> n;
		mp.clear (), sum = 0; //多组数据要清空
		while (n --) {
			cin >> x;
			++ mp[x];
		}
		for (auto i = mp.begin (); i != mp.end (); ++ i) { //map 的遍历方式
			sum += i->second * (i->second - 1) * (i->second - 2); //b=1 的情况
			for (int j = 2; j * j <= i->first; ++ j) //枚举到根号就够了
				if (! (i->first % (j * j))) //能整除
					sum += i->second * mp[i->first / j] * mp[i->first / j / j];
		}
		cout << sum << '\n';
	}
	return 0; //结束程序
}
```

---

