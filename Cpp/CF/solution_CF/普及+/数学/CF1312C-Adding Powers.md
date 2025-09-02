# Adding Powers

## 题目描述

Suppose you are performing the following algorithm. There is an array $ v_1, v_2, \dots, v_n $ filled with zeroes at start. The following operation is applied to the array several times — at $ i $ -th step ( $ 0 $ -indexed) you can:

- either choose position $ pos $ ( $ 1 \le pos \le n $ ) and increase $ v_{pos} $ by $ k^i $ ;
- or not choose any position and skip this step.

You can choose how the algorithm would behave on each step and when to stop it. The question is: can you make array $ v $ equal to the given array $ a $ ( $ v_j = a_j $ for each $ j $ ) after some step?

## 说明/提示

In the first test case, you can stop the algorithm before the $ 0 $ -th step, or don't choose any position several times and stop the algorithm.

In the second test case, you can add $ k^0 $ to $ v_1 $ and stop the algorithm.

In the third test case, you can't make two $ 1 $ in the array $ v $ .

In the fifth test case, you can skip $ 9^0 $ and $ 9^1 $ , then add $ 9^2 $ and $ 9^3 $ to $ v_3 $ , skip $ 9^4 $ and finally, add $ 9^5 $ to $ v_2 $ .

## 样例 #1

### 输入

```
5
4 100
0 0 0 0
1 2
1
3 4
1 4 1
3 2
0 1 3
3 9
0 59049 810```

### 输出

```
YES
YES
NO
NO
YES```

# 题解

## 作者：C　C　A (赞：8)

# $CF1312C\ Adding\ Powers's\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$能否对一个数组执行任意次操作，使得其变为目标数组。

$\qquad$对于第$i$次操作，我们可以放弃，或给数组中任意一个元素加上$k^i$。

## $Solution$

$\qquad$我这题被$Hack$了！！！

$\qquad$我们考虑每个数只有可能被唯一地分解为$a[i]=q_1k^{p_1}+q_2k^{p_2}+...+q_dk^{p_d}$,相当于将$a[i]$用$k$进制表示。再考虑把所有$k$进制数加起来（不进位），如果有某一位 $>1$，那么显然是不可能得到的。

$\qquad$ 然后我来讲讲错误原因（还是有一定参考价值的，很多人都因为这个被$Skip$了，顺便吐槽下$CF$的$LJ$数据，这么明显的错误都没卡掉$QAQ$）。

$\qquad$我写代码的时候参照了转换二进制的写法，但是二进制最大数字只有$1$，可以只判定有或没有，而$k$进制最大数可能为$k-1$，所以要取余数。

## Code

### 错误代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;
const long long inf = 1e16 + 10;

long long T , n , k , cnt , a[N] , vis[N] , fac[N];

int main(){
	scanf("%lld" , &T); while(T--){
		memset(vis , 0 , sizeof(vis));
		scanf("%lld %lld" , &n , &k);
		fac[0] = 1; for(int i = 1; fac[i - 1] < inf; i++)
			fac[i] = fac[i - 1] * k , cnt = i;
		for(int i = 1; i <= n; i++) scanf("%lld" , &a[i]);
		for(int i = 1; i <= n; i++){
			for(int j = cnt; j >= 0; j--)
                if(a[i] >= fac[j])
                    a[i] -= fac[j] , vis[j]++;
		}
		bool flag = false;
		for(int i = 0; i <= cnt; i++)
			if(vis[i] > 1) flag = true;
		flag ? puts("NO") : puts("YES");
	}
	return 0;
}
```

### 正确代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;
const long long inf = 1e16 + 10;

long long T , n , k , cnt , a[N] , vis[N] , fac[N];

int main(){
	scanf("%lld" , &T); while(T--){
		memset(vis , 0 , sizeof(vis));
		scanf("%lld %lld" , &n , &k);
		fac[0] = 1; for(int i = 1; fac[i - 1] < inf; i++)
			fac[i] = fac[i - 1] * k , cnt = i;
		for(int i = 1; i <= n; i++) scanf("%lld" , &a[i]);
		for(int i = 1; i <= n; i++){
			int j = 0; while(a[i]){
				vis[j] += a[i] % k;
				a[i] /= k , j++;
			}
		}
		bool flag = false;
		for(int i = 0; i <= cnt; i++)
			if(vis[i] > 1) flag = true;
		flag ? puts("NO") : puts("YES");
	}
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：foryou_ (赞：3)

### 题意：

对于一个初始全 $0$ 的序列，问是否能够进行若干次操作（第 $i$ 次操作为对序列中任意一个元素增加 $k^i$），使得此序列变为目标数组 $a$。

---

首先，我们令需要进行操作的序列为 $b$。

我们知道，如果能通过若干次操作将 $b$ 变为 $a$，则有以下三种情形：

- $a$ 中的元素全 $0$（初始时就达成了）；

- $k=1$（此时 $k$ 的任意次方均为 $1$）；

- 满足对于所有的 $1 \le i \le n$，都有 $a_i = k^{x_1} + k^{x_2} + ... +k^{x_y}$，且 $x_1 \neq x_2 \neq ... \neq x_y$（即 $a$ 中的每个元素均可以被表示为 $k$ 的若干次幂之和，并且这些指数均不相同）。

于是，我们首先特判前两种情形，再朴素地对于 $a$ 中的某个元素去分解成若干个 $k$ 的次幂之和，判断指数是否有重复即可。时间复杂度 $O(n \log A)$，其中 $A$ 表示 $\max\{a_i\}$。

核心代码（用于将元素分解成若干个 $k$ 的次幂之和，并判断指数是否重复）：

```cpp
bool check(int x){
	while(x){
		int base=1,power=0;
		while(base<=x) base*=k,power++;
		base/=k,power--,x-=base,vis[power]++;
		if(vis[power]>1) return 0;
	}
	return 1;
}
```

---

## 作者：Refined_heart (赞：3)

题目大意：给一个初始为全$0$的序列，给定$k$，问能不能通过一些操作，把这个序列变为目标序列。**操作是第$i$次操作选择一个数加上$k^i$.**

$\text{Solution:}$

注意到题目中，一次操作只能选择一个数。又看到数据范围很小，所以我们可以暴力一点来做。

对于一个可以做到的序列，那序列中每一个数绝对能分解成$k^{p_1}+k^{p_2}+k^{p_3}+...$的形式.

观察到，对于$k=1$,无论序列如何，都是可行的。那么除了$1$之外，最小的是$2$，所以我们暴力将一个数拆成上面形式的复杂度不超过$O(\log_2 10^{16}).$复杂度显然可以过。

那考虑哪几种情况是无解的：

当序列中的数所拆分出的$k$的指数有重合，则该序列无解。

于是这个题就这么做完了。对于拆分出来的指数用数组存储次数，一旦$>1$就可以跳出输出答案了。$0$跳过即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,k,a[200010];
int mp[2000];
bool work(int x){
	while(x){
		int r=0;
		int base=1;
		while(x>=base){
			r++;base*=k;
		}
		base/=k;r--;x-=base;mp[r]++;
		if(mp[r]>1)return 0;
	}
	return 1;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
		if(k==1){puts("YES");continue;}int fg=0;
		for(int i=1;i<=n;++i){
			if(a[i]==0)continue;
			if(!work(a[i])){
				puts("NO");
				fg=1;break;
			}
		}
		if(!fg)puts("YES");
		for(int i=0;i<=200;++i)mp[i]=0;
	}
	return 0;
}
```

其余事项：别忘了清空指数记录数组，别忘了开$\text{long long.}$

---

## 作者：Clever_Jimmy (赞：1)

题意是说在 $k$ 进制下，$k^i$ 最多只能用一次，问能否凑出所有的 $a_i$。

我们将 $a$ 中所有数按 $k$ 进制分解，然后统计第 $i$ 位 $k^i$ 所用次数 $c_i$ 即可。

如果 $max\{c_i\} > 1$ 那么不可行；否则可行。

[code](https://codeforces.ml/contest/1312/submission/72810941)

---

## 作者：do_while_true (赞：1)

### 题目分析

转化题意我们很容易想到，其实就是让我们把$a_i$转化为$(k^a+k^b+k^c...)$的形式，然而对于每一个$a_i$拆出来的数，一定要满足这些a,b,c....不能重复

仔细观察 $(k^a+k^b+k^c...)$ 你想到了什么，没错，这就是k进制数的表示方法，所以我们只需要把每一个$a_i$拆分成k进制数，就能求出来a,b,c....了

所以我们只需要看$a_i$转化成k进制后的每一个k进制位就可以了

根据题意我们很容易看出如果$a_i$能被表示出来，那它的k进制位一定非0即1，所以如果$a_i$的k进制位出现了非0并且非1的数，则一定为无解情况

记得注意k=1的特殊情况


### Code:
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
ll T,n,k,kk;
ll a[31],a_k[31][1100],len_a_k[31];
//a表示原序列，a_k[i][j]表示a[i]转化为k进制时第j-1位上的数，len_a_k[i]表示a_k[i]的长度 
bool f,f2,vis[1100];
//vis代表当前位数有没有出现过 
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		if(k==1){//k=1时转化为k进制会死循环 
			f2=f=0;
			for(int i=1;i<=n;i++)
			{
				scanf("%lld",&a[i]);
				if(f&&a[i]==1) f2=1;
				if(a[i]>1) f2=1;
				if(a[i]==1) f=1;
			}
			if(f2) puts("NO");
			else puts("YES");
			continue;
		}
		for(int i=1;i<=1099;i++){//数组初始化 
			vis[i]=0;
			for(int j=1;j<=n;j++)
				a_k[j][i]=0;
		}
		f=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			len_a_k[i]=0;//初始化 
			while(a[i]>0)//转化为k进制，每一位存在a_k[i]中 
			{
				if(a[i]%k!=0&&a[i]%k!=1) f=1;
				//如果a[i]的k进制位中出现了非0或非1，即无解情况，具体说明见题解上文 
				a_k[i][++len_a_k[i]]=a[i]%k;
				a[i]/=k;
			}
		}
		if(f){
			puts("NO");//无解 
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=len_a_k[i];j++) 
			{
				if(a_k[i][j]&&vis[j]==1){//如果出现重复 则无解 
					f=1;
					break;
				}
				if(a_k[i][j]&&vis[j]==0) vis[j]=1;//标记这位已经用过了 
			}
			if(f) break;
		}
		if(f) puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：Stars_visitor_tyw (赞：1)

## CF1312C Adding Powers 题解
### 思路：
我们可以把给数组中任意一个元素加上 $k^i$ 的操作转换为将 $a_i$ 转为 $k$ 进制。如果要完成目标，那么 $a$ 数组之和转为 $k$ 进制时的每个数位都不能大于 $1$，我们可以统计并累加每一个数转为 $k$ 进制时的每一位的数，如果大于一则不能完成目标。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n, k, tmp=0, a[105], cnt[105];
signed main() 
{
    cin>>t;
    while(t--) 
	{
        bool f=1;
        cin>>n>>k;
        memset(cnt,0,sizeof(cnt));
        tmp=0;
        for(int i=1;i<=n;i++) 
		{
			int x;
            cin>>x;
            int c=0;
            while(x!=0)
            {
                cnt[c]+=x%k;
				x/=k;
				c++;
				tmp=max(tmp,c);
			}
        }
        for(long long i=0;i<tmp;i++)
        {
            if(cnt[i]>1)
            {
                f=0;
        	}
        }
        if(f==0)
        {
        	cout<<"NO\n";
		}
		else
		{
			cout<<"YES\n";
		}
    }
    return 0;
}

---

## 作者：liwenxi114514 (赞：0)

### 题意：
能否对一个数组执行任意次操作，使得其变为目标数组。
对于第 $i$ 次操作，我们可以放弃，或给数组中任意一个元素加上 $k^{i}$。
### 思路：
根据题意可知，当目标数组中的每一个数字都可以通过底数为 $k$ 的几次幂相加得到，由于一次操作只能对一个元素加上一个值，所以指数不能重复出现，又由于一次操作只能加一次，所以进制转换后的每一位上要么是 $1$ 要么是 $0$。（$0$ 特殊，他不用进行任何操作）。

就拿样例解释一下：

$3$ $9$

$0$ $59049$ $810$

$0$ 不做操作。

$59049=9^{5}$

$810=9^{2}+9^{3}$

我们只需要在第二，三，五次操作一下即可。指数分别为：$2$，$3$，$5$，没有重复，所以输出 `YES`
。
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a[35],vis[100];//不开long long见祖宗
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));//记得初始化，vis[i]记录指数i是否出现过
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		bool flag=0;//标记
		vector<int> v;//由于我们需要知道a[i]是否可以由几个底数为k的幂相加得到，所以我们可以把a[i]转化为k进制数，如果只出现了1和0，那就合法。
		for(int i=1;i<=n;i++){//循环枚举每一个数
			v.clear();//记得初始化
			while(a[i]){//进制转化
				v.push_back(a[i]%k);
				a[i]/=k;
			}
			for(int j=0;j<v.size();j++){
				if((v[j]!=1&&v[j]!=0)||(v[j]==1&&vis[j]))//如果这一位上不是1和0或者你需要在第j次操作，但是第j次已经操作过了{
					flag=1;//标记
					break;//结束循环
				}
				if(v[j]==1){//在第j次操作
					vis[j]=1;//标记
				}
			}
			if(flag){
				break;
			}
		}
		if(!flag){//输出
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;//完结撒花！！！
}
```
望审核通过！！

---

## 作者：Andrewzdm (赞：0)

# [CF1312C Adding Powers](https://www.luogu.com.cn/problem/CF1312C)
这题还是有点数学题的味道。

我们要把一个数拆成若干个 $k$ 的自然数次幂。$(k^a+k^b+k^c+\dots)$ ，于是不难想到转进制。

我们把 $a_i$ 转换成 $k$ 进制，只要有任何一位大于1，答案就是`NO`。

其次，因为我们每一步最多只能操作一个数，所以一旦某一个 $a_i$ 中的某一位是1，其它所有的 $a_j$ 的相同位上就不能是1，否则答案就是`NO`。

剩下的情况答案就是`YES`了。

代码如下：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long a[35];
int trans[35][105], cnt[35];
int n, k;

void divide(int i, long long x, int m)
{
	if(x == 0)
		return;
	trans[i][++cnt[i]] = x % m;
	divide(i, x / m, m);
	return;
}

bool judge()
{
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= cnt[i]; j++)
			if(trans[i][j] == 1)
				for(int k = 1; k <= n; k++)
					if(k != i && trans[k][j] == 1)
						return false;
	return true;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(trans, 0, sizeof(trans));
		cin >> n >> k;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			cnt[i] = 0;
			divide(i, a[i], k);
		}
		bool flag = true;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= cnt[i]; j++)
				if(trans[i][j] > 1)
				{
					flag = false;
					break;
				}
		if(!flag)
		{
			cout << "NO" << endl;
			continue;
		}
		flag = judge();
		if(!flag)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	}
	return 0;
}
```


---

## 作者：流绪 (赞：0)

给一个 k 和一个序列,问能否把一个全 0 的序列，通过多次加上 k 的幂次方后变成所给的序列，k 的每个幂次方只能使用一次，或者不用。

对于每一个数，拿出来分解出它关于 k 的幂次方的因数，并记录，看看这个因数前面有没有用过，用过的话就不行，或者分解完出现不是 k 的幂次方的因数，这样也不行。

注意开 long long，好像要自己写求幂次方的函数？我用 pow WA 了 5 发，换了快速幂就过了，哭了。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1010
#define ri register int
#define il inline
#define mod 1000000007
#define db() cout << 1 << endl
#define eps 0.000001
using namespace std;
int a[maxn],v[maxn] ;
int f(int base,int p)
{
	int ans =1;
	while(p)
	{
		if(p&1)
			ans = ans * base;
		base = base* base;
		p>>=1;
	}
	return ans;
}//快速幂
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n,k;
		cin >> n >> k;
		int flag = 1;情况是否合法的标记
		for(int i=1;i<=n;i++)
			cin >> a[i];
            
			memset(v,0,sizeof(v));//清空v数组
			for(int i=1;i<=n;i++)
			{
				if(a[i] == 0)
					continue;//0不用处理
				if(flag ==0)
					break;//已经不合法了,退出
				while(a[i])//分解a[i]
				{
					int x= 0;//记录分解出了几次方
					int p =a[i];
					while(p%k==0)//若能整除
						x++,p/=k;//分解出一个k
					if(v[x])若分解出的数用过
					{
						flag = 0;
						break;
					}
					v[x] = 1;记录没用过
					a[i] -= f(k,x);	a[i]减去分解出的数
				}	
			}
		if(flag)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
```


---

## 作者：yimuhua (赞：0)

## 题意：
问能否对一个数组执行任意次操作，使得其变为目标数组。

对于第 $i$ 次操作，我们可以给数组中任意一个元素加上 $k^i$。
## 思路：
我们知道 $a_i$ 可以被唯一的分解为 $q_1\times k^{p_1}+q_2\times k^{p_2}+\dots +q_x\times k^{p_x}$，也就等价于将 $a_i$ 转成 $k$ 进制。

若是 $a_i$ 可以变成目标，那么 $q_1,q_2\dots q_x$ 必须都 $\leq1$，$p_1,p_2\dots p_x$ 必须都不重复，也就是说 $a$ 序列之和在 $k$ 进制中的每一位都必须 $\leq 1$。

于是我们得到了正解，将每一个数分解成 $k$ 进制后有值的位计数加一，若计数大于一，则无法变为目标数组。
## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, k, tmp, a[105], cnt[105];
int main() {
    cin >> t;
    while(t--) {
        bool f = 1;
        cin >> n >> k, memset(cnt, 0, sizeof(cnt)), tmp = 0;
        for(long long i = 1, x; i <= n; i++) {
            cin >> x;
            for(long long j = 0; x;)
                cnt[j] += x % k, x /= k, tmp = max(tmp, ++j);
        }
        for(long long i = 0; i < tmp; i++)
            if(cnt[i] > 1)
                f = 0;
        cout << (f ? "YES\n" : "NO\n");
    }
    return 0;
}
```


---

