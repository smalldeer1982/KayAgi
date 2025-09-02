# Hard Problem

## 题目描述

Ball 是折纸大学的一名老师。他的教室有 $2$ 行座位，每行有 $m$ 个座位。

Ball 在教 $a + b + c$ 只猴子，他希望能够让尽可能多的猴子坐在座位上。他知道有 $a$ 只猴子只想坐在第 $1$ 行，有 $b$ 只只想坐在第 $2$ 行，有 $c$ 只对座位没有偏好。每个座位上只能坐一只猴子，且入座的猴子的偏好必须被满足。

Ball 最多可以让多少只猴子就坐？

## 说明/提示

对于第二组测试样例，有 $6$ 只猴子想坐在第一行，但只有 $3$ 个座位。对座位没有偏好的猴子和喜欢坐在第二行的猴子可以一起坐在第二行。因此，答案是 $3+2=5$ 。

## 样例 #1

### 输入

```
5
10 5 5 10
3 6 1 1
15 14 12 4
1 1 1 1
420 6 9 69```

### 输出

```
20
5
30
2
84```

# 题解

## 作者：OIerWu_829 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF2044C) / [Codeforces 传送门](https://codeforces.com/problemset/problem/2044/C)

我们用 $pa$ 表示能安排在第一排的猴子数，也就是 $\min(m,a)$，因为第一排最多有 $m$ 个座位，所以能安排的猴子数不能超过 $m$ 且不能超过只想坐在第一排的猴子数 $a$；用 $pb$ 表示能安排在第二排的猴子数，也就是 $\min(m,b)$，同理。

然后计算答案，先给出公式：`pa + pb + min(c, m * 2 - pa - pb)`。

解释一下，$pa+pb$ 是已经确定安排在第一排和第二排的猴子总数；$m\times2-pa-pb$ 表示两排总共 $2m$ 个座位减去已经安排在第一排和第二排的座位数，即剩余的空座位数；$\min(c,m\times2-pa-pb)$ 表示在无偏好的猴子数 $c$ 和剩余空座位数中取较小值，这就是还能安排的无偏好猴子数。然后把这几个部分相加就可以了。

```cpp
#include <iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int m, a, b, c;
		cin >> m >> a >> b >> c;
		int pa = min(m, a), pb = min(m, b);
		cout << pa + pb + min(c, m * 2 - pa - pb) << "\n";
	}
	return 0;
}
```

---

## 作者：JimmyQ (赞：2)

# CF2044C Hard Problem
## 思路
先让那 $a+b$ 个学生入座，记第一、二排分别入座了 $num1,num2$ 个学生。容易想到最终答案为 $2\cdot m$ 和 $num1+num2+c$ 取最小值。（注：$2\cdot m$ 为所有座位均坐满，$num1+num2+c$ 为所有学生均有位置）
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,m,a,b,c,num1,num2;
int main(){
	cin>>t;
	while(t--){
		cin>>m>>a>>b>>c;
		num1=min(a,m),num2=min(b,m);
		cout<<min(2*m,num1+num2+c)<<endl;	
	}
	return 0;
} 
```

[AC记录](https://codeforces.com/contest/2044/submission/299134157)

---

## 作者：alan1118 (赞：1)

## 题意

鲍尔正在教 $a+b+c$ 只猴子，他想尽可能在每个座位上安排猴子就座。鲍尔知道，其中 $a$ 只猴子只想坐在第 $1$ 行，$b$ 只猴子只想坐在第 $2$ 行，还有 $c$ 只猴子没有座位偏好。每个座位只能坐一只猴子，并且如果安排猴子入座，就必须满足每只猴子的偏好。

鲍尔最多可以安排多少只猴子入座？

## 思路
先让有偏好的猴子尽可能多的入座，如果有空座位就用那 $c$ 只没有偏好的猴子填。

## Code
``` cpp
#include <iostream>
using namespace std;
 
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n, a, b, c;
		cin >> n >> a >> b >> c;
		int ans = min(n, a)+min(n, b);
		if(n-a > 0) ans += min(n-a, c), c -= min(n-a, c);
		if(n-b > 0) ans += min(n-b, c), c -= min(n-b, c);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路
首先一定要满足有需求的猴子，所以先考虑第一排的 $a$ 和第二排的 $b$。第一排可以容纳的数量 $num_1=\min(m,a)$，第二排同理，得 $num_2=\min(m,b)$。综合一下就可以得到两排一共能坐的猴子数量。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,a,b,c,num1,num2;
int main(){
	cin>>t;
    while(t--){
        cin>>m>>a>>b>>c;
        num1=min(m,a);
		num2=min(m,b);
        cout<<num1+num2+min(2*m-num1-num2,c);
		cout<<endl;
    }
	return 0;
}
```

---

## 作者：Jasoncwx (赞：1)

[题目传送门！](/problem/CF2044C)
## 题目思路
我们知道，教室里有 $2$ 行座位，每行有 $m$ 个座位。座椅一共有 $2m$ 个座位。

先算出第一，二行最多能坐下多少只 $a,b$ 猴子，即 $tot=\min(m,a)+\min(m,b)$ 只。然后再看看剩下的位置能坐得下多少只 $c$ 猴子，即 $\min(2m-tot,c)$。

最后再把这两个算式相加即可。
## 代码
```cpp
while(t--){
		int m,a,b,c;
		cin>>m>>a>>b>>c;
		int row_1=min(m,a);
		int row_2=min(m,b);
		int rest=min(2*m-row_1-row_2,c);
		cout<<row_1+row_2+rest<<endl;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [Hard Problem](https://www.luogu.com.cn/problem/CF2044C) | Codeforces [C. Hard Problem](https://codeforces.com/contest/2044/problem/C)

更佳的阅读体验：[CF2044C 题解](https://blog.ryanli.top/index.php/archives/234/)

---

**简要题意**：教室里有两排座位，每排有 $m$ 个。$a$ 只猴子坐在第一排，$b$ 只猴子坐在第二排，$c$ 只猴子坐在剩下的位置上，问最多可以坐多少猴子。

因为 $c$ 只猴子可以坐到任意一排，所以我们只需要优先考虑必须坐在第一排的 $a$ 个和第二排的 $b$ 只猴子，将剩余的位置尽可能多的安排给剩下的 $c$ 只猴子即可。

```cpp
#include <iostream>
using namespace std;

int t, m, a, b, c, cnta, cntb;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cin >> m >> a >> b >> c;
        cnta = min(m, a), cntb = min(m, b);
        cout << cnta + cntb + min((m << 1) - cnta - cntb, c) << '\n';
    } return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# Solution
## 题目分析
贪心题。  
结论如下，为了安排尽量多的猴子，可以先安排有特殊需求的猴子，第一排可以放下 $\min(m,a)$ 只 $a$ 类猴子，第二排同理可以放下 $\min(m,b)$ 只 $b$ 类猴子，剩下的位置安排 $c$ 类猴子。  
此时答案即为 $\min(m,a)+\min(m,b)+\min(2 \times m-\min(m,a)-\min(m,b),c)$。  
## 赛时代码

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
void solve() 
{
	int m,a,b,c;
	cin>>m>>a>>b>>c;
	int ans=0;
	int x=m,y=m;
	ans+=min(m,a);
	x-=min(m,a);
	ans+=min(m,b);
	y-=min(m,b);
	ans+=min(x+y,c);
	cout<<ans<<'\n';
}
int main()
{
	int T;
	cin>>T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

### 题目翻译
鲍尔是折纸大学的老师。他的教室的座位一共有 $2$ 排，每排有 $m$ 个座位。

鲍尔正在教授 $a + b + c$ 猴子，他希望尽可能多的猴子分配到一个座位。鲍尔知道，其中 $a$ 只想坐在 $1$，$b$ 只想坐在 $2$，而 $c$ 没有偏好。每个座位只能坐一只猴子，如果每只猴子都坐着，就必须按照它的喜好。

鲍尔最多能容纳多少只猴子？

### 思路
设 $A$、$B$、$C$ 是三组猴子，使得 $A$ 中的猴子只能坐在 $1$、$B$ 中的行 $2$ 中，并且 $C$ 可以坐在任何地方。很明显，如果行 $1$ 中有自由空间，并且集合 $A$ 中有猴子，那么将猴子从集合 $A$ 安排到行 $1$ 是最佳的。这是因为来自集合 $C$ 的猴子可以坐在任何一排，并且在你已经坐了来自集合 $A$ 的猴子之后，可能还有空间留给集合 $C$ 中的同一只猴子。但是，如果你开始把猴子安排在前排 $C$，那么情况就不是这样了，因为你现在可能在后排留下空座位，但是在后排 $A$ 的猴子仍然没有安排座位。

因此，策略如下：从集合 $A$ 中尽可能多地安排猴子坐在前排，然后从集合 $B$ 中尽可能多地安排猴子坐在后排，然后从集合 $C$ 中尽可能多地安排猴子坐在后排，这样就得到了答案。

### 代码：
```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while (T --) {
		int n, a, b, c;
		cin >> n >> a >> b >> c;
		int num = min(a, n) + min(b, n);
		int cnt = max(0ll, n - a) + max(0ll, n - b);
		cout << num + min(c, cnt) << '\n';
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定 $a+b+c$ 个点和 $2m$ 个可选择的位置，这些可选择的位置分为两组，每组 $m$ 个，$a$ 个点只能选择第一组的位置，另外 $b$ 个点只能选择第二组的位置，剩下 $c$ 个点无限制。每个点最多只能选择一个位置，问最多有几个点可选择到位置。

## 解题思路

$a$ 个点只能选择第一组的位置，也就意味着如果 $a<m$ 则 $m$ 个位置不会被选满，只会被选择 $a$ 个位置，否则 $m$ 个位置都会被选满，所以可选到位置的最多点数就是 $\min(a,m)$。同理，$b$ 个点选择的位置与 $a$ 点选择的没有冲突，所以可选到位置的最多点数就是 $\min(b,m)$。$a$ 和 $b$ 选完后，还剩下 $2m-\min(a,m)-\min(b,m)$ 个位置没有选，所以 $c$ 可选到位置的最多点数就是 $\min(c,2m-\min(a,m)-\min(b,m))$，统计答案即可。

## AC 代码

[URL](https://codeforces.com/contest/2044/submission/296831888)。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll t,n,m,a,b,c,ans;

int main()
{
	t=read();
	
	while(t--)
	{
		n=read(); m=n; a=read();
		b=read(); c=read();
		ans=min(n,a)+min(n,b);
		n-=min(n,a); m-=min(m,b);
		write(ans+min(n+m,c)); endl;
	}

    return 0;
}
```

---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF2044C) & [CF 题目链接](http://codeforces.com/problemset/problem/2044/C)

# 题意简述：

有两排座位，每排 $m$ 个。有 $a$ 个人想坐第一排，$b$ 个人想坐第二排，$c$ 个人两排都愿意坐。注意：这 $a$ 个人要么坐第一排，要么没有位置坐；这 $b$ 个人要么坐第二排，要么没有位置坐。

求最多有多少人有座位坐。

# 思路分析：

贪心的思想。

第一排的座位优先给 $a$ 个人坐，第二排的座位优先给 $b$ 个人坐，再把两排剩下的所有座位（如果有剩余的话）尽量多的给剩下的 $c$ 个人坐。

# 赛时代码：

```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}
 
int T,m,a,b,c;
 
void solve(){
	cout<<min(a,m)+min(b,m)+min(c,max(0,m-a)+max(0,m-b))<<"\n";
	return;
}
 
int main(){
	T=read();
	while(T--){
		m=read(),a=read(),b=read(),c=read();
		solve();
	}
	return 0;
}
```

---

