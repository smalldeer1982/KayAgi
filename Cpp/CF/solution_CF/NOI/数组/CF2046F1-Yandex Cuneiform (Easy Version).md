# Yandex Cuneiform (Easy Version)

## 题目描述

这是该问题的简单版本。不同之处在于本版本中没有问号。只有在你解决了所有版本的问题后，才能进行 Hack。

很长时间以来，没有人能够破译苏美尔楔形文字。然而，如今它终于被攻克了！今天，你有机会来破译 Yandex 楔形文字。

Yandex 楔形文字由以下规则定义：

1. 空字符串是 Yandex 楔形文字。
2. 如果你在一个 Yandex 楔形文字中，恰好各插入一个字母 'Y'、'D' 和 'X'，并且插入后没有两个相邻的字母相同，那么你得到的字符串也是 Yandex 楔形文字。
3. 如果一个字符串无法通过上述规则得到，那么它不是 Yandex 楔形文字。

现给定一个模板。模板是一个仅由 'Y'、'D'、'X' 组成的字符串。

你需要判断，是否存在一种方式，使得将模板中的每个问号替换为 'Y'、'D' 或 'X' 后，可以得到一个 Yandex 楔形文字；如果存在，输出任意一种可行的方案，并给出一组插入操作序列，使得最终得到的字符串就是你输出的楔形文字。

在本题版本中，模板中没有问号。

## 说明/提示

在第二个样例中，字符串的变化过程如下：$"" \to \mathtt{YDX} \to \mathtt{YDXDYX}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
YDX
YDXDYX
YDX
DYYDXYXYX```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO```

# 题解

## 作者：wjwWeiwei (赞：6)

感觉具有诈骗性质。


可以猜到只要满足基本要求，也就是：
- `Y`，`D`，`X` 出现次数相同
- 最终串没有相邻字符相同


就一定有解。


考虑将插入改为删除，并将答案倒序输出。


钦定当前串首字母为 `Y`，另外两个字符为 `D`，`X`。在当前串中找到子串 ``DX`` 或 ``XD``，并令这个子串的左侧字母为 $A$，右侧字母为 $B$（可以为空）。


先证明一定能找到此子串。


若不能找到，则所有字符 `D`，`X` 的左侧一定是 `Y`（相邻字符不相同）。显然若 `Y` 的数量与 `D`，`X` 相同时，这种情况不可能出现。


下面分两种情况讨论：


1. $A$ 与 $B$ 不同

显然直接删除 `Y` 与 ``DX`` 后，新串相邻字符不同。


2. $A$ 与 $B$ 相同

此时 $A\neq$ `D`，$A\neq$ `X`，则 $A=$ `Y`，删除 $A$ 与 ``DX`` 后，原来 $A$ 左端的字母显然不为 `Y`，即不与 $B$ 相同，新串相邻字符不同。


按以上操作下去，最后消出来的一定是形如串 ``YDX``，串合法。


所以问题基本解决了，开一个 BIT 查询前缀剩余字符个数，还需要对每一个长度为 2 的子串维护一个支持
 $O(1)$ 插入，$O(1)$ 随机访问并删除的数据结构，可以使用栈。


时间复杂度为 BIT 的 $O(n\log(n))$，以及数据结构均摊的 $O(n)$，总复杂度 $O(n\log(n))$。


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5,M=1e6+5,mod=1e6+5;
using ll=long long;
int T,n;
int ton[4];
int a[N];
inline int to(char c){
	if(c=='Y')return 1;
	if(c=='D')return 2;
	return 3;
}
inline char rto(int x){
	if(x==1)return 'Y';
	if(x==2)return 'D';
	return 'X';
}
string s;
int tr[N];
inline void add(int x,int v){while(x<=n)tr[x]+=v,x+=x&(-x);}
inline int qry(int x){
	int res=0;
	while(x)res+=tr[x],x-=x&(-x);
	return res;
}
bool vis[N];
int pre[N],nxt[N];
struct pii{
	int fi,se;
};
struct My_stack{
	pii st[N<<1];int Top;
	inline void clear(){Top=0;}
	inline bool empty(){return !Top;}
	inline pii top(){return st[Top];}
	inline void pop(){Top--;}
	inline void push(pii x){st[++Top]=x;}
}us[12];
inline int kt(int x,int y){return (x-1)*3+y-1;}
inline void fadd(int x,int y){
	if(a[x]==a[y]||!a[x]||!a[y])return ;
	int ks=kt(a[x],a[y]);
	us[ks].push({x,y});
}
inline void fdel(int pos){
	add(pos,-1);
	nxt[pre[pos]]=nxt[pos];pre[nxt[pos]]=pre[pos];
	fadd(pre[pos],nxt[pos]);
	pre[pos]=nxt[pos]=0;
	vis[pos]=1;
}
inline pii find_valid(int ks){
	while(!us[ks].empty()){
		pii P=us[ks].top();
		if(vis[P.fi]||vis[P.se])us[ks].pop();
		else return us[ks].pop(),P;
	}
	return {-1,-1};
}
struct node{
	pii p1,p2,p3;
};
vector<node>ans;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>s;
		n=s.length();
		memset(ton,0,sizeof ton);
		for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;
		nxt[n]=a[n+1]=0;
		bool va=1;
		for(int i=0;i<n-1;i++)if(s[i]==s[i+1])va=0;
		for(int i=1;i<=n;i++)a[i]=to(s[i-1]),tr[i]=vis[i]=0,ton[a[i]]++;
		if(!va||(ton[1]^ton[2])||(ton[1]^ton[3])){
			cout<<"NO\n";
			continue;
		}
		ans.clear();
		for(int i=0;i<=10;i++)us[i].clear();
		for(int i=1;i<=n;i++)add(i,1);
		for(int i=1;i<n;i++)fadd(i,i+1);
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			vis[i]=1;
			int p1=0,p2=0;
			for(int j=1;j<=3;j++){
				if(j^a[i]){
					if(!p1)p1=j;
					else p2=j;
				}
			}
			pii cur=find_valid(kt(p1,p2));
			if(cur.fi==-1&&cur.se==-1)swap(p1,p2),cur=find_valid(kt(p1,p2));
			int x=pre[cur.fi],y=nxt[cur.se];
			if(x==i)ans.push_back({{p2,0},{p1,0},{a[i],0}}),fdel(i),fdel(cur.fi),fdel(cur.se);
			else if(a[x]^a[y]){
				int tot=qry(x)-1;
				ans.push_back({{p1,tot},{p2,tot+1},{a[i],0}});
				fdel(i),fdel(cur.fi),fdel(cur.se);
			}
			else{
				int tot=qry(x)-1;
				ans.push_back({{p2,tot},{a[i],tot},{p1,tot+1}});
				vis[i]=0;i--;
				fdel(x),fdel(cur.fi),fdel(cur.se);
			}
		}
		reverse(ans.begin(),ans.end());
		cout<<"YES\n";
		for(int i=0;i<n;i++)cout<<s[i];
		cout<<"\n";
		for(auto v:ans){
			cout<<rto(v.p1.fi)<<" "<<v.p1.se<<" ";
			cout<<rto(v.p2.fi)<<" "<<v.p2.se<<" ";
			cout<<rto(v.p3.fi)<<" "<<v.p3.se<<"\n";
		}
	}
	return 0;
}
```

---

