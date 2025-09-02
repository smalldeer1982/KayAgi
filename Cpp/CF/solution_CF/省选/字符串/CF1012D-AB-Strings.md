# AB-Strings

## 题目描述

## 题面描述
给定两个只包含 $\texttt{a}$ 和 $\texttt{b}$ 的字符串，每次操作可以把两个字符串的任意前缀进行交换（前缀长度可以为 $0$），问最少多少次操作可以使的一个串只有 $\texttt{a}$，另一个串只有 $\texttt{b}$。

## 样例 #1

### 输入

```
bab
bb
```

### 输出

```
2
1 0
1 3
```

## 样例 #2

### 输入

```
bbbb
aaa
```

### 输出

```
0
```

# 题解

## 作者：鱼跃于渊 (赞：3)

## 做法  

这里提供一种写法，与现有两篇略有不同。  
首先我们可以发现，在同一个字符串中相邻又相同的两个字符，在最优操作里必定不会分开。  
所以我们考虑压缩字符串，举个例子：$\texttt{aabbbaa}$ 可以压缩成 $\texttt{aba}$。  
压缩后可以发现，我们真正要操作的字符串一定形如 $\texttt{ababa\ldots}$ 或 $\texttt{babab\ldots}$。  
于是我们的目标就变成了如何使这两个字符串一个变成 $\texttt{a}$，另一个变成 $\texttt{b}$，同时操作数最小。  

首先显然的是，在一次操作中，我们只可能消除掉至多 $2$ 个字符。  
如何做到最优呢？我们分类讨论：  
1. 两个字符串首字母相同。  
    + 普通操作：  
        现在我们面临的是两个形如 $\texttt{ababa\ldots}$ 的字符串，显然我们只要将一个串开头的 $\texttt{a}$ 挪到另一个串的开头，就可以消除掉一个字符。  
    + 更优操作：  
        考虑更优操作，可以发现我们只需要交换一个串的 $\texttt{ab}$ 和另一个串的 $\texttt{a}$，就可以消除掉两个字符。  
        仅当有一个串的长度 $>2$ 时才能使用该操作，原因显然。  
    + 特殊操作：  
        如果有一个串的长度为 $1$ 呢？再次分类讨论：  
        当另一个串长度为 $2$ 或 $4$ 时，显然使用普通操作；为 $3$ 时，显然使用更优操作；那么 $>4$ 呢？这时候我们就要使用特殊操作了。  
        特殊操作就是把一个串开头的 $\texttt{aba}$ 挪到另一个串的开头，但为什么要这么做呢？  
        考虑 $\texttt{a}$ 和 $\texttt{ababa}$，如果我们使用普通操作（更优操作用不了），最小操作次数为 $4$，但是使用特殊操作就可以降到 $3$ 次。  
        究其根本，普通操作每次只能消除掉一个字符，而特殊操作后形成的 $\texttt{aba}$ 和 $\texttt{ba}$ 交换开头第一个字符后却可以消除掉两个字符。  
        综上所述，仅当有一个串的长度为 $1$ 且另一个串的长度 $>4$ 时才能使用特殊操作。  
        
2. 两个字符串首字母不相同。  
    + 普通操作：  
        现在我们面临的是一个形如 $\texttt{ababa\ldots}$ 和一个形如 $\texttt{babab\ldots}$ 的字符串，显然我们只要交换一个串开头的 $a$ 和另一个串开头的 $b$，就可以消除掉两个字符。  
    + 更优操作：  
        我们发现当有一个串的长度为 $1$ 时，使用普通操作只能消除掉一个字符，操作次数为另一个串的长度减 $1$。发现这样效率实在是低下，有没有什么优化方法呢？  
        当然有，考虑交换较长串开头的前三个字符和较短串开头的第一个字符。虽然这样依然只能消除掉两个字符，但是关键在于：它**平衡**了两个串的长度，使得只能用普通操作消除一个字符的情况出现得更少。  
        当然，仅当有一个串长度 $>4$ 时才可使用更优操作。  

在具体代码实现中，如果一次操作涉及的两串前缀长度不同，则钦定较长串涉及的前缀更长，这也是平衡两串长度的体现。比方说 $\texttt{abab}$ 和 $\texttt{ababab}$，变成 $\texttt{ab}$ 和 $\texttt{ababab}$ 显然在后续操作中更劣。  

笔者不敢保证已经列出所有情况，但依此写出的代码可以通过数据更全的 [AB-Strings](https://www.luogu.com.cn/problem/CF1012D)，如果有数据可以 hack，欢迎提出。  

至于代码具体实现，笔者使用了两个栈来分别维护两个字符串，所以倒序压缩字符串并加入栈中。不过使用 vector 也是可以的。  
具体细节看代码吧，虽然比别的要长一些，但细节不太多。  

## 代码  
此代码略有压行，还请见谅。  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node{
	int op,num;
	node(int _op=0,int _num=0){
		op=_op;num=_num;
	}
};
char a[N],b[N];
stack <node> st[2];
vector <node> ans;
void split(char *s,int op){
	for(int n=strlen(s+1),i=n,num=1;i>=1;i--){
		if(s[i]==s[i-1]) num++;
		else st[op].push({s[i]-'a',num}),num=1;
	}
}
inline node gtop(int op){
	node res=st[op].top();st[op].pop();
	return res;
}
void insert(int op,node &x){
	if(st[op].size()) x.num+=gtop(op).num;
	st[op].push(x);
}
#define add(x,y) insert(from,y);insert(to,x)
#define addans(x,y) ans.emplace_back((from?y:x),(to?y:x))
void merge(int from,int to){
	if(st[from].size()>4&&st[to].size()==1){
		node a=gtop(from),b=gtop(from),c=gtop(from);
		addans(a.num+b.num+c.num,0);
		insert(to,c);st[to].push(b);
		st[to].push(a);
	}
	else if(st[from].size()>3){
		node x=gtop(from),y=gtop(from),z=gtop(to);
		addans(x.num+y.num,z.num);add(y,z);
		st[to].push(x);
	}
	else{
		node x=gtop(from),y=gtop(to);
		addans(x.num,0);y.num+=x.num;
		st[to].push(y);
	}
}
void exchange(int from,int to){
	if(st[from].size()>4){
		node a=gtop(from),b=gtop(from),c=gtop(from),d=gtop(to);
		addans(a.num+b.num+c.num,d.num);add(c,d);
		st[to].push(b);st[to].push(a);
	}
	else{
		node x=gtop(from),y=gtop(to);
		addans(x.num,y.num);add(x,y);
	}
}
#define get(x,op) cin>>(x+1);split(x,op)
#define solve(function)\
	if(st[0].size()>=st[1].size()) function(0,1);\
	else function(1,0);
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	get(a,0);get(b,1);
	while(st[0].size()>1||st[1].size()>1){
		if(st[0].top().op==st[1].top().op)
			solve(merge)
		else solve(exchange)
	}
	cout<<ans.size()<<'\n';
	for(auto x:ans) cout<<x.op<<' '<<x.num<<'\n';
	return 0;
}
```

---

## 作者：flora715 (赞：2)

详见 https://img-blog.csdn.net/20180828144742579?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Zsb3JhNzE1/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70 qwq

（1）首先，连续的相同字符显然可以合并，直接减到只剩一个。

1.两串开头相同。分别取偶数长度前缀和奇数长度前缀交换。字符串长度缩减：2 。

2.两串开头不同。各取一个奇数长度前缀并交换。字符串长度缩减：2 。

（2）什么时候会使字符串长度缩减速度下降？

将S 、T中较长的称为A，较短的称为B，将 A 的开头字符设为 0，另一种字符设为 1 。

列举缩减速率变慢的情况（需要尽量避免）：

1.
A = 010101……
B = 0

方法：① 在 A 中选取长度为奇数的前缀，接到 B 上。

② 把 B 接到 A 上。 缩减： 1。

2.

A = 01    
B = 01
 
 缩减： 1。

3.

A = 010101……

B = 1

方法：① 在 A 中选偶数长度的前缀，接到 B 上。

② 在 A 中取奇数长度的前缀，与 B 交换。
缩减： 1。

（ " 将 X 的某某前缀 接到 Y 上 " 表示将 X 的某某前缀与 Y 的长度为 0 的前缀交换。）

避免缩减速率减缓、粗略的方法： 

每次操作尽量使得操作完毕后两个串的长度近似。

（这样使得串的长度尽量不会到 1 ）

对于 第 1、2 种情况，将 B 的开头与 A 的长度为奇数的前缀交换，并使得交换后长度近似。

对于 第 3 种情况，采用 任意一种方法，并使得交换后长度近似。两种方法效果相同。

对于两种基本情况，可以在短串只取开头一个，长串决策一下截取前缀的长度，使得交换后长度近似。

于是剩下的东西只需要读入的时候压缩一下，以及用链表维护一下字符串，分类讨论做决策。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;            

/*【F.AB-Strings】
有两个只含字符'a'、'b'的字符串。一次操作是指交换这两个字符串的可空前缀。
问：使得每个串内只包含一种字符最少的操作数。要求输出方案。 */

const int N=1000005;
int c[N],v[N],Next[N],cnt_node=0;
int L=0,R=1,len[2],head[2],n=0,ans[N][2];
char s1[N],s2[N];

int new_node(int color,int tot,int nxt){
    cnt_node++,c[cnt_node]=color;
    v[cnt_node]=tot,Next[cnt_node]=nxt;
    return cnt_node;
}

void build(int f,char s[]){
    int n=strlen(s+1),p=new_node(s[1]-'a',1,0);
    head[f]=p,len[f]=1;
    for(int i=2;i<=n;i++)
        if(s[i]==s[i-1]) v[p]++;
        else p=Next[p]=new_node(s[i]-'a',1,0),len[f]++;
}

int func0(int x,int a,int b){
    return abs((a-2*x-1)-(b+2*x));
}

int func1(int x,int a,int b){
    return abs((a-2*x)-(b+2*x-2));
}

int func2(int x,int a,int b){
    return abs((a-2*x-1)-(b+2*x-1));
}

int Get_len(int f){
    int cnt=0;
    for (int p=head[f];p;p=Next[p])
        cnt++;
    return cnt;
}

void New_ans(int Lv,int Rv){
    n++;
    ans[n][L]=Lv,ans[n][R]=Rv;
}

int main(){
    scanf("%s%s",s1+1,s2+1);
    build(0,s1),build(1,s2);
    while (max(len[L],len[R])>1){
        if (len[L]<len[R])
            swap(L,R);
        if (c[head[L]]==c[head[R]]&&len[R]>1&&len[L]>2){
            int a=len[L],b=len[R],x1=(a-b+2)/4,x2=x1+1;
            int x=max(1,min(func1(x1,a,b)<=func1(x2,a,b)?x1:x2,a/2));
            int tot=v[head[L]],p=head[L];
            for (int i=1;i<=x*2-1;i++)
                p=Next[p],tot+=v[p];
            New_ans(tot,v[head[R]]);
            int hL=head[L],hR=head[R];
            v[head[L]=Next[p]]+=v[hR];
            head[R]=hL;
            Next[p]=Next[Next[hR]];
            v[p]+=v[Next[hR]];
            len[L]-=x*2,len[R]+=x*2-2;
            continue;
        }
        else if (c[head[L]]==c[head[R]]){
            int a=len[L],b=len[R],x1=(a-b-1)/4,x2=x1+1;
            int x=min(func0(x1,a,b)<=func0(x2,a,b)?x1:x2,(a-1)/2);
            int tot=v[head[L]],p=head[L];
            for (int i=1;i<=x*2;i++)
                p=Next[p],tot+=v[p];
            New_ans(tot,0);
            swap(head[R],head[L]);
            swap(Next[p],head[L]);
            v[p]+=v[Next[p]];
            Next[p]=Next[Next[p]];
            len[L]=(len[L]<3)?(Get_len(L)):(len[L]-(x*2+1));
            len[R]=(len[R]<3)?(Get_len(R)):(len[R]+(x*2));
        }
        else {
            int a=len[L],b=len[R],x1=(a-b-1)/4,x2=x1+1;
            int x=min(func2(x1,a,b)<=func2(x2,a,b)?x1:x2,(a-1)/2);
            int tot=v[head[L]],p=head[L];
            for (int i=1;i<=x*2;i++)
                p=Next[p],tot+=v[p];
            New_ans(tot,v[head[R]]);
            v[head[R]]+=v[Next[p]];
            v[p]+=v[Next[head[R]]];
            swap(Next[head[R]],Next[p]);
            Next[head[R]]=Next[Next[head[R]]];
            Next[p]=Next[Next[p]];
            swap(head[L],head[R]);
            len[L]=(len[L]<3)?(Get_len(L)):(len[L]-(x*2+1));
            len[R]=(len[R]<3)?(Get_len(R)):(len[R]+(x*2-1));
        }
    }
    printf("%d\n",n);
    for (int i=1;i<=n;i++)
        printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}
```

---

## 作者：FFTotoro (赞：0)

考虑到一个简单的性质：如果一个串中有连续的两个相同的字符，那么可以将它们视为一个字符；于是最后两个串都形如 $\texttt{abab}\ldots\texttt{abab}$，我们的目标是让两个串变为一个 $\texttt{a}$ 一个 $\texttt{b}$。

接着分类讨论，对于两个字符串首字母相同的情况（不妨设为 $\texttt{a}$），最优的做法是选择一个串的 $\texttt{ab}$ 与另一个串的 $\texttt{a}$ 交换；这样可以让总长度减少 $2$；由此可得应在其中一个字符串中选择长度为奇数的前缀，另一个字符串中选择长度为偶数的前缀；类似的，如果首字母不同，那么应选择两个长度为奇数的前缀。

对于边界情况：其中一个字符串长度为 $1$，直接暴力做，此时每次只能减少一个字符；两个字符串长度均为 $2$，此时也是每次只能减少一个字符。对于这些情况，字符串的长度可能都很小——于是在上面的操作中可以尽量让两个字符串的长度平均。

参考代码（GNU C++17）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
vector<pii> q[2],r;
inline void add(int p,pii x){
  if(!q[p].empty()&&q[p].back().first==x.first)
    q[p].back().second+=x.second;
  else q[p].emplace_back(x);
}
inline void op(int x){
  pii a=q[0].back(); q[0].pop_back();
  int c=0;
  for(int i=x;i;i--){
    pii y=q[1][q[1].size()-i];
    add(0,y),c+=y.second;
  }
  r.emplace_back(a.second,c);
  while(x--)q[1].pop_back();
  add(1,a);
}
int main(){
  ios::sync_with_stdio(false);
  string s,t; bool f=false; cin>>s>>t;
  for(int i=s.length()-1;~i;i--)
    add(0,make_pair(s[i]&1,1));
  for(int i=t.length()-1;~i;i--)
    add(1,make_pair(t[i]&1,1));
  if(q[0].size()>q[1].size())
    swap(q[0],q[1]),f=true;
  if(q[0].back().first==q[1].back().first){
    if((q[1].size()-q[0].size()&3)==3)
      op(q[1].size()-q[0].size()+1>>1);
    add(0,make_pair(!q[0].back().first,0));
    op(q[1].size()-q[0].size()+1>>2<<1|1);
  }
  else if(q[1].size()-q[0].size()>2)
    op(q[1].size()-q[0].size()+1>>2<<1|1);
  while(q[0].size()>1||q[1].size()>1)op(1);
  if(f)for(auto &[x,y]:r)swap(x,y);
  cout<<r.size()<<endl;
  for(auto [x,y]:r)cout<<x<<' '<<y<<'\n';
  return 0;
}
```

---

