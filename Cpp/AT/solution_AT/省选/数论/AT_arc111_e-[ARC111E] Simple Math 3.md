# [ARC111E] Simple Math 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_e

この問題では一つの入力につきテストケースが $ T $ 個与えられます。

整数 $ A $, $ B $, $ C $, $ D $ が与えられます。次の条件を満たす正整数 $ i $ はいくつあるか求めてください。

- $ A\ +\ B\ \times\ i $ 以上 $ A\ +\ C\ \times\ i $ 以下の整数はいずれも、$ D $ の倍数ではない。

なお、制約より答えが有限であることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10{,}000 $
- $ 1\ \leq\ A\ <\ D $
- $ 0\ \leq\ B\ <\ C\ <\ D $
- $ 2\ \leq\ D\ \leq\ 10^8 $

### Sample Explanation 1

$ 1 $ ケース目の $ (A\ +\ B\ \times\ i,\ A\ +\ C\ \times\ i) $ を列挙すると次のようになります。 $ i\ =\ 3 $ のみ条件を満たすことがわかります。 - $ i\ =\ 1:\ (4,\ 5) $ - $ i\ =\ 2:\ (5,\ 7) $ - $ i\ =\ 3:\ (6,\ 9) $ - $ i\ =\ 4:\ (7,\ 11) $ - $ i\ =\ 5:\ (8,\ 13) $ - :

## 样例 #1

### 输入

```
2
3 1 2 5
99 101 103 105```

### 输出

```
1
25```

# 题解

## 作者：Seauy (赞：3)

可以称 $D$ 的倍数为解。

区间 $[A+Bi,A+Ci]$ 的长度为 $(C-B)i$，想要不存在解首先得满足 $(C-B)i<D$，这里设 $n=\lfloor \frac{D-1}{C-B} \rfloor$，那么 $i\leq n$。

剩下来的情况中，每个区间就最多只包含一个解。我们不妨把所有区间的解的个数之和求出来，然后减掉就是没有解的区间个数。

可以前缀和计算，$[0,A+Ci]$ 的解的个数为 $\lfloor \frac{Ci+A}{D} \rfloor$，$[0,A+Bi]$ 的解的个数为 $\lfloor 
\frac{Bi+A-1}{D} \rfloor$，交换一下求和顺序可以写成

$$ \sum_{i=0}^n \lfloor \frac{Ci+A}{D} \rfloor -\sum_{i=0}^n \lfloor 
\frac{Bi+A-1}{D} \rfloor $$

套上类欧模板即可，复杂度 $O(\log D)$。注意到 $A<D$，所以 $i=0$ 的时候肯定无解，因此上面的和式能从 $i=0$ 开始。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT=1e4;

int A,B,C,D;

inline ll squ(ll x) {return x*x;}
inline ll LIN(ll x) {return (x*(x+1))>>1;}

ll euclike(ll a,ll b,ll c,ll n)
{
	if(!a) return (n+1)*(b/c);
	if(a<c && b<c)
	{
		ll n_=(a*n+b)/c;
		return n_*n-euclike(c,c-b-1,a,n_-1);
	}
	return LIN(n)*(a/c)+(n+1)*(b/c)+euclike(a%c,b%c,c,n);
}

int main()
{
	int T;scanf("%d",&T);
	for(int n;T--;)
	{
		scanf("%d %d %d %d",&A,&B,&C,&D);
		n=(D-1)/(C-B);
		printf("%lld\n",n-euclike(C,A,D,n)+euclike(B,A-1,D,n));
	}
	return 0;
}
```


---

## 作者：SoyTony (赞：2)

若 $[A+Bi,A+Ci]$ 中没有 $D$ 的倍数，则有：

$$\left\lfloor\dfrac{A+Bi-1}{D}\right\rfloor=\left\lfloor\dfrac{A+Ci}{D}\right\rfloor$$

若保证二者之差不大于 $1$，即：

$$(A+Ci)-(A+B_i-1)\le D\Rightarrow (C-B)i\le D-1\Rightarrow i\le \left\lfloor\dfrac{D-1}{C-B}\right\rfloor$$

此时，

$$\sum_{i=1}^{\left\lfloor\frac{D-1}{C-B}\right\rfloor} \left\lfloor\dfrac{A+Ci}{D}\right\rfloor-\left\lfloor\dfrac{A+Bi-1}{D}\right\rfloor$$

即为 $[A+Bi,A+Ci]$ 中有 $D$ 的倍数的区间个数，使用类欧几里得算法求出，再用 $\left\lfloor\frac{D-1}{C-B}\right\rfloor$ 减去即可。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/arc111/submissions/45305268)

---

## 作者：Caiest_Oier (赞：1)

# [AT_arc111_e](https://www.luogu.com.cn/problem/AT_arc111_e)    
类欧板题。     

当一个区间 $[l,r]$ 的长度大于等于 $D$ 的时候，其必然会含有一个 $D$ 的整数倍，而对于所有长度小于 $D$ 的区间，其最多只含有一个 $1$。于是找到最大的一个 $mx$ 满足 $(A+Cmx)-(A+Bmx)+1<D$，则如果 $\lfloor\frac{A+Ci}{D}\rfloor-\lfloor\frac{A+Bi-1}{D}\rfloor=1$ 则不符合要求，否则符合要求。我们发现答案就等于 $mx-(\sum_{i=1}^{n}\lfloor\frac{A+Ci}{D}\rfloor-\lfloor\frac{A+Bi-1}{D}\rfloor)$，拆开来就是两个类欧式子，套板子即可。   

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,A,B,C,D,ans,lmt;
int floor_sum(int n,int m,int a,int b){//sum_{i=1}^{n} (a+b*i)/m
    if(n<=0)return 0;
    if(n==1)return (a+b)/m;
    if(b==0)return n*(a/m);
    if(m==1)return n*a+b*(n*(n+1)/2);
    int ra=(a/m),rb=(b/m);
    if(a<0)ra=(a-(((a%m)+m)%m))/m;
    if(b<0)rb=(b-(((b%m)+m)%m))/m;
	if(ra!=0||rb!=0)return floor_sum(n,m,a-ra*m,b-rb*m)+ra*n+rb*(n*(n+1)/2);
	return (n+1)*((a+b*n)/m)-floor_sum((a+b*n)/m,b,b-a-1,m);
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>A>>B>>C>>D;
		if(D%(C-B)==0)lmt=(D/(C-B))-1;
		else lmt=(D/(C-B));
		while(lmt*(C-B)+1>=D)lmt--;
		ans=lmt-(floor_sum(lmt,D,A,C)-floor_sum(lmt,D,A-1,B));
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Purslane (赞：0)

# Solution

取 $u = \lfloor \frac{d-1}{c-b} \rfloor$，显然他是可能的 $i$ 的上界。

发现 $i \le u$ 时，$[\exists x \in [a+bi,a+ci], \text{s.t.} \ d \mid x] =\lfloor \frac{a+ci}{d}\rfloor - \lfloor \frac{a+bi-1}{d} \rfloor$。

因此答案就可以写成两个类欧的形式。

用了一下 `atcoder library`。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
using namespace atcoder;
int T,a,b,c,d;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>a>>b>>c>>d;
		int lim=(d-1)/(c-b);
		cout<<lim-floor_sum(lim,d,c,a+c)+floor_sum(lim,d,b,a-1+b)<<'\n';
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

由于区间长度 $<d$ 才可能满足条件，所以 $i \le \displaystyle \left\lfloor\frac{d-1}{c-b}\right\rfloor$。考察区间 $l,r$（长度 $<d$），设“格”为 $[0,d),[d,2d),[2d,3d),\dots$ 如果 $[l,r]$ 中包含 $d$ 的倍数，那么 $l,r$ 在不同的相邻的“格”当中。如果不包含，则 $l,r$ 在同一个格当中，且 $l$ 不是 $d$ 的倍数。注意到格函数 $L(x) = \left\lfloor\dfrac xd \right\rfloor$。则根据上述观察有式：
$$
\begin{array}{l}
[\text{$l\sim r$ 不包含 $d$ 的倍数 ($r-l+1<d$)}] = 1 - (L(r) - L(l-1))
\end{array}
$$
两边 $\sum$ 一下发现拆开后是典中典类欧（$f$ 函数），然后就做完了。

---

