# Boboniu and Bit Operations

## 题目描述

Boboniu likes bit operations. He wants to play a game with you.

Boboniu gives you two sequences of non-negative integers $ a_1,a_2,\ldots,a_n $ and $ b_1,b_2,\ldots,b_m $ .

For each $ i $ ( $ 1\le i\le n $ ), you're asked to choose a $ j $ ( $ 1\le j\le m $ ) and let $ c_i=a_i\& b_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). Note that you can pick the same $ j $ for different $ i $ 's.

Find the minimum possible $ c_1 | c_2 | \ldots | c_n $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

## 说明/提示

For the first example, we have $ c_1=a_1\& b_2=0 $ , $ c_2=a_2\& b_1=2 $ , $ c_3=a_3\& b_1=0 $ , $ c_4 =       a_4\& b_1=0 $ .Thus $ c_1 | c_2 | c_3 |c_4 =2 $ , and this is the minimal answer we can get.

## 样例 #1

### 输入

```
4 2
2 6 4 0
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4```

### 输出

```
0```

## 样例 #3

### 输入

```
8 5
179 261 432 162 82 43 10 38
379 357 202 184 197```

### 输出

```
147```

# 题解

## 作者：KellyFrog (赞：6)

这次好像 $A$ 偏难，$BCD$ 都很简单。

令 $f(i,x)=0/1$ 表示是否存在一组 $c$，满足 $c_1\operatorname{or}c_2\operatorname{or}...\operatorname{or}c_i=x$。

首先显然有 $f(0,0)=1$，答案为 $\min\{i|f(n,i)=1\}$.

接下来考虑转移：$f(i,x\operatorname{or}(a_i\operatorname{and}b_j))$ 显然可以从 $f(i-1,x)$ 转移过来，由于可能有很多 $x\operatorname{or}(a_i\operatorname{and}b_j)$ 相等，所以我们再转移的时候取个或就行了。

复杂度$O(2^9\cdot nm)$

```cpp
#include <iostream>

using namespace std;

const int MAXN = 205;
const int MAXM = 205;
const int MAXA = (1 << 9) + 5;

int a[MAXN], b[MAXM];
bool f[MAXN][MAXA];

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	f[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int x = a[i] & b[j];
			for(int k = 0; k < (1 << 9); k++) {
				f[i][k | x] |= f[i - 1][k];
			}
		}
	}
	for(int i = 0; i < (1 << 9); i++) {
		if(f[n][i]) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：5G信号塔报装 (赞：4)

## 题意

首先，洛谷的题目翻译有误，详见 -> [讨论版-这题的翻译有误](https://www.luogu.com.cn/discuss/show/250341)

有两个非负整数序列 $a_1, a_2, ..., a_n$，$b_1, b_2, ..., b_m$。

对于每个 $i\ (1\leq i\leq n)$，有 $j\ (1\leq j \leq m)$，使得 $c_i = a_i\ \&\ b_j$。求出 $c_1|c_2|...|c_n$ 的最小值。

## 思路

观察数据可发现：$n,m$ 范围极小，最大仅 $2\times10^2$。

考虑 **暴力枚举答案**，对于每一个答案 $x$，我们 check(验证) $x$ 的可用性。

如何验证？题目告诉我们 $x = min(c)$ 且 $c_i = a_i\ \&\ b_j$。那么我们只需要 check 

$$a_i\ \&\ b_j \  \text{or}\ x = x$$ 

即可。（满足 $c_i$ 不超过 $x$）

## Code

**Think Twice, Code Once.**

```cpp

# include <bits/stdc++.h>
using namespace std;

int n, m, a[100005], b[100005];

bool ojbk(int x) { //check
	for (int i = 1; i <= n; i++) {
		bool flg= false;
		for (int j = 1; j <= m; j++)
			if (((a[i] & b[j]) | x) == x) {
				flg = true; break; 
			}
		if (!flg) return false;
	}
	return true;
}

signed main() {
	puts("5G 赋能未来 | by 5G信号塔报装(三网线路检修员)");
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]); 
	for (int i = 0; i <= 512; i++)
		if (ojbk(i)) { cout << i << endl; break; }
	return 0;
}

// 【调试记录】 
// 1. 过度压行导致不明错误！【第7行，写 for(int i =1,flg = 0; )...】 
```

---

## 作者：Theophania (赞：2)

首先，如果这个最小值是 $ans$，那么一定存在 $i$，$j$ 使得 $a_i \& b_j | ans=ans$。观察一下数据范围可以发现 $ans$ 一定在区间 $\lbrack 0,512)$ 内，因此直接 $O(nm)$ 暴力枚举就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}

int a[201], b[201];
signed main()
{
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
        read(b[i]);
    bool flag;
    int cnt;
    for (int ans = 0; ans < 512; ++ans)
    {
        cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            flag = false;
            for (int j = 1; j <= m; ++j)
                if ((a[i] & b[j] | ans) == ans)
                {
                    flag = true;
                    break;
                }
            if (flag)
                cnt++;
            else
                break;
        }
        if (cnt == n)
        {
            cout << ans << endl;
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1395C)

## 题意

- 给定两个数序列 $a$ $b$ ，元素数分别为 $n$ $m$。

- 令 $c_i=a_i \& b_j$（ $j$ 可任取，重复取也可），求 $min(c_1|c_2|...|c_n)$。

## Sol

~~为啥他们复杂度比窝大跑得比窝快啊。/kk~~

我们从答案入手。

对于答案从大到小的二进制位，我们希望它尽可能为 $0$。

我们即可贪心。

用 $v_{i,j}$ 记录当前对于 $a_i$ 还能否使用 $b_j$。

对于每一位，我们先枚举每个 $a_i$，枚举余剩可用的 $b_j$，查看是否有 $a_i \& b_j$ 在这个二进制位上为 $0$。

若无，则答案这一位上必为 $1$，更新答案。

若有，答案这一位上一定可取 $0$，更新 $v_{i,j}$

我们更新时将 当前位上 $a_i \& b_j$ 为 $1$ 的 $v_{i,j}$ 转换状态。

这样贪心到最后一位即可qwq。

时间复杂度 $O(nm\log_2v)$ （$v$ 指 $a$ $b$ 中数的值域）

~~为啥他们 $O(nmv)$ 的跑得比我快啊/kk~~

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=205;
ll n,m,a[N],b[N],ans,v[N][N];
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);
	for(ll i=1;i<=n;i++) rd(a[i]);
	for(ll i=1;i<=m;i++) rd(b[i]);
	for(ll s=8;s>=0;s--){
		ll qaq=1;
		for(ll i=1;i<=n;i++){
			ll ok=0;
			for(ll j=1;j<=m;j++)
				if(v[i][j]==0&&(a[i]&b[j]&(1<<s))==0) ok=1;
			if(ok==0){
				qaq=0;
				break;
			}
		}
		if(qaq==0){
			ans+=(1<<s);
			continue;
		}
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				if((a[i]&b[j]&(1<<s))!=0) v[i][j]=1;
	}
	wr(ans);puts("");
	return 0;
}
```

---

## 作者：10circle (赞：1)

#### 题意

给你两个序列 $a,b$，长度分别为 $n,m$。对于每一个 $i\ (\ 1 \le i \le n\ )$，都要找到一个 $j\ (\ 1 \le j \le m\ )$，使 $ c_i=a_i\&b_j $，$\&$ 指按位与运算。要你求出 $c_1|c_2|...|c_n$ 的最小值是几。

#### 分析

先写个暴搜，再去优化。

```cpp
void dfs(int i,int c){
	if(i>n){
		ans=min(ans,c);
		return;
	}
	for(int j=1;j<=m;j++){
		dfs(i+1,c|(a[i]&b[j]));
	}
}
```

然后我们可以看出来，对于 $i$ 和 $c$ 都相同时，最后的答案也是一样的。所以就可以加一个 $vis$ 数组来表示这个有没有来过，可以提升效率。而每回 $c$ 的最大的二进制位一定小于等于 $a,b$ 序列中最大的二进制位的，所以空间时间都承受的住。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[205],b[205];
int ans=2100000000,n,m;
bool vis[205][514];
void dfs(int i,int c){
	if(vis[i][c])return;
	vis[i][c]=1;
	if(i>n){
		ans=min(ans,c);
		return;
	}
	for(int j=1;j<=m;j++){
		dfs(i+1,c|(a[i]&b[j]));
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：_YyD_ (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1395C)

**思路：**

答案的范围是 $0\sim512$ 的，所以只需要枚举答案再判断：

$$a_i \& b_j\mid ans=ans$$

是否成立就好了。

时间复杂度是：$O(513\times N\times M)$。

**Code:**

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
long long n,m,a[300],b[300];
bool flag;
int main() {
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	rep(i,1,m) cin>>b[i];
	rep(ans,0,512) {
		rep(i,1,n) {
			flag=false;
			rep(j,1,m) {
				if(((a[i]&b[j])|ans)==ans) {
					flag=true;
					break;
				}
			}
			if(!flag)goto nmml; 
		}
		return cout<<ans,0;
		nmml:;
	}
	return 0;
}
```


---

## 作者：绝顶我为峰 (赞：0)

由于 $n,m\leq200$，几乎允许我们做想做的任何事。所以我们可以直接暴力把每一个  $a_i\&b_j$ 求出来。

由于高位选 $0$ 一定比低位选 $0$ 更优，考虑贪心。

或运算的性质是所有参与运算的数的二进制当前位中全部是 $0$ 则答案是 $0$，否则答案是 $1$。

那么我们对于每一位，遍历数组 $a$，对于每个 $a_i$ 查找是否有一个 $a_i\&b_j$ 的当前位是 $0$，如果没有，则当前位只能为 $1$，计算贡献。

如果每一个 $i$ 当前位都可以是 $0$，根据贪心思想，当前位必是 $0$，这个时候不需要计算贡献，而是重新遍历所有的 $a_i\&b_j$，把当前位是 $1$ 的答案删去即可。

代码很显然了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[201],b[201],num[201][201],ans,maxn;
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        maxn=max(maxn,a[i]);
    }
    for(register int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
        maxn=max(maxn,b[i]);
        for(register int j=1;j<=n;++j)
            num[j][i]=a[j]&b[i];
    }
    for(register int i=10;i>=0;--i)
    {
        if((1<<i)>maxn)
            continue;
        bool flag=1;
        for(register int j=1;j<=n;++j)
        {
            bool tag=0;
            for(register int k=1;k<=m;++k)
                if(num[j][k]!=-1&&!((num[j][k]>>i)&1))
                {
                    tag=1;
                    break;
                }
            if(!tag)
            {
                flag=0;
                break;
            }
        }
        if(!flag)
            ans+=1<<i;
        else
            for(register int j=1;j<=n;++j)
                for(register int k=1;k<=m;++k)
                    if((num[j][k]>>i)&1)
                        num[j][k]=-1;
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：引领天下 (赞：0)

考虑拆位。

对最后的答案，从高位到低位一次贪心，即：

对于第 $i$ 位，它能是 $0$ 就让它是 $0$ ，只有万不得已的时候才让它是 $1$ 。

于是我们枚举每一位，暴力判断是否可行即可。但是需要注意当前的方案不能与之前的有冲突，否则需要牺牲当前位的答案，因为让更高的位取 $0$ 更优。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int main(){
    register int n,m,a[205],b[205],c=0,u[205][205];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)scanf("%d",&b[i]);
    for(int i=9;i>=0;i--){
        bool l=0;
        for(int j=1;j<=n;j++){
            bool ok=1;
            for(int k=1;k<=m&&ok;k++)if(!u[j][k]&&!((a[j]&b[k])&(1<<i)))ok=0;//判断能否找到可行的方案
            l|=ok;
        }
        if(l)c+=l<<i;
        else for(int j=1;j<=n;j++)
        for(int k=1;k<=m;k++)if((a[j]&b[k]&(1<<i)))u[j][k]=1;//标记：这两个数已经固定，后续不能拆散
    }
    printf("%d",c);
    return 0;
}
```

---

