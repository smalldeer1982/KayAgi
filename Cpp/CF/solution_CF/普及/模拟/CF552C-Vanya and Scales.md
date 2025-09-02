# Vanya and Scales

## 题目描述

Vanya has a scales for weighing loads and weights of masses $ w^{0},w^{1},w^{2},...,w^{100} $ grams where $ w $ is some integer not less than $ 2 $ (exactly one weight of each nominal value). Vanya wonders whether he can weight an item with mass $ m $ using the given weights, if the weights can be put on both pans of the scales. Formally speaking, your task is to determine whether it is possible to place an item of mass $ m $ and some weights on the left pan of the scales, and some weights on the right pan of the scales so that the pans of the scales were in balance.

## 说明/提示

Note to the first sample test. One pan can have an item of mass $ 7 $ and a weight of mass $ 3 $ , and the second pan can have two weights of masses $ 9 $ and $ 1 $ , correspondingly. Then $ 7+3=9+1 $ .

Note to the second sample test. One pan of the scales can have an item of mass $ 99 $ and the weight of mass $ 1 $ , and the second pan can have the weight of mass $ 100 $ .

Note to the third sample test. It is impossible to measure the weight of the item in the manner described in the input.

## 样例 #1

### 输入

```
3 7
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
100 99
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
100 50
```

### 输出

```
NO
```

# 题解

## 作者：封禁用户 (赞：3)

# 注明：此篇题解的思路来自于网上。题解原网络位置https://blog.csdn.net/mblhq/article/details/51212267 这篇题解是在理解其基础上进行完全的重新编写的



------------
让我们来举个栗子：

当m=27，w=2时，是可以凑得这个数字的，让我们推导一下把m变成0的过程。

w[]=1,2,4,8,16,32

m=27

此时同学们肯定想到要-1或+1，为了变小，我们-1

s=26

假设s这个多项式（或单项式）=27。而且s中含有1.让我们同时减去1变成

s=26（s这个算数一直表达等于右边的算式）

此时的s中含有的数字都是偶数。让我们两边同时/2

得到

s=13

……

s=0

这是s=0了。于是我们得到可以通过2的次幂来得到27

举个不成功的栗子

w=4,m=7

s=7

首先我们发现++后就是2的倍数，意味着s中有-1，两边同时+1

s=8

这时我们判定s中的数字一定是4的倍数，于是我们/4

s=2

这时我们发现我发通过++或--或/w得到0或w的倍数了，于是判定不可以。

以下是正式代码↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int w,m;
int main()
{
	scanf("%d %d",&w,&m);
	while(m)
	{
		if(m%w==0);
		else if((m-1)%w==0) m--;
		else if((m+1)%w==0) m++;
		else
		{
			printf("NO");
			return 0;
		}
		m/=w;
	}
	printf("YES");
	return 0;
}
```

---

## 作者：Untitled (赞：2)

#这是一道水题

首先，我们需要明确：

这些数的加减，实际上就等于 $ a_0w^0+a_1w^1+...+a_nw^n $ 

a是各项的系数

而因为每项只能用一次， 

a只能取 $ 1 , 0 , -1 $ 中的一个

忽略第一个，如果能让 $ m $ 能成立，他至少的先决条件是能被 $ w $ 整除

所以，我们肯定是尽量让他成立

所以，我们通过第一项来调整，使他来满足条件

但如果不能的话，果断判错！！！

然后，我们再来判断一下m调整过的数n能否通过w的幂次的加减得到......如果可以，

~~很熟悉对不对~~

回去再判就行了

最后，如果能到0，毋庸置疑，坑顶阔以！

贴代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int w,m;
int main()
{
    scanf("%d%d",&w,&m);
    while(1)
    {
    		 if(m	   ==0) break;
             if( m   %w==0) {    m/=w;continue;} 
        else if((m-1)%w==0) {m--;m/=w;continue;} 
        else if((m+1)%w==0) {m++;m/=w;continue;}
        printf("NO");
        return 0;
    }
    printf("YES");
    return 0;
}
```

---

## 作者：Robin_kool (赞：1)

题意：给定 $w$ 和 $m$，判断是否存在 $\sum_{i=1} p_i \cdot w^i=m$，其中满足 $p_i=-1,0,1(0 \leq i)$。

抽象的理解一下，其实就是把 $m$ 换成 $w$ 进制后，每一位上的数字必须是 $-1,0,1$。

由于 $w,m \leq 10^9$ 且 $w > 1$，所以不用担心强转 $w$ 进制时间复杂度爆炸的问题，最多 $31$ 次左右。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m, w;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void fuckccf(){
	int fuckccf = 0;
	if(fuckccf) cout << "fuckccf";
}
signed main(){
	//freopen("CF552C.in", "r", stdin);
	//freopen("CF552C.out", "w", stdout);
    w = read(), m = read();
	while(m){
		if(m % w == 0) fuckccf();
		else if((m - 1) % w == 0) -- m;//确保能整除且数字在-1,0,1之间
		else if((m + 1) % w == 0) ++ m;
		else{//如果不满足则无解
			puts("NO");
			return 0;
		}
		m /= w;
	} 
	puts("YES");
	return 0;
}

```


---

## 作者：hswfwkj_ (赞：1)

看到这个数据范围，首先我们已知当 $w=2$ 时一定有解。

然后我就想歪了。

因为 $3^{19} > 10^9$，也就是说除去 $2$ 的情况被考虑进答案的最多只有 $19$ 个数。所以这给了我一种搜索的自信。

对于当前选择的 $w^n$，最多只有三种情况：
- 加上 $w^n$
- 减去 $w^n$
- 不选择 $w^n$

然后写了一个搜索交上去，结果被轻松卡 T。

注意到答案很方便合并，于是我们可以折半搜索，复杂度降到了 $O(3^{\frac {\log n}{2}})$，可以轻松水过。

没猜出结论导致的，我是 Joker。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
int len, tmp[25];
map<int, int> mp;
void dfs1(int s, int v)
{
	if(s > len / 2)
	{
		mp[v] = 1;
		return;
	}
	dfs1(s + 1, v - tmp[s]);
	dfs1(s + 1, v + tmp[s]);
	dfs1(s + 1, v);
}
void dfs2(int s, int v)
{
	if(s > len)
	{
		if(mp[m - v]) cout << "YES", exit(0);
		return;
	}
	dfs2(s + 1, v - tmp[s]);
	dfs2(s + 1, v + tmp[s]);
	dfs2(s + 1, v);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	int base = 1;
	for(int i = 1; i; i++)
	{
		tmp[++len] = base;
		if(base >= m) break;
		base *= n;
	}
	// for(int i = 1; i <= len; i++) cout << tmp[i] << ' ';
	// cout << '\n';
	dfs1(1, 0);
	dfs2(len / 2 + 1, 0);
	cout << "NO";
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

# 题意

$m$ 能否表示为 $p_0w^0+p_1w^1+p_2w^2+...+p_nw^n$ 的形式，其中 $p_i$ 只能为 $1,0,-1$。  


# 分析
如果满足题意，则**当前的** $m$，$m-1$，$m+1$ 中必有一个能被 $w$ 整除的数。  

因为 $p_0w^0$ 这一项的取值只有 $1,0,-1$ 三种可能。 

于是可以考虑类似迭代的方式去分解 $m$。

巧妙地发现每个 $m$ 都满足以上性质。  

一旦在任何一次循环中不满足条件就立刻退出即可。  

# 代码  

```cpp
int w=read(),m=read();
while(m)
{
	if(m%w==0){
		m/=w;
	}
	else if((m-1)%w==0){
		m=(m-1)/w;
	}
	else if((m+1)%w==0){
		m=(m+1)/w;
	}
	else{
		puts("NO");
		return 0;
	}
}
puts("YES");
```
相当于一次次的分解下去，如果最后为 0 就证明两者相等了。  

另外可以特判一下，如果 $w\le3$ 就可以直接输出，因为已知这个范围内可以拼出所有符合条件的 $m$。

---

## 作者：细数繁星 (赞：1)

[更好的体验！](https://www.cnblogs.com/2044-space-elevator/articles/17950443)

[传送门。](https://www.luogu.com.cn/problem/CF552C)

这篇题解相较于别的题解应该讲的很详细，别的题解一般式子一摆代码一给结束了。如果你感觉这篇题解对你有帮助，请为这篇题解点赞，谢谢！

## 大意

> 因为翻译有点烧脑，这里再翻译一遍。

给定 $w$ 以及 $m$，其中 $1\le m\le 10^9$ 且 $2\le w\le 10^9$，求是否存在一种情况，使得：

$$
\sum_{i=0}^kp_iw^i=m
$$

其中 $p_i$ 的值为 $1,0,-1$ 的其中一个。

## 思路

拿到题目大家可能会想到以下两种解法：

- 暴力出奇迹。实际上这么大的数据量奇迹出不了一点。
- 背包，数据量太大了过不了。

而且看这个数据量以及 CF 评测机的能力，能想到复杂度应该在线性或者更低。

接下来讲正解：可以想到，这个求和式里每一项都有至少一个 $w$，分解因式得：

$$
p_0+w(p_1+w(p_2+w(p_3+w(\ldots))))=m
$$

把 $p_0$ 移走，得：

$$
w(p_1+w(p_2+w(p_3+w(\ldots))))=m-p_0
$$

若 $m-p_0\nmid w$（也就是说如果 $m-1\nmid w$ 且 $m\nmid w$ 且 $m+1\nmid w$），结束输出 `NO`。如果满足，则重设 $m=\dfrac{m-p_0}{w}$，继续：

$$
p_1+w(p_2+w(p_3+w(\ldots))))=m
$$

所以我们就一直把这个式子像剥洋葱一样剥开，遇到剥不开的结束掉。

每一次剥洋葱都能从 $m$ 中除掉一个 $w$，如果能剥完也就是一直剥到 $m=0$，说明是存在题面所述的情况的。这个算法的复杂度是很优秀的，代码如下：

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
    ll w, m;
    cin >> w >> m;
    while (m) {
        m = (
            m % w ? (
                (m - 1) % w ? (
                    (m + 1) % w ? (
                        -114514 // 哨兵
                    ) : (m + 1) / w
                ) : (m - 1) / w
            ) : m / w
        );
        if (m == -114514) {
            RTN
            return;
        }
    }
    RTY;
}


main() {
	int t; t = 1; while (t--) solve();
	return 0;
}

```

时间复杂度 $\mathcal{O}(\log_wm)$。

---

## 作者：GaoKui (赞：1)

思维题

首先先转化一下问题，问题可以转化为，是否可以用所谓的砝码，凑成两个数字 $a,b$，满足 $a+m=b$。

观察可以发现，如果把 $a,b$ 写成一个 $w$ 进制数，它们必须满足的两个要求是：

1. 变为 $w$ 进制后的每一个数位，要么是 $0$，要么是 $1$，不可以有其他数字。
1. 它们 $w$ 进制位为 $1$ 的位，不能有重复。


------------


可以用 $m$ 作为基准，尝试利用一个 $a$，将 $a+m$ 凑成 $b$。

首先把 $m$ 变为一个 $w$ 进制数，从低位到高位遍历 $m$ 的每一位。

如果发现某一位是 $w-1$，在该位上 $+1$，并进行进位。

这就相当于是把 $a$ 的对应位设成了 $1$。

（注意进位以后下一位就算什么都不加可能也需要进）


------------



另外，如果某一位是 $0$ 或者 $1$，那么也是合法的，不需要处理。

但如果某一位是大于 $1$ 且小于 $w-1$ 的某个数，那就是不合法的，直接输出 NO，而正常遍历完所有位的话就输出 YES。

可以发现，全部处理完后剩下的数字刚好是 $b$。

之所以遍历完所有位直接输出即可，是因为 $w$ 就算取最小的 $2$，$2^{100}$ 也远远大于 $m$ 的最大值 $10^9$。

因此，砝码种数看成是无限的就行了。


------------
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll n, m;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    vector<ll> v;

    while (m)
    {
        v.push_back(m % n); // 把m拆成n进制数，每一位存到v里
        m /= n;
    }

    v.push_back(0); // 最高位补上一个0，处理进位的时候就不用判断边界了

    for (int i = 0; i < v.size() - 1; i++) // 遍历每一位
    {
        if (v[i] == n - 1 || v[i] == n) // 发现 n-1 或者 n 就进行进位
        {
            v[i] = 0;
            v[i + 1] += 1;
        }
        else if (v[i] > 1) // 否则只能是0或1，否则就输出NO
        {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";

    return 0;
}
```


---

## 作者：qusia_MC (赞：0)

其他题解都太严谨了我给大家讲通俗点。希望对你有帮助。
## 题意
一个数 $m$ 能不能表示成 $pw^0+pw^1+pw^2…pw^{100}$ 的形式。其中 $p$ 为符号，只能是 $1,0$ 或 $-1$。
## round 1
首先，$pw^1+pw^2…pw^{100}$ 这一串东西一定能被 $w$ 整除。因为提取公因数 $w$，就变成了 $w\times (pw^0+pw^1+pw^2…+pw^{99})$。所以，数列最前面的就起着决定性的作用。我们分两种情况：

- 如果 $m+1\times w^0$，$m+0\times w^0$，$m-1\times w^0$中有任意一个数能被 $w$ 整除，那么就把 $m$ 的值更新成这个数在计算。

- 如果$m+1\times w^0$，$m+0\times w^0$，$m-1\times w^0$中的所有数都不能被 $w$ 整除，不满足条件（至于为什么不满足见后面），输出 NO，结束程序。

我们接着第一种情况接着分析：

这个式子就是：$m=pw^1+pw^2…pw^{100}$（ $pw^0$ 已经使用了）

由于更新后的 $m$ 一定能被 $w$ 整除，利用等式的性质，等号左右两边同时除以 $w$：

$m\div w=(pw^1+pw^2…pw^{100})\div w$

$m\div w=w\times (pw^0+pw^1…pw^{99})\div w$

$m\div w=pw^0+pw^1…pw^{99}$

发现没？又回到原先的了！只不过少了一个 $w^{100}$ 而已。

所以我们可以用类似递推这样的方式写一个循环。

```
int cnt=0;//记录已经用过的砝码个数，由于不是无限个
while(m)
{
    if(cnt>=100)
    {
        cout<<"NO";
        return 0;
    }//用光了
    if(m%w==0)m+=0;//p=0
    else if((m+1)%w==0)m++;//p=1
    else if((m-1)%w==0)w--;//p=2
    else 
    {
        cout<<"NO";
        return 0;
     }
     m/=w;//除
     cnt++;//用掉一个
}
```
总代码（高清版）：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int w,m,cnt=0;
    cin>>w>>m;
    while(m)
    {
        if(cnt>=100)
        {
            cout<<"NO";
            return 0;
        }
        if(m%w==0)m+=0;
        else if((m-1)%w==0)m--;
        else if((m+1)%w==0)m++;
        else
        {
            cout<<"NO";
            return 0;
        }
        m/=w;
        cnt++;
    }
    cout<<"YES";
}

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF552C)

# 题意

$m$ 是否能拆成 $a_0w^{0}$ $+$ $a_1w^{1}$ $+$ $...$ $+$ $a_nw^{n}$ 的形式，其中 $a_i$ 只能是 $-1$，$0$，$1$。

# 思路

相当于问是否能将 $m$ 拆成 $w$ 进制。

用进制转换去分解 $m$，对 $w$ 取余，满足余数等于 $-1$，$0$，$1$，否则输出 NO。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>w>>m;
    while(m){
        if(m%w==1) m--;
        else if(m%w==w-1) m++;
        else if(m%w) return cout<<"NO",0;
        m/=w;//换下一位
    }
    cout<<"YES";
    return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

相当于问你能否将 $m$ 拆成奇特的 $n$ 进制是每一位是 $1$ 或 $0$ 或 $-1$。

然后就用[这题](https://www.luogu.com.cn/problem/P1143)的方法拆分。

1.  先对 $n$ 取余。
	- 如果余 $0$，直接继续。

	- 如果余 $1$，$m=m-1$。

	- 如果余 $-1$，$m=m+1$。

	- 否则，输出 NO。

2. 换下一位：$m=m\div n$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
signed main(){
	scanf("%lld%lld",&n,&m);
	if(n==2){
		puts("YES");
		return 0;
	}
	while(m>0){
		int p=m%n;
		if(p==1){
			m--;
		}
		else if(p==n-1){
			m++;
		}
		else if(p!=0){
			puts("NO");
			return 0;
		}
		m/=n;
	}
	puts("YES");
	return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
给定一个天平，砝码的重量为 $w^x$ ($2\le w \le10^9$ , $x$ 为任意数) ，每种砝码只有一个，砝码可以放在左盘或者右盘。

给定物品的重量 $m$ ($1\le m \le10^9$)，问是否有一种方案让天平两端平衡。
## $Answer$
因为砝码的是 $w$ 的幂次方，并且要可以称重物 $m$,那么 $m$ 或 $m+1$ 或 $m-1$ 就一定是 $w$ 的倍数。

不断将 $m$ 分解，会发现得到的新的 $m$ 仍然符合上述条件。

如果不符合上述条件，则表示天平两边不可能平衡，输出  $NO$。

## $Code$
```pascal
var
    w,m:longint;
begin
    readln(w,m);
    while m>0 do
    begin
        if (m-1)mod w=0 then dec(m)//如果m-1是w的倍数，在m-1
            else
            if (m+1)mod w=0 then inc(m)//如果m+1是w的倍数，则m+1
                else
                if m mod w=0 then
                begin
                    write('NO');
                    halt;
                end;
        m:=m div w;
    end;
    write('YES');
end.
```
维护和平洛谷，请不要复制代码，后果自负。。。

---

