# Queries on a String

## 题目描述

# **CF598B的翻译**
      给你一个字符串s，接着有m次循环移位。
      循环移位的一个操作就是将s的最后一个字符移动到第一个字符的位置，并且将所有其他的字符向右移动一个位置。
      例如，s='abacaba'，查询是L1=3，R1=6，K1=1，那么答案是’abbacaa’（解释：从s第三个位置到第六个位置’acab’，循环1次，把b移到第一位，其他往后移一位，就是’baca’，替换之前的’acab’），之后如果我们再做处理L2=1，R2=4，K2=2，那么答案就变’baabcaa’（解释：首先从第一个位置到第四个位置’abba’，第一次通过移位得到’aabb’，第二次就得到’baab’，替换之前的’abba’）。

## 样例 #1

### 输入

```
abacaba
2
3 6 1
1 4 2
```

### 输出

```
baabcaa
```

# 题解

## 作者：chlchl (赞：3)

好久没有写题解了，估值都掉光了……

## 题意简述
~~这题目翻译什么鬼啊……~~

给定一个字符串，$m$ 个询问，每次询问给定 $l,r,k$，意思是将 $\lbrack l,r\rbrack$ 这个子串循环移位 $k$ 次。

循环移位：若将 ``abc`` 循环移位一次，就变成 ``cab``。

## 思路
两种思路。

### 1、``fhq_treap`` 或 ``Splay`` 的简单板子。
没啥好说的，一道黄题用平衡树无疑是大题小做。
### 2、暴力模拟
注意到 $1\leq m\leq 300$ 的极小数据，我们可以直接暴力。

可以发现，循环移位若干次相当于拿走一个子串后缀，把它放到这个字串的前面，而这个后缀的长度应该是 $r-l+1-k$。我们可以使用 STL 里的 ``substr`` 和 ``erase`` 函数来完成操作。

但是 $k$ 有可能大于 $r-l+1$，所以我们需要对 $k$ 取模（因为每循环移位 $r-l+1$ 次相当于没移）。

然后这题就差不多啦！
## 代码
珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int len, m, l, r, k;

int main(){
	cin >> s >> m;
	len = s.length();
	s = " " + s;
	while(m--){
		cin >> l >> r >> k;
		int lens = r - l + 1;
		k %= lens;
		string s1 = s.substr(l, lens - k);//截取需要往后挪的字符（串）
		s.erase(l, lens - k);//删掉这个字符（串），模拟往前移 
		s.insert(l + k, s1);//把字符重新插入，模拟往后移，插入的位置应该在
	}
	s.erase(0, 1);//把刚开始加的空格删一下
	cout << s << endl;
	return 0;
}
```


---

## 作者：Jairon314 (赞：2)

### CF598B

> 据说 CSP 前发题解会涨 RP ，CSP2021 rp++！！1

> 希望今年能蓝勾吧~

看学长给普及组出的模拟赛，出了这个的原题。正确算法是暴力模拟，但是有个学长第一眼看成了平衡树，并且用平衡树 ``AC`` 了此题，于是我就把这题当作 ``Splay`` 的板子来写了。

这题的操作就是区间循环移位(revolve)。举个例子：

假设有序列

$ \color{red} {1 \, 2 \, 3 \, 4 \, 5 \, 6} $

我们对他进行 revolve(2,4,1) 操作，变成

$ \color{red} {1 \, 4 \, 2 \, 3 \, 5 \, 6} $

那么这题怎么用平衡树写呢？

~~直接找到区间分裂合并~~

其实有点麻烦，我实现好久没实现出来，这个操作 ``FHQ_Treap`` 好写。

后来我在纸上写写画画了好久，才发现了一个规律

$ \text {revolve(l,r,k) 等价于 reverse(r-k+1,r) , reverse(l,r-k) , reverse(l,r) } $

照着这个模拟一遍应该就能发现这个较为显然的规律了，我就不再证明了。

// reverse(l,r) 是区间翻转。

到这里，我们就成功的把区间循环移位操作转化成了区间翻转操作。那么区间翻转操作怎么实现呢？我们发现这就是文艺平衡树的板子题了。但是，写了个板子交上发现，``TLE on #3`` 了，这是什么情况呢？到 CF 上看了看数据，原来是没考虑到 $ k $ 大于区间长度的情况。所以还要在操作以前让 $ k=k \bmod len $ 。这里的 $ len $ 是区间长度，等价于 $ r-l+1 $。

// $ l $ 为区间左端点，$ r $ 为区间右端点。

至此，我们就能通过此题了。复杂度 $ O(mlogn) $ ，吊打暴力模拟。希望洛谷能把这题和文艺平衡树合并一下，作为加强版~

接下来就看一下代码实现吧~

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

#define $int long long

/***** Fast_IO *****/

using std::cin;
using std::cout;
using vii = std::vector<int> ;
using pii = std::pair<int,int> ;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	inline char gc (){
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<21),stdin),p1==p2)?EOF:*p1++;
	}

	#define gc getchar
	#define pc putchar
	#define ONLINE_JUDGE OJ

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}

	void _FILE(){
		#ifndef ONLINE_JUDGE
			freopen("text.in","r",stdin);
			freopen("text.out","w",stdout);
		#endif
	}

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

int n,m,l,r,k;

char s[maxn];

class splay{
	private:
		struct SP_tree{ int son[2],fa,cnt,size,val,rev; }tree[(maxn)];

		int tree_cnt,root;

	public:
		void pushup(int ID){ tree[ID].size=tree[tree[ID].son[0]].size+tree[tree[ID].son[1]].size+tree[ID].cnt; }

		void pushdown(int ID){
			if(tree[ID].rev){
				tree[tree[ID].son[0]].rev^=1;
				tree[tree[ID].son[1]].rev^=1;
				::swap(tree[ID].son[0],tree[ID].son[1]);
				tree[ID].rev^=1;
			}
			return;
		}

		int Son(int ID){ return tree[tree[ID].fa].son[1]==ID; }

		void connect(int x,int y,int k){
			if(x){ tree[x].son[k]=y; }
			tree[y].fa=x;
		}

		void rotate(int ID){
			int fa(tree[ID].fa),gra_fa(tree[fa].fa);
			int ty_son( Son(ID) ),ty_fa( Son(fa) );
			connect(fa,tree[ID].son[ty_son^1],ty_son);
			connect(ID,fa,ty_son^1);
			connect(gra_fa,ID,ty_fa);
			pushup(fa);
			pushup(ID);
			return;
		}

		void Splay(int ID,int goal=0){
			for(int index;(index=tree[ID].fa)!=goal;rotate(ID)){
				if(tree[index].fa!=goal){
					if(Son(index)==Son(ID)){
						rotate(index);
					} else{ rotate(ID); }
				}
			}
			if(goal==0){ root=ID; }
			return;
		}

		int NewNode(int val){
			tree[++tree_cnt]=(SP_tree){{0,0},0,1,1,val,0};
			return tree_cnt;
		}

		void insert(int val){
			if(!root){ root=NewNode(val); return; }
			int index=root;
			while(tree[index].val!=val&&tree[index].son[tree[index].val<val]){
				index=tree[index].son[tree[index].val<val];
			} if(tree[index].val==val){ ++tree[index].cnt; Splay(index); return; }
			connect(index,NewNode(val),tree[index].val<val);
			Splay(tree[index].son[tree[index].val<val]);
			return;
		}

		int get_num(int rk){
			int index=root;
			while(19260817){
				pushdown(index);
				if(tree[tree[index].son[0]].size>=rk){
					index=tree[index].son[0];
				} else if(tree[tree[index].son[0]].size+tree[index].cnt<rk){
					rk-=(tree[tree[index].son[0]].size+tree[index].cnt);
					index=tree[index].son[1];
				} else{ break; }
			}
			return index;
		}

		int split(int l,int r){
			l=get_num(l);
			r=get_num(r+2);
			Splay(l,0);
			Splay(r,l);
			return tree[tree[root].son[1]].son[0];
		}

		void reverse(int l,int r){
			int rt=split(l,r);
			tree[rt].rev^=1;
		}

		void revolve(int l,int r,int k){
			k=k%(r-l+1);
			reverse(r-k+1,r);
			reverse(l,r-k);
			reverse(l,r);
			return;
		}

		void dfs(int now=-1){
			if(now==-1){ now=root; }
			pushdown(now);
			if(tree[now].son[0]){ dfs(tree[now].son[0]); }
			if(tree[now].val>1&&tree[now].val<n+2){ ::cout<<(s[tree[now].val-1]); }
			if(tree[now].son[1]){ dfs(tree[now].son[1]); }
			return;
		}
}sp;

int main(){
	_FILE();
	::cin>>(s+1);
	n=strlen(s+1);
	FOR(i,1,n+2){ sp.insert(i); }
	read(m);
	while(m--){
		read(l,r,k);
		sp.revolve(l,r,k);
	}
	sp.dfs(); pc('\n');
	return 0;
}
```


---

## 作者：hxhhxh (赞：2)

## 大意

给定一个字符串 $ s $ ，有 $ m $ 此操作，每一次操作给定区间 $ l $ 到 $ r $ 和 $ k $ ，使 $ [l,r] $ 区间循环位移 $ k $ 位，输出结果。

## 思路

$ |s|\leq 10000 $ ， $ m\leq 300 $ ，所以可以直接模拟， $ O(n\times m) $ 不会`TLE`。

对于第 $ i $ 次操作，第 $ j (l \leq j \leq r) $ 个字符应移到 $ ((j-l_i+k_i) \mod (r_i-l_i+1))+l $ ，然后就可以直接模拟了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[10005],c[10005];
int main(){
    cin>>a+1;
    n=strlen(a+1);
    cin>>n;
    for(int i=1,l,r,k;i<=n;i++){
        scanf("%d %d %d",&l,&r,&k);
        for(int j=l;j<=r;j++) c[j]=a[j];
        for(int j=l;j<=r;j++) a[(j-l+k)%(r-l+1)+l]=c[j];
    }
    cout<<a+1;
    return 0;
}
```

---

## 作者：45dino (赞：1)

一个比较入门的字符串。

如果原字符串是 $s_0\dots s_{m-1}$ ，那对于第 i 位，应该放到 $(i+k)\mod m$ 的位置上。

然后代码就显而易见了。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int q,m,l,r,k;
char c[10001];
void work(int l,int r,int k)
{
	m=r-l+1;
	for(int i=l;i<=r;i++)
		c[(i-l+k)%m]=s[i];
	for(int i=l;i<=r;i++)
		s[i]=c[i-l];
	return ;
}
int main()
{
	cin>>s;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d%d",&l,&r,&k);
		work(l-1,r-1,k);
	}
	cout<<s;
	return 0;
}
```


---

## 作者：Crasole (赞：0)

## 题意

-----

有一种循环位移操作，每次将字符串 $s$ 上 $r_i$ 位置的字符移动到串 $s$ 的 $l_i$ 位置的前面，一共做 $k_i$ 次。

现在给出字符串 $s$，并给出 $m$ 次的循环位移操作，要输出 $m$ 次循环位移操作后的结果。

如串 `abacaba`，操作是 $l_1 = 3,r_1 = 6,k_i = 1$ 那么答案就是 `abbacaa`（解释：从 $s$ 第三个位置到第六个位置是 `acab`，循环 $1$ 次，把 `b` 移到第一位，其他往后移一位，就是 `baca`，替换之前的 `acab`）。

## 思路

-----

用C++中的STL可以解决这个问题。

- `st.insert(pos,t)`：在 `st` 的 `pos` 个字符前插入字符串 `t`。

- `st.substr(pos,k)`：在 `st` 的第 `pos` 个字符起，截取 `k` 个字符。

- `st.erase(pos,k)`：在 `st` 的第 `pos` 个字符起，删除 `k` 个字符。

---

1. 对于每次读入的 $l_i,r_i,k_i$ 先算出需要位移的位数，因为 $k$ 有可能大于区间长度，所以真实位移的长度等于 `k%=r-l+1`。

2. 接着截取串 $s$ 的后面 $k$ 位，等于 `st.substr(r-k+1,k)`。

3. 最后插入，`st.insert(l,s)`。

4. 因为后面的部分被插到前面去了，所以要把后面原来的部分给删掉， `st.erase(r+1,k)`。

## 代码

-----

```cpp
#include<bits/stdc++.h>
using namespace std;
string st;int m,len;
int main(){
	cin>>st>>m;
	st=" "+st;//开头加上空格方便操作
	while(m--){
		int l,r,k;
		cin>>l>>r>>k;
		len=r-l+1;
		k%=len;//算出实际要位移的长度
		string s=st.substr(r-k+1,k);//截取位移部分
		st.insert(l,s);//插入
		st.erase(r+1,k);//删掉原来的部分
	}
	st.erase(0,1);//删去最开始加的空格
	cout<<st;
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

大水题。

因为 $1\le|s|\le10000$ 且 $1\le m \le 300$，所以暴力是完全可行的！

~~不过我用的奇奇怪怪的方法还是不要借鉴了，看看就好。~~

思路：

1. 输入字符串，一开始建立一个数组 $qwq$ 表示现在的字符串的状态。现在字符串的第 $i$ 个对应 $s$ 的第 $qwq[i]$ 个字符。所以一开始，$qwq[i]=i$。（当然你也可以直接在字符串里操作，我只是比较菜）
2. 输入次数。输入开始和结束位置以及循环移位操作次数。（直接在字符串里操作的同学注意了，开始和结束位置是从一开始算的，所以当你操作时要减一）
3. 把待操作的字符串中要操作的地方提取出来。
4. 算出循环移位后的第一个字符对应待操作字符串中的哪个字符。
5. 从那个字符开始，循环把新的对应信息存进去。（注意如果超过结束位置要回到开始位置）
6. 输出对应的数，完结撒花！

写的比较艰涩难懂，如果看不懂就看代码注释。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int qwq[114514];//习惯写这个了，不要看
int t[114514],i;
int main(){
	string s;
	cin>>s;
	for(i=1;i<=s.length();i++)qwq[i]=i;//对应关系
	int m;
	scanf("%d",&m);
	while(m--)
	{
		memset(t,0,sizeof(t));
		int st,fn,mo;
		scanf("%d%d%d",&st,&fn,&mo);
		for(i=st;i<=fn;i++)t[i]=qwq[i];//提取
		int now=fn-(mo%(fn-st+1)-1);//这里是算出来开始位置的公式，不懂的自己想想为什么
		for(i=st;i<=fn;i++)
		{
			if(now>fn)now=st;//越界就重置
			qwq[i]=t[now];//代入新的值
			now++;
		}
	}
	for(i=1;i<=s.length();i++)
	cout<<s[qwq[i]-1];//一定要减一！字符串从零开始！
	return 0;
}

```

---

## 作者：CrTsIr400 (赞：0)

一开始我还以为要用链表做的。

后来看了看**数据范围**：

$1\leq n\leq 10^4$，$1\leq m\leq 300$。

${1\leq m\leq 300 }$！！！

直接**数组移位**就好。

每次读进来就把 $k$ **取模** $r-l+1$ ，然后给 $[l,r]$ 区间**移动** $k$ 位，**时间复杂度** $\text{O}(nm)$ ，**不会**超时。

**注意特判移位时会不会移出区间** $[l,r]$ 。

```cpp
#include<bits/stdc++.h>
#define inf ((1<<30)-1)
#define linf ((1<<62)ll-1)
#define LL long long
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define Fn(i,a) for(register int i=las[a];i;i=nex[i])
int Fl,Pn,SI=100;char mch=' ',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
int n,m,l,r,k;char a[10001],b[10001];
inline int ri(int i,int k){return (i+k-l)%(r-l+1)+l;}
inline void move_a()
{
	Fu(i,l,r)b[ri(i,k)]=a[i];
	Fu(i,l,r)a[i]=b[i];
}
int main()
{
	while(isalpha(a[++n]=getchar()));
	n--;in(m);
	Fu(i,1,m)
	{
		in(l,r,k);
		k%=(r-l+1);
		if(k==0)continue;
		move_a();
	}
	Fu(i,1,n)putchar(a[i]);
	return 0;
}

```

---

