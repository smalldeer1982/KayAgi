# [BalticOI 2014] Sequence (Day1)

## 题目描述

现在有 $K$ 个连续正整数，每个整数你只能看见其中一位数字，求最开始的数 $N$ 的最小值。

## 说明/提示

#### 样例说明

对于样例 $1$，使得 $N$ 最小的数列为 $47,48,49,50,51,52$，$N$ 的最小值为 $47$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（9 pts）：$N,K \le 1000$。
- Subtask 2（33 pts）：$K \le 1000$。
- Subtask 3（25 pts）：给定的数位都相等。
- Subtask 4（33 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le K \le 10^5$。

**本题强制 O2 优化。**

#### 说明

翻译自 [BalticOI 2014 Day1 C Sequence](http://www.boi2014.lmio.lt/tasks/sequence-en.pdf)。

## 样例 #1

### 输入

```
6
7 8 9 5 1 2```

### 输出

```
47```

# 题解

## 作者：Alan_Zhao (赞：6)

**[在我的 cnblogs 中查看](https://www.cnblogs.com/alan-zhao-2007/p/p6740-sol.html)**

## 题解

一堆细节的题。

首先答案一定不超过 $123456789000000$。

考虑枚举 $N$ 的最低位填啥。由于 $10x,10x+1,\dots,10x+9$ 这些数除去最低位以外的位置都相同，因此可以把它们并在一起，然后递归下去。对于每个“数”维护一个数集，表示需要有这个数集里的数位。

时间复杂度 $T(n)=10T(\frac{n}{10})+\mathcal{O}(n)$，解得 $T(n)=\mathcal{\Theta}(n\log n)$。

几点细节：

1. $N\ge 1$，这一点翻译里没有体现。
2. 当递归到只有一个“数”的时候，应当特判，否则复杂度是错的。
3. 注意特判 $N$ 有前导零的情况。
4. 注意处理进位，例如 $\langle 9,0,1,0,3 \rangle$ 的答案是 $99$。

貌似和其他人写法不太一样，欢迎 Hack。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T>
void Read(T &_x){
	_x=0;int _f=1;
	char ch=getchar();
	while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();
	while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();
	_x*=_f;
}
template<typename T,typename... Args>
void Read(T &_x,Args& ...others){
	Read(_x);Read(others...);
}
typedef long long ll;
const int N=1e5+5;
const ll Inf=0x3f3f3f3f3f3f3f3f;
int n,a[N];
ll pow10[16];
int Convert(int x){
	int res=0;
	while(x) res|=1<<(x%10),x/=10;
	return res;
}
ll Dfs(int k,const vector<int>& need,ll cur,int zero){
	if(!zero&&none_of(need.begin(),need.end(),[](int x){return bool(x);})){
		return cur;
	}
	if(need.size()==1){
		if(k+__builtin_popcount(need[0])>17) return Inf;
		ll res=0,cnt=0;
		For(i,1,9){
			if(need[0]&(1<<i)){
				res=res*10+i;
				if(!cnt&&(need[0]&1)) res*=10;
				++cnt;
			}
		}
		if(!cnt&&(need[0]&1)) res=10;
		else if(!cnt&&zero) res=1;
		return res*pow10[k]+cur;
	}
	if(k>17) return Inf;
	vector<int> nw;
	ll ans=Inf;
	For(i,0,9){
		nw.clear();
		ll x=cur+pow10[k]*i;
		int temp=0,flg=1;
		for(int j=0,dig=i;j<(int)need.size();++j,++dig){
			if(dig%10==0) flg&=(!temp),temp=0;
			temp|=(1023^Convert(dig))&need[j];
		}
		flg&=(!temp);
		temp=0;
		for(int j=0,dig=i;j<(int)need.size();++j,++dig){
			if(dig==10){
				nw.push_back(temp);
				dig=temp=0;
			}
			temp|=(1023^(1<<dig))&need[j];
		}
		nw.push_back(temp);
		ans=min(ans,Dfs(k+1,nw,x,i==0));
		if(flg) ans=min(ans,x);
	}
	return ans;
}
int main(){
	Read(n);
	For(i,1,n) Read(a[i]);
	pow10[0]=1;
	For(i,1,15) pow10[i]=10*pow10[i-1];
	vector<int> need;
	For(i,1,n) need.push_back(1<<a[i]);
	printf("%lld\n",Dfs(0,need,0,1));
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# P6740 题解

[Problem Link](https://www.luogu.com.cn/problem/P6740)

**题目大意**

> 给定 $n$ 个数码 $d_1\sim d_n$，求最小的正整数 $x$ 使得对于所有 $1\le i\le n$，数码 $d_i$ 在数字串 $x+i-1$ 中出现过。
>
> 数据范围：$n\le 10^5$。

**代码呈现**

考虑推广原问题，设数码集 $S_i\subseteq\{0,1,2,3,4,5,6,7,8,9\}$ 表示 $x+i-1$ 中必须出现的数码集合。

观察 $x\sim x+n-1$，注意到删掉末位后这些数会 $10$ 个一组地变成相同的数，容易发现可以把这些数压缩到一起，然后把没满足的条件放进新的 $S_i$ 里，我们就成功构造了一个规模更小的子问题，枚举末位递归求解即可。

时间复杂度 $T(n)=10\times T(\dfrac n{10})+\mathcal O(n)=\mathcal O(n\log n)$，还有一些细节要注意：

- 特判 $n=1$ 的情况，以及 $n=2$ 且填的数码形如 $99\dots 9,100\dots 0$ 的情况。
- 注意判断当前 $x$ 是否有前导 $0$，以及这些前导 $0$ 是否一定要保留。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int B=1023;
inline int b(int x) { return 1<<x; }
inline int d(int x,int v) { return (x>>v)&1; }
inline int dfs(const vector<int> &lim,int lst,bool rem0) {
    //required digits, last digit, need remain zero?
    if(lim.size()==1) {
        int S=lim[0],res=0;
        if(S==0) return (!lst&&rem0)?1:0;
            //need 1 to be the highest digit in order to protect the 0
        if(S==1) return 10; //only need zero
        bool req0=d(S,0); //need 0?
        for(int i=1;i<=9;++i) if(d(S,i)) {
            res=res*10+i;
            if(req0) res=res*10,req0=false; //push 0 after the first non-0 digit
        }
        return res;
    }
    int res=1e16;
    for(int s=0;s<=9;++s) { //last digit
        if(lim.size()==2&&s==9&&lst==9&&!d(lim[0],9)&&!d(lim[1],0)) continue;
            //no use 9...9,10...0
        vector <int> newlim;
        for(int i=0,t=s,S=0;i<(int)lim.size();++i,t=(t+1)%10) {
            S|=lim[i]&(1023^b(t));
            if(i==(int)lim.size()-1||t==9) newlim.push_back(S),S=0;
        }
        res=min(res,dfs(newlim,s,d(lim[0],0))*10+s);
    }
    return res;
}
signed main() {
    int n;
    scanf("%lld",&n);
    vector <int> lim(n);
    for(int &i:lim) scanf("%lld",&i),i=b(i);
    printf("%lld\n",dfs(lim,0,1));
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

### 题目传送门

[P6740](https://www.luogu.com.cn/problem/P6740)

### 分析

一道小清新数位分治题目。

我们有 $K$ 个数字，可以转化为 $K$ 个限制，每一个限制可以用一个 $10$ 位的 bitset 存储。

发现，当 $K \le 10^5$ 时，$N = 102345678900000$ 一定能满足要求，故如果答案大于 $102345678900000$ 一定不是最优解，所以可以直接剔除超过 $16$ 位的答案。

我们从低位到高位枚举，对当前限制已经满足的，直接去掉即可。再把前面位都相同的归为一类，此时，规模从宏观上缩小到原来的 $\frac{1}{10}$。

最后考虑在只有一个限制的时候怎么做，就是前面的数必须包含集合中的数。为了保证答案最小化，容易想到要将集合中的数排序，但还要考虑 $0$。当然，如果中只有一个 $0$，就不得不在前面凭空加上一个 $1$；如果还有别的数字，就把 $0$ 插入到第二位。

这样还有一个问题，虽然前导零对答案本身的计算并不影响，但它会去掉 $0$ 的限制导致错误。所以我们要加一个布尔变量，表示是否有前导零，同时判断是否可以直接结束。

时间复杂度为 $O(K \lg{K})$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1;
	x = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 100010
ll pw[20];
int n;
vector<bitset<10> > t; 
ll solve(int p,vector<bitset<10> > now,bool b)
{
	if(p > 16) return 1e18;
	if(p&&!b)
	{
		bool flag = 1;
		F(j,0,(int)now.size() - 1)
			F(i,0,9)
			{
				if(!now[j][i]) continue;
				int x = j;
				bool f = 1;
				while(x) 
				{
					if(x % 10 == i) 
					{
						f = 0;
						break;
					}
					x /= 10;
				}
				if(f == 1) 
				{
					flag = 0;
					break;
				}
			}
		if(flag) return 0ll;
	}
	if(now.size() == 1)
	{
		bitset<10> lim = now[0];
		if(p + lim.size() > 16) return 1e18;
		ll ret = 0;
		F(i,1,9)
			if(lim[i])
			{
				if(lim[0]) ret = i * 10,lim[0] = 0;
				else ret = ret * 10 + i;
			}
		if(lim[0]) ret = 10;
		if(b&&!ret) ret = 1;
		return ret * pw[p];
	}
	ll ans = 1e18;
	F(i,0,9)
	{
		t.clear();
		bitset<10> tp = 0;
		F(j,0,(int)now.size()-1)
		{
			bitset<10> lim = now[j];
			if(lim[(i+j)%10]) lim[(i+j)%10] = 0;
			tp |= lim;	
			if((i+j)%10 == 9||j == (int)now.size()-1) 
			{
				t.push_back(tp);
				tp = 0;
			}
		} 
		ans = min(ans,pw[p] * i + solve(p+1,t,(i == 0)));
	}
	return ans;
}
int main()
{
	pw[0] = 1;
	F(i,1,16) pw[i] = pw[i-1] * 10;
	read(n);
	F(i,1,n) 
	{
		int x;
		read(x);
		t.push_back(1<<x);	
	}	
	write(solve(0,t,0));  
	return 0;
}
```

---

## 作者：Aigony (赞：0)

小清新数位分治。

首先尝试构造一个答案的上界，容易发现当 $N=102345678900000$ 时，无论给出什么样的数列都符合条件。也就是说，当一个数大于 $16$ 位时不可能成为答案。

考虑枚举第一个数的最低位是什么。由此，我们可以推出所有位置最低位的值，并判断哪些已经满足了条件。  
在这个基础上，忽略掉所有数的最后一位，那么以每 $10$ 个数字分段，一段内的数字除最后一位外都相同。把它们的限制合并，当成一个数来看，问题规模缩小为原来的 $\frac{1}{10}$。递归计算即可。

对这个看起来很暴力的做法分析时间复杂度，根据主定理有 $10T(\frac{n}{10})+\mathcal{O}(n)=\mathcal{O}(n \lg n)$。

实现上，注意前导 $0$ 和进位的特判。

```cpp
#define int long long
const int N=1e5+5,M=10,inf=1e17;
int n,a[N];
int solve(int dep,vector<bitset<M>> t,int ld)
{
    if(!t.size()) return ld;
    if(dep+t[0].count()>16) return inf;
    int ans=inf;
    if(t.size()==1)
    {
        vector<int> nw;
        for(int i=0;i<10;i++) if(t[0][i]) nw.push_back(i);
        if(!nw.size()) return ld;
        if(nw.size()==1&&nw[0]==0) return 10;
        else
        {
            if(nw[0]==0) swap(nw[0],nw[1]); 
            int res=0;
            for(auto x:nw) res=(res*10)+x;
            return res;
        }
    }
    for(int i=0;i<=9;i++)
    {
        vector<bitset<M>> nxt;
        int l=i; bool fg=0;
        for(int j=0;j<t.size();j++)
        {
            bitset<M> nw;
            for(int k=j;k<t.size();k++,l=(l+1)%10)
            {
                bitset<M> qwq=t[k];
                if(l==0&&qwq[l]) fg=1;
                if(qwq[l]) qwq[l]=0;
                nw|=qwq;
                if(l==9||k+1==t.size()) {j=k,l=(l+1)%10;break;}
            }
            nxt.push_back(nw);
        }
        ans=min(ans,solve(dep+1,nxt,fg)*10+i);
    }
    return ans;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    vector<bitset<M>> st;
    for(int i=1;i<=n;i++)
    {
        bitset<M> nw;
        nw[a[i]]=1;
        st.push_back(nw);
    }
    int ans=solve(1,st,0);
    printf("%lld\n",ans);
    return 0;
}
```

---

