# Parquet

## 题目描述

给定一规模为 $n \times m$ 的矩阵，假定你有 $1 \times 2$ 的木板 $a$ 块，$2 \times 1$ 的木板 $b$ 块，$2 \times 2$ 的木板 $c$ 块，试问你能不能用这些木板铺满整个矩阵。

注意:木板不能旋转，不能重叠，不一定要用完。

## 说明/提示

$1 \leq n,m \leq 100$，$0 \leq a,b,c \leq 10^4$。

## 样例 #1

### 输入

```
2 6 2 2 1
```

### 输出

```
aabcca
aabdda
```

## 样例 #2

### 输入

```
1 1 100 100 100
```

### 输出

```
IMPOSSIBLE
```

## 样例 #3

### 输入

```
4 4 10 10 10
```

### 输出

```
aabb
aabb
bbaa
bbaa
```

# 题解

## 作者：SeeseaWY (赞：19)

一道显然的构造题。
### 思路
首先考虑进行特判，若 $n\times m$ 是奇数，则不可能铺成功，这是显然的。

若 $a,b,c$ 面积总和小于 $n\times m$，也不可能铺成功。
``` cpp
if(((n*m)&1)||(a<<1)+(b<<1)+(c<<2)<n*m){
	cout<<"IMPOSSIBLE";
	return 0;
}
```
若 $n$ 是奇数，即只有奇数行，则先用 $1\times2$ 的 $a$ 瓷砖把最后一行铺满，因为 $b,c$ 高度均为 $2$。换成 $m$ 同理。
``` cpp
if(n&1){
	if((m>>1)>a){//铺不满就特判
		cout<<"IMPOSSIBLE";
		return 0;
	}
	a-=m/2;
	for(int i=1;i<=m;i+=2)
		e[n][i]=e[n][i+1]=(i%4==1)?'y':'z';//铺掉
	n--;
}
if(m&1){//同理
	if(n/2>b){
		cout<<"IMPOSSIBLE";
		return 0;
	}
	b-=n/2;
	for(int i=1;i<=n;i+=2)
		e[i][m]=e[i+1][m]=(i%4==1)?'y':'z';
	m--;
}
```
接下来暴力模拟即可。

#### 有个贪心小技巧，先铺大的，再铺小的。

代码如下：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,flag;
char e[105][105];
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>m>>a>>b>>c;
	int nn=n,mm=m;
	if(((n*m)&1)||(a<<1)+(b<<1)+(c<<2)<n*m){
		cout<<"IMPOSSIBLE";
		return 0;
	}
	if(n&1){
		if((m>>1)>a){
			cout<<"IMPOSSIBLE";
			return 0;
		}
		a-=m/2;
		for(int i=1;i<=m;i+=2)
			e[n][i]=e[n][i+1]=(i%4==1)?'y':'z';
		n--;
	}
	if(m&1){
		if(n/2>b){
			cout<<"IMPOSSIBLE";
			return 0;
		}
		b-=n/2;
		for(int i=1;i<=n;i+=2)
			e[i][m]=e[i+1][m]=(i%4==1)?'y':'z';
		m--;
	}
	for(int i=1;i<=n;i+=2)
		for(int j=1;j<=m;j+=2){
			int z=(i%4/2+j%4/2)%2*2;
			if(c>=1){//先铺大的
				e[i][j]=e[i+1][j]=e[i][j+1]=e[i+1][j+1]=z+'b';
				c--;
			}
			else if(a>=2){
				e[i][j]=e[i][j+1]=z+'h';
				e[i+1][j]=e[i+1][j+1]=z+'i';
				a-=2;
			}
			else if(b>=2){
				e[i][j]=e[i+1][j]=z+'o';
				e[i][j+1]=e[i+1][j+1]=z+'p';
				b-=2;
			}
			else{
	    		cout<<"IMPOSSIBLE";
				return 0;
			}
		}
	for(int i=1;i<=nn;++i)
	{
		for(int j=1;j<=mm;++j)
			cout<<e[i][j];
		cout<<"\n";
	}
}
```
~~求赞！~~

---

## 作者：Tiankun2010 (赞：7)

# 题意
构造题，用 $a$ 块 $1\times 2$，$b$ 块 $2\times 1$，$c$ 块 $2\times 2$ 的木板**铺满** $n\times m$ 的矩阵,木板**不重叠**，**不翻转**。

若无法铺满，输出 `IMPOSSIBLE` 。
# 思路
- 判边界

显然，当 $n\times m$ 是奇数时，或所有木板都用上也铺不满时，无解。

```cpp
if( (n*m)%1==1 || (n*m)<(a*2+b*2+c*4) ){
    cout<<"IMPOSSIBLE";
    return 0;
}
```
在构造时，若发现木板不够用了，也无解。
- 构造矩阵

当 $n$ 为奇数时，只能用 $1\times 2$ 的木板将一行铺满（为了方便选取最后一行），$m$ 同理。

最后就是 $n$ 和 $m$ 都是偶数的情况了。

我们可以将它分成 $2\times 2$ 的小矩阵，每个小矩阵用 $2$ 块 $1\times 2$ 的,$2$ 块 $2\times 1$ 的或 $1$ 块 $2\times 2$ 的填充。

还有一个问题，要保证同一块木板用同种字母表示，相邻的木板不能都用同一种字母。

这里给出一种比较方便的方式分配字母。

先对所有 $2\times 2$ 的小矩阵进行分类：

![](https://cdn.luogu.com.cn/upload/image_hosting/qhv9m4ki.png)

对于同类的木板组（铺 $2\times 2$ 的小矩阵的木板为一组），只需要保证在 A，B 中用不同字母即可。

对于异类的木板组，直接让它们用不同的字母即可。

比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/6i7n0wm9.png)

注意，当 $n$，$m$ 为奇数时,最后一行（列）的填充可以再换一个字母。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace AC{
    const int maxn=105,maxm=105;
    char ans[maxn][maxm];
    int main(){
        int bj_n=0,bj_m=0;
        int n,m,a,b,c;
        scanf("%d%d%d%d%d",&n,&m,&a,&b,&c);
        if( (n*m)%2==1 || (n*m)>(a*2+b*2+c*4) ){
            cout<<"IMPOSSIBLE";
            return 0;
        }//判边界
        if(n&1){
            if(m/2>a){//不够
                cout<<"IMPOSSIBLE";
                return 0;
            }
            a-=m/2;
            bool bj=0;
            for(int i=1;i<=m;i+=2){
                ans[n][i]=ans[n][i+1]=(bj==1?'k':'l');
                bj^=1;
            }
            n--;
            bj_n=1;
        }else if(m&1){
            if(n/2>b){//不够
                cout<<"IMPOSSIBLE";
                return 0;
            }
            b-=n/2;
            bool bj=0;
            for(int i=1;i<=n;i+=2){
                ans[i][m]=ans[i+1][m]=(bj==1?'k':'l');
                bj^=1;
            }
            m--;
            bj_m=1;
        }//特判n,m是奇数的情况
        for(int i=1;i<=n;i+=2)
            for(int j=1;j<=m;j+=2){//枚举每个小矩阵
                bool bj=((i+j)%4==0);//bj=0:A,bj=1:B
                if(c>=1){//铺2*2的
                    c--;
                    ans[i][j]=ans[i+1][j]=ans[i][j+1]=ans[i+1][j+1]=(bj==0?'a':'b');
                }else if(a>=2){//铺1*2的
                    a-=2;
                    ans[i][j]=ans[i][j+1]=(bj==0?'c':'e');
                    ans[i+1][j]=ans[i+1][j+1]=(bj==0?'d':'f');
                }else if(b>=2){//铺2*1的
                    b-=2;
                    ans[i][j]=ans[i+1][j]=(bj==0?'g':'i');
                    ans[i][j+1]=ans[i+1][j+1]=(bj==0?'h':'j');
                }else{//中途发现木板不够用了
                    cout<<"IMPOSSIBLE";
                    return 0;
                }
            }
        for(int i=1;i<=n+bj_n;i++){
            for(int j=1;j<=m+bj_m;j++)
                cout<<ans[i][j];
            cout<<'\n';
        }
        return 0;
    }
}
int main(){return AC::main();}
```


---

## 作者：yeshubo_qwq (赞：4)

## 题意
用 $a$ 块 $1\times2$，$b$ 块 $2\times1$，$c$ 块 $2\times2$ 的木板填充满 $n\times m$ 的矩阵，**木板不能旋转，不能重叠，不一定要用完**，输出任意一种方案，如不能填充满矩阵，输出 `IMPOSSIBLE`。
## 思路
木板总面积小于矩阵面积显然无解。

因为填充的木板面积之和为偶数，所以当矩阵面积为奇数无解。

先特判这两种无解情况。

然后填充：

如果 $n$ 为奇数，我们考虑用 $1\times2$ 的木板单独填满最后一行。

同理，如果 $m$ 为奇数，我们考虑用 $2\times1$ 的木板单独填满最后一列。

然后就变成了 $n$ 和 $m$ 为偶数的情况了。

我们把它当成 $n\times m\div4$ 个 $2\times2$ 的小矩阵。

对于每个小矩阵，我们用 $2$ 块 $1\times2$ 或 $2$ 块 $2\times1$ 或 $1$ 块 $2\times2$ 的木板来填充。

注意：在填充过程中如果木板不够用同样无解。

我在填字母时，参考了 @LilliaAsupurei dalao 的方法：**在边界上用很大的字母，然后在内部按 $2\times2$ 的小矩阵的奇偶进行计算。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,r,r2,i,j,flag;
char ans[105][105];
int main(){
	cin>>n>>m>>a>>b>>c;
	r=n;r2=m;
	if(n*m%2==1||(a+b+c*2)*2<n*m){//特判无解 
		printf("IMPOSSIBLE");
		return 0;
	}
	if(n%2==1){//单独填满最后一行 
		if(m/2>a){
			printf("IMPOSSIBLE");//木板不够用无解 
			return 0;
		}
		a=a-m/2;
		flag=0;
		for(i=1;i<=m;i+=2)
			ans[n][i]=ans[n][i+1]=char(flag+'y'),flag=1-flag;
		n--;
	}
	if(m%2==1){//单独填满最后一列
		if(n/2>b){
			printf("IMPOSSIBLE");
			return 0;
		}
		b=b-n/2;
		flag=0;
		for(i=1;i<=n;i+=2)
			ans[i][m]=ans[i+1][m]=char(flag+'y'),flag=1-flag;
		m--;
	}
	for(i=1;i<=n;i+=2)
		for(j=1;j<=m;j+=2){
			flag=(i%4/2+j%4/2)%2*2;//按奇偶进行计算
			if(c>=1){
				ans[i][j]=ans[i+1][j]=ans[i][j+1]=ans[i+1][j+1]=flag+'a'+1;
				c-=1;
			}//其实a,b,c的顺序都随便啦~
			else if(a>=2){
				ans[i][j]=ans[i][j+1]=flag+'a'+5;
				ans[i+1][j]=ans[i+1][j+1]=flag+'a'+6;
				a-=2;
			}
			else if(b>=2){
				ans[i][j]=ans[i+1][j]=flag+'a'+10;
				ans[i][j+1]=ans[i+1][j+1]=flag+'a'+11;
				b-=2;
			}
			else{
	    		printf("IMPOSSIBLE");//木板不够用无解 
				return 0;
			}
		}
	for(i=1;i<=r;i++){
		for(j=1;j<=r2;j++)
			putchar(ans[i][j]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：jianhe (赞：3)

### 前言：
12.21 的每日一题。

### 思路：
首先注意到木板是 $1 \times 2$，$2 \times 1$ 或 $2 \times 2$ 的，只能拼出面积为偶数的矩阵，所以如果 $n \times m$ 是奇数就无解。

当然如果总共能拼出的面积小于矩阵面积也无解。

于是剩下一奇一偶的情况和两个偶数的情况。

如果 $n$ 是奇数，那么先摆一行 $1 \times 2$ 的方块。这样 $n$ 就转化为了偶数。因为 $n \times m$ 是偶数，所以 $m$ 是偶数，所以肯定能放下。

如果 $m$ 是奇数同理。

如果都是偶数，用贪心来做。因为在没有块数限制的时候怎么填都可以，所以优先填 $2 \times 2$ 的，再填其他的。

关于颜色，这里采取了一种不用动脑子的做法：暴力枚举周围的颜色，找到一个四周没用过的颜色填进去即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define no {cout<<"IMPOSSIBLE\n";return 0;}
const ll N=110;
ll n,m,a,b,c,nt,mt,dx[]={-1,0,0,1},dy[]={0,-1,1,0};
char s[N][N];bool co[28];
void ran(ll x,ll y){
    for(int k=0;k<4;k++){
        ll px=x+dx[k],py=y+dy[k];
        if(0<px&&px<=n&&0<py&&py<=m&&s[px][py]>='a'&&s[px][py]<='z') co[s[px][py]-'a']=1;// 标记旁边用过的颜色
    }
}
char get(ll x1,ll y1,ll x2,ll y2,ll x3=-1,ll y3=-1,ll x4=-1,ll y4=-1){// 找可以涂的颜色
    memset(co,0,sizeof co);
    ran(x1,y1),ran(x2,y2),ran(x3,y3),ran(x4,y4);
    for(int k=0;k<26;k++)
        if(!co[k]) return 'a'+k;
}
void col(ll i,ll j,ll tp){// 染色
    if(!tp) s[i][j]=s[i][j+1]=get(i,j,i,j+1);
    else if(tp==1) s[i][j]=s[i+1][j]=get(i,j,i+1,j);
    else s[i][j]=s[i][j+1]=s[i+1][j]=s[i+1][j+1]=get(i,j,i,j+1,i+1,j,i+1,j+1);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m>>a>>b>>c;nt=n,mt=m;
    if(((n*m)&1)||a*2+b*2+c*4<n*m) no;
    if(n&1){// n 是奇数：先排一行
        if(a<m/2) no;a-=m/2,nt--;
        for(int j=1;j<=m;j+=2) col(n,j,0);
    }
    if(m&1){// m 是奇数：先排一列
        if(b<n/2) no;b-=n/2,mt--;
        for(int i=1;i<=n;i+=2) col(i,m,1);
    }
    for(int i=1;i<=nt;i+=2)
        for(int j=1;j<=mt;j+=2)
            if(c>0) col(i,j,2),c--;// 优先使用 2*2
            else if(a>1) col(i,j,0),col(i+1,j,0),a-=2;
            else if(b>1) col(i,j,1),col(i,j+1,1),b-=2;
            else no;// 不够了
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cout<<s[i][j]<<(j==m?"\n":"");
    return 0;
}
```

---

## 作者：AsunderSquall (赞：2)

~~hoho！恭喜你发现一道CF*2000的水黑~~  
# 题意  
问你能不能用$a$个$1\times2$，$b$个$2\times 1$，$c$个$2\times2$的模板覆盖$n\times m$的矩形  
不能旋转，不能重叠，不能重复使用  

# 题解

首先显然$n\times m\%2==1$的情况直接无解  
```cpp
#define END {cout<<"IMPOSSIBLE"<<endl;return 0;}

if (n*m%2==1) END
```

为了方便，称$1 \times 2$的木板为$A$，$2 \times 1$的木板为$B$，$2 \times 2$的木板为$C$。   

--------
首先考虑n和m全是偶数的情况  
我们以$2\times 2$为一个单位进行覆盖，最多可以覆盖$\dfrac{a}{2}+\dfrac{b}{2}+c$个$2\times2$，分数全部向下取整  

可以证明这是最优策略    
考虑将矩形进行每列的黑白间隔染色，那么如果有多出来的奇数A，会使黑色格子和白色格子数量不一样。同理B，将每行黑白间隔染色即可。

然后考虑只有一个是奇数的情况  
以$n \%2==1$ 为例  
还是对每列进行黑白间隔染色，这次黑色格子比白色格子多了$m$个  
先用$\dfrac{m}{2}$个A覆盖掉最后一列，从而先使黑色格子和白色格子数量相同  
然后如果$a-[\dfrac{m}{2}]$依然为奇数，那多出来的依然会使黑色格子和白色格子数目不一样。  

所以接下来就按$n,m$都是偶数的情况处理即可，这是最优策略  

$m \%2==1$同理  

注意考虑一下相邻的不同木块要用不同的字母表示。我这里在边界上用了很大的字母，然后在偶数乘偶数内部按$2\times 2$块的奇偶进行计算。  

完整代码：  
```cpp
#include<bits/stdc++.h>
#define int long long 
#define rd(x) x=read()
#define END {cout<<"IMPOSSIBLE"<<endl;return 0;}
using namespace std;
const int N=305;
const int M=1e6+5;
const int maxn=5e6+5;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y,int z){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
inline int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
inline int INV(int x){return ksm(x,mod-2);}

int A[N][N];
int n,m;
int a,b,c;
signed main()
{
    rd(n);rd(m);
    rd(a);rd(b);rd(c);
    if (n*m%2==1) END
    if (n%2==1)
    {
        //把最后一行填满
        if (a<m/2) END
        for (register int i=1;i<=m;i+=2)
        {
            A[n][i]=A[n][i+1]=(i%4)/2+25;
            a--;
        }
    }
    if (m%2==1)
    {
        if (b<n/2) END
        for (register int i=1;i<=n;i+=2)
        {
            A[i][m]=A[i+1][m]=(i%4)/2+25;
            b--;
        }
    }
    int nn=n;int mm=m;
    n-=(n%2);m-=(m%2);
    if (a/2+b/2+c<n*m/4) END
    for (register int i=1;i<=n;i+=2)
        for (register int j=1;j<=m;j+=2)
        {
            int oe=((i%4/2)+(j%4/2))%2;
            oe*=2;
            if (a>1) 
            {
                A[i][j]=A[i][j+1]=oe+1;
                A[i+1][j]=A[i+1][j+1]=oe+2;
                a-=2;
            }else if (b>1)
            {
                A[i][j]=A[i+1][j]=oe+6;
                A[i][j+1]=A[i+1][j+1]=oe+7;
                b-=2;
            } else
            {
                A[i][j]=A[i+1][j]=A[i][j+1]=A[i+1][j+1]=oe+10;
                c--;
            }
            
            
        }
    if (a<0 || b<0 || c<0) END
    for (register int i=1;i<=nn;i++)
    {
        for (register int j=1;j<=mm;j++)
        {
            putchar(A[i][j]+'a'-1);
        }
        putchar('\n');
    }
}
```
完整代码：


---

## 作者：BigJoker (赞：0)

先判断一下无解的情况。

当面积全部拼凑起来也不足 $n\times m$ 时是不可行的，显然。

当 $n\times m$ 为奇数时也是不行的，因为木板都是偶数大小，肯定不能拼凑出奇数。

如果 $n,m$ 中的有一个为奇数，我们可以用 $1\times 2$ 或者 $2\times 1$ 的木板将那一行或者那一列全部填起来，这时候如果不够也不行。

经过上述操作，我们就可以得到一个 $n,m$ 都为偶数的矩阵。

直接暴力放上去就可以了。

先放 $2\times 2$ 最后再放 $1\times 2$ 和 $2\times 1$ 的木板。

当然提醒一下：同种木板要注意区分。

---

## 作者：zilingheimei (赞：0)

~~水黑 水黑！！！~~

[CF26C Parquet](https://www.luogu.com.cn/problem/CF26C)

这题就是纯模拟。

------------


### 题意

给你 $5$ 个数 $n$ ， $m$ ， $a$ ， $b$ ， $c$ ，分别代表有一个 $n \times m$ 的矩形，有 $a$ 块 $1 \times 2$ ， $b$ 块 $2 \times1 $ ， $c$ 块 $2 \times 2$ 的木块，问是否存在着用其中一些成功填充的方案，同时相邻的图形要用不同字母表示。


------------


### 思路

- 1. 很明显，当这几个木块的面积和小于矩形面积时无解。
  2. 同时，这些木块的面积中都含有因数 $2$ ，所以当面积为奇数时无解。
  
```cpp
if(n*m&1||a*2+b*2+c*4<n*m){//无解
     cout<<"IMPOSSIBLE";
     return 0;
}
```
- 对于 $n$ 与 $m$ ，可能会有并不是偶数的情况，所以当 $2|n$ 或 $2|m$ 时，可以用 $1 \times 2$ 或 $2 \times 1$ 的木板来填充。（为了方便，下面用 $2|n$ 来讲）

  当然，为了保证下面的整齐，所以要一次填满，用掉     $\frac{m}{2}$ 个 $1 \times 2$ 的木板来填，这里我们为了后面方便可以用较大的字母来表示。
  
  而如果所需要的木板不够，那么便无解，因为没有其他木板可以帮助填充最后一行（列）。
```cpp
if(n&1){//当n被2整除
	if(m/2>a){//1*2不够了
		cout<<"IMPOSSIBLE";
		return 0;
	}
	a-=m/2;
	pos=0;
	for(int i=1;i<=m;i+=2){
		ans[n][i]=ans[n][i+1]=pos+'y';
		pos^=1;
	}//填充
	n--;//去行
}
if(m&1){//当m被2整除
	if(n/2>b){//2*1不够了
		cout<<"IMPOSSIBLE";
		return 0;
	}
	pos=0;
	b-=n/2;
	for(int i=1;i<=n;i+=2){
		ans[i][m]=ans[i+1][m]=pos+'y';
		pos^=1;
	}//填充
	m--;//去列
}
```


- 填完这些了之后就是对一个偶数矩形填充了，我们可以发现，这个偶数矩形可以分为多个 $2 \times 2$ 组成，那么我们只需要凑 $2 \times 2$ 即可。

	这里我们可以利用行列的奇偶性来填充，同时将木块之间的差值变大以防溢出错误。
   
   同时，我们可以发现，当组成不了 $2 \times 2$ 时便无解了。
    
    
 ```cpp
for(int i=1;i<=n;i+=2){
	for(int j=1;j<=m;j+=2){
		pos=(i%4/2+j%4/2)%2;
		if(c>=1){
			ans[i][j]=ans[i][j+1]=ans[i+1][j]=ans[i+1][j+1]=pos+'a'+2;
			c--;
		}//用的2*2
		else if(a>=2){
			ans[i][j]=ans[i][j+1]=pos+'a'+4;
			ans[i+1][j]=ans[i+1][j+1]=pos+'a'+5;
			a-=2;
		}//用掉2个1*2
		else if(b>=2){
			ans[i][j]=ans[i+1][j]=pos+'a'+7;
			ans[i][j+1]=ans[i+1][j+1]=pos+'a'+8;
			b-=2;
		}//用掉2个2*1
		else {
			cout<<"IMPOSSIBLE";
			return 0;
		}//无解
	}
}
```

- 这样一来我们便得出了答案，然后输出即可。

  但注意，我们之前改变了 $n$ ， $m$ ，输出可能会缺失，所以要在先前用 $2$ 个变量先储存起来。
	
    如果跟样例不一样是正常的，自己推推就可以了。
    
```cpp
x=n;
y=m;//存储
/*
中间省略
*/
for(int i=1;i<=x;i++){
	for(int j=1;j<=y;j++){
		cout<<ans[i][j];
	}
	cout<<endl;
}//输出
```


------------


### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,x,y;
int pos;
char ans[110][110];
int main(){
	cin>>n>>m>>a>>b>>c;
	x=n;
	y=m;//存储 
	if(n*m&1||a*2+b*2+c*4<n*m){//无解 
		cout<<"IMPOSSIBLE";
		return 0;
	}
	if(n&1){//当n被2整除
		if(m/2>a){//1*2不够了
			cout<<"IMPOSSIBLE";
			return 0;
		}
		a-=m/2;
		pos=0;
		for(int i=1;i<=m;i+=2){
			ans[n][i]=ans[n][i+1]=pos+'y';
			pos^=1;
		}//填充
		n--;//去行
	}
	if(m&1){//当m被2整除
		if(n/2>b){//2*1不够了
			cout<<"IMPOSSIBLE";
			return 0;
		}
		pos=0;
		b-=n/2;
		for(int i=1;i<=n;i+=2){
			ans[i][m]=ans[i+1][m]=pos+'y';
			pos^=1;
		}//填充
		m--;//去列
	}
	for(int i=1;i<=n;i+=2){
		for(int j=1;j<=m;j+=2){
			pos=(i%4/2+j%4/2)%2;
			if(c>=1){
				ans[i][j]=ans[i][j+1]=ans[i+1][j]=ans[i+1][j+1]=pos+'a'+2;
				c--;
			}//用的2*2
			else if(a>=2){
				ans[i][j]=ans[i][j+1]=pos+'a'+4;
				ans[i+1][j]=ans[i+1][j+1]=pos+'a'+5;
				a-=2;
			}//用掉2个1*2
			else if(b>=2){
				ans[i][j]=ans[i+1][j]=pos+'a'+7;
				ans[i][j+1]=ans[i+1][j+1]=pos+'a'+8;
				b-=2;
			}//用掉2个2*1
			else {
				cout<<"IMPOSSIBLE";
				return 0;
			}//无解
		}
	}
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			cout<<ans[i][j];
		}
		cout<<endl;
	}//输出 
	return 0;
}

```



---

## 作者：MCRS_lizi (赞：0)

[CF26C题目传送门](https://www.luogu.com.cn/problem/CF26C)

~~啊哈哈哈终于有水黑了~~
# 题目大意
输入 $n,m,a,b,c$（ $1<=n,m<=100$ ， $0<=a,b,c<=10^4$ ） ，表示要用 $a$ 块 $1*2$ 的木板， $b$ 块 $2*1$ 的木板， $c$ 块 $2*2$ 的木板，填充一块大小为 $n*m$ 的矩形，如果可以，输出任意一种填充方式（具体输出方式见题目），如果不可以，输出 "IMPOSSIBLE "。
# 题目分析
拿到题目后第一个要想什么？那当然是先对 $n$ 和 $m$ 进行分析啦。

很显然，所有木板的面积都是偶数，那如果矩形的面积是个奇数（也就是 $n$ 和 $m$ 都是奇数），那自然是不可能的。

接下来考虑，如果 $n$ 和 $m$ 中有一个奇数那我们自然可以将其分成偶数乘偶数的一块加上 $1$ 乘偶数的一块。

那就先把 $1$ 乘偶数那一块先处理了吧，我们只要拿出 $n/2$ 或者 $m/2$ 块竖着的或者是横着的木板填了就行了。

那么无论如何，肯定只剩下偶数乘偶数的一大块了。

这一块一定可以被切分成许多个 $2*2$ 的小块，每个小块都可以用一个 $2*2$ 的，两个 $1*2$ 或者 $2*1$ 的来补齐。

按照这种方式去填就可以了，剩下的不过是慢慢模拟即可。

当然，如果以上过程中哪一种木板不够用了并且无法替代的话，那肯定是 "IMPOSSIBLE" 没跑了。
 
可以证明以上贪心策略是最优的，这个应该不用多说吧。
#  _**Code**_ 
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c;
bool used[1001];
char ch[101][101];
int main()
{
	cin>>n>>m>>a>>b>>c;
	if(n&1&&m&1)
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	if(n&1)
	{
		if(m/2>a)
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
		a-=m/2;
		for(int i=1;i<=m;i+=2)
		{
			ch[n][i]=ch[n][i-1]=='a'? 'b':'a';
			ch[n][i+1]=ch[n][i];
		}
	}
	if(m&1)
	{
		if(n/2>b)
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
		b-=n/2;
		for(int i=1;i<=n;i+=2)
		{
			ch[i][m]=ch[i-1][m]=='a'? 'b':'a';
			ch[i+1][m]=ch[i][m];
		}
	}
	for(int i=1;i<n;i+=2)
	{
		for(int j=1;j<m;j+=2)
		{
			memset(used,0,sizeof(used));
			for(int k=i-1;k<=i+2;k++)
			{
				for(int l=j-1;l<=j+2;l++)
				{
					if(k<=i+1&&k>=i&&l<=j+1&&l>=j)
					{
						continue;
					}
					if(k==i-1&&l==j-1||k==i-1&&l==j+2||k==i+2&&l==j-1||k==i+2&&l==j+2)
					{
						continue;
					}
					used[ch[k][l]]=1;
				}
			}
			if(c)
			{
				c--;
				for(char k='a';k<='z';k++)
				{
					if(!used[k])
					{
						ch[i][j]=k;
						ch[i][j+1]=k;
						ch[i+1][j]=k;
						ch[i+1][j+1]=k;
						break;
					}
				}
			}
			else if(a>=2)
			{
				a-=2;
				bool flag=0;
				for(char k='a';k<='z';k++)
				{
					if(!used[k])
					{
						if(flag)
						{
							ch[i+1][j]=k;
							ch[i+1][j+1]=k;
							break;
						}
						else
						{
							ch[i][j]=k;
							ch[i][j+1]=k;
						}
						flag=1;
					}
				}
			}
			else if(b>=2)
			{
				b-=2;
				bool flag=0;
				for(char k='a';k<='z';k++)
				{
					if(!used[k])
					{
						if(flag)
						{
							ch[i+1][j+1]=k;
							ch[i][j+1]=k;
							break;
						}
						else
						{
							ch[i][j]=k;
							ch[i+1][j]=k;
						}
						flag=1;
					}
				}
			}
			else
			{
				cout<<"IMPOSSIBLE";
				return 0;
			}
		//	cout<<a<<" "<<b<<" "<<c<<endl;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<ch[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$

---
### 解题思路：

问题分为两个部分，判断是否有解，以及有解时如何填充字母。

---
任意两个 $1\times 2$ 的地板都是可以拼出一个 $2\times 2$ 的地板的。中间的一大部分都可以用 $2\times 2$ 来填充，但是边角只能由对应的 $1\times 2$ 的地板填充，所以因当优先填充边角，然后再用剩余的填充中间的大部分。如果这两个进程中的任何一个地板不够用了，那么一定无解。

特别地，当 $nm$ 为一个奇数的时候，同样无解。

---
填充字母的时候依然是按照上述的过程模拟，不妨按照奇偶性为每一个位置上的每一种地砖确定字母，保证优先把边上填起来就行了。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int n,m,a,b,d,c[105][105],flag;
int main(){
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&d);
	flag=1;
	if(n*m%2==1)flag=0;
	if(n%2==1){
		for(int i=1;i<=m;i+=2)c[1][i]=c[1][i+1]=((i/2)%2==0?1:2),a-=1;
		if(a<0)flag=0;
	}
	if(m%2==1){
		for(int i=1;i<=n;i+=2)c[i][1]=c[i+1][1]=((i/2)%2==0?1:2),b-=1;
		if(b<0)flag=0;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(c[i][j]!=0)continue;
		if(a>=2){
			c[i][j]=c[i][j+1]=(i+j)/2%2==0?3:4;
			c[i+1][j]=c[i+1][j+1]=(i+j)/2%2==0?5:6;
			a-=2;continue;
		}
		if(b>=2){
			c[i][j]=c[i+1][j]=(i+j)/2%2==0?7:8;
			c[i+1][j+1]=c[i][j+1]=(i+j)/2%2==0?9:10;
			b-=2;continue;
		}
		if(d>=1){
			c[i][j]=c[i][j+1]=c[i+1][j]=c[i+1][j+1]=(i+j)/2%2==0?11:12;
			d--;continue;
		}
		flag=0;
	}
	if(flag==0){
		printf("IMPOSSIBLE\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		printf("%c",c[i][j]+'a'-1);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：星空舞涵 (赞：0)

###### 看到这道古老的CF水题还没有题解，本蒟蒻前来水一发。


~~这道题感觉没有黑题难度呀QAQ~~

## 正文：
对于矩形只有四种情况

1. $n,m$都是奇数

		S=n×m,S同样是个奇数，不可能组成；
2. $n$是奇数,$m$是偶数

		我们考虑把最后一行直接用1×2的木板填满;
 
3. $m$是奇数，$n$是偶数
 
 		我们考虑把最后一列直接用2×1的木板填满；
        
对于单独多出来的一行或者一列，我们直接用x,y(字母随意）两个字母填充
        
4. $m,n$都是偶数		
        
	我们如何填充呢？
    
   举个例子
   
   6 10 8 100 5
   
   假如2×2的木板是足够的，我们一定可以直接用2×2的木板直接填满，如果2×2的木块不够的话用把两块1×2的木板或者两块2×1的木板替代。
   所以我们先把矩形用2×2的形式
	
    ```cpp
	aabbaabbaa
	aabbaabbaa
	bbaabbaabb
	bbaabbaabb
	aabbaabbaa
	aabbaabbaa
	```
	如果2×2的木板不够用，我们就优先用1×2的木板替换（从头开始）
    ```cpp
	ccddccddaa
	aabbaabbaa
	bbaabbaabb
	bbaabbaabb
	aabbaabbaa
	aabbaabbaa
	```
 	如果1×2的木板同样不够用，我们就用2×1的木板替换（从尾开始）
    ```cpp
	ccddccddaa
	aabbaabbaa
	bbaabbaabf
	bbaabbaabf
	aebeaebeae
	aebeaebeae
	```

代码使用的字母可能与上面的不太一样。

但是思路最重要。

蒟蒻码风不好，请见谅。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,x,y,s,l,ll,na,nb,nc,o,lll;
char ans[1001][1001];
int main()
{
	cin>>n>>m>>a>>b>>c;
	if(n*m%2==1)//面积是奇数 
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	if(2*a+2*b+4*c<n*m)//木板总面积小于矩形面积 
	{
		cout<<"IMPOSSIBLE";
		return 0; 
	}
	x=m;
	y=n;
	if(n%2==1)
	{
		if(m/2>a)//最后一行无法填满 
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
		a=a-m/2;
		for(int i=1;i<=m;i++)
		{
			if(i%4==1)	ans[i][n]='a';
			if(i%4==2)	ans[i][n]='a';
			if(i%4==3)	ans[i][n]='b';
			if(i%4==0)	ans[i][n]='b'; 
		}
		n--;
	}
	if(m%2==1)
	{
		if(n/2>b)//最后一列无法填满 
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
			b=b-n/2;
		for(int i=1;i<=n;i++)
		{
			if(i%4==1)	ans[m][i]='a';
			if(i%4==2)	ans[m][i]='a';
			if(i%4==3)	ans[m][i]='b';
			if(i%4==0)	ans[m][i]='b'; 
		}
		m--;
	} 
	int s=a/2+b/2+c;
	int ss=n*m/4;
	if(ss>s)//木板不够用 
	{
		cout<<"IMPOSSIBLE";
		return 0; 
	}
	for(int i=1;i<=n;i=i+2)//不管够不够先填成2*2的形式 
	{
		ll++;
		l=0;
		for(int j=1;j<=m;j=j+2)
		{
			l++;
			if((ll+l)%2==1)
			{
				ans[j][i]='c';
				ans[j+1][i]='c';
				ans[j][i+1]='c';
				ans[j+1][i+1]='c';
			}
			else 
			{
				ans[j][i]='d';
				ans[j+1][i]='d';
				ans[j+1][i+1]='d';
				ans[j][i+1]='d';
			}
		}
	}
	ss=ss-c;
	if(ss>0)//2*2的木板不够用1*2的木板替代 
	{
		na=min(ss,a/2);
		ss=ss-na;
	}
	if(ss>0)//加上1*2的也不够用，用2*1的木板 替代 
	{
		nb=min(ss,b/2);
		ss=ss-nb;
	}
	for(int i=1;i<=n;i=i+2)//1*2的木板从头开始替代 
	{
		if(o==1)	break;
		for(int j=1;j<=m;j=j+2)
		{
			if(na==0)
			{
				o=1;
				break;
			}
			if(na%2==1)
			{
				ans[j][i]='e';
				ans[j+1][i]='e';
				na--;
			}
			else 
			{
				ans[j][i]='f';
				ans[j+1][i]='f';
				na--;
			}
		}
	}
	o=0;
	for(int i=n;i>=1;i=i-2)//2*1的木板从结尾开始替代 
	{
		lll++;
		if(o==1)	break;
		for(int j=m;j>=1;j=j-2)
		{
			if(nb==0)	
			{
				o=1;
				break;
			}
			if(lll%2==1)
			{
				ans[j][i]='g';
				ans[j][i-1]='g';
				nb--;
			}
			else 
			{
				ans[j][i-1]='h';
				ans[j][i]='h';
				nb--;
			}
		}
	}
	for(int i=1;i<=y;i++)
	{
		for(int j=1;j<=x;j++)
		{
			cout<<ans[j][i];
		}
		cout<<endl;
	}
		
 } 
```



---

