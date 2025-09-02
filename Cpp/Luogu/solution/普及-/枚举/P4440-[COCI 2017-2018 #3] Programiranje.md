# [COCI 2017/2018 #3] Programiranje

## 题目描述

Little Leticija 正在准备编程考试。虽然她已经解决了很多任务，但还有一个任务尚未解决，于是她向你寻求帮助。

有一个单词 $S$ 和 $Q$ 次询问。在每次询问中，给出正整数 $A$、$B$、$C$ 和 $D$。假设单词 $X$ 由单词 $S$ 中位置 $A$ 和 $B$ 及其之间的字母组成，而单词 $Y$ 由位置 $C$ 和 $D$ 及其之间的字母组成。您需要回答是否能以某种方式**重新排列单词 $Y$ 中的字母得到单词 $X$**。

## 说明/提示

对于 $50\%$ 的测试点，有 $1\le\lvert S\rvert\le1000$ 且 $1\le Q\le1000$。

对于 $100\%$ 的测试点，有 $1\le\lvert S\rvert\le50000$，$1\le Q\le50000$，$1\le A\le B\le\lvert S\rvert$ 且 $1\le C\le D\le\lvert S\rvert$。

样例 #3 的解释：在第一次询问中，$X=\tt vovo$，$Y=\tt devo$。在第二次询问中，$X=\tt odev$，$Y=\tt devo$。

## 样例 #1

### 输入

```
kileanimal
2
2 2 7 7
1 4 6 7
```

### 输出

```
DA
NE```

## 样例 #2

### 输入

```
abababba
2
3 5 1 3
1 2 7 8
```

### 输出

```
DA
DA
```

## 样例 #3

### 输入

```
vodevovode
2
5 8 3 6
2 5 3 6
```

### 输出

```
NE
DA
```

# 题解

## 作者：06ray (赞：9)

这题就是让我们判断字符串里的两个字串所包含的每个字母的个数是否相同。 

因为子串是连续的，所以我们不难想到前缀和，利用前缀和来快速求出一个子串所包含每个字母的个数。

设 $f[i][j]$为字母$j$在1到$i$的子串出现次数,那么$f[i][j]=f[i-1][j]+(j==c[i]);$

求出前缀和后，求a到b子串出现字符j的次数为	
$f[b][j]-f[a][j-1]$

最后判断询问的两个子串所含每个字母的个数是否相同即可。

代码：
```
#include <iostream>
#include <cstring>
using namespace std;
int f[50100][30];//前缀和数组
int main()
{
	char c[50100];//字符数组
	cin>>c;
	int n=strlen(c);
	for(int i=1; i<=n; i++)//预处理出前缀和
	{
		for(int j=1; j<=26; j++)
		{
			f[i][j]=f[i-1][j];
		}
		f[i][c[i-1]-'a'+1]++;
	}
	int q;
	cin>>q;
	while(q--)
	{
		bool flag=false;
		int a,b,c,d;
		int s[30];
		cin>>a>>b>>c>>d;
		for(int i=1; i<=26; i++)
		{
			if(f[b][i]-f[a-1][i]!=f[d][i]-f[c-1][i])//如果一个字母在这两个子串出现字母不同，就说明这两个子串不符合条件
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			cout<<"NE"<<endl;
		}
		else
		{
			cout<<"DA"<<endl;
		}
	}
	return 0;
}
```






---

## 作者：Hoks (赞：4)

## 前言

[题目链接](https://www.luogu.com.cn/problem/P4440) [个人博客内食用效果更佳](https://www.luogu.com.cn/blog/Hok/solution-p4440)

------------

## 思路分析

首先，我们注意到了“如果可以以某种方式重新排列单词 $Y$ 中的字母并获得单词 $X$ ”，把这句话拆分开，我们就能得到两个条件：

$1:$ $X$ 和 $Y$ 的长度必须相同，写成代码便是：
```cpp
b-a=d-c
```
$2:$ $X$ 中包含的各类字母数必须与 $Y$ 中包含的完全相同，写成代码便是：
```cpp
for(int i='a';i<='z';i++)
    if(x[i]!=y[i])//x[i],y[i]表示X,Y中包含字母i的数量
    {
        cout<<"NE";
        flag=1;
        break;
    }
```

接着，我们发现了 $1≤| S |≤50000$ ，既 $X$ ， $Y$ 的长度可能达到 $50000$ ,再仔细看看： $1≤Q≤50000$ 。 $50000$ 个询问，所以综上得出求字母数的函数必须极为迅速（~~这不废话吗~~）

又由于题目并没有限制字母的顺序相同，所以自然而然的就想到了前缀和，只需要用前缀和把每一个字母到位置 $i$ 出现的个数都统计下来就行了：
```cpp
for(int i=0;i<n;i++)//枚举位置
    for(int j='a';j<='z';j++)//枚举每种字母
        b[i][j]=b[i-1][j]+((int)a[i]==j);//b数组就是前缀和,a是原字符串
```

那到此为止，我们就把本题最主要的问题都解决了。

## 代码

只需要把之前的东西都串联起来，再加上一些基本输入输出就行了（无注释版本！）。
```cpp
#include<bits/extc++.h>
#define int long long
using namespace std;
string a;
int n,m;
int b[50010][151];
int read()
{
    char c=getchar();int x=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
signed main()
{
    cin>>a;n=a.size();
    m=read();
    for(int i=0;i<n;i++)
        for(int j='a';j<='z';j++)
            b[i][j]=b[i-1][j]+((int)a[i]==j);
    for(int i=1;i<=m;i++)
    {
        int flag=0,x=read()-1,y=read()-1,z=read()-1,k=read()-1;
        if(y-x!=k-z){cout<<"NE"<<endl;continue;}
        for(int i='a';i<='z';i++)
            if(b[y][i]-b[x-1][i]!=b[k][i]-b[z-1][i])
                {cout<<"NE"<<endl;flag=1;break;}
        if(!flag) cout<<"DA"<<endl;
    }
    return 0;
}
```

完结撒花 $(*^▽^*)$

---

## 作者：weak_ddb (赞：4)

## 废话不说，直接开始 

我们重新排列后要使两个字符串相等，我们只要让他们的$a$到$z$中的各个字母的个数相同就可以。

前缀和$a[i][j](j<=26)$表示从$1$到$i$，字母$j$出现的次数。每次循环$i$位置上的字母$+1$，其他的字母不变。

利用容斥原理我们可以推出$s(l,r)$=$sum[r]-sum[l-1]$其中s(l,r)为$l$到$r$数字总和，$sum[i]$为$1-i$的总和。
```
#include<bits/stdc++.h>
using namespace std;
int z[50005][30];//前缀和
char s[50005],ce;
int n,a,b,c,d,len;
int main()
{
    while(1)
    {
        ce=getchar();
        if(ce=='\n')break;
        s[++len]=ce;
    }//为了快一点
    for(int i=1;i<=len;i++)
    {
        for(int j=0;j<=25;j++)
        {
            if(s[i]=='a'+j)z[i][j]=z[i-1][j]+1;//相同即+1
            else z[i][j]=z[i-1][j];//不同即继承
        }
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        bool flag=false;
        cin>>a>>b>>c>>d;
        for(int j=0;j<=25;j++)
        {
            if(z[b][j]-z[a-1][j]!=z[d][j]-z[c-1][j]){//两个字母数量不同
                cout<<"NE"<<endl;flag=true;break;
            }
        }
        if(!flag)
        cout<<"DA"<<endl;
    }
    return 0;
}
```

---

## 作者：Hide_In_The_Shadow (赞：2)

## Programiranje 题解

模拟赛的签到题捏

题目要求，$[c,d]$ 之间的字母组成的单词 $Y$ 是否能以某种方式重新排列组合组成 $[a,b]$ 之间的字母构成的单词 $X$，也就是 $X$ 和 $Y$ 的字母组成应该是一样的。那么问题就很好解决了，可以利用前缀和处理字母数量来判断两个区间是否相等。时间复杂度是 $O(Q)$ 的，具体细节可以看代码。

### CODE

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
struct abc{//用结构体存储字母数量
	int num[30];
}n[114514];
abc operator -(abc a,abc b){//重定义结构体减法
	abc c;
	for(int i=0;i<=25;++i){
		c.num[i]=a.num[i]-b.num[i];
	}
	return c;
}
bool pd(abc a,abc b){//判断两个结构体是否相等
	for(int i=0;i<=25;++i){
		if(a.num[i]!=b.num[i])return 0;
	}
	return 1;
}
char s[114514];
int q;
int main(){
//	freopen("programiranje.in","r",stdin);
//	freopen("programiranje.out","w",stdout);
    scanf("%s",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;i++){//前缀和处理
    	n[i]=n[i-1];
    	n[i].num[s[i]-'a']++;
	}
	read(q);
	while(q--){
		int a,b,c,d;
		read(a);
		read(b);
		read(c);
		read(d);
		if(a-b!=c-d){//区间不相等，字母数量一定不相等，可以先行判断
			puts("NE");
			continue;
		}
		if(pd(n[b]-n[a-1],n[d]-n[c-1])){
			puts("DA");
		}
		else{
			puts("NE");
		}
	}
	return 0;
}

```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个字符串 $s$，共有 $q$ 组询问，每组询问给出 ```a,b,c,d```，问从 $a$ 到 $b$ 的子串能不能经过若干次变换与从 $c$ 到 $d$ 的子串相同。

#### 思路分析


------------
由于题目中要求的是在变换后相等即可，故只需要前者的每次字母的出现次数等于后者的就可以满足题意。

考虑利用前缀和的思想解决本题，用数组 $f[i][j]$ 表示前 $i$ 个数中第 $j$ 个字母出现的次数。

根据定义可以推得 $f[i][j] = f[i-1][j] + [s[i]=j]$。

每次询问循环每一个字母，若出现次数不同，直接输出 ```NE```，反之输出 ```DA```即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 50010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int f[N][27]; 
char s[N];

int main(){
	scanf("%s",s+1);
	int lens = strlen(s+1);
	for(int i=1;i<=lens;i++){
		for(int j=1;j<=26;j++){
			f[i][j] = f[i-1][j];
		}
		f[i][s[i]-'a'+1]++;
	} 
	int T = read();
	while(T--){
		bool flag = false;
		int a = read() , b = read() , c = read() , d = read();
		for(int i=1;i<=26;i++){
			if(f[b][i] - f[a-1][i] != f[d][i] - f[c-1][i]){
				flag = true;
				break;
			}
		}
		if(flag == true){
			printf("NE\n");
		}
		else printf("DA\n");
	}
	return 0;
}
```


---

## 作者：a_grain (赞：2)



------------
[题面](https://www.luogu.com.cn/problem/P4440)

------------
通过题目可以了解，此题主要让我们求 $a$ 到 $b$ 这段子串的字母个数是否等于 $c$ 到 $d$ 的子串。

------------
如果每输入一个查询做一次统计的话，无疑是会超时。因此，我们可以在读入单词的时候直接统计字母的前缀，用 $sum[i][j]$ 表示从第 $1$ 位到第 $i$ 位，字符 $j+97$ 出现的次数。

每次进行查询操作时，$26$ 个字母一一配对，不相等直接输出 NE。

------------
**AC code**
```cpp
#include<bits/stdc++.h>
#define I(x) ios::sync_with_stdio(x),cin.tie(x),cout.tie(x)//加快cin cout的语句
using namespace std;
int len,i,j,n,a,b,c,d,sum[50005][30];
char s[50005];
int main(){
	I(0);
	cin>>s+1;len=strlen(s+1);
	for(i=1;i<=len;i++){
		for(j=0;j<26;j++)sum[i][j]=sum[i-1][j];//前缀
		sum[i][s[i]-'a']++;
	}
	cin>>n;
	while(n--){
		cin>>a>>b>>c>>d;
		for(i=0;i<26;i++)
			if(sum[b][i]-sum[a-1][i]!=sum[d][i]-sum[c-1][i])//配对
				cout<<"NE"<<'\n',i=27;
		if(i==26)cout<<"DA"<<'\n';//判断是否输出NE
	}
	return 0;
}
```


------------
# The End.

---

## 作者：Aryzec (赞：2)

### [题面](https://www.luogu.org/problemnew/show/P4440)
### [博客使用](https://www.luogu.org/blog/41834/ti-xie-p4440-coci2017-20183-programiranje)
---
## 大致题意
有一个字符串，取出其中第 $x$~$y$ 位和第 $xx$~$yy$ 位，判断其中一个字符串能否通过调换字符的位置和另一个字符串一样。

---
## 思路
之前在练树状数组，看到这题正好就用来练树状数组了。

既然可以任意打乱顺序，那么只用判断这两个区间之内对应的字母的个数是否相等就好了。求一段区间内某个字母的个数，很明显的可以用树状数组~~（没有修改操作所以应该用前缀和更好）~~  ，而且时间复杂度也可以接受。具体操作就是对 $26$ 个字母每个都建一个树状数组，然后分开维护，最后查询时也是对每个字母进行查询比较。

#### 具体见代码↓~~(不过感觉这是个树状数组板子题，没啥好讲的)~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,xx,yy,n,Q,c[30][50005],sum1,sum2;
char s[100005];
int lowbit(int x){return x&-x;}
int get(int x){return x-'a'+1;}//将字母转换为对应的编号
void updata(int id,int x){
	for(;x<=n;x+=lowbit(x))c[id][x]++;
}
int getsum(int id,int x){
	int res=0;
	for(;x>0;x-=lowbit(x))res+=c[id][x];
	return res;
}
int main(){
	cin>>s+1;n=strlen(s+1);
	for(int i=1;i<=n;++i)updata(get(s[i]),i);//将每个字母加入树状数组
	scanf("%d",&Q);
	while(Q--){
		scanf("%d%d%d%d",&x,&y,&xx,&yy);
		bool bo=1;
		for(int i=1;i<=26;++i){//枚举每个字母
			sum1=getsum(i,y)-getsum(i,x-1);
			sum2=getsum(i,yy)-getsum(i,xx-1);
			if(sum1!=sum2){bo=0;break;}
		}
		if(bo)puts("DA");else puts("NE");//输出
	}
	return 0;
}
```

---

## 作者：B天选之子B (赞：2)

## 题目描述如下

- 有两个字符串出自同一个字符串。

- 问题是两个字符串的所有元素是否一样。

## 解题思路

**因为两个字符串都是一个连续区间，求的又是每个元素的个数所有用前缀和。**

- 统计个数可以在输入时进行。

- 元素一样就包括每个字母的个数。

- 求区间的元素就用区间末尾减去区间开头的前一个。

**最后解题方法就是用前缀和记录区间元素，最后进行比较。**

## 注意事项

-  区间元素包含两个端点。

-  字符串要从零开始，从一开始有问题。

## 奉上代码
```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL GS[500010][26];//前缀和数组
LL Q,A,B,C,D;
bool m=0;
string S;
int main() {
	cin>>S;
	for(int i=0; i<S.size(); i++) {
		for(int j=0; j<26; j++)
			GS[i+1][j]=GS[i][j];
			GS[i+1][S[i]-'a']++;//出现一次就加一个。
	}
	scanf("%lld",&Q);
	for(LL i=1; i<=Q; i++) {
		int	m=0;
		scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
		if(B-A!=D-C) 	printf("NE\n");	//可以先排除长度不一样的。
		else {
			for(int i=0; i<26; i++)
				if(GS[B][i]-GS[A-1][i]!=GS[D][i]-GS[C-1][i]) {//比较区间元素
					if(m==0) {
						printf("NE\n");
						m=1;
					}
				}
			if(m==0)
				printf("DA\n");
		}
	}
	return 0;
}
```
**纯暴力容易超时，最优前缀和。**

---

## 作者：yeshubo_qwq (赞：1)

## 思路
题目中要求重新排列单词中的字母，能否成功与字母顺序无关，与字母数量有关。

因此，我们只需要求出两个单词中不同字母的数量，进行比较，只要有一个字母数量不同就是不能重新排列成功的。

但显然，每次枚举求一遍会超时，所以要用前缀和进行优化。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,f[26][50005],q,a,b,c,d,flag;
char ch,s[50005];
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(i=1;i<=n;i++)//求出前缀和
        for(ch='a';ch<='z';ch++)
            if(s[i]==ch)f[ch-'a'][i]=f[ch-'a'][i-1]+1;
            else f[ch-'a'][i]=f[ch-'a'][i-1];
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        flag=1;
        for(i=0;i<26;i++)//每一个字母进行比较
            if(f[i][b]-f[i][a-1]!=f[i][d]-f[i][c-1]){
                flag=0;break;//不行直接退出
            }
        if(flag==1)printf("DA\n");
        else printf("NE\n");
    }
    return 0;
}
```


---

## 作者：syf2008 (赞：1)

这题可以用哈希来做。

我们给每一个字符一个随机值（也可以自己赋值），比如这样:
```
a[i]=(rand%10)*100000000+(rand%10)*10000000+(rand%10)*1000000+(rand%10)*100000+(rand%10)*10000+(rand()%10)*1000+(rand()%10)*100+rand()%10)*10+(rand()%10);
```
两个字符的哈希值重复概率很低（~~rp差那没办法~~）。

然后再用前缀和做一遍。

上代码
```
#include<bits/stdc++.h>
using namespace std;
string s;
int m,l1,r1,l2,r2,len,a[30];
long long h[50005];
int main()
{
    srand(time(0));
    cin>>s;
    len=s.size();
    for(int i=1;i<=26;i++)
    a[i]=(rand%10)*100000000+(rand%10)*10000000+(rand%10)*1000000+(rand%10)*100000+(rand%10)*10000+(rand()%10)*1000+(rand()%10)*100+rand()%10)*10+(rand()%10);//给每一个字符赋一个随机值
    for(int i=1;i<=len;i++)
    h[i]=h[i-1]+a[s[i-1]-'a'+1]*s[i-1];
    cin>>m;
    while(m--)
    {
        cin>>l1>>r1>>l2>>r2;
        if(r1-l1!=r2-l2)
        puts("NE");
    else if(h[r1]-h[l1-1]==h[r2]-h[l2-1])
        puts("DA");
    else puts("NE");
    }
}
```

---

## 作者：_Fontainebleau_ (赞：1)

有两种做法，暴力与前缀和，首先想到的是暴力，以为过不了，结果开 O2 就A了？？？

但是虽然暴力 A 了，还是准备两种都讲一下。



------------
### 暴力

对于每次询问，我们开两个数组 $numx,numy$ 统计单词 $X,Y$ 中 $a,b,c,\dots ,z$ 出现次数。然后比较 $numx,numy$ 数组。

然后就没了，注意开 O2 。

code 

```cpp
#include<bits/stdc++.h>
using namespace std;
int tc;
char s[50005];
int numx[123],numy[123];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	cin>>s+1;
	tc=read();
	while(tc--)
	{
		for(int i=97;i<=122;i++)//a的ASCII码为97，z为122
			numx[i]=numy[i]=0;
		int a=read(),b=read(),c=read(),d=read();
		bool flag=false;
		for(int i=a;i<=b;i++)
			numx[s[i]]++;
		for(int i=c;i<=d;i++)
			numy[s[i]]++;
		for(int i=97;i<=122;i++)
			if(numx[i]!=numy[i])
			{
				puts("NE");
				flag=true;
				break;
			}
		if(!flag)
			puts("DA");
	}
	return 0;
}
```


------------
### 前缀和

可以发现，当 $Q,b-a,d-c$ 过大时，上面的暴力显然是要 T 飞的。

我们考虑在循环外对字符串 $S$ 做预处理——前缀和。

我们用 $num_{i,j}$ 表示字符串 $S$ 前 $i$ 个字符中，ASCII码为 $j$ 的字符出现次数。

我们可以得到式子: $num_{i,j}=num_{i-1,j}+(j==S_i)$

那么单词 $X$ 中 ASCII码为 $i$ 的字符出现次数为 $num_{b,i}-num_{a-1,i}$

单词 $Y$ 同理，就不再赘述。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int tc;
char s[50005];
int num[50005][123];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	cin>>s+1;
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		for(int j=97;j<=122;j++)	num[i][j]=num[i-1][j];
		num[i][s[i]]++;
	}
	tc=read();
	while(tc--)
	{
		int a=read(),b=read(),c=read(),d=read();
		bool flag=false;
		for(int i=97;i<=122;i++)
			if(num[b][i]-num[a-1][i]!=num[d][i]-num[c-1][i])
			{
				puts("NE");
				flag=true;
				break;
			}
		if(!flag)
			puts("DA");
	}
	return 0;
}
```
~~目前是最优解~~


---

## 作者：Mu_leaf (赞：0)

直接上思路吧。

~~还挺水的....~~

## [思路]

既然第二个子串可以随意的调换位置，那么可以想到什么？

没错，我们只需要记录在这个子串里这个字母出现的次数就可以了！

这时再稍微往深处想想，预处理一下每个字母在 $1 \sim i$ 中 26 个字母出现的次数的前缀和即可。

此时设 $\mathit{dp}_{i,j}$ 表示为字母 $j$ 在 $1 \sim i$ 的子串中出现的次数。

状态转移方程就是：

```cpp
dp[i][j] = dp[i-1][j] + (j == str[i]);
```

~~其实也不算状态转移方程。~~

那此时里面任意子串中字母的出现次数都可以被求出来了。

既然都想到这了，那代码就可以直接出来了。

AC 代码：



------------

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=5e4+5;
int f[N][30],cnt_s1[30]; 
int Q, len, s1_l,s1_r,s2_l,s2_r;
string str;
bool fl=0;
int main(){
	cin >> str;
	scanf("%d",&Q);
	len=str.length();
	for(int i=1;i<=len;i++){
		for(int j=0;j<26;j++){
			if(char(j+'a')==str[i-1]) f[i][j]=f[i-1][j]+1;
			else f[i][j]=f[i-1][j]; 
		}
	}
	while(Q--){
		fl=0;
		scanf("%d%d%d%d",&s1_l,&s1_r,&s2_l,&s2_r);
		for(int i=0;i<26;i++) cnt_s1[i]=f[s1_r][i]-f[s1_l-1][i];
		for(int i=0;i<26;i++){
			if(f[s2_r][i]-f[s2_l-1][i]!=cnt_s1[i]){
				fl=1;
				break;
			} 
		}if(fl) printf("NE\n");
		else printf("DA\n");
	}
	return 0;
}
```

有了思路再往下想的话这道绿题就不足为据了。

---

## 作者：WhiteSunFlower (赞：0)

## 题目解析

阅读题目我们可以发现，题目就是给定一个字符串和两个区间，我们要做的就是判断一个区间的单词是否可以由另一个区间的单词重新排列得到。

我们假定两个区间分别为 X 和 Y。不难想到，若 X 可以由 Y 重新排列得到，那么会满足以下条件：

- X 的长度 = Y 的长度。
- X 中各个字母出现的次数和 Y 中各个字母出现的次数分别相等。

由此，题目就转换成了一个区间和的问题。利用前缀和就可以做到  $ O(1)$ 算出区间每个字母出现的次数。

## 代码思路

创建一个 $ sum[i][j] $ 的数组，表示直到前 $i$ 个字母中，字母 $j$ （$j$表示该字母在26个字母中的序号）出现的次数。那么区间 $ [l,r] $ 中, $j$ 出现的次数即为 
$$ sum[r][j] - sum[l-1][j]$$

将 j 从1~26依次判断一遍即可。
## AC代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=500005;
int sum[N][30],q,a,b,c,d;
char s[N];

void init(){
	cin >> s;
	int len=strlen(s);
	for(int i=1;i<=len;i++){
		for(int j=1;j<=26;j++){
			if((int)(s[i-1]-96)==j){
				sum[i][j]++;
			}
			sum[i][j]+=sum[i-1][j];
		}
	}
	return;
}

int main(){
	init();//前缀和预处理 
	cin >> q;
	while(q--){
		cin >> a >> b >> c >> d;
		if((b-a)!=(d-c)){
			cout << "NE" << "\n";
			continue;
		}
		bool _ok=1;
		for(int i=1;i<=26;i++){
			if((sum[b][i]-sum[a-1][i])!=(sum[d][i]-sum[c-1][i])){//挨个判断 
				_ok=0;
				break;
			}
		}
		if(_ok){
			cout << "DA" << '\n';
		}else{
			cout << "NE" << '\n';
		}
	}
	return 0;
}

```


---

