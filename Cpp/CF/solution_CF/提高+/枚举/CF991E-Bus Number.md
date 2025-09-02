# Bus Number

## 题目描述

This night wasn't easy on Vasya. His favorite team lost, and he didn't find himself victorious either — although he played perfectly, his teammates let him down every time. He had to win at least one more time, but the losestreak only grew longer and longer... It's no wonder he didn't get any sleep this night at all.

In the morning, Vasya was waiting the bus to the university on the bus stop. Vasya's thoughts were hazy and so he couldn't remember the right bus' number quite right and got onto the bus with the number $ n $ .

In the bus, Vasya thought that he could get the order of the digits in the number of the bus wrong. Futhermore, he could "see" some digits several times, but the digits he saw were definitely in the real number of the bus. For example, if Vasya saw the number 2028, it could mean that the real bus number could be 2028, 8022, 2820 or just 820. However, numbers 80, 22208, 52 definitely couldn't be the number of the bus. Also, real bus number couldn't start with the digit 0, this meaning that, for example, number 082 couldn't be the real bus number too.

Given $ n $ , determine the total number of possible bus number variants.

## 说明/提示

In the first sample, only variants $ 97 $ and $ 79 $ are possible.

In the second sample, the variants (in the increasing order) are the following: $ 208 $ , $ 280 $ , $ 802 $ , $ 820 $ , $ 2028 $ , $ 2082 $ , $ 2208 $ , $ 2280 $ , $ 2802 $ , $ 2820 $ , $ 8022 $ , $ 8202 $ , $ 8220 $ .

## 样例 #1

### 输入

```
97
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2028
```

### 输出

```
13
```

# 题解

## 作者：flora715 (赞：7)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
/*【E. Bus Number】
如果看到数字2028，它可能意味着实际的车号可能是2028,8022,2820或者仅仅是820。
然而，80号、22208号、52号肯定不是这辆车的号码。
而且，实际的车号不能以数字0开头，例如，数字082不能也是实际的车号。
给定看到的数字n，求出所有可能的车号种数。 */
 
 
/*【分析】
1.统计0~9出现的次数，按题意枚举每个数分别出现多少个，
对于每个情况设一共有sum个数字，A[i]为数字i出现的次数，
那么有sum!/（A[0]!*A[1]!*...*A[9]!）种[不考虑前导0情况下]
2.考虑计算有前导0的情况，把非0的数仿照上边的方法求出排列数，
然后把一个0放到开头固定，剩余的0插空放在这sum个数之间即可，
把上面两个值相减就是答案。  */
 
int num[10],tempNum[10];
ll jc[20],ans=0; //阶乘求出来的值用jc数组记录 
 
void dfs(int x){ //从0~9寻找各数字的出现
    if(x==10){ //0~9都寻找完毕了
        int cnt=0; //cnt记录所有数字的个数
        for(int i=0;i<10;++i) cnt += tempNum[i];
        
        ll p=jc[cnt]; //p为这种情况的临时记录变量
        for(int i=0;i<10;++i) p/=jc[tempNum[i]];
        //↑↑↑ sum!/（A[0]!*A[1]!*...*A[9]!）
        if(tempNum[0]>=1) p-=(p*tempNum[0]/cnt); 
        
        ans+=p; return; //完成计算，返回答案
    }
    for(int i=1;i<=num[x]; ++i){
        tempNum[x]=i; dfs(x+1); //某看到的数字可能有1~num个 
        //【巧妙】直接用递归解决多层次的问题
    }
    if(num[x]==0) dfs(x+1);
}
 
int main(){
    string s; cin>>s; //字符串用于输入
    int len=s.size(); //↓↓求出现次数
    for(int i=0;i<len;i++) num[s[i]-'0']++; 
    jc[0]=1; //阶乘
    for(int i=1;i<=19;i++) jc[i]=jc[i-1]*i; //ll存的下
    dfs(0); cout<<ans<<endl;
    return 0;   
}
```

---

## 作者：Textbook_blasphemy (赞：2)

## 题意简述
   给一个数字序列，问有多少个序列 $B$ 满足:
   
   ① $A$ 中所有数字都一定要在 $B$ 中出现过。
   
   ② $B$ 中所有数字也一定要在 $A$ 中出现过。
   
   ③ 序列 $B$ 不能以 $0$ 开头。
   
## 分析

 
 进一步简化题意:求在 $n$ 个可能**有重复**的数字中求开头**不为 $0$ **的**排列**总数。
 
 假设开头可以为 $0$ ，那么答案就是：
 $$ans=\frac{sum!}{\prod_{i=1}^{9}{num [i]}}$$
解释：$sum$ 为数字总数，$num$ 数组表示 $i$ 数字有 $num_i$ 个。

 接下来考虑开头不能为 $0$ 的情况。
 
 直接算开头不能为 $0$ 的情况比较棘手，考虑容斥原理（即总方案数减去开头为 $0$ 的方案数）。
 
 先把不为$0$的数按照开头可以为 $0$ 的情况处理，把一个 $0$ 放在开头，剩下的 $0$ 往后放置，统计数量，得出的结果便是开头为 $0$ 的情况。
 
 最后将总方案的数量减去开头为 $0$ 的数量即为答案。
 
## Code

注: $19!=121645100408832000$ ，不炸`long long` ，**不用写高精**。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;//输入的数当作字符串,方便处理 
int num[10];//每个数字出现的次数 
int slen;//n的位数 
int num_t[10];//因为num数组会改变,设置另一个num数组 
ll Fac[20]={1};//阶乘(Factorial),f[0]=1; 
ll ans=0;
void work(int x){
	if(x>9){//如果0~9统计完了 
		int cnt=0;//现在的总位数 
		for(int i=0;i<=9;i++){
			cnt=cnt+num_t[i];
		}
		ll tmp=Fac[cnt];//求总情况 
		for(int i=0;i<=9;i++){
			tmp=tmp/Fac[num_t[i]]; 
		}
		if(num_t[0]>=1)tmp=tmp-(tmp*num_t[0]/cnt);//最后,统计开头为0的情况 
		ans=ans+tmp;//相加 
		return;
	} 
	for(int i=1;i<=num[x];i++) {//当前数字出现过 
		num_t[x]=i;//设置成当前数字 
		work(x+1);
	}
	if(num[x]==0)work(x+1);
} 
int main(){
	cin>>s; 
	slen=s.size(); 
	for(int i=0;i<slen;i++){//字符串便于处理 
		num[s[i]-'0']++;
	}
	for(int i=1;i<=19;i++){//统计阶乘,方便算组合数 
		Fac[i]=Fac[i-1]*i;
	}
	work(0);
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：dxrS (赞：2)

$n\le18$，容易想到枚举子集。

首先得到所有一位数再子集中的出现次数 $cnt$。求出子集中元素总数 $c_1$ 和非 $0$ 元素总数 $c_2$。

首先，不能有前导 $0$，所以第一位就是 $c_2$ 种情况，剩下 $c_1-1$ 个元素可以随便排列，所以就是 $c_1-1$ 的全排列。

但是，对于数 $i$，两个 $i$ 交换得到的答案是同一个，所以还要除上 $\prod\limits_{i=0}^9A_{cnt_i}^{cnt_i}$。

综上，答案为 $\dfrac{c_2\times A_{c_1-1}^{c_1-1}}{\prod\limits_{i=0}^9A_{cnt_i}^{cnt_i}}$。

注意对于两个**完全**相同的 $cnt$，需要去重，时间复杂度 $O(n2^n\log n)$。

---

## 作者：Autream (赞：0)

#### 题意简述
给定一个序列 $A$，求构成序列 $B$ 的方案数。满足：
1. $B$ 中的数字在 $A$ 中出现过。
2. $A$ 中数字在 $B$ 中也出现过。
3. 不含前导 $0$。

---
#### 题目分析
考虑先不管第 $3$ 条限制，如果当前有 $sum$ 个数字，每个数字 $i \in [0,9]$ 出现了 $a_i$ 次，那么总排列数就是 $\frac{sum!}{\prod \limits ^9 _{i=0} a_i}$。
接下来考虑含前导 $0$ 的情况。
由于一共有 $sum$ 个数字，其中 $0$ 有 $a_0$ 个，那么 $0$ 开头的排列数就占所有排列数 $p$ 的 $\frac{a_0}{sum}$ 个（对于 $sum$ 中每个数都有以它为开头的对应排列，那么以 $0$ 开头的就有 $a_0$ 个），所以就需要从 $p$ 中减去 $p \times \frac{a_0}{sum}$。

暴力搜索 $B$ 中每个数有多少个就行。

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)a[i]=read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
CI N=30;
std::string s;
int ans,a[N],cnt[N],fac[N];
void dfs(int x){
    if(x>9){
        int sum=0;
        rep(i,0,9){
            sum+=a[i];
        }
        int p=fac[sum];
        rep(i,0,9){
            p/=fac[a[i]];
        }
        if(a[0]){
            p-=p*a[0]/sum;
        }
        ans+=p;
        return ;
    }
    rep(i,1,cnt[x]){
        a[x]=i;
        dfs(x+1);
    }
    if(!cnt[x]){
        dfs(x+1);
    }
}
signed main() {
    std::cin>>s;
    rep(i,0,s.size()-1) {
        cnt[s[i]-'0']++;
    }
    fac[0]=1;
    rep(i,1,20){
        fac[i]=fac[i-1]*i;
    }
    dfs(0);
    std::cout<<ans;
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf991e-bus-number-de-ti-jie/)
## 题目大意
给定一个全数字字符串 $s1$，假设数字 $i$ 出现了 $a_i$ 次。

现在要求构造全数字字符串 $s2$，假设数字 $i$ 出现了 $b_i$ 次。

那么 $b$ 满足一下要求
- 对于 $i\in[0,9]$，$b_i\le a_i$
- $a_i\ne 0$ 时 $b_i\ne 0$
-  $s2_{1}\ne 0$
## 思路
首先需要明确如何求解一个字符串的全排列。

假设字符串 $s$ 长度为 $n$，其全排列个数为 $f(s)$。

如果 $i,j\in[1,n],i\ne j$ 满足 $s_i\ne s_j$，那么 $f(s)=n!$。

因为对于第 $i$ 次选择时，在以前的选择中已经选择了 $i-1$ 个元素，那么对于这次选择就只有 $n-i+1$ 个元素可以选择了。

假设 $g_i$ 表示选择了 $i$ 次的方案数，因为乘法原理，$g_i=g_{i-1}\cdot (n-i+1)$。

所以 $g_n=f(s)=n\times  (n-1)\times \cdots \times 2 \times 1$。

对于不满足 $i,j\in[1,n],i\ne j$ 满足 $s_i\ne s_j$ 的情况，那么假设字符 $i$ 出现了 $a_i$ 次。

$$f(s)=n!-\sum_{i\in a} a_i!$$

因为将任意两个重复的元素交换得到的方案其实是一样的，所以需要将多余的方案减掉。

对于重复的可能性，其实就是对于这些重复的元素自己的看重顺序的全排列数量，所以就是 $a_i!$。

具体的对于这道题目，因为 $n$ 非常的小，可以使用 dfs 暴力枚举出所有字符串使用每一个元素的次数，那么答案就是所有元素的全排列减去以 $0$ 作为开头的排列个数。

$$ans=\cfrac{(\sum_{i=0}^{9}a_i)!}{\prod_{i=0}^{9}a_i! }-\cfrac{[(\sum_{i=0}^{9}a_i)-1]!}{(a_0-1)!\cdot\prod_{i=1}^{9}a_i! }$$

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int n,s[N],ans,f[N],jc[N];
char a[N];
void init(){
    jc[0]=1;
    for(int i=1;i<N;i++){
        jc[i]=jc[i-1]*i;
    }
}
void dfs(int x){
    if(x==10){
        int tot=0;
        for(int i=0;i<=9;i++){
            tot+=f[i];
        }
        int sum=jc[tot];
		for(int i=0;i<=9;i++){
			sum/=jc[f[i]];
		}
		if(f[0]>0){
			int num=jc[tot-1]/jc[f[0]-1];
			for(int i=1;i<=9;i++){
                num/=jc[f[i]];
            }
			sum-=num;
		}
		ans+=sum;
		return;
    }
    for(int i=1;i<=s[x];i++){
        f[x]=i;
        dfs(x+1);
    }
    if(!s[x]){
        dfs(x+1);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>a+1,n=strlen(a+1);
    init();
    for(int i=1;i<=n;i++){
        s[a[i]-'0']++;
    }
    dfs(0);
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ThisIsLu (赞：0)

这是一篇使用 DP 的题解。



设 $a_i$ 表示数码 $i$ 出现的次数，$f(i+1,j,0/1)$ 表示考虑到 $0$ 到 $i$ 的数字，填了 $j$ 个数字的方案数且考虑 / 不考虑前导零。

先考虑 $a_i=0$ 的情况，显然转移为：

$$f(i+1,j,0)=f(i,j,0)$$

$$f(i+1,j,1)=f(i,j,1)$$

对于不考虑前导零，转移的时候枚举用 $k$ 个 $i$，在 $j$ 个位置里选 $k$ 个填 $i$，方案数即 $\binom{j}{k}$，设 $a_i$ 表示数码 $i$ 出现的次数，转移方程为：

$$f(i+1,j,0)=\sum_{k=1}^{a_i}\binom{j}{k}f(i,j-k,0)$$


特别地，$f(0,0,0)=1$，其它置 $0$。

对于考虑前导零的，还是先枚举用 $k$ 个 $i$，可以按选的位置里是否包含首位分为两种情况：

- 对于不包含的，方案数为 $\binom{j-1}{k}$，贡献为 $\binom{j-1}{k}f(i,j-k,1)$。

- 对于包含的，方案数为 $\binom{j-1}{k-1}$，贡献为 $\binom{j-1}{k-1}f(i,j-k,0)$。

综上，转移为：

$$f(i+1,j,1)=\sum_{k=1}^{a_i}\binom{j-1}{k-1}f(i,j-k,0)+\binom{j-1}{k}f(i,j-k,1)$$

处理下边界情况：如果 $a_0 \not= 0$，那么 $f(1,i,1)$ 全部置 $0$，否则使用 $a_i=0$ 的转移。

放一下代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
char ch[20];
int n,a[10];
long long f[11][20][2],c[20][20];
int slove(){
    f[0][0][0]=1;
    for(int i=0;i<10;i++){;
        if(a[i]){
            for(int j=0;j<=n;j++){
                f[i+1][j][0]=0;
                for(int k=1;k<=min(a[i],j);k++){
                    f[i+1][j][0]+=c[j][k]*f[i][j-k][0];
                }
            }
            if(i==0){
                for(int j=0;j<=n;j++){
                    f[1][j][1]=0;
                }
            }
            else{
                for(int j=0;j<=n;j++){
                    f[i+1][j][1]=0;
                    for(int k=1;k<=min(a[i],j);k++){
                        f[i+1][j][1]+=c[j-1][k-1]*f[i][j-k][0]+c[j-1][k]*f[i][j-k][1];
                    }
                }
            }
        }
        else{
            for(int j=0;j<=n;j++){
                f[i+1][j][0]=f[i][j][0];
                f[i+1][j][1]=f[i][j][1];
            }
        }
    }
    long long ans=0;
    for(int i=0;i<=n;i++){
        ans+=f[10][i][1];
    }
    return ans;
}
signed main(){
    cin>>(ch+1);
    n=strlen(ch+1);
    for(int i=1;i<=n;i++){
        a[ch[i]-'0']++;
    }
    c[0][0]=1;
    for(int i=1;i<20;i++){
        c[i][0]=1;
        for(int j=1;j<=20;j++){
            c[i][j]=c[i-1][j]+c[i-1][j-1];
        }
    }
    long long ans=slove();
    cout<<ans;
    return 0;
}
```
（不过这方法还跑不过 dfs 的样子）

---

## 作者：Grisses (赞：0)

[题面](https://www.luogu.com.cn/problem/CF991E)

发现长度只有 $18$，直接暴搜加上可重集排列。

### 可重集排列

若不同的数共有 $n$ 种，第 $i$ 种有 $a_i$ 个。

则总排列数为 $\dfrac{(\sum\limits_{i=1}^na_i)!}{\prod\limits_{i=1}^na_i!}$。

显然是这样，总排列除去每种数内部重复的情况。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,cnt,sum[15],las[15];
  long long ans,C[25];
  void dfs(int x){
      if(x==10){
          long long res=C[cnt];
          for(int i=0;i<=9;i++)res/=C[las[i]];
          if(las[0]){
              long long h=C[cnt-1];
              las[0]--;
              for(int i=0;i<=9;i++)h/=C[las[i]];
              res-=h;
              las[0]++;
          }//可重集排列
          ans+=res;
          return;
      }
      int k=cnt;
      for(int i=(sum[x]!=0);i<=sum[x];i++){
          las[x]=i;
          cnt=k+i;
          dfs(x+1);//暴力枚举
      }
      cnt=k;
  }
  signed main()
  {
      int x;
      while(scanf("%1d",&x)!=EOF)n++,sum[x]++;
      C[0]=1;
      for(int i=1;i<=20;i++)C[i]=C[i-1]*i;
      dfs(0);
      printf("%lld",ans);
      return 0;
  }

```

---

## 作者：bwartist (赞：0)

发现 $n$ 很小。所以考虑对数字 $1$~$9$ 在答案中的出现次数进行搜索。

对数字 $1$~$9$ 枚举每个数字的出现次数：记 $sum_i$ 为数字 $i$ 在 $A$ 中的出现次数$(0\leq i\leq 9)$，故 **$i$ 在 $B$ 中出现次数为 $1$~$sum_i$.**

确定了每个数次的出现次数后需要让这些数字按照一定顺序排列，则是[多重集的排列数](https://oi-wiki.org/math/combinatorics/combination/#%E5%A4%9A%E9%87%8D%E9%9B%86%E7%9A%84%E6%8E%92%E5%88%97%E6%95%B0--%E5%A4%9A%E9%87%8D%E7%BB%84%E5%90%88%E6%95%B0)。

不考虑重复数字，总排列方案为所有数字的总数的阶乘 $(\sum a_i)!$。考虑重复，设数字 $i$在整个排列里有 $a_i$ 个，那么这 $a_i$ 个 $i$ 交换位置后（改变相对位置）真实方案是不会改变的，真实方案就是总方案除以他们交换位置后的方案数，他们交换位置后的方案数是 $a_i!$。

所以，排列的真实方案数为:所有数字总数的阶乘 $(\sum a_i)!$ 除以 每个数字的数量的阶乘的乘积 $\prod  a_i!(0\leq i\leq 9)$.即：
$$ans=\frac{(\sum a_i)!}{\prod  a_i!}(0\leq i\leq 9)$$
然而为了使首位不为 $0$，需要减去“首位为 $0$”这种不合法情况；不合法情况就相当于把数字 $a_0$ 减一后的 $ans$，（有一个 $0$ 放在了第一位）。注意此 $ans$ 非彼 $ans$,这里的 $ans$ 是**不合法的情况数量**，只是用刚刚计算总 $ans$ 的方法在计算而已。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[25];
int n,a[15],sum[15];
ll fac[25],ans;
void dfs(int x,int tot){
	if(x==10){
		ll now=fac[tot];
		for(int i=0;i<=9;i++){
			now/=fac[a[i]];
		}
		if(a[0]>0){
			ll jian=fac[tot-1]/fac[a[0]-1];
			for(int i=1;i<=9;i++)	jian/=fac[a[i]];
			now-=jian;
		}
		ans+=now;
		return;
	}
	if(sum[x]==0){
		dfs(x+1,tot);
		return;
	}
	for(int i=1;i<=sum[x];i++){
		a[x]=i;
		dfs(x+1,tot+i);
	}
}
int main(){
	fac[0]=1;
	for(int i=1;i<=20;i++)	fac[i]=fac[i-1]*i;
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)	sum[s[i]-'0']++;
	dfs(0,0);
	printf("%lld",ans);
	return 0;
}
```


---

