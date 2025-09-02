# Secret Box

## 题目描述

Ntarsis 有一个边长分别为 $x$、$y$、$z$ 的盒子 $B$。它位于三维坐标系中，范围从 $(0,0,0)$ 到 $(x,y,z)$。

Ntarsis 有一个秘密盒子 $S$。他想选择 $S$ 的尺寸，使得所有边长都是正整数，并且 $S$ 的体积为 $k$。他可以将 $S$ 放在 $B$ 内的某个位置，使得：

- $S$ 与所有坐标轴平行。
- $S$ 的每个顶点都位于整数坐标点上。

$S$ 是魔法盒子，所以当它被放在 $B$ 内的整数位置时，不会掉到地上。

在所有可能选择 $S$ 的尺寸的方式中，求 Ntarsis 能将秘密盒子 $S$ 放在 $B$ 内的不同位置的最大数量。Ntarsis 选定 $S$ 的边长后，不会旋转 $S$。

## 说明/提示

对于第一个测试用例，最优选择 $S$ 的边长为 $2$、$2$、$2$，体积为 $2 \cdot 2 \cdot 2 = 8$。可以证明有 $8$ 种方式将 $S$ 放入 $B$。

每种可能的 $S$ 的左下角坐标为：

1. $(0, 0, 0)$
2. $(1, 0, 0)$
3. $(0, 1, 0)$
4. $(0, 0, 1)$
5. $(1, 0, 1)$
6. $(1, 1, 0)$
7. $(0, 1, 1)$
8. $(1, 1, 1)$

$S$ 放在 $(0, 0, 0)$ 时的示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1985E/47efaaa7005bda1e805807f94ece6c58f2ba3050.png)

对于第二个测试用例，最优选择 $S$ 的边长为 $2$、$3$、$3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
3 3 3 8
3 3 3 18
5 1 1 1
2 2 2 7
3 4 2 12
4 3 1 6
1800 1800 1800 4913000000```

### 输出

```
8
2
5
0
4
4
1030301```

# 题解

## 作者：cute_overmind (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1985E)
### 题目思路
一道组合数学题。

定义：一个体积为 $S$ 的长方体长宽高分别为 $a,b,c$。

由小学知识可得，在 $B$ 放置方案数应为
$$(x-a+1) \times (y-b+1) \times (z-c+1)$$

所以我们只需要按照公式遍历即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t;
void solve()
{
	int x , y , z , m , k;
	int ans = 0;
	cin >> x >> y >> z >> m;
    for (int i = 1; i <= x; i++){
        for (int j = 1; j <= y; j++){
            if (m % (i * j) != 0 || m / (i * j) > z) continue;
            k = m / (i * j);
            if (i * j * k > m) continue;
            ans = max(ans , (x - i + 1) * (y - j + 1) * (z - k + 1));
        }
    }
    cout << ans << '\n';
}
signed main() {
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1985E Secret Box
## 思路
小学几何题

令 $S$ 的长宽高分别为 $a$ 和 $b$ 和 $c$，则我们可以得出以下公式求方案数。

$(x- a+  1)(y- b+  1)(z- c+  1)$

然后按照上述公式与题意模拟即可。

时间复杂度 $O(xy)$。

---

## 作者：MnZnOIer (赞：1)

### 解题思路
差不多橙吧，枚举 $x',y'$，再求 $z'$，即 $k\div x'y'$ 即可。

前提是，$k\div x'y'$ 是一个整数。

而满足以上条件后，方案数为：$(x-x'+1)(y-y'+1)(z-z'+1)$。

### 代码部分
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, x, y, z, k;
signed main ()
{
    ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
    cin >> t;
    while (t --)
    {
        int ans = 0;
        cin >> x >> y >> z >> k;
        for (int i = 1; i <= x; ++ i)for (int j = 1; j <= y; ++ j)
        {
            int c = k / i / j, cnt;
            if (k % (i * j) != 0 || k % (i * j) > z)continue;
            cnt = (x - i + 1) * (y - j + 1) * (z - c + 1);
            ans = max (ans, cnt);
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：BrotherCall (赞：1)

## 思路

可以枚举长和宽 $x_0$ 和 $y_0$，这样就直接能算出高为 $\displaystyle \frac{k}{x_0y_0}$ 了，但前提是 $k$ 能被 $x_0y_0$ 整除。

根据乘法原理可得，放置方案数为 $\displaystyle(x - x_0 + 1)(y - y_0 + 1)(z-\frac{k}{x_0y_0} + 1)$，取个 $\max$ 即可。

复杂度 $O(xy)$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100;
char ch[N];
int t , x , y , z , k;

signed main() {
	cin >> t;
	while(t --) {
		cin >> x >> y >> z >> k;
		int maxx = 0;
		for(int i = 1;i <= x;i ++) {
			for(int j = 1;j <= y;j ++) {
				if(k % i == 0) {
					int now = k / i;
					if(now % j == 0) {
						int dsw = now / j;
						maxx = max(maxx , (x - i + 1) * (y - j + 1) * max(0ll , (z - dsw + 1)));
					}
				}
			}
		}
		cout << maxx << "\n";
	}
	return 0;
}
```

---

## 作者：mynxzh (赞：1)

题意可以转化为给定四个数 $x, y, z, k$，我们需要找到满足条件 $k \bmod (i \cdot j) = 0$ 的 $i$ 和 $j$ 的组合，其中 $i$ 和 $j$ 分别为 $1$ 到 $x$ 和 $1$ 到 $y$ 之间的整数。

对于满足条件的 $i$ 和 $j$，可以计算出对应的 $cnt = k / (i \cdot j)$，然后计算出满足 $cnt \leq z$ 的方案数，即 $(x-i+1) \cdot (y-j+1) \cdot (z-cnt+1)$。

最终的答案为所有方案数中的最大值。



```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int x, y, z, k;
        cin >> x >> y >> z >> k;

        int ans = 0;
        for(int i=1; i<=x; i++) {
            for(int j=1; j<=y; j++) {
                if(k % (i*j) == 0) {
                    int cnt = k / (i*j);
                    ans = max(ans, (x-i+1)*(y-j+1)*(z-cnt+1));
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
简单几何题目，当一个大长方体的长、宽、高，分别为 $x,y,z$ 时，在里面可以放 $(x-a+1)(y-b+1)(z-c+1)$ 个小的长、宽、高，分别为 $a,b,c$ 的长方体。得出公式后直接枚举即可。
### 代码
```
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;

signed main()
{
	int t, x, y, z, k;
	cin >> t;
	while(t--){
		int ans = 0, cnt = 0;
		cin >> x >> y >> z >> k;
		for(int a = 1; a <= x; a++){
			for(int b = 1; b <= y; b++){
				if(k % (a * b) != 0 || k % (a * b) > z){
					continue;
				}
				int c = k / (a * b);
				cnt = (x - a + 1) * (y - b + 1) * (z - c + 1);
				ans = max(ans, cnt); 
			}
		} 
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：xcms (赞：0)

# 题解：CF1985E Secret Box
设一个长是 $x$ 厘米，宽是 $y$ 厘米，高是 $z$ 厘米的长方体，里面放长是 $a$ 厘米，宽是 $b$ 厘米，高是 $c$ 厘米的小长方体的方案数有 $(x-a+1)×(y-b+1)×(z-c+1)$ 个。

知道上面的公式只有，就可以明白一下思路：枚举 $a,b$ ，判断 $k$ 是否可以被 $a×b$ 整除。如果可以，就按照上面的公式求出最大值即可。

```cpp
for(int i=1;i<=x;i++){
	for(int j=1;j<=y;j++){
		if(k%(i*j)==0){
			int temp=k/(i*j);
			ans=max(ans,(x-i+1)*(y-j+1)*(z-temp+1));
		}
	}
}
```

---

## 作者：Mashu77 (赞：0)

我们知道一个长方体的体积公式是 $V=abh$，然后我们就可以得出方案数应为：$(x−a+1)\times (y−b+1)\times (z−h+1)$。

再遍历 $x$ 和 $y$ 就行了。

要开 long long。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' || x>'9'){if(x=='-') t1|=1;x=getchar();}while(x>='0' && x<='9'){t2=(t2<<1)+(t2<<3)+(x^48);x=getchar();}return t1?-t2:t2;}
inline void write(int x){if(x<0){putchar('-');x=-x;}int sta[100],top=0;do{sta[top++]=x%10;x/=10;}while(x);while(top) putchar(sta[--top]+48);}
int T,x,y,z,k,now,ans;
signed main(){
	T=read();
	while(T--){
		ans=0;
		x=read();
		y=read();
		z=read();
		k=read();
		for(int a=1;a<=x;a++){
			for(int b=1;b<=y;b++){
				if(k%(a*b)!=0 || k/(a*b)>z) continue;//排除不存在的情况
				int c=k/(a*b);
				if(a*b*c>k) continue;
				now=(x-a+1)*(y-b+1)*(z-c+1);
				ans=max(ans,now);
			}
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：dvsfanjo (赞：0)

# CF1985E Secret Box

## 思路

规定大小为 $x \times y \times z$ 的区域，要放下 $a \times b \times c$ 大小的长方体，可以放 $(x-a+1)\times(y-b+1)\times(z-c+1)$ 个，我们只要枚举 $a$ 和 $b$ 算 $c$ 后取最大值即可。

## 注意

在枚举时要注意：

1. 算出来的 $c$ 要是整数！

2. $c$ 不能比 $z$ 大！

3. 总面积要不能比规定的大！

4. 不开 long long 见祖宗。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, x, y, z, k, v, ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	while (n--)
	{
		ans = 0;
		cin >> x >> y >> z >> v;
		for (int i = 1; i <= x; i++)
			for (int j = 1; j <= y; j++)
			{
				if (v % (i * j)) //如果高不是整数
					continue;
				if (v / (i * j) > z) //如果高比限制大
					continue;
				k = v / (i * j);
				if (i * j * k > v) //如果体积比规定大
					continue;
				ans = max(ans, (x - i + 1) * (y - j + 1) * (z - k + 1));
			}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：GeYang (赞：0)

# 题意

给你一个体积为 $S$ 的长方体和一个长宽高分别为 $x$ 和 $y$ 和 $z$ 的长方体 $B$ 然后把后者放前者里，求方案数。

# 思路

放置方案数可以从长宽高三个方面推导，令 $S$ 的长宽高分别为  $a$ 和 $b$ 和 $c$ 得出以下公式为放置方案数。

$$(x-a+1)(y-b+1)(z-c+1)$$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	int x,y,z,k,ans=0;
	cin>>x>>y>>z>>k;
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(k%(i*j)!=0||k/(i*j)>z) continue;
			k=m/(i*j);
			if(i*j*k>k) continue;
			ans=max(ans,(x-i+1)*(y-j+1)*(z-k+1));
		}
	}
	cout<<ans<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--) return 0;
}
```

---

## 作者：LostKeyToReach (赞：0)

这是一道数学题。

首先，我们有一个显然的结论：当 $S$ 长为 $x'$，宽为 $y'$，高为 $z'$ 时，$S$ 在 $B$ 中的放置方案数为 $(x - x' + 1)(y - y' + 1)(z - z' + 1)$。

那么我们尝试枚举合法的三元组 $(x', y', z')$，满足 $x \ge x', y \ge y', z \ge z'$ 且 $x'y'z' = k$，每次更新答案即可。

```cpp
int main() {
    int t;
    read(t);
    while (t--) {
        ll x, y, z, k;
        read(x, y, z, k);
        ll maxn = 0;
        FORL(i, 1ll, k, 1) {
            if (k % i == 0) {
                ll now = k / i;
                FORL(j, 1ll, now, 1) {
                    if (now % j == 0 && x >= i && y >= now / j && z >= j) {
                        maxn = max(maxn, (x - i + 1) * (y - now / j + 1) * (z - j + 1));
                    }
                }
            }
        }
        writeln(maxn);
    }
}
```
但是这样的时间复杂度为 $O(k \log k)$，无法通过此题，由此，我们得优化程序。

我们考虑将第一层循环中枚举 $1$ 到 $k$ 改为枚举 $1$ 到 $\sqrt[3]{k}$，第二层循环中枚举 $1$ 到 $\lfloor \frac{k}{i} \rfloor$ 改为枚举 $1$ 到 $\lfloor \sqrt{\lfloor \frac{k}{i} \rfloor} \rfloor$，当检查到合法的三元组时，我们判断 $3!$ 种情况，也就是对三元组的三个元素进行全排列操作，当遇到合法的三元组时，计算最大值即可。

时间复杂度为：

$$
\begin{aligned}
O(\sum_{i = 1} ^ {\lfloor \sqrt[3]{k} \rfloor} \lfloor \sqrt{\lfloor \frac{k}{i} \rfloor} \rfloor) &=O(\sqrt{k}\int_{0.5}^{\lfloor \sqrt[3]{k} \rfloor + 0.5} x ^ {-\frac{1}{2}} \text{d}x) \\
&=O(2(k ^ {\frac{4}{3}}+k)^{\frac{1}{2}} - \sqrt{2} \times \sqrt{k}) \\
&= O(k ^ {\frac{2}{3}}).
\end{aligned}
$$

可以通过本题。

代码如下：

```cpp
ll x, y, z, k;
ll maxn;
int main() {
    int t;
    read(t);
    while (t--) {
        read(x, y, z, k);
        maxn = 0;
        for (ll i = 1; i * i * i <= k; i++) {
            if (k % i == 0) {
                ll now = k / i;
                for (ll j = 1; j * j <= now; j++) {
                    if (now % j == 0) {
                        ll a = i, b = j, c = now / j;
                        if (x >= a && y >= b && z >= c) maxn = max(maxn, (x - a + 1) * (y - b + 1) * (z - c + 1));
                        if (x >= a && y >= c && z >= b) maxn = max(maxn, (x - a + 1) * (y - c + 1) * (z - b + 1));
                        if (x >= b && y >= a && z >= c) maxn = max(maxn, (x - b + 1) * (y - a + 1) * (z - c + 1));
                        if (x >= b && y >= c && z >= a) maxn = max(maxn, (x - b + 1) * (y - c + 1) * (z - a + 1));
                        if (x >= c && y >= a && z >= b) maxn = max(maxn, (x - c + 1) * (y - a + 1) * (z - b + 1));
                        if (x >= c && y >= b && z >= a) maxn = max(maxn, (x - c + 1) * (y - b + 1) * (z - a + 1));
                    }
                }
            }
        }
        writeln(maxn);
    }
}

---

## 作者：ZnHF (赞：0)

# 题目分析

记 $S$ 的长为 $a$，宽为 $b$，高为 $c$，这时，放置方案数为 $(x-a+1) \times (y-b+1) \times (z-c+1)$。只需要枚举 $a,b$ 并计算出 $c$ 的值并按照上式计算方案数再更新方案数的最大值就能求出答案。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' || x>'9'){if(x=='-') t1|=1;x=getchar();}while(x>='0' && x<='9'){t2=(t2<<1)+(t2<<3)+(x^48);x=getchar();}return t1?-t2:t2;}
inline void write(int x){if(x<0){putchar('-');x=-x;}int sta[100],top=0;do{sta[top++]=x%10;x/=10;}while(x);while(top) putchar(sta[--top]+48);}
int T,x,y,z,k,now,ans;
signed main(){
	T=read();
	while(T--){
		ans=0;
		x=read();
		y=read();
		z=read();
		k=read();
		for(int a=1;a<=x;a++){
			for(int b=1;b<=y;b++){
				if(k%(a*b)!=0 || k/(a*b)>z) continue;//排除不存在的情况
				int c=k/(a*b);
				if(a*b*c>k) continue;
				now=(x-a+1)*(y-b+1)*(z-c+1);
				ans=max(ans,now);
			}
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：gh_AC (赞：0)

# CF1985E Secret Box 题解

## 思路

这是一道很简单的小学几何题。

通过之前学过的排列组合我们知道在长度为 $n$ 的一条坐标上放一个长度为 $x$ 的物体有 $(n-x+1)$ 种方法，在一个长为 $n$ 且宽为 $m$ 的矩形中放一个长为 $x$ 且宽为 $y$ 的矩形有 $(n-x+1)\cdot(m-y+1)$ 种方法。

那么，题目中让我们在一个长为 $x$ 宽为 $y$ 高为 $z$ 的立体图形中放一个体积为 $k$ 的立体图形的话，我们就可以先设这个体积为 $k$ 的立体图形的长为 $a$ 宽为 $b$ 高为 $c$，然后我们就能发现一共有 $(x-a+1)\cdot(y-b+1)\cdot(z-c+1)$ 种方法将这个立体图形放进长为 $x$ 宽为 $y$ 高为 $z$ 的立体图形中。

接着我们只需求出上面所说的体积为 $k$ 的立体图形的长、宽、高并求出最多的方案的方案数并输出就完成了。

下面是代码，有不懂的可以根据代码来理解，还是比较简单的。

## 代码

```cpp
#include<iostream>
using namespace std;
long long t;
long long x,y,z,k;
// 变量名称都与题目中含义相同 
long long ans;
// 最后的答案 
int main(){
	cin>>t;
	while(t--){
		ans=0;
		//初始化 
		cin>>x>>y>>z>>k;
		for(int i=1;i<=x;i++){
			for(int j=1;j<=y;j++){
				if(k/i/j>z||k/(i*j)*i*j>k) continue;
				//当构成的立体图形不符合题意时就跳过 
				if(k%(i*j)==0) ans=max(ans,(x-i+1)*(y-j+1)*(z-k/(i*j)+1));
				//当构成的立体图形符合题意时就取方案数的最大值 
				// k/(i*j)是构成的立体图形的高 
			}
		}// 遍历构成的立体图形的长和宽 
		cout<<ans<<endl;
	}
	return 0;
}// 复杂度为O(xy) 
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1985E Secret Box

[题目传送门](/problem/CF1985E)

## 题意简述

在一个长宽高分别为 $x,y,z$ 的长方体中放入一个长宽高为 $x',y',z'$ 的长方体，使得这个长方体的体积为 $k$。问这个长方体放置最多的方案数。

## 思路

对于单次询问，我们可以考虑枚举边长小的两条边，另外一条边可以通过 $k$ 算出了。由于枚举顺序是没必要的，所以倒着来。**注意：下面的优化按这个来的**！！！如果 $\frac {k}{i\times j}>z$，说明之后不管怎样都不可能找到解，直接结束循环（$i$ 表示第一条边，$j$ 表示第二条边）。

你是不是以为完了？不，还有！！！我们发现，其实，$i=1,j=2$ 的情况和 $i=2,j=1$ 的情况是等价的，所以第二重循环只需要从 $i$ 开始枚举就可以了。（貌似~~时间减半~~我的代码跑的最快）。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define elif else if
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
#define rnt register int
#define reg(i,x,y) for (register int i=(x);i<=(y);++i)
#define Reg(i,x,y) for (register int i=(y);i>=(x);--i)
using namespace std;
namespace rwm {inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)){w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}inline void write (int x) {if (x<0) putchar ( '-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}inline void writesp (int x) {write (x),putchar (' ');}inline void writeln (int x) {write (x),putchar ('\n');}inline int square (int x) {return x*x;}inline int floor (double x) {return x;}inline int ceil (double x) {return (int)(x+0.5);}inline int gcd (int x,int y) {int z=x%y;while (z) x=y,y=z,z=x%y;return y;}inline int lcm (int x,int y) {return x/gcd (x,y)*y;}};
using namespace rwm;
int t,x,y,z,k,a[3]; 
signed main ()
{
	t=read ();
	while (t--)
	{
		int ans=0;
		a[0]=read (),a[1]=read (),a[2]=read (),k=read ();
		sort (a,a+3);
		x=a[0],y=a[1],z=a[2];
		Reg (i,1,x)	//注意注意：倒着来！！！
			if (k%i==0)
				Reg (j,i,y)
					if ((k/i)%j==0)
					{
						int p=(k/i)/j;
						if (p>z) break;
						ans=max (ans,(x-i+1)*(y-j+1)*(z-p+1));
					}
		writeln (ans);
	}
	return 0;
}

```

---

## 作者：GeXiaoWei (赞：0)

# CF1985E Secret Box
## 解析
一道关于几何与排列组合的思维题。

令长方体 $S$ 的长宽高分别为 $a$ 和 $b$ 和 $c$，通过小学奥数可知，放置方案数为 $(x-a+1)\times(y-b+1)\times(z-c+1)$，然后两层循环枚举长和宽，根据长方体体积公式求出第三条边即可，注意开 long long 并且高为整数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,x,y,z,k,maxx;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld%lld",&x,&y,&z,&k);maxx=0;
		for(int i=1;i<=x;i++){
			for(int j=1;j<=y;j++){
				if(k%(i*j)!=0||k/i/j>z) continue;
				maxx=max(maxx,(x-i+1)*(y-j+1)*(z-k/(i*j)+1));
			}
		}
		printf("%lld\n",maxx);
	}
	return 0;
} 
```

---

## 作者：L_xcy (赞：0)

### 解题思路

小学的几何题，从长、宽、高三个方面去想，可以得到公式：
$$

(x−a+1)(y−b+1)(z−c+1)

$$

所以我们只需要按照公式遍历即可。

---

### Code

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main(){
	int t; cin >> t;
	while(t--){
		ll x, y, z, k; cin >> x >> y >> z >> k;
		ll ans = 0;
		for(int a = 1; a <= x; a++){
			for(int b = 1; b <= y; b++){
				if(k % (a * b)) continue;
				ll c = k / (a * b);
				if(c > z) continue;
				ll ways = (ll)(x - a + 1) * (y - b + 1) * (z - c + 1);
				ans = max(ans, ways);
			}
		}
		cout << ans << "\n";
	}
}
```

---

## 作者：封禁用户 (赞：0)

设长宽高分别为 $a,b,c$。

由题意可轻松的得到以下求方案数公式。

$(x-a+1)(y-b+1)(z-c+1)$

然后根据这个公式模拟即可。

[AC Code](https://codeforces.com/contest/1985/submission/268854002)

---

## 作者：iyka (赞：0)

### 解题方法
根据小学知识，我们知道一个长方体的体积公式是 $V=abh$，然后我们就可以得出方案数应为：
$$(x−a+1)\times (y−b+1)\times (z−h+1)$$
然后再遍历 $x$ 和 $y$ 根据题意模拟就行了。

不开 long long 见祖宗！！！

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,ans,x,y,z,m,k;
signed main()
{
    cin>>t;
    while(t--)
    {
		cin>>x>>y>>z>>m; ans=0;
	    for(int i=1;i<=x;++i)
	        for(int j=1;j<=y;++j)
			{
	            if((m%(i*j)!=0 || m/(i*j)>z) || (i*j*k>m))
	            	continue;
	            ans=max(ans,(x-i+1)*(y-j+1)*(z-m/(i*j)+1));
	        }
	    cout<<ans<<"\n";
	}
    return 0 ;
}
```

---

