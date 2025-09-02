# Sum of XOR Functions

## 题目描述

You are given an array $ a $ of length $ n $ consisting of non-negative integers.

You have to calculate the value of $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1) $ , where $ f(l, r) $ is $ a_l \oplus a_{l+1} \oplus \dots \oplus a_{r-1} \oplus a_r $ (the character $ \oplus $ denotes bitwise XOR).

Since the answer can be very large, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, the answer is equal to $ f(1, 1) + 2 \cdot f(1, 2) + 3 \cdot f(1, 3) + f(2, 2) + 2 \cdot f(2, 3) + f(3, 3) =  $ $ = 1 + 2 \cdot 2 + 3 \cdot 0 + 3 + 2 \cdot 1 + 2 = 12 $ .

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
12```

## 样例 #2

### 输入

```
4
39 68 31 80```

### 输出

```
1337```

## 样例 #3

### 输入

```
7
313539461 779847196 221612534 488613315 633203958 394620685 761188160```

### 输出

```
257421502```

# 题解

## 作者：Zelotz (赞：22)

记前缀异或和数组 $s$，于是题目中的 $f(l,r)$  可以被表示成 $s_r \oplus s_{l-1}$，转化为求 $\sum\limits_{l=1}^n \sum \limits_{r=l}^n (s_r \oplus s_{l-1})\times (r-l+1)$。

再记录 $4$ 个值，$cnt_0,cnt_1,sum_0,sum_1$ 分别表示当前已经出现过的 $0/1$ 的个数，出现的所有 $0/1$ 的下标和。

从左到右遍历 $s$ 数组，对于当前遍历到的 $s_i$，进行拆位计算贡献。

设 $s_i$ 的第 $j$ 位为 $x$，那么有 $cnt_{!x}$ 个数产生贡献，所以原式    $(s_r \oplus s_{l-1})\times (r-l+1)$ 中 $r$ 的贡献为 $cnt_{!x} \times i$，前面的 $l-1$ 的贡献即为维护的下标和 $sum_{!x}$。

参考了 jiangly 的做法，感觉非常优美。

```
const int N = 3e5 + 5, P = 998244353;
int n, s[N], cnt[2], sum[2];
signed main()
{
    cin >> n;
    R(i, 1, n)
    {
        int x;
        cin >> x;
        s[i] = s[i - 1] ^ x;
    }
    int ans = 0;
    R(j, 0, 31)
    {
        cnt[0] = cnt[1] = sum[0] = sum[1] = 0;
        R(i, 0, n)
        {
            int x = s[i] >> j & 1;
            (ans += ((1ll * i * cnt[!x] % P - sum[!x]) * (1 << j) % P + P) % P) %= P;
            ++cnt[x];
            (sum[x] += i) %= P;
        }
    }
    cout << ans << '\n';
    return 0;
}

---

## 作者：Na2PtCl6 (赞：12)

套路题。我们老师之前讲过一般像这样计算所有子区间的式子，如果要优化成接近线性，有一种可行思路是把注意力放在右端点，通过不断移动右端点，在移动的时候利用前面的统计结果算出移动右端点后的结果，从而得出所有子区间的答案。然后还有一个显然有用的套路是前缀和，这里记 $s_i=a_1 \operatorname{xor} a_2\operatorname{xor} ···\operatorname{xor}a_{n-1}\operatorname{xor}a_n $ ，$s_{i,j}$ 为 $s_i$ 二进制的第 $j$ 位，我们会发现 $\displaystyle \sum_{l=1}^{n}\sum_{r=l}^{n}f(l,r)=\sum_{i=0}^{32}\sum_{l=1}^{n}\sum_{r=l}^{n}s_{l,i} \operatorname{xor} s_{r,i}\times 2^i $

由于上面的式子可以优化成 $O(n\operatorname{log}V)$，我们受到启发推出下面的式子

$$\sum_{l=1}^{n}\sum_{r=l}^{n}f(l,r)\times(r-l+1)$$

$$=\sum_{r=1}^{n}\sum_{l=1}^{r}f(l,r)\times(r-l+1)$$

$$=\sum_{r=1}^{n}\sum_{l=1}^{r}\sum_{i=0}^{32} s_{l,i} \operatorname{xor} s_{r,i}\times 2^i\times(r-l+1)$$

$$=\sum_{r=1}^{n}\sum_{i=0}^{32} \sum_{l=1}^{r}[ s_{r,i}\operatorname{xor}s_{l,i} =1]\times 2^i\times(r-l+1)$$

$$=\sum_{r=1}^{n}\sum_{i=0}^{32} 2^i\times\sum_{l=1}^{r}[ s_{r,i}\operatorname{xor}s_{l,i} =1]\times r-[ s_{r,i}\operatorname{xor}s_{l,i} =1] \times (l-1)$$

把 $r$ 视作常量再观察上面的式子，你就会发现最后一维可以被优化掉，因为 $\displaystyle \sum_{l=1}^{r}[ s_{r,i}\operatorname{xor}s_{l,i} =1] $ 和 $\sum_{l=1}^{r}[ s_{r,i}\operatorname{xor}s_{l,i} =1]\times (l-1)$ 都可以预处理。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=300004,mod=998244353;
char sep[maxn][34];  //to minimize memory
int n,res,sum[34][2],cnt[34][2],a[maxn],xsum[maxn];

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		xsum[i]=xsum[i-1]^a[i];
		for(int j=32;j>=0;j--)
			sep[i][j]=((xsum[i]>>j)&1);
	}
	for(int i=32;i>=0;i--)
		cnt[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=32;j>=0;j--)
			res=(res+(cnt[j][sep[i][j]^1]*i%mod-sum[j][sep[i][j]^1]%mod+mod*2)*(1<<j))%mod;
		for(int j=32;j>=0;j--){
			sum[j][sep[i][j]]+=i;
			cnt[j][sep[i][j]]++;
		}
	}
	printf("%lld\n",res);
	return 0;
} 
```

---

## 作者：Creeper_l (赞：12)

## 题意

给定一个数 $n$ 和一个包含 $n$ 个数的序列 $a$，求出以下式子模 $998244353$ 的值：

$\sum_{i=1}^{n}\sum_{j=i}^{n} f(i,j)\times (j-i+1)$。

其中 $f(i,j)$ 的值为 $a_{i}\oplus a_{i+1}\oplus a_{i+2}\oplus...\oplus a_{j}$。

## 思路

首先我们可以考虑这道题的弱化版 [P3917 异或序列](https://www.luogu.com.cn/problem/P3917)，我们可以设 $dp_{i,j}$ 表示第 $i$ 个数的第 $j$ 位对答案的贡献，也就是在 $i$ 之前的每一个数的第 $j$ 位有多少个数满足区间异或的值为一。那么我们考虑将每个 $a_{i}$ 按照二进制位拆开，如果当前位置是 $1$ 的话，那么 $dp_{i,j}=i-dp_{i-1,j}$，因为只有前面的异或和为 $0$ 时（所有数的数量减去异或和为 $1$ 的数量），异或上当前位置的 $1$ 答案才为 $1$；否则如果当前位置的值是 $0$，那么 $dp_{i,j}=dp_{i-1,j}$，因为只有前面的异或和为 $1$ 时，异或上当前位置的 $0$ 答案才为 $1$。

因为这里的每一个 $dp_{i,j}$ 表示的是贡献的数量，所以还要乘上对应的值，也就是 $2^{j}$，这样就可以得出答案了。注意 $dp$ 数组可以滚掉一维，节省空间。

然后我们考虑这道题怎么做，其实比较好想了。我们可以对每一位计算贡献，对于每个数的每一位，可以多维护一个 $s_{0,1}$ 表示 $a_{1}\oplus a_{2}\oplus a_{3}\oplus...\oplus a_{i}$ 的值，$cnt_{0/1}$ 表示有多少个数的 $s_{j}$ 为 $1/0$，$sum_{1/0}$ 表示所有 $s_{j}$ 为 $0/1$ 的数到 $1$ 的距离（也就是 $j$）。然后每次加上相应的距离就行了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 3e5 + 10;
const int mod = 998244353;
int n,a[MAXN],s[MAXN],ans; 
signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 0;i <= 30;i++)
	{
		s[1] = 0;
		for(int j = 1;j <= n;j++) s[j + 1] = s[j] ^ (a[j] >> i & 1);
		vector <int> cnt(2, 0);
    	vector <int> sum(2, 0);
    	for(int j = 1;j <= n + 1;j++)
    	{
    		ans = (ans + cnt[s[j] ^ 1] * j % mod * (1ll << i)) % mod;
			ans = (ans - sum[s[j] ^ 1] * (1ll << i) + mod) % mod;
    		cnt[s[j]]++;
    		sum[s[j]] = (sum[s[j]] + j) % mod;
		}
		ans = ans % mod;
	} 
	cout << ans << endl;
	return 0;
}

```


---

## 作者：Κarrу5307 (赞：3)

看到区间异或，容易想到垒异或前缀和，记为 $sum$，则答案转为 $\sum\limits_{l=1}^n\sum\limits_{r=l}^n(sum_{r}\oplus sum_{l-1})\times (r-l+1)$，由于 $sum_{l-1}\oplus sum_{l-1}=0$，则可以修改一下求和的下界，将答案转为 $\sum\limits_{l=0}^n\sum\limits_{r=l}^n(sum_{r}\oplus sum_{l})\times (r-l+1)$。然后可以发现这个式子其实就是 $\frac{\sum\limits_{l=0}^n\sum\limits_{r=0}^n(sum_{r}\oplus sum_{l})\times (r-l+1)}{2}$，因为去掉了所有 $l>r$ 的 $(l,r)$ 对答案的贡献（对于 $l=r$ 很明显做 $0$ 贡献所以无所谓）。

现在相当于求一个长度为 $n+1$ 的数组 $sum$ 中两两元素异或值乘上距离的和。由于答案是异或乘一大堆东西，这明显不好直接算或者维护，所以考虑拆位算贡献。考虑 $2^i$ 位的贡献。

取出数组中每一个元素在这一位上的值，得到一个 $01$ 序列。然后顺序枚举每一个位置，计算这个位置上的元素作为 $l$ 或 $r$ 对答案的贡献。考虑在枚举过程中动态维护左侧每一个 $0,1$ 位置到这个位置的距离 $ldis_0,ldis_1$，以及右侧同样的变量 $rdis_0,rdis_1$，很明显若这个位置的值为 $x$，这个位置对答案的贡献即为 $(ldis_{1-x}+rdis_{1-x})\times 2^i$，因为只有值不相等的位置才能异或出来 $1$。

为了维护这四个变量，还需要维护左侧 $0,1$ 的个数和右侧同样的变量。由于是顺序枚举，这八个变量都可以 $\mathcal O(1)$ 在枚举的位置移动时转移。

计算出总答案后不要忘记除以 $2$。由于需要取模所以使用乘法逆元，在最后给答案乘上一个 $499122177$ 输出即可。

总时间复杂度为 $\mathcal O(n\log V)$。实现细节比较复杂。

---

## 作者：XioasDog (赞：2)

# CF1879D

拆位处理，对于每一位预处理出前缀和，令其为 $s_i$，对前缀和也前缀和处理（前 $i$ 位总和，是奇数的个数）令其为 $p_{1,i}$（偶数个数为 $p_{0,i}$）。

并记满足前 $i$ 位总和是奇数的所有下标的前缀和是 $sum_{1,i}$，偶数是 $sum_{0,i}$。

对于每一个 $r$ 右端点，如果 $s_r$ 为奇数，那么就是找前 $r-1$ 位的前缀和为偶数的个数。

就用前缀和的前缀和来找（也就是 $p_{0,i}$），那对于这一位（第 $k$ 位），这一个 $r$，此时的贡献为 
$(p_{0,r-1}\times r-sum_{0,r-1})\times 2^{k-1}$。$s_r$ 是偶数同理。

对于每一位，每一个右端点 $r$ 都这么处理。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=3e5+9,M=32,mod=998244353;

int n,a[N],s[N],p[N][2],sum[N][2],ans;

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int k=0;k<=30;k++){
        memset(s,0,sizeof s);
        memset(p,0,sizeof p);
        memset(sum,0,sizeof sum);

        p[0][0]=1;
        for(int i=1;i<=n;i++){
            s[i]=s[i-1];
            p[i][0]=p[i-1][0],p[i][1]=p[i-1][1];
            sum[i][0]=sum[i-1][0],sum[i][1]=sum[i-1][1];
            s[i]+=(a[i]>>k)&1;
            if(s[i]&1)p[i][1]++,sum[i][1]+=i;
            else p[i][0]++,sum[i][0]+=i;
        }
        for(int r=1;r<=n;r++){
            if(s[r]&1)ans+=(p[r-1][0]*r-sum[r-1][0])%mod*(1<<k)%mod;
            else ans+=(p[r-1][1]*r-sum[r-1][1])%mod*(1<<k)%mod;
            ans%=mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：DerrickLo (赞：1)

显然可以考虑拆位。

拆位后考虑第 $i$ 位，对于整个序列的第 $i$ 位我们可以转换成一个 $0,1$ 序列，我们考虑递推来求对于每个数结尾对答案的贡献。

如果现在求出对于第 $j$ 个数结尾的答案是 $ans$，对答案有贡献的地方有 $t$ 个的话，我们分两种情况讨论。

如果第 $j+1$ 个数为 $0$，那么前面所有的对答案有贡献的地方都不会变化，而每个有贡献的长度都会加 $1$，即对于第 $j+1$ 个数结尾的答案是 $ans+t$。

如果第 $j+1$ 个数为 $1$，那么前面所有对答案有贡献的地方对 $j+1$ 都没有贡献，反之亦然，所以对于第 $j+1$ 个数结尾的答案就是 $\frac{(j+1)(j+2)}{2}-ans-t$，此时 $t$ 要更新成 $j+1-t$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,a[300005],maxx,anss;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],maxx=max(maxx,a[i]);
	int hep=log2(maxx);
	for(int i=0;i<=hep;i++){
		int nwans=0,hv=0;
		for(int j=1;j<=n;j++){
			if(a[j]&(1<<i)){
				nwans=j*(j+1)/2-nwans-hv;
				hv=j-hv; 
			}
			else{
				nwans+=hv;
			}
			nwans%=mod,anss+=ksm(2,i)*nwans%mod,anss%=mod;
		}
	}
	cout<<anss;
	return 0;
}
```

---

## 作者：Struct_Sec (赞：1)

## 题意：

给定一个长度为 $n$ 的数组 $a$，它由非负整数组成。求 $\sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1)$。

## Sol

首先我们枚举每一个 $i$，算出 $\sum_{j=1}^{i} f(i, j) \cdot (i - j + 1)$ 并加到答案里。如果我们先不考虑乘上 $(i - j + 1)$，那么这个问题就退化成了[P3917](https://www.luogu.com.cn/problem/P3917)。我们考虑对每一位用前缀和记录这一位上 $0$ 和 $1$ 的个数，并计算答案。

然后我们再考虑乘上 $(i - j + 1)$。设当前枚举到第 $k$ 位，我们将原来的方法转换一下，多记录一个 $sum_{k}$，每次将这一位的贡献转换为 $(cnt_{k} \cdot i - sum_{k}) \cdot 2^{k}$，然后计算答案即可。

需要注意的是，计算答案的时候需要多次取模，这个玩意很容易爆 long long。

[评测链接](https://codeforces.com/contest/1879/submission/225013662)

---

## 作者：huangrenheluogu (赞：0)

注：$\oplus_{i=l}^{r}a_i=a_l\oplus a_{l+1}\oplus\dots\oplus a_r$。

这种求 $\oplus_{i=l}^{r}a_i$ 的题已经变成套路了。

直接考虑拆位（蒟蒻才疏学浅，没有其他套路）。

如果考虑二进制下第 $k$ 位，那么就变成 $0,1$ 序列。考虑对一个点 $i$ 记录以 $i$ 为结尾的答案。

那么，记 $a_i$ 的第 $k$ 位为 $b_i$。

根据 $x\oplus x=0$，$cnt0$ 表示 $\oplus_{I=j}^ia_{I}=0$ 的个数；同理可得到 $cnt1$。

定义 $sum0$ 表示对于 $\forall j,\oplus_{I=j}^ia_{I}=0$，$i-j+1$ 的长度之和；同理可得 $sum1$。

每次向右移动的时候，$sum0,sum1$ 分别增加 $cnt0,cnt1$；根据 $b_i$ 判断是否交换 $0,1$ 的统计结构。

根据 $sum1$ 求和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5, mod = 998244353;
int n, a[N], cnt0, cnt1, sum0, sum1, b[N], ans;
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
	}
	for(int dep = 0; dep < 30; dep++){
		for(int i = 1; i <= n; i++){
			b[i] = a[i] >> dep & 1;
		}
		cnt0 = cnt1 = sum0 = sum1 = 0;
		for(int i = 1; i <= n; i++){
			sum1 += cnt1, sum0 += cnt0;
			if(b[i] == 0){
				cnt0++, sum0++;
			}
			else{
				swap(sum1, sum0);
				swap(cnt1, cnt0);
				sum1++, cnt1++;
			}
			sum1 %= mod, sum0 %= mod;
			(ans += (1ll << dep) * sum1 % mod) %= mod;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

没想到几个月前我还能稳定地写出 D 题。

首先考虑按中点分治。

对于中点 $x$ 考虑所有跨过它的区间 $[l,r]$。

从这个点开始向两边遍历，将区间长度的贡献挂到相应的区间端点的二进制的每一位上。

那么最后将每一层分治的贡献按照二进制拆位后计算再乘上 $2^i$ 即可。

时间复杂度是 $O(n \log n \log V)$ 的，可以冲过去。

[代码](https://codeforces.com/contest/1879/submission/240230651)


---

## 作者：phigy (赞：0)

我们选择用前缀异或和与拆位将问题转化为每位求 $\sum_{l=1}^n\sum_{r=l}^n sum_l\otimes sum_r$。

那么实际上设 $s_{i,j}$ 表示前 $i$ 个前缀异或和为 $j$ 的数的个数。

而 $len_{i,j}$ 表示前 $i$ 个前缀异或和为 $j$ 的数的到 $i$ 的长度之和。

那么就有 $len_{i,j}=len_{i-1,j}+s_{i-1,j}$。

所以答案就转化为了 $\sum_{r=1}^n len_{i-1,sum_r\otimes1}$ 那就解决了。

```cpp
#include <iostream>

#define MOD 998244353
#define int long long

using namespace std;

int n;
int a[3000005];
int ans;
signed main()
{
    int i,j,k;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        a[i]^=a[i-1];
    }
    int res=1;
    for(j=1;j<=40;j++)
    {
        int sum0=1,sum1=0,len0=1,len1=0;
        for(i=1;i<=n;i++)
        {
            if(a[i]&1)
            {
                ans+=len0*res%MOD;
                sum1++;
            }
            else
            {
                ans+=len1*res%MOD;
                sum0++;
            }
            len0+=sum0;
            len0%=MOD;
            len1+=sum1;
            len1%=MOD;
            ans%=MOD;
        }
        for(i=1;i<=n;i++)
        {
            a[i]/=2;
        }
        res*=2;
        res%=MOD;
    }
    cout<<ans;
    return 0;
}

```


---

## 作者：RockyYue (赞：0)

### 题意
给定 $a_{1\dots n}$，求 $\sum_{1\le l\le r\le n}{(r-l+1)(a_l\oplus a_{l+1} \oplus \cdots \oplus a_r)}$。

其中 $n\le 3\times 10^5,1\le a_i\le 10^9$。

### 题解
异或求和，一般按结果每位进行处理。但是这里有区间长度，就复杂了很多。于是对 $a_{1\dots n}$ 每位分别处理贡献和。

对于从后往前第 $i$ 位，设 $b_j$ 为 $a_j$ 二进制中的这一位，则其贡献为 $2^{i-1} \cdot \sum_{1\le l\le r\le n}{[b_l\oplus b_{l+1} \oplus \cdots \oplus b_r=1](r-l+1)}$。

这样处理有什么好处呢？由于 $b_i \in {0,1}$，异或和为 $1$ 即这一段 $1$ 的个数为奇数，于是记 $s_i$ 为 $b_{1\dots i}$ 中 $1$ 的个数，方便处理。

对于每一个 $r$ 分别考虑，$l$ 满足区间异或和为 $1$ 即 $s_r \not \equiv s_{l-1}\pmod 2 $。记所有满足条件的 $l-1$ 的集合为 $T$，则当前位的贡献为 $|T|\cdot r-\sum _{t\in T}{t}$。

如此一来我们只需要维护：
- $cnt_{i,0/1}$：对于 $1\le j < i$，满足 $s_j$ 为偶（奇）的 $j$ 的个数。
- $sum_{i,0/1}$：满足条件的 $j$ 的和。

则当前位以 $r$ 为右端点贡献：```cnt[r][s[r] ^ 1] * r - sum[r][s[r] ^ 1]```。

设 $m=\max_{i=1}^{n}\{a_i\}$，则复杂度 $O(n \log m)$。

---

## 作者：qwq___qaq (赞：0)

二进制位拆已经变成套路

位拆之后转化成 0/1 序列，然后相当于求所有有奇数个 $1$ 的序列的长度和。

类似于周考 T6 用一条边代表路径的方法，考虑用一个点代表一个区间，那么就非常自然地想到以区间的右端点作为代表。

显然总长度跟方案有关，由此可以自然地想到定义 $f_{i,0/1,0/1}$ 表示第 $i$ 个元素结尾的序列中 $1$ 个数为偶数/奇数的方案数/区间长度和。

然后就对 $a_i$ 分成 $0/1$ 讨论转移即可，状态转移方程式非常的简单。

---

## 作者：spdarkle (赞：0)

给定 $a_i$，设 $f(l,r)=a_l\oplus a_{l+1}\oplus\dots \oplus a_r$，求 $\sum_{i=1}^n\sum_{j=i}^n(j-i+1)f(i,j)$，其中 $1\le n\le 3\times 10^5$。

简单的问题。

首先设 $s_i=s_{i-1}\oplus a_i,s_0=0$。

然后我们按位统计贡献,将 $(i-j+1)s_i\oplus s_{j-1}$ 拆为 $i\times (s_i\oplus s_{j-1})-(j-1)\times(s_i\oplus s_{j-1})$

设当前统计到了第 $k$ 位，每一位贡献位 $2^k$。

统计 `b[i]=(a[i]>>k)&1`，对于每个数统计贡献就只分四种情况：$b_i$ 的取值和其作为 $l-1,r$ 其中之一的取值。

设 $pre_i=pre_{i-1}+b_i,pre_0=0,suf_i=suf_{i+1}+b_{i},suf_{n+1}=0$。

然后，分类讨论，取 $i$ 从零到 $n$：

1. $b_i=0$，此时作为 $r$ 的贡献为 $2^k\times i\times pre_i$，作为 $l-1$ 的贡献为 $-2^k\times i\times suf_i$
2. $b_i=1$，将上面的 $pre_i$ 改为 $i-pre_i$，$suf_i$ 改为 $n-i-suf_i$ 即可。

[code](https://codeforces.com/contest/1879/submission/224935250)


---

## 作者：Hisaishi_Kanade (赞：0)

精神状态值得担忧。

首先拆位是显然的，然后变成了一个弱化形如 01 序列的东西，数奇数个 $1$ 的区间个数。

这个题我相信都会，记录一下前缀和奇偶性即可。现在考虑区间个数略微麻烦一点。但是也不难，你考虑 $\sum {(i-j+1)}$ 实际可以变成 $ki-\sum j$ 这样的玩意。那么我们只需要记录奇偶性个数和位置数之和即可。

这样做是 $O(n\log V)$ 的。

题外话是我写了一个 $O(n\log n\log V)$ 的线段树但是没有跑过去。

包括暴力在内三个版本都在[这里](https://codeforces.com/contest/1879/submission/226149075)。


---

