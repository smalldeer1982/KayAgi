# [APC001] C - Not APC

## 题目背景

这题并没有什么有趣的题目背景，祝您愉快。

## 题目描述

小 A 有一个**仅由 `A`、`P`、`C` 构成**的字符串 $S$。

小 A 需要**尽可能地**不断在这个字符串中消除形如 `APC` 这样的**子序列**，直到无法消除。

最后，小 A 需要输出消除后的字符串。如果字符串可以被消除成空串，则输出 `Perfect`。

然而小 A 不会这个题，所以来找你帮忙。

## 说明/提示

**样例解释 #1：**  
对于第一组数据，字符串为 `PAAAAPPPCA`，下标为 $\{5,6,9\}$ 的字符串被删除，最终得到 `PAAAPPA`。

对于第二组数据，字符串为 `CAPPCPCAPAPA`，下标为 $\{2,4,5\}$ 的字符被消除，得到 `CPPCAPAPA`。

**样例解释 #2：**  
唯一的一组数据中，字符串为 `APC`，显然能被全部消除，方案也显然。

$1\leq T\leq 10$，$1\leq \sum |S|\leq 3\times 10^6$。

## 样例 #1

### 输入

```
5
PAAAAPPPCA
CAPPCPCAPAPA
PPAAAACCAAAAAAAAC
CAPPCAAPA
APPAACPPAPPPAPAAAA```

### 输出

```
PAAAPPA
1
5 6 9
CPPCAPAPA
1
2 4 5
PPAAAACCAAAAAAAAC
0
CPAAPA
1
2 3 5
PAAPPAPPPAPAAAA
1
1 2 6```

## 样例 #2

### 输入

```
1
APC
```

### 输出

```
Perfect
1
1 2 3```

## 样例 #3

### 输入

```
10
PPCPAPAAACPAPACPPCPC
APPAPPAPPCPAPPCCCPPA
APPCCPPAPPAACCPPPPPP
PACPPCAPCPPCPPPAAAAC
PPPCPPCCPACAAACCCCAC
ACAAPCPAPAAAAPPACPPC
ACACPPCCPPAACPAAAAAC
APPCPCCCAPCACPAACACC
AACPCAPACPPPCAAPCCPC
PPACPPPCCAPAAAPCPAPA
```

### 输出

```
PPCPAAPP
4
5 6 10
7 11 15
8 13 18
9 16 20
PPPPPPPA
4
1 2 10
4 5 15
7 8 16
12 13 17
PCPPPAACPPPPPP
2
1 2 4
8 9 13
PCPPPCPPPAAAAC
2
2 4 6
7 8 9
PPPCPPCCPACAAACCCCAC
0
CAAAAAPPAPP
3
1 5 6
3 7 17
4 9 20
CCPPACAAAAA
3
1 5 7
3 6 8
11 14 20
PPCCCCAAACC
3
1 2 4
9 10 11
12 14 17
CP
6
1 4 5
2 7 9
6 10 13
8 11 17
14 16 18
15 19 20
PPCPPCAAAPPAPA
2
3 5 8
10 11 16
```

# 题解

## 作者：Zskioaert1106 (赞：6)

题目传送门：[P11138 [APC001] C - Not APC](https://www.luogu.com.cn/problem/P11138)

### 题意简述

消消乐。如果能找到按顺序的 `APC` 串就消掉，要让字符串尽量小并输出过程。

### 题目分析

像这道题一样用[字符串](https://www.luogu.com.cn/problem/list?tag=2)、[栈](https://www.luogu.com.cn/problem/list?tag=287)或[队列](https://www.luogu.com.cn/problem/list?tag=288)的题[已](https://www.luogu.com.cn/problem/AT_code_festival_2017_qualc_a)经有很多了，本题不过是要输出过程。

我们建三个队列来存字符 `A`、`P`、`C` 的数量和位置，遍历一遍字符串。当我们看到字符 `A`时，肯定要存入队列以备后面的 `P` 和 `C`；当我们看到 `P` 时，如果加上它后存 `P` 的队列数量小于等于存 `A` 的队列，那这些字符都能匹配到 `A`；如果是 `C` 则要当存 `A` 和 `P` 的队列都比它大，才考虑将它入队。

一旦存 `C` 的队列有值（此时另外两个队列一定也有），则为了利益最大就正好从队列最前端的 `A` 和 `P` 选字符，将这三个消掉并将这次的操作存入另一个队列。

此时将这三个消掉的字符在字符串中的位置要替换成一个不存在的以便之后输出。

输出时先遍历一遍字符串，如果不是之前的专用替换字符就输出，之后输出存操作的队列的长度，然后次序输出。

……枯燥的文字好抽象啊，还是上代码吧。

### 编写代码

首先初始化各种队列，为了方便定义一个三元组结构体类型的队列存操作：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int t;
string s;
queue<int>qa,qb,qc;
struct three{
	int a,b,c;
};
queue<three>q;
```

然后编写字符串处理部分：

```cpp
for(int i=0;i<s.size();i++){
  if(s[i]=='A')qa.push(i+1);
  else if(s[i]=='P'&&(qa.size()>qb.size()))qb.push(i+1);
  else if(s[i]=='C'&&(qb.size()>qc.size())){
    qc.push(i+1);
    three o;o.a=qa.front(),o.b=qb.front(),o.c=qc.front();
    s[o.a-1]=char(0),s[o.b-1]=char(0),s[o.c-1]=char(0);
    qa.pop(),qb.pop(),qc.pop();
    q.push(o);
  }
}
```

当字符为能用到的 `C` 时，（放存它的队列只是为了清晰明了）首先把三元组存起来入队，然后把入队的三个字符出队，再占位删除字符串中的相应位置。

- 注意，操作输出时下标从 $1$ 开始，但字符串的下标从 $0$ 开始。

然后是输出部分：

```cpp
bool b=1;
for(int i=0;i<s.size();i++){
  if(s[i]!=char(0)){
    cout<<s[i];
    b=0;
  }
}
if(b)cout<<"Perfect";
cout<<'\n'<<q.size()<<'\n';
while(!q.empty()){
  cout<<q.front().a<<' '<<q.front().b<<' '<<q.front().c<<'\n';
  q.pop();
}
```

每次操作边输出边出队即可。注意：

- 每个测试数据输出后要清空四个队列。

- 记得特判字符串为空输出 `Perfect`。

知周所众，多测函数好。所以这是我的主函数（起名废默默碎了）：

```cpp
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		doing();
		while(!qa.empty())qa.pop();
		while(!qb.empty())qb.pop();
		while(!qc.empty())qc.pop();
	}
	return 0;
}
```

这题除了难点外还是蛮简单的，下面放完整代码：

### 完整代码

（赛时）

```cpp
#include<iostream>
#include<queue>
#define doing doing()
using namespace std;
int t;
string s;
queue<int>qa,qb,qc;
struct three{int a,b,c;};
queue<three>q;
void doing{
	for(int i=0;i<s.size();i++){
		if(s[i]=='A')qa.push(i+1);
		else if(s[i]=='P'&&(qa.size()>qb.size()))qb.push(i+1);
		else if(s[i]=='C'&&(qb.size()>qc.size())){
			qc.push(i+1);
			three o;o.a=qa.front(),o.b=qb.front(),o.c=qc.front();
			s[o.a-1]=char(0),s[o.b-1]=char(0),s[o.c-1]=char(0);
			qa.pop(),qb.pop(),qc.pop();
			q.push(o);
		}
	}
	bool b=1;
	for(int i=0;i<s.size();i++){
		if(s[i]!=char(0)){
			cout<<s[i];
			b=0;
		}
	}
	if(b)cout<<"Perfect";
	cout<<'\n'<<q.size()<<'\n';
	while(!q.empty()){
		cout<<q.front().a<<' '<<q.front().b<<' '<<q.front().c<<'\n';
		q.pop();
	}
	return ;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>s;
		doing;
		while(!qa.empty())qa.pop();
		while(!qb.empty())qb.pop();
		while(!qc.empty())qc.pop();
	}
	return 0;
}
```

[赛时 AC](https://www.luogu.com.cn/record/179305955)。当然我们可以把没必要的队列简化掉：

```cpp
#include<iostream>
#include<queue>
using namespace std;
queue<int>qa,qp;
struct three{
	int a,b,c;
};
queue<three>q;
void doing(string s){
	for(int i=0;i<s.size();i++){
		if(s[i]=='A')qa.push(i+1);
		else if(s[i]=='P'&&(qa.size()>qp.size()))qp.push(i+1);
		else if(s[i]=='C'&&(!qp.empty())){
			three o;o.a=qa.front(),o.b=qp.front(),o.c=i+1;
			s[o.a-1]=char(0),s[o.b-1]=char(0),s[i]=char(0);
			qa.pop(),qp.pop(),q.push(o);
		}
	}
	bool b=1;
	for(int i=0;i<s.size();i++){
		if(s[i]!=char(0)){
			cout<<s[i];
			b=0;
		}
	}
	if(b)cout<<"Perfect";
	cout<<'\n'<<q.size()<<'\n';
	while(!q.empty()){
		cout<<q.front().a<<' '<<q.front().b<<' '<<q.front().c<<'\n';
		q.pop();
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		doing(s);
		while(!qa.empty())qa.pop();
		while(!qp.empty())qp.pop();
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/179338127)。

---

## 作者：T_TLucas_Yin (赞：3)

我们遍历一遍字符串，从前到后分别存储每一个 `A`、`P`、`C` 出现的位置。

字符串中的每一个 `APC` 子序列，其中的三个字母在原字符串中的位置肯定是 `A` 最小，`P` 其次，`C` 最大。所以倒序遍历存储字符出现位置的数组，对于每个 `C`，找到位置比它小的第一个 `P`，再找到位置比这个 `P` 小的第一个 `A`，将这三个字符作为一对删掉即可。由于取得是符合条件的第一个字符，即能删尽删，所以不会出现非最优删法。

对于删除的操作，我们不一定要真的在字符串中删掉字符，而可以打一个标记表示是否要输出这个字符。

不建议加快读之类的读入优化，在这种输入输出都有多个字符串的题中很容易造成混乱。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[1000005],topa,b[1000005],topb,c[1000005],topc,top;
struct node{
	int x,y,z;
}f[1000005];
char s[1000005];
int read(){
	int sum=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) sum=sum*10+(c-'0'),c=getchar();
	return sum;
}
bool flag[1000005];
int main(){
	cin>>t;
	while(t--){
		int n=0;
		cin>>(s+1);
		n=strlen(s+1);
		topa=topb=topc=top=0;
		for(int i=1;i<=n;i++) flag[i]=1;
		for(int i=1;i<=n;i++){
			if(s[i]=='A') a[++topa]=i;
			if(s[i]=='P') b[++topb]=i;
			if(s[i]=='C') c[++topc]=i;
		}
		while(topa!=0&&topb!=0&&topc!=0){
			while(b[topb]>c[topc]&&topb!=0) topb--;
			while(a[topa]>b[topb]&&topa!=0) topa--;
			if(topa!=0&&topb!=0) 
				f[++top]={a[topa],b[topb],c[topc]},
				flag[a[topa]]=flag[b[topb]]=flag[c[topc]]=0,
				topa--,topb--,topc--;
		}
		bool ff=0;
		for(int i=1;i<=n;i++) if(flag[i]) printf("%c",s[i]),ff=1;
		if(!ff) printf("Perfect");
		printf("\n%d\n",top);
		for(int i=1;i<=top;i++) printf("%d %d %d\n",f[i].x,f[i].y,f[i].z);	
	}
	return 0;
} 
```

---

## 作者：__Allen_123__ (赞：2)

本题 spj 出锅，导致输出方案时不能留有行末空格，十分抱歉。（update：修了。）

---

从前往后，使用 $3$ 个队列分别记录从前往后的没有被删除且可以被删除的 `A`、`P`、`C` 的下标。每次入队之后，查看三个队列是否都不为空（如果是，则可以进行删除），注意要把这些下标出队。使用一个数组记录哪些下标的字符被删除了就可以。

Code：

```cpp
#include <bits/stdc++.h>
//#define int long long
#define pii pair<int, int>
#define rep(x, y, z) for(int x = (y);x <= (int)(z);x++)
#define per(x, y, z) for(int x = (y);x >= (int)(z);x--)
#define ask(x) while(x--)
#define ask1(x) for(scanf("%d", &x);x--;)
#define fvec(x, y) for(auto x : y)
#define all(x) x.begin(), x.end()
#define pb push_back
#define fi first
#define se second
typedef long long ll;
using namespace std;
void gmax(auto &x, auto y){
	x = max(x, y);
}
void gmin(auto &x, auto y){
	x = min(x, y);
}
const int MAXN = 3e6 + 5, inf = 0x3f3f3f3f, p = 1e9 + 7;
void add(auto &x, auto y){
	x = (x + y % p) % p;
}
int t, n;
string s;
bool b[MAXN];
unsigned int s1, s2, s3;
queue<int> q1, q2, q3;
vector<array<int, 3>> ans;
signed main(){
	ask1(t){
		cin >> s;
		n = s.size();
		memset(b, 0, sizeof(b));
		while(!q1.empty()) q1.pop();
		while(!q2.empty()) q2.pop();
		ans.clear();
		rep(i, 0, n - 1){
			if(s[i] == 'A'){
				q1.push(i);
			}
			if(s[i] == 'P' && !q1.empty()){
				q2.push(i);
			}
			if(s[i] == 'C' && !q1.empty() && !q2.empty()){
				q3.push(i);
			}
			if(!q3.empty()){
				while(!q2.empty() && q2.front() < q1.front()){
					q2.pop();
				}
				if(q2.empty()) continue;
				while(!q3.empty() && q3.front() < q2.front()){
					q3.pop();
				}
				if(q3.empty()) continue;
				b[q1.front()] = b[q2.front()] = b[q3.front()] = 1;
				ans.pb({q1.front() + 1, q2.front() + 1, q3.front() + 1});
				q1.pop();
				q2.pop();
				q3.pop();
			}
		}
		string ret = "";
		rep(i, 0, n - 1){
			if(!b[i]){
				ret += s[i];
			}
		}
		if(ret == ""){
			printf("Perfect\n");
		}
		else{
			cout << ret << "\n";
		}
		printf("%d\n", (int)ans.size());
		fvec(i, ans){
			printf("%d %d %d\n", i[0], i[1], i[2]);
		}
	}
	return 0;
}
```

---

## 作者：DFbd (赞：1)

## 思路：
把字符 `A` 的位置放进一个队列里，再把字符 `P` 的位置放进一个队列里。

当遇到字符 `C` 时，就看 `A` 的队列的队首和 `P` 的队列的队首。

当 `P` 的队列的队首的位置在`A` 的队列的队首之前时，这个 `P` 就一定不会被消除了，将它出队。

消除到 `P` 的队列空了或 `P` 的队列的队首的位置在`A` 的队列的队首之后时，把这两个数取出来，统计答案，并且标记。

输出剩余字符串时只需要输出没被标记的位置的字符。

如果全部被标记了就输出 `Perfect`。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,sz,a[3000005],p[3000005],la,lp,ra,rp,ans1[1000005],ans2[1000005],ans3[1000005],f[3000005];
string s;
int main(){
    cin>>t;
    while(t--){
        cin>>s;
        sz=ra=rp=0;
        la=lp=1;
        for(int i=0;i<s.size();i++) f[i]=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='A') a[++ra]=i;
            else if(s[i]=='P') p[++rp]=i;
            else if(la<=ra&&lp<=rp){
                while(a[la]>p[lp]&&lp<=rp) lp++;
                if(lp>rp) continue;
                ans1[++sz]=a[la]+1;
                f[a[la]]=1;
                la++;
				ans2[sz]=p[lp]+1;
				f[p[lp]]=1;
				lp++;
				ans3[sz]=i+1;
				f[i]=1;
            }
        }
        for(int i=0;i<s.size();i++){
            if(!f[i]) cout<<s[i];
        }
        if(sz*3==s.size()) cout<<"Perfect";
        cout<<"\n"<<sz<<"\n";
        for(int i=1;i<=sz;i++) cout<<ans1[i]<<" "<<ans2[i]<<" "<<ans3[i]<<"\n";
    }
    return 0;
}
```

---

## 作者：a18981826590 (赞：1)

# [P11138 [APC001] C - Not APC](https://www.luogu.com.cn/problem/P11138)
## 题意简述
在字符串中不断寻找 `APC` 这样的子串，即不断找到 `A` 及其后的 `P` 及其后的 `C`。记录其在**原字符串**中的下标并将其删除。
## 解题思路
我们要求的都是原字符串中的下标，那就不要改变原字符串，用一个 `bool` 数组记录某个下标位置上的字符是否被删去。

寻找子串时就从上次已找到的位置往后遍历即可（其实字符串有个 `find` 函数，但我在赛时调了会没条出来，就改成手写的了）。找到后就记录下来。
## AC 代码
注意格式！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,n;
bool d[3000010];
vector<int>x,y,z;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	while(n--){
		cin>>s;
		a=b=c=0;
		for(int i=0;i<s.size();i++) d[i]=0;
		x.clear();
		y.clear();
		z.clear();
		while(1){
			while(s[a]!='A'&&a<s.size()) a++;
			b=max(a,b)+1;
			while(s[b]!='P'&&b<s.size()) b++;
			c=max(b,c)+1;
			while(s[c]!='C'&&c<s.size()) c++;
			if(c>=s.size()) break;
			d[a]=d[b]=d[c]=1;
			x.push_back(a);
			y.push_back(b);
			z.push_back(c);
			a++;
		}
		if(3*x.size()==s.size()) cout<<"Perfect\n";
		else{
			for(int i=0;i<s.size();i++){
				if(!d[i]) cout<<s[i];
			}
			cout<<'\n';
		}			
		cout<<x.size()<<'\n';
		for(int i=0;i<x.size();i++) cout<<x[i]+1<<' '<<y[i]+1<<' '<<z[i]+1<<'\n';
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑使用栈来维护当前序列中的 `A,P`，遇到 `C` 进行弹栈。

考虑什么情况不需要入栈：当前是 `P`，且栈里 `A` **不**比 `P` 多，那么肯定不能匹配；同理如果是 `C`，且没有 `A,P`，也不行。最后栈里面剩下的也不能删除。

栈维护什么？既然操作要给出操作的位置，那不如直接存位置（分 `A,P` 来存储，`C` 直接弹）。

最后把操作过的字符去掉就是最简的字符串。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,tag[3000001];
string s,ans;
stack<int>sta,stp;
vector<tuple<int,int,int> >op;
void Main(){
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='C'){
            if(!sta.empty()&&!stp.empty()){
                op.push_back(make_tuple(sta.top(),stp.top(),i+1));
                sta.pop(),stp.pop();
            }
        }//C
        else if(s[i]=='P'){
            if(sta.size()>stp.size())
                stp.push(i+1);
        }//P
        else if(s[i]=='A')
            sta.push(i+1);//A
    }
    for(auto p:op){
        tag[get<0>(p)-1]=1,
        tag[get<1>(p)-1]=1,
        tag[get<2>(p)-1]=1;//标记
    }
    for(int i=0;i<s.size();i++){
        if(tag[i]);
        else
            ans+=s[i];
    }
    if(ans.size())
        cout<<ans;
    else
        cout<<"Perfect";//全部清除
    cout<<'\n'<<op.size()<<'\n';
    for(auto p:op)
        cout<<get<0>(p)<<' '<<get<1>(p)<<' '<<get<2>(p)<<'\n';
    op.clear();
    while(!sta.empty())
        sta.pop();
    while(!stp.empty())
        stp.pop();
    memset(tag,0,sizeof(tag));
    ans="";
    return;
}
int main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：0)

### 思路
我们可以暴力枚举字符 `A` 的位置，第二重循环枚举字符 `P` 时应在字符 `A` 的位置的下一个位置与上一个字符 `P` 的下一个位置中最大的那一个开始枚举，第三重循环枚举字符 `C` 时与点 `P` 同理，最后统计一下答案即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
struct nn{
	int x,y,z;
};
vector<nn>ans;
bool vis[3000005];
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){
    	ans.clear();
    	memset(vis,0,sizeof vis);
    	int a,b,c;
    	a=b=c=0;
    	cin>>s;
    	for(;a<s.size();a++){
    		if(s[a]=='A'){
    			for(b=max(b,a)+1;b<s.size();b++){
    				if(s[b]=='P'){
    					for(c=max(c,b)+1;c<s.size();c++){
    						if(s[c]=='C'){
    							ans.push_back({a,b,c});
    							vis[a]=vis[b]=vis[c]=1;
    							if(vis[a]==1)break;
							}
						}
    					if(vis[a]==1)break;
					}
				}
			}
		}
		int x=0;
		for(int i=0;i<s.size();i++){
			if(vis[i]==0){
				cout<<s[i];
				x++;
			}
		}
		if(x==0){
			cout<<"Perfect";
		}
		cout<<"\n";
		cout<<ans.size()<<"\n";
		for(auto i:ans){
			cout<<i.x+1<<" "<<i.y+1<<" "<<i.z+1<<"\n";
		}
	}
	return 0;
} 
```

---

## 作者：NTT__int128 (赞：0)

# P11138 [APC001] C - Not APC题解
对于此题，我们可以贪心地选择第一个 $\texttt{A}$ 以及它后面的第一个 $\texttt{P}$ 以及它后面的第一个 $\texttt{C}$ 消除。剩下的同理。

用三个队列维护即可。

时间复杂度：$\Theta(\sum|S|)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+5;
int t;
string s;
queue<int>qa,ca;
queue<pair<int,int>>qp,cp;
queue<pair<pair<int,int>,int>>qc,cc;
bitset<N>b;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		b.set();
		qa=ca,qp=cp,qc=cc;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='A')qa.push(i+1);//记录A的位置
			if(s[i]=='P'&&!qa.empty())qp.push({qa.front(),i+1}),qa.pop();//记录AP的位置
			if(s[i]=='C'&&!qp.empty())qc.push({qp.front(),i+1}),b[qp.front().first]=b[qp.front().second]=b[i+1]=0,qp.pop();//记录APC的位置，并标记删除
		}
		for(int i=0;i<s.size();i++)if(b[i+1])cout<<s[i];//判断删除输出
		if(qc.size()*3==s.size())cout<<"Perfect";//判断是否全删
		cout<<'\n'<<qc.size()<<'\n';
		while(!qc.empty()){
			cout<<qc.front().first.first<<' '<<qc.front().first.second<<' '<<qc.front().second<<'\n';//输出A、P、C的位置
			qc.pop();
		}
	}
	return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

我们可以先预处理三个数组 $a,b,c$，分别记录所有 `A`，`P`，`C` 的位置。

因为题目要求了 `APC` 的顺序，所以我们可以枚举每个 `P` 的位置，然后找到这个位置前面第一个还没有用过的 `A`，以及这个位置后面第一个还没有用过的 `C`，然后将这三个位置标记为用过。

最后输出时，直接输出那些没有被标记过的字符即可。

**注意特判 `Perfect`，但是笑点解析：只有样例 $2$ 中有 `Perfect`，其余数据点都没有。**

时间复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool flag[3000005];
int posa[3000005],posp[3000005],posc[3000005];
int ansa[3000005],ansp[3000005],ansc[3000005];
int main() {
	int t; cin >> t;
	while(t--) {
		string s; cin >> s;
		memset(flag,false,sizeof flag);
		int cura = 0,curp = 0,curc = 0;
		for(int i = 0;i < s.size();i++) {
			if(s[i] == 'A') posa[++cura] = i;
			if(s[i] == 'P') posp[++curp] = i;
			if(s[i] == 'C') posc[++curc] = i;
		}
		int nowa = 1,nowp = 1,nowc = 1,anscur = 0;
		int num = s.size();
		for(;nowp <= curp;nowp++) {
			if(nowa > cura || nowc > curc) break;
			if(posp[nowp] > posa[nowa]) {
				while(posc[nowc] <= posp[nowp] && nowc <= curc) nowc++;
				if(nowc == curc+1) break;
				flag[posp[nowp]] = flag[posa[nowa]] = flag[posc[nowc]] = true; num -= 3;
				ansa[++anscur] = posa[nowa]+1; ansp[anscur] = posp[nowp]+1; ansc[anscur] = posc[nowc]+1;
				nowa++; nowc++;
			}
		}
		for(int i = 0;i < s.size();i++) if(!flag[i]) cout << s[i];
		if(num == 0) cout << "Perfect";
		cout << endl;
		cout << anscur << endl;
		for(int i = 1;i <= anscur;i++) cout << ansa[i] << ' ' << ansp[i] << ' ' << ansc[i] << endl;
	}
	return 0;
}
```

---

