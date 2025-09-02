# [USACO25FEB] Transforming Pairs S

## 题目描述

聪明奶牛 Bessie 发现了一种新的迷恋——数学魔法！一天，当她在 Farmer John 牧场的草地上小跑时，她偶然发现了两堆有魔法的干草。第一堆包含 $a$ 捆干草，第二堆包含 $b$ 捆干草（$1\le a,b\le 10^{18}$）。

在干草堆边上，半埋在泥土里，她发现了一卷古老的卷轴。当她展开卷轴时，发光的字母揭示了一个预言：

奉大草原之令，被选中者需令此平凡之干草堆转为恰好 $c$ 捆及 $d$ 捆——不可多，亦不可少。

Bessie 意识到她只能施展以下两种魔法：

- 她可以施法召唤新的干草捆以增加第一堆的大小，增加的数量等于当前第二堆的数量。
- 她可以施法召唤新的干草捆以增加第二堆的大小，增加的数量等于当前第一堆的数量。

她必须逐次执行这些操作，但可以任意顺序执行任意多次。她必须恰好使第一堆达到 $c$ 捆，第二堆达到 $d$ 捆（$1\le c,d\le 10^{18}$）。

对于 $T$（$1\le T\le 10^4$）个独立的测试用例中的每一个，输出实现预言所需的最小操作次数，或者如果不可能实现时输出 -1。

## 说明/提示

样例 1 解释：

在第一个测试用例中，由于 $b>d$，但操作只可能增加 $b$，因此不可能实现。

在第二个测试用例中，最初两堆有 $(5, 3)$ 捆。Bessie 可以将第一堆增加第二堆的数量，得到 $(8, 3)$ 捆。然后 Bessie 可以将第二堆增加第一堆的新数量，并执行该操作两次，得到 $(8, 11)$ 并最后得到 $(8, 19)$ 捆。这与 $c$ 和 $d$ 一致，且是达到目标的最小操作次数。

注意，第三个测试用例的答案与第二个不同，因为 $c$ 和 $d$ 的值交换了（堆的顺序有影响）。

在第四个测试用例中，不需要任何操作。

- 测试点 $3\sim 4$：$\max(c, d) \le 20 \cdot\min(a, b)$。
- 测试点 $5\sim 7$：$T \le 10$ 且 $a,b,c,d\le 10^6$。
- 测试点 $8\sim 12$：没有额外限制。

## 样例 #1

### 输入

```
4
5 3 5 2
5 3 8 19
5 3 19 8
5 3 5 3```

### 输出

```
-1
3
-1
0```

## 样例 #2

### 输入

```
1
1 1 1 1000000000000000000```

### 输出

```
999999999999999999```

# 题解

## 作者：封禁用户 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P11841)

赛时 AC 了 T2T3，就差 T1 没调出来（恼。

一道很简单的数学题，可以逆向推回答案。首先目标数量小于初始数量肯定无解，因为操作只能增加数量。如果目标数量等于初始数量则不需要进行操作。否则进行逆向推导，如果第一堆的目标数量大于第二堆的目标数量，就尝试从第一堆中减去若干个第二堆的数量，如果无法实现就是无解。同理，如果第二堆的目标数量大于第一堆的目标数量，就尝试从第二堆中减去若干个第一堆的数量。如果最后目标数量等于初始数量就可以实现，否则无解。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

LL Calc(LL a, LL b, LL c, LL d) {
  if (c < a || d < b) return -1;
  if (c == a && d == b) return 0;
  LL ans = 0;
  while (c > a || d > b) {
    if (c > d) {
      if (d == 0) return -1;
      LL k = (c - a) / d;
      if (k == 0) return -1;
      c -= k * d;
      ans += k;
    } else if (d > c) {
      if (c == 0) return -1;
      LL k = (d - b) / c;
      if (k == 0) return -1;
      d -= k * c;
      ans += k;
    } else return -1;
  } if (c == a && d == b) return ans;
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  LL T;
  cin >> T;
  while (T--) {
    LL a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << Calc(a, b, c, d) << "\n";
  } return 0;
}
```

---

## 作者：littlebug (赞：7)

有人：数论只会 gcd！（鉴定为 fAKe）

而我：连 gcd 都不会！/ll

## Solution

因为从 $a,b$ 推 $c,d$ 比较复杂，情况比较多，所以考虑反过来，用 $c,d$ 推 $a,b$。

这时候有一个很重要的性质：

> 考虑一次操作 $x,y \to x+y,y$，那么一定有 $x+y > x,y$，所以操作后比较大的那个数一定是被操作的那个数！

于是，我们可以每次用 $c,d$ 中大的数减小的数。所以不妨假设 $c>d$，那么会发现执行 $k$ 次 $c \gets c-d$ 相当于 $c \gets c-kd$，看起来很像一个 gcd 的过程，所以考虑转化为 $c \gets c -  \lfloor \frac c d \rfloor \times d$ 的形式。

但是这样不好判断 $a$ 是否出现在了这一过程中，所以不妨直接令 $c \ge a$，于是就变成了 $c \gets c -  \lfloor \frac {c-a} d \rfloor \times d$，这样就可以保证 $c$ 总是 $\ge a$ 了。

不过这样在无解的时候可能会导致无限循环，也就是说 $\lfloor \frac {c-a} d \rfloor$ 一直等于 $0$，所以可以把这个值和 $1$ 取个 $\max$，这样就保证了不会出现无限循环，也不会影响 $a$ 是否出现的判断。

时间复杂度只有一只 $\log$，虽然我懒得算 $\log$ 的是什么了，但是显然可过。

## Code

```cpp
int a,b,c,d;

il void solve(int __Ti)
{
	read(a,b,c,d);
	
	int ans=0;
	while(c!=a || d!=b)
	{
		if(c<a || d<b) {ans=-1; break;}
		
		c<d && (swap(c,d),swap(a,b),1);
		ans+=max((c-a)/d,1ll);
		c-=max((c-a)/d,1ll)*d;
	}
	
	write(ans,'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：hanyu0722 (赞：4)

### 题目链接

[P11841 [USACO25FEB] Transforming Pairs S](https://www.luogu.com.cn/problem/P11841)

### 题目思路

依据题目中的思路，我们应该从 $a,b$ 推到 $c,d$，但这样会导致操作方案太多，把问题极度复杂化，于是我们选择从 $c,d$ 推到 $a,b$。

具体地，我们需要选择 $c$ 与 $d$ 中较大的一个，将其减去较小的一个。我们很容易发现，这里的操作极度类似于**更相减损术**。由于更相减损术本质上是在求最大公因数，我们只需使用欧几里得算法求解即可。



### 代码时间


[link](https://www.luogu.com.cn/record/205986730)

code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//usaco S 3
int a,b,c,d,ans;
void gcd(int x,int y){
	if (x==a){
		if (y<b){
			ans=-1;
			return ;
		}
		if ((y-b)%a==0){
			ans+=(y-b)/a;
			return ;
		}
		else{
			ans=-1;
			return ;
		}
	}
	if (y==b){
		if (x<a){
			ans=-1;
			return ;
		}
		if ((x-a)%b==0){
			ans+=(x-a)/b;
			return ;
		}
		else{
			ans=-1;
			return ;
		}
	}
	if (x==0 || y==0){
		ans=-1;
		return ;
	}
	//
	if (x>y){
		ans+=x/y;
		gcd(x%y,y);
	}
	else{
		ans+=y/x;
		gcd(x,y%x);
	}
}
void work(){
	cin>>a>>b>>c>>d;
	ans=0;
	gcd(c,d);
	cout<<ans<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while (t--){
		work();
	}
	return 0;
}


```

---

## 作者：Zhl2010 (赞：3)

题目要求从初始状态 $ (a, b) $ 出发，通过两种操作：
- 操作 $1$：令第一堆变为 $ a+b $（第二堆保持不变），即变为 $ (a+b,\, b) $；
- 操作 $2$：令第二堆变为 $ a+b $（第一堆保持不变），即变为 $ (a,\, a+b) $；

经过若干次操作，正向变换目标为 $ (c, d) $。

由于操作只能增加数字，而目标 $ (c, d) $ 必须恰好达到给定值，所以常规的正向搜索可能非常困难。  

**核心思想**：反向思考，从目标 $ (c, d) $ 倒推回初始状态 $ (a, b) $。  

反向操作的规则正好相反：
- 如果上一步执行的是操作 $1$（增加第一堆），那么必定是由 $ (a, b) \to (a+b,\, b) $ 得到的；反过来，从 $ (c, d) $ 可以逆推为 $ (c-d,\, d) $；
- 如果上一步执行的是操作 $2$（增加第二堆），那么必定是由 $ (a, b) \to (a,\, a+b) $ 得到的；反过来，从 $ (c, d) $ 可以逆推为 $ (c,\, d-c) $。

然后我们可以发现反向思考只有一种情况，可以直接做，但注意，可以让一个数一下子减去很多（就可以让代码更快，详见代码）。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,d;

signed main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>d;
		int ans=0;
		while(a!=c||b!=d){
			if(d-b>=c){
				int x=(d-b)/c;
				ans+=x;
				d=d-c*x;
			}else if(c-a>=d){
				int x=(c-a)/d;
//				if(x==0){
//					ans=-1;
//					break;
//				}
				ans+=x;
				c=c-d*x;
			}else{
				ans=-1;
				break;
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
/*


*/


```

---

## 作者：yanqijin (赞：1)

## 题目大意
给你一个局面 $(a,b)$，有如下两个操作：
1. $(a,b)\Rightarrow(a+b,b)$
2. $(a,b)\Rightarrow(a,a+b)$

现在问你可否由局面 $(a,b)$ 转移到局面 $(c,d)$。
## 思路
我们发现如果正着做，有一个局面可以转移到多个局面，处理起来很困难，所以正难则反，我们可以倒着做试试。

首先观察数据，发现 $1\le a,b,c,d\le10^{18}$，所以由 $(a,b)$ 转移出去的局面是正数。其次，可以把 $a>c$ 或 $b>d$ 的局面判掉。

现在题目转化成了给你一个局面 $(c,d)$，有如下两个操作：
1. 若 $c>d$，则$(c,d)\Rightarrow(c-d,d)$
2. 否则 $(c,d)\Rightarrow(c,d-c)$

现在问你可否由局面 $(c,d)$ 转移到局面 $(a,b)$。再次观察，发现这就相当于一个辗转相减，是辗转相除的低级形式，所以考虑转化成辗转相除。

但是辗转相除可能会跳过一些局面，所以当我们发现出现第一个 $c\le a$ 或 $d\le b$ 时，我们就需要考虑将手动减去一些局面。

具体的，设之前跳过的总次数为 $sum$。若 $a=c$ 且 $d-b \bmod a = 0$ 时，答案为 $sum+(d-b)/a$，否则显然。

注意，如果 $a=c$ 且 $d-b \bmod a = 0$ 这个条件还有 $b=d$ 且 $c-a \bmod b = 0$ 都不满足时，则为 $-1$。

时间复杂度 $O(T \log V)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,c,d,g[10005][2],sum1[10005],cnt;
void read(long long &x)
{
	x=0;
	int w=1;
	char ch=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	int sta[100];
	int top=0;
	do
	{
		sta[top++]=x%10,x/=10;
	} while(x);
	while(top) putchar(sta[--top]+48);
	putchar('\n');
}
int main()
{
	read(t);
	while(t--)
	{
		cnt=0;
		read(a);read(b);read(c);read(d);
		if(a>c||b>d) {write(-1);continue;}
		sum1[1]=0;
		g[++cnt][0]=c;
		g[cnt][1]=d;
		while(c&&d)
		{
			if(c>d) sum1[++cnt]=c/d,c%=d;
			else sum1[++cnt]=d/c,d%=c;
			g[cnt][0]=c;
			g[cnt][1]=d;
		}
		long long ans=-1,sum=0;
		for(int i=cnt;i>=1;i--)
		{
			if(a>g[i][0]||b>g[i][1]) continue;
			sum=0;
			for(int j=i;j>=1;j--) sum+=sum1[j];
			if(g[i][0]>g[i][1])
			{
				if(b==g[i][1]&&(g[i][0]-a)%b==0) ans=sum+(g[i][0]-a)/b;
			}
			else
			{
				if(a==g[i][0]&&(g[i][1]-b)%a==0) ans=sum+(g[i][1]-b)/a;
			}
			break;
		}
		write(ans);
	} 
	return 0;
}
```

---

## 作者：qW__Wp (赞：1)

考虑反向操作，从 $(c, d)$ 变为 $(a, b)$，每次可以让 $c, d$ 中一个数减去另一个数。不妨设 $c > d$，则上一步进行的操作必然是 $c \leftarrow c + d$（因为 $c > d$）。

那么思路就很简单了，每次令 $c \leftarrow c - d$ 得到上一次的 $c$，直到 $c = a$ 且 $d = b$ 说明有解，否则若某一时刻 $c < a$ 或 $d < b$ 则无解。

但是这样会在样例 #2 超时，考虑优化。不如直接一步到位，令 $c$ 连续多次减去 $d$ 直到 $c < d$，即令 $c \leftarrow c - \lfloor \frac{c}{d} \rfloor \times d$。但是可能在这之中的某次恰好得到 $c = a$ 且 $d = b$，特判即可，详见代码。

```C++
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T --) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int ans = 0;
		while (a <= c && b <= d) {
			if (a == c && b == d) break;
			if (c < d) swap(a, b), swap(c, d);
				// 不妨设 c >= d 
			if (b == d && (c - a) % d == 0) {
				ans += (c - a) / d;
				c = a;
			} else {
				ans += c / d;
				c -= c / d * d;
			}
		}
		if (a == c && b == d) cout << ans << endl;
		else cout << -1 << endl;
	} 
	return 0;
}
```

---

## 作者：PDAST (赞：1)

# T3
## 题目大意
有两堆石子，分别有 $a$ 和 $b$ 个石子，每次可以使 $a=a+b$ 或 $b=b+a$，请问要使得 $a=c$ 且 $b=d$ 最少需要几次操作，或输出不可能（$-1$）。
## 思路
从小往大推比较困难，不如思考从大往小推，我们发现，当一个数比另一个数大时，大的数肯定是由某个数加上若干倍的较小的数得到，所以每次将大的减小的，直到有数小于等于目标数即可。由于时间无法接受，考虑优化，可以直接一次减去全部可以减去的，留下 $d \mod c$ 或 $c \mod d$，直到剩下的数均小于等于其所对应的目标，注意，如果剩下 $0$，则把另一个数加上并退出循环，最后判断剩下的是否与目标相等即可。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
signed main(){
	// freopen("pairs.in", "r", stdin);
	// freopen("pairs.out", "w", stdout);
    short T=read();
    while(T--){
        int a=read(),b=read(),c=read(),d=read(),s=0;
        while(c>a&&d>b){
            if(c>d)s+=(c-1)/d,c-=(c-1)/d*d;
            else s+=(d-1)/c,d-=(d-1)/c*c;
            // cout<<c<<" "<<d<<"\n";
            if(c==d&&c!=a&&b!=d)break;
        }
        if(c==a&&b<=d&&(d-b)%a==0)cout<<(int)(s+(d-b)/a)<<"\n";
        else if(d==b&&a<=c&&(c-a)%b==0)cout<<(int)(s+(c-a)/b)<<"\n";
        else cout<<"-1\n";
    }
}
~~~

---

## 作者：_zhouyixuan_ (赞：1)

本题由于 $a,b$ 都为正整数，所以每次施展魔法时被施展魔法的那一堆干草数量一定大于另一堆。

从反面考虑，我们可推出**当前数量大的一堆在上一轮一定被施展了魔法**。

如果倒推，则容易可以推出最终状态能否还原成原状态。

但由于直接减超了，只能考虑优化，采用类似辗转相除的“辗转相模”。

代码如下：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int a,b,c,d,ans=0,f=0;
		cin>>a>>b>>c>>d;
		while(c>=a&&d>=b)
		{
			if(c==a&&d==b) 
			{
				cout<<ans<<"\n";
				f=1;
				break;
			}
			if(c==d) break;
			if(c==a)
			{
				if(c>d||(d-b)%c!=0) break;
				ans+=(d-b)/c;
				cout<<ans<<"\n";
				f=1;
				break;
			}
			else
			{
				if(d==b)
				{
					if(d>c||(c-a)%d!=0) break;
					ans+=(c-a)/d;
					cout<<ans<<"\n";
					f=1;
					break;
				}
				else
				{
					if(c>d)
					{
						ans+=c/d;
						c%=d;
						if(c<a&&(a-c)%d==0) ans-=(a-c)/d,c=a;
					}
					else
					{
						ans+=d/c;
						d%=c;
						if(d<b&&(b-d)%c==0) ans-=(b-d)/c,d=b;
					}
				}
			}
		}
		if(!f)cout<<-1<<"\n";
	}
    return 0;
}

```
( 有点丑 )

---

## 作者：Colinxu2020 (赞：1)

考虑将操作反过来，用 $c,d$ 去构造 $a,b$，因为任意时刻 $a,b \gt 0$，所以 $a+b \gt a,b$，因此我们只需要用 $c,d$ 中较大（$a+b$）的减去较小（$a/b$）的就可以得到这一次操作前的两个数的值，朴素的做法是暴力模拟这个过程，然后直接判定是否有 $a=c,b=d$。

但这样复杂度直接炸了，观察到这个过程和 $\gcd$ 的过程很像，考虑用类似的每次让 $c \gets c \bmod d$ 的方式来优化，讨论如何判断在 $\gcd$ 的过程中出现了 $a=c,b=d$ 的情况，如果 $c \bmod d \lt a \leq c$，那么说明在 $\gcd$ 的过程中路过了点 $a$，因此判断一下如果 $d=b$ 且 $a \equiv c  \pmod d$，则输出 $(c-a) \div d$，否则无解，$d \bmod c$ 同理处理即可，利用和 $\gcd$ 类似的分析，复杂度为 $O(\log \min(c,d))$。 

代码：

```cpp
#include<iostream>
#include<cassert>
using namespace std;

#define ll long long
ll a,b,c,d;

int main(){
    int T; cin>>T;
    while(T--){
        cin>>a>>b>>c>>d;
        if(a>c||b>d){
            cout<<-1<<endl;
            continue;
        }
        bool flag=false; ll cnt=0;
        while(true){
            if(a==c&&b==d){
                flag=true; cout<<cnt<<endl;
                break;
            }
            if(d>c){
                if(b>d%c){ // d%c<b<=d
                    if(b%c!=d%c)break;
                    if(c!=a)break;
                    cout<<cnt+(d-b)/c<<endl;
                    flag=true;
                    break;
                }
                cnt+=d/c; d%=c;
            }else{
                if(a>c%d){ // c%d<a<=c
                    if(c%d!=a%d)break;
                    if(b!=d)break;
                    cout<<cnt+(c-a)/d<<endl;
                    flag=true;
                    break;
                }
                cnt+=c/d; c%=d;
            }
        }
        if(!flag)cout<<-1<<endl;
    }
}
```

---

## 作者：Your_Name (赞：1)

## 题解

首先，我们考虑把整个过程倒过来做，那么我们的操作其实也就抽象为 $c,d$ 每次可以减去若干个另一捆，最后变成 $a,b$。

那么我们先把减去若干个另一捆看成一次操作。

然后我们发现，如果当前 $c>d$，那么下一次操作只能是把 $c$ 减去若干个 $d$。反之同理。

那么我们考虑这一次操作能进行的次数即为 $\min\{\lfloor \frac{c-a}{d}\rfloor,\lfloor \frac{c}{d}\rfloor\}$。

显然前者是小于等于后者的，那么我们直接操作这么多次就行。

无解显然就是不能操作并且当前 $[a\not =c\lor b\not =d]$。

复杂度可以类比辗转相除求 $\gcd$，是 $O(\log V)$ 的。

那么总复杂度即为 $O(T\log V)$，可以通过。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a, b, x, y, ans, T;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while(T --){
        ans = 0;
        bool fl = 1;
        cin >> a >> b >> x >> y;
        while(x != a || y != b){
            if(x < y)swap(x, y), swap(a, b);
            LL k = (x - a) / y;
            if(k <= 0){fl = 0;break;}
            ans += k;
            x -= k * y;
        }
        if(fl)cout << ans << '\n';
        else cout << "-1\n";
    }
    return 0;
}
```

_完结撒花。_

---

## 作者：ThisIsLu (赞：0)

考虑倒着做，就发现变成了每一次可以 $c \gets c-d$ 或 $d \gets d-c$。

当 $c=d$ 时，则要么不变要么变为 $(c,0)$ 或是 $(0,c)$，分别判断即可。

否则，必然为大的减小的，不妨假设 $c<d$。

若 $c=0$，则无论如何都改变不了，判断即可。

否则，我们就可以辗转相除，如果 $c\ne a$，那么直至变为 $(c,d \bmod c)$，然后加上 $\left\lfloor\dfrac{d}{c}\right\rfloor$，否则判断是否 $b<d$ 且 $b \bmod c=d\bmod c$，操作次数为 $\dfrac{d-b}{c}$。

$c>d$ 的情况同理。

根据辗转相除法可知单次询问复杂度 $O(\log V)$（$V$ 为值域）。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d;
long long query(long long x,long long y){
    if(x<a||y<b) return -1;
    if(x==a&&y==b) return 0;
    if(x==0){
        if(y!=b) return -1;
        return 0;
    }
    if(y==0){
        if(x!=a) return -1;
        return 0;
    }
    if(x<y){
        if(x==a){
            if((y-b)%a!=0) return -1;
            return (y-b)/a;
        }
        long long tmp=query(x,y%x);
        if(tmp==-1) return -1;
        return tmp+y/x;
    }
    if(x==y){
        if(a==x&&b==0){
            return 1;
        }
        if(a==0&&b==x) return 1;
        return -1;
    }
    if(y==b){
        if((x-a)%b!=0) return -1;
        return (x-a)/b;
    }
    long long tmp=query(x%y,y);
    if(tmp==-1) return -1;
    return tmp+x/y;
}
void solve(){
    cin>>a>>b>>c>>d;
    cout<<query(c,d)<<"\n";
}
signed main(){
    int T=1;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

正着思考，我们发现会有一堆子选择；但是倒着思考，我们发现只有一种选择。也就是说，其实倒着来，只有一种选择可行。因此直接模拟就完了。

毕竟，每次操作本质上是将其中一个数替换为二者的和，因此只能是更大的那个减更小的那个。注意一定不要让 $c,d$ 减的小于 $a,b$ 了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, a, b, c, d, ans;
inline int dec() {
	if (c < a || d < b) return -5e18;
	if (a == c) {
		int rc = (d - b);
		if (rc % a) return -5e18;
		d = b;
		return rc / a;
	}
	if (b == d) {
		int rc = (c - a);
		if (rc % b) return -5e18;
		c = a;
		return rc / b;
	}
	if (d > c) {
		int dec = min((d - c) / c, (d - b) / c);
		ans += dec; d -= dec * c;
		if (d == b) return 0;
		if (d == c) return -5e18;
		d -= c; ans++;
	}
	else {
		int dec = min((c - d) / d, (c - a) / d);
		ans += dec; c -= dec * d;
		if (c == a) return 0;
		if (d == c) return -5e18;
		c -= d; ans++;
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> a >> b >> c >> d; ans = 0;
		while ((a != c || b != d) && ans >= 0) ans += dec();
		cout << (ans >= 0 ? ans : -1) << endl;
	}
}
```

---

## 作者：MoonCake2011 (赞：0)

赛时 AK 了，这是银组最简单的一道题。

看到由 $a$，$b$ 变为 $c$，$d$ 我们发现正向不好做，尝试逆向。

设 $f(c,d)$ 为答案。

我们发现，每次如果 $d>c$，那么 $f(c,d)=f(c,d-c)+1$ 否则 $f(c,d)=f(c-d,d)+1$。

又注意到，这是求最大公约数的辗转相减法，虽然支持了线性，但是奈何 $c$ 与 $d$ 太大，我们需要对数级别复杂度才能通过。

不难想到用辗转相减法。

于是发现 $f(c,d)=f(c,d \bmod c)+\dfrac{d-d \bmod c}{c}$，另一种情况同理，于是可以通过。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
inline int forwardgcd(int x,int y){
	if(x<y){
		if(x==0) return -1;
		if(a==x && y%x<=b && b<=y && b%x==y%x) return (y-b)/x;//这里就直接得出答案
		int t=forwardgcd(x,y%x);
		if(t==-1) return -1;
		else return t+(y-y%x)/x;
	}
	else{//以下同理
		if(y==0) return -1;
		if(b==y && x%y<=a && a<=x && a%y==x%y) return (x-a)/y;
		int t=forwardgcd(x%y,y);
		if(t==-1) return -1;
		else return t+(x-x%y)/y;
	}
}
inline void solve(){
	cin>>a>>b>>c>>d;
	cout<<forwardgcd(c,d)<<"\n";
}
signed main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：iced_tea543 (赞：0)

## 引言：
我们来看看 2 月银组的第三题。本题难度不高。

## 题解：
题目需要我们把两个变量 $a$ 和 $b$ 的值相互叠加，问是否能够得到 $c$ 和 $d$。很显然正着模拟这个过程非常困难。那么考虑正难则反，我们倒着执行这个过程。

观察发现，由于最后的结果一定是通过把两个数中小的那一个数加上大的那一个数若干次得到的。因此每次必定需要让大的数减去小的数，这个操作策略很显然是固定的。于是代码很容易就可以写出来了。

但是测试第二个样例就可以发现，由于减的次数太多，程序执行会超时。仔细观察可以想到，我们本来的方法就是辗转相减法，我们需要把它改成辗转相除即可。

不必重新写程序，直接在源程序上把减法改成 mod，通过除法计算操作次数。

最后需要注意，直接取模可能会取过头，每次取模之后特判一下即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int T;
	cin >> T;
	while (T--) {
		long long a, b, c, d;
		cin >> a >> b >> c >> d;
		long long cnt = 0;
		while (c > a or d > b) {
			if (c == d) {
				cout << -1 << endl;
				goto end;
			}
			if (c > d) {
				cnt += c / d - (c % d == 0), c = (c % d == 0 ? d : c % d);
				if ((a - c) % d == 0 and b == d) {
					cout << cnt - (a - c) / d << endl;
					goto end;
				}
			}
			else {
				cnt += d / c - (d % c == 0), d = (d % c == 0 ? c : d % c);
				if ((b - d) % c == 0 and a == c) {
					cout << cnt - (b - d) / c << endl;
					goto end;
				}
			}
		}
		if (a == c and b == d)
			cout << cnt << endl;
		else
			cout << -1 << endl;
	end:;
	}
}
```

---

## 作者：_EternalRegrets_ (赞：0)

### 题意描述：
>给定 $(a,b)$，现在可以使其变为 $(a,a+b)$ 或 $(a+b,b)$。求是否存在一种可以构造出 $(c,d)$ 的方案及其操作个数。

### Solution:

__正难则反。__

转化题意：考虑如何从 $(c,d)$ 转化回到 $(a,b)$，即可以使其变为 $(c-d,d)$ (此处假设 $c > d$)。

稍微手玩一下比较容易发现它很像 __辗转相除__ 法求 $\gcd$。

于是，就可以考虑递归来求解转化题意。

详见代码。

### code:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a,b,c,d;
int solve(int x,int y){
    //cout<<x<<" "<<y<<endl;
    if(x<y){
        if(x==0){
            return -1;
        }

        if(x==a && (y-b)%a==0 && y%a<=b && y>=b){
            //cout<<y-b<<" "<<a<<" "<<(y-b)%a<<endl;
            return (y-b)/a;
        }

        int tmp; tmp=solve(x,y%x);

        if(tmp==-1){
            return -1;
        }
        else{
            return tmp+y/x;
        }
    }
    else{
        if(y==0){
            return -1;
        }

        if(y==b && (x-a)%b==0 && x%b<=a && x>=a){
            return (x-a)/b;
        }

        int tmp; tmp=solve(x%y,y);

        if(tmp==-1){
            return -1;
        }
        else{
            return tmp+x/y;
        }
    }
}

signed main(){
    int T; cin>>T;
    while(T--){
        cin>>a>>b>>c>>d;
        if(a>c || b>d){
            cout<<-1<<endl;
        }
        else{
            cout<<solve(c,d)<<endl;
        }
    }

    return 0;
}

```

---

