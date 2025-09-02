# [ZJOI2006] GameZ游戏排名系统

## 题目描述

GameZ为他们最新推出的游戏开通了一个网站。世界各地的玩家都可以将自己的游戏得分上传到网站上。这样就可以看到自己在世界上的排名。得分越高，排名就越靠前。当两个玩家的名次相同时，先上传记录者优先。由于新游戏的火爆，网站服务器已经难堪重负。为此GameZ雇用了你来帮他们重新开发一套新的核心。

排名系统通常要应付三种请求：上传一条新的得分记录、查询某个玩家的当前排名以及返回某个区段内的排名记录。当某个玩家上传自己最新的得分记录时，他原有的得分记录会被删除。为了减轻服务器负担，在返回某个区段内的排名记录时，最多返回 $10$ 条记录。


## 说明/提示

20
+ADAM 1000000     加入ADAM的得分记录

+BOB 1000000       加入BOB的得分记录

+TOM 2000000       加入TOM的得分记录

+CATHY 10000000    加入CATHY的得分记录

?TOM               输出TOM目前排名

?1                  目前有记录的玩家总数为4，因此应输出第1名到第4名。

+DAM 100000        加入DAM的得分记录

+BOB 1200000       更新BOB的得分记录

+ADAM 900000      更新ADAM的得分记录（即使比原来的差）

+FRANK 12340000   加入FRANK的得分记录

+LEO 9000000       加入LEO的得分记录

+KAINE 9000000     加入KAINE的得分记录

+GRACE 8000000    加入GRACE的得分记录

+WALT 9000000      加入WALT的得分记录

+SANDY 8000000    加入SANDY的得分记录

+MICK 9000000      加入MICK的得分记录

+JACK 7320000      加入JACK的得分记录

?2                  目前有记录的玩家总数为12，因此应输出第2名到第11名。

?5                  输出第5名到第13名。

?KAINE             输出KAINE的排名

输入文件总大小不超过 2M。

NOTE：用 C++ 的 fstream 读大规模数据的效率较低

## 样例 #1

### 输入

```
20
+ADAM 1000000
+BOB 1000000 
+TOM 2000000
+CATHY 10000000
?TOM 
?1
+DAM 100000 
+BOB 1200000
+ADAM 900000 
+FRANK 12340000 
+LEO 9000000
+KAINE 9000000 
+GRACE 8000000 
+WALT 9000000 
+SANDY 8000000 
+MICK 9000000 
+JACK 7320000 
?2 
?5  
?KAINE```

### 输出

```
2
CATHY TOM ADAM BOB
CATHY LEO KAINE WALT MICK GRACE SANDY JACK TOM BOB
WALT MICK GRACE SANDY JACK TOM BOB ADAM DAM
4
```

# 题解

## 作者：浅色调 (赞：17)

~~HAOI2008也考了这题，一模一样！。~~
### Solution：

　　本题纯pbds模拟~~平衡树+hash~~。

　　这种动态加点、改值、查询排名和k大值的问题，直接想到平衡树。

　　题目中需要用到的信息有：字符串、得分、时刻，其中时刻就是该字符串得到当前分数是第几次操作，维护时刻是因为对于得分相同的字符串，时刻小的要排在前面。

　　我们用~~一棵Splay来维护~~pbds中的rb_tree来维护。

　　对于每个字符串，把其和插入的时刻进行map映射，然后每个节点以分数为第一关键字、时刻为第二关键字，构建平衡树。对于每种操作：1、插入节点，直接可以insert ; 2、改变节点分数和时刻，我们直接改为删除这个节点，并加入新的值的节点 ; 3、查询排名，我们有order_of_key ; 4、查询第k大值，我们有find_by_order。

　　只需要模拟就好了，减少了很多冗余的码农操作（pbds大法好！）

$\quad\;\;$欢迎来踩博客：[five20](http://www.cnblogs.com/five20/p/9690055.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！～）
### 代码：
```cpp
    /*Code by 520 -- 9.21*/
    #include<bits/stdc++.h>
    #include<ext/pb_ds/assoc_container.hpp>
    #include<ext/pb_ds/tree_policy.hpp>
    #define il inline
    #define ll long long
    #define RE register
    #define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
    #define Bor(i,a,b) for(RE int (i)=(b);(i)>=(a);(i)--)
    using namespace std;
    using namespace __gnu_pbds;
    const int N=500005;
    int n,val[N],cnt,tot;
    map<string,int> mp;
    string ss[N];
    struct node{
        int v,id;
        bool operator < (const node &x) const {return v==x.v?id<x.id:v>x.v;}
    };
    tree<node,null_type,less<node>,rb_tree_tag,tree_order_statistics_node_update> T;
    il bool isdig(char x){return x>='0'&&x<='9';}
    int main(){
        ios::sync_with_stdio(0);
        cin>>n;char c;string s;int x,tp;
        while(n--){
            cin>>c>>s;
            if(c=='+') {
                if(mp[s]) {
                    tp=mp[s],T.erase(node{val[tp],tp});tot--;
                }
                mp[s]=++cnt,cin>>val[cnt],T.insert(node{val[cnt],cnt});tot++;
                ss[cnt]=s;
            }
            else if(c=='?'&&!isdig(s[0])) {
                x=mp[s];cout<<T.order_of_key(node{val[x],x})+1<<endl;
            }
            else {
                x=0;
                For(i,0,s.size()-1) x=(x<<3)+(x<<1)+(s[i]^48);
                tp=min(tot,x+9);
                For(i,x-1,tp-1) cout<<ss[T.find_by_order(i)->id]<<' ';cout<<endl;
            }
        }
        return 0;
    } 
```

---

## 作者：JYTS (赞：6)

题意是~~很容易理解的~~，基本就是套个平衡树然后进行一些操作

[模板传送门](https://www.luogu.org/problemnew/show/P3369)

本人用的FHQ Treap以及一些~~非常慢~~的STL~~<map>~~还有~~<pair>~~
 
 基本的思路就是读取这个人的名字存到map里，然后就进行正常的FHQ的操作，因为有同分的情况所以要以两个关键词进行比较，这一部分就是本题的精髓,~~话不多说上代码~~
 ```cpp
#include <bits/stdc++.h>
#define re register int
#define INF 1e9
#define N 260000
using namespace std;
int read()
{
    int sum=0,fg=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fg=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){sum=sum*10+ch-'0';ch=getchar();}
    return sum*fg;
}
struct noode
{
    long long val,tim;
};
map<string,noode>player;
map<pair<int,int>,string>players;//这里可以存到节点里面去，或者用结构体，但本人懒得（不会）重载运算符
struct node
{
    int siz,key,lch,rch;//key为rand值
    noode val;
}t[N];
int n,m;
int tot,root;
int _add_new_point(noode val)
{
    t[++tot].siz=1;
    t[tot].val=val;
    t[tot].key=rand();
    t[tot].lch=t[tot].rch=0;
    return tot;
}
void updata(int p)
{
    t[p].siz=t[t[p].lch].siz+t[t[p].rch].siz+1;
}
bool judge(int x,noode val)//核心部分
{
    if(t[x].val.val==val.val)return t[x].val.tim<=val.tim;
    else return t[x].val.val>val.val;
}
void split(int now,int &a,int &b,noode val)
{
    if(now==0){a=b=0;return;}
    if(judge(now,val))
    {
        a=now;split(t[now].rch,t[a].rch,b,val);
    }
    else
    {
        b=now;split(t[now].lch,a,t[b].lch,val);
    }
    updata(now);
}
void _merge(int &now,int a,int b)//将a,b合并给now
{
    if(a==0||b==0){now=a+b;return;}
    //key=rand
    if(t[a].key<t[b].key)
    {
        now=a;_merge(t[now].rch,t[a].rch,b);
    }
    else
    {
        now=b;_merge(t[now].lch,a,t[b].lch);
    }
    updata(now);
}
void _insert(noode val)
{
    int x=0,y=0,z;
    z=_add_new_point(val);
    split(root,x,y,val);
    _merge(x,x,z);
    _merge(root,x,y);
}
void _del(noode val)
{
    int x=0,y=0,z=0;
    split(root,x,y,val);
    val.tim--;
    split(x,x,z,val);
    _merge(z,t[z].lch,t[z].rch);
    _merge(x,x,z);
    _merge(root,x,y);
}
void _rank(noode val)
{
    val.tim--;
    int x=0,y=0;
    split(root,x,y,val);
    printf("%d\n",t[x].siz+1);
    _merge(root,x,y);
}
void _find(int now,int _rank)
{
    while(t[t[now].lch].siz+1!=_rank)
    {
        if(t[t[now].lch].siz>=_rank)now=t[now].lch;
        else _rank-=(t[t[now].lch].siz+1),now=t[now].rch;
    }
    cout<<players[make_pair(t[now].val.val,t[now].val.tim)]<<' ';
}
int main()
{
    srand(time(NULL));//19260817毕竟太暴力了..
    scanf("%d",&n);
    string s;
    for(int i=1;i<=n;i++)
    {
        s.clear();
        cin>>s;
        switch(s[0])
        {
            case '+':if(s[1]<='Z'&&s[1]>='A')
                    {
                        s.erase(s.begin());
                        if(player.count(s))
                        {
                            noode w;
                            scanf("%lld",&w.val);w.tim=i;
                            _del(player[s]);
                            player[s]=w;
                            players[make_pair(w.val,w.tim)]=s;
                            _insert(w);
                        }
                        else
                        {
                            noode w;
                            scanf("%lld",&w.val);w.tim=i;
                            player[s]=w;
                            players[make_pair(w.val,w.tim)]=s;
                            _insert(w);
                        }
                    }
                    break;
            case '?':
            if(s[1]<='Z'&&s[1]>='A')
            {
                s.erase(s.begin());
                _rank(player[s]);
            }
            else
            {
                int opps=0;
                for(int j=1;j<s.size();j++)
                {
                    opps=opps*10+s[j]-'0';
                }
                for(int j=0;j<10;j++)
                {
                    if(t[root].siz<opps+j)break;
                    _find(root,opps+j);
                }
                printf("\n");
            }
            break;
        }
    }
    return 0;
}

```

---

## 作者：沧海映繁星 (赞：4)

### 引言

看了一下，这道题都没有巨佬使用这种思路

本蒟蒻再在这里提供一种我自认为比较巧（tōu）妙（lǎn）的做法

### 思路

最初看到这个题，我高兴坏了，这不就和splay模板一样吗？~~又可以水一道紫题了~~

然后，我发现我错了……

因为这个题目里存在排名系统，会出现多个人使用一个分数的情况

好吧，看起来似乎是只能在树的节点上建链了……

想想就头大有木有？好麻烦的……

于是乎，本蒟蒻开始寻找其（tōu）他（lǎn）的方法

重新读题，发现一个有趣的事情：人数最多1e6,也就是说同一个分数最多1e6个人在使用（但这看起来好像并没有什么用）

仔细想想：如果我们把每个人的分数乘上1e6，那就是说，无论如何离它最近的分数也会差个1e6

这相当于是分块的思想，将它们的分数划分成区间长度为1e6的若干个区间，区间范围为n * 1e6  ~  （n - 1）* 1e6 + 1，其中n为输入的分数，至于为什么是这么分和后面的某些处理有关

根据题意：相同分数先传者排名高

于是乎，我们在每个分数入的时候，在分数上减去当前指令编号 i 的值（反正指令也就那么多，就算减了也不可能会到下一个区间的）

自由就是一些奇奇怪怪的细节了，比如怎么输入输出什么的，并不难处理
~~（个人表示被卡了很久）~~

额……好像有点抽象，但我实在不知道怎么画图，所以不懂的同学请看代码（内附部分解释）

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 1000005
int n,m,rt,tot,fa[maxn],ch[maxn][2],sz[maxn],cnt[maxn],val[maxn];
string s,name[maxn];
map<string,int> p;
int read(){
	int x = 0,f = 1;
	char s = getchar();
	while(s < '0' || s > '9'){
		if(s == '-') f = -1;
		s = getchar();
	}
	while(s >= '0' && s <= '9'){
		x = (x << 1) + (x << 3) + s - '0';
		s = getchar();
	}
	return x * f;
}
void maintain(int x){sz[x] = sz[ch[x][1]] + sz[ch[x][0]] + cnt[x];}
bool get(int x){return x == ch[fa[x]][1];}
void clear(int x){ch[x][1] = ch[x][0] = val[x] = cnt[x] = fa[x] = 0;}
void rotate(int x){
	int y = fa[x],z = fa[y],chk = get(x);
	ch[y][chk] = ch[x][chk ^ 1];
	if(ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
	ch[x][chk ^ 1] = y;
	fa[x] = z;fa[y] = x;
	if(z) ch[z][y == ch[z][1]] = x;
	maintain(y);maintain(x);
}
void splay(int x){
	for(int f = fa[x];f = fa[x],f;rotate(x)) if(fa[f]) rotate(get(x) == get(f) ? f : x);
	rt = x;
}
void ins(int k){
	if(!rt){
		val[tot] = k;
		cnt[tot]++;
		rt = tot;
		maintain(tot);
		return;
	}
	int cur = rt,f = 0;
	while(1){
		if(k == val[cur]){
			cnt[cur]++;
			maintain(cur);
			maintain(f);
			splay(tot);
			return;
		}
		f = cur;cur = ch[cur][val[cur] < k];
		if(!cur){
			val[tot] = k;
			cnt[tot]++;
			fa[tot] = f;
			ch[f][val[f] < k] = tot;
			maintain(tot);
			maintain(f);
			splay(tot);
			return;
		}
	}
}
int rk(int k){
	int cur = rt,s = 0;
	while(1){
		if(k < val[cur]) cur = ch[cur][0];
		else{
			s += sz[ch[cur][0]];
			if(k == val[cur]){
				splay(cur);
				return s + 1;
			}
			s += cnt[cur];
			cur = ch[cur][1];
		}
	}
}
int kth(int k){
	int cur = rt;
	while(1){
		if(k <= sz[ch[cur][0]]) cur = ch[cur][0];
		else{
			k -= sz[ch[cur][0]] + cnt[cur];
			if(k <= 0){
				splay(cur);
				return cur;
			}
			cur = ch[cur][1];
		}
	}
}
int pre(){
	int cur = ch[rt][0];
	while(ch[cur][1]) cur = ch[cur][1];
	splay(cur);
	return cur;
}
int nxt(){
	int cur = ch[rt][1];
	while(ch[cur][0]) cur = ch[cur][0];
	splay(cur);
	return cur;
}
void del(int k){
	rk(k);
	if(cnt[rt] > 1){
		cnt[rt]--;
		maintain(rt);
		return;
	}
	if(!ch[rt][0] && !ch[rt][1]){
		clear(rt);
		rt = 0;
		return;
	}
	if(!ch[rt][0]){
		int cur = rt;
		rt = ch[rt][1];
		fa[rt] = 0;
		clear(cur);
		return;
	}
	if(!ch[rt][1]){
		int cur = rt;
		rt = ch[rt][0];
		fa[rt] = 0;
		clear(cur);
		return;
	}
	int cur = rt,x = pre();
	ch[x][1] = ch[cur][1];
	fa[ch[cur][1]] = x;
	rt = x;
	clear(cur);
	maintain(x);
	return;
}//从这里往上都是splay模板 
int number(){
	int len = s.size(),x = 0;
	for(int i = 0; i < len; i++) x = (x << 1) + (x << 3) + s[i] - '0';
	return x; 
}
void query(int k){
	for(int i = k; i < min(k + 10,sz[rt] + 1); i++){
		cout << name[kth(i)] << " ";
	}
	puts("");
}
signed main(){
	char t;
	n = read();
	for(int i = 1; i <= n; i++){
		cin >> t;tot++;
		if(t == '+'){
			cin >> name[i];
			if(p[name[i]]) del(p[name[i]]);
			p[name[i]] = read() * -1000000 + tot; 
            		//这句话是重点！！！！！ 
			ins(p[name[i]]);
		}
		if(t == '?'){
			cin >> s;
			if(s[0] >= '0' && s[0] <= '9') query(number());
			else printf("%lld\n",rk(p[s]));
		}
	}
}
```


---

## 作者：G_hz (赞：3)

这个题一开始犯傻，WA了半页。。。

既然没有指针版SBT那我就写一个好了

思路就是输入一个人的分数时，分别用开两个map分别保存TA的分数和这个分数对应的名字，介于有可能存在重复的分数，而分数<1e8所以我们就把分数\*1e8再加上它的操作编号（第几个），就可以避免这个问题。

对于修改操作我们就把它的值删掉，再插入新的值便可。

下面是蒟蒻的代码：

        
```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<map>
#define x 19260817
using namespace std;
int n;
long long a;
char c,ss[100000];
string s;
map<int,long long>score;
map<long long,string>name;
typedef struct Node{
    Node *l,*r;
    int size,cnt;
    long long val;
}SBT,*LE;
LE Null,root;
void L_Rotate(LE&k){
    LE tmp=k->r;
    k->r=tmp->l;
    tmp->l=k;
    tmp->size=k->size;
    k->size=k->l->size+k->r->size+1;
    k=tmp;
}
void R_Rotate(LE&k){
    LE tmp=k->l;
    k->l=tmp->r;
    tmp->r=k;
    tmp->size=k->size;
    k->size=k->l->size+k->r->size+1;
    k=tmp;
}
void Insert(LE&k,long long val){
    if(k==Null){
        k=new Node;
        k->l=k->r=Null;
        k->val=val;
        k->cnt=k->size=1;
        return;
    }
    k->size++;
    if(val<k->val){
        Insert(k->l,val);
        if(k->l->l->size>k->r->size)
            R_Rotate(k);
    }
    else
    if(val>k->val){
        Insert(k->r,val);
        if(k->r->r->size>k->l->size)
            L_Rotate(k);
    }
    else
    if(k->val==val){
        k->cnt++;
        return;
    }
}
void Delete(LE&k,long long val,int cnt){
    if(k==Null)return;
    k->size-=cnt;
    if(k->val>val)
        Delete(k->l,val,cnt);
    if(k->val<val)
        Delete(k->r,val,cnt);
    if(k->val==val){
        k->cnt-=cnt;
        if(k->cnt!=0)return;
        if(k->l==Null)
            k=k->r;
        else
        if(k->r==Null)
            k=k->l;
        else{
            LE tmp=k->l;
            while(tmp->r!=Null){
                tmp=tmp->r;
            }
            k->val=tmp->val;
            k->cnt=tmp->cnt;
            Delete(k->l,k->val,k->cnt);
            return;
        }
    }
}
int Query_rank(LE k,long long val,int &Cnt){
    if(k==Null)return 1;
    if(k->val==val){
        Cnt=k->cnt;
        return k->l->size+1;
    }
    if(k->val>val)return Query_rank(k->l,val,Cnt);
    if(k->val<val)return Query_rank(k->r,val,Cnt)+k->l->size+1;
}
long long Query_num(LE k,int rank){
    if(k==Null)return 0;
    if(k->l->size>=rank)return Query_num(k->l,rank);
    if(k->l->size+k->cnt>=rank)return k->val;
    rank=rank-(k->l->size+1);
    Query_num(k->r,rank);
}
int main()
{
    Null=new Node;
    Null->l=Null->r=Null;
    Null->size=Null->cnt=0;
    Null->val=-1;
    root=Null;
    scanf("%d",&n);
    int k=n;
    while(k--){
        int hash=0;
        s.clear();
        scanf("\n%c",&c);
        if(c=='+'){
            cin>>s;
            int l=s.size();
            int cc=x;
            for(int i=0;i<l;i++){
                hash+=cc*s[i];
                cc=cc*x;
            }
            scanf("%lld",&a);
            a=a*100000000+k;
            if(score[hash]!=0)
                Delete(root,score[hash],1);
            name[a]=s;
            score[hash]=a;
            Insert(root,a);
        }
        if(c=='?'){
            cin>>s;
            if(s[0]>'9'||s[0]<'0'){
                int l=s.size();
                int cc=x;
                for(int i=0;i<l;i++){
                    hash+=cc*s[i];
                    cc=cc*x;
                }
                long long val=score[hash];
                int aa;
                printf("%d\n",root->size-Query_rank(root,val,aa)+1);
            }    
            else{
                int l=s.size();
                int cc=1;
                int rank=0;
                for(int i=l-1;i>=0;i--){
                    rank+=cc*(s[i]-'0');
                    cc=cc*10;
                }
                for(int i=0;i<10;i++){
                    if(rank+i>root->size)break;
                    long long val=Query_num(root,root->size-rank-i+1);
                    cout<<name[val]<<' ';
                }
                putchar(10);
            }
        }
    }
    return 0;
}
```

---

## 作者：jxcakak (赞：3)

用好平板电视（pb\_ds）库能省下不少代码量

就是开两个平衡树，一个是得分->名字，一个是名字的哈希值->得分

得分要开双关键字，存成绩和插入时间

```cpp
#include<cstdio>
#include<string>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
struct data{
    int score,cnt;
    bool operator<(const data&t)const{return score==t.score?cnt<t.cnt:score>t.score;}
};
tree<data,string,less<data>,rb_tree_tag,tree_order_statistics_node_update> T; //得分->名字
tree<int,data,less<int>,rb_tree_tag> M;//名字的哈希值->得分
string getstr(){char c[1001]; scanf("%s",c); return c;}//读入字符串
int f(string s){//哈希
    unsigned int ans=0;
    for(int i=0;i<s.size();++i) ans=ans*131+s[i];
    return ans%(1LL<<31);
}
int main(){
    int n; scanf("%d",&n);
    for(int i=1;i<=n;++i){
        char c=getchar(); for(;c!='+'&&c!='?';c=getchar());
        if(c=='+'){
            string s=getstr(); int x; scanf("%d",&x); data t={x,i};
            tree<int,data,less<int>,rb_tree_tag>::iterator it=M.find(f(s));
            if(it!=M.end()){//如果存在就替换
                T.erase(it->second); M.erase(it);
            }
            T.insert(make_pair(t,s)); M.insert(make_pair(f(s),t));
        }else if(c=='?'){
            string s=getstr(); if(isalpha(s[0]))
                printf("%d\n",T.order_of_key(M.find(f(s))->second)+1);//询问排名
            else{
                int t=0; for(int j=0;j<s.size();++j) t=t*10+s[j]-'0';
                for(int j=t;j<=t+9;++j){//询问第t-t+9名的人的名字
                    if(j>T.size()) break;
                    printf("%s ",T.find_by_order(j-1)->second.data());
                }
                printf("\n");
            }
        }
    }
    return 0;
}
```

---

## 作者：Log_x (赞：3)

显然这是一道Splay，然而被各种细节和自身蒟蒻坑成傻逼……

**分析:**楼下已经讲的差不多了，这里给出几点补充

(1)输出排名的时候要求按双关键字(得分【高分在前】-最近一次上传得分的时间【上传早在前】)排序(然而恶心的题目只字未提QAQ)，不过事实上只要在树上添加一个域，然后在插入时稍加判断，那么剩下的就都是板了；

(2)由于记录的数量问题可能无法输出10条，因此在伸展时应与总节点数取最小值；

(3)由于要通过伸展把10条排名记录输出，所有要先建两个哨兵(最大-最小，注意值取极端些，之前开不好一个点一直TLE……)(可能也不用开哨兵，毕竟我蒟蒻……但如果由于特殊情况只输出1条记录时，伸展会死循环)；

(4)Orz楼下神犇，字典树不知道比什么map,哈希高到哪里去了，目前数组Splay竟然拿了rank1

**代码:**



















```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int Maxn = 2147483647; //极端值 
const int N = 250005, M = 1e5;
int fa[N], lc[N], rc[N], sze[N], vis[N], len[N], pos[N], tag[N];
int n, m, E, T = 1, rt, tis, G[M][27];
char a[N][12], tp[12];
template <class T> inline T Min(T a, T b) {return a < b? a : b;}
inline int get()
{
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >='0' && ch <= '9')
        res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline void put(int x)
{
    if (x < 0)
      x = ~x + 1, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
inline void Push(int x)
{
    sze[x] = sze[lc[x]] + sze[rc[x]] + 1;
}
inline bool Wrt(int x) {return rc[fa[x]] == x;}
inline void Rot(int x)
{
    int y = fa[x], z = fa[y];
    int b = (lc[y] == x) ? rc[x] : lc[x];
    fa[x] = z; fa[y] = x;
    if (b) fa[b] = y;
    if (z) (y == lc[z] ? lc[z] : rc[z]) = x;
    if (x == lc[y]) rc[x] = y, lc[y] = b;
     else lc[x] = y, rc[y] = b;
    Push(y);
}
inline void Splay(int x, int tar)
{
    while (fa[x] != tar)
    {
        if (fa[fa[x]] != tar)
         Wrt(x) == Wrt(fa[x]) ? Rot(fa[x]) : Rot(x);
        Rot(x);
    }
    Push(x);
    if (!tar) rt = x;
}
inline void Ins(int t, int vi, int ti)
{
    int x = rt, y = 0, dir;
    while (x)
    {
        ++sze[y = x];
        if (vi > vis[x] || (vi == vis[x] && ti < pos[x])) x = rc[x], dir = 1; //双关键字 
         else x = lc[x], dir = 0;
    }
    fa[x = t] = y; sze[x] = 1; vis[x] = vi; pos[x] = ti;
     if (y) (dir == 1 ? rc[y] : lc[y]) = x;
    Splay(x, 0);
}
inline void Join(int x, int y)
{ 
    lc[fa[x]] = rc[fa[y]] = 0;
    int k = y;
    while (lc[k]) k = lc[k];
    lc[k] = x; fa[x] = k;
    fa[rt = y] = 0;
    Splay(k, 0);
}
inline void Del(int x)
{
    Splay(x, 0);
    if (!lc[x] || !rc[x])
     fa[rt = lc[x] + rc[x]] = 0; 
    else Join(lc[x], rc[x]);
}
inline int Getkth(int k)
{
    int x = rt;
    while (x)
    {
        if (k <= sze[rc[x]]) x = rc[x];
        else 
        {
            k -= sze[rc[x]] + 1;
            if (!k) return x;
            x = lc[x];
        }
    }
    return 0;
}
inline int Putkth(int x)
{
    if (!x) return 0;
    Splay(x, 0);
    return sze[rc[x]];
}
inline void Print(int x, int k)
{
    if (!x) return ;
    Print(rc[x], k);
    for (int i = 0; i < len[x]; ++i) putchar(a[x][i]);
    putchar(k != x ? ' ' : '\n');
    Print(lc[x], k); 
}
inline void Que(int k)
{
    int x = Getkth(Min(sze[rt], k + 11)),  
        y = Getkth(k), z;
    Splay(x, 0); Splay(y, x);
    z = lc[y]; 
    while (lc[z]) z = lc[z];
    Print(lc[y], z); 
}
inline int TrAsk(char *s, int L)
{
    int x = 1;
    for (int i = 0; i < L; ++i) x = G[x][s[i] - 'A'];
    return tag[x];
}
inline void TrIns(char *s, int L)
{
    int x = 1, y; 
    for (int i = 0; i < L; ++i)
    {
        y = s[i] - 'A';
        if (!G[x][y]) G[x][y] = ++T;
        x = G[x][y];
    }
    if (!tag[x])
    {
        Ins(tag[x] = ++E, get(), ++tis);
        len[E] = L;
        for (int i = 0; i < L; ++i) a[E][i] = s[i];
        a[E][L] = '\0';
    }
    else Del(tag[x]), Ins(tag[x], get(), ++tis);
}
int main()
{
    n = get(); 
    char cr, fr; int u, v, l;
    Ins(++E, -Maxn, 0); 
    Ins(++E, Maxn, Maxn); //哨兵 
    while (n--)
    {
        l = 0;
        while ((fr = getchar()) != '+' && fr != '?');
        while (((cr = getchar()) >= 'A' && cr <= 'Z') || (cr >= '0' && cr <= '9')) tp[l++] = cr;
        if (fr == '+') TrIns(tp, l);
        else if (tp[0] >= '0' && tp[0] <= '9')
        {
            u = 0;
            for (int i = 0; i < l; ++i)
             u = (u << 3) + (u << 1) + tp[i] - '0';
            Que(u);
        }
        else put(Putkth(TrAsk(tp, l))), putchar('\n');
    }
    return 0;
}
```

---

## 作者：xuyuansu (赞：2)

## 简要题意
给你每个人的分数更新信息，要求查询某些人的排名和某个排名区间的人。
## 题解
对于这种排名类题目，毫无疑问FHQtreap是非常适合的，在平衡树中按分数为第一关键字，更新时间为第二关键字排序，这些是比较基础的操作，不多解释，详细看代码。

在根据人名找排名的时候，我们用map存下人的分数和更新时间。在排名类问题中，一般每个对象的信息都是比较独特的，也就是说我们完全可以在平衡树之外维护对象的有关信息，在平衡树中查找的时候可以根据这些信息来找到对象，在这道题中一个时间的对象是唯一的，所以根据分数和时间可以找到对象。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
int n,pri[N],siz[N],son[N][2],cnt,root;
struct node
{
	ll s;int t;string name;
	node (){s=t=0;}
	bool operator < (const node &a)const
	{
		if(s!=a.s) return s<a.s;
		return t>a.t;
	}
}val[N];
map<string,node> m;
int add(ll x,int y,string s)
{
	siz[++cnt]=1;pri[cnt]=rand();val[cnt].s=x;val[cnt].t=y;val[cnt].name=s;return cnt;
}
void update(int x)
{
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}
void split1(int rt,int &x,int &y,node z)//按照权值分裂
{
	if(!rt)
	{
		x=y=0;return;
	}
	if(z<val[rt])
	{
		y=rt;split1(son[rt][0],x,son[y][0],z);
	}
	else x=rt,split1(son[rt][1],son[x][1],y,z);
	update(rt);
}
void split2(int rt,int &x,int &y,int z)//按照大小分裂
{
	if(!rt)
	{
		x=y=0;return;
	}
	if(siz[son[rt][0]]>=z)
	{
		y=rt;split2(son[rt][0],x,son[y][0],z);
	}
	else x=rt,split2(son[rt][1],son[x][1],y,z-siz[son[rt][0]]-1);
	update(rt);
}
int merge(int x,int y)
{
	if(!x || !y) return x+y;
	if(pri[x]<pri[y])
	{
		son[x][1]=merge(son[x][1],y);
		update(x);return x;
	}
	son[y][0]=merge(x,son[y][0]);
	update(y);return y;
}
void insert(int x)
{
	int r1,r2;
	split1(root,r1,r2,val[x]);
	root=merge(r1,merge(x,r2));
}
void print(int x)//遍历
{
	if(son[x][1]) print(son[x][1]);
	cout<<val[x].name<<" ";
	if(son[x][0]) print(son[x][0]);
}
void query(int x)
{
	x=siz[root]-x+1;
	int r1,r2,r3;
	split2(root,r1,r2,x);
	if(siz[r1]>10)
	{
		split2(r1,r1,r3,siz[r1]-10),print(r3);
		root=merge(merge(r1,r3),r2);
	}
	else{
		print(r1);root=merge(r1,r2);
	}
	printf("\n");
}
void queryrank(node x)
{
	int r1,r2;
	split1(root,r1,r2,x);
	printf("%d\n",siz[r2]+1);
	root=merge(r1,r2);
}
int main()
{
	srand(19260817);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char opt;string name;ll x;
		cin>>opt>>name;
		if(opt=='+')
		{
			 scanf("%lld",&x);
			 int r1,r2,r3;
			 if(m[name].t!=0)
			 {
				 split1(root,r1,r3,m[name]);
				 split2(r1,r1,r2,siz[r1]-1);
				 root=merge(r1,r3);
				 val[r2].s=x;val[r2].t=i;
			 }
			 else r2=add(x,i,name),m[name].name=name;
			 m[name].t=i;m[name].s=x;
			 insert(r2);
		}
		else{
			if(name[0]>='0' && name[0]<='9')
			{
				x=name[0]-'0';
				for(int j=1;j<(int)name.size();j++) x=x*10+name[j]-'0';
				query(x);
			}
			else queryrank(m[name]);
		}
	}
	return 0;
}

```
[双倍经验](https://www.luogu.com.cn/problem/P4291)

---

## 作者：_luanyi_ (赞：2)

平衡树好题，本人使用 fhq。  
观察本题，发现本题与一般的 fhq 题目有些许不同：
 - 需要支持按排名分裂或者按权值分裂，分别实现即可；
 - 分数相同按时间排序，可以双关键字排序，但笔者使用了按照（分数 $\times260000+$ 时间（时间为倒序））作为节点的权值，排序起来更方便~~其实本质还是双关键字排序~~。

接下来分析题目所给的操作。

## 上传分数

我们给每个人编号，如果这个名字以前没有被编过号，就编一个号，并把权值扔进 fhq 中；如果这个名字已经编过号了，就把旧的权值删除，更新权值（外部数组记录），并将新权值扔进 fhq 中。

## 查询排名

对于输入给定的名字，先查阅其编号，再用外部数组查他的权值，将 fhq 按权值分裂，得到他的排名。

## 查询名字

首先按排名分裂，由于笔者的 fhq 权值从小到大排，故需要先将排名取个反。  
之后就变成了在一棵子树中查询排名为 $1\sim\min(10,size)$ 的节点的编号，其中 $size$ 为子树大小。  
由于笔者不是很聪明，采用了 `for` 循环加暴力分裂合并的方法，常数巨大~~差点过不去~~。  
具体地，若查询排名为 $i$ 的节点的权值，则将 $i$ 作为关键字按排名分裂，再在左子树中将 $i-1$ 作为关键字按排名分裂，注意如果查询到为空就及时退出，防止 RE。  

## code

trick：字符串处理推荐用 string，用起来很方便，但它只能 cin 和 cout，此时可以关闭同步流**和将 endl 改为 \`\n\`**。（实测能快亿倍，学校 OJ 过不去就是这样卡过去的）  
关闭同步流的方法：

```cpp
ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);
```

但需注意之后只能 cin 和 cout，否则可能会出一些神奇的问题。

```cpp
#include <bits/stdc++.h>
#define fq(i,a,b) for (int i = (a); i <= (b); i++)
#define fnq(i,a,b) for (int i = (a); i < (b); i++)
#define nfq(i,a,b) for (int i = (a); i >= (b); i--)
#define nfnq(i,a,b) for (int i = (a); i > (b); i--)
#define fqs(i,a,b,c) for (int i = (a); i <= (b); i += (c))
#define fnqs(i,a,b,c) for (int i = (a); i < (b); i += (c))
#define nfqs(i,a,b,c) for (int i = (a); i >= (b); i -= (c))
#define nfnqs(i,a,b,c) for (int i = (a); i > (b); i -= (c))
#define elif else if
using namespace std;

#define int long long

//#define GRAPH
//const int EDGES = -1;
//const int VERTEXES = -1;
////# define EDGE_W
////typedef int W_TYPE;

//#define COMPLEX

inline int rd () {
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) (ch == '-' ? (f = -1) : 0), ch = getchar ();
	int num = 0;
	while (isdigit (ch)) num = num * 10 + ch - '0', ch = getchar ();
	return num * f;
}
#define d rd ()

inline int rd (const int modp) {
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) (ch == '-' ? (f = -1) : 0), ch = getchar ();
	int num = 0;
	while (isdigit (ch)) num = (num * 10 + ch - '0') % modp, ch = getchar ();
	return (num * f % modp + modp) % modp;
}

#ifdef GRAPH
struct Edge {
	int v, nxt;
# ifdef EDGE_W
	W_TYPE w;
# endif
	Edge () {}
# ifdef EDGE_W
	Edge (int _v, W_TYPE _w, int _nxt) {v = _v, w = _w, nxt = _nxt;}
# else
	Edge (int _v, int _nxt) {v = _v, nxt = _nxt;}
# endif
} edge[EDGES];
int head[VERTEXES], ecnt;
# ifdef EDGE_W
void addedge (int u, int v, W_TYPE w) {edge[++ecnt] = Edge (v, w, head[u]); head[u] = ecnt;}
#  define fe(u) for (int i = head[u], v, w; v = edge[i].v, w = edge[i].w, i; i = edge[i].nxt)
# else
void addedge (int u, int v) {edge[++ecnt] = Edge (v, head[u]); head[u] = ecnt;}
#  define fe(u) for (int i = head[u], v; v = edge[i].v, i; i = edge[i].nxt)
# endif
void init () {memset (head, 0, sizeof head); ecnt = 0;}
#endif

#ifdef COMPLEX
struct cpx {
	double a, b;
	cpx () {a = 0, b = 0;}
	cpx (double _a) {a = _a, b = 0;}
	cpx (double _a, double _b) {a = _a, b = _b;}
	friend cpx operator + (cpx a, cpx b) {return cpx (a.a + b.a, a.b + b.b);}
	friend cpx operator - (cpx a, cpx b) {return cpx (a.a - b.a, a.b - b.b);}
	friend cpx operator * (cpx a, cpx b) {return cpx (a.a * b.a - a.b * b.b, a.b * b.a + a.a * b.b);}
	friend cpx operator / (cpx a, cpx b) {return cpx ((a.a * b.a + a.b * b.b) / (b.b * b.b + b.a * b.a), (a.b * b.a - a.a * b.b) / (b.b * b.b + b.a * b.a));}
	friend cpx operator += (cpx &a, cpx b) {return a = a + b;}
	friend cpx operator -= (cpx &a, cpx b) {return a = a - b;}
	friend cpx operator *= (cpx &a, cpx b) {return a = a * b;}
	friend cpx operator /= (cpx &a, cpx b) {return a = a / b;}
};
#endif
// 以上均为码头，以下为主要程序 
const int maxn = 300300;
struct node {
	int l, r, pri, sz, key, id;
	node () {}
	node (int k, int i) {l = r = 0; sz = 1; key = k; id = i; pri = rand ();}
} tree[maxn]; int cnt;
#define sz(p) tree[p].sz
#define l(p) tree[p].l
#define r(p) tree[p].r
#define pri(p) tree[p].pri
#define key(p) tree[p].key
//开头5个宏，代码短一倍 
void push_up (int p) {sz (p) = sz (l (p)) + sz (r (p)) + 1;}
pair <int, int> split (int p, int k) {//按权值分裂，<k放左子树，>=k放右子树 
	if (!p) return make_pair (0, 0);
	if (k <= key (p)) {
		pair <int, int> q = split (l (p), k);
		l (p) = q.second;
		push_up (p);
		return make_pair (q.first, p);
	} else {
		pair <int, int> q = split (r (p), k);
		r (p) = q.first;
		push_up (p);
		return make_pair (p, q.second);
	}
}
pair <int, int> splitt (int p, int k) {//按排名分裂，<=k放左子树，>k放右子树 
	if (!k) return make_pair (0, p);
	if (!p) make_pair (0, 0);
	if (k <= sz (l (p))) {
		pair <int, int> q = splitt (l (p), k);
		l (p) = q.second; push_up (p);
		return make_pair (q.first, p);
	} elif (k == sz (l (p)) + 1) {
		int rr = r (p);
		r (p) = 0; push_up (p);
		return make_pair (p, rr);
	} else {
		pair <int, int> q = splitt (r (p), k - sz (l (p)) - 1);
		r (p) = q.first; push_up (p);
		return make_pair (p, q.second);
	}
}
int merge (int x, int y) {//合并 
	if (!x || !y) return x | y;
	if (pri (x) > pri (y)) {
		r (x) = merge (r (x), y);
		push_up (x);
		return x;
	} else {
		l (y) = merge (x, l (y));
		push_up (y);
		return y;
	}
}
int addnode (int id, int k) {tree[++cnt] = node (id, k); return cnt;}
int root;
void insert (int score, int id) {//插入 
	pair <int, int> q = split (root, score);
	root = merge (q.first, merge (addnode (score, id), q.second));
}
void erase (int score) {//删除 
	pair <int, int> q = split (root, score);
	pair <int, int> r = split (q.second, score + 1);
	root = merge (q.first, r.second);
}
map <string, int> mp; string mmp[maxn]; int ccnt; int sc[maxn];
const int shift = 260000;//乘以一个很大的数 
string s;
signed main () {
	ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);//关闭同步流 
	int m; cin >> m; while (m--) {
		cin >> s;
		if (s[0] == '+') { int x; cin >> x;
			s = s.substr (1);
			if (!mp[s]) {//这个名字没有被编过号 
				mp[s] = ++ccnt;
				mmp[ccnt] = s;
				sc[ccnt] = x * shift + m;
				insert (x * shift + m, ccnt);
			} else {//这个名字编过号 
				erase (sc[mp[s]]);
				sc[mp[s]] = x * shift + m;
				insert (x * shift + m, mp[s]);
			}
		} else {
			s = s.substr (1);
			if (isdigit (s[0])) {//给排名查询名字 
				int num = 0;
				for (auto c : s) num = num * 10 + c - '0';
				pair <int, int> q = splitt (root, sz (root) - num + 1);
				fq (i, 1, 10) {//暴力查询 
					if (sz (q.first) - i < 0) break;//及时退出
					pair <int, int> r = splitt (q.first, sz (q.first) - i);
					pair <int, int> t = splitt (r.second, 1);
					if (!t.first) {
						q.first = merge (r.first, merge (t.first, t.second));
						break;//及时退出之前不要忘记merge回来
					}
					cout << mmp[tree[t.first].id] << ' ';
					q.first = merge (r.first, merge (t.first, t.second));
				} cout << '\n'; root = merge (q.first, q.second);
			} else {//给名字查询排名 
				int score = sc[mp[s]];
				pair <int, int> q = split (root, score);
				cout << sz (q.second) << '\n';
				root = merge (q.first, q.second);
			}
		}
	}
	return 0;
}

/*
20
+A 1
+B 1
+C 2
+D 3
?1
*/

```

可以从代码看出，fhq 的优点还是代码短，好写，好处理，**易 debug**。

---

## 作者：BFSDFS123 (赞：1)

这道是一道 [双倍经验]( https://www.luogu.com.cn/problem/P4291 )

-----

本题是一道平衡树的模板题，对于想练习平衡树基本知识的同学们很有帮助。

~~但是我就是用 pb_ds 水了过去。~~

-----

我们对于每个名字，使用 map 存储名字的编号，并对每个编号，用一个数组存储这个编号的值。

对于每次更新，直接把这个位置的值删掉，再加入这个节点。（注意更新个平衡树数）

对于每次询问，利用 `` find_by_order(x) `` 和 `` T.order_of_key(x) `` 来处理问题。

就这样，一道平衡树的紫题就被我们在 80 行之内给水掉了！

-----

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp> 
using namespace std;
int cnt=0;
map<string,int> mp;
int val[250010];
struct Node{
	int v,id;
	bool operator<(const Node &rhs) const{
		if(v!=rhs.v)
		{
			return v>rhs.v;
		}
		return id<rhs.id;
	}
};
__gnu_pbds::tree<Node,__gnu_pbds::null_type,less<Node>,
				  __gnu_pbds::rb_tree_tag,
				  __gnu_pbds::tree_order_statistics_node_update>
T;
string Name[250010]; 
int main()
{
	int Case;
	scanf("%d",&Case);
	int tot=0;
	while(Case--)
	{
		char opt;
		string nm;
		cin>>opt>>nm;
		if(opt=='+')
		{
			if(mp[nm])
			{
				int pos=mp[nm];
				Node tmp;
				T.erase((Node){val[pos],pos});
				tot--;
			}
			mp[nm]=++cnt;
			scanf("%d",&val[cnt]);
			Node tmp;
			tmp.v=val[cnt];
			tmp.id=cnt;
			T.insert(tmp);
			Name[cnt]=nm;
			tot++;
		}else{
			if(isdigit(nm[0]))
			{
				int x=0;
				for(int i=0;i<nm.size();i++)
				{
					x=x*10+nm[i]-'0';
				}
				int N=min(tot,x+9);
				for(int i=x-1;i<=N-1;i++)
				{
					printf("%s ",Name[T.find_by_order(i)->id].c_str());
				}
				putchar('\n');
			}else{
				int id=mp[nm];
				printf("%d\n",T.order_of_key((Node){val[id],id})+1);
			}
		}
	}
	return 0;
}
```

因为 pb_ds 常数巨大，所以不开 O2 只有 90 分，最后一个点 TLE 1.07 秒。

当然，你加上快读和快输也是可以的——只是我懒得改

----

另附：根据 CCF 的最新规则，pb_ds 已经能在正规比赛中使用啦！好时代，来临力！！！

[pb_ds 简介](https://oi-wiki.org/lang/pb-ds/)

---

## 作者：fanypcd (赞：1)

蒟蒻刚学平衡树，来水一发


------------

### 前置芝士:
#### [FHQtreap-OIwiki](https://oi-wiki.org/ds/treap)


------------

### 前置题目:
#### [普通平衡树](https://www.luogu.com.cn/problem/P3369)


------------
### 题目简述：
要求维护一个数据结构，支持插入，删除，查询值的排名，查询连续的 10 名，且每个点是本质不同的。

### 题目思路：

使用无旋 treap ，暴力维护节点信息（左右孩子，值，名字）即可，再开一个 map 保存名字对应的节点编号

有一个重要的优化：本题需要维护两个值 $score$ 和 $count$ 。但注意到只有在 $score$ 相同的情况下才需要比较 $count$ ， 所以可以维护值 $v$ 为 $score*maxval-count$ ，其中 $maxval$ 表示 $score$ 能取到的最小值 与 $count$ 能取到的最大值之差的绝对值（当然可以比这个还大），这样就能保证在 $score$ 不同时 $count$ 不会影响比较结果


------------

### 两种 split 方式：
后文的 ```splitval``` 和 ```splitrnk``` 分别是按值分裂和按排名分裂（在 OIwiki 中讲得不太清楚，所以我提一嘴）。

**按值分裂**，也是 OIwiki 中的代码实现，即 ```splitval(root, v, x, y)``` ，功能是将以 root 为根节点的子树分裂成两棵树，一个树所有节点的值小于（可以是小于等于，但是改为小于等于需要相应修改后面的查询时传递的参数） v ，根节点为 x ；另一颗树所有节点值大于等于 v ，根节点为 y 。

实现：（ x 和 y 都是传引用来递归修改值）
```cpp
void splitval(long long rt, long long v, long long &x, long long &y)
{
	if(!rt)
	{
		x = 0;
		y = 0;
		return;
	}
	if(val[rt] <= v)
	{
		x = rt;
		splitval(ch[rt][1], v, ch[rt][1], y);
		pushup(x);
	}
	else
	{
		y = rt;
		splitval(ch[rt][0], v, x, ch[rt][0]);
		pushup(y);
	}
	return;
}
```

------------

**按排名分裂**，即 ```splitrnk(root, k, x, y)``` ,功能是将以 root 为根节点的子树分裂成两棵树，一个树所有节点的排名小于（可以是小于等于，两种写法都对，我的代码中是小于的写法） k ，根节点为 x ；另一颗树所有节点排名大于等于 k ，根节点为 y 。

代码实现：

```cpp
void splitrnk(long long rt, long long k, long long &x, long long &y)
{
	if(!rt)
	{
		x = 0;
		y = 0;
		return;
	}
	if(size[ch[rt][0]] + 1 <= k)
	{
		x = rt;
		splitrnk(ch[rt][1], k - size[ch[rt][0]] - 1, ch[rt][1], y);
		pushup(x);
	}
	else
	{
		y = rt;
		splitrnk(ch[rt][0], k, x, ch[rt][0]);
		pushup(y);
	}
}
```


------------

**1. 对于加入操作：**

如果以前加入过该人，则先删除旧的记录，并加入新的记录

**2. 对于查询某人排名：**

```splitval(v - 1)``` ,并取根节点的子节点个数 +1 

**3. 对于查询连续的 10 名:**

假设连续 10 名中第 1 个排名是 rank ，nodesize 表示总节点数，因为名次按从大到小排，同时我们维护的树是一个节点的左子树所有节点小于根，右子树所有节点大于根，所以要用总结点数 - rank 。易知我们需要的是排名 $max(nodesize - rank - 9, 0)$ 和 $nodesize - rank + 1$ 之间的节点（包含这两个）

先按 $nodesize - rank + 1$ 将整棵树分成分别以 x ， z 为根的子树，其中以 x 为根的子树所有节点排名小于 $nodesize - rank + 1$ ，以 y 为根的子树所有节点排名大于等于 $nodesize - rank + 1$ ，然后再将以 x 为根的子树按 $max(nodesize - rank - 9, 0)$ 分为以 x ， y 为根的子树。这样以 y 为根的子树就包含了我们需要的节点。
即：

```splitrnk(root, nodesize - rank + 1, x, z)``` , ```splitrnk(x, max(nodesize - rank - 9, 0), x, y)```

遍历以 y 为根的子树输出即可。（前面取最大值是为了防止人数不够 10 个，比如查询从第 2 名开始的 10 个）。

### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
long long ch[maxn][2], size[maxn], rnd[maxn], val[maxn], lastscore[maxn], tot, root;
map<string, long long> getname;
string name[maxn];
void pushup(long long x)
{
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
	return;
}
long long newnode(long long v, long long count, string s)
{
	long long x = ++tot;
	name[x] = s;
	ch[x][0] = 0;
	ch[x][1] = 0;
	val[x] = v * maxn - count;
	size[x] = 1;
	rnd[x] = rand() % 500000;
	return x;
}
long long merge(long long a, long long b)
{
	if(!a || !b)
	{
		return  a + b;
	}
	if(rnd[a] < rnd[b])
	{
		ch[a][1] = merge(ch[a][1], b);
		pushup(a);
		return a;
	}
	else
	{
		ch[b][0] = merge(a, ch[b][0]);
		pushup(b);
		return b;
	}
}
void splitrnk(long long rt, long long k, long long &x, long long &y)
{
	if(!rt)
	{
		x = 0;
		y = 0;
		return;
	}
	if(size[ch[rt][0]] + 1 <= k)
	{
		x = rt;
		splitrnk(ch[rt][1], k - size[ch[rt][0]] - 1, ch[rt][1], y);
		pushup(x);
	}
	else
	{
		y = rt;
		splitrnk(ch[rt][0], k, x, ch[rt][0]);
		pushup(y);
	}
}
void splitval(long long rt, long long v, long long &x, long long &y)
{
	if(!rt)
	{
		x = 0;
		y = 0;
		return;
	}
	if(val[rt] <= v)
	{
		x = rt;
		splitval(ch[rt][1], v, ch[rt][1], y);
		pushup(x);
	}
	else
	{
		y = rt;
		splitval(ch[rt][0], v, x, ch[rt][0]);
		pushup(y);
	}
	return;
}
void del(long long &rt, long long v)
{
	long long x = 0, y = 0, z = 0;
	splitval(rt, v, x, z);
	splitval(x, v - 1, x, y);
	rt = merge(x, z);
	return;
}
void insert(long long &rt, long long score, long long count, string s)
{
	if(getname[s] != 0)
	{
		del(rt, val[getname[s]]);
	}
	getname[s] = newnode(score, count, s);
	long long x = 0, y = 0, z = 0;
	splitval(rt, val[tot], x, y);
	rt = merge(merge(x, tot), y);
	return;
}
long long rank(long long &rt, long long v)
{
	long long x = 0, y = 0;
	splitval(rt, v, x, y);
	long long ret = size[y] + 1;
	rt = merge(x, y);
	return ret;
}
void dfs(long long x)
{
	if(!x)
	{
		return;
	}
	dfs(ch[x][1]);
	cout << name[x] << " ";
	dfs(ch[x][0]);
	return;
}
void index(long long k)
{
	long long x = 0, y = 0, z = 0, nowtot = size[root];
	splitrnk(root, nowtot - k + 1, x, z);
	splitrnk(x, max(nowtot - k - 9, 0ll), x, y);
	dfs(y);
	cout << endl;
	root = merge(merge(x, y), z);
	return;
}
long long getnum(string s)
{
	long long ret = 0;
	for(long long i = 0; i < s.size(); i++)
	{
		ret = ret * 10 + s[i] - '0';
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	long long T, score, time = 0;
	char opt;
	string s;
	cin >> T;
	while(T--)
	{
		time++;
		cin >> opt;
		if(opt == '+')
		{
			cin >> s >> score;
			insert(root, score, time, s);
		}
		else if(opt == '?')
		{
			cin >> s;
			if(s[0] >= '0' && s[0] <= '9')
			{
				index(getnum(s));
			}
			else
			{
				cout << rank(root, val[getname[s]]) << endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：devout (赞：1)

这题...跑的真慢

~~本来前面三道题积攒了半秒优势这题直接拖了1s多~~

一眼就是一个平衡树的问题，使用$\text{FHQ Treap}$实现

- 查询某人排名

我们可以利用STL里面的map储存每一个字符串在平衡树中的节点编号，然后查询排名的时候先找到那个点的编号，然后从下往上到根，如果这个点是他爸爸的右子树，答案就加上$siz[fa[x]]+1$，所以我们需要再维护一个父指针

- 查询从排名为x开始的连续10个

按照排名进行$split$，分别应该是$x+9$和$x-1$，然后遍历中间那一部分，输出即可

- 插入

这个东西有点恶心，我的做法非常麻烦，应该有更好的做法

1.当这个人之前出现过，我们先找到这个点的排名

按照排名进行$split$，然后更改这个点的得分

然后把左右部分合并起来，然后再按权值进行$split$，把这个点再合并回去...

2.当这个人之前没出现过，暴力更新

然后按照权值$split$，再合并回去

当然，如果你这么写是有可能有问题的，为什么呢？因为我们发现，当两个人的得分一样的时候，是按照获得得分的先后顺序来的，一种解决方法就是双关键字，但是这同样是没有必要的

当我们再插入一个数$k$的时候，之前在平衡树中的所有$\geq k$的数最后都会比这个大，所以我们$split$的时候直接从$rank=k-1$开始分裂就可以

****

当然你这么写之后会收获样例都过不去的好成绩

为什么呢？题目要求我们求的是前$k$大的，而不是正常平衡树操作中的前$k$小的

做法很简单，把所有权值取反，其他的正常打板子就行了，但是注意$split$的条件需要适当的修改

然后还有一个易错点就是$\text{FHQ Treap}$维护父指针，其实很简单，保险暴力一点就可以了，详见代码


```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e6+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int fa[N],son[N][2],siz[N],val[N],treap[N];
int tot,rt;
string s,name[N];
map<string,int> var;

int todigit(string s){
    int res=0;
    for(int i=0;i<s.size();i++)
        res=res*10+s[i]-'0';
    return res;
}

void update(int x){
    if(son[x][0])fa[son[x][0]]=x;
    if(son[x][1])fa[son[x][1]]=x;
    siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}

int merge(int u,int v){
    if(!u||!v)return u|v;
    int rt;
    if(treap[u]<treap[v])son[rt=u][1]=merge(son[u][1],v);
    else son[rt=v][0]=merge(u,son[v][0]);
    return update(rt),rt;
}

void split_by_rnk(int o,int &u,int &v,int k){
    if(!o){u=v=0;return;}
    fa[o]=0;
    int rank=siz[son[o][0]]+1; 
    if(rank<=k)split_by_rnk(son[u=o][1],son[o][1],v,k-rank);
    else split_by_rnk(son[v=o][0],u,son[o][0],k);
    update(o);
}

void split_by_val(int o,int &u,int &v,int k){
    if(!o){u=v=0;return;}
    fa[o]=0;
    if(val[o]<=k)split_by_val(son[u=o][1],son[o][1],v,k);
    else split_by_val(son[v=o][0],u,son[o][0],k);
    update(o);
}

int rnk(int x){
    int res=siz[son[x][0]]+1;
    while(fa[x]){
        if(son[fa[x]][1]==x)res+=siz[son[fa[x]][0]]+1;
        x=fa[x];
    }
    return res;
}

void dfs(int x){
    if(son[x][0])dfs(son[x][0]);
    cout<<name[x]<<" ";
    if(son[x][1])dfs(son[x][1]);
}

int main()
{
    srand(19260817);
    read(n);
    Rep(i,1,n){
        char c=getchar();
        while(c!='+'&&c!='?')c=getchar();
        int k,lft,mid,rht;   
        cin>>s;
        if(c=='+'){
            read(k);
            if(var[s]){
                int rank=rnk(var[s]);
                split_by_rnk(rt,lft,rht,rank);
                split_by_rnk(lft,lft,mid,rank-1);
                val[mid]=-k;
                rt=merge(lft,rht);
                split_by_val(rt,lft,rht,-k);
                rt=merge(merge(lft,mid),rht);
            }
            else{
                var[s]=++tot;
                treap[tot]=rand();
                siz[tot]=1;
                name[tot]=s,val[tot]=-k;
                split_by_val(rt,lft,rht,-k);
                rt=merge(merge(lft,tot),rht);
            }
        }
        if(c=='?'){
            if(isdigit(s[0])){
                k=todigit(s);
                split_by_rnk(rt,lft,rht,k+9);
                split_by_rnk(lft,lft,mid,k-1);
                dfs(mid);
                rt=merge(merge(lft,mid),rht);
                puts("");
            }
            else{
                k=var[s];
                int rank=rnk(k);
                printf("%d\n",rank);
            }
        }
    }
    return 0;
}
```


---

## 作者：rediserver (赞：1)

# P2584 [ZJOI2006]GameZ游戏排名系统
[原体地址](https://www.luogu.com.cn/problem/P2584)

[Github题解](https://github.com/jerrykcode/luogu)

## 思路
使用结构体
```cpp
struct Record {
	string name;
	int score;
	int count;
	Record() {}
	Record(string name, int score, int count) : name(name), score(score), count(count) {}
	bool operator< (const Record& rec) {
		return score != rec.score ? score < rec.score : count > rec.count;
	}
	bool operator> (const Record& rec) {
		return score != rec.score ? score > rec.score : count < rec.count;
	}
	bool operator== (const Record& rec) {
		return score == rec.score && count == rec.count;
	}
};

```
存储每一条记录，重载运算符，score不同时，score大的记录更大，score相同时，count即提交次序小的，先提交的更大。

使用一个map存储名字与记录的对应。
再用一个SBT平衡树存储所有记录。

对于+Name Score操作，通过map查询Name，若有对应的记录，即以前该用户提交过，则从SBT中删除该记录，然后map更新记录，再在SBT中插入新的记录。

对于？Name操作，通过map查询Name对应的记录，由于SBT树存储了每个结点的size(所有后代结点包括自己的个数)，那么在SBT中搜索一条记录时，就可以知道大于该记录的记录数量（向左子树递归时，右子树的所有记录及根结点的记录均大于搜索的记录；搜索到该记录时，所在结点的右子树的所有记录也大于它），该数量+1就是排名。

对于？Index操作，循环Index递增10次（若Index大于总数就提前break），查找排名Index的记录。显然在SBT中有Index - 1条记录大于它，在SBT中写一个函数`rank(Tree t, int idx)`，用于查找在SBT中有idx条记录比它大的记录。（那么调用时传递给idx的就是Index - 1了）。rank函数中，从SBT根结点开始，若右子树的size正好等于idx，那么正好有idx个记录大于根结点，所以返回根结点的记录就可以啦；若右子树的size小于idx，那么光右子树的记录还不够，左子树中还要有`idx - 右子树的size - 1`个记录大于查找的记录，递归查找左子树；若右子树的size大于idx，则查找的记录在右子树中，递归查找右子树。

（若结点为NULL，其size应该为0，在代码使用getSize函数判断）

代码中实现了一个SBT模板类，其实对于任意类型T，只要提供了<, >, ==运算，SBT<T>就是一种数据结构，它可以存储，删除T类型的元素，也可以查找一个T类型元素的排名，以及查找排名为idx的元素。由于本题题意，SBT<T>在删除元素，查找元素排名时，没有考虑元素不存在的情况；查询排名为idx的元素时，也没有考虑idx超过所有元素数量的情况。

SBT<Record>即可用于对记录进行操作。

## 代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <iostream>
using namespace std;

struct Record {
	string name;
	int score;
	int count;
	Record() {}
	Record(string name, int score, int count) : name(name), score(score), count(count) {}
	bool operator< (const Record& rec) {
		return score != rec.score ? score < rec.score : count > rec.count;
	}
	bool operator> (const Record& rec) {
		return score != rec.score ? score > rec.score : count < rec.count;
	}
	bool operator== (const Record& rec) {
		return score == rec.score && count == rec.count;
	}
};

template<typename T>
class SBT {
public:
	SBT() : t(NULL) {}
	~SBT() { deleteTree(t); }
	void insert(T key);
	void remove(T key);
	int rank(T key);
	T rank(int idx);
	int size();
private:
	typedef struct TNode {
		T key;
		int size;
		struct TNode *left;
		struct TNode *right;
		TNode(T key) : key(key), size(1), left(NULL), right(NULL) {}
	} *Tree;

	int getSize(Tree t) { return t ? t->size : 0; }
	
	Tree leftRotate(Tree t);
	Tree rightRotate(Tree t);
	Tree maintain(Tree t);
	Tree maintainLeft(Tree t);
	Tree maintainRight(Tree t);
	Tree insert(Tree t, T key);
	Tree remove(Tree t, T key);
	int rank(Tree t, T key);
	T rank(Tree t, int idx);
	void deleteTree(Tree t);
private:
	Tree t;
};

int main() {
	map<string, Record> name_to_rec;
	SBT<Record> recs;
	int n;
	scanf("%d", &n);
	char cmd;
	string name;
	int score, index;
	for (int i = 0; i < n; i++) {
		scanf(" %c", &cmd);
		if (cmd == '+') {
			cin >> name;
			scanf("%d", &score);
			if (name_to_rec.count(name)) {
				recs.remove(name_to_rec[name]);
			}
			Record rec(name, score, i);
			name_to_rec[name] = rec;
			recs.insert(rec);
		}
		else {
			cin >> name;
			if (name[0] >= 'A' && name[0] <= 'Z') {
				printf("%d\n", recs.rank(name_to_rec[name]));
			}
			else {
				index = stoi(name);
				for (int j = 0; j < 10; j++) {
					if (index + j > recs.size()) break;
					if (j) putchar(' ');
					cout << recs.rank(index + j).name;
				}
				printf("\n");
			}
		}
	}	
	map<string, Record>().swap(name_to_rec);
	return 0;
}

template<typename T>
void SBT<T>::insert(T key) {
	t = insert(t, key);
}

template<typename T>
void SBT<T>::remove(T key) {
	t = remove(t, key);
}

template<typename T>
int SBT<T>::rank(T key) {
	return rank(t, key) + 1;
}

template<typename T>
T SBT<T>::rank(int idx) {
	return rank(t, idx - 1);
}

template<typename T>
int SBT<T>::size() {
	return t->size;
}

template<typename T>
typename SBT<T>::Tree SBT<T>::leftRotate(SBT<T>::Tree t) {
	Tree k = t->right;
	t->right = k->left;
	k->left = t;
	k->size = t->size;
	t->size = getSize(t->left) + getSize(t->right) + 1;
	return k;
}

template<typename T>
typename SBT<T>::Tree SBT<T>::rightRotate(SBT<T>::Tree t) {
	Tree k = t->left;
	t->left = k->right;
	k->right = t;
	k->size = t->size;
	t->size = getSize(t->left) + getSize(t->right) + 1;
	return k;
}

template<typename T>
typename SBT<T>::Tree SBT<T>::maintain(SBT<T>::Tree t) {
	t = maintainLeft(t);
	return maintainRight(t);
}

template<typename T>
typename SBT<T>::Tree SBT<T>::maintainLeft(SBT<T>::Tree t) {
	if (t == NULL || t->left == NULL) return t;
	if (t->left->left && t->left->left->size > getSize(t->right)) {
		t = rightRotate(t);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	else if (t->left->right && t->left->right->size > getSize(t->right)) {
		t->left = leftRotate(t->left);
		t = rightRotate(t);
		t->left = maintain(t->left);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	return t;
}

template<typename T>
typename SBT<T>::Tree SBT<T>::maintainRight(SBT<T>::Tree t) {
	if (t == NULL || t->right == NULL) return t;
	if (t->right->right && t->right->right->size > getSize(t->left)) {
		t = leftRotate(t);
		t->left = maintain(t->left);
		t = maintain(t);
	}
	else if (t->right->left && t->right->left->size > getSize(t->left)) {
		t->right = rightRotate(t->right);
		t = leftRotate(t);
		t->left = maintain(t->left);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	return t;
}

template<typename T>
typename SBT<T>::Tree SBT<T>::insert(SBT<T>::Tree t, T key) {
	if (t == NULL) {
		return new TNode(key);
	}
	t->size++;
	if (key < t->key) {
		t->left = insert(t->left, key);
		t = maintainLeft(t);
	}
	else {
		t->right = insert(t->right, key);
		t = maintainRight(t);
	}
	return t;
}


template<typename T>
typename SBT<T>::Tree SBT<T>::remove(SBT<T>::Tree t, T key) {
	t->size--;
	if (key < t->key) {
		t->left = remove(t->left, key);
		t = maintainRight(t);
	}
	else if (key > t->key) {
		t->right = remove(t->right, key);
		t = maintainLeft(t);
	}
	else {
		if (t->left && t->right) {
			Tree left_max = t->left;
			while (left_max->right) left_max = left_max->right;
			t->key = left_max->key;
			t->left = remove(t->left, left_max->key);
			t = maintainRight(t);
		}
		else {
			Tree tmp = t;
			t = t->left ? t->left : t->right;
			delete tmp;
		}
	}
	return t;
}

template<typename T>
int SBT<T>::rank(SBT<T>::Tree t, T key) {
	if (key < t->key) {
		return rank(t->left, key) + getSize(t->right) + 1;
	}
	else if (key > t->key) {
		return rank(t->right, key);
	}
	else {
		return getSize(t->right);
	}
}

template<typename T>
T SBT<T>::rank(SBT<T>::Tree t, int idx) {
	int right_size = getSize(t->right);
	if (idx > right_size) {
		return rank(t->left, idx - right_size - 1);
	}
	else if (idx < right_size) {
		return rank(t->right, idx);
	}
	else {
		return t->key;
	}
}

template<typename T>
void SBT<T>::deleteTree(SBT<T>::Tree t) {
	if (t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	delete t;
}

```

---

## 作者：眠ㅤㅤㅤ (赞：0)

写的结构体 $Spaly$，维护得分，左子树的分数比父亲的得分高，这样方便查 $Kth$。

用 $map$ 映射哪个名字对应在哪个节点，每个分数都放大 $10^n$ 倍，再加上一个随着操作减小的时间戳，就保证了相同的分数先存在的排名靠前了。

对于 $?index$ 的询问，$p = Kth(index), s = Kth(min(nidex + 11, tree.size))$

把 $p$ 转到根，$s$ 转到 $p$ 的右孩子，然后遍历 $s$ 的左孩子就行了。


```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
constexpr auto Inf = 0x3F3F3F3F;
typedef long long LL;
using namespace std;

namespace IO {
    inline LL read() {
        LL o = 0, f = 1; char c = getchar();
        while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
        while (c > '/' && c < ':') { o = o * 10 + c - '0'; c = getchar(); }
        return o * f;
    }
    inline char recd() {
        char o; while ((o = getchar()) != 'C' && o != 'Q' && o != 'D'); return o;
    }
}
using namespace IO;

const int SIZE = 2E5 + 7;

map<string, int> Map;

struct Node {
    int son[2], Fa, sze; LL w; string str;
} Node[SIZE << 2]; int Root, Ind;

inline int which(int now) {
    return now == Node[Node[now].Fa].son[1];
}

inline void pushup(int now) {
    Node[now].sze = Node[Node[now].son[1]].sze + Node[Node[now].son[0]].sze + 1;
}

void Rot(int now) {
    int F = Node[now].Fa, FF = Node[F].Fa, w = which(now);
    Node[Node[now].son[!w]].Fa = F, Node[F].son[w] = Node[now].son[!w];
    Node[now].Fa = FF, Node[FF].son[which(F)] = now;
    Node[F].Fa = now, Node[now].son[!w] = F, pushup(F), pushup(now);
}

void Splay(int now, int pos) {
    for (int F = Node[now].Fa; F != pos; Rot(now), F = Node[now].Fa)
        if (Node[F].Fa != pos)
            which(F) ^ which(now) ? Rot(now) : Rot(F);
    if (!pos) Root = now;
}

int Ins(int& now, int F, LL w) {
    if (!now) {
        now = ++Ind, Node[now].Fa = F, Node[now].sze = 1, Node[now].w = w; return now;
    }
    int pos = Ins(Node[now].son[Node[now].w > w], now, w); pushup(now);
    return pos;
}

int Fnd(LL w) {
    int now = Root;
    while (Node[now].son[Node[now].w > w] && Node[now].w != w) 
        now = Node[now].son[Node[now].w > w];
    return now;
}

//   前驱
int Per(LL w) {
    int pos = Fnd(w); Splay(pos, 0);
    if (Node[Root].w > w) return Root;
    int now = Node[Root].son[0];
    while (Node[now].son[1]) now = Node[now].son[1];
    return now;
}

//   后继
int Suf(LL w) {
    int pos = Fnd(w); Splay(pos, 0);
    if (Node[Root].w < w) return Root;
    int now = Node[Root].son[1];
    while (Node[now].son[0]) now = Node[now].son[0];
    return now;
}

//   删除
void Rem(string str) {
    if (!Map[str]) return;
    int per = Per(Node[Map[str]].w), suf = Suf(Node[Map[str]].w);
    Splay(per, 0), Splay(suf, per);
    Node[Node[Root].son[1]].son[0] = 0;
    pushup(Node[Root].son[1]), pushup(Root);
}

//   插入
void Ins(string str, LL w) {
    Rem(str); 
    int pos = Ins(Root, 0, w); 
    Map[str] = pos, Node[pos].str = str, Splay(pos, 0);
}

int Rnk(string str) {
    Splay(Map[str], 0); return Node[Node[Root].son[0]].sze;
}

int Kth(int now, int K) {
    if (K == Node[Node[now].son[0]].sze + 1) return now;
    if (K <= Node[Node[now].son[0]].sze) return Kth(Node[now].son[0], K);
    return Kth(Node[now].son[1], K - Node[Node[now].son[0]].sze - 1);
}

//   输出名字
void Prtview(int now) {
    if (!now) return;
    Prtview(Node[now].son[0]);
    cout << Node[now].str << ' ';
    Prtview(Node[now].son[1]);
}
void Prt(int K) {
    int per = Kth(Root, K), suf = Kth(Root, min(K + 11, Node[Root].sze));
    Splay(per, 0), Splay(suf, per);
    Prtview(Node[Node[Root].son[1]].son[0]); puts("");
}

//   调试用
void DEBUG(int now, int space) {
    if (!now) { 
        for (int pos = 1; pos <= space; pos++) cout << "     ";
        puts("NULL"); return;
    }
    DEBUG(Node[now].son[0], space + 1);
    for (int pos = 1; pos <= space; pos++) cout << "     ";
    cout << Node[now].str << " w = " << double(Node[now].w) << ' ' << endl;
    DEBUG(Node[now].son[1], space + 1);
}

int main() {
    int N; char o; string Tmp; LL w; cin >> N;
    Ins("Inf", LLONG_MAX), Ins("-Inf", LLONG_MIN);
    
    for(int pos = N, K, I; pos >= 1; pos--) {
    
    // pos 为一个从大到小的时间戳
        cin >> o >> Tmp;
        if (o == '+') 
            cin >> w, Ins(Tmp, w * 1000000 + pos);
        else if (isupper(Tmp[0]))
            cout << Rnk(Tmp) << endl;
        else {
            for (I = K = 0; Tmp[I]; I++) K = K * 10 + Tmp[I] - '0'; 
            Prt(K);
        }
        /*puts(""); DEBUG(Root, 0); puts("");*/
    }
}

```

---

## 作者：Huami360 (赞：0)

首先这题双倍经验，想知道哪题去我[博客](https://www.cnblogs.com/Qihoo360/p/10374578.html)

一眼看去平衡树裸题，我用$Splay$实现的。

本题的难点在于如何维护名字和编号的映射关系，现有的题解都是用$map+$字符串哈希的方法来维护的。

但还有更快的方法：$Trie$

码量真的不大，跑的飞快（总共479ms，未吸氧）

另外本题还有个坑，debug了好久，就是会出现分数非常大的童鞋，达到了十位数，如果你的虚点的值不够大的话就会像我一样TLE，所以INF还是都设为2147483647吧

一些细节看代码吧。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;
const int MAXN = 250010;
inline int read(){
    int s = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9')ch = getchar(); 
    while(ch >= '0' && ch <= '9'){ s = s * 10 + ch - '0'; ch = getchar(); }
    return s;
}
struct info{
    int val, id;
    int operator > (const info A) const{
        return val == A.val ? id < A.id : val > A.val;
    }
};
struct splay{
    info val;
    int size, ch[2], fa;
}t[MAXN];
int root, num, T;
struct Trie{    //字典树维护名字和编号映射关系
	int val;    //编号
	Trie *ch[26];
	Trie(){ for(int i = 0; i < 26; ++i) ch[i] = NULL; val = 0; }
}rt;
int Insert(char *s, int pos){ //字典树插入，成功返回0，如果已经存在了就返回已有的编号
	int len = strlen(s);
	Trie *u = &rt;
	for(int i = 0; i < len; ++i){
	   if(u->ch[s[i] - 'A'] == NULL) u->ch[s[i] - 'A'] = new Trie();
	   u = u->ch[s[i] - 'A'];
	}
	if(u->val) return u->val;
	u->val = pos;
	return 0;
}
inline void pushup(int x){
    t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + 1;
}
inline void rotate(int x){
    int y = t[x].fa, z = t[y].fa, k = t[y].ch[1] == x;
    t[y].ch[k] = t[x].ch[k ^ 1]; t[t[x].ch[k ^ 1]].fa = y;
    t[y].fa = x; t[x].ch[k ^ 1] = y;
    t[x].fa = z; t[z].ch[t[z].ch[1] == y] = x;
    pushup(y); pushup(x);
}
inline void Splay(int x, int goal){
    int y, z;
    while(t[x].fa != goal){
        y = t[x].fa; z = t[y].fa;
        if(z != goal) rotate((t[y].ch[1] == x) ^ (t[z].ch[1] == y) ? x : y);
        rotate(x);
    }
    if(!goal) root = x;
}
inline int insert(info x, int num){  //Splay插入
    if(!root){ root = num; t[root].val = x; t[root].size = 1; return root; }
    int u = root, fa = 0;
    while(u){ fa = u; u = t[u].ch[x > t[u].val]; }
    int id = num; t[id].val = x; t[id].size = 1; t[id].fa = fa; if(fa) t[fa].ch[x > t[fa].val] = id;
    Splay(id, 0);
    return id;
}
int limit, tmp, Time;
void find(int x){
    int u = root;
    while(233){
        if(t[t[u].ch[0]].size == x - 1) break;
        if(t[t[u].ch[0]].size >= x) u = t[u].ch[0];
        else x -= t[t[u].ch[0]].size + 1, u = t[u].ch[1];
    }
    Splay(u, 0);
}
char ch, name[MAXN][12];
int len[MAXN];
void dfs(int x){
    if(!limit) return;   //题中的排名是从大到小的，所以先遍历右儿子
    if(t[x].ch[1]) dfs(t[x].ch[1]);
    if(!limit) return;
    for(int i = 0; i < len[x]; ++i)
       putchar(name[x][i]);
    putchar(' ');
    --limit;
    if(t[x].ch[0]) dfs(t[x].ch[0]);
}
int next(int x, int mode){
    Splay(x, 0);
    int u = t[root].ch[mode]; 
    while(t[u].ch[!mode]) u = t[u].ch[!mode];
    return u;
}
char s[12];
int pq;
int main(){
	//freopen("1.txt","r",stdin);
	//freopen("2.txt","w",stdout);
    T = read(); insert((info){ -2147483646, 9999999 }, ++num); insert((info){ 2147483646, -1 }, ++num);
    while(T--){
        ch = getchar();
        while(ch != '+' && ch != '?') ch = getchar();
        if(ch == '+'){ 
          scanf("%s", s);
          if(pq = Insert(s, num + 1)){ //已经存在了
          	int l = next(pq, 0), r = next(pq, 1);  //删了再插进去
            Splay(l, 0);
            Splay(r, l);
            t[t[root].ch[1]].ch[0] = 0;
            Splay(t[root].ch[1], 0);
            insert((info){ read(), ++Time }, pq);
          }
          else{
            insert((info){read(), ++Time}, ++num); 
            memcpy(name[num], s, sizeof s);
            len[num] = strlen(name[num]);
          }
        }
        if(ch == '?'){
            ch = getchar();
            if(ch >= '0' && ch <= '9'){
                tmp = 0;
                while(ch >= '0' && ch <= '9'){ tmp = tmp * 10 + ch - '0'; ch = getchar(); }
                find(num - tmp);  //因为题中的排名是从大到小的，而平衡树排名是从小到大的，所以要反过来
				for(int i = 0; i < len[root]; ++i)
       			   putchar(name[root][i]);
    			putchar(' '); limit = 9;
                if(t[root].ch[0]) dfs(t[root].ch[0]);
                printf("\n");
            }
            else{
                int p = 0;
                while(ch >= 'A' && ch <= 'Z'){ s[p++] = ch; ch = getchar(); }
                for(int i = p; i < 12; ++i) s[i] = 0;
                Splay(Insert(s, 233), 0);
                printf("%d\n", t[t[root].ch[1]].size);
            }
        }
        if(T % 200 == 0) Splay(rand() % num + 1, 0);  //保持Splay随机性
    }
    return 0;
}
```

---

