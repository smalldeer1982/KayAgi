# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314
```

### 输出

```
2
```

## 样例 #2

### 输入

```
625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
333
```

### 输出

```
-1
```

# 题解

## 作者：GusyNight (赞：9)

**题目翻译**
```cpp
给您一个正整数n n，
不带前导零（例如，数字04不正确）。
在一个操作中，您可以删除给定整数的任何数字，
以便结果保持正整数而不带前导零。
确定需要一致地应用于给定整数n n的最小操作数，
以使其成为某个正整数的平方或报告它是不可能的。
当且仅当x=y^2 x=y时，整数x x x是某个正整数的平方。
x=y^2
对于某个正整数y。
```
**题目意思**
```cpp
给你正整数n，
每次可以进行一次操作移除一个数字
（当然也可以不操作），
求出一个数x，x是操作后开方的结果。
输出最少的操作步数.不能的话就输出-1.
```
**思路**
```cpp
暴力时间给了两秒，
而且只有9位数字，
暴力时间都是多的。
做比赛的时候，
想的是深搜，不过dfs，还要处理前导零写晕头了，
就放弃了。
有的大佬有的位运算/2的，
看不懂别人的思路，
然后看到了有暴力的，
也就暴力了。先把输入的n每位数分解存入数组，
在从最大的可能（sqrt（n））
里面递减找是否等于n里面的几位数字，
等于对的位数越多，
说明需要移除的数字就越少，操作步数也越少。
```
**AC代码**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    long long n,m,a[10],b[10];
    cin>>n;m=n;
    int cnt1=0,cnt2=0,l;
    while(m)a[cnt1++]=m%10,m/=10;
    for(int i=sqrt(n);i>=1;i--){
        long long x=i*i;cnt2=0;
        long long k=x;
        while(x)b[cnt2++]=x%10,x/=10;
        l=0;
        for(int j=0;j<cnt1;j++){
            if(a[j]==b[l]){
                l++;
                if(l==cnt2)break;
            }
        }
        if(l==cnt2)return cout<<cnt1-l,0;
    }
    puts("-1");
    return 0;
}
```

---

## 作者：Andy_Li (赞：6)

# CF962C Make a Square 题解

## 题意

给定一个正整数 $x$，要求删掉几位之后 $x$ 能变成完全平方数。

特殊情况：前导零。如果枚举的这个数位数与删除的位数不符，则不考虑。

## 思路

考虑爆搜，因为 $x \le 2 \times 10^9$，所以最多删 $10$ 位。考虑每一位删和不删。时间复杂度很低。

计算答案取 $\min $ 时记得特判前导零。

提供一组一开始没特判前导零数据把我卡住的数据：输入 ```101```，输出 ```2```。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
int cnt=0,ans=40;
int a[maxn];
int checks(int x,int num)
{
	num=cnt-num;
	while(x)
	{
		x/=10;
		num--;
	}
	if(num!=0)
		return 0;
	return 1;
}
void dfs(int pos,int x,int choose)
{
	if(pos>cnt)
	{
		if(int(sqrt(x))*int(sqrt(x))==x && x!=0 && checks(x,choose)!=0)
			ans=min(ans,choose);
		//		cout<<x<<" "<<choose<<" "<<ans<<endl;
		return ;
	}
	for(int i=0;i<=1;i++)
		if(i==0)
			dfs(pos+1,x*10+a[pos],choose);
	else
		dfs(pos+1,x,choose+1);
	return ;
}
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	//srand((unsigned)time(NULL));
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int x;
	cin>>x;
	int t=x;
	while(t)
	{
		a[++cnt]=t%10;
		t/=10;
	}
	for(int i=1;i<=cnt/2;i++)
		swap(a[i],a[cnt-i+1]);
	//	for(int i=1;i<=cnt;i++)
	//		cout<<a[i]<<" ";
	dfs(1,0,0);
	if(ans==40)
		ans=-1;
	cout<<ans;
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：1)

这是一个深搜的模板题。

首先，我们发现n的位数很小，只有9位。于是我们想到了深搜算法。

首先，把n拆分成数组，记n的数位个数位$|n|$。

枚举$|n|$个元素的全排列。

之后我们判定。

一个是完全平方数当且仅当 
$\left\lfloor\sqrt(x)\right\rfloor$ = $\sqrt(x)$

于是对于每一个全排列，把他们拼起来，然后判定即可

注意要去除前导零和长度为0的情况。

代码中，存放排列使用$vector$实现的


```cpp
// Author : harry
// Language : C++ (GNU C++ 11)
// Upload : CodeForces / luogu
// Time : 2018.9
// Problem : Make a Square
// Tell Myself : Think Twice Code Once
// All rights reserved

#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i,a,b) for (int (i)=(a);(i)<=(b);(i)++)
#define Rep(i,a,b) for (int (i)=(a)-1;(i)<(b);(i)++)
#define REP(i,a,b) for (int (i)=(a);(i)>=(b);(i)--)
#define reg(i,x) for (int (i)=head[x];(i);i=e[i].next)

#define ull unsigned long long
#define ll long long
#define ls ((x)<<1)
#define rs ((x)<<1|1)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define Pii pair<int,int>

const int N = 100010 ;
const int iinf = INT_MAX/2 ;
const ll linf = LONG_MAX/2 ;
const int MOD = 1e9+7 ;

inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}

void write(int x){
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}

int a[20] ;
int n,ans=-1,x ;
vector<int> b ;

void init(int x){
	while(x) a[++n]=x%10,x/=10 ;
	reverse(a+1,a+n+1) ;
}

bool judge(int m){ //判定是不是完全平方数
    double x=sqrt(m);
    if (floor(x)==x) return 1;
    return 0;
}

bool check(vector<int> dig){ //深搜
	int tmp=0 ;
	for (int i=0;i<dig.size();i++) tmp=tmp*10+dig[i] ;
	if (dig.size()==0 || dig[0]==0 || !judge(tmp)) return 0 ;
	return 1 ;
}

void dfs(int k,vector<int> dig){
	if (k==n+1){
		if (check(dig)) ans=max(ans,(int)dig.size());
		return ;
	}
	dfs(k+1,dig);
	dig.pb(a[k]);dfs(k+1,dig) ;
}

int main(){
	scanf("%d",&x) ;
	init(x) ;
	dfs(1,b) ;
	if (ans==-1) printf("-1\n") ;
	else printf("%d\n",n-ans) ;
}

```

---

## 作者：Wf_yjqd (赞：1)

又和同学 duel，然后又碰上水题了。

------------

考虑枚举最终的完全平方数，最多只有 $\sqrt n$ 种。

对于每一个考虑拆位，和 $n$ 对比。

可以双指针匹配，判断每个完全平方数是否是 $n$ 的子序列。

复杂度 $\operatorname{O}(\sqrt n\times\log n)$。

------------

很简单的模拟题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,wn,a[23],b[23],cnt,ans=0x3f3f3f3f;
inline int w(int x){
    if(x>9)
        return w(x/10)+1;
    return 1;
}
inline void f(int x,int *s){
    cnt=0;
    while(x){
        s[++cnt]=x%10;
        x/=10;
    }
    return ;
}
int main(){
    scanf("%d",&n);
    wn=w(n);
    f(n,a);
    for(int i=1;i*i<=n;i++){
        if(w(i*i)==wn&&i*i!=n)
            continue;
        f(i*i,b);
        int j,k;
        for(j=1,k=1;j<=wn&&k<=cnt;j++){
            if(a[j]==b[k])
                k++;
        }
        if(k>cnt)
            ans=min(ans,wn-cnt);
    }
    printf("%d",ans>1e9?-1:ans);
    return 0;
}
```


---

## 作者：QianianXY (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF962C)
## 题目分析

观察到位数最大为 $9$，$O(n!)$ 可过，暴力搜索。

按位搜索，选择删或不删，并记录在一个字符串内。

搜索到尽头后，类比快读，将字符串转换为十进制数，判断开方后是否为整数，并更新答案。

最后注意处理前导零的情况。

细节看代码。

## code

喜提最优解。

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 200010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int len, ans = 1e9;
char c[N], str[N];

inline bool check(int tot)
{
	double num = 0; 
	for (rei i = 1; i <= tot; i++) num = num * 10 + str[i] - 48;
	double ret = sqrt(num);
	return (ret == (int)ret);
}

inline void dfs(int k, int tot)
{
	if (k > len)
	{
		if (tot && check(tot)) ans = min(len - tot, ans);
		return;
	} 
	dfs(k + 1, tot);
	if (c[k] == '0' && !tot) return;
	str[++tot] = c[k];
	dfs(k + 1, tot);
}

int main()
{
	scanf("%s", c + 1); len = strlen(c + 1);
	dfs(1, 0);
	printf("%d", (ans == 1e9 ? -1 : ans));
	return 0;
}
```


---

## 作者：ChenJr (赞：1)

	题意：给你一个大小在1到2e9的数，问能否删去部分数字，使这个数成为一个平方数，若能，则输出最少需要删除多少个数字使得原来的数成为一个平方数，否则输出-1。
    分析：拿到题目看到数据范围：n最大2e9，因此直接大暴力估计会超时。然而因为题目要求是要删除位数，故联想到数位dp。先存储每一位的数字，然后进行dfs记录最小操作数即可。
    
  ```cpp
#include <bits/stdc++.h>
#define maxn 10005
using namespace std;
const int INF=0x3f3f3f3f;
int bit[maxn],res;//bit数组存储位数，res记录结果
int cnt=0;//统计总位数大小
void getbit(int x){//获取一个数上各个位上的数字
    while(x){
        bit[++cnt]=x%10;
        x/=10;
    }
}
void dfs(int x,int num,int lowbit)//x代表枚举个数，num代表当前的数，lowbit代表当前的位数
{
	int tmp=num;
	int cntt=0;//当前的数的位数
	while(tmp) tmp/=10,cntt++;//获取当前数的位数
	int q=sqrt(num);//求当前的开根
	if(num==q*q) res=min(cnt-cntt,res);//判断是否满足平方数，如果是，记录位数差的最小值
	if(lowbit>=cnt) return;//如果当前的位数大于总位数，返回
	for(int i=lowbit+1;i<=cnt;i++) //从当前位数枚举到总位数
        dfs(x+1,num*10+bit[i],i);//不断递归下去求解
}
int main(){
    //startcoding
    int n;
	cin>>n;//输入数
	getbit(n);//获取位数
	res=INF;//初始值赋予INF
	reverse(bit+1,bit+1+cnt);//bit数组所存储的位数与实际位数相反，因此要反转一下
	dfs(1,0,0);//dfs统计答案
	if(res==cnt) puts("-1"); //如果答案数刚好等于总位数，则不存在
	else cout<<res<<endl;//否则输出答案
    return 0;
}

```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定一个不含前导 0 的正整数 $n(1\le n\le2×10^9)$，你每次可以选取这个数的任意一位删去，但是得到的数不能含前导 0，问你最少删去几位这个数才变成完全平方数，如果不可能，输出 $-1$。

## 思路

因为原数字最多为十位数，因此我们可以考虑时间复杂度为 $O(n!)$ 的暴力枚举：从删去 0 个，删去 1 个……一直枚举到删至只剩下一个，枚举删去哪些，留下哪些，把所有情况都试一遍即可，注意对前导 0 的判断，只要一可以，就直接输出删去的个数，结束程序。若全部试了一遍都不行，输出 $-1$。

关键点：

暴力枚举可以使用全排列，开一个数组，0 代表要删去，1 代表保留下来。

判断前导 0 ：如果第一个保留下来的数字为 0，那就直接跳过这种情况。

判断是否为完全平方数：若原数为 $sum$。则判断条件为 $(\lfloor \sqrt{sum}\rfloor)^2=sum$，代码实现如下：

```cpp
floor(sqrt(sum))*floor(sqrt(sum))==sum
```

这道题就这样完美的解决了，最后抛出个问题给大家思考：如果 $1\le n\le10^{18}$，那该如何解决呢。提示：时间复杂度约 $O(2^{\lg n})$，枚举每个数字是否选。

## 代码

下面放上我的代码。希望大家不要抄袭！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[20],m[20],c,f[10],d;
bool b;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    while(n>0){
        a[c++]=n%10;
        n/=10;
    }
    for(int i=0;i<c;i++)f[i]=1;
    for(int i=0;i<c;i++)m[i]=a[c-i-1];
    while(1){
	do{
	    int sum=0;
	    bool p=0;
	    for(int i=0;i<c;i++){
		if(f[i]){
		    sum=sum*10+m[i];
		    if(m[i]==0&&p==0)break;
		    p=1;	
		}
	    }
	    if(p&&floor(sqrt(sum))*floor(sqrt(sum))==sum){
	        cout<<d<<endl;
	        return 0;
	    }
	}while(next_permutation(f,f+c));
	f[d++]=0;
	if(d==c){
	    b=1;
	    break;
	}	
    }
	if(b==1)cout<<-1<<endl;
	return 0;
}
```


---

## 作者：RNTBW (赞：0)

## 题意

给一个数，要找出使这个数成为完全平方数的最小删数个数。

## 思路

一看这个数据范围，$n\leqslant2\times10^9$，意思就是说 $n$ 最多有九位。

再看到 _可以删除其中的一些位_， 

那这不就是个搜吗。

于是直接掏出 DFS 祭天。(~~还祭了五次，只能说我太蒟蒻了~~)

有人用了暴力，不过我本人蒟蒻得连暴力都看不懂，还是 DFS 吧。

最开始本蒟蒻想限定位数，WA 得很惨...

后来改用 ``bool`` 数组判断一个数的可行性，加了算位数的操作，才 A 掉了它。

## 代码解析

+ 用两个参数 $K , S$ 表示上一个选了第 $K$ 个数(接下来只能从 $K+1$ 开始搜)，现在的数是 $S$。

+ 每次对 $S$ 取位数（简称 ``ws``），如果 $S$ 是完全平方数就将 ``ws`` 标记——**可以取到位数为** ``ws`` **的数**。

+ 最后 ``for`` 一下判断 ``i`` 是否被标记，取最大值。

+ ``i`` 一定要**从大到小**循环，否则 TLE 两行泪！

+ 最最最后，我们将输入的 ``char`` 数组进行处理前导零，并将其转换成 ``int`` 类型。（好算）（48是 ASCII 的0）
$$
a\left[i-q+1\right]=c_i-48
$$
具体看代码~
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[10];
int a[10];
int n,i,j,q;
bool f[10];
void dfs(int k,int s)
{
	int tmp=s;
	int ws=0;//位数
	while(tmp) tmp/=10,ws++;//求位数
	int nw=sqrt(s);
	if(nw*nw==s)f[ws]=1;//标记
	if(k>=n)return;//如果上一个取的数的位置在n之外就return
	for(int i=k+1;i<=n;i++)
		dfs(i,s*10+a[i]);//递归DFS
}
int main()
{
	scanf("%s",c);
	n=strlen(c);
	while(c[i]=='0') i++,q++;//q是c数组的前导零的位置
	for(i=q;i<n;i++) a[i-q+1]=c[i]-'0';//处理前导零
	dfs(0,0);//初始上一个选了第0个数，当前数为零
	for(i=n;i>0;i--)
	{
		if(f[i])
		{printf("%d",n-i);return 0;//有标记就输出，第一个就是最大的
		}
	}
	printf("-1");
	return 0;//OVER~~
}
```

---

## 作者：千年陈皮精 (赞：0)

这一题不是很难，思路对了就行了。~~但是我调试了一个小时。~~
### 思路
把**正整数**拆分出来存入一个数组里，再用一个变量记录位数，枚举**平方数**，把**平方数**也拆拆分出来存入一个数组里，也用一个变量记录位数，接着判断删掉后能不能变成一个平方数。

------------
整体思路就是这样，其他的注释看代码吧。
### 代码
```c++
#include<bits/stdc++.h>
using namespace std;
long long n,s,b,wwss,ans=300000000000,sum;    //b= 正整数 的位数，wwss=枚举的 平方数 的位数，sum=对上了的数量。 
int a[15],c[15];
int main(){
	cin>>n;
	for(int i=n;i>0;i/=10)
		b++;    //累加 正整数 位数。

	for(int i=n,j=b-1;i>0;i/=10,j--)
		a[j]=i%10;    //把 正整数 一位一位存进去，倒着存入是为了方便。

	for(s=sqrt(n);s>=1;s--)
	{
		wwss=0;    //清零 平方数 的位数。 
		sum=0;    //清零sum。 
		for(int i=s*s;i>0;i/=10)
			wwss++;    //累加 平方数 位数。
		for(int i=s*s,j=wwss-1;i>0;i/=10,j--)
			c[j]=i%10;    //把 平方数 一位一位存进去，无需倒着存入了。
		for(int i=0;i<b;i++)
			if(c[sum]==a[i])sum++;    //判断删掉后能不能变成一个平方数。
		if(sum>=wwss)    //如果和 正整数 对上的数量大于 平方数 的位数的话，ans存起来。
		{
			cout<<b-wwss;
			return 0;
		}	
	}
	cout<<-1;    //无解输出-1。
 	return 0;
}
```

---

