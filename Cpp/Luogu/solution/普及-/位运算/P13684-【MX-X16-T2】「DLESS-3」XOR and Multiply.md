# 【MX-X16-T2】「DLESS-3」XOR and Multiply

## 题目描述

给定非负整数 $x, y, h$，保证 $0 \le x, y < 2^h$，你需要找到一个整数 $z$ 使得 $0\le z<2^h$ 且 $(x\oplus z)\times(y\oplus z)$ 最大，求这个最大值。

其中 $\oplus$ 表示按位异或运算。

## 说明/提示

**【样例解释 #1】**

每一组数据分别可能选取的 $z$ 为 $3,0,1,2,4$。

**【数据范围】**

对于所有数据，保证 $1\le T\le 10^6$，$0\le x,y<2^h$，$1\le h\le 30$。

各测试点特殊限制如下：

|测试点编号|$T\le$|$h\le$|
|:-:|:-:|:-:|
|$1,2$|$5000$|$12$|
|$3\sim 5$|$10^6$|$30$|

## 样例 #1

### 输入

```
5
0 0 2
1 0 1
0 3 2
1 0 2
3 3 3```

### 输出

```
9
0
2
6
49```

## 样例 #2

### 输入

```
3
213467858 78934 30
789432278 948729048 30
114514 1919810 22```

### 输出

```
934398046840059525
763270444894761743
10523686794257```

# 题解

## 作者：zengyongxu (赞：3)

::::warning[警告]
请不要抄题解。
::::

::::info[约定]
约定 $x$ 的第 $y$ 位是指 $x$ 在二进制下从低到高数第 $y$ 位，且标号从 0 开始。
::::

是道橙题，看了一会儿，还挺好想，就是代码不是很好写。

[题目传送门](https://www.luogu.com.cn/problem/P13684)

### 解题思路

首先，最后我们要求 $(x \oplus z) \times (y \oplus z)$。

那么显然，我们想要 $x \oplus z$，$y \oplus z$ 都尽可能的大。

考虑对于 $z$ 的每一位的情况进行考虑。

分情况讨论，设 $t$ 为当前遍历道的尾数，$x$ 在二进制下这一位上是 $tx$，$y$ 在二进制下这一位上是 $ty$。

如果 $tx = ty$，则为了让 $z \oplus x$ 和 $z \oplus y$ 最大，则 $z$ 这一位上选 $tx$ 取反，这样 $z \oplus x$ 和 $z \oplus y$ 在这一位上都是 1。

否则，如果 $tx \not= ty$，就需要考虑是选 $tx$ 取反还是 $ty$ 取反。

我们考虑选 $tx$ 取反和选 $ty$ 取反的价值：

- 选 $tx$ 取反 —— 这样选最终 $x \oplus z$ 会变大，而 $y \oplus z$ 会不变，价值为 $(y \oplus z)\times 2^t$。
- 选 $ty$ 取反 —— 这样选最终 $y \oplus z$ 会变大，而 $x \oplus z$ 会不变，价值为 $(x \oplus z)\times 2^t$。

然而发现只要让 $t$ 从大到小遍历，则当前状态下的 $x \oplus z$ 和 $y \oplus z$ 的大小就决定了最终的大小。

所以只需要计算当前遍历到 $t$ 位的状态下 $x \oplus z$ 和 $y \oplus z$ 的大小，如果 $x \oplus z$ 大，则 $z$ 的第 $t$ 位为 $ty$ 取反，否则为 $tx$ 取反。

### 具体实现

如上部分所说，我们只需枚举一个 $t$ 即可，这个 $t$ 需要倒序枚举，但是起点是什么呢？

发现题目里 ~~善良的~~ 给出了 $h$ 而到现在为止都没有用过。

发现 $x, y, z$ 满足 $x, y, z < 2^h$，所以最高位最多是第 $h - 1$ 位，于是 $t$ 就从 $h - 1$ 开始枚举即可。

### 代码 & 代码解释

::::success[code]
```cpp
#include <bits/stdc++.h>

using namespace std;

int t, x, y, h;

int main(){
    cin >> t;
    while (t -- ){
        cin >> x >> y >> h;
        int ans = 0;
        for (int i = h - 1; i >= 0; i -- ){
            int tx = (x >> i) & 1;
            int ty = (y >> i) & 1;
            if (tx == ty && tx == 0){
                ans += (1 << i);
            }
            else if (tx != ty){
                if ((ans ^ x) <= (ans ^ y) && tx == 0){
                    ans += (1 << i);
                }
                else if ((ans ^ x) > (ans ^ y) && ty == 0){
                    ans += (1 << i);
                }
            }
        }
        cout << 1ll * (ans ^ x) * (ans ^ y) << "\n";
    }
}
```
::::

代码解释：

代码中 $i$ 就是上文中的 $t$，其他都与上文含义相同。

### 注意：

1. 不要搞反到底是 $tx$ 取反还是 $ty$ 取反
2. 注意最终答案要开 `long long`

### 写在后面

这是一道不错的题目，适合练习思维，也是一道练习对于二进制理解和代码能力的好题。代码不长，但是证明起来并不简单。

---

## 作者：Vct14 (赞：2)

显然每个二进制位的结果互不影响。我们考虑每一个二进制位位。对于每一位，我们尽量使它们均为 $1$。

- 如果两个数的某位相等，则该位我们可以通过异或其取反后的结果使两数均为 $1$。
- 否则，两数该位一定为一个 $0$ 和一个 $1$。可以发现无论 $0$ 和 $1$ 赋给谁，最终两数和是一定的。大家可能听过“和一定，差小积大”（“和同近积大”）。要使两数差尽量小，我们把最高的不相等的位的 $1$ 赋给 $x$，$0$ 赋给 $y$；其余的 $1$ 赋给 $y$，$0$ 赋给 $x$ 即可（反过来也可以）。

简单证明一下“和一定，差小积大”：设定和为 $S$，两数分别为 $\dfrac S2+k$ 与 $\dfrac S2-k$（$k\ge0$）。则两数之积为 $(\dfrac S2+k)(\dfrac S2-k)=\dfrac{S^2}4-k^2$，易知 $k$ 越小积越大。 

实际操作方面：
- 将 $x$ 从低到高第 $i$ 位赋 $1$ 即将 $x$ 按位或 $2^i$（`1<<i`），也就是第 $i$ 位或 $1$，结果为 $1$；其它位或 $0$，结果不变。
- 将 $x$ 从低到高第 $i$ 位赋 $0$ 即将 $x$ 按位与 $2^i$ 按位取反后的结果（`~(1<<i)`），也就是第 $i$ 位与 $0$，结果为 $0$；其它位与 $1$，结果不变。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		long long x,y,h;cin>>x>>y>>h;bool ok=0;
		for(int i=h-1; i>=0; i--){
			long long a=(x>>i)&1,b=(y>>i)&1,c=(1<<i);
			if(a==b) x|=c,y|=c;
			else{
				if(!ok) x|=c,y&=~c,ok=1;
				else y|=c,x&=~c;
			}
		}
		cout<<x*y<<"\n";
	}
	return 0;
}
```

---

## 作者：Dollartree (赞：1)

### 解题思路

1. 容易发现每一位具有独立性，即不同位之间不会影响，可以逐位考虑，如果 $z$ 某一位取了之后会使结果更大，让 $z$ 加上这一位并同时求出答案即可。

### 注意事项

1. 要开 longlong。

2. 最大是 $h-1$ 位，不是 $h$ 位。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
    int x,y,h;
    cin>>x>>y>>h;
    int sum=x*y,temp=0;
    for(int i=h-1;i>=0;--i)
    {
    	int ttemp=(1LL<<i)+temp;
        if((ttemp^x)*(ttemp^y)>=sum)//判断是否比原来更大
        {
            sum=(ttemp^x)*(ttemp^y);
            temp=temp+(1LL<<i);
        }
    }
    cout<<sum<<"\n";
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
```

---

## 作者：__CJY__ (赞：1)

## 思路
从最高位到最低位，逐位确定 $z$ 的每一位是 $0$ 还是 $1$，使得每一步的选择尽可能最大化最终的乘积 $(x \oplus z) \times (y \oplus z)$。

对于每一位 $k$（从高到低），我们检查将这一位置为 $0$ 或 $1$ 后，剩余位可以取的最佳可能值是否能使得乘积更大。

假设当前处理到第 $k$ 位，已经确定了前几位，剩下的低位可以自由选择。对于第 $k$ 位，尝试设置为 $0$ 和 $1$，计算这两种情况下可能的最大乘积的上界，选择上界较大的方向。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long//不开 long long 见祖宗
using namespace std;
ll solve(ll x,ll y,ll h){
	ll z=0;
	for(ll k=h-1;k>=0;k--){//从高到低确定每一位
		ll mask=1<<k,z0=z,z1=z|mask,xz0=x^z0,yz0=y^z0,xz1=x^z1,yz1=y^z1;//mask 是当前处理的位的掩码（如第 k 位为 1，其余为 0），z0 是当前位设为 0 时的 z，z1 是当前位设为 1 时的 z
		ll u0=(xz0|((1ll<<k)-1))*(yz0|((1ll<<k)-1)),u1=(xz1|((1ll<<k)-1))*(yz1|((1ll<<k)-1));//计算当前位设为 0 时的理论上界（剩余位全为 1 时的乘积）和计算当前位设为 1 时的理论上界（剩余位全为 1 时的乘积）
		if(u0>=u1) z=z0;//比较哪个更优
		else z=z1;
	}
	return (x^z)*(y^z);//返回结果
}
int main(){
	ll T;cin>>T;
	while(T--){
		ll x,y,h;cin>>x>>y>>h;
		cout<<solve(x,y,h)<<'\n';
	}
}
```

---

## 作者：ACtheQ (赞：1)

闭眼题

考虑贪心使得异或值更大。

我们将原数 $a$ 与 $b$ 从高位向低位进行二进制拆分，设 $a_i,b_i$ 表示他们在二进制下从高到低的第 $i$ 位。

从高向低依次比较 $a_i$ 与 $b_i$ 的值，若相同则取 $a_i$ 的相反值，这样可以为 $(a\oplus z)$ 与 $(b \oplus z)$ 分别贡献 $2^i$。

对于不同的情况，分别计算 $z$ 这位分别取 $0$ 和 $1$ 的答案，谁对答案的贡献更大就取谁。

---

## 作者：ylch (赞：1)

遇到位运算求最值，首先考虑按位贪心。

对于本题，首先考虑按位分类讨论。对于两个数，它们的每一位有 $4$ 种情况：
```text
0 1
1 0
0 0
1 1
```

发现对于第三种情况就让 $z$ 的这一位变成 $1$，对于第四种情况就让 $z$ 的这一位变为 $0$。

那对于剩下两种情况呢？不难想到可以把 $z=0$ 或 $1$ 的情况都试一试，那个大就留哪个。这其实就是贪心的思想。

下面要考虑贪心的顺序问题，即枚举位数的方向是从高到低还是从低到高？根据贪心的全局最优性，枚举应该是从低位到高位。

---


以下是详细证明：

设 $a = x \oplus z$ 和 $b = y \oplus z$，则 $b = a \oplus c$（其中 $c = x \oplus y$)。目标函数转化为：
$$
(x \oplus z) \times (y \oplus z) = a \times (a \oplus c)
$$
其中 $a$ 的取值范围为 $[0, 2^h)$。

考虑函数 $g(a) = a \times (a \oplus c)$。贪心策略从低位到高位（位索引 $i$ 从 $0$ 到 $h-1$) 逐位确定 $a$ 的每一位，确保每一步的局部选择最大化当前乘积（高位暂时设为 $0$）。

下面将从以下三个方面入手：

1. **位权重主导性**：在决策第 $i$ 位时，该位的权重 $2^i$ 严格大于所有低位权重之和（即 $2^i > 2^{i-1} + 2^{i-2} + \cdots + 1$)。因此，当前位的选择对乘积的影响起主导作用，后续高位的设置不会逆转当前决策的优势。

2. **局部最优性**：设当前已确定低 $i$ 位为 $L$，决策第 $i$ 位时，高位暂时为 $0$。比较 $a = L$ 和 $a = L + 2^i$ 的乘积：
- 若 $g(L) \geq g(L + 2^i)$，则保留当前位为 $0$。
- 否则，设置当前位为 $1$。
这一选择确保了在当前位及低位固定的情况下，该局部解优于其他选择。

3. **全局最优性**：由数学归纳法证明：
- **基础**：当 $i = -1$（无位确定），$sum = 0$ 是唯一选择。
- **归纳**：假设低 $i$ 位已最优确定，为 $L$。决策第 $i$ 位时，选择 $L$ 或 $L + 2^i$ 中使 $g(a)$ 更大的一个。对于任意高位组合 $H$（$H$ 是 $2^{i+1}$的倍数），有：
  
  $$
  g(H + L) = [(x \oplus H) \oplus L] \times [(y \oplus H) \oplus L]
  $$
  
  $$
  g(H + L + 2^i) = [(x \oplus H) \oplus (L + 2^i)] \times [(y \oplus H) \oplus (L + 2^i)]
  $$

  贪心选择的 $L$ 或 $L + 2^i$ 在 $H = 0$ 时已最优，且该优势在任意 $H$ 下保持，因为：
  
  - 函数 $g$ 的结构确保低位决策的优劣不依赖于高位。
  - 贪心后续会优化高位，但不会破坏已确定的低位优势。

综上，只要从低位到高位按位贪心即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
	int x, y, h; cin >> x >> y >> h;
	ll sum = 0;
	for(int i = 0; i < h; i ++){ // 位数从低到高枚举
		ll tmp = sum + (1 << i); // 尝试把第i位变为1
		if((x^sum) * (y^sum) < (x^tmp) * (y^tmp)){
			sum = tmp;
		}
	}
	cout << (x^sum) * (y^sum) << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T; cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：XingYueLi (赞：1)

## 思路

令 $a = x \oplus z$，$b = y \oplus z$。  
目标是最大化 $a \times b$，注意到

$
a \oplus b \;=\; (x\oplus z)\oplus(y\oplus z)\;=\;x\oplus y \;=\; w.
$

也就是说不管怎么选 $z$，总有$a \oplus b=x \oplus y$。

因此问题等价于：在 $0\le a,b<2^h$ 且 $a\oplus b = x \oplus y$ 的条件下，使 $a\times b$ 最大。

从高位到低位（第 $h-1$ 位到第 0 位）考虑：

- 若 $w_i = 0$（$a_i=b_i$）：  
  为了增大两个数，把两个数的**这一位都设为 1**。

- 若 $w_i = 1$（$a_i\ne b_i$）：  
  为了让乘积最大，应让 $a$ 与 $b$ **尽量接近**（在给定总和下，乘积随差值变小而变大），所以把这一位的 1 给当前较小的那个数。

这样贪心构造得到的 $a,b$ 就使乘积最大，最后答案是 $a\times b$。

---

## Code

```cpp
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long x, y, h;
        cin >> x >> y >> h;

        long long w = x ^ y;
        long long a = 0, b = 0;

        for(int i = h - 1; i >= 0;i--){
            if((w >> i) % 2 == 0){
                // a_i 与 b_i 相等
				a += (1 << i);
				b += (1 << i);
            }
			else {
                // a_i 与 b_i 不等
                if(a < b){
                    a += (1 << i);
                }
				else{
                    b += (1 << i);
                }
            }
        }

        cout << a * b << endl;
    }
    return 0;
}
```

---

## 作者：Pratty (赞：1)

难度预估：橙/黄。

对于任意两个满足要求的 $x,y$，要使得 $(x\oplus z)\times(y\oplus z)$ 最大，很显然我们要让 $x,y$ 的二进制与 $z$ 有尽可能多的位数不相同。

这时候就要分两种情况，如下。

- 若 $x$ 和 $y$ 的每一位都相同（二进制下）：
  - $h=6$。
  - $x=(00101)_2$。
  - $y=(00101)_2$。
  
  此时要让 $z$ 的二进制与 $x,y$ 有尽可能多的位不同，所以 $z$ 的每一位与以上的每一位都要取反，即：
  
  - $z=(11010)_2$。


- 若 $x$ 和 $y$ 的有某些位不同（二进制下）：
  - $h=6$。
  - $x=(00101)_2$。
  - $y=(00111)_2$。
  
  此时要让 $z$ 的二进制与 $x,y$ 有尽可能多的位不同，所以在 $x,y$ 相同的位上 $z$ 的每一位与以上的每一位都要取反，即：
  
  - $z=(110?0)_2$。
 
那么 $?$ 处该填入什么数字呢？

显然，对于任意的 $x,y$，$z$ 中的所有 $?$ 一定是 $x$ 和 $y$ 的二进制位当中不同的地方。

我们发现答案是两者乘积，则当这两者的值最接近的时候一定是最大乘积，而现在我们能改变的只有所有二进制下 $z$ 中的 $?$ 位。

我们知道，对于一个 $1$ 后面是 $k$ 个 $0$ 的二进制数，一定大于所有长度 $\le k$ 的二进制数。

所以如果我们在 $z$ 中的第一个位置放入与 $y$ 相同的值（即与 $x$ 当前这一位异或会产生贡献），其他位置放入与 $x$ 相同的值（即与 $y$ 当前这一位异或会产生贡献）。这时候由 $x$ 和由 $y$ 产生的贡献一定是最接近的，且由 $y$ 产生的贡献一定多于由 $x$ 产生的。故此时两者的乘积一定最大。

最后放上赛时手搓代码：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, x, y, h;
signed main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld%lld%lld", &x, &y, &h);
		int ans = 0, lst = -1;
		for (int i = 0; i < h; i++) {
			if (((x >> i) & 1) != ((y >> i) & 1)) {
				ans += (1LL << i) * ((x >> i) & 1);
				lst = i;
			} else {
				ans += (1LL << i) * (1 - ((x >> i) & 1));
			}
		}
		if (lst > 0) {
			ans -= (1LL << lst) * ((x >> lst) & 1);
			ans += (1LL << lst) * ((y >> lst) & 1);
		}
		printf("%lld\n", (x ^ ans) * (y ^ ans));
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

首先我们记 $x$ 的第 $b$ 位为 $f(x,b)$。

逐位考虑，如果 $f(x,b)=f(y,b)$，那么我们取 $f(z,b)=1-f(x,b)$。如果 $f(x,b) \neq f(y,b)$，我们令 $S=\{b\mid f(x,b) \neq f(y,b)\}$，若 $b$ 为 $S$ 中的最大值，取 $f(z,b)=1-f(x,b)$，否则取 $f(z,b)=f(x,b)$。

核心代码：

```cpp
int x,y,h;
void solve()
{
  x=R,y=R,h=R;
  int t=x^y;
  int a=0,b=0,fst=0;
  rep(i,h-1,0)
  {
    if(t>>i&1)
    {
      if(!fst) a+=(1ll<<i),fst=1;
      else b+=(1ll<<i);
    }
    else
    {
      a+=(1ll<<i);
      b+=(1ll<<i);
    }
  }
  write(a*b),puts("");
}
void main(){
  MT solve();
}
```

---

## 作者：a18981826590 (赞：0)

# [P13684 【MX-X16-T2】「DLESS-3」XOR and Multiply](https://www.luogu.com.cn/problem/P13684)
## 解题思路

设 $a_{i}$ 表示 $a$ 在二进制下的第 $i$ 位，$a'$ 表示 $a \oplus z$。

我们对 $x,y$ 在二进制下的每一位进行分析。

1. 若 $x_{i}$ 与 $y_{i}$ 相等，则直接使 $x'_{i}=y'_{i}=1$ 即可。

2. 若 $x_{i}$ 与 $y_{i}$ 不相等，则无论 $z_{i}$ 怎么取，$x'_{i}+y'_{i}$ 始终为 $1$；则在保证情况 $1$ 时，$x'+y'$ 为定值，此时使 $x'-y'$ 最小即可；故对于情况 $2$ 的最高位 $j_{0}$，使 $x_{j_{0}}=1$，对于情况 $2$ 的其余位 $j$，使 $y_{j}=1$ 即可。
## [AC](https://www.luogu.com.cn/record/230161292) 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool b;
long long int n,t,x,y,z;
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>x>>y>>z;
		b=0;
		for(int i=z-1;i>=0;i--){
			if(((x>>i)&1)==0&&((y>>i)&1)==0){
				x+=(1<<i);
				y+=(1<<i);
			}
			else if(((x>>i)&1)!=((y>>i)&1)){
				if(b){
					if(((y>>i)&1)==0){
						y+=(1<<i);
						x-=(1<<i);
					}
				}
				else{
					if(((x>>i)&1)==0){
						x+=(1<<i);
						y-=(1<<i);
					}
					b=1;
				}
			}
		}
		cout<<x*y<<'\n';
	}
	return 0;
}
```

---

## 作者：M1__ (赞：0)

# 题解：P13684 【MX-X16-T2】「DLESS-3」XOR and Multiply

[Link](https://www.luogu.com.cn/problem/P13684)

## 题目思路

> 异或运算：对于 $x \oplus y$，若 $x$ 和 $y$ 的第 $i$ 位相同，则返回 $0$，否则返回 $1$。

构造 $(x \oplus z)$ 和 $(y \oplus z)$ 的最大乘积。

令 $a=x \oplus z$，$b=y \oplus z$，$f=x \oplus y$，现在我们尽可能的增大 $a \cdot b$ 即可。

我们可以从最高位逐位构造。提取每位 $i$ 的值，将 $i$ 与 $f$ 进行按位与运算。若 $i \mid f=1$，则 $x$ 与 $y$ 在这个数位上不同。这里要记录最高位的 $x$ 与 $y$ 不同的数位的位置。因为数位越高权值越大，所以这里我们最大化 $a$ 的贡献，即令 $a$ 在这个地方位 $1$，$b$ 为 $0$。对应的，在其他的 $b$ 的数位上令其为 $1$ 来增大 $b$ 的值。

若 $i \mid f=0$，显然此时 $x$ 与 $y$ 在这个数位上相同。这时令其为 $1$ 即可最大化贡献。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,x,y,h;
ll read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int main() {
    T=read();
    while (T--){
        x=read(),y=read(),h=read();
        ll f=x^y;
        ll a=0,b=0;
        bool flag=false;
        for(int i=h-1;i>=0;i--){
            ll m=1LL<<i;
            if(f&m){
                if(!flag) a|=m,flag=true;
                else b|=m;
            }
			else a|=m,b|=m;
        }
        cout<<a*b<<"\n";
    }
    return 0;
}

```

时间复杂度 $O(T \cdot h)$。

---

## 作者：Tiger_Rory (赞：0)

约定：我们用 $x_i$ 表示 $x$ 的第 $i$ 位。$y$ 也一样。

我们无需知道 $z$ 具体是多少，我们只要对 $x,y$ 的每位进行操作就行。具体就是将它们转化为二进制后右对齐，若小的那个不足就用 $0$ 补位，然后逐位修改：若 $x_i=y_i=0$，都改为 $1$。若 $x_i=y_i=1$，都不改。若 $x_i\ne y_i$，则将数值小的那个数该位赋值为 $1$，数值大的那个赋值为 $0$，因为差小积大。前提是要确认那个数数值大，如果不确定就先钦定一个。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std; 
const int N = 1e6 + 5; 
int T, x, y, h, a[32], b[32], tot; 
void Solve() {
	cin >> x >> y >> h; 
	if(x < y) swap(x, y); 
	int tx = x, ty = y, maxtot = 0;
	ll newx = 0, newy = 0; 
	memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); 
	tot = 0; while(tx) {
		a[++tot] = tx % 2;
		tx /= 2; 
	} 
	maxtot = tot; 
	tot = 0; while(ty) {
		b[++tot] = ty % 2; 
		ty /= 2; 
	}
	maxtot = max(maxtot, tot);  
	bool flag = 0; 
	for(int i = h; i >= 1; i--) {
		if(a[i] == b[i] && !a[i]) {
			a[i] = b[i] = 1;   
		} else if(a[i] != b[i]) {
			if(flag) b[i] = 1, a[i] = 0;  
			else a[i] = 1, b[i] = 0, flag = 1;//钦定x大 
		}
	}
	int base = 1; 
	for(int i = 1; i <= h; i++) {
		newx += 1ll * a[i] * base; 
		newy += 1ll * b[i] * base; 
		base *= 2; 
	} 
	cout << 1ll * newx * newy << '\n'; 
	return; 
} 
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
	cin >> T; while(T--) Solve(); 
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13684)

---
### 题目大致意思
要最大化表达式 $(x \oplus z) \times (y \oplus z)$ 的值，其中 $\oplus$ 是按位异或运算。其中每组数据包含 $x$, $y$ 和 $h$，并且需要寻找合适的 $z$ 来使得该表达式最大化。

如果你想用暴力枚举，~~那你就用吧~~。一用一个不吱声。

要在这题实现暴力枚举可谓是非常简单，直接枚举 $z$ 到 $2^h - 1$ 就完了。

### TLE code：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long solve(int x, int y, int h) {
    long long max_product = 0;
    // 枚举 z 为 0 到 2^h - 1
    int max_z = (1 << h) - 1; // 最大的 z
    for (int z = 0; z <= max_z; ++z) {
        long long prod = (x ^ z) * (y ^ z);
        max_product = max(max_product, prod);
    }
    return max_product;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int x, y, h;
        cin >> x >> y >> h;
        cout << solve(x, y, h) << "\n";
    }

    return 0;
}
```
此时你会发现，超时了！！！

为了解决超时这个问题，我们要用**按位异或的规律**。
再配上下面三个小妙招，轻松解决。（不知道按位异或的规律是什么的[看这个](https://so.csdn.net/so/search?spm=1000.2115.3001.4498&q=%E6%8C%89%E4%BD%8D%E5%BC%82%E6%88%96%E7%9A%84%E8%A7%84%E5%BE%8B&t=&u=)）
1. **关键操作** $x \oplus y$：通过计算 $t = x \oplus y$，得到 $x$ 和 $y$ 之间的差异。然后根据每一位的差异来调整 $z$，从而影响 $x \oplus z$ 和 $y \oplus z$ 的结果。

2. **高位优先构造 $z$**：我们从高位开始，根据 $t$ 的值来决定每一位的 $z$，如果 $t$ 在当前位上为 1，则这两位的不同会影响最大值，我们需要合理选择 $a$ 和 $b$ 的构造方式。

3. **动态调整 $a$ 和 $b$**：通过调整 $a$ 和 $b$ 的值，来最大化乘积。

### AC code：
```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y, h;
    cin >> x >> y >> h;
    
    int t = x ^ y;  // x 和 y 之间的异或结果
    long long a = 0, b = 0;
    bool fst = false;

    // 从高位向低位进行处理
    for (int i = h - 1; i >= 0; --i) {
        if (t >> i & 1) {  // 如果 t 在第 i 位为 1
            if (!fst) {
                a += (1LL << i);  // 选择将这一位给 a
                fst = true;
            } else {
                b += (1LL << i);  // 选择将这一位给 b
            }
        } else {  // 如果 t 在第 i 位为 0
            a += (1LL << i);  // a 和 b 都加上这一位
            b += (1LL << i);
        }
    }
    
    cout << a * b << endl;  // 输出最大乘积
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
```

---

## 作者：LTTXiaochuan (赞：0)

##### T2 [P13684 【MX-X16-T2】「DLESS-3」XOR and Multiply - 洛谷](https://www.luogu.com.cn/problem/P13684?contestId=265699)

**题目大意**：二进制位小于某数的情况下，将 $x$ 和 $y$ 异或上某个数，求最大乘积。

我们发现，给 $x$ 和 $y$ 同时异或上某数，等于拥有了如下能力：

1. 如果某一位都是 $0$，变成 $1$；
2. 如果某一位都是 $1$，变成 $0$；
3. 调换某一位的 $0/1$。



显然，如果某一位都是 $0$，就可以都变成 $1$；如果某一位都是 $1$，就不用改了。

如果某一位不一样，可以通过异或来调换——此时我们发现，除去上述的“某一位都是 $0$”的情况，$x+y$ 的值将不再发生改变，再根据我们小学一年级就学过的基本不等式可以得到——只需要让 $x,y$ 尽量接近，乘积就会最大。

那么只需要等情况 $3$，将一位大的分给 $x$，剩下的全部给 $y$ 就行了。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int x,y,h;
        cin>>x>>y>>h;

        int nx=0,ny=0,flag=0;
        for(int i=h-1; i>=0; i--)
        {
            if(((x>>i)&1)==((y>>i)&1)) nx+=(1<<i),ny+=(1<<i);
            else if(flag) ny+=(1<<i);
            else
            {
                flag=1;
                nx+=(1<<i);
            }
        }
        cout<<nx*ny<<"\n";
    }

    return 0;
}
```

---

