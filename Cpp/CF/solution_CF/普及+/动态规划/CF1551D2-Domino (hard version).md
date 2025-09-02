# Domino (hard version)

## 题目描述

The only difference between this problem and D1 is that you don't have to provide the way to construct the answer in D1, but you have to do it in this problem.

There's a table of $ n \times m $ cells ( $ n $ rows and $ m $ columns). The value of $ n \cdot m $ is even.

A domino is a figure that consists of two cells having a common side. It may be horizontal (one of the cells is to the right of the other) or vertical (one of the cells is above the other).

You need to place $ \frac{nm}{2} $ dominoes on the table so that exactly $ k $ of them are horizontal and all the other dominoes are vertical. The dominoes cannot overlap and must fill the whole table.

## 样例 #1

### 输入

```
8
4 4 2
2 3 0
3 2 3
1 2 0
2 4 2
5 2 2
2 17 16
2 1 1```

### 输出

```
YES
accx
aegx
bega
bdda
YES
aha
aha
YES
zz
aa
zz
NO
YES
aaza
bbza
NO
YES
bbaabbaabbaabbaay
ddccddccddccddccy
NO```

# 题解

## 作者：Lynkcat (赞：3)

分类讨论。

* $n$ 为偶数

考虑从下往上填，我们最终的目标是使每一列上空余的个数为偶数，这样才能完整地填入竖直骨牌。

那么我们就有个很显然的做法，从第一列开始，每两列都填满，直到不够填满 $n$ 行，判断剩余的是否为奇数，如果是则说明我们没有办法填出合法状态，因为总有一个列剩余部分为奇数。如果是偶数就填完水平后补上竖直的。

* $n$ 为奇数

考虑每一列剩余的个数要为偶数，容易想到先在最后一行填上，就转化成 $n$ 为偶数的情况了。


关于具体填字母的方案，我在水平的骨牌上用了 $a$、$b$ 两种字母，竖直的骨牌上用了 $c$、$d$ 两种字母，这种摆法应该不难判断相邻的骨牌之间的关系，这里不多赘述。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define y1 nmsl
#define il inline
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 1000000007
#define Endl endl
//#define int ll
#define N 2005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int T,n,m,k;
char A[N][N];
signed main()
{
	T=read();
	while (T--)
	{
		n=read(),m=read(),k=read();int kkk=k;
			int ans=1;
			for (int i=1;i<=n;i++)	for (int j=1;j<=m;j++) A[i][j]='*';
			if (m%2==0&&n%2==1)
			{
				if (k<m/2) ans=0;
				else
				{
					k-=m/2;
					if (k%2==1) ans=0;
					else ans=1;
				}	
				if (ans) 
				{
					puts("YES");
					k=kkk;
					for (int i=1;i<=m/2;i++)
					{
						A[n][i*2-1]=A[n][i*2]='a'+(i%2);
						k--;
					}
					for (int i=1;i<=m/2;i++)
					{
						if (!k) break;
						for (int j=n-1;j>=1;j--)
						{
							if (!k) break;
							A[j][2*i-1]=A[j][2*i]=(A[j+1][2*i]=='a')?'b':'a';
							k--;
						}
					}
					if (n>1)
					{
						int i=1;
						for (int j=1;j<=m;j++)
						{
							if (A[i][j]=='*')
							{
								A[i][j]=A[i+1][j]='c'+j%2;
							}
						}
						for (int i=3;i<n;i+=2)
						{
							for (int j=1;j<=m;j++)
							{
								if (A[i][j]=='*')
								{
									A[i][j]=A[i+1][j]=(A[i-1][j]=='c')?'d':'c';
								}
							}
						}
					}
					for (int i=1;i<=n;i++)
					{
						for (int j=1;j<=m;j++) cout<<A[i][j];
						puts("");
					}
				}
				else puts("NO");
			} else
			{
				
				for (int i=1;i<=m/2;i++)
				{
					if (k<n)
					{
						if ((n-k)%2==1) ans=0;
						else ans=1;
						k=0;
						break;
					}
					k-=n;
				}
				if (k!=0) ans=0;
				if (ans) 
				{
					puts("YES");
					k=kkk;
					for (int i=1;i<=m/2;i++)
					{
						if (!k) break;
						A[n][2*i-1]=A[n][2*i]=(A[n][2*i-2]=='a')?'b':'a';
						k--;
						for (int j=n-1;j>=1;j--)
						{
							if (!k) break;
							A[j][2*i-1]=A[j][2*i]=(A[j+1][2*i]=='a')?'b':'a';
							k--;
						}
					}
					if (n>1)
					{
						int i=1;
						for (int j=1;j<=m;j++)
						{
							if (A[i][j]=='*')
							{
								A[i][j]=A[i+1][j]='c'+j%2;
							}
						}
						for (int i=3;i<n;i+=2)
						{
							for (int j=1;j<=m;j++)
							{
								if (A[i][j]=='*')
								{
									A[i][j]=A[i+1][j]=(A[i-1][j]=='c')?'d':'c';
								}
							}
						}
					}
					for (int i=1;i<=n;i++)
					{
						for (int j=1;j<=m;j++) cout<<A[i][j];
						puts("");
					}
				} else puts("NO");
			}
	}
}
/*

*/

```

---

## 作者：xuanyuan_Niubi (赞：1)

交了20多遍，az。

# 题意简述

$ n \times m $ 的桌面用 $ \frac{n\times m}{2} $ 个$ 1\times 2 $ 的多米诺骨牌覆盖完且其中恰好有 $ k $ 个多米诺骨牌是水平放置的。

问是否可以达到条件，如果可以就先输出 ``YES``，再输出构造的方案，不行就只输出 ``NO``。

对于每组构造方案，一个多米诺骨牌所占的两个方格用一个相同的小写字母表示，不允许两个相邻的多米诺骨牌用同一小写字母表示。

# 分析

这道题要在简单版的基础上解决，无论 $ n $、$ m $ 哪个是奇数，都想办法将其转化为 $ n $、$ m $ 都为偶数的情况解决。

如果 $ n $ 是奇数，就先把最后一排放满，然后 $ n-1 $ 就成了偶数。若 $ m$ 是奇数，就先把最后一列放满，然后 $ m-1 $ 就成了偶数。

之后 $ n $、$ m $ 都是偶数了。怎么放呢？我的策略是这样的：

- 先把 $ k $ 个需要横着放的从最右边开始，两列两列地从上往下放。这两列放完了就换下两列放。假如放完是这样的：

$$
\begin{pmatrix}
0 & 0 & e & e & a & a\\
0 & 0 & f & f & b & b\\
0 & 0 & 0 & 0 & c & c\\
0 & 0 & 0 & 0 & d & d
\end{pmatrix}
$$

- 之后发现最后放的 $ f$ 下面有空的没有放，那就用竖着的把下面空的放了。每次放 $2\times 2 $ 的格子。

$$
\begin{pmatrix}
0 & 0 & e & e & a & a\\
0 & 0 & f & f & b & b\\
0 & 0 & h & g & c & c\\
0 & 0 & h & g & d & d
\end{pmatrix}
$$

- 最后将剩下的一列一列放。

$$
\begin{pmatrix}
k & i & e & e & a & a\\
k & i & f & f & b & b\\
l & j & h & g & c & c\\
l & j & h & g & d & d
\end{pmatrix}
$$

放的主要过程没有什么问题，主要的就是相邻的多米诺骨牌不可以用同一字母表示。情况较多。

- 在第一步时，有：

  1. 当前要填的字母和右边已经填了的字母一样。
  2. 当前要填的字母和下面一排已经填了的字母一样（下面为什么会有字母呢，因为可能为了使 $ n $ 变成偶数已经将第 $ n $ 行填了）。

- 在第二步时，有：

  3. 左边那一列当前要填的字母和右边已经填了的字母一样。

  4. 左边那一列当前要填的字母和下面第二排已经填了的字母一样。参考下面：
     $$
     \begin{pmatrix}
     & & \cdots\\
     0 & 0 & z & z & a & a\\
     0 & 0 & a & a & b & b\\
     0 & 0 & 0 & b & c & c\\
     0 & 0 & 0 & b & d & d\\
     a & a & b & b & c & c
     \end{pmatrix}
     $$

  5. 右边那一列要填的字母和右边那一列下面已经填了的字母一样。参考下面：
     $$
     \begin{pmatrix}
     & & \cdots\\
     0 & 0 & y & y & w & w\\
     0 & 0 & z & z & x & x\\
     0 & 0 & b & a & y & y\\
     0 & 0 & b & a & z & z\\
     a & a & b & b & c & c
     \end{pmatrix}
     $$

- 在第三步时，有：

  6. 当前要填的和左边或左下角已经填了的字母一样。参考下面：
     $$
     \begin{pmatrix}
     & & \cdots\\
     0 & z & y & y & w & w\\
     0 & z & z & z & x & x\\
     0 & 0 & c & a & y & y\\
     0 & 0 & c & a & z & z\\
     a & a & b & b & c & c
     \end{pmatrix}
     $$

  7. 要填的和下面已经填了的一样。参考情况 $ 4 $。

基本上就讲完了。对于每种情况都换下一个字母就可以了。

#### code

```c++
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int M=210;
inline int read(){
	char c=getchar();int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
int ans[M][M];
inline void print(int n,int m){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%c",ans[i][j]+'a');
		puts("");
	}
}
inline void chang(int &x){x++;if(x>=25)x-=25;}
signed main(){
	int T=read();
	while(T--){
		int n=read(),m=read(),k=read(),t=m/2,c=0;
		int nn=n,mm=m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)ans[i][j]=0;
		}
		if(!(m&1)&&k>=t&&n&1){//若n是奇数，先放最后一排 
			for(int i=1;i<=m;i+=2){
				ans[n][i]=ans[n][i+1]=++c;if(c>=25)c-=25;//注1
			}
			k-=t,n--;
		}
		if(n*t<k){
			puts("NO");continue;
		}
		if(!(n&1)&&!(k&1)){
			puts("YES");
			if(m&1){//若m是奇数，先放最后一列 
				for(int i=1;i<=n;i+=2){
					ans[i][m]=ans[i+1][m]=++c;if(c>=25)c-=25;
				}
				m--;
			}
			int i;
			for(i=1;k;i++){//先把k个横着的摆完 
				if(ans[i][m+1]==c+1||ans[i+1][m]==c+1)c++;if(c>=25)c-=25;//情况1、2
				ans[i][m]=ans[i][m-1]=++c;if(c>=25)c-=25;
				if(i==n)i-=n,m-=2;//这两列摆完了，换下两列
				k--;
			}
			for(int j=i;j<=n-1;j+=2){//横着摆的最后那两列会空下一些格子，先把这些摆满 
				if(ans[j][m+1]==c+1||ans[j+1][m+1]==c+1)c++;if(c>=25)c-=25;//情况3
				if(ans[j+2][m]==c+1)c++;if(c>=25)c-=25;//情况4
				ans[j][m]=ans[j+1][m]=++c;if(c>=25)c-=25;
				if(ans[j+2][m-1]==c+1)c++;if(c>=25)c-=25;//情况5
				ans[j][m-1]=ans[j+1][m-1]=++c;if(c>=25)c-=25;
				if(j==n-1)m-=2;//这两列摆完了。
			}
			for(int i=1;;i+=2){//之后就一列一列地摆 
				if(ans[i][m+1]==c+1||ans[i+1][m+1]==c+1)c++;if(c>=25)c-=25;//情况6
				if(ans[i+2][m]==c+1)c++;if(c>=25)c-=25;//情况7
				if(ans[i][m+1]==c+1||ans[i+1][m+1]==c+1)c++;if(c>=25)c-=25;//注2
				if(!ans[i][m]&&!ans[i+1][m])ans[i][m]=ans[i+1][m]=++c;if(c>=25)c-=25;//注3
				if(i>=n-1){//这一列摆完了，换下一列
					if(m<=1)break;//真的摆完了
					i-=n,m-=1;
				}
			}
			print(nn,mm);
		}
		else puts("NO");
	}
	return 0;
}
```

**注**：

1. 每次对 $ c $ 操作后都要让他在小写字母的范围内。所以如果 $ c\ge25 $ 那就 $ -25 $。如果不想每次都这样的话，就需要在判断情况的时候对 $ (c+1)\mod26 $。
2. 为什么又要判断一次情况 $ 6 $ 呢？因为如果你为了避开情况 $ 7 $ 而满足了情况 $ 6 $ 的情况是存在的。
3. 为什么要要填的地方没有填才填？因为有只有一排的情况，如 ``1 6 3``，不加这个判断，就会输出 ``bbccde``。

---

## 作者：dthythxth_Huge_Brain (赞：0)

## 前言
分类讨论水题。

## 解题思路

1. $n \equiv 0 \pmod{2}$ 且 $m \equiv 1 \pmod{2}$。  
   显然将网格分成 $2 \times 2$ 的小网格，每个小网格上可以放 $2$ 个横着的骨牌或 $2$ 个竖着的骨牌，所以需满足 $k \equiv 0 \pmod{2}$。
2. $n \equiv 1 \pmod{2}$ 且 $m \equiv 0 \pmod{2}$。  
   将第一行用横着的骨牌填满，剩下的见 1 的构造，可得 $k \ge \frac{m}{2}$ 且 $k - \frac{m}{2} \equiv 0 \pmod{2}$。
3. $n \equiv 0 \pmod{2}$ 且 $m \equiv 1 \pmod{2}$。  
   将第一列用竖着的骨牌填满，剩下的见 1 的构造，可得 $k \le \frac{n\times(m-1)}{2}$ 且 $k \equiv 0 \pmod{2}$。

于是 D1，D2 就喜提 AC 了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
int t,n,m,k,ans[102][102],sum;
signed main(){
    scanf("%lld",&t);
    for(;t--;){
        memset(ans,-1,sizeof ans),sum=0;
        scanf("%lld%lld%lld",&n,&m,&k);
        if(!((n&1))&&!((m&1))&&k&1){
            puts("NO");
            continue;
        }
        else if(n*m&1){
            puts("NO");
            continue;
        }
        else if((n&1)&&!((m&1))&&(k<m/2||k-m/2&1)){
            puts("NO");
            continue;
        }
        else if(!((n&1))&&(m&1)&&(k&1||k>n*(m-1)/2)){
            puts("NO");
            continue;
        }
        else puts("YES");
        if(!(n&1)&&!(m&1)){
            for(int i=1;i<=n;i+=2){
                for(int j=1;j<=m;j+=2){
                    if(sum<k){
                        sum+=2;
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i-1][j+1]!=I)ans[i][j]=ans[i][j+1]=I;
                        for(int I=0;I<26;I++)if(ans[i][j]!=I&&ans[i+1][j-1]!=I&&ans[i][j+1]!=I)ans[i+1][j]=ans[i+1][j+1]=I;
                    }
                    else{
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i+1][j-1]!=I)ans[i][j]=ans[i+1][j]=I;
                        for(int I=0;I<26;I++)if(ans[i-1][j+1]!=I&&ans[i][j]!=I&&ans[i+1][j]!=I)ans[i][j+1]=ans[i+1][j+1]=I;
                    }
                }
            }
        }
        else if(n&1&&!(m&1)){
            sum=m/2;
            for(int j=1;j<=m;j+=2)for(int I=0;I<26;I++)if(ans[0][j]!=I&&ans[1][j-1]!=I&&ans[0][j+1]!=I)ans[1][j]=ans[1][j+1]=I;
            for(int i=2;i<=n;i+=2){
                for(int j=1;j<=m;j+=2){
                    if(sum<k){
                        sum+=2;
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i-1][j+1]!=I)ans[i][j]=ans[i][j+1]=I;
                        for(int I=0;I<26;I++)if(ans[i][j]!=I&&ans[i+1][j-1]!=I&&ans[i][j+1]!=I)ans[i+1][j]=ans[i+1][j+1]=I;
                    }
                    else{
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i+1][j-1]!=I)ans[i][j]=ans[i+1][j]=I;
                        for(int I=0;I<26;I++)if(ans[i-1][j+1]!=I&&ans[i][j]!=I&&ans[i+1][j]!=I)ans[i][j+1]=ans[i+1][j+1]=I;
                    }
                }
            }
        }
        else{
            for(int i=1;i<=n;i+=2)for(int I=0;I<26;I++)if(ans[i-1][1]!=I&&ans[i][0]!=I&&ans[i+1][0]!=I)ans[i][1]=ans[i+1][1]=I;
            for(int i=1;i<=n;i+=2){
                for(int j=2;j<=m;j+=2){
                    if(sum<k){
                        sum+=2;
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i-1][j+1]!=I)ans[i][j]=ans[i][j+1]=I;
                        for(int I=0;I<26;I++)if(ans[i][j]!=I&&ans[i+1][j-1]!=I&&ans[i][j+1]!=I)ans[i+1][j]=ans[i+1][j+1]=I;
                    }
                    else{
                        for(int I=0;I<26;I++)if(ans[i-1][j]!=I&&ans[i][j-1]!=I&&ans[i+1][j-1]!=I)ans[i][j]=ans[i+1][j]=I;
                        for(int I=0;I<26;I++)if(ans[i-1][j+1]!=I&&ans[i][j]!=I&&ans[i+1][j]!=I)ans[i][j+1]=ans[i+1][j+1]=I;
                    }
                }
            }
        }
        for(int i=1;i<=n;puts(""),i++)for(int j=1;j<=m;j++)printf("%c",ans[i][j]+'a'); 
    }
    return 0;
}
```

---

## 作者：ncwzdlsd (赞：0)

分讨。

以下三种情况对 $k$ 的限制详见 D1 题解，这里只考虑合法的情况。

1. $n,m$ 均为偶数。

2. $n$ 为奇数，$m$ 为偶数。

3. $n$ 为偶数，$m$ 为奇数。

对于情况 1，把矩阵拆分成 $2\times 2$ 的小矩阵，填够 $k$ 个横的多米诺后全部填竖的即可。

对于情况 2，最后一行记录 $\dfrac{m}{2}$ 个横的多米诺，其他按情况 $1$ 放 $k-\dfrac{m}{2}$ 个横的多米诺考虑即可。

对于情况 3，最后一列记录 $\dfrac{n}{2}$ 个竖的多米诺，其他按情况 $1$ 放 $k$ 个横的多米诺考虑即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=105;
char ans[105][105];
int n,m,k;

void op1(int a,int b,int k)
{
    int cnt=0;
    for(int i=1;i<=a/2;i++)
        for(int j=1;j<=b/2;j++)
        {
            cnt++;
            char c=(((i+j)%2)?'a':'c');
            if(cnt>k/2) ans[i*2][j*2-1]=c,ans[i*2-1][j*2-1]=c,ans[i*2][j*2]=c+1,ans[i*2-1][j*2]=c+1;
            else ans[i*2][j*2-1]=c,ans[i*2-1][j*2-1]=c+1,ans[i*2][j*2]=c,ans[i*2-1][j*2]=c+1;
        }
}

void op2()
{
    op1(n-1,m,k-m/2);
    int tmp=0;
    for(int i=1;i<m;i+=2)
    {
        tmp++;
        if(tmp%2) ans[n][i]='e',ans[n][i+1]='e';
        else ans[n][i]='f',ans[n][i+1]='f';
    }
}

void op3()
{
    op1(n,m-1,k);
    int tmp=0;
    for(int i=1;i<n;i+=2)
    {
        tmp++;
        if(tmp%2) ans[i][m]='e',ans[i+1][m]='e';
        else ans[i][m]='f',ans[i+1][m]='f';
    }
}

void solve()
{
    bool flag=0;
    cin>>n>>m>>k;
    if(n%2==0){if(k%2==0&&n*(m/2)>=k) flag=1;}
    else {if(m%2==0&&(k-m/2)%2==0&&k>=m/2) flag=1;}
    if(!flag) return cout<<"NO\n",void();
    cout<<"YES\n";
    if(n%2==0&&m%2==0) op1(n,m,k);
    else if(n%2!=0&&m%2==0) op2();
    else if(n%2==0&&m%2!=0) op3();
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=m;j++) cout<<ans[i][j];
        cout<<'\n';
    }
}

int main()
{
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1551D2 题解



## 思路分析

显然考虑把 $k$ 个横着的都聚拢到最上面，那么每一列在除去横着的骨牌的数量后，剩下的高度应该是偶数，只有这样才能用竖着的骨牌填满这一列。

由于题目已经保证了 $2\mid nm$，因此我们可以按 $n\bmod 2,m\bmod 2$ 的值分成以下三类情况：

1. $n\bmod 2=0,m\bmod 2=1$：

此时最右边一列用竖着的骨牌填满，假如竖着的骨牌不足 $\dfrac n2$ 个则无解。

剩下的列考虑用 $2$ 个横着的骨牌组成一个 $2\times 2$ 的“方块”，这样每个“方块”填进去不会影响每一列剩下的高度的奇偶性，因此如果 $2\mid k$ 时我们可以构造一种合法的方案，同样我们也可以证明 $2\nmid k$ 时无解。

2. $n\bmod2=1,m\bmod 2=0$：

显然先把一行用横着的骨牌填满，假如横着的骨牌不足 $\dfrac m2$ 则无解。

剩下的一样考虑构造方块，类似上一种情况，当且仅当剩下的的骨牌数为偶数时有解。

3. $n\bmod2=0,m\bmod2=0$：

此时直接构造方块，有解当且仅当 $2\mid k$。

根据上面的分析，我们能够得到判定条件和构造方案，模拟即可。

时间复杂度 $\Theta(nm)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=101,dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int n,m,a[MAXN][MAXN];
char ch[MAXN][MAXN];
inline bool valid(int i,int j) {
	return 1<=i&&i<=n&&1<=j&&j<=m;
}
inline void get(int i,int j) {
	if(ch[i][j]) return ;
	int i2=0,j2=0;
	for(int k:{0,1,2,3}) {
		int x=i+dx[k],y=j+dy[k];
		if(!valid(x,y)) continue;
		if(a[x][y]==a[i][j]) {
			i2=x,j2=y;
			continue;
		}
	}
	for(char ret='a';ret<='z';++ret) {
		bool ok=true;
		for(int k:{0,1,2,3}) {
			int x=i+dx[k],y=j+dy[k];
			if(!valid(x,y)||(x==i2&&y==j2)) continue;
			if(ch[x][y]==ret) {
				ok=false;
				break;
			} 
		}
		for(int k:{0,1,2,3}) {
			int x=i2+dx[k],y=j2+dy[k];
			if(!valid(x,y)||(x==i&&y==j)) continue;
			if(ch[x][y]==ret) {
				ok=false;
				break;
			} 
		}
		if(ok) {
			ch[i][j]=ch[i2][j2]=ret;
			return ;
		}
	}
	return ;
}
inline void solve() {
	int k,cnt=0;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			a[i][j]=ch[i][j]=0;
		}
	}
	if(n%2==0&&m%2==1) {
		if(k>n*(m/2)) {
			puts("NO");	
			return ;
		} else {
			if(k%2==0) {
				puts("YES");
				for(int i=1;i<=n;i+=2) {
					for(int j=1;j<m;j+=2) {
						if(cnt>=k) goto fill;
						a[i][j]=a[i][j+1]=++cnt;
						a[i+1][j]=a[i+1][j+1]=++cnt;
					}
				}
			} else {
				puts("NO");
				return ;
			}
		}
	}
	if(n%2==1&&m%2==0) {
		if(k<m/2) {
			puts("NO");
			return ;
		} else {
			if((k-m/2)%2==0) {
				puts("YES");
				for(int j=1;j<=m;j+=2) a[n][j]=a[n][j+1]=++cnt;
				for(int i=1;i<n;i+=2) {
					for(int j=1;j<=m;j+=2) {
						if(cnt>=k) goto fill;
						a[i][j]=a[i][j+1]=++cnt;
						a[i+1][j]=a[i+1][j+1]=++cnt;
					}
				}
			} else {
				puts("NO");
				return ;
			}
		}
	}
	if(n%2==0&&m%2==0) {
		if(k%2==0) {
			puts("YES");
			for(int i=1;i<=n;i+=2) {
				for(int j=1;j<=m;j+=2) {
					if(cnt>=k) goto fill;
					a[i][j]=a[i][j+1]=++cnt;
					a[i+1][j]=a[i+1][j+1]=++cnt;
				}
			}
		} else {
			puts("NO");
			return ;
		}
	}
	fill:;
	for(int i=1;i<=n;i+=2) {
		for(int j=1;j<=m;++j) {
			if(!a[i][j]) {
				a[i][j]=a[i+1][j]=++cnt;
			}
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			get(i,j);
			printf("%c",ch[i][j]);
		}
		puts("");
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```





---

## 作者：little_sheep917 (赞：0)

> 定义多米诺骨牌是一个 $1\times 2$ 的小矩形 . 给定 $n,m,k$，求是否可以将一个 $n\times m$ 的方格（ $n$ 行 $m$ 列）用多米诺密铺（不重不漏地铺满），其中横向的多米诺有 $k$ 个。若可以，则给出任意一种构造方案。
>
> 输出方案时，输出一个由小写字母组成的 $n\times m$ 的字母矩阵，两个相邻的单元格拥有相同的字母表明这两个单元格由一个多米诺覆盖，否则不算。
>
> $1\leq t\leq 10$
>
> $1\leq n,m\leq 100,\ 0\leq k\leq \frac{nm}{2},\ n\cdot m$ 是偶数

暑假比赛时想了很久都没有想出来，现在来看，为什么有点一眼 ...

可以将矩形分类解决，题目中要求要不重不漏地铺满 .

1. $n$ 是奇数，$m$ 是偶数 .

   那么，第一行都必须要铺横向的 . 要铺 $\frac{m}{2}$ 个 . 所以，如果 $k<\frac{m}{2}$ 的可以判断无解了 . 接下来，因为纵向的要占据偶数行，所以，横向的必须两两铺，才能保证最后纵向的能不重不漏地铺满 . 如果 $k-\frac{m}{2}$ 不是偶数的也可以判断无解了 . 剩下的暴力模拟，先放第一行，再把横向的放完，剩下放纵向的 .

2. $n$ 是偶数，$m$ 是奇数 .

   第一列必须用纵向的铺 . 所以，如果 $k<\frac{n(m-1)}{2}$ 或者 $k$ 是奇数的是无解的 ，否则有解 . 接着，先放第一列的纵向，再两个两个放横向的 . 剩下放纵向的 .

3. $n$ 是偶数，$m$ 是奇数 .

   $k$ 是奇数的是无解的，否则有解 . 先两个两个放横向的，剩下的放纵向的 .

最后用字母表示也不是很难 . 要判断一下，不能用这两个格子四周的格子 . 

时间复杂度 : $\mathrm O(tnm)$

空间复杂度 : $O(nm)$

code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int t;
int n,m,k;
int cnt=0;
int a[110][110];
char ans[110][110];
bool used[30];
void check(int x,int y){
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<0||nx>n||ny<0||ny>m)continue;
		if(ans[nx][ny]!=-1)used[ans[nx][ny]-'a']=true;
	}	
}
void output(){
	memset(ans,-1,sizeof(ans));
	for(int i=0;i<n;i++)for(int j=0;j<m;j++){
		if(ans[i][j]!=-1)continue;
		if(j+1<m&&a[i][j]==a[i][j+1]){
			memset(used,0,sizeof(used));
			check(i,j);
			check(i,j+1);
			char c;
			for(int l=0;l<26;l++){
				if(!used[l]){
					c=l;
					break;
				}
			}
			ans[i][j]=ans[i][j+1]='a'+c;
		}
		if(i+1<n&&a[i][j]==a[i+1][j]){
			memset(used,0,sizeof(used));
			check(i,j);
			check(i+1,j);
			char c;
			for(int l=0;l<26;l++){
				if(!used[l]){
					c=l;
					break;
				}
			}
			ans[i][j]=ans[i+1][j]='a'+c;
		}
	}
	puts("YES");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)putchar(ans[i][j]);
		putchar('\n');
	}
}
void solve1(){
	if(k<m/2||(k-m/2)%2!=0){
		puts("NO");
		return;
	}
	for(int i=0;i<m/2;i++){
		a[0][i<<1]=a[0][i<<1|1]=cnt++;
	}
	k-=m/2;
	for(int i=0;i<m/2;i++){
		for(int j=1;j<n;j++){
			if(k==0)break;
			a[j][i<<1]=a[j][i<<1|1]=cnt++;
		//	cout<<j<<","<<(i<<1)<<" "<<j<<","<<(i<<1|1)<<endl;
			k--;
		}
	}
	for(int i=1;i<n;i+=2)for(int j=0;j<m;j++){
		if(a[i][j]==-1&&a[i+1][j]==-1){
			a[i][j]=a[i+1][j]=cnt++;
		}
	}
	output();
}
void solve2(){
	if(k>n*(m-1)/2||k%2!=0){
		puts("NO");
		return;
	}
	for(int i=0;i<n/2;i++){
		a[i<<1][0]=a[i<<1|1][0]=cnt++;
	}
	for(int i=1;i<m;i+=2){
		for(int j=0;j<n;j++){
			if(k==0)break;
			k--;
			a[j][i]=a[j][i+1]=cnt++;
		}
	}
	for(int i=0;i<n;i+=2){
		for(int j=0;j<m;j++){
			if(a[i][j]==-1&&a[i+1][j]==-1){
				a[i][j]=a[i+1][j]=cnt++;
			}
		}
	}
	output();
}
void solve3(){
	if(k%2!=0){
		puts("NO");
		return;
	}
	for(int i=0;i<m;i+=2){
		for(int j=0;j<n;j++){
			if(k==0)break;
			k--;
			a[j][i]=a[j][i+1]=cnt++;
		}
	}
	for(int i=0;i<n;i+=2){
		for(int j=0;j<m;j++){
			if(a[i][j]==-1&&a[i+1][j]==-1){
				a[i][j]=a[i+1][j]=cnt++;
			}
		}
	}
	output();
}
void solve(){
	n=read();m=read();k=read();
	cnt=0;
	memset(a,-1,sizeof(a));
	if(n&1)solve1();
	else if(m&1)solve2();
	else solve3();
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/

```

---

## 作者：KSToki (赞：0)

# 题目大意
问 $n\times m$ 的棋盘是否能用恰好 $k$ 个水平的多米诺骨牌（大小为 $1\times2$）全部覆盖，保证 $n\times m$ 为偶数且 $k\le \frac{nm}{2}$。区别于 D1 的地方在于，如果能，请输出方案，要求共边的多米诺骨牌不能用同一字母表示。
# 题目分析
相信做到这里的人都切了 D1 吧，这里挂个[D1的题解链接](https://www.luogu.com.cn/blog/ypcaeh/solution-cf1551d1)，这里就主要讲输出方案。

每个多米诺骨牌一个字母肯定是不够用的，那么考虑构造。如果 $n$ 为偶数，$m$ 为偶数，我们用 ab 和 cd 两组字母间隔表示水平的两块，ef 和 gh 两组字母间隔表示竖直的两块。如果有多出来的一行或一列，我们用 ii 和 jj 间隔表示即可做到。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,k;
char ans[101][101];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		k=read();
		if(n%2==0&&m%2==0)
		{
			if(k%2==0)
			{
				puts("YES");
				int cnt=0,op=0;
				for(R int i=1;i<=n;i+=2)
				{
					for(R int j=1;j<=m;j+=2)
					{
						if(cnt<k/2)
						{
							op=(j/2)%2;
							ans[i][j]=ans[i][j+1]='a'+op*2;
							ans[i+1][j]=ans[i+1][j+1]='b'+op*2;
							++cnt;
						}
						else
						{
							op=(i/2)%2;
							ans[i][j]=ans[i+1][j]='e'+op*2;
							ans[i+1][j+1]=ans[i][j+1]='f'+op*2;
						}
					}
				}
				for(R int i=1;i<=n;++i)
				{
					for(R int j=1;j<=m;++j)
						printf("%c",ans[i][j]);
					puts("");
				}
			}
			else
				puts("NO");
		}
		else if(n%2==0&&m%2==1)
		{
			if(k<=m/2*n&&k%2==0)
			{
				puts("YES");
				for(R int i=1,op=0;i<=n;i+=2,op^=1)
					ans[i][1]=ans[i+1][1]='i'+op;
				int cnt=0,op=0;
				for(R int i=1;i<=n;i+=2)
				{
					for(R int j=2;j<=m;j+=2)
					{
						if(cnt<k/2)
						{
							op=(j/2)%2;
							ans[i][j]=ans[i][j+1]='a'+op*2;
							ans[i+1][j]=ans[i+1][j+1]='b'+op*2;
							++cnt;
						}
						else
						{
							op=(i/2)%2;
							ans[i][j]=ans[i+1][j]='e'+op*2;
							ans[i+1][j+1]=ans[i][j+1]='f'+op*2;
						}
					}
				}
				for(R int i=1;i<=n;++i)
				{
					for(R int j=1;j<=m;++j)
						printf("%c",ans[i][j]);
					puts("");
				}
			}
			else
				puts("NO");
		}
		else
		{
			if(k>=m/2&&(k-m/2)%2==0)
			{
				puts("YES");
				for(R int i=1,op=0;i<=m;i+=2,op^=1)
					ans[1][i]=ans[1][i+1]='i'+op;
				int cnt=m/2,op=0;
				for(R int i=2;i<=n;i+=2)
				{
					for(R int j=1;j<=m;j+=2)
					{
						if(cnt<k)
						{
							op=(j/2)%2;
							ans[i][j]=ans[i][j+1]='a'+op*2;
							ans[i+1][j]=ans[i+1][j+1]='b'+op*2;
							cnt+=2;
						}
						else
						{
							op=(i/2)%2;
							ans[i][j]=ans[i+1][j]='e'+op*2;
							ans[i+1][j+1]=ans[i][j+1]='f'+op*2;
						}
					}
				}
				for(R int i=1;i<=n;++i)
				{
					for(R int j=1;j<=m;++j)
						printf("%c",ans[i][j]);
					puts("");
				}
			}
			else
				puts("NO");
		}
	}
	return 0;
}

```


---

## 作者：staly (赞：0)

证明是否有方案的问题应该已经解决了，如果没有请移步 [这道题的 Easy Version](https://www.luogu.com.cn/problem/CF1551D1)。

我们现在已经知道：

1. 当 $n$, $m$ 皆为偶数时，如果 $k$ 是偶数，则有解。 
2. 当 $n$ 是奇数，$m$ 是偶数是，如果 $0\leq k-\frac{m}{2}\leq\frac{(n-1)m}{2}$ 且 $k-\frac{m}{2}$ 为偶数，则有解。
3. 当 $n$ 是偶数，$m$ 是奇数时，如果 $0\leq k \leq \frac{n(m-1)}{2}$ 且 $k$ 为偶数，则有解。

对于第一种情况，我们就直接把这张 $n\times m$的矩阵分成 $\frac{n}{2}\times\frac{m}{2}$ 的 $2\times 2$ 的子矩阵。按顺序枚举每一个子矩阵，当子矩阵的序号的两倍小于等于 $k$ 时，则记录两张横着的骨牌，反之则记录两张竖着的骨牌。

对于第二种情况，我们就把这个矩阵分成最后一列和剩余的部分，最后一列记录 $\frac{m}{2}$ 张横着的骨牌，剩余的部分等同于记录 $k-\frac{m}{2}$ 张骨牌时的第一种情况。

对于第三种情况，我们就把这个矩阵分成最后一行和剩余的部分，最后一列记录 $\frac{n}{2}$ 张竖着的骨牌，剩余的部分等同于记录 $k$ 张骨牌时的第一种情况。

所以代码如下：

```cpp
// User: xinchengo
// Fear cuts deeper than swords.

#include<iostream>
using namespace std;
int t;
int n, m, k;
char ans[107][107];
int main()
{
    cin >> t;
    while (t--)
    {
        int flag = 0;
        cin >> n >> m >> k;
        if (n % 2 == 0 && m % 2 == 0)
        { // n, m, 均为偶数，第一种情况
            if (k % 2 == 0)
            { // 如果 k 是偶数则有解
                flag = 1;
                int cnt = 0;
                for (int i = 1;i <= n / 2;i++)
                {
                    for (int j = 1;j <= m / 2;j++)
                    { // 依次记录 n/2 x m/2 张子矩阵
                        cnt++;
                        char c = (((i + j) % 2) ? 'a' : 'c');
                        if (cnt > k / 2)
                        { // 如果序号的两倍大于 k ，记录两张竖着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c;
                            ans[i * 2][j * 2] = c + 1;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                        else
                        { // 否则记录两张横着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c + 1;
                            ans[i * 2][j * 2] = c;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                    }
                }
            }
        }
        else if (n % 2 != 0 && m % 2 == 0)
        { // n（行数）为奇数的情况，第二种
            if ((k - m / 2) % 2 == 0 && k - m / 2 >= 0 && (n - 1) * m >= k - m / 2)
            { // 前面讲的的判断条件
                flag = 1;
                k = k - (m / 2);
                int cnt = 0;
                for (int i = 1;i <= n / 2;i++)
                {
                    for (int j = 1;j <= m / 2;j++)
                    { // 依次记录 n/2 x m/2 张子矩阵
                        cnt++;
                        char c = (((i + j) % 2) ? 'a' : 'c');
                        if (cnt > k / 2)
                        { // 如果序号的两倍大于 k ，记录两张竖着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c;
                            ans[i * 2][j * 2] = c + 1;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                        else
                        { // 否则记录两张横着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c + 1;
                            ans[i * 2][j * 2] = c;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                    }
                }
                for (int i = 1;i <= (m / 2);i++)
                { // 记录最后一行横着的骨牌
                    char c = (((i) % 2) ? 'e' : 'f');
                    ans[n][i * 2] = c;
                    ans[n][i * 2 - 1] = c;
                }
            }
        }
        else if (n % 2 == 0 && m % 2 != 0)
        { // m（列数）为奇数的情况，第三种
            if (k % 2 == 0 && n * (m - 1) / 2 >= k)
            { // 前面讲的的判断条件
                flag = 1;
                int cnt = 0;
                for (int i = 1;i <= n / 2;i++)
                {
                    for (int j = 1;j <= m / 2;j++)
                    { // 依次记录 n/2 x m/2 张子矩阵
                        cnt++;
                        char c = (((i + j) % 2) ? 'a' : 'c');
                        if (cnt > k / 2)
                        { // 如果序号的两倍大于 k ，记录两张竖着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c;
                            ans[i * 2][j * 2] = c + 1;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                        else
                        { // 否则记录两张横着的骨牌
                            ans[i * 2][j * 2 - 1] = c;
                            ans[i * 2 - 1][j * 2 - 1] = c + 1;
                            ans[i * 2][j * 2] = c;
                            ans[i * 2 - 1][j * 2] = c + 1;
                        }
                    }
                }
                for (int i = 1;i <= (n / 2);i++)
                { // 记录最后一列竖着的骨牌
                    char c = (((i) % 2) ? 'e' : 'f');
                    ans[i * 2][m] = c;
                    ans[i * 2 - 1][m] = c;
                }
            }
        }
        if (flag == 0) // 最后再输出
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
            for (int i = 1;i <= n;i++)
            {
                for (int j = 1;j <= m;j++)
                {
                    cout << ans[i][j];
                }
                cout << '\n';
            }
        }
    }
}
```


---

## 作者：白鲟 (赞：0)

## 前言
WA 了 3 发直接送命。

## 题目分析
解的有无与构造解事实上容易同时完成，不太懂为什么要分到两个题。

易得竖向的骨牌能且仅能填满任意行数为偶数的棋盘，横向的骨牌能且仅能填满任意列数为偶数的棋盘。

开始分类讨论。

若行列数均为偶数，要使得纵向的可以填满横向填后的格子，需要使得剩余的每个连通块在每一列均为偶数行。由于只需构造合法解，故不妨将每一列的剩余部分拼在一起，这样只需满足每一列剩余行数为偶数，而这要求横向在每一列占用行数均为偶数。于是将横向骨牌两两绑成 $2\times 2$ 的正方形从上至下、从左至右填，同时也得到了判断有解的条件为 $k$ 为偶数。

若行数为奇数，则类似地，需要横向在每一列占用行数为奇数。先铺满一行横向，则剩余问题转化为上一种情况。故有解条件为 $k$ 不小于行数且铺满一行后剩余为偶数。

若列数为奇数，与行数为奇数并无本质不同。将横纵互换、$k$ 取补后即转化为上一种情况。

关于解的输出，事实上可以每次填的时候枚举决定颜色。由于每两个格子相邻的已填格子数目很少，枚举只需进行常数次。

## 代码
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100;
int T,n,m,k;
char board[maxn+1][maxn+1];
bool conflict(int x,int y,char now)
{
	return board[x][y-1]==now||board[x][y+1]==now||board[x-1][y]==now||board[x+1][y]==now;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&k);
		if(n&1)
		{
			if(k>=m/2&&!((k-m/2)&1))
			{
				puts("YES");
				memset(board,0,sizeof board);
				k-=m/2;
				int now=0;
				for(int i=1;i<=m;i+=2,now=(now+1)%26)
					board[1][i]=board[1][i+1]=now+'a';
				for(int i=2,cnt=1;i<=n;i+=2)
					for(int j=1;j<=m;cnt+=2,j+=2,now=(now+2)%26)
						if(cnt<=k)
						{
							while(conflict(i,j+1,now+'a')||conflict(i,j,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i][j]=now+'a';
							while(conflict(i+1,j+1,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i+1][j+1]=board[i+1][j]=now+'a';
						}
						else
						{
							while(conflict(i,j,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i][j]=board[i+1][j]=now+'a';
							while(conflict(i,j+1,now+'a')||conflict(i+1,j+1,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i+1][j+1]=now+'a';
						}		
				for(int i=1;i<=n;++i)
					puts(board[i]+1);
			}
			else puts("NO");
		}
		else if(m&1)
		{
			if((n*m)/2-k>=n/2&&!((((n*m)/2-k)-n/2)&1))
			{
				puts("YES");
				memset(board,0,sizeof board);
				k=(n*m)/2-k-n/2;
				int now=0;
				for(int i=1;i<=n;i+=2,now=(now+1)%26)
					board[i][1]=board[i+1][1]=now+'a';
				for(int i=1,cnt=1;i<=n;i+=2)
					for(int j=2;j<=m;cnt+=2,j+=2,now=(now+2)%26)
						if(cnt>k)
						{
							while(conflict(i,j+1,now+'a')||conflict(i,j,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i][j]=now+'a';
							while(conflict(i+1,j+1,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i+1][j+1]=board[i+1][j]=now+'a';
						}
						else
						{
							while(conflict(i,j,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i][j]=board[i+1][j]=now+'a';
							while(conflict(i,j+1,now+'a')||conflict(i+1,j+1,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i+1][j+1]=now+'a';
						}	
				for(int i=1;i<=n;++i)
					puts(board[i]+1);
			}
			else puts("NO");
		}
		else
		{
			if(k&1)
				puts("NO");
			else
			{
				puts("YES");
				memset(board,0,sizeof board);
				int now=0;
				for(int i=1,cnt=1;i<=n;i+=2)
					for(int j=1;j<=m;cnt+=2,j+=2,now=(now+2)%26)
						if(cnt<=k)
						{
							while(conflict(i,j+1,now+'a')||conflict(i,j,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i][j]=now+'a';
							while(conflict(i+1,j+1,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i+1][j+1]=board[i+1][j]=now+'a';
						}
						else
						{
							while(conflict(i,j,now+'a')||conflict(i+1,j,now+'a'))
								now=(now+1)%26;
							board[i][j]=board[i+1][j]=now+'a';
							while(conflict(i,j+1,now+'a')||conflict(i+1,j+1,now+'a'))
								now=(now+1)%26;
							board[i][j+1]=board[i+1][j+1]=now+'a';
						}
				for(int i=1;i<=n;++i)
					puts(board[i]+1);
			}
		}
	}
	return 0;
}
```

---

