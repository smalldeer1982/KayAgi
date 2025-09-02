# 圈图的匹配 Edge Case

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4521

[PDF](https://uva.onlinejudge.org/external/16/p1646.pdf)

# 题解

## 作者：RE_Prince (赞：3)

# UVA1646 圈图的匹配 Edge Case

来一发 Python 题解/cy

这是一道递推题。

状态转移公式的证明其余题解说的很清楚了，我就不再叙述了。

状态转移公式： $dp_i=dp_{i-1}+dp_{i-2}$。

其实就是斐波那契数列。

因为 Python 自带高精，所以把这个式子套进去就行了（我因为输入的数没转 `int` 调了好久）

197B 代码奉上：

```python
dp=[]
dp.append(1)
dp.append(2) #初始化
for i in range(2,10009):
    dp.append(dp[i-1]+dp[i-2]) #预处理，节省时间
while True:
    try: #这里解释一下，这其实相当于C++里的while(~scanf())
        n=int(input()) #转int！
        print(dp[n-1]+dp[n-3]) #其实是n和n-2，但是因为下标是从0开始的，输出的下标也应该往后推一位
    except EOFError: #没得可输入了，结束
        break
```


---

## 作者：cyffff (赞：2)

# UVA1646 圈图的匹配 Edge Case
#### [_传送门_](https://www.luogu.com.cn/problem/UVA1646)
## 思路
不考虑第 $n$ 条边时，只有连接和不连接的情况，所以
$$f[n] =\begin{cases}1&n=1\\2&n=2\\f[n-1]+f[n-2]&n>2\end{cases}$$
而 $1$ 与 $n$ 连接时有 $n-2$ 条链，不连接时有 $n$ 条，所以
$$ans[n]=f[n]+f[n-2]$$
$O(n)$预处理到$10000$，每次输出将 $n$ 读入，输出 $ans[n]$ 即可。

注意：需要使用高精加法，不然到 $48$ 左右就炸了，在结构体里面重载运算符即可。

其余在代码注释里讲

上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
struct big_int{
	int len;
	int l[N];
	inline void f(){//初始化
		memset(l,0,sizeof(l));
	}
	friend big_int operator +(const big_int &a,const big_int &b){//重载运算符+
		big_int c;
		c.f();
		c.len=max(a.len,b.len);//高精加
		for(int i=1;i<=c.len;i++){
			c.l[i]=a.l[i]+b.l[i]+c.l[i];
			c.l[i+1]+=c.l[i]/10;
			c.l[i]%=10;
		}
		if(c.l[c.len+1]){
			c.len++;
		}
		return c;
	}
	inline void write(){//输出
		for(int i=len;i;i--){
	    	printf("%d",l[i]);
		}
		puts("");
	}
}a[N];
int main(){
	int n;
	a[0].len=0;
	a[0].f();
	a[1].len=1;
	a[1].l[1]=1;
	a[2].len=1;
	a[2].l[1]=2;
	for(int i=3;i<=10000;i++){//预处理
		a[i]=a[i-1]+a[i-2];
	}
	while(scanf("%d",&n)!=EOF){//多测
		(a[n]+a[n-2]).write();//注意优先级
	}
	return 0;
}
/*
代码长度:812B
用时:270ms
*/
```


---

## 作者：loser_seele (赞：1)

状态转移方程别的题解已经讲的很清楚了，这里再略微提一下。

这道题目要求的相当于是 OEIS A00032 这个数列，得到的递推式是设答案数列为 $ a $，斐波那契数列为 $ f $，则有 $ a_i=f_i+f_{i-2} $。

至于证明，可以分析第 $ i $ 条边连接和不连接的情况，两种方法的方案总数分别是 $ f_i $ 和 $ f_{i-2} $，于是可以直接递推计算即可。

但是递推的方法显然未免过于简单，考虑用矩阵快速幂优化实现计算斐波那契数列，计算出矩阵后直接上矩阵快速幂即可，时间复杂度理论上为 $ \mathcal{O}(nw^3\log{n}) $ 的，其中 $ w=2 $ 为矩阵大小。

但因为自己的高精跑得太慢，而且小数据规模下多次计算数列值时矩阵快速幂表现不优，于是考虑对于较小的数据用矩阵快速幂计算，较大的数据直接递推。

这个算法常数很大，因为题目时限开大才能通过，喜提最劣解。

以下代码因为高精度模板过长已经省略高精度部分。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=3000+10;
HP ans[10020];
typedef long long ll;
const int N=2;
int n;
int k;
struct node
{
HP g[N+2][N+2];
}f,res;
void matrixI(node &x)
{
for(int i=1;i<=N;i++)
for(int j=1;j<=N;j++)
if(i==j)
x.g[i][j]=1;
else
x.g[i][j]=0;
}
void matrixMultiple(node &x,node &y,node &z)
{
memset(z.g,0,sizeof(z.g));
for(int i=1;i<=N;i++)
for(int j=1;j<=N;j++)
if(x.g[i][j].cmp())
for(int k=1;k<=N;k++)
z.g[i][k]=z.g[i][k]+x.g[i][j]*y.g[j][k];
}
void matrixMuli(int k)
{
matrixI(res);
node tmp=f,t;
while(k)
{
if(k&1)
{
matrixMultiple(res,tmp,t);
res=t;
}
matrixMultiple(tmp,tmp,t);
tmp=t;
k>>=1;
}
}
void solve()
{
matrixMuli(k);
ans[k]=res.g[1][2];
}
signed main()
{
ans[1]=1;
ans[2]=1;
for(k=3;k<=10002;k++)
{
if(k<=3000)
{
n=2;
f.g[1][1]=1;f.g[1][2]=1;
f.g[2][1]=1;f.g[2][2]=0;
solve();
}
else
ans[k]=ans[k-1]+ans[k-1];
}
while(cin>>n)
{
HP sum=ans[n+1]+ans[n-1];
sum.output();
}
}
```


---

## 作者：JK_LOVER (赞：0)

## 题意
$n$ 个点连成一个圆，求没有公共点的边集的个数。可能不太好懂，这里搬一下原题的图片。
![](https://cdn.luogu.com.cn/upload/image_hosting/ta98nqet.png)
所以 $n=4$ 时候，$ans=7$ 。
## 分析
我们先破环成链。那么在不考虑第 $n$ 条边时。因为每一个点只可以连一条边。那么就有链接和不连接两种方法。
$$
dp[n] = dp[n-1]+dp[n-2]
$$
其实可以看做跳楼梯的方案数
-  走一步。
- 走两步。
那么现在考虑第 $n$ 条边时，产生的方案数。那么就是 $1$ 号和 $n$ 号，到底连不连边。
- 连边就只考虑 $n-2$ 个组成链。
- 不连边就是 $n$ 个组成链。
- $ans = dp[n]+dp[n-2]$

最后再写 
~~（抄）~~
个高精就可以了。
## 代码
```cpp
#include<iostream>  
#include<cstring>  
#include<string>  
#include<cstdio>  
  
using namespace std;  
  
#define MAXN 4000  
  
struct HP  
{  
    int len;  
    long long s[MAXN];  
    HP()  
    {  
        memset(s,0,sizeof(s));  
        len=1;  
    }  
  
    HP operator =(const char *num)  
    {  
        int k=0,j=0;  
        long long mul=1,tmp=0;  
        for(int i=strlen(num)-1;i>=0;i--)  
        {  
            tmp=tmp*mul+(long long)(num[i]-'0');  
            j++,mul*=10;  
            if(j==8)  
            {  
                s[k++]=tmp;  
                j=0;  
                mul=1;  
                tmp=0;  
            }  
        }  
        if(tmp!=0)  
            s[k++]=tmp;  
        len=k;  
        return *this;  
    }  
  
    HP operator =(int num)  
    {  
        char s[MAXN];  
        sprintf(s,"%d",num);  
        *this=s;  
        return *this;  
    }  
  
    HP(int num) { *this=num;}  
  
    HP(const char*num) {*this=num;}  
  
    string str()const  
    {  
        string res="";  
        for(int i=0;i<len-1;i++)  
        {  
            long long tmp=s[i];  
            for(int j=0;j<8;j++)  
            {  
                res=(char)(tmp%10+'0')+res;  
                tmp/=10;  
            }  
        }  
        long long tmp=s[len-1];  
        while(tmp!=0)  
        {  
            res=(char)(tmp%10+'0')+res;  
            tmp/=10;  
        }  
        if(res=="") res="0";  
        return res;  
    }  
  
    HP operator +(const HP& b) const  
    {  
        HP c;  
        c.len=0;  
        long long g=0;  
        for(int i=0;g!=0||i<max(len,b.len);i++)  
        {  
            long long x=g;  
            if(i<len) x+=s[i];  
            if(i<b.len) x+=b.s[i];  
            c.s[c.len++]=x%100000000;  
            g=x/100000000;  
        }  
        return c;  
    }  
    void clean()  
    {  
        while(len > 1 && !s[len-1]) len--;  
    }  
  
    HP operator *(const HP& b)  
    {  
        HP c;  
        c.len=len+b.len;  
        for(int i=0;i<len;i++)  
            for(int j=0;j<b.len;j++)  
                c.s[i+j]+=s[i]*b.s[j];  
        for(int i=0;i<c.len-1;i++)  
        {  
            c.s[i+1]+=c.s[i]/100000000;  
            c.s[i]%=100000000;  
        }  
        c.clean();  
        return c;  
    }  
  
    HP operator - (const HP& b)  
    {  
        HP c;  
        c.len = 0;  
        long long g=0;  
        for(int i=0;i<len;i++)  
        {  
            long long x=s[i]-g;  
            if(i<b.len) x-=b.s[i];  
            if(x>=0)  
                g=0;  
            else  
            {  
                g=1;  
                x+=100000000;  
            }  
            c.s[c.len++]=x;  
        }  
        c.clean();  
        return c;  
    }  
    void output()  
    {  
        printf("%lld",s[len-1]);  
        for(int i=len-2;i>=0;i--)  
            printf("%.8lld",s[i]);  
        printf("\n");  
    }  
};  
  
  
HP a[12000];  
int n;  
  
int main()  
{  
    a[1] = 1; 
	a[2] = 2;
    for(int i=3;i<10005;i++)  
        a[i]=a[i-1]+a[i-2];  
    while(~scanf("%d",&n))  
    {  
		HP ans = a[n] + a[n-2]; 
        ans.output();  
    }  
    return 0;  
  
}  
```


---

