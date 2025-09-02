# [ABC323C] World Tour Finals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc323/tasks/abc323_c

$ N $ 人のプレイヤーが参加するプログラミングコンテスト World Tour Finals が行われており、競技時間の半分が過ぎました。 このコンテストでは $ M $ 問の問題が出題されており、問題 $ i $ の点数 $ A_i $ は $ 500 $ 以上 $ 2500 $ 以下の $ 100 $ の倍数です。

各 $ i\ =\ 1,\ \ldots,\ N $ について、プレイヤー $ i $ がどの問題を既に解いたかを表す文字列 $ S_i $ が与えられます。 $ S_i $ は `o`, `x` からなる長さ $ M $ の文字列で、$ S_i $ の $ j $ 文字目が `o` のときプレイヤー $ i $ は問題 $ j $ を既に解いており、`x` のときまだ解いていません。 ただし、どのプレイヤーもまだ全ての問題を解いてはいません。

プレイヤー $ i $ の総合得点は、解いた問題の点数の合計に、**ボーナス点** $ i $ 点を加えた点数として計算されます。  
さて、各 $ i\ =\ 1,\ \ldots,\ N $ について以下の質問に答えてください。

- プレイヤー $ i $ がまだ解いていない問題を少なくとも何問解くことで、プレイヤー $ i $ の総合得点が他のプレイヤー全員の現在の総合得点を上回ることができますか？

なお、問題文中の条件と制約から、プレイヤー $ i $ が全ての問題を解くことで、他のプレイヤー全員の現在の総合得点を上回ることができることが証明できます。 このことから、答えは常に定義されることに注意してください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 100 $
- $ 1\leq\ M\leq\ 100 $
- $ 500\leq\ A_i\leq\ 2500 $
- $ A_i $ は $ 100 $ の倍数
- $ S_i $ は `o`, `x` からなる長さ $ M $ の文字列
- $ S_i $ には `x` が一個以上含まれる
- 入力される数値は全て整数

### Sample Explanation 1

競技時間の半分の経過時の各プレイヤーの総合得点は、プレイヤー $ 1 $ が $ 2001 $ 点、プレイヤー $ 2 $ が $ 1502 $ 点、プレイヤー $ 3 $ が $ 1703 $ 点です。 プレイヤー $ 1 $ は $ 1 $ 問も解かずとも、他のプレイヤー全員の総合得点を上回っています。 プレイヤー $ 2 $ は、例えば問題 $ 4 $ を解けば総合得点が $ 3502 $ 点となり、他のプレイヤー全員の総合得点を上回ります。 プレイヤー $ 3 $ も、例えば問題 $ 4 $ を解けば総合得点が $ 3703 $ 点となり、他のプレイヤー全員の総合得点を上回ります。

## 样例 #1

### 输入

```
3 4
1000 500 700 2000
xxxo
ooxx
oxox```

### 输出

```
0
1
1```

## 样例 #2

### 输入

```
5 5
1000 1500 2000 2000 2500
xxxxx
oxxxx
xxxxx
oxxxx
oxxxx```

### 输出

```
1
1
1
1
0```

## 样例 #3

### 输入

```
7 8
500 500 500 500 500 500 500 500
xxxxxxxx
oxxxxxxx
ooxxxxxx
oooxxxxx
ooooxxxx
oooooxxx
ooooooxx```

### 输出

```
7
6
5
4
3
2
0```

# 题解

## 作者：A_R_O_N_A (赞：4)

## 题意

有 $n$ 个选手和 $m$ 道题，每题有不同的分值，现给出各题目分值和各选手每题的通过情况，求每一位选手要超过目前的最高分选手至少还需要通过几道题。数据保证没有人全部通过。**每个人有基础分，为自己的编号**。

## 思路分析

简简单单贪心，把题目分数排一遍序然后依次选取，如果已经做过就跳过该题，直至超过目前最高分。然后输出答案即可。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*w;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	static int sta[35];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top)putchar(sta[--top]+'0');
}//快读快写不解释
struct node{
	int sum,num,ans;//选手分数，编号，需要通过的题目数
	string s;
};
struct problem{
	int point;//分值
	map<int,bool>mp; //储存选手是否已经通过此题
}pro[105];
node a[105];
int n,m;
bool cmp1(node x,node y){
	return x.sum>y.sum;;
}//排序找出最高分
bool cmp2(problem x,problem y){
	return x.point>y.point;
}//排序题目分值
bool cmp3(node x,node y){
	return x.num<y.num;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		pro[i].point=read();
	}//输入
	for(int i=1;i<=n;i++){
		cin>>a[i].s;
		a[i].num=i;
		a[i].sum=i;//初始分
		for(int j=0;j<a[i].s.size();j++){
			if(a[i].s[j]=='o'){
				a[i].sum+=pro[j+1].point;
				pro[j+1].mp[a[i].num]=true;
			}//累加分数，标记已经通过此题
		}
	}
	sort(a+1,a+1+n,cmp1);//对选手排序
	sort(pro+1,pro+1+m,cmp2);//对题目排序
	for(int i=2;i<=n;i++){//第一个已经是最高分所以从第二个开始
		int anss=0;//储存需要通过的题目数
		for(int j=1;j<=m;j++){//选取题目
			if(a[i].sum>=a[1].sum)break;//如果超过，退出
			if(pro[j].mp[a[i].num]==false){//如果没有做过此题，选取
				a[i].sum+=pro[j].point;
				anss++;//累加题目数
			}
		}
		a[i].ans=anss;//将通过题目数转移到选手结构体里面
	}
	sort(a+1,a+1+n,cmp3);//因为刚刚我们按分数排了一遍序，现在的顺序是乱的，所以按照编号排回去
	for(int i=1;i<=n;i++){
		write(a[i].ans);puts("");//输出答案
	}
	return 0;
}
```

但是我们发现，这个代码还是过于复杂，对选手排序只是为了找出最大值，而且排了两遍序，如果 $n$ 再大一些可能会超时，我们可以优化此代码，去掉排序选手的步骤。

##  Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x=0,w=1;
    char ch=0;
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+(ch-'0');
        ch=getchar();
    }
    return x*w;
}
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    static int sta[35];
    int top=0;
    do{
        sta[top++]=x%10,x/=10;
    }while(x);
    while(top)putchar(sta[--top]+'0');
}//快读快写不解释
struct node{
    int sum,num;//选手分数，编号
    string s;
};
struct problem{
    int point;//分值
    map<int,bool>mp; //储存选手是否已经通过此题
}pro[105];
node a[105];
int n,m,maxx=-1;
bool cmp(problem x,problem y){
    return x.point>y.point;
}//排序题目分值
int main(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        pro[i].point=read();
    }//输入
    for(int i=1;i<=n;i++){
        cin>>a[i].s;
        a[i].num=i;
        a[i].sum=i;//初始分
        for(int j=0;j<a[i].s.size();j++){
            if(a[i].s[j]=='o'){
                a[i].sum+=pro[j+1].point;
                pro[j+1].mp[a[i].num]=true;
            }//累加分数，标记已经通过此题
        }
        maxx=max(maxx,a[i].sum);//直接在线求出最大值
    }
    sort(pro+1,pro+1+m,cmp);//对题目排序
    for(int i=1;i<=n;i++){//循环从一开始
        if(a[i].sum==maxx){//如果该选手已经是最大值，那么输出 0 并且跳过
        	puts("0");
			continue;
		}
		int anss=0;//储存需要通过的题目数
        for(int j=1;j<=m;j++){//选取题目
            if(a[i].sum>maxx)break;//如果超过，退出
            if(pro[j].mp[a[i].num]==false){//如果没有做过此题，选取
                a[i].sum+=pro[j].point;
                anss++;//累加题目数
            }
        }
        write(anss);//输出
        puts("");
    }
    return 0;
}
```

$\text{The End}$

---

## 作者：没见过AC (赞：2)

有 $n$ 个选手参赛，共有 $m$ 道题。每题的分数为一百的倍数，给出每个选手目前完成题目的情况，第 $i$ 个选手的分数为完成题目的分数和加上 $i$ 。

问每个选手至少再完成几道题可以超过目前的最高分（即成为第一名）。

因为只是问最少题目数，所以可以贪心。每次做没做过的题中分数最高的题，对于每个选手枚举下一道完成哪道题，直到成为最高分。因为分数加上了 $i$ ,所以在处理时不需要考虑分数相同。处理枚举时可以将做过的题的分数变为零。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1000;
#define reg register
typedef long long ll;
inline ll read()
{
    char c=getchar();ll x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
int m,n,p[N],a[N],b[N],c[N],ma=0,ma_p=0; 
string s[N];
int main()
{
	m=read();
    n=read();
    for(int i=1;i<=n;i++)
    {
    	p[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		cin>>s[i];
		a[i]+=i;
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='o')
			{
				a[i]+=p[j+1];
			}
		}
		if(ma<a[i])
		{
			ma=a[i];
			ma_p=i;
		}//记录第一名的分数和编号 
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			b[j]=p[j];//b数组中做过的题分数为0 
		}
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='o')
			{
				b[j+1]=0;
			}
		}
		int sum=a[i];
		int cnt=0;
		while(sum<=ma&&ma_p!=i)//分数为第一名则退出循环 
		{
			cnt++;
			int max_=0,maxp=0;
			for(int j=1;j<=n;j++)
			{
				if(max_<b[j])
				{
					max_=b[j];
					maxp=j;
				}
			}
			sum+=max_;
			b[maxp]=0;
		}
		cout<<cnt<<"\n";
	}
	return 0;
}

```


---

## 作者：无钩七不改名 (赞：1)

本文是求最少多做多少题分数才能超过当前所有对手。

那么我们只需要记录分数最大值和最大值的人数。

如果当前为最大值，且最大值的人数为 $1$，不需要多做题，否则需要多做一题。

否则，贪心地从分数高向分数低选取未做过的题目，直到分数大于当前最大值，选取的个数即为答案。

### 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=105;

int n,m;
struct emm{
	int a,b[N];
}d[N];
int val[N],mx,qwq;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

bool cmp(emm aaa,emm bbb){
	return aaa.a>bbb.a;
}

int main(){
	n=read();m=read();
	for(int i(1);i<=m;++i)d[i].a=read();
	for(int i(1);i<=n;++i){
		val[i]=i;
		for(int j(1);j<=m;++j){
			char ch;scanf(" %c",&ch);
			if(ch=='o'){
				d[j].b[i]=1;
				val[i]+=d[j].a;
			}
		}
		if(val[i]>mx){
			mx=val[i];
			qwq=1;
		}
		else if(val[i]==mx)++qwq;
	}
	sort(d+1,d+1+m,cmp);
	for(int i(1);i<=n;++i){
		int ans=0;
		if(mx<=val[i]){
			if(qwq==1)puts("0");
			else puts("1");
			continue;
		}
		for(int j(1);j<=m;++j){
			if(d[j].b[i])continue;
			val[i]+=d[j].a;
			++ans;
			if(mx<val[i]){
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：hellolin (赞：1)

# ABC323C World Tour Finals 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/abc323c/) 获得更好的阅读体验！

由于题目保证一定有解，所以对于每个人，贪心地做得分多的题目就好了。

注意已经是最大得分时要输出 $0$。

``` cpp
constexpr int N = 200;
int n, m;
int a[N], r[N], ans, mx;
str s[N];
void solve() {
    std::cin >> n >> m;
    rep(i, m) std::cin >> a[i];
    rep(i, n) {
        std::cin >> s[i];
        s[i] = '#' + s[i];
        rep(j, m) {
            if (s[i][j] == 'o')
                r[i] += a[j];
        }
        r[i] += i;
    }
    mx = *std::max_element(r + 1, r + 1 + n);
    rep(i, n) {
        if(r[i] == mx) {
            std::cout << 0 << '\n';
            continue;
        }
        ans = 0;
        vec<int> wt;
        rep(j, m) if (s[i][j] == 'x')
            wt.pb(a[j]);
        std::sort(wt.begin(), wt.end(), std::greater<int>());
        for (auto &j : wt) {
            ++ans;
            if ((r[i] += j) > mx) break;
        }
        std::cout << ans << '\n';
    }
}
```


---

## 作者：xiaomuyun (赞：1)

## 思路分析

我们先将每个人当前的分数计算出来，其中第 $i$ 个人的分数记为 $cur_i$。然后对于每个人，遍历一遍其他人，看看自己至少还需要多少分数才能超过所有人。记需要的分数为 $need$。

然后我们就只需要提前给输入的数组 $a$ 记下编号后从大到小排个序，再用最基本的的贪心思路做即可（即尽可能选分数贡献大的加上）。具体见代码。

## 代码实现

代码思路和上面一致，虽然可能有一些冗余的空间浪费，但是不影响阅读。

有一些实现细节，大家在看代码时应该可以注意到，在自己写的时候也不要忘了哦。

```cpp
// Problem: C - World Tour Finals
// URL: https://atcoder.jp/contests/abc323/tasks/abc323_c
// Start Time: 2023-10-07 20:00:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
#define inff 0x3f3f3f3f3f3f3f3f
#define mod1 998244353
#define mod2 1000000007
#define int long long
const int maxn=1e2+2;
string s[maxn];
int n,m,cur[maxn],res[maxn];
struct node{
	int val,id;
}a[maxn];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		cin>>a[i].val;
		a[i].id=i;
	}
	for(int i=1;i<=n;++i){
		cin>>s[i];
		s[i]="."+s[i];
		cur[i]=i;
		for(int j=1;j<=m;++j){
			if(s[i][a[j].id]=='o') cur[i]+=a[j].val;
		}
	}
	sort(a+1,a+1+m,[](node a,node b){return a.val>b.val;});//按照题目的分数从大到小排序以保证后面的答案会尽可能小
	for(int i=1;i<=n;++i){
		int need=0;
		for(int j=1;j<=n;++j){
			if(i==j||cur[i]>cur[j]) continue;
			need=max({cur[j]-cur[i],1ll,need});//这里要和 1 取最大值是因为如果 cur[i] 和 cur[j] 相等时还需要 1 的分数才能使 i 超过 j
		}
		// cout<<" "<<need<<'\n';
		if(need>0) for(int j=1;j<=m;++j){//贪心，尽可能选分数贡献大的加上
			if(s[i][a[j].id]=='x') need-=a[j].val,++res[i];
			if(need<=0) break;
		}
		cout<<res[i]<<'\n';
	}
	return 0;
}
```

---

