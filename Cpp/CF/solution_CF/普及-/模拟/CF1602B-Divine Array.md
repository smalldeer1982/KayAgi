# Divine Array

## 题目描述

给定一个序列，一次转换是将一个数变成这个数在这个序列中出现的次数。

序列 $\{2,1,1,4,3,1,2\}$ 中，$2$ 出现 $2$ 次，$1$ 出现 $3$ 次，$3$ 和 $4$ 出现 $1$ 次，那么这个序列进行一次转换之后就变成了 $\{2,3,3,1,1,3,2\}$，同理，进行两次转换后是 $\{2,3,3,2,2,3,2\}$，进行三次转换后是 $\{4,3,3,4,4,3,4\}$。

有 $q$ 次询问，每次询问第 $x$ 个位置的元素经过 $k$ 次转换之后是什么。

## 说明/提示

$1\le t\le1000,1\le\sum n\le2000,1\le a_i,x\le n,1\le\sum q\le10^5，0\le k\le10^9$。

## 样例 #1

### 输入

```
2
7
2 1 1 4 3 1 2
4
3 0
1 1
2 2
6 1
2
1 1
2
1 0
2 1000000000```

### 输出

```
1
2
3
3
1
2```

# 题解

## 作者：wei2013 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1602B)

## 题目大意：
给定一个序列 $a$，询问 $q$ 次，每次将 $a_i$ 变成 $a_i$ 的个数，问 $k$ 次后，第 $x$ 项是几。
## 思路：
时间限制十分宽松，$n$ 只到 $2000$，仔细观察，可发现任何一个序列在进行一定次数的变换后就会一直不变，明显可直接暴力模拟，时间复杂度 $\mathcal{O(n^2)}$。


## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a[2005][2005],cnt[2005];
int main(){
	cin>>T;
	while(T--){
		int n;
		cin>>n; 
		for(int i=1;i<=n;i++){
			cin>>a[i][0];
		}
		for(int j=1;j<=n;j++){
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=n;i++){
				cnt[a[i][j-1]]++;
			}
			for(int i=1;i<=n;i++){
				a[i][j]=cnt[a[i][j-1]];
			}
		}
		int q;
		cin>>q;
		while(q--){
			int x,k;
			cin>>x>>k;
			if(k>n){
				cout<<a[x][n]<<endl; 
			}else{
				cout<<a[x][k]<<endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：rouxQ (赞：1)

具体实现方法别的题解讲的很清楚了，就是暴力模拟，模拟 $n$ 次一定可以使这个序列不再变化，所以一个粗略的复杂度上界是 $O(n^2)$，可以通过本题。下面简单证明一下该做法一个更精准的复杂度上界为 $O(n\log n)$.

如果序列中某几个数出现的次数相同，我们称这几个数是**可合并的**，称这些数为一个**可合并组**，称一个可合并组的**频率**为该组内数出现的次数。在某次操作中，一些可合并组进行合并后，这些组的频率至少会变为原来的两倍。以此类推，操作 $O(\log_2n)$ 次后，可合并组的频率会达到 $O(n)$，意味着不会有可合并组存在，这就完成了证明。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2005][20];
int cnt[2005];
int main (){
	int T;
	cin >> T;
	while(T--){
		int n, q;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i][0];
		int Max, f = 1;
		for (Max = 1; Max <= 15; Max++){//操作次数开成15次已经可以通过
			memset(cnt, 0, sizeof(cnt));
			for (int j = 1; j <= n; j++) cnt[a[j][Max - 1]]++;
			for (int j = 1; j <= n; j++) a[j][Max] = cnt[a[j][Max - 1]];
		}
		Max--;
		cin >> q;
		int x, k;
		while(q--){
			cin >> x >> k;
			cout << a[x][min(k, Max)] << endl;
		}
	}
	return 0;
}
```

---

## 作者：shredded_beef_qwq (赞：0)

## 具体思路
从题目中我们可以知道 $n \le 2000$，$n$ 很小，那我们就可以用暴力来解决这道题目。我们在仔细读题后可以发现，如果按照题目的题意写，不仅很简单而且不会超时，那我们就先记录每次改变完以后的数组中每个数的个数，再按照题意将每一位上的数改为这个数在原数组中的个数，最后输出第 $x$ 位第 $k$ 次改变后的数就可以了。
## 提示
枚举次数最多到 $n$，因为同过我们自己造数据，并计算可以知道，当枚举到 $n$ 时变换后的数组已经在前面出现过了，所以就不用再枚举了。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2010][2010],f[2010];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,k,q;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i][0];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) f[a[j][i-1]]++;
			for(int j=1;j<=n;j++) a[j][i]=f[a[j][i-1]];
			memset(f,0,sizeof(f));
		}
		cin>>q;
		while(q--){
			cin>>x>>k;
			if(k>n) k=n;
			cout<<a[x][k]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：little_sheep917 (赞：0)

> 给出一个长度为 $n$ 的序列 $a$ . 会按照一定规则进行变换，在第 $i$ 步中，对于位置 $j$ , $a_j$ 会变为变换前 $a_j$ 在序列中出现的个数 . 这样的变换会永远进行 .
>
> 有 $q$ 个询问，求 $a_x$ 在进行 $k$ 次变换后的值 .
>
> 多测，有 $t$ 组数据 .
>
> $1\leq t\leq 1000,1\leq n\leq 2000,1\leq a_i\leq n,1\leq q\leq 100000,0\leq k_i\leq 10^9,\sum n\leq 2000,\sum q\leq 100000$

考虑对于 $a_i$ 在一次变化中会经历怎样的改变 。

$a_i=cnt(a_i)$ ，$a_i$ 保持不变 。

$a_i>cnt(a_i)$ ，$a_i$ 变小 。

$a_i<cnt(a_i)$ ，$a_i$ 变大 。

光看这个，发现不了规律，但是发现 $a_i>cnt(a_i)$ 的情况，只会在第一轮出现 。 一旦 $a_i\leq cnt(a_i)$ 时，在后面的所有变化中 $a_i\leq cnt(a_i)$ 肯定成立 。 因为当前 $a_i$ 的出现次数至少为 $a_i$ 次，不会变少，只会变多 。

所以，到了某一个固定的轮次，所有的 $a_i=cnt(a_i)$ 。 序列会一直保持不变 。

那么，到达这个固定的轮次，要经历多久呢 ?

除了第一轮，变化相当于把多个集合合并成一个集合，这种合并最多进行 $n$ 次 。

那么，最多在 $n$ 轮之后，$a$ 序列保持不变 。

所以，可以模拟一下这个过程，直到序列不再改变，存储过程中所有变化过的序列 . 最后询问的时候判断一下，是在这个临界之前还是之后 ，分别处理就好啦 。

时间复杂度 : $O(\sum q+\sum n^2)$

空间复杂度 : $O(n^2)$

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	} 
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)	
		putchar(a[i]+'0');
}
int t;
int n,q;
int cnt[2010];
vector<vector<int> >v;
vector<int>get_vec(vector<int>a){
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<(int)a.size();i++)cnt[a[i]]++;
	vector<int>b;
	for(int i=0;i<(int)a.size();i++)b.push_back(cnt[a[i]]);
	return b;
}
void solve(){
	v.clear();
	n=read();
	vector<int>a;
	for(int i=0;i<n;i++){
		int x=read();
		a.push_back(x);
	}
	v.push_back(a);
	while(true){
		vector<int>b=get_vec(v.back());
		if(v.back()==b)break;
		v.push_back(b);
	}
	q=read();
	for(int t=0;t<q;t++){
		int pos=read()-1,i=read();
		if(i<(int)v.size()){
			print(v[i][pos]);
		}else{
			print(v.back()[pos]);
		}
		putchar('\n');
	}
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/

```
写在最后，也可以来我的cnblog看看哦.
[link](https://www.cnblogs.com/suadwm/p/15509811.html)

---

## 作者：gaozitao1 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1602B)

经过对样例的分析，会发现一个序列经过一些调整，最后调整之后序列不会改变。所以就可以将序列暴力调整到不会改变，查询时输出结果。

对于每个序列，做 $n$ 次操作时序列就不在改变了（一般小于 $n$ 次，时间复杂度为 $O\left(\sum n^2+\sum q\right)$。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
int b[2001],a[2001][2001];
//a[i][j]表示第i次操作后第j个数的值
int main()
{
	int c,i,j,k,n,q,t,x;
	scanf("%d",&t);
	while(t--)
	{
		c=1;
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[0][i]);
		for(i=0; c; ++i)//c表示上一次操作是否改变，如果没改变就退出
		{
			memset(b,0,sizeof(b));
			c=0;//注意清空
			for(j=1; j<=n; ++j)
				++b[a[i][j]];
			for(j=1; j<=n; ++j)
			{
				if(a[i][j]!=b[a[i][j]])
					c=1;//如果改变了就记录
				a[i+1][j]=b[a[i][j]];
			}
		}
		--i;//i表示到第几次操作不变了
		scanf("%d",&q);
		while(q--)
		{
			scanf("%d%d",&x,&k);
			if(i<k)
				k=i;//如果超过了，就变成i
			printf("%d\n",a[k][x]);
		}
	}
	return 0;
}
```

---

## 作者：HerikoDeltana (赞：0)

## 「Div2.B」题目简述

给出一个长度为 $n$ 的序列，求问在经过第 $k$ 次变换之后序列中的第 $x$ 个数。

第 $i$ 次变换为：对于所有的 $1 \le j \le n$，将 $a_j$ 变为 $a_j$ 在第 $i-1$ 次修改后出现的次数。

## 「Div2.B」思路简述

时空限制还是挺宽的，而且我们可以简单的手玩一下发现一个序列进行最多 $n$ 操作之后就不会发生变化了，所以我们预处理出每次操作后的序列即可。

## 「Div2.B」Code

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>

#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
#define Files() freopen("RNMTQ.in","r",stdin);freopen("RNMTQ.out","w",stdout)

using namespace std;

template<typename J>
I void fr(J &x)
{
    short f(1);x=0;char c=getchar();

    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        
        c=getchar();
    }

    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }
   
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    if(x<0) x=-x,putchar('-');

    static short stak[35];short top(0);

    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);

    while(top) putchar(stak[--top]+'0');

    k?puts(""):putchar(' ');
}

CI MXX(2001);

int a[MXX][MXX],co[MXX];

S main()
{
    Files();

    int T;fr(T);

    while(T--)
    {
        int n,q;fr(n);

        for(int i(1);i<=n;++i) fr(a[i][0]),co[i]=0;

        fr(q);

        for(int i(1);i<=n;++i) ++co[a[i][0]];

        for(int i(1);i<=n;++i)
        {
            for(int j(1);j<=n;++j) a[j][i]=co[a[j][i-1]];

            for(int j(1);j<=n;++j) co[j]=0;

            for(int j(1);j<=n;++j) ++co[a[j][i]];
        }

        while(q--)
        {
            int x,k;fr(x),fr(k);

            if(k>n) fw(a[x][n],1);
            else fw(a[x][k],1);
        }
    }

    Heriko Deltana;
}
```

---

## 作者：智子 (赞：0)

## 题意

输入一个长度为 $n$ 的序列 $a$，对 $a$ 进行若干次变换，每次变换会将 $a_i$ 变成 $a_i$ 在 $a$ 中的出现次数。

给出 $q$ 个询问，每次输入 $x$ 和 $k$，求 $k$ 次变换后的 $a_x$。

## 思路

分析一下样例再自己造几组数据后会发现，任何一个序列在进行一定次数的变换后就会一直不变。容易发现变换到不变的序列中需要的次数肯定不会超过 $n$ （有人说不超过 $log\ n$），所以这道题可以直接模拟，复杂度 $O(n^2)$

## 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 2000 + 5;

int last[MAXN], ans[MAXN][MAXN], cnt[MAXN];
int n, q;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &last[i]);
            ans[i][0] = last[i];
        }
        for(int now = 1; now <= n; now++) {
            memset(cnt, 0, sizeof(cnt));
            for(int i = 1; i <= n; i++) {
                cnt[ans[i][now - 1]]++;
            }
            for(int i = 1; i <= n; i++) {
                ans[i][now] = cnt[ans[i][now - 1]];
            }
        }
        scanf("%d", &q);
        for(int i = 1; i <= q; i++) {
            int x, k;

            scanf("%d%d", &x, &k);
            if(k > n) {
                k = n;
            }
            printf("%d\n", ans[x][k]);
        }
    }

    return 0;
}

```

---

## 作者：Kris_hukr (赞：0)

第一次写题解，大佬轻喷。

### 题目大意

给定数组 $a$ ，每次变换将 $a_i$ 变换为 $a$ 中 $a_i$ 出现的次数。询问 $k$ 次变换后 $a_x$ 的值。

$e.g.$

$$
\begin{array}{cc}
	\text{初始数组} &2 \ 1 \ 1 \ 4 \ 3 \ 1 \ 2 \\
	\text{第一次变换后} & 2 \ 3 \ 3 \ 1 \ 1 \ 3 \ 2 \\
	\text{第二次变换后} & 2 \ 3 \ 3 \ 2 \ 2 \ 3 \ 2 \\
	\text{第三次变换后} & 4 \ 3 \ 3 \ 4 \ 4 \ 3 \ 4 \\
	\dots &\dots \\
\end{array}
$$

### 分析

我们称 $a$ 中所有相同的元素为一**组**。

容易发现，当一组内的元素**等于**其出现次数时，这组元素便不再变化。我们称这种状态为**稳定**。

所以说，当没有组发生**合并**，也就是所有元素都不发生变化时，以后也不会再有变化。此时整个数组**稳定**。

换言之，在整个数组稳定前，组的数量**严格递减**。

很容易得出最多变换 $n$ 次整个数组便**稳定**的结论。

（官方题解说最多 $\log n$ 次就会达到稳定，可是我不会证。不过 $n$ 次的复杂度也足够通过此题了。）

### 代码

```cpp
#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

int a[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();

        for (int i = 1; i <= n; i++) {
            a[0][i] = read<int>();
        }
        for (int i = 1; i <= n; i++) {
            auto *cnt = new int[n + 1]{};
            for (int j = 1; j <= n; j++) {
                cnt[a[i - 1][j]]++;
            }
            for (int j = 1; j <= n; j++) {
                a[i][j] = cnt[a[i - 1][j]];
            }
        }

        int q = read<int>();
        while (q--) {
            int x = read<int>(), y = read<int>();
            std::cout << a[std::min(y, n)][x] << '\n';
        }
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
```



---

## 作者：A_Đark_Horcrux (赞：0)

本来在想用什么数据结构，结果暴力就过了……原来是 $n$ 太小了。

经过手动模拟/观察样例可以发现这样的变换不能持续下去，必定有一个时候 $\forall i, s_i=a_i$（其中 $s_i$ 为出现次数）

再经过手动模拟发现变换次数不超过 $n$ 次

于是 $O(n^2)$ 模拟即可。

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int T,n,q,x,k,i,j,a[2010][2010],cnt[2010];
int count(int x)
{
	int s=0,last=x;
	while(last>1) s+=last,last=sqrt(last);
	return s+1;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n); int t=count(n);
		for(i=1;i<=n;i++) scanf("%d",&a[i][0]);
		for(j=1;j<=t;j++)
		{
			for(i=1;i<=n;i++) cnt[i]=0;//记录数组
			for(i=1;i<=n;i++) cnt[a[i][j-1]]++;//记录
			for(i=1;i<=n;i++) a[i][j]=cnt[a[i][j-1]];//赋值
			//for(i=1;i<=n;i++) printf("%d ",a[i][j]); puts("");
		}
		scanf("%d",&q);
		while(q--) scanf("%d %d",&x,&k),printf("%d\n",k>n?a[x][n]:a[x][k]);//输出，如果超过k次输出第n次结果
	}
	return 0;
}
```

这里是一个不严谨的证明：

考虑每一次变换以后使变换后序列数字种类数 $x$ 最多

则 $n\geq \frac{x(x+1)}{2}$

每一次的 $x$ 均在 $\sqrt{n}$ 量级

所以最多大约需要 $\sqrt{n}+\sqrt[4]{n}+\sqrt[8]{n}...+1$ 次操作使得数字总类数等于1

全部加起来约等于 $n$ 

但是最后的数字种类数可能大于1，

所以应该是小于 $n$ 的。



---

