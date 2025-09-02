# Swap Letters

## 题目描述

``Monocarp``有两个长度相等的，里面只有字母``a``和``b``的字符串$s,t$。

``Monocarp``想要使这两个字符串相等。他可以执行以下操作任意次：指定两个下标$pos1,pos2$，交换$s_{pos1}$和$t_{pos2}$。

你需要确定``Monocarp``使这两个串变得相等所需要的最小操作次数，并且输出任意一个这样的步数最少的操作序列。或者说这两个串不可能变得相等。

## 说明/提示

在第一个样例中，你可以交换$s$的第三个字母，在交换$t$的第三个字母。于是$s$变为``abbb``，$t$变为``aaab``。再交换$s$的第三个字母和$t$的第二个字母即可达成目标，使得$s,t$都变成``abab``。

第二个样例中，显然不论怎么交换$s,t$都不可能相等。

## 样例 #1

### 输入

```
4
abab
aabb
```

### 输出

```
2
3 3
3 2
```

## 样例 #2

### 输入

```
1
a
b
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8
babbaabb
abababaa
```

### 输出

```
3
2 6
1 3
7 8
```

# 题解

## 作者：superman (赞：4)

首先看到比赛看到此题只有十分钟了，纵观此题发现题目描述的复杂程
度不像一个dp题，自然也不是数据结构题。于是考虑贪心。

大家可以对着代码理解思路（但不要copy）

首先判断无解的情况显然a，b字符个数为奇数时输出无解（下一步）
将a，b转化为0和1。
稍微手玩发现两列a在上b在下的字符或a在下b在上的字符只需交换一
次，而不同位置的两列则要两次交换。于是考虑把a同在上或下的尽量
多的排在一组。最后统计答案就是如果两种都为上下列不同且a，b位置
相反的个数为奇数就输出（上下不同列的列数）/2+1,不然就不加1.

实现：
记录q1和q2两个数组记录a在上和a在下的上下不同列的编号；num1和num2记录列数

1：若都为偶数交换这列和下列同类型的列的编号

2：若都为奇数就先进行1操作在进行余下两列的操作

即先交换同列，再交换两列不同类型的列的编号
此题完结（在考场上应为puts-1没return 0 导致没时间交了祝大家不要犯这种错误）










```
#include<bits/stdc++.h>
const int N=2e5+10;
using namespace std;
char s1[N],s2[N];
int num1,num2,q1[N],q2[N];
int cnt;
int a[N],b[N];
int tot;
int main(){
	int n;
	cin>>n;
	scanf("%s%s",s1+1,s2+1);
	for(int i=1;i<=n;i++){
		if(s1[i]=='a')tot++,a[i]=1;
		if(s2[i]=='a')tot++,b[i]=1;
	}
	if(tot&1){printf("-1");return 0;}
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]){
			cnt++;
			if(a[i])q1[++num1]=i;
			else{
				q2[++num2]=i;
			}
		}
	}
	if(num1%2 && num2%2)
	printf("%d\n",cnt/2+1);
	else printf("%d\n",cnt/2);
	if(num1%2 && num2%2){
		for(int i=1;i<=num1-1;i+=2){printf("%d %d\n",q1[i],q1[i+1]);}
		for(int i=1;i<=num2-1;i+=2){printf("%d %d\n",q2[i],q2[i+1]);}
		printf("%d %d\n",q1[num1],q1[num1]);
		printf("%d %d\n",q1[num1],q2[num2]);
	}else{
		for(int i=1;i<=num1-1;i+=2){printf("%d %d\n",q1[i],q1[i+1]);}
		for(int i=1;i<=num2-1;i+=2){printf("%d %d\n",q2[i],q2[i+1]);}
	}
	return 0;
}
```


---

## 作者：Binary_Lee (赞：2)


## [题面传送门](https://www.luogu.com.cn/problem/CF1215C)

#### 解决思路

首先容易得知，两个字符串中 $b$（或 $a$） 的个数为偶数时，一定有解。为奇数则一定无解。

其次考虑怎么交换。对照样例三：

**in:**
```
8
babbaabb
abababaa

```
**out:**
```
3
2 6
1 3
7 8
```

发现，**每一对交换的字符有共同点**：

- 要不是串一都为 $a$，串二都为 $b$ 的一对

- 要不是串一都为 $b$，串二都为 $a$ 的一对

简单思考后发现这样**成对交换就是最优的**。（换一次就可以匹配上两位）

于是，考虑先统计出 串一为 $a$，串二为 $b$ 的位数 $cnt1$，并将相应位置存入 $ans1$ 数组。同时统计出 串一为 $b$，串二为 $a$ 的位数 $cnt2$，并将相应位置存入 $ans2$ 数组。

这时发现一个问题，$cnt1$ 和 $cnt2$ 不一定为偶数，有可能不能各自成对匹配完。但可以发现， $cnt1$ 与 $cnt2$ 必同奇偶。由于偶数成对匹配更优，所以只可能剩下 **一位串一为 $a$，串二为 $b$** 与 **一位串一为 $b$，串二为 $a$** 。

这时就出现了样例一的情况：

**in:**
```
4
abab
aabb

```
**out:**
```
2
3 3
3 2
```

所以只要按着样例一的顺序特判输出即可：

```cpp
printf("%d %d\n",ans1[cnt1],ans1[cnt1]);
printf("%d %d\n",ans1[cnt1],ans2[cnt2]);
```

#### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans1[200005],ans2[200005],cnt,cnt1,cnt2;
string s1,s2;
int main(){
	scanf("%d",&n);
	cin>>s1>>s2;
	for(int i=0;i<n;i++){
		if(s1[i]=='b') cnt++;
		if(s2[i]=='b') cnt++;
	}
	if(cnt%2==1) printf("-1");
	else{
		for(int i=0;i<n;i++){
			if(s1[i]=='a'&&s2[i]=='b') ans1[++cnt1]=i+1;
			if(s2[i]=='a'&&s1[i]=='b') ans2[++cnt2]=i+1; 
		}
		if(cnt1%2==0){
			printf("%d\n",cnt1/2+cnt2/2);
			for(int i=1;i<=cnt1;i+=2){
				printf("%d %d\n",ans1[i],ans1[i+1]);
			}
			for(int i=1;i<=cnt2;i+=2){
				printf("%d %d\n",ans2[i],ans2[i+1]);
			}
		}
		else{
			printf("%d\n",cnt1/2+cnt2/2+2);
			for(int i=1;i<=cnt1-1;i+=2){
				printf("%d %d\n",ans1[i],ans1[i+1]);
			}
			for(int i=1;i<=cnt2-1;i+=2){
				printf("%d %d\n",ans2[i],ans2[i+1]);
			}
			printf("%d %d\n",ans1[cnt1],ans1[cnt1]);
			printf("%d %d\n",ans1[cnt1],ans2[cnt2]);
		}
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：2)

一开始看到这题时，我感觉无从下手，直到我看到了题目中这句话：

**字符串中只有字母 a 和字母 b！**

那么，需要交换操作的情况就很少了。我们可以开始分类讨论：

第 ① 类：

| 下标 | $i$ | $j$ |
|:----------:| :----------: | :----------: |
| 字符串 $S$ | $\texttt{a}$ | $\texttt{a}$ |
| 字符串 $T$ | $\texttt{b}$ | $\texttt{b}$ |
显然，选择下标 $i$ 和 $j$ 的位置交换即可，需要 $\color{green}1$ 步操作。

第 ② 类：

| 下标 | $i$ | $j$ |
|:----------:| :----------: | :----------: |
| 字符串 $S$ | $\texttt{b}$ | $\texttt{b}$ |
| 字符串 $T$ | $\texttt{a}$ | $\texttt{a}$ |
同 ①，选择下标 $i$ 和 $j$ 的位置交换即可，需要 $\color{green}1$ 步操作。

第 ③ 类：

| 下标 | $i$ | $j$ |
|:----------:| :----------: | :----------: |
| 字符串 $S$ | $\texttt{a}$ | $\texttt{b}$ |
| 字符串 $T$ | $\texttt{b}$ | $\texttt{a}$ |
对于这类情况，要先选择下标 $i$ 和 $i$ （或者下标 $j$ 和 $j$）进行交换，然后情况就转换为第 ① 类或第 ② 类的情况，再执行一次交换即可，共需要 $\color{red}2$ 次操作。

又因为题目要求最小的操作次数，我们就可以考虑一个简单的**贪心**策略：**尽可能地使用第 ① 类和第 ② 类的操作。**如果按这样的策略去执行操作，最后必定只有两种情况：
- 最后的字符串 $S$ 与字符串 $T$ 已经相等。
- 最后的字符串 $S$ 与字符串 $T$ 还剩下一组第 ③ 类情况，执行第 ③ 类情况交换即可相等。

最后的操作次数一定是最少的。

那么，我们用两个 vector 存储不匹配的位置。一个存储 $S(i)=\texttt{a},T(i)=\texttt{b}$ 的位置下标，一个存储 $S(i)=\texttt{b},T(i)=\texttt{a}$ 的位置下标，按照情况分类合成操作序列，最后输出合成的答案即可。

至于判断无解，我们只要判断两个串中字符 $\texttt{a}$ 和字符 $\texttt{b}$ 的总数是否可以被 $2$ 整除即可。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string> 
#include<vector>
using namespace std;
vector<int>sg[2];
vector< pair<int,int> >anss;  
//存储最后拼出来的操作序列
int main()
{
	int n,a1=0,a2=0,b1=0,b2=0;
	scanf("%d",&n);
	string str1,str2;
	cin>>str1>>str2;  //读入字符串 S 和 T
  
	for(int i=0;i<n;i++){
                          
		if(str1[i]=='a')
			a1++;
		else
			b1++;
        //统计 S 中的 a 和 b 的数量
                          
		if(str2[i]=='a')
			a2++;
		else
			b2++;
        //统计 T 中的 a 和 b 的数量
                          
		if(str1[i]=='a'&&str2[i]=='b')
			sg[0].push_back(i+1);
		if(str1[i]=='b'&&str2[i]=='a')
			sg[1].push_back(i+1);	
        //分类存储
	}
                          
	if(!((a1+a2)%2==0&&(b1+b2)%2==0)){
		printf("-1");   //判断无解
		return 0;
	}
                          
	while(sg[0].size()>=2){
		anss.push_back(make_pair(sg[0][sg[0].size()-1],sg[0][sg[0].size()-2]));
		sg[0].pop_back();
		sg[0].pop_back();
		//第一类情况操作
	}
  
	while(sg[1].size()>=2){
		anss.push_back(make_pair(sg[1][sg[1].size()-1],sg[1][sg[1].size()-2]));
		sg[1].pop_back();
		sg[1].pop_back();
  		//第二类情况操作
	}
  
	if(sg[1].size()==1&&sg[0].size()==1){
		anss.push_back(make_pair(sg[1][sg[1].size()-1],sg[1][sg[1].size()-1]));
		anss.push_back(make_pair(sg[0][sg[0].size()-1],sg[1][sg[1].size()-1]));
  		//最后的第三次操作
	}
  
	printf("%d\n",anss.size());   //输出操作数量
	for(int lans=anss.size(),i=0;i<lans;i++)
		printf("%d %d\n",anss[i].first,anss[i].second);
	//输出最后合成的操作序列
                                             
        return 0;
}
```



---

## 作者：开始新的记忆 (赞：0)

题目大意：现在给你两个长度为n且只由a，b两个字母组成的字符串，每次操作可在每个字符串中选择一个位置并交换，现求最小的操作次数使得两个字符串相等，如果可以相等，则输出次数并输出如何操作，反之则输出-1；

具体思路：先考虑不可能的情况，我们先记录a和b的个数，如果个数为奇数，那么不可能平均分到两个字符串中（程序的ans1，ans2为记录的数）。

稍微思考一下可发现，每次交换的位置上与其对应位置的字母肯定是不同的，于是我们只需记录与对应位置不同的位置即可。我们每次记录时会有两种情况，分别为ab和ba，每个的判断方法不同，得分开记录。如果ab，ba的个数都为偶数（不存在一奇一偶的情况，不然ans1+ans2也为奇数，那么应该是输出-1的），那么就ab和ab换，ba和ba换（e.g:5 ababa baaab，交换1，5和2，4即可），如果ab和ba的个数都是奇数，那么只需将其中的一个ab的上下交换，使ab变ba（要判断有没有ab，我WA了三次），然后同上。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
vector <int > x,y;
int n,xx=0,yy=0,ans1=0,ans2=0;
 
int main()
{	cin>>n>>a>>b;
	for(int i=1;i<=n;++i)
	{
		if(a[i-1]=='a')
			ans1++;
		else
			ans2++;
		if(b[i-1]=='a')
			ans1++;
		else
			ans2++;
		if(a[i-1]==b[i-1])
			continue;
		if(a[i-1]=='a')
			x.push_back(i);
		else
			y.push_back(i);
	}
	if(ans1&1 || ans2&1)
	{
		cout<<-1<<endl;
		return 0;
	}
	int m=x.size()/2,k=y.size()/2;
	cout<<x.size()/2+y.size()/2+(x.size()%2+y.size()%2)<<endl;
	for(int i=0;i<m;++i)
		cout<<x[i]<<' '<<x[x.size()-i-1]<<endl;
	for(int i=0;i<k;++i)
		cout<<y[i]<<' '<<y[y.size()-i-1]<<endl;
	if(x.size()%2==1)
	{
        cout<<x[x.size()/2]<<' '<<x[x.size()/2]<<endl;
        cout<<x[x.size()/2]<<' '<<y[y.size()/2]<<endl;
    }
	return 0;
}
```


---

## 作者：两年打铁 (赞：0)

yy一下不难发现，对于任意不相同的两个位置，只要这两个位置的字符相同，我们直接换是最优的，一步就能换掉两个不一样。

然后可能a,b只剩下一个不一样，那就用两步暴力换掉就可以了。

```
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define kong putchar(' ')
#define huan putchar('\n')
#define bug puts("QWQ")
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[100];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
inline void wrs(const int &x)
{
	write(x);
	putchar(' ');
}
 
inline void wrl(const int &x)
{
	write(x);
	putchar('\n');
}
 
const int N=2e5+233;
 
 
int n;
char s1[N],s2[N];
vector<int>v1,v2;
 
int main()
{
	read(n);
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	for(register int i=1;i<=n;++i)
	{
		if(s1[i]!=s2[i])
		{
			if(s1[i]=='a')
			{
				v1.push_back(i);
			}
			else 
			{
				v2.push_back(i);
			}
		}
	}
	if((v1.size()+v2.size())&1)
	{
		puts("-1");
		return 0;
	}
	int ans=v1.size()/2+v2.size()/2;
	if(v1.size()&1)ans+=2;
	cout<<ans<<endl;
	if(v1.size()>1)
	for(register int i=0;i<(int)v1.size()-1;i+=2)
	{
		wrs(v1[i]);
		wrs(v1[i+1]);
		huan;
	}
	if(v2.size()>1)
	for(register int i=0;i<(int)v2.size()-1;i+=2)
	{
		wrs(v2[i]);
		wrs(v2[i+1]);
		huan;
	}
	if(v1.size()&1)
	{
		cout<<v1[v1.size()-1]<<" "<<v1[v1.size()-1]<<endl;
		cout<<v2[v2.size()-1]<<" "<<v1[v1.size()-1]<<endl;
	}
}
```


---

## 作者：弦巻こころ (赞：0)

~~为什么这场考试这么喜欢 O(n) 题~~

我们~~仔细~~观察一下就可以发现

相同的我们就肯定不会再去动他.

如果n为奇数肯定就没有.

如
```
aab
bba
```
所以我们在读入的时候直接无视掉相同的部分,再特判一下.

然后我们再观察下不同的该怎么办

```
aaaa
bbbb
交换两次就行了

abaa
babb
则需要交换三次

```
思考一下就可以发现

如果我们只看上面的部分.(假设已经排除了不合法的数据和上下相同的数据)

abaa 

a,b为奇数个(这里奇偶定义不一样,不要搞错了)

就会共有((n+2)/2)次交换.也就是2次

aabb

a,b为偶数个
就会共有(n/2)次交换.也就是2次

对于输出交换的数也很好处理.

我们记录下每次出现不同的数的位置再两两输出一下就行了.

代码

```cpp
//can1+can2其实就是n,考试时候写复杂了
#include<bits/stdc++.h>
using namespace std;
char s[3][200005];
int n;
int can1,can2,bc;
int cnt1[200005],cnt2[200005];
int sum;
int main()
{
	cin>>n>>s[1]>>s[2];
	for(int i=0;i<n;i++)
	{
		if(s[1][i]!=s[2][i])
		{
			if(s[1][i]=='a')
			{
				can1++;
				cnt1[can1]=i+1;
			}else
			{
				can2++;
				cnt2[can2]=i+1;
			}
		}
	}
	if((can1+can2)%2==1)//如果n为奇数
	{
		cout<<"-1";
		return 0;
	} 
	if(can1%2==1)//上面如果a的个数为奇数
	{
		sum+=2;
		sum+=(can1+can2-2)/2; 
		cout<<sum<<endl;
		cout<<cnt1[1]<<" "<<cnt1[1]<<endl;
		cout<<cnt1[1]<<" "<<cnt2[1]<<endl;
		for(int i=2;i<=can1;i+=2)
		{
			cout<<cnt1[i]<<" "<<cnt1[i+1]<<endl;
		} 
		for(int i=2;i<=can2;i+=2)
		{
			cout<<cnt2[i]<<" "<<cnt2[i+1]<<endl;
		} 
		return 0;
	}
	sum=(can1+can2)/2; 
	cout<<sum<<endl;
	for(int i=1;i<=can1;i+=2)
	{
		cout<<cnt1[i]<<" "<<cnt1[i+1]<<endl;
	} 
	for(int i=1;i<=can2;i+=2)
	{
		cout<<cnt2[i]<<" "<<cnt2[i+1]<<endl;
	} 
	return 0;
   
}

```
听说CYJian神仙 Rank16上橙了%%%%

---

## 作者：LordLeft (赞：0)

~~智商不够，数据结构来凑~~

题意：给定两个$ab$串$S_1$,$S_2$，每次可以交换$S_1$和$S_2$中的两个字符，求使两字符串相等的最小交换次数，输出方案

换句话说，以最小的代价消除所有错位字符

---------------------

首先，读完题后，先想出一种贪心的交换策略：

>对于每一个$S_1$中的错位的字符，找到$S_2$中它下标后面第一个与之交换后能使它匹配的错位字符与之交换，如果没有，则使它与$S_2$中与它下标相同的字符交换后重新寻找。

>(可能有点绕)

$No$ $Solution$就是$a$的数量为奇数，特判一下就好

---------------------

举个例子：

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| b    | a    | b    | b    | a    | a    | b    | b    |
| a    | b    | a    | b    | a    | b    | a    | a    |

对于$S_1[1]$，找到$S_2$中的第一个错位$a$，也就是3号，将它们互换

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| a    | a    | b    | b    | a    | a    | b    | b    |
| a    | b    | b    | b    | a    | b    | a    | a    |

下一个错位是$S_1[2]$，找到$S_2$中第一个错位$b$，也就是6,将它们互换

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| a    | b    | b    | b    | a    | a    | b    | b    |
| a    | b    | b    | b    | a    | a    | a    | a    |

下一个是$S_1[7]$，将其与$S_2[8]$交换

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| a    | b    | b    | b    | a    | a    | a    | b    |
| a    | b    | b    | b    | a    | a    | a    | b    |

此时$S_1$与$S_2$相等，结束程序

-------------------------------

现在我们来思考一下这个贪心的正确性(可能是伪证，有问题回复一下)：

对于每一次交换，最多使两对错位字符归位，那么我们就考虑每次找到这两对字符将它们交换

但是如果找不到呢(假设现在在匹配$S_1$中一个错位$a$)？

也就是说，$S_2$中没有错位$b$了，但是由于这时候两个串还没有完全匹配，所以$S_2$中一定还有错位的$a$，所以我们把现在匹配到的$S_1$中的$a$与$S_2$中与之对应的$b$交换，让这个$b$与$S_2$中的错位$a$交换就行了

这样贪心的换一定是最优的，而且由于我们是顺序的找错位，一个字符绝对不会与它后面的字符交换

----------------------------

如果直接找的话，时间复杂度是$O(n^2)$的，不可接受

~~听说他们人人会$O(n)$模拟，我还是太菜了~~

这时候我们考虑用一些神奇的方法优化一下复杂度

瓶颈在“第一个错位的字符”这里，那么我们想办法优化一下

首先，对于“第一个XXX”这种题目，很容易想到二分，但是这个题目好像没什么二分的，因为“第一个错位位置”这个东西不具备单调性

转念一想，前缀和是具有单调性的，那么我们记录错位$a$数量的前缀和和错位$b$数量的前缀和，那么找第一个错位字符就转化成了二分出第一个错位前缀和大于($>$)当前位置错位前缀和的下标

发现每次交换只会改变两个位置的错位前缀和，而我们的查询又是前缀和，单点改区间求和，很自然想到用树状数组维护这个东西

时间复杂度$O(nlog^2n)$，勉强可以过

具体还有一些细节见代码

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<string>
#include<cstring>
using namespace std;
const int N=2000005;
int n;
//树状数组
struct BIT{
	BIT(){
		memset(c,0,sizeof(c));
		}
	int c[N];
	int lowbit(int x){
		return x&(-x);
		}
	void update(int x,int y){
		for(int i=x;i<=n;i+=lowbit(i)){
			c[i]+=y;
			}
		}
	int query(int x){
		int sum=0;
		for(int i=x;i>0;i-=lowbit(i)){
			sum+=c[i];
			}
		return sum;	
		}	
	};
//c1记录S2中的错位a前缀和，c2记录S2中的错位b前缀和
BIT c1,c2;
string s1,s2;
int cnt;
//Ans数组记录答案
int Ans[N][2];
int tot;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	cin>>s1>>s2;
	s1='!'+s1;
	s2='!'+s2;
	for(int i=1;i<=n;i++){
		if(s1[i]=='a'){
			cnt++;
			}
		if(s2[i]=='a'){
			cnt++;
			}	
		//下面的部分是将错位字符插入树状数组
		if(s2[i]=='a'&&s1[i]=='b'){
			c1.update(i,1);
			}
		else if(s2[i]=='b'&&s1[i]=='a'){
			c2.update(i,1);
			}	
		}	
	if(cnt&1){
		//无解特判
		cout<<-1;
		return 0;
		}	
	for(int i=1;i<=n;i++){
		//仅对错位字符进行匹配
		if(s1[i]==s2[i]){
			continue;
			}
		int tmp;
		//tmp是二分的界限
		if(s1[i]=='a'){
			tmp=c2.query(i);
			}
		else{
			tmp=c1.query(i);
			}		
		int le=i,ri=n,mid,ans=0;
		//二分出下标
		while(le<=ri){
			int now;
			mid=(le+ri)>>1;
			if(s1[i]=='a'){
				now=c2.query(mid);
				}
			else{
				now=c1.query(mid);
				}	
			if(now>tmp){
				ans=mid;
				ri=mid-1;
				}	
			else{
				le=mid+1;
				}	
			}
		if(!ans){
			ans=i;
			}	
		//记录交换位置
		tot++;
		Ans[tot][0]=i;
		Ans[tot][1]=ans;
		//交换之后对于树状数组的修改(略恶心)
		if(ans!=i){
			if(s1[i]=='a'){
				c2.update(i,-1);
				c2.update(ans,-1);
				}
			else{
				c1.update(i,-1);
				c1.update(ans,-1);
				}	
			}
		else{
			if(s1[i]=='a'){
				c1.update(ans,1);
				c2.update(ans,-1);
				}
			else{
				c1.update(ans,-1);
				c2.update(ans,1);
				}	
			}	
		swap(s1[i],s2[ans]);
		//如果它之后没有错位，上下交换后重新匹配
		if(ans==i){
			i--;	
			}
		}	
	//输出答案 
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++){
		cout<<Ans[i][0]<<" "<<Ans[i][1]<<endl;
		}
	return 0;
	}
```

GL～

---

## 作者：天南月 (赞：0)

题目描述：

Monocarp有两个长度相等的，里面只有字母$a$和$b$的字符串$s,t$。

Monocarp想要使这两个字符串相等。他可以执行以下操作任意次：指定两个下标$pos1,pos2$交换$s_{pos1}$和$t_{pos2}$。

你需要确定Monocarp使这两个串变得相等所需要的最小操作次数，并且输出任意一个这样的步数最少的操作序列。或者说这两个串不可能变得相等。

输入格式

第一行是一个整数$n(1\le n\le 2*10^5)$表示$s,t$的长度。

第二行一个只包含字母$a,b$的长度为$n$的字符串$s$。

第三行一个只包含字母$a,b$的长度为$n$的字符串$t$。

输出格式

如果不可能使这两个串相等，输出$-1$。

否则，第一行输出最小操作步数$k$，然后再输出$k$行，每行两个整数，表示你在这一次进行操作时所指定的$pos1$和$pos2$。

输入输出样例

输入1
4
abab
aabb

输出1
2
3 3
3 2

输入2
1
a
b

输出2
-1

说明/提示

在第一个样例中，你可以交换$s$的第三个字母，在交换$t$的第三个字母。于是$s$变为$abbb$，$t$变为$aaab$。再交换$s$的第三个字母和$t$的第二个字母即可达成目标，使得$s,t$都变成$abab$。

第二个样例中，显然不论怎么交换$s,t$都不可能相等。

做法：

首先我们可以发现，如果在某个位置上$s$和$t$上的字母相等，那么不交换他们肯定要更优一点。接下来我们把在$s$中为$a$，在$t$中为$b$的位置记为第一种，在$s$中为$b$，在$t$中为$a$的位置记为第二种，我们可以发现，同种情况交换只要一步，而不同种的情况交换需要两步，这时候就可以确定贪心策略了：

### 如果$i$位置后面还有同种情况的，就把两个位置都标记同时记录答案，否则就找不同种的

我们只需要$O(n)$记录一下两种情况的位置，再$O(n)$匹配一下就行了。无解的情况很显然，因为我们每一种情况都需要另一个与之搭配，所以如果两种情况的位置总数为奇数就必定无解。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,l1,r1,l2,r2,len;
char s[N],t[N];
int stack1[N],stack2[N];//记录两种情况
bool bj[N];//标记位置
int x1[N],x2[N];//记录答案
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	scanf("%s",t+1);
	for(int i=1;i<=n;++i){
		if(s[i]==t[i]||bj[i])continue;//如果相同就不做操作
		if(s[i]=='a'&&t[i]=='b')stack1[++r1]=i;
		else stack2[++r2]=i;//记录
	}
	if((r1+r2)&1){puts("-1");return 0;}
	for(int i=1;i<=n;++i){
		if(s[i]==t[i]||bj[i])continue;
		//cout<<i<<endl;
		if(s[i]=='a'&&t[i]=='b'){
			l1++;
			if(l1<r1){
				l1++;
				x1[++len]=i;
				x2[len]=stack1[l1];
				bj[stack1[l1]]=true;
			}
			else{
				if(l2<r2){
					l2++;
					x1[++len]=i;
					x2[len]=i;
					x1[++len]=i;
					x2[len]=stack2[l2];
					bj[stack2[l2]]=true;
				}
				else {cout<<1<<endl;puts("-1");return 0;}
			}
		}
		else{
			l2++;
			if(l2<r2){
				l2++;
				x1[++len]=i;
				x2[len]=stack2[l2];
				bj[stack2[l2]]=true;
			}
			else{
				if(l1<r1){
					l1++;
					x1[++len]=i;
					x2[len]=i;
					x1[++len]=i;
					x2[len]=stack1[l1];
					bj[stack1[l1]]=true;
				}
				else {puts("-1");return 0;}
			}
		}//匹配
	}
	printf("%d\n",len);
	for(int i=1;i<=len;++i)
		printf("%d %d\n",x1[i],x2[i]);
	return 0;
}
```
总的来说，大概黄题难度。

---

