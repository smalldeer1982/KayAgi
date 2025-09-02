# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000```

### 输出

```
1 1
3 7
299929959 603196135```

# 题解

## 作者：yitinboge_fan (赞：1)

# CF2120D Matrix game

观察题目，题目要求**按字典序**最小化矩阵大小。换句话说，优先判断行数。因此，我们先最小化 $n$。

考虑行数时，需要保证每一列都必然存在 $a$ 个数相同，否则根据题意 Harshith 就可以构造出不满足条件的矩阵。于是有 $n$ 的下界为 $k(a-1)+1$。

接下来考虑 $m$。我们发现，对于 Harshith 来说，每一列中重复出现至少 $a$ 次的数出现次数越少越好。例如 $a=k=2$ 时，根据上面的式子算出 $n\ge 3$，那么如果 $n=3$，假设在一列中 $1$ 出现至少两次，那么对于 Harshith 来说最优解就是 $1$ 出现两次，$2$ 出现一次。

假设 Harshith 已经构造出了矩阵，那么对于 Aryan 来说，每一列只需要考虑那个重复出现了 $a$ 次的数和其出现的 $a$ 个位置即可，简单计算得这些共有 $k\dbinom{n}{a}$ 种情况。于是，可以计算得到当 $n$ 取下界时，$m$ 的下界为 $k(b-1)\dbinom{n}{a}+1$。由于 $a\le10^5$，组合数暴力计算即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1e9+7;
ll fastpow (ll a, ll b)
{
    ll r = 1;
    while (b)
    {
        if (b & 1) r = r * a % p;
        a = a * a % p; b >>= 1;
    }
    return r;
}
int main (void)
{
    int $; scanf ("%d", &$);
    while ($--)
    {
        int a, b, k, i; scanf ("%d%d%d", &a, &b, &k);
        ll n = (a-1ll) * k + 1; n %= p;
        ll m = 1;
        for (i=1; i<=a; i++) m = m * fastpow (i, p-2) % p * ((n-i+1+p) % p) % p;
        m = m * k % p * (b-1) % p + 1;
        printf ("%lld %lld\n", n, m%p);
    }
}

```

---

## 作者：_O_v_O_ (赞：0)

赛时唐了，看到组合数不会算了。

先考虑 $n$。

根据鸽笼原理，每列中至少应有一种数出现 $a$ 次。

那么很显然，$n$ 最少为 $k\times(a-1)+1$。

再考虑 $m$。

设 $x$ 为每列中能出现的不同方案数，很显然 $x={n\choose a}\times k$。这个组合是可以暴力算的。

根据鸽笼原理，这个矩阵中最少要有一种方案出现了 $b$ 次，那么 $m=x\times (b-1)+1$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
int a,b,k;
int n,m; 

int fp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
} 
int inv(int x){
	return fp(x,mod-2)%mod;
}

int calc(int x,int y){
	int res=1;
	for(int i=1;i<=y;i++) (res*=inv(i)*((n-i+1+mod))%mod)%=mod;
	return res;
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>a>>b>>k;
		n=(a-1)*k+1;n%=mod;
		m=calc(n,a);m=m*k%mod*(b-1)%mod+1;m%=mod;
		cout<<n<<' '<<m<<endl;
	}
	return 0;
}

```

---

