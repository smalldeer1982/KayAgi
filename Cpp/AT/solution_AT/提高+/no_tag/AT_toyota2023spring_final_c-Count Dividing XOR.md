# Count Dividing XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/toyota2023spring-final/tasks/toyota2023spring_final_c

整数 $ L,R $ が与えられます． 以下の条件を満たす整数の組 $ (A,B) $ の個数を数えてください．

- $ L\ \leq\ A\ <\ B\ \leq\ R $
- $ A $ は $ A\ \oplus\ B $ で割り切れる．
- $ B $ は $ A\ \oplus\ B $ で割り切れる．

ただしここで $ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表します．

  ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の非負整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ L\ <\ R\ \leq\ 10^{18} $
- $ R-L\ \leq\ 10^6 $
- 入力される値はすべて整数である

### Sample Explanation 1

$ (A,B)=(4,5) $ と $ (A,B)=(4,6) $ が条件を満たします．

## 样例 #1

### 输入

```
3 6```

### 输出

```
2```

## 样例 #2

### 输入

```
1 100```

### 输出

```
124```

## 样例 #3

### 输入

```
999000000 1000000000```

### 输出

```
1726239```

# 题解

## 作者：FFTotoro (赞：6)

神仙数学题，有数学竞赛那味了。

有一个重要结论：$A\oplus B=B-A$，这里 $\oplus$ 表示按位异或。证明如下：

$\because A\oplus B|A, A\oplus B|B,$

$\therefore A\oplus B|B-A\Rightarrow A\oplus B\le B-A,$

$\because A\oplus B\ge B-A,$

$\therefore A\oplus B=B-A.$

所以只用枚举 $A\oplus B$（即 $B-A$），然后枚举可能的 $A$ 即可。令 $D=R-L$，则时间复杂度 $O(D\log D)$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int l,r,c=0; cin>>l>>r;
  for(int i=1;i<=r-l;i++) // 枚举 A^B
    for(int j=(l+i-1)/i*i;i+j<=r;j+=i)
      c+=(j^i+j)==i; // 如果 j 和 i+j 的异或值为 i，那么这个答案就是合法的
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：AC_love (赞：1)

发现 $L, R$ 都很大但 $R - L$ 很小，猜测答案和 $R - L$ 有关。

找性质：

$$A \oplus B | A, A \oplus B | B$$

所以有：

$$A \oplus B | B - A$$

因此：

$$A \oplus B \le B - A$$

而根据异或的定义，有：

$$A \oplus B \ge B - A$$

所以：

$$A \oplus B = B - A$$

到这里我们知道：$A \oplus B = B - A$ 是原命题的必要条件。因此我们只要枚举 $B - A$ 的值，然后枚举所有 $[L, R]$ 范围内它的倍数，判断一下相邻两个数的异或和是否是 $B - A$ 即可。

令 $n = R - L$，复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/toyota2023spring-final/submissions/59996642)

---

## 作者：zhangjiahe__ (赞：1)

数学好题。

# 思路：

发现 $R$ 值域很大，而 $R-L$ 却很小，考虑往 $R-L$ 方向分析，可以发现 $A \oplus B$ 在能整除 $A$ 和 $B$ 时有一些性质。

$A \oplus B$ 能整除 $A$ 和 $B$，所以也能整除 $B-A$，得 $A \oplus B \leq B-A$。而 $A \oplus B$  $\ge B-A$（根据定义，再怎么消除二进制重复位最多也只能从 $B$ 中消去一个 $A$），所以 $A \oplus B = B-A$，证毕。

枚举 $A \oplus B$ 和 $A$ 即可，时间复杂度 $\Theta((R-L) \log (R-L))$，显然可过，细节见注释。

注意开 long long! ~~不开见祖宗~~
```cpp
#include <bits/stdc++.h>
using namespace std;
long long l, r, ans;
int main()
{
    cin >> l >> r;
    for(long long i = 1; i <=  r-l; i++)  //异或(B-A)枚举
        for(long long j = (i+l-1)/i*i; j+i<=r;j+=i)
            ans += ((j^i+j)==i);//判断，j表示A，i+j表示B
    cout << ans;
}
```

---

## 作者：Magus (赞：1)

## 前言

非常好数学题！！

## 题解

有一个显然的结论是 $A \oplus B = B-A$。

证明：

根据题意，因为 $A \oplus B|A$ 且 $A \oplus B|B$，所以 $A \oplus B \leq B-A$。

因为 $A \oplus B \geq B-A$，$A \oplus B \leq B-A$，所以 $A \oplus B = B-A$。

证毕。

那么我们就枚举 $A \oplus B$ 和 $A$ 即可，需要注意的是运算符优先级。

## Code

```cpp
#include<bits/stdc++.h>
#define FastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
int n,m,x,y,ans;
signed main()
{
	FastIO;
	cin>>x>>y;
	for(int i=1;i<=abs(x-y);i++)
	{
		for(int j=(x+i-1)/i*i;i+j<=y;j+=i)
		{
			if((j^(i+j))==i)
			{
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Wilderness_ (赞：0)

病了，写篇题解复活。

### 思路
根据题意，

$$\because A\oplus B\mid A, A\oplus B\mid B,A<B\\\therefore A\oplus B\le B-A\\\because A\oplus B\ge B-A\\\therefore A\oplus B=B-A$$

根据上述结论，以及题目中 $R-L\le 10^6$ 这一特别的条件，我们只需枚举 $A\oplus B$（范围在 $[1,R-L]$）和 $A$
（范围在 $[L,R]$）的值即可（枚举 $A\oplus B$ 和 $B$ 的值同理），时间复杂度为 $O((R-L)\log (R-L))$。

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
	{
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void write(ll x)
{
    if(x<0)
	{
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x%10+48);
    return;
}
int main()
{
	ll l=read(),r=read(),ans=0;
    for(ll del=1;del<=r-l;++del)
        for(ll a=((l-1)/del+1)*del;a+del<=r;a+=del)
            ans+=(a^(a+del))==del;
    write(ans);
	return 0;
}
```

---

## 作者：Bamboo_Day (赞：0)

简单数学题

# 性质
zzy 曾说过：数学，先猜后证。

考虑寻找一个量与 $R-L$ 有关。

整体一共涉及三个量：$A,B,A\oplus B$。

很自然的想到枚举 $A\oplus B$。

## 证明
设 $A\oplus B = C$，则 $C$ 整除 $A$ 也整除 $B$，故 $C$ 也整除 $B-A$，则 $C \leq B-A$。

# 
所以枚举 $A\oplus B$ 和 $A$ 即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,ans=0;
signed main() {
	cin >> l >> r;
	for(int i = 1; i <= r-l; i++){
		for(int j = (l+i-1) / i*i; i+j <= r; j += i){
			if((i^j)%i == 0 && (i^j) > j && (i^j) <= r){//用到一个性质，B^A^A=B , 注意限定 B 的范围
				ans++;
			}
        }
	}
	cout << ans;
	return 0;
}
```

---

