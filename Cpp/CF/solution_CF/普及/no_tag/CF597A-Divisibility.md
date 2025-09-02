# Divisibility

## 题目描述

寻找在区间 $\left[a,b\right]$ 中可以被 $k$ 整除的数字个数。

## 样例 #1

### 输入

```
1 1 10
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2 -4 4
```

### 输出

```
5
```

# 题解

## 作者：Grisses (赞：5)

[题面](https://www.luogu.com.cn/problem/CF597A)

这是一道简单的数学题。让我们看看暴力：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long int a,b,k,ans;
  int main{
      cin>>k>>a>>b;
      for(int i=a;i<=b;i++){
          if(i%k==0)ans++;
      }
      cout<<ans;
  }
```

当然，这样是不行的。~~（不过可以得到 TLE 的好成绩）~~

我们设 $l$ 是大于等于 $a$ 的最小的 $k$ 的倍数，$r$ 是小于等于 $b$ 的最大的 $k$ 的倍数。

不难发现，区间 $[a,b]$ 中 $k$ 的倍数的个数是等同于区间 $[l,r]$ 的。

设 $l=xk,r=yk(x,y\in Z)$，因为 $l\le r$，所以 $x\le y$。答案就是：
$$y-x+1$$

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long int k,a,b;//不开long long见祖宗
  int main()
  {
      cin>>k>>a>>b;
      k=abs(k);//正负无影响，取正好算一点
      long long int l=a+(a>0?k-abs(a%k):abs(a%k)),//|a%k|在a为正数时是a-(l-k)；a为负数时是l-a
      r=b-(b>0?abs(b%k):-abs(b%k)+k);//r同理
      if(l-a==k)l=a;
      if(b-r==k)r=b;//如果a、b刚好是k的倍数，那么l、r会向内k，要特判一下
      cout<<r/k-l/k+1;输出
      return 0;
  }
```

---

## 作者：流绪 (赞：4)

为什么这个A题能评到绿题???

由于 x/k,可以表示 (0,x] (x>0) 或 [x,0) (x<0) 这个区间内有多少个k的倍数

不懂的翻翻小学数学书

所以我们只要计算 b/k-a/k 就可以了,然后我们需要特判一些东西

a,b 均小于 0 时,根据上面那个范围的原理,若 b 刚好是 k 的倍数时,b/k 并不会将 b 包含进去,所以我们将 b+1 来包含 b

a,b 均大于 0 时,同样的道理,我们要对 a-1 来包含 a

a,b 一正一负时,可以发现 0 也是 k 的倍数,但他并不会被计算进去,所以我们 +1 来包含0 

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll k,a,b;
	cin >> k >> a >> b;
	ll ans;
	if(b<0)
		ans = (b+1)/k-a/k;
	else if(a>0)
		ans = b/k-(a-1)/k;
	else
		ans = b/k-a/k+1;
	cout << ans;
}
```


---

## 作者：xxzjbd (赞：1)

虽然是一道简单的数学题，但是细节很多。

这是一个区间问题，根据区间的性质，满足 $a < b$ 且 $a$ 与 $b$ 都能取到。除法的运算实则就是计算 $a$ 中有多少 $k$ 的倍数。只需分类讨论即可得出答案。

- $a > 0$ ，整个区间在正数范围。那么 $b$ $/$ $k$ $-$ $a$ $/$ $k$ 就是答案，但由于区间两边可取到，所以 $a$ 的情况不能减去，最终答案是 $b$ $/$ $k$ $-$ $a - 1 $ $/$ $k$
- $b < 0$ ，整个区间在负数范围，与正数同理，不同的是此时 $b$ 的情况不能减去，且负数需要变号，所以答案为 $-a$ $/$ $k$ $+$ $b + 1 $ $/$ $k$
- 区间跨越 $0$ ，由于两数相减时 $0$ 的情况不会计入，且 $0$ 也是 $k$ 的倍数，所以答案要 $+ 1$
## 代码如下
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll k,a,b,ans;
	cin>>k>>a>>b;
	if(a>0)ans=b/k-(a-1)/k;
	else if(b<0)ans=-a/k+(b+1)/k;
	else ans=b/k-a/k+1;
	cout<<ans;
}
```
## 谢谢观赏

---

## 作者：shenmadongdong (赞：1)

其实这道题多找规律就行了

把l,r缩放为能被k整除的数，输出它们的差除以k加1即可

代码：
```
var a,b,c,k:int64;
function cx(a:real):longint;
begin
  if a<0 then exit(trunc(a)-1) else exit(trunc(a));
end;
begin
  read(k,a,b);
  if (a mod k)<>0 then a:=(cx(a/k)+1)*k;
  if (b mod k)<>0 then b:=(cx(b/k))*k;
  c:=trunc((b-a)/k)+1;
   if a<=b then write(c) else write('0');
end.
```

---

## 作者：cqbzjyh (赞：1)

[题面](https://www.luogu.com.cn/problem/CF597A)

### Solution.

我们可以直观地发现 $[a,b]$ 之间能被 $k$ 整除的个数可以等价于 $[a,b]$ 中第一个能被 $k$ 整除的数减去最后一个能被 $k$ 整除的数的差除 $k$ 加 $1$。

我们设 $x\in[a,b]$ 是第一个能被 $k$ 整除的数字。

那么 $\forall x_0\in[a,b] =px$ , 所以能被 $k$ 整除的数字序列即为：
$$
x,2x,3x,...,px
$$
所以能被 $k$ 整除的数字就有 $p$ 个。

我们又设 $x=rk$ 。

所以原序列又可以表示为：
$$
rk,2rk,3rk,...,prk
$$
因为是等差数列，公差为 $k$

所以项数 $p=\frac{prk-rk}{k}+1$

(得证)

求第一个能被 $k$ 整除的数用除法就行了。

### Code.

```cpp

#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define dep(i, r, l) for (int i = r; i >= l; i--)
using namespace std;
const int inf = 1e9, mod = 1e8;
template <typename T>
void read (T &x) {
    x = 0; T f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar ();
    }
    x *= f;
}
char For_Print[25];
template <typename T>
void write (T x) {
    if (x == 0) { putchar ('0'); return; }
    if (x < 0) { putchar ('-'); x = -x; }
    int poi = 0;
    while (x) {
        For_Print[++poi] = x % 10 + '0';
        x /= 10;
    }
    while (poi) putchar (For_Print[poi--]);
}
template <typename T>
void print (T x, char ch) {
    write (x); putchar (ch);
}
int k, a, b;
signed main() {
	read(k), read(a), read(b);
	int t;
	if (a % k == 0) t = a;
	else {
		int x = a / k;
     	//保险起见三个都找一遍
		if (k * (x - 1) > a) t = k * (x - 1);
		else if (k * x > a) t = k * x;
		else t = k * (x + 1);
	}
	if (t <= b) write((b - t) / k + 1);
	else write(0);
	return 0;
}

```



---

## 作者：qwq___qaq (赞：0)

$O(1)$ 的顺序结构题。

首先，我们分两种情况讨论：$a$ 和 $b$ 在数轴同侧异侧。

如果为同侧，那么，我们只需要把两边的贡献加起来即可，答案为 `b/k-a/k+1`。

如果在异侧，那么我们只需要把贡献值减去即可，如果都是负数，那么就是 `a/l-(b+k-1)/k+1`；如果都是正数，那么就是 `b/l-(a+k-1)/k+1`。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long k,a,b,ans;
	cin>>k>>a>>b;
	k=abs(k);
	if((a<0&&b<0)||(a>0&&b>0)){
		a=abs(a),b=abs(b);
		if(a>b)
			swap(a,b);
		ans=b/k-(a+k-1)/k+1;//a 是向上取整
	} else
		ans=b/k-a/k+1;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

这道题我的思路是：

如果一开始 $a$ 和 $b$ 都小于 $0$，那么交换它们的绝对值（要保证 $a < b$）


之后，如果 $a$ 和 $b$ 都大于 $0$，则直接输出 $b\,/\,k\,-\,(a-1)\,/\,k$（$n\,/\,k$ 表示 $[1,n]$ 中 $k$ 的倍数的个数）；否则输出 $[1,b]$ 中 $k$ 的倍数的个数 $+$ $[a,-1]$ 中 $k$ 的倍数的个数 $+$ $1$（这里再 $+1$ 是因为 $0$ 是任何数的倍数）。

**注意开 $long$ $long$。**

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll k, a, b;
    scanf("%lld%lld%lld", &k, &a, &b);
    if (a < 0 && b < 0)
    {
        ll t = abs(a);
        a = abs(b);
        b = t;
    }
    if (a > 0 && b > 0) printf("%lld", b / k - (a - 1) / k);
    else printf("%lld", b / k + abs(a) / k + 1);
    return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF597A 【Divisibility】

### 题意分析

寻找在区间$[a,b]$中可以被$k$整除的数字个数。

难点就是这里会有负数出现。

苣佬门都说是~~恶评~~简单数论，可我却交了十次才过，佩服造数据者的全面！

### $SOLUTION$

$a>=0$&&$b>=0$ $ans=calc(abs(b))-calc(abs(a-1))$

$a<=0$&&$b>=0$ $ans=calc(b)+calc(a)+1$

$a<=0$&&$b<=0$ $ans=calc(abs(a))-calc(abs(b+1))$

注意事项：

$0$不要忘记算

### $CODE$

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll k,a,b,ans;

ll calc(ll x){
	return x/k;
}
int main(){
	scanf("%lld%lld%lld",&k,&a,&b);
	if(a<0&&b<0)
		ans=calc(b+1)-calc(a);
	else if(a>0&&b>0)
		ans=calc(b)-calc(a-1);
	else
		ans=calc(b)-calc(a)+1;
	printf("%lld",ans);
    return 0;
}

```

$wtrl$

---

