# 「Diligent-OI R1 B」DlgtArray

## 题目描述

现给定一个长为 $n$ 的序列 $a_1\sim a_n$，其中 $a_i\in\{0,1\}$。

$q$ 次询问，每次给定 $l,r,k$，要你更改一些位置上的数值（只能改为 $0$ 或 $1$）使得 $\sum\limits_{i=l}^ra_i=k+\prod\limits_{i=l}^ra_i$。也就是说要让 $a_l\sim a_r$ 的和要恰好等于 $a_l\sim a_r$ 的乘积再加上 $k$。你需要求出最少的修改次数。如果无解，输出 $-1$。

**请注意每次的更改不会对后续询问产生影响。**

## 说明/提示

#### 样例 #1 解释

$a=\{0,0,1,0,1\}$。

第一个询问只需将 $a_1$ 或 $a_2$ 改为 $1$。此时和为 $2$，积为 $0$。

第二个询问只需将 $a_3$ 改为 $0$。此时和为 $0$，积为 $0$。

第三个询问不需进行更改，和为 $2$，积为 $0$。

第四个询问，因为只有一个数，所以和与积相等，所以不可能做到。

#### 数据范围

对于 $100\%$ 数据，$1\le n,q\le10^6$，$0\le k\le10^6$，$1\le l\le r\le n$，$a_i\in\{0,1\}$。

| Subtask 编号 | $n,q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $10$ | 无 | $10$ |
| $1$ | $10^3$ | A | $7$ |
| $2$ | $10^3$ | BC | $7$ |
| $3$ | $10^3$ | B | $13$ |
| $4$ | $10^3$ | C | $13$ |
| $5$ | $10^3$ | 无 | $20$ |
| $6$ | $10^5$ | B | $9$ |
| $7$ | $10^5$ | C | $9$ |
| $8$ | $10^6$ | 无 | $12$ |

特殊性质 A：$k=n$。

特殊性质 B：$\forall 1\le i\le n,a_i=0$。

特殊性质 C：$k=0$。

## 样例 #1

### 输入

```
5 4
0 0 1 0 1
1 3 2
2 4 0
3 5 2
1 1 1```

### 输出

```
1
1
0 
-1```

## 样例 #2

### 输入

```
8 3
1 1 1 1 1 1 1 1
2 6 2
5 8 2
1 8 7```

### 输出

```
3
2
0```

# 题解

## 作者：easy42 (赞：5)

特判的点较多，要注意。

首先，不难想到用前缀和来维护区间和。

其次的点：

1. 如果只有一个数且 $$k$$ 是大于零的，输出无解。

2. 如果只有一个数且 $$k$$ 是等于零的，无需操作。

3. 如果 $$k$$ 比区间长还大，输出无解。

4. 如果已经满足条件，无需操作。

5. 最后在判一下乘积，再直接搞即可。

具体见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[10000005],b[10000005];//b是前缀和
int l,r,k;
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		b[i]=a[i]+b[i-1];
	}
	while(q--){
		cin>>r>>l>>k;
		if(l-r==0&&k!=0){
			cout<<-1<<endl;
			continue;
		}
		if(l-r==0&&k==0){
			cout<<0<<endl;
			continue;
		}
		if(k>l-r){
			cout<<-1<<endl;
			continue;
		}
		int xans=b[l]-b[r-1];
		int xch;
		if(xans-(l-r+1)==0){//乘积
			xch=1;
		}
		else{
			xch=0;
		}
		if(xans==xch+k){
			cout<<0<<endl;
			continue;
		}
		if(xch==0){
			int minn;
			minn=abs(k-xans);
			cout<<minn<<endl;
		}
		if(xch==1){
			cout<<abs(k-xans)<<endl;
		}
	}
    return 0;
}
```

---

## 作者：yanxu_cn (赞：4)

## 做法
显然分讨 $\prod_{i=l}^{r}a_i$。

* 若全为 $1$。则 $r-l+1=\sum_{i=l}^{r}a_i=k+1$。显然可以特判。
* 若不全为 $1$。此时 $\sum_{i=l}^{r}a_i=k$。

显然有结论：
* 若 $k>r-l$，无解。
* 若 $k=r-l$，显然有两种方案：或是全为 $1$，或是只有 $1$ 个 $0$。如果本身序列中存在 $0$ 则第二种划算，否则第一种划算。
* 若 $k<r-l$。显然就是要有 $k$ 个 $1$。我们直接求 $\sum_{i=l}^{r}a_i$，并与 $k$ 作差求绝对值即可。由于要加快区间求和，所以可以用前缀和。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000007];
inline int abs(int&x)
{
    return x>=0?x:-x;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,q,l,r,k,cnt;
	cin>>n>>q;
	for(int i=0;i<n;i++)
	{
		cin>>l;
		a[i+1]=l+a[i];
	}
	for(int i=0;i<q;i++)
	{
		cin>>l>>r>>k;
		if(r-l<k)
		{
			cout<<"-1\n";
		}
		else
		{
			cnt=a[r]-a[l-1];
			if(cnt==r-l+1&&k==r-l)
			{
				cout<<"0\n";
			}
			else
			{
				cout<<abs(cnt-k)<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：AkihabaraQ (赞：3)

# P11272 「Diligent-OI R1 B」DlgtArray
[题目传送门](https://www.luogu.com.cn/problem/P11272)\
[或许更好的阅读体验](https://www.luogu.com.cn/article/m7jlbyzy)


---

### 提示：本篇题解较为详细，需要看结论和代码的请跳到最后。


---

## 一、题意概括
给定长度为 $n$ 的 $01$ 序列 $a$，对于 $q$ 次询问，给定 $l$，$r$，$k$，欲求出**最小的**修改（$0$ 变 $1$，$1$ 变 $0$）次数，使得从 $a_l$ 到 $a_r$ 的**加和**恰好等于 $a_l$ 到 $a_r$ 的**乘积**再加上 $k$。无解则输出 $-1$ 。（**注：每次更改不会对后续询问产生影响**）。\
公式化的：
$$
\sum\limits_{i=l}^ra_i= \prod\limits_{i=l}^ra_i+k
$$


---


## 二、前置知识
**前缀和**：对于给定的数列 $A$，其**前缀和**数列 $S$ 是可以通过**递推**求出的基本信息（复杂度：$O(n)$）：
$$
S_i=\sum\limits_{j=1}^iA_j
$$
对于数列 $A$ 中某个区间 $[l,r]$ 的**区间和**，可以表示成**前缀和相减**的形式：
$$
sum(l,r)=\sum\limits_{i=l}^rA_i=S_r-S_{l-1}
$$


---


## 三、题目分析
对于一个数列的**区间和**，可以通过 $O(n)$ 预处理出其**前缀和**再用前缀和**相减**的方式 $O(1)$ 求出。对于**区间积**，考虑到给定序列 $a$ 为 $01$ 序列，故其任意区间的区间积**只有** $0$ 和 $1$ **两种取值**（$0$ 乘**任何数**都得 $0$）。所以**不必**进行累计乘法，可以根据每个**区间**的**性质**进行分类讨论求解。


---


## 四、解题步骤
先读入序列 $a$，同时预处理出其**前缀和**，对于每次询问，我们根据**区间积取值**的两种情况分类讨论区间性质：
1. **区间积**为 $0$：说明这段区间内的数**不全为** $0$，那么对于 $k$，我们只需求出这段区间内 $1$ 的**数量** $_{[1]}$，并计算其与 $k$ 相减的**绝对值**，即为答案（大于 $k$ 就把部分 $1$ 该成 $0$，小于 $k$ 就把部分 $0$ 该成 $1$）。

2. **区间积**为 $1$：说明这段区间内的数**全为** $1$（或者在操作中全部**被改成**了 $1$），那么此时**区间和**等于 $k+1$ 才能满足题目要求 $_{[2]}$。

3. 对于上述两种情况的**每一个** $k$，都应满足设区间的**长度**为 $len$，则有 $k\leq len$ $_{[3]}$（否则无论如何改变，即使把该区间内的**所有数**都改为 $1$，也**无法**满足题目要求）。

**注**：$[1]$ 因为 $a$ 为 $01$ 序列（**仅由** $0$ 和 $1$ 组成），所以任意区间内 $1$ 的**数量**等于**区间和**，故可以通过**前缀和**求出。

$[2]$ **特殊地**：区间**全为** $1$ 时，对于 $k$ 和区间**长度** $len$，若 $k+1=len$，则**无需更改**就能满足题目要求（即输出 $0$ 的情况）。

$[3]$ 考虑区间内**全部**为 $1$ 的情况，此时**区间积**为 $1$（**不要忘记**考虑），**区间和**为区间长度 $len$ 若要满足题意，则有：$k+1=len$。所以当：$k>len$ 时该区间问题**无解**（即 $k$ 需**满足**：$k\leq len$）。


---


## 五、代码实现
**注意**：**使用流输入等较慢的读取方式会导致两个测试点运行超时**。\
建议使用以下**任意**一种读入方式读取数据：
1. 关闭同步流：
```cpp
#include<iostream>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
    int n;
    cin>>n;
	return 0;
}
```
2. 使用输入函数：
```cpp
#include<cstdio>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	return 0;
}
```
3. 使用快读：

```cpp
#include<cstdio>
using namespace std;
inline int Get(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9'){c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x;
}
int main(){
	int n;
	n=Get();
	return 0;
}
```


---


  
啰嗦了这么多，来看**完整版代码**qwq。
```cpp
#include<iostream>
#include<cmath> 
using namespace std;
const int maxn = 1e6+5;
int n, q;
int a[maxn], s[maxn];    //分别为原数组和前缀和数组 
int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		s[i] = s[i-1] + a[i];    //计算前缀和 
	}
	for(int i = 1; i <= q; i++){
		int l, r, k, len, sum;
		scanf("%d %d %d", &l, &r, &k);
		len = r - l + 1;    //计算区间长度 
		sum = s[r] - s[l-1];    //计算区间和(1的数量) 
		if(k + 1 > len) printf("-1\n");    //无解情况判断 
		else if(sum == len && k + 1 == len) printf("0\n");    //正好不用更改的情况 
		else printf("%d\n", abs(sum - k));    //其他情况则输出需要更改的次数 
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11272)

### 思路

首先我们可以轻松发现区间积是 $0$ 或 $1$。

那么分开处理：

- 如果区间积是 $0$，那说明我们要让 $\sum_{i = l}^{r} a_i = k$，那么输出它与 $k$ 的绝对值即可，另外因为 $\sum_{i = l}^{r} a_i$ 最大为 $r-l+1$，此时它要等于 $k+1$，所以 $r-l$ 大于 $k$ 时无解。

- 如果区间积为 $1$，那说明我们要让 $\sum_{i = l}^{r} a_i = k+1$，那么和就是 $r-l+1$，如果它不为 $k+1$ 那么同区间积为 $0$ 的情况。

注意要用前缀和优化。

然后就做完了。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[1000005],s[1000005],l,r,k;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];
    }
    while(q--)
    {
        scanf("%d%d%d",&l,&r,&k);
        if(s[r]-s[l-1]==r-l+1)//区间积为1
        {
           if(k>r-l)  printf("-1\n");//特判
           else  if(r-l+1==k+1)  printf("0\n");//可以
		   else  printf("%d\n",abs(r-l+1-k));//否则输绝对值 
        }
        else//区间积为0
        {
        	if(k>r-l)  printf("-1\n");//特判
			else  printf("%d\n",abs(s[r]-s[l-1]-k));//注意要绝对值 
        }
    }
    return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：2)

~~没想到水题还没关题解通道。~~

题意简述，给定一个长度为 $n$ 的零一序列，$q$ 次询问，每次询问给定 $l,r,k$，求使该序列 $l$ 到 $r$ 的区间和等于区间积加 $k$ 的最少次数。无解输出 $-1$。

思路：

另一序列那么区间积只能是零或一，区间和初始值也可以用前缀和求出来，所以只要分类讨论即可。

当区间积为零时，区间和为 $k$，所以如果 $k$ 大于区间长度则无解，否则，设区间和为 $a$，答案为 $|a-k|$。

当区间积为一时，区间和为 $k-1$ 且区间内没有 $0$，所以如果 $k$ 不等于区间长度减一则无解，否则将区间内所有数都改为 $1$，设区间和为 $a$，答案为 $k-a$，可以与第一种情况合在一起。

最后将两种情况的答案比大小。如果两种情况都无解输出 $-1$。

代码：
```
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int a[1000000],n,q;signed main(){
	IOS;cin>>n>>q;for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];//输入加求前缀和
	for(int i=1,l,r,k;i<=q;i++){
		cin>>l>>r>>k;
		cout<<(k>r-l?-1:a[r]-a[l-1]==r-l+1&&k==r-l?0:abs(a[r]-a[l-1]-k))<<endl;//分类讨论
	}return 0;
}
```

---

## 作者：Cosine_Func (赞：1)

考虑使用前缀和维护初始序列。若区间和与区间长度相同，则区间积为 $1$，否则为 $0$。

分类讨论以下三种情况：
- $k>r-l$ 时，无解；
- $\sum_{i=l}^{r}=r-l+1$ 且 $r-l=k$ 时，无需修改区间；
- 否则输出 $\sum_{i=l}^{r}-k$ 的绝对值。

很容易解释这一做法。

参考代码：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define endl '\n'
#define itn int
#define pi pair<int,int>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
const int MOD1=1e9+7;
const int MOD2=998244353;
const int N=1e6+5;
int n,q,l,r,k,a[N],s[N];
inline void Solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i],s[i]=s[i-1]+a[i];
	while(q--){
		cin>>l>>r>>k;
		if(k>r-l)cout<<-1<<endl;
		else if(s[r]-s[l-1]==r-l+1 and k==r-l)cout<<0<<endl;
		else cout<<abs(s[r]-s[l-1]-k)<<endl;
	}
}
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=1;
    //cin>>T;
    while(T--)
    	Solve();
    return 0;
}
```

---

## 作者：DDD_et (赞：1)

# P11272 Solution

**做法：找规律，推公式，分类讨论，打表**

## 题意

给定一个长度为 $n$ 的 $0/1$ 序列 $a_1 \dots a_n$；每次询问给定 $l,r,k$，一次操作可以将 $[l,r]$ 范围内的一个值修改为 $0/1$，问最少需要几次操作使得 $\sum \limits_{i=l}^r a_i=k+ \prod \limits_{i=l}^r a_i$，无解输出 `-1`（更改不会对后续询问产生影响）。

## 思路

这题吧……挺需要分类讨论水平的（个人意见）。

我的分类讨论思路是：分两种情况，一种是将 $[l,r]$ 范围内元素全部改为 $1$ 的情况，另一种是这其中有 $0$ 的情况（因为 $a_{[l,r]}$ 全部为 $1$ 时 $\prod \limits_{i=l}^r a_i=1$，有 $0$ 时则为 $0$，所以就是根据 $[l,r]$ 中所有元素的乘积分类讨论的）。

约定：下面我们用 $S$ 表示 $a_{[l,r]}$ 中所有元素的和，用 $M$ 表示 $a_{[l,r]}$ 中所有元素的积，用 $c_x$ 表示 $a_{[l,r]}$ 中元素 $x$ 的出现次数（元素总个数即为 $r-l+1=c_0+c_1$，并且发现 $S=c_1$）。

首先求出题目给的 $a$ 数组的前缀和，$a_{[1,i]}$ 中所有元素的和记作 $prm_i$，则当前 $S=c_1=prm_r-prm_{l-1}$。

- 当 $M=1$ 时，也就是将范围内全部改为 $1$ 的情况。此时必须要总元素数刚好为 $k+M=k+1$，这样就需要 $c_0$ 次修改将所有 $0$ 改为 $1$；否则的话就将此答案设为极大值。
  
- 当 $M=0$ 时，也就是 $a_{[l,r]}$ 中有 $0$ 的情况，这时我们只需要修改 $|c_1-k|$ 次，将 $1$ 的个数控制在 $k$ 个（多了就减少，少了就加，所以取绝对值）。

最后取两种方法的较小值即可。

不过要注意特判，当 $k$ 的值**大于等于**此时总元素个数时，此时无论怎么修改都无法达成条件，输出 `-1`。

**注意：输入数据较大，可以直接使用函数读入优化。**

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, q, sum[N];
bool sta[N];

int main ()
{
	ios :: sync_with_stdio (0);
	cin.tie (0); //读入优化
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) cin >> sta[i];
    for (int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + sta[i];
    //sum即为前缀和数组
    while (q --)
    {
        int l, r, k; cin >> l >> r >> k;
        int c1 = sum[r] - sum[l - 1], cnt = r - l + 1, c0 = cnt - c1;
        //cnt就是总元素个数
        int S = c1, M = !c0;
        //M(乘积)其实跟0的个数相关，只有0的个数为0时M才为1，否则为0
		if (k >= cnt) cout << "-1\n";
		else
		{
            //全部为1的情况
            int a1 = (cnt == k + 1 ? c0 : 0x3f3f3f3f);
            //有0的情况
			int a2 = abs (S - k);
            //取最小值
			cout << min (a1, a2) << '\n';
		}
    }
    return 0;
}
```

### 写在最后

（其实本来“写在最后”是没写的，现在补上了，麻烦管理重申谢谢♪(･ω･)ﾉ）

**谢谢观看！**

---

## 作者：_dbq_ (赞：0)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/P11272)

知识点：前缀和。

## 思路
我们可以想到对于区间和可以使用前缀和来完成，因此定义 $sum_i=\sum_{j=1}^i a_j$。

由于 $a_i\in\{0,1\}$，所以 $a_l\sim a_r$ 的乘积为零或一。因此，我们分为两种情况讨论。

首先，当不用修改就满足要求的特判，答案为零。

当乘积为零时，如果 $k>l-r$，无解。此外，又分为三种情况：

- 全部改成一
- 增加一的数量
- 减少一的数量

全部改成一，则答案为 $r-l+1-sum_r+sum_{l-1}$；增加一的数量，则答案为 $k-sum_r+sum_{l-1}$；减少一的数量，则答案为 $sum_r-sum_{l-1}-k$。

当乘积为一时，无解的情况如上，其余答案为 $sum_r-sum_{l-1}-k$。

最后将所有的结果取最小值，输出即可。

## 代码

```cpp
/* 2024-11-15-22:44 by _dbq_ */
#include<iostream>
#include<algorithm>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
cint N=1e6+10;
int a[N],sum[N];//sum是前缀和
inline LL read(){
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve()
{
    int n=read(),q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        sum[i]=sum[i-1]+a[i];//前缀和
    }
    while(q--){
        int l=read(),r=read(),k=read();
        int ans=1e9;
        if(k+(sum[r]-sum[l-1]==r-l+1)==sum[r]-sum[l-1])//不用修改的情况
            ans=0;
        if(sum[r]-sum[l-1]==r-l+1){//乘积为一
            if(k<=r-l)//k>r-l时无解
                ans=min(ans,sum[r]-sum[l-1]-k);
        }
        else{
            /*
            r-l+1是有多少个数
            sum[r]-sum[l-1]是当前有多少个一
            k是需要多少个一
            */
            if(k+1==r-l+1)//1是乘积，满足所有数为一的情况
                ans=min(ans,r-l+1-(sum[r]-sum[l-1]));
            if(k<=r-l&&sum[r]-sum[l-1]<k)//注意k>r-l无解且需要增加一
                ans=min(ans,k-(sum[r]-sum[l-1]));
            if(sum[r]-sum[l-1]>k)//减少一的情况
                ans=min(ans,sum[r]-sum[l-1]-k);
        }
        cout<<(ans==1e9?-1:ans)<<'\n';//1e9的时候就是无解
    }
    return ;
}
int main()
{
    #ifdef dbq
    freopen("P11272.in","r",stdin);
    freopen("P11272.out","w",stdout);
    #endif
    solve();
    return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
用 ``one``、``zero`` 两个数组存贮前 $i$ 个数字的 $0$ 和 $1$ 的个数。输入完之后现特判，若 $l=r$ 且 $k=0$，直接输出 $0$。因为无论如何，一个数的积永远等于其和，否则输出无解。特判完之后，根据 $a_l$ 到 $a_r$ 的积进行分类讨论即可。

### 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[1000005], zero[1000005], one[1000005];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		if(a[i] == 0){
			zero[i] = zero[i - 1] + 1;
			one[i] = one[i - 1];
		}
		else{
			zero[i] = zero[i - 1];
			one[i] = one[i - 1] + 1;
		}
	}
	while(q--){
		int l, r, k;
		cin >> l >> r >> k;
		if(l == r && k != 0){
			cout << -1 << endl;
			continue;
		}
		else if(l == r && k == 0){
			cout << 0 << endl;
			continue;
		}
		int num_zero = zero[r] - zero[l - 1];
		int num_one = one[r] - one[l - 1];
		if(k == (r - l)){
			if(k >= num_one){
				cout << min((r - l + 1) - num_one, k - num_one) << endl;
				continue;
			}
			cout << (r - l + 1) - num_one << endl;
		}
		else if(k < (r - l)){
			if(k > num_one){
				cout << k - num_one << endl;
			}
			else if(k == num_one){
				cout << 0 << endl;
			}
			else{
				cout << num_one - k << endl;
			}
		}
		else{
			cout << -1 << endl;
		}
	}
	return 0;
} 
```

---

## 作者：许多 (赞：0)

很好玩的一道题。

不难发现一段区间如果有一个 $0$ 那么这一段的乘积也是 $0$，所以我们要分开讨论，即讨论区间全都是 $1$ 和有 $0$ 两种情况。

我们设 $d=r-l+1$，即这段区间长度。当区间全都是 $1$ 的时候显然 $k=d-1$；当区间有 $0$ 时，$k=\sum_{i=l}^{r} a_i$，即这段区间 $1$ 的个数，显然 $k$ 此时最大也只能取到 $d-1$。

那么我们就有策略了，当 $k>d-1$ 时无解；当 $k=d-1$ 时对上述两种构造方案求最小值；当 $k<d-1$ 时在这段区间构造 $k$ 个 $1$。

原序列中区间 $1$ 的个数可以用前缀和维护。

详细见代码。

## code

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 1111111
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n,q,pre[N];
int main(){
    n=read();q=read();
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+read();
    while(q--){
        int l=read(),r=read(),k=read();
        int d=r-l+1,cnt=pre[r]-pre[l-1];//cnt是这段原区间 1 的个数
        if(k==d-1){
            printf("%d\n",min(d-cnt,abs(k-cnt)));
            continue;
        }
        if(k>=d){
            printf("-1\n");
            continue;
        }
        printf("%d\n",abs(k-cnt));
    }
    return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P11272)
# 思路
定义：之后我们用 $s$ 表示 $a_{[l,r]}$ 中所有元素的和，用 $a$ 表示 $a_{[l,r]}$ 中所有元素的积。$cnt_0$ 表示 $a_{[l,r]}$ 中 $0$ 出现的个数，$cnt_1$ 表示 $a_{[l,r]}$ 中 $1$ 出现的个数。
## 普通思路
首先我们要求出前缀和，$a_{[l,r]}$ 中所有元素的和就为 $sum_{r} - sum_{l-1}$（即 $s = cnt_1 = sum_{r} - sum_{l-1}$）。

随后我们有两种情况：

- 当 $a=1$ 时，现在需要判断 $k$ 是否等于 $cnt-1$。如果是，那么答案是 $cnt_0$，否则就是极大值。
- 当 $a=0$ 时，我们只需要将 $cnt_1$ 变为 $k$ 即可，即答案是 $cnt_1-k$ 的绝对值。

最后将两个答案取最小值即可。
## 特判
当 $k \ge r-l+1$ 时，输出 $-1$。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+6;
int sum[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,q;
	cin >>n>>q;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin >>x;
		sum[i]=sum[i-1]+x;
	}
	while(q--)
	{
		int l,r,k;
		cin >>l>>r>>k;
		int cnt=r-l+1;
		int s=sum[r]-sum[l-1];
		int a=(s==cnt ? 1 : 0);
		int cnt1=s;
		int cnt0=cnt-s;
		if(k>=cnt) cout <<-1<<'\n';
		else
		{
			int ans1=(cnt==k+1 ? cnt0 : INT_MAX);
			int ans2=abs(cnt1-k);
			cout <<min(ans1,ans2)<<'\n';
		}
	}
	return 0;
}

```
最后的最后，求管理员大人通过。

---

