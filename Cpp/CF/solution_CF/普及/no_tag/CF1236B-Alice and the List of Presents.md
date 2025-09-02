# Alice and the List of Presents

## 题目描述

Alice got many presents these days. So she decided to pack them into boxes and send them to her friends.

There are $ n $ kinds of presents. Presents of one kind are identical (i.e. there is no way to distinguish two gifts of the same kind). Presents of different kinds are different (i.e. that is, two gifts of different kinds are distinguishable). The number of presents of each kind, that Alice has is very big, so we can consider Alice has an infinite number of gifts of each kind.

Also, there are $ m $ boxes. All of them are for different people, so they are pairwise distinct (consider that the names of $ m $ friends are written on the boxes). For example, putting the first kind of present into the first box but not into the second box, is different from putting the first kind of present into the second box but not into the first box.

Alice wants to pack presents with the following rules:

- She won't pack more than one present of each kind into the same box, so each box should contain presents of different kinds (i.e. each box contains a subset of $ n $ kinds, empty boxes are allowed);
- For each kind at least one present should be packed into some box.

Now Alice wants to know how many different ways to pack the presents exists. Please, help her and calculate this number. Since the answer can be huge, output it by modulo $ 10^9+7 $ .

See examples and their notes for clarification.

## 说明/提示

In the first example, there are seven ways to pack presents:

 $ \{1\}\{\}\{\} $

 $ \{\}\{1\}\{\} $

 $ \{\}\{\}\{1\} $

 $ \{1\}\{1\}\{\} $

 $ \{\}\{1\}\{1\} $

 $ \{1\}\{\}\{1\} $

 $ \{1\}\{1\}\{1\} $

In the second example there are nine ways to pack presents:

 $ \{\}\{1,2\} $

 $ \{1\}\{2\} $

 $ \{1\}\{1,2\} $

 $ \{2\}\{1\} $

 $ \{2\}\{1,2\} $

 $ \{1,2\}\{\} $

 $ \{1,2\}\{1\} $

 $ \{1,2\}\{2\} $

 $ \{1,2\}\{1,2\} $

For example, the way $ \{2\}\{2\} $ is wrong, because presents of the first kind should be used in the least one box.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
9```

# 题解

## 作者：jiangXxin (赞：5)

题目简述：

你有n种礼物，m个盒子，现在把这所有n种礼物装进盒子，盒子不能全为空，问有几种装法，答案对$1e9+7$取模.

考虑每个礼物在每个盒子有放和不放两种情况，那么就是$2^m$,但是题目说的不能全部为空，所以是$2^m-1$,总共有n个礼物，所以最终答案就是$(2^m-1)^n$

**code:**

c++

```cpp
    /**
    *    author:  a2954898606
    *    created: 2019/10/17 21:25:20
    **/
    #include<bits/stdc++.h>
    #define REP(A,B,I) for(int I=(A);I<=(B);I++)
    #define PER(A,B,I) for(int I=(A);I>=(B);I--)
    #define LL long long
    #define N 1000010
    #define M 100
    using namespace std;
    const long long mod=1e9+7;
    //long long quickpow(long long a,long long b){long long ret=1;while(b){if(b&1){ret=ret*a%mod;}}a=a*a%mod;b>>=1;return ret;}
    long long quickpow(long long a,long long b){
        long long ret=1;
        while(b){
            if(b&1){
                ret=ret*a%mod;
            }
            a=a*a%mod;
            b>>=1;
        }
        return ret;
    }
    //using namespace std;
    long long n,m,ans;
    int main(){
     
        cin>>n>>m;
        ans=quickpow(2,m);
        ans--;
        ans=quickpow(ans,n);
        cout<<ans<<endl;
        return 0;
    }
```


------------
**python:**

```python
s=input().split()
n=int(s[0])
m=int(s[1])
mod=10**9+7
print(pow((pow(2,m,mod)-1),n,mod))
```


---

## 作者：reyik (赞：4)

有人说$CF$的$B$~$E$比较适合备战$CSP-S$ $round$ $2$ ~~我咋不信呢~~

于是我来了

每一个物品，他在$m$个背包中的出现情况总数为$2^m$ ,但要保证他至少要再一个背包中出现，那么要减去全不选的情况

也就是$2^m-1$

然后一共有$n$个物品

所以答案就是$(2^m-1)^n$

做完了

```cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const long long mod=1000000007;
int n,m;
long long res2=2;
long long quick_pow(long long x,long long l) {
	x%=mod;
	long long res=1;
	while(l) {
		if(l&1) res=res*x%mod;
		x=x*x%mod;
		l>>=1;
	}
	return res;
}
int main() {
	scanf("%d%d",&n,&m);
	printf("%lld\n",quick_pow(quick_pow(2,m)-1+mod,n));
	return 0;
}
```

---

## 作者：fkcufk (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1236B)

#  解析
每一种物品都有放进去和不放进去两种选择，但是不能全部不放，也就是说要减去不放的情况。所以共有 $ 2^m-1 $ 种情况，一共有 $n$ 种物品，总共就是 $ (2^m-1)^n $ 种情况。

# 注意点
- 不开 `long long` 见祖宗。
- 需使用快速幂。

# 代码
```cpp
#include<bits/stdc++.h> // 万能头
using namespace std;
typedef long long ll; // 需开 long long
const int mod = 1000000007; // 取模值
ll n,m,ans;
ll kasumi(ll a,ll b){ // 快速幂
    ll ret=1;
    while(b){
        if(b%2) ret=(ret*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(false); // 断开 cin scanf
    cin.tie(NULL);cout.tie(NULL); // cin cout 加速
    cin >> n >> m;
    ans=kasumi(kasumi(2,m)-1+mod,n);
    cout << ans;
    return 0; // 好习惯
}
```

# 这可是蒟蒻第一篇题解，望管理员通过。

---

## 作者：风华正茂 (赞：1)

~~这不是一道水题吗？~~

~~尽管比赛时推了20min，我太蒟了~~。

假如这道题目没有“每种物品都出现过”的限制，那么它的答案就是$2^{nm}$，也就是每种物品的方案为$2^m$。

那么加上这个限制呢，每种物品必须要放，只用将每种物品的方案减一即可，也就是$2^m-1$。

所以用乘法原则得到$ans=(2^m-1)^n$。

~~快速幂都会吧~~

```cpp
#include<iostream>
#define ll long long
#define N 20005
#define K 1000000007
using namespace std;
ll qp(ll a,ll b){
	a=a%K;
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%K;
		a=a*a%K;
		b>>=1;
	}
	return ans;
}
ll n,m;
int main(){
	cin>>n>>m;
	cout<<qp(qp(2,m)-1+K,n)<<endl;
	return 0;
}
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1236B)

[CodeForces 链接](https://codeforces.com/problemset/problem/1236/B)

思路：

对于每一种物品，每个背包都有放进去和不放进去两种选择，但是不能全部不放，所以共有 $(2^m-1)$ 种情况。而一共有 $n$ 个物品，所以总共有 $(2^m-1)^n$ 中情况。

坑点：

- 本题需要开 ```long long```，不然会爆精度。
- 本题需要使用[快速幂](https://oiwiki.org/math/binary-exponentiation/)算法求解，否则会 TLE。
- 记得取模。

上代码：
```cpp
#include <iostream>
using namespace std;

inline long long ksm(long long a, long long b, long long p){// 快速幂模板
    long long s = 1;
    while (b > 0){
        if (b % 2 == 1){
            s = (s * a) % p;
        }
        a = (a * a) % p;
        b /= 2;
    }
    return s;
}

const int mod = 1e9 + 7;// 模数

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout加速
    int n, m;
    cin >> n >> m;
    // 计算公式并输出
    long long temp = ksm(2, m, mod);
    temp--;
    temp = ksm(temp, n, mod);
    cout << temp << "\n";
    return 0;
}
```

---

## 作者：ImposterAnYu (赞：0)

# 解析

我们先考虑 $1$ 种物品放进 $m$ 个背包的方法。

很显然，这个物品对于每个背包，都有放与不放两种选择，所以可以想到有 $2^m$ 种方案。~~如果你不知道为什么的话，建议你从头开始学数学。~~

但是呢，因为必须要求这个物品在 $m$ 个背包内至少出现一次，所以不能让这个物品在 $m$ 个背包内一次都不出现，即让 $m$ 个背包都为空，所以方案数变为 $2^m - 1$。

接下来，我们考虑 $n$ 种物品。

因为每种物品都和上面讲的一样，有 $2^m - 1$ 种方案，并且没有其他任何限制，所以我们可以得出总方案数为 $(2^m - 1)^n$。

这题 $n$ 和 $m$ 都比较大，暴力算幂妥妥的TLE，所以考虑使用快速幂统计答案，时间复杂度 $O(\log(n + m))$，空间复杂度 $O(1)$。

另外，这题其实是个双倍经验，另一道题为神鱼的[炼金术](https://www.luogu.com.cn/problem/P8557)，只要改个模数就能过了，切完这题后可以顺便把炼金术也切了。

# code

```c++
#include<bits/stdc++.h>
#define mod 1000000007
#define int1 long long
using namespace std;
int1 n,k;
int1 read(){
    int1 x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-'){
            f = -1;
        }
        ch = getchar();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(int1 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9){
        print(x / 10);
    }
    putchar(x % 10 + 48);
    return ;
}
int1 quick_pow(int1 a,int1 b,int1 p){//快速幂。
	int1 s = 1;
    while(b){
    	if(b & 1){
    		s = (s % p) * (a % p) % p;
    	}
    	a = (a % p) * (a % p) % p;
    	b >>= 1;
    }
    return s;
}
int main(){
	n = read(),k = read();
	print(quick_pow(quick_pow(2,k,mod) - 1,n,mod));//直接套公式。
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

# 题意
n 种物品放进 m 个盒子里，盒子不能全为空，求方案数（对 $1e9+7$ 取模）。
# 分析
对于每一个物品，若可使盒子全为空，则有每个盒子放和不放 2 种方案，根据乘法原理，总数是 $2^{m}$，考虑到全空的这一方案应该舍去，所以应该再减一，答案是 $2^{m}-1$。  
推广到 n 个物品时，再次考虑乘法原理，即 $(2^{m}-1)^{n}$。  
# 做法
由于 $1\le n,m\le 10^{9}$，如果朴素的做法会 TLE，因此考虑快速幂。  
不会的可以先看[P1226快速幂](https://www.luogu.com.cn/problem/P1226)。  
代码如下（请忽略快读快输的压行处理）。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(long long x){if (x < 0) x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
const long long p=1000000007;
long long qpow(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1) ans=ans*a%p;
        a=a*a%p,b>>=1;//位运算加快效率
    }
    return ans;
}
int main() {
	int n=read(),m=read();
	write(qpow(qpow(2,m)-1,n));
}


```
总体思路不难，重点是考虑好每一步的方案数。

---

