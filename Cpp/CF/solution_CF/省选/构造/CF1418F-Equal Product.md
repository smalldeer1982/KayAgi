# Equal Product

## 题目描述

You are given four integers $ n $ , $ m $ , $ l $ and $ r $ .

Let's name a tuple $ (x_1, y_1, x_2, y_2) $ as good if:

1. $ 1 \le x_1 < x_2 \le n $ ;
2. $ 1 \le y_2 < y_1 \le m $ ;
3. $ x_1 \cdot y_1 = x_2 \cdot y_2 $ ;
4. $ l \le x_1 \cdot y_1 \le r $ .

Find any good tuple for each $ x_1 $ from $ 1 $ to $ n $ inclusive.

## 样例 #1

### 输入

```
8 20
91 100```

### 输出

```
-1
-1
-1
-1
-1
6 16 8 12
-1
-1```

## 样例 #2

### 输入

```
4 5
1 10```

### 输出

```
1 2 2 1
2 3 3 2
-1
-1```

## 样例 #3

### 输入

```
5 12
16 60```

### 输出

```
-1
2 9 3 6
3 8 4 6
4 5 5 4
-1```

# 题解

## 作者：RainAir (赞：11)

[更好的阅读体验](https://blog.aor.sd.cn/archives/1416/)

发现一个结论：对于任何一对 $x_1y_1 = x_2y_2(x_1 < x_2)$，都存在一对正整数 $a < b$，满足 $x_2 = \frac{x_1}{a}b,y_2 = \frac{y_1}{b}a$。

证明：设 $g=\gcd(x_1,x_2)$，我们构造 $a=\frac{x_1}{g},b = \frac{x_2}{g}$，不难发现 $\frac{x_1}{a}b = x_2$，接下来只需要证明 $b|y_1$即可。注意到 $b=\frac{x_2}{g} | \frac{x_2y_2}{g} = \frac{x_1y_1}{g}$，又因为有 $(b,\frac{x_1}{g}) = 1$，所以得到 $b|y_1$。


因为 $a|x_1,b|y_1$，所以有效的 $(a,x_1)$ 只有 $O(n \log n)$ 对。

现在我们去固定 $x_1$，考虑 $y_1$ 的种种限制：首先要保证 $y_1 \leq m$，其次还要保证 $\lceil \frac{L}{x_1}\rceil  \leq y_1 \leq \lfloor \frac{R}{x_1} \rfloor$。

我们考虑枚举一对 $(a,x_1)$，现在相当于要求快速询问是否存在一对 $(b,y_1)$ 满足如下条件：
$$
\begin{aligned}
y_1 \leq m\\
\lceil \frac{L}{x_1}\rceil  \leq y_1 \leq \lfloor \frac{R}{x_1} \rfloor\\
\frac{x_1}{a}b \leq n\\
a < b
\end{aligned}
$$
显然我们会贪心选择能选择的 $b$ 中最小的去判断第三个限制是否成立。

第一个和第二个限制可以通过从小到大枚举 $x$ 双指针解决，第四个限制可以维护当前所有可选值的 set 解决，复杂度 $O(n \log^2 n)$。

```cpp
#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
std::vector<int> G[MAXN];

inline void prework(){
	FOR(i,1,200000) for(int j = i;j <= 200000;j += i) G[j].pb(i);
}

LL L,R;
int n,m;
std::set<P> S;

int main(){
	prework();
	scanf("%d%d%lld%lld",&n,&m,&L,&R);
	int nowl=m+1,nowr=m;
	FOR(x,1,n){
		LL l=L/x,r=R/x;
		if(1ll*x*l < L) ++l;
		r = std::min(r,(LL)m);
		if(l > r){
			puts("-1");
			continue;
		}
		while(l < nowl){
			nowl--;
			for(auto x:G[nowl]) S.insert(MP(x,nowl));
		}
		while(nowr > r){
			for(auto x:G[nowr]) S.erase(MP(x,nowr));
			nowr--;
		}
		bool flag = 0;
		for(auto a:G[x]){
			auto it = S.upper_bound(MP(a,1e9));
			if(it == S.end()) break;
			int b = it->fi,y = it->se;
			if(1ll*(x/a)*b <= n){
				flag = 1;
				printf("%d %d %d %d\n",x,y,x/a*b,y/b*a);
				break;
			}
		}
		if(!flag){
			puts("-1");
		}
	}
	return 0;
}
```

---

## 作者：zfy2006 (赞：4)

本题初看好像两对 $(x,y)$ 中除了乘积相等之外好像并无其他联系，那么如果枚举乘积的话复杂度将在 $n^3$ 左右，是我们无法接受的，那我们接下来考虑构造，将其联系起来。

首先我们构造两个数 $a$ 和 $b$ ，$a<b$ ,那么一定存在这一对数使得 $x_2=\frac{x_1}{a}b $ ， $y_2=\frac{y_1}{b}a$ 并且 $b\mid y_1$ , $a \mid x_1$ 。那么如何证明呢，令 $a=\frac{x_1}{g}$ ，$b= \frac{x_2}{g}$ ，那么由定义可得 $a \mid x_1$ 成立。因为由定义可得 $b \mid \frac{x_2y_2}{g}$ 且 $x_1y_1=x_2y_2$ ，故 $b \mid \frac{x_1y_1}{g}$ ，又因为 $b$ 与 $\frac{x_1}{g}$ 互质，则有 $b \mid y_1$  成立。

于是接下来我们只需考虑数对 $(a,x_1)$ 即可，它只有 $n\log n$ 对合法数对，即对于每一个 $x_1$ 我们只需要考虑它的约数（注意要先枚举约数进行预处理否则复杂度就假了，会变成根号)。

然后我们再来看数对 $(b,y_1)$ ，该数对的限制有四个：

1.  $a < b$
2.  $\left\lceil\frac{L}{x_1}\right\rceil\le y_1\le\left\lfloor\frac{R}{x_1}\right\rfloor$
3.  $y_1\le m$
4.  $\frac{x_1}{a}b\le n$

首先为了满足限制一和四，我们只需贪心的选出大于 $a$ 的最小的 $b$ 即可。其次，我们发现随着 $x_1$ 的增大， $y_1$ 的范围是一直缩小不扩大的，我们可以用双指针加 $set$ 维护 $y_1$ 合法的区间，对于每个 $a$ 直接查询其后继即可。这里需要注意一下，如果你往 $set$ 里装的是数对的话会被最后一个点卡掉，因为我们只需要一个合法解，而对于一个相同的 $b$ 会有多个相对应的 $y_1$ ，导致同一个 $b$ 会出入多边，但其实我们只需要用 $set$ 维护一下合法的 $b$ ，用它在 $y_1$  的合法范围内算出一个合法解就行（这里我觉得用到了一点点莫队的思想），复杂度 $O(n \log^2n)$ 。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,L,R;
vector<int>g[N];
set<int>s;
int num[N];
inline void pre(){
    for(register int i=1;i<=200000;i++){
        for(register int j=i;j<=200000;j+=i){
            g[j].push_back(i);
        }
    }
}
signed main(){
    pre();
    scanf("%lld%lld%lld%lld",&n,&m,&L,&R);
    int nl=m+1,nr=m;
    for(register int x=1;x<=n;x++){
        int l=(L+x-1)/x,r=R/x;
        r=min(r,m);
        if(l>r){
            puts("-1");
            continue;
        }
        while(nl>l){
            nl--;
            for(auto v:g[nl]){
                if(!num[v])s.insert(v);
                num[v]++;
            }
        }
        while(nr>r){
            for(auto v:g[nr]){
                --num[v];
                if(!num[v])s.erase(v);
            }
            nr--;
        }
        bool f=1;
        for(auto a:g[x]){
            auto t=s.upper_bound(a);
            if(t==s.end())break;
            int b=*t;
            if(x/a*b>n)continue;
            int y=r/b*b;
            printf("%lld %lld %lld %lld\n",x,y,x/a*b,y/b*a);
            f=0;
            break;
        }
        if(f){
            puts("-1");
        }
    }
    return 0;
}
```



---

