# Contest Start

## 题目描述

### 题意描述

有 $n$ 个人参加某个竞赛，他们以 $x$ 分钟的间隔开始。

每个参赛者的比赛时长为 $t$ 分钟，因此第一个参赛者在 $t$ 时间结束比赛，第二个参赛者在 $t+x$ 时间结束比赛，依此类推。当一个参赛者完成比赛时，他们的不满意程度等于已开始比赛（或现在正好开始）但还没有完成比赛的参赛者人数。

求所有参赛者的不满意程度之和。

## 样例 #1

### 输入

```
4
4 2 5
3 1 2
3 3 10
2000000000 1 2000000000```

### 输出

```
5
3
3
1999999999000000000```

# 题解

## 作者：Noby_Glds (赞：9)

这题用数学方法就可以直接得出答案。
### 思路：
拿 $\texttt{6 3 8}$ 来举例，每个人的不满意程度分别是:$\texttt{2 2 2 2 1 0}$。

发现没，前面 $4$ 个人的不满意程度是一样的，我们把这个值叫做 $len$。

如何求 $len$ 呢？$len$ 实际上就是在第一个人参加比赛的期间又举办了多少场比赛。

显而易见，$len$ 等于 $t/x$。

如果第一个人参加比赛的时间足够举办多于总人数场的比赛呢？

因为最多只能举办 $n-1$ 场比赛，所以我们加一个 min 函数就行了。

到第五个人后，由于人数小于 $len$，不满意程度逐渐减一。

所以只有第一到第 $n-len$ 个人的不满意程度是 $len$。

很显然，从第 $n-len+1$ 到第 $n$ 个人，他们的不满意程度是从 $len-1$ 到 $0$ 的等差数列。

用小学数学就行了。
### 代码：
```cpp
#include <iostream>
using namespace std;
long long p,n,x,t;
int main(){
    cin>>p;
    for(int i=1;i<=p;i++){
    	cin>>n>>x>>t;
    	long long len=min(n-1,t/x);
    	cout<<len*(n-len)+(len-1)*len/2<<endl;
	}
}
```


---

## 作者：XYY1411 (赞：3)

# Contest Start

提交地址：[洛谷 CF1539A](https://www.luogu.com.cn/problem/CF1539A)，[
CodeForces CF1539A](https://codeforces.com/problemset/problem/1539/A)

## 题目大意

有 $n$ 个人比赛，每隔 $x$ 分钟有一人开始比赛，每个人比赛时长为 $t$，当每个人比赛结束时会有一个不满意程度，为已经开始比赛（或现在开始比赛）但尚未完成比赛的参与者人数，求所有人的不满意程度。

## 分析

盯着看一会儿，发现前几个人的不满意程度不一样，后面的人则是比前面的人少一。

我们看这组数据 `4 2 5`：

第一、二个人的贡献为 $2$，第三个人为 $1$，第四个人没有贡献，和为 $5$。

这组 `10 2 10`：

我们发现前几个的贡献为 $5$ ，第五到第十贡献为 $5, 4, 3, 2, 1, 0$，和为 $35$。

我们发现了规律，前几个都是 $\lfloor t \div x \rfloor$，最后一个往前为 $0$ 到 $\lfloor t \div x \rfloor$ 的每次增加一的数列，那么答案就有了。

注意开 `long long`，如果 $\lfloor t \div x \rfloor > n$ 的话等差数列是到不了 $\lfloor t \div x \rfloor$ 的，特判就行。

## $\color{green}\text{code}$

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iomanip>
using namespace std;
typedef long long ll;
ll k, n, x, t, tmp, ans;
int main() {
    cin >> k;
    while (k--) {
        cin >> n >> x >> t;
        tmp = t / x, ans = 0;
        if (n < tmp) {
            ans = (1 + n - 1) * (n - 1) / 2;
            cout << ans << endl;
            continue;
        }
        ans += (1 + tmp) * tmp / 2;
        n -= (1 + tmp);
        cout << ans + n * tmp << endl;
    }
    return 0;
}
```

---

## 作者：SalomeJLQ (赞：1)

题意不用说了，翻译一遍就很清楚了。

画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fuliet6c.png?x-oss-process=image/resize,m_lfit,h_870,w_1025)

相当于一堆长度相同的木棒，开头按照一定间隔排在一起，然后从每一根木棒结尾往下切，总共能切到多少次。也就是这些蓝点的数量。

我们发现这些点分为两部分，第一部分每一根木棒切下去都能切到相同数目的棒子，第二段是个递减的等差数列。

在第一段每次能切到 $\Big\lfloor\dfrac{t}{x}\Big\rfloor$ 根木棒这是很显然的吧。然后我们看这一段的结尾，就是总木棒数减去 $\Big\lfloor\dfrac{t}{x}\Big\rfloor$。然后第二段就是个等差数列求和，令 $a=\Big\lfloor\dfrac{t}{x}\Big\rfloor$，那么就是 $1$ 加到 $a-1$。

最后注意特判，如果没有第一段的情况那么直接对 $n-1$ 做等差数列求和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
ll k,n,x,t,a,ans;
int main(){
	k=read();
	while(k--)
		n=read(),x=read(),t=read(),
		a=min(n,t/x),ans=a*(n-a)+a*(a-1)/2,
		printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Mysterious_Mini (赞：1)

题目链接：[$\text{CF1539A}$](https://www.luogu.com.cn/problem/CF1539A)

### 分析：

我们先不考虑共有几个人，单纯考虑对于一组 $(x,t)$，它造成的选手不满意度是什么样的。

第一个选手的不满意度为 $0$，此后每一个人的不满意度增加 $1$ 。但是，不满意度是有限制的。只要人数足够，一定有人的不满意度可以达到 $\left\lfloor\dfrac{t}{x}\right\rfloor$，也就是最大值。由于最大值限制了后面选手不满意度的增加，所以可能会有多个最大值。

考虑构造数列 $A$，表示第 $i$ 个选手的不满意度。

$A_1 = 0$，$A_i = \min(A_{i - 1} + 1,~ \left\lfloor\dfrac{t}{x}\right\rfloor)$。

最终答案：$\sum\limits_{i=1}^k A_i$。

代码很好写，就不给了。

---

## 作者：wcop114514 (赞：0)

**题目分析**

我们把最多相同的不满意程度叫做 $a$。

而 $a=t \div x$。

到了第五个人，不满意程度逐渐 $-1$。

第一人到了 $n-a$ 人不满意程度是 $a$。

由此分析出从第 $n - a+1$ 人到第 $n$ 人，不满意程度是 $a-1$ 到 $0$ 的等差数列。

给个位大佬奉上代码
```cpp
#include <iostream>
using namespace std;
long long p,n,x,t;
int main(){
    cin>>p;
    while(p--){
    	cin>>n>>x>>t;
    	long long a=min(n-1,t/x);
    	cout<<a*(n-a)+(a-1)*a/2<<endl;
	}
}
```

---

## 作者：rainygame (赞：0)

感觉第一篇写的比较难懂，所以我决定补一篇题解。

首先，以第一组数据 `4 2 5` 为例，这里面每个人的不满意度分别为 $\{2,2,1,0\}$。（具体看样例解释）

可以发现前面有两个相同的数，通过模拟其它样例发现也有一些，那么为什么呢？

以第一组数据为例，第一个人在比赛结束的时候有 $2$ 个人还在参加，而第二个也是；但是到了第三个，发现没有那么多人了，所以就变成了 $1$；第四个后面一个都没有了，所以为 $0$。

我们把这个固定的值设为 $g$，那么可以发现 $g=\lfloor\frac{t}{x}\rfloor$，因为再多的就不在范围之内了。当然，这个数最多也就是 $n-1$，否则没有那么多人参加比赛。

然后又可以发现，共有 $n-g$ 个人的不满意度为 $g$，因为后面的人都灭有那么多人可以算。而后面是一个项数为 $g-1$，公差为 $1$ 的等差数列，直接用求和公式即可。

综上所述，答案为：

$$
\begin{aligned}
g&=\min\{\lfloor\frac{t}{x}\rfloor,n-1\}\\
ans&=g(n-g)+\frac{g(g-1)}{2}
\end{aligned}
$$

**十年 OI 一场空，不开 `long long` 见祖宗！**

---

## 作者：cff_0102 (赞：0)

首先看看第一个人比赛结束时的不满意程度是多少。

因为在第一个人之前没有人在参赛，所以他的不满意程度就是在他参赛的那 $t$ 秒内开始比赛的 $\lfloor\frac{t}{x}\rfloor$ 人（假设 $n\ge\lfloor\frac{t}{x}\rfloor+1$）。

再看看第二个人比赛结束时的不满意程度。此时第一个人比赛结束了，又有一个人刚开始比赛（假设 $n\ge\lfloor\frac{t}{x}\rfloor+2$），那么第二个人的不满意程度应该和第一个人一样。

这种情况持续到什么时候？

当第 $i-1$ 个人比赛结束后，所有人都已经开始参赛，没有新的开始比赛的人了。接着，第 $i$ 个人比赛结束。他的不满意程度就变成了 $\lfloor\frac{t}{x}\rfloor-1$。

这样，得出一个结论：不满意程度的总和应该是 $\lfloor\frac{t}{x}\rfloor+\lfloor\frac{t}{x}\rfloor+\dots+\lfloor\frac{t}{x}\rfloor+(\lfloor\frac{t}{x}\rfloor-1)+(\lfloor\frac{t}{x}\rfloor-2)+\dots+(\lfloor\frac{t}{x}\rfloor-\lfloor\frac{t}{x}\rfloor)=1+2+\dots+\lfloor\frac{t}{x}\rfloor+(n-\lfloor\frac{t}{x}\rfloor-1)\times\lfloor\frac{t}{x}\rfloor=\lfloor\frac{t}{x}\rfloor\times(\lfloor\frac{t}{x}\rfloor+1)\div2+(n-\lfloor\frac{t}{x}\rfloor-1)\times\lfloor\frac{t}{x}\rfloor$（假设 $n\ge\lfloor\frac{t}{x}\rfloor+1$）。

不过，当 $n\le\lfloor\frac{t}{x}\rfloor$ 时，不满意程度总和应该是 $\frac{n(n-1)}{2}$。

也就是说，分类讨论一下。当 $n\le\lfloor\frac{t}{x}\rfloor$ 时，输出 $\frac{n(n-1)}{2}$，否则输出 $\lfloor\frac{t}{x}\rfloor\times(\lfloor\frac{t}{x}\rfloor+1)\div2+(n-\lfloor\frac{t}{x}\rfloor-1)\times\lfloor\frac{t}{x}\rfloor$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);int t;cin>>t;while(t--){
		unsigned long long n,x,t;
		cin>>n>>x>>t;
		unsigned long long a=t/x;
		if(n<=a)cout<<n*(n-1)/2<<endl;
		else cout<<a*(a+1)/2+a*(n-a-1)<<endl; 
	}return 0;
}
```

注意数据范围，`int` 绝对会爆。

---

## 作者：lrmlrm_ (赞：0)

## 题意

有 $n$ 个人参加某个竞赛，他们以 $x$ 分钟的间隔开始。

每个参赛者的比赛时长为 $t$ 分钟，因此第一个参赛者在 $t$ 时间结束比赛，第二个参赛者在 $t+x$ 时间结束比赛，依此类推。当一个参赛者完成比赛时，他们的不满意程度等于已开始比赛（或现在正好开始）但还没有完成比赛的参赛者人数。

求所有参赛者的不满意程度之和。

## 思路

此题是数学题。

先看样例： `4 2 5` ，画个图理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/z0gxtder.png?x-oss-process=image/resize,m_lfit,h_3000,w_5000)

容易发现，前两位选手的不满意程度都是 $2$，接下来的依次递减。

再来一个样例 `5 2 6` 。

![](https://cdn.luogu.com.cn/upload/image_hosting/mck34xvk.png?x-oss-process=image/resize,m_lfit,h_3000,w_5000)

容易发现，前 $2$ 位选手的不满意程度都是 $3$，接下来也是依次递减。

多试一些样例，就会发现，每个样例的前几个人的不满意程度相等，接下来依次递减。我们假设前几个人的不满意程度都是 $s$，经过简单思考和观察图片就可以发现： $s=t\div x$ （包含除，在比赛期间有多少个人开始了比赛）。接下来考虑到底有几个人的不满意程度相等。由于过了接下来的人的不满意程度要递减到 $0$，从 $s-1$ 递减到 $0$ 一共是 $s$ 个数，那么前面不满意程度相等的人数就应该是 $n-s$ 个。

那么到这里这题也差不多了，把所有的人分成两部分，一部分是前面的 $n-s$ 个人，不满意程度都是 $s$，不满意程度之和是 $(n-s)\times s$。另一部分是后面的 $s$ 个人，不满意程度从 $s-1\sim0$ 递减，不满意程度之和是 $\sum\limits_{i=1}^{s-1}i$，利用等差数列公式，可以用 $(s-1)\times s\div2$ 表示。也就是所有人的不满程度之和应该是 $(n-s)\times s+(s-1)\times s\div 2$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,n,x,t,s;
signed main(){
	scanf("%lld",&k);
	while(k--){
		scanf("%lld%lld%lld",&n,&x,&t);
		s=min(t/x,n);
		printf("%lld\n",s*(n-s)+(s-1)*s/2);
	}
	return 0;
} 
```

---

## 作者：zbk233 (赞：0)

## 解题思路

看到数据范围 $(1\leq n,x,t\leq 2⋅10^9)$ 就说明这道题一定要使用数学方法。

拿样例里 $n,x,t$ 分明为 $4,2,5$ 的情况举例。

第一个人的参赛时间为 $0-5$；第二个人的参赛时间为 $2-7$；第三个人的参赛时间为 $4-9$；第四个人的参赛时间为 $6-11$。

那么他们的不满值就分别为 $2,2,1,0$。

对于这些不满值，我们可以把它们分为两部分：$2,2$ 与 $1,0$。

我们可以发现第一部分的不满值都是相同的，我们把这个值设为 $q$。

显而易见，$q$ 等于 $t/x$。

但是，我们需要特判第一个人参加比赛的时间足够举办多于总人数场的比赛的情况。

这时候，$q$ 的值就为 $n-1$。

那么，$q$ 的值就应该取 $\min(t/x,n-1)$。

容易发现值为 $q$ 的数有 $n-q$ 个。

而对于第二部分的不满值，很明显是一个等差数列，利用等差数列求和公式就能很容易求出第二部分的和。

## 参考代码

```cpp
#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long k, n, x, t, q;
	cin >> k;
	while (k--)
	{
		cin >> n >> x >> t;
		q = min(n - 1, t / x);
		cout << q * (n - q) + q * (q - 1) / 2 << '\n';
	}
	return 0;
}
```


---

## 作者：Booksnow (赞：0)

# Contest Start

## 题目大意

有 $n$ 个人报名参加一个比赛，从 $0$ 时刻开始每隔 $x$ 分钟有一个人开始比赛，每个人参赛时间相同，均为 $t$ 。定义一个选手的**不满意度**为他结束比赛时**已经开始但尚未结束比赛**的人数，求所有选手不满意度的总和。

## 题外话

这场 $CF$ 私以为 $B$ 题才是最简单的一道题， $A$ 题比 $B$ 题要难一些，但其实也比较容易。

## 分析

我们可以先考虑分析一下样例（下展示样例 $4$ 、 $2$ 、 $5$ ）：

|  | 一号 | 二号  |三号  | 四号 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| **开始时间** | 0 | 2 | 4 | 6 |
| **结束时间** | 5 | 7 | 9 | 11 |
| **不满意度** | 2 | 2 | 1 | 0 |

其实题目告诉我们每个选手的参赛时间相同且开始时间有着相同的间隔，应该不难想到肯定又一定的**规律**存在。

就例如这组样例，虽然比较小，但是我们也能注意到，一号和二号的不满意度没有变化，想象有更多的参赛选手，是否会有更多的选手不满意度为 $2$ ？至于最后两个选手不满意度变化的原因，很显然其实是因为后面已经没有更多的选手了，所以会一次递减 $1$ 。

于是很容易想到，其实答案就是前面**一串相同**的加上后面的**等差数列**，重点是如何求前面一串相同不满意度的**个数**。

这个其实比较容易想，就是 $\lfloor \frac{t}{x}\rfloor $ ，参赛的时间除以间隔，想一想其实就是在自己参赛的这段时间内有多少人开始了比赛。

又因为**最后一个人的不满意度**肯定为 $0$ ，肯定能和前面形成一串长度未知的递减数列（如果不能，那其实就是所有人的不满意度肯定为 $0$ 了，这种情况不影响我们的讨论）。

这个数列的长度是多少呢？他肯定会一直递增到一个人的参赛时间内**最多有多少人开始比赛**的数量，也及时我们的 $\lfloor \frac{t}{x}\rfloor $ ，最后我们只需要注意一个地方，就是可能**人数不够**，只需要在该长度和 $n$ 之间取最小值就行了。

既然我们已经知道了这里的长度 $l$ ，前面一连串相等值的长度就是 $n-l$ ，加起来就完了。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int k,n,x,t;
signed main()
{
	k=read();
	while(k--){
		n=read(),x=read(),t=read();
		int temp=min(t/x,n-1);
		int ans=(n-temp)*temp;
		temp--;
		ans+=(1+temp)*temp/2;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：bifanwen (赞：0)

[CSDN同步](https://blog.csdn.net/bifanwen/article/details/118314049)

[博客园同步](https://www.cnblogs.com/bifanwen/p/14947823.html)

[原题链接](https://www.luogu.com.cn/problem/CF1539A)

简要题意：略。

考虑一个位置的最大不满意度，就是在 $t$ 的时间内，有 $\lfloor \frac{t}{x} \rfloor$ 个选手间隔 $x$ 时间开始比赛，于是其不满意度为 $\lfloor \frac{t}{x} \rfloor$. 不妨设 $\text{mid} = \lfloor \frac{t}{x} \rfloor$

这个不满意度取不到的时候，你会发现选手数量不够了。因此易得答案的贡献值长这样：

$\text{mid},\text{mid},\text{mid} \cdots \text{mid},\text{mid}-1,\text{mid}-2 \cdots 0$

于是考虑中间选手的位置。很明显是 $n-\text{mid}$.

两边求和。注意特判 $n<\text{mid}$ 的情况。

时间复杂度：$\mathcal{O}(T)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ld long double

inline ll read(){char ch=getchar(); int f=1; while(!isdigit(ch)) {if(ch=='-') f=-f; ch=getchar();}
	   ll x=0;while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return x*f;}

int T; ll n,x,t;

int main() {
	T=read(); while(T--) {
		n=read(),x=read(),t=read();
		ll mid=t/x;
		if(n<mid) {printf("%lld\n",n*(n-1)/2); continue;}
		ll lft=(n-mid)*mid;   //左边可以取到 mid 的答案
		ll rht=(mid-1)*mid/2; //右边等差数列求和
		printf("%lld\n",lft+rht);
	}
	return 0;
}

```

---

