# Obtain The String

## 题目描述

You are given two strings $ s $ and $ t $ consisting of lowercase Latin letters. Also you have a string $ z $ which is initially empty. You want string $ z $ to be equal to string $ t $ . You can perform the following operation to achieve this: append any subsequence of $ s $ at the end of string $ z $ . A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements. For example, if $ z = ac $ , $ s = abcde $ , you may turn $ z $ into following strings in one operation:

1. $ z = acace $ (if we choose subsequence $ ace $ );
2. $ z = acbcd $ (if we choose subsequence $ bcd $ );
3. $ z = acbce $ (if we choose subsequence $ bce $ ).

Note that after this operation string $ s $ doesn't change.

Calculate the minimum number of such operations to turn string $ z $ into string $ t $ .

## 样例 #1

### 输入

```
3
aabce
ace
abacaba
aax
ty
yyt```

### 输出

```
1
-1
3```

# 题解

## 作者：xiaomuyun (赞：6)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1295C)
- [Codeforces 题目传送门](https://codeforces.com/problemset/problem/1295/C)

## 思路分析

注意判断无解。容易发现，无解的情况只有 $t$ 中有 $s$ 中没有的字符，这很好办。

因为要让操作次数尽可能少，所以每次操作要尽可能选多个字符。比如字符串 $s=\texttt{abdcd}$，$t=\texttt{abdc}$ 时，如果我们在 $s$ 里选了第 $1$、$2$ 和 $5$ 个字符，得到了 $\texttt{abd}$，但是选第 $1$、$2$、$3$ 和 $4$ 个字符的话，可以得到 $\texttt{abdc}$，通过这个例子不难想到，每次选字符要选尽可能靠前的。

那么就做完了。遍历一遍 $t$，如果 $t$ 中的下一个字符在 $s$ 中剩下的位置出现了，那就选尽量靠前的，否则就开始下一次操作，从 $s$ 的头开始。

## 代码实现

我用了 `vector` 来存每个字符的位置，这样可以通过二分来查找是否还能选字符。

注意对于每组数据要初始化。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
using namespace std;
int _,cnt=0;
bool vis[300];
string s,t;
vector<int> v[300];
int main(){
	scanf("%d",&_);
	while(_--){
		memset(vis,false,sizeof vis);
		for(char i='a';i<='z';++i) v[i].clear();
		cnt=1;//初始化，注意cnt初始为1
		cin>>s>>t;
		int n=s.length(),m=t.length();
		s="+"+s,t="+"+t;//小癖好可以不管，只是为了让下标从1开始
		for(int i=1;i<=n;++i){
			vis[s[i]]=true;
			v[s[i]].push_back(i);//存位置
		}
		bool flag=false;
		for(int i=1;i<=m;++i){//判断无解
			if(!vis[t[i]]){
				flag=true;
				break;
			}
		}
		if(flag){
			printf("-1\n");
			continue;
		}
		int lst=0;
		for(int i=1;i<=m;++i){//二分找位置
			int it=upper_bound(v[t[i]].begin(),v[t[i]].end(),lst)-v[t[i]].begin();
			if(it>=v[t[i]].size()) lst=v[t[i]][0],++cnt;//如果找不到了就从头再来
			else lst=v[t[i]][it];//找得到就继续
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：yeaDonaby (赞：5)

### 题目大意
输入只包含小写字母的字符串$s,t$，一开始$z$是个空字符串，每次可以将$s$的一个子序列添加到$z$末尾得到新的$z$，计算最少多少次操作可以让$z=t$。

### 算法
考虑将$t$拆成若干段，每段都是$s$的子序列，显然可以贪心。
假设已经解决了$t_{1}$~$t_{i-1}$，且$t_{i-1}$对应的$s_{j}$，现在给$t_i$在$s$中找个字符与之对应：
> 1. 如果$t_i$从未出现过则无解；
> 2. 如果$s_{j}$后面能找到$t_i$，则找第一个；
> 3. 否则在整个$s$中找到第一个$t_i$，且答案增加 。

#### 那么，问题变成，怎么找$s_{j}$后面首个与$t_i$相同的字符的位置。

  方法很多，我开了$26$个$vector$；
把同一个字母在$s$中每次出现的数组下标扔进一个$vector$，每次$upper\_bound$。
时间复杂度$O(|t|log^{|s|})$。
```
#include<stdio.h>
#include<bits/stdc++.h>
#define R register
using namespace std;
int T,tot;
char ch;
string t;
vector<int > k[26];
inline void reads(string &t)
{
	ch=getchar();
	while(ch<'a'||ch>'z')
	{
		ch=getchar();
	}
	while(ch>='a'&&ch<='z')
	{
		t+=ch;
		ch=getchar();
	}
	return ;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		tot=0;
		ch=getchar();
		while(ch<'a'||ch>'z')
		{
			ch=getchar();
		}
		while(ch>='a'&&ch<='z')
		{
			k[ch-'a'].push_back(tot);
			ch=getchar();
			tot++;
		}
		reads(t);
		int F=1,pop=-1,ans=1;
		for(R int i=0; i<t.length(); i++)
		{
			int v=t[i]-'a';
//			printf("%d\n",v);
			if(k[v].empty())
			{
//				printf("%d ",i);
				printf("-1\n");
				F=0;
				break;
			}
			if(k[v].back()<=pop)
			{
				ans++;
				pop=k[v].front();
//				printf("add:%d %d\n",i,pop);
			}
			else
			{
				pop=k[v][upper_bound(k[v].begin(),k[v].end(),pop)-k[v].begin()];
//				printf("then:%d %d\n",i,pop);
			}
		}
		if(F)
		{
			printf("%d\n",ans);
		}
		for(R int i=0; i<=25; i++)
		{
			k[i].clear();
		}
		t.clear();
	}
	return 0;
}
```

---

## 作者：ix35 (赞：3)

这基本是一道子序列自动机的模板题。

在一般的子序列自动机的转移 $nx[i][j]$ 建完以后，因为 $t$ 不一定是 $s$ 的子序列，所以如果走不下去就要从头再走，所以我们还需要建 "fail" 指针，令 $first(j)$ 表示 $s$ 中第一个 $j$ 出现的位置，那么如果某一个 $nx[i][j]=0$，则直接令 $nx[i][j]=first(j)$。

然后在子序列自动机上跑一遍 $t$ 就可以了，如果跑到了一个靠前的位置，就说明重新选了一次，记录一下即可

如果某个 $t$ 中的字符在自动机上没有转移，那么答案显然是 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int tc,n,m,fir[27],nx[MAXN][27];
char s[MAXN],t[MAXN];
int main () {
	scanf("%d",&tc);
	for (int ii=1;ii<=tc;ii++) {
		memset(nx,0,sizeof(nx));
		memset(fir,0x3f,sizeof(fir)); 
		scanf("%s%s",s+1,t+1);
		int n=strlen(s+1),m=strlen(t+1);
		for (int i=1;i<=n;i++) {fir[s[i]-'a']=min(fir[s[i]-'a'],i);}
		for (int i=n;i>=0;i--) {
			if (i<n) {nx[i][s[i+1]-'a']=i+1;}
			for (int j=0;j<26;j++) {
				if (!nx[i+1][j]&&!nx[i][j]) {nx[i][j]=fir[j];}
				else if (!nx[i][j]) {nx[i][j]=nx[i+1][j];}
			}
		}
		int flg=0,ans=0,cur=0;
		for (int i=1;i<=m;i++) {
			if (nx[cur][t[i]-'a']==0x3f3f3f3f) {printf("-1\n");flg=1;break;}
			else {
				if (nx[cur][t[i]-'a']<=cur) {ans++;}
				cur=nx[cur][t[i]-'a'];
			}
		}
		if (flg) {continue;}
		printf("%d\n",ans+1);
	}
	return 0;
}
```


---

## 作者：Deft_t (赞：2)

首先注意到每次操作加上的是一个子序列而不是子串。  
每个字符的选择，可以考虑贪心地选取尽可能靠前的，为之后的字符预留尽可能多的空间。  
对于不可能的情况只需要判断 $t$ 中是否未出现过 $s[i]$ 即可。  
对于其他情况。使用 $lst$ 记录上一步选择的 $s[i-1]$ 在字符串 $t$ 的下标。就相当于每次去 $t$ 中寻找 $s[i]$ 出现的位置 $pos$ ，并且要在 $lst$ 之后。此时需要考虑 $pos$ 是否存在:  
   - 如果存在，则 $ans$ 不变，更新 $lst$ 。  
   - 如果不存在，则 $ans$ 加 $1$ ，贪心的选择出现位置最靠前的。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
vector<int> v[260];
string s,t; 
int main(){
	cin>>T;
	while(T--){
		cin>>s>>t;
		for(char i = 'a';i <= 'z';i++) v[i].clear();
		for(int i = 0;i < s.length();i++) v[s[i]].push_back(i);
		bool ok = true;
		int lst = -1,ans = 1; //lst记录上一步选择的s[i-1]在字符串t的下标 
		for(int i = 0;i < t.length();i++){
			if(v[t[i]].size()==0){   //t中不存在s[i]，则不可能生成s 
				ok = false;
				break;
			}
			int pos = upper_bound(v[t[i]].begin(),v[t[i]].end(),lst)-v[t[i]].begin();
			if(pos < v[t[i]].size()){  //pos存在，ans不变，更新lst 
				lst = v[t[i]][pos];
			}
			else{
				lst = v[t[i]][0]; //不存在则选择尽可能前面的 
				ans++;
			}
		}
		if(ok) cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}



```


---

## 作者：YLWang (赞：1)

一眼题

思考字符串问题时，我们可以考虑转化思路，不基于哪个位置上是哪个数，而基于哪个数在哪些位置上出现

显然这就是一个基于字符集操作的题。

我们考虑维护出每个字符出现在了哪些位置。每次记录上次的位置然后在当前数组里二分就可以了。

十分的套路。

```cpp
const int MAXT = 205;
vector < int > pos[MAXT];
int n, m;
signed main()
{
	IOS;
	int T; cin >> T;
	while(T--) {
		string s, t; cin >> s >> t;
		n = s.size(), m = t.size();
		s = ' ' + s, t = ' ' + t;
		For(i, 1, 200) pos[i].clear();
		For(i, 1, n)
			pos[s[i]].pb(i);
		int ans = 0, lst = 0;
		For(i, 1, m) {
			if(!pos[t[i]].size()) { cout << "-1" << endl; goto end;}
			if(pos[t[i]][pos[t[i]].size()-1] <= lst) lst = 0; 
			if(lst == 0) ans++;
			int l = 0, r = pos[t[i]].size()-1, tt = 0;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(pos[t[i]][mid] > lst) 
					tt = pos[t[i]][mid], r = mid-1;
				else l = mid + 1;
			}
			lst = tt;
		}
		cout << ans << endl;
		end:;
	} 
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

看到这道题，第一思路就是去暴力地做，对于每个 $b_i$ 找一下对应匹配的 $a_i$。但是，由于 $a_i$ 可能会被取很多次，这个复杂度就不是像双指针一样的 $O(n+m)$ 的了。那么我们考虑对查找操作进行优化。

每次的查找，假设上一次取的是 $a_i$，那么就相当于 $k$ 从 $i+1$ 到 $n$ 找到第一个和 $b_j$ 相等的 $a_k$。这样看起来难以优化，但是我们注意到一点：字符只有 26 个。

因此，我们可以对每一个字符开一个 vector，记录所有字符在 $a$ 中出现的位置。而我们在顺序遍历的过程中，vector 中存储的元素一定是有序的。而每次的查找很简单，直接在当前字符的 vector 上二分，找到第一个大于 $i$ 的位置即可，也就是 ```upper_bound()``` 函数的功能。如果找到了，就记录当前取得位置，方便下次继续向后找；如果找不到，那么就从头开始找，次数加一。

最后，特判一下找不到的情况，即从头开始找时，```upper_bound()``` 依然找不到，说明这个元素 $a$ 数组中根本没有，直接退出循环即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> p[30];
char a[100005],b[100005];
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",a+1,b+1);
		int n=strlen(a+1),m=strlen(b+1);
		for(int i=1;i<=n;i++) p[a[i]-96].push_back(i);
		int cur=0,cnt=1;
		bool flag=1;
		for(int i=1;i<=m;i++)
		{
			int m=upper_bound(p[b[i]-96].begin(),p[b[i]-96].end(),cur)-p[b[i]-96].begin();
			if(m==p[b[i]-96].size())
			{
				cur=0; cnt++;
				m=upper_bound(p[b[i]-96].begin(),p[b[i]-96].end(),cur)-p[b[i]-96].begin();
				if(m==p[b[i]-96].size())
				{
					flag=0;
					break;
				}
				cur=p[b[i]-96][m];
			}
			else cur=p[b[i]-96][m];
		}
		if(!flag) printf("%d\n",-1);
		else printf("%d\n",cnt);
		for(int i=1;i<=26;i++) p[i].clear();
	}
	return 0;
}
```

---

