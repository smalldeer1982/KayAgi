# Dreamoon and WiFi

## 题目描述

Dreamoon is standing at the position $ 0 $ on a number line. Drazil is sending a list of commands through Wi-Fi to Dreamoon's smartphone and Dreamoon follows them.

Each command is one of the following two types:

1. Go 1 unit towards the positive direction, denoted as '+'
2. Go 1 unit towards the negative direction, denoted as '-'

But the Wi-Fi condition is so poor that Dreamoon's smartphone reports some of the commands can't be recognized and Dreamoon knows that some of them might even be wrong though successfully recognized. Dreamoon decides to follow every recognized command and toss a fair coin to decide those unrecognized ones (that means, he moves to the $ 1 $ unit to the negative or positive direction with the same probability $ 0.5 $ ).

You are given an original list of commands sent by Drazil and list received by Dreamoon. What is the probability that Dreamoon ends in the position originally supposed to be final by Drazil's commands?

## 说明/提示

Dreamoon is standing at the position $ 0 $ on a number line. Drazil is sending a list of commands through Wi-Fi to Dreamoon's smartphone and Dreamoon follows them.

Each command is one of the following two types:

1. Go 1 unit towards the positive direction, denoted as '+'
2. Go 1 unit towards the negative direction, denoted as '-'

But the Wi-Fi condition is so poor that Dreamoon's smartphone reports some of the commands can't be recognized and Dreamoon knows that some of them might even be wrong though successfully recognized. Dreamoon decides to follow every recognized command and toss a fair coin to decide those unrecognized ones (that means, he moves to the $ 1 $ unit to the negative or positive direction with the same probability $ 0.5 $ ).

You are given an original list of commands sent by Drazil and list received by Dreamoon. What is the probability that Dreamoon ends in the position originally supposed to be final by Drazil's commands?

## 样例 #1

### 输入

```
++-+-
+-+-+
```

### 输出

```
1.000000000000
```

## 样例 #2

### 输入

```
+-+-
+-??
```

### 输出

```
0.500000000000
```

## 样例 #3

### 输入

```
+++
??-
```

### 输出

```
0.000000000000
```

# 题解

## 作者：Dws_t7760 (赞：4)

一道简单的深搜题。

我们首先根据第一个字符串判断 Wifi 的位置，在对第二个字符串进行深搜。

深搜思路：逐个读取第二个字符串的字符，如果不为为 `?`，则按照要求走，否则两种情况都走一遍，进入下一轮深搜。如果最后能到达终点，则将变量 $s2$ 加一。

最后我们将 $s2$ 除以情况的总数，得到答案。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
string a,b;
long long n,endd,s1=1,s2;
void dfs(long long p,long long t) {
	if(t==n) {
		if(p==endd) s2++;
		return;
	}
	if(b[t]=='+'||b[t]=='?') dfs(p+1,t+1);
	if(b[t]=='-'||b[t]=='?') dfs(p-1,t+1);
}
int main() {
	cin>>a>>b;
	n=a.length();
	for(int i=0;i<n;i++) a[i]=='+'?endd++:endd--;
	for(int i=0;i<n;i++) if(b[i]=='?') s1*=2;
	dfs(0,0);
	cout<<fixed<<setprecision(12)<<1.0*s2/s1;
	return 0;
}
```


---

## 作者：Grisses (赞：2)

你需要按照一个字符串行走，但你收到了另一个字符串，问你依然在最后走到正确的地方的概率。

看看数据范围，10。显然暴搜，最后对于所有的情况算到达的情况的占比。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,k,ans,sum;
  char a[15],b[15];
  void dfs(int x,int cnt){
      if(x>n){
          sum++;//完了
          if(cnt==k)ans++;//成功到达
          return;
      }
      if(b[x]=='+')dfs(x+1,cnt+1);
      else if(b[x]=='-')dfs(x+1,cnt-1);
      else{
          dfs(x+1,cnt-1);
          dfs(x+1,cnt+1);//‘?’枚举
      }
  }
  signed main()
  {
      scanf("%s%s",a+1,b+1);
      n=strlen(a+1);
      for(int i=1;i<=n;i++){
          if(a[i]=='+')k++;
          else k--;
      }
      dfs(1,0);
      printf("%.7lf",1.0*ans/sum);//计算占比
      return 0;
  }
```

---

## 作者：zjhzs666 (赞：1)

# 题目意思
给你一个字符串 $a$ 和字符串 $b$,你要按照 $a$ 路线走一次，找到终点的位置，再按照 $b$ 路线走一次，求走到终点的概率为多少（保留 $12$ 位小数），已知当符号为加号时代表向前走一格，减号代表向后走一格，问号代表向前走一格或向后走一格，且你的初始位置为 $0$。
# 代码思路
~~这题比较水，可以直接暴力搜索。~~

首先我们按照 $a$ 路线走一次，找到终点的位置，然后从 $0$ 开始走，并从第 $1$ 个字符开始读取，当该字符不为 $?$ 时，我们就依题意走，如果该字符为 $?$，那么我们就分别把它当做 $+$ 和 $-$ 各走一遍，当路线走完时，就把 $zf$ 加上 $1$，再判断这个方案可否到达终点，如果可以就把 $kx$ 加上 $1$，最后输出。
# 代码实现
```
#include<bits/stdc++.h>
using namespace std;
string a,b;
int zf,kx,aa,zd;
void f(int n,int y){
	if(n>aa){
		zf++;//记录总方案
		if(y==zd)kx++;//记录可行解
		return ;
	}
	if(b[n]=='+')f(n+1,y+1);
	else if(b[n]=='-')f(n+1,y-1);
   	//当该字符不为?时
	else{
		f(n+1,y+1);
		f(n+1,y-1);
        	//当该字符为?时
	}
}
int main(){
	cin>>a>>b;
	aa=a.length();
	a=' '+a;
	b=' '+b; 
	for(int i=1;i<=aa;i++){
		if(a[i]=='+')zd++;
		if(a[i]=='-')zd--;
     		//求终点的位置
	}
	f(1,0);//开始搜索
	printf("%.12lf",kx*1.00/zf);
	return 0;
}
```


---

## 作者：tzc_wk (赞：1)

这道题是一道概率问题，有多种解法：

先讲一个比较暴力的算法，
bitmask算法

思路是：暴力枚举每一个'?'是加还是减，然后与已经走到路程相加，如果等于Wifi的位置那么方案数量+1，最后拿方案数除以2的('?'的个数)次方

时间复杂度O(|s| * 2的|s|次方)

代码：
```
#include <bits/stdc++.h>
using namespace std;
string s,t;
int a,b,cnt=0;//a用来记录Wifi的位置，b用来记录根据已知的信息所走到的位置
int main(){
	cout<<fixed<<setprecision(12);//调整输出精度
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		if(s[i]=='+')	a++;
		else if(s[i]=='-')	a--;
	}
	for(int i=0;i<t.size();i++){
		if(t[i]=='+')	b++,cnt++;
		else if(t[i]=='-')	b--,cnt++;
	}
	int ret=0;
	double ans;
	int n=t.size()-cnt;//n表示字符串t中'?'的个数
	for(int i=0;i<(1<<n);i++){//i用二进制表示每一位上如果是1，表示这个位置为+，否则这个位置为-
		int tmp=b;//tmp首先先赋上b因为b是已经确定的位所行走的路程，没法增加或减少
		for(int j=0;j<n;j++){
			if(i>>j&1)	tmp++;//bitmask基本技巧,判断从右往左数第(j+1)位是否为1
			else	tmp--;
		}
		if(tmp==a)	ret++;//结果加1
	}
	ans=(ret*1.0)/(double)(1<<n);
	cout<<ans<<endl;
}
```
然而还有一种更高效的解法：DP解法

dp[i][j]表示走到第i个问号,坐标为j时的概率.因为坐标可能为负,所以数组前移10距离.

状态转移方程：dp[i][j]=dp[i-1][j-1] * 0.5+dp[i-1][j+1] * 0.5

时间复杂度O(|s|方)
```
#include <bits/stdc++.h>
using namespace std;
double dp[40][40]={0};
string s,t;
int main(){
    cout<<fixed<<setprecision(12);
    cin>>s>>t;
    int len=s.size();
    int pos1=0,pos2=0,pos3=0;//跟上次a,b,n类似
    for (int i=0;i<len;i++){
        if(s[i]=='+')	pos1++;
        else	pos1--;
        if(t[i]=='+')	pos2++;
        else if (t[i]=='-')	pos2--;
        else	pos3++;
    }
    dp[0+10][pos2+10]=1;
    //将所有已经识别的信号扫过之后，也就是扫到第0个问号的所在的位置一定是pos2，因为整个dp都向右移了10格，所以要+10
    for(int i=1;i<=pos3;i++)
        for(int j=-10;j<=len;j++)
            dp[i+10][j+10]=dp[i-1+10][j-1+10]*0.5+dp[i-1+10][j+1+10]*0.5;//dp状态转移，上面已经解释过了
    cout<<dp[pos3+10][pos1+10];//输出扫完了所有问号位置pos1的概率
    return 0;
}
```

---

## 作者：wcop114514 (赞：0)

**题目分析**

第一个输入是距离 $+$ 是 $+1$,$-$ 是 $-1$。 初始为 $0$。

第二个输入才是寻找，字符用法与上方相同。若遇到 $?$ 两种都跑一遍，遇到终点次数 $+1$。

给各位大佬奉上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int m,a=1,cnt;
void dfs(int x,int y) {//暴力搜索
	if(s1.size()==y) {
		if(x==m)cnt++;//次数+1
		return;//结束
	}
	if(s2[y]=='+'||s2[y]=='?') dfs(x+1,y+1);
	if(s2[y]=='-'||s2[y]=='?') dfs(x-1,y+1);
		//加号+1，减号-1，问号都试一下
}
int main() {
	cin>>s1>>s2;//输入
	for(int i=0;i<s1.size();i++) {
		if(s1[i]=='+') m++;
		else m--;
	}//得出位置
	for(int i=0;i<s1.size();i++){
		if(s2[i]=='?') a*=2;
	}
	dfs(0,0);
	printf("%.12lf",1.0*cnt/a);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路分析
一道深度优先搜索题目，先按照第一个字符串走，得出 Wifi 的位置，然后对第二个字符串进行搜索。搜索方法：遍历第二个字符串，如果是问号就跑两种路线，跑下一轮搜索，是加号或减号就按要求跑。如果能到终点次数加一。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
long long n,m,s1=1,cnt;//定义变量
void dfs(long long x,long long y) {//搜索函数
	if(n==y) {
		if(x==m) cnt++;//次数+1
		return;//结束
	}
	if(b[y]=='+'||b[y]=='?') dfs(x+1,y+1);
	if(b[y]=='-'||b[y]=='?') dfs(x-1,y+1);
		//加号向前，减号向后，问号都跑一遍 
}
int main() {
	cin>>a>>b;//输入
	n=a.size();//获取长度
	for(int i=0;i<n;i++) {//遍历第一个字符串
		if(a[i]=='+') m++;
		else m--;
	}//得出WiFi位置
	for(int i=0;i<n;i++){
		if(b[i]=='?') s1*=2;
	}
	dfs(0,0);//遍历第二个字符串并进行搜索
	printf("%.12lf",1.0*cnt/s1);//输出（保留12位）
	return 0;//结束了
}
```

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Dreamoon and WiFi](https://www.luogu.com.cn/problem/CF476B)

## 算法思路

看到范围 $n \le 10$ 就可以想到用搜索。

我们先按照 $a$ 走一次找出 Wifi 的位置，在按照 $b$ 走一次，如果遇到 $+$ 就往前走一格，如果遇到 $-$ 就往后走一格，如果遇到 $?$ 就枚举往前和往后走一格。当步数走到 $n$ 时，就把方案数 $+1$，如果走到 Wifi 的位置了，就把合法方案数 $+1$，最后输出合法方案数 $\div$ 方案数就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
ll n,daan,sum,ans;
string a,b;
void dfs(ll cnt,ll now)//cnt代表已经走了cnt步，now代表现在在位置now 
{
	if(cnt==n)//如果已经走了n步 
	{
		sum++;//方案数++
		if(now==daan)//如果走到了答案 
		{
			ans++;//可行方案++ 
		}
		return;
	}
	if(b[cnt]=='+')//如果是+ 
	{
		dfs(cnt+1,now+1);//前进一步 
	}
	else if(b[cnt]=='-')//如果是- 
	{
		dfs(cnt+1,now-1);//后退一步 
	}
	else//如果是问号 
	{
		dfs(cnt+1,now+1);//前进一步 
		dfs(cnt+1,now-1);//后退一步
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>a>>b;
	n=a.size();
	for(int i=0;i<n;i++)
	{
		if(a[i]=='+')//找出答案为止 
		{
			daan++;
		}
		else
		{
			daan--;
		}
	}
	dfs(0,0);//dfs 
	cout<<setprecision(9)<<1.0*ans/sum<<"\n";//输出（记得保留9位小数） 
	return 0;
}
```

---

## 作者：I_have_been_here (赞：0)

# 题目分析

明显概率题，bitmask 正解，可是我真的太蒻了，但是，我们想一想，如果需要求到达终点的概率，那么我们只需要知道到达终点的方案有多少种，和总共的方案有多少种，除一下就搞定了。

# 思路解析

考虑直接使用爆搜，先对于原串计算出终点位置，在对于含有问号的字符串进行搜索，是加就加，是减就减，是问号就两种都搜一搜，最后统计即可，复杂度 $2$ 的串的长度次方。

# AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
char a[maxn], b[maxn];
int n, ans1, ans2, pos;
void dfs(int step, int now) {
	if (step > n) {
		ans1++; // 每一种方案都对总方案做贡献
		if (now == pos)
			ans2++; // 能到达终点的方案单独统计
		return;
	}
	if (b[step] == '+') dfs(step + 1, now + 1);
	else if (b[step] == '-') dfs(step + 1, now - 1);
	else {
		dfs(step + 1, now + 1);
		dfs(step + 1, now - 1);
	} // 分情况讨论即可
}
int main() {
	cin >> (a + 1) >> (b + 1);
	n = strlen(a + 1); 
	for (int i = 1; i <= n; i++) {
		if (a[i] == '+') pos++;
		if (a[i] == '-') pos--;
	} // 计算终点
	dfs(1, 0);
	printf("%.12lf", ans2 * 1.0 / ans1); // 概率
	return 0;
} 
```


---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF476B)

### 思路

~~爆搜水题。~~

首先根据第一个字符串找出终点，然后第二个字符串直接搜索，如果遇到问号就让他先 `+` 一次，再 `-` 一次，其余的直接跟题意来。最后把能够到终点的方案除以总方案就是概率。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[15],b[15];
int xx;
int ans,anss;
void dfs(int step,int x)
{
	if(step>n)
	{
		anss++;
		if(xx==x) ans++;
		return;
	}
	if(b[step]=='?')
	{
		dfs(step+1,x+1);
		dfs(step+1,x-1);
	}
	else if(b[step]=='-')
	{
		dfs(step+1,x-1);
	}
	else
	{
		dfs(step+1,x+1);
	}
}
int main()
{
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);
	for(int i=1;i<=n;++i)
	{
		if(a[i]=='+') xx++;
		else xx--;
	}
	dfs(1,0);
	printf("%.10lf",ans/(anss*1.0));
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

首先，可以得到标准的 WIFI 位置，然后，因为 $|s|\le 10$，我们可以直接对第二个字符串暴力求解，求出总共的方案数 $b$ 和正好到达标准位置的方案数 $a$，那么答案就是 $\dfrac{a}{b}$。

时间复杂度 $O(2^{|s|})$。

---

## 作者：tZEROちゃん (赞：0)

CF 里找 dp 题找到了这题，于是写了 dfs。

注意到字符串长度最多就 $10$（可以在原题面中看到），所以显然可以 dfs。

由于只有位置是我们关心的，所以我们首先需要记录确定的字符会带他到哪个位置。

可以记 $pos_1$ 表示正确的地点，那显然我们当 $s_i = \texttt{+}$ 时，就让 $pos_1$ 加上 $1$，否则减去 $1$，记 $pos_2$ 表示他已经确定的路线走到的位置，算法与 $pos_1$ 相同，不看问号就行。

我们记 $q$ 表示问号的数量，然后写一个 `dfs(q, pos1, pos2)`，当 $q = 0$ 时，若 $pos_1 = pos_2$，那就正确了，我们让计数器 $ans$ 加上 $1$。

然后每次 dfs，我们分别 `dfs(q - 1, pos1, pos2 + 1)` 和 `dfs(q - 1, pos1, pos2 - 1)`，$q-1$ 是因为每次 dfs 一次就会多一个确定的位置，$pos_2 \pm 1$ 是因为每次会向正方向一步或向负方向一步。

最后我们显然发现一共有 $2^q$ 种可能，那答案就是 $\dfrac{ans}{2^q}$。

所以可以轻松的写出代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans;

void dfs(int ques, int pos1, int pos2) {
  if (ques == 0) {
    if (pos1 == pos2) {
      ++ans;
    }
    return ;
  }
  dfs(ques - 1, pos1, pos2 + 1);
  dfs(ques - 1, pos1, pos2 - 1);
}

int main() {
  string s1, s2;
  cin >> s1 >> s2;
  int truepos = 0, walkpos = 0, questionMark = 0;
  for (auto i : s1) truepos += (i == '+' ? 1 : -1);
  for (auto i : s2) {
    if (i == '+') ++walkpos;
    else if (i == '-') --walkpos;
    else ++questionMark;
  }
  dfs(questionMark, truepos, walkpos);
  int tot = (1 << questionMark);
  cout << fixed << setprecision(12) << (double(ans) / tot) << endl;
}
```

---

## 作者：hensier (赞：0)

# 注意！绝非正解！
这里给出一种蒟蒻的思路。由于本蒟蒻不会$DP$，因而我们可采用二进制的思路——即，先处理输入，得到两种的最终坐标，然后一一枚举。

```cpp
#include<bits/stdc++.h>
#define ll long long
using std::queue;
queue<bool>s;
char ch;
ll x,y,z,cnt,ans,n;
void f(ll n)//递归二进制
{
    if(n>0)
    {
        f(n/2);
        s.push(n%2);
    }
}
int main()
{
    do//do-while输入
    {
        ch=getchar();
        if(ch!='\n')x+=ch=='+'?1:-1;//如果为+就加1否则减1
    }while(ch!='\n');
    do//同理
    {
        ch=getchar();
        if(ch!='\n')y+=ch=='+'?1:ch=='-'?-1:0;
        cnt+=ch=='?';
    }while(ch!='\n');
    if(!cnt)//如果没有问号的话要么是0要么是1
    {
        printf("%d",x==y);
        return 0;
    }
    n=1<<cnt;//左移速度更快，等同于pow(2,cnt)
    for(ll i=0;i<n;i++)//循环
    {
        z=y;//保存
        f(i);//二进制
        while(!s.empty())//队列出队
        {
            if(s.front())z++;//如果bool值为1就加1，否则减1
            else z--;
            s.pop();//弹出顶部元素
        }
        if(z==x)ans++;//ans加1
    }
    printf("%.10f",1.0*ans/n);
}
```

---

