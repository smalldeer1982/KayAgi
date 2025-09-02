# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb```

### 输出

```
1
7
3```

# 题解

## 作者：hhhhhhhhhhh (赞：38)

~~自认为写的还好，应该能看懂。~~

### 题意：
求最小的把字符串$S$分割成若干个互不相交的回文子串的个数。



#### Step $1$：列状态转移方程。
考虑$DP$，设 $p[ i ]$ 为前$i$个字符中划分的最小回文子串的个数，对于每一个$i$，会出现两种情况：

$1.$ $s[ i ] $为一个单独的回文子串，此时 $p[ i ] = p[ i - 1 ] +1 $。因为新划分了一个回文子串，所以$ p[ i ]$ 为前 $i - 1$ 个字符的最优值$+1$。

$2.$ $s[ i ] $与其他字符组成了一个回文子串，此时 $p[ i ] = p[ j - 1 ] + 1$。$j $为这个回文子串的左端。那么~~显然~~ 前 $j - 1$ 个字符的最优值加上新划分的回文串就是$ p[ i ]$ 的值。


~~建议动手模拟一下。~~

理解上面这些，应该就能切掉这道题了。不过，我们还没有想好如何判断 $s[ i , j ]$是否回文呢！

#### Step $2$： 判断字串回文。

刘汝佳大神的紫书上已经介绍了中心扩展法，让我们试一下动态规划，那我们就用动态规划。

设 $f[ i ][ j ] $表示字串$ s[ i ][ j ] $是否回文，是为$true$，否则为$false$。那么这个方程该是比较好想的了，即

$f[i][j]=\left\{\begin{matrix}f[i+1][j-1] & (s[i]=s[j])\\ 0 & (s[i]\neq s[j])\end{matrix}\right.$

初始状态为 
$\left\{\begin{matrix}f[i][i]=1& \\ f[i-1][i]=1& (s[i-1]=s[i])\end{matrix}\right.$


### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,p[1001];
    bool f[1001][1001];
    string s;
    cin>>t;
    while(t--)
    {
        cin>>s;
        n=s.size();
        s=' ' + s;
        memset(f,0,sizeof(f));//多测试数据时记得清空
        memset(p,0,sizeof(p));
        for(int i=1;i<=n;++i)
        {
            f[i][i]=true;
            f[i-1][i]=(s[i-1]==s[i]);
        }
        for(int j=2;j<=n;++j)
        {
            for(int i=1;i<j-1;++i)//枚举长度大于等于三的字串，还能防止下标越界
            {
                if(s[i]==s[j])//相同
                    f[i][j]=f[i+1][j-1];
                else f[i][j]=false;//不同
            }
        }
        for(int i=1;i<=n;++i)
        {
            p[i]=p[i-1]+1;//假设没有回文串与其匹配，可以理解为赋初值
            for(int j=1;j<i;++j)//枚举j，判断能不能让子串s[i,j]回文
                if(f[j][i])
                    p[i]=min(p[i],p[j-1]+1);                 
        }
        cout<<p[n]<<endl;
    }
    return 0;
}

```
时间复杂度与空间复杂度均为$O(N^{2})$~~吧~~

你以为到这就完了吗？~~确实~~不，你还没有点赞！

若有错误请多多指教。

UPD1:修改了部分笔误，丰富了代码注释。


---

## 作者：星沐 (赞：15)

## 这是一道经典的区间DP。
#### 当然深搜也能过

看题之后写了个判断是否为回文串的函数，虽然最后并没有用上，
但还是码上吧,
很简单的函数
```
/*int judge(string s)
{
     int i,ls;
	 int flag=1;
	 ls=s.length();
	 for(i=0;i<ls/2;i++)
	 {
		 if(s[i]!=s[ls-1-i])
		 {
			 flag=0;
			 break;
		 }
	 }
	 return flag;
}*///判断回文串的函数。

```
### 状态转移方程c[i]=min(c[i],c[j-1]+1);
### 然后记得边界条件要写对，读题很重要；
------------
## 正解如下
###### 如有不到位的地方，欢迎指正，谢谢
###### bool tt[i][j]指i位置元素到j位置元素是否为回文串。相当于标记，优化了判断字符串的速度。
```
#include<bits/stdc++.h>
using namespace std ;
string s;
int t;
int c[1005];	
bool tt[1005][1005];
int work(string s)
{
	int ls=s.length();
	for(int i=0;i<ls;++i)
	{
		c[i]=i+1;//初始条件
		for(int j=i;j>=0;j--)
	 	{
       	 	if (i==j||s[j]==s[i]&&(j+1==i||tt[j+1][i-1])) //注意奇数和偶数长度的字符串。 
			{
        		tt[j][i]=1;//注意j到i才是正序； 
          	    if (j==0) 
				 {
          		  	c[i]=1; //当j==0时，题目是问子串的个数，不是分割次数！！！
          	 	 } 
				else
				{
                	c[i]=min(c[i],c[j-1]+1);//状态转移方程； 
           		}
       		}	
   		 }
	}
    return c[ls-1];//因为字符串下标是从0开始的
}
int main()
{
	cin>>t;
	for(int i=1;i<=t;++i)
	{
		cin>>s;
		memset(c,0x3f,sizeof(c));//记得初始化
		memset(tt,0,sizeof(tt));
		cout<<work(s)<<endl;//换行一定要打。
	}
	return 0；
}


```


---

## 作者：龙潜月十五 (赞：5)

## 一、前言

这是一道线性 DP，思路十分简单，不过这道题需要判断**回文串**，这里就介绍一种专门求解回文串的算法——**manacher**。

## 二、题意

有一个字符串 $s$，把它分割成互不相交的回文子串，求分割的回文子串的**最小个数**。

## 三、思路

### （1）状态

状态十分明确，设 $f(i)$ 为**字符 $0 \sim i$ 划分成的最小回文串的个数**。

### （2）转移

$f(i)=min \{ f(j)+1 \}$，当且仅当 $s(j+1 \sim i)$ 是回文串。由于每次转移都要判断回文串，可以想到用 manacher 来解决。

## 四、manacher算法

### （1）简介

manacher 是一个**求字符串中最长回文连续子序列的算法**，相比于 $O(n^2)$ 的暴力求解回文串，它可以达到 $O(n)$ 的线性时间复杂度。

### （2）好文

- [洛谷日报](https://www.luogu.com.cn/blog/codesonic/manacheralgorithm)

- [oi-wiki](https://oi-wiki.org/string/manacher/)

### （3）例题

- [P3805 【模板】manacher算法](https://www.luogu.com.cn/problem/P3805)

- [P4555 [国家集训队]最长双回文串](https://www.luogu.com.cn/problem/P4555)


## 五、本题的实现

**_PS_**：建议读者先学会 manacher 算法再看。

前面通过 manacher 算法只能求出**依次以字符串中每个字符为对称中心向两边延伸的最长回文串长度** $hw(i)$，如何通过这个来判断每个子串是否是回文串呢？举个例子：

| 序号 | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| **字符** | # | a | # | a | # | a | # |
| $hw(i)$ | $0$ | $1$ | $2$ | $3$ | $2$ | $1$ | $0$ |

我们可以发现对于每个字符，根据其 $hw(i)$ 的值可以判断区间 $i-hw(i)+1 \sim i+hw(i)-1$ 是一个**回文串**。具体细节参考代码。

## 六、代码

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=2e3+7;
const int INF=1e9;
int hw[N],t,n,f[N];
char s[N];
char ss[N];
bool b[N][N];

void change()//插入# 
{
	ss[0]='#';
	ss[1]='#';
	for(int i=0;i<n;i++)
	{
		ss[i*2+2]=s[i];
		ss[i*2+3]='#';
	}
	n=n*2+2;
	s[n]=0;
}

void manacher()
{
	change();
	
	int maxright=0,mid;
	for(int i=1;i<n;i++)
	{
		if(i<maxright)
			hw[i]=min(hw[(mid<<1)-i],hw[mid]+mid-i);
		else
			hw[i]=1;
		while(ss[i+hw[i]]==ss[i-hw[i]])
			++hw[i];
		if(hw[i]+i>maxright)
		{
			maxright=hw[i]+i;
			mid=i;
		}
	}
}

void check()
{
	memset(b,false,sizeof(b));
	
	for(int i=0;i<n;i++)
		b[i+1][i+1]=true;//自己到自己一定是回文串 
	
	manacher();
	
	for(int i=0;i<=n;i++)
		hw[i]--;
	
	for(int i=0;i<=n;i++)
		if(hw[i]>0)//按奇偶性分类 
			if(hw[i]%2)
				while(hw[i]>1)
				{
					b[(i-hw[i]+1)/2][(i+hw[i]-1)/2]=true;
					hw[i]-=2;
				}
			else
				while(hw[i]>0)
				{
					b[(i-hw[i]+1)/2][(i+hw[i]-1)/2]=true;
					hw[i]-=2;
				}	
	
	n=(n-2)/2;//恢复原来的长度 
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin>>s;
		n=strlen(s);
		
		check();
		
		for(int i=2;i<=n;i++)
			f[i]=INF;
		f[1]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=i-1;j++)
				if(b[j+1][i])
					f[i]=min(f[i],f[j]+1);
		
		printf("%d\n",f[n]);
	}
}
```


---

## 作者：谁是鸽王 (赞：4)

### 很典型的DP题。
#### dp[t]代表从1到t，最少的回文子串数
#### 状态转移~~方程~~代码为 
	for(int t=1;t<=len;t++)
    	for(int k=1;k<=t;k++)//区间dp常用模板
        	if(jde(k,t))
        		dp[t]=min(dp[t],dp[k-1]+1);
#### 初始条件为：dp[t]=t (0<=t<=len)
#### jde(int L,int R)函数代表子串 L 到 R 是否是回文串
##### 写jde必须使用记忆化搜索
#### 注意： 若对于 字符串[l,r]是回文串，若 字符[l-1]==字符[r+1] 则可以判断 [l-1,r+1] 也是回文串

不说了，上代码，注释很详细。自己体会，我调了好久ToT

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
#define RP(t,a,b)	for(int t=(a),edd=(b);t<=edd;t++)
#define DRP(t,a,b)	for(int t=(a),edd=(b);t>=edd;t--)
inline int qr(void) {
	char c=getchar();
	int x=0,q=1;
	while(c<48||c>57)
		q=c=='-'?-1:q,c=getchar();
	while(c>=48&&c<=57)
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return q*x;
}//没有用的快读 
string data;
int dp[1001];//如上所述 
int rem[1001][1001];//记忆化搜索 
int T,len;
const int inf=0x3f3f3f3f;
bool dfs (int l,int r) {
	if(rem[l][r]!=-1)//若该区间运算过，直接返回 
		return rem[l][r];
	if(data[l]==data[r]&&dfs(l+1,r-1))//将dfs写在后面，减少递归次数 
		return rem[l][r]=1;
	if(l==r)
		return rem[l][r]=1;
	int t=l,i=r;
	while(l<r) {
		if(data[t]!=data[i])
			return rem[l][r]=0;
		t++;
		i--;
	}
	return rem[l][r]=1;
}
inline int work_dp(void) {
	RP(t,1,len) {
		RP(k,1,t)
		if(dfs(k,t))
			dp[t]=min(dp[t],dp[k-1]+1);

	}
	return dp[len];
}
int main() {
	T=qr();
	RP(t,1,T) {
		string temp;
		cin>>temp;
		data=" "+temp;
		memset(rem,-1,sizeof rem);
		dp[0]=0;
		len=temp.length();
		RP(i,1,len)
		dp[i]=i;
		printf("%d\n",work_dp());
	}
	return 0;
}
//功德圆满 
```



---

## 作者：qfbgsm (赞：3)

题解求通过。。。

蒟蒻第一篇题解，~~这道题应该不能算蓝题吧。。。感觉水了点~~
这道题的状态表示感觉和照明系统设计有点类似。。。

1.状态定义：dp(i)表示**前i个字母的最少回文子串数量**

2.核心代码：在第二层循环中每次都从**第一个字母**开始（设为l）与当前字母（设为r）比较，判断此区间[l,r]能否形成一个回文串

3.回文串判定：我的回文串判定也是~~十分水~~，就是暴力遍历一遍即可，相信一看就懂

解释一下为什么这样写：dp[i]=min(dp[i],dp[j-1]+1)

1.每次都先假设第i个字母无法与前i个（不包括第i个）字母形成回文串，于是乎就在dp[i-1]基础上+1

2.通过上述方法去遍历前i个字母判断是否能形成回文串，若第j个字母能与第i个字母形成回文串，那么前j-1个字母还是按照原先的最优方案，即dp[j-1]，别忘了dp(i)表示前i个字母的**最少**回文子串数量

```cpp
#include<iostream>
#include<cstring>
#include<math.h>
#include<stdlib.h>
#include<cstring>
#include<cstdio>
#include<utility>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll; 

/*------------------------------------------------------------------------*/
const int maxn=1005; 
int dp[maxn];
string s;
bool judge(int l,int r){//判断回文 
	int flag=1;
	while(l<r){
		if(s[l]==s[r]){
			l++,r--;
		}
		else {
			flag=0;
			break;
		}
	}
	
	
	if(flag)return 1;
	
	return 0;
	
}
int main( )
{	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("a.txt","r",stdin);
    //freopen("a.txt","w",stdout);
    
    int t;
    cin>>t;
    while(t--){
    	//char s[maxn];cin>>(s+1);
    	
    	
    	cin>>s;
    	dp[0]=1;
    	for(int i=1;i<s.length();++i){
    		dp[i]=dp[i-1]+1;
    		for(int j=0;j<=i;++j){
    			
    			if(judge(j,i)){//如果为回文串 
    				
    				dp[i]=min(dp[i],dp[j-1]+1);
    			}
    			
    			//
    			
    		}
    		
    	}
    	
    	cout<<dp[s.length()-1]<<endl;
    	
    	
    }
    
    return 0;
}
```



---

## 作者：Daniel_7216 (赞：2)

不懂第一篇题解为什么说这是一道区间 DP……真的很简单，十五分钟写完，一遍过。

先来考虑转移方程，设 $dp_i$ 表示把前 $i$ 个字符最少划分成多少个回文串，于是得到方程：

$dp_i=\min\limits_{j=1,p(j,i)}^i(dp_{j-1}+1)$

其中 $p(l,r)$ 是判断 $[l,r]$ 范围的子串是否回文的函数，最简单的方法是遍历子串每一个位置看这一位和对应位是否相同，这样我们可以写出 $O(N^3)$ 的做法，会超时，方程的 $O(N)$ 转移是无法进一步优化的，所以考虑 $p(l,r)$ 的 $O(1)$ 方法。

首先得出三条结论：

- 单个字符或两个相邻且相同的字符是回文子串。

- 如果一对相同的字符之间的子串是回文子串，则这对分别以这对字符为左右端点的字符也是回文子串。

- 如果前两条结论都不满足，则这个子串不是回文子串。

换句话说：

$p(l,r)=\begin{cases}true&l=r\\true&l+1=r,S_l=S_r\\true&p(l+1,r-1)=true,S_l=S_r\\false&otherwise\end{cases}$

因此，分别枚举左右端点，递推即可，注意对于第三种情况，$p(l,r)$ 是由 $p(l+1,r-1)$ 推得，所以 $l$ 要逆推，$r$ 要顺推，这样才能保证每个状态在被用来进行转移提前算过。

经过此处理，我们的转移方程复杂度降为 $O(N^2)$。代码也非常好写，想明白了就能过。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int T, n, dp[1001];
char s[1001];
bool p[1001][1001]; 
int main(){
	scanf("%d", &T);
	while (T--){
		memset(dp, 0x3f, sizeof(dp));
		dp[0] = 0;
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i = n; i >= 1; i--){
			for (int j = i; j <= n; j++){
				if (i == j || (i + 1 == j && s[i] == s[j])) p[i][j] = true;
				else if (s[i] == s[j] && p[i + 1][j - 1]) p[i][j] = true;
				else p[i][j] = false;
			}
		}
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= i; j++){
				if (p[j][i]) dp[i] = min(dp[i], dp[j - 1] + 1);
			}
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}
```

~~写题解的时间比写代码的时间还长祭~~

---

## 作者：安静学习 (赞：2)

线性结构的Dp

主要是要预处理字符串中的回文子串的位置分别是哪里到哪里，然后dp[n]表示前n个位置的最少回文子串的个数

状态转移方程为
dp[i] = min(dp[i], dp[j]+1)//j+1到i必须是回文子串

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
string a;
const int maxn = 1000 + 10;
int s[maxn][maxn], dp[maxn];//是不是回文的判断,第i个位置的最小回文数

void init(){
    int len = a.length();
    for(int i = 0; i < len; i++){
        s[i][i] = 1;
        dp[i] = i + 1;//计算最初值,自己就是回文的最差情况
    }
    for(int i = 0; i < len; i++){//头和尾只有自己可以作为中心
        int Left = i, Right = i + 1;
        while(Left >= 0 && Right < len){//长度为偶数的回文
            if(a[Left] != a[Right]){break;}
            s[Left][Right] = 1;
            //cout << Left << ' ' << Right << endl;
            Left--;
            Right++;
        }
        Left = i - 1;
        Right = i + 1;
        while(Left >= 0 && Right < len){//奇数回文
            if(a[Left] != a[Right]){break;}
            s[Left][Right] = 1;
            //cout << Left << ' ' << Right << endl;
            Left--;
            Right++;
        }
    }
}

int main(){
    int n = 0;
    cin >> n;
    while(n--){
        cin >> a;
        memset(s, 0, sizeof(s));
        memset(dp, 0, sizeof(dp));
        init();
        int len = a.length();
        for(int i = 0; i < len; i++){
            if(s[0][i]){dp[i] = 1;}
            for(int j = 0; j < i; j++){
                if(s[j + 1][i]){//是一个回文
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
            //cout << dp[i] << endl;
        }
        printf("%d\n", dp[len - 1]);
    }
    return 0;
}

```


---

## 作者：swl3992 (赞：1)

可以定义 $d_i$ 为 $0 $ ~ $ i$ 可以划分成的最小回文串的个数。

则可以得到状态转移方程为 : $d_i = min( d_j+1 )$  前提是 $s_j+_1$~$_i$ 为回文串。

可以预处理一下 $s_j$~$_i$ 是否为回文串，方法是区间 dp 

定义 $is_{i,j}$ 为 $s_j$~$_i$ 是否为回文串。

接着先枚举长度，然后枚举起始点。

示例代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int d[1005];
string str;
int is[1005][1005];
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(is,0,sizeof(is));
        cin>>str;
        str=" "+str;	//方便后续状态转移
        int size=str.size();
        for(int len=1;len<=size;len++)	//枚举长度
        {
            for(int b=1;b+len-1<size;b++) //枚举起点
            {
                int e=b+len-1;	//终点
                if(len==1)	//长度为1，必为回文
                {
                    is[b][e]=1;
                }
                else if(len==2&&str[b]==str[e])	//长度为2且开始等于结束
                {
                    is[b][e]=1;
                }
                else if(is[b+1][e-1]&&str[b]==str[e])	//头+1和尾-1为回文，并且头尾相等
                {
                    is[b][e]=1;
                }
            }
        }
        d[0]=0;
        for(int i=1;i<size;i++)
        {
            d[i]=i;	//原本要分成i个
            for(int j=0;j<i;j++)
            {
                if(is[j+1][i])
                {
                    d[i]=min(d[i],d[j]+1);	//转移
                }
            }
        }
        cout<<d[size-1]<<endl;
    }
    return 0;
}
```


---

## 作者：xiaohuang (赞：1)

### 题意描述：

 现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。
 
### 解题思路：

p[i][j]=true表示字符串st的第i个字符到第j个字符是回文串。

p[i][j]=false表示字符串st的第i个字符到第j个字符不是回文串。

接着就可以用dp了，dp方程是f[i]=min(f[i],f[j]+1)，

条件p[j+1,i]=true。

### AC代码：

```pascal
var n,t,i,j,cas,len,mid,l,r:longint;
    p:array[0..1005,0..1005] of boolean;
    f:array[0..1005] of longint;
    st:ansistring;
function min(o1,o2:longint):longint;//求min
begin
  if o1<o2 then exit(o1) else exit(o2);
end;
begin
  readln(cas);//读入多组数据
  for t:=1 to cas do
  begin
    readln(st);
    len:=length(st);//为了方便，先把长度求出来
    fillchar(p,sizeof(p),false);//初始化p数组，令它们都不是回文串
    for i:=1 to len do
      p[i,i]:=true;//一个字符保证是回文串
    for i:=1 to len do//枚举中心点，两个指针向两边扩展，这里是奇数
    begin
      j:=1;
      while (i-j>0) and (i+j<=len) and (st[i-j]=st[i+j]) do
      begin
        p[i-j,i+j]:=true;
        inc(j);
      end;
    end;
    for i:=1 to len-1 do//枚举中心点，两个指针向两边扩展，这里是偶数
    begin
      j:=1;
      while (i-j+1>0) and (i+j<=len) and (st[i-j+1]=st[i+j]) do
      begin
        p[i-j+1,i+j]:=true;
        inc(j);
      end;
    end;
    fillchar(f,sizeof(f),1);//把f数组初始化成最大值
    f[0]:=0;
    for i:=1 to len do//开始dp
      for j:=0 to i-1 do
        if p[j+1,i] then f[i]:=min(f[i],f[j]+1);//调用dp方程
    writeln(f[len]);//输出
  end;
end.
```

---

## 作者：昤昽 (赞：1)

[Partitioning by Palindromes[UVa11584]](https://www.luogu.org/problemnew/show/UVA11584#sub)

字符串长度往往可以当做Dp顺序.按照"从左到右"的顺序,可以得到Dp方程:
f[i]=f[j]+1|(j+1,i)是回文串

判断某一个子串是否是回文串可以利用Dp,同样可以利用字符串长度作为DP顺序:
is_pali[i][j]=(s[i] == s[j] && is_pali[i+1][j-1]);


```
#include <cstdio>
#include <cstring>
const int maxn=1000+1+1;
char s[maxn];
int f[maxn],is_pali[maxn][maxn];
inline int min(const int& a,const int& b)
{
	return a<b?a:b;
}
int main()
{
	
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(s,0,sizeof(s));
		memset(f,0,sizeof(f));
		memset(is_pali,0,sizeof(is_pali));
		
		scanf("%s",s+1);
		const int n=strlen(s+1);
		
		for(int i=0;i<=n;i++)is_pali[i+1][i]=is_pali[i][i]=true;
        //"空串"与单个字符都为回文串
		for(int l=2;l<=n;l++)
			for(int i=1;i<=n-l+1;i++)
				is_pali[i][i+l-1]=(s[i]==s[i+l-1] && is_pali[i+1][(i+l-1)-1]);
//Dp判断是否为回文串:is_pali[i][j]=(s[i] == s[j] && is_pali[i+1][j-1]),注意这个方程中"长区间依赖于短区间",因此应该按照区间长短的顺序Dp
		for(int i=0;i<=n;i++)f[i]=i;
		
		for(int i=1;i<=n;i++)
			for(int j=i-1;j>=0;j--)
				if(is_pali[j+1][i])f[i]=min(f[i],f[j]+1);
		
		printf("%d\n",f[n]);
        //if(T)printf("\n");
        //UVa坑爹评测,,,最后一行不加换行会判错
	}
	return 0;
}
```

---

## 作者：Y_J_Y (赞：1)

很明显
看到了紫书上的dp题
又迫不及待的来打代码了
但是一片wrong
## （因此想发一篇小题解安慰我幼小的心灵）

------------
但是我在看了很多篇之后，
## 发现大佬们大都为n^2
## 那我只好打一打我的mid之判断了
# 希望能给您们点想法（虽然速度不一定快）

太菜勿喷

```c
毫无疑问
一道dp题
当然
前面大佬们的dp方程
是正确（毫无疑问）

#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
int t;
char s[10000];
int d[2000];
int hw[2000][2000];
int panduan(int l,int r) {//接下来就是判断回文了，自以为轻松易懂———l为左端点，r为右端点
	int mid=(l+r)/2;
	if((r-l)%2==1) {//不是长度为偶数的串，不包括单个，单个在下面判断
		int a=mid,b=mid+1;
		while(1) {
			//cout<<s[a]<<" "<<s[b]<<endl;
			if(a<l||b>r) {
				return 1;
			}
			if(s[a]!=s[b]) {
				return false;
			}
			a--,b++;
		}
	}
	else {//长度为偶数的串，包括一个的
		int a=mid-1,b=mid+1;
		while(1) {
			if(a<l||b>r) {
				return 1;
			}
			if(s[a]!=s[b]) {
				return false;
			}
			a--,b++;
		}
	}
}
int main() {
	//cin>>s;
	//cout<<panduan(0,1)<<endl; 
	scanf("%d",&t);
	while(t--) {
		memset(s,0,sizeof(0));//注意要请空
		memset(d,0,sizeof(0));
		scanf("%s",s);
		//cout<<panduan(0,1)<<endl;
	//	cout<<endl;
		for(int i=0;i<=strlen(s)-1;i++) {//如果自己单个为回文（最坏情况）
			hw[i][i]=1;
			d[i]=i+1;
		}
		for(int i=0;i<=strlen(s)-1;i++) {
			for(int j=i;j<=strlen(s)-1;j++) {
				hw[i][j]=panduan(i,j);
				hw[j][i]=hw[i][j];
				//cout<<hw[i][j]<<" ";
			}
			//cout<<endl;
		}
		for(int i=0;i<=strlen(s)-1;i++)//dp方程，相信大佬们都讲得很清楚了 {
			if(hw[0][i]) {
				d[i]=1;
			}
			for(int j=0;j<i;j++) {
				if(hw[j+1][i]==1) {
					d[i]=min(d[j]+1,d[i]);
					//cout<<i<<" "<<d[i]<<endl;
				}
			}
		}
		printf("%d\n",d[strlen(s)-1]);
	}
	return 0;
}
```
希望能过啊

期待中——————

---

## 作者：Dream_It_Possible (赞：1)

**此题是一道经典的动态规划。**

且是一类动规的代表题————回文串DP

我们设b[i][j]表示从i到j是不是回文串，是为1，不是为0.

我们设f[i]表示前i个字符分割的回文子串的最少个数。

则有转移方程：
### _**f[i]=min(f[i],f[j-1]+1);**_ 

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
char s[1005];
bool b[1005][1005];
int f[1005];
int main()
{
	freopen("palind.in","r",stdin);
	freopen("palind.out","w",stdout);
	int t,n,i,j;
	cin>>t;
	while (t--)
	{
		memset(b,0,sizeof(b)); //每次做完清空
        memset(f,0,sizeof(f)); //每次做完清空
		scanf("%s",s+1);
		n=strlen(s+1);
		for (i=1;i<=n;i++)
		{
			b[i][i]=1;//字母本身就是一个回文串
			if (s[i]==s[i+1])
			b[i][i+1]=1;//判断当前字母和后一个字母是否是回文串
		}
		for (i=n;i>=1;i--)
		{
			for (j=i+1;j<=n;j++)
			{
				if (s[i]==s[j]&&b[i+1][j-1]==1)
				b[i][j]=1;//判断出所有的回文串
			}
		}
		for (i=1;i<=n;i++)
		{
			f[i]=i;
			for (j=i;j>=1;j--)
			{
				if (b[j][i]==1)
				{
					f[i]=min(f[i],f[j-1]+1);//动规
				}
			}
		}
		cout<<f[n]<<endl;
	}
	return 0;
}
```

---

## 作者：Jeremiahy (赞：0)

## 分析

考虑 dp。设 $d_i$ 为字符 $1$ 到 $i$ 划分成的最小回文串的个数，$S$ 为回文串集合，则状态转移方程为：

$$d_i=\min\{d_j+1|s_{j+1\sim i}\in S\}$$

最后的答案为 $d_{|s|}$。

注意频繁的要判断回文串。状态 $O(n)$ 个，决策 $O(n)$ 个，如果每次转移都需要 $O(n)$ 的时间判断，总时间复杂度会达到 $O(n^3)$。然而……可以过啊。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, dp[1005];
string s;
bool is_palindrome(int l, int r) { //O(n)判断回文
	bool flag = 1;
	while (l < r)
		if (s[l] == s[r])
			l++, r--;
		else {
			flag = 0;
			break;
		}
	return flag;
}
signed main() {
    cin >> t;
    while (t--) {
    	cin >> s;
    	dp[1] = 1;
    	for (int i = 2; i <= s.size(); i++) {
    		dp[i] = dp[i - 1] + 1;//先设自己单独成一个
    		for (int j = 1; j <= i; j++)
    			if(is_palindrome(j - 1, i - 1))//因为s字符串是从 0 开始存储的，所以减1
    				dp[i] = min(dp[i], dp[j-1] + 1);
    	}
    	cout << dp[s.size()] << '\n';
    }
    return 0;
}
```

当然，也可以先用 $O(n^2)$ 的时间预处理回文串。方法是枚举中心，然后不断向左右延伸并且标记当前子串是回文串，直到延伸的左右字符不同为止。这样一来，每次转移的时间降为了 $O(1)$，总时间复杂度为 $O(n^2)$。

当然也可以使用动态规划预处理回文串。

注：本文参照刘汝佳大神的紫书。


---

## 作者：Otue (赞：0)

### 思路
我们可以定义 $dp[i]$ 为字符串第 $0$ 位到第 $i$ 位至少分为的回文串个数。

定义 $b[i][j]$ 表示字符串第 $i$ 位到第 $j$ 位是否回文。

那么状态转移方程为：

当 $b[i][j]=1$ 时，$dp[j]=\min(dp[j],dp[i-1]+1)$

答案即 $dp[N-1]$ ( $N$ 表示字符串位数)。

但是这样做很慢，复杂度为 $O(n^3)$ 。
### 优化方法
从中间开始枚举，然后不断向左右延伸并且标记当前子串是回文串，知道延伸左右字符不同为止。这样一来，每次转移时间变成了 $O(1)$ ，总复杂度为  $O(n^2)$。
### 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int n;
int dp[1005];
bool b[1005][1005];
int main(){
    cin>>t;
    while(t--){
        cin>>s;
        n=s.size();
        memset(b,0,sizeof(b));
        for(int i=0;i<=n-1;i++)dp[i]=INT_MAX;
        for(int j=0;j<=n-1;j++){
        	for(int i=0;i<=j;i++){
	            if(s[i]==s[j]&&(j-i<=1||b[i+1][j-1])){
	                b[i][j]=1;
	                if(j==0)dp[j]=1;
	                else dp[j]=min(dp[j],dp[i-1]+1);
	            }
        	}
		}
        cout<<dp[n-1]<<endl;  
    }
}
```

---

## 作者：fanfansann (赞：0)

整理的算法模板合集： [***ACM模板***](https://fanfansann.blog.csdn.net/article/details/105493218)

---

依旧是线性DP


我们使用闫氏DP分析法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201015174043674.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_8,color_FFFFFF,t_70#pic_center)
总体DP转移的时间复杂度为$O(n^2)$。
但是这里牵扯到判断 $\tt i$ 到 $\tt j$ 是否为回文串，普通的判断为$O(n)$，那么组合到一块循环的话总体的时间复杂度就变成了$O(n^3)$，这是我们不能接受的，所以考虑使用DP预处理字符串S中任意两点i到j之间是否为回文串，可以用一个 $\tt bool$ 型的数组`f[i][j]`表示 $\tt i$ 到 $\tt j$ 之间是否为回文串。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201015174413880.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_8,color_FFFFFF,t_70#pic_center)

最后给出优美的代码，全程DP递推，别忘了初始化～
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;
const int N = 5007, M = 5000007, INF = 0x3f3f3f3f;

string s, ss;
bool f[N][N];
int p[N];
int t;

void init()
{
    memset(f, 0, sizeof f);
    memset(p, 0, sizeof p);
}

void hwjudge(int n)
{
    for(int i = 1; i <= n; ++ i){
        f[i][i] = true;
        f[i - 1][i] = (s[i - 1] == s[i]);
    }

    for(int j = 2; j <= n; ++ j){//右
        for(int i = 1; i < j - 1; ++ i){//左(要枚举长度大于等于3的子串1,2已经算过了)
            if(s[i] == s[j]){
                f[i][j] = f[i + 1][j - 1];
            }
            else f[i][j] = false;
        }
    }
}

void solve()
{
    cin >> ss;
    s = " " + ss;//习惯从1开始
    int n = s.length() - 1;

    hwjudge(n);//DP,O(n^2)预处理回文串

    for(int i = 1; i <= n; ++ i){
        p[i] = p[i - 1] + 1;
        for(int j = 1; j < i; ++ j){
            if(f[j][i])
                p[i] = min(p[i], p[j - 1] + 1);
        }
    }
    printf("%d\n", p[n]);
    return ;
}

int main()
{
    scanf("%d", &t);
    while(t -- ){
        init();
        solve();
    }
    return 0;
}

```


---

## 作者：argpath (赞：0)

##### Uva 11584 划分成回文串 - 题解

- 假设现在我们已经知道$\forall [i,j], S_i\sim S_j$这个区间是不是回文串。
- 考虑状态的定义。状态最简化的方案是定义$f[i]$表示考虑当前$i$位的时候划分出来的回文串个数。
- 那么考虑转移，我们发现如果枚举$j$，如果$j\sim i(j\leq i )$是回文串，那么就可以在$j$的地方分开成为两个回文串。那么这时候$f[i] = f[j-1]+1$.
- 初始条件就是$f[i] = i$.
- 求解$S_i\sim S_j$是不是回文串：
  - 观察发现回文串有长度为1为中心的和长度为2作为中心的。
  - 直接枚举中心情况，再根据两边的情况往上加就行了。
- 注意细节：
  - 数组开大
  - 边界条件
  - 隐藏陷阱：注意段数的定义。如果要划分在第一段，那么段数就直接是1.

代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
int hw[1055][1055];//数组稍微开大点。
int f[1055];
int solve(){
	string s;cin>>s;
	s = "0"+s;// 从1开始下标
	int n = (int)s.size()-1;
	for(int i=1;i<=n;i++){
		hw[i][i] = 1;
	}
    //预处理s[i...j]的回文串
	for(int i=1;i<n;i++){
		if(s[i]==s[i+1]) {hw[i][i+1] = 1;}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=min(i-1,n-i);j++){
			if(s[i-j] == s[i+j]) {hw[i-j][i+j] = 1;}
			else break;
		}
	}
	for(int i = 1;i<=n;i++){
		if(s[i] == s[i+1]){
			for(int j = 1;j<=min(i-1,n-i-1);j++){
				if(s[i-j] == s[i+1+j]){hw[i-j][i+1+j] = 1;}
				else break;
			}
		}
	}
	f[1] = 1;
	for(int i = 1;i<=n;i++){
		f[i] = i;
	}
    //进行DP。
	for(int i = 1;i<=n;i++){
		for(int j = i;j>=0;j--){
			if(hw[j][i]){f[i] =min(f[i],f[j-1]+1) ;if(j==0) f[i] = 1;/*注意这里的陷阱。*/}
		}
	}
	cout<<f[n];
	return 0;
}
int main(){
	int T;cin>>T;
	while(T--) {memset(hw,0,sizeof hw);memset(f,0,sizeof f);solve();}
	return 0;
}
```



---

## 作者：TheShadow (赞：0)

# 闲扯

这道题不是一个字符串 $hash$ 的题吗，为啥题解全部都是区间 $DP$ 求回文串。。。

# 题面

[UVA11584 划分成回文串 Partitioning by Palindromes](https://www.luogu.org/problem/UVA11584)

# Solution

我们先不考虑回文串的问题，考虑怎么求解这个问题。

显然，我们设 $dp_i$ 表示前 $i$ 位最少能被划分为几个回文串，那么很容易写出以下方程： $dp_i=\min\limits_{j=0,check(j+1,i)}^{i-1}(dp_j+1)$ 。其中 $check(l,r)$ 表示 $l\sim r$ 是一个回文串。

那么我们只需要求出每一个子段是不是一个回文串即可。

其他题解都是用的区间 $DP$ 来求解，~~或者直接暴力判~~，然而我们是可以在 $O(n)$ 的时间复杂度里处理出来的。

我们考虑**字符串 $hash$** 。

对一个字符串，我们正向求一遍 $hash$ ，反向求一遍 $hash$ 。（不会的同学可以去做一下模板题）

查询时，我们计算出这一段正向的 $hash$ 值和反向的 $hash$ 值，判断是否相等即可。

时间复杂度： $O(n^2)$ 。

空间复杂度： $O(n)$ 。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e3+5;
int T,len,dp[MAXN];
char s[MAXN];
unsigned ll h1[MAXN],h2[MAXN],p[MAXN],x,y;
it min(int x,int y){return x<y?x:y;}
it check(int l,int r){
	x=h1[r]-h1[l-1]*p[r-l+1];
	y=h2[l]-h2[r+1]*p[r-l+1];
	return x==y;
}
il solve(){
	scanf("%s",s+1);len=strlen(s+1),del(dp,0x3f),dp[0]=0;
	for(ri i=1;i<=len;++i) h1[i]=h1[i-1]*131+s[i]-'a'+1;
	for(ri i=len;i;--i) h2[i]=h2[i+1]*131+s[i]-'a'+1;
	for(ri i=1;i<=len;++i)
		for(ri j=0;j<i;++j)
			if(check(j+1,i))
				dp[i]=min(dp[i],dp[j]+1);
	print(dp[len]),puts("");
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T),p[0]=1;
	for(ri i=1;i<=1000;++i) p[i]=p[i-1]*131;
	for(ri i=1;i<=T;++i) solve();
	return 0;
}
```

# 总结

感觉大家都是看刘汝佳的蓝书过来的。。。

也不能只有区间 $DP$ 一种做法对吧，还是拓展一下思路好些。

---

## 作者：Zroom (赞：0)

~~转移方程很简单。~~
f[i]表示到i为止的最少回文串
因为最优子结构性，所以再加一个字符，就要判断，之前的最优解f[i-1]跟f[i]比较，在运算过程中f[i]只是暂存目前最优。


------------

还有一个任务要求出从i到j是不是字符串。在代码中有写
```cpp
scanf("%s", s + 1);//下面要用到字符的第一位跟前一位比较，从1开始方便初始化，c++没有负数数组。
        s[0] = '0';//填上第一位，如果不填strlen算出长度就是0
        int len = strlen(s)-1;
        memset(sum,0,sizeof(sum));//多组数据要初始化。
        //求sum有三种情况
        for(int i=1; i <= len; i++)
        {
            int j,k;
            sum[i][i]=1;//每个单独的字符是回文串
            for(j =i, k = i+1 ; j >= 1 && k <= len ; j--, k++)
            {//如果是偶数个的回文串
                if(s[j] == s[k] )
                {
                    if(j+1<=k-1 && sum[j+1][k-1])//不能j+1，k-1后j跑到k前面去了
                    sum[j][k]=1;
                    if(k-j==1)//如果只相差1就是两个相邻的字符
                    sum[j][k]=1;
                }

               //if(sum[j][k]) cout<<j<<"->"<<k<<" "<<sum[j][k]<<endl;
            }
            for(j = k = i ; j >= 1 && k <= len ; j--, k++)
            {//如果是奇数的回文串
                if(s[j] == s[k] &&k!=j && sum[j+1][k-1])
                {
                    sum[j][k]=1;
                }
               //if(sum[j][k]) cout<<j<<"->"<<k<<" "<<sum[j][k]<<endl;
            }
        }
```


------------
判断是否为回文串还可以动态判断
```cpp
bool is_palindrome(int i,int j){
    if(i>j) return 1;
    if(s[i] != s[j]) return 0;

    if(vis[i][j] == kase) return p[i][j];
    vis[i][j] = kase;
    p[i][j] = is_palindrome(i+1,j-1);
    return p[i][j];
}
```


------------

```
        memset(f,12,sizeof(f));//初始化为无穷大
        f[0]=0;//方便更新状态
        for(int i=1;i<=len;i++)
        {
            for(int j=1;j<=i;j++)
            if(sum[j][i])f[i]=min(f[i],f[j-1]+1);
        }
        cout<<f[len]<<endl;;
```


---

