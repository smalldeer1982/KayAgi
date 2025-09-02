# Restore a Number

## 题目描述

Vasya decided to pass a very large integer $ n $ to Kate. First, he wrote that number as a string, then he appended to the right integer $ k $ — the number of digits in $ n $ .

Magically, all the numbers were shuffled in arbitrary order while this note was passed to Kate. The only thing that Vasya remembers, is a non-empty substring of $ n $ (a substring of $ n $ is a sequence of consecutive digits of the number $ n $ ).

Vasya knows that there may be more than one way to restore the number $ n $ . Your task is to find the smallest possible initial integer $ n $ . Note that decimal representation of number $ n $ contained no leading zeroes, except the case the integer $ n $ was equal to zero itself (in this case a single digit 0 was used).

## 样例 #1

### 输入

```
003512
021
```

### 输出

```
30021
```

## 样例 #2

### 输入

```
199966633300
63
```

### 输出

```
3036366999
```

# 题解

## 作者：_edge_ (赞：1)

非常非常非常搞人的贪心题。

首先可以明确的是，可以通过第一个串可以确定长度。

这个各位应该有自己的方法来求，我想来写 $2300$ 应该不至于这个也处理不了把。

然后问题就是如何处理子串和原串了。

我们先思考没有子串的情况，这种情况下，我们从前往后贪是对的。

那么我们思考如何把这个子串插进去。

首先可以直接插到头上，这是第一种简单的情况，但是有可能会遗漏，因为插到头上后面就可以接 $0$，因此这种方案有可能是最优的。

那么我们思考怎么插在中间。

如果当前这个数 $i$ 比子串的头要小，那么肯定填 $i$。

如果当前这个数 $i$ 比子串头大，那么肯定填子串。

然后思考 $i$ 和头一样的时候，这种情况下，如果子串后面出现了某个递减的地方，那么一定是比较优秀的，填子串，如果出现递增那么就填 $i$。

如果相等呢？那填子串和 $i$ 本质相同。

搞好这些东西就可以切掉这道题了，不得不说，如果想到其他地方很容易写出一个假做法然后调不出来。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int num[INF],n,m;
string s1,s2;
int calc(int x) {
	int xx=x,S=0;
	while (xx) {
		num[xx%10]--;
//		cout<<num[xx%10]<<" "<<xx%10<<" endl\n";
		if (num[xx%10]<0) S=1;
		xx/=10;
	}
//	cout<<S<<" print\n";
	int cnt=0,sum1=0;
	for (int i=1;i<=9;i++)
		cnt|=num[i];
	for (int i=0;i<=9;i++) sum1+=num[i];
	xx=x;
	while (xx) {
		num[xx%10]++;
		xx/=10;
	}
	if (S || sum1+m!=x) return -1;
	return cnt;
}
string ans,ans2,res;
int check(int xx) {
	int nn=ans.size();
	for (int j=1,k=xx;j<=m;j++,k++) {
		if (k<nn) {
			if (s2[j]<ans[k]) return 1;
			else if (s2[j]>ans[k]) return 0;
		}
		else {
			for (int l=j;l<=m;l++) {
				if (s2[l-1]>s2[l]) return 1;
				if (s2[l-1]<s2[l]) return 0;
			}
			return 1;
		}
		
//		{
//			if (s2[j]<s2[k-nn+1]) return 1;
//			else if (s2[j]>s2[k-nn+1]) return 0;
//		}
	}
	return 1;
}
void solve(int x) {
	int xx=x;
	while (xx) {
		num[xx%10]--;
		xx/=10;
	}
	
	int la=0;
	for (int i=1;i<=9;i++)
		if (num[i]) {la=i;break;}
	int fl=0,K=-1;
	if (la==0) ;
	else { ans+=(char)(la+'0');num[la]--;K=la;}
	for (int i=1;i<=m;i++) res+=s2[i];
	int F=0;
	for (int i=2;i<=m;i++) {
		if (s2[i-1]<s2[i]) {F=1;break;}
		if (s2[i-1]>s2[i]) {F=0;break;}
	}
	for (int i=0;i<=9;i++)  {
		int cnt=0;
		while (num[i]) num[i]--,res+=(char)(i+'0'),cnt++;
		num[i]+=cnt;
		if (K==i) res+=(char)(i+'0');
	}
	for (int i=0;i<=9;i++) {
		if (s2[1]-'0'==i && !F) {for (int i=1;i<=m;i++) ans+=s2[i];}
		while (num[i]) num[i]--,ans+=(char)(i+'0');
		if (s2[1]-'0'==i && F) {for (int i=1;i<=m;i++) ans+=s2[i];}
	}
	if (ans[0]-'0'==0) ans=res;
	if (ans>res && res[0]-'0') ans=res;
	cout<<ans<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1>>s2;
//	if (s1=="01" && s2=="0") {cout<<"0\n";return 0;}
//	if (s1=="10" && s2=="0") {cout<<"0\n";return 0;}
	n=s1.size(),m=s2.size();
	s1=" "+s1;s2=" "+s2;
	for (int i=1;i<=n;i++) num[s1[i]-'0']++;
	for (int i=1;i<=m;i++) num[s2[i]-'0']--;
	
	for (int i=n;i;i--) {
		int fl=0;
		if (s2[1]!='0') fl=1;
		int xx=calc(i);
		if (xx==-1) continue;
		xx|=fl;
		if (xx) {
			solve(i);
			return 0;
		}
	}
	solve(1);
	return 0;
}
```


---

