# You Are Given Some Letters...

## 题目描述

给你一个 $a$ ，一个 $b$ ，让你找出所有字符串，满足它仅由 $a$ 个 _A_ 和 $b$ 个 _B_ ，并且分别求出它们的最小周期 $k$ （设该串为 $s$ ,即k满足s[i]=s[i%k]）。

输出共有多少不同的 $k$ 。

## 样例 #1

### 输入

```
2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
5
```

# 题解

## 作者：皎月半洒花 (赞：9)

Σ( ° △ °|||)︴啊嘞，为什么这么好一道题没人做啊。

下文中用$a,b$表示输入的那俩值。

我们考虑对于一个合法的$k$而言，假设在这个$k$满足$k=\lfloor n/p\rfloor,p\in \mathbb{N}$，那么$p$就是循环节的数量。现在我们假设有$q_a+q_b=k$，即每一段循环节中$A$的数量和$B$的数量。那么一定需要满足的是$q_a\cdot p\leq a$并且$q_b\cdot p\leq b$。

看上去有了这个之后我们就可以直接数了？我们考虑一定需要的是

$$ q_a \leq \lfloor\frac{a}{p}\rfloor, q_b \leq \lfloor\frac{b}{p}\rfloor $$
但同时也要注意，还有一个条件，就是我们的$p$既然是循环节的数量，并且我们实际上可以多出去一堆下脚料（雾，那么也就是说剩下的字符数量$a_{rest},b_{rest}$必须小于等于我们的$q_a$和$q_b$。也就是说需要有
$$(p+1)\cdot q_a \geq a,(p+1)\cdot q_b\geq b$$

美化一下就是

$$\lceil \frac{a}{p+1} \rceil \leq q_a\leq \lfloor \frac{a}{p} \rfloor $$
$$\lceil \frac{b}{p+1} \rceil \leq q_b\leq \lfloor \frac{b}{p} \rfloor $$

那么我们就可以通过从1到n枚举$p$来求得$q_a$和$q_b$，那么根据上文的定义，$q_a$和$q_b$是单独一段循环节中的$A$和$B$的数量，所以$q_a+q_b$对$k$产生贡献。

然后这东西显然是可以数论分块的，所以我们分一下块就做完了：

```cpp
#define LL long long
#define Mod 1000000007

using namespace std ;
int N, M, L ; LL Ans ;

int main(){
    cin >> N >> M, L = N + M ;
    for (int g, l = 1, r ; l <= L ; l = r + 1){
        g = L / l, r = L / g ;
        if (N < g || M < g) continue ;
        int ln = (N + g) / (g + 1), hn = N / g ;
        int lm = (M + g) / (g + 1), hm = M / g ;
        if (hn >= ln && hm >= lm)
            Ans += max(0ll, 1ll * (min(hn + hm, r) - max(l, lm + ln) + 1)) ;
    }
    cout << Ans << endl ; return 0 ;
}

```

---

## 作者：Leap_Frog (赞：2)

### P.S.
有意思的好题。  

### Description.
好的字符串定义为其满足有 $a$ 个 `a`，$b$ 个 `b`。  
求所有好的字符串有多少种可能的不同循环节。  
$$a,b\le 10^9$$

### Solution.
下文设 $k$ 为循环节数量，$a_1$ 和 $b_1$ 分别表示一个循环节内有多少 `a` 和 `b`
$$k\times a_1\le a\le (k+1)\times a_1$$
$$k\times b_1\le b\le (k+1)\times b_1$$
$$\therefore \left\lfloor\frac {a+k}{k+1}\right\rfloor\le a_1\le\left\lfloor\frac ak\right\rfloor$$
$$\therefore \left\lfloor\frac {b+k}{k+1}\right\rfloor\le b_1\le\left\lfloor\frac bk\right\rfloor$$
同时也有
$$\left\lfloor\frac{a+b+k}{k+1}\right\rfloor\le a_1+b_1\le\left\lfloor\frac{a+b}k\right\rfloor$$
$$len=a_1+b_1$$
所以只需要整除分块就可以了

### Coding.
```cpp
//我是一发子弹，子弹没有感情，因此，没有迷茫，只会飞向目标。{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
int a,b,n;ll rs=0;
int main()
{
	read(a),read(b),n=a+b;
	for(int l=1,r,k;l<=n;l=r+1)
	{
		k=n/l,r=n/k;if(a<k||b<k) continue;
		int la=(a+k)/(k+1),ra=a/k,lb=(b+k)/(k+1),rb=b/k;
		if(la<=ra&&lb<=rb) rs+=max(0,min(r,rb+ra)-max(l,la+lb)+1);
	}
	return printf("%lld\n",rs),0;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先，假设周期长度为 $x_1+x_2$，最后一小段为 $y_1+y_2$，$x_1,x_2$ 为一段周期中 `a` 和 `b` 的数量，$y_1,y_2$ 同理，那么显然有 $x_1\geq y_1$，$x_2\geq y_2$。同时，这也是充分条件，因为可以构造 `aaa...aaabbb...bbbaaa...aaa`，其中前半段 `a` 共有 $y_1$ 个。

考虑枚举最短周期循环了多少次，容易发现符合要求的次数是 $O(\sqrt{a+b})$ 的。枚举每个循环的次数 $i$，即可得到 $x_1$ 的最小值与最大值（也就是 $y_1$ 的最大值与最小值），$x_2,y_2$ 同理。那么该次数的贡献也就是 $x_1$ 最小值与 $x_2$ 最小值的和到 $x_1$ 最大值与 $x_2$ 最大值的和中的所有 $k$。注意特判一下重复计算。总复杂度 $O(\sqrt{a+b})$，具体细节见代码。

```cpp
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*m+j)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
signed main(){
	int a,b; cin>>a>>b;
	int l=a+b,ans=1;
	for(int i=2;i<=sqrt(l);i++){
		//calc a
		int l1,r1;
		int p1=a/i,q1=a%i;
		if(q1!=0&&p1<(i-1-q1)) continue;
		if(q1==0){
			l1=p1;
			r1=p1+p1/(i-1);
		}
		else{
			l1=p1+1;
			r1=p1+1+(p1-(i-1-q1))/(i-1);
		}
		//calc b
		int l2,r2;
		int p2=b/i,q2=b%i;
		if(q2!=0&&p2<(i-1-q2)) continue;
		if(q2==0){
			l2=p2;
			r2=p2+p2/(i-1);
		}
		else{
			l2=p2+1;
			r2=p2+1+(p2-(i-1-q2))/(i-1);
		}
		ans+=(r1+r2)-(l1+l2)+1-((a%(i-1)==0)&(b%(i-1)==0));
	}
	for(int j=1;(l+j-1)/j>sqrt(l);j++){
		int i=(l+j-1)/j;
		//calc a
		int l1,r1;
		int p1=a/i,q1=a%i;
		if(q1!=0&&p1<(i-1-q1)) continue;
		if(q1==0){
			l1=p1;
			r1=p1+p1/(i-1);
		}
		else{
			l1=p1+1;
			r1=p1+1+(p1-(i-1-q1))/(i-1);
		}
		//calc b
		int l2,r2;
		int p2=b/i,q2=b%i;
		if(q2!=0&&p2<(i-1-q2)) continue;
		if(q2==0){
			l2=p2;
			r2=p2+p2/(i-1);
		}
		else{
			l2=p2+1;
			r2=p2+1+(p2-(i-1-q2))/(i-1);
		}
		ans+=(r1+r2)-(l1+l2)+1-((a%(i-1)==0)&(b%(i-1)==0));
	}
	cout<<ans; 
	return 0;
}
```

---

## 作者：songhongyi (赞：0)

我们设每个循环节里有 $a'$ 个 A，$b'$ 个 B。

枚举有 $k$ 个循环节。那么肯定有  $ka'\le a$，$(k+1)a'\ge a$，$b$ 同理。

可以把 $a',b'$ 的范围刻画成：
$$
\left\lceil\dfrac a {k+1}\right\rceil \le a' \le \left\lfloor\dfrac a k\right\rfloor\\\left\lceil\dfrac b {k+1}\right\rceil \le b' \le \left\lfloor\dfrac b k\right\rfloor
$$
那么答案 $l$ 满足：
$$
\left\lceil\dfrac a {k+1}\right\rceil +\left\lceil\dfrac b {k+1}\right\rceil \le l \le\left\lfloor\dfrac a k\right\rfloor+\left\lfloor\dfrac b k\right\rfloor
$$
注意到考虑原题的性质，$k$ 是可以整除分块的。所以整除分块后会得到 $O(\sqrt{a+b})$ 个区间，且左端点递增，所以直接合并即可。复杂度 $O(\sqrt{a+b})$。

---

