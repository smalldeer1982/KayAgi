# Seller Bob

## 题目描述

Last year Bob earned by selling memory sticks. During each of $ n $ days of his work one of the two following events took place:

- A customer came to Bob and asked to sell him a $ 2^{x} $ MB memory stick. If Bob had such a stick, he sold it and got $ 2^{x} $ berllars.
- Bob won some programming competition and got a $ 2^{x} $ MB memory stick as a prize. Bob could choose whether to present this memory stick to one of his friends, or keep it.

Bob never kept more than one memory stick, as he feared to mix up their capacities, and deceive a customer unintentionally. It is also known that for each memory stick capacity there was at most one customer, who wanted to buy that memory stick. Now, knowing all the customers' demands and all the prizes won at programming competitions during the last $ n $ days, Bob wants to know, how much money he could have earned, if he had acted optimally.

## 样例 #1

### 输入

```
7
win 10
win 5
win 3
sell 5
sell 3
win 10
sell 10
```

### 输出

```
1056
```

## 样例 #2

### 输入

```
3
win 5
sell 6
sell 4
```

### 输出

```
0
```

# 题解

## 作者：sSkYy (赞：1)

# [CF18D Seller Bob](https://www.luogu.com.cn/problem/CF18D)

考虑 $\text{DP}$。

设 $f_i$ 为第 $i$ 天的最大答案，$lst_x$ 为 $x$ 上一次出现的位置。

由于手上只能拿一个东西，所以只会拿最近的东西卖，所以只用记录上一次出现的位置即可。

易得转移方程：

- $s = \text{win}$ 时：$f_i=f_{i-1},lst_x=i$
- $s = \text{sell}$ 时：$f_i = \max (f_{i-1},f_{lst_x}+2^x)$

建议高精度最好封装一下，写起来美观。

核心代码如下：
```cpp
	p[0]=1;
	for(int i=1;i<=X-20;i++) p[i]=p[i-1]*2;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		int x;
		cin>>s>>x;
		f[i]=f[i-1];
		if(s[0]=='s'){
			if(nxt[x]){
				BigInteger tmp=f[nxt[x]]+p[x];
				if(f[i]<tmp) f[i]=tmp;
			}
		}
		else nxt[x]=i;
	}
	cout<<f[n];
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

考虑动态规划。

记录下每一种内存的硬盘的上一个可以取到的位置，以及每一个位置能取到的最大价值。

对于每一个能卖出的位置，向前找到一个最近的能获取的位置，加上获得的价值与当前最大比较即可。形式化地，有：$f_i=\max(f_{i-1},f_{last}+2^{num})$。

注意需要写高精度。

---
### 代码：

```cpp
#include<cstdio>
#include<bitset>
#include<string>
#include<iostream>
using namespace std;
struct str{
	int len,num[2005];
	bool operator <(str a){
		if(len!=a.len)return len<a.len;
		for(int i=len;i>=1;i--){
			if(a.num[i]==num[i])continue;
			return num[i]<a.num[i];
		}
		return 0;
	}
	str operator +(str a){
		a.len=max(a.len,len);
		for(int i=1;i<=len;i++){		
			a.num[i]+=num[i],
			a.num[i+1]+=a.num[i]/10;
			a.num[i]=a.num[i]%10;
		}
		if(a.num[a.len+1]!=0)a.len++;
		return a;
	}
}p[2005],f[5005],x;
void pow(str &a){
	for(int i=a.len;i>=1;i--){
		a.num[i]*=2;
		a.num[i+1]+=a.num[i]/10;
		a.num[i]=a.num[i]%10;
	}
	if(a.num[a.len+1]!=0)a.len++;
}
void print(str a){
	if(a.len==0){
		printf("0\n");
		return;
	}
	for(int i=a.len;i>=1;i--)
	printf("%d",a.num[i]);
	printf("\n");
}
void init(){
	p[0].num[1]=1;
	p[0].len=1;
	for(int i=1;i<=2001;i++){
		p[i]=p[i-1];
		pow(p[i]);
	}
}
int n,num[5005],last[5005];
string s;
int main(){
	scanf("%d",&n);
	init();
	for(int i=1;i<=n;i++){
		cin>>s;scanf("%d",&num[i]);
		f[i]=f[i-1];
		if(s[0]=='w')last[num[i]]=i;
		else{
			if(last[num[i]]==0)continue;
			x=f[last[num[i]]]+p[num[i]];
			if(f[i]<x)f[i]=x;
		}
	}
	print(f[n]);
	return 0;
}
```


---

## 作者：_edge_ (赞：1)

有几个性质比较显然，比如现在如果要 sell $7$，必然选择最接近这一天的 win $7$。

所以可以记录最近的 $x$，将其丢到一个桶里面。

然后呢 …… 对于一天来讲，如果是 win 那么，将 $x$ 扔进一个桶里面，如果是 sell，那么有两个决策，第一个是不卖了，第二个是卖，但是要到之前那一天，也就是说要之前那一天到现在都没有卖出东西。

转移方程是：

win：$f_{i,j}=f_{i-1,j}$。

sell：$f_i=\max(f_i,f_{pre_x}+x)$。

第二种比较方式大力从 $2000$ 找到 $0$ 就可以了。

另外：是二维的，我有一维用了 bitset。

最后的答案还需要高精来处理，注意这里不能瞎搞，显然 $0$ 到 $2000$ 具有单调性，也就可以从上一个 $x$ 乘 $2$，千万不要从头开始计算。。。

顺便压了个位，不过不压位也没事。 (

```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstring>
#define int long long
using namespace std;
const int INF=5005;
const int Mod=1e16;
const signed Mod1=16;
int n,x,ans[INF],c[INF],lena,lenc,d[INF],pre[INF],la;
string s1;
bitset<2005> f[INF];
void mul(int x,int y) {
        for (int i=la; i<=y; i++) {
                for (int j=1; j<=lenc; j++)
                        c[j]=c[j]*x;
                for (int j=1; j<=lenc; j++)
                        c[j+1]+=c[j]/Mod,c[j]%=Mod;
                lenc++;
                while (c[lenc]==0 && lenc>1) lenc--;
                while (c[lenc]>=Mod) {c[lenc+1]+=c[lenc]/Mod; c[lenc]%=Mod; lenc++;}
                while (c[lenc]==0 && lenc>1) lenc--;
        }
        return;
}
void jia() {
        memset(d,0,sizeof d);
        int len=max(lena,lenc);
        for (int i=1; i<=len; i++)
                d[i]+=ans[i]+c[i],d[i+1]+=d[i]/Mod,d[i]%=Mod;
        len++;
        while (d[len]==0 && len>1) len--;
        while (d[len]>=Mod) {d[len+1]+=d[len]/Mod; d[len]%=Mod; len++;}
        while (d[len]==0 && len>1) len--;
        lena=len;
        memcpy(ans,d,sizeof d);
        return;
}
void printc() {
        for (int i=lenc; i>=1; i--) cout<<c[i];
        cout<<"\n";
        return;
}
signed main()
{
        ios::sync_with_stdio(false);
        cin>>n;
        for (int i=1; i<=n; i++) {
                cin>>s1>>x;
                if (s1=="win") {pre[x]=i; f[i]=f[i-1]; continue;}
                else {
                        if (!pre[x]) {f[i]=f[i-1]; continue;}
                        // cout<<i<<" "<<pre[10]<<"\n";
                        f[pre[x]][x]=1; bool fl=true;
                        for (int j=2000; j>=0; j--) {
                                if (f[i-1][j]<f[pre[x]][j]) {f[i]=f[pre[x]]; fl=false; break;}
                                if (f[i-1][j]>f[pre[x]][j]) {f[i]=f[i-1]; fl=false; break;}
                        }
                        if (fl) f[i]=f[i-1];
                        // f[pre[x]][x]=0;
                }
        }
        // cout<<f[7]<<"\n";
        // cout<<(1ll<<31);
        // cout<<f[n]<<"\n";
        c[1]=1; lenc=1;
        lena=1; la=1;
        for (int i=0; i<=2000; i++) {
                if (!f[n][i]) continue;
                mul(2,i);
                jia();
                la=i+1;
                // for (int i=lena; i>=1; i--) cout<<ans[i];
                // cout<<"\n";
        }
        printf("%lld",ans[lena]);
        for (int i=lena-1; i>=1; i--) printf("%0*lld",Mod1,ans[i]);
        printf("\n");
        return 0;
}

```


---

## 作者：lilong (赞：0)

设 $f_i$ 表示前 $i$ 个事件发生后的最大收益，如果第 $i$ 个事件是获得硬盘，则 $f_i \leftarrow f_{i-1}$，否则二分找到最大的 $j$ 使第 $j$ 个事件得到的硬盘与当前需要的相同（尽可能减少对前面的影响。可以预处理每种硬盘对应的事件编号），则 $f_i\leftarrow \max (f_j+2^x,f_{i-1})$。实现时需要高精度，可以开结构体重载运算符以简化代码。

实测发现不需要二分查找 $j$，直接暴力找也能通过，而且时空几乎一样。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> G[2010];
struct N{
    int a[1010];
    N(){
        memset(a,0,sizeof(a));
        a[0]=1;
    }
    N operator+(const N &A)const{
        N B;
        for(int i=1;i<=max(a[0],A.a[0]);i++){
            B.a[i]+=a[i]+A.a[i];
            B.a[i+1]+=B.a[i]/10;
            B.a[i]%=10;
        }
        B.a[0]=max(a[0],A.a[0]);
        if(B.a[B.a[0]+1])B.a[0]++;
        return B;
    }
}p[2010],f[5010],ans;
N mx(N A,N B){
        if(A.a[0]!=B.a[0]){
            if(A.a[0]>B.a[0])return A;
            return B;
        }
        for(int i=A.a[0];i>=1;i--){
            if(A.a[i]>B.a[i])return A;
            if(A.a[i]<B.a[i])return B;
        }
        return A;
    }
string s;
int n,op[5010],x[5010];
int main(){
    p[0].a[1]=1;
    for(int i=1;i<=2000;i++)
        p[i]=p[i-1]+p[i-1];
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s>>x[i];
        if(s=="win")op[i]=1,G[x[i]].push_back(i);
        else op[i]=2;
    }
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        if(op[i]==2){
            if(!G[x[i]].size())continue;
            if(G[x[i]][0]>i)continue;
            auto it=upper_bound(G[x[i]].begin(),G[x[i]].end(),i);
            it--;
            int j=*it;
            f[i]=mx(f[i],f[j]+p[x[i]]);
            ans=mx(ans,f[i]);
        }
    }
    for(int i=ans.a[0];i>=1;i--)
        cout<<ans.a[i];
    return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

## 前言

[题目传送门。](https://www.luogu.com.cn/problem/CF18D)

## 题解

### 思路

这个题贪心是不可能的，因为可能后面有更优的方法，那只有可能是动态规划。

定义 $f_i$ 为第 $i$ 天结束后的最大收益，$u_i$ 为容量是 $2^i$ 的硬盘上一次买入是多久。显然有 $f_0=0$。

容易推出转移方程。如果这一天是买入容量为 $2^x$ 的硬盘，则什么都不变，$f_i=f_{i-1}$，但是 $u_x=i$。如果这一天是有人来买容量为 $2^x$ 的硬盘，那么 $f_i=\max(f_{i-1},f_{u_x}+2^x)$。

答案是 $f_n$，时间复杂度 $O(n)$。

但是 $2^x$ 太大了，所以用高精度存。

### 代码

我这里把高精度封装起来，直接开始递推。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=1e5+5,X=2000+5;
int t[N],u[N];
struct Bigint{
	string num;
	string operator + (const Bigint &s){
		string a=num,b=s.num;
		if (a.size()<b.size()) swap(a,b);
		int temp=0;
		while (a.size()!=b.size()) b="0"+b;
		for (int i=b.size()-1;i>=0;--i){
			temp+=a[i]-'0'+b[i]-'0';
			a[i]=temp%10+'0';
			temp/=10;
		}
		if (temp) a="1"+a;
		return a;
	}
	void operator += (const Bigint &s){
		num=num+s.num;
	}
	void operator *= (const Bigint &s){
		int la=num.size(),lb=s.num.size();
		for (int i=1;i<la+lb;++i) t[i]=0;
		for (int i=1;i<=lb;++i)
			for (int j=1;j<=la;++j)
				t[i+j-1]+=(num[la-j]-'0')*(s.num[lb-i]-'0');
		for (int i=1;i<la+lb;++i)
			if (t[i]>9)
				t[i+1]+=t[i]/10,t[i]%=10;
		bool f=0;
		num="";
		for (int i=la+lb;i>=1;--i){
			if (t[i]!=0) f=1;
			if (f) num.push_back('0'+t[i]);
		}
		if (num.size()==0) num="0";
	}
}pw[X],f[N],g;
void mx(Bigint &a,Bigint b,Bigint c){
	if (b.num.size()>c.num.size()) a.num=b.num;
	else if (b.num.size()<c.num.size()) a.num=c.num;
	else{
		if (b.num>c.num) a.num=b.num;
		else a.num=c.num;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	pw[0].num="1";
	for (int i=1;i<X;++i) pw[i].num="2",pw[i]*=pw[i-1];
	int n;
	cin >> n;
	string op;
	int x;
	f[0].num="0";
	for (int i=1;i<=n;++i){
		cin >> op >> x;
		if (op=="win") mx(f[i],f[i-1],f[i-1]),u[x]=i;
		else{
			op=f[u[x]]+pw[x];
			if (u[x]==0) op="0";
			g.num=op;
			mx(f[i],f[i-1],g);
		}
	}
	cout<<f[n].num<<endl;
	cout.flush();
	return 0;
}
```

---

## 作者：SJH__qwq (赞：0)

设 $f_i$ 表示前 $i$ 次操作可以得到的最大收益。显然有 $f_0=0$，$f_i=f_{i-1}$。

考虑对于每一个卖出的位置，设要卖出 $2^j$ 这么大的硬盘，记录 $g_j$ 表示 $j$ 这样的硬盘上一次被买入的位置。因为 $j$ 的 $f$ 值单调递增所以不需要使用数据结构来优化，所以直接用 $f_{g_j}$ 的值来更新 $f_j$。当然也可以选择不卖。也就是说：

$$
f_i=\max(f_{i-1},f_{g_{a_i}}+2^{a_i})
$$

直接转移。时间复杂度为 $O(n)$。但是这个题需要用高精度，所以提供了题解区中没有的 `Python` 写法。实测可以通过。

[Code](https://codeforces.com/contest/18/submission/250326725)

---

## 作者：jhdrgfj (赞：0)

## 思路

考虑 dp，设 $dp_i$ 为第 $i$ 天的最大获利。

对于每个 ``sell``，我们有两种选择：

1. 什么也不干，此时可以从上一天转移过来。则 $dp_i=dp_{i-1}$。

2. 从最近的一个 ``win x`` 转移过来并获得 $2^x$ 收益。设 $b_x$ 为最近的 ``win x`` 的天数，则 $dp_i=dp_{b_x}+2^x$。

综上，对于每个 ``sell``，有 $dp_i=\max(dp_{i-1},dp_{b_x}+2^x)$。

对于每个 ``win``，只能从 $dp_{i-1}$ 转移过来，并置 $b_x=i$。

注意要加上高精度。

## 代码

我用了同学写的 30k 的高精模板，如果不压行会交不上去，看 [link](https://www.luogu.com.cn/paste/qn9q5l6h) 吧。

---

