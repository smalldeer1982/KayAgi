# New Year Letter

## 题目描述

Many countries have such a New Year or Christmas tradition as writing a letter to Santa including a wish list for presents. Vasya is an ordinary programmer boy. Like all ordinary boys, he is going to write the letter to Santa on the New Year Eve (we Russians actually expect Santa for the New Year, not for Christmas).

Vasya has come up with an algorithm he will follow while writing a letter. First he chooses two strings, $ s_{1} $ anf $ s_{2} $ , consisting of uppercase English letters. Then the boy makes string $ s_{k} $ , using a recurrent equation $ s_{n}=s_{n-2}+s_{n-1} $ , operation '+' means a concatenation (that is, the sequential record) of strings in the given order. Then Vasya writes down string $ s_{k} $ on a piece of paper, puts it in the envelope and sends in to Santa.

Vasya is absolutely sure that Santa will bring him the best present if the resulting string $ s_{k} $ has exactly $ x $ occurrences of substring AC (the short-cut reminds him оf accepted problems). Besides, Vasya decided that string $ s_{1} $ should have length $ n $ , and string $ s_{2} $ should have length $ m $ . Vasya hasn't decided anything else.

At the moment Vasya's got urgent New Year business, so he asks you to choose two strings for him, $ s_{1} $ and $ s_{2} $ in the required manner. Help Vasya.

## 样例 #1

### 输入

```
3 2 2 2
```

### 输出

```
AC
AC
```

## 样例 #2

### 输入

```
3 3 2 2
```

### 输出

```
Happy new year!
```

## 样例 #3

### 输入

```
3 0 2 2
```

### 输出

```
AA
AA
```

## 样例 #4

### 输入

```
4 3 2 1
```

### 输出

```
Happy new year!
```

## 样例 #5

### 输入

```
4 2 2 1
```

### 输出

```
Happy new year!
```

# 题解

## 作者：Push_Y (赞：6)

[view in Push_Y's blog](https://www.wzsyyh.ml/post/CF379D/)

读完题感觉分类讨论太多了，想借鉴一下题解，然而并没有题解。于是肝完大讨论之后来写篇题解。

显然，最终的 `AC` 串的个数由这么几种情况构成：

1. 初始的串 $s1$ 。
1. 初始的串 $s2$ 。
1. $s1$ 与 $s2$ 拼接处 。
1. $s2$ 与 $s1$ 拼接处 。
1. $s1$ 与 $s1$ 拼接处 。
1. $s2$ 与 $s2$ 拼接处 。

上述的前两种情况显然是斐波那契数列中的某一项。

打表推敲一下，发现后四种情况也一定可以用斐波那契数列中的某一项通过代数运算得到。

![](https://cdn.luogu.com.cn/upload/image_hosting/1vtbfkga.png)

具体的，图中表格 F 和 G 这两列都可以用 [OEIS A052952](https://oeis.org/A052952) 计算。

已知了这些东西，结合此题非常小的数据范围，就可以直接枚举两个初始串的 `AC` 串个数以及每一种拼接情况求解了。

贴一下我的代码吧，不过调错的时候越写越玄学。**建议自己当做大模拟来写**。

[提交记录](https://codeforces.com/problemset/submission/379/127042462)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pi;
inline int gin(){
    int s=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        s=(s<<3)+(s<<1)+(c^48);
        c=getchar();
    }
    return s*f;
}

pi Fib(int k) {
    if(k==0) return {0,1};
    pi p=Fib(k>>1);
    int c=p.first*(2*p.second-p.first);
    int d=p.first*p.first+p.second*p.second;
    if(k&1) return {d,c+d};
    else return {c,d};
}

signed main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    int k=gin()-2,x=gin(),n=gin(),m=gin();
    int A=Fib(k).first,B=Fib(k+1).first,AB=A,BA=Fib(k).first-(1+((k&1)?1:-1))/2,BB=Fib(k-1).first-(1-((k&1)?1:-1))/2;
    // cout<<A<<" "<<B<<" "<<AB<<" "<<BA<<" "<<BB<<"\n";
    for(int a=0;a<=n/2;a++) {
        if(a*A>x) continue;
        if(a*A==x) {
            string s1,s2;
            for(int i=1;i<=a;i++) s1+="AC";
            for(int i=1;i<=n-2*a;i++) s1+="B";
            for(int i=1;i<=m;i++) s2+="B";
            printf("%s\n%s\n",s1.c_str(),s2.c_str());
            return 0;
        }
        for(int b=0;b<=m/2;b++) {
            if(b*B==x) {
                string s1,s2;
                for(int i=1;i<=n;i++) s1+="B";
                for(int i=1;i<=b;i++) s2+="AC";
                for(int i=1;i<=m-2*b;i++) s2+="B";
                printf("%s\n%s\n",s1.c_str(),s2.c_str());
                return 0;
            }
            if(a*A+b*B>x) continue;
            if(a*A+b*B==x) {
                string s1,s2;
                for(int i=1;i<=a;i++) s1+="AC";
                for(int i=2*a+1;i<=n;i++) s1+="B";
                for(int i=1;i<=b;i++) s2+="AC";
                for(int i=2*b+1;i<=m;i++) s2+="B";
                printf("%s\n%s\n",s1.c_str(),s2.c_str());
                return 0;
            }
            if(n&1 || a<n/2) {
                if(m&1 || b<m/2) {
                    // s1开头留C s2结尾留A
                    if(a*A+b*B+BA==x) {
                        string s1,s2;
                        for(int i=1;i<=n-2*a;i++) s1+="C";
                        for(int i=1;i<=a;i++) s1+="AC";
                        for(int i=1;i<=b;i++) s2+="AC";
                        for(int i=1;i<=m-2*b;i++) s2+="A";
                        printf("%s\n%s\n",s1.c_str(),s2.c_str());
                        return 0;
                    }
                    // s1结尾留A s2开头留C
                    if(a*A+b*B+AB==x) {
                        string s1,s2;
                        for(int i=1;i<=a;i++) s1+="AC";
                        for(int i=1;i<=n-2*a;i++) s1+="A";
                        for(int i=1;i<=m-2*b;i++) s2+="C";
                        for(int i=1;i<=b;i++) s2+="AC";
                        printf("%s\n%s\n",s1.c_str(),s2.c_str());
                        return 0;
                    }
                    // s2开头留C,结尾留A
                    if(b<m/2) {
                        // s1开头留C
                        if(a*A+b*B+BA+BB==x) {
                            string s1,s2;
                            for(int i=1;i<=n-2*a;i++) s1+="C";
                            for(int i=1;i<=a;i++) s1+="AC";
                            s2+="C";
                            for(int i=1;i<=b;i++) s2+="AC";
                            for(int i=1;i<=m-2*b-1;i++) s2+="A";
                            printf("%s\n%s\n",s1.c_str(),s2.c_str());
                            return 0;
                        }
                        // s1结尾留A
                        if(a*A+b*B+AB+BB==x) {
                            string s1,s2;
                            for(int i=1;i<=a;i++) s1+="AC";
                            for(int i=1;i<=n-2*a;i++) s1+="A";
                            s2+="C";
                            for(int i=1;i<=b;i++) s2+="AC";
                            for(int i=1;i<=m-2*b-1;i++) s2+="A";
                            printf("%s\n%s\n",s1.c_str(),s2.c_str());
                            return 0;
                        }
                    }
                }
            }
            // s1,s2开头留C,结尾留A
            if(b<m/2) {
                // s1开头结尾都不留
                if(a*A+b*B+BB==x) {
                    string s1,s2;
                    s1+="B";
                    for(int i=1;i<=a;i++) s1+="AC";
                    for(int i=1;i<=n-2*a-1;i++) s1+="B";
                    s2+="C";
                    for(int i=1;i<=b;i++) s2+="AC";
                    for(int i=1;i<=m-2*b-1;i++) s2+="A";
                    printf("%s\n%s\n",s1.c_str(),s2.c_str());
                    return 0;
                }
                if(a<n/2 && a*A+b*B+AB+BA+BB==x) {
                    string s1,s2;
                    s1+="C";
                    for(int i=1;i<=a;i++) s1+="AC";
                    for(int i=1;i<=n-2*a-1;i++) s1+="A";
                    s2+="C";
                    for(int i=1;i<=b;i++) s2+="AC";
                    for(int i=1;i<=m-2*b-1;i++) s2+="A";
                    printf("%s\n%s\n",s1.c_str(),s2.c_str());
                    return 0;
                }
            }
        }
    }
    puts("Happy new year!");
    return 0;
}
```


---

## 作者：SalN (赞：2)

~~鉴于本人在精神极差的时候强行理解这个题目出 4 个意思并且每一版都写了代码然后发现第 4 版才过太逆天了写个题解。~~

首先我们考虑固定了 $s_1,s_2$ 怎么求 $s_k$ 的答案，不妨设 $s_i$ 有 $f_i$ 个 ```AC```，那么转移首先有一个 $f_i\gets f_{i-2}+f_{i-1}$，但是拼接处可能还会产生一个 ```AC```，所以我们还关心 $L_i/R_i$ 表示 $s_i$ 的第一个/最后一个字符是 ```A/C/非A非C```，然后就很好转移了。

这个东西显然只跟 $L_1/R_1/L_2/R_2/f_1/f_2$ 相关，那我们不妨枚举这个，总共有 $3\times 3\times3\times3*\frac{n}{2}\times\frac{m}{2}$ 种，每次花 $O(k)$ 验证是否等于 $k$ 就行了。

然后还有一个问题就是我们需要判一个$L_1/R_1/L_2/R_2/f_1/f_2$ 的合法性，直接贪心狂暴构造然后随便判定一下就行了，具体的，首尾确定了，然后尽量在前面放需要的 ```AC```，剩下的部分就放 ```C```。

ac code

```cpp
#include<bits/stdc++.h>
#define int long long
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)
 
using namespace std;
 
const int N=105;
 
int k, x, n, m, f[N], L[N], R[N]; 
 
int count(string a) { int ret=0; up(i,1,(int)a.size()-1) if(a[i]=='C'&&a[i-1]=='A') ++ret; return ret; }
inline int fad(char c) { if(c=='A') return 1; if(c=='C') return 0; return -1; }

string print(int a,int b,int f1,int n) {
	if(!n) return "";
	string ret=""; int nn=n, ff=f1;
	if(a==-1) --n, ret+="W"; if(a==0) --n, ret+="C";
	while(f1--) ret+="AC", n-=2; while(n-->0) ret+="C";
	if(b==-1) ret[ret.size()-1]='W'; if(b==0) ret[ret.size()-1]='C'; if(b==1) ret[ret.size()-1]='A'; 
	if(count(ret)==ff&&(int)ret.size()==nn&&ret.size()&&fad(ret[0])==a&&fad(ret[ret.size()-1])==b) return ret;
	return "";
}
 
void solve(int a,int b,int f1,int c,int d,int f2) {
	L[1]=a, R[1]=b, L[2]=c, R[2]=d, f[1]=f1, f[2]=f2;
	up(i,3,k) f[i]=f[i-2]+f[i-1]+(R[i-2]==1&&L[i-1]==0), L[i]=L[i-2], R[i]=R[i-1];
	if(f[k]==x) { cout << print(a,b,f1,n) << '\n' << print(c,d,f2,m); exit(0); }
}
 
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> k >> x >> n >> m;
	up(a,-1,1) up(b,-1,1) up(c,-1,1) up(d,-1,1) up(l,0,n/2) up(r,0,m/2) {
		string qwq=print(a,b,l,n), awa=print(c,d,r,m);
		if(qwq!=""&&awa!="") solve(a,b,l,c,d,r);
	}
	cout << "Happy new year!";
	return 0;
}
```

---

## 作者：zhicheng (赞：2)

### 思路

提供一种比较容易想到的做法。

拿到题看数据范围发现都很小，所以放心大胆地暴力。

容易发现 $s_i$ 中 `AC` 的个数等于 $s_{i-2}$ 中 `AC` 的个数加 $s_{i-1}$ 中 `AC` 的个数再加上两者拼接处可能有的一个 `AC`。

所以 $s_1$ 和 $s_2$ 从第二个字符到倒数第二个字符这之间的 `AC` 串的排布与后面拼接没有任何关系。枚举里面有几个 `AC` 即可。不是 `AC` 的地方用一个无关字母表示就没有贡献了（我的代码中用的是 `X`）。

然后对于 $s_1$ 和 $s_2$ 第一个和最后一个字符，仍然是大力枚举这个字符（分别为 `X`，`A`，`C` 的时候），然后直接模拟，判断最后结果是不是等于给定的 $x$ 即可。

模拟的具体方法就是记录前两个串的第一个和最后一个字符然后判断有没有新 `AC` 产生即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x;
char s1[110],s2[110],s[4]={"\0AC"};
void fun(int fir1,int las1,int fir2,int las2){
	int sum,l1,l2,q1,q2,w1,w2,qq=0,ww=0;
	memset(s1,0,sizeof(s1));
	s1[1]=s[fir1];
	s1[n]=s[las1];
	if(n<=3){
		qq=1;  //串长<=3时无法写入AC，需要特判
	}
	for(int i=fir1?2:1,sum1=0;i+1<=(las1?n-1:n)||qq;i+=2,sum1++){
		qq=0;
		if(sum1){
			s1[i]='A';
			s1[i+1]='C';
		}
		else{
			i-=2;
		}
		memset(s2,0,sizeof(s2));
		s2[1]=s[fir2];
		s2[m]=s[las2];
		if(m<=3){
			ww=1;
		}
		for(int j=fir2?2:1,sum2=0;j+1<=(las2?m-1:m)||ww;j+=2,sum2++){
			ww=0;
			if(sum2){
				s2[j]='A';
				s2[j+1]='C';
			}
			else{
				j-=2;
			}
            //模拟。
			l1=sum1;//s[i-2]的答案
			l2=sum2;//s[i-1]的答案
			q1=fir1;//s[i-2]的头
			q2=fir2;//s[i-1]的头
			w1=las1;//s[i-2]的尾
			w2=las2;//s[i-1]的尾
			if(n==1){
				q1=las1;
			}
			if(m==1){
				q2=las2;//特判覆盖了
			}
			for(int kk=3;kk<=k;kk++){
				sum=l1+l2+(w1==1&&q2==2);
				l1=l2;
				l2=sum; //模拟，更新
				swap(q1,q2);
				w1=w2;
				if(sum>x){
					break;
				}
			}
			if(sum==x){
				for(int kk=1;kk<=n;kk++){
					if(s1[kk]){
						printf("%c",s1[kk]);
					}
					else{
						printf("X");
					}
				}
				printf("\n");
				for(int kk=1;kk<=m;kk++){
					if(s2[kk]){
						printf("%c",s2[kk]);
					}
					else{
						printf("X");
					}
				}
				exit(0);
			}
		}
	}
}
int main(){
	scanf("%d%d%d%d",&k,&x,&n,&m);
	if(x==0){
		for(int i=1;i<=n;i++){
			printf("A");
		}
		printf("\n");
		for(int i=1;i<=m;i++){
			printf("A");
		}
		return 0;
	}
    //枚举头尾
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			for(int k=0;k<=2;k++){
				for(int l=0;l<=2;l++){
					fun(i,j,k,l);
				}
			} 
		}
	}
	printf("Happy new year!");
}
```

完结撒花！！

---

## 作者：Resolute_Faith (赞：2)

观察题目没有太多信息，但是可以先猜一点结论：

> 1. 初始字符串 $s_1,s_2$ 可能包含非 $\tt A,C$ 的字符。

不妨先定义其为**无关字符**，接下来简要证明结论 $1$：

假设在构造 $s_1,s_2$ 串的过程中，我们需要考虑一个子串 $\tt A\_C$（$\tt \_$ 表示我需要构造的字符），其贡献为 $0$，即填入字符后不存在一个 $\tt AC$ 的子串。但是我们发现无论填入 $\tt A,C$，都不能使得该串贡献为 $0$。于是我们考虑填入 $\tt X$（$\tt X$ 为任意非 $\tt A,C$ 的大写字母），便可以使得该串贡献为 $0$。

> 2. 若字符串 $s$ 存在若干 $\tt X$ 字符，则该字符可以被统一替换为 $\tt B$。

该结论非常显然，因为字符 $\tt X$ 不可能参与任何贡献，所以无论我选择什么字符都不会改变该串总贡献。

> 3. 若字符串 $s_k$ 存在 $s_{k,i}=\texttt {A},s_{k,i+1}\neq\tt{C}$，则将 $s_{k,i}$ 替换为 $\tt B$ 不改变总贡献；同理，若字符串 $s_k$ 存在 $s_{k,i}\neq \texttt{A},s_{k,i+1}=\texttt{C}$，则将 $s_{k,i+1}$ 替换为 $\tt B$ 不改变总贡献。

由题目定义可以得到，字符 $s_{k,i}$ 有贡献当且仅当它可以与前面的字符组成 $\tt AC$ 或可以与后面的字符组成 $\tt AC$。显然这两个条件并不能同时取到，因此如果一个字符不能产生贡献，他就可以被替换为无关字符 $\tt B$。

有了上面的结论 $3$，我们可以发现任何字符串在保证贡献相同的条件下，都可以变为只由 $\tt AC$ 和 $\tt B$ 组成的字符串。

> 4. 若一个字符串只由 $\tt AC$ 和 $\tt B$ 组成，那么无论如何排列这些 $\tt AC,B$（$\tt AC$ 必须作为一个整体参与排列），总贡献不会改变。

该结论也十分显然，若 $\tt B$ 被排列在两个 $\tt AC$ 串之间，总贡献不变。因为 $\tt B$ 没有破坏任何一个 $\tt AC$ 的结构，也不会参与任何 $\tt AC$ 的构成。所以结论 $4$ 显然。

回到题目本身，我们考虑 $s_1$ 的首字符为 $p_1$，尾字符为 $q_1$；$s_2$ 的首字符为 $p_2$，尾字符为 $q_2$。

则我们可以得到 $s_3$ 的首字符为 $p_1$，尾字符为 $q_2$；$s_4$ 的首字符为 $p_2$，尾字符为 $q_2$，依此类推。

不难发现对于 $k\geqslant 3$ 时，若 $k$ 为奇数，则 $s_k$ 的首字符为 $p_1$，尾字符为 $q_2$；若 $k$ 为偶数，则 $s_k$ 的首字符为 $p_2$，尾字符为 $q_2$。

设 $(q_2,p_2)$ 能产生贡献 $x_1$，$(q_2,p_1)$ 能产生贡献 $x_2$，$(q_1,p_2)$ 能产生贡献 $x_3$。

不妨先计算 $(q_2,p_2)$ 能带来的总贡献，即 $s_2$ 与 $s_2$ 一共相连多少次。设 $f_k$ 表示 $s_2$ 与 $s_2$ 相连的次数，考虑到每一个 $s_k$（$k$ 为奇数）在与 $s_{k+1}$ 拼接的过程中，必然会产生一次额外的 $(q_2,p_2)$，所以状态转移方程如下：

$$
\begin{cases}
f_k=1,&k=5\;\text{or}\;6\\
f_k=f_{k-1}+f_{k-2}+1,&k\equiv 1\pmod 2\\
f_k=f_{k-1}+f_{k-2},&k\equiv 0\pmod 2
\end{cases}
$$

于是我们可以在 $\mathcal{O}(k)$ 的复杂度内得到 $f_k$。

接下来考虑计算 $(q_2,p_1)$ 能带来的总贡献，即 $s_2$ 与 $s_1$ 一共相连多少次。设 $g_k$ 表示 $s_2$ 与 $s_1$ 相连多少次，考虑到每一个 $s_k$（$k$ 为偶数）与 $s_{k+1}$ 拼接的过程中，必然会产生一次额外的 $(q_2,p_1)$，所以状态转移方程如下：

$$
\begin{cases}
g_k=1,&k=4\;\text{or}\;5\\
g_k=g_{k-1}+g_{k-2}+1,&k\equiv 0\pmod 2\\
g_k=g_{k-1}+g_{k-2},&k\equiv 1\pmod 2
\end{cases}
$$

于是我们可以在 $\mathcal{O}(k)$ 的复杂度内得到 $g_k$。

再接下来考虑 $(q_1,p_2)$ 能带来的总贡献，即 $s_1$ 与 $s_2$ 一共相连多少次。设 $\varphi_k$ 表示 $s_1$ 与 $s_2$ 相连的次数，与上面不同的是，在子串的拼接中，不会产生额外的 $(q_1,p_2)$，当且仅当第一次拼接出 $s_3$ 时，才产生一次额外的贡献，所以状态转移方程如下：

$$
\begin{cases}
\varphi_k=1,&k=3\;\text{or}\;4\\
\varphi_k=\varphi_{k-1}+\varphi_{k-2},&\text{Otherwise}\\
\end{cases}
$$

因此在枚举 $p_1,q_1,p_2,q_2$ 的情况下，我们可以 $\mathcal{O}(k)$ 的得到额外贡献 $\Delta x=f_k+g_k+\varphi_k$。

接着考虑只由 $s_1,s_2$ 产生的贡献，设 $s_1$ 产生贡献为 $x_4$，$s_2$ 产生贡献为 $x_5$。不妨设 $dp_{k}$ 表示只由 $s_1,s_2$ 产生的总贡献，有状态转移方程如下：

$$
\begin{cases}
dp_k=x_4,&k=1\\
dp_k=x_5,&k=2\\
dp_k=dp_{k-2}+dp_{k-1},&\text{Otherwise}
\end{cases}
$$

该方程可以在 $\mathcal{O}(k)$ 的时间内计算完毕，可以用程序证明 $x_4,x_5$ 都取到最大值 $50$ 时，$dp_k$ 最大不会超过 `long long` 的数据范围，因此同理可得 $f_k,g_k,\varphi_k$ 也不会超过该范围。

于是在已知 $s_1,s_2$ 的情况下，我们可以在 $\mathcal{O}(k)$ 的复杂度内计算 $s_k$ 的子串 $\tt AC$ 数量 $x$。我们只需要考虑如何尽可能少地枚举出 $s_1,s_2$，使其能够得到每一个可能的 $x$。

结合上面的四条结论，我们只需要构造两个 $\tt PXQ$ 型的串（其中 $\tt P,Q$ 为 $\tt A,C$ 中的任意一种字符，而 $\tt X$ 表示中间的全部字符）。因为 $\tt X$ 与产生的额外贡献无关，而 $\tt P,Q$ 与产生的额外贡献有关，故作此定义。

结论 $3,4$ 告诉我们，最终构造的字符串在保证贡献相同的情况下，一定与 $\tt PACAC...ACBB...BQ$ 的贡献相同。这里 $\tt P=A$ 时，下一位应当从 $\tt C$ 开始填入，但本质相同不做赘述，可以用来讨论。

那么枚举这样的一个串需要的时间复杂度时多少呢？可以发现我们本质是得到有多少个 $\tt AC$ 的串，而该值在 $s_1$ 或 $s_2$ 中不会超过 $50$，故可以枚举，枚举 $s_1$ 的时间复杂度为 $\mathcal{O}(9n)$，枚举后构造的时间复杂度为 $\mathcal{O}(n)$。同理得到，如果我们枚举 $s_1,s_2$，则总时间复杂度不会超过 $\mathcal{O}(81nkm)$。极限情况下依然可以通过。

务必注意讨论 $s_1,s_2$ 长度 $\leqslant 2$ 的情况，特判即可。

有一点乱，将就着看吧，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int k,sum,n,m,dp[N];
char s1[N],s2[N];
bool check(char a,char b){
	if(a=='A'&&b=='C') return true;
	else return false;
}
signed main(){
	scanf("%lld %lld %lld %lld",&k,&sum,&n,&m);
	for(register int p1='A';p1<='C';p1++){
		for(register int q1='A';q1<='C';q1++){
			if(n==1&&p1!=q1) continue;
			for(register int p2='A';p2<='C';p2++){
				for(register int q2='A';q2<='C';q2++){
					if(m==1&&p2!=q2) continue;
					for(register int x1=0;x1<=50;x1++){
						for(register int x2=0;x2<=50;x2++){
							s1[1]=p1,s1[n]=q1;
							s2[1]=p2,s2[m]=q2;
							int cntx=0,cnty=0;
							if(n==2) cntx=check(p1,q1);
							if(m==2) cnty=check(p2,q2);
							for(register int i=2;i<n;i++){
								if(s1[i-1]=='A'){
									if(cntx<x1) cntx++,s1[i]='C';
									else s1[i]='B';
								}
								if(s1[i-1]=='C'){
									if(i==n-1&&cntx<x1&&q1=='C') cntx++,s1[i]='A';
									else if(cntx<x1) s1[i]='A';
								}
								if(s1[i-1]=='B') s1[i]='B';
							}
							if(cntx!=x1) continue;
							for(register int i=2;i<m;i++){
								if(s2[i-1]=='A'){
									if(cnty<x2) cnty++,s2[i]='C';
									else s2[i]='B';
								}
								if(s2[i-1]=='C'){
									if(i==m-1&&cnty<x2&&q2=='C') cnty++,s2[i]='A';
									else if(cnty<x2) s2[i]='A';
								}
								if(s2[i-1]=='B') s2[i]='B';
							}
							if(cnty!=x2) continue;
							dp[1]=1,dp[2]=1;
							for(register int i=3;i<=k;i++) dp[i]=dp[i-1]+dp[i-2];
							int x=dp[k-2]*check(q1,p2);
							dp[1]=1,dp[2]=1;
							for(register int i=3;i<=k;i++) dp[i]=dp[i-1]+dp[i-2]+(i>=3)*(i%2==1);
							x+=dp[k-4]*check(q2,p2)*(k>=4)+dp[k-3]*check(q2,p1)*(k>=3);
							dp[1]=x1,dp[2]=x2; 
							for(register int i=3;i<=k;i++) dp[i]=dp[i-1]+dp[i-2];
							if(x+dp[k]==sum){
								printf("%s\n%s",s1+1,s2+1);
								return 0;
							}
						}
					}
				}
			}
		}
	}
	printf("Happy new year!");
}
```

---

## 作者：Frictional (赞：0)

## 题意
有两个初始字符串 $s_1,s_2$，长度分别为 $n,m$，第三个字符串由前两个拼接而成，即 $s_3=s_1+s_2$，之后的每个字符串都由前面的两个字符串拼接而成（类似斐波那契数列）。给出 $s_k$ 中有几个 $AC$，找到一组合法的 $s_1,s_2$。没有合法解就输出 Happy new year!

## 解法
我们将 $s_1$ 简称为 $a$，$s_2$ 简称为 $b$。则能形成 $AC$ 的只有以下几种情况：

1.前两个字符串中原本就有的 $AC$。

2.在字符串拼接处有的 $AC$。

在字符串拼接处只有 $ba,bb,ab$ 这三种情况。我们设这三种情况的拼接处分别有 $x,y,z$ 个 $AC$，原本的 $a,b$ 中有 $p,q$ 个 $AC$。之后我们就可以列出来个方程，暴力枚举方程的解，判断是否合法就可以了。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P pair<int,int>
#define int long long
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define gc getchar()
#define pc putchar
using namespace std;
inline int rd(){
    int x=0,f=1;
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
int ans;
int k,x,n,m;
int a[55],b[55],ab[55],ba[55],bb[55];
int A,B,AB,BA,BB;
char l[55],r[55];
void init(){
    a[1]=b[2]=1;
    b[1]=a[2]=0;
    ab[1]=ab[2]=ba[1]=ba[2]=0;
    l[1]=r[1]='a',l[2]=r[2]='b';
    bb[1]=bb[2]=0;
    FOR(i,3,k){
        l[i]=l[i-2];
        r[i]=r[i-1];
        a[i]=a[i-1]+a[i-2],b[i]=b[i-1]+b[i-2],ba[i]=ba[i-1]+ba[i-2],ab[i]=ab[i-1]+ab[i-2],bb[i]=bb[i-1]+bb[i-2];
        if(r[i-2]=='b'&&l[i-1]=='a') ba[i]++;
        if(r[i-2]=='a'&&l[i-1]=='b') ab[i]++;
        if(r[i-2]=='b'&&l[i-1]=='b') bb[i]++;
    }
}
string pa,pb;
string zero;
signed main(){
    cin>>k>>x>>n>>m;
    init();
    FOR(i,0,n/2){
        FOR(j,0,m/2){
            FOR(ab1,0,1){
                FOR(ba1,0,1){
                    FOR(bb1,0,1){
                        if(i*a[k]+j*b[k]+ab1*ab[k]+ba1*ba[k]+bb1*bb[k]==x&&j*2+(ab1||bb1)+(ba1||bb1)<=m&&i*2+ab1+ba1<=n&&!(ab1&&ba1&&(!bb1))){
                            pa=pb=zero;
                            if(ba1) pa+="C";
                            if(ab1||bb1) pb+="C";
                            FOR(o,1,i) pa+="AC";
                            FOR(o,1,j) pb+="AC";
                            if(i*2+ab1+ba1<n) FOR(o,i*2+ba1+1,n-ab1) pa+="X";
                            if(j*2+(ab1||bb1)+(ba1||bb1)<m) FOR(o,j*2+(ab1||bb1)+1,m-(ba1||bb1)) pb+="X";
                            if(ba1||bb1){
                                pb+="A";
                            }
                            if(ab1){
                                pa+="A"; 
                            }
                            cout<<pa<<'\n'<<pb;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    cout<<"Happy new year!";
    return 0;
}

```

---

