# Old Berland Language

## 题目描述

$Berland$的科学家知道，古老的$Berland$语言中有$n$个单词。这些单词的长度为$l_1$,$l_2$,...,$l_n$。每个单词由$0$和$1$组成。

尽管古代$Berland$人语速很快并且说话不停顿，但同时他们也能很好地理解对方。

可能的原因是：没有一个单词是另一个单词的前缀。字符串的前缀被认为是子串的其中一个开端。

请你帮助科学家确定，是否所有的古$Berland$语的单词都可以被重构。如果可以，输出单词本身。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
YES
0
10
110
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
NO
```

# 题解

## 作者：神之蒟蒻xyk (赞：3)

发现与楼上的做法完全不同

观察题面：不能有与前面子串相同的前缀

于是想到了字典树

相当于每次在0、1的字典树上跑一遍，不能遇到前面的结尾

当然，要先按读入的长度排序处理

code：

```cpp
#include<bits/stdc++.h>
#define fir(a, b, c) for(register int a = b; a <= c; a ++)
#define ll long long
using namespace std;

inline int read() {
	int x = 0; bool flag = 1; char c = getchar();
	for(; !isdigit(c); c = getchar())  if(c == '-') flag = 0;
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	return flag ? x : -x;
}

const int N = 1e3 + 10;
int f[N*N][2];
int n, a[N];
int tot;
bool endd[N*N];
int id[N], ans[N][N];
bool flg = 0;

bool bo;
inline void work(int k, int tt, int step, int p) {
	if (bo) return;
	if (step > k) {
		endd[p] = 1;
		bo = 1; return;
	}
	if (endd[f[p][0]] == 0) {
		if (f[p][0] == 0) f[p][0] = ++ tot;
		ans[tt][step] = 0;
		work(k, tt, step+1, f[p][0]);
	}
	if (bo) return;
	if (endd[f[p][1]] == 0) {
		if (f[p][1] == 0) f[p][1] = ++ tot;
		ans[tt][step] = 1;
		work(k, tt, step+1, f[p][1]);
	}
}

inline bool cmp(int x, int y){return a[x] < a[y];}

int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read();
	tot = 1;
	fir (i, 1, n) a[i] = read(), id[i] = i;
	sort(id+1, id+1+n, cmp);
	fir (i, 1, n) {
		bo = 0;
		work(a[id[i]], id[i], 1, 1);
		if (bo == 0){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	fir (i, 1, n) {
		fir (j, 1, a[i])
			printf("%d",ans[i][j]);
		cout<<endl;
	}
	return 0;
}



```


---

## 作者：Ag2WO4 (赞：1)

## 声明三点：
1. 提醒看其他楼的各位，[本题亲测有 SPJ](https://codeforces.com/contest/37/submission/245874817)；
2. 本题解法是位运算实现的，不涉及树，接下来讲解时为了便于理解会使用树的语言；
3. 提供的 AC 代码是提交版 Python 代码的美化版，非 Python 用户请自行翻译。

对一棵无限大的满二叉树，剪去任意一棵满二叉子树，若保留子树根节点，整棵树是完全二叉树，即：第 $n+1$ 层的所有节点数等于第 $n$ 层非叶子结点数的二倍。所以，考虑自上而下的剪枝过程：
- 若在层内剪枝，当前层非叶子节点数减一；
- 若向下一层，当前层（此时层已更新）非叶子节点数翻倍（有点像动态规划的思想）；
- 若当前层已经没有非叶子节点，无法剪枝。

每次的剪枝目标取当前层最左侧节点即可，而在上述过程中，剪枝时最左侧节点编号加一，向下一层时最左侧节点编号乘二即可。而按本题要求以零为根节点的树可以以如下形式构造：
- 根节点编号为零（事实上这棵树可以上下无限延伸，方便讨论人为进行向上的剪枝，认为存在根节点）；
- 对节点 $n$，左儿子为 $2n$，右儿子为 $2n+1$。特别地，对于编号为零的节点，其右儿子是以一为根节点的无限大的满二叉树的根节点；整棵树可以看作在最左侧无限延伸的一群编号为零的节点，每个节点的右儿子都是以一为根节点的无限大的满二叉树的根节点。

所以初始化根节点编号为零，层数为一（字符串最短长度），按上述要求变化，记录答案即可。忽略 $O(n\log n)$ 的排序，代码主体复杂度 $O(n)$。
#### 代码
```python
input()#第一行对 Python 没用
cuts=list(map(int,input().split()))#剪枝，注意存储输入顺序

poss=2#剩余可能性数
floor=1#层数
ans={}#保存答案
node=0#层内最左节点编号

for cut in sorted(cuts):#从上到下排序
    if poss==0:#无法剪枝但是还有需求
        print('NO')
        exit()

    poss<<=cut-floor#向下层数左移（效果同乘二）
    node<<=cut-floor#同上

    tmp=bin(node)[2:]#记录答案
    node+=1#剪枝
    poss-=1#同上
    floor=cut#更新层数
    
    if cut in ans:#基础字典操作，小心 KeyError
        ans[cut].append('0'*(cut-len(tmp))+tmp)#用零补全位数
    else:
        ans[cut]=['0'*(cut-len(tmp))+tmp]

print('YES')
for i in cuts:
    print(ans[i].pop())#每个答案用过即销毁
```

---

## 作者：lilong (赞：0)

将每个 01 串看作一个二进制数，将长度从小到大排序，对于当前第 $i$ 个串，首先在第 $i-1$ 个串的基础上加 $1$（如果不能加 $1$ 即爆位数则无解），如果长度相同则无需任何操作，否则按照缺少的长度从后面补 $0$。这样做能保证长度短的不为长度长的前缀，且尽可能的多填数。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
struct L{
    int v,id;
    int c[1010];
    L(){c[0]=1;}
}a[1010],ans[1010];
int n,flag,pp[1010];
bool cmp(L x,L y){
    return x.v<y.v;
}
bool add(int i){
    for(int j=a[i].c[0];j>=1;j--){
        if(a[i].c[j]==0){
            a[i].c[j]=1;
            return true;
        }
        a[i].c[j]=0;
    }
    return false;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].v,a[i].id=i;
    sort(a+1,a+n+1,cmp);
    a[1].c[0]=a[1].v;
    for(int i=1;i<=a[1].v;i++)
        a[1].c[i]=0;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=a[i-1].c[0];j++)
            a[i].c[j]=a[i-1].c[j];
        if(!add(i)){
            cout<<"NO";
            return 0;
        }
        a[i].c[0]=a[i].v;
        // cout<<a[i].c[0]<<endl;
    }
    for(int i=1;i<=n;i++)
        ans[a[i].id]=a[i];
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=ans[i].c[0];j++)
            cout<<ans[i].c[j];
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

普通的字典树。

看到 01 Trie 和前缀信息不难想到字典树。我们考虑每次在跑到树上的一个点时，如果它后面可以选 $0$ 就选 $0$，否则选 $1$。

注意到 $N \le 1000$，可以边加串边维护哪些点可以用。

每次成功跑完长度就标记最后的点，并记录构造的字符串。

如果一个点往后选 $0$ 和选 $1$ 都被标记了，这个点也打上标记。

最后看有没有字符串无法构造（是空的）。

特别注意：这个算法只有在长度从小到大构造时是正确的，所以先要对每个构造的长度离线。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
string s[1010];
int n,tot,ch[N][2];
int vis[N];
struct node{
    int len,id;
    bool operator <(const node &o)const{return len<o.len;}
}a[1010];
void insert(int len,int id){
    int p=0;
    string tmp="";
    for(int i=0;i<len;++i){
        if(!ch[p][0]){
            ch[p][0]=++tot;
            p=ch[p][0];
            tmp=tmp+"0";
            continue;
        }
        else if(ch[p][0] && !vis[ch[p][0]]){
            p=ch[p][0];tmp=tmp+"0";
            continue;
        }
        else if(!ch[p][1]){
            ch[p][1]=++tot;tmp=tmp+"1";
            p=ch[p][1];continue;
        }
        else if(ch[p][1] && !vis[ch[p][1]]){
            tmp=tmp+"1";
            p=ch[p][1];continue;
        }
    }vis[p]=1;s[id]=tmp;
    for(int p=tot;p;--p)if(vis[ch[p][0]] && vis[ch[p][1]])vis[p]=1;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)s[i]="";
    for(int i=1;i<=n;++i){
        int len;cin>>len;
        a[i]={len,i};
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;++i)insert(a[i].len,a[i].id);
    for(int i=1;i<=n;++i){
        if(s[i]==""){
            cout<<"NO";return 0;
        }
    }
    cout<<"YES\n";
    for(int i=1;i<=n;++i)cout<<s[i]<<'\n';
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先我们发现这是一道简单题于是我们怎么暴力怎么来。

首先发现是 01 串，想到用 Trie 树，于是我们想到一个平凡做法：我们遍历整棵 Trie 树，然后如果深度有符合目前的 $a$ 中的长度，那么我们直接返回，这样可以不再搜索这棵子树，然后等到全部搜完之后退出，简单而言，代码长这样：

```cpp
void dfs ( int &x, string s, int dep ) {
  if ( !x ) {
    x = ++ cnt;
  }
  if ( tong[dep] ) {
    tong[dep] --;
    ans.push_back ( s );
    return ;
  }
  dfs ( trie[x][0], s + '0', dep + 1 ), dfs ( trie[x][1], s + '1', dep + 1 );
}
```

但是你发现这个代码会一直搜下去，于是时间复杂度就成了 $O(2^{len})$ 了，我们考虑剪枝。

注意到如果当前没有比这个结点深度大的 $a$ 时可以直接跳出，我们可以利用树状数组维护一下桶的后缀和，然后不难发现最后的树最多就是 $n$ 个长度为 $1000$ 的字符串，然后又由于你用了树状数组，于是复杂度就是 $O(n^2 \log n)$。

## code

具体来说，代码长这样：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 1005;

int n, cnt, rt;
int a[N], trie[N * N][2];
vector < string > ans;
bool vis[N];

int tree[N];

int lowbit ( int x ) {
  return x & -x;
}

void update ( int x, int k ) {
  while ( x < N ) {
    tree[x] += k;
    x += lowbit ( x );
  }
}

int query ( int x ) {
  int res = 0;
  while ( x ) {
    res += tree[x];
    x -= lowbit ( x );
  }
  return res;
}

void dfs ( int &x, string s, int dep ) {
  if ( !x ) {
    x = ++ cnt;
  }
  if ( dep >= 1 && query ( dep ) - query ( dep - 1 ) ) {
    update ( dep, -1 );
    ans.push_back ( s );
    return ;
  }
  if ( !( query ( 1000 ) - query ( dep ) ) ) {
    return ;
  }
  dfs ( trie[x][0], s + '0', dep + 1 ), dfs ( trie[x][1], s + '1', dep + 1 );
}

void Solve () {
  cin >> n;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
    update ( a[i], 1 );
  }
  dfs ( rt, "", 0 );
  if ( ans.size () != n ) {
    cout << "NO";
  }
  else {
    cout << "YES\n";
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 0; j < ans.size (); j ++ ) {
        if ( !vis[j] && ans[j].size () == a[i] ) {
          vis[j] = 1;
          cout << ans[j] << '\n';
          break;
        }
      }
    }
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑用一个队列维护没有被用到的前缀，每次取出用或者取出拓展，注意到拓展到 $n$ 个时就不用扩展 $2$ 个了，因为一定够用了。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e3+114;
string S[maxn];
vector<int> query[maxn];
queue<string> q;
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		query[x].push_back(i);
	}
	string emp;
	q.push(emp);
	int t=0;
	for(int i=1;i<=1000;i++){
		if(q.size()==0){
			if(t<n){
				cout<<"NO\n";
				return 0;
			}
			break;
		}
		while((int)q.front().size()<i){
			if(q.size()<1000){
				string s=q.front();
				q.pop();
				q.push(s+'0');
				q.push(s+'1');
			}else{
				string s=q.front();
				q.pop();
				q.push(s+'0');
			}
		}
		for(int x:query[i]){
			if(q.size()==0){
				cout<<"NO\n";
				return 0;
			}
			t++;
			S[x]=q.front();
			q.pop();
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<S[i]<<'\n';
	return 0;
}

```

---

## 作者：Drind (赞：0)

### 题目解析

首先我们发现这道题很像哈夫曼树，所以我们先考虑建一棵字典树。我们直接在字典树上 dfs 即可，如果遇到空节点就打开，如果深度等于自己的长度就记录答案，如果遇到前面字符串的结束点就返回（因为前面的字符串是再往下走构造出的字符串的前缀）。记录答案的时候开 1000 个 deque 记录即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int tr[N][2];
int val[N];

struct node{
	int val,id;
}a[N];

int cnt,flag;

deque<int>q[1001];

void dfs(int u,int step,int fnl,int id){
	if(val[u]==1) return;
	if(step==fnl){
		val[u]|=1; flag=1;
		return;
	}
	for(int i=0;i<2;i++){
		if(!tr[u][i]) tr[u][i]=++cnt;
		q[id].push_front(i);
		dfs(tr[u][i],step+1,fnl,id);
		if(flag==1) break;
		q[id].pop_front();
	}
}

inline void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].val,a[i].id=i;
	sort(a+1,a+n+1,[](node x,node y){
		return x.val<y.val;
	});
	int u=0;
	for(int i=1;i<=n;i++){
		flag=0;
		dfs(0,0,a[i].val,a[i].id);
		if(flag==0){
			cout<<"NO\n"; return;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		while(!q[i].empty()){
			cout<<q[i].back(); q[i].pop_back();
		}
		cout<<"\n";
	}
}

int main(){
	ios::sync_with_stdio(false); 
	int t; t=1;
	while(t--) fake_main(); 
}
```

---

## 作者：yanhao40340 (赞：0)

前置知识：[字典树](https://www.luogu.com.cn/problem/P8306)。

### 题意

构造 $n$ 个 $01$ 字符串，使得没有一个字符串是另一个的前缀。

### 分析

看到前缀，第一反应当然就是字典树啦。

可以用 $\text{tag}$ 数组记录该点是不是一个字符串的结尾。

每次在字典树上插入字符串时，如果遇到打过标记的点，那么就停止搜索。

如果不论怎样插入都不行，那么就返回无解。

否则可以在每一次插入时记录答案。

时间复杂度：$O(|S|^2)$，其中 $S$ 表示最长的字符串。

### 坑点

1. 本题没有 $\text{spj}$，需要按顺序输出每一个字符串。

2. 字典树要开三倍空间。

### 代码

代码中的 $\text{fa}$ 好像并没有什么用，可删（~~但是我懒~~）。

```cpp
const int maxn=3010;//十年OI一场空，没开三倍见祖宗
struct trie{int ls,rs,fa;} tr[maxn];
string ans[maxn];bool tag[maxn];
bool Insert(int len,int x,string now){//字典树插入操作
	if (tag[x]) return false;//如果碰到标记，那么返回 false
	if (len==0) return ans[++tot]=now,tag[x]=true;//插入成功，记录答案
	now.push_back('0');//尝试在后面加0
	if (tr[x].ls){if (Insert(len-1,tr[x].ls,now)) return true;}//模板
	else{//开点
		tr[++cnt].fa=x;tr[x].ls=cnt;
		if (Insert(len-1,cnt,now)) return true;
	}
	*(--now.end())='1';//尝试在后面加1
	if (tr[x].rs){if (Insert(len-1,tr[x].rs,now)) return true;}
	else{
		tr[++cnt].fa=x;tr[x].rs=cnt;
		if (Insert(len-1,cnt,now)) return true;
	}
	return false;//如果都不行，返回false
}
```

完整代码（不是用来抄的）见 [link](https://codeforces.com/contest/37/submission/170118881)。

---

## 作者：XL4453 (赞：0)

### 解题思路：

简单构造题。

首先判断是否可行，发现每一个长度为 $1$ 的编码相当于占用了两个长度为 $2$ 的编码，四个长度为 $3$ 的编码，以此类推。

想到可以将一个长度为 $0$ 的编码的“权”设定为 $1$，然后根据这个推出其他的编码权值，如果所有的编码权值之和大于 $1$，则一定无解，反之一定有解，这个是显然的，就不赘述证明了。

然后就是构造解，可以强制规定按照长度排好序之后编码的字典序严格单调递增，那么直接在上一个的基础上末位加一即可。

---
### 解题花絮

其实就是一个哈夫曼编码题，一开始我想到的是给每一个数按照其长度给定权值，然后按照一般的哈夫曼编码做，随即发现自己想复杂了，然后就按照前面的方法写了。

---
### 代码：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct str{
	int len,id;
	int num[1005];
	bool operator <(str a){
		return len<a.len;
	}
}num[10005];
bool cmp(str a,str b){
	return a.id<b.id;
}
int n,max_len,now[10005],len,fi;
double tot;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i].len);
		max_len=max(max_len,num[i].len);
		tot+=pow(2,-num[i].len);
		num[i].id=i;
	}
	if(tot>1.0){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	sort(num+1,num+n+1);
	fi=1;
	for(int i=1;i<=n;i++){
		if(len<num[i].len){
			if(fi==0)now[len]++;
			len=num[i].len,fi=1;
		}
		if(!fi)now[len]++;
		for(int j=len;j>=1;j--){
			if(now[j]==2){
				now[j-1]++;
				now[j]=0;
			}
		}
		for(int j=1;j<=len;j++)num[i].num[j]=now[j];
		fi=0;
	}
	sort(num+1,num+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=num[i].len;j++){
			printf("%d",num[i].num[j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：灵光一闪 (赞：0)

~~抢头一篇题解！~~

这题做的我心累……

思路：从最小的数位开始向上枚举，如果发现不能继续了，就``puts("NO");``不然就一直枚举，然后就可以整理整理输出了~

Tip:注意顺序 ~~，这题木有spj~~

代码分开讲~

需要的头文件：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<map>
#include<string>
#include<vector>
```
定义环节：
```
map<int,int> mp;//用来装每种长度有多少个
vector<string> ans;//答案不解释
vector<int> v;//去重排序，枚举时用
vector<int> vv;//既无去重也无排序，用于保存顺序
map<int,bool> vvmp;//vv的某一个元素是否用过
map<int,bool> ansmp;//同上，不过是ans的
string last;//枚举的
int n;//不解释
int a;//长度
```
函数：
```
string add(string s){//主要实现2进制加1
    s[s.size()-1]++;//先给末位+1
    for(int i=s.size()-1;i>0;i--){//循环判断是不是合法
        if(s[i]=='2'){
            s[i]='0';
            s[i-1]++;
        }
    }
    if(s[0]=='2'){//如果首位都为2就GG了
        return "no";
    }
    else{
        return s;//不然都返回
    }
}
```
主程序：
```
int main(){//懂了每个变量的意思的话就很好理解了
    v.clear();
    last.clear();
    cin>>n;
    for(int i=0;i<n;i++){//简单的循环
        cin>>a;
        vv.push_back(a);
        if(mp[a]==0){
            v.push_back(a);
        }
        mp[a]++;
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v[0];i++){//last的首值
        last+='0';
    }
    for(int i=0;i<v.size();i++){//循环ing
        for(int j=last.size();j<v[i];j++){//记得补全
            last+='0';
        }
        bool flag=false;
        while(1){//珂怕的"死循环"
            if(mp[v[i]]==0){//如果这种长度的全用完了
                break;//终止
            }
            if(flag){//第一个是不加1的
                last=add(last);
            }
            if(last.substr(0,2)=="no"){//错误qaq
            //Tip:这里last.substr是为了防止在下面循环外面的if里的add函数返回值是no
                puts("NO");
                return 0;
            }
            flag=true;//第一个过去了……
            ans.push_back(last);//fire!完美丢进vector里~
            mp[v[i]]--;
        }
        if(flag){//如果上一个循环至少循环了一次的话就说明这个前缀不能用了
           last=add(last);//所以++；
        }
    }
    puts("YES");//构造完成！
    for(int j=0;j<vv.size();j++){
        if(vvmp[j]){//Aya，这个用过了……
            continue;
        }
        for(int i=0;i<n;i++){
            if(ansmp[i]){//Aya，这个也用过了……
                continue;
            }
            if(vv[j]==ans[i].size()){
                cout<<ans[i]<<endl;//输出
                vvmp[j]=true;
                ansmp[i]=true;//标记为用过了
                break;//开始下一个~
            }
        }
    }
    return 0;//结束！AC，
}
```
The End.

哦不不不，还有完整程序！~~（从厕所跑回来的作者~~

给完整程序是为了能让查错好看一点，不是抄袭哟亲~
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<map>
#include<string>
#include<vector>
using namespace std;
map<int,int> mp;
vector<string> ans;
vector<int> v;
vector<int> vv;
map<int,bool> vvmp;
map<int,bool> ansmp;
string last;
int n;
int a;
//string s;
string add(string s){
    s[s.size()-1]++;
    for(int i=s.size()-1;i>0;i--){
        if(s[i]=='2'){
            s[i]='0';
            s[i-1]++;
        }
    }
    if(s[0]=='2'){
        return "no";
    }
    else{
        return s;
    }
}
int main(){
    v.clear();
    last.clear();
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a;
        vv.push_back(a);
        if(mp[a]==0){
            v.push_back(a);
        }
        mp[a]++;
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v[0];i++){
        last+='0';
    }
    for(int i=0;i<v.size();i++){
        for(int j=last.size();j<v[i];j++){
            last+='0';
        }
        bool flag=false;
        while(1){
            if(mp[v[i]]==0){
                break;
            }
            if(flag){
                last=add(last);
            }
            if(last.substr(0,2)=="no"){
                puts("NO");
                return 0;
            }
            flag=true;
            ans.push_back(last);
            mp[v[i]]--;
        }
        if(flag){
           last=add(last);
        }
    }
    puts("YES");
    for(int j=0;j<vv.size();j++){
        if(vvmp[j]){
            continue;
        }
        for(int i=0;i<n;i++){
            if(ansmp[i]){
                continue;
            }
            if(vv[j]==ans[i].size()){
                cout<<ans[i]<<endl;
                vvmp[j]=true;
                ansmp[i]=true;
                break;
            }
        }
    }
    return 0;
}
```
The End.

---

