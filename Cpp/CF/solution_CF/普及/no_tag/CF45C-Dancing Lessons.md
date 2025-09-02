# Dancing Lessons

## 题目描述

There are $ n $ people taking dancing lessons. Every person is characterized by his/her dancing skill $ a_{i} $ . At the beginning of the lesson they line up from left to right. While there is at least one couple of a boy and a girl in the line, the following process is repeated: the boy and girl who stand next to each other, having the minimal difference in dancing skills start to dance. If there are several such couples, the one first from the left starts to dance. After a couple leaves to dance, the line closes again, i.e. as a result the line is always continuous. The difference in dancing skills is understood as the absolute value of difference of $ a_{i} $ variable. Your task is to find out what pairs and in what order will start dancing.

## 样例 #1

### 输入

```
4
BGBG
4 2 4 3
```

### 输出

```
2
3 4
1 2
```

## 样例 #2

### 输入

```
4
BBGG
4 6 1 5
```

### 输出

```
2
2 3
1 4
```

## 样例 #3

### 输入

```
4
BGBB
1 1 2 3
```

### 输出

```
1
1 2
```

# 题解

## 作者：Zskioaert1106 (赞：7)

题目传送门：[CF45C Dancing Lessons](https://www.luogu.com.cn/problem/CF45C)

~~双倍经验：[P1878 舞蹈课](https://www.luogu.com.cn/problem/P1878)~~

### 前置知识

- 链表

- 优先队列

- 模拟

### 题目分析

我们发现最初这 $n$ 个人组成了一条链，而每次出列的是相邻的两个人，之后他们俩两旁的人会挨到一起。这启示我们什么？我们可以用链表。

每个人有如下属性：编号（自 $1$ 到 $n$）、性别、舞蹈技术值，以及他/她左右的人。

我们定义结构体来存储：

```cpp
struct people{
	int l,r,a;
	bool x,vis;
}a[200005];
```

其中 $x$ 指性别，$l$ 和 $r$ 分别指左侧和右侧的人的编号。

对于一对舞伴来说，其中的某人可能已经同其他人跳过舞，而这种情况下这对舞伴就没法跳舞了，所以我们要用 $vis$ 记录这个人是否已经出列跳过舞了。

每次都是队伍中舞蹈技术差值**最**小的一堆舞伴出列跳舞，这有启示我们什么？我们可以用**优先队列**。

（不知道优先队列的同学可以[自行搜索](https://iwo.im/?q=优先队列)，在此不再赘述了）

于是我们将所有可能的舞伴放入优先队列里，然后每次选出技术差最小的一对，所以我们可以用结构体开一个小顶堆。

这个结构体本质上存两人的编号就行了，但是为了方便可以将技术差一并存在内。

```cpp
struct peoples{
	int a;//此处指两人的舞蹈技术差
	int l,r;
};
```

好了，接下来是重要部分。

最初，我们遍历一遍队伍，如果两个相邻的人性别不同，我们就将他们加入最初的优先队列。

接下来，一直弹出堆顶。

如果这两个人都没跳过舞，那么这就是一组可行舞伴，且是所有可行舞伴中最般配的。所以我们自然要让他们出列跳舞。我们记录下来他们的编号，然后把他们俩都标记为跳过舞的。

之后呢？我们把他们从链表中删去，即：将这组舞伴（他们一定是挨着的）左边的人与右边的人连接起来。然后如果这俩人性别不同，那么他们也就是一组舞伴了。

如果有哪怕一个人跳过舞，这组舞伴都不可行，直接跳过即可。因为是优先队列，所以这样安排一定是符合题目规则的。

好啦！在代码的编写中去完善细节吧！

### 代码编写

先定义好存储配对顺序的数组和结构体。

因为要用结构体还是小根堆，所以我们可以重载运算符。

```cpp
bool operator<(peoples a,peoples b){
	if(a.a==b.a)return a.l>b.l;
	return a.a>b.a;
}
priority_queue<peoples>q;
```

- 细节：这里要写第二关键字的判断，因为“如果不止一对，那么最左边的那一对出列”，否则你将获得一半的 WA。

读入时将每个人的左右邻居初始化为（对于第 $i$ 个人）$i-1$ 和 $i+1$，然后将所有相邻的舞伴以 $(|a_{i-1}-a_{i}|,i-1,i)$ 的形式放入优先队列：

```cpp
cin>>n;
string s;
cin>>s;
for(int i=1;i<=n;i++){
  cin>>a[i].a;
  a[i].l=i-1,a[i].r=i+1;
  a[i].x=(s[i-1]=='G');
  if(i>1&&a[i-1].x!=a[i].x)
    q.push(peoples{abs(a[i].a-a[i-1].a),i-1,i});
}
```

之后一直循环直到没有正常的舞伴：

```cpp
while(!q.empty()){
  int l=q.top().l,r=q.top().r;
  q.pop();
  if(a[l].vis||a[r].vis)continue;//跳过舞直接跳过
  k++,ans[0][k]=l,ans[1][k]=r;//存入答案
  a[l].vis=1,a[r].vis=1;
  l=a[l].l,r=a[r].r;
  a[l].r=r,a[r].l=l;//连接这对舞伴左右两侧的人
  if(l>0&&r<=n&&a[l].x!=a[r].x)//满足条件就新加进来
    q.push(peoples{abs(a[l].a-a[r].a),l,r});
}
```

最终按照顺序输出即可。

### 完整代码

就知道你们爱看这个，讲了半天~~终于到重点了~~：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,k,ans[2][100005];
string s;
struct people{
	int l,r,a;
	bool x,vis;
}a[200005];
struct peoples{
	int a;
	int l,r;
};
bool operator<(peoples a,peoples b){
	if(a.a==b.a)return a.l>b.l;
	return a.a>b.a;
}
priority_queue<peoples>q;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i].a;
		a[i].l=i-1,a[i].r=i+1;
		a[i].x=(s[i-1]=='G');
		if(i>1&&a[i-1].x!=a[i].x)
			q.push(peoples{abs(a[i].a-a[i-1].a),i-1,i});
	}
	while(!q.empty()){
		int l=q.top().l,r=q.top().r;
		q.pop();
		if(a[l].vis||a[r].vis)continue;
		k++,ans[0][k]=l,ans[1][k]=r;
		a[l].vis=1,a[r].vis=1;
		l=a[l].l,r=a[r].r;
		a[l].r=r,a[r].l=l;
		if(l>0&&r<=n&&a[l].x!=a[r].x)
			q.push(peoples{abs(a[l].a-a[r].a),l,r});
	}
	cout<<k<<'\n';
	for(int i=1;i<=k;i++)cout<<ans[0][i]<<' '<<ans[1][i]<<'\n';
	return 0;
}
```

[ P1878 的 AC 记录](https://www.luogu.com.cn/record/195206345)，[CodeForces 上的 AC 记录](https://codeforces.com/contest/45/submission/297228220)。

---

## 作者：xyx404 (赞：3)

## 思路：
定义结构体，结构体包含三个成员 $left$ 表示左边的人，$right$ 表示右边的人，$cz$ 表示这两个人的差值，自定义排序：
```cpp
bool operator <(const node &X)const{
  return cz==X.cz?left>X.left:cz>X.cz;
}
```

定义优先队列，类型为上面定义的结构体。  
定义标记数组 $bj$ 标记这个人是否已经被搭配了。  
定义二维数组 $ans$ 存答案。  
定义 $ans2$ 存答案的数量。  
定义数组 $last$ 和 $nex$ 模拟链表，记录上一个人和下一个人。

在输入时顺便把 $last$ 和 $nex$ 初始化，初始化时 $last_i$ 的值为 $i-1$，$nex_i$ 的值为 $i+1$。

在输入完后，遍历字符串，直到现在遍历到的是字符串的最后一个字母，注意是遍历到而不是遍历完，当字符串的第 $i$ 个字符与第 $i+1$ 个字符不同时，也就是他们为异性时，把他们及他们的差值的绝对值存进结构体加入优先队列。

然后进入循环，循环条件为队列不为空，在循环内，先把队列里的结构体取出来，然后弹出，然后判断下，取出来的结构体里的 $left$ 和 $right$ 是否在 $bj$ 里被标记过，如果其中有一个被标记过那么直接开始下一次循环，否则标记他们，并把他们存在 $ans$ 数组里，并让 $ans2$ 加一，在这之后维护链表，如果去掉他们两个后，$left$ 原本的左边的人与 $right$ 原本右边的人为异性那么把他们与他们的差值的绝对值存进结构体加入优先队列。

最后先输出 $ans2$，然后把 $ans$ 数组里被存过的答案输出就行了。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int last[200005],nex[200005],a[200005],ans[200005][3],ans2;
struct node{
	itn left,right,cz;
	bool operator <(const node &X)const{
		return cz==X.cz?left>X.left:cz>X.cz;
	}
};
priority_queue<node>dl;
bool bj[200005];
string str;
itn n;
int main(){
	cin>>n>>str;
	str=" "+str;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		last[i]=i-1;
		nex[i]=i+1;
	}
	for(int i=1;i<n;i++){
		if(str[i]!=str[i+1]){
			dl.push(node{i,i+1,abs(a[i]-a[i+1])});
		}
	}
	while(!dl.empty()){
		node tamp=dl.top();dl.pop();
		if(bj[tamp.left]||bj[tamp.right])continue;
		ans[++ans2][1]=tamp.left;
		ans[ans2][2]=tamp.right;
		bj[tamp.left]=bj[tamp.right]=1;
		int l=last[tamp.left],ne=nex[tamp.right];
		nex[l]=ne;last[ne]=l;
		if(l<1||ne>n)continue;
		if(str[l]!=str[ne]){
			dl.push(node{l,ne,abs(a[l]-a[ne])});
		}
	} 
	cout<<ans2<<"\n";
	for(itn i=1;i<=ans2;i++){
		cout<<ans[i][1]<<" "<<ans[i][2]<<"\n";
	}
	return 0;
}
```

---

## 作者：Sayori (赞：3)

### Description
给出长度为 $n$ 的一个男女序列，每次求出当前相邻舞蹈技术差值最小的一对相邻男女的位置，并把他们从序列中删除，直到不存在相邻男女
### Solution
看到序列中的删除操作，就能想到用链表去维护这个序列，而求舞蹈技术差值最小，则可以用优先队列去维护，将差值最小的放在最上面，每次求的时候在更新一下链表即可
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int pre[N], nex[N], a[N], fl[N];//fl数组用来标记当前位置是否使用
char s[N];
int n, cnt, ans[N][2];
struct node{
	int l, r, d;
	node(int L, int R, int D):l(L), r(R), d(D){}
	bool operator <(const node &o)const{
		return d == o.d ? l > o.l : d > o.d;//当二者差值相同时，按照l排序
	}
};
priority_queue<node> q;
template <typename T>
inline void read(T &x){
	char t(getchar()), flg(0); x = 0;
	for (; !isdigit(t); t = getchar() ) flg = t == '-';
	for ( ; isdigit(t); t = getchar() ) x = x * 10 + ( t & 15 );
	flg ? x = -x : x;
}
template <typename T, typename... Args>
inline void read(T &x, Args &... args){read(x);read(args...);}
int main(){
	read(n);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; ++i)
		read(a[i]), pre[i] = i - 1, nex[i] = i + 1;//初始化
	for(int i = 1; i < n; ++i)
		if(s[i] != s[i + 1])
			q.push(node(i, i + 1, abs(a[i] - a[i + 1])));
        //当两者性别不同时，即可插入优先队列
	while(!q.empty()){
		node tmp = q.top(); q.pop();//取出差值最小
		if(fl[tmp.l] || fl[tmp.r]) continue;//若当前节点访问过，就可以跳过
		ans[++cnt][0] = tmp.l, ans[cnt][1] = tmp.r;
		fl[tmp.l] = fl[tmp.r] = 1;
		int L = pre[tmp.l], R = nex[tmp.r];
		nex[L] = R, pre[R] = L;//维护链表
		if(L < 1 || R > n) continue;
		if(s[L] != s[R])
			q.push(node(L, R, abs(a[L] - a[R])));
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; ++i)
		printf("%d %d\n", ans[i][0], ans[i][1]);
}
```


---

## 作者：ymhxjsh (赞：2)

# 思路  
本题大致思路很简单，使用优先队列，将两异性的差的绝对值从小到大排序，每次模拟输出最小的差所对应的两点位置。
## 难点
1. 输出过后的两个点便不能再被使用，即**有差不能使用**。  
解决方案：对此很好解决，我们无法对优先队列中某个差删除，但可以建立 vis 数组，记录此点是否使用，并在遇到含此点的差时进行判断。   
2. 两个点禁用后还带来一个问题，**产生新的差**。   
解决方案：暴力处理查找两个点的左右端第一个未被使用（即 $vis[i]=0$ 的点），若符合异性，则将差弹入优先队列。但对于最后一点，暴力会 TLE 。
 对于查找的优化可以想到链表和二分查找，此处使用链表记录每个点左右所连接的点，二分较为复杂。

**还存在一个其他题解没有写到的很巧妙的求 $k$ 的方法**     
由于只要存在异性相邻，便可配对，并且任意人的旁边只存在男或女两种情况，不难推出  
$$k=\min(numb,numg)$$    
其中 $numb$ 为男生数量， $numg$ 为女生数量    
### 其思路如下：  
只要存在男生和女生，则必然有男生与女生相邻，即必然有一组新的配对产生。配对的产生直到男女一方数量降为 $0$ 时结束，此时才不会有 BG 相邻。  
这样就方便写模拟的外层循环条件。

## 上代码   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,numb,numg,k,noww;
bool vis[200005];
struct node{
    char sex;
    int a,leftt,rightt;//leftt,rightt分别计入此点的左右连接
}f[200005];
struct edge{
    int idf,ids,cha;//idf为配对的左边的人，ids为右边
    bool operator<(const edge& other) const{
        if(cha!=other.cha) return cha>other.cha;
        else return idf>other.idf;
    }
};
priority_queue<edge> q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>f[i].sex;
        if(f[i].sex=='B') numb++;
        else numg++;
    }k=min(numb,numg);//依据结论得出k
    cout<<k<<endl;
    for(int i=1;i<=n;i++){
        cin>>f[i].a;
        f[i].leftt=i-1,f[i].rightt=i+1;//初始化左右连接
        if((i>1&&f[i-1].sex=='B'&&f[i].sex=='G')||(f[i-1].sex=='G'&&f[i].sex=='B')) q.push({i-1,i,abs(f[i-1].a-f[i].a)});//判断BG是否相邻
    }while(noww<k){
        edge t=q.top();
        q.pop();
        if(vis[t.idf]==0&&vis[t.ids]==0){
            vis[t.idf]=1,vis[t.ids]=1;
            noww++;
            cout<<t.idf<<" "<<t.ids<<endl;
            f[f[t.idf].leftt].rightt=f[t.ids].rightt;
            f[f[t.ids].rightt].leftt=f[t.idf].leftt;
            int l=f[t.idf].leftt,r=f[t.ids].rightt;
            //把idf的左边，ids的右边的人进行连接
            if((f[l].sex=='B'&&f[r].sex=='G')||(f[l].sex=='G'&&f[r].sex=='B')) q.push({l,r,abs(f[l].a-f[r].a)});
        }
    }return 0;
}
```

---

## 作者：Barewalk (赞：1)

### Description

有一个长度为 $n$ 的带权 01 串，每次删除相邻且不同，权值之差最小的一对字符并输出，直至 01 串全部相同为止。若有多对，则先删最左边的。

### Solution

类似这种题，其实做多了都能一眼看出套路。

由于题目要求先输出权值之差最小的，如果每次都 sort 一遍显然过劣。如何维护动态最小值呢？自然是想到用小根堆维护：先将所有合法的字符对加入堆中，每次取出堆顶，更新答案，然后删除元素，最后更新小根堆，即判断删除后该点左右两边是否不同，不同就加入堆中。

如何删除元素？对于动态维护序列相邻关系，双向链表显然最为高效。于是，优先队列 + 双向链表这个数据结构诞生，本题也就迎刃而解。

但双向链表还需注意边界问题，因为 $l_1=0$，$r_n=n+1$，这是我们不想更新的点。这里有个比较方便的处理方式：用 $vis$ 记录该点是否被删除，初始化时 $vis_0=1$，$vis_{n+1}=1$，即可。常见的处理方式还有将 $val_0$，$val_{n+1}$ 赋成极大极小值，保证不会用来更新答案。

像优先队列 + 双向链表这种数据结构还是挺常见的，大多会与贪心结合在一起~~就变成蓝的了~~。[试试这个](https://www.luogu.com.cn/problem/P10478)

### Code

```cpp
char op[SIZE];
int n, s[SIZE], v[SIZE];

int idx[SIZE], idy[SIZE], cnt;
//记录答案
int l[SIZE], r[SIZE], vis[SIZE];
//l r 为双向链表，vis 记录是否被删除了

struct node {
    int i, j, val;
    bool operator < (const node&nd) const {
        return val == nd.val? i > nd.i: val > nd.val;
        //细节 1：
        //因为下面建立的是大跟堆，想要维护最小值需要重载小于号成大于号
    }
};
priority_queue<node> q;

int main() {
    scanf("%d %s", &n, op + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = op[i] == 'B'? 0: 1;
        //转成 01 串
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", v + i);
        l[i] = i - 1, r[i] = i + 1;
        if(i > 1 && s[i-1] != s[i]){
            q.push({i - 1, i, abs(v[i - 1] - v[i])});
        }
        //添加候选集合
    }      
    vis[0] = vis[n + 1] = 1;
    //细节 2
    while (!q.empty()) {
        int i = q.top().i, j = q.top().j;
        q.pop();
        if (vis[i] || vis[j]) continue;
        idx[++cnt] = i, idy[cnt] = j;
        vis[i] = vis[j] = 1;
        int x = l[i], y = r[j];
        r[x] = y, l[y] = x;
        //Del
        if (s[x] != s[y] && ! (vis[x] || vis[y])) {
            q.push({x, y, abs(v[x] - v[y])});
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) {
        printf("%d %d\n", idx[i], idy[i]);
    }
    return 0;
}
```

---

## 作者：scc36 (赞：1)

[原题跃迁窗口](https://www.luogu.com.cn/problem/CF45C)     
[双倍经验](https://www.luogu.com.cn/problem/P1878)     
### 思路  
其实在 P1878 的题面中有这么一句话：任务是**模拟**以上过程。所以很简单，题目怎么说，我们就怎么做。  
有点啰嗦，大佬误入~~

---


先考虑不会并到一起的情况（就是选出一组后，剩下的人不会合拢成一组）。    
这样一来就很容易，只要预处理输入时每一对男女的差值，从小到大排序，最后输出即可。    
这里要注意的是不能重复计算。比如说以下数据：   

```
3
GBG
1 2 10
```
第二个位置的人会被分到两组里面去。    
第一次出列，第一个位置的女生和第二个位置的男生一起出列。  
第二次出列，本来应该是第二个位置的男生和第三个位置的女生一起出列，但第二个位置的男生已经出列了，所以跳过这一次操作。   


---


然后考虑会并在一起的情况。   
这个时候，有两人出列后，并在一起的这一对男女也要考虑进来。因为插值要求最小的，就要对原来的插值序列重新排序，每次要 $O(n \log n)$，这样很耗费时间。    
于是我们就想到了优先队列，也就是堆。不懂堆的戳[这里](https://www.luogu.com.cn/problem/P3378)。     
每次插入一个新的差值，只需要 $O(\log n)$。复杂度直线下降。    
这里要注意的是合并之后，并在一起的男女在原来的序列中的位置距离可能超过 2，所以要向前和向后去寻找第一个没出列的位置。比如说一下数据：

```
6
BBGBGG
1 4 3 4 2 10
```
第一次，第二个位置和第三个位置的人出列。    
第二次，第四个位置和第五个位置的人出列。   
第二次后，如果比较合并后的两端的位置为 3（4-1） 和 6（5+1） 的话，就会发现第三个位置已经出列了，然后就结束了。但实际上，第一个位置和第六个位置的人也会一起出列。    
~~为啥会有这种奇奇怪怪的注意点啊？？？~~   
~~因为我一开始就错在这里了 QWQ~~   
然后我们就能写出代码~~   
### 代码
大致如下：

```cpp
struct no{
	int a,b,c;
};
no tmp;
struct cmp{  //因为记录了位置编号，就自定义了堆比较的方法~~
	bool operator()(no t,no w){
		if(t.c>w.c) return 1;
		else if(t.c==w.c&&t.a>w.a) return 1;
		return 0;
	}
};
priority_queue<no,vector<no>,cmp>q;

int qian(int x){//向前找 
	if(f[x]==0) return x;
	else return qian(x-1);
}
int hou(int x){//向后找 
	if(f[x]==0) return x;
	else return hou(x+1);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i].c;
	for(i=1;i<=n;i++) cin>>a[i].a;
	for(i=1;i<=n-1;i++) //将一开始就的并列的男女加进堆里 
		if(a[i].c=='B'&&a[i+1].c=='G'||a[i].c=='G'&&a[i+1].c=='B'){
			tmp.a=i,tmp.b=i+1;tmp.c=abs(a[i].a-a[i+1].a);
			q.push(tmp);
		}
	while(q.size()>0){
		while(q.size()>0){ //已经出列了，就不要再计算了 
			if(f[q.top().a]||f[q.top().b]) q.pop();
			else break;
		}
		if(q.size()==0) break;//啥都没了 QWQ 
		
		v++,b[v].a=q.top().a,b[v].b=q.top().b;
		f[b[v].a]=f[b[v].b]=1;
		//将本次数列的人记录下来 
		
		Q=qian(b[v].a-1);
		H=hou(b[v].b+1);
		if(a[Q].c=='B'&&a[H].c=='G'||a[Q].c=='G'&&a[H].c=='B'){
			tmp.a=Q,tmp.b=H;tmp.c=abs(a[Q].a-a[H].a);
			q.push(tmp);
		}
		//对合并后相邻的两人进行比较 
	}
	cout<<v<<"\n";
	for(i=1;i<=v;i++) cout<<b[i].a<<" "<<b[i].b<<"\n";
}
```
然后就超时了 /(ㄒoㄒ)/~~   
P1878 会在第 11 个点会超时，本题则超时在第 26 个点。    
~~是不是感觉被放鸽子了~~     
### 优化
不难发现，我们在向前寻找和向后寻找上会花上很多时间。很多已经出列的点会被我们跑上好几次。   
我们可以将链表思想融入进来，这样就可以跳过很多已经出列的点。   
具体来说，当第 $t$ 和 第 $t+1$ 个位置的人出列后，第 $t-1$ 个人的后指针指向 $t+2$，第 $t+2$ 个人的前指针指向 $t-1$。   
在向前寻找时，每次都到这个位置前指针指向的位置；再向后寻找时，每次都到这个位置后指针指向的位置。    
这样能节省很多很多时间，但还是超时。    
~~为了卡掉一些错误做法，出题人真是煞费苦心~~    
于是我就想到了打并查集经常用的路径压缩，终于不超时了！o((>ω< ))o
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,v,f[1000001],Q,H;
struct no1{
	int a;
	char c;
}a[1000001];
struct no2{
	int a,b;
}b[1000001];
struct no{
	int a,b,c;
};
no tmp;
struct cmp{
	bool operator()(no t,no w){
		if(t.c>w.c) return 1;
		else if(t.c==w.c&&t.a>w.a) return 1;
		return 0;
	}
};
priority_queue<no,vector<no>,cmp>q;
struct no3{
	int qian,hou;
}fa[1000001];

int qian(int x){
	if(f[x]==0) return x;
	else return fa[x].qian=qian(fa[x].qian);//路径压缩 
}
int hou(int x){
	if(f[x]==0) return x;
	else return fa[x].hou=hou(fa[x].hou);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++) fa[i].qian=i-1,fa[i].hou=i+1;
	for(i=1;i<=n;i++) cin>>a[i].c;
	for(i=1;i<=n;i++) cin>>a[i].a;
	for(i=1;i<=n-1;i++)
		if(a[i].c=='B'&&a[i+1].c=='G'||a[i].c=='G'&&a[i+1].c=='B'){
			tmp.a=i,tmp.b=i+1;tmp.c=abs(a[i].a-a[i+1].a);
			q.push(tmp);
		}
	while(q.size()>0){
		while(q.size()>0){
			if(f[q.top().a]||f[q.top().b]) q.pop();
			else break;
		}
		if(q.size()==0) break;
		
		v++,b[v].a=q.top().a,b[v].b=q.top().b;
		f[b[v].a]=f[b[v].b]=1;
		
		fa[b[v].b+1].qian=b[v].a-1,fa[b[v].a-1].hou=b[v].b+1;
		//链表思想 
		
		Q=qian(b[v].a-1);
		H=hou(b[v].b+1);
		if(a[Q].c=='B'&&a[H].c=='G'||a[Q].c=='G'&&a[H].c=='B'){
			tmp.a=Q,tmp.b=H;tmp.c=abs(a[Q].a-a[H].a);
			q.push(tmp);
		}
	}
	cout<<v<<"\n";
	for(i=1;i<=v;i++) cout<<b[i].a<<" "<<b[i].b<<"\n";
}
```
~~好长啊~~

---

## 作者：Daniel_xu (赞：0)

# 题意简述
有 $n$ 个人顺序站成一排，不断选出能力，即 $a_{i}$ 差值最小且相邻的男女（差值相同，选第一个人编号更小的），直到没有男女相邻。
# 大致思路
首先由于要从最小的差值选起，进行一些动态操作，于是我们可以想到使用一个优先差值升序、其次第一人编号升序的优先队列，存储每一对相邻男女的位置与差值。每次取出队首，直到队列为空。其次，我们考虑以下情况：\
共有四人：
| 序号 | 性别 | 能力 |
|:----:|:----:|:----:|
|  1   |  男  |   1  |
|  2   |  女  |   3  |
|  3   |  男  |   4  |
|  4   |  女  |   6  |

队列中有如下元素：
| 序号 | 第一人位置 | 第二人位置 | 差值 |
|:----:|:----------:|:----------:|:-----:|
|  1   |     2      |     3      |  1    |
|  2   |     1      |     2      |  2    |
|  3   |     3      |     4      |  2    |

经过一次操作后，取出第 $2$ 个人和第 $3$ 个人。
| 序号 | 性别 | 能力 |
|:----:|:----:|:----:|
|  1   |  男  |   1  |
|  4   |  女  |   6  |

我们发现，应当把队列中编号为 $1$、$2$、$3$ 的、也就是二人中含有 $2$、$3$ 的删除，处理这种个情况，我们可以使用一个 $vis$ 数组标记无效的编号，如果队首元素含有无效编号，跳过即可。
另外，还需要添加一个：

| 序号 | 第一人位置 | 第二人位置 | 差值 |
|:----:|:----------:|:----------:|:-----:|
|  1   |     1      |     4      |   5   |

于是，为了避免修改造成时间复杂度的增加，我们采用双向链表进行快速删除元素并快速得到选中二人的前一人、后一人，并将此二人连接并入队。\
总体来讲，时间复杂度为 $O(n \log n)$，对于 $1 \le n \le 2 \times 10^{5} $，可以通过。
# 关于初始化
本题的优先队列、链表均需初始化。
- 优先队列：对于每一个 $1 \le i < n$ 如果第 $i$ 个人与第 $i+1$ 个人是不同性别的，则将它们入队。
- 链表：对于每一个 $1 \le i < n$，连接 $i$ 与 $i+1$ 即可。
# 写代码前的前置知识
对于本体涉及的优先队列与双向链表，建议过一过[P1090合并果子](https://www.luogu.com.cn/problem/P1090)和[B3631单项链表](https://www.luogu.com.cn/problem/B3631)（其实双向链表与单向链表差不多，只不过多了一个指向上一个元素的指针而已）。
# AC 代码

```cpp
#include<iostream>
#include<queue> 
#include<cmath> 
using namespace std;
const int N=2e5+5;
struct Node{
	int pre,nxt,data;
	bool operator<(const Node &nd)const{//重载运算符，注意与实际相反 
		if(data==nd.data)return pre>nd.pre;
		return data>nd.data;
	}
}l[N],ans[N];//链表与记录答案的数组（借用一下pre和nxt，免再定义struct，实际用于优先队列） 
int a[N];//能力 
bool vis[N];//是否被选出 

priority_queue<Node> q;
int main(){
//输入 
	int n;
	string str;
	cin>>n;
	cin>>str;
	str=" "+str;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
//初始化 
	for(int i=1;i<n;i++){
		if(str[i]!=str[i+1]){
			q.push({i,i+1,abs(a[i+1]-a[i])});
		}
		l[i].nxt=i+1;
		l[i+1].pre=i;
	}
	int len=0;
	while(q.size()){//循环遍历队列 
		Node t=q.top();
		q.pop();
		if(vis[t.pre] || vis[t.nxt])continue;//被取出过 
		vis[t.pre]=vis[t.nxt]=true;//标记 
		ans[++len]={t.pre,t.nxt,t.data};
		int pre=l[t.pre].pre;//第一个人的前一个人 
		int nxt=l[t.nxt].nxt;//第二个人的后一个人 
		if(pre*nxt==0)continue;//有一个为0（0代表没有前/后一个） 
		if(str[pre]!=str[nxt]){
			q.push({pre,nxt,abs(a[nxt]-a[pre])});
		}
		//删除 
		l[pre].nxt=nxt;
		l[nxt].pre=pre;
	}
//输出 
	cout<<len<<'\n';
	for(int i=1;i<=len;i++){
		cout<<ans[i].pre<<" "<<ans[i].nxt<<'\n';
	}
	return 0;
}
```

---

## 作者：Liuliuliuliuliu (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF45C)

# 思路

先想朴素的暴力。每次选取没有出队的一男一女，出队。明显过不了。

然后可以看到这道题需要求差值最小的一对，于是就想到了用堆来做。先 $O(n)$ 循环一遍，选满足条件的一男一女入队。然后只要队列非空，就记入答案，同时更新队列。具体如下。
```
int n;
int ansx[N],ansy[N],tot=0;//记录答案
bool vis[N];//判断是否出队
char s[N];
struct node2{
	int sex,x;
}a[N];
struct node{
	int data,id1,id2;
	bool operator < (const node &A) const {
		return data==A.data?id1>A.id1:data>A.data;
	}
}; 
priority_queue<node> q;
signed main(){
	n=Read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='B') a[i].sex=1;
		else a[i].sex=2;
	}
	for(int i=1;i<=n;i++){
		a[i].x=Read();
	}
	vis[0]=vis[n+1]=1;
	for(int i=2;i<=n;i++){
		int l=i-1,r=i;
		if(a[l].sex!=a[r].sex) {
			q.push((node){abs(a[l].x-a[r].x),l,r}); 
		}
	}
	
	while(!q.empty()){
		node t=q.top();
		if(!vis[t.id1]&&!vis[t.id2]){
			++tot;
			ansx[tot]=t.id1;
			ansy[tot]=t.id2;
			vis[t.id1]=1;
			vis[t.id2]=1;
			q.pop();
		}
		else {
			q.pop();
			continue;
		}
		int l=t.id1-1,r=t.id2+1;
		if(l<1||r>n) continue;
		if(a[l].sex!=a[r].sex){
			q.push((node){abs(a[l].x-a[r].x),l,r}); 
		}
	}
	printf("%lld\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%lld %lld\n",ansx[i],ansy[i]);
	}
	return 0;
} 
```

然后你会发现喜提 $0$ pts。

hack数据（[来源](https://www.luogu.com.cn/discuss/906296)）。
```
in：
6
GBGBBG
3 1 2 100 3 7
expected:
3
2 3
5 6
1 4
```

于是继续思考。发现 $l$ 和 $r$ 两边的人不一定是 $l-1$ 和 $r+1$，所以应该预处理出每个人的前一个人和后一个人。如下。
```
for(int i=1;i<=n;i++){
  pre[i]=i-1;
  suf[i]=i+1;
}
```

```
suf[pre[t.id1]]=suf[t.id2];
pre[suf[t.id2]]=pre[t.id1];
int l=pre[t.id1],r=suf[t.id2];
```

这样这道题就结束了。

# 代码
```
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long 
#define INF 0x3f3f3f3f
inline int Read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,pre[N],suf[N];
int ansx[N],ansy[N],tot=0;
bool vis[N];
char s[N];
struct node2{
	int sex,x;
}a[N];
struct node{
	int data,id1,id2;
	bool operator < (const node &A) const {
		return data==A.data?id1>A.id1:data>A.data;
	}
}; 
priority_queue<node> q;
signed main(){
	n=Read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='B') a[i].sex=1;
		else a[i].sex=2;
	}
	for(int i=1;i<=n;i++){
		a[i].x=Read();
	}
	for(int i=1;i<=n;i++){
		pre[i]=i-1;
		suf[i]=i+1;
	}
	vis[0]=vis[n+1]=1;
	for(int i=2;i<=n;i++){
		int l=i-1,r=i;
		if(a[l].sex!=a[r].sex) {
			q.push((node){abs(a[l].x-a[r].x),l,r}); 
		}
	}
	while(!q.empty()){
		node t=q.top();q.pop();
		if(vis[t.id1]||vis[t.id2]) continue;
		++tot;
		ansx[tot]=t.id1;
		ansy[tot]=t.id2;
		vis[t.id1]=1;
		vis[t.id2]=1;
		suf[pre[t.id1]]=suf[t.id2];
		pre[suf[t.id2]]=pre[t.id1];
		int l=pre[t.id1],r=suf[t.id2];
		if(vis[l]||vis[r]) continue;
		if(a[l].sex!=a[r].sex){
			q.push((node){abs(a[l].x-a[r].x),l,r}); 
		}
	}
	printf("%lld\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%lld %lld\n",ansx[i],ansy[i]);
	}
	return 0;
} 
```

---

## 作者：XiaoXia_uwu (赞：0)

# CF45C Dancing Lessons
## 题意
给你一个长度为 $n$ 的字符串，以及长度为 $n$ 的数组，让你每次删除字符串中相邻字符不同，且对应数组元素差值最小的那一对。如果有多对，选最左边那一对。让你模拟并输出第几次删了哪一对元素。
## 大概思路
_题目让我们模拟，我们就直接模拟。看了一圈都是用 struct 链表模拟的，那我就发一个不用 struct 模拟的版本吧。感受一下 STL 的魅力吧。_

首先得解决，一共有多少对输出。显然，只要字符串中同时存在 “B” 和 “G”，那么必然会出现二者相邻的情况，所以输出对数应该是 $\min(cnt_G,~cnt_B) $，即输出对数取决于数量较少的那个字符。

然后接下来考虑怎么模拟这个过程：

>我们知道，std::map 是有序的，通过 .find() 成员函数，我们可以获得对应键值的迭代器，那么自然地我们就能通过这个迭代器访问该键值的“前驱”和“后继”，从而实现模拟链表的需求。
>
>我们可以先将信息全部丢到 map 里面：
>
>```cpp
>std::map<int, std::pair<char, int>> treap;
>for (int i = 1; i <= n; i++) {
>    int x;
>    std::cin >> x;
>    treap[i] = {s[i], x};
>}
>```

为了维护哪一对相邻字符的对应权值相差最小，我们可以先暴力 $O(n)$ 扫一遍字符串，统计所有相邻字符不同的情况，把权值差、左边的下标、右边的下标收集到优先队列里。

>这里我选用 set 代替了 priorty_queue，具体为什么，后面再讲：
>```cpp
>std::set<std::array<int, 3>> q;
>for (int i = 2; i <= n; i++) {
>    if (s[i] != s[i - 1]) {
>        q.insert({std::abs(treap[i].second - treap[i - 1].second), i - 1, i});
>    }
>}
>```

然后就可以开始一个个用 .begin() 从集合里弹出权值差最小的那对相邻下标 $l$ 和 $r$ 并输出了。

但是要注意，输出后，我们还得考虑三种特殊情况：

- 这对下标删除前，左边是否有其它的相邻字符与这对下标产生了贡献？
- 这对下标删除前，右边是否有其它的相邻字符与这对下标产生了贡献？
- 这对下标删除后，两边的字符串拼接到一起，是否会产生新的贡献对？

对于前两种情况，我们可以结合 map 的迭代器来查询前驱后继，然后把多余的贡献用 .erase() 从优先队列中剔除（这就是为什么要用 set 代替 priority_queue 的原因，pq 是不支持删除中间的元素的）

对于后一种情况，把贡献用 .insert() 补回来就行。

最后更新完，记得把 $l$ 和 $r$ 从 map 中 erase 掉，保证 map 能够继续行使链表的功能。
## 参考代码
```cpp
void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s = " " + s;

    std::map<int, std::pair<char, int>> treap;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        treap[i] = {s[i], x};
        if (s[i] == 'B') cnt++;
    }

    std::cout << std::min(cnt, n - cnt) << "\n";

    std::set<std::array<int, 3>> q;
    for (int i = 2; i <= n; i++) {//暴力统计当前所有不相等的相邻对
        if (s[i] != s[i - 1]) {
            q.insert({std::abs(treap[i].second - treap[i - 1].second), i - 1, i});
        }
    }

    while (q.size()) {
        auto [_, l, r] = *q.begin();
        q.erase(q.begin());
        std::cout << l << " " << r << "\n";

        if (treap.find(l) != treap.begin()) {//排除左边的额外贡献
            if (s[(--treap.find(l)) -> first] != s[l]) {
                q.erase({std::abs((--treap.find(l)) -> second . second - treap[l].second), (--treap.find(l)) -> first, l});
            }
        }
        if (treap.find(r) != --treap.end()) {//排除右边的额外贡献
            if (s[(++treap.find(r)) -> first] != s[r]) {
                q.erase({std::abs((++treap.find(r)) -> second . second - treap[r].second), r, (++treap.find(r)) -> first});
            }
        }
        if (treap.find(l) != treap.begin() && treap.find(r) != --treap.end() && s[(--treap.find(l)) -> first] != s[(++treap.find(r)) -> first]) {
            q.insert({//补上新的贡献
                std::abs((--treap.find(l)) -> second . second - (++treap.find(r)) -> second . second),
                (--treap.find(l)) -> first,
                (++treap.find(r)) -> first
            });
        }
        //map返回的迭代器是个pair，first是键，second是值

        treap.erase(l);//记得删多余的贡献
        treap.erase(r);
    }
}
```

---

## 作者：Jin_Yichen (赞：0)

# 洛谷CF45C题解
### [题目传送门](https://www.luogu.com.cn/problem/CF45C)

## 题意：
给定一个长度为 $n$ 的序列，每次从中选出一对差值最小的并且相邻的男女组合，记录位置并输出，直至无组合为止。

## 解析：
每次都删除一对男女，所以肯定会有新组合出现。

我们可以创建一个结构体，在里面存入与之相邻的人。

考虑 BFS 算法。每次一有符合条件的男女时，便把他们存入答案数组中，并删除。再重复操作。

然后，题目就做完了。

## code：
代码长，勿喷。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, ans, l[N], r[N];
bool vis[N];

int read() {
    int x = 0;
    char c = getchar();
    while (c > '9' || c < '0')
        c = getchar();
    while (c <= '9' && c >= '0')
        x = (x << 1) + (x << 3) + c - '0', c = getchar();
    return x;
}

struct node {
    int left, right, differ;
    bool operator <(const node &a)const {
        if (a.differ != differ)
            return a.differ < differ;
        else
            return a.left < left;
    }
} xe, ye;
priority_queue<node> que;

struct edge {
    int left, right, num;
    char gender;
} k[N];

void add1(int x, int num) {
    if (k[x + 1].gender != k[x].gender) {
        xe.differ = abs(k[x + 1].num - k[x].num);
        xe.left = x, xe.right = x + 1;
        que.push(xe);
    }
}

void add2(int x, int y) {
    ye.differ = abs(k[x].num - k[y].num);
    ye.left = x, ye.right = y;
    que.push(ye);
}

void bfs() {
    while (!que.empty()) {
        node head = que.top();
        que.pop();
        if (vis[head.left] || vis[head.right])
            continue;
        vis[head.left] = true, vis[head.right] = true;
        int x = k[head.left].left, y = k[head.right].right;
        k[x].right = y, k[y].left = x;
        if (x >= 1 && x <= n && y >= 1 && y <= n && k[x].gender != k[y].gender)
            add2(x, y);
        ans++;
        l[ans] = head.left, r[ans] = head.right;
    }
}

int main() {
    n=read();
    for (int i = 1; i <= n; i++)
        k[i].gender = getchar();
    for (int i = 1; i <= n; i++) {
        k[i].num=read();//一定要用快读！！！
        k[i].left = i - 1, k[i].right = i + 1;
    }
    for (int i = 1; i < n; i++)
        add1(i, k[i].num);
    bfs();
    printf("%d\n", ans);
    for (int i = 1; i <= ans; i++)
        printf("%d %d\n", l[i], r[i]);
    return 0;//完结撒花
}
```


---

## 作者：nxd_oxm (赞：0)

# 题意
我们的题目说啊，有一群男生女生站成一排，相邻的异性可以组成一组，每次捏就选取舞蹈技能差值最小的一组，把他们两个挑出来，如果有一样的就选取最左边的。（重点！）

# 思路
首先我们要非常方便的找的左右，并且还要方便的删除，那肯定是用链表。

我们要找出差值最小的一组，还得找 $n$ 次，那最好用优先队列，找出差值最小的一对。

先定义一个结构体，把它作为优先队列的载体。每个值存他们的差值 ``to``，左边人的编号 ``left``，右边人的编号 ``right``。

只要每次取出优先队列的队首，将他们存起来，再检测新位置补上后会不会出现一男一女在一起，如果有就入队。

注意要拿个数组存一下当前的左右两人出队没，出对了就不能再算了。

一定要注意，差值相同的要拿最左边的，写结构体排序的函数的时候就得注意加上。

~~（我就被坑了半个小时）~~

不会超时，时间复杂度应该是 $n \log n$。
## AC code
```cpp
#include<bits/stdc++.h>
#include<queue>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
struct anv{
	int to;
	char gen;
	int left;
	int right;
}a[200001];
struct av{
	int to;
	int left;
	int right;
	av(int t,int l,int r):to(t),left(l),right(r){
	}
	friend bool operator > (struct av a,struct av b){
		return a.to==b.to?a.left>b.left:a.to>b.to;
	}
};
int p[200001][2]={},pi;
bool vis[200001];
priority_queue<av,vector<av>,greater<av> >q;
signed main(){
	int n;
	cin>>n;
	a[0].right=1;
	f(i,1,n){
		a[i].left=i-1;
		a[i].right=i+1;
	}
	f(i,1,n){
		cin>>a[i].gen;
	}
	f(i,1,n){
		cin>>a[i].to;
		if(i>1&&a[i-1].gen!=a[i].gen){
			q.push(av(abs(a[i-1].to-a[i].to),i-1,i));
		}
	}
	while(q.empty()==0){
		av t=q.top();
		q.pop();
		if(vis[t.left]||vis[t.right]){
			continue;
		}
		pi++;
		p[pi][0]=t.left;
		p[pi][1]=t.right;
		int l=t.left,r=t.right;
		vis[l]=vis[r]=1;
		a[a[l].left].right=a[r].right;
		a[a[r].right].left=a[l].left;
		if(a[l].left>=1&&a[r].right>=1&&a[r].right<=n&&a[a[l].left].gen!=a[a[r].right].gen){
			q.push(av(abs(a[a[l].left].to-a[a[r].right].to),a[l].left,a[r].right));
		}
	}
	cout<<pi<<endl;
	f(i,1,pi){
		cout<<p[i][0]<<" "<<p[i][1]<<endl;
	}
	return 0;
}
```
这里用了一下循环的简便写法，就定义了一个宏。

看 $4$ 行。

---

