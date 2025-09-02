# Least Cost Bracket Sequence

## 题目描述

This is yet another problem on regular bracket sequences.

A bracket sequence is called regular, if by inserting "+" and "1" into it we get a correct mathematical expression. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not. You have a pattern of a bracket sequence that consists of characters "(", ")" and "?". You have to replace each character "?" with a bracket so, that you get a regular bracket sequence.

For each character "?" the cost of its replacement with "(" and ")" is given. Among all the possible variants your should choose the cheapest.

## 样例 #1

### 输入

```
(??)
1 2
2 8
```

### 输出

```
4
()()
```

# 题解

## 作者：Loner_Knowledge (赞：29)

这是一道贪心题

---

题意是对于一个字符串，序列里面有`(`、`)`和`?`，对于`?`可以以一定的代价将其替换为`(`或`)`，如果括号是匹配的，求最小代价。


首先`)`肯定匹配最近的没有匹配的`(`，我们可以用一个计数器`mark`记录`(`的数量，如果遇到`)`则自减1代表匹配一对。


先考虑**匹配**，设想所有的`?`都是`)`。如果`mark`在遍历时小于零代表没有足够的`(`来匹配`)`，于是我们到前面去找由`?`变成的`)`变为`(`来填补`mark`的空缺，并将`mark`加上2，如果找不到说明字符串不合法。如果在遍历完成后`mark`不为0，那么说明这个字符串不合法。


再考虑**代价最小**，匹配时设想所有的`?`都是`)`，于是在开始时的代价为所有`?`替换为`)`的代价之和。如果`mark`在遍历时小于零时进行替换，考虑到**代价最小**，应该在之前寻找`-b+a`（减去替换为`)`的代价加上替换为`(`的代价）最小的`?`。


经由上面的分析，我们需要一个以`-b+a`降序排列，同时存储`?`位置的优先队列，每次遇到`?`入队一个，`mark`小于零时出队一个。


注意**数据范围**，答案要用$long\ long$，$long\ long$在`CodeForces`要用`"%I64d"`输出。（当然如果你用`cout`另说）


```cpp
#include<cstdio>
#include<queue>
using namespace std;
struct Data {        //优先队列的元素
    int delta;        //这是-b+a
    char *p;        //这是?的位置
    bool operator <(const Data &b)const {    //重定义比较运算符进行降序排列
        return delta>b.delta;
    }
}t;
priority_queue<Data> q;        //优先队列
char s[50002];
int main() {
    int mark=0;            //计数器
    long long ans=0;
    scanf("%s",s);
    for(int i=0,a,b;s[i]&&ans!=-1;++i) {
        if(s[i]=='(')    //计数器加1
            ++mark;
        else {
            --mark;        //计数器减1，'?'也一样，因为开始时设想所有的'?'都是')'
            if(s[i]=='?') {
                scanf("%d%d",&a,&b);
                t.delta=a-b;
                t.p=s+i;    //给指针赋值
                q.push(t);    //入队
                s[i]=')';
                ans+=b;
            }
        }
        if(mark<0) {        //此时要到前面去找'?'
            if(q.empty())
                ans=-1;        //如果队列为空，那么字符串不合法
            if(ans!=-1) {
                mark+=2;
                t=q.top();    //取队尾元素并替换
                q.pop();
                *t.p='(';
                ans+=t.delta;
            }
        }
    }
    if(mark)    //判断计数器是否为0，否则字符串不合法
        ans=-1;
    printf("%I64d",ans);    //用%I64d
    if(ans!=-1)
        printf("\n%s",s);
    return 0;
}
```

---

---

## 作者：little_sheep917 (赞：9)

这一题是一个贪心的题目。
先把字符串中的问号都换成右括号，扫过去，如果左括号比右括号多（因为在任意一个位置上，它前面的左括号都不可能比右括号多，在最后一位要相等），则在前面所有待定（原是有问号，但现在改成右括号的位子）上找左右差值最小的，换掉（因为只要在一个位置上左括号右括号相等，就是合法的）。

```cpp
#include<bits/stdc++.h>
using namespace std;

priority_queue <pair<int,int> > Q;
int a[50010],b[50010];
string s;
string str;

int main(){
	cin>>s;
	int len=0;
	int l=0,r=0;
	str=s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='(') l++;
		else if(s[i]==')') r++;
		if(s[i]=='?'){
			str[i]=')';
			cin>>a[i]>>b[i];
			len++;	
		}
	}
	if(s[0]==')'||s[s.size()-1]=='('){
		cout<<"-1"<<endl;
		return 0;
	}
	if(abs(l-r)>len){
		cout<<"-1";
		return 0;
	}
	long long ans=0;
	l=0,r=0;
	if(s[0]!='(') str[0]='(';
	l++;
	for(int i=1;i<str.size();i++){
		if(s[i]=='?') Q.push(make_pair(b[i]-a[i],i)); 
		if(str[i]=='(') l++;
		if(str[i]==')') r++;
		if(r>l){
			pair<int,int> p=Q.top();
			Q.pop();
			int x=p.second;
			r--;l++;
			str[x]='(';
		}
	}
	if(l!=r){
		cout<<"-1";
		return 0;
	}
	if(str[0]!='('||str[str.size()-1]!=')'){
		cout<<"-1";
		return 0;
	}
	for(int i=0;i<str.size();i++){
		if(s[i]=='?'){
			if(str[i]=='(') ans+=a[i];
			if(str[i]==')') ans+=b[i];
		}
	}
	cout<<ans<<endl;
	cout<<str<<endl;
	return 0;
}
```


---

## 作者：ahawzlc (赞：5)

用堆来实现贪心

----

读入字符串序列 s1，为了操作方便，我们把这个序列备份至 s2 。

扫描字符串序列 s1 ，统计左括号和右括号的个数，如果遇到```?``` ， 先统一化成右括号，并保存在 s2 。

贪 心 开 始。重新扫描 s2，统计左括号右括号的个数，如果当前情况下右括号数比左括号数大，说明没有匹配好，那么我们需要从前面找一个花费最小的```?```来替换。考虑替换的代价，因为原来默认化成```)```，要想化成```(```，需要花费$a[i]-b[i]$的代价，那么我们就可以用小根堆实现找出价值最小的```?```，替换成```(```，并保存在 s2 中。

最后再扫描 s2 ，统计```?```改成左右括号的代价和，输出答案，同时 s2 ，就是可行的答案。

最后分析一下```-1```的情况：

1. 原字符串开头是```)```或结尾是```(```，肯定没法找到另一半，无解。
2. ```?```的个数比左右括号个数差的绝对值小，无解。
3. 在贪心过后发现左右括号数不匹配，即出现奇偶数矛盾关系，无解

（其实还有一个点，因为```c++```默认的```priority_queue```是大根堆，所以存的时候存负数即$b[i]-a[i]$，免去重载运算符的麻烦 ~~（人类的本质）~~。

``` cpp
#include<bits/stdc++.h>
#define int long long
#define pi pair<int,int>
#define F first
#define S second
#define mp make_pair
#define ed; puts("-1");return 0;//懒惰直接结束
using namespace std;
string s1,s2;
int l,r,a[50004],b[50004],ans;
priority_queue<pi> q;
signed main() {
	cin>>s1;
	s2=s1;
	int len1=s1.size(),len2=0,sum=0;
	if(s1[0]==')'||s1[len1-1]=='(') {
		ed;
	}
	for(int i=0;i<len1;i++) {
		if(s1[i]=='(') ++l;
		else if(s1[i]==')') ++r;
		else {
			s2[i]=')';
			cin>>a[i]>>b[i];
			++sum;
		}
	}
	if(l-r>sum||r-l>sum) {
		ed;
	} 
	l=r=0;
	if(s1[0]=='?') s2[0]='(';
	++l;
	for(int i=1;i<s2.size();i++) {
		if(s1[i]=='?') q.push(mp(b[i]-a[i],i));
		if(s2[i]=='(') l++;
		else if(s2[i]==')') r++;
		if(r>l) {
			s2[q.top().S]='(';
			--r;
			++l;
			q.pop();
		}
	}
	if(r-l) {
		ed;
	}
	for(int i=0;i<s2.size();i++) {
		if(s1[i]=='?') {
			if(s2[i]=='(') ans+=a[i];
			else ans+=b[i];
		}
	}
	cout<<ans<<endl;
	cout<<s2;
	return 0;
}
```

---

## 作者：DarthVictor (赞：4)

# 题目
[原题地址](https://www.luogu.com.cn/problem/CF3D)
# 解说
~~被自己选的题卡了两节课……~~

首先，问号的状态会影响能否匹配，那么我们不妨就先让所有问号都为右括号，什么时候右括号太多了就把前面的问号改成左括号即可。

那么前面有多个问号的时候我们应该选择哪个？显然我们应该运用贪心思想，哪个问号改变后为我们减少的花费多我们就选哪个，这就需要我们维护一个优先队列，排序的依据是$-b+a$的大小（$b$是该问号改为右括号的价值，$a$是该问号改为左括号的价值）。我们每遇到一个问号就把它推进队列里，以备之后选用。每选用一个括号就把它改为左括号，同时修改我们的$answer$和计数器。

当然，在这个过程中我们还需要判断能否匹配。不匹配的情况总共两种：

1.发现右括号比左括号还多后前面却没有问号用来抵消

2.到最后发现左括号比右括号和问号的和还多

这时输出$-1$即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=50000+3;
typedef long long ll;
char s[maxn];
struct inf{//记录问号的位置和价值
	int loc;
	ll a,b;
	inf(int d,ll e,ll f){
		loc=d; a=e; b=f;
	}
	bool operator<(const inf &x)const{//排序依据
		return -b+a>-x.b+x.a;
	}
};
priority_queue<inf> q;
int main(){
	scanf("%s",s);
	int len=strlen(s),js=0;//js为计数器
	ll ans=0;
	for(int i=0;i<len;i++){
		if(s[i]=='(') js++;
		if(s[i]==')') js--;
		if(s[i]=='?'){
			js--;
			ll a,b;
			scanf("%lld%lld",&a,&b);
			q.push(inf(i,a,b));
			ans+=b;//默认为右括号
			s[i]=')';
		}
		if(js<0){//右括号太多了
			if(q.empty()){//解说里输出-1的情况一
				printf("-1");
				return 0;
			}
			inf k=q.top();
			ans=ans-k.b+k.a;//改为左括号
			js+=2;
			q.pop();
			s[k.loc]='(';
		}
	}
	if(js!=0){//解说里输出-1的情况二
		printf("-1");
		return 0;
	}
	printf("%lld\n",ans);
	printf("%s",s);
	return 0;
} 
```

幸甚至哉，歌以咏志。

---

## 作者：Otomachi_Una_ (赞：2)

一道很喵喵的妙妙题

## 题目简述

- 给你一个括号序列 $s$，当中有一些 `?`。
- 把这些 `?` 换成 `(` 有 $a_i$ 的价值，换成 `)` 有 $b_i$ 的价值。求总价值的最小值。
- $|s|\leq 5\times 10^4$。

## 解题思路

一道喵喵贪心题。

对于每一个 `?` 我们先把它当做 `)` 丢进原序列。如果发现某个位置不合法就把从 `)` 修改到 `(` 代价差最小的进行更换。

把一个 `?` 修改的时候只要丢到一个小根堆里面就好了，实现非常简单。

## 参考代码

```cpp
#include<iostream>
#include<queue>
using namespace std;
#define ll long long
priority_queue <pair<int,int> > q;
string s;
int x,y;
ll ans=0,les=0;
int main(){
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='(') les++;
		else if(s[i]==')') les--;
		else{
			les--;
			s[i]=')';
			cin>>x>>y;
			q.push(make_pair(-(x-y),i));
			ans+=y;
		} 
		if(les<0&&q.empty())
			break;
		if(les<0){
			int k=-q.top().first,p=q.top().second;
			q.pop(); 
			les+=2;
			s[p]='(';
			ans+=k;
		}
	}
	if(les!=0)
		cout<<"-1";
	else
		cout<<ans<<endl<<s;
}
```


---

## 作者：ncwzdlsd (赞：1)

~~看到带括号的题，我们的第一反应就是开个栈QwQ~~

首先需要知道一切一切的前提是括号序列合法，所以不能单纯的浅浅贪心求出代价最小的放法。

对于一个合法的序列来说，左右括号的数量一定相等，并且在当前位置，左括号的数量一定不小于右括号的数量，于是可以开一个栈来存左括号，遇到右括号就弹栈，栈空则不合法。

然而其实我们并不需要一整个栈，只需要留下栈顶即可，因为栈中元素相同。

然后就可以考虑贪心了，扫描整个序列：

如果是问号，就替换成右括号，然后判断能否配对，显然，这样的想法是正确的，因为左括号的数量一定不小于右括号的数量，所以在右括号数量多于左括号时，取出左括号代价最少的那个即可。

于是乎，每一步都保证了当前括号序列合法且最优，贪心的合理性也显而易见。

代码主体如下（要自己思考哟qwq）：
```cpp
	for(int i=0;i<l;i++)
	{
		if(s[i]=='(') top++;
		else 
		{
			top--;
			if(s[i]=='?')
			{
				int a,b;
				cin>>a>>b;
				q.push(node(a-b,i));
				s[i]=')';
				ans+=b;
			}
		}
		if(top<0)
		{
			if(q.empty())
				return printf("-1\n"),0;
			top+=2;
			node u=q.top();q.pop();
			s[u.id]='(';
			ans+=u.val;
		}
	}
```

---

## 作者：linaonao (赞：1)

## 分析
刚在网校看了贪心算法，以下为这道题的分析：

首先先只考虑括号匹配，就是用 *)* 匹配 *(* ，所以我们首先贪心的将所有 *?* 替换为 *)*,若两者不匹配则将某些换为 *(* 。

但题目还有替换代价，所以我们维护一个堆，以*val_a-val_b*为关键维护一个 *?* 的堆（val_a为改为 *(* 的代价，val_b为 *）* 的代价），当不匹配时，去除堆顶的替换。
## 注意点
注意：

- 优先队列默认大顶堆，多以重置$<$时要将val_a-val_b小的当做大的。

- 要即使更改字符串中的符号。

有两种不匹配情况：

- 括号数不匹配时队列已空

- 按照贪心策略匹配完时括号时不匹配

## 代码
贴代码：

~~~cpp

#include<bits/stdc++.h>
#define int long long
template<typename T>inline void read(T &x){
	T f=0;x=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f|=ch=='-';
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    x=f?-x:x;
}
template<typename T>inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
using namespace std;
struct node{
	int loc,val_a,val_b;
	bool operator<(const node &x)const{
		return val_a-val_b>x.val_a-x.val_b;
	}
};priority_queue<node>q; 
char s[50005]; 
int key,sum;
signed main(){
	scanf("%s",s); 
	int len=strlen(s);
	for(int i=0;i<len;++i){
		if(s[i]=='('){
			++key;
		}else if(s[i]==')'){
			--key; 
		}else if(s[i]=='?'){
			int a,b; read(a),read(b);
			q.push((node){i,a,b});
			sum+=b; s[i]=')';
			--key;
		}
		if(key<0){
			if(q.empty()){
				cout<<-1; return 0;
			}
			node t=q.top(); q.pop();
			sum+=t.val_a-t.val_b; s[t.loc]='(';
			key+=2;
		}
	} 
	if(key!=0){
		cout<<-1; return 0;
	}
	write(sum); putchar('\n');
	printf("%s",s);
	return 0;
} 

~~~

---

## 作者：hzoi_liuchang (赞：1)

## 分析

一句话题意：:给一个序列，序列里面会有左括号、问号、右括号。对于一个`?`而言，可以将其替换为一个`(`，也可以替换成一个`)`，但是都有相应的代价。问：如何替换使得代价最小。前提是替换之后的序列中，括号是匹配的。如果不能替换为一个括号匹配的序列则输出`-1`。

这道题要用到贪心的思想，我们可以先遍历一遍，把所有的问号都改成右括号

然后我们再从左到右进行匹配，同时记录一下左括号的个数$cnt$，如果当前遍历到了一个右括号，那么$cnt$-- 代表有一对括号匹配成功

如果$cnt<0$那么我们就从之前由问号变成的右括号中找一个，把它变成左括号，同时把$cnt+2$

那么我们找哪一个呢？肯定是找变成左括号的价值减去变成右括号的价值最小的那一个，我们可以用一个优先队列维护

要是找不到就说明匹配失败，直接输出$-1$

最后循环结束的时候如果左括号的个数不为0，也要输出$-1$

否则就输出你记录的字符串

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
char s[maxn],s2[maxn];
struct asd{
    int lef,rig,num;
    asd(int aa=0,int bb=0,int cc=0){
        lef=aa,rig=bb,num=cc;
    }
    bool operator < (const asd& A) const {
        return (lef-rig)>(A.lef-A.rig);
    }
};
priority_queue<asd> q;
int main(){
    scanf("%s",s);
    int n=strlen(s);
    int cnt=0;
    long long ans=0;
    for(int i=0;i<n;i++){
        if(s[i]=='('){
            cnt++;
            s2[i]='(';
        }
        else{
            cnt--;
            s2[i]=')';
            if(s[i]=='?'){
                int aa,bb;
                scanf("%d%d",&aa,&bb);
                ans+=(long long)bb;
                q.push(asd(aa,bb,i));
            }
            if(cnt<0){
                if(q.empty()){
                    printf("-1\n");
                    return 0;
                }
                cnt+=2;
                int ll=q.top().lef,rr=q.top().rig,id=q.top().num;
                s2[id]='(';
                q.pop();
                ans+=(long long)(ll-rr);
            }
        } 
    }
    if(cnt!=0) printf("-1\n");
    else printf("%lld\n%s\n",ans,s2);
    return 0;
}

```



---

## 作者：bsdsdb (赞：1)

题意：给一个字符集为 $\{\texttt(,\texttt?,\texttt)\}$ 的偶数长度字符串 $s$，每个问号 $s_i$ 有将其修改为左括号的代价 $l_i$ 和修改为右括号的代价 $r_i$。你需要用最少代价将 $s$ 改成一个合法括号序列 $s'$。输出代价和 $s‘$ 或报告无解。

先上括号序列的经典套路：`(` 视作 $+1$，`)` 视作 $-1$，序列合法当且仅当所有前缀和非负且整体和为 $0$。再上一个括号序列经典（？）贪心策略：先把所有的改成 `(`，如果最小前缀和为负则无解，然后在保证可能合法（即最小前缀和非负）的情况下一个一个改成 `)`，如果最后整体和不为 $0$ 则无解，否则输出答案。最小前缀和可用线段树维护。对于本题来说，策略就是将括号按照 $r_i-l_i$ 大到小排序，如果能改就改成 `)`。

接下来是策略的正确性证明。记我们改出来的方案为 $a$，随便一种另外的方案为 $t$。一定能找到最左边的 $p$ 使得 $a_p=\texttt),t_p=\texttt($，以及最左边的 $q$ 使得 $a_q=\texttt(,t_q=\texttt)$。首先，如果 $t_p$ 和 $t_q$ 能互换，根据我们的贪心策略，这一定是不劣的。如果 $q<p$，说明我们需要把 $t$ 里的一个 `)...(` 改成 `(...)`，改完之后每个前缀和都不减少，一定合法。

否则，$p<q$，如下图，因为 $p$ 是最左边的所以 $t_{[1,p)}=a_{[1,p)}$，令 $S(q)$ 表示 $q$ 的整体和，则 $S(t_{[1,p]})=S(a_{[1,p]})-S(a_p)+S(t_p)=S(a_{[1,p]})+2$。因为 $q$ 也是最左边的，所以如果有 $r\in(p,q)$ 满足 $a_r\neq t_r$ 那一定是 $a_r=\texttt),t_r=\texttt($，所以有了这个证明最关键（？）的结论：$\forall i\in(p,q):S(t_{(p,i]})\ge S(a_{(p,i]})$。可以推出 $\forall i\in(p,q):S(t_{[1,i]})=S(t_{[1,p]})+S(t_{(p,i]})\ge2+S(a_{[1,p]})+S(a_{(p,i]})\ge2$。这么改之后，对于任意的 $i\in[p,q)$，$S(t_{[1,i]})$ 都会减少 $2$，但是原本就 $\ge 2$，所以这么改是合法的。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/1rd74yaq)

注意不能直接说「因为 $a$ 合法，所以 $t$ 这么一改一定合法」，因为 $t$ 和 $a$ 可能还有其他不同，这么证明不严谨。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace modint {
    const ll MOD = 1;
    struct modint {
        ll val, mod;
        void setmod(ll x) {
            mod = x;
        }
        explicit operator ll() {
            return val;
        }
        modint() {
            val = 0, mod = MOD;
        }
        modint(ll v, ll m = MOD) {
            if (m == 1) {
                cus_throw("init modint without mod");
            }
            v %= m;
            if (v < 0) {
                v += m;
            }
            val = v;
            mod = m;
        }
    };
    #define chkmod(x, y) if (x.mod != y.mod) cus_throw("mod isn't the same")
    modint operator+(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val + y.val, x.mod);
    }
    modint operator-(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val - y.val, x.mod);
    }
    modint operator*(modint x, modint y) {
        chkmod(x, y);
        return modint(__int128(1) * x.val * y.val, x.mod);
    }
    modint qpow(modint x, ll y) {
        if (!y) {
            return modint(1, x.mod);
        } else if (y & 1) {
            return x * qpow(x, y ^ 1);
        } else {
            return qpow(x * x, y >> 1);
        }
    }
    modint inv(modint x) {
        return qpow(x, x.mod - 2);
    }
    modint operator/(modint x, modint y) {
        chkmod(x, y);
        if (ll(y) == 0) {
            cus_throw("modint divide by 0");
        }
        return x * inv(y);
    }
    modint operator+=(modint& x, modint y) {
        return x = x + y;
    }
    modint operator-=(modint& x, modint y) {
        return x = x - y;
    }
    modint operator*=(modint& x, modint y) {
        return x = x * y;
    }
    modint operator/=(modint& x, modint y) {
        return x = x / y;
    }
    bool operator==(modint x, modint y) {
        chkmod(x, y);
        return x.val == y.val;
    }
}

const ll MAXN = 5e4 + 5;

string s;
ll lb[MAXN], rb[MAXN], n, iq[MAXN], qc;

namespace segtree {
    struct sec {
        ll sum = 0, mnp = inf;
        explicit operator ll() {
            return mnp;
        }
    };
    sec operator+(sec x, sec y) {
        sec r;
        r.sum = x.sum + y.sum;
        r.mnp = min(x.mnp, x.sum + y.mnp);
        return r;
    }
    struct segtree {
        ll size;
        sec val[MAXN << 2];
        #define l(x) (x<<1)
        #define r(x) ((x<<1)|1)
        #define mid ((lx+rx)>>1)
        #define lpr l(x),lx,mid
        #define rpr r(x),mid+1,rx
        #define prl ll x, ll lx, ll rx
        void init(ll x) {
            size = 1;
            while (size < x) size <<= 1;
        }
        void psu(ll x) {
            val[x] = val[l(x)] + val[r(x)];
        }
        void mdf(ll p, ll v, prl) {
            if (p < lx || rx < p) {
                return;
            }
            if (p == lx && lx == rx) {
                val[x].mnp = val[x].sum = v;
                return;
            }
            mdf(p, v, lpr), mdf(p, v, rpr), psu(x);
        }
        void mdf(ll p, ll v) {
            mdf(p, v, 1, 1, size);
        }
        sec qry(ll l, ll r, prl) {
            if (r < lx || rx < l) {
                return sec();;
            }
            if (l <= lx && rx <= r) {
                return val[x];
            }
            return qry(l, r, lpr) + qry(l, r, rpr);
        }
        sec qry(ll l, ll r) {
            return qry(l, r, 1, 1, size);
        }
    } st;
}

map<char, ll> cv;
ll ans = 0;

int main() {
    cv['('] = cv['?'] = 1;
    cv[')'] = -1;
    read(s);
    n = s.size();
    for (ll i = 0; i < n; ++i) {
        if (s[i] == '?') {
            iq[++qc] = i + 1;
        }
    }
    s = '.' + s;
    for (ll i = 1; i <= qc; ++i) {
        read(lb[iq[i]]), read(rb[iq[i]]);
    }
    segtree::st.init(n);
    for (ll i = 1; i <= n; ++i) {
        segtree::st.mdf(i, cv[s[i]]);
    }
    if (ll(segtree::st.qry(1, n)) < 0) {
        puts("-1");
        return 0;
    }
    vector<ll> a;
    for (ll i = 1; i <= n; ++i) {
        if (s[i] == '?') a.empb(i);
    }
    sort(a.begin(), a.end(), [](ll x, ll y)->bool {return mkp(rb[x] - lb[x], x) < mkp(rb[y] - lb[y], y);});
	for (ll i : a) {
        segtree::st.mdf(i, -1);
        if (ll(segtree::st.qry(1, n)) < 0) {
            segtree::st.mdf(i, 1);
            s[i] = '(';
            ans += lb[i];
        } else {
            s[i] = ')';
            ans += rb[i];
        }
    }
    ll pre = 0;
    for (char c : s) {
        pre += cv[c];
    }
    if (pre > 0) {
        puts("-1");
        return 0;
    }
    write(ans), enter(), puts(s.c_str() + 1);
    return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：Link_Cut_Y (赞：0)

### 题目大意

给定字符串 $S$，（$|S| \leq 5 \times 10 ^ 4$） 。字符串由 $\texttt{(}$，$\texttt{)}$ 和 $\texttt{?}$ 构成。其中 $\texttt{?}$ 表示当前点可以填左括号也可以填右括号。但是，填写左括号或者右括号都有相应的代价 $a, b$ 。

给出每个 $\texttt{?}$ 处填写左右括号的代价，问：将原字符串填写成为合法括号匹配所需的最小代价。

### 题目分析

贪心。

-------------

首先将原字符串的问号处全部填充成右括号。（一定填右括号！）

接下来我们考虑对于一个位置 $u$，如果 $u$ 前面的右括号比左括号多，那么必定要将其中一些右括号换成左括号。因为如果不替换，$u$ 前面一定有无法匹配的右括号。

那么贪心就出来了。我们每次找花费代价少的来替换。那么现在又两个问题：

1. 代价是什么？

	首先假设选择了第 $x$ 个括号进行替换。那么就需要将原来的代价 $b$ 变成现在的代价 $a$，多余花费为 $a - b$ ，我们要让这个代价尽可能小。
    
2. 怎样找到最小代价？

	考虑使用一个小根堆来维护当前点之前的所有代价，每次取出堆顶。
    
最后在来说一下无解的情况：

1. 如果开始时，字符串的第一个字符是 $\texttt{)}$ 或者最后一个字符是 $\texttt{(}$ ，则无解。

2. 如果匹配完成后，括号串不合法，则无解。（其实这里有别的方法，但是因为懒不想分类讨论，于是就暴力判断了。）

### CODE

```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 50010;

char s[N];
int n;
priority_queue<PII, vector<PII>, greater<PII>> q;
long long s1, s2, res;

bool check() {
	int top = 0;
	static int a[N];
	for (int i = 1; i <= n; i ++ ) {
		if (s[i] == '(') a[ ++ top] = i;
		else top -- ;
	}
	return top ? 0 : 1;
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	
	if (s[1] == ')' or s[n] == '(')
		return puts("-1"), 0;
	
	for (int i = 1; i <= n; i ++ ) {
		if (s[i] == '?') {
			int a, b;
			scanf("%d%d", &a, &b);
			s[i] = ')';
			q.push({a - b, i});
			res += b;
		}
		(s[i] == '(') ? s1 ++ : s2 ++ ;
		
		if (s2 > s1) {
			while (s2 > s1 && q.size()) {
				s2 -- , s1 ++ ;
				auto t = q.top();
				q.pop();
				int ver = t.second, w = t.first;
				s[ver] = '(', res += w;
			}
		}
	}
	
	if (!check()) return puts("-1"), 0;
	
	printf("%I64d\n", res);
	puts(s + 1);
	
	return 0;
}
```

---

## 作者：intel_core (赞：0)

先考虑什么是合法的括号序列。

设一个 $det$ ，如果碰到一个 `(` ，就 `det++` ，如果是 `)` ，就 `det--`。

那么一个括号序列合法当且仅当在任意未知的 $det$ 都满足 $det \ge0$

下面接着考虑怎么让代价最小。

因为要保证合法性，所以当遍历到一个位置的时候出现了 $det<0$ 的情况，我们就需要在当前位置的前面将一个 `?` 变成 `(`。

这个时候我们只需要取出来 $a_i-b_i$ 最小的就行。

具体来说，我们先假定每个 `?` 都被替换成了 `)` ，如果当前位置上的字符是 `?` ，我们将 $a_i-b_i$ 加入小根堆中。

每次 $det<0$ 时让当前答案加上堆顶权值，把堆顶元素 `pop` 掉，再 `det+=2`。

最后注意初始答案是所有 `?` 替换为 `)` 的权值之和。

时间复杂度： $O(n \log n)$ 。

---

## 作者：zrzring (赞：0)

[更好的阅读体验](http://zrzring.cn/index.php/archives/258)

> 给定一个带`?`的长度为$n$的括号串，第$i$个`?`变成`(`代价为$l_i$，变成`)`的代价为$r_i$，求将括号串全部`?`变成括号且括号串是合法的的最小代价

考虑贪心，为了保证合法，我们初始化所有`?`为`)`，然后碰到`(`不够的时候把前面的`)`变成`(`即可

堆优化每次找到前面变`)`为`(`最小代价的那个即可

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

#define int long long
#define mp(x, y) make_pair(x, y)

using namespace std;

void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}

const int N = 1e6 + 10, M = 2e6 + 10, inf = 1e9;

inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

int n, m, cnt, ans;

char ch[N];

priority_queue<pair<int, int> >q;

signed main() {
    scanf("%s", ch + 1); n = strlen(ch + 1);
    if (n % 2) {printf("-1"); return 0;}
    for (int i = 1, j = 0; i <= n; i++) {
        if (ch[i] == '(') cnt++;
        if (ch[i] == ')') cnt--;
        if (ch[i] == '?') {
            int l = read(), r = read(); cnt--; ans += r; ch[i] = ')'; q.push(mp(r - l, i));
        }
        if (cnt < 0) {
            if (q.empty()) {printf("-1"); return 0;}
            pair<int, int> t = q.top(); q.pop();
            ans -= t.first; ch[t.second] = '('; cnt = 1; 
        }
    }
    if (cnt) {printf("-1"); return 0;}
    printf("%lld\n", ans); printf("%s", ch + 1);
    return 0;
}
```

---

## 作者：Hexarhy (赞：0)

### Preface

括号匹配相关题目。太久没写这玩意儿导致写出来又长又慢……

### Solution

括号匹配一般都用前缀和来维护。而在本题，问号的出现是繁琐的，于是不妨将全部问号改为`)`，答案统计为 $\sum b_i$。

记`(`为 $1$，`)`为$-1$，前缀和为 $s_{i}$。遍历一遍字符串（为了方便，下表从 $1$ 开始）。

如果 $s_i<0$，则说明右括号太多了，需要一个左括号匹配。于是我们就在 $[1,i)$ 的范围内寻找**最划算**的`?`将其修改为`(`，更新答案即可。修改的时候，也维护一下前缀和。其中，**“最划算”** 的是指，$b_i-a_i$ 最大的一项。

寻找最划算的可以用优先队列维护。

另外，为了修改维护方便，笔者用了线段树而不是前缀和~~常数偏大~~。

至于`-1`，只需要保证从左往右右括号数目不超过左括号，从右往左左括号数目不超过右括号即可。

总的时间复杂度 $O(n\log n)$。

### Notice

- 为了方便，可以在字符串首加一个字符，使得从 $1$ 开始遍历。

- 访问堆顶时一定要判断是否为空，避免 RE。

### Code

虽然长，但是好写。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

typedef long long ll;
typedef const int cint;
const int MAXN=5e4+5;
string s;
int n;
bool f[MAXN];
int sum[MAXN];
ll ans;
struct node
{
	int a,b,id;
	bool operator<(const node x)const
	{
		if(b-a!=x.b-x.a)
		 return (b-a)<(x.b-x.a);//注意维护最划算的
		return id>x.id;
	}
}a[MAXN];
class segment_tree//模板
{
private:
	#define mid ((tree[cur].l+tree[cur].r)>>1)
	#define lson (mid<<1)
	#define rson (mid<<1|1)
	struct node
	{
		int l,r,val;
	}tree[MAXN<<2];//小细节
	void pushup(cint cur)
	{
		tree[cur].val=tree[lson].val+tree[rson].val;
	}
	inline int trans(const char ch)
	{
		if(ch=='(')	return 1;
		if(ch==')')	return -1;
		return 0;
	}
public:
	void build(cint cur,cint l,cint r)
	{
		tree[cur].l=l;tree[cur].r=r;
		if(l==r)
		{
			tree[cur].val=trans(s[l]);
			return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushup(cur);
	}
	void modify(cint cur,cint pos,const char ch)
	{
		if(tree[cur].l==pos && tree[cur].r==pos)
		{
			tree[cur].val=trans(ch);
			return;
		}
		if(pos<=mid)	modify(lson,pos,ch);
		else			modify(rson,pos,ch);
		pushup(cur);
	}
	int query(cint cur,cint l,cint r)
	{
		if(l<=tree[cur].l && tree[cur].r<=r)
		 return tree[cur].val;
		int res=0;
		if(l<=mid)	res+=query(lson,l,r);
		if(mid<r)	res+=query(rson,l,r);
		return res;
	}
	void clear(void)
	{
		memset(tree,0,sizeof(tree));
	}
}t;

void solve(void)
{
	for(int i=1;i<=n;i++)
	 ans+=a[i].b;
	priority_queue<node> q;
	for(int i=1;i<=n;i++)//全部修改为')'
	 if(s[i]=='?')
   {
	  f[i]=true;//标记问号位置
	  s[i]=')';
   }
	t.build(1,1,n);//先修改后建树
	for(int i=1;i<=n;i++)
	{
		if(f[i])//问号就入队
		 q.push(a[i]);
		if(!q.empty() && t.query(1,1,i)<0)//小心 RE
		{
			cint tmp=q.top().id;q.pop();
			s[tmp]='(';
			t.modify(1,tmp,'(');
			ans=ans-a[tmp].b+a[tmp].a;
		}
	}
}

void output(void)
{
	for(int i=1;i<=n;i++)
	 if(t.query(1,1,i)<0)
	 {
	  	cout<<-1<<endl;
	  	return;
	 }
	for(int i=n;i>=1;i--)
	 if(t.query(1,i,n)>0)
	 {
	 	cout<<-1<<endl;
	 	return;
	 }
	cout<<ans<<endl<<s<<endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>s;s=' '+s;
	n=s.size()-1;
	for(int i=1;i<=n;i++)
	 if(s[i]=='?')
	 {
	 	cin>>a[i].a>>a[i].b;
	 	a[i].id=i;
	 }
	solve();
	output();
	return 0;
}
```

---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF2600-zuo-ti-ji-lu.html)
#### 题意

一个括号序列，其中有几位为 `?`，将第 $i$ 个 `?` 修改为 `(` 的代价是 $a_i$，修改为 `)` 的代价是 $b_i$，问将所有 `?` 修改后使得序列匹配的最小代价。

#### 分析

贪心。发现一个匹配的括号序列的每一个前缀的左括号数一定不小于右括号数，因此先把问号都替换成右括号，对于每一位判断一下，如果到这一位时右括号数大于左括号数，就把前面右换左代价最小的一位替换成左。这样一定是正确的，因为前面如果左括号多了后面还能补救，但是右括号多了前面就不能完全匹配了。

于是可以从前往后扫，遇到一个问号就换成右括号，并把这个位置的下标和右换左的代价一起扔到一个小根堆里，如果右括号多了就取出堆顶换成左括号。

#### 核心代码
```cpp
priority_queue<Pair,vector<Pair>,greater<Pair> >q;
signed main(){
    scanf("%s",s+1);n=strlen(s+1);int i,j,cnt=0;
    for(i=1;i<=n;i++) if(s[i]=='?') m++,mp[i]=++mp[0];for(i=1;i<=m;i++) qread(a[i],b[i]);
    for(i=1;i<=n;i++){
        if(s[i]=='(') cnt++,t[i]=s[i];if(s[i]==')') cnt--,t[i]=s[i];
        if(s[i]=='?'){
            t[i]=')';q.push(Pair(a[mp[i]]-b[mp[i]],i));cnt--;ans+=b[mp[i]];
        }if(cnt<0){
            if(q.empty()) return printf("-1\n"),0;
            auto u=q.top();q.pop();t[u.second]='(';cnt+=2;
            // cout<<u.first<<" "<<u.second<<endl;
            ans+=u.first;
        }
    }if(cnt) return printf("-1\n"),0;
    printf("%lld\n%s\n",ans,t+1);
    return 0;
}
```

---

