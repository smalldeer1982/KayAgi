# Enchanted Artifact

## 题目描述

This is an interactive problem.

After completing the last level of the enchanted temple, you received a powerful artifact of the 255th level. Do not rush to celebrate, because this artifact has a powerful rune that can be destroyed with a single spell $ s $ , which you are going to find.

We define the spell as some non-empty string consisting only of the letters a and b.

At any time, you can cast an arbitrary non-empty spell $ t $ , and the rune on the artifact will begin to resist. Resistance of the rune is the edit distance between the strings that specify the casted spell $ t $ and the rune-destroying spell $ s $ .

[Edit distance](https://en.wikipedia.org/wiki/Levenshtein_distance) of two strings $ s $ and $ t $ is a value equal to the minimum number of one-character operations of replacing, inserting and deleting characters in $ s $ to get $ t $ . For example, the distance between ababa and aaa is $ 2 $ , the distance between aaa and aba is $ 1 $ , the distance between bbaba and abb is $ 3 $ . The edit distance is $ 0 $ if and only if the strings are equal.

It is also worth considering that the artifact has a resistance limit — if you cast more than $ n + 2 $ spells, where $ n $ is the length of spell $ s $ , the rune will be blocked.

Thus, it takes $ n + 2 $ or fewer spells to destroy the rune that is on your artifact. Keep in mind that the required destructive spell $ s $ must also be counted among these $ n + 2 $ spells.

Note that the length $ n $ of the rune-destroying spell $ s $ is not known to you in advance. It is only known that its length $ n $ does not exceed $ 300 $ .

## 样例 #1

### 输入

```

2

2

1

2

3

0```

### 输出

```
aaa

aaab

abba

bba

abaaa

aabba```

# 题解

## 作者：liuyz11 (赞：4)

# 题解 CF1282D 【Enchanted Artifact】

**该场比赛的题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12173579.html)**

题目大意：本题为交互题。有一个字符串s，只由字符'a'和'b'组成。每次你可以询问一个字符串，它会返回这两个字符串的编辑距离。为一个字符串经过修改，删除或插入操作得到另一个字符串，两个字符串编辑距离的定义为最小的操作次数，若返回值为0，那么就是字符串s。让你在n + 2操作内得出字符串s（n为字符串s的长度，未知）。

人生中第一次对交互题有想法，但是是错的想法……

一开始我认为输入'a'和'b'，若是原字符串有'a'字符，那么返回的是长度n - 1，否则返回的是长度n，那么原字符串的长度n为返回两值的最小值+1。

然后询问一个由1个'b'和 n - 1 个'a'组成的字符串，共有n种，返回的数一定是字符串中b的个数加1或减1，即该位是否为b，然后因为在询问n +1次后一定要给出字符串s，那么通过前n - 1推出最后一位是否是'b'。

这个方法看上去没问题，但是发现了一组反例。

    s字符串为"baaab"

    询问的字符串为"aaaba"

    根据我的思路返回数应该是3，即字符串中不相同的个数，但是这个数据返回了2。

    只需要在首位插入'b'，在末位插入'a'即可。

然后我就傻掉了，去看了下题解。

发现题解的思路是先输入300个'a'，再输入300个'b'，返回的数分别是300 - 'a'的个数以及300 - 'b'的个数，那么就得到了原字符串中'a'和'b'的个数以及字符串的长度。然后将答案串设为全'a'，对于每一位将该位改为'b'，如果返回值小于当前的编辑长度（一开始全'a'的编辑长度就是字符'b'的个数），那么答案的这一位一定是'b'。但是最多询问n + 2次，那么最后一位也只能靠前面答案推出，即若当前编辑长度为1那么最后一位是'b'，否则为'a'。

乍一看这个题解思路和我的差不多，但是它不会像我的代码一样出现反例。

为什么呢，因为对于第i位改为'b'时，它前面的字符已经是和字符串s相同了，而我这个反例的最少的编辑操作是将'b'前面的一段往后移动一位，再插入一位比只修改操作要优。但是由于前i - 1位已经相同了就不会有这种操作，那么后面就一定是修改操作。

另外题解中一开始求长度的操作也是优于我的方法的，我的方法很难得出是插入操作还是存在修改操作，所以在n = 2的情况下很难直接得出答案，而题解直接得出了字符串s中'a'和'b'的个数，可以直接给出。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int judge(string st){
	puts(st.c_str());
	fflush(stdout);
	int ans;
	scanf("%d", &ans);
	if(!ans) exit(0);
	return ans;
}

int main(){
	int n = 300;
	int lena = n - judge(string(n, 'a')),
		lenb = n - judge(string(n, 'b'));
	int len = lena + lenb;
	string ans = string(len, 'a');
	int res = lenb;
	rep(i, 0, len - 2){
		ans[i] = 'b';
		int s = judge(ans);
		if(s > res) ans[i] = 'a';
		else res = s;
	}
	if(res) ans[len - 1] = 'b';
	judge(ans);
    return 0;
}
```

---

## 作者：LinkyChristian (赞：3)

vp的时候没注意，赛后一看：蛙趣，2300

蛮有趣的构造题。

首先我们要知道串 $s$ 的长度 $n$。~~那么直接询问空串~~直接询问 $a$ 和 $b$ ，如果 $s$ 同时包含 $a$ 和 $b$ ，那么两个返回值都会是 $n-1$ ，否则一个返回值为 $n$ 另一个为 $n-1$ 。所以取小的返回值 $+1$ 即是串的长度。

知道了串的长度后我们直接询问 $n$ 个 $a$ 就能得出 $a$ 和 $b$ 的个数 $A,B$  。要做接下来的操作我们首先要知道如何判断一个串是否为 $s$ 的子串。询问一个长度为 $x$ 的串，设返回值为 $y$ ，如果 $x+y=n$ 那么询问串是 $s$ 的子序列。

我们知道 $s$ 的形式一定是由长度为 $A$ 的全 $a$ 串，在每个 $a$ 前面插入若干个 $b$ ，再在最后放一些 $b$ 组成的。我们从第一个 $a$ 开始尝试在它前面插 $b$ ，插到不是 $s$ 的子串了就换下一个 $a$ 继续插。一共会插入 $B$ 个 $b$ ，最多试错 $A$ 次，这里的总操作次数为 $A+B=n$ 。

我们现在得到了 $n+3$ 步的做法。考虑优化，在两次操作内同时得出 $n$ 和 $A,B$。我们询问 $a$ ，设返回值为 $res$ 。接着询问 $res+1$ 个 $a$ 。考虑如果 $s$ 包含 $a$ ，那么 $res$ 为 $n-1$ ，返回值为 $B$ 。否则 $res=n$ ，返回值将为 $res+1$ 。因此如果返回 $res+1$ 则确定整个串都为 $b$ ，否则我们就在两步操作内得出了 $n,A,B$ 。

注意一个比较坑的点：询问串的长度不能超过 $300$ ，因此如果第一次询问返回值为 $300$ 可以直接确定 $s$ 为长为 $300$ 的全 $b$ 串。

```cpp
#include<bits/stdc++.h>
#define N 310
using namespace std;
string s;
int query(int len) {
	for(int i=0; i<len; i++) cout<<s[i];
	cout<<endl;
	cout.flush();
	int res;cin>>res;
	if(!res) exit(0);
	return res;
}
int n,A,B,num[N];
int main() {
	s="a";
	int res=query(1);s="";
	if(res==300) {
		for(int i=0; i<300; i++) s[i]='b';
		query(300);return 0;
	}
	for(int i=0; i<=res; i++) s[i]='a';
	int B=query(res+1);
	if(B==res+1) {
		s="";
		for(int i=0; i<res; i++) s[i]='b';
		query(res);return 0;
	}
	if(B==0) {
		s="";
		for(int i=0; i<=res; i++) s[i]='a';
		query(res+1);return 0;
	}
	n=res+1,A=n-B;
	for(int i=1,j=1; i<=B; i++) {
		if(j==A+1) {
			int ttt=B,tot=-1;s="";
			for(int k=1; k<=A; k++) ttt-=num[k];
			for(int k=1; k<=A; k++) {
				for(int p=1; p<=num[k]; p++) s[++tot]='b';
				s[++tot]='a';
			}
			for(int k=1; k<=ttt; k++) s[++tot]='b';
			query(tot+1);
		}
		s="";int tot=-1;
		for(int k=1; k<j; k++) {
			for(int p=1; p<=num[k]; p++)s[++tot]='b';
			s[++tot]='a';
		}
		for(int p=1; p<=num[j]+1; p++) s[++tot]='b';
		for(int k=j; k<=A; k++) s[++tot]='a';
		int gt=query(tot+1);
		if(gt+tot+1==n) num[j]++;
		else j++,i--; 
	}
} 
```


---

## 作者：Zemu_Ooo (赞：1)

~~一开始看到$2300$难度的题目，我是拒绝的。~~

一开始想由于不知道字符串长度，可以先输入”$a$“得到$n$，”$b$“得到$m$。如果$n≠m$，那么字符串肯定是$min(n,m)$个$a$或者$b$。如果$n=m$，则说明字符串长度为$n+1$。然后我们输出$n+1$个$a$就可以得到一个$k$，然后知道这个字符串有$k$个$b$，然后按位枚举$b$。但是一算最多需要$n+1+3$次，超过了题目的要求。

然后转念一想，没必要第二次输出”$b$",直接输出$n+1$个$a$，如果的到$k=n+1$，那字符串肯定是$n$个$b$。其他的$k$就表明字符串有几个$b$，然后从头到尾枚举，如果得到的次数增多了，就表明这个位置是$a$，否则是$b$。

然后最最最坑的一个点就是，$n≤300$，所以如果一个长为$300$的字符串全是$b$，按照程序，他第一次会输出$300$，然后第二次输出$301$，超过$300$，直接报**Wrong Answer**。

那么，只需要加一个特判就行了。

代码：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define cl(x,y) memset(x,y,sizeof(x))
#define ct cerr<<"Time elapsed:"<<1.0*clock()/CLOCKS_PER_SEC<<"s.\n";
const int N=1e6+10;
const int mod=1e7+9;
const int maxn=0x3f3f3f3f;
const int minn=0xc0c0c0c0;
const int inf=99999999;
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	string s;
	int n,m,i;
	cout<<"a"<<endl;
	fflush(stdout);
	cin>>n;
	if(n==0)
		exit(0);
	if(n==300)
	{
		for(i=1;i<=300;i++)
			cout<<"b";
		cout<<endl;
		cin>>m;
		exit(0);
	}
	for(i=0;i<=n;i++)
		s+='a';
	cout<<s<<endl;
	fflush(stdout);
	cin>>m;
	if(m==0)
		exit(0);
	if(m>n)
	{
		for(i=1;i<=n;i++)
			cout<<"b";
		cout<<endl;
		fflush(stdout);
		cin>>m;
		exit(0);
	}
	int pre=m,temp;
	for(i=0;i<=n;i++)
	{
		s[i]='b';
		cout<<s<<endl;
		fflush(stdout);
		cin>>temp;
		if(temp==0)
			exit(0);
		if(temp>=pre)
			s[i]='a';
		else
			pre=temp;
	}
	return 0;
}


```


---

## 作者：Eltaos_xingyu (赞：0)

## 题意

本题为交互题。

有一个字符串 $s$，只由字符 `a` 和 `b` 组成。每次你可以询问一个字符串，它会返回这两个字符串的编辑距离。

编辑距离为一个字符串经过修改，删除或插入操作得到另一个字符串，两个字符串编辑距离的定义为最小的操作次数，若返回值为 $0$，那么就是字符串 $s$。让你在 $n + 2$ 次操作内得出字符串 $s$（$n$ 为字符串 $s$ 的长度，未知）。

## 解法

很有意思的一道题。

首先对编辑距离不熟的同学一定会想到一个简单的策略，即我们先直接输出 $300$ 个 `a`，然后逐位改成 `b`。如果改错了那么输入的值会加一，改对了的话输入的值减一。一直改直到输入的值不变，这时字符串就是上次修改那一位的前缀。

但是不难举出一个反例：`ab`。如果询问 `aa...a`（$300$ 个 `a`），编辑距离确实是 $299$，但是询问 `baa....a` 时就不对了，按上面的策略来讲，编辑距离应是 $300$，但是我们完全可以选择先从开头删除，直到删到只剩下两个字符，然后再把其中第二个字符改成 `b`，编辑距离仍为 $299$。

再手玩一下发现结论：当**当前询问字符串长度大于我们要求的字符串长度**时，逐位改 `b` 的话改错了编辑距离不变，改对了编辑距离减一。因为根据上面的反例，我们询问的字符串的结构应该是正确的一部分 + 改错了或改对了 + 一堆 `a`。对于改对了，那么我们就可以在原来的基础上少修改一个，编辑距离减一，如果改错了，我们可以把这个改错了的 `b` 删掉，然后像之前一样删去元素，由于删去元素个数相同，所以编辑距离相同。所以沿用之前的思路，当改了之后编辑距离减小，那么改的正确，否则改错了。

这个时候就要开始判终末条件了。一个很容易想的思路是当当前遍历到的正确字符串长度加上目前的编辑距离等于询问的字符串长度 $300$，那么就能确定正确字符串结构。因为当前正确字符串部分后面要么没有字符了，要么还有一堆 `b`。那么直接枚举 `b` 的个数即可。

这样的话开头全 `a` 的一次和枚举 `b` 的个数时判断 $0$ 个 `b` 是否为目标字符串的一次是多的两次，询问次数最多是 $n+2$。

我的实现不太精细，不然应该是可以不用特判全 `b` 的情况。

```cpp
// Problem: Enchanted Artifact
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1282D
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Start coding at 2024-01-05 14:56:42
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
string s,t;
int main(){
	ios::sync_with_stdio(0);
	for(int i=1;i<=300;i++)s+='a';
	cout<<s<<"\n";
	cout.flush();
	int dist;
	cin>>dist;
	if(dist==300){
		s.clear();
		while(dist){
			s+='b';
			cout<<s<<"\n";
			cout.flush();
			cin>>dist;
		}
		return 0;
	}
	int nowp=0;
	while(1){
		int newdist,ll=dist;
		s[nowp]='b';
		cout<<s<<"\n";
		cout.flush();
		cin>>newdist;
		if(newdist==0)break;
		if(newdist>=dist)s[nowp]='a';
		else dist=newdist;
		nowp++;
		if(nowp+newdist>=300&&ll==newdist){
			for(int i=0;i<nowp-(nowp+newdist-300);i++)t+=s[i];
			cout<<t<<endl;
			cout.flush();
			cin>>dist;
			while(dist){
				t+='b';
				cout<<t<<"\n";
				cout.flush();
				cin>>dist;
			}
			break;
		}
	}
	// while(1);
	return 0;
}
```



---

## 作者：luo_shen (赞：0)

## 题意简述
交互题，要求得到一个未知长度，只包含字符 `a` 和字符 `b` 的字符串 $s$，最多询问 $|s|+2$ 次（$|s|$ 表示字符串 $s$ 的长度，$|s|\le 300$），每次返回的是询问串与答案串的编辑距离，且最后一次所询问的必须是答案。

编辑距离 $f(a,b)$ 的定义为：若字符串 $a$ 最少通过 $x$ 次删除、添加或修改某个字符的操作才能得到字符串 $b$，则 $f(a,b)=x$。

## 题目分析
发现字符串长度是未知的，这十分影响解题，于是考虑将字符串长度求出。可以发现询问全 `a` 串和全 `b` 串是很有用的，因为询问一次可以得到 $s$ 中有多少个字符 `a`，有多少个字符 `b`，因为字符串中只有 `a` 和 `b` 两种字符，所以得到了整个字符串的长度。

接下来还有 $|s|-1$ 次询问操作，与 $|s|$ 大小相近，可以想到逐位确定的思路。

令第 $1\sim i$ 位为已经确定的位置，没有确定的位置中有 $sum_a$ 个 `a`，$sum_b$ 个 `b`。  
首先，若 $sum_a$ 为 $0$，则剩下的位置全为 `b`，$sum_b$ 为 $0$，则剩下的位置全为 `a`。  
对于 $sum_a\not =0,sum_b\not =0$ 的情况，先将剩下的位置填为 `a`，因为所有的 `a` 都填到位了，可以发现此时的字符串 $s'$ 与 $s$ 的编辑距离 $f(s',s)=sum_b$。将 $s'_{i+1}$ 由 `a` 换成 `b`，分类讨论，若 $s_{i+1}$ 为 `a`，此时需要将这个 `b` 换回 `a`，$f(s',s)=sum_b+1$；若 $s_{i+1}$ 为 `b`，原来需要将这个字符由 `a` 换为 `b`，而现在不需要，$f(s',s)=sum_b-1$。  
因为到最后一个位置，$sum_a$ 和 $sum_b$ 之间必然有一个数为 $0$，因此可以直接确定。因此这样确定的询问次数为 $n+1$ 次。
## Code
```cpp

string ask,ans;
int suma,sumb,len;
int query(){
    cout<<ask<<endl;
    string s;
    swap(s,ask);
    int x;
    read(x);
    if(!x){//若当前的字符串是答案串，没必要再询问了，答案就是该串
        exit(0);
    }
    return x;
}
signed main(){
    for(int i=1;i<=300;i++){
        ask.pb('a');
    }
    suma=300-query();//询问长度为300的全a串，得到答案串中a的数量
    for(int i=1;i<=300;i++){
        ask.pb('b');
    }
    sumb=300-query();//询问长度为300的全a串，得到答案串中b的数量
    len=suma+sumb;//总长度等于a的数量+b的数量
    for(int i=1;i<len;i++){
        if(!suma||!sumb){
            break;
        }//如果a或b已经都填到位了，剩下的位置都可以确定
        ask=ans;
        ask.pb('b');
        while(ask.size()<len){
            ask.pb('a');
        }//构造s'
        int x=query();
        if(x>sumb){
            suma--;
            ans.pb('a');
        }
        else{
            sumb--;
            ans.pb('b');
        }//大于则为'a'，小于则为'b'
    }
    while(suma){
        suma--;
        ans.pb('a');
    }
    while(sumb){
        sumb--;
        ans.pb('b');
    }//剩下什么填什么
    cout<<ans<<endl;
    return 0;
}
```

---

