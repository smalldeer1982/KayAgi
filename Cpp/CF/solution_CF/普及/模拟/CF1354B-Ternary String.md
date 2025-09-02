# Ternary String

## 题目描述

You are given a string $ s $ such that each its character is either 1, 2, or 3. You have to choose the shortest contiguous substring of $ s $ such that it contains each of these three characters at least once.

A contiguous substring of string $ s $ is a string that can be obtained from $ s $ by removing some (possibly zero) characters from the beginning of $ s $ and some (possibly zero) characters from the end of $ s $ .

## 说明/提示

Consider the example test:

In the first test case, the substring 123 can be used.

In the second test case, the substring 213 can be used.

In the third test case, the substring 1223 can be used.

In the fourth test case, the substring 3221 can be used.

In the fifth test case, there is no character 3 in $ s $ .

In the sixth test case, there is no character 1 in $ s $ .

In the seventh test case, the substring 3112 can be used.

## 样例 #1

### 输入

```
7
123
12222133333332
112233
332211
12121212
333333
31121```

### 输出

```
3
3
4
4
0
0
4```

# 题解

## 作者：vectorwyx (赞：7)

逛了一圈发现没有和我思路一样的，赶紧过来码一篇题解qwq。


------------
易知最短的满足条件的连续子串的形式一定为$abb……bc$（$a \not=b\not=c$，$1\le a,b,c\le 3$）

因此我们把原字符串里的所有连续的相同数字都“打包”成“块”然后遍历一遍，每次取“块”两边的元素作为左右端点并判断是否合法，不断更新答案就行了，时间复杂度是严格$O(n)$的。

（核心代码只有5行，~~自认为是最简单的做法~~）


------------
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=1e6+5,maxx=1e9;
int dis1[maxn][5],dis2[maxn][5];
int a[maxn],L[maxn],R[maxn],siz[maxn];
char s[maxn];

void work(){ 
	scanf("%s",s);
	int len=strlen(s),ans=maxx,t;
	fo(i,0,len-1) a[i+1]=s[i]-'0';//先转成以1为下标的整数数组，就是图个方便 
	fo(i,1,len){
		L[i]=i,R[i]=i;
		while(R[i]<len&&a[R[i]+1]==a[R[i]]) R[i]++;//把每一"块"的左右端点处理出来 
		siz[i]=R[i]-L[i]+1;//顺便求出大小 
		t=i;//这个是为了记录最后一个块的位置 
		i=R[i];//当前"块"已处理完毕，跳到下一个"块" 
	}
	//由于"块"永远在满足要求的连续字串的中间
	//因此不用遍历第一个和最后一个"块" 
	fo(i,R[1]+1,L[t]-1){
		//这个"块"的相邻的元素不同
		//那么它和两个相邻元素一定能构成一个合法的连续子串
		if(a[L[i]-1]!=a[R[i]+1]) ans=min(ans,siz[i]+2);//更新答案 
		i=R[i];//跳到下一个"块" 
	}
	if(ans==maxx) puts("0");
	else printf("%d\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```
点个赞再走吧~

---

## 作者：andyli (赞：4)

记 $pos_i$ 表示字符 $i$ 上一次出现的位置，未出现过则为 $-1$ ，则对于字符 $s_i$ ：  
- 当 $s_i=1$ 且 $pos_2,pos_3\neq -1$ 时，以 $s_i$ 结尾的区间的答案为 $i-\min\{pos_2,pos_3\}+1$
- 当 $s_i=2$ 且 $pos_1,pos_3\neq -1$ 时，以 $s_i$ 结尾的区间的答案为 $i-\min\{pos_1,pos_3\}+1$
- 当 $s_i=3$ 且 $pos_1,pos_2\neq -1$ 时，以 $s_i$ 结尾的区间的答案为 $i-\min\{pos_1,pos_2\}+1$

时间复杂度 $\mathcal O(n)$ 。

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <cstring>
constexpr int maxn = 200005, INF = -1u / 2;

char s[maxn];
int main() {
    int q;
    io.read(q);
    while (q--) {
        io.read(s + 1);
        int n = strlen(s + 1), ans = INF, pos1 = -1, pos2 = -1, pos3 = -1;
        for (int i = 1; i <= n; i++) {
            if (s[i] == '1') 
                if (pos1 = i; ~pos2 && ~pos3) 
                    chkmin(ans, i - min(pos2, pos3) + 1);
            if (s[i] == '2') 
                if (pos2 = i; ~pos1 && ~pos3) 
                    chkmin(ans, i - min(pos1, pos3) + 1);
            if (s[i] == '3') 
                if (pos3 = i; ~pos1 && ~pos2) 
                    chkmin(ans, i - min(pos1, pos2) + 1);
        }
        writeln(ans == INF ? 0 : ans);
    }
    return 0;
}
```

---

## 作者：hereiszd (赞：3)

看着题解区内没有双指针的做法，这里向大家介绍一下本题双指针的做法。

## 题目分析

显然，若 $S$ 的一个字串 $T$ 满足题意，则所有包含 $T$ 的字符串均满足题意。

我们不妨从 $1$ 开始，维护两个指针 $l,r$，每次操作使 $r$ 向右尝试增加，判断新的字串是否满足题意，若是，则尝试将 $l$ 右移，尽量缩小字串。

因为首先是满足题意，其次再缩小长度，所以本题的正确性可以得到保证。

时间复杂度分析：因为每个点最多分别被 $l,r$ 扫到一次，所以时间复杂度为 $\Theta(n)$ 可以通过该题。

## $code$

```cpp
/*
	Author:zd
	Status:WA on pretest 2
*/

//去掉了快读，快写等函数。 
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define INF 0x7f7f7f7f
void solve();
signed main(){int _;read(_);while(_--)solve();return 0;}
char s[N];
void solve(){
	scanf("%s",s+1);
	int a=0,b=0,c=0,l=0,r=0,n=strlen(s+1);//a,b,c分别维护区间内1,2,3的个数 
	int ans=INF;
	while(r<=n){
		if(a&&b&&c){
			if(s[l]=='1')a--;
			if(s[l]=='2')b--;
			if(s[l]=='3')c--;
			l++;
		}
		else{
			r++;
			if(s[r]=='1')a++;
			if(s[r]=='2')b++;
			if(s[r]=='3')c++;
			
		}
		if(a&&b&&c)cmin(ans,r-l+1);
	}
	if(ans==INF){//判断整个串是否满足题意 
		puts("0");
		return;
	}
	writeh(ans);
}




```


---

## 作者：xh39 (赞：2)

首先,我们为了快速判断一段区间是否符合要求,先跑一遍前缀和,分别设s1,s2,s3为从0~i的区间数字1,2,3出现的个数。现在我们要求l~r区间1,2,3的个数,只需要s[r]-s[l-1]就可以了。符合条件即个数全部>0。 

## 暴力算法。

暴力找出以每个点开头最短包含123的。然后在这每个点中取最小值。 

时间复杂度:O(n²);显然过不了。

## 优化

我们可以发现,如果l~r1不符合要求,那么l~r2 (r2>=r1)肯定也不符合要求。(因为123的数量只会多,不会少)。

假设现在找到的最小值为min,那么我们在枚举起始点为l的时候,先判断l~l+min是否符合要求,如果不符合要求,枚举下一个点,否则r--,表示min更新。


## 代码

```cpp
#include<iostream>
using namespace std;
int s1[1000005],s2[1000005],s3[1000005];
void Main(){
	string s;
	cin>>s;
	int i,size=s.size();
	s1[0]=(s[0]=='1');
	s2[0]=(s[0]=='2');
	s3[0]=(s[0]=='3');
	for(i=1;s[i];i++){
		s1[i]=s1[i-1]+(s[i]=='1');
		s2[i]=s2[i-1]+(s[i]=='2');
		s3[i]=s3[i-1]+(s[i]=='3');
	}
	for(i=size;i<=(size<<1);i++){ //在这个代码中,可能会枚举到超过s.size()的下标。 
		s1[i]=s1[i-1];
		s2[i]=s2[i-1];
		s3[i]=s3[i-1];
	}
	int l,r=-1;
	for(i=0;s[i];i++){ //枚举第一个的r。(第一个点没有前面的点的信息,无法优化)。 
		if(s1[i]&&s2[i]&&s3[i]){
			r=i;
			break;
		}
	}
	if(r==-1){
		cout<<0<<endl;
		return;
	}
	int Min=2147483647;
	for(i=1;s[i];i++){
		while((s1[r]-s1[i-1])&&(s2[r]-s2[i-1])&&(s3[r]-s3[i-1])){
			r--;
		}
		r++; //注意,r现在不符合要求,r+1才符合要求。 
		Min=min(Min,r-i);
		r++; //枚举下一个点,r也要加一。 
	}
	cout<<Min+1<<endl;
}
int main(){
	int t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```
## 时间复杂度

预处理前缀和:O(6n)。

核心代码:O(2n)。 

这里可以理解为O(n),因为前面的都是常数。

虽然有两重循环,但是r一直在缩小(除了i++的时候),所以这里的复杂度为O(n)。

---

## 作者：Werner_Yin (赞：2)

# 题意
给出一个字符串，只包含 ${1,2}$ 或 ${3}$ 。从中找出一个长度最短的子串，要求至少包含 ${1,2,3}$ 各一次，并输出其长度。
## 输入格式
**本题有多组测试数据**

第一行一个整数 $t$ ，表示数据组数

接下来 ${t}$ 行，每行一个字符串 $s$ ，它的每个字符只可能是 $1,2$ 或 $3$ 。${s}$ 的长度不超过$200000$。

## 输出格式
对于每组数据，输出一行一个整数，表示最短的符合要求的子串的长度。如果不存在，输出 $0$ 。

### 说明与提示
$ 1 \le t \le20000$，
$1 \le |s| \le 200000 $
# Solution
我们可以开一个数组 $a $ ，其中 $a_i$ 表示 i 上次出现的位置（$ 1\le i \le 3$ ），初始时，$a_i=-1$。

然后线性扫过去，不断更新 $a$，当停留在第 $ k $位时， a[ s[k]-'0' ]= k 。 显然，以第 $k$ 位结尾的符合要求的子串长度为 k-min(a[1],a[2],a[3])+1 。此时我们可以更新 $ans$ 。
## 代码 ↓
**注意多测**
```cpp
#include<bits/stdc++.h>
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
const int MAXN=200010;
int t,a[5],ans=MAXN;
int main (){
	scanf("%d",&t);
	while(t--){
		string s;
		cin>>s;
		a[1]=-1;a[2]=-1;a[3]=-1;ans=MAXN;
		int ls=s.length();
		for(int i=0;i<ls;i++){
			a[s[i]-'0']=i;
			int minn=MAXN;
			for(int j=1;j<=3;j++){
				minn=min(minn,a[j]);	
			}
			if(minn==-1)continue;
			ans=min(ans,i-minn+1);
			if(ans==3)break;
		}
		if(ans==MAXN)printf("0\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```
~~本蒟蒻第一次写题解，巨佬轻喷~~

---

## 作者：lndjy (赞：1)

### 此题最简单题解

枚举一个符合要求子串的后一位，对于其他两个数字，记录目前他们出现最晚的位置，子串 $l,r$ 的 $l$ 越大，子串长度越小。

令 $num1,num2,num3$ 表示 $1,2,3$ 出现最晚的位置，对于每个 $r$ 点，合法子串最短长度为 $max(num1,num2,num3)-min(num1,num2,num3)$,取最小值即可。

代码：
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char s[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(s,0,sizeof s);
		scanf("%s",s);
		int num1=0,num2=0,num3=0,ans=1e9;
		int len=strlen(s);
		for(int i=0;i<len;i++)
		{
			if(s[i]=='1') num1=i+1;
			if(s[i]=='2') num2=i+1;
			if(s[i]=='3') num3=i+1;
			if(num1&&num2&&num3)
			{
				int now=max(num1,max(num2,num3));
				now-=min(num1,min(num2,num3));
				ans=min(ans,now);
			}
		 }
		 if(ans==int(1e9))
		 cout<<0<<endl;
		 else
		 cout<<ans+1<<endl;
	}
	return 0;
}
```


---

## 作者：novax (赞：1)

**题目大意**：给你一个长度为 $s$ 的只由字符‘1’‘2’和‘3’构成的字符串，让你找出最短的包括‘1’‘2’‘3’的连续字串长度，不存在则输出0

#### 思路
设 $n$ 是读入字符串的长度，我的做法是先 $O(n)$ 遍历一遍整个字符串，如果字符串中的三种字符不全，那么不可能有解，直接输出0。

然后用两层循环计算从字符串中第 $i$ 个字符开始的最短包含‘1’‘2’‘3’三个字符的连续字串长度，因此，第二层的循环只需要三种字符都碰到了从这个字符开始的最短长度，然后更新答案。

但这样做的话时间复杂度可能会很高
~~(我也没试过)~~
，因此，考虑到像``122123``这样的数据，第1位的字符‘1’往后计算的结果一定比第3位的‘1’字符计算到的答案要大，而且无法为答案做出有效的贡献，同样，在遇到许多连续相同的字符时，也一定是从这些连续的相同字符的最后一个计算才能得到最短的子串。因此，在第二层循环中在三种字符都遇到之前遇到与第 $i$ 个字符相同的字符，就进行下一次循环，因为后面一定存在更优解，这样两层循环的复杂度最多比 $O(n)$ 大一点了

#### 代码如下
```cpp
#include <cstdio>
#include <cstring>
char a[200010];
int min(int x,int y)//返回两数较小值 
{
	return (x<y)?x:y;
}
int mj(int N)//判断这个输入的字符串是否无解 
{
	int i,b1,b2,b3;
	b1=0;b2=0;b3=0;
	for(i=1;i<=N;i++)
	{
		if(a[i]=='1')
			b1++;
		if(a[i]=='2')
			b2++;
		if(a[i]=='3')
			b3++;
		if(b1&&b2&&b3)
			return 0;
	}
	return 1;
}
int main()
{
	int T,N,i,j,ans,lt,cc,dd;
	char c1,c2,c3; 
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",a+1);
		N=strlen(a+1);
		if(mj(N))//无解则输出0 
		{
			printf("0\n");
			continue;
		}
		ans=1000000;
		for(i=1;i+2<=N;i++)//查找从第i个字符开始的包含1，2，3三个字符的子串长度 
		{
			c1=a[i];c2=0;
			cc=0;dd=0;lt=1;
			for(j=i+1;j<=N;j++)
			{
				if(a[j]==c1)//如果在后面遇到了与第i个字符相同的字符，那么一定存在更优解，所以跳过本次循环 
				{
					cc++;
					break;
				}
				lt++;
				if(a[j]!=c1&&a[j]!=c2)
				{
					if(c2==0)//c2为0时，第j个字符是第一个与第i个字符不同的字符 
					{
						c2=a[j];
					}
					else//否则第j个字符与c1和c2都不同，一定出现了第三种字符 
					{
						dd++;
						break;
					}
				}
			}
			if(cc)
				continue;
			if(!dd)
				continue;
			ans=min(ans,lt);
		}
		printf("%d\n",ans);
	}
}
```
~~虽然很长，但这是提交这个题解时洛谷上此题的最优解~~

---

## 作者：EternalEpic (赞：1)

提供一个思路，二分。

可以二分答案最小连续s个字符就能都包含 $1,2,3$。

判断方式为类似一个可回退双端队列模型，通过循环遍历，判断以第K个字符开头往后连续s个能否满足条件。

如果满足条件，则看能否有更小的s。否则，则相反。

判断：

```cpp
int s1, s2, s3, n;
inline bool check(int x) {
	s1 = s2 = s3 = 0;
	for (int i = 0; i < x; i++) {
		if (s[i] == '1') s1++;
		if (s[i] == '2') s2++;
		if (s[i] == '3') s3++;
	} if (s1 && s2 && s3) return true;
	for (int i = x; i < n; i++) {
		if (s[i - x] == '1') s1--;
		if (s[i - x] == '2') s2--;
		if (s[i - x] == '3') s3--;
		if (s[i] == '1') s1++;
		if (s[i] == '2') s2++;
		if (s[i] == '3') s3++;
		if (s1 && s2 && s3) return true;
	} return false;
}
```



---

## 作者：Qquun (赞：0)

## 1.解题思路：
子序列自动机弱化版(赛时第一眼思路)，处理出pre[i][j]表示第i位后字符j出现的第一个位置。

(本篇叫pre数组,其他博客通常称为Next[i][j]）


例如：
```c
s=1223

则可以得到:
pre[1][1]=0;
pre[1][2]=2;
pre[1][3]=4;

pre[2][1]=0;
pre[2][2]=3;
pre[2][3]=4;

pre[3][1]=0;
pre[3][2]=0;
pre[3][3]=4;

......
```
由此处理出pre数组后，可以由题意得最短的答案序列可能为

"1...2...3", "1...3..2", "2...1...3",

"2...3...1", "3...1...2", "3...2...1"。

所以我们只要遍历一遍s，当s[i]='1'时，对于答案为"1...2...3"的情况，找到第i位后出现'2'的第一个位置，再从这个位置出发，寻找出现'3'的第一个位置。即可得到当前第i位能构成的最短答案序列的长度=pre[pre[i][2]][3]-i+1。其他情况类似，这里不再讲解。

## 2.Code:
```c

#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=2e5+20;
int pre[N][4];
char s[N];
int q[10];
map<int,int>mp;
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>s+1;
		int len=strlen(s+1);
		rep(i,1,len){
			q[s[i]-'0']++;
		}
		if(q[1]==0||q[2]==0||q[3]==0){
			cout<<"0"<<"\n";
			q[1]=q[2]=q[3]=0;
			continue;
		}
		dep(i,len,1){//处理出pre数组
			rep(j,1,3){
				pre[i][j]=mp[j];
			}
			mp[s[i]-'0']=i;
		}
		int ans=INF;
		rep(i,1,len-2){//边界处理最短的答案序列为3，所以枚举到len-2
			if(s[i]=='1'){
				if(pre[i][2]!=0&&pre[pre[i][2]][3]!=0)ans=min(ans,pre[pre[i][2]][3]-i+1);
				if(pre[i][3]!=0&&pre[pre[i][3]][2]!=0)ans=min(ans,pre[pre[i][3]][2]-i+1);
			}
			if(s[i]=='2'){
				if(pre[i][3]!=0&&pre[pre[i][3]][1]!=0)ans=min(ans,pre[pre[i][3]][1]-i+1);
				if(pre[i][1]!=0&&pre[pre[i][1]][3]!=0)ans=min(ans,pre[pre[i][1]][3]-i+1);
			}
			if(s[i]=='3'){
				if(pre[i][2]!=0&&pre[pre[i][2]][1]!=0)ans=min(ans,pre[pre[i][2]][1]-i+1);
				if(pre[i][1]!=0&&pre[pre[i][1]][2]!=0)ans=min(ans,pre[pre[i][1]][2]-i+1);
			}
		}
		rep(i,1,3)q[i]=0;
		dep(i,len,1){
			rep(j,1,3){
				pre[i][s[i]-'0']=0;
			}
		}
		mp.clear();
		cout<<ans<<"\n";
	}
	return 0;
}

```

## 3.复杂度:O(n)




 


---

