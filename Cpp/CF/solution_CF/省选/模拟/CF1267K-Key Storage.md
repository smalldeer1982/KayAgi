# Key Storage

## 题目描述

Karl is developing a key storage service. Each user has a positive integer key.

Karl knows that storing keys in plain text is bad practice. So, instead of storing a key, he decided to store a fingerprint of a key. However, using some existing fingerprint algorithm looked too boring to him, so he invented his own one.

Karl's fingerprint is calculated by the following process: divide the given integer by 2, then divide the result by 3, then divide the result by 4, and so on, until we get a result that equals zero (we are speaking about integer division each time). The fingerprint is defined as the multiset of the remainders of these divisions.

For example, this is how Karl's fingerprint algorithm is applied to the key 11: 11 divided by 2 has remainder 1 and result 5, then 5 divided by 3 has remainder 2 and result 1, and 1 divided by 4 has remainder 1 and result 0. Thus, the key 11 produces the sequence of remainders $ [1, 2, 1] $ and has the fingerprint multiset $ \{1, 1, 2\} $ .

Ksenia wants to prove that Karl's fingerprint algorithm is not very good. For example, she found that both keys 178800 and 123456 produce the fingerprint of $ \{0, 0, 0, 0, 2, 3, 3, 4\} $ . Thus, users are at risk of fingerprint collision with some commonly used and easy to guess keys like 123456.

Ksenia wants to make her words more persuasive. She wants to calculate the number of other keys that have the same fingerprint as the keys in the given list of some commonly used keys. Your task is to help her.

## 说明/提示

The other key with the same fingerprint as 11 is 15. 15 produces a sequence of remainders $ [1, 1, 2] $ . So both numbers have the fingerprint multiset $ \{1, 1, 2\} $ .

## 样例 #1

### 输入

```
3
1
11
123456
```

### 输出

```
0
1
127
```

# 题解

## 作者：lgswdn_SA (赞：2)

首先每一个有序的 fingerprint 唯一对应一个 password。所以我们只需要求出有多少个合法的不同排列即可。我们设这个 fingerprint 的集合大小为 $m$。合法的序列有以下两个条件：  

- $a_m\neq 0$
- $\forall i\in [1,m], a_i\le i$

第一个条件是因为若最后一位是 0，则在除以上一个数的时候就已经到 $0$ 了，显然不符合要求。第二个条件是因为余数小于被除数。 

最后一个 0 不好处理。我们考虑补集转换。首先不管最后一位是 0 的情况。

我们从大到小遍历每一个 fingerprint 中的位置（因为大的余数只能配大的除数，而小的余数谁都可以配）。设排完序的 fingerprint 为序列 $f$。那么 $f_i$ 这个数可以配可以配的 $m-i-(f_i-1)$ 个除数。还有我们要排除那些相同的余数所导致的重复计算。

$$
ans1=\prod_{i=0}^{m-1} \frac{m-i-\max(0,f_i-1)}{\sum_{j=0}^{i} [f_i=f_j]}
$$

然后我们减去等于 $0$ 的情况。我们只需要把出现的那个 0 给去掉，就能转化成上面一样的问题。

$$
ans2=[f_{m-1}=0]\prod_{i=0}^{m-2} \frac{m-1-i-\max(0,f_i-1)}{\sum_{j=0}^{i}[f_i=f_j]}
$$

由于题目要求 other keys，最终的答案为 $ans1-ans2-1$。

```cpp
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,k,f[209],s[209];

signed main() {
	T=read();
	while(T--) {
		k=read();
		int cnt=0;
		while(k) {
			f[cnt]=k%(cnt+2);
			k/=(cnt+2), cnt++;
		}
		sort(f,f+cnt); reverse(f,f+cnt);
		int lst=0;
		rep(i,0,cnt-1) {
			if(i==0||f[i]!=f[i-1]) lst=i;
			s[i]=i-lst+1;
		}
		int ans1=1, ans2=1;
		rep(i,0,cnt-1) ans1=ans1*max(0ll,cnt-i-max(0ll,f[i]-1))/s[i];
		if(f[cnt-1]!=0) ans2=0;
		else {
			rep(i,0,cnt-2) ans2=ans2*max(0ll,cnt-1-i-max(0ll,f[i]-1))/s[i];
		}
		printf("%lld\n",ans1-ans2-1);
	}
	return 0;
}
```

---

## 作者：panyf (赞：2)

简单组合数学题。

我们把所给数的 key 计算出来，按照题意模拟即可。将这个 key 打乱顺序，再还原回去，就可以得到 key 相同的数。

考虑打乱顺序后哪些 key 是合法的。

首先， key 的最后一位不能为 $0$ ，因为这样的话在前一位这个数就已经变成 $0$ 了，不符合题意。

由于 key 的每一位都代表一个余数，而除数是从 $2$ 开始的，所以第 $i$ 位的数不能大于 $i$ 。

满足以上两个条件的 key 都是合法的，因为我们一定能够通过这个 key 还原出原数。

考虑如何计算。我们从大到小枚举 key 中的数。设当前有 $j$ 个可用位置，枚举到 $i$ ， key 中有 $a$ 个 $i$ 。初始时答案为 $1$ ， $j=1$ 。那么我们可以从 $j$ 个位置选出 $a$ 个加入 $i$ ，所以答案乘上 $C(j,a)$ 。 每枚举完一个数，就增加一个可用位置（注意枚举到 $0$ 时可用位置不增加）。

考虑如何处理第一条限制。我们只需固定最后一位为 $0$ ，再按上述方法计算一遍，将答案减去不合法的个数即可。

注意要减去自己，因此答案最后要减 $1$ 。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll c[23][23];
int f[23];
int main(){
	int i,j,k,t;
	ll a,s,p;
	scanf("%d",&t);
	c[0][0]=1;
	for(i=1;i<21;++i){
		c[i][0]=1;
		for(j=1;j<=i;++j)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}//预处理组合数
	while(t--){
		memset(f,0,sizeof(f));
		scanf("%lld",&a),i=2,s=p=1;
		while(a)++f[a%i],a/=i,++i;
		k=i;
		for(i-=2,j=1;i>=0;--i,++j){
			if(!i)--j;
			s*=c[j][f[i]],j-=f[i];
		}//第一遍计算
		i=k-1,--f[0];
		if(f[k-2])p=0;
		else for(i-=2,j=1;i>=0;--i,++j){
			if(!i)--j;
			p*=c[j][f[i]],j-=f[i];
		}//第二遍计算
		printf("%lld\n",s-p-1);
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
所谓的简单组合计数题卡了我一下午。我是真被样例中的这个 $127$ 搞吐了。

翻译题意：  
卡尔正在开发一种密钥存储服务。每个用户都有一个正整数密钥。卡尔知道，用纯文本存储密钥是不好的做法。因此，他决定不存储密钥，而是存储密钥的指纹。

卡尔的指纹是这么计算的：对给定的整数先除以 $2$ 然后再除以 $3$ 再除以 $4$ 一直除下去直到结果为 $0$ 为止。

举个例子，例如 $11$ 是这么计算的：
- 首先 $11$ 除以 $2$ 的结果为 $5$ 余数为 $1$。
- 其次 $5$ 除以 $3$ 结果为 $1$ 余数为 $2$。
- 最后 $1$ 除以 $4$ 结果为 $0$ 余数为 $1$。

密钥的余数集合就是 $\left[1,2,1\right]$ 的样子。

有人认为用户的密钥很可能和最容易猜的密钥的指纹重合，即产生相同指纹。她想计算出给定的常用密钥列表中的每个密钥有多少个同样指纹的其他密钥。
## 分析。

前置知识：一是[组合数预处理](https://blog.csdn.net/jefferson__/article/details/119547754`)二是[组合数的原理](https://www.cnblogs.com/DL1024/p/16881791.html)然后阅读以下题解。

我们假定**排序过后的**余数序列 $A$ 称为不在乎顺序的余数序列，将**排序前的**余数序列 $B$ 称为在乎顺序的余数序列。

我们发现，对于任意一个序列 $B$ 其对应的数一定是唯一的，因为它就是一步步计算得来的，有固定的顺序。也就是说，我们只需要考虑将一个序列 $B$ 进行任意顺序的打乱后能得到的方案数。此时就很明显是组合数学了。

但是如果最后一个余数为 $0$ 即可以整除则该序列 $B$ 不满足要求，这类情况要被特判掉。那么我们现在的问题就是如何计算方案数：

假定一个情况，然后反证。

因为一个数模 $p$ 的余数肯定比 $p$ 小，所以越大的数有越少的选择。那么我们可以假定先取小一些的余数，但是又出现一个问题，就是我们没有办法确定这些小余数的位置，是否在大余数可以取到的位置上出现，这样就没有办法实时维护。做法伪了。

所以为了便于计算，我们就反其道而行之，考虑大余数，再考虑小余数。这样因为余数越大时，其可能包含的余数越大，则后选择的数的范围一定比最先选择的数的范围要大。

那么此时假设之前已经被抢占了 $N$ 个数，而且当前整个余数的序列长度为 $L$ 的同时，假设计算的当前余数为 $i$ 且当前已经抢占的余数的个数为 $tot_i$ 个。则有 $C_{L-N-i}^{tot_i}$ 个可能的方案数。然后去维护抢占的数 $N$ 和当前的余数 $i$ 即可。在此过程中，我们可以考虑最后一个余数为 $0$ 的情况，然后去掉它。

显然我们每次询问都要计算一次，考虑到数据范围，所以要预处理组合数。组合数可以用 $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$ 处理。因为要找的是与当前数列余数序列相同的数的方案数，所以要排除掉输入序列的情况。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
ll t,k;
ll cnt,ans;
ll tot[30],sum[30][30];
ll work(ll chdu){
	ll res=1,sed=0;
    for (int i=chdu;i>=1;i--){
    	ll q=chdu-i-sed;
        if(q<tot[i]){
	        return 0;
	    }
        if(tot[i]){
            res*=sum[q][tot[i]];
            sed+=tot[i];
        }//公式计算。
    }
    return res;
}
void init(){
	sum[0][0]=1;
    for (int i=1;i<=25;i++){
	    sum[i][0]=sum[i][i]=1;
	}
    for(int i=1;i<=25;i++){
	    for(int j=1;j<i;j++){
	    	sum[i][j]=sum[i-1][j]+sum[i-1][j-1];
	    }
	}
}//预处理。
int main(){
	init();
    cin>>t;
    while(t--){
        cnt=2;
        memset(tot,0,sizeof(tot));
        cin>>k;//多测不清空，样例过不去。
        while(k){
            tot[k%cnt]++;
            k/=cnt;
            cnt++;
        }
        ans=work(cnt-1);
        if(tot[0]){
            tot[0]--;
            ans-=work(cnt-2);
        }
        ans--;//特判掉自己。
        cout<<ans<<"\n";
    }
    return 0;
}
```
## 后记。
注意小细节，有缜密的思路，然后看看数据范围，这道题还是不难解决的。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：happybob (赞：0)

不懂啊，为啥要算组合数呢。

考虑到这个过程是可以还原的，于是每一个有序序列，只要最后一个结果不是 $0$，且每一次的余数都小于除数，就唯一对应一个初始的数。最后一个结果如果是 $0$，那么相当于最后 $i\mid k$，那么 $\dfrac{k}{i}$ 必然不是 $0$，此时还可以继续操作。

考虑对于输入的数求出序列，记为 $a$，长度为 $n$。发现我们要计算这个序列的本质不同排列数量，使得 $a_n \neq 0$ 且 $\forall 1 \leq i \leq n, a_i \leq i$。先忽略掉最后一个 $a_n \neq 0$ 的限制，直接算。枚举 $i$，考虑 $\leq i$ 的数的个数有 $c$ 个，则有 $c-(i-1)$ 的贡献。这样会算重，设每个数出现次数为 $d_i$，除以 $\prod \limits_{i} d_i!$ 即可。

然后加上限制，直接容斥，强制最后选 $0$ 把方案数减去即可。

[Submission Link](https://codeforces.com/contest/1267/submission/266185662)。

---

## 作者：Reunite (赞：0)

简单题

## 零
---
翻译：

给一个数 $k$，定义由 $k$ 生成的可重集合 $S$ 为：$i$ 从 $2$ 开始，若 $k$ 不为 $0$，则 $S$ 中加入一个元素 $k \bmod i$，然后 $k \leftarrow \lfloor \frac{k}{i} \rfloor$，$i \leftarrow i+1$。

多组询问，每次询问一个 $k$，求有多少个不同的数 $x$（$x \neq k$），使得 $x$ 与 $k$ 的可重集相同。

## 一
---

首先需要观察到一个性质，那就是若将 $S$ 中的元素以加入集合的顺序排列的话，数 $k$ 与可重集 $S$ 是一一对应的。其实很显然，因为整个生成过程就是唯一确定的，类似于保留了余数和商，被除数就是确定的。

先求出询问的 $k$ 的可重集 $S$，大小为 $n$，那问题就转化为，有多少种由 $S$ 中的元素组成的合法序列。然后就是两个约束了：

- $S_n \ne0$，反证，若 $S_n=0$，则最后一步的时候 $(n+1)|k$，若 $k=0$，那在上一步的时候就应该停止了；若 $k \neq 0$，那么 $\lfloor \frac{k}{n+1} \rfloor$ 至少为 $1$，那还可以进行下一步。矛盾，得证。

- $S_i<i+1$，显然余数得小于除数吧。

那么直接计数就好了！不妨从大到小钦定元素，因为这样的话钦定过的元素的具体位置并不影响之后的操作。设目前有 $cnt$ 个空，那么方案数乘上一个 $\binom{cnt}{h_i}$，$h_i$ 就是值为 $i$ 的元素个数。然后更新一下 $cnt$ 就行。

这样算的是只考虑第二个限制的方案，一步容斥，钦定最后一个位置必填 $0$，将方案数减去这种情况即可。其实写的时候只需要把 $cnt$ 初值设为 $-1$ 即可。

## 二
---

显然 $k$ 是 $n!$ 级别的，时间复杂度 $O(20t)$，$20$ 是 $n$ 的大小。

```cpp
	while(k) h[k%(n+2)]++,k/=(n+2),n++;
	ll ans1=1,ans2=1;
	int cnt=0;
	for(int i=n;i>=1;i--){
		cnt++;
		ans1*=C[cnt][h[i]];
		cnt-=h[i];
	}
	cnt=-1;
	for(int i=n;i>=1;i--){
		cnt++;
		ans2*=C[cnt][h[i]];
		cnt-=h[i];
	}
	printf("%lld\n",ans1-ans2-1);

```

---

