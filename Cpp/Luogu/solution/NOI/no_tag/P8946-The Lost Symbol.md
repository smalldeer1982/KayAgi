# The Lost Symbol

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/g4ofcg40.png)

## 题目描述

设二元运算符 $k\operatorname A n$ 为排列数 ${\rm A}_n^k$，$k \operatorname C n$ 为组合数 ${\rm C}_n^k$，定义 $k>n$ 时两者的值都为 $0$。

给定 $n,m$ 和一个长度为 $n-1$ 的仅包含 $\textrm A,\textrm C$ 的序列 ${\rm opt}_{[1,n-1]}$，对所有长度为 $n$，且每一个数都是 $[1,m]$ 中的整数的序列 $a_{[1,n]}$ 求 $(\cdots(((a_1\operatorname{opt}_1 a_2)\operatorname{opt}_2 a_3)\operatorname{opt}_3 a_4)\cdots\operatorname{opt}_{n-2}a_{n-1})\operatorname{opt}_{n-1}a_n$ 的和。

答案对质数 $11417603$ 取模。

## 说明/提示

#### 【样例解释】
对于样例 #1：

$1\operatorname C 1=1$，$1\operatorname C 2=2$，$2\operatorname C 1=0$，$2\operatorname C 2=1$，求和为 $4$。

对于样例 #2：

$1\operatorname A 1=1$，$1\operatorname A 2=2$，$2\operatorname A 1=0$，$2\operatorname A 2=2$，求和为 $5$。

#### 【数据范围】

不开启捆绑测试，按点给分。

对于 $100\%$ 的数据，$2\leq n,m\leq 10^5$，${\rm opt}$ 仅包含 $\textrm A,\textrm C$。

| 测试点编号 | $n\leq$ | $m\leq$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1\sim3$ | $8$ | $8$ | 无 | 
| $4\sim6$ | $314$ | $159$ | 无 | 
| $7\sim10$ | $2718$ | $2818$ | 无 | 
| $11\sim13$ | $10^5$ | $10^5$ | $\rm opt$ 仅由 $\rm A$ 构成 |
| $14\sim16$ | $10^5$ | $10^5$ | $\rm opt$ 仅由 $\rm C$ 构成 |
| $17\sim20$ | $10^5$ | $10^5$ | $\rm opt$ 由不超过 $10$ 段连续的 $\rm A$ 和连续的 $\rm C$ 拼接而成 |
| $21,22$ | $8492$ | $10^5$ | 无 |
| $23\sim25$ | $10^5$ | $10^5$ | 无 |

## 样例 #1

### 输入

```
2 2
C```

### 输出

```
4```

## 样例 #2

### 输入

```
2 2
A```

### 输出

```
5```

## 样例 #3

### 输入

```
8 8
CCACAAC```

### 输出

```
399968```

# 题解

## 作者：Sol1 (赞：5)

[Ex 题解](https://www.luogu.com.cn/paste/2eevaebh)

## 1C

考虑暴力 DP：

设 $f_{i,j}$ 表示填到前 $i$ 位，运算结果是 $j$ 的方案数，结果大于 $m$ 统一记为 $m+1$（因为再接一位一定是 0）。朴素实现可得 24，精细实现可得 40。（事实上 40 分很提示正解）

考虑所有转移。对于 A：

1. 所有数都可以往后接一个更小的数转移到 0。
1. 1 可以接任意数转移到对应的数。
1. 0 接任意数转移到 1。
1. 其余转移不多。

对于 C：

5. 所有数都可以往后接一个更小的数转移到 $0$。
1. 所有数都可以往后接自己转移到 $1$。
1. 所有数都可以往后接自己 +1 转移到自己 +1。
1. 1 可以接任意数转移到该数。
1. 其余转移不多。

这里会有几个重复转移（例如 $1{\rm C}1=1$ 会被多次转移），需要减掉。重复部分很少所以可以直接归到最后一类里面。

依次考虑每一种转移：

1. 全局 $\sum a_i(i-1)$，单点修改
1. 全局加
1. 单点修改，单点求值
1. 单点修改，单点求值
1. 同 1
1. 全局和，单点修改
1. 整体向右平移一位
1. 全局加
1. 同 3

所以数据结构需要支持：

- $O(1)$ 单点修改；
- $O(1)$ 单点求值；
- $O(\sqrt m)$ 以下全局加；
- $O(\sqrt m)$ 以下全局和；
- $O(\sqrt m)$ 以下全局 $\sum a_i(i-1)$；
- $O(\sqrt m)$ 以下向右平移一位。

注意这个转移的过程中前一列的 DP 不能继承到后一列，所以还要支持：

- $O(\sqrt m)$ 以下全部清零。

使用一个 $O(1)$ 数据结构维护：保存 DP 数组 $f$ 和一个时间标记数组 $t$，$s_1=\sum_{i=0}^mf_i$，$s_2=\sum_{i=0}^mf_{i}(i-1)$，以及一个清零值 $v_0$，清零时间 $t_0$，整体加的值 $v_A$。考虑所有操作：

- 单点修改：这里是单点加，下放标记（如果 $t_i<t_0$，将时间修改到 $t_0$，$f_i$ 修改到 $v_0$）之后直接改数组并对应更新 $s_1$ 和 $s_2$ 就行，$O(1)$。
- 单点求值：下放标记后返回 $f_i+v_A$ 即可，$O(1)$。
- 全局加：修改 $v_A,s_1,s_2$ 即可，$O(1)$。
- 全局和：返回 $s_1$ 即可，$O(1)$。
- 全局 $\sum a_i(i-1)$：返回 $s_2+f_0$ 即可（注意 $s_2$ 中 $f_0$ 的系数是 $-1$），$O(1)$。
- 向右平移一位：修改 $f,t$ 的起始指针的位置（可以开一个两倍长的数组，初始把指针指在中间，这样每次直接自减 1 即可），并对应修改 $s_1$ 和 $s_2$ 即可，$O(1)$。
- 清零：将 $t_0$ 设为当前时间，$v_0$ 设为 $-v_A$，$s_1$ 和 $s_2$ 均设为 $0$ 即可，$O(1)$。

最后一个运算符特殊处理，需要求组合数上指标前缀和或者下降幂底数前缀和，都是经典问题，可以 $O(1)$ 求。

所以这题就做完了。最后复杂度是 $O(n\sum_{i=2}^{\sqrt m}\sqrt[i]{i!m})$，实际 $m=10^5$ 时 A/C 转移分别只有 $393/1195$ 个，可以通过。



---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

~~做阴间题不能白做，还得水篇题解~~

首先考虑一个基本的动态规划：记 $f_{i,j}$ 表示考虑到第 $i$ 个数时运算结果为 $j$ 的方案数。$j>m$ 时一律记作 $m+1$，因为此时无论选什么数都会一次变为 $0$。

考虑当前符号是 A 还是 C，A 的变化如下：

1. $\forall x>y$，$A_y^x=0$
2. $\forall x$，$A_x^1=x$
3. $\forall x$，$A_x^0=1$
4. 其他 $A_y^x=z\le m$ 的情况不多，可以预处理出来。

C 的变化如下：

5. $\forall x>y$，$C_y^x=0$
2. $\forall x$，$C_x^x=1$
3. $\forall x$，$C_{x+1}^x=x+1$
4. $\forall x$，$C_x^0=1$
5. $\forall x$，$C_x^1=x$
6. 其他 $C_y^x=z\le m$ 的情况不多，可以预处理出来。

注意 $C_2^1$ 和 $C_1^1$ 是会在上面被算两次的，需要单独减掉，可以跟 10 放在一起。

容易发现上面需要预处理的转移数是 $O(\sqrt m)$ 的。每一个 $C_y^x=z$ 都代表可以从 $x$ 转移到 $z$，于是直接暴力 dp 的复杂度是 $O(n^2)$ 的。

不过需要注意的是，最后一个运算符的时候我们不能和刚才一样做了，因为最终的运算结果是带取模的，不能用 $m+1$ 表示超出的情况了，所以算到倒数第二个运算符之后再进行一次 $O(n^2)$ 暴力计算结果即可。

暴力部分实现：

```cpp
int n,m;
string s;
ll dp[3005][3005];
vector<pii>A,C;

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(){
	cin>>n>>m>>s;
	for(int i=2;i<=m;i++){// 预处理所有剩下的 A 和 C
		ll ans=i;
		for(int j=2;j<=i;j++)if((ans*=i-j+1)<=m)A.push_back({j,ans});
		else break;
	}
	for(int i=2;i<=m;i++){
		ll ans=i;
		for(int j=2;j<=i/2;j++)if((ans=ans*(i-j+1)/j)<=m){
			// cerr<<j<<" "<<ans<<"\n"<<i-j<<" "<<ans<<"\n";
			C.push_back({j,ans});
			if(j!=i-j)C.push_back({i-j,ans});
		}else break;
	}
	for(int i=1;i<=m;i++)dp[1][i]=1;
	ll cur=m;
	for(int _=2;_<n;_++){
		auto add=[&](int x,int y,ll v=1){(dp[_][y]+=dp[_-1][x]*v)%=mod;};
		char op=s[_-2];
		if(op=='A'){
			// xAy = 0 (x>y)
			for(int x=1;x<=m+1;x++)add(x,0,x-1);
			// 1Ax = x
			for(int x=1;x<=m;x++)add(1,x);
			// 0Ax = 1
			add(0,1,m);
			// xAy = z
			for(auto[x,z]:A)add(x,z);
		}else{
			// xCy = 0 (x>y)
			for(int x=1;x<=m+1;x++)add(x,0,x-1);
			// xCx = 1
			for(int x=1;x<=m;x++)add(x,1);
			// xC(x+1) = (x+1)
			for(int x=0;x<m;x++)add(x,x+1);
			// 0Cx = 1
			add(0,1,m-1);
			// 1Cx = x
			for(int x=1;x<=m;x++)add(1,x);
			// xCy = z
			for(auto[x,z]:C)add(x,z);
			// spe
			add(1,1,mod-1);add(1,2,mod-1);
		}
		cur=cur*m%mod;// 因为 m+1 的方案数太多了，所以可以考虑算完其他部分之后用当前的总方案数减去其他的方案数
		dp[_][m+1]=cur;
		for(int x=0;x<=m;x++)(dp[_][m+1]+=mod-dp[_][x])%=mod;
		// cerr<<_<<": ";
		// for(int x=0;x<=m+1;x++)cerr<<dp[_][x]<<" ";
		// cerr<<"\n";
	}
	ll ans=0;
	for(int y=1;y<=m;y++){// 最后一个运算符直接暴力枚举前面的结果以及这一次的数计算答案
		if(s[n-2]=='A'){
			ll cur=1;
			(ans+=dp[n-1][0])%=mod;
			for(int x=1;x<=y;x++){
				cur=cur*(y-x+1)%mod;
				(ans+=dp[n-1][x]*cur)%=mod;
			}
		}else{
			ll cur=1;
			(ans+=dp[n-1][0])%=mod;
			for(int x=1;x<=y;x++){
				cur=cur*(y-x+1)%mod*qpow(x,mod-2)%mod;
				(ans+=dp[n-1][x]*cur)%=mod;
			}
		}
	}
	cout<<ans<<"\n";
}
```

于是我们拿到了 40 分。

-----

接下来考虑刚才的转移过程，我们需要优化它。

分析上面的转移，我们需要一个数据结构支持以下操作：

1. 求 $\sum\limits_x a_x(x-1)$，单点加
2. 单点查询，全局加
3. 单点查询，单点加
4. 很多个单点查询，单点加（这部分不需要优化也比较难优化）
5. 求 $\sum\limits_x a_x(x-1)$，单点加
6. 全局求和，单点加
7. 全局右移
8. 单点查询，单点加
9. 单点查询，全局加
10. 很多个单点查询，单点加

另外因为我们一直在使用同一个数组，所以我们在 A 的时候需要清空，而在 C 的时候只需要右移。

考虑设计一种 $O(1)$ 数据结构。需要维护的东西：

- 数组 $a$，记录所有单点加的值；
- 数组 $t$，记录上一次加的时间，用于检查清空；
- 变量 $s_1$ 和 $s_2$ 分别表示 $\sum a_x$ 和 $\sum a_x(x-1)$；
- 变量 $t0$ 和 $v0$ 表示上一次清空的时间以及值（因为还需要考虑全局加的 tag）
- 变量 $v_a$ 表示全局加的值。

所有操作的实现官方题解讲的很清楚了，这里就直接贴代码了。

```cpp
namespace O1{
	ll F[200005],T[200005],*f=F+100003,*t=T+100003,s1,s2,v0,t0,va,curt;
	void add(int p,ll v){
		if(t[p]<t0)t[p]=t0,f[p]=v0;
		t[p]=++curt;
		(f[p]+=v)%=mod;
		(s1+=v)%=mod;
		(s2+=(p-1+mod)%mod*v)%=mod;
	}
	ll qry(int p){
		if(t[p]<t0)t[p]=t0,f[p]=v0;
		return (f[p]+va)%mod;
	}
	void add(ll v){
		(va+=v)%=mod;
		(s1+=v*(m+2))%=mod;
		(s2+=(1ll*m*(m+1)/2-1)%mod*v)%=mod;
	}
	ll sum1(){return s1;}
	ll sum2(){return (s2+qry(0)+mod)%mod;}
	void rt(){
		f--,t--;
		(s1+=mod-qry(m+2))%=mod,(s2+=mod-qry(m+2)*m%mod)%=mod;
		f[0]=mod-va;t[0]=++curt;
		(s2+=s1)%=mod;
	}
	void clr(){
		t0=++curt;
		v0=mod-va;
		s1=s2=0;
	}
	void prt(){
		cerr<<"after time "<<curt<<": ";
		ll rs1=0,rs2=0;
		for(int i=0;i<=m+1;i++){
			ll v=qry(i);
			cerr<<v<<",";
			(rs1+=v)%=mod;
			if(i)(rs2+=v*(i-1))%=mod;
		}
		cerr<<"   "<<sum1()<<"("<<rs1<<") "<<sum2()<<"("<<rs2<<")\n";
	}
	void test(){
		cin>>n>>m;
		while(n--){
			int op,p,v;
			cin>>op;
			if(op==1)cin>>p>>v,add(p,v);
			if(op==2)cin>>v,add(v);
			if(op==3)rt();
			if(op==4)clr();
			prt();
		}
	}
}
```

数据结构部分结束之后，仍然有一些细节问题需要注意：

- $s_1$ 和 $s_2$ 维护的和以及全局加都是包括 $0$ 和 $m+1$ 的，所以在执行全局加的时候需要对两个端点进行一些特殊处理。
- 转移的时候需要先把所有需要执行的加操作的位置以及加的值先存下来，清空或者右移之后再依次执行。

最后只剩下最后一个运算符的问题。这个时候我们相当于要求 $\sum\limits_{y=1}^m\sum\limits_{x=0}^y f_x\binom yx$，交换求和顺序之后发现 $f_x$ 的系数为 $\sum\limits_{y=x}^m\binom yx=\binom{m+1}{x+1}$，于是就可以 $O(n)$ 求了。

总复杂度 $O(n\sqrt n)$。

---

