# Nice Garland

## 题目描述

You have a garland consisting of $ n $ lamps. Each lamp is colored red, green or blue. The color of the $ i $ -th lamp is $ s_i $ ('R', 'G' and 'B' — colors of lamps in the garland).

You have to recolor some lamps in this garland (recoloring a lamp means changing its initial color to another) in such a way that the obtained garland is nice.

A garland is called nice if any two lamps of the same color have distance divisible by three between them. I.e. if the obtained garland is $ t $ , then for each $ i, j $ such that $ t_i = t_j $ should be satisfied $ |i-j|~ mod~ 3 = 0 $ . The value $ |x| $ means absolute value of $ x $ , the operation $ x~ mod~ y $ means remainder of $ x $ when divided by $ y $ .

For example, the following garlands are nice: "RGBRGBRG", "GB", "R", "GRBGRBG", "BRGBRGB". The following garlands are not nice: "RR", "RGBG".

Among all ways to recolor the initial garland to make it nice you have to choose one with the minimum number of recolored lamps. If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
3
BRB
```

### 输出

```
1
GRB
```

## 样例 #2

### 输入

```
7
RGBGRBB
```

### 输出

```
3
RGBRGBR
```

# 题解

## 作者：MattL (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF1108C) & [原题链接](http://codeforces.com/problemset/problem/1108/C)

---

**分析题意：**

首先，我们先来看洛谷给的题目翻译：

给定一个长度为 $N$ 的字符串（只包含'R','G','B'），修改最少的字符，使字符串满足当 $s[i]=s[j]$ 时必有 $i \equiv j\pmod{3}$

其实就是所有 $\bmod3$ 为一个数时，字符一样

也就是最终字符串一定是以一个长度为三的字符串自我复制（循环）得到的。（没有重复）

我们用样例来验证一下：

样例一输出：
```GRB```

这个没啥好说的，没有规律。

样例2输出：
```RGBRGBR```

这个输出是由 ```RGB``` 不断自我复制得到的。

---

**代码思路：**

首先，字符串只有三个字符，长度为三且没有重复的字符串只有六个：

```
RGB
RBG
BRG
BGR
GBR
GRB
```
我们只需枚举是哪种字符串即可，然后累加不同的字符，再求最小值。

代码时间复杂度： $\Theta (6n)$

---

**代码实现：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=INT_MAX,cnt,ansi;
string s,mb[]={"RGB","RBG","BRG","BGR","GBR","GRB"};
int main()
{
	cin>>n>>s;
	for(int u=0;u<6;u++)//枚举是那种字符串循环得到的
	{
		cnt=0;
		for(int i=0;i<s.size();i++)
			cnt+=(s[i]!=mb[u][i%3]);//累加不同字符的个数
		if(cnt<ans)
			ans=cnt,ansi=u;//更新答案，记得记录是那种字符串
	}
	cout<<ans<<endl;
	for(int i=0;i<s.size();i++)
		cout<<mb[ansi][i%3];//循环输出目标字符串
	return 0;
}
```

---

## 作者：zsc2003 (赞：2)

因为一共只有```R```,```G```,```B```三种字母

因为相同的一定隔了3个

所以变化后的字串一定是循环的

并且循环的情况一共只有$3!=6$种

所以只需要对$RGB$的全排列每个都O(n)扫一遍统计个数即可

所以总体复杂度$=O(3!n)=O(6n)=O(n)$


下面附上蒟蒻的代码

(蒟蒻因为过菜所以重复部分都是复制的,导致代码量过长......)
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=200010;
int l,ans1,ans2,ans3,ans4,ans5,ans6,t,x,ans;
char s[N];
int main()
{
	l=read();
	t=l/3;
	x=t*3;
	scanf("%s",s+1);
	for(int i=1;i<=t;i++)//RGB  1
	{
		if(s[i*3-2]!='R')ans1++;
		if(s[i*3-1]!='G')ans1++;
		if(s[i*3]!='B')ans1++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='R')ans1++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='R')ans1++;
			if(s[l]!='G')ans1++;
		}
	}
//--------------------------------------------
	for(int i=1;i<=t;i++)//RBG  2
	{
		if(s[i*3-2]!='R')ans2++;
		if(s[i*3-1]!='B')ans2++;
		if(s[i*3]!='G')ans2++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='R')ans2++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='R')ans2++;
			if(s[l]!='B')ans2++;
		}
	}
//--------------------------------------------
	for(int i=1;i<=t;i++)//BGR  3
	{
		if(s[i*3-2]!='B')ans3++;
		if(s[i*3-1]!='G')ans3++;
		if(s[i*3]!='R')ans3++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='B')ans3++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='B')ans3++;
			if(s[l]!='G')ans3++;
		}
	}	
//--------------------------------------------
	for(int i=1;i<=t;i++)//BRG  4
	{
		if(s[i*3-2]!='B')ans4++;
		if(s[i*3-1]!='R')ans4++;
		if(s[i*3]!='G')ans4++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='B')ans4++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='B')ans4++;
			if(s[l]!='R')ans4++;
		}
	}
//--------------------------------------------
	for(int i=1;i<=t;i++)//GBR  5
	{
		if(s[i*3-2]!='G')ans5++;
		if(s[i*3-1]!='B')ans5++;
		if(s[i*3]!='R')ans5++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='G')ans5++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='G')ans5++;
			if(s[l]!='B')ans5++;
		}
	}	
//--------------------------------------------
	for(int i=1;i<=t;i++)//GRB  6
	{
		if(s[i*3-2]!='G')ans6++;
		if(s[i*3-1]!='R')ans6++;
		if(s[i*3]!='B')ans6++;
	}
	if(l-x!=0)
	{
		if(l-x==1)
		{
			if(s[l]!='G')ans6++;
		}
		if(l-x==2)
		{
			if(s[l-1]!='G')ans6++;
			if(s[l]!='R')ans6++;
		}
	}		
	ans=min(min(min(ans1,ans2),min(ans3,ans4)),min(ans5,ans6));
	printf("%d\n",ans);
	if(ans==ans1)
	{
		for(int i=1;i<=t;i++)
			printf("RGB");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("R");
			}
			if(l-x==2)
			{
				printf("RG");
			}
		}
		return 0;
	}
	if(ans==ans2)
	{
		for(int i=1;i<=t;i++)
			printf("RBG");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("R");
			}
			if(l-x==2)
			{
				printf("RB");
			}
		}
		return 0;
	}
	if(ans==ans3)
	{
		for(int i=1;i<=t;i++)
			printf("BGR");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("B");
			}
			if(l-x==2)
			{
				printf("BG");
			}
		}
		return 0;
	}
	if(ans==ans4)
	{
		for(int i=1;i<=t;i++)
			printf("BRG");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("B");
			}
			if(l-x==2)
			{
				printf("BR");
			}
		}
		return 0;
	}
	if(ans==ans5)
	{
		for(int i=1;i<=t;i++)
			printf("GBR");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("G");
			}
			if(l-x==2)
			{
				printf("GB");
			}
		}
		return 0;
	}
	if(ans==ans6)
	{
		for(int i=1;i<=t;i++)
			printf("GRB");
		if(l-x!=0)
		{
			if(l-x==1)
			{
				printf("G");
			}
			if(l-x==2)
			{
				printf("GR");
			}
		}
		return 0;
	}
	return 0;
}
```

---

## 作者：yzx4188 (赞：0)

# 一道纯暴力搜索题

这一题的中文翻译有点迷惑，但是具体意思就是要求按照 "RGB","RBG","GRB","GBR","BRG"和"BGR"这六种循环节来不断的循环

例如:

"RGBRGBRG"

"BRGBRGBRGBRG"

所以我们只需要六种情况都看一遍，看一看那种需要修改的字符最少，然后就取这种情况就行了

此时的时间复杂度为 $O(6n)$ ,数据范围在 $2\times10^5$ ,不会炸

### CODE(个人认为还是比较短的):
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[202020];
int cnt[6];//统计每一种情况需要修改多少个字符
int mi=0x7fffffff,minn;//用来记录修改字符最少的数量和情况
char ans[6][202020];//直接记录修改后字符串

char f[6][3]={//将每一种循环节都枚举出来，方便枚举
	'R','G','B',
	'R','B','G',
	'G','R','B',
	'G','B','R',
	'B','R','G',
	'B','G','R',
}; 

int main(){
	cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<6;i++){//按照循环节来枚举
    	for(int j=0;j<n;j+=3){//因为循环节是固定的所以可以每次看三位
	        if(a[j]!=f[i][0])//比较第一位，如果和这种情况下应该出现的字符没有出现，就记录它是错误的
    	        cnt[i]++;
        	if(a[j+1]!=f[i][1]&&j+1<n)//比较第二位
            	cnt[i]++;
	        if(a[j+2]!=f[i][2]&&j+2<n)//比较第三位
        	    cnt[i]++;
        	ans[i][j]=f[i][0];//记录这种情况下的最终字符串，不管用不用得上
        	ans[i][j+1]=f[i][1];
        	ans[i][j+2]=f[i][2];
    	}
    	if(mi>cnt[i]){//更新修改最少的字符的数量和情况
    		mi=cnt[i];
    		minn=i;
		}
	}	
    cout<<cnt[minn]<<endl;//输出
    for(int i=0;i<n;i++)
		cout<<ans[minn][i];
	return false;//撒花！！！
} 

```

---

## 作者：wwldx (赞：0)

暴力出奇迹，由题意知道，最后肯定是每三位一循环，既然是3个3个循环，那么最后肯定是RGBRGB这样的，那么还有其他可能吗，当然，还有可能GBR,BRG,RBG,BGR,GBR，一共就这6种情况，你全都比较一遍，找到最小的不就行了吗，并且只要列出其中一种比较情况，其他5种基本上都是复制粘贴，
具体可以见代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int num1[3]={1,2,3};
int num3[3]={1,3,2};
char num2[3]={'R','G','B'};//一共6组，这可以代表其中3组，RGB，GBR，BRG ```c
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int num1[3]={1,2,3};
int num3[3]={1,3,2};
char num2[3]={'R','G','B'};//一共6组，这可以代表其中3组，RGB，GBR，BRG 
char num4[3]={'R','B','G'};//剩下3组，RBG，BGR，GRB 
int s1,s2,s3,s4,s5,s6;//分别代表各种情况的更改次数，初始都是0 
int l1=0,l2=1,l3=2,l4=0,l5=1,l6=2;//l1是第一组RGB,从0开始跑，也就是按照RGBRGB的顺序跑
//同理,l2是从G开始跑,l2就是GBRGBR,l3就是BRGBRG,l4就是RBGRBG,l5就是 BGRBGR,l6就是GRBGRB 
char q;
//123 132 231 213 321 312
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>q;
		switch(q)//将字符转化,R->1,G->2,B->3,方便处理 
		{
			case'R':{
				a[i]=1;
				break;
			}
			case'G':{
				a[i]=2;
				break;
			}
			case'B':{
				a[i]=3;
				break;
			}
		}
		if(a[i]!=num1[l1++])//如果这一位跟GRB的顺序不同,s1++ 
		s1++;
		if(a[i]!=num1[l2++])//如果这一位跟GBR的顺序不同,s2++ 
		s2++;
		if(a[i]!=num1[l3++])//以下同理，复制粘贴即可 
		s3++;
		if(a[i]!=num3[l4++])
		s4++;
		if(a[i]!=num3[l5++])
		s5++;
		if(a[i]!=num3[l6++])
		s6++;
		l1%=3,l2%=3,l3%=3,l4%=3,l5%=3,l6%=3;//每过3位，归零，对3取余即可 
	}
	int qwe=min(min(s1,min(s4,s5)),min(min(s2,s6),s3));//找到修改次数最小的情况 
	cout<<qwe<<"\n";//输出次数 
	int flag=1;//假如flag是1的话，使用num2数组输出，默认是1，假如flag变为0，改为使用num4数组输出 
	if(qwe==s1)
	l1=0;
	else
	if(qwe==s2)
	l1=1;
	else
	if(qwe==s3)
	l1=2;
	else
	{
		flag=0;//改为num4数组输出，flag更改为0 
		if(qwe==s4)
		l1=0;
		else
		if(qwe==s5)
		l1=1;
		else
		l1=2;
	}
	if(flag)//判断flag 
	for(int i=1;i<=n;i++)
	{
		cout<<num2[l1++];
		if(l1==3)
		l1-=3;
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			cout<<num4[l1++];
			if(l1==3)
			l1-=3;
		}
	}
	cout<<"\n";
	return 0;
}
```


---

## 作者：_louhc (赞：0)

# 思路

我们可以想到，要满足条件，必须要有$s[0]\ne s[1]\ne s[2]$，$s[i]=s[i\% 3]$（很好理解吧？）

所以$s[0],s[1],s[2]$分别选取$'R','G','B'$（可打乱顺序），这可以用全排列解决；然后处理出要修改的个数，记录最优答案即可。时间复杂度为$O(3!\times n)$，稳得很。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Re register
#define MAXN 200005

int N;
char s[MAXN], cur[MAXN], ans[MAXN];
int res(INT_MAX);
int m[] = { 1, 2, 3 };
char a1, a2, a3;

int main(){
	scanf( "%d", &N );
	scanf( "%s", s );
	do{
		int c(0);
		a1 = m[0] == 1 ? 'R' : ( m[0] == 2 ? 'G' : 'B' );
		a2 = m[1] == 1 ? 'R' : ( m[1] == 2 ? 'G' : 'B' );
		a3 = m[2] == 1 ? 'R' : ( m[2] == 2 ? 'G' : 'B' );
		for ( int i = 0; i < N; i += 3 ){ cur[i] = a1; if ( s[i] != a1 ) c++; }
		for ( int i = 1; i < N; i += 3 ){ cur[i] = a2; if ( s[i] != a2 ) c++; }
		for ( int i = 2; i < N; i += 3 ){ cur[i] = a3; if ( s[i] != a3 ) c++; }
		if ( c < res ){ res = c; memcpy( ans, cur, sizeof ans ); }
	}while( next_permutation( m, m + 3 ) );
	printf( "%d\n%s\n", res, ans );
	return 0;
}

```



---

## 作者：Zechariah (赞：0)

暴搜  
考虑到最终的字符串是每三个一组，每组完全相同，我们可以搜出每一组的所有情况（也就是全排列），然后取修改最少的那一种  
复杂度3!\*n,完全可过
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
char s[N], base[4], tmp[4];
bool flag[N];
int minn = 1e9, n;
void dfs(rg int step)
{
    if (step > 3)
    {
        rg int sum = 0;
        for (rg int i = 1; i <= n; ++i)
            if (s[i] != base[(i - 1) % 3 + 1])
                ++sum;
        if (sum < minn)memcpy(tmp, base, sizeof(tmp)), minn = sum;
        return;
    }
    if (!flag['G'])
    {
        flag['G'] = true;
        base[step] = 'G';
        dfs(step + 1);
        flag['G'] = false;
    }
    if (!flag['B'])
    {
        flag['B'] = true;
        base[step] = 'B';
        dfs(step + 1);
        flag['B'] = false;
    }
    if (!flag['R'])
    {
        flag['R'] = true;
        base[step] = 'R';
        dfs(step + 1);
        flag['R'] = false;
    }
}

int main(void)
{
    n = fast_IO::read();
    scanf("%s", s + 1);
    dfs(1); fast_IO::write(minn); putchar('\n');
    for (rg int i = 1; i <= n; ++i)putchar(tmp[(i - 1) % 3 + 1]);
    return 0;
}

```

---

## 作者：fsy_juruo (赞：0)

## CF1108C 【Nice Garland】题解

### 题意：

你有一个由 $n$ 个灯组成的的花环。（这不应该叫灯环么...）

每盏灯都被染成了红，绿，蓝三色之一。

你需要重新染色，是这个花环成为一个“好花环”。

好花环的定义：对于**任意**两盏颜色相同的灯，记这两盏灯的序号为 $i$ 和 $j$, 都满足$| i - j | \; mod \; 3 = 0$, 那么这一个花环就是好花环。

比如说，下面这些就是好花环：

```RGBRGBRG```, ```GB```, ```R```, ``GRBGRBG``, ``BRGBRGB``

但是这些花环不是：

``RGBG`` (第 $2$ 盏灯与第 $4$ 盏灯不符合条件)

``BGRBGRBGRBGRBGG`` (最后两盏灯不符合条件)

求最少要重新染色的灯数，并且给出方案。

### 解析：

重新审视“好花环”的定义，可以发现：

好花环一定是由一个 **长度为 3 的字母互不相同的RGB序列** $s$ 不断循环，最后加上这个 RGB序列的前缀得到的。

比如说：

```RGBRGB``` （$s$ 序列是 RGB）

```BGRBGRB``` （$s$ 序列是 BGR，加上 $s$ 的前缀 $B$）

而且 $s$ 只有 $3! = 6$ 种可能，枚举 $s$, 计算不同字符数，找出最优的答案即可。

### 代码：

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
char col[3] = {'B', 'G', 'R'};
string bestans = "";
int main() {
	int n;
	string origin;
	read(n);
	cin >> origin;
	int ans = 0, swaps = 2147483240;
	do{
		string anss = "";
		int cost = 0;
		_rep(i, 0, n - 1) {
			anss.push_back(col[i % 3]);
			if(origin[i] != anss[i]) cost++;
		}
		if(cost < swaps) {
			swaps = cost;
			bestans = anss;
		}
	}while(next_permutation(col, col + 3));
	
	write(swaps); putchar('\n');
	cout << bestans << endl;
	return 0;
}


```

---

## 作者：da32s1da (赞：0)

如果我们确定了前三个$a[0],a[1],a[2]$，那么$a[3]=a[0],a[4]=a[1],a[5]=a[2],a[6]=a[3]...$后面的都能确定。

于是暴枚前三个共$6$种情况，取更改次数最少的即可。
```
#include<cstdio>
const int N=2e5+50;
int n,Ans,G[3],R[3],B[3];
char s[N];
void get(int opt){
	for(int i=opt;i<n;i+=3)
	if(s[i]=='R')R[opt]++;
	else if(s[i]=='G')G[opt]++;
	else B[opt]++;
	R[opt]=(n-opt)/3+((n-opt)%3>0)-R[opt];
	G[opt]=(n-opt)/3+((n-opt)%3>0)-G[opt];
	B[opt]=(n-opt)/3+((n-opt)%3>0)-B[opt];
    //计算需要更改多少
}
void change(char a,char b,char c){
	for(int i=0;i<n;i+=3)s[i]=a;
	for(int i=1;i<n;i+=3)s[i]=b;
	for(int i=2;i<n;i+=3)s[i]=c;
}
int main(){
	scanf("%d%s",&n,s);
	for(int i=0;i<3;i++)get(i);
    //统计i%3=0,1,2的字母个数
	Ans=n;
    //以下暴枚6种情况
	if(R[0]+G[1]+B[2]<Ans){
		Ans=R[0]+G[1]+B[2];
		change('R','G','B');
	}
	if(R[0]+B[1]+G[2]<Ans){
		Ans=R[0]+B[1]+G[2];
		change('R','B','G');
	}
	if(G[0]+R[1]+B[2]<Ans){
		Ans=G[0]+R[1]+B[2];
		change('G','R','B');
	}
	if(G[0]+B[1]+R[2]<Ans){
		Ans=G[0]+B[1]+R[2];
		change('G','B','R');
	}
	if(B[0]+R[1]+G[2]<Ans){
		Ans=B[0]+R[1]+G[2];
		change('B','R','G');
	}
	if(B[0]+G[1]+R[2]<Ans){
		Ans=B[0]+G[1]+R[2];
		change('B','G','R');
	}
	printf("%d\n%s",Ans,s);
}
```

---

