# [NEERC 2015] Adjustment Office

## 题目描述

加里森和安德森在一家名为“Adjustment Office”的公司工作。在竞争公司中，员工改变现实，而在这家公司中，他们尝试预测未来。

他们得到一个 $n \times n$ 的大方板。最初在这个方板的每个单元格 $(x, y)$ 中写着 $x + y$ 的值（$1 \leq x, y \leq n$）。他们知道在未来将会有两种类型的查询：
- “R $r$”——计算第 $r$ 行的所有值之和，打印结果并将第 $r$ 行的所有值设为零；
- “C $c$”——计算第 $c$ 列的所有值之和，打印结果并将第 $c$ 列的所有值设为零。

他们已经预测了将会有哪些查询和结果。他们需要确保他们正确预测了结果。请帮助他们计算查询的结果。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 7
R 2
C 3
R 2
R 1
C 2
C 1
R 3
```

### 输出

```
12
10
0
5
5
4
0
```

# 题解

## 作者：lrx___ (赞：6)

**思路**

由于 $n$ 有 $10^6$，所以不能直接模拟，要用数学来做。

思考：删除行会影响列，删除列会影响行。

如果没有删除任何行，那么第 $i$ 列的和为 $\frac{(n+1)\!\times\!n}{2}\!+\!n\!\times\!i$。

如果删除了一些行，剩余 $cr$ 行，这些行的行号之和为 $sr$，那么第 $i$ 列的和就为剩余行号之和加上剩余行数乘列号，转换为数学公式就是 $sr\!+\!cr\!\times\!i$。对于行同理。于是这道题就做出来了。

要注意一点，$n\!\times\!n$ 会超出 `int` 的范围。

**代码**

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const int N=1e6+5;
bool vr[N],vc[N];
/* (vr[i],vc[i])分别为第i（行，列）是否被删除 */
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,q,m;
	ll cr,cc,sr,sc;
	char c;
	/* (cr,cc)分别为剩余的（行，列）数  (sr,sc)分别为剩余的（行号，列号）之和 */
	
	cin>>n>>q;
	cr=cc=n;sr=sc=cc*(n+1)/2;
	while(q--){
		cin>>c>>m;
		if(c=='R'){
			if(vr[m]){
				cout<<"0\n";
			}else{
				cout<<sc+m*cc<<'\n';
				/* 思路中有解释 */
				sr-=m;cr--;vr[m]=1;
			}
		}else{
			if(vc[m]){
				cout<<"0\n";
			}else{
				cout<<sr+m*cr<<'\n';
				sc-=m;cc--;vc[m]=1;
			}
		}
	}
	return 0;
}
```

---

## 作者：L_sdcs (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P6974)

### 题目大意


有一个大小为 $ n \times n $ 的矩阵，每个位置的值为该位置的行数$+$列数。

接下来有 $ q $ 次操作：

$ R\;i $：输出第 $i$ 行的总和并整行消去。

$ C\;i $：输出第 $i$ 列的总和并整列消去。

~~这不就是把题目复制下来吗？~~

### 大致思路

我们可以把一个值看成行数$+$列数。~~(废话)~~

显然的，每删去一行，对其他行是没有影响的。

于是我们考虑对列的影响。

假设我们删去第$i$行，第$j$列的总值就少了$i+j$。

我们用一个变量$r$储存被删去的$i$的和，$rs$表示被删去的行数。

就可以得出第$j$列的剩余值为:$(n+1)*n/2-r+(n-rs)*j$。

对行来说同理。

再定义两个$bool$类型的数组来判断次行/列是否已被删去就行了。


总体而言这道题比较简单(~~所以我会做~~。
### 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int an=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	for(;c>='0'&&c<='9';c=getchar())
		an=(an<<1)+(an<<3)+c-'0';
	return an;
}
long long r,l,rs,ls;//n有1e6，n*n是会爆int的
bool br[1000006],bl[1000006];
int main()
{
	long long n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		char c;
		cin>>c;
		int x=read();
		if(c=='R')
		{
			if(br[x])//如果已经被删了，输出0即可。
				cout<<0<<endl;
			else
			{
				cout<<(1+n)*n/2-l+x*(n-ls)<<endl;
				rs++;//被删行数
				r+=x;
				br[x]=1;
			}
		}
		else
			if(bl[x])
				cout<<0<<endl;
			else
			{
				cout<<(1+n)*n/2-r+x*(n-rs)<<endl;
				ls++;//被删列数
				l+=x;
				bl[x]=1;
			}
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：3)

~~水~~思维题。
# 大意
有一个矩阵 $a$，$a_{ij}=i+j$。

两个操作，一个删一行，一个删一列。

删完之后剩下的行 / 列不会向上 / 左补齐。

每次操作后输出所有删掉的 $a_{ij}$ 的和。
# 思路
这种题一看就可以用~~各种神奇的~~数据结构来做，

然而~~我不会~~它是道橙题，没有必要。

我们分别分析操作 $1,2$ 对矩阵的影响。
## 操作1
设消的是第 $i$ 行。

对剩下的行：无影响。

对剩下的列：对于第 $j$ 列，使这一列的和减少 $i+j$。
## 操作2
设消的是第 $j$ 列。

对剩下的行：对于第 $i$ 行，使这一行的和减少 $i+j$。

对剩下的列：无影响。


------------
接下来，我们就要处理询问的结果了。

## 行的和
易得第 $i$ 行初始和为 $\dfrac {n(n+1)}2+ni$。

此时设共消了 $x$ 列，消去的每一列的编号和为 $p$。

那么根据上面，这个初始和要减去 $xi+p$
## 列的和
易得第 $j$ 列初始和为 $\dfrac {n(n+1)}2+nj$。

此时设共消了 $y$ 行，消去的每一行的编号和为 $q$。

那么根据上面，这个初始和要减去 $yj+q$


------------
这样，每次操作就是 $O(1)$ 的，总复杂度 $O(q)$。
# 代码
注意 `long long`。
```cpp
#include <iostream>
#define int long long
using namespace std;
int n, x, y, p, q, t;bool fr[1000050], fc[1000050];
signed main()
{
    cin >> n >> t;
    for(int i = 0;i < t;++i)
    {
        int m;char c;cin >> c >> m;
        switch(c)
        {
            case 'R':
                if(fr[m]) {cout << 0 << endl;break;}
                fr[m] = 1;++y;q += m;cout << n * (n + 1) / 2 + n * m - (x * m + p) << endl;break;
            case 'C':
                if(fc[m]) {cout << 0 << endl;break;}
                fc[m] = 1;++x;p += m;cout << n * (n + 1) / 2 + n * m - (y * m + q) << endl;break;
        }
    }
    return 0;
}
```


---

## 作者：Zhangyuhao2009 (赞：2)

# 题解
[题目](https://www.luogu.com.cn/problem/P6974)

## 思路
1. 如果直接用二维数组，时间复杂度为 $O(nq)$，空间复杂度 $n^2$，超时超空间；
2. 因此，我们可以利用行和列两个一维数组来模拟二维（即代码中的 $h$ 与 $l$）。由题，每一个空可以拆分为行数部分+列数部分，因此一行的和可以表示为未归零的列数×行的下标+该行下标和，代码体现为 $h_t+sl$（$sl$ 为一行列数下标之和（删去一列对于每行列数部分影响相同，所以可以用一个变量表示），$h_t$ 为 $t$ 行的每格的行数部分之和（在后面的代码里也可以体现为该行是否已被清空））。
3. 但是此时若每清空一列便减去所有行的行数部分，时间复杂度则为 $O(n)$，超时，所以我们引进了 $nl$，即已经删去的列数，原先的式子变为 $h_{t}+sl-nl \times t$，可以完美解决超时问题。列数同上。接下来上代码！

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll h[1000010],l[1000010];
ll sh,sl,n,q,nh,nl;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		h[i]=l[i]=n*i;
		sh+=i;
		sl+=i;
	}
	while(q--)
	{
		char c;
		int t;
		cin>>c>>t;
		if(c=='R')
		{
			if(h[t])
			{
				cout<<h[t]+sl-nl*t;//该行总和
				nh++;//已经删去行数加一
				sh-=t;//每一列都删去以该行为下标的格
			}
			else//已经删了
			{
				cout<<0;
			}
			cout<<endl;
			h[t]=0;//标记该行已经删了
		}
		else
		{
			if(l[t])
			{
				cout<<l[t]+sh-nh*t;
				nl++;//已经删去列数加一
				sl-=t;
			}
			else
			{
				cout<<0;
			}
			cout<<endl;
			l[t]=0;
		}
	}
	return 0;
}

```
对了，最重要的是：
 **参加运算的数据一定要开 `long long`！**


---

## 作者：zhangjiting (赞：2)

## 题解

这个题我们考虑先预处理出这个网格图每一行每一列的和，逐个暴力求 $O(n^2)$ 必超时，考虑求出了第一行第一列的和，显然下一行的和为这一行的和加上 $n$。$O(n)$ 就能递推出结果。然后考虑一次操作一。如果这一列已经空了，输出 $0$ 即可，如果没有，先观察有多少行的和已经是 $0$ 了，这一列的实际的和就是：

原来求出的和 $- ($ 和为 $0$ 的行的行号的和 $+$ 这一列的列号 $\times$ 和为 $0$ 的行的数量 $)$

然后把这一列的和记为 $0$。然后记录下来。对操作二同理。

注意：所有参加计算的值都需要 `long long`，否则会溢出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
#define ll long long
vector<ll>rd, cd;
ll rdsum, cdsum,rsum[N], csum[N];
int main(){
    ll n, q;
    cin>>n>>q;
    rsum[1] = (2ll + n + 1ll) * n / 2;
    for (int i = 2; i <= n; ++i) rsum[i] = rsum[i - 1] + n;
    for (int i = 1; i <= n; ++i) csum[i] = rsum[i];
    char op[2];
    ll p = 0;//p不用ll会溢出
    for (int i = 1; i <= q; ++i){
        cin>>op>>p;
        if (op[0] == 'R')
        {
            if (!rsum[p]) cout<<0<<endl;
            else{
                rdsum += p;
                cout<< rsum[p] - (ll)cd.size() * p - cdsum<<endl;
                rsum[p] = 0;
                rd.push_back(p);
            }
        }
        else if (op[0] == 'C'){
            if (!csum[p])cout<<0<<endl;
            else{
                cdsum += p;
                cout<<csum[p] - (ll)rd.size() * p - rdsum<<endl;
                csum[p] = 0;
                cd.push_back(p);
            }
        }
    }
    return 0;
}
```


---

## 作者：Unnamed114514 (赞：2)

显然 $O(nq)$ 的正向求和是行不通的，所以我们需要逆向思维，即求出删除了多少个。

下面以行为例进行求解，列同理：

若该行已经被清除，那么答案是 $0$。

接下来，我们考虑这一行里面的元素的和：$\sum\limits_{j=1}^n i+j$ 注意到对于同一行 $i$ 是定值，给它提出来，就是 $i\times n+\sum\limits_{j=1}^nj$，那么此时我们就已经能求出初始的和为 $i\times n+\dfrac{n(n+1)}{2}$。

此时我们来考虑删除一列会造成哪些影响：会减少一个贡献的 $i$ 和一个贡献的 $j$，$i\times n-i=i\times(n-1)$，所以我们只需要记录一个 $cnt$ 表示删除元素的数量，那么前半部分的式子就是 $i\times (n-cnt)$；对于后半部分，若删除列 $i$，那么就会减少 $i$，那么我们记录 $sum$ 为删除列的编号的和，那么后半部分的答案就是 $\dfrac{n(n+1)}{2}-sum$。

最终全体答案就是 $\dfrac{n(n+1)}{2}-sum+i(n-cnt)$。

注意到删除一列对每一行的 $cnt$ 和 $sum$ 的影响都相同，所以我们只需要对所有行打一个标记即可。

时间复杂度 $O(q)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5;
int n,q,cnt1,cnt2,sum1,sum2,t;
char c;
bool vis1[maxn],vis2[maxn];
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>q;
	while(q--){
		cin>>c>>t;
		if(c=='R'){
			if(vis1[t]){
				puts("0");
				continue;
			}
			printf("%lld\n",(n-cnt1)*t+n*(n+1)/2-sum1);
			sum2+=t,++cnt2,vis1[t]=1;
		} else{
			if(vis2[t]){
				puts("0");
				continue;
			}
			printf("%lld\n",(n-cnt2)*t+n*(n+1)/2-sum2);
			sum1+=t,++cnt1,vis2[t]=1;
		}
	}
	return 0;
} 
```

---

## 作者：banned_xiejiayun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6974)

### STEP 1：题意简化：


有一个大小为 $n\times n$ 的矩阵，每个位置的值为该位置的行数+列数。

接下来有 $q$ 次操作：

- $R\ m$：输出第 $m$ 行的总和并整行消去。
- $C\ m$：输出第 $m$ 列的总和并整列消去。


~~这个题目真良心，题意简洁。~~


------------

### STEP 2：思路分析：

第一反应是直接开个数组，直接模拟。但是——

$1\leqslant n\leqslant 10^6$，$1\leqslant q\leqslant 10^5$，$1\leqslant m\leqslant n$。

这么大的二维数组怎么开！

~~再度陷入苦恼……~~

但上帝为我们关一扇门时，又给我们开了一扇窗。

以下是引用：有一个大小为 $n\times n$ 的矩阵，每个位置的值为该位置的行数 $+$ 列数。

所以整个矩阵可以画成这样：

```
n=4

1+1 1+2 1+3 1+4
2+1 2+2 2+3 2+4
3+1 3+2 3+3 3+4
4+1 4+2 4+3 4+4
```

假设删除的是第 $2$ 列：

```
1+2
2+2
3+2
4+2
```
发现了吗，每一列的和就是从 $1$ 加到 $n$ 的和再加上 $n$ 倍的 $x$（第 $x$ 列）。

行也是一个道理。

但是在这之前，可能会有一些删除：

```
假设删除了 1 和 3 行：

/
2+2
/
4+2
```

这个时候答案就应该是 $(1+4)\times4\div2+2\times(4-2)-(1+3)$。

其中 $4-2$ 的 $2$ 是删除行的数量，$1+3$ 是删除的行编号之和，这个可以在删除时顺便保存。

所以，在删除一行的时候就需要：
```cpp
	cc++;
	c_sum+=x;
```
其中 $cc$ 是删除行的数量，$c$_$sum$ 即删除行（编号）之和。

在输出时就可以直接：

```cpp
	cout<<s+x*(n-cc)-c_sum;
```
其中 $s$ 就是事先算好的 $(1+n)\times n\div2$。


------------

### STEP 3：避开坑点

还记得我们开始时的顾虑吗？

$1\leqslant n\leqslant 10^6$，$1\leqslant q\leqslant 10^5$，$1\leqslant m\leqslant n$。

既然 $n$ 这么大，输出……

所以一定要加上一句：
```cpp
#define int long long
```
并且要注意标记已删除，这个用数组没问题。

## AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,x,c_sum,r_sum,cc,rr;
char ch;
bool c[1000001],r[1000001];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	const int s=(1+n)*n/2;
	while(q--){
		cin>>ch>>x;
		if(ch=='R'){
			if(r[x])cout<<0;//如果已被删除直接输出 0。
			else {
				r[x]=1;//标记已经没有了。
				cout<<s+x*(n-cc)-c_sum;
				rr++;
				r_sum+=x;
			}
		} else {
			if(c[x])cout<<0;
			else {
				c[x]=1;
				cout<<s+x*(n-rr)-r_sum;
				cc++;
				c_sum+=x;
			}
		}
		cout<<'\n';
	}
	return 0;
}
```




---

## 作者：zibenlun (赞：1)

# 分析亿下

数组需要开很大所以不能开二维数组，询问的次数很多，所以不能通过遍历去求和。

打个表可以发现在原始状态下，第 $i$ 行或列的值为：
```latex
n*i+n*(n+1)/2
```
所以每一行或列的值都是固定的，那么就只需要统计出减少的值。模拟一下可以发现，每一次行的减少，会对所有的列减少当前的行数加上这一列的列数，所以就可以用一个变量统计下所有行减少的当前行数，在统计一下一共减去了多少行，再在输出时将它乘上当前的列数。列的算法同样如此。
# 重点（代码）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,C,R,sumr,sumc,visr[1000005],visc[1000005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=q;i++) {
		char s;
		int x;
		cin>>s>>x;
		if(s=='R'){
			if(visr[x]){
				cout<<0<<'\n';
				continue;
			}
			cout<<n*(n+1+2*x)/2-sumc*x-R<<"\n";
			visr[x]=1;
			C+=x;
			sumr++;
		}
		else {
			if(visc[x]){
				cout<<"0\n";
				continue;
			}
			cout<<n*(n+1+2*x)/2-sumr*x-C<<"\n";
			visc[x]=1;
			R+=x;
			sumc++;
		}
	}
	return 0;
}

```

---

## 作者：ybc2025chenyuyang (赞：1)

# 洛谷P6974题解

## 题目大意
这道题，其实也不是很难。

简单的说，就是给出一个 $n \times n$ 的矩阵，且 $a[x][y]$ 的值为 $x+y$，每次可以查询行或列。

## 思路
每次查询的时候先输出查询的行或列的和，然后把这行或列的值全部置为 $0$ 每次查询的结果。

可以通过简单推导发现，该矩阵的每一行或者每一列都是等差数列；而由于其求出每一行或每一列的和之后，都会清零该行或列，所以可以用数组去标记即可。

然后考虑之前删除列操作的累积效果，用 $sum1$、$sum2$、$cnt1$、$cnt2$ 分别表示行的和、列的和、删去的行数、删去的列数。

那么通过对矩阵的模拟，可以推导出为

**该行总和=该行之和+该行中被清零的列数**

**该列总和=该列之和+该列中被清零的行数**

等差数列的和减去累积的影响输出即可，但要记得更新 $sum1$、$sum2$、$cnt1$、$cnt2$ 的值。

## 代码

接下来是你们最心心念念的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,sum1,sum2,cnt2,cnt1;
char op;
bool r[1000005],c[1000005];
int main(){
	cin>>n>>m;
    cnt2=n,cnt1=n;
    sum1=sum2=(1+n)*n/2;
    while(m--){
        cin>>op>>x;
        if(op=='R'){
            if(r[x]){
                puts("0");
                continue;
            }
            r[x]=true;
            sum2-=x;
            cnt2--;
            cout<<cnt1*x+sum1<<endl;
        }else{
            if(c[x]){
                puts("0");
                continue;
            }
            c[x]=true;
            sum1-=x;
            cnt1--;
            cout<<cnt2*x+sum2<<endl;
        }
    }
    return 0;
}

```


---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6974)

# 题目大意

有一个 $n \times n$ 的矩阵，每个数的值为那个数所在的行数与列数的和。

接下来给定 $q$ 个操作，对于每个操作：

- `R m`：输出第 $m$ 行的总和并删去第 $m$ 行。
- `C m`：输出第 $m$ 列的总和并删去第 $m$ 列。

# 思路

显然，若删去第 $m$ 行，对于其它行没有任何影响。删除第 $m$ 列，对其它列没有影响。

我们先只分析删除列，操作行的情况。

假设之前已经删除了 $k$ 列，列号分别为 $x_1,x_2,\dots,x_k$，要操作的行号为 $i$。

那么第 $i$ 行的初始元素和即为：
$$
\begin{aligned}    sum&=(i+1)+(i+2)+\dots+(i+n)\\    &=i \times n+1+2+3+\dots+n\\    &=i \times n+\dfrac{n \times (n+1)}{2}\end{aligned}
$$
那么很容易得到在删除了 $k$ 列后的第 $i$ 行：
$$
\begin{aligned}    ans&=i \times n+\dfrac{n \times (n+1)}{2}-(i+x_1)-(i+x_2)-\dots-(i+x_k)\\    &=i \times (n-k)+\dfrac{n \times (n+1)}{2}-x_1-x_2-\dots-x_k\end{aligned}
$$
那么，可以开两个变量 `l,ls` 分别记录已经删除了多少列（$k$）和删除的列数的总和（$x_1+x_2+\dots+x_k$），这样就可以 $\mathcal{O}(1)$ 地算出每个操作的答案了。

列也是同理，两个变量 `h,hs` 分别记录删了多少行和删除的行数的总和。

还要注意已经删过行或列却还删了一次的情况，开两个数组 `bh,bl` 分别记录。

# 代码

```cpp
#include <iostream>
using namespace std;
template<typename T=int>
inline T read(){
    T X=0; bool flag=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
    if(flag) return X;
    return ~(X-1);
}

template<typename T=int>
inline void write(T X){
    if(X<0) putchar('-'),X=~(X-1);
    T s[20],top=0;
    while(X) s[++top]=X%10,X/=10;
    if(!top) s[++top]=0;
    while(top) putchar(s[top--]+'0');
    putchar('\n');
}

typedef long long ll;
const int N=1e6+5;
ll n,q,x,h,l,hs,ls;
char c;
bool bh[N],bl[N];

int main(){
    n=read(),q=read();
    while(q--){
        cin >> c;
        x=read();
        if(c=='R'){
            if(bh[x]){
                puts("0");
                continue;
            }
            write(x*(n-ls)-l+(1+n)*n/2);
            hs++;
            h+=x;
            bh[x]=1;
        }else{
            if(bl[x]){
                puts("0");
                continue;
            }
            write(x*(n-hs)-h+(1+n)*n/2);
            ls++;
            l+=x;
            bl[x]=1;
        }
    }
    return 0;
}
```



---

## 作者：danny101 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6974)

题目大意：一个矩阵，每次查询一行或一列的和，再将其删去。

#### 大致思路如下：

既然行与列对称，我们只考虑删行即可。如果删掉了第 $i$ 行，很明显地，第 $i$ 行与第 $j$ 列只有 $(i,j)$ 一个交点，而它的值就是行号 $(i)$ 加列号 $(j)$，所以这一操作会让第 $j$ 列的元素和减少 $i+j$。

这样的话，可以展开以下推导：

我们还是只分析行。假设所有删列操作的列号分别为 $x_1,x_2,\dots,x_k$ 。

易得第 $\texttt{i}$ 行的初始元素和为

$(i+1)+(i+2)+\dots+(i+n)=(i+1+i+n)*n/2$

$\kern13.5em=i*n+n*(n+1)/2$。

那么，根据上面推导的规律, $\texttt{k}$ 次删除之后，元素和就会变为下面这个柿子：

$i*n-(i+x_1)-(i+x_2)-\dots-(i+x_k)+n*(n+1)/2$，化简得

$i*(n-k)-(x_1+x_2+\dots+x_n)+n*(n+1)/2$。

所以，我们只需要两个变量保存剩余列数 $\&$ 每次删列的索引和即可直接计算出剩余元素和了。

巴拉巴拉讲了一大堆，该 ~~跑路~~ 贴标程了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,r,l,a,b,x,sum;//l保存删列索引和，r保存删行索引和，
bool vis1[1000001],vis2[1000001];//a保存剩余列数，b保存剩余行数
char c;
int main(){
	cin>>n>>m;
	sum=(n+1)*n/2,a=b=n;
	for(int i=1;i<=m;i++){
		cin>>c>>x;
		if(c=='R'){
			if(vis1[x])cout<<0<<endl;//如果删掉了直接输出0
			else{
				vis1[x]=1;//记录这行被删了
				cout<<x*a-l+sum<<endl;//公式
				b--;
				r+=x;
			}
		}else{//同上
			if(vis2[x])cout<<0<<endl;
			else{
	        	vis2[x]=1;
				cout<<x*b-r+sum<<endl;
				a--;
				l+=x;
			}
		}
	}
    return 0;
}
```

蒟蒻的第三篇题解，求管理大大通过~

---

