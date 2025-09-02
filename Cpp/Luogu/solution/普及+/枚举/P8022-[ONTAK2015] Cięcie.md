# [ONTAK2015] Cięcie

## 题目描述

给定一个长度为 $k$ 的数字串 $N$ 以及三个**质数** $p, q, r$，请你将 $N$ 划分为三段非空字符串，使得第一段能被 $p$ 整除，第二段能被 $q$ 整除，第三段能被 $r$ 整除，且每一段都不含前导 $0$。

注：**单独的 $0$ 是允许的**。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq k \leq 10^6$，$2015 < p, q, r \leq 10^5$，$p, q, r$ 为**质数**。

## 样例 #1

### 输入

```
19 2017 2027 2029
2017202741127832029```

### 输出

```
2```

# 题解

## 作者：wjr_jok (赞：3)

## 题意

将一个长度为 $k$ 的数字串 $N$ 划分为三段非空字符串，使得第一段能被 $p$ 整除，第二段能被 $q$ 整除，第三段能被 $r$ 整除，且每一段都不含前导 $0$。

## 思路

### $step1$：

从前往后枚举求出第一段成立的情况，再从后往前枚举出第三段成立的情况，并记录他们的位置。

### $step2$：

当知道了第一段和第三段的位置后第二段就确定了，那么只需判断是否合法即可。

### $step3$：

优化枚举过程。由于枚举第一，三段都是从左往右的，那么如果当前的第三段和第一段相交，那么它和后面的第一段也一定相交。

同样，如果当前的第二段有前导 0，而向后枚举第三段时只会让第二段向后延伸，仍然会有前导 0。

### $step4$：

进一步优化时间复杂度，使用前缀和来 $O(1)$ 求取余数：由于取余运算满足结合律，我们可以把取余运算分开来操作。

我们用到两个数组 $qzh$ 和 $ac$，分别表示数字串前 $i$ 位组成的数字对 $q$ 取余的结果和 $10^i$ 对 $q$ 取余的结果。

求解数字串第 $i \sim j$ 位组成的数字对 $q$ 取余的结果如下：

$$
(qzh_{j} - qzh_{i-1} \times ac_{j-i+1} \bmod q + q) \bmod q
$$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6;
int k,p,q,r,cnt,ans,jl;
char s;
int xl[N],fst[N],lst[N],qzh[N],ac[N];//fst 记录第一段成立情况的位置,lst 记录第三段成立情况的位置 
int cf(int x){
	jl=(jl*10)%r;
	return jl;
}
signed main(){
	cin>>k>>p>>q>>r;
	for(int i=1;i<=k;i++){//使用 char 类型来读入无空格数据 
		cin>>s;
		xl[i]=s-'0';
	}
	ac[0]=1;
	for(int i=1;i<=k;i++){//预处理余数，qzh 记录由 1~i 位组成的数取余q的结果，ac 记录 10^i 取余 q 的结果,用取余运算的结合律来 O(1) 求余数 
		qzh[i]=(qzh[i-1]*10+xl[i])%q;
		ac[i]=(ac[i-1]*10)%q;
	}
	for(int i=1;i<=k;i++){//枚举第一段 
		cnt=(cnt*10+xl[i])%p;
		if(!cnt){
			fst[++fst[0]]=i;
		}
	}
	cnt=0,jl=1;
	for(int i=k;i>=1;i--){//枚举第三段 
		cnt=(cnt+xl[i]*cf(k-i))%r; 
		if(!cnt&&(xl[i]||i==k)){
			lst[++lst[0]]=i;
		}
	}
	for(int i=1;i<=fst[0];i++){//判断第二段 
		for(int j=lst[0];j>=1;j--){
			if(fst[i]>=lst[j]-1){//优化，以免多次访问相交情况
				lst[0]--;
				continue;
			}
			if(!xl[fst[i]+1]&&fst[i]<lst[j]-2){//优化以免多次访问有前导 0 情况
				break;
			}
			if(!((qzh[lst[j]-1]-qzh[fst[i]]*ac[lst[j]-fst[i]-1]+q)%q)){//成立，使用前缀和预处理余数，同样使用取余运算的结合律 
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lyhqwq (赞：2)

# Solution
这题题解都是什么唐，写一篇正解。

考虑预处理出所有符合要求的前缀 $[1,i]$ 和后缀 $[j+1,n]$，现在只需要判断 $[i+1,j]$ 是否符合条件即可。

即 $q \mid \sum\limits_{k=i+1}^{j} a_i \times 10^{j-k}$。

把式子拆开，得到 $q\mid10^j \sum\limits_{k=i+1}^{j}a_i\times10^{-k}$。

显然有 $q\nmid 10^j$，令 $sum_i=\sum\limits_{j=1}^i a_j\times 10^{-j}$，可以得出 $sum_i \equiv sum_j \pmod q$。

开桶子计算即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,p,q,r,ans;
int a[N],cnt[N],vis[N],sum[N],suf[N];
int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%q) if(b&1) ans=1ll*ans*a%q;
    return ans;
}
int main(){
    scanf("%d%d%d%d",&n,&p,&q,&r);
    for(int i=1;i<=n;i++) scanf("%1d",&a[i]),sum[i]=(sum[i-1]+1ll*a[i]*qpow(qpow(10,i),q-2)%q)%q;
    for(int i=n,x=0,base=1;i>=3;i--,base=1ll*base*10%r){
        x=(x+1ll*a[i]*base%r)%r;
        if(!x&&(a[i]||i==n)) cnt[sum[i-1]]++,vis[i]=1;
        suf[i]=x;
    }
    for(int i=1,x=0;i<=n-2;i++){
        x=(x*10%p+a[i])%p;
        if(vis[i+1]) cnt[sum[i]]--;
        if(!x&&(a[1]||i==1)){
            if(a[i+1]) ans+=cnt[sum[i]];
            else ans+=(!suf[i+2]&&(a[i+2]||i+2==n));
        }
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：_EternalRegrets_ (赞：0)

## P8022 题解

### 题意描述：
>给定一个数字串 $N$ 和三个质数 $p,q,r$。将这个数字串分割为三个没有前导零的部分，使得这三个部分依次被 $p,q,r$ 整除。

### Solution:
对于 $p$ 和 $q$ 的整除条件，直接从前到后、从后到前得到可行的分割点。

现在只需要检验对于每一个 $p$ 与 $q$ 的分割点，中间的部分是否被 $q$ 整除即可。

可以用类似哈希的方法，用 $pre_i$ 记录前 $i$ 个数码组成的数字模 $q$ 的余数，即可 $O(1)$ 检验。

### code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int qpow(int a,int b,int mod){
	if(b==1){
		return a;
	}
	
	if(b==0){
		return 1;
	}
	
	int x; x=qpow(a,b/2,mod)%mod;
	
	if(b%2==0){
		return x*x%mod;
	} 
	else{
		return x*x%mod*a%mod;
	}
} 

vector <int> pp,rr;
int pre[1000005];

signed main(){
	int k,p,q,r; cin>>k>>p>>q>>r;
	string s; cin>>s; s=" "+s;
	
	int num; num=0;
	
	if(s[1]!='0'){//如果第一位是0，那第一个区间只可以是0
		for(int i=1;i<=k;i++){
			num=((num*10%p)+s[i]-'0')%p;
			if(num==0){
				pp.push_back(i);
			}
		}
	}
	else{
		pp.push_back(1);
	}
	
	num=0;
	for(int i=k;i>=1;i--){
		num=(num+(s[i]-'0')*qpow(10,k-i,r)%r)%r;
		
		//cout<<num<<endl;
		if(num==0 && (s[i]!='0' || i==k)){
			rr.push_back(i);
		} //i==k是最后一个区间为0的情况
	}
	
	//cout<<pp.size()<<" "<<rr.size();
	
	for(int i=1;i<=k;i++){
		pre[i]=((pre[i-1]*10%q)+s[i]-'0')%q;
	} 
	
	int ans; ans=0;
	for(int i=0;i<pp.size();i++){
		for(int j=rr.size()-1;j>=0;j--){
			//cout<<pp[i]<<" "<<rr[j]<<endl;
			if(pp[i]>=rr[j]-1){
				continue;
			}
			
			if(s[pp[i]+1]=='0' && pp[i]<rr[j]-2){
				break;
			}
			
			if((pre[rr[j]-1]-pre[pp[i]]*qpow(10,rr[j]-pp[i]-1,q)+q)%q==0){
				ans++;
			}
		}
	}
	
	cout<<ans;
	return 0;
}
```

---

