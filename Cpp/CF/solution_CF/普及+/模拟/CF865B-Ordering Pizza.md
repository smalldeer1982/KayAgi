# Ordering Pizza

## 题目描述

It's another Start\[c\]up finals, and that means there is pizza to order for the onsite contestants. There are only 2 types of pizza (obviously not, but let's just pretend for the sake of the problem), and all pizzas contain exactly $ S $ slices.

It is known that the $ i $ -th contestant will eat $ s_{i} $ slices of pizza, and gain $ a_{i} $ happiness for each slice of type 1 pizza they eat, and $ b_{i} $ happiness for each slice of type 2 pizza they eat. We can order any number of type 1 and type 2 pizzas, but we want to buy the minimum possible number of pizzas for all of the contestants to be able to eat their required number of slices. Given that restriction, what is the maximum possible total happiness that can be achieved?

## 说明/提示

In the first example, you only need to buy one pizza. If you buy a type 1 pizza, the total happiness will be $ 3·5+4·6+5·9=84 $ , and if you buy a type 2 pizza, the total happiness will be $ 3·7+4·7+5·5=74 $ .

## 样例 #1

### 输入

```
3 12
3 5 7
4 6 7
5 9 5
```

### 输出

```
84
```

## 样例 #2

### 输入

```
6 10
7 4 7
5 8 8
12 5 8
6 11 6
3 3 7
5 9 6
```

### 输出

```
314
```

# 题解

## 作者：蒟酱 (赞：2)

简要题意：有 $n$ 个人去披萨店吃披萨，有两种披萨，每个披萨有 $m$ 片。现在第 $i$ 个人要吃 $c_i$ 片披萨，如果吃一片第一种披萨会获得 $a_i$ 的幸运值，如果吃一片第二种披萨会获得 $b_i$ 的幸运值。现在需要购买最少数量的披萨使得每个人都吃饱并且所有人获得的幸运值之和最大。

贪心，如果一个人吃第一种披萨幸运值更高就让他只吃第一种披萨，吃第二种披萨幸运值更高就让他只吃第二种披萨，这样就能使幸运值之和最大了。  
不过有个问题，这样无法保证买最少的披萨。比如说一个披萨是 $5$ 片，第一种披萨买了 $6$ 片，第二种披萨买了 $7$ 片，总共买了 $4$ 个披萨，但实际上买 $3$ 个披萨就够了。把买第一种披萨比整个多出的数量记作 $s1$，买第二种披萨比整个多出的数量记作 $s2$，若 $s1+s2>m$，代表没办法买更少的披萨惹。  
否则按照吃两种披萨获得的幸运值之差从小到大排序，按照幸运值之差从小到大排序可以保证失去的幸运值最小，把多出来的那些减掉，也就是在吃第一种披萨中把 $s1$ 个人改成吃第二种披萨，或者在吃第二种披萨中把 $s2$ 个人改成吃第一种披萨，两种方案取更优的就行了。

代码：
```cpp
//不向焦虑与抑郁投降，这个世界终会有我们存在的地方。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define int loli
#define all(x) std::begin(x),std::end(x)
using std::cin;using std::cout;
using std::max;using std::min;
using loli=long long;
using pii=std::pair<int,int>;
int n,m,s1,s2,c1,c2,ans;;
std::vector<pii>b1,b2;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int c,a,b;n--;)if(cin>>c>>a>>b,a>b){
		ans+=a*c;
		b1.emplace_back(a-b,c);
		s1+=c;
	}else{
		ans+=b*c;
		b2.emplace_back(b-a,c);
		s2+=c;
	}
	s1%=m;s2%=m;
	if(s1+s2>m)return cout<<ans,0;
	sort(all(b1));
	sort(all(b2));
	for(auto[k1,k2]:b1){
		c1+=min(k2,s1)*k1;
		s1-=min(k2,s1);
		if(s1<=0)break;
	}
	for(auto[k1,k2]:b2){
		c2+=min(k2,s2)*k1;
		s2-=min(k2,s2);
		if(s2<=0)break;
	}
	cout<<ans-min(c1,c2);
	return 0;
}
```

---

## 作者：LJ07 (赞：0)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF865B)
## 思路简述

一道贪心题。

先让所有人买第一块披萨，再贪心地去选择剩下的人是否要改成买第二块披萨。

显然的，我们可以根据 $b_i-a_i$ 从大到小对每个人进行排序，然后次序每 $S$ 块披萨的去判断：如果对答案的贡献大于 $0$，就加入答案，否则就停止。

那如何保证购买最少份数的披萨呢？我们不妨搞出一个额外的人来**凑数**，使得 $\sum s_i$ 是 $S$ 的倍数即可。
## 丑陋の代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int frd() {
	char c;
	bool f(true);
	while (!isdigit(c = getchar())) f = c != '-';
	int x(c ^ 48);
	while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
	return f ? x : -x;
}
const int N(1e5 + 5);
int n, S, a[N + 5], b[N + 5], c[N + 5], p[N + 5], s[N + 5], ans, sum;
bool cmp(int q, int p) {return c[q] > c[p];}
signed main() {
	n = frd(), S = frd();
	for (int i(1); i <= n; ++i) 
		s[i] = frd(), a[i] = frd(), b[i] = frd(), p[i] = i, c[i] = b[i] - a[i];
	for (int i(1); i <= n; ++i) ans += a[i] * s[i], sum += s[i];
	s[0] = (S - sum % S) % S, sort(p, p + 1 + n, cmp);
	int cnt(0), tsum(0);
	for (int i(0); i <= n; ++i) {
		if (cnt + s[p[i]] >= S) {
			tsum += (S - cnt) * c[p[i]];
			if (tsum < 0) break;
			ans += tsum, s[p[i]] -= (S - cnt), tsum = 0;
			int temp((s[p[i]] / S) * S * c[p[i]]);
			if (temp < 0) break;
			ans += temp, tsum = (cnt = s[p[i]] % S) * c[p[i]];
		}else {
			tsum += s[p[i]] * c[p[i]], cnt += s[p[i]];
			if (tsum < 0) break;
		}
	}
	printf("%lld", ans);
    return 0;
}

```

---

