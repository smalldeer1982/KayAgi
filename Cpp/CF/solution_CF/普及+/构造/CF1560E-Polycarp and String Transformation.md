# Polycarp and String Transformation

## 题目描述

Polycarp has a string $ s $ . Polycarp performs the following actions until the string $ s $ is empty ( $ t $ is initially an empty string):

- he adds to the right to the string $ t $ the string $ s $ , i.e. he does $ t = t + s $ , where $ t + s $ is a concatenation of the strings $ t $ and $ s $ ;
- he selects an arbitrary letter of $ s $ and removes from $ s $ all its occurrences (the selected letter must occur in the string $ s $ at the moment of performing this action).

Polycarp performs this sequence of actions strictly in this order.

Note that after Polycarp finishes the actions, the string $ s $ will be empty and the string $ t $ will be equal to some value (that is undefined and depends on the order of removing).

E.g. consider $ s $ ="abacaba" so the actions may be performed as follows:

- $ t $ ="abacaba", the letter 'b' is selected, then $ s $ ="aacaa";
- $ t $ ="abacabaaacaa", the letter 'a' is selected, then $ s $ ="c";
- $ t $ ="abacabaaacaac", the letter 'c' is selected, then $ s $ ="" (the empty string).

You need to restore the initial value of the string $ s $ using only the final value of $ t $ and find the order of removing letters from $ s $ .

## 说明/提示

The first test case is considered in the statement.

## 样例 #1

### 输入

```
7
abacabaaacaac
nowyouknowthat
polycarppoycarppoyarppyarppyrpprppp
isi
everywherevrywhrvryhrvrhrvhv
haaha
qweqeewew```

### 输出

```
abacaba bac
-1
polycarp lcoayrp
is si
everywhere ewyrhv
-1
-1```

# 题解

## 作者：Miraik (赞：14)

一道不错的字符串题。

首先容易得到结论：从字符串  $t$ 的末尾向前遍历，越早出现的字符越迟被删掉。

为什么呢？以样例的第一组数据为例：

$t=\texttt{abacabaaacaac}$

可以逆推出初始串逐渐被删除的过程：

$\texttt{c}$ ——> $\texttt{aacaa}$ ——> $\texttt{abacab}$

这样我们就得到了第二问的解（当然，这个解最终不一定存在）



------------



那么，我们应该如何根据第二问的解，来推出第一问的解（初始串）呢？

我们统计出每个字符的出现次数，设为 $f_i$。

对于字符 $i$，如果它在第 $q$ 轮操作中被删除，那么它在初始串中的出现次数即为 $\frac{f_i}{q}$。如果任意一个 $f_i$ 不能 $q$ 整除，那么解就不成立了，输出 $-1$。

通过上面的方式，我们将所有字符的出现次数加在一起，就得到了初始串的长度 $l$，然后取 $t$ 的前 $l$ 个字符，就是初始串了。



------------

### 但是！

我们这样求出的解，仍然不一定是存在的！

为什么呢？

以样例的最后一组数据为例（良心样例，点赞）：


$t=\texttt{qweqeewew}$

我们按照上面的做法得出：

第二问的解：$\texttt{qew}$

初始串：$\texttt{qweqe}$

这时我们发现，欸，好像有点不对？

我们用这个解来构造出对应的字符串 $t$ 

$\texttt{qweqe}$ ——> $\texttt{wee}$ ——> $\texttt{w}$

$t=\texttt{qweqeweew}$

怎么和给出的 $t$ 不一样了？

我们在上面求初始串时，判断任意一个 $f_i$ 不能 $q$ 整除，那么解就不成立了。

但是实际上我们不仅出现次数要正确，出现的 **顺序** 也要正确。

对此，我们就按照题面中给的操作过程将得到的解检验一遍即可。

代码：

```cpp
/*
+   +   +   +    +++     +++++     ++++
 + +     + +      +         +      +   +
  +       +       +        +       +   +
 + +      +       +       +        +   +
+   +     +      +++     +++++     ++++
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
const int inf=1<<30;
const ll inff=1ll<<60;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
string s,s1,s2,s3;
int l,f[35],ans[35],cnt;
void solve(){
	cin>>s;
	int sz=s.size();
	for(int i=0;i<26;i++)f[i]=0;
	cnt=0;
	for(int i=sz-1;i>=0;i--){//倒序处理，得到第二问的解
	    if(!f[s[i]-'a'])ans[++cnt]=s[i]-'a';
	    f[s[i]-'a']++;
	}
    //注意我们求出来的第二问的解实际上也是倒序的，
    //但是由于我比较懒就没有数组翻转了
	l=0;
	for(int i=1;i<=cnt;i++)
	    if(f[ans[i]]%(cnt-i+1)!=0){//cnt-i+1即ans[i]出现的轮数
	    	puts("-1");//这个解已经不合法了
			return;
	    }
	    else l+=f[ans[i]]/(cnt-i+1);
        //求出初始串的长度l
	s1="",s2="";
	for(int i=0;i<l;i++)s1+=s[i];
	int now=cnt;
    //接下来是模拟，检验解的合法性
    //s1为当前的字符串，s2为字符串对应的串t，s3用来更新s1
	while(s1!=""){
		s2+=s1;
		s3="";
		sz=s1.size();
		for(int i=0;i<sz;i++)
		    if(ans[now]!=s1[i]-'a')
				s3+=s1[i];
		s1=s3;
		now--;
	}
	//cout<<s2<<'\n';
	if(s2==s){//如果检验得到的串t与给出的串t相同，那么这个解是合法的
		for(int i=0;i<l;i++)cout<<s[i];
		cout<<' ';
		for(int i=cnt;i;i--)putchar(ans[i]+'a');
		puts("");
	}
	else puts("-1");//解不合法，输出-1
}
int main(){int tests=1;tests=read();
while(tests--){
	solve();
}	return 0;
}

```


---

## 作者：LinkZelda (赞：5)

- **题意**：

Polycarp 有一个字符串 $s$，初始时令 $t=s$。每次选择一个 $s$ 中至少出现一次的字符，然后把 $s$ 中的所有这个字符删去，然后令 $t=t+s$。这里的 $+$ 表示将两个字符串拼接。

$T$ 组数据，每次给定按上述步骤生成的字符串 $t$，请你求出一组合法的 $s$ 以及删除的顺序。

$\sum \left\vert t\right\vert \leq 5\cdot10^5,T\leq 10^4$。

- **做法**：

考虑 $t$ 中最后一个位置的字符肯定是最后删去的，倒数第二个字符（也就是从后往前第一个不同于最后一个位置）的字符肯定是倒数第二个删的......以此类推，我们就可以把删字符的顺序确定下来。

接下来，我们对每个字符开一个桶 $cnt$ 记录它的出现次数，那么这个字符串有解的一个必要条件显然是：对于第 $i$ 个删去的字符，该字符在全串中的出现次数 $cnt_i$ 必为 $i$ 的倍数。如果不满足直接判为无解即可。

然后我们算出字符串 $s$ 的长度 $Cnt$，显然 $Cnt$ 即为所有 $\frac{cnt_i}{i}$ 求和。按照题目模拟一下，如果出现问题直接判断无解。

最后如果不是无解，直接输出即可，时间复杂度为 $O(\sum\left\vert t\right\vert)$。

- [代码](https://www.luogu.com.cn/paste/wlh00mp6)

---

## 作者：Illusory_dimes (赞：2)

[还须要往下翻却仍然不一定有更好的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15169251.html)

## description

对于一个串，每次选择一个字符，设新串式将原串中所有这个字符全部删去（删去后不恢复），然后把新串接到上一次的新串后面（第一个新串就在前面加一个原串）。

现在给定了所有新串接起来的长串，求原串和每次选择的字符构成的小串

## solution

好像乍一看，直接硬上是不行的，看看哪里有突破口。

看了半天，发现好像输出里面后面那个小串能直接算，只要从后往前扫。

最先出现的就是最后删除的，

其次出现的就是倒数第二个删除的，然后以此类推。

（不能顺着找，谁知道原串是怎么排列的呀）

因为每次删完这个字符，之后接到后面的串就不存在这个字符了，所以可以这样直接求出。

（所以不能顺着找呀）

感觉可以先求有解的情况下原串应该的长度，并且能够算出原串每个字符要有多少个。

因为只要不删掉这个字符，每次复制一遍的话，数量就会加倍，正好已经求出了小串：

对于第一个删掉的字符，数量只被复制了一遍，

对于第二个删掉的字符，数量被复制了两遍，之后又是以此类推。

又因为，被删掉后不会再出现，所以只要预处理 26 个字符各出现了几次，就能算了（连哪个位置都不需要）

最后模拟一遍构造方式，验证一下就行。

因为题目给的字符串有可能是乱写的，导致计算原串长度的时候因为除不尽或者位置不对，反而算完长度之后不会检查出来，所以再检查一遍。

（不验证的话其实可以去掉大部分无解的串，但不能做到滴水不漏，比如样例 abacabaaacaac ，如果改成 abcaabaaacaac，即使预处理算 26 种字符的个数时加上了位置，也很难检查出来是错的，所以还是得检查一遍至少比较方便。。）


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,m,cnt[28];
string s;
inline void clear(){
	memset(cnt,0,sizeof(cnt));
}
inline void mian(){
	clear();
	string ans,tot;
	cin>>s;n=s.size();
	for(int i=n-1;~i;--i){
		if(!cnt[s[i]-'a'+1])tot+=s[i];
		++cnt[s[i]-'a'+1];
	}
	m=tot.size();n=0;
	reverse(tot.begin(),tot.end());
	for(int i=0;i<m;++i){
		n+=(cnt[tot[i]-'a'+1])/(i+1);
		//这一位应该在原串中出现几次
	}
	if(n>s.size()){
		printf("-1\n");
		return ;
	}
	ans=s.substr(0,n);
	string chk,add=ans;
	for(int i=0;i<m;++i){
		chk+=add;
		string now;
		for(int j=0;j<n;++j){
			if(add[j]!=tot[i])now+=add[j];
		}
		add=now;n=add.size();
	}
	if(chk!=s){
		printf("-1\n");
	}
	else cout<<ans<<" "<<tot<<"\n";
}
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;++i)mian();
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/1560/problem/E)

比 F 难吧。

#### 分析：

首先发现，从后往前扫 $t$，如果当前字符第一次出现，把它塞入 $ord$ 的末尾。扫描完后，反转 $ord$，就是字符删除的顺序。这个不难理解。

确定了顺序以后，计算每个字符，在 $s$ 中的出现次数，假设一个字符在第 $i$ 轮被删除，一共在 $t$ 中出现了 $k$ 次，那么它在 $s$ 中就应该出现 $\frac{i}{k}$ 次。这样就能确定初始 $s$ 里字符 $j$ 的出现次数，记作 $occ(j)$。如果不合法就直接删掉。

然后我们扫描 $t$ 就能得到 $s$，但是还要判断其是否合法。

赛场上我脑子进水写了一百多行垃圾代码调了一小时过去，把二十分钟前四题的手速优势全玩没了（）。

考虑如何模拟 $s$ 得到 $t$ 的过程，首先考虑对 $s$ 再模拟一遍然后判断是不是和 $t$ 相同。发现我们模拟的瓶颈在于每次删除一个字符的所有出现位置。首先考虑用 vector 记录一类字母的所有出现位置。然后我们可以使用类似链表的数据结构维护删除，但是方便起见可以直接用一个 set 来维护：初始化的时候塞入 $1\sim |S|$，每次删除的时候把 vector 里的对应位置删了就行。

单次时间复杂度 $O(|t|\log |t|)$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=5e5+10;
int T,n,t[30],t2[30],cnt,rk[30],flag,tot,occ[30];
char s[MAXN],ret[MAXN],ord[30];
set<int>S;
vector<int>pos[30];
int check(){
	rep(i,1,cnt){
		if(t2[ord[i]-'a'] != occ[ord[i]-'a'])return 0;
	}
	return 1;
}
int valid(){
	S.clear();
	rep(i,0,25)pos[i].clear();
	rep(i,1,tot){
		pos[ret[i]-'a'].pb(i);
		S.is(i);
	}
	int start=1,rd=cnt;
	while(S.size()){
		ll sz=S.size();
	//	printf("start:%d sz:%d\n",start,sz);
		if(start+sz-1 > n)return -1;
		sit it=S.begin();
		while(it!=S.end()){
			int val=*it;
			if(ret[val] != s[start])return -1;
			it++; 
			start++;
		}
		sz=pos[ord[rd]-'a'].size();
		rep(j,0,sz-1){
		//	printf("擦除 %c %d\n",ord[rd],pos[ord[rd]-'a'][j]);
			S.erase(pos[ord[rd]-'a'][j]);
		}
		rd--;
	}
	if(start!=n+1)return -1;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);n=strlen(s+1);
		memset(t,0,sizeof t);
		memset(t2,0,sizeof t2);
		memset(rk,0,sizeof rk);
		memset(occ,0,sizeof occ);
		flag=1;cnt=tot=0;
		per(i,n,1){
			if(!t[s[i]-'a']){
				ord[++cnt]=s[i];
				rk[s[i]-'a']=cnt;
			}
			t[s[i]-'a']++;
		}
		rep(i,1,cnt){
			int num=t[ord[i]-'a'];
			if(num % (cnt-i+1)!=0){
				flag=0;
				break;
			} 
			occ[ord[i]-'a']=num/(cnt-i+1);
		}
		if(flag==0){printf("-1\n");continue;}
		flag=0;
		rep(i,1,n){
			t2[s[i]-'a']++;
			if(t2[s[i]-'a'] > occ[s[i]-'a'])break;
			if(check()){
				rep(j,1,i){
					ret[++tot]=s[j];
				}
				flag=1;
				break;
			}
		}
		if(!flag){printf("-1\n");continue;}
		if(valid()==-1){printf("-1\n");continue;}
		rep(i,1,tot)printf("%c",ret[i]);printf(" ");
		per(i,cnt,1)printf("%c",ord[i]);printf("\n");
	}

	return 0;
}
```

---

## 作者：123zbk (赞：1)

首先考虑删字母顺序的字符串 $a$。从字母串 $t$ 的末尾向前遍历，越早出现的字母越迟被删掉，所以 $a$ 是很好求的。

然后我们要求出初始字符串 $s$ 的长度。我们设在操作完之后的字符串 $t$ 中每一个字符 $i$ 的出现次数为 $cnt_i$，在原始字符串 $s$ 中为 $tot_i$，且 $i$ 是第 $q$ 个被删除的，那么有：$q\times tot_i=cnt_i$。
            
现在我们可以求出 $q$ 和 $cnt_i$，那么只要任意一个 $cnt_i$ 不能被 $q$ 整除，就不可能存在字符串 $s$。如果全部整除，我们将所有的商加在一起，就一定是原始字符串 $s$ 的长度 $len$，所以在字符串 $t$ 中截取前 $len$ 位就是答案。

但是这并不能完全准确地判断。关注最后一个样例 qweqeewew，按照之前的做法得到的 $a = \texttt{qew}$，$s= \texttt{qweqe}$。可是当我们将它复原回去时，$t = \texttt{qweqeweew}$。与给出的不一样。所以还要注意字母出现的顺序。

在截取前 $len$ 位之后只需按照删除的顺序模拟一遍，看是否与原字符串相同即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,cnt[28],ok,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		string s,t;
		memset(cnt,0,sizeof(cnt));
		ok=n=0;
		cin>>s;
		int len_s=s.size();
		for(int i=len_s-1;i>=0;i--)
		{
			if(cnt[s[i]-'a'+1]==0)
			{
				t+=s[i]; 
			}
			cnt[s[i]-'a'+1]++;//每一个字符出现的次数	
		}	
		reverse(t.begin(),t.end());//删除顺序 
		int len_t=t.size();
		for(int i=0;i<len_t;i++)
		{
			if(cnt[t[i]-'a'+1]%(i+1)!=0)//总共的出现次数必须是删除顺序的倍数 
			{
				ok=1;
				break;
			}
			n+=(cnt[t[i]-'a'+1])/(i+1);//原始字符串的真正长度 
		}
		if(ok==1)
		{
			puts("-1");
		}
		else//模拟一遍
		{
			string ans=s.substr(0,n);//截取前n个 
			string add=ans;
			string res;
			for(int i=0;i<len_t;i++)
			{
				res+=add;//全部拼接在一起 
				string now;//目前这一块的字符串 
				for(int j=0;j<n;j++)
				{
					if(add[j]!=t[i])
					{
						now+=add[j];
					}
				}
				add=now;
				n=add.size();
			}
			if(res!=s)
			{
				puts("-1");
			}
			else
			{
				cout<<ans<<" "<<t<<endl;
			}	
		} 
	} 
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：1)

$\Large{\text{Solution}}$

其实是偏模拟的一道题。

观察后你会发现，最后一个字符就是最后删掉的 ~~（废话）~~，同理可得从后往前第二种字符就是倒数第二个删除的。我们就可以找出删除的顺序了。

知道染色的顺序，我们就知道每个字符重复了几次，用字符出现的总次数除以它就知道每段中出现的次数（除不尽就无解），把每种字符每段出现的次数加起来就是第一段，也就是要求的 $s$ 的长度，$t$ 的前这么多个字符就是 $s$。用删除的顺序和原字符串验证即可。

$\Large{\text{Code}}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int cnt[130], cnt2[130];

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		memset (cnt, 0, sizeof cnt);
		memset (cnt2, 0, sizeof cnt2);
		string s;
		cin >> s;
		string sx = "";
		for (int i = s.size () - 1; i >= 0; i--)
		{
			if (!cnt[s[i]]) sx = s[i] + sx;
			cnt[s[i]]++;
		}
		bool flag = true;
		int len = 0;
		for (int i = 0; i < sx.size (); i++)
		{
			if (cnt[sx[i]] % (i + 1) != 0)
			{
				flag = false;
				break;
			}
			len += cnt[sx[i]] / (i + 1);
		}
		string ans = s.substr (0, len), now = ans;
//		cout << ans << " " << sx << endl;
		string tep = "";
		for (int i = 0; i < sx.size (); i++)
		{
			string next = "";
			tep += now;
			for (int j = 0; j < now.size (); j++)
				if (now[j] != sx[i]) next += now[j];
			now = next;
		}
		if (tep == s) cout << ans << " " << sx << endl;
		else cout << -1 << endl;
	}
	return 0;
}
```

---

## 作者：きりと (赞：1)

[My Blog](https://starshadow-silent.github.io/) 

### 题目大意

起初有一个小写字符串 $s$ 和一个空串 $t$，现对 $s$ 进行一些操作，每次操作会选择一个字母，并删除 $s$ 中所有此字母，然后将 $s'$ 加入 $t$ 的末尾，直到 $s$ 为空。

已知 $t$ ，求原串 $s$ 以及字母删除顺序，若无解输出 $-1$。

### 解题思路

先考虑怎么求删除顺序，首先可以确定的是，$t$ 末尾最后一个字母一定是最后被删的，然后在此之上，发现从后往前，越早出现的字母一定越晚被删，直接拿个 `map` 啥的求一下删除顺序。

在知道删除顺序以后，可以发现，**每一个**在第 $i$ 次操作被删掉的字母一定会被复读 $i-1$ 次，也就是在 $t$ 中出现 $i$ 次，那我们直接预处理出每个字母在 $t$ 中出现的次数 $v[i]$，然后按删除顺序遍历一遍字母，每个字母会在 $s$ 中出现 $\frac{v[i]}{i}$ 次，如果除不通那就无解，最后累加一下各个字母出现次数，记为 $l$，$t$ 的前 $l$ 个字符就可能是原串 $s$。

然后发现样例最后一个有问题，如果一些无解情况，换了顺序不换字母数量就会被搞，所以最后要再按题意模拟一遍看看和 $t$ 是不是一样的。

赛时~~由于前一天熬夜打派~~，困得头昏脑涨，没想到 $t$ 中前 $l$ 个就是可能答案，在写 KMP，然后就因为调了太久，导致比赛结束约 $30s$ 以后才写出来。

![](https://pic.imgdb.cn/item/6103a1ec5132923bf89ab087.png)

### Code

```cpp
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
#define int long long
#define forr(i,l,r) for(register int i=l;i<=r;i++)
#define ffor(i,r,l) for(register int i=r;i>=l;i--)
using namespace std;
const int N=5e5+10;
int v[27];
int cc;
char ans[27];
int f[N];
string n;
signed main()
{
	int t;
	cin>>t;
	flag:while(t--)
	{
		memset(v,0,sizeof(v));
		forr(i,1,26)
		{
			ans[i]=' ';
		}
		cc=0;
		cin>>n;
		int l=n.size();
        if(l==1)
        {
            cout<<n<<" "<<n<<endl;
            continue;
        }
		n=' '+n;
		ffor(i,l,1)
		{
			if(!v[n[i]-'a'])
			{
				ans[++cc]=n[i];
			}
			v[n[i]-'a']++;
		}
		int ll=0,e,o;
		ffor(i,cc,1)
		{
			e=cc-i+1;
			o=v[ans[i]-'a'];
			if(o%e!=0)
			{
				puts("-1");
				goto flag;
			}
			ll+=o/e;
		}
		memset(v,0,sizeof(v));
		string q=" ",qq=" ";
		forr(i,1,ll)
		{
			q+=n[i];
			qq+=n[i];
		}
		ffor(i,cc,1)
		{
			v[ans[i]-'a']=1;
			forr(j,1,qq.size()-1)
			{
				if(!v[qq[j]-'a'])
				{
					q+=qq[j];
				}
			}
		}
		if(q!=n)
		{
			puts("-1");
			continue;
		}
		forr(i,1,qq.size()-1)
		{
			cout<<qq[i];
		}
		cout<<" ";
		ffor(i,cc,1)
		{
			cout<<ans[i];
		}
		puts("");
	}
}

```



---

## 作者：ChenYanlin_20 (赞：0)

### 思路
每拼接一次，字符串 $s$ 的字母会少一，不难发现，第一次拼接的字符串一定是全字符，最后一次所拼接的一定只剩下一个字符，我们可以从最后一个字母开始往前搜，每搜到一个新字母，将其加入字符串表示顺序，并统计他的出现次数，根据字母去除的先后顺序求出其真正的次数。

比如一字符串字母去除顺序先后为 $ a , b ,c $  ,已知 $c$ 的出现次数为 $3$ ，由于最后一次去除，相当于三次拼接都出现在了字符串中，真实次数应除 $3$ 。

求出每个字母的次数后，我们只需要模拟一边删数的过程，最后与原串 $t$ 对比就可以了。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int INF=1e9;
int t,ans;
int sum[1500];
signed main(){
	int t;
	cin>>t;
	while(t--){
		memset(sum,0,sizeof sum);
//		vector<int> ss;
		string s;
		cin>>s;
		string ss="";
		for(int i=s.size()-1;i>=0;i--){
			if(sum[s[i]]==0){
//				ss.push_back((int)s[i]);
				ss=s[i]+ss;
			}
			sum[s[i]]++;
		}
		int len=0;
		bool flag=0;
		for(int i=0;i<ss.size();i++){
//			cout<<ss[i]<<' '<<sum[ss[i]]<<'\n';
			if(sum[ss[i]]%(i+1)!=0){
				flag=1;
				break;
			}
			sum[ss[i]]/=(i+1);
			len+=sum[ss[i]];
			
		}
		string yuan="",last="",yy="";
		last=s.substr(0,len);//从0开始截取len 
		if(flag){
			cout<<"-1\n";
		} 
		else{
			yy=last;
			int j=0;
			while(last.size()){
			    yuan+=last;
			    string xx="";
			    for(int i=0;i<last.size();i++){
			        if(last[i]!=ss[j]) xx+=last[i];
			    }
			    last=xx;
			    j++;
			}
// 			for(int i=0;i<ss.size();i++){
// 				string xx="";
// 				for(int j=0;j<last.size();j++)
// 					if(last[j]!=ss[i]) xx+=last[j];
// 				yuan+=last;
// 				last=xx;
// //				cout<<yuan<<'\n';
// 			}
			if(yuan==s) 
				cout<<yy<<' '<<ss<<'\n';
			else{
//				cout<<yuan<<' '<<s<<'\n';
				cout<<"-1\n";
			}
				
		}
	}
    return 0;
}
```

---

## 作者：_shine_ (赞：0)

考场万万不要用 ios 加速，三道爆零印象深刻。

首先发现第二个输出很好做，即按照每个字符最后出现的位置从后往前输出即可。

而第一个输出难度在于不好进行分段操作，但是手玩有解样例即可发现每段出现的同一字符数量均相同（未出现的除外），则可以此简单划分出每一个的范围，则有解情况下答案可解。

对于无解情况，无论如何第二个输出会有答案，而无解在于其均分无法完全均匀以及其在之后每段均不相同（删去的不算），特判即可。
#### code
代码赛事未发现 ios 问题而导致含有大量戾气语言，敬请谅解。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=1e6+10; 
int p[200],p1[200],p2[200],p3[200],p4[200],kinds;
int g[maxn],g1[200],l[maxn],r[maxn];
bool check(){
	for(int i='a';i<='z';++i)if(p2[i]!=0){return false;}
	return true;
}
string get_do(string t,string ans2){
	for(int i='a';i<='z';++i){
		if(p1[i]==0 || p[i]==0)continue;
		if(p1[i]%p3[i]==0)p2[i]=p1[i]/p3[i];
		else return "-1";
//		cout << p1[i] << " " << p3[i] << " " << (char)i << endl;	
	}
//	cout << "mk" << endl;
	string ans="";
	for(int i='a';i<='z';++i)p4[i]=p2[i];
	for(int i=0;i<t.size();++i){
		if(check()==true)break;
		ans+=t[i],p2[t[i]]--;
//		cout << ans << endl;
	}
	memset(g1,0,sizeof(g1));
	for(int i=0;i<t.size();++i){
		g1[t[i]]++;
//		cout << g1[t[i]] << " " << g1[t[i]] << " " << p4[t[i]] << endl;
		g[i]=(g1[t[i]]-1)/p4[t[i]]+1;
//		cout << g[i] << " ";
	}
//	cout << "mdf" << endl;
//	puts("what?");
	for(int i=0;i<t.size();++i){
		if(g[i]<g[i-1]){
			return "-1";
		}
	}
	memset(l,0x3f,sizeof(l));
	memset(r,-0x3f,sizeof(r));
	for(int i=0;i<t.size();++i){
		l[g[i]]=min(l[g[i]],i);
		r[g[i]]=max(r[g[i]],i);
	}
	for(int i=0;i<ans2.size()-1;++i){
		int now_y=l[i+2];
//		cout << l[i+2] << " " << l[i+1] << endl; 
		for(int j=l[i+1];j<=r[i+1];++j){
			if(t[j]==ans2[i])continue;
//			cout << t[j] << " " << t[now_y] << " " << j << " " << now_y << endl;
			if(t[j]!=t[now_y])return "-1";
			now_y++;
			if(now_y>r[i+2])break;
		}
	}
//	cout << ans << endl;
	return ans;
}
signed main(){
	int T;cin >> T;
	while(T--){
		memset(p,0,sizeof(p));
		memset(p2,0,sizeof(p2));
		memset(p1,0,sizeof(p1));
		string t;cin >> t;
		string ans2="";
		for(int i=t.size()-1;i>=0;--i){
			if(p[t[i]]==0)p[t[i]]++,kinds++,ans2=t[i]+ans2;
			p1[t[i]]++;
		}
		for(int i=0;i<ans2.size();++i)p3[ans2[i]]=i+1;
		string ansp=get_do(t,ans2);
		if(ansp!="-1")cout << ansp << " " << ans2 << endl;
		else puts("-1");
	}		
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：0)

这题是一道 $ 10^4 $ 的多测题。

有一个串 $ S $ ，进行过如下操作：

1. 把 $ S $ 拼接到一个字符串 $ T $ 后面。

2. 删除 $ S $ 中任意一种字符。

3. 若 $ S $ 非空，回到步骤 $ 1 $ 。

现在给你 $ T $ ，让你求出一种可能的S与删除字符的顺序，无解输出 $ -1 $ 。

 $ |T| \leq 5 \times 10^5 $ 
 
 $ \sum |T| \leq 5 \times 10^5 $ 

题目要求我们做到 $ O(|T|) $ 左右。

------------

首先，只有 $ 26 $ 种字符。

 $ T $ 中每个字符最后出现的相对位置就是删除的顺序。

因为你删除它之后就不再出现了，但是没删除的还在，并且一次只能删一种。

 $ S $ 的长度就是每个字符的 $\frac{\text{出现次数}}{\text{删除顺序}}$ 之和，如果不能整除显然无解。

由1可以一眼看出 $ S $ 就在 $ T $ 的最前面。

容易构造出上面符合要求但无解的情况（样例中即存在），所以要再模拟一遍。

接着只要模拟一遍即可。

------------

程序每组复杂度 $ O(|T|) $ 。

需要对出现字符最后位置的排序，但字符范围只有 $ 26 $ ，可以忽略不计。

据说直接写 ` string ` 也能过。

------------

代码如下 （~~非常的短~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
struct stringplas{//没有必要的手写字符串
    int sz;
    int a[505050];
    inline int size(){return sz;}
    inline void print(){for(register int i=0;i<sz;++i)putchar(a[i]);}
    inline void read(){sz=0;char ch=getchar();while(ch==' ' || ch=='\n')ch=getchar();while(ch!=' ' && ch!='\n')a[sz++]=ch,ch=getchar();}
    inline void operator = (register const string& b){sz=b.size();for(register int i=0;i<sz;++i)a[i]=b[i];}
    inline void operator = (register const stringplas& b){sz=b.sz;for(register int i=0;i<sz;++i)a[i]=b.a[i];}
    inline bool operator == (register const stringplas& b){if(sz!=b.sz)return 0;for(register int i=0;i<sz;++i)if(a[i]!=b.a[i])return 0;return 1;}
    inline bool operator != (register const stringplas& b){if(sz!=b.sz)return 1;for(register int i=0;i<sz;++i)if(a[i]!=b.a[i])return 1;return 0;}
    inline void operator += (register const char& b){a[sz++]=b;}
    inline void operator += (register const stringplas& b){for(register int i=0;i<b.sz;++i){a[sz++]=b.a[i];}}
};
stringplas st,ans,S,T;
int a[30],b[30],p[30];
inline bool cmp(int x,int y){return b[x]<b[y];}
inline void slove(){
    for(register int i=0;i<26;++i){
        a[i]=0;
        b[i]=505050;
        p[i+1]=i;
    }
    st.read();
    n=st.size();
    m=0;
    for(register int i=0;i<n;++i){//记录每个字符出现的次数，最后出现的位置
        if(!a[st.a[i]-'a'])++m;
        ++a[st.a[i]-'a'];
        b[st.a[i]-'a']=i;
    }
	//p表示排名为pi的字符是什么
    sort(p+1,p+27,cmp);
    l=0;
    for(register int i=1;i<=m;++i){
        if(a[p[i]]%i){
            printf("-1\n");
            return;
        }
        l+=a[p[i]]/=i;//用l统计S的长度
    }
	//构造出S
    for(register int i=0;i<l;++i)--a[st.a[i]-'a'];
    for(register int i=0;i<26;++i)if(a[i]!=0){
            printf("-1\n");
            return;
    }
    S="";
    T="";
    for(register int i=0;i<l;++i)S+=st.a[i];
    ans=S;
	//如题模拟
    for(register int i=1;i<=m;++i){
        if(T.size()+S.size()>st.size()){
            printf("-1\n");
            return;
        }
        T+=S;
        s=S.size();
        S="";
        for(register int j=0;j<s;++j)if(S.a[j]!=p[i]+'a')S+=S.a[j];
    }
    if(T!=st){
        printf("-1\n");
        return;
    }
	//输出答案
    ans.print();
    putchar(' ');
    for(register int i=1;i<=m;++i)putchar(p[i]+'a');
    putchar('\n');
}
int main(){
    int t;
    cin>>t;
    while(t--)slove();
    return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：0)

## 思路

有一个显然的结论，从字符串末尾往前看，**越早出现的字母越晚被删除**。所以删除字母的顺序是可以求出来的。我们就得到了第二个问题的答案。

我们考虑用第二问的答案来推出原串。设第 $ i $ 个 字符第 $ q $ 个被删除，在原串（ $ s $ ）中出现了 $ cnt_i $ 次，在处理过后的串（ $ t $ ）中出现  $ tot_i $ 次，那么显然 $ q \times cnt_i = tot_i $ 。现在我们已经求出了 $ q $ 和 $ tot_i $ ，那么 $ cnt_i $ 就可以求出来了，我们可以 $ O(n) $ 遍历原串，看什么时候对于每个 $ i $ 都满足  $ q \times cnt_i = tot_i $ ，这样我们就找到了第一问的解。

但这个时候，我们发现这个程序过不了样例  ` qweqeewew ` 。手推一下发现，我们输出的与原串不符。所以在最后，还要在模拟一遍变化的过程，判断是否与原串相同，这题就能轻松水过。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=130;
int T,n,cnt[maxn],now[maxn],tot;//将数组开大一点，处理的时候就可以直接存字符，不用做ch-'a'+1之类的操作
bool g[maxn],flag;
vector<char> ans;//用来存删除顺序
map<char,int> mp;//用来存字符是第几个删除的
string s,ch;
inline int read(){
    int s=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return s;
}
inline int llread(){
    ll s=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return s;
}
inline void init(){//初始化
	n=ch.size(),s="",tot=flag=0,mp.clear(),ch=" "+ch,ans.clear();
	for(register int i='a';i<='z';++i) cnt[i]=g[i]=now[i]=0;
}
int main(){
	T=read();
	while(T--){
		cin>>ch;
		init();
		for(register int i=n;i>=1;--i){//从后往前找删除顺序
			if(!g[ch[i]]) ans.push_back(ch[i]);
			g[ch[i]]=1,cnt[ch[i]]++;
		}
		reverse(ans.begin(),ans.end());//因为它是倒序的，所以要reverse倒转
		for(register int i=0;i<ans.size();++i){//判断是否可以分
			mp[ans[i]]=i+1;
			if(now[ans[i]]%(i+1)){
				cout<<"-1\n";
				flag=1;
				break;
			}
		}
		if(flag) continue;
		for(register int i=1;i<=n;++i){//找原串
			now[ch[i]]++;
			s+=ch[i];
			if(now[ch[i]]*mp[ch[i]]==cnt[ch[i]]) tot++;
			if(tot==ans.size()) break;
		}
		string p=s,last=s;
		for(register int i=0;i<ans.size();++i){//模拟操作
			string l="";
			for(register int j=0;j<last.size();++j) if(ans[i]!=last[j]) l+=last[j];
			p+=l,last=l;
		}
		p=" "+p;
		if(p==ch){
			cout<<s<<" ";
			for(register int i=0;i<ans.size();++i) cout<<ans[i];
			putchar('\n');
		}else cout<<"-1\n";
	}
	return 0;
}
```


---

