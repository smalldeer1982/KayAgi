# Easy Strings Merging

## 题目描述

给定 $n$ 个 01 串，每次你可以从某个串开头移除一个字符并把它加入一个新串 $S$ 的末尾。最大化 $S$ 中相邻两个字符相同的对数。

## 说明/提示

### 样例解释

最优方案下，每次取的串的编号为 $1,1,2,1,2,3,1,2,3,2,3,3$，最终的 $S=000111111000$。

### 数据范围

**本题采用捆绑测试**

设 $s$ 表示输入的 01 串的长度之和。

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------: |
| $0$ | $5$ | $n=1$ |
| $1$ | $20$ | $n\le 2$，$s\le 10$ |
| $2$ | $25$ | $n\le 5$，$s\le 30$ |
| $3$ | $25$ | $n\le 100$，$s\le 200$ |
| $4$ | $25$ | 无特殊限制 |

对于所有数据，保证 $1\le n\le s\le 10^6$。

## 样例 #1

### 输入

```
3
0011
0110
1100```

### 输出

```
9```

# 题解

## 作者：HYdroKomide (赞：10)

### 题意：
题目里说的挺简洁明白的，换句话说也可以是最小化相邻字符不同的个数。

很明显，这个也可以理解成：每次取所有串前面一样的数，使取的次数最少。

### 思路：
首先，取的方法决定，该取一个数就一定要把这一个串前面的这个数全部取出来，所以一个串取的次数最少就是相邻字符不同的个数再 $+1$。

每次要把所有的串前面的数都取出来，所以每个串取的次数都应该考虑。整体能够取的次数就是所有串能取次数的最大值。

然后就出来一份代码：
```cpp
#include<iostream>
#include<cstring>
#define ri register int
using namespace std;
int n,l,tot,cnt,maxcnt;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(ri i=1;i<=n;i++){
		cin>>s;
		l=s.length(),cnt=0;
		tot+=l;//一共相邻的字符数，就是全部字符的个数-1
		for(ri j=1;j<l;j++)
			if(s[j]!=s[j-1])//求相邻字符不同的个数
				cnt++;
		maxcnt=cnt>maxcnt?cnt:maxcnt;//取最大值
	}
	tot--;
	cout<<tot-maxcnt<<endl;//最后减去不同的个数
	return 0;
}
```

然而只有 50pts。

原因应该很明显，一个串的开头可能是 $0$ 或者 $1$，但是要是取的话，第一次可能取的字符不能是这个串的开头。换句话说，第一次取的如果是 $0$，但是这个串的开头是 $1$，那么这个串暂时取不了，所以此时其实应该再多算一次。

所以我们对于每个串，都同时考虑最先取 $0$ 或 $1$ 的情况，然后取这两种情况的最优方案即可。

### 程序如下：
```cpp
#include<iostream>
#include<cstring>
#define ri register int
using namespace std;
int n,l,tot,cnt0,cnt1,maxcnt0,maxcnt1,maxcnt;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(ri i=1;i<=n;i++){
		cin>>s;
		l=s.length(),cnt0=cnt1=0;
		tot+=l;
		if(s[0]=='0')cnt1++;//如果字符串开头是0，那么一开始取1的次数+1
		if(s[0]=='1')cnt0++;//反之亦然
		for(ri j=1;j<l;j++)
			if(s[j]!=s[j-1])
				cnt0++,cnt1++;
		maxcnt0=cnt0>maxcnt0?cnt0:maxcnt0;
		maxcnt1=cnt1>maxcnt1?cnt1:maxcnt1;
	}
	maxcnt=min(maxcnt0,maxcnt1);//取其最小值
	tot--;
	cout<<tot-maxcnt<<endl;
	return 0;
}
```

### THE END

---

## 作者：VinstaG173 (赞：5)

怎么最近两场月赛的 A 都不够水了啊（

转化题意就是问最终字符串中段数的最小值。

显然有贪心策略：每次把所有串开头能取的同种字符取完放在最终字符串中成一段一定最优。比如：

$11000$ 和 $01100$，就先把它们最前面的所有 $0$ 都取出来，最终字符串中放入 $1$ 个 $0$，或者把它们最前面的所有 $1$ 都取出来，最终字符串中放入 $2$ 个 $1$。然后依此方式继续操作。

然后在这样的策略下，我们会发现一件事情：首先我们定下来我们的最终字符串第一段是 $0$ 还是 $1$，然后最终的段数就是照此规则对每个字符串分段后段数的最大值。比如：

以 $0$ 为第一段，$11000$ 和 $01100$ 都分成 $3$ 段，最终字符串 $0111100000$ 也分成 $3$ 段。

以 $1$ 为第一段，$11000$ 分成 $2$ 段，$01100$ 分成 $4$ 段，最终字符串 $1101100000$ 分成 $4$ 段。

于是我们只要分别计算一遍以 $0$ 和 $1$ 为第一段的段再取最小者即可。

Code:
```cpp
#include<cstdio>
#define rg register
int n,ans,t0,t1,tt0,tt1;
int main(){
	n=read();while(n--){
		char c=gc(),l0='0',l1='1';t0=t1=1;
		while(!isdigit(c))c=gc();while(isdigit(c)){
			(c!=l0)&&(l0=c,++t0),(c!=l1)&&(l1=c,++t1),c=gc(),++ans;
		}(t0>tt0)&&(tt0=t0),(t1>tt1)&&(tt1=t1);
	}return 0&printf("%d\n",ans-((tt0<tt1)?tt0:tt1));
}
```

---

## 作者：MY（一名蒟蒻） (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P8001)

算比较难的月赛 2A 了，整场只会这一道。

以为 2A 会很容易，所以一开始直接丢了个队列暴力，结果 [MLE](https://www.luogu.com.cn/record/66141344) 了。

推了一会儿性质想出来了。进入正题。

不妨设第一次拿了全部开头的 $0$ ，考虑拿第一次之后，全部字符串绝对都以 $1$ 开头，那么我们一定会拿走全部的 $1$ ，下一次全部字符串绝对都以 $0$ 开头，于是我们就会重复上面的过程直到拿完。

贪心正确性显然。可以发现方案实际上只有两种，只与第一次取出的是 $0$ 还是 $1$ 有关。

把两种方案跑出来之后取最大值即可。

### Talk is cheap, show me the code.

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

const int N=1e6+10;

int n;
char s[N];
struct node {int col,cnt;} q[N];
int ans[2][N];

int main()
{
//  freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	
	int tot;
	
	for(int i=1,m,l,r;i<=n;i++)
	{
		scanf(" %s",s);
		m=strlen(s);
		l=0; tot=0;
		for(r=1;r<m;r++)
		{
			if(s[l] != s[r])
				q[++tot]={s[l]-'0',r-l},l=r;
		}
		q[++tot]={s[l]-'0',r-l},l=r;
		if(q[1].col == 0) for(int i=1;i<=tot;i++) ans[0][i]+=q[i].cnt,ans[1][i+1]+=q[i].cnt;
		else for(int i=1;i<=tot;i++) ans[0][i+1]+=q[i].cnt,ans[1][i]+=q[i].cnt;
	}
	int ans1=0,ans2=0;
	for(int i=1;ans[0][i];i++) ans1+=ans[0][i]-1;
	for(int i=1;ans[1][i];i++) ans2+=ans[1][i]-1;
	
	printf("%d",ans1 > ans2? ans1:ans2);
//  fclose(stdin); fclose(stdout);
    return 0;
}
```

***Thanks for your reading !***

---

## 作者：Elgo87 (赞：4)

题意应该比较清楚了，在此就不多说了。

当字符串 $S$ 相邻两个数相同的对数最大时，很容易可以看出 $S$ 的连通块个数最少。

取出字符时，可以考虑先确定好第一个要取的数（$0$ 或 $1$），然后把读入的字符串以这个数开头的字符**全部取出**，当没有字符可取时，就切换当前取的数。

就拿样例来举个例子。

样例输入：

```
3
0011
0110
1100
```

首先考虑先取 $0$，把所有开头为 $0$ 的字符全部取出后，得到

```
11
110
1100
```

取完后再切换成取 $1$，得到

```
                       //这里有个空行，因为这一行已经全部被取出来了
0
00
```

最后切换成取 $0$，就可以把所有字符取出来了。

然后记录一下取出的串 $S$，它为 $000111111000$，然后直接求答案即可。

需要注意的是，在求解时需要同时考虑先取 $0$ 或先取 $1$，然后这两个求得的结果取 $\max$。

感觉数据造的有点水，这复杂度卡的很悬，但还是过了。

---

## 作者：yeshubo_qwq (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/P8001)
## 思路：贪心
显然，尽量让相同的字符在一起，可以最大化相邻两个字符相同的对数。

因此，我们第一次让开头是 $0$ 的串开头连续是 $0$ 的部分进去，第二次让剩下的开头是 $1$ 的串开头连续是 $1$ 的部分放进去……一直交替放到没有非空字串为止。

先放开头是 $1$ 的同理。

最后，在开头是 $0$ 和开头是 $1$ 中取一个最大值即可。

注意：一段连续的相同的子串相邻两个字符相同的对数并非这段子串的长度，而是其长度减一。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,s,j,l,mi,flag,ans,ans1,b[1000001],c[1000001],bb[1000001],d[1000001];
string s1;
vector<int> a[1000001];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>s1;
		l=s1.size();
		s=1;
		bb[i]=b[i]=s1[0]-'0';//开头是0还是1 
		for(j=1;j<l;j++)
			if(s1[j]==s1[j-1])s++;
			else{
				a[i].push_back(s);//用vector按连续相同的子串的长度存 
				s=1;
			}
		a[i].push_back(s);
	}
	for(i=1;i<=n;i++)d[i]=a[i].size(); 
	flag=1;
	/*
	c数组为vector中第几个
	d数组为vector长度 
	flag表示取开头为flag的串 
	*/ 
	for(;;){//开头0 
		flag=1-flag;ans1=ans;
		for(i=1;i<=n;i++)
			if(c[i]<d[i]&&b[i]==flag)ans+=a[i][c[i]],c[i]++,b[i]=1-b[i];
		if(ans1!=ans)ans--;//相邻两个字符相同的对数是其长度减一
		else break;//如果ans没有变化说明放完了 
	}
	mi=ans;
	for(i=1;i<=n;i++)b[i]=bb[i],c[i]=0;
	flag=0;ans=0;//还原被改变过的值 
	for(;;){//开头1 
		flag=1-flag;ans1=ans;
		for(i=1;i<=n;i++)
			if(c[i]<d[i]&&b[i]==flag)ans+=a[i][c[i]],c[i]++,b[i]=1-b[i];
		if(ans1!=ans)ans--;
		else break;
	}
	cout<<max(mi,ans);//最大数就是答案 
	return 0; 
}
```
~~不过，这个程序非常慢……~~

---

## 作者：a_grain (赞：2)



------------
[题面](https://www.luogu.com.cn/problem/P8001)


------------
通过题目可知，我们取字符时是可以连续取的，因此如果**取的字符**与**后一位字符**相等，则连续取最优。

因为这个策略，我们可以在读入中把相同的字符个数用一个二维数组来存，$j$ 为当前的字符，而 $i$，则是用来存取字符时的次序。

为什么会这样存呢？因为已经压缩过 $01$ 串，所以如果要取就是全取完，且在同一次中是可以任意调换取 $n$ 个 $01$ 串的顺序的，而 $01$ 串只有 $0$ 或 $1$ 这两种字符，自然是把它们各自凑在一起最优。

而读入后，便是枚举第一次取的是 $0$ 还是 $1$。

至于其余的解释，我会在代码注释中提起。


------------
**AC code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int bj,s1,s2,sum,n,i,len,j,f[1000001][2],t,ma;
char a[1000001];//存01串
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%s",a+1);
		len=strlen(a+1);
		t=0;//把取的次数清0
		for(j=1;j<=len;j++)
			if(a[j]!=a[j-1])f[++t][a[j]-'0']++;//char数组第0位默认为空格，++把自己也算上
			else f[t][a[j]-'0']++;//如果相等就当前次数的字符数量++
		ma=max(ma,t);//求每一个01串要做的次数的最大
	}
	//枚举先取1的情况的答案 
	bj=0;//没取的字符(变为int型) 
	s1=f[1][1]-1;//当前的对数 
	sum=f[1][0];//没取的字符个数，因为没取的就可以和后面的凑成一条长队 
	for(i=2;i<=ma;i++){
		s1+=sum+f[i][bj]-1;//sum+f[i][bj]-1为之前没取的和后面连起来的对数 
		bj=!bj;//换另一个字符不取 
		sum=f[i][bj];//更新没取字符的个数 
	}
	s1+=max(sum-1,0);//判断最后还有没有没取的个数，如果有答案再加，没有则加0
	//枚举先取0的情况的答案(注释同上) 
	bj=1;
	s2=f[1][0]-1;
	sum=f[1][1];
	for(i=2;i<=ma;i++){
		s2+=sum+f[i][bj]-1;
		bj=!bj;
		sum=f[i][bj];
	}
	s2+=max(sum-1,0);
	printf("%d\n",max(s1,s2));//输出两个答案中的最大对数 
}
```


------------
# The End.

---

## 作者：DPseud (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8001)

有些大佬用贪心做这道题，其实这道题直接模拟也是能过去的。

大致思路就是每次遍历数组，取走开头的连续 0 或 1，然后删除该段，遍历完后，我们需要判断字符串是否全部为空，如果不为空，那么就继续执行上述操作。

但是，开始从 0 或 1 取的结果是不一样的，举个例子：

```cpp
7
110
01
0000101110
1010
0
1
10
```

如果从 0 开始取，结果是 18，但若是从 1 开始取，结果则是 17。

所以，我们需要遍历数组两次，因为我的方法是将字符串删去子串而非减少长度，所以读入时就需要备份字符串。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[1111111],ss[1111111];//s是第一次取的字符串数组，ss是第二次取 
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
		ss[i]=s[i];//备份操作 
	}
	if(n==1)//这种操作因为要删除，所以n=1时很费时间，为了优化，我们可以进行特判 
	{
		int sss=0;
		for(int i=0;i<s[0].length();i++)
		{
			if(s[0][i]==s[0][i+1]&&i!=s[0].length()-1)sss++;
		}
		cout<<sss;
		return 0;
	}
	string st="";//取走的字符连起来放到st里 
	bool val=0;//第一次取的值 
	bool bb=1;//用于记录数组是否不为空，初始值一定要定为1 
	while(bb==true)
	{
		for(int i=0;i<n;i++)
		{
			if(s[i]=="")continue;//空串直接跳过 
			int tj=s[i].length();
			for(int j=0;j<s[i].length();j++)
			{
				if(s[i][j]!=val+48)
				{
					tj=j;//第一个不为当前要取走的坐标 
					break;
				}
			}
			for(int j=0;j<tj;j++)st+=s[i][j]; 
			s[i].erase(0,tj);//删去前面 
		}
		bb=0;
		for(int i=0;i<n;i++)
		{
			if(s[i]!="")bb=1;
		} 
		val=1-val;//这里其实相当于if(val==0)val=1;else val=0;的简写 
	}
	static int sum;
	for(int i=0;i<st.length();i++)
	{
		if(st[i]==st[i+1]&&i!=st.length()-1)sum++;//统计 
	}
	val=1;//初始值设为1 
	bb=1;
	st="";
	while(bb==true)//如上 
	{
		for(int i=0;i<n;i++)
		{
			if(ss[i]=="")continue;
			int tj=ss[i].length();
			for(int j=0;j<ss[i].length();j++)
			{
				if(ss[i][j]!=val+48)
				{
					tj=j;
					break;
				}
			}
			for(int j=0;j<tj;j++)st+=ss[i][j];
			ss[i].erase(0,tj);
		}
		bb=0;
		for(int i=0;i<n;i++)
		{
			if(ss[i]!="")bb=1;
		} 
		val=1-val;
	}
	static int sum2;
	for(int i=0;i<st.length();i++)
	{
		if(st[i]==st[i+1]&&i!=st.length()-1)sum2++;
	}
	if(sum2>sum)sum=sum2;//更新大小 
	cout<<sum;
 	return 0;
}
```


---

## 作者：Aurora_Borealis_ (赞：2)

看到题目求的是相邻两个字符相同的对数，想要让这个值最大，就要尽可能让相邻的 0（或 1）相同。那就暴力地每次都将每个串遍历一次，取走所有能取的 0（或 1）。由于从 0 开始取与从 1 开始取的结果可能不同，所以进行两次上述过程。

又有同学要问了：你这时间复杂度~~保熟~~能过吗？

全题最重点：$ s \leq 10^6 $。

$ O(n) $的东西完全能过。

代码：
```cpp
#include<iostream>
using namespace std;
int n,now[1000006];
int siz=0,siz2=0,lst,ans=0,ans2=0;
string s[1000006];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		siz+=s[i].size();
		now[i]=0;
	}
	siz2=siz,lst=0;
	while(siz){
		for(int i=1;i<=n;i++){
			if(s[i][now[i]]-'0'==lst){
				if(now[i]==s[i].size()) continue;
				while(s[i][now[i]]-'0'==lst&&now[i]<s[i].size()){
					now[i]++;
					siz--;
					ans++;
				}
			}
		}
		ans--;
		lst^=1;
	}
	for(int i=1;i<=n;i++){
		now[i]=0;
	}
	lst=1;
	while(siz2){
		for(int i=1;i<=n;i++){
			if(s[i][now[i]]-'0'==lst){
				if(now[i]==s[i].size()) continue;
				while(s[i][now[i]]-'0'==lst&&now[i]<s[i].size()){
					now[i]++;
					siz2--;
					ans2++;
				}
			}
		}
		ans2--;
		lst^=1;
	}
	cout<<max(ans,ans2);
	return 0;
} 
```


---

## 作者：Iratis (赞：1)

本解法相对于其它题解略麻烦，只是多提供一种解题思路。

题目既然要求相邻两个字符相同的对数最多，所以观察到可以满足贪心性质。

且我们发现倘若取出字符相同，那么与取的顺序无关，例如：

有字符串
```1100``` 和字符串 ```1000``` ，那么先取出第一个串的开头与先取出第二个串的开头所带来的结果是相同的。

所以我们只需要枚举第一步取的字符为 ```0``` 还是 ```1``` ，剩余可以使用队列随时维护。

代码如下：
```
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define push0(x,y) q0.push((rt){x,y})
#define push1(x,y) q1.push((rt){x,y})
int n;
int al;
int ans;
string s[1000001];
struct rt
{
	int x,y;
};
queue<rt> q0,q1;
void push(int x,int y)
{
	if(s[x][y]=='0')push0(x,y);
	else push1(x,y);
}
int solve0()
{
	int an=0;
	for(int i=1;i<=n;i++)push(i,0);
	if(q0.size()==0)return 0;
	int bj=0;
	for(int i=1;i<=al;i++)
	{
		if(bj==0)
		{
			if(q0.size()>0)
			{
				if(i!=1)an++;
				rt no=q0.front();
				q0.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
			else
			{
				bj=1;
				rt no=q1.front();
				q1.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
		}
		else
		{
			if(q1.size()>0)
			{
				if(i!=1)an++;
				rt no=q1.front();
				q1.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
			else
			{
				bj=0;
				rt no=q0.front();
				q0.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
		}
	}
	return an;
}
int solve1()
{
	int an=0;
	for(int i=1;i<=n;i++)push(i,0);
	if(q1.size()==0)return 0;
	int bj=1;
	for(int i=1;i<=al;i++)
	{
		if(bj==0)
		{
			if(q0.size()>0)
			{
				if(i!=1)an++;
				rt no=q0.front();
				q0.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
			else
			{
				bj=1;
				rt no=q1.front();
				q1.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
		}
		else
		{
			if(q1.size()>0)
			{
				if(i!=1)an++;
				rt no=q1.front();
				q1.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
			else
			{
				bj=0;
				rt no=q0.front();
				q0.pop();
				if(s[no.x].length()-1==no.y)continue;
				else push(no.x,no.y+1);
			}
		}
	}
	return an;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)cin>>s[i],al+=s[i].length();
//	sort(s+1,s+n+1);
	ans=max(ans,solve0());
	while(!q0.empty())q0.pop();
	while(!q1.empty())q1.pop();
	ans=max(ans,solve1());
	cout<<ans;
	return 0;
}
```

---

## 作者：xxasmcd (赞：1)

这道题可以把 n 个字符串看成一个整体，每次尽可能的把所有开头能取的 0 或 1 全部取完。因为开头一次要取的是 0 或 1 不确定，所以需要分别枚举，最后在两种情况中取最大即可。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans1=0,ans2=0,ans=0,sum=0;
struct node
{
    string s;
    int top;
}stu1[1000005],stu2[1000005];//分两种情况穷举s表示输入的字符串，top表示现在选到哪里
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)//输入初始化
    {
        cin>>stu1[i].s;
        stu1[i].top=stu2[i].top=0;
        stu2[i].s=stu1[i].s;
        ans+=(int)stu1[i].s.size();
    }
    int now=0;// now用来表示当前要取的是0还是1
    while(sum!=ans)
    {
        for(int i=1;i<=n;i++)
        {
            int len=stu1[i].s.size();
            if(stu1[i].top==len)continue;
            while(stu1[i].s[stu1[i].top]-'0'==now&&stu1[i].top<=len-1)//如果可以取
            {
                sum++;
                ans1++;
                stu1[i].top++;
            }
        }
        ans1--;//由于求的是连着的对数，每次计算还需要-1
        now^=1;
    }
    now=1,sum=0;//重新统计另一种情况
    while(sum!=ans)
    {
        for(int i=1;i<=n;i++)
        {
            int len=stu2[i].s.size();
            if(stu2[i].top==len)continue;
            while(stu2[i].s[stu2[i].top]-'0'==now&&stu2[i].top<=len-1)
            {
                sum++;
                ans2++;
                stu2[i].top++;
            }
        }
        ans2--;
        now^=1;
    }
    cout<<max(ans1,ans2);//答案取最大
    return 0;
}

```




---

## 作者：IYSY2009I (赞：0)

这道题应该是一道水红，可惜我考场上 sb 先写了 40min 搜索然后才想到正解，花了不到 30minA 掉。

这道题的做法是贪心。我们要让相邻两个字符相同的对数最大化，也就是让相邻两个字符不同的对数最小化。通过观察可以得知，答案 = 所有 01 串的总长度-相邻两个字符不同的对数。

那么我们就有了一个贪心策略。每轮一口气取走目前能取走的所有 0 或 1，知道全部取完了位置。那么我们可以发现。我们可以先取 0，再取 1，再取 0……或者先取 1，再取 0，再取 1……显然易见，最优解一定在这两种取法当中，比较一下就行了。

我们还是拿珂爱的样例来举个栗子。

我们来开一个数组 $cnt$,$cnt_i$ 表示第 $i$ 个 01 串目前要取的字符的下标。因为我们从 0 开始存，所以 $cnt$ 数组默认全为 0 就行。

所以一开始是这样的：

$cnt$:0 0 0

我们先来看一下先取 0 的方法，在经过一轮之后，$cnt$ 应该变化成这样：

$cnt$:2 1 0

然后再取 1：

$cnt$:3 2 1

然后再取 0：

$cnt$:3 3 3

然后我们发现所有的 01 串全部取完了，结束。

最后答案是：4+4+4-3=9，时间复杂度为 O(s)。

先取 1 同理，略。

最后附一下代码：

```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
string s[1000005];
int ls[1000005];
int cnt[1000005];
int hh;
int ans;
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		ls[i]=s[i].size();
		hh+=ls[i];
	}
	int flag=0;
	int ii=0;
	while(true){
		for(int i=1;i<=n;i++)
			if(cnt[i]<=ls[i]-1) goto otog1;
		break;
		otog1:;
		ii++;
		char c='0';
		if(flag==1) c='1';
		for(int i=1;i<=n;i++)
			while(s[i][cnt[i]]==c) cnt[i]++;
		if(flag==1) flag=0;
		else flag=1;
	}
	flag=1;
	int jj=0;
	for(int i=1;i<=n;i++)
		cnt[i]=0;
	while(true){
		for(int i=1;i<=n;i++)
			if(cnt[i]<=ls[i]-1) goto otog2;
		break;
		otog2:;
		jj++;
		char c='0';
		if(flag==1) c='1';
		for(int i=1;i<=n;i++)
			while(s[i][cnt[i]]==c) cnt[i]++;
		if(flag==1) flag=0;
		else flag=1;
	}
	ans=hh-min(ii,jj);
	printf("%d",ans); 
	return 0;
}
```

~~STL 和 goto 真好用~~

---

## 作者：_lfxxx_ (赞：0)

~~这 A 卡了我好久。~~

题意那么短就不赘述了。

首先有一个很明显的贪心就是每次取一个段都要取 $0$ 或 $1$ 时要取到不能再取为止。

那到底是先取 $0$ 还是 $1$ 呢？这时就要尝试两种方案最后分的段数选小的那个作为答案。

模拟的时候需要用开一个数组作为指针去扫，不然暴力会被卡到 $O(n^2)$。

献上我丑陋的代码：
```cpp
namespace solution{
	#define N 1000005
	string s[N];
	int p[N];
	int solve(int n,char f){
		int cnt(0);
		for(int i=1;i<=n;++i)
			p[i]=0;//清空指针
		while(n){
			++cnt;
			for(int i=1;i<=n;){
				while(p[i]<s[i].size()&&s[i][p[i]]==f)
					++p[i];//能取就取
				if(p[i]==s[i].size())
					swap(s[i],s[n]),swap(p[i],p[n]),--n;//扫完之后扔掉它，放到最后一个并总数减 1
				else
					++i;
			}
			f='0'+(f=='0');//取另一个
		}
		return cnt;
	}
	int main(){
		int n,sum(0);//sum 为总共多少字符
		cin>>n;
		for(int i=1;i<=n;++i)
			cin>>s[i],sum+=s[i].size();
		cout<<sum-min(solve(n,'0'),solve(n,'1'))<<endl;
		return 0;
	}
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定 $n$ 个长度和为 $s$ 的 01 串，每次你可以从某个串开头移除一个字符并把它加入一个新串 $S$ 的末尾。最大化 $S$ 中相邻两个字符相同的对数。

**数据范围：$1\leqslant n\leqslant s\leqslant 10^6$。**
## Solution
给出一个不需要脑子的方法。

一个比较显然的结论是，要使得 $S$ 中相邻两个字符相同的对数最大，就要交替着尽量连续地多取相同的数。因此，我们计算出从 $0$ 开始取和从 $1$ 开始取最后得到的 $S$ 中相邻两个字符相同的对数，取最大值即可。

计算 $S$ 中相邻两个字符相同的对数的具体实现见代码，利用了桶来实现，比较简洁。
## Code
```cpp
namespace Solution {
	const int N = 1e6 + 7;
	int n, len, sum[N]; string s[N];
	
	ii solve(int st) {
		F(int, i, 1, n) len += s[i].size();
		int mxl = 0, ans = 0;
		F(int, i, 1, n) {
			int num = (s[i][0] != st + '0'), l = s[i].size();
			sum[num]++;
			F(int, j, 1, l - 1) {
				if(s[i][j] != s[i][j - 1]) num++;
				sum[num]++;
			}
			mxl = max(mxl, l);
		}
		F(int, i, 0, mxl) {
			if(sum[i]) ans += (sum[i] - 1);
			sum[i] = 0;
		}
		return ans;
	}
	
	iv Main() {
#ifdef LOCAL
		double st = clock();
#endif
		read(n);
		F(int, i, 1, n) cin >> s[i];
		write(max(solve(0), solve(1)));
		return;
	}
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解
本题我采用的是一种模拟取数的思路。

如果前一个取的是 $1$，那么就把所有能取的 $1$ 都取完再开始取 $0$；前一个取的是 $0$ 也同理。每取完一个数字，就将它加到 `ans` 后面，最后计算 `ans` 连对数即可。

所以需要分两类：先取 $1$ 和先取 $0$（这里指第一个数）

本人用了变量 `finish` 表示已经取完多少个数字，如果还没有取完就继续取，取完了就 `return 0` 即可。

由于取数要取两遍（本人思路，不是最优），所以我把取数过程写成了一个函数，方便调用。最后输出先取零和先取一连续对数中较大的一个即可。

这时有人要问了，既然每一个串都有可能被取，当再来取这个串时，如何知道从哪里取呢？

答：本人用 $q_{i}$ 记录了第 $i$ 个串已经取到什么位置了，下次就应该从 $q_{i}+1$ 开始去取。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn=1e6+5;
string a[maxn];//存下串
int p=1;
int finish=0;//已经取了多少个
int all=0;
string ans;
int q[maxn];//存取到哪里了
void clear()
{
	p=0;
	finish=0;
	memset(q,0,sizeof(q));
	ans="\0";
}//因为要模拟两次，所以写了清空记录函数
int x=0;
void d()//取数函数
{
	while(finish<all)//还没取完
	{
		if(p==0)//本次应该取0
		{
			for(int i=1;i<=n;i++)
			{
				int len=a[i].length();
				for(int j=q[i];j<len;j++)
				{
					if(a[i][j]=='0')//是0
					{
						finish++;
						ans+=a[i][j];
					}
					else if(a[i][j]=='1')//是1
					{
						q[i]=j;
						break;
					}
					if(j==len-1) q[i]=j+10;//已经取完这个串
				}
			}
			p=1;
		}
		else if(p==1)//本次应该取1
		{
			for(int i=1;i<=n;i++)
			{
				int len=a[i].length();
				for(int j=q[i];j<len;j++)
				{
					if(a[i][j]=='1')//是1
					{
						finish++;
						ans+=a[i][j];
					}
					else if(a[i][j]=='0') //是0
					{
						q[i]=j;
						break;
					}
					if(j==len-1) q[i]=j+10;//已经取完这个串
				}
			}
			p=0;
		}
	}
	int lenans=ans.length();
	int asdf=0;
	//cout<<ans<<endl;
	for(int i=0;i<lenans-1;i++)
	{
		if(ans[i]==ans[i+1]) asdf++;//计算连对数
	}
	x=max(asdf,x);//取最大
}
int main(){
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)all+=a[i].length(); //计算总位数
	memset(q,0,sizeof(q));
	d();
	clear();
	d();
	cout<<x;
	return 0;
}

```

谢谢各位观看~

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8001)

## 题意

给定 $n$ 个 01 串，每次你可以从某个串开头移除一个字符并把它加入一个新串 $S$ 的末尾。最大化 $S$ 中相邻两个字符相同的对数。

## 分析

一段长为 $x$ 的同样字符中相邻两个字符相同的对数显然为 $x-1$，但如果拆成 $k$ 段只有 $n-k$ 对，所以我们只要使同种字符尽量合起来，总段数尽可能少即可，显然题目给的是 $n$ 个栈，我们一次性把所有栈顶的 $0$ 取完，再取完所有的 $1$，再 $0…$ 以此类推，直到全都取完，这样得到的段数肯定最少，相当于把每个栈按字符种类划分成几段，将每段对数依次放在数组中，把每个栈的贡献叠合，就可以计算答案了。

然而这样写完你发现过不了，原来第一次有从 $0$ 或 $1$ 开始取两种情况，聪明的你一定能想到，~~合理~~运用三大键 ``Ctrl``、``C``、``V`` 就可以通过。

## 代码
  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e6+10;
int n,lst;
ll ans1,d1[N],d2[N],ans2,mx;
int c[N];
int main(){
	n=read();
	for(int i=1,j,D;i<=n;i++){
		j=1;
		while((c[j]=getchar())!='\n')
			c[j++]-='0';
		lst=1;
		if(c[1]^1)
		    D=1;
		else
		    D=2;
		for(int k=2;k<=j;k++)
			if(c[k]^c[k-1]){
				d1[D++]+=k-lst;
				lst=k;
			}
		mx=max(mx,(ll)D-1);
		lst=1;
		if(c[1]^0)
		    D=1;
		else
		    D=2;
		for(int k=2;k<=j;k++)
			if(c[k]^c[k-1]){
				d2[D++]+=k-lst;
				lst=k;
			}
		mx=max(mx,(ll)D-1);
	}
	for(int i=1;i<=mx;i++)
		ans1+=max(d1[i]-1,(ll)0);
	for(int i=1;i<=mx;i++)
		ans2+=max(d2[i]-1,(ll)0);
	write(max(ans1,ans2));
	return 0;
}
```


---

## 作者：奥斯卡小冰人 (赞：0)

挺简单的一道题。~~但是感觉自己写复杂了~~

题意的话题目已经写得很清楚了，不需要赘述。

思路就是模拟它拿出字符的过程，而如果要连续字符对数最多就需要一直拿 0（或 1）直到不能拿 0（或 1）再去拿 1（或 0）。

不过这样就出现了一个问题，一开始拿 0 还是 1。

我的方法是将先拿 0 和先拿 1 都试一遍，最后求最大即可。

本人一开始的方法是用队列来模拟，但是发现开大会全MLE，而开小会 $\text{\purple{RE}}$，所以想到了动态的 $\text{vector}$ 和 $\text{string}$。

可是写完 $\text{vector}$ 发现又有两个点 TLE 了。（当然 $\text{string}$ 也试过了）

当时发现了是 $\text{erase()}$ 复杂度太高导致 T 了两个点。

之后便用一个数组来记录每次停止拿的位置，下一次循环直接跳到那个位置去拿。

但是感觉这个东西不是正解，写着很复杂，求一个正解。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int n;
vector<char>v1[1000010];
vector<char>v2[1000010];
int idx[1000010];
bool check()
{
    bool ag = 0;
    for(int i = 1;i <= n;i++) ag |= (idx[i] < v2[i].size());
    return ag;
}
int main()
{
    int ans1 = 0,ans2 = 0;scanf("%d",&n);
    for(int i = 1;i <= n;i++) 
    {
        string s;cin >> s;
        for(int j = 0;j < s.length();j++) 
            v1[i].push_back(s[j]),
            v2[i].push_back(s[j]);
    }
    while(check())
    {
        int cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            for(int j = idx[i];j < v2[i].size();j++)
            {
                if(v2[i][j] == '0') {idx[i] = j;break;}
                cnt++;
                if(j == v2[i].size() - 1) idx[i] = inf;
            }
        }
        if(cnt > 0) ans1 += cnt - 1;
        cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            for(int j = idx[i]*/记录每次停止拿的位置*/;j < v2[i].size();j++)
            {
                if(v2[i][j] == '1') {idx[i] = j;break;}
                cnt++;
                if(j == v2[i].size() - 1) idx[i] = inf;
            }
        }
        if(cnt > 0) ans1 += cnt - 1;
    }
    for(int i = 1;i <= n;i++) 
    {
        v2[i].clear();
        for(int j = 0;j < v1[i].size();j++) 
            v2[i].push_back(v1[i][j]),idx[i] = 0;
    }
    while(check())
    {
        int cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            for(int j = idx[i];j < v2[i].size();j++)
            {
                if(v2[i][j] == '1') {idx[i] = j;break;}
                cnt++;
                if(j == v2[i].size() - 1) idx[i] = inf;
            }
        }
        if(cnt > 0) ans2 += cnt - 1;
        cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            for(int j = idx[i];j < v2[i].size();j++)
            {
                if(v2[i][j] == '0') {idx[i] = j;break;}
                cnt++;
                if(j == v2[i].size() - 1) idx[i] = inf;
            }
        }
        if(cnt > 0) ans2 += cnt - 1;
    }
    cout << max(ans1,ans2);
    return 0;
}
```

---

## 作者：Tzs_yousa (赞：0)

## 暴力出奇迹
直接硬遍历就可以了，需要注意的就是如果第一个取的是 $0$ ，那么就需要先把所有的零取出，再取出 $1$ ，知道没有可以取出的 $1$ ，再重新取 $0$ ，直到取完为止，中途变换了几次就用 $len$ 减去几，然后就是答案了。
### 遍历函数
记一个 $q$ 数组，存每一个字符串遍历到的长度就可以防止重复计算。
```cpp
int solve(char x)
{
	int l = 0, ans = 0;
	while(1)
	{
		int p = 0;
		for (int i = 1; i <= n; i++)
		{
			while(s[i][q[i]] == x) q[i]++, p++;
		}
		ans += p - 1;
		l += p;
		p = 0;
		if(l == len) return ans;
		for (int i = 1; i <= n; i++)
		{
			if(x == '0')
			while(s[i][q[i]] == '1') q[i]++, p++;
			else 
			while(s[i][q[i]] == '0') q[i]++, p++;
		}
		ans += p - 1;
		l += p;
		if(l == len) return ans;
	}
}
```
额，好像也没什么必要放全套代码了，不过还是放一下吧。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, len, c1, c2, q[1000001];
string s[1000001];
inline string read()//快读 
{
	string str = "";
	char ch = getchar();
	while(ch == ' ' || ch == '\n' || ch == '\t') ch = getchar();
	while(ch != ' ' && ch != '\n' && ch != '\t') str += ch, ch = getchar();
	return str;
}
int solve(char x)
{
	int l = 0, ans = 0;
	while(1)
	{
		int p = 0;
		for (int i = 1; i <= n; i++)
		{
			while(s[i][q[i]] == x) q[i]++, p++;
		}
		ans += p - 1;
		l += p;
		p = 0;
		if(l == len) return ans;
		for (int i = 1; i <= n; i++)
		{
			if(x == '0')
			while(s[i][q[i]] == '1') q[i]++, p++;
			else 
			while(s[i][q[i]] == '0') q[i]++, p++;
		}
		ans += p - 1;
		l += p;
		if(l == len) return ans;
	}
}
signed main()
{
	freopen("1.in","r",stdin);
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) 
	{
		s[i] = read();
		len += s[i].size();
	}
	c1 = solve('0');
	memset(q, 0, sizeof(q));
	c2 = solve('1');
	printf("%lld", max(c1, c2));
	return 0;
}
```
完结！

---

## 作者：Yikara (赞：0)

## 题意理解：

给你 $n$ 个 $01$ 串和一个初始为空的答案串，每次取任意串的开头字符加入答案串尾部，使得所有$01$ 串取完之后答案串中相邻字符相同的对数最多。

比如有两个串 `001` 和 `100` 此时最优的选取顺序为 `1-1-2-1-2-2`，答案串为`001100`，答案为 $3$ 。

## 思路：

假设把答案串以不同的字符为分界线分为若干段，例如 `0001100` 分为三段 `000` ，`11` ，`00`：

若一段长度为 $1$ 其对答案的贡献为 $0$ ，贡献率为 $0\%$ 。

若一段长度为 $2$ 其对答案的贡献为 $1$ ，贡献率为 $50\%$ 。

若一段长度为 $3$ 其对答案的贡献为 $2$ ，贡献率约为 $67\%$ 。

若一段长度为 $4$ 其对答案的贡献为 $3$ ，贡献率为 $75\%$ 。

不难发现，若连续的字符长度越大，其“性价比”越高，也越是我们想要的最优方案。换句话说，我们要使得答案串中的“分界点”最少，因为这样能尽量获得更多的长串，以此得到更优的答案。

于是可以想到贪心，初始设定一个要取的字符，反复从各串中取该字符，直到所有串中没有该字符为止，此时再改为取另一个字符，如此循环，直到取完。

这样就会取出若干段，由于我们采取的贪心策略使得每一段的长度最长，也就是“性价比”最高，那么总的“性价比”也就越高了。

那么是先开始取 $0$ 还是 $1$ 呢？我用了一个笨办法：都算一遍，选最大的。

这样我们可以写出贪心代码，复杂度 $O(n+s)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[1000001],s;
int n,b[1000001],cnt1,cnt2,ans1,ans2,len[1000001],sb=0,qwq,lens,lenp;
//b数组为每个串当前取到的长度
char cur;
bool check(){
	for(int i=1;i<=n;i++){
		if(b[i]!=len[i])return 0;
	}
	return 1;
} 
signed main(){
	ios::sync_with_stdio(false);//优化输入
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		len[i]=a[i].length();//length()常数极大，预先存好。
	}
	if(n==1){
		s=a[1];goto rrr;
	}
	cur='0';
	while(!check()){
		for(int i=1;i<=n;i++){//枚举串
			while(a[i][b[i]]==cur&&b[i]<len[i]){//取完
				s+=cur;lens++;
				b[i]++; 
			}
		}
		if(lens==lenp){//没取到
			cur=cur=='1'?'0':'1';
		}
		lenp=lens;
	}
	qwq=s.length();
	for(int i=0;i<qwq;i++){
		if(s[i]==s[i+1])ans1++;
	}
	memset(b,0,sizeof(b));
	cur='1';s="";lens=lenp=0;
	while(!check()){
		for(int i=1;i<=n;i++){
			while(a[i][b[i]]==cur&&b[i]<len[i]){
				s+=cur;lens++;
				b[i]++; 
			}
		}
		if(lens==lenp){
			cur=cur=='1'?'0':'1';
		}
		lenp=lens;
	}
rrr:
	qwq=s.length();
	for(int i=0;i<qwq;i++){
		if(s[i]==s[i+1])ans2++;
	}
	cout<<max(ans1,ans2);
}
```


---

