# Bad Mood

## 题目描述

给定两个正整数 $M$ 和 $N$。有一个 $M$ 行 $N$ 列的正方形格子。

现在，要在每个格子里画上其中一条对角线。在此基础上，考虑一个无向图，该图的顶点对应于格子的角（共有 $(M + 1) \times (N + 1)$ 个顶点），画上的对角线对应于图的边。定义通过这种方式能形成的连通分量的数量为得分。

请计算可能的最小得分和最大得分。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_xmascon21_b/0651d892dadc631ce7f050fce6b1391d1aef7999.png)示例中得分为 $10$ 的情况

## 说明/提示

### 限制

- $1 \le M \le 10^9$。
- $1 \le N \le 10^9$。

### 样例解释 #1

得分为 $6$ 和得分为 $7$ 的示例分别如下图所示：

![得分为 6 的示例](https://img.atcoder.jp/xmascon21/105091090192bc5be451863d86ff441c.png)

![得分为 7 的示例](https://img.atcoder.jp/xmascon21/b293f4f8d17c9c01555ac5bc4d9c3b72.png)

## 样例 #1

### 输入

```
2 3```

### 输出

```
6 7```

# 题解

## 作者：Nightsky_Stars (赞：8)

题目大意：给定一个 $n$ 行 $m$ 列的格子。现在，要在每个格子里画上其中一条对角线。在此基础上，考虑一个无向图，该图的顶点对应于格子的角，画上的对角线对应于图的边。通过这种方式能形成的连通分量的数量为得分，计算可能的最小得分和最大得分。

容易看出，第一个数是 $(n+1)\times(m+1)-n\times m$，化简得 $n+m+1$。

下一个数是上一个数加上 $\frac{n\times m+(n-2)\times(m-2)}{4}$，化简得 $\frac{n\times m+n+m}{2}+2$。

## CODE:
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;//记得开long long
	cin>>n>>m;
	cout<<n+m+1<<" "<<(n*m+n+m)/2+2<<"\n";
	return 0;
}
```

---

## 作者：zyc_bot (赞：3)

~~蒟蒻第一篇题解，管理大大求过。~~

## 题意简述

还没有翻译，可以暂且先看看 [我的](https://www.luogu.com.cn/paste/idt54m2g)。

这里提供一个简述版本：

给定一个 $M \times N$ 的格子，每个格子画一条对角线。构成无向图，顶点为格子角，边为对角线。求构成的连通分量最小和最大可能数量。

## 思路分析

这么大的数据范围一眼丁真鉴定为规律题，来手推一下。

不难发现，第一个数就是 $(b+1) \times (a+1)-b\times a$，化简一下，就是 $a+b+1$。

再看看第二个数，明显就是前面的拿一个数再加上 $\frac{a \times b + (a-2) \times (b-2)}{4} $，稍微再化简一下，明显就是 $a+b+2+ \frac{a \times b - a - b} {2}$。

## AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<20+5];
inline long long read(){
	long long x=0;
	char c=gc();
	while(!isdigit(c)){
		c=gc();
	}while(isdigit(c)){
		x=x*10+(c^48);
		c=gc();
	}return x;
}

long long a, b;

int main()
{
	a = read(), b = read();
	long long ans = (a + b + 1), ans1 = a + b + 2 + (a * b - a - b) / 2;
	printf("%lld %lld\n", ans, ans1); 
}

```


---

## 作者：dulinfan2023 (赞：1)

[题目传送门](/problem/AT_xmascon21_b)

# 思路

很明显是一道找规律~~的水题~~。

最小得分很容易得出是 $\lparen n+1 \rparen \times \lparen m+1 \rparen- n \times m = n \times m + 1$。

而最大得分即为最小得分 $n+m+1$ 再加上 $\frac{n \times m  + \lparen n-2 \rparen \times \lparen m-2 \rparen}{4}$。

#### 化简过程：

$\begin{aligned}n+m+1+\frac{n \times m  + \lparen n-2 \rparen \times \lparen m-2 \rparen}{4}\end{aligned}$

$\begin{aligned}= \frac{4 \times n + 4 \times m + 4 + n \times m  + \lparen n-2 \rparen \times \lparen m-2 \rparen}{4}\end{aligned}$

$\begin{aligned}= \frac{4 \times n + 4 \times m + 4 + n \times m  + m \times n - 2 \times m - 2 \times n + 4}{4}\end{aligned}$

$\begin{aligned}= \frac{2 \times m \times n + 2 \times m + 2 \times n + 8}{4}\end{aligned}$

$\begin{aligned}= \frac{m \times n + m + n + 4}{2}\end{aligned}$

$\begin{aligned}= \frac{m \times n + m + n}{2} + 2\end{aligned}$

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//记得开long long
const int N=1e6+10;
#define debug() cout<<"come on"<<'\n'
signed main(){
	int n,m;
	cin>>n>>m;
	int ans1=n+m+1,ans2=(n*m+n+m)/2+2;
	cout<<ans1<<" "<<ans2; 
	return 0;
}
```

~~求通过~~。

---

## 作者：_Sky_Dream_ (赞：1)

# [传送门](https://www.luogu.com.cn/problem/AT_xmascon21_b)

很简单。第一个数是 $(n+1)\times(m+1)-n \times m$，化简一波：

$(n+1) \times (m+1)-n \times m$

$=n \times m+n+m-n \times m+1$

$=n+m+1$

好，下一个数……

下一个数是前一个数再加上 $\frac{n \times m + (n-2) \times (m-2)}{4}$。

好烦，再化简一波：

$\frac{n \times m + (n-2) \times (m-2)}{4} +n+m+1 $

$=\frac{n \times m + (n-2) \times (m-2)+4n+4m+4}{4}$

$=\frac{n \times m + n \times m -2n-2m+4+4n+4m+4}{4}$

$=\frac{2 \times n \times m + 2 \times n + 2 \times m +8}{4}$

$=\frac{n \times m + n +m}{2}+2$

好。接下来敲代码：
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
int n,m;
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	cout<<n+m+1<<' '<<(n*m+n+m)/2+2;
	exit(0);
}
signed main(){Enchanted();}

```

~~完结撒花。~~

诶，咋 WA 了？

注意看最后：

$1 \le N,M \le 10^9$……

~~不开 ``long long`` 见祖宗……~~

AC node:
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	cout<<n+m+1<<' '<<(n*m+n+m)/2+2;
	exit(0);
}
signed main(){Enchanted();}
```


---

## 作者：QoQ_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_xmascon21_b)

这是一道比较简单的结论题，一般这种题目都是有公式的，所以先从样例入手：

通过样例我们能看出，最小得分的公式为 $(n+1) \times (m+1)-n \times m$，不过这公式未免太长了……让我们来化简一下：

$(n+1) \times (m+1)-n \times m$

$= n\times m+n+m+1-n \times m$

$=n+m+1$

通过再次观察，最大得分的公式为最小得分再加上 $\frac{n \times m+(n-2)\times(m-2)}{4}$，让我们再来化简一下：

$n+m+1+\frac{n \times m+(n-2)\times(m-2)}{4}$

$=\frac{4\times n+4\times m+4+n \times m+(n-2)\times(m-2)}{4}$

$=\frac{4 \times n+4\times m+4+n \times m-2\times n-2 \times m+n \times m+4}{4}$

$=\frac{2 \times n+2 \times m+8+2\times n\times m}{4}$

$=\frac{n+m+n\times m}{2}+2$

这样就把公式全部化简完成了，最后注意题目结尾的 $1\le n,m \le 10^9$，所以要开 `long long`。

## code 参考：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a,b;
int main(){
    cin>>n>>m;
    a=n+m+1;
    b=n*m+n+m;
    b/=2;
    b+=2;
    cout<<a<<" "<<b<<"\n";
    return 0;
}
```
完结撒花~~~

---

## 作者：封禁用户 (赞：0)

# AT_xmascon21_b Bad Mood

## 题意
给定你一个 $n\times m$ 的矩形。

以一条对角线为基础上，制作一个无向图，该图的顶点对应于格子的共有 $(m+1) \times (n+1)$ 个顶点，画上的对角线对应于图的边。这种方式能形成的连通分量的数量为得分。

求最小得分和最大得分。
## 思路

最小得分是好算的，就是 $(n+1)\times (m+1)−n\times m$,也就是 $n+m+1$。

最大得分就是最小得分加上 $\frac{n\times m-(n-2)\times(m-2)}{4}$,即 $\frac{n\times m+n+m}{2}+2$。

#### 注意
**$n$ 和 $m$ 要用 long long 类型**

## 代码
```
#include <bits/stdc++.h>
using namespace std;
long long a, b;
int main() {
	cin>>a>>b;
	cout<<a+b+1<<' '<<(a+b+a*b)/2+2<<'\n';
	return 0;
}
```

---

## 作者：Mierstan085 (赞：0)

这是一道比较简单的结论题。

不难发现，最小得分为 $(n+1)(m+1)-nm$，化简得到:

$$
\begin{aligned}
&(n+1)(m+1)-nm\\
= &nm+n+m+1-nm\\
=&n+m+1
\end{aligned}
$$

继续不难发现，最大得分应该是最小得分加上 $\lfloor \frac{(n-2)(m-2)+nm}{4} \rfloor$ 的结果，化简，得到（忽略向下取整是因为 C++ 的除法是默认向下取整的）：

$$
\begin{aligned}
&n+m+1+\frac{(n-2)(m-2)+nm}{4}\\
=&\frac{4n+4m+4+(n-2)(m-2)+nm}{4}\\
=&\frac{4n+4m+4+nm-2n-2m+4+nm}{4}\\
=&\frac{2n+2m+8+2nm}{4}\\
=&\frac{n+m+nm}{2}+2
\end{aligned}
$$

然后算就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    long long a, b;
    cin >> a >> b;
    cout << a + b + 1 << ' ' << (a + b + a * b) / 2 + 2;
}
```

[record.](https://www.luogu.com.cn/record/148944144)

---

## 作者：Programming_Konjac (赞：0)

# 思路
不难看出，第一个数就是 $(a+1) \times (b+1)-a\times b$，通过化简，得到 $a+b+1$。

第二个数，是第一个数加上 $\lfloor \frac{n\times m+(n-2) \times (m-2)}{4} \rfloor$ 后的结果，带入式子，第二个数就是 $a+b+1\lfloor \frac{n\times m+(n-2) \times (m-2)}{4} \rfloor$，通过化简，得到 $\lfloor\frac{(a+1)\times(b+1)+1}{2}\rfloor+1$，最后进行输出。

**注意：记得开 `long long`！**
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long a,b;
	cin>>a>>b;
	cout<<a+b+1<<" "<<((a+1)*(b+1)+1)/2+1;
	return 0;
}
```


---

## 作者：IOI_official (赞：0)

## 思路：
这题 $1 \le M,N \le 10^{9}$，一眼就是找规律题，否则一般的图论题不会这么出的。

不难发现，$a=M+N+1$，$b$ 就是 $a+\frac{(N-2)\cdot (M-2)+N\cdot M}{4} $，化简后得 $\frac{M\cdot N+M+N}{2}+2 $，所以这道题就迎刃而解了。

数据会爆 `int`，记得开 `long long`。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int main(){
	cin>>a>>b;
	cout<<a+b+1<<" "<<(a*b+a+b)/2+2;
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

# 题意

给定你一个 $n\times m$ 的矩形。以一条对角线为基础上，制作一个无向图，该图的顶点对应于格子的共有 $(m+1)\times(n+1)$ 个顶点，画上的对角线对应于图的边。这种方式能形成的连通分量的数量为得分。求最小得分和最大得分。

# 思路

- 最小值：容易看出，第一个数是 $(n + 1) \times (m + 1) - n \times m$，然后我们进行化简得 $n + m + 1$。
- 最大值：就是最小值加上 $\frac{n \times m + (n - 2) \times (m - 2)}{4}$，我们再次进行化简得 $\frac{n + m + (n \times m)}{2} + 2$。

最后注意因为 $1 \le N \le 10^9$ 并且 $1 \le M \le 10^9$ 所以相乘已经超过了 ``int`` 的范围，记得开 ``long long``。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int n,m;
    cin>>n>>m;
    cout<<(n+m+1)<<" "<<(n+m+n*m)/2+2<<endl;
return 0;
}
```

---

## 作者：fried_chicken (赞：0)

通过观察可得，第一个数是 $(a+1) \times (b+1)-a \times b$ ，也就是 ```(a+1)*(b+1)-a*b``` 其实根本没必要化简，不化简也能做出来（其他题解都化简了，不化简只不过是代码比较长罢了，这里用不化简来做一下）。

第二个数是第一个数加上 $\frac{a\times b+(a-2)\times (b-2)}{4} $ ，也就是 $(a+1) \times (b+1)-a \times b + \frac{a\times b+(a-2)\times (b-2)}{4}$ ，也就是 ```(a+1)*(b+1)-a*b+(a*b+(a-2)*(b-2))/4``` ，也不需要化简。

记得开 long long 。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
signed main(){
	cin>>a>>b;
	cout<<(a+1)*(b+1)-a*b<<' '<<(a+1)*(b+1)-a*b+(a*b+(a-2)*(b-2))/4<<endl;
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## AT_xmascon21_b Bad Mood 题解
### 分析
最小得分很容易发现为所有的顶点减去 $n \times m$，即 $(n+1) \times (m+1) - n \times m$。

把公式化简得 $n+m+1$

通过观察，最大得分为 $(n+1) \times (m+1) - n \times m + \frac{n\times m +(n-2)\times (m-2)}{4}$。

把公式化简得 $\frac{n +m + n\times m}{2} +2$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
signed main()
{
  	cin>>n>>m;
	cout<<n+m+1<<" "<<(n+m+n*m)/2+2<<"\n";
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

很容易从题中或样例中看出：第一个答案应该为 $(n+1)(m+1)-nm$，即 $n+m+1$。

第二个答案，也很显然，是在第一个答案的基础上加上 $\lfloor\frac{(n-2)(m-2)+nm}{4}\rfloor$。

化简就不写了，过程可以参考其他大佬的题解。答案为 $\frac{nm+n+m+4}{2}$。

注意，$1\le n,m\le 10^9$，乘积远超 ``int`` 范围。得开 ``long long``。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    cout<<n+m+1<<" ";;
    cout<<((n*m+n+m+4)>>1)<<'\n';
    return 0;
}
```

---

