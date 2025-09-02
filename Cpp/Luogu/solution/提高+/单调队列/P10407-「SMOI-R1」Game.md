# 「SMOI-R1」Game

## 题目背景

myz 很喜欢玩一款病毒游戏。

## 题目描述

在这个游戏里，一开始有 $n$ 个病毒，每个病毒的危害值为 $1$。

每隔一段时间，病毒就会变异，会分裂成两个病毒，右边的病毒会比左边的病毒危害值多 $1$，变异过的病毒不会再变异。

每个病毒有个变异极限 $b_i$，当这个病毒变异到 $b_i$ 时，这个病毒就会停止变异。也就是说，第 $i$ 个病毒最后都会分裂成一个危害值为 $\{1,2,3,\ldots,b_i\}$ 的病毒序列，当所有病毒变异完时，游戏开始，最终变异完的序列是 $\{1,2,3,\ldots,b_1,1,2,3,\ldots,b_2,\ldots,1,2,3,\ldots,b_n\}$。

每次游戏，系统会选择一个区间，myz 需要把这个区间的病毒全部杀死，如果这个区间内的病毒的危害值的最大值是 $x$，那么 myz 需要花费 $x$ 的能量才能消灭它们。

因为不知道系统会选择哪个区间，myz 想知道每个区间需要消耗的**能量值之和**。

由于答案太大了，myz 想让你把答案对 $998244353$ 取模。

## 说明/提示

### 样例解释
第一个样例，病毒最后分裂成 $\{1,2,1,2,3\}$，区间  $[1,1],[1,2],[1,3],[1,4],[1,5],[2,2],[2,3],[2,4],[2,5],[3,3],[3,4],[3,5],[4,4],[4,5],[5,5]$ 的最小代价和就是 $1+2+2+2+3+2+2+2+3+1+2+3+2+3+3=33$。

### 数据范围
**本题采用捆绑测试**。

subtask 编号|$n\leq$|$b_i\leq$|特殊性质|分值
-|-|-|-|-
$1$|$10^2$|$10^2$|无|$20$
$2$|$10^4$|$10^2$|无|$20$
$3$|$10^6$|$10^9$|A|$20$
$4$|$10^6$|$10^9$|无|$40$

**特殊性质 A**： $b_1 \leq b_2 \leq \ldots \leq b_n$。

对于 $100\%$ 的数据，保证 $1\le n\le10^6$，$1\le b_i\le 10^9$。

## 样例 #1

### 输入

```
2
2 3```

### 输出

```
33```

# 题解

## 作者：Supor__Shoep (赞：2)

~~就我觉得 T3 比 T4 简单吗QAQ~~

首先有一个非常常规的思路：枚举每一个数，求出其作为最大值的区间个数。这道题也是如此。

如果最终的序列 $a$ 长度够小，那么我们可以利用单调栈得出每一个数 $a_i$ 向前和向后的第一个 $>a_i$ 的数 $a_{l_i}$ 和 $a_{r_i}$，如果找不到则分别为 $0,|a|+1$，那么 $a_i$ 作为最大值的区间就有 $(i-l_i)(r_i-i)$ 个。

但是需要注意，有的区间是会被算重的，比如 $a=\{1,2,1,2\}$，两个 $2$ 分别计算得到的区间都包含 $[2,4],[1,4]$。这个时候考虑更改 $l_i$ 的定义为**向前找到的第一个 $≥a_i$ 的数的下标**，如果找不到则为 $|a|+1$，计算方式仍然是 $(i-l_i)(r_i-i)$。这样就可以保证不会重复计算了，原因显然，因此把它当成一个 Trick 掌握就行了。

但是出题人非常可爱啊！这个 $a$ 的长度可以达到 $10^{15}$，不可能直接计算。但是 $n$ 的范围倒是很合理。这就说明我们要找到 $a$ 序列的计算规律。

我们将 $a$ 视为 $n$ 个形如 $\{1,2,\dots,b_i-1,b_i\}$ 的子段前后拼接得到的序列，记 $s_{i,j}$ 表示第 $i$ 个子段中的第 $j$ 个数在 $a$ 中的下标。

先考虑 $s_{i,b_i}$ 的代价该怎么计算。由于各个子段的单调性，我们可以知道其向前能够找到的第一个 $≥b_i$ 的数的下标一定是 $s_{j,b_j}$（$j<i$），向后能够找到的第一个 $> b_i$ 的数的下标一定是 $s_{k,b_i+1}$（$i<k$，**注意是 $b_i$ 而不是 $b_k$**）。可以发现 $b_j$ 是 $b_i$ 向前第一个大于等于它的数，$b_k$ 是 $b_i$ 向后第一个大于它的数。可以通过这个结论，利用单调栈找到 $j,k$。我们找到这两个 $j,k$ 记为 $L(i),R(i)$（如果不存在满足条件的 $j$ 或 $k$，则分别变为 $0,n+1$），则 $s_{i,b_i}$ 的区间个数就是 $(s_{i,b_i}-s_{L(i),b_{L(i)}})(s_{R(i),b_{i}+1}-s_{i,b_i})$，可以利用 $b_i$ 的前缀和解决。

我们记 $sum_i=\sum _{j=1}^ib_j$，那么：

$$(s_{i,b_i}-s_{L(i),b_{L(i)}})(s_{R(i),b_{i}+1}-s_{i,b_i})=(sum_i-sum_{L(i)})(sum_{R(i)-1}-sum_i+1+[R(i)\leq n])$$

每一个子段的顶点值我们就算完了，我们考虑将这种做法拓展到其它数上面。其实我们可以利用图像去思考：

![](https://cdn.luogu.com.cn/upload/image_hosting/okf5jbaq.png)

我们知道对于每一个数，要去找前面和后面比自己大的，由于除了顶点以外，每个数的后面都有一个比自己大一的数，所以右侧比较好找。而对于左侧，我们结合上图去思考，不难发现最终形成的 $a$ 序列就是若干个等腰直角三角形排在一起，那么每个数作为最大值的区间可以延展到的左端点一定是在 $s_{k,b_k}$ 的位置。因此我们像之前那样用一个单调栈就行了。

但是对于每个数都用单调栈的话显然会寄。

我们可以找一下规律：

![](https://cdn.luogu.com.cn/upload/image_hosting/u5o9rbtl.png)

考虑对第 $3$ 个子段的每个元素的答案进行统计，我们发现 $IK$ 这一段对应过去的线段是 $EF$，这说明 $1\leq j\leq |IK|$ 的元素 $s_{3,j}$ 可以向左延伸的最远点都是 $F$，即 $s_{2,b_2}$。而 $GL$ 对应过去是 $CD$ 的一个子线段，这说明 $|IK|<j\leq |GH|$ 的元素 $s_{3,j}$ 向左延伸的最远点都是 $s_{1,b_1}$。这启示我们将每一个子段中的元素分成若干个子部分进行处理，并且要保证每个部分的 $s_{i,j}$ 对应的左侧端点是相同的。

于是我们用单调栈去储存 $b_i$，维护一个单调递减的子序列的**下标**。当我们要处理第 $i$ 个子段时，我们就在栈中从后往前遍历，设当前遍历的元素为 $p$，上一个遍历的元素是 $q$，那么我们就将 $[s_{i,b_q+1},s_{i,b_p}]$ 的答案进行加和，下文令 $t=sum_{i-1}-sum_p+b_q$，$m=b_p-b_q$，则：

$$
\begin{aligned}
\sum _{j=b_q+1}^{b_p}j(s_{i,j}-s_{p,b_p})&=\sum _{j=b_q+1}^{b_p}j(sum_{i-1}-sum_p+j)\\
&=\sum _{j=1}^{m}(b_q+j)(sum_{i-1}-sum_p+b_q+j)\\
&=mb_qt+\dfrac{m(b_q+t)(m+1)}{2}+\dfrac{m(m+1)(2m+1)}{6}
\end{aligned}
$$

这样就可以 $O(1)$ 计算这一段的答案之和了。

根据单调栈的性质，可以推断 $n$ 个子段分成的子部分的个数和是 $O(n)$ 级别的，可以跑过。

最后就是一些细节问题了，放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+5;
const int MOD=998244353;
int n,a[MAXN];
stack<int> stk;
int res;
int L[MAXN],R[MAXN];
int sum[MAXN];
int qpow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)	res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;
		y>>=1;
	}
	return res;
}
int solve(int x,int y,int z){ return (1ll*x*y%MOD*z%MOD+1ll*(x+y)%MOD*(1ll*(z+1)*z/2%MOD)%MOD+1ll*z*(z+1)%MOD*(2*z+1)%MOD*qpow(6,MOD-2)%MOD)%MOD; }
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i],sum[i]=sum[i-1]+a[i],sum[i]%=MOD;
	a[n+1]=a[n];
	for(int i=1;i<=n;i++)
	{
		while(!stk.empty()&&a[stk.top()]<a[i])	R[stk.top()]=i,stk.pop();
		if(!stk.empty())	L[i]=stk.top();
		stk.push(i);
	}
	while(!stk.empty())	R[stk.top()]=n+1,stk.pop();
	for(int i=1;i<=n;i++)	res+=1ll*a[i]*(sum[i]-sum[L[i]]+MOD)%MOD*(sum[R[i]-1]-sum[i]+1+(R[i]<=n)*a[i]+MOD)%MOD,res%=MOD;
	while(!stk.empty())	stk.pop();
	stk.push(0),a[0]=1e9;
	for(int i=1;i<=n;i++)
	{
		int lst=0;
		while(!stk.empty()&&a[stk.top()]<=a[i]-1)	res+=solve(sum[i-1]-sum[stk.top()]+lst,lst,a[stk.top()]-lst),lst=a[stk.top()],stk.pop();
		if(lst!=a[i]-1)	res+=solve(sum[i-1]-sum[stk.top()]+lst,lst,a[i]-lst-1),res%=MOD;
		while(!stk.empty()&&a[stk.top()]==a[i])	stk.pop();
		stk.push(i);
	}
	cout<<res;
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

我最爱的数学题！

为方便，我们设变异后第 $i$ 个病毒为 $a_i$，若变异后第 $i$ 个病毒变异前属于第 $j$ 个病毒，则设 $c_i=j$。

先考虑暴力，我们考虑 $O((\sum b_i)^2)$ 算法。

枚举变异后第 $l$ 个病毒开始，不妨设此时第 $r$ 个病毒结束，$f(r)$ 表示从 $l$ 到 $r$ 病毒危险最大值。

显然 $f(r)$ 是单调不降的，有 $f(r)=\max(f(r-1),a_r)$。

这个做法是很简单的，我们不需要写出来，可以直接脑内优化。

发现每次 $f(r)$ 相对于 $f(r-1)$ 增加都有 $b_{c_r}>\max(b_{c_l},b_{c_l+1}\dots b_{c_r-1})$，并且这是有一段区间是 $x+1,x+2,x+3\dots b_r$，其中 $x$ 表示 $\max(b_{c_l},b_{c_l+1}\dots b_{c_r-1})$。

那么我们只需要记录 $x$，枚举 $b_{c_l+1}\sim b_n$，如果 $b_i\le x$，则直接加 $b_i\times x$，因为这个区间的 $f(i)$ 显然都为 $x$，否则就分两段计算，一段是 $1\sim x$，一段是 $x+1\sim b_r$，然后更新 $x$。

由于 $b_{c_l}$ 显然为 $b_{c_l}$ 这一段最大值，因此初始化时直接设 $x=b_{c_l}$，把后面的贡献乘上 $b_{c_l}$。

此时我们要计算 $b_{c_l}$ 这一段的贡献。

显然 $l$ 有 $b_{c_l}$ 种取值，为 $1\sim b_{c_l}$，当 $a_l=i$ 时，答案贡献 $i+(i+1)+(i+2)\dots+b_{c_l}$。

我们设 $b_{c_l}=p$。

于是我们要计算 $\sum\limits_{i=1}^{p}\sum\limits_{j=i}^p j$。

$\sum\limits_{i=1}^{p}\sum\limits_{j=i}^p j=\sum\limits_{j=1}^{p}\sum\limits_{i=1}^j j=\sum\limits_{i=1}^{p}i^2$。

发现这个式子很典，由 bdfs 算法（如果你不知道这是什么算法，请学习 bfs，dfs，和 [bdfs 比较复杂，详见博客](http://baidu.physton.com/?q=https://www.luogu.com/article/9sdr6beo)）可知其计算公式为 $\frac{p(p+1)(2p+1)}{6}$。

然后就可以写出 $O(n^2)$ 啦。

此时思路比较混乱，为了方便思考优化，所以可以吧这几行敲出来。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mod=998244353;
int ans;
int a[1000009];
int ksm(int a,int b){//求逆元详见费马小定理
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int x;
		x=a[i];
		int sum;
		sum=0;
		for(int j=i+1;j<=n;j++){
			if(a[j]>x){
				sum+=x*x;
				sum+=(a[j]+x+1)*(a[j]-x)*ksm(2,mod-2);
				x=a[j];
			}else{
				sum+=a[j]*x;
			}
			ans%=mod;
		}
		ans+=sum*a[i];
		ans%=mod;
		ans+=a[i]*(a[i]+1)%mod*(2*a[i]+1)%mod*ksm(6,mod-2)%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

这时候优化，发现似乎唯一可以优化的只有 $sum$ 求值。

即有上一个 $sum$ 得到当前 $sum$。

对 $x$ 产生的 $b_i$ 有单调性，考虑单调栈。

$b_i$ 从栈顶到栈底显然要上升，且栈顶的 $i$ 最小，所以倒着枚举维护单调栈。

栈内靠近底部的元素显然比靠近顶部的元素要大，所以 $x$ 不受顶部影响。对应的，往后的 $sum$ 也不受影响，因此可以由次顶部的 $sum$ 求出顶部的 $sum$，每次顶部处理的显然枚举了所有的 $b_i$，因此只需要每次处理答案贡献即可。

这个题需要开 `__int128`。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
__int128 ans;
int a[1000009];
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
int q[1000009];
__int128 su[1000009];
int t;
__int128 qz[1000009];
signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(0); 
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		qz[i]=qz[i+1]+a[i];
	}
	for(int i=n;i>=1;i--){
		while(t>0&&a[i]>a[q[t]]){
			t--;
		}
		q[++t]=i;
		su[t]=su[t-1]+a[i]*qz[i+1]-a[i]*qz[q[t-1]];
		su[t]%=mod;
		if(t!=1)
		su[t]+=a[i]*a[i]%mod+(a[q[t-1]]+a[i]+1)*(a[q[t-1]]-a[i])%mod*ksm(2,mod-2)%mod;
		su[t]%=mod;
		__int128 sum;
		sum=su[t];
		ans+=sum*a[i];
		ans%=mod;
		ans+=a[i]*(a[i]+1)%mod*(2*a[i]+1)%mod*ksm(6,mod-2)%mod;
		ans%=mod;
	}
	int z;
	z=ans;
	cout<<z;
	return 0;
}
```

---

## 作者：ThisIsLu (赞：1)

先考虑暴力，不难想到单调栈，设最后分裂得到的序列为 $a$，计算以第 $i$ 个数结尾的区间的贡献之和，设其为 $f_i$，则有：

$$f_i=f_k+a_i(i-k)$$

其中 $k$ 为满足 $a_k>a_i,0 \le k<i$ 的最大值。特别地，设 $f_0=0$。

可 $b_i$ 是 $10^9$ 级别的，明显会超时，需要优化。

首先，可以发现 $k$ 一定是某个病毒所生成序列的最后一个，也就是说单调栈里头只需要压入 $b_i$ 就可以了。

因此，设 $s(i)=\sum\limits_{j=1}^{i}b_j$，$f(i)$ 表示以第 $s(i)$ 个数结尾的区间的贡献。

再设 $g(i)$ 表示右端点在 $s_{i-1}+1$ 到 $s_i$ 之间的区间贡献，$ltail$ 表示在加入 $b_i$ 之前的栈顶位置，$tail$ 表示在把所有小于 $b_i$ 的都删掉后的栈顶位置，$st_i$ 则表示当前的栈内从栈底到栈顶第 $i$ 个元素的标号，$k(i,j)$ 表示满足 $b_x>j,0 \le x<i$ 的 $x$ 的最大值。

那么，有：

$$
\begin{aligned}
g(i)=&\sum_{j=1}^{b_i}f(k(i,j))+j(s(i)+j-s(k(i,j))\\
=&\frac{b_i(b_i+1)(2b_i+1)}{6}+\frac{b_i(b_i+1)}{2}s(i)+\sum_{j=1}^{b_i}f(k(i,j))-js(k(i,j))\\
=&\frac{b_i(b_i+1)(2b_i+1)}{6}+\frac{b_i(b_i+1)}{2}s(i)+\sum_{j=1}^{b_i}f(k(i,j))-\sum_{j=1}^{b_i}js(k(i,j))\\
=&\frac{b_i(b_i+1)(2b_i+1)}{6}+\frac{b_i(b_i+1)}{2}s(i)+b_{st_{ltail}}f(st_{ltail})-s(st_{ltail})\frac{b_i(b_i+1)}{2}+\sum_{j=tail}^{ltail-1}f(st_j)(b_{st_j}-b_{st_{j+1}})-\sum_{j=tail}^{ltail-1}s(st_j)\frac{(b_{st_j}-b_{st_{j+1}})(b_{st_j}+b_{st_{j+1}}+1)}{2}\\
\end{aligned}
$$

显然，求和部分可以直接在单调栈时处理。

贴上丑陋无比的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,b[N],tail,stk[N],f[N],s[N];
signed main(){
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        cin>>b[i];
        s[i]=(s[i-1]+b[i])%998244353;
        ans+=b[i]*(b[i]+1)%998244353*(2*b[i]+1)%998244353*166374059%998244353;
        ans+=b[i]*(b[i]+1)/2%998244353*s[i-1]%998244353; 
        ans+=(f[stk[tail]]*min(b[i],b[stk[tail]])%998244353-s[stk[tail]]*(min(b[i],b[stk[tail]])*(min(b[i],b[stk[tail]])+1)/2%998244353)%998244353+998244353);
        while(tail&&b[stk[tail]]<b[i]){
            tail--;
            ans+=f[stk[tail]]*(min(b[i],b[stk[tail]])-b[stk[tail+1]])%998244353;
            ans-=s[stk[tail]]*((min(b[i],b[stk[tail]])-b[stk[tail+1]])*(min(b[i],b[stk[tail]])+b[stk[tail+1]]+1)/2%998244353)%998244353;
            ans+=998244353;
        }
        f[i]=(f[stk[tail]]+b[i]*(s[i]-s[stk[tail]]+998244353)%998244353)%998244353;
        stk[++tail]=i;
        ans%=998244353;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Shxt_Plus (赞：1)

简要题意：

给一个 $\{1,2,3,\ldots,b_1,1,2,3,\ldots,b_2,\ldots,1,2,3,\ldots,b_n\}$ 的序列，问每一个子区间的最大值的和是多少。

$v$ 为最大权值

### Subtask1

直接暴力处理出这个序列，然后枚举左端点，然后在枚举枚举右端点的同时算出这个区间的最大值。

时间复杂度 ： $O((nv)^2)$

### Subtask2

同样暴力处理出这个序列，然后对于每个数考虑这个数的贡献是多少，也就是这个数可以成为多少个区间的最大值，（如果这个区间有多个最大值那就只算第一个最大值的贡献）。

考虑如何计算，对于一个数想成为最大值则说明这个区间没有比这个数还要大的数（~~废话~~）。

那就找到这个数左边第一个大于等于这个数的数 $l$ ，再找到右边第一个比这个数大的数 $r$，那么这个数就可以成为左端点在 $[l,i]$，右端点在 $[i,r]$ 的区间的最大值，证明显然，所以第 $i$ 个数的贡献就是 $a_i*(i-l+1)\times(r-i+1)$，然后用单调队列维护第一个比自己大的数的位置即可。

时间复杂度：$O(nv)$

### Subtask3

我们沿用 $\text{Subtask 2}$ 的思路，但是因为 $b_i$ 最大可能到 $10^{18}$，所以不能再处理出这个序列了，我们考虑分段，将 ${1,2,\ldots，b_i}$ 分为一段，然后我们一段一段地考虑。

先计算出在左右端点都在第 $i$ 段内的区间的贡献，因为这是一个递增的序列，所以最大值就是右端点，我们枚举右端点，当 $i$ 作为右端点时，显然前 $i$ 个数都能成为左端点，所以贡献是 $i^2$ ，所以第 $i$ 段的贡献是 ${\sum_{j = 1}^{b_i}}{j^2}$ 可以用公式快速计算。

然后我们再考虑右端点在第 $i$ 段，左端点在 $1-(i-1)$ 段的区间的贡献，很显然，以 $1-b_{i-1}$ 为右端点的数的区间的贡献都是 $b_{i-1}$ 所以总贡献是 ${b_{i-1}}^2$ ，而以 $b_{i-1}+1-b_i$ 为右端点的区间的贡献都是右端点的值，所以总贡献是 $\sum_{j=b_{i-1}+1}^{b_i}j^2$ 同样可以通过公式快速计算。

时间复杂度：$O(n)$

### Subtask 4

我们继续沿用 $\text{Subtask 3}$ 的思路，对于段内的贡献计算还是一样的。

我们考虑如何计算右端点在第 $i$ 段，左端点在 $1-(i-1)$ 段的区间的贡献，我们用 $f_i$ 来表示以 $b_i$ 为右端点的所有区间的总贡献。

我们受到 $\text{Subtask 3}$ 的启发，发现 $1-b_{i-1}$ 的数的贡献就是以 $b_{i-1}$ 为右端点的区间的贡献，那么怎么算以 $b_{i-1}-b_i $ 为右端点的贡献呢，我们找到最后一个比 $b_{i-1}$ 大的数 $t$ ，那么我们可以很容易的求出 $b_{i-1}+1-b_t$ 的数的贡献，一直求下去就能求出最终答案，用单调队列维护就好了。

由于有点难理解放一下代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 5, mod = 998244353, inv6 = 166374059, inv2 = 499122177;
stack<int> q;
int n, b[maxn], sum[maxn], f[maxn];
int ans = 0;
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", b + i);
    }
    for (int i = 1; i <= n; i++) {
        int l = 0;
        ans += (b[i]) * (b[i] + 1) % mod * (2 * b[i] + 1) % mod * inv6 % mod;
        ans %= mod;
        while (!q.empty() && b[i] >= b[q.top()]) {
            int t = q.top();
            q.pop();
            ans += (b[t] - l) * f[t];
            ans %= mod;
            ans +=
                (sum[i - 1] - sum[t]) % mod * (b[t] - l) % mod * (b[t] + l + 1) % mod * inv2 % mod;
            ans %= mod;
            l = b[t];
        }
        sum[i] = sum[i - 1] + b[i];
        sum[i] %= mod;
        int t;
        if (!q.empty()) t = q.top();
        else t = 0;
        ans += (b[i] - l) * f[t];
        ans %= mod;
        ans += (sum[i - 1] - sum[t]) % mod * (b[i] - l) % mod * (b[i] + l + 1) % mod * inv2 % mod;
        ans %= mod;
        f[i] = f[t] + (sum[i] - sum[t]) * b[i] % mod;
        f[i] %= mod;
        q.push(i);
    }
    ans = (ans % mod + mod) % mod;
    cout << ans;
    return 0;
}
```

---

