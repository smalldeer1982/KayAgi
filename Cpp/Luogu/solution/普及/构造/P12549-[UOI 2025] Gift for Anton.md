# [UOI 2025] Gift for Anton

## 题目描述

Anton 希望收到一份礼物：一个大小为 $n \times m$ 的矩形表格，表格中填有数字 0、1、2、3 或 4。

如果满足以下条件，Anton 就会感到开心：
- 每个 "0" 的旁边没有其他 "0"；
- 每个 "1" 的旁边恰好有一个其他 "1"；
- 每个 "2" 的旁边恰好有两个其他 "2"；
- 每个 "3" 的旁边恰好有三个其他 "3"；
- 每个 "4" 的旁边恰好有四个其他 "4"（即 "4" 的所有邻居也必须是 "4"）。

两个单元格如果共享一条边，则认为它们是相邻的。

你需要设计一个能让 Anton 开心的表格作为礼物。

下图是一个让 Anton 开心的表格示例（$n=4$，$m=6$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/gldglw1a.png)

## 说明/提示

### 评分标准

- （$10$ 分）：$n = 1$；
- （$10$ 分）：$n = 2$；
- （$10$ 分）：$n = 3$；
- （$10$ 分）：$n = m = 4$；
- （$10$ 分）：$n = m = 30$；
- （$5$ 分）：$n = 30$，$m = 31$；
- （$5$ 分）：$n = 30$，$m = 32$；
- （$10$ 分）：$n = m = 31$；
- （$5$ 分）：$n = 31$，$m = 32$；
- （$10$ 分）：$n = m = 32$；
- （$15$ 分）：无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 6```

### 输出

```
1 1 2 2 2 1
0 2 2 0 2 1
1 2 0 2 2 0
1 2 2 2 1 1```

# 题解

## 作者：ningyy (赞：4)

# **题目分析**
对于一个 $m\times n$ 的表格，用 $0,1,2,3,4$ 中的数字填满表格，且要满足数字 $x$ 的周围有 $x$ 个数和它相同。

---
# **解决**
首先不难想到 $4$ 不可能出现，否则整张表格都要是 $4$，但周围的 $4$ 无法有四个邻居。

然后 ~~观察~~ 分析可知，存在一种万能的单位表格，可以直接填满整张表格，这样这题就做完了。

接下来就是如何构造了，首先这种单位表格要可以相互拼接，所以拼接时对应的数不能相同，然后就不难想到可以先放 $4$ 个 $2$ 然后周围用 $0$ 和 $1$ 来补齐。

可以得到以下单位表格（可能会有别的单位表格，~~不过本蒟蒻想不到~~）。
|0|1|1|
|:-:|:-:|:-:|
|1|2|2|
|1|2|2|

然后就是如何填表了，根据 $m,n\bmod3$ 的结果进行分类，为 $1$ 或 $0$ 时从第一列开始，为 $2$ 时从第二列开始，这样就可以愉快的切掉这道~~蓝题~~（降绿了）了。

代码挺短的。

---
# **AC Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[210][210];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=201;i+=3)
		for(int j=1;j<=201;j+=3){
			a[i][j]=0;
			a[i+1][j]=a[i+2][j]=a[i][j+1]=a[i][j+2]=1;
			a[i+1][j+1]=a[i+2][j+1]=a[i+1][j+2]=a[i+2][j+2]=2;
		}
  //提前打出整张表格
	int stn,stm;
	if(n%3==2) stn=2;
	else stn=1;
	if(m%3==2) stm=2;
	else stm=1;
  //通过n和m模3的结果决定表格的开头
	for(int i=stn;i-stn+1<=n;i++){
		for(int j=stm;j-stm+1<=m;j++)
			cout<<a[i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}
```
完结撒花。

---

## 作者：Eden_star (赞：4)

## 思路
这道题说是可以用 $3$ $4$，但是这两个数却并不能使用。因为不能只使用这两个数字中的一种拼成一个合法的礼物。

所以尝试构造出一个合法的单位并且可以作为一个小单元的方格。不难找出这种情况。

[![pExhvrR.png](https://s21.ax1x.com/2025/05/21/pExhvrR.png)](https://imgse.com/i/pExhvrR)

当行列有不是 $3$ 的倍数时
- $N$ 取余三等于 $1$ 时以下图的格式进行插入\
[![pEx4fJO.png](https://s21.ax1x.com/2025/05/21/pEx4fJO.png)](https://imgse.com/i/pEx4fJO)
- $N$ 取余三等于 $2$ 时以下图的格式进行插入\
[![pEx4oyd.png](https://s21.ax1x.com/2025/05/21/pEx4oyd.png)](https://imgse.com/i/pEx4oyd)

$M$ 的情况就是把 $N$ 的情况竖过来。
## 代码
这道题的代码简直是又臭又长

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int n,m,xn,xm;
int dt[205];
int gz[5][5];
int main(){
	cin>>n>>m;
	gz[1][1]=gz[1][2]=gz[2][1]=gz[2][2]=2;
	gz[1][3]=gz[2][3]=gz[3][1]=gz[3][2]=1;
	gz[3][3]=0;
	if(n==1&&m==1){
		cout<<"0\n";
		return 0;
	}
	if(n<3){
		if(n==1){
			if(m%3==0){
				for(int i=1;i<=m;i++){
					cout<<gz[3][(i+3+m%3-1)%3+1]<<" ";
				}
			}
			if(m%3==1){
				for(int i=1;i<=m;i++){
					cout<<gz[3][(i+3+m%3)%3+1]<<" ";
				}
			}
			if(m%3==2){
				for(int i=1;i<=m;i++){
					cout<<gz[3][(i+3+m%3)%3+1]<<" ";
				}
			}
		}
		if(n==2){
			if(m%3==0){
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3-1)%3+1]<<" ";
				}
				cout<<"\n";
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3-1)%3+1]<<" ";
				}
			}
			if(m%3==1){
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3)%3+1]<<" ";
				}
				cout<<"\n";
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3)%3+1]<<" ";
				}
			}
			if(m%3==2){
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3)%3+1]<<" ";
				}
				cout<<"\n";
				for(int i=1;i<=m;i++){
					cout<<gz[1][(i+3+m%3)%3+1]<<" ";
				}
			}
		}
		return 0;
	}
	if(m<3){
		if(m==1){
			if(n%3==0){
				for(int i=1;i<=n;i++){
					cout<<gz[3][(i+3+n%3-1)%3+1]<<"\n";
				}
			}
			if(n%3==1){
				for(int i=1;i<=n;i++){
					cout<<gz[3][(i+3+n%3)%3+1]<<"\n";
				}
			}
			if(n%3==2){
				for(int i=1;i<=n;i++){
					cout<<gz[3][(i+3+n%3)%3+1]<<"\n";
				}
			}
		}
		if(m==2){
			if(n%3==0){
				for(int i=1;i<=n;i++){
					cout<<gz[1][(i+3+n%3+1)%3+1]<<" "<<gz[1][(i+3+n%3+1)%3+1]<<"\n";
				}
			}
			if(n%3==1){
				for(int i=1;i<=n;i++){
					cout<<gz[1][(i+3+n%3)%3+1]<<" "<<gz[1][(i+3+n%3)%3+1]<<"\n";
				}
			}
			if(n%3==2){
				for(int i=1;i<=n;i++){
					cout<<gz[1][(i+3+n%3)%3+1]<<" "<<gz[1][(i+3+n%3)%3+1]<<"\n";
				}
			}
		}
		return 0;
	}
	if(n%3==0){
		if(m%3==0){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
		}
		if(m%3==1){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m-1;j++){
					if(j==1) cout<<gz[3][(i-1)%3+1]<<" ";
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
		}
		if(m%3==2){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m-2;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
					if(j==m-2) cout<<gz[1][(i-1)%3+1]<<" "<<gz[1][(i-1)%3+1];
				}
				cout<<"\n";
			}
		}
	}
	if(n%3==1){
		if(m%3==0){
			for(int i=1;i<=m;i++){
				cout<<gz[3][(i-1)%3+1]<<" ";
			}cout<<"\n";
			for(int i=1;i<=n-1;i++){
				for(int j=1;j<=m;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
		}
		if(m%3==1){
			for(int i=1;i<=m-1;i++){
				if(i==1) cout<<gz[3][(i+1)%3+1]<<" ";
				cout<<gz[3][(i-1)%3+1]<<" ";
			}cout<<"\n";
			for(int i=1;i<=n-1;i++){
				for(int j=1;j<=m-1;j++){
					if(j==1) cout<<gz[3][(i-1)%3+1]<<" ";
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
		}
		if(m%3==2){
			for(int i=1;i<=m-2;i++){
				cout<<gz[3][(i-1)%3+1]<<" ";
				if(i==m-2) cout<<gz[1][(i-1)%3+1]<<" "<<gz[1][(i-1)%3+1];
			}cout<<"\n";
			for(int i=1;i<=n-1;i++){
				for(int j=1;j<=m-2;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
					if(j==m-2) cout<<gz[1][(i-1)%3+1]<<" "<<gz[1][(i-1)%3+1];
				}
				cout<<"\n";
			}
		}
	}
	if(n%3==2){
		if(m%3==0){
			for(int i=1;i<=n-2;i++){
				for(int j=1;j<=m;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
			for(int i=1;i<=m;i++){
				cout<<gz[1][(i-1)%3+1]<<" ";
			}cout<<"\n";
			for(int i=1;i<=m;i++){
				cout<<gz[2][(i-1)%3+1]<<" ";
			}cout<<"\n";
		}
		if(m%3==1){
			for(int i=1;i<=n-2;i++){
				for(int j=1;j<=m-1;j++){
					if(j==1) cout<<gz[3][(i-1)%3+1]<<" ";
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
				}
				cout<<"\n";
			}
			for(int i=1;i<=m-1;i++){
				if(i==1) cout<<gz[3][(i-1)%3+1]<<" ";
				cout<<gz[1][(i-1)%3+1]<<" ";
			}cout<<"\n";
			for(int i=1;i<=m-1;i++){
				if(i==1) cout<<gz[3][(i-1)%3+1]<<" ";
				cout<<gz[2][(i-1)%3+1]<<" ";
			}cout<<"\n";
		}
		if(m%3==2){
			for(int i=1;i<=n-2;i++){
				for(int j=1;j<=m-2;j++){
					cout<<gz[(i-1)%3+1][(j-1)%3+1]<<" ";
					if(j==m-2) cout<<gz[1][(i-1)%3+1]<<" "<<gz[1][(i-1)%3+1];
				}
				cout<<"\n";
			}
			for(int i=1;i<=m-2;i++){
				cout<<gz[1][(i-1)%3+1]<<" ";
				if(i==m-2) cout<<gz[1][(i+1)%3+1]<<" "<<gz[1][(i+1)%3+1];
			}cout<<"\n";
			for(int i=1;i<=m-2;i++){
				cout<<gz[2][(i-1)%3+1]<<" ";
				if(i==m-2) cout<<gz[1][(i+1)%3+1]<<" "<<gz[1][(i+1)%3+1];
			}cout<<"\n";
		}
	}
}
```

---

## 作者：未来姚班zyl (赞：4)

很水，直接按照下图构造即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/s3mgwk2l.png)

只需要 $2$ 不被拆开，根据 $n,m$ 对 $3$ 的余数讨论一下即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<29)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,a[205][205];
inline void out(){
  repn(i){
    repm(j)cout <<a[i][j]<<' ';
    cout <<"\n";
  }
  exit(0);
}
inline void Main(){
  n=read(),m=read();
  if(n==1){
    int nw=!(m%3==1||m%3==0);
    while(m){
      if(nw==0)cout <<"0 ",m--;
      else cout <<"1 1 ",m-=2;
      nw^=1;  
    } 
    return; 
  } 
  bool fn=(n%3<=1),fm=m%3<=1;
  repn(i){
    int A=fn?1:2,B=fm?1:2;
    repm(j){
      if(A==1&&B==1)a[i][j]=0;
      else if(A==2&&B==2)a[i][j]=a[i+1][j+1]=a[i][j+1]=a[i+1][j]=2;
      else if(A==2)a[i][j]=a[i+1][j]=1;
      else a[i][j]=a[i][j+1]=1;
      j+=B-1,B=3-B;
    }
    i+=A-1,fn^=1;
  }
  out();
}
signed main(){
  int T=1;
  while(T--)Main();
  return 0;
}
```

---

## 作者：sacc (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P12549)

## 题目分析

$3$ 和 $4$ 不能存在，直接考虑用 $0$，$1$，$2$ 进行构造。

## 解决方法

设此块为 $map(i,j)$ 有三种构造：

这一块填 $0$ 那么 $map(i,j)=0$。

这一块填 $1$ 那么 $map(i+1,j)=map(i+2,j)=map(i,j+1)=map(i,j+2)=1$。

这一块填 $2$ 那么 $map(i+1,j+1)=map(i+2,j+1)=map(i+1,j+2)=map(i+2,j+2)=2$。

但注意，$i$ 和 $j$ 每次加 $3$。

可以用预处理算法预处后输出即可。

## AC代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MOD 1000007
#define int long long
int n,m;
int mapp[335][335];
int ii,jj;
signed main()
{
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>m;
	//预处理。
	for(int i=0;i<=330;i+=3)
	{
		for(int j=0;j<=330;j+=3)
		{
			mapp[i][j]=0;
			mapp[i+1][j]=mapp[i+2][j]=mapp[i][j+1]=mapp[i][j+2]=1;
			mapp[i+1][j+1]=mapp[i+2][j+1]=mapp[i+1][j+2]=mapp[i+2][j+2]=2;
		}
	}
	//特殊情况。
	if(n%3==2)ii=1;
	if(m%3==2)jj=1;
	for(int i=ii;i<n+ii;i++)
	{
		for(int j=jj;j<m+jj;j++)
		{
			cout<<mapp[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Lamp_holder (赞：2)

## P112549

首先我们发现数字 $3$ 和 $4$ 是不可能被填进这个方框里的，因为在边界上我们无法处理他们的摆放方法，以及可以看出 $2$ 所形成的连通块一定是一个环。

然后我发现竟然给了部分数据。

那就不得不先打表找规律了。

- 对于 $n=1$ 的情况，我们容易想到把：

  ```
  1 1 0
  ```

  循环摆放即可。

- 对于 $n=2$ 的情况，我们手摸一下，得到可以将：

  ```
  2 2 1
  2 2 1
  ```

  循环摆放。

- 对于 $n=3$ 的情况，我们发现可以将 $1$ 和 $2$ 的做法组合一下，得到：

  ```
  1 1 0
  2 2 1
  2 2 1
  ```

  并将其循环摆放即可。

然后我们他扩展一下：

将对于 $n>3$ 的情况只需要将 $n=3$ 时的单位对于除3的余数分类讨论即可，一下举出 $n=4$ , $m=5$ 时的情况:
```
1 1 0 1 1
2 2 1 2 2 
2 2 1 2 2
1 1 0 2 2
```
~~这么好写就不贴代码了。~~

完结撒花❀。

---

## 作者：Vct14 (赞：1)

显然没有 $4$，否则所有数都为 $4$，边上的数不符合要求。显然边上没有 $3$，否则所有边上的数都为 $3$，角上的数不符合要求。

结合题目中的例子我们猜测只会用到 $0,1,2$ 这三个数。很容易构造出如下图的符合要求的小网格：

![](https://cdn.luogu.com.cn/upload/image_hosting/14t5rab4.png)

于是我们如此构造即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/zn5rvf8q.png)

需要注意的是小网格中的四个 $2$ 是不能拆开的。我们发现当且仅当 $n\bmod 3=2$ 时上下两行 $2$ 会被拆开，这时我们要删去第一行输出；当且仅当 $m\bmod 3=2$ 时左右两列 $2$ 会被拆开，这时我们要删去第一列输出。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=202;
int a[N][N];

int main(){
	int n,m;cin>>n>>m;
    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++){
            if(i%3>=1 && j%3>=1) a[i][j]=2;
            else if(!(i%3) && !(j%3)) a[i][j]=0;
            else a[i][j]=1;
        }
    }
    int ns=0,ms=0;
    if(n%3==2) ns=1;
    if(m%3==2) ms=1;
    for(int i=ns; i<=ns+n-1; i++,cout<<"\n") for(int j=ms; j<=ms+m-1; j++) cout<<a[i][j]<<" ";
	return 0;
}
/*
(0 1 1 0)
(1)2 2 1
(1)2 2 1
(0)1 1 0
*/
```

---

## 作者：StarTwinkleTwinkle (赞：1)

容易得到 $3$ 和 $4$ 不能存在，直接考虑用 $0$，$1$，$2$ 进行构造。

对于 $3\times 3$ 的，我们有如下构造方式：

```
0 1 1
1 2 2
1 2 2
```

我们发现这种构造方式延展性较强，故直接进行扩展即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=500;i+=3){
		for(int j=0;j<=500;j+=3){
			a[i][j]=0;
			a[i+1][j]=a[i+2][j]=a[i][j+1]=a[i][j+2]=1;
			a[i+1][j+1]=a[i+2][j+1]=a[i+1][j+2]=a[i+2][j+2]=2;
		}
	}
	int fri=0,frj=0;
	if(n%3==2)fri=1;
	if(m%3==2)frj=1;
	for(int i=fri;i<n+fri;++i){
		for(int j=frj;j<m+frj;++j){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：LG086 (赞：1)

我们仔细手玩一下，不难发现 $3$ 和 $4$ 是不能用的，所以只剩下 $0$，$1$，$2$ 了。那么慢慢构造答案吧。


---


我们尝试构造 $n=1$ 的情况，发现有如下表格：

$$\text{011011011}\dots$$

这是由 $\text{011}$ 循环排列组成的。进一步分析，发现 $m \bmod 3 = 2$ 时，我们需要用 $\text{110}$ 来循环排列。



---



构造 $n=2$ 的情况，发现有如下表格：

$$\text{122122122}\dots\\\text{122122122}\dots$$

发现这是由如下表格循环排成的。

$$\text{122}\\\text{122}$$

我们再看看，发现 $m \bmod 3 = 2$ 时，我们需要用如下表格来循环排列。

$$\text{221}\\\text{221}$$


---


当 $n \ge 3$ 时，我们又可以构造出这个表格：

$$\text{011011011}\dots\\\text{122122122}\dots\\\text{122122122}\dots\\\text{011011011}\dots\\\text{122122122}\dots\\\text{122122122}\dots$$

这是由一个 $3\times 3$ 的如下表格循环排列构成的。

$$\text{011}\\\text{122}\\\text{122}$$

同时发现如果 $m \bmod 3 = 2$，表格需要变化为下图形式。

$$\text{110}\\\text{221}\\\text{221}$$


这就完了吗？如果 $n=5,m=5$，应当输出：

$$
\text{22122}\\
\text{22122}\\
\text{11011}\\
\text{22122}\\
\text{22122}\\
$$

所以当 $n \bmod 3 = 2$ 时，表格也需要变化，变化如下：

$$
\text{122}\\\text{122}\\\text{011}
$$

而且当 $n \bmod 3 =2$ 并且 $m \bmod 3 = 2$ 时，表格就变成了：

$$\text{221}\\\text{221}\\\text{110}$$



---

综上，实际只需要一个表格循环即可。  
即循环排列：

$$\text{011}\\\text{122}\\\text{122}$$

同时判断 $n \bmod 3$ 和 $m \bmod 3$ 的值进行改变即可。  
代码略。

---

## 作者：Scean_Tong (赞：1)

## P12549 [UOI 2025] Gift for Anton

好玩诈骗构造，抢个首发题解。

虽然但是，是蓝我吃。

### Problem

构造一个 $n \times m$ 的矩阵，使得矩阵中 $0$ 旁边没有 $1$，$1$ 旁边有 $1$ 个 $1$，$2$ 旁边有 $2$ 个 $2$，$3$ 旁边有 $3$ 个 $3$，$4$ 旁边有 $4$ 个 $4$。

### Solution

诈骗题。

我在纸上画了好久得出一个结论：不存在一个局部图形可以使得 $3$ 旁边有 $3$ 个 $3$，$4$ 旁边有 $4$ 个 $4$。

这个也比较好想，因为这个你画着画着就会发现它一直会多出来一块不符合条件的。

所以题意转化为：构造一个 $n \times m$ 的矩阵，使得矩阵中 $0$ 旁边没有 $1$，$1$ 旁边有 $1$ 个 $1$，$2$ 旁边有 $2$ 个 $2$。

这个就比较好做了，先考虑构造一个可以拼起来且符合条件的，不难想到下面这种。

![](https://cdn.luogu.com.cn/upload/image_hosting/1uv6cxqv.png)

原谅一下我不太会使用公式表示这个矩阵，直接用图片了。

画出这个东西之后，把它自己拼到它的上下左右都是合法的，所以 $n,m$ 均为 $3$ 的倍数的时候就做完了，我们称拼到现在为止的东西为**标准矩阵**。

考虑推广正解，我直接考虑大力分讨 $n,m$ 除以 $3$ 的余数，为方便讲解，接下来令 $a$ 表示 $n$ 除以 $3$ 的余数，$b$ 表示 $m$ 除以 $3$ 的余数。

- 当 $a=1,b=0$ 时，在标准矩阵下面横着放若干个 `1 1 0` 即可。

- 当 $a=2,b=0$ 时，在标准矩阵上面横着放若干个两行的 `2 2 1` 即可。

- 当 $a=0,b=1$ 时，在标准矩阵左面竖着放若干个 `0 1 1` 即可。

- 当 $a=0,b=2$ 时，在标准矩阵右面竖着放若干个两列的 `1 2 2` 即可。

还有几种情况，但是你会发现就是把上面四种中的两种揉到一起就行了。

然后这题就做完了，代码巨大但是很好写，都是差不多的东西，而且很好调。


```cpp
#include <bits/stdc++.h>
int n, m;
constexpr int maxn = 210;
std::deque<int> ans[maxn];
int main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	for(int i = 3; i <= 2 + (n / 3) * 3; i++){
		if(i % 3 == 0){
			for(int j = 1; j <= (m / 3); j++){
				ans[i].push_back(1);
				ans[i].push_back(1);
				ans[i].push_back(0);	
			}
		}
		if(i % 3 == 1){
			for(int j = 1; j <= (m / 3); j++){
				ans[i].push_back(2);
				ans[i].push_back(2);
				ans[i].push_back(1);	
			}
		}
		if(i % 3 == 2){
			for(int j = 1; j <= (m / 3); j++){
				ans[i].push_back(2);
				ans[i].push_back(2);
				ans[i].push_back(1);	
			}
		}
	}
	if(n % 3 == 1 && m % 3 == 0){
		for(int i = 1; i <= (m / 3); i++){
			ans[n + 3].push_back(1);
			ans[n + 3].push_back(1);
			ans[n + 3].push_back(0);
		}
	}
	if(n % 3 == 2 && m % 3 == 0){
		for(int i = 1; i <= (m / 3); i++){
			ans[1].push_back(2);
			ans[1].push_back(2);
			ans[1].push_back(1);
			ans[2].push_back(2);
			ans[2].push_back(2);
			ans[2].push_back(1);
		}
	}
	if(n % 3 == 0 && m % 3 == 1){
		for(int i = 3; i <= n + 2; i++){
			if(i % 3 == 0){
				ans[i].push_front(0);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_front(1);
			}
		}
	} 
	if(n % 3 == 1 && m % 3 == 1){
		for(int i = 3; i <= n + 2; i++){
			if(i % 3 == 0){
				ans[i].push_front(0);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_front(1);
			}
		}
		for(int i = 1; i <= (m / 3); i++){
			ans[n + 2].push_back(1);
			ans[n + 2].push_back(1);
			ans[n + 2].push_back(0);
		}
	}
	if(n % 3 == 2 && m % 3 == 1){
		for(int i = 1; i <= (m / 3); i++){
			ans[1].push_back(2);
			ans[1].push_back(2);
			ans[1].push_back(1);
			ans[2].push_back(2);
			ans[2].push_back(2);
			ans[2].push_back(1);
		}
		for(int i = 1; i <= n; i++){
			if(i % 3 == 0){
				ans[i].push_front(0);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_front(1);
			}
		}
	}
	if(n % 3 == 0 && m % 3 == 2){
		for(int i = 3; i <= n + 2; i++){
			if(i % 3 == 0){
				ans[i].push_back(1);
				ans[i].push_back(1);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_back(2);
				ans[i].push_back(2);
			}
		}
	}
	if(n % 3 == 1 && m % 3 == 2){
		for(int i = 1; i <= (m / 3); i++){
			ans[n + 2].push_back(1);
			ans[n + 2].push_back(1);
			ans[n + 2].push_back(0);
		}
		for(int i = 3; i <= n + 2; i++){
			if(i % 3 == 0){
				ans[i].push_back(1);
				ans[i].push_back(1);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_back(2);
				ans[i].push_back(2);
			}
		}
	}
	if(n % 3 == 2 && m % 3 == 2){
		for(int i = 1; i <= (m / 3); i++){
			ans[1].push_back(2);
			ans[1].push_back(2);
			ans[1].push_back(1);
			ans[2].push_back(2);
			ans[2].push_back(2);
			ans[2].push_back(1);
		}
		for(int i = 1; i <= n; i++){
			if(i % 3 == 0){
				ans[i].push_back(1);
				ans[i].push_back(1);
			}
			if(i % 3 == 1 || i % 3 == 2){
				ans[i].push_back(2);
				ans[i].push_back(2);
			}
		}
	}
	for(int i = 1; i <= n + 3; i++){
		if(ans[i].size()){
			for(int x : ans[i]){
				std::cout << x << ' ';
			}
			std::cout << '\n';
		}
	} 
	
	return 0; 
}
```

---

