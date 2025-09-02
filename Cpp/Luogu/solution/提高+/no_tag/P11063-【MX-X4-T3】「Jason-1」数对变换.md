# 【MX-X4-T3】「Jason-1」数对变换

## 题目背景

原题链接：<https://oier.team/problems/X4D>。

## 题目描述

对于一个**正整数**数对 $(x, y)$，定义一次变换为：选择其中一个数 $a$，记另一个数为 $b$，同时选择一个正整数 $k \leq a$，然后将 $a$ 除以 $k$ 向下取整，同时将 $b$ 乘以 $k$。

形式化地说，对于数对 $(x,y)$，你可以执行以下两种变换：

- 类型 1：取 $1 \le k \le x$，令 $(x,y) \gets (\lfloor \frac{x}{k} \rfloor, y \cdot k)$。
- 类型 2：取 $1 \le k \le y$，令 $(x,y) \gets (x \cdot k, \lfloor \frac{y}{k} \rfloor)$。

显然，变换后的数对仍然是正整数数对。

给出两组正整数数对 $(a, b)$ 与 $(c, d)$，你需要执行**不超过 $\bm{65}$ 次**变换将 $(a, b)$ 变为 $(c, d)$，或者报告无解。**注意：你不需要最小化执行变换的次数**。

需要注意数对是有序的，即若 $x \neq y$，则 $(x,y) \neq (y,x)$。

本题使用**自定义校验器**检验你的答案是否正确，因此若有多种满足条件的方案，你只需要输出**任意一种**。

## 说明/提示

**【样例解释】**

对于第 1 组数据，不需要进行任何操作，因为初始时 $a = c$ 且 $b = d$。

对于第 2 组数据，可以证明无解。

对于第 3 组数据，第一次变换后 $(a,b)=(1,4)$，第二次变换后 $(a,b)=(3,1)$，第三次变换后 $(a,b)=(1,2)$。

对于第 4 组数据，一次变换即可使 $a = c$ 且 $b = d$。

对于第 5 组数据，可以证明无解。

对于第 6 组数据，第一次变换后 $(a,b)=(26,129)$，第二次变换后 $(a,b)=(52,64)$。

对于第 7 组数据，第一次变换后 $(a,b)=(31438,3878395026435)$，第二次变换后 $(a,b)=(313814116,388538872)$。

**【数据范围】**

**本题采用捆绑测试。**

令 $n=\max(a,b,c,d)$。

| 子任务 | $n\le$| 特殊性质 | 分值 |
| :--------------: | :-----: |:-----:| :--------: |
| 1 | $6$ | 无 | $7$ |
| 2 | $10^5$ | A | $11$ |
| 3 | $10^5$ | C | $13$ |
| 4 | $10^6$ | B | $23$ |
| 5 | $10^9$ | C | $19$ |
| 6 | $10^9$ | 无 | $27$ |

- 特殊性质 A：保证 $\dfrac{a}{c}=\dfrac{d}{b}$。
- 特殊性质 B：保证 $a=b$ 且 $c=d$。
- 特殊性质 C：保证 $a,b,c,d$ 在值域内独立均匀随机生成。

对于 $100\%$ 的数据，$1 \le T \le 10^4$，$1 \le a,b,c,d \le 10^9$。

## 样例 #1

### 输入

```
7
1 1 1 1
1 2 1 1
2 2 1 2
10 10 2 50
5 5 4 10
80 43 52 64
987654321 123456789 313814116 388538872
```

### 输出

```
0
-1
3
1 2
2 3
1 2
1
1 5
-1
2
1 3
2 2
2
1 31415
2 9982
```

# 题解

## 作者：InformationEntropy (赞：8)

### 题目分析

每次变换，$a,b$ 都在变化，难以把控，故考虑把 $a,b$ 捆绑在一起。注意到只要变换到 $a\cdot b = c\cdot d$ 则只需两步便可结束：

$$(a,b)\rightarrow(\gcd(a,c),\dfrac{b\cdot a}{\gcd(a,c)})\rightarrow(c,d)$$

故只需考虑 $a\cdot b$ 的变化即可。

又有  $\forall a,b,k \in \N,k\ne0,$

$$\left\lfloor\dfrac{a}{k}\right\rfloor\cdot b\cdot k \le a\cdot b$$

当且仅当 $k \mid a$ 时取等。

这意味着，经过若干次操作后，数对中两数的积不会增加，若初始 $a\cdot b <c\cdot d$ 直接无解。

考虑 $a\cdot b$ 在进行操作 $(1,k)$ 前后的变化量：

$$a=tk+r$$
$$a\cdot b-\left\lfloor\dfrac{a}{k}\right\rfloor\cdot k\cdot b=a\cdot b-t\cdot k\cdot b=a\cdot r$$

（操作 2 同理。）

由于 $a,b$ 动态变化，考虑始终将其一固定（即 $a,b$ 交替变化为固定值），不妨令定值为 1，则每次变换， $a\cdot b$ 减少 $r$，考虑从最后一次操作逆推，$r=a\cdot b-c\cdot d$ 时结束操作，此时可令 $k=c\cdot d$，则 $a\cdot b<2\cdot c\cdot d$ 时满足上述条件。

对于 $a\cdot b \ge c\cdot d\cdot2$，控制 $a,b$ 之一为 1，另一个除以比它的一半大一点的数，可实现 $a\cdot b$ 以 2 的幂次递缩，保证复杂度为 $\operatorname{O}(\log n)$，直到 $a\cdot b<2\cdot c\cdot d$，化归为上一种情况。

最终变化：

$$(a,b)\rightarrow(ab,1)\rightarrow(1,\left\lfloor\dfrac{ab}{2}\right\rfloor+1)\dots\rightarrow(1,cd)/(cd,1)\rightarrow(c,d)$$


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
template<class T>inline void read(T &x){
	x=0;
	int f=0;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) f^=!(c^45);
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
ll gcd(ll a,ll b){
	if(a%b == 0){
		return b;
	}
	return gcd(b,a%b);
}
struct node{
	ll op,k;
}ans[65];
int main(){
	int T;
	read(T);
	ll a,b,c,d;
	for(int i=1; i<=T; i++){
		read(a);
		read(b);
		read(c);
		read(d);
		ll k = a*b-c*d;
		if(c*d == 1 && a*b != 1){
			cout << -1 << endl;
			continue;
		}
		if(a==c && b==d){
			cout << 0 << endl;
			continue;
		}//这两个特判不要忘
		if(k == 0){
			cout << 2 << endl;
			cout << 1 << " " << a/gcd(a,c) << endl;
			cout << 2 << " " << c/gcd(a,c) << endl;
		}else if(k < 0){
			cout << -1 << endl;
		}else{
			ll u=a*b,v=c*d;
			int cnt = 0;
			ans[++cnt].op = 2;
			ans[cnt].k = b;
			int op = 0;
			while(u >= (v<<1)){
				ans[++cnt].op = op+1;
				ans[cnt].k = (u>>1)+1;
				u = (u>>1)+1;
				op ^= 1;
			}//a,b辗转变为1
			if(op == 1){
				ans[++cnt].op = 2;
				ans[cnt].k = u;
			}
			ans[++cnt].op = 1;
			ans[cnt].k = v;
			ans[++cnt].op = 2;
			ans[cnt].k = c;
			cout << cnt << endl;
			for(int j=1; j<=cnt; j++){
				cout << ans[j].op << " " << ans[j].k << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：mahaihang1 (赞：4)

## 50pts
观察部分分，容易发现性质A：$\dfrac{a}{c}=\dfrac{d}{b}$ 很特殊，考虑如何将普通数据转化成这种形式。

不妨将设将 $b$ 变为 $a \times b$，发现对于一个数 $x$，如果有 $\lfloor \frac{b}{x} \rfloor=1$，可以选择 $k=x$ 进行一次操作 $1$ 和操作 $2$，这样能使 $b$ 变为 $x$，当 $x=\lfloor \frac{b}{2} \rfloor+1$ 时最优。

## 100pts
发现 50pts 的做法操作次数最高是 $\log_2{10^{18}} \times2+3 \approx 121$ 次，不符合题目要求。

考虑在转化数据的时候，我们可以在操作 $2$ 的时候可以再选择 $k=\lfloor \frac{x}{2} \rfloor+1$，这时在操作后 $b=\lfloor \frac{x}{2} \rfloor+1$，最多只需进行 $\log_2{10^{18}}+3 \approx 62$ 次操作，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,c,d,sum;
queue <pair<int,int> > q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		while(q.size()) q.pop();
		cin>>a>>b>>c>>d;
		if(a*b<c*d||((c==1)+(d==1)==2&&(a==1)+(b==1)!=2)){
			cout<<-1<<endl;
			continue;
		}
		q.push(make_pair(1,a));
		b*=a;
		sum=2;
		while(b/(c*d)!=1){
			int k=b/2+1;
			q.push(make_pair(sum,k));
			b/=k,b*=k;
			sum=3-sum;
		}
		if(sum==2) q.push(make_pair(2,c*d)),q.push(make_pair(1,c*d));
		else q.push(make_pair(1,c*d));
		q.push(make_pair(2,c));
		cout<<q.size()<<endl;
		while(q.size()){
			cout<<q.front().first<<" "<<q.front().second<<endl;
			q.pop();
		}
	}
	return 0;
}

```

---

## 作者：xiaoliebao1115 (赞：4)

观察部分分，发现有一个 $a\times b=c\times d$ 的东西，那么显然我们可以先让进行 $(1,a)$ 操作，再进行 $(2,c)$ 操作。

那么问题就转化成了如何在有限的次数内将 $a\times b=c\times d$，初始时令 $op=2$。

我们先进行一次 $(1,a)$ 操作，把 $b$ 变成 $a\times b$。

- 若 $a\times b<c\times d$，那么一定不行，因为除法只会多减掉一部分，而无法增加。
- 若 $c\times d\le\frac{a\times b}{2}$，那么可以一直进行 $(op,\lfloor\frac{a\times b}{2}\rfloor+1)$ 操作，$op$ 初始为 $2$，之后 $1$ 和 $2$ 交替变换。这样的操作总会让 $a\times b$ 变为 $\lfloor\frac{a\times b}{2}\rfloor+1$，在一般情况下总会使得 $c\times d>\frac{a\times b}{2}$，除了 $c\times d=1$ 的时候，永远不行。
- 当 $c\times d>\frac{a\times b}{2}$ 的时候，进行一次 $(op,c\times d)$ 操作就可以使得 $a\times b=c\times d$。
  
这里的变换次数应该是 $\log{(a\times b)}$ 级别的，可以通过。

整体下来感觉应该是中位绿的一道题，简介里面说黄感觉有点太离谱了。

放上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,l[75],r[75];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        int a,b,c,d,cnt=0;
        cin>>a>>b>>c>>d;
        if(c==1&&d==1){
            if(a==1&&b==1) cout<<0<<endl;
            else cout<<-1<<endl;
            continue;
        }
        if(c*d>a*b){
            cout<<-1<<endl;
            continue;
        }
        cnt++;
        l[cnt]=1,r[cnt]=a;
        int sum=a*b,op=2;
        while(c*d<=sum/2){
            cnt++;
            l[cnt]=op,r[cnt]=sum/2+1;
            if(op==2) op=1;
            else if(op==1) op=2;
            sum=sum/2+1;
        }
        if(a*b!=c*d){
            cnt++;
            l[cnt]=op,r[cnt]=c*d;
            if(op==2) op=1;
            else if(op==1) op=2;
        }
        if(op==1){
            cnt++;
            l[cnt]=op,r[cnt]=d;
        }
        else{
            cnt++;
            l[cnt]=op,r[cnt]=c;
        }
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++)
            cout<<l[i]<<' '<<r[i]<<endl;
    }
    return 0;
}
```

---

## 作者：pigeonteam (赞：4)

易得，当 $a \times b < c \times d$ 时，一定无解。  
然后通过样例，不难发现(~~至于为什么，看了下面的内容就可以自己推出来了~~)当 $c \times d = 1$ 且 $a \times b \ne 1$ 时，无解。  
然后在不损耗的情况下将 $\left\{ a , b \right\}$ 转移为 $\left\{ 1 , a \times b \right\}$ 。  
不难发现，在保证 $a , b$ 中有一个为 $1$ 的情况下每次操作最多将现在的 $a \times b$ 减去 $\lfloor \frac{a \times b - 1 }{2} \rfloor$。  
最后加一个当 $a \times b = c \times d$ 时转换的操作以及输出时判断操作次数是否过多的操作就做完了。  
样例代码：

``` c++
ll t, a, b, c, d;
vector<pair<int, ll>> ans;

int main()
{
    FastIO::read(t);
    while (t--)
    {
        ans.clear();
        FastIO::read(a, b, c, d);
        if ((c * d > a * b))
        {
            puts("-1");
            continue;
        }
        else if (a * b == c * d)
        {
            if (a == c)
            {
                puts("0");
                continue;
            }
            else
            {
                cout << 2 << endl;
                cout << 1 << ' ' << a << endl;
                cout << 2 << ' ' << c << endl;
                continue;
            }
        }
        else if (c * d == 1)
        {
            puts("-1");
            continue;
        }
        else
        {
            ans.push_back({1, a});
            b = a * b;
            a = 1;
            while (a * b > c * d)
            {
                ll sub = a * b - c * d;
                if (a == 1)
                {
                    if (sub < (b >> 1))
                    {
                        // cerr << "first ";
                        ans.push_back({2, b - sub});
                        a *= (b - sub);
                        b /= (b - sub);
                    }
                    else
                    {
                        // cerr << "secon ";
                        ans.push_back({2, (b >> 1) + 1});
                        a *= ((b >> 1) + 1);
                        b /= ((b >> 1) + 1);
                    }
                }
                else
                {
                    if (sub < (a >> 1))
                    {
                        // cerr << "third ";
                        ans.push_back({1, a - sub});
                        b *= (a - sub);
                        a /= (a - sub);
                    }
                    else
                    {
                        // cerr << "forth " << b * ((a >> 1) + 1) << ' ';
                        ans.push_back({1, (a >> 1) + 1});
                        b *= ((a >> 1) + 1);
                        a /= ((a >> 1) + 1);
                    }
                }
                // cerr << a << ' ' << b << ' ' << c << ' ' << d << endl;
            }
            if (a != c)
            {
                ans.push_back({1, a});
                ans.push_back({2, c});
            }
        }
        if (ans.size() > 65)
            puts("-1");
        else
        {
            FastIO::println(ans.size());
            for (auto i : ans)
            {
                FastIO::write(i.first, i.second);
                putchar('\n');
            }
        }
    }
    return 0;
}
```

---

## 作者：UniGravity (赞：3)

## Solution P11063 【MX-X4-T3】「Jason-1」数对变换

鲜花：怎么 T2 比这题还难啊。

这篇文章主要讲解如何得出正解的思维过程。

观察题目，发现**不超过 $65$ 次操作**非常的具有提示性。结合 $10^9$ 的数据范围，有这些可能：
1. 进行 $\log10^9$ 次行动，每次行动花费代价为 $2$。
2. 进行 $\log10^{18}$ 次操作。

发现题目中的操作有带**下取整**，如果不带，那么无论怎么操作 $(x,y)$ 其 $x\cdot y$ 都是定值。有带**下取整**时，发现操作后的两数的积一定是要**小于等于**操作前两数的积的。这样，若是有 $a\cdot b<c\cdot d$ 则直接无解。

发现如果一直对 $(a,b)$ 操作十分困难，因为每次操作都涉及到两个数字，那么如果能只对一个数字操作呢？考虑变成 $(a\cdot b,1)$（只需要执行操作把右边的 $b$ 除到左边去），这样只需要将其转化为 $(c\cdot d,1)$ 即可。

再考虑到上文对操作数量的分析，可以得出结论：通过 $\log10^{18}$ 次操作将 $a\cdot b$ 变成 $c\cdot d$。

记 $s=a\cdot b,t=c\cdot d$。发现如果有 $t\le s<2t$，则可以直接 $(s,1)\to(1,t)$，只需除以 $t$ 即可。

那么如何每次将 $s$ 缩小一半呢？发现下取整的性质，如果有 $x>\frac{s}{2}$，则 $\lfloor\frac{s}{x}\rfloor=1$。那么我们想到每次将 $s$ 除以 $\lfloor\frac{s}{2}\rfloor+1$，就能保证其缩小一半了！这样直到 $t\le s<2t$ 再进行上文的操作即可。

需要注意的是每次操作会把 $(x,y)$ 的两项互换，所以还需记录 $s$ 的位置。同时当 $s=2$ 时上述的操作就无法进行了（样例一第二组）。

代码：
```cpp
int a,b,x,y;
il void work(){
	a=read(),b=read(),x=read(),y=read();
	int s=a*b,t=x*y;
	if(s<t){puts("-1");return;}
	vector<pii>op;
	op.eb(mp(2,b));
	int val=1,zero=2,c=0;
	while(s>=t*2){
		op.eb(mp(val,s/2+1));
		s=s/(s/2+1)*(s/2+1);
		swap(val,zero); 
		c++;
		if(c>=66){puts("-1");return;}
	}
	op.eb(mp(val,t));swap(val,zero);
	if(val==1)op.eb(mp(val,y));
	else op.eb(mp(val,x));
	
	printf("%lld\n",op.size());
	for(pii p:op){
		printf("%lld %lld\n",p.first,p.second);
	}
}
```

---

## 作者：naroto2022 (赞：3)

# P11603 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P11063)

### 思路

首先，看到题目想到一个性质：对于一个数 $x$，$x$ 除以一个比 $x\div2$ 大的数的结果一定为 $0$，再配合上题目给不能超过 $65$，自然地想到二进制拆分。

首先，先判断肯定有解的情况：$a=b=c=d$，显然输出 $0$ 即可，接着判断无解的情况，也很简单，当且仅当 $a\times b<c\times d$ 或 $c*d$ 时，因为你一次操作之后 $a\times b$ 的值只可能不断地减小（整除的那一部分余数乘以另一个数），而且最多减到 $2$（不信你手玩试试）。

接下来就开始解题，配合上前面想到的性质，很自然的想到，先用一次操作将 $b\gets a\times b$，然后不断地把 $b\gets b\div2+1$，直到 $b\div2+1\leq c\times d$，那么直接 $b\gets c\times d$，接下来直接将 $a\gets c,b\gets d$。（因为 $a=1,b=c\times d$）

对于一次赋值操作可以选择先将 $a\gets b\div2+1,b\gets1$，然后再 $a\gets1,b\gets b\div2+1$，但是这样答案会跑过 $65$，所以考虑这样转换会浪费一步，所以可以直接轮换着赋值，即 $a\gets b\div2+1,b\gets 1$，接着 $a\gets 1,b\gets a\div 2+1$，于是问题就解决了。

注意，这样要特判最后一步是赋值 $a$ 还是 $b$，别让两个顺序反了。

至于小于等于 $65$ 的正确性很好证明，首先一开始 $b\gets c\times d$，和最后得到答案的都是花费一步，而中间的步数最多为 $63$，因为 $a\times b\leq 10^{18},2^{63}>10^{18}$，加起来最多正正好是 $65$ 步！结束啦！！！

只能说这题出得很好！$65$ 竟然分配的这么准确！

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define pll pair<ll,ll>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
ll T,a,b,c,d,num,awa;
vector<pll> op;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void work(ll awa, ll n){op.pb(mp(awa,n));}
int main(){
    // freopen("1.in","r",stdin);
    T=read();while(T--){
        a=read();b=read();c=read();d=read();op.clear();
        if(a*b<c*d){
            write(-1);putchar('\n');
            continue;
        }
        if(a==c&&b==d){
            write(0);putchar('\n');
            continue;
        }
        if(c*d==1){
            write(-1);putchar('\n');
            continue;
        }
        op.pb(mp(1,a));b=a*b;num=c*d;awa=1;
        while(b!=num){
            if(awa==1) awa=2;else awa=1;
            if(b/2+1>num) work(awa,b/2+1),b=b/2+1;
            else work(awa,num),b=num;
        }
        if(awa==1) awa=2;else awa=1;
        if(awa==2) op.pb(mp(awa,c));
        else op.pb(mp(awa,d));
        write(op.size());putchar('\n');
        for(int i=0; i<op.size(); i++) write(op[i].fi),putchar(' '),write(op[i].se),putchar('\n'); 
    }
	return 0;
}
```

---

## 作者：naught (赞：2)

# 【MX-X4-T3】「Jason-1」数对变换

## 题外话

场上把贪心注重在一个奇怪地方了，导致交的时候已经有 $9$ 个人 $\textcolor{green}{AC}$ 了（哭）。

## 题意简述

对于数对 $(x,y)$，你可以执行以下两种变换：

- 类型 1：取 $1 \le k \le x$，令 $(x,y) \gets (\lfloor \frac{x}{k} \rfloor, y \cdot k)$。
- 类型 2：取 $1 \le k \le y$，令 $(x,y) \gets (x \cdot k, \lfloor \frac{y}{k} \rfloor)$。

显然，变换后的数对仍然是正整数数对。

给出两组正整数数对 $(a, b)$ 与 $(c, d)$，你需要执行**不超过 $\bm{65}$ 次**变换将 $(a, b)$ 变为 $(c, d)$，或者报告无解。**注意：你不需要最小化执行变换的次数**。

## Solution

不难发现，当 $\dfrac{a}{c}=\dfrac{d}{b}$ 即 $a \times b = c \times d$ 时，最多两步操作即可完成数对变换，我们称 $a \times b = c \times d$ 的状态为“最终态”。

手玩一些数据之后，显然操作 $1$ 和操作 $2$ 本质一样，同时操作 $1$ 与操作 $2$ 必然是交替进行（因为多次操作 $1$ 亦或是多次 $2$ 都可以并为一次操作）。

因为操作 $1$ 和操作 $2$ 本质无差别，故后文将以“操作”代替操作 $1$ 或操作 $2$，同时默认操作是类型 $1$。

> 推论：每次非进入最终态的操作必定化为使数对 $(a, b)$ 变成形如 $(x, 1)$ 的形式，且操作的 $k$ 值为 $a/2+1$ 或 $b/2+1$。

#### 证明

首先，若一次操作之后进入最终态，本轮操作就大部分解决了，所以我们要尽量进入最终态，也就是说 $a \times b$ 要尽量接近 $c \times d$。

思考一次操作能为我们带来多大的贡献。

假设对数对 $(a, b)$ 进行操作，取 $k$ 值为 $k$，设：

$$

a = p \times k + q (0 \le q < k)。

$$

则操作结束后数对 $(a, b)$ 将变成数对 $(p, b \times k)$，数对之积减少了 $b \times q$。

**$b$ 为定值，则要使 $q$ 尽量大**。

发现 $q$ 在 $k = a/2+1$ 取最大值，此时 $p$ 为 $1$。

证毕。

之后的思路就清晰起来了：每次对于数对 $(a, 1)$，若无法使其一次进入最终态（即 $a \ge (2 \times c \times d)$），就进行操作直到进入最终态。

其他疑问见代码。

## 代码

```cpp
// written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
// #define int long long
#define Maxn 105
#define p2(x) ((x)*(x))
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
// void train() {ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);}

struct ope
{
    int op;
    ll k;
}ans[Maxn];
ll cnt;

void print()
{
    printf("%lld\n", cnt);
    fo(i, 1, cnt) printf("%d %lld\n", ans[i].op, ans[i].k);
}

int main()
{
    int _ = read();
    while(_--)
    {
        ll x = lread(), y = lread(), c = lread(), d = lread(); cnt = 0;
        if(x == c && y == d) {puts("0");continue;}
        if(x * y < c*d ) {puts("-1");continue;}
        int tmp = 2;
        ans[++cnt] = {tmp, y}; x *= y, y = 1, tmp = 3-tmp;
        while(x*y >= 2*c*d && cnt <= 63)
        {
            ll k = x*y/2+1;
            ans[++cnt] = {tmp, k};
            if(tmp == 2) y /= k, x *= k;
            else x /= k, y *= k;
            tmp = 3-tmp;
        }
        if(cnt == 64 && x*y != c*d) {puts("-1"); continue;}
        ans[++cnt] = {tmp, c*d}; tmp = 3-tmp;
        ans[++cnt] = {tmp, tmp == 1? d: c};
        print();
    }
    return 0;
}

```

## Tips

$10^9 \times 10^9$ 会爆 `int`，记得开`long long`。

---

## 作者：2huk (赞：1)

我们用 $(a, b) \xrightarrow{t, k} (c, d)$ 表示将数对 $(a, b)$ 通过参数为 $k$ 的类型-$t$ 的操作变化成 $(c, d)$ 的过程。如 $(2, 2) \xrightarrow{1, 2} (1, 4)$。

显然一次变化 $(a, b) \xrightarrow{t, k} (a', b')$ 后乘积不会变大，即 $a'b' \le ab$。

所以如果题目给定的 $ab < cd$ 则无解。另一个无解的情况是 $ab\ne 1$ 且 $c = d = 1$，如样例 1。接下来我们将构造地证明除这些情况外都有解。

显然有两个东西：

- $(1, x) \xrightarrow{2, x} (x, 1)$ 以及 $(x, 1) \xrightarrow{1, x} (1, x)$。也就是说 $(1, x),(x,1)$ 可以轻易地相互转换。
- $(a, b) \xrightarrow{1,a} (1,ab)$ 以及 $(cd,1) \xrightarrow{1, k} (c, d)$。也就是说 $(a, b) \rightsquigarrow (c, d)$ 等价于：

$$
\begin{matrix}
&(a, b) \xrightarrow{1,a} (1,ab) \rightsquigarrow (cd,1) \xrightarrow{1, d} (c, d) \\
\text{或 }&(a, b) \xrightarrow{1,a} (1,ab) \rightsquigarrow (1, cd) \xrightarrow{2,c} (c, d)
\end{matrix}
$$

所以我们需要解决 $(1,ab) \rightsquigarrow (cd,1)$ 或 $(1,ab) \rightsquigarrow (1, cd)$。

分类讨论。

- 如果 $\lfloor\frac{ab}{cd}\rfloor = 1$ 那么一步 $(1,ab) \xrightarrow{2,cd} (cd,1)$ 即可。
- 你尝试把它的后一位设成 $1$ 且前一位尽量大。因为这样操作后得到的子问题更容易满足上一个条件。不难发现可以 $(1,ab) \xrightarrow{2, \lfloor \frac{ab}2 \rfloor+1} (\lfloor \frac{ab}2 \rfloor+1,1)$。

重复这样操作，直到情况一发生。不难发现因为你每次有个除以二的操作所以操作总次数是 $\log n$ 的，恰好在 $65$ 内。

代码：

```cpp
signed main() {
	int T;
	cin >> T;
	while (T -- ) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		
		if (a * b < c * d || c * d == 1 && a * b > 1) puts("-1");
		else {
			int pos = 1;
			vector<pair<int, int>> res;
			
			auto work = [&](int t, int k) {
				res.emplace_back(t, k);
				if (t == 1) {
					a /= k;
					b *= k;
				} else {
					a *= k;
					b /= k;
				}
			};
			
			work(1, a);
			while (max(a, b) != c * d) {
				int k = max(c * d, max(a, b) / 2 + 1);
				work(a == 1 ? 2 : 1, k);
			}
			work(a == 1 ? 2 : 1, a == 1 ? c : d);
			
			cout << res.size() << '\n';
			for (auto t : res) cout << t.first << ' ' << t.second << '\n';
		}
	}
	return 0;
}
```

---

## 作者：xujunlang2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11063)

## 思路

发现并没有要求最小次数，~~所以我们直接拍一个最大值上去。~~

然后进行一个小的分讨：

- $a\times b = c \times d$

  很显然两次操作解决：

  把 $(a,b) $ 变成 $ (1,a\times b)$ 然后再变成 $(c,\frac{a\times b}{c})$ 就行了。

- $a\times b < c \times d$

  不难发现在除完下取整之后乘积不会变大，直接无解。

- $a\times b > c \times d$

  这个比较麻烦。

  如果 $a\times b < c \times d \times 2$，很显然 $\left\lfloor\frac{a\times b}{c \times d}\right\rfloor=1$，直接解决。

  否则 我们可以把 $k$ 取到 $\left\lfloor\frac{a\times b}{2}\right\rfloor+1$，约等于将 $a\times b$ 除以 $2$，直到 $a\times b < c \times d \times 2$。

  还能发现，若 $k\le2$，那么 $k$ 就一直不会改变，此时无解。

接下来证明修改次数足够，$a\times b\le10^{18}$, 所以进行最多 $59$ 次操作。

还有一次操作使 $a\times b = c \times d$，最后两次操作解决，最多 $62$ 次。

剩下的次数直接用 $(1,1)$ 来浪费。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    for (int i = 1;i <= t;i++)
    {
        long long x, y, a, b;//这里赛时写的是 x, y, a, b 
        cin >> x >> y >> a >> b;
        if (x * y == a * b)
        {
            if (x < y)
            {
                cout << "2\n2 " << a / __gcd(x, a) << "\n1 " << x / __gcd(x, a) << "\n";
            }
            else
            {
                cout << "2\n1 " << b / __gcd(y, b) << "\n2 " << y / __gcd(y, b) << "\n";
            }
        }
        else if (x * y < a * b)
        {
            cout << "-1\n";
        }
        else
        {
            bool f = 1, F = 1;//f 表示 a * b 在 a 上还是在 b 上，F表示是否有解 
            long long x2 = x * y, ans = 65;//x2 判是否有解时的 a * b 
            while (x2 >= 2 * a * b)
            {
                if (x2 <= 2)
                {
                    cout << -1 << "\n";
                    F = 0;
                    break;
                }
                x2 = x2 / 2 + 1;
                f ^= 1;
            }//处理无解 
            if (F)
            {
                cout << "65\n1 " << x << "\n";
                ans--;
                f = 1;
                while (x * y >= 2 * a * b)
                {
                    if (f)
                    {
                        cout << "2 " << x * y / 2 + 1 << "\n";
                        x = x * y / 2 + 1;
                        y = 1;
                        f = 0;
                    }
                    else
                    {
                        cout << "1 " << x * y / 2 + 1 << "\n";
                        y = x * y / 2 + 1;
                        x = 1;
                        f = 1;
                    }
                    ans--;
                }//除以二直到 a * b < 2 * c * d
                if (f)
                {
                    cout << "2 " << a * b << "\n1 " << b << "\n";
                    ans -= 2;
                }
                else
                {
                    cout << "1 " << a * b << "\n2 " << a << "\n";
                    ans -= 2;
                }//和 a * b = c * d 的处理方法相似
                while (ans)
                {
                    ans--;
                    cout << "1 1\n";
                }//处理多余的操作次数 
            }
        }
    } 
    return 0;
}
```

---

## 作者：MicroSun (赞：1)

好玩题。

## 特殊性质 A

这档部分分保证了 $\frac{a}{c}=\frac{d}{b}$，两边同时乘以 $bc$ 得到 $ab=cd$。

我们可以先进行一次操作，将 $a$ 和 $b$ 乘到一起，再用一次操作将其分开成 $c$ 和 $d$ 即可。`1 a 2 c` 是一种合法构造。

## 正解

既然我们已经知道 $a\times b=c\times d$ 时的解法，那么我们考虑通过一系列操作使 $a\times b=c\times d$。

发现除法是向下取整，也就是在一系列操作后 $a\times b$ 不可能变得更大。因此，如果 $a\times b<c\times d$ 则无解。需要注意的是 $a\times b \ne 1$ 且 $c\times d=1$ 也是一种无解情况，可以手玩几组数据验证其正确性。

与特殊性质 A 一样，我们先将 $a$ 和 $b$ 转换到一起，设 $a\times b=x$，下面我们观察一次操作对 $x$ 的值的影响：

- 显然对值为 $1$ 的元素进行操作是无意义的。
- 对 $x$ 进行操作，则 $x$ 变为 $p\times\lfloor\frac{x}{p}\rfloor=x-(x\bmod p)$。

因为操作次数的上限为 $65$，而 $\log_2(\max(a\times b))$ 约为 $60$，所以我们容易想到折半操作。

每次令 $k=\lfloor\frac{x}{2}\rfloor+1$，进行一次操作后 $x$ 会大约缩小一半。

那么我们就可以重复用 $k$ 来操作，直到 $x$ 可以表示为 $c\times d+m(m<c\times d)$，此时用 $c\times d$ 来进行操作就可以使 $x\leftarrow c\times d$，再用一次操作拆分即可。

实现细节方面，观察到每次整除的结果都为 $1$，所以轮流使用两个数即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=2e5+10;

ll a[N];
void solve(){
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a*b<c*d||(c*d==1&&a*b!=1)){
		cout<<"-1\n";
		return;
	}
	if(a==c&&b==d){
		cout<<"0\n";
		return;
	}
	vector<pll> ve;
	ll tmp=a*b;
	ve.pb({2,b});
	bool pos=0;
	while(tmp!=c*d){
		ll t=max(tmp/2+1,c*d);
		ve.pb({pos+1,t});
		tmp=tmp/t*t;
		pos^=1;
	}
	if(pos==0) ve.pb({pos+1,d});
	else ve.pb({pos+1,c});
	cout<<ve.size()<<endl;
	for(auto [a,b]:ve) cout<<a<<' '<<b<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：Crosser (赞：0)

这还 Ad-hoc 吗，我觉得完全不。

$\text{*1700, maths, number theory.}$

## Solution

首先一个乘一个除显然想到观察**乘积**，注意到在操作过程中乘积是**单调不增**的，因此 $ab<cd$ 直接无解。同时我们可以在任何时刻把两个数变成 $(1,ab)$，也可以任意地把 $(1,ab)$ 分解。因此可行。

我们发现对于 $\lfloor\frac{ab}{cd}\rfloor=1$，我们可以通过 $(ab, 1)\to (1,cd)$ 完成任务，因此我们的目标再次转化：**把 $\bm {ab}$ 变得和 $\bm {cd}$ 尽量接近。**

**考虑怎么除最快**：类似于一个数取模过后最大为其一半的性质，我们发现：做完一次操作之后两个数乘积的变化最小可以缩减为其一半，具体地：$n'\ge\lfloor\frac n2\rfloor+1$。因为只要使得 $ab$ 在 $cd$ 的两倍之内，所以我们尽力除就行了，不难发现一定会有一个 $ab$ 落在 $cd$ 的一倍到两倍之内。

**考虑实现**：每次把 $1$ 变成 $\lfloor\frac n2\rfloor+1$，把 $n$ 变成 $1$，以此交替。发现有的 Corner Case 会陷入死循环，不难特判。特判发现 $cd>1$，因此操作次数小于等于 $3+\log \frac{ab}2$。

## Implementation

```cpp
int solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int A = a * b, B = c * d;
    if(A < B) return puts("-1");
    if(A == B) {
        cout << 2 << endl;
        cout << "1 " << a << endl;
        cout << "2 " << c << endl;
        return 0;
    }
    if(B == 1) return puts("-1");
    vector<pair<int, int> > opt;
    int L = 1;
    if(a != 1) opt.emplace_back(1, a);
    while(A / 2 + 1 > B) {
        int now = A / 2 + 1;
        if(A == now) {
            return puts("-1");
        }
        L = 3 - L;
        if(now != 1) opt.emplace_back(L, now);
        A = now;
    }
    if(B != 1) opt.emplace_back(3 - L, B);
    if((L == 1 ? d : c) != 1) opt.emplace_back(L, L == 1 ? d : c);
    cout << opt.size() << endl;
    for(auto x : opt) cout << x.first << ' ' << x.second << endl;
    return 0;
}
```

有点冗长。

---

