# Rock and Lever

## 题目描述

"You must lift the dam. With a lever. I will give it to you.You must block the canal. With a rock. I will not give the rock to you."





Danik urgently needs rock and lever! Obviously, the easiest way to get these things is to ask Hermit Lizard for them.

Hermit Lizard agreed to give Danik the lever. But to get a stone, Danik needs to solve the following task.

You are given a positive integer $ n $ , and an array $ a $ of positive integers. The task is to calculate the number of such pairs $ (i,j) $ that $ i<j $ and $ a_i $ $ \& $ $ a_j \ge a_i \oplus a_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Danik has solved this task. But can you solve it?

## 说明/提示

In the first test case there is only one pair: $ (4,7) $ : for it $ 4 $ $ \& $ $ 7 = 4 $ , and $ 4 \oplus 7 = 3 $ .

In the second test case all pairs are good.

In the third test case there are two pairs: $ (6,5) $ and $ (2,3) $ .

In the fourth test case there are no good pairs.

## 样例 #1

### 输入

```
5
5
1 4 3 7 10
3
1 1 1
4
6 2 5 3
2
2 4
1
1```

### 输出

```
1
3
2
0
0```

# 题解

## 作者：STDquantum (赞：4)

考虑二进制位，对于任何正整数 $a_i$ 和 $a_j$，有：

若是 $a_i$ 和 $a_j$ 最高位不同，那么必然 $a_i\&a_j\lt a_i\oplus a_j$，因为 $1\oplus0=1,1\&0=0$，按位与操作后最高位变成了 $0$，而按位异或后最高位变成了 $1$。

若是 $a_i$ 和 $a_j$ 最高位相同，那么必然 $a_i\&a_j\gt a_i\oplus a_j$，因为 $1\oplus1=0,1\&1=1$，按位与操作后最高位变成了 $1$，而按位异或后最高位变成了 $0$。

只可能有这两种情况，所以 $a_i\&a_j= a_i\oplus a_j$ 的情况无需考虑（对 $a_i=a_j=0$ 是成立的，但限定了为正整数）。

而统计答案的时候，只需要记录最高位 $k$ 相同的数的个数 $num_k$，在这些数中，任选两个都符合题意，所以 $\displaystyle  ans=\sum_k\left(\begin{array}{c}num_k\\2\end{array}\right)$。

记得开`long long`。

```cpp
typedef long long ll;
const int N = 40;

int n, t, num[N];
ll ans;
inline void main() {
  for (read(t); t--;) {
    read(n);
    for (int i = 1, x; i <= n; ++i) {
      read(x);
      for (int k = 30; ~k; --k) {
        if (x & (1 << k)) {
          ++num[k];
          break;
        }
      }
    }
    ans = 0;
    for (int i = 0; i <= 30; ++i) {
      ans += (ll)num[i] * (num[i] - 1) / 2;
      num[i] = 0; // 省掉memset
    }
    write(ans), putchar('\n');
  }
}
```

# 

---

## 作者：Skyjoy (赞：1)

# 思路

既然题目中的操作是位运算，那么我们就可以把数转换为二进制数来考虑。而小学数学告诉我们，两数比大小要**从最高位**进行比较。所以我们对两次运算结果的最高位进行分析。我们可以发现：

1. 若 $a_i$ 与 $a_j$ 最高位不相同，则 $a_i\& a_j<a_i\oplus a_j$ ，因为此时按位与操作后最高位是 $0$ ，异或之后是 $1$ 。

2. 若 $a_i$ 与 $a_j$ 最高位相同，则 $a_i\& a_j>a_i\oplus a_j$ ，因为此时按位与操作后最高位是 $1$ ，异或之后是 $0$ 。

所以我们记录二进制最高位是 $i$ 的数的个数 $cnt_i$ ，就可以算出最终的答案 $\sum_i C_{cnt_i}^2$ 。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=100010;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
ll T,n,x,cnt[40],maxn,ans;
ll lg(ll x){
	ll res=0;
	while(x)x>>=1,res++;
	return res;
}
int main(){
	T=read();
	while(T--){
		memset(cnt,0,sizeof(cnt));
		maxn=ans=0;
		n=read();
		for(int i=1;i<=n;i++){
			x=read();
			cnt[lg(x)]++;
			maxn=max(maxn,lg(x));
		}
		for(int i=1;i<=maxn;i++)ans+=1ll*(cnt[i]-1)*(cnt[i])/2;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：king_xbz (赞：1)

唯一的一篇题解没有代码，我来发一篇完整的讲解+代码。

对于这道题，我们要求$i<j$且$a_i$&$a_j≥a_i$^$a_j$的二元组数量。

最暴力的思路肯定是$O(n^2)$暴力枚举，然而数据范围1e5，直接pass。

**那么有什么办法来优化呢？**

我们可以来考虑一下位运算的性质。那就是什么时候&>^？

我们知道，对于&运算，只有在二进制位均为1时该位才为1，而^运算则是在一位为1，一位为0的时候为1.这恰好的覆盖了所有二进制最高位的关系。也就是说，只有当两数二进制最高位都为1，才有可能使得二者按位与值大于等于按位异或值。

所以我们先**预处理出各个数的二进制位数和二进制最高位。当位数相同且最高位都是1时就可以构成这种条件。**

然而，还有一个条件$i<j$限制着我们。但是，我们可以想到，**对于几个满足以上条件的数，他们的排列是对结果无影响的**，也就是说，我们可以直接忽视掉这个条件，也就是说，如果有5个数满足条件，答案直接就是$4+3+2+1$，与先后顺序无关。（不要忘记一个数永远不能和自己构成数对）

**最后别忘开long long**

知道这几点，我们就可以AC此题了。

代码：
```cpp
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		int n;
		cin>>n;
		int tot=0,a,maxxs=0;
		for(fint i=1,j=0;i<=n;i++)
		cin>>a,s[i]=yap(a),maxxs=max(s[i].wei,maxxs),s[i].hig==1?vis[s[i].wei]++:j++;
		int ans=0;
		for(fint i=1;i<=maxxs;i++)
		if(vis[i]>0)
		ans+=sigma(vis[i]-1);
		cout<<ans<<endl;
	}
	return 0;
}

inline node yap(int x)
{
	node b;
	int cnt=0;
	while(x)
	an[++cnt]=x%2,x>>=1;
	b.hig=an[cnt],b.wei=cnt;
	return b;
}

inline int sigma(int x)
{
	int tot=0;
	for(fint i=1;i<=x;i++)
	tot+=i;
	return tot;
}
```

---

## 作者：nztyz (赞：1)

### 题意:
给定一段序列,求次序列中有多少对满足
$a[i]&a[j]>=a[i]^a[j]$
$i<j$
##
如4,7  
4 的二进制 100  
7 的二级制 111  
4&7 =       100(只有1,1,才为1)  
4^7 =        011(相同为假,不同为真)     
可以发现当两个数的最高位相同时,才满足$a[i]&a[j]>=a[i]^a[j]$,所以可以求出所有数字的最高位并储存在数组C中;  
```int get_bit(int x,int v) { return (x>>v)&1; } ``` **判断x的第v位上是否为1**
#### Code
```c
#include <bits/stdc++.h>
using namespace std;
int get_bit(int x,int v) { return (x>>v)&1; } 
int main()
{
	int n;
	cin>>n;
	while(n--){
		int t;
		cin>>t;
		int cnt[30] = {};
		while(t--){
			int x;
			cin>>x;
			for(int i = 29 ; i >= 0 ; i--){//从29开始,可以保证第一个存入cnt数组的位最高位
				if(get_bit(x,i)){
					cnt[i]++;
					break;
				}
			}	
		}
		long long ans = 0;
		for(int i = 0 ; i < 30 ; i++){
			ans += cnt[i] * (cnt[i]-1ll) / 2;//每一位如果>2,则要求出他们的排列组合;
		}
		cout<<ans<<endl;
	}

	return 0;
}

---

## 作者：引领天下 (赞：0)

注意到一个性质：

> $a_i$ 只可能跟与 $a_i$ 转成二进制之后位数相同的 $a_j$ 产生贡献。

证明：

设 $a_i,a_j$ 为转成二进制之后位数不同的两个数（不妨设 $a_j>a_i$），则他们转成二进制后形式必然如下：

```
ai: 0...0....
aj: 0...1....
```

那么有：

```
ai^aj: 0...1....
ai&aj: 0...0....
```

可以注意到在 $a_i,a_j$ 不同的第一位就已经出现了 $a_i\text{XOR}a_j$ 为 $1$，而 $a_i\text{AND}a_j$ 为 $0$ 的情况，即 $a_i\text{XOR}a_j$ 必然大于 $a_i\text{AND}a_j$.

故只有 $a_i,a_j$ 具有相同的二进制位数的时候 $a_i,a_j$ 才可能产生贡献。

于是我们可以枚举二进制位数，仅对二进制位数为当前枚举的二进制位数的 $a$ 统计答案，时间复杂度为 $O(nlog\text{maxa})$，其中 $\text{maxa}$ 表示最大的 $a_i$。

---

## 作者：SuperTNT (赞：0)

该题用到了异或，与的性质，异或是两位不同为 $1$ ，与是两位是 $1$ 才是  $1$ ，因此我们可以贪心的统计每一个数的最高位，最后组合数一求每一位上选两个 $1$ 的方案数即可
记得开  $long long$
```
#include <bits/stdc++.h>

#define re register

namespace TNT
{
    const int MAXN = 33;

    inline int read()
    {
        int x = 0;
        char ch = getchar();
        while (ch < '0' || ch > '9')
            ch = getchar();
        while (ch >= '0' && ch <= '9')
        {
            x = x * 10 + ch - '0';
            ch = getchar();
        }
        return x;
    }

    int a[MAXN];

    inline long long C(int n, int m)
    {
        if(n < m)
            return 0;
        if (m < n - m)
            m = n - m;
        long long ans = 1;
        for (re int i = m + 1; i <= n; i++)
            ans *= i;
        for (re int i = 1; i <= n - m; i++)
            ans /= i;
        return ans;
    }
    inline void main()
    {
        int t = read();
        while (t--)
        {
            memset(a,0,sizeof(a));
            int n = read();
            for (re int i = 1; i <= n; i++)
            {
                int x = read();
                int cnt = 31;
                while (!(x >> cnt))
                    --cnt;
                ++a[cnt + 1];
            }

            long long ans = 0;
            for (re int i = 1; i <= 31; i++)
                if(a[i] >= 2)
                    ans += 1ll * a[i] * (a[i] - 1) / 2;
            
            printf("%lld\n",ans);
        }   
        return;
    }
} // namespace TNT

int main()
{
    TNT::main();
    return 0;
}
```

---

## 作者：几何之舞丶 (赞：0)

题意:给定一个序列A,求 满足
  i<j,且A[i]& A[j]>A[i] xor A[j] 的(i,j)的对数.
  
  
 
 考虑两个数 & 与 xor 实际上是在做什么工作.
 
 如果两个数,写成二进制之后最高位不同,那么最高位更高的数肯定更大.
 
 这两个数xor 起来最高位肯定是1,这两个数&起来肯定是0
 
 如果两个数,写成二进制之后最高位相同,那么他们 &起来肯定是1,xor起来肯定是0;
 
 因此我们只需要统计二进制下最高位为k的个数,然后组合数统计就可以了.
 


---

