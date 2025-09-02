# Number Table

## 题目描述

As it has been found out recently, all the Berland's current economical state can be described using a simple table $ n×m $ in size. $ n $ — the number of days in each Berland month, $ m $ — the number of months. Thus, a table cell corresponds to a day and a month of the Berland's year. Each cell will contain either 1, or -1, which means the state's gains in a particular month, on a particular day. 1 corresponds to profits, -1 corresponds to losses. It turned out important for successful development to analyze the data on the state of the economy of the previous year, however when the treasurers referred to the archives to retrieve the data, it turned out that the table had been substantially damaged. In some table cells the number values had faded and were impossible to be deciphered. It is known that the number of cells in which the data had been preserved is strictly less than $ max(n,m) $ . However, there is additional information — the product of the numbers in each line and column equaled -1. Your task is to find out how many different tables may conform to the preserved data. As the answer to the task can be quite large, you have to find it modulo $ p $ .

## 样例 #1

### 输入

```
2 2
0
100
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2
1
1 1 -1
100
```

### 输出

```
1
```

# 题解

## 作者：是个汉子 (赞：13)

[原题](https://www.luogu.com.cn/problem/CF40E)

### Solution

这是个计数题。

~~我直接正难则反~~

我们观察题面，发现一个很重要的条件 $k< \max\{n,m\}$ ，我们这里设 $n>m$ ，那么也就是如果填入的每个数都不同行，也会有一行是空出来什么都没有的。

~~我艸，妙啊~~

继续想，这一行是空的，别的行需要满足乘积为 $-1$ 。

列是不需要考虑的，因为别的列可以通过这个**空着的列**满足乘积为 $-1$ 。而这空着的这一行也因为别的都是 $-1$ ，它自己也得是 $-1$ 。

此时每行乘起来为 $(-1)^n$ ，每列为 $(-1)^m$ ，如果 $n,m$ 奇偶性不一样，直接判无解。

~~就这？~~

因为要满足每一行乘积为 $-1$ ，所以将每一行分开考虑：

1. 这一行还没填满，那么除了某一个位置，剩下的位置随便填，最后剩的位置用来使这一行乘积为 $-1$ ，则答案为 $2^{m-cnt-1}$ ，其中 $cnt$ 为这一行填着的位置数。
2. 这一行是填满的，如果乘积为 $1$ ，判无解。否则跳过。

这个时间复杂度是 $O(n)$ 的。

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1005;
int n,m,k,p,pow2[N],cnt[N],mul[N],ans=1;
bool is_change;

int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(n<m) swap(n,m),is_change=true;
    for(int i=1;i<=n;i++) mul[i]=1;
    for(int i=1,x,y,v;i<=k;i++){
        scanf("%d%d%d",&x,&y,&v);
        if(is_change) swap(x,y);
        cnt[x]++,mul[x]*=v;
    }
    scanf("%d",&p);
    if((n&1)!=(m&1)){
        puts("0");
        return 0;
    }
    pow2[0]=1;
    for(int i=1;i<=n;i++)
        pow2[i]=(pow2[i-1]*2)%p;
    for(int i=1;i<n;i++)
        if(!cnt[i]){
            swap(cnt[i],cnt[n]);
            swap(mul[i],mul[n]);
            break;
        }
    for(int i=1;i<n&&ans;i++){
        if(cnt[i]==m){
            if(mul[i]==1) ans=0;
        }
        else ans=ans*1ll*pow2[m-cnt[i]-1]%p;
    }
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：xixike (赞：5)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15496844.html)

# Description

> [洛谷传送门](https://www.luogu.com.cn/problem/CF40E)

## 输入格式

第 1 行两个整数 $n$，$m$，表示一个 $n \times m$ 的矩阵。

第 2 行一个整数 $k$，表示有 $k$ 个点已经被填上数。

第 $3$ ~ $k + 2$ 行，每行 3 个整数 $a$，$b$，$c$，表示矩阵$M_{a,b} = c$。

第 $k + 3$ 行，1 个整数 $p$，表示模数。

## 输出格式

一个整数，表示方案数。

# Solution

我们首先考虑填一个空的矩阵有多少种方案数。

对于 $1$ ~ $n - 1$ 行，我们先把最后一个数单独取出来一个数，剩下前 $m - 1$ 个数随便填，最后一个数可以让这一行的乘积变成  $-1$。

同理，不管前 $n - 1$ 行怎么填，最后一行总能让每一列的乘积变为 $-1$。

所以总方案数就是：

$$ans = 2^{(n - 1)(m - 1)}$$

下面我们来考虑一下这道题。

首先可以判一波无解，先把结论放在这里：$n$，$m$ 奇偶性不同时，无解。

证明：

> 每一行，每一列乘积都为 $-1$，我们可以把这些 $-1$ 乘在一起，即$(-1)^{n + m}$，再考虑一下这些数乘起来的本质是什么，是不是矩阵中每一个点的平方的乘积呢？是的。也就是说，乘积必为正数，就是 $1$。当 $n$，$m$ 奇偶数性不同时，乘积是 $-1$，矛盾。

证毕.

我们继续来分析，观察到最后一句话：$0 \leq k < max(n, m)$

这有什么用呢？

我们假设 $n > m$，上面的条件就变为了 $k < n$，也就是说，不论你怎么填，必定有一行是空的（一个数都没有）。

我们发现，这样就有上面简化版题目的性质了，即，我们可以不考虑列了。

这时我们也可以套用上面的解法了，$O(n)$ 枚举每一行，$ans = ans \times 2^{m - cnt_i - 1}$，$cnt_i$ 是第 $i$ 行 $1$ 的个数，减去 1 是因为要空出来一个数来使这一行的乘积为 $-1$。

注意：这里也要判一下无解，当有一行全部被填满且乘积为 $1$ 时，无解（显然）。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;
int n, m, k, mod, flag;
int x[N], y[N], z[N];
int line[N], mul[N], fac[N];

int main(){
    scanf("%d%d%d", &n, &m, &k);
    if((n + m) & 1){
        puts("0");
        return 0;
    }
    if(n < m) swap(n, m), flag = 1;
    for(int i = 1; i <= n; ++i) mul[i] = 1;
    for(int i = 1, x, y, z; i <= k; ++i){
        scanf("%d%d%d", &x, &y, &z);
        if(flag) swap(x, y);
        line[x]++, mul[x] *= z;
    }
    scanf("%d", &mod);
    fac[0] = 1;
    for(int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * 2 % mod;
    int ans = 1;
    for(int i = 1; i < n; ++i)
        if(!line[i]){
            swap(line[i], line[n]), swap(mul[i], mul[n]);
            break;
        }
    for(int i = 1; i < n && ans; ++i){
        if(line[i] == m && mul[i] == 1) ans = 0;
        if(line[i] < m) ans = ans * (long long)fac[m - line[i] - 1] % mod;
    }
    printf("%d\n", ans);
    return 0;
}
```

# End

---

## 作者：jianhe (赞：4)

切了个 *2500，写篇题解纪念一下。

由于每行乘积的绝对值永远为 $1$，可以只考虑符号。

那么简要题意为：对一个位置填入数，可以选择改变符号或不改变，使得每行每列乘积都为负。

先只考虑行。

容易想到，每行最后一次填入时，可以将乘积调整为负。所以，前面填正或负并不重要。除最后一个位置外，每个位置都有两种选择。记每行未填入的个数为 $x$，则这行的方案数为 $2^{x-1}$ 种。

再加上列，似乎有点复杂。

但题目中给了 $k<\max(n,m)$。不妨假设 $n>m$。

则至少会有一个空行，即每列至少有一个空格。

即不需要考虑列。

特判一下无解的情况即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e3+10;
ll n,m,k,x,y,z,p,d,ans=1,a[N],b[N],e[N];
bool flag;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	if((n&1)!=(m&1)){cout<<"0";return 0;}
	if(n<m) n^=m^=n^=m,flag=1;
	for(int i=1;i<=n;i++) a[i]=1;
	for(int i=1;i<=k;i++){
		cin>>x>>y>>z;
		if(flag) x^=y^=x^=y;
		a[x]*=z,b[x]++;
	}
	cin>>p;e[0]=1;
	for(int i=1;i<=n;i++) e[i]=e[i-1]*2%p;
	for(int i=1;i<=n;i++){
		if(!b[i]&&!d){d++;continue;}
		if(b[i]==m&&a[i]==1){ans=0;break;}
		if(b[i]<m) ans=ans*e[m-b[i]-1]%p;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：2)

为了方便起见，当 $n<m$ 时我们交换 $n,m$。这显然不影响正确性。

首先显然的，$n,m$ 不同奇偶时，无解。

注意到 $k<\max\{n,m\}$，那么一定有一行是空的。我们可以通过这空的一行让所有列满足条件。

考虑行。假设第 $i$ 行已经有了 $d_i$ 个，那么还剩下 $m-d_i$ 个位置可以填，我们得留下一个来控制乘积是 $-1$，因此可以填的位置有 $m-d_i-1$ 个，那么这一行的方案数就是 $2^{m-d_i-1}$ 种。

如果一行已经填满了，但是积是 $1$，那就无解，因为你改不了了。

代码大概就是统计一下第 $i$ 行目前的积和已经填入的数的个数，然后预处理一下 $2$ 的幂，直接按照上面的思路计算就行。

---

## 作者：WNico (赞：1)

> 考了相同的题并且数据范围还更大于是来水一发题解
>
> 做到的那道题数据有点弱（然而数据范围大），但是（我觉得）cf的题应该也需要注意这些地方

# 解法

> oi只需要感性证明

显然，n,m 奇偶性不同时，答案为0

加个特判

> 我也只是套了几张图知道的

> 然而这和后面并没有什么关系

可以发现有一个十分奇怪的条件

`k严格小于n和m的最大值`

从它来考虑，会发现必然有一行上没有填上一个数

> 这也没有什么关系

忘了上面那些让你感到奇奇怪怪的东西，我们先来单独考虑一行

对于一行（假设m=0）的情况

假设其中有 t 个空位

可以发现，对于这一行来说，可以填的情况有 $2^{t-1}$ 种

因为将这 t 个空位中 t-1 个随便填掉之后，为了保证积为-1的性质，最后一个空位必然有且仅有一种可以填的情况

所以我们可以保证每一行的乘积为-1

> 所以列呢

回到之前的奇怪条件

必然有一行是空的

那就拿出空的这一行来维护每一列的性质

至于这一行为什么乘积一定会是 -1

我也不知道

> 感性证明感性证明

希望有dalao可以来证明这个和最上面那个性质

> 但是n不一定大于m

简单，交换一下n,m ,输入的时候交换 a,b就行了

于是可以用桶来计数

然而我考试的时候是排序来做的，反正意思一样

```cpp
#include<bits/stdc++.h>		// 考试时的代码稍微订正+hack
#define ll long long		// 这个没有交换n,m 写法诡异 看看就好
using namespace std;

inline ll read(){
	ll s=0,w=1;char ch;
	while(ch=getchar(),!isdigit(ch)) if(ch=='-') w=-1;
	while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
	return s*w;	
}

const int N = 1000009;
ll n,m,p,k,ans;
struct node{
	int x,y,z;
}fid[N];

inline ll fpow(ll x,ll q){
	ll ret=1;
	while(q>0){
		if(q&1) ret=ret*x%p;
		x=x*x%p;
		q>>=1;
	}
	return ret;
}

inline ll pow2(ll q){
	ll ret=1;
	while(q){
		if(q>30) ret=(ret*(1ll<<30)%p)%p,q-=30;
		else ret=(ret*(1ll<<q)%p)%p,q=0;
	}
	return ret;
}

inline bool cmp(node a,node b){
	return a.x<b.x;
}

inline bool cmp2(node a,node b){
	return a.y<b.y;
}

int main(){freopen("2254.b","r",stdin);
	//io();
	n=read(),m=read();
	if(n%2!=m%2){
		cout<<0<<endl;
		return 0;
	}
	k=read();
	for(int i=1;i<=k;++i){
		fid[i].x=read();
		fid[i].y=read();
		fid[i].z=read();
	}
	p=read();
	bool met=0,flag=0; ans=0;
	if(n>m){
		sort(fid+1,fid+1+k,cmp);
		for(int i=1,j=1,cnt,tmp;i<=n;++i){
			if((fid[j].x>i||j>k)&&!met){
				met=1;continue;
			}
			cnt=0,tmp=1;
			while(fid[j].x==i) tmp*=fid[j].z,j++,cnt++;
			if(cnt==m&&tmp!=-1) flag=1;
			//ans=(ans*pow2(m-cnt-1)%p)%p;
			if(cnt!=n) ans+=(m-cnt-1);
		}
	}else{
		sort(fid+1,fid+1+k,cmp2);
		for(int i=1,j=1,cnt,tmp;i<=m;++i){
			if((fid[j].y>i||j>k)&&!met){
				met=1;continue;
			}
			cnt=0,tmp=1;
			while(fid[j].y==i) tmp*=fid[j].z,j++,cnt++;
			if(cnt==n&&tmp!=-1) flag=1;
			//ans=(ans*pow2(n-cnt-1)%p)%p;
			if(cnt!=n) ans+=(n-cnt-1);
		}
	}
	//cout<<ans<<endl;
	//cout<<pow2(ans)<<endl;
	if(!flag) cout<<fpow(2,ans)<<endl;
	else cout<<0<<endl;
	return 0;
}
```

以下重新打的桶排

(标记了hack数据的判断

hack1：需要注意开始时填的数就已经让一行的积为0

hack2：需要判断一开始就有一行被填满的情况（否则会多减1

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

inline ll read(){
	ll s=0,w=1;char ch;
	while(ch=getchar(),!isdigit(ch)) if(ch=='-') w=-1;
	while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
	return s*w;	
}

const int N = 1000009;
ll n,m,p,k,ans=0;
int sum[N],pro[N];
bool usew=0,flag;

inline ll pow(ll q){		// 传过去要用long long
	ll ret=1,x=2;
	while(q>0){
		if(q&1) ret=ret*x%p;
		x=x*x%p;
		q>>=1;
	}
	return ret;
}

int main(){//freopen("2254.b","r",stdin);
	n=read();m=read();k=read();
	if((n+m)&1){
		cout<<0;
		return 0;
	}
	if(n<m){
		swap(n,m);usew=1;
	}
	for(int i=1,j,l;i<=k;++i){
		if(!usew) j=read(),read();
		else read(),j=read();
		l=read(); sum[j]++;
		pro[j]=pro[j]?l*pro[j]:l;			// hack1
	}
	p=read();
	for(int i=1;i<=n;++i){
		if(sum[i]!=m) ans+=m-sum[i]-1;		// hack2
		if(sum[i]==m&&pro[i]!=-1) flag=1;	// hack1
	}
	ans-=m-1;
    //cout<<ans<<endl;
	if(flag) cout<<0;
	else cout<<pow(ans)<<endl;;
	
	return 0;
} 
```

---
$$Fin$$

[我的博客](https://a-wnico-blog.blog.luogu.org/)


---

## 作者：Priestess_SLG (赞：0)

首先特殊判断某一行或某一列的数全部填完，且这行或这列所有数乘积不为 $-1$ 的情况，该情况无解。同样还有若 $n\not\equiv m\pmod 2$，则奇偶性分析后可知显然也无解。

先考虑一个简单一些的子问题：若 $k<\min(n,m)$，那么应该如何解决？很显然，此时至少存在一行和一列使得这一行和一列没有被填任何一个数。把这一行一列删去，剩下的数任意填写，最后用这一行一列的唯一填法把答案补充完整即可。

现在考虑 $k<\max(n,m)$ 的母问题。此时仍然存在一行**或**一列使得这一行**或**一列没有被填任何一个数。删除这一行**或**一列，那么剩下的每一行**或**每一列都可以任意填写答案，用最后这个行**或**列的唯一填法把答案补充完整。因此问题做完，通过预处理 $2$ 的幂次可以做到 $O(n+m)$ 解决问题。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
int bin[N], a[N], buc[N];
inline void add(int &x, int v) {
    x += v;
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n, m, k, p;
    cin >> n >> m >> k;
    if ((n + m) & 1) cout << "0\n";
    else {
        int ok = 0;
        if (n < m) swap(n, m), ok = 1;
        fill(a + 1, a + n + 1, 1);
        for (int i = 0; i < k; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            if (ok) swap(x, y);
            ++buc[x], a[x] *= z;
        }
        for (int i = 1; i < n; ++i)
            if (!buc[i]) {
                swap(buc[i], buc[n]);
                swap(a[i], a[n]);
                break;
            }
        cin >> p;
        bin[0] = 1 % p;
        for (int i = 1; i < N; ++i) bin[i] = bin[i - 1] * 2 % p;
        int res = 1;
        for (int i = 1; i < n; ++i)
            if (buc[i] == m) {
                if (a[i] != -1) {
                    cout << "0\n";
                    return 0;
                }
            } else res = res * bin[m - buc[i] - 1] % p;
        cout << res << '\n';
    }
    return 0;
}
```

---

## 作者：ncwzdlsd (赞：0)

**题目大意**

给定一个 $n\times m$ 的网格，每个格子上要么填 $1$，要么填 $-1$，有 $k$ 个位置上的数是已经填好的，其他位置都是空的。问有多少种填法使得任意一行或一列上的数的乘积为 $-1$。

$1 \leqslant n, m \leqslant 10^{3}$，$1 \leqslant k < \max (n, m)$。

**解法**

看到 $k$ 的范围，显然可知至少有一行或者一列为空。

假设空的是一行。那么剩下的行只需要满足那一行的乘积为 $-1$，而空的这一行对应一种唯一的填法。

显然，空的这一行填完之后的乘积为 $(-1)^m\times(-1)^{n-1}$，即 $(-1)^{m+n-1}$。

所以我们可以通过判断 $m$、$n$ 奇偶性是否相同进行计算求解。

每一行中，要么只填奇数个 $-1$，要么只填偶数个 $-1$。

这样就可以解决问题啦！时间复杂度为 $O(mn)$。

当然其实还有一种 $O(n)$ 的做法，这里要用到一个柿子（$n>0$ 时）：
$$
\sum_{k=0}^nC_n^k=2^{n-1}
$$

提示：可用杨辉定理、杨辉三角形证明。

于是乎，我们只需要预先处理 $2$ 的幂，就可以在 $O(n)$ 内解决问题。

代码实现也比较简单，这里就省略了，要自己思考哟QwQ

完结撒花！

---

## 作者：XL4453 (赞：0)


今日份降智：用 memset 给 long long 赋值为 1。

---
### 解题思路：

当 $n$ 和 $m$ 一个是奇数一个是偶数的时候一定无解。如果所有的值得乘积为 $1$，那么奇数的那一边一定有一个 $1$，反之，如果乘积是 $-1$，那么偶数的那一边一定有一个 $1$。这是显然的。

发现 $k$ 最大不超过 $n$，$m$ 最大值减一，也就是说一定有一行或者一列是空着的，所以空着的这一列或一行一定能保证这一行或者列是可以满足条件的。

那么另一种无解的情况就是有一列或者一行全部被赋值而且值为 $1$。

否则就可以用已经赋值的格子数来算这一列或者行提供的方案数了，若任意选择前 $n-cnt_i-1$ 个格子（$n$ 为行或者列的数量），然后最后一个格子根据前面的推出来，总方案数就是 $2^{n-cnt_i-1} 个$。

---
具体实现的时候可以翻转棋盘，强制规定 $n$ 或者 $m$ 较小。


---
### 代码：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,m,p,k,sw,cnt[1005],num[1005],x,y,z,ans=1,fi;
long long pow(int n){
	long long ans=1,now=2;
	while(n){
		if(n&1)ans=ans*now%p;
		now=now*now%p;
		n>>=1;
	}
	return ans;
}
int main(){
	scanf("%I64d%I64d",&n,&m);
	if((n+m)&1){
		printf("0\n");
		return 0;
	}
	scanf("%I64d",&k);
	if(n>m){
		swap(n,m);
		sw=1;
	}
	for(int i=1;i<=k;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		if(sw)swap(x,y);
		if(num[y]==0)num[y]=1;
		num[y]*=z;
		cnt[y]++;
	}
	scanf("%I64d",&p);
	for(int i=1;i<=m;i++){
		if(cnt[i]==0&&fi==0){
			fi=1;
			continue;
		}
		if(cnt[i]==n){
			if(num[i]==1){
				printf("0");
				return 0;
			}
			continue;
		}
		ans=ans*pow(n-cnt[i]-1)%p;
	}
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：JiaY19 (赞：0)



看到一道比较有意思的[题](https://www.luogu.com.cn/problem/CF40E)，于是就水了一发题解。

#### 思路

1. 一个通俗易懂的点，若n , m奇偶不同，那么直接判无解。

2. 看一眼k的范围。

$$0~\leq~k~<~\max(n,m)$$

嗯，好东西，不妨设$n > m$。

那么，k最大只能为$n - 1$。

所以即使每一行都放一个数，也**都**会有空的一行。

所以，我们就不需要考虑列的数了，因为最后一行可以满足乘积。

3. 那么对于行呢？

同样的道理，只需要将最后一列空出来，其余的随意就可以了。

所以，一个式子就出来了。

$$ans~=~ans~*~num[m~-~1~-~cnt[i]]~\bmod~p;$$

4. 一些细节。

- 对于$m>n$时我们可以看作将棋盘转了一下。

- 若一整行都满了，可以用一个数组记下它的乘积，如果为一，就直接判无解。

其余细节见代码。

#### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , m , k , p , x , y , z , ans = 1 , cnt[1010] , sum[1010] , num[1010];
//cnt为每行已填个数，sum统计每行乘积，num为2的幂。 
bool flag , kong;
signed main()
{
	cin >> n >> m >> k;
	if(n % 2 != m % 2)
	{
		cout << 0; return 0;
		//判断奇偶 
	}
	if(n < m) swap(n , m) , flag = 1;
	//如果m>n，就调换棋盘 
	for(int i = 1;i <= n;i++) sum[i] = 1;
	//初始化统计乘积数组 
	for(int i = 1;i <= k;i++)
	{
		cin >> x >> y >> z;
		if(flag) swap(x , y);
		cnt[x]++ , sum[x] *= z;
	}
	//输入 
	cin >> p; num[0] = 1;
	for(int i = 1;i <= n;i++) num[i] = (2 * num[i - 1]) % p;
	//初始化num数组 
	for(int i = 1;i <= n && ans;i++)
	{
		if(cnt[i] == m && sum[i] == 1) ans = 0; 
		//如果填了一行为1，直接退出 
		else if(cnt[i] == m && sum[i] == -1) continue;
		//如果为-1，则不加不减 
		else if(cnt[i] == 0 && !kong) kong = 1;
		//判到的第一个没填的选为上文的最后一行 
		else ans = ans * num[m - 1 - cnt[i]] % p;
		//直接计算 
	}
	cout << ans;
	return 0;
}

```

完结撒花！


---

## 作者：Erica_N_Contina (赞：0)

## 思路

注意这一点，$0~\leq~k~<~\max\{n,m\}$，所以我们惊奇的发现，无论如何，总有至少一行或者一列被空出来。我们假设 $n≥m$，那么即便每一列都有数字，那么也会有若干行没有数字。

那么我们就可以随便填前 $n-1$ 行了，因为 $1$ 和 $-1$ 十分特殊——如果要求为 $-1$ 但是前 $n-1$ 行乘积为 $1$ 的话，我们在第 $n$ 行 $1$ 放置一个 $-1$ 即可。如果要保持不变，那么放置一个 $1$ 即可。

此时我们再考虑每一行乘积为 $-1$ 的要求。

假如有空余的列没有数字，那么在前 $n-1$ 行，$m-1$ 列都可以随便填了。但是如果不存在有有空余的列没有数字，那么我们就需要保证每一行中 $-1$ 的个数为奇数个。所以，我们并不需要知道该行有哪些位置已经填了哪些数，我们只需要知道该行填了几个数字。

假设第i行已经填了 $cnt_i$ 个数字，那么该行的方案数为 $2^{m-cnt_i-1}$，注意最后一个位置我们要留下来以保证该行的乘积为 $-1$。最后一行我们也要保留下来保证每一列乘积为 $-1$。

但是如果该行已经被填满了，我们只需要判断其是否合法即可。因为 $k<\max\{n,m\}$ 而不是 $k<\min\{n,m\}$ 所以这种情况有可能成立。

此时我们再来考虑一下无解的情况。

我们要求每一行、每一列都满足所有数的乘积是 $−1 $，那么把所有行的乘积相乘为 $(-1)^n$，同理把所有列的乘积相乘为 $(-1)^m$。由于我们知道，$(-1)^n$ 和 $(-1)^m$ 本质上都是把矩阵中所有的数相乘得到的，所以当 $(-1)^m≠(-1)^n$ 时，产生了矛盾。

那么什么情况下会不相等呢？当且仅当 $m,n$ 奇偶不同或者有一个为 $0$（其实也与前面的情况一样）。于是我们知道如果 $n,m$ 奇偶性不同，则无解。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=1e3+5;
const int M=1e3;
int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,a[N],b,q,sw,k,ans,res,tmp,cnt[N],mul[N];
int dp[N][N];
int tot,du[N];
int L;

int ksm(int c,int k) {
	int res=1;
	if(!c)return 0;
	while(k){
		if(k&1)res=(res*c)%MOD;
		k>>=1;
		c=(c*c)%MOD;
	}
	return res;
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>m>>n>>k;
	

//	cerr<<"2^8="<<ksm(2,8)<<endl;
	
	if(m>n)swap(m,n),sw=1;
//	memset(mul,1,sizeof mul);//注意初始化不能memset(1)	
	for(int i=1;i<=n;i++)mul[i]=1;
	for(int i=1;i<=k;i++){
		int x,y,v;
		cin>>x>>y>>v;
		if(sw)swap(x,y);
		cnt[y]++;//注意这里不是x是y
		mul[y]*=v;
		
	}
	cin>>MOD;
	ans=1;
	
	if((m+n)%2){
		cout<<0<<endl;
		return 0;//无解
	}
//	cerr<<"OK"<<endl;
	int flg=1;
	for(int i=1;i<=n;i++){
//		cerr<<"i="<<i<<endl;
//		cerr<<cnt[i]<<' '<<mul[i]<<endl;
		if(0==cnt[i]&&flg){
			flg=0;continue;//将这一行作为保留行
		}
		if(cnt[i]==m){
			if(mul[i]==1){
				cout<<0<<endl;
				return 0;//无解
			}
		}else{
			int res=ksm(2,m-cnt[i]-1);
			ans*=res;
			ans%=MOD;
		}
		
	}
	cout<<ans<<endl;
	return 0;
}

//check your long long and the size of memery!!!

```




---

## 作者：Doveqise (赞：0)

来补模拟赛T3  
这道题为什么是蓝的（  
把模拟赛数据范围贴上来，方便分段解决  

对于30%的数据，$1 \leq n * m \leq 21 $。  
对于70%的数据，$1 \leq n , m \leq 1000 $。  
其中有10%的数据，$1 \leq n,m \leq 1000,k=0$。  
对于100%的数据，$1 \leq n , m \leq 1000000 $。  
$0 \leq k \leq max(n,m)$，  
$1 \leq a \leq n,1\leq b \leq m, c \in \{1,-1\} ,$  
$2 \leq p \leq 10^9+7,$  
数据保证不会同一个格子填两次。  

解法1：  
暴力$DFS$。  
得分：30pts  

解法2：  
特判$n+m$为奇数时答案显然为0。  
证明：  
我们把每一行和每一列的答案乘起来。  
易得，这种行为等价于将每一个格子的数字平方再相乘。  
但是每一行和每一列的答案相乘为-1，而后者为1。  
$Q.E.D.$  
得分：+10pts  

解法3：  
注意到$k \lt max(n,m)$，则必有一行或一列是完全空的。  
不妨设空的为一行，显然其他行填完后，这行有且只有一种填法。  
则问题转化为在一维上已经若干了多少个位置，有多少种合法填数情况。  
假设某行一共$s$个位置，已经填好$t$个位置，可以想到使用线性方法填这一行，然后用乘法原理求出答案。  
得分：70pts  

解法4：  
优化在一维上求解的方法。  
借用解法3的概念，  
若初始乘积为$1$，则$k=0$；   
若初始乘积为$0$，则$k=1$；  
不难发现一维上的方案数可写成$ C^{s-t}_{k} + C^{s-t}_{k+2} +C^{s-t}_{k+4} + C^{s-t}_{k+6} + ……$  
不难发现答案为$2^{s-t-1}$。  
得分：100pts

（记得JZ的OJ里面有一道这个题的加强版，$n$和$m$的范围扩大到了$10^9$，$k$为$10^6$，可惜自己的账号到期了QwQ就不能去交惹）  

代码如下：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
typedef long long ll;
ll T[maxn], N[maxn];
ll n, m, k, mod;
ll qpow(ll x, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b % 2)
            res = (res * x) % mod;
        x = (x * x) % mod;
        b >>= 1;
    }
    return res % mod;
}
signed main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    int swp = 0;
    if (n < m)
        swap(n, m), swp = 1;
    if ((n + m) % 2)
    {
        puts("0");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        N[i] = 1;
    for (int i = 1, x, y, z; i <= k; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        if (swp)
            swap(x, y);
        T[x]++;
        N[x] *= z;
    }
    scanf("%lld", &mod);
    ll det = 0;
    for (int i = 1; i <= n; i++)
    {
        if (T[i] == m && N[i] == 1)
        {
            puts("0");
            return 0;
        }
        det += min(T[i], m - 1);
    }
    printf("%lld\n", qpow(2, 1ll * (n - 1) * (m - 1) - det));
    return 0;
}
```


---

