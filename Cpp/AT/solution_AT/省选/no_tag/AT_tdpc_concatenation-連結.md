# 連結

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_concatenation

入力は以下の形式で標準入力から与えられる。

> $ N $ $ L $ $ w_1 $ $ ... $ $ w_N $

 答えを一行に出力せよ。 ```

4 10
00
01
10
11
```

```

1024
```

```

3 5
01
10
0
```

```

14
```

## 说明/提示

### Constraints

 $ N $ 個の 0, 1 からなる文字列 $ w_1 $, ..., $ w_N $ がある。すぬけ君は、この中から文字列をいくつか選び、好きな順番で連結して文字列を作ることにした (同じ文字列を複数回選んでもよい)。このようにして作ることのできる長さ $ L $ の文字列の個数を mod 1,000,000,007 で求めよ。ただし、文字列として同じであれば、連結のしかたが異なるものも同じであるとみなす。

- - - - - -

- $ 1\ <\ =\ N\ <\ =\ 510 $
- $ 1\ <\ =\ |w_i|\ <\ =\ 8 $
- $ 1\ <\ =\ L\ <\ =\ 100 $
- Each character in $ w_i $ will be either '0' or '1'.
- $ w_i $ are pairwise distinct.

# 题解

## 作者：_jimmywang_ (赞：0)

我一看到本质不同串，自动往字符串科技上思考。然后你就会发现，你字符串学傻了。

------------------

状压。

字符串科技可能不太擅长处理这种拼起来的东西，但是你观察到 $|s_i| \le 8$，考虑能不能状压。但是直接朴素的状压表示当前串后 $8$ 位的话，无法判定本质不同。因此我们需要一些聪明一点的做法。

考虑把求不同方案数转换为枚举所有长度为 $L$ 的 01 串，判定是否可以被切成若干个给定串，并统计这样的合法串数量。

这个东西是容易状压的。具体的：设 $dp_{i,j,k}$ 表示长度为 $i$ 的串 $s$，把下标编号为 $1$ 到 $i$，那么 $j$ 储存 $s_{i-7}$ 到 $s_i$ 的 01 状态，$k$ 储存 $i-7$ 到 $i$ 中，哪些位置可以成为拼串的终止位置，即对于哪些 $p$，$s_1$ 到 $s_{i-p}$ 可以切成若干个给定串。

那么转移十分易于理解。枚举当前位置放 0 还是 1，暴力往前枚举判断 $i$ 这个位置能否成为新的终止位置：如果存在从某一个之前的终止位置到末尾之间的串 是一个给定串，那么 $i$ 就可以成为终止位置。为了加速判断，可以 hash 一下。

最终统计第 $L$ 个位置可以成为终止位置的方案数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
ll n,m;
const ll mod=1000000007;
ll dp[110][256][256];
char c[10];
map<ll,bool>mp;
int main(){
	n=d;m=d;
    f(i,1,n){
        scanf("%s",c+1);ll l=strlen(c+1);
        ll t=0;for(int j=l;j>=1;j--)t=t*3+c[j]-'0'+1;
        mp[t]=1;
    }
    dp[0][0][1]=1;
    f(i,1,m)f(j,0,255)f(k,0,255)if(dp[i-1][j][k]){
        ll s=2*(j&127),t=2*(k&127),o=1;
        f(x,0,min(7ll,i-1)){
            if(mp[o]&&((k>>x)&1))t|=1;
            o=o*3+((j>>x)&1)+1;
        }dp[i][s][t]=(dp[i][s][t]+dp[i-1][j][k])%mod;
        // cout<<i<<" "<<s<<" "<<t<<"  <- "<<i-1<<" "<<j<<" "<<k<<endl;
        s=2*(j&127)+1,t=2*(k&127),o=2;
        f(x,0,min(7ll,i-1)){
            if(mp[o]&&((k>>x)&1))t|=1;
            o=o*3+((j>>x)&1)+1;
        }dp[i][s][t]=(dp[i][s][t]+dp[i-1][j][k])%mod;
        // cout<<i<<" "<<s<<" "<<t<<"  <- "<<i-1<<" "<<j<<" "<<k<<endl;
    }
    ll res=0;
    f(i,0,255)f(j,0,255)if(j&1)res=(res+dp[m][i][j])%mod;
    cout<<res<<endl;
	return 0;
}
```

---

