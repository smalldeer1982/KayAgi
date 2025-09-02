# Reverse String

## 题目描述

You have a string $ s $ and a chip, which you can place onto any character of this string.

After placing the chip, you move it to the right several (maybe zero) times, i. e. you perform the following operation several times: if the current position of the chip is $ i $ , you move it to the position $ i + 1 $ . Of course, moving the chip to the right is impossible if it is already in the last position.

After moving the chip to the right, you move it to the left several (maybe zero) times, i. e. you perform the following operation several times: if the current position of the chip is $ i $ , you move it to the position $ i - 1 $ . Of course, moving the chip to the left is impossible if it is already in the first position.

When you place a chip or move it, you write down the character where the chip ends up after your action. For example, if $ s $ is abcdef, you place the chip onto the $ 3 $ -rd character, move it to the right $ 2 $ times and then move it to the left $ 3 $ times, you write down the string cdedcb.

You are given two strings $ s $ and $ t $ . Your task is to determine whether it's possible to perform the described operations with $ s $ so that you write down the string $ t $ as a result.

## 说明/提示

Consider the examples.

The first test case is described in the statement.

In the second test case, you can place the chip on the $ 1 $ -st position, move it twice to the right, and then move it twice to the left.

In the fourth test case, you can place the chip on the $ 2 $ -nd position, and then don't move it at all.

In the fifth test case, you can place the chip on the $ 1 $ -st position, move it $ 5 $ times to the right, and then finish the process.

## 样例 #1

### 输入

```
6
abcdef
cdedcb
aaa
aaaaa
aab
baaa
ab
b
abcdef
abcdef
ba
baa```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：xuanxuan001 (赞：5)

>Can you solve this problem in $O(n^2)$ time? Maybe even faster?

话说这次 CF 我不知道在想啥就写了个 $O(n)$ 的做法，结果比赛结束了还没调出来，赛后又调了好长时间，前后交了 15 发才 A 。。

正文
-
思路主要就是枚举在哪里掉头，然后判断。

首先，断点（设它是 $p$，下同）两边应该是回文的，这个用 manacher 算法就可以解决（注意只处理长度为奇数的）。判断条件就是以点 $p$ 为中心的最长回文子串延伸到边界。

上面那个条件满足后，问题就转换成了判断 $t$ 的一个子串是否在 $s$ 中出现，并且这个 $t$ 的子串的一个端点在边界上，所以可以用 KMP 解决~~就是这个 KMP 调的时间最长~~。

如何匹配要分两种情况：

1. $p$ 在 $t$ 的左半段，此时要判断的是 $p$ 右边的后缀翻转后的，这个需要将 $s$ 在翻转后的 $t$ 上匹配，用一个布尔数组来存储每个翻转后的 $t$ 的每个长度的前缀在 $s$ 中有没有匹配。
1. $p$ 在 $t$ 的右半段，此时要判断的是 $p$ 左边的前缀，这同样可以用一个布尔数组来存储所有长度的 $t$ 的前缀。

对于代码的一些说明：

- 这里的 KMP 一般的套路是把匹配串和被匹配串合并，匹配串在前，中间加一些分隔符然后跑正常 KMP 的，但我是分开跑的，所以转移的数组还要另外在被匹配串上跑一遍正常 KMP，写起来很复杂，这是我的失误。
- 本来对于每个 $i$，应该把它的 KMP 值，它的 KMP 的 KMP 值，以此类推的所有相应布尔数组的位置都变成真，但是由于是将所有值都进行，所以不需要。

Code
-
```cpp
#include<cstdio>
#define MAXN 502
using namespace std;
int minn(int a,int b){return a<b?a:b;}
int qr(){
	char ch=getchar();int s=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}return s;
}int T,sl,tl,man[MAXN<<1],r,kmps1[MAXN<<1],kmps2[MAXN<<1],kmp1[MAXN],kmp2[MAXN],tmp;
char s[MAXN],t[MAXN<<1];bool flag,can[MAXN<<1],can2[MAXN<<1];
int main(){
	T=qr();
	while(T--){
		for(int i=1;i<=tl;i++)man[i]=can[i]=can2[i]=0;
		scanf("%s%s",s+1,t+1);r=1;flag=false;
		for(sl=0;s[sl+1]!='\0';sl++);
		for(tl=0;t[tl+1]!='\0';tl++);kmps2[tl]=0;
		for(int i=2;i<=tl;i++){//manacher
			if(i<r+man[r])man[i]=minn(man[(r<<1)-i],r+man[r]-i);
			while(i-man[i]>1&&t[i-man[i]-1]==t[i+man[i]+1])man[i]++;
			if(i+man[i]>r+man[r])r=i;
		}for(int i=2;i<=tl;i++){//前缀的KMP匹配预处理
			tmp=kmps1[i-1];
			while(tmp&&t[tmp+1]!=t[i])tmp=kmps1[tmp];
			if(t[tmp+1]==t[i])tmp++;kmps1[i]=tmp;
		}for(int i=tl-1;i>0;i--){//翻转后的后缀的KMP匹配预处理
			tmp=kmps2[i+1];
			while(tmp&&t[tl-tmp]!=t[i])tmp=kmps2[tl-tmp+1];
			if(t[tl-tmp]==t[i])tmp++;kmps2[i]=tmp;
		}for(int i=1;i<=sl;i++){//前缀的KMP匹配
			tmp=kmp1[i-1];
			while(tmp&&t[tmp+1]!=s[i])tmp=kmps1[tmp];
			if(tmp<tl&&t[tmp+1]==s[i])tmp++;
			kmp1[i]=tmp;can[kmp1[i]]=true;
		}for(int i=1;i<=sl;i++){//翻转后的后缀的KMP匹配
			tmp=kmp2[i-1];
			while(tmp&&t[tl-tmp]!=s[i])tmp=kmps2[tl-tmp+1];
			if(tmp<tl&&t[tl-tmp]==s[i])tmp++;
			kmp2[i]=tmp;can2[kmp2[i]]=true;
		}for(int i=1;i<=tl;i++){
			if(man[i]==i-1)flag|=can2[tl-i+1];//在前半段
			if(man[i]==tl-i)flag|=can[i];//在后半段
		}if(flag)printf("YES\n");
		else printf("NO\n");
	}return 0;
}
```

---

## 作者：cunzai_zsy0531 (赞：4)

## CF1553B题解-by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1553B)

注意到 $|s|\leq 500$，可以直接 $O(n^3)$ 做：枚举一个开头位置、一个转弯位置、一个结束位置，判断能不能匹配上 $t$ 的整个字符串即可。具体细节可以参考代码。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000+13;//数组一定不能开小！注意题中特殊的数据范围限制！
char s[N],t[N];
int n,m;
inline void solve(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;++i){//枚举s中的起始位置，先向右走
		if(s[i]!=t[1]) continue;
		int r=1;
		while(r+1<=m&&i+r<=n&&s[i+r]==t[r+1]) ++r;//首先找到能走到的最右边的位置
		if(r==m) return void(puts("YES"));
		for(int j=1;j<=r;++j){//枚举从哪里开始转弯向左走
			int l=0;
			while(l+1+j<=m&&i+j-l-2>=1&&s[i+j-l-2]==t[l+1+j]) ++l;//这个地方下标的加一减一要注意，可以手画一下加深理解
			if(l==m-j) return void(puts("YES"));
		}
	}
	puts("NO");
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
//B
```


---

## 作者：Sai_t (赞：1)

本题如果用纯暴力做的话（即枚举起点与转折点，向左判断是否可行），理论时间复杂度为 $O(q|s|^2|t|)$，但是其常数及其之小，加上剪枝后，$|s|^2$ 那两层循环几乎是一个不大的常数，所以暴力完全能过。

暴力Code：(纯暴力+基础剪枝，15ms)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;string s,t;int n,m;
bool chk(int x,int y){
	int N=m-y+x;
	for(int j=0;j<N;j++){
		int i=y-j;
		if(s[i]!=t[y-i+y-x])return false;
		if(y-i+y-x==m-1)return true;
	}
	return true;
}
int main(){
	cin>>T;
	while(T--){
		cin>>s>>t;
		n=(int)s.size(),m=(int)t.size();
		bool fl=0;
		for(int i=0;i<n;i++){
			if(s[i]!=t[0])continue;
			for(int j=i;j<n;j++){
				if(s[j]!=t[j-i])break;
				if(chk(i,j)){
					cout<<"YES\n";
					fl=1;
					break;
				}
			}
			if(fl)break;
		}
		if(!fl)cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：Daidly (赞：1)

数据范围较小。

- 考虑先查找到起点。

- 再从起点到结尾枚举断点。

- 最后模拟从起点到断点再往回走的路径判断是否可行即可。

注意：当从断点往回走的路径长度超过断点到起点长度时要特判。

代码如下:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,num,cnt;
string a,b;
bool f=0;
signed main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		n=a.length();
		m=b.length();
		a=' '+a;
		b=' '+b;
		f=0;
		for(int i=1;i<=n;++i){
			if(a[i]==b[1]){
				for(int j=i;j<=n;++j){
					f=1;
					for(int k=i;k<=j;++k){
						if(a[k]!=b[k-i+1])f=0;
					}
					num=m-j+i-1;
					if(num>=j){
						f=0;
						continue;
					}
					for(int k=j-1;k>=j-num;--k){
						if(a[k]!=b[j-i+1+j-k])f=0;
					}
					if(f){
						puts("YES");
						break;
					}
				}
			}if(f)break;
		}
		if(!f)puts("NO");
	}
	return 0;
}
```

---

## 作者：天泽龟 (赞：1)

来一篇纯正的 KMP 题解，不需要考虑任何回文的性质，按理说时间复杂度是 $O(n^2)$，但是不知道为啥有个 $O(n^3)$ 的题解跑的比我快。。

### 题目大意

对于给定的文本串 $s$，判断另一个字符串 $a$ 是否可以表示成**从 $s$ 某一位置开始，先向右移再向左移的路径**（我们不妨称其为“路径串”）。

### 解析

不需要考虑起始点与终止点，我们只需要通过枚举路径的断点 $i$，便可将 $a$ 分为两部分： 一部分是由起始点至断点的路径 $a_1$，以及由断点至终止点的路径 $a_2$。

我们注意到 $a_2$ 是在文本串上倒退走而形成的的路径串，那我们要在文本串倒退着匹配，很不舒服，于是我们干脆存一个 $s$ **的反转串** $s_r$，这样便可做到了在 $s_r$上跑关于$a_2$的 KMP，从而知道是否有该子串了。

若 $s_r$ 存在匹配于 $pos$，我们便将 $pos$ 往后长为 $a_1$的串截出来，与 $a_1$的**反转串**进行比对（注意到我们此时已经在 $s_r$ 上做匹配），若相等，那么就成功了。

最后在特判一下完全包含的情况，就完了。

上我丑陋的代码：
```cpp
#include <bits/stdc++.h>
#define inf 2147483647
#define maxn 5000
#define ck cout<<"OK"<<endl
using namespace std;

string s,a,rs,ra;

vector<int> check(string a)
{
	int n=a.size(),p=0; vector<int> pr(n); 
	for (int i=1;i<n;i++) {
		while (p && a[p]!=a[i]) p=pr[p-1];
		if (a[p] == a[i]) ++p; pr[i]=p;
	}
	return pr;
}

vector<int> kmp(string a,string s)
{
	vector<int> pr;
	vector<int> nex=check(a); 
	int n=a.size(),p=0;
	for (int i=0;i<s.size();i++) {
		while (p && a[p]!=s[i]) p=nex[p-1];
		if (a[p] == s[i]) ++p;
		if (p == n)  pr.push_back(i-n+1);
	}
	return pr;
}

bool fc(string s,vector<int> pos)
{
	int l=s.size();
	for (int i=0;i<pos.size();i++)
	if (pos[i]+l<=rs.size()) {
		string a=rs.substr(pos[i],l);
		if (a==s) return 1;
	}
	return 0;
}

int main()
{
int t; cin>>t;
while (t--)
{	bool flag=0;
	cin>>s; rs=s; reverse(rs.begin(),rs.end());
	cin>>a; ra=a; reverse(ra.begin(),ra.end());
	for (int i=0;!flag && i<a.size();i++)
	{
		string rig=a.substr(i,a.size()-i);
		vector<int> pos = kmp(rig,rs);
		if ( !pos.empty() ) {
			string raa=a.substr(0,i+1); reverse(raa.begin(),raa.end());
			if (fc(raa,pos)) flag=1;
		}
	}
	vector<int> ind=kmp(a,s); if (!ind.empty()) flag=1;
	ind=kmp(ra,s); if (!ind.empty()) flag=1;
	cout<<(flag? "YES":"NO")<<endl; 
}
	return 0;
}

```


---

## 作者：PLDIS (赞：1)

题意：
- 给你两个字符串。
- 现在有一个小片，你可以将它放在第一个字符串的**任意一个位置上**，往右移动若干格（可以为 $0$ 格），再往左移动若干格（可以为 $0$ 格），问小片**从第一次开始覆盖到的字符**组成的字符串可不可以为第二个字符串。
- 比如字符串为 `IAKIOI`，如果将小片放到第二个字符上，即 `A`，然后向右移动 $2$ 格，再向左移动 $1$ 格，最后的字符串即为 `AKIK`。

****

这道题我们可以暴力。我们知道，小片的移动过程为**先右再左**，不可能左右交叉或者先左再右。于是，我们枚举的就是**从向右移动到向左移动的分界线**。最后，判断时，我们需要暴力枚举每个开始处，**按着题中给出的方向模拟一遍**，如果正好符合第二个字符串，输出 `YES` 并停止。如果一直没有符合条件的，输出 `NO`。

如果设第一个串的长度为 $n$，第二个的长度为 $m$，则复杂度约为 $O(n\times m^2)$，因为暴力找分界线为 $O(m)$，寻找开始处 $O(n)$，最后的字符串和原串一个个比对为 $O(m)$。因为题目时间为 $3$ 秒，所以是可以的。

### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(int c, string n, string m){
    string p1 = m.substr(0, c + 1);
    string p2 = m.substr(c + 1, m.length() - c);
    if(p1.length() > n.length() || p2.length() > n.length()){
    	return false;
    }
    for(int i = max(0, int(p2.length() - p1.length() + 1));i <= n.length() - p1.length();i++){
        bool flag = false;
        //模拟，比对
        for(int j = 0;j < p1.length();j++){
            if(n[i + j] != m[j]){
                flag = true;
                break;
            }
        }
        for(int j = 0;j < p2.length();j++){
            if(n[p1.length() + i - j - 2] != p2[j]){
            	flag = true;
            	break;
	        } 
        }
        if(!flag){
            return true; //符合要求
        }
    }
    return false;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        string s, p;
        cin >> s >> p;
        bool flag = false;
        for(int i = 0;i < p.length();i++){
            if(check(i, s, p)){
            	cout << "YES" << endl;
            	flag = true;
            	break;
	        }
        }
        if(!flag){ //如果一直没有符合要求的输出 NO。
            cout << "NO" << endl;
	    }
    }
    return 0;
}
```

---

## 作者：张语诚ZYC (赞：0)

## 思路分析

由于数据巨水，$O(n^3)$ 肯定能过，~~所以像我这样只会暴力的蒟蒻开心极了~~。对于 KMP 的神仙，蒟蒻认为大可不必，毕竟也没叫你找大量子串。

第一步：在字符串 $s$ 中枚举 $t[0]$ 是否存在，如果不存在直接退出，同时输出 “NO”，如果心情好的话，可以枚举一下 $t[x-1]$，其中设 $x=$`strlen(t)` 。

第二步：对于每一个枚举出的 $t[0]$ 一个一个向前向后枚举，如果出现不存在的情况，退，输出 “NO”，若找到正解，输出 “YES”。 

~~代码就不贴了~~

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1553B)

一句话题意：在给定字符串 $s$ 中，可以以任意点为起点，先向右任意格，再向左任意格，就会得到一个新的字符串，求能否得到给定的字符串 $t$。

显然，起点 $i$ 必须满足 $s_i=t_0$。因此可以枚举出所有可能的起点 $i$。

对于每个可能的起点 $i$，暴力向下枚举所有可能的拐点 $j$，然后根据拐点 $j$ 的位置处理出一个长度与 $t$ 相同的字符串，直接判断这个字符串是否与 $t$ 完全相同即可。如果找不到这样的字符串，则说明无解。

细节：多测一定要清空！每次处理新字符串时要清空原字符串！

时间复杂度 $O(q|s|^2)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned long long
using namespace std;
int read()
{
    int x=0,f=1;
	char ch=getchar();
    while(ch<'0'||ch>'9')
    {
      	if(ch=='-')
      		f=-1;
      	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
      	x=x*10+ch-'0';
      	ch=getchar();
    }
    back x*f;
}
char s[10001],t[10001],s1[10001];
int q,n;
int main()
{
	cin>>q;
	while(q--)
	{
		memset(s1,0,sizeof(s1));
		bool flag=0;
		cin>>s>>t;
		int ls=strlen(s),lt=strlen(t);
		for(ri i=0;i<ls;i++)
		{
			if(s[i]==t[0])
			{
				memset(s1,0,sizeof(s1));
				for(ri j=i;j<=ls;j++)
				{
					int lsbl=-1;
					for(ri k=i;k<=j;k++)
						s1[++lsbl]=s[k];
					for(ri k=j-1;k>=0&&lsbl<lt-1;k--)
						s1[++lsbl]=s[k];
					if(strcmp(s1,t)==0)
					{
						cout<<"YES"<<endl;
						flag=1;
						break;
					}
				}				
			}
			if(flag==1)
				break;
			
		}
		if(flag==0)
			cout<<"NO"<<endl;
	}
    back 0;
}
```

---

## 作者：Cocoly1990 (赞：0)

看大家又是~~看毛片~~KMP又是回文串的，其实不至于。赛时随手糊了一个小的暴力，一不小心就过了，赛后也没有FST。

仔细观察目标字符串，可以发现我们必然要把选择一个断点，将目标字符串分成两段，分别在原字符串内进行匹配，很显然，断点前的那一段需要正向匹配，而断点后的一段则需要逆向匹配。

那么两段匹配时在原字符串的起点和终点呢？嗯，没错，第一段的起点可以选择，而第二段的起点必然为第一段的终点的**前一个字符**（注意第二段是**逆向匹配**）。至于怎么**逆向匹配**，其实只需要将目标字符串翻转一下就好，这样就可以当做**正向匹配**来做。

那么思路就很明确了，枚举断点，枚举以第一段的起点，综合时间复杂度 $\mathcal{O}\left(\sum\limits_{i=1}^q t_i^3 \right)$，或者可以写成 $\mathcal{O}\left(\texttt{3s可以过} \right)$.


贴个代码，感觉写的蛮清楚的

```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans = 2147483647 , T ;
string s , t ;
bool flag ;
int main()
{
	cin >> T ;
	while(T --)
	{
		cin >> s >> t ;
		flag = 0 ;
		string s1 = s ;
		reverse(s1.begin() , s1.end()) ;
		//cout << s << endl << s1 << endl ;
		int lens = s.size() ;
		int lent = t.size() ;
		for(int i = 1 ; i <= lent ; i ++)
		{
			for(int j = 0 ; j <= lens - i ; j ++)
				if(t.substr(0 , i) == s.substr(j , i) && t.substr(i , lent - i) == s1.substr(lens - j - i + 1, lent - i)) flag = 1 ;
		}
		if(flag) cout << "Yes" << endl ;
		else cout << "No" << endl ;
	}
	return 0 ;
}
```

---

## 作者：Jr_Zlw (赞：0)

# 字符串板子

考虑如果一个  $t$   串是合法的，分  $2$  种情况讨论：

-   $t$  串被完全包含在  $s$  串中。

-   $t$  串由指针折返了一次得到。

第一种情况直接暴力跑一遍  KMP  就行了。

对于第二种情况，考虑由于有折返，那么  $t$  长度为奇数的回文串。

暴力处理一遍  $t$  得出回文串即可。

枚举每一个作为回文串的前缀或后缀，由于先向右再向做走，用回文串的后一半跑  KMP  ，如果匹配上了，暴力再匹配一下剩下的字符就可以了。

具体来说就是：

- 前缀为回文串：挖掉回文前缀后正着记录剩下的串。在匹配成功位置左端点的前面倒序匹配一下记录下的串，如果都能匹配证明可以。

- 后缀为回文串：挖掉回文后缀后倒序记录剩余的串，如上在  KMP  中匹配。

最差时间复杂度 $O(n^3)$，卡的过去。

（晚上打CF降智了用了马拉车算回文，时间复杂度被覆盖了还调了好久）

代码

```
#include<bits/stdc++.h>
#define rep(a,b,c) for(register int c=(a);c<=(b);++c)
#define drep(a,b,c) for(register int c=(a);c>=(b);--c)
#define Clear(a)  memset(a,0,sizeof(a))
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();bool flag=0;
	while(ch<'0'||ch>'9')flag^=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();
	return flag ? -res : res ;
}
const int N=2010;int ans[N];char s[N],t[N],s2[N];
struct Manacher
{
	char s[N<<1];
	inline void mnc(char *a,int *ans)
	{
		int A=strlen(a);int r=0,mid=0;rep(1,A-1,i)
		{
			if(i<=r){ans[i]=min(ans[(mid<<1)-i],r-i+1);}
			while(a[i+ans[i]]==a[i-ans[i]])++ans[i];
			if(ans[i]+i>r)r=ans[i]+i,mid=i;
		}
	}
	inline int qry(char *q,int *res)
	{
		int Q=strlen(q),len=1;s[0]='$';s[1]='|';
		rep(0,Q-1,i)s[++len]=q[i],s[++len]='|';
		mnc(s,res);return len;
	}
}M;
int nxt[N];inline bool kmp(char *a,char *b,char *c)
{
	nxt[0]=nxt[1]=0;int A=strlen(a+1),B=strlen(b+1),C=strlen(c+1),j=0;
	rep(2,B,i){while(j&&b[j+1]^b[i])j=nxt[j];j+=(b[i]==b[j+1]);nxt[i]=j;}
	j=0;rep(1,A,i)
	{
		while(j&&b[j+1]^a[i])j=nxt[j];
		if((j+=(a[i]==b[j+1]))==B)
		{
			int st=i-j+1;bool flag1=1;
			rep(1,C,k){--st;if(a[st]^c[k]||!st){flag1=0;break;}}
			if(flag1){return 1;}
		}
	}
	return 0;
}

char q[N],g[N];inline void Solve()
{
	Clear(g);Clear(q);
	scanf("%s%s",s+1,t);int T=strlen(t);
	rep(1,T,i)q[i]=t[i-1];if(kmp(s,q,g)){puts("Yes");return;}
	int L=M.qry(t,ans);
	rep(1,L,i)
	{
		if(ans[i]==i&&M.s[i]<='z'&&M.s[i]>='a')
		{
			memset(g,0,sizeof(g));memset(q,0,sizeof(q));
			int l=i>>1;rep(1,l,j)q[j]=t[j-1];
			int tmp=0;rep(l<<1,T,j)g[++tmp]=t[j-1];
//			if(i==6){rep(1,tmp,k)putchar(g[k]);puts("");rep(1,l,k)putchar(q[k]);puts("");}
			if(kmp(s,q,g)){puts("Yes");return;}
		}
		if(ans[i]==L-i+1&&M.s[i]<='z'&&M.s[i]>='a')
		{
			memset(g,0,sizeof(g));memset(q,0,sizeof(q));
			int l=ans[i]>>1;int tmp=0;drep(T,T-l+1,j)q[++tmp]=t[j-1];
			int tmp2=0;int st=T-l+1-l;drep(st,1,j)g[++tmp2]=t[j-1];
//			if(ans[i]==4){rep(1,tmp2,k)putchar(g[k]);puts("");rep(1,tmp,k)putchar(q[k]);puts("");}
			if(kmp(s,q,g)){puts("Yes");return;}
		}
	}
	puts("No");
}
int main(){int T=read();while(T--)Solve();return 0;}
```

---

