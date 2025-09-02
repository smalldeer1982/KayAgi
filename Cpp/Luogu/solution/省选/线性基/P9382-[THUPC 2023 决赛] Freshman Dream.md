# [THUPC 2023 决赛] Freshman Dream

## 题目描述

小 J 正在学习矩阵乘法。

一旁的小 L 告诉他：只要将两个矩阵对应的位置乘起来，那就能得到两个矩阵的乘法了。

这当然是不对的，但是小 L 要继续骗小 J。为此，她需要在自己的 OJ 上放一道矩阵乘法题，使得这样的矩阵乘法也能得到正确的答案。

因为小 L 的 OJ 跑的很慢并且空间限制也很小，所以这道矩阵乘法题的答案都是 $\bmod 2$ 意义下的。

现在小 L 开始造数据。她先随机生成了一个 $n\times n$ 的矩阵 $A$，具体地，每一个元素以 $\frac 12$ 的概率为 $1$，剩下的概率为 $0$，且这些事件相互独立。现在，她还要设计另一个 $n\times n$  的 $01$ 矩阵 $B$，使得 $AB_{ij}\equiv A_{ij}B_{ij}\pmod 2$。

小 L 试图随机生成矩阵，但是找不出什么满足要求的矩阵；她试图构造几个矩阵，发现只会构造全 $0$ 矩阵，这太明显了。现在，她将生成数据的重任交给了你，你需要给出一个满足要求的 $B$，同时为了不让大家看出数据有猫腻，她还额外要求了 $B$ 里面恰好有 $k$ 个 $1$。

## 说明/提示

**【样例说明 #1】**

这里的 $A$ 是单位矩阵，构造的 $B$ 也是单位矩阵，乘积也为单位矩阵。同时，将对应位置相乘也为单位矩阵，并且 $B$ 中恰有 $k=3$ 个 $1$，故满足要求。

本样例中 $n$ 不为 $100$，但保证所有测试数据中 $n$ 均为 $100$。

**【数据范围】**

对于所有测试数据，$n=100$，$0 \le k \le n^2$，$a_{ij}\in \{0,1\}$，所有 $a_{ij}$ 均为独立均匀随机。

**【题目来源】**

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）决赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023> 查看。

## 样例 #1

### 输入

```
3 3
1 0 0
0 1 0
0 0 1```

### 输出

```
1
1 0 0
0 1 0
0 0 1```

# 题解

## 作者：Graphcity (赞：5)

根据矩阵乘法的式子 $C_{i,j}=\sum_kA_{i,k}\times B_{k,j}$，可以发现 $B$ 的每一列都是独立的。假设我们正在处理第 $p$ 列，根据题目所给的信息，列出如下方程：

$$
\begin{cases}
a_{1,1}b_{1,k}+a_{1,2}b_{2,k}+\cdots a_{1,n}b_{n,k}=a_{1,k}b_{1,k}\\
a_{2,1}b_{1,k}+a_{2,2}b_{2,k}+\cdots a_{2,n}b_{n,k}=a_{2,k}b_{2,k}\\
\ \vdots \\
a_{n,1}b_{1,k}+a_{n,2}b_{2,k}+\cdots a_{n,n}b_{n,k}=a_{n,k}b_{n,k}\\
\end{cases}
$$

移项，写成增广矩阵：

$$
\begin{bmatrix}
a_{1,1}-a_{1,k} & a_{1,2} & \cdots & a_{1,n} & 0 \\
a_{2,1} & a_{2,2}-a_{2,k} & \cdots & a_{2,n} & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots \\
a_{n,1} & a_{n,2} & \cdots & a_{n,n}-a{n,k} & 0
\end{bmatrix}
$$

设这个矩阵为 $A$。它最右边都是零，可以暂时不用管。对去掉最后一列的 $A$ 矩阵进行高斯-约旦消元，可以得到线性基。这个线性基有如下性质：

1. 如果 $A_{i,i}=0$，那么整行都是零。如果 $A_{i,i}=1$，那么 $i$ 这一列只有 $A_{i,i}=1$。
2. 对于任意一行 $k$，有等式 $\sum_{i}A_{k,i}b_{k,i}=0$。

由于数据随机，所以 $A$ 矩阵的自由元（也就是全为零的行代表的元）很少。（证明见官方题解）而且，如果确定了所有自由元，那么其它元的取值都能够确定。（因为性质 2 的等式中至多只有一个非自由元）

暴力枚举自由元，就可以得到一组解。题目要求所有列中 1 的个数恰好等于 $k$，做一个背包即可。

[Code](https://www.luogu.com.cn/paste/c518bj7l)

---

## 作者：do_it_tomorrow (赞：2)

[更好的阅读体验](https://www.doittomorrow.xyz/post/thupc-2023-jue-sai-freshman-dream/)

感谢 [Cczzyy20150005](/user/630240) 大佬指出了矩阵化简的错误。

## 题目大意

给定 $n\times n$ 的 $01$ 矩阵 $A$ 要求构造同样大小的矩阵 $B$ 要求满足 $A\times B$ 与两个矩阵中的元素一一乘起来，而且要求 $B$ 矩阵中恰好有 $k$ 个 $1$。

数据范围满足 $1\le n\le 100,0\le k\le n^2$ 且 $A$ 为**随机**生成。

## 思路

分析矩阵乘法的定义 $(A\times B)_{i,j}=\sum\limits_{k=1}^n A_{i,k}\cdot b_{k,j}$，可以发现对于 $B$ 矩阵的第 $j$ 行是相对独立的可以单独讨论。

分析题目条件，先不考虑取模，可以列出方程：

$$
\left\{\begin{matrix}
A_{1,1}\cdot B_{1,k}+A_{1,2}\cdot B_{2,k}+\cdots +A_{1,n}\cdot B_{n,k}=A_{1,k}\cdot B_{1,k} \\
A_{2,1}\cdot B_{1,k}+A_{2,2}\cdot B_{2,k}+\cdots +A_{2,n}\cdot B_{n,k}=A_{2,k}\cdot B_{2,k}  \\
\vdots   \\
A_{n,1}\cdot B_{1,k}+A_{n,2}\cdot B_{2,k}+\cdots +A_{n,n}\cdot B_{n,k}=A_{n,k}\cdot B_{n,k}  
\end{matrix}\right.
$$

接着进行移项：

$$
\left\{\begin{matrix}
A_{1,1}\cdot B_{1,k}+A_{1,2}\cdot B_{2,k}+\cdots +A_{1,n}\cdot B_{n,k}-A_{1,k}\cdot B_{1,k}=0 \\
A_{2,1}\cdot B_{1,k}+A_{2,2}\cdot B_{2,k}+\cdots +A_{2,n}\cdot B_{n,k}-A_{2,k}\cdot B_{2,k} =0 \\
\vdots   \\
A_{n,1}\cdot B_{1,k}+A_{n,2}\cdot B_{2,k}+\cdots +A_{n,n}\cdot B_{n,k}-A_{n,k}\cdot B_{n,k}=0  
\end{matrix}\right.
$$

提取公因式：

$$
\left\{\begin{matrix}
(A_{1,1}-A_{1,k})\cdot B_{1,k}+A_{1,2}\cdot B_{2,k}+\cdots +A_{1,n}\cdot B_{n,k}=0 \\
A_{2,1}\cdot B_{1,k}+(A_{2,2}-A_{2,k})\cdot B_{2,k}+\cdots +A_{2,n}\cdot B_{n,k}=0 \\
\vdots   \\
A_{n,1}\cdot B_{1,k}+A_{n,2}\cdot B_{2,k}+\cdots +(A_{n,n}-A_{n,k})\cdot B_{n,k}=0  
\end{matrix}\right.
$$

考虑因为所有的元素都是 $0$ 或者 $1$，所以可以可以将上面的运算转化为异或。

$$
\left\{\begin{matrix}
[(A_{1,1}\oplus A_{1,k})\cdot B_{1,k}]\oplus [A_{1,2}\cdot B_{2,k}]\oplus \cdots \oplus [A_{1,n}\cdot B_{n,k}]=0 \\
[A_{2,1}\cdot B_{1,k}]\oplus [(A_{2,2}\oplus A_{2,k})\cdot B_{2,k}]\oplus \cdots \oplus [A_{2,n}\cdot B_{n,k}]=0 \\
\vdots   \\
[A_{n,1}\cdot B_{1,k}]\oplus [A_{n,2}\cdot B_{2,k}]\oplus \cdots \oplus [(A_{n,n}\oplus A_{n,k})\cdot B_{n,k}]=0  
\end{matrix}\right.
$$
整理成系数的增广矩阵：

$$
\begin{bmatrix}
A_{1,1}\oplus A_{1,k}  & A_{1,2} & \cdots & A_{1,n} &0 \\
A_{2,1}  & A_{2,2}\oplus A_{2,k} & \cdots & A_{2,n} & 0\\
\vdots &\vdots &\ddots &\vdots &\vdots\\
 A_{n,1} & A_{n,2} & \cdots & A_{n,n}\oplus A_{n,k} &0
\end{bmatrix}
$$

写一个线性基（高斯消元也可以）求出方程的解，接着跑一个 DP 求出具体的方案即可。

其中 $f_{i,j}$ 表示是否有前 $i$ 行一共用了 $j$ 个 $1$ 的方案，而 $g_{i,j}$ 则记录了选择的方案。

总共的时间复杂度为 $O(n^4)$，但是有一个 bitset 的优化。

```c++
#include<iostream>
#include<bitset>
#include<stack>
#include<vector>
#include<cstring>
using namespace std;
const int N=105;
int n,m,top;
bitset<N>A[N],a[N],s[N],g[N][N*N];
bitset<N*N>f[N];
vector<bitset<N> >st;
bool vis[N],ans[N][N];
int read(){int x;cin>>x;return x;}
void insert(bitset<N>a){
	for(int i=1;i<=n;i++){
		if(!a[i]) continue;
		if(s[i].none()){s[i]=a;return;}
		a^=s[i];
	}
}
void solve(int id){
	for(int i=1;i<=n;i++) a[i]=A[i],a[i][i]=A[i][i]^A[i][id],s[i].reset();
	for(int i=1;i<=n;i++) insert(a[i]);
	st.clear();
	for(int i=n;i>=1;i--){
		if(s[i].none()) continue;
		for(int j=1;j<i;j++) if(s[j][i]) s[j]^=s[i];
	}
	for(int i=1;i<=n;i++){
		if(!s[i].none()) continue;
		bitset<N> top;top[i]=1;
		for(int j=1;j<=n;j++) if(s[j][i]) top[j]=1;
        st.push_back(top);
	}
    memset(vis,0,sizeof(vis));
	for(int xwd=0;xwd<(1<<st.size());xwd++){
		bitset<N>top;
		for(int i=0;i<st.size();i++) if(xwd&(1<<i)) top^=st[i];
		int siz=top.count();
		if(vis[siz]) continue;
		vis[siz]=1;
		for(int i=siz;i<=m;i++) if(!f[id][i]&&f[id-1][i-siz]) f[id][i]=1,g[id][i]=top;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=read();
	f[0][0]=1;
	for(int i=1;i<=n;i++) solve(i);
	if(!f[n][m]) cout<<-1<<'\n',exit(0);
	cout<<1<<'\n';
	for(int i=n,p=m;i>=1;i--){
		bitset<N> top=g[i][p];
		for(int j=1;j<=n;j++) if(top[j]) ans[j][i]=1;
		p-=top.count();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cout<<ans[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

题目的约束相当于：对每个 $1\le i,j\le n$，都有
$$
\sum_{k=1}^na_{i,k}b_{k,j}=a_{i,j}b_{i,j}
$$
发现 $b$ 的每一列是独立的。这里加法可以看作 xor。

依次考虑每一列，如果当前在第 $p$ 列，那么有以下方程组：
$$
\sum_{k=1}^na_{i,k}b_{k,p}=a_{i,p}b_{i,p}
$$
其中 $i=1,2,\cdots,n$。移项就可以得到一个右侧常数均为 $0$ 的方程组，其系数矩阵形如
$$
\begin{bmatrix}
a_{1,1}-a_{1,p}&a_{1,2}&\cdots&a_{1,n}\\
a_{2,1}&a_{2,2}-a_{2,p}&\cdots&a_{2,n}\\
\vdots&\vdots&\ddots&\vdots\\
a_{n,1}&a_{n,2}&\cdots&a_{n,n}-a_{n,p}
\end{bmatrix}
$$
这里减法也是 xor。然后由于 $a$ 是随机的，可以证明这样的矩阵自由元很少。

>$(n-1) \times n$ 矩阵秩为 $n-1-k$ 的概率可以这样估计，考虑这些向量都在对应的空间中的概率为 $\frac{1}{2^{kn}}$，而这样的空间数量和零空间数量相同，后者可以用零空间的任意张成组来简单估计上界为 $\binom{2^n}{k}$，因此是 $O(\frac{1}{k!})$ 级别的。

那么每一行解数很少，可以暴力处理出所有解。

还需要满足恰好有 $k$ 个 $1$，那么背包即可。使用 bitset 优化消元，复杂度 $O(\frac{n^4}{w})$。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define fi first
#define se second
#define mk make_pair

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}
const int N=205;
#define bs bitset<N> 

vector<bs>getSol(vector<bs>A,int n){
	auto Gauss=[&](vector<bs>&f,int n){
		vector<bs>w(n+1);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)if(f[i][j]){
				if(!w[j][j]){w[j]=f[i];break;}
				f[i]^=w[j];
			}
		}
		for(int i=1;i<=n;i++)if(w[i][i]){
			for(int j=1;j<i;j++)if(w[j][i])w[j]^=w[i];
		}
		f=w;
	};
	
	Gauss(A,n);vector<int>pos;
	for(int i=1;i<=n;i++)if(A[i][i]==0)pos.emplace_back(i);
	int V=pos.size();
	vector<bs>Res;
	for(int S=0;S<(1<<V);S++){
		vector<bs>F(V);
		vector<int>ans(n+V+1,0);bs B;
		for(int j=0;j<V;j++)F[j][pos[j]]=1,ans[n+j+1]=((S>>j)&1);
		auto tA=A;
		for(int j=0;j<V;j++)for(int i=1;i<=n;i++)if(A[i][pos[j]])A[i]^=F[j],ans[i]^=ans[n+j+1];
		for(int i=1;i<=n;i++)if(A[i][i])B[i]=ans[i];
		for(int j=0;j<V;j++)B[pos[j]]=ans[n+j+1];
		Res.emplace_back(B);
		A=tA;
	}
	return Res;
}

bitset<N*N>dp[N];
void ins(int i,int x){dp[i]|=(dp[i-1]<<x);}

void solve(){
	int n=read();int k=read();
	vector<bs>A(n+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)A[i][j]=read();
	
	dp[0][0]=1;
	vector<vector<bs> >W(n+1);
	for(int p=1;p<=n;p++){
		vector<bs>B(n+1);
		for(int i=1;i<=n;i++)B[i]=A[i];
		for(int i=1;i<=n;i++)B[i][i]=(B[i][i]^A[i][p]);
		W[p]=getSol(B,n);
		for(auto t:W[p])ins(p,t.count());
	}
	if(dp[n][k]!=1)return puts("-1"),void();
	puts("1");
	
	vector<bs>Ans(n+1);
	function<void(int,int)>getans=[&](int i,int j){
		if(i==0)return ;
		for(auto t:W[i]){
			int cnt=t.count();
			if(cnt<=j&&dp[i-1][j-cnt]){
				for(int p=1;p<=n;p++)Ans[p][i]=t[p];
				getans(i-1,j-cnt);return ;
			}
		}
	};
	getans(n,k);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cout<<Ans[i][j]<<" \n"[j==n];
}

signed main(void){

	solve();

	return 0;
}
```

---

