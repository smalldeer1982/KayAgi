# 「Cfz Round 3」Change

## 题目描述

给定一个质数 $p$ 和三个整数 $a,b,c$，你需要对一个初始为 $0$ 的整数 $x$ 进行操作，每次操作可以进行如下的两种之一：

- 第一种操作：令 $x$ 的值变为 $(x \times a) \bmod p$。
- 第二种操作：令 $x$ 的值变为 $(x+b) \bmod p$。

其中，$\bmod$ 表示**取模**运算。

你需要求出能否在**正整数次**操作后得到 $c$，若能则输出 `Yes`，否则输出 `No`。

本题中字符串大小写不敏感，即 `yes`、`yeS`、`yEs`、`Yes`、`YEs`、`YeS`、`yES`、`Yes` 都被认为是 `Yes`，`No` 同理。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，进行 $1$ 次第二种操作后进行 $2$ 次第一种操作即可。

对于第 $2$ 组数据，进行 $1$ 次第二种操作后进行 $1$ 次第一种操作即可。

对于第 $3$ 组数据，可以证明无论如何操作都无法得到 $3$。

#### 「数据范围」

对于所有数据，$1\le T \le 100$，$0\le a,b,c < p \le 10^9$，保证 $p$ 是质数。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3
5 2 1 4
3 2 2 1
7 2 0 3```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：玄学OIER荷蒻 (赞：7)

一道 CF 风格题，这里对大小写不敏感也是为了仿 CF。

首先，很明显如果 $b$ 不为 $0$，那么可以一直进行第二种操作，由于 $\gcd(p,b)=1$，可以由裴蜀定理得知一定能达到 $c$。

否则如果 $b=0$，那么第一种操作相当于一直对 $0$ 进行乘法，并没有任何用，此时只有 $c=0$ 满足条件，因为什么都不用操作就已经达到了需求，虽然说题目不让不进行操作，但我们还是可以先进行一次乘法操作（反正没用）。

综上，只要 $b \ne 0$ 或者 $c=0$ 答案就为 `YES`，否则就是 `NO`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int a,b,c,p;
	cin>>p>>a>>b>>c;
	if (b!=0 || c==0) cout<<"YES\n";
	else cout<<"NO\n";
} 
int main(){
    int T;
    cin>>T;
    while (T--) solve();
	return 0;
}
```


---

## 作者：fish_love_cat (赞：4)

**思路：**

可以发现乘法可以用加法实现，所以在这里只思考加法。

因为 $p$ 是质数并且 $b<p$，所以 $b$ 与 $p$ 互质，即 $\gcd(b,p)=1$。


那么也就是说可以加出所有小于 $p$ 的非负整数。

啊但是！！

如果 $b=0$，显然的无论怎么样 $x=0$。所以我们要判断此时 $c$ 是否也等于 $0$，是的话那还是 `yes`，不然就是 `no`。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int p,a,b,c;
		cin>>p>>a>>b>>c;
		if(b==0&&c!=0)puts("No");//判断
		else puts("Yes");
	}
	return 0;
} 
/*
你从黑暗中 走过来 牵着我的手
这份温度是我 面对未知的理由
你什么都不说 只是陪我向前走
不善言辞的我 也能穿过月色朦胧
*/
```

---

## 作者：LinkCatTree (赞：3)

题目传送[门](https://www.luogu.com.cn/problem/P10030)。

更好的[观感](https://3zinc.github.io/2023/13978/)。

首先发现：若 $c \ne 0$ 并且 $b=0$，那么肯定无解。

接下来发现：由于 $p$ 是质数并且 $b<p$，所以 $\gcd(b,p)$ 一定为 $1$，即 $b,p$ 互质。所以，若 $c \ne 0$，则一定有一个 $k \in \mathbb{N}^+$ 满足 $kb \equiv c \pmod p$。如果 $c=0$，可以通过乘一次 $a$ 获得。

```cpp
#include <bits/stdc++.h>
using namespace std;
int p,a,b,c,T;
int main() {
    cin>>T;
    while(T--) {
        cin>>p>>a>>b>>c;
        if(b==0&&c!=0) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}
```

---

## 作者：Vct14 (赞：3)

很明显，当 $b\ne0$ 时，如果一直执行 $b$ 操作，则一定可以得到 $c$。证明如下。

设执行 $x$ 次操作后得到 $c$，则 $bx\equiv c\pmod{p}$。由于 $p$ 为质数，即 $(p,b)=(p,c)=1$，则原同余方程一定有解。

当 $b=0$ 时，显然仅当 $c=0$ 有解。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--){
    	int p,a,b,c;cin>>p>>a>>b>>c;
    	if(b!=0) puts("YES");
    	else if(c==0) puts("YES");
    	else puts("NO");
	}
    return 0;
}
```

---

## 作者：CaiZi (赞：2)

## P10030 「Cfz Round 3」Change 题解
#### [题目链接](https://www.luogu.com.cn/problem/P10030)
### 题意理解
给定 $T$ 组数据，每组数据给定一个**质数** $p$ 和 $a,b,c$。你有一个变量 $x=0$。你每次可以使 $x\gets (x\times a)\bmod p$ 或 $x\gets (x+b)\bmod p$。询问你是否可以通过至少 $1$ 次操作使 $x=c$。$1\le T\le 100$，$0\le a,b,c<p\le 10^9$。
### 题目分析
场上发现规律但没完全发现，于是挂了。

首先观察到，$p$ 为一个质数，而质数和任何小于它的数都互质。即 $\gcd(p,x)=1$，其中 $0\le x<p$ 且 $x$ 为整数。所以我们可以通过不断的使 $x\gets (x+b)\bmod p$ 得到所有 $0\le x<p$ 的整数 $x$，前提为 $b\ne0$，证明略。所以 $a$ 毫无意义。

而在 $c=0$ 时，无论如何都有解，只要使 $x\gets (x\times a)\bmod p$ 便可以完成一次操作，因为 $x=0$，执行完这次操作 $x$ 依旧为 $0$。

综上所述，当 $b=0$ 且 $c\ne0$ 时无解，否则均有解。
### 代码展示
时间复杂度 $O(T)$，空间复杂度 $O(1)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,p,a,b,c;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>p>>a>>b>>c;
		cout<<(b==0&&c!=0?"No\n":"Yes\n");
	}
	return 0;
}
```
#### [提交记录](https://www.luogu.com.cn/record/141602307)

---

## 作者：__Tonycyt__ (赞：2)

### 思路

不扯别的了，直接上正解。

首先因为 $b<p$ 且 $p$ 为质数，所以如果 $b\neq0$ 就一定有 $\gcd(b,p)=1$，那么让 $x$ 一直加上 $b$ 就可以得到所有满足 $0\leq c<p$ 的数。

对于 $b=0$，如果 $c=0$ 就直接可以，如果 $c\neq0$，那么 $x$ 将一直是 $0$，无法满足条件。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int p,a,b,c;
		cin>>p>>a>>b>>c;
		if(b!=0) cout<<"YES\n";
		else if(c!=0) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}

```

---

## 作者：FurippuWRY (赞：1)

结论很好想，只有当 $b=0\land c\ne 0$ 时才输出 `no`。因为 $p$ 是质数，且 $b<p$，$\gcd(p,b)=1(b\ne 0)$，所以可以一直进行第二种操作使 $x=c$，输出 `yes`。但如果 $b=0$，$x$ 的值永远只会为 $0$，此时除非 $c=0$，那么 $x\ne c$，输出 `no`。

```cpp
//新年快乐。
#include<bits/stdc++.h>

using namespace std;

int t, p, a, b, c;

int main() {
	cin >> t;
	while (t--) {
		cin >> p >> a >> b >> c;
		if (b == 0 && c != 0) puts("no");
		else puts("yes");
	}
	return 0;
}
```

---

## 作者：xz001 (赞：1)

- 因为 $p$ 是质数，所以只要 $b$ 不是 $0$ 就满足 $\gcd(b,p)=1$，$x$ 只要一直加 $b$ 一定可以变成任何值，但若 $b=0$，那么只有在 $c=0$ 时可行，否则永远是 $0$。
- 代码如下：

```cpp

#include <bits/stdc++.h>

using namespace std;

#define re register
#define int long long 
#define fi first
#define se second
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define il inline
#define abs(x) ((x ^ (x >> 63)) - (x >> 63))
#define huk2 queue
#define is <int>
#define die q;

typedef pair<int, int> PII;

const int N = 2e6 + 10;
const int M = 2e6 + 10;
const int INF = 1e18, mod = 1e9 + 7;
const double eps = 1e-6;

int t, n;

signed main() {
	cin >> t;
	while (t -- ) {
		int p, a, b, c;
		cin >> p >> a >> b >> c;
		if (b != 0) cout << "Yes" << endl;
		else if (c == 0) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
    return 0;
}
```

---

## 作者：gaojizhe05 (赞：1)

# 题目分析
因为 $p$ 是一个质数，而质数与任何小于自己的数的最大公因数都是 $1$，也就是说只要我们不断进行 $(x+b) \bmod p$ 操作，最终一定可以让 $x=c$。此时就可以发现 $a$ 与答案无关。

那么在什么时候无法让 $x=c$ 呢？我们需要 $(x+b) \bmod p$ 操作无法改变 $x$ 的值，也就是 $b=0$。不过需要注意 $c \ne 0$，否则必然成立。

总结：**只要满足 $b=0$ 且 $c \ne 0$，那么 $x \ne c$，否则可以使 $x=c$**。
# 代码
````cpp
include <bits/stdc++.h>//万能头文件
using namespace std;
int T;
int p,a,b,c;
void Init(){
	cin>>p>>a>>b>>c;
	return;
} 
void Work(){
	if(b==0&&c!=0) cout<<"No\n";//b=0且c!=0时不成立
	else cout<<"Yes\n";//否则成立
	return;
}
int main(){
	cin>>T;
	while(T--){
	    Init();//读入
	    Work();//运行
	}
	return 0;
}
``````

---

## 作者：xxboyxx (赞：0)

### 思路

由于 $p$ 是质数，所以在 $b > 0$ 时，$x$ 可以变成 $0 \sim p-1$ 中的所有数，证明如下：

第一次 $x \bmod p$ 为 $0$ 是 $x=0$ 的时候，那下一次呢，当然是 $p$ 和 $b$ 的最小公倍数，由于 $p$ 是质数，所以 $p$ 和 $b$ 的最小公倍数就是 $p \times b$，那么就操作了 $p$ 次，在这之中，$p$ 个 $x$ 各不同。

如果 $b \ge 1$ ，肯定是可以的。

### 注意

如果 $b = 0$ ，也不一定不可以，如果 $c=0$，不管怎样都可以。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
long long t,p,a,b,c;
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>p>>a>>b>>c;
		if (b!=0)//b不为0，一定可以 
			cout<<"Yes\n";
		else if (c==0)//c为0，一定可以 
			cout<<"Yes\n";
		else//b为0，c又不为0，一定不可以 
			cout<<"No\n";
	}
	return 0;
}
```


---

