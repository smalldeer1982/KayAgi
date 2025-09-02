# Strongly Composite

## 题目描述

A prime number is an integer greater than $ 1 $ , which has exactly two divisors. For example, $ 7 $ is a prime, since it has two divisors $ \{1, 7\} $ . A composite number is an integer greater than $ 1 $ , which has more than two different divisors.

Note that the integer $ 1 $ is neither prime nor composite.

Let's look at some composite number $ v $ . It has several divisors: some divisors are prime, others are composite themselves. If the number of prime divisors of $ v $ is less or equal to the number of composite divisors, let's name $ v $ as strongly composite.

For example, number $ 12 $ has $ 6 $ divisors: $ \{1, 2, 3, 4, 6, 12\} $ , two divisors $ 2 $ and $ 3 $ are prime, while three divisors $ 4 $ , $ 6 $ and $ 12 $ are composite. So, $ 12 $ is strongly composite. Other examples of strongly composite numbers are $ 4 $ , $ 8 $ , $ 9 $ , $ 16 $ and so on.

On the other side, divisors of $ 15 $ are $ \{1, 3, 5, 15\} $ : $ 3 $ and $ 5 $ are prime, $ 15 $ is composite. So, $ 15 $ is not a strongly composite. Other examples are: $ 2 $ , $ 3 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 10 $ and so on.

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ a_i > 1 $ ). You have to build an array $ b_1, b_2, \dots, b_k $ such that following conditions are satisfied:

- Product of all elements of array $ a $ is equal to product of all elements of array $ b $ : $ a_1 \cdot a_2 \cdot \ldots \cdot a_n = b_1 \cdot b_2 \cdot \ldots \cdot b_k $ ;
- All elements of array $ b $ are integers greater than $ 1 $ and strongly composite;
- The size $ k $ of array $ b $ is the maximum possible.

Find the size $ k $ of array $ b $ , or report, that there is no array $ b $ satisfying the conditions.

## 说明/提示

In the first test case, we can get array $ b = [18] $ : $ a_1 \cdot a_2 = 18 = b_1 $ ; $ 18 $ is strongly composite number.

In the second test case, we can get array $ b = [60] $ : $ a_1 \cdot a_2 \cdot a_3 = 60 = b_1 $ ; $ 60 $ is strongly composite number.

In the third test case, there is no array $ b $ satisfying the conditions.

In the fourth test case, we can get array $ b = [4, 105] $ : $ a_1 \cdot a_2 \cdot a_3 = 420 = b_1 \cdot b_2 $ ; $ 4 $ and $ 105 $ are strongly composite numbers.

## 样例 #1

### 输入

```
8
2
3 6
3
3 4 5
2
2 3
3
3 10 14
2
25 30
1
1080
9
3 3 3 5 5 5 7 7 7
20
12 15 2 2 2 2 2 3 3 3 17 21 21 21 30 6 6 33 31 39```

### 输出

```
1
1
0
2
2
3
4
15```

# 题解

## 作者：Otue (赞：4)

容易想到，把一串 $a$ 的乘积拆成一串 $b$ 的乘积，则把数组 $a$ 所有数拆成一些质数，并分配给数组 $b$，且每个数 $b_i$ 尽量使用最少的质数。

我们怎样使用 **最少量的质数** 构成强合数：

* 一个数若含有两个相同质数，那么这个数绝对为强合数。所以我们先使用相同的两个质数来构成强合数。

* 一个数若含有三个不同的质数，那么这个数绝对为强合数。所以我们后使用三个不同的质数来构成强合数。

* 若以上两个条件下质数不够时，剩余的质数怎么办？无关紧要，直接扔到之前已经构成的强合数里面就行。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int T, n;
map<int, int> vis;

void slove(int x) {  // 分解质因数
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            for (; x % i == 0; x /= i) vis[i]++;
        }
    }
    if (x > 1) vis[x]++;
}

int main() {
    cin >> T;
    while (T--) {
        vis.clear(); 
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            slove(x);
        }
        int res = 0, cnt = 0;
        for (auto i = vis.begin(); i != vis.end(); i++) {
            int t = i -> second;
            res += t / 2; // 两个相同质数
            cnt += t % 2;
        }
        cout << res + cnt / 3 << endl; // 三个不同质数
    }
}
```
## 思考
最开始看到这道题你会很懵，但事实上绝大部分的数均为强合数。只需要满足一下条件：
* 含有两个及以上相同质数。

* 含有三个及以上不同的质数。

---

## 作者：One_JuRuo (赞：2)

## 思路

我们可以思考一下什么样子的合数是强合数。

首先一个数可以表示为 $p_1^{c_1}\times p_2^{c_2}\times \cdots \times p_x^{c_x}$。

那么这个数的约数个数为 $s=(c_1+1)\times (c_2+1)\times \cdots \times (c_x+1)$。那么，我们可以根据 $s$ 初步排除一部分强合数：

- 若 $s=1$，则原数是 $1$，不可能为强合数。

- 若 $s=2$，则原数是质数，不可能为强合数。

所以如果 $s\le2$，则该数不可能为强合数。

再令质数的个数为 $x$，则合数的个数为 $s-x-1$。

所以只要 $x\le s-x-1\Rightarrow 2\times x\le s-1$，这个数就是强合数。

若一个数是强合数，我们考虑给它乘以若干个互不相同且之前没出现过的质数，假设质数的数量为 $k$。

那么只要 $2\times(x+k)\le s\times 2^k -1$ 乘以这些质数后就还是强合数。

即需要证明 $2\times k\le s\times (2^k-1)$。

因为原数是强合数，所以 $s\ge 3$。

易知，$k=1$ 时，一定满足条件，因为左侧是线性增长，右侧是指数增长，所以后续右侧一定会越来越比左侧大。

所以强合数乘以若干个互不相同且不是原数的质因数的质数，无论乘以多少个，它还是强合数。

再思考，如果乘以了已经存在过的质数，那么质数因数不会变，合数因数会变多，所以还是强合数。

综合一下，就是强合数乘以任意正整数后还是强合数。

再来思考，至少存在几个质因数可以成为强合数。

首先是只有一种质因数，如果只有一个，那原数就是质数，不可能为强合数；如果超过一个，那就是上面的 $s=2$ 的情况，是强合数。

然后是至少有几个不同的质因数，令有 $x$ 个不同的质因数，那么共有 $2^x$ 个因数，有 $2^x-x-1$ 个合数因数。

如果原数是强合数，那么 $x\le 2^x-x+1$ 即 $2^x-2\times x-1\ge 0$，发现当且仅当 $x\ge 3$ 时，原数是强合数。

因为一个强合数乘以任意一个正整数后还是强合数，所以只要这个数有一个质因数的个数大于等于 $2$ 或者有至少 $3$ 个质因数时是强合数。

因为前一种所需的最少质因数比后一种所需的最少质因数还要少，所以我们尽量先多造前一种强合数，再造后一种强合数

现在给定了 $a_i$ 就代表 $\prod_{i}^n a_i$ 是定值，然后对其进行质因数分解。对于所有的质因数，令其个数为 $cnt$，如果 $cnt>1$，那么这些质因子可以造出 $\lfloor \frac{cnt}2\rfloor$ 个强合数，如果 $cnt$ 是奇数，那么就会剩下一个质因数。

剩下的质因数可以三个一对造强合数，剩下的质因数就随便乘给任意数即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int shu[10000005],pri[10000005],minp[10000005],cnt;
int T,n,a,b[10000005],num,siz;
map<int,int>m;
inline void init()//提前线性筛预处理每个数的最小质因数
{
	for(int i=2;i<=10000000;++i)
	{
		if(!shu[i]) pri[++cnt]=i,minp[i]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=10000000;++j)
		{
			minp[pri[j]*i]=pri[j],shu[pri[j]*i]=1;
			if(i%pri[j]==0) break;
		}
	}
}
inline void calc(int x)//除以最小质因数，较为快速地分解质因数
{
	while(minp[x]>1) ++m[minp[x]],x/=minp[x];
	if(x>1) ++m[x];
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),m.clear(),cnt=siz=0;
		for(int i=1;i<=n;++i) scanf("%d",&a),calc(a);//乘起来在质因数分解，和每个数质因数分解，再把相同质数的指数相加是等效的，并且乘起来会导致数太多，线性筛没法预处理那么多，还可能会爆unsigned long long导致没有类型可以存
		for(auto i:m)//遍历所有的质因数
		{
			cnt+=i.second/2;
			if(i.second%2) ++siz;//统计剩下的质因数个数
		}
		cnt+=siz/3;
		printf("%d\n",cnt);
	}
}
```

---

## 作者：yanwh1 (赞：2)

# 题目大意
给你一个长度为 $n$ 的序列 $a$，要求你需要构造出长度为 $k$ 的序列 $b$，我们需要使序列 $b$ 每个数为强合数（强合数满足它的质因子个数小于等于它的合数因子个数），且 $\prod_{i=1}^{n}a_i\le\prod_{i=1}^{n}b_i$。问 $k$ 最大能为多少。
# 思路讲解
我们求出序列 $a$ 的质因数个数后，可以发现：

- 两个相同的质数相乘必定为强合数。
- 三个不同的质数相乘必定为强合数。

因为我们需要 $k$ 最大，所以我们只需统计每个质数的个数除以二，剩余的质数个数再除以三即可。

但我们发现一个问题：如果做完以上操作还有剩余的怎么办呢？其实我们不用管。因为剩余的质数个数必定小于三个，凑不成强合数，且我们易证得：一个强合数乘上任意一个质数，其乘积必为强合数，所以我们可以直接将这些质数乘上处理过的强合数即可，不会影响答案。

代码实现
```
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(long long x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int M=1e7+5,Q=1e6+5;
unordered_map<int,int>vis;
int s[Q],tot;
signed main(){
	int T=read();
	while(T--){
		int n=read();
		for(rint i=1;i<=n;i++){
			int x=read(),num=2;
			while(x>1){
				if(num>x/num){
					if(!vis[x])
						vis[x]=++tot;
					s[vis[x]]++;
					break;
				}while(x%num==0){
					if(!vis[num])
						vis[num]=++tot;
					s[vis[num]]++;x/=num;
				}num++;
			}
		}int ans=0,sum=0;
		for(rint i=1;i<=tot;i++)
			ans+=s[i]/2,sum+=s[i]%2,s[i]=0;
		ans+=sum/3;
		write(ans),puts("");
		tot=0;
		vis.clear();
	}
	return 0;
}
```

---

## 作者：yanbinmu (赞：1)

# Strongly Composite题解

## 题目

称一个数 $n$ 为**强和数**，当 $n$ 的约数中质数的个数小于等于合数的个数。

给定一个序列 $a$ ，构造一个序列 $b$ 使得:

1. 两序列乘积相同
2. 任意一个 $b_i$ 都是强和数。

3. $b$ 数组的大小 $k$ 在满足上述条件的前提下要尽可能的大。

## 分析

考虑对于一个强和数，需要满足什么特性。

根据算术基本定理，对于任意一个数 $n$ 都可以分解为以下形式：
$$
n=p_1^{a_1}p_2^{a_2}……p_k^{a_k}
$$
而这个数的因数个数就是：
$$
t=(a_1+1)(a_2+1)……(a_k+1)
$$

### 简证

因为 $p_i$ 都是质数，无法再进行因式分解，所以任意 $p_i$ 的组合都可以构成一个约数，

对于质数 $p_i$ 有 $(a_i+1)$ 种可能的取法，分别是取 $0,1,2……a_i$ 个，

那么对于 $k$ 个 $p_i$ 共有 $(a_1+1)(a_2+1)……(a_k+1)$ 种可能的组合。

既然如此，我们就可以得知和数因数的个数，为 $t - k$ 个。

需要 $k \leq t-k$，即 $2k \leq t$。

所以我们可以得到几个推论：

1. 质数的平方是强和数
2. 三个以上不同质数的乘积是强和数

而由此我们就可以写出代码了（要求 $b$ 的长度最大，所以应用最少的质数来构成强和数）

## Code

```C++
#include <bits/stdc++.h>
using namespace std;
int x;
vector<int> prime;
unordered_map<int, int> p;
int vis[10000005];
void get(int n){
    if(vis[n] == 0){
        p[n] ++ ;
        return ;
    } 
    for(int i = 2;i * i <= n;i ++ ){
        if(n % i == 0 && vis[i] == 0){
            while(n % i == 0){
                n /= i;
                p[i] ++ ;
            }
        }
    }
    if(n != 1) p[n] ++ ;
}
void Eular(int n){
    for(int i = 2;i <= n;i ++ ){
        if(!vis[i]) prime.push_back(i);
        for(auto j : prime){
            if(i * j > n) break;
            vis[i * j] = 1;
            if(i % j == 0) break;
        }
    }
}
int main(){
    int T;
    scanf("%d", &T);
    Eular(1e7);
    while(T -- ){
        int n, k;
        scanf("%d", &n);
        for(int i = 1;i <= n;i ++ ){
            scanf("%d", &x);
            get(x);
        }
        int ans = 0;
        int cnt = 0;
        for(auto &i : p){
            ans += i.second / 2;//有多少个两个一组的
            cnt += i.second % 2;//拿完两个一组的还剩不剩
        }
        printf("%d\n", ans + cnt / 3);//两个的加上三个的
        p.clear();
    }
    return 0;
}
```

---

## 作者：rmzls (赞：1)

### 思路
很显然，我们要把所有的 $a_i$ 乘在一起，得到的数我们设成 $A$，则 $A$ 的质因子是所有 $a_i$ 的质因子之和。
我们考虑将任意一个数 $k$ 用他的质因子表示出来：$k=\prod\limits_{i=1}^n p_i^{c_i}$，其中 $n$ 是 $k$ 的质因子种数（这里先与个数区分，个数即为每种质因子有多少个，求和，即 $\sum\limits_{i=1}^n(n\times c_i)$），$c_i$ 是第 $i$ 个质因子的数量。  
我们将 $k$ 的所有因子拆解出来，其中我们可以发现：  
1. 质因子的个数即为 $n$；  
1. 合因子的个数即为 $(\prod\limits_{i=1}^n{(c_i+1)}-n-1)$（即所有因子的个数减去质因子个数再减去 $1$，$c_i-1$ 就是枚举第 $i$ 个质数选几个，从 $0$ 到 $c_i$）；

当这个数 $k$ 是强合数，那么 $n\leqslant(\prod\limits_{i=1}^n{(c_i+1)})-n-1$。  
我们这时候将 $k$ 分为两种情况，推出两个结论：  
1. 质因子种数小于等于 $2$，即 $n\leqslant2$，那么必然有一个 $c_i\ge2$（可以用反证法证明）。  
1. 质因子种数大于 $2$，即 $n>2$，或者说 $n\ge3$，那么等式必然成立。

那我们回归到题目，我们可以把题目转化为：  
**将 $A$ 分成若干个数的乘积，使得每个数都是强合数，并且使分成的数个数尽量多。**  
很显然，这些数质因子乘起来是等于 $A$ 的质因子个数的，那我们可以直接看成将 $A$ 的质因子分配到若干个数中。  
我们先将 $A$ 质因数分解，再考虑分配。既然想要得到最多的数，那么每个数分配到的质因数要尽可能的小。通过上面两个结论，我们可以得出：分出的一个数最优方案是**一个质数的平方，即 $p^2$（结论 $1$），或三个不同的质数相乘，即 $p_1p_2p_3$，$p_1\neq p_2\neq p_3$（结论 $2$）**，也可以使用反证法证明。  
这样我们枚举 $A$ 的每个质因子个数 $p_i$，将其全部按照第一种方式分出，若有一个多余的（即 $c_i$ 为奇数），则将其与其他有多余一个的质数以第二种方式分出。  
参照代码：
```cpp
for(int i=1;i<=cnt;i++){
	if(yins[i]){
		ans+=yins[i]/2;
		if(yins[i]&1){//判断是否是奇数
			ew++;//ew即为分剩下的单个质数的个数
		}
	}
	yins[i]=0;//多测清零
}
ans+=(ew/3);
```  
------------
### 代码
这里的质因数分解运用了 $\log$ 级别的拆解算法，具体可以去看[B3716](https://www.luogu.com.cn/problem/B3716)。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,M=1e7+100;
int prime[M],vis[M],cnt,n,t,a[N],yins[M],pl[M],ans,ew;
void getp(int up){
    for(int i=2;i<=up;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            pl[i]=cnt;
        }
        for(int j=1;j<=cnt;j++){
            if(i*prime[j]>up){
                break;
            }
            vis[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
}
void fenj(int k){
    while(k){
    	if(vis[k]){
    		yins[pl[vis[k]]]++;
    		k/=vis[k];
		}
    	else{
    		yins[pl[k]]++;
    		return ;
		}
	}
}
signed main(){
    getp(M-10);
    scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++){
    		scanf("%d",&a[i]);
    		fenj(a[i]);
		}
		for(int i=1;i<=cnt;i++){
			if(yins[i]){
          		ans+=yins[i]/2;
          		if(yins[i]&1){
          			ew++;
				}
        	}
        	yins[i]=0;
		}
		ans+=(ew/3);
		printf("%d\n",ans);
		ans=ew=0;
	}
    return 0;
} 
```


---

## 作者：浮光掠影 (赞：0)

### 题意

构造 $b$ 数组，元素乘积等于 $a$ 数组元素乘积，且所有元素都要是“强合数”，求 $b$ 数组长度 $k$ 的最大值。

### 题目分析

看看样例，想一个数怎样才能成为强合数。

发现三个不同质数的乘积或者一个质数的平方一定是一个强合数。为了让数组更长，优先选择质数的平方。于是就可以把 $a$ 数组的乘积进行质因数分解，然后去除每个质数的平方，最后三个三个组合就行。

但是，直接乘起来会爆掉，**所以碰到一个 $a_i$ 就分解。**

### 重要处理

在线性筛的时候记录每个数的最小质因子，**分解质因数的时候就从最小质因子开始，直接可以跳到每个数的质因子**，不用一个个枚举。

---

## 作者：kkxacj (赞：0)

#### 前言

赛时没打出来，糖丸了。

#### 思路

将部分强合数分解一下，可以发现一些性质。

1. **由两个相同质数相乘的数一定是强合数**，因为这样质数只有一个，合数有两个，所以一定是。

2.**由三个不同质数相乘的数一定是强合数**，因为这样乘出来质数个数小于等于合数个数，所以一定可行。

3.**强合数乘上任意的数还是强合数**，因为本来就满足条件，乘了后合数个数一定会 $\times 2$，而质数可能只会 $+1$，所以一定满足。

所以答案就是每个相同质数的个数除二加上剩下的不同质数的个除三就行了，多余的数可以乘进前面的强合数里，不用管。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 1e7;
int n,sum,sum1,o1,o2,ans,bj,l,st[N+10],cnt,st1[N+10],cnt1,t,a[1000010],v1[N+10],v2[N+10];
bool v[N+10];
signed main()
{
	v[1] = 1;
	for(int i = 2;i <= N;i++)
	{
		if(!v[i]) st1[++cnt1] = i,v2[i] = cnt1;
		for(int j = 1;j <= cnt1;j++)
		{
			if(i*st1[j] > N) break;
			v[i*st1[j]] = 1;
			if(i%st1[j] == 0) break;
		}
	}
	read(t);
	while(t--)
	{
		read(n);
		for(int i = 1;i <= n;i++) read(a[i]);
		ans = o2 = 0;
		for(int j = 1;j <= cnt1;j++) v1[j] = 0; 
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= cnt1 && a[i] >= st1[j];j++)
			{
				while(a[i] % st1[j] == 0) v1[j]++,a[i] /= st1[j];
				if(!v[a[i]])
				{
					v1[v2[a[i]]]++;
					break;
				}
			}
		for(int j = 1;j <= cnt1;j++) ans += v1[j]/2,o2 += v1[j]%2;
		print(ans+o2/3),pc('\n');
	}
	flush();
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## CF1823C Strongly Composite 题解

### 思路分析

显然的，对于任意质数 $x$，$x^2$ 只有质因数 $x$ 与合因数 $x^2$，为强合数。

同样的，对于任意三个两两不同的质数 $x, y, z$，$xyz$ 有质因数 $x, y, z$ 与合因数 $xy, xz, yz, xyz$，亦为强合数。

对于 $n$ 个数全部分解质因数，对于每一个质因数，优先按方案一组合。

否则，将剩下的质因数按方案二组合。

对于剩下的质数，随便放入某个强合数中。

对于总共只有不到两个质数的情况，打印 $\texttt{-1}$ 即可。

对于分解质因数，本文使用 $\sqrt{x}$ 的做法。（以及少量优化）

### 代码实现

```cpp
#include <cmath>
#include <cstdio>
#include <map>
constexpr int MaxN = 1e5 + 5;
constexpr int Limit = 1e7 + 5;
int n;
bool f[Limit];
std::map<int, int> map;
void init(int limit = 1e7)
{
    f[1] = true;
    for (int i = 2; i <= limit; i++)
    {
        if (f[i])
        {
            continue;
        }
        for (int j = 2 * i; j <= limit; j += i)
        {
            f[j] = true;
        }
    }
}
void solve()
{
    map.clear();
    scanf("%d", &n);
    int k = 0;
    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        if (x == 1)
        {
            continue;
        }
        if (!f[x])
        {
            s++;
            map[x]++;
            if (map[x] >= 2)
            {
                s -= 2;
                map[x] -= 2;
                k++;
            }
            continue;
        }
        int l = std::sqrt(x) + 1;
        for (int i = 2; i <= l; i++)
        {
            for (; x % i == 0;)
            {
                x /= i;
                s++;
                map[i]++;
                if (map[i] >= 2)
                {
                    s -= 2;
                    map[i] -= 2;
                    k++;
                }
            }
            if (x == 1)
            {
                break;
            }
            if (!f[x])
            {
                s++;
                map[x]++;
                if (map[x] >= 2)
                {
                    s -= 2;
                    map[x] -= 2;
                    k++;
                }
                break;
            }
        }
    }
    if (s < 3 && k == 0)
    {
        printf("%d\n", 0);
    }
    else
    {
        printf("%d\n", k + s / 3);
    }
}
int main()
{
    init();
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：dlzlj_2010 (赞：0)

首先让我们来证明几个结论：
1. **一个强合数乘以一个数一定还是一个强合数。**  
证明：  
乘上一个质数后，只会多一个质数，但会多若干合数，所以依然是强合数。  
而乘上一个合数后，无疑会多出更多的合数，所以依然是强合数。
2. **有两个相同质因子的数一定为强合数。**  
证明：  
记这个质数为 $p$，则该数在除去其他多余因数后，因数为 $\{1,p,p^2\}$，因为 $p^2$ 一定是合数，所以质数与合数数量相等，为强合数。  
3. **有三个不同质因子的数一定是强合数。**  
证明：  
记这三个质数为 $p_1,p_2,p_3$，则这个数在除去其他因子后，因数为 $\{p_1,p_2,p_3,p_1\cdot p_2,p_1\cdot p_3,p_2\cdot p_3,p_1\cdot p_2\cdot p_3\}$，质数明显比合数少，所以为强合数。

那么我们直接对每个数分解质因子，如果有两个相同的或三个不同的，就加一个强合数，然后把剩下的随便乘进去就完了。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
unordered_map<int,int>pf;//质因数
void prime_factor(int x){//分解质因数
    int i=2;
	while(x>1&&i*i<=x){
		while(x%i==0)x/=i,pf[i]++;
		i++;
	}
	if(x>1)pf[x]++;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		pf.clear();//多测不清空，爆零两行泪
		int n;
		cin>>n;
		int ans1=0,ans2=0;//相同质数数量，不同质数数量
		for(int i=1;i<=n;i++){
			int t;
			cin>>t;
			prime_factor(t);
		}
		for(auto [_,num]:pf){
			ans1+=num/2;
			ans2+=num%2;
		}
		cout<<ans1+ans2/3<<'\n';
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

由于只要求乘积相等，我们可以将 $a$ 的质因数分解形式存下来然后展开成 $b$。

怎样构成强合数呢？发现一个质数的平方是用到最少质因数组成的强合数（恰好有一个质数 $p$ 为约数和一个合数 $p^2$ 为约数）。而如果任意质数，则至少需要三个质数 $p_1,p_2,p_3$ 才能组成一个强合数。

因此对 $n$ 个数都进行质因数分解，然后优先将两个相同的质因数并成一个强合数，再将剩下的不同的质因数每三个一组并成一个强合数。

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    int n, x; scanf("%d", &n); map<int, int> a; 
    while (n--) {
        scanf("%d", &x); 
        for (int i = 2; i * i <= x; ++i) while (x % i == 0) x /= i, ++a[i]; 
        if (x > 1) ++a[x]; 
    }
    int c1 = 0, c2 = 0; 
    for (auto [x, y] : a) c1 += y / 2, c2 += y % 2; 
    printf("%d\n", c1 + c2 / 3); 
}

int main(void) {
    int T; scanf("%d", &T); 
    while (T--) solve();    
    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

好的如你所见，这道题是我平生最烦的构造题，但似乎非常简单。

考虑一件事情，我们分解质因数后，如果这个数 $x = p \times q$，且 $p$ 与 $q$ 是不同的质数，那么这个数就不是强合数，反之，它就是个强合数。

为啥呢，因为超过两个质数我随便组合其合数因子个数绝对会大于等于质数个数，如果这个数是某个质数的平方就更显然了。

然后我们就考虑优先把数字拉过来两两配对，然后落单的三个三个的配对，完了。

对了，预处理质数然后分解是个稳妥的办法，其时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7,N=1e7+5;
int n,prime[N],f[N],a[N];
bool vis[N];
int cnt;
unordered_map <int,int> col;
void init(){
	for(int i = 2;i <= maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j = 1;j <= cnt&&prime[j]*i <= maxn;j++){
			vis[prime[j]*i]=1;
			f[prime[j]*i]=prime[j];
			if(i%prime[j]==0)break;
		}
	}
}
void fj(int x){
	while(f[x]>1)col[f[x]]++,x/=f[x];
	if(x>1)col[x]++;
}
void work(){
	int ans=0,tmp=0;
	col.clear();
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i],fj(a[i]);
	for(auto it:col){
		ans+=(it.second>>1);
		if(it.second&1)tmp++;
	}
	cout << ans+(tmp/3) << "\n";
}
int t;
int main(){
	init();
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)work();
	return 0;
}

```

---

