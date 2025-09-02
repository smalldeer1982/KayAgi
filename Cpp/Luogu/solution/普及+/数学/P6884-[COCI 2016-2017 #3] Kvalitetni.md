# [COCI 2016/2017 #3] Kvalitetni

## 题目描述

定义一个算术表达式是有质量的，当且仅当这个算术表达式只由括号，数字，乘法符号和加法符号组成。

一个有质量的算术表达式由下列方式递归定义：

- 仅包含一个正实数**小于等于** $Z_1$。这种表达形式如下：
 
 $$(x)$$
 
 例如当 $Z_1=5$，那么 $(4)$ 就是有质量的算术表达式。

- 如果 $A_1,A_2,\cdots,A_k(2\le k\le K)$ 都是有质量的算术表达式，并且这些有质量的算术表达式的和**小于等于** $Z_k$，那么

$$(A_1+A_2+\cdots+A_k)$$

$$(A_1*A_2*\cdots*A_k)$$

也是有质量的算术表达式。

你会得到一条**所有数字都被问号代替**的算术表达式，求满足这个表达式是有质量的算术表达式的前提下，这个表达式可能的最大值。


## 说明/提示

#### 样例 1 解释

表达式 $((3)+(3))$ 满足条件，因此它是一个算术表达式。容易证明，$6$ 是这个表达式的最大值。

#### 样例 2 解释

对于表达式 $(((1)+(2))*(2))$ 可以达到最大值。

#### 样例 3 解释

对于表达式 $((2)*(2)*(2))$ 可以得到最大值。

### 数据规模与约定

对于 $100\%$ 的数据，满足 $2\le K\le 50,1\le Z_i\le 50$，表达式的长度 $\le 10^6$。

### 说明

**题目译自 [COCI2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #3](https://hsin.hr/coci/archive/2016_2017/contest3_tasks.pdf) _T4 Kvalitetni_**。

## 样例 #1

### 输入

```
2
10 6
((?)+(?))```

### 输出

```
6.00000```

## 样例 #2

### 输入

```
3
2 5 3 
(((?)+(?))*(?))```

### 输出

```
6.00000```

## 样例 #3

### 输入

```
3 
2 10 6 
((?)*(?)*(?))```

### 输出

```
8.0000000```

# 题解

## 作者：Feyn (赞：1)

[link](https://www.luogu.com.cn/problem/P6884)

首先一个重要结论是，由于这个式子中所有参数的取值范围都是任意实数，所以任意一个式子的取值都应该是连续的，也就是说假如一个式子的最大取值为 $X$，则 $\forall x\in[0,X]$ 都是可以通过调整一些参数的值得到的，这样一来关于一个人类高质量柿子我们只需要知道它可能的最大值就可以知道它所有可能的取值。

但最大值如何求呢？如果是和的形式那很简单，直接把这个式子中所有部分的最大值加起来，然后和 limit 取较小值即可，因为根据上面的结论，假如和大于了 limit，那么我们可以通过调整式子的参数使得它的值变得小一些然后使得整个大式子的值刚好等于 limit。

那乘的形式怎么办呢？小学奥数说过和定差小积大，也就是 $a\times b\le(\frac{a+b}{2})^2$ ，且当 $a=b$ 时可以取到等号。于是可以推而广之得到 $\prod\limits_{i=1}^Na_i\le(\frac{\sum a_i}{N})^N$，也就是说一个乘积式各项的和确定之后，这些项越接近最后的乘积也就越大，排序之后选择即可。


个人用的递归写法，人傻常熟大，仅供参考。

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=1000010;
const int M=100;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline double min(double s1,double s2){
	return s1<s2?s1:s2;
}

stack<int>st;
int m,len,a[M],pl[N];
char w[N];

inline double f(int l,int r){//返回一个区间对应的高质量柿子的最大取值
	if(l==r)return a[1];//如果括号中只有一个数直接反悔limit 
	int n=0;double data[M];//记录这个区间内所有柿子的最大值 
	char op;
	for(int i=l;i<=r;i++){
		if(w[i]=='(')data[++n]=f(i+1,pl[i]-1),i=pl[i];
		else op=w[i];//记录这些柿子用什么符号连接 
	}
	if(n==1)return data[1];
	if(op=='+'){
		double sum=0;
		for(int i=1;i<=n;i++)sum+=data[i];
		return min(a[n],sum);//如上文，返回和和limit的较小值 
	}
	if(op=='*'){
		double ava,ans=1,sum=a[n];
		sort(data+1,data+n+1);//从小到大贪心选择 
		int pl=1;
		while(pl<=n){
			ava=sum/(n-pl+1);
			if(ava<=data[pl]){
				for(;pl<=n;pl++)ans*=ava;
				break;
			}
			for(;pl<=n;pl++){
				if(data[pl]<=ava)ans*=data[pl],sum-=data[pl];
				else break;
			}
		}
		return ans;//返回即可 
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)read(a[i]);
	scanf("%s",w+1);len=strlen(w+1);
	for(int i=1;i<=len;i++){
		if(w[i]=='(')st.push(i);
		if(w[i]==')')pl[st.top()]=i,st.pop();
		//预处理出每个左括号对应右括号的位置 
	}
	printf("%f\n",f(1,len));
	
	return 0;
}
```

---

## 作者：Hasinon (赞：1)

### （第一次发题解，做的不好请多谅解)  
而且题目有点小错误，粗体表示大小关系的词都应该是**小于等于**。

------------

### 首先我们要探讨下如何得到每一个有质量的算术表达式的最大值  
'+' 组成的表达式简单  
一个由 '+' 组成的表达式: $ X=(x_1 + x_2 + ... + x_n) $  
表达式 X 最大值就是所有被包含表达式 $x$ 的最大值的和与当前表达式的限制最大值 $z_n$的最大值  

'* ' 组成的表达式，就要涉及**均值不等式**了。  

均值不等式的一部分是几何平均数小于等于算术平均数  
即：$\sqrt[n]{x_1 \times x_2 \times...\times x_n } \le \frac{1}{n}\sum_{i=1}^nx_i $  
所以 ：$ x_1 \times x_2 \times...\times x_n \le (\frac{1}{n}\sum_{i=1}^nx_i)^n $  

一个由 '* ' 组成的表达式: $ X=(x_1 * x_2 * ... * x_n) $的值就是左式  
所以表达式 $X$ 最大值等于所有被包含表达式 $x$ 的最大值的平均数的n次方.

但是吧，这是理想情况，实际会出现某被包含表达式 $x$ 的最大值小于平均数的情况。  

这时先单独把答案乘上这项的最大值，把平均数与最大值之差除以剩下的数的数量再加到平均数上。 （也能用均值不等式证明最优）  

还会出现刚开始某被包含表达式 $x$ 的最大值大于等于平均数，但后面随着平均数的改变导致最大值小于平均数了，所以开个 while 循环执行到以上情况不出现就好。  
（忘记考虑这个了，因此考试时丢了 10 分呜呜）


------------


实现的话用 DFS 做：   
每一个 DFS 返回的是此表达式的最大值。  

遇到 '(' 就往下一层。  

遇到 '?' 就...其实不用管的啦，因为每个 '?' 都是被一队括号圈起来的，只要只检查到括号，没有 '+' 和 '* ' ,肯定只有一个 '?' ,就是只有一个被包含表达式 $x$ ,所以返回$ z_1 $  

遇到 '+' 或者 '* ' 记录一下。  

遇到 ')'就算出此表达式最大值，然后返回。



------------
(注意一下输入啊，第一行后面有个空格)  

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
double z[55];
ll a[100005],ato=0;
double dfs()
{
	ll t=-1;//如果没有 '+','*'，直接返回只有一个问号的时候的最大值z[1]
	ll num=0;
	vector<double> bds;
	char c;
	while(1){ 
		c=getchar();
		if(c=='(') 
		{
			bds.push_back(dfs());//遇 '(' 进下一层
			num++;
		} 
		else{
			if(c=='+') t=0;//记录
			else{
				if(c=='*') t=1;//记录
				else{
					if(c==')')//开始算最大值
					{
						if(t==0)
						{
							double tot=0;
							for(int i=0; i<num; i++)
								tot+=bds[i]; 
							return min(tot,z[num]);
						}
						else
						{
							if(t==1)
							{
							double lnum=num,aver=z[num]/lnum,tot=1,dtaver=0;
							ato=0;
							for(int i=0; i<num; i++)
							a[++ato]=i;
							while(1)//不断判断是否存在某表达式最大值小于平均数并改变平均数
							{
								bool lb=0;
								ll lato=ato;
								ato=0;
								for(int j=1; j<=lato; j++)
								{
									ll i=a[j];
									if(bds[i]<aver) 
									{
										tot*=bds[i];
										dtaver=dtaver+(aver-bds[i]);
										lnum--; 
										lb=1;
									}
									else
									{
										a[++ato]=i;
									}
								}
								if(lb==0||lnum<=0) break;
								dtaver/=lnum;
								aver+=dtaver;
								dtaver=0;
							}
							if(lnum>0)//剩下的数直接按平均数乘就好
							{
								dtaver/=lnum;
								aver+=dtaver;
								for(int i=1; i<=lnum; i++)
								{
									tot*=aver; 
								}
							}
							return tot;
							}
							else
							{
								return z[1];//直接返回 z[1]
							}
						}
					} 
				}
			}		
		} 
	}
}
int main()
{
	ll k;
	cin>>k;
	for(int i=1; i<=k; i++)
		cin>>z[i];
	char lc=getchar();
	while(lc!='(') lc=getchar();
	printf("%.6f", dfs());//%.6f 保留 6 位小数
}
```

---

