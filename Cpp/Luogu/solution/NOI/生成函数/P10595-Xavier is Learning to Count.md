# Xavier is Learning to Count

## 题目描述

集合 $S$ 内有 $m$ 个互异整数。请对于任意整数 $i$ 求出 $S$ 内满足大小为 $p$ 且元素和为 $i$ 的子集数量。

## 样例 #1

### 输入

```
3
3 3
1 2 3
5 4
1 3 5 6 7
10 3
1 2 3 4 5 6 7 8 9 10```

### 输出

```
Case #1:
6: 1

Case #2:
15: 1
16: 1
17: 1
19: 1
21: 1

Case #3:
6: 1
7: 1
8: 2
9: 3
10: 4
11: 5
12: 7
13: 8
14: 9
15: 10
16: 10
17: 10
18: 10
19: 9
20: 8
21: 7
22: 5
23: 4
24: 3
25: 2
26: 1
27: 1```

# 题解

## 作者：dAniel_lele (赞：1)

#### 勘误 2024.6.22：时间复杂度应为 $O(p^2V+pV\log (pV))$。感谢 @NaCly_Fish。

问题的难点在于如何钦定每个位置不被重复选。否则就是直接看作是多项式，进行卷积即可。

考虑容斥，钦定某些点被选 $1\sim p$ 次。这类所有点不等的容斥系数，钦定某个点出现 $x$ 次时系数为 $(-1)^{x-1}(x-1)!$。可以使用动态规划计算出。

注意到卷积时暴力 $O(p^2V\log V)$ 无法通过。我们需要点值的多项式只有 $O(p)$ 个。于是先把所有初始多项式转化成点值的形式，然后进行 dp 后只在 $p$ 位置 IDFT 回来即可。

总复杂度 $O(p^2V+pV\log(pV))$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int __int128
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
int read(){
	long long x; cin>>x;
	return x;
}
void print(int x){
	cout<<(long long)x;
}
namespace Conv{
    typedef long long ll;
    const int mod=4179340454199820289,N=1050000,g=3,invg=(mod+1)/3;
    int wk[N+5],ta[N+5],tb[N+5];
    int Power(int x,int y){
    	int r=1;
    	while(y){
    		if(y&1)r=1ll*r*x%mod;
    		x=1ll*x*x%mod,y>>=1;
    	}
    	return r;
    }
    void DFT(int *a,int n){
    	for(int i=n>>1;i;i>>=1){
    		int w=Power(g,(mod-1)/(i<<1));
    		wk[0]=1;
    		for(int j=1;j<i;j++)wk[j]=1ll*wk[j-1]*w%mod;
    		for(int j=0;j<n;j+=(i<<1)){
    			for(int k=0;k<i;k++){
    				int x=a[j+k],y=a[i+j+k],z=x;
    				x+=y,(x>=mod&&(x-=mod)),a[j+k]=x;
    				z-=y,(z<0&&(z+=mod)),a[i+j+k]=1ll*z*wk[k]%mod;
    			}
    		}
    	}
    }
    void IDFT(int *a,int n){
    	for(int i=1;i<n;i<<=1){
    		int w=Power(invg,(mod-1)/(i<<1));
    		wk[0]=1;
    		for(int j=1;j<i;j++)wk[j]=1ll*wk[j-1]*w%mod;
    		for(int j=0;j<n;j+=(i<<1)){
    			for(int k=0;k<i;k++){
    				int x=a[j+k],y=1ll*a[i+j+k]*wk[k]%mod,z=x;
    				x+=y,(x>=mod&&(x-=mod)),a[j+k]=x;
    				z-=y,(z<0&&(z+=mod)),a[i+j+k]=z;
    			}
    		}
    	}
    	for(int i=0,inv=Power(n,mod-2);i<n;i++)a[i]=1ll*a[i]*inv%mod;
    }
    vector<int> conv(vector<int> A,vector<int> B){
    	int sa=A.size(),sb=B.size();
    	vector<int> ret(sa+sb-1);
    	int len=1;
    	while(len<ret.size())len<<=1;
    	for(int i=0;i<len;i++)ta[i]=tb[i]=0;
    	for(int i=0;i<sa;i++)ta[i]=A[i];
    	for(int i=0;i<sb;i++)tb[i]=B[i];
    	DFT(ta,len),DFT(tb,len);
    	for(int i=0;i<len;i++)ta[i]=1ll*ta[i]*tb[i]%mod;
    	IDFT(ta,len);
    	for(int i=0;i<ret.size();i++)ret[i]=ta[i];
    	while(ret.size()>A.size()) ret.pop_back();
    	return ret;
    }
    vector<int> getdft(vector<int> A,int len){
    	for(int i=0;i<len;i++)ta[i]=0;
    	for(int i=0;i<A.size();i++)ta[i]=A[i];
    	DFT(ta,len);
    	A.resize(len);
    	for(int i=0;i<len;i++) A[i]=ta[i];
    	return A;
	}
    vector<int> getidft(vector<int> A,int len,int alen){
    	for(int i=0;i<len;i++)ta[i]=0;
    	for(int i=0;i<A.size();i++)ta[i]=A[i];
    	IDFT(ta,len);
    	A.resize(alen);
    	for(int i=0;i<alen;i++) A[i]=ta[i];
    	return A;
	}
    vector<int> add(vector<int> A,vector<int> B){
    	if(A.size()!=B.size()) exit(2);
    	for(int i=0;i<B.size();i++) (A[i]+=B[i])%=mod;
    	return A;
	}
    vector<int> mul(vector<int> A,int B){
    	for(int i=0;i<A.size();i++) (A[i]*=B)%=mod;
    	return A;
	}
}
const int mod=4179340454199820289;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[6],C[6][6];
void solve(){
	int n=read(),m=read();
	int maxv=0; vector<int> vc;
	for(int i=1;i<=n;i++){
		int x=read(); vc.push_back(x);
		maxv=max(maxv,x);
	}
	vector<int> a[6],b[6];
	vector<int> ap[6],bp[6];
	for(int i=0;i<=m;i++){
		while(a[i].size()<maxv*m+1) a[i].emplace_back(0);
		while(b[i].size()<maxv*m+1) b[i].emplace_back(0);
	}
	int f=a[0].size()*2-1;
	int len=1;
	while(len<f) len<<=1;
	for(int i=0;i<=m;i++) while(bp[i].size()<len) bp[i].emplace_back(0);
	for(int i=1;i<=m;i++) for(auto v:vc) a[i][v*i]+=fac[i-1];
	for(int i=1;i<=m;i++) ap[i]=Conv::getdft(a[i],len);
	b[0][0]=1;
	bp[0]=Conv::getdft(b[0],len);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=i;j++){
			for(int l=0;l<len;l++) (bp[i][l]+=bp[i-j][l]*ap[j][l]%mod*C[i-1][j-1])%=mod;
//			b[i]=Conv::add(b[i],Conv::mul(Conv::conv(b[i-j],a[j]),C[i-1][j-1]));
		}
//		bp[i]=Conv::getdft(b[i],len);
	}
	b[m]=Conv::getidft(bp[m],len,a[0].size());
	int inv=1;
	for(int i=1;i<=m;i++) (inv*=i)%=mod;
	inv=qp(inv,mod-2);
	for(int i=0;i<b[m].size();i++){
		if(b[m][i]){
			cout<<(long long)i<<": "<<(long long)(b[m][i]*inv%mod)<<"\n";
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	for(int i=0;i<=5;i++) C[i][0]=1;
	for(int i=1;i<=5;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	fac[0]=1; for(int i=1;i<=5;i++) fac[i]=fac[i-1]*i;
	for(int i=1;i<=5;i+=2) fac[i]=mod-fac[i];
	int t=read();
	for(int i=1;i<=t;i++){
		cout<<"Case #"<<(long long)i<<":\n";
		solve();
		cout<<"\n"; 
	}
	return 0;
}
```

---

