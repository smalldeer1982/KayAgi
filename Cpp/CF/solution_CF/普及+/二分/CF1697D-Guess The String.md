# Guess The String

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury has chosen a string $ s $ consisting of $ n $ characters; each character of $ s $ is a lowercase Latin letter. Your task is to guess this string; initially, you know only its length.

You may ask queries of two types:

- $ 1 $ $ i $ — the query of the first type, where $ i $ is an integer from $ 1 $ to $ n $ . In response to this query, the jury will tell you the character $ s_i $ ;
- $ 2 $ $ l $ $ r $ — the query of the second type, where $ l $ and $ r $ are integers such that $ 1 \le l \le r \le n $ . In response to this query, the jury will tell you the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type. Your task is to restore the string $ s $ .

For each test in this problem, the string $ s $ is fixed beforehand, and will be the same for every submission.

## 说明/提示

Let's analyze the example of interaction.

The string chosen by the jury is guess, so initially the jury sends one integer $ 5 $ .

1. the first query is ? 2 1 5, which means "count the number of different characters among $ s_1, s_2, \dots, s_5 $ ". The answer to it is $ 4 $ .
2. the second query is ? 1 2, which means "tell which character is $ s_2 $ ". The answer to it is u.
3. the third query is ? 2 1 2, which means "count the number of different characters among $ s_1 $ and $ s_2 $ ". The answer to it is $ 2 $ .
4. the fourth query is ? 1 1, which means "tell which character is $ s_1 $ ". The answer to it is g.
5. the fifth query is ? 1 3, which means "tell which character is $ s_3 $ ". The answer to it is e.
6. the sixth query is ? 1 4, which means "tell which character is $ s_4 $ ". The answer to it is s.
7. the seventh query is ? 2 4 5, which means "count the number of different characters among $ s_4 $ and $ s_5 $ ". The answer to it is $ 1 $ , so it's possible to deduce that $ s_4 $ is the same as $ s_5 $ .

In the end, the answer is submitted as ! guess, and it is deduced correctly.

## 样例 #1

### 输入

```
5
4
u
2
g
e
s
1```

### 输出

```
? 2 1 5
? 1 2
? 2 1 2
? 1 1
? 1 3
? 1 4
? 2 4 5
! guess```

# 题解

## 作者：TH讠NK (赞：4)

**分析**：第二类查询只让用 $6000$ 次，$n$ 最大为 $1000$，显然 $n\log n$ 的时间复杂度是不行的，所以正确的时间复杂度应该是 $n \log(26)$，恰好和题目要求对应。

**预处理部分**：找到每个字母第一次出现的位置，以及每个字母分别是什么，方便之后确定每个位置是哪个。

**核心处理**：找出每个位置对应的字母。

我们要记录下每个字母最后出现的位置，这样我们才可以从左往右一次扫过去。

维护一个二元的数组 $a[]$，使其按 $pos$ 位置从小到大排序，满足单调性，这样就可以进行二分。

每次到一个新的位置 $i$，令 $l=1$，$r=mx$ 开始二分，每次查询 $(a[mid].pos,i)$

为方便说明我们记 $siz$ 为 $a[mid].pos$ 到 $i-1$ 包含的字母数（事实上 $a[mx].pos=i-1$）。

若查询结果为 $siz+1$，则第 $i$ 位字母不在 $mid \sim r$ 中，令 $r=mid-1$

若查询结果为 $siz$，则第 $i$ 位字母在 $mid \sim r$ 中，令 $l=mid$

别忘了此时 $mid=(l+r+1)/2$，不然可能会卡成死循环。

细节见代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
const int maxn=1005;
int n,l,r,mid,id[maxn],mx=0,t,pre[27],tot=0;
char mp[27],c,q[5];
il int read(){
	int x=0; char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') x=x*10+c-48, c=getchar();
	return x;
}
il char ask1(int x){
	printf("? 1 %d\n",x);
	cout<<flush;//交互题输出之后记得flush
	cin>>q;
	return q[0];
}
il int ask2(int x,int y){
	printf("? 2 %d %d\n",x,y);
	cout<<flush;
	x=read();
	return x;
}
struct node{
	int x,pos;//x表示是第几类字母，pos表示位置
	bool operator < (const node a)const{
		return pos<a.pos;
	}
} a[27];//这个数组将会被维护成pos从小到大的样子
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){//预处理部分
		t=ask2(1,i);
		if(t>mx){
			id[i]=mx=t;//id[i]表示第i个位置是第几类字母
			mp[id[i]]=ask1(i);//mp[i]表示第i类字母是什么
		}
	}
	mx=0;
	for(int i=1;i<=n;i++){
		if(!id[i]){
			l=1, r=mx;
			while(l<r){
				mid=l+r+1>>1;
				t=ask2(a[mid].pos,i);
				if(t==mx-mid+1) l=mid;
				else r=mid-1;
			}
			id[i]=a[l].x;//二分最终结果，确定了第i位
			for(int j=l;j<mx;j++) a[j]=a[j+1];//要更新这个字母最后出现的位置
		}
		else mx++;
		a[mx]=(node) {id[i],i};//显然它要排在最后一位，这样就保证了单调性
	}
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<mp[id[i]];
	cout<<endl;
	return 0;
}
```


---

## 作者：PosVII (赞：3)

**前言**

------------

超一眼的交互题！因为交互题不熟练没有刷新 TLE 了好几次。如果各位知道 printf 操作怎么刷新的话私信告诉我一声，谢谢了。

**思路**

------------

设一操作返回值为 $f1(i)$，二操作返回值为 $f2(l,r)$

看到操作一的 $26$ 次，显然是每次操作找一个不同的小写字母。

怎么保证每次找到的字母都不一样呢，我们有以下的思路：

对于目前询问第 $j$ 个字符是否没出现过。我们先查询 $f2(1,j)$，如果它不同与 $f2(1,j-1)$，就说明它没出现过。

这么找到了不同的 $26$ 个字符，接下来就利用它们进行判断。对于目前询问第 $j$ 个字符是什么，我们就从左到右一个一个删不同的字符，看什么时候 $f2$ 的值不变，说明第 $j$ 个字符就是被删去的那个字符，一个一个判断即可。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=1e3+5;
struct node{
	char c;
	int idx;
}str[30];
int idx[30];
string s;
int n,res,j=1;
int ask(int l,int r) {
	cout<<"? 2 "<<l<<" "<<r<<endl;
	read(res);
	return res;
}
signed main() {
	read(n);
	for(int i=1;i<=26&&j<=n;++i) {
		cout<<"? 1 "<<j<<endl;
		cin>>str[i].c,s+=str[i].c;
		str[i].idx=j,idx[str[i].c-'a']=i;
		++j;
		while(j<=n&&ask(1,j)==i) {
			int l=1,r=i,ans;char c;
			while(l<=r) {
				int mid=(l+r)>>1;
				if(ask(str[mid].idx,j)==i-mid+1) l=mid+1,c=str[mid].c;
				else r=mid-1;
			}
			s+=c;
			for(int k=idx[c-'a'];k<i;++k) {
				swap(str[k],str[k+1]);	
				idx[str[k].c-'a']=k,idx[str[k+1].c-'a']=k+1;
			}
			str[i].idx=j;
			++j;
		}
	}
	while(j<=n) {
		int l=1,r=26;char c;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(ask(str[mid].idx,j)==27-mid) l=mid+1,c=str[mid].c;
			else r=mid-1;
		}
		s+=c;
		for(int k=idx[c-'a'];k<26;++k) {
			swap(str[k],str[k+1]);	
			idx[str[k].c-'a']=k,idx[str[k+1].c-'a']=k+1;
		}
		str[26].idx=j;
		++j;
	}
	cout<<"! "<<s<<endl;
	return 0;
}
```

---

## 作者：lin_er (赞：1)

作为本蒟蒻第一次顺利独立做出的交互题，它值得一篇题解  
## 分析
做交互题，首先看交互方式及其交互次数要求，发现此题中第一种询问最多可用 $26$ 次，正好等于最大字符集个数，而另一种询问最多询问 $6\times10^3$ 次，发挥注意力可知这大概是 $n\log26$ 左右，所以此题的思路基本清晰：利用第一种询问得出目标字符串的种类及其个数，再利用得出的已知字符以及第二种询问得出其余字符是什么。
## 解题思路  
此题的重难点在于如何在 $\log26$ 第二种询问中得出某一位置的字符种类，通过 $\log26$ 的询问限制我们可能想到通过二分字符集来确定种类，但如何实现呢？这里直接给出一种解决方法：**维护出现过的每种字符最后出现的位置（单调递增）以助二分**，下面我们来具体讲讲原理及其实现方式。  
考虑下面的字符串  

```cpp
abbcdec//末尾c为本次目标字符
```
显然我们维护的位置为（下标从1开始） `1,3,4,5,6`。我们考虑对每一个位置到目标位置进行第二种询问，输出应为 `5,4,3,3,2`。我们容易注意到在与目标字符相同的字符的位置及其之前的位置中的询问结果都总等于 **总字符集个数-这一位置之前的字符种类个数**，而在此之后，询问结果变为原先结果加一，相信聪明的你一定已经明白其中缘由，至此你也应当明白之所以维护每种字符最后出现的位置，是为了保证在其之后的已知字符中，没有与它相同的，以此保证二分的正确性。至此主要问题已然解决。  
## 一些细节  
为保证每次利用上述方式的求解都是已经出现过的字符，我们可以 $O(n)$ 预处理每一字符第一次出现的位置，顺便处理出字符集是什么（具体实现可以看代码）。  
关于维护出现过的每种字符最后出现的位置的单调性，我们可以每次二分出结果后顺便修改其出现位置，再暴力重排~~谁会在交互题里卡时间啊~~。  
## AC代码 
#### （码风警告） 

```cpp
#include"bits/stdc++.h"
using namespace std;
int n,ret;
struct zz{
	int id,w;
};
char c[30];
int sum,ww[30];
char s[1010];
bool cmp(zz x,zz y){
	return x.w<y.w;
}
vector<zz> v;
void che(int x){//二分得出答案
	int l=0,r=v.size()-1;
	while(l<r){
		int mid=(l+r+1)>>1;
		cout<<"? 2 "<<v[mid].w<<' '<<x<<endl;
		cin>>ret;
		if(ret==(int)v.size()-mid) l=mid;
		else r=mid-1;
	}
	s[x]=s[v[l].w];//修改后暴力重排
	v[l].w=x;
	sort(v.begin(),v.end(),cmp);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//预处理
		cout<<"? 2 1 "<<i<<endl;
		cin>>ret;
		if(ret>sum){
			sum++;
			cout<<"? 1 "<<i<<endl;
			cin>>c[sum];
			s[i]=c[sum];
			ww[sum]=i;
		}
	}
	int now=1;
	ww[sum+1]=n+1;//是防止笔者写法出错的步骤
	for(int i=1;i<=n;i++){
		if(i<ww[now]){
			che(i);
		}
		else{
			v.push_back({now,i});
			now++;
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++){
		cout<<s[i];
	}
	cout<<endl;//每次输出后记得清空缓冲区！！
}
```

---

## 作者：Cocoly1990 (赞：1)

显然操作一是建立在字符集上的询问。

一种简单的想法是对于每个字符询问出他左边第一个和他一样的字符，这种做法是 $n\log n$ 的。二分过程是平凡的，只需要记录一下之前的字符的前缀和即可。

进一步，很多询问是无效的，容易发现我们真正关心的位置是每个字符的最后一次出现的位置，因此在字符集上二分就好，$n\log 26$.

---

## 作者：Sellaris (赞：1)

- 比较水的交互，赛时爆切。

- 注意到询问的次数，仅有 $26$ 次询问具体字母，显然对应英文的 $26$ 个字母，于是考虑如何用另一个询问区间字母种类数来维护这 $26$ 个字母。
- 注意到长度是 $1000 $ ，观察不难发现我们可以从头开始可以维护每个字母最后出现的位置。同时每次询问区间种类以位置坐标来二分，遇到种类数和这个位置往后的已知种类数不同的时候就问这是什么字母，而正好区间种类询问次数是不超过 $O(nlog26)$ 的。

```cpp

int ask1(int u){
	cout<<"? "<<1<<" "<<u<<endl;
	fflush(stdout);
	cin>>c;
	return (int)(c-'a');
}
int ask2(int l,int r){
	cout<<"? "<<2<<" "<<l<<" "<<r<<endl;
	fflush(stdout);
	cin>>tmp;return tmp;
}
const int N=1050;
int n,tong[26],a[N];
struct node{
	int id,pos;
}st[50];
int top;
int cmp(node x,node y){
	return x.pos<y.pos;
}
signed main(){
//	freopen("data.in","r",stdin);
	n=read();
	a[1]=ask1(1);
	tong[a[1]]=1;
	for(int i=2;i<=n;i++){
		top=0;
		for(int k=0;k<26;k++){
			if(tong[k])st[++top]={k,tong[k]};
		}
		sort(st+1,st+top+1,cmp);
		int l=1,r=top,jl=-1;
		#define mid ((l+r)>>1)
		while(l<=r){
			if(ask2(st[mid].pos,i)!=(top-mid+1)+1)jl=mid,l=mid+1;
			else r=mid-1;
		}
		if(jl==-1){
			a[i]=ask1(i);
			tong[a[i]]=i;
		}
		else{
			a[i]=st[jl].id;
			tong[a[i]]=i;
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++){
		cout<<(char)(a[i]+'a');
	}
    return 0;
}
```



---

## 作者：ax_by_c (赞：0)

设 $c(l,r)$ 为 $S_{l,\dots,r}$ 中不同字符的种数。

看到操作一只能进行 $26$ 次，合理猜测是每个字母用一次。

于是考虑从前往后一个个确定字母，首先先询问第一个字母，而对于之后的字母，需要先判断之前是否存在相同的字母，没有时才能直接询问。

对于一个位置 $i$，若位置 $j<i,S_j=S_i,\forall k\in (j,i),S_k\neq S_i$，容易发现 $\forall k\in[1,j],c(k,i)=c(k,i-1),\forall k\in(j,i),c(k,i)+1=c(k,i-1)$，可以二分，于是我们得到了一个二操作数不超过 $n\log n$ 的做法，考虑优化。

发现只有之前的每种字母最后一次出现的位置会对 $c$ 产生贡献，所以只需要关注这些位置。那么二操作数不超过 $n\log 26$，可以通过。

---

