# 题目信息

# 「DTOI-5」进行一个排的重 (Minimum Version)

## 题目背景

**本题与 Maximum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最小。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\min}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\min}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&500&20 \operatorname{pts}\cr\hline
\sf3&5\times10^3&20 \operatorname{pts}\cr\hline
\sf4&10^5&20 \operatorname{pts}\cr\hline
\sf5&5\times10^5&30 \operatorname{pts}\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
3 48```

# AI分析结果

• 综合分析与结论：
    - 思路方面：各题解均通过分类讨论解决问题，主要分为存在 \(p_i = q_i = n\) 和不存在 \(p_i = q_i = n\) 两种情况。对于第一种情况，将 \((n, n)\) 放首位，答案为 \(2\)，方案数为 \((n - 1)!\)；对于第二种情况，将 \(p_i = n\) 或 \(q_i = n\) 的项放首位，答案为 \(3\)，通过分析满足条件的排列方式来计算方案数。
    - 算法要点：计算阶乘、逆元（用于除法取模），并根据不同情况分类计算结果。
    - 解决难点：在不存在 \(p_i = q_i = n\) 的情况下，准确分析并计算满足最小权值的排列方案数。

    - 各题解质量评价：
        - FFTotoro：思路清晰，代码简洁，通过乘法逆元计算方案数，得4星。
        - DengDuck：思路表述清晰，利用组合数公式化简计算方案数，得4星。
        - Leasier：详细分析了最优解情况和方案数计算，时间复杂度为 \(O(n)\)，但代码相对复杂，得4星。
        - gyyyyx：思路正确，但代码中自定义的 `MUL` 函数可读性稍差，得3星。

  - 所选的题解：
    - 题解1 - FFTotoro（4星）
      - 关键亮点：思路清晰直接，分类讨论明确，代码简洁高效，利用快速幂求逆元解决除法取模问题。
      - 重点代码核心实现思想：先定义计算阶乘、快速幂和求逆元的函数，读入数据后判断属于哪种情况，直接根据公式输出结果。
```cpp
int f(int n){
  int s=1;
  for(int i=2;i<=n;i++)
    (s*=i)%=mod;
  return s;
}
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%mod*a%mod;
    a=a%mod*a%mod; b>>=1;
  }
  return r;
}
int inv(int x){return qpow(x,mod-2);}
main(){
  ios::sync_with_stdio(false);
  int n,x,y; cin>>n;
  vector<pii> a(n);
  for(auto &i:a)cin>>i.first;
  for(auto &i:a)cin>>i.second;
  for(auto [p,q]:a){
    if(p==n)x=q; if(q==n)y=p;
  } 
  if(x==n)cout<<"2 "<<f(n-1)<<endl; 
  else cout<<"3 "<<f(n-1)*((inv(n-x)+inv(n-y))%mod)%mod<<endl; 
  return 0;
}
```
    - 题解2 - DengDuck（4星）
      - 关键亮点：对每种情况的方案数计算解释详细，通过组合数公式推导得出化简后的方案数公式。
      - 重点代码核心实现思想：定义结构体存储数据，通过快速幂计算逆元，读入数据判断情况后按公式输出结果。
```cpp
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)F=F*i%mod;
	for(int i=1;i<=n;i++)cin>>a[i].p;
	for(int i=1;i<=n;i++)cin>>a[i].q;
	for(int i=1;i<=n;i++)
	{
		if(a[i].p==n)x=a[i].q;
		if(a[i].q==n)y=a[i].p;
	}
	if(x==n)
	{
		cout<<2<<' '<<F<<endl;
	}
	else 
	{
		cout<<3<<' '<<F*(ksm(n-x,mod-2)+ksm(n-y,mod-2))%mod<<endl;
	}
}
```
    - 题解3 - Leasier（4星）
      - 关键亮点：详细证明了最优解的情况，对方案数计算通过排列组合公式详细推导，时间复杂度优化到 \(O(n)\)。
      - 重点代码核心实现思想：先预处理阶乘和阶乘逆元，读入数据判断情况，对于方案数为3的情况，通过枚举中间项数量，利用排列组合公式计算方案数。
```cpp
inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}
inline ll arrange(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[n - m] % mod;
}
int main(){
	int n = read(), pos1, pos2;
	init(n);
	for (register int i = 1; i <= n; i++){
		p[i] = read();
		if (p[i] == n) pos1 = i;
	}
	for (register int i = 1; i <= n; i++){
		q[i] = read();
		if (q[i] == n) pos2 = i;
	}
	if (pos1 == pos2){
		printf("2 %lld", fac[n - 1]);
	} else {
		ll ans = 0;
		for (register int i = 0; i < q[pos1]; i++){
			ans = (ans + fac[n - i - 2] * arrange(q[pos1] - 1, i) % mod) % mod;
		}
		for (register int i = 0; i < p[pos2]; i++){
			ans = (ans + fac[n - i - 2] * arrange(p[pos2] - 1, i) % mod) % mod;
		}
		printf("3 %lld", ans);
	}
	return 0;
}
```
• 最优关键思路或技巧：
    - 分类讨论思想：清晰划分不同情况，分别求解，简化问题。
    - 利用排列组合知识：在计算方案数时，通过分析条件得出组合数公式，并化简计算。
    - 逆元的应用：解决除法取模问题，保证计算结果在模意义下的正确性。
• 可拓展之处：
此类题目属于排列组合与最值问题结合的类型，类似套路为分析不同情况，利用排列组合知识计算方案数，同时注意取模运算。对于更复杂的情况，可能需要结合动态规划等其他算法。
• 推荐洛谷题目：
    - P1036 [NOIP2002 普及组] 选数：考察组合数计算和取模运算。
    - P2671 [NOIP2015 普及组] 求和：结合排列组合和递推思想。
    - P1850 换教室：结合概率、动态规划和排列组合知识。
• 个人心得：无。 

---
处理用时：45.56秒