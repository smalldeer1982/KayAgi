# Rising Sand

## 题目描述

There are $ n $ piles of sand where the $ i $ -th pile has $ a_i $ blocks of sand. The $ i $ -th pile is called too tall if $ 1 < i < n $ and $ a_i > a_{i-1} + a_{i+1} $ . That is, a pile is too tall if it has more sand than its two neighbours combined. (Note that piles on the ends of the array cannot be too tall.)

You are given an integer $ k $ . An operation consists of picking $ k $ consecutive piles of sand and adding one unit of sand to them all. Formally, pick $ 1 \leq l,r \leq n $ such that $ r-l+1=k $ . Then for all $ l \leq i \leq r $ , update $ a_i \gets a_i+1 $ .

What is the maximum number of piles that can simultaneously be too tall after some (possibly zero) operations?

## 说明/提示

In the first test case, we can perform the following three operations:

- Add one unit of sand to piles $ 1 $ and $ 2 $ : $ [\color{red}{3}, \color{red}{10}, 2, 4, 1] $ .
- Add one unit of sand to piles $ 4 $ and $ 5 $ : $ [3, 10, 2, \color{red}{5}, \color{red}{2}] $ .
- Add one unit of sand to piles $ 3 $ and $ 4 $ : $ [3, 10, \color{red}{3}, \color{red}{6}, 2] $ .

 Now piles $ 2 $ and $ 4 $ are too tall, so in this case the answer is $ 2 $ . It can be shown that it is impossible to make more than $ 2 $ piles too tall.In the second test case, any operation will increase all piles by $ 1 $ unit, so the number of too tall piles will always be $ 0 $ .

In the third test case, we can increase any pile by $ 1 $ unit of sand. It can be shown that the maximum number of too tall piles is $ 1 $ .

## 样例 #1

### 输入

```
3
5 2
2 9 2 4 1
4 4
1 3 2 1
3 1
1 3 1```

### 输出

```
2
0
1```

# 题解

## 作者：MH_SLC (赞：5)

#### [题目传送门（CF）](https://codeforces.com/contest/1698/problem/B)
## 题目分析
给出一个数组 $a$，太大的数被定义为 $a_i>a_{i-1}+a_{i+1}$，再给出一个区间长度 $k$，你可以让区间长度 $k$ 的 $a_i+1$ 询问执行任意次操作止之后可以获得最大的过高的堆数。
计算答案是满足 $a_i>a_{i-1}+a_{i+1}$，当我们发现 $k≥2$ 的时候分难改变或者十分难增加答案。因此可以看出不操作是最好的。而对于 $k = 1$ 的情况，我们可以知道因为是任意次操作。

n 为奇数: $a_2>a_1+a_3,a_4>a_3+a_5,......,a_{n-1}>a_{n-2}+a_n$

n 为偶数: $a_2>a_1+a_3,a_4>a_3+a_5,......,a_{n-2}>a_{n-3}+a_{n-1}$

所以最多有 $\frac{n-2}{2}$，**不计算端点**。
## AC Code
```cpp
#include<bits/stdc++.h>	//万能头文件，听说NOIP都可以用哦~
using namespace std;
const int MAX = 1000010;
int n, k, a[MAX], cnt;
int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> k;
		cnt = 0;	//cnt不清零会WA
		for (int i = 1; i <= n; i++) cin >> a[i];	//n个数的读入
		if (k != 1) {	//k！=1的情况
			for (int i = 2 ; i < n ; i ++ )
				if (a[i] > a[i - 1] + a[i + 1]) cnt++;	//需要满足条件a[i]>a[i-1]+a[i+1]
		} else {	//k等于1的情况，按奇偶性分类
			if (n & 1) cnt = (n - 2) / 2 + 1;	//不会计算端点
			else cnt = (n - 2) / 2;
		}
		cout << cnt << endl;	//输出结果
	}
	return 0;
}
```
#### 该题解与[此处](https://blog.csdn.net/Chey_LER_SLC/article/details/125572010?spm=1001.2014.3001.5501)同时发布

---

## 作者：luogu_gza (赞：4)

题目大意
每一次操作可以对给定数组的连续 $k$ 个数加一，可以进行任意次操作。

求最终数组满足 $a_i > a_{i-1} + a_{i+1}(1 < i < n)$ 的最大个数。

那么假设我们选择了一个区间：

$a_1$ $a_2$ $a_3$ $a_4$ $a_5$ $a_6$ $a_7$ $a_8$ $a_9$ $a_{10}$

选择 $a_3,a_4,a_5,a_6,a_7$ 。
    
对于 $a_4,a_5,a_6$ ,答案只会减少，不会增加，因为如果 $a_4 \le a_3+a_5$ ,那么不可能 $(a4+1)>(a3+1)+(a5+1)$ 。

对于 $a_3,a_7$ ,答案不会变化，因为如果 $a_3 \le a_4+a_2$，那么不可能 $(a_3+1)>(a_4+1)+a2$ 。

所以答案就是原序列满足条件的最大值。

但是，在 $k = 1$ 时，我们可以构造这样的序列:

![](https://cdn.luogu.com.cn/upload/image_hosting/82uo36q7.png)

那么答案就是 $\frac{n-1}{2}$ 下取整。

完整代码：
```
#include<bits/stdc++.h>
using namespace std;
#define R read()
#define int long long
#define inf 0x3f3f3f3f
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a,b) for(int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
#define m2(a,b) memcpy(a,b,sizeof b)
namespace IO{
    inline int read()
    {
        int X=0; bool flag=1; char ch=getchar();
        while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
        while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
        if(flag) return X;
        return ~(X-1);
    }
    inline void write(int X)
    {
        if(X<0) {X=~(X-1); putchar('-');}
        if(X>9) write(X/10);
        putchar(X%10+'0');
    }
}
using namespace IO;
const int N = 2e5+10;
int t,n,k;
int a[N];
signed main(){
    t=R;
    while(t--)//多组测试数据
    {
        n=R,k=R;
        fo(i,1,n) a[i]=R;
        if(k==1)
        {
            if(n%2==0) write(n/2-1);//最后一个不算
            else write(n/2);
            puts("");
        }
        else
        {
            int ans=0;
            fo(i,2,n-1)
                if(a[i]>a[i-1]+a[i+1])
                    ans++;
            write(ans),puts("");//原序列满足条件的数量就是答案
        }
    }
    return 0;
}
```


---

## 作者：tian_jun_cheng (赞：1)

分成两种情况讨论。

## $ k = 1 $ 

当 $ k = 1 $ 的时候，我们发现最多有 $ \frac { n - 1 } { 2 } $ 个太高的数。

因为最多让相隔一个的数最高，只能是下标为 $ 2 , 4 , 6 , 8 , . . ., n - 1 $ 的数。

## $ k \ge 2 $

对于这种情况我们只需要统计原数组中太高的数。

举个例子。

$ 2 , 4 , 3 $ 。

当 $ k = 2 $ 的时候，每次将相邻的两个数 $ + 1 $ 。

可以成为如下的两种情况。

 $ 3 , 5 , 3 $ 。

 $ 2 , 5 , 4 $ 。

我们发现，无论如何都不能让$4$太高。

扩展到其他情况是一样的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		if(k==1)
			cout<<(n-1)/2<<endl;
		else
		{
			int cnt=0;
			for(int i=2;i<n;i++)
				if(a[i]>a[i-1]+a[i+1])
					cnt++;
			cout<<cnt<<endl;
		} 
	}
	return 0;
}

```


---

## 作者：Dry_ice (赞：1)

申明：已根据管理要求修改格式。

[Blog浏览](https://www.cnblogs.com/dry-ice/articles/cf1698a.html)

> cf的题目很喜欢使用分类讨论的思想。

## Analysis
这B题要分两种情况讨论。

情况一：$k=1$ 时，可累出可能最多的太高沙堆。

情况二：$k>1$ 时，操作无效，可能的太高沙堆最大值为只可能为原值。

## Proof
$k=1$ 时可以任意操作，由于题目中有最后一堆不能成为太高沙堆的限制，故答案为 $\lfloor \frac{n-1}{2} \rfloor$，注意此处 $n$ 的奇偶性被写入一式。

比如原沙堆高度为 $1$，$2$，$3$，$4$，$5$：可以分别对原高度为 $2$ 和 $4$ 的沙堆进行若干次操作，使二者成为太高沙堆。

$k>1$ 时如果想让 $a_i$ 从非太高沙堆变为太高沙堆，则相邻沙堆也会随操作增高，故太高沙堆数量不会增加即始终数量。 

## Code
```cpp
#include <stdio.h>
const int N = (int)2e5;
int n, k, a[N + 5];
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        if (k == 1) printf("%d\n", n - 1 >> 1); //k = 1的情况
        else { //k > 1的情况
            int Res = 0;
            for (int i = 2; i < n; ++i)
                Res += (a[i] > a[i - 1] + a[i + 1]);
            printf("%d\n", Res);
        }
    }
    return 0;
}
```

## The end. Thanks.

---

## 作者：hanzhang666 (赞：0)

# 分析
这道题需要分类讨论。
- 当 $k=1$ 时，我们显然可以使任何**不相邻**的数成为太高的数，所以答案为 $\lfloor \frac{n-1}{2} \rfloor$。
- 当 $k\neq1$ 时，显然会将太高的数及其相邻的数同时加 $1$，操作无效，直接输出原数列中太高的数的数量即可。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[200005];
signed main(){
	int T=read();
	while(T--){
		int n=read(),k=read();
		for(int z=1;z<=n;z++){
			a[z]=read();
		}
		if(k!=1){
			int ans=0;	
			for(int z=2;z<n;z++){
				if(a[z]>a[z-1]+a[z+1]){
					ans++;
				}
			}
			cout<<ans<<endl;
		}
		if(k==1){
			cout<<(n-1)/2<<endl;
		} 
	}
}
```


---

## 作者：Star_Ring (赞：0)

### 思路

我们知道最理想的情况是：每个数一高一矮，任取三个连续的数都至少有一个“太高的数”，这样，答案就是 $\left\lfloor\tfrac{n-1}{2}\right\rfloor$。如果 $k=1$，我们显然可以让答案变成最理想的情况，如果 $k≥2$ 呢？我们不妨来思考一下：

- 若将 $a_i$ 加 $1$，则 $a_{i-1}$ 或 $a_{i+1}$ 中至少有一项也会加 $1$，这样 $a_i$ 永远也不可能变成“太高的数”。

- 同时，若将 $a_i$ 加 $1$ 并且 $k≥3$，这样不仅 $a_{i-1}$ 或 $a_{i+1}$ 中至少有一项也会加 $1$，$a_{i-2}$ 或 $a_{i+2}$ 可能也会加 $1$，那么可能会造成原本是“太高的数”不再是“太高的数”。

所以我们得出结论：当 $k≥2$ 时，答案不但不会变优，反而可能变劣。根据结论，剩下的模拟就好。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main()
{
	int t,n,k;
	// 变量名见题意。 
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		// 平平无奇的输入 
		if(k==1){
			cout<<(n-1)/2<<endl;
			// 如果 k 等于 1，输出 (n-1)/2，整形自动向 0 取整（在这里就是向下取整）。 
		}else{
			int tot=0;
			for(int i=2;i<n;i++){
				if(a[i]>a[i-1]+a[i+1]){
					tot++;
				}
			}
			// 否则统计答案。注意 i 要从 2 开始，到 n-1 结束，防止越界。 
			cout<<tot<<endl; 
		}
	}
	return 0;
}
```


---

## 作者：nullqtr_pwp (赞：0)

# CF1698B 题解
分两类讨论：$k=1$ 与 $k\ne1$

对于第一类情况，可以任意地增加任何数字。对序列进行黑白染色，第一个是白色，让所有黑色（除了端点）的成为“过高的数”即可。容易知道答案是 $[\dfrac{n-1}{2}]$

对于第二类情况，先抛出结论：操作没用，原序列里符合要求的个数就是答案。因为对于每个操作，都无法增加“过高的数”的数量。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
void solve(){
	//do something
	int n=read(),k=read(),a[200005],ans=0;
	for(int i=1;i<=n;i++) a[i]=read();
	if(k==1){
		printf("%d\n",(n-1)>>1);
		return;
	}
	for(int i=2;i<n;i++){
		if(a[i+1]+a[i-1]<a[i]) ans++;
	}
	printf("%d\n",min(ans,(n-1)>>1));
}
int main(){
	int t=read();
	while(t--) solve();
}
```


---

## 作者：sw2022 (赞：0)

## 题意简析

定义“太大的数”为大于左右两元素之和的数。给定一个数集 $a\ (|a|=n,n>0)$ 和区间长度 $k(k>0)$，定义一次操作为任意选择一对 $l,r$（满足 $r-l+1=k$ 且 $1\le l,r\le n$），使得 $\forall i\in [l,r],a_i\leftarrow a_i+1 $。问执行任意次操作后，最多能形成多少个“太大的数”。

简单分析可知，如果将一个数和它左右两元素中的一个或两个元素都加 $1$，那么不会改变这个数是否是“太大的数”的性质。所以，当 $k>1$ 时，无论怎么选取区间进行操作，都不可能增加“太大的数”的数量，所以我们只要计算初始状况下“太大的数”的数量即可；当 $k=1$ 时，由于可以随意改变一个数的大小，所以我们只要计算出对于长度为 $n$ 的数集，最多有多少“太大的数”即可。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main()
{
    int t,n,k,s,i;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(i=1;i<=n;i++)
        cin>>a[i];
        if(k==1)
        printf("%d\n",(n-1)/2);//直接计算最大值
        else
        {
            s=0;
            for(i=2;i<n;i++)
            if(a[i]>a[i-1]+a[i+1])
            s++;printf("%d\n",s);//直接计算初始值
        }
    }
    return 0;
}
```

---

## 作者：IvanZhang2009 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1698B)

[传送门2](https://codeforces.com/contest/1698/problem/B)
## 题意
给定数组 $a$，每次可以给连续的 $k$ 个数都加上 1，求
$$(\sum^{n-1}_{i=2}[a_i>a_{i-1}+a_{i+1}])_{max}$$

即大于左右两边数的和的数的个数的最大值。
## 解法
分类讨论

首先是 $k=1$ 的情况：

我们可以将任意数任意增加。由于所有数都是正数，相邻两数不可能都满足条件，所以可以让所有下标为奇（偶）数的，不是两个端点的数都满足条件。

即让 $a_2>a_1+a_3$，$a_4>a_3+a_5$，$a_6>a_4+a_2$……$a_{n-1}>a_{n-2}+a_n$（$n$ 为奇数）或

$a_2>a_1+a_3$，$a_4>a_3+a_5$，$a_6>a_4+a_2$……$a_{n-2}>a_{n-3}+a_{n-1}$（$n$ 为偶数）。

容易得到答案为 $\lfloor\frac{n-1}{2}\rfloor$。

其次为 $k>1$ 的情况。

考虑满足条件的数的总数的变化。

如果改变区间 $[l,r]$，那么 $[0,l-2]$ 和 $[r+2,n]$ 左右的数均没有调整，对答案的贡献不变。

对于 $a_{l-1}$ 和 $a_{r+1}$ 两个数，右（左）的数会增加，而不可能使它们满足条件，对答案的贡献非正。

对于修改区间内的数，虽然本身能加 1，但是由于此时 $k>1$，其左右两边的数至少有一个会增加，导致对答案的贡献非正。这也是为什么要把 $k=1$ 和 $k>1$ 分开讨论的原因。

所以当 $k>1$ 时，显然不进行操作时答案最优，所以直接统计满足条件的数输出即可。
## 代码
```cpp
int n,k;
int a[200005];
void Main() {
	cin>>n>>k;
	REP(i,0,n)cin>>a[i];
	if(k==1){cout<<(n-1)/2<<endl;return;} //k=1时
	int ans=0;                            //k>1时
	REP(i,1,n-1)ans+=(a[i]>a[i-1]+a[i+1]);//直接统计答案
	cout<<ans<<endl;
}
```

---

## 作者：Otue (赞：0)

## 思路
简要题意：最大化 $a_i>a_{i-1}+a_{i+1}$ 的个数。

假如说选择长度为 $k$ 的区间（$k\geq2$），对这个区间进行加 $1$ 操作，其实跟不加没什么区别。

为什么？想一下，这样操作至少使得长度为 $2$ 的区间加上 $1$，那么不就等于 $(a_i+1)>a_{i-1}+(a_{i+1}+1)$ 吗？这跟原来不等式完全一样，所以操作之后跟没操作是一样的效果。

故 $k>1$ 时不需要操作，直接输出原数组的答案即可。
	
$k=1$ 的时候间隔间隔着加数，答案为 $\dfrac{n-1}{2}$。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int t, n, k, a[N];

int main() {
	cin  >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) cin >> a[i];
		if (k == 1) {
			cout << (n - 1) / 2 << endl;
		}
		else {  //k > 1
			int res = 0;
			for (int i = 1; i <= n; i++) {
				if (i != 1 && i != n && a[i] > a[i - 1] + a[i + 1]) {
					res++;
				}
			}  //原数组计算答案
			cout << res << endl;
		}
	} 
}
```

---

