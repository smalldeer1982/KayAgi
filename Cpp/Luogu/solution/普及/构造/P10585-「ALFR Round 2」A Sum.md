# 「ALFR Round 2」A Sum

## 题目描述

给定三个整数 $n,p,q$，你需要构造一个 $n$ 个数的序列 $a$，满足：

- $\forall 1\leq i\leq n:1 \leq a_i\leq 10^7,a_i\in\mathbb{Z}$；

- $(\sum\limits_{1\leq i<j\leq n}[a_i+a_j\leq q])=p$。

通俗地说，每个数都是正整数且在 $[1, 10^7]$ 之间，且这 $n$ 个数无序选两个不同位置的数构成的 $\dfrac{n(n-1)}{2}$ 个加和中有恰好 $p$ 个和不大于 $q$。你只需要给出一种方案即可。

## 说明/提示

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $p=0$ |
| $1$ | $80$ | - |

对于 $100\%$ 的数据，$4\leq n\leq10^6$，$0\leq p\leq\dfrac{n(n-1)}{2}$，$4\leq q\leq10^7$。

Update 2024.7.1：根据[此贴](https://www.luogu.com.cn/discuss/836854)添加了一组 hack 数据进入子任务 $2$，分数为 $0$ 分。

## 样例 #1

### 输入

```
4 2 5```

### 输出

```
1 3 4 15```

# 题解

## 作者：fish_love_cat (赞：4)

好玩的构造题！

---

设 $c,z,s,b,x,h$ 分别为序列 $a$ 中某个子串 $t$ 中第一大的值，第二大的值，长度，贡献，第二小的值和第一小的值。

依题意得：

当 $c+z\le q$ 时，则有 $b=\frac{s^2-s}{2}$。

当 $x+h>q$ 时，则有 $b=0$。

---

根据上面的条件可知：

当存在一个正整数 $i$ 满足 $p=\frac{i^2-i}{2}$ 时，则有关于序列 $a$ 的 $c,z$ 满足 $c+z\le q$。（情况一）

否则，必存在一个正整数 $i$ 满足 $\frac{i^2-i}{2}<p<\frac{i^2+i}{2}$。（情况二）

---

考虑对两种情况分别进行构造。

---

情况一：

我们可以构造出一个长度为 $i$ 且满足关于该序列的 $c,z$ 有 $c+z\le q$ 的序列 $a_1$，然后再构造出一个长度为 $n-i$ 且满足关于该序列的 $x,h$ 有 $x+h> q$ 的序列 $a_2$。将这两个数列的元素放在一起，就构造出了合法的序列 $a$。

因为题目保证 $p\le \frac{n(n-1)}{2}$，所以一定可以构造出这样的合法序列 $a$。

---

情况二：

因为有 $p=\frac{i^2-i}{2}+(p-\frac{i^2-i}{2})$，所以我们不妨将贡献拆成 $\frac{i^2-i}{2}$ 和 $p-\frac{i^2-i}{2}$ 两部分来分别构造。

显然 $\frac{i^2-i}{2}$ 的那部分可以用类似情况一的方式构造出一个长为 $i$ 的序列 $a_1$。

注意到，$i> p-\frac{i^2-i}{2}$。

设 $k,l$ 均为正整数。 

所以我们可以构造一个数字为 $q-l$，并将 $a_1$ 在保持它仍合法的情况下，将里面的数字设为若干个 $l$ 和若干个 $l+k$。**注意要求合法，即不违反情况一中对 $a_1$ 的定义。**

再设 $j$ 是当前 $a_1$ 中元素 $l$ 的个数。

显然的，修改后的贡献会在之前的基础上加上 $j$。

我们通过构造使 $j=p-\frac{i^2-i}{2}$ 即可。

剩下的，用类似情况一的方式构造一个长为 $n-i-1$ 的 $a_2$。

将这两个数列的元素**和 $q-l$** 放在一起，就构造出了合法的序列 $a$。

---

关于情况二中 $i\ge p-\frac{i^2-i}{2}$ 的证明：

$$\frac{i^2+i}{2}> p$$

$$i+\frac{i^2-i}{2}> p$$

$$i> p-\frac{i^2-i}{2}$$

证毕。

---

然后就可以开始愉快的构造了。

其实下面已经不重要了，看着上面相信大家都能构造出来对叭。

但还是介绍一下我的方法：

首先，$O(n)$ 跑一遍暴力求 $i$。

令 $k=l=1$，对于情况一中 $a_1$ 的构造，令元素全部为 $1$ 即可，而 $a_2$ 的构造，官解是全部 $10^7$，我是全 $q$，都能过的。

代码看不看其实无所谓吧。

懒得放了，注意求 $i$ 的时候跑不到 $n+1$ 可能会死在 #1。

做完了。[提交记录。](https://www.luogu.com.cn/record/list?pid=P10585&user=754021&page=1)

---

后话：

不知道怎么搞的，老是想到一些情况二的构造无法胜任的情况。不过按理来说能让情况二构造出锅的数据都会被情况一构造掉吧，所以大抵是 hack 不掉的。

至少现在看解法没什么问题。

~~至少我自以为的证伪 hack 居然都满足情况一，很神奇，欢迎 hack（~~

---

## 作者：happybob (赞：3)

当 $p=0$ 时，全部输出 $10^7$ 即可。

对于 $p \neq 0$：

我们令 $c_i = \dbinom{i}{2} = \dfrac{i \times (i-1)}{2}$。

若存在 $c_i = p$，则我们将前 $i$ 个输出 $1$，后 $n-i$ 个输出 $10^7$ 即可。

否则我们找到 $i$ 满足 $c_i > p$ 且 $c_{i-1} < p$。则答案序列为 $q-1,\underbrace{2,2,\cdots,2}_{c_i-p\text{个}},\underbrace{1,1,\cdots,1}_{i-c_i+p-1\text{个}},\underbrace{10^7,10^7,\cdots,10^7}_{n-i\text{个}}$。

可以发现 $q-1$ 可以与 $i-c_i+p-1$ 个 $1$ 搭配，对答案贡献 $i-c_i+p-1$。接着 $i-1$ 个数都是 $2$ 或 $1$，由于 $q \geq 4$，所以都可以搭配，有 $\dbinom{i-1}{2} = \dfrac{(i-1) \times (i-2)}{2}=c_{i-1}$ 的贡献，$q-1$ 与 $2$ 无法搭配，所以没有贡献。

于是总共的数量为 $i-c_i+p-1 + c_{i-1}$。

而 $\begin{aligned} &\; \; \; \; \; c_{i-1}-c_i+i-1 \\ &= \dfrac{(i-1) \times (i-2)}{2} - \dfrac{i \times (i-1)}{2} + i - 1 \\&= -\dfrac{(i-1)\times 2}{2} + i - 1 \\ &= -i+1+i-1 \\&= 0\end{aligned}$。

所以原式 $=p$，就做完了！

---

## 作者：bsjsaikou10 (赞：2)

# P10585 A Sum

## 题意：

给定你三个整数 $n, p, q$，让你输出一个长度为 $n$ 的序列 $a$，使得对于每个 $a_i$，都有 $1 \le a_i \le 10^7$，且在这个序列中无序地选两个不同位置的数，其加和不大于 $q$ 的数有 $p$ 个。

## Solution:

考虑构造，我们考虑这样一种构造：$\frac{q}{2}, \frac{q}{2}, \frac{q}{2}, \frac{q}{2}, \frac{q}{2}, \ldots$。我们发现，假如有 $k$ 个 $\frac{q}{2}$，那么这一段的贡献为 $\frac{k \times (k - 1)}{2}$。所以我们很容易想到，对于序列 $a$ 的构造，我们可以先用 $k$ 个 $\frac{q}{2}$，来尽可能地填满 $p$。那么这里我们可以列一个方程：$p = \frac{k \times (k - 1)}{2}$。整理一下可以得 $k^2 - k - 2p = 0$。我们发现这是一个一元二次方程的形式，根据一元二次方程的求根公式得 $k_1 = \frac{1 + \sqrt{1 + 8p}}{2}, k_2 = \frac{1 - \sqrt{1 + 8p}}{2}$。因为 $p \ge 4$，所以只有 $k_1$ 符合条件。

有了上面的推导后，我们可以直接处理第一种特殊情况：若 $p = \frac{n \times (n - 1)}{2}$，那么根据上面的结论，直接输入 $n$ 个 $\frac{q}{2}$ 即可。

特殊情况二：上文求出来的 $k_1$ 为整数

若 $k_1$ 为整数，则说明我们填 $k_1$ 个 $\frac{q}{2}$ 就可以满足题目的要求。这里有个问题，若 $k_1 \le n$ 怎么办？显然我们可以在填完 $k_1$ 个数之后，剩下的数全部填 $q + 1$。这样我们整个序列的贡献还是由这 $k_1$ 个数提供的。

好了，我们现在解决了上面两种特殊情况，现在只剩下 $k_1$ 不为整数的情况。

如果 $k_1$ 不为整数，因为我们填数时是按整数处理的，所以我们最后求出的应该是 $k_1' = \lfloor \frac{1 + \sqrt{1 + 8p}}{2} \rfloor$，所以我们会有一部分没有考虑到。

我们现在考虑一个极其重要的结论。

考虑极端情况，我们发现我们下取整之后得到的 $k_1'$，最极端只会比 $k_1$ 少 $1$，所以我们考虑一下，我们把当 $k = k_1 - 1$ 时，这些数对序列的贡献是多少。

所以我们有这样一个式子 $p_1 = \frac{(k - 1) \times (k - 2)}{2}$，我们可以全部产生的贡献为 $p_2 = \frac{k \times (k - 1)}{2}$。我们将两式相减得到 $\Delta = k_1' - 1$。

这说明什么呢？

这说明我们对于下取整之后所丢掉的贡献最多为 $k_1' - 1$。

有了上面的结论，我们再考虑如下构造：

我们这里先考虑 $q$ 为偶数的情况。因为 $q$ 为偶数，所以可得 $\lfloor \frac{q}{2} \rfloor + \lfloor \frac{q}{2} \rfloor = q$，所以有 $\lfloor \frac{q}{2} \rfloor + \lfloor \frac{q}{2} \rfloor + 1 > q$。于是我们可以这样构造：

我们先将第一个数填为 $\frac{q}{2} - 1$，后面再填 $\delta$ 个 $\frac{q}{2} - 1$，然后再填 $k_1' - \delta - 1$ 个 $\frac{q}{2}$。然后因为 $k_1' < n$，所以我们最后再填一个 $\frac{q}{2} + 1$。我们发现这样之后不仅考虑到了 $k_1'$ 的贡献，也把我们下取整掉的贡献考虑到了。所以这样填完之后，根据第一种特殊情况，我们只需要把剩下的数全填 $q + 1$ 即可。

若 $q$ 为奇数呢？我们发现当 $q$ 为奇数时，$\lfloor \frac{q}{2} \rfloor + \lfloor \frac{q}{2} \rfloor + 1 = q$，所以我们只需要对于 $q$ 为偶数时的构造进行细微的改动即可。

至于如何改动，我们只需要把偶数时最后填的 $\frac{q}{2} + 1$ 改为 $\frac{q}{2} + 2$ 即可。

这样我们这道题就愉快地做完了。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, p, q;
bool check(){
    if((int)sqrt(1 + 8 * p) * (int)sqrt(1 + 8 * p) == 1 + 8 * p){
        if((int)(1 + sqrt(1 + 8 * p)) & 1){
            return 0;
        }
        else{
            return 1;
        }
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> p >> q;
    int temp = (1 + sqrt(1 + 8 * p)) / 2;
    if(2 * p == n * (n - 1)){
        for(int i = 1; i <= n; i++){
            cout << 1 << " ";
        }
        return 0;
    }
    if(check()){
        for(int i = 1; i <= min(temp, n); i++){
            cout << q / 2 << " ";
        }
        for(int i = temp + 1; i <= n; i++){
            cout << q + 1 << " ";
        }
        return 0;
    }
    else{
        if(p - temp * (temp - 1) / 2){
            if(q & 1){
                cout << q / 2 - 1 << " ";
                for(int i = 2; i <= temp - (p - temp * (temp - 1) / 2) + 1; i++){
                    cout << q / 2 << " ";
                }
                for(int i = 1; i < p - temp * (temp - 1) / 2; i++){
                    cout << q / 2 - 1 << " ";
                }
                int cnt = 1;
                cout << q / 2 + 2 << " ";
                cnt++;
                for(int i = temp + cnt; i <= n; i++){
                    cout << q + 1 << " ";
                }
                return 0;
            }
            cout << q / 2 - 1 << " ";
            for(int i = 2; i <= temp - (p - temp * (temp - 1) / 2) + 1; i++){
                cout << q / 2 << " ";
            }
            for(int i = 1; i < p - temp * (temp - 1) / 2; i++){
                cout << q / 2 - 1 << " ";
            }
            int cnt = 1;
            cout << q / 2 + 1 << " ";
            cnt++;
            for(int i = temp + cnt; i <= n; i++){
                cout << q + 1 << " ";
            }
            return 0;
        }
        else{
            for(int i = 1; i <= temp; i++){
                cout << p / 2 << " ";
            }
            for(int i = temp + 1; i <= n; i++){
                cout << p + 1 << " ";
            }
        }
    }
}
```

## 总结

不错的一道题，若写的有什么问题欢迎指出！

---

## 作者：Pursuewind (赞：2)

先考虑用 $x$ 个 $1$，$y$ 个 $q - 1$，凑出多少 $\le q$ 的数呢？是：

$$xy+\frac{x(x-1)}{2}$$
$$=xy+\frac{1}{2}(x^2-x)$$
$$=x(y+\frac{1}{2}x-\frac{1}{2})$$

个数，假设我们知道 $x$，解关于 $y$ 的方程即可：

$$x(y+\frac{1}{2}x-\frac{1}{2})=p$$
$$x(2y+x-1)=2p$$
$$\therefore x | 2p$$
$$2y=\frac{2p}{x}-x+1$$
$$y=\frac{\frac{2p}{x}-x+1}{2}$$

```cpp
for (int x = 1; x <= n; x ++){
	if (2 * p % x) continue;
	int y = (2 * p / x - x + 1) / 2;
	if (x * y + x * (x - 1) / 2 == p && x + y <= n){
		for (int j = 1; j <= x; j ++){
			cout << "1 ";
		}
		for (int j = 1; j <= y; j ++){
			cout << q - 1 << " ";
		}
		for (int j = 1; j <= n - x - y; j ++){
			cout << "10000000 ";
		}
		return 0;
	}
}
```

这样还不够，因为无法凑出所有 $p$ 来。

进一步考虑用 $x$ 个 $1$，$y$ 个 $2$，$z$ 个 $q-1$，凑出：。

$$xz+xy+\frac{x(x-1)}{2}+\frac{y(y-1)}{2}$$
$$=xy+xz+\frac{1}{2}(x^2-x+y^2-y)$$

个数，假设知道 $x,y$，解关于 $z$ 的方程：

$$xy+xz+\frac{1}{2}(x^2-x+y^2-y)=p$$
$$xz=p-xy-\frac{1}{2}(x^2-x+y^2-y)$$
$$z=\frac{2p-2xy-x^2+x-y^2+y}{2x}$$

枚举 $x,y$ 会超时，考虑优化：

我们知道 $2x|(2p-2xy-x^2+x-y^2+y)$，即

$$2x|(2p-x^2+x-y^2+y)$$

所以设 $y(y-1)=2xk+(2p \bmod 2x)-x(x-1)$

此时解一元二次方程，即 $y(y-1)=t$，$y=\frac{\sqrt{4t+1}+1}{2}$。枚举 $k$ 即可。

复杂度 $O(\frac{n}{1}+\frac{n}{2}+\dots+\frac{n}{n})=O(n \log n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int a[N];
signed main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	int n, p, q;
	cin >> n >> p >> q;
	for (int x = 1; x <= n; x ++){
		if (2 * p % x) continue;
		int y = (2 * p / x - x + 1) / 2;
		if (x * y + x * (x - 1) / 2 == p && x + y <= n){
			for (int j = 1; j <= x; j ++){
				cout << "1 ";
			}
			for (int j = 1; j <= y; j ++){
				cout << q - 1 << " ";
			}
			for (int j = 1; j <= n - x - y; j ++){
				cout << "10000000 ";
			}
			return 0;
		}
	}
	for (int x = 1; x <= n; x ++){
		for (int k = x * (x - 1) / (2 * x) - 1; ; k ++){
			int res = 2 * k * x + 2 * p % (2 * x) - x * (x - 1);
			if (res < 0) continue;
			if (res > n) break;
			int delta = res * 4 + 1; int s = sqrt(delta);
			if (s * s != delta) continue;
			int y = (s + 1) / 2;
          //以上用求根公式解出 y
			if ((2 * p - 2 * x * y - x * x + x - y * y + y) % (x * 2)) continue;
			int z = (2 * p - 2 * x * y - x * x + x - y * y + y) / (x * 2);
			if (x + y + z <= n && z >= 0){
				int tot = 0;
				for (int i = 1; i <= x; i ++){
					a[++ tot] = 1;
				}
				for (int i = 1; i <= y; i ++){
					a[++ tot] = 2;
				} 
				for (int i = 1; i <= z; i ++){
					a[++ tot] = q - 1;
				}
				for (int i = 1; i <= n - x - y - z; i ++){
					a[++ tot] = 10000000;
				}
				for (int i = 1; i <= tot; i ++){
					cout << a[i] << " ";
				}
				cout << "\n";
//				int cnt = 0;
//				for (int i = 1; i <= n; i ++){
//					for (int j = i + 1; j <= n; j ++){
//						if (a[i] + a[j] > q) break;
//						if (a[i] + a[j] <= q) cnt ++;
//					}
//				}
//				cout << cnt;
				return 0;
			}
		}
	}
	return 0;
} 
```

---

## 作者：WorldMachine (赞：2)

简单构造题。

注意到 $q\geq 4$，考虑只填 $1,2,q-1$ 这三种数。

首先找到最大的 $x$ 使得 $\dfrac{x(x-1)}{2}\leq p$，那么前 $x$ 个就都填上 $1$ 或 $2$，但是具体填多少个 $1$ 要后面决定。

设 $y=p-\dfrac{x(x-1)}{2}$，如果 $y=0$ 前面就可以随便填，后面也不用填 $q-1$；否则前面填 $y$ 个 $1$ 与 $x-y$ 个 $2$，然后是一个 $q-1$。注意为了让后面剩下的元素不产生贡献，剩下的元素全部填 $10^7$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, p, q, a[1000005];
signed main() {
	scanf("%lld%lld%lld", &n, &p, &q);
	for (int i = 1; i <= n; i++) a[i] = 1e7;
	int x = n;
	for (int i = 1; i <= n; i++) {
		if (i * (i - 1) / 2 > p) {
			x = i - 1;
			break;
		}
	}
	int y = p - x * (x - 1) / 2;
	for (int i = 1; i <= y; i++) a[i] = 1;
	for (int i = y + 1; i <= x; i++) a[i] = 2;
	if (y) a[x + 1] = q - 1;
	for (int i = 1; i <= n; i++) printf("%lld ", a[i]);
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

考虑寻找一个**最大的**数 $x$，使得 $\frac{x\times(x-1)}{2}\le p$。

另 $t=p-\frac{x\times(x-1)}{2}$。

显然 $t=0$ 时，可以用 $x$ 个 $1$ 和 $n-x$ 个 $q$ 来构造。

剩下的时候我们需要一个数可以和前面产生 $t$ 对数。

考虑前面的 $x$ 分为 $t,x-t$ 两部分，分别用 $1,2$（$q$ 最小是 $4$ 满足条件）。

然后再加上一个数：$q-1$，正好和 $t$ 个 $1$ 组成 $t$ 对。

剩下的无脑开大（$q\sim 10^7$ 都行）。

求 $x$ 的过程二分一下就行了，别忘了开 `long long`。

## 证明

首先根据求 $x$ 的步骤：不会出现超过 $n$（显然不足 $p$ 对的 $x$ 一定比 $n$ 小，否则肯定是比 $p$ 对多）。

考虑证明 $t\le x$。显然 $t>x$ 时，$x\gets x+1$ 只会增加 $x$ 对，所以这样的 $x$ 不是最大的，也就不存在（不符合定义）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=1e7+1;
int n,p,q,l=0,r=1e6,t,lft;
bool check(int x){
    return x*(x-1)/2<=p;
}
signed main(){
	cin>>n>>p>>q;
	while(l<r){
        int mid=(l+r+1)>>1;
        if(check(mid))
            l=mid;
        else
            r=mid-1;
	}//二分
	if((t=l*(l-1)/2)==p){
        for(int i=1;i<=l;i++)
            cout<<"1 ";
        for(int i=l+1;i<=n;i++)
            cout<<"10000000 ";
        return 0;
	}//运气好，直接来
	lft=p-t;
	for(int i=1;i<=lft;i++)
        cout<<"1 ";
    for(int i=lft+1;i<=l;i++)
        cout<<"2 ";//分开输出
    cout<<q-1<<' ';//补齐
    for(int i=l+2;i<=n;i++)
        cout<<"10000000 ";//无脑
	return 0;
}
```

---

## 作者：Andy1101 (赞：1)

# 思路
## 题目描述
题目要求输出任意一对长度为 $n$ 的序列，满足**恰好**有 $p$ 对数（两个不同位置的数）的和不大于 $q$。
## 做法

一开始，我就看到了 $q \ge 4$ 这个条件，意识到要填 $1$、$2$、$q-1$。

如果 $p = 0$，全都输出 $1 \times 10^7$ 即可。

首先我们要找一个最大的 $line$ 使得 $\dfrac{line(line - 1)}{2} \le p$，然后把 $1 \sim line$ 都赋值成 $1$。

但 $\dfrac{line \times (line-1)}{2}$ 不一定够 $p$，少了 $p- \dfrac{line \times (line-1)}{2}$ 个和，于是我们用一个 $more$ 变量存 $p- \dfrac{line \times (line-1)}{2}$，然后让 $a_{line+1}=q-1$，最后把多的 $more+1 \sim line$ 赋值为 $2$ 即可。

证明：我们的目的是利用 $a_{line+1}$ 多凑出几对，赋值为 $q-1$ 就是最好的选择，但这样会多出 $line-more$ 对，所以我们可以把 $more+1 \sim line$ 都赋值为 $2$（因为 $2+q-1$ 会超过 $q$）。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
const int P=1e7;
ll a[N];
int main()
{
	ll n,p,q;
	cin>>n>>p>>q;
	for(ll i=1;i<=n;i++) a[i]=P;
	if(p==0)
	{
		for(ll i=1;i<=n;i++) cout <<a[i]<<" ";
		return 0;
	}
	ll line=n;
	for(ll i=1;i<=n;i++)
	{
		if(i*(i-1)/2>p)
		{
			line=i-1;
			break;
		}
	}
	ll more=p-(line*(line-1)/2);
	for(ll i=1;i<=line;i++) a[i]=1;
	for(ll i=more+1;i<=line;i++) a[i]=2;
	a[line+1]=q-1;
	for(ll i=1;i<=n;i++) cout <<a[i]<<" ";
	return 0;
}

——————
拒绝抄袭，创建美好洛谷
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
题目说到要我们构造一个序列，又简单地看了数据范围，可以看出这是一道构造题。
## 2. 题目做法
### 部分分做法：
我们可以看到，第一个子任务的 $p$ 是等于零的。故我们要让任意两个数的和均大于 $q$，那么我们直接输出一个全为 $q$ 的序列就行了。这样就直接骗到部分分。
### 正确做法：
看数据范围，$q$ 是大于等于 $4$ 的，那么如果一个序列全为 $1$ 或 $2$，那么此序列任意两个数的和绝对不可能大于 $q$。先记住这个结论，后面有用。  
我们先创建一个用来表示序列的数组，再设立一个变量 $s$，用来记录现在有多少个数。我们先从下标 $1$ 开始，将序列中的此数设为 $1$，然后将 $s$ 加上下标减一，若 $s$ 小于等于 $p$，则继续，否则就将其此时加上的值减去，进入最后调整。  
我们将此下标的数的值赋为 $q - 1$，然后将 $1$ 到 $i - p + s - 1$ 的数赋为 $2$，将此下标之后的数全都赋值为 $q$，这样我们便可以保证此序列成立。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
inline long long read()
{
	long long x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
long long n,p,q,s,ed;//记得开long long 
int a[N];
int main()
{
	n=read(),p=read(),q=read();
	for(long long i=1;i<=n;i++)
	{
		s+=i-1; 
		if(s<=p)
			a[i]=1;
		else
		{
			s-=i-1;
			ed=i-(p-s)-1;
			for(int j=1;j<=ed;j++)
				a[j]=2;
			a[i]=q-1;
			for(int j=i+1;j<=n;j++)
				a[j]=q;
			break;
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：ctzm (赞：0)

## 题意简述

给定三个整数 $n, p, q$，构造一个长为 $n$ 的正整数序列，使得这 $n$ 个数无序选两个不同位置的数构成的 $\dfrac{n(n-1)}{2}$ 个加和中有恰好 $p$ 个和 $\le q$，输出任意一种方案。

## Solution:

像这种构造题目乍一看没有什么头绪，但是可以先从一些特殊性质想起。

假设 $p$ 恰好 $= \dfrac{i(i-1)}{2}$ $(1 \le i \le n)$，显然可以放 $i$ 个足够小的数，使得这个数的两倍依然 $\le q$，这里取 $1$（其实 $2$ 也满足，因为保证 $q \ge 4$）。

猜测正解也是由这样的方式变化过来的：首先取出 $k$ 个 $1$，其中 $k$ 为满足 $\dfrac{k(k-1)}{2} \le p$ 的最大值。

但是现在还需要继续增加 $p - \dfrac{k(k - 1)}{2}$ 的答案，那就只留下 $p - \dfrac{k(k - 1)}{2}$ 个 $1$，其余全部替换成 $2$，显然此时答案不变。

然后再添加一个 $q - 1$，此时 $q - 1$ 可以与 $p - \dfrac{k(k - 1)}{2}$ 个 $1$ 结合产生贡献，且不会与 $2$ 结合，所以此时答案恰为 $p$，其余数全部填充 $10^7$ 即可。

## code:

注意：
1. 开 `long long`，[否则就会……](https://www.luogu.com.cn/record/188878119)
2. 如果你 [WA on #1](https://www.luogu.com.cn/record/188877068)，那多半是 $p = \dfrac{n(n-1)}{2}$ 的时候出了问题，可以手造一组数据来看看（很可能是你不小心多输出了一个数）。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p,q,cntm,cnt1,cnt2;//cntm 表示 10^7 的个数，里面包含了一个 q-1 
int main(){
	scanf("%lld%lld%lld",&n,&p,&q);//十年 OI 一场空，____________________ 
	for(int i=0;;i++){
		if(p<i)break;
		p-=i;
		cnt2++;//维护增量，实际上就是求 k 的值 
		//此处假装全部添加 2 
	}
	cnt2-=p;
	cnt1+=p;//替换 p-k(k-1)/2 个 2 为 1 
	cntm=n-cnt1-cnt2;
	for(int i=1;i<=cntm;i++){
		printf("%d ",i==cntm?q-1:10000000);//需要一个 q-1 
	}
	for(int i=1;i<=cnt1;i++)printf("1 ");
	for(int i=1;i<=cnt2;i++)printf("2 ");

}
```

---

## 作者：Vct14 (赞：0)

简单构造题，但是赛时因为打错一个符号而且没开 `long long` 被卡了半个小时。

先说构造：取最小的 $m$ 使得 $s=\frac{m(m-1)}{2}\geqslant p$，构造的序列含有 $(n-m)$ 个 $q$、$1$ 个 $q-1$、$(s-p)$ 个 $2$ 和 $(m-s+p-1)$ 个 $1$。

下面我将逐步讲讲我是如何想到这种构造的。（可能有些繁琐。）

下文中的两数“配对”均指这两个数相加不大于 $q$。

------------


首先我考虑了几种特殊情况。

$p=0$ 时，容易想到全部取 $q$ 即可。这种情况让我知道，**如果想让某个数与任何数都无法配对，那么取 $q$ 即可。**（实际上也可以取 $10^7$。）

$p<n$ 时，我想到使某一个数 $m$ 和另外 $p$ 个数两两配对。那么那 $p$ 个数中任意取两数都不能配对。如果使这 $p$ 个数相同，则这个数必须大于 $\left\lfloor\frac{q}{2}\right\rfloor$。为了方便起见，我取这个数为 $q-1$，$m=1$。由于已经凑够了 $p$ 个加和，剩下的数按上文所说取 $q$ 即可。

接下来，为了找一些特殊情况，我开始倒着考虑。

$p=\frac{n(n-1)}{2}$ 时，全部取 $1$ 即可。

$p=\frac{n(n-1)}{2}-1$ 时，只需减少一组配对的数。如果只改变一个数，显然是不行的。因此需要改变两个数。这两个数分别可以与剩下的数配对，但它们俩之间不能配对。顺着 $p<n$ 的思路，我想到了取 $2$ 和 $q-1$。

$p=\frac{n(n-1)}{2}-2$ 时，需要再减少一组配对的数。于是我想到了少取一个 $1$，多取一个 $2$ 的思路。我们取 $n-3$ 个 $1$、两个 $2$ 和一个 $q-1$ 即可。

依此类推，我得到了这样一个结论：当 $p=\frac{n(n-1)}{2}-k$ 时（其中 $k$ 满足 $0\leqslant k\leqslant n-1$），取 $n-1-k$ 个 $1$、$k$ 个 $2$ 和一个 $q-1$ 即可。这个结论可以转化为：序列中的 $n$ 个数可以满足所有 $p\in[\frac{(n-2)(n-1)}{2},\frac{n(n-1)}{2}]$。（当 $k=n-1$ 时，$p=\frac{n(n-1)}{2}-(n-1)=\frac{n(n-1)-2(n-1)}{2}=\frac{(n-2)(n-1)}{2}$。于是我推得，**序列中的 $m$ 个数可以满足所有 $p\in[\frac{(m-2)(m-1)}{2},\frac{m(m-1)}{2}]$**。又因为 $\frac{(m-2)(m-1)}{2}=\frac{(m-1)((m-1)-1)}{2}$，所以这些集合可以覆盖所有 $p\in[1,\frac{n(n-1)}{2}]$。剩下的数取 $q$ 即可。

想到了构造方法，接下来的问题就是怎样实现。按照以上思路，我们取最小的 $m$ 使得 $s=\frac{m(m-1)}{2}\geqslant p$。那么用这 $m$ 个数一定可以符合条件。换一种与上文相同的形式，现在 $p=\frac{m(m-1)}{2}-(s-p)$，那么取 $(m-1-s+p)$ 个 $1$、$(s-p)$ 个 $2$ 和一个 $q-1$ 即可。剩下的 $(n-m)$ 个数全部填 $q$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,p,q;
	cin>>n>>p>>q;
	int m=1;while(m*(m-1)<2*p) m++;
	int s=m*(m-1)/2;
	for(int i=1; i<=m-s+p-1; i++) cout<<"1 ";
	for(int i=1; i<=s-p; i++) cout<<"2 ";
	cout<<q-1<<" ";
	for(int i=1; i<=n-m; i++) cout<<q<<" ";
	return 0;
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
容易得到，任意一个正整数都能被唯一地表示为 ${x(x-1) \over 2}+y(0 \le y < x)$，那么我们只需将 $p$ 按上述方式表示，即令 $p={x(x-1) \over 2}+y(0 \le y < x)$，那么序列
$$a_i=\begin{cases}
1,&\text{$i \le y$}\\
2,&\text{$y<i \le x$}\\
q-1,&\text{$i=x+1$}\\
q,&\text{$i>x+1$}
\end{cases}$$
满足要求。其正确性极易证明：对于所有的 $1 \le i < j \le x$，有 $a_i+a_j \le 2+2 = 4$，这就已经有 $x(x-1) \over 2$ 个和不大于 $q$ 了。而对于 $1 \le i \le y$，每个 $a_i$ 都能与 $a_{x+1}$ 相加组成 $q$，则又有 $y$ 个和不大于 $q$。而对于其它的和，都为 $q+1$ 或 $q+2$，都大于 $q$。这样便满足要求。

最后记得开 long long。
# 参考代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,p,q,tab[(int)1e6+5];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>p>>q;
	for(int i=1;i<=n;i++) tab[i]=tab[i-1]+i-1;
	tab[n+1]=1e15;
	int x=1;
	while(tab[x+1]<=p) x++;
	int y=p-tab[x];
	for(int i=1;i<=n;i++){
		if(i<=y) cout<<"1 ";
		else if(i<=x) cout<<"2 ";
		else if(i==x+1) cout<<q-1<<' ';
		else cout<<q<<' ';
	}
	return 0;
}
```

---

