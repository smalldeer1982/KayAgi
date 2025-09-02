# Vasya and Shifts

## 题目描述

Vasya has a set of $ 4n $ strings of equal length, consisting of lowercase English letters "a", "b", "c", "d" and "e". Moreover, the set is split into $ n $ groups of $ 4 $ equal strings each. Vasya also has one special string $ a $ of the same length, consisting of letters "a" only.

Vasya wants to obtain from string $ a $ some fixed string $ b $ , in order to do this, he can use the strings from his set in any order. When he uses some string $ x $ , each of the letters in string $ a $ replaces with the next letter in alphabet as many times as the alphabet position, counting from zero, of the corresponding letter in string $ x $ . Within this process the next letter in alphabet after "e" is "a".

For example, if some letter in $ a $ equals "b", and the letter on the same position in $ x $ equals "c", then the letter in $ a $ becomes equal "d", because "c" is the second alphabet letter, counting from zero. If some letter in $ a $ equals "e", and on the same position in $ x $ is "d", then the letter in $ a $ becomes "c". For example, if the string $ a $ equals "abcde", and string $ x $ equals "baddc", then $ a $ becomes "bbabb".

A used string disappears, but Vasya can use equal strings several times.

Vasya wants to know for $ q $ given strings $ b $ , how many ways there are to obtain from the string $ a $ string $ b $ using the given set of $ 4n $ strings? Two ways are different if the number of strings used from some group of $ 4 $ strings is different. Help Vasya compute the answers for these questions modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example, we have $ 4 $ strings "b". Then we have the only way for each string $ b $ : select $ 0 $ strings "b" to get "a" and select $ 4 $ strings "b" to get "e", respectively. So, we have $ 1 $ way for each request.

In the second example, note that the choice of the string "aaaa" does not change anything, that is we can choose any amount of it (from $ 0 $ to $ 4 $ , it's $ 5 $ different ways) and we have to select the line "bbbb" $ 2 $ times, since other variants do not fit. We get that we have $ 5 $ ways for the request.

## 样例 #1

### 输入

```
1 1
b
2
a
e
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
2 4
aaaa
bbbb
1
cccc
```

### 输出

```
5
```

# 题解

## 作者：daniEl_lElE (赞：1)

考虑一个每维是 $0\sim4$ 的线性基，将所有的串塞入线性基当中。设 `abcde` 分别为 $0\sim4$。不难发现除了 `a` 以外的循环节都为 $5$。也就是说，取 $0\sim4$ 个 `bcde` 均能构成 `abcde` 中每个一遍。

类比普通线性基进行操作，插入的时候如果对应位置已经有值那么就将对应位置扣减至 $0$（也可以预处理一个除法表来解决），插不入线性基里的东西是自由元，就可以将答案乘 $5$。

计算到某个串的方案本质上就是判断他是否可达，可达答案就是 $5^{cnt}$，其中 $cnt$ 为自由元数量。类似插入地考虑即可。

总复杂度 $O((n+q)m^2)$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1; 
	}
	return ans;
}
struct node{
	int p[505];
};
int n,m;
node a[505];
node rem[505];
int opermul[5][5]={{0,0,0,0,0},{0,1,2,3,4},{0,2,4,1,3},{0,3,1,4,2},{0,4,3,2,1}};
int operadd[5][5]={{0,1,2,3,4},{1,2,3,4,0},{2,3,4,0,1},{3,4,0,1,2},{4,0,1,2,3}};
int operdiv[5][5];
node mul(node x,int y){
	for(int i=1;i<=m;i++) x.p[i]=opermul[x.p[i]][y];
	return x;
}
node rev(node x){
	for(int i=1;i<=m;i++) x.p[i]=(x.p[i]!=0)?5-x.p[i]:0;
	return x;
}
node add(node x,node y){
	for(int i=1;i<=m;i++) x.p[i]=operadd[x.p[i]][y.p[i]];
	return x;
}
signed main(){
	for(int i=0;i<5;i++) for(int j=0;j<5;j++) operdiv[opermul[i][j]][i]=j;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c; cin>>c;
			a[i].p[j]=c-'a';
		}
	}
	int fcnt=0;
	for(int i=1;i<=n;i++){
		bool ok=1;
		for(int j=1;j<=m;j++){
			if(a[i].p[j]){
				if(rem[j].p[j]){
					int l=operdiv[a[i].p[j]][rem[j].p[j]];
					a[i]=add(a[i],rev(mul(rem[j],l)));
				}
				else{
					rem[j]=a[i];
					ok=0;
					break;
				}
			}
		}
		fcnt+=ok;
	}
	int ans=qp(5,fcnt);
	int t; cin>>t;
	while(t--){
		node b;
		for(int j=1;j<=m;j++){
			char c; cin>>c;
			b.p[j]=c-'a';
		}
		bool ok=1;
		for(int j=1;j<=m;j++){
			if(b.p[j]){
				if(rem[j].p[j]){
					int l=operdiv[b.p[j]][rem[j].p[j]];
					b=add(b,rev(mul(rem[j],l)));
				}
				else{
					ok=0;
					break;
				}
			}
		}
		cout<<(ok*ans)<<"\n";
	}
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

~~被 sinsop90 神仙爆踩了~~

### 题意

好抽象啊，不讲了……

### 分析

这题不难设方程，假设 $x_i$ 表示第 $i$ 个字符串用了几个，$a_{i,j}$ 表示对第 $i$ 个字符串，第 $j$ 位对应的字符在 $5$ 进制下对应的权值，就有：

$$\begin{cases}\sum_{i=1}^na_{i,1}x_i\bmod5=b_1\\\sum_{i=1}^na_{i,2}x_i\bmod5=b_2\\\vdots\\\sum_{i=1}^na_{i,m}x_i\bmod5=b_m\end{cases}$$

发现这是高斯消元，方案数的统计就直接是 $5^{n-cur+1}$，其中 $cur$ 为本质不同方程数，即线性不相关的方程数。无解很好判，不讲。但是直接暴力做的复杂度是 $\mathcal O(qn^3)$，这显然过不去。

我们发现我们做了很多无用功，系数矩阵进行了 $q$ 次消元，而实际上只需要消元 $1$ 次就够了。所以我们考虑把所有答案都扔到数组中同意进行消元，判无解单次复杂度 $\mathcal O(n)$，所以总复杂度 $\mathcal O((n+q)n^2+qn)$。

### code

```cpp
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) a[j][i] = s[j] - 'a';
	}
	T = read();
	for (int i = 1; i <= T; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) a[j][i + n] = s[j] - 'a';
	}
	for (int i = 1; i <= n; i++) {
		int d = 0;
		for (int j = cur; j <= m; j++) if (a[j][i]) { d = j; break; }
		if (!d) continue;
		swap(a[cur], a[d]);
		for (int j = n + T; j >= i; --j) a[cur][j] = a[cur][j] * iv[a[cur][i]] % 5;
		for (int j = 1; j <= m; j++)
			if (j != cur)
				for (int k = n + T; k >= i; --k)
					a[j][k] = (a[j][k] - a[j][i] * a[cur][k] % 5 + 5) % 5;
		++cur;
	}
	for (int i = 1, ans = ksm(5, n - cur + 1); i <= T; i++) {
		bool fl = 0;
		for (int j = cur; j <= m; j++) if (a[j][i + n]) { fl = 1; break; }
		if (fl) { puts("0"); continue; }
		writeln(ans);
	}
}
// I love WHQ!
```

---

## 作者：MornStar (赞：0)

## Vasya and Shifts
题意已经很清楚了。

### sol
按照题意做 $q$ 次高斯消元，时间复杂度 $O(n^2mq)$，很明显过不了。

这个时候就需要我们去发现题目的性质，显而易见的是，高斯消元的系数矩阵并未发生变化，我们是否可以只做一次高斯消元呢？

答案是可以的。我们可以在高斯消元是记录下对系数矩阵的整行进行的操作，如交换两行，整行乘以一个数，某行减去另一行。操作的总数只有 $O(nm)$ 个。

接着我们只需要对 $q$ 个询问进行同样的操作，就可以模拟这一列放在高斯消元里的变化情况了。

最后判断无解，有解的情况答案就是 $5^{num}$，$num$ 是自由元的数量。

tips：因为系数相同，所以最后自由元的个数也是相同的，也就是答案只会是 $0$ 或 $5^{num}$。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
struct Todo{int opt,fr,to,tim;}todo[N*N*5];
const int mod=5;
long long q_pow(long long x,long long b,long long Mod){
	long long c=1;
	while(b){
		if(b&1)	c=c*x%Mod;
		x=x*x%Mod,b>>=1;
	}
	return c;
}
int inv(int x){return q_pow(x,mod-2,mod);}
int n,m,q,mat[N][N],now,cnt,num[N],ans;
string s;
int GaussElimination(){
	now=1;
	for(int i=1;i<=n;i++){
		int pos=now;
		while(!mat[pos][i]&&pos<=m)	pos++;
		if(pos>m)	continue;
		swap(mat[now],mat[pos]);todo[++cnt]={3,now,pos,0};
		todo[++cnt]={1,now,0,inv(mat[now][i])};
		for(int j=n;j>=i;j--)	mat[now][j]=mat[now][j]*inv(mat[now][i])%mod;
		for(int j=1;j<=m;j++){
			if(j==now)	continue;
			todo[++cnt]={2,now,j,mat[j][i]};
			for(int k=n;k>=i;k--)	mat[j][k]=((mat[j][k]-mat[j][i]*mat[now][k]%mod)%mod+mod)%mod;
		}
		now++;
	}
	return q_pow(5,n-now+1,1e9+7);
}
int solve(){
	for(int i=1;i<=cnt;i++){
		if(todo[i].opt==1)	(num[todo[i].fr]*=todo[i].tim)%=mod;
		else if(todo[i].opt==2)	num[todo[i].to]=((num[todo[i].to]-num[todo[i].fr]*todo[i].tim%mod)%mod+mod)%mod;
		else	swap(num[todo[i].fr],num[todo[i].to]);
	}
	for(int i=now;i<=m;i++){
		if(num[i])	return 0;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;m=max(m,n);
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<s.length();j++)	mat[j+1][i]=s[j]-'a';
	}
	ans=GaussElimination();
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>s;
		for(int j=0;j<s.length();j++)	num[j+1]=s[j]-'a';
		cout<<solve()<<"\n";
	}
}
```

---

