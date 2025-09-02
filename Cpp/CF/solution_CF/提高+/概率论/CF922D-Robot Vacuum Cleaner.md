# Robot Vacuum Cleaner

## 题目描述

Pushok the dog has been chasing Imp for a few hours already.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/829d42ff73514382387680ad82853edceea77a87.png)Fortunately, Imp knows that Pushok is afraid of a robot vacuum cleaner.

While moving, the robot generates a string $ t $ consisting of letters 's' and 'h', that produces a lot of noise. We define noise of string $ t $ as the number of occurrences of string "sh" as a subsequence in it, in other words, the number of such pairs $ (i,j) $ , that $ i<j $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/f1a56c1d084d739e6652be99271753eea487f10e.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/1c020fe0ca945d3f2fc54f71a604c6ab2188fcee.png).

The robot is off at the moment. Imp knows that it has a sequence of strings $ t_{i} $ in its memory, and he can arbitrary change their order. When the robot is started, it generates the string $ t $ as a concatenation of these strings in the given order. The noise of the resulting string equals the noise of this concatenation.

Help Imp to find the maximum noise he can achieve by changing the order of the strings.

## 说明/提示

The optimal concatenation in the first sample is $ ssshhshhhs $ .

## 样例 #1

### 输入

```
4
ssh
hs
s
hhhs
```

### 输出

```
18
```

## 样例 #2

### 输入

```
2
h
s
```

### 输出

```
1
```

# 题解

## 作者：MattL (赞：8)

[洛谷链接](https://www.luogu.com.cn/problem/CF922D) & [原题链接](http://codeforces.com/problemset/problem/922/D)

---
我们先把题意转化一下：

先把给出的字符串按任意顺序拼成总串，再交换相邻的字符串，使得得分最大。

---

我们发现的规律：

1. 相邻字符串交换，不影响各自得分。
2. 相邻字符串交换，不影响前后字符串得分。

根据我们发现的规律，我们只需要关注交换相邻字符串是否得分更大即可。

---
设 $s_i$ 和 $h_i$ 分别表示串 $i$ 有 $s$ 和 $h$ 个字符。

串 $i$ 和 $i+1$ 交换前的得分：
$$s_i\times h_{i+1}$$
交换后的得分：
$$s_{i+1}\times h_i$$
要是交换后的得分比原来的大，选择交换相邻的串 $i$ 和 $j$ ，这样得分就可以获得最大值。

---
最后上代码前献上一句话：

**十年 OI 一场空，忘开 ```long long``` 见祖宗**

```cpp
#include <bits/stdc++.h>
using namespace std;
struct qp//定义结构体
{
    long long s,h;
}a[111111];
long long n,ans,cnt;
string s;
bool cmp(qp q,qp w)
{
    return q.s*w.h>w.s*q.h;//sort 的判断函数，其实也可以重载运算符
}
int main()
{
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        cin>>s;
        for(long long o=0;o<s.size();o++)
        {
            if(s[o]=='s')
                a[i].s++;
            if(s[o]=='h')
                a[i].h++,ans+=a[i].s;//别忘了加上自身得分
        }
    }
    sort(a+1,a+n+1,cmp);//大的放前面，就是取最优得分
    for(long long i=1;i<=n;i++)
    {
        ans+=cnt*a[i].h;//累加连续两个字符串的得分
        cnt+=a[i].s;//前缀和
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：chlchl (赞：5)

## 前言
不得不说，作为某某机构 CSP-J 某一场模拟赛的第四题，这道题还是有点难度的（蒟蒻第一次写蓝题题解，如有不足请见谅）。

## 题目意思
题目翻译就是题目意思，没什么好讲的。

## 主要思路
本题主要算法是贪心。

这道题最难想的地方在于如何将**字符串排序**。如果想要**组成的字符串 $sh$ 子序列数量尽量大**，第一反应是让每个 $h$ 的前面有尽可能多的 $s$。但是，如果单纯地按照每个字符串前缀 $s$ 或者是后缀 $h$ 排序，并没有什么用处。

其实我们一开始的思路是对的。对字符串进一步观察，很容易就会发现以下几个点：
1. **无论怎么变换，每个字符串自己所作出的贡献是一样的**。
2. **如果考虑相邻两个字符串变换，对前后并没有影响。**
3. **如果要求两个字符串是否需要交换，只需比较他们交换前后所组成的 $sh$ 串数量即可。**

因此，排序规则（也就是贪心策略）就是按照**相邻两个字符串交换前后所组成的 $sh$ 串数量从大到小**排序。

现在，问题转化成如何**求出相邻两个字符串所组成的 $sh$ 串个数**。

对于每个字符串，我们先**预先求它 $s$ 的数量（$sum_s$）和 $h$ 的数量（$sum_h$）**。

接下来的步骤用文字不好说明，我举个例子让大家理解。

就用样例中其中两个字符串吧：``ssh``（设这个字符串为 $S_1$） 和 ``hs``（设这个字符串为 $S_2$）。

首先知道以下四个信息：

$S_1sum_s = 2$，$S_1sum_h = 1$；

$S_2sum_s = 1$，$S_2sum_h = 1$。

- 如果组成的字符串为 ``sshhs``，那么两个字符串之间组成的 $sh$ 串数量应该是 $S_1sum_s\times S_2sum_h=2$（**前面 $s$ 数量 $\times$ 后面 $h$ 数量**）。
- 如果组成的字符串为 ``hsssh``，那么两个字符串之间组成的 $sh$ 串数量应该是 $S_2sum_s\times S_1sum_h=1$（同理）。

看完这个这例子，相信大家都懂了吧？

 ~~懂了，但是没有完全懂！~~

相信有部分 OIer 会问：如果这样算，那字符串自己的子序列数量不就被忽略了吗？

我在前面说过，**无论怎么变换，每个字符串自己所作出的贡献是一样的**。我们**只需要比较交换前后横跨两个字符串的子序列数量**。至于自己本身的子序列数量，就无关紧要了。

现在，我们已经确定好了字符串的顺序，拼好了那个字符串。接下来，就是统计这个新的字符串到底有多少个子序列了。

这里有个小技巧：先**求出整个字符串 $h$ 的数量（$cnth$），每遇见一个 $s$ 就将答案加上 $cnth$，如果当前是个 $h$，则 $cnth-1$。这样就能 $O(n)$ 求出子序列数量了。**

## 一些小坑
- 交换顺序时，记得把字符串也交换位置（推荐用结构体，结构体里面存一个字符串，$sum_s$ 和 $sum_h$）。
- 五年 OI 一场空，不开 ``long long`` 见祖宗。

## 代码
以下是参考代码。珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100000 + 10;
ll n, lens, cnts, cnth, ans;
struct sstring{
	string s;
	ll sums, sumh;
} str[N];//结构体
string anss;

bool cmp(sstring x, sstring y){return x.sums * y.sumh > x.sumh * y.sums;}//排序规则

int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> str[i].s;
		for(int j=0;j<str[i].s.length();j++)	if(str[i].s[j] == 's')	str[i].sums++;
		for(int j=0;j<str[i].s.length();j++)	if(str[i].s[j] == 'h')	str[i].sumh++;
		//预处理求出每个字符串 s, h 的数量 
	}
	sort(str + 1, str + 1 + n, cmp);
	for(int i=1;i<=n;i++){
		anss += str[i].s;//最终字符串
		cnth += str[i].sumh;//事先求出 h 的数量
	}
	lens = anss.length();
	for(int i=0;i<lens;i++){//巧妙的思想 
		if(anss[i] == 's')	ans += cnth;//如果遇到一个s，加上后面h的数量（一定正确） 
		if(anss[i] == 'h')	cnth--;//因为如果遇到在s前面的h，就被减掉了，不重不漏 
		if(cnth == 0)	break; //一个小优化
	}
	cout << ans << endl;
	return 0;
}
```
本篇题解到此结束，如果对你有帮助，别忘了点个赞哦！

---

## 作者：Xdl_rp (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF922D)

solution
------------

这道题我们考虑**贪心**

- 我们可以先将每一个字符串进行一个计算 `sh` 的操作（也就是说计算这个序列一共有多少个 `sh` 这个序列）

```cpp
int cal(string x) {
	int cnt = 0, sum = 0;//s的数量，总共有多少个
	for (int i = 0; i < x.size(); i++) x[i] == 's' ? ++cnt : sum += cnt;//如果当前字符为s，则cnt加1，否则（也就是h）就让答案加上当前s的数量（cnt），这里cnt没必要清空。
	return sum;//返回
}
```

- 这时候我们可以将整个字符串集合拍一个序，按照字符串（$x$）的 `cal` 值从大到小进行排序，然后将排序后的字符串集合一个连着一个拼在一起。

```cpp
bool cmp(string x, string y) {return cal(x + y) > cal(y + x);}//先x后y和先y后x进行比较
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);//排序
	for (int i = 1; i <= n; i++) tmp += a[i];//拼起来
	printf("%lld\n", cal(tmp));//计算最后的答案
	return 0;
}
```

最后附上~~不压行~~的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//记得一定要开long long！！
const int N = 1e5 + 10;
int n;
string a[N], tmp;
int cal(string x) {
	int cnt = 0, sum = 0;
	for (int i = 0; i < x.size(); i++) x[i] == 's' ? ++cnt : sum += cnt;
	return sum;
}
bool cmp(string x, string y) {return cal(x + y) > cal(y + x);}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) tmp += a[i];
	printf("%lld\n", cal(tmp));
	return 0;
}
```

补充一下：这题一定要开 long long


---

## 作者：Inui_Sana (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF922D)

解题思路：贪心+排序

我们先想一想，如果有一个只含 s 和 h 的字符串，怎么求出它含有的 sh 字串的个数呢？很简单，对于每个 h，看它前面有多少个 s，相加即可。

回到这道题上，我们很容易就可以发现，交换相邻的两个串，对其他的串是没有影响的。所以我们很容易可以写出排序的 cmp 函数：

```cpp
inline bool cmp(node a,node b){return a.fi*b.se>a.se*b.fi;}
```

最后再进行统计即可。

code：

```cpp
int n;
ll ans;
string str;
struct node{
	ll s,h;
}d[maxn];
inline bool cmp(node a,node b){return a.s*b.h>a.h*b.s;}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>str;
		for(int j=0;j<str.size();j++){
			d[i].s+=str[j]=='s';
			d[i].h+=str[j]=='h';
			ans+=(str[j]=='h')*d[i].s;//先计算该串内的sh子序列数
		}
	}
	sort(d+1,d+n+1,cmp);
	ll sum=0;
	for(int i=1;i<=n;i++)ans+=sum*d[i].h,sum+=d[i].s;//再计算不同串之间的
	printf("%lld",ans);
}
```

---

## 作者：Prurite (赞：1)

## 思路
直接贪心，将每个字符串按照s的比例排序，比例大的排在前面，最后连接到一起再统计所能产生的子序列就行了。统计的时候有一些骚操作：

1. 不用“连接”到一起，直接在原字符串数组里统计
2. 用一个变量存储出现过的s的数量，遇到一个h直接把子序列数加上之前的s的数量

（不理解就看代码吧）

注意最后统计的时候要用long long。

## 代码
有注释
```
#include <cstdio>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN=1e5+1, MAXSL=1e5+1;
int n;
string s[MAXN];
map<string, int> scount;
//预处理出每个串内的s的数量，用一个map存

inline int min( int a, int b ) { return a<b?a:b; }

inline bool cmp( string a, string b )
{
    return scount[a]*b.length() > scount[b]*a.length(); 
    //按照比例排序，利用预处理的s的数量和交叉相乘（把除变成乘）优化
}

inline long long check( )
{
    long long power=0, noise=0;
    for ( int i=1; i<=n; i++ )
        for ( int j=0; j<s[i].length(); j++ )
        {
            if ( s[i][j]=='s' )
                power++;
            if ( s[i][j]=='h' )
                noise+=power;
        }
    return noise;
    //统计子序列数量，变量名此处的意义见英文题面
}

int main()
{
    while ( scanf( "%d", &n )!=-1 ) //预备多组数据
    {
        char s1[MAXSL];
        for ( int i=1; i<=n; i++ )
        {
            scanf( "%s", s1 );
            int scount1=0;
            for ( int j=0; s1[j]!=0; j++ )
                if ( s1[j]=='s' )
                    scount1++;
            s[i]=s1;
            scount[s[i]]=scount1; 
            //读入字符串并预处理s的数量
        }
        sort( s+1, s+n+1, cmp ); //排序
        printf( "%lld\n", check( ) ); //输出
    }
    return 0;
}
```
[提交记录 用时: 6307ms / 内存: 6424KB](https://www.luogu.org/record/show?rid=6635616)

---

## 作者：XL4453 (赞：0)

### 解题思路：

先假设随便取任意一个序列，然后考虑如何交换相邻的两个才能使得价值更大。

首先发现，无论两个相邻的串如何交换，都不会影响每一段各自的贡献（包括前面的、后面的和自身），那么就只需要考虑每一串和其他串联合起来产生的贡献。

然后还发现，由于是相邻串交换，对于后面的和前面的也都没有影响，所以总够就只需要考虑这两个串自身之间的贡献是否在交换后更大了。

那么设：第一个串有 $s_1$ 个 s 字符，$h_1$ 个 h 字符，第二个串有 $s_2$ 个 s 字符，$h_2$ 个 h 字符。

在交换之前两个相邻串产生了：$s_1\times h_2$ 的贡献，在交换后产生了：$s_2\times h_1$ 的贡献，只需要比较这两个就好了。

-------------

假如将上面的两个式子变一下形，可以得到：$\dfrac{s_1}{h_1}$ 和 $\dfrac{s_2}{h_2}$ 可以理解为在每一个串中 s 字符的“密度”，而排序就是要将“密度”大的放到前面去，似乎更好理解一点。

------------
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	long long s,h;
	bool operator <(node a){
		return s*a.h>h*a.s;
	}
}e[100005];
long long n;
long long ans,tots;
string a;
int main(){
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		cin>>a;
		for(long long j=0;j<a.length();j++){
			if(a[j]=='s')e[i].s++;
			if(a[j]=='h')e[i].h++,ans+=e[i].s;
		}
	}
	sort(e+1,e+1+n);
	for(long long i=1;i<=n;i++){
		ans+=tots*e[i].h;
		tots+=e[i].s;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：JK_LOVER (赞：0)

## 题意
给你 $n$ 个字符串，求出一个排列方式，使 $ans$ 最大。
$$
ans= \sum_{i=1}^{tot} ([ch[i]=h]\times \sum_j^{j<i}[ch[j]=s])
$$

[QWQ](https://www.luogu.com.cn/blog/xzc/solution-cf922d)

## 分析
由这个 $ans$ 的计算方式可知，对于每个 $ch[i] = h$ 我们应该让它前面的 $s$ 个数尽量多。
- 对每个串，我们进行单独分析。我们可以先求出每个串自己的贡献，这一部分的贡献也不会随排列的变化而变化。
- 那么它对于其他串的贡献就是，令每个串 $h$ 的个数为 $sum[i][1]$ ， $s$ 的个数为 $sum[i][0]$
$$
val[n] = sum[i][1]\times(\sum_{i=1}^{n-1} sum[i][0])
$$
$$
ans = \sum_{i=0}^n (val[i]+\text{自己的贡献})
$$
对与两个串来说，如果交换两个的顺序会更优，那么一定满足
$$
val[i] < val[j] \Rightarrow val[i]-val[j]<0
$$
所以只需要考虑交换之后的变化要更优即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 1e5+10;
struct S{
	int sum[2];
	int len;
	int val;
}s[N];
char ch[N];
int n;
bool cmp(S a,S b)
{
	return a.sum[1] * b.sum[0] < a.sum[0] * b.sum[1];
}
signed main()
{
	cin>>n;
	for(int j = 1;j <= n;j++)
	{
		scanf("%s",ch+1);
		s[j].len = strlen(ch+1);
		for(int i = 1;i <= s[j].len;i++)
		{
			s[j].sum[1] += (ch[i]=='h');
			s[j].sum[0] += (ch[i]=='s');
			if(ch[i]=='h')
			{
				s[j].val += s[j].sum[0];
			}
		}
	}
	sort(s+1,s+1+n,cmp);
	int ans = 0,sum = 0;
	for(int i = 1;i <= n;i++)
	{
		ans = (ans + s[i].sum[1] * sum);
		ans = (ans + s[i].val);
		sum += s[i].sum[0];
	}
	cout<<ans<<endl;
	return 0;
}
```



---

