# [ABC167D] Teleporter

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc167/tasks/abc167_d

高橋王国には $ N $ 個の町があります。町は $ 1 $ から $ N $ まで番号が振られています。

それぞれの町にはテレポーターが $ 1 $ 台ずつ設置されています。町 $ i\ (1\ \leq\ i\ \leq\ N) $ のテレポーターの転送先は町 $ A_i $ です。

高橋王は正の整数 $ K $ が好きです。わがままな高橋王は、町 $ 1 $ から出発してテレポーターをちょうど $ K $ 回使うと、どの町に到着するかが知りたいです。

高橋王のために、これを求めるプログラムを作成してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\ \leq\ K\ \leq\ 10^{18} $

### Sample Explanation 1

町 $ 1 $ から出発してテレポーターを $ 5 $ 回使うと、$ 1\ \to\ 3\ \to\ 4\ \to\ 1\ \to\ 3\ \to\ 4 $ と移動します。

## 样例 #1

### 输入

```
4 5
3 2 4 1```

### 输出

```
4```

## 样例 #2

### 输入

```
6 727202214173249351
6 5 2 5 3 2```

### 输出

```
2```

# 题解

## 作者：iiiiiiiiiiiiiiiiiii (赞：19)

因为 $K$ 很大，所以纯暴力会寄掉。

容易证明经过城镇的序列循环节长度不超过 $n$：若循环节长度超过 $n$，则一个循环节中经过一个城镇两次或以上，则下一个城镇也一样。这样一直推下去就会得到一个矛盾的结果。

从 $1$ 一直走下去，记录**每一次到达的城镇**和**每个城镇最后一次到达时间**。如果访问到一个之前走过的城镇，算出周期 $d$。设 $b_i$ 为传送 $i$ 次到达的城镇，则易得 $b_i=b_{i+d}=b_{i+2d}=\cdots=b_{i+jd}$（$j$ 为正整数）。

之后如果传送了 $x$ 次，满足 $x\equiv K(\bmod\space d)$，则 $b_x=b_K$，输出 $b_x$ 即可。

- 如果 $K$ 比较小，没出现循环节时就走了 $K$ 次，则可以直接输出 $b_K$。

代码如下，比较简洁：

```cpp
const int N=4e5+10;
int n,m,a[N],vis[N],b[N],len,d;
void solve()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=0,j=1;;i++,j=a[j])
	{
		if(i==m||d&&i%d==m%d)
			write(j),exit(0);
		if(vis[j])
			d=i-vis[j];
		vis[j]=i,b[len++]=j;
	}
}


```

---

## 作者：PineappleSummer (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc167_d)

倍增例题，但是怎么没人写倍增题解啊？

设 $f_{i,j}$ 表示从 第 $i$ 个城镇传送 $2^j$ 次所到达的城镇，于是可以得出转移：$f[i][j]=f[f[i][j-1]][j-1]$。这个转移什么意思呢，就是说从第 $i$ 个城镇传送 $2^j$ 次到达的城镇为从第 $i$ 个城镇传送 $2^{j-1}$ 次所到达的城镇再传送 $2^{j-1}$ 次所到达的城镇，好好理解一下。

转移代码：
```cpp
for(int j=1;j<=65;j++)//j必须放在外层循环
	for(int i=1;i<=n;i++)
		f[i][j]=f[f[i][j-1]][j-1];
```

然后再来看一下对 $k$ 次传送的处理。

考虑对 $k$ 进行二进制拆分。比如传送 $7$ 次，$7$ 的二进制数为 $111$，所以 $7$ 的二进制拆分为：$7=2^2+2^1+2^0$。结合刚才对 $f$ 数组的倍增处理，我们只需要将从第 $1$ 个城镇依次传送 $2^2$ 次、$2^1$ 次、$2^0$ 即可。总的来说，就是对 $k$ 进行二进制拆分，然后用处理好的 $f$ 数组依次跳即可。

代码:
```cpp
while(k)//k不为0
{
	if(k%2)	now=f[now][t];//k在二进制下的这一位上是1，所以要进行传送
	k/=2;
	t++;//位数加1
}
```
最后输出 $now$ 就行了。

[完整代码](https://atcoder.jp/contests/abc167/submissions/44142455)

---

## 作者：Kobe_BeanBryant (赞：2)

### 题目大意：
![](https://cdn.luogu.com.cn/upload/image_hosting/30ydxef0.png)
### 思路推导：
当我们读完题目后第一反应应该就是暴力模拟来推导，但是我们先看看数据范围。
![](https://cdn.luogu.com.cn/upload/image_hosting/7wnotk5h.png)

我相信当看到 $ k $ 的数据范围后，都放弃了暴枚的想法。

那我们该如何快速的完成这道题呢，详情请看**方法**。

### 方法：
我们前面说过暴力枚举是不行的，那么我们就应该去找一下这道题的周期，通俗一点就是找规律。

当我们找出规律后代码长度也可以大大的缩短，而我所找到的规律也就是本题的核心代码。

**规律：**

1. 首先我们先定义一个变量用来存储答案和一个变量 $ q $ 来统计次数。
2. 然后我们循环 $ k $ 次，每一次都将答案赋值为 $ a $ 数组对应的元素。
3. 判断，如果当 $ b $ 数组中对应的变量为 $ 0 $ 时，$ k $ 就模等于 $ q $ 与其的差。
4. 输出存储答案的变量，结束。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
long long ans=1,q;
long long a[200005],b[200005];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	while(k--){
		ans=a[ans];
		if(b[ans]!=0)
			k%=q-b[ans];
		b[ans]=q++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：flysfy_LJX (赞：2)

由题目可轻易的知道我们要找**循环节**来做出本题。

只需要把国王每次来到的地方标记一下，等再次来到有标记的地方就找到了循环节，随后根据循环节输出即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ans=1,step,a[202020],vis[202020];
int main()
{
	cin >> n >> k;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	while(k--)
	{
  		ans=a[ans];
		if(vis[ans]) k%=step-vis[ans];//找到了循环节
    	vis[ans]=step;
    	step++;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：YuTianQwQ (赞：1)

# 题目解析

这段代码的目标是处理一个含有 $n$ 个元素的整数序列，根据一定的规则，重复操作 $k$ 次后，确定操作结束时位于序列哪个位置。

## 解题思路

1. **读取输入**：首先，我们读取输入的整数 $n$ 和 $k$ ，以及整数序列 `a`。我们需要对序列的每个元素减一，以适应从 0 开始的索引。

    ```cpp
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) 
    {
        cin >> a[i];
        a[i]--;
    }
    ```

2. **初始化变量**：我们使用一个变量 `t` 来记录当前位置，以及一个数组 `vis` 来记录每个位置第一次被访问的次序。

    ```cpp
    vector<int> vis(n, -1);
    int t = 0;
    vis[t] = 0;
    ```

3. **进行操作**：我们按照规则进行操作。如果在某次操作后，当前位置已经被访问过，则表示找到了循环。此时，我们可以计算出循环的周期 `p`，以及还需进行的操作次数 `r`，然后快速进行 `r` 次操作。如果在进行 $k$ 次操作后还没有找到循环，则直接输出当前位置。

    ```cpp
    for(int i = 1; i <= k; i++)
    {
        t = a[t];
        if(vis[t] != -1)
        {
            int p = i - vis[t];
            int r = (k - i) % p;
            for(int j = 0; j < r; j++) 
                t = a[t];
            break;
        }
        vis[t] = i;
    }
    ```

4. **输出结果**：完成所有操作后，输出最终的位置，注意输出时要加一，以适应从 1 开始的索引。

    ```cpp
    cout << t + 1;
    ```

总的来说，这段代码通过模拟操作的过程，并在发现循环时利用循环的性质进行优化，找出重复操作 $k$ 次后位于序列的哪个位置。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) 
    {
        cin >> a[i];
        a[i]--;
    }
    vector<int> vis(n, -1);
    int t = 0;
    vis[t] = 0;
    for(int i = 1; i <= k; i++)
    {
        t = a[t];
        if(vis[t] != -1)
        {
            int p = i - vis[t];
            int r = (k - i) % p;
            for(int j = 0; j < r; j++) 
                t = a[t];
            break;
        }
        vis[t] = i;
    }
    cout << t + 1;
    return 0;
}


---

## 作者：nbtngnllmd (赞：1)

## 题意：

已知有 $n$ 台电视，每台电视都有一个转发地址 $a_i$，给出一个正整数 $k$，问从城市 $1$ 开始进行 $k$ 次操作后会到达哪个城市。

## 分析：

首先看数据范围：$ 1 \le k \le 10^{18}$，直接模拟和暴力枚举肯定是不可以的，我们需要寻找规律。

已知电视信号转发操作经过不断的操作后，会进入一个循环，例如样例 $2$ 中，通过直接演算，我们可以推出转发过程：$1$ 到 $6$ 到 $2$ 到 $5$ 到 $3$ 到 $2$ ……

因此我们可以得知，无论 $k$ 多大，经过一定次数的操作后，操作过程会进入循环，这是所有的操作都是固定的，因此我们没有必要直接枚举很多次，只需要判断循环前的操作次数与进入循环后对循环轮数进行取模即可。

我们用首先开一个桶 $sum$ 来记录每个 $i$ 出现的次数，用数组 $f$ 来模拟整个循环过程，如果 $i$ 出现次数为 $0$ 就丢入桶里，反之直接跳出循环。


------------

```cpp
int l = w[1];
	f[1] = w[1];
	sum[w[1]]++;
	while(true) {
	    sum[w[l]]++;
		if(sum[w[l]] > 1) {b = w[l];break;}
		else{
		    f[++r] = w[l],l = w[l];
	    }
	}
```


------------

其次进行分情况讨论：

首先如果 $k$ 小于等于第一次循环次数，直接输出 $f[k]$ 即可，反之循环找出出现第二次的 $i$ 出现在第一次的位置，跳出循环，然后进行取模即可。


------------
```cpp
ll m,c;
        for(int i = 1 ; i <= r ; i++ ) {
	    	if(f[i] == b) {
	    		c = i ;break;
		    }
	    }
	    ll p = 0;
	    for(int i = c ; i <= r ; i++ ) ff[++p] = f[i]; 
        m = (k - r) % (r - c + 1);
        if ( m == 0) cout << ff[p] << endl;
        else cout << ff[m ] << endl; 
```


------------
最后奉上参考代码：

## $ACcode$

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
int n;
int f[5000010],ff[5000010];
ll k,r = 1,b;
int w[5000010],sum[5000010];
int main(){
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++i ) cin >> w[i];
	int l = w[1];
	f[1] = w[1];
	sum[w[1]]++;
	while(true) {
	    sum[w[l]]++;
		if(sum[w[l]] > 1) {b = w[l];break;}
		else{
		    f[++r] = w[l],l = w[l];
	    }
	}
//	for(int i = 1 ; i <= r ; i++ ) cout << f[i] <<' ';
	if(k <= r) cout << f[k] << endl;
    else {
    	ll m,c;
        for(int i = 1 ; i <= r ; i++ ) {
	    	if(f[i] == b) {
	    		c = i ;break;
		    }
	    }
	    ll p = 0;
	    for(int i = c ; i <= r ; i++ ) ff[++p] = f[i]; 
        m = (k - r) % (r - c + 1);
        if ( m == 0) cout << ff[p] << endl;
        else cout << ff[m ] << endl; 
	}
	return 0;
}
```




---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实并不复杂，因为每一个点都只能到固定的下一个点，所以必定在其中会出现环，这样我们就可以找到循环节，从而找到相应数的位置了。~~一道大大的水题呢。~~

在此我们还可以进行一个小小的优化，就是把标记数组原来用来标记的 $0$ 与 $1$ 变化成扫到这个数时的位置，从而找到循环节时就可以少一重算循环个数的循环，可以有效的减低时间复杂度。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],vis[200001];
int main()
{
	long long k;
	int n,sum=1;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int i;
	for(i=1;k>0;)
	{
		i=a[i];
		k--;//跳动一次找节点 
		if(vis[i]!=0) k=k%(sum-vis[i]);//找到循环的节点，从而快速到位，否则会超时 
    	vis[i]=sum;//记录当前的次数
    	sum++;
	}
	cout<<i;
	return 0;
}
```


---

## 作者：small_john (赞：0)

## 思路

看一眼就知道是找周期。

隆重介绍周期新找法：**龟兔赛跑法**。

我们知道，周期有时候是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/isl70mda.png)

而不是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/cn016ez5.png)

也就是说，周期不一定会回到开始，有可能会从中间开始循环，如果真有这样的数据，普通的周期就会超时。龟兔赛跑法就是解决前者的方法，步骤如下：

1. 有两个数 $s1,s2$ 都为 $1$（即开始），每次，$s1$ 走一步，$s2$ 走两步，当 $s1$ 和 $s2$ 相等时，那就是周期的起始点；

2. 如果 $k$ 还有值，那么就进入计算周期长度的部分。设 $zq=1$（周期长度），$s1$ 先走一步，再继续走直到 $s1=s2$。算完后 $k$ 对 $zq$ 取余数；

3. $s1$ 一步一步走直到 $k=0$，最后输出 $s1$。

由于最多只有 $n$ 种情况，所以只需要 $n$ 次扫一遍即可，时间复杂度为 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
const int N = 2e5+5;
int n,k,a[N],s1,s2;
signed main()
{
	cin>>n>>k;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	for(s1 = s2 = 1;k;k--)//确定周期开始点
	{
		s1 = a[s1],s2 = a[a[s2]];//s1走一步，s2走两步
		if(s1==s2)
		{
			k--;
			break;
		}
	}
	if(k)//计算周期长度
	{
		int zq = 1;
		for(s1 = a[s1]/*先走一步*/;s1!=s2;s1 = a[s1])
			zq++;
		k%=zq;
	}
	for(;k;k--)
		s1 = a[s1];
	cout<<s1;
	return 0;
}
```



---

## 作者：kkxacj (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_abc167_d)


#### 题目大意

高桥王国有 $N$ 个城镇，编号从 $1 \sim N$。

在 $i$ 号城镇能到达的城镇为 $A_i$，国王高桥想知道他从第 $1$ 号城镇出发，走 $K$ 次可以到达的位置。

#### 思路

注意到 $K \le 10^{18}$，所以肯定不能直接暴力求解，由于每个城镇只连接一个城镇，所以至多循环 $N$ 次，一定会出现循环节，如样例 $1$：
![](https://cdn.luogu.com.cn/upload/image_hosting/vddxl6u2.png)

答案明显为 $4$，但注意，循环节不一定是固定的，如第二个样例:

![](https://cdn.luogu.com.cn/upload/image_hosting/wxrp27mu.png)

所以我们需要把不是循环节的删除掉，但有可能 $K$ 很小，不在循环节里，所以当 $K$ 很小时需要暴力算。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[500010],v[500010],o,t[1000010],l,he,kk,jntm,tt[1000010],pp;
long long k;
int main()
{	
	cin >> n >> k;
	l = 1;
	for(int i = 1;i <= n;i++) cin >> a[i];
	if(k <= 1e7)//如果k很小直接暴力 
	{
		for(int i = 1;i <= k;i++) l = a[l];
		cout << l << endl;
		return 0;
	}
	for(int i = 1;i <= n * 2;i++) 
	{
		if(v[l])//如果找到循环节 
		{
			he = v[l];//头 
			kk = i - 1;//尾 
			break;
		}
		v[l] = i;
		l = a[l],t[++o] = l;
	}
	for(int i = he;i <= kk;i++) tt[++pp] = t[i];//删除不是循环节的 
	printf("%lld",tt[(k - he) % pp + 1]);//由于前he个不是循环节，所以删除它 
	return 0;
}
```


---

## 作者：liangbowen (赞：0)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc167_d)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17154708.html)

两篇题解的代码写得很复杂，我是没有想到。

## 思路

很显然对于一个点，它必定会进入一个循环节。

如何判断它进入循环节了呢？当**一个点被经过两次**，就意味着已经有环了。

假设第一次进入的时候是 $i$，第二次是 $j$，循环节长度是 $j - i$。

当然进入环之前，可能有一部分不是环，所以 $k \gets \Big [ \small (k - (i - 1)) \bmod (j - i) \Big ]$。

然后题解又去统计循环的内容。这显然没有必要啊，直接暴力跑就完事了！

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int a[N], dfn[N];
int main()
{
	int n; ll k;
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int u = 1;
	for (ll i = 1; i <= k; i++)
	{
		if (dfn[u]) //循环节找到了 
		{
			k = (k - (i - 1)) % (i - dfn[u]);
			while (k--) u = a[u];
			cout << u;
			return 0;
		}
		dfn[u] = i, u = a[u];
	}
	cout << u;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：WOERDESUGX (赞：0)

本蒟蒻又来发题解了。

----------------------

### 题意：

已知有 $n$ 个整数。
每个下标下都有一个整数，每次操作后都会转移到下标为该整数的位置，求出经过 $k$ 次操作后会在哪个位置。

### 思路：

第一眼看到这道题：不要管直接暴力枚举。你会交上这样一份代码。

```cpp
cin >> n >> k ;
for(int i = 1 ; i <= n ; ++i ) cin >> a[i];
now = 1;
while(k) {
    k--;
    now = a[now];
}
cout << now << endl;
return 0;
```

毫无疑问，这样会超时地飞起了。所以还是老老实实的想正解吧。

看一下样例 $1$ 的解释：从 $1$ 到 $3$ 到 $4$ 到 $1$ 到 $3$ 到 $4$。 

发现规律了吗，从第 $4$ 次开始操作过程就会陷入一个循环，这个循环永远不会变，
我们可以看看样例 $2$：从 $1$ 到 $6$ 到 $2$ 到 $5$ 到 $3$ 到 $2$ 到 $5$ 到 $3$，又是一个循环，因此我们得知因为 $n$ 的范围很小，所以程序会进行很多次无用的循环这时候我们只需要找出循环来取模求出是第几步循环即可。

我们可以用 $vis$ 代表每个下标是否出现过，如果出现过直接跳出循环即可。然后找出循环。如果要求的次数大于没有循环的次数对循环层数进行取模即可。

------------------

### ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200050],vis[200050],now=0,K,vs[200050],mark,l=0;
long long k;
int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		if(a[i]==i) now++;
	}
	long long kk=k;
	now=0;
	K=a[1];
	while(!vs[K]) {
		vs[K]=1;
		vis[++now]=K;
		K=a[K];
		mark=K;
	}
	if(k<=now) {
		cout<<vis[k]<<endl;
		return 0;
	}	
	memset(vs,0,sizeof(vs));
	for(int i=1;i<=now;++i) {
		if(vis[i]==mark) break;
		l++;
	}
	int num=0;
	for(int i=l+1;i<=now;++i) vs[++num]=vis[i];
	kk-=now;
	if(kk%num==0) cout<<vs[num]<<endl;
	else printf("%d\n",vs[kk%num]);
}
```

---------------------

注：感谢@nbtngnllmd的倾力帮助，给我调了将近两个小时~~不要问问就是太蒟了~~

---

## 作者：Mu_leaf (赞：0)

## [思路]
很明显的找循环节的模板题目。

这里给出几个需要注意的坑点：


------------


- 循环节不一定从 1 开始，也就是说，找到循环节后要从循环节的起点开始。
- 在寻找循环节的时候，如果此时已经超出了 $k$ 直接输出即可，不然就和我一样 $k$ 成为负数。
- 关于时间复杂度的话：由于在第 $i$ 个城市通往第 $A_i$ 给城市，那么这个循环节的长度**一定**不会超过 $n$。

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n,k;
int a[N],vis[N],ind,pre,sum;
int ans=1;
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> a[i];
	ind=1;
	while(vis[ind]<2){
		if(!vis[ind]) pre++;
		else{
			sum++;	
			if(sum==1) ans=ind;
		}
		if(pre>k){
			cout << ind << "\n";
			return 0;
		}
		vis[ind]++;
		ind=a[ind];
	}//这里循环 2 次是为了防止出现循环节的起点不在 1 的情况。
	pre-=sum;
	k=(k-pre)%sum;
	while(k--) ans=a[ans];
	cout << ans;
	return 0;//完结撒花！
}

```



---

