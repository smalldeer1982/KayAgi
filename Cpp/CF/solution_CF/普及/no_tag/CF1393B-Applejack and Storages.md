# Applejack and Storages

## 题目描述

你一开始有 $n$ 根木棍，接下来有 $q$ 次操作。

操作如下:
* `+ x` 增加一根长度为 $x$ 的木棍。
* `- x` 减少一根长度为 $x$ 的木棍，保证减少之前有长为 $x$ 的木棍。

你要计算出每次操作之后能否用 $8$ 根木棍拼出一个矩形（可以是正方形）和一个正方形。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 样例 #1

### 输入

```
6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2```

### 输出

```
NO
YES
NO
NO
NO
YES```

# 题解

## 作者：45dinо (赞：5)

不是很好讲这一题，因为没有什么可以说的。

感觉就是一个模拟，存储每一种长度出现的次数，记录 4 个一组，2 个一组的个数，每次更新即可。

“YES”的前提：4 个一组的个数大于 0，2个一组的个数大于 3。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a,four,two,num[100001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		num[a]++;
		if(num[a]%4==0)
			four++;
		if(num[a]%2==0)
			two++;
	}
	scanf("%d",&q);
	while(q--)
	{
		char opt;
		scanf("%s %d",&opt,&a);
		switch(opt)
		{
			case '+':{
				num[a]++;
				if(num[a]%4==0)
					four++;
				if(num[a]%2==0)
					two++; 
				break;
			}
			case '-':{
				num[a]--;
				if(num[a]%4==3)
					four--;
				if(num[a]%2==1)
					two--;
				break;
			}
		}
		if(four&&two>=4)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
```

---

## 作者：UniGravity (赞：1)

## Solution CF1393B Applejack and Storages

[传送门](https://www.luogu.com.cn/problem/CF1393B)

### 题意简述
有 $n$ 个数，$q$ 次操作，每次操作可以加入或删除 $x_i$。

现在要你判断每次操作后能否用着 $n$ 个数组成一个正方形和一个矩形。

### 题目分析
首先分析正方形，正方形由长度相等的 $4$ 个边组成，矩形由 $2$ 组长度相等的 $2$ 条边组成。

发现最后结果只与 $2$ 个一组，$4$ 个一组的个数有关，记为 $num_2$ 和 $num_4$。

显然可以发现 `YES` 有一下几种情况：
* $num_4\ge 2$，此时组成 $2$ 个正方形（矩形包含正方形）。
* $num_4\ge 1, num_2\ge2$，此时组成 $1$ 个矩形 $1$ 个正方形。

注意到题目不能重复，$4$ 个一组的情况被包含在 $2$ 个一组的情况中。所以我们需要**额外**的 $2$ 个 $num_2$，判断条件即为 $num_4\ge 1, num_2\ge 4$。

至于如何统计 $num_2$ 和 $num_4$，我们还需记录每个数出现的次数 $cnt_i$。  
在进行增加运算**后**，如果 $cnt_i\bmod 4=0$，那么 $num_4 \gets num_4+1$。  
在进行删除运算**前**，如果 $cnt_i\bmod 4=0$，那么 $num_4 \gets num_4-1$。  
$num_2$ 的计算方法同上。

如此我们便可以在 $O(1)$ 的复杂度内判断，整体复杂度为 $O(n)$。

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q;
int a[100005];
int cnt[100005];
int cnt2 = 0, cnt4 = 0; 

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
        
        // 统计个数
        if (cnt[a[i]] % 4 == 0) cnt4++;
        if (cnt[a[i]] % 2 == 0) cnt2++;
    }
    scanf("%d", &q);
    char s;
    int x;
    while (q--) {
        scanf("%s %d", &s, &x);
        // 注意加与减的顺序不同
        if (s == '+') {
            cnt[x]++;
            
            if (cnt[x] % 4 == 0) cnt4++;
            if (cnt[x] % 2 == 0) cnt2++;
        } else {
            if (cnt[x] % 4 == 0) cnt4--;
            if (cnt[x] % 2 == 0) cnt2--;
            
            cnt[x]--;
        }
        
        if (cnt4 >= 1 && cnt2 >= 4) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```

---

## 作者：绝顶我为峰 (赞：1)

大家都是 $O(n)$ 过此题，本菜鸡提供一个考场上 yy 的 $O(n\log n)$ 垃圾算法![](https://i.loli.net/2020/08/09/eCLhbZzXa2fQc8g.gif)

显然，我们只关心整个序列中数量最多的三个数字（这里按数量从多到少记为 $a,b,c$）：

当 $a,b,c$ 存在以下关系时答案为 ```YES```：

1. $a\geq8$

1. $a\geq6,b\geq2$

1. $a\geq4,b\geq4$

1. $a\geq4,b\geq2,c\geq2$

现在我们考虑如何维护区间前三大值

看到 $n\leq1e5$，而且操作分不同 $opt$，考虑用 $O(n \log n)$ 数据结构维护

由于这个信息满足结合律，想到线段树

因为 $a_i\leq1e5$，所以可以用权值线段树直接记录每个值出现的次数

合并时直接拿左儿子和右儿子的六个值直接暴力合并即可

同时要支持单点修改，查询时直接查询树根的前三大值是否满足上述条件

时间复杂度 $O(n\log n)$，可以通过本题

~~不过没有写出线性算法我真的好菜啊~~

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=100000;
int n,q,a[100001],ans[100001<<2][3];
inline int ls(int k)
{
    return k<<1;
}
inline int rs(int k)
{
    return k<<1|1;
}
inline void push_up(int k)
{
    int l=0,r=0;
    for(register int i=0;i<3;++i)
        if(ans[ls(k)][l]>=ans[rs(k)][r])
            ans[k][i]=ans[ls(k)][l++];
        else
            ans[k][i]=ans[rs(k)][r++];
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        ans[k][0]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls(k),l,mid);
    build(rs(k),mid+1,r);
    push_up(k);
}
void update(int node,int l,int r,int k,int p)
{
    if(l==r)
    {
        ans[k][0]+=p;
        return;
    }
    int mid=(l+r)>>1;
    if(node<=mid)
        update(node,l,mid,ls(k),p);
    if(node>mid)
        update(node,mid+1,r,rs(k),p);
    push_up(k);
}
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    build(1,1,maxn);
    scanf("%d",&q);
    while(q--)
    {
        char c=getchar();
        while(c!='+'&&c!='-')
            c=getchar();
        int x;
        scanf("%d",&x);
        update(x,1,maxn,1,c=='+'? 1:-1);
        if(ans[1][0]>=8||(ans[1][0]>=6&&ans[1][1]>=2)||(ans[1][0]>=4&&ans[1][1]>=4)||(ans[1][0]>=4&&ans[1][1]>=2&&ans[1][2]>=2))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
```


---

## 作者：NuoCarter (赞：1)



### 大致题意

开始给你 $n$ 个木板，之后有 $q$ 次操作

每次操作为以下两种方式：

$+x$ 为长为$x$的木板的个数$+1$

$-x$ 为长为$x$的木板的个数$-1$

每次进行操作后同时查询

所有木板中是否可以构成一个正方形和一个矩形



#### 那么就有以下4种情况：

1.有$8$个长度相等的木板（不会现在都有人不知道正方形算矩形吧）

2.有$>=6$个长度相等的木板1 有$>=2$个长度相等的木板2

3.有$>=4$个长度相等的木板1 有$>=4$个长度相等的木板2

4.有$>=4$个长度相等的木板1 有$>=2$个长度相等的木板2 有$>=2$个长度相等的木板3

很容易想到

只需要获取前三大的长度相等的木板的数量就可以了

#### 我用了一个。。桶+平衡树维护

平衡树用的fhq_treap。。没别的理由就是短。。

### 代码：

```cpp
//CF1393B Applejack and Storages
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
const int N=1e5+5;
int n;
int maxn;
int fhq_size;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
struct node{
	int l,r;
	int size;
	int val,key;
}fhq[2*N];
int cnt,root;
int firstx,secondx,thirdx;
int many[N];
inline int newnode(int val){
	fhq[++cnt].val=val;
	fhq[cnt].size=1;
	fhq[cnt].key=rand();
  fhq_size++;
	return cnt;
}
inline void update(int x){
	fhq[x].size=fhq[fhq[x].l].size+fhq[fhq[x].r].size+1;
	return;
}
inline void split(int now,int val,int &x,int &y){
	if(!now) x=y=0;
	else{
		if(fhq[now].val<=val){
			x=now;
			split(fhq[now].r,val,fhq[now].r,y);
		}
		else{
			y=now;
			split(fhq[now].l,val,x,fhq[now].l);
		}
		update(now);
	}
	return;
}
inline int merge(int x,int y){
	if(!x||!y)	return x+y;
	else{
		if(fhq[x].key>fhq[y].key){
			fhq[x].r=merge(fhq[x].r,y);
			update(x);
			return x;
		}
		else{
			fhq[y].l=merge(x,fhq[y].l);
			update(y);
			return y;
		}
	}
}
int x,y,z;
inline void insert(int val){
	split(root,val,x,y);
	root=merge(merge(x,newnode(val)),y);
	return;
}
inline int getrank(int val){
	split(root,val-1,x,y);
	int t=fhq[x].size+1;
	root=merge(x,y);
	return t;
}
inline int getval(int rank){
	int now=root;
	while(now){
		if(fhq[fhq[now].l].size+1==rank){
			break;
		}
		else if(fhq[fhq[now].l].size>=rank){
			now=fhq[now].l;
		}
		else{
			rank-=fhq[fhq[now].l].size+1;
			now=fhq[now].r;
		}
	}
	return fhq[now].val;
}
inline void del(int val){
	split(root,val,x,z);
	split(x,val-1,x,y);
	y=merge(fhq[y].l,fhq[y].r);
	root=merge(merge(x,y),z);
  fhq_size--;
	return;
}
inline int getpre(int val){
	split(root,val-1,x,y);
	int now=x;
	while(fhq[now].r){
		now=fhq[now].r;
	}
	root=merge(x,y);
	return fhq[now].val;
}
inline int getnext(int val){
	split(root,val,x,y);
	int now=y;
	while(fhq[now].l){
		now=fhq[now].l;
	}
	root=merge(x,y);
	return fhq[now].val;
}
int q,query;
int t,siz;
char op[2];
int main(){
	n=read();
  for(int i=1;i<=n;++i){
    t=read();
    many[t]++;
    maxn=max(maxn,t);
  }
  for(int i=1;i<=maxn;++i){
    if(many[i]) insert(many[i]);
  }
  q=read();
  while(q--){
    scanf("%s",op);
    query=read();
    if(op[0]=='+'){
      del(many[query]);
      many[query]++;
      insert(many[query]);
      siz=fhq[root].size;

      firstx=getval(siz);
      secondx=getval(siz-1);
      thirdx=getval(siz-2);

      if(firstx>=8||(firstx>=6&&secondx>=2)||(firstx>=4&&secondx>=4)||(firstx>=4&&secondx>=2&&thirdx>=2)){puts("YES");}
      else{puts("NO");}
    }
    else{
      del(many[query]);
      many[query]--;
      insert(many[query]);
      siz=fhq[root].size;

      firstx=getval(siz);
      secondx=getval(siz-1);
      thirdx=getval(siz-2);

      if(firstx>=8||(firstx>=6&&secondx>=2)||(firstx>=4&&secondx>=4)||(firstx>=4&&secondx>=2&&thirdx>=2)){puts("YES");}
      else{puts("NO");}
    }
  }
  return NuoCarter;
}

```



---

## 作者：引领天下 (赞：1)

显然答案只与仓库中个数为 $4$ 和 $2$ 的木板各有多少种有关。

由于有 $8$ 块的木板可以拆成 $2$ 个 $4$ 块的，也可以拆成 $4$ 个 $2$ 块的，也可以拆成 $1$ 个 $4$ 块的， $2$ 个 $2$ 块的， $6$ 块的、 $12$ 块的……等等同理，故所有 `YES` 的情况都可以转化为一种情况：存在**至少** $1$ 个 $4$ 块的，以及存在**至少** $2$ 个 $2$ 块的。两个条件要求同时满足，而且需要考虑是否会重叠。

那么我们开若干个 `set` ，将个数为 $i$ 的木板丢到 $s[i>>1]$ 中去，最后统计是否满足题意即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,q,cnt[100055],a,k[100055],c4,c2;
char c;
set<long long>s[10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n;
	for(register int i=1;i<=n;i++){cin>>a;cnt[a]++;}
	cin>>q;
	for(register int i=1;i<=100051;i++)
	for(register int j=8;j>=2;j-=2)if(cnt[i]>=j){s[j>>1].insert(i);break;}//统计有哪些木板有>=j块
	while(q--){
		cin>>c>>a;
		if(c=='+'){//将新来的木板放入对应的set中，并且更新此长度的木板的数量
			if(cnt[a]==1)s[1].insert(a);
			if(cnt[a]==3||cnt[a]==5||cnt[a]==7)s[cnt[a]>>1].erase(a),s[(cnt[a]+1)>>1].insert(a);
			cnt[a]++;
		}
		else{//将该木板从对应的set中删除，并更新此长度的木板的数量
			if(cnt[a]==2)s[1].erase(a);
			if(cnt[a]==4||cnt[a]==6||cnt[a]==8)s[cnt[a]>>1].erase(a),s[(cnt[a]-1)>>1].insert(a);
			cnt[a]--;
		}
		if(s[4].size()){puts("YES");continue;}//分类讨论：有8块的，那肯定满足，可拆成4+2+2
		if((s[3].size()>1)||(s[3].size()&&(s[2].size()||s[1].size()))){puts("YES");continue;}//有6块的，且不止一个，则可以拆成4+2+2；有6块的，且有4块的或者2块的，均可以拆成4+2+2，满足题意。
		if((s[2].size()>1)||(s[2].size()&&s[1].size()>1)){puts("YES");continue;}//有4块的，且不止一个，可拆成4+2+2；或者有4块的，且2块的不止一个，也是4+2+2，符合题意。
		puts("NO");
	}
}
```

---

## 作者：K2sen (赞：1)

### 思路
用 ma 来存每一个数出现的次数，我们将出现次数为 4 或者 2 分开来看。

er 用来存有除了能组成正方形之外还有多少对长方形的对边， si 存储能组成多少个正方形。

我们用 gsi 来存储每一个数 x 出现出现次数为 4 （ 最多能组成多少个正方形 ） 的所产生的贡献。

例: 2 出现了 7 次那么它对 gsi 产生的贡献就是 1 。

我们用 ger 来存储每条长度为 x 的边除了组成正方形之外还能组成长方形的多少个对边所产生的贡献。

例： 2 出现了 7 次， 可以组成一个正方形，最后会剩下 3 个长为 2 的边，能组成的长方形一个对边的对边数为 1 ，显然这个东西不会超过 1 。

一开始的时候算一下每一个数能产生多少个正方形和长方形的对边， 在每一次公司事件发生之后，更新每个数出现的次数，重新算一下数 x 对 er 和 si 的贡献。

代码中还有详解

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 1010

using namespace std;
map<int, int> ma;
int er, si, n, q, em[N], top;
map<int, int> ger, gsi;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

bool check() {//每次事件发生之后判断是否能组成两个正方形或长方形
	if (si == 0) return 0;
	else if (si == 1) {
		if (er < 2) return 0;
		else return 1;
	} else return 1;
}

int main() {
	n = read();
	for (int i = 1, x; i <= n; i++)
		x = read(), ma[x]++, em[top++] = x;
	sort(em, em + top);
	int sy = unique(em, em + top) - em;//去重，防止重复计算
	for (int i = 0; i < sy; i++) {//计算一开始每个数的贡献
		if (ma[em[i]] >= 2) {
			er += (ma[em[i]] % 4) / 2;
			ger[em[i]] = (ma[em[i]] % 4) / 2;
		}
		if (ma[em[i]] >= 4) {
			si += ma[em[i]] / 4;
			gsi[em[i]] += ma[em[i]] / 4;
		}
	}
	q = read();
	char opt; int x;
	for (int i = 1; i <= q; i++) {
		cin >> opt; x = read();
		if (opt == '+') ma[x]++;//更新出现次数
		if (opt == '-') ma[x]--;
		er -= ger[x];//对于更新完次数的每一个数可以
		//先减去以前的贡献再加上现在的贡献
		er += (ma[x] % 4) / 2;
		ger[x] = (ma[x] % 4) / 2;
		si -= gsi[x];
		si += ma[x] / 4;
		gsi[x] = ma[x] / 4;
		if (check()) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：__CrossBow_EXE__ (赞：0)

一道超级简单的模拟题。

# 前言

我对此题的意见如下：

- 建议降橙；
- 建议加上模拟标签。

# 题意

~~直接看翻译~~

首先输入一个长度为 $n$ 的数组 $a$，定义两个操作：

- `+ x` 在 $a$ 中添加 $x$；
- `- x` 在 $a$ 中删除 $x$。

接着输入 $q$ 行，每行分别代表一个指令，就是上面的两个操作。

最后 $a$ 中有 $8$ 个元素，问它们能否拼成一个矩形和一个正方形。

# 分析

实在没什么好说的。

长度要满足如下条件：

1. 必须得有**至少一个正方形**，也就是说 $8$ 个长度中至少得有 $4$ 个长度是一样的；
2. 如果有 $4$ 个长度一样，那剩下的只能是 $2$ 个较长的，$2$ 个较短的；
3. 如果有 $6$ 个长度一样，那剩下的 $2$ 个长度也得一样。

是不是被绕晕了？没关系，我们可以用排序实现！排序会自动将一样的长度放到一起。

# 代码

上面讲的很详细了，代码不放，能理解吧？

不能也得能！

---

## 作者：Tiago (赞：0)

## Solution

注意到能拼出时必须要存在 $2$ 组及以上的四个相同的木棍，或者 $1$ 组及以上的四个相同的木棍和**除此之外**的 $2$ 组及以上的两个相同的木棍。

同时又注意到 $a_i$ 很小，所以可以用桶统计，同时实时更新四个相同木棍的组数和两个相同木棍的组数即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

const int N=1e5;
int n,t[N+4],_4,_2;
void solve()
{
	char ch;int x;cin>>ch>>x;
	// cout<<ch<<"\n";
	if(ch=='+')
	{
		if((t[x]+1)/4>t[x]/4)_4++;
		if((t[x]+1)/2>t[x]/2)_2++;
		if(_4>=2 || (_4>=1 && _2>=4))cout<<"YES\n";// 注意这里的 _2 要 >=4，因为 _4 的那一组不能算上，准确写应为 _2-2>=2。下同。
			else cout<<"NO\n";
		t[x]++;
	}
	if(ch=='-')
	{
		if((t[x]-1)/4<t[x]/4)_4--;
		if((t[x]-1)/2<t[x]/2)_2--;
		if(_4>=2 || (_4>=1 && _2>=4))cout<<"YES\n";
			else cout<<"NO\n";
		t[x]--;
	}
	// cout<<_4<<" "<<_2<<"\n";
}
int main()
{
	IOS;
	cin>>n;
	For(i,1,n){int x;cin>>x;t[x]++;}
	For(i,1,N)_4+=(t[i]/4),_2+=(t[i]/2);
	int q;cin>>q;
	while(q--)solve();

	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](https://codeforc.es/problemset/problem/1393/B)  
[在CSDN上查看](https://blog.csdn.net/jiangtaizhe/article/details/108102337)  
## 题目翻译
你需要维护一个序列，让它满足一下操作：  
1. 插入一个数字
2. 删除一个数字，保证这个数字是存在
3. 在每次删除和插入之后查询这些数字是否可以组成一个正方形和矩形

## 题目解析
为了方便，我们可以开一个桶，这样就变成了：
1. 单点修改
2. 区间查询最大值、第二、第三大值（不严格）  

查询最大、第二大、第三大的值的作用：组成一个正方形、一个矩形最多要用三种木棍，如果最多的都不能组成就表示肯定不能组成了。

然后看一眼数据范围： $n,q\leq100000$ ，那么暴力还是过不去的，需要加一点数据结构优化，~~因为我菜所以我们就用分块吧！~~  
块的大小的取值是 $\sqrt{n}$ ,所以我们取 $316$ ，这样就可以达到最快的速度了。  
我们~~只~~要维护六个数组就可以了。  
$maxx_i,maxy_i,maxz_i$ 表示第 $i$ 块的最大值，第二大值，第三大值。  
$num1_i,num2_i,num3_i$ 表示第 $i$ 块的最大值，第二大值，第三大值的序号。  
然后只要注意加亿点点细节就可以了，~~因为比赛的时候WA了4次~~。  

最后奉上代码：
```cpp
#include<cstdio>
#include<cstring>
#define maxn 100039
#define maxk 350
using namespace std;
int maxx[maxk],maxy[maxk],maxz[maxk];
int num1[maxk],num2[maxk],num3[maxk];
int a[maxn];
int n,T,x,y,z,k,m;
char c;
void build(){
	k=316; m=100000/k+2;
	memset(maxx,0xaf,sizeof(maxx));
	memset(maxy,0xaf,sizeof(maxy));
	memset(maxz,0xaf,sizeof(maxz));
	int tmp;
	for(int i=1;i<=100001;i++){
		tmp=(i-1)/k+1;
		if(maxx[tmp]<a[i]){
			maxz[tmp]=maxy[tmp];
			maxy[tmp]=maxx[tmp];
			maxx[tmp]=a[i];
		}
		else if(maxy[tmp]<a[i]){
			maxz[tmp]=maxy[tmp];
			maxy[tmp]=a[i];
		}
		else if(maxz[tmp]<a[i]){
			maxz[tmp]=a[i];
		}
	}
	return;
}
void add(int x,int y){
	a[x]+=y;
	int s,t,tmp;
	tmp=(x-1)/k+1;
	s=(tmp-1)*k+1;
	t=tmp*k;
	maxx[tmp]=maxy[tmp]=maxz[tmp]=1e-10;
	for(int i=s;i<=t;i++){
		if(maxx[tmp]<a[i]){
			maxz[tmp]=maxy[tmp];
			maxy[tmp]=maxx[tmp];
			maxx[tmp]=a[i];
		}
		else if(maxy[tmp]<a[i]){
			maxz[tmp]=maxy[tmp];
			maxy[tmp]=a[i];
		}
		else if(maxz[tmp]<a[i]){
			maxz[tmp]=a[i];
		}
	}
}
int check(int x,int y,int z){
	if(x>=8) return 1;
	if(x>=6&&y>=2) return 1;
	if(x>=4&&y>=4) return 1;
	if(x>=4&&y>=2&&z>=2) return 1;
	return 0;
}
void findmax(){
	for(int i=1;i<=m;i++){
		    if(maxx[i]>x){
		    	z=y; y=x; x=maxx[i];
			}
			else if(maxx[i]>y){
				z=y; y=maxx[i];
			}
			else if(maxx[i]>z) z=maxx[i];
			
			if(maxy[i]>x){
		    	z=y; y=x; x=maxy[i];
			}
			else if(maxy[i]>y){
				z=y; y=maxy[i];
			}
			else if(maxy[i]>z) z=maxy[i];
			
			if(maxz[i]>x){
		    	z=y; y=x; x=maxz[i];
			}
			else if(maxz[i]>y){
				z=y; y=maxz[i];
			}
			else if(maxz[i]>z) z=maxz[i];
		}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		a[x]++;
	}
	build();
	scanf("%d",&T);
	while(T--){
		c=getchar();
		while(c!='+'&&c!='-') c=getchar();
		scanf("%d",&x);
		if(c=='+') add(x,1);
		if(c=='-') add(x,-1);
		x=y=z=-1;
		findmax();
		if(check(x,y,z)) printf("YES\n");
		else printf("NO\n");	
	}
	return 0;
}
```

---

## 作者：huayucaiji (赞：0)

我们思考一下这个题给我们的信息。我们要用已有木棒拼出一个正方形和一个长方形。因为长方形的范围比正方形广，所以我们有一个贪心策略就是先判断是否有正方形再判断剩下的是否有长方形。

我们做的就是要统计有多少组木棒可以拼出正方形，我们记为 $four$（重复的木棒不能出现在两组中）。我们再来统计把所有 $4$ 个木棒长度相等的组剔除后，有多少组是两个木棒程度相等的，记为 $two$。注意，由于我们的贪心策略，我们优先考虑 $four$。所以两组相等的二元组就会被我们合并成为一个四元组。

最后只要满足 $four>0$ 且 $two>1$，或者 $four>1$，即拼出两个正方形，我们就输出 ```YES```。否则 ```NO```。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10; 

int n,cnt[maxn],m,four,two;
char ch;

signed main() {
	n=read();
	for(int i=1;i<=n;i++) {
		int x=read();
		cnt[x]++;
		if(cnt[x]%4==0) {//先4后2
			four++;
			two--;
		}
		if(cnt[x]%4==2) {
			two++;
		}
	}
	m=read();
	
	for(int i=1;i<=m;i++) {
		cin>>ch;
		int x=read();
		if(ch=='+') {
			cnt[x]++;
			if(cnt[x]%4==0) {//先4后2
				four++;
				two--;
			}
			if(cnt[x]%4==2) {
				two++;
			}
		}
		else {
			if(cnt[x]%4==0) {//先4后2
				four--;
				two++;
			}
			if(cnt[x]%4==2) {
				two--;
			}
			cnt[x]--;
		}
		
		if(four>0&&two>1) {
			printf("Yes\n");
		}
		else if(four>1) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}

```

---

## 作者：yu__xuan (赞：0)

### 题目
[CF1393B Applejack and Storages](https://www.luogu.com.cn/problem/CF1393B)

### 思路
模拟。
拼出一个正方形需要 $4$ 根长度相同的木棍，拼出一个矩形需要 $4$ 根长度相同的木棍或者 $2$ 组 $2$根长度相同的木棍

那么我们只要记录能凑出多少组长度相同的 $4$ 根木棍 $four$,（对于每种长度的木棍只需要记录一次贡献，因为 $4$ 根完全相同已经足够拼一个正方形，剩下的记录到长度相同的 $2$ 根木棍中即可）和能凑出多少组长度相同的 $2$ 根木棍 $two$。

最后判断组数即可：
* 如果 `four == 0` 显然拼不出正方形，答案为 `NO`。

* 如果 `four >= 2` 能拼出两个正方形，答案为 `YES`。

* 如果 `four == 1` 当 `two >= 2` 时答案为 `YES`，否则答案为 `NO`。

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define MAXN 100001

int n, m, a[MAXN], two, four;
int times[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (times[a[i]] >= 2) {
			if (times[a[i]] >= 4) {
				--four;
				two -= (times[a[i]] - 4) / 2;
			}
			else two -= times[a[i]] / 2;	
		}	
		++times[a[i]];
		if (times[a[i]] >= 2) {
			if (times[a[i]] >= 4) {
				++four;
				two += (times[a[i]] - 4) / 2;
			}
			else two += times[a[i]] / 2;	
		}	
	}
	scanf("%d", &m); char opt;
	for (int i = 1, x; i <= m; ++i) {
		std::cin >> opt;
		scanf("%d", &x);
		if (opt == '+') {
			if (times[x] >= 2) {
				if (times[x] >= 4) {
					--four;
					two -= (times[x] - 4) / 2;
				}
				else two -= times[x] / 2;
			}
			++times[x];
			if (times[x] >= 2) {
				if (times[x] >= 4) {
					++four;
					two += (times[x] - 4) / 2;
				}
				else two += times[x] / 2;
			}
		}	
		else {
			if (times[x] >= 2) {
				if (times[x] >= 4) {
					--four;
					two -= (times[x] - 4) / 2;
				}
				else two -= times[x] / 2;
			}
			--times[x];
			if (times[x] >= 2) {
				if (times[x] >= 4) {
					++four;
					two += (times[x] - 4) / 2;
				}
				else two += times[x] / 2;
			}
		}
		if (four >= 2) puts("YES");
		if (four == 1) {
			if (two >= 2) puts("YES");
			else puts("NO");
		}	
		if (four == 0) puts("NO");	
	}	
	return 0;
}	
```

---

